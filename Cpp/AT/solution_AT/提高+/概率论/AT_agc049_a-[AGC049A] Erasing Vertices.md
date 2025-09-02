# [AGC049A] Erasing Vertices

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc049/tasks/agc049_a

$ 1 $ から $ N $ までの番号のついた $ N $ 頂点からなる有向グラフがあります． このグラフの辺は，$ N $ 個の長さ $ N $ の文字列 $ S_1,S_2,\ldots,S_N $ によって表されます． 具体的には，頂点 $ i $ から頂点 $ j $ に向かう辺が存在する場合は $ S_{i,j}= $`1` で， そうでない場合は $ S_{i,j}= $`0` です． このグラフに自己ループや多重辺はありません．

クマの AtCobear くんが，以下の操作をグラフが空になるまで繰り返します．

- (まだ削除されていない) グラフの頂点を一様ランダムに $ 1 $ つ選ぶ（このランダムな選択は，今までの選択とは独立である）． そして，その頂点，およびその頂点からいくつかの辺をたどることで到達可能なすべての頂点を，削除する． 削除された頂点に接続する辺も，すべて削除される．

操作回数の期待値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ S_i $ は `0`,`1` からなる長さ $ N $ の文字列．
- $ S_{i,i}= $`0`

### Sample Explanation 1

以下の $ 3 $ つのシナリオが等確率で起こります． - 最初の操作で頂点 $ 1 $ を選び，頂点 $ 1,2,3 $ が削除される． グラフが空になったので操作を終了する． - 最初の操作で頂点 $ 2 $ を選び，頂点 $ 2,3 $ が削除される． 次の操作で，頂点 $ 1 $ を選び，頂点 $ 1 $ が削除される． グラフが空になったので操作を終了する． - 最初の操作で頂点 $ 3 $ を選び，頂点 $ 2,3 $ が削除される． 次の操作で，頂点 $ 1 $ を選び，頂点 $ 1 $ が削除される． グラフが空になったので操作を終了する． よって操作回数の期待値は，$ (1+2+2)/3=5/3 $ になります．

### Sample Explanation 2

必ず $ 3 $ 回の操作を行います．

### Sample Explanation 3

必ず $ 1 $ 回の操作を行います．

## 样例 #1

### 输入

```
3
010
001
010```

### 输出

```
1.66666666666666666667```

## 样例 #2

### 输入

```
3
000
000
000```

### 输出

```
3.00000000000000000000```

## 样例 #3

### 输入

```
3
011
101
110```

### 输出

```
1.00000000000000000000```

# 题解

## 作者：童年的小翼龙 (赞：2)

对于任意的一个点 $i$，若它被选，就会对答案产生 $1$ 的贡献；若它不被选，就不会对答案产生贡献。所以我们就能把答案转化为 $\sum_{i=1}^n p_i$，其中 $p_i$ 是 $i$ 被选中的概率。

考虑如何计算 $p_i$。对于 $\forall i$，由于它最后一定会被删除，所以要么 $i$ 被选，要么一个能到达 $i$ 的点被选。那么对于那些不能够到达 $i$ 的点，它们与 $i$ 被选的概率就没有关系了。由于一个点只能被删除一次，所以若任意一个能到达 $i$ 的点被选，$i$ 就不能被选了。所以 $p_i=\frac{1}{num}$，其中 $num$ 是能够到达 $i$ 的点的个数（包括 $i$）。

我们可以先在 ```bitset``` 的优化下处理每个点能够到达的点，然后对于每一个点枚举并计算能够到达它的点，就可以算出 $p_i$，进而算出最终答案 $\sum_{i=1}^np_i$。这样总的时间复杂度为 $O(\frac{n^3}{w})$，跑得飞快，目前还是最优解 rk1，见 [评测记录](https://www.luogu.com.cn/record/108810423)。

对于 [CF280C](https://www.luogu.com.cn/problem/CF280C) 这道题，只要把上述 $num$ 的定义改为当前点祖先的个数就行了。

AC Code:  

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Slongod{
const int N = 107;
bitset <N> g[N];
int n; long double ans; 
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char c; cin >> c;
            g[i][j] = c - '0';
        }
        g[i][i] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (g[j][i])
                g[j] |= g[i];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int sz = 0;
        for (int j = 1; j <= n; j++)
        {
            if (g[j][i])
                sz++;
        }
        ans = ans + 1.0 / sz;
    }
    cout << fixed << setprecision(14) << ans << '\n';
    return 0;
}
}int main()
{
    ios :: sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    return Slongod :: main();
}
```

---

## 作者：无钩七不改名 (赞：1)

先对于每个点 $i$ 求出可以到达它的节点的数量 $c_i$（包括自己本身）。使用 $n$ 次 dfs，对于每个点能到达的点 $v$ 增加 $c_v$。

那么答案便是 $\sum \frac{1}{c_i}$。因为每个点只有除了它本身能到达它的其他点没被选中时才可能被选中，此时计入答案。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=105;

int n,c[N];
bool vis[N];
vector<int> vc[N];
double ans;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

void dfs(int i){
	if(vis[i])return;
	vis[i]=1;++c[i];
	for(int v:vc[i])dfs(v);
	return;
}

int main(){
//	freopen("F.in","r",stdin);
//	freopen("F.out","w",stdout);
	n=read();
	for(int i(1);i<=n;++i)
		for(int j(1);j<=n;++j){
			char c;scanf(" %c",&c);
			if(c-'0')vc[i].push_back(j);
		}
	for(int i(1);i<=n;++i){
		memset(vis,0,sizeof(vis));
		dfs(i);
	}
	for(int i(1);i<=n;++i)ans=ans+1.0/c[i];
	printf("%.10f",ans);
	return 0;
}
```


---

## 作者：CQ_Bab (赞：0)

# 思路
发现对于一个点如果选了它那么一定会对答案有 $1$ 的贡献，而如果选了能直接到达它的点那么它就不能对答案有贡献了所以我们设 $cnt_i$ 为能直接到达第 $i$ 个点的数量，而答案就是 $\sum 1\div (cnt_i+1)$ 因为要加上自己，这个直接对于每一个点去暴力搜索即可，时间复杂度 $O(n^2)$ 跑得飞快。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define in(x) scanf("%lld",&x)
#define int long long
#define fire signed
#define il inline
il void print(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int T=1;
int n;
const int N=110;
string s[N];
int cnt[N];
vector<int>v[N];
double res;
int vis[N];
void dfs(int x) {
	vis[x]=1;
	cnt[x]++;
	for(auto to:v[x]) {
		if(vis[to]) continue;
		dfs(to);
	}
}
void solve() {
	in(n);
	rep(i,1,n) cin>>s[i],s[i]=" "+s[i];
	rep(i,1,n) rep(j,1,n) if(s[i][j]=='1') v[i].pb(j);
	rep(i,1,n) {
		rep(j,1,n) vis[j]=false;
		dfs(i);
	}
	rep(i,1,n) res+=1.0/cnt[i];
	printf("%.9lf",res);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [[AGC049A] Erasing Vertices](https://www.luogu.com.cn/problem/AT_agc049_a) | AtCoder [A - Erasing Vertices](https://atcoder.jp/contests/agc049/tasks/agc049_a)

更佳的阅读体验：[AGC049A 题解](https://blog.ryanli.top/index.php/archives/53/)

---

**简要题意**：$n$ 个点的简单有向图。重复等概率随机选定一个还未删除的点，删除它和它能到达的点，直到图中没有任何未被删除的点。求期望进行多少次操作后会把图删完。

首先来考虑每个点被删掉的概率。

对于 $x$ 还未被删除时的任意一次操作，如果随到了 $x$，则 $x$ 被选中，如果随到了能到达 $x$ 的其它点，则 $x$ 不可能被选中，否则继续选点。由此过程可知，设 $f_x$ 为能到达 $x$ 的点数（包括 $x$ 本身），则 $x$ 被选中的概率为 $\dfrac{1}{f_x}$ 。

我们知道，期望是线性函数。因此，直接暴力计算出每个点的 $f_i$，答案即为 $\sum \limits_{i = 1}^{n} f_i$。

``` cpp
#include <iostream>
#include <bitset>
using namespace std;

const int N = 110;
int n, f[N];
char c;
bitset<N> g[N], vis;
double ans;

void dfs(int u) {
    if (vis[u]) return;
    ++f[u], vis.set(u);
    for (int i = 1; i <= n; ++i) if (g[u][i]) dfs(i);
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) cin >> c, g[i].set(j, c == '1');
    for (int i = 1; i <= n; ++i) vis.reset(), dfs(i);
    for (int i = 1; i <= n; ++i) ans += 1.0 / f[i];
    cout.precision(12);
    cout << fixed << ans << '\n';
    return 0;
}
```

---

## 作者：WilliamFranklin (赞：0)

竟然抢到了一个最优解。

### 主要思路

考虑把操作次数拆到每一个点上，利用期望的线性性质，分别计算每个点对答案的贡献。

其实可以将一次操作不用真的看作删点，而是每一次选择一个点染成红色，然后把它所能到达的点中尚未染色的点染成蓝色。

记变量 $X_u$ 表示 $u$ 是否染成了红色，那么：

$$E\left(\sum X_u\right) = \sum E\left(X_u\right)$$

记 $S_u$ 表示 $u$ 和能到达 $u$ 的点的集合，当只有 $S_u$ 中的点被染色时 $u$ 才会被染色，所以 $X_u = 1$ 当且仅当 $u$ 是 $S_u$ 中第一个被选中的，概率就是 $\frac{1}{|S_u|}$。

对于求 $S_u$，直接用传递闭包即可。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 105;
bitset<N> b[N];
int n;
vector<int> G[N];
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	For(i, 1, n) {
		string s;
		cin >> s;
		b[i][i] = 1;
		For(j, 0, n - 1) {
			if (s[j] == '1') {
				b[i][j + 1] = 1;
			}
		}
	}
	For(i, 1, n) {
		For(j, 1, n) {
			if (b[j][i]) b[j] |= b[i];
		}
	}
	long double ans = 0;
	For(i, 1, n) {
		long double now = 0;
		For(j, 1, n) if (b[j][i]) now++;
		ans += 1.0000000000 / now;
	}
	printf("%.10Lf", ans);
	return 0;
} 
```

### 谢谢观看

---

## 作者：WhisperingWillow (赞：0)

提供一种感性理解做法。

由于如果 $i$ 被选，则会对答案产生 $1$ 的贡献。

我们要求的就是 $i$ 被选的概率。

记能到达 $i$ 的点数量为 $w_i$，则 $i$ 选的概率为 $\dfrac{1}{w_i}$，这是显然的。

做一遍传递闭包即可。

[Code](https://netcut.cn/p/87060948ef1f2f6f)

---

## 作者：gdf_yhm (赞：0)

[AT_agc049_a](https://www.luogu.com.cn/problem/AT_agc049_a)

[Erasing Vertices](https://atcoder.jp/contests/agc049/tasks/agc049_a)

### 思路

期望。

与 [CF280C](https://www.luogu.com.cn/problem/CF280C) 相似的思路。

每个点最多被做一次，或者被其他点影响。设 $f_i$ 表示 $i$ 是否被选，为 $0$ 或 $1$。答案为 $E[\sum f_i]$，即 $\sum f_i$ 的期望。

$$ans=E[\sum f_i]=\sum E[f_i]=\sum p_i$$

所以答案为每个点被选的概率的和。

能影响点 $i$ 使其不被选的点，是那些能到达 $i$ 的点，如果在 $i$ 之前被选，那么 $i$ 就不用选了。所以设 $siz$ 为能影响点 $i$ 的点数（包括自己），则 $p_i=\frac{1}{siz}$ 。

$n\leq100$ ，用 flody 看一个点能去哪些点。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=110;
const int inf=2e9;

double n,ans,siz;
char c[maxn];
int e[maxn][maxn];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c+1;
		for(int j=1;j<=n;j++)e[j][i]=c[j]-'0';
	}
	for(int i=1;i<=n;i++)e[i][i]=1;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(e[i][k]&&e[k][j])e[i][j]=1;
			}
		}
	}
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=n;j++)cout<<e[i][j]<<" ";
//		cout<<"\n";
//	}
	for(int i=1;i<=n;i++){
		siz=0;
		for(int j=1;j<=n;j++){
			if(e[i][j])++siz;
		}
		ans+=1.0/siz;
//		cout<<ans<<" "<<siz<<"\n";
	}
	printf("%.10lf",ans);
}

```


---

