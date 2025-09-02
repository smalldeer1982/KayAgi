# [USACO09NOV] A Coin Game S

## 题目描述

小 A 和小 B 在玩游戏。

初始时，有 $n$ 个硬币被摆成了一行，从左至右第 $i$ 个硬币的价值为 $c_i$。

游戏的规则是，两人交替从这堆硬币的**左侧**连续取出若干硬币，然后将取出的硬币的价值累加至自己获得的累计价值中。若对方上次操作取出了 $k$ 个硬币，那么本次自己最多取出 $k \times 2$ 个硬币。当没有硬币可取时，游戏结束。

游戏开始时，由小 A 先动手取硬币，最多取出 $2$ 个硬币。

请求出当双方都尽可能使自己的累计价值最大的情况下，小 A 能获得的累计价值最大是多少。

## 说明/提示

#### 输出输出样例 $1$ 解释

初始时，硬币序列为 $\{1,~3,~1,~7,~2\}$。

由小 A 先操作，他取出了一个硬币，硬币序列变为 $\{3,~1,~7,~2\}$，小 A 的累计价值为 $1$。

再由小 B 操作，由于小 A 上回合取出了 $1$ 个硬币，所以他本回合可以取出至多 $1 \times 2 = 2$ 个硬币。他取出了一个硬币，硬币序列变为 $\{1,~7,~2\}$，小 B 的累计价值为 $3$。

再由小 A 操作，由于上回合小 B 取出了 $1$ 个硬币，所以他本回合可以取出至多 $1 \times 2 = 2$ 个硬币。他取出了两个硬币，硬币序列变为 $\{2\}$，小 A 的累计价值为 $1 + 1 + 7 = 9$。

再由小 B 操作，由于上回合小 A 取出了 $2$ 个硬币，所以他本回合可以取出至多 $2 \times 2 = 4$ 个硬币。但是只剩下了 $1$ 个硬币，因此他只能取出一个硬币，硬币序列变为空，小 B 的累计价值为 $3 + 2 = 5$，游戏结束。

#### 数据范围与约定

对于全部的测试点，保证 $5 \leq n \leq 2 \times 10^3$，$1 \leq c_i \leq 10^5$。

**提示：请注意本题的空间限制为 $20$ MiB**。

## 样例 #1

### 输入

```
5 
1 
3 
1 
7 
2 
```

### 输出

```
9 
```

# 题解

## 作者：cjlak1o1 (赞：32)

由于巨佬语言过于高深，本蒟蒻这研究道题时间较为长，所以在这里本蒟蒻再用最朴素的语言重新讲解这道题。

## 题意描述
由 $n$ 个硬币，每一个硬币都有一个面值，两个人轮流取硬币，第一个人可以取 $1\sim 2$ 个硬币，设第一个人取了 $j$ 个硬币，则第二个人可以取 $1 \sim 2 \times j$ 个硬币，并以此类推，每一次当前的人都可以取 $1 \sim 2 \times j$ 个硬币（ $j$ 为上一个人取的硬币数），最后输出第一个人最多能拿多少面值。
## 构建dp
这道题不断在发生转移，所以我们想到用dp求解：

- 因为这是一道博弈论dp，满足两个人都很**聪明**，所以面对这样的问题，我们并不需要知道当前是谁在取，我们只需要让当前的这每一步最优即可。
- 由于如果是正着求的话，我们要记录的 $2$ 倍会有很多很多种情况，记录下来十分麻烦，所以我们将这道题目的题意转换为**两个人轮流放硬币，一个人放硬币时需要满足这一次放的硬币数的两倍大于等于上一次另一个人放的硬币数**。
- 我们先记录前缀和， **$sum_i$ 记录放了 $i$ 枚硬币后放的总面值数量。**
- 用一个二维dp， **$dp[i][j]$ 表示已经放了 $i$ 枚硬币，下一个人要放 $j$ 枚硬币。也就是说这次最多放 $2 \times j$ 个的情况**
- 每一次转移, $k$ 表示这一次取的硬币数量，枚举 $k$ 的值从等于 $1$ 到等于 $2 \times j$ ，在 $2 \times j$ 个 $sum[i]-dp[i-k][k]$ 中取一个 $max$ 值。 $dp[i-k][k]$ 记录上一个人在当前这个人要放 $k$ 枚硬币时上一个人最多能放的硬币数，用 $sum[i]$ 减去 $dp[i-k][k]$ 即为当前这个人放 $k$ 个时放的总硬币数。

按照上述想法，时间复杂度为 $O(n^3)$ ，这道题 $n$ 有 $2e3$ ,没办法过去。所以我们要对dp进行优化。
## 优化dp
由于前两维是必须枚举的，所以我们考虑对第三个循环进行优化，我们观察一下 $dp[i][j]$ 与 $dp[i][j-1]$ 的关系。

$dp[i][j-1]$ 是枚举 $k$ 从等于 $1$ 到等于 $2 \times (j-1)$ ，在 $2  \times (j-1)$ 个 $sum[i]-dp[i-k][k]$ 中取一个 $max$ 值。 

$dp[i][j]$ 是枚举 $k$ 从等于 $1$ 到等于 $2 \times j$ ，在 $2\times j$ 个 $sum[i]-dp[i-k][k]$ 中取一个 $max$ 值。

所以从这里大家一定发现了， **$dp[i][j]$ 是严格包含 $dp[i][j-1]$ 的，我们只需要在 $dp[i][j-1]$ 的基础上继续枚举 $k=2 \times j-1$ 和 $k = 2 \times j$ 这两种状态即可。**
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+10;

int n,a[maxn];
int sum[maxn],dp[maxn][maxn];

inline int read()
{
	int res=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) res=(res<<1)+(res<<3)+(c^48);
	return res*f;
}
int main()
{
	n=read();
	for(int i=n;i>=1;i--) a[i]=read();//反过来读入，方便求前缀和 
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];//sum[i]记录放了i个硬币后的总面值 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) 
		{
			int k=2*j-1; 
			dp[i][j]=dp[i][j-1];//由上面分析可知，dp[i][j]严格包含了dp[i][j-1] 
			//在dp[i][j-1]的基础上更新两个状态。 
			if(k<=i) dp[i][j]=max(dp[i][j],sum[i]-dp[i-k][k]);
			//当k<=i时，才能取max 
			if(k+1<=i) dp[i][j]=max(dp[i][j],sum[i]-dp[i-k-1][k+1]);
			//当k+1<=i时，才能取max 
		}
	/*for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);*/ 
	printf("%d\n",dp[n][1]);
	//这里dp[n][1]表示已经放了n个马上要再放1个，但还没有放。
	//马上下一个人要放1个硬币，也就意味着上一次只能放1个或2个，即为第一次取的情况。 
	return 0;
}

```
**蒟蒻拙见，大佬勿喷。**




---

## 作者：Twilight_ (赞：24)

嗯既然还没有题解那么我就来一发吧……

DP：
1.状态：建立一个二维的状态(i,j)说明拿硬币的权力到达其中一名玩家时，桌面上还剩下编号为1~i(倒序，1为最底下的) 的硬币，

上一名玩家拿走了j枚硬币。

2.下一步的状态：那么这一个玩家在这一轮可以选择拿走1,2,3,4…2\*j枚硬币，而他所能获得的最大硬币面值就是1~i所有的硬币面

值之和减去他完成此次操作后（设他取走了k枚硬币）到达状态(i-k,k)的另一名玩家所能获得的最大硬币数。

3.状态的转移：可是因为k的取值范围很大，所以不能直接枚举，不难发现(i,j-1)和(i,j)的状态只相差两种选择的可能，即下一步取走

2\*j-1或2\*j个硬币的这两种，只需要再比较一次这两种状态即可。

****状态转移方程：dp[i][j]=max(dp[i][j],sum[i]-dp[i-k][k]，sum[i]-dp[i-k-1][k+1])(k==2\*j-1);**

4.答案：答案则是在剩下1~n枚硬币时（初始状态）的dp[n][1]（下一步可以选择1枚或两枚硬币）了。

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum[3001],c[3001],dp[3001][3000]; //数组要开大一点，不然会WA；
int main()
{
    cin>>n;
    for(int i=n;i>=1;i--)cin>>c[i];//为了处理方便，我们直接逆序输入（编号自底向上）
    for(int i=1;i<=n;i++)sum[i]+=sum[i-1]+c[i];//获取前缀和
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=dp[i][j-1];//重合部分
            int k=2*j-1;
            if(k<=i)dp[i][j]=max(dp[i][j],sum[i]-dp[i-k][k]);//新增状态
            k+=1;
            if(k<=i)dp[i][j]=max(dp[i][j],sum[i]-dp[i-k][k]);//新增状态
        }
    cout<<dp[n][1]<<endl;
    return 0;
}
```

---

## 作者：C3H5ClO (赞：22)

发一篇思路极其自然，而且短小精悍的题解。

首先，看到题目。博弈论？求最大值？上DP。

令$f[i][j]$为当前剩下第$i$至第$n$个硬币，先手从第$i$个硬币开始取$j$个硬币所能获得的最大价值。

由于取完后对方变成了先手，他肯定会取价值最大的方案，因此可以列出状态转移方程:

$f[i][j]=s[n]-s[i-1]-max\{f[i+j][k]\}(1\leq k\leq min(2j,n-i-j+1))$

其中$s[i]=\sum\limits_{j=1}^{i}{c[i]}$

显然，这个DP是$O(n^3)$的时间复杂度，会TLE。由于$k$总是从1开始循环，因此可以在每次DP出值时在维护一个$maxf[i][j]=max^{j}_ {k=1}\{f[i][k]\}$,就可以将时间复杂度优化到$O(n^2)$。

上代码！
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define ri register int
int n,a[2005],s[2005],f,maxf[2005][2005];
int main()
{
    scanf("%d",&n);
    for(ri i=1;i<=n;i++)scanf("%d",a+i),s[i]=s[i-1]+a[i];
    for(ri i=n;i;i--)
        for(ri j=1;j<=n-i+1;j++)
        {
            f=s[n]-s[i-1]-maxf[i+j][min(j<<1,n-i-j+1)];
            maxf[i][j]=max(maxf[i][j-1],f);
        }
    printf("%d",maxf[1][2]);
}
```

---

## 作者：crpboy (赞：11)

# 博弈dp 记忆化搜索

感觉另外一篇记搜有点奇怪，这里给出亲民写法。

设$f[i][j]$表示做到当前玩家为先手，已经做到第$i$个金币（第$i$个未取），取币上限为$j$的最大价值。

预处理从栈底到栈顶的后缀和。直接暴力枚举选金币的个数记搜，$dfs$枚举复杂度是$O(n^2)$，每次$dfs$还有一个$O(n)$的枚举，总复杂度$O(n^3)$。

```cpp
int dfs(int x,int lim)//取到第x个金币，当前取金币上限是lim
{
    if(x>n)return 0;//超出边界没有金币可选
    lim=min(lim,n-x+1);//取金币上限不能超过n
    if(~f[x][lim])return f[x][lim];
    int ans=0;
    for(int i=1;i<=lim;i++)
        ans=max(ans,sum[x]-dfs(x+i,i<<1));//当前所有金币的和减去对手的最优策略（对手肯定走最优策略）。
    return f[x][lim]=ans;
}

```

然后恭喜T飞。考虑优化，我们发现$f[i][j]$的答案包含了$f[i][j-1]$，所以可以直接由$f[i][j-1]$转移。不难发现，$f[i][j]$只比$f[i][j-1]$多枚举了$(x+lim,lim*2)$，所以就可以省去$dfs$内的$O(n)$枚举，直接搜多余部分，复杂度降到$O(n^2)$。优秀。


$AC$代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2005;

int n,c[N],sum[N];
int f[N][N];
int dfs(int x,int lim)
{
    lim=min(lim,n-x+1);
    if(~f[x][lim])return f[x][lim];
    if(x+lim>n)return sum[x];//能直接取完何必再爆搜
    if(!lim)return 0;
    int ans=dfs(x,lim-1);
    ans=max(ans,sum[x]-dfs(x+lim,lim<<1));
    return f[x][lim]=ans;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    for(int i=n;i>=1;i--)
        sum[i]=sum[i+1]+c[i];
    memset(f,-1,sizeof(f));
    cout<<dfs(1,2);
    return 0;
}
```

[双倍经验](https://www.luogu.org/problemnew/show/SP5271)

---

## 作者：Leap_Frog (赞：10)

# P2964 [USACO09NOV]硬币的游戏A Coin Game（题解）

### 1.吐槽
首先，这道题是博弈论，再看一下难度，发现是$\color{white}\colorbox{#3498DB}{\texttt{提高+/省选-}}$  
那么应该与$\texttt{SG}$函数等无关了。。。  
所以则道题应该是博弈论$\texttt{DP}$  

### 2.主要过程
设$\texttt{dp[i][j]}$是桌子上还剩下$\texttt{i}$个堆，上一个玩家取了$\texttt{j}$堆的情况  

这一个玩家在这一轮可以选择拿走$\texttt{1,2…2*j}$枚硬币，而他所能获得的最大硬币面值就是$\texttt{1-i}$所有的硬币面值  

但是我们发现这样的复杂度是$\texttt{O(n}^\texttt{3}\texttt{)}$  
不足以通过此题。。。

我们发现$\texttt{dp[i][j]}$的一部分是$\texttt{dp[i][j-1]}$，所以我们可以考虑从$\texttt{dp[i][j-1]}$向$\texttt{dp[i][j]}$转移，只考虑最后一堆取不取。。。

成功把复杂度降到$\texttt{O(n}^\texttt{2}\texttt{)}$  

### 3.上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int n,s[N],dp[N][N];
int main()
{
    scanf("%d",&n);
    for(int i=n;i>=1;i--) scanf("%d",s+i);
    for(int i=1;i<=n;i++) s[i]+=s[i-1];
    for(int i=1;i<=n;i++)
        for(int j=1,k=2*j-1;j<=n;j++,k=2*j-1)
        {
            dp[i][j]=dp[i][j-1];
            if(k<=i) dp[i][j]=max(dp[i][j],s[i]-dp[i-k][k]);
            if(k+1<=i) dp[i][j]=max(dp[i][j],s[i]-dp[i-k-1][k+1]);
        }
    printf("%d\n",dp[n][1]);
    return 0;
}
```

---

## 作者：堇墨浮华 (赞：8)

## 这是本蒟蒻发布的第一篇题解QwQ
#这道题很明显是一道动规题，~~卡了我快2小时才编好~~
#用f[i][j]表示还剩下i枚硬币，上次对手拿了j枚硬币时第一个玩家最多能拿多少钱，~~思路还是很好想的~~，具体过程见代码（注释应该还算清楚吧。。。）
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=2005;
int n,c[N],sum[N],f[N][N];
int main(){
	scanf ("%d",&n);
	for (int i=n;i>=1;i--)
		scanf ("%d",&c[i]);//倒着读入,这样方便统计前缀和 
	for (int i=1;i<=n;i++)
		sum[i]=sum[i-1]+c[i];//前缀和,表示从堆底到现在的硬币总价值 
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			f[i][j]=f[i][j-1];//本来是想再用一个k从1~2*j枚举的,但是看到数据范围。。。O(n^3)还是算了吧 
			//O(n^3)转移是很好想的,如果i<=j,则f[i][j]=sum[i]-min(f[i-k][k]),反之则用sum[j]-sum[i]
			int k=2*j-1;
			if (k<=i) f[i][j]=max(f[i][j],sum[i]-f[i-k][k]);
			k++;
			if (k<=i) f[i][j]=max(f[i][j],sum[i]-f[i-k][k]);
			//通过观察,发现f[i][j]和f[i][j-1]大部分都是一样的,只不过f[i][j]比f[i][j-1]多了两种转移
			//所以只要在f[i][j-1]的基础上加上k=2*j和k=2*j-1这两种转移即可
			//当然,k不能大于i,不然剩下硬币数还没有拿的多了。。。 
		}
	printf ("%d\n",f[n][1]);//输出结果~0v0~ 
	return 0;
}

```

---

## 作者：Linne (赞：7)

傻逼题。
写个n^2dp本来以为过不了结果随便水...
f[i][j]表示还剩i个，限制取j个,最大收益。
易得如下转移
f[i][j]=max(f[i][j-1],s[i]-f[i-j][min(i-j,j<<1)])
（分类讨论是不是取j个，如果取的话收益就是总收益减去对方最大收益。）
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[2001],N,f[2001][2001];
int main()
{	scanf("%d",&N);
    for (int i=N;i;i--)scanf("%d",&s[i]);
    for (int i=2;i<=N;i++)s[i]+=s[i-1];
    for (int i=1;i<=N;i++)
        for (int j=1;j<=i;j++)
            f[i][j]=max(f[i][j-1],s[i]-f[i-j][min(i-j,j<<1)]);
    printf("%d\n",f[N][2]);
    return 0;
}
```



---

## 作者：Boxxxxxx (赞：3)

[点击博客，救救孩子](https://blog.csdn.net/qq_43804974/article/details/104113399)

在之前，我写dp看见题目说两个人都足够聪明，然后他们进行一些操作，求某些人的最大利益，我完全不知道怎么去设计dp的方法，然后我接触了一道题，看了题解

[洛谷p2734](https://www.luogu.com.cn/problem/P2734)


这道题的dp方法和现在这道题其实在设计思路上面是一样。
**我不知道现在是谁在取数字，但是我就是要为现在这个取数字的人谋取最大利益**这个思想在博弈论的dp是很关键的。

回到原题，一开始的玩家可以取k个币，下一个人只能取小于等于k*2个
我们这么设计状态f[i][j], 表示现在在i这个币的位置，现在要拿的这个人拿了j个币后， 这个人获得的总权值。

既然我们设计的是总权值，那么就不能从i= 1开始转移，要从后面开始向前面转，这样回到1的时候就是第一个人拿的总权值。

我们来尝试转移这个状态，f[i][j]很明显，你现在这个人就是拿了j个币，那么下一个人只能拿[1，j * 2]个币。也就是，如何达到f[i][j]最大？sum表示的是前缀和，那么从[i,n]的权就是sum[n] - sum[i-1]，然后下一个人拿的权是f[i+j][1, j * 2]里面最大的，为什么是最大的？因为第二个人也是最聪明的，他会选择最大的那个总权值，那么很明显，转移方程就是
maxf[i][j]表示f[i][1到n]的最大值

```cpp
f[i][j] = sum[n] - sum[i - 1] - maxf[i + j][min(j * 2 ,n)];
```
这里唯一的难点就是要考虑到第二个人也是最聪明的，你-的数字必须是可选择的数字里面最大的。
这样从后晚前dp最终max（f[1][1],f[1][2]）就是答案，代码就是

```cpp

int n, sum[max_], f[max_][max_],maxf[max_][max_];
int main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i-1] + read();
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= n; j++) {
			//现在这个人拿的时候到了第i枚币，你可以拿j没
			if (i + j - 1 <= n) {
				f[i][j] = sum[n] - sum[i - 1] - maxf[i + j][min(j * 2 ,n)];
			}
			else 
				break;
		}
		for (int j = 1; j <= n; j++) {
			maxf[i][j] = max(maxf[i][j - 1], f[i][j]);
		}
	}
	int ans = max(f[1][1], f[1][2]);
	cout << ans;
	return 0;
}
```
但是这样过不去，为什么？因为MLE，数组开太多了，我们就在考虑化简一下，少些数组，我们观察可得可以吧maxf和f融合在一起写就好了，这样就可以少掉个f，最终代码，（其实可以不需要额外的循环来维护maxf，在一开始填这个数字的时候就可以维护了，但是由于我上一份代码只需要吧f改成fmax就可以AC， ~~我就懒得写了~~ ）

```cpp
int n, sum[max_],maxf[max_][max_];
int main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i-1] + read();
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 1; j <= n; j++) {
			//现在这个人拿的时候到了第i枚币，你可以拿j没
			if (i + j - 1 <= n) {
				maxf[i][j] = sum[n] - sum[i - 1] - maxf[i + j][min(j * 2 ,n)];
			}
			else 
				break;
		}
		for (int j = 1; j <= n; j++) {
			maxf[i][j] = max(maxf[i][j - 1], maxf[i][j]);
		}
	}
	int ans = max(maxf[1][1], maxf[1][2]);
	cout << ans;
	return 0;
}
```


也就是把所有的f改成fmax，这道题主要是要学习最主要的思想！！！**去dp当前这个人的最大可得权值，你不关心现在拿的这个人是谁！！！**如果这道题是指询问第二个人的权呢？你dp出第一个人的权去减到总权就是第二个人的！这就是在开头我给出的第二个链接的题目的方法。


---

## 作者：asuldb (赞：3)

楼上的两篇题解好像啊

那我来发一篇长得一点也不一样的题解吧

这是一个非常自然的正着做的做法

我们用$dp[i][j]$表示从第$i$个硬币开始取，这一次取$j$个能获得的最大收益

显然由于双方都足够聪明，所以接下来就会转化为另一个人先手从$i+j$这个硬币开始取了

于是具体是什么转移回了$dp[i][j]$呢，显然是从剩下的硬币的和减去$i+j$这个位置能先手取得的最大值

所以就有了

$$dp[i][j]=s[i+j,n]-max(dp[i+j][k])+s[i,i+j-1](1<=k<=2*j)$$

也就是

$$dp[i][j]=s[i,n]-max(dp[i+j][k])(1<=k<=2*j)$$

但是这个样子的话我们$dp[i+1][k]$的状态还没有呢，我们应该怎么更新啊

那就记搜啊

代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define maxn 2005
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
int n,a[maxn],pre[maxn];
int dp[maxn][maxn];
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
int dfs(int x,int y)
{
	if(x+y==n+1) return pre[n]-pre[x-1];
	if(dp[x][y]<=336860170) return dp[x][y];
	for(re int i=1;i<=2*y&&x+y+i<=n+1;i++)
		dp[x][y]=min(dp[x][y],-dfs(x+y,i));
	dp[x][y]+=pre[n]-pre[x-1];
	return dp[x][y];
}
int main()
{
	n=read();
	for(re int i=1;i<=n;i++) a[i]=read();
	for(re int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
	memset(dp,20,sizeof(dp));
	dp[1][1]=min(dp[1][1],pre[n]-pre[1]-dfs(2,1));
	dp[1][1]=min(dp[1][1],pre[n]-pre[1]-dfs(2,2));
	dp[1][1]+=a[1];
	for(re int i=1;i<=4;i++)
	if(3+i<=n+1) dp[1][2]=min(dp[1][2],pre[n]-pre[2]-dfs(3,i));
	dp[1][2]+=a[1]+a[2];
	printf("%d",max(dp[1][2],dp[1][1]));
	return 0;
}
```

之后就$T$了，因为这个记搜的复杂度是$O(n^3)$的

但是我们会发现一个问题，就是$dp[i][j]$的$dp[i+1][j-1]$的转移好像啊

好像$dp[i][j]$就比$dp[i+1][j-1]$多了两个状态，$dp[i+j][2*j-1]$和$dp[i+j][2*j]$，于是这样就能优化成一个$O(n^2)$了

代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define re register
#define maxn 2005
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
int n,a[maxn],pre[maxn];
int dp[maxn][maxn];
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
int dfs(int x,int y)
{
	if(x+y==n+1) return pre[n]-pre[x-1];
	if(dp[x][y]<=336860170) return dp[x][y];
	if(y==1) 
	{
		for(re int i=1;i<=2*y&&x+y+i<=n+1;i++)
			dp[x][y]=min(dp[x][y],-dfs(x+y,i));
	}
	else
	{
		dp[x][y]=dfs(x+1,y-1);
		dp[x][y]-=pre[n]-pre[x];
		for(re int i=2*y-1;i<=2*y&&x+y+i<=n+1;i++)
			dp[x][y]=min(dp[x][y],-dfs(x+y,i));
	}
	dp[x][y]+=pre[n]-pre[x-1];
	return dp[x][y];
}
int main()
{
	n=read();
	for(re int i=1;i<=n;i++) a[i]=read();
	for(re int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i];
	memset(dp,20,sizeof(dp));
	dp[1][1]=min(dp[1][1],pre[n]-pre[1]-dfs(2,1));
	dp[1][1]=min(dp[1][1],pre[n]-pre[1]-dfs(2,2));
	dp[1][1]+=a[1];
	for(re int i=1;i<=4;i++)
	if(3+i<=n+1) dp[1][2]=min(dp[1][2],pre[n]-pre[2]-dfs(3,i));
	dp[1][2]+=a[1]+a[2];
	printf("%d",max(dp[1][2],dp[1][1]));
	return 0;
}
```

---

## 作者：JasonZRY (赞：2)

设f[i][j]表示还剩i枚硬币，上一个人拿了j枚硬币，到最后的最大收益。

先手后手转移相同，f[i][j]=f[i-k][k] (k<=min(2j,i))，直接DP是O(n^3)的。

发现每次j增加时对k的影响只有2j-1和2j，再判断一下与i的关系即可。

代码如下：

```
#include<iostream>
using namespace std;
int n,a[2001],s[2001],f[2001][2001];
int main(){
    cin>>n;
    for(int i=n;i>=1;i--)cin>>a[i];
    for(int i=1;i<=n;i++)s[i]+=s[i-1]+a[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j]=f[i][j-1];
            int k=2*j-1;
            if(k<=i)f[i][j]=max(f[i][j],s[i]-f[i-k][k]),k++;
            if(k<=i)f[i][j]=max(f[i][j],s[i]-f[i-k][k]);
        }
    }
    cout<<f[n][1];
    return 0;
}
```


---

## 作者：蒟蒻思翔 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P2964)
### 题目大意：
有一些价值不同的金币排成一列，两个人从左往右轮流取金币，每次可以至取多上一个人取的个数的两倍，求先手能获得的最大金币价值和。
### 大体思路：
- 乍一看：**两方轮流决策 + 已知的局面 + 决策所对应的固定结局**——我们很容易联想到博弈论 $dp$。

- 又由于两个人的除了先后顺序外取金币的方法相同，所以我们可以不管当前是谁在取，只考虑当前怎么取最优就可以了。

- 状态是互相的，**让对方取的最少即是让自己取得最多**，转移时通过这两个方面都可以思考。

### $dp$ 设计：
首先我们处理一下前缀和，$q_i$ 表示前 $i$ 个金币价值之和。

对于状态：无论如何，**每一次取的金币的多少**只由**当前从哪一个开始取**和**可以最多取几个**决定。本人采用的是倒推，所以状态设计为： **$f_{i,j}$ 表示加上这次取完了最后 $i$ 个 ，而这次最多可以取 $j$ 个的最大价值。**

然后我们第一层倒着枚举 $i$，第二层正着枚举 $j$, 依次更新每个 $f_{i,j}$ 。怎么设计转移呢？可以这样想，我们以样例为例：金币序列为 ${1,3,1,7,2}$




1. 当**剩下的数** $\leq$ **能选的数**时，比如 $i=3,j=4$ 时，既然可以选剩下所有的数 ${1,7,2}$ ，那必定要选完，不给对方留下任何机会。$f_{i,j}$ 为剩下所有的价值之和。
```cpp
if(j>=la)f[i][j]=q[n]-q[i-1];
```
2. 其余情况，我们只能由之前的状态转移。$f_{i,j}$ 为**所有已选的金币的价值 - 取这次之前，对方取的价值和**。由于设定的状态是**可以取多少**而不是**取了多少**，我们还要枚举实际取了多少，最终在所有的里面取**最大值**。比如 $i=3,j=1$ 时，需要考虑**对方取到7的位置，一共可以取2个**时和**对方取到2的位置，一共可以取2个**的最大值，也就是 $f_{4,2}+1$，$f_{5,2}+1+7$ 的最大值。
```cpp
for(int k=j;k<=j;k++)
f[i][j]=max(f[i][j-1],q[n]-q[i-1]-f[i+k][min(k*2,la)]);
```


### 精简的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,q[10000],f[2005][2005];//第几个，可以取几个
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		q[i]=q[i-1]+x;
	}
	for(int i=n;i;i--){
		int la=n-i+1;//la表示剩下的硬币 
		for(int j=1;j<=n;j++){//枚举可以取的个数 
			if(j>=la)f[i][j]=q[n]-q[i-1];
			else 
				for(int k=j;k<=j;k++)//实际选了k个 
					f[i][j]=max(f[i][j-1],q[n]-q[i-1]-f[i+k][min(k*2,la)]);
		}
	}
	cout<<f[1][2];
}
```

### 最后
当然，这个写法是三层循环的，复杂度较高，但是也可以通过。当然也可以根据单调性减少 $k$ 的枚举范围。这里就不再继续解释了。

---

## 作者：Fzrcy (赞：0)

设 $f_{i,j}$ 表示从第 $i$ 个硬币开始且开始时最多取 $j$ 个硬币时先手获得的最大累计价值、$s_i=\sum_{j=i}^na_i$ 表示后缀和。

则：

$$
f_{i,j}=\max_{k=i}^{\min(n,i+j-1)}s_i-f_{k+1,2(k-i+1)}
$$

时间复杂度为 $O(n^3)$。

显然 $f_{i,j}$ 的转移包含 $f_{i,j-1}$，则：
$$
f_{i,j}=\max\{f_{i,j-1},s_i-f_{i+j,2j}\}
$$
时间复杂度为 $O(n^2)$。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
constexpr int N=2e3+9;
int n,s[N],f[N][N];
int sol(int u,int lst){
    lst=min(lst,n-u+1);
    if(~f[u][lst])return f[u][lst];
    if(!lst)return 0;
    if(u+lst>n)return s[u];
    return f[u][lst]=max(sol(u,lst-1),s[u]-sol(u+lst,lst<<1));
}
int main(){
    memset(f,-1,sizeof f),cin>>n;
    for(int i=1;i<=n;i++)cin>>s[i];
    for(int i=n;i>=1;i--)s[i]+=s[i+1];
    return cout<<sol(1,2)<<'\n',0;
}
```



---

## 作者：Φρανκ (赞：0)

题意：从数列 $c_i$ 中从左到右轮流选数，每人每次至多选上一个人上次选数数量的两倍个数。双方追求自己数的和最大，且第一次选数可选 $1$ 或 $2$ 个，求先手的最优得分。

核心思想：DP

解：

令 $f(i,j)$ 表示从第 $i$ 个数开始选，先手开始时取 $j$ 个数时的最优得分。那么，先手的最优得分就是总分（数列所有项的和）减去取完第一次后剩余的数列中先手的最优得分（后手的最优得分）。表达式如下：$f(i,j)=\Sigma_{i=i}^n c_i-\max(f(i+j,1),f(i+j,2),...,f(i+j,2j))$

注意到 $f(i,n+1-i)=\Sigma_{i=i+1}^n c_i$，这一部分可用前缀和处理出。又注意到 $f(i+1,j-1)=\Sigma_{i=i+1}^n c_i-\max(f(i+j,1),f(i+j,2),...,f(i+j,2j-2))$，可以将 $\max(f(i+j,1),f(i+j,2),...,f(i+j,2j))$ 简化为 $\max(\Sigma_{i=i+1}^n c_i-f(i+1,j-1),f(i+j,2j-1),f(i+j,2j))$ 以优化复杂度。

按此式 DP 即可。注意要特判边界条件 $j=1$ 及 $j=n+1-i$ 并且 $\max()$ 中的项不能越界，答案即为 $\max(f(1,1),f(1,2))$。

代码：
```
#include <bits/stdc++.h>
using namespace std;
int n, c[2001], a[2001][2001], temp;
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
		cin>>c[i];
	for(int i=n; i>=1; i--)
		a[n+1-i][i]=a[n-i][i+1]+c[i];//前缀和处理边界
	a[1][n-1]=c[n-1];
	for(int i=n-2; i>=1; i--)
	{
		a[1][i]=a[n+1-i][i]-max(a[1][i+1], a[2][i+1]);//j=1边界
		for(int j=2; j<n+1-i; j++)
		{
			temp=a[n-i][i+1]-a[j-1][i+1];
			if(2*j-1<=n+1-i-j)//判断是否越界
				temp=max(temp, a[2*j-1][i+j]);
			if(2*j<=n+1-i-j)//判断是否越界
				temp=max(temp, a[2*j][i+j]);//求最大值
			a[j][i]=a[n+1-i][i]-temp;//求f(i,j)
		}
	}
//	for(int i=1; i<=n; i++)
//	{
//		for(int j=1; j<=n; j++)
//			cout<<a[i][j]<<" ";
//		cout<<endl;
//	}
	cout<<max(a[1][1], a[2][1]);//输出最大值
	return 0;
}

```

---

## 作者：activeO (赞：0)

## 题目大意

$ 2 $ 个人取硬币，每个硬币有一个价值。如果上一个人取了 $ x $ 个硬币，那么下一个人就最多只能取 $ 2x $ 个硬币，第一个人最多取 $ 2 $ 个硬币，问先手能取到的最大价值。

## 思路

首先容易发现这是道博弈论的题（~~发现不了看标签也可以发现~~）。

因为博弈论满足每个人都很 clever 所以，我们每一步都做到最优就行，所以考虑 dp。

然后发现直接推，需要处理的状态很麻烦，所以考虑反过来，每个人放硬币，于是如果一个人要放 $ x $ 个硬币，上个人放的硬币 $ y \leq  2x$。

$ dp_{i,j} $ 表示已经放了 $ i $ 个硬币，下一步放 $ j $ 个硬币。

于是可得方程 $ dp_{i,j}=\max(sum_i-dp_{i-k,k}) $。

可是这个方程是 $ O(n^3) $ ，范围：$ n \leq 2 \times 10^3 $，是过不了的。

**考虑优化**

然后又可以发现 $ dp_{i,j} $ 严格包含 $ dp_{i,j-1} $，所以我们只用在上个状态的基础上，继续枚举出 $ k=2j-1,2j $ 即可。

得出最终方程：$ dp_{i,j} = \max(sum_i-dp_{i-k,k},sum_i-dp_{i-k-1,k+1}) $。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn=2e3+5;
int dp[maxn][maxn];
int a[maxn],sum[maxn];

int main(){
	
	int n;
	
	scanf("%d",&n);
	for(int i=n;i>=1;i--) scanf("%d",&a[i]);
	
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int k=2*j-1;
			dp[i][j]=dp[i][j-1];
			if(k<=i) dp[i][j]=max(dp[i][j],sum[i]-dp[i-k][k]);
			if(k<i) dp[i][j]=max(dp[i][j],sum[i]-dp[i-k-1][k+1]);
		}
	}
	
	printf("%d\n",dp[n][1]);
	
	return 0;
}
```


---

