# Squeezing Slimes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2017-quala/tasks/code_festival_2017_quala_f

$ A $ 匹のスライムが横一列に並んでいます。 最初、スライムの大きさはすべて $ 1 $ です。

すぬけ君は次の操作を繰り返し行うことができます。

- 正の偶数 $ M $ をひとつ選ぶ。 位置が連続する $ M $ 匹のスライムを選び、それらのうち左から $ (1,\ 2) $ 番目、$ (3,\ 4) $ 番目、…、$ (M\ -\ 1,\ M) $ 番目のスライムをそれぞれペアにする。 そして、各ペアごとに $ 2 $ 匹のスライムを合成して $ 1 $ 匹のスライムにする。 ここで、合成後のスライムの大きさは、合成前のスライムの大きさの和とする。 また、合成後の $ M\ /\ 2 $ 匹のスライムの順序は、合成前の $ M\ /\ 2 $ 組のペアの順序のままである。

すぬけ君の目標は、スライムをちょうど $ N $ 匹にして、それらのうち左から $ i $ ($ 1\ <\ =\ i\ <\ =\ N $) 番目のスライムの大きさをちょうど $ a_i $ にすることです。 すぬけ君が目標を達成するために必要な操作回数の最小値を求めてください。

なお、$ A $ は入力として与えられず、$ A\ =\ a_1\ +\ a_2\ +\ ...\ +\ a_N $ であるとします。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 10^5 $
- $ a_i $ は整数である。
- $ 1\ <\ =\ a_i\ <\ =\ 10^9 $

### Sample Explanation 1

次のように操作を行えばよいです。 操作対象のスライムを太字で表しています。 - (1, \*\*1\*\*, \*\*1\*\*, \*\*1\*\*, \*\*1\*\*, 1) → (1, \*\*2\*\*, \*\*2\*\*, 1) - (\*\*1\*\*, \*\*2\*\*, \*\*2\*\*, \*\*1\*\*) → (\*\*3\*\*, \*\*3\*\*)

### Sample Explanation 2

次のように操作を行えばよいです。 - (\*\*1\*\*, \*\*1\*\*, 1, 1, 1, 1, 1) → (\*\*2\*\*, 1, 1, 1, 1, 1) - (2, 1, \*\*1\*\*, \*\*1\*\*, \*\*1\*\*, \*\*1\*\*) → (2, 1, \*\*2\*\*, \*\*2\*\*)

## 样例 #1

### 输入

```
2
3 3```

### 输出

```
2```

## 样例 #2

### 输入

```
4
2 1 2 2```

### 输出

```
2```

## 样例 #3

### 输入

```
1
1```

### 输出

```
0```

## 样例 #4

### 输入

```
10
3 1 4 1 5 9 2 6 5 3```

### 输出

```
10```

# 题解

## 作者：Labelray (赞：2)

这个合并的过程很像线段树维护区间和时的 `push_up` 的过程，所以对于一个数$x$，就可以将它当做一棵线段树整个的和来考虑，那么这个线段树维护的区间中每个数都是$1$，最少合并次数就是这棵树的树高$\log_2{x}$

这样就可以求出来一个序列$d_i=$合并出$a_i$最少的操作次数

对于一个$d_i$序列，如$2, 3, 5, 1, 0, 2, 4, 3$，对答案做出贡献的其实只有$5, 4$这两个画出折线图的话在顶峰的数，这样就可以很容易的求出答案了，记得考虑一下这棵树满不满，如果不满的话在下降序列中需要先减1再和之后的数比较

```
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int N, a, qwq, now, ans;

int main(){
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		scanf("%d", &qwq);
		a=log2(qwq);
		if((1<<a)<qwq){
			if(now>a)	now=a;
			else		a++;
			
		}
		if(a>now)	ans+=a-now, now=a;
		if(a<now)	now=a;
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：DJRzjl (赞：1)

考虑合并一个体积为 $w$ 的史莱姆，合并过程类似一颗线段树，答案为线段树的层数 $\lceil\log_2w \rceil$。

那么合并这 $n$ 个史莱姆的答案上界就是 $lim=\sum_{i=1}^n\lceil \log_2a_i\rceil$。

显然在很多情况下我们可以通过对相邻的史莱姆一起操作来使答案更小。

考虑把第 $i$ 个史莱姆合成时对应的线段树的左，右深度记做 $l_i,r_i$。

答案即为 $lim-\sum_{i=2}^n \min(r_{i-1},l_i)$。

对于一个二的幂，$l_i,r_i$ 都等于 $\log_2a_i$。

否则 $l_i,r_i$ 中有一个 $\lfloor \log_2a_i \rfloor$，另一个为 $\lfloor \log_2a_i\rfloor+1$。

设计一个 $f_{i,0/1}$ 简单 dp 即可。

#### [Code](https://atcoder.jp/contests/code-festival-2017-quala/submissions/36174268)

---

## 作者：Jsxts_ (赞：0)

提供另一个角度（可能更易于理解）的思路。

首先将操作逆序，即每次将一个区间的数都分成两个数。

我们从左到右贪心地考虑，发现一个 $i$ 最多要 $\lceil\log_2a_i\rceil$ 次操作（记为 $b_i$）。那么是否可以和它左边的操作合并以减少次数呢？

容易发现一个数只有两种可能会优的分解策略：每一次分解时都使得分解出的数升序或降序。如 $7\to 4,3\to2,2,2,1\to1,1,1,1,1,1,1$ 或 $7 \to 3,4\to 1,2,2,2\to1,1,1,1,1,1,1,1$。

那么当 $i$ 往 $i-1$ 合并时，容易发现当 $i-1$ 使用第一种策略时会使可以一起分解的次数减少 $1$。所以我们尽可能使用第二种。

但是当 $b_{i-1}\ge b_i$ 且 $a_i$ 不为 $2$ 的幂时，$i$ 使用第二种就会使一起分解次数减 $1$（会被自己分解出来的 $1$ 隔开）。此时显然用第一种不会劣（就算后面次数少了也不劣）。所以这时我们使用第一种，并将 $lst$（代表上一个可以一起分解的次数）减一。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 1e5;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int main() {
	int n = read(),lst = 0;
	ll ans = 0;
	for (int i = 1;i <= n;i ++ ) {
		int x = read(),t = ceil(log2(x));
		if ((1 << t) != x && lst >= t) t --;
		ans += max(0,t - lst), lst = t;
	}
	cout << ans;
	return 0;
}
```


---

## 作者：μηδσ (赞：0)

## Definition

~~这道题我开始读了半天~~

给出一个目标数列，看对初始序列进行多少次合并过后可以达到目标数数列

输入一个$N$表示目标数列的长度，

输入$a_1,a_2,a_3,a_4,\cdots,a_N$表示目标数列

其中初始数列的长度$A = \sum\limits_{i=1}^{N}a_i$

## Solution

对于每一个数进行考虑，他的操作次数最多为$\log_{2}{a_i}$

比如我要得到一个10，那么我可以进行如下操作

$\{1,1,1,1,1,1,1,1,1,1\}\rightarrow
\{2,2,2,2,2\}\rightarrow
\{4,4,2\}\rightarrow
\{8,2\}\rightarrow
\{10\}$

不过当数多起来的时候就会又很多的浪费，如果一个数十$2^n$那么无论进行多少次操作都没事，否则每一次操作只能是往左或者往右

然后贪心，从左往右，记录前面给了后面多少，多余的一次能往前就往前

思路已经非常清楚了，线面直接看代码

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

#define re register
#define rep(a, b, c) for(re long long a = b;a <= c;a++)
#define per(a, b, c) for(re long long a = b;a >= c;a--)

using namespace std;
const int MAXN = 100005;

int a[MAXN], b[MAXN], c[MAXN];
int n, res, lst, tmp;

int main(){
	scanf("%d",&n); 
	rep(i, 1, n){
		int x;
		scanf("%d",&x); 
		a[i] = x;
		b[i] = -1;
		while(a[i]){
			++b[i];
			a[i] >>= 1;
		}
		c[i] = ((x & -x) != x);
		res += b[i] + c[i];
	}
	rep(i,1,n){
		tmp = min(lst, b[i]);
		res -= tmp;
		lst -= tmp;
		if(lst && c[i]){
			--res;
			--c[i];
		}
		lst = b[i] + c[i];
	}
	printf("%d\n",res);
	return 0;
}
~~~

---

