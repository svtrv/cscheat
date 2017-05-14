#include "main.h"

pfnUserMsgHook pResetHUD;
pfnUserMsgHook pSetFOV;
pfnUserMsgHook pTeamInfo;
pfnUserMsgHook pCurWeapon;
pfnUserMsgHook pDeathMsg;
pfnUserMsgHook pHealth;


int ResetHUD( const char *pszName , int iSize , void *pbuf )
{
	return pResetHUD( pszName , iSize , pbuf );
}

int SetFOV( const char *pszName , int iSize , void *pbuf )
{
	return pSetFOV( pszName , iSize , pbuf );
}

/*int TeamInfo( const char *pszName , int iSize , void *pbuf )
{
	return pTeamInfo( pszName , iSize , pbuf );
}*/
int TeamInfo(const char *pszName, int iSize, void *pbuf)
{
	BEGIN_READ(pbuf, iSize);

	int iIndex = READ_BYTE();
	char *szTeam = READ_STRING();

	_strlwr(szTeam);

	if (!strcmp(szTeam, "terrorist"))
	{
		g_PlayerTeam[iIndex] = 1;
		if (iIndex == g_Local.iIndex) { g_Local.iTeam = 1; }
	}
	else if (!strcmp(szTeam, "ct"))
	{
		g_PlayerTeam[iIndex] = 2;
		if (iIndex == g_Local.iIndex) { g_Local.iTeam = 2; }
	}
	else
	{
		g_PlayerTeam[iIndex] = 0;
		if (iIndex == g_Local.iIndex) { g_Local.iTeam = 0; }
	}
	//g_Local.bAlive = g_Player[iIndex].bAlive;
	return (*pTeamInfo)(pszName, iSize, pbuf);
}
int CurWeapon( const char *pszName , int iSize , void *pbuf )
{
	return pCurWeapon( pszName , iSize , pbuf );
}

int DeathMsg( const char *pszName , int iSize , void *pbuf )
{
	return pDeathMsg( pszName , iSize , pbuf );
}

int Health( const char *pszName , int iSize , void *pbuf )
{
	BEGIN_READ(pbuf, iSize);
	int Health = READ_BYTE();
	g_Engine.Con_Printf("%i", Health);
	g_Local.bAlive = Health > 0;
	return pDeathMsg( pszName , iSize , pbuf );
}