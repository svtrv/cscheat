#include "aimbot.h" // получаем данные структуры из aimbot.h 
#include "main.h" // тут хранится информаци о локальном игроке (о нас) и о других игроках 

#pragma warning (disable:4244) // убераем лишнии предупреждения   
aimbot_s g_Aimbot; // даем нашей структуре имя (к которому мы и будем обращаться далее) 
float fAimAngles[3]={}; // fAimAngles - двумерный массив , который будет содержать в себе координаты в 2D пространстве (то есть на экране)   
#define M_PI 3.14159265359
void aimbot_s::MyVectorAngles(const float *forward, float *angles)//считаем угол для aimbot'a 
{
	float tmp, yaw, pitch;
	if (forward[1] == 0 && forward[0] == 0) {
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;
		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)             pitch += 360;
	}     angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
	while (angles[0] < -89) { angles[0] += 180; angles[1] += 180; }
	while (angles[0] > 89) { angles[0] -= 180; angles[1] += 180; }
	while (angles[1] < -180) { angles[1] += 360; }
	while (angles[1] > 180) { angles[1] -= 360; }
}
bool aimbot_s::bIsValidEnt(int iIndex)//определяем жив ли игрок (валидность) 
{
	/*cl_entity_s *ent = g_Engine.GetEntityByIndex(iIndex);
	if (ent->player && g_Local.iIndex != ent->index && ent->curstate.movetype != 6 && ent->curstate.movetype != 0  && !(g_Engine.GetLocalPlayer()->curstate.iuser1 == 4 && g_Engine.GetLocalPlayer()->curstate.iuser2 == ent->index)) {
		return true;
	}
	else {
		return false;
	}*/return true;
}
bool aimbot_s::bVisible(int iIndex) // обращение к члену структуры aimbot_s 
{
	if (!g_Player[iIndex].bVisible) return false;
	return true;
	//если мы не хотим стрелять через стены и не видим его , то возвращаем false    
	//если одно из условий не выполняется , то возвращаем true
}
bool aimbot_s::bCheckTeam(int iIndex) // обращение к члену структуры aimbot_s 
{
	if (g_PlayerTeam[iIndex] == g_Local.iTeam)return false;     return true;     //если мы не хотим стрелять по врагам и комманда игрока = нашей комманде, то возвращаем false     
																								  //если одно из условий не выполняется , то возвращаем true 
}
/*void aimbot_s::CL_CreateMove(struct usercmd_s *cmd) // обращение к члену структуры aimbot_s , вот он наш aimbot
{
		for (int i = 1; i < 33; i++)//цикл , который обрабатывае всех игроков       
		{//ID игрока в цикле = ID игрока в status листе (standar cs console command)       
			if (!bIsValidEnt(i))continue; //валидный ли игрок?        
			if (!bCheckTeam(i))continue; //союзник ли он ?           
			if (!bVisible(i))continue; //за стеной ли он ?          
			Vector EnemyOrigin = Vector(g_Player[i].vOrigin.x, g_Player[i].vOrigin.y, g_Player[i].vOrigin.z + cvar.aim_height->value); //Получаем координаты игроков и добавляем свое значение по оси z  
			MyVectorAngles(EnemyOrigin - g_Local.vEye, fAimAngles); //считаем и записываем координаты в fAimAngles     
			if (cmd->buttons&IN_ATTACK)g_Engine.SetViewAngles(fAimAngles);
			//если мы нажимаешь +attack - нацеливаемся на врага       
		}
}*/