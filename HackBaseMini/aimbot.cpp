#include "aimbot.h" // �������� ������ ��������� �� aimbot.h 
#include "main.h" // ��� �������� ��������� � ��������� ������ (� ���) � � ������ ������� 

#pragma warning (disable:4244) // ������� ������ ��������������   
aimbot_s g_Aimbot; // ���� ����� ��������� ��� (� �������� �� � ����� ���������� �����) 
float fAimAngles[3]={}; // fAimAngles - ��������� ������ , ������� ����� ��������� � ���� ���������� � 2D ������������ (�� ���� �� ������)   
#define M_PI 3.14159265359
void aimbot_s::MyVectorAngles(const float *forward, float *angles)//������� ���� ��� aimbot'a 
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
bool aimbot_s::bIsValidEnt(int iIndex)//���������� ��� �� ����� (����������) 
{
	/*cl_entity_s *ent = g_Engine.GetEntityByIndex(iIndex);
	if (ent->player && g_Local.iIndex != ent->index && ent->curstate.movetype != 6 && ent->curstate.movetype != 0  && !(g_Engine.GetLocalPlayer()->curstate.iuser1 == 4 && g_Engine.GetLocalPlayer()->curstate.iuser2 == ent->index)) {
		return true;
	}
	else {
		return false;
	}*/return true;
}
bool aimbot_s::bVisible(int iIndex) // ��������� � ����� ��������� aimbot_s 
{
	if (!g_Player[iIndex].bVisible) return false;
	return true;
	//���� �� �� ����� �������� ����� ����� � �� ����� ��� , �� ���������� false    
	//���� ���� �� ������� �� ����������� , �� ���������� true
}
bool aimbot_s::bCheckTeam(int iIndex) // ��������� � ����� ��������� aimbot_s 
{
	if (g_PlayerTeam[iIndex] == g_Local.iTeam)return false;     return true;     //���� �� �� ����� �������� �� ������ � �������� ������ = ����� ��������, �� ���������� false     
																								  //���� ���� �� ������� �� ����������� , �� ���������� true 
}
/*void aimbot_s::CL_CreateMove(struct usercmd_s *cmd) // ��������� � ����� ��������� aimbot_s , ��� �� ��� aimbot
{
		for (int i = 1; i < 33; i++)//���� , ������� ����������� ���� �������       
		{//ID ������ � ����� = ID ������ � status ����� (standar cs console command)       
			if (!bIsValidEnt(i))continue; //�������� �� �����?        
			if (!bCheckTeam(i))continue; //������� �� �� ?           
			if (!bVisible(i))continue; //�� ������ �� �� ?          
			Vector EnemyOrigin = Vector(g_Player[i].vOrigin.x, g_Player[i].vOrigin.y, g_Player[i].vOrigin.z + cvar.aim_height->value); //�������� ���������� ������� � ��������� ���� �������� �� ��� z  
			MyVectorAngles(EnemyOrigin - g_Local.vEye, fAimAngles); //������� � ���������� ���������� � fAimAngles     
			if (cmd->buttons&IN_ATTACK)g_Engine.SetViewAngles(fAimAngles);
			//���� �� ��������� +attack - ������������ �� �����       
		}
}*/