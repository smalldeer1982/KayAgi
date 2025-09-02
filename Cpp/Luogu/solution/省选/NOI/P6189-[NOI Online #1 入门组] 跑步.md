# [NOI Online #1 入门组] 跑步

## 题目描述

小 H 是一个热爱运动的孩子，某天他想给自己制定一个跑步计划。小 H 计划跑 $n$ 米，其中第 $i(i \geq 1)$ 分钟要跑 $x_i$ 米（$x_i$ 是正整数），但没有确定好总时长。

由于随着跑步时间增加，小 H 会越来越累，所以小 H 的计划必须满足对于任意 $i(i >1)$ 都满足 $x_i \leq x_{i-1}$。

现在小 H 想知道一共有多少个不同的满足条件的计划，请你帮助他。两个计划不同当且仅当跑步的总时长不同，或者存在一个 $i$，使得两个计划中 $x_i$ 不相同。

由于最后的答案可能很大，你只需要求出答案对 $p$ 取模的结果。 

## 说明/提示

#### 样例输入输出 1 解释

五个不同的计划分别是：$\{1,1,1,1\}$，$\{2,1,1\}$，$\{3,1\}$，$\{2,2\}$，$\{4\}$。 

---

#### 数据规模与约定

本题共 $10$ 个测试点，各测试点信息如下表。

| 测试点编号 | $n \leq$ | 测试点编号 | $n \leq$ |
| :----------: | :---------: | :----------: | :---------: |
| $1$ | $5$ | $6$ | $2\times 10^3$ |
| $2$ | $10$ | $7$ | $5\times 10^3$ |
| $3$ | $50$ | $8$ | $2\times 10^4$ |
| $4$ | $100$ | $9$ | $5\times 10^4$ |
| $5$ | $500$ | $10$ | $10^5$|

对于全部的测试点，保证 $1 \leq n \leq 10^5$，$1 \leq p < 2^{30}$。

## 样例 #1

### 输入

```
4 44
```

### 输出

```
5```

## 样例 #2

### 输入

```
66 666666
```

### 输出

```
323522```

## 样例 #3

### 输入

```
66666 66666666
```

### 输出

```
45183149
```

# 题解

## 作者：OMG_wc (赞：161)

本题就是正整数拆分问题，很容易想到一种 $O(n^2)$ 的 DP：

记 $f_{i,j}$ 表示用了前 $i$ 个数和为 $j$ 的方案数，那么 $f_{i,j}=f_{i-1,j}+f_{i,j-i}$，初始时 $f_{0,0}=1$ 。

这其实就是完全背包，但只能拿 $70$ 分（~~也可能乱搞到 $80$ 分~~）。

那么怎么办呢？我们采用分块的思路，令 $m=\sqrt n $，对于 $i<m$ 的数采用以上完全背包来求，这部分时间复杂度为 $O(n\sqrt n)$ 。

而对于大于等于 $m$ 的数，采用另外一种 DP：

记 $g_{i,j}$ 表示用了 $i$ 个大于等于 $m$ 的数和为 $j$ 的方案数，那么 $g_{i,j}=g_{i-1,j-m}+g_{i,j-i}$，初始时 $g_{0,0}=1$ 。

- 转移方程的第一项 $g_{i-1,j-m}$ 表示在拆分序列中增加一个数 $m$ 。
- 转移方程的第二项 $g_{i,j-i}$ 表示把当前拆分序列的每个数都加上 $1$。

$i$ 最大为 $\sqrt m$，因而这一步时间复杂度为 $O(n\sqrt n)$ 。

如果觉得不好理解，可以随便举个例子：

假设当前 $m=1$，你要拆的数是 $11$，其中一种方案是 $11=5+2+2
+2$。初始拆分序列为空，现在有两种操作：操作 $1$ 是在拆分序列中增加一个数 $1$，操作 $2$ 是把当前序列中每个数都增加 $1$ 。那么该方案对应的操作序列为：$12221112$。

容易发现，一种拆分方案和一种操作序列是一一对应的，因此这样 DP 不会重复也不会遗漏。

最后一步，就是把分块的两部分结合一下。枚举第一个部分的总和为 $j$，那第二个部分的总和就为 $n-j$，把两者的方案数乘起来记入答案中，即为 $\sum\limits_{j=0}^n (f_{m-1,j}\times \sum\limits_{i=0}^{m} g_{i,n-j})$。

那么本题总时间复杂度为 $O(n\sqrt n)$ ，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100005;

int f[N];
int g[400][N];
int main() {
    int n, p;
    cin >> n >> p;
    int m = sqrt(n) + 1;
    f[0] = 1;
    for (int i = 1; i < m; i++) {
        for (int j = i; j <= n; j++) {
            f[j] += f[j - i];
            f[j] %= p;
        }
    }
    g[0][0] = 1;
    for (int i = 1; i < m; i++) {
        for (int j = i; j <= n; j++) {
            g[i][j] = g[i][j - i];
            if (j >= m) g[i][j] += g[i - 1][j - m];
            g[i][j] %= p;
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        LL sum = 0;
        for (int j = 0; j < m; j++) sum += g[j][n - i];
        sum %= p;
        ans = (ans + f[i] * sum) % p;
    }
    cout << ans << endl;
    return 0;
}
```



---

## 作者：memset0 (赞：141)

这题相当于我们求任意模数的拆分数，可以使用五边形数定理。


五边形数定理用来描述欧拉函数展开式的特性：

$$\varphi(x) = \prod_{n=1}^\infty (1 - x^n) = \sum_{k=-\infty}^{\infty} (-1)^k x^{\frac {k(3k+1)} 2} = \sum_{k=0}^{\infty} (-1)^k x^{\frac {k(3k \pm 1)} 2}$$

欧拉函数的倒数是划分数的生成函数：

$$\frac 1 {\varphi(x)} = \sum_{i=0}^\infty p(i) x^i = \prod_{i=0}^\infty \sum_{j=0}^\infty x^{ij} = \prod_{i=0}^\infty \frac 1 {1 - x^i}$$


由定义我们可以得到：

$$\varphi(x) \times \frac 1 {\varphi(x)} = 1 \Leftrightarrow \left( \sum_{k=0}^{\infty} (-1)^k x^{\frac {k(3k \pm 1)} 2} \right) \left( \sum_{i=0}^\infty p(i) x^i \right) = 1$$

通过这个我们可以得到划分数的递推式。

同时发现五边形数生成函数的项数是 $O(\sqrt n)$ 级别的，故我们可以在 $O(n \sqrt n)$ 的时间复杂度内求出划分数前 $n$ 项。

当然此题中我们只需输出第 $n$ 项即可。

感兴趣的读者也可以思考下如果此题规定 $a_i$ 小于一给定常数 $k$ 应该如何处理。[sol](https://memset0.cn/wu-bian-xing-shu-ding-li)。

代码

```cpp
#include<bits/stdc++.h>
int T,n,m,mod,f[100010],g[100010];
int main(){
    f[0]=1,scanf("%d%d",&n,&mod);
    for(int i=1;i*(3*i-1)/2<=n;i++)g[m++]=i*(3*i-1)/2,g[m++]=i*(3*i+1)/2;
    for(int i=1;i<=n;i++)for(int j=0;j<m&&g[j]<=i;j++)f[i]=(f[i]+(((j>>1)&1)?-1ll:1ll)*f[i-g[j]])%mod;
    printf("%d\n",(f[n]+mod)%mod);
}
```

---

## 作者：StudyingFather (赞：76)

这次 NOI Online 入门组考了一道裸的整数拆分问题。

SF 实在太菜，只会暴力，不会这题的正解。

这个菜鸡决定查些资料，好好研究一下整数拆分问题背后的那些事情。

**Warning：阅读本文需要一些生成函数与形式幂级数的相关知识，如果您还不了解的话，推荐先阅读 [铃悬的数学小讲堂——生成函数初步](https://lx-2003.blog.luogu.org/generating-function)。**

**Note：如果题解界面公式炸了，更好的阅读体验点 [这里](https://studyingfather.com/archives/3000)。**

## 1 五边形数

**五边形数**（Pentagonal number）$p_n$ 大概长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/pw2infer.png)

简单来说，大概就是一个边长 $n$（指边上有 $n$ 个点）的五边形，里面套一个边长 $n-1$ 的五边形，以此类推。

从图中很容易看出递推式：$p_n=p_{n-1}+3n-2$，边界是 $p_1=1$（其实 $n=1$ 时上述递推式仍然成立，不过考虑它的几何意义还是将 $n=1$ 当作边界）。

根据这个递推式，很容易得出它的通项式：

$$
\begin{aligned}
p_n &= p_{n-1}+3n-2\\ 
 &= p_{n-2}+3(n-1)-2+3n-2\\ 
 &= \ldots\\ 
 &= \sum_{i=1}^{n} 3i-2\\
 &= \frac{3n^2-n}{2}
\end{aligned}
$$

五边形数在 OEIS 上的编号是 [A000326](https://oeis.org/A000326)。

五边形数的性质很多，这里简单列出几条：

1. 任何正整数都可以表示为不超过 $5$ 个五边形数的和（详见 [费马多边形数定理](https://zh.wikipedia.org/wiki/%E8%B4%B9%E9%A9%AC%E5%A4%9A%E8%BE%B9%E5%BD%A2%E6%95%B0%E5%AE%9A%E7%90%86)）。事实上绝大多数正整数都可以拆分为 $3$ 个五边形数的和。
2. 前 $n$ 个五边形数的平均数是第 $n$ 个三角形数。

## 2 广义五边形数

上面的式子中 $n$ 的取值是正整数，如果将 $n$ 的取值范围扩大到全体整数，会不会仍然具有一些优雅的性质呢？

于是我们按照 $n=0,1,-1,2,-2,3,-3,4,-4,\ldots$ 的顺序代入上面的通项式，得到下面的数列：

$$
0, 1, 2, 5, 7, 12, 15, 22, 26,\ldots
$$

这个数列是在原来五边形数的基础上扩充范围得到的，于是我们称其为**广义五边形数**。它在 OEIS 上的编号为 [A001318](http://oeis.org/A001318)。

为了方便，广义五边形数仍然用 $p_n$ 表示。

广义五边形数和下面要讲到的整数拆分问题有很大联系，我们在下文将会深入探究。

## 3 五边形数定理

介绍一个新函数：欧拉函数。

（注意：这里的欧拉函数 $\phi(x)$ 不是数论里的那个欧拉函数 $\varphi(x)$）

$$
\phi(x)=\prod_{k=1}^{\infty}(1-x^k)
$$

将这个式子展开（这个展开首先由欧拉完成）：

$$
\prod_{k=1}^{\infty}(1-x^k)=\sum_{k=-\infty}^{\infty}(-1)^k x^{\frac{3k^2-k}{2}}
$$

注意 $x$ 的次数，正是我们前面提到的**广义五边形数**。五边形数定理由此得名。

将得到的所有项按升幂排列，得到：

$$
\phi(x)=1-x-x^2+x^5+x^7-x^{12}-x^{15}+\ldots
$$

这个展开式的证明太神仙了，笔者并不会，感兴趣的可以看 [visit_world 大爷的博客](https://blog.csdn.net/visit_world/article/details/52734860)。

得到这个式子有什么用呢？它和我们接下来要提到的整数拆分问题有很大关系。

## 4 整数拆分问题

接下来进入重头戏。

我们来回顾一下刚刚结束的 NOI Online 里考到的 [这道题](https://www.luogu.com.cn/problem/P6189)：

> 求将正整数 $n$ 拆分为若干个正整数的和（允许同一个数使用多次，这里的拆分是无序的，即 $1+2$ 和 $2+1$ 等价）的方案数。

本题有很多做法，时间效率不尽相同。下面介绍一种运用生成函数的方法。

下面设 $p(x)$ 为拆分 $x$ 的方案数（$p(x)$ 在 OEIS 上的编号为 [A000041](https://oeis.org/A000041)）。

考虑 $p(x)$ 的生成函数，

$$
\sum_{k=0}^{\infty}p(k)x^k=\prod_{k=1}^{\infty}\frac{1}{1-x^k}=\frac{1}{\phi(x)}
$$

用五边形数定理展开一下，整理下式子：

$$
\begin{aligned}
\phi(x)\sum_{k=0}^{\infty}p(k)x^k &= (1-x-x^2+x^5+x^7-\ldots)(1+p(1)x+p(2)x^2+p(3)x^3+\ldots)\\ 
 &= 1
\end{aligned}
$$

现在我们想要求出 $p(k)$，或者说，算出 $x^k$ 前面的系数。

将整个式子展开，得到（展开过程这里略去，感兴趣的读者这里可以自己尝试）：

$$
p(k)-p(k-1)-p(k-2)+p(k-5)+p(k-7)-\ldots=0
$$

（PS：有的人可能对这个过程有点疑惑，这里稍微讲一下。上面的等式成立，意味着 $x^k$ 的系数（别忘了这里是形式幂级数）在左右两边是相等的。这个等式的左边是上面的式子展开后 $x^k$ 的系数，右边因为只有常数，所以 $x^k$ 的系数为零）

广义五边形数再一次出现在我们的式子里了。

根据上面这个式子，我们就可以递推计算 $p(x)$ 的值了。

因为广义五边形数是 $O(n^2)$ 的级别（不知道的，请翻到最上面看通项式），因此递推式共有 $O(\sqrt n)$ 项，这样计算的时间复杂度便是 $O(n \sqrt n)$。

嗯，代码实现挺短的：

```cpp
#include <iostream>
using namespace std;
long long f[100005];
int a(int x)
{
 return (3*x*x-x)/2;
}
int main()
{
 int n,p;
 cin>>n>>p;
 f[0]=1;
 for(int i=1;i<=n;i++)
  for(int j=1;;j++)
  {
   int x=a(j),y=a(-j);
   if(x<=i)
    f[i]=((f[i]+(j&1?1:-1)*f[i-x])%p+p)%p;
   if(y<=i)
    f[i]=((f[i]+(j&1?1:-1)*f[i-y])%p+p)%p;
   if(x>i||y>i)break;
  }
 cout<<f[n]<<endl;
 return 0;
}
```

## Reference

- [五角数 - 维基百科](https://zh.wikipedia.org/wiki/%E4%BA%94%E8%A7%92%E6%95%B0)
- [五边形数定理 - 维基百科](https://zh.wikipedia.org/wiki/%E4%BA%94%E9%82%8A%E5%BD%A2%E6%95%B8%E5%AE%9A%E7%90%86)
- [整数分拆 - 维基百科](https://zh.wikipedia.org/wiki/%E6%95%B4%E6%95%B8%E5%88%86%E6%8B%86)
- [五边形数定理的一种证明_visit_world的博客](https://blog.csdn.net/visit_world/article/details/52734860)

---

## 作者：皎月半洒花 (赞：51)

其实就是分拆数问题。分拆数问题本质上是 $n$ 也无标号的第二类斯特林数问题（第二类斯特林数是 $n$ 有标号但是 $k$ 无标号）。

那么对于这个问题，考虑两种 $dp$.

* 1、令 $f_{i,j}$ 表示对于 $i$ 拆分成若干个不大于 $j$ 的数的方案数。则有转移：

$$f_{i,j}=f_{i,j-1}+f_{i-j,j}$$

后面一项 $f_{i-j,j}$ 可以看成一个背包一样，后面的状态对前面的状态有天然的累加效应，所以只需要考虑丢掉一个 $j$ 的情况；而前面一项则把我们转移从后一项的**等于** $j$ 升级成为**不大于** $j$ 。

* 2、令 $g_{i,j}$ 表示对于 $i$ 拆分成 $j$ 个数的方案数。则有转移：

$$g_{i,j}=g_{i-1,j-1}+g_{i-j,j}$$

前面一项表示新拆出一个 $1$ 来，还是背包的那种“累加”思想，所以只需要考虑拆出一个 $1$ 的情况；后面一项则表示不拆，而是把拆出的数全体都 $+1$，即本来的 $5=3+1+1$ 转移到 $8=4+2+2$ 。注意此处不会存在“部分拆出来的数加了但是剩下的没加”或者“加的不一样”，因为这两个状态都是可以归约到 $i$ 较小的 $g$ 上去所以不需要额外转移。

ps：似乎某硬币xx的容斥题就用到了这个思想来着。。。实际上就是个背包吧qaq

但是上述做法是 $n^2$ 的。总结两个 $dp$ 的优劣，发现如果采用根号分治的策略，对于 $f$ 只转移 $< \sqrt n$ 的，对于 $g$ 只转移 $\geq \sqrt n$ 的，那么两者均只需要 $n\sqrt n$ 的时空代价（因为大于 $\sqrt n$ 的数不会用超过 $\sqrt n$ 个）。

具体的，考虑对先用 $f$ 求出来 $j< \sqrt n$ 的方案数，再魔改一下 $g$，让 $g$ 只转移那些 $\geq \sqrt n$ 的数字：就是第一维把 $\sqrt n$ 当作步长转移即可。

之后考虑如何合并答案。发现 $f,g$ 对于同一个 $n$，计数的部分互斥且互补，那么就可以直接乘法原理解决。合并是个卷积状物，但由于本题只需要求第 $n$ 项，所以直接算即可。

```cpp
const int B = 403 ;
const int N = 200010 ;

int S ;
int ans ;
int n, p ;
int f[N][B] ;
int g[N][B] ;
int X[N], Y[N] ;

int main(){
    cin >> n >> p ;
    S = n / B + 1 ; X[0] = 1 ;
    for (int i = 0 ; i < B ; ++ i) f[0][i] = 1 ;
    for (int j = 1 ; j < B ; ++ j)
        for (int i = 1 ; i <= n ; ++ i){
            if (i < j) f[i][j] = f[i][j - 1] ;
            f[i][j] = (f[i - j][j] + f[i][j - 1]) % p ;
            X[i] = f[i][j] ; //cout << i << " " << X[i] << endl ;
        }
    g[B][1] = 1 ; Y[0] = 1 ;
    for (int i = 0 ; i <= n ; ++ i)
        for (int j = 1 ; j <= S && j <= i ; ++ j){
            if (i >= B) (g[i][j] += g[i - B][j - 1]) %= p ;
            if (i >= j) (g[i][j] += g[i - j][j]) %= p ;
        }
    for (int i = 0 ; i <= n ; ++ i)
        for (int j = 1 ; j <= S ; ++ j)
            (Y[i] += g[i][j]) %= p ;
    for (int i = 0 ; i <= n ; ++ i)
        (ans += 1ll * X[i] * Y[n - i] % p) %= p ;
    cout << ans << endl ; return 0 ;
}


```

---

## 作者：X_Chara (赞：35)

# P6189 [NOI Online 入门组]跑步（民间数据）


思路：
> 这题其实就是一个背包的模板，但是他也有一个难点：他的数据太大了……

| **测试点编号** | $n \leq$ | **测试点编号** | $n \leq$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $6$ | $2000$ |
| $2$ | $10$ | $7$ | $5000$ |
| $3$ | $50$ | $8$ | $20000$ |
| $4$ | $100$ | $9$ | $50000$ |
| $5$ | $500$ | $10$ | $100000$ |

> 我们的背包DP在测试点8的时候还能应付，但是到了测试点9和测试点10的时候就会超时
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005
int f[MAXN];
int main()
{
    int n, p;
    cin >> n >> p;
    f[0] = 1;
    for(register int i = 1; i <= n; i++)
        for(register int j = i; j <= n; j++)
            f[j] = (f[j - i] + f[j]) % p;
    cout << f[n] << endl;
    return 0;
}
// 据说不贴代码就不会得赞qwq，所以动动手指点歌赞吧♪(^∇^*)
```
![image.png](https://i.loli.net/2020/03/12/EiY7J4lOe35Xk6b.png)


* * *

> 然后我们就 ~~没办法了，等S吧~~还有一个办法，他就是……

## 整数的无序分拆！

~~整♪数♪的♪无♪序♪分♪拆，我♪的♪救♪星♪~~

首先我们先定义状态：

设$f(n,k)$为$n$拆成$k$个正整数部分有$f(n,k)$种方案（$k$由小到大排列）

$f(n,k)$根据最后一部分是否大于1，分成两种情况

$f(n,k)=\begin{cases}f(n-1,k-1) \quad  \quad A_k = 1 \\f(n - k, k) \quad \quad \quad A_k > 1\end{cases}$

$∴f(n,k)=f(n-1,k-1)+f(n-k,k)$

> 我们接着将我们敬爱的小H的跑步的速度x分为两类来做

1. $x \leq \sqrt n$ 时
	
   $f[n]=f[n-x]$
   那么我们$O(n\sqrt n)$
   
2. $x > \sqrt n$ 时

	$g(n,k) = g(n-1,k-1)+g(n-k,k) \quad k \leq \sqrt n$
   
   那么我们的时间复杂度又是$O(n\sqrt n)$我们就不会超时啦啦♪(^∇^*)
   
最终的递推式是这样的：
$\sum_{i=1}^{i<=n}(f[i] * \sum_{k=1}^{k< \sqrt n} g(n-i,k))$

* * *
思路到此结束，代码~~写不来~~如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100005
int n,p,ans;
int f[MAXN];
int g[MAXN][330];
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>p;
    f[0]=1;
    int m=sqrt(n)+1;
    for(register int i=1;i<=m;i++)
    {
        for(register int j=i;j<=n;j++)
        {
           f[j]=(f[j-i]+f[j])%p;
        }
    }
    m++;
    g[0][0]=1;
    for(register int i=m;i<=n;i++)
    {
        g[i][1]=1;
        for(register int j=2;j<=m;j++)
        {
            g[i][j]=(g[i-j][j]+g[i-m][j-1])%p;
        }
    }
    for(register int i=0;i<=n;i++)
    	for(register int j=0;j<=m;j++)
    		ans=(ans+1ll*f[i]*g[n-i][j])%p;
    cout<<ans<<endl;
    return 0;
}
```


[亲测AC~~~](https://www.luogu.com.cn/record/31668970)


### 望通过QAQ







---

## 作者：　　　吾皇 (赞：17)

由于数据范围达到 $n \le 10^5$，显然不能做普通的 $O(n^2)$ DP。显然正解是一个复杂度 $O(n)$ 多一点的递推。

因此猜测答案具有规律，我们可以用 [数的划分](https://www.luogu.com.cn/problem/P1025) 中的程序稍作修改得到小数据的答案值。前 $15$ 个为 $1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101, 135$。肉眼看不出什么规律，考虑将其复制入一个				[神奇的网站](http://oeis.org)。

发现这是编号为 $A000041$ 的数列，我们找到 $\text{FORMULA}$ 这一项，

![](https://cdn.luogu.com.cn/upload/image_hosting/bkbtky0t.png)

发现里面大多数公式都是取近似值的，显然不能用。发现有一个 $a_(n)=a(n-1)-a(n-2)+a(n-5)+a(n-7)-a(n-12)-a(n-15)+\cdots =0$ 通过移项可以求出 $a(n)$ 的值。

那么这一串数 $1,2,5,7,12,15$ 又是什么呢，我们在百度上查一下，发现这是一个广义五边形数，它的计算是
![](https://bkimg.cdn.bcebos.com/pic/d833c895d143ad4b5b4f245389025aafa40f063b)

其中 $n$ 依序为 $0, 1, -1, 2, -2, 3, -3, 4 \cdots$。

那么第 $2i$ 项广义五边形数为 $\frac{i \times (i \times 3-1)}{2}$，第 $2i+1$ 项广义五边形数为 $\frac{i \times (i \times 3+1)}{2}$。

我们能得到一个这样的代码
```
for(int i=0;i<=n/2;i++){
		b[2*i]=i*(i*3-1)/2;
		b[2*i+1]=i*(i*3+1)/2;
	}
```

那么再代入上面那个公式 $a(n)=a(n-1)+a(n-2)-a(n-5)-a(n-7)+a(n-12)+a(n-15)-\cdots$

就能得到这样一个代码

```
for(int i=3;i<=n;i++){
		k=0;//从0开始也可以
		for(int j=2;b[j]<=i;j++){//因为在我们广义五边形数的求法中，可以看出实际是从2开始的，所以j从2开始循环，如果b[j]大于i那么数组越界，停止循环
			flag=k&2;//2的二进制为10 所以如果k%4的余数为0或1，flag就为0，就要+，否则则减
			if(!flag) a[i]=(a[i]+a[i-b[j]]+p)%p;
			else a[i]=(a[i]-a[i-b[j]]+p)%p;//按照上面得到的公式进行推
			k++;//推过一次k加一
		}
	}
```
核心思路和代码就在上面，总代码就不给了。

---

## 作者：Kevin5308 (赞：17)

话说现在连$pj$都考这么变态的数学题了吗……
#### 回归正题
看到这道题目，相信大家就一定想到了一个初赛中经常遇到的模型：

有 $ n $ 个完全相同的盒子和 $ n $个完全相同的小球，允许盒子为空，求有多少种不同的放法？

其实这道题本质上和上面的问题是完全相同的。

初赛的时候数据小手推就可以了，但是现在$1≤n≤10 
^5$
 ，$1 \leq p < 2^{30}$，显然~~dabiao~~是不现实的。
 
 那么应该如何解呢？
 
###  大家要注意的是！这是一场Online测试。
### 所以，我们要充分地利用网络。
我们可以先尝试着推前几个.

$n=1,ans=1$//(1)

$n=2,ans=2$//(2,0),(1,1)

$n=3,ans=3$//(3,0,0),(2,1,0),(1,1,1)

$n=4,ans=5$//(4,0,0,0),(3,1,0,0)(2,2,0,0)(2,1,1,0)(1,1,1,1)

$n=5,ans=7$//太长了，请dalao们自己去推算吧

~~众所周知，~~，有一个非常神奇的网站叫做[OEIS](http://oeis.org/)。

将我们刚才找到的规律1,2,3,5,7输入，很快得到一个数列[A000041](http://oeis.org/search?q=1%2C2%2C3%2C5%2C7&sort=&language=english&go=Search)。

阿嘞！全是英文，想我这种初二的蒟蒻如何看得懂？

但是，当你仔细地观察后，就会发现长长的解释中有一段名为PROG的版块，其中有一个~~在本蒟蒻眼里~~看着是伪代码的东西。
```cpp
def A000041(n):
    if n == 0: return 1
    S = 0; J = n-1; k = 2
    while 0 <= J:
        T = A000041(J)
        S = S+T if is_odd(k//2) else S-T
        J -= k if is_odd(k) else k//2
        k += 1
    return S
```
接下来的工作就相当容易了。我们把代码翻译成c++，然后把取模啊，记忆化搜索等等全部加上去就可以了。
## $Code$
```cpp
ll sol(int x){
	if (x==0) return 1;
	if (dp[x]>0) return dp[x];//记忆化
	ll s=0,j=x-1,k=2;
	while(0<=j){
		ll t=sol(j);
		if ((k/2)&1) s=(s+t)%p;
		else s=(s-t+p)%p;
		if (k&1) j-=k;
		else j-=(k/2);
		k++;
	}
	dp[x]=s;//记忆化
	return s;//也没有什么好解释了，纯翻译……
}
```


### 然而！

我却惊奇的发现第三个样例竟然过不了……

万分无奈的，本蒟蒻有将上面的代码修改成了dp。

## $AC$ $Code$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n,p,dp[100010];

int main()
{
	scanf("%lld%lld",&n,&p);
	dp[0]=1;
	for(int i=1;i<=n;i++){
		ll j=i-1,k=2;
		while(0<=j){
			if ((k/2)&1) dp[i]=(dp[i]+dp[j])%p;
			else dp[i]=(dp[i]-dp[j]+p)%p;
			if (k&1) j-=k;
			else j-=(k/2);
			k++;
		}//其实除了把x,s,t这些乱七八糟的换了一下，几乎没有什么区别…
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```

### 总结：
+ ~~要充分利用网络~~
+ 本题解纯粹供$pj$选手娱乐，请各位大佬们自行跳过！
+ 来自蒟蒻的忠告：希望大家在日常做题中不要过多利用此方法
~~（否则可能被kkk禁掉）~~……

最后，感谢~~xjd~~大佬提供的神奇思路

---

## 作者：Coffee_zzz (赞：2)

题意可以被转化为：求元素和为 $n$ 的可重集的数量。

我们来考虑两种做法。

做法一：

> 设 $f_{i,j}$ 表示当可重集内的元素都不大于 $i$ 且和为 $j$ 时可重集的数量，考虑当前可重集内是否有值为 $i$ 的元素即可得到转移方程：
> 
> $$
> f_{i,j}=f_{i-1,j}+f_{i,j-i}
> $$
> 
> 答案即为 $f_{n,n}$。

做法二：

> 考虑两种操作：
>
> - 向可重集中添加一个值为 $1$ 的元素；
> - 将可重集中所有元素的值都增加 $1$。
>
> 这两种操作实际上刻画了一种可重集的生成方式。我们可以利用这两种操作进行 dp 的转移。
>
> 设 $g_{i,j}$ 表示当可重集的大小为 $i$ 且元素和为 $j$ 时可重集的数量，考虑上一次操作进行了第一种操作还是第二种操作即可得到转移方程:
>
> $$
> g_{i,j}=g_{i-1,j-1}+g_{i,j-i}
> $$
>
> 答案即为 $\sum\limits_{k=0}^n g_{k,n}$。

这两种做法的时间复杂度均为 $\mathcal O(n^2)$，考虑优化。

设 $B=\left\lfloor\sqrt n\right\rfloor$，我们可以将可重集拆成两部分，第一部分只包含值小于 $B$ 的元素，第二部分只包含值大于等于 $B$ 的元素。

对于第一部分，我们可以直接使用做法一解决。由于可重集中的元素都不大于 $B$，所以这部分的时间复杂度为 $\mathcal O(nB)=\mathcal O(n\sqrt n)$。

对于第二部分，我们可以把做法二中的「向可重集中添加一个值为 $1$ 的元素」改为「向可重集中添加一个值为 $B$ 的元素」，并将转移方程修改为：

$$
g_{i,j}=g_{i-1,j-B}+g_{i,j-i}
$$

由于可重集中的元素都大于等于 $B$，所以可重集中最多有 $\left\lfloor\dfrac n B\right\rfloor$ 个元素，这部分的时间复杂度为 $\mathcal O\left(\dfrac {n^2} B\right)=\mathcal O(n\sqrt n)$。

最后，我们只需要枚举第一部分中元素的和 $c$，将答案加上 $f_{B-1,c}\times\sum\limits_{k=0}^{\lfloor\frac n B\rfloor}g_{k,n-c}$ 即可。

```c++
const int N=1e5+5,V=320;
int n,p,b,f[V][N],g[V][N],ans;
void add(int &a,int b){
	a+=b;
	if(a>=p) a-=p;
}
void solve(){
	cin>>n>>p;
	if(p==1) return cout<<0<<endl,void();
	if(n==1) return cout<<1<<endl,void();
	b=ceil(sqrt(n));
	f[0][0]=1;
	for(int i=1;i<b;i++){
		for(int j=0;j<=n;j++){
			f[i][j]=f[i-1][j];
			if(j>=i) add(f[i][j],f[i][j-i]);
		}
	}
	g[0][0]=1;
	for(int i=1;i<=n/b;i++){
		for(int j=b;j<=n;j++){
			g[i][j]=g[i-1][j-b];
			if(j>=i) add(g[i][j],g[i][j-i]);
		}
	}
	for(int c=0;c<=n;c++) for(int k=0;k<=n/b;k++) add(ans,1ll*f[b-1][c]*g[k][n-c]%p);
	cout<<ans<<endl;
}
```

---

## 作者：Union_Find (赞：1)

题意是要求模 $p$ 意义下 $n$ 的分拆数，即将 $n$ 分成若干个无序的数的和的方案数。

如果有 NTT 模数，我们就可以直接用分拆数的卷积做法 $O(n\log n)$ 来做。但是问题是这题没有 NTT 模数，所以 NTT 做法直接爆炸，我们要用**根号分治**。

令 $m = \sqrt{n}$。首先我们求只用不超过 $m$ 个数得到 $i$ 的方案数。

记 $f_{i,j}$ 表示用 $[1,i]$ 的数凑出 $j$ 的方案数，这就是简单的 dp，可以直接 $O(n\sqrt{n})$ 做。

$$f_{i,j} = f_{i,j-i}+f_{i-1,j}$$

注意到这些数只包括了 $[1,m)$ 的数，也就是超过 $m$ 的数都没用。

定义 $g_{i,j}$ 表示用 $i$ 个数凑出 $j$ 的方案数，但是这里要求用的数必须是大于 $m$ 的数。直接做就不好弄了，考虑要用到一个性质，就是用的数的个数不会超过 $m$ 个。

现在我们把问题变成将 $n$ 个球放入 $i$ 个盒子中，且每个盒子至少有 $m$ 个的方案数。这个问题可以用经典球盒模型的方法来做。如下。

定义 $g_{i,j}$ 表示用 $i$ 个不小于 $m$ 的数凑出 $j$ 的方案数。也就是，我们将 $j$ 个球放入 $i$ 个盒子中，且每个盒子至少有 $m$ 个球的方案数。

$$g_{i,j} = g_{i,j-i} + g_{i-1,j-m}$$

我们来解释一下。

- $g_{i,j-1}$ 表示把前面所有的盒子都再放入一个球，此时就是从 $j-i$ 变成了 $j$ 个球，盒子数不变。
- $g_{i-1,j-m}$ 表示新加入一个盒子，一开始就给他放了 $m$ 个球，那么就是从 $j-m$ 个球变成了 $j$ 个球，盒子数多 $1$。

因为 $i$ 的上界是 $m$，所以时间复杂度是 $O(n\sqrt{n})$。

现在考虑答案。一个分拆可以分成小于 $m$ 的部分和不小于 $m$ 的部分，于是就有

$$ans = \sum_{i=0}^n \sum_{j=0}^m f_{m-1,i}g_{j,n-i}$$

其中 $i$ 表示用小于 $m$ 的部分得到的和，$j$ 表示不小于 $m$ 的用了 $j$ 个。

最后时间复杂度就是 $O(n\sqrt{n})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 100005
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
int n, P, m, f[N], g[505][N], ans;
signed main(){
	n = rd(), m = sqrt(n) + 1, P = rd(), f[0] = g[0][0] = 1;
	for (int i = 1; i < m; i++) for (int j = i; j <= n; j++) f[j] = (f[j] + f[j - i]) % P;
	for (int i = 1; i < m; i++) for (int j = i; j <= n; j++) g[i][j] = (g[i][j - i] + (j >= m ? g[i - 1][j - m] : 0)) % P;
	for (int i = 0; i <= n; i++) for (int j = 0; j < m; j++) ans = (ans + 1ll * f[i] * g[j][n - i] % P) % P;
	printf ("%d\n", ans);
	return 0;
}

```

并且，伟大的 EI 有对于分拆数的第 $3$ 中做法，时间复杂度是 $O(n\sqrt{n})$，空间复杂度 $O(n)$，实测比上述做法快了很多。更关键的是，它可以求出 $1$ 到 $n$ 所有的分拆数。以下内容为复读 [分拆数的第三种做法](https://blog.csdn.net/EI_Captain/article/details/104729572)。

我们考虑对 Ferrers 图做一条 $y=x$ 的直线，并假设它在 $h$ 的时候离开了这张图。那么我们就可以得到他的两侧都是 $\le h$ 的整数划分。因此我们可以得到分拆数的生成函数的另一种表达式。

$$\prod_{k=1} \frac{1}{1-x^k} = \sum_{h=0} x^{h^2}\Big ( \prod_{k=1}^h \frac{1}{1-x^k} \Big )^2$$

注意到 $h^2 \le n$，所以 $h$ 不超过 $\sqrt{n}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 100005
il int rd(){
	int s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
int n, P, m, tmp[N], ans[N];
signed main(){
	n = rd(), m = sqrt(n) + 1, P = rd();
	ans[0] = tmp[0] = 1;
	for (int i = 1; i <= m; i++){
		for (int k = 0; k < 2; k++)
			for (int j = i; j <= n - i; j++) tmp[j] = (tmp[j] + tmp[j - i]) % P;
		for (int j = i * i; j <= n; j++) ans[j] = (ans[j] + tmp[j - i * i]) % P;
	}
	printf ("%d\n", ans[n]);
	return 0;
}

```

---

## 作者：LastKismet (赞：0)

# 前言
虽然名字叫五边形数定理，且确实与五边形数有关，但这个定理的重点事实上完全不在五边形数上。

这个定理可以 $O(n\sqrt n)$ 解决任意整数的拆分方案问题，详见例题部分。

本文参考了 [SF 的文章](https://www.luogu.com.cn/article/rejrmdfv)，在此拜谢。

由于证明并非 OI 中的重点，且网上已有一定量的详细证明，所以有一些非必要的证明过程作者会进行一定省略，但一般会在相应位置放上外链。

本文转载自[我讲解五边形数定理的博客](https://www.cnblogs.com/LastKismet/p/18948756)，希望能为各位提供**较**为详细的生成函数推导思路。

# 五边形数
友情提示：本部分可以跳过。

其几何意义就不说了，其递推式为：
$$
p_n=p_{n-1}+3n-2
$$
然后我们可以简单地推出其通项公式：
$$
p_n=\sum_{i=1}^n(3i-2)=\frac{3n^2-n}{2}
$$

然后是广义五边形数，不再限定 $n$ 为正整数。我们可以得到如下数列：
$$
0,1,2,5,7,12,15\dots
$$
对这个数列有一点印象就行了，等下我们会再遇到它。

# 欧拉函数与五边形数定理
注意，这里的欧拉函数 $\phi(x)$ 并非[数论中那个欧拉函数 $\varphi(x)$](https://www.cnblogs.com/LastKismet/p/18583949)。

$$
\begin{align*}
\phi(x)&=\prod_{k=1}^{\infty}(1-x^k)
&=\sum_{k=-\infty}^{\infty}(-1)^kx^{\frac{3k^2-k}{2}}
\end{align*}
$$

详细展开过程我就略了，此展开式由欧拉提出，若感兴趣可以自行搜索。

然后整个定理唯一和五边形数有关的部分出现了：注意到欧拉函数展开式中 $x$ 的次数是广义五边形数。于是这个定理便被称之为五边形数定理。也许是为了与[欧拉定理](https://www.cnblogs.com/LastKismet/p/18583949)做区分吧。

我们将欧拉函数升幂排序可得：
$$
\phi(x)=1-x-x^2+x^5+x^7-x^{12}-x^{15}+\dots
$$

# 整数拆分
求将一个正整数拆分为多个可重正整数之和的方案数。

这里推导一下这个问题的生成函数。

令 $ax^b$ 式系数 $a$ 表示方案数，$b$ 表示组成的数。

数 $i$ 的贡献序列的通项公式为：
$$
\sum_{k=0}^{\infty}x^{ik}=\frac{1}{1-x^{i}}
$$
这里简单证明一下，首先你应当知道 $\frac{1}{1-x}=\sum\limits_{k=0}^{\infty}x^k$。如果你不会这个的话，请自行学习生成函数入门或者跳过这段证明。

然后 $\frac{1}{1-x^{b}}=\sum\limits_{k=0}^{\infty}x^{kb}$，两边的 $x$ 同时 $b$ 次方可得。证毕。

那么我们将所有数的贡献多项式相乘即可得到这个问题的生成函数，此时次数 $b$ 的项的系数即为方案数，记作 $p(b)$。

$$
\sum_{k=0}^{\infty}p(k)x^k=\prod_{k=1}^{\infty}\frac{1}{1-x^k}
$$

这时候我们发现：
$$
\phi(x)=\prod_{k=1}^{\infty}(1-x^k)\\
\prod_{k=1}^{\infty}\frac{1}{1-x^k}=\frac{1}{\phi(x)}\\
\phi(x)\prod_{k=1}^{\infty}\frac{1}{1-x^k}=1\\
\phi(x)\sum_{k=0}^{\infty}p(k)x^k=1
$$

我们使用五边形数定理展开可得：

$$
(1-x-x^2+x^5+x^7-\dots)\sum_{k=0}^{\infty}p(k)x^k=1
$$

接下来我们尝试推出 $p(x)$ 的递推式，上述等式左右两边各项系数相等，那么除了 $0$ 次项外系数均为 $0$。

那么我们可以得出 $k$ 次项的系数为：
$$
p(k)-p(k-1)-p(k-2)+p(k-5)+p(k-7)-\cdots=0
$$
于是我们有了递推式：
$$
p(k)=p(k-1)+p(k-2)-p(k-5)-p(k-7)+\cdots
$$

五边形数的量级是 $\sqrt{n}$ 的，因为其通项为 $\frac{3n^2-n}{2}$。所以我们每次暴力枚举递推的复杂度是 $O(n\sqrt n)$ 的。

# 整数拆分-各数上限
要求拆分后每个正整数数量小于 $k$ 的方案数。

我们先推导一下这个问题的生成函数：

定义同上，数 $i$ 贡献序列的通项为：
$$
\sum_{j=0}^{k-1}x^{ij}=\frac{1-x^{ki}}{1-x^i}
$$
这个公式是这么推来的：
$$
\frac{1}{1-x^i}=\sum_{j=0}^{\infty}x^{ij}\\
\frac{x^{ki}}{1-x^i}=\sum_{j=k}^{\infty}x^{ij}
$$
作差即可。

因此这个问题的生成函数即为：
$$
\begin{align*}
\sum_{i=0}^{\infty}p'(i)x^i&=\prod_{i=1}^{\infty}\frac{1-x^{ki}}{1-x^i}\\
&=\prod_{i=1}^{\infty}(1-x^{ki})\prod_{i=1}^{\infty}\frac{1}{1-x^i}\\
&=\prod_{i=1}^{\infty}(1-x^{ki})\sum_{i=0}^{\infty}p(i)x^i
\end{align*}
$$
注意这里的系数用 $p'$ 表示，$p$ 表示无上限问题生成函数系数。

然后我们发现：
$$
\phi(x^k)=\prod_{i=1}^{\infty}(1-x^{ki})
$$
于是：
$$
\sum_{i=0}^{\infty}p'(i)x^i=\phi(x^k)\sum_{i=0}^{\infty}p(i)x^i
$$

由五边形数定理展开得：
$$
(1-x^k-x^{2k}+x^{5k}+x^{7k}-\dots)\sum_{i=0}^{\infty}p(i)x^i=\sum_{i=0}^{\infty}p'(i)x^i
$$

因而我们可以由 $p$ $O(\sqrt n)$ 求得 $p'$：
$$
p'(x)=p(x)-p(x-k)-p(x-2k)+p(x-5k)+p(x-7k)-\dots
$$

整体复杂度 $O(n\sqrt n+q\sqrt n)$。

# 例题
[洛谷整数拆分模板题](https://www.luogu.com.cn/problem/P6189)

```cpp
int n;
mint f[N];

inline int Ptg(int x){return 3*x*x-x>>1;}

inline void Main(){
    read(n,mod);
    f[0]=1;
    rep(i,1,n){
        rep(j,1,inf){
            int x=Ptg(j),y=Ptg(-j);
            if(x<=i)f[i]+=(j&1?1:mod-1)*f[i-x];
            if(y<=i)f[i]+=(j&1?1:mod-1)*f[i-y];
            else break;
        }
    }
    put(f[n]);
}
```

[HDU整数拆分-各数上限模板题](https://acm.hdu.edu.cn/showproblem.php?pid=4658)

```cpp
const int N=1e5+5;

int n,k;
mint f[N];

inline int Ptg(int x){return 3*x*x-x>>1;}

inline void Main(){
    read(n,k);
    mint ans=f[n];
    rep(j,1,inf){
        int x=Ptg(j),y=Ptg(-j);
        if(x*k<=n)ans+=(j&1?mod-1:1)*f[n-x*k];
        if(y*k<=n)ans+=(j&1?mod-1:1)*f[n-y*k];
        else break;
    }
    put(ans);
}
int main(){
    f[0]=1;
    rep(i,1,1e5){
        rep(j,1,inf){
            int x=Ptg(j),y=Ptg(-j);
            if(x<=i)f[i]+=(j&1?1:mod-1)*f[i-x];
            if(y<=i)f[i]+=(j&1?1:mod-1)*f[i-y];
            else break;
        }
    }
	// ReadFile(___);
	#define MultiTasks
	#ifdef MultiTasks
	int t;read(t);while(t--)
	#endif
	Main();
	return 0;
}
```

---

