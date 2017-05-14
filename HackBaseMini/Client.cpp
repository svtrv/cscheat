#include "main.h"
#include "UserMsgs.h"
#include "esp.h"
// для примера обычный bhop

cvar_s* bhop;
cvar_s* bone;
local_s g_Local;
player_s g_Player[33];
int g_PlayerTeam[33];
#define msgbox(n) MessageBoxA(NULL,n,"tkz",MB_OK);
void HookUserMessages()
{
	pUserMsgBase = c_Offset.FindUserMsgBase();

	pResetHUD = HookUserMsg( "ResetHUD" , ResetHUD );
	pSetFOV = HookUserMsg( "SetFOV" , SetFOV );
	pTeamInfo = HookUserMsg( "TeamInfo" , TeamInfo );
	pCurWeapon = HookUserMsg( "CurWeapon" , CurWeapon );
	pDeathMsg = HookUserMsg( "DeathMsg" , DeathMsg );
}

void InitHack()
{
	g_Engine.Con_Printf("\n\t%s\n\n", CL_INFO);
	bhop = g_Engine.pfnRegisterVariable("bhop", "1", 0);
	bone = g_Engine.pfnRegisterVariable("bone", "0", 0);
	g_Engine.pfnClientCmd("cl_crosshair_color 0 0 0");
}

void HUD_Frame( double time )
{
	static bool FirstFrame = true;

	if ( FirstFrame )
	{
		g_Screen.iSize = sizeof( SCREENINFO );
		g_Engine.pfnGetScreenInfo( &g_Screen );
		g_Info.InitText();
		HookUserMessages();
		InitHack();
		FirstFrame = false;
	}

	g_Engine.pfnGetScreenInfo( &g_Screen );
	return g_Client.HUD_Frame( time );
}

void HUD_Redraw( float time , int intermission )
{
	g_Client.HUD_Redraw( time , intermission );
	g_Engine.pfnFillRGBA(g_Screen.iWidth / 2 - 14, g_Screen.iHeight / 2, 9, 1, 154, 204, 255, 150);
	g_Engine.pfnFillRGBA(g_Screen.iWidth / 2 + 5, g_Screen.iHeight / 2, 9, 1, 154, 204, 255, 150);
	g_Engine.pfnFillRGBA(g_Screen.iWidth / 2, g_Screen.iHeight / 2 - 14, 1, 9, 154, 204, 255, 150);
	g_Engine.pfnFillRGBA(g_Screen.iWidth / 2, g_Screen.iHeight / 2 + 5, 1, 9, 154, 204, 255, 150);
	g_Engine.pfnFillRGBA(g_Screen.iWidth / 2, g_Screen.iHeight / 2, 1, 1, 154, 204, 255, 150);
	for (int i = 1; i < 33; i++)
	{
		int plyr = g_PlayerTeam[i];
		if (plyr != NULL) {
			g_Esp.HUD_Redraw(i,bone->value);
		}
	}
}

int HUD_Key_Event( int down , int keynum , const char *pszCurrentBinding )
{
	return g_Client.HUD_Key_Event( down , keynum , pszCurrentBinding );
}

// самый обычный bhop через кнопку space
void BhopFunction( usercmd_s *cmd )
{
	static bool bunnyhop = false;
	int IN_SPACE = GetAsyncKeyState( VK_SPACE );

	if ( bhop->value )
	{
		if ( cmd->buttons&IN_JUMP )
		{
			if ( bunnyhop && IN_SPACE )
			{
				cmd->buttons &= ~IN_JUMP;
				bunnyhop = false;
			}
			else
			{
				bunnyhop = true;
			}
		}
	}
}

void CL_CreateMove(float frametime, usercmd_s *cmd, int active)
{

	g_Client.CL_CreateMove(frametime, cmd, active);
	cl_entity_s *LocalEnt = g_Engine.GetLocalPlayer(); // создаем локальную entity (информация о нас)
	bool bAlive = LocalEnt && !(LocalEnt->curstate.effects & EF_NODRAW) && LocalEnt->player && LocalEnt->curstate.movetype != 6 && LocalEnt->curstate.movetype != 0; //проверка на нашу живучесть 
	static bool FirstFrame = true;
	if (FirstFrame&&bAlive)
	{
		for (int i = 1; i < 33; i++) 
		{
			int plyr = g_PlayerTeam[i];
			if (plyr != NULL) {
				cl_entity_s *ent = g_Engine.GetEntityByIndex(i);
				g_Engine.Con_Printf("\tint[%d], team: %d\n", i, plyr);//g_Engine.pfnConsolePrint();
			}
		}
		g_Engine.Con_Printf("\tint[%d] , player: %d\n", 5, g_PlayerTeam[5]);
		FirstFrame = false;
	}
	
	BhopFunction(cmd);
}

void SetViewAngles( float * Angles )
{
	//g_Engine.Con_Printf( "\tAngles_x: %0.2f , Angles_y: %0.2f\n" , Angles[0] , Angles[1] );
	g_Engine.SetViewAngles( Angles );
}

void SetRenderModel( struct model_s *model )
{
	//g_Engine.Con_Printf( "\tmodel: %s\n" , model->name );
	g_Studio.SetRenderModel( model );
}

void HookFunction()
{
	// Client Hook
	g_pClient->HUD_Frame = HUD_Frame;
	g_pClient->HUD_Redraw = HUD_Redraw;
	g_pClient->HUD_Key_Event = HUD_Key_Event;
	g_pClient->CL_CreateMove = CL_CreateMove;

	// Engine Hook
	g_pEngine->SetViewAngles = SetViewAngles;
	// Studio hook
	g_pStudio->SetRenderModel = SetRenderModel;
}