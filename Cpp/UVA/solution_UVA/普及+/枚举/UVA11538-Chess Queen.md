# Chess Queen

## 题目描述

你一定知道国际象棋是怎么玩的，以及皇后是怎么运作的吧。如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击。

例如，有两个皇后（一白一黑）放置在$2×2$的棋盘上，那么有$12$中放置方式可以使她们互相攻击。如下图所示。（见PDF版题面）

给出棋盘的大小，请你计算有多少种放置皇后的方式，可以使她们互相攻击。

## 样例 #1

### 输入

```
2 2
100 223
2300 1000
0 0```

### 输出

```
12
10907100
11514134000```

# 题解

## 作者：TemplateClass (赞：5)

简单计数题。

首先我们知道如果两个皇后在同一列，同一行或者同一对角线上，她们就会互相攻击，所以我们需要考虑 $3$ 种情况。

前 $2$ 种情况比较好统计，首先第 $1$ 个皇后放在任意一个位置，有 $mn$ 种方法，再在当前这一行或这一列选择另一个位置。因此前两种情况的方案数分别为 $mn(n - 1)$ 与 $mn(m - 1)$。

主要考虑对角线，我们知道，对于任意一个 $n \times m$ 的长方形（$n \le m$），同一个方向的对角线长度分别为（不理解的自己画一个图就明白了）：

$$1, 2, 3, \cdots, n - 1, \underbrace{n, n, n, \cdots, n}_{n - m + 1\ n}, n-1, n-2, n-3, \cdots, 1$$

这个式子左右两边之和是 $2 \sum\limits_{i = 1}^{n - 1} i$，再在这个对角线中选择另一个位置，所以就是 $2 \sum\limits_{i = 1}^{n - 1} i(i - 1)$。

中间的那些 $n$ 之和就是 $(n - m + 1) n$，再在其中选择另一个位置，所以就是 $(n - m + 1)(n - 1)n$。

其中：

$\begin{aligned}\sum\limits_{i = 1}^{n - 1} i(i - 1) &= \sum\limits_{i = 1}^{n - 1} i^2 - \sum\limits_{i = 1}^{n - 1} i \\ &= \dfrac{(2n - 1)(n - 1)n}{6} - \dfrac{(n - 1)n}{2} \\ &= \dfrac{(2n - 4)(n - 1)n}{3}\end{aligned}$

总和就为：

$\dfrac{(2n - 4)(n - 1)n}{3} + (n - m + 1)(n - 1)n = \dfrac{(3m - n - 1)(n - 1)n}{3}$

因为还有另一个方向上的对角线，所以上述结果还应 $\times 2$，即 $\dfrac{(3m - n - 1)(n - 1)2n}{3}$。

因此答案就为 $mn(n - 1) + mn(m - 1) + \dfrac{2(3m - n - 1)(n - 1)n}{3}$。

即 $mn(n + m - 2) + \dfrac{2(3m - n - 1)(n - 1)n}{3}$。

注意到上述讨论对角线的过程中我们假设 $n \le m$，所以如果输入数据中 $n \gt m$，直接交换即可。

值得注意的是，虽然题目保证答案在有符号 $64$ 位整数范围内，但是最好分析一下中间过程会不会爆 `long long`，如果不确定的话，最好用 `unsigned long long`。

代码就放个核心吧。（其实就是套公式，没啥可看的）

```cpp
while(true) {
	int a = read(), b = read();
	if(!a && !b) break;
	
	long long n, m;
	if(a > b) n = b, m = a;
	else n = a, m = b;
	
	write(n * m * (m + n - 2) + 2 * (3 * m - n - 1) * (n - 1) * n / 3);
	putchar('\n');
}
```

---

## 作者：МiсDZ (赞：4)

此题已经有大佬证明过了$\Theta(T)$的方法，蒟蒻再补充一种小学奥数的证明方法

已经得到了
$$
ans_1=C_m^1A_n^2=nm(n-1)
$$

$$
ans_2=C_n^1A_m^2=nm(m-1)
$$
ans1与ans2为在同一行与同一列互相攻击的皇后数

ans3为在同一斜列的互相攻击皇后数
显然
$$
ans_3=2\times[A_2^2+A_3^2+...+A_n^2\times(m-n+1)+...+A_3^2+A_2^2]
$$

如何化简？将此式展开
$$
ans_3=[1\times2+2\times3+...+(n-1)\times n]\times4+2n(n-1)(m-n)
$$

前半部分就像小学奥数中的通项求和问题了


$ans_3=\sum_{i=1}^{n-1}{i(i+1)}\times 4+2n(n-1)(m-n)$

$=\sum_{i=1}^{n-1}{i^2} \times 4+ \sum_{i=1}^{n-1} \times 4+2n(n-1)(m-n)$

由$\sum_{i=1}^ni^2=\frac{n(n+1)(2n+1)}{6}$得

$$
ans_3=[\frac{n(n-1)(2n-1)}{6}+\frac{n(n-1)}{2}]\times4+2n(n-1)(m-n)
$$
$$
=\frac {2n(n-1)(2n-1)}{3}+2n(n-1)(m-n)
$$

最后再把$ans_1$，$ans_2$，$ans_3$加起来即可

---

## 作者：Sternenlicht (赞：2)

思路：

因只有两个皇后，因此相互攻击的方式只有两个皇后在同一行、同一列或同一对角线 $3$ 种情况。又因这 $3$ 种情况没有交集，可以用加法原理。

同一行：放白皇后有 $nm$ 种方法，放黑皇后有 $m-1$ 种方法，用乘法原理将两个相乘，得到 $nm(m-1)$。

同一列：放白皇后有 $mn$ 种方法，放黑皇后有 $n-1$ 种方法，用乘法原理将两个相乘，得到 $mn(n-1)$。

同一对角线：设 $n \le m$，所有 “ / ” 方向的对角线，从左往右的长度依次为：

$$1,2,3,...,n-1,n,n,...,n,n-1,n-2,...,2,1$$

其中，$n$ 有 $m-n+1$ 个。

因为有两个方向的对角线，所以上面的结果还需 $\times 2$，得到：

$$2[2\sum\limits_{i=1}^{n-1}i(i-1)+(m-n+1)n(n-1)]$$

$\because \sum\limits_{i=1}^{n-1}i(i-1)=\sum\limits_{i=1}^{n-1}i^2-\sum\limits_{i=1}^{n-1}i=\frac{n(n-1)(2n-1)}{6}-\frac{n(n-1)}{2}=\frac{n(n-1)(2n-4)}{3}$

$\therefore 2[2\sum\limits_{i=1}^{n-1}i(i-1)+(m-n+1)n(n-1)] = \frac{2n(n-1)(3m-n-1)}{3}$

则最终结果为：
$$nm(m+n-2)+\frac{2n(n-1)(3m-n-1)}{3}$$

注意特判输入数据 $n>m$ 的情况，这种情况需要将 $m$ 和 $n$ 交换。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
using namespace std;

int main(){
	unsigned LL n,m;
	while (cin>>n>>m&&n&&m){
		if (n>m)swap(n,m);
		cout<<n*m*(m+n-2)+2*n*(n-1)*(3*m-n-1)/3<<endl;
	}
    return 0;
}
```

---

## 作者：AquaDemon (赞：2)

## 题意 
给定一个 $m × n$ 大小的棋盘，在上面放两个皇后，问使它们**互相攻击**的方案数量
## 思路
组合计数题。显然，对于一个皇后，可以攻击它同一行、列、斜线上的棋子。那我们分别讨论使两个皇后在同一行、列、斜线上互相攻击的方案数量。
### 1.同一行
在同一行的两个皇后，它们放置的方案是从 $n$ 列中任选两列进行放置。由于两个皇后颜色不同，所以方案数是 $A^2_n$ ，**而不是** $C^2_n$ 。
由于一共有 $m$ 行，根据**乘法原理**，同一行的总方案数为
$$
A^2_n  * m = \frac{n!}{(n-2)!} * m = n(n - 1) * m
$$
### 2.同一列
同理，可以得到在同一列的方案数量为
$$A^2_m  * n = \frac{m!}{(m-2)!} * m = m(m - 1) * n$$
### 3.同一斜线
有了前两步的分析 同一斜线上的情况就好分析了，
先假设某一条斜线长度为 $l$ ，根据前面的分析，皇后在这一条斜线上互相攻击的方案数就是
$$
A^2_l = \frac{l!}{(l-2)!}  = l(l - 1) 
$$
那么只需枚举所有斜线长度，答案加上对应的方案数就行了。画图寻找规律可以发现对于 $m × n$ 的棋盘，当 $m < n$ 时，它的所有斜线长度分别为
$$
1,2,3 \dots ,m - 1,\underbrace{m,m\dots,m}_{n - m + 1},m - 1,\dots1
$$

当 $m > n$ 时，只需要在计算前交换 $m,n$ 即可。

当然，对角线有两个方向，结果要乘以 $2$。

附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m = 1,n = 1;
int main(){
    while(m!=0&&n!=0){     
        ll ans = 0;
        scanf("%lld%lld",&m,&n);
        if(m > n)swap(m,n);//保证m < n
        ans += m * (m - 1) * n;
        ans += n * (n - 1) * m;//计算行与列方案数
       for(ll i = 1; i <= m - 1;i ++){
           ans += 2 * 2 * i * (i - 1);
       }//计算括号之外的所有斜线方案数 其中第一个2表示对角线两个方向 第二个2表示每个方向有两条这样长度的斜线
        for(ll i = 1;i <= n - m + 1;i ++){
            ans += 2 * m * (m - 1);
        }//计算括号内所有斜线方案数
        if(m != 0 && n != 0)printf("%lld\n",ans);
    }
    return 0;
}
```





---

## 作者：Paris_Commune (赞：1)

### 分析

使用加法，乘法原理。

同一列，行，对角线的方案互不影响，总体使用加法原理。


- 同一列的方案数使用乘法原理，为 $nm(n-1)$。

- 同一行的方案数使用乘法原理，为 $nm(n-1)$。

- 对角线的方案数 $\frac{2n(n-1)(3m-n-1)}{3}$。

总方案数为：$nm(n-1)+nm(n-1)+\frac{2n(n-1)(3m-n-1)}{3}$。

注意 `long long`。

### AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,m;
    while(cin>>n>>m&&n&&m){
        if(n>m){
        	swap(n,m);
		}
        cout<<n*m*(m-1)+m*n*(n-1)+2*n*(n-1)*(3*m-n-1)/3<<'\n';
    }
    return 0;
}
```

---

## 作者：ybc2025chenyuyang (赞：0)

# 题目大意
给你在棋盘上面放一黑一白两个皇后，求它们相互攻击的皇后的方案数（分别从一行，一列，一对角线进行攻击）。
# 思路
以上给出的三种情况是不重合的，因此我们可以想到用加法原理。

接下来我就要以小学生的听得懂的方式进行讲解了。

我们都知道，答案是同一行，同一列与同一个对角线安放皇后的方案数之和。接下来我们可以分步进行求解。

计算同一行的方案数我们可以用到加法原理：放白皇后有 $n\times m$ 种方法，放黑皇后有 $m-1$ 种方法，因此则共有 $n\times m\times \left(m-1\right)$ 种方法。

由于棋盘的行数和列数相等，所以我们可以得知：同一列的方案数也有 $n\times m\times\left(m-1\right)$ 种。

接着我们就是求在同一对角线上的方案数，这里有点难想。

如果 $n\leq m$，则所有 $k>0$ 的对角线从左到右的长度依此从 $1$ 到 $n-1$ 在经过 $m-n+1$ 个 $n$ 在重新回到 $1$。然后我们可以把它们累加起来，但是由于还有一条对角线我们没有考虑到，所以最后答案要乘 $2$。

所以我们可以整理一下通项公式，对角线的方案我用 $ans$ 表示。

$ans=2\times\left(2\times\sum_{i=1}^{n-1}i\times\left(i-1\right)+\left(m-n+1\right)\times n\times\left(n-1\right)\right)$。

这个等式中的 $\sum_{i=1}^{n-1}i\times\left(i-1\right)$ 可以分解成如下的简式。

$\sum_{i=1}^{n-1}i^{2}-\sum_{i=1}^{n-1}i=\frac{n\times(n-1)\times(2n-4)}{6}-\frac{n\times(n-1)}{2}=\frac{n\times(n-1)\times(2n-4)}{3}$。

因此，整个式子我们可以整理成：

$2\times(\frac{n\times(n-1)\times(2n-4)}{3}+(m-n+1)\times n\times(n-1))=\frac{2\times n\times (n-1)\times(3m-n-1)}{3}$。

接着明白了思路，代码就非常好写了。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
int main(){
    while(cin>>n>>m&&n&&m){
        if(n>m){
            swap(n,m);
        }//交换，避免对对角线的分类讨论
        cout<<n*m*(m+n-2)+2*n*(n-1)*(3*m-n-1)/3<<"\n";
    }
    return 0;
}
```


---

## 作者：hyjdouSHEN (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/UVA11538)

## 题目分析

因为只有两个皇后，因此互相攻击的方式只有两个皇后在同一行，同一列，同一对角线 $3$ 种情况。这 $3$ 种情况是没有交集的，因此可以使用加法原理。将三种分类的方案树汇总，就是我们想要的答案。

同一行，同一列的计算可以用乘法原理，例如它们在同一行时：放白后有 $n \times m$ 种放法，放黑后有 $m-1$种放法，相乘就是 $n \times m \times (m-1)$。同理当它们在同一列时，方案数也为 $n \times m \times (n-1)$。

求对角线有一点麻烦，不妨设 $m$ 大于等于 $n$，所有往左的对角线，从左往右的长度依次为 $1,2,3,\cdots,n-1,n,n,\cdots,n,n,n-1,n-2,\cdots,2,1$，其中有 $m-n+1$ 个 $n$。考虑到还有向右的对角线，所以整个结果还有乘以 $2$。

经过小小的整理后，我们可以得知对角线个数 $D(n,m)=2n(n-1)(3m-n-1)/3$，
完美的结束了！

代码如下。

## 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	unsigned long long n,m;
	while(cin>>n>>m){
		if(!n&&!m) break;
		if(n>m) swap(n,m);
		cout<<n*m*(m+n-2)+2*n*(n-1)*(3*m-n-1)/3<<endl;
	}
	return 0;
}
```

希望这篇题解对你有帮助~

[AC记录](https://www.luogu.com.cn/record/120153294)

---

## 作者：XLoffy (赞：0)

# UVA11538 Chess Queen
[题目传送门](https://www.luogu.com.cn/problem/UVA11538) | [更好的阅读体验](https://www.luogu.com.cn/blog/cxy-xlf-1003/solution-uva11538)

挺有意思的一个题目。

## 题目大意
给定一个棋盘，在棋盘上放两个皇后（一白一黑），求使得两个皇后相互攻击（在一行、一列或对角线）的方案数。

## 分析
我们首先可以想到的是一个皇后在一个任意的位置，另一个皇后可以放的在同一行或在同一列的方案数有 

$$m-1+n-1$$

棋盘上一共有 $m \times n$ 个格子，所以可放在同行或同列相互攻击的方案是 `ans=(m-1+n-1)*m*n`;

同行同列的方案数已经算好了，现在我们计算对角线上的方案数。因为左斜线上和右斜线上的方案是一样多的，所以我们只要求出左斜线即可知道右斜线的方案数。

首先我们要考虑到的是：斜线的最大值，是 $\min(m,n)$。那我们就把 `x=max(m,n)` 看作行，`y=min(m,n)` 看作列，所以我们的 $2$ 至 $y-1$ 行每行的格子数就是行号数，大于等于 $y$ 的行号数都只有 $y$ 个格子，所以等于 $y$ 个格子的左斜线有 
$$y-x+1$$
每一条上可以任选两个点放置皇后，即
```C++
for(long long i=2;i<m;i++) cnt+=(long long)i*(i-1)*2;
cnt+=(long long)(n-m+1)*m*(m-1));
```
即总方案数：$ans+2 \times cnt$。

## AC Code
```C++
#include <bits/stdc++.h>
using namespace std;
#define LL long long

int main()
{
    LL m,n;
    while(scanf("%lld%lld",&m,&n)==2&&(m+n))
    {
        if(m>n) swap(m,n);  // 确保m小于等于n，便于后续计算
        LL ans=0,cnt=0;
        ans+=n*m*(n-1+m-1); // 计算第一部分的结果
        for(LL i=2;i<m;i++)    cnt+=(LL)i*(i-1)*2; // 计算第二部分的结果
        cnt+=(LL)(n-m+1)*m*(m-1); // 计算第三部分的结果
        ans+=cnt*2; // 计算总结果
        printf("%lld\n",ans);
    }
    return 0;
}


```

---

## 作者：xiezheyuan (赞：0)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/uva11538.html)

## 简要题意

给你一个 $n\times m$ 的棋盘，你需要在棋盘上放置两个颜色不同的皇后，使得它们互相攻击。求方案数。

$1 \leq n,m \leq 10^6$

## 思路

下面假设 $n\leq m$。

首先发现，两个互相攻击的皇后大致有下面三种情况：

- 在同一行，方案数为 $\binom{n}{1}\operatorname{A}^{2}_{m}=nm(m-1)$。
- 在同一列，方案数为 $\binom{m}{1}\operatorname{A}^{2}_{n}=nm(n-1)$。
- 在同一个斜线上，这个比较复杂：

设所在的斜线的长度为 $S$，则方案数为 $2A^{2}_{S}=2S(S-1)$（因为斜线方向有两种）。

斜线长度一共有：

$$
1,2,\cdots,n-2,n-1,\underbrace{n,n,\cdots,n,n}_{m-n+1},n-1,n-2,\cdots,2,1
$$

所以同一个斜线的方案数就是：

$$
\begin{aligned}
&2(n(n-1)(m-n+1)+2\sum_{i=1}^{n-1}{i(i-1)})\\
&=2(n(n-1)(m-n+1)+2(\sum_{i=1}^{n-1}i^2-\sum_{i=1}^{n-1}i))\\
&=2(n(n-1)(m-n+1)+2(\frac{n(n-1)(2n-1)}{6}-\frac{n(n-1)}{2}))\\
&=2(n(n-1)(m-n+1)+2(\frac{n(n-1)(2n-4)}{6}))\\
&=2(n(n-1)(m-n+1)+\frac{n(n-1)(2n-4)}{3})\\
&=2\cdot\frac{3n(n-1)(m-n+1)+n(n-1)(2n-4)}{3}\\
&=2\cdot\frac{n(n-1)(3m-3n+3+2n-4)}{3}\\
&=\frac{2n(n-1)(3m-n-1)}{3}
\end{aligned}
$$

于是这道题就做完了。最后答案是：

$$
nm(m-1)+nm(n-1)+\frac{2n(n-1)(3m-n-1)}{3}
$$

单次计算时间复杂度 $O(1)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,m;

signed main(){
    while(cin>>n>>m&&n&&m){
        if(n>m) swap(n,m);
        int row=n*m*(m-1);
        int col=m*n*(n-1);
        int xie=2*n*(n-1)*(3*m-n-1);
        xie/=3;
        cout<<(row+col+xie)<<'\n';
    }
    return 0;
}
```


---

## 作者：Rainbow_Sky (赞：0)

## 思路与分析

我们对于一个棋盘上两个皇后的处理，往往可以分为 $3$ 类：行、列、对角线。

1. 同一行。在同一行中的情况其实很好分析，白皇后可以放在任何位置，而另一皇后则可以在这一行上的任意其他位置，从而我们可以得出方案数：$S_1=mn(m-1)$ 种。

1. 同一列。在同一列中的情况也不难，白皇后依旧可以放在任何位置，而另一皇后则可以在这一列上的任意其他位置，从而我们可以得出方案数：$S_2=mn(n-1)$ 种。

1. 同一对角线。这时候情况就比较麻烦了，我们需要对斜边长度进行一下枚举：

   $$1,2,3,4...n-1,\underbrace{n,n,n...n}_{m-n+1}
   ,n-1,n-2...3,2,1$$
   因而，我们可以得出：
   $$\begin{aligned} S_3 &= 2\times [2\sum_{i=1}^{n-1}(i-1)i+n(n-1)(m-n+1)]\\&=2\times [2(\sum_{i=1}^{n-1}i^2-\sum_{i=1}^{n-1}i+n(n-1)(m-n+1)]\\&=2\times [2(\frac{n(n-1)(2n-1)}{6}-\frac{n(n-1)}{2})+n(n-1)(m-n+1)]\\&=2\times [2(\frac{n(n-1)(2n-4)}{3}+n(n-1)(m-n+1)]\\ &=\frac{2n(n-1)(3m-n-1)}{3} \end{aligned}$$
   
综上，总方案数为：
$$ S=mn(n+m-2)+\frac{2n(n-1)(3m-n-1)}{3}$$

## AC code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	unsigned ll n,m;
	while (cin>>n>>m&&n&&m){
		 if(n>m)swap(n,m);
		 cout<<n*m*(m+n-2)+2*n*(n-1)*(3*m-n-1)/3<<endl;
	}
    return 0;
}
```

---

