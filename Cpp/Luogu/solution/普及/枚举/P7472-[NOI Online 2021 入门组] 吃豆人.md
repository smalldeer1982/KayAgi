# [NOI Online 2021 入门组] 吃豆人

## 题目描述

有一个 $n$ 行 $n$ 列的正方形点阵，左上角点坐标为 $(1, 1)$，右下角点坐标为 $(n, n)$。

点阵中每个整点上都有数量不一的豆子，坐标为 $(i, j)$ 的点上有 $a_{i,j}$ 个豆子。

你可以放置吃豆人，可以将点阵中任意的整点作为吃豆人的初始位置，再给定左上、左下、右上、右下之一作为吃豆人的初始方向。

吃豆人会不断沿初始方向行进，吃光遇到的所有豆子，直到碰到点阵的边界，此时：

1. 如果吃豆人处于正方形点阵四个角之一的位置，那么就会停止行动；

2. 否则，吃豆人的行进路线将以这条边界为镜面发生反射，下图展示了一个路径某两次发生反射的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/6tji95nq.png)

现在，你需要放置两个吃豆人，求两个吃豆人最多共能吃到多少个豆子？注意同一个豆子只能被吃一次。


## 说明/提示

### 样例 1 解释

在 $(1, 1)$ 和 $(1, 3)$ 位置放置吃豆人，初始方向分别为右下和左下，即可吃到位于
$(1, 1)$，$(1, 3)$，$(2, 2)$，$(2, 4)$，$(3, 1)$，$(3, 3)$，$(4, 2)$，$(4, 4)$ 位置上的豆子，总个数为 $132$，
达到最大，路径分别如下图绿线和红线所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/1axaad1b.png)

### 数据范围

对于 $30\%$ 的数据，$n\leq 3$。

对于 $60\%$ 的数据：$n\leq 100$。

对于 $100\%$ 的数据：$2\leq n\leq 1000$，$0\leq a_{i,j}\leq 1000$。

数据由 [SSerxhs](https://www.luogu.com.cn/user/29826) 和 [Karry5307](https://www.luogu.com.cn/user/60990) 共同提供。

感谢 [Silence_water](https://www.luogu.com.cn/user/338630) 提供一组 hack 数据。

## 样例 #1

### 输入

```
4
20 1 19 2
3 18 4 17
16 5 15 6
7 14 8 13```

### 输出

```
132```

# 题解

## 作者：Mine_King (赞：40)

这题其实挺好想的，只需要画两个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/p8ub23sx.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/x6o1bt1q.png)

这两张分别是 $n=4$ 和 $n=5$ 时(因为可以猜想路径和某些东西的奇偶性有关，所以挑两张 $n$ 的奇偶性不同的图)的网格和吃豆人行走的路径图（彩色的是路径，黑线的焦点是有豆子的点）

观察这两张图可以得到如下性质：

- 共有 $n$ 条路径。
- 每条路径都是一个回路或对角线。
- 在网格图的四条边的任意一条边上都会同时出现这 $n$ 条路径，**我们以最上面的一条边为标准，以路径在这条边上出现时的纵坐标来标记这条路径，如红线的编号为 $1$**
- 若编号为 $x,y$ 的两条路径满足 $y-x$ 是偶数，则这两条路径存在共同经过的点，否则不存在共同经过点。
- 若 $u,v$ 两条路径有共同经过的点，则：
  - 如果 $u,v$ 是两条对角线，则有一个共同经过的点，且该点为网格的中心。
  - 如果是一条对角线和一条回路，那么有两个焦点。
  - 如果是两条回路，那么有四个焦点。
- 若 $u,v$ 两条路径有共同经过的点且不是两条对角线，则共同经过的点关于第一条对角线对称，即每对共同经过的点的横纵坐标相反。
  
由于 $n$ 比较小，我们可以 $O(n^2)$ 预处理出每条路径能吃的豆子数，$O(n^2)$ 来枚举吃豆人走的路径。  
现在唯一的问题就是要求出我们选的两条路径的共同经过的点上的豆子数之和。

这里我们需要进行分类讨论。  
设我们现在选的路径编号为 $u,v$，且 $v>u$，共同经过的点上的豆子数之和为 $ans$，坐标 $(i,j)$ 上的豆子数为 $a_{i,j}$，则：

- 若 $v-u$ 是奇数，则 $ans=0$，否则
  - 若 $u=1$ 且 $v=n$（即两条对角线），则 $ans=a_{(n+1)/2,(n+1)/2}$。
  - 若 $u=1$ 且 $v \not= n$（即回路和第一条对角线），则 $ans=a_{(v+1)/2,(v+1)/2}+a_{(2n-y+1)/2,(2n-y+1)/2}$。
  - 若 $u \not= 1$ 且 $v=n$（即回路和第二条对角线），则 $ans=a_{(n-x)/2+1,(n+x)/2}+a_{(n+x)/2,(n-x)/2+1}$。
  - 若 $u \not= 1$ 且 $v \not= n$（即两条回路），则 $ans=a_{(x+y)/2,(y-x)/2+1}+a_{(y-x)/2+1,(x+y)/2}+a_{n-(y-x)/2,n-(x+y)/2+1}+a_{n-(x+y)/2+1,n-(y-x)/2}$。
  
这几点也可以通过找规律和推式子得到。  

于是就可以快快乐乐地写出代码啦~

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[1005][1005];
int ans,b[1005];//b[i]是第i条对角线的豆子数量
const int gx[4]={1,1,-1,-1};
const int gy[4]={-1,1,1,-1};
int repeat(int x,int y)//这里判共同经过的点的豆子数量
{
	if((y-x)%2) return 0;//无共同经过的点
	if(x==1&&y==n) return a[(n+1)/2][(n+1)/2];//两条对角线
	if(x==1) return a[(y+1)/2][(y+1)/2]+a[(2*n-y+1)/2][(2*n-y+1)/2];//第一条对角线和回路
	if(y==n) return a[(n-x)/2+1][(n+x)/2]+a[(n+x)/2][(n-x)/2+1];//第二条对角线和回路
	return a[(x+y)/2][(y-x)/2+1]+a[(y-x)/2+1][(x+y)/2]+a[n-(y-x)/2][n-(x+y)/2+1]+a[n-(x+y)/2+1][n-(y-x)/2];//两条回路
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	if(n==1){printf("%d\n",a[1][1]);return 0;}//特判n=1的情况，否则下面的计算路径中的豆子数量会挂掉
	for(int i=1;i<=n;i++)
	{
		int x=1,y=i,d=0;
		do
		{
			b[i]+=a[x][y];
			if(d==0&&y==1) d++;
			else if(d==1&&x==n) d++;
			else if(d==2&&y==n) d++;
			else if(d==3&&x==1) d++;
			d%=4;
            //这里是发生镜面反射时的方向改变
			x=x+gx[d],y=y+gy[d];
		}
		while(x!=1&&(x!=n||y!=n)&&(x!=n||y!=1));//这里是计算路径上的豆子数量
		if(i==1) b[i]+=a[n][n];
		if(i==n) b[i]+=a[n][1];
        //这两条特判对角线
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans=max(ans,b[i]+b[j]-repeat(i,j));//枚举选的路径
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Hanx16Kira (赞：26)

## P7472 [NOI Online 2021 入门组] 吃豆人（民间数据）

### 题目

传送门：https://www.luogu.com.cn/problem/P7472

### 题意分析

给定一个 $n \times n$ 的矩阵，需要在这个矩阵中找到两个斜向的矩阵使得它们边上的权值和最大。

### 分析

其实我一开始看到这道题就想到了做法，可惜当时手慢了点，没交上去，所以……

首先分析题目，需要找到两个矩阵边上的数字和最大，所以我们可以用很多办法。

#### [Way1] 暴力判断（期望得分：30pts）

$ n \le 3 $ 的数据规模并不大，所以我们可以挨个枚举 $n = 1$ ， $n = 2$ ， $n=3$ 的时候的所有情况，仅需要在草稿纸上将每一个情况画出来进行小的比较而已。

此种做法很简单，基本人人都会，所以在想不出什么思路的时候，可以优先将这种思路的代码写出来，拿到30pts。

#### [Way2] 暴力模拟（期望得分：60pts）

可能只需要稍微一想，我们就可以知道一种比较简单的方法，依次枚举吃豆人的位置 $(i,j)$ ，然后按题目模拟行走的过程，过程中可以使用一个 $flag_{i,j}$ 数组进行标记走过的路，以达到去重的目的。

当然，依次枚举每一个点的话每一个吃豆人都有 $n^2$ 个出发点，所以时间复杂度大约是 $O(n^4)$ ，所以我们还可以对此办法进行一个小优化。

观察一下就可以发现，对于在同一斜线上的点，吃豆人所走的路线都是相同的，所以我们可以在此基础上进行优化，对于每一个吃豆人我们都有 $n$ 种路线来走，然后模拟走过的路线，时间复杂度大约是 $O(n^3)$。但是也不能达到100pts的标准。

#### [Way3] 提前计算最后枚举每一种情况（期望得分：100pts）

在刚刚的[Way2]中已经提到，对于一条斜线上的出发点，吃豆人走过的路线是相同的，所以说我们可以在输入的时候就进行计算，将每一种路线可以得到的豆子总数记录下来，最后再枚举进行比较。计算需要枚举每一种可能的路径，时间复杂度为 $O(n)$ ，枚举两个吃豆人的出发点，对于每个吃豆人，都有 $n$ 种出发的位置，所以时间复杂度为 $O(n^2)$ ，足以胜任题目所要求的 $n \le 1000$ 的数据量。

为了计算矩阵的总和，我采用了一种方法，就是在输入时就将每一个斜线上的值的和计算出来，在计算矩阵边上权值和的时候就可以将构成边的四条斜线的和加起来减去重叠的 $4$ 个顶点的值。

问题来了，我们计算出了每一个矩阵的总和，但是两个矩阵难免会有交点，所以我们还需要计算交点，减去交点的值，才能得到我们想要的值。

但是怎么样求到这最多四个的交点呢？

我采用了平面直角坐标系的思想。

假设有一个平面直角坐标系，将这个矩阵放置在其中，我们将这个矩阵的第一行定义为 $x=1$ ，第一列定义为 $y=1$ ，所以我们就可以将矩阵中每个点的坐标都表示出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/1axaad1b.png)

首先看第一个点， 也就是图中 $(2,2)$ 的那个交点，我们应该怎么求到它呢？

我们已知两个矩阵在第一行的顶点坐标分别为 $(1,1)$ 和 $(1,3)$ ，所以我们可以推导出，这个交点的 $x$ 坐标与这两个顶点的中点坐标相同。根据中点坐标公式 $(\frac{x_1+x_2}{2},\frac{y_1+y_2}{2})$ 我们就可以知道交点的 $x$ 坐标为 $\frac{x_1+x_2}{2}=\frac{1+3}{2}=2$ ，然后再来推 $y$ 坐标，不难发现， $y$ 坐标的值就等于 $1$ 加上顶点的中点与其中一个顶点的距离，也就是 $1+(2-1)=2$ ，就这样得到了第一个交点的坐标为 $(\frac{x_1+x_2}{2},\frac{x_2-x_1}{2}+1)$ ，同理，即可求出其它交点坐标的值。

当然，也可以利用交点之间的对称性来求得其余的交点坐标。当我们求出交点坐标时，基本这道题也没什么难度了。还需要注意一点就是，当 $x_2-x_1$ 为奇数的时候，这是两个矩形没有交点，我们就不需要减去重叠部分。对于 $x_2-x_1$ 为偶数的时候，也得进行分类，分别判断当哪些交点重合时，应该减去多少重叠的部分，以免减去过多的重叠，导致计算值变小。


### Code[Way3]

~~~c++
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int n,a[1005][1005],sum1[1005][1005],sum2[1005][1005],sum3[1005];
//n为这个矩阵的边长，a表示每个点上的权值，sum1为自左上向右下斜线的权值和，sum2为自右上向左下斜线的权值和，sum3表示计算出的每个矩阵边上的权值和
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
            sum1[i][j]=sum1[i-1][j-1]+a[i][j];//计算斜线的权值和，计算方法类似前缀和
            sum2[i][j]=sum2[i-1][j+1]+a[i][j];
        }
    }
    //输入
    for (int i=1;i<=n;i++)
    {
        if (i==1 || i==n)//判断为对角线的情况
        {
            if (i==1)
                sum3[i]=sum1[n][n];
            else
                sum3[i]=sum2[n][1];
        }
        else
            sum3[i]=sum1[n][n-i+1]+sum1[n-i+1][n]+sum2[i][1]+sum2[n][n-i+1]-a[1][i]-a[i][1]-a[n-i+1][n]-a[n][n-i+1];//找到矩阵四条边的权值和加起来减去重叠部分计算矩阵边上的权值和
    }
    //计算矩阵
    int ans=-1;//准备寻找答案，因为答案一定为正整数所以将ans初值赋为-1
    for (int i=1;i<=n;i++)//枚举第一个吃豆人的起点
    {
        for (int j=i+1;j<=n;j++)//枚举第二个吃豆人的起点，避免重复所以从i+1开始枚举
        {
            int t;//暂时存放计算结果
            if ((j-i)%2==0)//当顶点横坐标差为偶数的时候
            {
                int x1=1+(j-i)/2,y1=(i+j)/2;//第一个交点
                int x2=y1,y2=x1;//第二个交点（利用对称性）
                int x3=n-y1+1,y3=n-x1+1;//第三个交点
                int x4=y3,y4=x3;//第四个
                if (x1==x2 && x2==x3 && x3==x4)
                    //当两个都是对角线的情况，也就是四个交点都重合的时候
                    t=sum3[i]+sum3[j]-a[x1][y1];//只需减去唯一一个交点
                else if (x1==x2 && x3==x4 && x1!=x3)
                    //当有两个交点时，分别判断是x1与x2相同还是x1与x3相同
                    t=sum3[i]+sum3[j]-a[x1][y1]-a[x3][y3];//减去两个交点
                else if (x1==x3 && x2==x4 && x1!=x2)
                    //x1与x3相同
                    t=sum3[i]+sum3[j]-a[x1][y1]-a[x2][y2];//减去两个交点
                else
                    //四个交点都不重合的时候
                    t=sum3[i]+sum3[j]-a[x1][y1]-a[x2][y2]-a[x3][y3]-a[x4][y4];//减去四个交点
            }
            else
            {
                //当顶点横坐标差为奇数时，两个矩形没有交点，这点可以通过画图得出
                t=sum3[i]+sum3[j];//直接加和，不需要去除重叠部分
            }
            ans=max(ans,t);//与已有的最大值比较，找出最大值
        }
    }
    printf("%d\n",ans);//输出
    return 0;//结束
}
~~~

第一次写题解，包容一下…… :D

---

## 作者：Poncirus (赞：15)

To 管理员大大：改了一下实现方法，不仅保证了正确性（手动对拍几百组，应该能过），码量还减少到了原来的 $\dfrac13$（（（

随便画个图就可以发现，以第一行的每个点为起点可以覆盖所有可能路径。

因为这个吃豆人重复“碰到边缘就反弹”的动作，可能形成的，也就是两条对角线以及四个角分别在点阵四个边界上的长方形，而这些路径毫无疑问都会经过第一行。（也可以是第 $n$ 行，第 $1$ 列或第 $n$ 列，这里选用第一行是因为较好思考）

这些都可以直接模拟：我们把第一行的所有点都跑一遍，记录一下所有路径可以吃到的豆子总数，先不管重复经过的点。

由于第一行不能再往上走了，我们只用枚举从 $(1,x)$ 向左下、右下走的情况。

还可以继续优化：$(1,1)$ 只能向右下走，$(1,n)$ 只能向右下走。我们假设 $x\ne 1$ 且 $x\ne n$，那么吃豆人从 $(1,x)$ 出发向左下走和向右下走经过的路径其实是相同的，如图：

![图片.png](https://sc01.alicdn.com/kf/U83bb0045b50b49a29d0b8f6355d63cbbh.jpg)

那么干脆就只模拟向左下的情况咯。

动动脑子就可以发现，点阵四个边界上的点最多只会被一个长方形包含，中间的最多被两个长方形包含（分别是↙方向的路径和↗方向的路径）

为了方便，结合刚才我们得到的“从第一行出发可以覆盖所有可能路径情况”，我们将以 $(1,i)$ 为起点的路径所形成的长方形编号为 $i$。

于是，我们可以用一个 $vis$ 来标记，每当访问到一个点 $(c,r)$，则将 $vis_{c,r}$ 置为 $i$。其中，$(1,i)$ 为当前路径起点。

若 $vis_{c,r}$ 中已经有值，说明当前点同时被编号为 $i$ 和编号为 $vis_{c,r}$ 的两个长方形包含。

定义数组 $val$，$val_{i,j}$ 表示第编号为 $i$ 的长方形和编号为 $j$ 的长方形的重叠部分，那么此时 $val_{i,vis_{c,r}}$ 就加上当前点的豆子数。

最后计算时，我们枚举每两个长方形的组合 $i,j$，用 $i$ 的豆子总数加上 $j$ 的豆子总数，再减去 $val_{i,j}$，比较最大值。

```cpp
#define In_Limit(x,y) x&&y&&x<=n&&y<=n
#define kakagogo(x,y) (x==1&&y==1)||(x==1&&y==n)||(x==n&&y==1)||\
(x==n&&y==n)
const int fangx[]={1,1,-1,-1};			//方向从 0~3 分别为：左下，右下，右上，左上
const int fangy[]={-1,1,1,-1};
int LiuYangAKIOI[maxn];
int mp[maxn][maxn],vis[maxn][maxn],val[maxn][maxn];
int main(){
    read(n);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)
            read(mp[i][j]);
    }
    for(int i=1;i<=n;++i){
        c=1,r=i;						//c,r 表示以 (1,i) 为起点，吃豆人当前位置
        if(i==1)f=1;					//f 表示当前方向
        else f=0;
        vis[c][r]=i;					//先标记起点，虽然第一行的点只会经过一次
        nx=c+fangx[f],ny=r+fangy[f];	//nx,ny 表示按当前方向下一步可以到达的位置
        if(In_Limit(nx,ny))
            c=nx,r=ny;
        LiuYangAKIOI[i]=mp[1][i];		//LiuYangAKIOI 记录当前路径总豆子数
        while(c!=1||r!=i){				//不走回起点，使其可以在刚好走完一个长方形后停止
            if(!vis[c][r])				//从未访问过则标记
                vis[c][r]=i;
            else						//以防万一，双向标记
                val[vis[c][r]][i]=val[i][vis[c][r]]=val[vis[c][r]][i]+mp[c][r];
            LiuYangAKIOI[i]+=mp[c][r];
            if(kakagogo(c,r))			//如果到了点阵的四个角则停止
                break;
            if(c==n||c==1||r==n||r==1)	//若碰到边界则换方向
                f=f+1&3;
            nx=c+fangx[f],ny=r+fangy[f];
            if(In_Limit(nx,ny))
                c=nx,r=ny;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=i+1;j<=n;++j)
            ans=max(ans,LiuYangAKIOI[i]+LiuYangAKIOI[j]-val[i][j]);
    }
    printf("%d",ans);
    return 0;
}
```



---

## 作者：Terac (赞：10)

[原题](https://www.luogu.com.cn/problem/P7472)  

首先看数据范围 $n\le10^3$，那么想到是一个 $O(n^3)$ 或 $O(n^2)$ 的做法。  

画图观察一下，发现对于每个边上的点，是具有确定性的，无论从哪个方向出发，均有且仅有一种矩阵能包含边上的点，于是考虑以边上的点确定每一个不同的矩阵。  

容易看出每个点出发的矩阵都会绕一圈回到该点，每个矩阵边上的点数量不超过 $2(n-1)$。于是可用第一行的每个点来表示经过该点的矩阵并预处理出每一个矩阵经过的点权之和，时间复杂度为 $O(n^2)$。  

需要注意会有线状的矩阵，不能重复加两次，需要特判一下。

枚举任意两个矩阵，发现所选的两个矩阵还可能会有重复的部分需要减去，这里需要分类讨论。  

设选择的矩阵分别包含第一行的第 $i$ 个和第 $j$ 个点，不妨设 $j>i$，$c_x$ 表示第一行第 $x$ 个点对应的矩阵点权之和，则有以下结论：  
1. 当 $j-i$ 为奇数时，$ans=c_i+c_j$。此时这两个矩阵不会有公共点，原因是它们的中点不是整数，其交点纵坐标也不是整数。  
2. 当 $j-i$ 为偶数且 $i=1,j=n$ 时，$ans=c_i+c_j-a_{\frac{n+1}{2},\frac{n+1}{2}}$。两个矩阵皆为线状，只有一个交点在矩阵中心。  
3. 当 $j-i$ 为偶数且 $i=1$ 和 $j=n$ 仅满足任意一条件时，$ans=c_i+c_j-a_{1+\frac{j-i}{2},\frac{i+j}{2}}-a_{n-\frac{j-i}{2},n-\frac{i+j}{2}+1}$。这是仅一个矩阵为线状时的情况，结论貌似很难懂，但画画图就发现纵坐标和中点有关，然后就很好理解了。  

4. 当 $j-i$ 为偶数且 $i\not=1,j\not=n$ 时，$ans=c_i+c_j-a_{1+\frac{j-i}{2},\frac{i+j}{2}}-a_{n-\frac{j-i}{2},n-\frac{i+j}{2}+1}-a_{\frac{i+j}{2},1+\frac{j-i}{2}}-a_{n-\frac{i+j}{2}+1,n-\frac{j-i}{2}}$。实质上就是满足了正方形的对称性，互换了下横纵坐标即为另外两个的交点。  

总体时间复杂度为 $O(n^2)$，这个数据范围稳过。  

```cpp
#include <bits/stdc++.h>
using namespace std;
const int kx[] = {1, 1, -1, -1}, ky[] = {-1, 1, 1, -1};
const int N = 1e3 + 10;
int n, a[N][N], c[N], ans;
bool vis[N][N];
int main() {
//	freopen("pacman.in", "r", stdin);
//	freopen("pacman.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; i++)
		c[1] += a[i][i], c[n] += a[i][n - i + 1];
	for(int i = 2; i < n; i++) {
		int x = 1, y = i, op = 0, sum = 0;
		bool flag = false;
		for(;;) {
			if(x == 1 && y == i && flag) {
				c[i] = sum;
				break;
			}
			sum += a[x][y];
			flag = true;
			if(x + kx[op] <= 0 || x + kx[op] > n || y + ky[op] <= 0 || y + ky[op] > n)
				op++;
			x += kx[op], y += ky[op];
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) {
			if(i == j)
				continue;
			int mx = max(i, j), mn = min(i, j);
			if((mx - mn) & 1) {
				ans = max(ans, c[i] + c[j]);
			}
			else if(mn == 1 && mx == n) {
				int t = c[i] + c[j] - a[(i + j) / 2][(i + j) / 2];
				ans = max(ans, t);
			}
			else {
				int t = c[i] + c[j];
				t -= a[1 + (mx - mn) / 2][(i + j) / 2];
				t -= a[n - (mx - mn) / 2][n - (i + j) / 2 + 1]; 
				if(mn == 1 || mx == n)
					ans = max(ans, t);
				else {
					t -= a[(i + j) / 2][1 + (mx - mn) / 2];
					t -= a[n - (i + j) / 2 + 1][n - (mx - mn) / 2];
					ans = max(ans, t);
				}
			}
		}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：cyffff (赞：7)

[P7472 [NOI Online 2021 入门组] 吃豆人](https://www.luogu.com.cn/problem/P7472)
## 题意
略
## 思路
考虑每个点出发会形成什么样的图形，枚举 $n\le 7$ 发现每个第一行的点中 $1,n$ 号点占据两条对角线，其余点从自身出发循环回到自身，覆盖所有点。

考虑维护 $4$ 个值，表示四个倾斜角度中第 $i$ 层的数的总和，即 
$$s_{1,i}=\sum_{j,k\ge1}a_{j,k}[j+k=i+1]$$
$$s_{2,i}=\sum_{j,k\ge1,k\le i}a_{j,k}[j-k=n-i]$$
$$s_{3,i}=\sum_{j,k\ge1,k\le n}a_{j,k}[j+k=2n-i+1]$$
$$s_{4,i}=\sum_{j,k\ge1,j\le i}a_{j,k}[k-j=n-i]$$
则第 $1$ 行第 $i$ 个位置的矩形的价值为
$$val_i=\begin{cases}s_{2,n}&i=1\\s_{3,n}&i=n\\s_{1,i}+s_{2,n-i+1}+s_{3,i}+s_{4,n-i+1}-a_{1,i}-a_{i,1}-a_{n,n-i+1}-a_{n-i+1,n}&2\le i< n\end{cases}$$
则最后枚举矩形删去相交点即可。

时间复杂度 $O(n^2)$。

再见 qwq~

---

## 作者：Unordered_OIer (赞：5)

# P7472 题解

考场上差点就做出来了，两个小小的 bug 能差不多让我 $100 \text{pts}$ 挂到差不多 $30 \sim 40\text{pts}$。

菜的真实

****

$\texttt{Update:}$ 修改了 $s1,s2$ 与文字定义与图片内容相反的错误。

## Description
给定一个 $n \times n$ 的二维格点图，$(i,j)$ 的格点图有 $a_{ij}$ 个豆子，一个吃豆人会以 $45\degree$ 斜角度不停地吃所经过的所有格子里的所有豆子。碰到边缘后吃豆人会 $90\degree$ 反弹到另一放向继续吃，以此类推。吃完豆子后格子里将不再有豆子。

有两个吃豆人，起点不定，问最多能吃到多少豆子。

## Solution
$n \leq 3$ 的数据肯定是送给暴搜的。  

$n \leq 100$ 的数据应该是送给优化过的暴搜的。

****

直接说正解。

因为只会碰到边缘后反弹，所以只要四边形的端点固定了整个路径就固定了。

因此我们可以想到利用这一性质快速求出一条路径的豆子和。

考虑维护 $↘$ 方向与 $↙$ 方向的豆子和，记为 $s2,s1$。

规定如下标号：

![](https://cdn.luogu.com.cn/upload/image_hosting/vgl2ouq1.png)

则以 $(x,y)$ 为端点（规定 $x>y$ 且 $y=1$）的路径权值和为 $s1[x]+s1[2 n-x]+s2[n-x+1]+s2[n+x-1]-(a[x][y]+a[y][x]+a[n-x+1][n-y+1]+a[n-y+1][n-x+1])$

~~手推一下即可~~

还有一个要注意的是如果路径是一条线的话要特判一下。

然后后面就没什么好说的了，直接暴力枚举两个端点开头，依次计算两个吃豆人的得分总和，并减去重复部分的格点内豆子数量即可。

复杂度 $\mathcal O(n^2)$。

因为这题数据 $1 \le n \leq 1000$，所以 $n^2$ 稳过。

但是这题细节很多：
1. $s1,s2$ 要开 $2n-1$ 的空间
2. 判断重复部分的时候要将线形路经和四边形路径特判一下



---

## 作者：pengyule (赞：3)

容易发现一个吃豆人要吃就吃一个矩形，就是不妨设他从第一排的一个点向左下出发，碰壁，向右下，碰壁，向右上，碰壁，向左上，回到出发点。另外这只适合不是 $(1,1)$ 和 $(1,n)$ 的点，这两个点就是吃掉所在对角线上的所有数。

把从 $(1,i)(1\leq i\leq n)$ 出发的答案存进 $b$ 数组，$O(n^2)$ 枚举两个吃豆人的出发点 $(1,p)$ 和 $(1,q)$ 所对应的 $b$ 中的答案，再减去两条路径的重合部分即可（因为一个豆子只能吃一次）。

---
找到两条路线重合的部分

不妨令 $p<q$。
1. 两条对角线：如果n是偶数就没有重合部分；是奇数就多算了 $a[(1+n)/2][(1+n)/2]$。
2. 一条“$(1,1)-(n,n)$”对角线+一个矩形：如果q是偶数，那么没有重合部分；是偶数，重合了 $a[(1+q)/2][(1+q)/2]$ 和 $a[n-(1+q)/2+1][n-(1+q)/2+1]$。
3. 一条“$(n,1)-(1,n)$”对角线+一个矩形：如果(n-p)是奇数，那么没有重合部分；是偶数，重合了 $a[(i+j)/2][n-(i+j)/2+1]$ 和 $a[n-(i+j)/2+1][(i+j)/2]$。
4. 两个矩形：如果(q-p)是奇数，那么没有重合部分；是偶数，重合了四个位置：$a[(j-i)/2+1][(i+j)/2]$，$a[(j-i)/2+i][(i+j)/2-i+1]$，$a[(j-i)/2+n-j+1][(i+j)/2+n-j]$，$a[(j-i)/2+i+n-j][(i+j)/2+n+1-j-i]$。

$b[p]+b[q]-$ 重合部分的和 $=$ 吃到的豆子，用一个变量更新答案即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[1005][1005];
signed main(){
	freopen("pacman.in","r",stdin);
	freopen("pacman.out","w",stdout);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
	if(n==2){
		cout<<a[1][1]+a[1][2]+a[2][1]+a[2][2]<<endl;
		return 0;
	}
	vector<int>b;b.clear();
	for(int i=1;i<=n;i++){
		int v=0;
		int x=1,y=i;
		for(;y>1;x++,y--) v+=a[x][y];
		for(;x<n;x++,y++) v+=a[x][y];
		for(;y<n;x--,y++) v+=a[x][y];
		for(;x>1;x--,y--) v+=a[x][y];
		if(i>1&&i<n)b.push_back(v);
		else if(i==1) b.push_back((v+a[1][1]+a[n][n])/2);
		else b.push_back((v+a[1][n]+a[n][1])/2);
	}
	int ans=0;
	for(int i=0;i<b.size();i++){
		for(int j=i+1;j<b.size();j++){
			if(i==0&&j==b.size()-1){
				if(n&1) ans=max(ans,b[i]+b[j]-a[n/2+1][n/2+1]);
				else ans=max(ans,b[i]+b[j]);
			}
			else if(i==0){
				if(j-i&1) ans=max(ans,b[i]+b[j]);
				else ans=max(ans,b[i]+b[j]-a[(i+j)/2+1][(i+j)/2+1]-a[n-(i+j)/2][n-(i+j)/2]);
			}
			else if(j==b.size()-1){
				if(j-i&1) ans=max(ans,b[i]+b[j]);
				else ans=max(ans,b[i]+b[j]-a[(i+j)/2+1][n-(i+j)/2]-a[n-(i+j)/2][(i+j)/2+1]);
			}
			else {
				if(j-i&1) ans=max(ans,b[i]+b[j]);
				else ans=max(ans,b[i]+b[j]-a[(j-i)/2+1][(i+j)/2+1]-a[(j-i)/2+1+i][(i+j)/2+1-i]-a[(j-i)/2+1+n-1-j][(i+j)/2+1+n-1-j]-a[(j-i)/2+1+i+n-j-1][(i+j)/2+1+n-1-j-i]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
       

---

## 作者：meyi (赞：3)

我们假设每条行进路线的起点都是第一行的某个点，于是可以 $O(n^2)$ 枚举第一行的两个点，计算出其答案，取最大值。

可以看出该做法的瓶颈在于如何计算答案。我们**先不考虑重复计入每个点的情况**，那么设 $l_{1,i}$ 为第一行第 $i$ 个点向左反射，碰到边界就终止，可以得到的贡献，则 $l_{1,i}=\sum\limits_{j=1}^ia_{i-j+1,j}$。同理，我们设 $l_{n,i}$ 为第 $n$ 行第 $i$ 个点向左反射的贡献，$r_{1,i}$ 为第 $1$ 行第 $i$ 个点向右反射的贡献，$r_{n,i}$ 为第 $n$ 行第 $i$ 个点向右反射的贡献，则可以得到 $l_{n,i}=\sum\limits_{j=1}^ia_{n-i+j,j}$，$r_{1,i}=\sum\limits_{j=i}^na_{j-i+1,j}$，$r_{n,i}=\sum\limits_{j=i}^na_{n-j+i,j}$。我们 $O(n^2)$ 预处理 $l,r$ ，于是以第一行第 $k$ 个点为起点可以得到的贡献为 $l_{1,k}+r_{1,k}+l_{n,n-k+1}+r_{n,n-k+1}$ （这里会对顶点处的数值重复计算，去重的方法会在后面提到）。

但我们的是需要两个点的贡献去重后的结果，不难发现，重复的点必定为两条直线的交点（可自行画图理解），于是我们以 $(0,0)$ 为原点建立平面直角坐标系，将行进路线拆成四条线段（若 $k=1$ 或 $n$ ，则拆成一条线段和该线段 $y=1$ 的端点，因为需要把该点的 $l,r$ 产生的重复去除），并将其所在直线的解析式记录下来，简单计算得到所有记录下的直线的交点，若该点满足 $x,y \in [1,n] \cap N^*$，则答案减去 $a_{y,x}$。

于是我们在 $O(n^2)$ 时间内解决了本题（常数有点大）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=1e3+10;
int a[maxn][maxn],l[maxn][maxn],n,r[maxn][maxn];
struct node{
	int k,b;
	inline node(int k_=0,int b_=0):k(k_),b(b_){}
};
inline int get1(node p,node q){
	if(p.k==q.k||((p.b-q.b)%(q.k-p.k)!=0))return 0;
	ri x=(p.b-q.b)/(q.k-p.k),y=p.k*x+p.b;
	if(x<1||x>n||y<1||y>n)return 0;
	return a[y][x];
}
vector<node>vl,vr;
inline int get2(int k){
	if(k==1||k==n){
		vl.push_back(node(1,1-k));
		vr.push_back(node(-1,1+k));
		return l[1][k]+r[1][k];
	}
	ri d=n-k+1,ans=l[1][k]+r[1][k]+l[n][d]+r[n][d];
	vl.push_back(node(1,1-k));
	vl.push_back(node(1,n-d));
	vr.push_back(node(-1,1+k));
	vr.push_back(node(-1,n+d));
	return ans;
}
inline int get3(int p,int q){
	vl.clear(),vr.clear();
	ri ans=get2(p)+get2(q);
	for(ri i=0;i<vl.size();++i)
		for(ri j=0;j<vr.size();++j)
			ans-=get1(vl[i],vr[j]);
	return ans;
}
int main(){
	scanf("%d",&n);
	for(ri i=1;i<=n;++i)
		for(ri j=1;j<=n;++j)
			scanf("%d",&a[i][j]);
	for(ri i=1;i<=n;++i){
		for(ri x=1,y=i;y<=n;++x,++y)r[1][i]+=a[x][y];
		for(ri x=1,y=i;y;++x,--y)l[1][i]+=a[x][y];
		for(ri x=n,y=i;y;--x,--y)l[n][i]+=a[x][y];
		for(ri x=n,y=i;y<=n;--x,++y)r[n][i]+=a[x][y];
	}
	ri ans=0;
	for(ri i=1;i<n;++i)
		for(ri j=i+1;j<=n;++j)
			ans=max(ans,get3(i,j));
	printf("%d",ans);
	return 0;
}
```

---

## 作者：syf2008 (赞：3)

首先看数据范围 $n\le10^3$,故要用小于$O(n^2)$的算法

当n=5时
![](https://cdn.luogu.com.cn/upload/image_hosting/lvbxjr23.png)

一共有5个矩阵,然后就用$n^2$选两个去算最大值

上代码
```
#include<bits/stdc++.h>
using namespace std;
int n,h,l,s,maxn,ans[1005],a[1005][1005],v[1005][1005];
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	cin>>a[i][j];
	for(int j=1;j<=n;j++)
	ans[1]+=a[j][j];
	for(int j=1;j<=n;j++)
	ans[n]+=a[j][n-j+1];//特判两条对角线
	for(int i=2;i<n;i++)//以第一行为准，找矩阵
	{
		h=1;
		l=i;
		ans[i]=ans[i]-a[1][i]-a[i][1]-a[n][n-i+1]-a[n-i+1][n];
		while(h<=n&&l<=n)
		{
		ans[i]+=a[h][l];
		h++;
		l++;
		}
		h=1;
		l=i;
		while(h<=n&&l>=1)
		{
		ans[i]+=a[h][l];
		h++;
		l--;
		}
		h=n;
		l=n-i+1;
		while(h>=1&&l<=n)
		{
		ans[i]+=a[h][l];
		h--;
		l++;
		}
		h=n;
		l=n-i+1;
		while(h>=1&&l>=1)
		{
		ans[i]+=a[h][l];
		h--;
		l--;
		}//类似蛇形方阵的转弯
	}
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)//用n^2选两个
	if((i+j)%2==0)//判重
	{
		v[i][j]=v[i][j]+a[(j-i)/2+1][(i+j)/2]+a[n-((j-i)/2)][n+1-((i+j)/2)];
		if(i!=1&&j!=n)
		v[i][j]=v[i][j]+a[(i+j)/2][((j-i)/2)+1]+a[n+1-((i+j)/2)][n-((j-i)/2)];
	}
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)
	if(i==1&&j==n)//特判选2条对角线
	maxn=max(maxn,ans[i]+ans[j]-v[i][j]/2);
else maxn=max(maxn,ans[i]+ans[j]-v[i][j]);
	cout<<maxn<<endl;
}
```

---

## 作者：Remake_ (赞：2)

暴力出奇迹qwq

遇到这种题，我们首先要发掘一些性质：

$1.$ 无论吃豆人在何种位置何种方向，最后一定会弹射回这个点，且弹射路径构成一个矩形（线）

$2.$ 总共只有 $n$ 种本质不同的矩形（线），其中第 $i$ 个矩形（线）的起点为 $(1,i)$ 

$3.$ 每个点最多被两个本质不同的矩形（线）包含

至于这些性质是为什么，把 $n=4,5,6$ 的图分别画一下就能发现了（）


然后我们就可以暴力膜你了

对于每一个矩形（线）的起点，我们给它设一个初始方向让它暴力把这个矩形（线）走出来，同时记录沿途经过的所有数的和

这样复杂度是有保证的，因为每个点最多被访问两次，所以直接均摊了

然后找和最大的两个矩形（线）就做完了


吗？

显然没有，我们找到的两个矩形（线）是可能有交的！

于是我们在暴力模拟的时候记录一下每个点在哪些矩形（线）内

根据这个用容斥原理随便算一下本题就做完了

上代码:

```cpp
const ll dx[10]={0,1,1,-1,-1},dy[10]={0,1,-1,1,-1};
ll n,a[1005][1005],st,en,dir,now=1,pd=1;
ll sum[1005],jc[1005][1005];
queue<pair<ll,ll> > q;
vector<ll> pos[1005][1005];
void mem(){
   while(q.size()){
      pos[q.front().first][q.front().second].pb(now);
      sum[now]+=a[q.front().first][q.front().second];
      q.pop();
   }
   ++now;
   return;
}
void to(ll x,ll y){
   q.push(mp(x,y));
   if(pd) return;
   if(x!=1&&y!=1&&x!=n&&y!=n) return;
   if(x==1){
      if(dir==4) dir=2;
      else if(dir==2) dir=4;
      if(dir==3) dir=1;
      else if(dir==1) dir=3;
   }
   if(y==1){
      if(dir==2) dir=1;
      else if(dir==1) dir=2;
      if(dir==3) dir=4;
      if(dir==4) dir=3; 
   }
   if(x==n){
      if(dir==1) dir=3;
      else if(dir==3) dir=1;
      if(dir==2) dir=4;
      else if(dir==4) dir=2;
   }
   if(y==n){
      if(dir==3) dir=4;
      else if(dir==4) dir=3;
      if(dir==2) dir=1;
      else if(dir==1) dir=2;
   }
   return;
}
int main(){
   rd(n);
   rep(i,1,n) rep(j,1,n) rd(a[i][j]);
   rep(i,1,n) q.push(mp(i,i));
   mem();
   rep(i,2,n-1){
      st=1;
      en=i;
      ll nowx=st,nowy=en;
      dir=1;
      pd=1;
      while(1){
         to(nowx,nowy);
         nowx+=dx[dir];
         nowy+=dy[dir];
         if(nowx==st&&nowy==en){
            mem();
            break;
         }
         pd=0;
      }
   }
   rep(i,1,n) q.push(mp(i,n-i+1));
   mem();
   rep(i,1,n){
      rep(j,1,n){
         if(pos[i][j].size()==2){
            jc[pos[i][j][1]][pos[i][j][0]]+=a[i][j];
            jc[pos[i][j][0]][pos[i][j][1]]+=a[i][j];
         }
      }
   }
   ll ans=0;  
   rep(i,1,now-1) rep(j,1,now-1) if(i!=j) ans=max(ans,sum[i]+sum[j]-jc[i][j]);
   printf("%lld",ans);
}
```


---

## 作者：SUNCHAOYI (赞：2)

1. 这道题大家可以先画画图，然后发现周围除四个角的任意一点出发，总能回到该点。因此我们可以只求出第一行开始遍历的求和答案，注意**四角的两点需要特判**！  
2. 至于如何求一个环之和，我们就找规律。令一开始往右下的方向走，则不断碰壁更改的方向依次是：**右下 -> 左下 -> 左上->右上**。直到回到原位。这样我们把第一行全部遍历后就能分别得到每条路径对应的豆子数量之和。所以下一步我们需要找到两条不同的路径减去**重复部分**后的最大值。  
3. 以题目中的图为例，我们再次找规律，设选择的两条路径第一行的横坐标为  $x,y(x < y)$，发现只有第一行两点间的距离为偶数时才可能出现交点。其次，易得两点距离为$y - x$ 则交点分别在任意一条路径与最大方框交点的向上、下、左、右的 $\frac{y-x}{2}$ 的点上（感性理解一下，就是如下图二箭头所指的四个点)。 

![1](https://cdn.luogu.com.cn/upload/image_hosting/1axaad1b.png)
![2](https://cdn.luogu.com.cn/upload/image_hosting/14dbdo32.png)

4. 注意的是，重复需要减去的点也有可能会有重叠。因此，**需要判断重复的点是否相同**。这个判断用 `if` 就行，千万不要用什么 `map` 等去判断！！！

---

最后发一下完整代码，没理解的看一下具体的实现：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 1e3 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int n,cnt,ans;
int a[MAX][MAX],num[MAX];
bool vis[MAX];
void search (int x,int y,int st);
int work (int x,int y);
int main ()
{
	freopen ("pacman.in","r",stdin);
	freopen ("pacman.out","w",stdout);
	n = read ();
	for (int i = 1;i <= n;++i) 
		for (int j = 1;j <= n;++j) a[i][j] = read ();
	for (int i = 1;i <= n;++i)
	{
		cnt = 0;
		if (i == 1) for (int j = 1;j <= n;++j) cnt += a[j][j];
		else if (i == n) for (int j = 1;j <= n;++j) cnt += a[n - j + 1][j];
		else search (1,i,1);
		num[i] = cnt;
	}
	for (int i = 1;i <= n;++i)//找到最优解
		for (int j = i + 1;j <= n;++j) ans = max (ans,work (i,j));
	printf ("%d\n",ans);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void search (int x,int y,int st)
{
	if (x == 1)
	{
		if (vis[y]) return ;//回到原位
		else vis[y] = 1;
	}
	cnt += a[x][y];//累加
   //不同方向
	if (y == 1) st = 3;
	if (y == n) st = 2;
	if (x == n) st = 4;
	if (st == 1) search (x + 1,y + 1,st);
	if (st == 2) search (x + 1,y - 1,st);
	if (st == 3) search (x - 1,y + 1,st);
	if (st == 4) search (x - 1,y - 1,st);
}
int work (int x,int y)
{
	int sum = num[x] + num[y],same = 0;
	if ((y - x) % 2 == 1) return sum;//没有交点的情况
	int len = (y - x) / 2;
	same += a[len + 1][x + len];//判重复的方向，注意不要重复减去！！！不要用map
	if (x + len != len + 1) same += a[x + len][len + 1];
	if ((n - x) + 1 - len != x + len && n - len != 1 + len && (n - x) + 1 - len != 1 + len && n - len != x + len) same += a[(n - x) + 1 - len][n - len];
	if ((n - x) + 1 - len != x + len && n - len != 1 + len && (n - x) + 1 - len != 1 + len && n - len != x + len && (n - x + 1) - len != n - len) same += a[n - len][(n - x) + 1 - len];
	return sum - same;	
}
```

---

## 作者：TRZ_2007 (赞：1)

**[题解 【[NOI Online 2021 入门组] 吃豆人】](https://www.luogu.com.cn/problem/P7472)**    

**update 2021.4.4**：Task 2 的做法，本题的 AC 代码
。
# Solution  

Task1：暴力枚举每一个放置吃豆人的位置，然后暴力计算求最大值，时间复杂度 $\mathcal{O(n^5)}$，期望得分 30pts。

Task2：模拟每一个吃豆人所走的路线，枚举每一个点，计算最大值。相较 Task1 做法不同的是，我们这边可以先存下来赤豆人所走的路线，方向，在枚举完第二个吃豆人的起点与方向后再进行计算，而且正如正解所说，我们只需要枚举第一列就可以了。这样干掉了一个 $n$，时间复杂度为 $\mathcal{O(n^3)}$。

**正解**：观察吃豆人所走的路线，发现除了对角线之外其他的路径都可以重合（具体证明可以通过数学方法得到），而且关于每一个点，最多只会有两段路径和它重合，因此我们可以考虑计算每一段路径可以吃到的豆的数量，令 $f_i$ 表示从 $(1,i)$ 出发的路径能吃到多少的豆，$p_{i,j}$ 表示路径 $i$ 和 路径 $j$ 所重合的豆的数量，其中 $f$ 可以通过暴力模拟路径所计算，那么最终的答案就是 $\max {f_i+f_j-p_{i,j}}$，总的时间复杂度为 $\mathcal{O(n^2)}$，可以通过本题。

# Code  

```cpp
#include <cstdio>
#include <cctype>
using namespace std;

const int N = 1009;

#define gc getchar
inline int read() {
	int c = gc(), t = 1, n = 0;
	while(isspace(c)) { c = gc(); }
	if(c == '-') { t = -1, c = gc(); }
	while(isdigit(c)) { n = n * 10 + c - '0', c = gc(); }
	return n * t;
}
#undef gc

#define max(a,b) a > b ? a : b

int n,a[N][N],sum1[N][N],sum2[N][N],cnt[N],ans,tmp;
// 这里的 cnt 表示题解中的 f，两个sum分别表示斜上方和斜下方所走的路径的前缀和，方便我们的计算。
int x1,x2,x3,x4,y1,y2,y3,y4;

int main() {
	n = read();
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) a[i][j] = read();
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= n;j++) {
			sum1[i][j] = sum1[i - 1][j - 1] + a[i][j];	//斜下方
			sum2[i][j] = sum2[i - 1][j + 1] + a[i][j];	//斜上方
		}
	}
	cnt[1] = sum1[n][n]; cnt[n] = sum2[n][1];	//特殊情况：对角线
	for(int i = 2;i < n;i++) {
		cnt[i] = sum1[n][n - i + 1] + sum1[n - i + 1][n] + sum2[i][1] + sum2[n][n - i + 1];
		cnt[i] = cnt[i] - a[1][i] - a[i][1] - a[n - i + 1][n] - a[n][n - i + 1];
        //通过题解描述我们可以知道： Fi 所走的路径为：(1,i)->(n - i + 1,n) -> (n,n - i + 1) -> (i,1) -> (1,i)，所以把这四列加在一起，减去它们的交点就可以了
	}
	ans = -1;
	for(int i = 1;i <= n;i++) {
		for(int j = i + 1;j <= n;j++) {
			tmp = cnt[i] + cnt[j];
			if((j - i) % 2 == 0) {	//如果两个起点的 i 的变化量是偶数的话，那么就会有交点，否则没有交点，可以用初中数学知识证明
				x1 = 1 + (j - i) / 2; y1 = (i + j) / 2;
				x2 = y1; y2 = x1;
				x3 = n - y1 + 1; y3 = n - x1 + 1;
				x4 = y3; y4 = x3;
				if(x1 == x2 && x2 == x3 && x3 == x4) tmp -= a[x1][y1];
				else if(x1 == x2 && x3 == x4 && x1 != x3) tmp -= (a[x1][y1] + a[x3][y3]);
				else if(x1 == x3 && x2 == x4 && x1 != x4) tmp -= (a[x1][y1] + a[x2][y2]);
				else tmp -= (a[x1][y1] + a[x2][y2] + a[x3][y3] + a[x4][y4]);	//这几行 if 都属于去重，即减去 p(i,j)，可以提前算，在这里算也是可以的
			}
			ans = max(ans,tmp);
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

