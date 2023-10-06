#include <ctime>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include "SimpleGraph.h"

using std::cout;        using std::endl;
using std::cin;         using std::cerr;
using std::max;         using std::min;
using std::vector;

const double PI = acos(-1);
const double eps = 1e-7;

SimpleGraph G;
int n;
int Time;
time_t st;

vector <vector<int>> Graph;
vector <int> degree;

double cross(Node x,Node y)
{
    return x.x*y.y-x.y*y.x;
}
Node operator - (Node a,Node b)
{
    return (Node){a.x-b.x,a.y-b.y};
}
int sgn(double x) // Preventing issues with the accuracy of double operations
{
    if(fabs(x)<eps) return 0;
    if(x<0) return -1;
    return 1;
}
bool is_intersect(Edge a,Edge b) // judge whether two segments intersect
{
    Node ax=G.nodes[a.start],ay=G.nodes[a.end];
    Node bx=G.nodes[b.start],by=G.nodes[b.end];
    return    max(ax.x,ay.x)>=min(bx.x,by.x) && max(bx.x,by.x)>=min(ax.x,ay.x)
           && max(ax.y,ay.y)>=min(bx.y,by.y) && max(bx.y,by.y)>=min(ax.y,ay.y)
           && sgn(cross(bx-ay,ax-ay))*sgn(cross(by-ay,ax-ay))<=0
           && sgn(cross(ax-by,bx-by))*sgn(cross(ay-by,bx-by))<=0;
}
int count_intersection(SimpleGraph A) // count the number of intersection of a grah
{
    int ans=0;
    for(auto u:A.edges)
        for(auto v:A.edges)
        {
            if(!sgn(G.nodes[u.start].x-G.nodes[v.start].x) && !sgn(G.nodes[u.start].y-G.nodes[v.start].y)) continue;
            if(!sgn(G.nodes[u.end].x-G.nodes[v.end].x) && !sgn(G.nodes[u.end].y-G.nodes[v.end].y)) continue;
            if(!sgn(G.nodes[u.start].x-G.nodes[v.end].x) && !sgn(G.nodes[u.start].y-G.nodes[v.end].y)) continue;
            if(!sgn(G.nodes[u.end].x-G.nodes[v.start].x) && !sgn(G.nodes[u.end].y-G.nodes[v.start].y)) continue;
            if(is_intersect(u,v)) ans++;
        }
    return ans/2;
}
bool evaluate_graph(SimpleGraph A,SimpleGraph B) // we define a graph better than the other when it has less intersections
{
    int intersect_of_A=count_intersection(A);
    int intersect_of_B=count_intersection(B);
    return intersect_of_A<=intersect_of_B;
}

// Input
void input()
{
	cout << "please give the number of seconds you want to consume to get the result" << endl;
//    cin>>Time;
    Time = 100000;
	st = time(NULL);
    freopen("D:\\code\\01_GraphViz\\res\\127binary-tree", "r", stdin);
	scanf("%d", &n);
	G.nodes.resize(n);
    Graph.resize(n);
    degree.resize(n);
	int x, y;
	while (scanf("%d%d", &x, &y) == 2) {
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
//	print(G);
}

void init_location_random()
{
    srand(clock());
    for(int i=0;i<n;i++)
    {
        G.nodes[i].x=1.0*(rand()%100)/101;
        G.nodes[i].y=1.0*(rand()%100)/101;
    }
}

const double Kr = 0.001;
const double Ka = 0.001;
vector <double> dx, dy;

double sqr(double _x)
{
	return _x * _x;
}

void compute_forces() // compute the forces of each node
{
	dx.resize(n); dy.resize(n);
	for (int i = 0; i < n; i++) dx[i] = dy[i] = 0; // clear before use
    for (int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            if(i==j) continue;
            double x0 = G.nodes[i].x, y0 = G.nodes[i].y;
            double x1 = G.nodes[j].x, y1 = G.nodes[j].y;
            double theta = atan2(y1 - y0, x1 - x0), dist2 = sqr(y1 - y0) + sqr(x1 - x0);
            double Fr = Kr / sqrt(dist2);
            dx[i] -= Fr * cos(theta); dy[i] -= Fr * sin(theta);
            dx[j] += Fr * cos(theta); dy[j] += Fr * sin(theta);
        }
    for (int i = 0; i < n; i++)
        for (int j:Graph[i])
        {
            double x0 = G.nodes[i].x, y0 = G.nodes[i].y;
            double x1 = G.nodes[j].x, y1 = G.nodes[j].y;
            double theta = atan2(y1 - y0, x1 - x0), dist2 = sqr(y1 - y0) + sqr(x1 - x0);
            double Fa = Ka * dist2;
            dx[i] += Fa * cos(theta); dy[i] += Fa * sin(theta);
            dx[j] -= Fa * cos(theta); dy[j] -= Fa * sin(theta);
        }
}
int root_of_tree,nowmn;
vector <int> size_of_sontree;
void dfs(int u,int fa)
{
    size_of_sontree[u]=1;
    int mxsiz=0;
    for(int to:Graph[u])
    {
        if(to==fa) continue;
        dfs(to,u);
        size_of_sontree[u]+=size_of_sontree[to];
        mxsiz=max(mxsiz,size_of_sontree[to]);
    }
    mxsiz=max(mxsiz,n-size_of_sontree[u]);
    if(mxsiz<nowmn)
    {
        nowmn=mxsiz;
        root_of_tree=u;
    }
}
void change_position()// change the position of each point according to dx,dy
{
    double mnx=1e18,mny=1e18,mxx=-1e18;
    for (int i = 0; i < n; i++)
    {
        if(i==root_of_tree) continue;
        G.nodes[i].x += dx[i], G.nodes[i].y += dy[i];
        mnx=min(mnx,G.nodes[i].x);
        mny=min(mny,G.nodes[i].y);
        mxx=max(mxx,G.nodes[i].x);
    }
    if(root_of_tree!=n+1)
        G.nodes[root_of_tree].x=0,G.nodes[root_of_tree].y=mny-1;
    return;
}

int main()
{
	Welcome();
	input();
    bool is_tree=1;
    root_of_tree=n+1;
    if(is_tree)
    {
        size_of_sontree.resize(n);
        nowmn=n+1;
        dfs(0,-1);
    }
//    cout<<root_of_tree<<" "<<nowmn<<endl;
    int T=1;
    init_location();
    G.nodes[root_of_tree].x=0;
    G.nodes[root_of_tree].y=-1;
    print(G);
//    return 0;
    while (difftime(time(NULL), st) < 50) { // check if there is time remain
        compute_forces();
        change_position();
        print(G);
    }
    print(G);
    return 0;
    cout<<count_intersection(G)<<endl;
    SimpleGraph ans=G;
    time_t lst=time(NULL);
    while(T--)
    {
        init_location_random();
        while (difftime(time(NULL), lst) < 50) { // check if there is time remain
            compute_forces();
            change_position();
        }
//        cout<<count_intersection(G)<<endl;
        if(!evaluate_graph(G,ans))
            ans.nodes=G.nodes;
        lst=time(NULL);
    }
    print(ans);
	return 0;
}
