# Accumulation Degree

## 题目背景

树木是自然景观的重要组成部分，因为它们可以防止土壤侵蚀，并在其树叶中及其下方提供特定的气候庇护生态系统。研究表明，树木在生产氧气和减少大气中的二氧化碳方面起着重要作用，还可以调节地面温度。它们在园林设计和农业中也是重要的元素，既因为它们的美学吸引力，也因为它们的果园作物（如苹果）。木材也是常见的建筑材料。

## 题目描述

树在许多世界神话中也扮演着亲密的角色。许多学者对树的一些特殊属性感兴趣，例如树的中心、树的计数、树的着色等。树的累积度 $A(x)$ 就是其中的一种属性。

我们这么定义 $A(x)$：

- 树的每一条边都有一个正容量。
- 树中度为 $1$ 的节点被称为终端节点。
- 每条边的流量不能超过其容量。
- $A(x)$ 是节点 $x$ 可以流向其他终端节点的最大流量。

树的累积度是指其节点中最大累积度的值。你的任务是找到给定树的累积度。

## 说明/提示

原题中没有提到的数据范围：$T \le 4$，$\sum n \le 2\times 10 ^ 5$。

## 样例 #1

### 输入

```
1
5
1 2 11
1 4 13
3 4 5
4 5 10```

### 输出

```
26```

# 题解

## 作者：lym2022 (赞：9)

### 思路
注意到 $n$ 较大，枚举每个点作为根 dp 一遍会超时，考虑换根 dp。

大体的可以先以 $1$ 为根节点 dp 一遍，然后将根节点的答案转移为子节点的答案。

具体的，在第一次 dp 时先从上向下搜，算出子节点 $v$ 的答案推出父节点 $u$ 的答案，这里要分两种情况，第一种：子节点是叶子节点，就直接将 $f_u$ 加上 $u,v$ 之间的容量 $w$，因为目标是要让根节点答案最大，第二种：子节点不是叶子节点，$f_u$ 就要加上 $f_v$ 和 $w$ 的较小值，因为 $f_v$ 是子节点的最大流量，$w$ 是当前的最大流量，因为题目要求边的流量不能超过 $w$。

再换根时减去重复的地方再加上当前边的贡献就可以了。画图就很好理解。统计答案时取每个节点为根节点时答案的最大值就可以了。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int T,n,f[N],g[N],ans;

vector<pair<int,int> > e[N];

void dfs1(int u,int fa) {
	f[u] = 0;
	for(auto it : e[u]) {
		int v = it.first,w = it.second;
		if(v == fa) continue;
		dfs1(v,u);  //先搜 
		if(e[v].size() == 1) f[u] += w;  //如果是儿子叶子节点，那么当前答案就直接加上 w 
		else f[u] += min(f[v],w);     //否则就取 f[v] 和 w 的较小值
	}
}

void dfs2(int u,int fa) {
	for(auto it : e[u]) {
		int v = it.first,w = it.second;
		if(v == fa) continue;
		if(e[v].size() == 1) g[v] = f[v] + w;   //由原来答案加上当前边权 
		else g[v] = f[v] + min(f[u] - min(f[v],w),w);   //减去重复 
		dfs2(v,u);
	}
	ans = max(ans,g[u]);  //答案取每个节点为根时的最大值 
}

void solve() {
	cin >> n;
	for(int i = 0;i<=n;i++) {   //多测初始化！！ 
		e[i].clear();
		f[i] = g[i] = 0;
	}
	ans = 0;
	for(int i = 1;i<n;i++) { 
		int u,v,w;
		cin >> u >> v >> w;
		e[u].push_back({v,w});  //邻接表存图
		e[v].push_back({u,w});  //要存双向边 
	}
	dfs1(1,0);
	g[1] = f[1];   //换根初始化 
	dfs2(1,0);
	cout << ans << '\n';
}

int main() {
	cin >> T;
	while(T--) solve();
	return 0;
}
```
点个赞再走吧！

---

## 作者：wangbinfeng (赞：8)

[![](https://img.shields.io/badge/题目-P10974_Accumulation_Degree-green)
![](https://img.shields.io/badge/难度-提高+/省选−-blue)
![](https://img.shields.io/badge/考点-换根_DP-red)
![](https://img.shields.io/badge/题型-传统题-yellow)](https://www.luogu.com.cn/problem/P10974)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

---
这不一眼换根 DP，然后我尝试不用编译器一遍过（也许算成功吧？3 次 CE、1 次 RE），感觉没难度。别被蓝题吓到了，其实挺简单的。

考虑下图（鸣谢 [Graph Editor](https://csacademy.com/app/graph_editor/) 生成图片）：![](https://cdn.luogu.com.cn/upload/image_hosting/vbtpm5g9.png)

显然，$ ans_A=c+d+\min\{b,e+f\},ans_B=\min\{b,c+d\}+e+f$。

暴力做法很容易想到：枚举根节点，对于每个根节点，DFS 计算出其对应的结果，取所有结果的最大值作为答案即可。但是时间复杂度为 $\Theta(n^2)$，肯定会超时，思考如何优化。

  注意到，计算完 $ans_A$ 后计算 $ans_B$ 时，其余部分点对答案的贡献被重复查找了。着虽然对答案的正确性没有影响，但是造成了极大的事件浪费。

经过分析得出，$ans_B=ans'_B+\min\{b,ans_A-\min\{b,ans'_B\}\}$（$ans'_X$ 表示以上一个节点为根时这个节点不考虑其父边的影响对答案的贡献，下同；这里一定要自己对着图分析一下，还是比较显然的），可以类比出其它的点转移方程。

注意到 $A$ 节点不是叶子节点，那我们再考虑一下如何从叶子节点 $C$ 转移到节点 $A$：$ans_A=ans'_C+c$，因为如果当前根节点只有一个子，那么换根后这个节点的流量也要被新根节点统计。

就完了，时间复杂度为 $\Theta(n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=200000+9,inf=0x3f3f3f3f3f3f3f3fLL;
vector<vector<pair<int,int>>>g;
int n,dp[maxn],ans; 
inline int dfs1(const int u,const int fa){
	for(const auto[v,w]:g[u])if(v!=fa)dp[u]+=min(dfs1(v,u),w);
	return dp[u]==0?inf:dp[u];
}
inline void dfs2(const int u,const int fa,const int sum){
	ans=max(ans,sum);
	for(const auto[v,w]:g[u])if(v!=fa){
		if(g[u].size()==1)dfs2(v,u,dp[v]+w);
		else dfs2(v,u,dp[v]+min(sum-min(dp[v],w),w)); 
	}
} 
signed main(){
	static int T=-1;
	if(T==-1){
		ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
		cin>>T;
	}
    if(T--==0)return 0;
	cin>>n,ans=0,g.resize(n+9),g.clear(),memset(dp,0,sizeof dp);
	for(int i=1,u,v,w;i<n;i++)cin>>u>>v>>w,g[u].push_back({v,w}),g[v].push_back({u,w}); 
	dfs1(1,-1),dfs2(1,-1,dp[1]);
	cout<<ans<<'\n';
	main();
}
```

- UPD. 2024 年 12 月 13 日进行订正，发现之前写的内容出现了不少错误，而作者本人由于已经 AFO 了一个季度，没有怎么接触 OI 导致也一时看不懂自己写的题解（诚挚地向之前阅读本提题解的同学道歉，还是写的太烂了）。如果还有错误希望能得到指出！

---

[![](https://jrenc.azurewebsites.net/api/signature?code=zHZRCCItO-yB8t7d2KyitELFDwADnXIotkeeIQL3juyNAzFucnyrWA%3D%3D&name=thanks%20for%20reading%20%20%20%20%20%20%20%20by%20%40wangbinfeng(387009)&animate=true&speed=0.7&color=purple)](https://www.luogu.com.cn/user/387009)
$$\color{grey}{\tiny{\texttt{发现上面的签名是动图了吗？}}}$$

---

## 作者：xuchuhan (赞：4)

省流：换根 DP。

## Description

认为题目描述不是很清晰，可以去看[这道题](https://www.luogu.com.cn/problem/U224225)的题目描述，认为较为清晰。

## Analysis

显然如果暴力枚举根，对于每个根算一遍答案是不可行的，这样复杂度到达了 $\mathcal{O(n^2)}$。

于是我们使用**换根 DP**，即随便找一个根节点算出初始答案 $dp_x$，表示在初始根节点下，$x$ 为根的子树的答案。然后再进行第二次 DFS，算出以 $x$ 为全局根节点，整棵树的答案 $f_x$。$f_x$ 的答案通常由其父亲节点 $fa$ 的答案 $f_{fa}$ 经过推导 $\mathcal{O(1)}$ 得到。

因此，**换根 DP** 也被称为**二次扫描 DP**。

## Solution

对于第一遍扫描，我们不妨设 $1$ 为根节点。那么 $dp_x$ 表示以 $x$ 为根节点的子树的流量。那么对于边 $x\rightarrow to$，边权为 $w$ 则有：$dp_x\leftarrow dp_x+\min(dp_{to},w)$。

对于第二遍扫描，我们设 $f_x$ 表示以 $x$ 为全局根节点整棵树的流量。设已经求出 $f_x$，希望通过 $x\rightarrow to$ 这条边求出 $f_{to}$。文字不是很好描述，看一张图理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/pkqucdjn.png)

首先，当前整棵树的流量是 $f_x$，蓝色部分的流量是 $dp_{to}$，那么黄色部分的流量就是 $f_x-\min(dp_{to},w)$，注意不是 $f_x-dp_{to}$，因为蓝色部分给整棵树贡献的流量还需要和 $x\rightarrow to$ 这条边的边权取较小值。

那么，当 $to$ 变为根节点时，答案仍然还是蓝色部分的流量加黄色部分的流量，但同样的，此时的黄色部分遭到了 $to\rightarrow x$ 这条边的限制，所以流量变为 $\min(w,f_x-\min(dp_{to},w))$。最后就是 $f_{to}=dp_{to}+\min(w,f_x-\min(dp_{to},w))$。

需要注意的是，当 $to$ 是叶子节点的时候，$dp_{to}$ 在第一次扫描的时候会被设为无限大，那么当答案为 $dp_{to}+\min(w,f_x-\min(dp_{to},w))$ 时会出问题。那么特判一下就好了：当 $to$ 是叶子节点的时候，$f_{to}=\min(w,f[x])$，这个式子是显然的。

初始时有 $f_1=dp_1$。

那么就没什么好说的了。注意多测清空。放一下代码。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,n;
int dp[N],f[N];
struct node{
	int id,val;
};
vector<node>v[N];
void DFS1(int x,int fa){//第一次扫描 
	if(x!=1&&v[x].size()==1)//叶子节点 
		dp[x]=1e18;
	for(int i=0;i<v[x].size();i++){
		int to=v[x][i].id,w=v[x][i].val;
		if(to==fa)
			continue;
		DFS1(to,x);
		dp[x]+=min(dp[to],w);
	}
	return;
}
void DFS2(int x,int fa){//第二次扫描 
	for(int i=0;i<v[x].size();i++){
		int to=v[x][i].id,w=v[x][i].val;
		if(to==fa)
			continue;
		if(dp[to]!=1e18)//不是叶子节点 
			f[to]=dp[to]+min(w,f[x]-min(w,dp[to]));
		else//是叶子节点 
			f[to]=min(w,f[x]);
		DFS2(to,x);
	}
	return;
}
void Work(){
	cin>>n;
	for(int i=1;i<=n;i++){//多测清空 
		dp[i]=f[i]=0;
		v[i].clear();
	}
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		v[x].push_back({y,z});
		v[y].push_back({x,z});
	}
	DFS1(1,0);
	f[1]=dp[1];
	DFS2(1,0);
	int ans=f[1];
	for(int i=2;i<=n;i++)
		ans=max(ans,f[i]);
	cout<<ans<<"\n";
}
signed main(){
	cin>>T;
	while(T--)
		Work();
	return 0;
}
```

---

## 作者：Barewalk (赞：4)

[biu biu ~](https://www.luogu.com.cn/problem/P10974)

### Preface

这篇题解是对蓝书的总结，力求用形象的语言深入理解此类问题。（为什么蓝书上的好题都这么少人做呢？）

### Description

感觉这题题面描述就很不形象啊，可以参考蓝书的题面呢：

有一个水系，可以看做一棵无根树，河道为无向边，每条河道的容量为边权。每条河道单位时间流过的水量不能超过容量。

若以某点为根，则水系中的水将从根出发流向叶子。定义流量为根单位时间流出的水量，求以哪点为根最大流量最大，输出这个最大值。

### Solution

我们先从朴素解法出发寻找灵感。枚举每个点为根，分别求出以它为根的最大流量，答案取最大值。

于是问题变成：在确定根的前提下，如何求出最大流量？这样就变成简单树形 DP 啦。定义 $f_u$ 为 $u$ 子树的最大流量，自底向上进行状态转移。对于一条连接 $u$ 与某棵子树 $v$ 的河道，它流过的水量既不能超过河道容量 $val$，也不能超过 $f_v$，于是我们成功得出 DP 方程：

$$f_u=\sum\min(val,f_v)$$

至于边界问题嘛，把叶子结点设成极大值就包了。

由于 DP 时每个结点都会被遍历一次，再加上枚举根，总复杂度为 $O(n^2)$，于是我们成功获得了 [30 pts](https://www.luogu.com.cn/record/197535312)。好！~~终于水完了~~是时候进入正题了：

我们发现，这道题需要我们以**每个结点为根**进行一系列统计。对于该类题目，我们自然想到：

### 二次扫描与换根法

1. 第一次扫描

任选一个点为根，本题我们默认为结点 1，在“有根树”上进行一次**自底向上**的树形 DP，统计子树的信息。这个问题我们上面已经解决，这里不再赘述。

2. 第二次扫描

从刚才选的根出发，对整棵树执行一次深度优先遍历，并进行**自顶向下**的转移。定义 $dp_u$ 为以 $u$ 为根时的最大流量，那么根据定义可以得出 $dp_1=f_1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/pbudi59t.png)

我们发现，若以 $u$ 为根，唯一改变的其实就是与 $w$ 连接的那一段，$w$ 从父亲变成了子树。于是我们计算出 $w$ 能给 $u$ 做出的贡献，再加上 $u$ 子树的最大流量即 $f_u$ 即可。

我们参考前面的转移，分别思考连接 $u,w$ 的河道与 $w$ 子树的最大流量。因为是自顶向下的转移，所以我们 dfs 时是在遍历 $w$ 时更新子结点 $u$，故前者就是边权 $val$。而后者，观察发现就是以 $w$ 为根时不算 $u$ 子树的最大流量，因此用 $dp_w$ 减掉 $u$ 子树的贡献即可。

于是我们成功得出新的转移方程：

$$dp_u=f_u+\min(dp_w-\min(val,f_u),val)$$

注意还需考虑边界情况。由于叶子的最大流量（这里指的是 $f$ 数组）前面赋成了极大值，因此不应根据这个转移。以叶子为根时的转移方程应该是：

$$dp_u=\min(dp_w-val,val)$$

最后，答案对 $dp$ 数组取 max 即可。于是，我们用二次扫描与换根法代替根的枚举，可以 $O(n)$ 的解决这个问题。还有一点实现上的小细节就在注释里说了。完结撒花！

### Code

```cpp
#include <cstring>
#include <iostream>

#define N 200100
using namespace std;

int h[N], nxt[N * 2], t[N * 2], w[N * 2], cnt;
// 无向图开 2 倍
void add(int x, int y, int v) {
    nxt[++cnt] = h[x], h[x] = cnt, t[cnt] = y, w[cnt] = v;
}

int f[N];
void DP(int x, int fa) {
    // 对于无根树的特殊写法
    int sum = 0;
    for (int i = h[x]; i; i = nxt[i]) {
        int v = t[i];
        if (v == fa) continue;
        dfs(v, x);
        sum += min(w[i], f[v]);
        // 自底向上转移
    }
    f[x] = sum ? sum : 0x3f3f3f3f;
    // 若 sum 没有被更新自然说明该节点为叶子结点，赋成极大值
}

int dp[N], ans;
void dfs(int x, int fa) {
    for (int i = h[x]; i; i = nxt[i]) {
        int v = t[i];
        if (v == fa) continue;
        if (f[v] == 0x3f3f3f3f) dp[v] = min(dp[x] - w[i], w[i]);
        else dp[v] = f[v] + min(dp[x] - min(w[i], f[v]), w[i]);
        DP(v, x);
        // 自顶向下转移
    }
    ans = max(ans, dp[x]);
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i = 1; i < n; i++) {
            int x, y, v; cin >> x >> y >> v;
            add(x, y, v), add(y, x, v);
            //无向图建 2 倍
        }
        DP(1, 0);
        dp[1] = f[1];
        dfs(1, 0);
        cout << ans << "\n";
        for (int i = 1; i <= n; i++) h[i] = 0;
        cnt = ans = 0;
        // 记得初始化
    }
    return O;
}
```

---

## 作者：LTTXiaochuan (赞：3)

**题目大意**：给一棵树（$n\leq2\times10^5$），选一个点作为源点，源点的水流向叶子，但流量不能超过该路径上的最小边权，求源点流出水的流量最大值。



每个点作为根（源点），实际上就是递归其**直属儿子**，然后取其儿子的流量和连接儿子的边的流量的最小值。（可以认为叶子结点的流量无穷大）

下面是用以帮助理解的暴力代码（下面我们还会用到）：

```c++
int dfs(int u,int fa)
{
    int ans=0,flag=0;
    for(int i=fi[u]; i; i=ne[i])
        if(v[i]!=fa)
            ans+=min(w[i],dfs(v[i],u)),flag=1; //取儿子和边的流量更小的一个
    if(flag) return ans;
    else return INF; //叶子结点返回 INF
}
```

复杂度为 $O(n^2)$，显然会 T 飞。

不难发现，这样做计算了大量重复冗余的信息。需要思考：更换根节点时，哪些信息发生了变化？

由上面的暴力发现，影响每个点信息的是 $fa$ 这个参数，只要它不变，该节点的流量也就不变。

我们掏一棵树出来（样例）：

![看我干嘛？](https://cdn.luogu.com.cn/upload/image_hosting/ilabgbuq.png)

如果拿 $1$ 作根，那么 $4$ 和 $2$ 的父亲是 $1$、$3$ 和 $5$ 的父亲是 $4$。

如果拿 $4$ 作根，那么 $2$、$3$、$5$ 的父亲不变，其存储的信息也就不变，只有 $1$ 和 $4$ 的父亲对调了。

对于“父亲对调”，信息会如何变化呢？我们用 $d_i$ 表示某个节点存储的信息。

不难发现，$1$ 的信息原本是 $\min(13,d_4)+\min(11,d_2)$，现在减去了 $\min(13,d_4)$，也就是减去了与之相连的边和点的信息。

又不难发现，$4$ 的信息原本是 $\min(5,d_3)+\min(10,d_5)$，现在多加了一个 $\min(13,d_1)$（注意此处的 $d_1$ 是上面的新信息）。然后，别的信息不变，就直接算出来了。

如果是和叶子节点进行对调呢......？

不难发现，虽然计算时将叶子结点信息看做无穷大，**但对调时应当作 $0$ 来处理**。



注意事项：

1. 注意多测清空；
2. 换根完毕后要复原数据。



示例代码：

```c++
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+10,INF=0x3f3f3f3f;

int idx=1,ans=0;
int v[N*2],w[N*2],fi[N],ne[N*2]; //注意开两倍
int dat[N];

void add(int x,int y,int z)
{
    v[idx]=y,w[idx]=z;
    ne[idx]=fi[x];
    fi[x]=idx++;
}

int getdat(int u,int fa) //上文的暴力代码，加了个存数据而已
{
    int ans=0,flag=0;
    for(int i=fi[u]; i; i=ne[i])
        if(v[i]!=fa)
            ans+=min(w[i],getdat(v[i],u)),flag=1;
    if(flag) return dat[u]=ans;
    else return INF;
}

void dfs(int u,int fa)
{
    ans=max(ans,dat[u]);
    int mem1=dat[u],mem2;
    for(int i=fi[u]; i; i=ne[i])
        if(v[i]!=fa)
        {
            mem2=dat[v[i]];
            dat[u]-=min(w[i],dat[v[i]]);
            dat[v[i]]+=min(w[i],(dat[u]==0 ? INF : dat[u])); //这里，计算时按照无穷大处理
            dfs(v[i],u);
            dat[u]=mem1,dat[v[i]]=mem2; //记得复原原数据
        }
}

void init() //一定记得多测要清空
{
    idx=1; ans=0;
    for(int i=0; i<N; i++) w[i]=fi[i]=dat[i]=ne[i]=ne[N+i]=0;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        init();

        int n;
        cin>>n;
        for(int i=1; i<n; i++)
        {
            int x,y,z;
            cin>>x>>y>>z;
            add(x,y,z); //注意建双向边
            add(y,x,z);
        }
        getdat(1,0);
        dfs(1,0);
        cout<<ans<<"\n";
    }

    return 0;
}
```

---

## 作者：liuChF (赞：2)

首先有一个朴素的做法：以每个点为根进行遍历，统计答案，复杂度 $O(n^2)$。考虑怎么进行 DP，设 $d_{i}$ 表示以 $i$ 为根的最大水量，DFS 的回溯的过程中，有：
$$
d_{i}=\sum_{s\in Son(i)}\min(d_{i},c(i,s))
$$
考虑进行换根优化，先以 $root$ 为根将 $d_{root}$ 进行更新，设 $f_i$ 表示以 $i$ 为根，最大的水流量。显然有 $f_{root}=d_{root}$，现在模拟换根的过程：

设有两个点 $u,v$ 其中 $u$ 是 $v$ 的父亲节点，现在已知 $d_{u},d_{v},f_{u}$，现在我们要求出 $f_{v}$，首先发现 $f_{v}$ 除了和 $u$ 相连的边，其他边的贡献都已经 $d_v$ 中计算了，我们只要处理 $u-v$ 这条边上的信息就行了，其对 $f_v$ 的贡献为 $\min(c(u,v),f_u-w_{u,v})$，其中 $w_{u,v}$ 表示以 $u$ 为根时，流向 $v$ 的水量，$f_{u}-w_{u,v}$ 表示 $u$ 流向 $s\in Son(u),s\ne v$ 这些点的水流量，再和 $c(u,v)$ 取最小值就是以 $v$ 为根时分配给 $u$ 的最大水流量。**注意到 $w_{u,v}$ 就是 $\min(d_{u,v},c(u,v))$，这是在第一遍 DP 时所决定的**。所以有：
$$
f_{v}=d_v+\min(c(u,v),f_u-\min(d_{u,v},c(u,v)))
$$
然后进行第二次 DFS 进行换根 DP，就可以了，**要注意边界时的状态转移**。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fq(i,d,u) for(int i(d); i <= u; ++i)
#define fr(i,u,d) for(int i(u); i >= d; --i)
#define pii pair <int, int>
#define inf 0x3f3f3f3f
using namespace std;
const int N = 2e5 + 10;
int T, n, f[N], d[N], ans;
vector <pii> g[N];
void dfs1(int u, int fa) {
	for (pii cur : g[u]) {
		int v = cur.first, w = cur.second;
		if (v == fa) continue;
		if (g[v].size() == 1) d[v] = w;
		else dfs1(v, u);
		d[u] += min(d[v], w);
	}
}
void dfs2(int u, int fa) {
	for (pii cur : g[u]) {
		int v = cur.first, w = cur.second;
		if (v == fa) continue;
		if (g[u].size() == 1) f[v] = (g[v].size() != 1) * d[v] + w;
		else f[v] = d[v] + min(f[u] - min(d[v], w), w);
		dfs2(v, u);
	}
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n;
		int u, v, w;
		ans = 0;
		fq(i, 0, n) g[i].clear(), f[i] = 0, d[i] = 0;
		fq(i, 1, n - 1) {
			cin >> u >> v >> w;
			g[u].push_back({v, w});
			g[v].push_back({u, w});
		}
		dfs1(1, -1);
		f[1] = d[1];
		dfs2(1, -1);
		fq(i, 1, n) ans = max(ans, f[i]);
		cout << ans << '\n';
	}
	return 0;
}
```
附一些 Hack:
``` cpp
2
2
1 2 1
3
1 2 1
2 3 1
```

---

## 作者：laoliu12345 (赞：2)

## P10974
### 解法说明
这是一道很不错的换根 DP 练习题，$d$ 数组表示在以 1 为根的树上各个子树的最大流量，$f$ 数组是答案。我们先求出在根为 1 的情况下的答案，然后考虑如何根据其来推出其他答案。

当我们通过一条边来转移时，我们设 $u$ 为已求出答案的根，$v$ 为待求根。那么我们考虑对于 $v$ 子树的答案就是 $d_v$，而对于 $u$ 子树来说 $v$ 对他的贡献是 $\min(d_v,w_i)$，其中 $w_i$ 指边权。那其余部分的贡献就是 $f_u-\min(d_v,w_i)$。那么我们就得到了状态转移方程 $f_v \leftarrow d_v+\min(f_u-\min(d_v,w_i),w[i])$。

最后不要忘了特判子树大小为 1 的情况。

那就可以愉快的写代码了。
### 题目代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10,M=N*2;
int n;
int h[N],e[M],w[M],ne[M],idx;
int d[N];
int f[N];
int in[N];
int root;
void add(int a,int b,int c)
{
	e[idx]=b,ne[idx]=h[a],w[idx]=c,h[a]=idx++;
}
void dp(int u,int pre)
{
	d[u]=0;
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i];
		if(j==pre) continue;
		dp(j,u);
		if(in[j]==1) d[u]+=w[i];
		else d[u]+=min(d[j],w[i]);
	}
}
void dfs(int u,int pre)
{
	for(int i=h[u];~i;i=ne[i])
	{
		int j=e[i];
		if(j==pre) continue;
		if(in[u]==1) f[j]=d[j]+w[i];
		else if(in[j]==1) f[j]=d[j]+min(f[u]-w[i],w[i]);
		else f[j]=d[j]+min(f[u]-min(d[j],w[i]),w[i]);
		dfs(j,u);
	}
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		memset(in,0,sizeof in);
		memset(h,-1,sizeof h);
		idx=0;
		for(int i=0;i<n-1;i++)
		{
			int a,b,c;
			cin>>a>>b>>c;
			add(a,b,c),add(b,a,c);
			in[a]++,in[b]++;
		}
		root=1;
		dp(root,-1);
		f[root]=d[root];
		dfs(root,-1);
		int res=0;
		for(int i=1;i<=n;i++) res=max(res,f[i]);
		cout<<res<<endl;
	}
	return 0;
}
```

---

## 作者：Enoch2013 (赞：1)

## 题目描述

我们这么定义树的累计度 $A(x)$：

- 树的每一条边都有一个正容量。
- 树中度为 $1$ 的节点被称为终端节点。
- 每条边的流量不能超过其容量。
- $A(x)$ 是节点 $x$ 可以流向其他终端节点的最大流量。

树的累积度是指其节点中最大累积度的值。你的任务是找到给定树的累积度。

## 输入输出样例

### 输入

```
1
5
1 2 11
1 4 13
3 4 5
4 5 10
```

### 输出

```
26
```

## 说明/提示

原题中没有提到的数据范围：$T \le 4$，$\sum n \le 2\times 10 ^ 5$。

# 本题所要用到的知识点
1. **[树形动态规划（树形 DP）](https://blog.csdn.net/NiNg_1_234/article/details/143442136)**，建议先做一下 **[P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)** 再来看这篇题解；
2. **[二次扫描与换根法](https://blog.csdn.net/weixin_51307520/article/details/127926189)**。

### 前言
讲一下蓝书的做法。。。

# 思路
通过读题，我们很容易发现这是一道“不定根”的树形动态规划题,我们采用“二次扫描与换根法”来做。

首先，我们考虑朴素解法：枚举源点，然后计算水系流量。把源点作为树根，整个水系就从一颗无根树（$n$ 个点、$n - 1$ 条边的无向连通图）变成了一颗有根树（请自行画图）。这样，子节点只能从父节点获得水源，然后流向自己的子节点。每个节点的“流域”都是以该节点为根的子树。我们发现，这样非常符合树形动态规划的应用场景（每棵树都是一个子问题）。

设 $D_s[x]$ 表示在以 $x$ 为根的子树中，把 $x$ 作为源点，从 $x$ 出发流向**子树**的流量最大是多少。
$$\sum_{y\in Son(x) } \begin{cases} (D_s[y],c(x,y))\Leftrightarrow deg_y>1 \\ c(x,y)\Leftrightarrow deg_y=1 \end{cases}$$
对于枚举的每个源点 $x$，可以用树形动态规划在 $\Theta(n)$ 的时间内求出 $D_s$ 数组，并用 $D_s[x]$ 更新答案。所以，最终的时间复杂度为 $\Theta(n^2)$。下面的代码给出了一次树形动态规划的过程。在主函数中调用 $dynamic\_programming(s)$，完成后 $d[x]$ 就是所求的 $D_s[s]$。代码：

```cpp
void dynamic_programming(int u)
{
    vis[u] = true; // 标记已访问
    for (int i = pre[u]; i; i = a[i].ne) // 链式前向星遍历
    {
        int to = a[i].to;
        if (vis[to]) continue; // 如果已访问，跳过
        dynamic_programming(to); // 递归
        // 回溯过程中计算d数组
        if (deg[to] == 1) d[u] += a[i].len;
        else d[u] += min(d[to], a[i].len);
    }
    return;
}
```

考虑用“**二次扫描与换根法**”代替源点的枚举，可以在 $\Theta(n)$ 的时间内解决整个问题。首先，我们任选一个源点作为根节点，记为 $root$，然后采用上面的代码进行一次树形动态规划，求出 $D_{root}$ 数组，下文简写为：$D$ 数组。

设 $dp[x]$ 表示把 $x$ 作为源点，流向**整个水系**，流量的最大值。那初始条件是什么？显然，对于根节点 $root$，显然有 $dp[root]=D[root]$。

假设 $dp[x]$ 已经被正确求出了，我们考虑它的子节点 $y$，$dp[y]$ 尚未计算。$dp[y]$ 包含了两部分（请自行理解并画图）：
1. 从 $y$ 流向以 $y$ 为根的子树的流量，已经计算并保存在 $D[y]$ 中；
2. 从 $y$ 沿着到父节点 $x$ 的河道，进而流向水系中其它部分的流量。

因为把 $x$ 作为源点的总流量为 $dp[x]$，从 $x$ 流向 $y$ 的流量为 $min(D[y], c(x,y))$，所以从 $x$ 流向除了 $y$ 以外的其它部分的流量就是二者之差。于是，把 $y$ 作为源点，先流到 $x$，再流向其它部分的流量就是把这个“差”再与 $c(x,y)$ 取最小值后的结果。

当然，对于度数为一的节点 $x$，需要进行特判。
$$dp[y]=D[y]+\begin{cases} min(dp[x] - min(D[y],c(x,y)),c(x,y))\Leftrightarrow deg_x>1,deg_y>1 \\min(dp[x] - c(x,y),c(x,y))\Leftrightarrow deg_x>1,deg_y=1 \\c(x,y)\Leftrightarrow deg_x=1 \end{cases}$$
$dp[y]$ 就是把源点（树根）从 $x$ 换成 $y$ 后，流量的计算结果。这是一个自上而下的递推方程，通过一次深度优先遍历即可实现。代码：

```cpp
void dfs(int u)
{
    vis[u] = true; // 标记已访问
    for (int i = pre[u]; i; i = a[i].ne) // 链式前向星遍历
    {
        int to = a[i].to;
        if (vis[to]) continue; // 如果已访问过，跳过
        // 接下来按照方程里的去实现
        if (deg[u] == 1) dp[to] = d[to] + a[i].len;
        else if (deg[to] == 1) dp[to] = d[to] + min(dp[u] - a[i].len, a[i].len);
        else dp[to] = d[to] + min(dp[u] - min(d[to], a[i].len), a[i].len);
        dfs(to); // 递归
    }
    return;
}
```
到此，整片题解就结束了，最后附上完整代码：

```cpp
#include <bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int T, n, k = 0, pre[N], dp[N], d[N], deg[N]; bool vis[N];
struct Edge { int to, ne, len; } a[N << 1];
void add(int u, int v, int w) { a[++k] = (Edge){v, pre[u], w}; pre[u] = k; }
void dynamic_programming(int u)
{
    vis[u] = true;
    for (int i = pre[u]; i; i = a[i].ne)
    {
        int to = a[i].to;
        if (vis[to]) continue;
        dynamic_programming(to);
        if (deg[to] == 1) d[u] += a[i].len;
        else d[u] += min(d[to], a[i].len);
    }
    return;
}
void dfs(int u)
{
    vis[u] = true;
    for (int i = pre[u]; i; i = a[i].ne)
    {
        int to = a[i].to;
        if (vis[to]) continue;
        if (deg[u] == 1) dp[to] = d[to] + a[i].len;
        else if (deg[to] == 1) dp[to] = d[to] + min(dp[u] - a[i].len, a[i].len);
        else dp[to] = d[to] + min(dp[u] - min(d[to], a[i].len), a[i].len);
        dfs(to);
    }
    return;
}
signed main()
{
    cin >> T;
    while (T--)
    {
        k = 0;
        memset(vis, 0, sizeof vis); memset(dp, 0, sizeof dp);
        memset(d, 0, sizeof d); memset(deg, 0, sizeof deg);
        memset(pre, 0, sizeof pre);
        cin >> n;
        for (int i = 1, x, y, z; i < n; i++)
        {
            cin >> x >> y >> z;
            deg[x]++, deg[y]++;
            add(x, y, z); add(y, x, z);
        }
        int root = 1;
        dynamic_programming(root);
        memset(vis, 0, sizeof vis);
        dp[root] = d[root]; dfs(root);
        int ans = 0;
        for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
        cout << ans << endl;
    }
    return 0;
}
```

# 后记
有问题留言或私信问我。

---

## 作者：Rain_cyl (赞：1)

经典的换根 dp。

假设我们现在规定了一个根节点，所有水流都只能由父流向子，求每个点能往下流出的最大流量。

那这就是一个非常简单的树形 dp。设 $d[u]$ 表示节点 $u$ 往下能流出的最大流量，$u$ 的儿子分别是 $v_{1,2,...,k}$，则 $d[u]=\sum_{i=1}^{k} \min(w[u][v_i],d[v_i])$。

然而，在这道题中并没有规定根节点，即每个点都可能是根节点。但我们刚刚求的 $d$ 数组是有用的。任取一个点钦定为根，求出 $d$，然后 dfs 考虑每个点如果变成根会对答案有什么贡献。

假设 $f[u]$ 表示以 $u$ 为根的最大流量，显然有 $f[root]=d[root]$，其中 $root$ 是我们钦定的根。由于我们已经求出了每个点向下的最大流量，所以我们关注向父节点的最大流量。设 $u$ 的父节点为 $p$，当前我们把 $p$ 看做根，则 $p$ 向 $u$ 的流量就等于 $\min(w[p][u],d[u])$，所以 $p$ 向除 $u$ 以外的其他方向的总流量为 $f[p]-\min(w[p][u],d[u])$。如果把 $u$ 变为根，这份流量就可以继承给 $u$，作为他向上的流量。但这受到 $w[p][u]$ 的限制，所以向上的流量就是 $\min(w[p][u],f[p]-\min(w[p][u],d[u]))$。

综上，$f[u]=d[u]+\min(w[p][u],f[p]-\min(w[p][u],d[u]))$。

用两次 dfs，第一次自底向上推导出 $d$ 数组，第二次自上而下推导出 $f$ 数组即可。

---------------------------------------
代码如下，时间复杂度 $O(n)$。
```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=N*2,inf=0x3f3f3f3f;

int n,d[N],f[N],degree[N];
int h[N],e[M],ne[M],w[M],idx;

void add(int a,int b,int c){
    e[idx]=b;
    ne[idx]=h[a];
    w[idx]=c;
    h[a]=idx++;
}

int dfs_d(int u,int fa){
    if(degree[u]==1){
        d[u]=inf;
        return d[u];
    }
    d[u]=0;
    for(int i=h[u]; ~i; i=ne[i]){
        int j=e[i];
        if(j==fa) continue;
        d[u]+=min(dfs_d(j,u),w[i]);
    }
    return d[u];
}

void dfs_f(int u,int fa){
    for(int i=h[u]; ~i; i=ne[i]){
        int j=e[i];
        if(j==fa) continue;
        if(degree[j]==1) f[j]=min(w[i],f[u]-w[i]);
        else{
            f[j]=d[j]+min(w[i],f[u]-min(d[j],w[i]));
            dfs_f(j,u);
        }
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(h,-1,sizeof h);
        memset(degree,0,sizeof degree);
        idx=0;
        for(int i=1; i<n; i++){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c),add(b,a,c);
            degree[a]++,degree[b]++;
        }
        
        int root=1;
        while(root<=n&&degree[root]==1) root++;
        if(root>n){
            printf("%d\n",w[0]);
            continue;
        }
        
        dfs_d(root,-1);
        f[root]=d[root];
        dfs_f(root,-1);
        
        int res=0;
        for(int i=1; i<=n; i++) res=max(res,f[i]);
        printf("%d\n",res);
    }
    return 0;
}
```

---

## 作者：Lysea (赞：1)

### [P10974 Accumulation Degree](https://www.luogu.com.cn/problem/P10974)

蓝书上的换根板子。

先求出每个点流向子树的流量，表示为 $f_i$。

$$f_x=\sum \min\{v,f_y\}$$

（`\sum` 挂了）

再令 $g_i$ 表示以 $i$ 为根的流量，不难得到转移：

$$g_y=f_y+\min\{g_x-\min\{d,f_y\},d\}$$

还是解释一下吧。

首先 $y$ 流向子树的流量肯定为 $f_y$，而流向非子树的流量需要通过 $g_x$ 得到。

$g_x$ 的答案包含 $y$ 子树中的点，所以需要先减掉它，也就是 $g_x-\min\{d,f_y\}$。再进行流量限制，变为 $\min\{g_x-\min\{d,f_y\},d\}$。

代码：


```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e18
#define N 1000005
using namespace std;
struct star{
    int next,to,val;
}e[N];
int T,n,head[N],cnt,siz[N],f[N],g[N],ans;
void add(int u,int v,int w){
    e[++cnt].next=head[u];
    head[u]=cnt;
    e[cnt].to=v;
    e[cnt].val=w;
}
void dfs1(int x,int fa){
    int fl=0; f[x]=0;
    for(int i=head[x];i;i=e[i].next){
        int y=e[i].to,d=e[i].val;
        if(y==fa) continue;
        dfs1(y,x),fl=1;
        f[x]+=min(f[y],d);
    }
    if(!fl) f[x]=INF;
}
void dfs2(int x,int fa){
    ans=max(ans,g[x]);
    for(int i=head[x];i;i=e[i].next){
        int y=e[i].to,d=e[i].val;
        if(y==fa) continue;
        if(f[y]==INF) f[y]=0;
        g[y]=f[y]+min(g[x]-min(d,f[y]),d);
        dfs2(y,x);
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>T;
    while(T--){
        cin>>n,ans=0;
        for(int i=1;i<=cnt;i++) head[i]=0;
        cnt=0;
        for(int i=1,u,v,w;i<n;i++){
            cin>>u>>v>>w;
            add(u,v,w),add(v,u,w);
        }
        dfs1(1,0),g[1]=f[1],dfs2(1,0);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：dci66666 (赞：0)

这个题不是特别难，就是细节有亿点多。本人将尽量详细讲解。
## 思路
怎么想到换根？

我们这么定义 $A(x)$：

- 树的每一条边都有一个正容量。
- 树中度为 $1$ 的节点被称为终端节点（也就是叶子节点）。
- 每条边的流量不能超过其容量。
- $A(x)$ 是节点 $x$ 可以流向其他终端节点的最大流量（和的流量最大）。

树的累积度是指其节点中最大累积度的值。你的任务是找到给定树的累积度（摘自题面）。

这里重写了一篇。

所有的终端节点只能是根节点和叶子节点（这个是因为只有这些点有可能度为一）。

当一个节点作为答案时，考虑它和它子节点的答案差别。

它子节点和它子节点的子树内终端的最大容量一定大于等于它对它子节点子树内终端的最大容量。显然，可能中间这条边撑不住那么大贡献。而对于子树外的终端节点就一定大于等于它子节点对于子树外终端节点的贡献。

我们发现这题的瓶颈就是父节点和子节点的这条边。

这条边选中点从上到下（从父到子），会使父节点的除自己子树内的所有贡献与边权取较小值。从子到父会时自己子树内节点的最大贡献和与边权取较小值。

我们钦定顺序为从父到子（毕竟根节点知道），对于根及所有节点子树内的答案我们可以算出来，在父亲节点考虑，对于儿子节点，可以将自己的贡献剪掉子节点子树内贡献与连边取较小值（其实就是实际贡献啦），得到儿子子树之外的节点实际贡献和，这个子树外节点的贡献的所有点对于子节点来说都会经过父子之间的这条边（毕竟这个父节点是它到每个终端节点最近公共祖先路径上的必经节点），所以会取较小值（画个图会好理解得多），那么可以列出式子。

设 $u,v$ 表示父与子节点，数组 $size$ 表示子节点子树内的贡献。可列式子 $dp[v]=min(dp[u]-min(size[v],edge[i]),edge[i])+size[v]$。

第一项即子节点对于子树之外的贡献，第二项是子树内的贡献。

由于我们从上到下遍历的，所以子节点处理之前父节点一定被处理好了，而 $size$ 我们早都预处理好了。

到此，我们写成了一个换根。

现在可以写代码了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+50,M=2e6+50;
#define ll long long
ll size[N],dp[N];
ll edge[M];
int ver[M],head[N],Next[M],tot,son[N];
void add(int x,int y,ll z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
	ver[++tot]=x,edge[tot]=z,Next[tot]=head[y],head[y]=tot;
}
int n,t;
void dfs1(int x,int fa){
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(y==fa)continue;
		dfs1(y,x);
		if(son[y]>1)size[x]+=min(edge[i],size[y]);
		else size[x]+=edge[i];
	}
}
void dfs2(int x,int fa){
	for(int i=head[x];i;i=Next[i]){
		int y=ver[i];
		if(y==fa)continue;
		if(son[x]==1)dp[y]=size[y]+edge[i];
		else if(son[y]>1)dp[y]=min(dp[x]-min(size[y],edge[i]),edge[i])+size[y];
		else dp[y]=min(dp[x]-edge[i],edge[i])+size[y];
		dfs2(y,x);
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		tot=0;
		for(int i=1;i<=n;i++)head[i]=0,size[i]=0,dp[i]=0,son[i]=0;
		for(int i=1;i<n;i++){
			int x,y;
			ll z;
			scanf("%d%d%lld",&x,&y,&z);
			son[x]++,son[y]++;
			add(x,y,z);
		}
		dfs1(1,0);
		dp[1]=size[1];
		dfs2(1,0);
		ll maxn=dp[1];
		for(int i=2;i<=n;i++){
			maxn=max(maxn,dp[i]);
		}
		printf("%lld\n",maxn);
	}
    return 0;
}
```

---

## 作者：lyas145 (赞：0)

题目在[这里](https://www.luogu.com.cn/problem/P10974)。

## 解题思路

这是一个树上问题，并且我们可能需要每个节点的 $A(x)$（这里的 $A(x)$ 的含义与题目相同），考虑使用**换根 dp**。

我们将节点 $1$ 作为树的根节点。

设 $deg_u$ 表示节点 $u$ 的度数，$c_{u,v}$ 表示 $u$ 和 $v$ 之间的边的容量，$sum_u$ 表示从 $u$ 流到以 $u$ 为根的子树中的终端节点的最大流量。

$sum_u$ 很好求：

$$sum_u=\sum\limits_{v\in son(u)}
\begin{cases}
c_{u,v} & deg_v=1\\
\min(c_{u,v},sum_v) & deg_v\ne 1
\end{cases}
$$

再设 $f_u$ 表示 $A(u)$。

那么 $f_1=sum_1$。

考虑如何转移。

假设我们要从 $f_u$ 转移到 $f_v$（$v\in son(u)$）。

可以发现：**度数为 $1$ 的节点**（终端节点）在这题中非常特殊，因此我们需要对她们进行一些特殊的处理。

有这么两个特殊情况：  
- $deg_u=1$
- $deg_v=1$

如果 $deg_u=1$，那么节点 $u$ **一定没有父亲节点**且**只有 $v$ 这一个子节点**。

也就是这个样子：

```
   u
   |
   v
  /...
...
```

显然：$f_v=sum_v+c_{u,v}$。

如果 $deg_v=1$。

也就是这个样子：

```
 ...
  |
  u
 /...
v
```

转移过来的话，接受流量的节点会少一个，并且从节点 $v$ **只能通过一条边流出去**，所以 $f_v$ **不会超过 $c_{u,v}$**；如果不考虑 $c_{u,v}$ 的大小，那么从 $v$ 流到 $u$，再流到其他终端节点（不包括 $v$），那么**最大流量也只会是 $f_u-c_{u,v}$**。

于是可得：$f_v=\min(c_{u,v},f_u-c_{u,v})$。

接下来考虑**一般情况**。

```
  u
...\
    v
   /...
 ...
```

$v$ 流到**以 $v$ 为根节点的子树内**的终端节点的流量很好搞，就是 $sum_v$。

然后是 $v$ 流到**以 $v$ 为根节点的子树以外**的终端节点的流量（为了方便讲述，我们将其设为 $k$）。

$k$ 的大小是会受到 $c_{u,v}$ 的影响的：$k\le c_{u,v}$；如果不考虑 $c_{u,v}$ 的大小，那么从 $v$ 流到 $u$，再从 $u$ 流向其他终端节点，**其流量最大也只有 $f_u-\min(c_{u,v},sum_v)$**。

于是可得：$f_v=sum_v+\min(c_{u,v},f_u-\min(c_{u,v},sum_v))$。

你会发现一般情况和 $deg_v=1$ 的情况的分析思路蛮像的，虽然也有一点差异。

综上所述，完整的转移方程为（$v\in son(u)$）：

$$f_v=\begin{cases}
sum_v+c_{u,v} & deg_u=1\\
\min(c_{u,v},f_u-c_{u,v}) & deg_v=1\\
sum_v+\min(c_{u,v},f_u-\min(c_{u,v},sum_v)) & deg_u\ne 1\land deg_v\ne 1
\end{cases}$$

没了，代码登场！

## 码儿

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5,M=N<<1;
int T,n;
ll ans;
int deg[N];
ll sum[N],f[N],c[M];
int h[N],e[M],ne[M],idx;
inline int read() {     //快读，没啥好看的。
	int x=0;
	char c=getchar();
	while (!isdigit(c)) {c=getchar();}
	while (isdigit(c)) {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x;
}
void add(int a,int b,int c) {     //链式前向星。
	e[idx]=b;::c[idx]=c;ne[idx]=h[a];h[a]=idx++;
}
void _dfs(int u,int fa) {    //预处理出 sum 的 dfs。
	for (int i=h[u];i;i=ne[i]) {
		int v=e[i];
		if (v==fa) {continue;}
		_dfs(v,u);
		if (deg[v]==1) {sum[u]+=c[i];}
		else {sum[u]+=min(sum[v],c[i]);}
	}
}
void dfs(int u,int fa) {     //换根 dp。
	for (int i=h[u];i;i=ne[i]) {
		int v=e[i];
		if (v==fa) {continue;}
		if (deg[u]==1) {f[v]=c[i]+sum[v];}
		else if (deg[v]==1) {f[v]=min(f[u]-c[i],c[i]);}
		else {f[v]=sum[v]+min(f[u]-min(c[i],sum[v]),c[i]);}
		ans=max(ans,f[v]);   //统计答案。
		dfs(v,u);
	}
}
int main() {
	T=read();
	while (T--) {
		idx=1;
		n=read();
		for (int i=1;i<n;i++) {
			int x=read(),y=read(),z=read();
			add(x,y,z);
			add(y,x,z);
			deg[x]++;deg[y]++;
		}
		_dfs(1,0);
		ans=f[1]=sum[1];
		dfs(1,0);
		printf("%lld\n",ans);
		for (int i=1;i<=n;i++) {deg[i]=sum[i]=f[i]=0;}
		for (int i=1;i<idx;i++) {h[i]=0;}
	}
	return 0;
}
```

Thanks for reading！

---

## 作者：Brilliant11001 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Brilliant11001/p/18572953)

NOIP 前写题解加 rp（

## [题目传送门](https://www.luogu.com.cn/problem/P10974)

### 题目大意：

给定一颗无根树，有一个节点是源点，度数为 $1$ 的点是汇点，树上的边有最大流量。除源点和汇点外，其它点不储存水，即**流入该点的水量之和等于从该点流出的水量之和**。整个水系的流量定义为原点**单位时间内能发出的水量**。

现在需要求出：在流量不超过最大流量的前提下，选取哪个点作为源点，整个水系的流量最大，输出最大值。

### 思路：

朴素的想法是枚举某个点作为源点，然后做树形 dp，设 $f_u$ 表示从点 $u$ 往下流向子树的最大流量，不难得出状态转移方程：

$$
f_u = \sum\limits_{j\in Son(u)}\begin{cases}\min(w_i, f_j) & \deg_j > 1\\w_i & \deg_j = 1\end{cases}
$$

对于每个点都这样做一遍，取 $\max$，时间复杂度 $O(n^2)$。

暴力 $\texttt{Code:}$

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010, M = 400010;
typedef long long ll;
int T, n;
int h[N], e[M], ne[M], w[M], idx;
int deg[N];
ll f[N];

void init() {
    for(int i = 1; i <= n; i++)
        deg[i] = 0, h[i] = -1;
}

inline void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dfs(int u, int fa) {
    f[u] = 0;
    for(int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == fa) continue;
        dfs(j, u);
        if(deg[j] == 1) f[u] += w[i];
        f[u] += min(f[j], (ll)w[i]);
    }
}

void solve() {
    scanf("%d", &n);
    init();
    for(int a, b, c, i = 1; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
        deg[a]++, deg[b]++;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) dfs(i, -1), ans = max(ans, f[i]);
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
```

因为这个题是一个无根树，而我们又要枚举根节点，所以不难想到用换根 dp 来代替源点的枚举。

所以考虑用换根 dp 来优化。

来回顾一下换根 dp 的基本思路：

1. 第一次 dfs，任选一个点为根进行方才的树形 dp；
2. 第二次 dfs，从相同的根出发，再扫描一遍从父节点向子结点更新信息，这里多半会用到剔除贡献的问题，要么记最大 / 次大值和具体从哪个点更新（这个主要用于最大 / 最小的不满足可减性的信息），要么从第一遍 dfs 的信息更新处倒推（这个一般用于满足可减性的信息）。

对应到这个题上就是思考子节点流向父节点的信息怎么计算。

先画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/iuddqzma.png)

这里 $g_u$ 表示 $u$ 为源点的最大流量。

这道题的信息显然具有可减性。

如图，我们可以考虑先去掉 $j$ 子树对 $g_u$ 的贡献得到以 $u$ 为源点的其他贡献，**然后这一部分实际就是从 $j$ 往上流的最大流量**，直接和 $f_j$ 相加就得到了 $g_j$。

但是这里有个魔鬼细节，需要考虑节点的度数，因为度数为 $1$ 的点在第一遍 dfs 时是直接加上的 $w_i$，所以在去掉贡献的时候需要判一下。父节点也基本同理。

那么这道题就结束了，时间复杂度 $O(n)$。

$\texttt{AC Code:}$

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200010, M = 400010;
typedef long long ll;
int T, n;
int h[N], e[M], ne[M], w[M], idx;
int deg[N];
ll f[N], g[N];

void init() {
    for(int i = 1; i <= n; i++)
        deg[i] = 0, h[i] = -1;
}

inline void add(int a, int b, int c) {
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void dfs(int u, int fa) {
    f[u] = 0;
    for(int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == fa) continue;
        dfs(j, u);
        if(deg[j] == 1) f[u] += w[i];
        else f[u] += min(f[j], (ll)w[i]);
    }
}

void dfs2(int u, int fa) {
    for(int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == fa) continue;
        g[j] = f[j];
        if(deg[u] == 1) g[j] += w[i];
        else if(deg[j] == 1) g[j] += min((ll)w[i], g[u] - (ll)w[i]);
        else g[j] += min((ll)w[i], g[u] - min((ll)w[i], f[j]));
        dfs2(j, u);
    }
}

void solve() {
    scanf("%d", &n);
    init();
    for(int a, b, c, i = 1; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
        deg[a]++, deg[b]++;
    }
    dfs(1, -1);
    g[1] = f[1];
    dfs2(1, -1);
    ll ans = 0;
    for(int i = 1; i <= n; i++)
        ans = max(ans, g[i]);
    printf("%lld\n", ans);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
```

---

## 作者：wdsjl (赞：0)

# P10974题解
## 分析
考虑暴力，枚举源点，然后再树形 dp 计算流量，然后记录下以 $x$ 为源头 $x$ 流向子树的最大流量。

时间复杂度为 $O( n^{2} )$ 显然不行。

## 优化
我们还是先随便找一个点作为根，求一下以 $x$ 为源头 $x$ 流向子树的最大流量记为 $d$ 数组。

然后我们用数组 $f_{i}$ 表示以 $i$ 为原点流向**整个水系**的的最大流量，显然我们作为根的点 $d_{root} = f_{root}$ 因为我们已经求过一次流向子树的最大流量为 $d$ 数组。我们可以从此只用一次 dp 来推出。称为**二次扫描与换根法**。

如果 $f_{x}$ 已经被求出， $y$ 为其子节点，且尚未计算，那么：

- 从 $y$ 流向以它为根的子树的流量，已经存在 $d_{y}$ 中。
- 从 $y$ 沿着流向父节点 $x$ 的河道，为父节点 $f_{x}$ 减去流向 $y$ 的流量。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, M = 2 * N, INF = 0x3f3f3f3f;
int n;
int h[N], e[M], ne[M], w[M], ind;
int deg[N], d[N], f[N], v[N];

void add(int a, int b, int c) {
	e[ind] = b, w[ind] = c, ne[ind] = h[a], h[a] = ind++;
}

void dp(int x) {
	v[x] = 1;
	d[x] = 0;
	for (int i = h[x]; i; i = ne[i]) {
		int y = e[i];
		if (v[y])continue;
		dp(y);
		if (deg[y] == 1)d[x] += w[i];
		else d[x] += min(d[y], w[i]);
	}
}

void dfs(int x) {
	v[x] = 1;
	for (int i = h[x]; i; i = ne[i]) {
		int y = e[i];
		if (v[y])continue;
		if (deg[x] == 1)f[y] = d[y] + w[i];
		else if (deg[y] == 1)
			f[y] = d[y] + min(f[x] - w[i], w[i]);
		else
			f[y] = d[y] + min(f[x] - min(d[y], w[i]), w[i]);
		dfs(y);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(h, 0, sizeof(h));
		ind = 1;
		memset(deg, 0, sizeof(deg));
		for (int i = 1; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			add(a, b, c), add(b, a, c);
			deg[a]++, deg[b]++;
		}
		int root = 1;
		memset(v, 0, sizeof v);
		dp(root);
		memset(v, 0, sizeof v);
		f[root] = d[root];
		dfs(root);
		int ans = 0;
		for (int i = 1; i <= n; i++)ans = max(ans, f[i]);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

一个简单的换根 dp。

## 换根DP

推销 ~~高()~~ 低仿 OI-wiki [https://ntsc-yrx.github.io/oi-beats/site](https://ntsc-yrx.github.io/oi-beats/site) 欢迎嘲讽。

有些时候，题目要求最优化一个值，但是它和选择哪个节点作为根节点，或者是从那个节点开始扩散有关，时间复杂度有要求我们不能采用 $n$ 次 dfs（树形 dp），这时我们就需要使用换根 dp 了。

换根 dp 是树形 dp 的一种，它通过第一遍dfs得到的数据（如将 $1$ 作为根节点跑出的各个节点的 dp 值），在第二次 dfs 中加以利用，通过转移式快速根据已有信息求出将邻接点作为根节点时的答案。

## 本题

首先求出 $f_x$ 是其儿子可以到 $x$ 节点的流量最大和，定义 $g_x$ 为每个节点的累积度。

下设 $x$ 是 $v$ 的一个儿子，我们要从 $g_v$ 推导出 $g_x$。

我们可以得出：$g_x=f_x+\min(w(v,x),从父亲 v 来的流量最大和)$。

$v 的流量最大和=g_v-min(f_v,w(v-x))$，$w(v-x)$ 代表边权。

```C++
void add(itn a,itn b,int c){
    e[a].push_back({b,c});
    e[b].push_back({a,c});
}


void dfs(int x,int fa){
	int cnt=0;
    for(auto v:e[x]){
        if(v.v==fa)continue;
        cnt++;
        dfs(v.v,x);
        f[x]+=min(v.w,f[v.v]);
    }
    if(!cnt)f[x]=INF;
}


void dfs2(int x,int fa){
    for(auto v:e[x]){
        if(v.v==fa)continue;
        if(x==1&&e[x].size()==1){
        	g[v.v]=v.w+f[v.v];	
		}else{
	        if(f[v.v]<INF)g[v.v]=f[v.v];
	        g[v.v]+=min(v.w,g[x]-min(f[v.v],v.w));
			
		}
	    dfs2(v.v,x);
    }
}

itn n;

void init(){
	for(int i=1;i<=n;i++){
		g[i]=0;
		f[i]=0;
		int sz=e[i].size();
		while(sz--)e[i].pop_back();
	}
}

void solve(){
	
	init();
	n=rd;
    for(int i=1;i<n;i++){
        itn a=rd,b=rd,c=rd;
        add(a,b,c);
    }


    dfs(1,0);
    g[1]=f[1];
    dfs2(1,0);

    itn ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,g[i]);
    }


    cout<<ans<<endl;
}
```

---

