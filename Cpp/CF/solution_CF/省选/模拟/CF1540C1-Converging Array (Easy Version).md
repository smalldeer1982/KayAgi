# Converging Array (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ q = 1 $ . You can make hacks only if both versions of the problem are solved.

There is a process that takes place on arrays $ a $ and $ b $ of length $ n $ and length $ n-1 $ respectively.

The process is an infinite sequence of operations. Each operation is as follows:

- First, choose a random integer $ i $ ( $ 1 \le i \le n-1 $ ).
- Then, simultaneously set $ a_i = \min\left(a_i, \frac{a_i+a_{i+1}-b_i}{2}\right) $ and $ a_{i+1} = \max\left(a_{i+1}, \frac{a_i+a_{i+1}+b_i}{2}\right) $ without any rounding (so values may become non-integer).

 See notes for an example of an operation.It can be proven that array $ a $ converges, i. e. for each $ i $ there exists a limit $ a_i $ converges to. Let function $ F(a, b) $ return the value $ a_1 $ converges to after a process on $ a $ and $ b $ .

You are given array $ b $ , but not array $ a $ . However, you are given a third array $ c $ . Array $ a $ is good if it contains only integers and satisfies $ 0 \leq a_i \leq c_i $ for $ 1 \leq i \leq n $ .

Your task is to count the number of good arrays $ a $ where $ F(a, b) \geq x $ for $ q $ values of $ x $ . Since the number of arrays can be very large, print it modulo $ 10^9+7 $ .

## 说明/提示

The following explanation assumes $ b = [2, 1] $ and $ c=[2, 3, 4] $ (as in the sample).

Examples of arrays $ a $ that are not good:

- $ a = [3, 2, 3] $ is not good because $ a_1 > c_1 $ ;
- $ a = [0, -1, 3] $ is not good because $ a_2 < 0 $ .

One possible good array $ a $ is $ [0, 2, 4] $ . We can show that no operation has any effect on this array, so $ F(a, b) = a_1 = 0 $ .

Another possible good array $ a $ is $ [0, 1, 4] $ . In a single operation with $ i = 1 $ , we set $ a_1 = \min(\frac{0+1-2}{2}, 0) $ and $ a_2 = \max(\frac{0+1+2}{2}, 1) $ . So, after a single operation with $ i = 1 $ , $ a $ becomes equal to $ [-\frac{1}{2}, \frac{3}{2}, 4] $ . We can show that no operation has any effect on this array, so $ F(a, b) = -\frac{1}{2} $ .

## 样例 #1

### 输入

```
3
2 3 4
2 1
1
-1```

### 输出

```
56```

# 题解

## 作者：Acfboy (赞：8)

这题看上去非常的奇怪，连“收敛（converging）”都来了，似乎是道很高大上的题目，完全不可做，但仔细想想似乎比 Div.2 D 还要简单。

别被“收敛”吓到，先研究一下这个操作到底在干什么，会对 $a_i$ 和 $a_{i+1}$ 产生什么样的影响。对比 $a_i$ 和 $a_{i+1}$ 的操作，发现不同只在于一个 $\min, \max$ 的区别和平均数加减 $\frac{b_i}{2}$ 的区别。后面这个区别引起了我们的注意，因为如果取后者，它们的差将变为 $b_i$, 而前一个是 $\min$ 后一个是 $\max$ 意味着它们的差也会取到最大。而且前面是平均数决定了这两个 $\min$ 和 $\max$ 里面的东西要么同时取到更新要么同时取到不更新。

那么这个操作就非常明白了：不断变化两数直到它们的差大于等于 $b_i$。所以如果 $a$ 中两个数原来的差不超过 $b_i$ 那么就会成为 $b_i$，如果一开始就超过了，就不会有任何变化。

然后继续往下看，题目给了我们 $a_i$ 的上界，让我们求可能的个数，那么只要求出下界就好了。

而那个变化已经决定了下界，设第一个数为 $f_1$, 那么第二个最小只能是 $f_1+b_1$, 再下个最小是 $f_1 + b_1 + b_2$, 然后是 $f_1 + b1 + b_2 + b_3$，以此类推。

那么题目就等价于给定了每一个开始的数，和每次要加上的范围，求最后一个数落在给定范围里的方案数。直接背包即可。

代码。

```cpp
#include <cstdio>
#include <algorithm>
const int N = 105, P = 1000000007;
int n, c[N], b[N], m, f1, f[N][N*N], l, r, ans;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 2; i <= n; i++) scanf("%d", &b[i]), b[i] += b[i-1];
    scanf("%d", &m), scanf("%d", &f1);
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        l += b[i] + f1, r += c[i];
        for (int j = std::max(l, 0); j <= r; j++)
            for (int k = 0; k <= c[i]; k++)
                f[i][j] = (f[i][j] + f[i-1][j-k]) % P;
    }
    for (int i = std::max(l, 0); i <= r; i++) ans = (ans + f[n][i]) % P;
    printf("%d", ans);
    return 0;
}
```

---

## 作者：monstersqwq (赞：6)

先挖掘几个性质罢。

- 在稳定状态下，一定满足 $\forall i\in\{2,3,\cdots,n\},a_i-b_{i-1}\ge a_{i-1}$。

如果不满足的话，对 $i-1$ 进行一次操作，就会改变原来的值，所以这是显然的。

- 对 $i$ 处进行一次操作后，$a_i+a_{i+1}$ 是不变的。

考虑操作的本质，形象地说，实际上是对两个数取平均后 向两边拉开相同的距离（$\dfrac{b_i}{2}$），如果能拉的更大就取拉后的结果，反之保持不变，从而我们可以很快看出来这个性质的正确性。

- 对 $i$ 处进行一次操作后，修改后的 $a_i$ 一定小于等于改前的 $a_i$，改后的 $a_{i+1}$ 一定大于等于改前的 $a_{i+1}$。

因为是取 min 和 max，所以是废话。

- 操作过程中，$\forall i,\sum\limits_{j=1}^{i}a_j$ 一定非严格递减。

结合第二三条性质可知，这是废话。

然后根据第一四条性质，就可以做了。

首先我们发现，设稳定后状态为 $d$，则一定有 $d_1\ge x,d_2\ge x+b_1,d_3\ge x+b_1+b_2,\cdots,d_n\ge x+\sum\limits_{i=1}^{n-1}b_i$。

由于前 $i$ 项的和是非严格递减的，则 $a$ 需要满足 $\forall i,\sum\limits_{j=1}^{i}a_j\ge\sum\limits_{j=1}^id_j\ge ix+\sum\limits_{j=1}^{i-1}(i-j)b_i$，再结合 $c$ 的条件，发现这个做个背包就好了，复杂度 $O(n^4)$（默认题目中所有限制同阶），结合前缀和优化可以做到 $O(n^3)$。

注意题目中 $a,b$ 均非负，背包时上下界需要考虑一下 $x$ 过小和过大的情况。

对于为何满足此下界的所有 $a$ 都是一组解，若最后的结果 $d_1$ 小于 $x$，说明一定对 $d_1$ 进行了至少一次有效果的操作，那么 $d_2=d_1+b_1$，以此类推，若在某处未进行有效操作，那么在它前面的 $d$ 的和便不满足要求，且由于与后面未进行，原先这些位置的 $a$ 也不满足要求，于是结论成立。

---

## 作者：Cry_For_theMoon (赞：1)

[传送门](codeforces.com/contest/1540/problem/C1)

一个有迹可循的 2700* 简单题。

~~大概就我学不会C2吧~~

##### 分析：

入手点显然是：
$$
\begin{cases}a_i=\min\{a_i,\frac{a_i+a_{i+1}-b_i}{2}\} \\
a_{i+1}=\max\{a_i,\frac{a_i+a_{i+1}+b_i}{2}\}
\end{cases}
$$
容易想到分讨第一个式子里两项的大小关系。会发现如果 $a_i+b_i<=a_{i+1}$ 则不会发生任何改变，反之新的 $a_i,a_{i+1}$ 满足 $a_i+b+a_{i+1}$. 如果数学比较强应该可以马上看出来 $\min \max$ 函数里第二项其实是方程
$$
\begin{cases}x+y=a \\
x-y=b\end{cases}
$$
 的解从而更快看出。

题里的收敛其实和高数啥的没关系。只要设收敛后的序列为 $d_1,d_2,...,d_n$. 那么对答案有贡献的序列最后应该满足：
$$
d_1 \ge x,d_i \ge a_{i-1}+b_{i-1}
$$
如果我们做前缀和，则
$$
\sum_{j=1}^i d_j \ge ix+\sum_{j=1}^{i-1}(i-j)\,\cdot\,b_i
$$
同时由题意有一个 
$$
\sum_{j=1}^ia_j \le \sum_{j=1}^ic_j
$$


考虑能不能把不好搞的 $a$ ，和 $d$ 用前缀和关联起来。首先有一个事实就是不管操作改变 $a_i$ 和 $a_{i+1}$ 的值与否其和不变。那么 $a$ 的前缀和就一定会大于等于 $d$ 的前缀和。证明如下：

设 $a$ 的前缀和为 $s_i$, $d$ 的前缀和为 $t_i$，则在 $[1,i)$ 的操作不影响 $s_i$ 和 $t_i$ 的值，$(i,n]$ 上的操作亦然。而每次在 $i$ 上的操作只可能让 $a_i$ 变小而不可能更大。那么每次操作后前缀和就只可能更小不可能更大。  

因此得到：
$$
\sum_{j=1}^i c_j \ge \sum_{j=1}^i a_j \ge \sum_{j=1}^id_j \ge ix+\sum_{j=1}^{i-1}(i-j) \cdot b_i
$$
得出这是 $a$ 合法的必要条件。

考虑证明其充分性。容易想到假设法，我们设 $a$ 满足这个不等式，但 $d_1<x$.

由于 $d_1<x$ 而原来 $a_1>=x$，因此必定有在 $1$ 处改变过 $a_1$ 与 $a_2$ 的值。那么 $d_2=d_1+b_1$.

依此类推。假设在 $k$ 处没有改变过 $a_k$ 与 $a_{k+1}$ 的值（$k \in [2,n])$，则 $\sum_{j=1}^ia_j=\sum_{j=1}^id_j$. 但是注意到此时对于 $2 \le i \le k$ 都满足 $d_i=d_{i-1}+b_{i-1}$. 而因为 $d_1<x$，那么 $\sum_{j=1}^ia_j=\sum_{j=1}^id_j \le ix+\sum_{j=1}^{i-1}(i-j) \cdot b_i$. 矛盾。所以充分性得到证明。

所以我们得到 $a$ 的前缀和的一个上下界。不难想到设 $f(i,j)$ 表示考虑了 $a$ 的前 $i$ 项前缀和为 $j$ 的方案数。此时容易得到 $a_{i+1}$ 的上下界。直接转移即可。复杂度为 $O(n^4)$.

但是有个大坑点就是 $a_i>=0$ 而 $x$ 可能为负。所以时刻记得下界和 $0$ 取 $\max$.

```C++
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=110,MAXM=1e4+10,moder=1e9+7;
int n,c[MAXN],b[MAXN],q,x;
ll f[MAXN][MAXM],sum[MAXN],sum2[MAXN],ans;
int main(){
	cin>>n;
	rep(i,1,n)cin>>c[i];
	rep(i,1,n-1)cin>>b[i];
	cin>>q>>x;
	rep(i,1,n){
		sum2[i]=sum2[i-1]+c[i];
		sum[i]=i*x;
		rep(j,1,i-1){
			sum[i]+=(i-j)*b[j];
		}
	}
	f[0][0]=1;
	rep(i,0,n-1){
		rep(j,0,sum2[i]){
			ll L=Max(0,sum[i+1]-j),R=c[i+1];
			rep(k,L,R){
				f[i+1][j+k]=(f[i+1][j+k]+f[i][j])%moder;
			}
		}
	}
	ll L=Max(0,sum[n]),R=sum2[n];
	rep(i,L,R){
		ans=(ans+f[n][i])%moder;
	}
	cout<<ans<<endl;
	return 0;
}

```





---

