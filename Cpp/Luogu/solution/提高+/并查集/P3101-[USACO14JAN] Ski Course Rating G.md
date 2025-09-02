# [USACO14JAN] Ski Course Rating G

## 题目描述

The cross-country skiing course at the winter Moolympics is described by an M x N grid of elevations (1 <= M,N <= 500), each elevation being in the range 0 .. 1,000,000,000.

Some of the cells in this grid are designated as starting points for the course.  The organizers of the Moolympics want to assign a difficulty rating to each starting point.  The difficulty level of a starting point P should be the minimum possible value of D such that a cow can successfully reach at least T total cells of the grid (1 <= T <= MN), if she starts at P and can only move from cell to adjacent cell if the absolute difference in elevation between the cells is at most D.  Two cells are adjacent if one is directly north, south, east, or west of the other.

Please help the organizers compute the difficulty rating for each starting point.

滑雪场用一个M\*N(1 <= M,N <= 500)的数字矩阵表示海拔高度，每个数字表示一个范围在0 .. 1,000,000,000的高度。有些格子被指定为起点，组织者想对这些起点做难度评级。


如果起点P点是一个难度级别为D的起点，则D必须是满足以下条件的一个最小值：


（1）从一个格子只能滑到相邻的格子；


（2）这两个格子的海拔差不超过D；


（3）至少能够到达T（1 <= T <= M\*N）个格子（包括起点本身）。


## 说明/提示

The ski course is described by a 3 x 5 grid of elevations.  The upper-left and lower-right cells are designated as starting points.  From each starting point, we must be able to reach at least 10 cells.


The difficulty rating of the upper-left starting point is 4, and for the lower-right it is 20.


## 样例 #1

### 输入

```
3 5 10 
20 21 18 99 5 
19 22 20 16 17 
18 17 40 60 80 
1 0 0 0 0 
0 0 0 0 0 
0 0 0 0 1 
```

### 输出

```
24 
```

# 题解

## 作者：zengxr (赞：21)

跟楼下大佬的做法都不一样

# 大致思路：
采用并查集巧妙联通

# 算法步骤：
1.先建立好图，每个点向右边点，下边点连边，权值为两者差的绝对值

2.将边权从小到大排序

3.不断加边进来，当合并的集合中点的个数>=T个，
则最新加入的边权*集合中有多少个出发点即为答案 

4.然后则集合中出发点个数清零即可

# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dx[3]={0, 1, 0}, dy[3]={0, 0, 1};
long long n, m, t;
long long cnt, tot;
long long ans;
struct node{
    long long x, y, dis;
}a[250005];
long long f[505][505];
long long father[250005],size[250005];
long long num[505][505],v[250005];
long long find(long long x)
{
  if(x!=father[x])
    father[x]=find(father[x]);
  return father[x];
}
bool cmp(node x,node y)
{
  return x.dis<y.dis;
}
int  main()
{
    for(int i=1;i<=250004;i++)
      size[i]=1,father[i]=i;
    scanf("%lld%lld%lld",&n,&m,&t);
    tot=0;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            scanf("%lld",&f[i][j]);
            tot+=1;
            num[i][j]=tot;
        }
    }
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            int flag;
            scanf("%d",&flag);
            if(flag) v[num[i][j]]=1;
            for (int k=1;k<=2;k++)
            {
                int tx=i+dx[k],ty=j+dy[k];
                if (tx<n+1&&ty<m+1) a[++cnt]=(node){num[i][j],num[tx][ty],abs(f[i][j]-f[tx][ty])};
            }
        }
    }//建图
    sort(a+1,a+1+cnt,cmp);//排序
    for(int i=1;i<=cnt;i++)//不断加边
    {
        int x=a[i].x,y=a[i].y;
        int fx=find(x), fy=find(y);
        if(fx==fy)continue;
        if (size[fx]+size[fy]>=t)
        {
            if (size[fx]<t)ans+=a[i].dis*v[fx];
            if (size[fy]<t)ans+=a[i].dis*v[fy];
        }
        if (size[fx]>size[fy]) swap(fx,fy);
        father[fx]=fy;
        size[fy]+=size[fx],v[fy]+=v[fx];
    }
    printf("%lld",ans);//输出答案
    return 0;
}

```

# 提醒：要记得开long long

---

## 作者：谦谦君子 (赞：11)

其实这题不是很难，是一个并查集很好的练手题qaq
~~虽然我为了加边调了将近1h~~
### 大体思路如下：
- 首先给滑雪场建边，给每两个点建边，在这里因为我们要使用并查集，所以要使用一个很~~easy~~的方法：二维转一维，代码：
```cpp
int get_pos(int i,int j)
{
	return (i-1)*n+j;	//显然这是很易懂的
}
```
- 然后将滑雪场分成多个集合，若x点可以滑到y点，则将y点并入x点的集合之中去。同时记录集合中点的个数，当点的个数大于等于t时即满足条件，于是答案就可以求出来了

接下来贴个并查集模板代码

```
int find(int x)
{
	if (fa[x]==x)
	{
		return x;
	}
	else
	{
		return fa[x]=find(fa[x]);
	}
}
```

## ok,最激动人心的代码来了
**不要在意开始的100行加边，可能出门磕到脑子了qaq**

先看我的最终AC去掉注释版
```cpp
/************************************************
*Author        :  Modesty
*Created Time  :  2019.09.17.00:02
*Mail          :  modestyscholarly@gmail.com
*Problem       :  SkiCourseRating
************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=500005;
const int INF=1000000000;
int m,n,t,x;
int a[maxn],fa[maxn],num[maxn],head[maxn],cnt[maxn],st_pt[maxn];
int id[505][505];
struct node
{
	int from,to,next;
	int h;
}edge[maxn];
bool cmp(node n1,node n2)
{
	return n1.h<n2.h;
}
int get_pos(int i,int j)
{
	return (i-1)*n+j;
}
int find(int x)
{
	if (fa[x]==x)
	{
		return x;
	}
	else
	{
		return fa[x]=find(fa[x]);
	}
}
signed main()
{
	cin>>m>>n>>t;
	for (int i=1;i<=m*n;i++)
	{
		fa[i]=i;
		cnt[i]=1;
	}
	int tot=0;
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
		{
			cin>>x;
			a[get_pos(i,j)]=x;
			if (i!=m)
			{
				tot++;
				edge[tot].from=get_pos(i,j);
				edge[tot].to=get_pos(i+1,j);
			}	
			if (j!=n)
			{
				tot++;
				edge[tot].from=get_pos(i,j);
				edge[tot].to=get_pos(i,j+1);
			}
		}
	}

	for (int i=1;i<=tot;i++)
	{
		int from,to;
		from=edge[i].from,to=edge[i].to;
		int dif;
		dif=abs(a[from]-a[to]);
		edge[i].h=dif;
	}
	sort(edge+1,edge+tot+1,cmp);
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
		{
			cin>>st_pt[get_pos(i,j)];
		}
	}
	int ans=0;
	for (int i=1;i<=tot;i++)
	{
		int fx=find(edge[i].from);
		int fy=find(edge[i].to);
		if (fx!=fy)
		{
			fa[fx]=fy;
			st_pt[fy]+=st_pt[fx];
			st_pt[fx]=0;
			cnt[fy]+=cnt[fx];
			cnt[fx]=0;
			if (cnt[fy]>=t)
			{
				ans+=edge[i].h*st_pt[fy];
				st_pt[fy]=0;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

原来的100行加边qaq
```cpp
/************************************************
*Author        :  Modesty
*Created Time  :  2019.09.17.00:02
*Mail          :  modestyscholarly@gmail.com
*Problem       :  SkiCourseRating
************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=500005;
const int INF=1000000000;
int m,n,t,x;
int a[maxn],fa[maxn],num[maxn],head[maxn],cnt[maxn],st_pt[maxn];
int id[505][505];
struct node
{
	int from,to,next;
	int h;
	
	bool operator <( const node &x)const
	{
		return h<x.h;
	}
	
}edge[maxn];
/*
bool cmp(node n1,node n2)
{
	return n1.h<n2.h;
}
*/
/*
void add(int x,int y)
{
	edge[++tot].next=head[x];
	edge[tot].from=x;
	edge[tot].to=y;
	head[x]=edge[tot].next;
}
*/
int get_pos(int i,int j)
{
	return (i-1)*n+j;
}
int find(int x)
{
	if (fa[x]==x)
	{
		return x;
	}
	else
	{
		return fa[x]=find(fa[x]);
	}
}
/*
bool check(int d)
{
	memset(num,0,sizeof(num));
	for (int i=1;i<=m*n;i++)
	{
		fa[i]=i;
	}
	for (int i=1;i<=tot;i++)
	{
		int from,to;
		int h;
		from=edge[i].from,to=edge[i].to,h=edge[i].h;
		if (h<=d)
		{
			fa[find(to)]=find(from);
		}
	}
	for (int i=1;i<=n*m;i++)
	{
		num[find(i)]++;
	}
	for (int i=1;i<=n*m;i++)
	{
		if (num[i]<t-1)
		{
			return false;
		}
	}
	return true;
}
*/
signed main()
{
	cin>>m>>n>>t;
	for (int i=1;i<=m*n;i++)
	{
		fa[i]=i;
		cnt[i]=1;
	}
/*	
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
		{
			cin>>x;
			a[get_pos(i,j)]=x;
			int pos=get_pos(i,j);
//			cout<<"&&&"<<pos<<" ";
			if (i==1&&j==1)
			{
				add(pos,get_pos(i+1,j));
				add(get_pos(i+1,j),pos);
				add(pos,get_pos(i,j+1));
				add(get_pos(i,j+1),pos);
			}
			else if (i==m&&j==n)
			{
				add(pos,get_pos(i-1,j));
				add(get_pos(i-1,j),pos);
				add(pos,get_pos(i,j-1));
				add(get_pos(i,j-1),pos);
			}
			else if (i==1)
			{
				add(pos,get_pos(i+1,j));
				add(get_pos(i+1,j),pos);
				add(pos,get_pos(i,j+1));
				add(get_pos(i,j+1),pos);
				add(pos,get_pos(i,j-1));
				add(get_pos(i,j-1),pos);
			}
			else if (i==m)
			{
				add(pos,get_pos(i-1,j));
				add(get_pos(i-1,j),pos);
				add(pos,get_pos(i,j-1));
				add(get_pos(i,j-1),pos);
				add(pos,get_pos(i,j+1));
				add(get_pos(i,j+1),pos);
			}
			else if (j==1)
			{
				add(pos,get_pos(i+1,j));
				add(get_pos(i+1,j),pos);
				add(pos,get_pos(i,j+1));
				add(get_pos(i,j+1),pos);
				add(pos,get_pos(i-1,j));
				add(get_pos(i-1,j),pos);
			}
			else if (j==n)
			{
				add(pos,get_pos(i-1,j));
				add(get_pos(i-1,j),pos);
				add(pos,get_pos(i,j-1));
				add(get_pos(i,j-1),pos);
				add(pos,get_pos(i+1,j));
				add(get_pos(i+1,j),pos);
			}
			else
			{
				add(pos,get_pos(i+1,j));
				add(get_pos(i+1,j),pos);
				add(pos,get_pos(i,j+1));
				add(get_pos(i,j+1),pos);
				add(pos,get_pos(i-1,j));
				add(get_pos(i-1,j),pos);
				add(pos,get_pos(i,j-1));
				add(get_pos(i,j-1),pos);
			} 
		}
//		cout<<endl;
	}
	
	
	int xxx=0;
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
		{
			xxx++;
			id[i][j]=xxx;
		}
	}
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
		{
			cin>>a[id[i][j]];
			if (i!=m)
			{
				add();
			}
		}
	}
	
*/
	int tot=0;
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
		{
			cin>>x;
			a[get_pos(i,j)]=x;
			if (i!=m)
			{
				tot++;
				edge[tot].from=get_pos(i,j);
				edge[tot].to=get_pos(i+1,j);
			}	
			if (j!=n)
			{
				tot++;
				edge[tot].from=get_pos(i,j);
				edge[tot].to=get_pos(i,j+1);
			}
		}
	}

	for (int i=1;i<=tot;i++)
	{
		int from,to;
		from=edge[i].from,to=edge[i].to;
//		cout<<"***"<<edge[i].from<<" "<<edge[i].to<<" "<<edge[i].h<<endl;
		int dif;
		dif=abs(a[from]-a[to]);
		edge[i].h=dif;
	}
	sort(edge+1,edge+tot+1);
	for (int i=1;i<=tot;i++)
	{
		//cout<<"***"<<edge[i].from<<" "<<edge[i].to<<" "<<edge[i].h<<endl;
	}
	for (int i=1;i<=m;i++)
	{
		for (int j=1;j<=n;j++)
		{
			cin>>st_pt[get_pos(i,j)];
		}
	}
	int ans=0;
	for (int i=1;i<=tot;i++)
	{
		int fx=find(edge[i].from);
		int fy=find(edge[i].to);
		if (fx!=fy)
		{
			fa[fx]=fy;
			st_pt[fy]+=st_pt[fx];
			st_pt[fx]=0;
			cnt[fy]+=cnt[fx];
			cnt[fx]=0;
			if (cnt[fy]>=t)
			{
				ans+=edge[i].h*st_pt[fy];
				st_pt[fy]=0;
			}
		}
	}
	cout<<ans<<endl;
	/*
	for (int i=1;i<=tot;i++)
	{
		int from,to;
		from=edge[i].from,to=edge[i].to;
		int dif;
//		int z1=from%n,h1=(from-z1)/n+1;
//		int z2=to%n,h2=(to-z2)/n+1; 
		dif=a[from]-a[to];
		edge[i].h=dif;
	}
	int l=-1,r=INF+1;
	int ans=0;
	while (l+1<r)
	{
		int mid=(l+r)>>1;
		bool pd=check(mid);
		if (pd==true)
		{
			r=mid;
			ans=0;
			for (int i=1;i<=m*n;i++)
			{
				if (st_pt[i]==1)
				{
					ans+=
				}
			}
		}
		else
		{
			l=mid;
		}
	}
	cout<<r<<endl;
	*/
	return 0;
}
```

# 完结散花
## 不要脸地求个赞qaq

---

## 作者：sxyugao (赞：8)

没有Pascal的题解，我来发一个，算是P党福利

（话说Pascal过的人也就2个。。）

------分割线------

**题意**

一张图有若干个起点，问从每个起点访问到K(K>=T)个格子，且访问到的格子与起点高度最大差的最小值。

**输入、输出**

详见题面~~（话说做这种题的人难道还不会吗。。）~~

**算法**

我一开始看到这种最大值最小，第一想法是二分，而且这道题算法标签的确有二分，然后就光荣的TLE了，错了至少5遍（可能有大佬的确是二分做的，希望也能发一下题解拓展一下思路）。。

然后请教了楼下两位大佬，发现并查集才是正解啊。。

把相邻的点连边，权值为两点高度差的绝对值，然后按权值从小到大排序，最后跑一遍类最小生成树就可以了。

对于更新答案，我是参考巨型方块的，所以我这篇题解主要是对他们算法的补充说明，让更多像我一样的蒟蒻看懂（雾

所以我把代码分成好几个模块，一点点讲。


以下为代码：
```cpp
type _edge=record x,y,v:longint;end;
//定义记录类型，x，y为当前边连的两个点的代号，v为权值。
//至于代号是什么，下面说。
var
n,m,k,i,j,t,tx,ty,tot:longint;
ans:int64;      //int64勿忘！！
f,size,head,next,p:array[1..250000]of longint;
//f为并查集中的父亲数组，size为当前联通块的大小。
//head，next，p是数组模拟链表，下面讲。
d:array[1..250000]of int64;
//d[i]表示代号为i的点满足题意的最小值
a:array[1..500,1..500]of longint;//初始地图
edge:array[1..500000]of _edge;   //储存边
st:array[1..500,1..500]of boolean;//判断是否为起点
procedure sort(l,r:longint);//按边权从小到大排序，C++选手可以参考另两篇题解
  var i,j:longint;x,y:_edge;
  begin
    i:=l;j:=r;x:=edge[(l+r)>>1];//x>>1就相当于x div 2
    repeat
      while edge[i].v<x.v do inc(i);
      while x.v<edge[j].v do dec(j);
      if not(i>j) then
        begin
           y:=edge[i];edge[i]:=edge[j];edge[j]:=y;
           inc(i);dec(j);
        end;
    until i>j;
    if l<j then sort(l,j);
    if i<r then sort(i,r);
  end;
//以下为get函数重载
function get(x,y:longint):longint;//第一个get函数：获得点（x,y)的代号。
  begin exit((x-1)*m+y); end;
//其实就是for i:=1 to NxM时访问的序号
function get(k:longint):longint;//第二个get函数：获得k的父亲。
  begin
    if f[k]=0 then exit(k);
    //这和平时的并查集略有不同，如果f[k]=0说明k并没有接在别的点上
    //换句话说，当f[k]=0时，k就是当前联通块的根，别的都挂在k上面。
    f[k]:=get(f[k]);
    exit(f[k]);
  end;
procedure init();//初始化，读入，这没什么好讲的。。
  begin
    read(n,m,k);
    for i:=1 to n do
      for j:=1 to m do
        read(a[i,j]);
    for i:=1 to n do
      for j:=1 to m do
        begin
          read(t);
          if t=1 then st[i,j]:=true else st[i,j]:=false;//标记起点
        end;
  end;
procedure build();//根据读入的数据建边
//题目中说是4个方向，但其实我们建边时只需要与下方和右方连边即可，因为边是双向的
//例如对于(x,y)只需连(x+1,y)，(x,y+1)，因为在(x-1,y)，(x,y-1)时已经连过边了
  begin
    for i:=1 to n do 
      for j:=1 to m do
        begin
          if i<>n then//和下方的点建边，当i=n时，原图中不存在(i+1,j)
            begin
              inc(tot);//边数加一
              edge[tot].x:=get(i,j);edge[tot].y:=get(i+1,j);
              //左边点为(i,j)的代号，右边点为(i+1,j)的代号。
              edge[tot].v:=abs(a[i,j]-a[i+1,j]);
              //权值为a[i,j]与a[i+1,j]差的绝对值
            end;
          if j<>m then//和右方的点连边，原理同上
            begin
              inc(tot);
              edge[tot].x:=get(i,j);edge[tot].y:=get(i,j+1);
              edge[tot].v:=abs(a[i,j]-a[i,j+1]);
            end;
        end;
    sort(1,tot);//按权值排序
  end;
procedure add(x,y:longint);//把y这个联通块合并到x上
  begin
    f[y]:=x;//把x联通块的父亲赋给y联通块
    inc(size[x],size[y]);//把y联通块的大小加到x联通块里
    if head[y]>0 then
      begin
        if head[x]=0 then head[x]:=head[y];
        if head[x]>0 then p[next[x]]:=head[y];
        next[x]:=next[y];
      end;
    //head相当于链表的头指针，next相当于一个指针指向的下一个节点，p为指针指向的点的代号
  end;
procedure solve();//这才是真正开始处理问题，前面那么长的铺垫233
  begin
    //初始化
    for i:=1 to n do
      for j:=1 to m do
        begin
          t:=get(i,j);//获得(i,j)的代号
          size[t]:=1;//自己一个点，联通块大小为1
          head[t]:=t;//链表头指针指向自己
          next[t]:=t;//下一个指针也指向自己
          //注意，此时的p[t]仍然为0，相当于没有下一个点
        end;
    for i:=1 to tot do//类最小生成树开始，从小到大枚举
      begin
        tx:=get(edge[i].x);ty:=get(edge[i].y);
        if tx=ty then continue;//如果当前两个点在同一个联通块则跳过
        add(tx,ty);//如果当前两个点不在同一个联通块则合并
        if size[tx]>=k then//合并后的大联通块符合题目要求了
          begin
            t:=head[tx];//沿着链表向下查找
            while t>0 do//还有下一个点
              begin
                d[t]:=edge[i].v;
                //等级为当前边的权值，因为是从小到大排序的，第一个满足要求的即为最优。
                t:=p[t];//下一个点
              end;
            head[tx]:=0;next[tx]:=0;
            //把当前联通块整个删除，只需删除头指针和下一个指针，就相当于找不到了。
            //至于为什么要这样更新，详见巨型方块的题解
          end;
      end;
  end;
procedure print();//输出，也没什么好讲的
  begin
    for i:=1 to n do
      for j:=1 to m do
        if st[i,j] then
          inc(ans,d[get(i,j)]);//如果当前点为起点，则把等级累加到ans里
    write(ans);
  end;
//接下来是华丽的主程序233
begin
init();//读入
build();//建边
solve();//解决
print();//输出
end.
```

---

## 作者：BigJoker (赞：5)

# 0x00 前言

此题需要使用并查集来解决，题目标签的二分是假的吧......

# 0x01 思路

* **建边**

此题的思路比较简单，首先建边，一个点的第一条边是它的右边那个点，第二条边是下面那个点，边的权值为两个点差的绝对值。

* **加边**

首先需要对边进行一个排序，按照边的权值从小到大排序，因为我们需要让答案尽可能的小，然后依次枚举每一条边，如果这条边的两个点已经在一个集合内了，就不需要去管。如果两个点没有在一个集合内，就需要去连接，当两个集合的数量加起来大于了 $t$ 那么就可以加答案，并且将这条边连接起来。

大致思路还是很简单，但是有十分多的细节。

# 0x02 技巧

* **数组范围**

我们观察数据

$n,m\le500$

因为我们需要用并查集来统计，所以可以把这个二维数据压缩成一维，那么点的个数就是 $n \times m$，因为每个点可以连接两条边，所以边的数组就需要开点的个数的两倍。

* **如何建边**

我们可以用一个数组来标记当前点是第几个点，用一个变量去累加当前是第几个点就可以了，由于后面加边的需要，我们要开一个用来统计当前这个集合要作为起点的个数。然后求权值就很简单了。

* **如何加边**

加边要注意的就是当两个集合的点的数量加起来大于等于 $t$ 时，需要逐次判断两个区间，为什么呢？因为如果其中一个区间点的个数已经达到了 $t$，前面已经加过了，就不用再加了，然后合并的时候就按照并查集的基本操作合并就好。

# 0x03 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define dep(i,r,l) for(int i=r;i>=l;i--)
using namespace std;
int n,m,t,tot,to,ans;
int fa[2500005];
int s[2500005];
int ma[505][505];
int bj[2500005];
int bh[505][505];
struct node{
	int x,y,f;
}a[2500005];
bool cmp(node l,node r){return l.f<r.f;}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
signed main(){
	scanf("%lld %lld %lld",&n,&m,&t);
	rep(i,1,n)
		rep(j,1,m){
			scanf("%lld",&ma[i][j]);
			tot++;
			bh[i][j]=tot;
		}
	rep(i,1,n){
		rep(j,1,m){
			int bjj;
			scanf("%lld",&bjj);
			if(bjj) bj[(i-1)*m+j]=1;
			if(j!=m){
				a[++to].f=abs(ma[i][j+1]-ma[i][j]);
				a[to].x=bh[i][j];
				a[to].y=bh[i][j+1];
			}
			if(i!=n){
				a[++to].f=abs(ma[i+1][j]-ma[i][j]);
				a[to].x=bh[i][j];
				a[to].y=bh[i+1][j];
			}		
		}
	}
	sort(a+1,a+1+to,cmp);
	rep(i,1,tot*2){
		fa[i]=i;
		s[i]=1;
	}
	rep(i,1,to){
		int x=find(a[i].x),y=find(a[i].y);
		if(x==y) continue;
		if(s[x]+s[y]>=t){
			if(s[x]<t) ans+=a[i].f*bj[x];
			if(s[y]<t) ans+=a[i].f*bj[y];
		}
		bj[x]+=bj[y];
		s[x]+=s[y];
		fa[y]=x;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：巨型方块 (赞：4)

我好菜啊，做了好长时间；

首先题目就很逗，这里的滑雪并不一定要从高处向低处滑；

所以大致方法就很明显；

我们先对相邻的点建边，权值自然就是差的绝对值；

那么我们在排序之后，一条一条把边权较小的连进来，就形成一个一个联通快；

联通块显然用并查集去搞；

当某个联通快的大小大于等于k的时候，那就把当前连通块里的没有跟新过的节点取出来，更新为当前答案；

因为边权从小到达，当前答案必然最优

然后就是我们怎么去维护一个联通快里没有被更新过的点呢？

大力模拟单项链表；


```cpp
#include<bits/stdc++.h>
#define Ll long long
#define U(i,j) ((i-1)*m+j)
using namespace std;
const int N=505;
struct cs{int x,y,v;}q[N*N*2];
int a[N][N],f[N*N],d[N*N],size[N*N],c[N*N],ct,head[N*N],last[N*N],Q[N*N];
bool need[N][N];
int n,m,k,top;
Ll ans;
bool cmp(cs a,cs b){return a.v<b.v;}
int get(int x){return f[x]?f[x]=get(f[x]):x;}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&need[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(i!=n){
                q[++top].v=abs(a[i][j]-a[i+1][j]);
                q[top].x=U(i,j);q[top].y=U(i+1,j);
            }
            if(j!=m){
                q[++top].v=abs(a[i][j]-a[i][j+1]);
                q[top].x=U(i,j);q[top].y=U(i,j+1);    
            }
        }
    sort(q+1,q+top+1,cmp);
    for(int i=1;i<=n*m;i++){
        size[i]=1;
        head[i]=i;
        last[i]=i;
    }
    for(int i=1;i<=top;i++){
        int X=get(q[i].x);
        int Y=get(q[i].y);
        if(X==Y)continue;
        f[Y]=X;size[X]+=size[Y];
        if(head[Y])
            if(!head[X]){
                head[X]=head[Y];
                last[X]=last[Y];
            }else{
                Q[last[X]]=head[Y];
                last[X]=last[Y];
            }
        if(size[X]>=k){
            for(int j=head[X];j;j=Q[j])d[j]=q[i].v;
            head[X]=last[X]=0;    
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(need[i][j])ans+=d[U(i,j)];
    printf("%lld",ans);
}
```

---

## 作者：我打 (赞：3)

**博客链接：** https://www.cnblogs.com/Laoli-2020/p/14015054.html

# Slove


**这题我们可以尝试建立一个图，以相邻的两个点建边，边的权值为两个点高度差的绝对值，然后把边按照边权值从小到大排序。**



**然后就可以愉快地使用并查集了：**


**一开始将每一个点划分到自己的集合。**

**每次枚举一条边，判断所枚举的边的两个点是否在同一个集合内，如果在就不管，不在就将这两个节点所处的集合进行合并。**

**每枚举一条边，如果发现合并后的集合点数已经不少于t个，且合并前有集合的点数小于t，如果以前这个集合里面包含终点，答案就直接加上当前边的权值就好了。**

**每次集合合并时需要合并的信息有集合大小和集合中是否含起点。**


# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct bian
{
	int a,b;
	long long c;
}s[1000000];
int cmp(bian xx1,bian xx2)
{
	if(xx1.c!=xx2.c)return xx1.c<xx2.c;
	else 
	{
		if(xx1.a!=xx2.a)return xx1.a<xx2.a;
		else return xx1.b<xx2.b;
	}
}
int m,n,t,bcj[1000000],tot=0,lll;
long long mm[1000][1000],num[1000000],siz[1000000],ans=0;
int find(int x)//并查集-找祖宗
{
	int zz;
	if(bcj[x]==x)zz=x;
	else zz=find(bcj[x]);
	bcj[x]=zz;
	return zz;
}
int main()
{
	scanf("%d%d%d",&m,&n,&t);
	for(int i=1;i<=m*n*3;i++)bcj[i]=i,siz[i]=1;//预处理
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)cin>>mm[i][j];
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			if(i!=1)s[++tot].a=(i-1)*n+j,s[tot].b=(i-2)*n+j,s[tot].c=abs(mm[i][j]-mm[i-1][j]);
			if(j!=1)s[++tot].a=(i-1)*n+j,s[tot].b=(i-1)*n+j-1,s[tot].c=abs(mm[i][j]-mm[i][j-1]);
		}
        //建边
	sort(s+1,s+tot+1,cmp);//排序
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&lll);
			if(lll==1)num[(i-1)*n+j]=1;//给起点打上标记(第i行第j列的点编号为((i-1)*n+j))
		}
	for(int i=1;i<=tot;i++)
	{
		int fa=find(s[i].a),fb=find(s[i].b);
		if(fa==fb)continue;//在同一个集合中
		if(siz[fa]+siz[fb]>=t)//判断集合是否满足条件
		{
			if(siz[fa]<t)ans+=s[i].c*num[fa];
			if(siz[fb]<t)ans+=s[i].c*num[fb];
		}
		num[fa]+=num[fb],siz[fa]+=siz[fb],bcj[fb]=fa;//合并信息
	}
	cout<<ans<<endl;

	return 0; 
}
```

---

## 作者：huyangmu (赞：3)

做这道题之前，推荐[这道题目](http://ybt.ssoier.cn:8088/problem_show.php?pid=1489)铺垫。

先看看标签，有二分，于是给了我们一个暴力思路，二分两个相邻格子的高度差 $D$，如果这个 $D$ 能够到达至少 $T$ 个格子，则比 $D$ 大的高度差肯定满足要求，如果这个高度差 $D$ 到不了 $T$ 个格子，则比 $D$ 小的高度差肯定也不满足要求，满足单调性。

二分的下界为与起点相邻的每个格子与起点高度之差绝对值的最小值，如果 $D$ 比这个值还小，就寸步难行了，上界设为一个极大值。

判断函数中需要搜索起点周围相邻的格子，如果高度差的绝对值小于等于 $D$ 就可以到达，如果能到达的格子数量等于 $T$，就直接结束搜索。

显然这种算法时间复杂度是行不通的，但可以得分。

```cpp

#include<bits/stdc++.h>
using namespace std;
const int NR = 505;
int n,m,t,a[NR][NR],p[NR][NR],sum,cnt;
bool vis[NR][NR]; 
void dfs (int x,int y,int mid){
	if (cnt>=t) return ;
	if (abs(a[x][y]-a[x-1][y])<=mid&&x-1>=1&&vis[x-1][y]==0){
		++cnt;
		vis[x-1][y]=1;
		dfs(x-1,y,mid);
	}
	if (abs(a[x][y]-a[x+1][y])<=mid&&x+1<=n&&vis[x+1][y]==0){
		++cnt;
		vis[x+1][y]=1;
		dfs(x+1,y,mid);
	}
	if (abs(a[x][y]-a[x][y-1])<=mid&&y-1>=1&&vis[x][y-1]==0){
		++cnt;
		vis[x][y-1]==1;
		dfs(x,y-1,mid);
	}
	if (abs(a[x][y]-a[x][y+1])<=mid&&y+1<=m&&vis[x][y+1]==0){
		vis[x][y+1]=1;
		++cnt;
		dfs(x,y+1,mid);
	}
}
bool check (int x,int y,int mid){
	cnt=0;
	memset(vis,0,sizeof(vis));
	dfs(x,y,mid);
	return cnt>=t;
}
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>t;
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j) cin>>a[i][j];
	}
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			cin>>p[i][j];
			if (!p[i][j]) continue;
			int l=min(abs(p[i][j]-p[i-1][j]),min(abs(p[i][j-1]-p[i][j]),min(abs(p[i+1][j]-p[i][j]),abs(p[i][j+1]-p[i][j])))),r=1e9,ans=0;
			while (l<=r){
				int mid=l+r>>1;
				if (check(i,j,mid)){
					ans=mid;
					r=mid-1;
				}else l=mid+1;				
			}
			//cout<<ans<<'\n';
			sum+=ans;
		}
	}
	cout<<sum<<'\n';
	return 0;
}
```
[评测记录](https://www.luogu.com.cn/record/138048389)

为什么二分行不通呢？原因是每个起点都要枚举一遍，大大提高了时间复杂度，所以我们把重点放在边上。

双重循环枚举每一个点，并向它的下方和右方连边，边权设为高度差的绝对值，如果往上方和左方连边会出现重边。

我们把每一个点看作一个单独的连通块，枚举每一条边，如果这条边对应的两个顶点不连通，就把这两个点对应的连通块合并。这时，如果两个连通块的点数之和达到了 $T$ 个，那这两个连通块中所有的起点对应的 $D$，就是两个连通块中所有边权的最大值。

那我们将建的 $len$ 条边排序，就可以保证满足条件的第一个 $D$，就是最终答案。

用 $siz_{i}$ 表示第 $i$ 个连通块对应的点的数量，$siz2_{i}$ 表示第 $i$ 个连通块中起点的数量。

若确定了难度 $D$，那么将 $siz_{i}$ 和 $siz2_{i}$ 清零，避免重复计算，实现过程可以用并查集处理。

```cpp

if (siz[x]+siz[y]>=t){	
				ans+=(siz2[x]+siz2[y])*b[i].w;				
				siz2[x]=0;
				siz2[y]=0;
			}
			siz[y]+=siz[x];
			siz2[y]+=siz2[x];
			siz[x]=0;
			siz2[x]=0;
```

这种算法就可以轻松过了。

```cpp

#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int NR = 505;
int n,m,t,a[NR][NR],p[NR][NR],fa[NR*NR+5],siz[NR*NR+5],siz2[NR*NR+5],len,ans;
struct node{
	int x,y,w;
}b[10*NR*NR+5];
bool cmp (node x,node y){
	return x.w<y.w;
}
int find (int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
void kruskal (){
	for (int i=1;i<=len;++i){
		int x=find(b[i].x),y=find(b[i].y);
		if (x!=y){
			fa[x]=y;
			if (siz[x]+siz[y]>=t){	
				ans+=(siz2[x]+siz2[y])*b[i].w;				
				siz2[x]=0;
				siz2[y]=0;
			}
			siz[y]+=siz[x];
			siz2[y]+=siz2[x];
			siz[x]=0;
			siz2[x]=0;
		}				
	}
	cout<<ans<<'\n';
}
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>t;
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j) cin>>a[i][j];
	}
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){		
			if (i!=n){
				++len;
				b[len].x=(i-1)*m+j;
				b[len].y=i*m+j;
				b[len].w=abs(a[i][j]-a[i+1][j]);
			}
			if (j!=m){
				++len;
				b[len].x=(i-1)*m+j;
				b[len].y=(i-1)*m+j+1;
				b[len].w=abs(a[i][j]-a[i][j+1]);
			}			
		}
	}
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			cin>>p[i][j];
			if (p[i][j]) siz2[(i-1)*m+j]=1;						
		}
	}
	for (int i=1;i<=n*m;++i) fa[i]=i;
	for (int i=1;i<=n*m;++i) siz[i]=1;
	sort(b+1,b+len+1,cmp);
	kruskal();
	return 0;
}
```

[评测记录](https://www.luogu.com.cn/record/138222222)


---

## 作者：foryou_ (赞：2)

看到这题很容易想到对于每个起点进行二分 + bfs check，但这样写显然 T 飞。

然后由此我们想到用并查集维护连通块做，

具体地，我们先建出图，令每个格子向其右、下格子连边，边权为高度绝对差，

然后将边权从小到大排序，

考虑每一条边，若其端点未被合并，则将它们合并为同一集合，

顺便维护连通块的大小 $sz_x$ 与起点个数 $v_x$，

若合并后集合大小 $\ge T$，则两边的集合中大小 $\le T$ 的，其对于答案的贡献即为 此集合的起点个数 $\times$ 当前边的边权。直接累加贡献即可。

时间复杂度 $O(MN \log MN)$。

[代码](https://www.luogu.com.cn/paste/jhx4uzl0)。非常好写。

---

## 作者：yimuhua (赞：2)

## 思路：

采用**并查集**联通

## 步骤：

1.建图，每个点向右边点，下边点连边，权值为两者差的绝对值

2.将边权从小到大排序

3.不断加边进来，当合并的集合中点的个数 $\geq T$ 个， 则最新加入的边权 $\times$ 集合中的点数即为答案

4.将集合中出发点个数清零

## AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long m, n, t, cp, ce, ans, h[505][505], s[505][505], id[505][505], fa[500005], tot[500005], ts[500005];
struct node {
    long long w, x, y;
}a[500005];
bool cmp(node a, node b) {
    return a.w < b.w;
}
int find(int x) {
    if(fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
int main() {
    cin >> m >> n >> t; //行、列、格子数量的要求
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            cin >> h[i][j]; //海拔
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            cin >> s[i][j]; //起点
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            id[i][j] = ++cp, ts[cp] = s[i][j]; //二维降一维编号， cp是点的数量
    //ts表示当前集合起点数量，每个编号的点初始化为一个集合
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++) {
            if(i != m) //向下建边
                ce++, a[ce].x = id[i][j], a[ce].y = id[i + 1][j], a[ce].w = abs(h[i][j] - h[i + 1][j]);
            if(j != n) //向右建边
                ce++, a[ce].x = id[i][j], a[ce].y = id[i][j + 1], a[ce].w = abs(h[i][j] - h[i][j + 1]);
        } //ce是边的数量
    for(int i = 1; i <= cp; i++) //所有的点初始化
        fa[i] = i, tot[i] = 1; //tot记录当前集合中的总点数
    sort(a + 1, a + ce + 1, cmp); //边排序
    for(int i = 1; i <= ce; i++) { //枚举所有的边
        int fx = find(a[i].x);
        int fy = find(a[i].y);
        if(fx != fy) {
            fa[fx] = fy, ts[fy] += ts[fx], tot[fy] += tot[fx], ts[fx] = tot[fx] = 0;
            //fy设为fx的祖先，维护fy的"起点"的数量，fx不再是一个祖先，已合并到fy, 集合数量清零，维护fy的总点数 
            if(tot[fy] >= t)
                ans += ts[fy] * a[i].w, ts[fy] = 0; //当前集合的难度系数和 = 起点数量 * 难度系数
            //计算过的起点删除
        }
    }
    cout << ans;
    return 0;
}
```


---

## 作者：JK_LOVER (赞：2)

## 题意
下面的翻译不太好理解，我这里重新再说一次。一张 $n\times m$ 大小的网格图中，给你 $k$ 个关键点。每个点可以和相邻的点连接。而每个关键点的价值为，$U$ 是这个点所属的联通块：
$$
val_i = \max(abs(h[i] - h[j]))  (j\in U ~~\&\&~~ size[U] \ge T)
$$
现在是要最小化 $\sum_{i=1}^k val_i$ 。[QAQ](https://www.luogu.com.cn/blog/xzc/solution-p3101) 。
## 分析

- 对于关键点来分析，每个关键点的 $val$ 是独立的，那么我们可以单独考虑一个关键点的 $val$ 该怎么求。可以贪心的考虑与这个点的联通块相邻的最优点。其实有点类似 $prim$ 算法的过程，求出这个点的最小生成树。然而这样做时间复杂度为 $O(n^4 \times \alpha(n^2))$ （带路径压缩的 $Kruskal$ 算法）。

- 能不能对上述过程优化？当然是可以的。把所有的边排个序，有小到大连边，就可以将这 $k$ 个关键点一起考虑，当然只有联通块大小大于等于 $T$ 时就可以统计了。

- 这里我使用的是按秩合并的并查集，时间复杂度为 $O(nm\log (nm))$

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int read(){
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='0')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 510;
int col = 0,id[N][N];
int n,m,k,val[N][N],fa[N*N],size[N*N],si[N*N],h[N*N];
struct Edge{int x,y,w;}e[N*N*2];
bool cmp(Edge a,Edge b){
	return a.w < b.w;
}
int find(int x)
{
	while(x^fa[x]) x = fa[x];
	return x;
}
int merge(int x,int y)
{
	if(h[x] > h[y]) swap(x,y);
	si[y] += si[x];size[y] += size[x];fa[x] = y;
	if(h[x] == h[y]) h[y]++;
	return y;
}
signed main()
{
	n = read();m = read();k = read();
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			id[i][j] = ++col;
			val[i][j] = read();
		}
	}
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			si[id[i][j]] = read();
		}
	}
	col = 0;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
		{
			if(i != n)
			e[++col] = (Edge){id[i+1][j],id[i][j],abs(val[i+1][j] - val[i][j])};
			if(j != m)
			e[++col] = (Edge){id[i][j+1],id[i][j],abs(val[i][j+1] - val[i][j])};
		}
	}
//	for(int i = 1;i <= n;i++)
//	{
//		for(int j = 1;j <= m;j++)
//		cout<<id[i][j]<<" ";
//		cout<<endl;
//	}
	sort(e+1,e+col+1,cmp);
	for(int i = 1;i <= n*m;i++)
	{
		fa[i] = i;h[i] = 1;size[i] = 1;
	}
	int Ans = 0;
	for(int i = 1;i <= col;i++)
	{
		int a = e[i].x,b = e[i].y;
		a = find(a);b = find(b);
//		for(int i  =1;i <= n;i++)
//		{
//			for(int j = 1;j <= m;j++)
//			cout<<find(id[i][j])<<" ";
//			cout<<endl;
//		}
		if(a == b) continue;
		int rt = merge(a,b);	//cout<<e[i].w<<" si: "<<si[rt]<<" size: "<<size[rt]<<endl;
		if(size[rt] >= k)
		{
			Ans += (e[i].w * si[rt]);
			si[rt] = 0;
		}
	}

	cout<<Ans<<endl;
}
```


---

## 作者：姬小路秋子 (赞：2)

首先让我抒发一下自己的情怀（如果不想看请忽略）：

**我不想去学校啊我不想去学校啊我不想去学校啊！！！**

~~去了也是睡觉啊去了也是睡觉啊去了也是睡觉啊！！！！！~~

好想现在就去sxyz~~认真学习~~（颓废）啊*3

不过当年我留下了那么~~美妙~~难以回首的往事，去了也会被野花和西格玛裱死啊。。。

今年zj普及取消了，一大波人去报提高，要是我翻车在初赛或者复赛被吊打岂不是很尴尬。。

还有好几个月的~~文化~~睡觉课生活要过，想想也是杯具。。

好了，吐槽的很爽，现在我很舒服的说。。。。。


### 以下是正文

发一篇~~简介~~（极度冗长）的题解。

顺便说一句，上面三层都是我校神犇（逃

如果你看过巨型方块的题解了，那么请注意，我的方法跟他的题解里前9行都是一样的（总共10行）

~~PS：竟然能跟退役巨佬想到一块去，我真是受宠若惊~~~

**重点来了**，请允许我引用下他的第十行：**大力模拟单项链表；**

这什么意思呢？我也不知道，我没看他的代码。

似乎上面三层的所有人都离不开一个核心（事实发现二楼yyhhenry的做法跟我一样）：判断还没有对答案作出贡献的起点有点麻烦！

怎么解决？

考虑并查集的过程，我们记录下每个集合中包含的点数和起点数，我们要保证每个起点只被算到一次，那么只要在合并两个集合时判断合并前的这个集合点数小于T且合并后点数大于等于T就行了，因为这样刚刚使答案符合条件且最优。。

。。。

于是就完了、、。

扯了一大通废话，不过思路还是挺好想的啊。

以及，我写这篇题解的原因是sxyugao那个沙雕用的是pascal，我感到不爽才来写的（话说那个时候他应该已经转为c++了啊，做事不听指挥会被野花裱的，~~要改正啊~~）

### 零错别字好评

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct aaa{
	long long x,y,z;
}b[1000001];
long long n1,n,m,T,f[1000001],g[1000001],a[501][501],c[1000001],ans,sum;
bool cmp(aaa a,aaa b){
	return a.z<b.z;
}
long long find(long long t){
	if(t==f[t])return t;
	return f[t]=find(f[t]);
}
int main(){
	long long i,j,t,k,u,v;
	scanf("%lld%lld%lld",&n,&m,&T);
	if(T<=1){
		printf("0");
		return 0;
	}
	for(i=1;i<=n;i++)
	 for(j=1;j<=m;j++)scanf("%lld",&a[i][j]);
	for(i=1;i<=n;i++) 
	 for(j=1;j<=m;j++){
	 	scanf("%lld",&t);
	 	if(t){
	 	g[(i-1)*m+j]=1;
	 	sum++;
	 }
	 }
	for(i=1;i<=n*m;i++)f[i]=i,c[i]=1;
	for(i=1;i<=n;i++)
	 for(j=1;j<=m;j++){
	 	if(j<m){
	 	 b[++n1].z=abs(a[i][j]-a[i][j+1]);
	 	 b[n1].x=(i-1)*m+j;b[n1].y=(i-1)*m+j+1;
	 }
	 	if(i<n){
	 	b[++n1].z=abs(a[i][j]-a[i+1][j]);
	 	b[n1].x=(i-1)*m+j;b[n1].y=i*m+j;
	 }
	 }
	sort(b+1,b+n1+1,cmp); 
	for(i=1;i<=n1;i++){
		u=b[i].x;v=b[i].y;
		t=find(u);k=find(v);
		if(t!=k){
			f[t]=k;
			if(c[k]+c[t]>=T){
				if(c[t]<T){
				 ans+=b[i].z*g[t];
				 //printf("%lld %lld %lld\n",t,c[k],g[t]);
			}
				if(c[k]<T){
				 ans+=b[i].z*g[k];
				 //printf("%lld %lld %lld\n",k,c[k],g[k]);
			}
			}
			g[k]+=g[t];c[k]+=c[t];
		}
	}
	printf("%lld",ans);
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

晃一眼题目，这不和[这道题](https://www.luogu.com.cn/problem/P2658)一样吗？

但是再仔细一看，有有些不一样，要求了起点至少到多少个点，不要求起点互通，求的也不是最小的 $d$，而是 $d$ 之和。

首先，很容易地发现，这道题再去二分肯定不现实，每个点都去二分一次，所需要的时间也很恐怖。

所以我们尝试从其他的方面入手。

可以发现，如果一个连通块的长度符合条件，那么整个连通块的点都符合条件，那么我们能否在更新并查集的时候，顺便维护这个并查集里的起点的个数呢。

这样的话，只要这个并查集符合条件，那么就直接取出这个并查集的起点个数，乘以答案，再把这个连通块的起点个数改为 $0$ 就好。

那么怎么获得答案呢？

考虑对所有的边按照权值从小到大排序，权值就是两个点的高度差，那么这样的话，我们就先加权值小的边，这样就可以尽可能地使 $d$ 变小了。

另外，因为是二维图，为了方便，我们采用二维转一维。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{long long u,v,w;}b[500005];
inline bool cmp(edge a,edge b){return a.w<b.w;}//边排序
long long rt,n,m,T,h[505][505],idx,sum,fa[250005],siz[250005],ans[250005],k;
long long find(long long x){return (fa[x]==x)?x:fa[x]=find(fa[x]);}//并查集
inline long long get(long long i,long long j){return (i-1)*m+j;}//二维转一维
int main()
{
	scanf("%lld%lld%lld",&n,&m,&T);
	for(long long i=1;i<=n;++i)
		for(long long j=1;j<=m;++j)
		{
			scanf("%lld",&h[i][j]);
			if(i>1) b[++idx].u=get(i-1,j),b[idx].v=get(i,j),b[idx].w=abs(h[i][j]-h[i-1][j]);
			if(j>1) b[++idx].u=get(i,j-1),b[idx].v=get(i,j),b[idx].w=abs(h[i][j]-h[i][j-1]);//建边
		}
	sort(b+1,b+idx+1,cmp);//排序
	for(long long i=1;i<=n;++i) for(long long j=1;j<=m;++j){scanf("%lld",&ans[get(i,j)]),k+=ans[get(i,j)];}
	if(T==1) printf("%lld",k),exit(0);//特殊情况
	for(long long i=1;i<=n*m;++i) siz[i]=1,fa[i]=i;//初始化
	for(long long i=1;i<=idx;++i)
		if(find(b[i].u)!=find(b[i].v))
		{
			siz[find(b[i].v)]+=siz[find(b[i].u)],ans[find(b[i].v)]+=ans[find(b[i].u)];
			if(siz[find(b[i].v)]>=T) sum+=ans[find(b[i].v)]*b[i].w,ans[find(b[i].v)]=0;//记得把起点个数清零，否则会重复统计
			fa[find(b[i].u)]=find(b[i].v);//这个要放在最后
		}
	printf("%lld",sum);
}
```

---

## 作者：YangXiaopei (赞：0)

## 思路：

首先有个最暴力的思路：每个起点都都去二分一个 $D$，在 `check` 中去用搜索跑一遍连通块，大于 $T$，即可。

很明显，时间复杂度为 $\mathcal{O}(n ^ 2 m ^ 2 \log{10 ^ 9})$，肯定过不了。

再仔细想想，不管怎样，光枚举起点最多就要 $\mathcal{O}(nm)$，去找 $D$，再怎么也不可能是 $\mathcal{O}(n)$ 或以下的时间复杂度。所以我们就直接否决了枚举点的做法。

那就只能以边为切入口了。

我们想想，每加入一条边，若这两边原来不连通，那这条边两边的两个连通块就会合成一个大连通块。而如果两边原来均不足 $T$ 个，而合并后达到了 $T$ 个，那这两个连通块中所有的起点，对应的 $D$，不就是这两的连通块中边权最大的边的边权吗？

那我们只需在最开始把所有边排下序，那最后所加的边的边权不就是最大的了吗？

由于边权排过序，那第一次找到的 $D$ 也一定是最小的 $D$。

那最后所需解决的问题就是如何判断联通与维护连通块中点和起点个数了。

判断联通用并查集即可。

我们可以定义 $f_i$ 为以 $i$ 号点为代表的连通块中点的个数。

$v_i$ 为以 $i$ 号点为代表的连通块中点起点的个数。

例如一次合并，左端点为 $x$，右端点为为 $y$。合并并查集时为 `fa[x] = y`，那么更新 $f_i$时即为 `f[y] += f[x], f[x] = 0`。$v_i$ 也同理。

这样就解决这题了。

时间复杂度最高的是排序边，为 $\mathcal{O}(nm\log({nm}))$，可以通过。

还有不懂可以看代码。

## 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int x, y, z;
}e[1000005];
int n, m, t, s, ans, v[250005], f[250005], fa[250005], p[505][505];
void init(){
	for(int i = 1; i <= n * m; i++) {
		fa[i] = i;
		f[i] = 1;
	}
	return;
}
int Find(int x) {
	if(fa[x] == x){
		return x;
	}
	return fa[x] = Find(fa[x]);
}
bool cmp(node a, node b) {
	return a.z < b.z;
}
signed main() {
	cin >> n >> m >> t;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++){
			cin >> p[i][j];
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(i < n){
				s++;
				e[s].x = (i - 1) * m + j;
				e[s].y = i * m + j;
				e[s].z = abs(p[i][j] - p[i + 1][j]);
			}
			if(j < m){
				s++;
				e[s].x = (i - 1) * m + j;
				e[s].y = (i - 1) * m + j + 1;
				e[s].z = abs(p[i][j] - p[i][j + 1]);
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			int x;
			cin >> x;
			if(x == 1){
				v[(i - 1) * m + j] = 1;
			}
		}
	}
	init();
	sort(e + 1, e + s + 1, cmp);
	for(int i = 1; i <= s; i++) {
		int x = Find(e[i].x);
		int y = Find(e[i].y);
		if(x != y) {
			fa[x] = y;
			if(f[x] + f[y] >= t){
				ans += (v[x] + v[y]) * e[i].z;
				v[x] = 0;
				v[y] = 0;
			}
			f[y] += f[x];
			v[y] += v[x];
			f[x] = 0;
			v[x] = 0;
		}
	}
	cout << ans;
	return 0;
}
```

## 最后，不要脸地要个赞。

---

