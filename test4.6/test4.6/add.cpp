#include <bits/stdc++.h>
using namespace std;
double ax, ay, bx, by, x1, y1a, x2, y2;
bool check1(double x, double y) 
{
	return x >= x1 - 1e-6 && x <= x2 + 1e-6 && y >= y2 - 1e-6 && y <= y1a + 1e-6;
}
bool check2(double x, double y) 
{
	double minx = min(ax, bx), maxx = max(ax, bx);
	double miny = min(ay, by), maxy = max(ay, by);
	return x >= minx - 1e-6 && x <= maxx + 1e-6 && y >= miny - 1e-6 && y <= maxy + 1e-6;
}
double cm(double x, double y)
{
	return sqrt(x*x+y*y);
}
int main() 
{
	
	cin >> ax >> ay >> bx >> by >> x1 >> y1a >> x2 >> y2;
	double xm = min(x1, x2), xn = max(x1, x2);
	double ym = max(y1a, y2), yn = min(y1a, y2);
	x1 = xm; y1a = ym; x2 = xn; y2 = yn;
	if (abs(ax - bx) <= 1e-6)
	{
		if (ay > by) 
		{
			swap(ay, by);
			swap(ax, bx);
		}

		if (ax < x1 - 1e-6 || ax > x2 + 1e-6)
			printf("0\n");
		else if (ay >= y2)
		{
			if (ay >= y1a) 
				printf("0\n");
			else if (by <= y1a) 
				printf("%.10f\n", by - ay);
			else 
				printf("%.10f\n", y1a - ay);
		}
		else 
		{
			if (by <= y2) 
				printf("0\n");
			else if (by <= y1a) 
				printf("%.10f\n", by - y2);
			else 
				printf("%.10f\n", y1a - y2);
		}
	}
	else if (abs(ay - by) <= 1e-6) 
	{
		if (ax > bx) 
		{
			swap(ay, by);
			swap(ax, bx);
		}
		if (ay < y2 - 1e-6 || ay > y1a + 1e-6) 
			printf("0\n");
		else if (ax >= x1) 
		{
			if (ax >= x2) 
				printf("0\n");
			else if (bx <= x2) 
				printf("%.10f\n", bx - ax);
			else 
				printf("%.10f\n", x2 - ax);
		}
		else 
		{
			if (bx <= x1)
				printf("0\n");
			else if (bx <= x2) 
				printf("%.10f\n", bx - x1);
			else 
				printf("%.10f\n", x2 - x1);
		}
	}
	else
	{
		double k1 = (ay - by) / (ax - bx);
		double k2 = (ax - bx) / (ay - by);
		double xa = x2, ya = k1 * (x2 - ax) + ay;
		double xb = x1, yb = k1 * (x1 - ax) + ay;
		double yc = y1a, xc = k2 * (yc - ay) + ax;
		double yd = y2, xd = k2 * (yd - ay) + ax;
		int cnt = 0;
		double xx1 = 0, yy1a = 0, xx2 = 0, yy2 = 0;
		if (check1(xa, ya) && check2(xa, ya)) 
		{
			if (cnt == 0) 
			{
				xx1 = xa; yy1a = ya;
				cnt++;
			}
			else if (cnt == 1)
			{
				if (!(abs(xa - xx1) < 1e-6 && abs(ya - yy1a) < 1e-6)) 
				{
					xx2 = xa; yy2 = ya;
					cnt++;
				}
			}
		}
		if (check1(xb, yb) && check2(xb, yb)) 
		{
			if (cnt == 0) 
			{
				xx1 = xb; yy1a = yb;
				cnt++;
			}
			else if (cnt == 1) 
			{
				if (!(abs(xb - xx1) < 1e-6 && abs(yb - yy1a) < 1e-6)) 
				{
					xx2 = xb; yy2 = yb;
					cnt++;
				}
			}
		}
		if (check1(xc, yc) && check2(xc, yc)) 
		{
			if (cnt == 0) 
			{
				xx1 = xc; yy1a = yc;
				cnt++;
			}
			else if (cnt == 1) 
			{
				if (!(abs(xc - xx1) < 1e-6 && abs(yc - yy1a) < 1e-6))
				{
					xx2 = xc; yy2 = yc;
					cnt++;
				}
			}
		}
		if (check1(xd, yd) && check2(xd, yd))
		{
			if (cnt == 0) 
			{
				xx1 = xd; yy1a = yd;
				cnt++;
			}
			else if (cnt == 1) 
			{
				if (!(abs(xd - xx1) < 1e-6 && abs(yd - yy1a) < 1e-6)) 
				{
					xx2 = xd; yy2 = yd;
					cnt++;
				}
			}
		}
		if (cnt == 0)
		{
			if (check1(ax, ay)) printf("%.10f\n", cm(ax - bx, ay - by));
			else printf("0\n");
		}
		else if (cnt == 1) 
		{
			if (check1(ax, ay)) printf("%.10f\n", cm(ax - xx1, ay - yy1a));
			else if (check1(bx, by)) printf("%.10f\n", cm(bx - xx1, by - yy1a));
			else printf("0\n");
		}
		else
		{
			printf("%.10f\n", cm(xx1 - xx2, yy1a - yy2));
		}
	}
	return 0;
}
