# 风暴之眼（Eye of the Storm）

## 题目背景

通过月岛，帝王蟹和天体探测仪，你成功拼合了三个天体科技，接下来你要做的，就是来到风暴之眼的中心，准备那个神秘实验的最后一步。

最终的真相近在咫尺，你能否成功通过这场考验呢？

## 题目描述

天体风暴中的气象瞬息万变。

风暴中的道路构成一棵 $n$ 个结点的**无根树**，第 $i$ 个结点有初始权值 $w_i$（$w_i$ 为 $0$ 或 $1$）和类型 $t_i$。

结点的类型分为两种：$\texttt{AND}$ 型结点和 $\texttt{OR}$ 型结点。

对于 $\texttt{AND}$ 型结点，每一秒结束后它的权值将变为**它与它所有邻居上一秒权值的 $\texttt{AND}$ 和**；

对于 $\texttt{OR}$ 型结点，每一秒结束后它的权值将变为**它与它所有邻居上一秒权值的 $\texttt{OR}$ 和**。

现在，已知从某一时刻起，所有结点的权值都不再发生任何变化，将此时点 $i$ 的权值称为 $a_i$。

现不知每个点的初始权值和类型，只知道最终每个点的权值 $a_i$，求出有多少种可能的初始权值和类型的组合，答案对 $998244353$ 取模。

## 说明/提示

**【样例 1 解释】**

有如下六种初始权值和类型的组合：

1. $((w_1, t_1), (w_2, t_2)) = ((0, \texttt{AND}), (0, \texttt{AND}))$。

2. $((w_1, t_1), (w_2, t_2)) = ((0, \texttt{AND}), (0, \texttt{OR}))$。

3. $((w_1, t_1), (w_2, t_2)) = ((0, \texttt{OR}), (0, \texttt{AND}))$。

4. $((w_1, t_1), (w_2, t_2)) = ((0, \texttt{OR}), (0, \texttt{OR}))$。

5. $((w_1, t_1), (w_2, t_2)) = ((1, \texttt{AND}), (0, \texttt{AND}))$。

6. $((w_1, t_1), (w_2, t_2)) = ((0, \texttt{AND}), (1, \texttt{AND}))$。

---

**【数据范围】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，$2 \le n \le 2 \times {10}^5$，$1 \le x, y \le n$，$a_i \in \{ 0, 1 \}$，保证输入构成一棵树。

| 子任务编号 | 分值 | $n\leq$ | 特殊限制 |
|:-:|:-:|:-:|:-:|
| $1$ | $10$ | $10$ | 无 |
| $2$ | $22$ | $20$ | 无 |
| $3$ | $22$ | $1000$ | 无 |
| $4$ | $11$ | ${10}^5$ | $y=x+1$ |
| $5$ | $15$ | ${10}^5$ | $a_i=0$ |
| $6$ | $20$ | $2 \times {10}^5$ | 无 |

---

![](https://cdn.luogu.com.cn/upload/image_hosting/j4citkld.png)

## 样例 #1

### 输入

```
2
0 0
1 2
```

### 输出

```
6
```

# 题解

## 作者：绝顶我为峰 (赞：7)

树上计数问题一般考虑树形 dp。显然可以按照权值划分出一个森林。

我们考虑一些特殊情况：

- $or1$ 和 $and0$ 的权值是不会变的，因此 $0$ 的联通块中没有 $or1$，$1$ 的联通块中没有 $and0$

- 每个权值划分出的联通块的分界线处的类型是确定的，这是因为权值最终稳定下来，那么必然边界的 $0$ 是 $and$，$1$ 是 $or$，否则会将相邻块的权值传递过去。

- 同一个联通块内 $and1$ 和 $or0$ 不能相邻，因为一步之后这两个节点会变成 $and0$ 和 $or1$，必然不满足题意。

有了这些结论我们就可以 dp 了，记 $dp_{i,0/1/2/3}$ 分别表示当前点选四种类型的节点的合法方案，那么联通块内直接根据结论 $1,3$ 转移，联通块之间根据结论 $1,2$ 转移。

这样可以通过此题……了吗？

考虑一种特殊情况：$0$ 的联通块内全部是 $and1$，周围相邻节点的都是 $or1$。这种情况显然不符合题意，因为不会有 $0$ 传递进入这个联通块。对于 $or0$ 是同理的。

但我们刚才并没有去掉这种情况。我们考虑额外进行一个 dp。记 $s_i$ 表示当前点所在联通块出现上述不合法方案的数量，那么在联通块内乘法合并，联通块之间转移 dp 数组时减掉儿子的统计的不合法方案，将父亲的不合法方案乘上儿子选 $and1/or0$ 的方案即可。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define int long long
struct edge
{
    int nxt,to;
}e[200001<<1];
const int mod=998244353;
int n,tot,h[200001<<1],a[200001],dp[200001][4],s[200001];
//0 0and 1 1and 2 0or 3 1or
inline void add(int x,int y)
{
    e[++tot].nxt=h[x];
    h[x]=tot;
    e[tot].to=y;
}
void dfs(int k,int f)
{
    dp[k][0]=dp[k][1]=dp[k][2]=dp[k][3]=1;
    if(a[k])
        dp[k][0]=0;
    else
        dp[k][3]=0;
    s[k]=1;
    for(register int i=h[k];i;i=e[i].nxt)
    {
        if(e[i].to==f)
            continue;
        dfs(e[i].to,k);
        if(!a[k]&&!a[e[i].to])
        {
            s[k]=s[k]*s[e[i].to]%mod;
            dp[k][0]=(dp[k][0]*(dp[e[i].to][0]+dp[e[i].to][1]+dp[e[i].to][2])%mod)%mod;
            dp[k][1]=(dp[k][1]*(dp[e[i].to][0]+dp[e[i].to][1])%mod)%mod;
            dp[k][2]=(dp[k][2]*(dp[e[i].to][0]+dp[e[i].to][2])%mod)%mod;
        }
        if(a[k]&&a[e[i].to])
        {
            s[k]=s[k]*s[e[i].to]%mod;
            dp[k][1]=(dp[k][1]*(dp[e[i].to][1]+dp[e[i].to][3])%mod)%mod;
            dp[k][2]=(dp[k][2]*(dp[e[i].to][2]+dp[e[i].to][3])%mod)%mod;
            dp[k][3]=(dp[k][3]*(dp[e[i].to][1]+dp[e[i].to][2]+dp[e[i].to][3])%mod)%mod;
        }
        if(a[k]&&!a[e[i].to])
        {
            s[k]=s[k]*dp[e[i].to][0]%mod;
            dp[k][0]=dp[k][1]=0;
            dp[k][2]=(dp[k][2]*(dp[e[i].to][0]+dp[e[i].to][1])%mod)%mod;
            dp[k][3]=(dp[k][3]*(dp[e[i].to][0]+dp[e[i].to][1]+mod-s[e[i].to])%mod)%mod;
        }
        if(!a[k]&&a[e[i].to])
        {
            s[k]=s[k]*dp[e[i].to][3]%mod;
            dp[k][2]=dp[k][3]=0;
            dp[k][0]=(dp[k][0]*(dp[e[i].to][2]+dp[e[i].to][3]+mod-s[e[i].to])%mod)%mod;
            dp[k][1]=(dp[k][1]*(dp[e[i].to][2]+dp[e[i].to][3])%mod)%mod;
        }
    }
}
signed main()
{
    scanf("%lld",&n);
    for(register int i=1;i<=n;++i)
    {
        scanf("%lld",&a[i]);
    }
    for(register int i=1;i<n;++i)
    {
        int x,y;
        scanf("%lld%lld",&x,&y);
        add(x,y);
        add(y,x);
    }
    dfs(1,0);
    printf("%lld\n",(dp[1][0]+dp[1][1]+dp[1][2]+dp[1][3]-s[1]+mod*114514)%mod);
    return 0;
}
```


---

## 作者：比利♂海灵顿 (赞：5)

# 风暴之眼

这道题的状态设计真是千奇百怪，有的做法每个点开了 $8$ 个状态，有的做法开了 $4$ 个，我一直尝试使这个数字变得更少，叉了几个做法还是没有成功，所以仍然是 $4$ 个状态。

传送门: [风暴之眼](https://www.luogu.com.cn/problem/P7727)

## 性质

每种类型都有一个稳定颜色，也就是说一个类型的点一旦变成某个颜色就再也不能变化了，因此每个点从开始到结束最多变化一次。

因为输入的终态是稳态，所以我们可以确定一些点的类型: 如果一个点的邻居存在和它颜色不一样的点，那么可以证明如果这个点是某种类型则这个状态下一刻还会发生变化。

接下来设计状态开始 DP。树形 DP 的核心就是把每棵子树作为子问题，并且通过子树的结果推得自己的结果。

或许可以记录每个点的初态和类型作为状态，但是只记录点的颜色或类型作为状态无法考虑颜色传递的方向，导致同色连通块陷入囚徒困境，即所有点都在等待他人更新。

因此转移需要记录每个点对父亲的要求和可以为父亲做出的贡献。

讨论一个点的不同状态，点的状态可以分为四种: 

- 需要父亲的颜色传递到自己
- 无需父亲即可变成自己的终态
- 自始至终都可以独自保持自己的终态
- 禁止父亲出现终态以外的颜色

这四个状态互不重合且覆盖了所有情况，分别用 $0, 1, 2, 3$ 表示它们。其中 $0, 1$ 状态初态和终态相反，类型也已确定。$2, 3$ 的初态和终态相同。状态 $3$ 是要求邻居始终为自己终态的类型，$0, 1, 2$ 是另一种类型。

设计状态 $f_{i, j}$ 表示第 $i$ 个点为状态 $j$，它子树合法的方案数。前三个状态的转移是:

$$
\begin{aligned}
f_{i, 0} &= \prod_{j \in Son_i} (f_{j, 0}[a_j = a_i] + f_{j, 2}[a_j \neq a_i])\\
f_{i, 1} &= \prod_{j \in Son_i} (f_{j, 0} + f_{j, 1} + f_{j, 2}) - f_{i, 0}\\
f_{i, 2} &= \prod_{j \in Son_i} (f_{j, 0}[a_j = a_i] + f_{j, 1} + f_{j, 2} + f_{j, 3})\\
f_{i, 3} &= [a_{Fa} = a_i]\prod_{j \in Son_i} (f_{j, 2} + f_{j, 3})[a_i = a_j]
\end{aligned}
$$

我们设一个新的根 $R$ 作为原来根 $r$ 的父亲，使它们终态相同。对于 $r$ 初态不变的状态，答案即为 $f_{r, 3} + f_{r, 2}$，对于 $r$ 初态改变的状态，取 $f_{r, 1}$ 即可。

```cpp
const unsigned long long Mod(998244353);
inline void Mn(unsigned& x) { x -= (x >= Mod) ? Mod : 0; }
unsigned long long Ans(1);
unsigned m, n, A, B;
struct Node {
  vector<Node*> E;
  unsigned f[4], Size;
  char Final;
}N[200005];
inline void DFS(Node* x, Node* Fa) {
  unsigned long long C1(1), C2(1), C3(1), C4(Fa->Final ^ x->Final ^ 1);
  for (auto i : x->E) if (i != Fa) {
    DFS(i, x);
    C1 = C1 * i->f[(x->Final ^ i->Final) << 1] % Mod;
    C2 = C2 * (i->f[0] + i->f[1] + i->f[2]) % Mod;
    C3 = C3 * (((i->Final == x->Final) ? i->f[0] : 0) + i->f[1] + i->f[2] + i->f[3]) % Mod;
    if (C4) C4 = C4 * ((i->Final == x->Final) ? (i->f[2] + i->f[3]) : 0) % Mod;
  }
  x->f[0] = C1;
  x->f[1] = Mod + C2 - C1, Mn(x->f[1]);
  x->f[2] = C3;
  x->f[3] = C4;
}
signed main() {
  n = RD();
  for (unsigned i(1); i <= n; ++i) N[i].Final = RD();
  for (unsigned i(1); i < n; ++i)
    A = RD(), B = RD(), N[A].E.push_back(N + B), N[B].E.push_back(N + A);
  N[0].Final = N[1].Final, DFS(N + 1, N), Ans = N[1].f[1] + N[1].f[2] + N[1].f[3];
  printf("%llu\n", Ans % Mod);
  return Wild_Donkey;
}
```

不是现场选手，是朋友退役前推荐我做的，这绝对是我做过最困难的蓝题。

---

## 作者：feecle6418 (赞：5)

~~比赛时被这个题**到了，赛后几秒钟调完 /px/px/px/px/px（i 写成了 j！！！！！！！！！！！）~~

本题和 ARC121F 很像（？

考虑已知初始状态如何推出最终状态，发现：

- 一些 and 点组成的连通块，当且仅当初始时连通块内部全是 1，与其相邻的一圈 or 点初值也全是 1，的时候，最终会全变为 1；否则最终会全变为 0
- 一些 or 点组成的连通块，当且仅当初始时连通块内部全是 0，与其相邻的一圈 and 点初值也全是 0，的时候，最终会全变为 0；否则最终会全变为 1

根据这个设计 dp：设 $f(x,i,j,k)$（点的编号 $x$，$x$ 的运算符是 and/or，$x$ 的初值是 $0/1$，附加在 $x$ 这个连通块上面的条件有/没有满足 [假如 $x$ 是 and 点初值是 1 最终要是 0，那这一维记录的相当于是 x 这一个连通块或者其邻域（旁边一圈点）初值现在填了 0 没有，其他情况类似]）

转移是 $O(1)$ 的，总复杂度 $O(n)$，需要考虑一些特殊情况，比如 $x$ 作为 $y$ 的父亲满足了 $y$ 的限制，那 $f(y,...,...,0)$ 可能是可以转移到 $f(x,...)$ 的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
int Power(int x,int y){
	int r=1;
	while(y){
		if(y&1)r=1ll*r*x%mod;
		y>>=1,x=1ll*x*x%mod;
	}
	return r;
}
int n,f[200005][2][2][2],a[200005];
//第一维 0 and 1 or
//第二维填什么 
//第三维没有满足/满足当前限制 
vector<int> g[200005];
void upd(int &x,int y){
	x=(x+y)%mod;
}
void dfs(int x,int fa){
	if(a[x]==0)f[x][0][0][1]=f[x][0][1][0]=f[x][1][0][1]=1;
	else f[x][1][1][1]=f[x][1][0][0]=f[x][0][1][1]=1;
	for(int y:g[x]){
		if(y==fa)continue;
		dfs(y,x);
		int t[2][2][2]={0};
		if(a[y]==0){
			if(a[y]==a[x]){
				//1.同一and联通块：中间或周围至少有一个0
				for(int i=0;i<2;i++)
					for(int j=0;j<2;j++)
						for(int k=0;k<2;k++)
							for(int l=0;l<2;l++)upd(t[0][i][j|l],1ll*f[x][0][i][j]*f[y][0][k][l]%mod);
				//2.同一or连通块：中间和周围全是0
				upd(t[1][0][1],1ll*f[x][1][0][1]*f[y][1][0][1]%mod);
				//3.x是or，y是and：都必须填0
				upd(t[1][0][1],1ll*f[x][1][0][1]*f[y][0][0][1]%mod);
				//4.x是and，y是or：都必须填0
				upd(t[0][0][1],1ll*f[x][0][0][1]*f[y][1][0][1]%mod);
			}
			else {//y=0 x=1
				//1.y and x or
				for(int i=0;i<2;i++)
					for(int j=0;j<2;j++)
						for(int k=0;k<2;k++)
							for(int l=0;l<2;l++)if(l|(!i))upd(t[1][i][j|k],1ll*f[x][1][i][j]*f[y][0][k][l]%mod);
			}
		}
		else {
			if(a[y]==a[x]){
				//1.同一or连通块
				for(int i=0;i<2;i++)
					for(int j=0;j<2;j++)
						for(int k=0;k<2;k++)
							for(int l=0;l<2;l++)upd(t[1][i][j|l],1ll*f[x][1][i][j]*f[y][1][k][l]%mod);
				//2.同一and连通块
				upd(t[0][1][1],1ll*f[x][0][1][1]*f[y][0][1][1]%mod);
				//3.x or y and：x填1,y填1
				upd(t[1][1][1],1ll*f[x][1][1][1]*f[y][0][1][1]%mod);
				//4.x and y or:都填1
				upd(t[0][1][1],1ll*f[x][0][1][1]*f[y][1][1][1]%mod); 
			}
			else {//y=1 x=0
				//只能是y or x and
				 for(int i=0;i<2;i++)
					for(int j=0;j<2;j++)
						for(int k=0;k<2;k++)
							for(int l=0;l<2;l++)if(l|i)upd(t[0][i][j|(!k)],1ll*f[x][0][i][j]*f[y][1][k][l]%mod);
			}
		}
		memcpy(f[x],t,sizeof(t));
	}
	
}
//一个and联通块中，只要所有点和周围点中有至少一个0，就会全变为0
//否则：1 
//一个or联通块中，只要所有点和周围点中有至少一个1，就会全变为1
//否则：0 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1,x,y;i<n;i++)cin>>x>>y,g[x].push_back(y),g[y].push_back(x);
	dfs(1,0);
	int ans=0;
	for(int i=0;i<2;i++)for(int j=0;j<2;j++)upd(ans,f[1][i][j][1]);
	cout<<ans; 
}
```

---

## 作者：littleKtian (赞：4)

显然对于所有 $\texttt{AND}$ 型结点，如果其在某一时刻权值变为 $0$，那么在后续时刻将不再变化权值。$\texttt{OR}$ 型结点同理在变为 $1$ 后不再发生变化。所以我们考虑对于所有最终权值为 $0$ 的结点，将 $\texttt{OR}$ 型称为**强制型**，$\texttt{AND}$ 型称为**非强制型**，最终权值为 $1$ 的结点反之。

可以发现对于所有强制型结点，其自身和周围结点的权值必须始终保持和该点最终权值相同，也就是要满足下面两个条件：

1. 自身和周围结点的最终权值相同。
2. 自身和周围结点的初始权值均和该点最终权值相同。

而对于所有非强制型结点，其初始权值不一定要和最终权值相同，其可以利用周围结点来传入最终权值。

根据上面的条件，显然对于一条连接两个**最终权值不同**的结点的边，其连接的两点均为非强制型结点。

那么对于一个**最终权值相同**的连通块，其最终权值满足条件需要满足下面两个条件之一：

1. 连通块内存在某个点，其初始权值和最终权值相同。
2. 连通块外存在某个和该连通块相邻的点，其初始权值和该连通块最终权值相同（因为那个点以及其在该连通块内相连的点均为非强制型结点）。

于是我们可以设 $f_{i,0/1,0/1,0/1}$ 表示以 $i$ 为根的子树内，结点 $i$ 的初始权值和最终权值相同/不同，结点 $i$ 为非强制型/强制型结点，$i$ 所在的连通块还未满足/已经满足最终权值的条件时的初始权值和类型的组合数，直接根据上面要求来转移即可。此时已经做到复杂度 $O(n)$

进一步观察，可以发现上面的 $8$ 种状态中我们真正需要的只有 $4$ 种：

+ 初始权值相同，强制型，已满足。
+ 初始权值相同，非强制型，已满足。
+ 初始权值不同，非强制型，已满足。
+ 初始权值不同，非强制型，未满足。

其余 $4$ 种容易发现其状态并不存在，所以我们直接在上面 $4$ 种情况之间 dp 即可。

```cpp
#include<bits/stdc++.h>
#define p 998244353
using namespace std;
int lw[200005],bi[400005][2],bs;
int f[200005][4],g[4];
int n,a[200005];
int dr()
{
	int xx=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')xx=xx*10+ch-'0',ch=getchar();
	return xx;
}
void tj(int u,int v){bi[++bs][0]=lw[u],bi[lw[u]=bs][1]=v;}
void dfs(int w,int fa)
{
	f[w][0]=f[w][1]=f[w][3]=1;
	for(int o_o=lw[w];o_o;o_o=bi[o_o][0])
	{
		int v=bi[o_o][1];
		if(v!=fa)
		{
			dfs(v,w);
			memset(g,0,sizeof(g));
			if(a[w]==a[v])
			{
				g[0]=1ll*f[w][0]*(f[v][0]+f[v][1])%p;
				g[1]=1ll*f[w][1]*((f[v][0]+f[v][1])%p+(f[v][2]+f[v][3])%p)%p;
				g[2]=(1ll*f[w][2]*((f[v][1]+f[v][2])%p+f[v][3])+1ll*f[w][3]*(f[v][1]+f[v][2]))%p;
				g[3]=1ll*f[v][3]*f[w][3]%p;
			}
			else
			{
				g[1]=1ll*f[w][1]*(f[v][1]+f[v][2])%p;
				g[2]=(1ll*f[w][2]*((f[v][1]+f[v][2])%p+f[v][3])+1ll*f[w][3]*(f[v][2]+f[v][3]))%p;
				g[3]=1ll*f[v][1]*f[w][3]%p;
			}
			memcpy(f[w],g,sizeof(g));
		}
	}
}
int main()
{
	n=dr();
	for(int i=1;i<=n;i++)a[i]=dr();
	for(int i=1;i<n;i++)
	{
		int x=dr(),y=dr();
		tj(x,y),tj(y,x);
	}
	dfs(1,0),printf("%d",((f[1][0]+f[1][1])%p+f[1][2])%p);
}
```


---

## 作者：xieyikai2333 (赞：0)

# 洛谷 P7727 风暴之眼（Eye of the Storm）

- [题目传送门-洛谷](https://www.luogu.com.cn/problem/P7727)

- 提供一种另类的思路。

---

## 解题思路

- 首先，这题显然是用 **树形 DP** 做。

### 状态设计

- $f_{u,1/0,\text{O}/\text{A}}$ 表示结点 $u$ 的初始类型是 $(0/1,\texttt{OR}/\texttt{AND})$ 时子树 $u$ 的方案数（保证加入父节点后满足条件）。

- 对于 $g$ 数组，
	
	若 $a_u=1$，则 $g_u$ 表示结点 $u$ 的初始类型是 $(0,\texttt{OR})$ 时使得子树 $u$ 在考虑父结点前不能满足条件的方案数；
	
	若 $a_u=0$，则 $g_u$ 表示结点 $u$ 的初始类型是 $(1,\texttt{AND})$ 时使得子树 $u$ 在考虑父结点前不能满足条件的方案数。

### 状态转移

- 默认根为 $1$ 号结点。
- 在这里，我们需要以结点的最终状态为依据对结点进行分类讨论。
- 根据各变量的定义不难得出以下状态转移方程（解释较繁杂，反而结合定义直接自行理解比较容易）：
	- 若 $a_u=1$：
		- 初始化：
			- $f_{u,1,\text{A}} \gets 1$，$f_{u,1,\text{O}} \gets 1$，$f_{u,0,\text{A}} \gets 0$，$f_{u,0,\text{O}} \gets 1$，$g_{u} \gets 1$
		- 枚举 $u$ 的每一个儿子 $v$：
			- 若 $a_v=1$：
				- $f_{u,1,\text{A}} \gets f_{u,1,\text{A}} \times (f_{v,1,\text{O}}+f_{v,1,\text{A}})$
				- $f_{u,1,\text{O}} \gets f_{u,1,\text{O}} \times (f_{v,0,\text{A}}+f_{v,1,\text{O}}+f_{v,1,\text{A}}+f_{v,0,\text{O}})$
				- $f_{u,0,\text{O}} \gets f_{u,0,\text{O} }\times (f_{v,0,\text{A}}+f_{v,1,\text{O}}+f_{v,0,\text{O}})$
				- $g_u \gets g_u \times g_v$
			- 若 $a_v=0$：
				- $f_{u,1,\text{A}} \gets 0$
				- $f_{u,1,\text{O}} \gets f_{u,1,\text{O}} \times [f_{v,0,\text{A}}+f_{v,1,\text{O}}+(f_{v,1,\text{A}}-g_v)]$
				- $f_{u,0,\text{O}} \gets f_{u,0,\text{O} }\times (f_{v,0,\text{A}}+f_{v,1,\text{O}}+f_{v,1,\text{A}})$
				- $g_u \gets g_u \times f_{v,0,\text{A}}$
	- 若 $a_u=0$：
		- 初始化：
			- $f_{u,0,\text{O}} \gets 1$，$f_{u,0,\text{A}} \gets 1$，$f_{u,1,\text{O}} \gets 0$，$f_{u,1,\text{A}} \gets 1$，$g_{u} \gets 1$
		- 枚举 $u$ 的每一个儿子 $v$：
			- 若 $a_v=0$：
				- $f_{u,0,\text{O}} \gets f_{u,0,\text{O}} \times (f_{v,0,\text{A}}+f_{v,0,\text{O}})$
				- $f_{u,0,\text{A}} \gets f_{u,0,\text{A}} \times (f_{v,1,\text{O}}+f_{v,0,\text{A}}+f_{v,0,\text{O}}+f_{v,1,\text{A}})$
				- $f_{u,1,\text{A}} \gets f_{u,1,\text{A} }\times (f_{v,1,\text{O}}+f_{v,0,\text{A}}+f_{v,1,\text{A}})$
				- $g_u \gets g_u \times g_v$
			- 若 $a_v=1$：
				- $f_{u,0,\text{O}} \gets 0$
				- $f_{u,0,\text{A}} \gets f_{u,0,\text{A}} \times [(f_{v,1,\text{O}}+f_{v,0,\text{A}}+(f_{v,0,\text{O}}-g_v)]$
				- $f_{u,1,\text{A}} \gets f_{u,1,\text{A} }\times (f_{v,1,\text{O}}+f_{v,0,\text{A}}+f_{v,0,\text{O}})$
				- $g_u \gets g_u \times f_{v,1,\text{O}}$
- 最后输出答案：
	- 若 $a_1=1$，答案为 $f_{1,1,\text{O}}+f_{1,1,\text{A}}+(f_{1,0,\text{O}}-g_1)$
	- 若 $a_1=0$，答案为 $f_{1,0,\text{A}}+f_{1,0,\text{O}}+(f_{1,1,\text{A}}-g_1)$

---

## 代码实现

### CODE

```cpp
#include <bits/stdc++.h>
#define int long long
#define A 0
#define O 1
using namespace std;
const int N=2e5+5,mod=998244353;
int f[N][2][2],g[N],a[N];
vector<int> nodes[N];
void dfs(int u,int fa)
{
	f[u][1][A]=f[u][0][O]=g[u]=1;
	if(a[u]==1)f[u][1][O]=1;
	else f[u][0][A]=1;
	for(int v:nodes[u])
	{
		if(v==fa)continue;
		dfs(v,u);
		if(a[u]==1)
		{
			if(a[v]==1)
			{
				(f[u][1][A]*=f[v][1][O]+f[v][1][A])%=mod;
				(f[u][1][O]*=f[v][0][A]+f[v][1][O]+f[v][1][A]+f[v][0][O])%=mod;
				(f[u][0][O]*=f[v][0][A]+f[v][1][O]+f[v][0][O])%=mod;
				(g[u]*=g[v])%=mod;
			}
			else
			{
				f[u][1][A]=0;
				(f[u][1][O]*=f[v][0][A]+f[v][1][O]+f[v][1][A]-g[v]+mod)%=mod;
				(f[u][0][O]*=f[v][0][A]+f[v][1][O]+f[v][1][A])%=mod;
				(g[u]*=f[v][0][A])%=mod;
			}
		}
		else
		{
			if(a[v]==0)
			{
				(f[u][0][O]*=f[v][0][A]+f[v][0][O])%=mod;
				(f[u][0][A]*=f[v][1][O]+f[v][0][A]+f[v][0][O]+f[v][1][A])%=mod;
				(f[u][1][A]*=f[v][1][O]+f[v][0][A]+f[v][1][A])%=mod;
				(g[u]*=g[v])%=mod;
			}
			else
			{
				f[u][0][O]=0;
				(f[u][0][A]*=f[v][1][O]+f[v][0][A]+f[v][0][O]-g[v]+mod)%=mod;
				(f[u][1][A]*=f[v][1][O]+f[v][0][A]+f[v][0][O])%=mod;
				(g[u]*=f[v][1][O])%=mod;
			}
		}
	}
	return;
}
signed main()
{
	int n;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%lld %lld",&u,&v);
		nodes[u].emplace_back(v);
		nodes[v].emplace_back(u);
	}
	dfs(1,0);
	if(a[1]==1)printf("%lld",(f[1][1][O]+f[1][1][A]+f[1][0][O]-g[1]+mod)%mod);
	else printf("%lld",(f[1][0][A]+f[1][0][O]+f[1][1][A]-g[1]+mod)%mod);
	return 0;
}
```

---

### AC 记录

![](https://cdn.luogu.com.cn/upload/image_hosting/9hc1pite.png)

---

