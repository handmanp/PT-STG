
#include <cmath>

// ===================================================
// 矩形同士の当たり判定
// ---------------------------------------------------
// x, y : 中心座標x, y 
// xr   : 横軸の直径
// yr   : 縦軸の直径
// ---------------------------------------------------
// 戻り値 : true = 衝突 / false = 衝突してない
// ===================================================
bool IsDetection_Square(int x1, int y1, int x2, int y2, int xr1, int yr1, int xr2, int yr2) {
	if (abs(x1 - x2) < (xr1 - xr2) / 2 && abs(y1 - y2) < (yr1 - yr2) / 2) {
		return true;
	}
	return false;
}

// ===================================================
// 矩形と点の当たり判定
// ---------------------------------------------------
// sx, sy : 矩形中心座標x, y 
// w, h   : 矩形の幅と高さ
// x, y   : 点の座標
// ---------------------------------------------------
// 戻り値 : true = 衝突 / false = 衝突してない
// ===================================================
bool IsDetection_PointAndSquare(int sx, int sy, int w, int h, int x, int y) {
	if ((x > sx - (w / 2) && x < sx + (w / 2)) && (y > sy - (h / 2) && y < sy + (h / 2))) {
		return true;
	}
	return false;
}