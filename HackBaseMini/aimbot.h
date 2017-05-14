#pragma once
#include "main.h"

#define PITCH 0 //up/down
#define YAW 1 // left/right
#define ROLL //fall over
struct aimbot_s {
	static bool bVisible(int iIndex);
	static bool bCheckTeam(int iIndex);
	static bool bIsValidEnt(int iIndex);

	static void MyVectorAngles(const float *forward, float *angles);
	static void CL_CreateMove(usercmd_s *cmd);
};
extern aimbot_s g_Aimbot;