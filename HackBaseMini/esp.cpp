#include "main.h"
#include "esp.h"
#include "aimbot.h" 
#include <math.h>

// up / down
#define	PITCH	0
// left / right
#define	YAW		1
// fall over
#define	ROLL	2 
#define M_PI 3.14159265359
#pragma warning(disable : 4244)
esp_s g_Esp;
bool esp_s::bCalcScreen(float *pflOrigin, float *pflVecScreen) //world to screenfunction 
{
	int iResult = g_Engine.pTriAPI->WorldToScreen(pflOrigin, pflVecScreen);

	if (pflVecScreen[0] < 1 && pflVecScreen[1] < 1 && pflVecScreen[0] > -1 && pflVecScreen[1] > -1 && !iResult)
	{
		pflVecScreen[0] = pflVecScreen[0] * (g_Screen.iWidth / 2) + (g_Screen.iWidth / 2);
		pflVecScreen[1] = -pflVecScreen[1] * (g_Screen.iHeight / 2) + (g_Screen.iHeight / 2);
		return true;
	} return false;
}
void GetBoneOrigin(cl_entity_s *ent)
{
	if (ent && ent->player && ent->index != -1 && ent->index != g_Local.iIndex && g_Aimbot.bIsValidEnt(ent->index))
	{
		model_t* pModel = g_Studio.SetupPlayerModel(ent->index);
		studiohdr_t* pStudioHeader = (studiohdr_t*)g_Studio.Mod_Extradata(pModel);
		typedef float TransformMatrix[MAXSTUDIOBONES][3][4];
		TransformMatrix*  pbonetransform = (TransformMatrix*)g_Studio.StudioGetBoneTransform();
		for (int i = 0; i <= 52; i++)
		{
			g_Player[ent->index].vBone[i][0] = (*pbonetransform)[i][0][3];
			g_Player[ent->index].vBone[i][1] = (*pbonetransform)[i][1][3];
			g_Player[ent->index].vBone[i][2] = (*pbonetransform)[i][2][3];
		}
	}
}
void esp_s::DrawDot(int iIndex, int bone)//рисуем точку 
{
	//if (g_PlayerTeam[iIndex] == g_Local.iTeam)return; //проверка на комманду
	int r = 255, g = 0, b = 255;
	if (g_Player[iIndex].bVisible) { g = 0; }    //если мы видим врага , то зеленый цвет = 0
	if (!g_Player[iIndex].bVisible) { g = 255; } //если же не видим , то зеленый цвет = 255
	if (g_PlayerTeam[iIndex] == 1) { r = 255, b = 0; } //Террористы красные
	if (g_PlayerTeam[iIndex] == 2) { r = 0, b = 255; } //Контр-террористы синие 
	GetBoneOrigin(g_Engine.GetEntityByIndex(iIndex));
	float flDrawPos[2];
	if (bCalcScreen(g_Player[iIndex].vBone[bone], flDrawPos))//высчитываем точку на экране с помощью Bone (место отрисоввки 
	{
		int x = (int)flDrawPos[0], y = (int)flDrawPos[1];
		g_Engine.pfnFillRGBA(x - 1, y + 1, 5, 5, r, g, b, 255);
	}
}
void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1 * sr*sp*cy + -1 * cr*-sy);
		right[1] = (-1 * sr*sp*sy + -1 * cr*cy);
		right[2] = -1 * sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy + -sr*-sy);
		up[1] = (cr*sp*sy + -sr*cy);
		up[2] = cr*cp;
	}
}
void DrawLine(int x1, int y1, int x2, int y2, int lw, color_s *pColor)
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(pColor->r, pColor->g, pColor->b, pColor->a);
	glLineWidth((float)lw);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
void DrawVectorLine(float *flSrc, float *flDestination, int lw, color_s *pColor)
{
	vec3_t vScreenSrc, vScreenDest;
	if (!esp_s::bCalcScreen(flSrc, vScreenSrc) || !esp_s::bCalcScreen(flDestination, vScreenDest))
		return;
	DrawLine((int)vScreenSrc[0], (int)vScreenSrc[1], (int)vScreenDest[0], (int)vScreenDest[1], lw, pColor);
}
void Draw3DBox(cl_entity_t *pEnt, color_s *pColor)
{
	if (!pEnt || !pColor)
		return;

	vec3_t vF, vR, vU;
	AngleVectors(Vector(0.0f, pEnt->angles[1], 0.0f), vF, vR, vU);

	//If you want only the hitbox of the player. simply make it only maxs & mins instead of adding numbers:P
	float flForward = pEnt->curstate.maxs.y + 15.0f;
	float flBack = pEnt->curstate.mins.y - 5.0f;
	float flRight = pEnt->curstate.maxs.x + 5.0f;
	float flLeft = pEnt->curstate.mins.x - 5.0f;

	vec3_t vUFLeft = pEnt->origin + vU*pEnt->curstate.maxs.z + vF*flForward + vR*flLeft; // vUFLeft = Top left front
	vec3_t vUFRight = pEnt->origin + vU*pEnt->curstate.maxs.z + vF*flForward + vR*flRight; // vUFRight = Top right front
	vec3_t vUBLeft = pEnt->origin + vU*pEnt->curstate.maxs.z + vF*flBack + vR*flLeft; // vUBLeft = Top left back
	vec3_t vUBRight = pEnt->origin + vU*pEnt->curstate.maxs.z + vF*flBack + vR*flRight; // vUBRight = Top right back

	vec3_t vBFLeft = pEnt->origin + vU*pEnt->curstate.mins.z + vF*flForward + vR*flLeft; // vBFLeft = Bottom left front
	vec3_t vBFRight = pEnt->origin + vU*pEnt->curstate.mins.z + vF*flForward + vR*flRight; // vBFRight = Bottom right front
	vec3_t vBBLeft = pEnt->origin + vU*pEnt->curstate.mins.z + vF*flBack + vR*flLeft; // vBBLeft = Bottom left back
	vec3_t vBBRight = pEnt->origin + vU*pEnt->curstate.mins.z + vF*flBack + vR*flRight; // vBBRight = Bottom right back

																						//Top Box
	DrawVectorLine(vUBLeft, vUBRight, 1, pColor); // Back left -> Back right
	DrawVectorLine(vUBRight, vUFRight, 1, pColor); // Back right -> Front right
	DrawVectorLine(vUFRight, vUFLeft, 1, pColor); // Front right -> Front left
	DrawVectorLine(vUFLeft, vUBLeft, 1, pColor); // Front left -> Back right

												 //Mid Box
	DrawVectorLine(vUBLeft, vBBLeft, 1, pColor); // Top left -> Bottom left
	DrawVectorLine(vUBRight, vBBRight, 1, pColor); // Top right -> Bottom right
	DrawVectorLine(vUFRight, vBFRight, 1, pColor); // Top right -> Bottom right
	DrawVectorLine(vUFLeft, vBFLeft, 1, pColor); // Top left -> Bottom left

												 //Bottom Box
	DrawVectorLine(vBBLeft, vBBRight, 1, pColor); // Back left -> Back right
	DrawVectorLine(vBBRight, vBFRight, 1, pColor); // Back right -> Front right
	DrawVectorLine(vBFRight, vBFLeft, 1, pColor); // Front right -> Front left
	DrawVectorLine(vBFLeft, vBBLeft, 1, pColor); // Front left -> Back right
}

void esp_s::HUD_Redraw(int iIndex,int bone) {
	if (g_Aimbot.bIsValidEnt(iIndex)) //включен ли есп и валидный ли игрок
	{
		color_s* redcolor= new color_s;
		redcolor->r = 255;
		redcolor->g = 0;
		redcolor->b = 0;
		redcolor->a = 1;
		DrawDot(iIndex,bone);//если esp_dot включен - рисуем точку
		Draw3DBox(g_Engine.GetEntityByIndex(iIndex),redcolor);
	}
}
