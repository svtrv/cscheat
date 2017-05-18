#pragma once

#include "Main.h"

int ResetHUD( const char *pszName , int iSize , void *pbuf );
int SetFOV( const char *pszName , int iSize , void *pbuf );
int TeamInfo( const char *pszName , int iSize , void *pbuf );
int NVGToggle( const char *pszName , int iSize , void *pbuf );
int CurWeapon( const char *pszName , int iSize , void *pbuf );
int DeathMsg( const char *pszName , int iSize , void *pbuf );
int Health( const char *pszName , int iSize , void *pbuf );
int SpecHealth( const char *pszName , int iSize , void *pbuf );
int SpecHealth2( const char *pszName , int iSize , void *pbuf );

extern pfnUserMsgHook pResetHUD;
extern pfnUserMsgHook pSetFOV;
extern pfnUserMsgHook pTeamInfo;
extern pfnUserMsgHook pCurWeapon;
extern pfnUserMsgHook pDeathMsg;
extern pfnUserMsgHook pHealth;