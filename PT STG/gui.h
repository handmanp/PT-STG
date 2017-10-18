
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