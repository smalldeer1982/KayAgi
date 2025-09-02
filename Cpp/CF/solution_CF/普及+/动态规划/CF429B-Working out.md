# Working out

## 题目描述

夏天要到了，$\texttt{dxbt}$ 和 $\texttt{songke}$ 决定去健身。它们要去的健身房可以被看做一个 $n$ 行 $m$ 列的矩阵。定义 $a_{i,j}$ 为在健身房第 $i$ 行第 $j$ 列运动后消耗的卡路里。

$\texttt{dxbt}$ 从 $\left(1,1\right)$ 出发，要去 $\left(n,m\right)$。并且，他只能从 $\left(i,j\right)$ 走到 $\left(i+1,j\right)$ 或 $\left(i,j+1\right)$；$\texttt{songke}$ 从 $\left(n,1\right)$ 出发，要去 $\left(1,m\right)$。并且，他只能从 $\left(i,j\right)$ 走到 $\left(i-1,j\right)$ 或 $\left(i,j+1\right)$。

由于 $\texttt{dxbt}$ 和 $\texttt{songke}$ 要聚在一起发张自拍，他们必须在健身房的某行某列相遇。由于他们没有好好健身，所以在自拍地点的卡路里消耗不计入总卡路里消耗值。

如果 $\texttt{dxbt}$ 和 $\texttt{songke}$ 中任何一个人完成了健身，则健身结束。你的任务是求出 $\texttt{dxbt}$ 和 $\texttt{songke}$ 可以消耗的最大总卡路里值。

另外，由于他们的健身速度不一定相同，所以可以走过的路线长度也不一定相同。

## 说明/提示

对于样例 $1$，$\texttt{dxbt}$ 可以选择：

$$
\left(1,1\right)\rightarrow\left(1,2\right)\rightarrow\left(2,2\right)\rightarrow\left(3,2\right)\rightarrow\left(3,3\right)
$$

$\texttt{songke}$ 可以选择：

$$
\left(3,1\right)\rightarrow\left(2,1\right)\rightarrow\left(2,2\right)\rightarrow\left(2,3\right)\rightarrow\left(1,3\right)
$$

## 样例 #1

### 输入

```
3 3
100 100 100
100 1 100
100 100 100
```

### 输出

```
800```

# 题解

## 作者：Sakii (赞：12)

# ~~继续水没人发的题解~~
~~裸dp~~

根据题意，只需枚举交点求出交点到四个角的最大值，再减去交点的值即可。

（~~借用cjq大仙的图~~） 

![](https://cdn.luogu.com.cn/upload/pic/32141.png)


显然，设两人在O点相遇，lahub只能从1或者2走到O，如果他从1走到O，那他的路线就是1=>O=>3，则Iahubina就是4=>O=>2，同理可知，若lahub是从2走到O，他的路线一定是2=>O=>4,Iahubina就是1=>O=>3。

所以，易得出最终解为max（A到1最大值+3到C最大值+D到4最大
值+2到B的最大值，A到2最大值+4到C最大
值+D到1最大值+3到B最大值）。

上代码：
```cpp
#include<iostream>
#include <algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int dp1[1010][1010],dp2[1010][1010],dp3[1010][1010],dp4[1010][1010];//用四个dp数组存放最大值	
int n,m;
int a[1010][1010];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
        scanf("%d ",&a[i][j]);
    }
}
memset(dp1,0,sizeof(dp1));
memset(dp2,0,sizeof(dp2));
memset(dp3,0,sizeof(dp3));
memset(dp4,0,sizeof(dp4));
     for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
        dp1[i][j]=a[i][j]+max(dp1[i-1][j],dp1[i][j-1]);}}
    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
        dp2[i][j]=a[i][j]+max(dp2[i+1][j],dp2[i][j+1]);}}
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++){
        dp3[i][j]=a[i][j]+max(dp3[i+1][j],dp3[i][j-1]);}}
    for(int i=1;i<=n;i++){
        for(int j=m;j>=1;j--){
        dp4[i][j]=a[i][j]+max(dp4[i-1][j],dp4[i][j+1]);}}
    int x=0;
    for(int i=2;i<n;i++){
        for(int j=2;j<m;j++)
        {
        x=max(x,dp1[i][j-1]+dp2[i][j+1]+dp3[i+1][j]+dp4[i-1][j]);
        x=max(x,dp1[i-1][j]+dp2[i+1][j]+dp3[i][j-1]+dp4[i][j+1]);}
    }
    printf("%d\n",x);
    return 0;
}
```

---

## 作者：Allanljx (赞：4)

## 思路
设从左上角到右下角的人叫 $A$ ，从左下角到右上角的人叫 $B$ 。根据题意，他们两个会在一个点相遇，而 $A$ 只能往下或往右走， $B$ 只能往上或往右走，所以在穿过照相点时他们一定是走对边。

枚举过程可以拆分成： $A$ 从出发点到照相点，再从照相点到终点，在枚举时要从终点往照相点枚举； $B$ 从出发点到终点，再从照相点到终点，在枚举时从终点往照相点枚举。

所以，先预处理出来从出发点到每个点和从终点到每个点的最大卡路里，然后枚举照相点，注意照相点不可能在边上，如果在边上就会出现两个照相点。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp1[1001][1001],dp2[1001][1001],dp3[1001][1001],dp4[1001][1001];
int n,m;
int a[1001][1001];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        	cin>>a[i][j];
    for(int i=1;i<=n;i++)//A从出发点到照相点 
        for(int j=1;j<=m;j++)
        	dp1[i][j]=a[i][j]+max(dp1[i-1][j],dp1[i][j-1]);
    for(int i=n;i>=1;i--)//A从终点到照相点 
        for(int j=m;j>=1;j--)
        	dp2[i][j]=a[i][j]+max(dp2[i+1][j],dp2[i][j+1]);
    for(int i=n;i>=1;i--)//B从出发点到照相点 
        for(int j=1;j<=m;j++)
        	dp3[i][j]=a[i][j]+max(dp3[i+1][j],dp3[i][j-1]);
    for(int i=1;i<=n;i++)//B从终点到照相点 
        for(int j=m;j>=1;j--)
        	dp4[i][j]=a[i][j]+max(dp4[i-1][j],dp4[i][j+1]);
    int x=0;//x记录总卡路里数 
    for(int i=2;i<n;i++)//枚举照相点
        for(int j=2;j<m;j++)
	        x=max(max(x,dp1[i][j-1]+dp2[i][j+1]+dp3[i+1][j]+dp4[i-1][j]),max(x,dp1[i-1][j]+dp2[i+1][j]+dp3[i][j-1]+dp4[i][j+1]));
    cout<<x<<endl;
    return 0;
}
```


---

## 作者：tuzhewen (赞：4)

~~老师今天上课讲的题，没什么题解就来水一发[doge]~~

### 思路
我们先假定左上角出发的那个人叫$A$，左下角出发的那个人叫$B$。那么，由题意得，他们两个一定会在地图上某一个且**仅**一个点相遇，求他们走的路上所有经过的点的权值和（不包括相遇的点）。

所以说我们先用四个数组分别递推出从左上、右上、左下、右下出发，到所有点的最小距离。预处理好了我们就可以开始~~愉快地~~暴力枚举了！枚举的东西就是$A$,$B$两个人相遇的点$(i,j)$。

~~显然~~，他们有两种走法：第一种是$A$走到$(i-1,j)$，然后从$(i+1,j)$出发，$B$走到$(i,j-1)$从$(i,j+1)$出发； 第二种是$A$走到$(i,j-1)$从$(i,j+1)$出发，$B$走到$(i+1,j)$从$(i-1,j)$出发。（觉得啰嗦？看图！）

第一种（红色为$A$，绿色为$B$，棕色是相遇点）：![1.png](https://i.loli.net/2020/07/29/QGirt1pZF4bsNOD.png)

第二种（红色为$A$，绿色为$B$，棕色是相遇点）：![2.png](https://i.loli.net/2020/07/29/A67LrQqdiYoIaHj.png)

于是就放$ACcode:$
```
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define uF(i,l,r) for(register int i=l;i>=r;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
using namespace std;
const int N=1005;
int n,m;
int mp[N][N];
ll ans,maxn,dp[N][N],dp1[N][N],dp2[N][N],dp3[N][N];
int main() {
	scanf("%d%d",&n,&m);
	F(i,1,n) F(j,1,m) scanf("%d",&mp[i][j]);
	F(i,1,n) F(j,1,m) dp[i][j]=mp[i][j]+max(dp[i][j-1],dp[i-1][j]);//左上
	F(i,1,n) uF(j,m,1) dp1[i][j]=mp[i][j]+max(dp1[i][j+1],dp1[i-1][j]);//右上
	uF(i,n,1) F(j,1,m) dp2[i][j]=mp[i][j]+max(dp2[i+1][j],dp2[i][j-1]);//左下
	uF(i,n,1) uF(j,m,1) dp3[i][j]=mp[i][j]+max(dp3[i+1][j],dp3[i][j+1]);//右下
	F(i,2,n-1) F(j,2,m-1) /*枚举出发点*/maxn=max({maxn,dp[i-1][j]+dp1[i][j+1]+dp2[i][j-1]+dp3[i+1][j],dp[i][j-1]+dp1[i-1][j]+dp2[i+1][j]+dp3[i][j+1]});//计算两种走法
	printf("%lld\n",maxn);
	return 0;
}
```
完结撒花~~

---

## 作者：zhangzehao1 (赞：3)

**题意**

有一个人从左上角走到右下角，有一个人从左下角走到右上角。

两个人的路线只能有一个交点。每一个格子都有自己的值，走过这个路径就能获得对应的值。

规定两个人路线的交点的值两个人都不能获得。

求这两个人获得的值得最大值时多少。

**思路**

一眼 `DP`。

首先考虑只有一个人的情况，推出只有一个人时如何求最大值；

再考虑两个人，但路径不相交时的方法，可以得到式子：

$dp_{i,j}=\max(dp_{i+1,j},dp_{i,j-1})+g_{i,j}$

**AC 代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e3+7;
int n,m;
int ans;
int dp1[M][M],dp2[M][M],dp3[M][M],dp4[M][M];
int g[M][M];
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            cin>>g[i][j];
    //左上
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            dp1[i][j]=max(dp1[i-1][j],dp1[i][j-1])+g[i][j];
    //左下
    for(int i=n;i>=1;--i)
        for(int j=1;j<=m;++j)
            dp2[i][j]=max(dp2[i+1][j],dp2[i][j-1])+g[i][j];
    //右上
    for(int i=1;i<=n;++i)
        for(int j=m;j>=1;--j)
            dp3[i][j]=max(dp3[i-1][j],dp3[i][j+1])+g[i][j];
    //右下
    for(int i=n;i>=1;--i)
        for(int j=m;j>=1;--j)
            dp4[i][j]=max(dp4[i+1][j],dp4[i][j+1])+g[i][j];
    for(int i=2;i<n;++i)
        for(int j=2;j<m;++j)
		{//两种交叉情况，用笔画一画就明白了
            int p1=dp1[i-1][j]+dp4[i+1][j];
            int p2=dp2[i][j-1]+dp3[i][j+1];
            ans=max(ans,p1+p2);
            p1=dp1[i][j-1]+dp4[i][j+1];
            p2=dp2[i+1][j]+dp3[i-1][j];
            ans=max(ans,p1+p2);
        }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：王大神——A001 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF429B)

### 题目分析

根据题目，我们不难发现两人一人要从左下角到右上角，一人从左上角，到右下角，且中间会有一次相遇。

关键在于那一次相遇的地点选择，并且从相遇点到终点和终点跑到相遇点的性质其实相同。所以我们可以考虑，四个人从四个角跑到一个点，左上角的人只能向右或向下；左下角的人只能向右或向上；右上角的人只能向左后向下；右下角的人只能向左或向上。四人跑到这个点路径的权值和最大。

由于我们不知道相遇的地方在哪，所以我们可以通过枚举相遇的点来比对进而找到最终的最大值。

那么如何使起点到这个点路径的权值和最大呢？

通过递推，找出起点到全图上所有点的最大权值。以左上角为例。

```cpp
//左上角递推 
for(int i=1;i<=n;i++)//枚举横坐标
    for(int j=1;j<=m;j++)//枚举纵坐标
        z_s[i][j]=a[i][j]+max(z_s[i-1][j],z_s[i][j-1]);//取最大值
```

### 情况分析

但是，我们可以发现每个角到一点回合时，进入点的方向也可能不同。分为两种情况（由于方向约束）。

```latex
       左上角
 左下角 汇合 右上角
       右下角

       右上角
 左上角 汇合 右下角
       左下角
```
### 注意

- 在计算结果的时候要判一下两种结果最大值。
- 我们的讨论的点上下左右四个都可以达到，所以这个相遇的点不在边线上。
- “另外，他们的健身速度不同，所以可以走过的路线长度也不同。”所以，我们不用特判他们的速度是否合法。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
long long r_r(){//快读 
	long long x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(isdigit(c)){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
const long long o_o=1e3+10;
using namespace std;
long long z_s[o_o][o_o];//左上角
long long y_x[o_o][o_o];//右下角
long long z_x[o_o][o_o];//左下角
long long y_s[o_o][o_o];//右上角
int x,y;
int a[o_o][o_o];
int main(){
    x=r_r(),y=r_r();
    for(int i=1;i<=x;i++)//读入 
        for(int j=1;j<=y;j++)a[i][j]=r_r();
    for(int i=1;i<=x;i++)//左上角递推 
        for(int j=1;j<=y;j++)
        	z_s[i][j]=a[i][j]+max(z_s[i-1][j],z_s[i][j-1]);
    for(int i=x;i>=1;i--)//右下角递推 
        for(int j=y;j>=1;j--)
        	y_x[i][j]=a[i][j]+max(y_x[i+1][j],y_x[i][j+1]);
    for(int i=x;i>=1;i--)//左下角递推 
        for(int j=1;j<=y;j++)
        	z_x[i][j]=a[i][j]+max(z_x[i+1][j],z_x[i][j-1]);
    for(int i=1;i<=x;i++)//右上角递推 
        for(int j=y;j>=1;j--)
        	y_s[i][j]=a[i][j]+max(y_s[i-1][j],y_s[i][j+1]);
    long long m_a=0;
    for(int i=2;i<x;i++)//找最大值 
        for(int j=2;j<y;j++)
        	m_a=max(max(m_a,z_s[i][j-1]+y_x[i][j+1]+z_x[i+1][j]+y_s[i-1][j]),max(m_a,z_s[i-1][j]+y_x[i+1][j]+z_x[i][j-1]+y_s[i][j+1]));        
    printf("%lld\n",m_a);
    return 0;
}
```


---

## 作者：LG_ljc2022 (赞：1)

## 题目描述

给定一个 $N \times M$ 的矩阵，在矩阵中找出两条路径，第一条路径由左上至右下，只能向下或向右走；第二条路径由左下至右上，只能向上或向右走。要求两条路径**有且仅有一个**交点，并且除去交点外两条路径经过的权值和最大。输出最大的权值和。

## 思路

~~这道题其实很简单，但考试时居然卡了……~~

考察内容： $\tt{DP}$

首先分析题目，题目的要求是这两条路径只能有一个交点。那么下意识的，脑海里就想出了这幅图：

   ![图1](https://cdn.luogu.com.cn/upload/image_hosting/n8q2apvl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

图中红点即为相交点，那么很容易发现，能够到达相交点的只有上、下、左、右四个格子。而要求解的蓝色和绿色路径，蓝色路径只可能是从上、左方向进入相交点，绿色路径只可能是从左、下方向进入相交点。

仔细想一想，除了上述图中的情况外，也只有一种情况了（从下方进入相交点）：

![图2](https://cdn.luogu.com.cn/upload/image_hosting/svw020b5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因此，设立 4 个 $\tt{DP}$ 数组，依次预处理左上，右上，左下，右下四个方位。得到四个处理好的 $\tt{DP}$ 数组后，枚举不同的相交点取 $\max$ 就行了。

转移方程：

左上到右下： $dp[i][j] = max(dp[i - 1][j],  dp[i][j - 1]) + a[i][j]$

左下到右上： $dp[i][j] = max(dp[i + 1][j],  dp[i][j - 1]) + a[i][j]$

右上到左下： $dp[i][j] = max(dp[i - 1][j],  dp[i][j + 1]) + a[i][j]$

右下到左上： $dp[i][j] = max(dp[i + 1][j],  dp[i][j + 1]) + a[i][j]$

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n, m, ans, a[1005][1005];
long long dp1[1005][1005], dp2[1005][1005], dp3[1005][1005], dp4[1005][1005];

int main()
{
	
	scanf("%lld%lld", &n, &m);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			scanf("%lld", &a[i][j]);
	
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			dp1[i][j] = max(dp1[i - 1][j], dp1[i][j - 1]) + a[i][j];
	
	for(int i = n;i >= 1;i--)
		for(int j = 1;j <= m;j++)
			dp2[i][j] = max(dp2[i + 1][j], dp2[i][j - 1]) + a[i][j];
	
	for(int i = 1;i <= n;i++)
		for(int j = m;j >= 1;j--)
			dp3[i][j] = max(dp3[i - 1][j], dp3[i][j + 1]) + a[i][j];
	
	for(int i = n;i >= 1;i--)
		for(int j = m;j >= 1;j--)
			dp4[i][j] = max(dp4[i + 1][j], dp4[i][j + 1]) + a[i][j];
	
	for(int i = 2;i < n;i++)
		for(int j = 2;j < m;j++){
			ans = max(dp1[i][j - 1] + dp4[i][j + 1] + dp2[i + 1][j] + dp3[i - 1][j], ans);
			ans = max(dp1[i - 1][j] + dp4[i + 1][j] + dp2[i][j - 1] + dp3[i][j + 1], ans);
		}
	
	printf("%lld", ans);
	
	return 0;
}
```

---

## 作者：Rex01 (赞：0)

## [CF429B 题目传送门](https://www.luogu.com.cn/problem/CF429B)

## 题目大意
给定一个 $n \times m$ 的非负整数矩阵，小明要从矩阵中的某一点出发，到达矩阵的四角顶点，沿途将经过的数取走，求他能够得到的数的总和的最大值。行走规则如下：
- 去矩阵的左上角，每步只能向上或向左走一格；
- 去矩阵的右上角，每步只能向右或向上走一格；
- 去矩阵的左下角，每步只能向左或向下走一格；
- 去矩阵的右下角，每步只能向右或向下走一格。

注意出发点的数不能取。

## 解决思路
注意数据范围：$3 \leq n,m \leq 1000$，因此可以直接打**暴力**，不会超时。分别用四个双重循环枚举前往四个角的情况，每重循环都枚举两种情况，即向上或向左，向右或向上，向左或向下，向右或向下。最后再枚举两种交叉的情况并取最大值即可。

## 代码展示
```cpp
#include <iostream>
using namespace std;

const int N = 1e3 + 10;
int n, m, a[N][N], ans;
int w[N][N], x[N][N];
int y[N][N], z[N][N];

int main()
{
    scanf("%d%d", &n, &m);//建议scanf,更快
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <=m ; j++)
            scanf("%d",&a[i][j]);
    //下面四个两重循环分别枚举去四种方位的情况
    for(int i = 1;i <= n; i++)//左上
        for(int j = 1;j <=m ; j++)
            w[i][j] = max(w[i - 1][j], w[i][j - 1]) + a[i][j];
    for(int i = n; i >= 1; i--)//左下
        for(int j = 1; j <= m; j++)
            x[i][j] = max(x[i + 1][j], x[i][j - 1]) + a[i][j];
    for(int i = 1; i <= n; i++)//右上
        for(int j = m; j >= 1; j--)
            y[i][j] = max(y[i - 1][j], y[i][j + 1]) + a[i][j];
    for(int i = n; i >= 1; i--)//右下
        for(int j = m; j >= 1; j--)
            z[i][j] = max(z[i + 1][j], z[i][j + 1]) + a[i][j];
    for(int i = 2; i < n; i++)
        for(int j = 2; j < m; j++)
		{//两种交叉情况
            int s1 = w[i - 1][j] + z[i + 1][j];
            int s2 = x[i][j - 1] + y[i][j + 1];
            ans = max(ans, s1 + s2);
            s1 = w[i][j - 1] + z[i][j + 1];
            s2 = x[i + 1][j] + y[i - 1][j];
            ans = max(ans, s1 + s2);
			//两次求最大值,确保没有遗漏情况
        }
    printf("%d\n", ans);//建议printf,更快
    return 0;
}
```

---

## 作者：__PJL__ (赞：0)

### 思路

用 4 次 dp 处理出每个点到左上角，右上角，左下角和右下角的最大卡路里数量。最后枚举照相的地点即可。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 1;

long long n, m, ans, a[MAXN][MAXN], dp1[MAXN][MAXN], dp2[MAXN][MAXN], dp3[MAXN][MAXN], dp4[MAXN][MAXN];  

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			dp1[i][j] = max(dp1[i - 1][j], dp1[i][j - 1]) + a[i][j];
		}
	}
	for(int i = n; i >= 1; i--) {
		for(int j = m; j >= 1; j--) {
			dp2[i][j] = max(dp2[i + 1][j], dp2[i][j + 1]) + a[i][j];
		}
	}
	for(int i = n; i >= 1; i--) {
		for(int j = 1; j <= m; j++) {
			dp3[i][j] = max(dp3[i + 1][j], dp3[i][j - 1]) + a[i][j];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = m; j >= 1; j--) {
			dp4[i][j] = max(dp4[i - 1][j], dp4[i][j + 1]) + a[i][j];
		}
	}
	for(int i = 2; i < n; i++) {
		for(int j = 2; j < m; j++) {
			ans = max({ans, dp1[i][j - 1] + dp2[i][j + 1] + dp3[i + 1][j] + dp4[i - 1][j], dp1[i - 1][j] + dp2[i + 1][j] + dp3[i][j - 1] + dp4[i][j + 1]});
		}
	}
	cout << ans;
	return 0;
}
```

---

