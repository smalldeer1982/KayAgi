# [ARC032B] 道路工事

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc032/tasks/arc032_2

大工のチョーさん(Daiku Cho)の町では道路の建設が進んでいます。チョーさんの町には $ N $ 個の交差点と $ M $ 個の道路があり、道路は異なる2つの交差点を双方向に結んでいます。 不便なことに、ある交差点から別の交差点まで道路を使って行き来できるとは限りません。

チョーさんの建設会社は、異なる交差点を結ぶいくつかの道路を作って、$ N $ 個のどの交差点からも道路を使って他のどの交差点へも行けるようにしたいと思っています。

どの交差点からも道路を使って別のどの交差点にも行けるようにするには最小で何本の道路を建設する必要があるかを答えてください。ただし、すでにある道路でどの交差点からも別のどの交差点へ行けるとき、$ 0 $ を出力してください。

## 说明/提示

### Sample Explanation 1

交差点 $ 1 $、$ 2 $、$ 3 $ は互いに道路でつながっているが、交差点 $ 4 $ はつながっていない。例えば、交差点 $ 1 $ と $ 4 $ を結ぶ道路を作れば十分である。 !\[\](http://arc032.contest.atcoder.jp/img/arc/032/B1.png)

## 样例 #1

### 输入

```
4 2
1 2
1 3```

### 输出

```
1```

## 样例 #2

### 输入

```
6 4
1 2
2 3
1 3
5 6```

### 输出

```
2```

# 题解

## 作者：血色黄昏 (赞：2)

题目翻译简洁明了，点赞

假设我们有$n$个连通块，把它们缩成一个个点，如何将它们变成一个连通图？显然将一个点作为根，这个点朝其他所有点连一条边是最节省的。这只需要$n-1$，所以我们只要求出连通块个数然后将个数减一即可。

如何实现？

暴力怎么做？加边!加边!!加边!!!然后并查集查询！

代码简短，常数小，轻松跑过，$471B173ms$，注释都在代码里了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int fa[1000010], n, m, ans = 0;
int find(int x)//查询公共祖先，并路径压缩 
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void unions(int x, int y)//将两个数的祖先合并 
{
	fa[find(x)] = find(y);
}
int main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i ++)fa[i] = i;//将一开始自己祖先设为自己 
	for(int i = 1;i <= m;i ++)
	{
		int x, y;
		cin>>x>>y;//输入边 
		unions(x, y);//将两个节点合并为一个集合里的，即在同一连通块 
	}
	for(int i = 1;i <= n;i ++)ans += fa[i] == i;//如果祖先还是自己说明这是一个单独的连通块，答案加一 
	cout<<ans - 1<<endl;//输出连通块个数减一 
	return 0;
}
```

新年快乐w！

---

## 作者：_i_i_ (赞：1)

假设现在整张图中有 $n_0$ 个连通块。我们需要加边使得图中的连通块数量变为 $1$。

连边的时候如果连到了两个来自同一个连通块的点，则连通块总数不变。

否则，连通块数量减一。

根据贪心，我们每一次都应当连接两个来自不同连通块的点。

易得需要连 $n_0-1$ 条边。

那么如何得到整张图的连通块数量呢？

我们可以使用[并查集](https://www.luogu.com.cn/problem/P3367)，将原图中的边转换成并查集中的父子关系，这样就可以求出原图的联通块数量。

并查集建立结束后直接记录合并成功的次数，拿 $n$ 减去该值即可得到连通块个数。

时间复杂度 $O(n+m\alpha(m))$。

```cpp
#include <cstdio>
const int MAXN = 100005;
int fa[MAXN], sz[MAXN];
int findfa(int a) {
	return fa[a] == a ? a : fa[a] = findfa(fa[a]);
}
bool merge(int x, int y) {
	x = findfa(x); y = findfa(y);
	if (x == y) return 0;
	if (sz[x] > sz[y]) fa[y] = x, sz[x] += sz[y];
	else fa[x] = y, sz[y] += sz[x];
	return 1;
}
void clear(int n) {
	for (int i = 1; i <= n; i++) fa[i] = i;
}
int main() {
	int n, m; scanf("%d %d", &n, &m); int tot = 0; clear(n);
	while (m--) {int x, y; scanf("%d %d", &x, &y); tot += merge(x, y);}
	tot = n - tot; printf("%d\n", tot - 1);
	return 0;
}
```

---

## 作者：DeepSkyBlue__ (赞：1)

要求出至少加上几条边使原图连通，那么其实只要求出连通块的个数就行了。

要加的边的条数就是连通块的个数 $- 1$ 。

这里使用一种 BFS 求连通块的方法，一个点如果没有被访问过，那么就说明这个点属于一个新的连通块，然后对这个点进行 BFS 即可。

CODE：

```cpp
#include<bits/stdc++.h>
//#include<tr1/unordered_map> 
using namespace std;
//using namespace std::tr1;
unordered_map<int,vector<int> > adj;
queue<int>q;
bool v[200001];
void bfs(int s)//bfs
{
    q.push(s);
    v[s]=true;//源点入队
    while(!q.empty())//队列不为空
    {
        int cur=q.front();//队首元素进行扩展
        q.pop();
        for(int i=0;i<adj[cur].size();i++)
        {
            int next=adj[cur][i];
            if(!v[next])//没走过
            {
                v[next]=true;//那就走
                q.push(next);
            }
        }
    }
}
int main()
{
    int n,m,ans=0;
    scanf("%d %d",&n,&m);
    memset(v,0,sizeof(v));
    for(int i=1;i<=m;i++) 
    {
        int x,y;
        scanf("%d %d",&x,&y);
        adj[x].push_back(y);//无向图两次建边
        adj[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
    	if(!v[i])//这个点没有被访问过
    	{
    		ans++;//连通块个数增加
    		bfs(i);//对这个点进行bfs
		}
	printf("%d\n",ans-1);//连通块个数-1就是加边的条数，记得换行
    return 0;
}
```


---

## 作者：HMP_Haoge (赞：1)

估计难度是黄的或者橙的。

## 思路


  让我们求最少需要多少条边能让这个图联通，显然就是要找出连通块个数，把每一个连通块想象成一个点。此时图就变成了很多个孤立的点，显然当他们构成一棵树的时候边数最少。
  
  至于怎么求连通块，用并查集就很方便啊。~~不会有人用Tarjan吧~~
  

上码！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
#define MAXN 100100

bool vis[MAXN];
int fa[MAXN],n,m,ans1;

namespace I_AK_NOIP //膨胀一波 
{
	template< typename T >inline void read(T &x)
	{
		char c=getchar();
		int f=0;
		x=0;
		for(; !isdigit(c); c=getchar()) f|=(c=='-');
		for(; isdigit(c); c=getchar()) x=((x<<3)+(x<<1)+(c^48));
		x=(f?-x:x);
	}
	template< typename T >inline void write(T x)
	{
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar(x%10^48);
	}
};
using namespace I_AK_NOIP;

inline int Find(int x) //并查集板子 
{
	return fa[x]==x?x:fa[x]=Find(fa[x]);
}

int main()
{
	read(n);read(m);
	for(ri i=1;i<=n;++i) fa[i]=i;
	int u,v,fx,fy;
	for(ri i=1;i<=m;++i)
	{
		read(u);read(v);
		fx=Find(u);
		fy=Find(v);
		if(fx==fy) continue;
		fa[fx]=fy;           //合并操作 
	}
	for(ri i=1;i<=n;++i) 
	{
		int FA=Find(fa[i]);
		if(!vis[FA]) ++ans1,vis[FA]=1; //注意这里一定不能写 if(!vis[fa[i]])
	}
	write(ans1-1);
	putchar('\n'); //一定要换行！！ 
	return 0;
}
```


---

## 作者：Helloworld_Dk (赞：0)

# solution-at1146


## 题目翻译
给定 $n$ 个点，$m$ 条边，问至少添加多少条边之后使得原图连通？

## 题意解释
- 一张图，图不连通，有很多独立的连通块
- 求用多少边可以把整张图连通

## 处理方法
要将 $n$ 个点用最少的边连起来，最少需要 $n - 1$ 条边。问题转化为确定每几个点是否在一个连通块内（是否连通）。
如何确定？使用**并查集**。

这道题就这样解决了，在输入边后我们并查集连边。
所有输入结束后,并查集遍历点确定连通块的数量 $n$ 最后输出 $n - 1$ 即可。

## 代码

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;
#define maxn 1000005

int fa[maxn];
void initbcj(){
    for(int i=0;i<maxn;i++)
        fa[i]=i;
}
int findfa(int u){
    return fa[u]==u?u:fa[u]=findfa(fa[u]);
}
void merg(int u,int v){
    fa[findfa(v)]=findfa(u);
}
int main()
{
    initbcj();
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        merg(u,v);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(fa[i]==i) ans+=1;
    }
    printf("%d\n",ans-1);
    return 0;
}
```


---

## 作者：唐一文 (赞：0)

## 思路
因为要使加的边最少，所以只要求出构成了多少棵树（即联通块）  
所以只要从一棵树把另外的树全都连上一条边，这个图就连通了  
求树的数量只要用并查集就能求了  
答案就很显然了：树的数量$-1$
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
//以下为并查集模板
int fa[100005];
int find(int x){
	if(fa[x]!=x){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}
inline void unionn(int x,int y){
	x=find(x);
	y=find(y);
	if(x!=y){
		fa[y]=x;
	}
}
int n,m;//如题
int a,b;//如题
int sum;//树的数量
int i;
int main(){
	cin>>n>>m;//如题
	for(i=1;i<=n;i++){//并查集初始化
		fa[i]=i;
	}
	while(m--){//如题
		cin>>a>>b;
		unionn(a,b);//合并
	}
	for(i=1;i<=n;i++){
		if(fa[i]==i){//根为本身，即一棵树的根
			sum++;
		}
	}
	cout<<sum-1;//谁复制谁稻花香里说丰年
	return 0;
}
```


---

## 作者：飞雪连天 (赞：0)

~~又是一道简单的黑题~~

### 题目大意
给定N个点，M条边，问至少添加多少条边之后使得原图连通？ 
### 解题思路
当一个图联通的时候，它最少要有n-1条边。题目要求我们求出最少添加多少条边让原图连通，也就是求出一共有多少个不同的连通块，然后再-1就是需要加边的数量了。最后一定记得换行，不然会wa掉！QAQ
### 代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

int n,m,f[100008],ans;

long long read()
{
	long long x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int find(int x)
{
	return f[x]==x?f[x]:f[x]=find(f[x]);
}

int main()
{
	ans=n=read();m=read();
	for(int i=1;i<=n;++i) f[i]=i;//初始化并查集 
	for(int i=1;i<=m;++i)
	{
		int uu=find(read()),vv=find(read());
		if(!(uu^vv)) continue;//如果两个点已经连通了 
		f[uu]=vv;ans--;//否则让两个点连通，并使总连通块数量-1 
	}
	printf("%d\n",ans-1);//x个连通块需要x-1条边 
	return 0;
}

```


---

