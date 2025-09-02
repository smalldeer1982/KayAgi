# [USACO2.1] 城堡 The Castle

## 题目背景

我们憨厚的 USACO 主人公农夫约翰（Farmer John）以无法想象的运气,在他生日那天收到了一份特别的礼物：一张“幸运爱尔兰”（一种彩票）。结果这张彩票让他获得了这次比赛唯一的奖品——坐落于爱尔兰郊外的一座梦幻般的城堡！

## 题目描述

喜欢吹嘘的农夫约翰立刻回到有着吹嘘传统的威斯康辛老家开始吹嘘了, 农夫约翰想要告诉他的奶牛们关于他城堡的一切。他需要做一些吹嘘前的准备工作：比如说知道城堡有多少个房间，每个房间有多大。  

另外，农夫约翰想要把一面单独的墙（指两个单位间的墙）拆掉以形成一个更大的房间。 你的工作就是帮农夫约翰做以上的准备，算出房间数与房间的大小。

城堡的平面图被划分成 $n \times m$ 个正方形的单位，一个这样的单位可以有 $0 \sim 4 $ 面墙环绕。城堡周围一定有外墙环绕以遮风挡雨。（就是说平面图的四周一定是墙。）

请仔细研究下面这个有注解的城堡平面图：

```plain
     1   2   3   4   5   6   7
   #############################
 1 #   |   #   |   #   |   |   #
   #####---#####---#---#####---#
 2 #   #   |   #   #   #   #   #
   #---#####---#####---#####---#
 3 #   |   |   #   #   #   #   #
   #---#########---#####---#---#
 4 # ->#   |   |   |   |   #   #
   #############################
```

- $\verb!#!$ 表示墙壁；
- $\verb!|!$ 和 $\verb!-!$ 表示没有墙壁；
- $\verb!->!$ 指向了一面墙，移除了这面墙我们就有一间最大的新房间。

友情提示，这个城堡的平面图是 $4 \times 7$ 个单位的。一个“房间”的是平面图中一个由 `#`、`-`、`|` 围成的格子（就是图里面的那一个个的格子）。比如说这个样例就有 $5$ 个房间。（大小分别为 $9,7,3,1,8$ 个单位（排名不分先后））

移去箭头所指的那面墙，可以使 $2$ 个房间合为一个新房间，且比移去其他墙所形成的房间都大。

城堡保证至少有 $2$ 个房间，而且一定有一面墙可以被移走。


## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n,m \le 50$。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
7 4
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13```

### 输出

```
5
9
16
4 1 E```

# 题解

## 作者：kradcigam (赞：143)

# [博客园体验更佳](https://www.cnblogs.com/zhaohaikun/p/12189327.html)

来讨论区大摇大摆地逛了一圈后，我发现竟然大家的代码
# 都很长
然而代码真的要写那么长吗


------------

首先，来分析问题，1，2，4，8，这些数显然是有特点的，也许你已经想到了没错，它们都是2的次方数。


1是2的0次方


2是2的1次方


4是2的2次方

8是2的3次方

知道这个就好办了，用什么呢？没错是位运算，哈哈！

1的二进制是1

2的二进制是10

4的二进制是100

8的二进制是1000

于是，就得出了以下代码：

```cpp
if(x&1)a[i][j][0]=1;
if(x&2)a[i][j][1]=1;
if(x&4)a[i][j][2]=1;
if(x&8)a[i][j][3]=1;
```

大家也看到了，我用了一个3维数组，a[55][55][4]。

看到这道题，我首先想到的是宽搜（宽度优先搜索），用数组模拟，这道题的数据范围不大，用数组完全可能。

上代码：
```cpp
#include <bits/stdc++.h>//用万能头文件开始了代码
using namespace std;//命名空间
int n,m,h[55][55],a[55][55][4],s,ans,z1,z2;
int q1[10010],q2[10010],f[10010];
int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
char z3;
string z="WNEA";
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			if(x&1)a[i][j][0]=1;//位运算
			if(x&2)a[i][j][1]=1;//位运算
			if(x&4)a[i][j][2]=1;//位运算
			if(x&8)a[i][j][3]=1;//位运算
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!h[i][j]){
				int front=0,rear=1,sum=1;
				q1[1]=i;
				q2[1]=j;
				h[i][j]=++s;
				while(front<rear){//开始宽搜
					front++;
					int x=q1[front],y=q2[front];
					for(int k=0;k<=3;k++){
						int tx=x+dx[k],ty=y+dy[k];
						if(tx>0&&tx<=n&&ty>0&&ty<=m&&!h[tx][ty]&&!a[x][y][k]){
							h[tx][ty]=s;
							sum++;
							q1[++rear]=tx;
							q2[rear]=ty;
						}
					}
				}ans=max(ans,sum);
				f[s]=sum;//记录编号s的房间的间数
			}
	cout<<s<<endl<<ans<<endl;
	for(int j=1;j<=m;j++)//这里有坑
		for(int i=n;i>=1;i--)//这里有坑
			for(int k=1;k<=2;k++)
				if(a[i][j][k]){
					int tx=i+dx[k],ty=j+dy[k];
					int x=f[h[tx][ty]]+f[h[i][j]];//活用数组下标
					if(x>ans&&h[tx][ty]!=h[i][j]){//一定要注意h[tx][ty]!=h[i][j]，有时候尽管有墙，但能通过别的房间，达到这个房间。（考虑要周全）
						ans=x;
						z1=i;
						z2=j;
						z3=z[k];
					}
				}
	cout<<ans<<endl<<z1<<" "<<z2<<" "<<z3;
	return 0;//华丽结束
}
```


---

## 作者：早右昕 (赞：16)

### 轻度中毒 （题解 in Luogu)

明明辣么简单的一道题，硬是搞了1.5h,WTF?以下列出本题的一些要点。


- 搜索(DFS)嘛，染色嘛，统计大小嘛，很容易想，也很更易处理。

- 接下来就只需要枚举墙，得出最大值了。好像很简单的样子QAQ——but №!我™就是在这里折腾了一个小时（可能是我太菜了）。

- 蒟蒻统计的思路是：北墙(-1,0)与东墙(0,+1)分开枚举，得到各自的最优解，然后再比较这两个解，输出更好的那个(捂脸）。

- 详细见丑\*代码：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
main() {}
const int fx[]= {0,-1,0,1};//W,N,E,S
const int fy[]= {-1,0,1,0};
int n,m,id[51][51],a[51][51],tot,room[50*50+1];
void clor(int x,int y,int c) {
    id[x][y]=c;
    room[c]++;//面积
    for(int i=0,nx,ny; i<4; i++)
        if(!(a[x][y]&(1<<i)))  {//美丽的二进制解析
            nx=x+fx[i],ny=y+fy[i];
            if(nx>0&&ny>0&&nx<=n&&ny<=m&&!id[nx][ny])
                clor(nx,ny,c);
        }
}
int entry() {
    scanf("%d%d",&m,&n);
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++)
            scanf("%d",&a[i][j]);
    }
    for(int i=1; i<=n; i++) {//染色
        for(int j=1; j<=m; j++)
            if(!id[i][j])
                clor(i,j,++tot);
    }
    int maxn=*std::max_element(room+1,room+tot+1);
    printf("%d\n""%d\n",tot,maxn);
    int ans1=maxn,ans2=maxn;
    int x1=n,y1=0,x2=n,y2=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++) {
            if((a[i][j]&2)&&id[i][j]!=id[i-1][j]&&ans1<=room[id[i][j]]+room[id[i-1][j]]) {
                if(ans1!=room[id[i][j]]+room[id[i-1][j]]) x1=i,y1=j;
                else if(j<y1) y1=j,x1=i;//West
                else if(j==y1 && i>x1) x1=i;//South
                ans1=room[id[i][j]]+room[id[i-1][j]];
            }//北墙
            if((a[i][j]&4)&&id[i][j]!=id[i][j+1]&&ans2<=room[id[i][j]]+room[id[i][j+1]]) {
                if(ans2!=room[id[i][j]]+room[id[i][j+1]]) x2=i,y2=j;
                else if(j<y2) y2=j,x2=i;//West
                else if(j==y2 && i>x2) x2=i;//South
                ans2=room[id[i][j]]+room[id[i][j+1]];
            }//东墙
        }
    if(ans1>ans2) printf("%d\n%d %d N\n",ans1,x1,y1);
    else if(ans1<ans2) printf("%d\n%d %d E\n",ans2,x2,y2);//maxmize result
    else if(y1<y2) printf("%d\n%d %d N\n",ans1,x1,y1);
    else if(y1>y2) printf("%d\n%d %d E\n",ans2,x2,y2);//west
    else if(x1>x2) printf("%d\n%d %d N\n",ans1,x1,y1);
    else if(x1<x2) printf("%d\n%d %d E\n",ans2,x2,y2);//south
    else printf("%d\n%d %d N\n",ans1,x1,y1);
}
int aptal=entry();
```
安利一下个人博客：[我是传送门](http://www.cnblogs.com/FreeRing/p/7904348.html)


---

## 作者：Ajwallet (赞：12)

~~图论题硬是做成了bfs~~

咳咳，一开始想没有负数，输入流就没有特殊处理负数，结果一直WA。~~不禁想起了书的复制里书的页数竟然也有负数~~

--------------------请忽略上述内容

#思路

首先输入，用wall[i][j][k](1<=i<=n,1<=j<=m,1<=k<=4)表示i,j这个方格的周围是否有墙。

用ce[i][j]表示这个房间是第几间房间，顺便用来封路。

用fjh[i]表示第i个房间他的房间面积。

我们每次找到两个房间号不一样的房间，拆除他们之间的墙，把两个房间的面积加在一起，取其中的最大值（**注意，南方和西方的房间优先**）

#代码

```cpp
#include<cstdio>
#define r(i,a,b) for (int i=a;i<=b;i++)
#define check1 fjh[ce[i][j]]+fjh[ce[i][j-1]]>ans||(fjh[ce[i][j]]+fjh[ce[i][j-1]]==ans&&j-1<qy)||(fjh[ce[i][j]]+fjh[ce[i][j-1]]==ans&&j-1==qy&&i>qx)//额，这一串有点难理解，先看下面的。
#define check2 fjh[ce[i][j]]+fjh[ce[i-1][j]]>ans||(fjh[ce[i][j]]+fjh[ce[i-1][j]]==ans&&j<qy)||(fjh[ce[i][j]]+fjh[ce[i-1][j]]==ans&&j==qy&&i>qx)//这些放在后面说
using namespace std;int head,tail;//队首队尾
int n,m,k,fj,maxn,maxfj;//n，m为矩阵的大小，是每次输入的数，fj表示有几间房间，maxn没用（额），maxfj为房间面积
int ce[50+10][50+10];//ce为这个房间的编号，就是他是第几间，顺带封路
bool wall[50+10][50+10][5];//表示wall[i][j]周围是否有墙壁
int ans,qx,qy;//ans是拆了一面墙后最大的房间面积，(qx,qy)为拆的那面墙的坐标
int state[2500+10][3],father[2500+10];//广搜数组不用解释吧
char ans2;int fjh[2500+10];//ans2用来表示最后是拆北方的还是东方的
const short dx[4]={-1,0,1,0};
const short dy[4]={0,1,0,-1};//四个方向
int max(int x,int y)//最大值不解释
{
    return x>y?x:y;
}
void read(int &f)//输入流
{
    f=0;char c;bool d=1;
    while (c=getchar(),c<'0'||c>'9') if (c=='-') d=0;f=f*10+c-48;//汗颜。。。
    while (c=getchar(),c>='0'&&c<='9') f=f*10+c-48;
    if (!d) f*=-1;
}
bool check(int x,int y,int ox,int oy)//判断(ox,oy)能否到达(x,y)
{
    if (x<1||y<1||x>n||y>m) return false;//跑出城堡
    if (ox-1==x&&y==oy&&!wall[ox][oy][1]) return true;//北面可以走
    if (ox+1==x&&y==oy&&!wall[ox][oy][2]) return true;//南面可以走
    if (ox==x&&oy-1==y&&!wall[ox][oy][3]) return true;//西面可以走
    if (ox==x&&oy+1==y&&!wall[ox][oy][4]) return true;//东面可以走
    return false;//否则
}
void bfs(int x,int y)
{
    if (ce[x][y]>0) return;//如果这个房间已经搜过了直接推出
    head=0;tail=1;fj++;//房间总数加一
    state[1][1]=x;
    state[1][2]=y;ce[x][y]=fj;//初始化
    do
    {
        head++;
        r(i,0,3)
         {
             int nx=state[head][1]+dx[i];
             int ny=state[head][2]+dy[i];
             if (check(nx,ny,state[head][1],state[head][2])&&!ce[nx][ny])//可以到达并且没有走过
             {
                 tail++;
                 father[tail]=head;
                 state[tail][1]=nx;
                 state[tail][2]=ny;//入队
                 ce[nx][ny]=fj;//封路
             }
         }
    }while(head<tail);
}
int main()
{
    read(m);read(n);//一定要记得反过来，其他一样
    r(i,1,n)
     r(j,1,m)
      {
          if (i==1) k-=2;
          if (i==n) k-=8;
          if (j==1) k-=4;
          if (j==n) k--;//边界处理，因为他说四周都有墙
          read(k);
          if (k>=8) {wall[i][j][2]=true;k-=8;}//先减去大的，反过来会错
          if (k>=4) {wall[i][j][4]=true;k-=4;}
          if (k>=2) {wall[i][j][1]=true;k-=2;}
          if (k>=1) {wall[i][j][3]=true;k-=1;}
      }
    r(i,1,n)
     r(j,1,m)
      {
          bfs(i,j);//广搜
          fjh[fj]=tail;//存下第fj个房间对应的面积也就是tail
          maxfj=max(maxfj,tail);//取下最大的房间
      }
    printf("%d\n%d\n",fj,maxfj);//输出房间总数和最大的房间面积
    r(i,1,n)
     r(j,1,m)
     {
         if (wall[i][j][3]&&ce[i][j-1]!=ce[i][j])//如果东面有墙并且这两个方格不是同一个房间
          if (check1)//这里有点复杂：如果这两个房间面积的和大于最优解就进行下面的语句。如果面积相等就看哪个更加靠近西边，如果离西面一样近就看哪个更加靠近南面。
          {
              ans=fjh[ce[i][j]]+fjh[ce[i][j-1]];//保存最优解
              qx=i;qy=j-1;//保存坐标，减一是因为是倒推，因为如果是j就是求东边的，但这样的结果和求西边是一样的，而且如果按照题目给的模拟的话，还要处理边界 ，而如果反过来就没有这样的顾忌了。
              ans2='E';//存下方向
          }
         if (wall[i][j][1]&&ce[i][j]!=ce[i-1][j])//跟上面道理是一样的，不过有人会问：不是优先考虑北方吗？怎么北方还在后面呢？这里解释一下，因为这样才是优先考虑北方，为什么呢？因为如果我先求出了东方可以，那么我还会再求北方，这是北方就替代了东方，也就相当于北方优先了
          if (check2)
          {
              ans=fjh[ce[i][j]]+fjh[ce[i-1][j]];
              qx=i;qy=j;
              ans2='N';
          }
     }
    printf("%d\n%d %d %c",ans,qx,qy,ans2);//输出答案
}
```

---

## 作者：「QQ红包」 (赞：11)

题解by：redbag

题解地址：http://redbag.duapp.com/?p=1122

这里的代码有缩进，比洛谷的美观些，这是事实23333333

我的博客：http://redbag.duapp.com/

欢迎来踩。

###暴力出奇迹

第一，二问：


简单的floodfill。


第三，四问：


暴力枚举

“有多解时选（重心）最靠西的（仍然有多解时选这些里面（重心）最靠南的）。” 请注意重心二字！ 北墙的重心比东墙的要靠西啊~~所以拆墙顺序是西墙，南墙，北墙，东墙。


附上代码：

/\*
ID: ylx14271

PROG: castle

LANG: C++

\*/
```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int f[51][51][5];//存墙,f[i][j][0]存所属标号 
int n,m,i,j,ii,jj;
int p=0;//连通块的个数 
int a[2501];//存每个连通块的大小？ 
int ff[5][3]={{0,0,0},
             {3,0,1},//右 
             {4,1,0},//下 
             {1,0,-1},//左 
             {2,-1,0}};//上，晕了~~~~(>_<)~~~~  
//上下左右四个方向,f[i][0]存到达那需穿过的墙的方向 
void dfs(int x,int y,int id)//dfs求连通块,id是标记的编号 
{
    if (x<=0||x>n||y<=0||y>m) return;//越界辣~\(≧▽≦)/~
    if (f[x][y][0]!=0) return;//被搜过辣，当然这种情况是不会出现的 
    f[x][y][0]=id;//存编号 
    a[id]++; 
    for (int ii=1;ii<=4;ii++)//四种情况去搜
        if ((f[x+ff[ii][1]][y+ff[ii][2]][0]==0)/*没被搜过*/&&(f[x][y][ff[ii][0]]==0)/*过去没墙*/)
        dfs(x+ff[ii][1],y+ff[ii][2],id);//往下搜 
}
int main() 
{
    freopen("castle.in","r",stdin);
    freopen("castle.out","w",stdout); 
    scanf("%d%d",&m,&n);//读入;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            int hehe;
            scanf("%d",&hehe);//读入墙的数字和
            if (hehe>=8) 
            {
                hehe-=8; 
                f[i][j][4]=1;//标记南方有墙 
            }
            if (hehe>=4) 
            {
                hehe-=4;
                f[i][j][3]=1;//标记东方有墙 
            } 
            if (hehe>=2) 
            {
                hehe-=2;
                f[i][j][2]=1;//标记北方有墙 
            } 
            if (hehe>=1) 
            {
                hehe-=1;
                f[i][j][1]=1;//标记西方有墙 
            }  
            //终于标记完了╮(╯▽╰)╭
            //这种方法好巧啊。 
        }
    for (i=1;i<=n;i++) 
        for (j=1;j<=m;j++)
        {
            if (f[i][j][0]==0)/*目前不属于任何一个连通块*/
            {
                p++;
                dfs(i,j,p);//++p是目前搜的这个连通块的标记 
            }
        }
    printf("%d\n",p);//成功灭掉第一问 
    int maxx=a[1];//初始化 
    for (i=1;i<=p;i++) if (a[i]>maxx) maxx=a[i];
    printf("%d\n",maxx); //成功灭掉第二问 
    //由题可知，移去的墙相对于某一个位置来说一定是东面或者北面 
    char k;
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) //枚举 挖走动墙
        {
            if (i!=1&&f[i][j][2]==1&&f[i][j][0]!=f[i-1][j][0])//第一行的北墙不能挖走,而且要有墙
            //而且没有在同一个连通块 
            {
                int hehe=a[f[i][j][0]]+a[f[i-1][j][0]];//合并后连通块大小 
                if (hehe>maxx) 
                {
                    maxx=hehe;
                    ii=i;
                    jj=j;//标记 
                    k='N';//标记 
                }
                if (hehe==maxx)
                {
                    if ((j<jj)/*更西*/||(i>ii&&j<=jj)/*更南且不会更东*/)
                    {
                        ii=i;
                        jj=j;//标记 
                        k='N';//标记 
                    }
                }
            } 
            if (j!=m&&f[i][j][3]==1&&f[i][j][0]!=f[i][j+1][0])//最后一列的东墙不能挖走 ,而且要有墙
            //而且没有在同一个连通块 
            {
                int hehe=a[f[i][j][0]]+a[f[i][j+1][0]];//合并后连通块大小 
                if (hehe>maxx) 
                {
                    maxx=hehe;
                    ii=i;
                    jj=j;//标记 
                    k='E';//标记 
                }
                if (hehe==maxx)
                {
                    if ((j<jj)||(i>ii&&j<=jj))//更西方，更南方且不会更东方 
                    {
                        ii=i;
                        jj=j;//标记 
                        k='E';//标记 
                    }
                }
            } 
        } 
    printf("%d\n",maxx);//第三问完成 
    printf("%d %d %c\n",ii,jj,k);//终于完成了 
    return 0;
}
```

---

## 作者：PrincessQi (赞：9)

# 这个题我个人感觉蛮好的，就是……

//如果有个SPJ就更好了（小声）

好了，下面是题解：

-----------------------并不华丽的分割线-----------------------

### 第一问：DFS搜索

难度：低

为了方便搜我把二进制的墙改成了数组

用以下代码实现：

```
			if(d%2==1)mp[i][j][1]=1;//西墙
			d/=2;
			if(d%2==1)mp[i][j][2]=1;//北墙
			d/=2;
			if(d%2==1)mp[i][j][3]=1;//东墙
			d/=2;
			if(d%2==1)mp[i][j][4]=1;//南墙
```

搜索的基本思路就是染色法：

```
void t(int i,int j){
	b[i][j]=s;//记录所属房间编号
	for(int k=1;k<=4;k++)
		if(mp[i][j][k]==0&&b[i+dx[k-1]][j+dy[k-1]]==0)a[s]++,t(i+dx[k-1],j+dy[k-1]);//如果它旁边的格子也属于这个房间记录下来并继续搜索
}
```
那么数组a是是干什么的呢？

~~那是第二问内容，第二问再说~~

在主程序里的循环模块：

```
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(b[i][j]==0)s++,a[s]=1,t(i,j);//如果不属于已知的任何房间就搜索
```
### 第二问：DFS搜索上的计数

难度：低

a数组只不过是一个计数的，当然，它在第三、四问里有大帮助。//不然题目要你求它干嘛嘞

### 第三问：枚举

难度：中

你们可能会问：

**枚举还能比搜索难？**

~~明明都很简单~~

但这个题我看了一下别的题解好像都把这一问想得比较恐怖

比如@早右昕 的题解：

```
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++) {
            if((a[i][j]&2)&&id[i][j]!=id[i-1][j]&&ans1<=room[id[i][j]]+room[id[i-1][j]]) {
                if(ans1!=room[id[i][j]]+room[id[i-1][j]]) x1=i,y1=j;
                else if(j<y1) y1=j,x1=i;//West
                else if(j==y1 && i>x1) x1=i;//South
                ans1=room[id[i][j]]+room[id[i-1][j]];
            }//北墙
            if((a[i][j]&4)&&id[i][j]!=id[i][j+1]&&ans2<=room[id[i][j]]+room[id[i][j+1]]) {
                if(ans2!=room[id[i][j]]+room[id[i][j+1]]) x2=i,y2=j;
                else if(j<y2) y2=j,x2=i;//West
                else if(j==y2 && i>x2) x2=i;//South
                ans2=room[id[i][j]]+room[id[i][j+1]];
            }//东墙
        }
```

在这里ta分开枚举了。

而我们因为有~~人工优势~~：**二进制的墙改成了数组！**

所以……

```
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=2;k<=3;k++)//二是北三是东
				if(mp[i][j][k]==1&&b[i][j]!=b[i+dx[k-1]][j+dy[k-1]])
					ans=max(ans,a[b[i][j]]+a[b[i+dx[k-1]][j+dy[k-1]]]);//选取可行的得到房间最大的墙的房间大小，房间大小即为a数组
                             
``` 

好了难关过去了，下面是一个著名的坑：

没有SPJ。

### 第四问：重新枚举找出墙的位置

难度：高

仔细分析题目后发现：

**有多解时选最靠西的，仍然有多解时选最靠南的。同一格子北边的墙比东边的墙更优先。**

//~~这不是题目原话吗~~

但是！

判断下面两面墙谁的优先级大：

![](https://cdn.luogu.com.cn/upload/pic/50486.png)

比较不出来了吧。

没有人告诉过你同一格子东边的墙和南边的墙谁大，你去推一推也推不出来。

所以在这我~~通过下了数据点~~告诉大家：

**在上图中蓝墙比红墙优先级大。**

但是，你的程序会这么想吗？

所以别看下面循环奇奇怪怪，是有他一定的道理的。

```
	for(int j=1;j<=m;j++)//先判东西
		for(int k=2;k<=3;k++)//再判方向
			for(int i=n;i>=1;i--)//最后判南北
				if(mp[i][j][k]==1&&b[i][j]!=b[i+dx[k-1]][j+dy[k-1]]&&a[b[i][j]]+a[b[i+dx[k-1]][j+dy[k-1]]]==ans){//碰到的墙第一个可行
					printf("%d %d ",i,j);
					if(k==3)printf("E\n");//三是东
					if(k==2)printf("N\n");//二是北
					return 0;
					}
}
```

好了，思路讲完了，下面上完整代码（别抄！）：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,mp[51][51][5],b[51][51],d,s,a[2501],ans;
const int dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
void t(int i,int j){
	b[i][j]=s;
	for(int k=1;k<=4;k++)
		if(mp[i][j][k]==0&&b[i+dx[k-1]][j+dy[k-1]]==0)a[s]++,t(i+dx[k-1],j+dy[k-1]);
}
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&d);
			if(d%2==1)mp[i][j][1]=1;
			d/=2;
			if(d%2==1)mp[i][j][2]=1;
			d/=2;
			if(d%2==1)mp[i][j][3]=1;
			d/=2;
			if(d%2==1)mp[i][j][4]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(b[i][j]==0)s++,a[s]=1,t(i,j);
	printf("%d\n",s);
	for(int i=1;i<=s;i++)
		ans=max(ans,a[i]);
	printf("%d\n",ans);
	ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=3;k<=4;k++)
				if(mp[i][j][k]==1&&b[i][j]!=b[i+dx[k-1]][j+dy[k-1]])
					ans=max(ans,a[b[i][j]]+a[b[i+dx[k-1]][j+dy[k-1]]]);
	printf("%d\n",ans);
	for(int j=1;j<=m;j++)
		for(int k=2;k<=3;k++)
			for(int i=n;i>=1;i--)
				if(mp[i][j][k]==1&&b[i][j]!=b[i+dx[k-1]][j+dy[k-1]]&&a[b[i][j]]+a[b[i+dx[k-1]][j+dy[k-1]]]==ans){
					printf("%d %d ",i,j);
					if(k==3)printf("E\n");
					if(k==2)printf("N\n");
					return 0;
					}
}
```

---

## 作者：Drifterming (赞：9)

```cpp
/*
个人感觉是一道不错的模拟+搜索的题，做了一上午，做两小时，调一小时，有一些细节需要注意。

ans_sum:房间数量
ans_max:最大的房间的面积
ans_area:把墙推倒后最大的房间的面积
ans_x:推墙的格子的横坐标
ans_y:推墙的格子的纵坐标
ans_dir:推墙的方向 

按题目的意思建一个图，每个房间格占一格，墙占一格。
画出来是这个样子：
     #
    #O#
     # 
四个角上不用标记为墙，因为拆墙的方向都是平行于x、y轴的。 

前两问：
    ①把图建起来以后跑dfs，把各个房间格连成联通块，变成一个房间。
    ②for循环寻找那些没有被连成房间的块，然后从这个点dfs，同时让房间数++。
    ③dfs的时候记录当前联通块的面积cnt，以及当前格子属于哪个联通块
    ④for循环一遍，dfs的次数就是房间的数量，最大面积ans_max在每次dfs后取max，这样前两问就解决了。

后两问：
    ①因为题目要求尽量靠西靠南，所以让行i从大到小循环，让列j从小到大循环。
    ②将墙推倒能对答案产生贡献的情况当且仅当墙两边的格子不属于同一个房间。 
    ③如果ans_area小于将当前的墙打穿后两个房间的面积的和，那么直接更新答案。
    ④如果ans_area等于将当前的墙打穿后两个房间的面积的和，那么就让ans_y尽量小。
*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<algorithm>
using namespace std;

int n,m,a,cnt,ans_sum,ans_max,ans_area,ans_x,ans_y;
char ans_dir;
int area[2505];
bool flag[200][200],visited[200][200];
int x_to[4]={0,-2,0,2},y_to[4]={-2,0,2,0};
int xx_to[4]={0,-1,0,1},yy_to[4]={-1,0,1,0};
struct BLO
{
    int area,belong;
}blo[200][200];

int read()
{
    char c=getchar();int num=0;
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar())
        num=num*10+c-'0';
    return num;
}

void west(int x,int y)	//西边有墙 
{
    flag[x][y-1]=0;
}

void north(int x,int y)	//北边有强 
{
    flag[x-1][y]=0;
}

void east(int x,int y)	//东边有墙 
{
    flag[x][y+1]=0;
}

void south(int x,int y)	//南边有墙 
{
    flag[x+1][y]==0;
}

void work(int a,int x,int y)	//当前格子四周墙的位置 
{
    //每个方向的墙设置完后让a减去其对应的值，方便设置其他方向的墙 
    if(a>=8)	//和大于等于8的南边一定有墙 
        south(x,y),a-=8; 
    if(a>=4)	//和大于等于4的东边一定有墙 
        east(x,y),a-=4;
    if(a>=2)	//和大于2的北边一定有墙 
        north(x,y),a-=2;
    if(a==1)	//和等于1的西边一定有墙 
        west(x,y),a-=1;
}

bool judge(int x,int y)		//判断能不能联通 
{
    if(x<1||x>m||y<1||y>n||visited[x][y])
        return false;
    return true;
}

void dfs(int x,int y)
{
    ++cnt;	//当前联通块的面积 
    blo[x][y].belong=ans_sum;	//当前格子属于哪个联通块 
    visited[x][y]=1;	//标记为已联通 
    for(int i=0;i<4;++i)	//向其他四个方向扩展 
    {
        int xx=x+x_to[i],yy=y+y_to[i];
        if(judge(xx,yy))
            if(flag[x+xx_to[i]][y+yy_to[i]])	//要扩展的方向没有墙隔着 
                dfs(xx,yy);
    }
}

int main()
{
    memset(flag,1,sizeof(flag));
    n=read(),m=read();
    n=n*2-1,m=m*2-1;	//矩形的大小，因为房间和墙都占格子，所以*2 
    for(int i=1;i<=m;++++i)
        for(int j=1;j<=n;++++j)
        {
            a=read();
            work(a,i,j);	//设置当前格子四周的墙的位置 
        }
    for(int i=1;i<=m;++++i)
        for(int j=1;j<=n;++++j)
        {
            if(!visited[i][j])		//不在别的联通块里，找到一个新的房间 
            {
                ++ans_sum;	//第一问：房间数量++ 
                cnt=0;	//房间面积清零 
                dfs(i,j);
                area[ans_sum]=cnt;	//新的房间的面积 
                ans_max=max(ans_max,cnt);	//第二问：最大房间的面积 
            }
        }
    for(int i=1;i<=m;++++i)		//让每一个格子的面积等于它属于的房间的面积 
        for(int j=1;j<=n;++++j)
        {
            blo[i][j].area=area[blo[i][j].belong];
        }
    ans_y=999999999;
    for(int i=m;i>=1;----i)
        for(int j=1;j<=n;++++j)
        {
            //北面的墙优先 
            if(blo[i][j].belong!=blo[i-2][j].belong)	//要对答案产生贡献，必须两个格子不是同一个房间的 
            {
                if(ans_area<blo[i][j].area+blo[i-2][j].area)	//能更新推完墙后最大房间的面积ans_area 
                {
                    ans_x=i,ans_y=j,ans_dir='N';
                    ans_area=blo[i][j].area+blo[i-2][j].area;
                }
                else if(ans_area==blo[i][j].area+blo[i-2][j].area)	//不能跟新面积，判断是否能更新位置 
                {
                    if(ans_y>j)	//让位置尽量靠西 
                    {
                        ans_x=i,ans_y=j,ans_dir='N';
                        ans_area=blo[i][j].area+blo[i-2][j].area;
                    }
                }
            }
            if(blo[i][j].belong!=blo[i][j+2].belong)
            {
                if(ans_area<blo[i][j].area+blo[i][j+2].area)
                {
                    ans_area=blo[i][j].area+blo[i][j+2].area;
                    ans_x=i,ans_y=j,ans_dir='E';
                }
                else if(ans_area==blo[i][j].area+blo[i][j+2].area)
                {
                    if(ans_y>j)
                    {
                        ans_area=blo[i][j].area+blo[i][j+2].area;
                        ans_x=i,ans_y=j,ans_dir='E';
                    }
                    
                }
            }
        }
    printf("%d\n",ans_sum);
    printf("%d\n",ans_max);
    printf("%d\n",ans_area);
    printf("%d %d %c\n",(ans_x+1)>>1,(ans_y+1)>>1,ans_dir);
    return 0;
}
```

---

## 作者：aZhouyiyulg1 (赞：4)

这题搞了我3H，其实回想起来也就是BFS加模拟（DFS也行）

翻到据老的判断墙的那里，其实不用枚举，用二进制存储即可
```
  while(cc)
	     {
	     	a[i][j][l]=cc%2;
	     	cc/=2;
			l--;
		 }
```


一二问dfs扫房间的数量和最大房间不是很难，像水洼那题，只要判断那里没墙走那边，顺便记下图形面积。（染色）
```
int bfs(int x,int y)
{
	int xx,yy,qq[2500],tt[2500],t=1,h=0;
	qq[1]=x;
	tt[1]=y;
	a[x][y][0]=ans;//记录它与谁一组 
	while(t>h)
	{
		h++;
		for(int i=1;i<=4;i++)
		{	
		    xx=qq[h]+b[i];
		    yy=tt[h]+c[i];
			if(xx>0&&xx<=m&&yy>0&&yy<=n)
			  if(a[xx][yy][0]==0&&a[qq[h]][tt[h][i]==0)
			  {
			    t++;
				qq[t]=xx;
				tt[t]=yy;
				a[xx][yy][0]=ans;
			  }                                                                   
		}
	}
	maxl=max(t,maxl);//最大值
	return t;//返回该房间的面积
}        
```


三四问本蒟蒻用了2H，题意的魔鬼性质，先西后南，所以
```
  for(int i=1;i<=n;i++)
    for(int j=m;j>=1;j--)
```
(两边循环不能换）！！！

然后枚举可能的条件，取最大值与找出最佳选项。注意：先北后东（推墙）

——————————————————————————————————————
```
#include<bits/stdc++.h>
using namespace std;
int a[100][100][6],k[100][100][6],n,m,ans,maxl;
//a[i][j][0]为哪一组,a[i][j][1--4]为 墙的情况 
int b[5]={0,1,0,-1,0};
int c[5]={0,0,1,0,-1};
int d[100][100];//坐标格所在的房间的面积 
int bfs(int x,int y)
{
	int xx,yy,qq[100],tt[100],t=1,h=0;//广搜
	qq[1]=x;
	tt[1]=y;
	a[x][y][0]=ans;//记录它与谁一组 
	while(t>h)
	{
		h++;
		for(int i=1;i<=4;i++)
		{	
		    xx=qq[h]+b[i];
		    yy=tt[h]+c[i];
			if(xx>0&&xx<=m&&yy>0&&yy<=n)
			  if(a[xx][yy][0]==0&&a[qq[h]][tt[h][i]==0)
			  {
			    t++;
				qq[t]=xx;
				tt[t]=yy;
				a[xx][yy][0]=ans;//染色
			  }                                                                   
		}
	}
	maxl=max(t,maxl);//最大值
	return t;//返回该房间的面积
}        
int main()

{
	int cc;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	  for(int j=1;j<=n;j++)
	  {
	     cin>>cc;
	     a[i][j][0]=0;
	     int l=4;
	     while(cc)
	     {
	     	a[i][j][l]=cc%2;
	     	cc/=2;
			l--;
		 }//把数化为二进制存储
	   } 
	for(int i=1;i<=m;i++)
	  for(int j=1;j<=n;j++)//染色，BFS 
	  {
         if(a[i][j][0]==0)
		 {
	    	ans++;        
	    	int t=bfs(i,j);
	    	for(int ii=1;ii<=m;ii++)
	    	{
	    	  for(int jj=1;jj<=n;jj++)
	    	  {
	    	  	if(a[ii][jj][0]==ans)
	    	  	{
	    	  		d[ii][jj]=t;
				  }
		      }
			}
		 }
	  }
		cout<<ans<<endl;
		cout<<maxl<<endl;
		int maxn=0,idx,idy,q,t;
	    for(int j=1;j<=n;j++)//三四问
	    {	
	    	for(int i=m;i>=1;i--)//毒瘤，由于题意是先西再南 所以这样 
	    	{
				if(a[i][j][3]&&i!=1)//小心越界 
	    		{
	    			if(a[i-1][j][0]!=a[i][j][0])//不要这一步小心之前已经被打通了 
					{
					  t=d[i-1][j]+d[i][j];// 和（可以被打通） 
	    			  if(t>maxn)
	    			  {  
	    				maxn=t;
	    				idx=i;
	    				idy=j;
	    				q=0;//当此值比最大值大时，记录下来，其中q=0为北，q=1为东 
					  }
					}
				}
				if(a[i][j][2]&&j!=m)//与在判北时同理，注意：先判北，后判东 
				{
				 //   cout<<"f "<<i<<"　"<<j<<endl; 
					if(a[i][j][0]!=a[i][j+1][0]) 
					{
					  t=d[i][j+1]+d[i][j];
					  if(t>maxn)
					  {  
						maxn=t;
						idx=i;
						idy=j;
						q=1;
					  }
				    }
				}
			}
		}
	    cout<<maxn<<endl;
	    cout<<idx<<" "<<idy<<" ";
		if(q==0) cout<<"N";
		else cout<<"E"; //华丽结束 
		抄袭党注意，此程序有几个小bug，但bug不是核心代码 
 } 



---

## 作者：青灯夜游 (赞：4)

首先，这题要求输出多个答案，他们分别是
1.初始房间数目
2.初始的最大房间的大小
3.移除一面墙后所能得到的最大房间的大小
4.移除后能够得到最大新房间的墙
仔细分析后，我们可以把这四个问题翻译成以下问题

question 1:联通块数量
question 2:最大联通块的大小
question 3:移除一处障碍后能够得到新的最大联通块的大小
question 4:移除后能够得到新的最大联通块的障碍

很明显，对于question 1，我们只需要用广搜记录就可以了

question 2其实也可以在求完每一个联通块时，将该联通块的大小与max_room比较一下(一开始max_room设为0)，如果更大就将max_room更新为该联通块的大小.

question 3，这个稍微麻烦一点点.首先我们考虑如何拆墙，其实很简单，对于城堡中的每一个小矩形，题目要求我们先考虑推掉北边的墙再考虑推掉东边的墙.
如果它北边有墙,并且它不是城堡最北边的小矩形(边界判断)，则我们先把它北边的墙推掉，再以该小矩形为起点进行广搜求联通块，求完后再看能不能更新max_new_room的值.然后把北边的墙建起来，再考虑推掉东边的墙的情况，方法与推北边的墙同理,只是边界判断稍微变化了一下而已.题目中要求，如有多解，则输出最西边的墙，若还有多解，则输出最南边的墙.所以我们应该按照从南到北，从西到东的顺序枚举小矩形搜索,这样的顺序能够保证搜到的解一定是满足题目要求的.

而对于question 4，完全可以在解question 3的时候顺便记录下来，这里就不多做赘述了

最后再讲一讲代码实现中的一些细节,首先就是如何对输入的 n乘m 的表示城堡内墙壁组成的数列矩阵进行处理，根据题目中给出的1对应西边有墙，2对应北边有墙等等标准，我们枚举一些数据可以发现，每个1到15的数字都对应一种墙壁的组成情况(如11代表北，西，南边有墙). 然后我们可以用bool 数组 wall[i][j][k]表示在(i,j)的位置的k方向有无墙(有则为true，无则为false)，在代码里我定义k=0表示北方向，k=1表示东方向，k=2表示南方向,k=3表示西方向.由于wall数组里的k如此定义，所以在广搜时用到的方向数组d[k]应该也按照上面的k的标准进行初始化.
还有，在解决question 3和question 4时记得每次都要清空队列
```
#include<bits/stdc++.h>
using namespace std;
const int N=50+5;
int d[4][2]=
{
    {-1,0},//北 
    {0,1},//东
    {1,0},//南
    {0,-1}//西 
};
int queue1[N*N][2],room_num,max_room,max_new_room,key_wall_x,key_wall_y;
char key_wall;
bool expend[N][N],wall[N][N][4];
inline int read()
{
    int res=0,flag=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') flag=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        res=(res<<3)+(res<<1)+ch-'0';
        ch=getchar();
    }
    return res*flag;
}
inline void write(int x)
{
    if(x/10) write(x/10);
    putchar(char(x%10+'0'));
}
inline void transform(int x,int y,int direction)
{
    if(direction==1) wall[x][y][3]=true;
    if(direction==2) wall[x][y][0]=true;
    if(direction==3) wall[x][y][0]=wall[x][y][3]=true;
    if(direction==4) wall[x][y][1]=true;
    if(direction==5) wall[x][y][3]=wall[x][y][1]=true;
    if(direction==6) wall[x][y][0]=wall[x][y][1]=true;
    if(direction==7) wall[x][y][0]=wall[x][y][1]=wall[x][y][3]=true;
    if(direction==8) wall[x][y][2]=true;
    if(direction==9) wall[x][y][3]=wall[x][y][2]=true;
    if(direction==10) wall[x][y][0]=wall[x][y][2]=true;
    if(direction==11) wall[x][y][0]=wall[x][y][3]=wall[x][y][2]=true;
    if(direction==12) wall[x][y][2]=wall[x][y][1]=true;
    if(direction==13) wall[x][y][3]=wall[x][y][1]=wall[x][y][2]=true;
    if(direction==14) wall[x][y][0]=wall[x][y][1]=wall[x][y][2]=true;
    if(direction==15) wall[x][y][0]=wall[x][y][1]=wall[x][y][2]=wall[x][y][3]=true;
}
inline void BFS(int x,int y,int task,char down_wall)
{
    memset(queue1,0,sizeof(queue1));
    int head=0,tail=1;
    queue1[1][0]=x;queue1[1][1]=y;
    expend[x][y]=true;
    do
    {
        head++;
        int rx=queue1[head][0];
        int ry=queue1[head][1];
        for(register int i=0;i<=3;++i)
        {
            int dx=rx+d[i][0];
            int dy=ry+d[i][1];
            if(!expend[dx][dy]&&!wall[rx][ry][i])
            {
                expend[dx][dy]=true;
                ++tail;
                queue1[tail][0]=dx;
                queue1[tail][1]=dy;
            }
        }
    }while(head<tail);
    if(task==1) max_room=max(max_room,tail);
    if(task==2)
    {
        if(tail>max_new_room)
        {
            max_new_room=tail;
            key_wall_x=x;
            key_wall_y=y;
            key_wall=down_wall;
        }
    }
}
int main()
{
    int n,m,x;
    m=read();n=read();
    for(register int i=1;i<=n;++i)
     for(register int j=1;j<=m;++j)
     {
     	x=read();
     	transform(i,j,x);
     }
     
    for(register int i=1;i<=n;++i)
     for(register int j=1;j<=m;++j)
        if(!expend[i][j])
        {room_num++;BFS(i,j,1,'M');}//step 1 and step 2
    
    for(register int j=1;j<=m;++j)
     for(register int i=n;i>=1;--i)
     {
        if(wall[i][j][0]&&i!=1)//北面有墙 
     	{
     		memset(expend,false,sizeof(expend));
            wall[i][j][0]=false;
     		BFS(i,j,2,'N');
     		wall[i][j][0]=true;
        }
        if(wall[i][j][1]&&j!=m)//东面有墙 
        {
            memset(expend,false,sizeof(expend));
            wall[i][j][1]=false;
            BFS(i,j,2,'E');
            wall[i][j][1]=true;
        }
     }
    write(room_num);printf("\n");
    write(max_room);printf("\n");
    write(max_new_room);printf("\n");
    write(key_wall_x);printf(" ");write(key_wall_y);printf(" ");printf("%c",key_wall);
    return 0;
}
```

---

## 作者：Limit (赞：3)

我们憨厚的USACO主人公农夫约翰(Farmer John)以无法想象的运气,在他生日那天收到了一份特别的礼物：一张“幸运爱尔兰”（一种彩票）。结果这张彩票让他获得了这次比赛唯一的奖品——坐落于爱尔兰郊外的一座梦幻般的城堡！

喜欢吹嘘的农夫约翰立刻回到有着吹嘘传统的威斯康辛老家开始吹嘘了, 农夫约翰想要告诉他的奶牛们关于他城堡的一切。他需要做一些吹嘘前的准备工作：比如说知道城堡有多少个房间，每个房间有多大。另外，农夫约翰想要把一面单独的墙（指两个单位间的墙）拆掉以形成一个更大的房间。 你的工作就是帮农夫约翰做以上的准备，算出房间数与房间的大小。

城堡的平面图被划分成M*N(1 <=M,N<=50）个正方形的单位，一个这样的单位可以有0到4面墙环绕。城堡周围一定有外墙环绕以遮风挡雨。（就是说平面图的四周一定是墙。）

请仔细研究下面这个有注解的城堡平面图：

![这里写图片描述](https://img-blog.csdn.net/20180906214002572?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N4eV9fb3J6/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

友情提示，这个城堡的平面图是7×4个单位的。一个“房间”的是平面图中一个由“#”、“-”、“|”围成的格子（就是图里面的那一个个的格子）。比如说这个样例就有5个房间。（大小分别为9、7、3、1、8个单位（排名不分先后））

移去箭头所指的那面墙，可以使2个房间合为一个新房间，且比移去其他墙所形成的房间都大。（原文为：Removing the wall marked by the arrow merges a pair of rooms to make the largest possible room that can be made by removing a single wall. ）

城堡保证至少有2个房间，而且一定有一面墙可以被移走。

输入输出格式
输入格式：
第一行有两个整数：M和N 城堡的平面图用一个由数字组成的矩阵表示，一个数字表示一个单位，矩阵有N行M列。输入与样例的图一致。

每一个单位的数字告诉我们这个单位的东西南北是否有墙存在。每个数字是由以下四个整数的某个或某几个或一个都没有加起来的。

1: 在西面有墙

2: 在北面有墙

4: 在东面有墙

8: 在南面有墙

城堡内部的墙会被规定两次。比如说（1，1）南面的墙，亦会被标记为（2，1）北面的墙。

输出格式：
输出包含如下4行:

第 1 行: 城堡的房间数目。

第 2 行: 最大的房间的大小

第 3 行: 移除一面墙能得到的最大的房间的大小

第 4 行: 移除哪面墙可以得到面积最大的新房间。

选择最佳的墙来推倒。有多解时选最靠西的，仍然有多解时选最靠南的。同一格子北边的墙比东边的墙更优先。

用该墙的南邻单位的北墙或西邻单位的东墙来表示这面墙，方法是输出邻近单位的行数、列数和墙的方位（"N"（北）或者"E"（东））。

先用特殊处理将平面图还原，跟方便使用dfs

用dfs实现，枚举每个房间，求出最大面积，并保存，最后按题目要求求出最优解。
usaco城堡题解
以下为源代码：
```
const z:array[1..4,1..2]of -1..1=((0,-1),(-1,0),(0,1),(1,0));
      uu:array[1..4]of 1..4=(4,2,3,1);
var i,j,k,i1,j1,k1:longint;
    m,n,x,y,sum,int,int2,max:longint;
    a,b:array[-1..500,-1..500]of boolean;
    c,d:array[-1..500,-1..500]of longint;
    jz:array[0..100]of longint;
    u:array[0..10000]of longint;
    s:string;
    max_ch:longint;
    max_x,max_y:longint;
    sum2:longint;
    boo:array[1..4]of boolean;
procedure jz_(m:longint); //处理
begin
  jz[4]:=m div 8;
  m:=m mod 8;
  jz[3]:=m div 4;
  m:=m mod 4;
  jz[2]:=m div 2;
  m:=m mod 2;
  jz[1]:=m;
end;
procedure dfs_1(x,y:longint); //求出答案1,2
var i:longint;
begin
  if not b[x,y] then exit;
  b[x,y]:=false;
  if (x mod 2=1) and (y mod 2=1) then
  inc(int);
  for i:=1 to 4 do
  dfs_1(x+z[i,1],y+z[i,2]); //搜索
end;
procedure dfs_2(x,y:longint); //求出答案3
var i:longint;
begin
  if not b[x,y] then exit;
  b[x,y]:=false;
  c[x,y]:=u[int2];
  d[x,y]:=int2; //方便处理打洞位置
  for i:=1 to 4 do
  dfs_2(x+z[i,1],y+z[i,2]); //搜索
end;
begin
  read(m,n);
  s:='WNES';
  for i:=1 to n do
  for j:=1 to m do
  begin
    read(x);
    a[i*2-1,j*2-1]:=true;
    jz_(x);
    for k:=1 to 4 do
    begin
      if jz[k]=0 then
      a[i*2-1+z[k,1],j*2-1+z[k,2]]:=true;
    end;
  end;
  b:=a;
  {for i:=0 to n*2 do
  begin
    for j:=0 to m*2 do begin if not a[i,j] then write('#') else write(' '); end;
    writeln;
  end;}
  for i:=1 to n*2-1 do
  for j:=1 to m*2-1 do
  begin
    if b[i,j] then
    begin
    inc(int2);
    dfs_1(i,j);
    u[int2]:=int;
    if int>max then max:=int;
    int:=0;
    end;
  end;
  writeln(int2); // 房间数
  writeln(max); // 最大房间
  b:=a;
 { for i:=0 to n*2 do
  begin
    for j:=0 to m*2 do begin if not a[i,j] then write('#') else write(' '); end;
    writeln;
  end;
  writeln;}
  int2:=0;
  for i:=1 to n*2-1 do
  for j:=1 to m*2-1 do
  begin
    if b[i,j] then
    begin
    inc(int2);
    dfs_2(i,j);
    end;
  end;
  {for i:=0 to n*2 do
  begin
    for j:=0 to m*2 do write(c[i,j]);
    writeln;
  end;}
  max:=0;
  // 找到打洞处
  for j:=m downto 1 do
  for i:=1 to n do
  begin
    x:=i*2-1;
    y:=j*2-1;
    sum:=c[x,y];
    for i1:=3 downto 2 do
    begin
      if not a[x+z[i1,1],y+z[i1,2]] and (d[x+z[i1,1]*2,y+z[i1,2]*2]<>d[x,y]) then
      begin
      if (c[x+z[i1,1]*2,y+z[i1,2]*2]+sum>=max) then
      begin
      max:=c[x+z[i1,1]*2,y+z[i1,2]*2]+sum;
      for k1:=1 to 4 do boo[k1]:=false;
      max_x:=i;
      max_y:=j;
      max_ch:=i1;
      end;
      end;
    end;
  end;
  //
  writeln(max); // 打洞后最大房间
  writeln(max_x,' ',max_y,' ',s[max_ch]);
end.
```
声明：本人蒟蒻一枚。



---

## 作者：封禁用户 (赞：3)

# **此方法极为暴力，请做好心理准备**

我用了个极为暴力的邻接矩阵：bv[y1][x1][y2][x2]，标记从点（x1,y1）到(x2,y2)之间是否有墙。然后剩下的就和比较正常的解法一样了。

先用位运算构造墙，然后枚举所有没走过的点，让他们为起点使劲的bfs，无法再bfs下去后就把队列中存的所有点都标上编号和连通块的大小，这样就解决了子问题①②，然后我们自西向东，自南而北（这个遍历的顺序很重要！）的枚举点，看它的北边或东边是否有墙，如果有，看墙两边的是否属于同一个连通块（编号相同），是同一个连通块的话就算推墙的新大小，最后取一个最先出现并且最大的方案即可。

代码如下：

```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;
    unsigned char bv[52][52][52][52];//存墙的邻接矩阵
    int bnumber[52][52];//所属连通块的编号
    int sizes[52][52];//所属连通块的大小
    int quex[2600];
    int quey[2600];//手写的队列，最好别用queue
    unsigned char bvgrid[52][52];//标记点是否走过
    int lx[4]={1,-1,0,0};
    int ly[4]={0,0,1,-1};//每步移动的偏移
    int main(){
        int width,height;
        cin>>width>>height;
        for(int y=1;y<=height;y++){
            for(int x=1;x<=width;x++){
                int a;
                scanf("%d",&a);
                if(a&1){//西面有墙
                    bv[y][x][y][x-1]=bv[y][x-1][y][x]=1;
                }
                if(a&2){//北面有墙
                    bv[y][x][y-1][x]=bv[y-1][x][y][x]=1;
                }
                if(a&4){//东面有墙
                    bv[y][x][y][x+1]=bv[y][x+1][y][x]=1;
                }
                if(a&8){//南面有墙
                    bv[y][x][y+1][x]=bv[y+1][x][y][x]=1;
                }
            }
        }
        int gn=0;
        int maxn=-123456789;
        for(int yy=1;yy<=height;yy++){
            for(int xx=1;xx<=width;xx++){
                if(!bvgrid[yy][xx]){
                    bvgrid[yy][xx]=1;
                    int head=0;
                    int tail=2;
                    quex[1]=xx;
                    quey[1]=yy;
                    do{//bfs
                        head++;
                        for(int i=0;i<4;i++){
                            int ix=quex[head]+lx[i];
                            int iy=quey[head]+ly[i];
                            if(ix>0&&ix<=width&&iy>0&&iy<=height){
                                if(!bvgrid[iy][ix]){
                                    if(!bv[quey[head]][quex[head]][iy][ix]){//没有墙
                                        bvgrid[iy][ix]=1;
                                        quex[tail]=ix;
                                        quey[tail]=iy;
                                        tail++;//入队
                                    }
                                }
                            }
                        }
                    }while(head<tail);
                    int bn=tail-1;//连通块大小即为tail-1
                    for(int i=1;i<=bn;i++){
                        bnumber[quey[i]][quex[i]]=gn;
                        sizes[quey[i]][quex[i]]=bn;
```
}//把队列中的所有点标上所属连通块编号和大小
        
```cpp
                    maxn=max(maxn,bn);
                    gn++;
                }
            }
        }
        cout<<gn<<endl<<maxn<<endl;
        char fangxiang;
        maxn=-123456789;
        int bestx;
        int besty;
            for(int x=1;x<=width;x++){
                for(int y=height;y>=1;y--){//一定要按照这个顺序！不然会WA！
                if(bv[y][x][y-1][x]){
                    if(bnumber[y][x]!=bnumber[y-1][x]){
                    //北面有墙且不是一个连通块
                        int news=sizes[y][x]+sizes[y-1][x];
                        if(news>maxn){
                            maxn=news;
                            fangxiang='N';
                            bestx=x;
                            besty=y;
                        }
                    }
                }
                if(bv[y][x][y][x+1]){
                    if(bnumber[y][x]!=bnumber[y][x+1]){
                    //东面有墙且不是一个连通块
                        int news=sizes[y][x]+sizes[y][x+1];
                        if(news>maxn){
                            maxn=news;
                            fangxiang='E';
                            bestx=x;
                            besty=y;
                        }
                    }
                }
            }
        }
        printf("%d\n%d %d %c\n",maxn,besty,bestx,fangxiang);
        return(0);
}
```

---

## 作者：多米 (赞：2)

辛辛苦苦写了200行，一次次是错中终于AC了
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N=50+10;
const int fx[4]={0,-1,0,1};
const int fy[4]={-1,0,1,0};

int ans,sum,n,m,tot,xx,yy,len;
int vis[N][N],f[N][N],num[N][N];
// vis用来记录是否访问过
// f用来记录该房间的总房间的房间数
// 记录该房间是第几个房间 
char ch;

struct wall
{
	int k;
	int w[4];
}a[N][N];
// 房间的墙 
struct str
{
	int x;
	int y;
	int flag;
}edge[N*N*4];
// 最后要将所有可能的墙排序 

bool cmp(str p,str q)
{
	if(p.y!=q.y)return p.y<q.y;// 再按往西 
	if(p.x!=q.x)return p.x>q.x;// 先按往南 
	return p.flag<q.flag;
	// 1是东，0是北，北优先 
}

void east(int x,int y)
{
	edge[len].x=x;
	edge[len].y=y;
	edge[len].flag=1;
	return;
}

void western(int x,int y)
{
	// W(i,j)，转到E(i,j-1) 
	edge[len].x=x;
	edge[len].y=y-1;
	edge[len].flag=1;
	return;
}

void south(int x,int y)
{
	// S(i,j)，转到N(i+1,j) 
	edge[len].x=x+1;
	edge[len].y=y;
	edge[len].flag=0;
	return;
}

void north(int x,int y)
{
	edge[len].x=x;
	edge[len].y=y;
	edge[len].flag=0;
	return;
} 

void init(int s,int i,int j)
{
	if(s>7)
	{
		s-=8;
		a[i][j].w[3]=1;
	}
	else a[i][j].w[3]=0;
	if(s>3)
	{
		s-=4;
		a[i][j].w[2]=1;
	}
	else a[i][j].w[2]=0;
	if(s>1)
	{
		s-=2;
		a[i][j].w[1]=1;
	}
	else a[i][j].w[1]=0;
	if(s)a[i][j].w[0]=1;
	else a[i][j].w[0]=0;
	return;
}

void room(int x,int y)
{
	if(vis[x][y])return;
	if(x>n||x<1||y>m||y<1)return;
	vis[x][y]=1;
	sum++;// 联通块数量+1 
	for(int i=0;i<4;i++)
	{
		xx=fx[i]+x;
		yy=fy[i]+y;
		if(!a[x][y].w[i])// 如果之间没有墙 
			room(xx,yy);
	}
	return;
}

void room_max(int x,int y)
{
	if(f[x][y])return;
	if(x>n||x<1||y>m||y<1)return;
	f[x][y]=sum;// 把对应的房间附上此总房间的大小 
	num[x][y]=tot;// 把对应的房间编号 
	for(int i=0;i<4;i++)
	{
		xx=fx[i]+x;
		yy=fy[i]+y;
		if(!a[x][y].w[i])// 如果这之间没有墙 
			room_max(xx,yy);
	}
	return;
}

void work()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!vis[i][j])
			{
				sum=0;// 同第二行，寻找房间最大 
				tot++;// 房间总数 
				room(i,j);// 寻找联通块 
				ans=max(ans,sum);
				room_max(i,j);// 同第三，四，寻找最大相邻房间和删去的墙 
			}
	printf("%d\n%d\n",tot,ans);
	ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<4;k++)
			{
				xx=i+fx[k];
				yy=j+fy[k];
				if(xx>n||xx<1||yy>m||yy<1)continue;
				if(num[i][j]!=num[xx][yy])// 只有两个是不一样的房间 
				{
					sum=f[i][j]+f[xx][yy];
					if(ans<sum)// 如果此联通块大，那就选他 
					{
						len=0;// 删除所有的边 
						ans=sum;// 赋值 
					}
					if(ans==sum)// 如果面积一样 
					{
						len++;
						switch(k)
						{
							case 0:western(i,j);break;// 如果是西边的墙 
							case 1:north(i,j);break;// 如果是北边的墙 
							case 2:east(i,j);break;// 如果是东边的墙 
							case 3:south(i,j);break;// 如果是西边的墙 
							default:break;// 可有可无 
						}
					}
				}
			}
	printf("%d\n",ans);// 打印最大的两房联通面积 
	sort(edge+1,edge+1+len,cmp);// 给边排序 
	if(edge[1].flag)ch='E';
	else ch='N';// 判断 
	printf("%d %d %c",edge[1].x,edge[1].y,ch);// 打印横纵坐标 
	return;
}

void read()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j].k);
			init(a[i][j].k,i,j);// 把每堵墙建好 
		}
	return;
}

int main()
{
	read(); 
	work();
	return 0;
}
```

---

## 作者：Lolierl (赞：2)

//这题最核心的部分就在于东南西北的位运算，而前两个问题可以用较简单的深搜解决，顺便做一个简易的并查集，最后打掉墙的问题就可以做穷举，对于每个格子都可以（只要存在）打掉东、北两个方向的四堵墙，每堵墙的房间大小只需用墙两边的房间大小（事先存储好）加起来，再比个max即可。



    
    
    
    
    
        
```cpp
//代码：
#include<iostream>
#include<cstring>
using namespace std;
int x,y;
struct h
{
    int num;//
    int wall;//读入的每个格子的墙的数据
};
struct h a[51][51];
void dfs(int h,int l,int num)
{
    a[h][l].num=num;//并查集，打标记 
    if(!(a[h][l].wall&1)&&!(a[h][l-1].num))dfs(h,l-1,num);//位运算，如果有方向没有墙就深搜 
    if(!(a[h][l].wall&2)&&!(a[h-1][l].num))dfs(h-1,l,num);
    if(!(a[h][l].wall&4)&&!(a[h][l+1].num))dfs(h,l+1,num);
    if(!(a[h][l].wall&8)&&!(a[h+1][l].num))dfs(h+1,l,num);
    //深搜， 标记房间编号 
}
int main()
{
    cin>>y>>x;
    int t=0;
    for(int i=1;i<=x;i++)
        for(int j=1;j<=y;j++)
            cin>>a[i][j].wall;
    for(int i=1;i<=x;i++)
        for(int j=1;j<=y;j++)
            if(!a[i][j].num){t++;dfs(i,j,t);}
    int b[t+1];    
    memset(b,0,sizeof(b));
    for(int i=1;i<=x;i++)
        for(int j=1;j<=y;j++)
                b[a[i][j].num]+=1;  //算出房间大小 
    int maxn=b[1];
    for(int i=2;i<=t;i++)
        if(b[i]>maxn)maxn=b[i];
    cout<<t<<endl;
    cout<<maxn<<endl;
    //前两问 
    maxn=0;
    int h=0,l=0;
    char f;
    for(int j=1;j<=y;j++)//体现优先级 
        for(int i=x;i>=1;i--)//逐一穷举，试着打掉每一堵墙 
        {
            if(a[i][j].wall>=2)
                if(a[i][j].num!=a[i-1][j].num)
                    if(i-1>=0&&b[a[i][j].num]+b[a[i-1][j].num]>maxn)
                    {
                        maxn=b[a[i][j].num]+b[a[i-1][j].num];
                        h=i;l=j;
                        f='N';
                    }
            if(a[i][j].wall>=4)
                if(a[i][j].num!=a[i][j+1].num)
                    if(j+1<=y&&b[a[i][j].num]+b[a[i][j+1].num]>maxn)
                    {
                        maxn=b[a[i][j].num]+b[a[i][j+1].num];
                        h=i;l=j;
                        f='E';
                    }            
        }
        cout<<maxn<<endl<<h<<' '<<l<<' '<<f;  //后两问 
    return 0;
}

```

---

## 作者：ljk_Elaina (赞：1)

安利一下我的[博客](https://www.cnblogs.com/20170330john2005)

-----

这道题我一开始只会做前两问，因为前两问一个暴力宽搜就可以解决。

后两问，最开始并没有想到如何去做，后来一想，只要从下到上扫一遍，打一个擂台比较大小便解决了。


这道题数据很水，只有50 * 50 = 2500 ，99%不超空间和时间。

输入处理的问题见代码。

```cpp
	cin>>m>>n;
	for(int i=1; i<=n; i++) {  //输入要处理好！！
		for(int j=1; j<=m; j++) {
			cin>>wall;
			if(wall>=8) {  //南面 '0' -> 8
				wall-=8;
				have_wall[i][j][0]=true;
			}
			if(wall>=4) {  //东面 '1' -> 4
				wall-=4;
				have_wall[i][j][1]=true;
			}
			if(wall>=2) {  //北面 '2' -> 2
				wall-=2;
				have_wall[i][j][2]=true;
			}
			if(wall>=1) {  //西面 '3' -> 1
				wall-=1;
				have_wall[i][j][3]=true;
			}
		}
	}
```

### 问题的拆分

问题可以拆成两部分：
- $BFS$ 搜出房间的个数，大小，及编号（后面有用 …… ）。
- 双重循环逐一检查拆去一面墙，如果墙两边的编号不同，就把面积加起来，打擂台。

### 第一部分

#### 传统$BFS$

记录是否来过，没来过大小$++$。

在顺带记录房间号。

```cpp
void bfs(int x,int y) {
	area[num]=1;			//num全局变量，用来记录房间数
    						//area[]用来记录每个房间大小
                            //附成1是因为第一个房间也算（它在BFS中没有++）
	vis[x][y]=num;			//vis[]用来判断是否来过和房间号码
    						//如果是0，没来过，如果填过数字了，来过。
	pos head;				//第一个位置
	head.x=x;
	head.y=y;
	q.push(head);			//压入队列
	while(!q.empty()) {		//如果队列不为空，说明还有状态
		pos fa=q.front();	//取出队首
		q.pop();			//弹出队首
		for(int i=0; i<4; i++) {
        					//四个方向
			pos son;
			son.x=fa.x+dx[i];
			son.y=fa.y+dy[i];
			if(have_wall[fa.x][fa.y][i]||son.x>n||son.y>m||son.x<1||son.y<1||vis[son.x][son.y]>0) continue;
            				//判断在不在范围内，有没有墙拦着，有没有来过
			else {
				vis[son.x][son.y]=num;//标记来过
				area[num]++;//房间大小++
				q.push(son);//压入队列
			}
		}
	}
	max_area=max(max_area,area[num]);//打擂台
}
```

### 第二部分

#### 爆搜+打擂台

```cpp
for(int j=1; j<=m; j++) {	//两个循环调换过来会 WA!
	for(int i=n; i>=1; i--) {
		if(have_wall[i][j][2]) //北面优先(([2]为北面))
			if(vis[i][j]!=vis[i-1][j]) {
				int tmp=area[vis[i][j]]+area[vis[i-1][j]];
				//判断是不是一个房间，就把房间大小相加
				if(tmp>col_max) {  //如果比最当前对大还要大的话
					col_max=tmp;   //更新
					max_area_wall[0]=i;
                    //max_area_wall用来存被推掉的墙能（使新房间面积最大）的信息
					//[0]为横坐标，[1]为纵坐标，[2]为东面还是北面，北面为0，东面为1
                    max_area_wall[1]=j;
					max_area_wall[2]=0;
				}
			}
		if(have_wall[i][j][1])  //同上([1]为东面)
			if(vis[i][j]!=vis[i][j+1]) {
				int tmp=area[vis[i][j]]+area[vis[i][j+1]];
				if(tmp>col_max) {
					col_max=tmp;
					max_area_wall[0]=i;
					max_area_wall[1]=j;
					max_area_wall[2]=1;
				}
			}
	}
}
```

### 讲到这儿，应该会写了吧！

---

## 作者：thhhty (赞：1)

这里是作为一个蓝名蒟蒻（提交题解时间为准）的代码
主要思路就是用并查集判断是否在一个房间。。。
和前面的红名大犇们不同只花了20min?!
废话不多上代码~~（事实上说了很多废话了）~~
```c
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
struct node
{
	int fa,c;
	bool qiang[4];//0123:西北东南 
}a[56000];
int n,m;
int findfa(int x)
{
	if(x==a[x].fa)return x;
	else return a[x].fa=findfa(a[x].fa);
}
int xy(int x,int y){return m*(x-1)+y;}
int main()
{
	scanf("%d %d",&m,&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int x,XY=xy(i,j);
			scanf("%d",&x);
			if(x>=8){x-=8;a[XY].qiang[3]=true;}
			else a[XY].qiang[3]=false;
			if(x>=4){x-=4;	a[XY].qiang[2]=true;}
			else a[XY].qiang[2]=false;
			if(x>=2){x-=2;a[XY].qiang[1]=true;}
			else a[XY].qiang[1]=false;
			if(x>=1){x-=1;a[XY].qiang[0]=true;}
			else a[XY].qiang[0]=false;
			a[XY].fa=XY;
			a[XY].c=1;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=1;j--)//这里选择从上到下，右到左(其实方向问题应该不大，开始打算和拆墙放到一起的。。后来懒得想就分开了)
		{
			int XY=xy(i,j);
			if(j!=m)//能走右边的话
			{
				if(a[XY].qiang[2]==false)
				{
					int fax=findfa(XY),fay=findfa(XY+1);
					if(fax!=fay)//把两个格子弄到一起
					{
						a[fax].fa=fay;
						a[fay].c+=a[fax].c;a[fax].c=0;//这就成为了一个新的房间
					}
				}
			}
			if(i!=1)//判断能不能和上面的格子弄成房间
			{
				if(a[XY].qiang[1]==false)
				{
					int fax=findfa(XY),fay=findfa(XY-m);
					if(fax!=fay)
					{
						a[fax].fa=fay;
						a[fay].c+=a[fax].c;a[fax].c=0;
					}
				}
			}
		}
	}
	int max=0,ans=0;//打代码开始的时候是先试着弄前两个输出（本蒟蒻开始是没打算A的。。）(手动滑稽)
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int XY=xy(i,j);
			if(a[XY].fa==XY)
			{
				if(max<a[XY].c)max=a[XY].c;
				ans++;
			}
		}
	}
	printf("%d\n%d\n",ans,max);
	max=0;int maxx,maxy;bool bk;//F:东，T:北 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int XY=xy(i,j);
			if(i!=1)//先找北墙是因为ij相同时选择先更新的（下面都是i>max,j<max这样没有“=”）
			{
				int fax=findfa(XY),fay=findfa(XY-m);
				if(fax!=fay)//因为全局找过就不判断墙了，直接看在不在一个房间
				{
					int s=a[fax].c+a[fay].c;
					if(max<s)//大小优先
					{
						max=s;
						maxx=i;maxy=j;
						bk=true;
					}
					else if(max==s)
					{
						if(j<maxy)//先向西（j尽量小）
						{
							maxx=i;maxy=j;
							bk=true;
						}
						else if(j==maxy) 
						{
							if(i>maxx)//再向南(i尽量大)
							{
								maxx=i;maxy=j;
								bk=true;
							}
						}
					}
				}
			}	if(j!=m)
			{
				int fax=findfa(XY),fay=findfa(XY+1);
				if(fax!=fay)
				{
					int s=a[fax].c+a[fay].c;
					if(max<s)
					{
						max=s;
						maxx=i;maxy=j;
						bk=false;
					}
					else if(max==s)
					{
						if(j<maxy)
						{
							maxx=i;maxy=j;
							bk=false;
						}
						else if(j==maxy) 
						{
							if(i>maxx)
							{
								maxx=i;maxy=j;
								bk=false;
							}
						}
					}
				}
			}
		}
	}
	printf("%d\n",max);//输出
	printf("%d %d ",maxx,maxy);
	if(bk==false)printf("E\n");
	else printf("N\n");
	return 0;
}
```

---

## 作者：肖恩Sean (赞：1)

个人表示不理解各位大佬们的联通块，观察题目后感觉用并查集会更好做一些；

将不分隔的两个房间合并集合中，合并后房间的大小就是两个房间大小之和，集合个数就是房间个数；

拆墙合面积比较，不是所有之间有墙的相邻格子都不是同一个房间，但所有不是同一个房间的相邻格子之间一定有墙；

此外，对于房间四面有无墙的判断用二进制，可以参考下面几位大佬解析的或是我的代码；

详细解析在代码在代码注释里，在外面说不清楚


```cpp
#include<iostream>
#define MAXK 3000
using namespace std;
struct room{
    bool e,s,w,n;//e东，s南，w西，n北
    int father,area;//father父亲节点，area房间面积 
}a[MAXK];
int m,n;
int find(int x){//祖先搜索 
    return x==a[x].father?x:a[x].father=find(a[x].father);//路径压缩 
}
void to(int x,int y){
    int f1=find(x),f2=find(y);//找祖先 
    if (f1!=f2) a[f1].father=f2,a[f2].area+=a[f1].area;//并查集合并集合，将合并后房间大小赋值给祖先
    return;
}
void input(){//输入以及数组初始化 
    cin>>m>>n;
    int i,j,in;
    for (i=1;i<=n*m;i++){
        cin>>in;
        a[i].father=i; 
        a[i].area=1;
        a[i].w=in%2?1:0;//同if (in%2==1) a[i].w==1; else a[i].w==0; 
        in/=2;
        a[i].n=in%2?1:0;
        in/=2;
        a[i].e=in%2?1:0;
        in/=2;
        a[i].s=in%2?1:0;
    }
    return;
}
void work(){
    int i,j,total=0,ans=0,wall_x,wall_y;
    for (i=1;i<=n*m;i++){//无墙的位置进行合并集合，我这里用东和南的墙，也可以用别的墙 
        if (!a[i].e) to(i,i+1);//为什么不用边界特判？我就不信这房子四周没墙漏风的 
        if (!a[i].s) to(i,i+m);
    }
    for (i=1;i<=n*m;i++){
        a[i].area=a[find(i)].area;
        //顺便把房间的大小赋值回去，此时第i个区域所在房间大小就是a[i].area，等会就不用多次调用祖先的房间大小 
        if (a[i].area>ans) ans=a[i].area;//最大房间 
        if (a[i].father==i) total++;//房间个数 
    }
    char which_wall;//北墙或东墙 
    cout<<total<<endl;
    cout<<ans<<endl;
    ans=0;//处理一下用来存拆墙后最大房间 
    for (j=1;j<=m;j++)//重中之重，外层循环第j列，内层循环第i行，因为是先选列数里最靠西的，再选行数里最靠南的 
        for (i=n;i>0;i--){
            int k=(i-1)*m+j;//得到第i行第j列的序号 
            //先北后东 
            if (k>m&&find(k)!=find(k-m)&&a[k].area+a[k-m].area>ans){//边界判断，是否在一个房间判断（不一定有墙就不在同一个房间了哈） 
                ans=a[k].area+a[k-m].area;
                wall_x=i;
                wall_y=j;
                which_wall='N';
            }
            if (k%m!=0&&find(k)!=find(k+1)&&a[k].area+a[k+1].area>ans){
                ans=a[k].area+a[k+1].area;
                wall_x=i;
                wall_y=j;
                which_wall='E';
            }
        }
    cout<<ans<<endl;
    cout<<wall_x<<" "<<wall_y<<" "<<which_wall<<endl;
}
int main(){
    input();
    work();
    return 0;
}
```

---

## 作者：Itache (赞：1)

在这一题中鄙人是采用结构体来记录每个房间的四周的墙的情况；（讲句实话：我一开始还很纳闷为什么题目中给定的墙的标号为1,2,4,8，直到打时才发现1-15每一个数都代表墙的每一种情况）

本题一二问是最普通的联通块问题，鄙人在前面两问采用的是深搜，但是在深搜的同时最好将每一个房间所归属的联通块记录一下，并记录下每个联通块的大小，为第三四题打基础；

三四问实在一二问上建立的，因为题目上说了先西后南，在同一个房间中先北后东，所以只要遍历每一个房间的北墙和东墙（前提是有墙），并把墙对面的房间所在联通块的大小加上即可。

下面贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
const int maxn=60;
using namespace std;
struct node{
    int u,d,l,r;//u:up上墙；d:down下墙；l：left左墙;r:right右墙 
    node(){
        op=u=d=l=r=0;
    }
}a[600][600];
int n,m,p[600][600],q[600][600],w[36100];//p:记录房间是否遍历过；
//q:记录房间所在连通快编号，w：连通块大小 
int ui[4]={1,0,0,-1};
int vi[4]={0,-1,1,0},tot=0,ans=0;
struct qiang{
    int x,y;//墙的位置 
    char w;//方向 
    qiang(){
        x=y=0;
    }    
}wu[36100];
bool cmp(qiang x,qiang y){
    return x.y<y.y||(x.y==y.y&&x.x>y.x)||(x.x==y.x&&x.y==y.y&&x.w>y.w);
}
void search(int x,int y){//搜索时注意边界 
    q[x][y]=ans;
    tot++;
    if(!p[x+1][y]&&!a[x][y].d&&x+1<=n){
        p[x+1][y]=1;
        search(x+1,y);
    }
    if(!p[x-1][y]&&!a[x][y].u&&x-1>0){
        p[x-1][y]=1;
        search(x-1,y);
    }
    if(!p[x][y+1]&&!a[x][y].r&&y+1<=m){
        p[x][y+1]=1;
        search(x,y+1);
    }
    if(!p[x][y-1]&&!a[x][y].l&&y-1>0){
        p[x][y-1]=1;
        search(x,y-1);
    }
}
int main(){
    int maxx=0;
    scanf("%d%d",&m,&n);//注意这里先列后行 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int x;
            scanf("%d",&x);        
            if(x==1)
                a[i][j].l=1;
            else if(x==2)
                a[i][j].u=1;
            else if(x==3)
                a[i][j].l=a[i][j].u=1;
            else if(x==4)
                a[i][j].r=1;
            else if(x==5)
                a[i][j].l=a[i][j].r=1;
            else if(x==6)
                a[i][j].u=a[i][j].r=1;
            else if(x==7)
                a[i][j].l=a[i][j].r=a[i][j].u=1;
            else if(x==8)
                a[i][j].d=1;
            else if(x==9)
                a[i][j].l=a[i][j].d=1;
            else if(x==10)
                a[i][j].u=a[i][j].d=1;
            else if(x==11)
                a[i][j].u=a[i][j].l=a[i][j].d=1;
            else if(x==12)
                a[i][j].r=a[i][j].d=1;
            else if(x==13)
                a[i][j].l=a[i][j].r=a[i][j].d=1;
            else if(x==14)
                a[i][j].u=a[i][j].r=a[i][j].d=1;
            else if(x==15)
                a[i][j].u=a[i][j].l=a[i][j].d=a[i][j].r=1;
        }//这里是惊奇的输入记录是否有墙； 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(!p[i][j]){
                ans++;//联通块数量 
                tot=0;
                p[i][j]=1;
                search(i,j);
                w[ans]=tot;
                maxx=max(maxx,tot);//maxx:记录最大联通块大小 
            }
    printf("%d\n%d\n",ans,maxx);
    maxx=0,ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[i][j].r&&j+1<=m&&q[i][j]!=q[i][j+1]){//注意两个房间不能在
            //同一个联通块上 
                if(w[q[i][j+1]]+w[q[i][j]]>maxx){
                    ans=1;
                    wu[ans].x=i,wu[ans].y=j;
                    wu[ans].w='E';
                    maxx=w[q[i][j+1]]+w[q[i][j]];
                //    if(maxx==17)
                //        printf("%d %d %c\n",i,j,wu[ans].w);
                }
                if(w[q[i][j+1]]+w[q[i][j]]==maxx){
                    ans++;
                    wu[ans].x=i,wu[ans].y=j;
                    wu[ans].w='E';
                //    printf("%d %d %c\n",i,j,wu[ans].w);
                }
            }                
            if(a[i][j].u&&i-1>0&&q[i][j]!=q[i-1][j]){
                if(w[q[i-1][j]]+w[q[i][j]]>maxx){
                    ans=1;
                    wu[ans].x=i,wu[ans].y=j;
                    wu[ans].w='N';
                    maxx=w[q[i-1][j]]+w[q[i][j]];
                //    if(maxx==17)
                //        printf("%d %d %c\n",i,j,wu[ans].w);
                }
                if(w[q[i-1][j]]+w[q[i][j]]==maxx){
                    ans++;
                    wu[ans].x=i,wu[ans].y=j;
                    wu[ans].w='N';
                //    printf("%d %d %c\n",i,j,wu[ans].w);
                }
            }
        }
    sort(wu+1,wu+ans+1,cmp);//最后把所有可行的墙排一下序，并取第一个 
    printf("%d\n",maxx);
    printf("%d %d %c\n",wu[1].x,wu[1].y,wu[1].w);
    return 0;
}
```

---

## 作者：B1ueC4t (赞：1)

**这道题正解是广搜 + 枚举**

**先Bfs一遍找出所有的连通块  ， 存入数组里**

**然后再暴力枚举 ， 寻找不同连通块 ， 并且打擂台 ， 找最大合并的连通块数量（枚举时记住要按题目给定的顺序枚举，先从西到东，再从南到北）**

**不多说 ， 代码里有详细的注释233**


```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 60;
const int STEP = 50010;
const int u[5] = {0,0,-1,0,1};    /* 顺序 : 西北东南 */
const int v[5] = {0,-1,0,1,0}; 
int n,m,ans,maxl,mx,my,mt;
int num[MAXN][MAXN];    /* num[i][j] : i行j列的房间属于第num[i][j]个连通块 */ 
int flag[MAXN][MAXN];    /* flag[i][j] : i行j列的房间所在的连通块里有flag[i][j]个连通块 */
bool grid[5][MAXN][MAXN];    /* gird[k][i][j] : i行j列的房间的第k个房间有没有墙 */

struct node {
    int rx;    /* 存放横坐标 */
    int ry;    /* 存放纵坐标 */
} q[STEP];    /* 数组模拟队列 */

inline void read(int &x) {    /* 快速读入 */
    
    int num = 0 , negative = 0;
    char ch = getchar();
    
    while((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    
    if(ch == '-')    negative = 1;
    else    num = ch - '0';
    
    ch = getchar();
    
    while(ch >= '0' && ch <= '9') {
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    
    x = num;
    if(negative)
        x = -x;
    
}

inline void judge(int x , int y , int k) {    /* 手动特判第x行y列的房间里的房间数 */
    if(k == 1) {
        grid[1][x][y] = true;
        return ;
    }
    if(k == 2) {
        grid[2][x][y] = true;
        return;
    }
    if(k == 4) {
        grid[3][x][y] = true;
        return ;
    }
    if(k == 8) {
        grid[4][x][y] = true;
        return ;
    }
    if(k == 1+2) {
        grid[1][x][y] = grid[2][x][y] = true;
        return ;
    }
    if(k == 1+4) {
        grid[1][x][y] = grid[3][x][y] = true;
        return ;
    }
    if(k == 1+8) {
        grid[1][x][y] = grid[4][x][y] = true;
        return ;
    }
    if(k == 2+4) {
        grid[2][x][y] = grid[3][x][y] = true;
        return ;
    }
    if(k == 2+8) {
        grid[2][x][y] = grid[4][x][y] = true;
        return ;
    }
    if(k == 4+8) {
        grid[3][x][y] = grid[4][x][y] = true;
        return ;
    }
    if(k == 1+2+4) {
        grid[1][x][y] = grid[2][x][y] = grid[3][x][y] = true;
        return ;
    }
    if(k == 1+2+8) {
        grid[1][x][y] = grid[2][x][y] = grid[4][x][y] = true;
        return ;
    }
    if(k == 1+4+8) {
        grid[1][x][y] = grid[3][x][y] = grid[4][x][y] = true;
        return ;
    }
    if(k == 2+4+8) {
        grid[2][x][y] = grid[3][x][y] = grid[4][x][y] = true;
        return ;
    }
    if(k == 1+2+4+8) {
        grid[1][x][y] = grid[2][x][y] = grid[3][x][y] = grid[4][x][y] = true;
        return ;
    }
}

inline void Bfs(int x , int y) {    /* 广搜 */
    
    int head = 0 , tail = 1 , tot = 1;
    ans++;    /* 连通块数量 + 1 */
    q[tail].rx = x;
    q[tail].ry = y;
    flag[x][y] = 1;
    
    while(head < tail) {
        head++;    /* 去掉队头 */
        x = q[head].rx;    /* 记下队头横坐标 */
        y = q[head].ry;    /* 记下队头纵坐标 */
        for(int i=1; i<=4; i++) {    /* 枚举4个方向 */
            int newx = x + u[i];    /* 构造新的横坐标 */
            int newy = y + v[i];    /* 构造新的纵坐标 */
            if(newx<1 || newx>n || newy<1 || newy>m)    /* 必须在城堡里 */
                continue;
            if(!flag[newx][newy] && !grid[i][x][y]) {    /* 必须没被连通且能连通 */
                tot++;    /* 该连通块区域内数量 + 1 */
                tail++;    /* 队尾 + 1 , 存入队列 */
                q[tail].rx = newx;
                q[tail].ry = newy;
                flag[newx][newy] = 1;    /* 被连通 */
            }
        }
    }
    
    for(int i=1; i<=tail; i++) {
        num[q[i].rx][q[i].ry] = ans;    /* 存下当前连通块的标号 */
        flag[q[i].rx][q[i].ry] = tot;    /* 存下当前连通块房间的个数 */
    }
    
    maxl = max(maxl,tot);    /* 打擂台取最大值 */
    
}

inline void Search(int x , int y) {    /* 暴力枚举 */
    for(int i=1; i<=4; i++) {    /* 不多说 , 和Bfs的枚举一样 */
        int newx = x + u[i];
        int newy = y + v[i];
        if(newx<1 || newx>n || newy<1 || newy>m)
            continue;
        if(num[x][y] != num[newx][newy] && grid[i][x][y]) {    /* 属于不同连通块 , 且没墙 */
            if(flag[x][y] + flag[newx][newy] > maxl) {    /* 又是打擂台。。。 */ 
                maxl = flag[x][y] + flag[newx][newy];
                mx = x;
                my = y;
                mt = i;
            }
        }
    }
}

int main() {
    
    read(m) , read(n);
    for(int i=1; i<=n; i++) {
        for(int j=1,tmp; j<=m; j++) {
            read(tmp);
            judge(i,j,tmp);    /* 手动特判这一个格子里有几个墙 */
        }
    }
    
    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
            if(!flag[i][j])    /* 枚举没被搜过的房间 */
                Bfs(i,j);
    
    printf("%d\n%d\n",ans,maxl);
    
    maxl = 0;
    for(int j=1; j<=m; j++)    /* 按题目中的顺序枚举 , 从西到东 */
        for(int i=n; i>=1; i--)    /* 从南到北 */
            Search(i,j);
    
    printf("%d\n%d %d ",maxl,mx,my);
    if(mt == 1)    puts("W");
    if(mt == 2)    puts("N");
    if(mt == 3)    puts("E");
    if(mt == 4)    puts("S");
    
    return 0;
    
}
```

---

## 作者：AFOier (赞：1)

【解题思路】

这一题描述那么长，看上去挺难的。但是看了一下数据范围，1 <=M,N<=50，真小啊！于是果断用了深搜。在输入的时候，我用了一个三维数组：a[i][j][u]，其中i，j代表这是第几行第几列，而u代表的是这个格子的东、南、西、北。所以数组的大小是a[51][51][4]。以下为我做的输入代码片段1

```cpp
for(int i=1;i<=n;i++)
for(int j=1;j<=m;j++)
{
    cin>>s;
    if(s>=8)a[i][j][1]=1,s-=8;
    if(s>=4)a[i][j][0]=1,s-=4;
    if(s>=2)a[i][j][3]=1,s-=2;
    if(s>=1)a[i][j][2]=1;
}
```
在输入的时候，我直接用a数组记录了每一个格子的周围有没有墙。当u=0时，代表标记东面，u=1标记南面，u=2标记西面，u=3标记北面。这么做会让接下来的解题环节更加easy。
接下来解答问题。第一个问题是求出有多少个房间。我们就用深搜，在此附上代码片段2用来参考：

```cpp
int dfs(int x,int y)
{
    if(b[x][y]==1||x<=0||y<=0||x>n||y>m)return 0;
    ans++;
    b[x][y]=1;
    if(a[x][y][0]==0)dfs(x,y+1);
    if(a[x][y][1]==0)dfs(x+1,y);
    if(a[x][y][2]==0)dfs(x,y-1);
    if(a[x][y][3]==0)dfs(x-1,y);
}
```
很显然，b数组用来标记路径，就是说我们不能在一个房间里一直来回走，轻而易举地拿下第一问（第二问也顺便拿下了，见ans++，然后我下面做了一个找最大的。
接下来是后两问。其实这也可以说是同一个问题。因为数据真的太太太太小了，所以我机智地用了循环。

每个格子试两次，删掉北面的墙或删掉东面的墙，然后再深搜，注意深搜完了要还原暂时删掉的墙。见代码片段3

```cpp
for(int i=1;i<=n;i++)
for(int j=m;j>=1;j--)
{
    for(int i1=1;i1<=n;i1++)for(int j1=1;j1<=m;j1++)b[i1][j1]=0; //初始化b数组
    if(a[i][j][3]==1){a[i][j][3]=0;a[i-1][j][1]=0;ans=0; //如果北面有墙才要深搜
    dfs(i,j);
    if(ans>maxn||(ans==maxn&&yy>j||(ans==maxn&&yy==j&&xx<i))){xx=i;yy=j;fx='N';maxn=ans;}
    a[i][j][3]=1;a[i-1][j][1]=1;}
    for(int i1=1;i1<=n;i1++)for(int j1=1;j1<=m;j1++)b[i1][j1]=0; //初始化b数组
    if(a[i][j][0]==1){a[i][j][0]=0;a[i][j+1][2]=0;ans=0; //如果东面有墙才要深搜
    dfs(i,j);
    if(ans>maxn||(ans==maxn&&yy>j||(ans==maxn&&yy==j&&xx<i))){xx=i;yy=j;fx='E';maxn=ans;}
    a[i][j][0]=1;a[i][j+1][2]=1;}
}
```
这个片段里面还有一个要注意的，就是在你删掉东面的墙后，右边的格子的西面的墙也没了，北面同理
注意这里同一格子北边的墙比东边的墙更优先。所以我这个判断就是如果北边的结果==东边的结果，北边一定会优先，详细看条件ans>maxn||(ans==maxn&&yy>j||(ans==maxn&&yy==j&&xx<i))
然后输出，就AC了。

【代码】

```cpp
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
int n,m,a[61][61][4],b[61][61],s,maxn,ans,xx,yy;
char fx;
int dfs(int x,int y)
{
    if(b[x][y]==1||x<=0||y<=0||x>n||y>m)return 0;
    ans++;
    b[x][y]=1;
    if(a[x][y][0]==0)dfs(x,y+1);
    if(a[x][y][1]==0)dfs(x+1,y);
    if(a[x][y][2]==0)dfs(x,y-1);
    if(a[x][y][3]==0)dfs(x-1,y);
} //深搜找这个房间有多大
int main()
{
    cin>>m>>n;yy=10000;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        cin>>s;
        if(s>=8)a[i][j][1]=1,s-=8;
        if(s>=4)a[i][j][0]=1,s-=4;
        if(s>=2)a[i][j][3]=1,s-=2;
        if(s>=1)a[i][j][2]=1;
    }s=0;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        ans=0;
        if(b[i][j]==0)dfs(i,j),s++;
        maxn=max(maxn,ans);
    }ans=0;
    cout<<s<<endl<<maxn<<endl; //先求前两个答案并输出
    for(int i=1;i<=n;i++) //南边优先所以从北至南循环
    for(int j=m;j>=1;j--) //西边优先所以从东至西循环
    {
        for(int i1=1;i1<=n;i1++)for(int j1=1;j1<=m;j1++)b[i1][j1]=0;
        if(a[i][j][3]==1){a[i][j][3]=0;a[i-1][j][1]=0;ans=0;
        dfs(i,j);
        if(ans>maxn||(ans==maxn&&yy>j||(ans==maxn&&yy==j&&xx<i))){xx=i;yy=j;fx='N';maxn=ans;}
        a[i][j][3]=1;a[i-1][j][1]=1;}
        for(int i1=1;i1<=n;i1++)for(int j1=1;j1<=m;j1++)b[i1][j1]=0;
        if(a[i][j][0]==1){a[i][j][0]=0;a[i][j+1][2]=0;ans=0;
        dfs(i,j);
        if(ans>maxn||(ans==maxn&&yy>j||(ans==maxn&&yy==j&&xx<i)))//如果当前结果>当前最大值||（当前结果==当前最大值&&当前最大值的位置在当前结果的东面）||（当前结果==当前最大值&&当前最大值的y值=当前结果的y值&&当前最大值的位置在当前结果的北面{xx=i;yy=j;fx='E';maxn=ans;}//更换答案
        a[i][j][0]=1;a[i][j+1][2]=1;}
    }
    cout<<maxn<<endl<<xx<<" "<<yy<<" "<<fx<<endl; //输出
    return 0; //完美结束
}
```

---

## 作者：FrankLi0324 (赞：1)

其实连通块问题可以通过更6的并查集解决。

将相连的房间union后可以得到房间数和每个房间的大小，也就是得到了最大房间的大小。

这时可以将每个房间的大小填到每个格子里，然后枚举敲掉的墙壁。

如果相邻的两个房间的大小标记相加最大，就可以确认要敲掉的是这面墙。

枚举的循环顺序！！！注意循环顺序！！！注意循环顺序！！！！！！！！

'''cpp
/\*
ID: frankli15

PROB: castle

LANG: C++11

\*/


```cpp
#include<cstring>
#include<iostream>
using namespace std;
#define max 1000000
int width, height;
//wall to break down
int cx, cy; char ddir;
class Union_Find {
    int pntOf[max];
    int find(int c) {
        while (pntOf[c] != -1)
            c = pntOf[c];
        return c;
    }
    int size, cntrot;
    int *SizeOfEachRoom;
    int *SerialOfEachRoom;
```
public:




```cpp
    Union_Find(int s) :size(s) {
        memset(pntOf, 255, sizeof pntOf);
        SerialOfEachRoom = (int*)malloc(sizeof(int)*size);
    }
    int maxSetSize() {
        SizeOfEachRoom = (int*)malloc((sizeof(int))*size);
        for (int i = 0; i < size; i++)SizeOfEachRoom[i] = 0;
        for (int i = 0; i < size; i++) {
            SizeOfEachRoom[find(i)]++;
        }
        int Max = 0;
        for (int i = 0; i < size; i++)
            if (SizeOfEachRoom[i] > Max)Max = SizeOfEachRoom[i];
        return Max;
    }
    void expandArray() {
        for (int i = 0; i < size; i++) {
            if (!SizeOfEachRoom[i])
                SizeOfEachRoom[i] =
                SizeOfEachRoom[find(i)];
            SerialOfEachRoom[i] = find(i);
        }
    }
    int maxTwoSumSize() {
        int Max = 0;
        for (int i = 0; i < height; i++) {
            for (int j = width - 1; j >0; j--) {
                if (SerialOfEachRoom[i*width + j] != SerialOfEachRoom[i * width + j - 1])
                    if (SizeOfEachRoom[i*width + j] + SizeOfEachRoom[i*width + j - 1] >= Max) {
                        Max = SizeOfEachRoom[i*width + j] + SizeOfEachRoom[i*width + j - 1];
                        cx = i + 1, cy = j, ddir = 'E';
                    }
            }
        }
        for (int j = width - 1; j >= 0; j--) {
            for (int i = 0; i < height - 1; i++) {
                if (SerialOfEachRoom[i*width + j] != SerialOfEachRoom[(i + 1)*width + j])
                    if (SizeOfEachRoom[i*width + j] + SizeOfEachRoom[(i + 1)*width + j] >= Max) {
                        if (SizeOfEachRoom[i*width + j] + SizeOfEachRoom[(i + 1)*width + j] == Max) {
                            if (j + 1 > cy)continue;
                            if (j + 1 == cy && i + 2 < cx)continue;
                        }
                        Max = SizeOfEachRoom[i*width + j] + SizeOfEachRoom[(i + 1)*width + j];
                        cx = i + 2, cy = j + 1, ddir = 'N';
                    }
            }
        }
        return Max;
    }
    void Union(int a, int b) {
        int ap = find(a), bp = find(b);
        if (ap == bp)return;
        pntOf[bp] = ap;
    }
    int roots() {
        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (pntOf[i] == -1)cnt++;
        }
        cntrot = cnt;
        return cnt;
    }
};
Union_Find *taskone;
int dx[5] = { 0,-1,0,1,0 };
int dy[5] = { 0,0,-1,0,1 };
void readMap() {
    int infotemp;
    cin >> width >> height;
    taskone = new Union_Find(width*height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cin >> infotemp;
            for (int dir = 1; dir <= 4; dir++) {
                if (!(infotemp & (1 << (dir - 1))))
                    taskone->Union(
```
i\*width + j,
(i + dy[dir])\*width + (j + dx[dir]));

```cpp
            }
        }
    }
}
int main() {
    readMap();
    //t one
    cout << taskone->roots() << endl;
    //t two
    cout << taskone->maxSetSize() << endl;
    //t three
    taskone->expandArray();
    cout << taskone->maxTwoSumSize() << endl;
    //t four
    cout << cx << " " << cy << " " << ddir << endl;
}
'''
```

---

## 作者：Ayano (赞：1)

第一次做图论，有点棘手，感觉还是要思路清晰在可以过关啊


    
    
    
    
    
    
  
  
   
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int i,j;  
char pos;
int m,n,ansx,ansy;  
int col,roomA,roomB,roomC;          
int room[51][51];   //--房间     
int size[2501];     //--房间大小
int Smax;           
bool wall[51][51][4]; //--墙   
bool check[51][51];  //--检查是否访问过    
void init()  //--读入数据 
{
    cin>>m>>n;  
    int t;  
    for(i=1;i<=n;i++)        
        for(j=1;j<=m;j++)  
        {  
            cin>>t;  
            if (t>=8)
            {
                t-=8;
                wall[i][j][3]=1; //--南面有墙 
            }  
            if (t>=4)
            {
                t-=4;
                wall[i][j][2]=1; //--东面有墙 
            }  
            if (t>=2)
            {
                t-=2;
                wall[i][j][1]=1;//--北面有墙 
            }  
            if (t>=1)
            {
                t-=1;
                wall[i][j][0]=1;//--西面有墙 
            }  
        }
}
void dfs(int i,int j)  //--DFS来FLOODFILL 
{  
    if (room[i][j]==col) return;  
    check[i][j]=1;   //--已经搜过了 
    size[col]++;     //--计算该种颜色的房间大小 
    room[i][j]=col;  //--Floodfill 
    if(!wall[i][j][0])  dfs(i,j-1);  //--西边没墙 我们走西边 
    if(!wall[i][j][1])  dfs(i-1,j);  //--北面没墙 我们走北边 
    if(!wall[i][j][2])  dfs(i,j+1);  //--东面没墙 我们走东边 
    if(!wall[i][j][3])  dfs(i+1,j);  //--南边没墙 我们走南边 
}  
int main()  
{  
   init();
    for(i=1;i<=n;i++)  
        for(j=1;j<=m;j++)  
        {  
            if(check[i][j]==0)  
            {  
                col++;     
                dfs(i,j);
            }  
        }  
    for (i=1;i<=col;i++)
    {
        if (size[i]>Smax) Smax=size[i];//--求出最大的房间 
    }
    cout<<col<<endl;
    cout<<Smax<<endl;
    //--1,2 floodfill 3,4枚举 
    Smax=0; 
    for(i=1;i<=m;i++)  
        for(j=n;j>=1;j--)  
        {
            roomA=room[j][i];//--搜索房间 
            roomB=room[j-1][i];//--搜索房间北边的房间 
            roomC=room[j][i+1];//--搜索房间西边的房间 
            //--判断房间
            if (j>1 && wall[j][i][1]==1 && roomA!=roomB && size[roomA]+size[roomB]>Smax) 
               {
                   Smax=size[roomA]+size[roomB];
                   ansx=j;
                   ansy=i;
                   pos='N';
               }
            else if (i<m && wall[j][i][2]==1 && roomA!=roomC && size[roomA]+size[roomC]>Smax)
               {
                   Smax=size[roomA]+size[roomC];
                   ansx=j;
                   ansy=i;
                   pos='E';
               }
          }
          cout<<Smax<<endl<<ansx<<" "<<ansy<<" "<<pos;
    return 0;
}

```

---

## 作者：汇文客 (赞：1)

哦，墙原来与位运算有关，真心佩服楼上。

BFS+记忆化，注意枚举顺序。

```delphi

type ftype=array[1..4]of boolean;
const dx:array[1..4]of shortint=(1,0,-1,0);
      dy:array[1..4]of shortint=(0,1,0,-1);
var g,v:array[0..51,0..51]of integer;
    q:array[1..2510,1..2]of integer;
    s:array[1..2510]of integer;
    n,m,i,j,k,x,y,ans,max,h,t:integer;
function check(x,y,k:integer):boolean;//请无视这段，快去拜楼上
var df:ftype;
begin
  fillchar(df,sizeof(df),true);
  if(g[x,y]=1)or(g[x,y]=3)or(g[x,y]=5)or(g[x,y]=9)or(g[x,y]=7)
  or(g[x,y]=11)or(g[x,y]=13)or(g[x,y]=15)then df[4]:=false;
  if(g[x,y]=2)or(g[x,y]=3)or(g[x,y]=6)or(g[x,y]=10)or(g[x,y]=7)
  or(g[x,y]=11)or(g[x,y]=14)or(g[x,y]=15)then df[3]:=false;
  if(g[x,y]=4)or(g[x,y]=12)or(g[x,y]=5)or(g[x,y]=6)or(g[x,y]=7)
  or(g[x,y]=15)or(g[x,y]=13)or(g[x,y]=14)then df[2]:=false;
  if(g[x,y]=8)or(g[x,y]=9)or(g[x,y]=10)or(g[x,y]=11)or(g[x,y]=12)
  or(g[x,y]=14)or(g[x,y]=13)or(g[x,y]=15)then df[1]:=false;
  exit(df[k]);
end;

begin
  readln(m,n);
  for i:=1 to n do
  begin
    for j:=1 to m do
    begin
      read(g[i,j]);
      v[i,j]:=0;
    end;
    readln;
  end;
  max:=0;
  for i:=1 to n do
  for j:=1 to m do
  if v[i,j]=0 then
  begin
    inc(ans);
    v[i,j]:=ans;
    s[ans]:=1;
    h:=0;t:=1;
    q[1,1]:=i;
    q[1,2]:=j;
    while h<t do
    begin
      inc(h);
      for k:=1 to 4 do
      if check(q[h,1],q[h,2],k) then
      begin
        x:=q[h,1]+dx[k];
        y:=q[h,2]+dy[k];
        if(x>=1)and(x<=n)and(y>=1)and(y<=m)and(v[x,y]=0)then
        begin
          inc(t);inc(s[ans]);
          q[t,1]:=x;q[t,2]:=y;
          v[x,y]:=ans;//记忆化
        end;
      end;
    end;
    if max<s[ans] then max:=s[ans];
  end;
  writeln(ans);
  writeln(max);max:=0;
  for j:=1 to m do
  for i:=n downto 1 do
  for k:=3 downto 2 do
  begin
    x:=i+dx[k];
    y:=j+dy[k];
    if(x>=1)and(x<=n)and(y>=1)and(y<=m)and(v[x,y]<>v[i,j])then
    if max<s[v[x,y]]+s[v[i,j]] then
    begin
      max:=s[v[x,y]]+s[v[i,j]];
      h:=i;t:=j;
      ans:=k;
    end;
  end;
  writeln(max);
  write(h,' ',t,' ');
  case ans of
  2:writeln('E');
  3:writeln('N');
  end;
end.

```

---

## 作者：hahalidaxin2 (赞：1)

【思路】

Dfs。
观察题目：利用位运算能够构造wall[][][]。

首先用dfs求出连通块，对每一格上色并用cnt记录颜色数目即房间大小。

其次从南到北从东向西枚举格子，如果可以则尝试拆除北墙、东墙，找到最优拆除。


【代码】

```cpp

#include<iostream>
#include<cstring>
#define FOR(a,b,c) for(int a=(b);a<=(c);a++)
using namespace std;

const int maxn = 100;
const int dx[]={0,-1,0,1};
const int dy[]={-1,0,1,0};

int wall[maxn][maxn][4];
int G[maxn][maxn];
int c[maxn][maxn],colors,cnt[maxn*maxn];
int n,m;

inline bool inside(int x,int y) {
    return x>=1 && x<=n && y>=1 && y<=m;
}
void dfs(int x,int y)
{
    for(int i=0;i<4;i++) if(!wall[x][y][i])
    {
        int xx=x+dx[i] , yy=y+dy[i];
        if(inside(xx,yy) &&  !c[xx][yy]) {
            c[xx][yy]=colors;
            cnt[colors]++;
            dfs(xx,yy);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin>>m>>n;
    FOR(i,1,n) FOR(j,1,m)
       {
             cin>>G[i][j];
             for(int k=0;k<4;k++)
               if(G[i][j]&(1<<k)) wall[i][j][k]=1;
       }
    int max_s=0;
    FOR(i,1,n) FOR(j,1,m) {
        if(c[i][j]) continue;
        ++colors;
        c[i][j]=colors; cnt[colors]++;
        dfs(i,j);
        max_s=max(max_s,cnt[colors]);
    }
    cout<<colors<<"\n"<<max_s<<"\n";
    
    char op; int ans_x,ans_y,ans=0;
    FOR(j,1,m) for(int i=n;i;i--)
    {
        if(i>1 && wall[i][j][1] && c[i][j]!=c[i-1][j]) {
            if(cnt[c[i-1][j]]+cnt[c[i][j]]>ans) {
                ans=cnt[c[i-1][j]]+cnt[c[i][j]];
                ans_x=i , ans_y=j , op='N';
            }
        }
        if(j<m && wall[i][j][2] && c[i][j]!=c[i][j+1]) {
            if(cnt[c[i][j+1]]+cnt[c[i][j]]>ans) {
                ans=cnt[c[i][j+1]]+cnt[c[i][j]];
                ans_x=i , ans_y=j , op='E';
            }
        }
    }
    cout<<ans<<"\n"<<ans_x<<" "<<ans_y<<" "<<op;
    return 0;
}

```（c/c++）

---

## 作者：wenkaijie (赞：1)

### 为什么大家都喜欢用BFS呢？？？
### 多麻烦！！！
### 能用DFS干吗用BFS？？？
# 思路：
对于输出前两行，就是一个赤裸裸的[联通分块](https://www.luogu.com.cn/problem/U102262)问题嘛！
对于输出后两行，暴力枚举就行了！
直接上代码
# 禁止抄袭！！！(麻烦洛谷严加看管！)
```cpp
# include<bits/stdc++.h>//万能头
using namespace std;
bool a[51][51][5];//记录每个格子是否有墙
int n,m,room[2501],cnt;//记录房间大小和个数
int maxr=0;//记录最大值
c[51][51];//记录每个格子的出发点
d[51][51];//记录每个格子所在房间大小
bool b[51][51];//防止重复计数
int ans=0;//移除一面墙能得到的最大的房间的大小
int ansx,ansy;//最后一行的输出
char ansf;//最后一行的输出
void dfs(int x,int y,int i)//深搜
{
	if(x>n || y>m || x<1 || y<1 || b[x][y])
		return ;
	c[x][y]=i;
	room[cnt]++;
	b[x][y]=1;
	if(a[x][y][1]==0)
		dfs(x,y-1,i);
	if(a[x][y][2]==0)
		dfs(x-1,y,i);
	if(a[x][y][3]==0)
		dfs(x,y+1,i);
	if(a[x][y][4]==0)
		dfs(x+1,y,i);
}
int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin>>m>>n;//题目很坑！先来列再来行！
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int p;
			cin>>p;
        //位运算
			if(p&1)
				a[i][j][1]=1;
			if(p&2)
				a[i][j][2]=1;
			if(p&4)
				a[i][j][3]=1;
			if(p&8)
				a[i][j][4]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(b[i][j]==0)
			{
				cnt++;
				dfs(i,j,cnt);
				maxr=max(maxr,room[cnt]);
			}//前两行的输出
  	//开始暴力枚举！
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			d[i][j]=room[c[i][j]];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
        //北面的墙
			if(a[i][j][2] && i!=1 && c[i][j]!=c[i-1][j])
			{
				if(ans<d[i][j]+d[i-1][j])
				{
					ans=d[i][j]+d[i-1][j];
					ansx=i;
					ansy=j;
					ansf='N';
				}
				if(ans==d[i][j]+d[i-1][j])
				{
					if(j<ansy)
					{
						ansx=i;
						ansy=j;
						ansf='N';
					}
					if(j==ansy && i>=ansx)
					{
						ansx=i;
						ansf='N';
					}
				}
			}
        //东面的墙
			if(a[i][j][3] && j!=m && c[i][j]!=c[i][j+1])
			{
				if(ans<d[i][j]+d[i][j+1])
				{
					ans=d[i][j]+d[i][j+1];
					ansx=i;
					ansy=j;
					ansf='E';
				}
				if(ans==d[i][j]+d[i][j+1])
				{
					if(j<ansy)
					{
						ansx=i;
						ansy=j;
						ansf='E';
					}
					if(j==ansy && i>ansx)
					{
						ansx=i;
						ansf='E';
					}
				}
			}
		}
	//输出
	cout<<cnt<<endl;
	cout<<maxr<<endl;
	cout<<ans<<endl;
	cout<<ansx<<' '<<ansy<<' '<<ansf;
}
```


---

## 作者：Grussg (赞：1)

# Part One 前置&注意的点
------------
### [题面戳这里](https://www.luogu.org/problem/P1457)

是一道很裸的Bfs题。不过一些细节之处，真的可以锻炼（~~搞人心态~~）人的耐心和细心程度。

另：进入[博客](https://134876.blog.luogu.org/p1457-solution)食用更佳

##  1.1 识别

先看看怎么处理那一边有墙

把对应数字在二进制下处理

1: 在西面有墙 **1->1**   

2: 在北面有墙 **2->10** 

4: 在东面有墙 **4->100**   

8: 在南面有墙 **8->1000** 

**由此可知**




   数字 | 方向 | 二进制中位数  
-|-|-
1 | 西 | 第一位为1
2 | 北 | 第二位为1
3 | 东 | 第三位为1
4 | 南 | 第四位为1






##  1.2 判断

那么问题来了**怎么判断**呢

这是我的判断函数（判断数x的第num位是否为1）

当这一位数是一的时候，这个方向就不能走。

所以返回false。

```cpp
bool check(int x,int num){
	if(x>>(num-1)&1==1) return false;
	else return true;
}
```




> Tips: 位运算& 在同一位上 同为1 返回1 有0 返回0

# Part Two 解题
------------

##  2.1 思路
做题开始先看数据范围！

**（1 <=M,N<=50）** 暴搜可做!

分成四个子问题来解决

###  2.1.1 （Target：城堡的房间数目）

> 类似于[求细胞数量](https://www.luogu.org/problem/P1451)便利每一个格子。若此各子没有被染过色。则从此格子开始跑bfs染色。最后有多少种颜色即是房间数量。

###  2.1.2（Target：最大的房间的大小）

>很容易。在每次染色时记录一下格子数目，取最大值就好了。

###  2.1.3（Target：移除一面墙能得到的最大的房间的大小）

>首先思考一下怎么才能做到拆墙操作
。标记还是归0？那样会有后效性，不好处理！我们把墙两边的点都加进队列进行拓展，既做到了“拆墙操作”也没有影响到后面的处理。

###  2.1.4（Target：移除哪面墙可以得到面积最大的新房间）

>因为是bfs，碰到没有被标记的格子就会开始拓展，所以我们只向东，北拓展。最后求得一定是西边和南边的墙

###  Tips

>显而易见，操作1，2可以一起完成；3，4可以一起完成。

##  2.2

###  2.2.1 Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,anx=-2222,anx2=-1999,ax,ay,ak;//anx是没拆墙时最大的房间大小，anx2是拆了墙之后最大房间的大小 
int a[55][55],mp[55][55];
int dy[5]={0,-1,0,1,0};//注意！这两个数组的顺序要和下面check一一对应。
int dx[5]={0,0,-1,0,1};//也就是枚举时i对应检测的方向和它要拓展的方向一致。 
struct node{int x,y;};
bool safe(int x,int y){return x>=1&&x<=m&&y>=1&&y<=n;}
bool check(int x,int num){
	if(x>>(num-1)&1==1) return false;
	else return true;
}
void bfs(int sx,int sy,int cnt){//处理问题1，2。cnt即是染色颜料 
	queue<node> q;int omax=1;
	mp[sx][sy]=cnt;
	q.push((node){sx,sy}); 
	while(!q.empty()){
		node u=q.front();q.pop();
		for(int i=1;i<=4;i++){
			int nx=u.x+dx[i],ny=u.y+dy[i];
			if(mp[nx][ny]==0&&check(a[u.x][u.y],i)&&safe(nx,ny)){//一个比较巧妙的操作 
				mp[nx][ny]=cnt;omax++;//check（x，i）和dx[i],dy[i]的i是一一对应的  
				q.push((node){nx,ny});// 1：西，2；北，3：东，4：南
			}
		}
	}
	anx=max(anx,omax);//最大的房间大小 
	return ;
}

void bfs2(int sx,int sy,int fx,int fy,int k){//处理问题3，4 
	memset(mp,0,sizeof(mp)); 
	queue<node> q;int omax=2;
	mp[sx][sy]=1;
	mp[fx][fy]=1;
	q.push((node){sx,sy}); 
	q.push((node){fx,fy}); 
	while(!q.empty()){
		node u=q.front();q.pop();
		for(int i=1;i<=4;i++){
			int nx=u.x+dx[i],ny=u.y+dy[i];
			if(mp[nx][ny]==0&&check(a[u.x][u.y],i)&&safe(nx,ny)){
				mp[nx][ny]=1;omax++;
				q.push((node){nx,ny}); 
			}
		}
	}
	if(omax>anx2) {//标记墙面 
		 ax=sx;ay=sy;
		 ak=k;
	}
	if(omax==anx2){//标记墙面 
		if(ay>=sy) ay=sy;
		if(ay==sy&&ax<=sx) ax=sx;
		if(ay==sy&&ax==sx) ak=k;
	} 
	anx2=max(anx2,omax);//打掉一个墙之后最大的房间大小 
	return ;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&a[i][j]);
		}
	}
	memset(mp,0,sizeof(mp));
	int cnt=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j]==0){//遍历，找到没有的拓展过的点。以它为起点扩展 
				cnt++;bfs(i,j,cnt);
			}
		}
	}
	cout<<cnt<<endl; 
	cout<<anx<<endl;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			for(int k=3;k>=2;k--){
				int nx=i+dx[k],ny=j+dy[k];//便利每一堵墙。把两边的格子加入队列 
				if(check(a[i][j],k)==false&&safe(nx,ny)){bfs2(i,j,nx,ny,k);}
			}
		}
	}
	cout<<anx2<<endl;
	cout<<ax<<" "<<ay<<" ";
	if(ak==3) cout<<"E";
	if(ak==2) cout<<"N";
	return 0;
}

```
# Part Three 写在最后
------------
欸，这个是**图论**？ 不是裸的bfs吗？

搜索写的真的很快乐（~~主要是可以写暴力~~）。

就到这里啦。

有什么问题也可以私聊我（~~我是真的蒟蒻~~）。
























---

## 作者：Snow_Dreams (赞：0)

这道题主要是两种方法，但本质都是搜索
1. dfs
深度优先搜索求联通块
这个地方讲解一下位运算（不要嫌我烦好不好qwq）：
### 一、位运算符


------------

- and：&  
- or：|
- not：~
- xor：^


------------


注：逻辑运算符

- && 与

_只有a，b都为真_ 时表达式才为真，否则为假

- || 或

_只有a，b都为假_ 时表达式才为假，否则为真


------------
### 二、补码


------------

- 定义：一个数字的补码就是将该数字作 _比特反运算，再将结果加 1_ ，即为该数字的补码。

 - 优势：可以在加法或减法处理中，不需因为数字的正负而使用不同的计算方式。 _只要一种加法电路_ 就可以处理 _各种有符号数_ 加法
 

------------
### 三、移位运算


------------
左移：<<

是将一个二进制位的操作数按指定移动的位数向左移动，移出位被丢弃

右移：>>
右边移出的空位一律补0。右移运算是将一个二进制位的操作数按指定移动的位数向右移动，移出位被丢弃


------------
### 四、成对变换

n为偶数：n^1 = n+1

n为奇数：n^1 = n-1



------------


现在讲解一下dfs函数（终于步入正题）
```cpp
if(c[i][j]) return;
```
剪枝（其实就是一个vis，只不过存的是数而已）

```cpp
    tmp++;
    c[i][j] = rooms;
    if(!(a[i][j]&1)) dfs(i,j-1);
    if(!(a[i][j]&2)) dfs(i-1,j);
    if(!(a[i][j]&4)) dfs(i,j+1);
    if(!(a[i][j]&8)) dfs(i+1,j);
```
&的运用上面讲了，dfs这张矩形的图
```cpp
int dx[] = {-1,0};
int dy[] = {0, 1};
```
采用滚动求方向来省略多个if或switch语句
```cpp
void solve()
{
    for(int j=1; j<=m; j++){
        for(int i=n; i>=1; i--){
            for(int k=0; k<2; k++){
                if(!(a[i][j]&(1<<(k+1)))) continue;
                int ii = i+dx[k];
                int jj = j+dy[k];
                if(c[i][j] == c[ii][jj]) continue;
                if(ii < 1|| ii>n || jj<1 || jj>m) continue;
                int temp = cnt[c[i][j]]+cnt[c[ii][jj]];
                if(temp > ans3){
                    ans3 = temp;
                    ansi = i; ansj = j;
                    ansk = k;
                }

            }
        }
    }
}
```
这段代码就是去求要移走的那面墙的位置


然后讲一下dfs的本质：在一个图内的一个顶点上依次选一条分支走下去

这道题时间还快，但有时dfs的时间复杂度太高，要用本题的第二种思路，bfs

代码就不贴了，贴一下dfs的代码：
```cpp
#include <cstdio>

const int N = 55;
int a[N][N];
int n,m;
int rooms, maxr, ans3, ansi, ansj, ansk;
int c[N][N], cnt[N*N];
int tmp;
void dfs(int i,int j)
{
    if(c[i][j]) return;
    tmp++;
    c[i][j] = rooms;
    if(!(a[i][j]&1)) dfs(i,j-1);
    if(!(a[i][j]&2)) dfs(i-1,j);
    if(!(a[i][j]&4)) dfs(i,j+1);
    if(!(a[i][j]&8)) dfs(i+1,j);
}
int dx[] = {-1,0};
int dy[] = {0, 1};
void solve()
{
    for(int j=1; j<=m; j++){
        for(int i=n; i>=1; i--){
            for(int k=0; k<2; k++){
                if(!(a[i][j]&(1<<(k+1)))) continue;
                int ii = i+dx[k];
                int jj = j+dy[k];
                if(c[i][j] == c[ii][jj]) continue;
                if(ii < 1|| ii>n || jj<1 || jj>m) continue;
                int temp = cnt[c[i][j]]+cnt[c[ii][jj]];
                if(temp > ans3){
                    ans3 = temp;
                    ansi = i; ansj = j;
                    ansk = k;
                }

            }
        }
    }
}
int main()
{
    scanf("%d%d", &m, &n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            scanf("%d", &a[i][j]);
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(!c[i][j]){
                ++rooms;
                tmp = 0;
                dfs(i,j);
                if(maxr < tmp) maxr = tmp;
                cnt[rooms] = tmp;
			}
        }
    }

    printf("%d\n%d\n", rooms, maxr);
    solve();
    printf("%d\n%d %d ", ans3, ansi, ansj);
    if(ansk == 0) printf("N\n");
    else printf("E\n");

    return 0;
}
/*;	

7 4
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13
*/
```
最后是广告qwq：推荐一下算法竞赛入门经典，啊哈算法（有对代码思路很好的剖析）

---

## 作者：zqiceberg (赞：0)

### 思路

题目一共四个问

第一行：城堡的房间数目。

第二行：最大的房间的大小

第三行：移除一面墙能得到的最大的房间的大小

第四行：移除哪面墙可以得到面积最大的新房间

前两问是Flood Fill，后两问是枚举

### 分析

从题意出发

eg. P1457_2.in
![](https://cdn.luogu.com.cn/upload/image_hosting/3aoofgqt.png)

要破除掉的墙壁是两个方块中间的那堵墙

eg. P1457_3.in
![](https://cdn.luogu.com.cn/upload/image_hosting/adv9m97o.png)

要破除掉的墙壁是第一行第一列方块的上方，那堵墙

题面表明

“选择最佳的墙来推倒。有多解时选最靠西的，仍然有多解时选最靠南的。同一格子北边的墙比东边的墙更优先。”

因此，推倒的时候，要打一下擂台。


### 框架
一、BFS求得连通块个数，最大连通块的面积

求连通块的时候，记录一下当前块属于哪个连通块，并把所有的连通块的面积记录下来。为了后面推导墙壁的时候，两个连通块面积相加

二、从上至下，从右至左的遍历。为了有西面的选西面的，有南面的选南面的。

判断一个方格的北面或者东面是否是墙，诸多合法判断后，把他推导，获得两个连通块的面积和，来更新擂台上记录的最大值


### 代码
```cpp
#include <iostream>
#include <algorithm>
#include <fstream>

#define x first
#define y second

using namespace std;

const int N = 55, M = N * N;

typedef pair<int, int> PII;

int g[N][N];
bool st[N][N];
PII q[M];

int n, m;

int dx[4] = {0, -1, 0, 1}, dy[4] = {-1, 0, 1, 0};

int idx, f[M];  //连通块编号，连通块的面积
int g_of_idx[N][N]; //记录每个方格属于哪个连通块
int max_area; //记录最大面积
int max_i = -1, max_j = -1;
char max_dir;
string dir = "WNES";

int bfs(int sx, int sy)
{   
    int area = 0;
    int hh = 0, tt = 0;   //模板hh = 0, tt = -1; 此处默认有一个start结点，tt = 0
    q[0].x = sx, q[0].y = sy;
    st[sx][sy] = true;
    
    idx++;       //每一个新队列，产生一个新的连通块
    
    while (hh <= tt)
    {
        area++;
        PII t = q[hh++];

        g_of_idx[t.x][t.y] = idx;   //标记这个方块属于哪个房间

        for (int i = 0; i < 4; i++)
        {
            int a = t.x + dx[i], b = t.y + dy[i];

            //越界，被遍历过，continue
            if (a < 0 || a >= n || b < 0 || b >= m) continue;
            if (st[a][b]) continue;

            //这个方格是墙，就continue
            if (g[t.x][t.y] >> i & 1) continue;

            //入队
            ++tt;
            q[tt].x = a, q[tt].y = b;
            st[a][b] = true;
        }
    }

    f[idx] = area; //记录这个编号连通块的面积，记录在f[]里面
    
    return  area;
}   

int main()
{
    //freopen("P1457_4.in", "r", stdin);

    scanf("%d%d", &m, &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &g[i][j]);

    int area = 0, cnt = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (!st[i][j])
            {
                area = max(area, bfs(i, j));
                cnt++;
            }
        }

    printf("%d\n%d\n", cnt, area);

    for (int i = 0; i < n; i++)
        for (int j = m - 1; j >= 0; j--)
            for (int k = 1; k <= 2; k++)  //遍历每个方格的北面和东面，是否是墙，可以推倒
            {
                if ((g[i][j] >> k & 1) != 1) continue; //当前的方格不是墙，就要continue

                int tx = i + dx[k], ty = j + dy[k];
                if (tx < 0 || tx >= n || ty < 0 || ty >= m) continue;

                if (g_of_idx[i][j] == g_of_idx[tx][ty]) continue;

                int sum_area = f[g_of_idx[i][j]] + f[g_of_idx[tx][ty]];
                if (sum_area > max_area)
                {
                    max_area = sum_area;
                    max_i = i;
                    max_j = j;
                    max_dir = dir[k];
                }
                else if (sum_area == max_area)
                {
                    //有多解时选最靠西的，仍然有多解时选最靠南的。同一格子北边的墙比东边的墙更优先。
                    if ((j == max_j && i > max_i) || (i == max_i && j < max_j))
                    {
                        max_area = sum_area;
                        max_i = i;
                        max_j = j;
                        max_dir = dir[k];
                    }

                }
            }

    printf("%d\n", max_area);
    printf("%d %d %c\n", max_i+1, max_j+1, max_dir);  //下标起始问题

    return 0;
}


```


### 总结

这道题的前两问被收录到《一本通》上机练习《The Castle》

2020年第一道题，奥利给！

---

## 作者：HeinzGuderian (赞：0)



言归正传，蒟蒻以前在Openjudge和一本通上都做过这题，看到竟是一道蓝题时，想都没想就把之前的代码复制粘贴上去，然后获得了0分的好成绩，仔细一看，还有两问是NOI和一本通上没有的，于是，wsl。
没办法只能继续打下去。唉……一言难尽，这题卡了我一上午。

该题的难点：

1.怎么判断每一堵墙的权值：![hmmm](https://cdn.luogu.com.cn/upload/image_hosting/xdrgjdvk.png)
```
	7 4
	11 6 11 6 3 10 6
	7 9 6 13 5 15 5
	1 10 12 7 13 7 5
	13 11 10 8 10 12 13
```
我们可以设西墙权值a，北墙权值b，东墙权值c，南墙权值d,根据样例中3个角的值11,6,13和东南角左边的点权值12可以得到:

1. a+b+d=11
2. a+c+d=13
3. b+c=6
4. c+d=12

从而解得a=1,b=2,c=4,d=8

2.优先级：西>南>北>东

这个好办啊，让i从大到小循环，j从小到大循环就轻松解决

其他的解释都在代码里了

```cpp
#include<bits/stdc++.h>
#define N 55
#define R register int
#define ll long long
#define AC return 0;
using namespace std;
int wall[N][N][4],//四个方向的墙
vis[N][N],f[10000001];//vis记录该点存在的房间 
int m,n,ans,room,l,r;
char ch;
int dx[4]={0,-1,0,1},
	dy[4]={-1,0,1,0};//方向数组 
string str="WNEA";//方向字串 
inline int read()//快读
{
	int f=1,x=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
inline bool judge(int x,int y)//边界判断 
{
	if(x>0&&x<=n&&y>0&&y<=m)return true;
	return false;
}
struct node{//存点的坐标
	int x;
	int y;
}now,next,st;
queue<node>Q;//STL大法好！！！ 
inline void bfs()
{
	//用STL队列实现广搜
	int sum=1;
	Q.push(st);
	vis[st.x][st.y]=++room;
	while(!Q.empty())//广搜模板，不讲了
	{
		now=Q.front();
		Q.pop();
		int x=now.x,
			y=now.y;
		for(int k=0; k<4; k++)
		{
			int nx=x+dx[k],
			    ny=y+dy[k];
			if(judge(nx,ny)==true&&!vis[nx][ny]&&!wall[x][y][k])//该点没有越界，且不是墙壁且该点不属于任何一个已知房间
			{
				vis[nx][ny]=room;//把该点加入现在的房间
				sum++;
				next.x=nx;next.y=ny;//压入队列
				Q.push(next);
			}
		}
	}
	ans=max(ans,sum);//每次寻找完一个房间就更新房间
	f[room]=sum;//存储该房间的大小
}
void init()
{
	ios::sync_with_stdio(false);
	m=read(),n=read();
	for(R i=1; i<=n; i++)
	{
		for(R j=1; j<=m; j++)
		{
			int x;
			x=read();
			if(x>=8){x-=8;wall[i][j][3]=1;}//南面有墙
			if(x>=4){x-=4;wall[i][j][2]=1;}//东面有墙
			if(x>=2){x-=2;wall[i][j][1]=1;}//北面有墙
			if(x>=1){x-=1;wall[i][j][0]=1;}//西面有墙 
		}
	}
}
void findmax()
{
	for(R j=1;j<=m;j++)//优先级是西->南
	{
		for(R i=n;i>=1;i--)
		{ 
			for(R k=1; k<=2; k++)
			{ 
				if(wall[i][j][k])
				{
					int nx=i+dx[k],
						ny=j+dy[k];
					int size=f[vis[nx][ny]]+f[vis[i][j]];//打破墙壁之后房间大小=两个房间的大小之和
					if(size>ans&&vis[nx][ny]!=vis[i][j])//更新最大值并记录位置和方向
					{
						ans=size;
						l=i;r=j;ch=str[k];
					}
				}
			} 
		} 
	}
}
int main()
{//简短的主函数QwQ 
	init();
	for(int i=1; i<=n; i++)
	{ 
		for(int j=1; j<=m; j++)
		{ 
			if(!vis[i][j]){st.x=i;st.y=j,bfs();}
		} 
	}
	cout<<room<<endl<<ans<<endl;
	findmax();//寻找最大值
	cout<<ans<<endl<<l<<" "<<r<<" "<<ch<<endl;
	AC
}
/*
7 4
11 6 11 6 3 10 6
7 9 6 13 5 15 5
1 10 12 7 13 7 5
13 11 10 8 10 12 13*/
```
给各位一组数据，自己出的，和题解输出一样，应该没错
![](https://cdn.luogu.com.cn/upload/image_hosting/4ahk8oja.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

	4 3
	15 11 14 15
	3 2  2 12
	13 9 12 15
最后祝各位
### CSP2019 RP++，Score++

---

## 作者：Thaumaturge (赞：0)

如果这也是提高+的题那我之前都在干些啥。。
搜索+模拟就好了，每个方格存储房子的序号与空间即可，然后枚举。代码如下：
```
#include <bits/stdc++.h>

using namespace std;

int a[60][60][5],b[60][60],c[60][60],i,j,k,m,n,sum,lo,max1,max2;//max1是最大房间，max2是推倒后能形成的最大房间
//c是房间序号，防止判断墙时出现拐弯同房但判为异房的错误
//a是序号
int xl=-10,yl=100,fx;//分别表示推倒的墙所处坐标,fx顾名思义
//1表示东，即j+1;
//2表示南，即i+1;
//3表示西，即j-1;
//4表示北，即i-1;
//b表示房间有多大;

int search(int x,int y)//穷举
{
	b[x][y]=-1;
	lo++;
	if(a[x][y][1]==0 && b[x][y+1]==0) {search(x,y+1);}
	if(a[x][y][2]==0 && b[x+1][y]==0) {search(x+1,y);}
	if(a[x][y][3]==0 && b[x][y-1]==0) {search(x,y-1);}
	if(a[x][y][4]==0 && b[x-1][y]==0) {search(x-1,y);}
}

int bl(int x,int y){//赋上房间空间及其序号，方便判断
	b[x][y]=lo;
	c[x][y]=sum;
	if(a[x][y][1]==0 && b[x][y+1]==-1) {bl(x,y+1);}
	if(a[x][y][2]==0 && b[x+1][y]==-1) {bl(x+1,y);}
	if(a[x][y][3]==0 && b[x][y-1]==-1) {bl(x,y-1);}
	if(a[x][y][4]==0 && b[x-1][y]==-1) {bl(x-1,y);}
}

int main(){
	cin>>m>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			cin>>b[i][j];

	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		{
			k=b[i][j]/8;
			a[i][j][2]=k;
			b[i][j]%=8;

			k=b[i][j]/4;
			a[i][j][1]=k;
			b[i][j]%=4;
			
			k=b[i][j]/2;
			a[i][j][4]=k;
			b[i][j]%=2;
			
			k=b[i][j];
			a[i][j][3]=k;
			b[i][j]=0;
		}


	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
		{
			lo=0;
			if(b[i][j]==0)
			{
				search(i,j);
				if(lo>max1) max1=lo;
				sum++;
				bl(i,j);
			}
		}

	for(i=1;i<=n;i++)//依次判断，先举纵再举横
		for(j=1;j<=m;j++)
		{
			if(a[i][j][1]==1) 
			{
				if((max2<b[i][j]+b[i][j+1] ||(max2==b[i][j]+b[i][j+1] && j<=yl )||(max2==b[i][j]+b[i][j+1] && j==yl && i>=xl))  && c[i][j]!=c[i][j+1])
				{max2=b[i][j]+b[i][j+1];xl=i;yl=j;fx=1;}
			}
			if(a[i][j][2]==1) 
			{
				if((max2<b[i][j]+b[i+1][j] ||(max2==b[i][j]+b[i+1][j] && j<=yl )||(max2==b[i][j]+b[i+1][j] && j==yl && i>=xl))  && c[i][j]!=c[i+1][j])
				{max2=b[i][j]+b[i+1][j];xl=i;yl=j;fx=2;}
			}
			if(a[i][j][3]==1) 
			{
				if((max2<b[i][j]+b[i][j-1] ||(max2==b[i][j]+b[i][j-1] && j<=yl )||(max2==b[i][j]+b[i][j-1] && j==yl && i>=xl))  && c[i][j]!=c[i][j-1])
				{max2=b[i][j]+b[i][j-1];xl=i;yl=j;fx=3;}
			}
			if(a[i][j][4]==1)
			{
				if((max2<b[i][j]+b[i-1][j] ||(max2==b[i][j]+b[i-1][j] && j<=yl )||(max2==b[i][j]+b[i-1][j] && j==yl && i>=xl))  && c[i][j]!=c[i-1][j])
				{max2=b[i][j]+b[i-1][j];xl=i;yl=j;fx=4;}
			}
		}
	//输出
	cout<<sum<<"\n"<<max1<<"\n"<<max2<<"\n"<<xl<<" "<<yl<<" ";
	if(fx==1) cout<<"E";
	if(fx==4) cout<<"N";
	return 0;
}
	cout<<sum<<"\n"<<max1<<"\n"<<max2<<"\n"<<xl<<" "<<yl<<" ";
	if(fx==1) cout<<"E";
	if(fx==4) cout<<"N";
	return 0;
}
```

充满着蒟蒻气息，C版C++的代码

---

## 作者：周子衡 (赞：0)

思路：深搜+模拟

个人认为本题没有那么难，但很考察代码能力。

首先是读入，由于数字是由几个二的幂相加而得，因此考虑位运算：

```cpp
scanf("%d%d",&m,&n);
for(int i=1,x=0;i<=n;i++)
{
	for(int j=1;j<=m;j++)
    {
        scanf("%d",&x);
        for(int k=0;k<4;k++)
        {
            wll[k][i][j]=x&(1<<k);
        }
    }
}
```

（其中$wll[0][i][j]$、$wll[1][i][j]$、$wll[2][i][j]$、$wll[3][i][j]$分别表示单位格$(i,j)$的西、北、东、南面是否有墙）

接下来看前两问：

```
第 1 行: 城堡的房间数目。

第 2 行: 最大的房间的大小
```

显然是洪泛算法能解决的问题，代码：

```cpp
void get_rm(int now_x,int now_y,int now_rm)
{
    rm_num[now_x][now_y]=now_rm;
    for(int i=0;i<4;i++)
    {
        if(now_x+mv_x[i]>=1&&now_x+mv_x[i]<=n
        &&now_y+mv_y[i]>=1&&now_y+mv_y[i]<=m
        &&!wll[i][now_x][now_y]
        &&!rm_num[now_x+mv_x[i]][now_y+mv_y[i]])
        {
            get_rm(now_x+mv_x[i],now_y+mv_y[i],now_rm);
        }
    }
}

int main()
{
	(read in)
    
    int rm_all=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!rm_num[i][j])
            {
                rm_all++;
                get_rm(i,j,rm_all);
            }
        }
    }
    printf("%d\n",rm_all);
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            rm_sz[rm_num[i][j]]++;
        }
    }
    int maxn_2=0;
    for(int i=1;i<=rm_all;i++)
    {
        maxn_2=maxn_2>rm_sz[i]?maxn_2:rm_sz[i];
    }
    printf("%d\n",maxn_2);
}
```

（其中$rm$_$num[i][j]$代表单位格$(i,j)$所处房间编号，$rm$_$sz[i]$代表编号为$i$的房间的面积，$void$ $get$_$rm(int$ $now$_$x,int$ $now$_$y,int$ $now$_$rm)$函数功能是将单位格及其周围的单元格编号）

接下来是第三、四问：

```
第 3 行: 移除一面墙能得到的最大的房间的大小

第 4 行: 移除哪面墙可以得到面积最大的新房间。
```

对于第三问，枚举每面墙拆掉后所形成的房间的大小即可。

第四问要求输出方案，看要求：

```
有多解时选最靠西的，仍然有多解时选最靠南的。同一格子北边的墙比东边的墙更优先。

用该墙的南邻单位的北墙或西邻单位的东墙来表示这面墙，方法是输出邻近单位的行数、列数和墙的方位（"N"（北）或者"E"（东））。
```

枚举时注意顺序即可。

代码：

```cpp
int main()
{
	(read in)
    (question 1&2)
    
    int maxn_3=0,maxn_i=0,maxn_j=0,maxn_sd=0;
    for(int j=1;j<=m;j++)
    {
        for(int i=n;i>=1;i--)
        {
            if(rm_num[i][j]!=rm_num[i-1][j])
            {
                if(maxn_3<rm_sz[rm_num[i][j]]+rm_sz[rm_num[i-1][j]])
                {
                    maxn_3=rm_sz[rm_num[i][j]]+rm_sz[rm_num[i-1][j]];
                    maxn_i=i;
                    maxn_j=j;
                    maxn_sd=0;
                }
            }
            if(rm_num[i][j]!=rm_num[i][j+1])
            {
                if(maxn_3<rm_sz[rm_num[i][j]]+rm_sz[rm_num[i][j+1]])
                {
                    maxn_3=rm_sz[rm_num[i][j]]+rm_sz[rm_num[i][j+1]];
                    maxn_i=i;
                    maxn_j=j;
                    maxn_sd=1;
                }
            }
        }
    }
    printf("%d\n%d %d %c",maxn_3,maxn_i,maxn_j,maxn_sd==0?'N':'E');
}
```

最后附上完整代码：

```cpp
#include<cstdio>

using namespace std;

int m,n;
bool wll[4][51][51]={};
int rm_num[52][52]={};
int rm_sz[2501]={};

const int mv_x[]={0,-1,0,1};
const int mv_y[]={-1,0,1,0};

void get_rm(int now_x,int now_y,int now_rm)
{
    rm_num[now_x][now_y]=now_rm;
    for(int i=0;i<4;i++)
    {
        if(now_x+mv_x[i]>=1&&now_x+mv_x[i]<=n
        &&now_y+mv_y[i]>=1&&now_y+mv_y[i]<=m
        &&!wll[i][now_x][now_y]
        &&!rm_num[now_x+mv_x[i]][now_y+mv_y[i]])
        {
            get_rm(now_x+mv_x[i],now_y+mv_y[i],now_rm);
        }
    }
}

int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1,x=0;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%d",&x);
            for(int k=0;k<4;k++)
            {
                wll[k][i][j]=x&(1<<k);
            }
        }
    }
    
    int rm_all=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!rm_num[i][j])
            {
                rm_all++;
                get_rm(i,j,rm_all);
            }
        }
    }
    printf("%d\n",rm_all);
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            rm_sz[rm_num[i][j]]++;
        }
    }
    int maxn_2=0;
    for(int i=1;i<=rm_all;i++)
    {
        maxn_2=maxn_2>rm_sz[i]?maxn_2:rm_sz[i];
    }
    printf("%d\n",maxn_2);
    
    int maxn_3=0,maxn_i=0,maxn_j=0,maxn_sd=0;
    for(int j=1;j<=m;j++)
    {
        for(int i=n;i>=1;i--)
        {
            if(rm_num[i][j]!=rm_num[i-1][j])
            {
                if(maxn_3<rm_sz[rm_num[i][j]]+rm_sz[rm_num[i-1][j]])
                {
                    maxn_3=rm_sz[rm_num[i][j]]+rm_sz[rm_num[i-1][j]];
                    maxn_i=i;
                    maxn_j=j;
                    maxn_sd=0;
                }
            }
            if(rm_num[i][j]!=rm_num[i][j+1])
            {
                if(maxn_3<rm_sz[rm_num[i][j]]+rm_sz[rm_num[i][j+1]])
                {
                    maxn_3=rm_sz[rm_num[i][j]]+rm_sz[rm_num[i][j+1]];
                    maxn_i=i;
                    maxn_j=j;
                    maxn_sd=1;
                }
            }
        }
    }
    printf("%d\n%d %d %c",maxn_3,maxn_i,maxn_j,maxn_sd==0?'N':'E');
    
    return 0;
}
```

---

## 作者：御·Dragon (赞：0)

### 这题可以用[宽度优先搜索](https://baike.so.com/doc/7806949-8081044.html)，搜索出每一个房间再计算。然而在计算墙的时候，就会用到[数据压缩](https://baike.so.com/doc/6144853-6358030.html)。所以这道题所考的知识点较多，值得珂学AC掉。

__话不多说，附上代码__

```
#include <stdio.h>//万能头不敢用,因为有map 

const int MAXN = 51;//定义常量 
const int d[4][2] = {{0, -1}, {-1 ,0}, {0, 1}, {1, 0}}; // 按照题目，用四个方向表示的2的幂作为下标。 
const char name[4] = {'W', 'N', 'E', 'S'};

int map[MAXN][MAXN], num[MAXN][MAXN]; // 地图和所属房间编号。 
int a[MAXN * MAXN]; // 每个房间的大小。 
int n, m, ans, c, ans2, ansx, ansy, ansd;

bool inMap(int x, int y) { // 检查一个坐标是否在地图中。 
	return  (x > 0) && (x <= n) && (y > 0) && (y <= m);
}

int search(int x, int y) { // 将与x,y坐标同一房间的格子全部标记，并返回从该格子开始新搜索出的格子的数量。 
	if (!inMap(x, y) || num[x][y] != 0) { // 如果该格子不在地图中，或者已经被标记过了，则停止搜索。 
		return 0;
	}
	num[x][y] = c; // 标记当前格子。 
	int sum = 1; // 记录新格子数量，初始时只有当前格子。 
	for (int i = 0; i <= 3; i++) { // 向四个方向尝试扩展。 
		if (((map[x][y] >> i) & 1) == 0) { // 如果i方向没有墙，则进行扩展。 
			sum += search(x + d[i][0], y + d[i][1]); 
		}
	}
	return sum; // 返回格子数量。 
}

void test(int x, int y, int i) { // 检查x,y格子向i方向打通墙得到的房间大小。 
	if ((map[x][y] >> i) & 1 == 0) { // 如果i方向没有墙则退出。 
		return;
	}
	int nx = x + d[i][0]; // 计算打通墙后隔壁的格子坐标。 
	int ny = y + d[i][1];
	if (!inMap[nx][ny]) { // 不能打通外围的墙。 
		return;
	}
	int sum = a[num[x][y]]; // 记录当前房间大小。 
	if (num[x][y] != num[nx][ny]) { // 如果墙后的格子不属于同一房间则累加大小。 
		sum += a[num[nx][ny]];
	}
	if (sum > ans2) { //更新答案。 
		ans2 = sum;
		ansx = x;
		ansy = y;
		ansd = i;
	}
}

int main() {//开始了 
	scanf("%d %d\n", &m, &n);//输入 
	for (int i = 1; i <= n; i++) {//枚举长宽输入 
		for (int j = 1; j <= m; j++) {
			scanf("%d", &map[i][j]);//将其存入map 
		}
	}
	
```

__其实他们所用的墙的表示法是用到了数据压缩的，所以前面会有计算哪里有墙的函数__

```
    
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) { // 枚举每一个格子。 
			if (num[i][j] == 0) { // 如果当前格子没有标记，则表示找到一个新的房间。 
				c++;
				a[c] = search(i, j); // 标记房间内所有的格子，并返回格子数量。 
				if (a[c] > ans) { // 更新答案。 
					ans = a[c]; 
				}
			}
		}
	}
	for (int j = 1; j <= m; j++) { // 由西往东枚举墙。 
		for (int i = n; i >= 1; i--) { // 由南往北枚举墙。 
			test(i, j, 1); // 优先考虑拆东墙。 
			test(i, j, 2); // 拆北墙。 
		}
	}
	printf("%d\n%d\n%d\n%d %d %c\n", c, ans, ans2, ansx, ansy, name[ansd]);//输出 
	return 0;	//完美结尾 
}
```

---

## 作者：QianhanOfficial (赞：0)

初次遇到这道题本蒟蒻是有点慌的 一看这么高大上的描述 好强啊  
实际上 当我们仔细分析他的描述之后会发现：他在逗我们  
首先 1 2 4 8这四个数可以组成1-15的所有的数 而这15个数各自代表了周围墙的安置情况:具体来说，就是数字由1 2 4 8中哪几个数字组成 周围就有哪些墙。  
如果输入是0 那就意味着周围没有墙 它在房间中心 什么也不用操作  
我们还发现，他给的矩阵n×m 是个剔除了墙的矩阵，这就不够直观。于是我们可以把这张图展开，变成n×2 × m×2的矩阵，把墙加上去。但是要注意加入墙的时候 该位置在墙的方向上的三个格子必须都设为墙。  
还是不够直观？没关系，我们直接输出这个展开之后的矩阵。  
以下是样例的初始矩阵。  
```cpp
 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
 -1  0 -2  0 -1  0 -2  0 -1  0 -2  0 -2  0 -1
 -1 -1 -1 -2 -1 -1 -1 -2 -1 -2 -1 -1 -1 -2 -1
 -1  0 -1  0 -2  0 -1  0 -1  0 -1  0 -1  0 -1
 -1 -2 -1 -1 -1 -2 -1 -1 -1 -2 -1 -1 -1 -2 -1
 -1  0 -2  0 -2  0 -1  0 -1  0 -1  0 -1  0 -1
 -1 -2 -1 -1 -1 -1 -1 -2 -1 -1 -1 -2 -1 -2 -1
 -1  0 -1  0 -2  0 -2  0 -2  0 -2  0 -1  0 -1
 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1
```
在这个矩阵中：  
0代表空地 也就是输入的房间所在点(相当于样例图片中的空地)    
-1代表墙(样例图片中的#)   
-2代表的是0周围没有墙的那些点(样例图片中的|和-)。  
这样我们就能发现，0和0之间在上下左右方向上有-1或者-2隔开 -1不能走 -2可以走但是不记录房间大小 遇到0房间大小+1。  
然后一套dfs即可解决。  
但是需要注意的是，我们用了好几个二维数组  
其中a是输入的原数组  
vis是dfs用的涂色数组  
map是一定不会被改变的原数组(因为a数组后来需要用来存储房间大小)  
sam用来存储房间编号，为了后面判断墙的两边不能是同一个房间  
需要注意的大概就这些，上代码：
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#define re register
#define max(x, y) (x > y ? x : y)
#define west a[x][y - 1] = a[x - 1][y - 1] = a[x + 1][y - 1]
#define north a[x - 1][y] = a[x - 1][y - 1] = a[x - 1][y + 1]
#define east a[x][y + 1] = a[x - 1][y + 1] = a[x + 1][y + 1]
#define south a[x + 1][y] = a[x + 1][y - 1] = a[x + 1][y + 1]

struct node//储存墙的信息
{
	int x, y, sum;//x,y坐标 sum是打通之后的两个房间的总和
	char dir;//dir:墙的朝向
};

bool operator < (node x, node y)//让优先队列按我们的要求排序
{
	if(x.sum == y.sum)
	{
		if(x.y == y.y)
		{
			return x.x < y.x;最后是按行(最南边的)
		}
		return x.y > y.y;//再按列排(最西边的)
	}
	return x.sum < y.sum;//先按房间大小排
}

std::priority_queue<node> q;

int n, m, rom, cnt, maxans;
//rom房间个数 cnt房间大小 maxans最大的房间
int a[101][101], vis[101][101], map[101][101], sam[101][101];

inline void build(int x, int y, int z)//处理信息...
{
	a[x][y] = 0;
	if(z == 1) west = -1;//west
	else if(z == 2) north = -1;//north
	else if(z == 3) west = -1, north = -1;//west north
	else if(z == 4) east = -1;//east
	else if(z == 5) west = -1, east = -1;//west east
	else if(z == 6) north = -1, east = -1;//north east
	else if(z == 7) west = -1, north = -1, east = -1;//north east west
	else if(z == 8) south = -1;//south
	else if(z == 9) west = -1, south = -1;//south west
	else if(z == 10) north = -1, south = -1;//south north
	else if(z == 11) west = -1, north = -1, south = -1;//south north west
	else if(z == 12) east = -1, south = -1;//south east
	else if(z == 13) west = -1, east = -1, south = -1;//south east west
	else if(z == 14) east = -1, north = -1, south = -1;//south east north
	else if(z == 15) west = -1, north = -1, east = -1, south = -1;//4.
}

void dfs(int x, int y)//标准dfs
{
	if(!vis[x][y]) vis[x][y] = 1, ++cnt;//如果遇到空地就+1并标记
	if(vis[x][y] == -2) vis[x][y] = -3;//防止死循环..
	if(!vis[x + 1][y] || vis[x + 1][y] == -2) dfs(x + 1, y);
	if(!vis[x - 1][y] || vis[x - 1][y] == -2) dfs(x - 1, y);
	if(!vis[x][y + 1] || vis[x][y + 1] == -2) dfs(x, y + 1);
	if(!vis[x][y - 1] || vis[x][y - 1] == -2) dfs(x, y - 1);
	maxans = max(maxans, cnt);//最终得出房间大小和最大的房间大小
}

int main()
{
	scanf("%d%d", &m, &n);
	for(re int i = 0; i <= (n << 1); ++i)//注意范围 0~(n*2)是矩阵下标范围
	{
		for(re int j = 0; j <= (m << 1); ++j)
		{
			a[i][j] = -2;//初始化a 
		}
	}
	for(re int i = 1; i <= n; ++i)
	{
		for(re int j = 1; j <= m; ++j)
		{
			int x;
			scanf("%d", &x);
			build((i << 1) - 1, (j << 1) - 1, x);//因为展开矩阵之后的下标就不再是原来的了 进行乘2再-1的处理
		}
	}
	for(re int i = 0; i <= (n << 1); ++i)
	{
		for(re int j = 0; j <= (m << 1); ++j)
		{
			vis[i][j] = a[i][j];//相当于memcpy 
			map[i][j] = a[i][j];
			sam[i][j] = a[i][j];
		}
	}
	for(re int i = 1; i <= (n << 1) - 1; ++i)//这里不需要寻找最外面一圈的城墙
	{
		for(re int j = 1; j <= (m << 1) - 1; ++j)
		{
			cnt = 0;
			if(!vis[i][j])
			{
				++rom;//找到一个房间
				dfs(i, j);
				for(re int i = 1; i <= (n << 1) - 1; ++i)
				{//使a中存储房间大小信息 方便后面打墙
					for(re int j = 1; j <= (m << 1) - 1; ++j)
					{
						if(vis[i][j] == -3) continue;//原来是-2的位置不储存信息
						if(vis[i][j] != a[i][j])//也就是原先的空地
						{
							a[i][j] = cnt;//记录房间大小
							vis[i][j] = cnt;//注意 vis也要同时更新
							sam[i][j] = rom;//储存房间编号
						}
					}
				}
			}
		}
	}
	for(re int i = 1; i <= (n << 1) - 1; ++i)//开始枚举可以打通的墙
	{//还是不需要处理外圈城墙
		for(re int j = 1; j <= (m << 1) - 1; ++j)
		{
			if(map[i][j] == -1)//-1代表墙
			{
				if(map[i - 1][j] == 0 && map[i + 1][j] == 0 && sam[i - 1][j] != sam[i + 1][j])//如果“南北”两边都是空地 且两边不属于同一房间 储存一下这堵墙的信息
				{
					q.push((node){(i >> 1) + 1, (j + 1) >> 1, a[i - 1][j] + a[i + 1][j], 'N'});
				}
				if(map[i][j - 1] == 0 && map[i][j + 1] == 0 && sam[i][j - 1] != sam[i][j + 1])//“东西”朝向的墙
				{
					q.push((node){(i + 1) >> 1, j >> 1, a[i][j - 1] + a[i][j + 1], 'E'});
				}
			}
		}
	}
	printf("%d\n", rom);
	printf("%d\n", maxans);
	printf("%d\n", q.top().sum);//输出最大值
	printf("%d %d %c", q.top().x, q.top().y, q.top().dir);//最需要打通的墙
	return 0;
}
```

---

## 作者：fengsq19474 (赞：0)

看大家都是遍历做的，发个并查集的做法吧。

题目问房间数目和最大房间大小，明显就是并查集的功能。
用n*m个元素代表每个格子，fa[x]代表x元素的连通块根节点，对于根节点用sz[x]表示此连通块的大小。

并查集的基本操作是合并而不是分割，所以我们从后往前做，假设一开始所有格子旁边都是墙，整个图有n*m个连通块。然后读入数据的时候对每个格子枚举四个方向，如果没有墙则合并相邻的格子。合并的时候记得维护sz和连通块的数量。

最后输出连通块的数量和最大的sz就行了。

对于最后两问，我们可以枚举每面墙，假设推掉它，合并相邻两个格子试试得到的连通块有多大，取最大的更新就行了。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#define REP(i,from,to)      for(auto i=(from); i<=(to); ++i)
#define PER(i,from,to)      for(auto i=(from); i>=(to); --i)
#define FOR(i,less_than)    for (auto i=0; i<(less_than); ++i)
#define FILL(container, value)    fill(container.begin(), container.end(), value)

using VI  = std::vector<int>;
using VVI = std::vector<VI>;

using namespace std;

int n, m;
vector<VVI> wall;
VI fa, sz;
int scc, max_sz;

vector<int> dx={0,-1,0,1};
vector<int> dy={-1,0,1,0};

inline bool ok(int x, int y) { return x>=0 && x<n && y>=0 && y<m; }

int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }

inline int encode(int x, int y) { return x*m+y+1; }

void merge(int x, int y, int tx, int ty) {
    int a = encode(x, y), b = encode(tx, ty);
    int fx=find(a), fy=find(b);
    if (fx!=fy) {
        --scc;
        fa[fx] = fy;
        sz[fy] += sz[fx];
        max_sz = max(max_sz, sz[fy]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> m >> n;
    wall = vector<VVI>(n+1, VVI(m+1, VI(4)));

    fa.resize(n*m+1);
    sz.resize(n*m+1);
    scc = n*m ,max_sz = 1;
    iota(fa.begin(), fa.end(), 0);
    FILL(sz, 1);

    REP(i, 0, n-1) REP(j, 0, m-1) {
        int x;
        cin >> x;
        REP(k, 0, 3) 
            wall[i][j][k] = (x>>k & 1);
        REP(k, 0, 3)
            if (!wall[i][j][k]) {
                 int tx=i+dx[k], ty=j+dy[k];
                 merge(i,j,tx,ty);
            }
    }

    cout << scc << '\n' << max_sz << '\n';

    int max_merge = 0;
    string direction = " NE ";
    string pos;
    FOR(j, m) PER(i, n-1, 0)  
        REP(k, 1, 2)
            if (wall[i][j][k]) {
                int tx=i+dx[k], ty=j+dy[k];
                if (ok(tx, ty)) {
                    int fx = find(encode(i,j)), fy = find(encode(tx,ty));
                    if (fx!=fy && sz[fx]+sz[fy]>max_merge) {
                        max_merge = sz[fx] + sz[fy];
                        pos = to_string(i+1) + " " + to_string(j+1) + " " + direction[k];
                    }
                }
            }

    cout << max_merge << '\n' << pos << endl;

    return 0;
}
```

---

## 作者：lijianyangyf (赞：0)

```
一道并查集模板题
我竟然做了2.5d
各位大佬1.5h就A了
我好菜，怎么办？？？
好吧，是道递归+并查集
解释都在下面了。
（1）尽量直接找最优解
（2）如果有家族标记就不能再搜了
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
struct node
{
    bool b[5];//南东北西 
    int jz;//家族号
    node()
    {
        memset(b,1,sizeof(b));
        jz=-1;//一开始没有家族
    }
}a[52][52];//存图
int n,m,lz,maxx,f[2601];//房间大小
const int dx[5]={0,1,0,-1,0};
const int dy[5]={0,0,1,0,-1};
void turn(int i,int j,int x);
int dfs(int x,int y);
int main()
{
    int ansx,ansy;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%d",&x);
            turn(i,j,x);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j].jz==-1)
            {
            	//lz:家族的数量(编号) 
                f[++lz]=dfs(i,j);//递归求家族 
                maxx=max(f[lz],maxx);//找最大房间的大小  
            }
    printf("%d\n%d\n",lz,maxx);
    maxx=0;char st;
    for(int j=1;j<=m;j++)//找答案(必为最优答案) 
    {
        for(int i=n;i>=1;i--)
        {
            if(!a[i][j].b[3]&&a[i-1][j].jz!=a[i][j].jz)//北墙 
            {
                int t=f[a[i-1][j].jz]+f[a[i][j].jz];
                if(t>maxx)//判断 
                {
                    maxx=t;
                    ansx=i;
                    ansy=j;
                    st='N';
                }
            }
            if(!a[i][j].b[2]&&a[i][j+1].jz!=a[i][j].jz)//东墙 
            {
                int t=f[a[i][j+1].jz]+f[a[i][j].jz];
                if(t>maxx)
                {
                    maxx=t;
                    ansx=i;
                    ansy=j;
                    st='E';
                }
            }
        }
    }
    printf("%d\n%d %d %c\n",maxx,ansx,ansy,st);
}
int dfs(int x,int y)
{
    int s=0;
    a[x][y].jz=lz;
    for(int i=1;i<5;i++)
    {
        int xx,yy;
        xx=x+dx[i],yy=y+dy[i];
        if(xx>0&&xx<=n&&yy>0&&yy<=m&&a[x][y].b[i])
            if(a[xx][yy].jz==-1)//没有墙就加入家族 
                s+=dfs(xx,yy);
    }
    return s+1;//加上自己 
}
void turn(int i,int j,int x)
{
    if(x>=8)a[i][j].b[1]=a[i+1][j].b[3]=0,x-=8;//2进制,判断该数第4位是否为1 
    if(x>=4)a[i][j].b[2]=a[i][j+1].b[4]=0,x-=4;//...
    if(x>=2)a[i][j].b[3]=a[i-1][j].b[1]=0,x-=2;//...
    if(x>=1)a[i][j].b[4]=a[i][j-1].b[2]=0,x-=1;//...
}
```

---

## 作者：Celebrate (赞：0)

这一道题用并查集+深搜来做

步骤如下：

（1）输入的时候顺便找出所有的墙

（2）枚举行和列，如果这一个点没有被找过的话，就把它当作祖先，四个方向搜索，顺便查找面积

（3）找最大的房间和房间总数

（4）枚举行和列，上和右两边的房间并查找两个房间之和最大，还有要打破的那堵墙

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node//(x,y)的父亲 
{
	int x,y;
}fa[52][52];
int wx,wy;
int dx[4]={-1,0,1,0};//上、右、下、左四个方向 
int dy[4]={0,1,0,-1};
int n,m,a[52][52],s;//a表示这个祖先点的房间面积 
bool f[52][52][52][52],v[52][52];//f[x1][y1][x2][y2]表示两个点是否想通 
void find_zuxian(int x,int y)//查找祖先，并把值放在wx,wy里面 
{
	if(fa[x][y].x==x && fa[x][y].y==y){wx=x,wy=y;return;}
	else find_zuxian(fa[x][y].x,fa[x][y].y);
}
inline void find(int x,int y,int c)//查找点(x,y)的墙 
{
	if(c>=8) f[x][y][x+1][y]=f[x+1][y][x][y]=false,c-=8;
	if(c>=4) f[x][y][x][y+1]=f[x][y+1][x][y]=false,c-=4;
	if(c>=2) f[x][y][x-1][y]=f[x-1][y][x][y]=false,c-=2;
	if(c==1) f[x][y][x][y-1]=f[x][y-1][x][y]=false;
}
void dfs(int x,int y)//从点(x,y)开始上下左右四个方向搜索 
{
	int i,xx,yy;
	for(i=0;i<=3;i++)
	{
		xx=x+dx[i];
		yy=y+dy[i];
		if(v[xx][yy]==true && f[x][y][xx][yy]==true)
		{
			v[xx][yy]=false;
			fa[xx][yy].x=x;
			fa[xx][yy].y=y;
			dfs(xx,yy);
		}
	}
	s++;//记录面积 
}
int main()
{
	int i,j,k,t;
	scanf("%d%d",&m,&n);
	memset(f,true,sizeof(f));
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&t),find(i,j,t),fa[i][j].x=i,fa[i][j].y=j;//查找这个点旁边的墙，一开始自己的祖先点就是为自己 
	memset(v,true,sizeof(v));//记录这个点是否搜过 
	for(i=1;i<=n;i++)//查找每一个点 
	{
		for(j=1;j<=m;j++)
		{
			if(v[i][j]==false) continue;//如果被找过了，就不用管了 
			v[i][j]=false;s=0;//初始化s 
			dfs(i,j);a[i][j]=s;//深搜，并且记录s 
		}
	}
	int ans=0,maxx=0;
	for(i=1;i<=n;i++)//找最大的房间和房间总数
	{
		for(j=1;j<=m;j++)
		{
			if(fa[i][j].x==i && fa[i][j].y==j)//如果自己的祖先是自己的话，说明它就是祖先 
			{
				ans++;
				maxx=max(maxx,a[i][j]);
			}
		}
	}
	printf("%d\n",ans);
	printf("%d\n",maxx);
	maxx=0;
	int max_x,max_y,max_t;
	for(i=1;i<=n;i++)//枚举行 
	{
		for(j=1;j<=m;j++)//枚举列 
		{
			for(t=0;t<=1;t++)//上和右两个方向 
			{
				int xx=i+dx[t];
				int yy=j+dy[t];
				if(xx>=1 && xx<=n && yy>=1 && yy<=m)//没有超出边界 
				{
					if(f[i][j][xx][yy]==false)//如果有墙挡住 
					{
						int x1,y1,x2,y2;
						find_zuxian(i,j);x1=wx;y1=wy;//查找这两个点的祖先 
						find_zuxian(xx,yy);x2=wx;y2=wy;
						if(x1!=x2 || y1!=y2) //如果两个点不相等 
						{
							if(maxx<a[x1][y1]+a[x2][y2])//更新最优值 
							{
								maxx=a[x1][y1]+a[x2][y2];
								max_x=i;max_y=j;max_t=t;
							}
							else if(maxx==a[x1][y1]+a[x2][y2])//如果等于最大值 
							{
								if(j<max_y)//先选择最靠西的 
								{
									max_x=i;max_y=j;max_t=t;
								}
								else if(i>max_x && j==max_y)//如果在相等的基础上，就选最靠南的 
								{
									max_x=i;max_y=j;max_t=t;
								}
							}
						}
					}
				}
			}
		}
	}
	printf("%d\n",maxx);//最后输出就好了 
	printf("%d %d ",max_x,max_y);
	if(max_t==0) printf("N\n");
	else		 printf("E\n");
	return 0;
}
```

---

## 作者：攀岩高手 (赞：0)

这题本来是挺简单的，但是身为蒟蒻的我还是做了一个多小时

下面我来说一下这道题的思路和主要过程：

- 读图

这里题目给了一个二进制的和，表示每个单位四周有没有墙。定义bool数组w[i][j][k]表示第i行第j列的k方向是否有墙（k=0, 1, 2, 3分别代表西、北、东、南）

- BFS求连通块

遍历每个单位跑一遍连通块，vis[i][j]表示(i, j)这个点是否访问过，cnt记录目前连通块的数量（目前有多少个连通块），num[i]记录第i个房间（连通块）包含的单位数量，fa[i][j]表示(i, j)这个点所在的连通块的编号， maxk记录最大的房间(连通块)所包含单位的数量

- 找出推掉后能使两个房间的总面积之和最大的墙

遍历每一个点的北墙和东墙，注意题目描述中的优先次序。maxx记录当前推掉一个墙以后两个房间面积（所含单位数量）的最大值。当这个点与它相邻的一个点的fa（所在连通块的编号）不同，且当这两个点所在连通块中所含单位数量之和大于maxx之时，更新答案


具体代码如下：

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
const int MAXN=55;
const int dir[4][2]={{0, -1}, {-1, 0}, {0, 1}, {1, 0}}; // 预处理下一个点与当前节点（房间）的位置关系（西、北、东、南）
struct node {int x, y;}; // 这里定义了一个结构体表示一个点的坐标
int n, m, t, k;
// 以下数组含义请见上面的思路和主要过程
int fa[MAXN][MAXN], num[MAXN*MAXN];
bool b[5], w[MAXN][MAXN][5];
bool vis[MAXN][MAXN];
queue<node> q; // 这里使用了一个STL队列作为BFS队列
int main()
{
    scanf("%d%d", &m, &n);
    memset(w, false, sizeof w);
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
        {
            scanf("%d", &t);
            // 将二进制数之和暴力分解
            // 然而蒟蒻并不会二进制解析，请见楼下题解
            while (t)
            {
                k=8; while (t<k) k>>=1;
                t-=k; w[i][j][(int)log2(k)]=true;
                // 注意这里k=0, 1, 2, 3分别代表西、北、东、南方向有墙
            }
        }
    memset(vis, false, sizeof vis);
    int cnt=0, maxk=0; 
    // bfs求连通块
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++) // 遍历每个节点
            if (!vis[i][j])
            {
                vis[i][j]=true; cnt++; int tmp=0;
                q.push((node){i, j});
                while (!q.empty())
                {
                    node u=q.front(); // 取出队列第一个节点
                    fa[u.x][u.y]=cnt; tmp++; // 将u所在的连通块的编号标记为cnt，tmp记录的是当前联通快所包含单位的数量
                    for (int k=0; k<4; k++) // 遍历4个方向
                        if (!w[u.x][u.y][k]) // 如果k方向没有墙
                        {
                            node v=(node){u.x+dir[k][0], u.y+dir[k][1]}; // v是u的k方向的相邻节点
                            if (!vis[v.x][v.y]) vis[v.x][v.y]=true, q.push(v); // 如果v没有访问过，则访问它
                        }
                    q.pop(); // 记得把已经用过的结点pop掉
                }
                num[cnt]=tmp; // 第cnt个连通块所包含的单位数量是tmp
                maxk=max(maxk, tmp); // 更新maxk
            }
    int maxx=0, maxi, maxj, maxd; // maxi，maxj，maxd分别表示答案的坐标和墙的方位
    for (int j=1; j<=m; j++) // 靠西优于靠东
        for (int i=n; i>=1; i--) // 靠南优于靠北
            for (int k=1; k<=2; k++) // 北墙优于东墙
            {
                int u=fa[i][j], v=fa[i+dir[k][0]][j+dir[k][1]]; // 取出(i, j)和其k方向的相邻节点所在的连通块的编号
                if (u!=v&&num[u]+num[v]>maxx) // 注意，只有u和v不在同一个房间内才能更新答案
                    maxx=num[u]+num[v], maxi=i, maxj=j, maxd=k;
            }
    printf("%d\n%d\n%d\n%d %d %c\n", cnt, maxk, maxx, maxi, maxj, maxd==1?'N':'E'); // 输出答案，maxd=1，2分别代表答案墙是(maxi, maxj)的北墙和东墙
    return 0;
}
```

---

## 作者：ViXbob (赞：0)

## 此题的思路其实是比较简单的，对于上面的两个输出，其实就是联通块的知识，但是此题加了一个东南西北墙来增加难度，其实无论是用何种方法来求每个点的东南西北强都是可以的，15个else if也不是不行啊,而我就是用这种最zz的方法求得，下面我给出对应表

> **1=W**
> **2=N**
> **3=WN**
> **4=E**
> **5=WE**
> **6=NE**
> **7=WNE**
> **8=S**
> **9=WS**
> **10=NS**
> **11=WNS**
> **12=ES**
> **13=WES**
> **14=NES**
> **15=WNES**
W,E,N,S分别为西东北南四个方向有墙。


## 代码如下，详解在代码旁边


```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,con=1,k,M=-1,Ms,X,Y;
int num[55][55],sum[]={0,1,2,4,8};
int move_x[]={0,0,1,0,-1};
int move_y[]={0,1,0,-1,0};
int judge[55][55],ans[5000];
char L;
struct node
{
    bool N,S,W,E;
    int x;
    int y;
}block[55][55],q[10000000];
void bfs(int x,int y)
{
    int fr=1,tail=0;
    q[1]=block[x][y];
    judge[x][y]=con;
    ans[con]++;
    while(fr>tail)
    {
        node t=q[++tail];
        for(int i=1;i<=4;i++)
        {
            int dx,dy;
            dx=t.x+move_x[i];
            dy=t.y+move_y[i];
            if(i==1)
            {
                if(!t.S&&!block[dy][dx].N&&!judge[dy][dx])
                {
                    q[++fr]=block[dy][dx];
                    judge[dy][dx]=con;
                    ans[con]++;
                }
            }
            else if(i==2)
            {
                if(!t.E&&!block[dy][dx].W&&!judge[dy][dx])
                {
                    q[++fr]=block[dy][dx];
                    judge[dy][dx]=con;
                    ans[con]++;
                }
            }
            else if(i==3)
            {
                if(!t.N&&!block[dy][dx].S&&!judge[dy][dx])
                {
                    q[++fr]=block[dy][dx];
                    judge[dy][dx]=con;
                    ans[con]++;
                }
            }
            else if(i==4)
            {
                if(!t.W&&!block[dy][dx].E&&!judge[dy][dx])
                {
                    q[++fr]=block[dy][dx];
                    judge[dy][dx]=con;
                    ans[con]++;
                }
            }
        }
    }
    M=max(ans[con],M);
    con++;return;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&num[i][j]);
            switch(num[i][j])//判断墙的方向
            {
                case 1:block[i][j].W=true;break;
                case 2:block[i][j].N=true;break;
                case 3:block[i][j].W=true,block[i][j].N=true;break;
                case 4:block[i][j].E=true;break;
                case 5:block[i][j].W=true,block[i][j].E=true;break;
                case 6:block[i][j].N=true,block[i][j].E=true;break;
                case 7:block[i][j].W=true,block[i][j].N=true,block[i][j].E=true;break;
                case 8:block[i][j].S=true;break;
                case 9:block[i][j].W=true,block[i][j].S=true;break;
                case 10:block[i][j].N=true,block[i][j].S=true;break;
                case 11:block[i][j].W=true,block[i][j].N=true,block[i][j].S=true;break;
                case 12:block[i][j].E=true,block[i][j].S=true;break;
                case 13:block[i][j].W=true,block[i][j].E=true,block[i][j].S=true;break;
                case 14:block[i][j].N=true,block[i][j].E=true,block[i][j].S=true;break;
                case 15:block[i][j].W=true,block[i][j].N=true,block[i][j].E=true,block[i][j].S=true;break;
            }
            block[i][j].x=j;
            block[i][j].y=i;
        }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(!judge[i][j])
                bfs(i,j);//核心代码1：求解联通块,用一个judge数组来存每个块是否被染过色,ans数组就来存每个颜色染了多少个块，con则代表有多少种颜色，也就是说有多少个房间
    for(int i=1;i<=m;i++)//下面是打通墙的代码
    {
        for(int j=1;j<=n;j++)
            for(int k=1;k<=4;k++)
            {
                int dx,dy,pp=0,S;
                dx=j+move_x[k];
                dy=i+move_y[k];//模拟打通哪堵墙
                if(judge[dy][dx]!=judge[i][j])pp=ans[judge[dy][dx]];//判断是不是有墙可以打通
                S=pp+ans[judge[i][j]];
                if(S>Ms)
                {
                    if(k%2==0)
                    {
                        L='E';X=j;Y=i;Ms=S;
                    }
                    else if(k%2==1)
                    {
                        L='N';X=j;Y=i;Ms=S;
                    }
                }
                else if(S==Ms)
                {
                    if(k%2==0)
                    {
                        if(j<X)
                        {
                            L='E';X=j;Y=i;
                        }
                        else if(j==X&&i>Y)
                        {
                            L='E';X=j;Y=i;
                        }
                    }
                    else if(k%2==1)
                    {
                        if(j<X)
                        {
                            L='N';X=j;Y=i;
                        }
                        else if(j==X&&i>Y)
                        {
                            L='N';X=j;Y=i;
                        }
                    }
                }
            }
    }
    if(block[Y][X].N&&block[Y][X].E&&ans[judge[Y-1][X]]==ans[judge[Y][X+1]])L='N';//特判，被坑了好几次。。。
    printf("%d\n%d\n%d\n%d %d %c",con-1,M,Ms,Y,X,L);
    return 0;
}
```
> 关于联通块的知识不懂得童鞋可以去看一下01迷宫
> 自带传送门 [01迷宫](https://www.luogu.org/problem/show?pid=1141)


---

## 作者：whistle998 (赞：0)

这个题不难

不知道大家对处理墙有没有好方法

我在这里介绍一个


题目说墙的号码是 1 2 4 8

这四个数显然都是2的n次幂

这里有一个性质 就是 1 2 4 8四个数可以组成1-15之内的任意一个数

且每个数只有一种组成方式

15就是1+2+4+8

14就是2+4+8

13就是1+4+8

12就是4+8

。。。。。

所以 每一个数字 代表了唯一的一种情况

我们就可以 判断了

如下

int x[4]={0,1,0,-1};

int y[4]={1,0,-1,0}; //代表四个搜索方向 

------------------------------------------------------



```cpp
inline void cal(int now,int p) {
    if(p>=8) d[now][1]=1,p-=8;else d[now][1]=0;
    if(p>=4) d[now][0]=1,p-=4;else d[now][0]=0;
    if(p>=2) d[now][3]=1,p-=2;else d[now][3]=0;
    if(p>=1) d[now][2]=1,p-=1;else d[now][2]=0;//对于一个点 有几个搜索方向
}
```
下面是我的代码













```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
const int MAXN=600;
const int MAXM=4000;
int n,m,id,ans,mx;
int f[MAXN][MAXN],sum[MAXM],d[MAXM][4],belong[MAXM];
bool vis[MAXN][MAXN];
int x[4]={0,1,0,-1};
int y[4]={1,0,-1,0};
struct node {
    int to;
    int next;
};
inline void read(int&x) {
    register char c=getchar();
    for(x=0;!isdigit(c);c=getchar());
    for(;isdigit(c);x=x*10+c-48,c=getchar());
}
inline int max(int a,int b) {return a<b?b:a;}
inline void cal(int now,int p) {
    if(p>=8) d[now][1]=1,p-=8;else d[now][1]=0;
    if(p>=4) d[now][0]=1,p-=4;else d[now][0]=0;
    if(p>=2) d[now][3]=1,p-=2;else d[now][3]=0;
    if(p>=1) d[now][2]=1,p-=1;else d[now][2]=0;
}
void DFS(int the_x,int the_y) {
    int now=(the_x-1)*m+the_y;
    cal(now,f[the_x][the_y]);
    vis[the_x][the_y]=true;
    belong[now]=id;
    ++sum[id];
    mx=max(sum[id],mx);
    for(int i=0;i<4;++i) {
        int next_x=the_x+x[i];
        int next_y=the_y+y[i];
        if(next_x<1||next_y<1||next_x>n||next_y>m) continue;
        if(vis[next_x][next_y]||d[now][i]) continue;
        DFS(next_x,next_y);
    }
}
int hh() {
    read(m);read(n);
    for(int i=1;i<=n;++i) 
      for(int j=1;j<=m;++j)
        read(f[i][j]);
    for(int i=1;i<=n;++i)
      for(int j=1;j<=m;++j) 
          if(!vis[i][j]) ++id,DFS(i,j);
    printf("%d\n%d\n",id,mx);
    ans=-1;char p;
    int b_x,b_y;
    for(int j=1;j<=m;++j)
     for(int i=n;i>=1;--i)  {
         if(d[(i-1)*m+j][3]&&i!=1) {
            if(belong[(i-1)*m+j]!=belong[(i-2)*m+j])
              if(sum[belong[(i-1)*m+j]]+sum[belong[(i-2)*m+j]]>ans) 
                b_x=i,b_y=j,ans=sum[belong[(i-1)*m+j]]+sum[belong[(i-2)*m+j]],p='N';
        }
         if(d[(i-1)*m+j][0]&&j!=m) {
              if(belong[(i-1)*m+j]!=belong[(i-1)*m+j+1])
                if(sum[belong[(i-1)*m+j]]+sum[belong[(i-1)*m+j+1]]>ans)
                  b_x=i,b_y=j,ans=sum[belong[(i-1)*m+j]]+sum[belong[(i-1)*m+j+1]],p='E';
        }
      }
    printf("%d\n%d %d %c\n",ans,b_x,b_y,p);
    return 0;
} 
int sb=hh();
int main(int argc,char**argv){;}
```

---

## 作者：qa24601 (赞：0)

嗯嗯、这道题很水的

不过大家的题解都花了大篇幅去解析墙壁的存在（至少咱看到的）

完全没有必要15个if-else嘛=-=

讲真、

```cpp
8 = 0b1000
4 = 0b0100
2 = 0b0010
1 = 0b0001
```
于是原来的超级难受的if-else就变成了这样的代码：
```cpp
int s = 0b1010;//s: 1 0 1 0 
if(s & 1)      //         ^
    goWest();  //         off!
s >>= 1;       //s: 1 0 1 # 
if(s & 1)      //       ^
    goNorth(); //       on!
s >>= 1;       //s: 1 0 # #
if(s & 1)      //     ^ 
    goEast();  //     off!
s >>= 1;       //s: 1 # # #
if(s & 1)      //   ^
    goSouth(); //   on!
```
然后别的大家都讲清楚了所以就这样了喵

啦啦啦~


---

## 作者：快乐船长 (赞：0)

题目大意：给出一个 n\*m 矩阵，矩阵代表了一个大房间，然后矩阵的每个元素代表了该模块的信息，用 1 表示 WEST 方向是墙壁，2 表示 NORTH 方向是墙， 4 表示 EAST 方向是墙， 8 表示 SOUTH 方向是墙，题目所给矩阵的元素值就是该模块所有墙壁数值总和，现在要求统计这个大房间被分成了几个区域，其中最大区域包含几个模块。

 
显然的，BFS，DFS可解，我用的是并查集（= =！不想写搜索，对搜索的代码有阴影……）。其实这不是重点，关键是怎么把数字矩阵转化成我们想要的图形矩阵，就是从一个模块所有墙壁数值总和看出这个模块都有哪几面墙，这是这道题的亮点

 
本人用的应该是最笨的方法了，直接枚举打表所有可能……就 0 ~ 15 嘛，也不多哈……

 
看了神牛的报告，发现，用位运算的话会风骚很多……

 
1 的2进制 0001,2 的是 0010，4 的是 0100，8 的是 1000，例如 11 取2进制 1011，只有 4 和 11 取 & 运算是 0 ，即该模块在 4 方向（也就是 EAST 方向）是通的。

代码：

        
        
        
```cpp
#include<stdio.h>
#include<string.h>
#define M 55
int father[M*M],n,m;
int findx(int x)
{
    if(father[x]!=x)
        father[x]=findx(father[x]);
    return father[x];
}
void merge(int a,int b)
{
    int x,y;
    x=findx(a);
    y=findx(b);
    if(x!=y)father[x]=y;
    //father[a]=findx(a);
    //father[b]=findx(b);
}
void fun(int a,int i,int j)
{
    if(a==0){
        merge(m*(i-1)+j,m*(i-1)+j+1);
        merge(m*(i-1)+j,m*(i-1)+j-1);
        merge(m*(i-1)+j,m*(i-2)+j);
        merge(m*(i-1)+j,m*i+j);
    }
    else if(a==1){
        merge(m*(i-1)+j,m*(i-1)+j+1);
        merge(m*(i-1)+j,m*(i-2)+j);
        merge(m*(i-1)+j,m*i+j);
    }
    else if(a==2){
        merge(m*(i-1)+j,m*(i-1)+j+1);
        merge(m*(i-1)+j,m*(i-1)+j-1);
        merge(m*(i-1)+j,m*i+j);
    }
    else if(a==3){
        merge(m*(i-1)+j,m*(i-1)+j+1);
        merge(m*(i-1)+j,m*i+j);
    }
    else if(a==4){
        merge(m*(i-1)+j,m*(i-1)+j-1);
        merge(m*(i-1)+j,m*(i-2)+j);
        merge(m*(i-1)+j,m*i+j);
    }
    else if(a==5){
        merge(m*(i-1)+j,m*(i-2)+j);
        merge(m*(i-1)+j,m*i+j);
    }
    else if(a==6){
        merge(m*(i-1)+j,m*(i-1)+j-1);
        merge(m*(i-1)+j,m*i+j);
    }
    else if(a==7) merge(m*(i-1)+j,m*i+j);
    else if(a==8){
        merge(m*(i-1)+j,m*(i-1)+j+1);
        merge(m*(i-1)+j,m*(i-1)+j-1);
        merge(m*(i-1)+j,m*(i-2)+j);
    }
    else if(a==9){
        merge(m*(i-1)+j,m*(i-2)+j);
        merge(m*(i-1)+j,m*(i-1)+j+1);
    }
    else if(a==10){
        merge(m*(i-1)+j,m*(i-1)+j-1);
        merge(m*(i-1)+j,m*(i-1)+j+1);
    }
    else if(a==11) merge(m*(i-1)+j,m*(i-1)+j+1);
    else if(a==12){
        merge(m*(i-1)+j,m*(i-1)+j-1);
        merge(m*(i-1)+j,m*(i-2)+j);
    }
    else if(a==13) merge(m*(i-1)+j,m*(i-2)+j);
    else if(a==14) merge(m*(i-1)+j,m*(i-1)+j-1);
}
void check()
{
    int i,cnt,time[M*M];
    memset(time,0,sizeof(time));
    for(cnt=0,i=1;i<=n*m;i++)
    {
        time[father[i]]++;
        if(father[i]==i)
            cnt++;
    }
    int max=0;
    for(i=1;i<=n*m;i++)
        if(time[i]>max)max=time[i];
        printf("%d/n%d/n",cnt,max);
}
int main()
{
    int i,j,a;
    while(~scanf("%d%d",&n,&m))
    {
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                father[m*(i-1)+j]=m*(i-1)+j;
        }
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                scanf("%d",&a);
                fun(a,i,j);
            }
        }
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                father[m*(i-1)+j]=findx(m*(i-1)+j);
        }
        check();
    }
    return 0;
}
```

---

## 作者：Jason_Yvan (赞：0)

看题解没有新方法来发一篇题解。

处理地图的时候可以将原地图设置为两倍，更加好处理

代码内有详解

直接上代码C++：

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<cmath>
#include<algorithm>
#define Size 500
using namespace std;
int read(){
    int sum=0,fg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')fg=-1;c=getchar();}
    while(isdigit(c)){sum=sum*10+c-'0';c=getchar();}
    return sum*fg;
}
int n,m,N,M;//将地图变为两倍 
int map[Size][Size];//0为房间，1为房间过道，2为墙 
struct node1{
    int count,belong;//count为房间面积大小，belong为连通块的编号（将同一个连通块标记） 
}Map[Size][Size];
struct node2{
    int x,y,direct,val;//direct为墙的方向，val为房间面积 
}Wall[1000010];
int num;
bool p1[Size][Size],p2[Size][Size];
int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
void print(int type){//调试信息 
    if(type==0)
        for(int i=1;i<=N;i++,puts(""))
            for(int j=1;j<=M;j++)
                printf("%3d ",p1[i][j]);
    else if(type==1)
        for(int i=1;i<=N;i++,puts(""))
            for(int j=1;j<=M;j++)
                printf("%3d ",p2[i][j]);
    else if(type==2)
        for(int i=1;i<=N;i++,puts(""))
            for(int j=1;j<=M;j++)
                printf("%3d ",map[i][j]);
    else if(type==3)
        for(int i=1;i<=N;i++,puts(""))
            for(int j=1;j<=M;j++)
                printf("%3d ",Map[i][j].count);
    else if(type==4)
        for(int i=1;i<=N;i++,puts(""))
            for(int j=1;j<=M;j++)
                printf("%3d ",Map[i][j].belong);
    puts("");
}
int MAP(int x,int y,int w){//建立地图，判断墙的方向 
    if(w>=8){w-=8;map[x<<1|1][y<<1]=2;}
    else map[x<<1|1][y<<1]=1;
    if(w>=4){w-=4;map[x<<1][y<<1|1]=2;}
    else map[x<<1][y<<1|1]=1;
    if(w>=2){w-=2;map[(x<<1)-1][y<<1]=2;}
    else map[(x<<1)-1][y<<1]=1;
    if(w>=1){w-=1;map[x<<1][(y<<1)-1]=2;}
    else map[x<<1][(y<<1)-1]=1;
}
void init(){//预处理 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=M;j++)
            map[i<<1|1][j]=1;//将房间过道都设为1 
    for(int i=1;i<=m;i++)
        for(int j=1;j<=N;j++)
            if(map[j][i<<1|1])map[j][i<<1|1]=2;//特殊处理 将已有过道设为墙 
            else map[j][i<<1|1]=1;
    for(int i=1;i<=N;i++)
        map[i][1]=map[i][M]=2;//处理边界地图 
    for(int i=1;i<=M;i++)
        map[1][i]=map[N][i]=2;
}
int dfs1(int x,int y){//求房间面积大小 
    int ans=0;
    if(!map[x][y])ans++;
    p1[x][y]=1;
    for(int i=0;i<4;i++){
        int x0=x+d[i][0],y0=y+d[i][1];
        if(map[x0][y0]==2 || p1[x0][y0])continue;
        ans+=dfs1(x0,y0);
    }
    return ans;
}
void dfs2(int x,int y,int val,int belong){//按照第一次dfs的路径搜，将房间面积大小和属于哪个连通块出入地图中 
    p2[x][y]=1;
    Map[x][y].count=val;
    Map[x][y].belong=belong;
    for(int i=0;i<4;i++){
        int x0=x+d[i][0],y0=y+d[i][1];
        if(!p1[x0][y0] || p2[x0][y0])continue;
        dfs2(x0,y0,val,belong);
    }
}
bool cmp(node2 a,node2 b){return a.val==b.val?a.y==b.y?a.x>b.x:a.y<b.y:a.val>b.val;}//输出排序 
int main(){
    m=read(),n=read();
    M=m<<1|1,N=n<<1|1;
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            MAP(i,j,read());
        }
    }
    //print(2);
    int MAX_room=-1,sum=0;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            if(map[i][j]!=2 && p1[i][j]!=1){
                sum++;//连通块个数 
                int ans=dfs1(i,j);//房间面积大小 
                MAX_room=max(MAX_room,ans);
                dfs2(i,j,ans,sum);//将属于哪个连通块的值和房间面积大小存入地图中 
            }
        }
    }
    //print(0);
    //print(1);
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            if(map[i][j]==2){
                if(Map[i-1][j].belong!=Map[i+1][j].belong){//不属于同一个连通块 
                    int tmp=Map[i-1][j].count+Map[i+1][j].count;//把上下方向的墙打通 
                    Wall[++num].direct=1;//方向向北 
                    Wall[num].x=i;Wall[num].y=j;
                    Wall[num].val=tmp;
                }
                if(Map[i][j-1].belong!=Map[i][j+1].belong){
                    int tmp=Map[i][j-1].count+Map[i][j+1].count;//把左右方向的墙打通
                    Wall[++num].direct=2;//方向向东 
                    Wall[num].x=i;Wall[num].y=j;
                    Wall[num].val=tmp;
                }
            }
        }
    }
    sort(Wall+1,Wall+num+1,cmp);
    //print(3);
    //print(4);
    int x=Wall[1].x;
    int y=Wall[1].y;
    int wall=Wall[1].direct;
    int MAX=Wall[1].val;
    printf("%d\n%d\n%d\n",sum,MAX_room,MAX);
    if(wall==1)x++;//特殊处理 
    if(wall==2)y--;
    printf("%d %d %c\n",x>>1,y>>1,wall==1?'N':'E');
    return 0;
}
```

---

## 作者：Till_Gloam (赞：0)

本题用的广搜

对于每个格子，存下它的4堵墙（0/1表示）；

对每个联通块进行广搜（编号：id，记大小：big，顺便找出最大房间大小：ans . s[0]）

最后枚举每一堵墙，更新答案；

       




    
            

    
    
    
            
                
                
                    
                    
    
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
bool p[51][51];
int cnt,big[2501],d[4][2]={{1,0},{0,1},{0,-1},{-1,0}},n,m;
struct node{
    int wall[4],id;
}map[51][51];
struct n{
    int x,y;
}q[2501];
struct a{
    int s[2],x,y;
    char w;
}ans;
inline void bfs(int x,int y){//广搜
    p[x][y]=1;
    map[x][y].id=++cnt;
    big[cnt]++;
    q[1].x=x;
    q[1].y=y;
    int h=1,f=0;
    while(f<h){
        f++;
        for(int i=0;i<4;i++){//四个方向
            int x1=q[f].x+d[i][0];
            int y1=q[f].y+d[i][1];
            if(!x1 || !y1 || x1>n || y1>m) continue;
            if(!p[x1][y1]){         //避免重复搜索，死循环
                if(d[i][0]==0){       //横着动
                    if(!map[q[f].x][q[f].y].wall[d[i][1]+2]){      //可自己推一下：判断两格之间无墙
                        p[x1][y1]=1;
                        q[++h].x=x1;
                        q[h].y=y1;       //入队
                        map[x1][y1].id=cnt;      //记编号
                        big[cnt]++;        //更新大小
                    }
                }
                else         //同上、竖着动
                    if(!map[q[f].x][q[f].y].wall[d[i][0]+1]){
                        p[x1][y1]=1;
                        q[++h].x=x1;
                        q[h].y=y1;
                        map[x1][y1].id=cnt;
                        big[cnt]++;
                    }
            }
        }
    }
    ans.s[0]=max(ans.s[0],big[cnt]);       //更新最大房间大小
}
int main(){
    int i,j,k;
    scanf("%d%d",&m,&n);
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            scanf("%d",&k);
            if(k>=8){
                k-=8;
                map[i][j].wall[2]=1;
            }
            if(k>=4){
                k-=4;
                map[i][j].wall[3]=1;
            }
            if(k>=2){
                k-=2;
                map[i][j].wall[0]=1;
            }
            if(k) map[i][j].wall[1]=1;         //对每个格子记墙（北 0  西 1  南 2 东 3）
        }
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            if(!p[i][j]) bfs(i,j);         //广搜每个联通块
        }
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            for(int k=0;k<4;k++){
                int x1=i+d[k][0];
                int y1=j+d[k][1];
                if(x1>n || y1>m || x1<i || y1<j) continue;          //加了剪枝：防止重复搜
                int d1=map[i][j].id,d2=map[x1][y1].id;
                if(d1==d2) continue;         //同一个房间中就跳过
                if(big[d1]+big[d2]>ans.s[1]){          //比答案优，直接更新
                    ans.s[1]=big[d1]+big[d2];
                    if(d[k][0]==0){
                        ans.x=i;
                        ans.y=min(j,y1);           //取西格子的东墙
                        ans.w='E';
                    }
                    else{
                        ans.x=max(i,x1);           //取南格子的北墙
                        ans.y=j;
                        ans.w='N';
                    }
                }
                else if(big[d1]+big[d2]==ans.s[1]){          //若与答案相等
                    int xx,yy;           //先将信息记下，与答案进行比较
                    char ww;
                    if(d[k][0]==0){
                        xx=i;
                        yy=min(j,y1);
                        ww='E';
                    }
                    else{
                        xx=max(i,x1);
                        yy=j;
                        ww='N';
                    }
                    if(yy>ans.y) continue;
                    if(yy<ans.y){         //更西
                        ans.x=xx;
                        ans.y=yy;
                        ans.w=ww;
                    }
                    else{
                        if(xx<ans.x) continue;
                        if(xx>ans.x){            //更东
                            ans.x=xx;
                            ans.w=ww;
                        }
                        else if(ww=='N') ans.w='N';             //同一个格子北墙优
                    }
                }
            }
        }
    printf("%d\n%d\n%d\n%d %d %c",cnt,ans.s[0],ans.s[1],ans.x,ans.y,ans.w);       //输出答案， AC
    return 0;
}
```

---

## 作者：Marchia (赞：0)

搜索题

四个问题，一二个建图后填充颜色（其实也就是填数字）可以解决

三四问需要再搜一次，两层循环，记住先循环j再循环i，因为题目的优先方向


```cpp
#include<iostream>
#include<cstdio>
#define maxn 60
using namespace std;
int wall[maxn][maxn][4]={0},map[maxn][maxn]={0},N,M,dx[5]={1,0,-1,0},dy[5]={0,1,0,-1};
void savewalls(int a,int b,int c){
    if(c>=8){
        c-=8;
        wall[a][b][0]=1;
    }
    if(c>=4){
        c-=4;
        wall[a][b][1]=1;
    }
    if(c>=2){
        c-=2;
        wall[a][b][2]=1;
    }
    if(c>=1){
        c-=1;
        wall[a][b][3]=1;
    }
}
void mkmap(int a,int b,int colour){
    map[a][b]=colour;
    for(int i=0;i<4;i++){
        int nx=a+dx[i],ny=b+dy[i];
        if(nx>=0&&nx<N&&ny>=0&&ny<M&&map[nx][ny]==0&&wall[a][b][i]==0)
            mkmap(nx,ny,colour);
    }
}    
int main(){
    int colour=1,tmp;
    cin>>M>>N;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++){
            cin>>tmp;
            savewalls(i,j,tmp);
        }
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++){
            if(map[i][j]==0){
                mkmap(i,j,colour);
                colour++;
            }
        }
    cout<<colour-1<<endl;//pb en
    int num[maxn*maxn]={0};
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            num[map[i][j]]++;
    tmp=1;
    for(int i=1;i<colour;i++) if(num[tmp]<num[i]) tmp=i;
    cout<<num[tmp]<<endl;//pb två
    char ansdir;
    int ansx,ansy,ansize=0;
    for(int j=0;j<M;j++)
        for(int i=N-1;i>=0;i--){
            int tmpsize;
            if(i-1>=0&&i-1<N&&wall[i][j][2]==1&&map[i][j]!=map[i-1][j]){
                tmpsize=num[map[i][j]]+num[map[i-1][j]];
                if(tmpsize>ansize){
                    ansize=tmpsize;
                    ansx=i,ansy=j;
                    ansdir='N';
                }
            }
            if(j+1>=0&&j+1<M&&wall[i][j][1]==1&&map[i][j]!=map[i][j+1]){
                tmpsize=num[map[i][j]]+num[map[i][j+1]];
                if(tmpsize>ansize){
                    ansize=tmpsize;
                    ansx=i,ansy=j;
                    ansdir='E';
                }
            }
        }
    cout<<ansize<<endl<<ansx+1<<" "<<ansy+1<<" "<<ansdir<<endl;//last pb
    return 0;
}
```

---

