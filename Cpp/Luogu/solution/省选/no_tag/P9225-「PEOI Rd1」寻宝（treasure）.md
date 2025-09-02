# 「PEOI Rd1」寻宝（treasure）

## 题目描述

有一天 wrzSama 在寻宝，突然他掉到了一个神奇的房间里。这个房间里有 $n$ 个机器，第 $i$ 个机器可以生产 $2^i$ 个钻石。

具体地，wrzSama 可以用 $a_i$ 的时间开动第 $i$ 个机器，让它生产 $2^i$ 个钻石。这些机器有个很特殊的性质，每当他用一次第 $i$ 个机器后，会让它的开动时间 $a_i$ 加上 $b_i$。这意味着当他要第二次得到这 $2^i$ 个钻石时就需要 $a_i + b_i$ 的时间，每次不断累加，第 $x$ 次开动就需要 $a_i+(x-1)b_i$ 的时间。

wrzSama 需要得到至少 $2^n$ 个钻石来得到宝藏，请问他最少需要多长时间。

## 说明/提示

#### 样例解释

样例 1 解释：直接获得 $2^3$，花费 3 的时间。

样例 2 解释：获得 2 个 $2^1$，花费 3 的时间，然后再花 2 的时间获得一个 $2^2$，这样 wrzSama 就可以得到 $2 \times 2^1 + 2^2 = 8 = 2^n$ 了。

样例 3 解释：获得 2 个 $2^1$ 和 3 个 $2^2$。

---
#### 数据范围

**本题采用捆绑测试。**

|子任务|分值|特殊限制|
|:-:|:-:|:-:|
|$1$|$16$|$1 \leq n \leq 10$|
|$2$|$16$|$1 \leq n \leq 20$|
|$3$|$24$|$1 \leq a_i \leq 3 \times 10^3$|
|$4$|$44$|无|

对于 $100\%$ 的数据，保证 $1 \le n \le 10^3$，$1 \le a_i,b_i \le 10^7$。

## 样例 #1

### 输入

```
3
1 2 3
3 2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 2 100
1 2 1```

### 输出

```
5```

## 样例 #3

### 输入

```
4
1 2 100 100
1 2 1 1```

### 输出

```
15```

# 题解

## 作者：honglan0301 (赞：7)

## 题目分析

首先按照编号从小到大地考虑机器，可以发现当考虑到第 $i$ 台机器时，生产的钻石不是 $2^i$ 倍数的情况一定不优。那么想到 dp，设 $f(i,j)$ 表示前 $i$ 台机器生产了 $j\times 2^i$ 个钻石的最小花费，暴力实现的时间复杂度是指数级的，下面我们考虑优化。

第一个优化，根据 $a_i,b_i$ 的范围我们容易发现每台机器被启动的次数一定不会太多。具体来说启动 $k$ 次的花费是 $k\times a_i+{k\times (k-1)\over 2}\times b_i\geq {k\times(k+1)\over 2}$，而答案最大也只能是 $a_n$，于是 $k\leq \sqrt {2a_n}$，于是 $j$ 最大只需枚举到 $k\times{\sum_{p=1}^i 2^p\over 2^i}=2\sqrt {2a_n}$。此时我们优化到了 $O(n\times a_n)$。

第二个优化，再考虑能否快速转移。我们列式子有 $f_{i,j}=\min \{ f_{i-1,2\times k}+(j-k)\times a_i+{(j-k-1)(j-k)\over 2}\times b_i\}$，而在每一轮转移中与 $i$ 相关的东西都是固定的，所以转化成 $g_j=\min \{h_k+(j-k)\times a+{(j-k-1)(j-k)\over 2}\times b\}$ 这种形式。那么发现可以斜率优化，横坐标单增，使用单调队列维护下凸壳。总时间复杂度优化到了 $O(n\sqrt {a_n})$，可以通过本题。

## 代码

```cpp
/*
  author: PEKKA_l  
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
#define int long long

int n,a[1005],b[1005],dp[9005],g[9005],head,tail,q[9005];

int gety(int x,int k) {return g[k]+k*(k+1)*b[x]/2-a[x]*k;}

signed main()
{
	cin>>n; for(int i=1;i<=n;i++) cin>>a[i]; for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=0;i<=9000;i++) dp[i]=a[1]*i+b[1]*(i-1)*i/2;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=4500;j++) {g[j]=dp[j<<1]; g[j+4500]=100000000000000000;} head=tail=1;
		for(int j=1;j<=9000;j++)
		{
			while(head<tail&&(double)(gety(i,q[tail])-gety(i,q[tail-1]))/(q[tail]-q[tail-1])>=(double)(gety(i,j)-gety(i,q[tail]))/(j-q[tail])) tail--;
			q[++tail]=j;
			while(head<tail&&b[i]*j>=(double)(gety(i,q[head+1])-gety(i,q[head]))/(q[head+1]-q[head])) head++;
			dp[j]=g[q[head]]+a[i]*(j-q[head])+(j-q[head]-1)*(j-q[head])*b[i]/2;
		}
	}
	cout<<dp[1]<<endl;
}
```


---

## 作者：dead_X (赞：5)

这也能紫题吗哥？

首先显然答案不会超过 $a_n$，所以每层只能取 $\sqrt{2a_n}$ 个。

考虑从前往后 DP，每层选若干个之后 $\div2$ 转移到下一层。

然后你用脚都能看出来前 $x-1$ 层的决策和第 $x$ 层的决策都是凸的，所以直接双指针扫一遍（你也可以叫它闵可夫斯基和）处理当前层决策即可。

时间复杂度 $O(n\sqrt v)$。

---

## 作者：cfkk (赞：0)

`by wrzSama`

### subtask 1

爆搜。

### subtask 2

用 $dp_{i,j}$ 表示使用前 $i$ 个机器获得 $j \times 2^i$ 的价值需要的最小时间，转移时枚举开动几次第 $i$ 级机器，然后取 $\min$ 即可。

### subtask 3

直接开动第 $n$ 个机器会使用 $a_n$ 的时间，所以答案不会大于 $a_n$。由于 $b_i \ge 1$，所以任何机器开动 $i$ 次都至少需要 $\dfrac{i(i+1)}2$ 的代价，所以任意一个机器都不会被开动多于 $\sqrt{2a_n}$ 次。因此前 $i$ 个机器不会制造出多于 $2^i \times 2 \sqrt{2a_n}$ 的价值，所以 $j$ 最大只用枚举到 $2 \sqrt{2a_n}$。

时间复杂度 $O(n \sqrt{a_n}^2) = O(na_n)$。

### subtask 4

用斜率优化就可以做到 $O(n \sqrt{a_n})$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,hd=1,tl;
ll a[1005],b[1005],dp[1005][10005];
struct node
{
	ll x,y;
}q[10005],lst[10005];
int main()
{
	n=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) b[i]=read();
	for(int i=0;i<=10000;++i) dp[1][i]=(a[1]+a[1]+(i-1)*b[1])*i/2;
	for(int i=0;i<=5000;++i)
	{
		lst[i].x=i;
		lst[i].y=(dp[1][i<<1]+(i+1)*i*b[2]/2-a[2]*i);
	}
	for(int i=2;i<=n;++i)
	{
		q[hd=tl=1]=lst[0];
		for(int j=1;j<=10000;++j)
		{
			if(j<=5000)
			{
				while(hd<tl&&(__int128)(q[tl].y-q[tl-1].y)*(lst[j].x-q[tl].x)>=(__int128)(lst[j].y-q[tl].y)*(q[tl].x-q[tl-1].x)) --tl;
				q[++tl]=lst[j];
			}
			while(hd<tl&&(q[hd+1].y-q[hd].y)<=(__int128)b[i]*j*(q[hd+1].x-q[hd].x)) ++hd;
			dp[i][j]=dp[i-1][q[hd].x<<1]+(a[i]+a[i]+(j-q[hd].x-1)*b[i])*(j-q[hd].x)/2;
		}
		for(int j=0;j<=5000;++j)
		{
			lst[j].x=j;
			lst[j].y=(dp[i][j<<1]+(j+1)*j*b[i+1]/2-a[i+1]*j);
		}
	}
	write(dp[n][1]);
	return 0;
}
//dp[i-1][k<<1]=dp[i][j]-(a[i]+a[i]+(j-k-1)*b[i])*(j-k)/2;
//dp[i-1][k<<1]=dp[i][j]-a[i]*(j-k)-(j-k-1)*b[i]*(j-k)/2;
//dp[i-1][k<<1]=dp[i][j]-a[i]*j+a[i]*k-j*j*b[i]/2+k*j*b[i]/2+(k+1)*b[i]*(j-k)/2;
//dp[i-1][k<<1]+(k+1)*k*b[i]/2-a[i]*k=b[i]*j*k+dp[i][j]-a[i]*j-(j-1)*j*b[i]/2;
//(k,dp[i-1][k<<1]+(k+1)*k*b[i]/2-a[i]*k)
```

---

## 作者：chroneZ (赞：0)

记 $f(i, j)$ 表示决策到第 $i$ 个，当前选 $j$ 次后完成，处理前的最小代价。记 $g(i, j)$ 表示第 $i$ 个选 $j$ 次的代价，即 $g(i, j) = \sum \limits_{x = 1} ^ j a_i + (x - 1) b_i = ja_i + \frac{(j - 1)j}{2}b_i$。

边界显然是 $f(n, 1) = 0, \text{others} = \infty$。

枚举该层选了多少个，得 $f(i, j) \to f(i - 1, 2(j - t)) + g(i, t)$。写成 $\gets$ 形式，$f(i, j) \gets \min \limits_{k} \{f(i + 1, k) + g(i + 1, k - \frac{j}{2})\}$。

为了便于计算，记 $h(i, j) = f(i, 2j)$，则 $h(i, j) \gets \min \limits_{k \geq \frac{j}{2}} \{h(i + 1, k) + g(i + 1, 2k - j)\}$。注意把边界条件改成 $h(n - 1, 0) = g(n, 1), h(n - 1, 1) = 0$。

直接做的话第二维的上界是 $\mathcal{O}(2 ^ n)$ 的。发现答案一定不会大于 $a_n$，因此一定会要求 $\forall i, g(i, j) \leq a_n$，$a, b$ 的下界都是 $1$，最劣情况下不等式可化为 $\frac{j(j + 1)}2 \leq a_n$，也就是说，一定会有 $j \leq \sqrt{2a_n}$，这样我们可以将第二维的上界缩小至 $\mathcal{O}(\sqrt{a_n})$。这样做状态数是 $\mathcal{O}(n\sqrt{a_n})$ 的，转移是 $\mathcal{O}(\sqrt{a_n})$ 的。

考虑优化转移。为了便于叙述，下文中 $f$ 代表上文中的 $h$。记当前考虑到第 $i$ 个，并记 $h(j) = f(i, j), p(j) = f(i + 1, j)$。将 $a_{i + 1}, b_{i + 1}$ 记作两常量 $A, B$，则转移可以写作 
$$
h(i) = \min \limits_{j \geq \frac{i}{2}} \{p(j) + (2j - i)A+ \frac{(2j - i)(2j - i - 1)}{2}B\}
$$
发现转移方程大致是斜率优化的形式。考虑斜率优化。将与 $j$ 无关的部分移到外面，得到
$$
h(i) = \min \limits_{j \geq \frac{i}{2}} \{p(j) + 2jA + (2j^2 - j - 2ij)B\} - iA + \frac{i(i + 1)}{2}B
$$

$$
h(i) + iA - \frac{i(i + 1)}{2}B = \min \limits_{j \geq \frac{i}{2}} \{p(j) + 2jA + (2j^2 - j - 2ij)B\}
$$

推一推斜率优化的几部分就行，注意尽量保证 $x_j, k_i$ 的单调性。
$$
\begin{aligned}
b_i &= h(i) + iA - \frac{i(i + 1)}{2}B \\
y_j &= p(j) + 2jA + (2j ^ 2 - j)B \\
k_i &= 2iB \\
x_j &= j
\end{aligned}
$$

$k_i, x_j$ 均递增，直接单调队列 + 斜率优化可以做到均摊 $\mathcal{O}(1)$ 转移。最终复杂度 $\mathcal{O}(n\sqrt{a_n})$。细节可参考代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;

const int N = 1e3 + 10, V = 1e7 + 10, M = 5000;

i64 n, w[N], d[N], f[N][M];

i64 b[M], y[M], k[M], x[M];

inline f64 slope(int i, int j) {return (f64)(y[j] - y[i]) / (x[j] - x[i]);}

int q[M], head, tail;

void work(int cur){
	i64 *h = f[cur], *p = f[cur + 1];
	const i64 A = w[cur + 1], B = d[cur + 1];
	// O(n * a_n) 做法
	// for(int i = 0; i < M / 2; i++){
	// 	for(int j = (i + 1) / 2; j < M / 2; j++){
	// 		h[i] = min(h[i], p[j] + (2 * j - i) * A 
	// 			+ (2 * j - i) * (2 * j - i - 1) / 2 * B);
	// 	}
	// }
    
	for(int i = 0; i < M / 2; i++)
		x[i] = i, y[i] = p[i] + 2 * i * A + (2 * i * i - i) * B;

	head = 0, tail = -1;
	for(int i = 0; i < M / 2; i++){
		while(head < tail){
			if(slope(q[tail - 1], q[tail]) > slope(q[tail], i)) tail--;
			else break;
		}
		q[++tail] = i;
	}

	for(int i = 0; i < M / 2; i++){
		k[i] = 2 * i * B;
		while(head < tail){
			if(q[head] < (i + 1) / 2 || slope(q[head], q[head + 1]) < k[i]) head++;
			else break;
		}
		b[i] = y[q[head]] - k[i] * x[q[head]];
		h[i] = b[i] - i * A + i * (i + 1) / 2 * B;
	}
}

int main(){
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); cout.tie(nullptr);
	
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> w[i];
	for(int i = 1; i <= n; i++)
		cin >> d[i];
	memset(f, 0x3f, sizeof f);
	f[n - 1][0] = w[n]; f[n - 1][1] = 0;

	for(int i = n - 2; i >= 0; i--)
		work(i);
	cout << f[0][0];
}
```





---

