# [ABC162F] Select Half

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc162/tasks/abc162_f

長さ $ N $ の整数列 $ A_1,...,A_N $ が与えられます。

この中からちょうど $ \left\lfloor\ \frac{N}{2}\ \right\rfloor $ 個の整数を、どの $ 2 $ 箇所も連続しないように選びます。

選んだ要素の和としてありえる最大値を求めてください。

ここで、$ \lfloor\ x\ \rfloor $ は、$ x $ を超えない最大の整数を表します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ |A_i|\leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

$ 2,4,6 $ を選ぶと和は $ 12 $ となり、これが最大です。

### Sample Explanation 2

$ -10,10 $ を選ぶと和は $ 0 $ となり、これが最大です。

### Sample Explanation 3

オーバーフローに注意してください。

## 样例 #1

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
12```

## 样例 #2

### 输入

```
5
-1000 -100 -10 0 10```

### 输出

```
0```

## 样例 #3

### 输入

```
10
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
5000000000```

## 样例 #4

### 输入

```
27
18 -28 18 28 -45 90 -45 23 -53 60 28 -74 -71 35 -26 -62 49 -77 57 24 -70 -93 69 -99 59 57 -49```

### 输出

```
295```

# 题解

## 作者：Grisses (赞：17)

[这道题](https://www.luogu.com.cn/problem/AT5281)很明显，一看就是 dp。

我们可以设$ dp_{i} $ 表示前 $ i $ 位取数取得的最大值，$ sum_i $ 表示前 $ i $ 个数中奇数位上的数的和，$ a_i $ 表示第$i$个数。

然后我们分类讨论一下

1. 当$i$是偶数时，选 $ \frac{i}{2} $ 个数。

我们可以将数列划分为 $ \frac{i}{2} $ 段，每段有2个数。而我们需要从每段中选出1个数。(参照下图)

![](https://cdn.luogu.com.cn/upload/image_hosting/uagenm4u.png)

对于 $ a_i $，我们可以选也可以不选。

如果要选$a_i$，则$a_{i-1}$就不能选，所以这时的和为 $ dp_{i-2}+a_i $。

如果不选，那么在$a_i$所在的这一段中，就只能选$a_{i-1}$。选了$a_{i-1}$之后， $ a_{i-2} $ 又不能选了，因此只能选$ a_{i-3} $ $ \cdots $ 所以我们只能选所有的奇数位上的数，和为 $ sum_{i-1} $。
(参照下图)

![](https://cdn.luogu.com.cn/upload/image_hosting/2dujrunz.png)

所以当 $ i $ 时偶数时，$ dp_i=\max (dp_{i-1}+a_i,sum_{i-1}) $。

2. 当 $ i $ 时奇数时，选 $\frac{i-1}{2}$ 个数。

对于 $ a_i $，我们也可以选或不选。

如果选了 $ a_i $，与 $ i $ 位偶数时同理，和为 $ dp_{i-2}+a_i $。

如果不选，那就是从前 $ i-1 $ 个里选 $ \frac{i-1}{2} $ 个数，即 $ dp_{i-1} $ 。

所以当$i$时奇数时，$ dp_i=\max(dp_{i-1},dp_{i-2}+a_i) $ 。

### 代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
long long int n,a[200005],sum[200005],dp[200005];//n是数的数量，a，sum，dp的意义同题解。
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1];//前缀和
		if(i%2==1)sum[i]+=a[i];//如果在奇数位上，就累加。
	}
	for(int i=2;i<=n;i++){
		if(i%2==1){//当i是奇数时
			dp[i]=max(dp[i-2]+a[i],dp[i-1]);
		}
		else{//当i是偶数时
			dp[i]=max(dp[i-2]+a[i],sum[i-1]);
		}
	}
	printf("%lld",dp[n]);
	return 0;
}
```

---

## 作者：Guess00 (赞：4)

本题思路$:\texttt{DP}$

首先分$n$是偶数还是奇数进行考虑，偶数只有两种取法，随便搞搞(我是按和奇数同样的方法做的)。下面考虑$n$为奇数时怎么做。

当$n$为奇数时，如果取的每两个数中间刚好隔一个数，最后两个数就没有取到，也就是说有两次机会取得时候多隔一个数。

考虑$\texttt{DP}.$令$f[i][0/1/2]$为使用了$0/1/2$次多隔一个数的机会取到第$i$个数和的最大值。

状态转移$:f[i][0]=f[i-2][0]+a[i]$

$\qquad\quad\;\;\; f[i][1]=max(f[i-2][1],f[i-3][0])+a[i]$

$\qquad\quad\;\;\; f[i][2]=max(f[i-2][2],f[i-3][1],f[i-4][0])+a[i]$

注意转移的时候下标不能越界。

$\mathbb{CODE:}$
```cpp
#include <bits/stdc++.h>
#define int long long
using std::max;
const int MAXN=200005;
int n,i,a[MAXN],f[MAXN][3];
inline void read(int &x)     //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)     //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
signed main(void)
{
	read(n);
	for (i=1;i<=n;i++)
		read(a[i]);
	if (!(n%2))     //n为偶数的情况 
	{
		f[1][0]=a[1];
		for (i=2;i<=n;i++)
			if (i%2)
				f[i][0]=f[i-2][0]+a[i];
			else
			{
				if (i>=3)
					f[i][1]=max(f[i-2][1],f[i-3][0])+a[i];
				else
					f[i][1]=f[i-2][1]+a[i];
			}
		return print(max(f[n-1][0],f[n][1])),0;
	}
	f[1][0]=a[1];           //n为奇数的情况 
	for (i=2;i<=n;i++)
		if (i%2)
		{
			f[i][0]=f[i-2][0]+a[i];
			if (i>=4)       //避免下标越界特判 
				f[i][2]=max(f[i-2][2],max(f[i-3][1],f[i-4][0]))+a[i];
			else
			{
				if (i>=3)
					f[i][2]=max(f[i-2][2],f[i-3][1])+a[i];
				else
					f[i][2]=f[i-2][2]+a[i];
			}
		}
		else
		{
			if (i>=3)
				f[i][1]=max(f[i-2][1],f[i-3][0])+a[i]; 
			else
				f[i][1]=f[i-2][1]+a[i];
		}
	print(max(f[n][2],max(f[n-1][1],f[n-2][0])));
	return 0;
}
```

---

## 作者：Otue (赞：4)

看了一下大家的做法，我感觉都比较复杂，本蒟蒻来发一篇通俗易懂的题解。

大致做法：动态规划

# 思路

设 $dp_i$ 表示前 $i$ 个数的最大可能和。

设 $sum_i$ 表示前 $i$ 个数所有奇数位置的和。

### 当 $i$ 为偶数时：

将这个序列划分成 $\frac{i}{2}$ 段，每段 $2$ 个数。由于要选 $\frac{i}{2}$ 个数，且这些数不相邻，则需要每一段都选出 $1$ 个数。（建议手动画图）

考虑第 $i$ 个数选与不选：
* 若选了第 $i$ 个数，则第 $i-1$ 个数就必须不选，答案为 $dp_{i-2}+a_i$。
* 若不选第 $i$ 个数，则在 $a_i$ 这一段中，则必须选第 $i-1$ 个数，选了第 $i-1$ 个数，就只能选第 $i-3$ 个数....所以答案为 $sum_{i-1}$。




### 当 $i$ 为奇数时：

需要在前 $i$ 个数中选出 $\frac{i-1}{2}$ 个数。

* 若选了第 $i$ 个数，同上。
* 若不选第 $i$ 个数，需要在前 $i-1$ 个数中选取 $\frac{i-1}{2}$ 个数，即 $dp_{i-1}$ 

综上所述，$dp_i=\max(dp_{i-2}+a_i,dp_{i-1})$.
# 代码
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long //不开long long会死
int n;
int a[200005],sum[200005];
int dp[200005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1];
		if(i%2==1) sum[i]+=a[i];
	} 
	dp[1]=0;//初始化 
	for(int i=2;i<=n;i++){
		if(i%2==0){
			dp[i]=max(a[i]+dp[i-2],sum[i-1]);
		}
		if(i%2==1){
			dp[i]=max(a[i]+dp[i-2],dp[i-1]);
		}
	}
	cout<<dp[n]<<endl;
}
```


---

## 作者：dz_ice (赞：2)

[博客里阅读](https://www.cnblogs.com/dzice/p/12690560.html)

题目大意：给定一个长度为$n$的数列，让你从中取出$\lfloor\frac{n}{2}\rfloor$个互不相邻的数，输出这$\lfloor\frac{n}{2}\rfloor$个数的和的最大值

一开始以为就是分类讨论，但最后一个样例怎么都过不去，比赛结束后5min才想到了一个和官方题解的DP不一样的神奇解法...错失涨分的良机

首先考虑$n$为偶数的情况，手动模拟一下可以发现只有一种情况，取前面一段为奇数位的数和后面一段为偶数位的数

如(1表示选，0表示不选，接下来讨论的亦如此)
```
1 0 1 0 0 1 0 1 0 1
0 1 0 1 0 1 0 1
```

然后就是$n$为奇数的情况，这里有一个神奇的性质，我们先来写出几种情况
```
1 0 1 0 0 0 1
1 0 1 0 1 0 0 1 0 1 0
1 0 1 0 0 1 0 1 0 0 1 0 1
```
情况多而杂，不好分类讨论，于是我们考虑有没有一种通式能够概括所有的情况，先考虑把奇数位的数全都取上，总共是$\lfloor\frac{n}{2}\rfloor+1$个数，只需要减少一个数就可以满足题目的要求

然后试着把全取奇数位的数与我在上面列出来的情况对比一下,注意看加粗的部分

1 0 1 0 **1** 0 1

1 0 1 0 **0** 0 1

1 0 1 0 1 0 **1 0 1** 0 1

1 0 1 0 1 0 **0 1 0** 1 0

1 0 1 0 **1 0 1 0 1** 0 1 0 1

1 0 1 0 **0 1 0 1 0** 0 1 0 1

是不是已经发现了，所有的情况都可以视为将全取奇数位的数进行一个**两端为1的区间的01翻转**（注意所选的区间不能为空），我们要确定这样的一个区间，使得所取的和最大，这个可以用我们熟悉的最大子段和，时间复杂度$O(n)$,如果还感觉没理解的话可以再手玩一下

代码很简短，感觉没理解的相信你看一下代码就懂了

```
#include<bits/stdc++.h>
#define int long long //记得longlong！！
using namespace std;
int n,a[200003],fsum[200003],bsum[200003],ans=-2e18,sum,su; //fsum[i]代表的是与i奇偶性相同的数的前缀和，bsum[i]代表的是与i奇偶性相同的数的后缀和
signed main()
{
	scanf("%lld",&n);
	for(int i=1; i<=n; i++)
		scanf("%lld",&a[i]);
	fsum[1]=a[1],fsum[2]=a[2],bsum[n]=a[n],bsum[n-1]=a[n-1];
	for(int i=3; i<=n; i++)
		fsum[i]=fsum[i-2]+a[i];
	for(int i=n-2; i>=1; i--)
		bsum[i]=bsum[i+2]+a[i];
	sum=fsum[n];
	if(n%2==0)
	{
		ans=max(fsum[n-1],fsum[n]);
		for(int i=1; i<=n; i+=2)
			ans=max(ans,fsum[i]+bsum[i+3]);
		cout<<ans;
		return 0;
	}
	for(int i=1; i<=n; i++)
		if(i%2==0)
			su+=a[i];
		else
			su=max(su-a[i],-a[i]),ans=max(ans,sum+su); //最大子段和
	cout<<ans;
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：1)

本题显然 dp，时间复杂度 $O(n)$。
### 思路分析
首先，我们从奇偶性考虑，求出所有奇数位上的前缀和。对于 $dp_i$，如果当前位置为偶数，那么如果不选，就只能选前面的所有的奇数，即为 $dp_i\gets sum_i$，如果选它，那么不能选前一个，就只能从前两个的数集中选择，即 $dp_i\gets dp_{i-2}+a_i$；如果为奇数，第一种还是选它，同上：$dp_i\gets dp_{i-2}+a_i$；如果不选，这时选的数量为 $\frac{i-1}{2}$，可以从前 $i-1$  个选取，即 $dp_i\gets dp_{i-1}$。每次操作取最大值，答案为 $dp_n$。注意 $i=1$ 时数组越界的情况，循环可以从 2 开始。时空复杂度均为 $O(n)$。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int n,a[maxn],sum[maxn],dp[maxn];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),sum[i]=sum[i-1]+(i%2?a[i]:0);
	for(int i=2;i<=n;i++){
		dp[i]=dp[i-2]+a[i];
		if(i&1) dp[i]=max(dp[i],dp[i-1]);
		else dp[i]=max(dp[i],sum[i]);
	}
	printf("%lld\n",dp[n]);
	return 0;
} 

```

---

## 作者：cqbzhyf (赞：0)

[题面](https://www.luogu.com.cn/problem/AT5281)

先看题，发现这道题其实是多倍经验……

实现只是简单的[动态规划](https://oi-wiki.org/dp/)，于是就开始定义：

 $dp_i$ 表示以 $a_i$ 结尾的最大可能和（选择了 $a_i$），因为题目要求选择 $\frac{n}{2}$ 个数，于是自然地想到会涉及奇偶性，于是预处理除了一个数组：**用于存储奇数号位的前缀和（同时覆盖偶数位）。**

有了这些，我们就可以快快乐乐地去实现 `DP` 了。

## 几点注意

1.状态转移时循环计数变量从 $2$ 开始（防止越界，因为后面用到了 $i-2$）；

2.开 **long long!!!**;

## 代码在这里

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,sum[200005],dp[200005],a[200005];
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		if(i&1)sum[i]+=a[i];
		sum[i]+=sum[i-1];
	}
	for(int i=2;i<=n;++i){
		dp[i]=dp[i-2]+a[i];
		if(i&1)dp[i]=max(dp[i],dp[i-1]);
        else dp[i]=max(dp[i],sum[i-1]);
	}
	printf("%lld",dp[n]);
	return 0;
}
```

---

## 作者：hanzhongtlx (赞：0)

这里再提供一种比较屑的 dp 方法。  

偶数就不说了，反正随便做做就好了。   

奇数有点麻烦，  

因为我们发现如果将整个序列划段（每段只选一个数），有一个段长度是 $3$。  

那就好说了！  

我们令 $f_{i,0/1,0/1}$ 为划分到第 $i$ 段是否划分出长度为 $3$ 的段，该段的最后一位是否被选的最大获益。  

对于第二维是 $0$ 的部分，当偶数做，转移很简单。  

现在主要来讨论第二维是 $1$ 的部分。 

显然可以得到：  

$$f_{i,1,0}=\max\{f_{i-1,1,0}+a_{2i},f_{i-1,0,0}+\max\{a_{2i-1},a_{2i}\},f_{i-1,0,1}+a_{2i}\}$$  

$$f_{i,1,1}=a_{2i+1}+\max\{f_{i-1,1,0},f_{i-1,1,1},f_{i-1,0,1},f_{i-1,0,0}\}$$  

最后答案是 $\max\{f_{h,1,0},f_{h,1,1}\}\;\;(h=\dfrac{n-1}{2}\;\text{即组数})$

然后转移就好了，时间复杂度是 $\mathcal O(n)$。  

```
#include"iostream"
#include"cstdio"
#include"cmath"
using namespace std;

#define MAXN 100005
#define ll long long
#define read(x) scanf("%d",&x)

int n,a[MAXN<<1];
ll dp[MAXN][2];
ll f[MAXN][2][2];

int main()
{
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	if(!(n&1))
	{
		for(int i=1;i<=n/2;i++) dp[i][0]=dp[i][1]=-1ll<<60;
		dp[1][0]=(ll)a[1],dp[1][1]=(ll)a[2];
		for(int i=2;i<=n/2;i++)
		{
			dp[i][0]=(ll)a[i*2-1]+dp[i-1][0];
			dp[i][1]=(ll)a[i*2]+max(dp[i-1][0],dp[i-1][1]);
		}
		printf("%lld\n",max(dp[n/2][0],dp[n/2][1]));
	}
	else 
	{
		int h=(n-1)/2;
		for(int i=1;i<=h;i++)
		{
			f[i][0][0]=f[i][0][1]=-1ll<<60;
			f[i][1][0]=f[i][1][1]=-1ll<<60;
		}
		f[1][0][0]=(ll)a[1],f[1][0][1]=(ll)a[2];
		f[1][1][0]=(ll)max(a[1],a[2]),f[1][1][1]=(ll)a[3];
		for(int i=2;i<=h;i++)
		{
			f[i][0][0]=f[i-1][0][0]+(ll)a[i*2-1];
			f[i][0][1]=(ll)a[i*2]+max(f[i-1][0][0],f[i-1][0][1]);
			f[i][1][0]=f[i-1][1][0]+(ll)a[2*i];
			f[i][1][0]=max(f[i][1][0],f[i-1][0][0]+(ll)max(a[2*i-1],a[2*i]));
			f[i][1][0]=max(f[i][1][0],f[i-1][0][1]+(ll)a[2*i]);
			f[i][1][1]=(ll)a[i*2+1]+max(f[i-1][1][0],f[i-1][1][1]);
			f[i][1][1]=max(f[i][1][1],max(f[i-1][0][1],f[i-1][0][0])+(ll)a[2*i+1]);
		}
		printf("%lld\n",max(f[h][1][0],f[h][1][1]));
	}
	return 0;
}
```

---

