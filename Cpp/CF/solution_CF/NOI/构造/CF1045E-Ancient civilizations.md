# Ancient civilizations

## 题目描述

在一颗新发现的星球表面（我们将其视为一个平面），探险者在不同的位置发现了两个不同文明的遗迹。他们希望进一步了解这些文明，并需要在部分遗址之间修建道路以便探索。但如往常一样，有一些限制：

1. 同一文明的任意两个遗址之间必须通过唯一的一条道路路径连通。
2. 不同文明的任意两个遗址之间不能有道路相连（探险者不希望在探索过程中混淆不同文明）。
3. 道路必须是直线线段。
4. 由于交叉点的建设成本很高，任何两条道路都不能相交（即，任意两条道路的唯一公共点只能是某个遗址的位置）。

显然，所有遗址的位置在平面上都是不同的点。探险者还发现了一个有趣的信息，或许对你有帮助——没有三个遗址共线！

请帮助探险者为他们的问题找到一个解决方案，或者报告无法实现。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
0 0 1
1 0 0
0 1 0
1 1 1
3 2 0
```

### 输出

```
3
1 4
4 2
3 0
```

# 题解

## 作者：zhengrunzhe (赞：3)

感谢冬令营时钟子谦julao的讲解

简化题意：

在平面上有n个点，有的是白点，有的是黑点（给定坐标和颜色）。保证没有三点共线。
你需要把白点连成一颗生成树，黑点连成一颗生成树。生成树的树边即为平面上连接这两点的直线段。你需要保证任两条不共端点的边不相交（白树的边也不能和黑树的边相交）。如果无解输出Impossible。
1<=n<=1000

首先考虑做整张图的凸包

如果凸包上的点存在黑白相间的情况，那就无解

如果凸包上的点全是同种颜色：

如果内部的颜色也一样，就直接跑出个生成树就好了

如果内部存在异色点，那么就让凸包上的所有相邻点对与任意一个异色点形成个三角形

对于每个三角形，有两个颜色相同的顶点和一个异色顶点，查询其内部所有的点，如果不存在异色点（与异色顶点颜色相同的点），那么就连接两同色顶点与内部所有点（也可能里面没有点）的任意一个生成树；否则取任意一个异色点，如下图，再往三个顶点形成三角形递归下去，最终总能化成无异色点的情况

![luogu](https://cdn.luogu.com.cn/upload/pic/51786.png)

如果凸包上的点颜色并不相同，如果有解，那必是凸包只分成两段，一段黑一段白，那么同样地把相邻黑点往第一个白点形成三角形，相邻白点往第一个黑点形成三角形，同理递归下去即可

![luogu](https://cdn.luogu.com.cn/upload/pic/51787.png)

假设凸包上有m个点，那么初始就会有m-2(凸包不同色)或m个三角形(凸包同色)，每次剖分会多出两个三角形，所以最终会有2(n-m)+m=2n-m或2(n-m)+m-2=2n-m-2个三角形，而m<=n，所以三角形数是O(n)级别的，每次找三角形内部的点的朴素复杂度是O(n)的，共O(n^2)，连生成树每次是O(三角形点数^2)，但总共有n个点，所以总共是差不多O(n^2)的，所以总复杂度大概O(n^2) n<=1000，能过

```cpp
#include<cmath>
#include<cctype>
#include<cstdio>
#include<vector>
#include<algorithm>
using std::pair;
using std::sort;
using std::swap;
using std::make_pair;
typedef double dbl;
const int N=1e3+10;
int n,top,ans[N][2],cnt;
bool incv[N];
struct point
{
	int x,y,org;//org表示读入点的原编号(1开始)
	bool color;
	inline point(int a=0,int b=0){x=a;y=b;}
	inline const bool operator==(const point &p)const
	{
		return color==p.color;
	}
	inline const friend dbl distance(const point &p1,const point &p2)
	{
		return sqrt(pow(1.0*(p1.x-p2.x),2.0)+pow(1.0*(p1.y-p2.y),2.0));
	}
}p[N],s[N],ss[N];
typedef pair<point,point>ppp;
typedef std::vector<point>vpt;
struct vector
{
	int x,y;
	inline vector(const point &a,const point &b)
	{
		x=b.x-a.x;
		y=b.y-a.y;
	}
	inline const dbl length()
	{
		return distance(point(0,0),point(x,y));
	}
	inline const friend int cross_product(const vector &v1,const vector &v2)
	{
		return v1.x*v2.y-v1.y*v2.x;
	}
	/*inline const friend int dot_product(const vector &v1,const vector &v2)
	{
		return v1.x*v2.x+v1.y*v2.y;
	}
	inline const friend dbl getcos(vector v1,vector v2)
	{
		return dot_product(v1,v2)/v1.length()/v2.length();
	}*/
};
struct triangle
{
	point v[3];
	inline triangle(const point &a,const point &b,const point &c)
	{
		v[0]=a;v[1]=b;v[2]=c;
	}
	inline const bool difference() //得出异色
	{
		int cnt[2];
		cnt[0]=cnt[1]=0;
		for (int i=0;i<3;i++)
			cnt[v[i].color]++;
		return cnt[0]>cnt[1];
	}
	inline const ppp same() //得出同色点
	{
		bool c=difference();
		int s[2],cnt=-1;
		for (int i=0;i<3;i++)
			if (v[i].color^c)
				s[++cnt]=i;
		return make_pair(v[s[0]],v[s[1]]);
	}
	/*inline const dbl size()
	{
		return 0.5*abs(1.0*cross_product(vector(v[0],v[1]),vector(v[0],v[2])));
	}*/
	inline const bool in(const point &p) //判断一个点是否在该三角形内部
	{
		/*dbl S=0.0,s;
		for (int i=0;i<2;i++)
			if (S+=(s=triangle(v[i],v[i+1],p).size()),!s)return false;
		S+=triangle(v[0],v[2],p).size();
		return S==size();*/
		int cp1=cross_product(vector(v[0],v[1]),vector(v[0],p)),
			cp2=cross_product(vector(v[1],v[2]),vector(v[1],p)),
			cp3=cross_product(vector(v[2],v[0]),vector(v[2],p));
		return cp1&&cp2&&cp3&&(cp1>0)==(cp2>0)&&(cp1>0)==(cp3>0);
	}
};
int fa[N];//并查集建生成树
inline const void init()
{
	for (int i=1;i<=n;i++)fa[i]=i;
}
inline const int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
inline const void Union(int x,int y)
{
	fa[find(x)]=find(y);
}
inline const bool operator<(const point &p1,const point &p2)
{
	vector v1(p[1],p1),v2(p[1],p2);
	int cp=cross_product(v1,v2);
	if (cp>0)return true;
	if (!cp&&v1.length()<v2.length())return true;
	return false;
}
inline const void convex_hull()//求凸包
{
	for (int i=1;i<=n;i++)
		if (p[i].y<p[1].y)
			swap(p[1],p[i]);
	sort(p+2,p+n+1);s[++top]=p[1];incv[p[1].org]=1;//incv是看原标号为i的点是否在凸包上
	for (int i=2;i<=n;i++)
	{
		while (top>1&&cross_product(vector(s[top-1],s[top]),vector(s[top],p[i]))<=0)incv[s[top].org]=0,top--;
		s[++top]=p[i];
		incv[p[i].org]=1;
	}
}
inline const void divide(triangle t)
{
	bool c=t.difference();
//	for (int i=0;i<3;i++)printf("%d %d\n",t.v[i].x,t.v[i].y);puts("kk");
	static vpt same,diff;same.clear();diff.clear();//same是内部同色点集，diff是内部异色点集
	for (int i=1;i<=n;i++)
		if (t.in(p[i]))
			if (p[i].color^c)same.push_back(p[i]);
			else diff.push_back(p[i]);
	ppp P=t.same(); //表示两个同色顶点
	if (diff.empty())//没有内部异色点
	{
		same.push_back(P.first);same.push_back(P.second);
	//	printf("%d %d %d %d\npp\n",P.first.x,P.first.y,P.second.x,P.second.y);
		for (int i=0;i<same.size()-1;i++)
			for (int u,v,j=i+1;j<same.size();j++)
				if (find(u=same[i].org)^find(v=same[j].org))
					ans[++cnt][0]=u-1,ans[cnt][1]=v-1,Union(u,v);
		return;
	}
/*	dbl mx=-2.0,now;point nxt; //这个是用来找分割点的，默认是最靠近同色顶点的连边，其实并不需要
	for (vpt::iterator i=diff.begin();i!=diff.end();i++)
		if (mx==-2.0)nxt=*i;
		else 
			if ((now=getcos(vector(P.first,P.second),vector(P.first,*i)))>mx)
				nxt=*i,mx=now;*/
				point nxt=diff[0]; //任选一个就行了
	for (int i=0;i<2;i++)
		divide(triangle(t.v[i],t.v[i+1],nxt));
	divide(triangle(t.v[2],t.v[0],nxt));
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].color),
		p[i].org=i;
	convex_hull();init();
	for (int i=1;i<=top;i++)ss[i]=s[i];
	int tot=std::unique(ss+1,ss+top+1)-ss-1;//把同色串缩成一个点来判断有无解
	if (tot>3||tot==3&&ss[1].color^ss[tot].color)return puts("Impossible"),0; //被缩成了三个点及以上有两种情况：被缩成三个点，首位同色，因为凸包是一个环首位相接所以并不无解，但首位异色的话就无解了；被缩成三个点以上，无解
	bool c=ss[1].color;//首的颜色
	if (tot>2)
	{
    	int fst=0,lst=0; //fst表示连续的颜色串的头,lst表示尾(因为被分成三段的这种情况首位在数组中是不连续的)
		for (int i=1;i<=top;i++)
		{
			if (s[i].color^c&&!fst)fst=i;
			if (s[i].color^c)lst=i;
		}
	/*(int i=1;i<fst-1;i++)
			divide(triangle(s[i],s[i+1],s[lst]));
		for (int i=lst+1;i<top;i++)
			divide(triangle(s[lst],s[i],s[i+1]));
		divide(triangle(s[top],s[1],s[lst]));*/
		for (int i=fst;i<lst;i++)
			divide(triangle(s[i],s[i+1],s[lst+1]));
		for (int i=lst+1;i<top;i++)
			divide(triangle(s[i],s[i+1],s[fst]));
		for (int i=1;i<fst-1;i++)
			divide(triangle(s[i],s[i+1],s[fst]));
		divide(triangle(s[top],s[1],s[fst]));
	}
	if (tot==2) //只被分成了两段，就是上面那个if的简化版
	{
		int pos;
		for (int i=1;i<=top;i++)
			if (s[i].color^c)
				{pos=i;break;}
		for (int i=pos;i<top;i++)
			divide(triangle(s[pos-1],s[i],s[i+1]));
		for (int i=1;i<pos-1;i++)
			divide(triangle(s[i],s[i+1],s[top]));
	}
	if (tot==1)//只有一段，说明凸包同色
	{
		point one;bool found=0;
		for (int i=1;i<=n;i++)
			if (!incv[p[i].org]&&p[i].color^c)
				{one=p[i];found=1;break;} //找个异色点
		if (found)
		{
			for (int i=1;i<top;i++)
				divide(triangle(s[i],s[i+1],one));
			divide(triangle(s[top],s[1],one));
		}
		else //没异色点直接出生成树
		{
			for (int i=1;i<n;i++)
				for (int j=i+1;j<=n;j++)
					if (find(i)^find(j))
						ans[++cnt][0]=i-1,ans[cnt][1]=j-1,Union(i,j);
		}
	}
	printf("%d\n",cnt);
	for (int i=1;i<=cnt;i++)
		printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

凸包与构造结合的好题。

首先建出凸包，如果凸包上黑白色的段数 $\ge 2$，那么显然不可能将黑点、白点都连成一棵生成树，直接输出 `Impossible` 即可。

那么可以证明，对于剩余情况，必然存在合法的连边方案。在探究具体如何处理剩余情况之前，我们先来讨论一些特殊情况，进而将其推广到一般情况：

- 凸包上只有三个点，并且所有点（包括凸包上的点）颜色都一样。

  这时候我们先将凸包连成一条链，随便找到中间一个点并随便将其与凸包上某个点连边，然后将整个三角形分成三个小三角形递归处理即可。容易证明其正确性。

- 凸包上只有三个点，并且恰有两个点颜色相同。

  不妨假设凸包上有两个黑点 $A,B$ 和一个白点 $C$，那么我们先在 $A,B$ 间连边，考虑凸包内部的点，如果存在至少一个白点，那么我们就取出这个白点 $D$，然后连边 $CD$，并将其余点分到 $\triangle ABD,\triangle ACD,\triangle BCD$ 中处理即可。否则我们任取一个黑点 $D$，连边 $AD$（或 $BD$），然后还是递归三个三角形即可。值得注意的是，当三角形内部既有黑点又有白点时，不能随便取一个点而必须强调“取一个**白点**”，因为如果取到的是黑点 $D$，并且三角形 $ABD$ 中有白点 $E$，那么 $C,E$ 将不能连通。

- 凸包上只有三个点。

  - 如果所有点的颜色都相同，那么按照上面第一种情况处理即可。

  - 如果凸包上恰有两个点颜色相同，那么按照上面第二种情况处理即可。

  - 否则，凸包上三个点颜色相同，但凸包内部有颜色不同于凸包上三个点的点，我们找出这样的点 $D$，假设凸包上的点为 $A,B,C$，那么我们按照“凸包上只有三个点”的情况处理三个三角形 $\triangle ABD,\triangle ACD,\triangle BCD$ 即可。

  下图是上面的算法流程的一个例子（其中实线表示连出的边，虚线表示三角剖分连出的线，粉点、绿点表示两种颜色）：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/891tk6yr.png)

  去掉虚线以后：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/pfu6uguv.png)

接下来考虑原题：

- 如果所有点颜色都一样，那么我们将其三角剖分成若干个三角形，然后对每个三角形分别进行上面的情况三即可。
- 如果凸包上所有点颜色都一样，但内部存在异色点，我们任取一异色点，将其与凸包所有顶点相连形成 $n$ 个三角形，对每个三角形分别进行上面的情况二即可。
- 否则如果凸包上恰有一个点与其他点颜色不同，那么假设这个点为白色，其他点为黑色，我们就在凸包内部找一个白点然后将这个点与凸包顶点连边形成 $n$ 个三角形分别处理，如果凸包内部没有白点就改找一个黑点即可。
- 否则，假设凸包上 $P_1\sim P_k$ 为黑色，$P_{k+1}\sim P_m$ 为白色，我们就将这个三角形剖成 $P_1P_2\cdots P_kP_{k+1}$ 和 $P_{k+1}P_{k+2}\cdots P_{m-1}P_m$ 两个多边形——显然这两个多边形上都恰有一个点与其他点颜色不同，分别处理这两个多边形即可。

时间复杂度 $n^2$。

```cpp
const int MAXN = 1000;
int n;
struct point {
	int x, y;
	point() {x = y = 0;}
	point(int _x, int _y) {x = _x; y = _y;}
	point operator + (const point &rhs) {return point(x + rhs.x, y + rhs.y);}
	point operator - (const point &rhs) {return point(x - rhs.x, y - rhs.y);}
	ll operator | (const point &rhs) {return 1ll * x * rhs.y - 1ll * y * rhs.x;}
	ll operator ^ (const point &rhs) {return 1ll * x * rhs.x + 1ll * y * rhs.y;}
};
struct dat {point p; int col, id;} a[MAXN + 5];
bool cmp(dat A, dat B) {return (A.p.x ^ B.p.x) ? (A.p.x < B.p.x) : (A.p.y < B.p.y);}
ll area(point A, point B, point C) {return abs((B - A) | (C - A));}
struct tri {
	int A, B, C;
	tri() {A = B = C = 0;}
	tri(int _A = 0, int _B = 0, int _C = 0): A(_A), B(_B), C(_C) {}
	bool in(int id) {
		return area(a[A].p, a[B].p, a[id].p) + area(a[A].p, a[C].p, a[id].p) +
			   area(a[B].p, a[C].p, a[id].p) == area(a[A].p, a[B].p, a[C].p);
	}
	int gettyp() {
		if (a[A].col == a[B].col && a[B].col == a[C].col) return -1;
		static int cnt[2]; fill0(cnt);
		cnt[a[A].col]++; cnt[a[B].col]++; cnt[a[C].col]++;
		return (cnt[1] > cnt[0]);
	}
};
struct convex {
	vector<int> vec; // in counter-clockwise direction
	bool in(int x) {
		for (int i = 2; i < vec.size(); i++) if (tri(vec[0], vec[i - 1], vec[i]).in(x))
			return 1;
		return 0;
	}
} H;
bool on[MAXN + 5]; int f[MAXN + 5]; vector<pii> res;
int find(int x) {return (!f[x]) ? x : f[x] = find(f[x]);}
void con(int x, int y) {
	assert(a[x].col == a[y].col);
	int fx = find(x), fy = find(y);
	if (fx != fy) {
		f[fx] = fy;
		res.pb(mp(a[x].id - 1, a[y].id - 1));
	} else cerr << "!!!\n";
}
void solve_tri(tri A, vector<int> pt) {
	if (pt.empty()) return; int id = pt[0];
//	printf("solve:"); for (int x : pt) printf(" %d", x); printf("\n");
	if (~A.gettyp()) {
		for (int x : pt) if (a[x].col == (A.gettyp() ^ 1))
			id = x;
	}
	if (a[A.A].col == a[id].col) con(A.A, id);
	else if (a[A.B].col == a[id].col) con(A.B, id);
	else if (a[A.C].col == a[id].col) con(A.C, id);
	else exit(-1);
	vector<int> vec1, vec2, vec3;
	for (int x : pt) if (x != id) {
		if (tri(A.A, A.B, id).in(x)) vec1.pb(x);
		else if (tri(A.B, A.C, id).in(x)) vec2.pb(x);
		else if (tri(A.C, A.A, id).in(x)) vec3.pb(x);
	}
	solve_tri(tri(A.A, A.B, id), vec1);
	solve_tri(tri(A.B, A.C, id), vec2);
	solve_tri(tri(A.C, A.A, id), vec3);
}
void solve_hull(convex h, vector<int> pt) {
	if (pt.empty()) return;
	static int cnt[2]; fill0(cnt);
	for (int i = 0; i < h.vec.size(); i++) cnt[a[h.vec[i]].col]++;
	int C = (cnt[0] == 1) ? 0 : 1, id = pt[0];
	for (int x : pt) if (a[x].col == C) id = x;
	for (int x : h.vec) if (a[x].col == a[id].col) {con(x, id); break;}
//	printf("! %d %d\n", C, id);
//	for (int x : pt) printf("%d ", x); printf("\n");
	static vector<int> bel[MAXN + 5];
	for (int i = 0; i < h.vec.size(); i++) bel[i].clear();
	for (int x : pt) if (x != id) {
		for (int j = 0; j < h.vec.size(); j++)
			if (tri(h.vec[j], h.vec[(j + 1) % h.vec.size()], id).in(x))
				bel[j].pb(x);
	}
	for (int i = 0; i < h.vec.size(); i++)
		solve_tri(tri(h.vec[i], h.vec[(i + 1) % h.vec.size()], id), bel[i]);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].p.x, &a[i].p.y, &a[i].col), a[i].id = i;
	sort(a + 1, a + n + 1, cmp); static int stk[MAXN + 5]; int tp = 0;
	for (int i = 1; i <= n; i++) {
		while (tp > 1 && ((a[stk[tp - 1]].p - a[stk[tp]].p) | (a[i].p - a[stk[tp]].p)) >= 0) --tp;
		stk[++tp] = i;
	}
	for (int i = 1; i <= tp; i++) H.vec.pb(stk[i]);
	for (int i = 1; i <= n; i++) {
		while (tp > 1 && ((a[stk[tp - 1]].p - a[stk[tp]].p) | (a[i].p - a[stk[tp]].p)) <= 0) --tp;
		stk[++tp] = i;
	}
	for (int i = tp - 1; i > 1; i--) H.vec.pb(stk[i]);
	for (int id : H.vec) on[id] = 1;
	int pos = -1, cnt = 0;
	for (int i = 0; i < H.vec.size(); i++) if (a[H.vec[i]].col != a[H.vec[(i + 1) % H.vec.size()]].col)
		pos = (i + 1) % H.vec.size(), cnt++;
	if (cnt >= 4) return puts("Impossible"), 0;
	for (int i = 0; i < H.vec.size(); i++) if (a[H.vec[i]].col == a[H.vec[(i + 1) % H.vec.size()]].col)
		con(H.vec[i], H.vec[(i + 1) % H.vec.size()]);
	if (!~pos) {
		int id = -1;
		for (int i = 1; i <= n; i++) if (!on[i] && a[i].col != a[H.vec[0]].col)
			id = i;
		if (!~id) {
			static vector<int> bel[MAXN + 5];
			for (int i = 1; i <= n; i++) if (!on[i]) {
				for (int j = 2; j < H.vec.size(); j++)
					if (tri(H.vec[j - 1], H.vec[j], H.vec[0]).in(i))
						bel[j].pb(i);
			}
			for (int j = 2; j < H.vec.size(); j++)
				solve_tri(tri(H.vec[j - 1], H.vec[j], H.vec[0]), bel[j]);
		} else {
			static vector<int> bel[MAXN + 5];
			for (int i = 1; i <= n; i++) if (!on[i] && i != id) {
				for (int j = 0; j < H.vec.size(); j++)
					if (tri(H.vec[j], H.vec[(j + 1) % H.vec.size()], id).in(i))
						bel[j].pb(i);
			}
			for (int j = 0; j < H.vec.size(); j++)
				solve_tri(tri(H.vec[j], H.vec[(j + 1) % H.vec.size()], id), bel[j]);
		}
	} else {
		int L = pos, R = pos;
		while (a[H.vec[R]].col == a[H.vec[L]].col) R = (R + 1) % H.vec.size();
		if (R == (L + 1) % H.vec.size() || L == (R + 1) % H.vec.size()) {
			vector<int> vec;
			for (int i = 1; i <= n; i++) if (!on[i]) vec.pb(i);
			solve_hull(H, vec);
		} else {
			convex H1, H2;
			for (int i = L; i != (R + 1) % H.vec.size(); i = (i + 1) % H.vec.size())
				H1.vec.pb(H.vec[i]);
			for (int i = R; i != (L + 1) % H.vec.size(); i = (i + 1) % H.vec.size())
				H2.vec.pb(H.vec[i]);
			vector<int> vec1, vec2;
			for (int i = 1; i <= n; i++) if (!on[i]) {
				if (H1.in(i)) vec1.pb(i);
				else vec2.pb(i);
			}
			solve_hull(H1, vec1); solve_hull(H2, vec2);
		}
	}
	printf("%d\n", res.size());
	for (pii p : res) printf("%d %d\n", p.fi, p.se);
	return 0;
}
/*
11
0 0 0
0 10000 0
10000 0 1
10000 10000 0
5001 4994 0
2499 2501 0
7503 7499 0
4010 5995 0
6011 3987 0
1015 5003 0
5043 5007 0
*/
```

---

