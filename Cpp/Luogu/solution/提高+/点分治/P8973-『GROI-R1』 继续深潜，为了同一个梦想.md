# 『GROI-R1』 继续深潜，为了同一个梦想

## 题目背景

玘正在折叠床脚几件刚洗净的白衬衫，他注意到身后的声响，向右后转头看去。

以为是“外面的家伙”的他并没有刻意去遮掩自己的右眼——毕竟学院里的人不可能进来。

他看见了那个紫眸的少年；当然寒也看见了那一瞬间的鲜红。

「你什么都没看见。」

玘装作欣赏窗外的晚霞。

## 题目描述

「世上没有无价的情报，」玘露出一丝满意的微笑。

「你懂我的意思吧？」

寒收回手。

玘给出了他留给寒的题。

> 既然紫堇和彼岸花给予了我们异色的瞳孔，我们理所应当是连接在一起的。我称**一棵树上的一个点集是“连接的”**，当且仅当**树上存在一条链能够覆盖这个点集并且这个集合大小不小于 $2$**。我们是独一无二的，可是你知道，一棵树，总是连起来的啊。

「然后呢？」

「现在，你需要告诉我每个点被多少个这样的点集所包含。」


玘飘然而去。

湖底之城那封存已久的记忆，被彼岸花和紫堇的力量，揭开了封印的一角。

## 说明/提示

**样例解释**

![](https://cdn.luogu.com.cn/upload/image_hosting/rl9wkbww.png)

**连接**的集合有以下一些：
- $\{1,2\}$
- $\{1,3\}$
- $\{1,4\}$
- $\{2,3\}$
- $\{2,4\}$
- $\{3,4\}$
- $\{1,2,3\}$
- $\{1,2,4\}$
- $\{2,3,4\}$

如 $\{1,3,4\}$ 就不是一个连接的集合，因为你找不出一条链使得 $\{1,3,4\}$ 为它的子集。

其中 $1,2,3,4$ 号节点分别在 $5,6,5,5$ 个集合中出现。通过计算可得 $\operatorname{xor}_{i=1}^n ans_i\times i=18$。

**数据范围**

**本题采用捆绑测试。**

| 子任务编号 | 数据范围 | 特殊性质 | 分值 | 时间限制 |
| :----------: | :----------: | :----------: | :----------: | :-: |
| $\text{Subtask1}$ | $n\le20$ | | $15$ | $\text{1s}$ |
| $\text{Subtask2}$ | $n\le100$ | | $15$  | $\text{1s}$ |
| $\text{Subtask3}$ | $n\le3\times 10^3$ | | $20$ | $\text{1s}$ |
| $\text{Subtask4}$ | $n\le5\times10^5$ | $\text{A}$ | $15$ | $\text{2s}$ |
| $\text{Subtask5}$ | $n\le5\times10^5$ | | $35$ | $\text{2s}$ |

特殊性质 $\text{A}$：保证树退化成一条链。


对于 $100\%$ 的数据 $1\le u,v\le n\le5\times10^5$。

## 样例 #1

### 输入

```
4
1 2
2 3
2 4```

### 输出

```
18```

# 题解

## 作者：LKY928261 (赞：16)

# 验题人题解

考虑一个集合中一个点能产生贡献的情况。此时该点被集合包含，集合内的所有点在同一条树链上，且该集合中有至少两个点。

显然，一个点 $u$ 在一条长度为 $l$ 的链上产生的贡献为 $2^{l-1}-1$（除去 $u$ 每个点选或不选，再去掉只剩 $u$ 一个点的情况）。

由此延伸到一个点 $u$ 的总贡献：假定整棵树以 $u$ 为根，对每棵子树统计出从子树根出发的方案数（不包含全不选）。对于单棵子树，设其方案数为 $x$，则贡献为 $x$；对于不同的两棵子树，设其方案数分别为 $x,y$，则贡献为 $xy$。只不过此时单个子树的方案数并非简单的 2 的次幂，而是由它下方的子树合并而来。

考虑原题。对于结点 $u$，在以 $u$ 为根的子树中按上述方法统计一遍，再将子树内与子树外的进行一次合并统计。由于方法多样，且参考代码中有较详细的注释，具体实现方式此处不细讲。

时间复杂度 $O(n)$，~~优于 std~~。

### 参考代码

非唯一解法，仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define _ 1000005
#define Mod 1000000007
void pls(ll &x,ll y){x=(x+y)%Mod;}
ll n,x,y,a[_],ans,s[_],cnt,hd[_];
//a[u]: 在以u为根的子树内，u必选，其余点可以全不选，
//且所有集合内的点都在同一条以u为一端的链上的方案数
struct o{ll nxt,to;}edg[_];
void add(ll x,ll y){edg[++cnt].nxt=hd[x];hd[x]=cnt;edg[cnt].to=y;}
//这里由于代码习惯，所有的u都写成了x，请见谅
void dfs1(ll x,ll fa){
	a[x]=1;
	for(ll i=hd[x];i;i=edg[i].nxt)if(edg[i].to!=fa){
		dfs1(edg[i].to,x);
		pls(s[x],(a[x]-1)*(a[edg[i].to]*2-1));//统计当前子树内部产生的贡献
		pls(a[x],a[edg[i].to]*2-1);//更新当前子树下的方案数
	}
}
void dfs2(ll x,ll fa,ll z){//z: 该子树外的方案数（限制同a[u]）
	pls(s[x],a[x]*z-1);//直接统计穿过子树内外的链产生的贡献
	for(ll y,i=hd[x];i;i=edg[i].nxt)if(edg[i].to!=fa){
		y=edg[i].to;
		dfs2(y,x,((a[x]-a[y]*2+1+Mod*2)%Mod+z-1)*2%Mod);//更新
	}
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1;i<n;i++)cin>>x>>y,add(x,y),add(y,x);
	dfs1(1,0);dfs2(1,0,1);
	for(ll i=1;i<=n;i++)ans^=s[i]*i;
	cout<<ans<<'\n';
}
```

---

## 作者：wwwwwza (赞：14)

## [题目传送门](https://www.luogu.com.cn/problem/P8973)

## 附图
![](https://cdn.luogu.com.cn/upload/image_hosting/wnfvqwdc.png)

## 步骤
### 一、输入
1. 直接输入，把树存下来。

### 二、子树内部匹配（从下往上遍历）
1. 假设该子树的根节点为 $u$，设 $f_u$ 表示包含点 $u$ 的点集有几个。（此时假设 $u=2$）。
2. 设 $h_u$ 表示包含点 $u$ 的链式点集有几个。（如 $V_u=\{ 2,10 \}$ 或 $V_u=\{ 2,6 \}$）。
   - 看图可得，包含点 $u$ 的链式点集个数等于其所有子节点 $v$ 的链式点集个数加其子节点的个数，即令 $d_u$ 表示在以 $u$ 为根的子树中所有链式点集的个数。
   - 因为对于包含点 $v$ 的链式点集，直接在其中加上点 $u$ 即可。其次因为两个点就可形成一个点集，所以可以形成其子节点的个数个点集。
   - $ h_u=\sum\limits_{v \in u} d_v+size_v $ 
   - $d_u=h_u+\sum\limits_{v \in u} d_v$
   - $f_u=f_u+h_u$
3. 求从点 $u$ 分出两条链的点集个数。（如 $V_u=\{ 10,5,2,7 \}$）。
   - 可以从两个子树中选出一条链或一个点，根据乘法原理相乘即可。
   - $f_u=f_u+\frac{1}{2} \times \sum\limits_{v1,v2 \in u,v1\ne v2} (d_{v1}+size_{v1} )\times (d_{v2}+size_{v2})$
   - 化简式子 $: f_u=f_u+\frac{1}{2} \times (\sum\limits_{v \in u} d_v+size_v)^2-\frac{1}{2} \times \sum\limits_{v \in u} (d_v+size_v)^2$

### 三、子树与其父节点匹配（从上往下遍历）
1. 假设该子树的根节点为 $u$，设 $f_u$ 表示包含点 $u$ 的点集有几个。（此时假设 $u=2$，并钦定一个子节点 $v$，设 $v=5$）。
2. 设 $e_v$ 表示点 $v$ 向上形成链式点集（点 $u$ 是其中深度最浅的）。（如 $V_u=\{ 2,7 \}$）。
   - 令 $e_v$ 等于在以 $u$ 为根的子树中所有链式点集的个数减去点 $v$ 的贡献，并加上点 $u$ 的子树大小减点 $v$ 的子树大小（上文提到过，两个点也可构成一个点集）。
   - $e_v=d_u-d_v-size_v+size_u-size_v$
   - 化简式子 $: e_v=d_u-d_v \times 2-size_v \times 2+size_u$
3. 点 $v$ 向上形成链式点集中的最近公共祖先可并不一定是点 $u$，可以是点 $v$ 的任意一个祖先。（如 $V_u=\{ 5,2,7 \}$ 或 $V_u=\{ 5,1,4 \}$）。
	- 但在点 $v$ 和其祖先的路径上还有其他节点，都有两种情况，加与不加。设 $k_v$ 表示点 $v$ 向上形成链式点集的数量，在递归计算即可。
   - $k_v=k_u \times 2+e_v$
4. 向上形成链式点集求完了，往下拓展的方案为点 $v$ 的链式点集加其节点本身。
5. 根据乘法原理相乘上方答案和下方答案。
	- $f_v=f_v+k_v \times (h_v+1)$
    
### 四、输出
1. 因为 $f_i$ 表示包含点 $i$ 的点集有几个，而且要 $\bmod \ 998244353$。但最后输出的 $ans$ 不用。
	- $ans=\operatorname{xor}^{i=1} _ n \ f_i \times i$
2. 输出答案 $ans$。


## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
const int mod=1e9+7;
const int two=5e8+4;
int n,x,y,fat[N],ans=0;
int f[N],h[N],d[N],e[N],k[N],size[N];
//答案 链的数量 链数量之和 非该子树答案 非该子树答案之和 子树大小 
vector<int>g[N];
void dfs_in(int u,int fa){
	fat[u]=fa;
	size[u]=1;
	int sum=0,num=0;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fat[u])continue;
		dfs_in(v,u);
		size[u]+=size[v];//子树大小 
		int add=d[v]+size[v];
		add%=mod;
		h[u]+=add;h[u]%=mod;//链式点集个数 
		d[u]+=d[v];d[u]%=mod;//链式点集个数和 
		num=(num+add*add%mod)%mod;
		sum=(sum+add)%mod;
	}
	sum=(sum*sum)%mod;
	int cnt=((sum-num+mod)%mod*two)%mod;
	f[u]=(f[u]+h[u]+cnt)%mod;//计算答案 
	d[u]=(d[u]+h[u])%mod;//链式点集个数和 
}
void dfs_out(int u,int fa){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		int sum=(h[v]+1)%mod;
		e[v]=d[u]-d[v]*2-size[v]*2+size[u]+mod*4;//非该子树答案
		e[v]%=mod;
		k[v]=(k[u]*2%mod)+e[v];//非该子树答案之和
		k[v]%=mod;
		f[v]=(f[v]+k[v]*sum%mod)%mod;//计算答案 
		dfs_out(v,u);
	}
}
signed main(){
	cin >>n;
	for(int i=1;i<n;i++){
		cin >>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs_in(1,0);
	dfs_out(1,0);
	for(int i=1;i<=n;i++){
		f[i]%=mod;
		ans=ans^(f[i]*i);
	}
	cout <<ans;
	return 0;
}
```

---

## 作者：ccxswl (赞：4)

换根 dp 模板题。

$f_i$ 是在以 $i$ 为根的子树中，以 $i$ 为链的一个端点且 $i$ 在点集中的合法点集个数。
$ans_i$ 表示包含 $i$ 的合法点集个数。

当 $x$ 为树根时：

$$ans_x = {f_x \choose 2} - \sum_{s\in son}{2f_s+1 \choose 2} + f_x$$

简单解释一下，${f_x \choose 2}$ 是在所有符合条件的链中随便选两条拼起来的数量，但是有可能会选到同一个子树中的两条链，这样拼起来的集合就不合法了，就像样例解释中的 $\{1,3,4\}$ 一样，所以要减去。最后加上以 $x$ 为链的一端的数量，也就是不需要拼的。

$f_i$ 很好维护：

$$f_x= \sum_{s \in son}2f_s+1$$

$f_s$ 要乘 $2$ 是因为 $s$ 这个点可以选可以不选。即有可能是 $\{\dots, s, x\}$，也有可能是 $\{\dots, x\}$。
加一是因为要加上集合为 $\{s, x\}$ 的情况。

换根的时候根据上面的公式改下 $f$ 数组就可以了。$\sum{2f_s+1 \choose 2}$ 的部分用数组预处理出来就好了。


具体实现看代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int read() {
	int s = 0, w = 1;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-')
			w = -w;
		c = getchar();
	}
	while (isdigit(c)) {
		s = s * 10 + c - 48;
		c = getchar();
	}
	return s * w;
}
void pr(int x) {
	if (x < 0)
		putchar('-'), x = -x;
	if (x > 9)
		pr(x / 10);
	putchar(x % 10 + 48);
}
#define end_ putchar('\n')
#define spc_ putchar(' ')

const int maxN = 5e5 + 7, mod = 1e9 + 7;

const int m2 = 500000004;
// 2 的逆元

int n;

vector<int> E[maxN];

int f[maxN], s[maxN], A[maxN], ans;
// s 数组是预处理公式中求和的部分, A[i] 为 ans[i]

int C(int x) {
	return x * (x - 1 + mod) % mod * m2 % mod;
}

void dfs(int x, int fa) {
	for (int to : E[x])
		if (to != fa) {
			dfs(to, x);
			f[x] += f[to] * 2 + 1;
			f[x] %= mod;
			s[x] += C(f[to] * 2 + 1);
			s[x] %= mod;
		}
}

int ff[maxN];

void calc(int x, int fa) {
	A[x] = ((C(f[x]) - s[x] + mod) % mod + f[x]) % mod;

	for (int to : E[x]) {
		if (to == fa)
			continue;
		int fx = f[x], fto = f[to];
		int S = s[to];
		f[x] -= f[to] * 2 + 1;
		f[x] = (f[x] + mod * 2) % mod;
        // 这里要注意乘 2，因为上面的 f[to] 乘 2 了，只加一个 mod 有可能不够。

		f[to] += f[x] * 2 + 1;
		f[to] %= mod;

		s[to] += C(f[x] * 2 + 1);
		s[to] %= mod;

		calc(to, x);

		f[x] = fx, f[to] = fto;
		s[to] = S;
	}
}

signed main() {
	n = read();
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		E[u].emplace_back(v);
		E[v].emplace_back(u);
	}
	dfs(1, 0);
	calc(1, 0);
	
	for (int i = 1; i <= n; i++)
		ans ^= A[i] * i;
	pr(ans), end_;
}

```

---

## 作者：lsj2009 (赞：4)

## Solution

本题做法很多，本题解给出的做法为大常数 $\Theta(n\log n)$，在验题过程中 lvkaiyi0811 大佬给出了一种小常数 $\Theta(n)$ 而且代码极短的数学做法，但是因为鸽子原因并没有完成题解（Update：完成了！），感兴趣的选手可以询问他。

本题解不对部分分进行讲解。

设答案为 $\{f_n\}$，我们考虑如何计算他。

我们首先来考虑如何计算根的情况（即 $f_1$），我们不妨去枚举能包含题中点集的链，然后再考虑点集的情况。显然点 $1$ 要在这条链上。我们而链的两端 $(u,v)$ 分两种情况：第一种为点 $u,v$ 在点 $1$ 的两个不同的子树，第二种 $u=1$ 或 $v=1$。

先来考虑第一种，枚举两个节点 $(u,v)$，在这条链上除 $1,u,v$ 外的所有节点均可以属于或不属于这个集合，而这条链上共有 $d_u+d_v-1$ 个节点，所以这条链对于答案的贡献为 $2^{d_u+d_v-4}$。

$$f_1=\sum_u\sum_v 2^{d_u+d_v-4}[u\text{ 和 }v \text{ 在 1 的两个不同的子树}]$$

设 $S_u$ 为以 $u$ 为根的子树的节点集合，$S_{u,v}$ 为以 $v$ 所在的 $u$ 的那棵儿子几点为根的子树的节点集合并化简得：

$$f_1=\frac{1}{16}\sum_{u\in S_1-\{1\}} 2^{d_u}\sum_{v\in S_1-S_{1,u}-\{1\}}2^{d_v}$$

考虑 $\Theta(n\log n)$ 预处理 $s_u=\sum\limits_{u\in S_u} 2^{d_u}$，其中 $\log n$ 是快速幂的贡献，然后枚举 $1$ 的每个儿子（设 $\text{Son}_u$ 为 $u$ 的儿子集合）可以得到：

$$f_1=\frac{1}{16}\sum_{u\in \text{Son}_u} s_u(s_1-s_u-2^{d_u})$$

再化简可以得到：

$$f_1=\frac{1}{16}((s_1-2)^2-\sum\limits_{u\in \text{Son}_1}s_u^2)$$

但是需要注意，对于上面这种情况 $(u,v)$ 和 $(v,u)$ 分别统计了 $1$ 次，所有我们需要对答案 $\times \frac{1}{2}$。

再来看第二种情况，$1$ 为链的一端，我们考虑枚举另一端 $u$，参考前面可以得到：

$$f_1=\sum_{u\in S_1-\{1\}} 2^{d_u-2}$$

代入 $s_u$ 得：

$$f_1=\frac{s_1-2}{4}$$

综上得：

$$f_1=\frac{1}{32}((s_1-2)^2-\sum\limits_{u\in \text{Son}_1}s_u^2)+\frac{s_1-2}{4}$$

事实上，如果此时我们去枚举整棵树的根就可以的得到 $f_u=$ 在整棵树以 u 为根的情况下的 $\frac{1}{32}((s_u-2)^2-\sum\limits_{v\in \text{Son}_u}s_v^2)+\frac{s_u-2}{4}$。

现在答案可能已经呼之欲出了：换根 dp！但是要怎么换根呢？容易发现，我们维护住每一个 $s_u$ 即可，然后每一个 $s_u=\sum\limits_{v\in S_u} 2^{d_u}$，事实上真正变动的是每一个 $d_u$。

但是 $d_u$ 是怎么变化的呢？容易发现，在换根的过程中，我们把点 $u$ 提到它的父亲节点 $fa$ 头上的这一过程中，原本以 $u$ 为根的子树的所有节点高度都减掉了 $1$（因为所有节点头上都少了一个点 $fa$），而其余节点高度全部 $+1$（因为头上都多了一个点 $u$），这是什么！子树修改！

我们可以用线段树维护！我们维护住一棵对于 $d_u$ 可以区间乘区间询问和的线段树即可，则每次把点 $u$ 提上去的动作中，我们只需要把以 $u$ 为根的子树值全部 $\times\frac{1}{2}$，其余节点 $\times 2$ 即可，具体实现可以下全局 $\times2$ 然后子树 $\times\frac{1}{4}$，对于原柿子中的每一个值都可以通过加减乘除得到。

复杂度为 $\Theta(n\log n)$，事实上，其实应该可以不使用线段树就可以进行转移，复杂度如果忽略快速幂（事实上，初始化的 $s_u$ 是可以 $O(1)$ 转移的，逆元可以先与处理出来，然后就没有快速幂了）的话为 $\Theta(n)$，但是得到的代码细节过多，容易错，所以我们~~没有脑子~~地使用线段树维护。

详见代码。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define int long long
#define PII pair<int,int>
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
using namespace std;
const int N=1e6+5,MOD=1e9+7;
int qpow(int a,int b) {
	int res=1,base=a;
	while(b) {
		if(b&1)
			res=res*base%MOD;
		base=base*base%MOD; b>>=1;
	}
	return res;
}
int head[N],len;
struct node {
	int to,nxt;
}; node edge[N<<1];
void add_edge(int u,int v) {
	edge[++len]={v,head[u]}; head[u]=len;
}
int dfn[N],g[N],siz[N],d[N],p;
void dfs(int u,int fa) {
	dfn[u]=++p; g[p]=u; siz[u]=1; d[u]=d[fa]+1;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(v!=fa) {
			dfs(v,u); siz[u]+=siz[v];
		}
	}
}
struct seg {
	int l,r,val,tag;
}; seg tree[N<<2];
#define ls(k) (k<<1)
#define rs(k) (k<<1|1)
void push_up(int k) {
	tree[k].val=(tree[ls(k)].val+tree[rs(k)].val)%MOD;
}
void push_down(int k) {
	int t=tree[k].tag;
	tree[ls(k)].val=tree[ls(k)].val*t%MOD; tree[ls(k)].tag=tree[ls(k)].tag*t%MOD;
	tree[rs(k)].val=tree[rs(k)].val*t%MOD; tree[rs(k)].tag=tree[rs(k)].tag*t%MOD;
	tree[k].tag=1;
}
void build(int k,int l,int r) {
	tree[k]={l,r,0,1};
	if(l==r) {
		tree[k].val=qpow(2,d[g[l]]); return;
	}
	int mid=(l+r)>>1;
	build(ls(k),l,mid);
	build(rs(k),mid+1,r);
	push_up(k);
}
void update(int k,int l,int r,int val) {
	if(l<=tree[k].l&&tree[k].r<=r) {
		tree[k].val=tree[k].val*val%MOD; tree[k].tag=tree[k].tag*val%MOD; return;
	}
	push_down(k);
	if(l<=tree[ls(k)].r)
		update(ls(k),l,r,val);
	if(r>=tree[rs(k)].l)
		update(rs(k),l,r,val);
	push_up(k);
}
int query(int k,int l,int r) {
	if(l<=tree[k].l&&tree[k].r<=r)
		return tree[k].val;
	push_down(k);
	int ans=0;
	if(l<=tree[ls(k)].r)
		ans=(ans+query(ls(k),l,r))%MOD;
	if(r>=tree[rs(k)].l)
		ans=(ans+query(rs(k),l,r))%MOD;
	return ans;
}
int f[N],n;
void dfs2(int u,int fa) {
	int x=(query(1,1,n)-2+MOD)%MOD;
	f[u]=x*x%MOD;
	for(int i=head[u];i;i=edge[i].nxt) {
		int v=edge[i].to;
		if(v!=fa) {
			update(1,1,n,2);
			update(1,dfn[v],dfn[v]+siz[v]-1,qpow(4,MOD-2));
			dfs2(v,u);
			update(1,1,n,qpow(2,MOD-2));
			update(1,dfn[v],dfn[v]+siz[v]-1,4);
			int tmp=query(1,dfn[v],dfn[v]+siz[v]-1);
			f[u]=(f[u]-tmp*tmp%MOD+MOD)%MOD;
		}
	}
	int y=(x+2-query(1,dfn[u],dfn[u]+siz[u]-1)+MOD)%MOD;
	f[u]=qpow(32,MOD-2)*(f[u]-y*y%MOD+MOD)%MOD;
	f[u]=(f[u]+x*qpow(4,MOD-2)%MOD)%MOD;
}
signed main() {
	scanf("%lld",&n);
	rep(i,2,n) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0); build(1,1,n); dfs2(1,0);
	rep(i,1,n)
		printf("%lld ",f[i]);
	return 0;
}
```

---

## 作者：苏联小渣 (赞：2)

这种对每个点求答案的题，一般会考虑两种方法：一种是 dp，常见的有换根 dp；另一种是数据结构，处理子树问题比较常见，比如说线段树合并、拍成序列然后转化成区间问题。这题用的是换根 dp。

我们发现，如果钦定了 $1$ 为根，那么对于每个点，这个点集的其它点可能在子树内，也可能在子树外。这样非常不好计算，所以我们有了一个暴力的思路，就是钦定每个点为根各一遍，这样点集的其它点就一定在子树内了。

我们先考虑一下这个暴力的思路。假定 $r$ 为根，那么这条链有两种情况：以 $r$ 为一个端点，或者两个端点都在子树内，而后者又可以通过两条以 $r$ 为端点的链拼接而成，所以我们只需要考虑以 $r$ 为一个端点的情况。此时我们可以枚举另一个端点 $t$，那么这条链 $(r,t) $ 就唯一确定了。这两个点，我们钦定它们必选，那在这两个点之间的点可选可不选。设 $d_x$ 表示 $x$ 的深度，令 $d_r=1$，那 $(r,t)$ 这条链的贡献就是 $2^{d_t-2}$。

有了这个思路，就可以考虑换根。首先，我们可以把上面求答案的式子化成 dp 方程的形式：设 $f_r(x)$ 表示以 $r$ 为根时，以 $x$ 为一个端点，在 $x$ 的子树里面（不包括 $x$）选 $\ge 1$ 个点，满足这些点在一条链上的方案。根据上面的式子，我们有：

$$f_{r}(x)=\sum_{u \in \text{son}(x)}f_r(u) \times 2+1$$

原因就是当子树顶点从 $u$ 变成 $x$ 时，$u$ 子树内所有点相对 $u$ 的深度都加了一，那么反应到答案上，就是乘了 $2$。加一是因为 $f_r(u)$ 并没有把 $(u,u)$ 本身算入内。

这个时候，我们先来考虑统计以 $r$ 为根时的答案。可以由任意两条链拼接而成，设 $g_r(u)=f_r(u) \times 2+1$，那么就有：

$$ans_r=\sum_{u,v \in \text{son}(r),u \ne v}g_r(u )\times g_r(v)+\sum_{u \in \text{son}(r)}g_r(u)$$

这个可以先统计一下所有 $g_r(u)$ 的和 $s_r$，然后答案就是：

$$ans_r=\sum_{u \in \text{son}(r)} g_r(u) \times (s_r-g_r(u)+1)$$

然后接下来考虑换根。从 $u \to v$ 换根，考虑 $f_u \to f_v$ 的变化。可以发现在方程的定义下，变化的只有 $f_u(u)$ 和 $f_u(v)$。不难得出有：

$$f_v(u) =f_u(u)-(f_u(v) \times 2+1)$$

$$f_v(v)=f_u(v)+f_v(u) \times 2+1$$

其余点 $x$，$f_v(x)=f_u(x)$。

那么这个问题就可以在 $O(n)$ 复杂度求解了。代码中由于算法一开始假了很多次的原因，用 $siz$ 表示题解中的 $f$，用 $f$ 表示题解中的 $ans$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, p, x, y, ans, h[500010], f[500010], siz[500010];
struct node{
	int x, y, next;
}d[1000010];
void add(int x, int y){
	d[++p].y = y, d[p].next = h[x], h[x] = p;
}
const int mo = 1e9 + 7;
void dfs(int x, int fa){
	siz[x] = 0;
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		dfs(y, x);
		siz[x] = (siz[x] + 2LL * siz[y] % mo + 1) % mo;
	}
}
void dfs2(int x, int fa){
	int tot = 0;
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		tot = (tot + 2LL * siz[y] % mo + 1) % mo;
	}
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		int now = (2LL * siz[y] % mo + 1) % mo;
		f[x] = (f[x] + now) % mo;
		f[x] = (f[x] + 1LL * now * (tot - now + mo) % mo) % mo;
		tot = (tot - now + mo) % mo;
	}
	for (int i=h[x]; i; i=d[i].next){
		int y = d[i].y;
		if (y == fa) continue;
		int sx = siz[x], sy = siz[y];
		siz[x] = (siz[x] - 2LL * siz[y] % mo + mo - 1 + mo) % mo;
		siz[y] = (siz[y] + 2LL * siz[x] % mo + 1) % mo;
		dfs2(y, x);
		siz[x] = sx, siz[y] = sy;
	}
}
signed main(){
	scanf ("%lld", &n);
	for (int i=1; i<n; i++){
		scanf ("%lld%lld", &x, &y);
		add(x, y); add(y, x);
	}
	dfs(1, 0);
	dfs2(1, 0);
	for (int i=1; i<=n; i++){
		ans ^= (i * f[i]);
	}
	printf ("%lld\n", ans);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：2)

赛时看着 C 很久不会，一眼了 D 回来秒了 C。挺有趣的，解法貌似优于官方题解的 $O(n\log n)$。


## 题目简述

> - 给定树 $(V,E)$。
> - 定义一个点集 $V'$ 是“连接的”当且仅当存在一条链覆盖 $V'$。
> - 求每个点被多少“连接的”点集覆盖。对 $10^9+7$ 取模。
> - $n\leq 5\times 10^5$。

## 解题思路

下面不妨设 $1$ 为根。

第一眼想到 dp。定义 $f_i$ 表示在 $i$ 子树内当前的链其中一端点为 $i$ 且至少有一个已选点的方案数。不难有转移：
$$
f_u=2\sum_{v\in son} f_v+1
$$
这是因为如果除 $u$ 已有已选点，那么肯定只集中在 $u$ 的一个子树当中，此时的 $u$ 可以选或不选，如果没有那么 $u$ 必须选。

那么我们先看根节点 $1$，他的答案显然是：
$$
\sum_{v\in son} f_v+\sum_{v\not = v'\in son} f_vf_{v'}
$$
这里显然可以维护 $\sum_{v\in son} f_v,\sum_{v\in son} f_v^2$ 做到 $O(|son|)$。

那么对于其他的非根节点就会出现一个问题，这条链到底经不经过父亲，如果经过父亲的话又会很难算。解决这个问题我们可以每个点作为根可以做到 $O(n^2)$。

我们考虑加快速度，我们考虑当前根 $rt$ 换到儿子 $v$ 时发生的变化：

假设当前以 $1$ 为根，我们要把根换到 $2$。

![](https://cdn.luogu.com.cn/upload/image_hosting/vo7tpjla.png)

不难发现只有 $1,2$ 的 $f$ 值需要改变，更具体的，$f'_1\leftarrow f_1-2f_2$ 这是因为减少了一个儿子 $2$ 的贡献，$f'_2$ 按照上面的转移重新计算 $f'$ 即可。

不难发现可以做到 $O(n)$。 

## 参考代码

```cpp
#include<iostream>
#include<vector>
using namespace std;
#define ll long long
const int MAXN=5e5+5;
const int MOD=1e9+7;
int n;
vector<ll> ve[MAXN],st;
ll f[MAXN],tmp[MAXN];
inline int read(){
	int re=0,w=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') re=10*re+ch-'0',ch=getchar();
	return re*w;
}
int dfs(int u,int fa){
	f[u]=1;
	for(int v:ve[u]) if(v!=fa) f[u]+=2*dfs(v,u);
	f[u]%=MOD;
	return f[u];
}
ll get(){
	ll s=0,t=0;
	for(ll i:st)
		s+=i,t+=i*i;
	return (s+(s*s-t)/2)%MOD;
}
void dfs1(int u,int fa){
	st.clear();f[u]=1;
	for(int v:ve[u])
		st.push_back(f[v]),
		f[u]+=2*f[v];
	f[u]%=MOD;tmp[u]=get();
	ll p=f[u];
	for(int v:ve[u])
		if(v!=fa){
			f[u]=(p-2*f[v]+2*MOD)%MOD;
			dfs1(v,u);
		}
	return;
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	dfs(1,0);
	//for(int i=1;i<=n;i++) cout<<f[i]<<" ";cout<<endl;
	dfs1(1,0);
	ll ans=0;
	for(int i=1;i<=n;i++)
		ans^=(i*tmp[i]);
	cout<<ans;
	return 0;
} 
```



---

## 作者：DerrickLo (赞：1)

定义 $f_u$ 表示以 $u$ 为根的子树中以 $u$ 为端点的链的个数。

那么容易得到

$$f_u=\displaystyle{\sum_{v\in son_u}(2\times f_v+1)}$$

设 $ans_u$ 表示整个树的根是 $u$ 的情况下，方案的总数。

则 $ans_u$

$\begin{aligned}
&=f_u+\displaystyle{(\sum_{j\in son_u}\sum_{k\in son_u,k\neq j}(2\times f_j+1)\times(2\times f_k+1))\div 2}\\
&=f_u+\displaystyle{((\sum_{j\in son_u}(2\times f_j+1))^2-\sum_{j\in son_u}(2\times f_j+1)^2)\div 2}
\end{aligned}$

这可以在 $O(n)$ 的复杂度内求出。

那么我们进行一次换根 dp 即可。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
#define add(a,b) ((a)+(b))%mod
#define sub(a,b) (((a)-(b))%mod+mod)%mod
#define mul(a,b) (a)%mod*(b)%mod
using namespace std;
int n,u,v,ans1,f[500005],sum,ans;
vector<int> ve[500005];
void dfs1(int u,int fa){
	for(int v:ve[u]){
		if(v==fa)continue;
		dfs1(v,u);
		f[u]+=2ll*f[v]+1;
		f[u]%=mod;
	}
}
void dfs2(int u,int fa,int anss){
	int ansu=f[u]+2ll*anss+1,sum=0;
	if(u==1)ansu--;
	for(int v:ve[u]){
		if(v==fa)sum=add(sum,2ll*anss+1);
		else sum=add(sum,2ll*f[v]+1);
	}
	sum=mul(sum,sum);
	for(int v:ve[u]){
		if(v==fa)sum=sub(sum,mul(2ll*anss+1ll,2ll*anss+1ll));
		else sum=sub(sum,mul(2ll*f[v]+1ll,2ll*f[v]+1ll));
	}
	sum=mul(sum,500000004ll);
	ansu=add(ansu,sum);
	ans^=ansu*u;
	//cout<<u<<" "<<ansu<<"\n";
	for(int v:ve[u]){
		if(v==fa)continue;
		if(u==1)dfs2(v,u,add(sub(f[u],2ll*f[v]+1),2ll*anss));
		else dfs2(v,u,add(sub(f[u],2ll*f[v]+1),2ll*anss+1ll));
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++)cin>>u>>v,ve[u].emplace_back(v),ve[v].emplace_back(u);
	dfs1(1,-1);
	dfs2(1,-1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：Ericnoi (赞：0)

# P8973 题解

[题目传送门](https://www.luogu.com.cn/problem/P8973)

优雅的 $O(n)$ 换根题解。

# 分析

先考虑 $O(n^2)$ 做法。

合法点集的定义与题目中的连接点集类似，只不过要求点的数量 $\ge 1$ 即可。

定义 $dp_{u}$ 为在子树 $u$ 中，一共有多少个**包含** $u$ 的合法点集。转移方程是是显然的：

$$dp_{u} = \sum_{v \in son(u)}(2 \times dp_{v} - 1) + 1$$

其中 $2 \times dp_v + 1$ 表示的是在子树 $v$ 中，**不一定包含** $v$ 的合法点集。

最后，对于每一个根 $rt$，进行以上的状态转移并计算答案。为了简化方程，令 $f_{u} = 2 \times dp_{u} - 1$，则答案计算方式如下：

$$ans_{rt} = \sum_{v1,v2 \in son(rt),v1<v2}(f_{v1} \times f_{v2}) + \sum_{v \in son(rt)}f_{v}$$

原因是显然的：既然 $rt$ 一定要选，那么选 $1 \sim 2$ 个子树的**合法点集**自然就能得到题目要求的**连接点集**。

考虑优化到 $O(n)$ 发现。优化是显然的。因为 $dp$ 数组的转移方程是线性的。这意味着我们可以很方便地剥离掉其中一个子树的贡献。于是用经典的两次深搜来进行换根 DP。从 $u$ 的答案转移到 $v$ 的答案时，暂时剥离掉子树 $v$ 的影响，然后把剥离后的子树 $u$ 作为子树 $v$ 的子树加到子树 $v$ 上即可。最后在递归的同时走一遍计算 $ans_{u}$ 的流程。

如此我们便在 $O(n)$ 的时间内，处理出了每一个点作为根的答案。

不要忘了特判 $n = 1$。

# AC Code

```cpp
#include <bits/stdc++.h>
#define pb push_back
// 取模的最高境界是不出现取模
#define add(x, y) (((x) + (y)) % mod)
#define addto(x, y) ((x) = add((x), (y)))
#define minus(x, y) (((x) - (y) + (mod)) % (mod))
#define minusto(x, y) ((x) = minus((x), (y)))
#define times(x, y) ((1ll * (x) * (y)) % (mod))
#define timesto(x, y) ((x) = times((x), (y)))
#define divide(x, y) (times(x, inv(y)))
#define divideto(x, y) ((x) = divide((x), (y)))
#define isnumber(x) (((x) >= '0') && ((x) <= '9'))
using namespace std;
template<typename T, typename = enable_if_t<std::is_same<T, int>::value || is_same<T, long long>::value>>
inline T read(T &x) { 
	T f = 1; x = 0; char s = getchar();
	while(!isnumber(s)) {if(s == '-') f = -1; s = getchar();}
	while(isnumber(s)) x = (x << 1) + (x << 3) + (s ^ '0'), s = getchar();
	return x *= f;
}
inline int read(char* s) {return scanf("%s", s);}
inline double read(double &x) {scanf(REAL_INPUT_FORMAT_STR, &x); return x;}
inline string& read(string& s) {cin >> s; return s;}
template<typename T, typename... Args> inline void read(T& x, Args&... args) {read(x); read(args...);}
inline void print(bool x, char suf = 0) {if(x) putchar('1'); else putchar('0'); if(suf) putchar(suf);}
template<typename T, typename = enable_if_t<std::is_same<T, int>::value || std::is_same<T, long long>::value>>
inline void print(T x, char suf = 0, int base = 10) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x >= base) print(x / base, 0, base);
	putchar(48 ^ (x % base));
	if(suf) putchar(suf);
}
template<typename T, typename = enable_if_t<std::is_same<T, char*>::value || is_same<T, const char*>::value>>
inline void print(T s, char suf = 0) {printf("%s", s); if(suf) putchar(suf);}
inline void print(double x, char suf = 0, int digits = 2) {
	printf(REAL_OUTPUT_FORMAT_STR, static_cast<signed>(digits), x);
	if(suf) putchar(suf);
}
template<typename T> inline void prints(T x) {print(x, '\n');}
template<typename T, typename... Args> inline void prints(T x, Args... args) {print(x, ' '); prints(args...);}
template<typename... Args> inline void print(Args... args) {prints(args...);}
template<typename T> inline void printarr(T a[], int n) {
	int i; for(i = 1 ; i + 8 <= n ; i += 8) {
		print(a[i], ' '); print(a[i+1], ' ');
		print(a[i+2], ' '); print(a[i+3], ' ');
		print(a[i+4], ' '); print(a[i+5], ' ');
		print(a[i+6], ' '); print(a[i+7], ' ');
	}
	while(i <= n) {print(a[i], ' '); i++;}
	putchar('\n');
}
template<typename T> inline void readarr(T a[], int n) {
	int i; for(i = 1 ; i + 8 <= n ; i += 8) {
		read(a[i]); read(a[i+1]);
		read(a[i+2]); read(a[i+3]);
		read(a[i+4]); read(a[i+5]);
		read(a[i+6]); read(a[i+7]);
	}
	while(i <= n) {read(a[i]); i++;}
}
void solve();
signed main() {
    int cx = 1;
    // read(cx);
    while(cx--) {
        solve();
    }
    return 0;
}
const int N = 3e3 + 5;
const int mod = 1e9 + 7;
int n, dp[N];
vector<int> a[N];
long long sum = 0;
void dfs1(int u, int f) {
    dp[u] = 1;
    for(int v : a[u]) {
        if(v == f) continue;
        dfs1(v, u);
        addto(dp[u], minus(times(dp[v], 2), 1));
    }
}
void dfs2(int u, int f) {
    int ans = 0;
    vector<int> vec;
    for(int v : a[u]) {
        vec.pb(minus(times(dp[v], 2), 1));
    }
    for(int i = 1 ; i < vec.size() ; i++) {
        addto(ans, times(vec[i], vec[i-1]));
        addto(vec[i], vec[i-1]);
    }
    addto(ans, vec[vec.size()-1]);
    sum ^= static_cast<long long>(ans) * u;
    for(int v : a[u]) {
        if(v == f) continue;
        minusto(dp[u], minus(times(dp[v], 2), 1));
        addto(dp[v], minus(times(dp[u], 2), 1));
        dfs2(v, u);
        minusto(dp[v], minus(times(dp[u], 2), 1));
        addto(dp[u], minus(times(dp[v], 2), 1));
    }
}
void solve() {
    read(n);
    if(n == 1) {
        puts("0");
        return ;
    }
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        read(u, v);
        a[u].pb(v);
        a[v].pb(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    print(sum, '\n');
}


```

---

