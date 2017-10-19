
#define EDITOR_TOP  0
#define EDITOR_EDIT 1

//プロトタイプ宣言
int draw_EditorMainMenu();
int draw_NewProjectMenu();

void init_EditorStage();
void delete_EditorStage();

int  draw_StageEditor();
void draw_StageEditorMenu();
void draw_StageEditorRuler();
void move_StageEditor();

//Editor Global
int ss_x[4], ss_y[4];
int stage_size_x = 0 , stage_size_y =  0;
int stage_left_x = 20, stage_left_y = 20;

int mouse_diff_x = 0, mouse_diff_y = 0;

int ***stage_editor;

int editor_mode = 0;