# 『MdOI R2』Odyssey

## 题目背景

超越音速的极限，不及瑰丽多变的极光；

微弱的脉冲，开拓原本一片混沌的天地；

沉郁的蓝缓缓闪动，史诗的红迎接巅峰；

血色的夕阳尽头，是将夜的星辰；

夜半的满天星空，也会被来自地狱的硝烟掩盖；

炽红炼狱消逝，只金色遗迹永存。

在这里等待着每一位的，都是一段艰苦而璀璨的旅程。

## 题目描述

若正整数 $a$ 与 $b$ 满足：

- $a$ 与 $b$ 的积是一个正整数的 $k$ 次方，即存在正整数 $c$ 使得 $ab=c^k$。

那么我们称 $(a,b)$ 为一组**完美数对**。

---

有一个包含 $n$ 个结点和 $m$ 条边的**有向无环图**，这张图中的每条边都有权值和长度两个属性。

如果一条路径 $P$ 满足**以下条件之一**，则称其为一条**完美路径**：

- $P$ 中仅包含一条边。

- $P$ 从其起点开始依次为 $e_1, e_2, e_3, \ldots e_p$ 这 $p\ (p\ge 2)$ 条边，对于任意的 $1\leq i\leq p-1$，$e_i$ 的权值和 $e_{i+1}$ 的权值组成完美数对。

你需要求出图中最长完美路径的长度，一条路径的长度定义为这条路径上所有边的长度之和。

## 说明/提示

【帮助与提示】  

为方便选手测试代码，本题额外提供两组附加样例供选手使用。  

[样例输入1](https://www.luogu.com.cn/paste/wx1lz6m2) [样例输出1](https://www.luogu.com.cn/paste/28xe7f0x)      

[样例输入2](https://www.luogu.com.cn/paste/efgwngs5) [样例输出2](https://www.luogu.com.cn/paste/5hcpoayt)   

----

【样例解释】

样例中给出的有向无环图如图所示，其中边上的红色数字为边的权值，黑色数字为边的长度：

![](https://cdn.luogu.com.cn/upload/image_hosting/w6x03ksd.png)

最长完美路径为 $2\to 5\to 3$，因为这两条边的权值 $2$ 和 $18$ 满足 $2\times 18=6^2$，是完美数对，此路径长度为 $5+9=14$。

此外，$2\to 1\to 4\to 3,\ \ 2\to 4\to 3,\ \ 1\to 5\to 3$ 等也是完美路径，但不是最长的。

图中，$2\to 1\to 5\to 3$ 长度为 $15$，是一条更长的路径，但它并不是完美路径，因为前两个边权 $24$ 和 $8$ 的乘积为 $192$，不是正整数的平方，即 $(24,8)$ 不是完美数对。

---

【数据范围】

**本题采用捆绑测试。**

对于 $100\%$ 的数据：$1\leq n\leq 10^5,\ \ 1\leq m\leq 2\times 10^5,\ \ 1\leq k\leq 10,\ \ 1\leq u,v\leq n,\ \ 1\leq w\leq 10^5,\ \ 1\leq l\leq 10^4$。

给出的图**不保证弱连通**，图中从一个点到另一个点**可能**存在多条边，但保证给出的图是有向无环图。

| 子任务编号 | $n\leq$ |     $m\leq$      | $w\leq$ | $k\leq$ |  特殊性质  | 分值 |
| :--------: | :-----: | :--------------: | :-----: | :-----: | :--------: | :--: |
| Subtask 1  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $1$   |     无     | $18$ |
| Subtask 2  |  $10$   |       $10$       |  $100$  |  $2$   |     无     | $12$ |
| Subtask 3  |  $600$  | $1.5\times 10^3$ | $10^3$  |   $2$   |     无     | $10$ |
| Subtask 4  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   | $w$ 为素数 | $15$ |
| Subtask 5  | $10^5$  |  $2\times 10^5$  | $10^5$  |   $2$   |     无     | $15$ |
| Subtask 6  |  $600$  | $1.5\times 10^3$ | $10^3$  |  $5$   |     无     | $10$ |
| Subtask 7  | $10^5$  |  $2\times 10^5$  | $10^5$  |  $10$   |     无     | $20$ |



## 样例 #1

### 输入

```
5 7 2
2 5 2 5
5 3 18 9
2 4 6 7
4 3 6 3
2 1 24 2
1 4 6 8
1 5 8 4```

### 输出

```
14```

# 题解

## 作者：BFqwq (赞：12)

update：有大佬指出我的做法不需要特判，只是数组开小了。

因为在分层图拓扑的时候如果 $x=f_x$ 则相当于建图两遍，故要开双倍数组。

（于是我就省去了一个特判）

----

以一个验题人的身份来发一个题解。

对于每一个数字，由唯一分解定理，可以拆成 $p_1^{a_1}\times p_2^{a_2}\ldots p_s^{a_S}$ 的形式，

其中 $p_i$ 为素数且对于 $i\neq j,p_i\neq p_j$。

然后我们把所有的指数对 $k$ 取模，使得所有指数小于 $k$。

因此我们只需讨论每一个 $a_i$ 都小于 $k$ 的数。

然后我们发现，这样的数中，能与之构成完美数对的数唯一。

举个例子，$k=3$ 时，$16=2^4$，取模后为 $2^1$，也就是 $2$。

而能与 $2$ 构成完美数对且所有指数都小于等于 $2$ 的数只有 $4$。

然后我们记这个数为 $f_i$，例如 $k=3$ 时 $f_2=4$。

我们分别记录下每一个权值的边，然后对每一个 $i$ 和 $f_i$ 跑一次分层图拓扑排序。

然后取最大值即可。

（其实这个题做法有很多，但是对于前面对每个权值的处理这一部分基本是一样的）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register int x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=233333;
const int lim=100000;
struct edge{
	int from,to,nxt,lg;
}e[maxn<<1];
vector<edge>g[maxn];
int n,m,k,f[maxn];
int h[maxn],pri[maxn];
bool vis[lim+5];
void xxs(){
    for(int i=2;i<=maxn;++i){
        if(!vis[i]) pri[++pri[0]]=i;
        for(int j=1;j<=pri[0]&&pri[j]*i<=lim;j++){
            vis[pri[j]*i]=1;
            if(i%pri[j]==0){
                break;
            }
        }
    }
}
void work(int u,int v,int w,int l){
	int res1=1,res2=1;
	for(int i=1;pri[i]*pri[i]<=w;i++) {
		int tmp=0;
		while(w%pri[i]==0){
			tmp++;
			w/=pri[i];
		}
		if(tmp%k){
			for(int j=1;j<=tmp%k;j++){
				res1*=pri[i];
			}
			for(int j=1;j<=k-tmp%k;j++){
				if(res2*pri[i]>lim){
					return;
				}
				res2*=pri[i];
			}
		}
	}
	if(k!=1)res1*=w;
	for(int j=2;j<=k;j++){
		if(res2*w>lim){
			return;
		}
		res2*=w;
	}
	f[res1]=res2;f[res2]=res1;
	g[res1].push_back((edge){u,v,0,l});
}
queue<int> q;
int dp[maxn];
int cnt=1;
void add(int x,int y,int z) {
	e[++cnt].nxt=h[x];
	e[cnt].to=y;
	e[cnt].lg=z;
	h[x]=cnt;
	return;
}
int in[maxn],ans;
void topo(int w){
	while(!q.empty())q.pop();
	for(edge v:g[w]){
		in[v.to+n]++;
		add(v.from,v.to+n,v.lg);
	}
	for(edge v:g[f[w]]){
		in[v.to]++;
		add(v.from+n,v.to,v.lg);
	}
	for(edge v:g[w]){
		if(!in[v.from]) q.push(v.from),in[v.from]=999999999;
	}
	for(edge v:g[f[w]]){
		if(!in[v.from+n]) q.push(v.from+n),in[v.from+n]=999999999;
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].to,l=e[i].lg;
			dp[v]=max(dp[v],dp[u]+l);
			ans=max(ans,dp[v]);
			in[v]--;if(!in[v]) q.push(v);
		}
	}
	for(edge v:g[f[w]]){
		dp[v.from]=dp[v.from+n]=dp[v.to]=dp[v.to+n]=0;
		h[v.from]=h[v.from+n]=h[v.to]=h[v.to+n]=0;
		in[v.from]=in[v.from+n]=in[v.to]=in[v.to+n]=0;
	}
	for(edge v:g[w]){
		dp[v.from]=dp[v.from+n]=dp[v.to]=dp[v.to+n]=0;
		h[v.from]=h[v.from+n]=h[v.to]=h[v.to+n]=0;
		in[v.from]=in[v.from+n]=in[v.to]=in[v.to+n]=0;
	}
	cnt=1;
}
signed main(){
	n=read();m=read();k=read();
	memset(f,-1,sizeof(f));xxs();f[0]=0;
	for(int i=1;i<=m;++i){
		int u=read(),v=read(),w=read(),l=read();
		ans=max(ans,l);
		work(u,v,w,l);
	}
	for(int i=1;i<=lim;i++){
		if(f[i]>=0 && f[i]>=i){
			topo(i);
		}
	}
	print(ans);
    return 0;
}
```


---

## 作者：一扶苏一 (赞：11)

## 【dp】【P6381】『MdOI R2』Odyssey

### Analysis

这里有一个比较暴力不需要分析性质的做法。

首先对 $w$ 分解质因数并把指数对 $k$ 取模，把结果 hash 一下，并记录与其配对的数字的 hash 值。然后套路的进行 DAG 上 dp，用 map 存一下状态即可。

设 $f_{u, i}$ 是以 $u$ 为起点，第一条边的 hash 值为 $i$ 的最长路，转移为

$$f_{u, i} = \max\{f_{v, pi} + l\}$$

其中 $pi$ 是与 $i$ 配对的 hash 值，$v$ 是从 $u$ 出发的 hash 为 $i$ 的边指向的所有节点，$l$ 是对应边的长度。

时间复杂度 $O(m \log w + m \log m + w)$。

### Code

写起来有点码农，为了防止被卡用了双模数 hash。

```cpp
namespace Fusu {

const int maxn = 200005;
const int INF = 2000000005;

void Init();
void Calc();
void GetPrime();
void Topo_sort();
void Make_hash();

void Main() {
  Init();
  GetPrime();
  Topo_sort();
  Make_hash();
  Calc();
}

int n, m, t;
int ind[maxn];
struct Edge {
  int v, w, l, nxt;
};
Edge edge[maxn];
int hd[maxn];
int ecnt;
inline void cont(const int u, const int v, const int w, const int l) {
  auto &e = edge[++ecnt];
  e.v = v; e.w = w; e.l = l; e.nxt = hd[u];
  hd[u] = ecnt;
}

void Init() {
  qr(n); qr(m); qr(t);
  for (int i = 1, u, v, w, l; i <= m; ++i) {
    qr(u); qr(v); qr(w); qr(l);
    cont(u, v, w, l);
    ++ind[v];
  }
}

std::queue<int> Q;
int top;
int topo[maxn];
void Topo_sort() {
  for (int i = 1; i <= n; ++i) if (ind[i] == 0) {
    Q.push(i);
  }
  for (int u, v; !Q.empty(); Q.pop()) {
    topo[++top] = u = Q.front();
    for (int e = hd[u]; e; e = edge[e].nxt) if (--ind[v = edge[e].v] == 0) {
      Q.push(v);
    }
  }
}

int pcnt;
int prm[maxn], pre[maxn];
bool np[maxn];
void GetPrime() {
  const int x = 100000;
  for (int i = 2; i <= x; ++i) {
    if (np[i] == false) {
      prm[++pcnt] = i;
      pre[i] = pcnt;
    }
    for (int j = 1, k = prm[j] * i; j <= pcnt; k = prm[++j] * i) if (k <= x) {
      np[k] = true;
      pre[k] = j;
      if ((i % prm[j]) == 0) break;
    } else {
      break;
    }
  }
}

const int maxh = 2;
const int pmod[] = {998244353, 1000000009};

int dcnt;
std::vector<int> d, cd;
int make_hash(const int x) {
  ll ret = 0;
  for (int i = 0; i < dcnt; ++i) if (cd[i] != 0) {
    (ret += (d[i] ^ 20020924ll) * (cd[i] ^ 20020301ll)) %= pmod[x];
  }
  return ret;
}

int hash[maxh][maxn], ph[maxh][maxn];
void Make_hash() {
  for (int i = 1; i <= m; ++i) {
    d.clear(); cd.clear(); dcnt = 0;
    for (int x = edge[i].w, pp = 0; x != 1; x /= prm[pre[x]]) if (pp == pre[x]) {
      if (++cd[dcnt - 1] == t) cd[dcnt - 1] = 0;
    } else {
      d.push_back(pre[x]);
      cd.push_back(t != 1);
      ++dcnt;
      pp = pre[x];
    }
    for (int j = 0; j < maxh; ++j) {
      hash[j][i] = make_hash(j);
    }
    for (int j = 0; j < dcnt; ++j) if (cd[j]) {
      cd[j] = t - cd[j];
    }
    for (int j = 0; j < maxh; ++j) {
      ph[j][i] = make_hash(j);
    }
  }
}

std::map<std::pair<int, int>, int> f[maxn];
void Calc() {
  std::pair<int, int> k;
  int ans = 0;
  for (int i = n, u = topo[i], v; i; u = topo[--i]) {
    for (int e = hd[u]; e; e = edge[e].nxt) {
      v = edge[e].v;
      k = std::make_pair(hash[0][e], hash[1][e]);
      f[u][k] = std::max(f[u][k], edge[e].l);
      auto j = std::make_pair(ph[0][e], ph[1][e]);
      f[u][k] = std::max(f[u][k], edge[e].l + f[v][j]);
      ans = std::max(ans, f[u][k]);
    }
  }
  qw(ans, '\n');
}

} // namespace Fusu
```



---

## 作者：zzqDeco (赞：9)

好不容易过了这个大佬所谓的智障题，来写一篇题解

我们首先可以发现在我们把每一个数分解质因数过后指数对 $k$ 取模过后得到的数唯一对应一个可以继续走的数，也就是他们的对应质数的指数和为 $k$

然后我们就可以对每一个数分解质因数，找到他对应的下一个数

这里就有人说了，一个大质数的话，他的 $k$ 次方就很大了，就很难存下来了，但是这里可以考虑，**一个数大于值域就不能作为起点的状态出现了,换而言之，就只能作为终点了**，我们直接赋值 `-1` 就行了

由于是有向无环图，我们就可以考虑 DP

当前点的某个状态才能通过边，到达终点的另一个状态，这里的状态也就是上一次经过的边的 $val$

我们这里状态比较大，可以考虑hash，但是我直接用 unordered_map 解决问题

最后考虑一种特殊情况: $k=1$

```cpp
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <queue>

using namespace std;

struct edge
{
  int to,next;
  int win,vin,val;
}e[200010];

int n,m,k;

int head[100010],num;

int ru[100010];

int ans;

queue<int>q;

unordered_map<int,int>map[100010];

int inv(int w)
{
  int ans=1;
  for(int i=2;i*i<=w;i++)
  {
    int cnt=0;
    while(w%i==0) w/=i,cnt++;
    cnt%=k;
    if(cnt)
    {
      cnt=k-cnt;
      while(cnt--)
      {
        ans*=i;
        if(ans>100000) return -1;
      }
    }
  }
  if(w>1)
  {
    int cnt=k-1;
    while(cnt--)
    {
      ans*=w;
      if(ans>100000) return -1;
    }
  }
  return ans;
}

int yu(int w)
{
  int ans=1;
  for(int i=2;i*i<=w;i++)
  {
    int cnt=0;
    while(w%i==0) w/=i,cnt++;
    cnt%=k;
    while(cnt--) ans*=i;
  }
  if(w>1&&k!=1) return ans*w;
  else return ans;
}

void addedge(int a,int b,int w,int v)
{
  e[++num].to=b;
  e[num].next=head[a];
  e[num].win=yu(w);
  e[num].vin=inv(w);
  e[num].val=v;
  head[a]=num;
}

void topsort()
{
  while(!q.empty())
  {
    int now=q.front();
    q.pop();
    for(int i=head[now];i;i=e[i].next)
    {
      map[e[i].to][e[i].vin]=max(map[e[i].to][e[i].vin],map[now][e[i].win]+e[i].val);
      ans=max(ans,map[e[i].to][e[i].vin]);
      ru[e[i].to]--;
      if(!ru[e[i].to]) q.push(e[i].to);
    }
  }
  printf("%d",ans);
}

int main()
{
  scanf("%d%d%d",&n,&m,&k);
  for(int i=1;i<=m;i++)
  {
    int a,b,w,v;
    scanf("%d%d%d%d",&a,&b,&w,&v);
    addedge(a,b,w,v);
    ru[b]++;
  }
  for(int i=1;i<=n;i++) if(ru[i]==0) q.push(i);
  topsort();
}
```

---

## 作者：YellowBean_Elsa (赞：6)

### 一些 BF 的代码解释：

1. 每次 topo 只是对权值为 $w$ 和 $f_w$ 的边进行（权值默认已进行质因数分解转化），而且图要根据这些边重新建，因为以前 topo 的图留下的边不能存在，因此还要把邻接表 head 和边的编号 cnt 清零。

1. 建图时 $+n$ 是为了防止连续经过 $w$ 或 $f_w$ 的边，所以对于两种边，一种是起点 $+n$，一种是终点 $+n$，这样跑 DAGdp 时就会交错经过两种边。

1. DAGdp 的初始化，把零入度点加入队列时入度赋值为正无穷，是防止它作为其他边的起点时重复把它加入队列。

1. topo 最后要清零，这里BF写的有些多余了，只用这样：

```cpp
dp[e.v]=0;
in[e.v]=in[e.u+n]=0;
head[e.u+n]=0;
```

另一半同理，只是记得 $+n$ 的点变成终点 v。

注意每条边的起点入度也要清零因为有些被赋值成正无穷了。。。

质因数分解就不说了，就是注意算 $f_i$ 时 $>lim$ （边权 w 上限）就要 return，否则送你爆 long long。

对于用了快速幂的玩家，请注意快速幂里面特判有一堆细节，这里不再赘述~~因为没几个人像我这样傻的用快速幂~~

小贴士：不用 xxs 直接枚举来分解质因数也能过，虽然计算量按理会达到 $1.8 \times 10^8$ 左右。

~~自己代码就不贴了，丑死了~~


---

## 作者：under_the_time (赞：1)

## 题意

> 定义 $(a,b)$ 为完美数对，当且仅当存在正整数 $c$ 使得 $ab=c^k$。
>
> 定义一条完美路径 $P$​ 需要满足以下条件之一：
>
> - $P$ 只有一条边。
> - 路径中相邻的两条边的边权为完美数对。
>
> 给定正整数 $k$​ 和一张有向无环图，边有边权和长度，求最长的完美路径的长度（路径上边的长度之和）。

## 解法

~~个人感觉算较难的蓝题。~~

考虑分析完美数对的性质。对于两个数 $a,b$​，如果将 $a,b$​ 进行质因数分解后对应质数的指数和为 $k$​ 的倍数，则一定存在正整数 $c$​ 使得 $ab=c^k$​。我们对这些质因数的指数对 $k$​ 取模，则可以在质因数分解的过程中，快速计算出每条边走到下一条边的边权的值。

这里有两个点：

- 如果下一条边的边权（对所有质因数的指数取模后的边权）大于 $10^5$，即题目中给出的边权最大值，则一定找不到下一条可以走的边。所以这条边一定是一条路径的终点。
- 对于 $k=1$ 的情况，就是求最长路径的长度，不会受到约束。

计算最长完美路径的长度，且原图是张 `DAG`，提示我们使用拓扑排序求解。考虑动态规划，设 $f_{i,j}$ 表示由边权为 $j$ 的边（已经对所有质因数的指数取模后的边权）来到点 $i$ 时的最长完美路径。

拓扑排序中，设 $v$ 从 $u$ 转移，先求出当前边的边权的对应边权 $w1$，和对所有质因数的指数取模后当前边的边权 $w2$；转移方程：$\max(f_{u,w2}+w,f_{v,w1})\to f_{v,w1}$，其中 $w$ 为边的长度（和边权是两个量）。在转移过程中计算答案即可。

## 实现

由于状态比较大而 $n + m$​ 不大，可以用一个 `map` 存状态。$w1,w2$ 的求法可以参考代码中的 `cal1,cal2`。对于 $k=1$ 的特判也可以看代码中的注释。

如果在求 $w1$ 时发现 $w1$ 超过了 $10^5$，因为使用了 `map` 所以可以直接返回 $-1$。

分解质因数 $O(m\log m)$ 级别，拓扑排序（使用 `map`）$O((n+m)\log(n+m))$，总时间复杂度 $O(n\log n)$​ 级别。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5,maxl = 1e5;
struct Edge { int to,nxt,v1,v2,l; } e[maxn << 1];
int n,m,k,head[maxn],tot,d[maxn],ans;
map<int,int> mp[maxn];
int cal1(int w) { // 对应边权
    int res = 1;
    for (int i = 2,cnt;i * i <= w;i ++) {
        cnt = 0;
        while (w % i == 0)
            w /= i, cnt ++;
        cnt %= k; 
        if (cnt) { // 如果 k=1 则不会触发
            cnt = k - cnt;
            while (cnt --) {
                res *= i;
                if (res > maxl) return -1; // 越界返回 -1
            }
        }
    }
    if (w > 1) {
        int cnt = k - 1;
        while (cnt --) { // 如果 k=1 则不会触发
            res *= w;
            if (res > maxl) return -1; // 越界返回 -1
        }
    }
    return res; // 如果 k=1 一定返回 1
}
int cal2(int w) { // 自己边权
    int res = 1;
    for (int i = 2,cnt;i * i <= w;i ++) {
        cnt = 0;
        while (w % i == 0) w /= i, cnt ++;
        cnt %= k;
        while (cnt --) res *= i; // 同上，k=1 不会触发
    }
    if (w > 1 && k != 1) return res * w;
    else return res; // k=1 一定返回 1，这就实现了 k=1 情况的特判
}
void addEdge(int u,int v,int w,int l) {
    e[++ tot].to = v, e[tot].nxt = head[u];
    e[tot].v1 = cal1(w), e[tot].v2 = cal2(w);
    // v1 记录对应边权，v2记录自己边权
    e[tot].l = l, head[u] = tot, d[v] ++;
}
void topo() {
    queue<int> q;
    for (int i = 1;i <= n;i ++)
        if (d[i] == 0) q.push(i);
    while (q.size()) {
        int u = q.front(); q.pop();
        for (int i = head[u];i;i = e[i].nxt) {
            int v = e[i].to, w1 = e[i].v1, w2 = e[i].v2;
            mp[v][w1] = max(mp[v][w1],mp[u][w2] + e[i].l); // 转移方程
            // 如果 w1=-1，则视为结尾，因为不会有状态从 w1=-1 的地方转移
            ans = max(ans,mp[v][w1]);
            if (--d[v] == 0) q.push(v);
        }
    }
}
int main() {
    scanf("%d%d%d",&n,&m,&k);
    for (int i = 1,u,v,w,l;i <= m;i ++) {
        scanf("%d%d%d%d",&u,&v,&w,&l);
        addEdge(u,v,w,l);
    }
    topo();
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Ryo_Yamada (赞：1)

一条边能不能走仅取决于走的上一条边（可能没有）。可以考虑记录 $dp_{i,s}$ 表示第 $i$ 个点，到达这个点的边权值质因数分解后状态为 $s$ 的最长路径。（$s_i$ 表示第 $i$ 个质数出现次数 $\bmod k$ 的值）这个状态不好存，可以用 map+vector 实现。

然而我们发现在 $10^5$ 范围内的质数很多，如果都存到 $s$ 中会炸空间。而大于 $\sqrt {10^5}$ 的质数出现次数仅可能是 $0/1$，且仅可能出现一个。所以我们可以考虑用一个 `pair<vector<int>, pair<int, int> >` 来存状态。vector 中存 $\le \sqrt{10^5}$ 的质数出现状态，最后一个 pair 记录是否出现 $> \sqrt{10^5}$ 的质数以及出现次数。（我将 $k=1$ 的情况也记为了没有出现）。而 $\le \sqrt{10^5}$ 的质数只有 $65$ 个，所以这样就能存下了。

原图是个 DAG，所以拓扑的过程中转移即可，注意每条边都可能是起始边，忘记了就卡了 1h。

时间复杂度 $\mathcal O(n + 65m + m \log w + m \log 65m)$。不开 O2 过不了。

map 的复杂度不太会分析，有错误还请指出。

$\text{Code}$：

```cpp
def(N, int, 1e5 + 5)
def(M, int, 105)

struct Edge {
	int v, w, l;
};

int n, m, k, mx;
bool np[M << 2];
int pr[M], cnt;
int deg[N];
vector<Edge> e[N];
map<pair<vector<int>, pii>, int> dp[N];

void init() {
	int lim = sqrt(mx);
	rep(i, 2, lim) {
		if(!np[i]) pr[++cnt] = i;
		for(int j = 1; j <= cnt && i * pr[j] <= lim; ++j) {
			np[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

pair<vector<int>, pii> solve(int x) {
	vector<int> v;
	rep(i, 1, cnt) {
		int cn = 0;
		while(x % pr[i] == 0) {
			x /= pr[i];
			++cn;
		}
		v.pb(cn % k);
	}
	if(x == 1 || k == 1) return mp(v, mp(-1, -1));
	else return mp(v, mp(x, 1));
}

void topo() {
	int ans = 0;
	queue<int> q;
	rep(i, 1, n) if(!deg[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(Edge x : e[u]) {
			int v = x.v, w = x.w, l = x.l;
			--deg[v];
			pair<vector<int>, pii> nw = solve(w);
			To_max(ans, l), To_max(dp[v][nw], l);
			vector<int> vc;
			for(int vl : nw.fi) vc.pb(!vl ? 0 : k - vl);
			if(nw.se.fi != -1) {
				int nwd = dp[u][mp(vc, mp(nw.se.fi, k - nw.se.se))];
				if(nwd) To_max(ans, nwd + l), To_max(dp[v][nw], nwd + l);
			}
			else {
				int nwd = dp[u][mp(vc, mp(-1, -1))];
				if(nwd) To_max(ans, nwd + l), To_max(dp[v][nw], nwd + l);
			}
			if(!deg[v]) q.push(v);
		}
	}
	cout << ans << endl;
}

int main() {
	qread(n, m, k);
	rep(i, 1, m) {
		int u, v, w, l;
		qread(u, v, w, l);
		To_max(mx, w);
		e[u].pb((Edge){v, w, l});
		++deg[v];
	}
	init();
	topo();
	return 0;
}
```



---

## 作者：_Anchor (赞：1)

# 题意

[传送门](https://www.luogu.com.cn/problem/P6381)

# 分析

DP+分解质因数+哈希/map

首先手模一下可以发现这个 $$ab=c^k$$有点性质：

对于$a$和$b$分解质因数得到：

$a=p_1^{x_1}*p_2^{x_2}...*p_n^{x_n}$

$b=p_1^{y_1}*p_2^{y_2}...*p_n^{y_n}$

然后$a,b$一定满足：

$x_1+y_1 \equiv 0 \mod k$

$x_2+y_2 \equiv 0 \mod k$

$...$

$x_n+y_n \equiv 0 \mod k$

即对于任意的$i \in [1,n] ,\exists x_i+y_i \equiv 0 \mod k $且$0 \leq x_i,y_i \leq k*r$，其中$r$是某个上界

于是此时我们可以对所有的边的权值都分解质因数，然后用新的来代替（即对所有指数模$k$），然后可以得到新的权

接下来可以发现满足上述条件的一组两个数都是唯一的，换句话说，就是假设我们现在数为$p$，那么存在且只有**一个**数$q$和$p$一起构成”完美数对“（至于为什么，显而易见，因为$\exists x_i+y_i \equiv 0 \mod k$）

那么接下来我们分层图然后$dp$就行了

设$f_{x,p}$为到达点$x$，且上一条边的边权为$p$的最长路径长度，设$p$在上面的意义下映射为$map[p]$

那么转移就是$f_{y,q}=max(f_{y,q},f_{x,p}*(map[p]==q))$

然后我们发现这个值域太大了，空间开不下...再想到一个数分解质因数过后的质因子个数又不多，所以我们就可以使用$map$或者哈希乱搞就行了

# 代码

代码太丑就不发了$...$



---

## 作者：Fa_Nanf1204 (赞：0)

### 分析：
首先题目中要求求一条最长路，并且其相邻边权的权值满足 $ab=c^k$。

观察该式子的性质，我们可以将每条边的边权质因数分解，并将其指数对 $k$ 取模，那么这样做有什么好处呢，我们发现通过这种方法，就可以很方便的确定其下一条边权的权值，并且是唯一的。那么我们就可以先预处理，之后在 DAG 上跑 dp，即可求出答案。

注意几个细节：若该边权所对应的下一条边权的权值超出了值域，说明这条边一定为终点，下一条边权的权值直接赋值为 $-1$。dp 过程中状态太大，考虑用 map 来转移。
 
详见代码。
### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int n,m,k,in[N],ans;
int solve1(int w){//转化为对应的边权 
	int res=1,cnt=0;
	for(int i=2;i*i<=w;i++){
		cnt=0;
		while(w%i==0) w/=i,cnt++;
		cnt%=k;
		if(cnt){
			cnt=k-cnt;
			while(cnt--){
				res*=i;
				if(res>1e5) return -1;
			} 
		}
	}
	if(w>1){
		int cnt=k-1;
		while(cnt--){
			res*=w;
			if(res>1e5) return -1;
		} 
	}
	return res;
}
int solve2(int w){//将边权转化 
	int res=1,cnt=0;
	for(int i=2;i*i<=w;i++){
		cnt=0;
		while(w%i==0) w/=i,cnt++;
		cnt%=k;
		while(cnt--) res*=i;
	}
	if(k==1) return 1;
	if(w>1) return res*w;
	else return res;
}
struct node{
	int v,w,w1,w2,l;
};
vector<node> g[N];
queue<int> q;
unordered_map<int,int> dp[N];//dp[i][j]表示到达i点时前一条边权为j时的最长路 
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int u,v,w,l;
		cin>>u>>v>>w>>l;
		g[u].push_back({v,w,solve1(w),solve2(w),l});
		in[v]++;
	}
	for(int i=1;i<=n;i++){
		if(in[i]==0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(auto i:g[u]){
			dp[i.v][i.w2]=max(dp[i.v][i.w2],dp[u][i.w1]+i.l);
			if(--in[i.v]==0) q.push(i.v);
			ans=max(ans,dp[i.v][i.w2]);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：COsm0s (赞：0)

我们先从完美数对的定义入手。

对于任意可以组成完美数对的数对 $(a,b)$，我们记其积为 $d$。

将 $d$ 质因数分解，可以发现 $d=p_1^k\times p_2^k\cdots p_t^k$ 的形式。

那么 $a,b$ 必须都要包含 $p_1,p_2\cdots p_t$ 这 $t$ 种质因数，且两者在任意一个 $p_i$ 上的指数之积 $s$ 都能满足 $s \bmod k = 0$。

所以对于数 $a$，其质因子指数都可以对 $k$ 取模。

由此可以看出，指数取模后的 $(a,b)$ 必定唯一对应。

但是对于一个大质数乘积 $a$，对应的 $b$ 会非常大。但是我们知道值域只有 $10^5$，所以 $b>10^5$ 时直接跳过即可。

那么图变成了一个 DAG。拓扑 dp 即可。

可以用 map 存 dp 值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb emplace_back
const int N = 1e5 + 5, base = 17, mod = 998244353;
int n, m, k, maxw = 1e5;
struct {
	int to, nxt, lw, rw, l;
} e[N << 1];
int h[N], in[N], ecnt, ans;
unordered_map<int, int> mp[N];
int getlw(int w) {
	int res = 1;
	for(int i = 2; i * i <= w; i ++) {
		if(w % i) continue;
		int tot = 0;
		while(w % i == 0) w /= i, tot ++;
		tot %= k;
		while(tot) res *= i, tot --;
	}
	if(w > 1 && k > 1) res *= w;
	return res;
}
int getrw(int w) {
	int res = 1;
	for(int i = 2; i * i <= w; i ++) {
		if(w % i) continue;
		int tot = 0;
		while(w % i == 0) w /= i, tot ++;
		if(!(tot %= k)) continue;
		tot = k - tot;
		while(tot) {
			res *= i;
			tot --;
			if(res > maxw) return -1;
		}
	}
	if(w > 1) {
		int tot = k - 1;
		while(tot) {
			res *= w;
			tot --;
			if(res > maxw) return -1;
		}
	}
	return res;
}
void add(int u, int v, int w, int l) {
	e[++ ecnt].to = v;
	e[ecnt].nxt = h[u];
	e[ecnt].lw = getlw(w);
	e[ecnt].rw = getrw(w);
	e[ecnt].l = l;
	h[u] = ecnt;
}
void Topo() {
	queue<int> q;
	for(int i = 1; i <= n; i ++) {
		if(!in[i]) q.push(i);
	}
	while(!q.empty()) {
		int u = q.front();
//		cout << u << '\n';
		q.pop();
		for(int i = h[u]; i; i = e[i].nxt) {
			mp[e[i].to][e[i].lw] = max(mp[e[i].to][e[i].lw], mp[u][e[i].rw] + e[i].l);
			ans = max(ans, mp[e[i].to][e[i].lw]);
			in[e[i].to] --;
			if(!in[e[i].to]) q.push(e[i].to);
		}
	}
}
void Solve() {
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i ++) {
		int u, v, w, l;
		cin >> u >> v >> w >> l;
		add(u, v, w, l);
		in[v] ++;
	}
	Topo();
	cout << ans << '\n';
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) {
		Solve();
	}
	return 0;
}
```

---

## 作者：Day_Tao (赞：0)

### 题目大意

在一个 $n$ 个点 $m$ 条边的图中，边有边权 $w$ 和长度 $l$，找到一条路径 $P$，满足对于任意相邻的两条边之积为一个正整数的 $k$ 次方，并使得长度最大。

### Sol

首先可以发现，要使得两数之积为 $c^k$，那么对于每个数，因子为 $a^k$ 格式是没有贡献的，因为除去只会让最后的 $c$ 减去 $a$。所以我们对边权进行质因数分解，对相同质因子的幂次对 $k$ 取模。约完后可以得到每条边的边权的质因子幂次都小于 $k$。容易发现，现在每条边对应能够满足条件的边的边权情况只有一种了，即 $p_1^{a_1}\times p_2^{a_2}\times p_3^{a_3}\times\cdots\times p_q^{a_q}$ 只能对应 $p_1^{k-a_1}\times p_2^{k-a_2}\times p_3^{k-a_3}\times\cdots\times p_q^{k-a_q}$。这样就可以想到在 DAG 上拓扑排序 + DP。设 $w$ 为约完之后的边权，$inv$ 为 $w$ 所对应的边权，$f_{i,j}$ 表示到了点 $i$，当前枚举边的边权为 $j$，则可以得到转移方程 $f_{v,w}=\max(f_{v,w},f_{u,inv}+l)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 5;
int n,m,k,in[MAX],cnt,ans;
unordered_map<long long,int>f[MAX];
struct Day_Tao
{
	int v,w;
	long long inv; // inv 可能会很大，要开 long long！！！ 
	int l;
};
vector<Day_Tao>e[MAX];
queue<int>q;
inline void DayTao(int&w,long long&inv) // 处理 w 和 inv 的部分 
{
	if(k==1)
	{
		w=inv=1; // 特判 k = 1 的情况 
		return ;
	}
	int res=1,ww=w; // res 来记录约完之后的 w 
	inv=1;
	for(int i=2;i*i<=ww;i++) // 分解质因数，并把幂次取模 
	{
		int cnt=0;
		while(w%i==0)
			w/=i,cnt++;
		cnt%=k;
		if(cnt==0)
			continue;
		for(int j=1;j<=cnt;j++)
			res*=i;
		for(int j=1;j<=k-cnt;j++)
			inv*=i;
	}
	if(w!=1) 
	{
		res*=w;
		for(int i=1;i<k;i++)
			inv*=w;
	}
	w=res;
	return ;
}
signed main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++)
	{
		int u,v,w,l;
		long long inv;
		scanf("%d%d%d%d",&u,&v,&w,&l);
		DayTao(w,inv);
		e[u].push_back({v,w,inv,l}),in[v]++;
	}
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty()) // 拓扑排序
	{
		int u=q.front();
		q.pop();
		for(Day_Tao i:e[u])
		{
			int v=i.v,w=i.w,l=i.l;
			long long inv=i.inv;
			f[v][w]=max(f[v][w],f[u][inv]+l); // DP 转移 
			ans=max(ans,f[v][w]);
			in[v]--;
			if(!in[v])
				q.push(v);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

### END

---

## 作者：Moeebius (赞：0)

> 部分题解感觉做麻烦了啊，是不是直接做就好了！

把边权放入状态，记 $f_{i,j}$ 表示 $i$ 出发，第一条边边权是 $j$ 的最长路，容易发现总状态数就是 $O(m)$ 的。实现的时候拿个 ```map``` 记录一下即可。

$k=1$ 的时候直接跑，否则把每个权值分解质因数，指数对 $k$ 取模，那么已知 $a$ 可以直接算出形成完美数对的 $b$。这样转移只有 $O(m)$ 种。然后 DAG 上 $\text{DP}$ 做完了。

代码非常好写，不放了。

---

## 作者：船酱魔王 (赞：0)

## E. commander

### 题意回顾

找到有向无环图上边权和最大的相邻两条边标记乘积为完全 $ k $ 次方数的路径，输出其边权。

### 算法 1

$ k=1 $ 为 DAG 最长路问题模板。

期望得分 18 分。

### 算法 2

如果暴力枚举上一个点的所有入边，暴力判断幂次可行性并转移，可以获得 20 分。

### 算法 3

标记为素数时问题简化，$ k=2 $ 时只需要两个标记相等即可，考虑用 `std::map<int, int> mp` 中的 `mp[i][j]` 表示 $ i $ 点入边标记为 $ j $ 的最大边权和。

期望得分 15 分。

结合上述算法共计可以获得 53 分高分。

### 算法 4

考虑刻画一些数论性质：

* 对于 $ k $ 次方数 $ x $ 质因数分解分解 $ x=\prod_{i=1}^{t}a_t^{p_t} $，$ p_t $ 都是 $ k $ 的倍数，因此如果把所有 $ p_t $ 对 $ k $ 取模，$ p_t $ 均等于 $ 0 $，故考虑在模意义下处理 $ p_t $。

* 对于两个数的乘积，质因数分解为他们的所有对应质因子的幂次加和，显然如果乘积为 $ k $ 次方数，相邻边的标记值在因子指数模 $ k $ 意义下的分解可以唯一确定，这样的话可以用类似于算法 3 的方法用 `map` 辅助转移。

考虑用进制哈希表示因子指数模 $ k $ 意义下的分解，预处理出每个标记本身的哈希值合法相邻边的哈希值。

期望得分 100 分。

### 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#define ull unsigned long long
using namespace std;
const int N = 1e5 + 5;
const int base = 131;
int n, m, x;
map<ull, ull> inv;
struct node {
	int v;
	ull w;
	int l;
};
int ind[N];
ull ksm[N];
vector<node> g[N];
map<ull, int> mp[N];
queue<int> que;
int main() {
	ksm[0] = 1;
	for(int i = 1; i <= 100000; i++) {
		ksm[i] = ksm[i - 1] * base;
	}
	scanf("%d%d%d", &n, &m, &x);
	int u, v, w, l;
	int ans = 0;
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%d%d", &u, &v, &w, &l);
		ull th, iv;
		th = iv = 0;
		for(int j = 2; j * j <= w; j++) {
			if(w % j == 0) {
				int ct = 0;
				while(w % j == 0) w /= j, ct++;
				ct %= x;
				if(ct > 0) th += (ull)ct * ksm[j], iv += (ull)(x - ct) * ksm[j];
			}
		}
		if(w > 1 && x > 1) th = th + (ull)ksm[w], iv = iv + (ull)(x - 1) * ksm[w];
		inv[th] = iv;
		g[u].push_back((node){v, th, l});
		ind[v]++;
	}
	for(int i = 1; i <= n; i++) {
		if(!ind[i]) que.push(i);
	}
	while(!que.empty()) {
		int u = que.front();
		que.pop();
		for(int i = 0; i < g[u].size(); i++) {
			int v = g[u][i].v;
			ull w = g[u][i].w;
			int l = g[u][i].l;
			mp[v][w] = max(mp[u][inv[w]] + l, mp[v][w]);
			ans = max(mp[v][w], ans);
			ind[v]--;
			if(!ind[v]) que.push(v);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

### 总结

本题考察 `map` 的使用和数论性质的刻画与哈希的使用。

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

每条边有两个边权 $w$ 和 $l$，两条边可以先后走，当且仅当 $w_u \times w_v = c ^ k （c \in \Z^{+}）$，求 $l$ 为边权的最长路径长度。

### 题目分析

我们观察两个数 $a \times b = c ^ k$，首先因式分解，$a = p_1^{q_1} \times p_2^{q_2} \times \dots \times p_{m}^{q_m}, b = p_1^{l_1} \times p_2^{l_2} \times \dots \times p_{m}^{l_m}(q,l \ge 0)$，则 $c = p_1^{q_1+l_1} \times p_2^{q_2+l_2} \times \dots \times p_{m}^{q_m + l_m} = c^k$，所以满足 $\forall i \in [1, m], k \mid q_i+l_i$。

所以我们对于每个边 $u$ 的边权 $w_u = p_1^{q_1} \times p_2^{q_2} \times \dots \times p_m^{q_m}$，则若它想要走到另一边 $v$，$w_v$ 需满足 $w_v = p_1^{l_1 \equiv k - (q_1 \bmod k) \bmod k} \times p_2^{l_2 \equiv k - (q_2 \bmod k) \bmod k} \times \dots \times p_m^{l_m \equiv k - (q_m \bmod k) \bmod k}$，所以我们可以将每个边权映射为 $w_u = p_1^{q_1\bmod k} \times p_2^{q_2\bmod k} \times \dots \times p_m^{q_m\bmod k}$，则其目标边权唯一确定为 $w_v = p_1^{(k - (q_1\bmod k))\bmod k} \times p_2^{(k - (q_2\bmod k))\bmod k} \times \dots \times p_m^{(k-(q_m\bmod k))\bmod k}$。

特别的，对于较大的目标边权，可以直接取模映射，原理类似于哈希（当然也可以写成哈希）。

于是我们对于映射后的边权做有向无环图上 DP 即可。具体的，我们可以定义 $f_{i,j}$ 为 $i$ 点，出边边权为 $j$ 的最长路径长度。对于每条出边，用子结点出边恰好为这条边目标边权的 $f$ 更新即可。

时间复杂度主要瓶颈在分解质因数和算目标边权上，总的时间复杂度为 $\mathcal O(n \log ^ 2 n)$。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#define int long long

using namespace std;

const int N = 1e5 + 5, MOD = 998244353;
int n, m, k, ans, pri[N], pr, lst[N];
bool cnt[N], prime[N];
map <int, int> f[N];
struct node{
    int id, val, a0, a1;
};
vector <node> e[N];

void dfs(int x)
{
    if(cnt[x])  return ;
    cnt[x] = true;
    for(int i = 0;i < e[x].size();i++)
    {
        node y = e[x][i];
        dfs(y.id);
        f[x][y.a1] = max(f[x][y.a1], f[y.id][y.a0] + y.val);
        ans = max(ans, f[x][y.a1]);
        //printf("%lld %lld %lld\n", x, y.a1, f[x][y.a1]);
    }
    return ;
}

inline int qpow(int x, int y)
{
    register int res = 1;
    while(y)
    {
        if(y & 1)   (res *= x) %= MOD;
        (x *= x) %= MOD, y >>= 1;
    }
    return res;
}

signed main()
{
    for(register int i = 2;i <= N-5;i++)
    {
        if(!prime[i])
            pri[++pr] = i, lst[i] = i;
        for(register int j = 1;j <= pr && i * pri[j] <= N-5;j++)
        {
            prime[i*pri[j]] = true;
            lst[i*pri[j]] = pri[j];
            if(i % pri[j] == 0) break;
        }
    }
    scanf("%lld %lld %lld", &n, &m, &k);
    for(register int i = 1, u, v, l, w;i <= m;i++)
    {
        scanf("%lld %lld %lld %lld", &u, &v, &w, &l);
        node ed;
        ed.id = u, ed.val = l, ed.a1 = 1, ed.a0 = 1;
        for(;w > 1;)
        {
            register int tmp = 0, cnt = lst[w];
            for(;lst[w] == cnt;)    tmp++, w /= cnt;
            tmp %= k;
            if(!tmp)    continue;
            (ed.a1 *= qpow(cnt, tmp)) %= MOD;
            (ed.a0 *= qpow(cnt, k - tmp)) %= MOD;
            //printf("%lld %lld %lld\n", tmp, ed.a0, ed.a1);
        }
        if(w)
        {
            (ed.a1 *= w) %= MOD;
            (ed.a0 *= qpow(w, k-1)) %= MOD;
        }
        //printf("%lld %lld\n", ed.a0, ed.a1);
        e[v].push_back(ed);
    }
    for(register int i = 1;i <= n;i++)
        if(!cnt[i])
            dfs(i);
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：lyhqwq (赞：0)

# Solution

简单题。

首先看到幂相关考虑唯一分解定理。

$a=P_1^{\alpha_1}\times P_2^{\alpha_2}\times\cdots\times P_o^{\alpha_o}$

$b=P_1^{\beta_1}\times P_2^{\beta_2}\times\cdots\times P_o^{\beta_o}$

$ab=c^k$ 当且仅当 $\forall i\in[1,o]$，$\alpha_i+\beta_i \equiv 0 \bmod k$。

我们将每条边的权值分解，把指数对 $k$ 取模后用哈希记录，同时记录哪个数与其相乘合法，记为 $g_i$。

接着拓扑排序做 dp，令 $f_{i,j}$ 表示以 $i$ 结尾的路径，最后一条边的哈希值为 $j$ 的最大长度。

$f_{v,i}=\max(f_{v,i},f_{u,g_i}+w)$。

用 map 存状态即可。

# Code
```cpp
#include<bits/stdc++.h>
#define uLL unsigned long long
#define LL long long
using namespace std;
const int N=1e5+5;
const int M=2e5+5;
const int Base=1145141;
struct edge{
    int v,w,nxt;
    uLL val;
}edge[N<<1];
int head[N],cnt;
int n,m,k,tot;
int deg[N];
uLL Pow[N];
int p[N],vis[N],id[N];
queue<int> q;
vector<int> vec;
map<pair<int,uLL>,LL> f;
map<uLL,uLL> g;
void addedge(int u,int v,int w,uLL val){
    edge[++cnt].v=v,edge[cnt].w=w,edge[cnt].val=val,edge[cnt].nxt=head[u],head[u]=cnt;
}
void init(){
    for(int i=2;i<N;i++){
        if(!vis[i]) p[++tot]=i,id[i]=tot;
        for(int j=2*i;j<N;j+=i) vis[j]=1;
    }
}
uLL work(int x){
    uLL h1=0,h2=0;
    for(int i=1;p[i]*p[i]<=x;i++){
        int t=0;
        while(x%p[i]==0) x/=p[i],t++;
        t=t%k;
        h1+=Pow[i-1]*t,h2+=Pow[i-1]*((k-t)%k);
    }
    if(x>1){
        h1+=Pow[id[x]-1]*(1%k);
        h2+=Pow[id[x]-1]*((k-1)%k);
    }
    g[h1]=h2;
    g[h2]=h1;
    return h1;
}
int main(){
    init();
    scanf("%d%d%d",&n,&m,&k);
    Pow[0]=1;
    for(int i=1;i<N;i++) Pow[i]=Pow[i-1]*Base;
    for(int i=1;i<=m;i++){
        int u,v,w,l;
        scanf("%d%d%d%d",&u,&v,&l,&w);
        uLL val=work(l);
        addedge(u,v,w,val);
        deg[v]++;
    }
    LL ans=0;
    for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];i;i=edge[i].nxt){
            int v=edge[i].v,w=edge[i].w;
            uLL val=edge[i].val;
            pair<int,uLL> stv=make_pair(v,val),stu=make_pair(u,g[val]);
            f[stv]=max(f[stv],f[stu]+w);
            ans=max(ans,f[stv]);
            deg[v]--;
            if(!deg[v]) q.push(v);
        }
    }
    printf("%lld\n",ans);
    return 0;
}

```

---

