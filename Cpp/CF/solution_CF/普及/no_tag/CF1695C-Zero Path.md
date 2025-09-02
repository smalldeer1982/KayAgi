# Zero Path

## 题目描述

You are given a grid with $ n $ rows and $ m $ columns. We denote the square on the $ i $ -th ( $ 1\le i\le n $ ) row and $ j $ -th ( $ 1\le j\le m $ ) column by $ (i, j) $ and the number there by $ a_{ij} $ . All numbers are equal to $ 1 $ or to $ -1 $ .

You start from the square $ (1, 1) $ and can move one square down or one square to the right at a time. In the end, you want to end up at the square $ (n, m) $ .

Is it possible to move in such a way so that the sum of the values written in all the visited cells (including $ a_{11} $ and $ a_{nm} $ ) is $ 0 $ ?

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1695C/8f2d98d121e7e351eaa9a88e08080da6d06835b5.png)

## 说明/提示

One possible path for the fourth test case is given in the picture in the statement.

## 样例 #1

### 输入

```
5
1 1
1
1 2
1 -1
1 4
1 -1 1 -1
3 4
1 -1 -1 -1
-1 1 1 -1
1 1 1 -1
3 4
1 -1 1 1
-1 1 -1 1
1 -1 1 1```

### 输出

```
NO
YES
YES
YES
NO```

# 题解

## 作者：hongzy (赞：16)

感觉题出的很小清新，符合我的审美，所以来写一个题解。

用 `bitset` 过题，比赛时节约思考时间写就算了，考后补题写这个简直是亵渎。

首先我们给出结论，我们要找一条权值和为 $0$ 的路径，只需找到权值和最小和最大的路径对应权值，记为 $l,r$，那么答案是 `YES` 当且仅当 $l\leq 0 \leq r$。

下面是简单的证明。

首先如果路径长度 $n+m-1$ 是奇数，答案是 `NO`。

否则我们用 `R` 和 `D` 来记录一条路径。注意路径长度是 $n+m-2$，并且 `R` 的数量是固定的 $n-1$。那么权值最小的路径和最大的路径可以用序列 $p_1,p_2$ 表示。因为元素集相同，很明显我们可以从 $p_1$ 开始，通过不断交换两个相邻的 `RD` 来得到 $p_2$。我们思考一下交换 `RD` 意味着什么，就是先右后下和先下后右的区别。那么每次交换路径权值可能 $0,+2,-2$。既然最后路径权值从 $l$ 变成了 $r$ 并且我们限制了奇偶性，那么一定中间经历了 $l,l+2,\cdots,0,\cdots,r-2,r$ 这样的过程。于是得证。

---

## 作者：Blunt_Feeling (赞：6)

## CF1695C Zero Path 题解

一道简单又有意思的取数问题。

因为只能向右或向下走，所以共向下 $n-1$ 次，向右 $m-1$ 次，故一共经过 $n+m-1$ 个方格。取数和为 $0$，所以 $n+m-1$ 须为偶数，否则直接输出`NO`。

为了使取数和为 $0$，$-1$ 和 $1$ 的个数都为 $\frac{n+m-1}{2}$。接下来考虑如何刚好取到 $\frac{n+m-1}{2}$ 个 $1$。

运用 DP 的思想，求出从起点到终点能取到的最小的 $1$ 的数量为 $Min$，与能取到的最大的 $1$ 的数量为 $Max$（状态转移很简单，详见代码）。如果 $\frac{n+m-1}{2}$ 夹在这两个值之间（等号可以取到），即可证明有解。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1695C/8f2d98d121e7e351eaa9a88e08080da6d06835b5.png)

以样例为例：如图，因为格子内不是 $-1$ 就是 $1$，找出 $1$ 最多的路线共有 $4$ 个 $1$，最少的只有 $1$ 个 $1$。我们想让 $1$ 有 $3$ 个，每次更改一次转角处的走向，即可把 $1$ 的个数减少或增加 $1$。这样 $2$ 次就能找到红色这条路。

### Code

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int maxn=1024;
int T,n,m,a[maxn][maxn],f[maxn][maxn],g[maxn][maxn];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		For(i,1,n)
			For(j,1,m)
				cin>>a[i][j];
		if((n+m-1)&1) //特判
		{
			puts("NO");
			continue;
		}
		int h=(n+m-1)/2;
		f[1][1]=(a[1][1]==1?1:0);
		For(i,1,n)
			For(j,1,m)
				f[i][j]=max(f[i][j-1],f[i-1][j])+(a[i][j]==1?1:0); //f求最大值
		For(i,2,n) g[i][0]=0x3f3f3f3f;
		For(j,2,m) g[0][j]=0x3f3f3f3f; //因为要取min值，故先初始化
		For(i,1,n)
			For(j,1,m)
				g[i][j]=min(g[i][j-1],g[i-1][j])+(a[i][j]==1?a[i][j]:0); //g求最小值
		if(g[n][m]<=h&&h<=f[n][m]) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：vegetable_king (赞：6)

在[博客](https://yjh965.github.io/post/cf1695c-zero-path/)食用更佳。

提供一个无脑 `bitset` 优化暴力 DP 的做法。

首先如果 $n + m$ 为偶数则无解。

然后可以想到一个朴素的 DP：设 $f_{i, j, k}$ 为是否存在从左上角到 $(i, j)$ 且经过 $k$ 个 $1$ 的路径，转移简单不讲。

这个 DP 的 $k$ 只需要枚举到 $(n + m - 1) / 2$ 的范围，所以时间复杂度为 $O(nm(n + m))$，常数大概为 $1/2$。

然后这个 DP 很明显可以用 `bitset` 优化，时间复杂度变为 $O(\dfrac{nm(n + m)}w)$，$w$ 取 $32$ 或 $64$，我们就得到了一个非常小的常数。

然后呢？然后就[冲过去了](https://codeforces.com/problemset/submission/1695/161091846)。

---

## 作者：tzyt (赞：5)


题目链接[（CF](https://codeforces.com/problemset/problem/1695/C)，[洛谷）](https://www.luogu.com.cn/problem/CF1695C) | 强烈推荐[博客](https://ttzytt.com/2022/06/CF1695C/)中观看。

# 题意
给你一个 $n \times m$ ($1 \le n, m \le 1000$) 的格点图，每个格子的值要么是 $-1$，要么是 $1$，现在问你，是否有一条从 $(1, 1)$ 到 $(n, m)$ 的路径，使得路径上经过的格点的值的和为 $0$。在路径中，只能从 $a_{i, j}$ 移动到 $a_{i + 1, j}$ 或是 $a_{i, j + 1}$（向右或是向下走）。

# 思路
看到这个 ($1 \le n, m \le 1000$) 的数据范围就知道暴搜肯定要寄了（~~别学我~~），所以得想一些别的办法。

首先，如果经过奇数个格子，或者说 $n + m - 1$ 为奇数，那么肯定没有这样的一条路径（经过的 $-1$ 和 $1$ 点没有办法相等）。

直接判断某个格子图是否符合要求太麻烦，我们可以思考，如果有任意一条路径，我们是否能根据这条路径的值（也就是途径的格子的和），来做一些改变，最后让路径的值变为 $0$。

如下图这样就是对路径做了一次改变（改变前后只有一个格子不同）。最后让路径的值产生了变化。
![示意图，来自官方题解](https://espresso.codeforces.com/0302c7c74d2bdaaab831ab4ac207023a337cc00a.png)

在一次改变中，路径的值会产生 $-2 (-1 \rightarrow 1)$, $2 (1 \rightarrow -1)$ 或是 $0 (1 \rightarrow 1 \operatorname{OR} -1 \rightarrow -1)$ 的变化，那么如果我们刚开始的路径值是一个偶数，就可以把这个路径通过这样的改变变为 $0$ ……吗？

显然是不行的，如果整个格点图全是 $-1$ 或是全是 $1$ 就不行，所以我们还得做一些改进。

首先就得确保在这个格点图中不会只有值特别离谱的路径，如果只有值特别离谱的路径，那无论你怎么变，也搞不出值为 $0$ 的路径。

所以我们需要找出值最大的路径，以及值最小的路径。

设值最大的路径的值为 $p_{\max}$，最小的路径的值为 $p_{\min}$。

那么如果:
$$
p_{\min} \le 0 \le p_{\max}
$$

我们就一定可以通过这样的变化把任意一个值为偶数的路径变为值为 $0$ 的路径。

或者可以这样理解，如果符合上面那个条件，那我们就可以逐渐把值最小的路径向值最大的路径变换，在这个过程中，一定有一个路径的值等于 $0$。

至于求这样的格子图的最大和最小路径，就属于是典中典了（用 dp），这里不赘述，如果有不熟悉的可以看[洛谷P1004](https://www.luogu.com.cn/problem/P1004)。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        int a[n + 1][m + 1]; 
        int mx[n + 1][m + 1], mn[n + 1][m + 1];

        //mx[i][j] 的意思是到 i, j 这个点的最大路径的值
        //mn[i][j] 是最小

        memset(a, 0, sizeof(a));
        memset(mx, 0, sizeof(mx));
        memset(mn, 0, sizeof(mn));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                scanf("%d", &a[i][j]);
            }
        }        

        for (int i = 1; i <= n; i++)
            mx[i][1] = mn[i][1] = mx[i - 1][1] + a[i][1];
        //给 dp 设置边界条件，如果在格子图的左边界，显然只能从上面走过来

        for (int j = 1; j <= m; j++)
            mx[1][j] = mn[1][j] = mn[1][j - 1] + a[1][j];
        //如果在格子图的上边界，只能从左边走过来

        for (int i = 2; i <= n; i++) {
            for (int j = 2; j <= m; j++) {
                mx[i][j] = max(mx[i - 1][j], mx[i][j - 1]) + a[i][j];
                mn[i][j] = min(mn[i - 1][j], mn[i][j - 1]) + a[i][j];
                //经典 dp，选择是从左边走过来还是从上面走过来
            }
        }

        if (mx[n][m] & 1 || mn[n][m] > 0 || mx[n][m] < 0) {
            //mx[n][m] & 1 是判断这个路径是否是奇数的
            //当然也可以直接前面判断 n + m - 1，这样还能快一点
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
}
```

---

## 作者：lalaji2010 (赞：1)

# CF1695C Zero Path

## 分析

看这个数据范围，打暴力肯定是不行。

于是我们不得不思考一下这道题的几个特殊性质。

首先我们注意到，每个位置都是 $1$ 或 $-1$，想要最终得到的路径和为 $0$，我们就必须保证从左上角到右下角的路径长度 $n+m-1$ 为偶数。

其次，如果我们有一条路径和大于等于 $0$，另一条小于 $0$，那么由 $2 \mid n+m-1$ 易知两条路径和都被 $2$ 整除。我们就可以将较大的那条路径上经过的一个 $1$ 改为 $-1$，这个操作容易证明是可行的，最终得到一条和为 $0$ 的路径。

求最小路径和以及最大路径和是一道很典的 dp 问题。至此，这个问题就转化为了：

1. 判断路径总长奇偶性，若为奇数则不可行
2. 求给定矩阵从左上角到右下角的最大及最小路径和，若最大值大于等于 $0$，最小值小于等于 $0$，则可行。否则不可行。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[1005][1005],dp[1005][1005],f[1005][1005];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(i==1&&j==1){
					dp[i][j]=a[i][j];
					f[i][j]=a[i][j];
				}else if(i==1){
					dp[i][j]=dp[i][j-1]+a[i][j];
					f[i][j]=f[i][j-1]+a[i][j]; 
				}else if(j==1){
					dp[i][j]=dp[i-1][j]+a[i][j];
					f[i][j]=f[i-1][j]+a[i][j];
				}else{
					dp[i][j]=min(dp[i-1][j],dp[i][j-1])+a[i][j];
					f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];				}
			}
		}
		if(f[n][m]<0||dp[n][m]>0||(n+m-1)%2==1){
			cout<<"NO\n";
		}else{
			cout<<"YES\n";
		}
	}
	return 0;
}
```

---

## 作者：makerlife (赞：1)

[更好的阅读体验](https://blog.makerlife.top/post/solution-CF1695C) | [Problem Link](https://www.luogu.com.cn/problem/CF1695C)

## Explanation

给定一个 $n \times m$ 的格点图，每个格子的值为 $-1$ 或 $1$。问题要求判断是否存在一条从起点 $(1, 1)$ 到终点 $(n, m)$ 的路径，使得路径上经过的格点值的和为 $0$。路径只能向右或向下移动。

## Solution

先上结论。设权值和最大的路径权值为 $f_{max}$，最小权值为 $f_{min}$，则如果满足 $n+m-1$ 是偶数且 $f_{min}\leq 0 \leq f_{max}$，那么问题有解。

简单观察样例会发现路径的长度只能是 $n+m-1$ ，又因为权值只能是 $1$ 或 $-1$，则如果最终有解，$1$ 和 $-1$ 的数量应当相等。所以如果路径长度是奇数，必然要输出 `NO`。

接下来要思考的是路径是怎么从 $f_{min}$ 变化到 $f_{max}$ 的。我们会发现可以通过改变路径转向处的访问位置来变化权值和，一次变化将可能会使权值和改变 $+2,-2,0$。

以样例为例，第一次转向时选择 $(1,1)\to (2,1)$ 与 $(1,1)\to (1,2)$ 不会对结果造成影响。而第二次转向时，选择 $(1,2)\to (2,2)$ 会比 $(1,2)\to (1,3)$ 的权值和多 $2$。

又因为路径的长度限制了为偶数，也就是说 $1$ 和 $-1$ 的数量要么都是偶数，要么都是奇数。这两种情况都会使得权值和为偶数，也就是 $f_{min}$ 和 $f_{max}$ 都是偶数。

那么就可以看看权值和是怎么从最小值变化为最大值的了。因为我们限定了奇偶性和变化规律，所以其变化序列必将是：

$$
f_{min}, f_{min}+2, \dots,0 , \dots, f_{max}-2, f_{max}
$$

一定会在变化过程中经过权值和为 $0$ 的情况，所以结论得证。

## Core Code

```cpp
T=read();
while(T--)
{
	n=read();m=read();
	for(int i=0;i<=n;i++) minn[i][0]=INF,maxn[i][0]=-INF;
	for(int i=0;i<=m;i++) minn[0][i]=INF,maxn[0][i]=-INF;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
		}
	}
	if((n+m-1)%2==1)
	{
		printf("NO\n");
		continue;
	}
	minn[1][1]=maxn[1][1]=a[1][1];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(i!=1 || j!=1)
			{
				maxn[i][j]=max(maxn[i-1][j],maxn[i][j-1])+a[i][j];
				minn[i][j]=min(minn[i-1][j],minn[i][j-1])+a[i][j];
			}
		}
	}
	if(maxn[n][m]>=0 && minn[n][m]<=0) printf("YES\n");
	else printf("NO\n");
}
```


---

## 作者：LeTu_Jun (赞：1)

## 题意

给定一个由 $1$ 和 $-1$ 组成的 $n \times m$ 矩阵，从 $(1,1)$ 到  $(n,m)$，目标是找出一条经过点的权值和为 $0$ 的路线。

## 思路

首先观察题目给的图片。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1695C/8f2d98d121e7e351eaa9a88e08080da6d06835b5.png)

可以发现当某天路线权值和为 $0$ 时，**这条路线一定经过了相同数量的 $1$ 和 $-1$。**

又因为路线总长度为 $n+m-1$，所以可以先判断 $n+m-1$ 的奇偶性，如果为奇数则直接输出 `NO`。

再次观察，发现因为所有格子的权值不是 $1$ 就是 $-1$，所以，比起直接搜索答案路径，**不如搜索 $1$ 最多的路径和 $1$ 最少的路径，也就是 2 条边界路径，再判断 2 条边界之内有没有要求路径即可。**

即：如果满足 $f_{min} > 0 > f_{max}$ ($f$ 为路径权值和)，就有解。

这样问题就变成了求路径权值和的最大路径和最小路径。

什么？搜索？现在不 dp 什么时候 dp 啊。

注意有 $T$ 组数据。

复杂度 $O(Tn^2)$

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,m;
int t;
int a[N][N],l[N][N],r[N][N];
void init ()
{
	for(int i=1;i<=n;i++){
		r[i][1]=l[i][1]=r[i-1][1]+a[i][1];
	}
    for(int j=1;j<=m;j++){
        r[1][j]=l[1][j]=l[1][j-1]+a[1][j];
	}      
	return ; 
}
int main ()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		init();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=2;i<=n;i++){
			for(int j=2;j<=n;j++){
				r[i][j]=max(r[i-1][j],r[i][j-1])+a[i][j];
				l[i][j]=min(l[i-1][j],l[i][j-1])+a[i][j];
			}
		}
		if(r[n][m]%2==1 || l[n][m]>0 || r[n][m]<0) 
		{
        	printf("NO\n");
		}
		else 
		{
    	    printf("YES\n");
    	}
	}
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 思路

数据范围肯定是不能指数级爆搜的，看到这个只能向右和向下，就感觉是动态规划。

首先我们要知道的是因为有 $n$ 行 $m$ 列，所以总共走 $(n-1)+(m-1)$ 次，也就是会经过 $(n+m-1)$ 个格子，因为格子只有 $-1$ 和 $1$ 所以当 $(n+m-1)$ 是奇数的时候显然是无解的。

对于 $n+m-1$ 是偶数的情况，当我们有个路线时，若我们要改变它，这个路线的和会 $+2,-2$ 或者不变，通过变换我们可以最终算出任何一个有可能得到的和，也就是说，只要 $0$ 在可以得到的最大和与最小和之间，就是有解的。

所以说我们只需要通过简单的动态规划计算出路线和的最大值 $maxn$ 和最小值 $minn$ 再判断是否满足 $minn\le 0\le maxn$ 即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1145;
int t,n,m,a[N][N],maxn[N][N],minn[N][N];
signed main()
{
	memset(maxn,-0x3f,sizeof maxn);
	memset(minn,0x3f,sizeof minn);
	maxn[1][0]=maxn[0][1]=minn[0][1]=minn[1][0]=0;
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>a[i][j];
				maxn[i][j]=max(maxn[i-1][j],maxn[i][j-1])+a[i][j];
				minn[i][j]=min(minn[i-1][j],minn[i][j-1])+a[i][j];//取上面的或左面的在加上当前，相信你会动态规划就不多讲了
			}
		}
		if((n+m-1)&1||minn[n][m]>0||maxn[n][m]<0)cout<<"NO\n";
		else cout<<"YES\n";
	}
}
```

---

## 作者：ZLCT (赞：0)

# CF1695C Zero Path
## 题意
给定一个 $n\times m$ 的矩阵，矩阵中每个点都有一个权值 $a_{i,j}\in\{0,1\}$。问是否可以从 $(1,1)$ 点走到 $(n,m)$ 点使得走过路径上的点权值和为 $0$（只能向右或向下走）。
## 题意剖析
首先矩阵路径问题我们十分熟悉，它有以下几个简单性质：
- 走过的路径长度一定是 $n+m-1$（每次横纵坐标有且仅有一个 $+1$）。
- 一个点只能从它左边或上边走到（根据题意要求）。

于是根据第一条性质，我们可以得出如果 $n+m-1\equiv 1\pmod{2}$ 则无解。\
证明：假设走过 $x$ 个 $1$ 点，$y$ 个 $-1$ 点，如果要和为 $0$，那么一定满足 $x-y=0$ 即 $x=y$，所以 $x+y\equiv0\pmod{2}$。\
下面我们继续思考。\
首先假设我们走了一条点权和最大的路径，如果这个点权和小于 $0$，那么一定不存在合法路径（最大点权和都小于 $0$ 了，肯定不存在和为 $0$ 的路径）。\
同理可得如果点权和最小的路径点权和都大于 $0$ 了，那么也肯定不存在合法路径。\
那其他情况就一定存在合法路径吗？一定是的，我们来严谨证明一下。
- 如果最小点权和与最大点权和中有一个为 $0$，那么直接走那条路即可。
- 否则我们暂定路径为最大点权和路径，我们不断使这条路径靠近最小点权和路径，这样如果每次我们只改变一个点的点权，一定能保证路径点权和单调不升且能覆盖最大点权和与最小点权和直接的所有偶数。\
我们先来证明一下为什么可以覆盖所有偶数：\
因为我们每次只改变 $1$ 个点的点权，所以每次要么 $-1$ 变 $+1$，要么 $+1$ 变 $-1$。\
于是每次对于点权和的贡献就是 $+2$ 或 $-2$。\
由于 $n+m-1$ 是偶数，于是最大点权和与最小点权和一定也是偶数，而我们一定能使点权和达到这两点，所以这中间所有偶数也一定可以达到。\
如何保证每次只改变一个点的点权呢？\
这需要我们比较熟悉矩阵路径，我们可以考虑对于路径上的一个转折点处的 $2\times2$ 矩阵 $\begin{bmatrix}a&b\\c&d\end{bmatrix}$。我们假设原来的路径是 $(a,b,d)$，那么我们只需要把路径改为 $(a,c,d)$ 就可以保证每次只改一个点的点权。\
但是现在还有一个疑问：为什么可以保证这样一定可以从最大点权和路径走到最小点权和路径呢？\
这个不需要过多考虑，我们每次只需要按照上面操作先让路径变成从 $(1,1)$ 走到 $(1,m)$ 再走到 $(n,m)$。这个是好操作的，只需要把走 $(a,c,d)$ 的路径变成 $(a,b,d)$ 即可。\
然后我们把这条只有一个转折点的路径变成点权和最小的路径即可。具体的，我们每次找 $(a,b,d)$ 的路径，如果最小权值和路径不经过这个局部路径，就说明一定在这条路径下方，只需要把这条局部路径变成 $(a,c,d)$。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1111][1111],f[1111][1111][2];//0:max,1:min
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>a[i][j];
            f[i][j][0]=0;
            f[i][j][1]=0x3f3f3f3f;
        }
    }
    if((n+m-1)&1){
        cout<<"NO\n";
        return;
    }
    f[1][1][0]=f[1][1][1]=a[1][1];
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(i==1&&j==1)continue;
            if(i==1){
                f[i][j][0]=f[i][j-1][0]+a[i][j];
                f[i][j][1]=f[i][j-1][1]+a[i][j];
            }
            else if(j==1){
                f[i][j][0]=f[i-1][j][0]+a[i][j];
                f[i][j][1]=f[i-1][j][1]+a[i][j];
            }else{
                f[i][j][0]=max(f[i-1][j][0],f[i][j-1][0])+a[i][j];
                f[i][j][1]=min(f[i-1][j][1],f[i][j-1][1])+a[i][j];
            }
        }
    }
    if(f[n][m][0]>0&&f[n][m][1]<0||f[n][m][0]==0||f[n][m][1]==0)cout<<"YES\n";
    else cout<<"NO\n";
    return;
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

