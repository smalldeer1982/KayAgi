# [BalticOI 2021] The Xana coup (Day2)

## 题目描述

给定一棵点数为 $N$ 个树，第 $i$ 个点有点权 $a_i$，$a_i \in \{0,1\}$。

你可以进行切换操作：

- 对点 $i$ 进行切换操作会使得点 $i$ 及与其 **直接相连** 的点的点权取反。

其中直接相连指两点之间恰好只有一条边。

求至少需要多少次切换操作才能使得所有点的点权变为 $0$。

## 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/qyej3711.png)

$a_i=0$ 为黑色，$a_i=1$ 为白色。

可以对点 $4,5,3,1$ 进行切换操作使得所有点的点权为 $0$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$N \le 20$。
- Subtask 2（15 pts）：$N \le 40$。
- Subtask 3（10 pts）：如果点 $u$ 和点 $v$ 满足 $|u-v|=1$，那么他们有边相连。
- Subtask 4（40 pts）：一个点最多与 $3$ 个点相连。
- Subtask 5（30 pts）：无特殊限制。

对于 $100\%$ 的数据，$3 \le N \le 10^5$。

#### 说明

翻译自 [BalticOI 2021 Day2 C The Xana coup](https://boi.cses.fi/files/boi2021_day2.pdf)。

## 样例 #1

### 输入

```
5
1 2
1 3
2 4
2 5
0 1 0 1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
0 1 1 1 1```

### 输出

```
impossible```

# 题解

## 作者：quanjun (赞：16)

题目链接：[https://www.luogu.com.cn/problem/P8127](https://www.luogu.com.cn/problem/P8127)

题目大意：给定一棵包含 $n$ 个节点的树，树上每个点都有一个权值，节点 $i$ 的权值为 $a_i(a_i \in \{0,1\})$。每次可以选择树上一个点，将这个点以及与其相邻的所有点的权值取反（$0$ 变成 $1$，$1$ 变成 $0$）。问：最少需要几次操作能够让树上所有点的权值都变为 $0$？  

我的思路：

首先是树形DP，每个节点 $u$ 对应 $4$ 个状态：
- $f_{u,0}$ 表示节点权值为 $0$，没有对节点进行操作时对应的最小操作次数；
- $f_{u,1}$ 表示节点权值为 $1$，没有对节点进行操作时对应的最小操作次数；
- $f_{u,2}$ 表示节点权值为 $0$，有对节点进行操作时对应的最小操作次数；
- $f_{u,3}$ 表示节点权值为 $1$，有对节点进行操作时对应的最小操作次数。

上述所有状态（即 $f_{u,0},f_{u,1},f_{u,2},f_{u,3}$）因为对于节点 $u$ 的非子孙节点来说，它们是没有办法修改节点 $u$ 的子孙节点的状态的，所以所有的 $f_{u,i}(0 \le i \le 3)$ 对应的状态还包含的一个信息是 —— 节点 $u$ 的所有子孙节点当前的权值都为 $0$。

同时，这些操作都不考虑父节点的影响（因为我这里的状态都是根据子节点的状态推导当前节点的状态）。

除此之外，我用 $f_{u,i} = +\infty$ 来表示状态 $f_{u,i}$ 不合法。   

然后就可以推导所有的状态了。  

### 叶子节点

对于叶子节点 $u$ 来说：
- 如果 $a_u = 1$（也就是原始节点的权值为 $1$），则：
    - $f_{u,0} = +\infty$（因为叶子节点不操作的话无法让节点权值变成 $0$）
    - $f_{u,1} = 0$（因为本身节点权值就为 $1$）
    - $f_{u,2} = 1$（因为操作一次恰好让节点权值变成 $0$）
    - $f_{u,3} = +\infty$（因为操作一次之后节点权值变成了 $0$，而不是 $1$）
- 如果 $a_u = 0$（也就是原始节点的权值为 $0$），则：
    - $f_{u,0} = 0$（因为本身节点权值就为 $0$）
    - $f_{u,1} = +\infty$（因为叶子节点不操作的话无法让节点权值变成 $1$）
    - $f_{u,2} = +\infty$（因为操作一次之后节点权值变成了 $1$，而不是 $0$）
    - $f_{u,3} = 1$（因为操作一次恰好让节点权值变成 $1$）

### 非叶子节点

对于当前节点 $u$ 来说，只有可能操作或者不操作。

- 如果选择不操作，则它的子节点的状态必须都是 $0$（设子节点为 $v$，则此时只跟 $f_{v,0}$、$f_{v,2}$ 有关）
- 如果选择操作，则它的子节点的状态必须都是 $1$（设子节点为 $v$，则此时只跟 $f_{v,1}$、$f_{v,3}$ 有关）

但是这里有一个需要思考的问题，就是：当前节点 $u$ 的状态受子节点中节点的状态的影响！

影响主要在于 —— 子节点中操作过的点是奇数个还是偶数个。

所以可以额外定义四个状态：$g_{i,0}, g_{i,1}, h_{i,0}, h_{i,1}$，这四个状态是对于当前节点 $u$ 来说的。对于当前节点 $u$，设其有 $m$ 个子节点，则：  

- $g_{i,0}$ 表示节点 $u$ 的前 $i$ 个子节点全都是 $0$ 且有偶数个操作过时对应的最少操作次数（偶数个操作过相当于对节点 $u$ 的状态没影响，奇数个操作过就会对节点 $u$ 的状态造成影响）；
- $g_{i,1}$ 表示节点 $u$ 的前 $i$ 个子节点全都是 $0$ 且有奇数个操作过时对应的最少操作次数；
- $h_{i,0}$ 表示节点 $u$ 的前 $i$ 个子节点全都是 $1$ 且有偶数个操作过时对应的最少操作次数；
- $h_{i,1}$ 表示节点 $u$ 的前 $i$ 个子节点全都是 $1$ 且有奇数个操作过时对应的最少操作次数

首先：

- $g_{0,0} = h_{0,0} = 0$
- $g_{0,1} = h_{0,1} = +\infty$

其次，当 $i \gt 0$ 时，（设节点 $u$ 的第 $i$ 个子节点为 $v$，则）有：

- $g_{i,0} = \min \{ g_{i-1,0} + f_{v,0}, g_{i-1,1} + f_{v,2} \}$
- $g_{i,1} = \min \{ g_{i-1,0} + f_{v,2}, g_{i-1,1} + f_{v,0} \}$
- $h_{i,0} = \min \{ h_{i-1,0} + f_{v,1}, h_{i-1,1} + f_{v,3} \}$
- $h_{i,1} = \min \{ h_{i-1,0} + f_{v,3}, h_{i-1,1} + f_{v,1} \}$

当然我们需要的只有最终计算出来的 $g_{m,0}, g_{m,1}, h_{m,0}, h_{m,1}$ 这四个状态（其中 $m$ 是当前节点 $u$ 的子节点个数）。

此时再分别讨论 $a_u$ 是 $1$ 还是 $0$ 的情况。  

#### 当 $a_u = 1$ 时：
- $f_{u,0} = g_{m,1}$（因为本身是 $1$ 且不操作，要变成 $0$，所以需要子节点中是 $0$ 且操作过的数量是奇数个）
- $f_{u,1} = g_{m,0}$（因为本身就是 $1$ 且不操作，所以需要子节点中是 $0$ 且操作过的数量是偶数个）
- $f_{u,2} = 1 + h_{m,0}$（因为本身是 $1$，操作一次自己变成 $0$，所以需要子节点是 $1$ 且操作过的数量是偶数个）
- $f_{u,3} = 1 + h_{m,1}$（因为本身是 $1$，操作一次会变成 $0$，所以需要子节点是 $1$ 且操作过的数量是奇数个）

#### 当 $a_u = 0$ 时：
- $f_{u,0} = g_{m,0}$（因为本身是 $0$ 且不操作，所以需要子节点中是 $0$ 且操作过的数量是偶数个）
- $f_{u,1} = g_{m,1}$（因为本身是 $0$ 且不操作，要变成 $1$，所以需要子节点中是 $0$ 且操作过的数量是奇数个）
- $f_{u,2} = 1 + h_{m,1}$（因为本身是 $0$，操作一次会变成 $1$，所以需要子节点是 $1$ 且操作过的数量是奇数个）
- $f_{u,3} = 1 + h_{m,0}$（因为本身是 $0$，操作一次自己变成 $1$，所以需要子节点是 $1$ 且操作过的数量是偶数个）


示例程序：  

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int INF = (1<<29);
int n, a[maxn], f[maxn][4], g[maxn][2], h[maxn][2];
vector<int> e[maxn];

/**
f[u][0] 点权为 0，点未操作
f[u][1] 点权为 1，点未操作
f[u][2] 点权为 0，点有操作
f[u][3] 点权为 1，点有操作
*/

void dfs(int u, int p) {
    int sz = e[u].size();
    if (sz == 1 && u != 1) {    // 叶子节点
        if (a[u] == 1) {
            f[u][0] = INF;
            f[u][1] = 0;
            f[u][2] = 1;
            f[u][3] = INF;
        }
        else {  // a[u] == 0
            f[u][0] = 0;
            f[u][1] = INF;
            f[u][2] = INF;
            f[u][3] = 1;
        }
        return;
    }
    vector<int> tmp;
    for (auto v : e[u])
        if (v != p)
            dfs(v, u), tmp.push_back(v);
    int m = tmp.size();
    g[0][0] = h[0][0] = 0;
    g[0][1] = h[0][1] = INF;
    for (int i = 1; i <= m; i++) {
        int v = tmp[i-1];
        g[i][0] = min(INF, min(g[i-1][0] + f[v][0], g[i-1][1] + f[v][2]));
        g[i][1] = min(INF, min(g[i-1][0] + f[v][2], g[i-1][1] + f[v][0]));
        h[i][0] = min(INF, min(h[i-1][0] + f[v][1], h[i-1][1] + f[v][3]));
        h[i][1] = min(INF, min(h[i-1][0] + f[v][3], h[i-1][1] + f[v][1]));
    }
    if (a[u] == 1) {
        f[u][0] = g[m][1];
        f[u][1] = g[m][0];
        f[u][2] = min(INF, 1 + h[m][0]);
        f[u][3] = min(INF, 1 + h[m][1]);
    }
    else {
        f[u][0] = g[m][0];
        f[u][1] = g[m][1];
        f[u][2] = min(INF, 1 + h[m][1]);
        f[u][3] = min(INF, 1 + h[m][0]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) scanf("%d", a+i);
    dfs(1, -1);
    int ans = min(f[1][0], f[1][2]);
    if (ans == INF) puts("impossible");
    else printf("%d\n", ans);
    return 0;
}
```



---

## 作者：2018ty43 (赞：11)

考虑操作无顺序要求与子树只有儿子有影响，考虑树形 DP。  
设 $f_{i,0/1,0/1}$ 表示第 $i$ 个点，对父节点有无更改，对自己更改的 $0$ 偶 $1$ 奇次时的最小更改次数。  
若当前结点为 $u$，则从节点 $son$ 转移有转移方程：  
$$
f_{u,0,0}\gets\min (f_{u,0,0}+f_{son,0,a_{son}},f_{u,0,1}+f_{son,1,a_{son}}) $$
$$
f_{u,0,1}\gets\min(f_{u,0,1}+f_{son,0,a_{son}},f_{u,0,0}+f_{son,1,a_{son}})$$
$$
f_{u,1,0}\gets \min(f_{u,1,0}+f_{son,0,\neg a_{son}},f_{u,1,1}+f_{son,1,\neg a_{son}})$$
$$
f_{u,1,1}\gets \min(f_{u,1,1}+f_{son,0,\neg a_{son}},f_{u,1,0}+f_{son,1,\neg a_{son}})
$$
即儿子对当前节点有无更改的两种情况取 min。  
初始 $f_{u,0,0}=0,f_{u,1,1}=1,f_{u,0,1}=f_{u,1,0}=-inf$。  
最后 $\min(f_{root,0,a_{root}},f_{root,1,a_{root}})$ 即为答案。

---

## 作者：strlen_s_ (赞：4)

## 分析

很明显，操作顺序对答案无影响。

那这一题就是一个很明显的树形dp。

设 $dp_{i,0/1,0/1}$，表示以 $i$ 为根的子树中,$i$ 在操作完后值是零还是一和是否在 $i$ 上进行了操作。

考虑子树如何转移到根。

倘若 $i$ 不进行操作，且子树的根保持原来的状态，那么就要满足它的子树的根都必须是零，而且有偶数个进行了操作。

倘若 $i$ 不进行操作，且子树的根不保持原来的状态，那么就要满足它的子树的根都必须是零，而且有奇数个进行了操作。

倘若 $i$ 进行操作，且子树的根不保持原来的状态，那么就要满足它的子树的根都必须是一，而且有偶数个进行了操作。

倘若 $i$ 进行操作，且子树的根保持原来的状态，那么就要满足它的子树的根都必须是一，而且有奇数个进行了操作。

那么就只要解决维护 $i$ 的子树的贡献和。

这里可以再设一个 $f_{i,0/1,0/1}$，表示处理完第 $i$ 个子树，当前操作数量为偶数还是奇数，根要不要进行操作。

那么就有：

$f_{i,0,0}=\min(f_{i-1,1,0}+dp_{v,0,1},f_{i-1,0,0}+dp_{v,0,0})$

$f_{i,1,0}=\min(f_{i-1,1,0}+dp_{v,0,0},f_{i-1,0,0}+dp_{v,0,1})$

$f_{i,0,1}=\min(f_{i-1,1,1}+dp_{v,1,1},f_{i-1,0,1}+dp_{v,1,0})$

$f_{i,1,1}=\min(f_{i-1,1,1}+dp_{v,1,0},f_{i-1,1,0}+dp_{v,1,1})$

最后再把 $f$ 的贡献加到 $dp$ 里去了。

### code

 ```
 #include<bits/stdc++.h>
#define in inline
#define re register
//#define int long long
using namespace std;
in int read(){
	int x=0,f=1;
	char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=1e5+10;
int h[N],nex[N<<1],to[N<<1],tot,inf;
int dp[N][2][2];
bool a[N];
int n;
int out[N];
int ans;
void add(int x,int y){to[++tot]=y,nex[tot]=h[x],h[x]=tot;}
in int gmin(int x){
	return min(inf,x);
}
in void dfs(int u,int fa){
	if(out[u]==1&&fa!=0){
		dp[u][a[u]][0]=0;
		dp[u][a[u]^1][1]=1;
		return;
	}
	re int f00,f10,h01,h11;
	re bool fl=0;
	for(re int i=h[u];i;i=nex[i]){
		re int v=to[i];
		if(v==fa)continue;
		dfs(v,u);
		if(!fl){
			fl=1;
			f00=dp[v][0][0],f10=dp[v][0][1],h01=dp[v][1][0],h11=dp[v][1][1];		//把 f 初始化。 
			continue;
		}
		re int bf00=f00,bf10=f10,bh01=h01,bh11=h11;
		f00=min(gmin(bf10+dp[v][0][1]),gmin(bf00+dp[v][0][0]));			//转移。 
		f10=min(gmin(bf10+dp[v][0][0]),gmin(bf00+dp[v][0][1]));
		h01=min(gmin(bh11+dp[v][1][1]),gmin(bh01+dp[v][1][0]));
		h11=min(gmin(bh11+dp[v][1][0]),gmin(bh01+dp[v][1][1]));
	}
	dp[u][a[u]][0]=gmin(f00),dp[u][a[u]^1][0]=gmin(f10),dp[u][a[u]^1][1]=gmin(h01+1),dp[u][a[u]][1]=gmin(h11+1);
}
signed main(){
	n=read();
	for(re int i=1;i<n;i++){
		re int x=read(),y=read();
		add(x,y),add(y,x);
		out[x]++,out[y]++;
	}
	for(re int i=1;i<=n;i++)a[i]=read();
	memset(dp,0x3f,sizeof(dp));				//初始设为无穷。 
	inf=dp[0][0][0];
	dfs(1,0);
	ans=min(dp[1][0][0],dp[1][0][1]);
	if(ans!=inf)
	cout<<ans;
	else puts("impossible");
	return 0;
}

 ```

---

## 作者：船酱魔王 (赞：3)

# P8127 [BalticOI 2021 Day2] The Xana coup 题解

## 题意回顾

$ n $ 个点的树，初始时每个点都有颜色（黑或白），你可以对一个点进行一次操作使得这个点及相邻点颜色变化。求出让所有点变成白色的最小操作次数或报告无解。

$ 3 \le n \le 10^5 $。

## 分析

这个问题 [推广到一般无向图上](https://www.luogu.com.cn/problem/P2962) 是没有多项式时间内的求解算法的，所以我们要利用树的性质，即一个点可能影响的点只有父结点、本身、子结点，考虑设计树形 DP。

定义 $ dp_{u,x,y} $ 表示结点 $ u $ 的本身和子树需要操作的结点均已经操作完成，结点 $ u $ 的颜色为 $ x $，子树内其它点颜色为白色，这个点本身的操作情况为 $ y $，此时的操作数最小值。

我们讨论这个结点本身要不要操作，这里以这个结点不操作为例。

具体地，记 $ rol_{r,x} $ 为 $ u $ 的本身及前 $ r $ 个儿子结点对其颜色影响结果为 $ x $，设第 $ r $ 个儿子为 $ v $：（实现时可以滚动第一维）

* $ rol_{r,x}\leftarrow rol_{r-1,x}+dp_{v,0,0} $，即儿子结点已经是白色，父节点 $ u $ 本身不能变色，儿子结点没有操作因此对父亲结点没有影响。

* $ rol_{r,x}\leftarrow rol_{r-1,x\oplus 1}+dp_{v,0,1} $，即儿子结点已经是白色，父节点 $ u $ 本身不能变色，儿子结点进行了一次变色因此对父节点产生了影响。

* 两种情况取最小值，实现时注意特判无解避免溢出。

初始状态即为本身颜色代价为 $ 0 $，本身颜色的另一种颜色无解，实现时赋值为 $ \inf $。

这个结点需要操作时注意儿子结点颜色必须为黑色，且讨论儿子结点前的初始化时本身颜色为无解，另一种颜色为 $ 1 $（因为本身需要操作）。

把两种情况的 $ rol $ 数组的值赋值到 $ dp $ 数组上去即可。

本题树形 DP 的本质就是状态设计考虑一个结点与父结点的相互影响关系，转移时从子结点转移。这利用了树的连边较为单一的性质，事实上很多在一般图上不存在多项式时间解法的问题在树上均可以一个时间复杂度很优秀的算法解决。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
const int inf = 1e9 + 5;
int n;
int a[N];
vector<int> g[N];
int dp[N][2][2];
int rol[2][2];//self ? up ?
void solve(int u, int fath) {
    if(g[u].size() == 0 || (u > 1 && g[u].size() == 1)) {
        dp[u][0][0] = dp[u][0][1] = dp[u][1][0] = dp[u][1][1] = inf;
        dp[u][a[u]][0] = 0, dp[u][a[u] ^ 1][1] = 1;
        return;
    }
    for(int i = 0; i < g[u].size(); i++) {
    	int v = g[u][i];
    	if(v == fath) continue;
    	solve(v, u);
	}
    int fg = 0;
    rol[0][a[u]] = 0, rol[0][a[u] ^ 1] = inf;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(v == fath) continue;
        fg ^= 1;
        rol[fg][0] = min(min(rol[fg ^ 1][1] + dp[v][0][1], rol[fg ^ 1][0] + dp[v][0][0]), inf);
        rol[fg][1] = min(min(rol[fg ^ 1][1] + dp[v][0][0], rol[fg ^ 1][0] + dp[v][0][1]), inf);
    }
    dp[u][0][0] = rol[fg][0], dp[u][1][0] = rol[fg][1];
    rol[0][a[u]] = inf, rol[0][a[u] ^ 1] = 1;
    fg = 0;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(v == fath) continue;
        fg ^= 1;
        rol[fg][0] = min(min(rol[fg ^ 1][1] + dp[v][1][1], rol[fg ^ 1][0] + dp[v][1][0]), inf);
        rol[fg][1] = min(min(rol[fg ^ 1][1] + dp[v][1][0], rol[fg ^ 1][0] + dp[v][1][1]), inf);
    }
    dp[u][0][1] = rol[fg][0], dp[u][1][1] = rol[fg][1];
}
int main() {
    scanf("%d", &n);
    int u, v;
    for(int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    solve(1, 0);
    int t = min(dp[1][0][1], dp[1][0][0]);
    if(t >= inf) {
        cout << "impossible" << endl;
        return 0;
    }
    cout << t << endl;
    return 0;
}
```

---

## 作者：Vidoliga (赞：3)

提供不同的状态设计：

设 $f_{u,0/1,0/1}$ 表示 $u$ 节点是否进行操作，及当前为 $0/1$ 状态。

可以手玩出转移方程：

1. $f_{u,0,0} =\sum_{v \in E_{u}} min(f_{v,0,0},f_{v,1,0})$

2. $f_{u,0,1} =\sum_{v \in E_{u}} min(f_{v,0,0},f_{v,1,0})$

3. $f_{u,1,0} =\sum_{v \in E_{u}} min(f_{v,0,1},f_{v,1,1})$

4. $f_{u,1,1} =\sum_{v \in E_{u}} min(f_{v,0,1},f_{v,1,1})$

且有当：

$if(cnt \mod 2=0 \&\& a[u]=1|| cnt \mod 2=1 \&\& a[u]=0) f_{u,1,0}+=\min_{v \in E_{u}} |f_{v,0,0}-f_{v,1,0}|$

$if(cnt \mod 2=1 \&\& a[u]=1|| cnt \mod 2=0 \&\& a[u]=0) f_{u,1,0}+=\min_{v \in E_{u}} |f_{v,0,0}-f_{v,1,0}|$

$if(cnt \mod 2=1 \&\& a[u]=1|| cnt \mod 2=0 \&\& a[u]=0) f_{u,1,0}+=\min_{v \in E_{u}} |f_{v,0,1}-f_{v,1,1}|$

$if(cnt \mod 2=0 \&\& a[u]=1|| cnt \mod 2=1 \&\& a[u]=0) f_{u,1,0}+=\min_{v \in E_{u}} |f_{v,0,1}-f_{v,1,1}|$

最后答案为： $min(f_{rt,0,0},f_{rt,1,0})$

Code:

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#define N 100010
#define int long long
#define Inf 0x3f3f3f3f
using namespace std;
//typedef long long ll;
inline int read(){
	register int d=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){d = (d<<1)+(d<<3)+(ch^48);ch=getchar();}
	return d*f;
}
struct Edge{
	int v,w,nxt;
}edge[N<<1];
int head[N],ecnt;
inline void add(int u,int v){
	edge[++ecnt].v=v;
	edge[ecnt].nxt=head[u];
	head[u]=ecnt;
}
int a[N],n,Flag;
int f[N][2][2];
void dfs(int u,int fa){
//	if(!edge[head[u]].nxt&&u!=1){
		f[u][0][0]=(a[u]==0)?0:Inf;
		f[u][0][1]=(a[u]==1)?0:Inf;
		f[u][1][1]=(a[u]==0)?1:Inf;
		f[u][1][0]=(a[u]==1)?1:Inf;
//		printf("%d %d %d %d\n",f[u][0][0],f[u][0][1],f[u][1][0],f[u][1][1]);
//		return ;
//	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==fa) continue;
		dfs(v,u);
	}
	int cnt=0,tmp1=0,tmp2=0,tmp3=0,tmp4=0;
	bool flag=false,Flag=false;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==fa) continue;
		if(f[v][0][0]<f[v][1][0]){}
		else if(f[v][0][0]>f[v][1][0]) cnt++;
		else flag=true;
		if(min(f[v][0][0],f[v][1][0])>=Inf) Flag=true;
		tmp1+=min(f[v][0][0],f[v][1][0]);
		tmp2+=min(f[v][0][0],f[v][1][0]);
	}
	if(!flag){
		int minx=Inf;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			if(v==fa) continue;
			minx=min(minx,abs(f[v][0][0]-f[v][1][0]));
		}
		if((cnt%2==0&&a[u]==1)||(cnt%2==1&&a[u]==0)){
			tmp1+=minx;
		}
		if((cnt%2==1&&a[u]==1)||(cnt%2==0&&a[u]==0)){
			tmp2+=minx;
		}
	}
	if(Flag){
		f[u][0][0]=f[u][0][1]=Inf;
	}
	f[u][0][0]=tmp1;
	f[u][0][1]=tmp2;
	cnt=0;
	flag=false;Flag=false;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==fa) continue;
		if(f[v][0][1]<f[v][1][1]){}
		else if(f[v][0][1]>f[v][1][1]) cnt++;
		else flag=true;
		if(min(f[v][0][1],f[v][1][1])>=Inf) Flag=true;
		tmp3+=min(f[v][0][1],f[v][1][1]);
		tmp4+=min(f[v][0][1],f[v][1][1]);
	}
	if(!flag){
		int minx=Inf;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].v;
			if(v==fa) continue;
			minx=min(minx,abs(f[v][0][1]-f[v][1][1]));
		}
		if((cnt%2==1&&a[u]==1)||(cnt%2==0&&a[u]==0)){
			tmp3+=minx;
		}
		if((cnt%2==0&&a[u]==1)||(cnt%2==1&&a[u]==0)){
			tmp4+=minx;
		}
	}
	if(Flag){
		f[u][1][0]=f[u][1][1]=Inf;
	}
	f[u][1][0]=tmp3+1;
	f[u][1][1]=tmp4+1;
}
signed main(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	for(int i=1;i<=n;i++) a[i]=read();
	dfs(1,0);
//	for(int i=1;i<=n;i++){
//		printf("%d %d %d %d\n",f[i][0][0],f[i][0][1],f[i][1][0],f[i][1][1]);
//	}
	if(min(f[1][0][0],f[1][1][0])>=Inf) printf("impossible");
	else {
		printf("%d",min(f[1][0][0],f[1][1][0]));
	}
	return 0;
}
```


---

## 作者：Kao_Potato (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P8127)

~~做完看题解才发现题解的状态设计和转移都好**冗余**。~~

题目很简洁明了，很典型的树形DP的题面，考虑状态设计。

首先将无根树提一个根出来以后，若对一个节点进行操作，只会对其本身、父节点和儿子节点造成影响。而我们不希望进行操作时对父节点产生影响，否则不利于DP，所以考虑强制只对当前节点的儿子节点进行操作。

若状态已知则操作产生的影响很容易计算，因此考虑将节点权值放进状态定义中，而我们需知当前节点和儿子节点的权值（儿子的儿子的权值可以根据儿子的状态确定），因此可以得到状态定义。

每个结点对应 $4$ 个状态：
- $f_{i,0}$ 表示当前节点 $i$ 权值为 $0$，儿子节点权值为 $0$
- $f_{i,1}$ 表示当前节点 $i$ 权值为 $0$，儿子节点权值为 $1$
- $f_{i,2}$ 表示当前节点 $i$ 权值为 $1$，儿子节点权值为 $0$
- $f_{i,3}$ 表示当前节点 $i$ 权值为 $1$，儿子节点权值为 $1$

这里强制定义全部儿子节点的权值相同，且以 $i$ 为根的子树中除去 $i$ 和儿子节点外其余全部节点均为 $0$。

接下来考虑转移，转移可以考虑每加进一棵子树对当前节点答案的影响，每个状态都有两种转移方式，一种是从相应的状态直接转移过来，一种是对新加的儿子做一次操作转移过来，则可以写出代码。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int N=100005,MX=1e9;
int pn,cnt,first[N],v[N],dp[N][4];
struct Bian{
	int to,next;
}b[N*2];
void add(int from,int to){
	cnt++;
	b[cnt]=(Bian){to,first[from]};
	first[from]=cnt;
}
void dfs(int now,int f){
	if(v[now]==0){
		dp[now][2]=dp[now][3]=MX;
	}else{
		dp[now][0]=dp[now][1]=MX;
	}
	//初始状态即为单个节点时的状态，此时不用考虑儿子节点，不可能的状态就直接赋为无穷大。 
	for(int i=first[now];i!=0;i=b[i].next){
		if(b[i].to!=f){
			dfs(b[i].to,now);
			int ls0=dp[now][0],ls1=dp[now][1],ls2=dp[now][2],ls3=dp[now][3];
			//一定要将当前的状态记录下来，否则后面的转移会互相影响。 
			dp[now][0]=min(min(ls0+dp[b[i].to][0],ls2+dp[b[i].to][3]+1),MX);
			dp[now][1]=min(min(ls1+dp[b[i].to][2],ls3+dp[b[i].to][1]+1),MX);
			dp[now][2]=min(min(ls2+dp[b[i].to][0],ls0+dp[b[i].to][3]+1),MX);
			dp[now][3]=min(min(ls3+dp[b[i].to][2],ls1+dp[b[i].to][1]+1),MX);
		}
	}
}
int main(){
	scanf("%d",&pn);
	for(int i=1;i<pn;i++){
		int from,to;
		scanf("%d%d",&from,&to);
		add(from,to);
		add(to,from);
	}
	for(int i=1;i<=pn;i++){
		scanf("%d",&v[i]);
	}
	dfs(1,0);
	if(min(dp[1][0],dp[1][3]+1)>=MX){
		printf("impossible");
	}else{
		printf("%d",min(dp[1][0],dp[1][3]+1));
	}
	return 0;
}
```

---

## 作者：zsyzsy_2012 (赞：1)

很具有启发性的树状 DP 思维题。

看到了这个题的题面，应该不难想到树上 DP。我们用 $dp_{u,0 \to 3}$ 表示当前节点， $2$ 种初始状态和是与否操作两种情况，这个值表示的是当前情况的答案。但是，我们不能强制地在 $dp_u$ 的讨论范围内决定 $u$ 点权，所以在转移时引入 $f0,f1,f2,f3$ 记录：父亲不改变，儿子们是 $0$；父亲改变，儿子们是 $0$；父亲不改变，儿子们是 $1$；父亲改变，儿子们是 $1$。进一步分析可得决定父亲点权的只有儿子们操作次数的奇偶性，这样代码就好写多了。

下面是我的代码，状态不理解的可以对照代码看：

```
#include <bits/stdc++.h>
using namespace std;
const int N=100010,inf=(int)5e8;
vector<int>v[N];
int n,x,y,a[N],dp[N][4];
void dfs(int u,int fa){
	if((int)v[u].size()==1&&u>1){
		if(!a[u])dp[u][0]=0,dp[u][1]=inf,dp[u][2]=1,dp[u][3]=inf;
		else dp[u][0]=inf,dp[u][1]=0,dp[u][2]=inf,dp[u][3]=1;
		return;
	}
	int f0=0,f1=inf,f2=0,f3=inf,nf0,nf1,nf2,nf3;
	for(int i=0;i<(int)v[u].size();i++){
		int t=v[u][i];
		if(t==fa)continue;
		dfs(t,u);
		nf0=min(f0+dp[t][0],f1+dp[t][3]);
		nf1=min(f1+dp[t][0],f0+dp[t][3]);
		nf2=min(f2+dp[t][1],f3+dp[t][2]);
		nf3=min(f3+dp[t][1],f2+dp[t][2]);
		f0=nf0,f1=nf1,f2=nf2,f3=nf3;
		if(f0>inf)f0=inf;
		if(f1>inf)f1=inf;
		if(f2>inf)f2=inf;
		if(f3>inf)f3=inf;
	}
	if(!a[u])dp[u][0]=f0,dp[u][1]=f1,dp[u][2]=1+f2,dp[u][3]=1+f3;
	else dp[u][0]=f1,dp[u][1]=f0,dp[u][2]=1+f3,dp[u][3]=1+f2;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	dfs(1,0);
	int ans=min(dp[1][0],dp[1][3]);
	if(ans<inf)printf("%d",ans);
	else printf("impossible");
	return 0;
}
```


---

