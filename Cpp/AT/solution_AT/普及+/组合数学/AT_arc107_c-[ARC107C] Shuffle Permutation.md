# [ARC107C] Shuffle Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc107/tasks/arc107_c

$ N\ \times\ N $ の行列と、整数 $ K $ が与えられます。この行列の $ i $ 行目、$ j $ 列目の値を $ a_{i,\ j} $ とします。この行列は、 $ 1,\ 2,\ \dots,\ N^2 $ をちょうど一つずつ要素に含みます。

sigma くんは、以下の $ 2 $ 種類の操作を、好きな順序で **好きな回数** 行えます。

- 全ての $ i $ ($ 1\ \leq\ i\ \leq\ N $) について $ a_{i,\ x}\ +\ a_{i,\ y}\ \leq\ K $ を満たす $ x,\ y(1\ \leq\ x\ <\ y\ \leq\ N) $ を選び、行列の $ x,\ y $ 列目をswapする。
- 全ての $ i $ ($ 1\ \leq\ i\ \leq\ N $) について $ a_{x,\ i}\ +\ a_{y,\ i}\ \leq\ K $ を満たす $ x,\ y(1\ \leq\ x\ <\ y\ \leq\ N) $ を選び、行列の $ x,\ y $ 行目をswapする。

最終的に得られる行列は何種類存在するでしょうか？ $ \bmod\ 998244353 $ で答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ K\ \leq\ 2\ \times\ N^2 $
- $ a_{i,\ j} $ は $ 1,\ 2,\ \dots,\ N^2 $ の並び替え
- 入力される数は全て整数である。

### Sample Explanation 1

例えば $ x\ =\ 1,\ y\ =\ 2 $ として列ベクトルを swap でき、以下のようになります。 ``` 2 3 7 8 4 9 6 1 5 ``` その後更に $ x\ =\ 1,\ y\ =\ 3 $ として行ベクトルを swap でき、以下のようになります。 ``` 6 1 5 8 4 9 2 3 7 ```

## 样例 #1

### 输入

```
3 13
3 2 7
4 8 9
1 6 5```

### 输出

```
12```

## 样例 #2

### 输入

```
10 165
82 94 21 65 28 22 61 80 81 79
93 35 59 85 96 1 78 72 43 5
12 15 97 49 69 53 18 73 6 58
60 14 23 19 44 99 64 17 29 67
24 39 56 92 88 7 48 75 36 91
74 16 26 10 40 63 45 76 86 3
9 66 42 84 38 51 25 2 33 41
87 54 57 62 47 31 68 11 83 8
46 27 55 70 52 98 20 77 89 34
32 71 30 50 90 4 37 95 13 100```

### 输出

```
348179577```

# 题解

## 作者：MinimumSpanningTree (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_arc107_c)

观察发现，两种操作是不会互相影响的。做了一次行交换之后，再做列交换时两列的任何对应数的和不变。所以我们考虑分别计算行交换和列交换的方案数再相乘。

下面以行为例讲解，列是同理的。可以二重循环枚举可以交换的两行，再一重循环判断是否可以交换。我们知道，当第 $i$ 行和第 $j$ 行可以交换，第 $j$ 行和第 $k$ 行可以交换时，第 $i$ 行和第 $k$ 行也可以交换。为了保证答案不重不漏，可以把一些所有能够互通的的行放到一个集合里，于是我们可以使用并查集来维护，最后计算方案数。

时间复杂度 $O(n^3)$，记得做完行之后清空数组再计算列。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=510;
const int MOD=998244353;
int n,m,a[N][N],fa[N],cnt[N];
ll fac[N]={0,1},ans=1;
bool check_hang(int x,int y)
{
    for(int i=1;i<=n;i++)
    {
        if(a[x][i]+a[y][i]>m) return false;
    }
    return true;
}
bool check_lie(int x,int y)
{
    for(int i=1;i<=n;i++)
    {
        if(a[i][x]+a[i][y]>m) return false;
    }
    return true;
}
int set_find(int x)
{
	return x==fa[x]?x:fa[x]=set_find(fa[x]);
}
void set_merge(int x,int y)
{
	int gx=set_find(x),gy=set_find(y);
	if(gx!=gy) fa[gx]=gy;
}
int main()
{
	memset(a,0x3f,sizeof a);
	scanf("%d%d",&n,&m);
	for(int i=2;i<=500;i++) fac[i]=(fac[i-1]*i)%MOD;
    for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	}
	for(int i=1;i<=n;i++)
	{
        for(int j=i+1;j<=n;j++)
		{
            if(check_hang(i,j)) set_merge(i,j);
        }
    }
    for(int i=1;i<=n;i++) cnt[set_find(i)]++;
    for(int i=1;i<=n;i++)
	{
		if(cnt[i]) ans=(ans*fac[cnt[i]])%MOD;
	}
	for(int i=1;i<=n;i++) fa[i]=i,cnt[i]=0;
	for(int i=1;i<=n;i++)
	{
        for(int j=i+1;j<=n;j++)
		{
            if(check_lie(i,j)) set_merge(i,j);
        }
    }
    for(int i=1;i<=n;i++) cnt[set_find(i)]++;
    for(int i=1;i<=n;i++)
	{
		if(cnt[i]) ans=(ans*fac[cnt[i]])%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/article/ze1lga1n) $|$ 
[题目传送门](/problem/AT_arc107_c) $|$ 
[我的其他题解](/user/523641#article.2)

------------

### ${\color{#00CD00}\text{思路}}$

显然，如果两行可以交换，那么无论如何交换列，这两行都可以交换。也就是说，**行的操作不影响列的操作，列的操作也不影响行的操作**。

那么我们就只考虑行的操作，列的操作同理。

稍微思考一下可以发现，如果 $a,b$ 可以交换且 $b,c$ 可以交换，那么相当于 $a,c$ 也可以交换。交换方式是这样的：$[a,b,c]\xrightarrow{\text{交换}\ a,b}[b,a,c]\xrightarrow{\text{交换}\ b,c}[c,b,a]$。

注意到 $n\le 50$，我们可以先 $O(n^3)$ 预处理哪些行是可以交换的，同时将它们在一个**并查集**中合并。由上面的结论可得，在并查集中连通的行两两都可以交换。那么设这一个连通块的大小为 $s$，对答案的贡献就是 $s!$。最终的答案就是所有连通块的贡献的乘积。

------------

### ${\color{#00CD00}\text{代码}}$

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i=a; i<=b; i++)
using namespace std;
const int N = 5e2 + 5, Mod = 998244353;
long long n, m, ans = 1;
int a[N][N], js1[N], js2[N];
struct DSU{ //并查集 
	int f[N]; DSU(int n){rep(i, 1, n) f[i] = i;}
	void merge(int x, int y){f[find(x)] = find(y);}
	int find(int x){return f[x] == x ? x : f[x] = find(f[x]);}
};
int fac[N];
void init(int n){ //预处理阶乘 
	fac[0] = 1;
	rep(i, 1, n) fac[i] = 1ll * fac[i-1] * i % Mod;
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n >> m; init(n);
	rep(i, 1, n) rep(j, 1, n) cin >> a[i][j];
	DSU sr(n), sc(n); //开 2 个并查集，分别处理行和列 
	rep(i, 1, n) rep(j, i+1, n){ //O(n^3) 预处理哪些行/列可以交换 
		bool flag1 = 1, flag2 = 1;
		rep(k, 1, n){
			if(a[i][k] + a[j][k] > m) flag1 = 0;
			if(a[k][i] + a[k][j] > m) flag2 = 0;
		}
		if(flag1) sr.merge(i, j); //如果可以交换，在并查集中合并 
		if(flag2) sc.merge(i, j);
	}
	rep(i, 1, n) js1[sr.find(i)]++, js2[sc.find(i)]++; //统计每个连通块的大小 
	rep(i, 1, n){ //统计答案 
		ans = ans * fac[js1[i]] % Mod;
		ans = ans * fac[js2[i]] % Mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

上来先看题：又是一道 $998244353$……

不过再一看数据范围：$n\le50$，~~这不是标准乱搞么~~。我们仔细观察这个题，首先我们知道，**如果有 $\boldsymbol x$ 行（列）可以交换，那么它们会给答案有 $\boldsymbol{x!}$ 的贡献**。我们又发现，行的方案数和列的方案数是互不影响的。所以这题看似 $998244353$，实际上就是很简单的计数。

接下来看怎么统计。我们重点是要知道**能相互交换的行（列）数**。既然数据这么水，对于任意两行（列）能否交换我们直接暴力 $O(n^3)$ 求即可。我们发现若 $a,b$ 两行能交换，$b,c$ 两行能交换，那么 $a,b,c$ 三行都能交换。所以就很自然地并查集处理。然后这题就做完了。

```cpp
#define int long long
using namespace std;

constexpr int MAXN = 55, MOD = 998244353;
int n, K, a[MAXN][MAXN];
int ans = 1, fac[MAXN];
int f[MAXN], cnt[MAXN], fx, fy;

void init() {
	fac[0] = 1;
	for (int i = 1; i < MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
}

int find(int x) {
	if (f[x] != x) f[x] = find(f[x]);
	return f[x];
}

signed main() {
	init();
	scanf("%lld%lld", &n, &K);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%lld", &a[i][j]);
	iota(f + 1, f + n + 1, 1);
	fill(cnt + 1, cnt + n + 1, 1);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			for (int x = 1; x <= n; x++) if (a[i][x] + a[j][x] > K) goto fu;
			fx = find(i), fy = find(j);
			if (fx != fy) f[fy] = fx, cnt[fx] += cnt[fy];
			fu:;
		}
	for (int i = 1; i <= n; i++) if (f[i] == i) ans = ans * fac[cnt[i]] % MOD;
	iota(f + 1, f + n + 1, 1);
	fill(cnt + 1, cnt + n + 1, 1);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			for (int x = 1; x <= n; x++) if (a[x][i] + a[x][j] > K) goto gu;
			fx = find(i), fy = find(j);
			if (fx != fy) f[fy] = fx, cnt[fx] += cnt[fy];
			gu:;
		}
	for (int i = 1; i <= n; i++) if (f[i] == i) ans = ans * fac[cnt[i]] % MOD;
	cout << ans << '\n';

	return 0;
}
```

---

## 作者：YBaggio (赞：0)

### 题意
看题面翻译，十分清楚。

[传送门](https://www.luogu.com.cn/problem/AT_arc107_c)
## 1.分析
首先我们看到这两个交换的操作，分别定义为操作1和操作2。我们观察可以发现无论进行什么操作，原来同一列的元素操作完之后还是同一列，也就是说，对**行的操作不会影响列的操作的进行**，同理对**列的操作不会影响行的操作的进行**。

转眼一看数据范围：$n \le 50$ 基本可以确定是~~乱搞了~~。
## 2.思路
得到以上的结论后，我们可以将行与列分开考虑，即只操作行的答案乘上只操作列的答案就是最终的答案。
#### 如何求只操作行（列）的答案呢？
我们可以暴力 $O(n^2)$ 枚举任意2行，然后暴力判断它能否互相交换。

现在我们可以发现一个事情：**如果第A行和B行可以互相交换，B行和C行可以互相交换，则A行和C行显然也可以间接互相交换**。于是我们设若干个行构成的集合（满足集合中每个行都可以互相直接或间接交换）为一个块。那么一个块中的行由于都可以互相交换，所以共有“数量的阶乘的阶乘”种排列方式。最后将所有块的排列方式乘起来就是只操作行的答案，我们。

用同样的方式我们可以求出只操作列的答案。
## 3.代码（有注释）
```cpp
#include<bits/stdc++.h>
#define Mod 998244353
using namespace std;
const int maxn=55;
int n,k,a[maxn][maxn],f[maxn],siz[maxn];
long long ans=1,jc[maxn];
int find(int x){
    if(x==f[x])return x;
    else return f[x]=find(f[x]);
}
bool ck1(int x,int y){//检查两行是否可以互相直接交换
    for(int i=1;i<=n;i++)
        if(a[x][i]+a[y][i]>k)
            return false;
    return true;
}
bool ck2(int x,int y){//检查两列是否可以互相直接交换
    for(int i=1;i<=n;i++)
        if(a[i][x]+a[i][y]>k)
            return false;
    return true;
}
void init(){
    jc[1]=1;
    memset(siz,0,sizeof(siz));
    for(int i=2;i<=maxn;i++)jc[i]=(jc[i-1]*i)%Mod;//预处理阶乘
    for(int i=1;i<=n;i++)f[i]=i;
    return;
}
void solve(){
    init();
    for(int i=1;i<=n;i++){//求行的块
        for(int j=i+1;j<=n;j++){
            if(ck1(i,j)){
//如果一个行与块中的任意一个行可以互相交换那么它必然可以和块中的任
//意行交换
                int fx=find(i),fy=find(j);
                f[fy]=fx;
            }
        }
    }
    for(int i=1;i<=n;i++)siz[find(i)]++;
    for(int i=1;i<=n;i++)if(siz[i])ans=(ans*jc[siz[i]])%Mod;
    init();
    for(int i=1;i<=n;i++){//求列的块
        for(int j=i+1;j<=n;j++){
            if(ck2(i,j)){
                int fx=find(i),fy=find(j);
                f[fy]=fx;
            }
        }
    }
    for(int i=1;i<=n;i++)siz[find(i)]++;
    for(int i=1;i<=n;i++)if(siz[i])ans=(ans*jc[siz[i]])%Mod;
    return;
}
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    cin>>n>>k;
    memset(a,127,sizeof(a));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    solve();
    cout<<ans<<endl;
    return 0;
}
```

---

