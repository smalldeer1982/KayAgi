# Roads not only in Berland

## 题目描述

给定一个有 $n$ 个顶点，$n-1$ 条边的无向图。  
每一次操作都能去掉一条边，并且重新在某两个顶点之间连一条新边。  
试求需要多少次操作，才能使得从任一顶点都能到达其他的所有顶点，并构造方案。

$2 \le n \le 1000$。

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 2
2 3
3 1
4 5
5 6
6 7
```

### 输出

```
1
3 1 3 7
```

# 题解

## 作者：灵茶山艾府 (赞：10)

不需要并查集，只需要 DFS 就够了，复杂度 $O(n)$。

方法很简单，除去对整个图进行 DFS 所产生的搜索树上的边，剩余的边均为要删除的边，这些边可以在 DFS 的过程中得到。

哪些边需要相连呢？不妨从每个连通分量中任取一个点，计作 $v1, v2,v3...$，然后将 $v1$ 与 $v2$ 相连，$v2$ 与 $v3$ 相连，……

由于图中有 $n-1$ 条边，这样操作最后会将原图变成一棵树。

AC 代码（Golang）：

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, v, w int
	Fscan(in, &n)
	g := make([][]int, n+1)
	for i := 1; i < n; i++ {
		Fscan(in, &v, &w)
		g[v] = append(g[v], w)
		g[w] = append(g[w], v)
	}

	type edge struct{ v, w int }
	deletes := []edge{}
	vis := make([]bool, n+1)
	var f func(v, fa int)
	f = func(v, fa int) {
		vis[v] = true
		for _, w := range g[v] {
			if !vis[w] {
				f(w, v)
			} else if w != fa && v < w {
				deletes = append(deletes, edge{v, w})
			}
		}
	}
	vs := []int{}
	for i := 1; i <= n; i++ {
		if !vis[i] {
			vs = append(vs, i)
			f(i, 0)
		}
	}

	Fprintln(out, len(deletes))
	for i, p := range deletes {
		Fprintln(out, p.v, p.w, vs[i], vs[i+1])
	}
}
```


---

## 作者：Maxwang (赞：6)

首先，分析一下题目：

这个题目需要我们做的是：

- 计算需要拆（连）多少边。

- 判断哪些边可以拆。

- 拆下来的边补到哪里。

### 并查集概述

介绍一下前置知识：**并查集**。

如果有不知道并查集是何物的萌新可以做一下这些题：

[P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)
和 [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)。

在这里我们还是简单介绍一下：

并查集是一种树型的数据结构，用于处理一些不相交集合的合并及查询问题。常常在使用中以森林来表示。——百度百科

看到这里，不要被众多的名词吓到了，其实简单来讲就是认亲和找祖先的过程。

举个栗子：
如图所示，这里构成了两大亲戚集团，分别是以 $1$ 为祖先的和以 $2$ 为祖先的。
![](https://cdn.luogu.com.cn/upload/image_hosting/ywv8m8kj.png)

假如有一天 $1$ 和 $2$ 成为了亲戚，就把 $2$ 的祖先定为 $1$，这样所有的人都有一个共同的祖先了。
![](https://cdn.luogu.com.cn/upload/image_hosting/e7ltrw98.png)

当然这里还有很多其他的用法比如路径压缩，但是亲测本题不用路径压缩也能 AC，所以不再赘述，请自行查阅相关资料。

附上我的并查集代码供大家思考和使用（马蜂很丑，请dalao见谅）：
```cpp
struct uni{//并查集 
	int bin [ MAXN ];
	uni(){//初始自己是自己的祖先
		for(int i = 0  ; i < MAXN ;i++)
		bin[i]=i;
	}
	int anc(int x)//找祖先 
	{
		if( bin[x] == x )return x;
		else return bin[x] = anc( bin[x] ); //路径压缩 
	} 
	void link( int x , int y )//认亲 
	{
		bin[ anc(x) ] = anc(y);
	}
}u;
```
***

### 主要思路


#### 1.计算需要拆（连）多少边

不难发现，并查集有一个非常好的性质，就是所有联通的部分都有一个共同的祖先，所以在这道题中我们可以通过并查集判断这个图被分成了多少部分，即有多少不同的祖先，假设有 $x$ 个祖先，那么每个部分只要连一条边就可以使其联通，所以只需连 $x-1$ 条边就可以使图完全联通，由此可以解决这个问题。

#### 2.判断哪些边可以拆

我们手玩一下样例：
样例 1 想象一下就好，
样例 2 如图所示。
![](https://cdn.luogu.com.cn/upload/image_hosting/1ql79vsn.png)

我们发现，以 $1$ 为祖先的那一部分连通块有 $3$ 个点和 $3$ 条边，必然有一条边是无用的，所以任意一条边是可拆的。

那么，如何判断一条边是否为无用的呢？

我们边输入边判断，如果输入的边两端的点已经在同一连通块内了（即祖先相同了），就不用连接了，把他加入待删目录（我的待删目录是用队列实现的，因为这样好理解），否则正常建图。

#### 3.拆下来的边补到哪里

因为我们使用并查集，所以可以很容易的找到不同的祖先数（可以使用 STL 的 set 去重，最后 set 的大小就是连通块的数量），我们随意取出某个祖先，并把其余 $x-1$ 个祖先和这个祖先相连，这个图就是联通的了。

#### 4.具体细节和实现

大家可能会想到，我们拆边和连边的时候不会有不同的解法吗？
这就是翻译的锅了，原题上写的明明白白：

If the answer is not unique, output any.

如果答案不唯一，则输出任何答案。

希望大家不要进坑，~~我就是进坑的那个~~。

#### 5.完整代码

代码注释有很多细节呢，希望能认真食用呢。
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>
using namespace std;
const int MAXN = 1e3 + 19;
struct edge{
	int u,v;
};
vector<int>G[MAXN];//存图 

queue<edge>del;//待删目录 

set<int>fa;//祖先集合 

struct uni{//并查集 
	int bin [ MAXN ];
	uni(){//初始自己是自己的祖先 
		for(int i = 0  ; i < MAXN ;i++)
		bin[i]=i;
	}
	int anc(int x)//找祖先 
	{
		if( bin[x] == x )return x;
		else return bin[x] = anc( bin[x] ); //路径压缩 
	} 
	void link( int x , int y )//认亲 
	{
		bin[ anc(x) ] = anc(y);
	}
}u;
int n;
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i < n ; i++)
	{
		int x,y;
		scanf( "%d%d" ,&x ,&y);
		
		if(u.anc(x) == u.anc(y))//如果已经在同一连通块了 
		del.push( (edge) {x,y} );//加入待删目录 
		
		else//否则 
		u.link( x , y );//正常建图 
	}
	
	for(int i = 1 ; i <= n ; i++)
	{
		int x = u.anc(i);//找各个点的祖先 
		fa.insert(x);//加入集合（去重） 
	}
		
	cout << fa.size()-1 << endl;//集合的大小-1就是需要连的边数 
	
	if(fa.size()!=1)//如果未完全联通 
	{
		set<int>::iterator it=fa.begin();//取第一个祖先 
		int root = *it;
		
		fa.erase(root);//删掉所取的祖先 
		
		for(set<int>::iterator it=fa.begin();it!=fa.end();it++)//遍历其他祖先 
		{
			edge key = del.front();
			del.pop();//从待删目录里取边 
			
			printf("%d %d %d %d\n",key.u,key.v,root,*it);//输出 
		}
	}
	puts("");//好习惯 
	return 0;
} 
```
华丽的结束。

---

## 作者：ahawzlc (赞：4)

咋一看是个图论，仔细一看其实是个**并查集**。

----

我们用并查集可以表示每个连通块，方法就是用并查集```merge```操作来加边，同时如果加边不成功，即两个端点已经在同一连通块内，那么把这个边加进~~回收站~~```del[]```数组，等到后面输出答案时，这个有着半壁江山。```del[]```数组的大小就是最好的方案数。

然后我们扫描一遍并查集的```f[]```数组，统计连通块的个数（方法就是看有几个```f[i]==i```），连通块的个数后面要用。

再说后面的方案输出，我们只要清空回收站，然后把各个连通块合并成一个，具体的话——看代码罢。

~~代码在哪？就在下面~~

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define F first
#define S second
using namespace std;
const int N=10005;
int f[N],gr[N],n,tot,cnt,now;
pair<int,int> d[N];
int find(int x) {//并查集找祖宗
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
bool merge(int x,int y) {//并查集合并
	x=find(x);
	y=find(y);
	if(x!=y) f[x]=y;
	else return 1;
	return 0;
}
void del(int i) {//处理+输出函数
	printf("%d %d %d %d\n",d[i].F,d[i].S,gr[now],gr[cnt]);//输出回收站当前边、当前合并的连通块祖宗
	merge(gr[now++],gr[cnt]);//合并连通块并将当前连通块定位到下一个
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<n;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(merge(x,y)) d[++tot]=make_pair(x,y);//扔进回收站
	}
	for(int i=1;i<=n;i++) if(f[i]==i) gr[++cnt]=i;//统计连通块的祖宗
	now=1;
	printf("%d\n",tot);
	for(int i=1;i<=cnt-1;i++)
		del(i);//处理+输出
	return 0;
}

```

---

## 作者：Zvelig1205 (赞：2)

# 并查集

[题目传送门](https://www.luogu.com.cn/problem/CF25D)，个人感觉难度虚高。

题目保证有 $n$ 个点，$n-1$ 条边，让我们将整个图连通。

既然是 $n-1$ 条边，那么原图中肯定含有环。我们的任务就是找到这个环，然后拆环，将两个不同的连通块连起来。

直到最后连通块的数目为 1，任务完成。

细节方面：

1. 判环用并查集

	不知道这题能不能用 tarjan，~~反正我不会~~。

	当输入的两个点已经在同一个连通块内时，这条边的加入，会形成一个环。

2. 删边、连边

	我选择用一个队列储存每个连通块，每次找到构成环的一条边，然后将其删去（其实删不删都一样，都还在同一个连通块，所以并不需要什么操作），然后从队列里拿一个连通块，与当前连通块连起来。

	注意，如果拿出来的连通块仍是当前连通块，需要再拿一个。

	然后记录答案，将整个连通块塞到队列里，如果之前当前连通块就在队列里，则不操作。

大概的思路就是这样，代码：

```cpp
const int inf=1e5+7;
int n,ans,fa[inf];
bool inq[inf];
int huan[2][inf],cnt;
queue<int>h;
struct __ans{
	//个人感觉输出不需要太美观（主要是想不起来变量名了） 
	int _1,_2,_3,_4;
}ans_[inf];
int find(int x)
{//并查集基操
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	n=re();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<n;i++)
	{
		int u=re(),v=re();
		int r1=find(u),r2=find(v);
		if(r1^r2)fa[find(u)]=find(v);//并不连通 
		else huan[0][++cnt]=u,huan[1][cnt]=v;//环 
	}
	for(int i=1;i<=n;i++)
	{//找连通块 
		int ls=find(i);
		if(inq[ls])continue;
		inq[ls]=1;h.push(ls);
	}
	for(int i=1;i<=cnt;i++)
	{//删边 
		int rot=find(huan[0][i]);
		if(h.size()==1)break;//只剩 1 个连通块 
		int ls=h.front();h.pop();
		inq[ls]=0;fa[ls]=rot;
		if(ls==rot)
		{//同一个块，再拿一遍 
		//因为有 inq 的存在，所以队列里不可能有两个相同的连通块，
		//所以这里是 if 而不需要 while
			ls=h.front();h.pop();
			inq[ls]=0;fa[ls]=rot;
		}
		ans_[++ans]._1=huan[0][i];
		ans_[ans]._2=huan[1][i];//记录答案 
		ans_[ans]._3=rot,ans_[ans]._4=ls;
		if(inq[rot])continue;//塞到队列里 
		h.push(rot);inq[rot]=1;
	}
	wr(ans);putchar('\n');
	for(int i=1;i<=ans;i++)
	{//输出 
		wr(ans_[i]._1),putchar(' ');
		wr(ans_[i]._2),putchar(' ');
		wr(ans_[i]._3),putchar(' ');
		wr(ans_[i]._4),putchar('\n');
	}
	return 0;
}
```


---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF25D)

这是一道简单的灌水题。
## 思路
貌似题解里都在用并查集？其实只要一个灌水就可搞定，显然我们最少可以在一个大小为 $x$ 的连通块中保留 $x-1$ 条边，因为这个无向图只有 $n-1$ 条边，所以它如果不连通，那么在这些连通块中一定有某些连通块的边数大于点数减 $1$，我们显然可以把这些多余的边删掉，然后再把连通块连起来即可。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
int const N=1e3+10;
int vis[N],k[N],lian[N];
vector<int>a[N],b[N];
pair<int,int>p[N],del[N];
inline void dfs(int x){
    vis[x]=1;
    for (int i=0;i<a[x].size();++i){
        int v=a[x][i];
        if (!vis[v]){dfs(v),k[b[x][i]]=1;}//如果这条边连向了一个没有被灌水过的点，那么这条边需要保留
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cout.tie(0),cout.tie(0);
    int n,cnt=0;cin>>n;
    for (int i=1;i<n;++i){
        int u,v;cin>>u>>v;
        a[u].push_back(v);
        a[v].push_back(u);
        b[u].push_back(i);
        b[v].push_back(i);
        p[i]={u,v};
    }
    for (int i=1;i<=n;++i)
        if (!vis[i]) ++cnt,dfs(i),lian[cnt]=i;
    int tot=0;
    for (int i=1;i<n;++i) if (!k[i]) del[++tot]=p[i];//统计不需保留的边
    cout<<tot<<'\n';
    for (int i=1;i<=tot;++i)
        cout<<del[i].first<<' '<<del[i].second<<' '<<lian[1]<<' '<<lian[i+1]<<'\n';//把别的连通块与 1 号连通块连起来
    return 0;
}

```


---

## 作者：Minecraft万岁 (赞：1)

看看题目 $:$ 给定一个有 $n$ 个顶点 $n-1$ 条边的无向图  
咦 这不是一棵树吗  
于是本题拆边就变为了拆掉让树上**形成环**的边 连边就变为了让这颗树联通    
#### 先看判断拆边的条件   
比如说我们输入的时候有这个玩意 黑色是连接过了 红色是即将连接的     

![](https://cdn.luogu.com.cn/upload/image_hosting/bmprov1g.png)   
这个显然不可以连 连接就会产生环 不符合树的~~特性~~性质  
我们可以通过并查集 判断边的两个顶点在不在一个连通块 
如果在就不可以连 把这条边丢进拆边数组中   
如果不在就可以连 直接连上去就是了  

#### 再看看连边的条件  
连边就是让这棵树联通 说的简单点 就是把多棵树变成一颗   
比如说我们通过玄学处理 已经知道了若干个连通块以及要拆的边 黑色是连过的 红色是要连的 
![](https://cdn.luogu.com.cn/upload/image_hosting/rns9p0z3.png)  
我们不妨令 $1$ $2$ $3$ 为集合代表 ~~为了方便~~ 我们发现连边其实就是在祖先之间连边 **为了避免环的出现**  
我们就让其他的祖先全和 第一棵树的祖先连边 ~~反正输出任何一种 怕什么~~  
不会并查集的 [戳这里](https://www.luogu.com.cn/problem/P3367) 真的很简单  
于是乎我们有了~~简单易懂的~~代码  


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int n;
int f[1005],fx,fy;//并查集的相关部分 
int ans1[1005],ans2[1005],h1;//记录拆边的数组 
int dif[1005],h2;//记录不同的祖先 
int x,y;//读入边 
inline void read(int &x)//快读 
{
	int f;char c;
	for (f=1,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for (x=0;c<='9'&&c>='0';c=getchar()) x=x*10+(c&15);x*=f;
}
inline int mn(int _x,int _y)
{
	return _x<_y?_x:_y;
}
inline int mx(int _x,int _y)
{
	return _x>_y?_x:_y;
}
inline int ab(int _x)
{
	if(_x<0) return -_x;
	else return _x;
}
inline int fd(int p)//找一下祖先 
{
	return f[p]==p?p:f[p]=fd(f[p]);
}
int main()
{
	read(n); 
	for(int i=1;i<=n;i++) f[i]=i;//并查集的初始化 
	for(int i=1;i<n;i++)
	{
		read(x);read(y);
		fx=fd(x);//找两个点的祖先 
		fy=fd(y);
		if(fx==fy)//相同就代表在一个连通块里 
		{
			h1++;//这条边是要拆的 
			ans1[h1]=x;
			ans2[h1]=y;
		}
		else
		{
			f[fy]=fx;//不在一个连通块那就给它连上 
		}
	}
	for(int i=1;i<=n;i++)
		if(f[i]==i) dif[++h2]=i;//找一下不同的祖先 f[i]==i 保证不会重复记录同一个祖先 
	printf("%d\n",h1);//打印要拆的边 
	for(int i=1;i<=h1;i++)
		printf("%d %d %d %d\n",ans1[i],ans2[i],dif[1],dif[i+1]);//按照题目格式打印就是了 
	return 0;
}



```


---

## 作者：LuckyCloud (赞：1)

首先拆边的时候，肯定拆没用的边，换句话说就是，两个点已经联通了，再在这两个点上添加边，肯定就是没用的咯。

刚开始，所有点都是一个独立的集合，每当要添加一条新边的时候，判断该边连接的两点是否在同一个集合中，如果已经是同一个集合，那么该边就是没用的边。如果不在一个集合，那么就把该边连接的两点的所属集合合并——**并查集**

之后扫描任意两点，如果某两点不在同一个集合中，那么就添加一条边，使这两点联通，把该两点所属的集合合并。

主要就这么多，具体详细只能看代码了

    LuckyCloud
  
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct edge
{
  int u,v;
}del[4000];
struct data
{
 int u,v,x,y;
}Item[4000];
int fa[1013],sum[1013],tot,n,x,y,fx,fy,ans;
inline int find(int x)
{
  if (fa[x]==x) return x;
  fa[x]=find(fa[x]);
  return fa[x];
}
inline long long read()
{
  long long cnt=0,f=1;char ch=getchar();
  while (ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}
  while (ch>='0'&&ch<='9'){cnt=cnt*10+ch-48;ch=getchar();}
  return cnt*f;
}
void load()
{
  for (int i=1;i<=n;i++)
   fa[i]=i;
}
int main()
{
  n=read();
  load();
  for (int i=1;i<n;i++)
   {
   	x=read();y=read();
    fx=find(x);fy=find(y);
    if (fx!=fy) fa[fy]=fx;
    else {del[++tot].u=x;del[tot].v=y;}
   }
  for (int i=1;i<n;i++)
   for (int j=i+1;j<=n;j++)
    {
      fx=find(i);fy=find(j);
      if (fx!=fy)
       {
       	fa[fy]=fx;
       	Item[++ans].u=del[tot].u;
       	Item[ans].v=del[tot--].v;
       	Item[ans].x=i;
       	Item[ans].y=j;
       }
    }   
  printf("%d\n",ans);
  for (int i=1;i<=ans;i++)
   printf("%d %d %d %d\n",Item[i].u,Item[i].v,Item[i].x,Item[i].y);
  return 0;
}
```




---

## 作者：_szs9601 (赞：0)

### 思路
这道题的本质是并查集。

对于每两个点，如果祖先相同，则说明这两的点已经连通了，这条边是要删掉，所以我们将它保存下来。接着我们暴力枚举每两个点，若他们的祖先不同，则说明他们不是连通的，就把他们的祖先连起来。
### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
int i,n,m,ans,f[1010],a[1010],b[1010],c[1010],d[1010],fx,fy,x,y,j,t;
int find(int x){
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++) f[i]=i;
	for(i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		fx=find(x);fy=find(y);
		if(fx!=fy) f[fx]=fy;
		else a[++m]=x,b[m]=y;//保存
	}//并查集
	if(m==0){printf("0\n");return 0;}
	t=1;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){//枚举
			fx=find(i);fy=find(j);
			if(fx!=fy) ans++,c[t]=fx,d[t]=fy,f[fx]=fy,t++;//保存
//因为只有n-1条边，所以结果一定个不存在环的图，即是不会有边多出来的
		}
	printf("%d\n",ans);
	for(i=1;i<=m;i++) printf("%d %d %d %d\n",a[i],b[i],c[i],d[i]); 
	return 0;
}
```


---

## 作者：TheSky233 (赞：0)

## Description

给定一个有 $n$ 个顶点，$n-1$ 条边的无向图，每一次操作都能去掉一条边，并且重新在某两个顶点之间连一条新边。试求需要多少次操作，才能使得从任一顶点都能到达其他的所有顶点。

## Solution

前排提醒：~~这应该是本题最暴力的一篇题解了~~。

思路：并查集、暴力枚举。

对于每一个输入的 $u,v$，首先判断它们是否在一个联通块内，如果是，说明这条边没有用，扔进无效边的边集中去。如果不是，就合并两个集合。这些操作可以用并查集轻松实现。

然后**暴力枚举**每一个顶点 $i,j$，如果它们不在一个集合中，合并之后输出即可。

时间复杂度：$O(n^2\times \alpha(n))$，其中 $\alpha(n)$ 为阿克曼函数的反函数，一般情况下 $\alpha(n)\leq 4$。[Click here to know more。](https://baike.baidu.com/item/%E9%98%BF%E5%85%8B%E6%9B%BC%E5%87%BD%E6%95%B0/10988285?fr=aladdin)

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,fa[1005],size[1005],cnt;
pair<int,int> remain[100005];

int find(int x){
	if(x!=fa[x]) return fa[x]=find(fa[x]);
	return fa[x];
}

void merge(int x,int y){
	fa[find(x)]=find(y);
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		if(find(u)!=find(v)) merge(u,v);
		else remain[++cnt]=(make_pair(u,v));
	}
	cout<<cnt<<endl;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(find(i)!=find(j)){
				printf("%d %d %d %d\n",remain[cnt].first,remain[cnt].second,i,j);
				merge(i,j);
				--cnt;
			}
		}
	}
	return 0;
}

```

---

## 作者：初云悕 (赞：0)

一道非常简单的并查集练手题。题意大概是给你 $N-1$条边让你改几条边让图变成连通图，有一种非常简单的实现方法就是在读入的时候用一个栈记下重边（指两点已经在一个集合中，格外的连边），然后暴力求出每个集合的随意一个节点，也用栈存下，然后两个栈互相匹配一下（随意匹配就可以了），因为数据范围很小，所以直接用暴力实现就可以了。
```cpp
//简单的压行，极致的体验，程序的思路应该很清楚了罢
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}
const int N = 1005;
int n , pre[N] , cu1[N] , cu2[N] , tot , tot2 , s[N] , to[N],ans;
int _find(int x) {if(pre[x]==x) return x;return _find(pre[x]);}
bool _union(int x,int y){return _find(x)!=_find(y);}
main() {
	n = read();
	for(int i = 1 ; i <= n ; i ++) pre[i] = i;
	for(int i = 1 ; i <= n-1 ; i ++) {
		int x = read() , y = read();
		if(_union(x,y)) pre[_find(x)]=_find(y);
		else cu1[++tot]=x,cu2[tot]=y;
	}
	for(int i = 1 ; i <= n ; i ++) {
		int x = _find(i);
		if(!to[x]) s[++tot2]=x,ans++,to[x]=1;
	}
	cout << ans-1<<endl;
	if(ans-1)	for(int i = tot2 ; i > 1 ; i --) cout<<cu1[tot--]<<" "<<cu2[tot]<<" "<<s[i]<<" "<<s[i-1]<<endl;
}
```


---

## 作者：yingkeqian9217 (赞：0)

看到要求连通，基本确定是并查集。

这题分为2部分，一个是看没用的边，一个是看那些没连通。如果没用的比需要的多，那也没有关系。

没用的边可以预处理掉，没联通的要后面做。所以要把边存下来，接下去就没有难度了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt,fa[1001],sx[1001],sy[1001],ans[1001],ans2[1001],sum;//
bool b[1001];
int find(int x){
	return fa[x]==x?fa[x]:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x);
	y=find(y);
	if(x<y) swap(x,y);
	fa[y]=x;
}//并查集常规操作
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++){
		cin>>sx[i]>>sy[i];
		if(find(sx[i])==find(sy[i])){
			ans[++cnt]=i;
			continue;//如果没用就不用再合并了
		}
		merge(sx[i],sy[i]);
	}
	for(int i=1;i<=n;i++) if(b[find(i)]==0) b[find(i)]=1,ans2[++sum]=find(i);
	cout<<sum<<endl;//输出
	for(int i=1;i<sum;i++){
		cout<<sx[ans[i]]<<' '<<sy[ans[i]]<<' ';
		cout<<ans2[i]<<' '<<ans2[i+1]<<endl;
	}
	return 0;
}

```


---

## 作者：yangwenbin (赞：0)

# 题解 CF25D 【Roads not only in Berland】

简单的kurskal模板题

众所周知kurskal，先写并查集：
```
int get_root(int u){
	if(father[u] == u){
		return u;
	}else{
		return father[u] = get_root(father[u]);
	}
}
bool pd(int u,int v){
	return get_root(u) == get_root(v);
}
void merge(int u,int v){
	father[get_root(u)] = get_root(v);
	return ;
}
```
然后预处理：把自己的爸爸设为自己

前往别忘了；

然后输入排序，贪心，求最小看是否在一个树上

但这题没权值所以不排序，直接kurskal

不过要增加判断边是否用过

```
void kurskal(){
	int c=1;
	for (int i = 1; i < n; ++i){
		if(pd(input[i].x,input[i].y)){
			continue;
		}
		c++;
		merge(input[i].x,input[i].y);
		vis[i]=true;
		if(n == c){
			return ;
		}
	}
	
}
```

然后统计没用过的边，输出
```
for (int i = 1; i < n; ++i){
	if(!vis[i]){
		ans++;
	}
}
printf("%d\n",ans);
```

最后再找一遍没输出的边，输出边

找到后在顺序寻找不在一起的集合

输出两个集合中的任意一个点

千万别忘了把两个集合连起来（~~鄙人就忘了WA了一次~~）

```
for (int i = 1; i < n; ++i){
	if(!vis[i]){
		printf("%d %d ",input[i].x,input[i].y);
		while(j<=n){
			if(!pd(input[i].x,j)){
				printf("%d %d\n",input[i].x,j);
				merge(input[i].x,j);
				break;
			}else{
				j++;
			}
		}
	}	
}
```





# code
```
#include <bits/stdc++.h>
using namespace std;
int father[100050];
bool vis[1000050];
int n,m,sum;
struct rode{
	int x,y;
}input[100050];
int get_root(int u){
	if(father[u] == u){
		return u;
	}else{
		return father[u] = get_root(father[u]);
	}
}
bool pd(int u,int v){
	return get_root(u) == get_root(v);
}
void merge(int u,int v){
	father[get_root(u)] = get_root(v);
	return ;
}
void kurskal(){
	int c=1;
	for (int i = 1; i < n; ++i){
		if(pd(input[i].x,input[i].y)){
			continue;
		}
		c++;
		merge(input[i].x,input[i].y);
		vis[i]=true;
		if(n == c){
			return ;
		}
	}
	
}
int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; ++i){
		father[i] = i;
	}
	for (int i = 1; i < n; ++i){
		scanf("%d %d",&input[i].x,&input[i].y);
	}
	//sort(input ,input+m,cmp);
	kurskal();
	int ans=0;
	for (int i = 1; i < n; ++i){
		if(!vis[i]){
			ans++;
		}
	}
	printf("%d\n",ans);
	int j=1;
	for (int i = 1; i < n; ++i){
		if(!vis[i]){
			printf("%d %d ",input[i].x,input[i].y);
			while(j<=n){
				if(!pd(input[i].x,j)){
					printf("%d %d\n",input[i].x,j);
					merge(input[i].x,j);
					break;
				}else{
					j++;
				}
			}
		}
		
	}
}

```


---

