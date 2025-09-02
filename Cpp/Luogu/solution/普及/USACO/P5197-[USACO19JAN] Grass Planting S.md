# [USACO19JAN] Grass Planting S

## 题目背景

USACO 一月月赛银组第一题

## 题目描述

到了一年中 Farmer John 在他的草地里种草的时间了。整个农场由 $N$ 块草地组成（$1 \leq N \leq 10^5$），方便起见编号为 $1 \ldots N$，由 $N-1$ 条双向的小路连接，每块草地都可以经过一些小路到达其他所有的草地。
Farmer John 当然可以在每块草地里种不同种类的草，但是他想要使得使用的草的种类数最小，因为他用的草的种类数越多，他就需要负担更高的花费。

不幸的是，他的奶牛们对选择农场上的草表现得十分苛刻。如果两块相邻（由一条小路直接相连）的草地种了同一种草，或者即使是两块接近相邻（均可由一条小路直接连向同一块草地）的草地，那么奶牛们就会抱怨她们进餐的选择不够多样。Farmer John 能做的只能是抱怨这些奶牛，因为他知道她们不能被满足的时候会制造多大的麻烦。

请帮助 Farmer John 求出他的整个农场所需要的最少的草的种类数。

## 说明/提示

在这个简单的例子中，4 块草地以一条直线的形式相连。最少需要三种草。例如，Farmer John 可以用草 $A,B,C$ 将草地按 $A - B - C - A$ 的方式播种。

## 样例 #1

### 输入

```
4
1 2
4 3
2 3```

### 输出

```
3```

# 题解

## 作者：Polarnova (赞：21)

考虑在一个点的父节点，子节点，这个点本身涂不同的颜色。而在这个点的孙节点（或祖节点）可以用同一个颜色集合来涂色。 

所以统计每个点的度，找到度最大的点，输出 这个点的度+1。
```cpp
#include<cstdio>
int x,y,ans,n,deg[100007];
int main() {
    scanf("%d",&n);
    for(int i=1;i<n;i++) {
        scanf("%d%d",&x,&y);
        if(++deg[x]>ans)ans=deg[x];
        if(++deg[y]>ans)ans=deg[y];
    }
    printf("%d",ans+1);
    return 0;
}
```

---

## 作者：wwwttlll (赞：6)

这么水的题是蓝题？？？

度数最大的点的度数加1即可

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200000];
int main(){
	cin>>n;
	int x,y;
	while(cin>>x>>y){
		a[y]++;
		a[x]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(a[i]>ans){
			ans=a[i];
		}
	}
	ans+=1;
	cout<<ans;

}

```


---

## 作者：Alex_Wei (赞：4)

#### USACO 19JAN T1 Grass Planting

乍一看，还以为是道DFS+模拟，结果代码噼里啪啦一打上去，TLE的TLE，WA的WA，后来仔细思考，才发现原来这是道水题！

### 思路：求出度数最大的那个点，输出度数+1

所有草地如果都满足这个性质：

### 该草地及与其直接相邻的所有草地 的种类两两不同

那么就不会有两块直接相邻或接近相邻的草地种类一样（想一想，为什么？）

这样答案就是度数最大的点的度数+1（别忘了把这个点加上去）

### 代码：

估计这是全洛谷最水的蓝题了

~~码风：能打7行的代码绝不打17行，能打179b的代码绝不打279b~~

```cpp
#include<iostream>
int n,u,v,s,p[100100];
int main(){
	std::cin>>n;
	for(int x=1;x<n;x++)std::cin>>u>>v,p[u]++,p[v]++,s=std::max(s,std::max(p[u],p[v])+1);
	std::cout<<s;
}
```

#### 珍爱生命，远离抄袭！

如果有错误或建议欢迎在右侧->评论区指正或私信给我，谢谢！

求赞QWQ

---

## 作者：LZOI_LYH (赞：4)

这道题乍眼一看，感觉像是一道图论题；乍眼二看，感觉不像是求最短路的。

在仔细观察样例解释，诶，这不就是就图里的最大度数吗？（-_-\\）

心里很怀疑这道题到底是怎么评上蓝题的。。。

感觉并不难啊！

思路如下：

1. 输入

2. 存图

3. 找边的关系中出现最少的一个点作为dfs的起点，开始dfs

4. dfs结束后一遍循环找出度数最大的点

dfs的过程：

1. 首先判断当前dfs到的点有没有被搜索过

2. 如果搜索过，直接return。否则将当前点的度数+1，修改成已经被访问过

3. 枚举当前点的出边，直接去搜，回到步骤1。。。

4. 回溯的时候将当前边的终点的度数+1。。。

代码如下（码风比较丑，请各位大佬不要介意）

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct node{//链式前向星，担心邻接矩阵存不下。。。
	int nxt,to;
}edge[200002];
int head[100001],sum[100001],s[100001],cnt=0;//本人习惯请大家不要介意
//sum[i]是点i的度数，s[i]表示第i个点在输入中出现了几次。
//例如样例就是1出现了1次，2出现了2次，3出现了2次，4出现了1次。
bool vis[100001]={0};//vis[i]表示第i个点有没有dfs过
inline void add(int u,int v){
	edge[++cnt].nxt=head[u];
	edge[cnt].to=v;
	head[u]=cnt;
}//链式前向星存边
void dfs(int u){
	if(vis[u]==1)//查找当前点有没有被搜索过
		return ;//搜索过直接return
	sum[u]++;//当前点度数+1
	vis[u]=1;//设置为已经被访问过
	for(int i=head[u];i;i=edge[i].nxt){//枚举出边
		int v=edge[i].to;//当前枚举到的边的终点
		dfs(v);//继续dfs
		sum[v]++;//终点度数+1
		
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);//输入边的关系
		add(x,y);//加边
		add(y,x);//别忘了是双向边
		s[x]++,s[y]++;//统计出现次数
	}
	int tmp=2147483647,p;//tmp表示出现次数最少的点的出现次数
	//p表示出现次数最少的点
	for(int i=1;i<=n;++i)
  		if(tmp>s[i])
        tmp=s[i],p=i;//更新
	dfs(p);//开始dfs
	int ans=0;//ans表示最终答案
	for(int i=1;i<=n;++i)
		ans=max(ans,sum[i]);//找出度数最大值
	printf("%d",ans);//输出
	//完美结束(Yeah！！)
}
```

[AC证据](https://www.luogu.org/recordnew/show/16548905)

本人不才，第一次写题解，希望管理员大大可以审核通过，拜托了。


---

## 作者：06ray (赞：4)

很巧妙的树形$dp$。

设$f[x]$表示$x$的子树需要草的种类数。

那么，我们很容易得到状态转移方程

$f[x]=max(f[v],son[v]+2,son[x]+1);$

其中$v$为$x$的子节点，$son[x]$表示$x$的子节点的个数，$son[v]$表示$v$的子节点的个数

因为要让子树中的每个节点接近相邻和相邻节点类别不同，

所以我们要求子树中最大的一个每个节点都与其他节点接近相邻或相邻的集合。

$son[v]+2$是x节点与x的一个子节点以及这个子节点的所有子节点，
$son[x]+1$是x与x的所有子节点，
$f[v]$是x的一个子节点的子树中的不同种类数，
三者取最大就是$f[x]$的值。

代码：

```
#include <iostream>
#include <vector>
using namespace std;
vector<int>G[501000];//vector存图
int son[501000],f[501000];
void dfs(int x,int last)
{
	son[x]=G[x].size()-1;
	if(x==1) son[x]++;//求出son[x]
	for(int i=0; i<G[x].size(); i++)
	{
		int v=G[x][i];
		if(v==last) continue;
		dfs(v,x);
		f[x]=max(f[x],max(f[v],son[v]+2));
	}
	f[x]=max(f[x],son[x]+1);
}
int main()
{
	int n;
	cin>>n;
	for(int i=1; i<n; i++)
	{
		int a,b;
		cin>>a>>b;
		G[a].push_back(b);
		G[b].push_back(a);//建边 
	}
	dfs(1,0);
	cout<<f[1];//输出
	return 0;
}
```



---

## 作者：zylll (赞：3)

这道题非常的巧妙。

找到图中度最大的度数，加一即可。

因为要保证同一颗树下根节点与子节点的颜色都不相同，那么只要找到最大的个数，其他的节点均可用这些颜色中的一种来表示，可以说是一个子集包含的关系。

最后答案记得加一，因为还有根节点。

```
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
static const int MAXN=100050;
using namespace std;
int n,u,v,Max=-1,ans[MAXN];
inline int read()
{
    int x=0;bool sign=false;
    char alpha=0;
    while(!isdigit(alpha)) sign|=alpha=='-',alpha=getchar();
    while(isdigit(alpha)) x=(x<<1)+(x<<3)+(alpha^48),alpha=getchar();
    return sign?-x:x;
}
int main()
{
    freopen("planting.in","r",stdin);
    freopen("planting.out","w",stdout);
    n=read();
    for(int i=1;i<=n-1;i++)
    {
        u=read();v=read();
        ans[u]++,ans[v]++;
        Max=max(Max,max(ans[u],ans[v]));
    }
    printf("%d\n",Max+1);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
```

[分享一波自己的博客qwq，USACO 2019 January Contest, Silver](https://beyondlimits.site/1118.html)

---

## 作者：fls233666 (赞：2)

首先可以由题目描述得到，**FJ的农场是一个树型的结构**。

其次我们知道，**一块草地需要与其它与这个草地直接相连的草地用不同的草料**。

考虑到树的特点： _没有环_ 。我们可以发现，**对于与某块草地不直接相连的草地，可以使用已经使用过的草料解决问题**。

所以，我们只要**找到一个入度最大的点，输出最大的入度+1作为答案**即可。【 _+1的原因是要算上这个入度最大的点本身_ 】

对于入度的统计，在建树连边的函数中进行即可。

下面就是AC代码：

```cpp
#include<iostream>
#include<cstdio>
#define rgt register int
using namespace std;

const int mxn = 1e5+5;

int lst[mxn],nxt[mxn*2],to[mxn*2],d[mxn]; 
//边链表建边，数组d[]统计入度

int n,tot;

inline void add(int u,int v){
	tot++;
	to[tot]=v;
	d[v]++;   //统计入度，其它是边链表建边常规操作
	nxt[tot]=lst[u];
	lst[u]=tot;
}
//建边函数

int main()
{
	int ans=0;
	scanf("%d",&n);
	for(rgt a,b,i=1;i<n;i++){
		scanf("%d%d",&a,&b);
        //读入边并建边【无向边要正反建两次】
		add(a,b);
		add(b,a);
	}
	for(rgt i=1;i<=n;i++){
		ans=max(ans,d[i]+1);
	}    //找到答案并输出
	printf("%d",ans);
	return 0;
}
```


---

## 作者：45dino (赞：1)

一道结论题。

对于每一个点，衍生出的线连接的点的种类必然不同。

这听上去很~~骚~~玄学可以写一组样例（不要用题目中的）
```
7
1 2
2 3
3 4
2 5
5 6
5 7
```
把它画成图，就是这样的：
![](https://cdn.luogu.com.cn/upload/image_hosting/5t75osa9.png)

众所周知，一个块草地周围的所有草的种类都不能相同（包括这个点）。同样看一下图帮助理解：
![](https://cdn.luogu.com.cn/upload/image_hosting/2o678kr0.png)

（颜色有点奇怪，将就着看吧）

显而易见，由题意可知，草地2，5，6，7必然种类不同。

于是就如同其他人所说的，算出所有点中，连接最多的点的度，再加一。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int ans,n,a[100001];
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		a[x]++;//和x相邻的点的数量（不包括x）
		a[y]++;
		ans=max(a[x],max(a[y],ans));
	}
	cout<<ans+1;//因为不包括本身，所以要加一
	return 0;
}
```


---

## 作者：李若谷 (赞：1)

首先根据题意，我们知道这是一个N-1条变的连通图。

那么，一个点所能直接到的所有点终点最大值就是答案了。

因为这个图是没有交集的图，所以两个子图之间不会互相影响。
还有要注意的是判断一个点所到的连通图不要建立邻接矩阵，会超时，直接用数组。

代码：

```
#include <iostream>
using namespace std;
struct EDGE{
	int to;
	int next;
}edge[100001];
int head[100001];
int f[100001];
int cnt = 0;
int main()
{
	int n;
	cin>>n;
	int maxx = -1;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		f[x] ++;
		f[y] ++;
		maxx = max(f[x],maxx);
		maxx = max(f[y],maxx);
	}
	cout<<maxx+1<<endl; //要加1因为自己也算一个点，maxx只是能联通的点
	return 0;
}
```


---

