# [CEOI 2017] Mousetrap

## 题目描述

有一个有 $n$ 个房间和 $n-1$ 条走廊的迷宫，保证任意两个房间可以通过走廊互相到达，换句话说，这个迷宫的结构是一棵树。

一个老鼠被放进了迷宫，迷宫的管理者决定和老鼠做个游戏。

一开始，有一个房间被放置了陷阱，老鼠出现在另一个房间。老鼠可以通过走廊到达别的房间，但是会弄脏它经过的走廊。老鼠不愿意通过脏的走廊。

每个时刻，管理者可以进行一次操作：堵住一条走廊使得老鼠不能通过，或者擦干净一条走廊使得老鼠可以通过。然后老鼠会通过一条干净的并且没被堵住的走廊到达另一个房间。只有在没有这样的走廊的情况下，老鼠才不会动。一开始所有走廊都是干净的。管理者不能疏通已经被堵住的走廊。

现在管理者希望通过尽量少的操作将老鼠赶到有陷阱的房间，而老鼠则希望管理者的操作数尽量多。请计算双方都采取最优策略的情况下管理者需要的操作数量。

注意：管理者可以选择在一些时刻不操作。

## 说明/提示

**样例解释**

-    管理者先堵住房间 $4$ 和 $7$ 之间的走廊。
-    老鼠走到房间 $6$。房间 $4$ 和 $6$ 之间的走廊现在是脏的。
-    管理者堵住房间 $6$ 和 $8$ 之间的走廊。
-    老鼠不能动。
-    管理者清理房间 $4$ 和 $6$ 之间的走廊，房间 $4$ 和 $6$ 之间的走廊现在是干净的。
-    老鼠走到房间 $4$，房间 $4$ 和 $6$ 之间的走廊现在是脏的。
-    管理者堵住房间 $2$ 和 $3$ 之间的走廊。
-    老鼠走到房间 $2$，房间 $2$ 和 $4$ 之间的走廊现在是脏的。
-    管理者不进行操作。
-    老鼠走到房间 $1$。

这个过程中管理者总共进行了 $4$ 次操作。

**数据范围**

对于所有的数据，$1 \le n \le 10^6$。

## 样例 #1

### 输入

```
10 1 4
1 2
2 3
2 4
3 9
3 5
4 7
4 6
6 8
7 10```

### 输出

```
4```

# 题解

## 作者：lhm_ (赞：24)

为方便处理，把树看作有根树，将陷阱房作为树的根。

先考虑一种特殊情况，老鼠起始房间和陷阱房是相邻的，即老鼠起始房间为根节点的一个儿子。一开始老鼠的决策是不可能向上走，其只可能一路向下沿最优路线到叶子节点，直到其无法行动。管理者的决策则是在老鼠向下走时堵住沿途的一些边，直到老鼠无法行动后，再堵住老鼠所在的叶子节点到根的路径上每个点延伸出去的分叉边，然后将路径进行清理，这样老鼠就会被一路赶到根节点。考虑树形 $DP$，设 $f_x$ 为老鼠在点 $x$ 进入 $x$ 的子树后，将其又赶回点 $x$ 的最小操作次数，得：
$$
\large f_x =  \underset{y \in son_x}{\text{2ndmax}}\{ f_y \} + num_x
$$
其中 $\text{2ndmax}$ 表示次大值，$num_x$ 表示点 $x$ 的儿子个数。老鼠的最优决策一定是往 $f$ 尽可能大的点走，管理者的最优决策一定是堵住通向最大值的那条边，因此是从次大值转移过来。儿子个数是必要的操作次数，即堵住分叉边和清理边。

当老鼠起始房间和陷阱房不相邻时，一开始老鼠不一定会直接向下走，其可能会先向上跳，到达某个节点后才开始向下走，开始走后老鼠对走哪个儿子的选择取决于管理者堵边的情况。不难计算出老鼠选择完儿子后的最小操作次数，设老鼠在点 $x$ 开始向下走，选择儿子点 $y$，得：
$$
\large\begin{aligned}

cost&=f_y+sum_x \\

sum_x&=sum_{fa_x}+num_x-1+[x=m],(x\not = root)\\

\end{aligned}
$$
$sum_x$ 为堵上点 $x$ 到根的路径每个点的分叉边的操作次数，若 $x$ 不为老鼠起始房间，则已经有一条分叉边被弄脏了，这条边就不用再堵了。

并不好处理老鼠在向上跳时管理者的决策，发现答案具有单调性，可以考虑进行二分操作次数。判定二分时，让老鼠不断向上跳，当老鼠所在的节点可以和某个儿子组成的 $cost$ 大于当前还可进行的操作次数，就需要将通向这个儿子的边堵住。当前操作次数不够用或者超过了二分的操作次数时，二分的值就判定为不合法。

```cpp
#include<bits/stdc++.h>
#define maxn 2000010
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,root,m,l,r,ans;
int fa[maxn],f[maxn],sum[maxn];
bool tag[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]={to,head[from]},head[from]=edge_cnt;
}
void dfs(int x,int fath)
{
    fa[x]=fath;
    int son=0,mx1=0,mx2=0;
    for(int i=head[x];i;i=e[i].nxt) son+=(e[i].to!=fath);
    if(x!=root) sum[x]=sum[fath]+son-1+(x==m);
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(y==fath) continue;
        dfs(y,x);
        if(f[y]>mx1) mx2=mx1,mx1=f[y];
        else if(f[y]>mx2) mx2=f[y];
    }
    f[x]=mx2+son;
}
bool check(int val)
{
    int cnt=1;
    for(int x=m;x!=root;x=fa[x],cnt++)
    {
        int v=0;
        for(int i=head[x];i;i=e[i].nxt)
        {
            int y=e[i].to;
            if(tag[y]||f[y]+sum[x]<=val) continue;
            if(!cnt) return false;
            v++,cnt--;
        }
        val-=v;
    }
    return val>=0;
}
int main()
{
    read(n),read(root),read(m),r=2*n;
    for(int i=1;i<n;++i)
    {
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    dfs(root,0);
    for(int i=m;i;i=fa[i]) tag[i]=true;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：imsaileach (赞：9)

# 前言

模拟赛之后被胁迫上去讲这题，没怎么准备，然后就在几个省的 OIer 面前当小丑。。倒是把我自己讲得很明白，但感觉对其他人不是很负责任，就来赎罪一下。。

[更好的阅读体验](https://www.luogu.com.cn/blog/Rong7/post-ti-xie-p4654-ceoi2017-mousetrap)。

# 题意

[题目链接](https://www.luogu.com.cn/problem/P4654)。

# 分析

1. 以 $t$ 为根，我们的目的是让老鼠走到根的操作数最小。

2. 观察老鼠的动向，显然老鼠只要一往下走，那么除非管理员将它上方的道路擦干净，否则它就只能继续往下走。当然，老鼠可能也会往上走（待会儿再考虑）。

3. 若老鼠已经往下走，但未走到叶子节点，那么我们不用立刻将其往上的一条路的分支堵住，因为当老鼠自己到叶子节点之后就动不了了，这时我们再把从这个叶子节点往上直到根的路径上所有的分支（不包括根的分支）全部堵上，最后再一一擦干净老鼠的边，使其被迫走向根节点。如果不堵分支，那么老鼠走入分支消耗的操作数一定大于等于 $1$ 即直接堵的操作数。

4. 因为是最优策略，所以每个点的最优操作数之类的信息唯一。

5. 根据 4 提供的思路，考虑 $f_u$ 表示老鼠从 $u$ 点出发往下折腾一通再被迫回到 $u$ 点**在 $u$ 子树内**消耗的操作数。考虑 DP，由于每次老鼠出发前管理员可以先进行一次操作。只观察 $u$ 点的儿子节点，发现如果不把向最大值 $(f_v)_{\max}$ 的路径堵住的话，老鼠一定选这条路往下走，折腾 $(f_v)_{\max}$ 次操作后，回到 $u$ 点；否则老鼠会向次大值 $(f_v)_{\max_2}$ 走，折腾 $(f_v)_{\max_2}$ 次操作后回到 $u$ 点。我们发现两种情况老鼠回到 $u$ 点后情况其他都一样（分支全部被堵住，只能往上走），所以选择堵 $(f_v)_{\max}$ 一定最优（我们还可能堵与它不相连的边，但贡献一定小于等于堵 $(f_v)_{\max}$ 的贡献，显然）。

6. 考虑如何求 $f_u$，发现实际上根据 3 可知管理员的固定策略，$f_u$ 分为三部分：一、选择最大的 $f_v$ 堵住，使从 $u$ 点只能走向次大 $f_v$；二、在老鼠抵达叶子后，利用多出的时间堵上 $u$ 的其他分支；三、把老鼠往下走过的路径擦干净，让老鼠走回 $u$ 点。于是有转移方程：
   $$
   f_u=(f_v)_{\max_2}+deg_u-1
   $$
   其中 $deg_u-1$ 表示 $u$ 点的分支（度数）去掉连向 $father$ 节点的，去掉 $u \to v$ 走向次大子节点的（这个不堵），加上擦老鼠 $v \to u$ 走上来的边。再加上原本的次大子节点，就是 $f_u$。

7. 考虑由 $f_u$ 求出具体的操作次数。记录 $g_u$ 表示 $u$ 到 $t$ 路径上管理员需要堵的分支（不包括 $u$ 本身的分支），则可知 $g$ 的转移方程：

   $$
   g_u=g_{father}+\max(deg_{father} - 2, 0)
   $$
   解释一下，$u$ 向上的需要堵的分支，等于其 $father$ 节点向上需要堵的分支加上 $father$ 节点自己的分支（度数，去掉连向 $father$ 的父节点的边，去掉连向 $u$ 的边）（特殊情况用 $\max$ 判断）（特别地，钦定 $deg_t=1$（实际上，从本题的数据上看，不影响））。

   然后我们记录一个 $cnt_u$ 表示 **从 $u$ 的父节点走入 $u$ 后** 并最终结束游戏所需要的操作数。显然 $cnt_u$ 存在唯一值。

   知 $cnt_u$ 的转移方程为：
   $$
   cnt_u=f_u+g_u+1-(father\neq m)
   $$
   再解释一下，$f_u$ 是老鼠往下走最终回到 $u$ 点时 $u$ 子树内的操作数贡献，$g_u$ 是管理员不得不堵的 $u$ 到 $t$ 路径上的分支，额外加的 $1$ 是擦干净 $father \to u$ 这条边的操作。最后的 $01$ 判断意思是：若父节点不是 $t$，则老鼠自己是从 $father$ 的另一个分支走入 $father$ 再走下 $u$ 的，老鼠已经自己弄脏了一条边，管理员就可以少堵一条。

8. 然后我们会发现我们记录的值似乎没什么卵用。

9. 但是先别重开。再次分析老鼠的固定策略。显然老鼠可以向上走，进入一条比直接从 $u$ 往下走更优的分支，最大化答案。

10. 考虑简化问题。考虑二分。对于一个待检查的最大操作数 $T$，显然此时问题变为了：**老鼠能不能使最大操作数大于 $T$**。

11. 考虑简化老鼠的策略，并分析整个游戏的固定流程分层。老鼠显然可以先往上走 $k$ 次（$k \geq 0$）。然后选择当前点的一个分支，从当前点走入这个分支，（根据 4 知）老鼠走到叶子节点，管理员堵分支，老鼠出来走入根节点 $t$，游戏结束。

12. 考虑 11 中“从当前点走入这个分支”的隐含内容，显然走入分支后，剩下的操作数由 $cnt$ 可以直接计算。

13. 考虑二分检验时模拟过程。记 $\mathrm{check}(u, p, q)$ 表示当前在 $u$ 点，最多还可以进行 $p$ 次操作，管理员提前保留了 $q$ 次操作，能否满足。这里需要说一下，因为两方都执行最优，所以管理员、老鼠互相可以知道对方的一定的策略。所以管理员会在每次可操作时堵上老鼠走入会使总操作次数大于 $p$ 的分支。因为管理员执行最优，且方案一定，所以管理员可以在不需要堵当前点的分支的时候提前堵后面的点，形象地说，管理员将操作数保留累积下来，在以后的点中使用。

14. 考虑如何实现 $\mathrm{check}(u, p, q)$。记 $v$ 为 $u$ 的任意儿子（当然，要求 $u$ 不是从 $v$ 走上来的）。首先为了使老鼠在当前点无法直接使操作数大于 $p$，我们要将所有 $cnt_v>p$ 的分支堵住。令这些分支的数目为 $x$，显然若 $x>p$ 或 $x>q$ 就返回 $\text{false}$。否则保留的操作数 $q$ 用去 $x$，同时老鼠往上走，时间 $+1$，所以 $q$ 又多累积了 $1$；同时最大的剩余操作数 $p$ 也用去 $x$。

    这时显然有：
    $$
    \mathrm{check}(u,p,q)=\begin{cases}
    \mathrm{check}(father_u,p-x,q-x+1) & p \geq x , q \geq x \\
    \text{false} & \textrm{otherwise} \\
    \end{cases}
    $$
    可以递归或循环实现。

    特别地， $\mathrm{check} (t, i, j)=\text{true}$。

    注意记 $u$ 是从 $last$ 走上来的，对于 $u$ 的儿子特殊判断 $v \neq last$。对于 $u=m$，$last=0$。

15. 所以每次检查答案 $T$ 是否正确的返回值就是 $\mathrm{check}(m,T,1)$。



# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t, m, a, b;
int fa[1000005], dg[1000005], f[1000005], g[1000005], cnt[1000005];
int firs[1000005], nex[2000005], to[2000005], tot;
void Add (int u, int v){
    ++ tot;
    nex[tot] = firs[u];
    firs[u] = tot;
    to[tot] = v;
}
void init (int u, int father){
    fa[u] = father;
    g[u] = g[father] + max (dg[father] - 2, 0);
    int max1 = 0, max2 = 0;
    for (int e = firs[u];e;e = nex[e]){
        int v = to[e];
        if (v == father)
            continue;
        init (v, u);
        if (max1 < f[v]){
            max2 = max1;
            max1 = f[v];
        } else
        if (max2 < f[v])
            max2 = f[v];
    }
    f[u] = max2 + dg[u] - 1;
    cnt[u] = f[u] + g[u] + 1 - (fa[u] != m);
}
bool Check (int p){
    int q = 1, las = 0;
    for (int u = m;u != t;u = fa[u]){
        int x = 0;
        for (int e = firs[u];e;e = nex[e]){
            int v = to[e];
            if (v == fa[u] || v == las)
                continue;
            if (cnt[v] > p)
                ++ x;
        }
        q -= x;
        p -= x;
        if (q < 0 || p < 0)
            return false;
        ++ q;
        las = u;
    }
    return true;
}
int main (){
    scanf ("%d%d%d", &n, &t, &m);
    for (int i = 1;i < n;++ i){
        scanf ("%d%d", &a, &b);
        Add (a, b);
        Add (b, a);
        ++ dg[a];
        ++ dg[b];
    }
    dg[t] = 1;
    init (t, 0);
    int L = 0, R = n << 1;
    while (L < R){
        int mid = L + R >> 1;
        if (Check (mid))
            R = mid;
        else
            L = mid + 1;
    }
    printf ("%d\n", L);
    return 0;
}
```

---

## 作者：FjswYuzu (赞：6)

一般来说我们会考虑将树上的特殊点（比如重心之类的）当作根，这样的话问题就会好考虑一些。在这个题中，权衡老鼠一开始的点和陷阱房，显然陷阱房不变会好更好处理（毕竟起点没什么高妙性质）。实际上这个想法在样例中有迹可循，你可以发现陷阱房在 $1$。

并且，不难发现，假设某个时刻起，老鼠开始往下走了，那么这个老鼠的生命就差不多得了。因为就算管理员不操作，老鼠走到叶子了，也动不了了。此时管理员只需要保证这个点到根的路径上的所有点，只有向上的走法。用样例举个例子：假设老鼠走了 $4 \to 7$ 的边，先封住 $7 \to 10$ 的边，这样老鼠就动不了了；然后封住 $4 \to 6,2 \to 3$，最后打开 $4 \to 7$，老鼠只能从 $7$ 向上走到 $4,2,1$，进入陷阱房。

所以，不难发现老鼠被困住之后，陷阱房到老鼠初始点路径上老鼠没走过的点需要封住多余的子树，不然会产生额外的贡献（走进去之后还要走出来，并且里面的操作未知。但是这个过程完全可以规避），每个点 $u$ 的贡献是 $deg_u - 2$。这显然是一个前缀和的形式，可以把这条链先爬出来，然后做个后缀和。

那么不难想到，整个过程是管理员一边堵住某些走廊，老鼠一边走。最终老鼠会在 $m \to t$ 路径上的某一个点开始往下走到某一棵子树里面，然后遇到老鼠走不动的情况，剩下的工作在上面就已经说干净了。

但是不仅是上面的说法有漏洞（也就是，老鼠走入到子树，子树里面有些边还必须在老鼠困住无法操作时封掉），并且在子树中的过程中也没有想象中的这么好考虑——如何解决？

考虑 dp。定义 $dp_u$ 为，老鼠刚好到 $u$，并且 $u$ 的子树的边完好；老鼠在里面随意操作，管理员让老鼠最终被困回 $u$ 的最少操作是多少？显然 $u$ 如果是陷阱房到老鼠出发点路径上的某个点，$dp_u$ 没有意义（老鼠不可能走上去之后再走下来，这样显然不优，并且如果更优是老鼠的失误，管理员也不可能打开 $u \to fa_u$ 这条边）

如何求得 $dp_u$？当老鼠走到 $u$ 的时候，老鼠肯定想往 $son_u$ 中 $dp$ 值最大的 $p$。此时我们将 $u \to p$ 的边封住，这样老鼠就只能退而求其次，选 $son_u$ 中 $dp$ 值第二大的 $q$……然后最终老鼠会被困在子树中的某一个点，我们令其回到 $q$ 之后，先把 $u$ 子树中其他的还没被封过的边封住，然后再把 $u \to q$ 打开，这样老鼠最终会被困在 $u$。转移式可以阅读这一段话简单得出。

这样的话，我们求出所有结点的 $dp$ 值。接下来就是老鼠选择一个子树往下钻的时候了。注意到，如果老鼠能够向下进入一个结点 $u$，那么老鼠如果想向下钻入结点 $v$ 使得 $dp_v \leq dp_u$ 也是可以的，并且这属于老鼠的失误，老鼠肯定不会这么决策。但是这启发我们这个题可以用二分找到那个最大的 $dp$ 值。并且这样就可以直接二分答案了：管理员先封住一条边，然后老鼠向上跳一条边；或者老鼠检测发现现在有一条边通向的点的 dp 值比当前二分的值要大，那么这个答案不合法。

具体实现可以研究代码，很清楚了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[1<<18],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<18,stdin),p1==p2)?EOF:*p1++)
int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')	c=getchar();
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x;
}
void write(int x)
{
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
vector<int> G[1000005];
int n,s,t,lnk[1000005],cnt,fa[1000005],dp[1000005],brc[1000005];
#define Deg(x) (int(G[x].size()))
void dfs(int now,int pre)
{
	fa[now]=pre;
	int maxn=0,maxc=0;
	for(auto st:G[now])
	{
		if(st==pre)	continue;
		dfs(st,now);
		if(dp[st]>=maxn)	maxc=maxn,maxn=dp[st];
		else if(dp[st]>=maxc)	maxc=dp[st];
	}
	if(now!=s)	dp[now]=maxc+Deg(now)-1;
}
bool check(int lmt)
{
	int sum=0;
	for(int i=1;i<=cnt;++i)
	{
		int p=lnk[i],cks=0;
		for(auto st:G[p])
		{
			if(st==lnk[i-1] || st==lnk[i+1] || st==s)	continue;
			if(dp[st]+brc[i]+1-(i!=1)>lmt)	++cks;
		}
		sum+=cks,lmt-=cks;
		if(sum>i || lmt<0)	return false;
	}
	return true;
}
int main(){
	n=read(),s=read(),t=read();
	for(int i=1,u,v;i<n;++i)	u=read(),G[u].push_back(v=read()),G[v].push_back(u);
	dfs(s,0);
	int p=t;
	while(p^s)	p=fa[lnk[++cnt]=p];
	for(int i=cnt;i;--i)	brc[i]=brc[i+1]+Deg(lnk[i])-2;
	int l=0,r=2*n,ans=2*n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))	r=(ans=mid)-1;
		else	l=mid+1;
	}
	write(ans);
	return 0;
}
```

---

## 作者：GreenDay (赞：6)

这道题作为自己学校模拟赛出现了2次了，所以我就**爆零**了两次。今天在洛谷闲逛的时候无意间看到了这道题，觉得有必要写篇总结造福后人，~~下次考试再遇到，我就直接抄我自己的~~。

神仙题啊神仙题，无限orz出题人

---

先放篇代码 **CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1000010 , inf = 1e8;
int n , B , A;
int head[N] , to[N*2] , nxt[N*2] , cnt;
void addedge(int x , int y) {
	to[++cnt] = y , nxt[cnt] = head[x] , head[x] = cnt;
}

inline int read() {
    int x = 0 ; char c = getchar(); bool f = 0;
    while(c < '0' || c > '9') f |= (c=='-') , c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + (c^48) , c = getchar();
    return f ? -x : x;
}

int deep[N] , fa[N];
void dfs(int x) {
	for(int i = head[x] ; i ; i = nxt[i]) {
		int y = to[i];
		if(y == fa[x]) continue;
		fa[y] = x , deep[y] = deep[x] + 1 , dfs(y);
	}
}
bool onpath[N] ;
int dp[N];
vector<int> branch[N];

void DP(int x , int top , int sum) {
	if(onpath[x]) top = x;
	int son = 0;
	for(int i = head[x] ; i ; i = nxt[i]) {
		int y = to[i];
		if(y == fa[x]) continue;
		if(son) sum++;
		son++; 
	}
	if(!son) {dp[x] = deep[x] - deep[top] + sum ; return ;}
	
	int maxdp = -inf , max2dp = -inf;
	for(int i = head[x] ; i ; i = nxt[i]) {
		int y = to[i];
		if(y == fa[x]) continue;
		DP(y , top , sum);
		if(dp[y] > maxdp) max2dp = maxdp , maxdp = dp[y];
		else if(dp[y] > max2dp) max2dp = dp[y]; 
	}
	if(son == 1) dp[x] = deep[x] - deep[top] + sum + 1;
	else dp[x] = max2dp;
}

void prepare() {
	n = read() , B = read() , A = read();
	if(A == B) {puts("0"); exit(0);} 
	for(int i = 1 ; i < n ; ++i) {
		int u = read() , v = read();
		addedge(u , v) , addedge(v , u);
	}
	dfs(B);
	for(int p = A ; p != B ; p = fa[p]) onpath[p] = true;
	for(int i = head[B] ; i ; i = nxt[i]) {
		int y = to[i];
		if(onpath[y]) DP(y , y , 0);
	}
	for(int p = A ; p != B ; p = fa[p]) {
		for(int i = head[p] ; i ; i = nxt[i]) {
			int y = to[i];
			if(onpath[y] || y == B) continue;
			branch[p].push_back(dp[y]);
		}
		sort(branch[p].begin() , branch[p].end());
	}
}

bool check(int x) {
	int ban = 0 , id = 0;
	for(int p = A ; p != B ; p = fa[p]) {
		for(int i = 0 ; i < branch[p].size(); ++i)
			if(branch[p][i] + ban > x + (p!=A))
				ban++;
		if(ban > ++id) return false;
	}
	return true;
}

int main() {
//	freopen("fish.in" , "r" , stdin);
//	freopen("fish.out" , "w" , stdout);
	prepare();
	int l = dp[A] , r = 2*n , mid;
	while(l < r) {
		mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d\n" , l);
	return 0;
}
```

那么我们来分析一下这个代码。

首先，我们默认有陷阱的那个节点是根，方便处理。

### case 1 : 老鼠在一个叶子节点上，且这个节点到根节点的路径都被弄脏。

比如说这样的，红叉表示路径被弄脏，绿勾表示路径没有被弄脏

![](https://cdn.luogu.com.cn/upload/image_hosting/sijw3m6b.png)

此时，管理员需要多少代价把老鼠赶到陷阱里去？

显然是3(红叉)+6(绿勾),也就是代码里的
```cpp
if(!son) {dp[x] = deep[x] - deep[top] + sum ; return ;}
```

这个时候我们需要干2件事情：

- 把老鼠到根上，所有路径都疏通。

- 把这条路径上，其他的分支都堵死。

对于叶子节点，我们记$dp_i=deep+\sum branches$表明这个点的权值。

### case 2 : 老鼠和夹子是相邻的

~~显然老鼠不会傻到直接向夹子走过去吧~~

我们要对dp数组的定义加以拓展。设$dp_i$表示老鼠到了这个点所需要花的代价。

对于一个非叶子的节点，老鼠肯定会向叶子节点的方向走去。注意到，我们在此时最优的操作一定会封住一个儿子。（如果当前步骤不封住这个儿子，最后也一定会把这个儿子给封住的，老鼠永远赶不到根上去qwq）

我们根据每个节点儿子的数量加以讨论。

- 儿子数量=1。我们花费一次代价把它堵死。然后这个节点就和叶子一样了了。这对应如下的代码:

```cpp
	if(son == 1) dp[x] = deep[x] - deep[top] + sum + 1;
```

- 儿子数量>1。假如说我们已经计算出儿子节点们的权值。贪心的想，我们肯定要封住一个权值最大的么！所以，老鼠理所应当的走入了权值第二大的儿子里去。注意这一次封路径并不算浪费，毕竟老鼠到了叶子之后，这个儿子还是的封的。这对应如下的代码：

```cpp
else dp[x] = max2dp;
```

下面的图例中展示了儿子数量>1的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/3yxrm7kf.png)

### case 3 任意情况

刚才文章中提到了这样的话

> 显然老鼠不会傻到直接向夹子走过去吧

不幸的是，这句话在这种情况下并不合法。考虑这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/g1y10v99.png)


我们不能简单地认为我们的答案是$DP_{mouse}$，而这当中的罪魁祸首就是：**从老鼠到根的路径上的节点，他们不在路径上的儿子！** 同时，这条路径上的DP值都是毫无意义的，但是你惊奇大发现**其他地方的DP值还是有意义的**，只不过他们的“深度”是 **以这个节点最浅的一个，在路径上的祖先为根产生的深度。** (因为这个祖先以上的路径并不需要被疏通)。

以下代码找出了这条路径。

```cpp
	for(int p = A ; p != B ; p = fa[p]) onpath[p] = true;
```

我们先把这些儿子缀在相应的节点上，按照DP值（从小到大）排个序。

~~我实在不知道该怎么讲了~~你打开标签发现有“二分答案”的标签，我们二分这个答案。可以证明$ans\in[dp_{mouse},2n]$.(最优情况&&1条边不会被操作大于两次)


我们模拟一下是否在规定的步数中结可以结束。因为造成我们不确定的因素是**从老鼠到根的路径上的节点，他们不在路径上的儿子**，所以我们让这个老鼠不停的往上跳，伺机进入一个（DP值比较大）的分支儿子。

设我们当前已经封禁的节点数量是$ban$，我们二分的答案是$x$。

- 如果当前节点就是老鼠所在的节点，那么我们能够进入儿子的最大值是$x-ban$

这很好理解。我们已经禁掉了一些路径，剩余还能封禁的路径就是$x-ban$(要减掉的原因是：这些封禁掉的路径在老鼠到达最深节点之后就会**浪费**)。如果老鼠走到了DP值$>x-ban$的儿子里面，我们就不可能再用剩余的次数把他赶回根节点上去。

- 如果当前节点不是老鼠所在的节点，那么我们能够进入儿子的最大值是$x-ban+1$

老鼠代替我们封掉了这个节点的（在路径上的）儿子节点，所以可以等价于x++。

我们从$mouse$出发，向上跳到$root$，并且按照DP值从小到大的顺序扫描其其路径上的分支儿子。如果发现有不合法的，我们就把它的父亲边给堵住，即ban++。

我们模拟一下这个过程：

- 在当前节点是$mouse$的时候，我们最多封禁1条边；

- 在当前节点是$fa(mouse)$的时候，我们最多封禁2条边；

- 在当前节点是$fa(fa(mouse))$的时候，我们最多封禁3条边；

- ......

如果封禁的次数超限了，那么我们就return false;如下图所示描述了一次成功的check：按次序堵截打叉的边，可以保证在规定次数内使得老鼠到达根。

![](https://cdn.luogu.com.cn/upload/image_hosting/yiyu215f.png)

由此我们写出了如下的代码:

```cpp
bool check(int x) {
	int ban = 0 , id = 0;
	for(int p = A ; p != B ; p = fa[p]) {
		for(int i = 0 ; i < branch[p].size(); ++i)
			if(branch[p][i] + ban > x + (p!=A))
				ban++;
		if(ban > ++id) return false;
	}
	return true;
}
```

最后套个二分的模板就可以了。$O(NlogN)$

---

## 作者：lgnotus (赞：4)


## 题解

树上博弈是真的好玩……

首先看到这道题发现答案具有单调性，于是想到可能会二分。

先钦定陷阱所在的结点为根节点，这样老鼠向陷阱走的过程就是向根节点走的过程

先考虑这样一种情况：

**Bob 刚开始只在当前子树中向下走**

通过画图模拟可以发现，当 Bob 向下走走到叶子节点或其通往更深层的子树的边都被 Alice 封住的时候，它就陷入了一个通往父亲结点的路被弄脏，向下又走不通的局面，这时 Alice 不要先去清理路径让 Bob 向上走，而是要去做另一些有意义的事情

![](https://z3.ax1x.com/2021/10/11/5ZqDUO.png)

如上图，**假设**（注意只是假设，不要去问为什么 Alice 刚开始不去堵 $2\to 4$ 的边） Bob 初始在二号结点，最后被堵在了七号节点，棕色的边是被弄脏了的边，红色的是被堵住的边。现在 Alice 该做什么呢？

显然不是去清理路径直接放 Bob 向上走，因为 Bob 向上走的时候可能会遇到其他可以进入的子树再跳下去，不会让减少 Alice 的操作次数。所以 Alice 要趁 Bob 不能走的时候，将其之后向上走的路径上通往其他子树的边全部堵住。

接下来来探究 Bob 的策略：

设 $dp_u$ 为以 $u$ 为根的子树中， Bob 在 $u$ 处出发，双方均使用最优策略，且 Alice 使得 Bob 最后回到 $u$ 处，Alice 的最少操作数

如果 Bob 在 $x$ 处且他已经知道了所有 $y\in son(x)$ 的 $dp$ 值，显然，他会往最大的那个 $dp_v$ 的子树走，然而 Alice 希望花费数尽可能的少，所以他会堵住通向 $dp$ 值最大的那棵子树的边，于是状态转移方程呼之欲出：
$$
dp_u=|son(u)|+2\text{nd}\max_{v\in son(u)}dp_v
$$
其中，$\text{2nd}\max$ 是次大值

但是，**Bob不一定刚开始只在当前子树中向下走，也有可能向上走**

考虑二分

求出 $g_x$ 表示根节点到 $x$ 的路径中所有分叉路数量。
$$

g_x=\begin{cases}
0,&x=t\\
g_{fa}+|son(u)|-1,&x=m\\
g_{fa}+|son(u)|-2,&otherwise\\

\end{cases}

$$
设 $t\to m$ 的路径上结点集合为 $S$

对于路径上每一个点 $u$ 的分叉子树结点考虑，如果其满足以下条件，则需要堵住通往这条分叉子树的边：
$$
u\in S,v\in son(u),v\not \in S
$$
$$
g[u]+dp[v]>mid
$$
当前 $mid$ 不合法的条件：

* $mid$ 次操作次数不够用
* $Alice$ 的手速不如 $Bob$ ，即当 $Bob$ 走到 $u$ 处时，但 $u$ 处需要被堵住的通往分叉子树的边没有被堵住



---

## 作者：xiwang (赞：3)

这题是真的迷  
看了一堆东西才大概懂了一点，然后我就来水个题解  
首先为了各种方便，我们把t搞成根，完了m->t的路径  
就是从m一路向上爬了  
完了我们看看耗子的最优策略是啥  
稍有常识的人都能看出，耗子当然应该见的风是的雨只要当前节点有可以往下走的子树就滚下去了  
于是我们考虑二分答案，完了发现我们似乎可以处理出让这只耗子到每个点我们所要付出的代价f(i)  
完了f(i)我们想啊，最坏情况下我们是不是要赶紧一发把最小代价最大的边划掉？  
裆燃了！（~~烈焰裤裆？~~）  
完了我们就跳次大值转移就是了，边界就是度数1的叶子是0，度数2的链上是1  
完了我们揪出来t->m的路径，每次判断一个答案可不可行的时候就枚举路径上每个点算一算这些点的分枝付出代价能接受不，能就放着，不能就记录这条边必须划掉，完了看必须划掉的边能划完不，再看看这个点的代价加上之前用掉的步数够mid不就好了  
完了二分时候一堆细节  
垃圾代码：  
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;
typedef long long ll;
const int N=1000000+10;
int n,t,m;
struct edge{
	int to,next;
}g[N<<1];
int head[N],tot=1;
int d[N];
void add(int st,int ed){
	g[tot]=(edge){ed,head[st]};
	head[st]=tot++;
	d[st]++;
}
int f[N];
int fa[N];
int s[N],top;
int sm[N];
void dfs(int x){
	for(int i=head[x];i;i=g[i].next){
		int v=g[i].to;
		if(v==fa[x])continue;
		fa[v]=x;
		dfs(v);
	}
	if(d[x]==1)f[x]=0;
	else if(d[x]==2)f[x]=1;
	else if(d[x]>2){
		int mx=-1,m2=-1,p=-1;
		for(int i=head[x];i;i=g[i].next){
			int v=g[i].to;
			if(f[v]>mx&&v!=fa[x])mx=f[v],p=v;
		}
		for(int i=head[x];i;i=g[i].next){
			int v=g[i].to;
			if(f[v]>m2&&v!=p&&v!=fa[x])m2=f[v];
		}
		f[x]=m2+d[x]-2+1;
	}
}
bool chk(int mid){
	int re=0;
	for(int _i=1;_i<top;_i++){
		int c=0;
		for(int i=head[s[_i]];i;i=g[i].next){
			int v=g[i].to;
			if(v!=s[_i+1]&&v!=s[_i-1]&&sm[_i]+f[v]+1-(_i!=1)>mid-re)c++;
		}
		re+=c;
		if(re>mid||re>_i)return 0;
	}
	return 1;
}
int main(){
	int x,y,z;
	scanf("%d%d%d",&n,&t,&m);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(t);
	for(int i=m;i!=t;i=fa[i])s[++top]=i;s[++top]=t;
	for(int i=top-1;i;i--)sm[i]=sm[i+1]+d[s[i]]-1-(s[i]!=t);
	int l=0,r=n,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(chk(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
```

---

## 作者：Exp10re (赞：2)

见到两遍了，写一下题解。

这道题目也是我写出的第一道黑题。

以下均为考场思路。

文章同步于 [CSP 2023 游记](https://www.luogu.com.cn/blog/Exp10re/csp-2023)。

## 解题思路

记 $S$ 到 $T$ 的路径为主干道，与主干道直接相连且不在主干道上的边为支路。

手玩一下发现人和老鼠的操作必定按照下面四个步骤依次进行：

1. 老鼠沿主干道移动，同时人堵住一条支路。
2. 老鼠在某个节点沿一条支路进入一个子树，然后被自己弄脏的边堵死在某个叶子结点。
3. 人在老鼠被堵死的时候堵住老鼠当前位置到 $T$ 的路径上的所有支路，然后清理老鼠当前位置到 $T$ 的路径上所有被弄脏的边。
4. 老鼠此时只能走到 $T$，游戏结束。

步骤 1 和 3 的人的操作比较难模拟，注意到操作 2 是树上操作，可以用树形 DP 来计算，那么先考虑操作 2。

记 $f_x$ 表示若老鼠进入该树根节点后，在该树内的操作数。

考虑当某个节点的所有子树都计算完毕后，老鼠进入该节点时人类的操作：

- 如果人类不堵与 $f$ 最大的子树相连的边，那么老鼠肯定会走这条边，到达 $f$ 值最大的子树。
- 否则，老鼠会进入 $f$ 值次大的子树。

显然让老鼠进入 $f$ 值次大的子树一定比老鼠进入 $f$ 值最大的子树好，那么转移就应该从 $f$ 值次大的子树进行转移。

老鼠进入该子树后，在操作 3 时还需要堵住其其他支路。可以直接在此处计算。那么转移方程显然：记 $cnt_x$ 表示 $x$ 子树个数，$son_x$ 表示 $x$ 的某个子树，则有：

$$f_x=\underset{y\in son_x}{\operatorname{2ndmax}}{f_y}+cnt_x$$

把步骤 2 考虑完之后尝试考虑步骤 3，假定老鼠在步骤 2 中从节点 $p$ 进入子树 $x$ 然后被困死，那么从 $p$ 到 $T$ 的所有支路都必须堵住。这个可以用前缀和维护，不多赘述。

步骤 1 堵路的操作比较难想，这时我们可以转换思路。注意到答案具有单调性，可以二分答案转化成判定性问题。

假定老鼠走主干道已经到达了某个节点 $p$，它得知你期望的操作次数为不大于 $m$，那么考虑老鼠会如何进入子树。

如果现在已经堵住了 $u$ 次路，对于某一个子树 $x$，老鼠只会在 $f_x+sum_p+u \gt m$ 的情况下才会钻进这个子树。

正确性证明：若 $f_x+sum_p+u \leq m$，那么老鼠进入这个子树后，人必定能用 $f_x+sum_p+u$ 次操作完成游戏，由此说明人可以在 $m$ 次操作内完成游戏。在目标明确的情况下，老鼠的目的就是证明人不可以在 $m$ 次操作内完成游戏。因此，进入该子树一定对老鼠不优。

既然对于每个子树钻或不钻对于老鼠而言是一定的，那么人的操作就显然了：人需要按照从 $S$ 到 $T$ 的顺序堵住所有老鼠可能会进入的子树与主干道的相连边。如果老鼠在到达某个节点的时候还有可钻的子树，那么说明答案大于 $m$，否则 $m$ 就是一个可行的答案。

至此，这道题的思路就明确了。

## 代码

可以结合代码食用，虽然代码没写注释，但是思路大致清晰。

代码太长，扔到[剪贴板](https://www.luogu.com.cn/paste/dxxn46jf)了。

---

## 作者：lyxeason (赞：2)

首先可以把陷阱所在的房间设为根节点，这样方便计算。

设老鼠现在在 $x$ 点，则老鼠的移动可以分两种情况考虑：

- 向 $x$ 的子树移动
- 向 $x$ 的父节点移动

先考虑第一种情况，向子树移动，考虑使用动态规划，设 $f_i$ 表示从 $i$ 点老鼠走向其子树后又被管理员逼回到了 $i$ 点的最少操作数。

这样设计状态是因为可以发现，老鼠从 $i$ 点一直往下走最终会到叶子节点，并且往上走的路都被它自己来的时候弄脏了，它就被堵在了叶子节点上。此时把它走到叶子节点的这条路径上的其它的分支都堵死，再把路径上的边都擦干净，这样老鼠就会沿着来时的路径回到 $i$ 点。

考虑状态转移，设老鼠现在在 $i$ 点。因为管理员和老鼠都使用最优策略，而老鼠希望管理员的操作数尽量多，那么老鼠肯定会向 $i$ 的儿子中，$f$ 值，即动态规划值最大的子节点移动，因为这样可以使管理员花费最多的操作数再回到 $i$。管理员则希望操作步数尽量少，所以他的最优策略是将连向动态规划值最大的子节点的边堵住，那么老鼠会向动态规划值第二大的子节点移动。这样，就得到了状态转移方程：
$$f_i=\mathrm{2ndmax}_{\text{j是i的子节点}}\{f_j\}+s_i$$

这里的 $s_i$ 表示 $i$ 点有多少个子节点，$\mathrm{2ndmax}$ 表示取第二大。$+s_i$ 其实是 $+s_i-1+1$ 化简之后的结果。$+s_i-1$ 是因为这是从 $i$ 的一个子节点走上来的，那条边已经被弄脏，相当于被堵上了，所以只用堵上 $i$ 向其它子节点的连边就可以了。再 $+1$ 是因为从 $i$ 走到这个子节点时已经使这条边弄脏，现在又被堵回到这个子节点要再回到 $i$ 点需要擦干净这条边，有一次操作。

那么解决了从 $i$ 点向下走的情况，来看向上走的情况，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/wr8sqd77.png)
$t$ 点就是陷阱所在的点。老鼠可以先向父节点走一段距离，再向下走。这种情况很难处理，因为无法确定老鼠在向父节点移动多少步后向下可以使老鼠最优。

考虑到答案具有单调性，可以二分答案操作步数。

在二分中，每次判断是否老鼠无论从起始点 $M$ 向上走多少步都能在现在二分到的操作步数内堵到陷阱点。因为管理员无论如何都不能堵住向父节点走的边，否则就相当于直接让老鼠根本走不到作为根节点的陷阱点。具体看代码。

------------
### 代码
###### 代码里有注释
```cpp


#include <cstdio>
#include <cstring>

using namespace std;

int N;
int T;
int M;
int h[1000009];
int nxt[2000009];
int to[2000009];
int idx;
int dp[1000009];
int sum[1000009]; //在二分中有用到，表示将老鼠从当前点逼到根节点即陷阱点需要到少步操作
int fa[1000009];
bool st[1000009]; //也是在二分中用到，起始点的所有祖先节点st值为true
int res;

inline void Add (int a, int b) {
    nxt[idx] = h[a], to[idx] = b, h[a] = idx++;
}

void In () {
    int a;
    int b;
    
    memset(h, -1, sizeof(h));
    scanf("%d%d%d", &N, &T, &M);
    for (int i = 1; i < N; i++) {
        scanf("%d%d", &a, &b);
        Add(a, b), Add(b, a);
    }
}

void Get_Dp (int x, int p) { //求出每个点的动态规划值，dp就是前面的f
    int v;
    int mx1 = 0; //最大值
    int mx2 = 0; //次大值
    int siz = 0; //子节点数量

    fa[x] = p;
    for (int e = h[x]; ~e; e = nxt[e]) {
        v = to[e];
        if (v == p) continue;
        siz++;
    }
    if (x != T) sum[x] = sum[p] + siz - 1 + (x == M);
/*求sum值时因为把老鼠从当前点逼到根节点可以从父结点的值递推而来，就相
当于从当前点逼到父节点再从父节点逼到根节点。如果当前点不是起始点，那
么肯定是从它的某个子节点上来的，则那条连边已经被弄脏，不用再堵。但如
果它是起始点，那么就不是从哪个子节点来的，需要把所有子节点都堵上。*/
    for (int e = h[x]; ~e; e = nxt[e]) {
        v = to[e];
        if (v == p) continue;
        Get_Dp(v, x);
        if (mx1 < dp[v]) mx2 = mx1, mx1 = dp[v];
        else if (mx2 < dp[v]) mx2 = dp[v];
    }
    dp[x] = mx2 + siz;
}

bool Chk (int x) {
    int v;
    int cc = 1;
    int vv; //不要在意奇怪的命名。。

/*
这里的 cc 是因为老鼠再往上走时不会停下来，要堵就必须老鼠边走管理员边
堵，但如果老鼠现在在的节点上，向两个不同的子节点走都不能使管理员在x步
内把老鼠逼回来，且管理员不能一次操作堵两条边，那么就不能使老鼠在x步内
被逼回。(管理员堵其中一条边，老鼠就走另一条边，总会使步数超过x步)。

但如果在现在的节点上老鼠无论走哪个子节点都无法使步数超过x步，那么管理
员就可以在这时候将父节点或祖先节点的某个无法在x步内将老鼠逼回的边提前
堵上。
*/

    for (int i = M; i != T; i = fa[i]) {
        vv = 0;
        for (int e = h[i]; ~e; e = nxt[e]) {
            v = to[e];
            if (st[v] || dp[v] + sum[i] <= x) continue; //如果在当前这个点上向子节点走需要的步数不大于二分到的步数x，或者它刚刚从这个子节点移动上来，都不用管
            if (!cc) return false;
            cc--, vv++;
        }
        x -= vv, cc++;
    }
    return x >= 0;
}

void Solve () {
    int l;
    int r;
    int mid;

    Get_Dp(T, 0);
    for (int i = M; i; i = fa[i]) st[i] = true;
    l = 0, r = 2 * N;
    while (l <= r) {
        mid = l + r >> 1;
        if (Chk(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
}

void Out () {
    printf("%d\n", res);
}

int main () {

    In();
    Solve();
    Out();

    return 0;
}
```

---

## 作者：出言不逊王子 (赞：1)

起初考虑以 $s$ 为根，则每次都要往下走。但是这样一来 $s\to t$ 不能很好地和其他操作区分开来，所以改成以 $t$ 为根，这样每一步都是往上走了。

我们不难发现有一个神秘权值 $f_x$，满足老鼠会尽可能往 $f_x$ 大的走。多余的操作来源于老鼠向下走，所以我们**估计** $f_x$ 为**向下**往 $x$ 走会给管理员多带来的操作次数。

显然每次要炸最大的子树，老鼠就会走第二大的子树，因为最终要往上走，所以往下走最终都得回来，我们**定义** $f_x$ 为从 $x$ 启动再回家的最小成本，显然有 $f_u=\text{2nd}\max f_v+n_v-1+1$（其中 $n_v$ 表示 $u$ 的儿子 $v$ 的个数），表示从某个 $v$ 进去的边不用砍掉，但是要复原，等走出来的那一刻，又被烧毁了。

观察样例解释，我们发现只要困住老鼠，我们就能改天换地了。等老鼠被放出来的那一刻，它就只能追随我们给他的唯一路径走了。因为改天换地砍掉的边无论如何都要被砍掉，所以我们还不如一把他困住就砍。

具体地，我们定义 $cnt_u$ 表示从 $t$ 走到 $u$ 中间有几条没用的边。只要老鼠走进一个子树，我们就可以用 $f_v+cnt_{u}+[u=s]$ 的代价困住老鼠，把没用的边权砍了，再复原相应的边，看着老鼠走出大山。

但是老鼠很聪明，他可以跳过任何子树。一旦往上飞，就回不来了。所以我们可能扑了个空，但是不一定……我们没法确定啥时候会扑空啥时候不会扑空。**换句话说，这是一个动态的过程，无法直接用常规方法去做。**

因此我们考虑二分。在确定了上界之后，这就变成了一个判定问题。

既然是判定，那么我们就模拟从下往上跳的过程，每到一个点就枚举当前子树，如果可能被爆（$f_v+cnt_{u}+[u=s]>cur_k$），那就给他提前割掉。否则老鼠进去了就直接启动，反正次数足够，万事大吉。

考虑[这篇帖子](https://www.luogu.com.cn/discuss/348351?page=3)的疑问，我们回到 $cnt$ 的定义，$cnt$ 表示如果在此启动，还要砍掉几条边。

如果有一条边已经被砍掉了，那么 $cnt$ 自然已经被扣掉了 $1$（**因为这条边已经被砍掉了，不用再砍第二次了**），与其一同被扣掉的就是 $cur_k$ 的 $1$，二者相互被抵消。这就是为什么在对一个点做决策时，$cur_k$ 中途不用变化。

接下来暴力判定即可。往上跳了 $x$ 格，意味着我们现在有 $x$ 个机会。如果当前需要的机会太多了，判定失败，这个操作上限还不够用。

二分上界是 $n$，因为实在不行我们可以把 $t-s$ 以外的边全砍了，也不到 $n$ 条。特判 $s=t$ 的情况，二分下界要取 $0$。

```cpp
#include<bits/stdc++.h>
#define fs(i,x,y,z) for(int i=x;i<=y;i+=z)
#define ft(i,x,y,z) for(int i=x;i>=y;i+=z)
#define ll long long
#define ull unsigned long long
#define db double
#define ms(a,b) memset(a,b,sizeof(a))
#define sz(a) sizeof(a)
#define pii pair<int,int>
#define mid ((l+r)>>1)
using namespace std;
const int rw[]={-1,0,1,0,-1,1,-1,1},cl[]={0,1,0,-1,-1,1,1,-1};
const int N=2000001,inf=0x3f3f3f3f;
inline int read(){
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
vector<int> e[N];
int n,t,s,fa[N],sons[N],resu[N],deg[N],dp[N];//vis[i]=1表示i有统战价值，son[i]，son2[i]表示前两重的儿子 
void dfs0(int now,int f){
	int son=0,son2=0;
	fa[now]=f,sons[now]=deg[now]-bool(f);//你有父亲吗？ 
	if(f) resu[now]+=sons[now]-1;//总有一条边是u\to v 
	for(auto v:e[now]){
		if(v==f) continue;resu[v]=resu[now];
		dfs0(v,now);if(dp[v]>dp[son]) son2=son,son=v;
		else if(dp[v]>dp[son2]) son2=v;
	}
	dp[now]=dp[son2]+sons[now]-1+1;//要图几次，特别地，还要一个1代表复原1 
}
bool chk(int g){
	int need=0,pre=0,now=1;
	for(int u=s;u!=t;u=fa[u]){ 
	//	if(g==2)cout<<u<<' '<<need<<"?\n";
		int cur=need;//除了我要砍掉几个人 
		for(auto v:e[u])
			if(v==pre||v==fa[u]);else{
			//	(g==2)&&cout<<dp[v]<<','<<resu[now]<<','<<v<<','<<now<<'\n';
			if(dp[v]+resu[u]+bool(u==s)+cur>g) need++;
		}
		//如果照常爆了的代价大于tme，那你必须杀
		//否则的话，进来这个子树，直接——启动！ 
		if(need>min(now,g)) return 0; 
		//v照样砍，now其他边也得砍掉，如果可以允许滞留的话就留下来 
		//特别地，起点本身是大家一起图图图
		//我们计算时会扣掉一个叉边，但是你得加上去啊，如果下面空了的话那也得和你爆了 
	//	if(g==2) cout<<u<<' '<<need<<'\n';
		pre=u;now++;
	}
	return 1;//归家之路 
}
signed main(){
	n=read(),t=read(),s=read();
//	printf("%d",n+m);
	fs(i,1,n-1,1){
		int u=read(),v=read();deg[u]++,deg[v]++;
		e[u].push_back(v);e[v].push_back(u);
	}
	dfs0(t,0);
//	fs(i,1,n,1) cout<<dp[i]<<'$'<<resu[i]<<'\n';
	int l=0,r=n,res=0;while(l<=r){
		if(chk(mid)) res=mid,r=mid-1;
		else l=mid+1;
	}cout<<res;//<<' '<<chk(res);
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：1)


**以陷阱为根建树**

首先是一个很重要的结论，抑或是一个性质
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201203175533297.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)

假设现在是这样一个状态（命名为**STA1**），老鼠在一棵子树的根，这棵子树没有任何东西，老鼠所在的点与父亲的边是脏的（为什么会是脏的？因为老鼠刚从上面走下来）

然后我们堵住一条边，老鼠会逃往一个它认为更优的地方
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201203174802352.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)
我们再将一军
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201203174832254.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)
好，现在，我们把老鼠堵在了某一个地方，**老鼠动不了了**，我们可以慢慢操作

还可以推出更一般的情况，我们先堵住一个旁支，再擦干净一个地方，老鼠由于本能会走过去，然后那地方又脏了

![在这里插入图片描述](https://img-blog.csdnimg.cn/20201203181105327.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)
现在我们只用了4次操作将老鼠**堵**在了“起点”

我们将老鼠被堵在“起点”的状态命名为**STA2**

结论是每当老鼠处于等价于$STA1$的状态，即往下走了一步走到了$i$，我们可以用最少的操作次数把老鼠堵回$i$，变成$STA2$，令$dp_i$表示这个最少次数，我们可以把这个$dp$数组先用树形dp求出来
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201203180050640.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)
假设我们现在在点$i$，要求出$dp_i$，现在已经有了$i$的儿子们的dp值，假设是这样

按照人的最优策略，会选择堵住$i->son1$的边，因为不堵的话，老鼠会进去使得人类的操作数很大。所以我们堵住$i->son1$，接着老鼠因为它的最优策略会跑到$son2$，**因为$dp_{son2}$是次大值**，然后$i->son2$就脏了，我们可以花费$dp_{son2}$将老鼠堵在$son2$，在把$i$通向其他儿子的边给堵住($i->son3$)，这是一定要堵得，因为不堵的话，当我们把老鼠放出来的时候它会跑进去

这些都搞定之后，把$i->son2$擦干净，老鼠跑回$i$，又被堵住了

发现我们其实对所有$i->v(\text{v is son of i})$的边都操作了一遍

这样转移方程就有了

$dp_i=$次大值$(dp_{\text{son of i}})+(deg_i-1)$(这部分意思是把所有边操作一遍)

如果没有次大值，那就是0

**到现在为止，我们可以得到每个点$i$在STA1，把它变成STA2的最少操作数**

**我们还可以知道，一旦老鼠往下走一步，那么就会进入STA1状态，我们就可以把它变成STA2，然后它就坐以待毙了**

现在求老鼠在某一个地方往下走一步之后，我们还需要多少操作数
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201203181726336.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01vZGVzdENvZGVyXw==,size_16,color_FFFFFF,t_70)
假设老鼠从$u$往下走到了$i$，我们首先用$dp_i$让它**坐以待毙**

然后我们需要让老鼠乖乖听话，这样肯定是与我们最优的，于老鼠是无可奈何的

所以我们应该把老鼠到根的路径上的其他支链都封住

令$cnt_u$表示从$u$往下走一步之后，我们需要堵住的支链数

$cnt_u=cnt_{\text{father of u}}+deg_u-2$，-2的意思是减去$u$到父亲的一条边，减去$u->i$

然后老鼠从一个点$u$往下走一步到达$i$之后我们需要的操作数是
$dp_i+cnt_u+1(这是因为我们还要把u->i擦干净)$

但是老鼠很聪明，它也知道了往下走一步之后的操作数，他想要最大化操作数，它可能会选择从起点先往上走几步

所以老鼠走的过程可以分为两个

1.往上走几步（可以不走）

2.往下走到一棵子树，这时候操作数确定了

然后我们最小化人的操作数，用二分枚举答案，看看合不合理

对于每个$mid$

让老鼠从起点出发，往上走，每个时候，我们用$dp_i+cnt_u+1$算当前点跑儿子的操作数

不过如果$i$是起点的话，公式是$dp_i+cnt_u$因为可以少堵住一条边

然后当前是在$i$，如果一个儿子$u$满足$dp_i+cnt_u+1-(i!=start)>mid$，我们必须把$i->u$堵住

设共操作了$s$次

当满足$mid<s或s>往上跳次数+1（意思是老鼠会比人更快的跑进一个子树）$的时候，我们就输了，这个mid不合法

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 1000010
using namespace std;
struct Edge{
	int to, next;
}edge[maxn << 1];
int num, head[maxn], fa[maxn], n, dp[maxn], cnt[maxn], stk[maxn], top, deg[maxn];
int rt, st;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

void addedge(int x, int y){
	edge[++num] = (Edge){y, head[x]}, head[x] = num;
}

void dfs(int u, int pre){
	fa[u] = pre;
	int fir = 0, sec = 0;
	for (int i = head[u]; i; i = edge[i].next){
		int v = edge[i].to;
		if (v == pre) continue;
		dfs(v, u);
		//printf("%d -> %d : %d\n", u, v, dp[v]);
		if (dp[v] >= fir) sec = fir, fir = dp[v];
		else if (dp[v] >= sec) sec = dp[v];
	}
	if (u != rt) dp[u] = sec + deg[u] - 1;
//	printf("%d %d %d %d\n", u, dp[u], sec, deg[u]);
}

bool check(int mid){
	int sum = 0, tmp;
	for (int i = 1; i < top; ++i){
		tmp = 0;
		int u = stk[i];
		for (int j = head[u]; j; j = edge[j].next){
			int v = edge[j].to;
			if (v != stk[i - 1] && v != stk[i + 1] && dp[v] + cnt[i] + 1 - (i > 1) > mid)
				++tmp;
		}
		sum += tmp, mid -= tmp;
		if (mid < 0 || sum > i) return 0;
	}
	return 1;
}

int main(){
	n = read(), rt = read(), st = read();
	for (int i = 1; i < n; ++i){
		int x = read(), y = read();
		addedge(x, y), addedge(y, x);
		++deg[x], ++deg[y];
	}
	dfs(rt, 0);
//	for (int i = 1; i <= n; ++i) printf("%d %d\n", i, dp[i]);
	for (int i = st; i; i = fa[i]) stk[++top] = i;
	for (int i = top - 1; i; --i)
		cnt[i] = cnt[i + 1] + deg[stk[i]] - 2;
	int l = 0, r = 1e8, ans;
	while (l <= r){
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：OrezTsim (赞：0)

这题和省选联考 2024 Day2 T1 有点像啊。

考场上没写出来那题。

---

方便起见，先把树根设置为 $t$。

因为老鼠不会通过脏的走廊，所以它一定会在走了一定步数后被困在某个叶子节点 $x$。

那么管理者可以趁老鼠被困在 $x$ 时堵住 $x \rightarrow t$ 路径上所有点延伸出来的**其他**边，接着擦除 $x \rightarrow t$ 路径上所有脏的走廊，从而老鼠被迫前往 $t$。

可以发现，如果老鼠往当前点的子树里走而非往当前点的父亲走，我们就可以预见老鼠会在这个子树包含的叶子结点之一停下。

那么现在管理者要做的就是干预老鼠困住自己的这个过程，从而使得老鼠走向对管理者有利的点。

而老鼠也会选择对自己有利的点，所以它可能会先不断往父亲跳，然后往子树里跳，最终被困住。

看到处理子树信息就可以想 DP 了。

设 $dp_i$ 表示老鼠从 $i$ 往 $i$ 的子树走到达某个叶子再被迫回到 $i$ 的最小代价。

令 $son_i$ 表示 $i$ 的儿子个数，$s_{i,j}$ 表示 $i$ 的第 $j$ 个儿子。

假设我们知道了所有 $dp_{s_{i,j}}$，那么肯定可以在老鼠来到 $i$ 的时候封掉 $dp$ 值最大的 $s_{i,j_1}$，老鼠就会贪心地前往 $dp$ 值第二大的 $s_{i,j_2}$。

因为把老鼠逼进 $s_{i,j_2}$ 之后，我们还要让老鼠重新回到 $i$，并且要禁止它再次进入 $i$ 的子树，所以最终的形态就是 ban 掉除了 $dp$ 次大的 $s_{i,j_2}$ 以外的所有点，所以除了不让老鼠进入最优的节点之外，ban 掉儿子的顺序并没有任何影响，反正总共 ban 掉了 $son_i-1$ 个儿子。

另外，从 $s_{i,j_2}$ 回到 $i$ 还要擦除 $i \rightarrow s_{i,j_2}$ 这条脏的走廊，所以答案还要 $+1$。

那么 $dp_{i}=dp_{s_{i,j_2}}+son_i$。

```cpp
const int N=1e6+10;
int n,m,rt,len,p[N],dp[N],fa[N],pre[N];
vector<int>g[N];

void dfs1(int x,int f) {
    if(fa[x]=f) g[x].erase(find(all(g[x]),f));
    for(int to: g[x]) dfs1(to,x);
}

void dfs2(int x) {
    if(g[x].empty()) return;
    int mx1=-1,mx2=-1;
    for(int to: g[x]) {
        dfs2(to);
        if(dp[to]>mx1) mx1=dp[to];
        else if(dp[to]==mx1) swap(mx1,mx2),mx2=dp[to];
        else if(dp[to]>mx2) mx2=dp[to];
    }
    mx2=max(mx2,0);
    dp[x]=mx2+g[x].size();
}
```

因为当且仅当老鼠进入某个点的子树之后，我们才能正确地计算总代价，而目前管理者完全不知道老鼠会怎么走，所以二分答案，即管理者可支配的操作数 $mid$，那么老鼠就可以根据管理者可支配的操作数而决定自己要前往哪个节点。

管理者所做的就是堵住所有会使得代价 $>mid$ 的儿子，而老鼠所做的就是前往会使得代价 $>mid$ 的儿子，如此 $mid$ 就能实时刻画管理者和老鼠的操作，二分也就合理了。

$\text{check}$ 也就呼之欲出了。

```cpp
auto ck(int mid) -> bool {
    int tot=0;
    for(int i=1;i<len;++i) {
        int now=0;
        for(int to: g[p[i]]) {
            if(to==p[i-1]) continue;
            if(pre[i]+dp[to]+(i==1)>mid) ++now;
        }
        tot+=now,mid-=now;
        if(mid<0||tot>i) return false;
    }
    return true;
}
```

完整代码：

```cpp
#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
using namespace std;

const int N=1e6+10;
int n,m,rt,len,p[N],dp[N],fa[N],pre[N];
vector<int>g[N];

void dfs1(int x,int f) {
    if(fa[x]=f) g[x].erase(find(all(g[x]),f));
    for(int to: g[x]) dfs1(to,x);
}

void dfs2(int x) {
    if(g[x].empty()) return;
    int mx1=-1,mx2=-1;
    for(int to: g[x]) {
        dfs2(to);
        if(dp[to]>mx1) mx1=dp[to];
        else if(dp[to]==mx1) swap(mx1,mx2),mx2=dp[to];
        else if(dp[to]>mx2) mx2=dp[to];
    }
    mx2=max(mx2,0);
    dp[x]=mx2+g[x].size();
}

auto ck(int mid) -> bool {
    int tot=0;
    for(int i=1;i<len;++i) {
        int now=0;
        for(int to: g[p[i]]) {
            if(to==p[i-1]) continue;
            if(pre[i]+dp[to]+(i==1)>mid) ++now;
        }
        tot+=now,mid-=now;
        if(mid<0||tot>i) return false;
    }
    return true;
}

auto main() -> signed {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>rt>>m;
    for(int i=1,u,v;i<n;++i)
        cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
    dfs1(rt,0),dfs2(rt);
    for(int x=m;x;x=fa[x]) p[++len]=x;
    for(int i=len-1;i;--i) pre[i]=pre[i+1]-1+g[p[i]].size();
    int l=0,r=1e9,res;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(ck(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return cout<<res,0;
}
```

---

## 作者：hsaht2426 (赞：0)

#### 前言：

树形 $\text{DP}$ + 细节题。

此题解在结论处经进行了加粗而非思维处。

#### 思路/理论：

显然能不换根就不换根，反正是等价的，直接**以陷阱房 $t$ 为根**。

一种思路是考虑简单情形，但我太懒了就没发展。

直接考虑正解。首先整理一下我们的条件：

- 管理员可以进行：堵住/疏通/不操作，不操作不计入管理员操作

首先不操作很良心啊，说明管理员的**操作必须是有价值的**。考虑反面，直接去掉无价值操作。如何判断无价值操作？显然大力贪心。

考虑对于一个管理员的操作序列，分析交换邻项的代价。如果先疏通再堵住，显然没有先堵住再疏通优，即后者合法是前者合法的必要条件，原因是老鼠的**选择集合变大**了。显然就不必讨论前者了，结论是**先堵住再疏通一定最优**。

考虑疏通，显然**最终老鼠的路径是唯一的**，那么老鼠路径上的所有位置一定会被堵住或被弄脏，反推得初始时**老鼠**无法反复走，**位于一个点上**。

回到先做的堵住操作，整理得堵住操作的目标 $1$ 是使**老鼠位于一个点上**，堵住操作的目标 $2$ 是使**最终老鼠的路径是唯一的**，调整法易得先做前者更优。

继续考虑堵住，事实上很难一眼看堵住操作的最优策略，从老鼠下手。

- 老鼠可以进行：向上走/向下走。

显然是要分讨上下的。

1. 向上走：

暂时不会，放一放。

2. 向下走：

然而你还是不知道要堵住哪条边。继续考虑老鼠，发现老鼠只能向下走。

不知道为什么但是考虑树形 $\text{DP}$，每次只需要选出答案最大的子树删掉即可。

考虑之后的堵边部分 $2$，树外的所有位置不受老鼠影响，同样可以树形 $\text{DP}$。

具体的，设 $f_u$ 代表从老鼠当前在 $u$，并且一定往下走的最小操作次数，$g_u$ 代表**使得**老鼠被赶到 $u$ 后从 $u$ 子树开始往上走路径唯一的最少操作次数。

#### 考虑初值：

$f$ 在叶子就已经封死，无需操作，有 $f_v=0$。

$g$ 在根就已经在陷阱，无需操作，有 $g_{root}=0$。

#### 考虑转移：

建议画图理解。

$f_u$ 转移分成堵边(不堵父亲，$d_u-1$ 条边)，疏通（仅一条）。

式子：$f_u =\operatorname{2ndmax} f_v +(d_u - 1)  + 1$

$g_v$ 转移只用堵边(不堵父亲与子节点，$d_u-2$ 条边)，但要特判：

$First.$ 考虑老鼠若向上走，从 $u$ 进入时会额外弄脏一条边，可以少堵一条，而直接从 $m$ 向下不会。这个写到转移里没必要，可以放在最后计算。

$Second.$ 树根不需要进行计算。需特判，但此题数据较水此处不判也能过。

式子：$(u \ne t) g_v=g_u+ d_u - 2$

那么老鼠从 $fa$ 向下走入 $u$，代价即为 $f_u + g_u + 1$。

此部分复杂度 $O(n)$，细节较多。

代码：
```cpp
void dfs(int u,int fa){
	int mx1=0,mx2=0;
	for(int v:a[u]){
		if(v==fa) continue;
		nxt[v]=u;
		if(u!=t) g[v]=g[u]+a[u].size()-2;
		else g[v]=0;
		//fa and v;
		dfs(v,u);
		int x=f[v];
		if(x>mx1) swap(mx1,x);
		if(x>mx2) swap(mx2,x);
	}
	f[u]=mx2+a[u].size()-1;
	res[u]=f[u]+g[u]+1-(fa!=m);//clear u->nxt_u
}
```
3. Re：向上走

现在我们需要得知老鼠究竟什么时候会向下走，此时会堵什么边。

继续分讨，显然的是你不能堵它向上的边，那么显然还是堵子树。

形式化一下堵边，对于每层你可以新增一个堵边的机会，换句话说前 $k$ 层最多堵 $k$ 条边，你要最小化堵边的数量与老鼠可走到的 $\text{DP}$ 的和。对于老鼠来说，每次都会选择可以选择的最大 $\text{DP}$ 值。

考虑转化为判定性问题：是否可以使操作次数小于等于 $mid$。这很好维护，转移到每层时，直接删去不合法的即可。所以可以二分，此部分复杂度 $O(n \log n)$。

代码：
```cpp
bool check(int mid){
	int p=mid-1,q=1,lst=0;//q=1,first once
	for(int u=m;u!=t;u=nxt[u]){
		int x=0;
		for(int v:a[u])
			if(v!=nxt[u]&&v!=lst)
				if(res[v]>p) x++;
		p-=x;
		q-=x;
		if(q<0||p<0) return true;
		q++;
		lst=u;
	}
	return false;
}
```
综上时间复杂度 $O(n \log n)$，空间复杂度 $O(n)$。

---

## 作者：D_F_S (赞：0)

辣鸡贪心做法。
## Solution：
前一半的处理与一般做法相同，考虑最后会走出的路径，应当是从 $m$ 走向 $m$ 到 $t$ 链上的某个子树，再直接走向 $t$。用 DP 求出 $f_p$ 表示进入 $p$ 的子树时子树内所需代价。

考虑确定进入哪一棵子树，进入 $v$ 子树的答案为 $f_v+s_{[fa_v,t)}$，其中 $s{[fa_v,t)}$ 表示 $[fa_v,t)$ 链上的点不在链上的儿子数量，因为从 $v$ 出来前要将剩余可走到的子树全部堵住。

贪心地将答案尽可能大的子树堵住，一次移动之前只能进行一次操作，相当于 $m\to t$ 的链上与 $m$ 距离 $<d$ 的点只能进行 $d$ 次堵住某个儿子的操作。

为满足这一条件，可考虑维护 $g$ 数组表示剩余操作次数的后缀和，初始状态下 $m\to t$ 的值为 $1\to dep_m-dep_t+1$ 的等差数列，一次操作等价于后缀 $-1$，任何时刻都需要满足 $g$ 均 $\ge0$，可以用线段树维护。

有了 $g$ 限制选取合法，接下来考虑如何找答案最大的子树。考虑动态维护 $f_v+s_{[fa_v,t)}$，每次删去一个子树，都会令深度不小于它的子树 $-1$，也可以用线段树维护。

综上，用两颗线段树即可维护贪心，复杂度为 $O(n\log n)$。

## Code：
```cpp
#include<bits/stdc++.h>
#define inl inline
#define pb push_back
using namespace std;
const int N=1e6+5;
struct A {int d,v; }a[N];
int n,T,S,tc,sc,ac,an=INT_MAX,at,f[N],tf[N],g[N],fa[N],so[N],s[N]; vector<int> e[N];
inl int Read()
{
	int s=0; char c; while(!isdigit(c=getchar()));
	for(;isdigit(c);c=getchar()) s=s*10+c-'0'; return s;
}
inl bool DP(int p)
{
	int fi=0,se=0; for(int v:e[p]) v!=fa[p]&&(fa[v]=p,DP(v))&&(so[p]=v);
	tc=0; for(int v:e[p]) v!=fa[p]&&(f[v]>fi?(se=fi,fi=f[v]):f[v]>se&&(se=f[v]));
	f[p]=se+e[p].size()-1; return (so[p]||p==S)&&p!=T?(s[++sc]=p,true):false;
}
#define L (p<<1)
#define R (L|1)
namespace T1
{
	struct TR {int mi,ad; }tr[N*4];
	inl void PU(int p) {tr[p].mi=min(tr[L].mi,tr[R].mi); }
	inl void PO(int p,int v) {tr[p].mi+=v; tr[p].ad+=v; }
	inl void PD(int p) {if(int &t=tr[p].ad) PO(L,t), PO(R,t), t=0; }
	inl void BD(int p,int l,int r)
	{
		if(l==r) return tr[p].mi=l, void();
		int md=(l+r)>>1; BD(L,l,md); BD(R,md+1,r); PU(p);
	}
	inl int MD(int p,int l,int r,int la)
	{
		if(r<la) return 0; if(l>=la) return tr[p].mi?(PO(p,-1),0):1; int md=(l+r)>>1;
		PD(p); int t=MD(R,md+1,r,la)||MD(L,l,md,la); PU(p); return t;
	}
}
namespace T2
{
	struct TR {int ma,mp,dl,dr,ad; }tr[N*4];
	inl void PU(int p)
	{
		tr[p]=tr[L].ma>tr[R].ma?tr[L]:tr[R];
		tr[p].dl=tr[L].dl; tr[p].dr=tr[R].dr; tr[p].ad=0;
	}
	inl void PO(int p,int v) {tr[p].ma+=v; tr[p].ad+=v; }
	inl void PD(int p) {if(int &t=tr[p].ad) PO(L,t), PO(R,t), t=0; }
	inl void BD(int p,int l,int r)
	{
		if(l==r) return tr[p]={a[l].v,l,a[l].d,a[l].d,0}, void();
		int md=(l+r)>>1; BD(L,l,md); BD(R,md+1,r); PU(p);
	}
	inl void MD(int p,int l,int r,int d)
	{
		if(tr[p].dr>d) return; if(tr[p].dl<=d) return PO(p,-1);
		int md=(l+r)>>1; PD(p); MD(L,l,md,d); MD(R,md+1,r,d); PU(p);
	}
	inl void CG(int p,int l,int r,int po)
	{
		if(l==r) return tr[p]={-1,0,a[l].d,a[l].d}, void(); int md=(l+r)>>1;
		PD(p); po<=md?CG(L,l,md,po):CG(R,md+1,r,po); PU(p);
	}
	inl int QR(int p,int l,int r,int po)
	{
		if(l==r) return tr[p].ma; int md=(l+r)>>1; PD(p);
		return po<=md?QR(L,l,md,po):QR(R,md+1,r,po);
	}
}
#undef L
#undef R
int main()
{
	n=Read(); T=Read(); S=Read();
	for(int x,y,i=1;i<n;++i) e[x=Read()].pb(y=Read()), e[y].pb(x);
	DP(T); for(int i=sc;i>=1;--i)
	{
 		int t=s[i]; g[i]=g[i+1]+e[t].size()-(bool)fa[t]-(bool)so[t];
		for(int v:e[t]) v!=fa[t]&&v!=so[t]&&(a[++ac]={i,f[v]+g[i]},0);
	}
	if(!ac) return puts("0"), 0; T1::BD(1,1,sc); T2::BD(1,1,ac);
	for(int i=1;i<=ac;++i)
	{
		int u=T2::tr[1].mp; an=min(an,at+max(T2::QR(1,1,ac,u),0));
		if(!u||T1::MD(1,1,sc,a[u].d)) break;
		++at; T2::MD(1,1,ac,a[u].d); T2::CG(1,1,ac,u);
	}
	printf("%d\n",min(an,at+max(T2::tr[1].ma,0))); return 0;
}
```


---

## 作者：jockbutt (赞：0)

题目读完后，发现这只老鼠确实不太好管啊。

# Solution

首先，老鼠窜来窜去很麻烦，想办法把老鼠给关住，然后给它铺一条大道让它直通陷阱。

但是，把老鼠关在哪里呢？

和同学手玩几局发现，老鼠最优状态是进入一个最难管的子树，然后等着管理员把它赶出来。

在不断地思考与手玩，我们得出了最优策略：

定义陷阱到老鼠初始位置的这一根链为“大道”，大道上有很多小的枝丫，老鼠一进入枝丫就再也不能主动进入大道了，只有被关死后等待收编。  
而管理员的最优策略就是将老鼠赶到一个代价最小的树后铺好让老鼠去陷阱的路，然后把它请回去。

因为计算管理员的最小步数很麻烦，我们采用二分答案。

我们先预处理一下在老鼠走大道时管理员不作为，等老鼠钻进某个枝丫的时候再阻拦老鼠，最后收编老鼠需要的代价。

因为管理员每一步只能拦住一条边，所以只能拦住那个子树内的一个最大值，所以说老鼠可以转进次优的子树内。

因为管理员在阻拦老鼠时用的步数在铺路时也要用到，所以管理员会在老鼠钻子树时一直阻拦它。

预处理后，我们开始二分，每次的检验函数都会搜索一遍大道，管理员会砍掉超预算的道路，如果管理员来得及砍完所有的道路，并且最后为老鼠铺路时不超预算，那么这个答案就是可以的。

具体实现细节看代码。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int BUFFER_SIZE=5<<20;
char RB[BUFFER_SIZE],*RP=RB,*RT=RB;
#define getchar() RP==RT?(RT=RB+fread(RB,1,BUFFER_SIZE,stdin),RP=RB,*RP++):*RP++;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')	{x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,s,t;
const int maxn=2e6+10;
int to[maxn],nt[maxn],head[maxn],cnt;
inline void addedge(int u,int v)
{
    to[++cnt]=v,nt[cnt]=head[u],head[u]=cnt;
}
int d[maxn],f[maxn],sum[maxn],sta[maxn],top;
int dp[maxn];
inline void dfs(int u,int fa)
{
    f[u]=fa;
    int mx=0,mxx=0;
    for(int i=head[u],v;i;i=nt[i])
    {
        v=to[i];
        if(v==fa)   continue;
        dfs(v,u);
        if(dp[v]>=mx)    mxx=mx,mx=dp[v];
        else    mxx=max(mxx,dp[v]);
    }
    // cout<<"u : "<<u<<"      mxx : "<<mxx<<endl;
    if(u!=s)    dp[u]=mxx+d[u]-1;  
}
inline bool check(int x)
{
    int tmp=0;
    for(int p=1;p<=top;++p)
    {
        int u=sta[p],v,tot=0;
        for(int i=head[u];i;i=nt[i])
        {
            v=to[i];
            if(v==sta[p-1]||v==sta[p+1]||v==s)  continue;
            if(sum[p]+dp[v]+1-(p!=1)>x) tot++;
        }
        // cout<<tot<<"  ";
        tmp+=tot,x-=tot;
        if(x<0||tmp>p)  return false;
    }
    return true;
}
int main(){
    n=read(),s=read(),t=read();
    if(s==t)    return printf("0\n")&0;
    for(int i=1,u,v;i<n;++i)
    {
        u=read(),v=read();
        addedge(u,v),addedge(v,u);
        d[u]++,d[v]++;
    }
    dfs(s,0);
    for(int u=t;u!=s;u=f[u])   sta[++top]=u;
    for(int i=top;i;--i)    sum[i]=sum[i+1]+d[sta[i]]-2;
    // for(int i=1;i<=top;++i)   cout<<sum[i]<<" ";
    int l=0,r=n<<1,ans=n<<1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))  r=mid-1,ans=mid;
        else    l=mid+1;
    }
    printf("%d\n",ans);
    return 0;
}
/*
30 1 28
2 1
3 1
4 2
5 4
6 2
7 3
8 4
9 6
10 4
11 2
12 5
13 12
14 3
15 3
16 7
17 5
18 6
19 17
20 1
21 18
22 2
23 9
24 7
25 13
26 10
27 6
28 21
29 4
30 24


*/
```


代码不长，但是细节有点多。请认真注意细节！

---

## 作者：Martian148 (赞：0)

# Link
[P4654 [CEOI2017]Mousetrap](https://www.luogu.com.cn/problem/P4654)

# Solve

这道题是一个树上博弈问题，如果同时从管理者和老鼠两个角度考虑会比较复杂，所以先从老鼠的角度来看

方便起见，把陷阱的节点看做根节点，老鼠就可以看错被往上赶。

对于每个节点构成的子树，我们定义$F[i]$表示老鼠进到这个子树，又被赶回来的最少步数(从管理者的角度来说)

接下来就是一个树形$DP$了，对于老鼠，进到一个树里面，假设我已经知道每个子节点的$F[i]$，老鼠肯定往$F[i]$大的子节点跑(让管理员封更多次呗)，由于是管理员先手，他能预判到老鼠会往$F[i]$最大的子节点里面跑，所以就提前把$F[i]$最大的子节点堵死，但是老鼠预判了管理员的预判，钻进$F[i]$的次大值的节点，由于老鼠进入一个节点就被卡死了，只能等管理员来疏通，所以对于管理员，当老鼠进入次大子节点后，把$i$这个节点的其他边全部封死，防止老鼠又钻到别的子树里面(到父亲的节点不用封死，以为已经脏了)（对于次大值，要加1的代价把路疏通，好让老鼠从次大值的节点回来）

对于没有看懂的可以看一下图

[![DoTwWQ.png](https://s3.ax1x.com/2020/12/03/DoTwWQ.png)](https://imgchr.com/i/DoTwWQ)

所以就推出了转移方程，$Max_2$表示子节点$F[]$的次大值，$du[i]$表示节点的度数

$$F[i]=Max_2+du[i]-1$$

对于老鼠来说，肯定在往向根节点的路上钻进某个子树里面，让管理员的代价最大，注意，最多只能钻进一个子树，以为对于管理员来说，可以等老鼠被卡死的时候把改堵的全堵了，然后再疏通，让老鼠只能往根节点走。

如果老鼠能知道最后的答案就能知道到底要不要钻了，管理员也能预判到要不要堵了。

考虑答案有单调性，就用二分来处理。

二分最终的答案$k$，构造出一条从$m$到$t$的路径，枚举路径上碰到的每个子节点如果老鼠钻进去能让管理员在$k$的时间内完不成，肯定要钻，管理员为了不让老鼠钻进这些子节点，要提前把这些子节点堵上。

我是这么判断的，(此时在从$m$到$t$的链上处理)$sum[i]$表示，老鼠钻进去后腰把后面七七八八的别的边都堵了

$$if(sum[i]+F[son[j]]+1-(i!=1)>k)nowcnt++$$


这里$(i!=1)$是因为当$g[i]==m$时计算$sum[i]$，被多减了$1$，现在要加回去

然后把$k-=nowcnt$,把多出来要堵的步骤减去

如果在统计过程中，$k<0$了，能用的步骤已经用完了，还没堵死，只能$return 0$

还有一种情况，就是$i<allcnt$($allcnt$是把之前的$nowcnt$加起来，表示一共要堵的步骤)由于管理员堵一次，老鼠就走一下，如果管理员不能把该堵的都堵了，也就是不能控制老鼠到规定的节点，老鼠就会乱跑，管理员就控制不住了，也肯定不是最优解，所以$return 0$

除了这两种情况$return 1$就行了

这道题细节较多
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005,maxe=2000005;
int F[maxn],sum[maxn],fa[maxn],T,M,N,du[maxn],g[maxn],tot,ans;
int cnt,lnk[maxn],son[maxe],nxt[maxe];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch<='9'&&ch>='0')ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
inline void add_e(int x,int y){son[++cnt]=y;nxt[cnt]=lnk[x];lnk[x]=cnt;}
void DFS(int x,int f){
	int Max_1=0,Max_2=0;
	for(int j=lnk[x];j;j=nxt[j]){
		if(son[j]==f)continue;
		fa[son[j]]=x;DFS(son[j],x);
		if(F[son[j]]>=Max_1){Max_2=Max_1;Max_1=F[son[j]];}
		else if(F[son[j]]>Max_2)Max_2=F[son[j]];
	}
	F[x]=Max_2+du[x]-1;
	return ;
}
inline bool check(int k){
	int all_cnt=0;
	for(int i=1;i<=tot;i++){
		int now_cnt=0;
		for(int j=lnk[g[i]];j;j=nxt[j]){
			if(son[j]==g[i+1]||son[j]==g[i-1])continue;
			if(sum[i]+F[son[j]]+1-(i!=1)>k)now_cnt++;
		}
		all_cnt+=now_cnt;k-=now_cnt;
		if(k<0||all_cnt>i)return 0;
	}
	return 1;
}
int main(){
	freopen("mouse.in","r",stdin);
	freopen("mouse.out","w",stdout);
	N=read();T=read(),M=read();
	for(int i=1;i<N;i++){
		int x=read(),y=read();
		add_e(x,y);add_e(y,x);
		du[x]++;du[y]++;
	}
	DFS(T,0);
	for(int i=M;i;i=fa[i])g[++tot]=i;
	for(int i=tot-1;i;i--)sum[i]=sum[i+1]+du[g[i]]-2;
	int L=0,R=1e9;
	while(L<=R){
		int mid=(R-L>>1)+L;
		if(check(mid))R=mid-1,ans=mid;
		else L=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

