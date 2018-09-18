#include <iostream>
#include <cmath>
using namespace std;
int main() {
	//freopen("data.in", "r", stdin);
	int n, m, i, j, k, l, r, s1, s2, t1, t2, x, y;
	int a[102][102];
	int qx[50001], qy[50001], change[50001], face[50001];
	bool used[4][102][102];
	cin >> n >> m;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			cin >> a[i][j];
	for (i = 0; i <= n + 1; i++) a[i][0] = a[i][m + 1] = 0;
	for (i = 0; i <= m + 1; i++) a[0][i] = a[n + 1][i] = 0;
	for (i = 0; i <= n + 1; i++)
		for (j = 0; j <= m + 1; j++)
			for (k = 0; k<4; k++)
				used[k][i][j] = false;
	cin >> s1 >> s2 >> t1 >> t2;
	if (a[s1][s2] != a[t1][t2]) {
		cout << "No!" << endl;
		return 0;
	}
	r = 0; l = -1;
	qx[0] = s1; qy[0] = s2;
	used[0][s1][s2] = used[1][s1][s2] = used[2][s1][s2] = used[3][s1][s2] = true;
	change[0] = 0;
	while (l<r) {
		x = qx[++l]; y = qy[l];
		if (abs(x - t1) + abs(y - t2) <= 1) {
			if (change[l]<2) {
				cout << "Yes!" << endl;
				cin >> x;
				return 0;
			}
			else {
				if (face[l] == 0 && x + 1 == t1 || face[l] == 1 && x - 1 == t1 || face[l] == 2 && y + 1 == t2 || face[l] == 3 && y - 1 == t2) {
					cout << "Yes!" << endl;
					cin >> x;
					return 0;
				}
			}
		}
		if (x + 1 <= n + 1 && a[x + 1][y] == 0 && !used[0][x + 1][y]) {
			if (l == 0 || l != 0 && face[l] != 0 && change[l]<2 || l != 0 && face[l] == 0) {
				r++;
				qx[r] = x + 1; qy[r] = y;
				face[r] = 0;
				if (l == 0) change[r] = 0;
				else if (face[l] != 0) change[r] = change[l] + 1;
				else change[r] = change[l];
				used[0][x + 1][y] = true;
			}
		}
		if (x - 1 >= 0 && a[x - 1][y] == 0 && !used[1][x - 1][y]) {
			if (l == 0 || l != 0 && face[l] != 1 && change[l]<2 || l != 0 && face[l] == 1) {
				r++;
				qx[r] = x - 1; qy[r] = y;
				face[r] = 1;
				used[1][x - 1][y] = true;
				if (l == 0) change[r] = 0;
				else if (face[l] != 1) change[r] = change[l] + 1;
				else change[r] = change[l];
			}
		}
		if (y + 1 <= m + 1 && a[x][y + 1] == 0 && !used[2][x][y + 1]) {
			if (l == 0 || l != 0 && face[l] != 2 && change[l]<2 || l != 0 && face[l] == 2) {
				r++;
				qx[r] = x; qy[r] = y + 1;
				face[r] = 2;
				used[2][x][y + 1] = true;
				if (l == 0) change[r] = 0;
				else if (face[l] != 2) change[r] = change[l] + 1;
				else change[r] = change[l];
			}
		}
		if (y - 1 >= 0 && a[x][y - 1] == 0 && !used[3][x][y - 1]) {
			if (l == 0 || l != 0 && face[l] != 1 && change[l]<2 || l != 0 && face[l] == 1) {
				r++;
				qx[r] = x; qy[r] = y - 1;
				face[r] = 3;
				used[3][x][y - 1] = true;
				if (l == 0) change[r] = 0;
				else if (face[l] != 3) change[r] = change[l] + 1;
				else change[r] = change[l];
			}
		}
	}
	cout << "No!" << endl;
	cin >> x;
	return 0;
}