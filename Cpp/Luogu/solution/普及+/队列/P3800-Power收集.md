# Power收集

## 题目背景

据说在红雾异变时，博丽灵梦单身前往红魔馆，用十分强硬的手段将事件解决了。

然而当时灵梦在 Power 达到 MAX 之前，不具有“上线收点”的能力，所以她想要知道她能收集多少 P 点，然而这个问题她答不上来，于是她找到了学 OI 的你。

## 题目描述

可以把游戏界面理解成一个 $N$ 行 $M$ 列的棋盘，有 $K$ 个格子上有 $P$ 点，其价值为 $\operatorname{val}(i,j)$。

初始灵梦可以选择在第一行的任意一个格子出发，每秒她必须下移一格。

灵梦具有一个左右移动的速度 $T$，可以使她每秒向左或右移动至多 $T$ 格，也可以不移动，并且不能折返。移动可视为瞬间完成，不经过路途上的点，只能获得目标格子的 P 点。

求最终她能获得的 POWER 值最大是多少？

## 说明/提示

对于 $40\%$ 的测试点，$1 \le N,M,T,K \le 200$。

对于 $100\%$ 的测试点，$1 \le N,M,T,K \le 4000$。

$v \le 100$，$N,M,K,T$ 均为整数。

by-szc

## 样例 #1

### 输入

```
3 3 4 1
1 1 3
1 2 1
2 2 3
3 3 3
```

### 输出

```
9```

# 题解

## 作者：灵乌路空 (赞：35)

先无良宣传一下博客 $wwwwww$    
[文章列表 - 核融合炉心 - 洛谷博客](https://www.luogu.org/blog/koishikoishi/)

------------

## 知识点 : $DP$ 优化 , 单调队列

- ### 题意:
  
  有一个 $(N\times M)$ 大小的矩阵  
  部分矩阵中的点 **带有价值**    
  可以选择第一行 , 任何一个位置作为起点 .   
  
  对于当前的位置 $(i,j)\ $ (表示在第 $i$ 行第 $j$ 列)    
  可以转移到: $(i+1,\ [j-T , j+T]\ )$ 中任意一个点 $(j-T>0\ ,\ j+t\leqslant M)$    
  并且获得当前所在点的价值  .  
  
  **求** : 可以取得的 最大价值和
  
  样例解释:  
  ![样例](https://i.loli.net/2019/07/15/5d2c6d5de7de334156.jpg)
  
  1.灵梦从 $(1,1)$出发 : 总价值$+3$ , 现在为 $3$   
  2.灵梦转移到 $(2,2)$ : 总价值$+3$ ,现在为 $6$   
  3.灵梦转移到 $(3,3)$ : 总价值$+3$ ,现在为 $9$    
  故 , 总价值为 $9$
  
------------

- ### 分析题意:

  很显然  这是一道 $DP$  
  状态转移方程 极其简单 :  
  用 $f[i][j]$ 表示在点 $(i,j)$ 能到达的最大价值和 ,
  则有: $f[i][j] = max(f[i-1][k]) + v[i][j]\ ,\ (k\in [j-T , j+T]\ )$  
  
  - 暴力:  
    直接枚举所有点 , 再枚举能转移到他的点 ?  
    复杂度 $O(N^3)$ 级别 ,   
    $40Pts$ 到手  
  
  考虑优化 :  
     
  - 可知:  
    第 $i$ 行上点的 $f[][]$ , 只与第 $i-1$ 行有关    
    则可将每相邻的两行 , 单独拆分出来考虑 :
  
  如图:  
  
  ![滑动窗口](https://i.loli.net/2019/07/15/5d2c766d490dc15943.jpg)
  
  可以发现 :   
    1. 转移到 点$(i,j)$ 的点 ,    
       为 $i-1$ 行 , 区间 $\underline{[j-T,j+T]}$ 中 , $f[][]$ 最大的点 
  
    2. 转移到 点$(i,j+1)$ 的点 ,    
       为 $i-1$ 行 ,区间 $\underline{[j-T+1,j+T+1]}$ 中 , $f[][]$ 最大的点  
  
    3. 转移到 点$(i,j+2)$ 的点 ,    
       为 $i-1$ 行 ,区间 $\underline{[j-T+2,j+T+2]}$ 中 , $f[][]$ 最大的点  
  
  后两个区间 ,   
  都可以通过 上一个区间 **右移一个单位** 得到  
  这不禁让我们想到了另一道题 :    [P1886 滑动窗口](https://www.luogu.org/problemnew/show/P1886)  
  如果您还未学习过单调队列 , 推荐这篇文章:    
  [【洛谷日报﻿#9】 [Sweetlemon] 朝花中学OI队的奋斗历程——浅谈单调队列](https://sweetlemon.blog.luogu.org/dan-diao-dui-lie)  
  
  这种 **滑动窗口型** 最值问题 ,   
  显然 , 可以通过 单调队列 来进行维护 .   
  
  由上 ,  我们便找到了一种合适 $DP$ 优化方法: 单调队列优化.

------------
- ### 算法实现:

  假设,现在已经更新到第 $i$ 行 :    
  
   1. 先初始化单调队列 ,   
      将能够更新 $(i,1)$ 的点$(i,k) , (k \in [1,1+T])$ ,  
      加入单调队列  
   2. 开始循环 , 更新 $[1,M]$ 中每一个点 :  
      - 将能够转移到 $j$ 的最右侧一个点 $(i-1 , j+T)$ , 加入队列  
      - 使用单调队列找到能够转移到 $j$ 的点的最大$f[][]$  
      - 用最大的$f[][]$ 更新 $f[i][j]$
   3.  **清空单调队列** , 外层循环进入下一层 ,更新第 $i+1$ 行   
   
  最后找到最后一行中  ,   
  最大的 $f[N][j]$ ,     
  即所求最值 . 
   
------------
上代码: 

由于使用了手写数组模拟队列 ,   
清空时只需重置头尾指针 , 及队首元素即可 .  
常数吊打 $deque$

```cpp
#include<cstdio>
#include<ctype.h>
#include<cstring>
#define int long long
#define max(a,b) a>b?a:b
//=====================================
const int MARX = 4e3+10;
int n,m,k,t, now,ans;
int f[MARX][MARX];
int head=1,tail=1;//手写双端队列 
int q[MARX]={9223372036854775807};//为q[0]赋一个极大值,来防止插入元素时越界 
//=====================================
inline int read()
{
	int fl=1,w=0;char ch=getchar();
	while(!isdigit(ch) && ch!='-') ch=getchar();
	if(ch=='-') fl=-1;
	while(isdigit(ch)){w=w*10+ch-'0',ch=getchar();}
	return fl*w;
}
void in(int x)//向单调队列中插入元素 
{
	while(f[now-1][x]>f[now-1][q[tail]] && tail>=head) 
	  tail--;//取出队尾小于插入元素的数 , 以保证单调性 
	q[++tail]=x;//插入队尾 
}
int find(int x)//查询元素 
{
	if(x+t<=m)in(x+t);//将能转移到x点 的 最后一个元素 x+t 插入队列 
	while(q[head]+t<x) head++;//找到队首第一个能够转移到x的点 
	return q[head]; 
}
//=====================================
signed main()
{
	n=read(),m=read(),k=read(),t=read();
	while(k--)
	{
	  int x=read(),y=read(),w=read();
	  f[x][y]=w;
	}
	
	for(now=2;now<=n;now++)//从第二行,开始转移 
	{
	  for(int i=1;i<=t;i++) in(i);//初始化单调队列 , 满足能够 转移j=1的点 
	  for(int j=1;j<=m;j++) f[now][j]+=f[now-1][find(j)];// 进行转移 
	  head=tail=1 , q[1]=0;//清空队列 
	}
	
	for(int i=1;i<=m;i++)//取得最大值 
	  ans=max(ans,f[n][i]);
	printf("%lld",ans);
}
```

------------

完成了这篇题解 , 东方众信仰 $++$

---

## 作者：xcxc82 (赞：18)

# P3800 Power收集 题解

## [传送门](https://www.luogu.com.cn/problem/P3800)
前排声明:蒟蒻刚学oi没多久,写的可能比较粗糙,望谅解

## 大致题意

给一个$N×M$大小的矩阵

其中有k个点包含一个带有价值的P点

每一行中的一个格子i都可以从上一行中的第$[i-t,i+t]$个格子中转移过来

求可以获得的最大价值

## 分析


大致思路和[P1725 琪露诺](https://www.luogu.com.cn/problem/P1725)很像,只是换了一种形式而已

既然每一个格子$i$都可以从上一行中的第$ [i-t,i+t] $个格子中转移过来

我们**设$a[i][j]$为第$i$行第$j$个点的价值大小**

容易得到状态转移方程:

- $dp[i][j]=max(dp[i-1][k])+a[i][j] (j-T<=k<=j+T)$

- 因此,对于每一个$dp[i][j]$来说

他的值均是由上一行中$[j-t,j+t]$区间中的最大值转移过来的

![](https://cdn.luogu.com.cn/upload/image_hosting/f400j4mf.png)

###### (~~懒得找城管的图了,只好拿之前cirno的图改了一下~~)

可以看出这是一个滑动区间求最值的问题

可以考虑用单调队列来优化


在进行第$i$行第$j$列的转移前

利用滑动窗口将第$i-1$行中$[j-t,j+t]$的最大值来求出来

这里~~闲着无聊~~做了个$gif$

![](https://img-blog.csdnimg.cn/20200707134646322.gif)

## 代码分析

开一个数组 $q$ 模拟队列,用来滑动求最值

首先初始化第一行的$dp[i][j]$

第2~n行则利用$q$来求上一行的最大值进行转移

- **swp函数**

实现队列初始化功能

将前 $t$ 个数加入队列



- **swi函数**

当插入新元素时

先判断队列是否在$[1,m]$的区间内(不判会RE)

如果在区间内:

$1$.调整队列单调性

$2$.入队

反之,超出范围,不入队

$3$.去掉"超时"元素

贴上丑陋的代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 4010
int tail=0,head=1;
int n,m,k,t,ans; 
int q[MAXN],a[MAXN][MAXN],dp[MAXN][MAXN];
void queue_empty(){//清空窗口 
	tail=0,head=1;
}
void swi(int x,int last){//插入元素
   if(x+t<=m){//判断是否超过边界,不加会RE 
   	while(dp[last][x+t]>dp[last][q[tail]]&&tail>=head){//单调队列 
		tail--;
	}
	   
	q[++tail]=x+t;
   }
	
	while(q[head]+t<x) head++;	
}
void swp(int last){//初始化窗口 
	for(int i=1;i<=t;i++){
		while(dp[last][i]>dp[last][q[tail]]&&tail>=head){
		tail--;
	}
	  
	q[++tail] = i;
	}
}
int main(){

	scanf("%d%d%d%d",&n,&m,&k,&t);
	for (int i = 1; i <= k; i++) {
		int x, y, z;
		scanf("%d%d%d",&x,&y,&z);
		a[x][y] = z;
	}
   for(int i=1;i<=n;i++){//第一行初始化
   	dp[1][i]=a[1][i];
   }
   
   for(int i=2;i<=n;i++){
   	swp(i-1);
   	for(int j=1;j<=m;j++){
   		
   			swi(j,i-1);
   			
		  dp[i][j]=dp[i-1][q[head]]+a[i][j]; 
		  
	   }
	   queue_empty();
   }
   for(int i=1;i<=m;i++){
		ans=max(dp[n][i],ans);
	}
	cout<<ans;
}
```
如有错误欢迎dalao们指出qwq






---

## 作者：_edge_ (赞：16)

**本篇题解将带你走进优化的极致！**

这题目是好题，让我们来一步一步分析。

首先是最暴力的爆搜，复杂度是阶乘级别的，看样子会 TLE 起飞。

考虑优化成记忆化搜索，记录状态 $f_{i,j}$ 表示当前 $(i,j)$ 走到最后一行产生的最大贡献，复杂度 $O(nmt)$，可以拿到 40 分。

这一步之后我们考虑将其改为循环的 DP，第一维枚举行，第二维枚举列，第三维枚举前一行的最大值，优化成这样之后就会发现第三维的枚举是一个滑动窗口，可以使用单调队列优化。

$f_{i,j}=\max(f_{i-1,k})+a_{i,j}$ 其中 $k$ 的范围是一个单调的滑动窗口。

于是优化成 $O(nm)$ 的 DP 了！

这样已经可以拿到 100 分了，但是我们的目标不止这样！

考虑优化一下内存，显然 f 数组是可以滚存的，不过还有一个要记录地图。

不妨想一想，如果说记录地图的内存进一步优化，优化成 $k$ 的内存呢？

其实这个想法是可以的，可以使用一个指针来维护，从而我们将 128 MB 的内存优化为了 1 MB 不到。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
const int INF=4005;
int n,m,k1,t,f[5][INF],q[INF],ql,qr;
struct _node_data {
        int x,y,z;
} a[INF];
bool cmp(_node_data xx,_node_data yy) {
        if (xx.x!=yy.x) return xx.x<yy.x;
        else return xx.y<yy.y;
}
signed main()
{
        scanf("%lld %lld %lld %lld",&n,&m,&k1,&t);
        for (int i=1; i<=k1; i++)  {
                int x=0,y=0,z=0;
                scanf("%lld %lld %lld",&x,&y,&z);
                a[i].x=x; a[i].y=y; a[i].z=z;
        }
        for (int i=1; i<=m; i++) f[0][i]=0;
        sort(a+1,a+1+k1,cmp); int ll=1;
        for (int i=1; i<=n; i++) {
                // cout<<a[ll].x<<"\n";
                // if (a[ll].x!=i) continue;
                int u=(i&1),v=(i&1)^1;
                ql=1,qr=0; int rr=1;
                for (int j=1; j<=m; j++) {
                        int l=max(1ll,j-t),r=min(m,j+t);
                        while (ql<=qr && q[ql]<l) ql++;
                        for (int k=rr; k<=r; k++) {
                                while (ql<=qr && f[v][q[qr]]<=f[v][k]) qr--;
                                q[++qr]=k;
                        }
                        rr=r+1;
                        int Map1=0;
                        while (ll+1<=k1 && a[ll+1].y<=j && a[ll+1].x==i) ll++;
                        if (a[ll].x==i && a[ll].y==j) Map1=a[ll].z,ll++;
                        // cout<<i<<" "<<j<<" "<<Map1<<" "<<ll<<"\n";
                        if (ql<=qr) f[u][j]=f[v][q[ql]]+Map1;
                }
        }
        // for (int i=1; i<=n; i++) {
        //         for (int j=1; j<=m; j++)
        //                 cout<<f[i][j]<<" ";
        //         cout<<"\n";
        // }
        int ans=0;
        for (int i=1; i<=m; i++)
                ans=max(ans,f[n&1][i]);
        cout<<ans<<"\n";
        return 0;
}
```

好了，那么到现在 $O(nm)$ 的 DP 已经优化到了极致。

现在我们来考虑依赖 $k$ 的复杂度。

首先朴素的 $O(k^2)$ 的想法事考虑两个行相邻的，如果满足行的差小于等于列的差除以每次能移动的距离，那么两个肯定事可行的，也就是可以转移的。

这种复杂度就不依赖 $n,m$ 了，$n$ 和 $m$ 甚至可以开到 $10^{18}$。

```cpp
a[i].x<=a[i+1].x 1<=i<n
i 1->n
j 1->i-1
if abs(a[j].y-a[i].y)<=t*(a[i].x-a[j].x)
    fi=max(fj+a[i].z,fi)
```

上面事伪代码，将除转换为乘，避免损失精度。

看到这里难道就不能再进行优化了么？不！

我们将 `abs(a[j].y-a[i].y)<=t*(a[i].x-a[j].x)` 拆开来变成了:

$a[j].y+t \times a[j].x \le t \times a[i].x+a[i].y$

$a[j].y-t \times a[j].x \ge a[i].y-t \times a[i].x$

设 $x_i=t \times a[i].x+a[i].y,y_i=a[i].y-t \times a[i].x$。

这两个柿子可以做二维偏序，复杂度可以做到 $O(k \log k)$。

至于你用树状数组还是 CDQ 分治都不重要。

树状数组的话就是先离散化，然后按 $x$ 排序，如果 $x$ 相同那么按 $y$ 从大到小排序，显然后面的 $x$ 肯定大于等于前面的，统计一下大于等于当前的 $y$ 的最大权值就可以了。

目前这种方法排在最优解 rk1，32 ms。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define lowbit(x) x& -x
using namespace std;
const int INF=4005;
int n,m,k,t,ax[INF+INF],tree[INF<<1],f[INF<<1],tot,ans;
struct _node_data {
        int x,y,z;
} a[INF];
bool cmp(_node_data xx,_node_data yy) {
        if (xx.x!=yy.x) return xx.x<yy.x;
        else return xx.y<yy.y;
}
void add(int x,int y) {
        for (; x<=8000; x+=lowbit(x))
                tree[x]=max(y,tree[x]);
        return;
}
int query(int x) {
        int sum=0;
        for (; x>=1; x-=lowbit(x))
                sum=max(sum,tree[x]);
        return sum;
}
signed main()
{
        scanf("%d %d %d %d",&n,&m,&k,&t);
        for (int i=1; i<=k; i++) {
                int x=0,y=0,z=0;
                scanf("%d %d %d",&x,&y,&z);
                a[i].x=x*t+y;
                a[i].y=y-x*t;
                a[i].z=z;
                ax[++tot]=a[i].x;
                ax[++tot]=a[i].y;
                // cout<<a[i].x<<" "<<a[i].y<<"\n";
        }
        sort(ax+1,ax+1+tot);
        int res=unique(ax+1,ax+1+tot)-ax-1;
        for (int i=1; i<=k; i++)
                a[i].x=lower_bound(ax+1,ax+1+res,a[i].x)-ax,
                a[i].y=lower_bound(ax+1,ax+1+res,a[i].y)-ax;
        sort(a+1,a+1+k,cmp);
        // for (int i=1; i<=k; i++)
        // cout<<a[i].x<<" "<<a[i].y<<" "<<a[i].z<<" oveer\n";
        for (int i=1; i<=k; i++) {
                int ans1=query(a[i].y);
                f[i]=ans1+a[i].z;
                add(a[i].y,f[i]);
                ans=max(ans,f[i]);
        }
        cout<<ans<<"\n";
        return 0;
}

```

**如果有问题还请指出。**

---

## 作者：Seanq (赞：15)

**P3800 Power收集题解**  
出题人标程无误，是楼上、下的dp初始化出了问题！  
（此不是抄袭）先来看 s_a_b_e_r julao 的AC代码：  
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int N,M,K,T,ans;
struct SA{
int dp,x,y,w;
}a[4005];
int sa(SA X,SA Y){
    return X.x<Y.x;
}
int main(){
    cin>>N>>M>>K>>T;
    for(int i=1;i<=K;i++){
     cin>>a[i].x>>a[i].y>>a[i].w;
    }
    sort(a+1,a+K+1,sa);
    a[1].dp=a[1].w;
    for(int i=1;i<=K;i++)
       for(int j=0;j<i;j++)
         if(abs(a[j].y-a[i].y)<=T*abs(a[i].x-a[j].x))
     a[i].dp=max(a[i].dp,a[j].dp+a[i].w);
    for(int i=1;i<=K;i++)
    ans=max(a[i].dp,ans);
    cout<<ans;
    return 0;
}
```  
会被
```
8 8 2 3 
1 1 2 
2 8 8
```
hack 掉。  
为什么？  
我们来看初始化：  
```cpp
a[1].dp=a[1].w;
```
初始化为只有第一个点可到，实际上每个点都可以走到的。  
所以初始化应该是：  
```cpp
for(int i=1;i<=k;i++)
	a[i].dp=a[i].w
```
毕竟你可以一路向下走。  
这个故事告诉我们，出题人的数据太弱  
但是心存梦想还是可以A题的  
关于hack的事讲完了，现在来看题：  
40pts:  
用每个点更新后面一片点  
直接n^3dp  
核心代码：  
```cpp
for(int i=1;i<=n;i++)
{
	for(int j=1;j<=m;j++)
    {
    	//枚举每个可到点
        for(int k=-t;k<=t;k++)
        {
        	int u=j+k;
            if(u<1) continue;
            if(u>m) break;
            f[i][u]=max(f[i][u],f[i][j]+a[i][j]);
            //f[i][j]是到第i,j个点可获最大值
            //a[i][j]是i,j点的权值
        }
    }
}
```
这题40分还是很好拿到的  
100pts:  
单调队列肯定没问题。  
每次维护一下，时间复杂度n^2  
以下代码出自y2823774827y julao  
```cpp
#include<cstdio>
using namespace std;
int n,m,k,t,ans; int a[4001][4001],dp[4001][4001],que[4001][2];
inline int MIN(int g1,int g2){
    return g1<=g2?g1:g2;
}
inline int MAX(int g1,int g2){
    return g1>=g2?g1:g2;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&k,&t);
    for(int i=1;i<=k;++i){
        int x,y;
        scanf("%d%d",&x,&y);
        scanf("%d",&a[x][y]);
    }
    for(int i=1;i<=n;++i){
        int head=1,tail=0;
        for(int j=1;j<=MIN(m,t);++j){
            while(que[tail][0]<=dp[i-1][j]&&head<=tail)
                --tail;
            que[++tail][0]=dp[i-1][j];
            que[tail][1]=j;
        }
        for(int j=1;j<=m;++j){
            if(j+t<=m){
                while(que[tail][0]<=dp[i-1][j+t]&&head<=tail)
                    --tail;
                que[++tail][0]=dp[i-1][j+t];
                que[tail][1]=j+t;
            }
            if(que[head][1]<j-t)
                ++head;
            dp[i][j]=que[head][0]+a[i][j];
        }
    }
    for(int i=1;i<=m;++i)
        ans=MAX(ans,dp[n][i]);
    printf("%d",ans);
    return 0;
}
```
当然，我们发现也可以用线段树维护  
时间复杂度（n^2logn）  
只不过代码量太大，时间复杂度也挺危险  

最后，我的方法：  
有一道题叫做“打鼹鼠”，你们可以去看看  
那道题就很好  
我们发现有权值的点十分少  
将思路放到点上。  
先排个序  
如果两点之间可以到达，那就更新  
打鼹鼠那道题你会做的话，这道题也没问题  
状态转移：  
```cpp
rep(i,1,k)
	{
		f[i]=a[i].v;
		rep(j,1,i-1)
		{
			if(check(a[i],a[j]))
				f[i]=max(f[i],f[j]+a[i].v);
		}
	}
```
判断函数：  
```cpp
bool check(pos x,pos y)
{
	if(abs(x.y-y.y)<=t*abs(x.x-y.x)) return 1;
	return 0;
}
```
std:  
```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <cctype>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define frep(i,x,y) for(int i=x;i>=y;i--)
const int N=4005;
struct pos
{
	int x;
	int y;
	int v;
};
int n,m,k,t;
pos a[N];
int f[N];
int ans=0;
bool cmp(pos x,pos y)
{
	return x.x<y.x;
}
int read(void)
{
	int sum=0;
	scanf("%d",&sum);
	return sum;
}
void print(int x)
{
	if(x<10) printf("%d",x);
	else 
	{
		print(x/10);
		printf("%d",x%10);
	}
}
bool check(pos x,pos y)
{
	if(abs(x.y-y.y)<=t*abs(x.x-y.x)) return 1;
	return 0;
}
int main()
{
	n=read();
	m=read();
	k=read();
	t=read();
	rep(i,1,k)
	{
		a[i].x=read();
		a[i].y=read();
		a[i].v=read();
	}
	sort(a+1,a+k+1,cmp);
	rep(i,1,k)
	{
		f[i]=a[i].v;
		rep(j,1,i-1)
		{
			if(check(a[i],a[j]))
				f[i]=max(f[i],f[j]+a[i].v);
		}
	}
	rep(i,1,k) ans=max(ans,f[i]);
	print(ans);
	printf("\n");
	return 0;
}
```

---

## 作者：囧仙 (赞：10)

东方Project相关试题（Easy-Normal） [3 / 30]

- 题目大意

  给出一个 $n \times m$ 的棋盘，有一些格子上面有权值。一开始站在第一行，每次下移一行，可以向两边走 $t$ 步以内，求权值和最大的路径

- 解法

  这题和 dp 经典入门题，P1216 十分相似，只是每次行走的方案多了很多
  
  所以很容易就可以想到，设 $dp_{i,j}$ 表示走到第 $i$ 行，第 $j$ 列的最大权值和，每次的转移是：
  
  $$dp_{i,j} = max(dp_{i - 1,k}) + c_{i,j}(j - t \le k \le j + t)$$
  
  如果你暴力去枚举的话，是 $O(nmt)$ 的，显然不能通过
  
  但是我们枚举的区间实际上是很有规律的，它的长度相同，并且每次只会在左边少一个数，右边多一个数
  
  显然，这个是单调队列的经典例题，滑动窗口
  
  所以每次用单调队列去维护最大值就可以了，时间复杂度 $O(nm)$
  
代码：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,k,t;
int c[4005][4005];
int dp[4005][4005];

int h = 1,r = 1;
struct node{
	int id,val;
}que[4005];

void pop(int id){
	while(h != r){
		if(que[h].id < id){
			h++;
		}else{
			return;
		}
	}
}

void push(int id,int val){
	while(h != r){
		if(que[r - 1].val <= val){
			r--;
		}else{
			break;
		}
	}
	que[r++] = {id,val};
}

int main(){
	scanf("%d%d%d%d",&n,&m,&k,&t);
	for(int i = 1;i <= k;i++){
		int x,y,val;
		scanf("%d%d%d",&x,&y,&val);
		c[x][y] += val;
	}
	for(int i = 1;i <= n;i++){
		h = r = 1;
		for(int j = 1;j <= t;j++){
			push(j,dp[i - 1][j]);
		}
		for(int j = 1;j <= m;j++){
			pop(j - t);
			if(j + t <= m) push(j + t,dp[i - 1][j + t]);
			dp[i][j] = que[h].val + c[i][j];
		}
	}
	int ans = 0;
	for(int j = 1;j <= m;j++){
		ans = max(ans,dp[n][j]);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：szr666 (赞：7)

我这里推荐一下[我的博客](https://www.luogu.org/blog/szr666--blog/)

在博客里观看更美观哦~

[题目](https://www.luogu.org/problemnew/show/P3800)
------------

------------

华丽的分割线
# 解析

### 转移方程式

设dp[i][j]表示到val数组第i行第j列的最大值

转移方程式为dp[i][j]=max{dp[i-1][k]} (j-t<=k<=j+t)

表示第i行第j列有由第(i-1)行第(j-t)个位置到第(j+t)个位置转移

这与最长上升子序列很像,只不过多了一维,复杂度O(nmt)

但只能过40%的数据,状态复杂度为O(nm)，转移复杂度为O(t)

### 单调队列优化

状态复杂度无法改变,我们可以把转移复杂度降为O(1)

对于一些dp中最值的问题,可以用单调队列优化,主要有3个操作


1.查询一段区间最值

2.区间可从左向右(或从右向左)滑动

3.当前最优值在队首

我们在转移时要求dp[i-1][k],(i-1固定)这个序列上的最大值

范围为j-t~j+t,j从t+1到m-t,也就是区间从左向右滑动,

开始将1~t下标加入队列,若队尾大于队尾前一个数则替代那个数

这保证队列从队首到队尾单调递减,最大值在队首

之后j 1->n 每次加j+t直到j+t==m

当队首范围在j-t~j+t范围外时弹出队首

注意队列里是下标,值用dp数组进行比较

每次取出队+1首,转移复杂度O(1)

我为了节省空间用了循环队列,

就是当tail>=m+1时 tail=1，指向之前删除的元素
# 代码

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
const int N=4200;
void read(int &x)
{
    x=0;
    int f;
    f=1;
    char c;
    c=getchar();
    while((c<'0'||c>'9')&&c!='-')
    {
        c=getchar();
    }
    if(c=='-')
    {
        f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }
    x=x*f;
}
int dp[N][N];
int q[N],head,tail,m;
void push(int x,int *now)
{
    tail++;
    if(tail>=m+1)
    {
        tail=1;
    }
    q[tail]=x;
    while(abs(head+1-tail)>=1&&now[q[tail]]>now[q[(tail-1)>=1 ? tail-1 : m]])
    {
        q[tail-1>=1 ? tail-1 : m]=q[tail];
        tail--;
        if(tail<1)
        {
            tail=m;
        }
    }
}
inline int max(int x1,int x2)
{
    return x1>x2 ? x1 : x2;
}
inline int min(int x1,int x2)
{
    return x1<x2 ? x1 : x2;
}
int main()
{
    int n,k,t,i,x,y,j;
    read(n);
    read(m);
    read(k);
    read(t);
    for(i=1;i<=k;i++)
    {
        read(x);
        read(y);
        read(dp[x][y]);
    }
    for(i=1;i<=n;i++)
    {
        head=0;
        tail=0;
        for(j=1;j<=t;j++)
        {
            push(j,dp[i-1]);
        }
        for(j=1;j<=m;j++)
        {
            if(j+t<=m)
            {
                push(j+t,dp[i-1]);
            }
            while(q[head+1]<max(j-t,1))
            {
                head++;
                if(head+1>=m+1)
                {
                    head=0;
                }
            }
            dp[i][j]+=dp[i-1][q[head+1]];
        }
    }
    int ans;
    ans=-0x3f3f3f3f;
    for(j=1;j<=m;j++)
    {
        ans=max(ans,dp[n][j]);
    }
    printf("%d",ans);
}
```


---

## 作者：comando (赞：4)

[题面](https://www.luogu.com.cn/problem/P3800)  

## 题意分析
题目要求在 $n\times m$ 的矩阵中选取 $n$ 个点，这些点应满足：  
* 每一行有且仅有一个点
* 对于任意相邻两行的点 $(x,y_1)$ 和 $(x,y_2)$ ， $\vert y_1-y_2\vert \le t$
* 点的权值和最大

## 思路&解法
### Solution 1 : 朴素 dp  
对于任意点 $(x,y)$ ，  
* 若 $x=1$ , $f_{x,y}=a_{x,y}$
* 若 $x>1$ , $f_{x,y}=\max\{f_{x-1,y}\}+a_{x,y}$

其中 $a_{x,y}$ 表示点 $(x,y)$ 的权值， $f_{x,y}$ 如果第 $x$ 行选取点 $(x,y)$ ，前 $x$ 行的最大点权和。  
算法时间复杂度为 $O(n m^2)$ 显然超时。  
### Solution 2 : 单调队列优化
有兴趣可以看一下其它巨佬的题解。  
### Solution 3 : 最优解
我们回头看一下数据范围，发现 $k\le 4000$ ，也就是说矩阵中大部分点的权值都是 0 ，实际上这些权为 0 的点一定不会产生最优解，所以我们可以只考虑输入的有权点。  
~~面向数据编程实锤~~
  
dp 过程如下：  
对于任意有权点 $(x,y)$ ，
* 若不存在点 $(x_i,y_i)$ 使得 $x_i<x$ 且 $\vert y-y_i\vert\le(x-x_i)\times t$ ，则 $f_{x,y}=a_{x,y}$
* 反之，则 $f_{x,y}=\max\{f_{x_i+y_i}\}+a_{x,y}$

dp部分可以朴素实现如下：
```cpp
for(int i=1;i<=k;i++)
{
	f[i]=a[i].v;
	for(int j=1;j<i;j++)
		if(abs(a[j].y-a[i].y)<=t*(a[i].x-a[j].x))
			f[i]=max(f[i],f[j]+a[i].v);
	ans=max(ans,f[i]);
}
```

其中数组 a 保存了点坐标 x 、y 和点权 v ,已按行号排序。算法时间复杂度为跑不满的 $O(k^2)$ ，你谷数据总时间在 90ms 左右。  
  
但是 90ms 怎么能满足我们最优解的目标呢？这不再来一发优化?  
上面的代码段中用穷举的方式来找到 $\max\{f_{x_i+y_i}\}+a_{x,y}$ ，我们考虑在这里进一步优化。找有条件的最大值，我首先想到的是开一个 set，按权值从大到小进行排序，这样我们从前向后找，一旦找到符合条件的点就可以直接跳出循环。时间复杂度 $O(k\times$玄学$\times\log k)$ ,你谷数据总时间 40ms 不到。 

2021/10 upd:最优解已被楼上题解超过

上完整代码：  
```cpp
#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;

int n,m,k,t;
struct node{
	int x,y,p;
	bool operator < (const node &x) const
	{
		if(this->p==x.p)
		{
			if(this->x==x.x)
				return this->y<x.y;
			return this->x<x.x;
		}
		return this->p>x.p;
	}
};
inline bool cmp(const node &x,const node &y)
{
	if(x.x==y.x)
		return x.y<y.y;
	return x.x<y.x;
}
node a[4010];
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&t);
	for(node *i=a;i<a+k;i++)
		scanf("%d%d%d",&(i->x),&(i->y),&(i->p));
	sort(a,a+k,cmp);
	int ans=a[0].p;
	set<node> f;
	f.insert(a[0]);
	for(int i=1;i<k;i++)
	{
		for(set<node>::iterator it=f.begin();it!=f.end();it++)
			if(abs(a[i].y-it->y)<=(a[i].x-it->x)*t)
			{
				a[i].p+=it->p;
				break;
			}
		f.insert(a[i]);
		if(a[i].p>ans)
			ans=a[i].p;
	}
	printf("%d\n",ans);
	return 0;
}

```
特别注意重载运算符时要防止出现权值一样的点被 set 认为是相等而仅插入一个点。~~（我不会告诉你我为这玩意调试了多久的）~~

---

## 作者：Seg_Tree (赞：4)

能翻到我这儿的同志们基本应该能发现这是道单调队列的题了。看了好久，发现怎么好像没有人用stl的双端队列呀，本蒟蒻来贡献一篇。

的确，根据某些巨佬的测试，stl的双端队列比手写的要慢一些。但是~~显然~~，用系统给出的双端队列思路会清晰很多，反正我从bfs开始一直用stl~~才不是我懒呢！~~

言归正传，有关这道题的核心思想，应该是**用dp[i][j]储存在第i行中灵梦在位置j时所能取得的最大p值。** 40分代码很好打，如果没有后面60分这题应该也就橙黄的水平。

然而，由于灵梦同志在下移时还有速度v(或者叫t)的限制，我们在考虑下移时会发现我们只用考虑一段固定的，最大为2*v的区间内的最大值。而且，在我们在一个个考虑一行中每一点时应该都能脑补出对于每一个点我们需要考虑到区间正在一点一点往左移。这就~~很容易~~让我们想到[滑动窗口](https://www.luogu.org/problem/P1886)这个问题。因此，要ac这道题，我们还需要一个单调队列优化。

有关单调队列呢，我还是讲讲吧。

(以下代码中，k代表上一行的纵坐标，ps表示即将要进行操作的横坐标)

```cpp

void insert(int k,int ps){
	while(!q.empty() && dp[k][ps]>dp[k][q.back()])
		q.pop_back();
	q.push_back(ps);
}
```
通过这些操作呢，我们可以发现单调队列的一些特征：

首先，~~它是单调的，~~而在这道题目中，我要让它保持单调递减，以保证它的队头一定是队列中最大的元素。

其次，每当一个新的元素企图进来，我都会让他进来，因为**它虽然有可能比我的队列中任何一个元素都要小，但它一定是我现在这个队列中适用范围能到最远的元素**。而且在它进来之后它还会检查一下我的队伍，**看看队列是否中是否有比它小的元素，然后把它们踢出队列。因为这个新来的元素相对于将被踢走的元素来说，它不但元素值比它们大，而且接下来能用的时间还比它们久，那么有啥理由要保留它们呢？**

还有，在本题中，我们的队列中储存的是上一轮中单调dp值的横坐标，因为这样表示方便。

接下来是单调队列的查询(顺便更新)操作。
```cpp
int find(int k,int ps){
	if(ps+v<=m)
		insert(k,ps+v);
	while(q.front()+v<ps)
		q.pop_front();
	return q.front();
}
```
当我们把dp更新的脚步向右更新一格时我们会发现，原来的那个单调队列区间可能有些过时了。它必须要**弹出一些对于当前位置ps来说已无法达到的点，并在右边加入一个ps+v点，以完整当前ps的可达区间单调队列。** 最后才是返回我们查询操作应有的返回值。

以下完整代码。
```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int>q;
int dp[4001][4001];
int n,m,v;
void insert(int k,int ps){
	while(!q.empty() && dp[k][ps]>dp[k][q.back()])
		//维护单调队列的单调性 
		//!q.empty必须在前面判断，否则在开始时会因为企图让一个空队列返回值而RE 
		q.pop_back();
	q.push_back(ps);
}
int find(int k,int ps){
	if(ps+v<=m)
		//加入插入接下来合法的点 
		insert(k,ps+v);
	while(q.front()+v<ps)
		//弹出从今以后都不合法的点 
		q.pop_front();
	return q.front();
}
int main(){
	int k;
	cin>>n>>m>>k>>v;
	for(int i=1; i<=k; i++){
		int x,y;
		cin>>x>>y;
		cin>>dp[x][y];
	}
	for(int i=2; i<=n; i++){
		for(int j=1; j<=v; j++)
			//先将在点1时合法的点都入列 
			insert(i-1,j);
		for(int j=1; j<=m; j++)
			//更新dp 
			dp[i][j]+=dp[i-1][find(i-1,j)];
		q.clear();
	}
	int ans=0;
	for(int i=1; i<=m; i++)
		ans=max(ans,dp[n][i]);
	cout<<ans;
	return 0;
}
```
stl的双端队列也就比手写的慢了一些，也不会影响通不通过的问题的呀，思路也很清晰，怎么就没人用呢QAQ。

---

## 作者：y2823774827y (赞：3)

楼下有两篇题解被这道数据hack了，答案是8
```
8 8 2 3 
1 1 2 
2 8 8
```
注意：从任意一个格子出发，所以不一定要走到p点

做法和楼下的单调队列一样，主要是说说思路~~感觉单调队列才是正解dalao别喷~~

由于到i的位置能从上一行i-t~i+t转换过来，所以进队列要两次，一次单独进1~t，第二次进j+t，这时才能得到dp[i][j]（走到第i行第j列得到的最大分数）

```cpp
#include<cstdio>
using namespace std;
int n,m,k,t,ans; int a[4001][4001],dp[4001][4001],que[4001][2];
inline int MIN(int g1,int g2){
	return g1<=g2?g1:g2;
}
inline int MAX(int g1,int g2){
	return g1>=g2?g1:g2;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&t);
	for(int i=1;i<=k;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		scanf("%d",&a[x][y]);
	}
	for(int i=1;i<=n;++i){
		int head=1,tail=0;
		for(int j=1;j<=MIN(m,t);++j){
			while(que[tail][0]<=dp[i-1][j]&&head<=tail)
			    --tail;
			que[++tail][0]=dp[i-1][j];
			que[tail][1]=j;
		}
		for(int j=1;j<=m;++j){
			if(j+t<=m){
				while(que[tail][0]<=dp[i-1][j+t]&&head<=tail)
				    --tail;
				que[++tail][0]=dp[i-1][j+t];
				que[tail][1]=j+t;
			}
			if(que[head][1]<j-t)
			    ++head;
			dp[i][j]=que[head][0]+a[i][j];
		}
	}
	for(int i=1;i<=m;++i)
	    ans=MAX(ans,dp[n][i]);
	printf("%d",ans);
	return 0;
}/*
3 3 4 1
1 1 3
1 2 1
2 2 3
3 3 3
*/
```

---

## 作者：s_a_b_e_r (赞：2)

看到这个题吗，开始就暴力枚举i,j,k把可以到的点全枚举一遍

时间复杂度O(n\*m\*T)......赤裸裸的超时....比赛时只有40

**感谢出题人给蒟蒻思路**

一下转自出题人的话。。。。

```cpp
其实和地图大小并没有什么关系
先将所有果子按x 从小到大排序
核心代码：
for (int i=1;i<=k;i++)
for (int j=1;j<i;j++)
if (abs(y[i]-y[j])<=T*abs(x[i]-x[j]) dp[i]=max(dp[i],dp[j]+val[i])
```
现在看起来就是枚举power点K,时间复杂度<O(log(K)+K\*K)

这样y单纯成了转移的限制条件，于是就写成了结构体：

a[i].dp表示到第i个点最大到达的点数，然后丢掉图就好了O(∩\_∩)O哈哈~

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int N,M,K,T,ans;
struct SA{
int dp,x,y,w;
}a[4005];
int sa(SA X,SA Y){
    return X.x<Y.x;
}
int main(){
    cin>>N>>M>>K>>T;
    for(int i=1;i<=K;i++){
     cin>>a[i].x>>a[i].y>>a[i].w;
    }
    sort(a+1,a+K+1,sa);
    a[1].dp=a[1].w;
    for(int i=1;i<=K;i++)
       for(int j=0;j<i;j++)
         if(abs(a[j].y-a[i].y)<=T*abs(a[i].x-a[j].x))
     a[i].dp=max(a[i].dp,a[j].dp+a[i].w);
    for(int i=1;i<=K;i++)
    ans=max(a[i].dp,ans);
    cout<<ans;
    return 0;
}
```

---

## 作者：Jerrycyx (赞：1)

一眼 DP，设 $f_{i,j}$ 表示走到坐标 $(i,j)$ 的最大 POWER 值，那么有：

$$f_{i,j} = a_{i,j} + \max_{p=j-t}^{j+t} f_{i-1,p}$$

即每次从上一行可行的位置向下转移（$a_{i,j}$ 表示该点上的原始 POWER 值）。

直接计算的时间复杂度 $O(nm^2)$，无法通过。

-----

观察上式所求 $\max_{p=j-t}^{j+t} f_{i-1,p}$ 部分，是一个裸的静态 RMQ 模板，自然可以想到用好写而常数小的 ST 表处理。

对于每一行，对其上一行建 ST 表。更新坐标 $(i,j)$ 时，在区间 $[j-t,j+t]$ 内查询最大值进行累加就能直接得到答案。（注意防越界）

时间复杂度 $O(n m \log m)$，可过。

-----

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=4005;
int n,m,k,t;
int st[N][15],f[N][N];

int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&t);
	for(int i=1;i<=k;i++)
	{
		int x,y,v;
		scanf("%d%d%d",&x,&y,&v);
		f[x][y]=v;
	}
	int tp=__lg(m),ans=0; //__lg()函数用于计算以2为底的对数
	for(int i=2;i<=n;i++) //从第二行开始计算，因为第一行可以从任意位置开始
	{
		for(int j=1;j<=m;j++)
			st[j][0]=f[i-1][j];
		for(int l=1;l<=tp;l++) //建立ST表
			for(int x=1;x+(1<<l)-1<=m;x++)
				st[x][l]=max(st[x][l-1],st[x+(1<<(l-1))][l-1]);
		for(int j=1;j<=m;j++)
		{
			auto query = [&](int l,int r) -> int //lambda函数写法，可以直接当正常函数用
			{
				int p=__lg(r-l+1);
				return max(st[l][p],st[r-(1<<p)+1][p]);
			};
			f[i][j]+=query(max(j-t,1),min(m,j+t)); //对范围取max/min防止查询越界
			ans=max(ans,f[i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/198890805)

---

## 作者：devout (赞：1)

这里提供一种**跑的特别慢**，但是**空间特别小**的方法

在这里先吐槽一下出题人，要么就把空间开小点卡掉大空间，要么就把时间开小点卡掉大时间，~~结果一个都不卡~~

先考虑暴力的$dp$做法，我们用$f_{i,j}$表示走到$(i,j)$可以获得的最大收益

那么显然有这样一个转移

$$f_{i,j}=\max\{f_{i-1,j^\prime}\}+val_{i,j}\quad(j^\prime\in[j-t,j+t])$$

但是这个时候的复杂度是$O(nmt)$的，显然会超时

我们可以通过单调队列优化让他变成$O(nm)$的

但是题解里面大多数是维护一个长度为$2t+1$的滑动窗口，但是这样显然只会增加代码难度，我们可以正着做一遍$t$的，再反过来做一遍就可以

上面的部分别的题解里面都讲过了，那么接下来是优化空间的部分

我们发现，我们的空间主要是因为$f_{i,j}$和$val_{i,j}$这两个数组，考虑能不能把他们变成一维

显然，$f_{i,j}$是可以滚动数组滚掉一维的，那么$val$怎么办呢？

这里其实是一个小$\text{trick}$，也是典型的用时间换空间的案例

我们讲每个点按照$x$为第一关键字，$y$为第二关键字进行排序

那如何判断一个点有没有权值呢？我们想到二分！我们可以直接lower_bound一下，然后如果找到的那个点和我们现在这个点完全重合，那么这个点就是有权值的

这是这一部分的代码：

```cpp
int low=lower_bound(a+1,a+k+1,(node){i,j})-a,ext=0;
i(a[low].x==i&&a[low].y==j)ext=a[low].v;
```


那么这样的话我们的时间虽然变成了$O(nm\log k)$，但是空间上我们全部变成了一维数组，最后跑出来的情况是这个样子的

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200510210134590.png)

虽然~~时间翻了五倍~~，但是空间变成了KB级别

即使我们的空间缩成64MB（可以卡掉大部分人的代码），时限变成1s，同样也可以通过（最大点900ms左右）

然后就是代码了qwq

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=4005;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m,k,t;
struct node{
    int x,y,v;
    bool operator < (const node &cmp){
        if(x!=cmp.x)return x<cmp.x;
        return y<cmp.y;
    }
}a[N];

int f[2][N],x;
int q[N],head,tail;
int ans;

int main()
{
    // freopen("p3800.in","r",stdin);
    read(n),read(m),read(k),read(t);
    Rep(i,1,k)read(a[i].x),read(a[i].y),read(a[i].v);
    sort(a+1,a+k+1);
    Rep(i,1,n){
        x^=1;//滚动数组优化
        memset(f[x],0,sizeof(f[x]));
        head=1,tail=0;
        Rep(j,1,m){
            while(head<=tail&&f[x^1][q[tail]]<f[x^1][j])tail--;//正反各进行一次单调队列
            while(head<=tail&&q[head]<j-t)head++;
            q[++tail]=j;
            int low=lower_bound(a+1,a+k+1,(node){i,j})-a,ext=0;
            if(a[low].x==i&&a[low].y==j)ext=a[low].v;
            f[x][j]=max(f[x][j],f[x^1][q[head]]+ext);
        }
        head=1,tail=0;
        _Rep(j,m,1){
            while(head<=tail&&f[x^1][q[tail]]<f[x^1][j])tail--;
            while(head<=tail&&q[head]>j+t)head++;
            q[++tail]=j;
            int low=lower_bound(a+1,a+k+1,(node){i,j})-a,ext=0;
            if(a[low].x==i&&a[low].y==j)ext=a[low].v;
            f[x][j]=max(f[x][j],f[x^1][q[head]]+ext);
        }
    }
    Rep(i,1,m)ans=max(ans,f[x][i]);
    printf("%d\n",ans);
    return 0;
}

```


---

## 作者：Dispwnl (赞：1)

一看这题：嚯好简单！！！

在以为终于能找出一道蒟蒻如我都会的dp的激动心情下打完了这道题

一交
mmp怎么超时。。。

果然绿题dp无水题啊（好像是我太菜了）。。。

于是借鉴了（大雾）题解后

终于知道不超时的办法了

先将每个power根据横坐标排序

然后依次枚举每一个点和它之前的每一个点

如果它俩的纵坐标的距离不大于t\*它俩的横坐标之差

就更新这个点的最大值

##因为它俩的横坐标之差可以看成是移动次数

##所以在-(t\*横坐标之差)~t\*横坐标之差的范围内都可以到达

然后输出（每个点的最大值中的最大值）

（好吧我承认我语文表达不好）

c++
```cpp
# include<iostream>
# include<cstdio>
# include<algorithm>
# include<cstring>
# include<cstdlib>
using namespace std;
struct p{
    int x,y,dis;
}c[4001];
int n,m,k,t,ans;
int f[4001];
bool cmp(p a,p b)//按横坐标排序
{
    return a.x<b.x;
}
inline int read()
{
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x*w;
}
int main()
{
    n=read(),m=read(),k=read(),t=read();
    for(int i=1;i<=k;i++)
      c[i].x=read(),c[i].y=read(),c[i].dis=read();
    sort(c+1,c+1+k,cmp);
    f[1]=c[1].dis;//初始值
    for(int i=1;i<=k;i++)
      {
          for(int j=0;j<i;j++)//注意是0~i-1，因为可能前面的点一个都不选
          if(abs(c[i].y-c[j].y)<=t*abs(c[i].x-c[j].x))
          f[i]=max(f[i],f[j]+c[i].dis);
        ans=max(ans,f[i]);
      }
    printf("%d",ans);
    return 0;
}
//欢迎dalao指错
```

---

## 作者：Priori_Incantatem (赞：0)

考虑 $f[i][j]$ 表示走到位置$(i,j)$时可以获得的最大权值  
我们发现 $f[i][j]$ 是由 $f[i][j-k] \sim f[i][j+k]$ 和 $f[i-1][j]$ 转移过来的
那么，我们可以用单调队列维护区间 $[j-k,j+k]$ 内 $f$ 的最大值

明白这个后就很简单了，维护单调递减队列并枚举更新就可以了

注意有一点很容易错：在同一行你只能瞬移一次，并且不能折返  
也就是说瞬移的上一步不能还是瞬移，所以要用一个辅助数组$s$，保证上一步一定不是瞬移  
详情请看代码

**关键代码：**
```cpp
for(int i=1;i<=n;++i)
{
    for(int j=1;j<=m;++j)
	{
		f[i][j]=f[i-1][j]+a[i][j];
		s[j]=0;
	}
	q.clear();
	for(int j=1;j<=k;++j)
	push(i,j);
	for(int j=1;j<=m;++j)
	{
		pop(j);
		if(j+k<=m)push(i,j+k);
		s[j]=f[i][q.front()];
	}
	for(int j=1;j<=m;++j)
	f[i][j]=max(f[i][j],s[j]);
}
```

**完整代码：**

```cpp
#include<cstdio>
#include<iostream>
#include<deque>
#include<algorithm>
using namespace std;
const int Maxn=4010,inf=0x3f3f3f3f;
int f[Maxn][Maxn],a[Maxn][Maxn];
int s[Maxn];
int n,m,k,ans;
deque <int> q;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void push(int i,int j)
{
	while(1)
	{
		if(q.empty())break;
		if(f[i][q.back()]>=f[i][j])break;
		q.pop_back();
	}
	q.push_back(j);
}
void pop(int x)
{
	while(1)
	{
		if(q.empty())break;
		if(abs(q.front()-x)<=k)break;
		q.pop_front();
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	int tmp;
	n=read(),m=read(),tmp=read(),k=read();
	for(int i=1;i<=tmp;++i)
	{
		int x=read(),y=read(),c=read();
		a[x][y]=c;
	}
	
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			f[i][j]=f[i-1][j]+a[i][j];
			s[j]=0;
		}
		q.clear();
		for(int j=1;j<=k;++j)
		push(i,j);
		for(int j=1;j<=m;++j)
		{
			pop(j);
			if(j+k<=m)push(i,j+k);
			s[j]=f[i][q.front()];
		}
		for(int j=1;j<=m;++j)
		f[i][j]=max(f[i][j],s[j]);
	}
	
	for(int i=1;i<=m;++i)
	ans=max(ans,f[n][i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：wawcac (赞：0)

[广告](http://www.cnblogs.com/wawcac-blog/p/6969430.html)

典型的DP，我想到的有以下两种思路

1、类似于[这道题](https://www.luogu.org/problem/show?pid=1216)，可以从下到上一行行地填 f 数组，对于一行中的每一个，容易想到暴力搜索下一行从哪里转移过来，复杂度$O(nmt)$，然后就TLE了。于是咋办呢？发现我们填$f[i][j]$时，搜了一遍$f[i+1][j-t]$到$f[i+1][j+t]$(不要在意边界溢出，特判一下就是了)，然后填$f[i][j+1]$时，除了搜$f[i+1][j+t+1]$之外，又搜了一遍$f[i+1][j-t+1]$到$f[i+1][j+t]$，重复好多啊，于是怎么办呢？就想到了[质量检测](https://www.luogu.org/problem/show?pid=2251)这题，给一个序列，求所有一定长度的区间中的最值，嗯m，RMQ，可以用st表，也可以用单调队列，这里套在每一行上，总复杂度就分别是$O(nmlog_2m)$(套st表)$O(nm)$(套单调队列)，于是，st表有点虚啊，常数很大的同学可能就卡不过去了，而且st表空间$O(mlog_m)$，单调队列空间$O(t)$，还有……单调队列比st表好写太多了，果断单调队列，最慢一个点862ms。出题人把时限开到2s，放了这个大众的思路


2、和打鼹鼠这题很像，可以看看我[这篇博文](http://www.cnblogs.com/wawcac-blog/p/6965053.html)。存下所有power的信息，然后按照行号、列号排个序，然后就类似最长不下降序列的DP做法了，每拓展一个位置，就向前扫描已经拓展的所有的位置，看看能从哪里来到这里，如果速度、时间都满足，就刷新最大值吧。这个的时间复杂度$O(k^2)$，和上面那个单调队列是同阶的，但是这个思路实际用时是上面的二分之一，占用空间是上面的快十分之一，代码量是上面的二分之一，果然$\mbox{think twice, code once.}$啊

[源代码](http://www.cnblogs.com/wawcac-blog/p/6969430.html)


---

## 作者：pluszero (赞：0)

这道题是一道很经典的DP题，看题我们很容易就能想到DP方程：f[i][j]表示当走到第i行第j列时，获得的POWER的最大值，则f[i][j]=max(f[i-1][k])+a[i][j] (a[i][j]代表当前格的POWER值，j-t<=k<=j+t) ，时间复杂度是O(n\*m\*t)，再看数据范围（1<=n,m,t<=4000），说明这个方法会超时（实际上可以拿40分）。所以要优化，发现每一次都要求max(f[i-1][k])，而k所在的区间每一次只移动一位，所以可以用单调队列来优化这一过程，方法类似于洛谷P1886滑动窗口（不懂的可以去看这道题），这样就成功的把时间复杂度降到了O(n\*m)，AC。


下面是代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int a[4001][4001],f[4001][4001];

struct node
{
    int v,id;
}q[4001];

int main()
{
    int n,m,k,t;
    scanf("%d%d%d%d",&n,&m,&k,&t);
    for(int i=1;i<=k;i++)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        a[x][y]=v;
    }
    for(int i=1;i<=n;i++)
    {
        int num=0,h=1;
        for(int j=1;j<=min(m,t);j++)
        {
            while(f[i-1][j]>=q[num].v && num>=h) num--;
            q[++num].v=f[i-1][j];
            q[num].id=j;
        }
        for(int j=1;j<=m;j++)
        {
            if(j+t<=m)
            {
                while(f[i-1][j+t]>=q[num].v && num>=h) num--;
                q[++num].v=f[i-1][j+t];
                q[num].id=j+t;
            }
            if(q[h].id<j-t) h++;
            f[i][j]=q[h].v+a[i][j];
        }
    }
    int maxx=0;
    for(int i=1;i<=m;i++) 
        maxx=max(maxx,f[n][i]);
    printf("%d",maxx);
    return 0;
}
```

---

## 作者：嚯呀嚯呀 (赞：0)

一道很好的用单调队列优化DP的题目

首先你要先推出DP的公式，这道题和那种数塔很像(刚学DP都要做的题目)

f[i,j]表示走到(i,j)这个位置得到的最大power

那么显而易见对于这个状态f[i,j]可以由**上一行的 j-t到j+t 的状态中推过来**。
t是灵梦能左右移动的速度

**那么状态转移方程就是f[i,j]=max(f[i-1,k]); k∈[j-t,j+t]**，注意一下有没有超边界的话就可以用DP做出来了

最大的答案应该在f[n,j]，j∈[1,m]中找一个最大值

但是这样时间是会超的，如果我没有算错的话，计算机最差情况要计算64000000000次，超过一亿次的话不能在1秒钟出答案的

**优化**

我们可以从方程中发现，对于f[i,j]，我们每次都是在f[i-1,k]，k∈[j-t,j+t]里找一个最大值，对于下一个j，我们要找最大值的范围基本上也就是向有平移一格，这样的话有很多冗余的查找，如果可以更快的找出最大值就可以过这题了

这里就可以应用到我们的单调队列了，维护一个单调递减的队列，那么每次找最大值我就只需要把队列的头元素拿出来就行了，时间复杂度O(1);

**那么怎么维护呢，我的代码中dp[i],表示上一行的各列的最大power(怕超空间)
s[i]是我要推出来的这一行各列的最大power，其实就是滚动数组**

那么推s[i]就要在dp[i]中找在范围内的最大值
定义一个单调队列f，**如果新加进去的dp[i]连上去能保证单调递减，那就接上去，如果不能，那就不停从队列尾部弹出元素，直到dp[i]接在上面能保证单调**

拿出最大值的时候还需要判断一下，如果这个最大值不在我们的范围内，是一个过时的最大值，那我们就head=head+1;直到找到一个最大值在范围内。处理这个的话只需要加一个num数组记一下这个值是在哪里找到的就可以解决了

说这么多好累啊，看代码吧(**P党福利！！**)
```
var
  ans:int64;
  point,head,tail,a1,a2,a3:longint;
  len,i,j,m,n,k,p:longint;
  map:array[0..4005,0..4005]of longint;
  dp,f,s,num:array[0..4005]of int64;
function min(x,y:longint):longint;
begin
  if x<y then exit(x)
  else exit(y);
end;
begin
  readln(n,m,k,len);
  for i:=1 to k do
    begin
      readln(a1,a2,a3);
      map[a1,a2]:=a3;
    end;
  for i:=1 to m do
    dp[i]:=map[1,i];
  for i:=2 to n do
    begin
      a1:=min(m,1+len);
      head:=1; tail:=1; f[1]:=dp[1]; num[1]:=1;
      for j:=2 to a1 do
        begin
          if f[tail]>dp[j] then
            begin
              inc(tail); f[tail]:=dp[j]; num[tail]:=j;
            end
          else
            begin
              while (f[tail]<dp[j])and(tail>=head) do dec(tail);
              inc(tail); f[tail]:=dp[j]; num[tail]:=j;
            end;
        end;
      s[1]:=f[head]+map[i,1]; point:=1+len;
      for j:=2 to m do
        begin
          if point+1<=m then
            begin
              inc(point); a2:=dp[point];
              if f[tail]>a2 then
                begin
                  inc(tail); f[tail]:=a2; num[tail]:=point;
                end
              else
                begin
                  while (f[tail]<a2)and(tail>=head) do dec(tail);
                  inc(tail); f[tail]:=a2; num[tail]:=point;
                end;
            end;
          while num[head]<j-len do inc(head);
          s[j]:=f[head]+map[i,j];
        end;
      for j:=1 to m do
        dp[j]:=s[j];
    end;
  for j:=1 to m do
    if ans<dp[j] then
      ans:=dp[j];
  writeln(ans);
end.
```

---

## 作者：zhaoyifan (赞：0)

一道很不错的优先队列题

f[i][j]的最大值由上一行的状态有关，转移方程f[i][j]=max(f[i-1][z])+a[i][j]，z∈（j-k,j+k）

每个转移会超时，所以我们对上一行建立单调队列，由1推到m，提前入队，超出范围出队。

```cpp
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,k,t,f[4001][4001],a[4001][4001];
int main()
{
    cin>>n>>m>>k>>t;
    memset(a,0,sizeof(a));
    for(int i=1;i<=k;++i)
    {
        int x,y,z;
        cin>>x>>y>>z;
        a[x][y]=z;
    }
    for(int i=1;i<=n;++i)
     for(int j=1;j<=m;++j)
     f[i][j]=-99999;
    for(int i=1;i<=m;++i)
    f[0][i]=0;
    for(int i=1;i<=n;++i)
     {
         int q[4001],head=1,tail=0;
         for(int j=1;j<=t;++j)
         {
             while(f[i-1][q[tail]]<=f[i-1][j]&&head<=tail) tail--;
            q[++tail]=j;
         }
         for(int j=1;j<=m;++j)
          {
              if(q[head]<j-t&&head<=tail) head++;
            if(j+t<=m)
            {
                while(f[i-1][q[tail]]<=f[i-1][j+t]&&head<=tail) tail--;
                q[++tail]=j+t;
            }
            f[i][j]=f[i-1][q[head]]+a[i][j]; 
          }
     }
    int maxx=0;
    for(int i=1;i<=m;++i)
    if(f[n][i]>maxx) maxx=f[n][i];
    cout<<maxx;
    return 0;
}
```

---

