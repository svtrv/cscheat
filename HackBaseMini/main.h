#pragma once

#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;

#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib,"opengl32")

#include "ValveSDK/engine/wrect.h"
#include "ValveSDK/engine/cl_dll.h"
#include "ValveSDK/engine/r_studioint.h"
#include "ValveSDK/engine/cl_entity.h"
#include "ValveSDK/misc/com_model.h"
#include "ValveSDK/engine/triangleapi.h"
#include "ValveSDK/engine/pmtrace.h"
#include "ValveSDK/engine/pm_defs.h"
#include "ValveSDK/engine/pm_info.h"
#include "ValveSDK/common/ref_params.h"
#include "ValveSDK/common/studio_event.h"
#include "ValveSDK/common/net_api.h"
#include "ValveSDK/common/r_efx.h"
#include "ValveSDK/engine/cvardef.h"
#include "ValveSDK/engine/util_vector.h"
#include "ValveSDK/misc/parsemsg.h"
#include "ValveSDK/engine/studio.h"
#include "ValveSDK/engine/event_args.h"
#include "ValveSDK/engine/event_flags.h"
#include "ValveSDK/common/event_api.h"
#include "ValveSDK/common/screenfade.h"
#include "ValveSDK/engine/keydefs.h"
#include "ValveSDK/common/engine_launcher_api.h"
#include "ValveSDK/common/entity_types.h"

extern int g_PlayerTeam[33];
struct color_s {
	int r;
	int g;
	int b;
	float a;
};
typedef struct cl_clientfuncs_s
{
	int( *Initialize ) ( cl_enginefunc_t *pEnginefuncs , int iVersion );
	int( *HUD_Init ) ( void );
	int( *HUD_VidInit ) ( void );
	void( *HUD_Redraw ) ( float time , int intermission );
	int( *HUD_UpdateClientData ) ( client_data_t *pcldata , float flTime );
	int( *HUD_Reset ) ( void );
	void( *HUD_PlayerMove ) ( struct playermove_s *ppmove , int server );
	void( *HUD_PlayerMoveInit ) ( struct playermove_s *ppmove );
	char( *HUD_PlayerMoveTexture ) ( char *name );
	void( *IN_ActivateMouse ) ( void );
	void( *IN_DeactivateMouse ) ( void );
	void( *IN_MouseEvent ) ( int mstate );
	void( *IN_ClearStates ) ( void );
	void( *IN_Accumulate ) ( void );
	void( *CL_CreateMove ) ( float frametime , struct usercmd_s *cmd , int active );
	int( *CL_IsThirdPerson ) ( void );
	void( *CL_CameraOffset ) ( float *ofs );
	struct kbutton_s *( *KB_Find ) ( const char *name );
	void( *CAM_Think ) ( void );
	void( *V_CalcRefdef ) ( struct ref_params_s *pparams );
	int( *HUD_AddEntity ) ( int type , struct cl_entity_s *ent , const char *modelname );
	void( *HUD_CreateEntities ) ( void );
	void( *HUD_DrawNormalTriangles ) ( void );
	void( *HUD_DrawTransparentTriangles ) ( void );
	void( *HUD_StudioEvent ) ( const struct mstudioevent_s *event , const struct cl_entity_s *entity );
	void( *HUD_PostRunCmd ) ( struct local_state_s *from , struct local_state_s *to , struct usercmd_s *cmd , int runfuncs , double time , unsigned int random_seed );
	void( *HUD_Shutdown ) ( void );
	void( *HUD_TxferLocalOverrides ) ( struct entity_state_s *state , const struct clientdata_s *client );
	void( *HUD_ProcessPlayerState ) ( struct entity_state_s *dst , const struct entity_state_s *src );
	void( *HUD_TxferPredictionData ) ( struct entity_state_s *ps , const struct entity_state_s *pps , struct clientdata_s *pcd , const struct clientdata_s *ppcd , struct weapon_data_s *wd , const struct weapon_data_s *pwd );
	void( *Demo_ReadBuffer ) ( int size , unsigned char *buffer );
	int( *HUD_ConnectionlessPacket ) ( struct netadr_s *net_from , const char *args , char *response_buffer , int *response_buffer_size );
	int( *HUD_GetHullBounds ) ( int hullnumber , float *mins , float *maxs );
	void( *HUD_Frame ) ( double time );
	int( *HUD_Key_Event ) ( int down , int keynum , const char *pszCurrentBinding );
	void( *HUD_TempEntUpdate ) ( double frametime , double client_time , double cl_gravity , struct tempent_s **ppTempEntFree , struct tempent_s **ppTempEntActive , int( *Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ) , void( *Callback_TempEntPlaySound )( struct tempent_s *pTemp , float damp ) );
	struct cl_entity_s *( *HUD_GetUserEntity ) ( int index );
	int( *HUD_VoiceStatus ) ( int entindex , qboolean bTalking );
	int( *HUD_DirectorMessage ) ( unsigned char command , unsigned int firstObject , unsigned int secondObject , unsigned int flags );
	int( *HUD_GetStudioModelInterface ) ( int version , struct r_studio_interface_s **ppinterface , struct engine_studio_api_s *pstudio );
	void( *HUD_CHATINPUTPOSITION_FUNCTION ) ( int *x , int *y );
	int( *HUD_GETPLAYERTEAM_FUNCTION ) ( int iplayer );
	void( *CLIENTFACTORY ) ( void );
} cl_clientfunc_t;
struct local_s
{
	bool bAlive;
	bool bCanReload;
	bool bInReload;
	bool bInJump;
	bool bFps;
	bool bBadWpn;
	bool bJumped;
	bool bCanShot;
	bool bSlowDown;
	bool bPlayerjb;
	bool bAtEnemy;
	bool bOnSurf;
	bool bNoRefresh;
	bool bShActive;
	bool bGoto;
	bool bCanAttack;
	bool bAttacking;
	bool bSteam;
	bool bConnected;
	bool bHaveAmmo;
	bool bOverView;
	bool bUseDisconnect;
	bool bFpsxActive;
	bool bOnLan;
	bool bInAttack1;
	bool bInAttack2;

	int iMoveType;
	int iIndex;
	int iTeam;
	int iClip;
	int iWeaponID;
	int iFOV;
	int iFlags;
	int iWaterLevel;
	int iUseHull;
	int iAirAccelerate;
	int iBombTime;

	float Height;
	float flXYspeed;
	float flMaxSpeed;
	float m_flNextSecondryAttack;
	float m_flNextPrimaryAttack;
	float m_flReload;
	float frametime;
	float flFallSpeed;
	float fOnLadder;
	float flGroundAngle;
	float fFps;
	float fAngleSpeed;
	float fVSpeed;
	float EdgeOffset;
	float fEdgeGroundAngle;
	float fSinYaw;
	float fMinusCosYaw;
	float mainViewAngles[3];
	float mainViewAngles_SinYaw;
	float mainViewAngles_CosYaw;

	SHORT bMouse1;

	Vector vOrigin;
	Vector vEye;
	Vector vEyePred;
	Vector vPunchangle;
	Vector vForward;
	Vector vRight;
	Vector vUp;
	Vector vVelocity;
	Vector vViewAngles;
	Vector vAngles;
	Vector vNospreadAng;
	Vector vNorecoilAng;
	Vector vViewOrg;
	Vector cmdviewangles;
	Vector vFlashOrigin;

	char* cConnectionStatus;

	net_status_s net_status;
};
extern local_s g_Local; 
struct player_s
{
	int iFrags;
	int iDeaths;
	int iTeamID;
	int iHealth;
	int iAimWeighting;
	int iHitpoints;

	bool bAlive;
	bool bUpdated;
	bool bVisible;
	bool bDucked;
	bool bPerfectWalled;
	bool bInFriendList;

	float fFov;
	float fDistance;
	float fldmFixTime;
	float flPredTime;
	float flPredOldTime;
	float fHeight;

	Vector vAngle;
	Vector vOrigin;
	Vector vHitbox[11];
	Vector vBone[52];
	Vector vPredVec;
	Vector vPredOldVec;
	Vector vAimOrigin;
	Vector vSoundOrigin;

	hud_player_info_t Info;
	cl_entity_s *pEnt;
};
extern player_s g_Player[33]; 
typedef struct TUserMsg
{
	int number;
	int size;
	char name[16];
	struct TUserMsg* next;
	pfnUserMsgHook pfn;
} *PUserMsg;

#include "CvarUtils.h"
#include "Offset.h"
#include "Client.h"
#include "UserMsgs.h"
#include "Utils.h"
#include "cFont.h"