class esp_s //создаем класс под названием esp_s 
{
	public: //эти элементы класса можно будет изменять
		static bool bCalcScreen(float *pflOrigin, float *pflVecScreen);  //Считаем положение на экране и проверяем находится ли враг в видимости
		static void DrawDot(int iIndex, int bone);
		/*void Draw3DBox(cl_entity_t * pEnt, color_s * pColor);
		void DrawVectorLine(float * flSrc, float * flDestination, int lw, color_s * pColor);
		void DrawLine(int x1, int y1, int x2, int y2, int lw, color_s * pColor);*/
		//Будем рисовать точку на врагах
		static void HUD_Redraw(int iIndex,int bone); //Тут мы будем вызывать все ESP(виды) , которые мы сделаем 
};
extern esp_s g_Esp;