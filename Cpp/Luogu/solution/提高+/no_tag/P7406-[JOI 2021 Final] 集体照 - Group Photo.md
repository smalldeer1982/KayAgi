# [JOI 2021 Final] 集体照 / Group Photo

## 题目描述

有 $N$ 个人，这 $N$ 个人编号为 $1 \sim N$，第 $h$ 个人的身高为 $h$。

有 $N$ 个台阶，这 $N$ 个台阶从低到高编号为 $1 \sim N$，第 $i$ 级台阶比第 $i+1$ 个台阶低 $2$ 个单位高度。每个台阶上只能站一个人，第 $H_i$ 个人站在第 $i$ 个台阶上。

你可以进行无数次如下操作：

- 选择 $i \in [1,N-1]$，交换第 $i$ 个台阶上的人和第 $i+1$ 个台阶上的人。

假设第 $i$ 个台阶上站的人的高度为 $a_i$，你要满足：

- 对于任意 $i \in [1,N-1]$，都有 $a_i <a_{i+1}+2$。

求最少的操作次数。

## 说明/提示

#### 样例 1 解释

设 $h_i$ 为第 $i$ 个台阶上站的人的身高：

- 交换第 $2$ 个人和第 $3$ 个人，$h_i=\{3,2,5,4,1\}$。
- 交换第 $4$ 个人和第 $5$ 个人，$h_i=\{3,2,5,1,4\}$。
- 交换第 $3$ 个人和第 $4$ 个人，$h_i=\{3,2,1,5,4\}$。

$3$ 步刚好满足要求。

#### 样例 2 解释

已经满足要求，不需要进行任何操作。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$N \le 9$。
- Subtask 2（7 pts）：$N \le 20$。
- Subtask 3（32 pts）：$N \le 200$。
- Subtask 4（20 pts）：$N \le 800$。
- Subtask 5（36 pts）：无特殊限制。

对于 $100\%$ 的数据，$3 \le N \le 5000$，$1 \le H_i \le N$，$H_i$ 互不相等。

#### 说明

翻译自 [The 20th Japanese Olympiad in Informatics Final Round C 集合写真的英文翻译 Group Photo](https://www.ioi-jp.org/joi/2020/2021-ho/2021-ho-t3-en.pdf)。

## 样例 #1

### 输入

```
5
3 5 2 4 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5
3 2 1 5 4```

### 输出

```
0```

## 样例 #3

### 输入

```
9
6 1 3 4 9 5 7 8 2```

### 输出

```
9```

# 题解

## 作者：Starrykiller (赞：11)

找出性质 DP。好题！

> 结论：最终序列 $a$ 由若干个连续等差下降子段构成，其中公差为 $-1$。（对于上升的情况，我们可以认为是若干个长度为 $1$ 的下降子段）

考虑证明：首先 $a$ 是一个排列。注意到 $a_i+2\gt a_{i-1} \iff a_i\ge a_{i-1}-1$ 即可。


套路地，考虑设计一个 dp。设 $f(i)$ 为**值域** $[1,i]$ 已经分成若干个连续下降子段（可以认为是放在结果序列 $a$ 的前 $i$ 个位置）的最小交换次数。套路地写出转移：

$$f(i)=\min _{j\in [0,i)} \{f(j)+\mathrm{calc}(j+1,i)\}$$

其中 $\mathrm{calc}(l,r)$ 表示将 $[l,r]$ **值域**排列成**一个**连续下降子段的最小交换次数。

现在的序列中，**位置** $[1,l)$ 已经被**值域** $[1,l)$ 占据，所以 $[1,l)$ 已经被考虑过了，不能重复计算。我们只需要考虑 $[l,n]$ 这段值域，目标是：让**值域** $[l,r]$ 占据位置 $[l,r]$。

以下默认 $1\le i\neq j\le n$。

我们可以认为，操作是这么进行的：先将**值域**为 $[l,r]$ 的数摆在**位置** $[l,r]$，再交换使其变成下降的。

将值域为 $[l,r]$ 的数染成 $0$，值域为 $(r,n]$ 的数染成 $1$，我们要让 $0$ 占据**位置** $[l,n]$ 的前一段，并且 $0$ 之间不互相交换。这部分答案就是 $0,1$ 之间的逆序对数。也就是：

$$\sum_{i=1}^n \sum_{j=i+1}^n [a_i\gt r][l\le a_j\le r]$$

最后，交换成下降序列，交换次数就是顺序对数，也就是：

$$\sum_{i=1}^n\sum_{j=i+1}^n [a_i\in [l,r]][a_j\in [l,r]][a_i\lt a_j]$$

朴素地实现 $\mathrm{calc}$ 可以获得 $44$ 分。注意到：这是一个二维数点问题。例如，对于顺序对 $(i,j)$，视为 $(a_i,a_j)$ 上有一个点，那么每次查询就是查询 $(l,l)$，$(r,r)$ 为顶点的正方形内的点的数量，可以二维前缀和维护。

这样，我们就做到了 $\Theta(n^2)$。[代码](https://loj.ac/s/2110545)。

---

## 作者：ix35 (赞：10)

补充一下另外两篇题解，实际上在计算 $[l+1,r]$ 新增的逆序对数量时使用树状数组是多此一举的。

我们无非要计算以下两部分的数对数量：

- 原排列中某个 $x\in [l,r]$ 在 $y\in [1,l-1]$ 之前：暴力求出 $f(i,j)$ 表示原排列排在 $i$ 后面的 $<j$​ 的数有多少个即可；

- 原排列中某个 $x\in [l,r]$ 在 $y\in [l,r],\ y>x$​ 之前：求出原排列所有顺序对再二维前缀和。

具体细节见代码。

时间复杂度为 $O(n^2)$，可见树状数组是完全不必要的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=5010;
int n,a[MAXN],nw[MAXN],dp[MAXN],sum[MAXN][MAXN],cnt[MAXN][MAXN];
int main () {
	scanf("%d",&n);
	for (int i=1;i<=n;i++) {scanf("%d",&a[i]);}
	for (int i=n;i>=1;i--) {
		for (int j=1;j<=a[i]-1;j++) {cnt[a[i]][j]=nw[j];}
		for (int j=a[i];j<=n;j++) {nw[j]++;}
		for (int j=i-1;j>=1;j--) {
			if (a[j]<a[i]) {sum[a[j]][a[i]]++;}
		}
	}
	for (int i=n;i>=1;i--) {
		for (int j=i+2;j<=n;j++) {sum[i][j]+=sum[i][j-1]+sum[i+1][j]-sum[i+1][j-1];}
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for (int i=0;i<=n;i++) {
		int w=0;
		for (int j=i+1;j<=n;j++) {
			w+=cnt[j][i];
			dp[j]=min(dp[j],dp[i]+w+sum[i+1][j]);
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}
```


---

## 作者：moongazer (赞：7)

考察符合条件的序列的性质，一定可以被分割成为 $m$ 个降序连续段：$(r_1\sim l_1);(r_2\sim l_2);(r_3\sim l_3);\cdots;(r_m\sim l_m)$ 其中 $l_1=1,l_2=r_1+1,r_3=l_2+1,\cdots,r_m=l_{m-1}+1$ 不难证明不满足以上结构的排列都是非法的。

考虑调整次数即前后相对顺序改变的无序对个数，于是就可以 dp 了。

设 $f_i$ 表示 $1\sim i$ 调整成若干连续段的最小代价，考虑若最后一段是 $(i\sim j),j\le i$ 那么对于一个 $j\le k\le i$ 和它产生贡献的有：(1) $1\sim j-1$ 中位置在它后面的数，(2) $j\sim k-1$ 中位置在它前面的数，(3) $k+1\sim i$ 中位置在它后面的数。

(1) 和 (3) 都可以用树状数组简单处理，考虑将 (2) 转化为找在 $j$ 后面的 $k$，于是用一个树状数组维护 $1\sim i$ 的位置，对每个 $k$ 加上位置在它后面的数的个数，这样会算多 $j\sim k-1$ 中位置在它后面的数，可以在 $j$ 向左移动时减掉，于是再用一个树状数组维护即可。

时间复杂度 $\operatorname{O}(n^2\log n)$。

```cpp
const int N = 5005;

class BIT {
 public:
  int sum[N];
  void clear() { memset(sum, 0, sizeof(sum)); }
  void update(int x, int num);
  int query(int x);
} in, out;

int a[N], pos[N];
ll f[N];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    pos[a[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    in.clear();
    out.update(pos[i], 1);
    f[i] = iinf;
    ll sum = 0;
    for (int j = i; j >= 1; --j) {
      sum -= in.query(pos[j]);
      sum += i - out.query(pos[j]);
      f[i] = std::min(f[i], f[j - 1] + sum);
      in.update(pos[j], 1);
    }
  }
  write(f[n]), EL;
  return 0;
}

void BIT::update(int x, int num) {
  while (x <= n) {
    sum[x] += num;
    x += x & -x;
  }
}
int BIT::query(int x) {
  int ans = 0;
  while (x) {
    ans += sum[x];
    x -= x & -x;
  }
  return ans;
}
```

---

## 作者：DesignDigits (赞：6)

> 写一篇最长，但应该最好理解的题解

题中 $1\leq H_i\leq N, H_i$ 互不相同，告诉我们 $H$ 一定是 $1, 2, \dots, N$ 的排列。

而 $a_i<a_{i+1}+2$ 告诉我们：每项要么比下一项大 $1$，要么小于下一项（因为不能相等）。

发挥你的想象力！这就是要求我们把序列变成像 $3, 2, 1, \ 5, 4,\ 8, 7, 6$ 这样，**若干个 $x, x-1, x-2, \dots$ 这样的“顺子”相连，每个顺子中最大值 $+\ 1$ 等于下一个顺子中最小值** 的形式。

但这个结论还不能确定这个序列最终的样子。假如我们已经决定了最终的序列是什么样，最少要交换几次相邻元素才行呢？以 $d, a, c, b\to a, b, c, d$ 为例，容易想到先把 $d$ 一直换到最右，然后依次把 $c, b, a$ 换到第 $3, 2, 1$ 位。

> 下证此方法消耗的交换次数为最少。我们把像 $d, c$ 这样，排成与目标顺序反过来了的两个元素，称作一个“逆序对”。排序的过程相当于把逆序对数量减为 $0.$ 每次交换，逆序对数减少 $0$ 或 $1$，而上述方法中每次交换都减少 $1,$ 所以 **这是一种最省交换次数的方法**！

设 $f(i)$ 为抽出 $[i+1, n]$ 内的数后，剩下的排成相连顺子，最少要交换几次。例如 $3, 5, 2, 4, 1$ 中，$f(4)$ 考虑的是 $3, 2, 4, 1$，易看出 $f(4)=1.$

这样，设最后一个顺子是 $i, i-1, \dots, j+2, j+1$，那我们 **先把这个顺子在最右边排好**，剩下的部分消耗的交换次数，就是 $f(j).$ 题目的输出就是 $f(n).$

最后只要解决“先把这个顺子在最右边排好”的交换次数问题。根据上面的证明，依次把 $j+1, j+2, \dots, i$ 交换到从右数第 $1, 2, \dots, i-j$ 位。

对任意 $k\ (j+1\leq k\leq i),$ 当我们安排 $k$ 的位置时它所需的交换次数，就是 $[1, i]$ 内“应该在 $k$ 左边，但现在却堵在 $k$ 右边”的数的个数；这些数就是 $[1, j] \cup [k+1, i].$

我们设 $g(x, y)$ 为 $1, 2, \dots, y$ 中排在 $x$ 右边的有几个，就可以列出转移方程：

$$ f(i) = \min _{j=1} ^{i-1} f(j) + \sum _{k=j+1} ^i g(k, j)+g(k, i)-g(k, k)$$

$g$ 则可以递推：

$$g(x, y)=g(x, y-1) +[y\ \text{在}\ x\ \text{的右边}]$$

这是一个 $O(n^3)$ 的解法。但显然，对 $g$ 求两种前缀和 $(p(x, y)=\sum_{i=1}^{x}g(i,y), \quad q(x)=\sum_{i=1}^{x}g(i, i))$ 就能优化到 $O(n^2).$

```cpp
for (int i=1; i<=n; i++) b[a[i]] = i;
for (int i=1; i<=n; i++)
	for (int j=1; j<=n; j++) {
		g[i][j] = g[i][j-1] + (b[j]>b[i]);
		p[i][j] = p[i-1][j] + g[i][j];
		q[i] = q[i-1] + g[i][i];
}

for (int i=1; i<=n; i++) {
	f[i] = inf;
	for (int j=0; j<i; j++) f[i] = min(f[i],
		(p[i][j]-p[j][j]) + (p[i][i]-p[j][i]) - (q[i]-q[j])+f[j]);
}
```

---

## 作者：ShwStone (赞：4)

### 思路分析

可以看出符合 $h_i < h_{i+1} + 2$ 的排列有一个特点：一定是将一个顺序序列分成多个部分，并将每个部分都逆转。比如 $[1,2,3,4,5]$ 的 1 到 3 和 4 到 5 分别反转，就是 $[3,2,1,5,4]$。

注意：接下来所有的下标表示的都是值域，并不是序列的坐标，而是序列中的值！

如果我们能求出将原序列的 $[l,r]$ 部分交换成全部反转所需的步骤（记作 $g_{l,r}$），就可以用 dp 解决此题。定义 $f_i$ 表示只考虑 $[1,i]$ 的**值域**区间所需的最小步骤，那么可以通过枚举最后一段连续下降序列的长度来转移，即：$f_i\leftarrow\min_{j=1}^{i - 1}{(f_{j}+g_{j+1,i})}$。

剩下的问题就是考虑怎么快速求 $g$。

在目标序列中，$[l,r]$ 如果是一段连续下降区间，那么 $[l,r]$ 内部会产生全部 $\frac{(r - l + 1) \times (r - l)}{2}$ 个逆序对，但是 $[l,r]$ 与 $[1,l-1],[r+1,n]$ 之间**不会产生任何逆序对**。

我们可以枚举出原序列的 $[l,r]$ 内部还差多少个逆序对没产生（有多少个“顺序对”），以及 $[l,r]$ 与外部产生了几个多余的逆序对，则 $g_{l,r}$ 就是**内部“顺序对”与外部逆序对之和。**

而逆序对和顺序对本身是很好统计的。以逆序对为例：用 $b_{i,j}$ 表示在原序列中 $i$ 和 $j$ 两个数是否产生了逆序对，那么对 $b$ 做二维前缀和得到 $s$，$s_{i,j}$ 就表示第一个数小于等于 $i$，第二个数小于等于 $j$ 的逆序对个数。

逆序对对于 $g_{l,r}$ 的贡献（即 $[l,r]$ 与外部的逆序对）就是 $s_{r,l-1}-s_{l-1,l-1}$。

注意，这里我们只考虑了 $[l,r]$ 与 $[1,l-1]$ 之间的逆序对。为什么不考虑 $[r+1,n]$ 呢？是因为在计算后面的 $g$ 时，自然会统计到 $[l,r]$ 与 $[1,l-1]$，如果多考虑反而会重复。

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FILE_IO
namespace io {...};
using namespace io;

const int maxn = 5e3 + 5;

int n;
int h[maxn];
int rev[maxn][maxn], drev[maxn][maxn], dp[maxn];

int calc(int l, int r) {
    int res = 0;
    res += (drev[r][r] - drev[l - 1][r] - drev[r][l - 1] + drev[l - 1][l - 1]);
    res += rev[r][l - 1] - rev[l - 1][l - 1];
    return res;
}

int main() {
    // freopen("photo.in", "r", stdin);
    // freopen("photo.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; i++) {
        read(h[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (h[i] > h[j]) rev[h[i]][h[j]]++;
            else drev[h[i]][h[j]]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            drev[i][j] += drev[i][j - 1] + drev[i - 1][j] - drev[i - 1][j - 1];
            rev[i][j] += rev[i][j - 1] + rev[i - 1][j] - rev[i - 1][j - 1];
        }
    }
    memset(dp, 0x3f, sizeof dp);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j >= 1; j--) {
            dp[i] = min(dp[i], dp[j - 1] + calc(j, i));
        }
    }
    write(dp[n]);
	return 0;
}
```

---

## 作者：7KByte (赞：2)

$a_i<a_{i+1}+2$，等价于 $a_i-1\le a_{i+1}$ 。

如果我们将 $a_i$ 看成台阶，那么每次最多只能下降一个。

所以满足条件的排列一定可以分成若干段连续下降的台阶。

我们定义状态 $f[i]$ 表示前 $i$ 个数合法的最小代价。

转移方程为 $f[i]=\min\limits_{0\le j<i}\{f[j]+calc(j+1,i)\}$ 。

其中代价函数 ``calc(l,r)`` 表示将区间 $[l,r]$ 还原成一个下降的台阶的最小代价。

由于是邻项交换，所以考虑逆序对。

分开讨论。

对于 $<l$ 的数，在 $f[l-1]$ 中已经考虑过了，直接忽略。

对于 $\ge l$  并 $\le r$ 的数，计算顺序对 $i<j$ 且 $a_i <a_j$ 的个数。

对于 $>r$ 的数，只会与在它后面的 $\le r$ 的数产生贡献。

直接 $\mathcal{O}(N^2)$ 计算 ``calc`` 函数，总时间复杂度 $\mathcal{O}(N^4)$ ，可以得到 $44$ 分。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 5005
using namespace std;
int n,a[N],f[N];
int calc(int l,int r){
	int sum=0;
	rep(i,1,n)rep(j,i+1,n){
		if(a[i]<l||a[j]<l)continue;
		if(a[i]>r&&a[j]>r)continue;
		if(a[i]<=r&&a[j]<=r)sum+=a[i]<a[j];
		else if(a[i]>r)sum++;
	}
	return sum;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	memset(f,0x3f,sizeof(f));f[0]=0;
	rep(i,1,n)rep(j,0,i-1)f[i]=min(f[i],f[j]+calc(j+1,i));
	printf("%d\n",f[n]);
	return 0;
}
```

观察一下发现 ``calc`` 函数本质上还是计算逆序对，用两个树状数组维护一下即可。

我们可以通过 ``calc(l,r)`` 基础上加一个数快速计算 ``calc(l,r+1)`` ，总时间复杂度 $\mathcal{O}(N^2\log N)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 5005
using namespace std;
int c[2][N],n,a[N],f[N],mat[N];
inline void add(int op,int x,int y){for(;x<=n;x+=x&-x)c[op][x]+=y;}
inline int ask(int op,int x){int sum=0;for(;x;x-=x&-x)sum+=c[op][x];return sum;}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]),mat[a[i]]=i;
	memset(f,0x3f,sizeof(f));f[0]=0;
	rep(i,0,n-1){
		memset(c,0,sizeof(c));
		int sum=0;
		rep(j,i+1,n)add(1,mat[j],1);
		rep(j,i+1,n){
			sum+=2*ask(0,mat[j])+i+ask(1,mat[j])-j;
			add(1,mat[j],-1);add(0,mat[j],1);
			f[j]=min(f[j],f[i]+sum);
		}
	}
	printf("%d\n",f[n]);
	return 0;
}
```

---

## 作者：lilong (赞：0)

不难发现最终的序列一定是若干个公差为 $-1$ 的等差数列（上升部分视为若干个长度为 $1$ 的下降序列。设 $f_i$ 表示将值域为 $[1,i]$ 中的数排合法的最少交换次数（首项较小的要排到前面，否则与较大的首项会出现“断层”），则有显然的转移：

$$f_i=\min_{j=0}^{i-1} f_j+\operatorname{calc}(j+1,i)$$

考虑如何快速计算 $\operatorname{calc}(j+1,i)$。可以分两部分考虑，一部分是将 $[j+1,i]$ 内的数移到 $[j+1,i]$ 下标的操作次数，另一部分是 $[j+1,i]$ 内部调整成降序的操作次数。第一部分可以写成 $\sum_{p<q}[a_p>i][j+1 \le a_q \le i]$（$[1,j]$ 部分已经排好了，不用管），第二部分可以写成 $\sum_{p<q}[j+1\le a_p \le i][j+1\le a_q \le i][a_p<a_q]$。两个式子都是在统计指定值域范围内的顺序对/逆序对数量，因此可以将满足 $p<q$ 的 $(a_p,a_q)$ 数对视为平面上的若干个点，只需使用二位前缀和统计满足条件的点即可。

时间复杂度 $O(n^2)$。


```cpp
#include<iostream>
#include<cstdio>
#define N 5010
#define ll long long
using namespace std;
int n,a[N],f[N],s1[N][N],s2[N][N];
int js1(int l1,int l2,int r1,int r2){
    return s1[l2][r2]-s1[l1-1][r2]-s1[l2][r1-1]+s1[l1-1][r1-1];
}
int js2(int l1,int l2,int r1,int r2){
    return s2[l2][r2]-s2[l1-1][r2]-s2[l2][r1-1]+s2[l1-1][r1-1];
}
int calc(int l,int r){
    return js1(r+1,n,l,r)+js2(l,r,l,r);
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            if(a[i]>a[j])s1[a[i]][a[j]]=1;
            else s2[a[i]][a[j]]=1;
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            s1[i][j]+=s1[i-1][j]+s1[i][j-1]-s1[i-1][j-1];
            s2[i][j]+=s2[i-1][j]+s2[i][j-1]-s2[i-1][j-1];
        }
    for(int i=1;i<=n;i++){
        f[i]=0x3f3f3f3f;
        for(int j=0;j<i;j++)
            f[i]=min(f[i],f[j]+calc(j+1,i));
    }
    cout<<f[n];
    return 0;
}
```

---

## 作者：RyexAwl (赞：0)

令 $pos[h[i]]=i$，一个直接的 $O(n^2\times n!)$ 的暴力是考虑枚举结果排列 $p$，然后计算序列 $pos[p_1],pos[p_2],...,pos[p_n]$ 中的逆序对个数 $cnt$，$cnt$ 即为将序列 $h[]$ 通过交换操作“调整”成排列 $p$ 的最小操作次数（不懂的话可以左转 [P1966 [NOIP2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966)）。

考虑依次把 $1,2,3,...,n$ 填到 $n$ 个格子上去“构造合法排列”。

![](https://cdn.luogu.com.cn/upload/image_hosting/olijurn3.png)

考虑把 $1,2,3,...,i$ 填到格子上，因为大于等于 $i+2$ 的数是不能填到 $1,2,3...,i$ 前面的，而 $i+1,i+2,...,n$ 这些数中有且仅有 $i+1$ 能够填到 $i$ 的前面，那么意味着把 $1,2,3,...,i$ 填到格子上后，$1,2,3,...,i$ 这些数中至多有一个数前面有空格子，并且这个数一定是 $i$。

比如在 $n=10,i=5$ 时，在把 $1,2,3,4,5$ 填到格子中后，有且仅有 $5$ 前面有空格子。

![](https://cdn.luogu.com.cn/upload/image_hosting/ovb30x8z.png)

那么把 $[1,i]$ 填到格子中后一定是如下的形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/me7vain0.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/sg2n85xg.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/h8ppup50.png)


即一段前缀全是数（可能这段为空），接一堆空格，再接一段连续的数，并且这个数的开头是 $i$（这一段也可能为空）。

但是我们发现这样并不能很快的在 DP 枚举方案的时候确定方案的花费。

但是我们进一步发现，$i$ 后面只能接 $i-1$，而如果 $i$ 后面接了 $i-1$，那么 $i-1$ 后面只能接 $i-2$。

设绿色段的长度为 $j$，红色段的长度为 $i-j$，那么红色段一定是 $i,i-1,...,i-(i-j)+1$。而绿色段由 $1,2,3,...,j$ 构成。

那么考虑一个 $O(n^3)$ 的暴力 DP，令 $f[i,j,k]$ 表示考虑将 $1,2,...,i$ 填到格子中，恰好填了长度为 $j$ 的前缀（即绿色部分的长度为 $j$),且 $i$ 填到格子 $k$ 中的所有方案中，花费最小是多少。

这里“花费”定义为将 $1,2,...,i$ 填到格子后，将所有有数的格子拼接成一个长度为 $i$ 的序列 $a[]$，序列 $pos[a[1]],pos[a[2]],...,pos[a[i]]$ 的逆序对个数。


令 $suf[i,k]=\sum_{j=i-k}^{i-1}[pos[j]<pos[i]],pre[i,k]=\sum_{j=1}^k[pos[j]>pos[i]]$。

如果 $j=i$：

$$
f[i+1,j+1,j+1]\gets f[i,j,k]+pre[i+1,i]
$$


如果 $j\not= i,k=j+2$：

$$
f[i+1,i+1,k-1]\gets f[i,j,k]+pre[i+1,j]+suf[i+1,i-j]
$$

如果 $j\not =i,k\not= j+2$：

$$
f[i+1,j,k-1]\gets f[i,j,k]+pre[i+1,j]+suf[i+1,i-j]
$$

同时对于 $k\ge i+2$ 的 $k$ 有转移：

$$
f[i+1,j,k]\gets \min_{t}(f[i,i,t])+pre[i+1][i]
$$

配合滚动数组技巧优化空间，可以拿到 64 分。

代码：

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 805;

int pre[N][N],suf[N][N],f[2][N][N],pos[N];

int n;

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    gin >> n;
    rep(i,1,n) {
        int x; gin >> x; pos[x] = i;
    }
    rep(i,1,n) {
        rep(j,1,i-1) {
            pre[i][j] = pre[i][j-1];
            if (pos[j] > pos[i]) ++ pre[i][j];
        }
        per(j,i-1,1) {
            int t = i - j;
            suf[i][t] = suf[i][t-1];
            if (pos[j] < pos[i]) ++ suf[i][t];
        }
    }
    f[0][0][0] = 0;
    rep(i,0,n-1) { memset(f[(i+1)&1],0x3f,sizeof f[(i+1)&1]); rep(j,0,i) {
		rep(k,0,n) {
    		if (i > 0 && k == 0) continue;
			if (j == i) {
				f[(i+1)&1][j+1][j+1] = std::min(f[(i+1)&1][j+1][j+1],f[i&1][j][k] + pre[i+1][i]);
			}
			else {
				if (k == 0) continue;
				if (k == j + 2) 
					f[(i+1)&1][i+1][k-1] = std::min(f[(i+1)&1][j+1][k-1],f[i&1][j][k] + pre[i+1][j] + suf[i+1][i-j]);
				else f[(i+1)&1][j][k-1] = std::min(f[(i+1)&1][j][k-1],f[i&1][j][k] + pre[i+1][j] + suf[i+1][i-j]);
			}
		}
		if (i == j) {
			int val = 0x3f3f3f3f;
			rep(k,0,n) val = std::min(val,f[i&1][j][k]);
			rep(k,i+2,n) f[(i+1)&1][j][k] = std::min(f[(i+1)&1][j][k],val + pre[i+1][i]); 
		}
	}
	}
	int ans = 0x3f3f3f3f;
	rep(i,1,n) ans = std::min(ans,f[n&1][n][i]);
	prt << ans;
}

}signed main(){wxy::main(); return 0;}
```

但是实际上可以发现第三维可以直接去掉，因为我们并不在意 $i$ 具体是在哪个格子，只要确定了前缀的长度 $i$ 在哪费用都是一样的。

因此可以直接令 $f[i,j]$  表示考虑将 $1,2,...,i$ 填到格子中，恰好填了长度为 $j$ 的前缀（即绿色部分的长度为 $j$) 的所有方案中，花费最小是多少。

转移类似上面的暴力 DP。

复杂度 $O(n^2)$。代码：

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 5005;

int pre[N][N],suf[N][N],f[N][N],pos[N];

int n;

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    gin >> n;
    rep(i,1,n) {
        int x; gin >> x; pos[x] = i;
    }
    rep(i,1,n) {
        rep(j,1,i-1) {
            pre[i][j] = pre[i][j-1];
            if (pos[j] > pos[i]) ++ pre[i][j];
        }
        per(j,i-1,1) {
            int t = i - j;
            suf[i][t] = suf[i][t-1];
            if (pos[j] < pos[i]) ++ suf[i][t];
        }
    }
    memset(f,0x3f,sizeof f); f[0][0] = 0;
    rep(i,0,n-1) {
		rep(j,0,i) {
			if (j == i) {
				f[i+1][j+1] = std::min(f[i+1][j+1],f[i][j] + pre[i+1][j]);
			} else {
				f[i+1][j] = std::min(f[i+1][j],f[i][j] + pre[i+1][j] + suf[i+1][i-j]);
				f[i+1][i+1] = std::min(f[i+1][i+1],f[i][j] + pre[i+1][j] + suf[i+1][i-j]);
			}
			if (i == j) {
				f[i+1][i] = f[i][j] + pre[i+1][i];
			}
		}
	}
	prt << f[n][n];
}

}signed main(){wxy::main(); return 0;}
```













---

