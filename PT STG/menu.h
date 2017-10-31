

class coolmenu {
public:
	int y = 280;
	int x = 550;
	int selected = 0;
	int ease_flag = 0;
	//int ease_pos = 0;
	double ease_time = 0.0;

	int draw(int mx, int my, int n, char **str);
};

enum menumode {
	Title,
	CharaSelect,
	DiffiSelect,
	Option
};

int menu_mode = Title;

int title_alpha = 0;
int title_dir = 2;

int rad = 0;

int const num = 2;  // 必要なキーデータ分
int ctrl_trig[num];

coolmenu title;
coolmenu chara;

char *title_str[5] = { "GAME START", "STAGE SELECT", "STAGE CREATE", "OPTION", "QUIT GAME"};
char *charSelect_str[3] = { "FLORENCE", "CHARLOTTE", "BACK TO TITLE" };
char *charSelect_fstr[3] = { "FLORA FLORENCE", "AMERIA CHARLOTTE", "" };
char *charSelect_mes[3] = { "SHE ENJOYS SOAKING HERSELF IN A HOT BATH.\nUNIQUE SHOT = DOUBLE LASER, UPPER SHOT\nBOMB = STRAIGHT", "FLORENCE'S STEPSISTER. SO CUTE.\nUNIQUE SHOT = RING LASER, UNDER SHOT\n BOMB = WIDE", "" };

void draw_Title();
void draw_CharSelect();
void ctrl_trigg();
double OutQuint(double t, double totaltime, double max, double min);

