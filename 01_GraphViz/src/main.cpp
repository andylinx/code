//author : andyc_03 李南锡 523031910551
//acknowledgements : thank Wu Yuxiang for his support in the tech of input

#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include "SimpleGraph.h"

using std::cout;        using std::endl;
using std::cin;         using std::cerr;
using std::max;         using std::min;
using std::vector;      using std::string;
using std::pair;

const double PI = acos(-1);
const double eps = 1e-7;

SimpleGraph G;
int n, m;       // represent number of nodes and edges
int Time;       // user can define the running time of the program
time_t st;

vector <vector<int> > Graph;    // used to store edges of the graph to iterate the graph more easily
vector <int> degree;            // represent the number of edges connected to point i

double cross(Node x, Node y)
{
	return x.x * y.y - x.y * y.x;
}
Node operator -(Node a, Node b)
{
	return (Node){ a.x - b.x, a.y - b.y };
}
int sgn(double x) // Preventing issues with the accuracy of double operations
{
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	return 1;
}
bool is_intersect(Edge a, Edge b) // judge whether two segments intersect
{
	Node ax = G.nodes[a.start], ay = G.nodes[a.end];
	Node bx = G.nodes[b.start], by = G.nodes[b.end];

	return max(ax.x, ay.x) >= min(bx.x, by.x) && max(bx.x, by.x) >= min(ax.x, ay.x)
	       && max(ax.y, ay.y) >= min(bx.y, by.y) && max(bx.y, by.y) >= min(ax.y, ay.y)
	       && sgn(cross(bx - ay, ax - ay)) * sgn(cross(by - ay, ax - ay)) <= 0
	       && sgn(cross(ax - by, bx - by)) * sgn(cross(ay - by, bx - by)) <= 0;
}
int count_intersection(SimpleGraph A) // count the number of intersection of a grah
{
	int ans = 0;

	for (auto u:A.edges)
		for (auto v:A.edges) {
			if (!sgn(G.nodes[u.start].x - G.nodes[v.start].x) && !sgn(G.nodes[u.start].y - G.nodes[v.start].y)) continue;
			if (!sgn(G.nodes[u.end].x - G.nodes[v.end].x) && !sgn(G.nodes[u.end].y - G.nodes[v.end].y)) continue;
			if (!sgn(G.nodes[u.start].x - G.nodes[v.end].x) && !sgn(G.nodes[u.start].y - G.nodes[v.end].y)) continue;
			if (!sgn(G.nodes[u.end].x - G.nodes[v.start].x) && !sgn(G.nodes[u.end].y - G.nodes[v.start].y)) continue;
			if (is_intersect(u, v)) ans++;
		}
	return ans / 2;
}
bool evaluate_graph(SimpleGraph A, SimpleGraph B) // we define a graph better than the other when it has less intersections
{
	int intersect_of_A = count_intersection(A);
	int intersect_of_B = count_intersection(B);

	return intersect_of_A <= intersect_of_B;
}

// transfer a string to an integer
int get_a_number(string ss)
{
	int len = ss.length();
	int res = 0, f = 1;

	for (int i = 0; i < len; i++) {
		if (ss[i] != '-' && (ss[i] < '0' || ss[i] > '9')) continue;
		if (ss[i] == '-') f = -1;
		else res = res * 10 + ss[i] - '0';
	}
	return res * f;
}

// transfer a string to two integers
pair <int, int> get_two_number(string ss)
{
	int len = ss.length();
	int resa = 0, resb = 0, tag = 0;

	for (int i = 0; i < len; i++) {
		if (ss[i] != '-' && (ss[i] < '0' || ss[i] > '9')) {
			if (resa) tag = 1;
			continue;
		} else {
			if (!tag)
				resa = resa * 10 + ss[i] - '0';
			else resb = resb * 10 + ss[i] - '0';
		}
	}
	return { resa, resb };
}
// a flag to be determined by user,representing whether the graph should be treated as a tree
bool is_tree = 0;

// deal with the given input,use getline to avoid the dangerous opeartions like cin
void input()
{
	st = time(NULL);
	string ss;
	cout << "please give the number of seconds you want to consume to get the result" << endl;
	getline(cin, ss);
	Time = get_a_number(ss);
	cout << "please tell me whether if the graph is a tree (if so you would get a graph with the root at the top of the graph)" << endl;
	cout << "input 1 for tree, else input a 0" << endl;
	cin >> ss;
	if (get_a_number(ss)) is_tree = 1;
	cout << "please give the name of input file!" << endl;
	cin >> ss;
	std::ifstream File(ss);
	getline(File, ss);
	n = get_a_number(ss);
	G.nodes.resize(n);
	Graph.resize(n);
	degree.resize(n);
	int x, y;
	while (getline(File, ss)) {
		pair<int, int> res = get_two_number(ss);
		x = res.first; y = res.second;
		m++;
		Edge temp;
		temp.start = (size_t)x; temp.end = (size_t)y;
		G.edges.push_back(temp);
		Graph[x].push_back(y);
		Graph[y].push_back(x);
		degree[x]++; degree[y]++;
	}
}

// visualize graph
void print(SimpleGraph A)
{
	InitGraphVisualizer(A);
	DrawGraph(A);
//    _sleep(20); // pause for a while to give a better visual effect
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome()
{
	cout << "Welcome to CS106L GraphViz!" << endl;
	cout << "This program uses a force-directed graph layout algorithm" << endl;
	cout << "to render sleek, snazzy pictures of various graphs." << endl;
	cout << endl;
}

void init_location() //give every node an initial position by placing them on a circle

{
	for (int i = 0; i < n; i++) {
		G.nodes[i].x = cos(2.0 * PI * i / n);
		G.nodes[i].y = sin(2.0 * PI * i / n);
	}
//    print(G);
}

void init_location_random()
{
	srand(clock());
	vector <int> p;
	p.resize(n);
	for (int i = 0; i < n; i++) p[i] = i;
	std::random_shuffle(p.begin(), p.end());
	for (int i = 0; i < n; i++) {
		G.nodes[p[i]].x = cos(2.0 * PI * i / n);
		G.nodes[p[i]].y = sin(2.0 * PI * i / n);
	}
}

//two parameters that determines the amount of forces
const double Kr = 0.001;
const double Ka = 0.001;
const double Kd = 0.02;
vector <double> dx, dy; // represent the amount of movment of each point in x,y axis

double sqr(double _x)
{
	return _x * _x;
}

void compute_forces() // compute the forces of each node
{
	dx.resize(n); dy.resize(n);
    for (int i = 0; i < n; i++) dx[i] *=Kd, dy[i] *= Kd; // keep some of the delta by the last operation as inertia
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			double x0 = G.nodes[i].x, y0 = G.nodes[i].y;
			double x1 = G.nodes[j].x, y1 = G.nodes[j].y;
			double theta = atan2(y1 - y0, x1 - x0), dist2 = sqr(y1 - y0) + sqr(x1 - x0);
			double Fr = Kr / sqrt(dist2);
			dx[i] -= Fr * cos(theta); dy[i] -= Fr * sin(theta);
			dx[j] += Fr * cos(theta); dy[j] += Fr * sin(theta);
		}
	for (int i = 0; i < n; i++)
		for (int j:Graph[i]) {
			double x0 = G.nodes[i].x, y0 = G.nodes[i].y;
			double x1 = G.nodes[j].x, y1 = G.nodes[j].y;
			double theta = atan2(y1 - y0, x1 - x0), dist2 = sqr(y1 - y0) + sqr(x1 - x0);
			double Fa = Ka * dist2;
			dx[i] += Fa * cos(theta); dy[i] += Fa * sin(theta);
			dx[j] -= Fa * cos(theta); dy[j] -= Fa * sin(theta);
		}
	// we also add repulsion between edges so that we can have a better visual effect

	for (int i = 0; i < m; i++)
		for (int j = i + 1; j < m; j++) {
			Edge ei = G.edges[i], ej = G.edges[j];
			double x0 = (G.nodes[ei.start].x + G.nodes[ei.end].x) / 2, y0 = (G.nodes[ei.start].y + G.nodes[ei.end].y) / 2;
			double x1 = (G.nodes[ej.start].x + G.nodes[ej.end].x) / 2, y1 = (G.nodes[ej.start].y + G.nodes[ej.end].y) / 2;
			double theta = atan2(y1 - y0, x1 - x0), dist2 = sqr(y1 - y0) + sqr(x1 - x0);
			double Fr = 0.02 * Kr / sqrt(dist2);
			//dx[i] -= Fr * cos(theta); dy[i] -= Fr * sin(theta);
			//dx[j] += Fr * cos(theta); dy[j] += Fr * sin(theta);
		}
}
// compute some val and find the best root of the tree
int root_of_tree, nowmn;
vector <int> size_of_sontree;
void dfs(int u, int fa)
{
	size_of_sontree[u] = 1;
	int mxsiz = 0;
	for (int to:Graph[u]) {
		if (to == fa) continue;
		dfs(to, u);
		size_of_sontree[u] += size_of_sontree[to];
		mxsiz = max(mxsiz, size_of_sontree[to]);
	}
	mxsiz = max(mxsiz, n - size_of_sontree[u]);
	if (mxsiz < nowmn) {
		nowmn = mxsiz;
		root_of_tree = u;
	}
}
void change_position()// change the position of each point according to dx,dy
{
	double mnx = 1e18, mny = 1e18, mxx = -1e18;

	for (int i = 0; i < n; i++) {
		if (is_tree && i == root_of_tree) continue;
		G.nodes[i].x += dx[i], G.nodes[i].y += dy[i];
		mnx = min(mnx, G.nodes[i].x);
		mny = min(mny, G.nodes[i].y);
		mxx = max(mxx, G.nodes[i].x);
	}
	if (is_tree)
		G.nodes[root_of_tree].x = 0, G.nodes[root_of_tree].y = mny - 1;
	return;
}
void solve_as_tree() // treat the graph as a tree
{
	root_of_tree = n + 1;
	size_of_sontree.resize(n);
	nowmn = n + 1;
	dfs(0, -1);
	init_location();
	G.nodes[root_of_tree].x = 0;
	G.nodes[root_of_tree].y = -1;
	print(G);
	while (difftime(time(NULL), st) < 1.0 * Time) { // check if there is time remain
		compute_forces();
		change_position();
		print(G);
	}
	print(G);
	cout << "The final graph was printed on the screen! \n Attention:the effect may get better if you give it more time to run~" << endl;
	return;
}
int main()
{
	Welcome();
	input();
	if (is_tree) {
		solve_as_tree();
		return 0;
	}
	time_t lst = time(NULL);
	init_location();
	while (difftime(time(NULL), lst) < 1.0 * Time) { // check if there is time remain
		compute_forces();
		change_position();
		print(G);
	}
	SimpleGraph ans;
	ans.edges = G.edges;
	ans.nodes = G.nodes;
	int T = 3;
	while (T--) {
		init_location_random();
		while (difftime(time(NULL), lst) < 1.0 * Time / 3) { // check if there is time remain
			compute_forces();
			change_position();
			print(G);
		}
		if (!evaluate_graph(G, ans))
			ans.nodes = G.nodes;
		lst = time(NULL);
		print(G);
	}
	cout << "The final graph was printed on the screen! \nAttention:the effect may get better if you give it more time to run~" << endl;
	print(ans);
	return 0;
}

/*
 *  some optimizations were added:
 *      1.treat tree specially : pick the root of the tree at top of the graph
 *      2.random 3 times and compare the graph by counting the intersects of the segments
 *      3.add replusive forces between two edges (which turns out to be not so effective)
 *      4.add inertia for fear that nodes move back and force
 *
 *  observations:
 *      1.some graphs like binary-tree need longer time to complete
 *      2.some graphs like wheel may get over-calculated which leads to its being not balanced.
 */
