class esp_s //������� ����� ��� ��������� esp_s 
{
	public: //��� �������� ������ ����� ����� ��������
		static bool bCalcScreen(float *pflOrigin, float *pflVecScreen);  //������� ��������� �� ������ � ��������� ��������� �� ���� � ���������
		static void DrawDot(int iIndex, int bone);
		/*void Draw3DBox(cl_entity_t * pEnt, color_s * pColor);
		void DrawVectorLine(float * flSrc, float * flDestination, int lw, color_s * pColor);
		void DrawLine(int x1, int y1, int x2, int y2, int lw, color_s * pColor);*/
		//����� �������� ����� �� ������
		static void HUD_Redraw(int iIndex,int bone); //��� �� ����� �������� ��� ESP(����) , ������� �� ������� 
};
extern esp_s g_Esp;