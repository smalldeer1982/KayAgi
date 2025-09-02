# [ARC140D] One to One

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc140/tasks/arc140_d

全ての要素が $ 1 $ 以上 $ N $ 以下である長さ $ N $ の整数列 $ X=(X_1,X_2,\dots,X_N) $ に対して次の問題を考え、その答えを $ f(X) $ とします。

> $ N $ 頂点の無向グラフ $ G $ があります。($ G $ は多重辺や自己ループを含むことがあります。) $ G $ の辺は $ N $ 本あり、そのうち $ i $ 番目の辺は頂点 $ i $ と頂点 $ X_i $ を繋ぐ辺です。$ G $ の連結成分の個数を求めてください。

長さ $ N $ の整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。各 $ A_i $ は $ 1 $ 以上 $ N $ 以下の整数あるいは $ -1 $ です。

全ての要素が $ 1 $ 以上 $ N $ 以下である長さ $ N $ の整数列 $ X=(X_1,X_2,\dots,X_N) $ であって、$ A_i\ \neq\ -1\ \Rightarrow\ A_i\ =\ X_i $ を満たすものを考えます。そのような全ての $ X $ に対する $ f(X) $ の総和を $ 998244353 $ で割ったあまりを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 2000 $
- $ A_i $ は $ 1 $ 以上 $ N $ 以下あるいは $ -1 $ である。
- 入力は全て整数である。

### Sample Explanation 1

$ X $ として条件を満たすものは以下の $ 3 $ 通りがあります。 - $ X=(1,1,3) $ の時、問題の答えは $ 2 $ です。 - $ X=(2,1,3) $ の時、問題の答えは $ 2 $ です。 - $ X=(3,1,3) $ の時、問題の答えは $ 1 $ です。 よって答えは $ 2+2+1=5 $ です。

## 样例 #1

### 输入

```
3
-1 1 3```

### 输出

```
5```

## 样例 #2

### 输入

```
1
1```

### 输出

```
1```

## 样例 #3

### 输入

```
8
-1 3 -1 -1 8 -1 -1 -1```

### 输出

```
433760```

# 题解

## 作者：Conan15 (赞：13)

2024 年 10 月 31 日：修改状态、转移方程、统计答案部分的文字表述，以及转移方程的公式错误。\
2024 年 11 月 11 日：更详细地解释式子的含义。

## 题面翻译

你有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，其中每个元素都是 $[1,n]$ 中的整数。

初始时有编号为 $1 \sim n$ 的 $n$ 个节点，对于每个 $1\leq i \leq n$，从 $i$ 向 $a_i$ 连一条无向边。$a_i=-1$ 表示 $a_i$ 还没有确定。你需要对所有可能的 $a$ 序列求出图中连通块数量的和对 $998244353$ 取模的结果。

## 题目讲解

注意到一个美妙的性质。\
先把所有不是 $-1$ 的点 $i$ 向 $a_i$ 连边（可以先假设为有向边，更好理解），会发现每一个连通块是**树**、**环**或者**基环树**。\
环和基环树内一定没有 $-1$ 的点，用有向图的思维可以理解为**内向树**。\
至于树，$-1$ 的点只有一个，并且它是根节点。

因此确定完所有 $-1$ 点的连接状态之后，整个图会变成若干个基环树和环。

---------------

发现性质之后就是神仙计数题了，设有 $m$ 个**树连通块**。\
对于**基环树和环**而言，往它们连边后树不计算贡献，所以可以单独计算它们自己的贡献，根据乘法原理，每个基环树和环贡献是 $n^m$。

发现 $n$ 很小，可以设二维状态。\
设 $dp_{i,j}$ 表示前 $i$ 个**树连通块**，选择 $j$ 个使得他们组成一个基环树或环的**方案数**，则有：

$$dp_{i,j}=dp_{i-1,j-1} \times siz_{i} + dp_{i-1,j}$$

其中 $siz_{i}$ 表示第 $i$ 个树连通块的大小。\
前者表示选择 $i$ 这一树连通块，与当前已组成的连通块合并有 $sz_i$ 种方法。\
换句话说，设 $j$ 个联通块的顶点集合为 $S$，则一个环的方案数是 $\prod_{v \in S} sz_v$。而当前选 $i$，则表示该环要多一个元素 $i$，也即方案数要乘上 $sz_i$。\
后者表示不选择 $i$，直接从前 $i-1$ 个选 $j$ 个的状态转移而来。

---------------

考虑如何统计答案。基环树和环的答案已经统计过了，而我们现在要统计**树连通块**的贡献。

$$ans = \sum\limits_{i=1}^{m} dp_{m,i} \times n^{m-i} \times (i-1)!$$

它的意思是，从 $m$ 个树连通块中选择了 $i$ 个组成一个连通块， $i$ 个连通块本身则有 $i!$ 种排列方式，但由于这个环是可以循环位移（旋转）的，所以方案数量是 $\frac{i!}{i}=(i-1)!$，即 $dp_{m,i} \times (i-1)!$。\
而其余的 $m-i$ 个树连通块的根节点可以连接到任意一个点，与之合并成同一连通块，贡献是 $n^{m-i}$。注意这种情况并不会对**连通块个数**有 $+1$ 的贡献，但是它们可以任意选择 $n$ 个节点中的一个进行连接，所以会把 $dp_{i,j}$ 的答案乘上 $n^{m-i}$，即只考虑当前钦定的这个连通块所产生的贡献。

略微提一下，这样的状态设计就已经能过了，不过当然可以把 DP 压缩到一维，倒序转移，这和背包是类似的。\
注意开 `long long`。

时间复杂度 $O(N^2)$，~~码风可能比较抽象请见谅~~。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2015, M = N << 1;
const int mod = 998244353;
int n, a[N], dp[N][N];
int h[N], e[M], ne[M], idx = 0;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool st[N];
int sz[N];
void dfs(int u, int root) {
    st[u] = 1, sz[root]++;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (st[v]) continue;
        dfs(v, root);
    }
}

int m, b[N], fac[N];

int qmi(int a, int k) {
    int res = 1;
    while (k) {
        if (k & 1) res = (res * 1ll * a) % mod;
        a = (a * 1ll * a) % mod;
        k >>= 1;
    }
    return res;
}

int main() {
    scanf("%d", &n);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) h[i] = -1, fac[i] = (fac[i - 1] * 1ll * i) % mod;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        if (a[i] != -1) add(i, a[i]), add(a[i], i);
    }
    for (int i = 1; i <= n; i++)
        if (a[i] == -1) dfs(i, i), b[++m] = i;
    dp[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= i; j++)
            dp[i][j] = ((dp[i - 1][j - 1] * 1ll * sz[b[i]]) % mod + dp[i - 1][j]) % mod;
    }
    long long ans = 0;
    for (int i = 1; i <= m; i++)
        (ans += ((dp[m][i] * 1ll * fac[i - 1]) % mod * 1ll * qmi(n, m - i)) % mod) %= mod;  //树之间的连边
    
    for (int i = 1; i <= n; i++)
        if (!st[i]) dfs(i, i), (ans += qmi(n, m)) %= mod;   //基环树连通块
    
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Xy_top (赞：8)

好题。（不过绝大部分题解全在瞎说）

看到 $n$ 个点 $n$ 条边且每个点只有一条出边很容易的想到基环树。

而最后每个连通块一定是一个基环树，那么统计连通块的数量就相当于统计基环树的数量。

既然有基环树，这种题绝对不能枚举然后求连通块数量，一定是枚举连通块求它在多少种情况中会出现。

首先先扫一遍，把确定的边用并查集建好，同时维护每个树的点数量，变数量，这样就能够方便判断它是不是一个基环树了。

从基环树森林上断掉任意条边，一定会形成若干颗森林和若干颗基环树，这点十分显然，对于断开后仍是基环树的情况，可以直接统计答案了（因为日后无论怎么连始终是一个连通块），此时记输入的 $a$ 数组中有 $x$ 个 $-1$，方案为 $n^x$。（乘法原理）

接着考虑树，树中一定是有一个点向外连的边还没有确定，如果将这个边连到输入时就有的基环树上，此时的答案我们已经在输入时统计完了，所以唯一剩下的情况就是树连到树上形成基环树。

此时仍然不好考虑，不妨枚举一些东西，枚举这个基环树是由 $k$ 颗树构成的，然后发现倘若这 $k$ 颗树的根分别是 $a_1$ $a_2$ $a_3\cdots a_k$，那么由这些树互相连接组成基环树的方案数为 $sz_{a_1}\times sz_{a_2}\times sz_{a_3}\cdots \times sz_{a_k}$，当然这只是第 $i$ 颗基环树连向第 $i\bmod k+1$ 棵树的方案数。

事实上，我们还要对于这 $i$ 颗树进行排列后第 $i$ 颗连向第 $i+1$ 颗，这样才能不重不漏的计数。

排列的数量为 $k!$，但事实上并不是。

因为 $a_1$ $a_2$ $\cdots a_k$ 和 $a_2$ $a_3$ $\cdots a_k$ $a_1$ 是一样的，这种就是环状的情况，所以要除以 $k$。

如果有 $k$ 颗树 $a_1$ $a_2$ $a_3\cdots a_k$，那么连接成的基环树的数量就是 $(k-1)!\times sz_{a_1}\times sz_{a_2}\cdots \times sz_{a_k}$ 了。

于是枚举完 $k$，$(k-1)!$ 是可以提出来的，就剩下这样一个问题：从长度为 $n$ 的序列中选择 $k$ 项，求这些项的乘积和，设 $F_{i,j}$ 为前 $i$ 个数中选择 $j$ 个的乘积和，这是一个 $n^2$ 的劣质 DP。

此时发现枚举 $k$ 已经没有意义了，我们可以在计算完 $F$ 后，设 $cnt$ 为输入完后统计出树的数量，$F_{cnt,i}\times (i - 1)!$ 即为由 $i$ 颗树组成基环树的方案数了。

但答案仅仅如此吗？并不是，因为还有其余的 $-1$ 的 $a$ 没有选取，建基环树消耗了 $i$ 个 $-1$ 节点，剩下的 $-1$ 节点减一减就得到了，设剩下的 $-1$ 节点有 $sum$ 个，还是乘法原理 $n^{sum}$。

至此，这道题做完了：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
using namespace std;
int n, ans, cnt, cnt_1;
int a[2005], fac[2005], sum[2005];
int F[2005][2005];
const int mod = 998244353;
bool f, vis[2005];
int fa[2005], sz[2005], edge[2005];
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1) % mod;
}
int find (int x) {return (fa[x] == x ? x : fa[x] = find (fa[x]) );}
void merge (int x, int y) {
	int fx = find (x), fy = find (y);
	if (fx == fy) edge[fx] ++;
	else {
		fa[fy] = fx;
		sz[fx] += sz[fy];
		edge[fx] += edge[fy] + 1;
	}
}
signed main () {
	fac[0] = 1;
	For (i, 1, 2000) {
		fac[i] = fac[i - 1] * i % mod;
		fa[i] = i;
		sz[i] = 1;
	}
	cin >> n;
	For (i, 1, n) {
		cin >> a[i];
		if (a[i] == -1) {
			++ cnt_1;
			continue;
		} else merge (i, a[i]);
	}
	For (i, 1, n) {
		if (fa[i] == i) {
			if (edge[i] == sz[i]) ans = (ans + q_pow (n, cnt_1) ) % mod;
			else sum[++ cnt] = sz[i];
		}
	}
	F[0][0] = 1;
	For (i, 1, cnt) For (j, 0, i) {
		F[i][j] = F[i - 1][j];
		if (j) F[i][j] = (F[i][j] + F[i - 1][j - 1] * sum[i]) % mod;
	}
	For (i, 1, cnt) {
		ans = (ans + F[cnt][i] * q_pow (n, cnt_1 - i) % mod * fac[i - 1]) % mod;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：是青白呀 (赞：6)

这一篇题解的状态设计与转移应该是很清楚的。

## 分析

首先观察题干输入，发现这是一个 $n$ 个点、 $n$ 条边的图，且一个点只连出去一条边，那么它一定是由多个基环树或环组成的。现在考虑删去未定的边，发现删去一条边会使得一棵基环树变成两棵树、或使得一棵树变成两棵树，且每一棵树中仅有一个权值为 $-1$ 的节点（否则边数不够）。

我们发现原题中求的是每种情况下连通块数的总和，根据加法结合律，可以转化为求每种连通块（基环树）在多少种情况下出现，再加和。因而我们考虑数出有多少种连通块出现过。设权值为 $-1$ 的节点有 $cnt$ 个，则删去未定边的后的树有 $cnt$ 棵。分两种情况讨论。

1. 对于删去未定边后，仍然是基环树或环的连通块，无论其它边如何连接，这个连通块都一定存在。故它对每一种情况都会产生 $1$ 的贡献。情况总数是 $n^{cnt}$ 种，这一类的连通块数可以通过 dfs 求出。相乘即为第一种情况的贡献

2. 对于 $cnt$ 棵树，其内部连边可以形成新的连通块（基环树），具体的连边方式是每一个权值为 $-1$ 的节点向下一棵树的任意一个节点连边，最终形成一个基环树。考虑设 $dp_{i,j}$，表示从前 $i$ 棵树中选出 $j$ 棵树组成一个连通块的方案总数。设第 $i$ 棵树中的节点数量为 $num_i$，便有如下的转移。


$$
dp_{i,j}=dp_{i-1,j}+dp_{i-1,j-1}\times \max(1,j-1)\times num_i 
$$

其中第一部分是 $i$ 不选的方案数，第二部分是 $i$ 被选进基环树中的方案数。基环树中插入一棵树时，有 $j-1$ 个空位可供插入（注意插入第一棵树时，这里应该是 $1$，而不能乘 $0$），连接到该树上的边可以连到树上的任意一个节点，有 $num_i$ 种方案，相乘即为第二部分的方案数。

最终，考虑由 $i$ 棵树组成的一个连通块，共有 $dp_{cnt,i}$ 种；对于每种连通块，其以外的 $-1$ 节点可以任意连接，该连通块都存在，能产生 $1$ 的贡献，故每个连通块都会在 $n^{cnt-i}$ 种情况中出现。将两者相乘即为选出 $i$ 棵树的贡献，将所有 $i$ 的贡献相加即为第二种情况的贡献。

两种情况的贡献相加即为最终答案。

## 代码
```cpp
#include<bits/stdc++.h> 
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) x*2
#define rs(x) x*2+1
#define mp make_pair
#define fir first
#define sec second
using namespace std;
const int mo=998244353,N=2005;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
//1.发现：最终结果一定是若干棵基环树，现目前的情况一定是若干棵基环树+若干棵树，每棵树中有一个-1节点
//2.考虑：由于求的是每种情况下连通块的总和，根据加法结合律，可以转化为求每种连通块（基环树）在多少种情况下出现，再加和
//3.分类：原本存在的基环树一定在每种情况下出现，可以先记录答案，再考虑树之间连接形成的基环树在多少种情况下出现
//4.分析：先考虑由i棵树连接形成的基环树，设dp(i,j)表示前i棵树中选择j个形成一棵基环树的方案总数 
//若当前树被选择，则考虑：当前树会被插入已经形成的环的任意位置，共有j-1种插入点；该树的-1位置连接点已经确定，
//但上一个树连接到该树上的点任意，共有num[i]种，应该相乘。 
//则：已选择j棵树形成一棵基环树，对答案的贡献为1，其余的树无论如何连接，这一个贡献一定存在，且只会在这里计入
//（因为基环树的环已经唯一了），所以其他的任意连接均可。
int n,pw[N],dp[N][N];
struct tree{
	int to,nxt;
}e[2*N];
int a[N],fir[N],np,sz[N],num[N];
void add(int x,int y){
	e[++np]=(tree){y,fir[x]};
	fir[x]=np;
}
bool vis[N];
void dfs(int x){
	vis[x]=1;
	sz[x]=1;
	for(int i=fir[x];i;i=e[i].nxt){
		int j=e[i].to;
		if(vis[j])continue;
		dfs(j);
		sz[x]+=sz[j];
	}
}
signed main(){
	read(n);
	pw[0]=1;
	rep(i,1,n){
		pw[i]=pw[i-1]*n%mo;
		read(a[i]);
		if(a[i]!=-1)add(i,a[i]),add(a[i],i);
	}
	int cntt=0,ans=0;//cntt:-1的数量 
	rep(i,1,n){
		if(a[i]==-1){//先求树的数量 
			dfs(i);
			num[++cntt]=sz[i];
		}
	}
	rep(i,1,n){
		if(!vis[i]){//每做一次dfs就走了一个基环树，加上该点的贡献 
			dfs(i);
			ans=(ans+pw[cntt])%mo;
		}
	}	
	rep(i,0,cntt)
	    dp[i][0]=1;
	rep(i,1,cntt){
		rep(j,1,cntt){
			dp[i][j]=(dp[i-1][j]+dp[i-1][j-1]*max(j-1,1ll)%mo*num[i]%mo)%mo;//插入一棵新树时，乘插入点数和上一棵树连到这棵树上任意一个点的总数 
		//注意：当j=1时，插入点的方案数应该是1，不能乘0,；大于1时，插入点的方案数为j-1. 
		//	printf("%d %d:%lld\n",i,j,dp[i][j]);
		}
			
	}
	rep(i,1,cntt){
		ans=(ans+dp[cntt][i]*pw[cntt-i]%mo)%mo;
	}
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：Caiest_Oier (赞：3)

# [AT_arc140_d](https://www.luogu.com.cn/problem/AT_arc140_d)     

独立做出来的一道题。     

首先将求和转化成期望，于是问题变成随机连边，求连通块个数的期望。容易发现一个性质，对于初始的序列，每一个连通块要么是一个树，要么是一个基环树。如果是基环树则不能再连边，否则可以向外连一条边。于是我们将每一个连通块先缩成一个点来看。       

缩完点后，每个点要么可以连一条边，要么不能连，所以最后的图一定是一堆树和基环树。我们先不考虑环的情况，则每连一条边，连通块都减少 $1$，如果考虑环，则因为一个连通块最多出现一个环，所以每一个环会增加一个连通块。于是答案就是原序列的连通块数减去要连的边数，再加上环的期望个数。     

对于环的期望个数，我们不妨对所有种类环都统计出现的概率。缩完点后，每个点会有一个权值，代表其对应连通块的大小，令其为 $b_1,b_2,b_3\dots b_m$，则对于一个点集 $S$，出现点集等于 $S$ 的环的概率为 $\frac{(|S|-1)!}{n^{|S|}}\times \prod_{u\in S}b_u$，公式的推导可以考虑钦定环连边的顺序，然后将连边的概率乘起来。     

有了这个式子后，我们按点集大小做一个背包就可以了，复杂度 $O(n^2)$。如果用卷积优化背包可以做到 $O(n\log n)$，~~但是我不会~~。    

代码：    

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int n,a[500003],tot,mk[500003],vis[500003],ans,dp[500003],nyn;
int fstp(int X,int Y){
	int ret=1,bse=X;
	while(Y){
		if(Y&1)ret*=bse;
		bse*=bse;
		ret%=MOD;
		bse%=MOD;
		Y>>=1;
	}
	return ret;
}
vector<int>e[500003];
vector<int>ltk[500003];
void dfs(int now){
	vis[now]=1;
	ltk[tot].emplace_back(now);
	if(a[now]==-1)mk[tot]=1;
	for(auto i:e[now])if(!vis[i])dfs(i);
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	nyn=fstp(n,MOD-2);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=-1){
			e[a[i]].emplace_back(i);
			e[i].emplace_back(a[i]);
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			tot++;
			dfs(i);
		}
	}
	ans=tot;
	for(int i=1;i<=tot;i++)if(mk[i]==1)ans--;
	dp[0]=1;
	for(int i=1;i<=tot;i++){
		if(mk[i]==0)continue;
		for(int j=tot;j;j--)dp[j]=(dp[j]+dp[j-1]*(ltk[i].size()*nyn%MOD))%MOD;
	}
	for(int i=1,j=1;i<=tot;j=j*i%MOD,i++)ans=(ans+dp[i]*j)%MOD;
	for(int i=1;i<=n;i++)if(a[i]==-1)ans=ans*n%MOD;
	ans%=MOD;
	ans+=MOD;
	ans%=MOD;
	cout<<ans;
	return 0;
}
```


---

## 作者：LiveZoom (赞：3)

## Description

[link](https://www.luogu.com.cn/problem/AT_arc140_d)

## Solution

如果已经确定了 $a$ 数组，那么对于每一个大小为 $k$ 的连通块，它的边数也是 $k$，即它为一个基环树。

所以最后原图就变为一堆基环树，所以我们只要求环的个数即可。

首先在已经确定的图中，如果连通块中没有 $a_i=-1$ 的，那么它一定是基环树。

如果有 $a_i=-1$ 的，那么它的边数小于点数，又因为它是个连通块，所以它一定是个树。

对于每个基环树，先把贡献加上，然后就不管他了。如果一个树连向基环树，那么对环的个数没有贡献。

只有树与树之间的连接才可能有贡献。设 $f_{i,j}$ 表示把前 $i$ 个树，最后形成了 $j$ 个基环树的方案数。

那么 $f_{i,j}=f_{i-1,j-1}\times sz_i+f_{i-1,j}$，这个意思就是如果 $i$ 连了自己，就是 $f_{i-1,j-1}\times sz_{i}$，否则为 $f_{i-1,j}$。

最后这些树对答案的贡献就是 $\sum\limits_{i=1}^{m}{f_{m,i}\times (i-1)!\times n^{m-i}}$。这个就是组成 $i$ 个基环树的方案数乘这些树连接的顺序，再乘上其余随便连的答案。

时间复杂度：$O(n^2)$。

## Code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int kMaxN = 2005, kMod = 998244353;

int n, m;
int a[kMaxN], v[kMaxN], sz[kMaxN], fac[kMaxN], pw[kMaxN], f[kMaxN];
bool vis[kMaxN];
vector<int> G[kMaxN];

void dfs(int u, int fa) {
  sz[u] = 1;
  vis[u] = 1;
  for (auto v : G[u]) {
    if (v == fa || vis[v]) continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}

void dickdreamer() {
  cin >> n;
  pw[0] = fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = 1ll * n * pw[i - 1] % kMod;
    fac[i] = 1ll * i * fac[i - 1] % kMod;
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (~a[i]) {
      G[i].emplace_back(a[i]);
      G[a[i]].emplace_back(i);
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!~a[i]) {
      dfs(i, 0);
      v[++m] = sz[i];
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      dfs(i, 0);
      ans = (ans + pw[m]) % kMod;
    }
  }
  f[0] = 1;
  for (int i = 1; i <= m; ++i) {
    for (int j = i; j; --j) {
      f[j] = (f[j] + 1ll * f[j - 1] * v[i]) % kMod;
    }
  }
  for (int i = 1; i <= m; ++i) {
    ans = (ans + 1ll * f[i] * fac[i - 1] % kMod * pw[m - i]) % kMod;
  }
  cout << ans << '\n';
}

signed main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  // cin >> T;
  while (T--) dickdreamer();
  return 0;
}
```

---

## 作者：JWRuixi (赞：2)

~~/bx /bx /bx ?~~

### 题意

给定长度为 $n$ 的序列 $\{a_n\}$，表示 $i$ 与 $a_i$ 之间有一条无向边，若 $a_i=-1$，则表示不确定。请对于所有可能的 $\{a_n\}$ 求出无向图的连通块个数，答案对 $998244353$ 取模。

$n \le 2000$。

### 分析

发现这图有个性质：$n$ 个点，$n$ 条边；所以每个连通块都是一颗基环树！也就是说：数连通块的方案和数基环树的方案是等价的，那么也就等价于数简单环的数量。

先把所有非 $-1$ 的边连上，显然每个连通块要么是基环树，要么是树；那么每棵树里面就至多有一个 $-1$ 节点。我们考虑基环树部分不论 $-1$ 节点怎么连，对答案的贡献都是一样的，可以预处理。

我们将树抽象成一个点，那么相当于求点与点连边产生的环数。我们考虑统计长度为 $i$ 的环的贡献，我们可以简单设计 dp，$(i-1)!f_i$ 表示长度为 $i$ 的环出现的个数，那么可以有 $f_i \gets f_{i-1}v_u$，其中 $u$ 为当前考虑的树的大小。

复杂度 $\mathcal O(n^2)$。

### Code

提交记录：<https://atcoder.jp/contests/arc140/submissions/43693365>。

---

## 作者：小超手123 (赞：1)

##### 题意：

你有一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$，其中每个元素都是 $[1,n]$ 中的整数。

初始时有编号为 $1 \sim n$ 的 $n$ 个节点，对于每个 $1\leq i \leq n$，从 $i$ 向 $a_i$ 连一条无向边。$a_i=-1$ 表示 $a_i$ 还没有确定。你需要对所有可能的 $a$ 序列求出图中连通块数量的和对 $998244353$ 取模的结果。

##### 分析：

这种计数套路比较常见吧。

对 $a_{i} \ne -1$ 的情况建出一张图。每个连通块只有两种情况，不存在 $a_{i} \ne -1$ 或恰存在一个点的 $a_{i}=-1$。前者会形成一棵基环树（这个环可能由一个自环或两个点组成，不过无所谓），后者会形成一棵树。

不难发现，如果确定了 $a_{i}$ 后，最后一定是基环树森林。每棵基环树一定只有两种情况：

- **原来**（指不考虑 $a_{i}=-1$ 建出的图）的基环树加上一些附庸的**原来**的树。其对答案的贡献为 $n^{x}$，$x$ 为 $a_{i}=-1$ 的数量。
- **原来**的树拼成一棵基环树。假设有 $k$ 棵树组成，那么对答案的贡献为 $n^{x-k} \times (k-1)! \times \prod_{i=1}^{k} siz_{i}$。这是个很简单的 DP。

时间复杂度 $O(n^2)$。

##### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 2010
#define mod 998244353
using namespace std;

int Pow(int a, int n) {
    if(n == 0) return 1;
    if(n == 1) return a;
    int x = Pow(a, n / 2);
    if(n % 2 == 0) return x * x % mod;
    else return x * x % mod * a % mod;
}

int n, tot, ans, x;
int a[N], fa[N], siz[N];
vector<int>p[N];
int f[N][N];

int find(int x) {
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void upd(int &x, int y) {
    x = (x + y) % mod;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i], fa[i] = i;
        if(a[i] == -1) x++;
    }
    for(int i = 1; i <= n; i++)
        if(a[i] != -1) fa[find(i)] = find(a[i]);
    for(int i = 1; i <= n; i++) p[find(i)].push_back(i);
    for(int i = 1; i <= n; i++) {
        if(!p[i].size()) continue;
        bool flag = 0;
        for(auto x : p[i])
            if(a[x] == -1) {
                flag = 1;
                break;
            }
        if(flag) siz[++tot] = p[i].size();
        else upd(ans, Pow(n, x));
    }
    
    f[0][0] = 1;
    for(int i = 1; i <= tot; i++)
    for(int j = 0; j <= i; j++) {
        upd(f[i][j], f[i - 1][j]);
        if(j) upd(f[i][j], f[i - 1][j - 1] * siz[i] % mod);
    }

    int h = 1;
    for(int i = 1; i <= x; i++) {
        upd(ans, Pow(n, x - i) * f[tot][i] % mod * h % mod);
        h = h * i % mod;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：XYQ_102 (赞：1)

## D - One to One
### 题意
给一个长度为 $n$ 的数组 $a_i$，$a_i \ne -1$ 表示 $i$ 和 $a_i$ 之间有一条边，$a_i = -1$ 表示 $a_i$ 的可能在 $[1, n]$ 中任取。

$f(a)$ 表示 $a$ 对应的图中连通块的数目。

问所有可能情况中 $f(a)$ 的和。

其中 $n \le 2000$。
### 思路
建出来的图中，一个连通块对应一个环，然后可以从数连通块转化为数环。

首先是 $a_i \ne -1$ 的边组成的环，假设共有 $C$ 个，且有 $D$ 个 $i$ 使得 $a_i = -1$，则这部分的贡献为 $C \times n^D$。

此时，除了环之外其余连通块都是树，假设有 $K$ 棵树，第 $i$ 棵树的大小为 $B_i$。考虑选择其中 $k$ 个棵树链接起来组成一个环，假设选取了点 $x_i, 1 \le i \le k$，则这个环的种类有 $(k - 1)!\times\prod_{i = 1}^{k} B_{x_i}$。假设前 $i$ 个点，大小为 $j$ 的环共有 $dp_{i, j}$ 类，则 $dp_{i, j} = dp_{i - 1, j} + dp_{i - 1, j - 1} \times B_i$。

然后考虑大小为 $k$ 的环对答案的贡献，其值为 $dp_{K, k} \times (k - 1)! \times n^{K - k}$。
### AC代码
```cpp
// Problem: D - One to One
// Contest: AtCoder - AtCoder Regular Contest 140
// URL: https://atcoder.jp/contests/arc140/tasks/arc140_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main() {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

struct DSU {
  int n;
  std::vector<int> f, tag, sz;

  DSU(int _n) : n(_n), f(n), tag(n), sz(n) {
    for (int i = 0; i < n; ++i) {
      f[i] = i;
      tag[i] = 0;
      sz[i] = 1;
    }
  }

  int leader(int x) {
    if (f[x] == x)
      return x;
    f[x] = leader(f[x]);
    return f[x];
  }

  bool same(int x, int y) { return leader(x) == leader(y); }

  void merge(int x, int y) {
    x = leader(x);
    y = leader(y);
    if (x == y)
      return;
    f[x] = y;
    sz[y] += sz[x];
  }

  void set(int x) { tag[x] = 1; }
};

const int mod = 998244353;

void solve_case(int Case) {
  int n;
  std::cin >> n;

  std::vector<int> fact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i)
    fact[i] = i64(1) * fact[i - 1] * i % mod;
  std::vector<int> power(n + 1);
  power[0] = 1;
  for (int i = 1; i <= n; ++i)
    power[i] = i64(1) * power[i - 1] * n % mod;

  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    if (a[i] != -1)
      --a[i];
  }

  DSU dsu(n);
  for (int i = 0; i < n; ++i) {
    if (a[i] != -1) {
      if (dsu.same(i, a[i]))
        dsu.set(dsu.leader(i));
      else
        dsu.merge(i, a[i]);
    }
  }

  int C = 0;
  std::vector<int> B(1);
  for (int i = 0; i < n; ++i) {
    if (i != dsu.f[i])
      continue;
    if (dsu.tag[i]) {
      ++C;
      continue;
    }
    B.push_back(dsu.sz[i]);
  }
  logd(B);

  int D = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] == -1) {
      ++D;
    }
  }
  // cycle constructed by fixed edges
  int fixed = i64(1) * power[D] * C % mod;

  // cycle constructed by mutable edges
  int k = B.size() - 1;
  std::vector<std::vector<int> > dp(k + 1, std::vector<int>(k + 1, 0));
  for (int i = 0; i <= k; ++i)
    dp[i][0] = 1;
  for (int i = 1; i <= k; ++i) {
    for (int j = 0; j <= i; ++j) {
      dp[i][j] = (dp[i - 1][j] + i64(1) * dp[i - 1][j - 1] * B[i] % mod) % mod;
    }
  }
  int dynamic = 0;
  for (int i = 1; i <= k; ++i) {
    dynamic =
        (dynamic + i64(1) * fact[i - 1] * power[k - i] % mod * dp[k][i] % mod) %
        mod;
  }
  int ans = (fixed + dynamic) % mod;
  std::cout << ans << "\n";
}
```

---

## 作者：xcyyyyyy (赞：1)

### [ARC140D] One to One  

神奇计数题。

先将所有确定的边连起来，一个比较关键的点是，将每个方案的贡献摊到每一个环上，即统计每个可能的环的方案数。设 $a_i=-1$ 的数量为 $num$。

对于基环树来说，不论其他点怎么选这个环都存在，贡献为 $n^{num}$。

对于若干树构成的环来说，这种环有 $(t-1)!\prod \limits_{i=1}^t sz_i $ 个，对于每一个环，贡献为 $n^{num-t}$。

将树的贡献放到 dp 里面即可。

---

## 作者：Glacial_Shine (赞：1)

更好的[体验](https://blog.csdn.net/weixin_46700592/article/details/129063395)

---

## 思路
我们先来考虑先不将 $a[i] = -1$ 的边连出去。

则此时我们的图会变成多个连通块，每个连通块是基环树或环或树。

其中如果一个连通块是树，则其中一定有一个节点的 $a$ 值为 $-1$。

如果一个连通块是基环树或环，则其中没有节点的 $a$ 值为 $-1$。

此时我们可以发现，对于所有的基环树和环他们的贡献都可以算出来，因为如果目前我们将一个 $a$ 值为 $-1$ 的点连向基环树或环，则这个点所在的连通块的贡献我们就不会算进去，也并不会对基环树和环的贡献产生影响。

并且此时基环树和环已经确定了，并不会再连出去，所以我们可以先将所有基环树和环的贡献算出来。

接下来我们考虑树连通块的贡献。

我们知道如果一个树连通块连向基环树和环，则它们的贡献就可以不用计算。

如果不连向基环树和环，则最后这些树连通块一定会变成几个环。

于是我们可以把所有的树连通块看成一个点，并且点的权值为连通块的大小，然后我们考虑 DP。

我们设 $g[i]$ 表示形成长度为 $i$ 的环的方案数。

则我们可以对于每个点 $k$ 来更新 $g$ 值。

则方程式为 $g[i] = g[i] + g[i - 1] \cdot size[k]$。

我们求出来 $g$ 后考虑如何计算答案。

我们可以对每个环算贡献。

我们知道一个长度为 $i$ 的环的贡献为 $g[i] \cdot n^{cnt - i} \cdot (n-1)!$，其中 $cnt$ 是树连通块的个数。

我们来看看为什么。

首先除了这 $i$ 个点，其他我们可以随便连，它们的贡献后面再算，于是就有 $n^{cnt - i}$ 种可能出现长度为 $i$ 的环。

因为我们算贡献并没有考虑顺序的问题，于是我们考虑顺序，此时所有点的全排列是 $n!$ 的，又因为它可以旋转，所以要除上 $n$，也就变为 $(n - 1)!$。

到此问题就结束了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD = 998244353;
int n, m, a[2005], fa[2005], flag[2005], num;
LL g[2005], size[2005], ans, mul[2005], sum[2005];
LL Pow(LL a, LL b) {
    LL s = 1;
    while (b) {
        if (b & 1)
            s = s * a % MOD;
        a = a * a % MOD, b = b >> 1;
    }
    return s;
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int main() {
    scanf("%d", &n);
    mul[0] = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), fa[i] = i, sum[i] = 1, mul[i] = mul[i - 1] * i % MOD;
        //mul[i] 是 i 的阶乘。
    for (int i = 1; i <= n; i++)
        if (a[i] != -1) {
            int fx = find(i), fy = find(a[i]);
            if (fx != fy)
                fa[fy] = fx, sum[fx] += sum[fy], sum[fy] = 0;
            //用并查集维护连通块。
        }
    for (int i = 1; i <= n; i++)
        if (a[i] == -1)
            flag[find(i)] = 1, size[++m] = sum[find(i)];
            //如果这个连通块里有点的 a 值为 -1，则这个连通块是一个树连通块。
    for (int i = 1; i <= n; i++)
        if (!flag[i] && fa[i] == i)
            num++;
            //num 是环和基环树的数量
    ans = num * Pow(n, m) % MOD;
    //先把每个环或基环树的贡献计算上，其中 pow(n, m) 是所有可能的方案数。
    g[0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = i; j; j--)
            g[j] = (g[j] + g[j - 1] * size[i] % MOD) % MOD;
    for (int i = 1; i <= m; i++)
        ans = (ans + g[i] * mul[i - 1] % MOD * Pow(n, m - i) % MOD) % MOD;
    printf("%lld", ans);
    return 0;
}
```




---

## 作者：Rainy7 (赞：1)

### 前言

被同学发现笔误。改了一下。

更好的阅读体验：[Link](https://www.cnblogs.com/Rainy7/p/solution-at-arc140d.html)。

### 题解

若对每一块进行考虑，那么对于一个有 $n$ 个点 $n$ 条边的块，也就是基环树或环来说，里面一定不会存在 $a_i=-1$。否则就是一棵树了，那么也最多只会有一个 $a_i=-1$。 

这意味着 $a_i =-1 $ 所在的连通块一定是树，剩下的一定是环或基环树。且这些环或者基环树的贡献一定不会变，可以先加上。

于是只要考虑是树的块。首先如果树中的 $-1$ 连向了一个环或者基环树，那么当前情况的贡献 $f$ 是不变的。不考虑。所以只考虑树和树之间。

一棵树也只有一个 $-1$，因此考虑将一个树看成一个点。于是设 $g(j)$ 表示选若干个点合并成一个大小为 $j$ 的环的方案数。

转移显然有 $g(j) \leftarrow g(j-1) \times sz_i$。因为点 $i$ 都是内部连边，会贡献一个新的连通块。最后算一下贡献就好了。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=2000+5;
const int Mod=998244353;
struct edge{
	int v,nx;
}e[N<<1]; 
int n,ans,ne,cnt,f[N],a[N],pw[N],mul[N],sz[N],v[N],g[N];
bool vis[N];
void read(int u,int v)
{	e[++ne].v=v;
	e[ne].nx=f[u];
	f[u]=ne;
}
void dfs(int u)
{	vis[u]=1,sz[u]=1;
	for(int i=f[u];i;i=e[i].nx)
	{	int v=e[i].v;
		if(!vis[v])dfs(v),sz[u]+=sz[v];
	}
}
int main()
{	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	scanf("%d",&n);
	for(int i=pw[0]=mul[0]=1;i<=n;i++)mul[i]=1ll*mul[i-1]*i%Mod,pw[i]=1ll*pw[i-1]*n%Mod;
	for(int i=1;i<=n;i++)
	{	scanf("%d",&a[i]);
		if(a[i]!=-1)read(i,a[i]),read(a[i],i);
	}
	for(int i=1;i<=n;i++)
		if(a[i]==-1)dfs(i),v[++cnt]=sz[i];
	for(int i=1;i<=n;i++)
		if(!vis[i])dfs(i),ans=(ans+pw[cnt])%Mod;
	g[0]=1;
	for(int i=1;i<=cnt;i++)
		for(int j=i-1;j>=0;j--)g[j+1]=(g[j+1]+1ll*g[j]*v[i]%Mod)%Mod;
	for(int i=1;i<=cnt;i++)ans=(ans+1ll*g[i]*mul[i-1]%Mod*pw[cnt-i]%Mod)%Mod;
	printf("%d\n",ans);
	return 0;
}
```


---

