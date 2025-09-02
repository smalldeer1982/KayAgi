# [AGC062F] Preserve Distinct

## 题目描述

有 $N$ 组牌堆，每组牌堆由写有 $1$ 到 $M$ 之间整数的卡片组成。第 $i$ 个牌堆有 $K_i$ 张卡片，从上到下第 $j$ 张卡片上写的整数为 $A_{i,j}$。

卡片上的整数最初满足以下约束：

- 对于每个整数 $x\ (1\leq x\leq M)$，写有 $x$ 的卡片恰好出现在 $N$ 个牌堆中的两个不同牌堆中，每个牌堆各有一张。
- 每个牌堆最上面一张卡片上的整数互不相同。

对于这 $N$ 个牌堆，可以进行如下操作：

- 选择一个仍有卡片的牌堆，丢弃最上面的一张卡片。但丢弃后，所有仍有卡片的牌堆的最上面一张卡片上的整数必须互不相同。

请你求出最多可以进行多少次操作。

## 说明/提示

### 限制条件

- $2 \leq N \leq M$
- $2 \leq M \leq 2 \times 10^5$
- $1 \leq K_i \leq M$
- $1 \leq A_{i,j} \leq M$
- 对于每个整数 $x\ (1\leq x\leq M)$，$x=A_{i,j}$ 成立的 $i,j$ 组合恰好有 $2$ 个，且这两个 $i$ 互不相同。
- $A_{i,1}\ (1\leq i\leq N)$ 互不相同。
- 输入的所有值均为整数。

### 样例解释 1

一开始对第 $1$ 个牌堆进行操作后，该牌堆的卡片从上到下依次为 $2,3,4$。此时如果再次对第 $1$ 个牌堆操作，则第 $1$ 个和第 $2$ 个牌堆的最上面一张卡片上的整数都会变成 $3$，因此不能再对第 $1$ 个牌堆操作。同理也不能对第 $2$ 个牌堆操作。因此如果一开始对第 $1$ 个牌堆操作，最多只能操作 $1$ 次。如果一开始对第 $2$ 个牌堆操作，最多也只能操作 $1$ 次，所以答案是 $1$。

### 样例解释 2

通过合理操作可以丢弃所有卡片。

### 样例解释 3

有时一次操作都无法进行。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 4
4 1 2 3 4
4 3 2 1 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4 6
2 6 4
3 2 5 3
4 3 1 5 6
3 4 1 2```

### 输出

```
12```

## 样例 #3

### 输入

```
3 3
2 1 2
2 2 3
2 3 1```

### 输出

```
0```

## 样例 #4

### 输入

```
12 40
4 35 39 11 21
7 31 29 16 15 30 32 34
4 21 27 38 40
11 17 28 26 23 33 22 3 36 8 1 20
1 30
4 40 38 24 6
8 8 36 9 10 5 7 20 4
10 5 10 9 3 22 33 23 26 28 17
4 15 16 29 31
11 19 13 12 18 25 2 39 35 7 14 37
3 4 1 14
13 24 27 11 2 25 18 12 13 19 32 37 6 34```

### 输出

```
53```

# 题解

## 作者：Terry2022 (赞：2)

这是官方题解做法。

**题意**：



$n$ 个牌堆，有 $2m$ 张牌，$1\sim m$ 权值的牌各有两张，且同权值的牌不在同一个牌堆中；牌堆顶的牌要求时刻互不相同；现在进行若干次操作，每次选择一个非空牌堆删除牌堆顶，同时要求删除后满足条件，求最多操作多少次。

$2\le n\le m\le 2\times 10^5$

**思路**：

转化为图论模型，对于每一个牌堆，记 $a_i$ 为第 $i$ 个牌堆的堆顶，连接 $i\to O_i$，$O_i$ 中有 $a_i$，得到一个内向基环森林。

对于非基环上的牌堆，很明显可以直接弹空，且直接弹空一定最优，所以剩余的是若干个环。

对于一个环 $p_1,p_2\cdots,p_k$，其一定是以下形态：
$$
\begin{array}{c}
A_{p_1}:&a_{p_1},\cdots,a_{p_k},\cdots\\
A_{p_2}:&a_{p_2},\cdots,a_{p_1},\cdots\\
\vdots&\cdots\\
A_{p_k}:&a_{p_k},\cdots,a_{p_{k-1}},\cdots
\end{array}
$$
只考虑 $a_{p_i},\cdots, a_{p_{i-1}}$ 的部分，连接得到 $X=a_{p_k},\cdots,a_{p_{k-1}},a_{p_{k-1}},\cdots a_{p_{k-2}},\cdots,a_{p_{1}},\cdots a_{p_k}$。

以下提到环不是指 $X$，是指牌堆 $A_{p_1}\sim A_{p_k}$。

考虑什么样的情况可以直接将环弹空：

首先一个简单的情况是 $X$ 中存在一个值 $v$ 使得 $v$ 只在环中出现一次 $(1.1)$：

对于这种情况，通过旋转环使得 $v$ 出现在 $a_{p_k},\cdots,a_{p_{k-1}}$ 中的 $\cdots$ 中，然后不断弹 $p_{k}$ 直到 $v$，此时，剩余部分组成的图是一条链 $p_1\to p_2\to \cdots \to p_k$，可以直接弹空。

简单类推，即使 $v$ 在环中出现两次，而 $v$ 只在 $X$ 中出现一次，仍然可以删空 $(1.2)$：

假设 $v$ 出现在 $a_{p_k},\cdots,a_{p_{k-1}}$ 的 $\cdots $ 中以及 $a_{p_{t}},\cdots,a_{p_{t-1}},\cdots$ 的后一个 $\cdots $ 中，同理，弹空 $a_{1}\sim a_{t-1}$，剩余部分形态如下：
$$
\begin{array}{c}
A_{p_t}:&a_{p_t},\cdots,a_{p_{t-1}},\cdots,v,\cdots\\
A_{p_{t+1}}:&a_{p_{t+1}},\cdots,a_{p_t},\cdots\\
\vdots&\cdots\\
A_{p_k}:&v,\cdots,a_{p_{k-1}},\cdots
\end{array}
$$
$a_{p_{t-1}}$ 只在这个新环上出现一次，根据 $(1.1)$ 可以删空。

如果 $X$ 中出现 $\cdots,x,\cdots,y,\cdots,x,\cdots,y,\cdots$ 的形式，且 $x,y$ 均不是 $a_{p_i}$，也可以删空。

分类，如果 $x,y$ 旋转后同时出现在一个 $p_k$ 中，即以下情况 $(2.1)$：
$$
\begin{array}{c}
A_{p_1}:& a_{p_1},\cdots,a_{p_k},\cdots\\
\vdots&\cdots \\
A_{p_u}:& a_{p_u},\cdots,y,\cdots,a_{p_{u-1}},\cdots\\
\vdots&\cdots \\
A_{p_v}:& a_{p_v},\cdots,x,\cdots,a_{p_{v-1}},\cdots\\
\vdots&\cdots \\
A_{p_k}:& a_{p_{k}},\cdots,x,\cdots,y\cdots,a_{p_{k-1}},\cdots
\end{array}
$$
则可以先删去 $a_{p_k}\sim x$ 之间的数，保留 $x$，然后删空 $p_{1}\sim p_{v-1}$，这样就能转化为 $(1.1)$，即 $y$ 只出现一次。

否则，情况 $(2.2)$ 一定是：
$$
\begin{array}{c}
A_{p_1}:&a_{p_1},\cdots,a_{p_k},\cdots\\
\vdots&\cdots\\
A_{p_u}:&a_{p_u},\cdots,y,\cdots,a_{p_{u-1}},\cdots\\
\vdots&\cdots\\
A_{p_v}:&a_{p_v},\cdots,x,\cdots,a_{p_{v-1}},\cdots\\
\vdots&\cdots\\
A_{p_t}:&a_{p_t},\cdots,y,\cdots,a_{p_{t-1}},\cdots\\
\vdots&\cdots\\
A_{p_k}:&a_{p_{k}},\cdots,x\cdots,a_{p_{k-1}},\cdots
\end{array}
$$
此时，对 $p_k$ 进行弹堆，直到 $x$，然后删空 $p_1\sim p_{v-1}$，剩余的 $y$ 只出现一次，转化为 $(1.1)$。

去除能够删空的牌堆后，剩余的环一定形如：
$$
\begin{array}{c}
A_{p_1}:&a_{p_1},x,a_{p_k},\cdots\\
A_{p_2}:&a_{p_2},x,a_{p_1},\cdots\\
A_{p_3}:&a_{p_3},y,a_{p_2},\cdots\\
\vdots& \cdots\\
A_{p_{k-1}}:&a_{p_{k-1}},z,a_{p_{k-2}},\cdots\\
A_{p_k}:&a_{p_k},y,z,a_{p_{k-1}},\cdots
\end{array}
$$
这样的环是无法删空的，最终得到的剩余部分一定是：
$$
\begin{array}{c}
B_{q_1}:&b_{q_1},b_{q_t},\cdots\\
B_{q_2}:&b_{q_2},b_{q_1},\cdots\\
\vdots & \cdots\\
B_{q_t}:&b_{q_t},b_{q_{t-1}},\cdots
\end{array}
$$
因为只有这样的情况才不能继续删除。

注意到如果 $b_{q_1}$ 确定，则 $b_{q_k}$ 也会确定，可以进一步得到 $B_{q_1}\sim B_{q_t}$，所以考虑直接枚举 $b_{q_1}$，并且判定是否可以通过弹顶操作将 $A$ 转化为 $B$。

首先，$b_{q_i}$ 必须夹在 $a_{q_i}$ 与 $a_{q_{i-1}}$ 之间，同时不能取到 $a_{q_{i-1}}$，因为如果 $b_{q_i}$ 在 $a_{q_{i-1}}$ 以后，则 $q_{i}$ 一定可以被弹空，因为如果无法弹空代表出现 $b_{q_{i}}$ 的另一个位置出现在 $a_{p_{o}}\sim a_{p_{o-1}}$ 之间，这与初始条件（不是情况 $(1.1/1.2)$）矛盾，所以 $b_{q_{i}}$ 必须在 $a_{p_{i}}$ 与 $a_{q_{i-1}}$ 之间，取 $a_{q_{i-1}}$ 时 $b_{q_{i-1}}$ 不合法。

于是可以考虑一个构造，先对 $q_{1}$ 操作，一定可以将其弹至 $b_{q_1}$，这样可以得到 $b_{q_t}$ 在 $b_{q_1}$ 后不在堆头；所以接下来操作 $q_{t}$，得到 $b_{q_t}$，再操作 $q_{t-1}$，$\cdots$，以此类推，最终可以得到 $B$。

最后总结如何得到答案：

建立内向基环森林，对于叶节点可以直接弹空；剩余的环，分别判断是否是情况 $(1.1)/(1.2)/(2.1)/(2.2)$，对于这些情况也可以弹空；如果不符合任意一个情况，确定其无法弹空，枚举 $b_{q_1}$ 的值然后还原出 $B$，对于得到的 $B$ 找到剩余元素最少的一种。

容易证明时间复杂度为 $O(m)$。

**代码**：

代码实现的非常平凡，更优的写法可以看 at 中的一些提交记录

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<vector>
#include<random>
#include<climits>
const int Q=200005;
const int INF=(1<<30);
typedef long long ll;
typedef unsigned long long ull;
#define rg register int
#define cint const register int
char ibuf[1<<21],*IP1=ibuf,*IP2=ibuf;
#define gc() (__builtin_expect(IP1==IP2,0)&&(IP2=(IP1=ibuf)+fread(ibuf,1,1<<21,stdin),__builtin_expect(IP1==IP2,0))?EOF:*IP1++)
#define pc putchar
inline bool ig(const char c){return c>=48&&c<=57;}
inline void read(rg&oi){char c;rg f=1,res=0;while(c=gc(),(!ig(c))&&c^'-');c^'-'?res=(c^48):f=-1;while(c=gc(),ig(c))res=res*10+(c^48);oi=f*res;}
inline void print(rg oi){char io[23];rg l=0;if(oi<0)pc('-'),oi=~oi+1;do io[++l]=(oi%10+48);while(oi/=10);for(;l;--l)pc(io[l]);}
inline void write(cint oi,const char c){print(oi);pc(c);}char _ST_;
int n,m;std::vector<int>a[Q],b[Q],vs[Q];
struct node{int x,y;node()=default;node(cint X,cint Y):x(X),y(Y){}};node p[Q][2];
int nxt[Q],vst[Q],st[Q],sv[Q];
bool isr[Q],is[Q];int cnt[Q],ps[Q];
std::random_device sd;std::mt19937_64 rnd(sd());
std::uniform_int_distribution<ull>rng(0,ULLONG_MAX);
ull v[Q],s[Q];
char _ED_;int main(){
	fprintf(stderr,"memory:%llu MB\n",(&_ST_-&_ED_)>>20);
	read(n);read(m);rg res=m<<1;
	for(rg i=1,k;i<=n;++i){
		read(k);a[i].resize(k);b[i].resize(k);
		vs[i].resize(k);for(rg j=0,x;j<k;++j){
			read(x);a[i][j]=x;
			if(p[x][0].x)p[x][1]=node(i,j),b[i][j]=1;
			else p[x][0]=node(i,j),b[i][j]=0;
		}
	}
	for(rg i=1;i<=n;++i)nxt[i]=p[a[i][0]][b[i][0]^1].x;
//get ring
	rg T=0;for(rg i=1;i<=n;++i)if(!vst[i]){
		++T;rg x=i;for(;!vst[x];vst[x]=T,x=nxt[x]);
		if(vst[x]^T)continue;for(;!isr[x];isr[x]=1,x=nxt[x]);
	}
//solve ring
	for(rg i=1;i<=n;++i)vst[i]=0;
	for(rg i=1;i<=n;++i)if(isr[i]&&!vst[i]){
		rg top=0;for(rg x=i;!vst[x];vst[x]=1,st[++top]=x,x=nxt[x]);
		for(rg j=1;j<=top;++j)is[a[st[j]][0]]=1;
		for(rg j=1;j<=top;++j){
			cint o=st[j];for(rg k=1;k<(int)a[o].size();++k)
			if(is[a[o][k]]){ps[o]=k;break;}
		}
//1.1/1.2
		rg c=0;for(rg j=1;j<=top;++j){
			cint o=st[j];for(rg k=0;k<=ps[o];++k){
				cint t=a[o][k];if(!cnt[t])sv[++c]=t;++cnt[t];
			}
		}
		bool fl=1;for(rg j=1;j<=c&&fl;++j)if(cnt[sv[j]]==1)fl=0;
		for(rg j=1;j<=c;++j)cnt[sv[j]]=0;if(!fl)continue;
//2.1/2.2
//use random xor hash to check if (..x..y..x..y)
		rg cn=0;for(rg j=top;j>=1&&fl;--j){
			cint o=st[j];for(rg k=1;k<ps[o]&&fl;++k){
				cint t=a[o][k];if(!cnt[t])v[t]=rng(rnd),cnt[t]=++cn,s[cn]=s[cn-1]^v[t];
				else{++cn,s[cn]=s[cn-1]^v[t];if(s[cn]^s[cnt[t]-1])fl=0;}
			}
		}
		for(rg j=1;j<=cn;++j)s[j]=0;
		for(rg j=1;j<=c;++j)v[sv[j]]=cnt[sv[j]]=0;if(!fl)continue;
//3
//enumerate b_{q_{i}}
		rg mn=INF;for(rg j=1;j<=top;++j){
			cint o=st[j];for(rg k=0;k<ps[o];++k){
				if(vs[o][k])continue;rg s=0;
				for(rg x=o,y=k;!vs[x][y];){
					s+=(int)a[x].size()-y;vs[x][y]=1;
					const node t=p[a[x][y+1]][b[x][y+1]^1];x=t.x;y=t.y;
				}
				if(mn>s)mn=s;
			}
		}
		res-=mn;
	}
	write(res,'\n');
	return 0;
}
```



---

## 作者：Leasier (赞：0)

~~大家好，我是 cn_translater。~~

这也太人类智慧了吧。除了情况 $1, 2$ 之外都没能独立想到 /ll

------------

很难想到建立以下图论模型：

- 设 $A_{i, j}$ 对应于另一个 $k \neq i$ 中的 $A_{k, l}$，连边 $i \to k$。
- 不难发现这样会得到一棵**基环树**。
- 对于树上的部分，我们可以从叶子开始按深度从大到小删到其对应的环上点，于是树上的部分一定可以删干净。
- 下面讨论各个环上的情况。

考虑这样表述一个环：

- 不妨设环大小为 $k$，环上的第 $i$ 个点编号为 $i$。
- 则我们可以将环 $i$ 表示为 $L_i = [A_{i, 1}, A_{i, 2}, \cdots, A_{i, p_i} = A_{i - 1, 1}, \cdots]$。
- 设 $X$ 为把所有 $[A_{i, 1}, A_{i, 2}, \cdots, A_{i, p_i}]$ 拼起来的结果，$Y$ 为把所有 $L_i$ 拼起来的结果。

一个显然的想法是我们**尽量将环也删空**，下面开始大讨论：
#### 情况 $1$
若存在一个数 $t = A_{i, j} \in X$ 只在 $Y$ 上出现一次，则我们可以先将 $i$ 删到 $p$ 前，然后环转变为一条链，就可以删空了。
#### 情况 $2$
与上一种情况类似地，若存在一个数 $t = A_{i, j} = A_{k, l} \in X, i \neq k, j \leq p_i, l > p_k$ 在 $Y$ 上出现了两次但只在 $X$ 上出现一次，则我们可以类似地删空。
#### 情况 $3$
~~接下来就是一些我也不知道咋想到的情况了。~~

考虑下面这种情况：

- $L_1 = [\cdots]$。
- $\cdots$。
- $L_i = [A_{i, 1}, A_{i, 2}, \cdots, A_{i, a} = y, \cdots, A_{i, p_i}, \cdots]$。
- $\cdots$。
- $L_j = [A_{j, 1}, A_{j, 2}, \cdots, A_{j, b} = x, \cdots, A_{j, p_j}, \cdots]$。
- $\cdots$。
- $L_k = [A_{k, 1}, A_{k, 2}, \cdots, A_{k, c} = x, \cdots, A_{k, d} = y, \cdots, A_{k, p_k}, \cdots]$。
- 需要注意的是这里的环可能经过旋转。

此时我们可以通过执行以下操作删空：

- 删除 $A_{k, 1 \sim c - 1}$。
- 删除 $L_{1 \sim j - 1}$。
- 此时转化为情况 $1$，因为 $A_{k, p_k}$ 出现恰好一次。

于是此时也可以删空。实现时扫一遍每一行 $t$ 作为 $k$，记录前面遇到的 $\forall j < t, \max j$ 和 $\forall j > t, \min j$ 即可。
#### 情况 $4$
考虑下面这种情况：

- $L_1 = [\cdots]$。
- $\cdots$。
- $L_i = [A_{i, 1}, A_{i, 2}, \cdots, A_{i, a} = y, \cdots, A_{i, p_i}, \cdots]$。
- $\cdots$。
- $L_j = [A_{j, 1}, A_{j, 2}, \cdots, A_{j, b} = x, \cdots, A_{j, p_j}, \cdots]$。
- $\cdots$。
- $L_l = [A_{l, 1}, A_{l, 2}, \cdots, A_{l, c} = y, \cdots, A_{l, p_l}, \cdots]$。
- $\cdots$。
- $L_k = [A_{k, 1}, A_{k, 2}, \cdots, A_{k, d} = x, \cdots, A_{k, p_k}, \cdots]$。
- 需要注意的是这里的环也可能经过旋转，也可能出现 $i = j$ 但 $a < b$ 或 $l = k$ 但 $c < d$ 的情况。

此时我们可以通过与情况 $3$ 类似的方式删空。

实现时考虑异或哈希，这样就可以判断当前 $y$ 与后面的 $y$ 之间有无 $x$。
#### 情况 $5$
考虑规约到一个特殊的不能删空的情况：

- $L'_i = [A'_{i, 1}, A'_{i, 2} = A'_{i - 1, 1}, \cdots]$。

考虑暴力枚举 $A'_{i, 1} = A_{p, q}$，则我们可以通过依次找出 $A_{p, q + 1}$ 的另一个出现位置得到 $L'_i$ 中剩下元素的个数。

注意到我们只需要枚举一个形如 $(A'_{1, 1}, A'_{2, 1}, \cdots, A'_{k', 1})$ 的新环中的一个元素，于是总枚举量为 $O(m)$。取所有可能的新环的答案的最小值即可。

综上，时间复杂度为 $O(m)$。

代码：
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

typedef unsigned long long ull;

typedef struct {
	int nxt;
	int end;
} Edge;

const pair<int, int> e(0, 0);
int cnt = 0;
mt19937_64 rnd(time(NULL));
int k[200007], nxtx[200007], nxty[200007], deg[200007], head[200007], loop[200007], refer[200007], bucket1[200007], bucket2[200007], pos[200007];
ull val[200007], xor_sum[200007];
bool vis[200007];
Edge edge[200007];
queue<int> q;
pair<int, int> pr[200007];
vector<int> v1[200007];
vector<bool> v2[200007];
vector<pair<int, int> > v3[200007];

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

int main(){
	int n, m, ans;
	cin >> n >> m;
	ans = m * 2;
	for (int i = 1; i <= n; i++){
		cin >> k[i];
		v1[i].resize(k[i] + 1);
		v2[i].resize(k[i] + 1);
		v3[i].resize(k[i] + 1);
		for (int j = 1; j <= k[i]; j++){
			cin >> v1[i][j];
			if (pr[v1[i][j]] == e){
				pr[v1[i][j]] = make_pair(i, j);
			} else {
				v3[i][j] = pr[v1[i][j]];
				v3[pr[v1[i][j]].first][pr[v1[i][j]].second] = make_pair(i, j);
			}
		}
	}
	for (int i = 1; i <= n; i++){
		nxtx[i] = v3[i][1].first;
		nxty[i] = v3[i][1].second;
		deg[nxtx[i]]++;
		add_edge(i, nxtx[i]);
	}
	for (int i = 1; i <= n; i++){
		if (deg[i] == 0) q.push(i);
	}
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		for (int j = head[cur]; j != 0; j = edge[j].nxt){
			int x = edge[j].end;
			if (--deg[x] == 0) q.push(x);
		}
	}
	for (int i = 1; i <= n; i++){
		if (!vis[i] && deg[i] == 1){
			int cnt = 0;
			bool flag = false;
			for (int j = i; !vis[j]; j = nxtx[j]){
				vis[j] = true;
				cnt++;
				loop[cnt] = j;
				refer[j] = cnt;
			}
			for (int j = 1; j <= cnt; j++){
				for (int x = 1; x <= k[loop[j]]; x++){
					bucket1[v1[loop[j]][x]] = 0;
				}
			}
			for (int j = 1; j <= cnt; j++){
				for (int x = 1; x <= k[loop[j]]; x++){
					bucket1[v1[loop[j]][x]]++;
				}
			}
			for (int j = 1; j <= cnt && !flag; j++){
				int pre = loop[j == 1 ? cnt : j - 1];
				for (int x = 1; x < nxty[pre]; x++){
					if (bucket1[v1[loop[j]][x]] == 1){
						flag = true;
						break;
					}
				}
			}
			if (flag) continue;
			for (int j = 1; j <= cnt; j++){
				for (int x = 1; x <= k[loop[j]]; x++){
					bucket2[v1[loop[j]][x]] = 0;
				}
			}
			for (int j = 1; j <= cnt; j++){
				int nxt = loop[j % cnt + 1];
				for (int x = 1; x <= nxty[loop[j]]; x++){
					bucket2[v1[nxt][x]]++;
				}
			}
			for (int j = 1; j <= cnt && !flag; j++){
				int pre = loop[j == 1 ? cnt : j - 1];
				for (int x = 1; x < nxty[pre]; x++){
					if (bucket1[v1[loop[j]][x]] == 2 && bucket2[v1[loop[j]][x]] == 1){
						flag = true;
						break;
					}
				}
			}
			if (flag) continue;
			for (int j = 1; j <= cnt && !flag; j++){
				int pre = loop[j == 1 ? cnt : j - 1], max_pos1 = 0, max_pos2 = 0;
				for (int x = 1; x < nxty[pre]; x++){
					int y = refer[v3[loop[j]][x].first];
					if (y < j){
						if (max_pos1 > y){
							flag = true;
							break;
						}
						max_pos1 = y;
					} else {
						if (max_pos2 > y){
							flag = true;
							break;
						}
						max_pos2 = y;
					}
				}
			}
			if (flag) continue;
			int id = 0;
			for (int j = 1; j <= cnt; j++){
				for (int x = 1; x <= k[loop[j]]; x++){
					pos[v1[loop[j]][x]] = 0;
				}
			}
			for (int j = cnt; j >= 1 && !flag; j--){
				int pre = loop[j == 1 ? cnt : j - 1];
				for (int x = 2; x < nxty[pre]; x++){
					if (pos[v1[loop[j]][x]] == 0){
						pos[v1[loop[j]][x]] = id + 1;
						val[v1[loop[j]][x]] = rnd();
					} else if ((xor_sum[id] ^ xor_sum[pos[v1[loop[j]][x]]]) != 0){
						flag = true;
						break;
					}
					id++;
					xor_sum[id] = xor_sum[id - 1] ^ val[v1[loop[j]][x]];
				}
			}
			if (flag) continue;
			int min_val = 0x7fffffff;
			for (int j = 1; j <= cnt; j++){
				int pre = loop[j == 1 ? cnt : j - 1];
				for (int x = 1; x < nxty[pre]; x++){
					if (!v2[loop[j]][x]){
						int cur_val = 0;
						for (int y = loop[j], z = x; !v2[y][z]; ){
							pair<int, int> cur;
							cur_val += k[y] - z + 1;
							v2[y][z] = true;
							cur = v3[y][z + 1];
							y = cur.first;
							z = cur.second;
						}
						if (min_val > cur_val) min_val = cur_val;
					}
				}
			}
			ans -= min_val;
		}
	}
	cout << ans;
	return 0;
}
```

---

