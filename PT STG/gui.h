
class gui {
public:
	int stats;
	int x;
	int y;
	int h;
	int w;
	unsigned int normal_color;
	unsigned int over_color;

	bool draw_Button(int mx, int my, int mw, int mh, unsigned int normal, unsigned int over, const char *str);
};

class combo {
public:
	int select = 0;
	int stats = 0;
	int x;
	int y;
	int w;
	int list_num;
	gui com_button;

	int  draw_Combo(int mx, int my, int mw, int list, char **list_str);
	int  init_Combo(int selected);
};