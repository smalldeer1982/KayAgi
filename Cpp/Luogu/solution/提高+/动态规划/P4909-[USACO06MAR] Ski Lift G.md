# [USACO06MAR] Ski Lift G

## 题目描述

科罗拉多州的山脉是二维平面上的一条折线。这条折线由 $N$ 个端点，$N−1$ 段线段组成，第 $i$ 个端点的横坐标就是 $i$，纵坐标是 $H_i$，纵坐标代表高度，也可以称为海拔。

罗恩打算为奶牛建造一个滑雪场，为此要在山脉上规划一条缆车线路。缆线也是一条折线，由若干段缆绳组成，起点在山脉的第一个端点，终点在最后一个端点。每段缆绳可以贴着山脉的轮廓，也可以悬浮于空中，跳过山脉上几个海拔低的端点。每段缆绳的水平跨度有限制，不能超过给定的整数 $K$。罗恩需要在每段缆绳的端点处修建支柱，用来固定缆绳。

请帮助他规划一下，选择在山脉的哪些端点上修建，才能使得支柱数量最少？注意，根据题意，起点和终点上是一定要修建的。

## 说明/提示

解释 最优方案是把支柱设在 $1,5,7,9,13$。$5$ 不能直接连 $9$，因为 $9$ 的海拔较高，$1$ 不能直接连 $7$，因为跨度超过了 $K$。

### 数据范围

$2 \le N \le 5000$，$1 \le K \le N − 1$，$0\le H_i \le 10^9$。

## 样例 #1

### 输入

```
13 4
0
1
0
2
4
6
8
6
8
8
9
11
12```

### 输出

```
5```

# 题解

## 作者：AlexZhang (赞：18)

emmm,这道题我们今天集训的一道题。。。

思路:怎么搞呢这道题，对于当前点i,我们往后枚举，求得最优值，很明显是个动态规划，但是题中很明显有着一个限制条件，就是说当i要连向j时，我们这条线不能触碰到山顶，我们设两点间连线斜率为k，那么k[i][j]要保证任何大于i小于j的一个l都要满足k[i][l]<=k[i][j],那么我们再记录一下当前点连出去的最大斜率是多少就行了，剩下的只是dp了，如果上面的不理解那么就看我代码吧

对于斜率的概念如果不懂，可以自行百度
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int f[5005],n,ki,h[5005];
int main(){
	memset(f,0x3f,sizeof(f));//既然是找最少那么我们将答案数组初始化为一个极大值
	scanf("%d%d",&n,&ki);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	f[1]=1;//起点必须得建
	for(int i=1;i<=n;i++){
		double x=-2147483647;//x最大斜率
		for(int j=1;j<=ki&&i+j<=n;j++)
			if((h[i+j]-h[i])*1.0/(j)>=x){//如果斜率大于最大斜率，那么肯定会撞上些什么
				f[i+j]=min(f[i+j],f[i]+1);//dp过程
				x=(h[i+j]-h[i])*1.0/(j);
			}
	}
	printf("%d",f[n]);//输出答案
	return 0;
}

```
最后祝大家NOIP顺利

---

## 作者：MY_Lee (赞：8)

#### 闲聊
考试的时候看到老师出这道题自闭了 $\infty$ 秒。不过后来我看到了这道题，就想写篇题解抒发一下内心感想。

---
#### 题意
记得我第一眼看到这道题的时候：

smg 题目什么意思啊！

我来给和我一样的小伙伴们解释一下。

题目就是说，给定 $N$ 座山的高度，让你在其中尽可能少的选择几座山(**第一个和第 $n$ 个必须选**)，且相邻两座山的距离 $\le K$。使得将他们按输入顺序依次把山顶连线，所有连线不可以撞到其他山脉(**注意可以擦着山顶而过**)。输出最小的选择数量。

比如现在有 $3$ 座山高度分别是：$1,3,2$。那么第一座山就不能直接和第三座山直接相连。因为他们的连线会撞上第二座山。而 $3$ 座高为 $2,5,8$ 的山中，第一座山可以直接连线第三座山。原因画个图就知道：连线擦着第二座山的山顶而过。

---
#### 思路
这不是 dp 还能是甚？！

于是很自然的设 $dp_i$ 表示从第一座山到第 $i$ 座山的最小答案。初始化 $dp_1=1$。

转移方程是个套路：

$$
dp_i=\min(dp_i,dp_j+1)(i\le N,j\le i)
$$

但是我们并不能就这么转移——我们没考虑 $i$ 和 $j$ 能不能连线！

于是想想怎么判断。

---
先上图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lk4h7q7n.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

其中蓝色的线段表示山脉；红色的线段表示不可行的缆线；绿色的线段表示可行的缆线。相信聪明的你一定得到了启发：是否能连线好像跟其他的连线有关！我们要想办法储存每一条可行的连线。

如果你学过数学，那么你应该已经知道这道题的灵魂了：

**斜率。**

不难发现，若连线 $j\rightarrow i$ 的斜率 $\le$ 所有连线 $k\rightarrow i$ 的斜率$(j<k<i)$，那它就是一条可行的连线。

所以，我们可以从 $2\rightarrow n$ 循环 $i$，由于连线 $(i-1)\rightarrow i$ 一定可行，所以先将 $dp_i=dp_{i-1}+1$，新建一个 $slope$ 表示当前最小斜率。也把它初始化为 $h_i-h_{i-1}$(相当于 $\dfrac{h_i-h_{i-1}}{i-(i-1)}$)。由于不能超过 $k$，所以我们从 $(i-2)\rightarrow \min(1,i-k)$ 循环 $j$。若 $j\rightarrow i$ 的斜率，即 $\dfrac{h_i-h_j}{i-j}\le slope$ 则更新 $dp_i$ 和 $slope$。答案就是 $dp_n$。

---
#### 代码

终于解决了这个大难题，快快打开你的 IDE 写起来吧！

下面给出我滴参考代码：

~~(limingye 的同学：limingye 的码风丑死了！)~~
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int mountain,maks,high[5005],dp[5005];
double slope,slp;
inline double calc_slope(int x,int y){
	return 1.0*(high[x]-high[y])/(x-y);
}//算斜率
int main(){
	scanf("%d%d",&mountain,&maks);
	for(register int i=1;i<=mountain;i++){
		scanf("%d",&high[i]);
	}
	dp[1]=1;//初始化
	for(register int i=2;i<=mountain;i++){
		dp[i]=dp[i-1]+1;//初始化 dp[i]
		slope=calc_slope(i,i-1);//初始化 slope
		for(register int j=i-2;j>=max(1,i-maks);j--){
			slp=calc_slope(i,j);//算斜率
			if(slp<=slope){//如果这个斜率比当前斜率还要小则不会撞到其他山
				dp[i]=min(dp[i],dp[j]+1);//更新 dp[i]
				slope=slp;//更新 slope
			}
		}
	}
	printf("%d\n",dp[mountain]);//输出答案
	return 0;
}
```
---
#### 番外
把题解看完了。

不，等等，你没看完！

~~你还没看[我的博客](https://moon-snow.blog.luogu.org/)呢！~~

现在才看完了。

---

## 作者：Mysterious_Cat (赞：2)

### 题目思路：DP
状态：定义$dp_i$为以选择第$i$个山结尾的最小数量  
转移方程：$dp_i=min(dp_i,dp_j+1)(i<=n,i-k<=j<i,sc_{i,j}<=sc_{now})$  
其中$sc$为斜率  
边界：$dp_1=1$  
[斜率](https://baike.baidu.com/item/%E6%96%9C%E7%8E%87/4914111)公式：$sc_{i,j}={\frac{h_i-h_j}{i-j}}$
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int h[5005], dp[5005];

double get_scope(int i, int j)
{
    return 1.0 * (h[i] - h[j]) / (i - j);
}

int main()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> h[i];
    memset(dp, 0x3f, sizeof(dp));
    dp[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        double scope = INT_MAX;
        for(int j = i - 1; j >= max(1, i - k); j--)
        {
            double tmp_scope = get_scope(i, j);
            if(tmp_scope <= scope)
            {
                dp[i] = min(dp[i], dp[j] + 1);
                scope = tmp_scope;
            }
        }
    }
    cout << dp[n];
    
    return 0;
}
```


---

## 作者：Thomasguo666 (赞：2)

## 一道有趣的DP题

首先呢，我们可以想到一个dp式:

$$ f[j]=min_\text{i可以到达j}f[i]+1 $$（这里的“到达”指的是能否连缆绳，下同）

关键点在于，如何计算i是否可以到达j

我们发现，如果$i$可以到达$j$，则对于$i$，$j$任意一点$k$，都有

$$ h[k]-h[i]\leq h[j]-a[i] (\text{h[i]为i点的纵坐标}) $$

所以如果i不能到达j，那么也不能到达j后面

然后代码就很好写了：

```c++
#include <bits/stdc++.h>
#define For(i,x,y) for (int i=x;i<=y;i++)
using namespace std;
typedef double db;
db h[5005];
int f[5005];
int main()
{
	int n,m;
	cin>>n>>m;
	For(i,1,n) cin>>h[i];
	memset(f,0x3f,sizeof(f));
	f[1]=1;
	For(i,1,n)
	{
		db maxx=-1e9;
		For(j,i+1,min(i+m,n))
		{
			db cur=(h[j]-h[i])/(j-i);
			if (cur>=maxx)
			{
				f[j]=min(f[j],f[i]+1);
				maxx=cur;
			}
		}
	}
	cout<<f[n]<<endl;
	return 0;
}
```





---

## 作者：Gavin·Olivia (赞：2)

又一道USACO的经典动规题（←_←来自打了一个月动规的咸鱼的凝视）

这道题是否可以转移状态的判断与线段斜率有关，还没有学过一次函数的，请去找数学老师，这里就不赘述啦~

假设我们在当前拐点i设立了支柱，那么它的前一个支柱一定在max(0,i-k)到i-1之间。对于在此区间内的拐点j，它与拐点i的连线的斜率一定要小于等于j到i之间所有拐点与i的连线的斜率，j和i之间才能架缆线，否则一定会撞到一些拐点。如图：![](https://cdn.luogu.com.cn/upload/pic/38082.png)

2与4的连线比3与4连线的斜率大，会撞上拐点3，所以不能架缆线。而1与4的连线比3与4连线和2与4的斜率都小，因此不会撞上任何拐点。

处理完这个条件方程就很好推啦，f[i]=min(f[i],f[j]+1)，j满足以上条件，也没有别的优化，基本就是裸题啦。提高+的难度评定大概是因为条件的判断吧。~~其实并没有多难~~

题解配合代码食用，风味更加哦~
```cpp
#include<bits/stdc++.h>
 using namespace std;
 int n,m,i,j,a,b,temp;
 int h[5005],f[5005];
 inline int read()
{
	int x=0,c; bool f=0;
	for(;(c=getchar())<'0'||c>'9';f|=c=='-');
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	return f?-x:x;
}
 int main()
{
	n=read(); m=read(); for(i=1;i<=n;i++) h[i]=read();
	for(i=1;i<=n;i++)
	{
		temp=i; a=1e9; b=1;//因为除法太耗时间了，实数比大小又比较麻烦，所以就移项变形成乘法了
		for(j=i-1;j+m>=i&&j;j--)
			if(1ll*(h[i]-h[j])*b<=1ll*a*(i-j))
             a=h[i]-h[j],b=i-j,temp=min(temp,f[j]+1);
		f[i]=temp;
	}
	printf("%d",f[n]);
	return 0;
}
```

---

## 作者：da32s1da (赞：2)

一开始看错了题意，以为是贪心。。

然后仔细看题，发现一根缆绳是不能弯折的。

所以一根缆绳中间不能有其他的山峰穿过。

也就是要保证缆绳的起点$i$到缆绳的终点$j$之间$i,j$的斜率是最大的。

对于每个山峰，有转移方程$f[i]=min(f[i],f[j]+1)$，条件是$j,i~$这段斜率大于等于$(j+1,i)...(j+2,i)...(j+3,i)...(i-1,i)$的斜率。
```
#include<cstdio>
#include<iostream>
using namespace std;
const int N=5050;
const int inf=0x77777777;
typedef double D;
int n,k,f[N];
D xl,h[N],now;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lf",&h[i]),f[i]=n;
	f[1]=1;
	for(int i=2;i<=n&&(now=inf);i++)
	for(int j=i-1;j>=max(i-k,1);j--)
	if((h[i]-h[j])/(D)(i-j)<=now)now=(h[i]-h[j])/(D)(i-j),f[i]=min(f[i],f[j]+1);
	printf("%d\n",f[n]);
}
```

---

## 作者：XiangyuHu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P4909)

题目大意
---

给定 $n$ 个点，先连成一条折线。在其中选一些点，连成一条折线，要求折线不能在原来折线之下，且新折线中相邻两个点横向距离不超过 $k$。求最少选几个点。

题目解析
---

很明显，这就是一道 `dp` 题。考虑状态定义：

$f_i$ 表示前 $i$ 个点至少选出几个点。

那么转移就很清晰了：

$f_i=f_j+1$，其中 $j$ 表示可以转移到 $i$ 的点。

那么如何判断能否转移呢？只需要从后往前扫，扫到一个点计算一下当前点与这个点连线的斜率，再与之前的斜率对照判断一下即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/2yg34704.png)

考虑线段 $f$ 的转移。显然，$f$ 可以转移到 $g$。$f$ 上端点与 $h$ 的上端点连线斜率更小，所以也可以转移到 $h$。但是 $f$ 到 $l$ 斜率增大，不能连线。

综上，代码就出来了：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[5050];
int dp[5050];
int main() {
//	freopen("lift.in", "r", stdin);
//	freopen("lift.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[1] = 1;
	for (int i = 2; i <= n; i++) {
		dp[i] = min(dp[i], dp[i - 1] + 1);
		double d = a[i] - a[i - 1];
		for (int j = i - 2; j >= i - k && j >= 1; j--) {
			double tmp = 1.0 * (a[i] - a[j]) / (i - j);
			if (tmp <= d + 1e-4) {
				d = tmp;
				dp[i] = min(dp[i], dp[j] + 1);
			}
		}
	}
	printf("%d\n", dp[n]);
	return 0;
}
```

其实这题还有一种方法。

不知道刚学 `dp` 入门时老师有没有讲过，`dp` 有两种实现方式：填表法和刷表法。那么，这题用刷表法也是可以做的。

还是刚刚那个状态。但是转移方程变了：

$f_j=f_i+1$，其中 $j$ 为 $i$ 能转移到的点。

考虑如何判断能否转移到：

![](https://cdn.luogu.com.cn/upload/image_hosting/2yg34704.png)

考虑 $h$ 的转移。$h$ 到 $f$ 的斜率，比起 $h$ 到 $g$ 的斜率增大了，所以斜率增大或不变会使这一个能放。

刷表法代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[5050];
int dp[5050];
int main() {
//	freopen("lift.in", "r", stdin);
//	freopen("lift.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[1] = 1;
	for (int i = 1; i < n; i++) {
		dp[i + 1] = min(dp[i + 1], dp[i] + 1);
		double d = a[i + 1] - a[i];
		for (int j = i + 2; j <= i + k && j <= n; j++) {
			double tmp = 1.0 * (a[j] - a[i]) / (j - i);
			if (tmp >= d - 1e-4) {
				d = tmp;
				dp[j] = min(dp[j], dp[i] + 1);
			}
		}
	}
	printf("%d\n", dp[n]);
	return 0;
}
```

注意一个小细节：斜率要开 `double`，特别是除法！

还是要抱怨数据太水，

`double tmp = 1.0 * (a[j] - a[i]) / (j - i);`

写成

`double tmp = 1ll * (a[j] - a[i]) / (j - i);`，

都有 $80$ 分！

强烈建议加强数据 & 求通过！

---

## 作者：hank0402 (赞：1)

## 题解：

设 $dp_i$ 为选取前 $i$ 个点且选第 $i$ 个点的答案，显然答案为 $dp_n$.

考虑转移，转移类似于 $n^2$ 的最长上升子序列：

$$
dp_i=\min_{j\in S}dp_j+1
$$

其中，$S$ 为可以转移到 $i$ 的 $j$ 的集合。

考虑可以转移到 $i$ 的 $j$ 要满足什么条件。

首先，据题目所说，$i$ 和 $j$ 的距离要不大于 $k$，即 $j\geq i - k$.

然后，还有一个限制条件，钢丝不能穿过山坡，转化为数学语言就是对于任意的 $l$ 满足 $j\leq l\leq i$，要满足 $K_{i\to j}\geq K_{l\to j}$.

其中 $K_{i\to j}$ 表示连接 $i$ 和 $j$ 两点的线段的斜率。

于是我们可以在每次转移从满足条件 $1$ 的从大往小扫过去，统计斜率最小值，若斜率最小值为转移点 $j$ 到被转移点 $i$ 的斜率，则表明转移点 $j$ 满足条件 $2$，即为可转移点。

于是我们可以在 $O(nk)$ 的时间解决此题。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
const int N = 5005;
int f[N], n, k, h[N];
int main() {
//	freopen("lift.in", "r", stdin);
//	freopen("lift.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &h[i]);
	}
	for(int i = 0; i <= n; ++i) {
		f[i] = 1e9 + 11;
	}
	f[1] = 1;
	for(int i = 2; i <= n; ++i) {
		double minn = 1e9;
		int rg = max(1, i - k);
		for(int j = i - 1; j >= rg; --j) {
			double now = (h[i] - h[j]) * 1.0 / (i - j); //当前斜率
			minn = min(minn, now); //实时求斜率最小值
			if(fabs(now - minn) < eps) f[i] = min(f[i], f[j] + 1); //进行转移
		}
	}
	printf("%d", f[n]);
	return 0;
}
```


---

## 作者：quarmer (赞：0)

这道题显然是 dp。

状态表示和方程都不难想到： $f_{i}$ 表示前 $i$ 座山最少搭几架支柱。

方程：$ f_{i} = \min\{f_{j} + 1\}$。

这一步都是不难想到的，但是关键在于这个 $j$ 的取值范围，试想，如果 $i$ 与 $j$ 之间有一座很高的山，使 $i$ 不能通过一架缆车连到 $j$，那么那个方程就不能进行。

现在的问题变为，怎么确定对于每个 $h_{i}$，有哪些 $h_{j}$ 使得在此坐标系中连接 $P(i,h_{i})$ 与 $P(j,h_{j})$ 的直线（设此直线为 $l1$）不经过其他山脉。

此时，由~~小学基础数学知识~~可知，当且仅当连接每一个从 $h_{i}$ 连到 $h_{q}$ 的直线，斜率都不比 $l1$ 的斜率大，上述条件成立。其中 $q \in [i + 1, j - 1]$。

代码中，先预处理出对于每一对 $i,j$ 能否连一条直线，再直接套方程即可。程序如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath> 
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;
#define int long long
int n, k ;
int a[5005] ;
bool can[5005][5005] ; //can[i][j] 表示 i,j 间能否造一个缆车 
int f[5005] ;
double cal(int x1, int y1, int x2, int y2) {
	return (-(y1 - y2)) * 1.0 / (-(x1 - x2)) ; //给出两点，计算经过其的直线的斜率 
}
bool check(int x1, int y1, int x2, int y2, int x3, int y3) {
	return cal(x1, y1, x2, y2) <= cal(x2, y2, x3, y3) ; //判断是否大于 
}
int maxx(int x, int y) {return x > y ? x : y ;} 
void work() {
	for(int i = 1 ; i < n ; i++) can[i][i + 1] = can[i + 1][i] = 1 ;
	for(int i = 1 ; i <= n ; i++) {
		int maxn = a[i + 1], maxd = i + 1 ; //最大斜率取到的山的高度与位置 
		for(int j = i + 2 ; j <= n ; j++) {
			can[i][j] = can[j][i] = check(i, a[i], maxd, maxn, j, a[j]) ;
			if(cal(i, a[i], j, a[j]) > cal(i, a[i], maxd, maxn)) maxn = a[j], maxd = j ;
			//更新最大的斜率 
		}
	}
}
int read(){
	char ch ;int s = 0 ;int w = 1;
	while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
	while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
	return s * w ;
}
signed main(){
	n = read(), k = read() ;
	for(int i = 1 ; i <= n ; i++) a[i] = read() ;
	work() ; //预处理函数 
	memset(f, 0x3f, sizeof(f)) ;
	f[1] = 1 ; //初始化，因为起点必须建一个 
	for(int i = 1 ; i <= n ; i++)
		for(int j = i - 1 ; i - j <= k && j >= 1 ; j--)
			if(can[i][j]) f[i] = min(f[i], f[j] + 1) ; //套公式 
	cout << f[n] ;
    return 0 ;
}
```

---

## 作者：0x3F (赞：0)

显然用 `DP`，当可以从 $i$ 连到 $j$ 时 $dp_i=\max\{dp_j+1\}$.

问题来了：怎么判断是否可以从 $i$ 连到 $j$？

画一张图理解一下：

![](https://z3.ax1x.com/2021/06/25/R1Fl3d.png)

> Q:为什么 $4$ 可以到达 $2$？

> A:因为绿斜线与蓝直线（此处指垂直于地面的线段）不相交。

> Q:为什么不可以到达？

> A:因为红斜线与绿直线相交。

为什么红斜线与绿直线相交呢？因为绿斜线在红斜线上方，也就是说绿斜线在红斜线的顺时针方向。

如何判断两条线的顺逆时针方向？没错：斜率。

定义点 $i$ 到点 $j$ 的斜率为 $\dfrac{h_i-h_j}{i-j}$

如图。

![](https://z3.ax1x.com/2021/06/25/R1EBgH.png)

当然斜率可能为负，但此时斜率和顺逆时针的关系仍然成立。

~~不信你自己画一张图我懒得画了~~

说了这么多，究竟如何判断 $i$ 是否可以连到 $j$？

设 $t$ 为当前以 $i$ 为起点斜率最大的终点，则 $i$ 到 $j$ 的斜率大于**等于**从 $i$ 到 $t$ 的斜率，即

$$\dfrac{h_i-h_j}{i-j} \geqslant \dfrac{h_i-h_t}{i-t}$$

即

$$(h_i-h_j)(i-t) \geqslant (h_i-h_t)(i-j)$$

（这样可以避免浮点运算的误差）

时可以从 $i$ 连到 $j$。

此时由于 $i$ 到 $j$ 的斜率变成了最大，所以需要将 $j$ 赋给 $t$。

关键部分的伪代码如下：

```latex
if ((i-j)(h_i-h_t)>=(i-t)(h_i-h_j)) then
	min(dp_i, dp_j +1) → dp_i
	j → t

```

注意了：先将 $j = i-1$ 的情况的 $dp_j$ 的值算出来，循环中 $j$ 从 $i-2$ 开始枚举。因为 $j = i-1$ 时难以给 $t$ 赋值，同时两者之间没有第三者阻拦，必然可以连起来。

还有：如果像我这样做，那么两数相乘可能会爆 `int`！直接在前面乘个 `1ll` 就行了。（间接的类型转换）

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, h[5010], dp[5010], t;
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
		dp[i] = dp[t = i - 1] + 1;
		for (int j = i-2; j >= 1 && i - j <= k; j--) 
			if (1ll*(i-j)*(h[i]-h[t]) >= 1ll*(i-t)*(h[i]-h[j])) 
				dp[i] = min(dp[i], dp[t = j] + 1);
	}
	cout << dp[n] << endl;
	return 0;
}
```

---

## 作者：qzhwlzy (赞：0)

# [传送门](https://www.luogu.com.cn/problem/P4909)
## 思路
看图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ombqi6ny.png)  
由图我们可以发现，如果两个点 $i,j(i< j\le n,j-i\le k)$ 可以连接，那么两点间线段的[**斜率**](https://baike.baidu.com/item/%E6%96%9C%E7%8E%87/4914111?fr=aladdin)
 $k_{i,j}\le mink(mink$ 为 $i+1\sim j-1$ 范围内的最小斜率)，证明略，详细解释看下图 $($ 注： $k_{i,j}=\dfrac{h_j-h_i}{j-i})$ 。  
![](https://cdn.luogu.com.cn/upload/image_hosting/ybjn2qzo.png)  
图中，易得 $k_{i,j}=1,k_{i_1,j}=\dfrac54,k_{i_2,j}=\dfrac56$ ，因为 $k_{i_1,j}>k_{i,j},k_{i_2,j}<k_{i,j}$ ，所以线段 $ij$ 与线段 $i_1j$ 相交，与$i_2j$不相交。  
所以看到此题，我们可以得出此题的做法：用 $f_i$ 记录前 $i$ 个支柱的最少支柱数量，最后输出 $f_n$ 。  
计算 $f_i$ ，我们首先将其赋值为 $f_{i-1}+1$ ，即默认从 $i-1$ 个支柱拉缆线。之后，定义 $j$ 从 $i-2$ 循环到 $max(1,i-k)$ ，用 $mink$ 记录最小的斜率值（初值为 $k_{i,i-1}$ ），若 $k_{i,j}\le mink$ ，说明 $i,j$ 可以连线且支柱数量最小，将 $f_i$ 赋值为 $f_j+1,mink$ 赋值为 $k_{i,j}$ 。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#define maxn 5010
using namespace std;
int n,kk;
int a[maxn],f[maxn];
int main(){
	scanf("%d%d",&n,&kk);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	f[1]=1;
	for(int i=2;i<=n;i++){
		double k=0,mink=a[i]-a[i-1];
		f[i]=f[i-1]+1;//赋初始值
		for(int j=i-2;j>=1&&j>=i-kk;j--){
			k=(double)(a[i]-a[j])/(i-j);//斜率公式
			if(k<=mink){//可以连线注意是<=，不是<
				mink=k;//更新
				f[i]=min(f[i],f[j]+1);//更新
  				//注意此处不能直接break，因为有可能这个连不上但是后面的能连上
			}
		}
	}
	printf("%d",f[n]);//输出
	return 0;//完结撒花
}

```


---

