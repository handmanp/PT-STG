
#include <cmath>

// ===================================================
// ��`���m�̓����蔻��
// ---------------------------------------------------
// x, y : ���S���Wx, y 
// xr   : �����̒��a
// yr   : �c���̒��a
// ---------------------------------------------------
// �߂�l : true = �Փ� / false = �Փ˂��ĂȂ�
// ===================================================
bool IsDetection_Square(int x1, int y1, int x2, int y2, int xr1, int yr1, int xr2, int yr2) {
	if (abs(x1 - x2) < (xr1 - xr2) / 2 && abs(y1 - y2) < (yr1 - yr2) / 2) {
		return true;
	}
	return false;
}

// ===================================================
// ��`�Ɠ_�̓����蔻��
// ---------------------------------------------------
// sx, sy : ��`���S���Wx, y 
// w, h   : ��`�̕��ƍ���
// x, y   : �_�̍��W
// ---------------------------------------------------
// �߂�l : true = �Փ� / false = �Փ˂��ĂȂ�
// ===================================================
bool IsDetection_PointAndSquare(int sx, int sy, int w, int h, int x, int y) {
	if ((x > sx - (w / 2) && x < sx + (w / 2)) && (y > sy - (h / 2) && y < sy + (h / 2))) {
		return true;
	}
	return false;
}