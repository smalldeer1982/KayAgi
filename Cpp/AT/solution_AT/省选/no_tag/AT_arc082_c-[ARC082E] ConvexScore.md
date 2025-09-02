# [ARC082E] ConvexScore

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc082/tasks/arc082_c

二次元平面上に配置された $ N $ 個の点 $ (x_i,y_i) $ が与えられます。 $ N $ 点の部分集合 $ S $ であって、凸多角形をなすものを考えます。 ここで点集合$ S $が凸多角形をなすとは、 頂点の集合が $ S $ と一致するような正の面積の凸多角形が存在することとします。ただし、凸多角形の内角は全て $ 180° $ 未満である必要があります。

例えば下図では、$ S $ として {$ A,C,E $}, {$ B,D,E $} などは認められますが、{$ A,C,D,E $}, {$ A,B,C,E $}, {$ A,B,C $}, {$ D,E $}, {} などは認められません。

 ![cddb0c267926c2add885ca153c47ad8a.png](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc082_c/39667580a7bb2e28230ac88d6c9a69f608395d83.png)

$ S $ に対し、$ N $ 個の点のうち $ S $ の凸包の内部と境界 (頂点も含む) に含まれる点の個数を $ n $ とおき、 $ S $ のスコアを、$ 2^{n-|S|} $ と定義します。

凸多角形をなすような考えうる全ての $ S $ に対してスコアを計算し、これらを足し合わせたものを求めてください。

ただし答えはとても大きくなりうるので、$ 998244353 $ で割った余りをかわりに求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =N\ <\ =200 $
- $ 0\ <\ =x_i,y_i\ <\ 10^4\ (1\ <\ =i\ <\ =N) $
- $ i≠j $ なら $ x_i≠x_j $ または $ y_i≠y_j $
- $ x_i,y_i $ は整数

### Sample Explanation 1

$ S $ として三角形（をなす点集合）が $ 4 $ つと四角形が $ 1 $ つとれます。どれもスコアは $ 2^0=1 $ となるので、答えは $ 5 $ です。

### Sample Explanation 2

スコア $ 1 $ の三角形が $ 3 $ つ、スコア $ 2 $ の三角形が$ 2 $つ、スコア $ 4 $ の三角形が $ 1 $ つあるので、答えは $ 11 $ です。

### Sample Explanation 3

$ S $ として考えられるものがないので、答えは $ 0 $ です。

## 样例 #1

### 输入

```
4
0 0
0 1
1 0
1 1```

### 输出

```
5```

## 样例 #2

### 输入

```
5
0 0
0 1
0 2
0 3
1 1```

### 输出

```
11```

## 样例 #3

### 输入

```
1
3141 2718```

### 输出

```
0```

# 题解

## 作者：C　C　A (赞：10)

$$\huge\rm [ARC082C]ConvexScore$$

$$\large\text{——}~The~~Solution~~Written~~by~~CCA~\text{——}$$

---

$$\LARGE\mathcal{Description}$$

$\quad$给定平面上 $n$ 个整点 。定义一个凸包的贡献为 $2^k$ ，其中 $k$ 为凸包边上和内部的所有点的数量（不包括顶点）。求所有凸包的贡献和对 $998244353$ 取模后的值 。

$\quad n\leqslant 200~,~\forall x,y\in [0,10^4]$

---

$$\LARGE\mathcal{Solution}$$

$\quad$观察到 $2^k$ 这种贡献的求法非常奇怪，于是考虑它的组合意义 —— 在不改变凸包的情况下对它包含的所有点选择取或不取的方案数 。

$\quad$于是答案为合法点集的个数，一个合法的点集被定义为 “可以从中间选出一个子点集，这些点构成一个包围了所有点的凸包” 。

$\quad$考虑到点一个点集不合法当且仅当所有点都共线，于是可以考虑枚举线段两端点，计算在两端点之间的线段上有多少点，记其为 $cnt$ ，则这个点对对答案的贡献即为 $2^{cnt}$ 。

$\quad$时间复杂度 $\mathcal{O}(N^3)$ 。

---

$$\LARGE\mathcal{Code}$$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 200 + 10;
const int mod = 998244353;
const int INF = 1e9;
const double eps = 1e-6;

struct Point { int x, y; }p[N];

int n, cnt, ans = 1, fac[N];

bool cmp (Point a, Point b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

double clac (int i, int j) {
    int dx = p[i].x - p[j].x, dy = p[i].y - p[j].y;
    return dx ? 1.0 * dy / dx : INF;
}

int main () {

    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p + 1, p + n + 1, cmp);

    fac[0] = 1;
    for(int i = 1; i <= n; i++)
        fac[i] = 2 * fac[i - 1] % mod;
    ans = fac[n];

    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++, cnt = 0) {
            for(int k = i + 1; k < j; k++)
                if(clac(i, j) == clac(k, j)) cnt++;
            ans = (ans - fac[cnt] + mod) % mod;
        }

    printf("%d", (ans - n - 1 + mod) % mod);

    return 0;
}
```


---

## 作者：Kewth (赞：5)


对于凸包点集 S ，其贡献为 $2^k$ ，其中 k 是该凸包包含的点数除去顶点。  
设 T 表示这 k 个点组成的集合，那么 $2^k$ 就是 T 的子集数量。

那么每个 (S, U) 二元组对答案的贡献为 1 ，其中 U 是 T 的子集。  
而事实上 (S, U) 与 S 并 U 是一一对应的，  
因为一个点集的凸包是唯一的，也就是说已知 S 并 U 可以求出唯一的 S ，进而求出唯一的 U 。  
那么答案就是合法的 S 并 U 的点集数量。

合法指的是什么？指的就是存在凸包。  
那么什么样的点集不合法呢？一个点集 X 不合法当且仅当 X 的点共线或者 |X| < 3 。

那么可以简单容斥，用满足 |X| >= 3 的 X 的数量减去不合法的 X 数量。  
也就是统计共线的点集数，n 很小，枚举两个点，它们唯一确定一条直线，  
然后再暴力统计该直线上有多少点即可，这样一个 X 会被算多次，除掉算重次数即可。

另外也可以枚举共线 X 的两个端点，然后暴力统计端点构成的线段之间有多少点，设为 k ，  
那么这两个端点对不合法点集的贡献就是 $2^k$ ，这样的好处是不会算重，更好理解。

总复杂度 $O(n^3)$ 。  
事实上统计一条直线上的点数有更优秀的做法，可以做到 $O(n^2logn)$ ，  

参考实现：

```cpp
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 205, mod = 998244353;

inline ll sq(ll x) { return x * x; }
inline bool in_line(ll x1, ll y1, ll x2, ll y2) {
	ll a = x1 * x2 + y1 * y2;
	ll b = (sq(x1) + sq(y1)) * (sq(x2) + sq(y2));
	return a >= 0 and sq(a) == b;
}

int x[maxn], y[maxn];
ll p2[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		read(x[i], y[i]);

	p2[0] = 1;
	for(int i = 1; i <= n; i ++)
		p2[i] = (p2[i - 1] << 1) % mod;

	ll ans = p2[n] - n - 1;

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < i; j ++) {
			int tot = 0;
			for(int k = 1; k <= n; k ++)
				if(k != i and k != j and
						in_line(x[i] - x[k], y[i] - y[k], x[k] - x[j], y[k] - y[j]))
					++ tot;
			ans -= p2[tot];
		}

	printf("%lld\n", (ans % mod + mod) % mod);
}
```

---

## 作者：panyf (赞：4)

一个凸包的贡献等于满足以下条件的点集数量：

1.所有点都在凸包上或凸包内部；

2.凸包的所有顶点都在点集中。

若一个点集存在凸包，那么这个点集一定在此凸包的贡献中被计算了一次。

现在只需要求出不存在凸包的点集数量。

首先特判掉空集和只有一个点的集合。

然后不存在凸包当且仅当所有点在同一条直线上。

对于每条直线维护一个 $cnt$。

枚举两个点，求出这两点所在直线的斜率和截距。通过斜率和截距就能唯一确定一条直线。

容易发现，若直线上有 $x$ 个点，则 $cnt=\dfrac{x\times (x-1)}{2}$。

有 $x$ 个点的直线上不存在凸包的点集共有 $2^x-x-1$ 个（因为要去掉空集和只有一个点的集合）。

用哈希或 map 实现，复杂度 $O(n^2)$/$O(n^2\log n)$。

注意精度，注意特判和 $y$ 轴平行的特殊情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=209,P=998244353;
int to[N*N],x[N],y[N],p[N];
using ll=long long;
map<pair<ll,ll>,int>mp;
int main(){
	int n,i,j,s;
	double k,b;
	scanf("%d",&n),p[0]=1;
	for(i=2;i<=n;++i)to[i*(i-1)/2]=i;
	for(i=1;i<=n;++i)scanf("%d%d",x+i,y+i),p[i]=p[i-1]*2%P;
	for(i=1,s=(p[n]-n-1)%P;i<n;++i)for(j=i+1;j<=n;++j){
		if(x[i]==x[j])k=1e9,b=x[i];
		else k=(y[i]-y[j])*1./(x[i]-x[j]),b=y[i]-k*x[i];
		++mp[make_pair(ll(k*1e9+0.5),ll(b*1e9+0.5))];
	}
	for(auto o:mp)i=to[o.second],s=(s-p[i]+i+1)%P;
	printf("%d",(s+P)%P);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

遇到钦定凸包的题，可以尝试极角排序。

先极角排序出所有的边。

一个凸包的贡献是内部点的个数（不含顶点）。考虑将凸包剖分成三角形。设 $cnt3_{i,j,k}$ 表示以 $i,j,k$ 三点为顶点的三角形内部（含边上，不含顶点）包含的点数，$cnt2_{i,j}$ 表示以 $i,j$ 两点为顶点的边上包含的点数。

考虑 $dp_{i,j}$，表示起点为 $i$，上一个点为 $j$ 的所有凸包权值之和。转移时枚举 $l$，$dp_{i,j}\times 2^{cnt3_{i,j,l}-cnt2_{i,j}}\to dp_{i,l}$（三角形相邻的边会被多次计算，要扣减）。同时，按顺序对于每一条边，设 dp 初值 $dp_{u,v}=2^{cnt2_{u,v}}$，其中 $u,v$ 为极角排序后目前考虑到的边。

最后答案就是 $\sum_{i=1}^ndp_{i,i}$。

总复杂度 $O(n^4)$。瓶颈在于计算 $cnt3_{i,j,k}$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
const int mod=998244353;
struct line{
	int x,y,a,b;
	double ang;
}c[40005],d[205][205];
int mul(line p,line q){
	return p.x*q.y-p.y*q.x;
}
bool cmp(line p,line q){
	return p.ang<q.ang;
}
int cnt[205][205][205],X[205],Y[205];
int cntseg[205][205];
int dp[205][205],f[205][205],pw[205];
int ord[205][205];
signed main(){
	int n; cin>>n; for(int i=1;i<=n;i++) cin>>X[i]>>Y[i];
	pw[0]=1; for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
	int m=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			m++;
			c[m].a=i,c[m].b=j,c[m].x=X[j]-X[i],c[m].y=Y[j]-Y[i]; 
			c[m].ang=atan2(c[m].y,c[m].x);
			d[i][j].x=c[m].x;
			d[i][j].y=c[m].y;
		}
	}
	sort(c+1,c+m+1,cmp);
	for(int i=1;i<=m;i++) ord[c[i].a][c[i].b]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				if(i==j||j==k||k==i) continue;
				if(ord[i][j]>ord[j][k]||ord[j][k]>ord[k][i]) continue;
				for(int p=1;p<=n;p++){
					if(p==i||p==j||p==k) continue;
					if(mul(d[p][j],d[i][j])>=0&&mul(d[p][k],d[j][k])>=0&&mul(d[p][i],d[k][i])>=0) cnt[i][j][k]++;
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			for(int k=1;k<=n;k++){
				if(k==i||k==j) continue;
				if(mul(d[k][j],d[i][j])==0&&(min(X[i],X[j])<=X[k])&&(max(X[i],X[j])>=X[k])&&(min(Y[i],Y[j])<=Y[k])&&(max(Y[i],Y[j])>=Y[k])) cntseg[i][j]++;
			}
			if(i<j) (ans+=mod-pw[cntseg[i][j]])%=mod;
		}
	}
	for(int i=1;i<=m;i++){
		int j=i;
		while(j!=m&&c[i].ang==c[j+1].ang) j++;
		for(int k=i;k<=j;k++){
			for(int l=1;l<=n;l++){
				if(l==c[k].a) continue;
				(f[l][c[k].b]+=dp[l][c[k].a]*pw[max(0ll,cnt[l][c[k].a][c[k].b]-cntseg[l][c[k].a])])%=mod;
			}
			(f[c[k].a][c[k].b]+=pw[cntseg[c[k].a][c[k].b]])%=mod;
		}
		for(int k=i;k<=j;k++){
			for(int l=1;l<=n;l++){
				(dp[l][c[k].b]+=f[l][c[k].b])%=mod;
				f[l][c[k].b]=0;
			}
		}
		i=j;
	}
	for(int i=1;i<=n;i++) (ans+=dp[i][i])%=mod;
	cout<<ans;
	return 0;
}
```

---

