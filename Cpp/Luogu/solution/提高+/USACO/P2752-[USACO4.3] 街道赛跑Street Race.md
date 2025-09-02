# [USACO4.3] 街道赛跑Street Race

## 题目描述

图一表示一次街道赛跑的跑道。可以看出有一些路口（用 $0$ 到 $N$ 的整数标号），和连接这些路口的箭头。路口 $0$ 是跑道的起点，路口 $N$ 是跑道的终点。箭头表示单行道。运动员们可以顺着街道从一个路口移动到另一个路口（只能按照箭头所指的方向）。当运动员处于路口位置时，他可以选择任意一条由这个路口引出的街道。

 ![](https://cdn.luogu.com.cn/upload/pic/1967.png) 

图一：有 $10$ 个路口的街道

一个良好的跑道具有如下几个特点：

1. 每一个路口都可以由起点到达。
2. 从任意一个路口都可以到达终点。
3. 终点不通往任何路口。

运动员不必经过所有的路口来完成比赛。有些路口却是选择任意一条路线都必须到达的（称为“不可避免”的）。在上面的例子中，这些路口是 $0$，$3$，$6$，$9$。对于给出的良好的跑道，你的程序要确定“不可避免”的路口的集合，不包括起点和终点。

假设比赛要分两天进行。为了达到这个目的，原来的跑道必须分为两个跑道，每天使用一个跑道。第一天，起点为路口 $0$，终点为一个“中间路口”；第二天，起点是那个中间路口，而终点为路口 $N$。对于给出的良好的跑道，你的程序要确定“中间路口”的集合。如果良好的跑道 $C$ 可以被路口 $S$ 分成两部分，这两部分都是良好的，并且 $S$ 不同于起点也不同于终点，同时被分割的两个部分满足下列条件：（1）它们之间没有共同的街道（2）$S$ 为它们唯一的公共点，并且 $S$ 作为其中一个的终点和另外一个的起点。那么我们称 $S$ 为“中间路口 ”。在例子中只有路口 $3$ 是中间路口。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 4.3


## 样例 #1

### 输入

```
1 2 -2
3 -2
3 -2
5 4 -2
6 4 -2
6 -2
7 8 -2
9 -2
5 9 -2
-2
-1```

### 输出

```
2 3 6
1 3```

# 题解

## 作者：BJpers2 (赞：10)

看楼下大佬们代码及其长，我这里提供一种更简洁的写法，不过思想大同小异。

主要分两步。

首先起点bfs一波，看i是不是必经点。

然后不用再搜索了，因为第一张子图的点集已确定，第二张子图的也就显而易见，遍历这个点集，假如有连向起点子图的就不满足。

```cpp
#include<iostream>
#include<cstdio>
#define N 100
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,x,u,g[N][N],in[N],l,r,q[N],ans[N],mus[N],yes;
int main(){
	scanf("%d",&x);
	while(x!=-1){
		while(x!=-2 && x!=-1) g[n][x]=1,scanf("%d",&x);
		scanf("%d",&x),n++;
	}n--,in[0]=1;
	FOR(i,1,n-1){
		FOR(v,1,n) in[v]=0;
	    l=1,r=2;
	    while(l<r){
		    u=q[l++];
		    FOR(v,0,n) if(g[u][v] && in[v]==0 && v!=i)
			    in[v]=1,q[r++]=v;
	    }if(in[n]==0){
			mus[++mus[0]]=i,yes=1;
			FOR(v,0,n)if(!in[v])
			FOR(w,0,n)if(g[v][w] && in[w]) yes=0;
			if(yes) ans[++ans[0]]=i;
		}
	}
	FOR(i,0,mus[0]) printf("%d ",mus[i]);printf("\n");
	FOR(i,0,ans[0]) printf("%d ",ans[i]);
}```

---

## 作者：_unknown_ (赞：4)

先看数据范围，比较小，50,100，暴力没问题。前一个任务为后一个做铺垫。
任务1：必经点，枚举去掉的每一个点，从起点bfs，若不能能到达终点，则为必经点。
任务2：分裂点，根据题目分析，分裂点一定属于必经点，那么枚举已经求的必经点i，先从起点BFS，能到达的点在vis数组标记，再从必经点进行BFS，能到达的点在vst数组标记，
检验每一个点，（**除去当前枚举的点i**（这个很重要），若不存任何在一个点在vst和vis数组被标记，那么当前枚举的i为分裂点
上代码
```c
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<cmath>
#include<string>
#include<algorithm>
using namespace std;
int cntb,cntf,ansf[1005],ansb[1005],x,n,g[105][105],vis[1005],head[1005],he,ta,vst[1005];
int main()
{
	scanf("%d",&x);
	while(x!=-1){
		while(x!=-1&&x!=-2) {
			g[n][x]=1;
			scanf("%d",&x);
		}	
		scanf("%d",&x);
		n++;
	}
	n--; 
    //读入数据
	for(int i=1;i<=n-1;i++)
	{//枚举必经点
		memset(vis,0,sizeof(vis));
		vis[0]=1,vis[i]=1;
		he=1,ta=1;
		head[he]=0;
		while(he<=ta)
		{
			int k=head[he];
			he++;
			for(int z=1;z<=n;z++)
			{
				if(g[k][z]==1&&vis[z]==0)
				{
					vis[z]=1;
					head[++ta]=z;
				}
			}
		}
		if(vis[n]==0)
		{
			ansb[++cntb]=i;
		}
	}
	cout<<cntb<<" ";
	for(int i=1;i<=cntb;i++)printf("%d ",ansb[i]);
	printf("\n");
	memset(vis,0,sizeof(vis));
	he=1,ta=1;
	head[he]=0;
	vis[0]=1;
	while(he<=ta)
	{
		int k=head[he];
		he++;
		for(int z=1;z<=n;z++)
		{
			if(g[k][z]&&!vis[z])
			{
				vis[z]=1;
				head[++ta]=z;
			}
		}
	}
	for(int a=1;a<=cntb;a++)
	{//在必经点中枚举分裂点
		int i=ansb[a];
		memset(vst,0,sizeof(vst));
		memset(vis,0,sizeof(vis));
        //初始化
        //从起点bfs
		vis[i]=1;
		vis[0]=1;
		he=1,ta=1;
		head[1]=0;
		while(he<=ta)
		{
			int k=head[he];
			he++;
			for(int z=1;z<=n;z++)
			{
				if(g[k][z]&&!vis[z])
				{
					vis[z]=1;
					head[++ta]=z;
				}
			}
		}
        //从i点bfs
		he=1,ta=1;
		head[1]=i;
		
		while(he<=ta)
		{
			int k=head[he];
			he++;
			for(int z=0;z<=n;z++)
			{
				if(g[k][z]&&!vst[z])
				{
					vst[z]=1;
					head[++ta]=z;
				}
			}
		}
		int bj=1;
		for(int s=0;s<=n;s++)
		{
			if(vis[s]&&vst[s]&&s!=i)
			{
				bj=0;
				break;
			}
		}	
		if(bj)
		{
			ansf[++cntf]=i;
		}
	}
	cout<<cntf<<" ";
	for(int i=1;i<=cntf;i++)
	printf("%d ",ansf[i]);
	return 0;
}

```

---

## 作者：Hydra_ (赞：2)

## 分析 ##

这道题目是有向图dfs遍历的终极版本了！！！首先我们要想如何保存这个有向图。虽然邻接表的确功能和优点很强大，但是这道题目50个点，100条边还是邻接矩阵好写多了。在练习邻接表的时候别忘记练习下邻接矩阵哦。


这道题目分两问，第一问其实很好做，怎么去搜索“不可避免的点”呢，只要把从这个点出发的所有边都标记为不通，然后再去看是不是所有点都被遍历了就可以了。

第二问的答案一定都包含在第一问的答案里面。所以我们可以直接搜索第一问的答案。从第一问的答案的那个点开始遍历，看那个点之前的点有没有被遍历到就可以了。

## 代码 ##


```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y=0;
bool a[60][60],b[60][60],f[60]; 
int ans[60]={};int n=0,nn=0;
int fl[60]={};
以上是变量说明部分，a数组，用来读入数据。
b数组是个替死鬼，用来做第一题的。
f数组用来判断该点有没有遍历过。
ans数组用来存第一问的答案，n用来存第一问有多少个答案
fl数组用来存第二问的答案，nn用来存第二问有多少个答案
void print()
{
    printf("%d ",n);
    for(int i=1;i<=n;i++)
    printf("%d ",ans[i]);
    printf("\n");
    
    printf("%d ",nn);
    for(int i=1;i<=nn;i++)
    printf("%d ",fl[i]);
}
打印输出解。
void read()
{
    memset(a,false,sizeof(a));
    //邻接矩阵初始化代表没有边 
    //y用来记录当前是第几个点
    //x用来记录第y个点能通道哪几个点 
    while(scanf("%d",&x)==1)
    {
        if(x==-1)break;//跳出循环 
        if(x==-2)//如果是2 
        {
            y++; 
            continue;//下一次循环 
        }
        a[y][x]=true;//y到x有边。 
    }
    //不解释，读入。
    y--;
}
读入数据哈。
void dfs(int k)
{
    f[k]=false;
    for(int i=0;i<=y;i++)
    if(f[i]&&b[k][i])
    dfs(i);
}
第一问的深度优先遍历
void work1()
{
    for(int i=1;i<=y-1;i++)
    //起点和终点是不用搜索的。 
    {
        memset(f,true,sizeof(f));
        //标记每一个点都没有到达过 
        for(int j=0;j<=y;j++)
        for(int k=0;k<=y;k++)
        b[j][k]=a[j][k];
        //复制a矩阵 ,用b矩阵进行操作 
        for(int j=0;j<=y;j++)
        b[i][j]=false;
        //关于点i的边全部删去 
        dfs(0);
        f[0]=false; 
        //深度优先遍历 
        if(f[y])
        ans[++n]=i;
        //如果终点没有被访问，就记录i
    }
}
第一问的work函数。
void dfs2(int k)
{
    f[k]=true;
    for(int i=0;i<=y-1;i++)
    if(!f[i]&&a[k][i])
    dfs2(i);
}
第二问的深度优先遍历
void work2()
{
//从第一问的答案中搜索
    for(int i=1;i<=n;i++)
    {
                    memset(f,false,sizeof(f));
        dfs2(ans[i]);
        //从答案中开始遍历
        bool flag=true;
        for(int j=0;j<=ans[i]-1;j++)
        if(f[j])flag=false;
        //如果遍历到了，就说明有逆向边（顺的边在第一问就全部排除了。）
        if(flag)fl[++nn]=ans[i];
    }
}
第二问的work函数
int main()
{
    read();//读入 
    work1();//做第一问
    work2();//做第二问
    print();//输出
    return 0;
}
```
## 检讨 ##

这道题目我整过了一天半。错误是一个深度优先遍历的dfs2写成了dfs。我去。得做俯卧撑了。


---

## 作者：key_rA9 (赞：1)

### 算法：广度优先搜索
### 思路：
这道题有两个问，第二个建立在第一个基础上。  
①显然，枚举每个点设为不能走，bfs能否从起点到达终点，不能 就是必经之点。  
②其实题目条件中都是说分割成的两图不能有交集(即不能从一个图到另一个图)。所以这个点一定是必经之点，并且左图必然无法到达右图，剩下就是判断是否能从右到左。  
其实在第一问的bfs中，我们的判重数组可以派上用场。我们设v[i]为这个数组，则如果是必经之点，这里面被标记的点一定是左图中的所有点。这样的话，只需从必经之点开始，遍历能到的点(判重数组另开)，如果找到左图的点(当前必经之点不算)就不是第二个问的答案，否则反之。  
然后，易证两边肯定是良好的图。  
### 代码：
~~(假的说不定不能AC)~~
```cpp
#include<cstdio>
#include<cstring>
#define mes(x,y) memset(x,y,sizeof(x))
using namespace std;
inline int qr()
{
    int x=0,f=1;char c=getchar();
    while(c<'0'||'9'<c){c^'-'?1:f=-1;c=getchar();}
    while('0'<=c&&c<='9'){x=x*10+(c&15);c=getchar();}
    return x*f;
}
struct edge//边目录
{
    int y,next;
}a[110];int len,last[60];
int n,ans1[60],ans2[60];
inline void ins(int x,int y){a[++len]=(edge){y,last[x]};last[x]=len;}
int hd,tl,q[60];
bool v[60];
inline bool bfs(int del)
{
    mes(v,0);v[0]=1;
    hd=0;tl=1;q[1]=0;
    v[del]=1;
    while(hd^tl)
    {
        int x=q[++hd];
        for(int k=last[x];k;k=a[k].next)
        {
            int y=a[k].y;
            if(!v[y])
            {
                //if(y==n)return 0;
                v[y]=1;
                q[++tl]=y;
            }
        }
    }
    return !v[n];
}
bool v1[60];
inline bool bfs1(int mid)
{
	mes(v1,0);v1[mid]=1;
    hd=0,tl=1;q[1]=mid;
    while(hd^tl)
    {
        int x=q[++hd];
        for(int k=last[x];k;k=a[k].next)
        {
            int y=a[k].y;
            if(!v1[y])
            {
                if(v[y])return 0;
                v1[y]=1;
                q[++tl]=y;
            }
        }
    }
    return 1;
}
int main()
{
    for(int T=qr();T^(-2);T=qr())//输入时终点只有一个-2
    {
        ins(n,T);
        for(int t=qr();t^(-2);t=qr())
			if(n^t)ins(n,t);//自连边不管，好像没大关系
        n++;
    }
    for(int i=1;i<n;i++)
        if(bfs(i))//第一问
		{
			ans1[++ans1[0]]=i;
        	if(bfs1(i))ans2[++ans2[0]]=i;//第二问
		}
    printf("%d ",ans1[0]);
    for(int i=1;i<=ans1[0];i++)printf("%d ",ans1[i]);
    puts("");
    printf("%d ",ans2[0]);
    for(int i=1;i<=ans2[0];i++)printf("%d ",ans2[i]);
    return 0;
}
```

---

## 作者：Celebrate (赞：1)

第一问：

算法：深搜

枚举每一个点，判断从起点到终点不经过这一个点是否可以

如果不可以到达，就选择着一个点

第二问：

算法：宽搜（深搜也行）

枚举第一问的点，先用先标记起点出发不经过这一个的所有

点，然后从这一个点开始搜索，如果搜到了被标记的点，就

是不可以的方案

注意：

因为第二问枚举的都是必经点，所以判断“良好的图”时没有必要判断以下两个语句:

1.每一个点都可以由起点到达。

2.从任意一个点都可以到达终点。

但是我们要判断以下这个：

3.终点不通往任何点。

我比较喜欢从1开始，所以我就把全部的点的编号+1

代码如下：

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210];int len,last[110];//边 
inline void ins(int x,int y)//建边函数，模仿最短路 
{
	len++;
	a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n;
int cnt,s[110];
bool v[110],bk;
void dfs(int x)
{
	if(x==n) //如果不经过这一个点到达了n，就是不行的 
	{
		bk=false;
		return;
	}
	else
	{
		for(int k=last[x];k;k=a[k].next)//枚举边 
		{
			if(bk==false) break;//如果已经不可以了，就不要管了 
			int y=a[k].y;
			if(v[y]==true)//如果这一个点没有走过，就走这一个点，大幅度剪枝 
			{ 
				v[y]=false;//标记为不可以走 
				dfs(y);
			}
		}
	}
}
inline void bfs(int bk)//从1开始搜到bk 
{
	int x,y,head,tail,list[1100];
	head=1;tail=2;list[1]=1;
	while(head!=tail)
	{
		x=list[head];
		for(int k=last[x];k;k=a[k].next)
		{
			y=a[k].y;
			if(v[y]==true && y!=bk)
			{
				v[y]=false;//把走过的标记为不能走 
				list[tail]=y;tail++;
			}
		}
		head++;
	}
}
bool f[110];
int main()
{
	int i,x=0,y;
	while(1)//输入 
	{
		x++;
		while(1)
		{
			scanf("%d",&y);
			if(y<0) break;
			y++;ins(x,y);//建边 
		}
		if(y==-1)
		{
			x--;break;
		}
	}
	n=x;
	for(i=2;i<n;i++)//第一问 
	{
		memset(v,true,sizeof(v));v[i]=false;//假设这一个点不可以走 
		bk=true;dfs(1);//深搜，记得是从1开始的 
		if(bk==true)//记录 
		{
			cnt++;s[cnt]=i;
		}
	}
	int length=0,d[110];
	for(i=1;i<=cnt;i++)//枚举前面出现过的点 
	{
		bk=true;
		x=s[i];memset(v,true,sizeof(v));v[1]=false;bfs(s[i]);//初始化，并且搜索一次 
		for(int k=last[x];k;k=a[k].next)//判断一下 
		{
			if(v[a[k].y]==false)//如果不能满足终点不通往任何的点，也是不行的 
			{
				bk=false;break;
			}
		}
		if(bk==false) continue;//判断以下 
		int head,tail,list[1100];
		head=1;tail=2;list[1]=s[i];//还是宽搜判断 
		memset(f,true,sizeof(f));f[s[i]]=false;
		while(head!=tail)//还是用宽搜来判断是否可以 
		{
			x=list[head];
			for(int k=last[x];k;k=a[k].next)
			{
				y=a[k].y;
				if(v[y]==false){bk=false;break;}//如果从这一个点开始搜到了被标记为false的点，这也是不行的 
				if(f[y]==true)
				{
					f[y]=false;
					list[tail]=y;tail++;
				}
			}
			head++;
		}
		if(bk==true)//终于排除完了不行的 
		{
			length++;
			d[length]=s[i];
		}
	}
	printf("%d",cnt);//输出 
	for(i=1;i<=cnt;i++) printf(" %d",s[i]-1);
	printf("\n");
	printf("%d",length);
	for(i=1;i<=length;i++) printf(" %d",d[i]-1);
	printf("\n");
	return 0;
}
```

---

## 作者：zhangjianweivv (赞：1)

这道题同样也是A的特别艰难

------------
我的思路其实很简单，也就是用dfs去找。一开始没有看懂题（表示很无奈），然后就打了一个奇奇怪怪的代码。然后还在纳闷为什么样例的第一个是2，以为自己弄错了。。。后来多读了几遍才读懂：

原来2是数量！

emmm...用了**三个dfs**去找。
- 第一个dfs是找不可缺少的点的；
- 第二个dfs是标记1~第i个不可缺少的点之间所有的数的；
- 第三个dfs是看第i个不可缺少的点联通的所有点中有没有回到之前遍历过的点的点，也就是寻找那些可以当做中间点的点的。


------------

这道题其实看起来容易，做起来却没那么容易

因为其实有很多坑点，有些是对了这个点那个点就对不了，对了那个点这个点就过不了。就像现在如果我自己看到这篇题解，然后想办法打出了程序后，也有80%的可能性是A不了的：因为后来的调试改错真的很重要。

code：
```cpp
/*
ID:zhangji78
LANG:C++
TASK:race3
*/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct node
{
    int len,next[60];
    node()
    {
        len=0;memset(next,0,sizeof(next));
    }
}ss[200];bool bss,bs;
int bk[60],n,sk,a[60],len,b[60],lenb;
//其实bk数组本来是bool型的，但是后来到第二和第三个
//dfs的时候，就会有bug出现了（因为懒，所以bk数组
//重复用了）。这是bool数组的弊端：只有两个状态可以
//储存。
void dfs(int k)
{//这是第一个dfs
    if(k==n)
    {
        bs=true;
        return ;
    }
    else
    {
        for(int i=1;i<=ss[k].len;i++)
        {
            if(bk[ss[k].next[i]]==0)
            {
                bk[ss[k].next[i]]=1;
                dfs(ss[k].next[i]);
                if(bs==true)return;
                //这个剪枝一定要加，否则会超时
                bk[ss[k].next[i]]=0;
            }
        }
    }
}
void dfs1(int k)
{//第二个dfs
	bk[k]=1;
    if(k==sk){bss=true;return ;}
    else
    {
        for(int i=1;i<=ss[k].len;i++)
        {
            if(bk[ss[k].next[i]]==0)
            {
            	dfs1(ss[k].next[i]);
            	if(bss==true)return ;
			}
        }
    }
}
void dfs2(int k)
{//第三个dfs
	if(bss==false)return ;
	if(k==n)return ;
	else
	{
		for(int i=1;i<=ss[k].len;i++)
		{
			if(bk[ss[k].next[i]]==0)
			{
				bk[ss[k].next[i]]=2;
				dfs2(ss[k].next[i]);
				bk[ss[k].next[i]]=0;
			}
			else if(bk[ss[k].next[i]]==1)
            {
            	bss=false;return ;
            }
            //看这儿！看到之前说的bug了吧？
            //因为这里选的点有三种状态：
            //第一种：还未被寻找过
            //第二种：第二次dfs的时候被询问过了
            //第三种：第三次dfs的时候才被询问到
		}
	}
}
int main()
{
	//freopen("race3.in","r",stdin);
	//freopen("race3.out","w",stdout);
    int x,y=0;
    while(scanf("%d",&x)!=EOF)
    {
        if(x==-1)break;
        if(x==-2)y++;
        else ss[y].next[++ss[y].len]=x;
        //ss数组储存与它相连的每一个点及点的个数
    }
    n=y-1;
    for(int i=1;i<n;i++)
    {
        bs=false;
        memset(bk,0,sizeof(bk));
        bk[i]=1;dfs(0);
        if(bs==false)a[++len]=i;
        //a数组记录不可缺少的点
    }
    if(len!=0)
	{//这里巨坑了，一定要判断len，不然会错一个点
		printf("%d ",len);
		for(int i=1;i<len;i++)printf("%d ",a[i]);
	    printf("%d\n",a[len]);
	}
	else printf("%d\n",len);
    for(int i=1;i<=len;i++)
    {
        memset(bk,0,sizeof(bk));
        //bk数组反复用（捂脸）
        bss=false;sk=a[i];
        bk[a[i]]=2;//这个一定要放在dfs前面
        dfs1(0);
        bss=true;dfs2(sk);
        if(bss==true)b[++lenb]=a[i];
        //b数组记录可以做中间路口的点
    }
    if(lenb!=0)
    {//同上关于len的判断
	   	printf("%d ",lenb);
	    for(int i=1;i<lenb;i++)printf("%d ",b[i]);
	    printf("%d\n",b[lenb]);
	}
    else printf("%d\n",lenb);
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：1)

第一问和第二问丢一块处理

第一问：一个点一个点枚举，看去掉x点之后是否能到达终点

第二问：在第一问搜索的过程中，给x点左半部分加上t标记，然后从x点搜，搜到的部分做w标记，如果某点有t标记和w标记就不符合第二问条件

事实上在第二个搜索的过程中，可以遇到某个点有t标记和w标记就退出，然后标记，应该可以更快，但是由于数据比较水，都是0ms，所以不好比较

```cpp
/*
ID: ylx14271
PROG: buylow
LANG: C++     
*/
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int xx,yy,n,i;

int t[60],w[60];
int de;//删的那个点 

int a1[60],lla;
int b1[60],lb;

int a[60][60],la[60];
int dfs(int x)//搜去掉点x能不能到达终点n
{
    for (int j=1;j<=la[x];j++)
    {
        if (a[x][j]!=de&&t[a[x][j]]==0)
        {
            t[a[x][j]]=1;//顺便就给加t标记了
            dfs(a[x][j]);//继续搜
        }
    }
    if (t[n]==1) return 1;//n点被搜了返回1
    return 0; 
}

void dfs1(int x)//dfs做w标记
{
    for (int j=1;j<=la[x];j++)
    {
        if (w[a[x][j]]==0)
        {
            w[a[x][j]]=1;
            dfs1(a[x][j]);
        }
    }
    //if (w[n]==1) return 1;//n点被搜了返回1
}

int main()
{
    i=0;//点标号：0~n 
    while (scanf("%d",&xx)!=EOF)//读入 
    {
        if (xx==-2) continue;
        if (xx==-1) break;
        la[i]++;
        a[i][la[i]]=xx;
        while (scanf("%d",&yy)!=EOF)
        {
            if (yy==-2) break;
            la[i]++;a[i][la[i]]=yy;//连边
        } 
        i++; 
    }
    n=i;
    //n=i-1;//求出点的个数
    for (i=1;i<n;i++)
    {
        de=i;//删点i 
        memset(t,0,sizeof(t));
        t[0]=1;//t标记
        if (dfs(0)==0)//并不可以到达点n 
        {
            lla++;
            a1[lla]=i;
            
            memset(w,0,sizeof(w));
            
            dfs1(i); 
            int flag=0;
            for (int j=0;j<=n;j++) if (t[j]==1&&w[j]==1) //标记
            {
                flag=1;
                break;
            }
            if (flag==0)
            {
                lb++;
                b1[lb]=i;
            }
        }
    } 
    printf("%d",lla);//输出
    for (i=1;i<=lla;i++) printf(" %d",a1[i]);
    printf("\n%d",lb);
    for (i=1;i<=lb;i++) printf(" %d",b1[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：Ricardo_Y_Li (赞：0)

发现题解里没有人写BFS的，个人认为BFS要比DFS好写而且好理解（估计只有我这种蒟蒻才会这样想吧......）那我就来写一个BFS版本的

跟下面几位大佬的基本思路是一样的，找“不可避免路口”时把每个点取掉然后BFS一遍，检查是否能从起点到达终点，若不能到达，则取掉的这个点即为一个“不可避免路口”

然后我们依次搜索已经找到的这些“不可避免路口”，以一个“不可避免路口”为起点BFS一遍把能到达的点打上标记，再把这个“不可避免路口”取掉从起点再BFS一遍，如果这一遍的BFS能到达被标记到的点，那么这个“不可避免路口”就不是一个“中间路口”，反之，如果从起点出发的这次BFS达到的点都没有打过标记，则这个“不可避免路口”就是一个“中间路口”

总时间复杂度$O(n^2)$，像这道题这种$N \leq 50$的数据还是可以过的

实现细节看代码注释


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int maxn=60;
vector<int>g[maxn];
queue<int>q;
int n=0,cnt1=0,cnt2=0;
int a[maxn],b[maxn];
bool vis[maxn],is[maxn][maxn];

inline int read(){
    int Forca=0,Barca=1;
    char c=getchar();
    while(c<'0' || c>'9'){
        if(c=='-')
            Barca=-1;
        c=getchar();
    }
    while(c<='9' && c>='0'){
        Forca=Forca*10+(int)(c-'0');
        c=getchar();
    }
    return Forca*Barca;
}

inline bool bfs1(int x){//第一遍BFS找“不可避免路口”
    if(!q.empty()) q.pop();
    memset(vis,0,sizeof(vis));
    vis[x]=1,vis[0]=1;
    q.push(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i];
            if(!vis[v]){
                vis[v]=1;
                q.push(v);
            }
        }
    }
    if(vis[n-1]) return 1;
    else return 0;
}

inline void bfs2(int x){//第二遍BFS对“不可避免路口”能到达的点打标记
    while(!q.empty()) q.pop();
    memset(vis,0,sizeof(vis));
    vis[x]=1;
    q.push(x);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i];
            if(!vis[v]){
                q.push(v);
                vis[v]=1;
                is[x][v]=1;
            }
        }
    }
}

inline bool bfs3(int x){//第三遍BFS判断x是否为“中间路口”
    while(!q.empty()) q.pop();
    memset(vis,0,sizeof(vis));
    vis[0]=1;vis[x]=1;
    q.push(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(is[x][u]) return 0;//注意这里，要判断一下正在搜的点是否打过标记
        //之前就在这里卡了3个点卡了很久
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i];
            if(is[x][v]) return 0;//判断能到达的点是否打过标记
            if(!vis[v]){
                vis[v]=1;
                q.push(v);
            }
        }
    }
    return 1;
}

inline void work(int x){
    bfs2(x);
    if(bfs3(x)) b[++cnt2]=x;
}

int main(){
    memset(is,0,sizeof(is));
    while(1){//这道题最恶心的输入
        int x=read();
        if(x==-2){
            n++;
            continue;
        }
        if(x==-1) break;
        g[n].push_back(x);
    }
    for (int i=1;i<=n-2;i++){
        if(!bfs1(i)) a[++cnt1]=i;
    }
    sort(a+1,a+1+cnt1);
    for(int i=1;i<=cnt1;i++)
        work(a[i]);
    sort(b+1,b+cnt2+1);
    cout<<cnt1<<" ";
    for(int i=1;i<=cnt1;i++)
        cout<<a[i]<<" ";
    cout<<endl<<cnt2<<" ";
    for(int i=1;i<=cnt2;i++)
        cout<<b[i]<<" ";
    cout<<endl;
    return 0;
}
```

---

## 作者：Bzy_temp (赞：0)

/\*
一道超简单的水题n<=50,直接暴力出奇迹

\*/



```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;//流操作命名空间 
bool mp[55][55];//邻接矩阵存图 
bool gt[55];//第一遍是否 走过 
bool gt2[55];//第二遍是否走过 
int ps1[55],ps2[55],p1,p2;//答案存储及其指针 
int point=0;//地点指针 
bool dfs1(int place){
    if(gt[place])return false;//如果来过立即返回false 
    if(place==point)return true;//如果到终点则返回True 
    gt[place]=true;//标记 
    for(int i=0;i<=point;i++){
        if(mp[place][i] ){
            if(dfs1(i))return true;//如果返回true则返回True，否则继续搜 
        }
    }
    return false;//返回false 
}
//同理 
bool dfs2(int place){
    if(gt[place])return true;//第二遍搜时如果搜到第一遍搜过的地方返回true 
    if(gt2[place])return false;//搜到自己走过的地方返回False 
    gt2[place]=true;
    for(int i=0;i<=point;i++){
        if(mp[place][i]){
            if(dfs2(i))return true;
        }
    }
    return false;
}
int main(){
    //读入，不解释 
    while(1){
        int k;cin>>k;
        if(k==-1)break;
        if(k==-2)point++;
        else mp[point][k]=true;
    }
    point--;//指针转离线 
    for(int i=1;i<=point-1;i++){
        for(int j=0;j<=point;j++)gt[j]=false;gt[i]=true;
        for(int j=0;j<=point;j++)gt2[j]=false;
        //清空，因为不信任memset，所以手动清零 
        if(!dfs1(0)){//判断是否为必经点 
            ps1[p1++]=i;gt[i]=false;//赋值不解释 
            if(!dfs2(i))ps2[p2++]=i;//判断是否为中间点 
        }
    }
    cout<<p1;for(int i=0;i<=p1-1;i++)cout<<" "<<ps1[i];
    cout<<"\n"<<p2;for(int i=0;i<=p2-1;i++)cout<<" "<<ps2[i];
    //输出不解释 
    return 0;
}
```

---

## 作者：转身、已陌路 (赞：0)

这道题第一问很简单，只需要合法去掉任意一个点，然后判断图是否连通即可

第二问的求解在第一问的基础上进行  刚开始我想着的是将有向图改成无向图  后来一算发现答案会和第一问一样   所以必须要改变方法

即从第一问的答案开始遍历  如果不可避免的点后面的点与前面的点有联通  这个点就不能作为中间点

读入稍微操作一下就好

代码：

    
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[60][60];//邻接矩阵
int n;
int b[60],c[60];
int num=0,sum=0;
bool f[60];
bool flag;
void read()//读入  需要一些小操作
{
    int x;
    cin>>x;
    n=-1;
    while (x!=-1)
    {
        n++;
        while (x!=-2)
        {
        a[n][x]=1;
        cin>>x;
        }
        cin>>x;
    }
}
void dfs1(int j,int k)//第一问的遍历 将不可避免点去掉
{
    if (k==j) return;
    f[k]=true;
    for (int i=0;i<=n;i++)
        if (!f[i]&&a[k][i]) dfs1(j,i);
}
void dfs2(int k)//第二问   正常的遍历
{
    f[k]=true;
    for (int i=0;i<=n-1;i++)
        if (!f[i]&&a[k][i]) dfs2(i);
}
void work1()//第一问的解答
{
    for (int i=1;i<=n-1;i++)
    {
    memset(f,false,sizeof(f));
    dfs1(i,0);
    if (!f[n]) num++,b[num]=i;//记录不可避免点
    }
    cout<<num<<" ";
    for (int i=1;i<=num;i++) cout<<b[i]<<" ";
    cout<<endl;
}
void work2()//第二问的解答
{
    for (int i=1;i<=num;i++)
    {
    memset(f,false,sizeof(f));
    dfs2(b[i]);
    flag=true;
    for (int ii=0;ii<=b[i]-1;ii++)
    if (f[ii]) flag=false;
    if (flag) sum++,c[sum]=b[i];//记录中间点
    }
    cout<<sum<<" ";
    for (int i=1;i<=sum;i++) cout<<c[i]<<" ";
}
int main()//主程序
{
    read();
    work1();
    work2();
    return 0;
}
```

---

## 作者：0carryt0 (赞：0)

蒟蒻巨长代码，求各位神犇瞅一眼!!！

这题有俩问，我一共开了三个遍历。。。

第一问每个点搜过去，每个点认为舍去，舍掉后进行dfs，若还能达到终点，就使计数变量++，存入一个数组，输出。

第二问，大家稍微思考一下，可以发现中间路口的解的集合一定是属于上一问的解的集合的。每个点搜过去，点之前的路径经过的点若点之后路径也经过，则不成立。反之，计数变量++，存入数组输出，也是容易的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,sum=0,nn,t,s1=0,s2=0;
struct tu
{
    int xx,y,next;
}a[200];
int linkk[200];
bool b[200];
int a1[200];
int a2[200];
bool tt[200];
bool p=false;
void dfs(int x)
{
    if (x==nn) {p=true;return;}
    for(int i=linkk[x];i;i=a[i].next)
    if (!b[i])
    {
        b[i]=true;
        dfs(a[i].y);
    }
}
void read()
{
    for(nn=0;nn<=60;nn++)
    {cin>>x;
      if (x!=-1)
      {for(int j=1;j<=60;j++)
      if (x!=-2)
    {
        a[++sum].y=x;
        a[sum].xx=nn;
        a[sum].next=linkk[nn];
        linkk[nn]=sum;    
        cin>>x;
    }else break;
    }else break;}
    nn--;
}
void dfs1(int flagg,int endd)
{
    if (flagg==endd) return;
    if (flagg>nn) return;
    for(int i=linkk[flagg];i;i=a[i].next)
    if (!b[i])
    {
        tt[a[i].xx]=true;
        b[i]=true;
        dfs1(a[i].y,endd);
    }
}
void dfs2(int x)
{
    if (tt[x]) {p=false;return ;}
    for(int i=linkk[x];i;i=a[i].next)
    if (!b[i])
    {
        b[i]=true;
        dfs2(a[i].y);
    }
}
void work()
{
    for(int i=1;i<nn;i++)
      {
          p=false;
          t=linkk[i];linkk[i]=0;
          memset(b,0,sizeof(b));
          dfs(0);
          if(!p) {s1++;a1[s1]=i;}
          linkk[i]=t;
      }
      cout<<s1<<' ';
      for(int i=1;i<=s1;i++)
        {
        cout<<a1[i]<<' ';
        memset(tt,0,sizeof(tt));
        memset(b,0,sizeof(b));
        dfs1(0,a1[i]);
        memset(b,0,sizeof(b));
        p=true;
        dfs2(a1[i]);
        if (p) s2++,a2[s2]=a1[i];
           }
      cout<<endl;
      cout<<s2<<' ';
      for(int i=1;i<=s2;i++)
        cout<<a2[i]<<' ';
}
int main()
{
    read();
    work();
    //for(int i=0;i<=nn;i++)
      //cout<<tt[i]<<' ';
    return 0;
}
```

---

## 作者：Jason_Yvan (赞：0)

读入啰嗦点，

我们看题目可以发现，中间路口一定属于不可避免的点，所以只要在不可避免的点分开的两个图中判断没有其他路相连就可以了。

先暴力搜每个点找出不可避免点，接着判断两个图中没有路相连就可以了

代码有详解

C++代码:

/*************************************************************************

    > Author: wzw-cnyali
    > Created Time: 2017/4/19 19:47:11
************************************************************************/























```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
typedef unsigned long long uLL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define EREP(i, a) for(register int i = (be[a]); i != -1; i = nxt[i])
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
template <class T>
T read(T sum = 0, T fg = 0)
{
    char c = getchar();
    while(c < '0' || c > '9') { fg |= c == '-'; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return fg ? -sum : sum;
}
const int inf = 0x3f3f3f3f;
const int Size = 50;
const int maxn = 100000;
const int maxm = 100000;
int n;
vector <int> Node[Size];
bool p1[Size];
bool dfs1(int x, int End)//可以到终点返回1， 不能到终点返回1
{
    if(x == n) return true;
    p1[x] = 1;
    REP(i, 0, Node[x].size() - 1)
    {
        int y = Node[x][i];
        if(!p1[y] && y != End && dfs1(y, End))
            return true;
    }
    return false;
}
bool p2[Size];
void dfs2(int x, int End)
{
    if(x == n) return;
    p2[x] = 1;
    REP(i, 0, Node[x].size() - 1)
    {
        int y = Node[x][i];
        if(!p2[y]) dfs2(y, End);
    }
}
vector <int> ans1, ans2;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
#endif
    REP(i, 0, 50)
    {
        int x = read<int>();
        if(x == -1) break;
        n = i;
        while(x != -2)
        {
            Node[i].push_back(x);
            x = read<int>();
        }
    }
    REP(i, 1, n - 1)
    {
        mem(p1, 0);
        if(!dfs1(0, i))//搜每一个点如果可以到终点说明这不是不可避免的点
        {
            ans1.push_back((int)i);
            mem(p2, 0);
            dfs2(i, n);//把从i到终点的路标记出来
            REP(j, 0, n) if(p1[j] && p2[j] && j != i) goto CONTINUE;
            ans2.push_back((int)i);
            CONTINUE : ;
        }
    }
//输出
    printf("%d", (int)ans1.size());
    REP(i, 0, ans1.size() - 1)
    {
        printf(" %d", ans1[i]);
    }
    printf("\n%d", (int)ans2.size());
    REP(i, 0, ans2.size() - 1)
    {
        printf(" %d", ans2[i]);
    }
    puts("");
    return 0;
}

```

---

## 作者：姚文涛 (赞：0)

//分析：一道很水的图论题。第一问只要枚举把每个点删掉后用dfs判断起点能否走到终点就好了。第二问，很明显一个中间点一定满足第一问的要求，所以就在第一问找到的点中枚举就好了。

  
  
```cpp
//满足P党的需要
var  
  x,i,s,t,e1,u1,tot,n:longint;  
  a:array[1..50,0..50] of longint;  
  v:array[1..50] of boolean;  
  e,u:array[1..50] of longint;  
  flag:boolean;  
procedure dfs(x,y:longint);  
var  
  i:longint;  
begin  
  v[x]:=false;  
  inc(tot);  
  if x=t then  
  begin  
    flag:=false;  
    exit;  
  end;  
  for i:=1 to a[x,0] do  
    if (v[a[x,i]])and(a[x,i]<>y) then dfs(a[x,i],y);  
end;  
begin  
  read(x);  
  fillchar(v,sizeof(v),true);  
  while x<>-1 do  
  begin  
    inc(n);  
    if x=-2 then t:=n;  
    while x<>-2 do  
    begin  
      inc(a[n,0]);  
      a[n,a[n,0]]:=x+1;  
      v[x+1]:=false;  
      read(x);  
    end;  
    read(x);  
  end;  
  for i:=1 to n do  
    if v[i] then  
    begin  
      s:=i;  
      break;  
    end;  
  if s=0 then s:=1;  
  for i:=1 to n do  
    if (i<>s)and(i<>t) then  
    begin  
      flag:=true;  
      fillchar(v,sizeof(v),true);  
      dfs(s,i);  
      if flag then  
      begin  
        inc(u1);  
        u[u1]:=i;  
      end;  
    end;  
  write(u1);  
  for i:=1 to u1 do  
    write(' ',u[i]-1);  
  writeln;  
  for i:=1 to u1 do  
  begin  
    tot:=0;  
    fillchar(v,sizeof(v),true);  
    dfs(s,u[i]);  
    fillchar(v,sizeof(v),true);  
    dfs(u[i],0);  
    if tot=n then  
    begin  
      inc(e1);  
      e[e1]:=u[i];  
    end;  
  end;  
  write(e1);  
  for i:=1 to e1 do  
    write(' ',e[i]-1);  
  writeln;  
end.
```

---

## 作者：Skywalker_David (赞：0)

这道图论做得不太爽，因为数据范围太小了。


既然这样，就直接搜索了。第一问太水了，和我上次说的求最小环一样，我们枚举n个点，每次把它删掉并从起点遍历。如果不能到终点，它就是一个“不可避免”的点。


第二问要稍微转一下。首先我们可以知道，第二问的解集一定是属于第一问的。


设某一点P已经是“不可避免”的点。


在刚才遍历时，我已经对从起点0开始可以到达的点全部标记过了。此时我从那个点P开始遍历，开另一个数组来标记已遍历的点。倘若有个点Q同时被遍历到，说明这两个集合有边连接，就不是“中间路口”了。

```cpp
#include<stdio.h>
#include<cstring>
using namespace std;
const int maxn=51;
int num[maxn],sum[maxn],map[maxn][maxn],back[maxn][maxn];
bool that,ok1[maxn],ok2[maxn],flag[maxn],two[maxn],bre;
int n,c,del,j,i,cnt1,cnt2;
bool dfs(int k)
{
  bool o=false;
  if (k==n) return true;
  flag[k]=true;
  for (int i=1;(i<=num[k])&&(!o);i++)
  {
    int go=map[k][i];
    if (!flag[go]&&go!=del) o=dfs(go);
  }
  return o;
}
void find(int k)
{
  two[k]=true;
  for (int i=1;i<=num[k];i++)
  {
    int go=map[k][i];
    if (!two[go]) find(go);
  }
}
int main()
{
  freopen("race3.in","r",stdin);
  freopen("race3.out","w",stdout);
  bre=false;
  while (true)
  {
    while (true)
    {
      scanf("%ld",&c);
      if (c==-1) {bre=true;break;}
      if (c==-2) break;
      map[n][++num[n]]=c;
      back[c][++sum[c]]=n;
    }
    if (bre) break;
    n++;
  }
  n--;
  for (del=1;del<n;del++)
  {
    memset(flag,0,sizeof(flag));flag[0]=true;
    if (!dfs(0)) 
    {
      ok1[del]=true;cnt1++;
      memset(two,0,sizeof(two));two[n]=true;
      find(del);that=true;
      for (i=0;i<=n;i++) if (flag[i]&&two[i]) {that=false;break;}
      if (that) {ok2[del]=true;cnt2++;}
    }
  }
  if (cnt1==0) printf("0");else printf("%ld ",cnt1);
  for (i=1;(i<=n)&&(cnt1>1);i++) if (ok1[i]) {cnt1--;printf("%ld ",i);}
  for (j=n;j>0;j--) if (ok1[j]) break;if (ok1[j]) printf("%ld\n",j);else printf("\n");
  if (cnt2==0) printf("0");else printf("%ld ",cnt2);
  for (i=1;(i<=n)&&(cnt2>1);i++) if (ok2[i]) {cnt2--;printf("%ld ",i);}
  for (j=n;j>0;j--) if (ok2[j]) break;if (ok2[j]) printf("%ld\n",j);else printf("\n");
  return 0;
}
```

---

