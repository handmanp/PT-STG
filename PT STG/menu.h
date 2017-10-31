

class coolmenu {
public:
	int y = 280;
	int x = 550;
	int selected = 0;
	int ease_flag = 0;
	//int ease_pos = 0;
	double ease_time = 0.0;

	int draw(int n, char **str);
};

enum menumode {
	Title,
	CharaSelect,
	DiffiSelect,
	Option
};

int menu_mode = Title;

int title_img_1, title_img_2;
int menu_bg_1, menu_bg_2;

int title_selected;

int title_alpha = 0;
int title_dir = 2;

int const num = 2;  // 必要なキーデータ分
int ctrl_trig[num];
int menu_sehnd[3];

coolmenu title;
coolmenu chara;

char *title_str[5] = { "GAME START", "STAGE SELECT", "STAGE CREATE", "OPTION", "QUIT GAME"};
char *charSelect_str[3] = { "FLORENCE", "AMERIA", "BACK TO TITLE" };

void draw_Title();
void draw_CharSelect();
void ctrl_trigg();
double OutQuint(double t, double totaltime, double max, double min);

