# [JOI 2020 Final] 集邮比赛 3 / Collecting Stamps 3

## 题目描述

给定一个周长为 $L$ 的圆，从一个点出发，有 $N$ 个黑白熊雕像，编号为 $1$ 到 $N$，第 $i$ 个雕像在顺时针 $X_i$ 米处，如果你没有在 $T_i$ 秒内收集到这个黑白熊雕像，那么这个雕像就会发出“唔噗噗噗”的声音然后爆炸。

现在 JOI 君在这个点，他每一秒可以移动一米，并且他可以顺时针或者逆时针的移动。

JOI 君想问，他最多能收集到多少个黑白熊雕像？

## 说明/提示

#### 样例 1 解释

JOI 君可以按照如下策略拿到 $4$ 个黑白熊雕像：

|方向|路程|总时间|第几个雕像|能否拿到|
|:-:|:-:|:-:|:-:|:-:|
|逆时针|$2$ 米|$2$ 秒|$6$|$\sqrt{}$|
|逆时针|$2$ 米|$4$ 秒|$5$|$\sqrt{}$|
|顺时针|$7$ 米|$11$ 秒|$1$|$\sqrt{}$|
|顺时针|$1$ 米|$12$ 秒|$2$|$\times$|
|顺时针|$3$ 米|$15$ 秒|$3$|$\sqrt{}$|

#### 样例 2 解释

JOI 君可以直接一直逆时针走。

#### 样例 3 解释

JOI 君无法得到任何一个雕像。

#### 数据规模与约定

**本题采用捆绑测试。**
- Subtask 1（5 pts）：$N \le 12$，$L \le 200$，$X_i \le 200$。
- Subtask 2（10 pts）：$N \le 15$。
- Subtask 3（10 pts）：$L \le 200$，$T_i \le 200$。
- Subtaks 4（75 pts）：无特殊限制。

对于 $100\%$ 的数据：

- $1 \le N \le 200$。
- $2 \le L \le 10^9$。
- $1 \le X_i<L$。
- $X_i < X_{i+1}$。
- $0 \le T_i \le 10^9$。

#### 说明

翻译自 [第19回日本情報オリンピック　本選](https://www.ioi-jp.org/joi/2019/2020-ho/index.html) [C スタンプラリー 3](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t3.pdf)。

## 样例 #1

### 输入

```
6 25
3 4 7 17 21 23
11 7 17 10 8 10```

### 输出

```
4```

## 样例 #2

### 输入

```
5 20
4 5 8 13 17
18 23 15 7 10
```

### 输出

```
5```

## 样例 #3

### 输入

```
4 19
3 7 12 14
2 0 5 4
```

### 输出

```
0```

## 样例 #4

### 输入

```
10 87
9 23 33 38 42 44 45 62 67 78
15 91 7 27 31 53 12 91 89 46
```

### 输出

```
5```

# 题解

## 作者：彭天宇 (赞：16)

首先要看$n\le 200$这是允许$\Theta (n^3)$甚至跑不满的$\Theta(n^4)$的啊。
### 可以理解为拆环成链的区间DP
这也是由上面的允许复杂度产生的思维导向。

设置状态：$f[l][r][k][0/1]$表示从原点出发，向左走到过$l$个物品，向右走到过$r$个物品，然而不一定都拿到，$k$是真正拿到的数量，$0$表示当前最后一步处在左端点，反之则为右端点，所花的最小总时间。

这里一个转化很重要，也是一个难点——$k$是我们要求的，然而却把他安排在状态的维度里。首先：如果把时间作为维度，难免要离散化，转移又麻烦，而$k$只要转移$+1$或者不加。

那么转移也就不难了：例如
$f[l][r][k][0]\to f[l][r+1][k+(time+dis<=t[r])][1]$要经过原点绕一圈，$dis=L-a[n-l+1]+a[r+1]$

其余详见代码。

### 因为写挂了多次，所以有以下注意点：
1.$f$数组转移的时候要取$min$，第一次写挂在这里。

2.计算两个点端点之间距离使，不需要考虑顺时针更短还是逆时针走更短，因为状态中$l,r$规定了边界，如果这样比较取最优，就会走超出$l,r$的区域，既然走了就不可能不把那里的物品顺便拿掉，然而转移是没有拿，只是起点到终点，终点拿一下。

3.转移的边界：$l+r\le n$，不然结果偏大。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=202;
int n,L,ans,a[N],t[N],f[N][N][N][2];
signed main(){
	scanf("%lld%lld",&n,&L);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	a[n+1]=L;
	for(int i=1;i<=n;i++)scanf("%lld",&t[i]);
	memset(f,0x3f,sizeof f);
	f[0][0][0][0]=f[0][0][0][1]=0;
	for(int l=0;l<=n;l++)
		for(int r=0;r<=n;r++){
			if(l+r>=n)break;
			for(int k=0;k<=n;k++){
				int tmp=f[l][r][k][0];
				if(tmp<=1e13){
					f[l+1][r][k+(tmp+a[n-l+1]-a[n-l]<=t[n-l])][0]=min(f[l+1][r][k+(tmp+a[n-l+1]-a[n-l]<=t[n-l])][0],tmp+a[n-l+1]-a[n-l]);
					f[l][r+1][k+(tmp+L-a[n-l+1]+a[r+1]<=t[r+1])][1]=min(f[l][r+1][k+(tmp+L-a[n-l+1]+a[r+1]<=t[r+1])][1],tmp+L-a[n-l+1]+a[r+1]);
				}
				tmp=f[l][r][k][1];
				if(tmp<=1e13){
					f[l+1][r][k+(tmp+L-a[n-l]+a[r]<=t[n-l])][0]=min(f[l+1][r][k+(tmp+L-a[n-l]+a[r]<=t[n-l])][0],tmp+L-a[n-l]+a[r]);
					f[l][r+1][k+(tmp+a[r+1]-a[r]<=t[r+1])][1]=min(f[l][r+1][k+(tmp+a[r+1]-a[r]<=t[r+1])][1],tmp+a[r+1]-a[r]);
				}
			}
		}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			for(int k=0;k<=n;k++)if(min(f[i][j][k][0],f[i][j][k][1])<1e15)ans=max(ans,k);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：虚空之灵 (赞：15)

[个人博客链接](https://myxrcrs.de/%E7%AE%97%E6%B3%95%E7%AB%9E%E8%B5%9B/%E3%82%B9%E3%82%BF%E3%83%B3%E3%83%97%E3%83%A9%E3%83%AA%E3%83%BC-3/)

# 题目

[题目（ja）](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t3.pdf)

题目大概意思就是，沿着湖边有 $n$ 个邮票展台，JOI君可以顺时针或者逆时针移动，每移动一个单位长度需要 $1$ 秒，邮票展台在 $T_i$ 时间后会被移除，问JOI君最多可以收集多少个邮票。

~~为什么要把仅有的日语水平用到奇怪的地方啊~~

（P.S. 有官方的英语翻译版~~为什么题都做完了才发现~~

[题目（en）](https://www.ioi-jp.org/joi/2019/2020-ho/2020-ho-t3-en.pdf)

（P.S. 洛谷上有这道题的翻译版，但是把邮票展台翻译成了黑白熊（？这是什么）

[题目（zh）](https://www.luogu.com.cn/problem/P6879)

# 思路

看到 $N \leq 200$ ，上手当然是动态规划。

而且可以开到三维，甚至玄学优化后的四维。

这样一来，先是想用$dp$数组表示能够收集到的邮票个数，但是这样一来时间就没法放进状态里（因为 $T \leq 10^9$ ）。~~于是果断看官方题解~~

事实上，在看到题解里关于Subtask2的解法的时候，我就瞬间悟了。

![](https://pic.downk.cc/item/5fb76e9db18d627113ef34b6.jpg)

(图片版权信息：©保坂結)

（注：图上文字意思依次为：
- Exchange subscript and value
- Maximum stamps amount when elapsed time is T
- minimum time when stamps amount is k）

但是事实上之前我已经想到了可以用区间dp，这样就有了：

$$
dp_0[l][r][k]
$$
和
$$
dp_1[l][r][k]
$$

$l$ 表示原点逆时针方向取到的邮票个数， $r$ 表示原点顺时针方向取到的邮票个数， $k$ 表示当前已经取得的邮票数量， $dp$ 的值表示取得这些邮票所需要的最小时间， $dp_0$ 和 $dp_1$ 分别表示当前位于区间左端点和区间右端点的情况。

设周长为 $m$ ， $a_i$ 表示第 $i$ 个邮票展台的坐标， $t_i$ 表示第 $i$ 个邮票展台的移除时间。由于题目里的坐标是顺时针给出，对于原点顺时针方向的点，可以直接用更靠顺时针方向的点坐标与其相减得到距离，而对于逆时针方向的点，需要用总数减去个数来获取其下标，如果两个点刚好跨过原点，还需要用周长减去两者的距离才能得到移动的距离。这些关系在纸上画图推导一下就可以推出，此处不继续做详细说明。

不难发现，有如下转移：

当 $dp_0 \neq \text{INF}$ 时，对于 $dp_0$ ，设

$$tNow = dp_0[l][r][i]$$

$$t_0 = tNow+a_{n-l+1}-a_{n-l}$$

$$t_1 = tNow+m-(a_{n-l+1}-a_{r+1})$$

则：

$$
dp_0[l+1][r][i+(t_0 \leq t_{n-l})] = \min\left\{\begin{aligned}
&dp_0[l+1][r][i+(t_0 \leq t_{n-l})] \\
&t_0
\end{aligned}\right.
$$

$$
dp_1[l][r+1][i+(t_1 \leq t_{r+1})] = \min\left\{\begin{aligned}
&dp_1[l][r+1][i+(t_1 \leq t_{r+1})] \\
&t_1
\end{aligned}\right.
$$

当 $dp_1 \neq \text{INF}$ 时，对于 $dp_1$ ，则有：

$$tNow = dp_1[l][r][i]$$

$$t_0 = tNow+m-(a_{n-l}-a_{r})$$

$$t_1 = tNow+a_{r+1}-a_{r}$$

转移方程与 $dp_0$ 同理。

初始化的时候把所有 $dp$ 置为无穷大，并把 $a_{n+1}$ 置为 $m$ （为了求得从原点到逆时针方向第一个邮票展台的距离），最后统计答案的时候求出：

$$
ans = \max_i
$$

其中： 存在 $l,r$ 使得 $dp_0[l][r][i]\neq \text{INF}$ 或 $dp_1[l][r][i]\neq \text{INF}$ 。

上代码：

```C++
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
inline int& min_to(int& a,int b){
    return a=min(a,b);
}
const int MAXN = 205;
int t[MAXN];
int a[MAXN];
int dp[MAXN][MAXN][MAXN][2];
signed main(){
    int n,m;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",a+i);
    for(int i=1;i<=n;i++)scanf("%d",t+i);
    memset(dp,0x3f,sizeof(dp));
    dp[0][0][0][0]=dp[0][0][0][1]=0;
    a[n+1]=m;
    for(int c=0;c<n;c++){
        for(int l=0;l<=n;l++){
            int r=c-l;
            for(int i=0;i<=n;i++){
                if(dp[l][r][i][0]!=0x3f3f3f3f){
                    int tNow = dp[l][r][i][0];
                    int time0 = tNow+a[n-l+1]-a[n-l];
                    int time1 = tNow+m-(a[n-l+1]-a[r+1]);
                    bool canGet0 = time0 <= t[n-l];
                    bool canGet1 = time1 <= t[r+1];
                    min_to(dp[l+1][r][i+canGet0][0],time0);
                    min_to(dp[l][r+1][i+canGet1][1],time1);
                }
                if(dp[l][r][i][1]!=0x3f3f3f3f){
                    int tNow = dp[l][r][i][1];
                    int time1 = tNow+a[r+1]-a[r];
                    int time0 = tNow+m-(a[n-l]-a[r]);
                    bool canGet0 = time0 <= t[n-l];
                    bool canGet1 = time1 <= t[r+1];
                    min_to(dp[l+1][r][i+canGet0][0],time0);
                    min_to(dp[l][r+1][i+canGet1][1],time1);
                }
            }
        }
    }
    int ans = 0;
    for(int l=0;l<=n;l++)for(int r=0;r<=n;r++)for(int i=0;i<=n;i++){
        if(dp[l][r][i][0]!=0x3f3f3f3f || dp[l][r][i][1]!=0x3f3f3f3f)
            ans=max(ans,i);
    }
    printf("%d\n",ans);
    return 0;
}
```

~~（P.S. 刚把程序写出来的时候区间左端点的变量名`l`和周长`l`重名了，调了半节课才发现，遂把周长改成了`m`~~

这道题给了我们一个新的思路，就是如果某个状态不好表示，可以把状态变成值，所求变为下标，最后扫描一遍$dp$统计答案。

---

## 作者：天南地北 (赞：9)

## 思路:区间DP

#### 确立状态

首先，从顺时针和逆时针取一个雕像是不一样的状态，所以，前两维$[l][r]$指的是左边和右边分别取雕像的个数

但是取到雕像不代表这个雕像没有炸，所以我们要多加一个维度$[k]$，代表我取到没有炸的雕像的个数。

最后由于我们并不知道我们是往左边跑还是往右边跑，所以我们又要知道$[0/1]$即方向。

经过上述，我们最终确立状态$f[l][r][k][0/1]$为左边取到$l$个和右边$r$个，最终取到$k$个不炸的雕像，且在左边/右边的时间

#### 推倒公式

首先，$l$和$r$和$k$明显可以通过三重循环枚举。

接下来考虑跑左右两边的情况：

- 对于在左边，继续往左边走为
  
  $f[l+1][r][k+(tmp+num[n-l+1]-num[n-l]<=t[n-l])[0]=min\begin{cases}f[l+1][r][k+(tmp+num[n-l+1]-num[n-l]<=t[n-l])][0]\\tmp+num[n-l+1]-num[n-l]\end{cases}$

- 对于在左边，反过来往右边走为
  
  $f[l][r+1][k+(tmp+L-num[n-l+1]+num[r+1]<=t[r+1])][1]=min\begin{cases}f[l][r+1][k+(tmp+L-num[n-l+1]+num[r+1]<=t[r+1])][1]\\tmp+L-num[n-l+1]+num[r+1]\end{cases}$
  
- 对于在右边，反过来往左边走为
  
  $f[l+1][r][k+(tmp+L-num[n-l]+num[r]<=t[n-l])][0]=min\begin{cases}f[l+1][r][k+(tmp+L-num[n-l]+num[r]<=t[n-l])][0]\\tmp+L-num[n-l]+num[r]\end{cases}$

- 对于在右边，继续往右边走为
  
  $f[l][r+1][k+(tmp+num[r+1]-num[r]<=t[r+1])][1]=min\begin{cases}f[l][r+1][k+(tmp+num[r+1]-num[r]<=t[r+1])][1]\\tmp+num[r+1]-num[r]\end{cases}$
  
其中，前两种的$tmp$为$f[l][r][k][0]$，后两种的$tmp$为$f[l][r][k][1]$，$num$指的是每个雕像的位置，$t$指的是每个雕像的爆炸时间。（公式的其他部分可以手推，认真看就能理解）

#### 求解答案

关于最后的答案，其实很明显，我们枚举$l$和$r$和$k$，只要$f[l][r][k][0]$或$f[l][r][k][1]$不是临界值（就是初始化的值）就比大小，求出最大的$k$即可

算法复杂度$O(n^3)$

#### 参考程序
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++) 
#define drep(i,a,b) for(int i=a;i>=b;i--) 
using namespace std;
const int maxn=200+10;
int n,L,ans;
int num[maxn],t[maxn],f[maxn][maxn][maxn][2];
signed main()
{
	std::ios::sync_with_stdio(false);
	cin>>n>>L;
	rep(i,1,n)
		cin>>num[i];
	num[n+1]=L;//初始化
	rep(i,1,n)
		cin>>t[i];
	memset(f,0x3f,sizeof f);
	f[0][0][0][0]=f[0][0][0][1]=0;//初始化
	rep(l,0,n)
		rep(r,0,n)
		{
			if(l+r>=n)break;
			rep(k,0,n)
			{
				int tmp=f[l][r][k][0];
				if(tmp<=1e13)//只要状态是存在的，就可以更新答案
				{
					f[l+1][r][k+(tmp+num[n-l+1]-num[n-l]<=t[n-l])][0]=min(f[l+1][r][k+(tmp+num[n-l+1]-num[n-l]<=t[n-l])][0],tmp+num[n-l+1]-num[n-l]);
					f[l][r+1][k+(tmp+L-num[n-l+1]+num[r+1]<=t[r+1])][1]=min(f[l][r+1][k+(tmp+L-num[n-l+1]+num[r+1]<=t[r+1])][1],tmp+L-num[n-l+1]+num[r+1]);
				}
				tmp=f[l][r][k][1];
				if(tmp<=1e13)//只要状态是存在的，就可以更新答案
				{
					f[l+1][r][k+(tmp+L-num[n-l]+num[r]<=t[n-l])][0]=min(f[l+1][r][k+(tmp+L-num[n-l]+num[r]<=t[n-l])][0],tmp+L-num[n-l]+num[r]);
					f[l][r+1][k+(tmp+num[r+1]-num[r]<=t[r+1])][1]=min(f[l][r+1][k+(tmp+num[r+1]-num[r]<=t[r+1])][1],tmp+num[r+1]-num[r]);
				}
			}
		}
	rep(i,0,n)
		rep(j,0,n)
			rep(k,0,n)
				if(min(f[i][j][k][0],f[i][j][k][1])<1e15)
					ans=max(ans,k);//比较最大值
	printf("%lld\n",ans);
	return 0;
}
```
本题难点：记录表达状态，以及动态规划方程长，容易写挂,
$k$状态的表达，转化……


---

## 作者：licn (赞：9)

## **类似思考**

看到这道题会想到 [P1220 关路灯](https://www.luogu.com.cn/problem/P1220)，是一个 **区间 DP** ，这类区间 DP 是不需要枚举断点的，一般的转移方程是 $f_{i,j}=\min(f_{i+1,j},f_{i,j-1})$ 具体需要看情况而加减或乘除某个数。

------------

## **题目分析**

### **第一步：破环为链**

在一个环上，要转换成线性的，那么我们先要 **破环为链** ，相当于更简化的枚举断点。

还要将起点加入到这个数组中，将爆炸时间赋值为 $-1$ 就不会把它考虑最终的答案中。


------------

### **第二步：定义状态**

我们先考虑一般的二维数组 $f_{i,j}$ 为区间 $i,j$ 中最多能取几个。因为雕像会爆炸，那么我们不一定能将 $i,j$ 这个区间的所有雕像都拿完，没有办法计算能取几个，所以二维的不行。我们要考虑在 $i,j$ 这个区间中到底取了几个。从而来枚举这个个数。

那么我们加上一维变成 $f_{i,j,k}$ 表示在区间 $i,j$ 中取 $k$ 个最少需要的时间。显然通过枚举 $k$ 最后再判断能否成立。

但是在一个区间中位置有两种情况，一种是在区间的最左端，一种是在区间的最右端。用 $0/1$ 分别表示最左或最右。

最终定义的状态是 $f_{i,j,k,0/1}$ 表示在区间 $i,j$ 中最后到区间的最左端或最右端时拿 $k$ 个雕像最少需要的时间。



------------


### **第三步：寻找状态转移方程**

($a_i.x$ 表示点 $i$ 的位置，$a_i.t$ 表示点 $i$ 的爆炸时间)
首先我们考虑如果到达区间 $i,j$ 两端时，雕像已经爆炸的情况。那么取的个数相对于区间 $i+1,j$ 和 $i,j-1$ 不变,也就是 $k$ 的值不变，由此推出：

**第一个**:$f_{i,j,k,0}=\min(f_{i,j,k,0},f_{i+1,j,k,0}+a_{i+1}.x-a_i.x)$

**第二个**:$f_{i,j,k,0}=\min(f_{i,j,k,0},f_{i+1,j,k,1}+a_{j}.x-a_i.x)$

**第三个**:$f_{i,j,k,1}=\min(f_{i,j,k,1},f_{i,j-1,k,1}+a_{j}.x-a_{j-1}.x)$

**第四个**:$f_{i,j,k,1}=\min(f_{i,j,k,1},f_{i,j-1,k,0}+a_{j}.x-a_{i}.x)$

但是还有其他情况。当到达区间 $i,j$ 两端时，雕像没有爆炸的情况。那么取的个数相对于区间 $i+1,j$ 和 $i,j-1$ 增加了一个，也就是 $k$ 的值增加了 $1$。

由此推出（如果爆炸了就不考虑下列情况）：

**第五个**:

当 $(f_{i+1,j,k-1,0}+a_{i+1}.x-a_i.x)\leq a_i.t$ 时

$f_{i,j,k,0}=\min(f_{i,j,k,0},f_{i+1,j,k-1,0}+a_{i+1}.x-a_i.x))$

**第六个**:

当 $(f_{i+1,j,k-1,1}+a_j.x-a_i.x)\leq a_i.t$ 时

$f_{i,j,k,0}=\min(f_{i,j,k,0},f_{i+1,j,k-1,1}+a_j.x-a_i.x)$

**第七个**:

当 $(f_{i,j-1,k-1,1}+a_j.x-a_{j-1}.x)\leq a_j.t$ 时

$f_{i,j,k,1}=\min(f_{i,j,k,1},f_{i,j-1,k-1,1}+a_j.x-a_{j-1}.x)$

**第八个**:

当 $(f_{i,j-1,k-1,0}+a_j.x-a_i.x)\leq a_j.t$ 时

$f_{i,j,k,1}=\min(f_{i,j,k,1},f_{i,j-1,k-1,0}+a_j.x-a_i.x)$


------------

### **第四步： 起点（初始化）**

对于这道题，起点是确定的，但是我们要注意初始化的问题。

显然我们在枚举 $k$ 的过程中发现需要用到 $k$ 为 $0$ 时的区间时间。那么我们将 $k$ 为 $0$ 时的所有区间赋值。如果在左端点值为：周长 $-a_i.x$,如果在右端点值为：$a_j.x-$ 周长。（切记，虽然取得个数为 $0$，但是也需要将整个区间走完，不能取最小值）

还要将 $f$ 数组赋成最大值。从而为取最小值和判断是否成立做准备。但是要将原点的都赋为 $0$。

------------
### **第五步：终点**
这道题的终点比较特别，是判断时间是否小于最大值而确定这个 $k$ 是否能取到。如果能取到就更新 $ans$ 的最大值，最后输出 $ans$。


------------

## **完整代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=410;
int n,m,f[N][N][210][2],ans;//定义状态
struct que
{
	int x,t;
}a[N];//距离和爆炸时间
signed main(){
	cin>>n>>m;//个数和周长
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x;
		a[i+n+1].x=a[i].x+m;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].t;
		a[i+n+1].t=a[i].t;
	}//破环为链
	memset(f,0x3f,sizeof(f));
	a[n+1].x=m,a[n+1].t=-1e18,f[n+1][n+1][0][0]=0,f[n+1][n+1][0][1]=0;//加入起点
	for(int j=n+1;j<=2*n+1;j++)
	{
		for(int i=n+1;j&&j-i<=n;i--)
		{
			f[i][j][0][0]=m-a[i].x;
			f[i][j][0][1]=a[j].x-m;
		}
	}//初始化
	for(int len=1;len<=n;len++)//从小往大，按顺序
	{
		for(int i=1;i<=n+1;i++)//枚举左端点
		{
			int j=i+len;
			for(int k=1;k<=len;k++)//枚举个数
			{
				int s1;
				f[i][j][k][0]=min(f[i][j][k][0],f[i+1][j][k][0]+a[i+1].x-a[i].x);
				s1=f[i+1][j][k-1][0]+a[i+1].x-a[i].x;
				if(s1<=a[i].t)f[i][j][k][0]=min(f[i][j][k][0],s1);
				f[i][j][k][0]=min(f[i][j][k][0],f[i+1][j][k][1]+a[j].x-a[i].x);
				s1=f[i+1][j][k-1][1]+a[j].x-a[i].x;
				if(s1<=a[i].t)f[i][j][k][0]=min(f[i][j][k][0],s1);
				f[i][j][k][1]=min(f[i][j][k][1],f[i][j-1][k][1]+a[j].x-a[j-1].x);
				s1=f[i][j-1][k-1][1]+a[j].x-a[j-1].x;
				if(s1<=a[j].t)f[i][j][k][1]=min(f[i][j][k][1],s1);
				f[i][j][k][1]=min(f[i][j][k][1],f[i][j-1][k][0]+a[j].x-a[i].x);
				s1=f[i][j-1][k-1][0]+a[j].x-a[i].x;
				if(s1<=a[j].t)f[i][j][k][1]=min(f[i][j][k][1],s1);
				if(f[i][j][k][0]<1e15)ans=max(ans,k);
				if(f[i][j][k][1]<1e15)ans=max(ans,k);//判断是否成立
			}//状态转移
		}
	}
	cout<<ans;
	return 0;
}

---

## 作者：红火恍惚cxy (赞：7)

[题目链接](https://www.luogu.com.cn/problem/P6879)  
题目足够简短，这里就不再重复了。  
## 题目分析
看完题目第一件事一定是看数据范围。$n\leq200$，再加上环上问题，基本可以确定是 DP 或者记忆化搜索。  
我这里选择了 DP 的思路。  

仔细想想，发现如果我们经过了一个黑白熊雕像，我们一定会尝试把它拿走，所以我们尝试拿走的雕像在环上**一定是连续的**。而且当我们尝试拿走一个黑白熊雕像的时候，我们一定位于这段**连续区间的两个端点**。因为在中间的黑白熊雕像一定在我们之前经过它时已经拿走了。  
## 设计状态
我们可以用 $l$ 和 $r$ 表示我们尝试拿走的一段区间左端点和右端点。但因为有环的存在并不好处理，所以我将环**从起点位置断开**，$l$ 表示取走 $[1,l]$ 位置上的雕像，$r$ 表示取走 $[r,n]$ 位置上的雕像。这样就将枚举的区间分成了两部分，而在计算时只需要保证 $l<r$ 即可**避免重复计算**。  
我们还需要再加上一维状态 $opt$，$opt=0$ 表示我们位于区间的左侧，$opt=1$ 表示我们位于区间的右侧。  

再看一眼数据范围，这道题并**不允许我们将时间设计在状态当中**。既然无法设计到状态当中，又必须考虑时间带来的限制，那我们不妨把它作为 DP 值，把获得了几座雕像 $k$ 记录为状态。  

## 转移方程
每一个状态 $dp_{k,l,r,opt}$ 只有两种可以转移到的目标状态。  
设 $m$ 为周长，$whe_i$ 和 $tim_i$ 表示第 $i$ 个雕像位置与消失时间，$sum$ 为能否拿走当前雕像，若到达时间小于等于消失时间，$sum \gets 1$，否则 $sum \gets 0$。  
* 当 $opt=0$ 时，即当前位于区间左端点处：  
1. 走到区间左端点左边的雕像处，到达时间为 $dp_{k,l,r,0}+whe_{l+1}-whe_l$，目标状态为 $dp_{k+sum,l+1,r,0}$。  
2. 走到区间右端点右边的雕像处，到达时间为 $dp_{k,l,r,0}+m-(whe_{r-1}-whe_l)$，目标状态为 $dp_{k+sum,l,r-1,1}$。  
* 当 $opt=1$ 时，即当前位于区间右端点处：  
1. 走到区间左端点左边的雕像处，到达时间为 $dp_{k,l,r,1}+m-(whe_{r}-whe_{l+1})$，目标状态为 $dp_{k+sum,l+1,r,0}$。  
2. 走到区间右端点右边的雕像处，到达时间为 $dp_{k,l,r,1}+whe_{r}-whe_{r-1})$，目标状态为 $dp_{k+sum,l,r-1,1}$。  

## 初末状态
初状态即为 $dp_{0,0,n+1,0} \gets 0$，$dp_{0,0,n+1,1} \gets 0$。  
答案为最大的 $k$ 使 $dp_{k,l,r,opt} \neq \text{inf}$。  

这样时间复杂度为 $O(n^3)$，足够通过本题。
## 代码
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
    int w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){w=(w<<1)+(w<<3)+(ch^48);ch=getchar();}
    return w;
}
int n,m,ans;
struct qwq{
    int whe,tim;
}a[205];
int dp[205][205][205][2];
int main(){
    n=read();
    m=read();
    for(int i=1;i<=n;++i) a[i].whe=read();
    for(int i=1;i<=n;++i) a[i].tim=read();
    a[n+1].whe=m;//方便计算两点距离
    memset(dp,0x3f,sizeof(dp));
    dp[0][0][n+1][0]=dp[0][0][n+1][1]=0;
    for(int k=0;k<=n;++k){
        for(int l=0;l<=n;++l){
            for(int r=n+1;r>=1;--r){
                if(l>=r-1) continue;//保证左右区间不重叠
                int sum=0;
                if(dp[k][l][r][0]<0x3f3f3f3f){
                    sum=dp[k][l][r][0]+a[l+1].whe-a[l].whe<=a[l+1].tim?1:0;
                    dp[k+sum][l+1][r][0]=min(dp[k+sum][l+1][r][0],dp[k][l][r][0]+a[l+1].whe-a[l].whe);
                    sum=dp[k][l][r][0]+m-(a[r-1].whe-a[l].whe)<=a[r-1].tim?1:0;
                    dp[k+sum][l][r-1][1]=min(dp[k+sum][l][r-1][1],dp[k][l][r][0]+m-(a[r-1].whe-a[l].whe));
                }
                if(dp[k][l][r][1]<0x3f3f3f3f){
                    sum=dp[k][l][r][1]+m-(a[r].whe-a[l+1].whe)<=a[l+1].tim?1:0;
                    dp[k+sum][l+1][r][0]=min(dp[k+sum][l+1][r][0],dp[k][l][r][1]+m-(a[r].whe-a[l+1].whe));
                    sum=dp[k][l][r][1]+a[r].whe-a[r-1].whe<=a[r-1].tim?1:0;
                    dp[k+sum][l][r-1][1]=min(dp[k+sum][l][r-1][1],dp[k][l][r][1]+a[r].whe-a[r-1].whe);
                }
            }
        }
    }
    for(int k=1;k<=n;++k){
        for(int l=0;l<=n;++l){
            for(int r=n+1;r>=1;--r){
                if(l>=r||k>l+n+1-r) continue;
                if(min(dp[k][l][r][0],dp[k][l][r][1])<0x3f3f3f3f){
                    ans=k;
                    break;//一点小优化
                }
            }
            if(ans==k) break;
        }
        if(ans!=k) break;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：Nuyoah_awa (赞：3)

### 题目大意
一个环上有 $n$ 个雕塑，每个雕塑在 $T_i$ 时间前可以被收集，请问最多能收集几个雕塑。

### 题目分析

看完题目，容易发现收集雕像总是先顺时针走一段，然后又逆时针走一段，如此往复，沿路收集。

于是很明显就是一个区间 DP。

环上 DP 不太好写，于是我们可以考虑拆环成链。

我们可以以我们在的点为断电拆开，于是我们就相当于站在这个链的最左段或者最右端。

对于状态，我们根据最基础的区间 DP，可以设 $f_{l,r}$ 表示从最左端向右走（即顺时针走）最右端为 $l$，从最右端向左走最左端为 $r$，最多可以收集多少个雕塑。

但是我们无法知道已用多少时间，于是我们可以改变状态为 $f_{l, r, i}$ 表示从最左端向右走最右端为 $l$，从最右端向左走最左端为 $r$，收集了 $i$ 个雕塑的最少时间。

但是当我们考虑转移的时候会发现，我们还需要知道它当前走到了最左段还是最右端，于是再加一位状态 $0/1$ 表示在 $l$ 处还是在 $r$ 处。

然后就是状态转移（不妨设不合法状态的值为 $+\infty$）。

对于每个状态的前继状态可能如下：

$$f_{l, r, i, 0/1} \begin{cases}f_{l-1, r, i/i-1, 0/1} \\ f_{l, r+1, i/i-1, 0/1}\end{cases}$$

画个图稍微推一下式子易得，如下是 $f_{l-1, r, i-1, 0} \to f_{l, r, i, 0}$ 的具体过程。

![P6879](https://s11.ax1x.com/2024/01/22/pFZ8JsJ.png)

如上图，我们需要走的是绿色部分，即 $X_l - X_{l-1}$。所以转移条件为 $f_{l-1, r, i-1, 0} + X_l - X_{l-1} \le T_l$。转移方程为 $f_{l, r, i, 0} = f_{l-1, r, i-1, 0} + X_l - X_{l-1}$。

其他转移同理，可以得出转移方程为：

$$f_{l, r, i, 0} = \min\begin{cases}f_{l-1, r, i-1, 0} + X_l - X_{l-1} & f_{l-1, r, i-1, 0} \neq +\infty  & f_{l, r, i-1, 0} + X_l - X_{l-1} \le T_l \\ f_{l-1, r, i, 0} + X_l - X_{l-1} \\ f_{l-1, r, i-1, 1} + L - X_r + X_l & f_{l-1, r, i-1, 1} \neq + \infty & f_{l-1, r, i-1, 1} + L - X_r + X_l \le T_l \\ f_{l-1, r, i, 1} + L - X_r + X_l\end{cases}$$

$$f_{l, r, i, 1} = \min\begin{cases}f_{l, r+1, i-1, 0} + L + X_l - X_r & f_{l, r+1, i-1, 0} \neq +\infty  & f_{l, r+1, i-1, 0} + L + X_l - X_r \le T_r \\ f_{l, r+1, i, 0} + L + X_l - X_r \\ f_{l, r+1, i-1, 1} - X_r + X_{r+1} & f_{l, r+1, i-1, 1} \neq + \infty & f_{l, r+1, i-1, 1} - X_r + X_{r+1} \le T_r \\ f_{l, r+1, i, 1} - X_r + X_{r+1}\end{cases}$$

对于初值，假设所有状态最开始都是不合法的，设为 $+\infty$。则 $f_{l,r,0,1} = L - X_r + 2 \times X_l,f_{l, r, 0, 0} = 2 \times (L-X_r) + X_l$。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long

using namespace std;

const int N = 2e2 + 5, INF = 1e18 + 5;
struct node{
    int x, t;
}p[N];
int n, L, f[N][N][N][2], ans;

bool cmp_x(node u, node v){return u.x < v.x;}

signed main()
{
    scanf("%lld %lld", &n, &L);
    for(int i = 2;i <= n + 1;i++)
        scanf("%lld", &p[i].x);
    for(int i = 2;i <= n + 1;i++)
        scanf("%lld", &p[i].t);
    sort(p + 2, p + n + 2, cmp_x);
    for(int l = 0;l <= n + 3;l++)
        for(int r = n + 3;r >= l;r--)
            for(int i = 0;i <= n + 1;i++)
                f[l][r][i][0] = f[l][r][i][1] = INF;
    p[1].x = 0, p[n+2].x = L;
    for(int l = 1;l <= n + 2;l++)
    {
        for(int r = n + 2;r > l;r--)
        {
        	f[l][r][0][1] = L + p[l].x - p[r].x + p[l].x;
        	f[l][r][0][0] = L + p[l].x - p[r].x + L - p[r].x;
            for(int i = 1;i <= n;i++)
            {
            	if(l != 1)
            	{
	                if(f[l-1][r][i-1][0] != INF && f[l-1][r][i-1][0] + p[l].x - p[l-1].x <= p[l].t)
	                    f[l][r][i][0] = min(f[l][r][i][0], f[l-1][r][i-1][0] + p[l].x - p[l-1].x);
	                f[l][r][i][0] = min(f[l][r][i][0], f[l-1][r][i][0] + p[l].x - p[l-1].x); 
					if(f[l-1][r][i-1][1] != INF && f[l-1][r][i-1][1] + L - p[r].x + p[l].x <= p[l].t)
	                    f[l][r][i][0] = min(f[l][r][i][0], f[l-1][r][i-1][1] + L - p[r].x + p[l].x);
	                f[l][r][i][0] = min(f[l][r][i][0], f[l-1][r][i][1] + L - p[r].x + p[l].x);
				}
                //1
                if(r != n + 2)
                {
	                if(f[l][r+1][i-1][0] != INF && f[l][r+1][i-1][0] + L + p[l].x - p[r].x <= p[r].t)
	                    f[l][r][i][1] = min(f[l][r][i][1], f[l][r+1][i-1][0] + L + p[l].x - p[r].x);
	                f[l][r][i][1] = min(f[l][r][i][1], f[l][r+1][i][0] + L + p[l].x - p[r].x);
	                if(f[l][r+1][i-1][1] != INF && f[l][r+1][i-1][1] + p[r+1].x - p[r].x <= p[r].t)
	                    f[l][r][i][1] = min(f[l][r][i][1], f[l][r+1][i-1][1] + p[r+1].x - p[r].x);
	                f[l][r][i][1] = min(f[l][r][i][1], f[l][r+1][i][1] + p[r+1].x - p[r].x);
				}
                //2
                if(f[l][r][i][0] < INF || f[l][r][i][1] < INF)
                    ans = max(ans, i);
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：feecle6418 (赞：3)

设 $f_{l,r,k,0/1}$ 为左边走到 $l$，右边走到 $r$，收集了 $k$ 个，在左边/右边，的最小时间。

转移考虑 $f_{l,r}\to f_{l+1,r},f_{l,r+1}$。对于 $k$，就判断当前时间能否收集到 $a_l/a_{n-r+1}$，可以就转移到 $k+1$，否则转移到 $k$。

答案就枚举所有有值的 $f$，看 $k$ 的最大值即可。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,L,a[205],t[205],ans=0;
ll f[205][205][205][2];
void chk(ll &a,ll b){
	a=min(a,b);
}
int main(){
	cin>>n>>L,memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)cin>>a[i];
	a[n+1]=L;
	for(int i=1;i<=n;i++)cin>>t[i];
	f[0][0][0][0]=f[0][0][0][1]=0;
	for(int s=0;s+1<=n;s++){
		for(int i=0;i<=s;i++){
			int j=s-i;
			for(int k=0;k<=i+j;k++){
				ll w=f[i][j][k][0];
				chk(f[i+1][j][k+(w+a[i+1]-a[i]<=t[i+1])][0],w+a[i+1]-a[i]);
				chk(f[i][j+1][k+(w+a[i]+L-a[n-j]<=t[n-j])][1],w+a[i]+L-a[n-j]);
				w=f[i][j][k][1];
				chk(f[i+1][j][k+(w+L-a[n-j+1]+a[i+1]<=t[i+1])][0],w+L-a[n-j+1]+a[i+1]);
				chk(f[i][j+1][k+(w+a[n-j+1]-a[n-j]<=t[n-j])][1],w+a[n-j+1]-a[n-j]);
			}
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++)if(min(f[i][j][k][0],f[i][j][k][1])<1e15)ans=max(ans,k);
		}
	}
	cout<<ans;
}
```

---

## 作者：Mo默Sh笙 (赞：3)

### [传送门](https://www.luogu.com.cn/problem/P6879)

------------

思路前几篇题解都介绍了，这里着重介绍一个状态设计的小技巧。

在设计状态时，我们可能会碰到**状态数值过大，而dp数组内存的值较小**的情况。

例如在该题用 $dp_{l,r,t,0/1}$ 表示逆时针经过 $l$ 个，顺时针经过 $r$ 个，已经花费 $t$ 秒，所拿到的雕像个数，$0$ 表示当前在左端点，$1$ 表示在右端点。

但是 $T_{i}\leq10^9$，这样设计显然会爆空间。

注意到 $N\leq200$，我们可以**将状态和数组所存值互换**，用 $dp_{l,r,k,0/1}$ 表示拿 $k$ 个雕像所花费的时间，解决了状态数值爆空间的问题。

---

## 作者：Godzilla (赞：2)

### 题目大意：

环上有 $N$ 个点，给出从起点到 $N$ 个点的距离 ，环的周长，每移动 $1$ 个单位需要 $1$ 秒，每个点会在 $T_i$ 秒 **之后** 消失，求最多可以碰到多少个点。（起点不算）

### 思路：

动态规划。

发现 碰到的点或考虑过但是没碰到的点的集合必定为一个区间，因为如果不是一个区间，那么间隔的部分相当于路过但是没有碰到，这不符合最优解，而且结束后必然在区间左端点或者右端点，因为如果左端点和右端点先被碰到的话，相当于它们至中间隔的都碰到了，不符合假设。

状态中其实还要记录一个当前时间，能碰到的最多的点数，但是时间太大了，存不下，可以转换以下最优属性，变成村下碰到了 $k$ 个点需要的最少时间。

由于这是一个环，要转化成区间问题，就要破环为链，就是复制一份。

设 $f(j,i,k,0/1)$ 表示区间 $(i,j)$ 中碰到 $k$ 个点，当前在左端点或右端点的最少时间。

### 代码：

```c++
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

#define LL long long

using namespace std;

const int kN=205;
const int kInf=0x3f3f3f3f;

int n,l;
int x[2*kN],t[2*kN];
int f[2*kN][2*kN][kN][2];  
int ans;

int main(){
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;++i){
		scanf("%d",&x[i]);
		x[i+n+1]=x[i]+l;//将位置复制一份
	}
	for(int i=1;i<=n;++i){
		scanf("%d",&t[i]);
		t[i+n+1]=t[i];//将时间复制一份
	}
	memset(f,0x3f,sizeof f);
	t[n+1]=-kInf;x[n+1]=l;f[n+1][n+1][0][0]=f[n+1][n+1][0][1]=0;//初始化边界条件
    //n+1对应着起点
	for(int i=n+1;i<=(n<<1)+1;++i){
		for(int j=n+1;j&&i-j<=n;--j){
			f[j][i][0][0]=l-x[j];
			f[j][i][0][1]=x[i]-l;//初始化k=0的状态
		}
	}
	for(int i=n+1;i<=(n<<1)+1;++i){
		for(int j=n+1;j&&i-j<=n;--j){//保证区间<=n
			for(int k=1;k<=i-j;++k){
				f[j][i][k][0]=min(f[j][i][k][0],f[j+1][i][k][0]+(x[j+1]-x[j]));
				if(k&&f[j+1][i][k-1][0]+x[j+1]-x[j]<=t[j]){
					f[j][i][k][0]=min(f[j][i][k][0],f[j+1][i][k-1][0]+(x[j+1]-x[j]));
				}
				f[j][i][k][0]=min(f[j][i][k][0],f[j+1][i][k][1]+(x[i]-x[j]));
				if(k&&f[j+1][i][k-1][1]+x[i]-x[j]<=t[j]){
					f[j][i][k][0]=min(f[j][i][k][0],f[j+1][i][k-1][1]+(x[i]-x[j]));
				}
				f[j][i][k][1]=min(f[j][i][k][1],f[j][i-1][k][1]+(x[i]-x[i-1]));
				if(k&&f[j][i-1][k-1][1]+x[i]-x[i-1]<=t[i]){
					f[j][i][k][1]=min(f[j][i][k][1],f[j][i-1][k-1][1]+(x[i]-x[i-1]));
				}
				f[j][i][k][1]=min(f[j][i][k][1],f[j][i-1][k][0]+(x[i]-x[j]));
				if(k&&f[j][i-1][k-1][0]+x[i]-x[j]<=t[i]){
					f[j][i][k][1]=min(f[j][i][k][1],f[j][i-1][k-1][0]+(x[i]-x[j]));
				}
				if(f[j][i][k][0]<kInf){
					ans=max(ans,k);
				}
				if(f[j][i][k][1]<kInf){
					ans=max(ans,k);
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：lovely_hyzhuo (赞：2)

一道不错的区间 dp。

思路来源于机房大佬的分享（好像他写了题解）。

首先，对于环上问题，破环为链。

然后定义 $dp_{i,j,k,0/1}$ 表示当前区间为 $i,j$ 取了 $k$ 个雕像，最后在左端点还是右端点。

这样状态转移方程就显而易见了，由于其极其长（有八种，分爆炸了和没爆炸两大类情况），这里就只放两个，代码里有解释。

比如：$dp_{i,j,k,0}=\min(dp_{i+1,j,k,1}+|x_i-x_j|,dp_{i,j,k,0})$ 以及 $dp_{i,j,k,0}=\min(dp_{i+1,j,k,0}+|x_i-x_{i+1}|,dp_{i,j,k,0})$。

第一个意思大致是当前这个状态可以由 $i+1$ 转移过来，由于当前这个雕像已经爆炸，所以 $k$ 不用减一。

第二个意思是当前这个状态可以由 $i+1$ 转移过来，假设当前这个没有爆炸（需要判断），$k$ 就是从 $k-1$ 转移过来的。

这里重点说一下终点和初始化。

终点是取区间里能取到的 $k$ 的最大值。

而为 $dp_{i,j,0,0}=L-x_i$，其中，$L$ 表示周长，$x_i$ 表示位置；以及 $dp_{i,j,0,1}=x_j-L$。

但是要将原点的都赋为 $0$。

初始由于有些 $k$ 是取不到的并且保证后面取最小值要给 $dp$ 数组附极大值。

剩下不懂的看注释吧，注释很清晰了。

```cpp
#include<bits/stdc++.h>
#define int long long//可能时间很大 
using namespace std;
int n,L;
int dp[410][410][210][2];
const int N=1e16;//后面判断该状态是否可行 
struct node
{
	int x,t;
}a[410];//结构体存位置和爆炸事件 
signed main()
{
	cin>>n>>L;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x;
		a[i+n+1].x=a[i].x+L;//破环为链 
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].t;
		a[i+n+1].t=a[i].t;//同上 
	}
	a[0].x=0,a[n+1].x=L,a[0].t=0,a[n+1].t=0;//原点为零 
	memset(dp,0x7f,sizeof(dp));
	dp[n+1][n+1][0][0]=0,dp[n+1][n+1][0][1]=0;//加入起点 
	for(int j=n+1;j<=2*n+1;j++)
	{
		for(int i=n+1;j&&j-i<=n;i--)
		{
			dp[i][j][0][0]=L-a[i].x;
			dp[i][j][0][1]=a[j].x-L;//初始化 
		}
	}
	int ans=0;
	for(int len=1;len<=n;len++)//枚举长度 
	{
		for(int i=1;i<=n+1;i++)//枚举左端点 
		{
			int j=i+len;//右端点可以算出来 
			for(int k=1;k<=len;k++)//枚举多少个 
			{
				dp[i][j][k][0]=min(dp[i+1][j][k][1]+abs(a[i].x-a[j].x),dp[i][j][k][0]);
				dp[i][j][k][0]=min(dp[i+1][j][k][0]+abs(a[i].x-a[i+1].x),dp[i][j][k][0]);//对于这个状态可以由i+1和j两个点转移过来 
				dp[i][j][k][1]=min(dp[i][j-1][k][1]+abs(a[j].x-a[j-1].x),dp[i][j][k][1]);
				dp[i][j][k][1]=min(dp[i][j-1][k][0]+abs(a[i].x-a[j].x),dp[i][j][k][1]);//对于这个状态可以由i和j-1两个点转移过来 
				if(dp[i+1][j][k-1][0]+abs(a[i].x-a[i+1].x)<=a[i].t)
					dp[i][j][k][0]=min(dp[i+1][j][k-1][0]+abs(a[i].x-a[i+1].x),dp[i][j][k][0]);//统一解释，假如说该点没有爆炸，那么k应该减一，其余同上 
				if(dp[i+1][j][k-1][1]+abs(a[i].x-a[j].x)<=a[i].t)//假如没爆炸
					dp[i][j][k][0]=min(dp[i+1][j][k-1][1]+abs(a[i].x-a[j].x),dp[i][j][k][0]);
				if(dp[i][j-1][k-1][0]+abs(a[i].x-a[j].x)<=a[j].t)
					dp[i][j][k][1]=min(dp[i][j-1][k-1][0]+abs(a[i].x-a[j].x),dp[i][j][k][1]);
				if(dp[i][j-1][k-1][1]+abs(a[j-1].x-a[j].x)<=a[j].t)
					dp[i][j][k][1]=min(dp[i][j-1][k-1][1]+abs(a[j-1].x-a[j].x),dp[i][j][k][1]);
			}
		}
	}
	for(int len=n;len>=1;len--)//遍历所有区间取最大值 
	{
		for(int i=1;i<=n+1;i++)
		{
			int j=len+i;
			for(int k=len;k>=1;k--)
			{
				if(ans>=k)
					break;//类似于最优性剪枝 
				if(dp[i][j][k][1]<N||dp[i][j][k][0]<N)//假如该状态可行就取最大值 
				{
					ans=max(ans,k);
					break;//假如这个可行了，剩下的也没什么必要判断了 
				}
			}//多次取最大值 
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：under_the_time (赞：1)

## 题意

> 给定一个长度为 $L$ 的环和 $n$ 个物品 $\{X_n\}$，第 $i$ 的物品在距离出发点顺时针方向 $X_i$ 米处，且在 $T_i$ 秒后消失。$0$ 秒时你在出发点上，每一秒你可以选择顺时针或逆时针移动移动一米。求最多能获得多少个物品。

## 解法

考虑区间 dp。我们将答案和状态换一下，设 $f(l,r,k,0/1)$ 表示搞定了环上前 $l$ 个和环上后 $r$ 个，成功收集到了 $k$ 个，现在在出发点的顺时针侧还是逆时针侧，所花的最小时间。转移时各分两种决策：继续往下走，或者走到另一侧。我们可以令 $X_{n+1}=L$，对于当前枚举的区间 $[l,r]$，左侧的物品下标用 $(n-l+1)$ 表示，右侧的物品下标就用 $r$ 表示。初始值 $f(0,0,0,0)=f(0,0,0,1)=0$，其余正无穷；而边界即为 $l+r\le n$。

用三层循环分别枚举 $(l,r,k)$，则共有 $4$ 种情况（默认起点状态存在且合法）：

### 当前在左侧，继续往左走

即当前呆在第 $n-l+1$ 个物品上，继续搞定左侧第 $n-l+1-1=n-l$ 个物品。令 $dis=X_{n-l+1}-X_{n-l}$，则
$$
f(l+1,r,newK,0)\gets\min(f(l+1,r,newK,0),f(l,r,k,0)+dis)
$$
其中，如果走到新的物品 $x$ 上还没超时，可以拾取这个物品，即 $f(l,r,k,0)+dis\le T_{x}$（此时 $x=n-l$），则 $newK=k+1$；否则 $newK=k$​，下同。

### 当前在左侧，绕到右侧去

即当前呆在第 $n-l+1$ 个物品上，去到右侧搞定第 $r+1$ 个物品。令 $dis=L-X_{n-l+1}+X_{r+1}$，则
$$
f(l,r+1,newK,1)\gets\min(f(l,r+1,newK,1),f(l,r,k,0)+dis)
$$

### 当前在右侧，继续往右走

即当前呆在第 $r$ 个物品上，继续搞定右侧第 $r+1$ 个物品。令 $dis=X_{r+1}-X_r$，则
$$
f(l,r+1,newK,1)\gets\min(f(l,r+1,newK,1),f(l,r,k,1)+dis)
$$

### 当前在右侧，绕到左侧去

即当前呆在第 $r$ 个物品上，去到左侧搞定第 $n-l$ 个物品。令 $dis=L-X_{n-l}+X_r$，则
$$
f(l+1,r,newK,0)\gets\min(f(l+1,r,newK,0),f(l,r,k,1)+dis)
$$
最后找一个最大的 $k$ 使得存在至少一个包含它的合法状态即可。然而其实并不需要开 `long long`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 205;
int X[maxn],T[maxn];
int n,L;
int f[maxn][maxn][maxn][2];
const int inf = 1e9;
int main() {
    scanf("%d%d",&n,&L);
    for (int i = 1;i <= n;i ++)
        scanf("%d",&X[i]); X[n + 1] = L;
    for (int i = 1;i <= n;i ++)
        scanf("%d",&T[i]);
    for (int i = 0;i <= n;i ++)
        for (int j = 0;j <= n;j ++)
            for (int k = 0;k <= n;k ++)
                f[i][j][k][0] = f[i][j][k][1] = inf;
    f[0][0][0][0] = f[0][0][0][1] = 0;
    for (int l = 0;l <= n;l ++) for (int r = 0;r <= n;r ++) {
        if (l + r >= n) continue;
        for (int k = 0;k <= n;k ++) {
            int now = f[l][r][k][0];
            if (now < inf) {
                int dis = X[n - l + 1] - X[n - l];
                int newK = k + (dis + now <= T[n - l]);
                f[l + 1][r][newK][0] = min(f[l + 1][r][newK][0],now + dis);
                dis = L - X[n - l + 1] + X[r + 1];
                newK = k + (dis + now <= T[r + 1]);
                f[l][r + 1][newK][1] = min(f[l][r + 1][newK][1],now + dis);
            }
            now = f[l][r][k][1];
            if (now < inf) {
                int dis = X[r + 1] - X[r];
                int newK = k + (dis + now <= T[r + 1]);
                f[l][r + 1][newK][1] = min(f[l][r + 1][newK][1],now + dis);
                dis = L - X[n - l] + X[r];
                newK = k + (dis + now <= T[n - l]);
                f[l + 1][r][newK][0] = min(f[l + 1][r][newK][0],now + dis);
            }
        }
    }
    for (int k = n;k >= 0;k --)
        for (int l = 0;l <= n;l ++)
            for (int r = 0;r <= n;r ++)
                if (min(f[l][r][k][0],f[l][r][k][1]) < inf) {
                    printf("%d",k);
                    return 0;
                }
    return 0;
}
```

有幸成为最优解榜一！

![](https://cdn.luogu.com.cn/upload/image_hosting/2xai7ipc.png)

---

## 作者：djh0314 (赞：1)

[**传送门**](https://www.luogu.com.cn/problem/P6879)。
## 前置知识

区间 dp。

## 题意

一个周长为 $L$ 的圆，在初始点的顺时针方向依次排列着 $N$ 物品，第 $i$ 个物品在顺时针 $X_i$ 米处，可以在 $T_i$ 前收集到这个物品。

此时，从初始点出发，时间为 $0$，允许顺时针或逆时针移动，问最多可以收集到多少物品。

## 分析

首先考虑部分分，我们不可能在两个结点左右徘徊，假如现在开始行走，那么我们至少要一个方向走到一个结点，否则我们就在徘徊的时候就是在浪费时间。

这也就代表了，我们所行走的路程，必然是两个结点中间的这一段连续的空间，而由于我们是一个圆上的区间，因此我们考虑使用区间 DP 并且拆环成链来解决。

这时，我们又有了一个问题，那就是我们的物品只能在 $T_i$ 的时间内到达才可以拾取当前物品，我们该如何维护选取的个数与时间。

其实问题远没有想的那么麻烦，我们从数据范围出手，$n\le 200$，在时间复杂度上，支持 $n^3$ 以至于玄学 $n^4$，空间上，我们 $1GB$ 足以 $n^3$，因此直接再开一维来维护获取的物品量。

总结一下我们的 dp 数组：$f_{L,R,k,0/1}$ 表示当前的最左曾到达 $L$，最右到达 $R$，获取了 $k$ 个物品，当前位于左端点亦或是右端点。

考虑转移，对于 $f_{L,R,k,0/1}$，必然是从 $f_{L+1,R}$ 转移而来，只需要左走左，右走右，维护是否可以拾取，在将左右互相维护即可。

下面给出转移：
~~~cpp
for(int k=0; k<=n; ++k) {
	int t=f[L+1][R][k][0]+lenth(a[L+1].x,a[L].x),opt=k+(t<=a[L].t);
	f[L][R][opt][0]=min(f[L][R][opt][0],t);
	f[L][R][opt][1]=min(f[L][R][opt][1],f[L][R][opt][0]+lenth(a[R].x,a[L].x));
	t=f[L][R-1][k][1]+lenth(a[R].x,a[R-1].x),opt=k+(t<=a[R].t);
	f[L][R][opt][1]=min(f[L][R][opt][1],t);
	f[L][R][opt][0]=min(f[L][R][opt][0],f[L][R][opt][1]+lenth(a[R].x,a[L].x));
}
for(int k=0; k<=n; ++k) if(f[L][R][k][0]<INF||f[L][R][k][1]<INF) ans=max(ans,k);
~~~

对于初始化，直接走 $n$ 或 $n+1$（拆换成链）即可。

总结起来这道题还是比较简单的，是一道区间 dp 的比较常规的题。

---

## 作者：Anonymely (赞：0)

显然走过的一定是一段区间，走完后一定在区间左右端点，而区间内的数不会连续考虑两次，这里的考虑指的是一个数只在第一次经过的时候决定拿不拿。

暴力的思路是 $f_{l,r,T,0/1}$ 表示当前走过区间 $[l,r]$，人在左/右，时间在 $T$，能拿的最大值。

发现 dp 的值很小，和状态交换一下，$O(n^3)$。

可以动态数组省空间。


```cpp
#include <bits/stdc++.h>
using namespace std;
#ifdef RE
#define _GLIBCXX_DEBUG
#define _GLIBCXX_ASSERTIONS
#endif
#ifndef ONLINE_JUDGE
#include "Debug.h"
#else
#define debug(x, ...) 0
#endif

#define QwQ01AwA return 0
#define uint unsigned int
#define i128 __int128
#define i64 long long
#define u64 unsigned long long
#define dbg(fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)
#define file(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> bool ckmax(T &x, const T y) {return x < y ? (x = y, 1) : 0;}
template <typename T> bool ckmin(T &x, const T y) {return y < x ? (x = y, 1) : 0;}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int n, L;
	cin >> n >> L;
	int m = 2 * n + 2;
	vector <int> x(m), t(m);
	x[0] = 0, x[n + 1] = L, t[0] = -1, t[n] = -1;
	for (int i = 1; i <= n; i++) cin >> x[i], x[i + n + 1] = x[i] + L;
	for (int i = 1; i <= n; i++) cin >> t[i], t[i + n + 1] = t[i];
	vector < vector < vector < array <int, 2> > > > f;
	const int inf = 0x3f3f3f3f;
	f.resize(m);
	for (int i = 0; i < m; i++) {
		f[i].resize(i + n + 1);
		for (int j = i; j < i + n + 1; j++) {
			f[i][j].resize(j - i + 2);
			for (int k = 0; k <= j - i + 1; k++) {
				f[i][j][k][0] = f[i][j][k][1] = inf;
			}
		}
	}
	f[0][0][0][0] = f[0][0][0][1] = f[n + 1][n + 1][0][0] = f[n + 1][n + 1][0][1] = 0;
	for (int len = 1; len <= n; len++) {
		for (int l = 0, r = l + len - 1; r < m; l++, r++) {
			for (int k = 0; k <= r - l + 1; k++) {
				if (f[l][r][k][0] != inf) {
					if (l - 1 >= 0) {
						int T = f[l][r][k][0] + x[l] - x[l - 1];
						ckmin(f[l - 1][r][k + (t[l - 1] >= T)][0], T);
					}
					if (r + 1 < m) {
						int T = f[l][r][k][0] + x[r + 1] - x[l];
						ckmin(f[l][r + 1][k + (t[r + 1] >= T)][1], T);						
					}
				}
				if (f[l][r][k][1] != inf) {
					if (l - 1 >= 0) {
						int T = f[l][r][k][1] + x[r] - x[l - 1];
						ckmin(f[l - 1][r][k + (t[l - 1] >= T)][0], T);
					}
					if (r + 1 < m) {
						int T = f[l][r][k][1] + x[r + 1] - x[r];
						ckmin(f[l][r + 1][k + (t[r + 1] >= T)][1], T);						
					}
				}				
			}
		}
	}
	int ans = 0;
	for (int l = 0, r = n; r < m; l++, r++) {
		for (int k = r - l + 1; k >= 0; k--) {
			if (f[l][r][k][0] != inf || f[l][r][k][1] != inf) {
				ckmax(ans, k);
				break;
			}
		}
	}
	cout << ans << '\n';
	QwQ01AwA;
}
/*
g++ -o a a.cpp -O2 -Wall -Wextra -Wl,--stack=536870912 -D LOCAL
*/
```

---

## 作者：liugh_ (赞：0)

## [[JOI 2020 Final] 集邮比赛 3](https://www.luogu.com.cn/problem/P6879)

> 给定 $n$ 个物品在一个长度为 $L$ 的环上，给定 $X_i$ 表示起点与第 $i$ 个物品在顺时针方向上的距离，给定 $T_i$ 表示第 $i$ 个物品在 $T_i$ 时刻前取到才能造成贡献。初始时你在起点，时刻为 $0$，每次能向顺时针或逆时针方向移动 $1$ 单位长度，求能造成的最大贡献。
>
> $n\le 200$。

在一个环上顺时针逆时针走，自然想到破环为链，区间 dp（如果这个想不到就是做题太少了）。分析状态，只用 $f(l,r)$ 能做吗？很难，因为有一个时间限制，能到达一个物品不代表一定能造成它的贡献。所以，我们设 $f(l,r,k)$ 为区间 $[l,r]$ 中有 $k$ 个物品造成贡献，能做了吗？不行，转移时你怎么知道走完上一个区间后停在哪里呢？转移需要用到上一个位置到当前位置的距离啊！实际上，我们只需要设
$$f(l,r,k,0/1)$$
为区间 $[l,r]$ 中有 $k$ 个造成贡献，且走完后在此区间的左端点 / 右端点（即 $l/r$）处停留，**所需要的最小时间**。为什么不会在除 $l/r$ 之外的位置停留？因为如果物品在区间中间，在经过它时顺带取到不会更劣；如果不经过这个物品，就无法走完整个区间。

考虑转移。我们定义 $dis(x,y)$ 为在环上从 $x$ 走到 $y$ 的最短距离。首先强制让新点不造成贡献，但必须从上一个位置走到这个位置。于是有
$$f(l,r,k,0)=\min\{f(l+1,r,k,0)+dis(l,l+1),f(l+1,r,k,1)+dis(l,r)\}$$
$$f(l,r,k,1)=\min\{f(l,r-1,k,0)+dis(l,r),f(l,r-1,k,1)+dis(r-1,r)\}$$
接着，考虑**假定**当前区间左端点能造成贡献，而实际上能造成贡献的前提是到达左端点的时间不超过限制。于是有
$$t\gets\min\{f(l+1,r,k-1,0)+dis(l,l+1),f(l+1,r,k-1,1)+dis(l,r)\}$$
$$\texttt{if } t\le T_l \texttt{ then } f(l,r,k,0)\gets t$$
类似地，考虑右端点，有
$$t\gets\min\{f(l,r-1,k-1,0)+dis(l,r),f(l,r-1,k-1,1)+dis(r-1,r)\}$$
$$\texttt{if } t\le T_r \texttt{ then } f(l,r,k,1)\gets t$$
考虑初始化。首先将所有状态设为 $\infty$。此处我令总序列的中间为起点，向左走为逆时针转，向右走为顺时针转。于是我们令
$$
f(i,i,0,0)=f(i,i,0,1)=f(i,i,1,0)=f(i,i,1,1)=\left\{
\begin{aligned}
&L-X_i   &1\le i\le n \\
&X_{i-n} &n+1\le i\le 2n \\
\end{aligned}
\right.
$$
最后考虑统计答案，找到最大的 $k$ 使得 $\exist 1\le l<r\le 2n,f(l,r,k,0)\ne \infty \lor f(l,r,k,1)\ne \infty$ 即可。

时间复杂度 $O(n^3)$。

```cpp
#include<iostream>
#include<algorithm>
#include<cassert>
#include<list>
#include<vector>
#ifdef ONLINE_JUDGE
#define getchar() (_p==_q&&(_q=(_p=_b)+fread(_b,1,_s,stdin),_p==_q)?-1:*_p++)
#define putchar(x) ((_r-_o<_s)?(*_r++=x):(flush(),_r=_o,*_r++=x))
#endif
#define inline inline __attribute__((__always_inline__))
#define flush() (fwrite(_o,_r-_o,1,stdout),fflush(stdout))
using namespace std;const int _s=1<<20;char _b[_s],_o[_s],*_p=_b,*_q=_b,*_r=_o;template<class T>inline bool fr(T&x){x=0;char w=0;bool f=0;do{if((w=getchar())==-1)return 0;if(w=='-')f=1;}while(w<48||w>57);do {x=x*10+w-48;if((w=getchar())==-1)break;}while(w>47&&w<58);if(f)x=-x;return 1;}template<class T>inline void fw(T x){char _d[40],_l=-1;if(x<0)x=-x,putchar('-');do _d[++_l]=x%10+48;while(x/=10);do putchar(_d[_l]);while(~--_l);}

#define int long long
constexpr int maxn=400+5;
constexpr int inf=4e18;

int n,L,all,X[maxn],T[maxn];
int f[maxn][maxn][maxn][2];
#define f(a,b,c,d) f[a][b][c][d]
#define dis(x,y) min(abs(X[y]-X[x]),L-abs(X[y]-X[x]))

signed main(){
    fr(n),fr(L),all=n*2;
    int minX=inf;
    for(int i=1;i<=n;i++)fr(X[i]),X[i+n]=X[i],minX=min(minX,X[i]);
    for(int i=1;i<=n;i++)fr(T[i]),T[i+n]=T[i];
    for(int i=n+1;i<=all;i++)X[i]+=L;
    for(int l=1;l<=all;l++)for(int r=1;r<=all;r++)for(int k=0;k<=n;k++)f(l,r,k,0)=f(l,r,k,1)=inf;
    for(int i=1;i<=n;i++)
        if(L-X[i]<=T[i])f(i,i,0,0)=f(i,i,0,1)=f(i,i,1,0)=f(i,i,1,1)=L-X[i];
    for(int i=n+1;i<=all;i++)
        if(X[i-n]<=T[i])f(i,i,0,0)=f(i,i,0,1)=f(i,i,1,0)=f(i,i,1,1)=X[i-n];
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=all;l++){
            int r=l+len-1;
            for(int k=0;k<=n;k++){
                f(l,r,k,0)=min(f(l,r,k,0),min(f(l+1,r,k,0)+dis(l,l+1),f(l+1,r,k,1)+dis(l,r)));
                f(l,r,k,1)=min(f(l,r,k,1),min(f(l,r-1,k,0)+dis(l,r),f(l,r-1,k,1)+dis(r-1,r)));
            }
            for(int k=1,t;k<=n;k++){
                t=min(f(l+1,r,k-1,0)+dis(l,l+1),f(l+1,r,k-1,1)+dis(l,r));
                if(t<=T[l])f(l,r,k,0)=min(f(l,r,k,0),t);
                t=min(f(l,r-1,k-1,0)+dis(l,r),f(l,r-1,k-1,1)+dis(r-1,r));
                if(t<=T[r])f(l,r,k,1)=min(f(l,r,k,1),t);
            }
        }
    }
    for(int k=n;k>=1;k--)
        for(int len=k;len<=n;len++)
            for(int i=1;i+len-1<=all;i++)
                if(f(i,i+len-1,k,0)!=inf||f(i,i+len-1,k,1)!=inf)
                    {fw(k);goto ok;}
    putchar('0');ok:
    exit((flush(),0));
}
```

---

## 作者：masonpop (赞：0)

个人认为这题的状态设计颇具启发性。

首先注意到我们的行动是很随意的，从当前点 $x$ 出发可能走向任意位置。但是我们一定是在走的过程中，尽量拿走沿途能拿的雕像。因此我们可以拆分这个过程，**一次只将自己的行动范围扩大一步**，从而简化问题。

设 $f_{l,r,t,0/1}$ 表示当前走过的范围是顺时针 $l$ 个，逆时针 $r$ 个，收集到了 $t$ 个，且当前在位置 $0/1$（即在左边或右边）的最短时间。转移直接考虑向左扩展一步或向右扩展一步即可。具体实现参考代码。

复杂度 $O(n^3)$。[代码](https://www.luogu.com.cn/paste/p135kfnp)。

---

## 作者：Xiphi (赞：0)

参考了官方题解。

考虑 dp，设状态 $dp_{S,i,t}$ 表示所盖的邮票集合为 $S$，当前所在的为 $i$，印张数为 $t$ 的最短经过时间。这样状态就有 $O(2^n \times n^2)$ 个然后转移是 $O(n)$ 的。

考虑优化前面 $dp_{S,i}$ 的部分。发现要盖的区域总是连续的，故设状态 $dp_{l,r,t,op}$ 表示左端为第 $i$ 个盖章处，右端为第 $j$ 个盖章处，按下了 $t$ 个印章的最短时间，$op$ 表示现在位于左端还是右端，$op=0$ 表示在左边，$op=1$ 则表示在右边，状态数在 $O(n^3)$ 左右。

接下来考虑转移方程，过程中设 $dis(i,j)$ 表示两点距离，$op$ 表示能不能取到：

- 若走到左边，继续往左走，则到达时间为 $dp_{l,r,k,0}+X_{n-l+1}-X_{n-l}$。转移方程就是：$dp_{l+1,r,k+op,0}\gets dp_{l,r,k,0}+X_{n-l+1}-X_{n-l}$（和之前的要取 $\min$）。

- 若走到左边，继续往右走，则到达时间为 $dp_{l,r,k,0}+L-X_{n-l+1}+X_{r+1}$。转移方程就是 $dp_{l,r+1,k+op,1} \gets dp_{l,r,k,0}+L-X_{n-l+1}+X_{r+1}$ （和之前的要取 $\min$）。

- 若走到右边，继续往右走，则到达时间为 $dp_{l,r,k,1}+X_{r+1}-X_{r}$。转移方程是 $dp_{l,r+1,k+op,1} \gets dp_{l,r,k,1}+X_{r+1}-X_{r}$。

- 若走到右边，继续往左走，则到达时间为 $dp_{l,r,k,1}+X_{r}+L-X_{n-l}$。转移方程是 $dp_{l+1,r,k+op,0} \gets dp_{l,r,k,1}+X_{r}+L-X_{n-l}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,L,ans,t[205],x[205],dp[205][205][205][2];
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>L;
	for(int i=1;i<=n;++i){
		cin>>x[i];
	}
	x[n+1]=L;
	for(int i=1;i<=n;++i) cin>>t[i];
	memset(dp,0x3f,sizeof dp);
	dp[0][0][0][0]=0;
	dp[0][0][0][1]=0;
	for(int l=0;l<=n;++l){
		for(int r=0;r<=n;++r){
			if(n<=l+r) break;
			for(int k=0;k<=n;++k){
				int op =dp[l][r][k][0],
					op1=dp[l][r][k][1];
				if(op<=1e12){
					int esp1=x[n-l+1]-x[n-l],
						esp2=L-x[n-l+1]+x[r+1];
					int Op0=(op+esp1<=t[n-l]);
					int Op1=(op+esp2<=t[r+1]);
					dp[l+1][r  ][k+Op0][0]=min(dp[l+1][r  ][k+Op0][0],op+esp1);
					dp[l  ][r+1][k+Op1][1]=min(dp[l  ][r+1][k+Op1][1],op+esp2);
				}
				if(op1<=1e12){
					int esp1=L-x[n-l]+x[r],
						esp2=x[r+1]-x[r];
					int Op0=(op1+esp1<=t[n-l]);
					int Op1=(op1+esp2<=t[r+1]);
					dp[l+1][r  ][k+Op0][0]=min(dp[l+1][r  ][k+Op0][0],op1+esp1);
					dp[l  ][r+1][k+Op1][1]=min(dp[l  ][r+1][k+Op1][1],op1+esp2);
				}
			}
		}
	}
	int ans=0;
	for(int i=0;i<=n;++i)
	for(int j=0;j<=n;++j)
	for(int k=0;k<=n;++k){
		if(min(dp[i][j][k][0],dp[i][j][k][1])<=1e15){
			ans=max(ans,k);
		}
	}
	cout<<ans;
	return 0;
}




```

---

## 作者：Tang_poetry_syndrome (赞：0)

## [P6879] スタンプラリー 3
### 思路
很明显的区间 DP，但是破环为链。  
首先解析为什么是区间 DP，首先因为往一个方向移动，却达不到一个目标，被动回头，显然不是最优解，因此最优情况下一定是一个目标至另一个目标的直线。  
然后将整个圆复制一遍，设 $n+1$ 为起始点，$i\le n$ 的点为逆时针旋转得到的，$i>n$ 的点为顺时针旋转得到的，达到破环为链的效果。  
再来推一下 DP 式子：我们先设 $dp_{l,i,j,op}(op\in1,0)$ 为在左端点为 $l$，区间长度为 $i+1$ 的区间中收集了 $j$ 个雕像，$op=0$ 代表往左，否则往右，达到这个状态的最小时间。  
首先一个状态定然要确定一个事件后，才能传导到其它状态，所以我们将除原点外其他位置初始化一个极大值，剩下进行特判，将在一个方向上无法传到，即左端点为 $1$ 或右端点为 $2\times n$，从一个点到另一个点仅能在到这个点的最小时间与移动到下一个点的时间和小于时间限制时完成，分类讨论向左或向右扩张即可，最后枚举每一种答案，选取可行的最大的个数。  
式子用 Latex 好难写，直接看代码吧·-·。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,j,k) for(register ll i=j;i<=k;++i)
#define g(i,j,k) for(register ll i=j;i>=k;--i)
#define pb push_back
void gtmin(ll x,ll &y){if(y>x)y=x;}
const int N=2e2+10;
const ll INF=(1ll<<53);
int n,l;
ll x[N<<1],t[N<<1],dp[N<<1][N][N][2];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0); 
	cin>>n>>l;
	f(i,1,n)cin>>x[i],x[i+n+1]=x[i]+l;
	f(i,1,n)cin>>t[i],t[i+n+1]=t[i];
	memset(dp,0x7f,sizeof dp);
	dp[n+1][0][0][1]=dp[n+1][0][0][0]=0;
	x[n+1]=l;
	f(i,0,n-1)
	{
		f(l,0,(n<<1)+1-i)
		{
			ll r=l+i;
			f(j,0,i)
			{
				if(dp[l][i][j][1]<INF)
				{
					if(l>=2)
					{
						ll tmp=dp[l][i][j][1]+x[l]-x[l-1];
						gtmin(tmp,dp[l-1][i+1][j+(tmp<=t[l-1])][1]);
					}
					if(r<=(n<<1))
					{
						ll tmp=dp[l][i][j][1]+x[r+1]-x[l];
						gtmin(tmp,dp[l][i+1][j+(tmp<=t[r+1])][0]);
					}
				}
				if(dp[l][i][j][0]<INF)
				{
					if(l>=2)
					{
						ll tmp=dp[l][i][j][0]+x[r]-x[l-1];
						gtmin(tmp,dp[l-1][i+1][j+(tmp<=t[l-1])][1]);
					}
					if(r<=(n<<1))
					{
						ll tmp=dp[l][i][j][0]+x[r+1]-x[r];
						gtmin(tmp,dp[l][i+1][j+(tmp<=t[r+1])][0]);
					}
				}
			}
		}
	}
	g(k,n,1)f(i,0,n)f(j,1,(n<<1)+1-i)if(min(dp[j][i][k][1],dp[j][i][k][0])<INF){cout<<k;return 0;}
	cout<<0;
	return 0;
}
```

---

## 作者：Exschawasion (赞：0)

前言：这样的环形区间 $\texttt{dp}$ 题不建议使用记忆化搜索，用循环计算反而更好调试。至少，本人初见本题时尝试了记忆化搜索，结果是失败了。

***

首先设计状态。不难想到可以用一个四元组表示：$(l,r,t,\text{pos})$。$l$ 和 $r$ 分别表示从当前位置开始向左向右各**达到**了多少个雕像的位置（注意，不是取走雕像），$t$ 表示当前已经花费的时间，$\text{pos}$ 表示当前所在的雕像位置。

不着急列转移方程，先对这个状态进行优化。$l,r,\text{pos}$ 都是 $n$ 级别的，$t$ 是 $T$ 级别的，总时间复杂度为 $O(n^3T)$，能拿到 $25$ 分。

考虑优化，很容易就能发现，状态中的 $\text{pos}$ 一维的取值范围其实不需要开到 $n$ 级别。因为当取走一个雕像（即发生状态转移）之后，位置肯定是在 $l$ 或者在 $r$。也就是说，使用 $0/1$ 就能区分开是在 $l$ 或者在 $r$ 了。于是，时间复杂度降低到 $O(2\times n^2T)$。

然而，$T \leq 10^9$，如果不把 $T$ 优化掉是很难通过本题的。可以发现，本题对时间**没有任何直接限制**，唯一的限制就是雕像的自毁时间。换句话说，受限的反而是**能取走的雕像数量**。调整一下状态的设计，用一个四元组 $(l,r,i,\text{pos})$ 来表示**在 $[l, r]$ 中取 $i$ 个雕像**所需的**最短**时间，就可以将效率瓶颈 $T$ 去除。

具体来说，我们反其道而行之。目标是最大雕像数量，我们却让状态来表示最少用时，在计算出所有的状态之后，再次遍历所有状态，取所有**有解**状态中 $i$ 的最大值即可。

以上是本题的第一个难点。第二个难点就是推导方程。设当前状态为 $(l,r,i,\text{pos})$，状态的**值**记为 $f(l,r,i,\text{pos})$：

- 当 $\text{pos}=0$ 时，可以转移到 $(l-1,r,i+\Delta,0)$，代价为 $x_{l}-x_{l-1}$、或转移到 $(l,r+1,i+\Delta,1)$，代价为 $x_{r+1}-x_{l}$；
- 当 $\text{pos}=1$ 时，可以转移到 $(l-1,r,i+\Delta,0)$，代价为 $x_{r}-x_{l-1}$、或转移到 $(l,r+1,i+\Delta,1)$，代价为 $x_{r+1}-x_{r}$；

引入了一个新的变量 $\Delta$，表示**取得雕像的变化量**，取值范围为 $0$ 或 $1$。当能取得一个新的雕像的时候，$\Delta=1$，此时：

- 当 $\text{pos}=0$ 时：

如果转移到 $(l-1,r,i+\Delta,0)$，则用时为 $t_0=f(l,r,i,0)+x_{l}-x_{l-1}$，当且仅当 $t_0 \leq t_{l-1}$ 时 $\Delta=1$；


如果转移到 $(l,r+1,i+\Delta,0)$，则用时为 $t_0=f(l,r,i,0)+x_{r+1}-x_{l}$，当且仅当 $t_0 \leq t_{r+1}$ 时 $\Delta=1$；

- 当 $\text{pos}=1$ 时：

如果转移到 $(l-1,r,i+\Delta,0)$，则用时为 $t_0=f(l,r,i,0)+x_{r}-x_{l-1}$，当且仅当 $t_0 \leq t_{l-1}$ 时 $\Delta=1$；


如果转移到 $(l,r+1,i+\Delta,0)$，则用时为 $t_0=f(l,r,i,0)+x_{r+1}-x_{r}$，当且仅当 $t_0 \leq t_{r+1}$ 时 $\Delta=1$；

转移需要取最小值，这是显然的：取得 $i$ 个雕像的用时越少，留给后面取更多雕像的用时便越多，具有决策包容性。所以 $f$ 的初始化应当是初始化到无穷大。

***

由于这是一个环形的 $\texttt{dp}$，需要破环为链。这里不需要倍长，只需要在 $n+1$ 处设置位置为 $L$ 即可（即转了一圈回到原处）。

最后，遍历所有状态空间，对于 $(l,r,i,\text{pos})$，如果 $f(l,r,i,\text{pos})$ 等于无穷大，说明该状态是不可达的；否则，说明该状态肯定可达，在可达状态中取 $i$ 的最大值即可。

***

时间复杂度变为 $O(n^3)$，通过本题是绰绰有余的了。关键代码如下：


```
signed main() {
    memset(f, 0x3f, sizeof(f)); // 初始化
    int n, length; scanf("%lld%lld", &n, &length);
    for(int i = 1; i <= n; i++) scanf("%lld", &x[i]);
    for(int i = 1; i <= n; i++) scanf("%lld", &t[i]);
    x[n + 1] = length; // 转一圈回到原处
    f[0][0][0][0] = f[0][0][0][1] = 0;

    for(int len = 0; len < n; len++) {
        for(int L = 0; L <= len; L++) {
			int R = len - L;
			for(int i = 0; i <= n; i++) { // 四种状态转移
				f[L + 1][R][i + ((f[L][R][i][0] + x[n - L + 1] - x[n - L]) <= t[n - L])][0] = min(f[L + 1][R][i + ((f[L][R][i][0] + x[n - L + 1] - x[n - L]) <= t[n - L])][0], f[L][R][i][0] + x[n - L + 1] - x[n - L]);
				f[L][R + 1][i + ((f[L][R][i][0] + length - (x[n - L + 1] - x[R + 1])) <= t[R + 1])][1] = min(f[L][R + 1][i + ((f[L][R][i][0] + length - (x[n - L + 1] - x[R + 1])) <= t[R + 1])][1], f[L][R][i][0] + length - (x[n - L + 1] - x[R + 1]));
				f[L + 1][R][i + ((f[L][R][i][1] + length - (x[n - L] - x[R])) <= t[n - L])][0] = min(f[L + 1][R][i + ((f[L][R][i][1] + length - (x[n - L] - x[R])) <= t[n - L])][0], (f[L][R][i][1] + length - (x[n - L] - x[R])));
				f[L][R + 1][i + ((f[L][R][i][1] + x[R + 1] - x[R]) <= t[R + 1])][1] = min(f[L][R + 1][i + ((f[L][R][i][1] + x[R + 1] - x[R]) <= t[R + 1])][1], f[L][R][i][1] + x[R + 1] - x[R]);
			}
		}
    }
    int ans = 0;
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= n; j++) {
			for(int k = 0; k <= n; k++) {
				if(f[i][j][k][0] != inf || f[i][j][k][1] != inf) { // 可达
					ans = max(ans, k);
				}
		    }
		}
	}
    printf("%lld", ans);
    return 0;
}
```

本题提供了一个新的 $\texttt{dp}$ 状态设计思路：当某一维的状态空间过大不便表示时，可以试着将状态的值和状态本身调换，最后再次遍历状态空间，根据可达性取得最优解。

***

后记：在教练的指导下，本人才通过了本题。几乎没有万能的方法，各种方法都需要掌握，各种经验都需要积累，这也许就是刷题的目的所在。

---

## 作者：LimpidSlirm (赞：0)

### 题意

周长为 $L$ 的环上有 $n$ 个点，给定 $pos_i$ 表示第 $i$ 个点的位置。每移动 $1$ 个单位需要 $1$ 秒，每个点会在 $time_i$ 秒**之后**消失，以 $pos=0$ 为起点，求最多可以碰到多少个点。

### Solution

先破环为链。显然可以设计状态 $dp_{l,r,t,opt}$ 表示左边最远到了第 $l$ 个点，右边最远到了第 $r$ 个点，当前花费时间为 $t$，$opt$ 分别表示当前在最左边 or 最右边最大能碰到的点数。

然而 $t$ 的值域过大，考虑如何优化空间。发现 $dp_{l,r,t,opt}$ 值最大为 $n$，考虑把 $ans$ 置为一维状态。转移方程很好写，设当前最左端为 $j$，最右端为 $i$，已经取了 $k$ 个，则有：

-   $dp_{j,i,k,0} \gets dp_{j+1,i,k,0}+pos_{j+1}-pos_j$
-   $dp_{j,i,k,0} \gets dp_{j+1,i,k,1}+pos_{i}-pos_j$
-   $dp_{j,i,k,1} \gets dp_{j,i-1,k,0}+pos_{i}-pos_j$
-   $dp_{j,i,k,1} \gets dp_{j,i-1,k,1}+pos_{i}-pos_{i-1}$
-   当 $dp_{j+1,i,k-1,0}+pos_{j+1}-pos_j \le time_j$ 时，$dp_{j,i,k,0} \gets dp_{j+1,i,k-1,0}+pos_{j+1}-pos_j$
-   当 $dp_{j+1,i,k-1,1}+pos_{i}-pos_j \le time_j$ 时，$dp_{j,i,k,0} \gets dp_{j+1,i,k-1,1}+pos_{i}-pos_j$
-   当 $dp_{j,i-1,k-1,0}+pos_{i}-pos_j \le time_i$ 时，$dp_{j,i,k,1} \gets dp_{j,i-1,k-1,0}+pos_{i}-pos_j$
-   当 $dp_{j,i-1,k-1,1}+pos_{i}-pos_{i-1} \le time_i$ 时，$dp_{j,i,k,1} \gets dp_{j,i-1,k-1,1}+pos_{i}-pos_{i-1}$

时间复杂度 $\mathcal{O}(n^3)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
int n,l,ans;
pair<int,int> val[410];
int dp[410][410][210][2];
int main(int argc,const char *argv[])
{
	n=read(),l=read();
	for(int i=1;i<=n;i++)
		val[i].first=read();
	for(int i=1;i<=n;i++)
		val[i].second=read();
	for(int i=0;i<=n;i++)
		val[n+i+1]=make_pair(val[i].first+l,val[i].second);
	memset(dp,0x3f,sizeof dp);
	dp[n+1][n+1][0][0]=dp[n+1][n+1][0][1]=0;
	for(int i=n+1;i<=n*2+1;i++)
	{
		for(int j=n+1;j!=0&&i-j<=n;j--)
		{
			dp[j][i][0][0]=l-val[j].first;
			dp[j][i][0][1]=val[i].first-l;
		}
	}
	for(int i=n+1;i<=2*n+1;i++)
	{
		for(int j=n+1;j>=1;j--)
		{
			if(i-j>n)
				break;
			for(int k=1;k<=i-j;k++)
			{
				dp[j][i][k][0]=std::min(dp[j][i][k][0],dp[j+1][i][k][0]+(val[j+1].first-val[j].first));
				dp[j][i][k][0]=std::min(dp[j][i][k][0],dp[j+1][i][k][1]+(val[i].first-val[j].first));
				dp[j][i][k][1]=std::min(dp[j][i][k][1],dp[j][i-1][k][0]+(val[i].first-val[j].first));
				dp[j][i][k][1]=std::min(dp[j][i][k][1],dp[j][i-1][k][1]+(val[i].first-val[i-1].first));
				if(dp[j+1][i][k-1][0]+(val[j+1].first-val[j].first)<=val[j].second)
					dp[j][i][k][0]=std::min(dp[j][i][k][0],dp[j+1][i][k-1][0]+(val[j+1].first-val[j].first));
				if(dp[j+1][i][k-1][1]+(val[i].first-val[j].first)<=val[j].second)
					dp[j][i][k][0]=std::min(dp[j][i][k][0],dp[j+1][i][k-1][1]+(val[i].first-val[j].first));
				if(dp[j][i-1][k-1][0]+(val[i].first-val[j].first)<=val[i].second)
					dp[j][i][k][1]=std::min(dp[j][i][k][1],dp[j][i-1][k-1][0]+(val[i].first-val[j].first));
				if(dp[j][i-1][k-1][1]+(val[i].first-val[i-1].first)<=val[i].second)
					dp[j][i][k][1]=std::min(dp[j][i][k][1],dp[j][i-1][k-1][1]+(val[i].first-val[i-1].first));
				if(dp[j][i][k][0]<0x3f3f3f3f)
					ans=std::max(ans,k);
				if(dp[j][i][k][1]<0x3f3f3f3f)
					ans=std::max(ans,k);
			}
		}
	}
	printf("%d",ans);
	return 0;
}

```



---

