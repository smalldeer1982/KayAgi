# [USACO05MAR] Out of Hay S

## 题目描述

Bessie 计划调查 $N$（$2 \leq N \leq 2\,000$）个农场的干草情况，它从 $1$ 号农场出发。农场之间总共有 $M$（$1 \leq M \leq 10^4$）条双向道路，所有道路的总长度不超过 $10^9$。有些农场之间存在着多条道路，所有的农场之间都是连通的。

Bessie 希望计算出该图中最小生成树中的最长边的长度。


## 样例 #1

### 输入

```
3 3
1 2 23
2 3 1000
1 3 43```

### 输出

```
43```

# 题解

## 作者：Growl、 (赞：21)

**最小生成树算法**

~~根据题目描述，这道题是最小生成树~~

**树**：

~~树是一种植物，木本植物之总名，主要由根、干、枝、叶、花、果组成~~

一个不存在回路的无向联通图叫做树

**生成树**：生成树是连通图的极小联通子图。（加边会出现回路，减边变为非连通图）

**最小生成树**：
生成树的各边权值总和最小的树（最小代价树）

最小生成树一般有两种算法：prim和kruskal。prim一般用于稠密图，kruskal用于稀疏图。

这里介绍一下kruskal。

kruskal算法的基本思想是：始终选择当前可用的最小权值边（贪心

因此很容易想到题目所求的最大边就是最后一条边（每次加边权取max也可以）。

那么怎么判断当前选择的边是否可用呢？

**并查集**

意思就是说，开始的每个点都是独立的集合，加边的时候就合并起来，如果已经是联通的就跳过。

附上代码```
```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int fa[200004];
int n,m,l,r,tot,ans,k;

inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}//快读 

struct node{
	int fir;//第一个点 
	int sec;//第二个点 
	int data;//边权 
}edge[400005];

inline int find(int x){
	if(x==fa[x])return x;
	else return fa[x]=find(fa[x]);
}

inline bool cmp(node a,node b){
	return a.data<b.data;//结构体排序 
}

inline void kruskal(){
	for(register int i=1;i<=m;i++){
		l=find(edge[i].fir);
		r=find(edge[i].sec);
		if(l==r)continue ;//如果联通就跳过 
		fa[l]=r;//否则就合并 
		k=edge[i].data;//每次更新边权，最后一条边为最大 
	//	maxn=max(maxn,edge[i].data);每次加边取max也可以 
		tot++;
		if(tot==n-1)break;
	}
}

int main(){
	n=read();
	m=read();
	for(register int i=1;i<=n;i++)
	fa[i]=i;//初始化并查集 
	for(register int i=1;i<=m;i++){
		edge[i].fir=read();
		edge[i].sec=read();
		edge[i].data=read();
	}
	
	sort(edge+1,edge+m+1,cmp);//将边权排序，每次加小的 
	kruskal();
	cout<<k;//我喜欢cout...
	 
	return 0;
}
```

```


---

## 作者：卢本伟丶NiuB (赞：13)

### 题目：out of hay（翻译：奶牛爱干草）

（花里胡哨的 没有用）

[题目传送门](https://www.luogu.org/problemnew/show/P1547) 本人身为蒟蒻 来水一篇题解

题目还是好水的，最重要的是，题目把最主要的算法直接说出来了（真是直接啊）    

------------------------------------------------------------**分割线**---------------------------------------------------------

最小生成树：

就是任意一棵最小生成树一定包含无向图中权值最小的边。

这里有Kruskal和Prim两种算法 个人推荐克鲁斯卡尔（稀疏图）

##### 算法流程如下：

##### 1.建立一个并查集，每个点各自构成一个集合。

##### 2.把所有边按照权值从小到大排序，依次扫描每条边

##### 3.若x，y连通，就忽略这条边，扫描下一条

##### 4.否则，合并x，y所在的集合，并把z累加到答案里

时间复杂度为**O(m log m)**

下面上代码（想说的在里头）

```c
#include<iostream>
#include<algorithm> 
using namespace std;
int n,m;
long long fa[100000001];
struct hay
{
	int x,y,z;
}a[10001];
inline bool cmp(hay a,hay b)
{
	return a.z<b.z;
}
//将权值从小到大排序 
inline int find(int t)
{
	if(fa[t]==t) return t;
    else return fa[t]=find(fa[t]);
} 
//路径压缩的日常。。。。 
inline void me(int r1,int r2)
{
	int s1=find(r1);
	int s2=find(r2);
	fa[s1]=s2;	
}
// 核心代码如下
inline void Kruskal()
{
	int k=0;
	int k1,k2;
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		k1=find(a[i].x);
		k2=find(a[i].y);
		if(k1==k2) continue;//如果在一个集合内就忽略这条边，扫描下一条 
		k++;
		me(k1,k2);
		//合并 x y所在的集合 就是把边（x，y）放入最小生成树中 
		ans=max(a[i].z,ans);
		if(k==n-1) break;
		//到n-1条边停止，最小生成树只需要n-1条边 
	}
	cout<<ans;
}
int main()
{
	cin>>n>>m;
	int i;
	for(i=1;i<=n;i++)
	{
		fa[i]=i;
	}
	//并茶集初始化 
	//所有元素各自构成一个独立的集合 即为n棵点数为1的树 
	for(i=1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].y>>a[i].z;
	} 
	sort(a+1,a+m+1,cmp);
	Kruskal();
	return 0;
}
```

# 制作不易 不喜勿喷

---

## 作者：sounds_666 (赞：10)

额，这题貌似这就是一个Prim的模板题吧！

思路：
	先跑一遍Prim，得到最小生成树，然后在所有所选边中寻找最大值。
    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int dis[5000+10][5000+10],minn[6000];//dis用来存距离，minn求答案值
bool vis[6000];//记录访问情况
long long sum;//用来累加
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
    memset(dis,0x3f3f3f3f,sizeof(dis));//初始化
    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        dis[x][y]=min(dis[x][y],z);//双向图存图（邻键表）
        dis[y][x]=min(dis[y][x],z);
    }
    memset(vis,false,sizeof(vis));//继续初始化
    memset(minn,0x3f3f3f3f,sizeof(minn));
    minn[1]=0;
    for(int i=1;i<=n;i++){//Prim模板开始
        int k=0;
        for(int j=1;j<=n;j++)
            if(!vis[j]&&minn[j]<minn[k])//找点
                k=j;
        vis[k]=true;//标记已访问
        for(int j=1;j<=n;j++)
            if(!vis[j])
                minn[j]=min(minn[j],dis[k][j]);//更新最小值
    }
    for(int i=1;i<=n;i++)sum=max((long long)minn[i],sum);//找最大值
    printf("%lld",sum);
	return 0;
}
```


---

## 作者：Ajwallet (赞：10)

一开始看到最小生成树，果断prim然后。。。果断WA了5个点，所以就重新审视了一下题目，发现其实只要排个序（最长边嘛），连个边（生成树嘛），就可以了。

先发个50分的。。。
```
```C++
#include<bits/stdc++.h>
#define INF 2147483648
#define r(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int l[2001][2001],n,m,x,y,z,dis[2001],minn,k,ans;//只弄了2000乘2000.。。
bool vis[2001];
int main()
{
    r(i,0,2000) r(j,0,2000) l[i][j]=INF/4;
    scanf("%d %d",&n,&m);
    r(i,1,m)
     {
     	scanf("%d %d %d",&x,&y,&z);if(x==y) continue;//自环判断
     	l[x][y]=l[y][x]=min(l[x][y],min(z,l[y][x]));//重边判断
     }
    r(i,1,n)
     dis[i]=l[1][i];dis[1]=0;//初始化
    r(i,1,n-1)
    {
        minn=INF/4;k=0;vis[i]=true;
        r(j,1,n)
         if(dis[j]<minn&&!vis[j])//找最短的
          {
          	minn=dis[j];//赋值
          	k=j;//标记
          }
        vis[k]=true;//标记
        if(!k) break;//找不到直接结束
        if(minn<=INF/4) ans=max(ans,minn);//找到了才赋值
        r(j,1,n)
         if(l[j][k]<dis[j])//修整
          dis[j]=l[j][k];
    }
    printf("%d",ans);//输出
}
```
代码AC
```
```C++
#include<bits/stdc++.h>
#define r(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int f[2001],n,m,x,y,z,tat,ans;//tat是当前连边个数，f是并查集数组，ans是最终答案
struct node{int from,to,w;}a[20001];//结构体，等下直接排序
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}//找祖宗
void judge(int x,int y){f[find(x)]=find(y);}//连边
bool too(int x,int y){return find(x)==find(y);}//判断两个元素是否在同一集合内
bool cmp(node x,node y){return x.w<y.w;}//按按权值从小到大排（最小生成树）
int main()
{
    scanf("%d%d",&n,&m);r(i,1,n) f[i]=i;//初始化
    r(i,1,m)
     scanf("%d %d %d",&a[i].from,&a[i].to,&a[i].w);//输入
    sort(a+1,a+1+m,cmp);//排序
    r(i,1,m)
      if(!too(a[i].from,a[i].to))//没有连边
      {
      	tat++;if(tat==n-1) {ans=max(ans,a[i].w);break;}//连，如果连到n-1条边就退出，最小生成树只需要n-1条边
      	judge(a[i].from,a[i].to);//合并
      	ans=max(ans,a[i].w);//统计最大值
      }
    printf("%d",ans);//输出
}
```

---

## 作者：wmyQAQ (赞：7)

## 最小生成树

[更好的阅读体验](https://jvruo6666666666666.blog.luogu.org/solution-p1547#)

在这里介绍一下最小生成树的一个~~众所周知~~的算法—— **Kruskal（克鲁斯卡尔）** 算法
### 前置技能：并查集
如果你不会请移步模板：[P3367 【模板】并查集](https://www.luogu.org/problemnew/show/P3367)

这里举如下图的例子
![](https://cdn.luogu.com.cn/upload/pic/60901.png)

这个图中一共有3个连通块，其中1、2为一个，4、5、6为一个，3为一个。

## Kruskal

### 一般有下面几步：

1、将所有的边按边权从小到大排序（sort） ；

2、按从小到大排的顺序枚举所有的边 ；

3、如果是两个不同的集合，那么就计入最小生成树，合并集合。

### 算法流程：
1、初始化并查集 ~~（你就是你爸爸）~~
```
	for(int i=1;i<=n;i++)
    	fa[i]=i;
```
2、计数器（记录树边权和（ans），记录边数（bian））
```
	ans=0;
	bian=0;
```
3、排序所有的边权（这里用结构体来储存出发点，到达点，边权）
```
	struct chengshi
	{
		int x,y,v;
	}a[200001];
	sort(a+1,a+m+1,cmp);
```
4、枚举
```
	for(int i=1;i<=m;i++)
	{
		if(fa(a[i].x)!=fa(a[i].y))
		{
			lian(a[i].x,a[i].y);
			ans+=a[i].v;
			bian++;
			maxn=max(maxn,a[i].v);
		}
	}
```
5、这个题独特的一点，上面你也可能看出来了，它求的是最小生成树是最长边权，所以 ~~（貌似记录器都没什么用）~~
```
			maxn=max(maxn,a[i].v);
```

## 上代码
并查集的部分不在解释，关于**Kruskal**的解释上面以有。

状态：AC

``` 
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int n,m,fat[5001],x,y,v,shu,ans,bian,maxn=-1;
struct chengshi
{
    int x,y,v;
}a[200001];

int fa(int x)
{
    if(fat[x]!=x) fat[x]=fa(fat[x]);
    return fat[x];
}

void lian(int x,int y)
{
    int aa=fa(x),bb=fa(y);
    if(aa!=bb) fat[aa]=bb;
}

int cmp(chengshi a,chengshi b) //快排的cmp函数
{
    if(a.v<b.v) return 1;
    else return 0;
}

int max(int a,int b) {return a>b?a:b;}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y>>v;
        a[i].x=x;
        a[i].y=y;
        a[i].v=v;
    }
    for(int i=1;i<=n;i++) fat[i]=i;
    sort(a+1,a+m+1,cmp);
    for(int i=1;i<=m;i++)
    {
        if(fa(a[i].x)!=fa(a[i].y))
        {
            lian(a[i].x,a[i].y);
            ans+=a[i].v;
            bian++;
            maxn=max(maxn,a[i].v);
        }
    }
    cout<<maxn;
    putchar('\n'); //换行，比较快吧
    return 0;
}

/*
3 3
1 2 23
2 3 1000
1 3 43

*/
```

---

## 作者：菜鸡gyf (赞：2)

## 大致题意
有n(2<=n<=2000)个点，有m条(1<=m<=10000)无向边,它们是联通的。从1号出发，经过每一个点，使总路程最短，求这条路径中最大的一条边的权值。

## 算法分析
这是一道标准的最小生成树问题，一般有prim和kruskal两种方法。

## prim方法
朴素prim时间复杂度O（n^2），适合稠密图，堆优化后更是可以达到O（mlogn)的复杂度，但在此题完全没必要用堆优化（好吧，是我懒）。时间158ms 空间15.95MB

注意：在完全图中，m是m(m-1)/2，这时，堆优化不如朴素的prim。

代码：
```
#include<cstdio>
using namespace std;
int f[2001][2001],book[2001],dis[2001]={0};
const int inf=1e9;
int main()
{
	int n,m,i,j,k,count=1,maxn=0,x,y,z,minn;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
	for(j=1;j<=n;++j)
	{
		if(i!=j)
		f[i][j]=inf;
		else
		f[i][j]=0;
	}
	for(i=1;i<=m;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(f[x][y]!=0&&z>f[x][y])
		continue;
		f[x][y]=z;
		f[y][x]=z;
	}
	for(i=1;i<=n;++i)
	dis[i]=f[i][1];
	book[1]=1;
	while(count<n)
	{
		minn=inf;
		for(i=1;i<=n;++i)
			if(book[i]==0&&dis[i]<minn)
			{
				minn=dis[i];
				k=i; 
			}
		book[k]=1;
		if(dis[k]>maxn)
		maxn=dis[k];
		++count;
		for(i=1;i<=n;++i)
			if(book[i]==0&&dis[i]>f[i][k])
			dis[i]=f[i][k];
	}
	printf("%d",maxn);
	return 0;
}
```

## kruskal方法

kruskal算法时间复杂度O（mlogm),在稀疏图中表现较好。时间43ms 空间944.00KB

代码：
```
#include<cstdio>
using namespace std;
struct node{
	int u,v,w;
}e[100001];
int n,m,maxn,count=0;
int dis[2001];
void quicksort(int left,int right)
{
	int i,j;
	struct node t;
	if(left>right)
	return;
	i=left;
	j=right;
	while(i!=j)
	{
		while(e[j].w>=e[left].w&&i<j)
		j--;
		while(e[i].w<=e[left].w&&i<j)
		i++;
		if(i<j)
		{
			t=e[i];
			e[i]=e[j];
			e[j]=t;
		}
	}
	t=e[left];
	e[left]=e[i];
	e[i]=t;
	quicksort(left,i-1);
	quicksort(i+1,right);
}
int getf(int v)
{
	if(dis[v]==v)
	return v;
	else
	{
		dis[v]=getf(dis[v]);
		return dis[v];
	}
}
int merge(int v,int u)
{
	int x,y;
	x=getf(v);
	y=getf(u);
	if(x!=y)
	{
		dis[y]=x;
		return 1;
	}
	return 0;
}
int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	quicksort(1,m);
	for(i=1;i<=n;++i)
	dis[i]=i;
	for(i=1;i<=m;++i)
	{
		if(merge(e[i].u,e[i].v)==1)
		{
			count++;
			maxn=e[i].w;
		}
		if(count==(n-1))
		break;
	}
	printf("%d",maxn);
	return 0;
}
```

# 谢谢大家观看！

你以为到这里就完了吗？不！还有一道和这道题几乎一模一样的黄题，只需要在kruskal的
```
printf("%d",maxn);
```
改为
```
printf("%d %d",n-1,maxn);
```
即可AC，我是不会告诉你们这道题就是P2330的。
[这里](https://www.luogu.com.cn/problem/P2330)

---

## 作者：XQLG (赞：2)

这道题，就是模板

P3366【模板】最小生成树

**~~要是直接放代码我怕会过不了~~**

所以~~~~~~

还是先讲一讲模板吧（不是讲模板这道题）

最小生成树，就是在n个点上，有m条边，每条边有一定的权值，你就把他当做长度吧

这里介绍一种算法，叫做

# Kruskal

这种算法本质上就是贪心。

将题目给出的m条边的权值，进行排序

再从权值最小的边开始画图（前提是，加上这条边没有出现环）

由于有一个定理，最小生成树一共会有n-1条边。

所以，我们的循环边界就是生成树上由n-1条边

每一道最小生成树的题，总会有三个东西：起点、终点、权值

这三个东西是配套使用的，所以不可能用三个数组，单一排序是不可能完成的

所以，我们又引入了一个数据存储方式：结构体

之前我们学习过的存储方式有：变量、数组、队列、栈、优先队列等等

结构体就是自己自定义一种数据类型

结构体这个东西，肯定是有一些特殊的用法的

算了，给一段代码吧，自己看~~懒症上身~~

```cpp
#include<bits/stdc++.h>//习惯性用万能头，所以搞到每次考试都要重新背头文件
//希望你们不要学我 
using namespace std;
int n;
struct kk//kk是结构体的名字
{
	int a;//定义一个int类型的变量a 
	long long b;// 一个long long 类型的b 
	char c;//char类型的c 
	string d;//string类型的d 
	double e;//double类型的e 
 }k[110];//这是一个k数组，每一个数组格子里有5个变量 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>k[i].a>>k[i].b>>k[i].c>>k[i].d>>k[i].e;//输入 
	}
	for(int i=1;i<=n;i++)
	{
		cout<<k[i].a<<k[i].b<<k[i].c<<k[i].d<<k[i].e;//输出 
	 } 
    return 0;
}
```
由于我们的解题步骤中有一个地方是要进行排序的，所以，我们又有一个操作叫做结构体排序

给代码，自己看

```cpp
#include<bits/stdc++.h>//习惯性用万能头，所以搞到每次考试都要重新背头文件
//希望你们不要学我 
using namespace std;
int n;
struct kk//kk是结构体的名字
{
	int a;//定义一个int类型的变量a 
	int b;
	int c; 
}k[110];//这是一个k数组，每一个数组格子里有3个变量 
bool cmp(kk x,kk y)//写多了，就懂了 
{
	return x.a<y.a;//以a为排序的依据 （可以更换为b或c） 
} 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>k[i].a>>k[i].b>>k[i].c;
	}
	sort(a+1,a+n+1,cmp)//平常我们的数组排序中，也会有后面的cmp函数，只是平时不写，系统默认的只是从小到大的单个排序
	for(int i=1;i<=n;i++)
	{
		cout<<k[i].a<<k[i].b<<k[i].c;//自己试一下效果吧，我语文不好说不清楚 
	 } 
    return 0;
}
```
好了，我们终于有了一切的储备知识，可以开始做题了

上代码，看得懂的

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[5010],ok,ans,j;//自己按照题目的意思去定变量 
int find(int x)
{
	if(fa[x]==x) return x;
	else return fa[x]=find(fa[x]);
}//并查集，要是不会的，去买块豆腐撞死 
struct kk
{
	int x,y,z;
}a[200010];//结构体 
bool cmp(kk r,kk l)
{
	return r.z<l.z;
}//排序函数，写多了就会懂的，反正洛谷里基础的生成树很多，全刷完就对了 
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		fa[i]=i;//并查集的初始化，自己的爸爸是自己 
	for(int i=1;i<=m;i++)
		cin>>a[i].x>>a[i].y>>a[i].z;//输入 
	sort(a+1,a+m+1,cmp)//贪心排序 
	for(int i=1;i<=m;i++)
	{
		int f1=find(a[i].x);//寻找爸爸 
		int f2=find(a[i].y);//寻找爸爸 
		if(f1!=f2)//判环，若是一个环，就会是同一个爸爸，就不是一棵树，所以不执行操作 
		{
			fa[f1]=f2;//起点的爸爸是终点
			//或者可以
			//终点的爸爸是起点 
			ok++;//计数 
			if(a[i].z>ans) ans=a[i].z;//这道题目的要求并不仅仅是建造生成树，而是求最小生成树上的最长边 
		}
		if(ok==n-1) break;//到n-1就结束了 
	}
	cout<<ans;//输出 
	return 0;
}
```
码字不易，望通过。

要是这样还看不懂，你可以买块豆腐撞死了

---

## 作者：Eason_AC (赞：1)

## Content
$\text{Bessie}$打算调查$N$个农场的干草储备情况，她将从1号农场出发，顺着连接农场的$M$条边调查，每条边的长度为$a_i$。$\text{Bessie}$想知道，这个农场的地图中最小生成树中最长边的长度。

**数据范围：$2\leqslant N\leqslant2000,1\leqslant M\leqslant10000,a_i\leqslant10^9$**。

## Solution
最小生成树的模板题，刚学最小生成树的新手可利用此题加强巩固。

其实这道题目在$POJ$上有一模一样的题，叫做$\text{Highways(POJ2485)}$。它们两道题目都是让你求无向图中的最小生成树中最长边的长度。还有一个在洛谷上的[$\text{P1111}$](https://www.luogu.com.cn/problem/P1111)，实质上也和本题一样。

很简单，我们在[$\text{P3366}$](https://www.luogu.com.cn/problem/P3366)里头是不是让你求最小生成树的边权和？还记得$\text{Kruskal}$版本的核心代码是什么吗？
```cpp
for(int i = 1; i <= m; ++i) {
		int x = g(e[i].u), y = g(e[i].v);
		if(x != y) {
			f[x] = y;
			ans += e[i].w;
			cnt++;
		}
		if(cnt == n - 1)	break;
	}
```
那么这道题目很简单，就在这上面的$\text{ans += e[i].w}$的地方改动一下。这里是用的求和操作是不是？那么就把它改成取$\max$操作就可以了。

就像这样：
```cpp
for(int i = 1; i <= m; ++i) {
		int x = g(e[i].u), y = g(e[i].v);
		if(x != y) {
			f[x] = y;
			ans = max(ans, e[i].w);	//这里改动！
			cnt++;
		}
		if(cnt == n - 1)	break;
	}
```

把它改完，交上去，就过了！

是不是很简单？

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, x, y, z, f[2000010], line, side, sum;
inline int read () {
	char ch = getchar();
	int x = 0, f = 1;
	while (ch < '0' || ch >'9') {
		if(ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = x * 10 + (ch ^ 48), ch = getchar();
	return x * f;
}

struct Point {
	int u, v, w;
} po[2000010];

bool sorting_cmp(const Point &a,const Point &b) {
	return a.w < b.w;
}
 
inline int find(int x) {
	if(f[x] == 0)	return x;
	else			return f[x] = find(f[x]);
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read(), z = read();
		po[line].u = x, po[line].v = y, po[line].w = z;
		line++;
	}
	sort(po, po + line, sorting_cmp);
	for(int i = 0; i < line; ++i) {
		int t = po[i].w,
		ufa = find(po[i].u), vfa = find(po[i].v);
		if(ufa != vfa) {
			sum = max(sum, t);
			f[ufa] = vfa;
			line++;
		}
		if(line == n - 1)	break;
	}
	cout << sum;
	return 0;
}
```

---

## 作者：JasonZRY (赞：1)

最小生成树裸题。

下面是一个三目运算：

这道题如果你会最小生成树?一下就过了:点这里☞[我的博客：最小生成树](https://www.luogu.org/blog/666Jason/solution--p3366)

这里用Kruskal算法。

只要从新增的边找到一条最大的就好了，所以，merget函数要加一步。

所以说这就是代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,fa[2005],maxn;
struct edge{
    int fr,to,len;
}ed[100005];
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
void merget(int i){
	int fx=find(ed[i].fr),fy=find(ed[i].to);
	if(fx!=fy)fa[fx]=fy,maxn=max(maxn,ed[i].len);
}
bool cmp(edge a,edge b){
    return a.len<b.len;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)fa[i]=i;
    for(int i=1;i<=m;i++)cin>>ed[i].fr>>ed[i].to>>ed[i].len;
    sort(ed+1,ed+1+m,cmp);
    for(int i=1;i<=m;i++)merget(i);
    cout<<maxn;
    return 0;
}
```

完美搞定

---

## 作者：liuyifan (赞：1)

这道题就是个最小生成树的模板题

本蒟蒻表示:优先队列是什么?不知道

所以就老老实实的用Kruskal+并查集模板做吧,时间复杂度O(nlogn+np(n)),p(n)是一次并查集操作的复杂度)

对于像我一样啥都不懂的蒟蒻可以参考此链接:[Kruskal](https://www.cnblogs.com/yoke/p/6697013.html)(内容仅供参考,与我无关)

code:(所有模板均为手写,不含~~其实是不会~~STL)
```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
int n,m,p,s=0,cnt=0f[100005];
struct node{int a,b,x;}a[100005];//从A到B有一条边长为X的有向边
bool cmp(const node &ne,const node &be){return ne.x<be.x;}//将node按照边长X排序,如果要改成从大到小就把<换成>
inline int getfather(int x)
{
	if(f[x]==x) return x;
	f[x]=getfather(f[x]);
	return f[x],
}//并查集路径压缩,应该都会吧
原理:getfather(a)把a点到根节点的之间的所有节点(包括a)都接到了根节点的下方,显著降低了每次查询的复杂度
inline void kruskal()//Krustal模板,原理如上
{
	reg int cnt=0,x,y;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)
	{
		x=getfather(a[i].a);//压缩路径
		y=getfather(a[i].b);//同上
		if(x==y)continue;
		s=max(a[i].x,s);//最长边的长度
		f[x]=y;
		cnt++.
		if(cnt==n-1)break;
	}
	if(cnt<n-1)printff("-1");//操作不到n-1次(边不到n-1条),不存在最小生成树
	else printf("%d",s);//输出解
}
int main()
{
	scanf("%d%d",&n,&m);//scanf不用讲了吧
	for(reg int i=1;i<=m;i++)scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].x);
	sort(a+1,a+m+1,cmp);//结构体和多维数组的快排必须手写cmp(比较)函数
	kruskal();
	return 0
}
```
拒绝抄袭,共建和谐洛谷

提示:本题的代码可以和[P1111](https://www.luogu.org/problemnew/show/P1111)通用,~~可以一次水2道题~~

---

## 作者：wangyansong (赞：0)

# 优化的kruskal。
 自己刚看题，万分激动，双倍经验  t1111。
 
 AC后看大佬的超强思路，让我望尘莫及，无奈之下只好另辟蹊径
 
这篇题解主要是提供给新手参考（~~实际是自己太弱~~），其中还有一些小彩蛋（~~不用百度搜了~~），大佬勿喷啊...

 Kruskal 算法提供一种在 O(ElogV) 运行时间确定最小生成树的方案。Kruskal 算法基于贪心算法（Greedy Algorithm）的思想进行设计，其选择的贪心策略就是，每次都选择权重最小的但未形成环路的边加入到生成树中。其算法结构如下：

1）.将所有的边按照权重非递减排序；
2）.选择最小权重的边，判断是否其在当前的生成树中形成了一个环路。如果环路没有形成，则将该边加入树中，否则放弃。
3）.重复步骤 2，直到有 V - 1 条边在生成树中。

总的来说就是排个序，从头到尾判断（要最小耗费嘛），直到有都直接或间接连接，最后记下w就是答案。

还有一个是并查集的非递归是优化，主要是避免毒瘤顺序数据,像0123456789就成O(n)复杂度了。
详细请看代码。
```c
#include<bits/stdc++.h>//万能头文件不一定万能，还占用一定的时间 
using namespace std;
int f[3000],ans,m,n;//数组f的大小看n  
inline int find(int k)//路径压缩并查集  
{
   while(k!=f[k]) k=f[k]=f[f[k]];//非递归式，如果没查完就用k暂时记录。 
   return k;//最后返回到他的父亲。 
}
struct edge{
	int u,v;//u是开始遍（start），v是通往遍（to）。 
	long long w;//要定义long long。 
}e[10005];//e的大小看m
inline int cmp(edge x,edge y)
{//定义一个结构体大小比较，单独判断w。 
	return x.w <y.w ;
}
inline void kruskal()
{
	sort(e+1,e+m+1,cmp);//把w排好，w顺带就把 u ，v 带走 。 
	for(register int i=1;i<=m;i++)
	{//寻找 u，v 的父亲进行判断。  
		int a=find(e[i].u );
		int b=find(e[i].v );
		if(a==b) continue;//如果是一个父亲就不需要建树。 
		f[a]=b;//进行认亲 
		ans=e[i].w ;//因为前面排过序，ans会一直被最大值覆盖掉，结果永远最大。 
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
	//register 使变量尽可能存在CPU的内部储存器中，以提高效率。 
	  f[i]=i;//把自己当作父亲。 
	for(register int i=1;i<=m;i++)//注意是m条遍。 
	  scanf("%d%d%d",&e[i].u,&e[i].v ,&e[i].w );
	kruskal();
	printf("%d",ans);//ans要定义全局变量 
	return 0;//有无可无，调试必须有。 
}
```
注：蒟蒻是第一次发题解，如果有什么不对的或者总结不全的还望大佬指正。
 最后还希望管理能给点鼓励。

---

## 作者：蕾姆酱QvQ (赞：0)

让本蒟蒻来发一波题解吧QvQ


~~第一次写有点紧张的说（逃~~

首先我们看一下题目
题目背景
奶牛爱干草

题目描述
Bessie 计划调查N (2 <= N <= 2,000)个农场的干草情况，它从1号农场出发。农场之间总共有M (1 <= M <= 10,000)条双向道路，所有道路的总长度不超过1,000,000,000。有些农场之间存在着多条道路，所有的农场之间都是连通的。

Bessie希望计算出该图中最小生成树中的最长边的长度。

输入输出格式
输入格式：
两个整数N和M。

接下来M行，每行三个用空格隔开的整数A_i， B_i和L_i，表示A_i和 B_i之间有一条道路长度为L_i。

输出格式：
一个整数，表示最小生成树中的最长边的长度。

输入输出样例
输入样例#1： 复制
3 3
1 2 23
2 3 1000
1 3 43
输出样例#1： 复制
43


很明确，题目告诉我们就是裸的最小生成树，只不过要加一个特判条件：
当用kruskal生成的时候选择的边k==n-1时输出此时的边权就好啦qwq，因为已经排好序的边不需要再找最大的，最后加上的边一定是最大的啦qwq


下面是奇丑无比的代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>

using namespace std;

struct node{
	int x,y,dis;
}a[10001];

int father[10001],k,m,n;

bool cmp(node x,node y){ return x.dis<y.dis; }

int find(int x)
{
	if(father[x]!=x) father[x]=find(father[x]);
	return father[x];
}

void unionn(int x,int y)
{
	x=find(x),y=find(y);
	father[x]=y;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++) father[i]=i;
	for(int i=1; i<=m; i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].dis);
	sort(a+1,a+m+1,cmp);
	for(int i=1; i<=m; i++)
	{
		if(find(a[i].x)!=find(a[i].y))
		{
			unionn(a[i].x,a[i].y);
			k++;
		}
		if(k==n-1)
		{
			printf("%d",a[i].dis);
			return 0;
		}
	}
}
```


---

## 作者：op_z (赞：0)

```cpp
hhh 看到最小生成树 直接用kruskal了  
前向星+并查集
这道题求最小生成树最大边权 
而并查集里的mix()函数里
刚好可以把最小生成树每条边遍历一遍
不断比较找最大边权就好啦

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<set>
#include<string>
using namespace std;
const int INF=0x3f3f3f3f;
typedef pair<int, int> pr;
typedef long long ll;
#define fi first
#define se second
#define me(x) memset(x, -1, sizeof(x))
#define mem(x) memset(x, 0, sizeof(x))
#define MAXN 40000+5
#define NIL -1
struct node
{
    int u, v, w;
}edge[MAXN];
bool cmp(node a, node b) //升序排序
{
    if(a.w==b.w && a.u==b.u) return a.v,b.v;
    if(a.w==b.w) return a.u<b.u;
    return a.w<b.w;
}
int n, m;
int ans;
int p[MAXN];
int Find(int x) //查询操作
{
    int r=x;      
    while(p[r]!=r) //找根节点
        r=p[r];    
    int i=x, t;
    while(p[i]!=r) //路径压缩
    {              //其实就是把上级节点不断更新为根节点
        t=p[i];
        p[i]=r;
        i=t;
    }
    return r; //记得返回根节点
}
void mix() //合并 ans存当前最大边权
{
    for(int i=0; i<m; i++)
    {
        int x=Find(edge[i].u), y=Find(edge[i].v);
        if(x!=y)
            ans=max(ans, edge[i].w), p[y]=x;
    }
}
int main()
{
    int i, j, k;
    int u, v, w;
    while(cin>>n>>m)
    {
        for(i=1; i<=n; i++)
            p[i]=i;
        for(i=0; i<m; i++)
            cin>>edge[i].u>>edge[i].v>>edge[i].w;
        sort(edge, edge+m, cmp);
        ans=0;
        mix();
        cout<<ans<<endl;
    }
}
hhh 蒟蒻的题解结束

```

---

## 作者：agicy (赞：0)

# 思路

既然题目为求无向图最小生成树的最长边，那当然是选择$Kruskal$**+并查集**（时间复杂度为$O(mlogm+mα(n)),α(n)$是一次并查集的复杂度）来解题，其中最小生成树最后连接的那条边即为所求。

# 代码

代码如下。

```cpp
#include<stdio.h>
#include<algorithm>

struct Edge{
	int f,t,w;
	bool operator<(Edge a)const{
		return this->w<a.w;
	}//重载运算符，排序用，边权小的在前
};

int n,m,ID[2001],ans;//ID[]为并查集中的father数组
Edge r[10001];//边

void contact(int,int);//连接
bool search(int,int);//返回两点是否在同一集合
int find(int);//并查集的find()函数

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		ID[i]=i;//初始化
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&r[i].f,&r[i].t,&r[i].w);//读入
	std::sort(r+1,r+m+1);//排序
	for(int i=1,k=1;i<=m&&k<=n-1;i++){
		if(!search(r[i].f,r[i].t))//如果两点不在同一集合
			contact(r[i].f,r[i].t),//连接
			k++,//记数
			ans=r[i].w;//记录答案
	}
	printf("%d",ans);//输出
	return 0;//结束
}

void contact(int a,int b){
	int ra=find(a),rb=find(b);
	if(ra!=rb)
		ID[rb]=ra;
	return;
}

bool search(int a,int b){
	return find(a)==find(b);
}

int find(int x){
	if(ID[x]==x)
		return x;
	else
		return ID[x]=find(ID[x]);
}
```

---

## 作者：ysner (赞：0)

发现楼下的神犇用的都是Kruskal算法，我就给大家另一种思路：Prim算法（求最小生成树的另一种方法）。

首先，这道题是个裸的最小生成树模板题，与模板的唯一差别是：模板求的是最小生成树的各边的长度之和，而这道题求的是最小生成树的边的最大权。

但是，虽然说这道题可以用Prim算法，但它的效率在这里比Kruskal算法差太多了（笔者跑两个算法，前者1266ms,后者16ms），所以我还是建议大家用Kruskal算法，我的程序只代表另一种思路。

Prim算法很适合于点密集的图，适合采用邻接表的储存方式。而在边越少的情况下，Kruskal算法相对Prim算法的优势就越大。同时，因为边集数组便于维护，所以Kruskal在数据维护方面也较为简单，不像邻接表那样复杂。从一定意义上来说，Kruskal算法的速度与点数无关，因此对于稀疏图可以采用Kruskal算法。

模板程序改一句话即可A此题（既然是模板就不用解释了吧）：

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define fp(i,a,b) for(i=a;i<=b;i++)
#define fq(i,a,b) for(i=a;i>=b;i--)
#define il inline
#define re register
#define ll long long 
using namespace std;
int map[5005][5005]={},dis[100005]={};
bool vis[100005]={};
il int gi()//读入优化
{
  re int x=0;
  re short int t=1;
  re char ch=getchar();
  while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
  if(ch=='-') t=-1,ch=getchar();
  while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
  return x*t;
}
int main()
{
  re int i,j,k,n,m,x,y,z,ans=0;
  memset(map,0x3f3f3f,sizeof(map));//这是给数组赋极大值的好方法
  n=gi();m=gi();
  fp(i,1,m)
  {
    x=gi();y=gi();z=gi();
    if(z<map[x][y]) map[x][y]=z,map[y][x]=z;
  }
  memset(dis,0x3f3f3f,sizeof(dis));
  fp(i,1,n) vis[i]=1;
  dis[1]=0;
  fp(i,1,n)
  {
    k=0;
    fp(j,1,n) if(vis[j]==1&&(dis[j]<dis[k])) k=j;
    vis[k]=0;
    fp(j,1,n) if(vis[j]==1&&(map[k][j]<dis[j])) dis[j]=map[k][j];
  }
  fp(i,1,n) ans=max(ans,dis[i]);//把求各边长度之和改为求边的最大长度
  printf("%d\n",ans);
  return 0;
}
```

---

## 作者：封癫 (赞：0)

裸的最小生成树模板

将所有的边存在一个数组中，按长度排好序，然后一个一个比对

如果发现有一条边的起点和终点没连接，就合并他们的集合，并让ans=这条边的长度

因为是按照长度从小到大排好序，所以根本不需要判断，最后一个赋值给ans的长度肯定是最长的

当连接的边数到达n-1的时候退出循环并输出ans

这题就做完了

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<iostream>
template <typename T>
T read(){
    T num=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')    f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        num=num\*10+ch-'0';
        ch=getchar();
    }
    return num\*f;
}
#define read()    read<long long>()
struct Edge{
    int from;
    int to;
    int dis;
}edge[500000];
int father[500000];
int find(int x){
    if(father[x]!=x)    father[x]=find(father[x]);
    return father[x];
}

void unionn(int x,int y){
    x=find(x);y=find(y);
    father[y]=x;
}
using namespace std;

bool cmp(Edge a,Edge b)    {    return a.dis<b.dis;    }
int main(){
    int n=read(),m=read();
    for(int i=1;i<=n;++i){
        father[i]=i;
    }
    for(int i=1;i<=m;++i){
        edge[i].from=read();
        edge[i].to=read();
        edge[i].dis=read();
    }
    sort(edge+1,edge+m+1,cmp);
    int tot=0,ans=0;
    for(int i=1;i<=m;++i){
        if(find(edge[i].from)!=find(edge[i].to)){
            unionn(edge[i].from,edge[i].to);
            tot++;
            ans=edge[i].dis;
            if(tot==n-1)    break;
        }
    }
    printf("%d",ans);
    return 0;
}

---

## 作者：PTC06 (赞：0)

做完了P3366 之后立刻来做这题了...和3366没多大差别。

我用的是Kruskal算法。

思路：

首先，读入n和m.

然后读入m个道路分别连接了哪里与哪里，以及这条路的长度。

将这些道路以长度进行排序。

然后用一个while循环，判断如果有两条边是不连通的，就将它们进行合并，并且判断是不是最大的。（其实不用判断也可以，因为这个数组已经是有序的了，最后一个必定是最大的）

输出最长的那条边。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,ans,pre[20005],f;
struct pt              //定义一个结构体，方便下面快排
{
    int pnt1;
    int pnt2;
    int length;
} a[200100];            //定义数组a，存那m条边的信息。
bool cmp(pt x, pt y)
{
    return x.length<y.length;
}
int sch(int x)                  //搜索祖先。这是并查集的一个重要部分，不会的可以自己上网百度。网上有很多相关信息
{
    if (pre[x]==x) return pre[x];
    pre[x]=sch(pre[x]);
    return pre[x];
}
int main()
{
    cin>>n>>m;
    for (i=1;i<=m;i++)
    {
        cin>>a[i].pnt1>>a[i].pnt2>>a[i].length;        //输入每条道路的长，以及它连接了哪里跟哪里
    }
    for (i=1;i<=n;i++) pre[i]=i;             //初始化
    sort(a+1,a+m+1,cmp);                 //快排
    i=0;
    while (f<n-1)                             //还没有生成完就继续
    {
        i++;
        if (sch(a[i].pnt1)!=sch(a[i].pnt2))            //如果这个道路的头和尾没有道路连接
        {
            pre[sch(a[i].pnt1)]=sch(a[i].pnt2);      //就连接起来
            if (ans<a[i].length) ans=a[i].length;        //并且找最大的边
            f++;                        //不要忘了
        }
    }
    cout<<ans;          //输出
}
```

---

## 作者：co_step (赞：0)

##最小生成树，Kruskal，用记录类型，排序之后当s=n-1时的边就是最大边##

var
  n,m,i,s:longint;

a:array[0..10000] of record

```cpp
    u,v,w:longint;
  end; //定义一个记录类型的数组，表示边
  f:array[1..2000] of longint; //并查集数组
procedure qsort(l,r:longint);
  var
    i,j,x:longint;
  begin
    x:=a[(l+r) shr 1].w; //位运算，优化
    i:=l;
    j:=r;
    repeat
      while a[i].w<x do
        inc(i);
      while a[j].w>x do
        dec(j);
      if i<=j then
        begin
          a[0]:=a[i];
          a[i]:=a[j];
          a[j]:=a[0]; //用记录类型的原因，同类型可以互相赋值
          inc(i);
          dec(j);
        end;
    until i>j;
    if l<j then
      qsort(l,j);
    if i<r then
      qsort(i,r);
  end; //快速排序
function find(x:longint):longint; //返回集合标示
  begin
    if f[x]=0 then
      exit(x);
    f[x]:=find(f[x]);
    exit(f[x]);
  end;
begin
  readln(n,m);
  for i:=1 to m do
    readln(a[i].u,a[i].v,a[i].w); //读入边
  qsort(1,m); //排序边
  for i:=1 to m do
    if find(a[i].u)<>find(a[i].v) then //如果它们没有联通
      begin
        inc(s); //增加一条边
        if s=n-1 then //如果s=n-1，就表示最小生成树已经构建完毕，此时边的权值就是最大的权值
          begin
            writeln(a[i].w);
            exit;
          end;
        f[find(a[i].u)]:=find(a[i].v); //合并两个集合
      end;
end.

```

---

## 作者：NaVi_Awson (赞：0)

克鲁斯卡尔算法：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
 using namespace std;
struct tt
{
    int from,to,cost;
}a[10005];
int father[2005];
int k,n;
int  find(int x)
{
    if (father[x]==0) return x;
    return find(father[x]);
}
bool comp(tt a,tt b)
{
    return a.cost<b.cost;
}
int main()
{
    cin>>n>>k;
    for (int i=1;i<=k;i++)
        scanf("%d%d%d",&a[i].from,&a[i].to,&a[i].cost);
    sort(a+1,a+k+1,comp);
    int i=1,re=1;
    while(i<n)
    {
        int p=find(a[re].from);
        int q=find(a[re].to);
        if (p!=q)
        {
            i++;
            father[p]=q;
        }
        re++;
    }
    cout<<a[re-1].cost<<endl;
    return 0;
}
```

---

## 作者：汇文客 (赞：0)

标准的克鲁斯卡尔算法。贴上模板。

```delphi

var a,b,c,f:array[1..10000]of longint;
    n,m,i,ans:longint;
procedure swap(var p,q:longint);
var t:longint;
begin
  t:=p;
  p:=q;
  q:=t;
end;

procedure qsort(l,r:longint);
var mid,i,j:longint;
begin
  i:=l;j:=r;
  mid:=c[(l+r)div 2];
  repeat
  while c[i]<mid do inc(i);
  while mid<c[j] do dec(j);
  if i<=j then
  begin
    swap(a[i],a[j]);
    swap(b[i],b[j]);
    swap(c[i],c[j]);
    inc(i);dec(j);
  end;
  until i>j;
  if l<j then qsort(l,j);
  if i<r then qsort(i,r);
end;

function get(x:longint):longint;
begin
  if f[x]=x then exit(x);
  f[x]:=get(f[x]);
  exit(f[x]);
end;

procedure union(i:longint);
begin
  if get(a[i])<>get(b[i]) then
  f[get(a[i])]:=b[i];
end;

begin
  readln(n,m);
  for i:=1 to n do f[i]:=i;
  for i:=1 to m do readln(a[i],b[i],c[i]);
  qsort(1,m);
  for i:=1 to m do
  begin
    if get(a[i])=get(b[i]) then continue;
    union(i);
    ans:=c[i];
  end;
  writeln(ans);
end.

```

---

## 作者：courage (赞：0)

只要生成最小生成树再扫一遍就可以了。

采用kruskal算法，该算法思路如下：将所有边按从小到大排序(用快排），每遇到一条边就判断端点是不是在同一个连通块里面（用并查集判断），如果不是则将这条边加入集合。扫完得到的集合就是最小生成树。


```cpp

#include<cstdio>
#include<algorithm>
int f[2010],n,m,ans;
struct rec{int x,y,z;};
rec a[10010];
bool cmp(rec a,rec b){
    return (a.z<b.z);
}
int father(int x){
    if (x==f[x]) return x;
    f[x]=father(f[x]);
    return f[x];
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) f[i]=i;
    for (int i=1;i<=m;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
    std::sort(a+1,a+m+1,cmp);
    ans=0;
    for (int i=1;i<=m;i++) if (father(a[i].x)!=father(a[i].y)){
        f[father(a[i].x)]=father(a[i].y);
        if (ans<a[i].z) ans=a[i].z;
    }
    printf("%d",ans);
}

```

---

## 作者：兴安黑熊 (赞：0)

本题并查集+克鲁斯卡尔就可以了，问题在于a点到b点可以有很多条边，所以我先用2维数组进行输入，然后输入后就对比a点到b点的权值，保证vis[a][b]是最小的权值，然后把v这个2维数组中的值导入到结构体数组中，排序，记录最大边值就可以了。
另外本题用优先队列肯定也是可以的，把输入的值都压入队列，然后出队列，用vis[i][j]数组记录a点到b点是否使用过，没使用的话才可以进行并查集处理，然后标记为使用过即可；
下面为sort的代码：
```cpp
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
int a[200001];
int find(int x)
{
    if (x!=a[x])
       a[x]=find(a[x]);
    return a[x];

}
int join(int x,int y)
{
    int x1=find(x);
    int y1=find(y);
    if (x1!=y1)
       {a[y1]=x1;
        return 1;
       }
    return 0;

}
struct sa
{
    int a;
    int b;
    int dis;
}v[10001];
int cmp(const sa &a1,const sa &b1)
{
    return a1.dis<b1.dis;
}
int vis[2001][2001];
const int inf=0x3f3f3f3f;
int main()
{
   memset(vis,inf,sizeof(vis));
   int n,m,ai,bi,vi,num,k=0;
   cin>>n>>m;
   for(int i=1;i<=m;i++)
   {
       cin>>ai>>bi>>vi;
       if (vis[ai][bi]>vi) vis[ai][bi]=vi;

   }
   num=0;
   for(int i=1;i<=n;i++)
    a[i]=i;
   for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
      {
         if (vis[i][j]!=inf)
         {v[num].a=i;
          v[num].b=j;
          v[num].dis=vis[i][j];
          num++;
         }
      }
     sort(v,v+num,cmp);
     int ans=0;
     for(int i=0;i<num;i++)
     {
         if (join(v[i].a,v[i].b)==1)
           {
               if (ans<v[i].dis) ans=v[i].dis;
               k++;
           }

         if (k==n-1) break;
     }

    cout<<ans<<endl;


    return 0;
}

```

---

## 作者：stephen→_→ (赞：0)

//纯手打最小生成树(是因为我还不怎么喜欢用各种头文件^.^)

```cpp
#include<iostream>
using namespace std;
long long n,m,b=0,fa[999999],ans=0,j,v=0;
struct fg{//这里运用到结构体
    long long h;//存起始点
    long long t;//存终止点
    long long len;//存起始点到终止点的权值
};
fg a[999999];
void sort(int l,int r)//把权值从小到大排序
{
    int i,j,x,t=0;
    i=l;j=r;x=a[(l+r)/2].len;
    while(i<j)
    {
        while(a[i].len<x) i++;
        while(a[j].len>x) j--;
        if(i<=j) 
        {
            b=a[i].len;
            a[i].len=a[j].len;
            a[j].len=b;
            b=a[i].h;
            a[i].h=a[j].h;
            a[j].h=b;
            b=a[i].t;
            a[i].t=a[j].t;
            a[j].t=b;
            i++;
            j--;
        }
    }
    if(i<r) sort(i,r);
    if(l<j) sort(l,j);
}
int find(int k)//这里运用并查集来合并树，还外加了个路径压缩
{
    int kk=k;
    while (fa[kk]!=kk)
        kk=fa[kk];
    int i;
    while (fa[k]!=k)
    {
        i=k;
        k=fa[k];
        fa[i]=kk;
    }
    return kk;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)//初始化父亲节点数组
    fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i].h>>a[i].t>>a[i].len;//读入
    }
    sort(1,m);//排序
    j=1;
    while (j<=m)//枚举第一条边到第m条边
    {
        if(find(a[j].h)!=find(a[j].t))//判断两个节点是否连接
        {
            fa[find(a[j].t)]=find(a[j].h);//合并这两个节点为一棵树
            v++;//这里统计已生成的边数，一旦生成n-1条边就说明已经形成了一棵最小生成树了；
            ans=a[j].len;//数据已经排好序，所以可以直接把最长边保存进ans里
            if (v==n-1) break;//如果生成n-1条边就跳出循环
        }
        j++;
    }
    cout<<ans;//输出
    return 0;
}
//看了楼下的大佬们，感觉自己的代码不是最好的，但是觉得自己解释的一定是最好的（^.^）,最后祝大家AC顺利
```

---

## 作者：SAILING (赞：0)

只要生成最小生成树再扫一遍就可以了。

采用kruskal算法，该算法思路如下：将所有边按从小到大排序(用快排），每遇到一条边就判断端点是不是在同一个连通块里面（用并查集判断），如果不是则将这条边加入集合。扫完得到的集合就是最小生成树。


```cpp

#include<cstdio>
#include<algorithm>
int f[2010],n,m,ans;
struct rec{int x,y,z;};
rec a[10010];
bool cmp(rec a,rec b){
    return (a.z<b.z);
}
int father(int x){
    if (x==f[x]) return x;
    f[x]=father(f[x]);
    return f[x];
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) f[i]=i;
    for (int i=1;i<=m;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
    std::sort(a+1,a+m+1,cmp);
    ans=0;
    for (int i=1;i<=m;i++) if (father(a[i].x)!=father(a[i].y)){
        f[father(a[i].x)]=father(a[i].y);
        if (ans<a[i].z) ans=a[i].z;
    }
    printf("%d",ans);
}

```
补充一份PASCAL代码

  
  
```cpp
var   
    i,j,k,sum,ans,n,m:longint;  
    f:array[1..2000] of longint;  
    a,b,l:array[1..10000] of longint;
procedure sort(x,y:longint);  
var  
    z,i,j,mid:longint;  
begin   
   i:=x;j:=y;mid:=l[(x+y) div 2];  
   repeat   
        while l[i]<mid do inc(i);  
        while l[j]>mid do dec(j);  
        if not(i>j) then begin  
            z:=l[i];l[i]:=l[j];l[j]:=z;  
            z:=a[i];a[i]:=a[j];a[j]:=z;  
            z:=b[i];b[i]:=b[j];b[j]:=z;  
            inc(i);  
            dec(j);  
        end;  
   until i>j;  
   if x<j then sort(x,j);  
   if i<y then sort(i,y);  
end;  
function find(x:longint):longint;  
begin   
    if f[x]=x then exit(x);  
    f[x]:=find(f[x]);  
    exit(f[x]);  
end;  
begin   
    readln(n,m);  
    for i:=1 to m do  
        readln(a[i],b[i],l[i]);  
    sort(1,m);j:=1;ans:=0;  
    for i:=1 to n do f[i]:=i;  
    for i:=1 to n-1 do begin    
        while f[find(a[j])]=find(b[j])do inc(j);  
        f[find(a[j])]:=find(b[j]);  
        if ans<l[j] then ans:=l[j];  
    end;  
    writeln(ans);  
end.
```

---

