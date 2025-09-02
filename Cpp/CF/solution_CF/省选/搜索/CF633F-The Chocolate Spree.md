# The Chocolate Spree

## 题目描述

Alice and Bob have a tree (undirected acyclic connected graph). There are $ a_{i} $ chocolates waiting to be picked up in the $ i $ -th vertex of the tree. First, they choose two different vertices as their starting positions (Alice chooses first) and take all the chocolates contained in them.

Then, they alternate their moves, selecting one vertex at a time and collecting all chocolates from this node. To make things more interesting, they decided that one can select a vertex only if he/she selected a vertex adjacent to that one at his/her previous turn and this vertex has not been already chosen by any of them during other move.

If at any moment one of them is not able to select the node that satisfy all the rules, he/she will skip his turns and let the other person pick chocolates as long as he/she can. This goes on until both of them cannot pick chocolates any further.

Due to their greed for chocolates, they want to collect as many chocolates as possible. However, as they are friends they only care about the total number of chocolates they obtain together. What is the maximum total number of chocolates they may pick?

## 说明/提示

In the first sample, Alice may start at the vertex $ 9 $ and Bob at vertex $ 8 $ . Alice will select vertex $ 1 $ and Bob has no options now. Alice selects the vertex $ 7 $ and they both stop.

In the second sample, both of them will pick either of the nodes alternately.

## 样例 #1

### 输入

```
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
```

### 输出

```
25
```

## 样例 #2

### 输入

```
2
20 10
1 2
```

### 输出

```
30
```

# 题解

## 作者：NOIPZZY (赞：9)


f[u][0] 表示以u为根的子树中最长的两条链之和

f[u][1] 表示以u为根的子树中最长的一条链

g[u] 表示以u为根的子树中从u到叶子节点加上另外一条链的最长长度

h[u] 表示以u为根的子树中儿子节点中f[son][1]的最大值

down[u] 表示从u到叶子节点的最长长度


```cpp
#include<bits/stdc++.h>
#define eps 1e-6
#define LL long long
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
//#pragma comment(linker, "/STACK:1024000000,1024000000")
using namespace std; const int MAXN = 100100;
const int INF = 0x3f3f3f3f;int n;vector<int> G[MAXN];int w[MAXN];
/**f[u][0] 表示以u为根的子树中最长的两条链之和
*f[u][1] 表示以u为根的子树中最长的一条链**
g[u] 表示以u为根的子树中从u到叶子节点加上另外一条链的最长长度*
h[u] 表示以u为根的子树中儿子节点中f[son][1]的最大值*
down[u] 表示从u到叶子节点的最长长度*/
LL f[MAXN][2], g[MAXN], h[MAXN], down[MAXN];
void dfs(int cur, int fa) {	
f[cur][0] = w[cur];
f[cur][1] = w[cur];
g[cur] = w[cur];	
h[cur] = 0;	
down[cur] = w[cur];	
for (int i = 0; i < G[cur].size(); i++) {	
	int u = G[cur][i];		
	if (u == fa) continue;	
		dfs(u, cur);			
			//一共四种情况		
	f[cur][0] = max(f[cur][0], f[u][0]);	
	f[cur][0] = max(f[cur][0], f[cur][1]+f[u][1]);	
		f[cur][0] = max(f[cur][0], down[cur]+g[u]);		
		f[cur][0] = max(f[cur][0], g[cur]+down[u]); 	
			//一共两种情况		
	f[cur][1] = max(f[cur][1], f[u][1]);	
	f[cur][1] = max(f[cur][1], down[cur]+down[u]); 	
	g[cur] = max(g[cur], w[cur]+g[u]);	
	g[cur] = max(g[cur], down[cur]+f[u][1]);		
	g[cur] = max(g[cur], down[u]+w[cur]+h[cur]); 
	h[cur] = max(h[cur], f[u][1]); 		
	down[cur] = max(down[cur], down[u]+w[cur]);	}}
	int main(){    
	//freopen("input.txt", "r", stdin);	
	scanf("%d", &n);	
	for (int i = 1; i <= n; i++)		
	scanf("%d", &w[i]);	
	for (int i = 1; i < n; i++) {		
	int u, v;		
	scanf("%d%d", &u, &v);		
	G[u].pb(v);		
	G[v].pb(u);	}	
	dfs(1, 0);	
	printf("%I64d", f[1][0]);    
	return 0;}

```


---

## 作者：Liuxizai (赞：7)

[更好的阅读体验](https://ac-stray.github.io/post/solution-codeforces-633f-the-chocolate-spree/)

> 本题是华一高Ks 2020.11.26 T4 Attack

## $Description$

给出一棵有$n$个节点的树，每个节点有一个权值$a_i$，求出不相交的两条链的最大权值和。

<!-- more -->

$2 \leq n \leq 10^5$

$1 \leq a_i \leq 10^9$

## $Solution$

一道树形DP好题，难点在于状态的转移，即两条链的形态。

不要怕多设状态，重点在于把所有情况都描述出来。

$DP_{now,0}: 最大两条链之和$
$DP_{now,1}: 最大一条链$
$DP_{now,2}: 到叶子节点的链+一条与之不相交的链最大值$
$DP_{now,3}: 儿子节点DP_{x,1}最大值$
$DP_{now,4}: 到叶子节点的最大链$

对于每种转移，代码里有解释，建议在草稿纸上画图，对理解很有帮助。

## $AC \space Code$

仅展示代码的核心部分。

```cpp
Void dfs(int now, int fa){
    // 初始化
    dp[now][0] = dp[now][1] = dp[now][2] = dp[now][4] = a[now];
    dp[now][3] = 0;

    for(auto x: g[now]){
        if(x == fa) continue;
        dfs(x, now);

        /* ***************************************** *
        * dp[][0]: 最大两条链之和
        * dp[][1]: 最大一条链
        * dp[][2]: 到叶子节点的链+一条与之不相交的链最大值
        * dp[][3]: 儿子节点dp[][1]最大值
        * dp[][4]: 到叶子节点的最大链
        * ***************************************** */

        dp[now][0] = max(dp[now][0], dp[now][1] + dp[x][1]);           // 子树内最大一条链+子节点子树内最大一条链
        dp[now][0] = max(dp[now][0], dp[x][0]);                        // 从子节点直接转移
        dp[now][0] = max(dp[now][0], dp[x][2] + dp[now][4]);           // 子节点子树内到叶子节点的链 与 子树内到叶子节点的链构成一条穿过当前节点的链+一条与之不相交的链
        dp[now][0] = max(dp[now][0], dp[now][2] + dp[x][4]);           // 与上面的转移类似

        dp[now][1] = max(dp[now][1], dp[x][1]);                        // 从子节点直接转移
        dp[now][1] = max(dp[now][1], dp[now][4] + dp[x][4]);           // 子节点子树内到叶子节点的链 与 子树内到叶子节点的链构成一条穿过当前节点的链

        dp[now][2] = max(dp[now][2], dp[x][2] + a[now]);               // 从子节点直接转移，将子节点子树内那条到达叶子结点的链延伸到当前节点
        dp[now][2] = max(dp[now][2], dp[x][4] + dp[now][3] + a[now]);  // 与上面的转移类似
        dp[now][2] = max(dp[now][2], dp[now][4] + dp[x][1]);           // 按照dp[][2]的定义直接转移

        dp[now][3] = max(dp[now][3], dp[x][1]);                        // 按照dp[][3]的定义直接转移

        dp[now][4] = max(dp[now][4], dp[x][4] + a[now]);               // 按照dp[][4]的定义直接转移，将最大链延伸到当前节点
    }
}
int main(){
    input(n);
    for(ri i = 1; i <= n; i++) input(a[i]);
    for(ri i = 1; i < n; i++){
        input(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    write(dp[1][0]);
	return 0;
}
```

- 最优解$Rank15$
- 1.39s
- 11.84MB
- 2.40KB


---

## 作者：huyufeifei (赞：6)

题意：求树上两条不相交链的最大点权和。

如果大家做过[P4383](https://www.luogu.org/problemnew/show/P4383)的话，那么这道题就很显然了......

### 解法①
一定有一条边，断掉之后把两条链分开。枚举这条边。  
这样就相当于求子树中选一条链的最大值和子树外选一条链的最大值。可以用树形DP来解决。  

还可以这样处理：把每个边化为一个结点，这样，枚举断边就相当于枚举根结点，在子树中选择两颗权值最大的即可。可以用二次扫描与换根法解决，跟上面大同小异。

### 解法⑨
我本人用的是这种.....因为我太蠢了....

直接暴力设计状态: `f[i][0/1/2/3]` 表示在一个子树中选了一条链/选了两条链/选了一条链并可以向外延伸/选了两条链并其中一条可以向外延伸。

大概长这样~~(灵魂画手)~~
![](http://images.cnblogs.com/cnblogs_com/huyufeifei/1336857/o_%E6%96%B0%E5%BB%BA%E4%BD%8D%E5%9B%BE%E5%9B%BE%E5%83%8F.bmp)

然后我们转移的时候大力讨论即可......答案就是 `f[root][1]`。  
具体转移可以看代码：
```cpp
#include <cstdio>
#include <algorithm>

typedef long long LL;
const int N = 100010;

struct Edge {
	int nex, v;
}edge[N << 1]; int top;

LL f[N][4];// 0 have one in   1 have two in   2 have one at   3 have two at
int e[N], val[N]; 

inline void add(int x, int y) {
	top++;
	edge[top].v = y;
	edge[top].nex = e[x];
	e[x] = top;
	return;
}

inline void update(int x, int y, int z, int i) {
	if(x != z && y != z) {
		f[i][1] = std::max(f[i][1], f[x][2] + f[y][2] + f[z][0] + val[i]);
	}
	return; 
}

void DFS(int x, int fa) {
	int a = 0, b = 0, c = 0; //  max of f[y][2] 
	int a0 = 0, b0 = 0, c0 = 0; //  max of f[y][0] 
	int a3 = 0, b3 = 0; // max of f[y][3]
	for(int i = e[x]; i; i = edge[i].nex) {
		int y = edge[i].v;
		if(y == fa) {
			continue;
		}
		DFS(y, x);
		/// cal 2
		f[x][2] = std::max(f[x][2], f[y][2]);
		/// cal 0
		if(f[y][2] > f[a][2]) {
			c = b;
			b = a;
			a = y;
		}
		else if(f[y][2] > f[b][2]) {
			c = b;
			b = y;
		}
		else if(f[y][2] > f[c][2]) {
			c = y;
		}
		f[x][0] = std::max(f[x][0], f[y][0]);
		/// cal 3
		f[x][3] = std::max(f[x][3], f[y][3] + val[x]);
		if(f[y][0] > f[a0][0]) {
			c0 = b0;
			b0 = a0;
			a0 = y;
		}
		else if(f[y][0] > f[b0][0]) {
			c0 = b0;
			b0 = y;
		}
		else if(f[y][0] > f[c0][0]) {
			c0 = y;
		}
		// cal 1
		f[x][1] = std::max(f[x][1], f[y][1]);
		if(f[y][3] > f[a3][3]) {
			b3 = a3;
			a3 = y;
		}
		else if(f[y][3] > f[b3][3]) {
			b3 = y;
		}
	}
	f[x][2] += val[x];
	f[x][0] = std::max(f[x][0], f[a][2] + f[b][2] + val[x]);
	if(a != a0) {
		f[x][3] = std::max(f[x][3], f[a][2] + f[a0][0] + val[x]);
	}
	else {
		f[x][3] = std::max(f[x][3], f[a][2] + f[b0][0] + val[x]);
		f[x][3] = std::max(f[x][3], f[b][2] + f[a0][0] + val[x]); 
	}
	f[x][1] = std::max(f[x][1], f[a0][0] + f[b0][0]);
	
	update(a, b, a0, x);
	update(a, b, b0, x);
	update(a, b, c0, x);
	update(b, c, a0, x);
	update(b, c, b0, x);
	update(b, c, c0, x);
	update(a, c, a0, x);
	update(a, c, b0, x);
	update(a, c, c0, x);
	
	if(a != a3) {
		f[x][1] = std::max(f[x][1], f[a][2] + f[a3][3] + val[x]);
	}
	else {
		f[x][1] = std::max(f[x][1], f[a][2] + f[b3][3] + val[x]);
		f[x][1] = std::max(f[x][1], f[b][2] + f[a3][3] + val[x]);
	}
	return;
}

int main() {

	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
	}
	for(int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	
	DFS(1, 0);
	
	printf("%lld", f[1][1]);
	return 0;
}
```


---

## 作者：Rina_048 (赞：4)

众所周知，树形$dp$都是~~麻烦的~~好题(不是蓝的就是紫的)。

假如只有一条链，我们一看，这不是大水题吗？但是，这道题它不。两条链，还要不相交，那就请出我们的法宝...树形$dp$。

$dp$难就难在状态&转移（~~其实就是亿点点细节~~）（~~考场上就是因为打掉了一个细节只有75分~~）。

考虑从子树向父节点进行转移。

对于父节点来说，子树中的链有三种状态：

1. 与父节点完全不相交；

2. 一端在父节点，一端在父节点的祖先；

3. 一端在父节点的$A$子树内，另一端在父节点$B$子树内。换言之，就是形成了$Λ$型。

考虑用$0$表示第一种状态，$1$表示第二种状态，$2$表示第三种状态。同时增开一维，表示从子树内选取多少条链。于是我们可以得到一些状态转移：

1. $d_{i,0,1}$的转移，直接从子树中继承一条链就可以了，在此不做解释。
```cpp
d[now][0][1]=max(d[now][0][1],d[v][1][1]);
d[now][0][1]=max(d[now][0][1],d[v][2][1]);
d[now][0][1]=max(d[now][0][1],d[v][0][1]);
```
2. $d_{i,0,2}$的转移：1°从子树中直接继承两条；2°从$A$子树中取一条，从$B$子树中取另一条；
```cpp
d[now][0][2]=max(d[now][0][2],d[v][0][2]);
d[now][0][2]=max(d[now][0][2],d[v][2][2]);
d[now][0][2]=max(d[now][0][2],d[v][1][2]);
//直接继承
```
```cpp
ll yw=max(d[v][2][1],max(d[v][0][1],d[v][1][1]));//yw统计最大的一条链，因为不相交，所以有没有经过子节点没有关系
if(ywdp) d[now][0][2]=max(d[now][0][2],yw+ywdp);
ywdp=max(ywdp,yw);
//当前节点的最大链+以前的链，更新以前的链
```
3. $d_{i,1,1}$的转移：从子节点直接转移$or$从这个节点开始一条新链，非常简单。
```cpp
d[now][1][1]=A[now];
d[now][1][1]=max(d[now][1][1],d[v][1][1]+A[now]);
```
4. $d_{i,1,2}$的转移：1°从子节点直接转移；2°从$A$子树取最大的未完的链，从$B$子树取最大的已完链拼起来；3°从$A$子树取最大已完链，从$B$子树取最大未完链拼起来；4°在本题中单个点也算一条链，所以可以从子树中取最大链，再加上自己的权值。
```cpp
if(d[v][1][2]) d[now][1][2]=max(d[now][1][2],d[v][1][2]+A[now]);//1°
d[now][1][2]=max(d[now][1][2],yw+A[now]);//4°
if(ywi21) d[now][1][2]=max(d[now][1][2],d[v][1][1]+A[now]+ywi21);//2°
if(ywi11&&d[v][2][1]) d[now][1][2]=max(d[now][1][2],d[v][2][1]+ywi11+A[now]);//3°
//2＆3归结起来就是子树只贡献一条未完链or一条已完链
```
5. $d_{i,2,1}$的转移：从$A$子树中抽最大链，从$B$子树中抽最大链拼起来。
```cpp
if(ywi11!=0) d[now][2][1]=max(d[now][2][1],d[v][1][1]+ywi11+A[now]);
```
6. $d_{i,2,2}$的转移：1°直接从子树$A$中取最大链，从子树$B$的$_{v,1,2}_$中转移；2°从子树$A$中取最大未完链，从子树$B$中取最大未完链，从子树$C$中取最大已完链；
```cpp
if(ywi12!=0) d[now][2][2]=max(d[now][2][2],d[v][1][1]+ywi12+A[now]);//1°
if(ywi11&&d[v][1][2]) d[now][2][2]=max(d[now][2][2],d[v][1][2]+ywi11+A[now]);//1°
if(yqhi21&&d[v][2][1]) d[now][2][2]=max(d[now][2][2],d[v][2][1]+yqhi21+A[now]);//2°
if(ywwy) d[now][2][2]=max(d[now][2][2],d[v][1][1]+ywwy+A[now]);//2°
```
最后，别忘了更新：
```cpp
if(ywi21) ywwy=max(ywwy,d[v][1][1]+ywi21);//ywwy统计最大的子节点匹配好的链
if(ywi11&&d[v][2][1]) ywwy=max(ywwy,d[v][2][1]+ywi11);//ywi11统计1,1状态
if(ywi11) yqhi21=max(yqhi21,d[v][1][1]+ywi11);
ywi11=max(ywi11,d[v][1][1]);//ywi11统计1,1状态
ywi12=max(ywi12,d[v][1][2]);//ywi12统计1,2状态
ywi21=max(ywi21,d[v][2][1]);//ywi21统计最大的子节点的2,1状态
```
于是，有了我们最终的代码（密集恐惧症者勿入）（慢到飞起）。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e5+10;
int n A[N];
ll d[N][3][3],ans=0;
struct Addedge{
		int v,nxt;
}e[N*2];
int h[N],tail=0,vis[N];
void inst(int u,int v){
		e[++tail]=(Addedge){v,h[u]};
		h[u]=tail;
}
void dfs(int now){
		int i;
		vis[now]=1;
		d[now][1][1]=A[now];
		d[now][2][1]=A[now];
		ll ywdp=0,ywi21=0,ywi11=0,ywi12=0,yqhi21=0,ywwy=0;
		for(i=h[now];i;i=e[i].nxt){
			int v=e[i].v;
			if(vis[v]) continue;
			dfs(v);
			d[now][0][1]=max(d[now][0][1],d[v][1][1]);
			d[now][0][1]=max(d[now][0][1],d[v][2][1]);
			d[now][0][1]=max(d[now][0][1],d[v][0][1]);
			d[now][0][2]=max(d[now][0][2],d[v][0][2]);
			d[now][0][2]=max(d[now][0][2],d[v][2][2]);
			d[now][0][2]=max(d[now][0][2],d[v][1][2]);
			ll yw=max(d[v][2][1],max(d[v][0][1],d[v][1][1]));
			if(ywdp) d[now][0][2]=max(d[now][0][2],yw+ywdp);
			ywdp=max(ywdp,yw);
			d[now][1][1]=max(d[now][1][1],d[v][1][1]+A[now]);
			if(d[v][1][2]) d[now][1][2]=max(d[now][1][2],d[v][1][2]+A[now]);
			d[now][1][2]=max(d[now][1][2],d[v][1][1]+A[now]);
			d[now][1][2]=max(d[now][1][2],d[v][2][1]+A[now]);
			d[now][1][2]=max(d[now][1][2],d[v][0][1]+A[now]);
			d[now][1][2]=max(d[now][1][2],d[v][1][1]+A[now]);
			if(ywi21) d[now][1][2]=max(d[now][1][2],d[v][1][1]+A[now]+ywi21);
			if(ywi11&&d[v][2][1]) d[now][1][2]=max(d[now][1][2],d[v][2][1]+ywi11+A[now]);
			d[now][2][1]=max(d[now][2][1],d[v][2][1]);
			if(ywi11!=0) d[now][2][1]=max(d[now][2][1],d[v][1][1]+ywi11+A[now]);
			if(ywi12!=0) d[now][2][2]=max(d[now][2][2],d[v][1][1]+ywi12+A[now]);
			if(ywi11&&d[v][1][2]) d[now][2][2]=max(d[now][2][2],d[v][1][2]+ywi11+A[now]);
			if(yqhi21&&d[v][2][1]) d[now][2][2]=max(d[now][2][2],d[v][2][1]+yqhi21+A[now]);
			if(ywwy) d[now][2][2]=max(d[now][2][2],d[v][1][1]+ywwy+A[now]);
			if(ywi21) ywwy=max(ywwy,d[v][1][1]+ywi21);
			if(ywi11&&d[v][2][1]) ywwy=max(ywwy,d[v][2][1]+ywi11);
			if(ywi11) yqhi21=max(yqhi21,d[v][1][1]+ywi11);
			ywi11=max(ywi11,d[v][1][1]);
			ywi12=max(ywi12,d[v][1][2]);
			ywi21=max(ywi21,d[v][2][1]);
		}
}
int main()
{
		cin>>n;
		memset(d,0,sizeof(d));
		int i,j,x,y;
		for(i=1;i<=n;i++) cin>>A[i];
		for(i=1;i<n;i++){
			cin>>x>>y;
			inst(x,y);
			inst(y,x);
		}
		dfs(1);
		for(i=0;i<=2;i++)
		for(j=1;j<=2;j++) ans=max(ans,d[1][i][j]);
		cout<<ans;
		return 0;
}
```
其实有一些状态不一定需要转移，但是它A了。（逃）

蒟蒻求轻喷。

---

## 作者：Peter0701 (赞：2)

不妨设一个节点 $v$ 的权值为 $val_v$ ，向其子树最多可以得到的链的最大权值和为 $down_v$ ，在子树中最长链的权值为 $down_v$ 。

然后就可以 $dfs$ 处理出 $down_v$ （必须由 $v$ 节点向下）和 $down_v$ （可以由一棵子树从下往上经过 $v$ 节点然后转向另一棵子树，也可以是某棵子树的内部的最长链）。

开一个队列，遍历每个节点 $u$ ，求 $u$ 和其儿子 $v$ 这条边为分界线的两棵树的内部最长链。这时就相当于把 $v$ 节点和 $u$ 以及 $u$ 的其余子节点都分开了。

先求出 $u$ 以及 $u$ 除了 $v$ 以外的儿子节点所形成的树的最长链，记为 $outside$ 。

设 $up_u$ 为 $u$ 向上可连成的最长链（不包括 $u$ 本身）， $predown_x$ 和 $ppredown_x$ 为 $u$ 的儿子的 $down_x$ 的前缀最大和次大， $prebest_x$ 为儿子的前缀最大， $sufdown_x,ssufdown_x,sufbest_x$ 分别为相应的后缀 $down_x$ 最大和次大以及 $best_x$ 最大。

然后就可以考虑 $outside$ 可以怎样连成了。

设当前枚举到第 $i$ 个儿子，则 $outside$ 是下面五种情况的最大值： $up_u+val_u+\max \{predown_{i-1},sufdown_{i+1} \},val_u+predown_{i-1}+sufdown_{i+1},val_u+predown_{i-1}+ppredown_{i-1},val_u+sufdown_{i+1}+ssufdown_{i+1},\max \{prebest_{i-1},sufbest_{i+1} \}$ 。

然后将答案对 $outside+best_v$ 取 $\max$ 即可（ $v$ 是第 $i$ 个儿子）。

当然，还需要更新 $up_v$ ，计算方法是 $up_v=val_u+\max \{up_u,\max \{predown_{i-1},sufdown_{i+1} \} \}$ 。

注意 $up_v$ 不包括 $val_v$ 。

如有疑问，评论区见。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
int n,u,v,num,head[200005];
long long val[100005],bst[100005],dwn[100005],prebest[100005],sufbest[100005],predown[100005],ppredown[100005],sufdown[100005],ssufdown[100005],upp[100005],ans;
struct edge
{
	int ver,next;
}e[200005];
inline void adde(int u,int v)
{
	e[num].ver=v;
	e[num].next=head[u];
	head[u]=num++;
}
void dfs(int u,int fa)
{
	long long maxn1=0,maxn2=0;
	for(int i=head[u];i!=-1;i=e[i].next)
	{
		int v=e[i].ver;
		if(v==fa)
			continue;
		dfs(v,u);
		if(dwn[v]>maxn1)
		{
			maxn2=maxn1;
			maxn1=dwn[v];
		}
		else if(dwn[v]>maxn2)
			maxn2=dwn[v];
		bst[u]=max(bst[u],bst[v]);
	}
	dwn[u]=maxn1+val[u];
	bst[u]=max(bst[u],maxn1+maxn2+val[u]);
}
void solve()
{
	queue<pair<int,int> > q;
	q.push(make_pair(1,0));
	while(!q.empty())
	{
		int u=q.front().first,fa=q.front().second;
		q.pop();
		vector<int> child;
		child.push_back(0);
		for(register int i=head[u];i!=-1;i=e[i].next)
		{
			int v=e[i].ver;
			if(v!=fa)
				child.push_back(v);
		}
		int siz=child.size();
		prebest[0]=0;
		predown[0]=0;
		ppredown[0]=0;
		for(register int i=1;i<siz;i++)
		{
			int v=child[i];
			prebest[i]=max(prebest[i-1],bst[v]);
			predown[i]=predown[i-1],ppredown[i]=ppredown[i-1];
			if(dwn[v]>predown[i])
			{
				ppredown[i]=predown[i];
				predown[i]=dwn[v];
			}
			else if(dwn[v]>ppredown[i])
				ppredown[i]=dwn[v];
		}
		sufbest[siz]=0;
		sufdown[siz]=0;
		ssufdown[siz]=0;
		for(register int i=siz-1;i;i--)
		{
			int v=child[i];
			sufbest[i]=max(sufbest[i+1], bst[v]);
			sufdown[i]=sufdown[i+1], ssufdown[i] = ssufdown[i+1];
			if(dwn[v]>sufdown[i])
			{
				ssufdown[i]=sufdown[i];
				sufdown[i]=dwn[v];
			}
			else if(dwn[v]>ssufdown[i])
				ssufdown[i]=dwn[v];
		}
		for(register int i=1;i<siz;i++)
		{
			int v=child[i];
			long long otsd=upp[u]+val[u]+max(predown[i-1],sufdown[i+1]);
			otsd=max(otsd,val[u]+predown[i-1]+ppredown[i-1]);
			otsd=max(otsd,val[u]+sufdown[i+1]+ssufdown[i+1]);
			otsd=max(otsd,val[u]+predown[i-1]+sufdown[i+1]);
			otsd=max(otsd,max(prebest[i-1],sufbest[i+1]));
			ans=max(ans,otsd+bst[v]);
		}
		for(register int i=1;i<siz;i++)
		{
			int v=child[i];
			upp[v]=val[u]+max(upp[u],max(predown[i-1],sufdown[i+1]));
			q.push(make_pair(v,u));
		}
	}
}
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
		val[i]=read();
	memset(head,-1,sizeof(head));
	for(register int i=1;i<n;i++)
	{
		u=read();
		v=read();
		adde(u,v);
		adde(v,u);
	}
	dfs(1,0);
	solve();
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：tzc_wk (赞：1)

安利个人 blog：https://www.cnblogs.com/ET2006/

[Codeforces 题目传送门](https://codeforces.com/contest/633/problem/F) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF633F)

~~看来我这个蒟蒻现在也只配刷刷 *2600 左右的题了/dk~~

这里提供一个奇奇怪怪的大常数做法。

首先还是考虑分析“两条不相交路径”的性质。我们以 $1$ 号点为根。记 $subtree(u)$ 为 $u$ 子树内点的集合，那么对于两条不相交的路径 $P_1,P_2$，下面两条一定有至少一条成立：

- $\exist u$ 满足 $\forall v\in P_1,v\in subtree(u),\forall v\in subtree(u),v\notin P_2$
- $\exist u$ 满足 $\forall v\in P_2,v\in subtree(u),\forall v\in subtree(u),v\notin P_1$

用人话说就是两条路径中一定存在一条路径满足另一条路径中任何一个点都不在其 LCA 的子树中。

我们不妨枚举这条路径的 LCA $u$，按照树的直径的套路我们求出 $f_u$ 表示以 $u$ 为链顶的链中，权值最大的链的权值之和；$g_u$ 表示以 $u$ 为链顶的链中权值第二大的，并且链向下延伸到的儿子与 $f_u$ 表示的链向下延伸到的儿子不同的链的权值之和（可能讲的不是太清楚，不过学过树的直径的应该都知道是什么意思罢）。那么显然以 $u$ 为 LCA 的链权值之和的最大值就是 $f_u+g_u-a_u$。

故现在我们的任务就是求出另一条链长度的最大值，也就是**抠掉 $u$ 的子树后剩余部分**的直径长度，这个东西怎么求呢？

我们考虑将剩余部分以 $fa_u$ 为根，其中 $fa_i$ 为 $i$ 在原树中的父亲。

还是套路地枚举第二条路径在剩余子树部分中的 LCA $v$，记 $f'_u$ 为在新的树中以 $u$ 为链顶的链中，权值最大的链的权值之和；$g'_u$ 表示以 $u$ 为链顶的链中权值第二大的，并且链向下延伸到的儿子与 $g'_u$ 表示的链向下延伸到的儿子不同的链的权值之和。那么这部分对答案的贡献应当为 $f_u+g_u-a_u+\max\{f'_v+g'_v-a_v\}$。

但是显然我们每次枚举 $u$ 都重新求一遍 $f'_u,g'_u$ 是不现实的，我们不妨来探究一下 $f'_u,g'_u$ 究竟与 $f_u,g_u$ 有什么关系。

比方说有如下图所示的树：

![](https://cdn.luogu.com.cn/upload/image_hosting/a41tk6bz.png)

假设我们枚举到了点 $U$，原树的根为 $R$。我们抠掉 $U$ 的子树部分之后以 $F$ 为根，剩余部分长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/7wmwbgs5.png)

考虑将剩余的子树中的节点 $v$ 分为两类：

1. $v$ 不在 $u$ 到根节点的路径上，譬如图中的 $A$ 点，很容易注意到的一点是新树中 $A$ 子树内的点集与原树中 $A$ 子树内的点集相同，故对于这样的点 $v$ 一定有 $f'_v=f_v,g'_v=g_v$。而显然点 $v$ 满足该条件当且仅当 $v$ 与 $u$ 不存在祖先关系。如果我们记 $h_u=f_u+g_u-a_u$，那么这部分的贡献应为 $h_u+h_v$。故所有这样的点对 $(u,v)$ 所能产生的最大贡献就是 $\max\limits_{u,v\ \text{不存在祖先关系}}h_u+h_v$，考虑枚举 $w=\text{LCA}(u,v)$，记 $mx_u=\max\limits_{v\in subtree(u)}h_v$，那么以 $w$ 为 LCA 的 $u,v$ 产生的贡献的最大值就是 $\max\limits_{u,v\in son(w),u\ne v}mx_u+mx_v$，这个显然可以一遍 DFS 搞定，在 DFS 过程中记录最小值和次小值即可。
2. $v$ 在 $u$ 到根节点的路径上，譬如图中的 $B$ 点，对于这样点 $v$，也有 $u$ 在新子树内的点集**就是 $\{1,2,\dots,n\}$ 扣掉原树内 $v$ 在 $u$ 方向的儿子的子树内的点集**。我们记 $of_v$ 为扣掉 $v$ 的子树内的后，以 $fa_v$ 为根后，以 $v$ 为链顶的链的权值的最大值，$og_v$ 仿照前文也有类似的定义。那么 $f'_v=of_s,g'_v=og_s$，其中 $s$ 为 $v$ 在 $u$ 方向的儿子。考虑一遍 DFS 用换根 dp 的套路求出 $of_u,og_u$，那么这部分贡献的最大值就是 $f_u+g_u-a_u+\max\limits_{v\ \text{为}\ u\ \text{的祖先},v\ne 1}\{of_v+og_v-a_v\}$，这个又可以一遍 DFS 求出。

时间复杂度 $\mathcal O(n)$，总共需四遍 DFS，第一遍 DFS 求出 $f_i,g_i$，第二遍 DFS 用换根 dp 的套路求出 $of_i,og_i$，第三遍 DFS 求出 $\max\limits_{u,v\ \text{不存在祖先关系}}h_u+h_v$，第四遍 DFS 求出 $\max f_u+g_u-a_u+\max\limits_{v\ \text{为}\ u\ \text{的祖先},v\ne 1}\{of_v+og_v-a_v\}$。常数较大，跑得最慢的一个点跑了 171ms。

代码如下（代码中 `dfs1,dfs2,dfs3,dfs4` 分别对应上文中提到的四遍 DFS）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
int n,a[MAXN+5];
vector<int> g[MAXN+5];
vector<pair<ll,ll> > pre[MAXN+5];
vector<pair<ll,ll> > suf[MAXN+5];
pair<ll,ll> out[MAXN+5],dp[MAXN+5];
pair<ll,ll> merge(pair<ll,ll> x,ll y){
	ll a[3]={0};a[0]=x.fi;a[1]=x.se;a[2]=y;
	sort(a,a+3);reverse(a,a+3);return mp(a[0],a[1]);
}
void dfs1(int x=1,int f=0){
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i];if(y==f) continue;
		dfs1(y,x);dp[x]=merge(dp[x],dp[y].fi+a[y]);
	}
}
void dfs2(int x=1,int f=0){
	pre[x].resize(g[x].size()+2);
	suf[x].resize(g[x].size()+2);
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i];
		if(y==f) pre[x][i+1]=merge(pre[x][i],out[x].fi+a[f]);
		else pre[x][i+1]=merge(pre[x][i],dp[y].fi+a[y]);
	}
	for(int i=(int)g[x].size()-1;~i;i--){
		int y=g[x][i];
		if(y==f) suf[x][i+1]=merge(suf[x][i+2],out[x].fi+a[f]);
		else suf[x][i+1]=merge(suf[x][i+2],dp[y].fi+a[y]);
	}
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i];if(y==f) continue;
		ll a[4]={0};
		a[0]=pre[x][i].fi;a[1]=pre[x][i].se;
		a[2]=suf[x][i+2].fi;a[3]=suf[x][i+2].se;
		sort(a,a+4);reverse(a,a+4);out[y]=mp(a[0],a[1]);
		dfs2(y,x);
	}
}
ll mx[MAXN+5],ans=0;
void dfs3(int x=1,int f=0){
	mx[x]=dp[x].fi+dp[x].se+a[x];
	ll mx1=0,mx2=0;
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i];if(y==f) continue;
		dfs3(y,x);chkmax(mx[x],mx[y]);
		if(mx[y]>mx1) mx2=mx1,mx1=mx[y];
		else if(mx[y]>mx2) mx2=mx[y];
	}
	if(mx2) chkmax(ans,mx1+mx2);
}
ll mxx[MAXN+5];
void dfs4(int x=1,int f=0){
	if(x!=1) chkmax(ans,dp[x].fi+dp[x].se+a[x]+mxx[x]);
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i];if(y==f) continue;
		mxx[y]=max(mxx[x],out[y].fi+out[y].se+a[x]);dfs4(y,x);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),g[u].pb(v),g[v].pb(u);
	dfs1();dfs2();dfs3();dfs4();printf("%lld\n",ans);
	return 0;
}
/*1
9
1 2 3 4 5 6 7 8 9
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
*/
/*2
2
20 10
1 2
*/
/*
5
1 5 4 2 3
1 2
2 3
2 4
1 5
*/
```



---

## 作者：傅思维666 (赞：1)

## 题解：

树形DP好题。

众所周知，作为一道DP题，当你没办法转移的时候，你要想着再多来几个状态帮你转移。

比如这道题：

我们直接设答案：$dp[x][0]$表示以x为根的子树选出两条不相交链的最大值。

怎么转移呢？

首先设当前节点为$x$，其中一个儿子为$y$。转移要对以下四步取max：

首先，要在以$y$为根的子树中选两条不相交链，这可能是答案。然后，在$y$为根的子树中选一条，在其他儿子里选一条。再然后，从该点和子树中分别选出半条链，再从子树里选一条完整链。最后，第三条的反向思路也是可以的。

然后发现一时半会没办法维护这四种情况。于是再来几个状态：$dp[x][0]$表示以$x$为根的子树选出一条链的最大值。$g[x]$表示以$x$为根的子树中从$x$到叶子再加上一条不相交链的最大值。$down[x]$表示从$x$到叶子节点的最大值。然后为了快速维护第二种情况，再加上$h[x]$表示所有儿子的$dp[y][0]$最大值。

大功告成，还有亿点点细节。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
const int maxn=1e5+5;
const int INF=0x3f3f3f3f;
int n;
vector<int> e[maxn];
int w[maxn];
ll dp[maxn][2],g[maxn],h[maxn],down[maxn];
void dfs(int x, int f) 
{	
    dp[x][0]=dp[x][1]=g[x]=down[x]=w[x];
    h[x]=0;	
    for(int i=0;i<e[x].size();i++) 
    {	
    	int u=e[x][i];		
    	if(u==f) 
            continue;	
		dfs(u,x);			
    	dp[x][0] = max(dp[x][0], dp[u][0]);	
    	dp[x][0] = max(dp[x][0], dp[x][1]+dp[u][1]);	
		dp[x][0] = max(dp[x][0], down[x]+g[u]);		
        dp[x][0] = max(dp[x][0], g[x]+down[u]); 	
	    dp[x][1] = max(dp[x][1], dp[u][1]);	
	    dp[x][1] = max(dp[x][1], down[x]+down[u]); 	
	    g[x] = max(g[x], w[x]+g[u]);	
	    g[x] = max(g[x], down[x]+dp[u][1]);		
	    g[x] = max(g[x], down[u]+w[x]+h[x]); 
	    h[x] = max(h[x], dp[u][1]); 		
	    down[x] = max(down[x], down[u]+w[x]);	
    }
}
int main()
{    
	scanf("%d",&n);	
	for(int i=1;i<=n;i++)		
	    scanf("%d",&w[i]);	
	for(int i=1;i<n;i++) 
    {		
    	int u,v;		
    	scanf("%d%d",&u,&v);		
    	e[u].push_back(v);
        e[v].push_back(u);
    }	
	dfs(1,0);	
	printf("%lld",dp[1][0]);    
	return 0;
}
```



---

## 作者：龙翔凤翥 (赞：1)

## sol: dfs+树的直径
	想一想最大权值和可以有哪几种情况构成：
    1. 一条树的直径+直径上一一个点的子树的直径。
    2. 两条链，每一条都属于部分直径。（即一条链的左端点在树的直径的左端点，另一条链的右端点在树的直径的右端点。)
   **最后对这两种情况的答案取MAX就可以了**
## code:
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+50;
#define RN register int 
#define int long long 
inline int read()
{
    int k=1,x=0;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')
        ch=getchar();
    if(ch=='-')
        k=-1,ch=getchar();
    while(ch<='9'&&ch>='0')
        x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*k;
}
struct P{   
    int n;
    int t;
}a[N<<1];
int n,head[N<<1],val[N],tot,v[100050],dis[100050],d[100050],num[100050],cnt,pre[100050],ans,fa[100050];
int lin[100050],lu[100050],p1,p2,maxx=0,first[100050],endd[100050],A[100050],B[100050],pos;
inline void add(int x,int y)
{
    a[++tot].n=head[x];
    a[tot].t=y;
    head[x]=tot;
}
inline int max(int x,int y)
{
    return x>y?x:y;
}
inline void dfs(int x,int fa)
{
    dis[pos]=0;
    for(RN i=head[x];i;i=a[i].n)
    {
        int y=a[i].t;
        if(y==fa||v[y]) continue;
        dis[y]=dis[x]+val[y];
        if(dis[y]>lin[pos])
            lin[pos]=dis[y],p1=y;//以pos为根的子树内的最长链
        dfs(y,x);
    }
}
inline void dfs1(int x,int fa)
{
    for(RN i=head[x];i;i=a[i].n)
    {
        int y=a[i].t;
        if(y==fa||v[y])
            continue;
        dis[y]=dis[x]+val[y];
        if(maxx<dis[y])
            maxx=dis[y],p2=y;
        pre[y]=x;
        dfs1(y,x);
    }
}
signed main()
{
    //freopen("1.out","r",stdin);
	//freopen("a.out","w",stdout);
    n=read();
    for(RN i=1;i<=n;i++)
        val[i]=read();
    for(RN i=1;i<n;i++)
    {
        int x;int y;
        x=read(),y=read();
        add(x,y),add(y,x);
    }
    int pos1,pos2;
    dis[1]=val[1];
    dfs(1,0);
    int maxn=-1;
    for(RN i=1;i<=n;i++)
    {
        if(maxn<dis[i])
            maxn=dis[i],pos1=i;
    }
    memset(dis,0,sizeof(dis));
    dis[pos1]=val[pos1];
    dfs1(pos1,0);
    maxn=0;
    for(RN i=1;i<=n;i++)
    {
        if(maxn<dis[i])
            maxn=dis[i],pos2=i;
    }
    ans+=maxn;//两遍dfs求树的直径
    num[++cnt]=pos2;
    v[pos2]=1;
    while(pos2!=pos1)
    {
        pos2=pre[pos2];
        v[pos2]=1;
        num[++cnt]=pos2;
    }//记录直径由哪些点构成
    maxn=-1;
    for(RN i=1;i<=cnt;i++)//对于直径上的每一个点，搜索其子树的最长链以及子树内的直径
    {
        maxx=0;
        p1=p2=0;
        pos=num[i];
        dfs(num[i],0);
        //maxx=max(maxx,lin[pos]);
        dis[p1]=val[p1];
        dfs1(p1,0);
        //lu[num[i]]=maxx;
        maxn=max(maxn,maxx);//子树的直径
    }
    ans+=maxn;//ans表示第一种情况
    for(RN i=1;i<=cnt;i++)
        first[i]=first[i-1]+val[num[i]],A[i]=max(A[i-1],first[i]+lin[num[i]]);//求前缀和
    for(RN i=cnt;i;i--)
        endd[i]=endd[i+1]+val[num[i]],B[i]=max(B[i-1],endd[i]+lin[num[i]]);//求后缀和
    /*for(RN i=1;i<=cnt;i++)
        cout<<num[i]<<" "<<lin[num[i]]<<endl;*/
    int ans2=0;//ans2表示第二种情况
    for(RN i=0;i<=cnt;i++)
        ans2=max(ans2,A[i]+B[i+1]);//取最大值
    cout<<max(ans,ans2)<<endl;
    return 0;
}
```


---

