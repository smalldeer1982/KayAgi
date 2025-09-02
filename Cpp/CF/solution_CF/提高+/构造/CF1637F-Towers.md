# Towers

## 题目描述

You are given a tree with $ n $ vertices numbered from $ 1 $ to $ n $ . The height of the $ i $ -th vertex is $ h_i $ . You can place any number of towers into vertices, for each tower you can choose which vertex to put it in, as well as choose its efficiency. Setting up a tower with efficiency $ e $ costs $ e $ coins, where $ e > 0 $ .

It is considered that a vertex $ x $ gets a signal if for some pair of towers at the vertices $ u $ and $ v $ ( $ u \neq v $ , but it is allowed that $ x = u $ or $ x = v $ ) with efficiencies $ e_u $ and $ e_v $ , respectively, it is satisfied that $ \min(e_u, e_v) \geq h_x $ and $ x $ lies on the path between $ u $ and $ v $ .

Find the minimum number of coins required to set up towers so that you can get a signal at all vertices.

## 说明/提示

In the first test case it's optimal to install two towers with efficiencies $ 2 $ at vertices $ 1 $ and $ 3 $ .

In the second test case it's optimal to install a tower with efficiency $ 1 $ at vertex $ 1 $ and two towers with efficiencies $ 3 $ at vertices $ 2 $ and $ 5 $ .

In the third test case it's optimal to install two towers with efficiencies $ 6 $ at vertices $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
3
1 2 1
1 2
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1 3 3 1 3
1 3
5 4
4 3
2 3```

### 输出

```
7```

## 样例 #3

### 输入

```
2
6 1
1 2```

### 输出

```
12```

# 题解

## 作者：syzf2222 (赞：13)

其实不是一道什么很难的题……但我就是考场做不出来

首先只有叶子上才会填数，其他都是零，正确性显然。

我们以 $h$ 值最大的为根，那么就至少要在两个子树里有 $h_{rt}$，对于其他点，只要在子树内存在不小于自身 $h$ 值的就可以了。

于是我们遍历全树，每次在子树内贪心地选择目前最大的已填的 $h$ 值，如果不小于自身 $h$ 值就不用管了，否则将其改为自身 $h$ 值。对于根，我们选择最大和次大就好了。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
#define ll long long
int n,m,h[maxn];ll ans;
int beg[maxn],nex[maxn<<1],to[maxn<<1],e;
inline void add(int x,int y){
	e++;nex[e]=beg[x];beg[x]=e;to[e]=y;
	e++;nex[e]=beg[y];beg[y]=e;to[e]=x;
}
inline int dfs(int x,int fa){
	int Mx1=0,Mx2=0;
	for(int i=beg[x];i;i=nex[i]){
		int t=to[i];
		if(t==fa)continue;
		int p=dfs(t,x);
		if(p>Mx1)Mx2=Mx1,Mx1=p;
		else if(p>Mx2)Mx2=p;
	}
	if(fa){
		ans+=max(0,h[x]-Mx1);
		Mx1=max(Mx1,h[x]);
	}else ans+=max(0,h[x]-Mx1)+max(0,h[x]-Mx2);
	return Mx1;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)h[i]=read();
	for(int i=1,x,y;i<n;i++)
		x=read(),y=read(),add(x,y);
	int rt=1;
	for(int i=2;i<=n;i++)
		if(h[rt]<h[i])rt=i;
	dfs(rt,0);
	printf("%lld\n",ans);
	return 0;
}
```

深深地感到自己的弱小。

---

## 作者：CarroT1212 (赞：3)

+ 关键词：贪心

很神秘的题。

首先很明显所有的塔都建在叶子（含度数为 1 的根）上面最优。为了单独照顾那些太高的点而在其它地方建显然不如全部交给叶子打包处理。

那么这里有一个转化：一个点被覆盖当且仅当它作根时，它有至少两个儿子的子树内建了高度不小于 $h_i$ 的塔，或者它自己头上建了一个。

其实这里对路径问题的处理有点像点分治，就是只考虑路径两端分别在两棵子树里的情况。

两棵子树的话有点复杂，要不转成一棵子树？

所以先把 $h_i$ 最大的点拎出来当根，这样它两边都得有一棵子树符合条件。那么这时如果再往下搜索，相当于只用使除根以外的每个点儿子的一棵子树高度达到 $h_i$ 即可，因为根的另一侧肯定有另一个达到 $h_i$ 的。

那么就是维护每个点下面叶子上面建的塔的最大高度，如果一个点的儿子遍历完了发现下面一座高度足够的塔都没有，就把那个最高的塔往上加到 $h_i$，否则直接用那个最高的塔。到根节点的时候要取最高和次高的塔计算。

这样加出来就是答案了。

```cpp
ll n,h[N],pos,ans;
vector<ll> e[N];
ll dfs(ll p,ll f) {
	ll mx1=0,mx2=0;
	for (ll i:e[p]) if (i!=f) {
		mx2=max(mx2,dfs(i,p));
		if (mx1<mx2) swap(mx1,mx2);
	}
	if (p==pos) ans+=max(h[p]-mx1,0ll)+max(h[p]-mx2,0ll);
	else ans+=max(h[p]-mx1,0ll),mx1=max(mx1,h[p]);
	return mx1;
}
int main() {
	scanf("%lld",&n);
	for (ll i=1;i<=n;i++) {
		scanf("%lld",&h[i]);
		if (h[i]>h[pos]) pos=i;
	}
	for (ll i=1,x,y;i<n;i++) scanf("%lld%lld",&x,&y),e[x].pb(y),e[y].pb(x);
	dfs(pos,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Alex_Wei (赞：3)

> CF1637F Towers

考虑这样一个过程：我们总会在某两个经过 $h_{\max}$ 的叶子 $x, y$ 处放上 $h_{\max}$，那么 $x, y$ 之间所有点均被覆盖。接下来，每选择一个叶子 $u$，我们都希望能够利用 $x$ 或 $y$，在 $u$ 处放一个尽量小的塔，能够覆盖从 $u$ 到离它最近的一个已经被覆盖的节点（不含）的所有节点，其权值即这些节点的 $h$ 值的 $\max$。

根据上述理解，我们有如下贪心算法：考虑在一开始在所有节点处都放上 $h$，然后将所有标记 **下放**。具体地，从权值最大的节点开始（因为它最特殊，要有两个叶子才能覆盖，其它节点只要一个叶子：利用已经放上 $h_{\max}$ 的 $x$ 或 $y$）对整棵树进行深度优先搜索。对于根节点，它要有 **两棵** 子树各一个叶子节点放上 $h_{\max}$。对于其它节点 $u$，它只需要有某个子树的某个叶子节点放上 $\geq h_u$ 的权值即可。

因此，记录 $f_u$ 表示子树 $\max h$。对于叶子节点 $v$，令答案加上 $h_v$。对于非根节点 $u$，令答案加上 $\max(0, h_u - \max\limits_{v\in \mathrm{son}(u)} f_v)$。对于根节点 $R$，令答案加上 $2h_R$ 减去其子节点最大的两个 $f$ 值。最终答案即为所求。时间复杂度是极其优秀的线性，[代码](https://codeforces.com/contest/1637/submission/146185023)。

赛时做法：以最大值节点为根对整棵树进行深度优先搜索，标记根节点。按权值从大到小遍历每个非最大值节点，若当前节点 $u$ 没有被覆盖，则找到最近的被覆盖的祖先 $a$。若 $a$ 的路径已经延伸到其它子树里面（这意味着 $u$ 不是 $a$ 的 $f$ 值最大的子树），说明我们可以将 $u$ 的子树的某个叶子放上 $h_u$，从而覆盖 $u\to a$ 上的所有节点，令其权值为 $h_u$。否则，我们可以直接让 $a$ 的路径延伸到 $u$，令其权值为 $a$ 的权值。每个叶子的权值之和即为所求。注意若祖先为根节点，则必须向下延伸 $2$ 条路径，$u$ 才能在自己的子树内放上 $h_u$ 而非 $h_a$。[代码](https://codeforces.com/contest/1637/submission/146132848)。

---

## 作者：intel_core (赞：2)

我们显然可以把塔都挪到叶节点上，换成只有叶节点有塔的情况。

发现节点 $u$ 可以收到信号等价于以 $u$ 作为根的时候有至少两个不同的子树内有高度 $\ge h_u$ 的塔。

选高度最大的点作为根，则根的子树里至少有两个子树内有高度 $\ge h_{rt}$ 的塔。

所以非根的节点只需要保证自己子树内有一个节点上的塔 $\ge h_u$ 即可。

如果当前 $u$ 子树内没有高度 $\ge h_u$ 的子树，那么把当前子树内最高的塔加高成 $h_u$，否则不用管。

根节点要特判一下，复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=2e5+10;
#define int long long
int n,a[NR],rt,ans;
#define pb push_back
vector<int>g[NR];

int dfs(int id,int fath){
	int v1=0,v2=0,tmp;
	for(int x:g[id])
		if(x!=fath){
			tmp=dfs(x,id);
			v2=max(v2,tmp);
			if(v1<v2)swap(v1,v2);
		}
	if(id!=rt){
		ans+=max(0ll,a[id]-v1);
		v1=max(v1,a[id]);
		return v1;
	}
	ans+=max(0ll,a[id]-v1)+max(0ll,a[id]-v2);
	return 0; 
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),rt=a[rt]<a[i]?i:rt;
	for(int i=1,x,y;i<n;i++)
		scanf("%lld%lld",&x,&y),g[x].pb(y),g[y].pb(x);
	dfs(rt,0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：juruo999 (赞：1)

题目：[1637F](https://www.luogu.com.cn/problem/CF1637F)

一句话题意：给定一颗树，点权为高度，要求在一些节点建塔，势能可以自己决定，使得对于每个节点 $x$，都存在两个带塔的节点 $u$ 和 $v$ 使得 $x$ 在 $u$ 与 $v$ 间的路径上，且 $u$ 与 $v$ 的塔的势能均不低于 $x$ 的高度。使所有塔的总势能最小。

---

很好玩的一道构造题。

**事实一**：每个度为 $1$ 的节点都必须要建塔。

很显然，如果该节点没有塔的话路径肯定覆盖不到它。

**事实二**：如果两个塔的路径上有第三个塔，移除第三个塔肯定不劣。

不妨设塔 $x$ 和 $z$ 间有塔 $y$，势能分别为 $e_x,e_y,e_z$，则令 $e'_x=\max\{e_x,e_y\}$，$e'_y=0$，将塔 $y$ 移动到 $x$，肯定不劣。

![](https://cdn.luogu.com.cn/upload/image_hosting/0fti7kkf.png)

综上，一定要在所有度为 $1$ 的节点上放塔，且在其他地方不应该放塔（否则删掉不会更差）。

然后似乎就没啥思路了……

---

~~碎碎念时间~~

当没啥思路的时候，一般可以尝试下按照这类问题的一般套路想。考虑一个非叶节点怎么被覆盖。很显然，要么是两个儿子的子树各出一个塔，要么是子树内和子树外的两个塔。

第一种比较简单，第二种情况就很麻烦。麻烦的原因是什么呢？因为要考虑子树外的部分。那么如果我们保证子树外一定不用考虑，那问题不是简单了很多？

~~那就要考虑如何不用考虑了。~~

---

假设当前节点为 $u$，发现**如果子树外总存在一个节点** $v$，**其高度更高，那么覆盖它的塔势能一定高于** $v$，也当然高于 $u$，所以子树外面的那个塔总能找出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/uhlj8j3d.png)

那么怎么能保证子树外总存在一个更高的点呢？**把最高的点当成根** 就行了。

然后考虑子树内咋做，可以考虑调整法。具体来说，若子树内**有高度超过 $u$ 的塔**，那么 $u$ 满足条件。否则，**把子树内高度最高的塔** 的高度提高到 $h_u$，代价为 $h_u-e$。（$e$ 为高度最高的塔的高度）。

于是有以下做法：

1. 首先把 $h$ 最大的点作为根；

2. 对于每个非根节点，递归，并统计出子树中高度最高的塔，并调整该塔高度；

3. 对于根节点，若它只有 $1$ 个儿子（即度为 $1$），那么在该点上放塔。否则，选择高度最高与次高的塔进行调整。

复杂度 $O(n)$，可过。

# Code

```cpp

// cyb cutecute

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
typedef long long ll;

int n;
int h[200005];
vector<int> E[200005];
int fa[200005];

ll ans=0;
int dfs(int u){
    int fst=0,sec=0;
    for(auto v:E[u]){
        if(v==fa[u]) continue;
        fa[v]=u;
        int t=dfs(v);
        if(t>=fst){ sec=fst,fst=t; }
        else if(t>=sec) sec=t;
    }
    if(fa[u]==0){ ans+=max(0,h[u]-fst)+max(0,h[u]-sec); return 0; }     // 当 sec=0 时 max(0,h[u]-sec)=h[u]
    else{
        if(fst<h[u]) ans+=h[u]-fst,fst=h[u];
        return fst;
    }
}

int rt=1;

int main(){

    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>h[i];
    for(int i=1;i<n;i++){ int u,v;cin>>u>>v;E[u].push_back(v);E[v].push_back(u); }

    for(int i=2;i<=n;i++) if(h[rt]<h[i]) rt=i;

    dfs(rt);
    cout<<ans<<"\n";

    return 0;
}
```

---

## 作者：刘梓轩2010 (赞：0)

# CF1637F Towers 题解

## 题意

给你一棵树，树上的每一个节点都有一个高度，编号为 $i$ 的点的高度为 $h_i$。你可以在这些点中选任意多的点建信号塔，建一座权值为 $e$ 的塔花费为 $e$。

我们称一个点收到了信号，当且仅当存在一条路径，使得路径上的两个端点的权值都大于等于这个点的高度，问你令每个点都收到信号的最小花费。

## 思路

（温馨提示：下文中的高度并不是节点深度）

首先不难想到，每一座塔一定建在树的叶子上，因为任何非叶节点都能被叶节点替代。如果我在某个非叶节点上建了塔，为了满足要求，一定有另一个节点的权值大于等于这个节点的高度，那么我完全可以找到子树内的另一个叶节点，让它的权值大于等于当前节点的高度，这样的花费一定是更小的；另一方面，为了满足每个点都被覆盖的要求，每个叶节点一定有塔。所以，叶结点上一定有塔，而且只有叶结点上有塔。

上面的论述启发我们想到贪心的思路。首先，对于最大值，一定有两个叶节点上的塔的权值是最大值；对于其他的节点，我们令路径的一个端点是其中的一个最大值，另一个端点是当前节点子树内的某一个叶子，这样即可满足要求。

那么我们可以这么做：以一个高度最大的点为根，对于非根节点，如果当前节点的高度大于子树内的权值最大的塔的权值，那么就让这个权值变成当前节点的高度，否则不变；对于根节点，我们令整棵树权值最大的两个叶子的权值都变成最大的高度。不难证明，这样一定是最优的。

不理解可结合代码食用。

时间复杂度 $O(n)$。

## 代码
```c++
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
int n;
int h[N];
int ans;
vector<int> G[N];
int dfs(int u,int fa)
{
	int maxn1=0,maxn2=0;
	for(auto v:G[u])
	{
		if(v==fa) continue;
		int p=dfs(v,u);
		if(p>maxn1) maxn2=maxn1,maxn1=p;
		else if(p>maxn2) maxn2=p;
	}
	if(fa!=0) ans+=max(0ll,h[u]-maxn1);
	else ans+=max(0ll,h[u]-maxn1)+max(0ll,h[u]-maxn2);
	maxn1=max(maxn1,h[u]);
	return maxn1;
}
signed main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false); 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>h[i];
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u); 
	}
	int s=1;
	for(int i=1;i<=n;i++)
	{
		if(h[i]>h[s]) s=i;
	}
	dfs(s,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：eb0ycn (赞：0)

# [CF1637F towers](https://www.luogu.com.cn/problem/CF1637F) 题解

## 题意

感觉原题面有点误导，我就写个等价的题意。

给定一棵 $n$ 个结点的树，每个结点都有一个值 $h_i$。

现在你要把树上的第 $i$ 个结点赋值为 $e_i$，使得对于任意一个结点 $x$，总有**两个点** $u,v$ 满足下列条件：

- $u \ne v$；

- $i$ 在 $u$ 到 $v$ 的路径上；

- $\min (e_u,e_v) \ge h_x$。

求 $\large \sum _ {i=1} ^n e_i $ 的最小值。

原题面说要保证 $e_i > 0 $，其实没必要，因为 $e_i = 0$ 对结果没有影响。

## 思路

经过简单归纳可以得出，**把 $h_i$ 值最大的结点（以下简称“最大点”）设置在根结点是最优的**。这个我们能用反证法证一下：如果“最大点”不在树根，我们就需要把局部的某些结点的 $e_i$ 弄得很大，但这对整棵树没多少作用。所以，把“最大点”设置在根结点一定是最优的。

同时，**叶子结点的 $e_i$ 一定大于零**。这一点我放一幅图解释。下图标绿的点满足 $e_i > 0$。

![](https://cdn.luogu.com.cn/upload/image_hosting/t8jmpbdq.png)

### 做法：

设 $zd_i$ 为以 $i$ 为根结点的子树的所有结点的 $h_i$ 的最大值。

用 DFS 算法，先从根结点往下搜。

- 假设每次搜到结点 $x$；

- $x$ 为叶子结点时，$e_x \gets h_x$。

- 回溯时更新 $zd_x$，把当前 $e_i$ 最大的叶子结点的 $e_i$ 改为 $zd_x$，此时答案的增加量最小。

回溯到根结点时，设根结点的编号为 $maxtot$，分两种情况讨论：

#### 一、根结点只有一个儿子结点。

此时，根结点的 $\large e _ {maxtot} \gets h _ {maxtot}$，并且“最大点”的 $\large e_i \gets h_{maxtot} $。

![](https://cdn.luogu.com.cn/upload/image_hosting/l647e38t.png)

#### 二、根结点有两个及以上儿子结点。

此时，根结点的 $e_i$ 等于零就行了，但是要让来自**两个不同子树**的“最大点”的 $\large e_i \gets h_{maxtot}$。因为这样答案的增加值最小。

![](https://cdn.luogu.com.cn/upload/image_hosting/xt9k5dac.png)

有点抽象，具体看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,h[200001],zd[200001],cd[200001],u,v,maxtot;//maxtot表示h值最大的结点下标（根结点）。
/*zd[x]表示以x为根的子树（以下简称：x子树）所有点的最大值， 						（zd：最大） 
cd[x]表示以x为根的子树，除了zd[x]所在的子树以外（以下简称：x'子树）所有点的最大值。（cd：次大） 
这里建议好好理解一下。*/
vector<int>vec[200001];
#define ll long long
ll ans;
void dfs(int x,int fa)//表示第x个结点的父亲是fa。
{
	int s=vec[x].size();
	if(x-maxtot&&s==1)zd[x]=h[x],ans+=h[x];
	/*x不是根结点，只有一条连边，就说明是叶子结点。
	以叶子结点为根的子树只有一个结点，就是它本身，所以zd[x]显然就是h[x]。
	由于我们暂定h[x]最大，所以答案先加上h[x]，相当于暂定叶子结点的b值等于它本身的h值。*/
	for(int i=0;i<s;++i)
	{
		int p=vec[x][i];
		if(p==fa)continue;//无向图，不能“超级加辈”。
		dfs(p,x);
		if(zd[p]>zd[x])cd[x]=zd[x],zd[x]=zd[p];//如果它的子结点的最大值大于目前的最大值，更新最大值。
		else if(zd[p]>cd[x])cd[x]=zd[p];
		//注意：这个cd[x]很重要，这里我们暂且抽象地理解成“次大值”，具体见代码后面的证明。
	}//现在已经更新完子树的最大值和次大值了。
	if(x-maxtot)//如果当前点不是根结点，还要计算当前点的h值，从而再一步更新最大值。
	{
		if(h[x]>zd[x])ans+=h[x]-zd[x],zd[x]=h[x];
		//这里不传次大值，是为了看出来它的父亲结点是否有多个儿子。具体看后面的证明。
	}
	else//如果是根结点，就要算最终答案啦！由于根结点的h值最大，所以答案一定是要更新的。 
	{
		if(cd[x])ans+=(h[x]<<1)-zd[x]-cd[x];
		else ans+=(h[x]<<1)-zd[x];
		/*如果有cd[x]，说明根有两个以上的儿子结点，
		此时的操作相当于把最大值和次大值所在的结点的b值改为根结点的h值。
		如果没有cd[x]，说明根结点只有一个儿子结点，
		此时的操作相当于给根结点和最大值所在的结点的b值定为h[maxtot]。*/
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",h+i),maxtot=h[i]>h[maxtot]?i:maxtot;
	//这里选的是第一个最大值，但其实所有h值最大的点都可以作为根结点。
	for(int i=1;i<n;++i)scanf("%d%d",&v,&u),vec[v].push_back(u),vec[u].push_back(v);
	dfs(maxtot,-1);
	printf("%lld",ans);
	return 0;
}
/*证明：
由 22 23 行可知，“次大值”存在的条件是zd[p]<=zd[x]，
如果p在x的第一个子树里面，运行到22行，zd[x]还没更新，还是0，但zd[p]已经有值了。
所以，“次大值”存在，说明此时在搜索的已经不是第一个子树了。
由此，我们可以用“次大值”判断某个结点是否有两个或两个以上儿子。 
*/ 

```


说实在的，这个难度真的没必要评紫……

---

## 作者：Cure_Wing (赞：0)

[CF1637F Towers](https://www.luogu.com.cn/problem/CF1637F)

### 思路

看到 $\min(e_u,e_v)⩾h_x$ 这个条件，目光很容易看到最大 $h_i$ 上。因为一旦 $u\to v$ 这条路径经过 $h_{\max}$ 时，整条路径就都被解决了。也就是说，我们需要保证有两个点满足 $e_u=e_v=h_{\max}$，且 $u\to v$ 经过 $h_{\max}$。

然后我们继续想，这条路径能有多长？考虑将路径端点下移，如果下端的 $h_v$ 小于或等于当前的 $e_u$，那么端点可以带权值下移，因为 $e_u\ge h_v$，下移不会影响原有的路径，而且可以多加一个点；而如果说下端的 $h_v$ 大于当前的 $e_u$，我们可以把 $e_u$ 下移同时更新为 $h_v$，因为如果不连 $v$，那么就需要新开一条路径，且权值至少为 $h_v$，加上上方的路径权值和一定大于连起来的路径。所以这条路径可以一直向下，直到叶子节点，也就确定了路径端点一定是叶子结点，权值一定赋在它们上面。

确定了路径长，我们可以想象有两个叶子节点，它们的权值为 $h_{\max}$，连接起了最大值。对于剩下的路径，我们把它一端接在 $h_{\max}$ 上，另一端接在其它的叶子节点上，而为了保证题目要求，又因为 $h_u\le h_{\max}$，所以另一端点的权值 $e_v=\max h_{v\to\max}$。

那么每个叶子节点的权值要如何计算呢？考虑叶子节点权值的最小值，那肯定是它本身 $h_i$，我们让它带着权值往上检验，遇到 $h_u\le h_i$ 的直接跳过，遇到 $h_u>h_i$ 的直接把 $h_i$ 改成 $h_u$。如果多个叶子结点的权值同时检验一个节点，那么就拿权值最大的检验，因为就算要改，它的差价也是最小的。

但是这样有一个问题，就是 $h_{\max}$ 在计算时只会改动到一个叶子结点，不符合题目要求了。如果往上再找一个节点，那就太麻烦了，怎么办呢？让两条路径都向下不就好了？于是乎我们让 $h_{\max}$ 成为树根，当合并到树根时去检验 $h_{\max}$，这样只需要一次递归就可以解决问题了。

具体合并的时候，就和其它节点一样，只不过它需要两个端点，所以要同时记录最大权值和次大权值，然后检验差价就可以了。可是如果这个最大节点只有一个儿子怎么办呢？考虑此时它成为了叶子结点，那么直接在这个位置赋上 $h_{\max}$ 就可以了，也可以看做是另一条路权值为 $0$。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=200005;
int n,h[N],u,v,id,f[N][2];
long long ans;
std::vector<int>edge[N];
inline int down(int u,int fa){
	int m1=0,m2=0;
	for(auto i:edge[u]){
		if(i==fa) continue;
		int k=down(i,u);
		if(k>m1){m2=m1;m1=k;}//寻找最大权值
		else if(k>m2) m2=k;//树根还需要次大权值
	}
	if(fa) ans+=std::max(0,h[u]-m1);//普通节点直接检验下方权值，当它为叶子结点时，可以发现m1=0，那么赋的值就是hu。
	else ans+=std::max(0,h[u]-m1)+std::max(0,h[u]-m2);//树根要检验两条路径
	return std::max(m1,h[u]);//向上传递实际权值
}
signed main(){
	freopen("tower.in","r",stdin);
	freopen("tower.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>h[i];
		if(h[i]>h[id]) id=i;//找到最大 hi 点
	}
	for(int i=1;i<n;++i){
		cin>>u>>v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	down(id,0);//将它作为树根
	cout<<ans;
    return 0;
}
```

---

## 作者：紊莫 (赞：0)

好强，但模拟赛看错题意挂了一大堆分。

首先我们发现，当钦定一个点为根节点时，两边的值都需要大于等于根节点的值，那么显然，放的越远越优，因为贡献是不变的。

好，然后问题来了，钦定哪个点呢？我们选择最大的点，这样的话有一个非常优美的性质，就是我们在进一步修改子树的时候不会改变祖先的答案，想象一下假如选了一个非最大节点，那么在处理到最大点的时候就会“不够用”，那么此时就需要修改父亲的答案，非常麻烦，而选择最大点可以让我们操作下面的时候没有“后顾之忧”，相当于一端已经确定，只需要考虑另一端即可。

另一个坑点是你不能够单纯记录最大值，因为可能这两点的 LCA 是作为儿子节点出现的，必须记录子树的最大值。

最后是两种计算方法，一种是根节点，那么需要找到最大值和次大值作为两个端点，另一种只需要考虑最大值，假如最大值不够，那么就需要补全一部分。

```cpp
if(!fa) ans+=2*h[now]-mx[now]-m;//根
else if(h[now]>mx[now]) ans+=h[now]-mx[now];
```


---

## 作者：SamHJD (赞：0)

## [CF1637F Towers](https://www.luogu.com.cn/problem/CF1637F)

### 题意

给出一棵树，每个点有一个高度 $h_i$，你需要为每一个点赋上一个势能 $e_i\ge 0$。使得对于任意一个点 $p$，都有两个点 $u,v$ 满足 $u$ 到 $v$ 的简单路径经过 $p$，并且 $\min(e_u,e_v)\ge h_p$。

求 $\min\sum e_i$。

---

### 解法

显然，最优情况中，$e_i>0$ 的点都在叶子上。否则没有一条简单路径经过一个 $e_i=0$ 的叶子。

以 $h_i$ 最大的点为根，那么需有两个子树内存在 $e_i\ge h_{rt}$ 的点，其余子树只需满足存在一个 $e_i\ge$ 子树根的 $h$ 即可。

设 $f_u$ 为以 $u$ 为根的子树中满足上述**其余子树**情况下最大的 $e_i$，则有如下转移式：

$$f_{u}=\max(\max(f_{v}),h_u)$$

若最外层 $h_u$ 为最大值，那么意味着需要更改方案，为了花费尽可能小，将最大的 $f_v$ 对应的 $e_i$ 修改为 $h_u$。

回溯到根时，最坏情况需要找出前两个最大的 $f_v$ 对应的 $e_i$，修改为 $h_{rt}$，于是需要记录最大和次大。

---

### [代码](https://www.luogu.com.cn/paste/gdhn8tkm)

---

## 作者：Caiest_Oier (赞：0)

# [CF1637F](https://www.luogu.com.cn/problem/CF1637F)   

奇怪的思路。     

不难发现可以把塔全放到叶子。考虑将高度最大的点作为根，会存在两个值为 $h_{rt}$ 的点分布在两个不同的子树中，发现对于每个点 $i$，如果其子树内存在一个值为 $h_i$ 的点，则一定可以与一个值为 $h_{rt}$ 的点连一条路径。于是对于每个点 $i$ 只需要考虑子树内的情况即可。     

考虑贪心取，递归整棵树，对于点 $i$，其所有子树内最高的塔，将其增高到 $h_i$ 即可。    

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,h[500003],ans,rt,mx[500003],k1,k2;
vector<int>E[500003];
int stk[500003],tot;
void dfs(int now,int p){
	if(E[now].size()==1){
		if(!p){
			mx[now]=h[now];
			ans+=h[now];
			dfs(E[now][0],now);
			ans+=max(h[now]-mx[E[now][0]],0ll);
			return;
		}
		else{
			mx[now]=h[now];
			ans+=mx[now];
			return;
		}
	}
	for(auto i:E[now]){
		if(i==p)continue;
		dfs(i,now);
	}
	tot=0;
	for(auto i:E[now]){
		if(i==p)continue;
		stk[++tot]=mx[i];
		mx[now]=max(mx[now],mx[i]);
	}
	mx[now]=max(mx[now],h[now]);
	sort(stk+1,stk+tot+1);
	if(p==0)ans+=max(0ll,h[now]-stk[tot])+max(0ll,h[now]-stk[tot-1]);
	else ans+=max(0ll,h[now]-stk[tot]);
	return;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&h[i]);
	for(int i=1;i<n;i++){
		scanf("%lld%lld",&k1,&k2);
		E[k1].emplace_back(k2);
		E[k2].emplace_back(k1);
	}
	for(int i=1;i<=n;i++){
		if(rt==0||h[i]>h[rt])rt=i;
	}
	dfs(rt,0);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：0)

我高度怀疑这是不是 `*2500` 难度的题，感觉我这种脑子不应该这么快想出来吧（

## 思路

一眼想到一个性质：最好就是把每个点涵盖到根到叶子节点的路径上，这样应该是最优的情况。所以，我们根尽量放最大的。另外，如果在一个非叶子节点放一个塔，把它移到叶子结点，只会使答案更优，不会更劣。所以，我们对于每一个非根节点，都可以从他的子树里面选出一个节点把它包含到这个节点到根的路径里面。

就比如对于点 $u$，他子树内有一个点 $k$，它的高度是 $h_k$。我们只需要让 $h_k \geq h_u$ 就可以，因为根节点的 $h$ 一定是最大的，已经满足了条件。所以我们贪心的从子树选最大 $h$ 来比较即可，这样可以最大化减少不满足条件的情况。

具体实现就是很简单的，对于每个节点，记录一下子树最大值，每次和这个节点判断一下谁更大。如果是子树内更大，那么已经包含就去了就不用管了；否则，就把那个节点加上还差的数量。不过这里不用去记录是哪一个节点，因为上传之后这个节点是否修改并不会答案造成影响。

最后处理根节点，我们直接找到最大和次大的两个节点，把它们都改成根的大小，这样根就包含在了一个从下到根，再向下的这么一个路径上。

然后就处理完了所有情况。注意一下代码细节即可。

## 代码

注意开 long long，虽然看上去可能不用。~~别问我怎么知道的~~。

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int MAXN=200005;
ll a[MAXN],b[MAXN],ans=0;
vector<int> E[MAXN];
void dfs(int u,int fa){
	ll mx1=0,mx2=0;
	for(int i=0;i<E[u].size();i++){
		int v=E[u][i];
		if(v==fa) continue;
		dfs(v,u);
		if(b[v]>mx1) mx2=mx1,mx1=b[v]; // 更新最大值、次大值 
		else if(b[v]>mx2) mx2=b[v];
	}
	b[u]=max(mx1,a[u]); // 数组记录方便上传最大值 
	if(a[u]>mx1) ans+=(a[u]-mx1); // 如果 a[u] 比子树内最大的还大，说明需要补 
	if(fa==-1 && a[u]>mx2) ans+=(a[u]-mx2); // 根节点时 fa=-1，这个时候需要用次大值更新答案 
}
int main(){
	int n,rt=0; cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>a[rt]) rt=i; // 找到 a[i] 最大的 i 作为根节点 
	}
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs(rt,-1);
	cout<<ans;
	return 0;
}
```

~~另：50 紫题祭，菜死了/kk。~~

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2500}$
---
### 解题思路：

考虑贪心。

首先发现，一定存在一种最优方案，使得所有选择的点都是叶子结点。假设有一个点不是叶子结点而被选中建筑了一个信号塔，将这个信号塔移动到一个叶子结点上一定不会更劣。

如果一个节点的子树以外存在一个节点比这个节点的要求更高，则一定可以用那个节点所用到的一个叶子结点和这个节点子树中的某一个叶子结点进行覆盖。此时就能想到将要求最大的一个节点作为根节点，这样每一个非根节点都一定会在子树中找一个节点，而子树外也一定有至少一个节点可以选择。

更具体地，对于任意一个非根节点，找出子树中最大的信号塔，将这个信号塔补至当前要求，如果已经达到要求，不作处理。对于根节点，考虑最大的和次大的信号塔进行补足。

数据范围较大，需要用 $\text{long long}$ 进行存储。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int MAXN=400005;
int n,h[MAXN],head[MAXN],nxt[MAXN],num[MAXN],tot,x,y,maxn,maxi,ans;
void add(int x,int y){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
}
int dfs(int now,int fa){
	int fi=0,sc=0;
	for(int i=head[now];i;i=nxt[i]){
		if(num[i]==fa)continue;
		int p=dfs(num[i],now);
		if(p>fi){sc=fi;fi=p;}
		else if(p>sc)sc=p;
	}
	if(fa==0)ans+=max(0ll,h[now]-fi)+max(0ll,h[now]-sc);
	else ans+=max(0ll,h[now]-fi);
	return max(h[now],fi);
}
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++){
		scanf("%I64d",&h[i]);
		if(h[i]>maxn){
			maxn=h[i];
			maxi=i;
		}
	}
	for(int i=1;i<n;i++){
		scanf("%I64d%I64d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(maxi,0);
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：sprads (赞：0)

**题目传送门**：[CF1637F](https://codeforces.com/problemset/problem/1637/F)

### 前言

代码不难写，但要把性质抓准，想清楚，难（~~当然主要原因是我太菜了~~）。

先思考两个问题：

- 当所有点的 $h_i$ 都为 $1$ 时，怎么做？

- 假设这是一棵有根树，考虑一棵子树的根在 $v_1$ 到 $v_2$ 的路径上，两个点 $v_1$、$v_2$ 需要满足什么条件？

### 分析

**性质 $1$**：最优答案一定是在所有叶子（也就是度数为 $1$ 的节点）上花钱。

**口胡证明**：
- 考虑一个叶结点 $v$，除了将 $v$ 作为一个端点的路径，其他路径都不能覆盖 $v$ 这个点。所以所有叶结点必须花钱。

- 显然，每一个叶结点到其他叶结点构成的路径一定能将整棵树覆盖。所以在非叶节点花钱，一定可以被在叶结点花钱时替代，即仅对叶结点操作不会劣于对非叶结点操作。

**性质 $2$**：当我们确定了树的根，考虑覆盖一棵子树的根，至少有一个端点是它的子孙。（~~比较显然，不口胡证明了~~）

根据两个性质，就能有一个**重要的思路**：

1. 若 $h_k$ 最大，就将 $k$ 作为树根。

2. 其次确定每一个节点子树内的端点 $v$。

因为覆盖根的两个端点一定在两棵不同的子树内，所以对于任意一个子节点，都可以利用 $v$ 和覆盖 $k$ 的两个端点中的一个匹配，达到覆盖这个子节点的目的（简单来说就是白嫖根的端点）。

### 实现
**确定节点 $x$ 子树内的端点**：在 $x$ 的子树中贪心地选目前花钱最多的节点。如果花的钱小于 $h_x$，把费用补上；已经大于，则不管。

**确定根的两个端点**：贪心找子树中花钱最多和次多的节点，同上面类似处理。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
long long ans;
int n,h[N],rt,tot,head[N],ver[2*N],Next[2*N];
int rd(){
	int x = 0;char ch = getchar();
	while(ch < '0' || ch > '9')ch = getchar();
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x;
}
void add(int x,int y){
	tot++;
	ver[tot] = y;
	Next[tot] = head[x];
	head[x] = tot;
}
int dfs(int fa,int x){
	int Mx1 = 0,Mx2 = 0,Mxy;//Mx1 花钱最多多少，Mx2 花钱次多多少，Mxy 子树花钱最多多少
	for(int i = head[x];i;i = Next[i]){
		int y = ver[i];
		if(y == fa)continue;
		Mxy = dfs(x,y);
		if(Mxy > Mx1)
			Mx2 = Mx1,Mx1 = Mxy;
		else if(Mxy > Mx2)
			Mx2 = Mxy;
	}
	if(fa){//更新 and 交钱
		ans += max(0,h[x] - Mx1);
		Mx1 = max(Mx1,h[x]);
	}
	else{
		ans += h[x] - Mx1 + h[x] - Mx2;
		Mx1 = h[x];
	}
	return Mx1;
}
int main(){
	n = rd();
	for(int i = 1;i <= n;i++){
		h[i] = rd();
		if(!rt || h[i] > h[rt])
			rt = i;//选 h[i] 最大的为根
	}
	for(int i = 1;i < n;i++){
		int x = rd(),y = rd();
		add(x,y);
		add(y,x);
	}
	dfs(0,rt);
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Cat_shao (赞：0)

给定一棵 $n$ 个结点的树，第 $i$ 个点有一高度 $h_i$ 。你可以在任意一些结点上建信号塔，高度随意。结点 $i$ 有信号且当 $i$ 在 $u, v$ 的路径上， $u, v$ 分别有两座信号塔 $e_u, e_v$ ，满足 $\min(e_u, e_v) \ge h_i$ 。建高度为 $x$ 的信号塔花 $x$ 元，问最少得花多少钱使得所有结点都能有信号。

显然，将信号塔建在叶子结点最合算。记 $h_x$ 为所有结点中高度最高的。不妨将 $x$ 设为树根，然后在两个不同的子树中找两个叶结点 $u, v$ ，造两个高度为 $h_x$ 的信号塔。

假定我们先不管根结点怎么算，考虑除了根结点之外的结点怎么算。从树根开始 dfs ，到了结点 $i$ ，先 dfs $i$ 的子树，求出子树之中高度最高的信号塔，高度为 $mx$ 。

这个信号塔只是让一个局部有了信号。也就是说树根的子树中有一座位置不同于这个信号塔的信号塔，“不同于这个信号塔的信号塔”用于给树根信号，用于给树根信号的信号塔高度一定不低于 $h_i$ 。如果 $h_i \le mx$ 则不需要在 $h_i$ 上建信号塔，结点 $i$ 就有信号。否则将这个局部信号塔高度增加 $h_i - mx$ ，这样结点 $i$ 就有了信号。

根结点先 dfs 子树，然后知道了不同子树中的已经建好的最高信号塔。选出最高和次高的信号塔，将它们加高到 $h_{\text{根结点}}$ ，根结点也有了信号。

```cpp
//
// Created by Cat-shao on 2022/2/12.
//

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;

vector<int> graph[MAX_N];
int h[MAX_N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, x, y;
    cin >> n;
    for_each(h + 1, h + n + 1, [](int &x){ cin >> x; });
    for (int i = 1; i <= n - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int rt = max_element(h + 1, h + n + 1) - h;
    long long ans = 0;
    function<int(int, int)> dfs = [&](int cur, int par) {
        int mx1 = 0, mx2 = 0;
        for (const auto e : graph[cur]) {
            if (e != par) {
                int temp = dfs(e, cur);
                if (temp > mx1) {
                    swap(mx1, temp);
                }
                if (temp > mx2) {
                    swap(mx2, temp);
                }
            }
        }
        if (par) {
            int delta = max(h[cur] - mx1, 0);
            ans += delta;
            mx1 += delta;
        } else {
            ans += 2 * h[cur] - mx1 - mx2;
        }
        return mx1;
    };
    dfs(rt, 0);
    cout << ans;
    return 0;
}
```

---

## 作者：lyxeason (赞：0)

下面的讲解默认看过题了。

------------
首先先确定根节点 $root$。根节点的子树中定然有两个不在同一个 $root$ 的儿子的子树里的点，$p$ 和 $q$ 使得它们的 $e$ 值要大于等于 $h_{root}$，并且取等时最优。所以根节点应为所有点中高度最高的点。否则如果另一个高度比它低的点是根节点，那么 $p$ 和 $q$ 的 $e$ 值就可能会被其它高度比根节点高的点所提高，不再取等，变得不优。

确定好根节点后就会比较好做一些。首先对于根节点，根据贪心的思想，选取的点 $p$ 和 $q$ 应该是不处于同一儿子的子树里 $e$ 值最大和次大的点，并将这两个点的 $e$ 值 提升到 $h_{root}$（如果原本小于 $h_{root}$ 的话）。因为这样可以就利用原本建塔的点，并选取两个 $e$ 值与 $h_{root}$ 最接近或超过它的点，尽可能最小化花费。

对于一个不是根节点的点 $y$，我们只需选择一个其子树中的点 $z$，使得 $e_z\geq h_y$。因为在这里可以令 $u=z,x=y,v=p$ 或 $q$，就一定可以满足条件。因为 $e_p,e_q\geq h_{root}$ 而 $h_{root}$ 是所有点中高度最高的点，一定大于等于 $h_y$。$z$ 的最优选择就是 $y$ 子树中 $e$ 值最大的点，原因和前面选 $p$ 和 $q$ 时同理。

注意一点，叶节点显然必须建 $e_i=h_i$ 的塔，这样就保证了每一个子树里不会没有建塔的点。在代码里可以直接和其它不是叶子节点的判断情况合并起来。

------------
### 代码
###### 代码里有注释
```cpp


#include <cstdio>
#include <cstring>
#define ll long long

using namespace std;

int N;
int H[200009];
int h[200009];
int nxt[400009];
int to[400009];
int idx;
ll res;

inline void Add (int a, int b) {
    nxt[idx] = h[a], to[idx] = b, h[a] = idx++;
}

void In () {
    int a;
    int b;

    memset(h, -1, sizeof(h));
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &H[i]);
    for (int i = 1; i < N; i++) scanf("%d%d", &a, &b), Add(a, b), Add(b, a);
}

inline ll Max (ll a, ll b) {
    return a > b ? a : b;
}

int Dfs (int x, int p) {
    int v;
    int t;
    int mx1 = 0; //最大值
    int mx2 = 0; //次大值

    for (int e = h[x]; ~e; e = nxt[e]) {
        v = to[e];
        if (v == p) continue;
        t = Dfs(v, x);
        if (t >= mx1) mx2 = mx1, mx1 = t;
        else if (t > mx2) mx2 = t;
    }
    if (p) res += Max(0, H[x] - mx1), mx1 = mx1 > H[x] ? mx1 : H[x];
    //如果不是根节点则只需选最大值，注意最后要更新 mx1（如果原本大于就不用再增加），因为再往上的节点也要用到它。
    //对于一个叶子节点，mx1=0。在这里就会直接把 mx1 提到 H[x]，同时更新答案
    else res += (Max(0, H[x] - mx1) + Max(0, H[x] - mx2));
    //根节点这里不需要更新 mx1。因为再往上就没有节点了
    return mx1;
}

void Solve () {
    int x = 0;

    for (int i = 1; i <= N; i++)
        if (H[x] < H[i]) x = i; //高度最高的点设为根节点
    Dfs(x, 0);
}

void Out () {
    printf("%lld\n", res);
}

int main () {

    In();
    Solve();
    Out();

    return 0;
}
```

---

## 作者：black_trees (赞：0)


[在这里体验更佳](https://hylwxqwq.github.io/post/cf1637-f/)

---

首先我们可以发现一个结论，如果假定了树的根节点，那么每一个叶子节点都必须放一个 tower。

然后又可以发现一个结论，在假定了根节点的情况下，如果节点 $u$ 是有信号的的，那么 $u$ 的子树当中必然有至少一个 tower，满足这个 tower 的 $e\ge h_u$ 。

上面的结论全部基于 “根节点假定” 的情况。

但是本题给出的明显是一颗无根树，所以我们很自然的想到了换根DP。

那么我们可以设 $f_u$ 表示以 $u$ 为根节点的时候，使每一个节点都变成有信号的节点的最小花费。

然后发现这个换根不是很好写。

又发现，如果让 $h$ 最大的那一个（或者其中的一个）作为根节点，那么往下取值一定是最优的。

因为你现在要做的就是让每个子树当中都有一个 $e$ 大于等于这个子树的根的 $h$ 的 tower。

然后对于根节点，只需要让它的两个互不相同的子树当中有两个 tower 的 $e=h_{root}$ 即可。 

如果说这个 $h$ 最大的点不是 $root$ ，那么它就会在某个子树里面，就会导致子树里需要多放几个 $e=h_{max}$ 的 tower，明显不是最优的。

所以我们就直接令这个 $h$ 最大的点为 $root$ ，然后递归下去处理就行了。

```cpp
/*
 * @Author: black_trees <black_trees@foxmail.com>
 * @Date: 2022-02-13 09:32:23
 * @Last Modified by: black_trees <black_trees@foxmail.com>
 * @Last Modified time: 2022-02-13 10:21:40
 */

/*
 * READ THIS BEFORE YOU WRITE YOUR CODE
 * ====================================
 * @ Read the description carefully!
 * @ Pay attention to the data domain.
 * @ Keep calm.
 * @ Write down your thought on your draft.
 * @ Keep your mind clear.
 * @ Stabilize the coding speed.
 * ====================================
 * READ THIS AGAIN BEFORE YOU START !!!
 */

#include<bits/stdc++.h>
using namespace std;

#define int long long
constexpr int inf=1e18+1,si=2e5+10;
int n,height[si],res;
struct Edge{
	int head,ver,Next;
}e[si<<1]; int tot=0,root=0,rt[si];
inline void add(int u,int v){ e[++tot].ver=v,e[tot].Next=e[u].head,e[u].head=tot; }
inline pair<int,int> dfs(int u,int fa){
	int max1,max2; max1=max2=0;
	for(register int i=e[u].head;i;i=e[i].Next){
		int v=e[i].ver; if(v==fa) continue;
		int now=dfs(v,u).first; if(now>max1) max2=max(max2,max1),max1=now; else max2=max(max2,now);
	} if(fa!=0) res+=max(height[u]-max1,0ll),max1+=max(height[u]-max1,0ll);
	else res+=max(height[u]-max1,0ll)+max(height[u]-max2,0ll); return make_pair(max1,max2);
}
signed main(){
	scanf("%lld",&n); for(register int i=1;i<=n;++i) scanf("%lld",&height[i]);
	for(register int i=1,u,v;i<n;++i) scanf("%lld%lld",&u,&v),add(u,v),add(v,u);
	for(register int i=1;i<=n;++i) root=height[i]>height[root]?i:root; dfs(root,0); return printf("%lld\n",res),0; // 
}

```





---

## 作者：pzc2004 (赞：0)

# Solution
观察数据范围，我们可以猜测这题的解法是贪心。  
题目要求的即对于每个点 $x$，都有一条穿过它的路径 $(u,v)$ 满足 $u!=v$ 且 $u,v$ 上的塔大于 $h_x$。那么我们可以发现如果 $u,v$ 不是叶子节点，则我们将 $u,v$ 都分别移动到叶子节点必然不劣，这样我们就得出了第一个结论：每个塔必然是放在叶子节点。  
接着我们将根节点设为点权最大的点，并按照点权从大到小考虑每个点，可以发现除了第一个点要放两座塔，其他每个点都最多只需再放一座塔即可，并且每座塔都可以将塔所在的节点到根节点这一条链上的还未删除的点删除。这样我们的任务就转化为了每次找一个根节点放塔。  
显然我们可以在当前节点每次选择进入子树中最大点权最大的儿子节点，一直走到根即可，证明也很简单，考虑反证法，则发现交换后必然更优。  
每次选完根节点后，直接一路向上删点  即可。  
复杂度 $O(N\log_2N)$，瓶颈在于排序。
# Code
``` cpp
#include <bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x= 0;
	char c= getchar();
	while(!isdigit(c)) c= getchar();
	while(isdigit(c)) x= x * 10 + (c & 15), c= getchar();
}
#define N 2000001
int n, m, a[N], b[N], head[N], cnt, c[N], d[N], ma[N], son[N], fa[N];
bool vis[N];
long long ans;
struct Edge {
	int a, b;
} e[N << 1];
inline void add(int a, int b) {
	e[++cnt].a= head[a], e[cnt].b= b, head[a]= cnt;
}
inline void dfs(int x, int y) {
	ma[x]= a[x], fa[x]= y;
	for(int i= head[x]; i; i= e[i].a) {
		if(e[i].b == y) continue;
		dfs(e[i].b, x), ma[x]= max(ma[x], ma[e[i].b]);
		if(ma[e[i].b] > ma[son[x]]) son[x]= e[i].b;
	}
}
int main() {
	read(n);
	for(int i= 1; i <= n; i++) read(a[i]), b[i]= a[i];
	sort(b + 1, b + n + 1), m= unique(b + 1, b + n + 1) - b - 1;
	for(int i= 1; i <= n; i++) a[i]= lower_bound(b + 1, b + m + 1, a[i]) - b;
	for(int i= 1, x, y; i < n; i++) read(x), read(y), add(x, y), add(y, x);
	for(int i= 1; i <= n; i++) c[i]= i;
	sort(c + 1, c + n + 1, [](const int &x, const int &y) -> bool { return a[x] > a[y]; });
	dfs(c[1], 0);
	ans= 2 * b[a[c[1]]];
	vis[c[1]]= 1;
	for(int i= son[c[1]]; i; i= son[i]) vis[i]= 1;
	int s= 0;
	for(int i= head[c[1]]; i; i= e[i].a) {
		if(e[i].b != son[c[1]] && ma[e[i].b] > ma[s]) s= e[i].b;
	}
	for(int i= s; i; i= son[i]) vis[i]= 1;
	for(int i= 2; i <= n; i++) {
		if(vis[c[i]]) continue;
		ans+= b[a[c[i]]];
		for(int x= son[c[i]]; x; x= son[x]) vis[x]= 1;
		for(int x= fa[c[i]]; !vis[x] && x; x= fa[x]) vis[x]= 1;
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

