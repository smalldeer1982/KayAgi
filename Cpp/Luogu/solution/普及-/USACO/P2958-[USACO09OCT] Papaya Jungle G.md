# [USACO09OCT] Papaya Jungle G

## 题目描述

Bessie has wandered off the farm into the adjoining farmer's land. He raises delicious papaya fruit, which is a delicacy for cows. The papaya jungle is partitioned into a grid of squares with R rows and C columns (1 <= R <= 40, 1 <= C <= 40), as is popular in Wisconsin. Bessie can travel from a given square to any existing adjacent square whose route is parallel to the X or Y axis.  So in the

following diagram, if Bessie is at the square labeled 'B', she can travel to any of the squares labeled 'T':

.T.
TBT
.T.
Bessie always starts out by munching the papayas in square

(row=1,col=1).  After she's done with one square, Bessie always uses her trusty binoculars to count the low-hanging fruit in each of the adjacent squares. She then always moves to the square with the most visible uneaten fruit (a square that happily is always unique).

Sooner or later, following this rule, Bessie always ends up in square (R,C) and eats the fruit there.

Given the dimensions of the papaya jungle and the amount of fruit F\_ij in each square (1 <= F\_ij <= 100), determine the total number of fruit Bessie consumes for a given papaya jungle.

POINTS: 80

Bessie不小心游荡出Farmer John的田地，而走进了相邻的农民的地里。她举起一个木瓜，木瓜对奶牛来说可是不可多得得美味。这个木瓜林像一般的威斯康星州的田地一样被分割成一个R行C列的网格(1 <= R <= 40, 1 <= C <= 40)。Bessie可以从一个格沿着一条跟X轴或Y轴平行的直线走到邻接的另一个格。Bessie发现一开始她自己在木瓜林的(1,1)，也就是第一行第一列慢悠悠地咀嚼着木瓜。

Bessie总是用她最信赖地双筒望远镜去数每一个邻接的格里挂着的木瓜的数目。然后她就游荡到那个有最多没有被吃掉的木瓜的邻接的格子（保证这样的格子只有一个）。

按照这种移动方法，最终Bessie总是会在(R,C)停止然后吃掉那里的木瓜。

给定这个木瓜林的大小及每个格的木瓜数F\_ij(1 <= F\_ij <= 100), 要求Bessie一共吃了多少个木瓜。


## 说明/提示

Three rows; four columns. Bessie starts in upper left corner at the '3'.


Bessie eats the papayas in the order given by the letters next to the numbers below:

(1,1) ---> (1,C) 

(1,1) 3a  3   4g  5h  (1,C) 

|   4b  5c  3f  2i    |

(R,1) 1   7d  4e  2j  (R,C) 

(R,1) ---> (R,C) 

She declines to eat 4 of the papayas but consumes 39 (visiting all but two squares of the grid). 



## 样例 #1

### 输入

```
3 4 
3 3 4 5 
4 5 3 2 
1 7 4 2 
```

### 输出

```
39 
```

# 题解

## 作者：zjj20051228 (赞：9)

Bessie不小心游荡出Farmer John的田地，而走进了相邻的农民的地里。她举起一个木瓜，木瓜对奶牛来说可是不可多得得美味。这个木瓜林像一般的威斯康星州的田地一样被分割成一个R行C列的网格(1 <= R <= 40, 1 <= C <= 40)。Bessie可以从一个格沿着一条跟X轴或Y轴平行的直线走到邻接的另一个格。Bessie发现一开始她自己在木瓜林的(1,1)，也就是第一行第一列慢悠悠地咀嚼着木瓜。
Bessie总是用她最信赖地双筒望远镜去数每一个邻接的格里挂着的木瓜的数目。然后她就游荡到那个有最多没有被吃掉的木瓜的邻接的格子（保证这样的格子只有一个）。
按照这种移动方法，最终Bessie总是会在(R,C)停止然后吃掉那里的木瓜。
给定这个木瓜林的大小及每个格的木瓜数F_ij(1 <= F_ij <= 100), 要求Bessie一共吃了多少个木瓜。

思路：只要想如何让Bessie每次走的都是周围木瓜最多的就行了
~~~
#include<bits/stdc++.h>
using namespace std;
int r,c,a[41][41],sum;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
void dfs(int x,int y)
{
	sum=sum+a[x][y];
	a[x][y]=0;
	if(x==r&&y==c)
		return;
	int mx,my,ans=0;
	for(int i=0;i<4;i++)
	{
		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx>=1&&tx<=r&&ty>=1&&ty<=c&&a[tx][ty]>ans)
		{
			ans=a[tx][ty];
			mx=tx,my=ty;
		}	
	}
	dfs(mx,my);	
}
int main()
{
	cin>>r>>c;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++)
			cin>>a[i][j];
	dfs(1,1);
	cout<<sum;
}
~~~

---

## 作者：a___ (赞：2)

发一个最朴素、简单的做法

```cpp
#include <iostream>
using namespace std;
int main ()
{
    int r,c,g[42][42]={0}/*木瓜丛*/,i,j,sum=0/*木瓜数*/;
    cin>>r>>c//输入R、C
    for (i=1;i<=r;i++)
    for (j=1;j<=c;j++)
    cin>>g[i][j];//输入
    i=1;j=1;//初始化为（1,1）处
    while (1)//无限循环模拟
    {
        sum+=g[i][j];/*加上吃掉的木瓜*/g[i][j]=0/*该田木瓜数清0*/;
        if (i==r&&j==c) break;//到达目标退出
        else if (g[i+1][j]>g[i][j+1]&&g[i+1][j]>g[i][j-1]&&g[i+1][j]>g[i-1][j]&&i+1<=r) i++;//若（i+1,j）最大，跳到（i+1,j）
        else if (g[i-1][j]>g[i][j+1]&&g[i-1][j]>g[i][j-1]&&g[i-1][j]>g[i+1][j]&&i-1>=1) i--;//若（i-1,j）最大，跳到（i-1,j）
        else if (g[i][j+1]>g[i+1][j]&&g[i][j+1]>g[i][j-1]&&g[i][j+1]>g[i-1][j]&&j+1<=c) j++;//若（i,j+1）最大，跳到（i,j+1）
        else if (g[i][j-1]>g[i][j+1]&&g[i][j-1]>g[i+1][j]&&g[i][j-1]>g[i-1][j]&&j-1>=1) j--;//若（i,j-1）最大，跳到（i,j-1）
    }
    cout<<sum<<endl;//输出
    return 0;//结束
}
```

---

## 作者：DaftLord (赞：2)



```cpp
{pascal搜索}
var a:array[0..41,0..41] of longint;//这里数组一定要有0，一开始我也被坑了；
    n,m,ans,i,j:longint;
procedure search(x,y:longint);
var p,q:longint;
begin
 if (x=n) and (y=m) then exit;//如果在中点就结束；
 ans:=ans+a[x,y];//计算木瓜总数；
 a[x,y]:=0;//吃掉这一个的木瓜；
  if a[x-1,y]>a[x+1,y] then p:=x-1//寻找邻格中木瓜最多的；
   else p:=x+1;
  if a[x,y-1]>a[x,y+1] then q:=y-1
   else q:=y+1;
  if a[p,y]>a[x,q] then search(p,y)//递归，前往下一格；
   else search(x,q);
end;
begin
 readln(n,m);//输入；
  for i:=1 to n do
  begin
   for j:=1 to m do read(a[i,j]);
   readln;
  end;
  search(1,1);
  writeln(ans+a[n,m]);//不要忘记加上最后一格的木瓜数；
end.

```

---

## 作者：荷叶下 (赞：1)

##### ~~水题解~~
### 题意
##### 给出一片田地
##### 从(1,1)开始,走到(r,c),每次走四周的最大值
##### 求走过的总值

### 实现
##### AC代码如下
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n , m , ans , u = 1 , v = 1 ;
int mapp[2020][2020] ;
int dx[5] = {0, 1, -1, 0, 0} ;
int dy[5] = {0, 0, 0, 1, -1} ;

void bfs()
{
    int maxn , maxx , maxy ;
    while(u != n || v != m)
    {
        ans += mapp[u][v] ; mapp[u][v] = 0 ;
        maxn = 0 ;
        for(int i = 1 ; i <= 4 ; ++i)
        {
            int tx = u + dx[i] ;
            int ty = v + dy[i] ;
            if(mapp[tx][ty] >= maxn)
            {
                maxn = mapp[tx][ty] ;
                maxx = tx , maxy = ty ;
            }
        }
        u = maxx ; v = maxy ;
    }
    ans += mapp[u][v] ;  //!!!!!!!! 记得加上最后那个位置的值
}

int main()
{
    cin >> n >> m ;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= m ; ++j)
            cin >> mapp[i][j] ;
    bfs() ;
    cout << ans ;
    return 0 ;
}
```
##### [AC](https://www.luogu.com.cn/record/44263526)

---

## 作者：SUNCHAOYI (赞：1)

## 简单直白的dfs搜索题
**从（1,1）开始搜索四周数字的最大值（且要没走过的，也就是说也做标记表示走过的地方），同样在搜索的时候要注意不要越界，走到（n,m）就停止搜索，输出答案**
```
#include<iostream>
using namespace std;
const int MAX=51;
bool b[MAX][MAX]={0};//标记有无走过 
int a[MAX][MAX];
int ans=0,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1},n,m;//dx,dy4个方向 
void dfs(int x,int y);
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)cin>>a[i][j];
	dfs(1,1);//从1,1开始 
	cout<<ans<<endl;
    return 0;
}
void dfs(int x,int y)
{
	ans+=a[x][y];//积累数量 
	b[x][y]=1;//标记已走过 
	if(x==n&&y==m)return ;//达到边界 
	int k,s=0;
	for(int i=0;i<4;i++)//四个方向 
	{
		int x1=x+dx[i],y1=y+dy[i];
		if(a[x1][y1]>s&&!b[x1][y1]&&x1>=1&&y1>=1&&x1<=n&&y1<=m)//在符合规定的情况下找到最大值 
		{
			k=i;
			s=a[x1][y1];
		}
	}
	dfs(x+dx[k],y+dy[k]);//继续搜索 
}
```


---

## 作者：SCLBJKD (赞：1)

## 希望管理员能够通过
先吐槽一波，好烦啊，写了好久

思路：一直循环，直到那头无聊的牛走到（n,m），然后每次走时选择上下左右做多的木瓜数的地方走。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[50][50],b[50][50];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int main()
{
    int n,m,ans=0,x,y,maxx,maxy;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        cin>>a[i][j];//输入木瓜数
    x=1;
    y=1;
    //一开始ta在(1,1)
    ans=a[x][y];//木瓜数初始为a[1,1]
    while(!(x==n && y==m))//注意这里千万不能写x!=n && y!=m,教练告诉我的,我也无法解释,以后就这么写吧QwQ
    {
        b[x][y]=1;//这个地方已经吃过了
        int great=-1;//上下左右木瓜数最大值
        int k=-1;//最大值是第几个
        for(int i=0;i<4;i++)
        {
            int xx=x+dx[i];
            int yy=y+dy[i];
            //上下左右的方位
            if(b[xx][yy]==1) continue;//如果被吃过,跳过
            if(a[xx][yy] > great)//如果此地方木瓜数大于最大值
            {
                great=a[xx][yy];//更新最大值
                k=i;//更新最大是第几个
            }
        }
        x=x+dx[k];
        y=y+dy[k];
        //更新方位
        ans+=a[x][y];//更新木瓜数
    }
    cout<<ans;//输出
}
```
撒❀，结束！！！

---

## 作者：ljc20020730 (赞：1)

首先是帮大家翻译一下本题的含义：

Bessie不小心游荡出Farmer John的田地，而走进了相邻的农民的地里。她举起一个木瓜，木瓜对奶牛来说可是不可多得得美味。这个木瓜林像一般的威斯康星州的田地一样被分割成一个R行C列的网格(1 <= R <= 40, 1 <= C <= 40)。Bessie可以从一个格沿着一条跟X轴或Y轴平行的直线走到邻接的另一个格。Bessie发现一开始她自己在木瓜林的(1,1)，也就是第一行第一列慢悠悠地咀嚼着木瓜。

Bessie总是用她最信赖地双筒望远镜去数每一个邻接的格里挂着的木瓜的数目。然后她就游荡到那个有最多没有被吃掉的木瓜的邻接的格子（保证这样的格子只有一个）。

按照这种移动方法，最终Bessie总是会在(R,C)停止然后吃掉那里的木瓜。

给定这个木瓜林的大小及每个格的木瓜数F\_ij(1 <= F\_ij <= 100), 要求Bessie一共吃了多少个木瓜。

输入格式：

第一行2个分离的整数R,C（我这里是n,m）

第2行开始的i+1行表示一个二维数组表示这个木瓜丛林第i,j处有多少个木瓜

（我这里是用a数组表示）

输出格式，一个数表示她吃的木瓜数量

说明：

一个三行；四列的木瓜从林。

Bessie开始在左上角的“3”。

Bessie吃木瓜的字母顺序如下面的号码所示：

(1,1) ---> (1,C)

(1,1) 3a 3 4g 5h (1,C)

| 4b 5c 3f 2i |

(R,1) 1 7d 4e 2j (R,C)

(R,1) ---> (R,C)

她拒绝吃4的木瓜但访问所有的方格后最终吃掉39个木瓜。

【解析】

来一发用坐标增量的题解（可以更加让人理解）

const dx:array[1..4]of integer=(-1,0,+1,0);//表示她周围的木瓜的x坐标增量

dy:array[1..4]of integer=(0,+1,0,-1);//表示她周围的木瓜的y坐标增量

```cpp
var ans,i,j,n,m:longint;
    a:array[0..40,0..40]of longint;//木瓜林
procedure dfs(x,y:longint);//表示她现在到达的地方
var i,max,px,py:longint;
begin
 if (x=m)and(y=n) then exit;//到达目的地
 ans:=ans+a[x,y];//吃掉位于(x,y)的木瓜（当前地点）
 a[x,y]:=0;////当前地点的剩余木瓜为0
 max:=0; px:=0; py:=0;//px表示她四周最大木瓜数格子的x坐标增量，py表示她四周最大木瓜数格子的y坐标增量
 for i:=1 to 4 do
  if (max<a[x+dx[i],y+dy[i]])then//取四周木瓜的最大值和最大坐标增量
  begin
   px:=dx[i]; py:=dy[i];
   max:=a[x+dx[i],y+dy[i]];
  end;
 dfs(x+px,y+py);//dfs找下一个点
 end;
begin
 readln(m,n);
 for i:=1 to m do
  for j:=1 to n do read(a[i,j]);
 dfs(1,1);
 writeln(ans+a[m,n]);//不要忘记吃终点的木瓜
 a[m,n]:=0;////当终点的剩余木瓜为0（有始有终的好孩子）
end.
```

---

## 作者：甄黫陻堙 (赞：0)

## 题目
[P2958 [USACO09OCT]Papaya Jungle G](https://www.luogu.com.cn/problem/P2958)

## 思路
我用bfs搜的（其实也可以用dfs~~我懒得写~~）

具体的我写代码里了
```cpp
#include<queue>
#include<cstdio>
using namespace std;
long long ans;
int r,c,a[50][50];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1},bl[50][50];//方向数组和标记
struct node{
	int x,y;
};
queue<node>q;
void bfs(){
	int c1,c2;//临时坐标
	while(!q.empty()){
		int x,y,s=-1;
		for(int i=0;i<4;i++){
			x=q.front().x+dx[i];
			y=q.front().y+dy[i];
			if(s<a[x][y]&&x>0&&y>0&&x<=r&&y<=c&&bl[x][y]==0){
				c1=x,c2=y;s=a[x][y];
			}//找出四个方向最大的数（注意不要超范围）
		}
		bl[c1][c2]=1;
		ans+=a[c1][c2];//ans加
        
		q.pop();
		q.push((node){c1,c2});
        
		if(c1==r&&c2==c){//到（r，c）停止搜索
			printf("%lld",ans);
			return;
		}
	}
}
int main(){
	scanf("%d%d",&r,&c);
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			scanf("%d",&a[i][j]);
		}
	}
	ans=a[1][1];
	bl[1][1]=1;//从（1,1）开始搜
	q.push((node){1,1});
	bfs();
	return 0;
}
```

 _~~蒟蒻交的第二篇题解，望通过~~_ 

---

## 作者：鸿飞 (赞：0)

这是一道水题。
## PART1:题意
从（1,1）开始走，每次走到相邻四个位置中值最大的一个，直到（r,c）。
## PART2:思路
while循环模拟行走过程。在每个位置开始时ans加上该位置的值并判断四周的位置哪个值最大，然后继续行走。
## PART3:注意事项
用while的话还需要再加上（r，c）的值，因为while循环在到达（r,c）后立刻停止而没有让ans加上（r，c）的值。
## PART4：代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,m;//其实就是r和c 
int map[45][45];//地图
int mx[4]={0,0,1,-1};//控制x坐标移动 
int my[4]={1,-1,0,0};//控制y坐标移动 
int main(){
	cin >> n >> m ;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin >> map[i][j] ;//读入 
		}
	}
	int x=1,y=1;
	int maxx=0,maxxx,maxxy;
	int xx,yy;
	int ans=0;
	while(x!=n||y!=m)//模拟行走过程 
	{
		ans+=map[x][y];
		map[x][y]=0;
		maxx=0;
		for(int i=0;i<=3;i++)
		{
			xx=x+mx[i];
			yy=y+my[i];
			if(map[xx][yy]>=maxx)
			{
				maxx=map[xx][yy];
				maxxx=xx;
				maxxy=yy;
			}
		}
		x=maxxx;
		y=maxxy;
	}
	ans+=map[x][y];
	cout << ans ;
	return 0;
}

```


---

## 作者：jbc392 (赞：0)

此题很明显考搜索

思路：每次找四周最大的然后吃掉比作标记

AC Code：

```
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2010;
const int dx[5] = {-1 ,1 ,0 ,0} ,dy[5] = {0 ,0 ,-1 ,1};

int r ,c ,ans;
int a[MAXN][MAXN];
bool vis[MAXN][MAXN];

inline int read()//快读
{
    int x = 0 ,y = 1;
    char c = getchar();
    while(c > '9' || c < '0')
    {
        if(c == '-')y = -1;
        c = getchar();
    }
    while(c <= '9' && c >= '0')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * y;
}

void pre()//初始化
{
    for(register int i = 1;i <= r;i++)
    {
        for(register int j = 1;j <= c;j++)
        {
            vis[i][j] = false;//全标记为没吃过
        }
    }
    vis[1][1] = true;//第一个肯定要吃
    ans = a[1][1];
}

int main()
{
    r = read(); c = read();//输入
    for(register int i = 1;i <= r;i++)
    {
        for(register int j = 1;j <= c;j++)
        {
            a[i][j] = read();
        }
    }

    pre();//初始化

    int x = 1 ,y = 1;
    while(!(x == r && y == c))//如果没达到终点折继续
    {
        int s = 0 ,tx ,ty;
        for(int i = 1;i <= 4;i++)//搜索旁边的点
        {
            if(a[x + dx[i - 1]][y + dy[i - 1]] > s && !vis[x + dx[i - 1]][y + dy[i - 1]])
            {
                s = a[x + dx[i - 1]][y + dy[i - 1]];
                tx = x + dx[i - 1];
                ty = y + dy[i - 1];
            }
        }
        ans += s;//累加答案
        x = tx;
        y = ty;//走到下一格
        vis[x][y] = true;//标记
    }
    cout << ans;//输出

    return 0;//好习惯
}
```


---

## 作者：deamoon_2 (赞：0)

发现大家都用dfs和bfs,我认为没必要那么麻烦，这里教大家一种更简单粗暴的写法。

# **模拟！**

没有错！就是简单的模拟！

从（1,1）开始循环，看四边哪个数大，就走那个，然后更改坐标继续走，直到走到（n,m）。

注意每走完一块地要清零，不然又会跑回来。

亮代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
int x[5]={0,1,0,-1,0};
int y[5]={0,0,1,0,-1};
int a[51][51];
int main()
{
	int n,m,sum=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	cin>>a[i][j];
	int i,j;
	i=j=1;
	sum=a[i][j];
	while(i!=n||j!=m)
	{
		int t,s=0;
		for(int l=1;l<=4;l++)
		{
			if(a[i+x[l]][j+y[l]]>s)
			{
				s=a[i+x[l]][j+y[l]];
				t=l;
			}
		}
		a[i][j]=0; 
		i+=x[t];
		j+=y[t];
		sum+=s;
		//cout<<i<<' '<<j<<' '<<sum<<endl;
	}
	cout<<sum;
	return 0;
}
```

2019 NOIP RP++

---

## 作者：飞翔 (赞：0)

看到范围我就笑了。。。

就是水搜索！

其实做的1000也没什么啊，不回溯就可以啊

```pascal
var
  map:array[0..40,0..40]of longint;
  xx,yy,x,y,i,r,c,j,t,ans:longint;
begin
  read(r,c);
  for i:=1 to r do
    for j:=1 to c do
      read(map[i,j]);
  ans:=map[1,1];
  map[1,1]:=0;
  x:=1;y:=1;
  while (x<>r)or(y<>c) do begin
    t:=0;
    for i:=-1 to 1 do
      for j:=-1 to 1 do
        if (i=0)or(j=0) then
          if (x+i>0)and(x+i<=r)and(y+j>0)and(y+j<=c) then
            if map[x+i,y+j]>t then begin
              t:=map[x+i,y+j];
              xx:=x+i;yy:=y+j;
            end;
    x:=xx;y:=yy;
    ans:=ans+t;
    map[x,y]:=0;
  end;
  writeln(ans);
end.
```

---

## 作者：二元长天笑 (赞：0)

刚才天笑看了一下，下面的基本都是用**DFS**来做的。天笑这里借用了**BFS**的思想，每到一个点，就向周围的四个点拓展新节点，然后选取最优的节点作为下一步，也就是木瓜最多的格点。一般BFS都会用一个bool数组来记录走过的状况，但在此题中只需要将走过的点修改使它不能成为最优点，也就是将它赋为0。**最后，一定要记得加上（1，1）和（r，c）这两个点中的木瓜！！**

下面是AC代码：

```cpp
#include<iostream>
using namespace std;
int a[101][101],d1[4]={0,1,-1,0},d2[4]={1,0,0,-1},r,c,ans;
void search(int x,int y)
{
    ans+=a[x][y];  //带上（1，1）里的木瓜
    a[x][y]=0;
    while(x!=r||y!=c)
    {
        int maxn=0,maxx,maxy;
        for(int i=0;i<4;i++)  //向四周拓展节点
        {
            int nowx=x+d1[i];
            int nowy=y+d2[i];
            if(nowx>=1&&nowx<=r&&nowy>=1&&nowy<=c&&a[nowx][nowy]>maxn)  //判断是否越界与是否是最优点
            {
                maxn=a[nowx][nowy];
                maxx=nowx;
                maxy=nowy;
            }
        }
        ans+=maxn;
        a[maxx][maxy]=0;  //修改使其不能成为最优点
        x=maxx,y=maxy;
    }
}
int main()
{
    cin>>r>>c;
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            cin>>a[i][j];
    search(1,1);
    cout<<ans<<endl;
}
```
祝大家早日AC！！！


---

## 作者：封禁用户 (赞：0)

直接搜索模拟即可。

代码很简洁，题解最正常。

```cpp
#include<bits/stdc++.h>//万能头文件。
using namespace std;
int m,n,a[2010][2010],sum,k;
void dfs(int x,int y){//x，y表示当前搜到矩阵的哪一个位置。
 if(x==m && y==n){//如果到了终点的话就输出答案。
     cout<<sum;
     return ;
  }
    a[x][y]=0;//每次进去就把当前的位置的木瓜数设为0（1.因为牛吃了木瓜，2.不设为0有可能导致搜索时反复横跳）
    int k=sum;//记录前驱，下面有用。
    sum+=max(max(a[x-1][y],a[x+1][y]),max(a[x][y-1],a[x][y+1]));//找到当前位置前后左右最大的木瓜数，并加入到sum。
    if(sum-k==a[x-1][y]) dfs(x-1,y);
    if(sum-k==a[x+1][y]) dfs(x+1,y);
    if(sum-k==a[x][y-1]) dfs(x,y-1);
    if(sum-k==a[x][y+1]) dfs(x,y+1)//判断到底加的是前后左右哪一个点的木瓜数，并且从那一个点开始搜。;
}
int main(){
    cin>>m>>n;
    for(int i=1;i<=m;i++)
      for(int j=1;j<=n;j++)
         cin>>a[i][j];//读入矩阵表。
         sum=a[1][1];//我们（1,1）点上的木瓜数首先要加上去因为牛一开始是站在（1,1）点上的。
             dfs(1,1);//从（1,1）开始搜。
    return 零;
}//结束。
```

---

## 作者：tang_xu (赞：0)

用BFS不就好啦

```cpp
#include<iostream>
using namespace std;
int a[101][101],d1[4]={0,1,-1,0},d2[4]={1,0,0,-1},r,c,ans;
void search(int x,int y)
{
    ans+=a[x][y];  //带上（1，1）里的木瓜
    a[x][y]=0;
    while(x!=r||y!=c)
    {
        int maxn=0,maxx,maxy;
        for(int i=0;i<4;i++)  //向四周拓展节点
        {
            int nowx=x+d1[i];
            int nowy=y+d2[i];
            if(nowx>=1&&nowx<=r&&nowy>=1&&nowy<=c&&a[nowx][nowy]>maxn)  //判断是否越界与是否是最优点
            {
                maxn=a[nowx][nowy];
                maxx=nowx;
                maxy=nowy;
            }
        }
        ans+=maxn;
        a[maxx][maxy]=0;  //修改使其不能成为最优点
        x=maxx,y=maxy;
    }
}
int main()
{
    cin>>r>>c;
    for(int i=1;i<=r;i++)
        for(int j=1;j<=c;j++)
            cin>>a[i][j];
    search(1,1);
    cout<<ans<<endl;
}
```

---

