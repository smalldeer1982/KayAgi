# Yet Another Minimization Problem

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

You can perform the following operation any number of times (possibly zero): select an index $ i $ ( $ 1 \leq i \leq n $ ) and swap $ a_i $ and $ b_i $ .

Let's define the cost of the array $ a $ as $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (a_i + a_j)^2 $ . Similarly, the cost of the array $ b $ is $ \sum_{i=1}^{n} \sum_{j=i + 1}^{n} (b_i + b_j)^2 $ .

Your task is to minimize the total cost of two arrays.

## 说明/提示

In the second test case, in one of the optimal answers after all operations $ a = [2, 6, 4, 6] $ , $ b = [3, 7, 6, 1] $ .

The cost of the array $ a $ equals to $ (2 + 6)^2 + (2 + 4)^2 + (2 + 6)^2 + (6 + 4)^2 + (6 + 6)^2 + (4 + 6)^2 = 508 $ .

The cost of the array $ b $ equals to $ (3 + 7)^2 + (3 + 6)^2 + (3 + 1)^2 + (7 + 6)^2 + (7 + 1)^2 + (6 + 1)^2 = 479 $ .

The total cost of two arrays equals to $ 508 + 479 = 987 $ .

## 样例 #1

### 输入

```
3
1
3
6
4
3 6 6 6
2 7 4 1
4
6 7 2 4
2 5 3 5```

### 输出

```
0
987
914```

# 题解

## 作者：include_BM (赞：16)

这是一篇 dp 做法。

将所求式子展开：

$$
\begin{aligned}
  &\sum_{i=1}^n\sum_{j=i+1}^n (a_i+a_j)^2+\sum_{i=1}^n\sum_{j=i+1}^n (b_i+b_j)^2 \\
  =&\sum_{i=1}^n\sum_{j=i+1}^n(a_i^2+a_j^2+2a_ia_j)+\sum_{i=1}^n\sum_{j=i+1}^n(b_i^2+b_j^2+2b_ib_j) \\
  =&(n-1)(\sum_{i=1}^n a_i^2+\sum_{i=1}^n b_i^2)+2\times(\sum_{i=1}^n\sum_{j=i+1}^n a_ia_j+\sum_{i=1}^n\sum_{j=i+1}^n b_ib_j)
\end{aligned}
$$

可以发现 $(n-1)(\sum_{i=1}^n a_i^2+\sum_{i=1}^n b_i^2)$ 为定值，只需要计算剩余部分最小值即可。

设 $sum[i]=\sum_{j=1}^ia_j+\sum_{j=1}^ib_j$。

考虑 dp，设 $f[i][j]$ 表示只考虑前 $i$ 位，$\sum_{k=1}^i a_k=j$ 时的最大值（暂时不考虑系数 $2$，故为实际值的一半）。若不交换 $a_i,b_i$，$a_i$ 需要与 $a_1\dots a_{i-1}$ 相乘，$b_i$ 需要与 $b_1\dots b_{i-1}$ 相乘，那么可得：

$$f[i][j]=\min\left(f[i][j],f[i-1][j-a_i]+a_i\times(j-a_i)+b_i\times(sum[i-1]-j+a_i)\right)$$

若交换 $a_i,b_i$，即交换式子中 $a_i,b_i$ 位置，那么同理可得：

$$f[i][j]=\min\left(f[i][j],f[i-1][j-b_i]+b_i\times(j-b_i)+a_i\times(sum[i-1]-j+b_i)\right)$$

边界条件 $f[0][0]=0$，枚举 $i,j$ 转移即可，最终答案为 $(n-1)(\sum_{i=1}^na_i^2+\sum_{i=1}^nb_i^2)+2\times\min_{i=1} f[n][i]$。

---

## 作者：Hywel (赞：7)

#### 思路
$dp$ 是不可能 $dp$ 的，这辈子都不可能的

看到交换，我们可以想起模拟退火这种神奇的算法，对这个题来说，每次随机交换，然后把式子拆开：

$ cost = (n - 1) \cdot \sum_{i=1}^{n} a_i^2 + \sum_{i=1}^n (a_i \cdot (s - a_i))$

$= (n - 1) \cdot \sum_{i=1}^{n} a_i^2 + s^2 - \sum_{i=1}^{n} a_i^2$

$= (n - 2) \cdot \sum_{i=1}^{n} a_i^2 + (\sum_{i=1}^n a_i)^2$

就可以 $O(n)$ 计算贡献，为模拟退火提供充足随机次数，参数优秀的话是可以通过本题的。

#### Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define forever return
using namespace std;

namespace IO
{
    template < typename T > inline void write( T x )
    {
        if(x < 0)
            putchar('-') , x = - x;
        if(x == 0)
        {
            putchar('0') ;
            return ;
        }
        if(x > 9)
            write(x / 10) ;
        putchar(x % 10 + '0') ;
        return ;
    }
    template < typename T > inline void read( T &x )
    {
        x = 0 ; int w = 1 ; char ch = getchar() ;
        while( !isdigit( ch ) ) { if(ch == '-') w = -1 ; ch = getchar() ; }
        while( isdigit( ch ) ) x = (x << 1) + (x << 3) + (ch ^ 48) , ch = getchar() ;
        x *= w;
    }
}
#define writeln(x) write(x) , putchar('\n')
#define writesp(x) write(x) , putchar(' ')
using namespace IO ;

#define int long long
/* ------------------------------------------------------------------------------------------------------------------------ */
int n ;
const double delta = 0.993;
int a[1000],b[1000],ans;
inline int calc()
{
    ll res = 0 , asum = 0 , bsum = 0 , pfha = 0 , pfhb=0 ;
    for(int i = 1 ; i <= n ; ++ i)
    	asum+=a[i],bsum+=b[i],pfha+=a[i]*a[i],pfhb+=b[i] * b[i];
    res+=pfha*(n-1);res+=pfhb*(n-1);
    for(int i = 1 ; i <= n ; ++ i )
    	res += (asum-a[i])*a[i] , res += (bsum - b[i]) * b[i];
	return res;
}
inline void SA()
{
    double T=5000;
    while(T>1e-14)
    {
        int x=rand()%n+1;
        swap(a[x],b[x]);
        int nw = calc() ;
        int DE = nw-ans ;
        if( DE < 0 )
            ans=nw;
        else if(exp(-DE / T) * RAND_MAX < rand())
            swap(a[x],b[x]);
        T*=delta;
    }
}
signed main()
{
	srand(time(0));
    int T ;
    read( T ) ;
    double per = 1.95 / (double) T * 1.0;
    for(int nw = 1 ; nw <= T ; nw ++ )
    {
        read(n);
        for(int i = 1 ; i <= n; ++i)
            read(a[i]);
        for(int i = 1 ; i <= n ; ++ i )
            read(b[i]);
        ans=calc();
        while((double)clock()/CLOCKS_PER_SEC<(double)nw*1.0*per)
            SA();
        writeln(ans);
    }
    forever 0 ;
}
/*
1
2
9 8
72 83
*/


---

## 作者：ckain (赞：6)

考虑转换题目表述的对一个数组价值的计算式。

记原式 $\displaystyle S=\sum_{i=1}^{n} \sum_{j=i+1}^{n}(x_i+x_j)^2$。

原式乘以2，可以得到 $\displaystyle 2S=\sum_{i=1}^{n}\sum_{j=1}^n(x_i+x_j)^2-\sum_{i=1}^{n}(2x_j)^2$。

我们展开式子中的平方项

$\displaystyle 2S=\sum_{i=1}^{n}\sum_{j=1}^n(x_i^2 +2xy+x_j^2)-\sum_{i=1}^{n}4x_i^2$

$\displaystyle 2S=(2n-4)\sum_{i=1}^{n}x_i^2+2\sum_{i=1}^{n}\sum_{j=1}^nx_ix_j$

我们把先前乘上的2除掉

$\displaystyle S=(n-2)\sum_{i=1}^{n}x_i^2+\sum_{i=1}^{n}\sum_{j=1}^nx_ix_j$

这时侯观察式子，发现对于 $a,b$ 两数组，交换 $a_i,b_i$ 不会对第一项的答案产生变化，于是我们只用考虑最小化 $a, b$ 数组第二项的值。

单独把第二项拿出来

$T=\displaystyle \sum_{i=1}^{n}\sum_{j=1}^nx_ix_j$

我们考虑把它化成好进行dp的形式

$T=\displaystyle 2\sum_{i=1}^{n}\sum_{j=i+1}^nx_ix_j+\sum_{i=1}^nx_i^2$

这个式子的第二项同样是交换不会造成影响的，我们将其移出去。

现在写出最终化简出来的数组贡献式：

$S\displaystyle=(n-1)\sum_{i=1}^{n}x_i^2+2\sum_{i=1}^{n}\sum_{j=i+1}^nx_ix_j$

这时对第二项考虑dp即可。

由于发现题目中数的值域非常小，我们考虑第一维记枚举第 $i$ 个位置，第二维枚举 $a$ 到第 $i$ 位的前缀和。

code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline void rd(int &x){
	int s=0,f=1; char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=0; c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-48; c=getchar();}
	x=f? s:-s;
}
const int N=105, Max=1e4+5;
int T, n, a[N], b[N], dp[N][Max+5];
int sa[N], sb[N];
signed main(){
	rd(T);
	while(T--){
		rd(n);
		int s=0;
		for(int i=1; i<=n; i++){
			rd(a[i]), s+=(2*n-2)*a[i]*a[i];
			sa[i]=sa[i-1]+a[i];
		}
		for(int i=1; i<=n; i++){
			rd(b[i]), s+=(2*n-2)*b[i]*b[i];
			sb[i]=sb[i-1]+b[i];
		}
		dp[0][0]=0;
		for(int i=1; i<=n; i++){
			dp[i][0]=INT_MAX;
			for(int j=1; j<=Max; j++){//枚举 sigma a
				dp[i][j]=INT_MAX;
				if(j-a[i]>=0 && sa[i]+sb[i]-j-b[i]>=0)
					dp[i][j]=min(dp[i][j], dp[i-1][j-a[i]] + (j-a[i])*a[i] + (sa[i]+sb[i]-j-b[i])*b[i]);
				if(j-b[i]>=0 && sa[i]+sb[i]-j-a[i]>=0)
					dp[i][j]=min(dp[i][j], dp[i-1][j-b[i]] + (j-b[i])*b[i] + (sa[i]+sb[i]-j-a[i])*a[i]);//swap(a, b)
			}
		}
		int ans=INT_MAX;
		for(int i=1; i<=Max; i++)
			ans=min(ans, dp[n][i]);
		printf("%lld\n", (ans*4+s)/2);
	}
	return 0;
}
```

---

## 作者：donkeys (赞：4)

"数形结合百般好, 隔离分家万事休"

![](https://cdn.luogu.com.cn/upload/image_hosting/3dlx9yez.png)

针对一个数列, 计算的代价就是黄色覆盖的区域. 我们把单独一个代价拆分一下
$$
(a_i+a_j)^2=a_i^2+a_j^2+2a_ia_j
$$
然后我们分别考虑每个元素.

首先来看 $a_i^2$, 我们会统计到对应行的黄色格子数+对应列的黄色格子数次, 设总长度为 $n$ 的话,抽象一下就是 $(i-1)+(n-i)=n-1$ 次.

再看 $a_ia_j$.这种两项乘积的三角形求和有一个套路的处理方式,就是对称翻倍, 补出下图的红色部分.
![](https://cdn.luogu.com.cn/upload/image_hosting/9hvzgjet.png)

这个时候, 我们发现中间好像少了一些东西, 恰好是每个数的平方. 再想到我们之前计算过他们的出现次数是 $n-1$, 那不如找他们借一个, 把这个图形补成矩形.

结合上面的两步,我们就能得到一个数列的代价为
$$
(n-2)\sum_{i=1}^{n}a_i^2+(\sum_{i-1}^{n}a_i)^2
$$

## ~~**以下为废话**~~

然后考虑交换这个操作. 它会对结果产生什么本质影响?

首先它不会影响到第一项,因为针对每个 $i$ 的运算是独立的,交换后相加和不交换没有区别. 再看第二项, 考虑几何意义, 就是一个矩形的面积, 显然会受到影响. 我们设
$$
A=\sum_{i=1}^{n}a_i,B=\sum_{i=1}^{n}b_i
$$
$$
S=A+B
$$
那么交换 $a,b$ 中的元素也不会影响到 $S$. 和一定, 要求平方之和最小, 很容易想到均值不等式. 所以我们让 $A,B$ 之差尽可能小就好.

###### ~~**以上为废话**~~

做到这里我就很自然的想到了DP. 我们可以先最暴力的设 $f_{i,j,k}$ 为前 $i$ 个数, $a,b$ 的和分别为 $j,k$ 是否为合法方案. 但因为我们可以提前计算 $S$, 所以知道 $A,B$ 之一即可知道另一个,所以可以删掉一维, 然后转移的话就是考虑一个数是否要交换, 由 $i$ 转移到 $i+1$ 即可.

最后枚举一遍,直接套公式 $O(1)$ 爆算求最小(~~求出最小的差值然后代入公式~~)即可.

什么?代码?那是什么?~~(事实上是因为考场写的是差值转移比较麻烦所以不想贴但又懒得改)~~

---

## 作者：Jairon314 (赞：1)

> [题目链接](https://www.luogu.com.cn/problem/CF1637D)

$ \text{Solution} $

------------

首先拆开最初那个小式子：

$$ f(\{x_n\}) = \sum_{i=1}^{n} \sum_{j=i+1}^{n} (x_i+x_j)^2 $$

$$ = \frac{1}{2}(\sum_{i=1}^{n}\sum_{j=1}^{n}(x_i+x_j)^2-4\sum_{i=1}^{n}x_i^2) $$

$$ = \frac{1}{2}(\sum_{i=1}^{n}\sum_{j=1}^{n}(x_i^2+x_j^2+2x_ix_j)-4\sum_{i=1}^{n}x_i^2) $$

$$ =\frac{1}{2}(\sum_{i=1}^n(nx_i^2+\sum_{j=1}^{n}x_j^2+2x_i\sum_{j=1}^{n}x_j)-4\sum_{i=1}^nx_i^2) $$

$$ =\frac{1}{2}(n\sum_{i=1}^{n}x_i^2+n\sum_{i=1}^{n}x_i^2+2(\sum_{i=1}^{n}x_i)^2-4\sum_{i=1}^{n}x_i^2) $$

$$ = (n-2)(\sum_{i=1}^{n}x_i^2) + (\sum_{i=1}^{n}x_i)^2 $$

然后看看两行合并起来的式子：

$$ f(\{x_n\})+f(\{y_n\}) $$

$$ = (n-2)(\sum_{i=1}^n(x_i^2+y_i^2))+(\sum_{i=1}^{n}x_i)^2+(\sum_{i=1}^{n}y_i)^2 $$

$$ = (n-2)(\sum_{i=1}^{n}x_i^2+y_i^2) + $$
$$ (\sum_{i=1}^{n}x_i^2+2\sum_{i=1}^nx_i\sum_{j=1}^{i-1}x_j) +(\sum_{i=1}^ny_i^2+2\sum_{i=1}^ny_i\sum_{j=1}^{i-1}y_j) $$

$$ =(n-1)(\sum_{i=1}^{n}(x_i^2+y_i^2)) + 2(\sum_{i=1}^nx_i\sum_{j=1}^{i-1}x_j+\sum_{i=1}^ny_i\sum_{j=1}^{i-1}y_j) $$

> 操作：决定是否交换一些位置上的 $x_i$，$y_i$.

注意到无论怎么操作，前面这半个式子的值都是一定的，那么我们只需要使后面这个式子最小就可以了。

由于每个位置交换或不交换可以看作 $1$ 和 $0$，且每个操作对结果造成的影响比较小，容易想到动态规划这些小的影响从而得到最优解。注意到式子里有个前缀和，且这个前缀和的值域很小， $10^4$ 级别。所以考虑设一维跟前缀和有关的 $\operatorname{dp}$.

开始 $\operatorname{dp}$！

1. 发现前缀和不太好从之前状态确定，所以采用刷表法。

2. 注意到 $ {\forall k \in [1,n],  \sum_{i=1}^k x_i+y_i } $ 为定值，所以如果确定了操作完前 $k$ 个位置后的 $\sum_{i=1}^kx_i$，我们就可以 $O(1)$ 得到此时的 $\sum_{i=1}^ky_i$。

3. 设 $\operatorname{dp_{k,S}}$ 表示当前考虑到第 $k$ 个位置，操作后 $s = \sum_{i=1}^kx_i$ 时 $\sum_{i=1}^kx_i\sum_{j=1}^{i-1}x_j + \sum_{i=1}^ky_i\sum_{j=1}^{i-1}y_j$ 的值。

4. 对于每个位置都有两个方程，分别对应交换或者不交换的情况。

5. 边界条件 $\operatorname{dp}_{0,0}=0$，其他的位置初始都为正无穷。

可以写出以下方程：

若在这一位不交换，

$$ \operatorname{dp}_{k,s+x_k} = \min\{\operatorname{dp}_{k-1,s} + s\times x_k +(\sum_{i=1}^{k-1}(x_i+y_i)-s)*y_k \} $$

若在这一位交换，直接把上面式子的 $x_k$ 和 $y_k$ 换过来即可，

$$ \operatorname{dp}_{k,s+y_k} = \min\{ \operatorname{dp}_{k-1,s} + s\times y_k + (\sum_{i=1}^{k-1}(x_i+y_i)-s)*x_k \} $$

最后，枚举前缀和 $s$，答案就是最小的 $\operatorname{dp}_{n,s}$ 乘以 $2$ 加上一开始左半边的式子。

关于复杂度：

1. 注意到 $\sum_{i=1}^{k-1}(x_i+y_i)$ 可以在扫描过程中顺便 $O(1)$ 处理出来，所以不用算进复杂度里。

2. 注意到一开始左半边那个式子可以对于每组数据 $O(n)$ 预处理出来。

3. 设 $v$ 为前缀和值域，则最后的时间复杂度为 $O(\sum n \times \sum v)$

实现细节：

1. 注意两行前缀和爆出 $10000$ 的情况，因为是两行，所以最大的前缀和可能会是 $20000$ 这个量级的，但是爆的情况肯定不优，可以特判掉也可以直接数组开大一点。

------------

[点击查看缺省源"Jairon.h"](https://www.luogu.com.cn/paste/bckqxxoh)

```cpp
#include <bits/stdc++.h>
using namespace std;

#define lint long long

#include <"Jairon.h">

#define maxn 1000010
#define SIZE 5010

int n,ans=0;
int a[maxn];
int b[maxn];
int pre[maxn];
int dp[110][20010];

int main(){
	int T=read(_);
	while(T--){
		ans=0; read(n);
		FOR(i,1,n){ read(a[i]); }
		FOR(i,1,n){ read(b[i]); }
		if(n==1){ puts("0"); continue; }
		FOR(i,1,n){ ans+=sqr(a[i])+sqr(b[i]); }
		FOR(i,1,n){ pre[i]=pre[i-1]+a[i]+b[i]; }
		ans*=(n-1); int Mn=inf,res=0;
		FOR(i,1,n){ memset(dp[i],0x3f,sizeof dp[i]); }

		dp[0][0]=0;
		FOR(i,1,n){
			FOR(j,0,pre[i-1]){
				chmin(dp[i][j+a[i]],dp[i-1][j]+(j)*a[i]+(pre[i-1]-j)*b[i]);
				chmin(dp[i][j+b[i]],dp[i-1][j]+(j)*b[i]+(pre[i-1]-j)*a[i]);
			}
		}

		FOR(j,0,pre[n]){ if(dp[n][j]==inf){ continue; } chmin(Mn,ans+2*dp[n][j]); }
		outn(Mn);
	}
	return 0;
}

/**/
```


---

## 作者：Luciylove (赞：1)

考虑到一个数组 $x$ 的贡献为 ：

$$\sum_{1\leq i<j\leq n}(x_i+x_j)^2$$

略微展开得到 ：

$$\sum_{1\leq i<j\leq n}(x_i^2+x_j^2+2x_ix_j)$$

定义 **在右半边** 为有序点对 $(u, v)$ 产生贡献时，因为 $v > u$ ，$v$ 则被称为在 **在右半边的** ， 那么， 左半边的定义也照猫画虎。

考虑到对于第 $i$ 个位置上的元素 $x_i^2$ 会出现在 $[1,i-1]$ 的右半边， 和 $[i+ 1,n]$ 的这一部分则会在其作为左半边的时候的右半边。

那么可以化简得 ：

$$(n-1)\sum_{1\leq i\leq n}x_i^2 + \sum_{1\leq i<j\leq n}2x_ix_j$$

右边这个牵扯了两项显然不太好计算可以稍微做做手脚 ：

我们记 :

$$sum_i = \sum_{i<j\leq n}x_j$$

标志性的， 我们记录 $a$ 数组的为 $suma_i$ ， $b$ 数组同理。

合并得 ：

$$(n-1)\sum_{1\leq i\leq n}x_i^2+ \sum_{1\leq i\leq n}2x_isum_i$$

带入得:

$$(n-1)\sum_{1\leq i\leq n}a_i^2+ (n-1)\sum_{1\leq i\leq n}b_i^2+ \sum_{1\leq i\leq n}2a_isuma_{i}+\sum_{1\leq i\leq n}2b_isumb_i$$

显然这个问题变为了最优化后面那个东西 ：

咋做捏 ： 我们考虑对于 $i$ 一定， $suma_i$ 和 $sumb_i$ 是可以互相转化的， 一个有前途的 DP 就出来了 (有没有感觉有点像那个牛马 $\rm varience$ DP 题) ：

考虑到往前填往后填没啥区别， 所以这里默认往前填， 我们设 $f_{i,s}$ 为 $a$ 数组填了 $i$ 位， 和为 $s_a$ 的最小值。

$$f_{i,s_a} = \min\{f_{i -1, s_a - a_i} + 2a_i(s_a-a_i) +2b_i(s_b-b_i), f_{i -1, s_a - b_i} + 2a_i(s_b-b_i) +2a_i(s_b-a_i)\}$$

快乐暴力转移就完了 :D ， 具体实现可以看其他题解。

---

## 作者：Morgen_Kornblume (赞：1)

## 闲话

昨天打 CGR-19 的时候，就像大本钟上送外卖——上面寄，下面摆，第二道题卡死以后就彻底摆了，放飞自我（已经结束了 Nanoda！），和男足被别人进一个球就士气崩溃的精神差不多。

然后，掉大分！！！

## 正题

本题难度：蓝（提高+ / 省选-）。

标签：数学，DP。

直接上数学推导过程：

原式： 

$\sum_{i=1}^{n}\sum_{j=i+1}^{n}(a_i+a_j)^2$

展开：

$=\sum_{i=1}^{n}\sum_{j=i+1}^{n}(a_i^2+2a_ia_j+a_j^2)$

分离 $a_i$ 与 $a_j$。

$=\sum_{i=1}^{n}[a_i^2(n-i)+2a_i\sum_{j=i+1}^{n}a_j+\sum_{j=i+1}^{n}a_j^2]$

因为关于 $b$ 的式子和关于 $a$ 的式子同理，所以把它们直接相加并且化简，就是答案要求的式子：

$=\sum_{i=1}^{n}[(a_i^2+b_i^2)(n-i)+2a_i\sum_{j=i+1}^{n}a_j+2b_i\sum_{j=i+1}^{n}b_j+\sum_{j=i+1}^{n}(a_j^2+b_j^2)]$

对于原来的两个数组，我们可以发现一些显然的性质：

1. $\sum_{j=i+1}^{n}(a_i^2+b_i^2)$ 为定值。

2. $\sum_{j=i+1}^{n}a_j+\sum_{j=i+1}^{n}b_j$ 为定值。

发现具体的求解过程中，当前结果与前面结果的联系仅在于后缀和，所以我们可以设计一个 DP 过程，来求解这个式子的最小值。

因为 $1 \leq a_i,b_i \leq 100$ ，所以 $\sum_{j=i+1}^{n}a_j \leq 10000$。

设 $s=\sum_{j=i}^{n}a_j$ ，

可以用 $dp_i,s$ 来表示当前位置 $i$ ，后缀和为 $s$ 时，结果的最小值。

从 $n$ 到 $1$，每次扫遍所有可能的后缀和，枚举交换和不交换进行计算转移即可，详细过程见以下代码。

```cpp
for(int i=n-1;i>=1;i--){
	//cul dp[i][j];
	for(int j=0;j<=10000;j++){//枚举后缀和
		dp[i][j+a[i]]=min(dp[i][j+a[i]],dp[i+1][j]+(a[i]*a[i]+b[i]*b[i])*(n-i)+2ll*a[i]*j+2ll*b[i]*(ts[i+1]-j)+tpfs[i+1]);
		dp[i][j+b[i]]=min(dp[i][j+b[i]],dp[i+1][j]+(a[i]*a[i]+b[i]*b[i])*(n-i)+2ll*b[i]*j+2ll*a[i]*(ts[i+1]-j)+tpfs[i+1]);
	}
}
```


注意多组数据要清空。

完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int T;

int n;

ll a[110];
ll b[110];

ll ts[110],tpfs[110];
//hzh und pf-uzh

ll dp[110][10110];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);

	cin>>T;
	
	while(T--){
		
		cin>>n;
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		
		memset(ts,0,sizeof(ts));
		memset(tpfs,0,sizeof(tpfs));
		for(int i=n;i>=1;i--){
			ts[i]=ts[i+1]+a[i]+b[i];
			tpfs[i]=tpfs[i+1]+a[i]*a[i]+b[i]*b[i];
		}
		
		memset(dp,0x3f,sizeof(dp));
		
		dp[n][a[n]]=dp[n][b[n]]=0;
		
		for(int i=n-1;i>=1;i--){
			//cul dp[i][j];
			for(int j=0;j<=10000;j++){
				dp[i][j+a[i]]=min(dp[i][j+a[i]],dp[i+1][j]+(a[i]*a[i]+b[i]*b[i])*(n-i)+2ll*a[i]*j+2ll*b[i]*(ts[i+1]-j)+tpfs[i+1]);
				dp[i][j+b[i]]=min(dp[i][j+b[i]],dp[i+1][j]+(a[i]*a[i]+b[i]*b[i])*(n-i)+2ll*b[i]*j+2ll*a[i]*(ts[i+1]-j)+tpfs[i+1]);
			}
		}
		
		ll ans=LLONG_MAX;
		for(int i=0;i<=10000;i++){
			ans=min(ans,dp[1][i]);
		}
		cout<<ans<<endl;
	}

	return 0;
}

```


---

## 作者：FiraCode (赞：0)

## 题意：
有 $A,B$ 两个序列，长度为 $n$。
定义一个序列 $a_1 , a_2 ... a_n$。

他的价值： 为 $\sum^{n}_{i=1} \sum^{n}_{j=i+1} (a_i + a_j) ^ 2$

我们可以交换 $a_i,b_i$ 的位置。

最后求 $A$ 的价值 $+$ $B$ 的价值最小。
 
## 题解思路：
先把计算价值的式子拆一下变成：

$k_1 (\sum^{n}_{i=1}a_i ^ 2) + k_2 (\sum^{n}_{i=1} \sum^{n}_{j=i+1}a_i \times a_j)$

已知 $k_1 = n - 1 , k_2 = 2$\
$=(n-1)(\sum^{n}_{i=1}a_i ^ 2) + 2(\sum^{n}_{i=1} \sum^{n}_{j=i+1}a_i \times a_j)$

我们可以发现，不论我们怎么改，$a_i$ 乘方的次数是不变的。

但我们能改变 $a_i \times a_j$ 的次数

我们定义 $S_a$ 为他们两两想乘的结果

设一个序列为：$(a_i , a_2 , a_3)$

$S_{(a_1,a_2,a_3)}$ $\Longrightarrow$ $S_{(a_1,a_2,a_3,a_4)}$ 他们有什么不同的地方呢？

其实他就是加上了 $a_4 (a_1 + a_2 + a_3)$

所以，我们就可以进行 DP 了。

因为我们只需要存 $a_1 + a_2 + a_3 ... + a_n$ 的 $sum$。

$dp_{sumA,sumB,i}$ 表示分配了 $a_1 ... a_i$，$b_1 ... b_i$ 为 $S_{(a_1 ... a_i)} + S_{(b_1 ... b_i)}$（$S$ 之前定义过了）。

就是当 $a_1 + a_2 + ... + a_i = sumA$ 并且 $b_1 + b_2 + ... + b_i = sumB$ 并且分配了前 $i$ 情况下 $S$ 的最小值。

当我们给 $a$ 序列增加一个 $x$，给 $b$ 序列增加一个 $y$ 时，$dp_{sumA,sumB}$ 其实就是加上 $x \times sumA , y \times sumB$。

实际上 $sumB$ 这一维是不需要的，因为我们有了 $dp_i$ 了，那么我们就知道了 $sumA + sumB$，我们就可以直接算出 $sumB$ 的值了。

其实 $dp_{sumA,sumB,i}$ 有很多是无意义的。

就比如 $sumA + sumB \ne (a_1 + a_2 + ... + a_n + b_1 + b_2 + ... + b_n)$，那么 $dp_{sumA , sumB , i}$ 就是无意义的。

那我们就删掉一维，因为 $sumA$ 只有一个唯一对应的一个 $sumB$，我们就把 $sumB$ 这一维压掉。

$O(n ^ 3)$ 个状态，转移时间为 $O(1)$，所以总时间复杂度为 $O(n ^ 3)$。

[【AC 记录】]()
## AC Code:
```
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 110 , M = 20010;
const long long INF = 1e15;
int n;
int a[N] , b[N];
long long dp[M] , tmpdp[M];
int main() {
	int T;
	cin >> T;
	while (T --) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
		for (int i = 0; i <= 100 * n; ++ i) dp[i] = tmpdp[i] = INF;
		tmpdp[0] = 0;
		int Sum = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= 100 * n; j++) {
				int tmp1 = j, tmp2 = Sum - j;//算出sumA,sumB 
				if (tmpdp[j] == INF) continue;
				dp[j + a[i]] = min(dp[j + a[i]], tmpdp[j] + a[i] * tmp1 + b[i] * tmp2);//用了滚数组优化 
				dp[j + b[i]] = min(dp[j + b[i]], tmpdp[j] + a[i] * tmp2 + b[i] * tmp1);
			}
			Sum += a[i] + b[i];
			for (int j = 0; j <= 100 * n; j++) {
				tmpdp[j] = dp[j];
				dp[j] = INF;
			}
		}
		long long sum1 = INF, sum2 = 0;
		for (int i = 0; i <= 100 * n; i++) sum1 = min(sum1, tmpdp[i]);//看DP[sumA]最小的是多少
		for (int i = 0; i <= n; i++) sum2 += (a[i] * a[i] + b[i] * b[i]);//就是平方的那个 
		printf("%lld\n", sum2 * (n - 1) + sum1 * 2);//输出答案 
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1800}$
---
### 解题思路：

先进行一个式子的推。

$\sum_{i=1}^n\sum_{j=i+1}^n(x_i^2+2x_ix_j+x_j^2)$

$=(n-1)\sum_{i=1}^nx^2_i+2\sum_{i=1}^n\sum_{j=i+1}^nx_ix_j$。

可以发现，式子的前一半是固定的，变动只有后一半，可以推导至更数学化的水平，但是没有必要，不妨直接用这个式子进行动态规划。

设 $f_{i,j}$ 表示目前考虑到第 $i$ 个位置，其中上面一列的 总和为 $j$，下面一列总和为 $sum-j$ 的最小代价。

转移增加的代价为 $j\times x_i+(sum-j)\times y_i$，直接做就好了。

--- 
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
int T,n,x[105],y[105],sum[105],m,f[105][100005],ans;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		for(int i=1;i<=n;i++)scanf("%I64d",&x[i]),sum[i]=x[i];
		for(int i=1;i<=n;i++)scanf("%I64d",&y[i]),sum[i]=sum[i]+sum[i-1]+y[i];
		m=sum[n];
		memset(f,0x3f3f,sizeof(f));
		f[0][0]=0;
		for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++){
			if(j>=x[i])
			f[i][j]=min(f[i][j],f[i-1][max(0ll,j-x[i])]+x[i]*(j-x[i])+(sum[i]-j-y[i])*y[i]);
			
			if(j>=y[i])
			f[i][j]=min(f[i][j],f[i-1][max(0ll,j-y[i])]+y[i]*(j-y[i])+(sum[i]-j-x[i])*x[i]);
		}
		ans=f[n][0];
		for(int i=1;i<=m;i++)
		ans=min(ans,f[n][i]);
		ans*=2;
		for(int i=1;i<=n;i++)
		ans+=(n-1)*x[i]*x[i];
		for(int i=1;i<=n;i++)
		ans+=(n-1)*y[i]*y[i];
		printf("%I64d\n",ans);
	}
	return 0;
}
/*

1
2
1 4
2 3
*/
```


---

## 作者：Cocoly1990 (赞：0)

首先要考虑拆项

$$\left(a+b\right)^2=a^2+2\times a\times b+b^2$$

发现 $a^2,b^2$ 的贡献是恒定值，可以单独计算，下属贡献均指中间 $2\times a\times b$ 的那一项。

设 $f_{i,j}$ 为统计到前 $i$ 项，$\sum\limits_{k=1}^i a_k=j$ 的最小答案。

考虑添加一个数 $a_i$ 到 $a$ 中，他的贡献其实是 $2\times j\times a_i$.这很显然是正确的，因为他的贡献只和前面的数的和有关，所以 dp 的状态也是可以实现的。

所以可以转移

$$f_{i,j}=\min\{f_{i,j},f_{i-1,j-a_i}+\texttt{value},f_{i-1,j-b_i}+\texttt{value}\}$$

$\texttt{value}$ 用上述方法计算。

$b_i$ 的添加同理。

---

## 作者：清烛 (赞：0)

upd：感谢评论区提醒，锅已修。

感觉这场里面出的很好的一道题！

题意：给定两个长度为 $n$ 的数组 $a$ 和 $b$，可以进行若干次交换 $a_i$ 和 $b_i$ 的操作，求最后最小的

$$
\sum_{i=1}^n\sum_{j=i + 1}^n(a_i + a_j)^2 + \sum_{i=1}^n\sum_{j=i + 1}^n(b_i + b_j)^2
$$

$n$ 和值域的范围都是 $100$。

我们首先拆开式子，发现平方项的贡献为 $\sum_{i=1}^n(n-1)(a_i^2+b_i^2)$，是固定的，所以只需要考虑剩下的乘起来的部分即可。

然后呢，我们先考虑 $a$ 数组，则剩下的部分为

$$
2\sum_{i=1}^n\sum_{j=1}^{i-1}a_ia_j = 2\sum_{i=1}^na_i\sum_{j=1}^{i-1}a_j
$$

然后我们的操作是交换 $a_i$ 和 $b_i$，意思就是对于每个 $i$ 我们都有两种决策，换/不换。而一个很自然的拆贡献的想法就是，$a_i$ 在这一位产生的贡献是 $2a_i\sum_{j=1}^{i-1}a_j$，即和前缀和有关。

然后值域又这么小，所以考虑一个类似 NOIP21 T3 的 DP，设 $f_{i,s_1, s_2}$ 为当前考虑了 $i$ 位，前 $i$ 位 $a$ 的前缀和为 $s_1$，前 $i$ 位 $b$ 的前缀和为 $s_2$ 的最优解。然后发现 $s_1$ 知道之后 $s_2$ 是确定的，所以状态定义里面 $s_2$ 可以去掉。

转移就很好写了。

$$
f_{i, s_1} = \min\{f_{i - 1, s_1 - a_i} +  2a_i(s_1 - a_i) + 2b_i(s_2 - b_i), f_{i-1,s_1 - b_1} + 2b_i(s_1 - b_i) + 2a_i(s_2 - a_i)\}
$$

时间复杂度为 $O(n^3)$（视 $n$ 和值域同阶）。

```cpp
using ll = long long;
const int maxn = 105 + 5;
int a[maxn], b[maxn], n;
map<int, ll> f[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        FOR(i, 1, n) read(b[i]);
        FOR(i, 0, n) map<int, ll>().swap(f[i]);
        int sum = 0;
        f[0][0] = 0;
        FOR(i, 1, n) {
            sum += a[i - 1] + b[i - 1];
            for (auto &p : f[i - 1]) {
                int s1 = p.first, s2 = sum - s1;
                if (!f[i].count(s1 + a[i])) f[i][s1 + a[i]] = p.second + 2 * a[i] * s1 + 2 * b[i] * s2;
                else chkmin(f[i][s1 + a[i]], p.second + 2 * a[i] * s1 + 2 * b[i] * s2);
                if (!f[i].count(s1 + b[i])) f[i][s1 + b[i]] = p.second + 2 * b[i] * s1 + 2 * a[i] * s2;
                else chkmin(f[i][s1 + b[i]], p.second + 2 * b[i] * s1 + 2 * a[i] * s2);
            }
        }
        ll ans = 1e12;
        for (auto p : f[n]) chkmin(ans, p.second);
        FOR(i, 1, n) ans += (n - 1) * (a[i] * a[i] + b[i] * b[i]);
        print(ans);
    }
    return output(), 0;
}
```

---

## 作者：y0y68 (赞：0)

作为D题还是很水的吧

将题中计算总价值的式子拆开，设 $sum=(\sum_{i=1}^{n}a_i^2)+(\sum_{i=1}^{n}b_i^2),s_1=\sum_{i=1}^{n}a_i,s_2=\sum_{i=1}^{n}b_i$，则总价值为 $(n-2)\times sum+{s_1}^2+{s_2}^2$。显然 $sum$ 的值是不会改变的，$s_1+s_2$ 为定值，$s_1$ 不会超过 $10^4$，所以可以枚举所有可行 $s_1$ 计算总价值最小值。

所以问题变为如何判断一个 $s_1$ 是否可以通过交换 $a_i,b_i$ 得到，可以 DP，设 $dp[i][j]$ 表示 $\sum_{k=1}^{i}a_k$ 是否可以为 $j$，直接转移即可。

时间复杂度 $O(n^2V)$，$V$ 为 $a_i$ 的值域。

```
#include<bits/stdc++.h>
using namespace std;
bool dp[105][10005];
int T,n,a[105],b[105];
int main(){
	for(cin>>T;T;T--){
		cin>>n;int s=0;
		for(int i=1;i<=n;i++)cin>>a[i],s+=a[i];
		for(int i=1;i<=n;i++)cin>>b[i],s+=b[i];
		dp[0][0]=1;
		for(int i=1;i<=n;i++)
			for(int j=0;j<=s;j++){
				if(j>=a[i])dp[i][j]|=dp[i-1][j-a[i]];
				if(j>=b[i])dp[i][j]|=dp[i-1][j-b[i]];
			}
		long long sum=0;
		for(int i=1;i<=n;i++)sum+=a[i]*a[i];
		for(int i=1;i<=n;i++)sum+=b[i]*b[i];
		long long ans=1e18;
		for(int i=0;i<=s;i++){
			if(!dp[n][i])continue;
			ans=min(ans,1ll*(n-2)*sum+1ll*i*i+1ll*(s-i)*(s-i));
		}
		cout<<ans<<endl;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=s;j++)dp[i][j]=0;
	}
	return 0;
}
```

---

