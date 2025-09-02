# Grid Walk

## 题目描述

### 题意翻译
给定一个 $n\times n$ 的矩阵和两个正整数 $a$ 和 $b$，第 $i$ 行第 $j$ 列的权值 $c_{i,j}=\gcd(i,a)+\gcd(j,b)$，一开始你在点 $(1,1)$，你可以向右或者向下走，一直走到点 $(n,n)$。

你需要规划一条路径，使得从点 $(1,1)$ 走到点 $(n,n)$ 所经过的点的权值和 $\sum c_{i,j}$ 最小，输出这个最小值。

## 样例 #1

### 输入

```
4 2 4```

### 输出

```
21```

## 样例 #2

### 输入

```
10 210 420```

### 输出

```
125```

# 题解

## 作者：Chenhaoxuan (赞：4)

## [CF2038K Grid Walk](https://www.luogu.com.cn/problem/CF2038K)

### 题意简述

给定 $n\times n$ 的矩阵和两个正整数 $a$ 和 $b$，第 $i$ 行第 $j$ 列的权值 $c_{i,j}=\gcd(i,a)+\gcd(j,b)$，你需要从点 $(1,1)$ 走到点 $(n,n)$。只能向右或者向下走。求路径长度 $\sum c_{i.j}$ 的最小值。

对于所有数据，$1\le n,a,b\le 10^6$。

### 暴力做法

直接 dp 做。转移方程：$dp_{i,j}=\min(dp_{i-1,j},dp_{i,j-1})+\gcd(i,a)+\gcd(j,b)。$时间复杂度 $n^2\log n$。

### 正解做法

首先，容易发现 **每一行，每一列至少经过一次**。我们称这些代价为 **必须代价**，即：

$$
\sum_{i=1}^n \gcd(i,a) + \sum_{j=1}^n \gcd(j,b)
$$

计算它需要 $O(n\log n)$ 的时间复杂度。

称剩下的所有代价为 **选择代价**。容易发现，由于总路径长度为 $2n-1$，所以我们必须经过 $n-1$ 个多余行和 $n-1$ 个多余列。最好的情况当然是这 $2n-2$ 个选择代价全部为 $1$。

但是，这可能办到吗？

考虑在怎样的数字上行走会产生 $1$ 的贡献。显然需要满足 $i$ 与 $a$ 互质，$j$ 与 $b$ 互质。我们尽量让整个路径尽可能多地走过这样的点。

如果 $x$ 与 $a$ 互质，$y$ 与 $b$ 互质，那么我们可以构造一条 $(1,1)\to (1,y)\to (x,y)$（或 $(1,1)\to (x,1) \to (x,y)$）的路径，以 **选择代价均为 $1$ 的理论最优解** 到达 $(x,y)$。

设 $A$ 是小于 $n$ 的最大的与之互质的数，$B$ 是小于 $n$ 的最大的与之互质的数。那么点 $(1,1)$ 到点 $(A,B)$ 的选择代价就必然是 $(A-1)+(B-1)$。

### 补充两个证明

题解区的几篇题解，包括我也看了官解，似乎都没有提到这两个性质的证明。我来补充一下。

---

第一，**$(1,1)$ 到 $(n,n)$ 的最短路径必然经过 $(A,B)$**。也就是说，不存在一条路径不经过 $(A,B)$，且比经过 $(A,B)$ 的更优。

![](https://cdn.luogu.com.cn/upload/image_hosting/thcxukp2.png)

如图，标记为红色的点是选择代价为 $1$ 的点。显然，$a$ 与 $1,A$ 均互质，$b$ 与 $1,B$ 互质。那么用蓝色线连起来的区域形成了一个“包围圈”。

考虑暴力 dp 的过程。我们想要 dp 到“包围圈”内部的方格，必然不得不“突破包围圈”，即经过“包围圈”上的至少一个点。但任意“包围圈”上的点的最优解（即 dp 值）必然是沿着红色点一路走下来，故说明最优解必然经过点 $(A,B)$。

--- 

第二，**$\mathbf{n-A\le25,n-B\le25}$**。意思就是 $A$ 和 $B$ 距离 $n$ 应该不会很远（甚至是非常近）。

根据定义，$A$ 与 $a$ 互质，且 $(A+1)\sim n$ 的所有数字均不与 $a$ 互质。反证，假设存在超过连续 $26$ 个数字与 $a$ 不互质。

我们尝试找一些质因数来一一满足这些数字的需求。如果选定了一个质因数 $p$ 计入答案，则在对答案产生 $p$ 的贡献的同时，会让 **所有含有质因数 $p$，但还未满足要求的数字满足要求**。


显然，我们可以贪心地选择最小的质数开始。需要注意的是，尽管有些 $p_i$ 并不是任何尚存数字的因数，但是我们假定它是（即一换一，用它换掉一个大质数），这样必然比选择更大的质数更优。这是因为这样可能减少的数字更多，且使得答案尽可能小。

考虑如下枚举：

- 计入质因数 $p_1=2$，对答案产生 $2$ 的贡献，最多删去 $13$ 个数字，剩下 $13$ 个；

- 计入质因数 $p_2=3$，对答案产生 $3$ 的贡献，最多删去 $5$ 个数字，剩下 $8$ 个；

- 计入质因数 $p_3=5$，对答案产生 $5$ 的贡献，最多删去 $2$ 个数字，剩下 $6$ 个；
 
- 计入质因数 $p_4=7$，对答案产生 $7$ 的贡献，最多删去 $1$ 个数字，剩下 $5$ 个；

- 计入质因数 $p_5=11$，对答案产生 $11$ 的贡献，最多删去 $1$ 个数字，剩下 $4$ 个；

- 计入质因数 $p_6=13$，对答案产生 $13$ 的贡献，最多删去 $1$ 个数字，剩下 $3$ 个；

- 计入质因数 $p_7=17$，对答案产生 $17$ 的贡献，最多删去 $1$ 个数字，剩下 $2$ 个；

- 计入质因数 $p_8=19$，对答案产生 $19$ 的贡献，最多删去 $1$ 个数字，剩下 $1$ 个；

- 计入质因数 $p_9=23$，对答案产生 $23$ 的贡献，最多删去 $1$ 个数字，剩下 $0$ 个，结束。

可得 $a$ 至少为 $\prod p_i=223,092,870$，这远远超出了 $a\le10^6$ 的限制，矛盾。所以 $n-A\le 25$。

上述证明可能有不是很严谨的地方，我们只需要大致感受到它的正确性即可。不放心可以把范围放得大一些，这样肯定是正确的。

对 $B$ 同理。

---

至此，我们几乎已经完成了本题。在 $A\le i\le n,B\le j\le n$ 的部分，我们可以暴力 dp 完成，时间复杂度忽略不计。

### 小结

1. 统计出 **必须代价**。

2. 求出 $A$ 和 $B$。

3. 直接计入 $(1,1)$ 到 $(A,B)$ 的 **选择代价**。

4. 暴力 dp 出 $(A,B)$ 到 $(n,n)$ 的 **选择代价**。

时间复杂度 $O(n\log n)$。

### AC Code

方便起见，我们也可以只统计 $(1,1)$ 到 $(A,B)$ 的 **必须代价**，将其它 **必须代价** 放到后面的 dp 过程中直接计入。

代码中，使用 $x$ 代替了 $A$，使用 $y$ 代替了 $B$。

```c++
const int maxn = 1e6 + 10, maxm = 100;
int n, a, b, x, y;
long long sum, dp[maxm][maxm];
int main() {
	cin >> n >> a >> b;
	for (x = n; x >= 1; x--) {
		if (__gcd(x, a) == 1) break;
	}
	for (y = n; y >= 1; y--) {
		if (__gcd(y, b) == 1) break;
	}
	for (int i = 1; i <= x; i++) {
		sum += __gcd(i, a);  
	}
	for (int i = 1; i <= y; i++) {
		sum += __gcd(i, b);
	}
	memset(dp, 0x3f, sizeof dp);
	dp[1][1] = sum + (x - 1) + (y - 1);
	for (int i = x; i <= n; i++) {
		for (int j = y; j <= n; j++) {
			if (i == x && j == y) continue;
			dp[i - x + 1][j - y + 1] = min(dp[i - x][j - y + 1], dp[i - x + 1][j - y]) + __gcd(i, a) + __gcd(j, b);
		}
	}
	cout << dp[n - x + 1][n - y + 1];
	return 0;
}
```

记得开 long long，虽然其实卡不掉。

---

## 作者：_ZHONGZIJIE0608_ (赞：3)

给定一个 $n \times n$ 的网格图和两个整数 $a,b$。定义 $(i,j)$ 为第 $i$ 行第 $j$ 列的网格。

你从 $(1,1)$ 移动到 $(n,n)$。你可以向右或者向下移动。形式化地，你可以从 $(i,j)$ 移动到 $(i,j+1)$ 或 $(i+1,j)$，如果这些网格存在的话。

定义网格 $(i,j)$ 的花费为 $\gcd(i,a) + \gcd(j,b)$。你需要求出路径上网格的花费的和的最小值。

$ 2 \le n \le 10^6 ,1 \le a, b \le 10^6 $

首先打了个 $O(n^2)$ 的简单的 DP，找找规律。

**提示：** 显而易见，走横坐标和 $a$ 互质或者纵坐标和 $b$ 互质的网格是更优的，因为权值必定更小。

考虑计算从网格 $(1,1)$ 到网格 $(x,y)$ 的路径花费。

设 $P$ 表示网格 $(1,1)$ 到网格 $(x,y)$ 的一条路径，那么总花费就是：

$$C=\sum_{(i,j) \in P} \gcd(i,a)+\gcd(j,b)$$

观察样例的那一张图，我们发现对于有的网格，存在一条路径使得从 $(1,1)$ 到它们的路径上的权值只有 $2$ 和 $3$ 两种。

是不是很奇怪？

**提示：** 考虑一下如果横坐标和 $a$ 互质并且纵坐标和 $b$ 互质会发生什么。

令这个网格为 $(x,y)$，并且 $x,a$ 互质，$y,b$ 互质。

比如从 $(1,1)$ 到 $(3,5)$ 就有如下路径。

下面的代码框表示网格图，不在路径上的网格用 `X` 表示，在路径上的标出权值。

```
2 3 2 5 2
X X X X 3
X X X X 2
```

注意到此时最上方一行的横坐标部分贡献权值和最右边一行的纵坐标部分贡献的权值都是 $1$。我们减去这个部分。

```
1 2 1 4 0
X X X X 2
X X X X 1
```

$(1,y)$ 被减了两次。

我们是不是可以发现什么。

发现对于最上一行，$(1,j)$ 上的值就是 $\gcd(j,b)$。

对于最右一列 $(i,y)$ 上的值就是 $\gcd(i,a)$。

所以对于一个 $x,a$ 互质，$y,b$ 互质的网格，我们有

$$C=\sum_{j=1}^{y-1} \gcd(j,b) + \sum_{i=2}^{x} \gcd(i,a)+x+y$$

我们设 $dp_{x,y}$ 表示到达 $(x,y)$ 的最小花费。

于是我们找到小于 $n$ 的最大的和 $a$ 互质的数 $x$ 和与 $b$ 互质的最大的 $y$，然后 $O(n\log n)$ 找出 $dp_{x,y}$。

**提示：** 互质的数的密度是很大的。

所以说 $(x,y)$ 为左上角 $(n,n)$ 为右下角的矩形不会很大，平方级别的 DP 是可以接受的了。

我们直接暴力搞出 $dp_{n,n}$ 就行。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
unordered_map<int,int>dp[N];
int n,a,b,x,y,ans;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>a>>b;
	for(int i=n;i;--i)if(__gcd(a,i)==1){x=i;break;}
	for(int i=n;i;--i)if(__gcd(b,i)==1){y=i;break;}
	int ans=(x+y);
	for(int i=1;i<y;++i)ans+=__gcd(i,b);
	for(int i=2;i<=x;++i)ans+=__gcd(i,a);
	dp[x][y]=ans;
	for(int i=x+1;i<=n;++i){
		dp[i][y]=dp[i-1][y]+(__gcd(i,a)+__gcd(y,b));
	}
	for(int i=y+1;i<=n;++i)dp[x][i]=dp[x][i-1]+(__gcd(x,a)+__gcd(i,b));
	for(int i=x+1;i<=n;++i){
		for(int j=y+1;j<=n;++j){
			dp[i][j]=min(dp[i-1][j],dp[i][j-1])+(__gcd(i,a)+__gcd(j,b));
		}
	}
	cout<<dp[n][n];
	return 0;
}
```

---

## 作者：SJZ2010 (赞：1)

不知道为什么，别的题解都注意到了神奇的性质，我这种蒟蒻根本看不懂，于是来补一篇正常的题解。

考虑下路径。路径上有很多拐点。这些拐点确定路径的形态。

在走一条直的路时，比如往右，那 $(x, a)$ 要被算很多次。

而且我们注意到，有一些 $\gcd$ 是必须加上去的，比如上面说的 $\sum \gcd(j, b)$。

那我们就是要最优化被多算的哪些。

一个贪心的想法是，把 $\gcd$ 的后缀最小值取到的位置全记下来，然后右下右下轮流下去，然而写完假了，第二个样例都过不去。

hack 可能想不到，但是可以想象，路径不是一定轮流右下，可能是右右下之类，可见我们对路径的刻画不完整。

于是，我们得对这些位置做一个 DP，路径上的费用是容易计算的，不会看代码。

最后算一下复杂度：$O(d(a)d(b) \log n) = O(\sqrt{ab} \log n)$。远远跑不满。

[AC](https://codeforces.com/problemset/submission/2038/304194813)

---

## 作者：TTpandaS (赞：1)

首先每行每列都至少要走一次，所以这些花费是必不可少的，考虑额外花费最小。

找到最大的 $A,B$ 满足 $A,B \leq n$ 且 $\gcd(A,a)=\gcd(B,b)=1$，那么就可以在每次额外花费都为 $1$ 的情况下走到 $(A,B)$。因为 $a$ 要作为 $A+1$ 到 $n$ 的 $lcm$，而 $a \leq 10^6$，所以猜测 $n-A+1$ 不会很大，$n-B+1$ 同理，所以剩下部分直接 DP 即可。

实测开 $5000$ 可过。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5005;
int T=1;
int n,a,b;
int dp[N][N];
void solve(){
	cin>>n>>a>>b;
	int A,B;
	for(int i=n;i>=1;i--){
		if(__gcd(i,a)==1){
			A=i;
			break;
		}
	}
	for(int i=n;i>=1;i--){
		if(__gcd(i,b)==1){
			B=i;
			break;
		}
	}	
	int ans=(A-1)+(B-1);
	for(int i=1;i<=A;i++){
		ans+=__gcd(i,a);
	}	
	for(int j=1;j<=B;j++){
		ans+=__gcd(j,b);
	}
	for(int i=A;i<=n;i++){
		for(int j=B;j<=n;j++){
			if(i==A&&j==B){
				continue;
			}
			if(i>A&&j>B){
				dp[i-A+1][j-B+1]=min(dp[i-1-A+1][j-B+1],dp[i-A+1][j-1-B+1]);
			}
			else if(i>A){
				dp[i-A+1][j-B+1]=dp[i-1-A+1][j-B+1];
			}
			else if(j>B){
				dp[i-A+1][j-B+1]=dp[i-A+1][j-1-B+1];
			}
			dp[i-A+1][j-B+1]+=__gcd(i,a)+__gcd(j,b);
		}
	}
	cout<<ans+dp[n-A+1][n-B+1]<<endl;
}
signed main(){
//	cin>>T;
	while(T--){
		solve(); 
	}
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

提供一个不依赖于 $\gcd$ 的解法。

有固定贡献 $\sum\limits_{i=1}^n (\gcd(i,a)+\gcd(i,b))$。其余贡献是横向移动的 $\gcd(i,a)$ 和竖向移动 $\gcd(j,b)$。

设在第 $i$ 行横向移动的代价 $a_i=\gcd(i,a)$，在第 $i$ 列移动的代价是 $b_i=\gcd(j,b)$。求从 $(1,1)\to (n,n)$ 的最小代价。

考虑 $(l,x)\to(r,y)$ 的路径可以 $(l,x)\to (r,x)\to (r,y)$，也可以 $(l,x)\to (l,y)\to (r,y)$。

前者的代价是 $b_x(r-l)+a_r(y-x)$，后者的代价是 $a_l(y-x)+b_y(r-l)$。前者比后者更优需要满足

$$\dfrac{b_x-b_y}{x-y}<\dfrac{a_r-a_l}{r-l}$$

可以发现这可以放到两个凸包上求解。单调栈建立对于 $a,b$ 的凸包之后，每次选择斜率写的一边走。由于上述式子可以放到到任意局部，所以这是对的。

其实本质就是对于两个凸包进行闵可夫斯基和。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int n,m,A,B,a[maxn],b[maxn]; ll ans=0;
int sta[maxn],stb[maxn],ta,tb;
bool chk(int x1,int y1,int x2,int y2){ return 1ll*y1*x2<=1ll*y2*x1; }
bool cmpa(int x,int y,int z){ return chk(x-y,a[x]-a[y],y-z,a[y]-a[z]); }
bool cmpb(int x,int y,int z){ return chk(x-y,b[x]-b[y],y-z,b[y]-b[z]); }
bool cmpab(int w,int x,int y,int z){ return chk(w-x,a[w]-a[x],y-z,b[y]-b[z]); }
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>A>>B; m=n;
	for(int i=1;i<=n;i++) ans+=__gcd(A,i)+__gcd(B,i);
	for(int i=1;i<=n;i++) a[i]=__gcd(A,i);
	for(int i=1;i<=m;i++) b[i]=__gcd(B,i);
	sta[ta=1]=1; stb[tb=1]=1;
	for(int i=2;i<=n;i++){
		while(ta>1&&cmpa(i,sta[ta],sta[ta-1])) ta--;
		sta[++ta]=i;
	}
	for(int i=2;i<=m;i++){
		while(tb>1&&cmpb(i,stb[tb],stb[tb-1])) tb--;
		stb[++tb]=i;
	}
	int x=1,y=1;
	while(x<ta||y<tb){
		if(x==ta){
			ans+=1ll*(m-stb[y])*a[sta[x]];
			break;
		}
		if(y==tb){
			ans+=1ll*(n-sta[x])*b[stb[y]];
			break;
		}
		if(cmpab(sta[x+1],sta[x],stb[y+1],stb[y])){
			ans+=1ll*(sta[x+1]-sta[x])*b[stb[y]];
			x++;
		}else{
			ans+=1ll*(stb[y+1]-stb[y])*a[sta[x]];
			y++; 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Jelly_prx (赞：0)

## [CF2038K] Grid Walk



全队被 G 这个唐唐题卡了 1 个小时后才开的，感觉不是很难。

看到 $n$ 的范围很大，第一反应就是贪心。假设 $a \bot n \lor b\bot n$，那么我们一定是沿着边界走最优，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/c24bstjr.png)

知道这点之后我们考虑推广到 $a,b$ 均与 $n$ 不互质的情况。自然而然地，我们从 $n$ 往前扫分别找到第一个与 $a,b$ 互质的行和列，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/iv0a5bxa.png)

我们还是可以沿着红色路线走到最右下角的位置，然后对黄色部分的矩形暴力进行 dp。不难感受到矩形部分不会很大，所以复杂度是正确的。

让我们证明这样子为什么是对的：

![](https://cdn.luogu.com.cn/upload/image_hosting/he64df3c.png)

要想走到 $(n,n)$，紫色部分的格子是一定要经过的。因为紫色格子所在的行/列与 $a/b$ 互质，所以直接由红色格子走过来是最优的；而黄色部分的路径决策是我们暴力 dp 算出来的，正确性自然保证。

---

