# [BalticOI 2003] Gem 气垫车

## 题目描述

给出一棵树，要求你为树上的结点标上权值，权值可以是任意的正整数。

唯一的限制条件是相邻的两个结点不能标上相同的权值，要求一种方案，使得整棵树的总价值最小。

## 样例 #1

### 输入

```
10 
7 5 
1 2 
1 7 
8 9 
4 1 
9 7 
5 6 
10 2 
9 3```

### 输出

```
14```

# 题解

## 作者：moosssi (赞：26)

一道很经典的树形dp。

看完题，首先想到直接用1，2依次染色，但这种贪心思路是错的。

这里给一个hack数据：10 1 2 1 3 1 4 1 5 1 6 2 7 2 8 2 9 2 10。

画完图可以很容易地看出最优方案应为1，2节点分别填2，3，其余点填1。

做到这里，我们就可以知道填的权值的最大值不一定为2，但它有一个上界大致为logn+1，具体怎么证明我也不太清楚，大家可以看看其他大佬的题解。

知道上界，这道题就很简单了，设f[x][i]表示节点x取值为i时，子树内权值和最小值。

对于每个节点，依次枚举自己和儿子的权值，取最小值转移即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int head[N],ver[N],net[N],tot;
int n,f[N][20],ans=0x3f3f3f3f;
void add(int a,int b){
	net[++tot]=head[a];
	head[a]=tot;
	ver[tot]=b;
}
void dfs(int x,int fa){
	for(int i=1;i<=15;i++){
		f[x][i]=i;//初始化 
	}
	for(int i=head[x];i;i=net[i]){
		int v=ver[i];
		if(v==fa)continue;
		dfs(v,x);
		for(int j=1;j<=15;j++){
			int minn=0x3f3f3f3f;
			for(int k=1;k<=15;k++){//找最小值，并且不与当前值相同 
				if(j!=k)minn=min(minn,f[v][k]);
			}
			f[x][j]+=minn;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(1,0);
	for(int i=1;i<=15;i++){
		ans=min(ans,f[1][i]);//找最小值 
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：CNCAGN (赞：14)

感觉 P5765 和 P4395 都没有对于最大点权太认真的证明，故写了此题解。

## 题目描述
题目给出一个树的边，要求自选正整数点权值（即填色），使得点权和最小，同时要求相邻的两个点的点权不等。
## Solution
树形动规的绿题一般比较相似，这个题就和上司的舞会很像。

动规方程也很好推，令 $f_{u,i}$ 代表 $u$ 为根的树，点权为 $i$ 的情况下权值和的最小值。

则 $f_{u,i}=i+\sum\min(f_{v,j})(j{\neq}i,v{\in}son_u)$。

考虑用 $1$ 和 $2$ 来填色，思路很快就假，如下图所示，$1,2,3$ 填色明显比 $1,2$ 填色更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/y8ctt1ik.png)

讨论区也有说最大用 $1,2,3,4$ 即可满足最小填色，也可通过上图规模的扩大进行否定。

考虑正解，**对于本题任意一颗树的填色方案，总有一个最大的点权**。那么 dp 的前置问题转化为：**一个 $n$ 个点的树按本题规则填色，最大点权为何**。

我比较菜直接想不出来，但是可以把这个问题转化：**已经填好树上点权且最优，若这个点的点权为 $x_i$，那么求这个点的子树最小有多少个点（设为 $num_i$）**。据此，若有一点权为 $x$ 的点，使得 $num_i{\ge}n$，则这颗 $n$ 点的子树一定可以用 $1,2,3,\cdots,x_{i-1},x_i$ 来获得总权值最小的填色。

若最优答案树上一个点的点权为 $x$，那么显然这个点一定连接点权为 $1$ 到 $x-1$ 的所有的点，那么简单的打个表找规律（下图带颜色的数字代表点的个数）：

![](https://cdn.luogu.com.cn/upload/image_hosting/gyvlsyp0.png)

发现最大点权 $x_i$ 的最优最小子树的 $num_i$ 为 $2^{x_i-1}$。所以题目 $n$ 个点的树最大用 $\log_2n+1$ 即可最优填色，对于此题为 $15$ 左右，完全可过。至此，这个题最关键的步骤结束了。代码可能是最简单的部分了。简单 dfs 和 dp 即可。
## code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<deque>
#include<map>
using namespace std;
inline int red() {
    int op = 1, x = 0;
    char ch = getchar();
    while(!isdigit(ch)) {
        if(ch == '-')   op = -1; 
        ch = getchar();
    }
    while(isdigit(ch)) {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return op * x;
}
const int maxn = 1e5 + 10, maxm = 1e5 + 10, maxx = 16;
const int inf = 0x3f3f3f3f;
int n, x;
int root;
int deg[maxn];
int f[maxn][maxx];
int head[maxn], to[maxm], nxt[maxm];
int num;
void add(int a, int b) {
	to[++num] = b;
	nxt[num] = head[a];
	head[a] = num;
}
void dfs(int u, int fa) {
	for(int i = 1; i <= x; ++i) {
		f[u][i] = i;
	}
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v == fa)	continue;
		dfs(v, u);
		for(int j = 1; j <= x; ++j) {
			int minn = inf;
			for(int k = 1; k <= x; ++k) {
				if(k == j)	continue;
				minn = min(minn, f[v][k]);
			}
			f[u][j] += minn;
		}
	}
}
int main() {
	n = red();
	x = log(n) / log(2);
	++x;
	for(int i = 1; i < n; ++i) {
		int a = red(), b = red();
		add(a, b);
		add(b, a);
		++deg[a], ++deg[b];
	}
	root = 1;
	dfs(root, -1);
	int ans = inf;
	for(int i = 1; i <= x; ++i) {
		ans = min(ans, f[1][i]);
	}
	printf("%d\n", ans);
    return 0;
}

```


---

## 作者：AlanSP (赞：11)

### 本文附有权值数logn的~~口胡~~证明

这个题的确是个好题，但因为数据水的原因，曾一度放走了很多错解。

首先，01染色的方法已经被Hack了，这里不再多提。

而关于123染色是如何错误的，讨论区有dalao给出了数据，但好像没有人详细说一说，我这里就插个空qwq。

证明方法其实和之前的类似。

![如图](https://cdn.luogu.com.cn/upload/image_hosting/wgpa49a4.png)

假设每一个三角代表很多叶子。（它们都是同一层的。）

那么当一个三角有一个三角儿子时，若是按照1，2，3染色的方法，这个三角儿子只能被附成非1的权值，或者说这两个三角权值不能同时是1。

那么当你引入一个新的权值4时，可以让三角中挂着三角儿子的那一个节点不赋为1，下面的都为1，这样就完美解决了。

那么你可能会问，为什么是logn个权值呢？

---
### **证明**：
先来考虑什么情况是不优的，当然是这其中的叶子节点的数量大于父亲的数量。

这样便需要引入权值。

也就是说，如果有n个父亲节点，那么叶子必须要n+1个才可以。

我们还知道，这些叶子必须挂在一个节点上才行，所以每个节点的子节点数应该>=2。

这样至多会有logn层。

根据最上面的Hack，我们知道权值是跟层数是一个数量级的。

所以权值也在logn级别。

~~非常不严谨，大家感性理解一下，大佬轻喷。~~

那么这样我们就可以用树形dp来处理这个问题，每个子树可以转移给跟自己颜色不一样的父亲。

~~我为了怕自己错，在代码里面加了个rand，不要在意qwq~~

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+9,INF=0x3f3f3f3f;
int x,y,tot,dep,minn;
int ver[N<<1],nxt[N<<1],h[N],n,ans,belong[5];
int dp[N][59];

inline void add(int x,int y)
{
	ver[++tot]=y,nxt[tot]=h[x],h[x]=tot;
}

inline void dfs(int u,int fa)
{
	for(int i=1;i<=dep;i++) dp[u][i]=i;
	for(int i=h[u];i;i=nxt[i])
	{
		int v=ver[i];
		if(v==fa) continue;
		dfs(v,u);
	}
	for(int i=1;i<=dep;i++)
	{
		for(int t=h[u];t;t=nxt[t])
		{
			int v=ver[t];
			minn=INF;
			if(v==fa) continue;
			for(int j=1;j<=dep;j++)
			{
				if(j==i) continue;
				minn=min(minn,dp[v][j]);
			}
			dp[u][i]+=minn;
		}
	}
}

int main()
{
	// freopen("123.in","r",stdin);
	scanf("%d",&n);
	ans=INF;
	dep=log2(n);
	dep+=rand()%19;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=dep;i++) ans=min(dp[1][i],ans);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：cjZYZtcl (赞：8)

# 来一发Pascal的题解吧
### 首先，考虑暴力DFS。
每次DFS传入3个参数：当前节点编号，当前节点权值，父节点编号。

然后再DFS中枚举子节点的权值，如果与当前节点不同就继续往下DFS，并求出每棵子树的最小权值和，最后加上当前节点权值就是以这种情况的最小子树权值和，并返回。

## Code：（DFS，19 pts）：
```pascal
uses math;
var
  n,i,x,y,z:longint;
  r,t:array[0..20005]of longint;
  h:array[0..10005]of longint;
function dfs(root,y,fa:longint):longint;
var
  x,z,i,sum:longint;
begin
  sum:=y;
  x:=h[root];
  while x<>0 do
  begin
    if r[x]=fa then
    begin
      x:=t[x];
      continue;
    end;
    z:=maxlongint;
    for i:=1 to 20 do
      if i<>y then z:=min(z,dfs(r[x],i,root));
    sum:=sum+z;
    x:=t[x];
  end;
  exit(sum);
end;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(x,y);
    inc(z);
    t[z]:=h[x];
    h[x]:=z;
    r[z]:=y;
    inc(z);
    t[z]:=h[y];
    h[y]:=z;
    r[z]:=x;
  end;
  x:=maxlongint;
  for i:=1 to 20 do x:=min(x,dfs(1,i,1));
  write(x);
end.
```
### 考虑优化
我们可以先把以一号节点为根节点的树建起来，并且存下每一个节点的深度和每一棵子树内最深的点的深度。

可以得出，如果要使当前节点的一棵子树内权值和最小，树内每一个节点的权值一定不会超过当前节点的子树内最深深度减去当前节点深度加一。

为什么要加一呢？

因为可能出现子树内每一层权值都不同的情况，而如果当前节点在[1,最深深度-当前深度+1]的范围内时，就会导致子节点缺少一种权值取值情况，所以要加一。

## Code：（DFS+优化，28 pts）
```pascal
uses math;
var
  n,i,x,y,z:longint;
  r,t:array[0..20005]of longint;
  h,d,sd:array[0..10005]of longint;//d表示当前深度，sd表示子树中的最大深度。
procedure build(root,fa,dep:longint);//建树预处理深度
var
  x:longint;
begin
  d[root]:=dep;
  sd[root]:=dep;
  x:=h[root];
  while x<>0 do
  begin
    if r[x]=fa then
    begin
      x:=t[x];
      continue;
    end;
    build(r[x],root,dep+1);
    sd[root]:=max(sd[root],sd[r[x]]);
    x:=t[x];
  end;
end;
function dfs(root,y,fa:longint):longint;
var
  x,z,i,sum:longint;
begin
  sum:=y;
  x:=h[root];
  while x<>0 do
  begin
    if r[x]=fa then
    begin
      x:=t[x];
      continue;
    end;
    z:=maxlongint;
    for i:=1 to sd[r[x]]-d[root]+1 do//优化
      if i<>y then z:=min(z,dfs(r[x],i,root));
    sum:=sum+z;
    x:=t[x];
  end;
  exit(sum);
end;
begin
  readln(n);
  for i:=1 to n do
  begin
    readln(x,y);
    inc(z);
    t[z]:=h[x];
    h[x]:=z;
    r[z]:=y;
    inc(z);
    t[z]:=h[y];
    h[y]:=z;
    r[z]:=x;
  end;
  build(1,1,1);
  x:=maxlongint;
  for i:=1 to 20 do x:=min(x,dfs(1,i,1));
  write(x);
end.
```
## 正解：（树形DP）

我们设 $f_{i,j}$ 为第 $i$ 个点，取权值为 $j$ 的时候，这个点以及它的子树所能取到的最小的权值和。

很明显，由于相邻点的权值不能相同，所以我们只需要在当前点的所有的儿子的所有权值取法中，每一个儿子取一种与当前点不同的权值中最小的权值和，再加上当前点取的权值，就可以了。

而唯一的问题就是权值取值范围，这个我也不知道具体是多少，但我取 $20$ 过了，所以不会高于 $20$ ，大约在 $log$ $n$ 左右吧。

时间复杂度 $O(20*20*n)$ 。

表述可能不太清晰，具体怎么做请看代码。

## Code：（树形DP，100 pts）
```pascal
uses math;
var
  r,t:array[0..20005]of longint;
  h:array[0..10005]of longint;
  f:array[0..10005,0..25]of longint;
  x,y,z,i,n:longint;
procedure dp(root,fa:longint);//树形DP
var
  x,y,i,j:longint;
begin
  x:=h[root];
  while x<>0 do
  begin
    if r[x]=fa then//如果这条边通向它的父亲，就跳过
    begin
      x:=t[x];
      continue;
    end;
    dp(r[x],root);//先DP它的儿子
    for i:=1 to 20 do//枚举当前点取的权值
    begin
      y:=maxlongint;
      for j:=1 to 20 do//枚举当前点的儿子取的权值
      begin
        if i=j then continue;//如果权值相同就跳过
        y:=min(y,f[r[x],j]);//求最小值
      end;
      f[root,i]:=f[root,i]+y;//将最小值累加
    end;
    x:=t[x];//DP下一个儿子
  end;
  for i:=1 to 20 do f[root,i]:=f[root,i]+i;//将每一种情况加上当前取的权值
end;
begin
  readln(n);
  for i:=1 to n-1 do//读入，用链式前向星存储
  begin
    readln(x,y);
    inc(z);
    t[z]:=h[x];
    h[x]:=z;
    r[z]:=y;
    inc(z);
    t[z]:=h[y];
    h[y]:=z;
    r[z]:=x;
  end;
  dp(1,1);//将一号节点设置为根节点，DP
  x:=maxlongint;
  for i:=1 to 20 do x:=min(x,f[1,i]);//找出最小权值和
  write(x);//输出
end.
```
本人最近在转C++，也顺便贴一发C++的代码吧QwQ。
## C++ Code（码风丑勿喷）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int r[20005] = {0}, t[20005] = {0}, h[10005] = {0};
int f[10005][25] = {0};
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
void dp(int root, int fa){
	int x = h[root], y;
	while(x){
		if(r[x] == fa){
			x = t[x];
			continue;
		}
		dp(r[x], root);
		for(int i = 1; i <= 20; i++){
			y = 10000007;
			for(int j = 1; j <= 20; j++){
				if(i == j) continue;
				y = min(y, f[r[x]][j]);
			}
			f[root][i] += y;
		}
		x = t[x];
	}
	for(int i = 1; i <= 20; i++) f[root][i] += i;
}
int main(){
	int n = read(), x = 0, y = 0, z = 0;
	for(int i = 1; i < n; i++){
		x = read(), y = read();
		t[++z] = h[x];
		h[x] = z;
		r[z] = y;
		t[++z] = h[y];
		h[y] = z;
		r[z] = x;
	}
	dp(1, 1);
	x = 10000007;
	for(int i = 1; i <= 20; i++) x = min(x, f[1][i]);
	write(x);
}
```

---

## 作者：lightup37 (赞：6)

感谢[rqyBlog](https://rqy.moe/Solutions/bzoj1369/)里的思路

那个... 讨论区的那组数据似乎是真的... 我用rqy的方法写的代码和rqy的代码测过都比题解里的做法小1, 真的不打算加上吗...

---

关于这道题, 很容易想到是用DP, 那么设状态为dp[i][j]表示若节点i选择权值j, i的子树的最小权值和(注意j是$O(n)$级别的), 为了方便我们设$S_k = \{dp[k][x] | x\in\mathbb{N}^+\}$

那么易得一个转移方程:

$dp[i][j] = \sum\limits_{k \in son(i)} \min\limits_{t\not=j}\{dp[k][t]\}$

容易发现, 后面那个min是只有一个限制的, 即$\min\limits_{t\not=j}\{dp[k][t]\}$无论j如何改变, 都(要么是$S_k$中的最小值, 要么是其中的次小值), 因此我们可以**简化状态**, 具体来说, 对于每个$S_k$, 仅储存其最小值, 最小值取到的位置和次小值, 那么每次更新节点i时, 考虑如下三种情况:

1. 节点i取(最小的, 其儿子中没有取到的)的值 (可能作为最小值)

2. 节点i取(次小的, 其儿子中没有取到的)的值 (可能作为次小值)

3. 节点i取一个其儿子中取到的值, 那么所有(最小值在该值取到的)的儿子都要改取次小值

于是就得到了一个正确性完全没有问题的$O(n)$算法.


Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define d(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ri register int
#define ll long long
#define il inline
#define _ 19260817
namespace intio{char ch; int read(){ ri x=0,f=1; while(!isdigit((ch=getchar()))) f=ch=='-'?-1:1; while(isdigit(ch)) x=x*10+ch-'0', ch=getchar(); return x*f; } void read(int& x) {x = read();}}; using namespace intio;
int max(int x, int y) {return x>y?x:y;} int min(int x, int y) {return x<y?x:y;}
typedef struct wyxkkak{
	int mn, mp, ms;
	void upd(int x, int v){
		if(v<mn) ms=mn, mp=x, mn=v;
		else if(v<ms) ms=v;
	}
} dat ;
dat dp[_];
int ver[_], head[_], Next[_], tot;
int C[_], vis[_];
void add(int u, int v){
	ver[++tot]=v, Next[tot]=head[u], head[u]=tot;
}
void dfs(int n, int f){
	int S=0, k=1; dat& ans=dp[n]; ans.mn=ans.ms=0x3f3f3f3f;
	for(int i=head[n]; i; i=Next[i]) if(ver[i]!=f) dfs(ver[i], n);
	for(int i=head[n]; i; i=Next[i]){
		if(ver[i]==f) continue;
		dat t=dp[ver[i]]; S+=t.mn; C[t.mp]+=t.ms-t.mn; vis[t.mp]=1;
	}
	while(vis[k]) ++k; ans.upd(k, S+k); ++k;
	while(vis[k]) ++k; ans.upd(k, S+k);
	for(int i=head[n]; i; i=Next[i]){
		if(ver[i]==f) continue;
		dat t=dp[ver[i]]; if(!vis[t.mp]) continue;
		ans.upd(t.mp, S+C[t.mp]+t.mp); vis[t.mp]=C[t.mp]=0;
	}
}
int n;
int main(){
	scanf("%d", &n);
	for(int i=1;i<n;++i){
		int x, y; scanf("%d%d", &x, &y); add(x, y); add(y, x);
	} 
	dfs(1, 0);
	printf("%d\n", dp[1].mn);
	return 0;
}
```

---

## 作者：Hycyv (赞：6)

这是一篇使用 Go 的题解。

------------
树形动规的思路是清晰的。我们令 $f_{i,j}$   表示 “以 $i$ 为根的子树，其根节点颜色为 $j$ 所能获得的最小权值和”。

则其状态转移方程为：

$$f_{i,j} = \sum_{k \in son_i,c \in[1,???],c\ne j}\min(f_{
k,c_1},f_{
k,c_2},f_{
k,c_3},\dots)  + j
$$

我们跑一跑搜索，再加个数组记录算过的答案。
算过的直接返回，搜到叶节点则直接返回 $ j$。

但其中的 $???$ 正是问题所在。通过实验得知，确实有 $10000$ 个节点以内需要用到 $1,2,3,4$ 四种颜色的
[情况](https://www.luogu.org/discuss/show/140008) 存在。此树像是一个稠密的菊花图加一根很长的链，链上有小分支。

更进一步的，在 $100000$ 个节点以内可构造出使用 $5$ 的情况。[这个数据](https://www.luogu.org/paste/ieddmmwn)使用了 $74101$ 个节点，枚举到 $3$ 的答案为 $107170$ ，枚举到 $4$ 的答案为 $107160$ ，枚举到 $5$ 的答案为 $107159$ 。这是随机生成树跑了好几个小时的结果。

另外，几千组 $n>10000$ 的随机数据中没有出现需要 $6$ 的情况。 

有关需要 $logn$ 种颜色的说法未见证明，但感觉上有点多。实际答案也有可能是某个增长较快的函数的反函数。

这样，目前做法的复杂度就是 $O(???n)$ ，其中 $???$ 是按个人兴趣选择的一个常数。但不要选得太小。


------------
Markdown 没有 Go 的高亮，用 Python 的凑合一下。

```python
package main

import "fmt"

var a [10101][]int
var n int
var dep [10101]int

func min( a , b int) int {
	if( a < b  ) {
		return a
	}
	return b
}

func GetDepth( root , depth int) {
	dep[root] = depth
	for i := 0; i<len(a[root]); i++ {
		if( dep[a[root][i]] == 0 ){
			GetDepth( a[root][i] , depth+1 )
		}
	}
}

var f [10101][20]int

func dfs( root , c int ) int {
	if( f[root][c] != 0){
		return f[root][c]
	}

	var ans int = 0

	for i := 0; i < len(a[root]); i++{
		if( dep[a[root][i]] > dep[root]  ){
			var ans_ = 0x7fffffff
			for cc := 1; cc <= 15; cc++{
				if( cc != c ){
					 ans_ = min( dfs( a[root][i] , cc ) , ans_)
				}
			}
			ans += ans_
		}
	}

	f[root][c] = ans + c
	return f[root][c]
}

func main(){
	fmt.Scanf("%d",&n)
	for i := 1; i<=n-1; i++{
		var from int
		var to int
		fmt.Scanf("%d%d",&from,&to)
		a[from] = append(a[from],to)
		a[to] = append(a[to],from)
	}

	GetDepth( 1 , 1 )

//	for i := 1; i <= n; i++ {
//		fmt.Println(dep[i])
//	}
	var ans = 0x7fffffff
	for i := 1; i <= 14; i++{
		ans = min( ans , dfs( 1 , i ) )
	}

	fmt.Println(ans)
}

```


------------
Go 语言感觉上还是不错的，尤其是有类似于 vector 的 _“切片” （Slice）_ 存在。我可以保留我的习惯而不必写链式前向星了。然后其类型要求比较严格，int 型似乎依然不能用于布尔语境。  

---

## 作者：Plozia (赞：2)

宣传博客$\to$[link](https://blog.csdn.net/BWzhuzehao/article/details/117264560)

首先一种显然的想法是直接 1/2 染色。

但是很遗憾这个做法是错的，可以构造出如下反例：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20210526213555476.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0JXemh1emVoYW8=,size_16,color_FFFFFF,t_70)

显然 1,2 这两个节点应该一个填 2 一个填 3，但如果只是 1/2 染色就会得到错误答案。

因此考虑树形 DP。

设 $f_{i,j}$ 表示在第 $i$ 个点填 $j$ 数字的时候的最小花费。

那么就有转移方程：

$$f_{u,j}=j+\sum_{u \to v}\min\{f_{v,k} | k \ne j\}$$

这个方程还是比较好理解的吧qwq

到这里会出现两条路：

1. 如果写法是数字与点数同阶，那么复杂度是 $O(n^3)$ 的。为了降下复杂度，可以只存最大值与次大值及其填的数，这样可以优化转移。
2. 当然也可以手动调整一下最大的数字上限，题解区有人说过最大数为 $\log n$，但是我不会证qwq，我采用的是这种方法。

My Code：

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:P4395 [BOI2003]Gem 气垫车
    Date:2021/5/26
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 10000 + 10;
const LL INF = 0x7f7f7f7f7f7f7f7f;
int n, Head[MAXN], cnt_Edge = 1;
LL f[MAXN][70];
struct node { int to, Next; } Edge[MAXN << 1];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = (sum << 3) + (sum << 1) + (ch ^ 48);
    return sum * fh;
}
LL Max(LL fir, LL sec) { return (fir > sec) ? fir : sec; }
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }
void add_Edge(int x, int y) { ++cnt_Edge; Edge[cnt_Edge] = (node){y, Head[x]}; Head[x] = cnt_Edge; }

void DP(int now, int father)
{
    for (int i = 1; i <= 50; ++i) f[now][i] = i;
    bool flag = 0;
    for (int i = Head[now]; i; i = Edge[i].Next)
    {
        int u = Edge[i].to;
        if (u == father) continue ;
        DP(u, now); flag = 1;
    }
    if (flag) for (int i = 1; i <= 50; ++i) f[now][i] = i;
    for (int i = Head[now]; i; i = Edge[i].Next)
    {
        int u = Edge[i].to;
        if (u == father) continue ;
        for (int j = 1; j <= 50; ++j)
        {
            LL sum = INF;
            for (int k = 1; k <= 50; ++k)
                if (j != k) sum = Min(sum, f[u][k]);
            f[now][j] += sum;
        }
    }
}

int main()
{
    n = Read();
    for (int i = 1; i < n; ++i)
    {
        int x = Read(), y = Read();
        add_Edge(x, y); add_Edge(y, x);
    }
    DP(1, -1); LL ans = INF;
    for (int i = 1; i <= 50; ++i) ans = Min(ans, f[1][i]);
    printf("%lld\n", ans); return 0;
}
```


---

## 作者：MCAdam (赞：2)

[题目](https://www.luogu.com.cn/problem/P4395)

一个非常简单的暴力：

设$f[p][j]$表示以$p$为根的子树，$p$的权值为$j$的最小代价

$\displaystyle f[p][j]=j+\sum_{q\in son(p)} \min_{k\neq j}\{f[q][k]\}$

然后呢？瞎猜一个上限，然后暴力枚举$j,k$？？？？

其实可以证明权值的上限是$\log_2n +1$，然后就可以了艹过去了

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=1e4+10,INF=1e9+10;
int tot;
int fir[N],f[N][20];
struct edge
{
	int to;
	int nxt;
}e[2*N];
inline void add(int x,int y)
{
	e[++tot].to=y; e[tot].nxt=fir[x]; fir[x]=tot;
	e[++tot].to=x; e[tot].nxt=fir[y]; fir[y]=tot;
}
inline void dfs(int p,int fa)
{
	for(int j=1;j<=15;j++) f[p][j]=j;
	for(int i=fir[p];i;i=e[i].nxt)
	{
		int q=e[i].to;
		if(q==fa) continue;
		dfs(q,p);
		for(int j=1;j<=15;j++)
		{
			int minn=INF;
			for(int k=1;k<=15;k++)
				if(k!=j) minn=min(minn,f[q][k]);
			f[p][j]+=minn;
		}
	}
}
int main()
{
	int n,a,b,ans=INF;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	dfs(1,0);
	for(int i=1;i<=15;i++)
		ans=min(ans,f[1][i]);
	printf("%d\n",ans);
	return 0;
}
```


观察这个式子，后面取的是一个$\min$。如果$f[q][j]$取到最小值，那么$f[q][]$就只能取次小值了，反之则可以直接取最小值

对于每一个$p$，记录它在哪个$j$取得最小值，最小值多少以及次小值是多少

那么考虑$p$的$j$取多少的时候，就只有两种情况：

1、$j$取值都不是$q$取最小值的位置，那么$j$显然越小越好，即$j=mex\{pos_{q_1},pos_{q_2},...\}$

2、$j$取值是某些$q$中取最小值的位置，那么这些$q$都要取其次小值

这个时间复杂度emmm

不是很会分析，大概是$O(n)$的，因为肯定是能往小取就往小取，所以$pos$应该都不会很大的，再加上数据水的缘故，就是一个常数而已

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=1e4+10,INF=1e9+10;
int tot;
int fir[N],vis[20][2];
struct edge
{
	int to;
	int nxt;
}e[2*N];
inline void add(int x,int y)
{
	e[++tot].to=y; e[tot].nxt=fir[x]; fir[x]=tot;
	e[++tot].to=x; e[tot].nxt=fir[y]; fir[y]=tot;
}
struct dp
{
	int min1,min2;
	int pos;
	inline void update(int id,int num)
	{
		if(num<min1) min1=num,pos=id;
		else min2=min(min2,num);
	}
}f[N];
inline void dfs(int p,int fa)
{
	int maxn=0,sum=0;
	for(int i=fir[p];i;i=e[i].nxt)
	{
		int q=e[i].to;
		if(q==fa) continue;
		dfs(q,p);
	}
	for(int i=fir[p];i;i=e[i].nxt)
	{
		int q=e[i].to;
		if(q==fa) continue;
		vis[f[q].pos][0]+=f[q].min1;
		vis[f[q].pos][1]+=f[q].min2;
		sum+=f[q].min1;
		maxn=max(maxn,f[q].pos);
	}
	maxn+=2;
	f[p].min1=f[p].min2=INF;
	for(int j=1;j<=maxn;j++)
	{
		if(vis[j][0]) f[p].update(j,j+sum-vis[j][0]+vis[j][1]);
		else f[p].update(j,j+sum);
	}
	for(int i=fir[p];i;i=e[i].nxt)
	{
		int q=e[i].to;
		if(q==fa) continue;
		vis[f[q].pos][0]=vis[f[q].pos][1]=0;
	}
}
int main()
{
	int n,a,b;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b);
	}
	dfs(1,0);
	printf("%d\n",f[1].min1);
	return 0;
}
```

---

## 作者：一只书虫仔 (赞：1)

双倍经验（

#### Description

> 给定一棵 $n$ 个点的树，求给每一个点 $i$ 分配一个正整数点权 $w_i$ 使得任意相邻的两个点 $i,j$ 都满足 $w_i \ne w_j$ 且总和最小，输出最小总和。

#### Solution

设 $S_i$ 为 $i$ 的儿子的集合，$f_{i,j}$ 为 $w_i=j$ 时以 $i$ 为根节点的子树的点权总和的最小值，转移方程如下：

$$f_{i,j}=j+\sum\limits_{k \in S_i} \min \limits_{p=1,p \ne j}^{\infty}\{f_{k,p}\}$$

下面对上面这个转移方程进行简要解释，上面这个转移方程也就是说第 $i$ 个点的点权 $w_i=j$，然后枚举所有 $k \in S_i$，然后找到最小的 $f_{k,p}$，但是因为相邻的两个点要满足 $w_i \ne w_j$，因此要保证 $w_i \ne w_k$，即 $p \ne j$。

---

## 作者：ubec (赞：0)

**这篇题解参考了sunshinezff大佬的思路**

首先，我们可以考虑dp，把这个问题看成一个树的染色问题，用dp[i][j]表示以i为根节点，将树染成第i种颜色的最小代价，那么我们可以得到j的最大值是(log(maxn)/log(2)+1)=15,所以循环次数我们开到15就可以了，然后是常规初始化和dp，这里dfs是遍历整棵树寻找答案
```cpp 
#include<bits/stdc++.h>
using namespace std;
const int mx=50001;
int ans;
struct edge
{	
	int v,nxt;
}e[100000];
int cnt,n,dp[mx][16],h[mx];
void add_edge(int u,int v)
{
	e[++cnt]=(edge){v,h[u]};
	h[u]=cnt;
}
void dfs(int u,int fa)
{
	for(int i=h[u];i;i=e[i].nxt)
		if(e[i].v!=fa)
		{
			dfs(e[i].v,u);
			for(int j=1;j<=15;++j)//DP核心！！！！
			{
				int minn=INT_MAX;
				for(int k=1;k<=15;++k)
					if(k!=j) minn=min(minn,dp[e[i].v][k]);
				dp[u][j]+=minn;
			}
		}
	for(int i=1;i<=15;++i)	dp[u][i]+=i;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_edge(x,y);//树是无向图加两遍
		add_edge(y,x);
	}
	dfs(1,0);//这里以1号点为根节点遍历
	ans=INT_MAX;
	for(int i=1;i<=15;++i)
		ans=min(ans,dp[1][i]);
	printf("%d",ans);
	return 0;
}
```


---

