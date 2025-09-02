# 『MdOI R3』Fallen Lord

## 题目背景

统治着世界，统治着寂寞。

## 题目描述

L 国有 $n$ 个城市，它们之间有 $n-1$ 条道路，形成了一棵树的结构。

国王 L 派遣了一些军队来驻守这些道路，驻守每一条道路的军队战斗力都可以被量化为 $[1,m]$ 中的整数。

每个城市都有一个城主，第 $i$ 个城主有一个忍耐度 $a_i$。如果国王 L 在与第 $i$ 个城市相连的所有道路上驻守的军队战斗力的**中位数**超过了**城主**的忍耐度，那么**城主**就会认为国王不信任他而产生谋反的心理。

国王 L 当然不希望有人造反，但他又想使驻守道路的军队的总战斗力**最大**来保证国防安全。现在他找到了 L 国最强的 OIer —— 您，去来帮助他解决这个问题。

如果无论如何安排军队都会有人想要造反，那么输出 `-1`。

**注：对于任意 $k$ 个数，它们的中位数是将这些数从小到大排序后第 $\left\lfloor\dfrac{k}{2}\right\rfloor+1$ 个数。**

## 说明/提示

更多样例请[到这里](https://www.luogu.com.cn/paste/0wcdzik5)领取。

对于所有数据，$1\le u_i,v_i \le n\le 5\times 10^5$，$n\ge 2$，$1\le a_i\le m\le 10^9$。  

|子任务编号|$n\leq$|$m\leq$|其他性质|分值|
|:-:|:-:|:-:|:-:|:-:|
|1|$8$|$8$|无|$5$|
|2||$1$|无|$1$|
|3|||树的形态为一条链|$10$|
|4|||存在度数为 $n-1$ 的节点|$12$|
|5|$10^5$||每个节点度数 $\le 6$|$17$|
|6|$5\times 10^3$||无|$20$|
|7|||无|$35$|

其中，留空的表示和 $100\%$ 的数据范围限制相同。
### 样例解释
![](https://cdn.luogu.com.cn/upload/image_hosting/ipkyy6az.png)

如图驻守 $n-1=6$ 条道路的军队战斗力（按照输入中的顺序）依次为 $50,50,12,12,12,12$。

## 样例 #1

### 输入

```
7 100
50 25 25 12 12 12 12
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
148```

# 题解

## 作者：a___ (赞：16)

update(20/8/18):感谢[@loveJY](https://www.luogu.com.cn/user/76990)dalao指出错误。
_________

算法标签：$\color{#FFFFFF}\colorbox{#E74C3C}{\small\texttt{树上dp}}\ \color{#FFFFFF}\colorbox{#E74C3C}{\small\texttt{贪心}}$  

_____

这题其实很好写，就是dp状态不太好想。   

前置芝士：一个数列的中位数小于等于 $x$ $\Leftrightarrow$ 一个数列有至少 $\left\lfloor\dfrac{len}{2}\right\rfloor+1$ 个数小于等于 $x$。    

记 $\operatorname{val}(u,v)$ 表示边 $(u,v)$ 上的边权（或者叫做军队战斗力）。   

首先，显然没有无解的情况，因为如果每条边权都置为 $1$，无论如何都不会有人造反。    

然后，由于以上性质我们发现对于一条边的边权 **我们只关心其是否大于两端点点权**，于是    
**设 $f_{u,0/1}$ 表示   
当 $\operatorname{val}(\operatorname{fa}(u),u)\leq a_u\ \ /\ \ \operatorname{val}(\operatorname{fa}(u),u)> a_u$ 时 以点 $u$ 为根的 子树内 满足条件的 边权和的 最大值**。    
**设 $g_{u,0/1}$ 表示   
当 $\operatorname{val}(\operatorname{fa}(u),u)\leq a_{\operatorname{fa}(u)}\ \ /\ \ \operatorname{val}(\operatorname{fa}(u),u)> a_{\operatorname{fa}(u)}$ 时 $\operatorname{fa}(u)$ 的子树 $u$，包括边 $(\operatorname{fa}(u),u)$， 边权和的最大值**。    

>举个例子：   
>![](https://cdn.luogu.com.cn/upload/image_hosting/owlptcux.png)   
>以点 $5$ 为例，其周围有 $3$ 条边，则应存在 $2$ 条边边权小于等于 $40$。当边 $(2,5)$ 边权小于等于 $40$ 时，向下可以有一条边权大于 $40$，所以 $f_{5,0}=30+50$。    

显然，如果我们以点 $1$ 为根dfs，最后答案为 $f_{1,0}$。   

接下来是状态转移。   
1. 已经算出 $\forall v\in \operatorname{son}(u)\ \ \ \ g_{v,0/1}$，求 $f_{u,0/1}$：   
   考虑贪心。我们先选所有 $g_{v,0}$，即使所有到儿子的边的边权都小于点 $u$ 点权。对于 $f_{u,0}$ ，此时可以有 $\operatorname{du}(u)-\left(\left\lfloor\dfrac{\operatorname{du}(u)}{2}\right\rfloor+1\right)$ 条边的边权大于点 $u$ 点权；对于 $f_{u,1}$ ，此时可以有 $\operatorname{du}(u)-\left(\left\lfloor\dfrac{\operatorname{du}(u)}{2}\right\rfloor+1\right)-1$ 条边的边权大于点 $u$ 点权。设允许的边权大于 $a_u$ 的边数为 $k$，我们从大到小枚举 $k$ 个 $g_{v,1}-g_{v,0}$，即贪心地考虑将小于 $a_u$ 的边换成大于 $a_u$ 的边即可。      
2. 已经算出 $f_{u,0/1}$，求 $g_{u,0/1}$：   
   分类讨论：   
   1. $a_u<a_{\operatorname{fa}(u)}$   
      1. $g_{u,0}$    
         1. $a_u<\operatorname{val}(\operatorname{fa}(u),u)\leq a_{\operatorname{fa}(u)}$    
         2. $\operatorname{val}(\operatorname{fa}(u),u)\leq a_u<a_{\operatorname{fa}(u)}$    
      2. $g_{u,1}$   
         1. $a_u<a_{\operatorname{fa}(u)}<\operatorname{val}(\operatorname{fa}(u),u)\leq m$   
   2. $a_u=a_{\operatorname{fa}(u)}$   
      直接并入1或3   
   3. $a_u>a_{\operatorname{fa}(u)}$    
      1. $g_{u,0}$   
         1. $\operatorname{val}(\operatorname{fa}(u),u)\leq a_{\operatorname{fa}(u)} <a_u$   
      2. $g_{u,1}$    
         1. $a_{\operatorname{fa}(u)}<\operatorname{val}(\operatorname{fa}(u),u)\leq a_u$    
         2. $a_{\operatorname{fa}(u)}<a_u<\operatorname{val}(\operatorname{fa}(u),u)\leq m$    

综上：      
$$g_{u,0}=\begin{cases}\max\{f_{u,0}+a_u,f_{u,1}+a_{\operatorname{fa}(u)}\}&a_u\leq a_{\operatorname{fa}(u)}\\f_{u,0}+a_{\operatorname{fa}(u)}&a_u>a_{\operatorname{fa}(u)}\end{cases}$$    
$$g_{u,1}=\begin{cases}f_{u,1}+m&a_u\leq a_{\operatorname{fa}(u)}\\\max\{f_{u,0}+a_u,f_{u,1}+m\}&a_u>a_{\operatorname{fa}(u)}\end{cases}$$     

然后从下向上dp即可。    

注意到当 $\operatorname{du}(u)\leq 2$ 时，无论如何不可能出现 $\operatorname{val}(\operatorname{fa}(u),u)>a_u$。此时，需特判将 $f_{u,1}$ 置为 $-\inf$。     

[AC代码](https://www.luogu.com.cn/paste/nluar5kt)

---

## 作者：OMG_wc (赞：10)

做的时候发现这题充满了奥妙重重的各种情形，越是想把情况合并就越是想的太复杂，那干脆暴力点好了：

很容易发现最终连接 $u,v$ 两个点的权值只可能是 $a_u,a_v,m$ 三者之一，那么我们的DP状态定义为：

定义`f[u][0/1/2]` 表示`u`这个子树中，`u`的父边权值为 $a_{fa}/a_u/m$ 的满足题意要求的最大值（包括父边）。

对于一个度数为 $d$ 的点，其周围要满足至少有 $t=\lfloor {d\over2}\rfloor+1$ 条边的权值小于等于 $a_u$，那么可以根据父边的权值分成两种情况：儿子中的边有 $t$ 条满足或者 $t-1$ 条满足权值小于等于 $a_u$。

很容易写出一个 $O(n^2)$ 的做法（~~除了菊花图和最后一个数据点都能过了~~）：

对当前结点 $u$ 的某个儿子 $v$，其能产生  $1$ 的贡献的最大值为 $g_1$，不一定产生 $1$ 的贡献的最大值为 $g_0$，具体计算见下面的代码，很好理解。最终目的是所有儿子产生 $t$ 或者 $t-1$ 个贡献，这个做法其实就是个背包，但其实可以优化:

显然 $g_0\ge g_1$ ，现在的目的是选 $t$ 个儿子（选 $t-1$ 个儿子的情况不赘述 ），那么我们可以先假设都不选，即加的都是 $g_0$，得到一个较大的值 $s$，最后再减去 $t$ 个差值 $g_0-g_1$。因为求的是最大值，所以希望减得数值越小越好，那么通过排序把最小的 $t$ 个找出来减去就好了。

要注意的是，如果 $t>$ 儿子个数，要特殊判断：通过儿子产生 $t$ 个贡献是不可能的，记为负无穷。

最后根节点特殊处理下，`f[1][0]`就是答案。

参考代码如下：

```cpp
void dfs(int u, int fa) {
    int t = G[u].size() / 2 + 1;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
    LL s = 0;
    int tot = 0;
    for (auto v : G[u]) {
        if (v == fa) continue;
        LL g0 = max(f[v][2], max(f[v][0], f[v][1]));             // 不一定有1贡献
        LL g1 = a[u] <= a[v] ? f[v][0] : max(f[v][0], f[v][1]);  // 一定有1贡献
        s += g0;
        b[tot++] = g0 - g1;
    }
    sort(b, b + tot);
    for (int i = 0; i < t - 1; i++) {
        s -= b[i];
    }
    LL s1 = s;
    if (t - 1 < tot) {
        s -= b[t - 1];
    } else {
        s = -1e18;
    }
    if (u == 1) {
        f[u][0] = s;
        return;
    }
    f[u][0] = a[fa] <= a[u] ? s1 + a[fa] : s + a[fa];
    f[u][1] = s1 + a[u];
    f[u][2] = m <= a[u] ? s1 + m : s + m;
}
```






---

## 作者：AK_Dream (赞：10)

事月赛结束后1个多小时才开始做月赛题的屑选手

看到这个题目，想到一个naive的贪心，写了一下就爆WA了

然后去重新读了一遍题目 发现数据范围有 $5e5$，大概率不会是 $O(n\log n)$ 算法了，于是自然想到树形DP

首先，设 $x$ 的度数为 $de[x]$，题目中的"中位数"不超过 $a[x]$，可以理解为和 $x$ 相连的边中，至少要有 $\lfloor\dfrac{de[x]}{2}\rfloor + 1$ 条边权小于等于 $a[x]$。

当然，这就等价于说最多有 $\lceil\dfrac{de[x]}{2}\rceil - 1$ 条边权大于 $a[x]$ 的边，不妨设 $now[x]=\lceil\dfrac{de[x]}{2}\rceil - 1$。

设 $dp[x][0/1]$ 表示点 $x$ 的答案，其中 $dp[x][0]$ 表示 $x$ 连向父亲的边权值小于等于 $a[x]$ 时，$x$ 子树内最大的边权和；

而 $dp[x][1]$ 表示连向父亲的边权值可以大于 $a[x]$ 时，$x$ 子树内最大的边权和；

然后考虑怎么转移：

(1) $dp[x][0]$

由于 $x$ 连向父亲的边小于等于 $a[x]$ ，所以在所有 $x$ 连向儿子的边中，最多可以有 $now[x]$ 条边权大于 $a[x]$。

考虑 $x$ 的每个儿子 $y$，设 $p_y$ 表示 $x\rightarrow y$ 边权小于等于 $a[x]$ 时，($y$ 子树内的边权和加上 $x\rightarrow y$ 边权) 的最大值，$q_y$ 表示 $x\rightarrow y$ 边权可大于 $a[x]$ 时的值。

有如下的式子：

$$p_y = \max(dp[y][0]+\min(a[x],a[y]),dp[y][1]+a[x])$$
$$q_y = \max(dp[y][0]+a[y],dp[y][1]+m)$$

对于每个儿子 $y$ ，我们要么让 $dp[x][0]$ 加上 $p_y$，要么让它加上 $q_y$，但是由于最多只能有 $now[x]$ 条边权大于 $a[x]$ 的边，所以最多只有 $now[x]$ 个儿子能取 $q_y$。

对于 $dp[x][1]$ 的转移也同理，但是转移 $dp[x][1]$ 时只有 $now[x]-1$ 个儿子能取 $q_y$

这是什么？01背包啊！

把每个儿子看作一个物品，重量为 $1$，价值为 $q_y-p_y$  (如果 $q_y-p_y<0$ 就不用管这个儿子了)，然后跑一个01背包，存储在 $f[N]$ 数组里

那么就有 $dp[x][0]=\sum\limits_y p_y + f[now[x]]$  
$dp[x][1]=\sum\limits_y p_y + f[now[x]-1]$

完成！答案即为 $\max(dp[1][0],dp[1][1])$

然后交上去被菊花图卡成翔

发现这个01背包的物品重量都是 $1$ 。。。那还01背包个鬼哦，直接把 $q_y-p_y$ 从大到小排序，$f[i]$ 就是前 $i$ 项的前缀和

时间复杂度 $O(n\log n)$。。。还是没能逃过那个给 $q_y-p_y$ 排序的 $\log$ 但是一个`sort`能有多慢呢QWQ 最慢点(估计是菊花图)只跑了165ms


### 代码
```cpp
#include <bits/stdc++.h>
#define N 500005
using namespace std;
typedef long long ll;

template<typename T>
inline void read(T &num) {
	T x = 0, ff = 1; char _ch = getchar();
	for (; _ch > '9' || _ch < '0'; _ch = getchar()) if (_ch == '-') ff = -1;
	for (; _ch <= '9' && _ch >= '0'; _ch = getchar()) x = (x << 3) + (x << 1) + (_ch ^ '0');
	num = x * ff;
}

int n, m, a[N], now[N], tot;
int head[N], pre[N<<1], to[N<<1], sz;
ll dp[N][2], val[N], f[N];

inline void addedge(int u, int v) {
	pre[++sz] = head[u]; head[u] = sz; to[sz] = v;
	pre[++sz] = head[v]; head[v] = sz; to[sz] = u;
}

void dfs(int x, int fa) {
	for (int i = head[x]; i; i = pre[i]) {
		int y = to[i];
		if (y == fa) continue;
		dfs(y, x);
	}
	for (int i = 0; i <= now[x]; i++) f[i] = val[i] = 0; 
	tot = 0; ll sum = 0;
	for (int i = head[x]; i; i = pre[i]) {
		int y = to[i];
		if (y == fa) continue;
		ll p = max(dp[y][0] + min(a[x], a[y]), dp[y][1] + a[x]);
		ll q = max(dp[y][0] + a[y], dp[y][1] + m);
		if (q > p) val[++tot] = q - p;
		sum += p;
	}
	sort(val + 1, val + tot + 1, greater<ll>() );
	for (int i = 1; i <= now[x]; i++) {
		f[i] = f[i-1] + val[i];
	}
	dp[x][0] = sum + f[now[x]];
	if (now[x] > 0) dp[x][1] = sum + f[now[x]-1];
	else dp[x][1] = -0x3f3f3f3f3f3f3f3f;
}

int main() {
	read(n); read(m); tot = n - 1;
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1, u, v; i < n; i++) {
		read(u); read(v); now[u]++; now[v]++;
		addedge(u, v);
	}
	for (int i = 1; i <= n; i++) {
		now[i] = (now[i] + 1) / 2 - 1;
	}
	dfs(1, 0); 
	printf("%lld\n", max(dp[1][0], dp[1][1]));
	return 0;
}
```


---

## 作者：囧仙 (赞：7)

一道感觉有一定思维难度的树形 dp 题

- **中位数** 

   做这道题，首先要明白这个中位数 $\le a_i$ 的本质
  
   根据题目给的定义，中位数就是第 $\left\lfloor\dfrac{k}{2}\right\rfloor+1$ 小的数
  
   由此可以推得，前 $\left\lfloor\dfrac{k}{2}\right\rfloor+1$ 小的数都必须 $\le a_i$
  
   也就是说，至多只能有 $k - \left\lfloor\dfrac{k}{2}\right\rfloor - 1$ 个数 $>a_i$
  
- **设计 dp**

   现在题意已经被我们转化为：
   
   给你一颗树，要给每条边标上一个 $[1,m]$ 中的边权，满足每个点直接相连的边中，至多有 $b_i$ 条边的权 $>a_i$，且边权和最大。
   
   那么这个东西一看就很 dp，因为不与 $i$ 直接相连的边与 $i$ 点都是无关的，就没有后效性
   
   但是问题就来了，一般在树上 dp 我们都是设 $dp_i$ 为以 $i$ 为根的子树的某些信息，然后用一遍 dfs 来进行转移，但是当我们给以 $i$ 为根的子树中的所有边都标上边权时，我们却没法确定 $i$ 点加上连接 $i$ 与 $i$ 父亲的边是否依然合法
   
   所以我们改一下状态，改为 $dp_i$ 表示给以 $i$ 为根的子树内的所有边都标上了边权，且给连接 $i$ 与 $i$ 的父亲的边也标上了边权，以 $i$ 为根的子树内的所有点都合法的最大边权和
   
   但是这样就还有一个问题：连接 $i$ 与 $i$ 父亲的边可能大于 $a_{fa}$，也可能不大于 $a_{fa}$
   
   所以还得分类，改为 $dp_{i,0}$ 表示给以 $i$ 为根的子树内的所有边都标上了边权，且给连接 $i$ 与 $i$ 父亲的边也标上了边权，且这条边的权 $\le a_{fa}$ 的最大边权和
   
   $dp_{i,1}$ 同理，只不过这条边的边权 $> a_{fa}$
   
- **dp 转移**

   dp 只有一个没有后效性的状态设计可不够，还要有转移
   
   那么在从 $now$ 的儿子向 $now$ 转移时，实际上每个 $dp_{son,1}$ 就使得 $now$ 点相连的边多了一条 $>a_{now}$ 的
   
   所以我们要在所有 $now$ 的儿子中，选择一些 $dp_{son,0}$，选择一些 $dp_{son,1}$，最后确定连接 $now$ 与 $fa$ 的边的边权
   
   实际上，确定连接 $now$ 与 $fa$ 的边的边权反而是最重要的，要最先做，因为只有确定了这个，你才能知道可以最多选多少个 $dp_{son,1}$
   
   1. 连接 $now$ 与 $fa$ 的边小于等于 $now$ 与 $fa$ 的权，则我们要选至多 $b_{now}$ 个 $dp_{son,1}$，其余选 $dp_{son,0}$，边权当然是 $\min(a_{now},a_{fa})$ 最优，状态转移到 $dp_{now,0}$
   
   2. 连接 $now$ 与 $fa$ 的边小于 $now$ 的权，大于 $fa$ 的权，实际上选择的内容和 1 是一样的，只不过边权改为 $a_{now}$，转移到 $dp_{now,1}$
   
   3. 连接 $now$ 与 $fa$ 的边大于 $now$ 的权,小于 $fa$ 的权，则我们要选至多 $b_{now} - 1$ 个 $dp_{son,1}$，其余选 $dp_{son,0}$，边权选 $a_{fa}$，转移到 $dp_{now,0}$
   
   4. 连接 $now$ 与 $fa$ 的边大于 $now,fa$ 的权，选择的内容与 3 一样，边权 $m$ 最优，转移到 $dp_{now,1}$
   
- **解决选择的问题**

  现在问题被我们转化为这样：
  
  给你两个长度为 $n$ 的序列 $a,b$，你可以使最多 $k$ 个 $i$ 的贡献为 $b_i$，其余贡献为 $a_i$，要求贡献最大
  
  那么这个感觉就很可以用贪心来做，设 $c_i = b_i - a_i$，显然要选 $c_i$ 最大的 $k$ 个（如果 $c_i < 0$ 就不选了）
  
- **总结**

  然后这道题就做完了，感觉还是挺复杂的，不知道是不是我把问题弄复杂了
  
  还有一些小细节，比如转移根节点的时候不能标根节点与根节点父亲的权
  
  最后放一下代码：
  
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
int n,m;
int a[500005];

int cnt;
int head[500005];
struct eg{
	int to,nxt;
}edge[1000005];

void make(int u,int v){
	edge[++cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}

int deg[500005];
//给每个边标一个边权,每个点相连的边中,至多 k 条边的权 > a[i]

ll dp[500005][2];//dp[i][0] 表示以 i 为根的子树内的所有边，以及连接 i 与 i 父亲的边都标上了权且合法，连接 i 与 i 父亲的边 < a[fa[i]]
//dp[i][1] 表示大于

//前 [k / 2] + 1 个 <= 
//k - [k / 2] - 1 个大于

//1. 连接 i 与 i 父亲的边小于 i 与 i 父亲的权,则 dp[i][0] = 前 k 大的 dp[son][1] + 其他的 dp[son][0] + min(a[i],a[fa[i]])
//2. 连接 i 与 i 父亲的边小于 i 的权,大于 i 父亲的权 dp[i][1] = 前 k 大的 dp[son][1] + 其他的 dp[son][0] + a[i]
//3. 连接 i 与 i 父亲的边大于 i 的权,小于 i 父亲的权 dp[i][0] = 前 k - 1 大的 dp[son][1] + 其他的 dp[son][0] + a[fa[i]]
//4. 连接 i 与 i 父亲的边大于 i 的权,大于 i 父亲的权 dp[i][1] = 前 k - 1 大的 dp[son][1] + 其他的 dp[son][0] + m

int len;
int Q[500005];

bool cmp(int x,int y){
	return (dp[x][1] - dp[x][0]) > (dp[y][1] - dp[y][0]);
}

ll max(ll a,ll b){
	if(a < b) return b;
	return a;
}

ll min(ll a,ll b){
	if(a < b) return a;
	return b;
}

void dfs(int now,int fa){
	for(int i = head[now];i;i = edge[i].nxt){
        if(edge[i].to == fa) continue;
        dfs(edge[i].to,now);
	}
	len = 0;
	for(int i = head[now];i;i = edge[i].nxt){
		if(edge[i].to == fa) continue;
		Q[++len] = edge[i].to;
	}
	/*printf("node %d: fa %d sons : \n",now,fa);
	for(int i = 1;i <= len;i++) printf("%d ",Q[i]);
	printf("\n"); */
    std::sort(Q + 1,Q + len + 1,cmp);

    ll tmp = 0;

    for(int i = 1;i <= len;i++){
    	if(i <= deg[now]) tmp += dp[Q[i]][1];
    	else tmp += dp[Q[i]][0];
    }
    if(now != 1) tmp += min(a[now],a[fa]);
    dp[now][0] = max(dp[now][0],tmp);

    if(a[now] > a[fa]){
    	tmp = 0;
    	for(int i = 1;i <= len;i++){
    		if(i <= deg[now]) tmp += dp[Q[i]][1];
    		else tmp += dp[Q[i]][0];
    	}
    	if(now != 1) tmp += a[now];
    	dp[now][1] = max(dp[now][1],tmp);
    }

    dp[now][1] = max(dp[now][0],dp[now][1]);

    if(!deg[now]) return;
    
    tmp = 0;
    if(a[now] < a[fa]){
    	for(int i = 1;i <= len;i++){
    		if(i < deg[now]) tmp += dp[Q[i]][1];
    		else tmp += dp[Q[i]][0];
    	}
    	if(now != 1) tmp += a[fa];

    	dp[now][0] = max(dp[now][0],tmp);
    }

    tmp = 0;

    for(int i = 1;i <= len;i++){
    	if(i < deg[now]) tmp += dp[Q[i]][1];
    	else tmp += dp[Q[i]][0];
    }
    if(now != 1) tmp += m;

    dp[now][1] = max(dp[now][1],tmp);

    dp[now][1] = max(dp[now][0],dp[now][1]);
}

int main(){
	memset(dp,0xcf,sizeof(dp));
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;i++){
    	scanf("%d",&a[i]);
    }
    for(int i = 1;i < n;i++){
    	int u,v;
    	scanf("%d%d",&u,&v);
    	make(u,v);
    	make(v,u);
        deg[u]++;
        deg[v]++;
    }
    for(int i = 1;i <= n;i++){
    	deg[i] = deg[i] - deg[i] / 2 - 1;
    }
    a[0] = m;
    dfs(1,0);

    printf("%lld\n",max(dp[1][0],max(dp[1][1],-1)));
	return 0;
}
```


---

## 作者：littleKtian (赞：3)

前置芝士：树形 dp、贪心

------------

题意：有一棵树，树上每个点有一个点权 $a_i$，要求给每条边分配一个边权 $b_i(b_i\in \left[1,m\right])$，使得所有与点 $i$ 连接的边的边权从小到大排序后**中位数不超过 $a_i$**，且所有边边权和**最大**，输出这个最大值。

------------

设 $d_i$ 表示第 $i$ 个点最多允许 $d_i$ 条边边权大于 $a_i$，这玩意可以 $O(1)$ 计算。

设 $f_{i,0/1}$ 分别表示点 $i$ 连向父亲的边可以/不可以大于 $a_i$ 时以 $i$ 为根的子树中边权和的最大值，容易发现 $f_{i,0/1}$ 分别对应所有点 $i$ 连向儿子的边中选出**至多** $d_i-1/d_i$ 条边使其边权大于 $a_i$ 时边权和的最大值。特别的，当 $d_i=0$ 时，$f_{i,0}$ 不存在。

容易发现一条边选或不选，其贡献是确定的，所以只要贪心选取选与不选的贡献中差值最大的前 $d_i-1/d_i$ 条边就能求出了。总复杂度 $O(n\log n)$。

具体实现有一定细节（比如差值 $<0$ 的边也不会选，但我不知道会不会有这种情况）。

代码（树形 dp 部分）

```cpp
void dfs(int w,int fa)
{
	int o_o=lst[w];
	while(o_o)
	{
		int v=bi[o_o][1];
		if(v!=fa)dfs(v,w);
		o_o=bi[o_o][0];
	}
	tot=0,o_o=lst[w];
	while(o_o)
	{
		int v=bi[o_o][1];
		if(v!=fa)
		{
			++tot;
			if(a[w]<a[v])g[tot].x=max(max(f[v][0],f[v][1])+a[v],f[v][0]+m),g[tot].y=max(f[v][0],f[v][1])+a[w];
			else if(a[w]>a[v])g[tot].x=f[v][0]+m,g[tot].y=max(f[v][0]+a[w],max(f[v][0],f[v][1])+a[v]);
			else g[tot].x=f[v][0]+m,g[tot].y=max(f[v][0],f[v][1])+a[w];
		}
		o_o=bi[o_o][0];
	}
	sort(g+1,g+tot+1,cmp);
	int d=ds[w]-((ds[w]>>1)+1);
	for(int i=1;i<d;i++)
	{
		ll ad=max(g[i].x,g[i].y);
		f[w][0]+=ad,f[w][1]+=ad;
	}
	f[w][0]+=g[d].y,f[w][1]+=max(g[d].x,g[d].y);
	for(int i=d+1;i<=tot;i++)f[w][0]+=g[i].y,f[w][1]+=g[i].y;
	if(d==0)f[w][0]=oo;
}
```


---

## 作者：EM_LGH (赞：3)

首先，肯定没有不合法情况（每条边的权值都赋值为 $1$ 就一定合法）   

然后对于一条边 $(x,y)$ 来说，只可能有 3 种取值.  

1. 取 $a[x]$ 

2. 取 $a[y]$ 

3. 取 $m$    

然后转化成这一步后就可以进行树形 DP 了.  

令 $f[x][0],f[x][1]$ 分别表示以 $x$ 为根的子树，且 $x$ 与 $x$ 父亲连边的边权小于等于 $a[x]$/大于 $a[x]$ 的最大权和.     

这个裸做的话是一个 $O(n^2)$ 的树形背包.  

但是我们发现这个问题中所有物品的体积都是 $1$，那么我们就可以先贪心选取一个儿子 $y$ 的最优决策点.   

如果该决策点没有让边权小于等于 $a[x]$ ，就把差量扔进一个 set 里，贪心取出需要补齐的部分就行了.  

时间复杂度 $O(n \log n)$.    

代码：
```cpp
#include <cstdio>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
#define N 500009 
#define ll long long
#define setIO(s) freopen(s".in","r",stdin)
using namespace std; 
const ll inf=1000000000;   
int n,m,edges; 
ll f[N][2]; 
int deg[N];
int a[N],hd[N],to[N<<1],nex[N<<1]; 
void add(int u,int v) {
    nex[++edges]=hd[u];
    hd[u]=edges,to[edges]=v;
}
multiset<ll>se[N];         
multiset<ll>::iterator it; 
void dfs(int x,int ff) { 
    int det=deg[x]/2+1,cnt=0;     
    // f[x][0] : det-1 
    // f[x][1] : det    
    f[x][0]=f[x][1]=0;    
    for(int i=hd[x];i;i=nex[i]) {
        int y=to[i];  
        if(y==ff) continue; 
        dfs(y,x);    
        ll cur=max(f[y][0]+a[y],f[y][1]+m);      
        f[x][0]+=cur; 
        f[x][1]+=cur;  
        if(a[x]>=a[y]) {
            if(f[y][1]+m==cur&&m>a[x]) {            
                se[x].insert(-(max(f[y][0]+a[y],f[y][1]+a[x])-cur));          
            } 
            else ++cnt;   
        }
        else {
            se[x].insert(-(max(f[y][0]+a[x],f[y][1]+a[x])-cur));   
        }
    }   
    int k0=det-1,k1=det;     
    if(cnt+se[x].size()>=k0) {   
        it=se[x].begin();  
        for(int i=1;i<=k0-cnt;++i)   { 
            f[x][0]-=(*it);             
            it++;  
        }
    }      
    else f[x][0]=-inf;  
    if(cnt+se[x].size()>=k1) { 
        it=se[x].begin(); 
        for(int i=1;i<=k1-cnt;++i)   {  
            f[x][1]-=(*it);
            it++;  
        }
    } 
    else f[x][1]=-inf;
    se[x].clear();  
    if(deg[x]==1&&ff) {  
        f[x][0]=0;  
        f[x][1]=-inf;  
    }  
}  
int main() {
    // setIO("input");  
    scanf("%d%d",&n,&m);  
    for(int i=1;i<=n;++i) {
        scanf("%d",&a[i]);
        a[i]=min(a[i],m);   
    }  
    int x,y,z;
    for(int i=1;i<n;++i) {
        scanf("%d%d",&x,&y);
        add(x,y); 
        add(y,x);  
        ++deg[x];
        ++deg[y]; 
    }        
    dfs(1,0);  
    printf("%lld\n",f[1][1]);     
    return 0;
}
```


---

## 作者：KaguyaH (赞：2)

> [**返回题目**](/problem/P6748) [**博客查看**](/blog/236807/Solution-luogu-P6748)

## 题意简述

- 给定一个 $n$ 个点的树，每个节点有一个点权 $a$。
- 你的任务是为每条边指定一个在 $[1, m]$ 的边权，使得对于任意一个节点，她的出边的权值的中位数不大于她的点权。
- 形式化地，令 $v_i$ 为 $i$ 的出边序列，$d_i$ 为 $i$ 的度，则 $v_i$ 中超过 $a_i$ 的数的个数不应超过 $\left\lfloor\frac{d_i - 1}2\right\rfloor$。
- $2 \leqslant n \leqslant 5 \times 10^5$，$1 \leqslant m \leqslant 10^9$。

## 题目分析

考虑树形 DP，可人为规定任意一个点作为根。

### 状态设计

考虑点 $i$ 的子树时，其向母亲连的边并未被考虑。该边有两种情况：大于 $a_i$ 或不大于 $a_i$。

于是，我们可以如下定义状态：$f_{i, j}$ 表示以 $i$ 为根的子树中的最大可行边权和，满足 $i$ 节点连向母亲节点的边可以（$1$）/不一定可以（$0$）大于 $a_i$，其中 $i \in [1, n]$，$j \in \{0, 1\}$。

### 状态转移

假设当前转移到点 $i$。

首先，先将 $f_{i, 0}$ 和 $f_{i, 1}$ 设为所有出边均不大于 $a_i$ 的满足条件的最大值。

定义 $g_j$ 为此时 $i$ 的女儿 $j$ 的贡献，即

$$
g_j \leftarrow \max(f_{j, 0} + \min(a_i, a_j), f_{j, 1} + a_i)
$$

$$
f_{i, 0},f_{i, 1} \leftarrow \sum_{j \in daughter_i}g_j.
$$

然后，考虑如果一条边大于 $a_i$，对 $f_i$ 的贡献。

定义此时的贡献为 $h_j$，则

$$
h_j \leftarrow \max(f_{j, 1} + m, f_{j, 0} + a_j(a_j > a_i)) - g_j.
$$

那么，我们可以求出大于 $0$ 的 $h_j$ 中最大的几个加入到 $f_i$ 中。

具体地，$f_{i, 0}$ 可以取 $\left\lfloor\frac{d_i - 1}2\right\rfloor$ 个， $f_{i, 1}$ 可以取 $\left\lfloor\frac{d_i - 1}2\right\rfloor - 1$ 个。

这里需要注意一点，如果 $f_{i, 1}$ 取的限制为 $-1$，即 $\left\lfloor\frac{d_i - 1}2\right\rfloor = 0$，那么说明 $f_{i, 1}$ 不合法，赋值为 $-\inf$ 即可。

## 代码

```cpp
# include <cctype>
# include <cstdio>
# include <algorithm>
# include <vector>

typedef long long signed int lld;
typedef short unsigned int hu;
typedef long unsigned int lu;
typedef long long unsigned int llu;
enum { N = (const lu)5e5, M = (const lu)1e9 };
static const lld min_lld(-1ll * M * N);
static inline const void amax(lld& a, const lld b) { if (a < b) a = b; }
static inline const lu max(const lld a, const lld b) { return a < b ? b : a; }
static inline const lu min(const lu a, const lu b) { return b < a ? b : a; }
static const lu (*_max)(const lld, const lld)(max);

const class IOstream {
public:
	inline const IOstream operator>>(lu&) const;
	inline const IOstream operator<<(llu) const;
} io;

struct node {
	struct edge {
		lu to;
		const edge* next;
		edge() : to(), next(nullptr) {}
		edge(const lu to, const edge* const next) : to(to), next(next) {}
	};
	lu a;
	lu d;
	const edge* head;
	std::vector<lld> delta;
	lld f[2];
	node() : a(0), d(0), head(nullptr) { f[1] = f[0] = 0; }
	inline const void add(const lu to) { head = new edge(to, head); }
	inline const lu delta_f() const;
	inline const lu max() const { return (d - 1) / 2; }
};

static lu n, m;
static node o[N + 1];

inline const lu node::delta_f() const { return _max(f[1] + m, f[0] + a) - f[0]; }
static inline const bool comp(const lu a, const lu b) { return a > b; }

static const void search(const lu x = 1, const lu f = 0) {
	for (const node::edge* i(o[x].head); i; i = i->next) {
		if (i->to not_eq f) {
			const lu to(i->to); const node& v(o[to]);
			search(to, x);
			lld t(v.f[0] + min(o[x].a, v.a));
			if (o[x].a > v.a) amax(t, v.f[1] + o[x].a);
			o[x].f[0] += t, o[x].f[1] += t;
			lld u = v.a < m ? v.f[1] + m : v.f[1] + m;
			if (o[x].a < o[i->to].a) amax(u, o[i->to].f[0] + o[i->to].a);
			u -= t;
			//printf("%lu %lu %lld\n", x, to, u);
			if (u > 0) o[x].delta.push_back(u);
		}
	}
	//printf("%lu %lld %lld\n", x, o[x].f[0], o[x].f[1]);
	std::sort(o[x].delta.begin(), o[x].delta.end(), comp);
	const lu d(o[x].d), _d(d - (const bool)f);
	for (register lu i(0); i < o[x].max() and i < o[x].delta.size(); ++i)
		o[x].f[0] += o[x].delta[i];
	for (register lu i(0); i + 1 < o[x].max() and i < o[x].delta.size(); ++i)
		o[x].f[1] += o[x].delta[i];
	//printf("%lu %lld %lld\n", x, o[x].f[0], o[x].f[1]);
	if (d <= 2) o[x].f[1] = min_lld;
	//printf("%lu %lld %lld\n", x, o[x].f[0], o[x].f[1]);
}

signed int main() {
	io >> n >> m;
	for (register lu i(1); i <= n; ++i) io >> o[i].a;
	for (register lu i(1); i < n; ++i) {
		static lu u, v;
		io >> u >> v;
		++o[u].d, ++o[v].d;
		o[u].add(v), o[v].add(u);
	}
	search();
	io << o[1].f[0];
	return 0;
}

inline const IOstream IOstream::operator>>(lu& a) const {
	char t;
	while (isspace(t = getchar()));
	a = 0;
	while (a = a * 10 + (t - '0'), isdigit(t = getchar()));
	return *this;
}
inline const IOstream IOstream::operator<<(llu a) const {
	char s[20]; hu l(0);
	while (s[l++] = a % 10 + '0', a /= 10);
	while (l) putchar(s[--l]);
	putchar('\n');
	return *this;
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

对于一条边 $u \to v$，它的权值只会影响到 $u$ 和 $v$ 两个节点，故我们得出结论，这条边的权值只有三种选择 $a_u$，$a_v$ 和 $m$。

对于一个节点，不妨设它的度为 $k$，则与它相邻的边的权值的中位数大于这个点的忍耐度，我们可以将其转化为，存在最多 $k-\lfloor\dfrac{k}{2}\rfloor-1$ 条边的权值大于其忍耐度。

我们设计 dp

令 $f_{u,0/1}$ 表示以 $u$ 为根的子树，$fa \to u$ 这条边的权值不大于（大于） $a_u$ 的答案。

相应的，对于所有的 $u\to v$，我们只需要从中选出 $k-\lfloor\dfrac{k}{2}\rfloor-1/k-\lfloor\dfrac{k}{2}\rfloor-2$ 条边使其权值为 $m$，剩下的边权值为 $\min(a_u,a_v)$ 即可。

注意到这个 01 背包的体积为 1，所以我们只需要排序后从大到小选即可，时间复杂度 $O(n\log n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500005;
const int INF=0x3f3f3f3f3f3f3f3f;
struct edge{
	int v,nxt;
}edge[N<<1];
int head[N],cnt;
int n,m;
int a[N],deg[N];
int val[N],sum[N];
int f[N][2];
void addedge(int u,int v){
	edge[++cnt].v=v,edge[cnt].nxt=head[u],head[u]=cnt;
}
void dfs(int u,int fa){
	int k=deg[u]-deg[u]/2-1,tot=0,o=0;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==fa) continue;
		dfs(v,u);
	}
	for(int i=1;i<=k;i++) val[i]=sum[i]=0;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==fa) continue;
		int p=max(f[v][0]+min(a[u],a[v]),f[v][1]+a[u]);
		int q=max(f[v][0]+a[v],f[v][1]+m);
		tot+=p;
		if(q>p) val[++o]=q-p;
	}
	sort(val+1,val+1+o,[](int x,int y){return x>y;});
	for(int i=1;i<=k;i++) sum[i]=sum[i-1]+val[i];
	f[u][0]=tot+sum[k];
	if(k) f[u][1]=tot+sum[k-1];
	else f[u][1]=-INF;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%lld%lld",&u,&v);
		addedge(u,v),addedge(v,u);
		deg[u]++,deg[v]++;
	} 
	dfs(1,0);
	printf("%lld\n",max(f[1][0],f[1][1]));
	return 0;
}

```


---

## 作者：LaDeX (赞：0)

[P6748 『MdOI R3』Fallen Lord](https://www.luogu.com.cn/problem/P6748)。

树形 DP 好题。

我们先钦定 $1$ 为根吧。容易发现一个点周围的边是否合法，和具体的边权大小无关，而和边权与点权的相对大小有关。。于是我们定义状态：$f_{i,0/1}$ 表示点 $i$ 子树内的边和 $i$ 向父亲的边都已经确定了权值，子树内的点都合法了，并且连向父亲的边是或否大于父亲点权，最大的边权和。然后考虑转移。

先合并子节点状态，而不考虑父节点这条边。注意到为了满足合法条件，至多有 $\lfloor\frac{d - 1}{2}\rfloor$ 条连边是大于当前节点的权值的。我们求出 $r_0,r_1$，分别表示在通往子节点的边中选择了小于等于 $\lfloor\frac{d-1}{2}\rfloor$ 或 $\lfloor\frac{d-1}{2}\rfloor-1$ 条大于当前点权的边，的最大边权和。求出 $r_1$ 是为了考虑往父节点连一条大于当前点权的边这一情况。具体求解以 $r_0$ 为例，我们先不考虑限制，在子节点的 $f_{v,0/1}$ 中取 $\max$ 直接求和，并把所有最大值取到 $f_{v,1}$ 的 $v$ 记录下来，假设有 $c$ 个子节点取到了 $f_{v,1}$，如果 $c\leq \lfloor\frac{d-1}{2}\rfloor$ 那么合法，否则我们需要更换 $c-\lfloor\frac{d-1}{2}\rfloor$ 条边为小于当前点权。于是我们把这些选择了 $f_{v,1}$ 的子节点按照 $(f_{v,1}-f_{v,0})$ 升序排序并取前 $c-\lfloor\frac{d-1}{2}\rfloor$ 小的即可。

在求出了 $r_0,r_1$ 之后，再来解决当前节点的 $f$ 状态。记 $u$ 为当前节点，$p$ 为父节点。对于 $r_0,r_1$，我们有一种另外的解释，$r_0$ 即为连向父亲的边只能小于等于 $a_u$ 的边权，子树的答案，$r_1$ 则表示连向父亲的边任意，子树的答案。轻微分讨一下：

- 当 $a_p < a_u$​ 时，有以下两种转移：
  - $f_{u,0}\leftarrow\max(r_0,r_1)+a_p.$
  - $f_{u,1}\leftarrow \max(r_0+a_u,r_1+m).$

- 当 $a_p \geq a_u$ 时，有以下两种转移：
  - $f_{u,0}\leftarrow\max(r_0+a_u,r_1+a_p).$
  - $f_{u,1}\leftarrow r_1+m.$

然后做完了。答案显然就是根节点的 $r_0$ 值。注意要考虑当 $\lfloor\frac{d - 1}{2}\rfloor=0$ 以及叶子节点之类的 corner case。

```cpp 
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e5 + 10;
int n; LL m, A[N], DP[N][2]; vector<int> G[N];
void DFS(int u, int f) {
	if (G[u].size() - (f > 0) == 0) {
		if (A[f] >= A[u]) DP[u][0] = A[u], DP[u][1] = -1e15;
		else DP[u][0] = A[f], DP[u][1] = A[u];
		return ;
	}
	for (int v : G[u]) if (v != f) DFS(v, u);
	int d = ((int)G[u].size() - 1) / 2, cnt = 0; vector<LL> tmp; LL res1 = 0, res0 = 0;
	for (int v : G[u]) if (v != f) {
		res1 += max(DP[v][0], DP[v][1]);
		if (DP[v][1] > DP[v][0]) tmp.emplace_back(DP[v][1] - DP[v][0]), ++ cnt;
	} sort(tmp.begin(), tmp.end()); res0 = res1;
	for (int i = 0; i < cnt - d; i ++) res0 -= tmp[i];
	if (!f) { DP[u][0] = res0; return ; }
	if (!d) {
		if (A[f] >= A[u]) DP[u][0] = res0 + A[u], DP[u][1] = -1e15;
		else DP[u][0] = res0 + A[f], DP[u][1] = res0 + A[u];
		return ;
	}
	for (int i = 0; i < cnt - d + 1; i ++) res1 -= tmp[i];
	if (A[f] >= A[u]) DP[u][0] = max(res1 + A[f], res0 + A[u]), DP[u][1] = res1 + m;
	else DP[u][0] = max(res0, res1) + A[f], DP[u][1] = max(res0 + A[u], res1 + m);
}

int main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m; if (!n) { cout << "0\n"; return 0; }
	for (int i = 1; i <= n; i ++) cin >> A[i];
	for (int i = 1, u, v; i < n; i ++) {
		cin >> u >> v; G[u].emplace_back(v); G[v].emplace_back(u);
	}
	DFS(1, 0); cout << DP[1][0] << "\n";
	return 0;
}
```

---

## 作者：一架飞机 (赞：0)

## 题意

给定一个 $x$ 个点的树，每个节点有一个点权 $a_i$。

你的任务是为每条边指定一个在 $[1, m]$ 的边权，使得对于任意一个节点，它的出边的权值的中位数不大于它的点权。

求最大边权和。

$2 \leqslant n \leqslant 5 \times 10^5$，$1 \leqslant m \leqslant 10^9$。

## 思路

### 1.找性质简化题目

搞一下中位数，就是：令 $v_i$ 为点 $i$ 的出边边权序列，$ind_i$ 为 $i$ 的度，则 $v_i$ 中小于等于 $a_i$ 的数的个数大于等于 $\left\lfloor\frac{d_i}2\right\rfloor+1$ 个。

因为要最大，所以贪心地让它“往上顶”，所以边 $(x,fa)$ 的边权 $va$ 只有 3 种可能：$m$，$w[x]$，$w[fa]$。

### 2.找算法

发现一个边只会对它的端点起作用，容易想到 [没有上司的舞会](https://www.luogu.com.cn/problem/P1352)。考虑树形 dp。设 up 边表示边 $(x,fa)$。定义 $dp[x][0/1/2]$ 表示 $x$ 这个子树中，钦定 $x$ 的 up 边权值为 $a_{fa}/a_u/m$ 的，最大子树边权和（包括 up 边）。

很容易想到 $n^2$ 的背包。$f[i][j]$ 表示考虑 $x$ 的前 $i$ 个 son，有 $j$ 个 son 的 up 边小于等于 $a_i$ 的最大边权和。

### 3.优化

这里可以贪心地用代价（不规定 up 边小于等于 $a_x$ 的最大和减规定 up 边小于等于 $a_x$ 的最大和 ）最小的那几个。

证明正确性：首先它肯定是符合条件的。然后**它影响的代价只有那个儿子下面的和父亲，而儿子的代价我们已经知道了，父亲的代价只和数量有关，所以保证了没有后效性**。

---

