# 【MX-J1-T1】『FLA - III』Spectral

## 题目背景

原题链接：<https://oier.team/problems/J1A>。

---

> 没有看到昂星团。

## 题目描述

有一团火，最开始它的温度是 $0$，火焰旁边有 $n$ 个炭块，每块炭都有 $k$ 点能量。

使用 $T_i$ 表示烧掉 $i$ 块炭后火焰的温度，有：

$$T_i = \begin{cases} 0 & i = 0 \\ k+ \dfrac{T_{i-1}}{i} & i \neq 0 \end{cases}$$

火焰能够达到的最高温度是多少？

## 说明/提示

**「样例解释 #1」**

对于第一组测试数据，有 $1$ 块炭，未烧炭时火焰温度为 $0$，烧掉 $1$ 块炭后火焰温度为 $6$，答案为 $6.0$。对于第二组测试数据，有 $2$ 块炭，未烧炭时火焰温度为 $0$，烧掉 $1$ 块炭后火焰温度为 $7$，烧掉 $2$ 块炭后火焰温度为 $10.5$，答案为 $10.5$。

**「数据范围」**

|测试点编号|$T \leq$|$n \leq $|$k \leq$|
|:---:|:---:|:---:|:---:|
|$1 \sim 2$|$5$|$2$|$10$|
|$3 \sim 4$|$5$|$10^7$|$10^9$|
|$5$|$10^5$|$10^9$|$10^9$|

对于 $100\%$ 的数据，$1 \leq T \leq 10^5$，$1 \leq n,k \leq 10^9$。

## 样例 #1

### 输入

```
2
1 6
2 7
```

### 输出

```
6.0
10.5
```

# 题解

## 作者：ScaredQiu (赞：11)

### 模拟、数学

------------

#### 测试点 $1 \sim 2$

容易得到在 $n=1$ 时答案为 $k$，在 $n=2$ 时答案为 $1.5k$。

#### 测试点 $3 \sim 4$

暴力计算 $T_1 \sim T_n$ 后取最大值。

#### 测试点 $5$

|$i$|$0$|$1$|$2$|$3$|$4$|$5$|$\cdots$|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|$T_i$|$0$|$k$|$1.5k$|$1.5k$|$1.375k$|$1.275k$|$\cdots$|

**序列 $T$ 的最大值是 $T_2$ 和 $T_3$，读者可以自行查看题解结尾处的证明。**

当 $n=1$ 时答案为 $k$，否则答案为 $1.5k$。

单组数据时间复杂度 $O(1)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        if(n==1) printf("%d.0\n",k);
        else if(k%2==0) printf("%d.0\n",k+k/2);
        else printf("%d.5\n",k+k/2);
    }
    return 0;
}
```

------------

证明：若 $T_i > T_{i+1}$，由于 $T_{i+1}=k+ \dfrac{T_i}{i+1}$，$T_{i+2}=k+ \dfrac{T_{i+1}}{i+2}$，那么 $T_{i+2}-T_{i+1}=\dfrac{T_{i+1}}{i+2}- \dfrac{T_i}{i+1}<0$，因为 $\dfrac{T_{i+1}}{i+2}$ 的分母更大，分子更小。

因为 $T_{i+2}-T_{i+1}<0$，所以 $T_{i+1}>T_{i+2}$，又因为 $T_{i+1}>T_{i+2}$ 所以 $T_{i+2}>T_{i+3}$。以此类推，只要存在 $T_i > T_{i+1}$，那么对于所有大于 $i$ 的整数 $j$ 都有 $T_i > T_j$，又因为 $T_3 > T_4$，所以序列 $T$ 的最大值只可能在 $T_1,T_2,T_3$ 中取到，可知序列 $T$ 的最大值为 $T_2=T_3=1.5k$。

---

## 作者：Pink_Cut_Tree (赞：3)

# P10781 【MX-J1-T1】『FLA - III』Spectral 题解

### 解析

对于前 $4$ 个测试点，直接暴力模拟即可，这里不再赘述。

对于测试点 $5$，我们需要找些规律。

发现 $i$ 与 $T_i$ 的关系：

| $i$ | $0$ |$1$|$2$|$3$|$4$|$5$
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $T_i$ | $0$ |$k$|$1.5k$|$1.5k$|$1.375k$|$1.25k$

联系测试点 $1\sim 4$ 的暴力数据，似乎数列 $\left \{ T_n \right \} %$ 满足 $T_3>T_4>T_5>\dots$，真的是这样吗？

先亮结论：是的！证明如下：

$T_{i+1}-T_i\\=(k+\frac{T_i}{i+1})-(k+\frac{T_{i-1}}{i})\\=\frac{T_i}{i+1}-\frac{T_{i-1}}{i}\\=\frac{T_i\times i-T_{i-1}\times (i+1)}{(i+1)i}<0$。

易知对于 $i=4$，显然成立（$T_3>T_4,3<4$）。

$\therefore T_4>T_5$，由此可以推得 $T_5>T_6$。

……

得出结论，对于 $\forall i\geq 3,T_i>T_{i+1}$。

于是  $\left \{ T_n \right \}_{\max} =T_2=T_3=1.5k$。

$ans=\left\{\begin{matrix}
 k & n=1\\
 k+\frac{k}{2} & \text{otherwise }
\end{matrix}\right.$

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
double k;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cout<<setiosflags(ios::fixed)<<setprecision(1);
	cin>>T;
	while(T--){
		cin>>n>>k;
		if(n==1){
			cout<<k<<"\n";
		}
		else{
			cout<<double(k+k/2)<<"\n";
		}
	}
return 0;
}
```

记得开 `double` 哦。

---

## 作者：xuduang (赞：1)

这里给出一种更易理解的做法。

### 分析

要求最值，先看它的变化趋势。

我们可以这样理解，每次都只会加上 $k$，但是除的数变大，即减的数变多，我们可以大概推测出最大值应该在前面，不会遍历太远。

因为一开始是 $0$，所以是先向上走，由上可知，又综上所述，这是单峰的。

所以我们可以确定一件事，当 $T_{i+1}$ 比 $T_{i}$ 要小时，$T_i$ 就是最大值了，再往下就会往下走。

使用 `for` 模拟一下即可。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <string.h>
#include <queue>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--)
	{
		int n, k;
		cin >> n >> k;
		double ans = 0;//即Ti 
		double mx = 0;//最大值 
		for(int i = 1; i <= n; i++)//模拟 
		{
			ans = k + ans / i;//见题目 
			if(mx > ans) break;//往下走了 
			mx = ans;//一开始会往上走
		}
		printf("%.1lf\n", mx);
	}
	return 0;
}
```

---

## 作者：letianJOE (赞：1)

# P10781的题解

## 结论

$$ans_{n,k} = \begin{cases} k & n = 1 \\ \frac{3}{2}k & n \neq 1 \end{cases}$$

## 推导&证明

我们可以先写出 $T_i$ 前几项找一找规律。

$$T_1=k+\frac{T_0}{1}=k+\frac{0}{1}=k$$

$$T_2=k+\frac{T_1}{2}=k+\frac{k}{2}=\frac{3}{2}k$$

$$T_3=k+\frac{T_2}{3}=k+\frac{\frac{3}{2}k}{3}=\frac{3}{2}k$$

$$T_4=k+\frac{T_3}{4}=k+\frac{\frac{3}{2}k}{4}=\frac{11}{8}k$$

如果继续往下推得话，我们发现答案会越来越小。

所以答案只能是 $T_2$ 或 $T_3$，也就是 $\frac{3}{2}k$，记得特判 $n=1$ 的情况。

### 证明

首先我们把式子分为两部分，第一部分的 $k$ 是定值，那么对于答案我们只需要看后面的分数。

这个分数的分母会随 $T_i$ 的 $i$ 变大而变大，所以在第四次答案变小了。

那么对于分子，我们用的是上一次变小的答案。

分子变小，分母变大，在加上一个定值，所以答案永远不会大于 $\frac{3}{2}k$。

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main()
{
	int t;
	cin>>t;
	while(t--)
	{
		double n,k;
		cin>>n>>k;
		if(n==1)
		{
			printf("%.1lf\n",k);
			continue;
		}
		printf("%.1lf\n",k*1.0*1.5);
	}
	return 0;
} 
```

---

## 作者：Link_Cut_Y (赞：1)

首先我们做出一个很高明的观察，就是添 $> 2$ 块炭一定不会更优，填 $2$ 块炭一定最优。

我们可以先来简单验证一下这个观点。$T_1 = k$。我们暴力往下算一下，$T_2 = \dfrac{3}{2}k, T_3 = \dfrac{3}{2} k, T_4 = \dfrac{11}{8}k, T_5 = \dfrac{51}{40}k$。由于 $k > 0$，所以这个东西在目前看来是越变越小的。所以我们果断猜想第二块炭一定取得最优值。

我们来证明一下。我们用 $T_i$ 减去 $T_{i - 1}$，如果大于 $0$ 就更优，否则就不优，这里应该没有什么问题。

将 $T_i = \dfrac{T_{i - 1}}{i} + k$ 带进去，就可以得到方程：

$$\dfrac{T_{i - 1}}{i} - T_{i - 1} + k > 0$$

移项并且解方程，得到 $T_{i - 1} < \dfrac{i}{i - 1}k$。

我们容易得到 $T_1 = k$。对于 $T_2$，我们发现 $T_1 > \dfrac{2}{2 - 1}k$，就说明 $T_2 > T_1$，我们可以求出来 $T_2 = \dfrac{3}{2}k$。接下来我们发现 $T_2 = \dfrac{3}{2} k$，所以 $T_3$ 一定不优，并且等于 $T_2$。以此类推。

当然这个证明是不严谨的。比较严格的证明可以利用生成函数，然后做微分方程。这里不赘述了，或者我写一下扔到剪贴板里。

```cpp
read(T);
while (T -- ) {
	int n, k; read(n, k);
	if (n == 1) printf("%.1lf\n", (double)k);
	else printf("%.1lf\n", 1.50 * (double)k);
} return 0;
```

---

## 作者：FurippuWRY (赞：1)

注意到 $n\in[1,10^9]$，那么跑递归肯定会炸，可以针对递归式进行推导：

$$
\begin{cases}
T_0=0 \\
T_1=k+\frac{T_0}{1}=k \\
T_2=k+\frac{T_1}{2}=\frac{3}{2}k \\
T_3=k+\frac{T_2}{3}=\frac{3}{2}k\\
T_4=k+\frac{T_3}{4}=\frac{11}{8}k\\
T_5=k+\frac{T_4}{5}=\frac{51}{40}k\\
...
\end{cases}
$$

可以发现，随着 $n$ 的增大，$T_n$ 先增后减，且在 $n=2$ 或 $3$ 时取到最大值，根据题意，$n=1$ 时最大值为 $k$，那么判断 $n$ 是否等于 $1$，若等于输出 $k$，否则输出 $\dfrac{3}{2}k$ 即可。

接下来对 $T_i>T_{i+1}(i\ge3)$ 进行证明。

证明：  
假设
$$T_i>T_{i+1}$$
那么有

$$
\begin{aligned}
T_{i+1}&=k+\dfrac{T_i}{i+1}\\
T_{i+2}&=k+\dfrac{T_{i+1}}{i+2}\\
\end{aligned}
$$

$$
\begin{aligned}
T_{i+1}-T_{i+2}&=k+\dfrac{T_i}{i+1}-k-\dfrac{T_{i+1}}{i+2}\\
&=\dfrac{T_i}{i+1}-\dfrac{T_{i+1}}{i+2}\\
\end{aligned}
$$


因为 $T_i>T_{i+1},i+1<i+2$，所以

$$
\begin{aligned}
\dfrac{T_i}{i+1}-\dfrac{T_{i+1}}{i+2}&>0\\
\dfrac{T_i}{i+1}&>\dfrac{T_{i+1}}{i+2}\\
T_{i+1}&>T_{i+2}
\end{aligned}
$$

假设此时 $i=3$，那么

$$
\dfrac{11}{8}k>\dfrac{50}{41}k
$$

不等式成立。我们可以从上式进行递推，因为

$$
T_{i}>T_{i+1}
$$

与

$$
T_{i+1}>T_{i+2}
$$

成立，那么对于 $\forall j\in[0,+\infty)$

$$
T_{i+j}>T_{i+j+1}
$$

也同样成立。综上，可以得出结论

$$
\max(T_n)=
\dfrac32k
$$

------------


```cpp
#include <cstdio>
int t, k, n;
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &k);
		printf("%.1lf\n", (n == 1 ? k : 1.5 * k));
	}
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

赛时用实时更新最大值并判断的方法通过了此题，现在证明一下这个算法的时间复杂度。

首先，我们可以将 $T_1 \sim T_n$ 都表示为 $(1 + \frac{p}{q})k$ 的形式，$T_1$ 显然是 $k$，$T_2$ 通过推导可得 $(1 + \frac{1}{2})k = \frac{3}{2}k$。随着 $i$ 的增加，$q$ 也随之增加，那么 $T_i$ 也会变得越来越小。对于 $i$ 在 $2 \sim n$ 中的 $T_i$，我们就有 $T_2 \ge T_3 \ge T_4 \ge T_5 \ge \ldots \ge T_n$，实际上从 $T_3$ 开始就已经满足严格单调递减了，所以这个算法最多会执行 $3$ 次，时间复杂度显然是 $O(1)$。

参考代码如下：

```cpp
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#define ll long long
#define writes(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n');
static char buf[100000], * pa(buf), * pb(buf);
int st[114], top;
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
void debug(auto st, auto ed, bool endline) {
	for (auto it = st; it != ed; ++it) {
		cout << *it << " ";
	}
	if (endline) cout << '\n';
}
template <typename T> void read(T& x) {
	T t = 0, sgn = 1;
	char ch = gc;
	while (!isdigit(ch)) {
		if (ch == '-') sgn = -sgn;
		ch = gc;
	}
	while (isdigit(ch)) {
		t = (t << 3) + (t << 1) + (ch ^ 48);
		ch = gc;
	}
	x = sgn * t;
}
template <typename T, typename ...Args> void read(T& tmp, Args &...tmps) {
	read(tmp); read(tmps...);
}
template <typename T> void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	top = 0;
	while (x) {
		st[++top] = x % 10;
		x /= 10;
	}
	do {
		putchar(st[top--] + '0');
	} while (top > 0);
}
template <typename T, typename ...Args> void write(T& tmp, Args &...tmps) {
	writes(tmp);
	writes(tmps...);
}
template <typename T> T rand(T l, T r) {
	return rnd() % (r - l + 1) + l;
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--) {
		ll n, k;
		cin >> n >> k;
		double ans = 0.0;
		double mxn = 0.0;
		for (int i = 1; i <= n; i++) {
			ans = (1.0 * k + 1.0 * ans / i);
			if (ans > mxn) {
				mxn = ans;
			}
			else break;
		}
		cout << fixed << setprecision(1) << mxn << '\n';
	}
}
```

---

## 作者：donnieguo (赞：0)

## 分析

显然直接暴力是不能得满分的，考虑优化。

其实我们可以把 $T_i$ 的前几项都写出来，分析一下。

$$T_1 = k + 0 = k \\ T_2 = k + \dfrac{k}{2} \\ T_3 = k + \dfrac{k+\dfrac{k}{2}}{3} = k + \dfrac{k}{2}$$

从上面的分析，我们不难看出，$T_2$ 和 $T_3$ 的值都是相同的，而之后的 $T$ 一定不会比 $T_2$ 和 $T_3$ 更优，因为

$$T_4 = k + \dfrac{k+\dfrac{k}{2}}{4}$$

一定比 $T_2$ 和 $T_3$ 小，之后的 $T_i$ 也是同理。

所以我们得出结论：

$$\max(T_i)=\begin{cases}k \quad i=1\\ k+\dfrac{k}{2} \quad i \ge 2\end{cases}$$

## AC代码

```cpp
#include <iostream>
using namespace std;

int T, n, k;

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &k);
		if (n == 1) {
			printf("%.1lf\n", k * 1.0);
			continue;
		}
		printf("%.1lf\n", k * 1.5);
	}
	return 0;
}
```

---

## 作者：TPJX (赞：0)

### 简要分析
题目给出的温度变化公式是一个递推形式：

$$T_i = \begin{cases} 0 & i = 0 \\ k+ \dfrac{T_{i-1}}{i} & i \neq 0 \end{cases}$$

这里，当我们计算第 $i$ 块炭燃烧之后的火焰温度 $T_i$ 时，温度依赖于上一次的温度 $T_{i-1}$，并加上一个递减的比例 $\frac{T_{i - 1}}{i}$。这表明，每增加一块炭，温度的增加逐渐减少

### 解题思路

#### 非满分做法

直接通过递推公式迭代计算最后一块炭的温度 $T_n$。

先设 $T_0 = 0$，然后从 $i = 1$ 到 $n$，使用公式 $T_i = k + \frac{T_i - 1}{i}$ 更新温度。计算完所有炭块后，$T_n$ 即为所求的最高温度。

以上方法对于规模较小的 $n$ 可行，但对于非常大的 $n$（例如 $10^9$），需进行优化或找到近似方法。

#### 优化至 100 分

- 由于每次计算只依赖前一次结果，空间复杂度可以优化到 $O(1)$。
- 时间复杂度理论上是 $O(n)$，但对于非常大的 $n$，计算 $n$ 次可能不现实。
- 注意到当 $i$ 非常大时，$\frac{T_{i-1}}{i}$ 变得非常小，因此在某一点后，$T_i$ 增长将变得非常缓慢。可以考虑在实现时设置一个阈值，当温度变化非常小的时候停止计算。

### Python 实现

```python
def calc(n, k):
    pre = 0
    for i in range(1, n + 1):
        cur = k + pre / i
        if abs(cur - pre) < 1e-6:  # 一个合理的阈值来减少不必要的计算
            break
        pre = cur
    return round(cur, 1)

import sys
input = sys.stdin.read
data = input().split()
T = int(data[0])
idx = 1
res = []
for _ in range(T):
    n = int(data[idx])
    k = int(data[idx+1])
    idx += 2
    ans = calc(n, k)
    res.append(f"{ans:.1f}")

print("\n".join(res));

```

### C++ 实现

```cpp
#include <bits/stdc++.h>
using namespace std;

double calc(int n, long long k) {
    double pre = 0.0, cur = 0.0;
    for (int i = 1; i <= n; ++i) {
        cur = k + pre / i;
        if (abs(cur - pre) < 1e-6) break;
        pre = cur;
    }
    return cur;
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        int n; long long k;
        cin >> n >> k;
        double ans = calc(n, k);
        printf("%.1lf\n",ans);
    }
    return 0;
}
```

在这两个实现中，我们用一个阈值来优化计算过程，减少了在 $n$ 特别大时的计算量，使其在实际情况下能够较快运行。对于极端大数据的情况，可能需要更复杂的数学分析或优化策略。

---

## 作者：Bc2_ChickenDreamer (赞：0)

## P10781

### Sol

我们一开始拿到题目先可以通过推导来发现答案，我们可以推导每个 $T_i$：

+ $T_1 = k$
+ $T_2 = k + \frac{1}{2} \cdot T_1 = 1.5k$
+ $T_3 = k + \frac{1}{3} \cdot T_2 = 1.5k$
+ $T_4 = k + \frac{1}{4} \cdot T_3 = 1.375k$
+ $T_5 = k + \frac{1}{5} \cdot T_4 = 1.275k$
+ $T_6 = k + \frac{1}{6} \cdot T_5 = 1.2125k$

渐渐的，你会发现 $T_n$ 的 $n$ 越大，值就越小，最后无限趋近于 $1$。

所以说，整个 $T$ 的最大值为 $T_2, T_3$ 的 $1.5k$。所以得出结论，只要 $n \ge 2$ 输出 $1.5k$，$n = 1$ 输出 $k$。

为什么呢？本来 $\cfrac{1}{i}$ 的值会越来越小，而从 $T_4$ 开始 $T_{i - 1}$ 的值也随着 $i$ 一直变小，所以就会越算越小。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
 
using namespace std;
 
using ll = long long;
 
const int kMaxN = 25250, kInf = (((1 << 30) - 1) << 1) + 1, kMod = 998244353;
const ll kLInf = 9.22e18;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    ll n, k;
    cin >> n >> k;
    if (n == 1) {
      cout << k << ".0" << '\n';
    } else {
      cout << fixed << setprecision(1) << 1.5 * k << '\n';
    }
  }
  return 0;
}
```

---

## 作者：封禁用户 (赞：0)

本题的主要思路就是数学。

首先，让我们先来打一个表。

| $i$ | $1$ | $2$ | $3$ | $4$ | $\dots$ | 
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $T_{i}$ | $k$ | $1.5k$ | $1.5k$ | $1.375k$ | $\dots$ |

易用肉眼看见，自 $T_{3}$ 之后数越来越小，于是我们大胆猜测，若 $n\ne1$，则它的最大值是 $1.5k$ 否则 $k$。

想到这里，其实就可以通过这道题啦。

不过这只是猜测，证明过程有一些复杂。

$T_{i+1}-T_{i}=k+\frac{T_{i}}{i+1}-T_{i}=\frac{T_{i}}{i+1}-\frac{(i+1)T_{i}}{i+1}=-\frac{iT_{i}}{i+1}$

因为 $-\frac{iT_{i}}{i+1}$ 一定小于零，所以 $T_{i+1}$ 一定小于 $T_{i}$，但从打表中可以看出 $T_{2}$ 和 $T_{3}$  是例外，所以结论与猜测的一样。若 $n\ne1$，则它的最大值是 $1.5k$ 否则 $k$。

### AC Code
```
#include<iostream>
#include<cstring>
#define ll long long 
using namespace std;
int t, n, k, a;
int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		if(n==1){
			printf("%.1lf\n",k*1.0);
		}else{
			printf("%.1lf\n",k*1.5);
		}
	}
	return 0;
}
```

---

