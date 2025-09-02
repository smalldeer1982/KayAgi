# [IOI 2009] Raisins

## 题目背景

IOI2009 D1T4

## 题目描述

普罗夫迪夫的著名巧克力大师 Bonny 需要切开一板带有葡萄干的巧克力。巧克力是一个包含许多相同的方形小块的矩形。小块沿着巧克力的边排列成 $N$ 行 $M$ 列，共有 $N\times M$ 块。每个小块上有 $1$ 个或多个葡萄干，没有葡萄干在小块的边上或者跨过两个小块。

最开始，巧克力是一整块。Bonny 需要把它切成上述的 $N\times M$ 个独立的小块。因为 Bonny 很忙，她需要她的助手 Sly Peter 帮她切。
Peter 只能从一端到另一端切直线，并且他要为他的每一刀得到报酬。Bonny 手头没有钱，但是她有足够的葡萄干，所以她提出用葡萄干付给 Peter。Sly Peter 同意接受葡萄干，但是有下面的条件：每次他把给定的一块巧克力切成两小块，他都要得到和那块给定的巧克力上葡萄干数目相同的葡萄干。

Bonny 想要付给 Peter 尽可能少的葡萄干。她知道这 $n\times m$ 个小块中每一个小块上葡萄干的数目。她可以选择递给 Peter 的巧克力的顺序，也可以告诉 Peter 如何切（横切还是竖切）以及从哪里切。请告诉 Bonny 如何把巧克力切成一个个独立的小块，使她能够付给 Sly Peter 尽可能少的葡萄干。

**任务**：编写一个程序，给定每个小块上葡萄干的数目，计算出 Bonny 要付给 Sly Peter 的最少的葡萄干的数目。

## 说明/提示

### 样例解释

一种可能的代价为 $77$ 的切割方案如下所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/zg74ypip.png)

第一次切割将第三列和剩下来的巧克力分开了。Bonny 需要付给 Peter $29$ 个葡萄干。

接下来 Bonny 把较小的那一块巧克力（有两小块，每一块都有 $5$ 个葡萄干）给 Peter，要求 Peter 切成两半并支付 $10$ 个葡萄干。

在此之后，Bonny 给 Peter 剩下来的最大块（分别有 $2,  7, 1, 9$ 个葡萄干在它的四个小块上）。Bonny 要求 Peter 水平切割这一块，将第一行和第二行分开并付给他 $19$ 个葡萄干。

此后 Bonny 给 Peter 左上角的块，支付 $9$ 个葡萄干。最后 Bonny 要求 Peter 将左下角的块分开，支付 $10$ 个葡萄干。

Bonny 的总代价是 $29 + 10 + 19 + 9 + 10 = 77$ 个葡萄干。没有其它安排切割的方案有更小的代价。

### 数据范围与约定

- 对于 $25\%$ 的数据，$n,m\leq 7$。
- 对于 $100\%$ 的数据，$1\leq n,m\leq 50$，$1\leq R_{k, p}\leq 1000$。

## 样例 #1

### 输入

```
2 3
2 7 5
1 9 5
```

### 输出

```
77
```

# 题解

## 作者：SuperJvRuo (赞：6)

此题竟然放在了D1T4的位置，不知组题人有何居心。完全是一道NOIP普及组题。

不难想到$O(n^5)$的dp解法，状态数$O(n^4)$，转移$O(n)$。$f[i][j][k][l]$表示左上角为$u$行$l$列，右下角为$d$行$r$列的子矩形的结果。对这个子矩形切一刀有$O(n)$种切法，因此转移为$O(n)$。预处理出前缀和，写一发记忆化搜索~~开启o2优化~~就过了。

```
#include<cstdio>
#include<climits>
#include<algorithm>
#define LL long long

int sum[55][55];

LL f[55][55][55][55];

LL dfs(int u,int d,int l,int r)
{
	if(f[u][d][l][r])
		return f[u][d][l][r];
	else if(u==d&&l==r)
	{
    	//递归边界，如果只剩一小块，返回0
		return 0;
	}
	else
	{
		f[u][d][l][r]=LLONG_MAX;
		LL cut=sum[d][r]-sum[d][l-1]-sum[u-1][r]+sum[u-1][l-1];//这一大块上的总数
		for(int i=l;i<r;++i)
		{
			f[u][d][l][r]=std::min(dfs(u,d,l,i)+dfs(u,d,i+1,r),f[u][d][l][r]);
		}
        //竖着切
		for(int i=u;i<d;++i)
		{
			f[u][d][l][r]=std::min(dfs(u,i,l,r)+dfs(i+1,d,l,r),f[u][d][l][r]);
		}
        //横着切
		f[u][d][l][r]+=cut;
		return f[u][d][l][r];
	}
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int temp;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			scanf("%d",&temp);
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+temp;
		}//预处理前缀和
	}
	printf("%lld",dfs(1,n,1,m));
	return 0;
}
```

---

## 作者：chinuya (赞：4)

### 为了纪念[第一道蓝题](https://www.luogu.com.cn/user/685664)，特来写一篇题解。 ###
2022.8.25：更改了 LaTeX 格式。
### 直奔主题： ###
## 思路: ##
显然的，当有一个矩阵满足：

+ 左上角坐标为 $(a1,b1)$，右下角坐标为 $(a2,b2)$

则这个矩阵的最优解为：

+ 将这个矩阵切开（横、竖）后的两个矩阵的最优解中的最小值与这个矩阵的各元素之和。

![竖着切](https://cdn.luogu.com.cn/upload/image_hosting/rv6bk7ft.png)

![横着切](https://cdn.luogu.com.cn/upload/image_hosting/859dma74.png)

如上，是横着切和竖着切的两种情况。

所以，我们可以 dfs 枚举每一刀切的位置。同时，用记忆化删去部分冗余的计算。定义一个数组 $f_{a,b,c,d}$ 进行记忆化搜索。

## 代码： ##
```cpp
#include<bits/stdc++.h>//支持万能头文件！！
using namespace std;
int n,m;
int ra[60][60];			//每块巧克力上的葡萄干数量
int f[60][60][60][60];  //记忆化
int dfs(int a,int b,int c,int d)	
{
	if(f[a][b][c][d]!=0)//如果已经切过这种情况了
    		return f[a][b][c][d];//直接返回	
    	if(b==d&&a==c)	return 0;//如果开始点和结束点是同一点,即没法切了，就return
	int ma=1e10;//赋一个极大值，以便后来作min运算
	for(int i=a;i<c;i++)	ma=min(ma,dfs(a,b,i,d)+dfs(i+1,b,c,d));//横着切，即上边加下边
	for(int i=b;i<d;i++)	ma=min(ma,dfs(a,b,c,i)+dfs(a,i+1,c,d));//竖着切，即左边加右边
	for(int i=a;i<=c;i++)
		for(int j=b;j<=d;j++)
			ma+=ra[i][j];//要付出多少葡萄干
	return f[a][b][c][d]=ma;
	/*等价于:
	f[a][b][c][d]=ma;
	return f[a][b][c][d];*/
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ra[i][j];	//循环输入葡萄干
		}
	}
	cout<<dfs(1,1,n,m);
	return 0;
}

```
这种做法开 O2 就可以 AC 了，~~但是，作为一个合格的 oier ,我们应该不断追求更好的做法。~~

## 优化思路: ##
因为考虑到每进行一次 dfs，就要算一遍葡萄干的和，所以很自然地想到利用前缀和数组来优化。

每输入一个数，则对其进行前缀和计算。就避免每次搜索都用一个双层循环来计算。

前缀和代码： $s_{i.j}=s_{i-1,j}+s_{i,j-1}-s_{i-1,j-1}+a_{i,j}$
## AC代码： ##

```cpp
#include<bits/stdc++.h>//支持万能头文件！！
using namespace std;
int n,m;
int ra[60][60];			//每块巧克力上的葡萄干数量
int f[60][60][60][60];  //记忆化
int cc[60][60];			//前缀和数组
int dfs(int a,int b,int c,int d)	
{
	
	if(f[a][b][c][d]!=0)//如果已经切过这种情况了
		return f[a][b][c][d];//直接返回	
	if(b==d&&a==c)	return 0;//如果开始点和结束点是同一点,即没法切了，就return
	int ma=1e10;
	for(int i=a;i<c;i++)	ma=min(ma,dfs(a,b,i,d)+dfs(i+1,b,c,d));//横着切，即上边加下边
	for(int i=b;i<d;i++)	ma=min(ma,dfs(a,b,c,i)+dfs(a,i+1,c,d));//竖着切，即左边加右边
	f[a][b][c][d]=ma+cc[c][d]-cc[a-1][d]-cc[c][b-1]+cc[a-1][b-1];
	//这里使用前缀和优化
	return f[a][b][c][d];
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ra[i][j];	//循环输入葡萄干
			cc[i][j]=ra[i][j]+cc[i][j-1]+cc[i-1][j]-cc[i-1][j-1];//计算前缀和
		}
	}
	cout<<dfs(1,1,n,m);
	return 0;
}
```
这样不用 O2 就可以过了！

[评测记录](https://www.luogu.com.cn/record/84932559)
## 拓展： ##
不会吧不会吧，不会还有人不知道二维前缀和怎么算吧！

核心代码： $s_{i.j}=s_{i-1,j}+s_{i,j-1}-s_{i-1,j-1}+a_{i,j}$

其中，$s$ 表示前缀和数组，$k$ 表示原数组。

我们可以用一个图形来理解一下：
![二维前缀和](https://cdn.luogu.com.cn/upload/image_hosting/gt5yiert.png)
整个面积就是 $s_{i,j}$，$s_{i-1,j} $ 相当于 $a+b$，$s_{i,j-1}$ 相当于 $a+c$，$k_{i,j}$ 相当于 $d$，$s_{i-1,j-1}$相当于$a$。

很显然：

$$
\begin{aligned}
  s_{i,j} &=a+b+c+d \\
  &=(a+b)+(a+c)-a+d \\
  &=s_{i-1,j}+s_{i,j-1}-s_{i-1,j-1}+k_{i,j}    
\end{aligned}

$$

当然，这不是严谨的推论，图也不标准，仅供参考。

---

## 作者：Createsj (赞：4)

这才发现题解页面 $\LaTeX$ 貌似不支持在 `$$` 多行书写，于是都改好，并在讨论区里测试过了，很惭愧，麻烦管理员再审核一遍，抱歉。

[更好的阅读体验？~~不存在的！~~](https://createsj.gitee.io/post/solution-p4850/)

------------

既然大家都在用记忆化搜索，那我就来个 `DP` 题解吧。~~有了 `O2` 谁还会用 `DP` ？！~~

状态转移方程很容易推出来。设问题给出的矩阵为 $\textbf A$，其有一子矩阵，左上角坐标为 $(x_1,y_1)$ ，右下角坐标为 $(x_2,y_2)$ ，那么当只考虑这个子矩阵时，最优解为将该子矩阵切开后的两个矩阵的最优解的最小值与该子矩阵的各元素之和，即

$f_{x_1,y_1,x_2,y_2}=min_{x_1,y_1,x_2,y_2}+\sum\limits_{i=x_1}{x_2}\sum\limits_{j=y_1}^{y_2}\textbf A(i,j).$

这个很容易用记忆化搜索实现，但应如何 `DP` 呢？

容易想到，我们应该枚举每个行数和列数不都为 $1$ 的子矩阵，并保证该子矩阵的任意子矩阵都已得出最优解。为了方便实现，我们设一子矩阵左上角坐标为 $(i,j)$ ，有 $k$ 行 $l$ 列，那么当只考虑这个子矩阵时，最优解为

$f_{i,j,k,l}=min_{i,j,k,l}+\sum\limits_{x=1}^k\sum\limits_{y=1}^l\textbf A(x+i,y+j).$

这个状态转移方程与上面的等价，但能方便我们用 `DP` 实现。

至于求子矩阵各元素之和，我们可以利用前缀和的思想，用 $sum_{i,j}$ 表示左上角坐标为 $(1,1)$ ，右下角坐标为 $(i,j)$ 的子矩阵各元素之和，那么左上角坐标为 $(i,j)$ 的 $k$ 行 $l$ 列的子矩阵各元素之和为

$\sum\limits_{x=1}^k\sum\limits_{y=1}^l\textbf A(x+i,y+j)=sum_{i+k-1,j+l-1}-sum_{i+k-1,j-1}-sum_{i-1,j+l-1}+sum_{i-1,j-1}.$

为了消去 $-1$，我们设一子矩阵左上角坐标为 $(i+1,j+1)$ ，有 $k$ 行 $l$ 列，那么当只考虑这个子矩阵时，最优解为 $f_{i,j,k,l}$ 。

核心代码如下：

```cpp
// i,j,k,l 的意义已经说明
for(register int i,j,k=1,l,c,xs,ys,min,t;k<=n;++k)
    for(l=1;l<=m;++l)
        if(k!=1 || l!=1)
            for(i=0,xs=n-k;i<=xs;++i)// xs 是为了限制 i，减少运算次数
                for(j=0,ys=m-l;j<=ys;++j)//ys 同理
                {
                    // min 表示将该子矩阵切开后的两个矩阵的最优解的最小值
                    min=0x7fffffff;
                    // 横着切
                    for(c=1;c<k;++c)
                    {
                        t=f[i][j][c][l]+f[i+c][j][k-c][l];
                        if(t<min)
                            min=t;
                    }
                    // 竖着切
                    for(c=1;c<l;++c)
                    {
                        t=f[i][j][k][c]+f[i][j+c][k][l-c];
                        if(t<min)
                            min=t;
                    }
                    // 状态转移方程
                    f[i][j][k][l]=min+sum[i+k][j+l]-sum[i+k][j]-sum[i][j+l]+sum[i][j];
                }
```

不用开 `O2` 就可以过，[评测记录](https://www.luogu.com.cn/record/31176754)证明一切。

---

## 作者：Konnyaku_ljc (赞：4)

感谢luogo给了我这次吸氧的机会  
刚看到这题时，看到紫题！吓了一跳。然后看了看DP？不像呀。。。最后默默点开了算法标签——
#### 记忆化搜索！！！  
本题思路不难想  
对每块巧克力（矩阵），我们计算切其每一个子巧克力（矩阵）的葡萄干,层层递归，直到这个巧克力（矩阵）的大小为1时，我们返回0（不需要切了）；否则，返回现在的葡萄干数量的最小值与此块巧克力的葡萄干数量的和。所以，我们需要前缀和  
```cpp
cin >> n >> m;
for ( int i = 1; i <= n; i++ )
	    for ( int j = 1; j <= m; j++ )
		    cin >> a[i][j] , a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
```
然后开始搜索  
```cpp
int dfs (int x1,int y1,int x2,int y2)//左上坐标与右下坐标
{
	if (b[x1][y1][x2][y2]) return dp[x1][y1][x2][y2];
    //此矩阵已算过直接返回最小值
	b[x1][y1][x2][y2] = 1;//此矩阵算过了
	if ( x1 == x2 && y1 == y2 ) { dp[x1][y1][x2][y2] = 0;return 0;}
    //面积为1是不需要切，就什么都不给
    for ( int i = x1; i < x2; i++ ) 
        dp[x1][y1][x2][y2] = min( dfs(x1,y1,i,y2) + dfs(i+1,y1,x2,y2) , dp[x1][y1][x2][y2]);
    //要不，让他横着切切看，将其切成两半dfs
    for ( int i = y1; i < y2; i++ ) 
        dp[x1][y1][x2][y2] = min( dfs(x1,y1,x2,i) + dfs(x1,i+1,x2,y2) , dp[x1][y1][x2][y2]);
    //要么，让他竖着切切看，将其切成两半dfs
	dp[x1][y1][x2][y2] += a[x2][y2] + a[x1-1][y1-1] - a[x1-1][y2] - a[x2][y1-1];
    //加上此块的葡萄干数
    return dp[x1][y1][x2][y2];//返回最小值
}
```
拼凑一下上面的代码，发现T了两个点。。。  
~~神说：“写快读！”~~  emmm~ 还是T两个点 ~~我再也不写快读了~~  
~~神说：“吸氧气！”~~ 万能的洛谷呀，我竟然AC了！
附完整代码（码风较丑，不喜勿喷）
```cpp
// luogu-judger-enable-o2
//上边那句一定不能少！！！
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
int n,m,a[52][52],dp[52][52][52][52];
bool b[52][52][52][52];
int dfs (int x1,int y1,int x2,int y2)
{
	if (b[x1][y1][x2][y2]) return dp[x1][y1][x2][y2];
	b[x1][y1][x2][y2] = 1;
	if ( x1 == x2 && y1 == y2 ) { dp[x1][y1][x2][y2] = 0;return 0;}
    for ( int i = x1; i < x2; i++ )
	    dp[x1][y1][x2][y2] = min( dfs(x1,y1,i,y2) + dfs(i+1,y1,x2,y2) , dp[x1][y1][x2][y2]);
    for ( int i = y1; i < y2; i++ )
	    dp[x1][y1][x2][y2] = min( dfs(x1,y1,x2,i) + dfs(x1,i+1,x2,y2) , dp[x1][y1][x2][y2]);
	dp[x1][y1][x2][y2] += a[x2][y2] + a[x1-1][y1-1] - a[x1-1][y2] - a[x2][y1-1];
    return dp[x1][y1][x2][y2];
}
int main()
{
	cin >> n >> m;
	for ( int i = 1; i <= n; i++ )
	    for ( int j = 1; j <= m; j++ )
		    cin >> a[i][j] , a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
	memset (dp,0x3f,sizeof(dp));
	cout << dfs(1,1,n,m);
	return 0;
}
```
谢谢观赏~qwq

---

## 作者：淸梣ling (赞：2)

# 题目位置
注：时限已改为5s

[传送门](https://www.luogu.com.cn/problem/P4850)

# 分析
这道题与[石子合并](https://www.luogu.com.cn/problem/P1880)有几分相似，只是将一维变为二维，由环变成了面，~~所以可以用贪心~~。

但是！！我们都知道~~贪心有时并不灵~~，所以此时自然要看一眼数据啦。$1 \le n,m \le 50$ 很显然，这么小的数再加几个指数之类的也没什么事，所以直接暴力！


------------

### 24pts
暴力的话思路还是很好找的，就是枚举每一刀可能切的位置，如果不需要再切割则返回 $0$，然后取最小值 ~~（妈妈我 AC 啦）~~

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int p[60][60];

int dfs(int a,int b,int c,int d)
{
	if(c==a&&d==b)return 0;//不需要分割

	int i,j,num=2147483647;

	for(i=a;i<c;i++)//横着切
	num=min(num,dfs(a,b,i,d)+dfs(i+1,b,c,d));
	for(i=b;i<d;i++)//竖着切
	num=min(num,dfs(a,b,c,i)+dfs(a,i+1,c,d));

	for(i=a;i<=c;i++)
	for(j=b;j<=d;j++)
	num+=p[i][j];//当前巧克力切割的费用

	return num;
}
int main()
{
	int n,m;
	int i,j;

	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)
	scanf("%d",&p[i][j]);
    
	cout<<dfs(1,1,n,m);
	return 0;
}
```


------------
### 76pts
$24$分的我们深知出题人不会让我们用最简单的暴力过去，那么我们只能在继续优化。

仔细观察一下，既然 $dfs$ 是列举所有可能，那么是不是有一些较小的巧克力是重复算的呢？答案是肯定的，那么对待这些，**我们当然是用一个数组进行存储**，这样会少去大量的冗余计算。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int f[60][60][60][60];//记忆化搜索
int p[60][60];

int dfs(int a,int b,int c,int d)
{
	if(f[a][b][c][d])//已经搜索过则返回已知
    return f[a][b][c][d];
	
    if(c==a&&d==b)return 0;

	int i,j,num=2147483647;

	for(i=a;i<c;i++)
	num=min(num,dfs(a,b,i,d)+dfs(i+1,b,c,d));
	for(i=b;i<d;i++)
	num=min(num,dfs(a,b,c,i)+dfs(a,i+1,c,d));

	for(i=a;i<=c;i++)
	for(j=b;j<=d;j++)
	num+=p[i][j];

	return f[a][b][c][d]=num;//记录当前巧克力的最优解
}
int main()
{
	//此处和上面一样
}
```


------------
### 100pts
当我们看到仍有两个点 $T$ 了时，~~开O2！~~

这时还有一个点没有注意到，就是每层搜索时都对当前的巧克力进行**求和**。求和？那我们是不是提前把数组的**二维前缀和**算出来，然后 $O(1)$ 使用，是不是就可以 $A$ 掉了呢？

以下为正解：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int f[60][60][60][60];//记忆化搜索
int p[60][60];
int s[60][60];//前缀和求和

int dfs(int a,int b,int c,int d)
{
	int i,num=2147483647;

	if(f[a][b][c][d])return f[a][b][c][d];
	if(c==a&&d==b)return 0;

	for(i=a;i<c;i++)
	num=min(num,dfs(a,b,i,d)+dfs(i+1,b,c,d));
	for(i=b;i<d;i++)
	num=min(num,dfs(a,b,c,i)+dfs(a,i+1,c,d));

	f[a][b][c][d]=num+s[c][d]-s[a-1][d]-s[c][b-1]+s[a-1][b-1];

	return f[a][b][c][d];
}
int main()
{
	int n,m;
	int i,j;

	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)
	{
		scanf("%d",&p[i][j]);
		s[i][j]=p[i][j]+s[i][j-1]+s[i-1][j]-s[i-1][j-1];//提前计算
	}
	
	cout<<dfs(1,1,n,m);
	return 0;
}
```
求通过~~~

---

## 作者：Lyrella (赞：1)

# 题意

将一个 $n\times m$ 的方格切割成若干个 $1\times1$ 的小方格，每次只能横着或竖着切，且代价为两个子方格的数字和，求最小代价。

# 思路

看一眼数据范围 $n, m\le50$，时间限制有足足五秒，可以想到直接 $O(n^5)$ **记忆化搜索**。

定义 ```f[x1][x2][y1][y2]``` 表示左上角为 $(x1, y1)$、右下角为 $(x2, y2)$ 的矩阵切割后的最小代价，然后**暴力枚举**横着切、竖着切的情况即可。

# 代码

```cpp
/*
 * @Author: Nekopedia 
 * @Date: 2023-08-11 12:34:53 
 * @Last Modified by: Nekopedia
 * @Last Modified time: 2023-08-11 12:46:43
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll rd(){
   ll x = 0, f = 1; char c = getchar();
   while(! isdigit(c)){if(c == '-')f = - f; c = getchar();}
   while(isdigit(c)){x = (x << 3) + (x << 1) + (c ^ 48); c = getchar();}
   return x * f;
}

const int N = 55;
int n, m, a[N][N], vis[N][N][N][N], f[N][N][N][N];

int dfs(int x1, int x2, int y1, int y2){
    if(vis[x1][x2][y1][y2])return f[x1][x2][y1][y2];
    vis[x1][x2][y1][y2] = 1;
    if(x1 == x2 and y1 == y2)return f[x1][x2][y1][y2] = 0;
    int res = f[x1][x2][y1][y2]; f[x1][x2][y1][y2] = a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
    for(int i = x1; i < x2; ++i)res = min(res, dfs(x1, i, y1, y2) + dfs(i + 1, x2, y1, y2));
    for(int i = y1; i < y2; ++i)res = min(res, dfs(x1, x2, y1, i) + dfs(x1, x2, i + 1, y2));
    return f[x1][x2][y1][y2] += res;
}

signed main(){
    //freopen(,stdin);
    //freopen(,stdout);
    n = rd(), m = rd();
    memset(f, 0x3f, sizeof f);
    for(int i = 1; i <= n; ++i)for(int j = 1; j <= m; ++j)a[i][j] = rd() + a[i - 1][j] + a[i][j - 1] - a[i  -1][j - 1];
    printf("%d", dfs(1, n, 1, m));
    return 0;
}
```

---

## 作者：asd369 (赞：1)

## [也许更好的阅读体验](https://www.cnblogs.com/asd369-blog/p/p4850-raisins.html)
## 题目链接

[题目传送门](https://www.luogu.org/problem/P4850)

## 题目解析

这里介绍一种~~不用开$O2$~~的方法

这题的dp方程很好推：  

$f[x_1][y_1][x_2][y_2]=min(f[x_1][y_1][x_2][y_2],f[x_1][y_1][i][y_2]+f[i+1][y_1][x_2][y_2]+s[x_1][y_1][x_2][y_2])$

以及：  

$f[x_1][y_1][x_2][y_2]=min(f[x_1][y_1][x_2][y_2],f[x_1][y_1][x_2][i]+f[x_1][i+1][x_2][y_2]+s[x_1][y_1][x_2][y_2])$ 

具体的数组含义看代码就懂了

然后打个记忆化搜索上去——$TLE$了
  
我们发现四维数组的访问很慢，所以可以用类似哈希的方法将四维转化为一维

然后就卡~~cao~~过去了

## 代码
```cpp
#include <stdio.h>

using namespace std;

template <typename T> inline void Read(T &t)
{
    int c=getchar(),f=0;
    for (;c<'0'||c>'9';c=getchar()) f=(c=='-');
    for (t=0;c>='0'&&c<='9';c=getchar()) t=(t<<3)+(t<<1)+(c^48);
    if (f) t=-t;
}

const int N=55,t[]={1,55,3025,166375,9150625};
int n,m,s[N][N];
int dp[N*N*N*N];

inline int min(int a, int b) {return a<b?a:b;}

int dfs(int x, int y, int _x, int _y)
{
	int a=x*t[3]+y*t[2]+_x*t[1]+_y*t[0];
	if (dp[a]) return dp[a];
	if (x==_x&&y==_y) return 0;
	dp[a]=0x7fffffff;
	for (int i=x;i<_x;i++)
		dp[a]=min(dp[a],dfs(x,y,i,_y)+dfs(i+1,y,_x,_y));
	for (int i=y;i<_y;i++)
		dp[a]=min(dp[a],dfs(x,y,_x,i)+dfs(x,i+1,_x,_y));
	return dp[a]+=s[_x][_y]-s[x-1][_y]-s[_x][y-1]+s[x-1][y-1];
} 

int main()
{
	Read(n),Read(m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			Read(s[i][j]),s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	printf("%d\n",dfs(1,1,n,m));
    return 0;   
} 
```

---

## 作者：封禁用户 (赞：0)

看到这是个最优化的题，且数据范围很小，可以用搜索。

并且，对于一个相同的子矩阵，可能会搜到多次，由于它的最优值是一定的，所以可以用记忆化优化一下。

总结出搜索思路：

1. 枚举是竖着切和横着切，以及切的位置。

2. 继续递归，计算出切割后两个更小的子矩阵的价值，并求出所有切割方案中的最优值。

3. 当搜索到的子矩阵大小为 $1$，直接返回。

4. 当前子矩阵搜过，返回得出的最优值。

5. 用最优值再加上当前子矩阵本身的和，即为该子矩阵的最优值。

对于子矩阵的和，可以用二维前缀和计算，优化时间。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[51][51];//读入的矩阵 
int ans[51][51][51][51];//记忆化，记录最优值 
bool f[51][51][51][51];//记忆化，记录搜没搜过 
inline int dfs(int lx,int ly,int rx,int ry)
{
	if(f[lx][ly][rx][ry]) return ans[lx][ly][rx][ry];//搜过直接返回最优值 
	f[lx][ly][rx][ry]=1;//否则先标记一下 
	if(lx==rx&&ly==ry)//大小为1，不需再切，直接返回 
	{
		ans[lx][ly][rx][ry]=0;
		return 0;
	}
	for(int i=lx;i<rx;i++)//横着切，以及切的位置 
	{
		ans[lx][ly][rx][ry]=min(ans[lx][ly][rx][ry],dfs(i+1,ly,rx,ry)+dfs(lx,ly,i,ry));	//递归算值，并维护最优值 
	} 
	for(int i=ly;i<ry;i++)//竖着切，以及切的位置 
	{
		ans[lx][ly][rx][ry]=min(ans[lx][ly][rx][ry],dfs(lx,i+1,rx,ry)+dfs(lx,ly,rx,i));//同上 
	}
	ans[lx][ly][rx][ry]+=a[rx][ry]+a[lx-1][ly-1]-a[lx-1][ry]-a[rx][ly-1];//加上子矩阵自身，这里用了二维前缀和优化 
	return ans[lx][ly][rx][ry];//返回 
}
int main()
{
	cin>>n>>m;
	memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];//二维前缀和预处理 
		}	
	}
	printf("%d\n",dfs(1,1,n,m));	
	return 0;
}

```


---

## 作者：zhangxiao666 (赞：0)

### 前言:
IOI 还出这样~~水~~的纯记忆化搜索题？还是 T4？真令人难以置信。
### 题意：
[题目传送门](https://www.luogu.com.cn/problem/P4850)

一个 $N\times M$ 的矩阵，对于任意一个子矩阵，只能横着或竖着分割，并且分割一次的价值为改子矩阵的元素之和，现要将该矩阵分割成 $1\times 1$ 的方格，求最小的分割总价值之和。
### 思路：
看到这是个最优化的题，且数据范围很小，可以用搜索。

并且，对于一个相同的子矩阵，可能会搜到多次，由于它的最优值是一定的，所以可以用记忆化优化一下。

总结出搜索思路：

1. 枚举是竖着切和横着切，以及切的位置。

1. 继续递归，计算出切割后两个更小的子矩阵的价值，并求出所有切割方案中的最优值。

1. 当搜索到的子矩阵大小为 $1$，直接返回。

1. 当前子矩阵搜过，返回得出的最优值。

1. 用最优值再加上当前子矩阵本身的和，即为该子矩阵的最优值。

对于子矩阵的和，可以用二维前缀和计算，优化时间。不知道二维前缀和的同学可以参考我的[这篇博客](https://www.luogu.com.cn/blog/zhangxiao666/er-wei-qian-zhui-hu)。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[51][51];//读入的矩阵 
int ans[51][51][51][51];//记忆化，记录最优值 
bool f[51][51][51][51];//记忆化，记录搜没搜过 
inline int dfs(int lx,int ly,int rx,int ry)
{
	if(f[lx][ly][rx][ry]) return ans[lx][ly][rx][ry];//搜过直接返回最优值 
	f[lx][ly][rx][ry]=1;//否则先标记一下 
	if(lx==rx&&ly==ry)//大小为1，不需再切，直接返回 
	{
		ans[lx][ly][rx][ry]=0;
		return 0;
	}
	for(int i=lx;i<rx;i++)//横着切，以及切的位置 
	{
		ans[lx][ly][rx][ry]=min(ans[lx][ly][rx][ry],dfs(i+1,ly,rx,ry)+dfs(lx,ly,i,ry));	//递归算值，并维护最优值 
	} 
	for(int i=ly;i<ry;i++)//竖着切，以及切的位置 
	{
		ans[lx][ly][rx][ry]=min(ans[lx][ly][rx][ry],dfs(lx,i+1,rx,ry)+dfs(lx,ly,rx,i));//同上 
	}
	ans[lx][ly][rx][ry]+=a[rx][ry]+a[lx-1][ly-1]-a[lx-1][ry]-a[rx][ly-1];//加上子矩阵自身，这里用了二维前缀和优化 
	return ans[lx][ly][rx][ry];//返回 
}
int main()
{
	cin>>n>>m;
	memset(ans,0x3f,sizeof(ans));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];//二维前缀和预处理 
		}	
	}
	printf("%d\n",dfs(1,1,n,m));	
	return 0;
}
```

写题解不易，点个赞呗。

---

## 作者：ryf_loser (赞：0)

此题用记忆化搜索极为简单。

但是此题将动态规划和记忆化搜索完美的结合在了一起，我们既需要推状态转移方程，也需要在搜索中用到记忆化。

此题还有一个细节就是要用前缀和进行提速，否则会~~直接去世~~。

怎么推到方程呢？我们必须要明确我们怎样切才能使在此区域内所耗费的最小，取到最小值。而此便捷区域即为    $x,y,l,h$，其中 $x,y$ 即是相当于此区域左上方的坐标。$l,h$ 即是相当于此区域右上方的坐标。

此时方程呼之欲出：

$dp_{x,y,l,h}\leftarrow\min(dp_{i+1,y,l,h}+dp_{x,y,i,h},dp_{x,y,l,h})$

$dp_{x,y,l,h}\leftarrow\min(dp_{x,i+1,l,h}+dp_{x,y,l,i},dp_{x,y,l,h})$

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,a[51][51],dp[51][51][51][51];
int dfs(int x,int y,int l,int h){
	if (dp[x][y][l][h]!=-1)return dp[x][y][l][h];//如果有结果了，直接返回。
	if (x==l&&y==h)return dp[x][y][l][h]=0;..边界条件
	dp[x][y][l][h]=2147483647;
	for (int i=x;i<l;i++)dp[x][y][l][h]=min(dfs(i+1,y,l,h)+dfs(x,y,i,h),dp[x][y][l][h]);//状态转移方程。
	for (int i=y;i<h;i++)dp[x][y][l][h]=min(dfs(x,i+1,l,h)+dfs(x,y,l,i),dp[x][y][l][h]);//状态转移方程。
	dp[x][y][l][h]+=a[x-1][y-1]+a[l][h]-a[x-1][h]-a[l][y-1];//将搜到的最小值与此区域的之和相加。
	return dp[x][y][l][h];
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++){
			scanf ("%d",&a[i][j]);
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];//前缀和优化。
		}
	memset(dp,-1,sizeof(dp));//初始化为 -1，方便后面进行判断。
	printf ("%d",dfs(1,1,n,m));//搜索。
	return 0;
}
```
评测记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/fxlx3a4p.png)

---

## 作者：WZKQWQ (赞：0)

# 感谢洛谷给我这个水题机会

紫题？不存在的。

记忆化搜索+一发吸氧水过。

窝的第二篇题解

很容易看出f[x][y][x1][y1] = min(f[x][y][x1][y1],

这一块的分数 + 最小的方案);

这一块的分数用前缀和O(1)得出。

答案是f[1][1][n][m];

那我们重点看怎么得出最小的方案。

已知我们可以横着切(x1 - x)刀，

竖着切(y1 - y)刀。

那么最小的方案就是这些刀切完后的最小值。

```cpp
ll tmp = 0;
    for (int i = x; i < x1; i++)
    {
        tmp = 0;
        tmp += dfs(x, y, i, y1);
        tmp += dfs(i + 1, y, x1, y1);
        tmp += num[x1][y1] - num[x1][y - 1] - num[x - 1][y1] + num[x - 1][y - 1];
        f[x][y][x1][y1] = min(f[x][y][x1][y1], tmp);
    }
    for (int i = y; i < y1; i++)
    {
        tmp = 0;
        tmp += dfs(x, y, x1, i);
        tmp += dfs(x, i + 1, x1, y1);
        tmp += num[x1][y1] - num[x1][y - 1] - num[x - 1][y1] + num[x - 1][y - 1];
        f[x][y][x1][y1] = min(f[x][y][x1][y1], tmp);
    }
```

上AC代码完结撒花:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 55;
ll f[N][N][N][N], num[N][N];//不开long long见祖宗
ll dfs(int x, int y, int x1, int y1)
{
    if (x == x1 && y == y1)
        return 0;//一小块就不用切了
    if (f[x][y][x1][y1] != 1e9)
        return f[x][y][x1][y1];//重要剪枝
    ll tmp = 0;
    for (int i = x; i < x1; i++)
    {
        tmp = 0;
        tmp += dfs(x, y, i, y1);
        tmp += dfs(i + 1, y, x1, y1);
        tmp += num[x1][y1] - num[x1][y - 1] - num[x - 1][y1] + num[x - 1][y - 1];
        f[x][y][x1][y1] = min(f[x][y][x1][y1], tmp);
    }
    for (int i = y; i < y1; i++)
    {
        tmp = 0;
        tmp += dfs(x, y, x1, i);
        tmp += dfs(x, i + 1, x1, y1);
        tmp += num[x1][y1] - num[x1][y - 1] - num[x - 1][y1] + num[x - 1][y - 1];
        f[x][y][x1][y1] = min(f[x][y][x1][y1], tmp);
    }
    //重要部分
    return f[x][y][x1][y1];
}
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, o; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &o);
            num[i][j] = num[i][j - 1] + num[i - 1][j] - num[i - 1][j - 1] + o;//维护前缀和
        }
    for (int i = 1, o; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int i1 = 1, o; i1 <= n; i1++)
                for (int j1 = 1; j1 <= m; j1++)
                    f[i][j][i1][j1] = 1e9;//不初始化见祖宗
    cout << dfs(1, 1, n, m);
    return 0;
}
```


最后一句：

## 我爱记搜

---

