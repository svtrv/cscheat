#include "main.h"

pfnUserMsgHook pResetHUD;
pfnUserMsgHook pSetFOV;
pfnUserMsgHook pTeamInfo;
pfnUserMsgHook pCurWeapon;
pfnUserMsgHook pDeathMsg;
pfnUserMsgHook pHealth;
int v_Health;
int v_SpecHealth;
int v_SpecHealth2;
int v_ID;

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
	v_Health = READ_BYTE();
	g_Engine.Con_Printf("Health=%i", v_Health);
	return pDeathMsg( pszName , iSize , pbuf );
}

int SpecHealth( const char *pszName , int iSize , void *pbuf )
{
	BEGIN_READ(pbuf, iSize);
	v_SpecHealth = READ_BYTE();
	g_Engine.Con_Printf("SpechHealth=%i", v_SpecHealth);
	return pDeathMsg( pszName , iSize , pbuf );
}

int SpecHealth2( const char *pszName , int iSize , void *pbuf )
{
	BEGIN_READ(pbuf, iSize);
	v_SpecHealth2 = READ_BYTE();
	v_ID = READ_BYTE();
	g_Engine.Con_Printf("SpechHealth2=%i\nID=%i", v_SpecHealth2, v_ID);
	return pDeathMsg( pszName , iSize , pbuf );
}