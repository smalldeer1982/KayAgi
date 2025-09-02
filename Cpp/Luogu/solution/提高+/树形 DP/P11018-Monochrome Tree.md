# Monochrome Tree

## 题目描述

给定你一棵根节点为 $1$ 的树，对于任意的节点 $u$ 都只能有两种颜色：黑或白。每个节点 $u$ 的起始颜色都是已知的，记为 $\mathrm{color}_u$。

现在你有两种操作：
- 操作 $1$：把任意一个节点 $u$ 到根节点的路径上节点的颜色全部翻转（路径包括 $u$ 和根节点）。
- 操作 $2$：把任意一个以 $u$ 为根节点的子树上的节点颜色全部翻转（$u$ 的子树包括 $u$）。

现在问你，最少需要几次操作才能把整棵树变成黑色。

## 说明/提示

#### 【数据范围】

对于全部数据，保证：$1 \le n \le 2\times 10^5$， $0\le \mathrm{color}_i\le 1$。

|$\text{Subtask}$|$n\leq$|分值|特殊性质|
|:-:|:-:|:-:|:-:|
|$0$|$5$|$3$|无|
|$1$|$10$|$7$|无|
|$2$|$2\times 10^3$|$29$|无|
|$3$|$2\times 10^5$|$61$|无|

## 样例 #1

### 输入

```
6
0 1 1 1 0 0
1 2
1 3
2 5
5 4
5 6```

### 输出

```
3```

## 样例 #2

### 输入

```
7
0 0 1 0 0 1 1
6 4
3 4
3 5
1 5
7 3
2 7
```

### 输出

```
3```

# 题解

## 作者：arimaw (赞：9)

# Monochrome Tree 题解

一眼树形dp。

首先考虑没有操作 1 的情况（即不用从根到某个节点的翻转操作）。

设 $dp_{x,0/1}$ 表示以 $x$ 为根的子树且子树中的节点颜色都为白/黑色的最少步数。记 $cl_x$ 表示 $x$ 号节点原本的颜色，那么有转移：
$$
dp_{x,0}\gets\min(dp_{y,0},dp_{y,1}+1)
$$

$$
dp_{x,1}\gets\min(dp_{y,1},dp_{y,0}+1)
$$
其中 $y$ 表示 $x$ 的儿子。
特别的，对于叶子节点有
$$
dp_{x,cl[x]}=0,dp_{x,cl[x]\land1}=1
$$

~~所以为什么不给这部分的部分分 QwQ 。~~

接下来我们考虑往其中加入 1 操作，我们发现对于一个节点，我们并不关心 1 操作具体用了几次，只关心使用 1 操作次数的奇偶性（奇数颜色反转，偶数颜色不变），而且 1 操作还具有传递性（可以从儿子传递到父亲），这启发我们考虑一个新的 $dp$ 状态。

设 $dp_{x,0/1,0/1}$ 表示以 $x$ 号节点为根的子树颜色为白 / 黑，且 $x$ 号节点被1操作覆盖了奇 / 偶数次（有 / 没有被覆盖）。

答案即为 $\min(dp_{1,1,0},dp_{1,1,1})$。

接下来我们考虑如何进行转移。

我们发现如果直接处理当前节点和儿子节点的转移并不是很好想（可能是因为我太菜了），由于最终所有儿子的颜色要一样，所以最后的状态并不多，所以我们可以先把儿子的状态合并好，再处理所有儿子到父亲的转移（详见代码）。

因为只是单纯的合并儿子，所以转移比较简单，我们有：
$$
dp_{x,i,j\land k}\gets\min(dp_{x,i,j\land k},dp_{x,i,j}+dp_{y,i,k})
$$

在接下来的讨论中，我们记儿子的状态为 $f$，父亲的状态为 $dp$ 。

接下来我们考虑从儿子转移到父亲，总共有四种情况，所以我们进行分类讨论：

1. $x$ 的颜色不变，且 $x$ 没有被1操作覆盖。
   首先显然有：
   $$
   dp_{x,cl[x],0} \gets f_{x,cl[x],0}
   $$
   但是由于我们可以在 $x$ 处单独进行一次 1 操作，所以还有：
   $$
   dp_{x,cl[x].0} \gets f_{x,cl[x],1}+1
   $$

2. $x$ 的颜色改变，且 $x$ 有被 1 操作覆盖
   显然有:
   $$
   dp_{x,cl[x]\land1,1} \gets f_{x,cl[x]\land1,1}
   $$
   但是我们还是可以在 $x$ 处单独进行一次操作，所以有：
   $$
   dp_{x,cl[x]\land 1,1} \gets f_{x,cl[x]\land1,0}+1
   $$

3. $x$ 的颜色改变，且 $x$ 没有被 1 操作覆盖这种情况我们显然可以从情况 1 转移过来（在 $x$ 处进行一次操作），所以有：
   $$
   dp_{x,cl[x]\land1,0} \gets dp_{x,cl[x],0}+1
   $$
   因为 $x$ 没有被 1 操作覆盖，所以没有第二种转移。

4. $x$ 的颜色不变，且 $x$ 有被 1 操作覆盖
   因为 $x$ 有被 1 操作覆盖颜色却没有改变，所以肯定在 $x$ 处进行了一次二操作，所以有：
   $$
   dp_{x,cl[x],1} \gets dp_{x,cl[x]\land1,1}+1
   $$

到这里就结束了，还有一些细节详见代码。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10,inf=1e9+10;
vector<int> e[N];
int dp[N][2][2],f[N][2][2],cl[N],n;
// 开两个数组是怕转移时出现重复
void clean(int x){
	for(int i=0;i<2;++i) for(int j=0;j<2;++j) f[x][i][j]=inf;
}
void dfs(int x,int fa){
	int fla=0;
	for(int i=0;i<2;++i) for(int j=0;j<2;++j) dp[x][i][j]=inf;
	clean(x);
	for(int y:e[x]){
		if(y==fa) continue;
		dfs(y,x);
		fla++;
		clean(x);
		if(fla==1){
			for(int i=0;i<2;++i) 
			for(int j=0;j<2;++j) 
			f[x][i][j]=dp[y][i][j];
		}//第一个儿子直接赋值就好
		else {
			for(int i=0;i<2;++i) 
			for(int j=0;j<2;++j) 
			for(int k=0;k<2;++k){
		    	f[x][i][j^k]=min(f[x][i][j^k],dp[x][i][j]+dp[y][i][k]);//转移
     		}
		}
		for(int i=0;i<2;++i) for(int j=0;j<2;++j) dp[x][i][j]=f[x][i][j];//复制
	}
    for(int i=0;i<2;++i) for(int j=0;j<2;++j) dp[x][i][j]=inf;
	dp[x][cl[x]][0]=min(f[x][cl[x]][0],f[x][cl[x]][1]+1);
	dp[x][cl[x]^1][1]=min(f[x][cl[x]^1][0]+1,f[x][cl[x]^1][1]);
	dp[x][cl[x]^1][0]=min(dp[x][cl[x]^1][0],dp[x][cl[x]][0]+1);
	dp[x][cl[x]][1]=min(dp[x][cl[x]][1],dp[x][cl[x]^1][1]+1);
//对应题解中的1,2,3,4 注意后两个是dp而不是f
	if(fla==0){
		dp[x][cl[x]^1][0]=1;
		dp[x][cl[x]][0]=0;
		dp[x][cl[x]^1][1]=1;
	}//叶子节点赋初值
}
int main(){
//	freopen("1.in","r",stdin);
//	freopen("E.txt","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&cl[i]);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1,0);
	printf("%d\n",min(dp[1][1][1],dp[1][1][0]));
	return 0;
}
```

第一次写题解有不好的地方请见谅 QwQ。

---

## 作者：Alice2012 (赞：2)

首先考虑简化问题。假设只存在操作 $2$（即翻转子树），考虑如何操作。可以设 $dp_{x,0/1}$ 表示以 $x$ 为根节点的子树全部变为 $0/1$ 的最小操作数，那么有：$dp_{x,0}=\sum_{to\in son(x)}\min(dp_{to,0},dp_{to,1}+1)$，$dp_{x,1}$ 同理。

考虑加入操作 $1$（即翻转其至根节点的链）。思考发现我们只关心当前节点被 $1$ 操作的次数的奇偶性，而不关心具体操作了几次。于是在上文状态的基础上加上一维，$dp_{x,0/1,0/1}$ 表示以 $x$ 为根节点的子树全部变为 $0/1$，且 $x$ 这个结点被 $1$ 操作了奇数/偶数次的最小操作数。

考虑转移：首先考虑合并 $x$ 所有儿子子树的答案，利用这个统一处理好的答案再与 $x$ 结点本身合并，这样转移比直接转移会好处理一些。具体地，设 $dp_{x,i,j}$ 存储前面已处理过的子树答案，则有 $dp_{x,i,j\oplus k}\leftarrow dp_{x,i,j}+dp_{to,i,k}$，当然在代码中处理的时候为避免当前转移影响到后续转移，需要开一个临时数组 $f_{0/1,0/1}$ 存储 $dp_{x,0/1,0/1}$，类似于滚动数组的效果。后续转移也将用 $f_{0/1,0/1}$ 代替所有儿子子树合并完后的答案。

现在考虑如何将儿子子树合并而成的答案与 $x$ 节点进行合并。设 $t=color_x$，即 $x$ 的初始颜色。考虑转移 $dp_{x,t,0}$。首先显然有 $dp_{x,t,0}\leftarrow f_{t,0}$，即 $x$ 和合并后的子树都不需要进行任何操作。再有就是 $dp_{x,t,0}\leftarrow f_{t,1}+1$。此时因为儿子子树内的奇数次 $1$ 操作，$x$ 的颜色已经从 $t$ 变为 $!t$，想要再变回 $t$ 需要单独对 $x$ 进行一次操作 $1$，那么答案即为 $f_{t,1}+1$。综合来看，$dp_{x,t,0}=\min(f_{t,0},f_{t,1}+1)$。

需要注意的点是，从 $f_{!t,0}$ 和 $f_{!t,1}$ 转移是不合法的。下面图示一下从 $f_{!t,0}$ 转移的过程并阐述一下不合法的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/l83y9c7x.png)

$f_{!t,1}$ 不合法的原因同理。

同理，可以得出另外三种状态的转移：

- $dp_{x,t,1}=\min(f_{!t,0}+2,f_{!t,1}+1)$
- $dp_{x,!t,0}=\min(f_{t,0}+1,f_{t,1}+2)$
- $dp_{x,!t,1}=\min(f_{!t,0}+1,f_{!t,1})$

最后，考虑初始状态：对于叶子节点，有 $dp_{x,t,0}=0,dp_{x,!t,0}=dp_{x,!t,1}=1$。同时答案应该是：$\min(dp_{1,1,0},dp_{1,1,1})$。都比较简单就不解释了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=1e18;
int n,a[N],dp[N][2][2],f[2][2];
vector<int>v[N];
void dfs(int x,int fa){
	int cnt=0,t=0;
	dp[x][0][0]=dp[x][0][1]=dp[x][1][0]=dp[x][1][1]=inf;
	for(int i=0;i<v[x].size();i++){
		int to=v[x][i];
		if(to==fa)continue;
		cnt++,dfs(to,x);
		memset(f,0x3f,sizeof(f));
		if(cnt==1)for(int i=0;i<2;i++)for(int j=0;j<2;j++)f[i][j]=dp[to][i][j];
		else for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)f[i][j^k]=min(f[i][j^k],dp[x][i][j]+dp[to][i][k]);
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)dp[x][i][j]=f[i][j];
	}
	dp[x][0][0]=dp[x][0][1]=dp[x][1][0]=dp[x][1][1]=inf,t=a[x];
	dp[x][t][0]=min(f[t][0],f[t][1]+1);
	dp[x][t][1]=min(f[1^t][0]+2,f[1^t][1]+1);
	dp[x][1^t][0]=min(f[t][0]+1,f[t][1]+2);
	dp[x][1^t][1]=min(f[1^t][0]+1,f[1^t][1]);
	if(!cnt)dp[x][t][0]=0,dp[x][1^t][0]=dp[x][1^t][1]=1;
	return;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1,x,y;i<n;i++)
		cin>>x>>y,
		v[x].push_back(y),
		v[y].push_back(x);
	dfs(1,0),cout<<min(dp[1][1][0],dp[1][1][1]);
	return 0;
}
```

---

## 作者：Aventurine_stone (赞：2)

## 1. 题目分析
题目要求用最少的操作将树上的点权全都变为 $1$，很明显的树形 dp 题。~~推了两个小时的状态转移方程。~~  
本题的根节点是固定的，只要分别考虑每个操作对这棵树的影响，状态转移方程不难推出，就是细节处理有一点多。
## 2. 题目做法
既然我们要把树上的点都变成 $1$，我们不妨想成将根节点的子树都变成 $1$。  
我们设 $f$ 为 dp 数组，那么状态表示就是 $f_{i,0}$ 为将 $i$ 节点的子树全部变为 $0$ 的最少操作次数，$f_{i,1}$ 也同理。  
每个节点只有这两个状态够不够呢，当然不够。要知道，虽然每个节点初始只有一个权值，但如果它的子树中有一些点进行了操作一，那么在进行这个点的状态转移时，它很可能不再是原来那个权值了。因为只有在子树有奇数个点进行操作一时，这个点的权值才会改变，若有偶数个点进行操作一则点权不变。故我们 dp 数组的第三维只需要记录 $0$ 和 $1$ 两个值就行。所以 $f_{i,0/1,0}$ 表示这个点的子树中有偶数个点进行了操作一，$f_{i,0/1,1}$ 同理。  
那么状态转移方程也就很简单了。  
我们设除 $i$ 节点外它的子树中点的状态和为 $f_{j,0/1,0/1}$。  
故非叶子节点初始颜色为 $1$，那么状态转移方程如下。  
$f_{i,0,0} = \max(f_{j,1,0} + 1,f_{j,1,1} + 2)$。  
$f_{i,0,1} = \max(f_{j,0,0} + 1,f_{j,0,1})$。  
$f_{i,1,0} = \max(f_{j,1,0},f_{j,1,1} + 1)$。  
$f_{i,1,1} = \max(f_{j,0,0} + 2,f_{j,0,1} + 1)$。  
非叶子节点初始颜色为 $0$ 时同理，稍微修改一下即可。  
如果是叶子节点的话，那么就无法从 $f_{j,0/1,1}$ 转移过来，因为除叶子节点外它的子树就为空了，特判一下就好。  
至于如何合并一个节点上所有儿子结点的信息，很简单，记录四个最小的差值就行了，具体的看我代码。  
最后用一个深搜遍历一下就行了，时间复杂度 $O(n)$。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010,M=400010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x; 
}
int head[N],ne[M],e[M],idx;
inline void add(int x,int y)
{
	ne[++idx]=head[x];
	head[x]=idx;
	e[idx]=y;
}
int n;
bool co[N],vis[N];
struct P{
	int f0[2],f1[2];
};
inline P dfs(int x)
{
	vis[x]=1;
	P t={0,0,0,0},tt;
	int min0[2]={INT_MAX,INT_MAX},min1[2]={INT_MAX,INT_MAX};
	bool p=0;
	int cnt0[2]={0,0},cnt1[2]={0,0};
	for(int i=head[x];i;i=ne[i])
	{
		int c=e[i];
		if(!vis[c])
		{
			p=1;
			tt=dfs(c);
			//记录四个最小差值 
			if(tt.f0[1]<tt.f0[0])
				t.f0[0]+=tt.f0[1],min0[0]=min(min0[0],tt.f0[0]-tt.f0[1]),cnt0[1]++;
			else
				t.f0[0]+=tt.f0[0],min0[1]=min(min0[1],tt.f0[1]-tt.f0[0]),cnt0[0]++;
			if(tt.f1[1]<tt.f1[0])
				t.f1[0]+=tt.f1[1],min1[0]=min(min1[0],tt.f1[0]-tt.f1[1]),cnt1[1]++;
			else
				t.f1[0]+=tt.f1[0],min1[1]=min(min1[1],tt.f1[1]-tt.f1[0]),cnt1[0]++;
		}
	}
	if(p)
	{
		t.f0[1]=t.f0[0],t.f1[1]=t.f1[0];
		if(cnt0[1]&1)
		{
			if(cnt0[0])
				t.f0[0]+=min(min0[0],min0[1]);
			else
				t.f0[0]+=min0[0];
		}
		else
		{
			if(cnt0[0]&&cnt0[1])
				t.f0[1]+=min(min0[0],min0[1]);
			else if(cnt0[0])
				t.f0[1]+=min0[1];
			else
				t.f0[1]+=min0[0];
		}
		if(cnt1[1]&1)
		{
			if(cnt1[0])
				t.f1[0]+=min(min1[0],min1[1]);
			else
				t.f1[0]+=min1[0];
		}
		else
		{
			if(cnt1[0]&&cnt1[1])
				t.f1[1]+=min(min1[0],min1[1]);
			else if(cnt1[0])
				t.f1[1]+=min1[1];
			else
				t.f1[1]+=min1[0];
		}
	}
	tt={0,0,0,0};
	//状态转移 
	if(co[x])
	{
		tt.f0[0]=t.f1[0]+1;
		tt.f0[1]=t.f0[0]+1;
		tt.f1[0]=t.f1[0];
		tt.f1[1]=t.f0[0]+2;
		if(p)
		{
			tt.f0[0]=min(tt.f0[0],t.f1[1]+2);
			tt.f0[1]=min(tt.f0[1],t.f0[1]);
			tt.f1[0]=min(tt.f1[0],t.f1[1]+1);
			tt.f1[1]=min(tt.f1[1],t.f0[1]+1);
		}
	}
	else
	{
		tt.f0[0]=t.f0[0];
		tt.f0[1]=t.f1[0]+2;
		tt.f1[0]=t.f0[0]+1;
		tt.f1[1]=t.f1[0]+1;
		if(p)
		{
			tt.f0[0]=min(tt.f0[0],t.f0[1]+1);
			tt.f0[1]=min(tt.f0[1],t.f1[1]+1);
			tt.f1[0]=min(tt.f1[0],t.f0[1]+2);
			tt.f1[1]=min(tt.f1[1],t.f1[1]);
		}
	}
	return tt;
}
int x,y;
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		co[i]=read();
	for(int i=1;i<n;i++)
	{
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	P t=dfs(1); 
	printf("%d",min(t.f1[0],t.f1[1]));
	return 0;
}
```

---

## 作者：Pentatonic_Vi0lin (赞：2)

### Solution

首先，很容易观察到，**对于一个点执行 $2$ 次同一操作是无意义的**，从而对一个点执行操作的情况有：是否执行操作一与是否执行操作二的共 $4$ 种组合。

其次，一个点受到的影响，仅来自其子树的操作二的个数的**奇偶性**，与这个点本身的操作。同时对自身子树有影响的操作一是翻转整颗子树，说明这棵子树本身必须**全黑或全白**，因而存在局部最优解。

从而，我们考虑树形 dp，从叶子节点向上转移状态，记录为 $f(u,c,t)$，其中 $u$ 为节点编号，$c$ 为其子树所染成的颜色，$1$ 为全黑，$0$ 为全白，$t$ 为其子树中总共进行的操作二次数的奇偶性，$1$ 为奇数，$0$ 为偶数，$f(u,c,t)$ 即为这个点的子树达到这一状态所需操作次数。

令 $u$ 节点颜色为 $color_u$。

对叶子节点状态初始化：

```cpp
f[u][color[u]][0] = 0;（不用操作）

f[u][!color[u]][0] = 1;（操作一）
		
f[u][!color[u]][1] = 1;（操作二）
		
f[u][color[u]][1] = 2;（操作一和二）
```

接下来考虑状态转移，由于一个点有多个子节点，我们要将这些点合并为一些可以代替 $f$ 数组意义的量，同样有颜色和奇偶性两个标度，假定已经知道一些当前点子节点的子树全变成同一颜色，且用了某一奇偶性的操作的最小操作次数，设为 $g_{c,u}$，而要再加入一个子节点，则（令转移后为 $t_{c,u}$）转移来自同一种颜色，奇偶性相同或相反:

```cpp
t[0][0] = min(g[0][0] + f[v][0][0], g[0][1] + f[v][0][1]);

t[0][1] = min(g[0][1] + f[v][0][0], g[0][0] + f[v][0][1]);

t[1][0] = min(g[1][0] + f[v][1][0], g[1][1] + f[v][1][1]);

t[1][1] = min(g[1][1] + f[v][1][0], g[1][0] + f[v][1][1]);
```

最后，由子节点的转移为：

```cpp
f[u][color[u]] [0] = min(g[color[u]][0]//不操作, g[color[u]][1] + 1//只用操作二);

f[u][!color[u]][0] = min(g[color[u]][0] + 1//只用操作一, g[color[u]][1] + 2//用操作一、二);

f[u][!color[u]][1] = min(g[!color[u]][0] + 1//只用操作二, g[!color[u]][1]//不操作);

f[u][color[u]] [1] = min(g[!color[u]][0] + 2//用操作一、二, g[!color[u]][1] + 1//只用操作一);
```

通过递归实现上述过程即可。


### AC Code

以下是 [Pentatonic_Vi0lin](/user/761743) 给出的实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr unsigned inf = INT_MAX >> 1;
constexpr unsigned SIZ = 2e5 + 7;
vector<int> son[SIZ];
bitset<SIZ> color;
int f[SIZ][2][2], n;
void dp_on_the_tree(int u, int fa) {
	f[u][0][0] = f[u][0][1] = f[u][1][0] = f[u][1][1] = inf;
	if (son[u][0] == fa && son[u].size() == 1) {
		f[u][color[u]][0] = 0;
		f[u][!color[u]][0] = 1;
		f[u][!color[u]][1] = 1;
		f[u][color[u]][1] = 2;
		return ;
	}
	int g[2][2]= {{0, inf}, {0, inf}}, t[2][2] = {};
	for (auto v : son[u]) {
		if (v == fa) continue;
 		dp_on_the_tree(v, u);
		t[0][0] = min(g[0][0] + f[v][0][0], g[0][1] + f[v][0][1]);
		t[0][1] = min(g[0][1] + f[v][0][0], g[0][0] + f[v][0][1]);
		t[1][0] = min(g[1][0] + f[v][1][0], g[1][1] + f[v][1][1]);
		t[1][1] = min(g[1][1] + f[v][1][0], g[1][0] + f[v][1][1]);
		memcpy(g, t, sizeof(t));
	}
	f[u][color[u]] [0] = min(g[color[u]][0], g[color[u]][1] + 1);
	f[u][!color[u]][0] = min(g[color[u]][0] + 1, g[color[u]][1] + 2);
	f[u][!color[u]][1] = min(g[!color[u]][0] + 1, g[!color[u]][1]);
	f[u][color[u]] [1] = min(g[!color[u]][0] + 2, g[!color[u]][1] + 1);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> n;
	for (int i=1, c; i<=n; i++) cin >> c, color[i] = c;
	for (int i=1, x, y; i<n; i++) 
		cin >> x >> y, son[x].push_back(y), son[y].push_back(x);
	dp_on_the_tree(1, 1);
	cout << min({f[1][1][0], f[1][1][1], f[1][0][1] + 1, f[1][0][0] + 1}) << '\n';
	return 0;
}

---

## 作者：Claire0918 (赞：1)

我们希望答案是在子树内独立的，这样就可以使用树形 DP，但是操作 1 会对子树外的点产生影响。

我们注意到一个点受操作 1 的影响只与受到操作的次数奇偶性相关，所以可以将奇偶性压在状态里向上转移，解决了对子树外影响的问题。具体来说，设 $f_{u, x, y}$ 表示在以 $u$ 为根的子树中将所有点变成 $x \in \{0, 1\}$ 的颜色，操作 1 的次数奇偶性为 $y \in \{0, 1\}$ 的最小操作次数。

现在考虑树上的一个节点 $u$。因为我们只能对 $u$ 单点或者 $u$ 子树内所有点操作，所以我们要求它的所有儿子的子树内颜色都是相同的，否则无论在 $u$ 上怎样操作，都不能使 $u$ 子树内颜色相同。

状态中 $y$ 的值是受到所有儿子影响的，所以我们需要先将所有儿子的状态合并。记辅助数组 $g_{x, y}$ 表示使所有儿子子树中点的颜色均为 $x$ 且 1 操作的次数之和奇偶性为 $y$ 的最小操作次数。

我们先把已经搜过的儿子的答案压进一个数组 $h_{x, y}$ 中。对于当前的搜索到的儿子 $v$，枚举所有儿子的颜色 $i$，搜索过的儿子的操作 1 奇偶性 $j$，当前儿子的操作 1 奇偶性 $k$，有 $g_{i, j \oplus k} \gets h_{i, j} + f_{v, i, k}$。特别地，如果 $v$ 是首个搜索到的儿子，直接将 $g$ 赋值为 $f_v$。

为了优化空间，我们可以直接将当前还没有用的 $f_u$ 当作 $h$ 使用。

现在我们尝试用 $g$ 来转移 $f_u$。我们枚举 $f_{u, x, y}$ 的 $(x, y)$ 情况。

对于 $f_{u, c_u, 0}$，即 $u$ 不变色，$u$ 子树内没有操作 1。$u$ 没有受到操作 1 且其不变色，这要求 $u$ 没有操作 2，所以儿子的颜色需要与 $u$ 相同。当儿子没有操作 1 时直接转移，有操作 1 时在 $u$ 做一次操作 1 抵消，有 $f_{u, c_u, 0} = \min\{g_{c_u, 0}, g_{c_u, 1} + 1\}$。

对于 $f_{u, c_u, 1}$，即 $u$ 不变色，$u$ 子树内有操作 1。$u$ 受到了操作 1 而其不变色，这显然要求 $u$ 本身进行了一次操作 2，所以儿子的颜色要与其不同。分讨儿子是否有操作 1，得到转移 $f_{u, c_u, 1} = \min\{g_{c_u \oplus 1, 0} + 2, g_{c_u \oplus 1, 1} + 1\}$。

对于 $f_{u, c_u \oplus 1, 0}$，即 $u$ 变色，$u$ 子树内没有操作 1。$u$ 没有受到操作 1 而 $u$ 变色，显然是 $u$ 本身进行了一次操作 2，与第三条类似，有 $f_{u, c_u \oplus 1, 1} = \min\{g_{c_u, 0} + 1, g_{c_u, 1} + 2\}$。

对于 $f_{u, c_u \oplus 1, 1}$，即 $u$ 变色，子树内有操作 1。$u$ 受到了操作 1 且其变色，显然 $u$ 没有进行操作 2，这与第一条类似，有 $f_{u, c_u \oplus 1, 1} = \min\{g_{c_u \oplus 1, 0} + 1, g_{c_u \oplus 1, 1}\}$。

特别地，如果 $u$ 是叶子节点，由定义我们有初始化 $f_{u, c_u, 0} = 0, f_{u, c_u, 1} = 2, f_{u, c_u \oplus 1, 0} = f_{u, c_u \oplus 1, 1} = 1$。

综上，我们完整地解决了 $f_{u}$ 的转移。答案即为 $\min\{f_{1, 1, 0}, f_{1, 1, 1}\}$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2e5 + 10;

struct{
    int v, nex;
} edge[maxn << 1];

int n;
int c[maxn], f[maxn][2][2], g[2][2];
int head[maxn], top = 0;

inline void add(int u, int v){
    edge[++top].v = v;
    edge[top].nex = head[u];
    head[u] = top;
}

inline void dfs(int u, int fa){
    int son = 0;
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        if (v != fa){
            dfs(v, u);
            son++;
            if (son == 1){
                memcpy(g, f[v], sizeof(f[v]));
            }else{
                mem(g, 0x3f);
                for (int j = 0; j < 2; j++){
                    for (int k = 0; k < 2; k++){
                        for (int l = 0; l < 2; l++){
                            g[j][k ^ l] = min(g[j][k ^ l], f[u][j][k] + f[v][j][l]);
                        }
                    }
                }
            }
            memcpy(f[u], g, sizeof(g));
        }
    }
    if (!son){
        f[u][c[u]][0] = 0, f[u][c[u]][1] = 2, f[u][c[u] ^ 1][0] = f[u][c[u] ^ 1][1] = 1;
        return;
    }
    f[u][c[u]][0] = min(g[c[u]][0], g[c[u]][1] + 1);
    f[u][c[u]][1] = min(g[c[u] ^ 1][0] + 2, g[c[u] ^ 1][1] + 1);
    f[u][c[u] ^ 1][0] = min(g[c[u]][0] + 1, g[c[u]][1] + 2);
    f[u][c[u] ^ 1][1] = min(g[c[u] ^ 1][0] + 1, g[c[u] ^ 1][1]);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &c[i]);
    }
    for (int i = 1; i < n; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    printf("%d", min(f[1][1][0], f[1][1][1]));

return 0;
}
```

---

## 作者：sgl654321 (赞：1)

一道非常不错的树形 dp。可以锻炼分类讨论能力。

## 题目大意

给定一棵树，树上每个节点有黑白两种颜色。初始时颜色给定。

有两种操作。一种是从根节点 $1$ 到 $x$ 的路径，所有点颜色反转。还有一种是 $x$ 的子树，所有点颜色反转。

询问最少几次操作把整个树变成全黑色。

## 解题思路

### 设计 dp 状态

考虑弱化问题。如果只有一种操作，这种操作是子树颜色反转，我们如何去做呢？

考虑简单树形 dp。设 $f_{x,p} (p\in \{0,1\})$ 表示 $x$ 为根的子树，操作成所有点颜色均为 $p$ 的最少步数。然后转移是显然的。

接下来考虑原问题。现在多了一种到根节点的路径颜色翻转操作（即操作 $1$），这意味着一个节点的颜色，可能会受其子树中的节点做此操作而影响。那么我们如何设计状态，使每个节点能从各个子节点的 dp 状态转移过来呢？

设根节点到 $z$ 的路径上，经过了两个节点 $x,y$，他们三者的深度满足 $x<y<z$。我们发现，如果在 $z$ 上做一次路径反转，再在 $y$ 上又做一次路径反转，那么 $x$ 的颜色并没有变化。

所以说，一个节点的颜色是否被子树中的节点做操作 $1$ 而影响，只与**子树中各个节点做操作 $1$ 的次数奇偶性有关。**

所以我们可以设计状态：$f_{x,p,q}(p,q\in\{0,1\})$ 表示 $x$ 的子树，操作成所有点的颜色均为 $p$，并且该子树中各个节点做操作 $1$ 的次数的奇偶性为 $q$ 的最少操作次数。

### 考虑边界状态

初始状态：设 $x$ 是一个叶子，其颜色为 $t$。那么，我们有：$f_{x,t,0} = 0, f_{x,1-t,0} = 1,f_{x,1-t,1}=1,f_{x,t,1} = 2$。考虑该节点做不做操作 $1$，做不做操作 $2$ 容易得到。

结束状态：$\min\{f_{1,1,0}, f_{1,1,1}\}$。

### 考虑状态转移

我们要合并所有儿子的信息，再考虑自身节点做不做操作 $1$，做不做操作 $2$ 进行转移。

首先先合并儿子信息。我们设数组 $g_{p,q}(p,q\in\{0,1\})$ 表示当前这些儿子，他们的子树颜色都变成了 $p$，并且总计操作 $1$ 的次数的奇偶性是 $q$ 的最少操作次数。

那么我们容易得到：

$g_{p,q} = \min\{g_{p,q}+f_{y,p,q},g_{p,1-q}+f_{y,p,1-q}\}$。其中 $y$ 是 $x$ 的一个儿子，我们考虑他操作 $1$ 的次数是奇数还是偶数即可。这里可以使用滚动数组进行实现。



接下来考虑自身节点的操作。设这个节点初始颜色为 $t$，我们依次来考虑 $f_{x,t,0},f_{x,t,1},f_{x,1-t,0},f_{x,1-t,1}$。

对于 $f_{x,t,0}$，它要么是直接从 $g_{t,0}$ 转移过来，就不用干别的了。要么是从 $g_{t,1}$ 转移过来。注意到此时 $x$ 的颜色已经变成 $1-t$ 了。我们可以再进行一次操作 $1$ 把它反过来，同时操作 $1$ 次数的奇偶性也发生了改变。所以 $f_{x,t,0} = \min\{g_{t,0},g_{t,1} + 1\}$。

追问：有没有可能从 $g_{1-t,0}$ 或者 $g_{1-t,1}$ 转移过来呢？答案是否定的。举 $g_{1-t,0}$ 说明，此时除了 $x$ 其他子树中的点都是 $1-t$ 为颜色，因此他肯定要做一次子树反转，即操作 $2$。这样它就又要做一次操作 $1$ 来把自己的颜色变回来了。那么操作 $1$ 次数的奇偶性发生了改变，不可能仍然是 $0$ 即偶数次。$g_{1-t,1}$ 同理可以说明无法对其进行转移。

对于 $f_{x,t,1},f_{x,1-t,0},f_{x,1-t,1}$ 的转移也是类似的。大家可以自己推理一下。最后我们整理得到四个转移方程式：

 $f_{x,t,0} = \min\{g_{t,0},g_{t,1} + 1\},f_{x,t,1} = \min\{g_{1-t,0}+2,g_{1-t,1}+1\}$。

$f_{x,1-t,0} = \min\{g_{t,0} + 1,g_{t,1} + 2\},f_{x,1-t,1} = \min\{g_{1-t,0} + 1, g_{1-t,1}\}$

### 总结与回顾

这道题的核心在于发现你只需要关心一个子树中操作 $1$ 次数的奇偶性即可。我们把这个加入状态之中就可以轻松进行转移。同时，这里转移分类讨论比较复杂，需要有足够的模拟能力，因此还是对选手能力有一定要求的。



## 参考代码

我的图论比较抽象，所以大家要学会自己实现啊。

```cpp  
#include<bits/stdc++.h>
#define maxn 200100
#define maxm 400010
using namespace std;
typedef long long ll;
ll n, a[maxn], x, y, kk, poi[maxn], v[maxm], nex[maxm], t, t2;
ll fa[maxn], f[maxn][2][2];
void add_edge(ll x, ll y){
	kk++; v[kk] = y; nex[kk] = poi[x]; poi[x] = kk;
}
void dfs(ll x){
	ll save = poi[x], cnt = 0;
	while(save){
		if(v[save] != fa[x]) cnt++, fa[v[save]] = x, dfs(v[save]);
		save = nex[save];
	}
	if(cnt == 0){
		if(a[x] == 0){
			f[x][0][0] = 0; f[x][1][0] = 1;
			f[x][1][1] = 1; f[x][0][1] = 2;
		}else{
			f[x][1][0] = 0;	f[x][0][0] = 1;
			f[x][0][1] = 1; f[x][1][1] = 2;
		}
		return;
	}
	
	ll g[2][2], gg[2][2];
	save = poi[x];
	gg[0][0] = -1;
	
	while(save){
		if(v[save] != fa[x]){
			if(gg[0][0] == -1){
				for(int i = 0; i <= 1; i++) for(int j = 0; j <= 1; j++)
			 		gg[i][j] = g[i][j] = f[v[save]][i][j];
			 	save = nex[save]; continue;
			}	
			y = v[save];
			g[0][0] = min(gg[0][0] + f[y][0][0], gg[0][1] + f[y][0][1]);
			g[0][1] = min(gg[0][1] + f[y][0][0], gg[0][0] + f[y][0][1]);
			g[1][0] = min(gg[1][0] + f[y][1][0], gg[1][1] + f[y][1][1]);
			g[1][1] = min(gg[1][1] + f[y][1][0], gg[1][0] + f[y][1][1]);
			gg[0][0] = g[0][0]; gg[0][1] = g[0][1];
			gg[1][0] = g[1][0]; gg[1][1] = g[1][1];
		}
		save = nex[save];
	} 
	t = a[x]; t2 = 1 - t;
	f[x][t][0] = min(g[t][0], g[t][1] + 1);
	f[x][t][1] = min(g[t2][0] + 2, g[t2][1] + 1);
	f[x][t2][0] = min(g[t][0] + 1, g[t][1] + 2);
	f[x][t2][1] = min(g[t2][0] + 1, g[t2][1]);
} 
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n; for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i < n; i++)
		cin >> x >> y, add_edge(x, y), add_edge(y, x);
	dfs(1);
	cout << min(f[1][1][0], f[1][1][1]) << endl;
	return 0;
}

```

---

## 作者：jiangzenyu (赞：1)

### P11018 Monochrome Tree

题面跳转：[链接](https://www.luogu.com.cn/problem/P11018)

#### 正文

首先有一个非常显然的性质，对于任意一个点进行两次翻转是还原回未翻转的状态。

因此我们设计一个状态为 $dp[i][0/1]$ 代表对于第 $i$ 个点用黑色或白色全部填满的最少操作数。

那么此时我们会发现我们没有对根部进行记录，因此我们可以再设计一维来保存根部是否被修改。即 $dp[i][0/1][0/1]$ 代表对于第 $i$ 个点用黑色或白色填满并且根部是否被翻转的最少次数。

转移方程便为:

$dp[u][color[u]][0] = \min(son[color[u]][0],son[color[u]][1]+1)$

$dp[u][!color[u]][0] = \min(son[color[u]][0]+1,son[color[u]][1]+2)$

$dp[u][!color[u]][1] = \min(son[!color[u]][0]+1,son[!color[u]][1])$

$dp[u][color[u]][1] = \min(son[!color[u]][0]+2,son[!color[u]][1]+1)$

#### Code


```cpp
#include <bits/stdc++.h>
#define maxn 200010
using namespace std;
int n;
vector<int> g[maxn];
int color[maxn];
int d[maxn][2][2];
void dfs(int u,int f){
	int dp[2][2]= {{0, (1<<30)}, {0, (1<<30)}}, t[2][2] = {};
	for(int i = 0;i<g[u].size();i++){
		int v = g[u][i];
		if(f==v) continue;
		dfs(v,u);
		t[0][0] = min(dp[0][0] + d[v][0][0], dp[0][1] + d[v][0][1]);
		t[0][1] = min(dp[0][1] + d[v][0][0], dp[0][0] + d[v][0][1]);
		t[1][0] = min(dp[1][0] + d[v][1][0], dp[1][1] + d[v][1][1]);
		t[1][1] = min(dp[1][1] + d[v][1][0], dp[1][0] + d[v][1][1]);
		memcpy(dp, t, sizeof(t));
	}
	if(g[u].size()==1 and f!=0){
		d[u][color[u]][0] = 0;
		d[u][!color[u]][0] = 1;
		d[u][color[u]][1] = 2;
		d[u][!color[u]][1] = 1;
		return ;
	}
	if(color[u]==0){
		d[u][0][0] = min(dp[0][0],dp[0][1]+1);
		d[u][1][0] = min(dp[0][1]+2,dp[0][0]+1);
		d[u][0][1] = min(dp[1][0]+2,dp[1][1]+1);
		d[u][1][1] = min(dp[1][1],dp[1][0]+1);
	}
	if(color[u]==1){
		d[u][0][0] = min(dp[1][0]+1,dp[1][1]+2);
		d[u][1][0] = min(dp[1][0],dp[1][1]+1);
		d[u][0][1] = min(dp[0][1],dp[0][0]+1);
		d[u][1][1] = min(dp[0][0]+2,dp[0][1]+1);
	}
	d[u][0][0] = min(d[u][0][0],d[u][1][0]+1);
	d[u][0][1] = min(d[u][0][1],d[u][1][1]+1);
	d[u][1][0] = min(d[u][1][0],d[u][0][0]+1);
	d[u][1][1] = min(d[u][1][1],d[u][0][1]+1);
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&color[i]);
	}
	for(int i = 1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	if(color[1]==0){
		printf("%d",min({d[1][0][0]+1,d[1][0][1]+2,d[1][1][0]+1,d[1][1][1]}));
//		printf(" %d %d %d %d",d[1][0][0]+1,d[1][0][1]+2,d[1][1][0]+1,d[1][1][1]);
	}
	if(color[1]==1){
		printf("%d",min({d[1][0][0]+1,d[1][0][1]+1,d[1][1][0],d[1][1][1]+1}));
	}
	return 0;
}
```

---

## 作者：Ericnoi (赞：0)

# P11018 题解
[题目传送门](https://www.luogu.com.cn/problem/P11018)

提供一种简洁易懂的代码实现。

# 分析

首先确定是树形 DP。接下来考虑如何设计 DP 数组可以消除后效性。

不难发现引入后效性的主要是操作 $1$。又注意到操作 $1$ 只需要区分奇数次和偶数次。因此可以这样设计状态空间：

令 $dp_{u,i,j}$ 表示把以 $u$ 为根节点的子树全部变成颜色 $i$，使用操作 $1$ 的次数模 $2$ 余 $j$，所需要的最少操作数。

转移分两种情况：对节点 $u$ 施加或者不施加操作 $1$。然后根据当前状态，计算子结点操作 $1$ 数量的总和应该是奇数还是偶数。再用经典的做差排序法转移即可。

有人进行了分类讨论。而我使 $8$ 种转移复用一段代码，看起来不臃肿。甚至不需要处理叶子边界。

# AC Code

```cpp
#include <bits/stdc++.h>
#define fill(x, y) memset(x, y, sizeof(x))
#define chkmax(x, y) ((x) = max((x), (y)))
#define chkmin(x, y) ((x) = min((x), (y)))
#define isnumber(x) (((x) >= '0') && ((x) <= '9'))
#define inf (0x3f3f3f3f)
using namespace std;
void solve();
signed main() {
    int cx = 1;
    // cin >> cx;
    while(cx--) {
        solve();
    }
    return 0;
}
const int N = 2e5 + 5;
int n, w[N], dp[N][2][2];
vector<int> a[N];
void dfs(int u, int f) {
    vector<int> son;
    for(int v : a[u]) {
        if(v == f) continue;
        dfs(v, u);
        son.push_back(v);
    }
    for(int col = 0 ; col <= 1 ; col++) {
        for(int cnt = 0 ; cnt <= 1 ; cnt++) {
            int normal_col = col ^ cnt;
            if(w[u] == normal_col) {
                for(int cur = 0 ; cur <= 1 ; cur++) {
                    vector<int> tmp;
                    int even = cur ^ cnt ^ 1, now = 0;
                    for(int v : son) {
                        now += dp[v][col][0];
                        tmp.push_back(dp[v][col][1] - dp[v][col][0]);
                    }
                    sort(tmp.begin(), tmp.end());
                    for(int i = 1 ; i < tmp.size() ; i++) {
                        tmp[i] += tmp[i-1];
                    }
                    int delta = even ? 0 : inf;
                    int start_pos = even ? 1 : 0;
                    for(int i = start_pos ; i < tmp.size() ; i += 2) {
                        chkmin(delta, tmp[i]);
                    }
                    now += delta + cur;
                    chkmin(dp[u][col][cnt], now);
                }
            }
        }
    }
    chkmin(dp[u][0][0], dp[u][1][0] + 1);
    chkmin(dp[u][1][0], dp[u][0][0] + 1);
    chkmin(dp[u][0][1], dp[u][1][1] + 1);
    chkmin(dp[u][1][1], dp[u][0][1] + 1);
}
void solve() {
    cin >> n;
    for(int i = 1 ; i <= n ; i++) {
        cin >> w[i];
    }
    for(int i = 1 ; i < n ; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    fill(dp, 0x3f);
    dfs(1, 0);
    cout << min(dp[1][1][0], dp[1][1][1]) << endl;;
}


```

---

