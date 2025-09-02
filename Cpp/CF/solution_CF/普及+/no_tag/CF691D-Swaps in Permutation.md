# Swaps in Permutation

## 题目描述

You are given a permutation of the numbers $ 1,2,...,n $ and $ m $ pairs of positions $ (a_{j},b_{j}) $ .

At each step you can choose a pair from the given positions and swap the numbers in that positions. What is the lexicographically maximal permutation one can get?

Let $ p $ and $ q $ be two permutations of the numbers $ 1,2,...,n $ . $ p $ is lexicographically smaller than the $ q $ if a number $ 1<=i<=n $ exists, so $ p_{k}=q_{k} $ for $ 1<=k&lt;i $ and $ p_{i}&lt;q_{i} $ .

## 样例 #1

### 输入

```
9 6
1 2 3 4 5 6 7 8 9
1 4
4 7
2 5
5 8
3 6
6 9
```

### 输出

```
7 8 9 4 5 6 1 2 3
```

# 题解

## 作者：Yizhixiaoyun (赞：9)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17050690.html)

[题目传送门](https://www.luogu.com.cn/problem/CF691D)

## 题目分析

随机跳到的一道很有意思的题。

显然在这 $m$ 对交换中，我们可以将它们划为多个集合，其中所有的数都是可以互相交换的。

那么如何去划分这些集合？没错，并查集。把可以互换的数当成点并连边，接着就可以并查集找连通块。

已经满足了一个条件，接着我们去找连通块中字典序最大的排列。显然在集合中再进行一次由大到小的排序就可以了。对于这一步，所有并查集题解似乎都不约而同用了滚动数组，但是使用优先队列会更加简单，不需要自己进行额外的排序。

## 贴上代码

```cpp
#include<bits/stdc++.h>
// #define int long long
#define debug puts("Shiina_Mashiro_kawaii")
#define ok puts("Yes")
#define no puts("No")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=1e6+5;
int n,m;
int a[maxn];
int f[maxn];
priority_queue<int> q[maxn];
// int cnt_edge,head[maxn];
// struct edge{
	// int to,nxt;
// }e[maxn<<1];
// void add(int u,int v){
	// e[++cnt_edge].nxt=head[u];
	// e[cnt_edge].to=v;
	// head[u]=cnt_edge;
// }
int find(int x){
	if(x!=f[x]) f[x]=find(f[x]);
	return f[x];
}
void unity(int x,int y){f[find(x)]=find(y);}
inline void init(){
	n=read();m=read();
	for(register int i=1;i<=n;++i) f[i]=i;
	for(register int i=1;i<=n;++i) a[i]=read();
	while(m--){
		int u=read(),v=read();
		unity(u,v);
	}
}
int main(){
	init();
	for(register int i=1;i<=n;++i) q[find(i)].push(a[i]);
	for(register int i=1;i<=n;++i){
		int fi=find(i);
		printf("%d ",q[fi].top());q[fi].pop();
	}
}
```

---

## 作者：世末OIer (赞：3)

题目大意:

有n个整数的数列，由数字[1, n]构成，同时还有m对交换(ai, bi)，表示交换位置ai和位置bi上的值，这些交换可以使用0到多次。

现在希望通过这些交换，获得最大的排列（字典序最大），问最大排列是什么？

题解:

并查集。

对于每一次更新，都将x的祖宗指向y的祖宗。

对于每一个祖宗(越靠前的越老)，将它的所有儿孙都压进去，然后排序。

最后输出:从1至n，输出它的祖宗的目前可以用的最后一个值。

```cpp
using namespace std;
int a[1000006],n,m,fa[1000006],sz[1000006];
vector<int> v[1000006];
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
	int i,j,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i) scanf("%d",a+i),fa[i]=i;
	for(i=1;i<=m;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		fa[find(x)]=find(y);
	}
	for(i=1;i<=n;++i) v[find(i)].push_back(a[i]);
	for(i=1;i<=n;++i) sort(v[i].begin(),v[i].end()),sz[i]=v[i].size();
	for(i=1;i<=n;++i) printf("%d ",v[find(i)][--sz[find(i)]]);
}
```

---

## 作者：E1_de5truct0r (赞：1)

## 思路

首先我们得到一个性质：如果存在 $(w,x)$，$(x,y)$，$(y,z)$ 等多个二元组，那么它的形象含义就是 $w,x,y,z$ 可以任意互换位置。

因此我们的最优策略就是把可以任意互换位置的数都从大到小放。这个做法很简单，直接每次对于 $(x,y)$ 连边，暴力 dfs 找到所有的连通块，然后把每一个连通块用 `vector` 存储下来进行排序。令 $s_i$ 为第 $i$ 个连通块的元素数量，显然有 $\sum s_i=n$，那么排序的复杂度 $\sum (s_i \log s_i) = n \log n$。

对于输出，我们可以记录第 $i$ 个点属于哪一个连通块，直接输出这个连通块第一个还没输出的数即可，即输出最大的数。这个可以记录一下下标，每次输出之后下标加一就可以实现。

时间复杂度 $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> E[1000005],L[1000005];
int tot,a[1000005],bel[1000005],now[1000005];
bool vis[1000005];
void dfs(int u,int fa)
{
	L[tot].push_back(a[u]); // 第 tot 个连通块中包含了 a[u] 这个数
	vis[u]=1; bel[u]=tot; // 记录 vis，以及 u 所处连通块的编号。
	for(int i=0;i<E[u].size();i++)
	{
		int v=E[u][i];
		if(vis[v]) continue;
		dfs(v,u);
	}
}
int main()
{
	int n,m; scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)
	{
		int x,y; scanf("%d%d",&x,&y);
		E[x].push_back(y);
		E[y].push_back(x);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			tot++; dfs(i,0);
			sort(L[tot].begin(),L[tot].end(),greater<int>()); // 进行排序
		}
	for(int i=1;i<=n;i++) printf("%d ",L[bel[i]][now[bel[i]]++]);
	// 输出第 i 个所处的连通块的第一个没输出的数，now[i] 记录第 i 个连通块第一个没输出的位置，每次输出之后就++。
	return 0;
}
```

---

## 作者：尹昱钦 (赞：1)

题解中都是并查集做法，这里补一发图的连通性做法。

## 解题思路

首先注意一个很重要的条件：
> 这些交换可以使用0到多次。

这告诉我们什么呢？

也就是说，我们把可以互换的点之间建边，在形成的图上的每个连通块内的点可以**随意交换**。

于是，我们建完图以后在每个连通块内从大到小排列出结果即可。

### 优点

想起来比较省事，写起来用不到什么算法，一般不会出错。
### 缺点

码量比并查集~~稍微~~多一点点。

## AC代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=1000005;
int n,m,cnt,p[maxn],vis[maxn],a[maxn],ans[maxn];
struct node{
	int v,next;
}e[maxn*2];
void insert(int u,int v){
	cnt++;
	e[cnt].v=v;
	e[cnt].next=p[u];
	p[u]=cnt;
}
priority_queue<int> q;
priority_queue<int,vector<int>,greater<int> >  qid;
void dfs(int u,int fa){
	vis[u]=1;
	for(int i=p[u];i!=-1;i=e[i].next){
		int v=e[i].v;
		if(v==fa||vis[v]) continue;
		q.push(a[v]);
		qid.push(v);
		dfs(v,u);
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	memset(p,-1,sizeof(p));
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		insert(u,v);
		insert(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			q.push(a[i]);
			qid.push(i);
			dfs(i,-1);
			while(!q.empty()){
				ans[qid.top()]=q.top();
				q.pop();
				qid.pop();
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：wkjwkj (赞：1)

[可能更好的阅读体验](https://mywkj.github.io/2020/04/05/cf691d-ti-jie/)


[原题链接](http://codeforces.com/problemset/problem/691/D)

这是一道并查集的题目，从题目的条件中应该还是比较容易看出的。下面我们来分析一下具体实现方法。

- 首先我们可以通过题目中的条件发现，在这 $ m$  对交换下，我们可以构造出 $ p $ 个集合，每个集合内的数字的顺序都是可以任意交换的，同时注意到题目中要求最大的排列，那么我们就应该把大的数放在前面。一个策略就慢慢成型了，我们可以先通过**并查集**将原数列划分为若干个集合，同时在每个集合内，**我们再将数字由大到小排列，再按原下标从小到大的顺序，放回原数列中，即可得到最后的答案**。

- 同时再介绍一个 $ STL $ 函数 $vector$ ,它能很好的帮我们解决这道问题。基本用法如下:

  ```cpp
  vector<int> a;//定义一个vector数组
  a.push_back(x);//在a的末尾插入x元素
  a.pop_back();//删除a末尾的元素
  a.size();//返回vector内的元素个数
  a[i];//表示a[i]这个元素，用法同数组，但vector默认下标从0开始
  ```

  

  代码如下:

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int fa[1000005];
  int a[1000005];
  int get(int x)
  {
  	if(fa[x]==x)return x;//路径压缩
  	return fa[x]=get(fa[x]);
  }
  vector<int> h[1000005];//用于记录每个集合
  vector<int> p[1000005];//记录每个集合中数字在原序列的下标
  int ans[1000005];//答案
  bool b[1000005];//判重，防止同一个集合多次计算
  bool cmp(int x,int y)
  {
  	return x>y;
  }
  int main()
  {
  	memset(b,0,sizeof b); 
  	int n,m;
  	scanf("%d%d",&n,&m);
  	for(int i=1;i<=n;i++)
  	  scanf("%d",&a[i]);
  	for(int i=1;i<=n;i++)
  	  fa[i]=i;
  	for(int i=1;i<=m;i++)
  	{
  		int x,y;
  		scanf("%d%d",&x,&y);
  		x=get(x),y=get(y);
  		fa[x]=y;
  	}
  	for(int i=1;i<=n;i++)
  	{
  		int x=get(i);
  		h[x].push_back(a[i]);//记录到集合中,其中x为集合代表
  		p[x].push_back(i);
  	}
  	for(int i=1;i<=n;i++)
  	{
  		int x=get(i);
  		if(b[x])continue;
  		sort(h[x].begin(),h[x].end(),cmp);//将集合内数字由大到小排列
  		sort(p[x].begin(),p[x].end());//将集合内的数字下标有小到大排列
  		for(int i=1;i<=h[x].size();i++)ans[p[x][i-1]]=h[x][i-1];//记录答案
  		b[x]=1;
  	}
  	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
  }
  ```

  本蒟蒻写的题解也许语言中有很多欠缺，望大佬能够指出，万分感谢。

---

## 作者：orz_z (赞：0)

### 题目大意

有 $n$ 个整数的数列，由数字 $[1, n]$ 构成，同时还有 $m$ 对交换 $(a_i, b_i)$，表示交换位置 $a_i$ 和位置 $b_i$ 上的值，这些交换可以使用 $0$ 到多次。

现在希望通过这些交换，获得最大的排列（字典序最大），问最大排列是什么？



### 解题思路

寻找突破口。

将题目转成图上问题，便于理解。

首先注意一个很重要的条件：

> 这些交换可以使用 $0$ 到多次。

这告诉我们什么呢？

也就是说，我们把可以互换的点之间建边，在形成的图上的每个连通块内的点可以**随意交换**。

于是，我们建完图以后在每个连通块内从大到小排列，用并查集维护连通块即可。

### CODE

```cpp
#include <bits/stdc++.h>
using namespace std;

const int _ = 1000007;
int n, m;

int a[_], fa[_], siz[_];

vector<int> v[_];

inline int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

signed main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        fa[i] = i;
    }
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        fa[find(x)] = find(y);
    }
    for (int i = 1; i <= n; ++i)
        v[find(i)].push_back(a[i]);
    for (int i = 1; i <= n; ++i)
    {
        sort(v[i].begin(), v[i].end());
        siz[i] = v[i].size();
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", v[find(i)][--siz[find(i)]]);
    return 0;
}
```





---

