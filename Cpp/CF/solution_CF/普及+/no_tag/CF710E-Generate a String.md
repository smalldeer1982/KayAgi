# Generate a String

## 题目描述

zscoder wants to generate an input file for some programming competition problem.

His input is a string consisting of $ n $ letters 'a'. He is too lazy to write a generator so he will manually generate the input in a text editor.

Initially, the text editor is empty. It takes him $ x $ seconds to insert or delete a letter 'a' from the text file and $ y $ seconds to copy the contents of the entire text file, and duplicate it.

zscoder wants to find the minimum amount of time needed for him to create the input file of exactly $ n $ letters 'a'. Help him to determine the amount of time needed to generate the input.

## 样例 #1

### 输入

```
8 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 1 10
```

### 输出

```
8
```

# 题解

## 作者：LYYY (赞：25)

## 简单题 ?

### STEP1 ?

首先很显然的,转移方程是这样:

当$i$是奇数时:

$$f[i]=min\left \{ f[i-1]+x,f[i+1]+x \right \}$$

当$i$是偶数时:

$$f[i]=min\left \{ f[i-1]+x,f[i+1]+x,f[i/2]+y \right \}$$

但是这个方程是带环的,显然并不能O(n)转移.

这时我们想到了把一个状态看成一个点,然后建图跑最短路(反正cf机子快不会超时).于是**MLE**了QAQ.

### STEP2 ?

惨痛的经验告诉我们这道题并没有那么简单.~~可这毕竟是一道比赛时做出来的人比D还要多的题啊.~~

通过分析易知: **我们进行删除操作一定是因为原来长度比当前小,然后进行了翻倍操作,结果超了所以要删除.**

因此我们可以将原先的状态转移方程改一下:

$$f[i]=min\left \{ f[i-1]+x,f[k]+y+(k*2-i)*x \right \}$$

其中

$$k*2 \geq i$$

通过转化,我们就成功地将DP方程变成了一个DAG,然后单调队列搞一波就行了(**可以AC**).

### STEP3 ?

~~单调队列虽然不难写但是并不想写.~~

聪明的我们通过进一步分析得: **删除操作一定不会连续进行两次.**

因为刚才我们得到性质"进行删除操作一定是因为原来长度比当前小,然后进行了翻倍操作, 结果超了所以要删除", 那么如果我们连续删除两次, 一定不如在翻倍操作前先删除一次要优. 同理, 在翻倍之后连续多次删除也一定不如先删除再翻倍更优.

所以我们可以进一步优化状态转移:

当$i$是偶数时(不可能由删除操作转移而来):

$$f[i]=min\left \{ f[i-1]+x,f[i/2]+y \right \}$$

当$i$是奇数时(最多由一次删除操作转移而来):

$$f[i]=min\left \{ f[i-1]+x,f[(i+1)/2]+y+x \right \}$$

**AC**



------------


代码如下(三个代码分别对应STEP1/2/3,如果想练习带环DP和单调队列优化DP的可以看前两个):

### STEP1

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#define mp make_pair
using namespace std;
typedef long long LL;

const int maxn=20000005;//可能会先超过再删到N.
LL dis[maxn];
int N,x,y,tot;
bool vis[maxn];
priority_queue<pair<LL,int> > Q;

LL Dij()
{
	memset(dis,0x3f,sizeof(dis));
	dis[1]=x;
	Q.push(mp(-dis[1],1));
	while(!Q.empty())
	{
		int q=Q.top().second;Q.pop(),vis[q]=true;
		if(q==N) return dis[N];
		if(q>1&&!vis[q-1]&&dis[q-1]>dis[q]+x) Q.push(mp(-(dis[q-1]=dis[q]+x),q-1));
		if(q<N&&!vis[q+1]&&dis[q+1]>dis[q]+x) Q.push(mp(-(dis[q+1]=dis[q]+x),q+1));
		if(q<N&&!vis[q<<1]&&dis[q<<1]>dis[q]+y) Q.push(mp(-(dis[q<<1]=dis[q]+y),q<<1));
		while(!Q.empty()&&vis[Q.top().second]) Q.pop();
	}
	return dis[N];
}

int main()
{
	scanf("%d%d%d",&N,&x,&y);
	printf("%I64d",Dij());
	return 0;
}
```

### STEP2

由状态转移方程

$$f[i]=min\left \{ f[i-1]+x,f[k]+y+(k*2-i)*x \right \}$$

转化得

$$f[i]=min\left \{ f[i-1]+x,(f[k]+2*k*x)+y-i*x \right \}$$

这样的形式套单调队列就很显然了. $f[k]+2*k*x$是与$k$相关的部分, 所以单调队列中的元素比较的是$f[k]+2*k*x$的大小, 从队首到队尾单调递增.

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long LL;
LL f[11111111],Q[11111111];

int main()
{
	int N,x,y;scanf("%d%d%d",&N,&x,&y);
	f[0]=0;
	int l=1,r=0;
	for(int i=1;i<=N;++i)
	{
		while(l<=r&&Q[l]*2<i) ++l;
		f[i]=f[i-1]+x;
		if(l<=r) f[i]=min(f[i],f[Q[l]]+y+(Q[l]*2ll-i)*x);
		while(l<=r&&f[Q[r]]+Q[r]*2ll*x>=f[i]+i*2ll*x) --r;
		Q[++r]=i;
	}
	printf("%lld",f[N]);
	return 0;
}
```

### STEP3

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long LL;
LL f[11111111];

int main()
{
	int N,x,y;scanf("%d%d%d",&N,&x,&y);
	f[1]=x;
	for(int i=2;i<=N;++i)
	{
		f[i]=f[i-1]+x;
		if(i&1) f[i]=min(f[i],f[i/2+1]+x+y);
		else f[i]=min(f[i],f[i>>1]+y);
	}
	printf("%I64d",f[N]);
	return 0;
}
```

 _谢谢阅览！_ 

---

## 作者：柳下惠 (赞：17)

# CF710E 题解




题意可能不好理解，我们可以这样想，一个人在跳方格，每次向左或向右跳一步需要花费 $x$ 的代价，同时他还可以花费 $y$ 的代价翻倍跳跃（假设他当前在第 $i$ 格，他可以跳到第 $2i$ 格），他的初始位置在第 $0$ 格，求他跳到第 $n$ 个格子需要最少花费多少代价。

很显然，这是道 `dp` 题，来分析一下它的式子。

### 1.当 $n$ 为偶数时
此时这个人会从两个位置到 $i$，一个为 $i-1$（普通跳跃，代价为 $x$），另一个为 $i/2$（翻倍跳跃，代价为 $y$）。

所以我们可以很轻松的得到 $n$ 为偶数时的方程 ${f_i}=\min(f_{i-1}+x,f_{i/2}+y)$

### 2.当 $n$ 为奇数时
我们需要考虑一种情况，就是这个人会跳过终点，我们需要往回跳一步，所以此时到 $i$ 的两个位置分别为 $i-1$（普通跳跃，代价为 $x$）和 $i+1$（翻倍跳跃，代价为 $y$，再用普通跳跃往回跳一个就好了）。

此时的方程为 $f_i=\min(f_{i-1}+x,f_{(i+1)/2}+y+x)$

### 代码实现
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
ll n,x,y;
ll f[10000005];
int main()
{
	n=read(),x=read(),y=read();
	f[0]=0;//初始位置为0
	for(int i=1;i<=n;i++)
	{
	    if(i%2==0) f[i]=min(f[i-1]+x,f[i/2]+y);
	    else f[i]=min(f[i-1]+x,f[(i+1)/2]+y+x);
	}
	cout<<f[n];//此时f[n]为最优解
	return 0;
}
```



---

## 作者：Buried_Dream (赞：4)

## 题意：

 要生成一个长度为 $n$ 的字符串，
 
 有两种操作，一种是添加一个或删除一个字符。
 
 另外一种是将已有的字符复制下来，变成两倍的字符。
 
 第一种的代价为 $x$，第二种的代价为 $y$；
 
 ## 思路：
 
 看到数据范围，暴力会`TLE`，考虑动态规划。
 
 每一种一定是由前一种状态转移来的，需要考虑的就是当前有字符数量为奇数还是
 
 偶数。
 
 我们用 $dp[i]$ 来表示到达第 $i$ 个位置所需要的最小代价。
 
 ### 当 $i$ 为偶数的时候：
 
 我们可以知道有两种状态转移过来，一种是从上一格过来， 也就是 $i - 1$，代价为 $x$；
 
 另一个是从 $i / 2$ 过来的，代价为 $y$。

 显而易见，转移方程为：
 
 $$dp[i] = \min({dp[i - 1] + x, dp[\frac{i}{2}] + y})$$
 
 ### 考虑 $i$ 为奇数的时候：
 
 和 $i$ 为偶数的时候差不多。
 
 只不过转移方程第二种为先往后退一步在走，代价为 $x + y$；
 
 转移方程为：
 
 $$ dp[i] = \min({dp[i - 1] + x, dp[\frac{i+1}{2}] + x + y})$$


## AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

typedef long long LL;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
	while(isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();}
	return s * w;
}

 void print(int x){
	if(x < 0) putchar( '-' ),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int Pow(int a,int b) {
	int res = 1, base = a;
	while(b) {if(b & 1) res *= base;
	base *= base, b >>= 1;}
	return res;
 }
 
const int N = 1e7;
int dp[N << 1], n, x, y;

bool judge(int x) {
	return  !(x & 1) ? 1 : 0;
}

void init() {dp[0] = 0;}

void work() {
	for(int i = 1; i <= n; i++) 
		if(judge(i)) dp[i] = min(dp[i - 1] + x, dp[i / 2] + y);
		else dp[i] = min(dp[i - 1] + x, dp[(i + 1) / 2 ] + x + y);
}


signed main(){
//	ios::sync_with_stdio(0);
	n = read(), x = read(), y = read();
	init();
	work();
	print(dp[n]);
}
```


---

## 作者：dalao_see_me (赞：4)

题目大意：

可以花费x的代价使得一个数加一或者减一，或花费 $y$ 的代价使其乘 $2$，问从 $0$ 到 $n$ 需要多少的代价。

这一题，显然时间复杂度不能高于 $O(n)$。

我们考虑一波dp。

设 $f_i$ 为把 $0$ 变成 $i$ **至少**需要多少代价。

若 $i$ 是**偶数**，$f_i$ 只能从 $f_{i\div 2}$ 和 $f_{i-1}$ 转来。

这是可以证明的。

若 $f_i$ 可以由 $f{i+1}$ 转移过来，那么 $f_{i+1}$ 就由 $f_{i+2}$ 转移来。~~这总不需要解释吧~~。$f_{i+2}$ 由 $f_{i\div 2+1}$ 转移来。这中间产生了 $2x+y$ 的代价。

但是，这种转移明显不如 $f_{i\div 2+1}$ 转到 $f_{i\div 2}$ 再转到 $f_i$。这只需要 $x+y$ 的代价。

所以当 $i$ 为偶数时 $f_i$ 不会从 $f_{i+1}$ 转来。

所以 $f_i=\min(f_{i-1}+x ,f_{i\div 2}+y)$。

若 $i$ 为**奇数**时，$f_i$ 可以从 $f_{i+1}$ 和 $f_{i-1}$ 转过来。

但是，$f_{i+1}$ 我们还无法确定。怎么办呢？

如果 $f_{i+1}$ 要对答案产生贡献，那么它必然不由 $f_i$ 转移过来。

根据之前我们的结论，$f_{i+1}$ 只能从 $f_{(i+1)\div 2}$ 转移过来。

所以 $f_i=\min(f_{i-1}+x,f_{(i+1)\div 2}+x+y)$。

然后转移方程就列完了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
//数据较大记得开long long
using namespace std;
const int N=1e7+6;
int x,y,n;
int f[N];
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
signed main(){
	n=read();x=read();y=read();
	for(int i=1;i<=n;i++)f[i]=min(f[i-1]+x,f[i+1>>1]+y+x*(i&1));//把之前的两个转移方程合并了
	printf("%lld",f[n]);
	return 0;
}
```


---

## 作者：Suzt_ilymtics (赞：2)

~~这好像是出给学弟的模拟赛题~~

[题面传送](https://www.luogu.com.cn/problem/CF710E) | [更差的阅读体验？](https://www.cnblogs.com/Silymtics/p/solution-CF710E.html)

## Solution

显然需要考虑 DP。观察数据范围设 $f_i$ 表示生成一个长度为 $i$ 的字符串所需要的最少花费。

三个操作对应着 $i \to i - 1, i \to i + 1, i \to i \times 2$。

如果没有中间那个操作，显然每个状态只会由前面的状态转移而来，直接转移即可，转移方程如下：

$$f_i = \min \{ f_{i-1} + X \}$$

$$f_i = \min \{ f_{i/2} + Y\} (i \bmod 2 =0)$$

考虑中间的操作 $i \to i + 1$，它需要使用到后面的状态，这个状态我们现在并没有更新。那么我们想：我们能不能从 $\frac{i+1}{2} \to i+1 \to i$，因为 $f_{(i+1)/2}$ 我们是确定的是吧。

想了想是可以的。并且只需要在 $i \bmod 2 = 1$ 的时候考虑这个转移即可，所以有转移方程：

$$f_{i} = \min \{ f_{(i+1)/2} + X + Y \}(i \bmod 2 = 1)$$

（如果 $i \bmod 2 = 0$ 的话根本不需要 $-1$）

把这三个转移方程结合起来这题就做完了，时间复杂度 $\mathcal O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e7 + 10;

int n, X, Y;
int f[MAXN];

signed main() {
	cin >> n >> X >> Y;
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for(int i = 1; i <= n; ++i) {
		f[i] = min(f[i], f[i - 1] + X);
		if(i & 1) {
			f[i] = min(f[i], f[i + 1 >> 1] + X + Y);
		} else {
			f[i] = min(f[i], f[i >> 1] + Y);
		}
	}
	printf("%lld\n", f[n]);
	return 0;
}

```

---

## 作者：jiangtaizhe001 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16491898.html)

[题目传送门](https://codeforces.com/problemset/problem/710/E)

### 题目大意
你需要通过以下操作生成一个长度为 $n$ 的字符串：  
1. 在字符串末尾添加一个字符，代价为 $x$。
2. 将整个字符串复制一遍添加在后面，代价为 $y$。

求最小代价。  
$1\le n\le 10^7$，$1\le x,y\le 10^9$
### 题目解析
看似可以贪心并且很难找到正确解法，又可以搜索，显然是 DP。  
设 $f_i$ 为生成长度为 $i$ 的字符串的代价。
根据题目可以列出转移方程;
$$
f_i=\left\{
\begin{aligned}
& \min\{f_{i-1}+x,f_{i+1}+x\} & & x\text{为奇数} \\
& \min\{f_{i-1}+x,f_{i+1}+x,f_{i/2}+y\} & & x\text{为偶数}
\end{aligned}
\right.
$$
但是我们会发现，这样列出来的 DP 式是有环的，不能快速转移。我们考虑将 DP 式中的 $f_{i+1}+x$ 这一项替换掉。  

首先考虑 i 为偶数的情况。  
如果从 $i+1$ 转移过来得到答案，那么显然此时 $i+1$ 是由 $i+2$ 转移来的。此时我们连续执行了两次减一操作。显然我们可以先减一在乘二，所以这样肯定不优，因此 $i$ 为偶数的时候就没必要从 $i+1$ 转移了。  
然后考虑 $i$ 为奇数。  
如果从 $i+1$ 转移，那么显然 $i+1$ 肯定是由 $(i+1)/2$ 转移得来的，因为偶数不可能从更大的数字减一得到。

这样 DP 式就变成了
$$
f_i=\left\{
\begin{aligned}
& \min\{f_{i-1}+x,f_{(i+1)/2}+x+y\} & & x\text{为奇数} \\
& \min\{f_{i-1}+x,f_{i/2}+y\} & & x\text{为偶数}
\end{aligned}
\right.
$$
此时就可以直接 $O(n)$ 转移了。

```cpp
int n; ll x,y,f[maxn]; 
int main(){
	n=read(); x=read(); y=read(); int i; f[1]=x;
	for(i=2;i<=n;i++)
		if(i&1) f[i]=mmin(f[i-1]+x,f[(i+1)>>1]+x+y); 
		else f[i]=mmin(f[i-1]+x,f[i>>1]+y);
	print(f[n]); return 0;
}
```

---

## 作者：happybob (赞：1)

## 题意

题面描述十分清晰。

## 思路

CF 上有一个 tag 是搜索，但是尝试了许久，bfs 一直 WA，于是考虑 DP。

注意到范围 $n \leq 10^7$，显然考虑 $O(n)$ 的线性 DP。可以设 $f_i$ 表示生成长度为 $i$ 的最小代价，显然：

$f_i= \begin{cases} \min\{f_{i \div 2} + y,f_{i-1}+x\} & i \equiv 0 \pmod 2 \\ min\{f_{(i+1) \div 2 + x +y},f_{i-1}+x\} & \text{otherwise} \end{cases}$。

---

## 作者：XL4453 (赞：1)

### 解题思路：

有趣的 DP 题。

对于每一个奇数，都可以从两个方向转移过来（加一和减一），每一个偶数都可以从三个方向转移过来（一半，加一和减一）。

这其中比较麻烦的是从比自己大一的那一个转移过来，因为在一般的 DP 中是不能从后向前转移的，那么就考虑改变一下。

首先发现，任意一个数都不可能连续减两次一的，减一一定是发生在乘以二之后的，如果是加一之后那还不如不做，而在乘以二之后连续减两次一一定劣于在乘以二之前减一，这两种效果一样，但前一种一定更优。

根据这个，显然偶数是不可能从比自己大一的数转移过来的。

再往后推一步，任意一个奇数从比自己大一的数转移过来一定是从后一个数的一半乘以二然后在减一的，否则会与刚才的结论冲突。

-----

综上所述，实际的转移只有如下几种可能：

1. 当前数是偶数，从这个数的一半或比这个数小一的数转移过来。

2. 当前数是奇数，从比这个数大一的数的一半或比这个数小一的数转移过来。

形式化地，有：

$\begin{cases}f_i=\min(f_{i-1}+x.f_{\frac{x}{2}}+y)|i \mod2=0\\f_i=\min(f_{i-1}+x,f_{\frac{x+1}{2}}+y)|i \mod2=1\end{cases}$

-----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long f[10000005],n,x,y;
int main(){
	scanf("%lld%lld%lld",&n,&x,&y);
	for(int i=1;i<=n;i++){
		if(i&1)f[i]=min(f[i-1]+x,f[(i+1)/2]+x+y);
		else f[i]=min(f[i-1]+x,f[i/2]+y);
	}
	printf("%lld",f[n]);
	return 0;
}
```


---

## 作者：Umbrella_Leaf (赞：1)

一道比较好的 DP 题。

首先设出 DP 状态，即 $dp_i$ 表示从长度为 $1$ 的字符串转移到长度 $i$ 的字符串最少的代价。

但是这题能够从 $i+1$ 转移到 $i$，因此用通常的方法不大可做。因为要处理 $dp_i=dp_{i+1}+x$ 这个转移方式。

这是我们用分类讨论的思想

1. 如果 $i$ 是偶数，$dp_i$ 显然只能从 $i-1$ 和 $\dfrac{i}{2}$ 转移过来，因为如果从 $i+1$ 转移，那么 $dp_{i+1}$ 肯定从 $i+2$ 转移过来。那就等价于 $\dfrac{i}{2}+1\to i+2\to i+1\to i$，不如 $\dfrac{i}{2}+1\to \dfrac{i}{2}\to i$，后者比前者少一个 $x$ 的代价。

1. 如果 $i$ 是奇数，$dp_i$ 只能从 $i-1$ 和 $i+1$ 转移，根据偶数的情况 $i+1$ 肯定是从 $\dfrac{i+1}{2}$ 或者 $i$ 转移过来，那么要转移到 $i$ 就是 $\dfrac{i+1}{2}\to i+1\to i$。

综合一下， $dp_i=\min(dp_{i-1}+x,dp_{\left\lfloor\frac{i+1}{2}\right\rfloor}+y+x\times [i\,is\,an\,odd])$

注意数据范围，要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long x,y;
long long dp[10000005];
int main(){
	scanf("%d%lld%lld",&n,&x,&y);
	for(int i=1;i<=n;i++)
		dp[i]=min(dp[i-1]+x,dp[(i+1)/2]+y+x*(i&1));
	printf("%lld\n",dp[n]);
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

首先如果加了一个字符，然后再删肯定不优。

于是只有倍长后才能删去一个字符，此时长度一定为奇数。

于是分奇数和偶数长度考虑，无论如何都可以加一个字符，然后看是否倍长而来更优。

所以：

$f_i=\min\{f_{i-1}+x,f_{i/2}+y\},2\mid i$ 

$f_i=\min\{f_{i-1}+x,f_{(i+1)/2}+y+x\},2\nmid i$。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 1e7 + 100;
int n, x, y, dp[maxn];

signed main() {
    n = read(), x = read(), y = read();
    dp[1] = x;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + x;
        if (i & 1) dp[i] = min(dp[(i + 1) / 2] + y + x, dp[i]);
        else dp[i] = min(dp[i / 2] + y, dp[i]);
    }
    write(dp[n]);
    return 0;
}
```

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/121318817)

一道比较不错的 DP。

设 $f_i$ 表示当前字符串长为 $i$ 时的最小代价，发现这道题麻烦的地方在于 $f_i$ 可以从 $f_{i+1}$ 的地方转移过来。

分类讨论一下：

---------

$i$ 为偶数：

$i$ 为偶数时 $f_i$ 能从 $f_{i-1},f_{\frac{i}{2}},f_{i+1}$ 三个点转移过来，但是 $f_{i+1}$ 的转移路程是 $? \to f_{\frac{i+2}{2}} \to f_{i+2} \to f_{i+1} \to f_{i}$
，总代价是 $y+2x$，这显然不如 $? \to f_{\frac{i+2}{2}} \to f_{\frac{i}{2}} \to f_{i}$ 更优，总代价是 $y+x$。

所以 $i$ 为偶数的转移方程是 $f_{i}=\min\{f_{i-1}+x,f_{\frac{i}{2}}+y\}$。

---------

$i$ 为奇数：

$i$ 为奇数时 $f_i$ 能从 $f_{i-1},f_{i+1}$ 转移过来，接下来讨论 $f_{i+1}$ 的转移思路。

显然 $f_{i+1}$ 不能从 $f_{i}$ 转移，于是只能从 $f_{i+2},f_{\frac{i+1}{2}}$ 转移，发现 $f_{i+2}$ 又是个奇数，因此如果从 $f_{i+2}$ 转移的话路径只能是这样：

$? \to f_{\frac{i+1}{2}} \to f_{\frac{i+3}{2}} \to f_{i+3} \to f_{i+2} \to f_{i+1} \to f_{i}$

总代价是 $4x+y$，显然不如从 $f_{i+1}$ 的转移路径 $? \to f_{\frac{i+1}{2}} \to f_{i+1} \to f_{i}$，总代价是 $y+x$。

所以 $i$ 为奇数的转移方程是 $f_{i}=\min\{f_{i-1}+x,f_{\frac{i+1}{2}}+x+y\}$。

---------

所以最后的方程就是上面两个式子综合一下就好了。

Code：[GitHub CodeBase-of-Plozia CF710E Generate a String.cpp](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/Codeforces%20%E5%88%B7%E9%A2%98%E5%90%88%E9%9B%86/CF710E%20Generate%20a%20String.cpp)

```cpp
/*
========= Plozia =========
    Author:Plozia
    Problem:CF710E Generate a String
    Date:2021/6/22
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e7 + 5;
int n, x, y;
LL f[MAXN * 2 + 1];

int Read()
{
    int sum = 0, fh = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
    return sum * fh;
}
LL Min(LL fir, LL sec) { return (fir < sec) ? fir : sec; }

int main()
{
    n = Read(), x = Read(), y = Read();
    for (int i = 1; i <= n; ++i)
    {
        if (i & 1) f[i] = Min(f[i - 1] + 1ll * x, f[(i + 1) >> 1] + 1ll * x + 1ll * y);
        else f[i] = Min(f[i - 1] + x, f[i >> 1] + y);
    }
    printf("%lld\n", f[n]);
    return 0;
}
```

---

## 作者：JiaY19 (赞：0)

应该算一道简单题吧。

可惜蒟蒻还交了很多遍。

#### 思路

考虑DP。

就能发现。

每一个状态只能从它上一个，或者从它的二分之一处转移。

所以这不就一个DP板子吗。

推一下转移式。

第一个。

$$ f_{i} = \min(f_{i - 1} + x , f_{\frac{i}{2}} + y) $$

第二个。

$$ f_{i} = \min(f_{i - 1} + x , f_{\frac{i}{2} + 1} + y + x) $$

第一个用于能整除二时。

第二个用于不能整除二时。

因为当它不能整除二时，它只能选择减少一个（如果是加就直接转移了）。

代码就超级简单了。

#### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , x , y , f[10000010];

int read()
{
	int X = 0 , W = 1;
	char asd = getchar();
	while(!isdigit(asd))
	{
		if(asd == '-') W = -1;
		asd = getchar();
	}
	while(isdigit(asd)) X = X * 10 + (int)(asd - '0') , asd = getchar();
	return X * W;
}

signed main()
{
	n = read() , x = read() , y = read();
	f[1] = x;
	for(int i = 2;i <= n;i++)
	{
		f[i] = f[i - 1] + x;
		if(i % 2 == 1) f[i] = min(f[i] , f[i / 2 + 1] + x + y);
		else f[i] = min(f[i] , f[i / 2] + y);
	}
	cout << f[n];
	return 0;
}
```
完结撒花！

---

