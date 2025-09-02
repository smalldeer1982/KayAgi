# [ARC129D] -1+2-1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc129/tasks/arc129_d

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます．

あなたは，以下の操作を好きな回数繰り返すことができます．

- 整数 $ i $ ($ 1\ \leq\ i\ \leq\ N $) を選び，$ A_{i-1},A_i,A_{i+1} $ にそれぞれ $ -1,2,-1 $ を足す． ただしここで，$ A_0 $ は $ A_N $ を指すものとし，また $ A_{N+1} $ は $ A_1 $ を指すものとする．

$ A $ のすべての要素を $ 0 $ にすることが可能かどうか判定し，また可能な場合は必要な最小の操作回数を求めてください．

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 200000 $
- $ -100\ \leq\ A_i\ \leq\ 100 $
- 入力される値はすべて整数である

### Sample Explanation 1

以下のように $ 5 $ 回操作すればよいです． - $ i=2 $ を選んで操作する．$ A=(2,2,-2,-2) $ になる． - $ i=3 $ を選んで操作する．$ A=(2,1,0,-3) $ になる． - $ i=3 $ を選んで操作する．$ A=(2,0,2,-4) $ になる． - $ i=4 $ を選んで操作する．$ A=(1,0,1,-2) $ になる． - $ i=4 $ を選んで操作する．$ A=(0,0,0,0) $ になる．

## 样例 #1

### 输入

```
4
3 0 -1 -2```

### 输出

```
5```

## 样例 #2

### 输入

```
3
1 0 -2```

### 输出

```
-1```

## 样例 #3

### 输入

```
4
1 -1 1 -1```

### 输出

```
-1```

## 样例 #4

### 输入

```
10
-28 -3 90 -90 77 49 -31 48 -28 -84```

### 输出

```
962```

# 题解

## 作者：OIer_Eternity (赞：11)

# Description

给定一个环序列 $\{a_1,a_2,\cdots,a_n\}$，其中 $a_n$ 的下一位是 $a_1$。

现在可以进行若干次操作，每次操作任意选定一个位置 $i\in[1,n]$，并将该位置的权值加上 $2$，前后相邻位置的权值分别减去 $1$。

求将该序列全部变为 $0$ 所需要的最少操作次数，若无解则输出 `-1`。

# Solution

（事实上这题只需观察性质即可，并不需要推特别复杂的式子）

首先很容易观察到每一次操作不会改变 $\sum a_i$，因此若 $\sum a_i\not=0$ 则无解。

但仅仅有这一个性质还不够，而对于此类问题，可以考虑从差分数组或前缀和数组中寻找性质。

在经过探究后，可以发现本题的操作性质出现在前缀和数组之中。

记 $s_i=\sum\limits_{j=1}^i a_j$，我们考虑每次操作对前缀和数组 $\{s_1,s_2,\cdots,s_n\}$ 的影响，经过简单的推导可以发现：

- 若选择的位置 $k\in[2,n-1]$，前缀和数组将会变为 $\{s_1,s_2,\cdots,s_{k-1}-1,s_k+1,s_{k+1},\cdots,s_n\}$。

- 若选择的位置 $k=1$，前缀和数组将会变为 $\{s_1+2,s_2+1,s_3+1,\cdots,s_n+1,s_n\}$。

- 若选择的位置 $k=n$，前缀和数组将会变为 $\{s_1-1,s_2-1,s_3-1,\cdots,s_n-2,s_n\}$。

可以发现 $\sum s_i$ 的变化量始终是 $n$ 的倍数，那么说明若前缀和的和不为 $n$ 的倍数则无解。

接着考虑如何计算最少的操作次数。

首先我们先花费 $\dfrac{|\sum s_i|}n$ 的代价将 $\sum s_i$ 变为 $0$，因为只有这么做才有可能满足条件。

而接下来的操作就是选择 $[1,n-1]$ 中的任意位置 $p$，并将 $s_p$ 减去 $1$，$s_{p+1}$ 加上 $1$。

而若需要进行该种操作，$s_i$ 的任意前缀和必须不小于 $0$。

则我们可以计算出 $s_i$ 的 $n$ 个前缀和中最小的值 $\text{Min}$。

若 $\text{Min}$ 为负数，我们需要通过一些操作将其变为 $0$。

可以发现若我们同时选择位置 $1$ 和位置 $n$ 进行操作，$s_1$ 会被加上 $1$，$s_{n-1}$ 则会被减去 $1$。

因此我们只需要花费 $-2\times\text{Min}$ 的代价让 $s_1\leftarrow s_1-\text{Min}$  即可（因为 $\text{Min}<0$）。

最后只需加上选择 $[1,n-1]$ 中的任意位置 $p$，将 $s_p$ 减去 $1$，$s_{p+1}$ 加上 $1$ 的代价即可，详细过程可以结合代码理解。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
long long a[200005],sum;
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]+=a[i-1],sum+=a[i];
    if (sum%n||a[n]) return !puts("-1");
    sum/=n;
    for (int i=1;i<n;i++) a[i]-=sum;
    if (sum>0) a[n-1]-=sum;
    else a[1]-=sum;
    sum=abs(sum);
    long long cnt=0,Min=0;
    for (int i=1;i<=n;i++) cnt+=a[i],Min=min(Min,cnt);
    a[1]-=Min,a[n-1]+=Min,sum-=2*Min;
    long long cnt_p=0;
    for (int i=1;i<=n;i++){
        sum+=cnt_p;
        if (a[i]>0) cnt_p+=a[i];
        else cnt_p+=a[i];
    }
    printf("%lld\n",sum);
    return 0;
}
```

---

## 作者：Egg_eating_master (赞：5)

牛逼推式子题！

首先，当 $\sum a\not=0$ 时显然无解。

设 $x_i$ 表示 $i$ 被选择的次数，那么根据题意有

$$2\times x_i-x_{i-1}-x_{i+1}+a_i=0$$

设 $d_i=x_i-x_{i-1}$，上述式子可写成

$$d_{i+1}-d_i=a_i$$

所以

$$d_i-d_1=\sum_{j=1}^{i-1}(d_{j+1}-d_j)=\sum_{j=1}^{i-1} a_j$$

因此

$$\sum_{i=1}^n(d_i-d_1)=\sum_{i=1}^n\sum_{j=1}^{i-1}a_j=\sum_{i=1}^n (n-i)\times a_i$$

$$\sum_{i=1}^nd_i=n\times d_1+\sum_{i=1}^n (n-i)\times a_i$$

另一方面，$\sum d_i=\sum (x_i-x_{i-1})=0$，所以

$$d_1=-\dfrac{\sum\limits_{i=1}^n (n-i)\times a_i}{n}$$

如果求出来 $d_1$ 不是整数，那么无解；否则就可以求出所有的 $d$。

根据定义，$x_i=x_{i-1}+d_i$，所以

$$x_i=x_1+\sum_{j=2}^i d_j\ge 0$$

我们需要构造出一组方案使得 $\sum x$ 最小，相当于要让 $x_1$ 最小。根据上面的这个限制求出其最小值即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 200005;
int n;
int a[maxn];
int d[maxn];
int x[maxn];
int sum;
int res;
int ans;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    if (sum != 0) {cout << -1 << endl; return 0;}
    for (int i = 1; i < n; i++) res += a[i] * (n - i);
    if (res % n) {cout << -1 << endl; return 0;}
    d[1] = -res / n;
    for (int i = 2; i <= n; i++) d[i] = d[i - 1] + a[i - 1];
    res = 0;
    for (int i = 2; i <= n; i++) {
        res += d[i];
        x[1] = max(x[1], -res);
    }
    for (int i = 2; i <= n; i++) x[i] = x[i - 1] + d[i];
    for (int i = 1; i <= n; i++) ans += x[i];
    cout << ans << endl;
    return 0;
}
```


---

## 作者：EuphoricStar (赞：2)

挺有趣的题。自己推出来感觉挺有意思的。

首先显然若 $\sum\limits_{i=0}^{n-1} a_i \ne 0$ 就无解。

设 $b_i$ 为 $i$ 的操作次数。可得：

$$-b_{i-1} + 2b_i - b_{i+1} = a_i$$

整理得：

$$b_i = \frac{b_{i-1} + b_{i+1} - a_i}{2}$$

发现因为有 $i - 1$ 和 $i + 1$ 不好处理。考虑一个通用套路就是设 $b_i = x_i b_{i-1} + c_i$，得：

$$b_i = \frac{b_{i-1} + x_{i+1} b_{i} + c_{i+1} - a_i}{2}$$

整理得：

$$b_i = \frac{1}{2 - x_{i+1}} b_{i-1} + \frac{1}{2 - x_{i+1}} (c_{i+1} - a_i)$$

那么 $x_i = \frac{1}{2 - x_{i+1}}$，解得 $\forall i \in [1, n], x_i = 1$。那么：

$$b_i = b_{i-1} + c_{i+1} - a_i$$

得到：

$$c_i = c_{i+1} - a_i$$

发现 $b_i$ 是一个类似前缀和的形式，$b_n - b_0 = \sum\limits_{i=0}^{n-1} c_i - \sum\limits_{i=0}^{n-1} a_i = 0$，所以 $\sum\limits_{i=0}^{n-1} c_i = 0$。

设 $c_0 = c_n = t$，那么 $i \in [1, n - 1], c_i = t - \sum\limits_{j=i}^{n-1} a_j$，$c_0 = t$。因为 $\sum\limits_{i=0}^{n-1} c_i = 0$，所以 $t$ 可以解出来，如果 $t$ 是小数就无解。

那我们现在得到了每个 $c_i$，剩下的就是求 $\sum\limits_{i=0}^{n-1} b_i$ 的最小值，并要求 $b_i = b_{i-1} + c_i, \forall i \in [0, n - 1], b_i \ge 0$。

设 $b_0 = k$，那 $b_i$ 和 $\sum\limits_{i=0}^{n-1} b_i$ 是关于 $k$ 的一次函数，并且斜率都为正。因此我们二分最小的 $k$ 使得 $\forall i \in [0, n - 1], b_i \ge 0$，得到 $k$ 后一遍递推即可求出答案。

时间复杂度 $O(n \log V)$，$V$ 为值域。

[code](https://atcoder.jp/contests/arc129/submissions/41326577)

---

## 作者：Inui_Sana (赞：1)

给个很好理解的做法。

原有的操作还是太难看了，考虑变化为前缀和。然后就会发现，操作变成了在前缀和数组 $s$ 上选一个位置 $i$，$s_i\to s_i-1,s_{i+1}\to s_i+1$。

但是发现一个问题：一个环的前缀和怎么定义？这是困难的，但是不妨换一个角度，考虑 $a_i$ 是 $s_i$ 的差分数组，于是可以令 $s_i+a_i=s_{i\bmod n+1}$。这样当 $\sum a_i\not=0$ 时会出现矛盾，但是这个情况显然无解。

完成了 $s$ 的定义后就简单了。最后要还原成 $a_i=0$，变成 $s$ 则是 $s_i$ 全部相等。首先 $\sum s_i\bmod n>0$ 则无解，否则直接能操作就操作，直接模拟即可。具体地，只需要将整个环枚举两次即可。

code：

```cpp
int n,m;
ll a[N];
void Yorushika(){
	read(n);
	a[1]=0;
	rep(i,1,n){
		int x;read(x);
		if(i<n){
			a[i+1]=a[i]+x;
		}else{
			if(a[1]!=a[n]+x){
				puts("-1");
				return;
			}
		}
	}
	ll s=0;
	rep(i,1,n){
		s+=a[i];
	}
	if(s%n){
		puts("-1");
		return;
	}
	ll t=s/n,ans=0;
	rep(i,1,n){
		ll x=max(a[i]-t,0ll);
		a[i]-=x,a[i%n+1]+=x,ans+=x;
	}
	rep(i,1,n){
		ll x=max(a[i]-t,0ll);
		a[i]-=x,a[i%n+1]+=x,ans+=x;
	}
	printf("%lld\n",ans);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：AC_love (赞：0)

首先注意到我们的操作不会改变环上所有数的和，因此如果所有数的和不是 $0$ 一定无解。

设 $x_i$ 表示 $i$ 位置被操作了多少次，有：

$$- x_{i - 1} + 2x_{i} - x_{i + 1} + a_i = 0$$

即：

$$- x_{i - 1} + 2x_{i} - x_{i + 1} = -a_i$$

有多少个未知数呢？$n$ 个。

这样的方程有多少个呢？$n$ 个。

于是想到高斯消元。

但理论上高斯消元的复杂度是 $O(n^3)$ 的，我们该怎么办呢？

这个时候就需要灵活运用高斯消元了：我们消元的时候只需要处理两个方程里非 $0$ 位就行了，而非 $0$ 位个数很少，因此实际复杂度其实只有 $O(n)$。

到这里结束了吗？并没有。

如果你真的去写了高斯消元，你发现消到最后一行的时候把所有未知数都消没了，得到了一个形如 $0 = 0$ 的东西，我们失败了吗？

并没有。

根据高斯消元的性质，我们知道：如果消出了 $0 = 0$，代表方程组有多解。

存在多解？为啥呢？

我们发现：如果一个形如 $x_1, x_2, x_3, \cdots, x_n$ 的消除次数符合题目要求，那么 $x_1 + k, x_2 + k, x_3 + k, \cdots, x_n + k$ 一定也符合要求。

这时我们该怎么办呢？

考虑直接指定 $x_n = 0$，这样消到最后就有解了。

于是我们的高斯消元就完成了，我们求出了所有 $x_i$ 的值，下一步呢？

$x_i$ 不可能存在小数，因此如果存在小数，一定是无解的。

$x_i$ 也不可能是负数，因此如果最后求出的 $x_i$ 有负数，我们就把所有 $x_i$ 整体平移一下，然后所有 $x_i$ 的和就是答案了。

这个办法相比题解区其他方法要麻烦好多，提出这个方法仅供思维拓展，不建议使用。

---

## 作者：Phartial (赞：0)

不是很懂为啥这题有 2300.jpg

首先显然在经过一次操作后 $\displaystyle\sum_{i=1}^na_i$ 不变，所以有解的充分条件为 $\displaystyle\sum_{i=1}^na_i=0$。

我们设 $x_i$ 表示我们对下标 $i$ 进行了 $x_i$ 次这样的操作，那么我们有一系列方程，其中每个方程都形如 $a_i-x_{i-1}-x_{i+1}+2x_i=0$。考虑通过 $x_1,x_2$ 推出后续的数，我们有：

$$
x_i=a_{i-1}-x_{i-2}+2x_{i-1}
$$

于是可以得到：

$$
\begin{aligned}
  x_1&=x_1\\
  x_2&=x_2\\
  x_3&=a_2-x_1+2x_2\\
  x_4&=a_3-x_2+2x_3&=a_3+2a_2-2x_1+3x_2\\
  &\vdots
\end{aligned}
$$

定理 1：对所有 $i\ge 2$，$x_i$ 必定可以表示为 $v_i-(i-2)x_1+(i-1)x_2$ 的形式，且 $v_i=a_{i-1}-v_{i-2}+2v_{i-1}$。

证明：

考虑归纳。我们在上面列出的方程中已经证明了对 $i=2,3$ 来说定理 1 成立，对 $i\ge 4$，我们有：

$$
\begin{aligned}
  x_i
  &=a_{i-1}-x_{i-2}+2x_{i-1}\\
  &=a_{i-1}-(v_{i-2}-(i-4)x_1+(i-3)x_2)+2(v_{i-1}-(i-3)x_1+(i-2)x_2)\\
  &=a_{i-1}-v_{i-2}+(i-4)x_1-(i-3)x_2+2v_{i-1}-2(i-3)x_1+2(i-2)x_2\\
  &=(a_{i-1}-v_{i-2}+2v_{i-1})+[i-4-2(i-3)]x_1+[-(i-3)+2(i-2)]x_2\\
  &=v_i-(i-2)x_1+(i-1)x_2\\
\end{aligned}
$$

故得证。

考虑 $x_{n+1}$，我们知道它等于 $v_{n+1}-(n-1)x_1+nx_2$，但同时由于 $a_i$ 的循环性，它也等于 $x_1$。于是有 $x_1-x_2=\dfrac{v_{n+1}}{n}$，因为 $x_1,x_2$ 都为整数，所以有解的充要条件是 $n\mid v_{n+1}$。以下设 $d=\dfrac{v_{n+1}}{n}=x_1-x_2$。

那么我们可以使用 $x_1$ 和 $d$ 得出剩下所有 $x_i$。具体的，我们有：

$$
\begin{aligned}
  x_i
  &=v_i-(i-2)x_1+(i-1)x_2\\
  &=v_i-(i-2)x_1+(i-1)(x_1-d)\\
  &=v_i-(i-1)d+x_1\\
\end{aligned}
$$

因为我们要求 $x_i\ge 0$ 的同时使得 $\displaystyle\sum_{i=1}^nx_i$ 的值最小，且 $x_i$ 都为 $x_1$ 加上一个数，所以我们需要让 $x_1$ 最小，因此有：

$$
x_i=v_i-(i-1)d+x_1\ge 0\\
x_1\ge (i-1)d-v_i\\
x_1=\max((i-1)d-v_i)
$$

注意到 $x_1\ge 0$，所以最后 $x_1$ 还要和 $0$ 取 $\max$。然后直接算出剩下的 $x_i$，累加答案即可。

```cpp
#include <numeric>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 2;

int n, a[kN];
LL v[kN], x1, ans;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  if (accumulate(a + 1, a + n + 1, 0) != 0) {
    cout << "-1";
    return 0;
  }
  for (int i = 3; i <= n + 1; ++i) {
    v[i] = a[i - 1] - v[i - 2] + 2 * v[i - 1];
  }
  if (v[n + 1] % n != 0) {
    cout << "-1";
    return 0;
  }
  LL d = v[n + 1] / n;
  for (int i = 2; i <= n; ++i) {
    x1 = max(x1, (i - 1) * d - v[i]);
  }
  for (int i = 1; i <= n; ++i) {
    ans += x1 - (i - 1) * d + v[i];
  }
  cout << ans;
  return 0;
}
```


---

