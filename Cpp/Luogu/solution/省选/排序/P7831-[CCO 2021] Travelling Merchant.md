# [CCO 2021] Travelling Merchant

## 题目描述

一个国家有 $n$ 个城市和 $m$ 条单向道路，一个旅行商在这些城市之间旅行。

第 $i$ 条道路从城市 $a_i$ 到城市 $b_i$，只有当他的资产不少于 $r_i$ 元才可以走这条道路，走过这条道路之后他的资产会增加 $p_i$ 元。

他希望自己可以永远不停的游走下去，于是他想知道从任意一个城市出发至少需要多少元初始资产。

## 说明/提示

#### 样例 #1 解释
以第 $2$ 座城市为例：从第 $2$ 座城市出发，初始资产 $3$ 元，则可以在第 $2, 1, 3$ 三座城市无限绕圈。
#### 数据范围
对于 $\frac{2}{7}$ 的数据，$2 \leq n, m \leq 2 \times 10^3$；

对于另 $\frac{15}{49}$ 的数据，$p_i = 0$；

对于 $100\%$ 的数据，$2 \leq n, m \leq 2 \times 10^5$，$1 \leq a_i, b_i \leq n$，$a_i \neq b_i$，$0 \leq r_i, p_i \leq 10^9$，**保证没有自环但可能有重边**。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D2T1

## 样例 #1

### 输入

```
5 5
3 1 4 0
2 1 3 0
1 3 1 1
3 2 3 1
4 2 0 2```

### 输出

```
2 3 3 1 -1```

# 题解

## 作者：bsTiat (赞：43)

## 题目分析
我们用 $ ans_i $ 表示从城市 $ i $ 出发可以一直走下去的最小花费，所有  $ ans_i $ 初始赋值为 $ inf $，方便更新最小值，最后输出的时候判断一下如果为  $ inf $ 就输出 $ -1 $。

首先，对于出度为 $ 0 $ 的城市，我们可以直接将其删去，因为无论有多少钱都不可能一直走下去，其答案即为 $ -1 $。

那么，剩下的点都有出边，所以剩下的点一定有答案。

### 最初的思路——错误的想法

依次考虑从城市 $ i $ 开始，但是我们可以发现，城市 $ i $ 的答案不能一开始就求出，如果从城市 $ i $ 开始，那么我们每经过的一个城市都可能对城市 $ i $ 的答案造成更新，进而要回溯到之前的每一个城市更新，时间复杂度太大会超时。

### 正确的想法

换一种思路，当有多少钱时，从城市 $ i $ 出发一定能一直走下去呢？当我们的钱数为当前最大的 $ r_i $ 时，可以一直走下去，因为当前的 $ r_i $ 是全场最大的，且 $ p_i $ 均不小于 $ 0 $，所以我们就可以一直走，不可能存在不能通行的道路。

可以采用一种类似于 **拓扑排序** 的算法，结合 **贪心** 思想。

1. 把所有所有边按 $ r_i $ 排个序，每次取出 $ r $ 最大的那条边 $ edge_i $，设这条边起点为 $ u $，更新 $ u $ 的答案 $ ans_u = \min(ans_u,r_i) $。

2. 如果这个点还有其它出边，那么我们就先记下这个答案，并删掉这条边。

3. 如果这个点没有其它出边了，那么这个点答案就是确定的，将这个点入队，删掉这个点，这时可能会出现新的没有出度的点，它们的答案也确定了。

4. 每一轮入队的点，在处理下一条边之前先处理，取出这个点的每一条进入的边 $ edge_i $，设其起点为 $ u $，终点为 $ v $，更新 $ u $ 的答案 $ ans_u=\min(ans_u,\max(r_i,ans_v-p_i)) $。 删去这条边，注意，在这过程中可能还会出现新的没有入度的点，也要记得进队。

5. 重复如此，直到没有点。

### 算法实现

$ vis_i $ 表示第 $ i $ 条边是否被删去，$ dep_i $ 表示这条边的出度。


#### 存储
```cpp
struct node{
	int a,b,r,p;
	bool operator<(const node &x)const{	//因为等下是用链式前向星存边
		return r<x.r;					//读的时候是逆序的，所以按升序排
	}									//依次遍历边的时候再反过来
}edge[N];
queue<int>q;
int ans[N],vis[N],n,m,dep[N];
int head[N],nxt[N],to[N],tot;
inline void add(int &x,int &y){		
	//链式前向星存边的编号，y不是终点,而是边的编号
	to[++tot]=y;nxt[tot]=head[x];head[x]=tot
}
```

#### 读入&排序
```cpp
memset(ans,0x3f,sizeof(ans));
n=read();m=read();
for(i=1;i<=m;++i){
	edge[i].a=read();edge[i].b=read();
	edge[i].r=read();edge[i].p=read();
	++dep[edge[i].a];
}
sort(edge+1,edge+1+m);
for(i=1;i<=m;++i) add(edge[i].b,i);		//存储每个点的入边的编号
for(i=1;i<=n;++i) if(!dep[i])q.push(i);	//将没有出边的点入队
```

#### 每次入队的点的处理

```cpp
while(!q.empty()){
	u=q.front();q.pop();	
	for(j=head[u];j;j=nxt[j]){			 //k存的是边的编号
     		k=to[j];if(vis[k])continue; //如果这条边被删了就跳过
		vis[k]=1;--dep[edge[k].a];		 //处理当前点
		if(!dep[edge[k].a])q.push(edge[k].a);
		if(ans[u]!=INF)					 //更新答案
        		ans[edge[k].a]=min(ans[edge[k].a],max(edge[k].r,ans[u]-edge[k].p));
	}
}
```

#### 依次处理每条边

```cpp
for(i=m;i>=1;--i){					    //与每次入队的点的处理的类似
	if(!vis[i]){
		vis[i]=1;--dep[edge[i].a];
		if(!dep[edge[i].a])q.push(edge[i].a);
		ans[edge[i].a]=min(ans[edge[i].a],edge[i].r);//更新答案
	}
}
```

## 完整代码
```cpp
#include<bits/stdc++.h>
# define INF (0x3f3f3f3f)
# define reg register
# define min(x,y) (x<y?x:y)
# define max(x,y) (x>y?x:y)
# define N (200005)
using namespace std;
inline int read(){
	reg char c=getchar();reg int sum=0,f=1;
	while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){sum=(sum<<3)+(sum<<1)+(c^48);c=getchar();}
	return sum*f;
}
struct node{
	int a,b,r,p;
	bool operator<(const node &x)const{
		return r<x.r;
	}
}edge[N];
queue<int>q;
int ans[N],vis[N],n,m,dep[N];
int head[N],nxt[N],to[N],tot;
inline void add(int &x,int &y){
	to[++tot]=y;nxt[tot]=head[x];head[x]=tot;
}
int main(){
	reg int i,j,k,u,v;
	memset(ans,0x3f,sizeof(ans));
	n=read();m=read();
	for(i=1;i<=m;++i){
		edge[i].a=read();edge[i].b=read();
		edge[i].r=read();edge[i].p=read();
		++dep[edge[i].a];
	}
	sort(edge+1,edge+1+m);
	for(i=1;i<=m;++i) add(edge[i].b,i);
	for(i=1;i<=n;++i) if(!dep[i])q.push(i);
	for(i=m;i>=1;--i){
		while(!q.empty()){
			u=q.front();q.pop();
			for(j=head[u];j;j=nxt[j]){
				k=to[j];if(vis[k])continue;
				vis[k]=1;--dep[edge[k].a];
				if(!dep[edge[k].a])	q.push(edge[k].a);
				if(ans[u]!=INF)
					ans[edge[k].a]=min(ans[edge[k].a],max(edge[k].r,ans[u]-edge[k].p));
			}
		}
		if(!vis[i]){
			vis[i]=1;--dep[edge[i].a];
			if(!dep[edge[i].a])q.push(edge[i].a);
			ans[edge[i].a]=min(ans[edge[i].a],edge[i].r);
		}
	}
	for(i=1;i<=n;++i) printf("%d ",(ans[i]==INF?-1:ans[i]));
	return 0;
}
```


这是本蒟蒻第一次写题解，如有不足多多见谅，有意见或错误欢迎提出。

---

## 作者：uniqueharry (赞：25)

货真价实的好题。

如果定义 $f_u$ 表示从 $u$ 出发能不停走下去的最少初始资产，很容易得到一个这样的转移：$f_u = \min\limits_{(u, v) \in E}\{f_u,\max(r(u, v), f_v - p(u, v))\}$。但是图上有环，不能直接转移。我们尝试发现一些性质：

1. 如果你从某点开始走，初始资产为所有边 $r$ 的最大值，那你自然可以畅行无阻。
2. 出度为 $0$ 的点一定无解。由此得出形如 $(u, v)$ 的边若 $v$ 出度为 $0$，则该边没有意义，可以删去。

综合以上两个性质得出做法：

1. 将所有出度为 $0$ 的节点入队。
2. 按 $r$ 从大到小的顺序考虑每条边。首先进行一次“拓扑排序”。具体来说，取出队头 $v$，遍历 $v$ 在反图上的出边 $(v, u, r, p)$。若 $v$ 有解，则用最开始提到的转移式子来更新 $f_u$。因为此时 $v$ 已经入队，$f_v$ 已经确定，所以可以用这条边更新。同时，这条边被使用之后不再具有价值，可以退出历史的舞台。删去这条边之后把 $u$ 的出度 $-1$，若 $u$ 的出度变为 $0$ 则将其入队。
3. 从大到小考虑第 $i$ 条边时：做完第二步之后，若第 $i$ 条边仍未被删除则用 $r_i$ 更新 $f_{u_i}$，并将 $u_i$ 的出度 $-1$，若变为 $0$ 则将其入队。为啥可以这样更新呢？我们发现一条边被删除，当且仅当沿着这条边最终会走到出度为 $0$ 的点，也就是无解。所以如果第 $i$ 条边未被删除则代表着“在未被删除的边构成的图上，沿着第 $i$ 条边并不会走到出度为 $0$ 的点”，同时边是按 $r$ 从大到小的顺序考虑的，以 $r_i$ 为初始资产不会受到未被删除的边的 $r$ 的限制。所以此时可以更新。
4. 第 3 步使得每个节点最终都会入队，解决了一开始“有环就无法转移”的问题。

由于拓扑排序中每个节点只会入队出队各一次，所以复杂度瓶颈在排序：$O(m \log m)$。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5, inf = 0x3f3f3f3f;
int n, m, out[N];
struct Edge{
	int u, v, id, r, p;
	bool operator < (const Edge &k) const {
		return r > k.r;
	}
}E[N];
bool vis[N];
int head[N], cnt;
struct edge{
	int nxt, to, id, r, p;
}e[N << 1];
void add(int u, int v, int id, int r, int p){
	e[++cnt].nxt = head[u], e[cnt].to = v, e[cnt].id = id, e[cnt].r = r, e[cnt].p = p, head[u] = cnt;
}
int ans[N];
queue <int> q;
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++) scanf("%d%d%d%d", &E[i].u, &E[i].v, &E[i].r, &E[i].p), E[i].id = i, add(E[i].v, E[i].u, E[i].id, E[i].r, E[i].p), out[E[i].u]++;
	memset(ans, 0x3f, sizeof(ans));
	for(int i = 1; i <= n; i++) if(!out[i]) q.push(i);
	sort(E + 1, E + m + 1);
	for(int i = 1; i <= m; i++){
		while(!q.empty()){
			int v = q.front(); q.pop();
			for(int i = head[v]; i; i = e[i].nxt){
				if(vis[e[i].id]) continue;
				vis[e[i].id] = true;
				int u = e[i].to;
				if(ans[v] != inf) ans[u] = min(ans[u], max(e[i].r, ans[v] - e[i].p));
				out[u]--; if(!out[u]) q.push(u);
			}
		}
		if(!vis[E[i].id]){
			vis[E[i].id] = true, ans[E[i].u] = min(ans[E[i].u], E[i].r);
			out[E[i].u]--; if(!out[E[i].u]) q.push(E[i].u);
		}
	}
	for(int i = 1; i <= n; i++) printf("%d ", ans[i] == inf ? -1 : ans[i]);
	return 0;
}
```

---

## 作者：翼德天尊 (赞：7)

好高妙。

首先路径的行走约束要求的是最大值，大概可以想到按照约束大小顺序加边/删边。

其次能够不断行走一定是跟环相关的，所以走不到环上的节点都可以被先行删除了。

之后我们肯定是要做一个类似 dp 转移的东西的，比如我们设 $dp_u$ 表示从 $u$ 出发需要的最小资产，则对于每条边 $(u,v)$ 有：
$$
dp_u=\min(dp_u,\max(r_{(u,v)},dp_v-p_{(u,v)}))
$$
所以现在我们要做的其实就是，利用第一点性质，找到一个序去掉环的限制，从而进行转移。

观察转移中的 $\max$ 式子，考虑在何时可以拆掉它、减少决策。发现其实 $dp$ 值一定是 $\le r_{\max}$ 的，再大就冗余了。故对于 $r_{max}$ 这条边，在 $\max$ 式子中一定可以作为决策，所以我们可以直接利用这条边 $(u,v)$ 对 $u$ 进行一次转移，之后将其删除，因为边的作用只是转移出点，它的作用已经达到了。

考虑若一个点 $u$ 在某一时刻存在出边（设当前图上 $r_{\max}=k$），则说明它此时仍然可以到达环 $r_{\max}$ 至多为 $k$ 的环，真实的 $dp_u$ 仍然一定不大于 $r_{\max}$，所以只要当前图上没有出现出度为 $0$ 的节点，我们就可以不断取剩余边中 $r_i$ 最大的边进行转移；直到出现出度为 $0$ 的节点 $u$ 时，说明 $u$ 的答案一定确定了，此时我们就可以从 $u$ 向其所有前驱 dp 转移，不断在反图上做拓扑排序，把一连串的出度为 $0$ 的节点全部处理掉。

不断重复这个过程即可处理完整张图，时间复杂度 $O(n+m)$，其实还有个排序的 log。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,in[N],dp[N];
bool vis[N];
struct Edge{
    int to[N<<1],next[N<<1],head[N],tot,r[N<<1],p[N<<1];
    void adde(int u,int v,int rr,int pp){
        to[++tot]=v,next[tot]=head[u],head[u]=tot,r[tot]=rr,p[tot]=pp;
    }
}S;
struct node{
    int u,v,r,p,id;
    node (int u=0,int v=0,int r=0,int p=0,int id=0)
        :u(u),v(v),r(r),p(p),id(id){}
}d[N];
int read(){
    int w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
}
bool cmp(node x,node y){
    return x.r>y.r;
}
queue<int> q;
int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    memset(dp,0x3f,sizeof(dp));
    n=read(),m=read();
    for (int i=1;i<=m;i++){
        int u=read(),v=read(),r=read(),p=read();
        S.adde(v,u,r,p),++in[u];
        d[i]=node(v,u,r,p,i);
    }
    for (int i=1;i<=n;i++)
        if (!in[i]) q.push(i);
    sort(d+1,d+1+m,cmp);
    for (int f=1;f<=m;f++){
        // cout<<"----------- "<<f<<" ------------\n";
        while (!q.empty()){
            int u=q.front();
            // cout<<u<<"\n";
            q.pop();
            for (int i=S.head[u];i;i=S.next[i]){
                if (vis[i]) continue;
                vis[i]=1;
                int v=S.to[i];
                --in[v];
                if (dp[u]<=1e9) dp[v]=min(dp[v],max(S.r[i],dp[u]-S.p[i]));
                if (in[v]==0) q.push(v);
            }
        }
        if (vis[d[f].id]) continue;
        vis[d[f].id]=1,--in[d[f].v];
        // cout<<"delete : "<<d[f].v<<"\n";
        dp[d[f].v]=min(dp[d[f].v],d[f].r);
        if (in[d[f].v]==0) q.push(d[f].v);
    }
    for (int i=1;i<=n;i++)
        if (dp[i]>1e9) cout<<-1<<" ";
        else cout<<dp[i]<<" ";
    puts("");
    return 0;
}
```

---

## 作者：liangbowen (赞：5)

[problem](https://www.luogu.com.cn/problem/P7831) & [blog](https://www.cnblogs.com/liangbowen/p/17577222.html)。

妙妙题。单杀了，来写篇题解。

---

下文中 $ans_u$ 表示从 $u$ 点出发的答案。

考虑直接做。发现更新任何一个点，都可能会对一堆点造成影响，$O(n^2)$ 无法接受。

一些简单的性质：不能进入一个环的 $ans_u=-1$。否则，对于 $(u,v,r,p)$，$r$ 是最大的 $r$，那么只要 $ans_u\ge r$，$u$ 就可以随便走。

这启示我们跑类似于拓扑排序的东西。

+ 先跑一遍拓扑，把 $-1$ 搞出来。
+ 按 $r_i$ 从大到小排序，每次取出这个最大的 $r$，如果它没有被转移过，$ans_u\gets r$，然后把这条边去掉。
+ 去掉后跑拓扑，由于去掉了边，所以一些环就会破掉了，于是把所有能到它的点（也就是建反图后，$u$ 能到的点）更新 $ans_u\gets \max\{r_i, ans_v-p_i\}$，同时把这条边删掉。
+ 这里是**没有出边**就入队。

每一条边显然只与 $(u,v)$ 有关，实际的正确性取决于枚举的顺序。这条边没被删，当且仅当它在一个环里。找到最大的 $r_i$，$u_i$ 想要过掉这条边，确实得有这个限制。如果我能过掉，那我顺着这个环一直走显然正确。所以用类似于倒着反推的方式，一定能得到正确的答案。

实现方面直接建反图。删边直接标记一下就行。

[代码](https://www.luogu.com.cn/paste/kb523r3b)，时间复杂度 $O(m\log m)$，瓶颈在排序。


---

## 作者：Creeper_l (赞：3)

题意不多赘述。

注：全文所用的“点 $u$ 的出度”均指的是点 $u$ 在**原图**上的出度。

首先我们考虑 $r_{i} = 0$ 的情况怎么写，这时我们会发现要么答案是 $0$ 要么无解。当当前点 $u$ 无论怎么走都走不到一个环上，即无论怎么走最终都会走到一个出度为 $0$ 的点上的话，那么显然这个点是无解的。否则一定有解，因为可以先走到一个环上，然后在环上无限走。

然后考虑正解。可以发现一些性质：

- 性质一：如果一个点的出度为 $0$ 的话，那么这个点一定无解。

- 性质二：对于一条边 $u \to v$，如果点 $v$ 的出度为 $0$ 的话，那么删除这条边对答案没有影响。

- 性质三：如果当前边 $u \to v$ 的 $r$ 值是它所在环中 $r$ 值最大的，那么 $u$ 点的答案一定小于等于当前 $r$。

- 性质四：如果当前边 $u \to v$ 的 $r$ 值是剩下所有边中 $r$ 值最大的，那么 $u$ 点的答案一定小于等于当前 $r$。

那么我们可以先考虑一个类似于拓扑序上 dp 的东西，设 $dp_{v}$ 表示 $v$ 点的答案，对于一条边 $u \to v$，则有：

$dp_{u}=\min(dp_{u},\max(r_{u \to v},dp_{v}-p_{u \to v}))$。

因为 dp 方程的转移 $u$ 和 $v$ 是反过来的，所以建反图跑 dp。

但是给定的图不是 DAG，不好直接在拓扑序上 dp，于是考虑加上一些贪心。

先将所有边按照 $r$ 的值从大到小排序，枚举每一条边。对于每一条边先进行一次拓扑排序，在队列里的点表示当前点的 dp 值已经确定了的点，遍历它的出边 $u \to v$，用它来更新其它点即可。注意拓扑排序中遍历过的边可以直接删除了，因为 dp 值已经转移了，所以这条边已经没有任何价值了。同时 $v$ 点的出度减一，如果 $v$ 点的出度变为 $0$ 了，则入队。

进行完拓扑排序过后，如果当前枚举到的边还没有被删除的话，那么可以直接用性质四来更新答案，并将这条边删掉。因为如果一条边会被删掉必须满足它只能走到一些出度为 $0$ 的点上，而这条边还没有被删除所以它一定在一个环中，又因为 $r$ 值是从大到小枚举的，所以可以这样更新。

排序时间复杂度 $O(m \log m)$，dp 时间复杂度 $O(m)$，总时间复杂度 $O(m \log m)$。



---

## 作者：One_JuRuo (赞：3)

# 题目大意

给出一个有向图，每条边有两个权值，分别代表通过该路径的最小要求 $r_i$，和通过后增加的值 $p_i$。问：从每个点出发，各需要至少多少初始值，才能不停走下去。

# 思路

首先，分析一下，如果设 $f_i$ 为从 $i$ 点出发需要的最少初始值。那么可以轻易的推出转移方程：$f_i=\min(f_i,\max(f_j-p_{i,j},r_{i,j}))$ （存在有向路径 $i\to j$）。

但是，因为有环的出现，没办法 dp，也没办法爆搜，所以我们需要从其他方面进行考虑。

很容易地想到一下两个性质：

- 如果一个点没有办法进入一个环，那么他一定无解。

- 如果一个点有解，那么 $f_i$ 一定小于等于环中最大的 $r_i$。因为 $p_i \geq 0$，所以初始值只可能变大或不变不可能变小，如果初始值等于最大的 $r_i$，那它在这个环中哪条路径都可以走，自然满足条件。

如果正着找，需要搜索回溯，多半会 TLE。那为什么不反着建图，然后就可以用起点更新终点了（其实也可以不反着建图，就是更新要用终点更新起点）。

然后我们就可以用拓扑排序+贪心来做这道题啦。

先把所有最开始出度为 $0$ 的点找到，然后去掉同时减去相连的点的出度，用这个方法可以找到所有无解的点，找到后也不用更新，就赋成原来的值，最后输出的时候特判就好，然后把所有相关的边和点都删掉。

然后把边按照 $r_i$ 从大到小排序，每次取最大的边，用最开始推得转移方程更新对应点的值，然后删边、减出度，直到有个点出度为 $0$ 了，就代表答案固定了，就可以入队了。

然后每次取队首，更新连接的点，然后删边、减出度，如果又有点出度为 $0$，就又入队，直到队空，然后又开始找最大且没被删的边。

为什么要按照从大到小排序呢？如果最开始取了环中的较小边，某个点固定的答案，就可能不能满足较大边，而取最大边虽然最开始答案可能会比真实答案略大，但是最后一定是可以更新成正确答案的。

另外删边就直接用数组标记就好。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
struct node{int u,v,id,r,p;node(int _u=0,int _v=0,int _id=0,int _r=0,int _p=0){u=_u,v=_v,id=_id,r=_r,p=_p;}}a[200005];
inline bool cmp(node a,node b){return a.r>b.r;}
int n,m,e[400005],ne[400005],id[400005],wr[400005],wp[400005],h[200005],idx=1,out[200005],ans[200005],x,y,z,k;
bool vis[200005];
queue<int>q;
inline void add(int a,int b,int i,int r,int p){e[idx]=b,id[idx]=i,wr[idx]=r,wp[idx]=p,ne[idx]=h[a],h[a]=idx++;}
int main()
{
	scanf("%d%d",&n,&m),memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=m;++i) scanf("%d%d%d%d",&x,&y,&z,&k),a[i]=node(x,y,i,z,k),add(y,x,i,z,k),out[x]++;//反向建边，还要记得存边用来排序，顺便统计出度
	for(int i=1;i<=n;++i) if(!out[i]) q.push(i);//找到出度为0的点
	sort(a+1,a+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
		while(!q.empty())//更新答案
		{
			int u=q.front();q.pop();
			for(int i=h[u];i;i=ne[i])
			{
				if(!vis[id[i]])
				{
					vis[id[i]]=1,--out[e[i]];
					if(ans[u]!=inf) ans[e[i]]=min(ans[e[i]],max(wr[i],ans[u]-wp[i]));//此处特判是用于最开始的无解情况，无解情况就不能更新答案了
					if(!out[e[i]]) q.push(e[i]);
				}
			}
		}
		if(!vis[a[i].id]) vis[a[i].id]=1,ans[a[i].u]=min(ans[a[i].u],a[i].r),out[a[i].u]--;//每次找最大边，保证答案符合题意
		if(!out[a[i].u]) q.push(a[i].u);//出度为0了就要入队
	}
	for(int i=1;i<=n;++i) printf("%d ",(ans[i]!=inf)?ans[i]:-1);//输出记得特判-1
	return 0;
}

```

---

## 作者：Leasier (赞：2)

小清新妙妙题。

------------

首先可以拓扑排序删掉无法到达任何一个环的点，它们的答案显然显然为 $-1$。

接下来，一个简单的想法是：

- 设 $f_u$ 表示从 $u$ 出发无限走至少需要多少资产。
- 不难发现有 $f_u = \displaystyle\min_{u \to^{r, p} v} \max(f_v - p, r)$。
- 但问题在于我们很难精确地给出一些 $f_u$ 的初值，于是就没法直接像最短路一样转移了 /ng

虽然精确值很难给出，但我们可以**考虑某些 $f_u$ 的上界**，然后据此进行**调整**。

设图中 $r$ 最大的边为 $u \to^{r, p} v$，则 $f_u \leq r$，因为资产在行走过程中**单调不降**，于是我们可以凭借 $r$ 的初始资产走遍 $u$ 所在 SCC。

类似于差分约束，我们考虑拿 $f_u = r$ 去调整其他 $f_x$——直接从 $u$ 出发在反图上 SPFA 或 Dijkstra，但更新次数看上去似乎有点问题？

**注意到这条边此后就没用了——因为我们一定可以不经过 $u \to v$ 这条边使得其他 $f_x \leq r$。**

考虑删掉这条边，此后图上出现了一些不能到达环的点——此时我们可以拓扑排序给出它们对应的 $f$ 值，此时我们也可以删掉这些点。

接下来又变为了**每个点都可以到达环**的情况，于是我们继续找出一条没用过的边，重复上述过程，直到每条边都被用过即可。

时间复杂度为 $O(n + m \log m)$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

typedef struct {
	int id;
	int nxt;
	int start;
	int end;
	int r;
	int p;
} Edge;

int cnt = 0;
int head[200007], deg[200007], ans[200007];
bool vis[200007];
Edge edge1[200007], edge2[200007];
queue<int> q;

bool operator <(const Edge a, const Edge b){
	return a.r > b.r;
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int id, int start, int end, int r, int p){
	cnt++;
	edge2[cnt].id = id;
	edge2[cnt].nxt = head[start];
	head[start] = cnt;
	edge2[cnt].end = end;
	edge2[cnt].r = r;
	edge2[cnt].p = p;
	deg[end]++;
}

int main(){
	int n = read(), m = read();
	for (int i = 1; i <= m; i++){
		edge1[i].id = i;
		edge1[i].start = read();
		edge1[i].end = read();
		edge1[i].r = read();
		edge1[i].p = read();
		add_edge(i, edge1[i].end, edge1[i].start, edge1[i].r, edge1[i].p);
	}
	for (int i = 1; i <= n; i++){
		ans[i] = 0x7fffffff;
		if (deg[i] == 0) q.push(i);
	}
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		for (int i = head[cur]; i != 0; i = edge2[i].nxt){
			int x = edge2[i].end;
			vis[edge2[i].id] = true;
			if (--deg[x] == 0) q.push(x);
		}
	}
	sort(edge1 + 1, edge1 + m + 1);
	for (int i = 1; i <= m; i++){
		if (!vis[edge1[i].id]){
			int u = edge1[i].start;
			vis[edge1[i].id] = true;
			ans[u] = min(ans[u], edge1[i].r);
			if (--deg[u] == 0){
				q.push(u);
				while (!q.empty()){
					int cur = q.front();
					q.pop();
					for (int j = head[cur]; j != 0; j = edge2[j].nxt){
						if (vis[edge2[j].id]) continue;
						int x = edge2[j].end;
						vis[edge2[j].id] = true;
						ans[x] = min(ans[x], max(ans[cur] - edge2[j].p, edge2[j].r));
						if (--deg[x] == 0) q.push(x);
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; i++){
		if (ans[i] == 0x7fffffff){
			cout << -1 << " ";
		} else {
			cout << ans[i] << " ";
		}
	}
	return 0;
}
```

---

## 作者：7KByte (赞：1)

有删减，同步发表于[**我的博客**](https://www.cnblogs.com/SharpnessV/p/15183006.html)。

先口胡一个，明天再来补代码（

先考虑 $-1$ 的情况，显然没有出边的点是 $-1$，将这样的点和对应的边删掉，直到每个点都有出边。显然被删掉的点都是 $-1$，其余的点都不是 $-1$。

对于剩下的边，显然 $r_i$ 最大的边如果走了，那么其他的边随便走，所以对应的 $+p_i$ 没有意义。我们直接删掉这条边，然后在起始点 $a_i$ 打上 $r_i$ 的标记表示到达这里后且资产 $\ge$ 标记可以直接结束。

删掉边后 $a_i$ 可能没有出边了，这又回到 $-1$ 的情况，将对应的点和边删掉，然后找 $r_i$ 最大的边删掉。最后将所有边删掉。

每个点的标记就是答案。

这道题的关键在于逆向思维和归纳法，如果顺着模拟非常困难，但是从结束时的边入手则非常清晰。每次删除一条边归纳下去也是关键。

---

