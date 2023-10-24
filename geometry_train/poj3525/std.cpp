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
 * ����ж�
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
//��
struct Point {
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z)
	{
	}
};
//����
typedef Point Vector;
//����
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
//����������  �������������µ�ͶӰ�������µĳ��ȳ˻���������
double Dot(Vector A, Vector B)
{
	return A.x * B.x + A.y * B.y + A.z * B.z;
}
//����������  ������������ųɵ�ƽ���ı��ε��������
double Cross(Vector A, Vector B)
{
	return A.x * B.y - A.y * B.x;
}
//ȡģ
double Length(Vector A)
{
	return sqrt(Dot(A, A));
}
//����н�
double Angle(Vector A, Vector B)
{
	return acos(Dot(A, B) / Length(A) / Length(B));
}
//������ת
Vector Rotate(Vector A, double rad) //radΪ���� ��Ϊ��ʱ����ת�Ľ�
{
	return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}
Vector Normal(Vector A) //����A��ת90��ĵ�λ������
{
	double L = Length(A);

	return Vector(-A.y / L, A.x / L);
}
//���������ԲԲ��
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
//�������
double dis(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
/*------------------------------------------------------------------------------------------------*/
//��
struct Line {//ֱ�߶���
	Point v, p;
	Line(Point v, Point p) : v(v), p(p)
	{
	}
	Point point(double t)//���ص�P = v + (p - v)*t
	{
		return v + (p - v) * t;
	}
};
//�жϵ��Ƿ�������
bool PointOnline(Line A, Point a)
{
	Vector v1(A.p.x - a.x, A.p.y - a.y, A.p.z - a.z);
	Vector v2(A.v.x - a.x, A.v.y - a.y, A.v.z - a.z);

	return !(Cross(v1, v2));
}
//������ֱ�߽��� ���뱣ֱ֤���ཻ�����򽫻���ֳ���������
Point GetLineIntersection(Point a1, Point a2, Point b1, Point b2)
{
	Vector v = a1 - a2;
	Vector w = b1 - b2;
	Vector u = a1 - b1;
	double t = Cross(w, u) / Cross(v, w);

	return a1 + v * t;
}
//��P��ֱ��AB���빫ʽ
double DistanceToLine(Point P, Point A, Point B)
{
	Vector v1 = B - A, v2 = P - A;

	return fabs(Cross(v1, v2) / Length(v1));
}
//��P���߶�AB���빫ʽ
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
//��P��ֱ��AB�ϵ�ͶӰ��
Point GetLineProjection(Point P, Point A, Point B)
{
	Vector v = B - A;

	return A + v * (Dot(v, P - A) / Dot(v, v));
}
//�жϵ��Ƿ����߶ζ���
bool OnSegment(Point p, Point a1, Point a2)
{
	return dcmp(Cross(a1 - p, a2 - p), 0) == 0 && dcmp(Dot(a1 - p, a2 - p), 0) <= 0;
}
//�ж��߶��ཻ
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
	double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
	double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);

	//if�жϿ����Ƿ������߶��ڶ˵㴦�ཻ��������Ҫ���
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
//��c�Ƿ����߶�ab����� ��1 ����0 ��-1
int ToLeftTest(Point a, Point b, Point c)
{
	if (Cross(b - a, c - b) > 0) return 1;
	else if (Cross(b - a, c - b) == 0) return 0;
	else return -1;
}
/*------------------------------------------------------------------------*/
//�����
//��͹�� �����p  ͹��ch
int ConvexHull(Point *p, int n, Point *ch)
{
	n = unique(p, p + n) - p;//ȥ��
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
//��͹���ܳ�
double CofCH(Point *ch, int m)
{
	double C = 0;

	for (int i = 0; i < m; i++)
		C += dis(ch[i], ch[(i + 1) % m]);
	return C;
}
//������������
double PolygonArea(Point *p, int n) //pΪ�˵㼯�ϣ�nΪ�˵����
{
	double s = 0;

	for (int i = 1; i < n - 1; ++i)
		s += Cross(p[i] - p[0], p[i + 1] - p[0]);
	return s;
}
//�жϵ��Ƿ��ڶ�����ڣ������ڶ�����ڷ���1���ڶ�����ⲿ����0���ڶ�����Ϸ���-1
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
//��ƽ��
struct Hplane {
	Point	p;      //ֱ����һ��
	Vector	v;      //�������� ��������ǰ�ƽ��
	double	ang;    //����
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
	}                                             //��������
};
//p�Ƿ���L���
bool OnLeft(Hplane L, Point p)
{
	return sgn(Cross(L.v, p - L.p)) > 0;
}
//��ƽ�潻��
Point Cross_point(Hplane a, Hplane b)
{
	Vector u = a.p - b.p;
	double t = Cross(b.v, u) / Cross(a.v, b.v);

	return a.p + a.v * t;
}
vector<Point>HPI(Hplane *L, int n)
{
	sort(L, L + n);
	int frist, last;        //ָ��˫�˶��е���β
	vector<Point>p(n);      //������ƽ��Ľ���
	vector<Hplane>q(n);     //˫�˶���
	vector<Point>ans;       //��ƽ�潻͹��
	q[frist = last = 0] = L[0];
	for (int i = 1; i < n; i++) {
		//ɾ��β����ƽ��
		while (frist < last && !OnLeft(L[i], p[last - 1])) last--;
		//ɾ���ײ���ƽ��
		while (frist < last && !OnLeft(L[i], p[frist])) frist++;
		q[++last] = L[i];
		//������ͬ�������
		if (fabs(Cross(q[last].v, q[last - 1].v)) < eps) {
			last--;
			if (OnLeft(q[last], L[i].p)) q[last] = L[i];
		}
		//�������β����ƽ�潻
		if (frist < last) p[last - 1] = Cross_point(q[last - 1], q[last]);
	}
	//ɾ������β�����õĶ���
	while (frist < last && !OnLeft(q[frist], p[last - 1])) last--;
	if (last - frist <= 1) return ans; //�ռ�
	p[last] = Cross_point(q[last], q[frist]);
	for (int i = frist; i <= last; i++) ans.push_back(p[i]);
	return ans;
}
/************************************************************************************/
Point p[510];
Hplane v[510], C_v[510];
void Change(double r, int n)//����������r�ľ���
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
