# [ARC016D] 軍艦ゲーム

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc016/tasks/arc016_4

高橋君は艦長である。  
 高橋艦長の任務は、鎮守府のある海域から最終目的地となる海域へ進軍することである。  
 高橋艦長は次の順序で行動する。

1. 航路選択

- 進軍する航路を選択する。現在の海域から異なる海域へ移動できる航路が $ 1 $ 本も存在しない場合、$ 4 $ の海域離脱を行う。
- また、現在の海域から異なる海域への航路が複数本存在する場合、何者かの陰謀によって等確率で航路が選択される。
- たとえば、鎮守府のある海域から、他の海域への航路が $ 4 $ 本存在する場合、それぞれ $ 25% $ の確率で選択されます。


4. 進軍
- 選択された航路によって、海域を移動する。

6. 戦闘
- 進軍先の海域 $ i $ には敵艦が待ち構えており、戦闘が発生する。
- 鎮守府から出港したとき、高橋艦長が率いる軍艦の体力は $ H $ であり、戦闘によって軍艦の体力は $ D_i $ だけ減少する。
- 軍艦の体力が $ 0 $ 以下になると、軍艦は沈没してしまう。
- 軍艦が沈没すると高橋艦長は失意のあまりこれ以上出撃することが出来なくなってしまうため、`絶対に沈没させてはいけない`。
- なお、鎮守府のある海域では戦闘は発生しないが、最終目的地である海域では必ず戦闘が発生する。

8. 海域離脱 or 航路選択に戻る
- 海域離脱とは、鎮守府のある海域へ戻ることを意味する。
- 海域離脱した際に、軍艦の残り体力が $ C $ であった場合、$ H-C $ だけ体力回復のために時間を消費する。
 
 上記`1`,`2`,`3`,`4`のサイクル1回につき時間を $ 1 $ だけ使う。  
- - - - - -

 海域と航路について - いま、$ N $ 個の海域と $ M $ 個の航路がある。
- これら $ M $ 個の航路は、すべて一方通行である。
 
 そのため、任意の異なる海域 $ A,B $ において、ある $ 1 $ 本の航路を利用して、海域 $ A $ から海域 $ B $ へ移動し、海域 $ B $ から海域 $ A $ へ移動することはできない。  
- - - - - -

 あなたは高橋艦長の参謀であり、高橋艦長が消費する時間を最小となるよう行動した場合、最終目的地における戦闘で生存するまでに経過する時間の期待値を求めることが仕事である。  
 どのようにしても高橋艦長が任務を完遂できない場合は`-1`と出力せよ。  
 ただし、出力する期待値が $ 10^6 $ より大きくなる入力は与えられない。 入力は以下の形式で標準入力から与えられる。 > $ N $ $ M $ $ H $ $ f_1 $ $ t_1 $ $ f_2 $ $ t_2 $ : $ f_M $ $ t_M $ $ D_1 $ $ D_2 $ : $ D_N $

1. $ 1 $ 行目は、海域数を表す整数 $ N\ (2≦N≦100) $、航路数を表す整数 $ M\ (0≦M≦N\ *\ (N\ -\ 1)\ /\ 2) $、出港時の艦隊の体力を表す整数 $ H\ (1≦H≦100) $ が半角空白区切りで与えられる。

- 鎮守府のある海域は $ 1 $ で、最終目的地である海域は $ N $ です。

32. $ 2 $ 行目から $ M $ 行は、 $ i $ 番目の航路を表す。移動元の海域を表す整数 $ f_i\ (1≦f_i≦N) $、移動先の海域を表す整数 $ t_i\ (1≦t_i≦N) $ が、スペース区切りで与えられる。
- $ f_i\ <\ t_i $ であることが保証されている。

34. $ 2+M $ 行目から $ N $ 行は、$ i $ 番目の海域での戦闘で受けるダメージを表す整数 $ D_i\ (0≦D_i≦100) $ が、一行で与えられる。
- $ D_1 $ の値は常に $ 0 $ である（鎮守府のある海域です）。

- 出力する期待値が $ 10^6 $ より大きくなる入力が与えられないことに留意せよ。
 
 高橋艦長が消費する時間が最小となるよう行動した場合、最終目的地における戦闘で生存するまでに経過する時間の期待値を出力せよ。  
 出力は絶対誤差あるいは相対誤差の少なくとも片方が $ 10^{-6} $ 以下であれば許容される。   
 また、どのようにしても高橋艦長が任務を完遂できない場合は`-1`と出力せよ。  
 なお、出力の最後には改行をいれること。  

- 鎮守府のある $ 1 $ から、最終目的地である $ 6 $ までは、$ 2 $ 通りの経路があります。

1. 1 -&gt; 2 -&gt; 4 -&gt; 6

- このルートが選択される確率は $ 50% $ です。
- このルートで軍艦が受けるダメージは $ 0+1+2+4=7 $ です。
- このルートで消費する時間は、サイクル $ 3 $ 回の時間のみなので、$ 3 $ です。

48. 1 -&gt; 3 -&gt; 5 -&gt; 6
- このルートが選択される確率は $ 50% $ です。
- このルートで軍艦が受けるダメージは $ 0+1+3+4=8 $ です。
- 出港時の軍艦の体力は $ 8 $ なので、このルートでは沈没してしまいます。
- 高橋艦長は、沈没を避けるため、海域 $ 3 $ の戦闘終了時に海域離脱を選択します。
- このルートで消費する時間は、サイクル $ 1 $ 回の時間 $ + $ 体力の回復にかかる時間 $ = $ $ 1+1=2 $ です。
 
 1 -&gt; 3 -&gt; 5 -&gt; 6 で `1` 度撤退してから 1-&gt; 2-&gt; 4 -&gt; 6 - $ 50% $ の確率で 1 -&gt; 3 -&gt; 5 -&gt; 6 が選択され、時間 $ 2 $ を使って鎮守府に戻る。
- その後、 $ 50% $ の確率で 1 -&gt; 2 -&gt; 4 -&gt; 6 が選択され、時間 $ 3 $ を使って最終目的地に到達する。
- つまり、$ 25% $ の確率で時間 $ 5 $ を使って最終目的地に到達。
 
 1 -&gt; 3 -&gt; 5 -&gt; 6 で `2` 度撤退してから 1-&gt; 2-&gt; 4 -&gt; 6 - $ 12.5% $ の確率で時間 $ 7 $ を使って最終目的地に到達。
 
 1 -&gt; 3 -&gt; 5 -&gt; 6 で `3` 度撤退してから 1-&gt; 2-&gt; 4 -&gt; 6 - $ 6.25% $ の確率で時間 $ 9 $ を使って最終目的地に到達。

62. 上記から、求める期待値は $ 3*0.5+5*0.25+7*0.125+...=5 $ となります。


## 样例 #1

### 输入

```
6 6 8
1 2
1 3
2 4
3 5
4 6
5 6
0
1
1
2
3
4```

### 输出

```
5.0```

## 样例 #2

### 输入

```
3 2 5
1 2
1 3
0
5
1```

### 输出

```
-1```

## 样例 #3

### 输入

```
3 2 6
1 2
1 3
0
5
1```

### 输出

```
7```

## 样例 #4

### 输入

```
9 13 4
1 2
1 3
2 4
2 5
2 7
3 5
3 6
4 7
5 8
6 8
7 8
7 9
8 9
0
1
1
1
1
1
1
1
1```

### 输出

```
36.9999999999999```

# 题解

## 作者：iMya_nlgau (赞：9)

这个二分很有意思欸

首先期望 DP，设 $f_{x,i}$ 表示在点 $x$ HP 为 $i$ 的期望，状态转移方程也很容易列出

$$
f_{x,j}=\min\{f_{1,H}+H-j,1+\mathbb{E}_{(x,y)\in E}(f_{y,j-d_y})\}
$$

边界

$$f_{x,j}=\infty\ (j\leq0)$$

$$f_{n,j}=0\ (j>0)$$


但这个是有后效性的，不过后效性只与 $f_{1,H}$ 有关，我们考虑钦定 $f_{1,H}=A$，然后直接按方程转移，最后在看算出的实际 $f_{1,H}$ 是否等于 $A$。

我们把这样计算出来的 $f_{1,H}$ 看成是 $A$ 的函数 $g(A)$，想一想就有 $g^\prime(A)\leq1$，所以就有 $[g(A)-A]^\prime\leq 0$ 他是有单调性的，可以二分出 $g(A)=A$ 的 $A$，也就是答案。

至于这个 $g^\prime(A)\leq 1$ 应该也可以感性证明，考虑按拓扑序归纳，考虑 $A$ 减小了 $\mathrm{d}A$，$f_{n,\star}$ 不会变所以它的导数是 $0\leq1$，$f_{x,j}$ 如果从 $A+H-j$ 转移来那么 $\mathrm{d}f_{x,j}=\mathrm{d}A$，如果从 $f_{y,\star}$ 转移来，那么 $\mathrm{d}f_{x,j}=\mathrm{d}f_{y,\star}\leq \mathrm{d}A$ 也是成立的，所以就证明了恒有 $\mathrm{d}f_{\star,\star}/\mathrm{d}A\leq1$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<queue>
using namespace std;

inline int read(){
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c^'0'),c=getchar();
	return x;
} 

int n,m,H,d[110];

struct Edge{ int to,next;}edge[10010];
int head[110],cnt;
inline void addedge(int u,int v){
	edge[++cnt]=(Edge){v,head[u]};
	head[u]=cnt;
}

const double eps=1e-8;
const double inf=1e12;

double A,f[110][110];
bool v[110];

void dfs(int x){
	v[x]=true;
	for(int j=1;j<=H;j++) f[x][j]=0;
	int deg=0;
	for(int i=head[x];i;i=edge[i].next){
		int y=edge[i].to;
		if(!v[y]) dfs(y);
		for(int j=1;j<=H;j++){
			if(j-d[y]<=0) f[x][j]=inf;
			else f[x][j]+=f[y][j-d[y]];
		}
		deg++;
	}
	for(int j=1;j<=H;j++){
		if(x<n){
			if(x==1&&j==H) f[x][j]=1+f[x][j]/deg;
			else 
				f[x][j]=min(A+H-j,1+f[x][j]/deg);
		} else
			f[x][j]=0;
	}
}

double calc(double mid){
	A=mid;
	memset(v,0,sizeof(v));
	dfs(1);
	if(!v[n]) return inf;
	return f[1][H];
}

int main(){
	n=read(),m=read(),H=read();
	for(int i=1;i<=m;i++){
		int f=read(),t=read();
		addedge(f,t);
	}
	for(int i=1;i<=n;i++) d[i]=read();
	
	double l=0,r=1e6+10;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(calc(mid)>mid) l=mid;
		else r=mid;
	}
	
	if(l>1e6) puts("-1");
	else printf("%.6lf\n",l);

	return 0;
}

```

---

## 作者：Locix_Elaina_Celome (赞：4)


~~这么小声，还想开軍艦！~~


# 题意

给出一张 DAG，$1$ 号点为起点，$n$ 为终点。每次等概率选择一条出边走，花费 $1$ 时间。

初始血量为 $h$，每次经过点 $i$ 会扣除 $a_i$ 点血，必须保持血量始终为正。

扣完一次血之后可以选择：继续走或回城（回到起点），设当前血量为 $c$，则回城需额外停留 $h-c$ 的时间。

求最优策略下的期望最短时间。

tips：必须保持血量始终为正，意为若当前血量小于等于某一条出边通向的点的权值，除非已经到达终点，否则必须回城。

# 题解

一眼 dp。

状态和方程是不难想的，设 $dp_{u,i}$ 为 $u$ 这个位置血量为 $i$ 要到达 $n$ 的期望步数。

则有 $dp_{u,i}=\min\{dp_{1,h}+h-i,\sum \dfrac{dp_{v,i-a_v}+1}{d_u}\}$。特别的，若 $u=n$，$dp_{u,i}=0$；若 $u\ne n$ 且 $d_u=0$，$dp_{1,h}+h-i$。
其中 $d_u$ 表示 $u$ 的出边数量。

然后就发现这里面有一个叫做 $dp_{1,h}$ 的东西不伦不类的，导致 DP 出现了环。

我们又发现这里面出现了一个叫做 $\min$ 的东西导致我们不好直接解方程。

但这里涉及环的只有 $dp_{1,h}$，所以容易想到在这里搞些科技。

于是想到先预设一个 $dp_{1,h}$ 跑 DP 再验证是否合法。

由于人菜知识少，只能想到二分 $dp_{1,h}$（实在想不到除了二分还能怎么搞~~模拟退火~~）。

感性理解单调性（楼上的大佬有证明 Orz），二分出一个 $mid$，按上面的式子将 $mid$ 作为 $dp_{1,h}$ 跑 DP，将跑出来的结果与二分的结果比较，若 $dp_{1,h} > mid$，$l=mid$，否则 $r=mid$。

DP 过程记搜或拓扑排序都可做。

注意当 $u=1$ 的时候不能与 $mid+h-i$ 取 $\min$，不然还二分个锤锤。

记得判无解。

题不卡常，多二分几次。

```cpp
using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 1005
#define M 100005
#define LL long long
#define LD long double
#define int LL
#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n,m,h;
int t[M],las[M],fir[N],num;
void add(int u,int v){t[++num]=v;las[num]=fir[u];fir[u]=num;}
int a[N];
double dp[N][N];
int d2[N],d[N];
int fl[N][N];
double check(double mid){
	for(int i=0;i<=n;i++)for(int j=0;j<=h;j++)dp[i][j]=0;
	queue<int> q;
	for(int i=1;i<=n;i++){
		d[i]=d2[i];
		if(d2[i]==0){
			q.push(i);
			for(int j=1;j<=h;j++)
				 dp[i][j]=h-j+mid;
		}
	}
	for(int i=1;i<=h;i++)dp[n][i]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=1;i<=h;i++)
			if(u!=1)dp[u][i]=Min(dp[u][i],h-i+mid);
		for(int i=fir[u];i;i=las[i]){
			for(int j=1;j<=a[u];j++)dp[t[i]][j]=h-j+mid;
			for(int j=a[u]+1;j<=h;j++)
				dp[t[i]][j]+=(dp[u][j-a[u]]+1)/d2[t[i]];
			if(!(--d[t[i]]))q.push(t[i]);
		}
	}
	return dp[1][h];
}
signed main(){
	read(n);
	read(m);
	read(h);
	for(int i=1,x,y;i<=m;i++)
		read(x),read(y),add(y,x),d2[x]++;
	for(int i=1;i<=n;i++)read(a[i]);
	double l=0,r=INF;
	for(int i=200;i;i--){
		double mid=(l+r)/2;
		double x=check(mid);
		if(Abs(x-mid)<=EPS){
			l=r=mid;
			break;
		}
		if(x>mid)l=mid;
		else r=mid;
	}
	if(l>1145141910||l<=EPS)puts("-1");
	else printf("%.17lf",l);
	return 0;
}
```

---

## 作者：123456xwd (赞：2)

设 $f_{i,j}$ 表在点 $i$ 有 $j$ 滴血，到终点的最小期望时间，则有：

$$
f_{u,i}=\min\{(\frac{1}{out_u}\sum_{(u,v)\in E}f_{v,i-D_v})+1,H-i+f_{1,H}\}
$$

我们发现这玩意有后效性，怎么办呢？

我们考虑直接把 $f_1,H$ 二分出来，显然，我们可以根据这个二分值 $mid$ 搞出来一个新的 $X=f_{1,H}$。

显然 $X\le mid$，若 $X=mid$，则证明第二部分**可能**过小，我们移动 $l$，同时将答案设为他；否则证明第二部分过大，我们移动 $r$ 即可。

dp 直接 $\mathcal{O}(n^2)$ 记忆化求解即可，注意，若到了没有出度的非结尾点，我们只能传送回去。

```c++
#include<bits/stdc++.h>
#define int long long
#define m_p make_pair
#define p_b push_back
#define pii pair<int,int>
#define db double
using namespace std;
inline int rd(){
	int x=0,f=1; char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if (ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
const int N=100+5;
const db eps=1e-9,INF=2e6;

db dp[N][N];
bool vis[N][N];
int n,m,H,D[N];
vector<int> G[N];

db dfs(int u,int i,db mid){
	if(i<=0) return INF; 
	if(u==n) return 0;
	if(G[u].size()==0) return H-i+mid;
	if(vis[u][i]) return dp[u][i];
	vis[u][i]=1;db ans=0;
	for(auto v : G[u])ans+=dfs(v,i-D[v],mid);
	ans/=(db)G[u].size(),ans+=1;
	ans=min(ans,(H-i)*1.0+mid);
	return dp[u][i]=ans;
}

bool check(db mid){
	memset(vis,0,sizeof(vis));
	db ans=dfs(1,H,mid);
	return (abs(ans-mid)<=eps);
}

signed main(){
	n=rd(),m=rd(),H=rd();
	for(int i=1;i<=m;i++){
		int u=rd(),v=rd();
		G[u].p_b(v);
	}
	for(int i=1;i<=n;i++) D[i]=rd();
	db l=0,r=1e6+10,mid,ans=1e6+10;
	while((r-l)>=eps){
		mid=(l+r)/2.0;
		if(check(mid)) l=mid,ans=mid;
		else r=mid;
	}
	if(ans>1000000) puts("-1");
	else printf("%.10lf\n",ans);
	return 0;
} 

```

---

