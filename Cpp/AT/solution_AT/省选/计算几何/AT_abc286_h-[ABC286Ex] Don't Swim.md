# [ABC286Ex] Don't Swim

## 题目描述

（本题暂无题目描述。）

## 说明/提示

（本题暂无提示信息。）

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 1
3 1
3 3
1 3
0 2
5 2```

### 输出

```
5.65028153987288474496```

## 样例 #2

### 输入

```
3
0 0
2 0
1 10
3 7
10 3```

### 输出

```
8.06225774829854965279```

# 题解

## 作者：zifanwang (赞：3)

我们首先求出线段与多边形的交点，如果交点个数 $<2$ 或者有无数个交点，则可以直接输出 $S$ 到 $T$ 之间的距离。

接下来我们考虑交点个数为 $2$ 的情况。

为了方便，我们记距离 $S$ 最近的那个交点为 $P_1$，远的为 $P_2$。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/e0f0ck34.png)

在这个例子中，直线 $ST$ 将整个多边形分成了两个凸壳，我们可以从多边形下面过去也可以从上面过去。考虑对于两部份分别求出一条最短路径再取一个最小值。（这里上半部分指的是向量 $\overrightarrow{ST}$ 的左半平面）

我们先考虑上半部分的一条路径 $S\rightarrow P_1 \rightarrow A_1\rightarrow A_6 \rightarrow A_5 \rightarrow P_2 \rightarrow T$，可以发现这条路径的一个前缀 $S\rightarrow P_1 \rightarrow A_1$ 没有 $S\rightarrow A_1$ 更优（三角形的性质）。

考虑按到 $S$ 的距离的顺序枚举上半部分的所有点。我们维护一个栈，每次新加入一个点时，如果栈的大小 $<2$，就直接入栈。

对于其它情况，我们记当前这个点为 $P$，栈顶的两个点分别为 $A,B$（$A$ 比 $B$ 先入栈），考虑向量 $\overrightarrow{AB}$ 与向量 $\overrightarrow{BP}$ 的叉积，如果符号不为**负**则将 $B$ 弹出栈，重复这个操作直到符号不为负或者栈的大小 $<2$。最后再将 $P$ 入栈。

那么路径的长度就是最后的栈中相邻两个点的距离的和。对于下半部分也是类似的操作，但是在判断叉积的符号时如果符号不为**正**才将 $B$ 弹出栈。

那么剩下的问题就是如何求出两半部份的点了。我们记 $P_1$ 所在的线段的两个端点分别是 $A_i,A_{(i+1)\mod n}$（如果存在多条线段则任取一个），$P_2$ 所在的线段的两个端点分别是 $A_j,A_{(j+1)\mod n}$，那么点 $A_{i+1},A_{i+2},\dots,A_{n-1},A_0,A_1,\dots A_j$ 属于下半部分，剩下的就属于上半部分。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 100003
#define md 1000000007
#define pb push_back
#define mkp make_pair
#define ld long double
#define umap unordered_map
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
#define pq priority_queue
using namespace std;
struct point{
	ld x,y;
	inline void in(){
		scanf("%Lf%Lf",&x,&y);
	}
}s,t,a[mxn],q[mxn+10];
struct line{
	ld k,b;
	line(point x,point y){
		k=(y.y-x.y)/(y.x-x.x);
		b=x.y-x.x*k;
	}
	inline ld at(ld x){
		return x*k+b;
	}
};
const ld esp=1e-8;
inline point operator-(point x,point y){
	return {x.x-y.x,x.y-y.y};
}
inline bool operator==(point x,point y){
	return fabs(x.x-y.x)<esp&&fabs(x.y-y.y)<esp;
}
inline bool operator==(line x,line y){
	return fabs(x.k-y.k)<esp&&fabs(x.b-y.b)<esp;
}
inline point operator&(line a,line b){
	ld x=(b.b-a.b)/(a.k-b.k);
	return {x,a.k*x+a.b};
}
inline ld operator*(point x,point y){
	return x.x*y.y-x.y*y.x;
}
inline int cmp(ld x){
	if(fabs(x)<esp)return 0;
	return x<0?-1:1;
}
inline ld len(point x){
	return sqrt(x.x*x.x+x.y*x.y);
}
int n,m;
vector<pair<point,int> >st,d1;
ld ans1,ans2;
inline void add1(point x){
	while(m>1&&(x==q[m]||cmp((q[m]-q[m-1])*(x-q[m]))!=1))m--;
	q[++m]=x;
}
inline void add2(point x){
	while(m>1&&(x==q[m]||cmp((q[m]-q[m-1])*(x-q[m]))!=-1))m--;
	q[++m]=x;
}
signed main(){
	scanf("%d",&n);
	rept(i,0,n)a[i].in();
	s.in(),t.in();
	line d(s,t);
	rept(i,0,n){
		line x(a[i],a[(i+1)%n]);
		if(s.x==t.x&&a[i].x==a[(i+1)%n].x){
			if(s.x==a[i].x){
				printf("%.10Lf",len(s-t));
				return 0;
			}
			continue;
		}
		if(s.x!=t.x&&x.k==d.k){
			if(x.b==d.b){
				printf("%.10Lf",len(s-t));
				return 0;
			}
			continue;
		}
		point p;
		if(s.x==t.x){
			p={s.x,x.at(s.x)};
		}else if(a[i].x==a[(i+1)%n].x){
			p={a[i].x,d.at(a[i].x)};
		}else p=x&d;
		if(p.x>=min(a[i].x,a[(i+1)%n].x)&&p.x<=max(a[i].x,a[(i+1)%n].x)&&p.x>=min(s.x,t.x)&&p.x<=max(s.x,t.x)&&p.y>=min(a[i].y,a[(i+1)%n].y)&&p.y<=max(a[i].y,a[(i+1)%n].y)&&p.y>=min(s.y,t.y)&&p.y<=max(s.y,t.y)){
			d1.pb(mkp(p,i));
		}
	}
	for(auto i:d1){
		for(auto j:st)if(i.first==j.first)goto next;
		st.pb(i);
		next:;
	}
	if(st.size()!=2){
		printf("%.10Lf",len(s-t));
		return 0;
	}
	if(len(s-st[0].first)>len(s-st[1].first))swap(st[0],st[1]);
	add1(s),add1(st[0].first);
	int i=(st[0].second+1)%n;
	while(1){
		add1(a[i]);
		if(i==st[1].second)break;
		i=(i+1)%n;
	}
	add1(st[1].first),add1(t);
	rep(i,2,m)ans1+=len(q[i]-q[i-1]);
	m=0;
	add2(s),add2(st[0].first);
	i=st[0].second;
	while(1){
		add2(a[i]);
		if(i==(st[1].second+1)%n)break;
		i=(i+n-1)%n;
	}
	add2(st[1].first),add2(t);
	rep(i,2,m)ans2+=len(q[i]-q[i-1]);
	printf("%.10Lf",min(ans1,ans2));
	return 0;
}
```

---

## 作者：taojinchen (赞：2)

# 思路
我们发现如果把起点和终点放在原本的凸多边形，得到一个大凸包，那么起点到终点在大凸包上的两条路径中最短的，就是最优方案。

考虑证明。首先，原本的图形就是凸多边形，所以弧线就不可能最优。其次，大凸包的走法一定优于凹多边形。我们发现如果有一个地方凹进去，那么如果把两条边的两个端点连起来，直接两点之间线段最短，最后还是变回了大凸包。

在实际写的时候，要特判起点和终点的连线不穿过被围起来的地方而且两个点都不在大凸包上，直接两点之间线段最短。

一定要注意一点，直接输出它不一定给你保留七位小数。还有，起点和终点都不在被围起来的地方。我不知道我为什么知道。
# 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define dl double
#define ld long double
using namespace std;
const ll kM = 2e5 + 5;
ll n, q, i, j, p[kM], top, sx, sy, tx, ty, t;
struct M{
  dl x, y;
}a[kM];
ld ans, cnt;
ll cmp(M a, M b){
  if(a.x == b.x) return a.y > b.y;
  return a.x < b.x;
}
ll tmp(M f, M s){
  f.x -= a[1].x, s.x -= a[1].x;
  f.y -= a[1].y, s.y -= a[1].y;
  if(f.x * s.y - f.y * s.x == 0){
    return (f.x * f.x + f.y * f.y) < (s.x * s.x + s.y * s.y);
  }
  return f.x * s.y - s.x * f.y > 0;
}
ll lt(M f, M s, M o){
  f.x -= o.x, s.x -= o.x;
  f.y -= o.y, s.y -= o.y;
  if(f.x * s.y - f.y * s.x == 0){
    return (f.x * f.x + f.y * f.y) > (s.x * s.x + s.y * s.y);
  }
  return f.x * s.y - s.x * f.y > 0;
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  n += 2;
  for(i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y;
  }
  sx = a[n - 1].x, sy = a[n - 1].y;
  tx = a[n].x, ty = a[n].y;
  sort(a + 1, a + 1 + n, cmp);
  sort(a + 2, a + 1 + n, tmp);
  p[++top] = 1;
  for(i = 2; i <= n; i++){
    while(top > 1 && lt(a[i], a[p[top]], a[p[top - 1]])){
      --top;
    }
    p[++top] = i;
  }
  while(top > 1 && lt(a[1], a[p[top]], a[p[top - 1]])){
    --top;
  }
  for(i = 1; i <= top; i++){
    p[i + top] = p[i];
  }
  t = 0;
  for(i = 2; i <= 2 * top; i++){
    dl dx = a[p[i]].x - a[p[i - 1]].x, dy = a[p[i]].y - a[p[i - 1]].y;
    if(sx == a[p[i - 1]].x && sy == a[p[i - 1]].y) t = 1;
    if(t && tx == a[p[i - 1]].x && ty == a[p[i - 1]].y) break;
    if(t) cnt += sqrt(dx * dx + dy * dy);
  }
  if(i > 2 * top){
    dl t = sqrt((sx - tx) * (sx - tx) + (sy - ty) * (sy - ty));
    printf("%.7lf", t);
    return 0;
  }
  ++top;
  for(i = 2; i <= top; i++){
    dl dx = a[p[i]].x - a[p[i - 1]].x, dy = a[p[i]].y - a[p[i - 1]].y;
    ans += sqrt(dx * dx + dy * dy);
  }
  dl t;
  if(ans - cnt < cnt) t = ans - cnt;
  else t = cnt;
  printf("%.7lf", t);
  return 0;
}
```

---

## 作者：_Imaginary_ (赞：1)

第一次赛场上做出 Ex，祭之。（其实我还没做出过 G。）

## Problem

给你平面上的 $S,T$ 以及一个多边形的墙，求 $S\to T$ 不跨越墙的最短路。

一道不错的计算几何。

## Solution 1

建议不感兴趣的直接看 Solution 2。

首先，如果 $S\to T$ 线段与多边形的边不交，那么两点之间线段最短。

```
      B G
     A    E
S               T
     C    F
      D H
```

假如我们有一条路是 $S\to A\to B \to G\to T$，我们发现在 $\Delta ABS$ 中，$|SA|+|AB|>|SB|$，所以 $S\to B\to G\to T$ 是最优的。

经过一些尝试，我们发现：

最短路径必须形如：$S$ 到 $S$ 对多边形的一条切线的切点（比如图中的 $B,D$，即整个多边形在切线的一侧，且切线经过多边形的一个顶点）到 $T$ 的一个切点（这一段沿着多边形外框）到 $T$。

切点的话，$S$ 和 $T$ 分别处理，比如处理 $S$ 的时候，把所有点按照极角排序，取最大和最小的就行。

然后讨论 $2\times 2=4$ 种情况就可以了。

一个小提示：`atan2(y,x)` 值域是 $[-\pi,\pi]$，需要特殊处理。我的处理是手动把值域处理成 $[0,2\pi]$，然后特判存在点同时在 $S$ 的右下方和右上方的情况。

总之有那么点复杂，我考场上花了整整九十几分钟外加 7 发罚时才干出来，其它啥事没干。

**upd：**判断线段不相交时一定不能等于 0，具体看代码。

为什么？因为：

```
S=(-100,0),T=(100,0)
A(-1,0) B(0,1) C(1,0) D(0,-1)
```

线段 $ST$ 与别的线段只交在端点，会出问题，误判成与多边形不相交。

贴个丑陋的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define db double
const int N=100005;
const db eps=1e-9;
#define pi 6.283185307179
int n;
inline int sgn(db a) {return a<-eps?-1:a>eps;}
inline int cmp(db a,db b){return sgn(a-b);}
struct P{
	db x,y;
	P operator +(P p){return {x+p.x,y+p.y};}
	P operator -(P p){return {x-p.x,y-p.y};}
	db operator *(P p){return x*p.y-y*p.x;}
	P operator /(db d){return {x/d,y/d};}
	bool operator <(const P& p) const{
		int c=cmp(x,p.x);
		if(c) return c==-1;
		return cmp(y,p.y)==-1;
	}
	bool operator ==(const P& o) const{
		return cmp(x,o.x)==0 && cmp(y,o.y)==0;
	}
	db dot(P p){return x*p.x+y*p.y;}
	db abs2(){return x*x+y*y;}
	db abs() {return sqrt(abs2());}
	db distTo(P p) {return (*this-p).abs();}
	db alpha() {return sgn(atan2(y,x))==-1?atan2(y,x)+pi:atan2(y,x);}
	void read() {cin>>x>>y;}
	void write(){printf("(%lf,%lf)\n",x,y);}
	P rot90() {return P{-y,x};}
	P unit() {return *this/abs();}
	int quad() const{
		if(sgn(x)==1&&sgn(y)==1) return 1;
		if(sgn(x)==1&&sgn(y)<=0) return 4;
		if(sgn(x)<=0&&sgn(y)<=0) return 3;
		if(sgn(x)<=0&&sgn(y)==1) return 2;
	}
	void rev(){x=-x;}
};
P a[2*N];
P S,T;
bool inter(P A,P B,P C,P D)
{
	if(((C-A)*(D-A))*((C-B)*(D-B))>0.0) return 0;
	if(((A-C)*(B-C))*((A-D)*(B-D))>0.0) return 0;
	return 1;//这里是>不是>=!!!!!!!!!!(我赛后被hack了)
}
void solve1()
{
	for(int i=1;i<=n;i++)
		if(inter(S,T,a[i],a[i+1])) return;
	printf("%.7f",(T-S).abs());
	exit(0);
}
db dis[2*N];
db d(int x,int y)
{
	if(y<x) y+=n;
	return dis[y]-dis[x]; 
}
db dist(int x,int y)
{
	return min(d(x,y),d(y,x));
}
int s1=1,s2=1,t1=1,t2=1;

void solve(P S,int& s1,int& s2)
{
	bool vis[5];
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) 
		vis[(a[i]-S).quad()]=1;
	if((vis[1]&&vis[4]))
	{
		S.rev();
		for(int i=1;i<=n;i++) a[i].rev();
	}
	for(int i=2;i<=n;i++)
	{
		if((a[s1]-S).alpha()<(a[i]-S).alpha()) s1=i;
		if((a[s2]-S).alpha()>(a[i]-S).alpha()) s2=i;
	}
	if((vis[1]&&vis[4]))
	{
		S.rev();
		for(int i=1;i<=n;i++) a[i].rev();
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		a[i].read();
		a[n+i]=a[i];
	}
	S.read(); T.read();
	solve1();
	dis[1]=0.0;
	for(int i=2;i<=2*n;i++) dis[i]=dis[i-1]+(a[i]-a[i-1]).abs();
	solve(S,s1,s2);
	solve(T,t1,t2);
	db ans=1e19;
	ans=min(ans,(S-a[s1]).abs()+dist(s1,t1)+(a[t1]-T).abs());
	ans=min(ans,(S-a[s2]).abs()+dist(s2,t1)+(a[t1]-T).abs());
	ans=min(ans,(S-a[s1]).abs()+dist(s1,t2)+(a[t2]-T).abs());
	ans=min(ans,(S-a[s2]).abs()+dist(s2,t2)+(a[t2]-T).abs());
	printf("%.7f",ans);
	return 0;
}
```

## Solution 2

求 $S,T,A_1,A_2,\cdots,A_n$ 的凸包上 $S$ 到 $T$ 的距离。没了。~~读者自证不难~~可以参考 Solution 1 来理解。

---

## 作者：Diaоsi (赞：0)

发现最优解形如一条固定在起终点的橡皮筋绷紧凸包。把 $S$ 和 $T$ 丢进点集 $C$ 重新求出一个凸包，然后输出两个点在凸包上的最短距离，若有一个点不在凸包上则直接输出两点距离。避免了繁杂的分类讨论，非答案部分的运算可以全整。

[提交记录](https://atcoder.jp/contests/abc286/submissions/62793656)

---

## 作者：ottora (赞：0)

截至发稿前的最优解。

首先判断线段 $ST$ 是否不经过凸包内部，如果是的话直接输出 $ST$ 的长度。

否则最短路一定是经过凸包的若干相邻顶点的折线。

有个小清新做法是直接 DP 求出 $S$ 到凸包上任一点 $A_i$ 的最短路，记为 $F_i$。首先对所有 $S$ 可以直线到达的点 $A_i$ 令 $F_i = \left|SA_i\right|$，然后逆时针更新两圈 $F_{i + 1} = \min\left(F_{i + 1}, F_i + \left|A_iA_{i + 1}\right|\right)$ 再顺时针更新两圈 $F_{i - 1} = \min\left(F_{i - 1}, F_i + \left|A_iA_{i - 1}\right|\right)$，最后对于 $T$ 能直线到达的点 $A_i$ 求出 $\min F_i + \left|A_iT\right|$ 即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template <class int_t, class sqr_t = int_t> struct vec2d{
  int_t x, y;
  vec2d(): x(0), y(0){}
  vec2d(int_t x, int_t y): x(x), y(y){}
  int quad() const {
    if(x > 0 && y >= 0) return 0;
    if(x <= 0 && y > 0) return 1;
    if(x < 0 && y <= 0) return 2;
    if(x >= 0 && y < 0) return 3;
    assert(false);
  }
  bool operator < (const vec2d &rhs) const {
    return quad() < rhs.quad() || (quad() == rhs.quad() && (*this) % rhs > 0);
  }
  vec2d operator + (const vec2d &rhs) const {return vec2d(x + rhs.x, y + rhs.y);}
  vec2d operator - (const vec2d &rhs) const {return vec2d(x - rhs.x, y - rhs.y);}
  sqr_t operator * (const vec2d &rhs) const {return (sqr_t)x * rhs.x + (sqr_t)y * rhs.y;}
  sqr_t operator % (const vec2d &rhs) const {return (sqr_t)x * rhs.y - (sqr_t)rhs.x * y;}
  vec2d& operator += (const vec2d &rhs){return *this = *this + rhs;}
  vec2d& operator -= (const vec2d &rhs){return *this = *this - rhs;}
  vec2d operator - () const {return vec2d(-x, -y);}
  sqr_t sqr() const {return (sqr_t)x * x + (sqr_t)y * y;}
}; typedef vec2d<int, int64_t> vec;
bool cross(vec A, vec B, vec C, vec D){
  auto sgn = [](int64_t x){return x < 0? -1: x > 0;};
  return sgn((C - A) % (B - A)) * sgn((D - A) % (B - A)) <= 0
      && sgn((A - C) % (D - C)) * sgn((B - C) % (D - C)) <= 0;
}
bool check(vec A, vec B, vec C, vec D){
  return (D - A) % (B - A) >= 0 || (D - C) % (B - C) <= 0;
}
constexpr int MAXN = 100005;
int n; double F[MAXN], Ans;
vec A[MAXN], S, T;
int main(){
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n, cout << fixed << setprecision(20), Ans = INFINITY;
  for(int i = 0; i < n; i++) cin >> A[i].x >> A[i].y, F[i] = INFINITY;
  cin >> S.x >> S.y >> T.x >> T.y;
  bool flg = 0;
  for(int i = 0; i < n; i++) if(cross(A[i], A[(i + 1) % n], S, T)) flg = 1;
  if(!flg){cout << sqrt((S - T).sqr()) << '\n'; return 0;}
  for(int i = 0; i < n; i++) if(check(A[(i + n - 1) % n], A[i], A[(i + 1) % n], S)) F[i] = sqrt((A[i] - S).sqr());
  for(int i = 0; i < 2 * n; i++) F[(i + 1) % n] = min(F[(i + 1) % n], F[i % n] + sqrt((A[i % n] - A[(i + 1) % n]).sqr()));
  for(int i = 2 * n; i    ; i--) F[(i - 1) % n] = min(F[(i - 1) % n], F[i % n] + sqrt((A[i % n] - A[(i - 1) % n]).sqr()));
  for(int i = 0; i < n; i++) if(check(A[(i + n - 1) % n], A[i], A[(i + 1) % n], T)) Ans = min(Ans, F[i] + sqrt((A[i] - T).sqr()));
  cout << Ans << '\n';
  return 0;
}

---

## 作者：hsaht2426 (赞：0)

#### 思路：

考虑分讨：

不相交时即为两点距离。

相交时手摸一下样例：

我们先考虑沿着凸包走。

但由于三角形两边之和大于第三边，所以上述思路不对。

于是维护一个凸包，去掉凹的三角形即可。

比较凸包两种路径的大小。

#### 实现：

我们发现维护凸包的情况会包含前者的一部分，后者的所有情况。

于是我们额外对点维护一个标记，代表是否为题目所问的点。

把上下凸包拼起来，可以用异或和判断是否两个点都在凸包上，同时求出一种情况的答案。

不同时在就输出两点的距离。

否则输出两路径的最小值。

[代码](https://atcoder.jp/contests/abc286/submissions/43288972)

---

