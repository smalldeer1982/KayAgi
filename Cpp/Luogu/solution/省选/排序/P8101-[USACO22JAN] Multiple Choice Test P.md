# [USACO22JAN] Multiple Choice Test P

## 题目描述

奶牛们正在参加一个选择题测试。在通常的测试中，对每个问题你的选项会被单独评分然后累加，而在此测试中，你的选项在累加之后再评分。

具体地说，你被给定二维平面上的 $N$（$2 \le N \le 10^5$）组整数向量，其中每个向量用一个有序对 $(x,y)$ 表示。从每组中选择一个向量，使向量的总和尽可能远离原点。

输入保证向量的总数不超过 $2 \times 10^5$。每组至少包含 $2$ 个向量，并且一组内所有向量各不相同。输入同时保证每个 $x$ 和 $y$ 坐标的绝对值不超过 $\dfrac{10^9}{N}$。

## 说明/提示

【样例解释】

最优方案是从第一组选择 $(1,0)$，从第二组中选择 $(0,1)$，从第三组选择 $(10,10)$。这些向量之和等于 $(11,11)$，与原点的距离平方等于 $11^2+11^2=242$。

【数据范围】

- 测试点 1-5 中，向量的总数不超过 $10^3$。
- 测试点 6-9 中，每一组恰好包含 $2$ 个向量。
- 测试点 10-17 没有额外限制。

供题：Benjamin Qi

## 样例 #1

### 输入

```
3

2
-2 0
1 0

2
0 -2
0 1

3
-5 -5
5 1
10 10```

### 输出

```
242```

# 题解

## 作者：Alex_Wei (赞：11)

> [P8101 [USACO22JAN] Multiple Choice Test P](https://www.luogu.com.cn/problem/P8101)

对于没见过套路的新手，是好题；对于见多识广的高手，是套路题。

关键结论：可能成为答案的点一定在凸包上。根据 $x ^ 2$ 的凸性容易证明。接下来就好做了。考虑对每组向量均建出凸包，求出这 $n$ 个凸包的闵可夫斯基和，最后用大凸包上的点更新答案。

大小为 $a$ 和大小为 $b$ 的凸包的闵可夫斯基和需要 $\mathcal{O}(a + b)$ 时间计算，因此考虑启发式合并。视向量总数与 $n$ 同级，时间复杂度为 $\mathcal{O}(n\log n)$。

更为厉害的做法：考虑我们对两个凸包做闵可夫斯基和的过程，就是把所有边拿出来归并排序，再塞回去，这个过程 **不改变边本身**。因此，我们直接把所有凸包的所有边拿出来，**极角排序**，再塞回去，就不需要启发式合并的过程了，相当于同时求多个凸包的闵可夫斯基和。时间复杂度也是线性对数，但是比上个做法高妙多了。

代码分别是启发式合并和直接对边排序，后者借鉴了 Benq 在极角排序上的处理。

- upd：对错误代码进行更新，详见 https://www.luogu.com.cn/discuss/417389。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 5;

struct Pt {
	int x, y;
	bool operator < (const Pt &rhs) {return x != rhs.x ? x < rhs.x : y < rhs.y;}
	Pt operator + (const Pt &rhs) {return {x + rhs.x, y + rhs.y};}
	Pt operator - (const Pt &rhs) {return {x - rhs.x, y - rhs.y};}
	ll norm() {return 1ll * x * x + 1ll * y * y;}
	ll cross(const Pt &rhs) {return 1ll * x * rhs.y - 1ll * y * rhs.x;}
	void print(string info = "") {cout << info << " " << x << " " << y << endl;}
};

void print(vector <Pt> &v, string info) {
	cout << "print convex hull : " << info << "\n";
	for(auto it : v) cout << it.x << " " << it.y << "\n";
	cout << "finished.\n";
}

ll n, ans;
vector <Pt> c[N]; Pt cen;
set <pair <int, int>> s;
bool cmp(Pt x, Pt y) {
	ll res = (x - cen).cross(y - cen);
	if(res) return res > 0;
	return (x - cen).norm() > (y - cen).norm();
}
void ConvexHull(vector <Pt> &v) {
	static Pt stc[N]; int top = 0;
	for(int i = 1; i < v.size(); i++) if(v[i] < v[0]) swap(v[i], v[0]);
	cen = stc[top = 1] = v[0], sort(v.begin() + 1, v.end(), cmp);
	for(int i = 1; i < v.size(); i++) {
		while(top >= 2 && (stc[top] - stc[top - 1]).cross(v[i] - stc[top]) < 0) top--;
		stc[++top] = v[i];
	} v.clear(), assert(v.size() == 0);
	for(int i = 1; i <= top; i++) v.push_back(stc[i]);
}

vector <Pt> operator + (vector <Pt> &lhs, vector <Pt> &rhs) {
	vector <Pt> ret; ret.push_back(lhs[0] + rhs[0]);
	static Pt sl[N], sr[N]; int pl = 0, pr = 0, L = lhs.size(), R = rhs.size();
	for(int i = 0; i < L; i++) sl[i] = lhs[(i + 1) % L] - lhs[i];
	for(int i = 0; i < R; i++) sr[i] = rhs[(i + 1) % R] - rhs[i];
	while(pl < L && pr < R) ret.push_back(ret.back() + (sl[pl].cross(sr[pr]) > 0 || sl[pl].cross(sr[pr]) == 0 && sl[pl].x > sr[pr].x ? sl[pl++] : sr[pr++]));
	while(pl < L) ret.push_back(ret.back() + sl[pl++]);
	while(pr < R) ret.push_back(ret.back() + sr[pr++]);
	return ret.pop_back(), ret;
}

int main() {
	cin >> n;
	for(int i = 1, k, x, y; i <= n; i++) {
		scanf("%d", &k);
		while(k--) cin >> x >> y, c[i].push_back({x, y});
		ConvexHull(c[i]), s.insert({c[i].size(), i});
	} while(s.size() > 1) {
		int a = s.begin() -> second, b = (++s.begin()) -> second;
		s.erase(s.begin()), s.erase(s.begin());
		c[a] = c[a] + c[b], s.insert({c[a].size(), a});
	} for(auto it : c[s.begin() -> second]) ans = max(ans, it.norm());
	assert(c[s.begin() -> second].size() <= 2e5);
	cout << ans << endl;
	return 0;
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e5 + 5;

struct Pt {
	int x, y;
	bool operator < (const Pt &rhs) {return x != rhs.x ? x < rhs.x : y < rhs.y;}
	Pt operator + (const Pt &rhs) {return {x + rhs.x, y + rhs.y};}
	Pt operator - (const Pt &rhs) {return {x - rhs.x, y - rhs.y};}
	ll norm() {return 1ll * x * x + 1ll * y * y;}
	ll cross(const Pt &rhs) {return 1ll * x * rhs.y - 1ll * y * rhs.x;}
	bool dir() {return x > 0 || (x == 0 && y > 0);}
} off[N];

ll n, cnt, ans;
vector <Pt> c; Pt cen, start;
bool cmp(Pt x, Pt y) {
	ll res = (x - cen).cross(y - cen);
	if(res) return res > 0;
	return (x - cen).norm() > (y - cen).norm();
}
void ConvexHull(vector <Pt> &v) {
	static Pt stc[N]; int top = 0;
	for(int i = 1; i < v.size(); i++) if(v[i] < v[0]) swap(v[i], v[0]);
	cen = stc[top = 1] = v[0], sort(v.begin() + 1, v.end(), cmp);
	for(int i = 1; i < v.size(); i++) {
		while(top >= 2 && (stc[top] - stc[top - 1]).cross(v[i] - stc[top]) < 0) top--;
		stc[++top] = v[i];
	} for(int i = (v.clear(), 1); i <= top; i++) v.push_back(stc[i]);
}

int main() {
	cin >> n;
	for(int i = 1, k, x, y; i <= n; i++) {
		scanf("%d", &k), c.clear();
		while(k--) cin >> x >> y, c.push_back({x, y});
		ConvexHull(c), start = start + c[0];
		for(int i = 1; i <= c.size(); i++) off[++cnt] = c[i % c.size()] - c[i - 1];
	}
	sort(off + 1, off + cnt + 1, [&](Pt x, Pt y) {return x.dir() != y.dir() ? x.dir() : x.cross(y) > 0;});
	for(int i = 1; i <= cnt; i++) ans = max(ans, start.norm()), start = start + off[i];
	cout << ans << endl;
	return 0;
}
```

---

## 作者：ETHANK (赞：4)

题意：给定 $n$ 组向量，求每一组中选出一个向量，加起来后最大的长度。

数据范围：向量数不超过 $10^5$ ，$|x|,|y|\le \frac{10^9}{N}$ 。

我们维护当前所有可能答案构成的点集，有

性质1：如果一个点不在该点集的凸包上，那么这个点离原点的距离不是最大的。

对每一组向量我们都可以求出它的凸包。对于第 $i$ 组向量，我们将它的凸包与前 $i-1$ 组得到的答案凸包合并，用 Minkowski 和即可。

时间复杂度：$O(N\log N)$ 。

```cpp
#include <bits/stdc++.h>
#define int long long
#define Vector Point
using namespace std;
struct Point {
    int x, y;
    friend Point operator + (Point a, Point b) {return {a.x+b.x,a.y+b.y};}
    friend Point operator - (Point a, Point b) {return {a.x-b.x,a.y-b.y};}
    friend int operator * (Point a, Point b) {return (a.x*b.y-a.y*b.x);}
};
const int inf = 1e15;
int Abs (Point a) {return (a.x*a.x+a.y*a.y);}
Point Inv (Point a) {return {-a.x,-a.y};}
int Pos (Vector X) {return (bool)((X.y)>0||(X.y==0&&X.x>0));}
const int maxn = 1e6+5;
int cmp (Vector a, Vector b) {
    if (a.y!=b.y) return a.y<b.y;
    return a.x<b.x;
}
int n;
int stk[maxn],h[maxn],used[maxn];
vector<Vector> ans;
Vector start;
vector<Vector> Convex (vector<Vector> p) {
    vector<Vector> ret,q;
    int l = p.size();
    int tp = 0;          
    sort(p.begin(),p.end(),cmp);
    stk[++tp] = 0;
    for (int i=0;i<=l;i++) used[i] = 0;
    for (int i=1;i<l;i++) {
        while (tp>=2&&(p[stk[tp]]-p[stk[tp-1]])*(p[i]-p[stk[tp]])<=0) {
            used[stk[tp--]] = 0;
        }
        used[i] = 1;  
        stk[++tp] = i;
    }
    int tmp = tp;  
    for (int i=l-2;i>=0;i--) if (!used[i]) {
        while (tp>tmp&&(p[stk[tp]]-p[stk[tp-1]])*(p[i]-p[stk[tp]])<=0) {
            used[stk[tp--]] = 0;
        }
        used[i] = 1;
        stk[++tp] = i;
    }
    for (int i=1;i<=tp;i++) ret.push_back(p[stk[i]]);
    return ret;
}
int rad (Vector a, Vector b) {   
    int A = Pos(a);
    int B = Pos(b);
    if (A!=B) return A>B;
    return a*b>0;
}
int Minkowski () {
    int res = 0;
    sort(ans.begin(),ans.end(),rad);
    for (int i=0;i<ans.size();i++) {
        res = max(res,Abs(start));
        start = start+ans[i];
    }
    res = max(res,Abs(start));
    return res;
}
signed main () {
    int T;cin>>T;
    while (T--) {
        cin>>n;
        vector<Vector> v;
        for (int i=1;i<=n;i++) {
            int x, y;
            cin>>x>>y;
            v.push_back({x,y});
        }    
        vector<Vector> res = Convex(v); 
        if (res[res.size()-1].x==res[0].x && res[res.size()-1].y==res[0].y) res.pop_back();
        for (int i=1;i<res.size();i++) ans.push_back(res[i]-res[i-1]);
        ans.push_back(res[0]-res[res.size()-1]);
        start = start+res[0];
    }
    int fans = Minkowski();
    cout<<fans<<endl;
    return 0;
}
```



---

## 作者：Anonymely (赞：1)

计算几何入门题。

不难证明答案一定取在凸包上，证明考虑若取在凸包内部则可调整到外部。

也就是要对 $n$ 个凸包求闵可夫斯基和，分治即可。

注意细节，额外注意判断共线等情况。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define debug(x) cerr << #x << " = " << x << '\n'
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

struct Point {
	int x, y;
	Point () {}
	Point (int _x, int _y) {x = _x, y = _y;}
	Point operator + (Point rhs) const {return Point(x + rhs.x, y + rhs.y);}
	Point operator - (Point rhs) const {return Point(x - rhs.x, y - rhs.y);}
	ll norm() {return 1ll * x * x + 1ll * y * y;}
	friend ll cross(Point a, Point b) {return 1ll * a.x * b.y - 1ll * a.y * b.x;}
} ;
const int N = 2e5 + 5;
Point stk[N], sa[N], sb[N]; int top;
void Convex(vector <Point> &p) {
	int n = p.size();
	sort(p.begin(), p.end(), [&](auto u, auto v) {return u.x == v.x ? u.y < v.y : u.x < v.x;});
	sort(p.begin() + 1, p.end(), [&](auto u, auto v) {return cross(u - p[0], v - p[0]) == 0 ? u.norm() > v.norm() : cross(u - p[0], v - p[0]) > 0;});
	top = 0;
	stk[++top] = p[0];
	for (int i = 1; i < n; i++) {
		while (top >= 2 && cross(stk[top] - stk[top - 1], p[i] - stk[top]) < 0) top--;
		stk[++top] = p[i];
	}
	p.clear();
	for (int i = 1; i <= top; i++) p.push_back(stk[i]);
}
vector <Point> Minkowski(vector <Point> a, vector <Point> b) {
	int n = a.size(), m = b.size();
	for (int i = 1; i < n; i++) sa[i] = a[i] - a[i - 1];
	for (int i = 1; i < m; i++) sb[i] = b[i] - b[i - 1];
	sa[n] = a[0] - a[n - 1], sb[m] = b[0] - b[m - 1];
	top = 0;
	int ia = 1, ib = 1;
	while (ia <= n && ib <= m) {
		if (cross(sa[ia], sb[ib]) > 0 || (cross(sa[ia], sb[ib]) == 0 && sa[ia].x > sb[ib].x)) stk[++top] = sa[ia++];
		else stk[++top] = sb[ib++];
	}
	while (ia <= n) stk[++top] = sa[ia++];
	while (ib <= m) stk[++top] = sb[ib++];
	vector <Point> c;
	Point st = a[0] + b[0];
	c.push_back(st);
	for (int i = 1; i < top; i++) st = st + stk[i], c.push_back(st);
	return c;
}
int n;
vector <Point> p[N];
vector <Point> solve(int l, int r) {
	if (l == r) return p[l];
	int mid = (l + r) / 2;
	return Minkowski(solve(l, mid), solve(mid + 1, r));
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i = 1, m; i <= n; i++) {
		cin >> m;
		for (int j = 1, x, y; j <= m; j++) {
			cin >> x >> y;
			p[i].push_back(Point(x, y));
		}
		Convex(p[i]);
	}
	vector <Point> res = solve(1, n);
	ll ans = 0;
	for (auto p : res) ckmax(ans, p.norm());
	cout << ans << '\n';
	QwQ01AwA;
}
```

---

## 作者：yanqijin (赞：1)

# 题目大意
给你多组向量，每组中选一个向量，使得所有选出的向量之和离原点的欧几里得距离的平方最大。
# 思路
我们发现暴力会超时，所以只考虑保留对我们更新答案有用的点，当我们将对我们有用的点画出来时，我们发现其实有用的点都在这几个点围成的凸包上，所以第一步，考虑将每组点的凸包求出来(这里使用 Graham 算法)。

然后我们将所有的凸包画出来之后，我们发现答案其实就在这几个凸包的闵可夫斯基和的凸包的边上，所以将所有凸包合并之后再把这个大凸包的边上的所有点遍历一遍即可(合并过程使用极角排序)。

时间复杂度 $O(n \log n)$。
# code
```cpp
#include<cstdio>
#include<cmath>
using namespace std;
long long n,cnt=0,cntt=0,t=0,h=0,ans=0;
struct node{
	long long x,y;
	double p;
}a[200005],s[200005],k[200005],first;
void read(long long &x)
{
	x=0;
	int w=1;
	char ch=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=w;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	int sta[100];
	int top=0;
	do
	{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(sta[--top]+48);
	putchar(' ');
}
long long max(long long a,long long b){return a>b?a:b;}
double dis(node a1,node b1){return sqrt((a1.x-b1.x)*(a1.x-b1.x)+(a1.y-b1.y)*(a1.y-b1.y));}
void swap(node &a,node &b)
{
	node p=a;
	a=b;b=p;
}
long long pd(node a1,node aa1,node b1,node bb1)
{
	return (aa1.x-a1.x)*(bb1.y-b1.y)-(bb1.x-b1.x)*(aa1.y-a1.y);
}
void qsort(long long l,long long r)
{
	double mid=a[l+r>>1].p;
	long long i=l,j=r;
	do
	{
		while(a[i].p>mid) i++;
		while(a[j].p<mid) j--;
		if(i<=j)
		{
			swap(a[i],a[j]);
			i++;j--;
		}
	}while(i<=j);
	if(i<r) qsort(i,r);
	if(l<j) qsort(l,j);
}
void qsort1(long long l,long long r)
{
	double mid=k[l+r>>1].p;
	long long i=l,j=r;
	do
	{
		while(k[i].p>mid) i++;
		while(k[j].p<mid) j--;
		if(i<=j)
		{
			swap(k[i],k[j]);
			i++;j--;
		}
	}while(i<=j);
	if(i<r) qsort1(i,r);
	if(l<j) qsort1(l,j);
}
void Graham(long long n)
{
	cnt=0;
	node minn;
	minn.x=minn.y=2147483647;
	for(int i=1;i<=n;i++)
	{
		read(a[i].x);read(a[i].y);
		if(i>1 and a[i].y<a[1].y)
		{
			swap(a[i],a[1]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		a[i].p=atan2(a[i].x-a[1].x,a[i].y-a[1].y);
	}
	qsort(2,n);
	s[++cnt]=a[1];
	for(int i=2;i<=n;i++)
	{
		while(cnt>1 and pd(s[cnt-1],s[cnt],s[cnt],a[i])<0) cnt--;
		s[++cnt]=a[i];
	}
	if(s[1].x==minn.x)
	{
		if(s[1].y>minn.y)
		{
			minn.x=s[1].x;
			minn.y=s[1].y;
		}
	}
	else if(s[1].x<minn.x)
	{
		minn.x=s[1].x;
		minn.y=s[1].y;
	}
	k[++cntt].x=s[1].x-s[cnt].x;
	k[cntt].y=s[1].y-s[cnt].y;
	k[cntt].p=atan2(k[cntt].x,k[cntt].y);
	for(int i=2;i<=cnt;i++)
	{
		k[++cntt].x=s[i].x-s[i-1].x;
		k[cntt].y=s[i].y-s[i-1].y;
		k[cntt].p=atan2(k[cntt].x,k[cntt].y);
		if(s[i].x==minn.x)
		{
			if(s[i].y>minn.y)
			{
				minn.x=s[i].x;
				minn.y=s[i].y;
			}
		}
		else if(s[i].x<minn.x)
		{
			minn.x=s[i].x;
			minn.y=s[i].y;
		}
	}
	first.x+=minn.x;
	first.y+=minn.y;
	return ;
}
int main()
{
	read(t);
	while(t--)
	{
		read(h);
		Graham(h);
	}
	qsort1(1,cntt);
	for(int i=1;i<=cntt;i++)
	{
		ans=max(ans,first.x*first.x+first.y*first.y);
		first.x+=k[i].x;
		first.y+=k[i].y;
	}
	write(ans);
	return 0;
}
```

---

## 作者：Red_river (赞：1)

### 题目大意

这道题其实就是一道凸包的模板题，大概题意就是给你一个 $N$ 然后在这 $N$ 组数据中每组挑一个点来相加，得到最大的两数平方和。其实这几个向量就是几个点而已，然后求最大的凸包，及所有的凸包之和就行了。

### 题意分析

竟然是凸包，那我们就有法了啊。每次输入就先排好序，再接着用凸包来求，毕竟如果没有序的话就不符合贪心了。毕竟该算法本身就是顺时针或逆时针转，遇到右拐或左拐就跳出，因为这样的话就是凹包了，与题意不相符。再接着，我们找到纵坐标最小的点来枚举起点，因为这个点一定在凸包上。再接着看上凸包和下凸包壳，如果叉积小于等于零的话，就说明不合法，就跳出来。**即化简为一个栈，不合法跳出，合法则继续**。可以用闵可夫斯基和优化，但此处并没使用，毕竟时间复杂度已经够用了。具体可以参考注释理解。

### CODE

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define int long long
#define INF 2147483647
#define mod 998244353
#define N 200005
#define NO printf("No\n")
#define YES printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,ans,num,cnt,tot;
int head[N],dis[N];

struct X{
	int x,y,id;
	X(){};
}f[N],wis[N],k,sum;

struct sat2{
	int x,y;
	double p;
	sat2(){}
}vis[N*2];

X got(X a,X b){
	if(a.y==b.y){
		if(a.x>b.x) return a;
		else return b;
	}
	if(a.y<b.y){
		return a;
	}
	return b;
}

struct node{//叉积，正负性等
	X add(X a,X b){X c;c.x=a.x+b.x,c.y=a.y+b.y;return c;}
	X sub(X a,X b){X c;c.x=a.x-b.x,c.y=a.y-b.y;return c;}
	bool pd(X a,X b){return sgn(a.x-b.x)==0&&sgn(a.y-b.y)==0;}
	int Cross(X a,X b){return a.x*b.y-a.y*b.x;}
	int sgn(int x){if(abs(x)==0) return 0;else return x<0?-1:1;}
}_;

void qsort2(int l,int r){
	int i=l,j=r;
	long double mid=vis[(l+r)/2+1].p;
	while(i<=j){
		while(vis[i].p<mid) i++;
		while(vis[j].p>mid) j--;
		if(i<=j){
			swap(vis[i],vis[j]);
			i++,j--;
		}
	}
	if(l<j) qsort2(l,j);
	if(i<r) qsort2(i,r);
}

void qsort(int l,int r){
	int i=l,j=r;
	int mid=f[(l+r)/2+1].x,midy=f[(l+r)/2+1].y;
	while(i<=j){
		while(_.sgn(f[i].x-mid)<0||(_.sgn(f[i].x-mid)==0&&_.sgn(f[i].y-midy)<0)) i++;
		while(_.sgn(f[j].x-mid)>0||(_.sgn(f[j].x-mid)==0&&_.sgn(f[j].y-midy)>0)) j--;
		if(i<=j){
			swap(f[i],f[j]);
			i++,j--;
		}
	}
	if(l<j) qsort(l,j);
	if(i<r) qsort(i,r);
}

int get(int n){//取上凸壳和下凸壳
	qsort(0,n-1);int v=0;
	for(int i=0;i<n;i++){
		while(v>1&&_.Cross(_.sub(wis[v-1],wis[v-2]),_.sub(f[i],wis[v-1]))<=0) v--;
		wis[v++]=f[i];
	}
	int j=v;
	for(int i=n-2;i>=0;i--){
		while(v>j&&_.Cross(_.sub(wis[v-1],wis[v-2]),_.sub(f[i],wis[v-1]))<=0) v--;
		wis[v++]=f[i];
	}
	if(n>1) v--;
	return v;
}

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');return;
	}
	if(x<0){
		x=-x;putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()
{
//	freopen("multiple.in","r",stdin);
//	freopen("multiple.out","w",stdout);
	read(n);for(int i=1;i<=n;i++){
		read(dis[i]);
		for(int j=0;j<dis[i];j++) read(f[j].x),read(f[j].y);
		int len=get(dis[i]);k.x=k.y=k.id=INF;
		for(int j=0;j<len;j++) wis[j].id=j+1,k=got(k,wis[j]);
		sum.x+=k.x,sum.y+=k.y;
		for(int j=k.id-1;j>0;j--){
			vis[cnt].x=wis[j-1].x-wis[j].x;
			vis[cnt].y=wis[j-1].y-wis[j].y;
			vis[cnt].p=atan2(vis[cnt].y,vis[cnt].x);
			cnt++;
		}
		if(len){
			vis[cnt].x=wis[len-1].x-wis[0].x;
			vis[cnt].y=wis[len-1].y-wis[0].y;
			vis[cnt].p=atan2(vis[cnt].y,vis[cnt].x);
			cnt++;
		}
		for(int j=len-1;j>=k.id;j--){
			vis[cnt].x=wis[j-1].x-wis[j].x;
			vis[cnt].y=wis[j-1].y-wis[j].y;
			vis[cnt].p=atan2(vis[cnt].y,vis[cnt].x);//atan2：极角函数
			cnt++;
		}
	}
	qsort2(0,cnt-1);//排序（极角来排）
	int ans=sum.x*sum.x+sum.y*sum.y;
	for(int i=cnt-1;i>=0;i--){//统计答案
		sum.x+=vis[i].x,sum.y+=vis[i].y;
		ans=max(ans,(sum.x*sum.x+sum.y*sum.y));
	}
	wh(ans);
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

考虑点集 $\mathcal P$ 表示所有选择向量的方式中，能得到的点构成的集合。

答案一定在 $\mathcal P$ 的凸包上。

而两个点集以 $\{(x_i+X_j,y_i+Y_j) | 1 \le i \le |\mathcal{P}_1|,1 \le j \le |\mathcal{P}_2|\}$ 合并，这就是闵可夫斯基和的形式。

求出对应的上凸壳和下凸壳，直接把所有边放一起排序即可。

代码可以写的简单一点：只需要处理上凸壳，因为把整个平面上下对称一下下凸壳就变成上凸壳了。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,ans;
vector<pair<int,int>> pt[MAXN];
struct Node {int x,y;}st[MAXN];
int tot;
void insert(int x,int y) {
	while(tot>=2&&(st[tot].x-st[tot-1].x)*(y-st[tot].y)>=(st[tot].y-st[tot-1].y)*(x-st[tot].x))	tot--;
	return st[++tot]={x,y},void();
}
void solve(void) {
	int sx=0,sy=0;
	vector<pair<int,int>> df;
	ffor(i,1,n) {
		tot=0;
		sort(pt[i].begin(),pt[i].end());
		for(auto pr:pt[i]) insert(pr.first,pr.second);
		sx+=st[1].x,sy+=st[1].y;
		ffor(j,2,tot) df.push_back({st[j].x-st[j-1].x,st[j].y-st[j-1].y});	
	}
	ans=max(ans,sx*sx+sy*sy);
	sort(df.begin(),df.end(),[](pair<int,int> A,pair<int,int> B) {return A.first*B.second-A.second*B.first<0;});
	for(auto pr:df) sx+=pr.first,sy+=pr.second,ans=max(ans,sx*sx+sy*sy);
	return ; 
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) {int m;cin>>m;ffor(j,1,m) {int u,v;cin>>u>>v,pt[i].push_back({u,v});}}
	solve();
	ffor(i,1,n) ffor(j,0,pt[i].size()-1) pt[i][j].second=-pt[i][j].second;
	solve();
	cout<<ans;
	return 0;
}
```

---

## 作者：yzx3195 (赞：0)

# 题目大意

给你 $n$ 组向量，在每一组向量中选取一个，让后求加起来后最大的长度。

# 思路

**关键结论**：能够成为答案的点一定在凸包上。

具体的，对于每一组向量，我们用 `Andrew` 算法建一个凸包，不会 `Andrew` 的详见 [这里](https://www.cnblogs.com/RioTian/p/13714244.html)。

然后，我们在建完每一组凸包之后，用一个数组将每两个点之间的位移量存下来，对这个数组 [极角排序]([计算几何——极角排序-CSDN博客](https://blog.csdn.net/qq_44691917/article/details/105264091))。然后再求一个闵可夫斯基和即可，实际上就是，在求完每一个凸包之后，用一个向量 $fr$，再按每个凸包的第一个点的横纵坐标位移，之后再统计答案。其他的详见代码。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e05 + 7;

#define gc getchar //卡常用

#define int long long

int n, g;

struct Node {
    int x, y;
    friend Node operator-(Node a, Node b)
    {
        return Node{a.x - b.x, a.y - b.y};
    }
    friend Node operator+(Node a, Node b)
    {
        return Node{a.x + b.x, a.y + b.y};
    }
} Num[MAXN];

int stck[MAXN];

Node fr = {0, 0};

int ans;

int st;

bool bz[MAXN];

Node mv[MAXN];

int cnt;

template <class T> int mymax(T x, T y)
{
    return x > y ? x : y;
}

int cross(Node a, Node b) //叉积
{
    return a.x * b.y - a.y * b.x;
}

int dis(Node x)
{
    return x.x * x.x + x.y * x.y;
}

bool cmp_a(Node a, Node b)
{
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

template <class T> void read(T &x)
{
    x = 0;
    T f = 1;
    char ch = gc();
    while(!(ch >= '0' and ch <= '9'))
    {
        if(ch == '-')
            f = -f;
        ch = gc();
    }
    while(ch >= '0' and ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = gc();
    }
    return (void) (x = x * f);
}

template <class T> void write(T x)
{
    if(x < 0)
        x = -x, putchar('-');
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return ;
}

bool pd(Node a)
{
    if(a.x > 0)
        return true;
    else if(a.x == 0 and a.y > 0)
        return true;
    return false;
}

bool cmp(Node a, Node b)
{
    if(pd(a) == pd(b))
        return cross(a, b) > 0;
    return pd(a) == 1;
}

void Andrew()
{
    sort(Num + 1, Num + g + 1, cmp_a);
    st = 0;
    stck[++st] = 1;
    for(int i = 1; i <= g; i++)
        bz[i] = false;
    for(int i = 2; i <= g; i++) //down
    {
        while(st >= 2 and cross(Num[stck[st]] - Num[stck[st - 1]], Num[i] - Num[stck[st]]) <= 0)
        {
            bz[stck[st--]] = false;
        }
        stck[++st] = i;
        bz[i] = true;
    }
    int down = st;
    for(int i = g - 1; i >= 1; i--) //up
    {
        if(!bz[i])
        {
            while(st > down and cross(Num[stck[st]] - Num[stck[st - 1]], Num[i] - Num[stck[st]]) <= 0)
            {
                bz[stck[st--]] = false;
            }
            stck[++st] = i;
            bz[i] = true;
        }
    }
    for(int i = 1; i <= st; i++)
    {
        if(i == 1)
            fr = fr + Num[stck[i]];
        else
            mv[++cnt] = Num[stck[i]] - Num[stck[i - 1]];
    }
    return ;
}

signed main()
{
	// //freopen("multiple.in", "r", stdin);
	// //freopen("multiple.out", "w", stdout);
    read(n);

    for(int i = 1; i <= n; i++)
    {
        read(g);
        for(int j = 1; j <= g; j++)
        {
            read(Num[j].x), read(Num[j].y);
        }
        Andrew();
    }

    sort(mv + 1, mv + cnt + 1, cmp);

    for(int i = 1; i <= cnt; i++)
    {
        ans = mymax(ans, dis(fr));
        fr = fr + mv[i];
    }

    printf("%lld", ans);

    return 0;
}
/*
1
10
1 2
2 4
2 6
3 5
5 2
1 3
7 4
6 5
10 9
8 4

*/
```

---

