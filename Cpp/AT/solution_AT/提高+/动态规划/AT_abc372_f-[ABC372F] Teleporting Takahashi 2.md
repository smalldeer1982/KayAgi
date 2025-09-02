# [ABC372F] Teleporting Takahashi 2

## 题目描述

有一张有 $N$ 个顶点和 $N+M$ 条边的简单有向图 $G$。顶点从 $1$ 到 $N$ 标号，边从 $1$ 到 $N+M$ 标号。

第 $i(1\le i\le N)$ 条边从 $i$ 连向 $i+1$。（这里的 $N+1$ 号点是 $1$ 号点。）

第 $N+i(1\le i\le M)$ 条边从 $X_i$ 连向 $Y_i$。

高桥在 $1$ 号点。在每个顶点，他可以移动到任何与这个顶点有边相连的点。

计算出他有多少种方式能够移动 $K$ 次。

也就是说，找到满足以下条件的长度为 $K+1$ 的序列 $(v_0,v_1,\dots,v_K)$ 的数量：

- 对于 $i=0,1,\dots,K$，$1\le v_i\le N$。
- $v_0=1$。
- 对于 $i=1,2,\dots,K$ 存在一条从 $v_{i-1}$ 到 $v_i$ 的边。

因为答案可能很大，所以你需要输出答案对 $998244353$ 取模后的值。

## 说明/提示

- $2\le N\le 2\times10^5$
- $0\le M\le 50$
- $1\le K\le 2\times 10^5$
- $1\le X_i,Y_i\le N,X_i\not=Y_i$
- 所有的 $N+M$ 条边都是不同的。
- 所有输入都为整数。

## 样例 #1

### 输入

```
6 2 5
1 4
2 5```

### 输出

```
5```

## 样例 #2

### 输入

```
10 0 200000```

### 输出

```
1```

## 样例 #3

### 输入

```
199 10 1326
122 39
142 49
164 119
197 127
188 145
69 80
6 120
24 160
18 154
185 27```

### 输出

```
451022766```

# 题解

## 作者：BFSDFS123 (赞：11)

感觉并不是很简单 /shuai， 可能是我水平下降太多了。

先考虑一个简单 dp，考虑 $dp_{i,k}$ 表示到第 $k$ 次移动，到 $i$ 号节点的方案数。

显而易见地，会对 $dp_{v,k}$ 作出贡献的有 $dp_{i-1,k-1}$。其中 $i-1$ 可以认为是广义的，即若 $i=1$，$i-1=n$。

对于某些边 $(u,v)$，又有 $dp_{u,k-1}$ 会对 $dp_{v,k}$ 做出贡献。

综上所述，有方程 $dp_{v,k}=dp_{v-1,k-1}+\sum\limits_{(u,v)\in E} dp_{u,k-1}$。

时间复杂度与空间复杂度均较大无法接受。

首先，数组第二维可以滚动数组优化掉。

对于 $dp_{v}=dp_{v-1}$，这是一个整体平移的过程。

对于朴素的 dp，我们每次处理下一时刻时，是对于每条边，在这两个固定的点之间进行更新答案的工作。

我们不妨变换参考系，假设整个 $dp$ 数组不动，让这 $m$ 条边进行移动，每次对 $m$ 条边移动完后的两端节点予以更新答案，就变相完成了平移原 $dp$ 数组，每次再固定的两个节点之间更新答案的任务。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mod=998244353;
const int Maxn=2e5+10;
int dp[Maxn],lst[Maxn];
int n,m,k;
vector<pair<int,int> > vc;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        u--,v--;
        vc.push_back(make_pair(u,v));
    }
    dp[0]=1;
    for(int i=1;i<=k;i++)
    {
        for(auto j:vc)
        {
            int u=j.first,v=j.second;
            v=((v-i)%n+n)%n,u=((u-i+1)%n+n)%n;
            lst[v]=dp[v],lst[u]=dp[u];
        }
        for(auto j:vc)
        {
            int u=j.first,v=j.second;
            dp[((v-i)%n+n)%n]=(dp[((v-i)%n+n)%n]+lst[((u-i+1)%n+n)%n])%Mod;
        }
    }
    int ans=0;
    for(int i=0;i<n;i++)
    {
        ans=(ans+dp[i])%Mod;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Ratio_Y (赞：7)

有点诈骗感的题，可惜赛时没改出来。

---

## 思路

发现 $m\le 50$，而和这 $m$ 条边无关的其他点**只有一条路能走**，这意味着到这些点时只有一种选择，那么我们完全可以将这些点合并到其他有价值的点上去，这样缩完图之后最多只有 $101$ 个点，范围很小，思路就容易出了。

方案这类问题一般采取 dp 的办法。设 $f_{i,j}$ 表示在点 $i$ 花费为 $j$ 的方案数，外层枚举花费，内层枚举缩完后的每个点，根据连边情况转移，状态转移方程为：

$$f_{v,i}+=f_{j,i-w}\ \ \ (i\ge w)$$

其中 $v$ 为与 $j$ 连接的边的终点，$w$ 为边权，复杂度 $\mathcal{O(km)}$。

发现最后有可能停在被合并的点上，于是我们记录每条有缩点的边的边权，最后特殊处理一下即可。

## 细节

缩点上，考虑记录每条边的出度入度，都为 $0$ 的就合并掉，遇到其他的点就遇上一个缩完的点连边，**记得连最后一个点和起点 $1$ 的那条边！**

dp 边界 $f_{1,0}=1$，比较易得，其他就是取模问题等小事了。

## 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define lx ll
inline lx qr()
{
	char ch=getchar();lx x=0,f=1;
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
#undef lx
#define qr qr()
const int Ratio=0;
const int N=2e5+5,NN=105;
const int mod=998244353;
int n,m,k,tot=1;// 缩后图中点个数
int ds[N],rpre[N],ff[NN];
// 每点度数 映射：原点->缩后点 缩点边权
ll f[NN][N],ans;
struct edge{int u,v;}e[55];
int hh[NN],ne[NN<<1],to[NN<<1],w[NN<<1],cnt;
namespace Wisadel
{
    void Wadd(int u,int v,int va)
    {
        to[++cnt]=v;
        w[cnt]=va;
        ne[cnt]=hh[u];
        hh[u]=cnt;
    }
    short main()
    {
        memset(hh,-1,sizeof hh);
        n=qr,m=qr,k=qr;
        for(int i(1);i<=m;i++) e[i].u=qr,e[i].v=qr,ds[e[i].u]++,ds[e[i].v]++;
        rpre[1]=1;
        int ddd=1,las=1;
        for(int i(2);i<=n;i++)
        {
            if(!ds[i]) ddd++;// 没用的点使边权++
            else rpre[i]=++tot,ff[las]=ddd,Wadd(las,tot,ddd),las=tot,ddd=1;
            // 记录有关变量 连边
        }
        Wadd(las,1,ddd),ff[las]=ddd;
        // 处理最后一个点和边
        for(int i(1);i<=m;i++)
        {
            int u=rpre[e[i].u],v=rpre[e[i].v];
            Wadd(u,v,1);
        }
        f[1][0]=1;
        for(int i(1);i<=k;i++) for(int j(1);j<=tot;j++)
        {// dp
            for(int ee=hh[j];ee!=-1;ee=ne[ee])
            {
                int v=to[ee],va=w[ee];
                if(i>=va)
                    f[v][i]=(f[v][i]+f[j][i-va])%mod;
            }
        }
        for(int i(1);i<=tot;i++)
        {
            ans=(ans+f[i][k])%mod;
            for(int j=1;j<=ff[i]-1;j++) ans=(ans+f[i][k-j])%mod;
            // 计算没到缩点的情况的答案
        }
        printf("%lld\n",ans);
        return Ratio;
    }
}
signed main(){return Wisadel::main();}

```


---

完结撒花~

---

## 作者：ddxrS_loves_zxr (赞：6)

题目中给出的 $M$ 很小，我们将被多给出的 $M$ 条边相连的点称为关键点。

除开关键点，其它所有点的状态转移都是相同的，即从 $i-1$ 多走一步走到 $i$。这启示我们可以只把这至多 $2M$ 个关键点单独拿出来跑一边 dp，剩下不是关键点的点都可以最后再通过一次 dp 得出答案。

具体的，我们设 $f_{i,j}$ 表示到达第 $i$ 个关键点用了 $j$ 步的方案数。令 $dis(i,j)$ 表示从第 $i$ 个关键点走到第 $j$ 个关键点的步数，转移有两种：

- $f_{i,j}=f_{i,j}+f_{i-1,j-dis(i-1,i)}$，即直接从第 $i-1$ 个关键点走 $dis(i-1,i)$ 步到 $i$。
- $f_{i,j}=f_{i,j}+\sum f_{k,j-1}$，其中 $k$ 是有边连向 $i$ 的点。也就是从多出来的 $M$ 条边走 $1$ 步到 $i$。

时间复杂度 $O(N+MK)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int mod = 998244353;
int n, m, k, pos[105], turn[200005], cnt;
vector<int> E[400005];
int dist(int x, int y) {return (x < y ? y - x : y + n - x);}
int dp[105][200005], ans;
int main() {
	scanf("%d %d %d", &n, &m, &k);
	pos[++cnt] = 1;
	for(int i = 1, u, v; i <= m; i++) {
		scanf("%d %d", &u, &v);
		E[v].push_back(u);
		pos[++cnt] = u, pos[++cnt] = v;
	}
	sort(pos + 1, pos + cnt + 1);
	cnt = unique(pos + 1, pos + cnt + 1) - pos - 1;
	for(int i = 1; i <= cnt; i++) turn[pos[i]] = i;
	dp[1][0] = 1;
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j <= cnt; j++) {
			int p = j - 1;
			if(p == 0) p = cnt;
			if(i - dist(pos[p], pos[j]) >= 0)
				dp[j][i] = dp[p][i - dist(pos[p], pos[j])];
			for(auto k : E[pos[j]]) {
				dp[j][i] = (dp[j][i] + dp[turn[k]][i - 1]) % mod;
			}
		}
	}
	for(int i = 1; i <= cnt; i++) {
		int j = i + 1;
		if(j == cnt + 1) j = 1;
		for(int p = k; p >= k - dist(pos[i], pos[j]) + 1; p--) ans = (ans + dp[i][p]) % mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：gesong (赞：6)

题目传送门：[[ABC372F] Teleporting Takahashi 2](https://www.luogu.com.cn/problem/AT_abc372_f)。
# 思路

看到这类计数问题，很容易想到 dp，我们设 $f_{i,j}$ 表示我们已经做了 $i$ 步，目前在点 $j$ 的方案数，很明显一开始 $f_{0,1}=1$。

这时候考虑转移：假设点 $k$ 能够到达点 $j$，那么 $f_{i,j}$ 加上 $f_{i-1,k}$，因此转移即为 $f_{i,j}=\sum_{(k,j)\in E} f_{i-1,k}$，最后答案很明显为 $\sum_{i=1}^n f_{n,i}$。

但是这样子做是 $O(nk)$ 的，会超时，我们考虑优化。

因为题目中固定有 $i$ 连向 $i+1$ 的边，我们先将式子拆开，$f_{i,j}=f_{i-1,j-1}+\sum_{(k,j)\in E'}$，其中 $E'$ 为题目中 $m$ 条边组成的集合，特别的当 $j=1$ 时，$f_{i,j}=f_{i-1,n}+\sum_{(k,j)\in E'}$。

我们可以想到这样一种方法转移：首先将 $f_{i,j}=f_{i-1,j-1}$，特别的当 $j=1$ 时，$f_{i,j}=f_{i-1,n}$，然后将 $f_{i,u}$ 加上 $f_{i-1,v}$ 其中 $(u,v)\in E'$。 

这样我们后半部分已经优化成功了，但是前半部分每次依然需要 $O(n)$ 计算，这时如果我们使用滚动数组，每一次计算 $f$ 时都赋值成前一个 $f$ 的向右偏移 $1$ 个单位的结果，但是让无法优化，这时我们可以每次 $f$ 记录的点的编号为前面一个点的编号向右偏移的值，这样我们就可以直接复制下来了，最后我们只需要记录当前的 $1$ 号位置实际的点的编号，在后半部分转移的时候利用分类讨论得到真正的下标，这样我们就将复杂度优化成了 $O(nm)$。

可能写的有点抽象，大家可以结合代码画图理解。

记得取模。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int N=2e5+10,mod=998244353;
int f[N],g[N],n,m,k;
vector<pii >a;
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
inline int get(int x,int c){
	if (c==0) c=n;
	if (x>=c) x=x-c+1;
	else x=x+n-c+1;
	return x;
}
main(){
	n=read(),m=read(),k=read();
	while(m--){
		int x=read(),y=read();
		a.push_back({x,y});
	}
	f[1]=1;
	int c=1;
	for (int i=1;i<=k;i++){
		for (auto i:a){
			int x=i.first,y=i.second;
			g[get(x,c)]=f[get(x,c)],g[get(y,c)]=f[get(y,c)];
		}
		c++;
		if (c==n+1) c=1;
		for (auto i:a){
			int x=i.first,y=i.second;
			f[get(y,c)]=(f[get(y,c)]+g[get(x,c-1)])%mod;
		}
	}
	int ans=0;
	for (int i=1;i<=n;i++) ans=(ans+f[i])%mod;
	cout <<ans;
    return 0;
}
```

---

## 作者：DengStar (赞：3)

（为了方便，文中点的编号从 $0$ 开始。实际上，对于环上的问题，0-indexed 往往都更方便。）

先把问题转化一下：把环断开成链，复制 $(K + 1)$ 层，每走一步就相当于前进一层：

![](https://img.atcoder.jp/abc372/9ee0b5370b9f7611d55ddd9c4dfaec6d.png)

可以想到一个简单的 dp：设 $f(i, j)$ 表示走到第 $i$ 层第 $j$ 个位置的方案数。

- 初始化：$f(0, 0) = 1$，其它均为 $0$，表示 Takahashi 从第 $0$ 层的 $0$ 位置出发。
- 答案统计：$ans = \sum_{i = 0}^{N-1} f(K + 1, i)$。
- 转移：$f(i, u) = \sum_{v \in pre(u)} f(i - 1, v)$，其中 $pre(u)$ 表示能通过一条边直接到达 $u$ 的点的集合。

上述做法的时空复杂度都是 $O(NK)$。由于每层的状态只和前一层有关，我们可以简单地用滚动数组把空间复杂度优化到 $O(N)$，但时间复杂度似乎不太好优化。（[提交记录](https://atcoder.jp/contests/abc372/submissions/58021050)）

突破口在于 $M$。我们先假设 $M = 0$。这时，所有的边都形如 $(i, i + 1)$（在环的意义下），并且所有的点 $u$ 都只能从前一层的 $u - 1$ 这一个位置转移过来，也就是 $f(i, j) = f(i-1, j-1)$。换句话说，我们把 $f(i - 1, *)$ ”右移“一位就得到了 $f(i, *)$：

![](https://img.atcoder.jp/abc372/134e767ca911b74940feaa5d0404958d.png)

这启示我们转移时，不用暴力地赋值 $f(i, *)$，而是用一个变量 $be$ 代表当前数组把哪个下标当作“$1$”，每次转移到下一层，就让 $be \gets (be - 1) \bmod N$ （也就是在环上自减 $1$）。用 $f'$ 表示代码中的数组：一开始在第 $0$ 层，$be = 0$，于是 $f'(0) = f(0, 0), f'(1) = f(0, 1), \dots, f'(N-1) = f(0, N-1)$。转移到第 $1$ 层以后，$be = N-1$，于是 $f'(N-1) = f(1, 0), f'(0) = f(1, 1), \dots, f'(N-2) = f(N-1)$。这样，转移时我们只需更新 $be$，而不用把 $f'$ 全部扫一遍。

当 $M \not= 0$ 时呢？这时，只有 $M$ 条边不是 $(i, i+1)$ 类型的，而 $M \le 50$，因此可以暴力地枚举这些边来转移。

具体实现时，下标转化的细节有点多。此外，为了防止新旧版本的 $f'$ 混淆，我用了 `map` 来存储那些被 $M$ 条边连接的点的值。这使得时间复杂度乘上一个 $\log$，或许更精细的做法可以去掉这个 $\log$，但我感觉用 `map` 方便一些。

时间复杂度 $O(N + KM \log M)$，空间复杂度 $O(N + M)$。

参考代码：

```cpp
vector<int> f(N);
f[0] = 1;
int be = 0;
map<int, int> tmp;
for(int i = 1; i <= K; i++)
{
    tmp.clear();
    be = (be + N - 1) % N;
    for(auto ed: e)
    {
        int u = ed.u, v = ed.v;
        u = (be + 1 + u) % N, v = (be + v) % N;
        // u 表示上一层中 u 的下标，v 表示这一层中 v 的下标 
        if(tmp.find(v) == tmp.end()) tmp[v] = f[v];
        tmp[v] = (f[u] + tmp[v]) % MOD;
    }
    for(auto p: tmp)
        f[p.first] = p.second;
}

int ans = 0;
for(int x: f)
    ans = (ans + x) % MOD;
cout << ans << endl;
```

[提交记录](https://atcoder.jp/contests/abc372/submissions/58021488)

（注：图源：[ATcoder 的官方题解](https://atcoder.jp/contests/abc372/editorial/10991)）

---

## 作者：chenxi2009 (赞：3)

# 题目描述

给定一个简单有向图 $G$，由 $N$ 个点和 $N+M$ 条边组成。点的编号区间为 $[1,N]$，边的编号区间为 $[1,N+M]$。

- $\forall i\in [1,N)$，边 $i$ 连接结点 $i$ 与 结点 $i+1$。
- 边 $N$ 连接点 $1$ 与点 $N$。
- $\forall i\in(N,N+M]$，边 $i$ 连接结点 $X_i$ 与 $Y_i$。

求从点 $1$ 开始，移动 $k$ 次的不同的方案个数。对 $998244353$ 取模。

# 输入格式

共 $M+1$ 行。\
第一行有三个数 $N,M,K$。\
$\forall i\in [2,M+1]$，第 $i$ 行有两个数 $X_i,Y_i$。

# 输出格式

一行一个整数，表示答案对 $998244353$ 取模的值。

# 提示

**数据范围**

$2\le N,K\le 2\times 10^5$\
$0\le M\le50$\
$1\le X_i,Y_i\le N,X_i \ne Y_i$\
保证无重边。输入均为整数。

# 思路

令边 $i$ 的起点与终点分别为 $u_i,v_i$，边集为 $S$。

容易想到一个**初步**的递推：\
用 $f_{i,j}$ 表示行走 $i$ 步，以结点 $j$ 为终点的路径方案数。初始令 $f_{0,1}$ 为 $1$。\
有递推式：

$$
f_{i,j}=\sum_{k\in S,v_k=j}{f_{i-1,u_k}}
$$

这样做的时空复杂度均为 $O(NK)$，优化势在必行。

发现 $M$ 的范围很小，而我们花费了大量时间去处理边 $[1,N]$ 造成的更新。能不能去掉这一部分呢？

发现在边 $[1,N]$ 上行动总是让我们节点编号 $+1$（点 $N$ 走到点 $1$），递推过程中 $f$ 的第一维递增，于是我们压掉一维，用 $f_i$ 表示第 $i$ 步后，以结点 $j-i$（对 $N$ 取模，$0$ 号点即第 $N$ 号点）为终点的方案数。

这样我们发现当用边 $[1,N]$ 更新时，**我们把某个 $f_i$ 的值累加到了 $f_i$ 上**，说白了就是啥也没干，于是就愉快地跳过它们啦！

接下来开动脑筋，对剩下 $M$ 条边的操作略微修改下即可通过此题。

**注意**：压掉一维后可能会出现新数据把原来仍需使用的数据覆盖掉的情况，可以模仿代码中的处理方式解决。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,u[51],v[51],f[200001],nn,gs[200001],las[200001],ans;
const int MOD = 998244353;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	nn = n;
	while(nn < k){//由于前文中 j-i 可能产生负数，我们需要找一个 n 的倍数让它“转正”
		nn <<= 1;
	}
	for(int i = 1;i <= m;i ++){
		scanf("%d%d",&u[i],&v[i]);
	}
	f[1] = 1;
	for(int i = 1;i <= k;i ++){
		for(int j = 1;j <= m;j ++){
			int fr = (u[j] - (i - 1) + nn) % n,to = (v[j] - i + nn) % n;
			if(gs[to] != i){
				gs[to] = i;//标记该数据已更新，上一轮的数据存储在 las 中
				las[to] = f[to];
			}
			if(gs[fr] == i){
				f[to] = (f[to] + las[fr]) % MOD;
			}
			else{
				f[to] = (f[to] + f[fr]) % MOD;
			}
		}
	}  
	for(int i = 0;i < n;i ++){//累加答案
		ans = (ans + f[i]) % MOD; 
	}
	printf("%d",ans);
	return 0; 
}
```

---

## 作者：Lele_Programmer (赞：3)

# AT_abc372_f 题解

## 思路

设 $f_{u,t}$ 为从 $u$ 出发，走 $t$ 步的情况数量。

设 $u$ 可以走到的点是 $v$，则枚举 $v$，然后 $f_{u,t} = \sum f_{v,t-1}$。

然而这样做的时间复杂度是 $\mathcal{O}(NK)$ 的，肯定过不去，考虑寻找突破口。

发现 $0 \le M \le 50$，考虑从这里分析，发现这 $M$ 条边会连接着 $2M$ 个点，其余的点的出边都是连接到下一个点，考虑缩掉这些点，对于这 $M$ 条边，设边权为 $1$，对于环中的其它与这 $M$ 条边无关的点，直接跳过，体现在边权之中，表示距离，比如点 $5$ 和点 $8$ 有被 $M$ 条边其中的某些连接，但 $6,7$ 没有，则直接从 $5$ 连接到 $8$，边权 $3$。

那么状态转移若 $t-w_i \ge 0$，则从 $f_{v,t-w_i}$ 得到，否则只有一种方法，就是沿着这个环走若干步，均与 $M$ 条边无关，则取 $1$。

于是核心部分的时间复杂度 $\mathcal{O}(MK)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
typedef pair<int,int> pii;

const int N=200005;
const int M=1005;
const int K=200005;
const int P=205;
const int mod=998244353;

int n,m,k;
int e[M],w[M],ne[M],h[N],tot;
bool flag[N];
pii edges[M];
vector<int> vec;

unordered_map<int,int> rhs;
int idx;

int f[P][K];

void add(int a,int b,int c) {
    // cout<<a<<" "<<b<<" "<<c<<endl;
    e[tot]=b,w[tot]=c,ne[tot]=h[a],h[a]=tot++;
}

bool cmp(const int& a,const int& b) {
    return a<b;
}

signed main() {
    memset(h,-1,sizeof(h));
    scanf("%lld %lld %lld",&n,&m,&k);
    _rep(i,1,m) {
        int a,b;
        scanf("%lld %lld",&a,&b);
        edges[i]={a,b};
        flag[a]=true;
        flag[b]=true;
    }
    _rep(i,1,n) if (flag[i] || i==1) rhs[i]=++idx,vec.emplace_back(i);
    _rep(i,1,m) add(rhs[edges[i].first],rhs[edges[i].second],1);
    sort(vec.begin(),vec.end(),cmp);
    _rep(i,0,(int)vec.size()-2) add(rhs[vec[i]],rhs[vec[i+1]],vec[i+1]-vec[i]);
    add(rhs[vec.back()],rhs[1],1+n-vec.back());
    _rep(u,1,idx) f[u][0]=1;
    _rep(t,1,k) _rep(u,1,idx) _graph(i,u) f[u][t]=(f[u][t]+((t-w[i]>=0)?f[e[i]][t-w[i]]:1))%mod;
    printf("%lld\n",f[rhs[1]][k]);
    // _rep(t,1,k) _rep(u,1,idx) printf("f[%lld][%lld] = %lld\n",u,t,f[u][t]);
    return 0;
}

/*
10 1 3
1 10
*/

/*
10 1 2
1 5
*/
```

---

## 作者：Redshift_Shine (赞：3)

## 题意

给出一个按标号排序的环，以及 $m$ 条辅助边，求从节点 $1$ 开始走 $k$ 步的方案数。$2\le n\le 2\times 10^5$，$1\le m\le {\color{red}{50}}$，$1\le k\le 2\times 10^5$。

## 思路

本题有显然的 $O(k(n+m))$ 暴力转移思路，但数据范围决定了这是不可行的。考虑优化。

首先考虑 $m=0$ 的情况，即没有辅助边。在这种情况下，不管走几步，高桥君能够抵达的点都是唯一的。

在这种情况下，DP 数组就像是每次向后循环位移了一位。这也正是本题的关键。

设 $d_i$ 为走到节点 $i$ 的方案数。

首先，为了处理方便，不妨将所有节点的标号减 $1$，这样旋转操作可以转化为标号取模操作。

在旋转辅助边的情况下，我们可以忽略对原环上边的转移。边 $(x,y)$ 在第 $t$ 次转移时的实际效果是

$$
d_{(y-t)\bmod n}\to d_{(y-t)\bmod n}+d_{(x-t+1)\bmod n}
$$

原因是，若数组整体向后偏移一位，相对的，在原数组上的位置相应向前偏移一位。由于转移前数组未偏移，所以得到额外方案的位置少偏移一位。

另外，由于所有操作需要同时进行，所以需要缓存值后再操作。

时间复杂度 $O(n+mk)$。

## 代码

```c++
#include <cstdio>
#include <utility>
using namespace std;
const int N = 2e5 + 10, K = 5e1 + 10, mod = 998244353;
int n, m, k, x[N], y[N], dp[N], res;
using pii = pair<int, int>;
pii ad[K];
#define adm(x, y, mod) ((x) + (y) >= (mod) ? (x) + (y) - (mod) : (x) + (y))
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    dp[0] = 1;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", x + i, y + i);
        x[i]--, y[i]--;
    }
    for (int i = 0, p = 1, p2 = 0; i < k; i++, p = adm(p, 1, n), p2 = adm(p2, 1, n))
    {
        for (int j = 1; j <= m; j++)
        {
            ad[j] = {adm(y[j], n - p, n), dp[adm(x[j], n - p2, n)]};
        }
        for (int j = 1; j <= m; j++)
        {
            dp[ad[j].first] = adm(dp[ad[j].first], ad[j].second, mod);
        }
    }
    for (int i = 0; i < n; i++)
        res = adm(res, dp[i], mod);
    printf("%d\n", res);
}

---

## 作者：Segment_Treap (赞：2)

### 题目大意
给定一个有 $n$ 个点和 $n+m$ 条边的有向图，其中点的编号是 $1$ 到 $n$，对于所有 $1 \le i < n$，都有一条边从 $i$ 连向 $i+1$，此外，还有一条从 $n$ 连向 $1$ 的边，和 $m$ 条输入给出的边。求从 $1$ 号点出发沿着边走 $k$ 步，有多少种不同走法，答案对 $998244353$ 取模。
$1 \le n,k \le 2 \times 10^5, 1 \le m \le 50$

### 思路
求方案数可以考虑 dp。$f_{cnt,id}$ 表示从 $id$ 号点出发沿着边走 $cnt$ 步有几种走法，可以得到一个简单的转移方程，即 $f_{cnt,i}$ 可以从 $f_{cnt-1,j}$ 转移过来，$j$ 是 $i$ 连出去的边到达的点，对于所有 $i$，$f_{0,i}=1$。

### 优化
#### 空间优化
直接做空间 $\Theta(nk)$，会 MLE。可以发现，可以转移到 $f_{cnt,i}$ 的只有 $f_{cnt-1,j}$，那么就可以滚动数组优化掉第一维，空间复杂度从 $\Theta(nk)$ 降到了 $\Theta(n)$。
#### 时间优化
直接做时间 $\Theta(nk)$，会 TLE。假设只有 $n$ 条边，没有多余的 $m$ 条边，那么 dp 转移就是
```
1 1 4 5 1 4
```
$\Downarrow$

```
1 4 5 1 4 1
```
手玩几组后可以发现，其实就是循环移位，那么这样每次转移变的最多只有 $2 \times m$ 个点，只要改这几个点的 dp 值就可以了，时间复杂度从 $\Theta(nk)$ 降到了 $\Theta(mk)$。

---

## 作者：Heldivis (赞：2)

## [ABC372F] Teleporting Takahashi 2

> **背景**&emsp;赛时有大佬喊了一声广义串并联图，于是想到这个算法。

先考虑大力暴力：记 $f_{i,j}$ 表示走到第 $i$ 个点，还可以走 $k$ 步的方案路径数。记忆化搜索之，可以做到 $O(NK)$。

注意到 $0\le M\le50$，所以在上述搜索过程中，有大量点是没有用处的，当 $a\to(a+1)\to\dots\to b$ 是一个单纯的链，即其中没有任何一个点有新加的 $M$ 条边，那么 $a\to b$ 的路径是唯一的，不需要进行搜索模拟。

那么考虑将这一串点全部删掉，从 $a$ 向 $b$ 连一条边权是 $b-a$（实际中涉及回头，还要分讨）的边，于是将点数降至 $2M$，在跑上边的暴力，即可做到 $O(MK)$。

另外实现上不要偷懒用 `unordered_map` 做记忆化，否则会 [TLE](https://atcoder.jp/contests/abc372/submissions/58055832)，可以把点编号做个离散化用数组做记忆化。

[AC 记录](https://atcoder.jp/contests/abc372/submissions/58056430)。

---

## 作者：__3E24AC7002AD9292__ (赞：2)

这个题赛时把 $M$ 看成 $20$ 了所以没过，改完过了 QaQ。

虽然 $N$ 很大，但是因为 $M\leq50$，所以可以猜想最多 $100$ 个有用的点我们需要使用。可以考虑建立一个新的图。

容易发现这 $M$ 条边可以构建出更多的环，容易发现这就是在一些环上跑的问题。我们考虑把 $2M$ 个点放在新的图中，把 $M$ 连边和初始环上相邻的点连边并加上边权，跑 $\Theta(MK)$ 的动态规划即可。

```cpp
vis[1]=1,d.push_back(1);
for (int i=1;i<=m;i++){
	int u=read(),v=read();
	b[i]={u,v};
	if (!vis[u]) vis[u]=1,d.push_back(u);
	if (!vis[v]) vis[v]=1,d.push_back(v);
}
sort(d.begin(),d.end());
for (int i=0;i<(int)d.size()-1;i++)
	e[i+1].push_back({i+2,d[i+1]-d[i]});
e[d.size()].push_back({1,d[0]+n-d[d.size()-1]});
for (int i=1;i<=m;i++){
	int u=b[i].fr,v=b[i].sc;
	u=lower_bound(d.begin(),d.end(),u)-d.begin()+1;
	v=lower_bound(d.begin(),d.end(),v)-d.begin()+1;
	e[u].push_back({v,1});
}
n=d.size();
f[1][0]=1;
for (int i=0;i<k;i++)
	for (int j=1;j<=n;j++)
		for (auto t:e[j])
			(f[t.fr][i+t.sc]+=f[j][i])%=M;
int ans=0;
for (int i=k;i<=2*k;i++)
	for (int j=1;j<=n;j++)
		(ans+=f[j][i])%=M;
```

---

## 作者：hhhqx (赞：2)

~~简单易懂易写~~。

考虑一步一步走。要么顺着环走，要么走那 $m$ 条边。

设 $id(k, i) = (i - 1 - k) \bmod n + 1$。

设 $g_{k,id(k, i)}$ 表示走了 $k$ 步走到 $i$ 的方案数。

这样设计下标就不需要管顺着环走了。顺着环走的转移就是直接 $g_{k+1,\cdots} = g_{k,\cdots}$ 整体转移。

如果第 $k$ 步选择走 $m$ 条边，对于边 $(u,v)$，就是 $g_{k,id(k,v)}$ 由 $g_{k-1,id(k-1,u)}$ 转移来。记得转移的时候建临时数组。

实现可以直接省略第一维，具体可以看代码。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using PII = pair<int, int>;

const int MAXN = 2e5 + 3;
const LL mod = 998244353;

int n, m, k;
PII eg[53];
LL dp[MAXN], tmp[MAXN];

int Ri(int t, int i){
  i--;
  return (i + t % n + n) % n + 1;
}
int _Ri(int t, int i){
  i--;
  return (i - t % n + n) % n + 1;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> k;
  for(int i = 1; i <= m; i++){
    cin >> eg[i].first >> eg[i].second;
  }
  dp[1] = 1;
  for(int t = 1; t <= k; t++){
    for(int i = 1; i <= m; i++){
      int U = _Ri(t - 1, eg[i].first), V = _Ri(t, eg[i].second);
      tmp[U] = dp[U];
    }
    for(int i = 1; i <= m; i++){
      int U = _Ri(t - 1, eg[i].first), V = _Ri(t, eg[i].second);
      dp[V] = (dp[V] + tmp[U]) % mod;
    }
  }
  LL ans = 0;
  for(int i = 1; i <= n; i++){
    ans = (ans + dp[i]) % mod;
  }
  cout <<ans;
  return 0;
}

```

---

## 作者：harmis_yz (赞：1)

## 分析

这不是正解，但是实测能过 pwp。

考虑暴力 DP。首先观察到这里有用的点只有 $1$ 号点与 $m$ 条特殊边上的点。因为其它的点是可以通过这些点走普通边到的。定义状态方程 $f_{i,j}$ 表示第 $i$ 步，落在第 $j$ 条特殊边的终点的方案数。

因为 $n$ 步能走一圈，所以有：$f_{i+n,j} \to f_{i+n,j}+f_{i,j}$。对于当前 $i,j$，枚举一个 $k$，表示**下一条**特殊边走到的是 $k$。这说明 $v_j \to x_k$ 的路程只能走普通边。所需步数计算简单，记为 $d$。有：$f_{i+d+1,j} \to f_{i+d+1,j} + f_{i,j}$。

对于答案的计算。如果在第 $i$ 步走到了 $v_j$，那么我们还有 $k-i$ 步要走。钦定第 $j$ 条边是最后一条，这时只能走普通边。所以路径一定。但由于 $n$ 步能走一圈，如果 $i-k \ge n$，那就属于 $f_{i+n,j}$ 了，故答案为：$\sum\limits_{i=k-n+1}^{k} \sum\limits_{j=0}^{m} f_{i,j}$。复杂度 $O(m^2k)$。

## 代码

```
	n=rd,m=rd,k=rd;
	x[0]=y[0]=1,f[0][0]=1;
	for(re int i=1;i<=m;++i) x[i]=rd,y[i]=rd;
	for(re int i=0;i<=k;++i)
		for(re int now=0;now<=m;++now){
			if(i+n<=k) f[i+n][now]=(f[i+n][now]+f[i][now]>=p?f[i+n][now]+f[i][now]-p:f[i+n][now]+f[i][now]);
			for(re int nxt=1;nxt<=m;++nxt){
				int xx=i+1+dis(y[now],x[nxt]);
				if(xx<=k) f[xx][nxt]=(f[xx][nxt]+f[i][now]>=p?f[xx][nxt]+f[i][now]-p:f[xx][nxt]+f[i][now]);
			}
		}
	for(re int i=k;i>=max(0ll,k-n+1);--i)
		for(re int now=0;now<=m;++now) ans=(ans+f[i][now])%p;
	printf("%lld\n",ans);
```

---

## 作者：hzxphy (赞：1)

## 思路
定义 $dp_{i,j}\gets$ 移动 $i$ 次到 $j$ 点的可能数，答案对 $998244353$ 取模。

但是更新显然是 $O((n+m)k)$，考虑优化。

我们发现了一个很抽象的活：对于 $1\le i<n$，可以将 $dp_{p,i}=dp_{p+1,i+1}$，将其并为一个值，可以压缩到 $O(mk)$ 的时间复杂度。
## 注意
本题虽然没有自环，但是存在重边，所以拿一个 $tmp$ 数组存出需要增加的值避免重边导致修改倍增。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
const int MAXN=2e5;
int n,m,k;
pair<long long,long long>E[52];
long long dp[2*MAXN+10],tmp[52];
int main(){
    cin>>n>>m>>k;m++;
    E[1]=(make_pair(n,1));
    for(int i=2;i<=m;i++){
        cin>>E[i].first>>E[i].second;
    }
    dp[k]=1;
    for(int i=k-1;i>=0;i--){
        for(int j=1;j<=m;j++){
            tmp[j]=dp[i+E[j].first];
        }
        for(int j=1;j<=m;j++){
//            cout<<i+E[j].second-1<<' '<<i+E[j].first<<'\n';
            dp[i+E[j].second-1]=(dp[i+E[j].second-1]+tmp[j])%mod;
        }
//        cout<<"***\n";
    }
    long long ans=0;
    for(int i=0;i<n;i++){
        ans=(ans+dp[i])%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：mmbbyy (赞：0)

**本人做法为记忆化搜索 $+$ 建图优化，比较好理解**

首先我们发现，题目给的图具有一些特殊性质：这张图大部分是一个环，在环的中间加入很少一些横跨的边。

那么我们先不考虑特殊性质，就考虑随机给我们一张图，我们如何暴力地做。首先我们想到最暴力的搜索，就是从一号点开始直接搜索 $k$ 步（也就是控制搜索的层数，搜够了步数就回溯），每一步选择不同的点到达。

此时可以发现，这是可以进行记忆化优化的。具体而言，如果我们之前对于一个点（设为 $y$），把从 $y$ 点出发走 $ky$ 步的答案记录下来，保存在 $dp[y][ky]$ 中，那么如果现在对于一条从 $x$ 到 $y$ 的边，如果我们需要用到从 $y$ 点出发走 $ky$ 步的数据，则我们可以不用再次重复地搜索，直接从 $dp[y][ky]$ 中取出相应的值就行了。

可是我们发现这样做时间复杂度和空间复杂度都是 $O(nk)$ 的，无法接受。于是我们考虑题目给我们的特殊性质。

我们发现对于题目给的图，大体就是一个环。以下我们称每条横跨的非环边对应的两个点为特殊点，其他点称为环点（显然环点只有一个入度和一个出度）。对于一条环边 $x\to y$，$dp[x][kx]$ 的值就等于 $dp[y][kx-1]$ 的值，只有沿着环边走到一个特殊点z才有转移：$dp[z][kz]=\sum_s dp[s][kz-1]$（$s$ 为 $z$ 指向的点）。所以我们可以这样优化建图：

对于特殊边，直接建边一条长度为 1 的边。然后从 1（因为我们要求 $dp[1][k]$，所以要强制其为特殊点）开始，顺时针找到下一个特殊点，在这两个特殊点 $i$，$j$ 中，建一条 $j\to i$ 为长度的边。这样我们的点数就变成了 $O(m)$ 了。

最后我们在记忆化搜索的过程中按照暴力的方式进行，就是对于一条 $x\to y$ 长度为 $w$ 的边，判断一下如果 $dep-w<0$ 就直接跳过 $y$ 这个点就行了。时间复杂度就变成了 $O(mk)$ 了！

要注意对于特殊点要进行离散化处理。

其余细节可看代码

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int mod=998244353;

int n,m,k,ys[N],tot;//ys[i]为i这个特殊点离散化后点的编号
vector<pair<int,int>>edge[N];
void add(int x,int y,int z){
    edge[x].push_back({y,z});
}
int Dot[N],cnt;//Dot数组存贮特殊点
int dp[105][N];//注意至少要开2*m+1的空间

void dfs(int x,int dep){
    if(dp[x][dep])return;
    if(dep==0){
        dp[x][dep]=1;
        return;
    }
    for(auto i:edge[x]){
        int y=i.first,z=i.second;
        if(dep-z<0){//搜索中唯一和暴力不同的地方
            (dp[x][dep]+=1)%=mod;
            continue;
        }
        dfs(y,dep-z);
        (dp[x][dep]+=dp[y][dep-z])%=mod;
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        if(!ys[x])ys[x]=++tot,Dot[++cnt]=x;
        if(!ys[y])ys[y]=++tot,Dot[++cnt]=y;
        add(ys[x],ys[y],1);
    }
    if(!ys[1]){//强制1为特殊点
        Dot[++cnt]=1;
        ys[1]=cnt;
    }
    sort(Dot+1,Dot+1+cnt);
    for(int i=1;i+1<=cnt;i++){
        add(ys[Dot[i]],ys[Dot[i+1]],Dot[i+1]-Dot[i]);
    }
    add(ys[Dot[cnt]],ys[Dot[1]],n-Dot[cnt]+1);//最后一个特殊点连向1这个点连边时要注意长度的计算细节
    dfs(ys[1],k);
    printf("%d",dp[ys[1]][k]);
    return 0;
}
```
Hope this can help you!

---

## 作者：WuMin4 (赞：0)

# 题意

给出一个 $n$ 个点的有向图，点 $i$ 连向点 $(i+1)$，点 $n$ 连向点 $1$。再给你 $m$ 条额外边。你的初始位置为 $1$，问你移动 $k$ 步的不同方案数（仅当路径不同时两个方案不同）。

# 思路

先想怎样暴力转移，显然移动 $k$ 步到达一个点的方案数为所有跟这个点连边的移动 $(k-1)$ 步到达的点的方案数的总和，时间复杂度 $O((n+m)k)$，显然不能接受。\
可以发现 $m\le 50$，考虑优化掉 $n$。最开始的 $n$ 条初始边构成了一个环，所以每个点 $i$ 都一定会从 $(i-1)$ 转移过来，也就是环上的数整体右移一位。我们换位思考，不去右移环上的数，而是整体左移一位额外边上的数，时间复杂度就会大大减小了。因为最外圈是个环，所以整体左移额外边虽然会改变连边关系，但是不会改变边的相对位置，对答案不会造成影响。时间复杂度 $O(mk)$，可以通过。\
![](https://cdn.luogu.com.cn/upload/image_hosting/szpzlslb.png)

# 代码

```cpp
#include<bits/stdc++.h>
#define md 998244353
using namespace std;
int n,m,k,num[200005],ANS;
vector<int> t[200005],pt;
int to(int x,int i){//将点x左移i位，注意取模
	return ((x-i-1)%n+n)%n+1;
}
signed main(){
	cin>>n>>m>>k;
	num[1]=1;
	for(int x,y,i=1;i<=m;i++){
		cin>>x>>y;
		if(!t[x].size())
			pt.push_back(x);
		t[x].push_back(y);
	}
	for(int i=0;i<k;i++){//这里先从额外边转移再整体左移，所以i从0开始
		vector<pair<int,int>> cge;
		for(int v:pt)
			for(int v2:t[v])
				cge.push_back({num[to(v,i)],to(v2,i+1)});//因为整体左移，所以从原来的u->v变为了u->(v-1)
		for(pair<int,int> v:cge)
			num[v.second]=(1ll*num[v.second]+v.first)%md;
	}
	for(int i=1;i<=n;i++)
		ANS=(ANS+num[i])%md;
	cout<<ANS;
	return 0;
}
```

---

