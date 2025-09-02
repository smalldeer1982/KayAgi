# [ABC173F] Intervals on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc173/tasks/abc173_f

$ N $ 頂点 $ N-1 $ 辺から成る木があり、頂点には $ 1,\ 2,\cdots,\ N $ の番号が、辺には $ 1,\ 2,\ \cdots,\ N-1 $ の番号がついています。辺 $ i $ は頂点 $ u_i,\ v_i $ を繋いでいます。

整数 $ 1\ \leq\ L\ \leq\ R\ \leq\ N $ に対して関数 $ f(L,\ R) $ を次のように定義します。

- $ S $ を番号が $ L $ 以上 $ R $ 以下の頂点から成る集合とする。頂点集合 $ S $ と、両端が $ S $ に属する辺のみから成るような部分グラフの連結成分の個数を $ f(L,\ R) $ で表す。

$ \sum_{L=1}^{N}\ \sum_{R=L}^{N}\ f(L,\ R) $ を計算してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ u_i,\ v_i\ \leq\ N $
- 与えられるグラフは木である
- 入力は全て整数である

### Sample Explanation 1

考えられる $ L,\ R $ の組み合わせは以下の $ 6 $ 通りがあります。 - $ L\ =\ 1,\ R\ =\ 1 $ のとき、$ S\ =\ \{1\} $ であり、連結成分の個数は $ 1 $ です。 - $ L\ =\ 1,\ R\ =\ 2 $ のとき、$ S\ =\ \{1,\ 2\} $ であり、連結成分の個数は $ 2 $ です。 - $ L\ =\ 1,\ R\ =\ 3 $ のとき、$ S\ =\ \{1,\ 2,\ 3\} $ であり、辺 $ 1,\ 2 $ は両端が $ S $ に含まれるので、連結成分の個数は $ 1 $ です。 - $ L\ =\ 2,\ R\ =\ 2 $ のとき、$ S\ =\ \{2\} $ であり、連結成分の個数は $ 1 $ です。 - $ L\ =\ 2,\ R\ =\ 3 $ のとき、$ S\ =\ \{2,\ 3\} $ であり、辺 $ 2 $ は両端が $ S $ に含まれるので、連結成分の個数は $ 1 $ です。 - $ L\ =\ 3,\ R\ =\ 3 $ のとき、$ S\ =\ \{3\} $ であり、連結成分の個数は $ 1 $ です。 これらの和は $ 7 $ です。

## 样例 #1

### 输入

```
3
1 3
2 3```

### 输出

```
7```

## 样例 #2

### 输入

```
2
1 2```

### 输出

```
3```

## 样例 #3

### 输入

```
10
5 3
5 7
8 9
1 9
9 10
8 4
7 4
6 10
7 2```

### 输出

```
113```

# 题解

## 作者：Zhao_daodao (赞：4)

# Intervals on Tree

考虑点边容斥。

因为初始是一棵树，所以最后构成的一定是若干棵子树。

每一个子树中，点的数量都是边的数量加 `1`。

所以连通块数量就是点的数量减边的数量。

## 点的数量

对于区间 $[l,r]$，此时一共有 $(r-l+1)$ 个点。

所以点的数量之和：
$$
\sum_{l=1}^{n}\sum_{r=l}^{n}(r-l+1)\\
=\sum_{l=1}^{n}(1+2+\cdots+(n-l+1))\\
=\sum_{i=1}^{n}i(n-i+1)
$$
从第二行推导到第三行是因为考虑 `1` 在 $l\in[1,n]$ 中被计算，`2` 在 $l\in[1,n-1]$ 中被计算，以此类推。

## 边的数量

如果有一条边 $(u,v)$，不妨假设 $u<v$。

那么这一条边被连上等价于当前区间 $[l,r]$ 满足 $l\le u$ 且 $v\le r$。

这样满足条件的区间一共有 $u(n-v+1)$ 个。

---

所以最后的答案：
$$
Ans=\sum_{i=1}^{n}i(n-i+1)-\sum_{(u,v)\in E}u(n-v+1)
$$
其中假设 $u<v$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e6+5;
int n,ans;
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		ans+=i*(n-i+1);
	}
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		if(u>v)swap(u,v);
		ans-=u*(n-v+1);
	}
	cout<<ans<<"\n";
}
```

---

## 作者：Expert_Dream (赞：2)

史诗水 F。一眼秒了。

考虑到所有的 $f(l,r)$ 有 $n^2$ 种，肯定不能单独计算，一定是有什么性质然后计算出来。

很容易发现，在一棵树上，每删掉一条边连通块加一。

于是考虑从这里入手。

先计算出没有任何一条边的 $\sum f(l,r)$。

很容易得出，即 $\sum_{i=1}^n \dfrac{i \times (i+1)}{2}$。

对于每条边如果这一条边会产生贡献，必定是在 $l \le u$ 且 $v \le r$ 的边。所以答案需要减去 $l \times (n-r+1)$。

```cpp
cin>>n;
For(i,1,n) ans+=(1+i)*i/2;
For(i,1,n-1){int x,y;cin>>x>>y;if(x>y) swap(x,y);ans -= (x) * (n-y+1);}
cout<<ans;
```

---

## 作者：toolong114514 (赞：2)

# [ABC173F] Intervals on Tree 题解
这题在 GZFLS 的一场模拟赛中当 T1，但是赛事被降智了，没写出正解。
## 题目大意
[传送门](https://www.luogu.com.cn/problem/AT_abc173_f)。
## 解题思路
### 部分分
有一种 $O(n^3)$ 的暴力，直接把每个 $f(L,R)$ 求出来即可。

~~虽然我知道 AT 的比赛没有部分分，但是国内 OI 系列赛事还是有的。在想不到正解的情况下，对部分分的研究仍然重要。~~
### 正解
考虑从贡献的角度推导。

我们先假定所有的点都不联通，再往里面连边。那么，每连一条边，都会给某些 $f(L,R)$ 以 $-1$ 的贡献。

容易证明，每次新连的的边，都是连接两个属于不同连通块的点。

如果新连的边连接了两个属于相同连通块的点，那么就会有两条边完全不同的路径去连接它们，也就是产生了一个环，与题面中“给定一颗 $n$ 个点的树”矛盾，所以不存在这种情况。

我们只需要确定每次连边会给哪些 $f(L,R)$ 贡献，就可以计算 $\sum_{L=1}^{N}\ \sum_{R=L}^{N}\ f(L,R) $ 了。

假设每次连的边的两个端点为 $u,v(u<v)$。

如果边 $(u,v)$ 能贡献一个 $f(l,r)(l\le r)$，那么 $u$ 和 $v$ 一定会被 $[l,r]$ 包括在其中，否则不会影响连通性。

即 $\forall$ 能被边 $(u,v)$ 贡献的 $f(l,r)(l\le r)$，$l \in [1,u]$ 且 $r\in [v,n]$。

这些 $f(l,r)$ 的数量可以通过[乘法原理](https://baike.baidu.com/item/%E4%B9%98%E6%B3%95%E5%8E%9F%E7%90%86/7538447?fr=ge_ala) $O(1)$ 地计算出来。

每输入一个边，就算一次贡献，最后让所有区间点的数量减去总的贡献即可。

上述算法的时间复杂度为 $O(n)$，可以通过本题。

~~教练表示：不知道你们怎么想到这种做法的……~~
## 参考代码
```cpp
#include<iostream>
using namespace std;
#define int long long
int n,ans;
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		ans+=(n-i+1)*(n-i+2)/2;
	}
	//cout<<ans<<endl;
	for(int i=1;i<n;i++){
		int p1,p2;
		cin>>p1>>p2;
		if(p1>p2) swap(p1,p2);
		ans-=p1*(n-p2+1);
	}
	cout<<ans;
	return 0;
}
```
[此代码可以通过 AT 的评测。](https://www.luogu.com.cn/record/159409917)

Written by [toolong114514](https://www.luogu.com.cn/user/477821) on 2024/5/19.

---

## 作者：cppcppcpp3 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc173_f)。

## Solution

（the method from $\operatorname{yinhee}$，拜谢）

选定 $1$ 为根节点，我们称连通块 $i$ 中深度最小的点为它的根 $rt_i$，那么每个 $rt_i$ 就代表了一个连通块。

所以现在考虑计算每个点在多少个区间做出了 $1$ 的贡献。

我们发现，点 $u$ 可以做出贡献当且仅当 $u \in [l,r]$ 且 $fa \notin [l,r]$（如果 $fa$ 在区间内，连通块的根将会是 $fa$ 或其祖先）。分两种情况讨论：

- $u>fa$，则左端点 $L \in [fa+1,u]$，右端点 $R \in [u,n]$，贡献为 $(u-fa)(n-u+1)$。

- $u<fa$，则左端点 $L \in [1,u]$，右端点 $R \in [u,fa-1]$，贡献为 $u \times (fa-u)$。

此外，点 $1$ 的贡献为 $n$ （左端点只能为 $1$）。

$\operatorname{dfs}$ 一次即可。

```cpp
#include<bits/stdc++.h>
#define il inline
#define int long long
using namespace std;
const int N=2e5+5;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,cnt,ans,head[N];

struct edge{
	int to,nxt;
}e[N<<1];

il void add(int u,int v){
	e[++cnt]=edge{v,head[u]},head[u]=cnt;
}

void dfs(int u,int fa){
	if(u^1){
		if(u<fa) ans+=(fa-u)*u;	
		else ans+=(u-fa)*(n-u+1);
	}else ans+=n;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
}

main(){
	n=wrd();
	for(int i=1;i<n;++i){
		int u=wrd(),v=wrd();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	return printf("%lld",ans),0;
}
```

---

## 作者：zixiangming (赞：2)

个人认为这种题属于那种开题不会做，题解一眼切那种。

$f(l,r)$ 的定义是 $[l,r]$ 中点组成的一张图，又因为原图是一棵树，所以这张图一定是**森林**。

设点数为 $N$，边数为 $E$，连通块数 $G$

那么就有这样一个性质：$N = E + G$

证明很简单，当这个图是一棵树时，$E = N - 1$，$G = 1$

每当我断开一条边时，边的两边会分开，一个连通块变成两个。

所以边数减一时块数加一，右边等式恒为 $N$。

证毕。

那么求一个森林的块数就可以直接用 $N - E$ 来计算。

暴力枚举左右端点维护的复杂度肯定是 $O(n^2 \alpha(n))$

采用区间题的惯用套路从左往右扫，加入新的点 $r$ 同时更新左端点为 $[1,r]$ 的所有区间。

那么每次更新在点数上的贡献是加上 $ \sum_{i=1}^{r} i $，枚举 $r$ 所有的边，另一个端点 $x$ 属于 $[1,r]$ 时，所有左端点为 $[1,x]$ 的区间都会多出一条边，在答案中的贡献是减去 $x$。

而当每次右端点扩张时之前存在的边一定会再次产生贡献，所以维护一个 $k$，每次答案减去一条边贡献的 $x$ 时就在 $k$ 上加上 $x$，每次扩张时减去 $k$ 即可。

结束。

```cpp
#define abhwolxq bailan
#define WWW signed

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define M 200005
#define ll long long
#define fre(x) freopen(#x ".in", "r", stdin), freopen(#x ".out", "w", stdout)
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define dwn(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
using namespace std;
namespace rushB {
    const int bif = 1 << 22; char buf[bif], *p1, *p2; int wrt[20], TP;
    inline int Max(int a, int b) { return a > b ? a : b; } inline int Min(int a, int b) { return a < b ? a : b; } inline void Swap(int &a, int &b) { int tmp = a; a = b, b = tmp; }
    inline char gc() { if (p1 == p2) { p2 = (p1 = buf) + fread(buf, 1, bif, stdin); if (p1 == p2) return EOF; } return *p1++; }
    inline int read() { int x = 0; bool f = false; char c; while(!isdigit(c = gc())) if (c == '-') f = true; do { x = (x << 1) + (x << 3) + (c ^ 48);}while(isdigit(c = gc())); if (f) return -x; return x; }
    inline void print(ll x, bool f) { if (x < 0) putchar('-'), x = -x; do { wrt[++TP] = x % 10, x /= 10; }while(x); while(TP) putchar(wrt[TP--] | 48); if (f) putchar('\n'); else putchar(' '); }
    inline ll qbow(ll a, ll b, ll p) { ll res = 1; while(b) { if (b & 1) res = res * a % p; a = a * a % p; b >>= 1; } return res; }
} using namespace rushB;
int n; ll res, k;
struct edge { int v, next; }e[M << 1];
int head[M], tot = 1;
void add(int u, int v) { e[tot].v = v, e[tot].next = head[u], head[u] = tot++; }
inline ll sum(ll x) { return x * (x + 1) / 2; }
WWW main() {
    n = read();
    rep(i, 2, n) { int u = read(), v = read(); add(u, v), add(v, u); }
    rep(x, 1, n) {
        res += sum(x) - k;
        for (int i = head[x]; i; i = e[i].next) {
            int v = e[i].v;
            if (v > x) continue;
            res -= v; k += v;
        }
    }
    print(res, 0);
    return 0;
}

```


---

## 作者：Genius_Star (赞：1)

### 思路：

~~第一次看成图了，想半天 LCT……~~

考虑先算点的贡献，然后再减去边的贡献。

点为：

$$\sum_{i=1}^n i \times (n-i+1)  = \frac{n(n+1)^2}{2} - \frac{n(n+1)(2n+1)}{6}$$

对于一条边 $(u,v)$，当没有加入这条边时两点肯定不在一个连通，则加入之后肯定会清掉一个联通块的贡献，为：

$$u \times (n-v+1)$$

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=2e5+10;
mt19937 R(time(0));
inline ll Rand(ll l,ll r){
	if(l==r)
	  return l;
	return R()%(r-l+1)+l;
}
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,u,v;
ll ans;
int main(){
	n=read();
	ans=n*(n+1)*(n+1)/2-n*(n+1)*(2*n+1)/6;
	for(int i=1;i<n;i++){
		u=read(),v=read();
		if(u>v)
		  swap(u,v);
		ans-=u*(n-v+1);
	}
	write(ans);
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

# [ABC173F] Intervals on Tree

## 伪代码

```C++
for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans+=query(i,j);//返回点i~j构成的子图中的连通块个数
		}
	}
```


## 思路 

猛然发现思路和 `_maojun_` 大佬差不多

既然是求所有区间的答案之和，那么我们就不要考虑如何快速求出区间 $[l,r]$ 的答案（即不要把本题当作多次询问的题目来做），而是要一步计算出所有区间的答案和。

我们考虑一下的思路：先考虑没有边的情况，再慢慢地把边加入进来，考虑每一条边的负贡献。

**点**

首先，对于点 $i$（我们假设点的编号为 $1\sim n$），在没有任何边的情况下，每个点就是一个连通块。那么只要区间 $[l,r]$ 包含了这个点，这个点就能作出 $1$ 的贡献。

已知包含点 $i$ 的区间满足 $l≤i,r≥i$，那么 $l$ 有 $i$ 种取值，$r$ 有 $n-i+1$ 种取值，组合一下就是包含 $i$ 的区间 $[l,r]$ 有 $i\times(n-i+1)$ 种。

那么在没有连边的情况下，所有点的贡献之和为 $\sum\limits_{i=1}^n [i\times(n-i+1)] $。

**边**

现在我们来考虑边的负贡献。

假设我们现在有一条边 $u-v\ (u<v)$，那么它会在某些情况下使得原本是两个不同的连通块的 $u,v$ 变成一个连通块。很显然，“某些情况”指的是区间 $[l,r]$ 即包含了 $u$ 又包含了 $v$ 的情况。

满足这个要求的区间的数量很明显是 $l≤u,r≥v$，即 $u\times (n-v+1)$ 个。

那么对于所有边 $u_i-v_i$，我们所有负贡献为 $\sum\limits_{i=1}^{n-1} [u_i\times (n-v_i+1)$]。

所以本题的答案可以直接计算得出，为 $\sum\limits_{i=1}^n [i\times(n-i+1)]-\sum\limits_{i=1}^{n-1}[ u_i\times (n-v_i+1)]$。

## 代码

```C++
/*////////ACACACACACACAC///////////
	   . Coding by Ntsc .
	   . ToFind Chargcy .
	   . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=2e5+5;
const int M=1e3;
const int MOD=1e9+7;
const int INF=1e9;
//变量
int n,m,a,b,c,x[N],y[N],ans;
char num[N];

signed main() {
    cin>>n;
	for(int i=1;i<=n;i++){
		ans+=i*(n-i+1);
	}
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		if(u>v)swap(u,v);
		ans-=u*(n-v+1);
	}
	cout<<ans;
	return 0;
}
```






---

## 作者：V1mnkE (赞：1)

提供一种跟现有题解不一样的做法。

记与一点 $u$ 有边相连的点集为 ${S_u}$。

想一下怎么计算 $\sum_{i=k}^{n}f(k,i)$ 的值，可以把这个过程看成往一个图里加点，然后考虑新加入一个点 $u$ 的贡献，手画一下图可以发现加入后增加的连通块数量为 $1-|S_u\cap [k,u]|$，这是显然的。

然后我们就得到了一个 $O(n^2)$ 的解法：预处理 $1-|S_u\cap [1,u]|$，记为 $f_u$，然后从 $1$ 到 $n$ 遍历，计算完之后要将当前点删除，可以 $O(|S_u|)$ 更新 $f_u$。

```cpp
for(int i=1;i<=n;i++){
	int d=1;
	for(int j=i+1;j<=n;j++){
		d+=(1-f[j]);
		ans+=d;
	}
	for(int j=head[i];j;j=e[j].nxt){
		int v=e[j].to;
		if(v>i)f[v]--;
	}
}
```


接下来考虑优化，把枚举到 $i$ 时的 $d$ 列几项出来：
$$d=1$$
$$d=d+1-f_{i+1}$$
$$d=d+1-f_{i+1}+1-f_{i+2}$$
$$d=d+1-f_{i+1}+1-f_{i+2}+1-f_{i+3}$$
发现很有规律，$\sum d=\sum_{j=1}^{n-i+1} j-\sum_{j=i+1}^{n}f_j\times (n-j+1)$

然后减号左边的可以 $O(1)$ 算，右边的可以预处理初始和之后每次 $O(|S_u|)$ 更新，具体见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int ans,n,head[maxn],cnt,f[maxn],x;
struct edge{
	int to,nxt;
}e[maxn<<2];
void addedge(int u,int v){
	e[++cnt]={v,head[u]};
	head[u]=cnt;
}
signed main(){
	cin>>n;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		if(u<v)f[v]++;
		else f[u]++;
		addedge(u,v);
		addedge(v,u);
	}
	for(int i=1;i<n;i++)x+=(n-i)*f[i+1];
	for(int i=1;i<=n;i++){
		ans+=(n-i+1)*(n-i+2)/2-x;
		for(int j=head[i];j;j=e[j].nxt){
			int v=e[j].to;
			if(v>i)f[v]--,x-=(n-v+1);
		}
		x-=(n-i)*f[i+1];
	}
	cout<<ans;
}
```

---

## 作者：zzzyyyyhhhhh (赞：0)

这道题要求我们计算一棵树中所有可能的区间 $[l,r]$ 内形成的连通块的数量。每个区间由树上的连续节点构成。题目的核心在于对区间 $f(l,r)$ 连通块数量的计算。

可以分解问题为两个部分：
1. 计算不包含任何边的连通块的总数。
2. 减去会形成额外连通块的边的贡献。

由于是树，每条边只连接两个顶点，所以如果一个区间 $[l,r]$ 内不包含这条边，则该边会增加一个连通块。我们需要逐步统计所有不连通的情况，最后求出总的连通块数。


我们可以先计算初始的连通块数。由于每个区间 $[l,r]$ 中没有边时，所有点都会形成一个独立的连通块。因此，初始的连通块总数可以通过公式求得：  
$$
\text{total\_blocks} = \sum_{i=1}^{n} i \times (n-i+1)
$$  
即每个顶点可以作为区间的起点 $l$ 和终点 $r$。

接下来，对于每一条边，如果区间 $[l,r]$ 跨过该边，就会使得两个顶点连通，我们需要减去这些由于边带来的额外连通块。具体来说，对于每条边 $(u,v)$，我们假设 $u < v$，则当 $l \leq u$ 并且 $r \geq v$ 时，这条边连通了两个点，它的贡献为 $u \times (n-v+1)$，这部分需要从总的连通块数中减去。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+100;
int n;
struct edge {
    int f,t;
} e[N];

signed main() {
    cin >> n;
    int x, y;

    // 输入边
    for(int i = 1; i < n; i++) {
        cin >> x >> y;
        e[i] = {x, y};
    }

    int ans = 0;

    // 计算初始的连通块总数
    for(int i = 1; i <= n; i++) {
        ans += i * (n - i + 1);
    }

    // 处理每条边的贡献
    for(int i = 1; i < n; i++) {
        if(e[i].f > e[i].t) swap(e[i].f, e[i].t);
        ans -= e[i].f * (n - e[i].t + 1);
    }

    cout << ans;
}
```

---

## 作者：__Cby___ (赞：0)

## 思路
拆贡献题。  
对于点不连接的贡献，假设这个点为 $u$，$u$ 在区间 $[l,r]$ 内时才会产生贡献，很明显要满足 $l\le u$ 且 $u\le r$，根据加法原理，该点贡献为 $u(r-u+1)$。  
接下来要扣去边的贡献，假设这条边是从 $u$ 连向 $v$ 的双向边，为了方便处理，我们设 $u < v$。则若要产生贡献，得有 $u$ 在区间 $[l,r]$ 内且 $v$ 也要在区间 $[l,r]$ 内，显然有 $l\le u$ 且 $v\le r$，根据加法原理，该边应减去的贡献为：$u(n-v+1)$。  
## 代码
```cpp
#include <iostream>
using namespace std;
int main() {
	long long int n;
	cin >> n;
	long  long int sum = 0;
	for (int i = 1; i <= n; i++) {
		sum += i * (n - i + 1);
	}
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		if (u > v)u ^= v ^= u ^= v;
		sum -= u * (n - v + 1);
	}
	cout << sum << endl;
	return 0;
}
```

---

