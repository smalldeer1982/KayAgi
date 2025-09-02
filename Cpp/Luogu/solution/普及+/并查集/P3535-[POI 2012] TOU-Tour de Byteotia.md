# [POI 2012] TOU-Tour de Byteotia

## 题目描述

**译自 POI 2012 Stage 2. Day 0「[Tour de Byteotia](https://szkopul.edu.pl/problemset/problem/mormqC6WwjeIiBpSNMhVbHni/site/?key=statement)」**

给定一个 $n$ 个点 $m$ 条边的无向图，问最少删掉多少条边能使得编号小于等于 $k$ 的点都不在任何一条简单环上。

## 说明/提示

样例配图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/gs7p4m5e.png)

对于 $40\%$ 的数据有 $n \le 1000,m \le 5000$.

对于所有数据有 $1 \le n \le 1\ 000\ 000,0 \le m \le 2\ 000\ 000,1 \le k \le n, 1 \le u \lt v \le n$.

翻译来自于 [LibreOJ](https://loj.ac/p/2693)。

## 样例 #1

### 输入

```
11 13 5
1 2
1 3
1 5
3 5
2 8
4 11
7 11
6 10
6 9
2 3
8 9
5 9
9 10```

### 输出

```
3
2 3
5 9
3 5```

# 题解

## 作者：Dream_poetry (赞：10)

### 思路：

首先，由于我们只需要保证编号小于等于 $k$ 的点不在简单环上，这就意味着两个编号大于 $k$ 的点之间的连边是没有必要删除的，因为假如有一个编号小于等于 $k$ 的点在一个简单环上，我们肯定可以通过删除一条与这个点相连的边使得这个环消失，所以我们直接删除一条与这个编号小于等于 $k$ 的点相连的边使得它脱离这个环显然是不劣的。

所以，必然有一组最优解保留了所有大于 $k$ 的点相互之间的连边。因此我们直接保留这些边即可。

然后将这些边所连的点通过并查集归在一起，方便后续判环。

然后枚举每一条边，如果这条边所连的两个点有一个的编号小于等于 $k$，那么我们就考虑保留这条边是否会产生环，否则直接跳过即可。

如果保留这条边会产生环，那我们必然舍弃，计入答案即可。

那如果保留这条边不会产生环，我们是否要保留呢？

其实此时问题可以转化为 $k$ 个独立点和若干个连通块，每个独立点和每个连通块之间最多只能连一条边。

那么显然我们肯定是要能连尽量连，这样才能保证删除的边最少。

当上述情况发生时，其实就相当于一个独立点和一个连通块第一次尝试连边，那么由于我们无法保证后续是否会出现新的边来把这两部分连起来，为保证最优性，我们肯定是要保留这条边的。

至此，思路显然了，代码也就简单了，利用并查集判环即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int k;

struct node{
	int x,y;
};
node e[2000005];
node ans[2000005];

int fa[1000005];
int cnt;


inline int find(int x){
	if (fa[x]!=x){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}


signed main(){
	ios::sync_with_stdio(0);
	
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m;
	for (int i=1;i<=n;i++){
	    fa[i]=i;
	}
	cin>>k;
	for (int i=1;i<=m;i++){
		cin>>e[i].x>>e[i].y;
		if (e[i].x>k && e[i].y>k){
			fa[find(e[i].x)]=find(e[i].y);
		}
	}
	for (int i=1;i<=m;i++){
		int u=find(e[i].x);
		int v=find(e[i].y);
		if (e[i].x<=k || e[i].y<=k){
			if (u==v){
				cnt++;
				ans[cnt]=e[i];
			}
			else{
			    fa[u]=v;
			}
		}
	}
	cout<<cnt<<"\n";
	for (int i=1;i<=cnt;i++){
		if (ans[i].x<ans[i].y){
			cout<<ans[i].x<<' '<<ans[i].y<<"\n";
		}
		else{
			cout<<ans[i].y<<' '<<ans[i].x<<"\n";
		}
	}
	return 0;
} 
```

---

## 作者：yl_ykf (赞：2)

# 思路：

~~首先，本蒟蒻雀食很蒻~~。

首先，因为我们只需要保证编号 $\le k$ 的点不在**简单环**上（简单环：又称**简单回路**，图的顶点序列中，除了第一个顶点和最后一个顶点相同外，其余顶点不重复出现的回路叫简单回路。或者说，若通路或回路不重复地包含相同的边，则它是简单的）。

也就是两个编号 $>k$ 的点之间的连边是没有必要删除的，因为假如有一个编号 $\le k$ 的点在一个简单环上，我们肯定可以通过删除一条与这个点相连的边使得这个环消失，所以我们直接删除一条与这个编号 $\le k$ 的点相连的边使得它脱离这个环显然是不劣的。因此我们直接保留所有 $>k$ 的点相互之间的连边即可。

然后将这些边所连的点通过并查集归在一起，否则后续难度将会**飙升**。

然后枚举每一条边，如果这条边所连的两个点有一个的编号 $>k$，直接跳过即可。

如果这条边所连的两个点有一个的编号 $\le k$，那么我们就考虑保留这条边是否会产生环。如果保留这条边会产生环，那我们必然**舍弃**，计入答案即可；那如果保留这条边不会产生环，我们也是需要**保留**的，因为我们肯定是要能连尽量连，这样才能保证删除的边最少。

其实此时问题可以转化为 $k$ 个独立点和若干个连通块，每个独立点和每个连通块之间最多只能连一条边。

当上述情况发生时，其实就相当于一个独立点和一个连通块第一次尝试连边，但是因为我们无法保证后续是否会出现新的边来把这两部分连起来，为保证最优性，我们肯定是要保留这条边的。

# code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 2000005
int n,m,k,fa[N],cnt;
struct node {
	int x,y;
}e[N],ans[N];
int find(int x) {//并查集找根 
	if (fa[x]!=x) {
		fa[x]=find(fa[x]);
	}
	return fa[x];
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//以上为快读模板
	cin>>n>>m;
	for (int i=1; i<=n; i++)fa[i]=i;//把每一个点设为自己的根，方便并集
	cin>>k;
	for (int i=1; i<=m; i++) {
		cin>>e[i].x>>e[i].y;
		if (e[i].x>k && e[i].y>k) fa[find(e[i].x)]=find(e[i].y);
	}
	for (int i=1; i<=m; i++) { 
		int u=find(e[i].x);
		int v=find(e[i].y);
		if (e[i].x<=k || e[i].y<=k) {
			if (u==v) {
				cnt++;
				ans[cnt]=e[i];
			} else fa[u]=v;
		}
	}
	cout<<cnt<<"\n";
	for (int i=1; i<=cnt; i++) {
		if (ans[i].x<ans[i].y) {
			cout<<ans[i].x<<' '<<ans[i].y<<"\n";
		} else {
			cout<<ans[i].y<<' '<<ans[i].x<<"\n";
		}
	}
	return 0;
}
```

[《跑的可快了》](https://www.luogu.com.cn/record/193871115)

本文借鉴于 @Dream_poetry 大佬的题解，其中结合了本人一些思想，大家可以交叉着看。

---

## 作者：Like_Amao (赞：1)

**前言**

[题目传送门](https://www.luogu.com.cn/problem/P3535)

**前置知识**

[并查集](https://oi-wiki.org/ds/dsu/)

**思路**

我们要确保编号 $\le k$ 的点不在简单环的上面，这就代表着两个编号 $> k$ 的点之间的连边是不需要删除的，因为假如存在一个编号 $\le k$ 的点在一个简单环之上，我们一定可以通过删除一条与这个点相连的边使得这个环消失，所以我们直接删除一个编号 $\le k$ 的点相连的边使得它脱离这个环很显然是不劣的，因此我们直接保留所有 $\ge k$ 的点相互之间的连边即可，然后将这些边所连的点用并查集归在一起，然后枚举每一条边，如果这条边所连的两个点有一个的编号 $> k$，直接跳过即可，如果这条边所连的两个点有一个点的编号 $\le k$，我们就需要思考保留这么一条边是否会产生环形，如果会产生环形，那么我们肯定要抛弃这一条边，反之，我们就可以保留这一条边。

**代码**


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int x;
	int y;
};
node a[2000001],anss[2000001];
int father[2000001];
int find(int);
signed main()
{
	int n,m,k,ans=0;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		father[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].y;
		if(a[i].x>k && a[i].y>k)
		{
			father[find(a[i].x)]=find(a[i].y);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(a[i].x<=k or a[i].y<=k)
		{
			int son1=find(a[i].x);
			int son2=find(a[i].y);
			if(son1==son2)
			{
				anss[++ans]=a[i];
			}
			else
			{
				father[son1]=son2;
			}
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)
	{
		if(anss[i].x<anss[i].y)
		{
			cout<<anss[i].x<<" "<<anss[i].y<<endl;
		}
		else
		{
			cout<<anss[i].y<<" "<<anss[i].x<<endl;
		}
	}
	return 0;
}
int find(int x)
{
	if(father[x]!=x)
	{
		father[x]=find(father[x]);
	}
	return father[x];
}
```

[AC记录](https://www.luogu.com.cn/record/200681381)

---

## 作者：SnowTrace (赞：1)

先考虑如果你钦定了两端端点编号都 $>k$ 的边哪些被删哪些没被删，设没被删的边集是 $S$。

题目的限制也就是说剩下的边都不能在一个环里，这个事情等价于你先把 $S$ 里面的边放进去，然后对有一个端点 $<k$ 的所有边尝试求一个最大生成森林（这里森林的定义不严格，实际上是指连上 $S$ 以后的连通块在连边的时候形成森林结构，原本的连通块可能不是森林）。因为最大生成森林没有环而且还最大。

我们声称**所有两端端点编号都 $>k$ 的边都会被选。**

考虑上述过程，如果删掉一条两端都 $>k$ 的边，保留的边数会先减少 $1$，而此时保留 $S$ 后图的连通性可能改变，最多多出来一个连通块，那么根据求生成树的过程，多出来一个连通块，答案至多增加 $1$，所以只要删掉一条两端都 $>k$ 的边就会不优，或者可以理解成这个生成森林是优先选择端点 $>k$ 的点，那么这个删除操作相当于强制前面有条边不选，这对生成森林是不优的。

我们先从没有限制的地方入手，然后发现剩下来的有限制的部分是一个经典问题，再从经典问题解决方法的性质反推出没有限制的地方的决策。

---

## 作者：liuzhengtao (赞：0)

## 解题思路
首先分三步走，这三步每一步都很短。
### 第一步
先明确一点，由于我们仅需要保证编号小于等于 $k$ 的点并不在某个简单环上，所以说两个编号大于 $k$ 的点之间的连边是没有必要删除的。因为如果有一个编号小于等于 $k$ 的点在一个简单环上，我们肯定可以通过删除一条与这个点相连的边使得这个环消失，所以如果我们想要把这个简单环断开，我们直接删除一条与这个编号小于等于 $k$ 的点相连的边使得它脱离这个环显然不会更劣。

先说明一下，这道题我采用的方式是用结构体存储每一条边，下面的 $x$ 和 $y$ 分别表示该边所连的两个点

```cpp
struct node
{
	int x,y;
}e[N<<1],ans[N<<1];
```
第一个数组存边，第二个数组存的是答案要输出的边。

接下来显而易见，必有一组最优解保留了所有大于 $k$ 的点相互之间的连边。因此我们最开始直接保留这些边即可。

然后将这些被保留的边所连的点通过并查集归在一起。由于这些边所连的点的编号都大于 $k$，所以我们这样合并不会错。

先展示一下这部分的代码：

```cpp
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].x>>e[i].y;
		if(e[i].x>k&&e[i].y>k)
		{
			fa[find(e[i].x)]=find(e[i].y);
		}
	}
```
### 第二步
然后枚举每一条边，如果这条边所连的两个点有一个的编号小于等于 $k$，也就是说这个点在目前所连的图中是被晾在一边的一个独立点，那么我们就考虑如果保留这条边是否会产生环，如果会那么把答案加上这条边，否则就把这条边加上，用并查集合并。

先等一下，刚刚一定有人会问如果保留这条边不会产生环，我们为什么可以直接保留这条边而不是不保留呢呢？这个问题待会儿说。

我们先看这一部分的代码：

```cpp
	for(int i=1;i<=m;i++)
	{
		int p1=find(e[i].x);
		int p2=find(e[i].y);
		if(e[i].x<=k||e[i].y<=k)
		{
			if(p1==p2) ans[++cnt]=e[i]; 
			else fa[p1]=p2;
		}
	}
```

好，现在解释一下刚才的问题：

如果保留这条边不会产生环，我们是否要保留？

其实这个问题可以转化为目前已知若干个独立点和若干个连通块。易证得每个独立点和每个连通块之间最多只能连一条边，这句话大家先理解一下。刚刚说的独立点就是这些编号小于等于 $k$ 的点，连通块就是已经保留完边并用并查集合并在一起的点所连成的联通块。

因为每个独立点最多向外连一条边，那么我们肯定是要把能连的边尽量连上，这样才能保证删除的边最少。

当发生上面的情况时，其实就相当于一个独立点和一个连通块第一次尝试连边，由于我们无法保证后续是否会出现新的边来把这两部分连起来，为保证答案最优，我们肯定是要保留这条边的。
### 第三步
额其实就是把答案输出。

直接上代码。

```cpp
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
	{
		if(ans[i].x>ans[i].y) swap(ans[i].x,ans[i].y);
		cout<<ans[i].x<<" "<<ans[i].y<<endl;
	}
```
## 完整版代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,m,k,fa[N],op,p1,p2,cnt;
struct node
{
	int x,y;
}e[N<<1],ans[N<<1];
inline int find(int k)
{
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i;
	cin>>k;
	for(int i=1;i<=m;i++)
	{
		cin>>e[i].x>>e[i].y;
		if(e[i].x>k&&e[i].y>k)
		{
			fa[find(e[i].x)]=find(e[i].y);
		}
	}
	for(int i=1;i<=m;i++)
	{
		int p1=find(e[i].x);
		int p2=find(e[i].y);
		if(e[i].x<=k||e[i].y<=k)
		{
			if(p1==p2) ans[++cnt]=e[i]; 
			else fa[p1]=p2;
		}
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
	{
		if(ans[i].x>ans[i].y) swap(ans[i].x,ans[i].y);
		cout<<ans[i].x<<" "<<ans[i].y<<endl;
	}
	return 0;
}
```

---

