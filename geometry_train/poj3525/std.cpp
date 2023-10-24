//#include<bits/stdc++.h>
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const double pi = acos(-1.0);
const double inf = 1e100;
/*
 * 误差判断
 */
const double eps = 1e-7;
int dcmp(double x, double y)
{
	if (fabs(x - y) < eps)
		return 0;
	if (x > y)
		return 1;
	return -1;
}
int sgn(double d)
{
	if (fabs(d) < eps)
		return 0;
	if (d > 0)
		return 1;
	return -1;
}
/*---------------------------------------------------------------------------------------*/
//点
struct Point {
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z)
	{
	}
};
//向量
typedef Point Vector;
//运算
Vector operator +(Vector A, Vector B)
{
	return Vector(A.x + B.x, A.y + B.y, A.z + B.z);
}
Vector operator -(Vector A, Vector B)
{
	return Vector(A.x - B.x, A.y - B.y, A.z - B.z);
}
Vector operator *(Vector A, double p)
{
	return Vector(A.x * p, A.y * p, A.z * p);
}
Vector operator /(Vector A, double p)
{
	return Vector(A.x / p, A.y / p, A.z / p);
}
bool operator ==(Point A, Point B)
{
	return sgn(A.x - B.x) == 0 && sgn(A.y - B.y) == 0;
}
bool P_cmp1(Point a, Point b)
{
	if (a.x == b.x)
		return a.y < b.y;
	return a.x < b.x;
}
//向量数量积  向量α在向量β的投影于向量β的长度乘积（带方向）
double Dot(Vector A, Vector B)
{
	return A.x * B.x + A.y * B.y + A.z * B.z;
}
//向量向量积  向量α与β所张成的平行四边形的有向面积
double Cross(Vector A, Vector B)
{
	return A.x * B.y - A.y * B.x;
}
//取模
double Length(Vector A)
{
	return sqrt(Dot(A, A));
}
//计算夹角
double Angle(Vector A, Vector B)
{
	return acos(Dot(A, B) / Length(A) / Length(B));
}
//向量旋转
Vector Rotate(Vector A, double rad) //rad为弧度 且为逆时针旋转的角
{
	return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
Vector Normal(Vector A) //向量A左转90°的单位法向量
{
	double L = Length(A);

	return Vector(-A.y / L, A.x / L);
}
//三角形外接圆圆心
Point Excenter(Point a, Point b, Point c)
{
	double a1 = b.x - a.x;
	double b1 = b.y - a.y;
	double c1 = (a1 * a1 + b1 * b1) / 2;
	double a2 = c.x - a.x;
	double b2 = c.y - a.y;
	double c2 = (a2 * a2 + b2 * b2) / 2;
	double d = a1 * b2 - a2 * b1;

	return Point(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
}
//两点距离
double dis(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
/*------------------------------------------------------------------------------------------------*/
//线
struct Line {//直线定义
	Point v, p;
	Line(Point v, Point p) : v(v), p(p)
	{
	}
	Point point(double t)//返回点P = v + (p - v)*t
	{
		return v + (p - v) * t;
	}
};
//判断点是否在线上
bool PointOnline(Line A, Point a)
{
	Vector v1(A.p.x - a.x, A.p.y - a.y, A.p.z - a.z);
	Vector v2(A.v.x - a.x, A.v.y - a.y, A.v.z - a.z);

	return !(Cross(v1, v2));
}
//计算两直线交点 必须保证直线相交，否则将会出现除以零的情况
Point GetLineIntersection(Point a1, Point a2, Point b1, Point b2)
{
	Vector v = a1 - a2;
	Vector w = b1 - b2;
	Vector u = a1 - b1;
	double t = Cross(w, u) / Cross(v, w);

	return a1 + v * t;
}
//点P到直线AB距离公式
double DistanceToLine(Point P, Point A, Point B)
{
	Vector v1 = B - A, v2 = P - A;

	return fabs(Cross(v1, v2) / Length(v1));
}
//点P到线段AB距离公式
double DistanceToSegment(Point P, Point A, Point B)
{
	if (A.x == B.x && A.y == B.y && A.z == B.z)
		return Length(P - A);
	Vector v1 = B - A, v2 = P - A, v3 = P - B;
	if (dcmp(Dot(v1, v2), 0) < 0)
		return Length(v2);
	if (dcmp(Dot(v1, v3), 0) > 0)
		return Length(v3);
	return DistanceToLine(P, A, B);
}
//点P在直线AB上的投影点
Point GetLineProjection(Point P, Point A, Point B)
{
	Vector v = B - A;

	return A + v * (Dot(v, P - A) / Dot(v, v));
}
//判断点是否在线段端上
bool OnSegment(Point p, Point a1, Point a2)
{
	return dcmp(Cross(a1 - p, a2 - p), 0) == 0 && dcmp(Dot(a1 - p, a2 - p), 0) <= 0;
}
//判断线段相交
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
	double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
	double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);

	//if判断控制是否允许线段在端点处相交，根据需要添加
	if (!sgn(c1) || !sgn(c2) || !sgn(c3) || !sgn(c4)) {
		bool f1 = OnSegment(b1, a1, a2);
		bool f2 = OnSegment(b2, a1, a2);
		bool f3 = OnSegment(a1, b1, b2);
		bool f4 = OnSegment(a2, b1, b2);
		bool f = (f1 | f2 | f3 | f4);
		return f;
	}
	return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}
//点c是否在线段ab的左侧 左1 线上0 右-1
int ToLeftTest(Point a, Point b, Point c)
{
	if (Cross(b - a, c - b) > 0) return 1;
	else if (Cross(b - a, c - b) == 0) return 0;
	else return -1;
}
/*------------------------------------------------------------------------*/
//多边形
//求凸包 多边形p  凸包ch
int ConvexHull(Point *p, int n, Point *ch)
{
	n = unique(p, p + n) - p;//去重
	sort(p, p + n, P_cmp1);
	int v = 0;
	for (int i = 0; i < n; i++) {
		while (v > 1 && Cross(ch[v - 1] - ch[v - 2], p[i] - ch[v - 1]) < 0)
			v--;
		ch[v++] = p[i];
	}
	int j = v;
	for (int i = n - 2; i >= 0; i--) {
		while (v > j && Cross(ch[v - 1] - ch[v - 2], p[i] - ch[v - 1]) < 0)
			v--;
		ch[v++] = p[i];
	}
	if (n > 1) v--;
	return v;
}
//求凸包周长
double CofCH(Point *ch, int m)
{
	double C = 0;

	for (int i = 0; i < m; i++)
		C += dis(ch[i], ch[(i + 1) % m]);
	return C;
}
//多边形有向面积
double PolygonArea(Point *p, int n) //p为端点集合，n为端点个数
{
	double s = 0;

	for (int i = 1; i < n - 1; ++i)
		s += Cross(p[i] - p[0], p[i + 1] - p[0]);
	return s;
}
//判断点是否在多边形内，若点在多边形内返回1，在多边形外部返回0，在多边形上返回-1
int isPointInPolygon(Point p, vector<Point> poly)
{
	int wn = 0;
	int n = poly.size();

	for (int i = 0; i < n; ++i) {
		if (OnSegment(p, poly[i], poly[(i + 1) % n])) return -1;
		int k = sgn(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
		int d1 = sgn(poly[i].y - p.y);
		int d2 = sgn(poly[(i + 1) % n].y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0) wn++;
		if (k < 0 && d2 <= 0 && d1 > 0) wn--;
	}
	if (wn != 0)
		return 1;
	return 0;
}
/*-----------------------------------------------------------------------------------*/
//半平面
struct Hplane {
	Point	p;      //直线上一点
	Vector	v;      //方向向量 他的左边是半平面
	double	ang;    //极角
	Hplane()
	{
	};
	Hplane(Point p, Vector v) : p(p), v(v)
	{
		ang = atan2(v.y, v.x);
	}
	bool operator <(Hplane &L)
	{
		return ang < L.ang;
	}                                             //用于排序
};
//p是否在L左边
bool OnLeft(Hplane L, Point p)
{
	return sgn(Cross(L.v, p - L.p)) > 0;
}
//半平面交点
Point Cross_point(Hplane a, Hplane b)
{
	Vector u = a.p - b.p;
	double t = Cross(b.v, u) / Cross(a.v, b.v);

	return a.p + a.v * t;
}
vector<Point>HPI(Hplane *L, int n)
{
	sort(L, L + n);
	int frist, last;        //指向双端队列的首尾
	vector<Point>p(n);      //两个半平面的交点
	vector<Hplane>q(n);     //双端队列
	vector<Point>ans;       //半平面交凸包
	q[frist = last = 0] = L[0];
	for (int i = 1; i < n; i++) {
		//删除尾部半平面
		while (frist < last && !OnLeft(L[i], p[last - 1])) last--;
		//删除首部半平面
		while (frist < last && !OnLeft(L[i], p[frist])) frist++;
		q[++last] = L[i];
		//极角相同保留左边
		if (fabs(Cross(q[last].v, q[last - 1].v)) < eps) {
			last--;
			if (OnLeft(q[last], L[i].p)) q[last] = L[i];
		}
		//计算队列尾部半平面交
		if (frist < last) p[last - 1] = Cross_point(q[last - 1], q[last]);
	}
	//删除队列尾部无用的队列
	while (frist < last && !OnLeft(q[frist], p[last - 1])) last--;
	if (last - frist <= 1) return ans; //空集
	p[last] = Cross_point(q[last], q[frist]);
	for (int i = frist; i <= last; i++) ans.push_back(p[i]);
	return ans;
}
/************************************************************************************/
Point p[510];
Hplane v[510], C_v[510];
void Change(double r, int n)//将边往里推r的距离
{
	for (int i = 0; i < n; i++) {
		C_v[i] = v[i];
		C_v[i].p = v[i].p + Normal(v[i].v) * r;
	}
}
void isok(int n)
{
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
	for (int i = 0; i < n; i++)
		v[i] = Hplane(p[i], p[(i + 1) % n] - p[i]);
	double l = 0.0, r = 20000.0;
	while (l + eps < r) {
		double mid = (l + r) / 2;
		Change(mid, n);
		int m = HPI(C_v, n).size();
		if (!m)
			r = mid;
		else
			l = mid;
	}
	printf("%.6lf\n", l);
}
int main()
{
	int n;

	while (1) {
		cin >> n;
		if (n == 0)
			return 0;
		isok(n);
	}
}
