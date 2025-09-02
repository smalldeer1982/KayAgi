# 「dWoi R2」Arcade hall / 街机厅

## 题目背景

众所周知，才囚学院地下有一个街机厅，~~百田被星龙马打败了 114514 次~~。

百田不服气，于是他打开了一个单人游戏 —— 先辈的城市。

---

114514 年，火星，幺舅幺舅巴以灵国。

因为有小可爱提出题面过于冗长，所以下方有 **简要题面**。

## 题目描述

幺舅幺舅巴以灵国一共有 $n$ 个城市，他们之间用一种神奇的通讯工具 —— 先辈符，第 $i$ 个城市的先辈符上刻有一个正整数 $w_i$。这 $n$ 个城市之前有 $n-1$ 条道路，第 $j$ 条道路连接第 $u_j$ 个城市和第 $v_j$ 个城市，有一个属性 $t_j$，这一条道路就表示为 $(u_j,v_j,t_j)$，其中 $t_j \in \{0,1,2\}$，意为：

- $t_j=0$ 时，第 $u_j$ 个城市与第 $v_j$ 个城市是敌对关系；
- $t_j=1$ 时，第 $u_j$ 个城市与第 $v_j$ 个城市是平等关系；
- $t_j=2$ 时，第 $u_j$ 个城市与第 $v_j$ 个城市是友好关系。

每一条道路都是双向的，并且保证任意两个城市 $u,v$ 之间都是可以互相到达的。

最近火星发生了 MARS-514 病毒疫情，先辈符系统的修建要加快脚步。我们规定：

- $w_i \in [1,R]$，且是一个正整数；
- 对于一条道路 $(p,q,r)$，有如下要求：
	- 当 $r=0$ 时，即第 $p$ 个城市与第 $q$ 个城市处于敌对关系时，需要保证 $w_p \ne w_q$；
    - 当 $r=2$ 时，即第 $p$ 个城市与第 $q$ 个城市处于友好关系时，需要保证 $w_p=w_q$；
    - 当 $r=1$ 时，即第 $p$ 个城市与第 $q$ 个城市处于平等关系时，不需要保证 $w_p$ 与 $w_q$ 的大小关系。
    
求这样分配 $w_i$ 后，将 $w_i$ 作为一个序列，会形成多少个本质不同的序列 $w_i$。

额外地，幺舅幺舅巴以灵国的统治者浩二结节在建造先辈符发现 $w_i$ 越大，用墨就会越多，建造起来也会越困难，所以浩二结节想知道 $w_i$ 的和的最小值是多少。

注意，本题的序列 $A_i$ 与 $B_i$ 本质相同当且仅当对于所有 $i$ 都有 $A_i=B_i$。

本质不同即为不满足本质相同的两个序列。

---

**简要题面**：

- 有一棵 $n$ 个点的树，第 $i$ 个点有点权 $w_i$，第 $j$ 条边有边权 $t_j$；
- 每一条边 $(u_j,v_j,t_j)$ 两边点的点权有如下要求：
	- $t_j=0$，$w_{u_j} \ne w_{v_j}$；
    - $t_j=1$，没有要求；
    - $t_j=2$，$w_{u_j}=w_{v_j}$；
    - 对任意点权都要有 $w_i \in [1,R]$；
- 求当 $w_i$ 作为序列时，一共有多少种本质不同的序列 $w_i$ 以及 $w_i$ 的和的最小值。

## 说明/提示

#### 样例 1 解释

样例中的道路分布如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/vq4dukx8.png)

一共有 $12$ 种赋值方式：

1. $w_i=\{1,2,2\}$；
2. $w_i=\{1,2,3\}$；
3. $w_i=\{1,3,2\}$；
4. $w_i=\{1,3,3\}$；
5. $w_i= \bf \{2,1,1\}$，这是最优情况；
6. $w_i=\{2,1,3\}$；
7. $w_i=\{2,3,1\}$；
8. $w_i=\{2,3,3\}$；
9. $w_i=\{3,1,1\}$；
10. $w_i=\{3,1,2\}$；
11. $w_i=\{3,2,1\}$；
12. $w_i=\{3,2,2\}$。

#### 样例 2 解释

样例中的道路分布如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/9f1qjpm4.png)

对于第二问，其中一种最优的赋值方式是：$w_i=\{2,1,1,1,1,1,2,1,2\}$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$t_j=1$ 或 $t_j=2$；
- Subtask 2（5 pts）：$R=1$；
- Subtask 3（10 pts）：$u_j=j$，$v_j=j+1$；
- Subtask 4（20 pts）：$t_j=0$；
- Subtask 5（10 pts）：$n \le 10$，$R \le 5$；
- Subtask 6（50 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n \le 10^5$，$1 \le R \le 100$。

对于 Subtask 1 ~ 5，$R \le 40$。

上面描述 Subtask 时 $t_j=P$ 即为对于所有 $j \in [1,n)$ 都有 $t_j=P$。

其中对于 Subtask 1，“或” 意为 Subtask
1 的一部分测试点满足 $t_j=1$，另一部分测试点满足 $t_j=2$。

## 样例 #1

### 输入

```
3 3
1 2 0
1 3 0```

### 输出

```
12 4```

## 样例 #2

### 输入

```
9 3
1 2 0
1 3 1
1 4 1
2 5 2
2 6 1
6 7 0
4 8 2
4 9 0```

### 输出

```
648 12```

# 题解

## 作者：JackMerryYoung (赞：11)

# 前言

继 [P7238「DCOI」迷失森林](https://www.luogu.com.cn/problem/P7238) 后本人写的第二篇树形 DP 的题解。（终于把比赛写挂的题写完了...）

若有错误，请指出。

---

~~本题考察了选手的各种优化技巧。~~

我一开始没有想到 $\mathcal{O}(nR)$ 的算法，发现过不了，看了书虫的题解才明白。

本人觉得书虫的题解有点~~奇怪~~深奥（太蒻了，看的时候差点没看懂），自己写了一篇。

本题较 [P7238「DCOI」迷失森林](https://www.luogu.com.cn/problem/P7238) 较为简单，不过看看我的提交记录就知道有多坑了...

![](https://cdn.luogu.com.cn/upload/image_hosting/u3t9vg4a.png)

（~~这件事告诉我们：特判与初始化很重要~~）

好了，废话不多说，又双叒叕开始讲题了！

# 正文

## 第一问

我们分类讨论。

设 $t$ 为连接 $i$ 和其子节点 $j$ 的边的边权。

### 1. $t = 0$

子节点可以选与父节点不一样的值，因此有 $R - 1$ 种方案。

### 2. $t = 1$

子节点的值并没有要求，因此有 $R$ 种方案。

### 3. $t = 2$

子节点的值必须与父节点一样，因此有 $1$ 种方案。

于是将所有节点的值乘在一起，结果即为答案。

记得一开始乘个 $R$！

## 第二问

依旧分类讨论。

设 $f_{i, j}$ 为第 $i$ 个节点的点权为 $j$ 时的最小值，则枚举的时候设 $k$ 为子节点 $son$ 的点权。

### 1. $t = 0$

子节点必须与父节点不同，因此将每个子节点选与父节点不同的值时的最小值累加即可。
$$
f_{i, j} = \min_{k = 1, k \ne j}^R{\{f_{son, k}\}} + j
$$


### 2. $t = 1$

子节点的值并没有要求，因此直接取个最小值。
$$
f_{i, j} = \min_{k = 1}^R{\{f_{son, k}\}} + j
$$


### 3. $t = 2$

子节点的值必须与父节点一样，只能从 $f_{son, j}$ 转移而来。
$$
f_{i, j} = f_{son, j} + j
$$
则答案为 $\min_{w = 1}^R{\{f_{Root, w}\}}$，而树根 $Root$ 可以随便选择，因此我们为了方便选 $1$ 号节点为根。

# ~~小~~优化

如果你真这么写了，那么恭喜您拿到了部分分...

因为你枚举父子节点的点权要 $\mathcal{O}(R^2)$。

正解：

既然没有后效性，那就在做完一个节点以后记录一下当节点 $i$ 的点权为 $j$ 时最小值的前驱最小值与后继最小值，即前面的最小：
$$
pre_{i, j} = \min_{k = 1}^{j - 1}{\{f_{i, j}\}} = \min{\{pre_{i, j - 1}, f_{i, j}\}}
$$
以及后面的最小：
$$
suf_{i, j} = \min_{k = j + 1}^{R}{\{f_{i, j}\}} = \min{\{suf_{i, j + 1}, f_{i, j}\}}
$$
于是就将第二问中，$t = 0$ 的动态转移方程改一下：
$$
f_{i, j} = \min{\{pre_{i, j}, suf_{i, j}\}}
$$
这样就不必枚举子节点的点权了，从而将复杂度降至 $\mathcal{O}(R)$，总共遍历 $N$ 个节点，所以总共复杂度为 $\mathcal{O}(nR)$。

# 代码

~~你们最想要的..~~ 

Talk is$\color{white}\text{n't}$ cheap, $\color{white}\text{Don't}$ show me the code...

```cpp
// Problem: P7846 「dWoi R2」Arcade hall / 街机厅
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7846
// Memory Limit: 512 MB
// Time Limit: 1000 ms

#include <bits/stdc++.h>
#define MOD (unsigned long long)(1e9 + 7)
using namespace std;

struct Edge {
    unsigned long long nxt, to, dis;
} edge[200005];

unsigned long long cnt, ans = 1;
unsigned long long head[200005], f[100005][105], g[100005];
unsigned long long pref[100005][105], suff[100005][105], all[100005];
bool visited[100005];

unsigned long long N, R;

void add(unsigned long long u, unsigned long long v, unsigned long long w)
{
    ++ cnt;
    edge[cnt].to = v;
    edge[cnt].nxt = head[u];
    edge[cnt].dis = w;
    head[u] = cnt;
}

void dfs1(unsigned long long u)
{
    for(unsigned long long i = head[u]; i; i = edge[i].nxt)
    {
        unsigned long long v = edge[i].to, w = edge[i].dis;
        if(visited[v]) continue;
        visited[v] = true;
        if(w == 0)      g[v] = R - 1;
        else if(w == 1) g[v] = R;
        else if(w == 2) g[v] = 1;
        else puts("114514");
        ans = ((ans % MOD) * (g[v] % MOD)) % MOD;
        dfs1(v);
    }
}

void dfs2(unsigned long long u)
{
	for(unsigned long long i = 1; i <= R; ++ i)
		f[u][i] = i;
	
    for(unsigned long long i = head[u]; i; i = edge[i].nxt)
    {
        unsigned long long v = edge[i].to, w = edge[i].dis;
        if(visited[v]) continue;
        visited[v] = true;
        dfs2(v);
        if(w == 0)
            for(unsigned long long j = 1; j <= R; ++ j)
                f[u][j] += min(pref[v][j - 1], suff[v][j + 1]);
                
        if(w == 1)
        	for(unsigned long long j = 1; j <= R; ++ j)
        		f[u][j] += all[v];
        		
        if(w == 2)
        	for(unsigned long long j = 1; j <= R; ++ j)
        		f[u][j] += f[v][j];
    }
    
    pref[u][0] = LONG_LONG_MAX;
    suff[u][R + 1] = LONG_LONG_MAX;
    all[u] = LONG_LONG_MAX;
    for(unsigned long long i = 1; i <= R; ++ i)
    	pref[u][i] = min(pref[u][i - 1], f[u][i]);
    	
    for(unsigned long long i = R; i >= 1; -- i)
    	suff[u][i] = min(suff[u][i + 1], f[u][i]);
    	
    for(unsigned long long i = 1; i <= R; ++ i)
    	all[u] = min(all[u], f[u][i]);
}

signed main()
{
	srand(time(0));
    cin >> N >> R;
    bool flag = false;
    for(unsigned long long i = 1; i < N; ++ i)
    {
        unsigned long long u, v, t;
        cin >> u >> v >> t;
        add(u, v, t);
        add(v, u, t);
        if(!t)
        	flag = true;
    }
	
	ans *= R;
	unsigned long long Root = rand() % N;
    visited[Root] = true;
    dfs1(Root);
    if(R == 1 && flag)
    {
        cout << "0 0";
        return 0;
    }
    else
    {
        cout << ans << ' ';
    }

    memset(visited, 0, sizeof(visited));
    visited[Root] = true;
    dfs2(Root);
    ans = LONG_LONG_MAX;
    for(unsigned long long i = 1; i <= R; ++ i)
        ans = min(ans, f[Root][i]);

    cout << ans << endl;
    return 0;
}
```

# 后言

这里感谢毒瘤出题人！

本题 DP 难度不大，不过需要加点优化，希望每一位读者都能够学好树形 DP（~~以后把我吊打~~）。

---

## 作者：一只书虫仔 (赞：7)

#### Description

> 给定一棵树，每一条边有边权 $t_i$，每一个点有点权 $w_i$，$t_i$ 对应的值决定这条边连接的两个点的值的大小关系（等于，不等于，没有关系），求满足所有 $t_i$ 的关系且 $w_i \in [1,R]$ 的点权赋值情况一共有多少种，并且求出最小的点权和。

注：本文有视频讲解，请在文章最下方查看 qwq。

#### Solution

两问分别考虑，都要考虑树形 dp。

**第一问**

设 $f_{i,j}$ 为以 $i$ 为根节点的子树且 $w_i=j$ 时的答案。

设 $k$ 为 $i$ 的一个儿子，对边 $(i,k)$ 的边权 $t$ 分类讨论：

- $t=0$，$w_i=w_k$ 时情况数就是 $0$，$w_i \ne w_k$ 就可以转移过来，即为：

$$f_{i,j}=f_{i,j} \times \sum\limits_{p=1,p \ne j}^Rf_{k,p}$$

- $t=1$，$w_i$ 可以从任意 $w_k$ 转移过来，即为：

$$f_{i,j}=f_{i,j} \times \sum\limits_{p=1}^Rf_{k,p}$$

- $t=2$，$w_i$ 只能从 $w_k$ 转移过来，即为：

$$f_{i,j}=f_{i,j} \times f_{k,j}$$

答案即为 $\displaystyle \sum\limits_{i=1}^R f_{1,i}$。

**第二问**

设 $f_{i,j}$ 为以 $i$ 为根节点的子树且 $w_i=j$ 时的答案。

设 $k$ 为 $i$ 的一个儿子，对边 $(i,k)$ 的边权 $t$ 分类讨论：

- $t=0$，$w_i=w_k$ 时直接跳过，$w_i \ne w_k$ 时取 $f_{k,w_k}$ 中最小的那一个，即为：

$$f_{i,j}=\min\limits_{p=1,p \ne j}^{R}\{f_{k,p}\}+j$$

- $t=1$，直接取 $f_{k,w_k}$ 中最小的那一个，即为：

$$f_{i,j}=\min\limits_{p=1}^R\{f_{k,p}\}+j$$

- $t=2$，只能从 $f_{k,w_k}$ 转移过来，即为：

$$f_{i,j}=f_{k,j}+j$$

答案即为 $\min\limits_{i=1}^R f_{1,i}$。

**优化**

（思路来自 Euler_Pursuer）

如果按照上面的方法打代码，你会发现最终复杂度为 $\mathcal O(nR^2)$，过不了。

我们尝试把 $\mathcal O(nR^2)$ 优化为 $\mathcal O(nR)$。

操作比较简单，对于第一问，预处理前缀和，对于第二问预处理 $\min$ 的前缀和后缀即可。

**总结**

本题为一道简单的树形 dp，只要想清楚升维就没了。

下面是代码的主要部分，仅供参考（写的很难看）：

```cpp
void dfs1 (int cur, int fa) {
	for (int i = 1; i <= r; i++) dp1[cur][i] = 1ll;
	bool isleaf = false;
	for (int p = head[cur]; p; p = e[p].v) {
		if (e[p].u == fa) continue;
		isleaf = true;
		dfs1(e[p].u, cur);
		int t = e[p].w;
		if (t == 0) {
			for (int i = 1; i <= r; i++) {
				long long sum = s[e[p].u][r];
				sum += Mod;
				sum -= dp1[e[p].u][i];
				sum %= Mod;
				dp1[cur][i] *= sum;
				dp1[cur][i] %= Mod;
			}
		}
		if (t == 1) {
			for (int i = 1; i <= r; i++) {
				dp1[cur][i] *= s[e[p].u][r];
				dp1[cur][i] %= Mod;
			}
		}
		if (t == 2) {
			for (int i = 1; i <= r; i++) {
				dp1[cur][i] *= dp1[e[p].u][i];
				dp1[cur][i] %= Mod;
			}
		}
	}
	if (!isleaf)
		for (int i = 1; i <= r; i++)
			dp1[cur][i] = 1;
	for (int i = 1; i <= r; i++) {
		s[cur][i] = s[cur][i - 1] + dp1[cur][i];
		s[cur][i] %= Mod;
	}
}

void dfs2 (int cur, int fa) {
	for (int i = 1; i <= r; i++) dp2[cur][i] = 1ll * i;
	for (int p = head[cur]; p; p = e[p].v) {
		if (e[p].u == fa) continue;
		dfs2(e[p].u, cur);
		int t = e[p].w;
		if (t == 0) {
			for (int i = 1; i <= r; i++) {
				dp2[cur][i] += min(pre[e[p].u][i - 1], suf[e[p].u][i + 1]);
			}
		}
		if (t == 1) {
			for (int i = 1; i <= r; i++) {
				dp2[cur][i] += pre[e[p].u][r];
			}
		}
		if (t == 2) {
			for (int i = 1; i <= r; i++)
				dp2[cur][i] += dp2[e[p].u][i];
		}
	}
	pre[cur][0] = 0x3f3f3f3f;
	suf[cur][r + 1] = 0x3f3f3f3f;
	for (int i = 1; i <= r; i++) pre[cur][i] = min(pre[cur][i - 1], dp2[cur][i]);
	for (int i = r; i >= 1; i--) suf[cur][i] = min(suf[cur][i + 1], dp2[cur][i]);
}
```

**视频讲解**

您是否觉得文字太过枯燥？本人提供了不知道是否生动有趣的视频讲解 $\downarrow$

![](bilibili:BV1f3411z7CS)

设置在 2021 年 8 月 23 日 17 点 30 分发布，因此可能提前看不到。

---

## 作者：moosssi (赞：4)

第一问，从根节点开始依次遍历每个节点，对于当前点只考虑与父结点的连边情况。

当 $t_i=0$ 时，与父结点不同，赋值的方案则为 $R-1$ 。

当 $t_i=1$ 时，没有要求，赋值的方案则为 $R$ 。

当 $t_i=2$ 时，与父结点相同，赋值的方案则为 $1$ 。

运用乘法原理，每个点的赋值方案之积即为答案，因为每个点都满足了与父结点连边的要求，所以不会冲突。

第二问，树形dp看到范围后很容易想出状态方程，$f[x][i]$ 表示当节点 $x$ 赋值为 $i$ 时，子树内点权和的最小值，接下来考虑转移，遍历整棵树，回溯时从子节点那里来更新答案。

当 $t_i=0$ 时，与子节点不同，$f_{x,i}$ $+=$ $ f_{v,j}$ ，$j$ 与 $i$ 不等，$v$ 是 $x$ 的子节点，如果对于每一个 $i$ 都找一个 $j$ 的话太慢了，我们可以直接找一个最小值和一个次小值，判断一下从哪一个转移而来即可。

当 $t_i=1$ 时，没有要求，从最小值转移而来即可。

当 $t_i=2$ 时，与子结点相同，每一种情况从对应的子节点赋值转移而来即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,mod=1e9+7;
const ll INF=0x3f3f3f3f3f3f3f3f;
int head[N],ver[N*2],net[N*2],edge[N*2],tot;
int n,flag;
ll ans1=1,ans2=INF,f[N][105],R;
void add(int a,int b,int c){
	net[++tot]=head[a];
	head[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
}
void dfs(int x,int fa,int op){
	if(op==1)ans1=(ans1*R)%mod;
	else if(op==0)ans1=(ans1*(R-1))%mod;
	for(int i=head[x];i;i=net[i]){
		int v=ver[i];
		if(v==fa)continue;
		dfs(v,x,edge[i]);
	}
}
void dfs2(int x,int fa){
	for(int i=1;i<=R;i++){
		f[x][i]=i;
	}
	for(int i=head[x];i;i=net[i]){
		int v=ver[i];
		if(v==fa)continue;
		dfs2(v,x);
		if(edge[i]==0){
			ll m1=INF,m2=m1;
			int id=0;
			for(int i=1;i<=R;i++){
				if(f[v][i]<m1){
					m2=m1;
					m1=f[v][i];
					id=i;
				}
				else if(f[v][i]<m2)m2=f[v][i];
			}	
			for(int i=1;i<=R;i++){
				if(i==id)f[x][i]+=m2;
				else f[x][i]+=m1;
			}
		}
		else if(edge[i]==1){
			ll mi=INF;
			for(int i=1;i<=R;i++)mi=min(mi,f[v][i]);
			for(int i=1;i<=R;i++)f[x][i]+=mi;
		}
		else for(int i=1;i<=R;i++)f[x][i]+=f[v][i];		
	}
}
int main(){
	scanf("%d%d",&n,&R);
	for(int i=1;i<n;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
		if(!c)flag=1;
	}
	if(flag&&R==1){
		printf("0 0");
		return 0;
	}
	dfs(1,0,1);
	dfs2(1,0);
	for(int i=1;i<=R;i++){
		ans2=min(ans2,f[1][i]);
	}
	printf("%lld %lld",ans1,ans2);
	return 0;
}
```


---

## 作者：Fan_Tuan (赞：4)

## 题意：
[题面](https://www.luogu.com.cn/problem/P7846)

## 思路：
第一问，
我们首先随便选一个点作为根节点，当前方案数为 $r$，然后从根节点 dfs，对于所到达的 $to$，如果边长为 1，是没有任何限制的，所以它的方案数也是 $r$；如果边长为 0，那么它和它的父亲节点的颜色不同，那么它的方案数为 $r-1$；如果边长为 2，那么它必须和它父亲颜色相同，那么它的方案数为 1。最后根据乘法原理将所有节点乘起来就是总的方案数。

第二问是一个简单树形dp。

设 $dp_{i,j}$ 表示第 $i$ 个点染第 $j$ 种颜色时所能获得的最小值，开始我们初始化 dp_{i,j} 的值为 $j$。

由于 $r$ 的值很小，我们可以直接枚举给 $u$ 染色。

如果边的值为 1，则 $dp_{u, i} = \min dp_{to, j} + dp_{u,i}$。

如果边的值为 0，我们只需要存一个 $dp_{to,j}$ 的最小值 $x$ 和次小值 $y$，如果 $u$ 的染色和 $to$ 的最优染色一样的话 $dp_{u,i} = dp_{u,i} + y$，否则 $dp_{u,i} = dp_{u,i} + x$。

如果边的值为 2，那么 $dp_{u,i} = dp_{u,i} + dp_{to,i}$。

如果以 1 为根节点的话，最后答案就是 $\min dp_{1,i}$。

## 代码：
```cpp
#include <cstring>
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <string>
#define int long long
using namespace std;

inline int read() {
    int f = 0, s = 0;
    char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
    return f ? -s : s;
}

void print (int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print (x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 2e5 + 10, mod = 1e9 + 7;
int n, r, head[maxn], num, a[maxn], s, ans, vis[maxn], sum, dp[maxn][105];

struct node {
    int nex, to, w;
}edge[maxn];

void add(int from, int to, int w) {
    edge[++num].nex = head[from];
    edge[num].to = to;
    edge[num].w = w;
    head[from] = num;
}

void dfs(int u) {
    for (int i = head[u]; i; i = edge[i].nex) {
        int to = edge[i].to;
        int w = edge[i].w;
        if (vis[to]) continue;
        vis[to] = 1;
        int x;
        if (w == 0) x = r - 1;
        if (w == 1) x = r;
        if (w == 2) x = 1;
        ans = ans * x % mod;
        dfs(to);
    }
}

void dfs2(int u) {
    for (int i = 1; i <= r; i++) dp[u][i] = i; 
    for (int i = head[u]; i; i = edge[i].nex) {
        int to = edge[i].to;
        int w = edge[i].w;
        if (vis[to]) continue;
        vis[to] = 1;
        dfs2(to);
        if (w == 1) {
            int x = 1000000000000;
            for (int i = 1; i <= r; i++) 
                x = min(x, dp[to][i]);
            for (int i = 1; i <= r; i++) 
                dp[u][i] += x;
        }
        if (w == 2) {
            for (int i = 1; i <= r; i++)
                dp[u][i] += dp[to][i];
        }
        if (w == 0) {
                int x = 1000000000000, id;
                int y = x, tot = 1;
                for (int j = 1; j <= r; j++) {
                    if (x == dp[to][j]) tot++;
                    if (x > dp[to][j]) {
                        y = min(y, x);
                        x = dp[to][j];
                        id = j;
                        tot = 1;
                    }
                    if (y > dp[to][j] && dp[to][j] != x) {
                        y = dp[to][j];
                    }
                }
            for (int j = 1; j <= r; j++) {
                if (id == j) {
                    if (tot == 1)
                        dp[u][j] += y;
                    else dp[u][j] += x;
                } 
                else dp[u][j] += x;
            }
        }
    }
}

signed main () {
    n = read(), r = read();
    s = 1;
    for (int i = 2; i <= n; i++) {
        int u, v, w;
        u = read(), v = read(), w = read();
        add(u, v, w);
        add(v, u, w);
        if (w == 0) s = u;
    }
    vis[1] = 1;
    a[1] = r, ans = r;
    dfs(1);
    if (ans == 0) {
        cout << "0 0";
        return 0;
    }
    memset(vis, 0, sizeof vis);
    vis[1] = 1;
    dfs2(1);
    cout << ans << " ";
    ans = 1000000000000;
    for (int i = 1; i <= r; i++) ans = min(ans, dp[1][i]);
    cout << ans;
    return 0;
}
```

---

## 作者：Harry27182 (赞：3)

~~话说这题为什么是绿啊，个人感觉应该有蓝...~~
### 简要题意

给定一棵树，每一条边有边权 $t_i$ ，每一个点有点权 $w_i$，$t_i$ 对应的值决定这条边连接的两个点的值的大小关系（等于，不等于，没有关系），求满足所有 $t_i$ 的关系且 $w_i \in [1,R]$ 的点权赋值情况一共有多少种，并且求出最小的点权和。
### 具体思路

提供一种与题解略有不同的做法吧，对于 $t_i=2$ 的情况，可以考虑使用并查集维护相等关系，然后把所有相等的缩成一个点，然后在新图上建边。这样的话时间上常数会小一点，因为点数 $n$ 已经缩小了，实测跑了 std 的一半时间。

然后就是考虑树形 dp ，这里注意，这题树形 dp 与其他题不同，需要考虑升维，设 $f[i][j]$ 表示以 i 节点为根的子树上， i 节点权值为 j 的方案数, $g[i][j]$ 表示以 i 节点为根的子树上， i 节点权值为 j 的最小权值。两问都考虑分类讨论，由于 $t_i=2$ 的情况已经处理过了，所以就考虑剩下两种情况。

- $t[i]=0$：$f[i][j]$ 只能从 $f[k][l](l!=j)$ 转移过来$(k\in son[i])$。

- $t[i]=1$：$f[i][j]$ 可以从 $f[k][l]$ 转移过来$(k\in son[i])$。

根据题意可以得到下面的转移方程式：


#### 第一问：
- $t[i]=0$：$f_{i,j}=f_{i,j}\times ∑f_{k,l}(l \in [1,r],l!=j)$
- $t[i]=1$：$f_{i,j}=f_{i,j}\times ∑f_{k,l}(l \in [1,r])$

#### 第二问：
- $t[i]=0$：$f_{i,j}=min{f_{k,l}}+num_i \times j(l \in [1,r],l!=j)$
- $t[i]=1$：$f_{i,j}=min{f_{k,l}}+num_i \times j(l \in [1,r])$

注意细节即可。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
#define mod 1000000007
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
struct edge
{
	int v,w,next;
}e[200005];
int fa[100005],h[100005],f[100005][105],g[100005][105],num[100005];
int u[100005],v[100005],t[100005],cnt,n,r,ans1,ans2=inf;
int find(int x)
{
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
void add(int u,int v,int w)
{
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].next=h[u];
	h[u]=cnt;
}
void dfs1(int u,int fa)
{
	for(int i=h[u];i;i=e[i].next)
	{
		int v=e[i].v,sum=0;
		if(v==fa)continue;
		dfs1(v,u);
		for(int j=1;j<=r;j++)sum=(sum+f[v][j])%mod;
		if(e[i].w==1){for(int j=1;j<=r;j++)f[u][j]=(f[u][j]*sum)%mod;}
		else {for(int j=1;j<=r;j++)f[u][j]=(f[u][j]*((sum-f[v][j]+mod)%mod))%mod;}//不要忘记+mod
	}
}
void dfs2(int u,int fa)
{
	for(int j=1;j<=r;j++)g[u][j]=j*num[u];
	for(int i=h[u];i;i=e[i].next)
	{
		int v=e[i].v,min1=inf,min2=inf;
		if(v==fa)continue;
		dfs2(v,u);
		for(int j=1;j<=r;j++)
		{
			if(g[v][j]<min1)
			{
				min2=min1;
				min1=g[v][j];
			}
			else if(g[v][j]<min2)min2=g[v][j];
		}
		if(e[i].w==1){for(int j=1;j<=r;j++)g[u][j]+=min1;}
		else {for(int j=1;j<=r;j++)g[u][j]+=(g[v][j]==min1)?min2:min1;}
	} 
}
signed main()
{
	scanf("%lld%lld",&n,&r);
	for(int i=1;i<=n;i++)fa[i]=i,num[i]=1;
	for(int i=1;i<n;i++)
	{
		scanf("%lld%lld%lld",&u[i],&v[i],&t[i]);
		if(t[i]==2)
		{
			int fu=find(u[i]),fv=find(v[i]);
			fa[fu]=fv;
			num[fv]+=num[fu];
		}
	}
	for(int i=1;i<n;i++)
	{
		if(t[i]==2)continue;
		add(find(u[i]),find(v[i]),t[i]);//加边为 find(u[i]),find(v[i])，不是 fa[u[i]],fa[v[i]]
		add(find(v[i]),find(u[i]),t[i]);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=r;j++)f[i][j]=1;//注意初始化
	}
	for(int i=1;i<=n;i++)
	{
		if(fa[i]==i)
		{
			dfs1(i,0);
			dfs2(i,0);
			for(int j=1;j<=r;j++)
			{
				ans1=(ans1+f[i][j])%mod;//注意取模
				ans2=min(ans2,g[i][j]);
			}
			printf("%lld %lld",ans1,(ans1==0)?0:ans2);
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：信息向阳花木 (赞：2)

很水的树形 dp，但要注意特判，我没特判卡在 $95$ 好久。

设 $f_{i,j}$ 表示 $w_i = j$ 时的方案数，$m_{i,j}$ 表示 $w_i = j$ 时 $\sum_{i=1}^{n}w_i$ 的最小值。

对于 $f_{u,j}$，我们可以由子节点 $v$ 的状态，推出。

* 当 $t = 0$ 时，$w_u ≠ w_v$，$f_{u,j} = f_{u,j} \times (\sum_{i = 1}^{R}f_{v,i} - f_{v,j})$。
* 当 $t = 1$ 时，$w_u$ 没有任何要求，$f_{u,j} = f_{u,j} \times (\sum_{i = 1}^{R}f_{v,i})$。
* 当 $t = 2$ 时，$w_u = w_v$，$f_{u,j} = f_{u,j} \times f_{v,j}$。

对于 $m_{u,j}$，$m_{u,j} = j + \min_{i = 1}^{R}m_{v, i}$。当 $t = 0$ 时，可能 $m_{v,j}$ 为最小值，这样使得 $w_u = w_v$。所以我们还得记录次小值，当 $t = 0$ 时特判。

时间复杂度 $O(nm)$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 200010, mod = 1000000007;

typedef long long LL;

void in(int &x)
{
	x = 0;
	bool f = 0;
	char c = getchar();
	
	while (c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + (c - '0');
		c = getchar();
	}
	if(f) x = -x;
	return;
}

int n, m;
int h[N], e[N], ne[N], t[N], idx;
LL f[N][110], minn[N][110];

inline void add(int a, int b, int c)
{
	e[idx] = b, ne[idx] = h[a], t[idx] = c, h[a] = idx ++;
	return;
}

void dfs(int u, int fa)
{
	for (int i = h[u]; ~i; i = ne[i])
	{
		int v = e[i];
		if(v == fa) continue;
		
		dfs(v, u);
		LL s = 0, mn1 = 1e18, mn2 = 1e18;
		for (int j = 1; j <= m; j ++ )
		{
			s = (s + f[v][j]) % mod;
			if(minn[v][j] <= mn1)
			{
				mn2 = mn1;
				mn1 = minn[v][j];
			}
			else if(minn[v][j] < mn2) mn2 = minn[v][j];
		}
		for (int j = 1; j <= m; j ++ )
		{
			if(t[i] == 0)
			{
				f[u][j] = f[u][j] * (((s - f[v][j]) % mod + mod) % mod) % mod;
				if(mn1 == minn[v][j]) minn[u][j] += mn2;
				else minn[u][j] += mn1;
			}
			else if(t[i] == 1)
			{
				f[u][j] = f[u][j] * s % mod;
				minn[u][j] += mn1;
			}
			else
			{
				f[u][j] = f[u][j] * f[v][j] % mod;
				minn[u][j] += minn[v][j];
			}
		}
	}
	return;
}

int main()
{
	memset(h, -1, sizeof h);
	
	in(n); in(m);
	
	bool flag = 0;
	for (int i = 1; i < n; i ++ )
	{
		int a, b, c;
		in(a); in(b); in(c);
		add(a, b, c); add(b, a, c);
		if(c == 0) flag = 1;
	}
	
	if(flag && m == 1) { puts("0 0"); return 0; }
	//没有上面的特判只有 95！！
    
	for (int i = 1; i <= n; i ++ )
		for(int j = 1; j <= m; j ++ )
			f[i][j] = 1, minn[i][j] = j;
	dfs(1, 0);
	
	LL res = 0, mn = 1e18;
	for (int i = 1; i <= m; i ++ )
	{
		res = (res + f[1][i]) % mod;
		mn = min(mn, minn[1][i]);
	}
	if(res == 0) puts("0 0");
	else printf("%lld %lld\n", res, mn);
	
	return 0;
}
```

---

## 作者：许多 (赞：2)

# 题目分析

~~第一问和第二问不能说关系不大，只能说毫无关联~~，所以我们选择分开考虑。

考虑到 $t_i$ 为 $1$ 时两边点的点权没有要求，我们可以**将后查询的节点当做新的根**。重新 dfs。

# 正解

我们将 $1$ 看做根节点，跑一遍 dfs 将节点的父节点记录下来。~~没错，只有这一件事~~。

```cpp
void dfs(int now,int f){
    fa[now]=f;
    for(int i=0;i<b[now].size();i++)
        if(b[now][i]!=f)
                dfs(b[now][i],now);
        
    return ;
}
```
## 第一问

我们用队列存储每一个根，每找到一条边的边权为 $1$ 就把它下面连接的节点加入队列。我们设一个变量 $g$ 存储有多少**种可以不同的点权**,对于边权为 $0$ 的边，我们就使 $g+1$，**注意，当 $t_i$ 为 $2$ 时，我们不做任何处理**。利用乘法原理，我们能得到答案为 $R(R-1)^{sum-1}$。

### dfs 代码

```cpp
void dfs2(int now){
    for(int i=0;i<b[now].size();i++)
        if(b[now][i]!=fa[now]){
            if(b1[now][i]==0)
                g++,dfs2(b[now][i]);
            if(b1[now][i]==1)
                q.push(b[now][i]);
            if(b1[now][i]==2)
                dfs2(b[now][i]);
        }
    return ;
}
```

### 队列加答案处理代码

```cpp
q.push(1);
    while(q.size()){
        g=1;
        int now=q.front();q.pop();
        dfs2(now);
        sum=(sum*R)%mod;//记得乘上上次答案
        for(int i=1;i<g;i++)sum=sum*(R-1)%mod;
    }   
```
## 第二问

基本就是一个裸的树形 DP。我们用 $f[i][j]$ 表示当节点 $i$ 的点权为 $j$ 时，这颗子树最小的点权和。

### DP 代码

```cpp
long long f[N][200];
void dp(int now){
    for(int i=0;i<b[now].size();i++)
        if(b[now][i]!=fa[now])
            dp(b[now][i]);
    for(int i=1;i<=R;i++){
        f[now][i]=i;
        for(int k=0;k<b[now].size();k++)
            if(b[now][k]!=fa[now]){
                long long m=10000000;
                if(b1[now][k]==0)
                    for(int j=1;j<=R;j++)
                        if(i!=j)
                            m=min(m,f[b[now][k]][j]);
                if(b1[now][k]==1)
                    for(int j=1;j<=R;j++)
                        m=min(m,f[b[now][k]][j]);
                if(b1[now][k]==2)
                    m=f[b[now][k]][i];
                if(m!=10000000)f[now][i]+=m;
            }
    }
    return ;
}
```

我们来简单讲一下，只填 $1$ 或 $2$ 为什么不是最小值。
![](https://cdn.luogu.com.cn/upload/image_hosting/xtbciadi.png)

假设这上面的边权都是 $0$，如果只填 $1$ 或 $2$，那么第二行点的点权或最后一行点的点权必定有一个是 $1$，一个是 $2$。而如果我们将中间两行的点的点权改成一个是 $2$，一个是 $3$，则第二行点的点权和最后一行点的点权都是 $1$。


# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 200000
#define mod 1000000007
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
using namespace std;
int n,R,fa[N],g;
vector<int>b[N];
vector<int>b1[N];
long long sum=1,Min=100000000000000000;
queue<int>q;
void dfs(int now,int f){
    fa[now]=f;
    for(int i=0;i<b[now].size();i++)
        if(b[now][i]!=f)
                dfs(b[now][i],now);
        
    return ;
}
void dfs2(int now){
    for(int i=0;i<b[now].size();i++)
        if(b[now][i]!=fa[now]){
            if(b1[now][i]==0)
                g++,dfs2(b[now][i]);
            if(b1[now][i]==1)
                q.push(b[now][i]);
            if(b1[now][i]==2)
                dfs2(b[now][i]);
        }
    return ;
}
long long f[N][200];
void dp(int now){
    for(int i=0;i<b[now].size();i++)
        if(b[now][i]!=fa[now])
            dp(b[now][i]);
    for(int i=1;i<=R;i++){
        f[now][i]=i;
        for(int k=0;k<b[now].size();k++)
            if(b[now][k]!=fa[now]){
                long long m=10000000;
                if(b1[now][k]==0)
                    for(int j=1;j<=R;j++)
                        if(i!=j)
                            m=min(m,f[b[now][k]][j]);
                if(b1[now][k]==1)
                    for(int j=1;j<=R;j++)
                        m=min(m,f[b[now][k]][j]);
                if(b1[now][k]==2)
                    m=f[b[now][k]][i];
                if(m!=10000000)f[now][i]+=m;
            }
    }
    return ;
}
int main(){
    n=read();R=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),t=read();
        b[u].push_back(v);b1[u].push_back(t);
        b[v].push_back(u);b1[v].push_back(t);
    }
    dfs(1,1);
    q.push(1);
    while(q.size()){
        g=1;
        int now=q.front();q.pop();
        dfs2(now);
        sum=(sum*R)%mod;
        for(int i=1;i<g;i++)sum=sum*(R-1)%mod;
    }   
    if(sum==0)cout<<"0 0";
    else {
        dp(1);
        for(int i=1;i<=R;i++)if(f[1][i]<Min)Min=f[1][i];
        cout<<sum<<" "<<Min;
    }
    return 0;
}
```





---

## 作者：kbtyyds (赞：2)

# P7846 题解

建议在[博客](https://www.luogu.com.cn/blog/453059/solution-p7846)里食用：

[题目链接](https://www.luogu.com.cn/problem/P7846)

---

## 题目描述

- 有一棵 $n$ 个点的树，第 $i$ 个点有点权 $w_i$，第 $j$ 条边有边权 $t_j$；
- 每一条边 $(u_j,v_j,t_j)$ 两边点的点权有如下要求：
	- $t_j=0$，$w_{u_j} \ne w_{v_j}$；
    - $t_j=1$，没有要求；
    - $t_j=2$，$w_{u_j}=w_{v_j}$；
    - 对任意点权都要有 $w_i \in [1,R]$；
- 求当 $w_i$ 作为序列时，一共有多少种本质不同的序列 $w_i$ 以及 $w_i$ 的和的最小值。

## 前置知识/算法：

树形 dp，常见优化技巧。

## 分析

很明显这两个问题没什么关系，于是我们分开计算。

### $\rm Problem\ 1$

记 $f[u][i]$ 为 $w_u$ 的值为 $i$ 时，$u$ 子树的序列方案数。

那么我们根据 $t_j$ 简单讨论一下便可以得到方程：

$$f[u][i]=\prod_{v\in Son_u}\begin{cases}\sum\limits_{j=1}^R[i\ne j]f[v][j]&t_j=0\\\sum\limits_{j=1}^R f[v][j]&t_j=1\\f[v][i]&t_j=2\end{cases}$$

时间复杂度：$\mathcal O(nR^2)$，显然还差一点通过。

#### 优化

枚举 $u$ 和 $i$ 的复杂度消不掉，那就把 $\sum$ 的一层消掉！

我们记 $f[u][0]=\sum\limits_{i=1}^R f[u][i]$，那么转移方程变为：

$$f[u][i]=\prod_{v\in Son_u}\begin{cases}f[v][0]-f[v][j]&t_j=0\\f[v][0]&t_j=1\\f[v][i]&t_j=2\end{cases}$$

注意到我们把 $[i\ne j]$ 的限制条件巧妙地化为了减法，刚好把 $[i=j]$ 的部分减去，符合题意。

时间复杂度 $\mathcal O(nR)$，可以通过。

输出答案为 $f[\mathrm{rt}][0]$，其中 $\rm rt$ 是根节点。

---

### $\rm Problem\ 2$

状态与 $\rm Problem\ 1$ 类似，记 $g[u][i]$ 为 $w_u$ 的值为 $i$ 时，子树 $u$ 的权值和的最小值。

同样得到方程：

$$g[u][i]=\sum_{v\in Son_u}\begin{cases}\min\limits_{j=1}^R [i\ne j] g[v][j]&t_j=0\\\min\limits_{j=1}^R g[v][j]&t_j=1\\g[v][i]&t_j=2\end{cases}$$

同样，时间复杂度 $\mathcal O(nR^2)$，也要尝试消掉 $\min$ 的复杂度。

先让 $g[u][0]=\min\limits_{i=1}^R g[u][i]$。

但是，取 $\min$ 不像加法一样有逆运算，于是我们得改变思路。

我们可以维护前缀 $\min$ 以及后缀 $\min$，查询时裂开区间即可。

即：

$$\mathrm{pre}[u][i]=\min_{j=1}^i g[u][j]\\\mathrm{nxt}[u][i]=\min_{j=i}^R g[u][j]$$

方程：

$$g[u][i]=\sum_{v\in Son_u}\begin{cases}\min(\mathrm{pre}[v][i-1],\mathrm{nxt}[v][i+1])&t_j=0\\g[v][0]&t_j=1\\g[v][i]&t_j=2\end{cases}$$

时间复杂度 $\mathcal O(nR)$。

输出答案为 $g[\mathrm{rt}][0]$（如果有解），其中 $\rm rt$ 是根节点。

## 代码

[Link](https://www.luogu.com.cn/paste/eyp8v03i)

---

## 作者：Farkas_W (赞：2)

$\quad$可以发现第一问和第二问并无关联，所以可以分开讨论。

### 第一问

$\quad$显然是树形DP，可以从上向下DP，$f_i$ 表示 $i$ 号结点可能的方案数，$son_i$ 为 $i$ 号结点的儿子数,设 $j$ 为i的一个儿子，$val_{i,j}$ 为 $i,j$ 连边的关系($t$)。

$\quad$可得：

$$ \left\{
\begin{aligned}
& f_{root}= R\\
& f_j= & R-1(val_{i,j}=0)\\
& f_j= & R(val_{i,j}=1)\\
& f_j= & 1(val_{i,j}=2)
\end{aligned}
\right.
$$

$\quad$最终答案就是 $\prod\limits_{i=1}^{n}f[i]$。

### 第二问

$\quad$同样是树形DP，但是是从下向上传递答案，设 $g_{i,j}$ 为 $i$ 号结点取 $j$ 时子树的最小值，R并不大，所以可以逐一枚举。(经测试，枚举到13即可)

$\quad$可得：(设 $p_{i,0}$ 为 $g_{i,j}$中的最小值， $p_{i,1}$ 为次小值， $v$ 为 $i$ 的一个儿子)

$$g_{i,j}=j$$
$$ \left\{
\begin{aligned}
& g_{i,j}+= p_{v,0} (val_{i,v}=0,p_{v,1}>=g_{v,j})\\
& g_{i,j}+= p_{v,1} (val_{i,v}=0,p_{v,1}<g_{v,j})\\
& g_{i,j}+= p_{v,0} (val_{i,v}=1)\\
& g_{i,j}+= g_{v,j}(val_{i,v}=2)
\end{aligned}
\right.
$$

$\quad$最后的答案就是 $p_{root,0}$。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<time.h>
#define int long long
#define re register int
#define il inline
using namespace std;
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
il int min(int x,int y){return x<y?x:y;}
const int N=1e5+5,MOD=1e9+7,inf=0x3f3f3f3f;
int n,R,p,rt,tot,ans=1,head[N],nxt[N<<1],val[N<<1],go[N<<1],f[N],g[N][15];
il void Add(int x,int y,int z)
{
	nxt[++tot]=head[x];
	head[x]=tot;go[tot]=y;val[tot]=z;
}
il void dfs(int x,int fa,int h)//g[i][0]表示最小值，g[i][14]表示次小值
{
	for(re i=1;i<=p;i++)g[x][i]=i;//初始的代价
	if(h==1)f[x]=R;else if(h==2)f[x]=1;else f[x]=R-1;//第一问
	for(re i=head[x],y;i,y=go[i];i=nxt[i])
	if(y!=fa){
		dfs(y,x,val[i]);
		for(re j=1;j<=p;j++)
		if(val[i]==1)g[x][j]+=g[y][0];
		else if(val[i]==2)g[x][j]+=g[y][j];
		else {
			if(g[y][j]>=g[y][14])g[x][j]+=g[y][0];
			else g[x][j]+=g[y][14];
		}
	}
	g[x][0]=g[x][14]=inf;
	for(re i=1;i<=p;i++)//更新最小值和次小值
	{
		if(g[x][i]<g[x][0])g[x][14]=g[x][0],g[x][0]=g[x][i];
		else if(g[x][i]==g[x][0])g[x][14]=g[x][i];
		else if(g[x][i]<g[x][14])g[x][14]=g[x][i];
	}
}
signed main()
{
	n=read();R=read();srand(time(0));rt=rand()%n+1;p=min(R,13);//随机的根不容易被卡
	for(re i=1,x,y,z;i<n;i++)x=read(),y=read(),z=read(),Add(x,y,z),Add(y,x,z);
	dfs(rt,0,1);
	for(re i=1;i<=n;i++)ans=(ans*f[i])%MOD;//记得要取模
	print(ans);putchar(' ');if(ans==0){putchar('0');return 0;}
	print(g[rt][0]);
	return 0;
}
```
$$\texttt{后记}$$

$\quad$一开始以为只填1或2就是最小值，然而只有30分，至今不知道为什么？

$\quad$这里有[一组数据](https://www.luogu.com.cn/paste/ucc7cq5h)，有大佬可以解释吗？

---

## 作者：slzx2022YuYihan (赞：1)

[P7846 「dWoi R2」Arcade hall / 街机厅](https://www.luogu.com.cn/problem/P7846)

# Solution

一道比较水的树形 dp，却因为边界赋值而调了半个小时。

首先来计算方案数。

*	如果 $w=0$，此时有 $R-1$ 种选择方案。
*	如果 $w=1$，此时有 $R$ 种选择方案。
*	如果 $w=2$，此时有 $\mathbb 1$ 种方案。

总方案数就把他们乘起来。如果方案数为 $\mathbb 0$，那么输出两个 $\mathbb 0$，以免后面出现 ggguaiguai 的错误。

接下来计算方案中的最小值。设 $f_{i,j}$ 表示当前第 $i$ 个节点取 $j$ 这个值时这棵子树的最小值。

*	如果 $w=0$，$f_{i,j}=\sum_{v\in u,k\ne j}\min{f_{v,k}}+j$
*	如果 $w=1$，$f_{i,j}=\sum_{v\in u}\min{f_{v,k}}+j$
*	如果 $w=2$，$f_{i,j}=\sum_{v\in u}f_{v,j}+j$

这时的总复杂度为 $O(nR^2)$，我们对其进行如下优化。

令 $pre_{i,j}$ 表示 $\min_{k=1}^{j}f_{i,k}$，$suf_{i,j}$ 表示 $\min_{k=j}^{r}f_{i,k}$，$mi_i$ 表示 $\min_{j=1}^{r}f_{i,j}$，那么转移如下：

*	如果 $w=0$，$f_{i,j}=\sum_{v\in u}\min(pre_{v,j-1},suf_{v,j+1})+j$
*	如果 $w=1$，$f_{i,j}=\sum_{v\in u}mi_v+j$
*	如果 $w=2$，$f_{i,j}=\sum_{v\in u}f_{v,j}+j$

此时复杂度就降为 $O(nR)$，注意边界值的处理。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>inline void read(T& x){
    x = 0; T w = 1; char ch = getchar();
    while (!isdigit(ch)){if (ch == '-')	w = -1; ch = getchar();}
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x *= w;
}
template<typename T>inline void write(T x){
    if (x < 0)	putchar('-'), x = ~(x - 1);
    if (x > 9)	write(x / 10);
    putchar(x % 10 ^ 48);
}

const int N = 1e5 + 5;

const int R = 105;

const ll mo = 1e9 + 7;

int n, r;

int num, h[N], to[N << 1], edge[N << 1], nxt[N << 1];
void addedge(int u, int v, int w){
    to[++num] = v, edge[num] = w, nxt[num] = h[u], h[u] = num;
}

int f[N][R];
bool flag;
ll ans;
int anss;
void dfs1(int u, int pre){
    for (register int i = h[u]; i; i = nxt[i]){
        int v = to[i], w = edge[i];
        if (v == pre)   continue;
        if (!w) ans = ans * (r - 1) % mo, flag |= (r == 1);
        else    if (w == 1) ans = ans * r % mo;
        dfs1(v, u);
    }
}
int previ[N][R], suf[N][R], mi[N];
void dfs2(int u, int pre){
    for (register int i = 1; i <= r; ++i)
        f[u][i] = i;
    for (register int i = h[u]; i; i = nxt[i]){
        int v = to[i], w = edge[i];
        if (v == pre)   continue;
        dfs2(v, u);
        if (!w){
            for (register int j = 1; j <= r; ++j)
                f[u][j] += min(previ[v][j - 1], suf[v][j + 1]);
        }
        else    if (w == 1){
            for (register int j = 1; j <= r; ++j)
                f[u][j] += mi[v];
        }
        else{
            for (register int j = 1; j <= r; ++j)
                f[u][j] += f[v][j];
        }
    }
    previ[u][0] = 0x3f3f3f3f;
    for (register int i = 1; i <= r; ++i)
        previ[u][i] = min(previ[u][i - 1], f[u][i]);
    suf[u][r + 1] = 0x3f3f3f3f;
    for (register int i = r; i; --i)
        suf[u][i] = min(suf[u][i + 1], f[u][i]);
    mi[u] = 0x3f3f3f3f;
    for (register int i = 1; i <= r; ++i)
        mi[u] = min(mi[u], f[u][i]);
}

int main(){
    //ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    read(n), read(r);
    for (int i = 1, u, v, w; i < n; ++i){
        read(u), read(v), read(w);
        addedge(u, v, w), addedge(v, u, w);
    }
    ans = r, dfs1(1, 0);
    if (flag)    return puts("0 0"), 0;
    write(ans), putchar(' ');
    dfs2(1, 0);
    anss = 0x3f3f3f3f;
    for (register int i = 1; i <= r; ++i)   anss = min(anss, f[1][i]);
    return write(anss), putchar('\n'), 0;
}
```

---

## 作者：_lqs_ (赞：1)

这道题我不知道怎么评价，调了我一天，结果是数组开小了......

# solution

- 这道题有两个问，分别求组合的总方案数和最小情况。以下记 $m$ 为题目中的 $R$。

### Q1

- 对于第一个问题，先引入一个小背景：需要构造一个序列，要求相邻两个数不能相同，求可能的方案数，设序列长度为 $n$，值域为 $m$。

- 这是很经典的排列组合的问题（不知道算不算），序列的第一个数肯定是有 $m$ 个选择，因为第二个数要和第一个数不同，所以第二个数有 $m-1$ 个选择，第三个也是有 $m-1$ 个选择......以此类推（感性理解一下）。把序列每个位置可选择的方案数用数组 $a$ 存下，则 $a_{1}=m$，其余为 $m-1$。设答案为 $ans$，则有以下式子：
$$ans=\prod\limits_{i=1}^na_{i}$$

- 这个弄懂之后第一问也就迎刃而解了，读懂题目其实就会发现跟这个没什么区别。其中，$t_{i}=0$ 时就是刚刚那个问题，答案乘上 $r-1$ 即可； $t_{i}=1$ 时没有限制，那么也是有 $r$ 个选择，答案乘上 $r$ 即可；$t_{i}=2$ 时要求相同，也就是被上一个选择限制了，也可以理解为选择数为 $0$，答案乘上 $1$ 就行。

- 这个问题的实现把整颗树遍历一遍，判断边权即可。

### code

```cpp
void dfs(int a,int la){//la是a的父亲节点
	if(a==1) f[a]=m; //根节点没有限制直接赋值为m 
	for(int i=h[a];i;i=d[i].n){
		int b=d[i].b,c=d[i].c;
		if(b!=la){//防止重复遍历
			dfs(b,a);
			if(c==0) f[b]=m-1;
			if(c==1) f[b]=m;
			if(c==2) f[b]=1;//这里也可以选择直接乘
		}
	}
}//这里的代码只是把每个位置的选择存了下来，所以最后要遍历一次f数组乘起来
```

### Q2

- 第二个问题就是标准的树形 dp 啦，定义数组 $f1_{i,j}$ 表示 $i$ 节点点权选 $j$ 的最小总和。

- 显然，$f1_{i,j}$ 的值与 $i$ 的儿子节点有关系，即由叶子结点向根传递，定义 $i$ 点的某个儿子节点为 $b$。

1. 当 $t_{i}=0$ 时，要求是选的值不能相同，那么枚举每种可能的值，即枚举 $f1_{i,j}$ 中的 $j$，在 $i$ 节点的每个儿子节点中找出所有 $f1_{b,p}(j \ne p)$，取出最小值，累加进 $f1_{i,j}$ 即可。

1. 当 $t_{i}=1$ 时，没有限制，那么在每个儿子节点中找出 $\min \{f1_{b,p}\}(1 \le p \le m)$ 累加即可。

1. 当 $t_{i}=2$ 时，要求值相同，那么直接把 $f1_{b,j}$ 的值直接累加进 $f1_{i,j}$ 中即可。

- 最后别忘了每个状态都要加上自己的值。

### code

```cpp
void check(int a,int la){
	for(int i=1;i<=m;i++) f1[a][i]=i;//先加上自己的值
	for(int i=h[a];i;i=d[i].n){
		int b=d[i].b,c=d[i].c;
		if(b!=la){
			check(b,a);
			if(c==0){
				for(int j=1;j<=m;j++){
					int sum=1e9;
					for(int p=1;p<=m;p++){
						if(j==p) continue;//不选相同的
						sum=min(sum,f1[b][p]);
					}
					f1[a][j]+=sum;
				}
			}
			if(c==1){
				for(int j=1;j<=m;j++){
					int sum=1e9;
					for(int p=1;p<=m;p++){
						sum=min(sum,f1[b][p]);//任意最小值
					}
					f1[a][j]+=sum;
				}
			}
			if(c==2){
				
				for(int j=1;j<=m;j++){
					f1[a][j]+=f1[b][j];//只能选相同的
				}
			}
		}
	}
}
```

- 但是以上代码的最坏复杂度是 $\mathcal {O}(nR^2)$，必然超时，因此考虑对 $t_{i}=0$ 及 $t_{i}=1$ 的情况进行优化（~~当然你也可以选择吸氧直接过~~）。

- 先看 $t_{i}=1$ 的情况，仔细观察就会发现每次遍历都是一样的内容，和遍历一次没有区别，因此一次遍历就将最小值存下，再循环赋值。

- 思考一下就会发现若按照 $t_{i}=1$ 的情况先找最小值，其实在 $t_{i}=0$ 时整个值域中只有一个状态不会累加进最小值，其余都会累加进，所以我们再记录个次小值给这个不累加最小值的状态即可。

### code

```cpp
void check(int a,int la){
	for(int i=1;i<=m;i++) f1[a][i]=i;
	for(int i=h[a];i;i=d[i].n){
		int b=d[i].b,c=d[i].c;
		if(b!=la){
			check(b,a);
			if(c==0){
				int sum1=1e18,sum2,w1,w2;//sum1是最小值，sum2是次小值，w1记录最小值的下标，w2记录次小值的下标
				for(int j=1;j<=m;j++){
					if(f1[b][j]<sum1){
						w2=w1,w1=j;
						sum2=sum1;
						sum1=f1[b][j];
					}
					else if(f1[b][j]<sum2) sum2=f1[b][j],w2=j;
				}
				for(int j=1;j<=m;j++){
					if(j!=w1) f1[a][j]+=sum1;
					else f1[a][j]+=sum2;
				}
			}
			if(c==1){
				int sum=1e18;
				for(int j=1;j<=m;j++){
					sum=min(sum,f1[b][j]);
				}//这里一次遍历找最小值
				for(int j=1;j<=m;j++){
					f1[a][j]+=sum;
				}
			}
			if(c==2){
				for(int j=1;j<=m;j++){
					f1[a][j]+=f1[b][j];
				}
			}
		}
	}
}
```
- 整个代码复杂度为 $\mathcal {O}(nR)$，全部代码就不给了，可能是昨晚做了 [P4084](https://www.luogu.com.cn/problem/P4084) 的原因，思考时一直是以 $R=3$ 的例子想的，搞得我写代码 $f1$ 数组第二维只开了 $5$，这点小问题调了一天（[做题记录](https://www.luogu.com.cn/record/list?pid=P7846&user=664744&page=1)）。

---

## 作者：yhylivedream (赞：0)

# 第一问

- 如果 $t_i=0$ 那么子节点不能选父节点的值，贡献为 $R-1$。

- 如果 $t_i=1$ 那么子节点随便选，贡献为 $R$。

- 如果 $t_i=2$ 那么子节点只能选父节点的值，贡献为 $1$。

将根节点的贡献和非根节点的贡献相乘即为答案。

注意如果可选的值只有一种即 $R=1$ 且存在 $t_i=1$ 则无解。

# 第二问

树形 dp，设状态 $f_{i,j}$ 表示点 $i$ 选的数为 $j$， 以 $i$ 为根的子树的 $w_i$ 之和最小值。

## 转移方程

记 $x$ 为点 $i$ 的子节点，$t$ 为边 $(i,x)$ 的权值。

- 如果 $t=0$，则转移方程为 $f_{i,j}=f_{i,j}+\min_{k=1,k\neq j}^R f_{x,k}$。

- 如果 $t=1$，则转移方程为 $f_{i,j}=f_{i,j}+\min_{k=1}^R f_{x,k}$。

- 如果 $t=2$，则转移方程为 $f_{i,j}=f_{i,j}+f_{x,j}$。

初始状态就是 $f_{i,j}=j$。

注意到这样 dp 是 $nR^2$ 的，可以对每个点维护最小值和次小值，$t=0$ 时，若 $j$ 正好是取到最小值的那个位置 $p$ 则选则次小值，否则选最小值，$t=1$ 时直接取最小值。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
using Pii = pair<int, int>;

const int kMaxN = 1e5 + 5, kMaxR = 105, kM = 1e9 + 7;

int n, r, ans, fl, f[kMaxN][kMaxR];
vector<Pii> e[kMaxN];

struct Max {
  int mn1 = 1e18, mnp1 = 0, mn2 = 1e18;
  void Record(int x, int y) {
    if (x < mn1) mn2 = mn1, mn1 = x, mnp1 = y;
    else if (x < mn2) mn2 = x;
  }
  int Get(int x) { return (mnp1 == x ? mn2 : mn1); }
} st[kMaxN];

void S(int x, int fa) {
  iota(f[x] + 1, f[x] + r + 1, 1);  
  for (auto [nxt, w] : e[x]) {
    if (nxt != fa) {
      S(nxt, x);
      if (!w) {
        for (int i = 1; i <= r; i++) f[x][i] += st[nxt].Get(i);
      } else if (w == 1) {
        for (int i = 1; i <= r; i++) f[x][i] += st[nxt].Get(114514);
      } else {
        for (int i = 1; i <= r; i++) f[x][i] += f[nxt][i];
      }
    }
  }
  for (int i = 1; i <= r; i++) st[x].Record(f[x][i], i);
}

signed main() {
  cin >> n >> r, ans = r;
  for (int i = 1, x, y, w; i < n; i++) {
    cin >> x >> y >> w;
    fl |= (w == 0);
    if (!w) ans = ans * (r - 1) % kM;
    else if (w == 1) ans = ans * r % kM;
    e[x].push_back({y, w}), e[y].push_back({x, w});
  }
  if (r == 1 && fl) return cout << "0 0", 0;
  cout << ans << ' ';
  S(1, 0);
  cout << *min_element(f[1] + 1, f[1] + r + 1);
}
```

---

## 作者：Lele_Programmer (赞：0)

# P7846 题解

## 思路

题目要求的两个子问题，都可以用树形 dp 来做。

### 子问题 1

求方案数量，设 $g_{i,j}$ 为以 $i$ 为根的子树中，根节点填的是数字 $j$ 的方案数量。

枚举每一个子节点，若边权是 $0$，则两个数字不能相同，若边权是 $1$，则任何 $1$ 到 $R$ 的数字都可以取，若边权是 $2$，则只能取相同的数字。将 $g_{i,j}$ 赋予初始值 $1$，后面枚举的时候把结果相乘即可。

这里不用分别枚举父节点和子节点填充的数字，这一操作的复杂度是 $O(R^2)$，其实 $O(R)$ 就可以完成，记录子节点的所有 $g$ 值的和。枚举到边权为 $0$ 的情况，直接与 $sum-g_{v,j}$ 相乘，边权为 $1$，与 $sum$ 相乘，边权为 $2$，与 $g_{v,j}$ 相乘。

以 $1$ 为根做一次树形 dp，最终结果 $ans=\sum\limits_{i=1}^{R}g_{1,i}$

### 子问题 2

求最值（本题求最小值），设 $f_{i,j}$ 为以 $i$ 为根的子树中，根节点填 $j$ 的点权和最小值。

边权为 $0$，取子节点所有 $g$ 值中，$j$ 不相同的值的最小值。边权为 $1$，取全部的最小值。边权为 $2$，取 $j$ 值相同的值。

当然，这里也不需要用 $O(R^2)$ 枚举父节点子节点的填充状态，开两个数组 $p_1,p_2$，$p_1$ 记录前缀最小值，$p_{1_i}=\min \{ p_{1_{i-1}},g_{v,i} \}$，$p_2$ 记录后缀最小值，$p_{2_i}=\min \{ p_{2_{i+1}},g_{v,i} \}$，求除某个元素外的其余值最小值，只需 $\min \{ p_{1_{x-1}},p_{2_{x+1}} \}
$

以 $1$ 为根做一次树形 dp，最终的结果：$ans=\min\limits_{i=1}^{R}f_{1,i}$

两个问题的时间复杂度都是：$O(NR)$。

### 特判

最后别忘了输出 `0 0` 的特殊情况，当 $R=1$ 且出现边权为 $0$ 的边时，出现矛盾，无解。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N=100005;
const int M=200005;
const int K=105;
const int mod=1000000007;
const int inf=1000000007;

int n,R;
int e[M],ne[M],h[N],w[M],tot;
int f[N][K];
int g[N][K];
int p1[K];
int p2[K];

void add(int a,int b,int c) {
    e[tot]=b,w[tot]=c,ne[tot]=h[a],h[a]=tot++;
}

void dfs1(int u,int fa) {
    for (int i=1;i<=R;++i) {
        g[u][i]=1;
    }
    for (int i=h[u];~i;i=ne[i]) {
        if (e[i]==fa) continue;
        dfs1(e[i],u);
        int sum=0;
        for (int j=1;j<=R;++j) {
            sum+=g[e[i]][j];
        }
        for (int j=1;j<=R;++j) {
            if (w[i]==0) {
                g[u][j]*=(sum-g[e[i]][j])%mod;
            } else if (w[i]==1) {
                g[u][j]*=sum%mod;
            } else {
                g[u][j]*=g[e[i]][j];
            }
            g[u][j]%=mod;
        }
    }
}

void dfs2(int u,int fa) {
    for (int i=1;i<=R;++i) {
        f[u][i]=i;
    }
    for (int i=h[u];~i;i=ne[i]) {
        if (e[i]==fa) continue;
        dfs2(e[i],u);
        p1[0]=inf;
        p2[R+1]=inf;
        for (int j=1;j<=R;++j) {
            p1[j]=min(p1[j-1],f[e[i]][j]);
        }
        for (int j=R;j;--j) {
            p2[j]=min(p2[j+1],f[e[i]][j]);
        }
        for (int j=1;j<=R;++j) {
            if (w[i]==0) {
                f[u][j]+=min(p1[j-1],p2[j+1]);
            } else if (w[i]==1) {
                f[u][j]+=p1[R];
            } else {
                f[u][j]+=f[e[i]][j];
            }
        }
    }
}

signed main() {
    memset(h,-1,sizeof(h));
    scanf("%lld %lld",&n,&R);
    bool flag=false;
    for (int i=1;i<=n-1;++i) {
        int a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        add(a,b,c);
        add(b,a,c);
        if (c==0) flag=true;
    }
    if (flag && R==1) {
        puts("0 0");
        return 0;
    }
    dfs1(1,0);
    int ans1=0;
    for (int i=1;i<=R;++i) {
        ans1+=g[1][i];
    }
    ans1%=mod;
    dfs2(1,0);
    int ans2=inf;
    for (int i=1;i<=R;++i) {
        ans2=min(ans2,f[1][i]);
    }
    printf("%lld %lld",ans1,ans2);
    return 0;
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
~~简要题意已经说的很清楚了就不说了~~
## Sol
先解决问题一，分析一下树上三种边会对答案产生什么影响。

$t=1$，两端点随便选任何值，可以看作这种边将原图分成了若干连通块，连通块彼此之间选值不受影响，由乘法原理，答案是所有由该边分成连通块的答案相乘。

$t=2$，两端点值相同，确定一个端点的值以后另一个端点也可以确定，那不妨把所有这样的边所连的点合并，进行缩点操作。我们认为缩点后，所有点集内点的值相同。

$t=0$，两端点值不同。经过上述两种操作，变成了只有这种边的森林，对应测试数据四。让树根随便选，有 $R$ 种答案，任意边两端点值不同，则树根子结点就只有 $(R-1)$ 种可选，树根子节点的子节点也只有 $(R-1)$ 种方案，之后所有点的方案都是这样，直到叶子结点，则由乘法原理，一颗边全为 $t=0$ 的树的答案是：

$$R \times (R-1)^{size-1}$$

$size$ 是这颗树的节点数量，注意在这个时候已经缩完点了，是缩完点后，点的数量。

答案就是（$T$ 是森林中的一颗极大树，下同）：

$$\prod_{T \subseteq G}  (R-1)^{size(T)-1}$$

怎么实现？输入时 $t=2$ 建双向边跑 `tarjan` ，或者直接并查集维护。$t=1$ 不管扔掉，$t=0$ 存下来，缩完点建新图。然后在第二问 dfs 时顺带记录一下大小，直接相乘即可。

第二问是个树形 dp，注意到数据 $nR\le 10^7$，考虑枚举所有点的取值，从初始化，最终答案，转移方程来考虑。

令 $f[u][i]$ 表示 $u$ 节点取 $i$ 时整个子树最小的点权之和。
不难得到一颗树的最终答案是：

$$ \min_{i=1}^{R} f[root][i] $$

初始化（$n'$ 为缩完点后的所有点数）：

$$f[i][j]=j,1\le i\le n',1 \le j\le R$$

转移方程：

$$f[u][j]=\sum_{v \in son(u)}\left(\min_{k=1}^R f[v][k],k\neq j \right)$$

这么做是 $O(nR^2)$ 的，大抵是会超时的，注意到每次转移几乎都是取儿子答案的最小值，只有一种情况取得是次小值，也就是儿子答案最小时的点值和当前点相等。

也就是两种情况，对于：
$$f[v][p]=\min_{k=1}^R f[v][k]$$

$$f[v][c]=\min(\min_{k=1}^{p-1} f[v][k],\min_{k=p+1}^{R} f[v][k])$$

也就是最小值和次小值。

$$\begin{cases}
  f[u][j]=\sum_{v \in son(u)} f[v][c_{v}]& \text{ if } p_{v}=j \\
  f[u][j]=\sum_{v \in son(u)} f[v][p_{v}]& \text{ otherwise}
\end{cases}$$

只需要记录当前的最小值和次小值，以及最小值，次小值对应取值，返回给父亲节点即可。

最后答案：

$$ans=\sum_{T\subseteq G} f[root(T)][p_{root(T)}]$$

时间复杂度 $O(nR)$，瓶颈在于求最小值。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 150005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
vector<ll>v[N];
ll n,m;
struct edge{
    ll x,y;
}e[N];
namespace scc{
    ll dfn[N],low[N],vis[N],cnt;
    ll bel[N],siz[N];
    ll tot;
    stack<ll>q;
    void dfs(ll x){
        dfn[x]=low[x]=++cnt;
        vis[x]=1;
        q.push(x);
        for(auto y:v[x]){
            if(!dfn[y]){
                dfs(y);
                low[x]=min(low[x],low[y]);
            }else if(vis[y])low[x]=min(low[x],dfn[y]);
        }
        if(low[x]==dfn[x]){
            ++tot;
            while(1){
                ll p=q.top();
                q.pop();
                bel[p]=tot;
                vis[p]=0;
                siz[tot]++;
                if(x==p)break;
            }
        }
    }
}using namespace scc;
ll fpow(ll x,ll y){
    ll z=1;
    while(y){
        if(y&1)z=z*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return z;
}
ll fl[N],sz,ans,p1,p2;
ll f[N][105];
pair<pair<ll,ll>,ll> dfs2(ll x,ll now){
    fl[x]=1;
    sz++;
    ll mi=inf,lmi=inf-1;;
    p1=n+1,p2=n+1;
    for(int i=1;i<=m;i++)f[x][i]=i*siz[x];
    for(auto y:v[x]){
        if(fl[y])continue;   
        auto t=dfs2(y,now^1);
        for(int i=1;i<=m;i++){
            if(i!=t.fi.se)f[x][i]=f[x][i]+t.fi.fi;
            else f[x][i]=f[x][i]+t.se;
        } 
    }
    for(int i=1;i<=m;i++){
        if(f[x][i]<mi){
            p1=i;
            lmi=mi;
            mi=f[x][i];
            continue;
        }
        if(f[x][i]<lmi){
            lmi=f[x][i];
        }
    }
    return {{mi,p1},lmi};
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m;
    ll cnt=0;
    for(int i=1;i<n;i++){
        ll x,y,z;
        cin>>x>>y>>z;
        if(z==2)v[x].push_back(y);
        if(z==2)v[y].push_back(x);
        if(z==0)e[++cnt]={x,y};
    }
    for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
    for(int i=1;i<=n;i++)v[i].clear();
    for(int i=1;i<=cnt;i++){
        v[bel[e[i].x]].push_back(bel[e[i].y]);
        v[bel[e[i].y]].push_back(bel[e[i].x]);
    }
    ll res=1;
    for(int i=1;i<=tot;i++){
        if(!fl[i]){
            sz=p1=p2=0;
            ans=(ans+dfs2(i,0).fi.fi);
            res=res%mod*fpow(m-1,sz-1)%mod*(m)%mod;
        }
    }
    if(res==0)ans=0;
    cout<<res<<" "<<ans<<endl;
    return 0;
}

```

---

