# Towers

## 题目描述

The city of D consists of $ n $ towers, built consecutively on a straight line. The height of the tower that goes $ i $ -th (from left to right) in the sequence equals $ h_{i} $ . The city mayor decided to rebuild the city to make it beautiful. In a beautiful city all towers are are arranged in non-descending order of their height from left to right.

The rebuilding consists of performing several (perhaps zero) operations. An operation constitutes using a crane to take any tower and put it altogether on the top of some other neighboring tower. In other words, we can take the tower that stands $ i $ -th and put it on the top of either the $ (i-1) $ -th tower (if it exists), or the $ (i+1) $ -th tower (of it exists). The height of the resulting tower equals the sum of heights of the two towers that were put together. After that the two towers can't be split by any means, but more similar operations can be performed on the resulting tower. Note that after each operation the total number of towers on the straight line decreases by 1.

Help the mayor determine the minimum number of operations required to make the city beautiful.

## 样例 #1

### 输入

```
5
8 2 7 3 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
5 2 1
```

### 输出

```
2
```

# 题解

## 作者：dcmfqw (赞：31)

Updated in 20220920：优化了部分表述和格式。

## $O(n^3)$

首先肯定要统计前缀和 $pref_n=\sum\limits_{i=1}^{n}h_i$。

我们记 $dp_{i,j}$ 表示到原第 $i$ 号塔为止的最后一个塔是第原 $j+1$ 到 $i$ 号合成的。

那么显然有 $dp_{i,j}=\min\{dp_{j,k}+i-j-1\}$。

这里 $k$ 要满足 $pref_j-pref_k\le pref_i-pref_j$。

枚举 $k$ 即可。

但是这家伙是 $O(n^3)$，直接硬上去会 T 掉。

需要优化。

## $O(n^2)$

$i-j-1$ 的值与 $k$ 没关系，拎出来看看。

$dp_{i,j}=\min\{dp_{j,k}\}+i-j-1$

括号里剩下的只和 $j$ 与 $k$ 有关了。

那么对于每一个 $j$，只要知道 $dp_{j,k}$ 最小时的 $k$ 就行，这个 $k$ 记为 $dpfr_j$，这个最小值记为 $dpol_j$。

那么还有个限制条件不管了吗？

变个形：

$2\times pref_j-pref_i\le pref_k$

$pref_k$ 明显随递增而 $k$ 递增，左边又和 $k$ 无关。

然鹅只要有解，$dp_{j,k}$ 也随 $k$ 递增而递减，理由自己想。

所以，$dpfr_j$ 就是最大的有解的 $k$。

那么对于每个 $i$，找到最大的 $j$ 使其满足限制条件，然后将其作为 $dpfr_i$，并以此处理出 $dpol_i$。

那限制条件中的 $i$ 和 $j$ 都知道了，$k$ 是谁呢？

就是 $dpfr_j$ 了，理由自己想。

复杂度 $O(n^2)$，能过了。

贴个代码：

```
#include<bits/stdc++.h>
using namespace std;
const int _maxn = 5011;
int n, dpfr[_maxn], dpol[_maxn];
long long h[_maxn], pref[_maxn];
int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%lld", &h[i]);
    pref[i] = pref[i - 1] + h[i];
  }
  for(int i = 1; i <= n; ++i) {
    for(int j = i - 1; j >= 0; --j) {
      if(pref[i] - pref[j] >= pref[j] - pref[dpfr[j]]) {
        dpol[i] = dpol[j] + (i - j - 1);
        dpfr[i] = j;
        break;
      }
    }
  }
  printf("%d", dpol[n]);
  return 0;
}
```

## $O(n\log n)$

虽然过了题但还是不能停。

一种做法是楼上的巨佬讲的方法。

我的做法：很明显上面的 $dpfr_i$ 是随 $i$ 递增的。

这就是我们说的决策单调性！

然后就能优化到 $O(n\log n)$ 了。

我没有具体实现，要是假了告诉我。

## $O(n)$

既然都有了 $O(n\log n)$ 了那为什么不试一下 $O(n)$ 呢？

再转换一下限制条件：

$2\times pref_j+pref_{dpfr_j}\le pref_i$

好家伙这东西不就是单调队列了吗？。

知道怎么做的自己切题去吧。

没学过的自己 bdfs。

学过的但没头绪的看我的垃圾解说吧。

我们记 $dpva_i=2\times pref_i+pref_{dpfr_i}$ (就是左边那坨东西)

首先 $pref_i$ 随 $i$ 递增而递增，而且 $i$ 在我们的求解过程中递增，所以 $pref_i$ 会越来越大。

然额我们要求最大的 $j$。

那么对于两个候选为 $j$ 的数 $a,b$，如果 $a<b$ 还有 $dpva_a\ge dpva_b$。

说明只要 $b$ 合法，$a$ 就没有存在的必要。

但 $b$ 必然比 $a$ 先或同时合法。

那么我们要 $a$ 有何用？

所以我们维护一个 $dpva_i$ 单调递减的单调队列即可。

注意队头只用且必须留一个合法的数。

开始前把 $0$ 丢进去，它一定合法。

贴一下代码：

（好像比 $O(n^2)$ 的更慢了呜呜呜）

（也许是 $n$ 太小起不到效果吧）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _maxn = 5011;
int n, queu[_maxn], head, tail;
long long h[_maxn], dpva[_maxn], pref[_maxn], dpol[_maxn];
int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%lld", &h[i]);
    pref[i] = pref[i - 1] + h[i];
  }
  queu[tail++] = 0;
  for(int i = 1; i <= n; ++i) {
    while(head + 1 < tail && dpva[queu[head]] <= pref[i] && dpva[queu[head + 1]] <= pref[i])
      ++head;
    dpol[i] = dpol[queu[head]] + (i - queu[head] - 1);
    dpva[i] = (pref[i] << 1) - pref[queu[head]];
    while(head < tail && dpva[queu[tail - 1]] >= dpva[i])
      --tail;
    queu[tail++] = i;
  }
  printf("%lld", dpol[n]);
  return 0;
}
```

然后我们会惊奇地发现 [CSP-S2019 D2T2](https://www.luogu.com.cn/problem/P5665) 也有类似性质。

所以那题也顺带被我们做完了。

自己领双倍经验去。

---

## 作者：素质玩家孙1超 (赞：22)

题目意思：

你可以把第i座塔和i+1座或i-1座合并成一个

使得到的那座塔的高度是原来两座塔的和

问最使序列变成严格不增最小合并次数



------------

首先我想到的是贪心，然而贪心果断行不通（~~自证~~）

然后看到严格不增，那么如果i前面的塔符合要求，我们只要知道最后一个的高度就可以往后推

所以我们可以用DP做

S[i]代表前缀和 L[i]代表到i高度（合并之后）dp[i]表示到i都符合要求的最小合并次数

那么就有转移方程

```cpp
for(int i=1;i<=n;i++)
	for(int j=0;j<=i;j++)
		if(S[i]-S[j]>=L[j]&&dp[i]>=dp[j]+i-j-1)
		{
			dp[i]=dp[j]+i-j-1;
			L[i]=min(L[i],S[i]-S[j]);
		}
```

注意前面的初始化要把dp和L赋值为inf

代码QAQ

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int Maxn=5e3+5;
const int inf=1<<30;
inline int R()//快读 
{
	char c;int res;
	while((c=getchar())>'9'||c<'0');res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res;
}
int L[Maxn],dp[Maxn],S[Maxn],n;
int main()
{
	n=R();
	for(int i=1;i<=n;i++)//初始化 
	S[i]=S[i-1]+R(),dp[i]=L[i]=inf;
	for(int i=1;i<=n;i++) 
	for(int j=0;j<=i;j++)
	if(S[i]-S[j]>=L[j]&&dp[i]>=dp[j]+i-j-1)//状态转移 
	dp[i]=dp[j]+i-j-1,L[i]=min(L[i],S[i]-S[j]);
	printf("%d\n",dp[n]);
}
```



---

## 作者：Kobe303 (赞：13)

这里提供一种 $\text{O}(n^2)$ 的做法。

记 $sum_i=\sum_{j=1}^{i}h_j$，$f_i$ 表示前 $i$ 个塔要形成非递减序列所需要的最小操作次数，$g_i$ 表示前 $i$ 个塔形成非递减序列时最后一个塔的高度。

初始赋值：$f_0=0,g_0=-\infty$，其余的 $f$ 与 $g$ 均为 $\infty$。

转移为：$f_i=\min\limits_{0\le j\lt i,sum_i-sum_j\ge g_j}\left\{f_j+(i-j-1)\right\}$。

在计算 $f_i$ 时顺便维护一下 $g_i$ 就好了。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
int sum[N], n, a[N];
int f[N], g[N];

int main() {
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	f[0] = 0, g[0] = -100000;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (sum[i] - sum[j] < g[j]) continue;
			if (f[i] > f[j] + (i - j - 1)) {
				f[i] = f[j] + (i - j - 1);
				g[i] = sum[i] - sum[j];
			}
			else if (f[i] == f[j] + (i - j - 1)) {
				g[i] = min(g[i], sum[i] - sum[j]);
			}
		}
	}
	printf("%d", f[n]);
	return 0;
}
```


---

## 作者：王奕清 (赞：11)

## 提供一种n logn 做法

本题朴素 $n^{2}$ 做法如下：

枚举一个 $i$ 表示处理到 $i$ 个塔，

枚举一个 $j$ 表示前 $i$ 个塔合并完后，最后一个塔是由原来 $j+1$ 到 $i$ 的塔组成的，找到最大的 $j$。

**三个数组：**$sum_i$ 表示前 $i$ 个塔的高度之和，即前缀和数组

$dp_i$ 表示前 $i$ 个塔合并完后所需的最少操作数，

$h_i$ 表示 合并完后最后一个塔的高度。

那么就可以进行转移了：

```
for(int i=1;i<=n;i++)
	for(int j=i-1;j>=0/*0不要漏了，即所有的都选*/;j--)
	if(h[j]<=sum[i]-sum[j])
	{//我们只要找到最后一个符合条件的就可以了,因为要dp[i]最小和h[i]最小 
		h[i]=sum[i]-sum[j];//j+1~i,所以是sum[i]-sum[i] 
		dp[i]=dp[j]+i-j-1;//自己手推一下就好了 
		break;
	}
```
到现在，你就可以拿100分了，但是，怎么可以就止步于此呢？

## nlogn做法

我们发现，就上面这个式子：$h[j]<=sum[i]-sum[j]$ 似乎并不可以二分
，但是转换后可以得到：$h[j]+sum[j]<=sum[i]$ ，此时式子左边依旧没有单调性（这个可以自己手推一下），然而右边却是单调递增的。

所以，我就在枚举到第 $i$ 个塔时，二分出第一个大于 $h[i]+sum[i]$ 的$sum[p]$ 然后在$p$处打上一个 $i$ 的标记（这个标记时可以直接覆盖的，因为我们要的是最后一个，所以越后打上就越优）。

同时，我们用一个 $nx$ 来表示目前最大的 $j$ ，并每次和 $fl[i]$，取最大值（$fl[i]$ 即第 $i$ 个上的标记）

代码：
```
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	register int x=0;register char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int n,a[5005],dp[5005],h[5005],sum[5005],p,nx,fl[5005];
int main()
{
	n=read();
	for(register int i=1;i<=n;i++)
	a[i]=read(),sum[i]=sum[i-1]+a[i];
	sum[n+1]=1e9;
	h[1]=a[1];//第一个塔直接赋值就好了，因为只能选自己 
	p=lower_bound(sum+1,sum+n+2,h[1]+sum[1])-sum;
	fl[p]=1;nx=0;
	for(register int i=2;i<=n;i++)
	{
		nx=max(nx,fl[i]);
		dp[i]=dp[nx]+i-nx-1;//和原来的转移一模一样 
		h[i]=sum[i]-sum[nx];
		p=lower_bound(sum+1,sum+n+2,h[i]+sum[i])-sum;
		fl[p]=i;//打标记 
	}
	printf("%d",dp[n]);
}
//by wyq 
```
然而还是比n方的最优解慢好多，呜呜呜。

---

## 作者：小木虫 (赞：6)

### Preface  
这是一道练习单调队列的好（水）题。  
### Problem  
给定一个数列，可以将子串合并为一个数，合并花费为该子串长度，合并之后该子串变为一个数，即该子串所有数字之和，最后使其成为一个单调不降序列。  
### Solution  
看到这题我们首先就可以想到合并数字的一种线性 dp，我们发现每步递推是否合法仅仅与上一个子串有关，于是推出状态转移方程：  
$dp_{i,j}=(dp_{j,k}+(i-j-1))×[sum(k+1,j) \leq sum(j+1,i]$  
其中 $dp_{i,j}$ 代表推到第 $i$ 个数，上一个合并的子串为 $(j+1,i)$。  
这个玩意复杂度是 $O(n^3)$ 的，考虑优化。  
很显然，在同一个 $i$ 下，$j$ 越靠前那么就会越晚被转移到，  
如果在这种情况下其本身值还比前面的人要大的话它就是个废物，可以直接扔掉。  
于是现在我们对于每一个 $i$ 得到了一个从大到小依次排开的 dp 序列，越往后越大，也越晚被转移。  
当我们发现这个序列的第二个元素可以被转移时我们把第一个扔掉，这里的做法与 CSP2019-S 划分 的做法类似。  
依题意对于每个 $i$ 打出一个单调队列。  
code：  
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=5010;
int n;int h[N];
ll sum[N];int dp[N][N];int ans=1e9;
int Stack[N][N];int head[N];int tail[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]),sum[i]=sum[i-1]+h[i];
	for(int i=0;i<=n;i++)head[i]=1,tail[i]=0;
	Stack[0][++tail[0]]=0;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=0;j--){
			if(head[j]>tail[j]||sum[i]-sum[j]<sum[j]-sum[Stack[j][head[j]]])continue;
			while(head[j]<tail[j]&&sum[i]-sum[j]>=sum[j]-sum[Stack[j][head[j]+1]])head[j]++;
			dp[i][j]=dp[j][Stack[j][head[j]]]+(i-j-1);
			if(i==n)ans=min(ans,dp[i][j]);
			if(head[i]>tail[i]||(head[i]<=tail[i]&&dp[i][j]<=dp[i][Stack[i][tail[i]]]))
				Stack[i][++tail[i]]=j;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Godzilla (赞：3)

### $\mathtt{Description:}$

给定 $1$ 个序列，包含 $n$ 个数，每次可以合并相邻两个数，合并后的数为它们的和，求最少多少次操作可以将其变为 **非递减** 序列。

### $\mathtt{Solution:}$

发现一个性质，就是合并的数必然为 $1$ 个区间，那么可以按照最后合并的数是哪个区间进行分类讨论。

设 $f(i,j)$ 表示前 $i$ 个数，合并后最后 $1$ 个数的区间为 $(j,i)$ ，$p(i)$ 表示前缀和，有：

$f(i,j)=\min\{f(i-j,k)+(j-1)\}\quad(k\le i-j\;,\;p(i)-p(i-j)\le p(i-j)-p(i-j-k)$ 。

复杂度 $O(n^3)$ 。

固定 $i$ 发现随着 $j$ 的变大，转移集合也随之变大，那么 $k$ 的值就不用再枚举了，直接加就好了。

可以预处理 $g(i,j)$ 表示 $\sum\limits_{k=j}^{i}\min f(i,k)$ 。

复杂度 $O(n^2)$ 。

### $\mathtt{Code:}$

```c++
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

#define LL long long
#define PR pair<int,int>

using namespace std;

const int kN=5e3+5;
const int kInf=1e9;

int n;
int a[kN];
int f[kN][kN];
int p[kN];
int g[kN][kN];
int ans;

void Input(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		p[i]=p[i-1]+a[i];
	}
}

void Output(){
	ans=kInf;
	for(int i=1;i<=n;++i){
		ans=min(ans,f[n][i]);
	}
	printf("%d",ans);
}

int main(){
	Input();
	fill(f[0],f[0]+kN*kN,kInf);
	fill(g[0],g[0]+kN*kN,kInf);
	for(int i=0;i<2;++i){
		for(int j=0;j<2;++j){
			f[i][j]=g[i][j]=0;
		}
	}//初始化i=0/1的情况
	for(int i=2;i<=n;++i){
		int k=i-1;
		while(k>0&&p[i-1]-p[k-1]<=a[i]){
			k--;
		}//j=1的情况
		f[i][i]=i-1;//j=i的情况
		for(int j=1;j<i;++j){
			if(k<i-j){//排除无效状态
				f[i][j]=min(f[i][j],g[i-j][i-j-k]+(j-1));
			}
			while(k>0&&p[i-j-1]-p[k-1]<=p[i]-p[i-j-1]){
				k--;
			}//k的值减小，转移集合也就变大
		}
		for(int j=1;j<=i;++j){
			g[i][j]=min(g[i][j-1],f[i][j]);
		}//处理g数组
	}
	Output();
	return 0;
}
```



---

## 作者：JWRuixi (赞：2)

紫题，第一眼看到就开始冒汗，思路稍微有点烦。

- 题意

解读一下，其实就是把一个长度为 $n$ 序列分拆成 $m$ 个小块使得每个小块中在 $i$ 到 $j$ 的区间中有 $\sum\limits_{u=i}^j{a_{u}}$ 成递增顺序。

- 分析

所以说了那么多废话实际上就是想说这道题用贪心无法解决，因考虑动规的做法。

这时候这样想一下，如果我已经得到了上一个块的高度和，那么我就可以确定这一块的最小长度和最小高度，这样就有了状态转移方程：**在当前选中块合法的前提下有**

$dp_{i}=\min\limits_{i=1}^{n}{\{dp_{i}, dp_{j}+i-j-1\}}$

- 就讲完了，最后 Code：

```cpp
#include <bits/stdc++.h>
#define maxn 6000
using namespace std;
namespace q_wr {
	inline int read() {
		char c = getchar();
		int x = 0, f = 1;
		while (c < '0' || c > '9') {
			if (c == '-') f = -1;
			c = getchar();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + c - '0';
			c = getchar();
		}
		return x * f;
	}
	inline void write(int x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace q_wr;
int n, a[maxn], s[maxn], dp[maxn];
int main () {
	n = read();
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + (a[i] = read());
		dp[i] = 1e9;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {
			if (s[i] - s[j] >= a[j]) {//判断区间的合法性
				dp[i] = min (dp[i], dp[j] + i - j - 1);
				a[i] = min(s[i] - s[j], a[i]);//更新上一块的高度
			}
		}
	}
	write(dp[n]);
}
```


---

## 作者：HllwEureka (赞：2)

有一说一  ，这道题还蛮有意思的 ， 所以写个题解

看到这道题应该可以想到前缀和这个东东 ， 别问我为什么 ，问就是直觉 ，我们先把玩一波样例（~~这个样例太复杂了 ，我们自己整一个~~


```cpp
zdf[i].len 表示满足题目要求时此时的这个数并或不合并的最小值，若不需要合并也就是他自己本身 
```
可能略有些绕口 ，我们来推一下 ， 第一个数自然没有要求，也就是他本身 ， 第二个数我们来分类讨论 ，若第二个数 >= 第一个数 ，我们便不用将他们合并 ，也就是若sum[2] - sum[1] >= zdf[1].len ,则让 zdf[2].len = sum[2] - sum[1] （也就是不动）

但是要是第二个数 < 第一个数要怎么办呢 ？ 这时候就要把第二个数和第一个数合并 ，以此类推取一个满足条件的最小值 

![](https://cdn.luogu.com.cn/upload/image_hosting/n1swbt3j.png)

我们康康这组数据 ：可知zdf[1].len = 8 , zdf[2].len = 8 , zdf[3].len = 15 , zdf[4].len = 9

搞懂了这个奇怪的东西 ， 状态转移方程便迎刃而解了 //zdf[i].f 就是dp数组啦

dp[i] 表示前i个需要几次操作变成合法序列 
状态转移方程 ：dp[i] = dp[j] + (i - j  - 1)//也就是说再加上i+1到j需要合并的次数 

```cpp
	for (int i = 1 ; i <= n ; i++) {
		for (int j = 0 ; j < n ; j++) {
			if (sum[i] - sum[j] - zdf[j].len >= 0) {
				zdf[i].f = zdf[j].f + i - j - 1 , zdf[i].len = min(zdf[i].len , sum[i] - sum[j]) ; 
			}
		} 
	}
```
以上是核心代码

可能说的有些啰嗦了 ， 小萌新的第一篇题解 ， 希望可以给dalao们讲明白 orz 



---

## 作者：Boxxxxxx (赞：1)

博客连接[希望可以给点访问量](https://blog.csdn.net/qq_43804974/article/details/106482524)


因为我菜所以只能想到消耗空间大，时间复杂度差的做法但是我就是要发！！

首先这种题需要知道他是个dp（看不出来就GG），然后思考下怎么做，首先他是会进行区间合并，并且可以进行连续的合并，也就是把这个过程看做是一个连续区间合并的过程




[1,2]  [3,4,5] [6]

可以将一个序列分解为若干个区间（区间长度可以为1），但是区间必须是连续的，不能说你1和3去合并在一起，这是不允许的。

知道他是这样一个过程后要干嘛呢，我们可以设计dp转态

设 f[i][j] 表示[1,i]的序列都合法后，第i个与前j个位置一起合并的最少次数，也就是区间[i-j+1, i]作为一个连续区间。

为什么是这样子记录呢，因为在dp中一个很常见的做法的第二维度记录的是第i个位置所代表的权值。但是在这道题里的问题是权值的取值范围是取决于输入数据，即使离散化后这个权值的取值范围也可能达到一个很大的量级，这会导致我们的空间炸掉。

所以就有了上述的状态转移方程，同样是记录那些状态，但是我们换了种表示方法。

接下来思考转移

我是区间[i-j+1, i]作为一个连续区间，那么我这个区间的权值是固定的，上一个区间的最后一个位置是i-j，那么我们在i-j所在区间是可以获取信息，i-j这个位置往前合并了1个，2个，3个。。。。。


  这个大小取决于什么时候拿的权值超过当前i的区间所代表的权值就不行了。然后观察每个位置的高都大于1，区间权值具有单调性。我们就对于i-j这个位置最多可以合并多少个位置是可以二分出来的。

然后在先前记录一个答案的前缀min，就可以二分后O(1)得到答案。
复杂度就是O(n^2logn)

```cpp
int N,f[max_][max_],sum[max_],value[max_][max_];
il int getsum(int L, int R) {
	return sum[R] - sum[L - 1];
}
il void update(int x) {
	value[x][0] = inf;
	for (int i = 1; i <= x; i++) {
		value[x][i] = min(value[x][i - 1], f[x][i]);
	}
}

il int getv(int weizhi, int ht) {
	if (weizhi == 0)return 0; 
	if (getsum(weizhi, weizhi) > ht)return inf;
	int L = 1, R = weizhi;
	while (L < R){
		int mid = ((L + R) >> 1) + 1;
		//[1,mid]//[weizhi,weizhi - mid + 1]
		if (getsum(weizhi - mid + 1,weizhi) <= ht)L = mid;
		else R = mid - 1;
	}
	//[1,R]
	return value[weizhi][R];
}
signed main() {
	N = read();
	for (int i = 1; i <= N; i++) {
		sum[i] = read();
		sum[i] += sum[i - 1];
	}
	memset(f, 127, sizeof(f)); memset(value, 127, sizeof(value));
	f[1][1] = 0; update(1);
	for (int i = 2; i <= N; i++) {
		for (int j = 1; j < i; j++) {
			//[i-j+1,i]
			f[i][j] = getv(i - j, getsum(i - j + 1, i)) + j - 1;
		}
		f[i][i] = i - 1;
		update(i);
	}
	int ans = inf;
	for (int i = 1; i <= N; i++) {
		ans = min(ans, f[N][i]);
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：TainityAnle (赞：0)

- DP，但可以用 $O(n^2)$ 水过

在我发这篇题解的时候，前面已经有 9 位 dalao 发过了，我本以为自己的做法肯定重了，但是一一看完之后发现自己的做法和别人还是有区别的。

**题目大意：**

可以将任意一个数“移”到与它相邻的数上，所谓“移”，就是把这个数加到与它相邻的数上，然后把这个数删掉。问最少移几次能是这个序列成为一个非降序列。

**解题思路：**

- 定义一维**前缀和**数组 $a$，$a_i$ 表示初始状态下从第 $1$ 个数到第 $i$ 个数的总和，这里直接边输入边做前缀和即可，就像这样

```cpp
for(int i=1; i<=n; i++) cin>>a[i],a[i]+=a[i-1];
```

- 状态是二维的，比较乱，可以理解为 $f_{i,j}$ 表示当前已经合并完前 $i$ 个啦，现在管的是第 $i+1$ 个，且 $i+1$ 个是第 $j+1$ 个到第 $i$ 个合成的。

- 再枚举一个 $k$ 表示在满足 $a_j-a_k\le a_i-a_j$ 并且 $f_j<f_i$ 的情况下，$f_{i,j}$ 相当于 $f_{j,k}+i-j-1$。为什么要 ```+i-j-1``` 呢，因为我们不难看出，合并的区间是 $[i,j]$，所以合并次数就是 $i-j-1$ 啦。

- ~~获得成就：~~ 结束了？当然没有！，我们可以看到，这样的话时间复杂度是 $O(n^3)$，而 $n\le5000$ 然后就 TLE 啦。

- **优化**，我们真的必须要枚举 $k$ 吗，当然不用，我们不难想到用一个数组来记录，就叫它 $fm$ 吧，一开始的 $k$ 必定是 $0$，所以 $fm_0$ 为 $0$，后面，在满足 $a_j-a_k\le a_i-a_j$ 并且 $f_j<f_i$ 的情况下，$fm_i=j$。此时，我们就可以把 $k$ 替换为 $fm_j$，然后，我们的任务就完成啦！

- 注意初始化，$f$ 数组和 $fm$ 数组要赋值成为极大值。

~~这么简单的题就没必要附[代码](https://www.luogu.com.cn/paste/0k5e324m)了吧~~

---

