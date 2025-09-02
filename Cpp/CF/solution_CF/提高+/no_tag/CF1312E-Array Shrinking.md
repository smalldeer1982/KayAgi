# Array Shrinking

## 题目描述

给你一个长度为 $n(1 \le n \le 500)$ 的数组 $a$，每次你可以进行以下两步操作：

1. 找到 $i \in [1, n)$，使得 $a_i = a_{i + 1}$；

2. 将 **它们** 替换为 $a_i + 1$。

每轮操作之后，显然数组的长度会减小 $1$，问剩余数组长度的最小值。

## 样例 #1

### 输入

```
5
4 3 2 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
7
3 3 4 4 4 3 3```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 3 5```

### 输出

```
3```

## 样例 #4

### 输入

```
1
1000```

### 输出

```
1```

# 题解

## 作者：C　C　A (赞：28)

# $CF1312E\ Array\ Shrinking's\ Solution$
						
$\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad By$ [$CCA$](https://www.luogu.com.cn/user/78645)

## $Problem$

$\qquad$给定一个数组，定义一次合并为对于两个相邻的数，如果他们相等，则可以将它们合并为一个数，其值为原数$+1$（参照$2048$）。问原数组合并完后的最小长度。

## $Solution$

$\qquad$这题十分套路。

$\qquad$我们考虑区间$DP$，令$dp[l][r]$表示$l$到$r$这段区间合并后的最小长度，同时，我们需要一个$w$数组来辅助计算，$w[l][r]$表示按照$dp[l][r]$合并完后，$l$到$r$这段区间的和是多少，转移很显然：

$$dp[l][r] = min\{dp[l][mid] + dp[mid + 1][r]\}$$

如果$dp[l][mid]=dp[mid + 1][r]=1$，并且$w[l][mid]=w[mid + 1][r]$，则：

$$dp[l][r] = 1 , w[l][r] = w[l][mid] + 1$$

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 500 + 10;

int n , a[N] , dp[N][N] , w[N][N];

int main(){
	memset(dp , 63 , sizeof(dp));
	scanf("%d" , &n);
	for(int i = 1; i <= n; i++)
		scanf("%d" , &a[i]) , dp[i][i] = 1 , w[i][i] = a[i];
	for(int k = 2; k <= n; k++)
		for(int l = 1; l + k - 1 <= n; l++){
			int r = l + k - 1;
			for(int mid = l; mid < r; mid++){
				dp[l][r] = min(dp[l][r] , dp[l][mid] + dp[mid + 1][r]);
				if(dp[l][mid] == dp[mid + 1][r] && dp[l][mid] == 1 && w[l][mid] == w[mid + 1][r])
					dp[l][r] = 1 , w[l][r] = w[l][mid] + 1;
			}
		}
	printf("%d" , dp[1][n]);
	return 0;
}
```

自认为码风还是比较清奇可看的，大家可以对着$Solution$仔细看一下。

最后，[$This\ is\ my\ blog$](https://www.luogu.com.cn/blog/A66-888/) , 有兴趣的可以逛一下，应该能有所收获。

---

## 作者：chen_qian (赞：13)

[题目链接](https://www.luogu.com.cn/problem/CF1312E)

这里有一个性质，就是对于一个区间$[l,r]$，如果它可以被缩成一个数，那么这个数是一定的。

知道了这个结论，我们要做就是，确定一个区间是否能合并成一个数，如果能，那么这个数是多少？

假设这个区间是$[l,r]$,
在本题中，很容易想到一个区间DP的思路，枚举一个中间点$k$。假如说，$[l,k]$与$[k+1,r]$都可以合成一个数$x$,那么$[l,r]$就可以合成一个数$x+1$了，这时就有一个无法回避的问题，就是我们必须要确定合成的数，这时一般有两种处理方式：

1.将这个数作为$dp$方程的一维，用枚举来确定

2.将其作为$dp$的目标

这里显然使用后者。所以设$f[l][r]$表示将区间$[l,r]$合成成一个数后其值为多少。$f[l][r]=0$就表示其不能合成一个数。

那么就有

$f[l][r]=f[l][k]+1 (f[l][k]=f[k+1][r]$)

简单区间$dp$即可

但是这并不是我们要求的答案。

不过既然我们都求出每个区间能不能合成一个数，那么就$dp[i]$表示$[1,i]$合成最短的长度。

那么就有

$dp[i]=\min_{f[j][i]>0}(dp[j-1]+1)$

```
#include<bits/stdc++.h>
#define N 505
using namespace std;
int n,f[N][N],a[N];
int dp[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) f[i][i]=a[i];
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r=l+len-1;
			for(int i=l;i<r;i++)
				if(f[l][i]&&f[l][i]==f[i+1][r]) f[l][r]=f[l][i]+1;
		}
 	}
 	memset(dp,0x3f,sizeof(dp));
 	dp[0]=0;
 	for(int i=1;i<=n;i++){
 		for(int j=1;j<=i;j++){
 			if(f[j][i]) dp[i]=min(dp[j-1]+1,dp[i]);
		 }
	 }
	 printf("%d",dp[n]);
	return 0;
} 
```
总结：
对于比较难的$dp$题往往不以题面所要求的目标作为目标，而是进行一些目标的转换。一般有以下两种情况。

1. 利用容斥，取题面目标的反面。
1. 如本题，将要想求得题面目标所需要处理的信息进行处理。

---

## 作者：ix35 (赞：8)

一开始写了个大力 $O(n^4)$ 的 Bitset 优化 DP，不出所料炸了，只好写 $O(n^3)$。

这里需要用到一个结论：

**对于一个区间，如果它可以被合成一个数，那么它被合成的数是唯一的。**

证明：我们定义一个数 $i$ 的权值为 $2^i$，那么权值守恒。

于是我们设 $dp(i,j)$ 表示 $[i,j]$ 能被合成哪一个数（原本我就是这里开了个 Bitset）。

转移方程就是：

$$dp(i,j)=dp(i,m)+1\qquad(i\leq m<j,\ \ dp(i,m)=dp(m+1,j)$$

也就是枚举最后一次合并的位置。

暴力做，$O(n^3)$。

最后再来个 $O(n^2)$ 的线性 DP 求一下整个数组至少要分多少段即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=510;
int n,a[MAXN],dp[MAXN][MAXN],g[MAXN];
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		dp[i][i]=a[i];
	}
	for (int len=1;len<=n-1;len++) {
		for (int l=1;l+len<=n;l++) {
			int r=l+len;
			for (int m=l;m<r;m++) {
				if (dp[l][m]&&dp[l][m]==dp[m+1][r]) {
					dp[l][r]=dp[l][m]+1;
					break;
				}
			}
		}
	}
	memset(g,0x3f,sizeof(g));
	g[0]=0;
	for (int i=1;i<=n;i++) {
		for (int j=0;j<=i-1;j++) {
			if (dp[j+1][i]) {
				g[i]=min(g[i],g[j]+1);
			}
		}
	}
	printf("%d\n",g[n]);
	return 0;
}
```


---

## 作者：GGapa (赞：6)

看到题解都是用的 $O(n^3)$ 的区间 DP，蒟蒻在这里给出一种不需要区间 DP 且时间复杂度为 $O(nv)$ 的做法。

有一个很经典的题是问 $a$ 能够得到的最大的数是多少。

考虑定义 $F(i, j)$ 代表 $i$ 开始的区间要合成值 $j$ 的所需要的区间的右端点 $+1$，也就是说 $[i, F(i, j))$ 这个区间可以合成 $j$，转移是类倍增的。但是这样不能够解决问题。

考虑定义 $G(i)$ 代表考虑构成 $[i, n]$ 的最小可能长度，转移为 $G(i) \gets \min\{G(F(i,v)) + 1\}$。

最终的答案即为 $G(1)$，代码非常短。

```cpp
const int N = 500 + 5;
int F[N][1500];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for(int i = 1, x; i <= n; i++) cin >> x, F[i][x] = i + 1;
    rep(v, 2, 1500 - 1) rep(i ,1, n) {
        auto &f = F[i][v], f1 = F[i][v - 1] ;
        if(f == 0 && f1 && f1 <= n + 1) f = F[f1][v - 1];
    }
    vector<int> G(n + 10, 1e9) ;
    G[n + 1] = 0;
    per(i, n, 1) rep(v, 1, 1500 - 1) {
        auto &f = F[i][v];
        if(F[i][v]) G[i] = min(G[i], G[F[i][v]] + 1);
    }
    cout << G[1] << '\n';
    return 0;
}
```

---

## 作者：Jairon314 (赞：6)

$$ \textbf{\huge 1312E[CF]} $$
$$ \textbf{\LARGE Array Shrinking} $$
$$ \text{\large ————Jair} $$

$$ \text{\small Warning: This problem's solving belongs to} $$
$$ \textbf {\huge $ \mathbb{TOP\;SECRET} $} $$
$$ \text {\small Unauthorized personnel are prohibited from visiting} $$
$$ \text {\small Perpetrators will be monitored, located, and dealt with} $$

$$ PAY\;ATTENTION: $$
$$ \text {\small 本题解主要解释dpAC代码} $$

$$ \large· $$
$$ \large· $$
$$ \large· $$

$$ \large \frak {Forward} $$
--------
昨天，我在参加急训的时候，老师净讲些紫题......好不容易讲一道蓝题，~~~我还没听~~~，于是我就自己按照区间动规的模板，在纸上写写画画一小会儿，终于AC了这道题[呼~]

接下来，我提一下状态转移方程

首先，我们令$ G[i][j] $代表闭区间$ [i,j] $经过几次合并之后的最小长度是多少,令$ value[i][j] $代表闭区间$ [i,j] $的每一个元素的值(前提是能够合并成一个数字，所以每一个元素的值相同)

那么：

$$ G[l][r]=G[l][mid]+G[mid+1][r] $$

如果相邻的两个元素可以合并成一个值，则：

$$ G[l][r]=1 $$

$$ value[l][r]=value[l][mid]+1 $$

因为相邻的元素合并之后就变成了一个元素，所以就推出了第一个式子。第二个式子就是根据题目的转移情况直接得到的。


$$ \large \frak {CodeTime}$$
--------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define maxn 1000010

int n,array[maxn];
int G[1010][1010];
int value[1010][1010];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&array[i]);
	}
	for(int i=1;i<=n;i++){
		G[i][i]=1;//只有一个元素肯定长度是1
		value[i][i]=array[i];//i这个元素的值就是array[i]
		if(array[i]==array[i+1]){
			G[i][i+1]=1;//两个元素的合并
			value[i][i+1]=array[i]+1;
		}
		else{
			G[i][i+1]=2;
		}
		for(int j=i+2;j<=n;j++){
			G[i][j]=j-i+1;//每个区间的初始最小长度是它一开始的长度
		}
	}
	for(int len=1;len<=n;len++){
		for(int l=1,r=l+len-1;l<=n&&r<=n;l++,r++){
			for(int mid=l;mid<r;mid++){
				G[l][r]=min(G[l][r],G[l][mid]+G[mid+1][r]);
				if(G[l][mid]==1&&G[l][mid]==G[mid+1][r]&&value[l][mid]==value[mid+1][r]){
					G[l][r]=1;
					value[l][r]=value[l][mid]+1;
					//经典区间dp
				}
			}
		}
	}
	printf("%d\n",G[1][n]);
	return 0;
}
```

之后我又加了一些常数优化，勉强跑到了最优解第一页

```cpp
#include<cstdio>
using namespace std;

inline char nc () {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read () {
	register int x(0), f(1);
	register char ch = nc ();
	while (ch < '0' || ch > '9') {if (ch == '-') f = ~f +1; ch = nc ();}
	while (ch <= '9' && ch >= '0') {x = (x<<3) + (x<<1) + (ch ^48); ch = nc ();}
	return x *f;
}

int n,array[1010];
int G[1010][1010];
int value[1010][1010];

int main(){
	n=read();
	int nn=n+1;
	for(register int i(1);i^(nn);i=-~i){
		array[i]=read();
	}
	for(register int i(1);i^(nn);i=-~i){
		G[i][i]=1;
		value[i][i]=array[i];
		if(array[i]==array[i+1]){
			G[i][i+1]=1;
			value[i][i+1]=array[i]+1;
		}
		else{
			G[i][i+1]=2;
		}
		for(register int j(i+2);j<=n;j++){
			G[i][j]=j-i+1;
		}
	}
	for(register int len(1);len^(nn);len=-~len){
		for(register int l(1),r(l+len-1);l^(nn)&&r^(nn);l=-~l,r=-~r){
			for(register int mid(l);mid^r;mid=-~mid){
				G[l][r]=G[l][r]<(G[l][mid]+G[mid+1][r])?G[l][r]:(G[l][mid]+G[mid+1][r]);
				if(G[l][mid]==G[mid+1][r]&&G[l][mid]==1&&value[l][mid]==value[mid+1][r]){
					G[l][r]=1,value[l][r]=value[l][mid]+1;
				}
			}
		}
	}
	printf("%d\n",G[1][n]);
	return 0;
}
```

$$ \large \frak {in\;the\;end}$$
--------
留个赞呗~

---

## 作者：CXY07 (赞：3)

# 第一次过 Div2 E，然鹅 C 挂了......

## 题目链接：[CF1312E 【Array Shrinking】](https://www.luogu.com.cn/problem/CF1312E)

> **本题解同步发布于 [My Blog](http://cxy07.blog/index.php/archives/18/)**

本人在这道题上花了 $1h$，但实际上看起来并没有那么的难

我们很快可以发现：

**在最终数组中，某一个数字一定是原数组中连续的一段。**

**并且容易看出，某一段如果可以缩成一个点，则这个数字是固定的**

这样的话，状态就很好设置了：

定义 $dp[i][j]$ 为 $[i,j]$ 缩为一个数字后，这个数字是多少

如果不能缩成一个数字，值为 $0$

那么我们就有转移：

$$dp[i][j] = dp[i][k] + 1$$

$$ (i \le k < j,dp[i][k] = dp[k + 1][j] \neq 0)$$

这明显是一个区间 $dp$，时间复杂度为 $O(n^3)$

这样我们就可以得到所有能够缩成一个数字的区间了

接下来我们所需要做的，就是把所有数字分割为若干段，满足每一段都能被缩成一个数字，且段的个数最小

这又是一个简单的 $dp$，复杂度为 $O(n^2)$

然后我们就做完啦！

$Code:$

```cpp
//Code By CXY
#include<bits/stdc++.h>
using namespace std;
    
const int MAXN = 510;
     
int n;
int a[MAXN];
int dp1[MAXN][MAXN],dp2[MAXN]; 
     
signed main () {
  	scanf("%d",&n);
   	for(register int i = 1;i <= n; ++i)
   		scanf("%d",&a[i]),dp1[i][i] = a[i];
   	for(register int l = 2;l <= n; ++l) {//注意枚举的是区间长度！
   		for(register int i = 1,j;i + l - 1 <= n; ++i) {
   			j = i + l - 1;
   			for(register int p = i;p < j; ++p)
   				if(dp1[i][p] && dp1[i][p] == dp1[p + 1][j]) dp1[i][j] = dp1[i][p] + 1;	
   		}
   	}
   	for(register int i = 1;i <= n; ++i) {
   		dp2[i] = i;
   		for(register int j = 1;j <= i; ++j)
   			if(dp1[j][i]) dp2[i] = min(dp2[i],dp2[j - 1] + 1);
   	}
   	cout << dp2[n] << endl;
   	return 0;//End.
}
```

所以这道题其实不是很难的样子，~~然鹅我考场竟然还妄想了一波贪心~~

还是太弱了......

初三的 $OIer$，请多关照

---

## 作者：cff_0102 (赞：1)

不同于其它题解的 dp 做法。

考虑状态 $i,j$ 表示将前 $i$ 个数进行若干次合并操作，且最终得到的最右侧的数是 $j$。

设 $dp_{i,j}$ 表示达到状态 $i,j$ 时，最右侧的这个数由几个数合并而来，$ans_{i,j}$ 表示此时 $1\sim i$ 最少合并为几个数，$mn_i=\min_{j}(ans_{i,j})$，其中状态 $i,j$ 合法。

每次遍历到一个新的数 $i$ 的时候，可以选择：

- 不与前面的数合并，则 $dp_{i,a_i}=1$，$mn_{i}=ans_{i,a_i}=mn_{i-1}+1$。
- 与前面的数合并：
  1. 首先，设 $x=a_i,l=i-1$。
  2. 如果 $dp_{l,x}$ 不为 $0$，即状态 $(l,x)$ 可达，因此可以将现在的数 $x$ 和前面的状态 $l,x$ 最右边的 $x$ 合并。现在的 $x$ 变为 $x+1$，$l$ 变为 $l-dp_{l,x}$，并继续重复这一步，尝试与更前面的数合并（并分别把答案保存在 $dp_{i,x}$ 和 $ans_{i,x}$ 中），直到 $dp_{l,x}=0$，则不能继续合并。

最后输出 $mn_i$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int a[N];
int dp[N][N<<1],ans[N][N<<1],mn[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		int x=a[i];
		dp[i][x]=1;
		mn[i]=ans[i][x]=mn[i-1]+1;
		int l=i-1;
		while(dp[l][x]){
			dp[i][x+1]=i-(l-dp[l][x]);
			ans[i][x+1]=ans[l][x];
			mn[i]=min(mn[i],ans[i][x+1]);
			l-=dp[l][x];
			x++;
		}
	}
	cout<<mn[n];
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

从 $n\le500$ 以及题意中的“合并”不难猜出是区间动态规划问题。

考虑如何进行动态规划。

想到一个很朴素的方法，设 $v_{i,j,k}$ 表示区间 $[i,j]$ 合并后只剩下 $k$ 是否可行，$f_{i,j}$ 表示区间 $[i,j]$ 合并后最少数字个数。不难有：

+ 若存在 $p$ 和 $k$，使得 $v_{i,k,p}$ 和 $v_{k+1,j,p}$ 均可行，则 $f_{i,j}=1$，$v_{i,j,p+1}$ 标记为可行。
+ 否则，$f_{i,j}=\min\{f_{i,k}+f_{k+1,j}\}$。

这是一个 $O(n^3 V)$ 的抽象做法，但是为我们的解法提供方向。

我们考虑将第一步的 $O(nV)$ 降为 $O(n)$，使得总复杂度变为 $O(n^3)$。

发现 $p$ 的枚举是不必要的，人类智慧可得，一个区间若能缩成一个数，这个数唯一。

引入辅助数组 $q_{i,j}$ 表示若 $[i,j]$ 是可以缩成一个数的，那么这个数的值。

转移变为这样：

+ 若存在 $k$ 使得 $q_{i,k}=q_{k+1,j}$，则 $f_{i,j}=1$ 并且 $q_{i,j}=q_{i,k}+1$。
+ 否则，$f_{i,j}=\min\{f_{i,k}+f_{k+1,j}\}$。

[AC record](https://codeforces.com/contest/1312/submission/199717542)

---

## 作者：smoothset (赞：1)

[原文链接](https://blog.csdn.net/qq_43537070/article/details/107632539)
#### 题意
给定一个数组，每一次对于两个相邻的数，如果他们相等，则可以将它们合并为一个数，其值为原数$+1$，求原数组合并完后的最小长度。
#### 思路
首先看到这种描述，我们就可以想到区间dp
>区间dp的模板：dp[i][j] = min(dp[i][k] + dp[k + 1][j] + w[i])（w[i]随题目改变）

考虑令$dp[i][j]$为区间$[i, j]$所能合并的最小长度，$w[i][j]$为区间$[i,j]$所能合并出来的和
那么可以很简单的得出这样一个式子
$$dp[i][j] = \min(dp[i][j],  dp[i][k]+dp[k+1][j])$$
然后如何可以保证这个题目上的合并呢
我们可以考虑在每次枚举$i,j,k$时像这样更新

```cpp
if (dp[i][k] == 1 && dp[k + 1][j] == 1 && w[i][k] == w[k + 1][j])
	dp[i][j] = 1, w[i][j] = w[i][k] + 1;
```
最后直接输出$dp[1][n]$即可
#### 代码
具体实现见代码：
~~~cpp
const int N = 505, INF = 0x3f3f3f3f;
int n, dp[N][N], w[N][N];
// dp[i][j]:[i, j]区间合并的长度
// w[i][j]:[i, j]区间合并的和
int main()
{
	memset(dp, 0x3f, sizeof dp);
	rd(n);
	for (int i = 1; i <= n; i++)
		rd(w[i][i]), dp[i][i] = 1;
	for (int len = 2; len <= n; len++)
		for (int i = 1; i <= n - len + 1; i++)
		{
			int j = len + i - 1;
			for (int k = i ; k < j; k++)
			{
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
				if (dp[k + 1][j] == 1 && dp[i][k] == 1 && w[i][k] == w[k + 1][j]) //相邻两段长度相同都为1，且值也相同，即可更新
					dp[i][j] = 1, w[i][j] = w[i][k] + 1;
			}
		}
	pt(dp[1][n]);
	return 0;
}
~~~
#### 谢谢

---

## 作者：WaterSun (赞：0)

# 思路

本题为 [P3146](https://www.luogu.com.cn/problem/P3146) 变式，也算是一道很经典的区间 DP 题了。

因为 $n \leq 500$，考虑区间 DP。定义 $dp_{i,j}$ 表示操作 $[i,j]$ 区间剩余长度的最小值。

那么，我们可以枚举一个中间值 $k$，可以显然地得到一个状态转移方程（即不能合二为一的情况）：

$$
dp_{i,j} = \min(dp_{i,k} + dp_{k + 1,j})
$$

然后，我们再来考虑两个区间能够合并的情况。

如果 $[i,k]$ 和 $[k + 1,j]$ 能合并，当且仅当 $dp_{i,k} = dp_{k + 1,j} = 1$，以及两段区间合并出的值相同。

但是，我们现在并不知道两段区间的值具体是多少。所以，现在有两种处理方式：

1. 将合并区间得到的值作为 $dp$ 的一维用来枚举，但这显然是不行的，因为时间复杂度将变为 $\Theta(n^3m)$。（其中 $m = \max\{a_i\}$。）

2. 再开一个数组 $f$ 记录两个区间的合并后的值。

那么，对于这个问题显然只能选择第二种方案。

由此，不妨令 $f_{i,j}$ 表示合并 $[i,j]$ 区间得到的数值。那么，我们就可以在处理 $dp_{i,j}$ 的时候同时更新 $f_{i,j}$。

综上，对于 $[i,k]$ 和 $[k + 1,j]$ 能合并，需满足：

$$
dp_{i,k} = dp_{k + 1,j} = 1 \wedge f_{i,k} = f_{k + 1,j}
$$

时间复杂度：$\Theta(n^3)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 510,inf = 0x3f3f3f3f;
int n,ans = inf;
int arr[N];
int f[N][N],dp[N][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	memset(dp,inf,sizeof(dp));
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = 1;i <= n;i++){
		f[i][i] = arr[i];
		dp[i][i] = 1;
	}
	for (re int l = 1;l <= n;l++){
		for (re int i = 1;i + l - 1 <= n;i++){
			int j = i + l - 1;
			for (re int k = i;k < j;k++){
				dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j]);//不合并 
				if (dp[i][k] == dp[k + 1][j] && dp[i][k] == 1 && f[i][k] == f[k + 1][j]){//满足条件，说明两区间可以合并 
					dp[i][j] = min(dp[i][j],dp[i][k]);//更新两个 DP 数值 
					f[i][j] = f[i][k] + 1;
				}
			}
		}
	}
	printf("%d",dp[1][n]);
	return 0;
}
```

---

## 作者：LIUYC_C (赞：0)


 
## 题目大意：
本题翻译有点怪。

题目描述如下：

给定一个数组 $a$，你可以找到一对相等且相邻的数，将他们合并为一个比它们两个数大一的数。

**问，可以将数组最短合并到多长？**

## 一、关于思路：
对于一开始拿到的题目，我们一般都会先去观察它具备什么性质，而对于这一类涉及操作选择，然后再询问最值的，就是 DP 考虑的事情。

 
 进而我们再去确定到底是什么类型的 DP 问题，观察它的操作方式，不难发现，这题很显然是区间 DP，因为它的操作涉及了合并区间，而合并区间计算贡献非常符合区间 DP 分阶段划分问题的性质。**（可参见[区间 DP 的定义](https://oi-wiki.org/dp/interval/)）**
 
##  二、关于状态设计：
做 DP，状态设计肯定少不了，可以说这是 DP 的灵魂，一般来说，符合以下两个性质的状态是好状态：


1. **可以进行有效的转移，并且便于转移。**

2. **可以表示所有的状态。**


对于此题，我们仿照区间 DP 的一般思路，以一段区间作为它的一二维。

**我们设 $f_ {i,j}$ 表示在 $[i,j]$ 区间内可以合并的最小长度。**

**检验**：关于这个方程的设计，我们可以把小范围区间合并成大区间，符合第一点性质，也可以表示出所有的状态，符合第二点，可行。（其实就是个套路区间 DP）
## 三、关于转移方程：
考虑如何转移：

一般就是枚举 $[l,r]$ 的中间点。
 
如果相邻两段长度相同都不为 $1$，或可合并后的值不相同，不可合并。

那么对于 $[l,mid]$ 可以合成的最小长度为 $x$，和 $[mid+1,r]$ 可以合成的最小长度为 $y$，那 $[l,r]$ 就可以合成一个最小长度 $x+y$。

因此有：

$f_{i,j}\leftarrow\min(f_ {l,mid}+f_ {mid+1,r})$

反之，对于 $f_ {l,mid}=f_ {mid+1,r}$ 即可以合并。

我们设 $w$ 数组表示：这段区间可合并之后的值。

因此我们需要满足：

$f_ {l,mid}=f_{mid+1,r}$，$w_{l,mid}=w_{mid+1,r}$，$f_ {l,mid}=1$ 

满足这三个条件后，即可合并，使：

$$f_ {l,r} \leftarrow 1 $$
$$w_ {l,r} \leftarrow w_{l,mid}+1$$ 
## 四、代码实现：

应该讲到这里没什么难的了吧：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1010;
typedef long long LL;


int f[N][N];
int w[N][N];
int a[N];

int main(){
    int n;
    cin>>n;
    memset(f,127,sizeof f);//求最小，赋极大
    
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        f[i][i]=1,w[i][i]=a[i];
    }
    
    
    for(int k=2;k<=n;k++){
        for(int l=1;l+k-1<=n;l++){
            int r=l+k-1;
            for(int mid=l;mid<r;mid++){
                f[l][r]=min(f[l][r],f[l][mid]+f[mid+1][r]);
                //1. 前后区间长度相同。	
				//2. 前后区间可合并之后的值相同。
				//3. 区间长度为一。
                if(f[l][mid]==f[mid+1][r]&&f[l][mid]==1&&w[l][mid]==w[mid+1][r]){
                    f[l][r]=1;
                    w[l][r]=w[l][mid]+1;
                }
            }
        }
    }
    
    cout<<f[1][n]<<endl;
    return 0;
}
```



---

## 作者：lmy_2011 (赞：0)

### 初始思路
考虑到数字相对顺序不改变，应该可以区间动态规划。

状态：将区间 $[l,r]$ 的数字合并起来，最少剩下几个数字。
### 正解思路
首先，定义状态：

$dp_i$ 表示前 $i$ 个数可以合成的最小长度。


我们要知道最终合成的结果是分截合成的，只要算出任意区间 $[i,j]$ 的顺序合成结果，就能知道最终结果。

同样在寻找 $[i,j]$ 的合成结果中，我们就需要双重循环，时间复杂度 $n^2$。

通过上面的推导，我们就可以推导出状态转移方程，具体推导过程如下：

我们先设一个数 $x$ 为从 $j$ 位到 $i$ 位顺序合成的长度，然后得知状态转移方程是

$$dp_i=min(dp_{i,x}+dp_j)$$

总复杂度 $n^3$（因为求从 $j$ 位到 $i$ 位顺序合成的长度的时间复杂度为 $n$）。

### 剪枝优化
可以顺序合成的值保存下来，定义 $x_{i,j}$ 为从 $j$ 位到 $i$ 位顺序合成的最小长度。

$x_{i,j}=x_{i,j-1}$ 可以用来合成第 $j$ 位，所以在已知 $x_{i,j-1}$ 的情况下计算 $x_{i,j}$ 的复杂度为 $1$。在此基础上进一步可以做如下优化：
```cpp
	for (int i = 1; i <= n; i++) {
		int t = 0;
		for (int j = i; j <= n; j++) {
			que[++t] = a[j];
			while (t != 0) {
				if (que[t] == que[t - 1]) {
					t--;
					que[t]++;
				}
				else break;
			}
			dp[j] = min(dp[j], dp[i - 1] + t);
		}
	}

```



---

## 作者：Supor__Shoep (赞：0)

本人是通过网上查找区间 DP 练习题来到这里的。

那么很明显，这道题是可以用区间 DP 完成的。我们首先定义状态 $dp_{i,j}$ 表示区间 $[i,j]$ 的最小长度，但是我们发现这样并不能实现状态转移，因为本题当中相同的数才能进行合并，比如 `2 2 2 2` 可以进行合并变成 `8`，但是我们不能确定中间的 `4 4` 是否可以进行合并。

所以应该怎么进行改进呢？这是我们就需要第二个 DP，为什么要这么想呢？根据所给的 $a_i$，我们只能直接合并 $a_i$ 和 $a_{i+1}$ 得到 $k$，但是如果旁边还有一个 $k$ 可以合并，我们就需要记录 $k$ 的值进行判断，而为了记录 $k$ 的值，我们就可以想到定义一个新的数组 $f_{i,j}$ 表示当 $[i,j]$ 的长度可以变成 $1$ 的时候，所得到的最终数字。这样一来，当 $[i,k]$ 和 $[k+1,j]$ 都可以合并成一个数的时候，因为记录的 $f_{i,k}$ 和 $f_{k+1,j}$ 是相等的，所以可以又一次合并得到 $f_{i,j}=f_{i,k}+1$。否则就不能进行转移。

所以最终结果：

$$dp_{i,j}=\text{max}(dp_{i,j},dp_{i,k}+dp_{k+1,j})$$

$$dp_{i,j}=1,~f_{i,j}=f_{i,k}+1~(f_{i,k}=f_{k+1,j})$$

那么代码就可以轻轻松松打出来了：

```cpp
int main()
{
	memset(dp,0x3f,sizeof(dp));
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>f[i][i],dp[i][i]=1;//区间长度为1，f[i][i] 的结果就是 a[i]
	for(int len=2;len<=n;len++)
	{
		for(int i=1;i<=n-len+1;i++)
		{
			int j=i+len-1;
			for(int k=i;k<j;k++)
			{
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);//拼接两个区间的长度
				if(dp[i][k]==dp[k+1][j]&&dp[i][k]==1&&f[i][k]==f[k+1][j])	dp[i][j]=1,f[i][j]=f[i][k]+1;//可以进行合并
			}
		}
	}
	cout<<dp[1][n];
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

两个简单的区间 DP。

首先求出对于一段区间 $[l,r]$，如果能将其合并为一个值，那么这样的一个值一定是确定的，所以用一个 $f_{i,j}$ 来记录这个值是多少。

对于某一段区间，这样的一个值可以从中间的任意一个断点处合并起来，所以在这样的一个区间中枚举断点来进行转移，由于这样的值是唯一确定的，所以一旦找到就可以立即退出枚举断点的循环。

复杂度 $O(n^3)$。

---

然后考虑如何取到一个最短的合并后序列。

用一个 $dp_i$ 记录下从一合并到 $i$ 号元素最短需要多少个数，然后对于每一个 $i$，向前枚举一个断点使得断点到 $i$ 全都合并成一个元素。

需要注意的是，这样的一个点有可能就是 $i$，也就意味着 $i$ 这个点单独挪开。

复杂度 $O(n^2)$。

---

总复杂度 $O(n^3)$，由于基本没有什么常数，$n\le 500$ 的数据范围也是可以接受的。

---

### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[505][505],n,dp[505];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d",&f[i][i]),dp[i]=i;
	for(int i=2;i<=n;i++){
		for(int j=1;j<=n-i+1;j++){
			for(int k=j+1;k<=i+j-1;k++){
				if(f[j][k-1]==f[k][i+j-1]&&f[j][k-1]!=0){
					f[j][i+j-1]=f[j][k-1]+1;
					break;
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(f[j][i]!=0)
			dp[i]=min(dp[i],dp[j-1]+1);
		}
	}
	printf("%d",dp[n]);
	return 0;
}
```


---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1312E)

# 题解

由于 $n\le 500$，所以这道题支持类似 $\mathcal O(n^3)$ 之类的小暴力...

发现对于固定的某一段 $[l,r]$，我们可以直接处理出它们会合并成什么亚子，定义 $f[i][j]$ 为 $[i,j]$ 可以合并成什么数，如果不可行为 $-1$，否则为合并的值

这里直接给出求 $f$ 的代码，不作过多说明

```cpp
inline int Merge(const int l,const int r){
    if(l==r)return a[l];
    if(a[l]!=a[l+1])return -1;
    if(l+1==r)return a[l]+1;
    rep(i,l+2,r)if(a[i-1]+1!=a[i])return -1;
    return a[r]+1;
}

inline void Solve_f(){
    rep(i,1,n)rep(j,i,n)f[i][j]=Merge(i,j);
}
```

然后，我们可以直接进行 $dfs$，首先定义 $memo[i][j]$ 表示区间 $[i,j]$ 最少会被合并成多少个点，首先我们显然知道，若 $f[i][j]\neq -1$，那么 $memo[i][j]=1$，对于其他情况，显然有转移
$$
memo[i][j]=\min \{memo[i][k]+memo[k+1][j]|k\in[l,r-1]\}
$$
但是有一种比较特殊的情况，就是 $memo[i][k]=memo[k+1][j]=1$ 且 $f[i][k]=f[k+1][j]$ 时，我们可以将左右区间合并，即 $memo[i][j]=1,f[i][j]=f[i][k]+1$，其他情况随便做就可以了...

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13391732.html
```



---

## 作者：Clever_Jimmy (赞：0)

设 $f_{i, j}$ 表示 $a[i\cdots j]$ 能整合成的数字，如果不能整合成一个数字，则 $f_{i, j} = 0$。

设 $g(i)$ 表示 $a[1\cdots i]$ 最少需要被分成的段数。

那么 $f_{i, j}$ 可以用区间 dp 求出来：
$$
f_{i, j} = f_{i, k} + 1
$$

（当 $f_{i, k} = f_{k + 1, j}$ 且 $f_{i, k} > 0, i \le k < j$ 时）

然后 $g(i)$ 可以枚举前面的一个点 $j$，然后考虑 $[i\cdots j]$ 这一段被整合后的影响。
$$
g(i) = \min\{g(j) + 1\}(f_{j + 1, i} > 0, j < i)
$$
答案即为 $g(n)$，时间复杂度为 $O(n^3)$。

[code](https://codeforces.ml/contest/1312/submission/73148764)

```cpp
#include <bits/stdc++.h>
#define LL long long

const int N = 5e2 + 5;

int n, a[N], f[N][N], g[N]; 

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i) f[i][i] = a[i];
	for(int len = 2; len <= n; ++len) {
		for(int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			f[l][r] = 0;
			for(int k = l; k < r; ++k)
				if(f[l][k] == f[k + 1][r] && f[l][k] > 0)
					f[l][r] = f[l][k] + 1;
		}
		/*for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				printf("f(%d, %d) = %d ", i, j, f[i][j]);
			}
			putchar('\n');
		}
		putchar('\n');*/
	}
	/*for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			printf("f(%d, %d) = %d ", i, j, f[i][j]);
		}
		putchar('\n');
	}*/
	memset(g, 0x3f, sizeof(g));
	g[0] = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < i; ++j)
			if(f[j + 1][i])
				g[i] = std::min(g[i], g[j] + 1);
	/*for(int i = 1; i <= n; ++i) {
		printf("g(%d) = %d ", i, g[i]);
	}
	putchar('\n');*/
	printf("%d", g[n]);
	return 0;
}
/*
5
4 3 2 2 3

*/
```

---

## 作者：xiaolou (赞：0)

这里提供一种诡异的做法。

定义$dp_i,_j$为在区间$[i$,$j]$最多可以去掉的元素个数；

$size_i,_j$为$dp_i,_j$最大时区间$[i,j]$中的元素个数，其实相当于$i-j+1-dp_i,_j$，但是用一个数组有助于理解$(?)$；

$l_i,_j$与$r_i,_j$分别为$dp_i,_j$最大时区间$[i,j]$的左端点的值与右端点的值。

### 初始化

初始化的部分十分简短$(?)$。

对于每个长度为$1$的区间，

$dp_i,_j=0$

$l_i,_j=r_i,_j=a_i$

$size_i,_j=1$ 

### 转移

转移的部分十分令人迷惑$(?)$。

按照区间dp的套路转移方法，我们先枚举区间的长度len。

随后分别枚举区间的起点i与转移点j，

如果此时左区间的右端点与有区间左端点不等，即

$r[i][j]$与$l[j+1][i+len-1]$不相等，

没有进行任何合并的操作，直接将两个区间的信息合并；

否则两个区间可以进行一次合并操作，因此有

$dp[i][i+len-1]=dp[i][j]+dp[j+1][i+len-1]+1$

$size[i][i+len-1]=size[i][j]+size[j+1][i+len-1]-1$

对于$l$数组和$r$数组，需要判断一下两个区间的$size$数组是否为$1$,分为4类，但理解起来应该并不困难$(?)$。

### 统计答案

输出n-dp[1][n]即可。



```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int n,a[505],dp[505][505],l[505][505],r[505][505],size[505][505];
int main()
{
	memset(a,-1,sizeof(a));
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		l[i][i]=a[i];
		r[i][i]=a[i];
		dp[i][i]=0;
		size[i][i]=1;
	}	
	for(int len=2;len<=n;++len)
	{
		for(int i=1;i+len-1<=n;++i)
		{
			for(int j=i;j<i+len-1;++j)
			{
				if(size[i][j]==0||size[j+1][i+len-1]==0)
				{
					continue;
				}
				if(r[i][j]!=l[j+1][i+len-1])
				{
					if(dp[i][i+len-1]<dp[i][j]+dp[j+1][i+len-1])
					{
						dp[i][i+len-1]=dp[i][j]+dp[j+1][i+len-1];
						l[i][i+len-1]=l[i][j];
						r[i][i+len-1]=r[j+1][i+len-1];
						size[i][i+len-1]=size[i][j]+size[j+1][i+len-1];
					}
					continue;
				}
				int tmp=dp[i][j]+dp[j+1][i+len-1]+1;
				if(dp[i][i+len-1]>=tmp)
				{
					continue;
				}
				dp[i][i+len-1]=tmp;
				size[i][i+len-1]=size[i][j]+size[j+1][i+len-1]-1;
				if(size[i][j]==1)
				{
					if(size[j+1][i+len-1]==1)
					{
						l[i][i+len-1]=l[i][j]+1;
						r[i][i+len-1]=r[j+1][i+len-1]+1;
					}
					else
					{
						l[i][i+len-1]=l[i][j]+1;
						r[i][i+len-1]=r[j+1][i+len-1];
					}
				}
				else
				{
					if(size[j+1][i+len-1]==1)
					{
						l[i][i+len-1]=l[i][j];
						r[i][i+len-1]=r[j+1][i+len-1]+1;
					}
					else
					{
						l[i][i+len-1]=l[i][j];
						r[i][i+len-1]=r[j+1][i+len-1];
					}
				}
			}
		}
	}
	printf("%d",n-dp[1][n]);
	return 0;
}
```
### 总结&展望$(?)$

看了很多神仙写的代码，大多都用了一个我没有想到的结论，比我写的冗杂的代码简洁多了。

好像只需要记录一个区间合并成一个数以后的值$(?)$（我完全懂了$(?)$）

用LaTeX敲字太难了/kk


---

## 作者：违规用户名gAGt8$%z (赞：0)

## 思路

这题一看就是区间 $dp$ 。

$dp[i][j]$ 表示 $i$ 到 $j$ 合并之后最小长度

维护一个 $s[i][j]$ 表示合并后 $i$ 到 $j$ 这一段的和

枚举断点 $k$ ：

$dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j])$

如果 $dp[i][k]=dp[k+1][j]=1$ 并且 $s[i][k]=s[k+1][j]$ , 那么   $dp[i][j]=1 , s[i][j]=s[i][k]+1$

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505],dp[505][505],s[505][505],n;
int main() {
	memset(dp, 0x3f, sizeof dp);
	cin>>n;
	for (int i=1; i<=n; i++){cin>>a[i]; dp[i][i]=1; s[i][i]=a[i];}
	for (int len=2; len<=n; len++) 
		for (int l=1,r=l+len-1; r<=n; l++,r++) 
			for (int k=l; k<r; k++) {
				dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
				if (dp[l][k]==1&&dp[k+1][r]==1&&s[l][k]==s[k+1][r]) {
					dp[l][r] = 1;
					s[l][r] = s[l][k] + 1;
					break;
				}
			}
	cout << dp[1][n] << '\n';
	return 0;
}
```


---

