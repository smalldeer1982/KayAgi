# Helping the Nature

## 题目描述

Little Leon lives in the forest. He has recently noticed that some trees near his favourite path are withering, while the other ones are overhydrated so he decided to learn how to control the level of the soil moisture to save the trees.

There are $ n $ trees growing near the path, the current levels of moisture of each tree are denoted by the array $ a_1, a_2, \dots, a_n $ . Leon has learned three abilities which will help him to dry and water the soil.

- Choose a position $ i $ and decrease the level of moisture of the trees $ 1, 2, \dots, i $ by $ 1 $ .
- Choose a position $ i $ and decrease the level of moisture of the trees $ i, i + 1, \dots, n $ by $ 1 $ .
- Increase the level of moisture of all trees by $ 1 $ .

Leon wants to know the minimum number of actions he needs to perform to make the moisture of each tree equal to $ 0 $ .

## 说明/提示

In the first test case it's enough to apply the operation of adding $ 1 $ to the whole array $ 2 $ times.

In the second test case you can apply the operation of decreasing $ 4 $ times on the prefix of length $ 3 $ and get an array $ 6, 0, 3 $ .

After that apply the operation of decreasing $ 6 $ times on the prefix of length $ 1 $ and $ 3 $ times on the suffix of length $ 1 $ . In total, the number of actions will be $ 4 + 6 + 3 = 13 $ . It can be shown that it's impossible to perform less actions to get the required array, so the answer is $ 13 $ .

## 样例 #1

### 输入

```
4
3
-2 -2 -2
3
10 4 7
4
4 -4 4 -4
5
1 -2 3 -4 5```

### 输出

```
2
13
36
33```

# 题解

## 作者：linyihdfj (赞：12)

## C.Helping the Nature ##
### 题目描述 ###
给定一个 $n$ 个数的序列 $a$，你可以选择进行下面三种操作：

1. 任选一个 $i$，使 $a_1,a_2,a_3,\cdots ,a_{i}$ 减一
2. 任选一个 $i$，使 $a_i,a_{i+1},\cdots,a_n$ 减一
3. 使 $a_1,a_2,a_3,\cdots,a_{n}$ 加一

请问经过**最少**多少次操作后可以使得序列 $a$ 中的每个数都变成 $0$.

### 题目分析 ###
我们考虑我们是怎么使得整个序列的数都变成 $0$，很明显只有是将序列中的所有数都变成同一个数，然后同时加或减某一个数之后才能做到。或者将序列的中间变成 $0$，将序列的左右部分分别变成同一个数，但是这样跟原问题有啥区别吗，还变得更加复杂了，所以就果断弃掉这个思路。考虑如何操作使得区间中的所有数都变成同一个数。

我们考虑如果对原序列做差分，那么我们最终的答案就是差分序列所有的值为 $0$ 时，序列中的所有的数是同一个数。

我们会发现一个很神奇的事情：我们对于一个前缀/后缀整体减一，只会对一个位置的差分值产生影响，加一或减一，那么就利用这个性质一点一点将差分数组变成 $0$ 就可以了。

注意：这只是将整个序列都变成同一个数，还需要将所有的数都变成 $0$，这一步不能忘记了。 

### 代码详解 ###
```
#include<bits/stdc++.h>
using namespace std;
const long long MAXN = 2e5+5;
long long a[MAXN];
int main(){
	long long t;
	cin>>t; 
	while(t--){
		long long n,ans = 0;
		cin>>n;
		for(long long i=1; i<=n; i++){
			cin>>a[i];
		}
		long long h = a[1];
		for(long long i=2; i<=n; i++){
			long long b = a[i-1] - a[i]; 
			ans += abs(b);
			if(b > 0)
				h -= b;
		}
		ans += abs(h);
		printf("%lld\n",ans);
	}
	return 0;
}

```

对于一个差分后的值 $x$，因为每一次操作都只能加一或减一，所以也就是 $|x|$ 次操作后能变成 $0$。我的代码里维护的 $h$ 值即差分序列全部变成 $0$ 之后，原序列中的这个数是多少。

---

## 作者：Phartial (赞：3)

## 题意简述

给你一个长为 $n$ 的序列 $a_i$，每次你可以执行如下操作的其中一个：

1. 将序列里的前 $i$ 个数同时减 $1$。
1. 将序列里的后 $i$ 个数同时减 $1$。
1. 将序列里的全部数同时加 $1$。

问最少要多少次操作才可以把序列里的数都变成 $0$。

## 思路

遇到这种可以区间加减的题目我们可以先考虑差分原序列，这样就可以把区间加减转化成单点加减。

差分之后可以发现原来的操作会变成如下几种：（$b_i$ 是 $a_i$ 的差分序列，特别的，定义 $b_{n+1}$ 为 $-a_n$）

1. 将 $b_1$ 减一，同时将 $b_i$ 加一。
1. 将 $b_i$ 减一，同时将 $b_{n+1}$ 加一。
1. 将 $b_1$ 加一，同时将 $b_{n+1}$ 减一。

（可以注意到目标仍然是让 $b_i$ 里的数都为 $0$。）

发现 $b_i$ 之间都是相互独立的，所以可以直接看 $b_i$ 是正数还是负数，正数就执行 $b_i$ 次操作 $2$，负数就执行 $-b_i$ 次操作 $1$，最后看一下要多少次操作 $3$ 即可。

注意 $b_1>0$ 时需要额外执行 $b_1$ 次操作二。

## 代码

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 2;

int t, n;
LL ans, b[kN], p;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    p = ans = 0;
    for (int i = 1, x; i <= n; ++i) {
      cin >> x;
      b[i] = x - p, p = x;  // 计算差分序列
    }
    b[n + 1] = -p;                      // b[n + 1] = -a[n]
    for (int i = 2; i <= n; ++i) {      // 考虑每个数
      if (b[i] > 0) {                   // 如果是正数
        b[n + 1] += b[i], ans += b[i];  // 执行 b[i] 次操作二
      } else if (b[i] < 0) {            // 如果是负数
        b[1] += b[i], ans -= b[i];      // 执行 -b[i] 次操作一
      }
      b[i] = 0;
    }
    if (b[1] > 0) {  // 如果 b[1] > 0
      b[n + 1] += b[1], ans += b[1], b[1] = 0;
    }
    cout << ans - b[1] << '\n';  // 统计要进行多少次操作三
  }
  return 0;
}
```

---

## 作者：郑朝曦zzx (赞：2)

# 一 解题思路

用一个变量 $a$ 来记录把所有树统一成**同一个高度**时所需的操作次数。

当我们遇到一棵树高为 $h$ 的树的时候，有以下两种可能的情况：

- 如果 $h \le a$ 那么把前面的树操作 $h - a$ 次使高度统一。

- 否则把在这棵树上操作 $a - h$ 次把它的高度将为 $a$。

我们发现在两种情况下我们都要操作 $|h - a|$ 次，最后不要忘记给答案再加上 $|a|$ 次操作使得所有树的高度都变为 $\mathrm{0}$。
# 二 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, x, y;
long long a, ans;
int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d %d", &n, &x);
		a = x; ans = 0;
		for (int i = 2; i <= n; ++i, x = y)
		{
			scanf("%d", &y);
			ans += abs(x - y);
			if (x > y) a += (y - x);
		}
		ans += abs(a);
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：Galois_Field_1048576 (赞：1)

考虑进行差分。  
可以变成如下三种操作：  
- $d_1$ 自减的同时 $d_i$ 自增
- $d_i$ 自减
- $d_1$ 自增

目标 $\forall i \in [1, n], d_i=0$。  
首先考虑如果 $\forall i \in [2, n], d_i=0$，那么可以执行 $|d_1|$ 次 $2$ 或 $3$ 操作。  
于是我们就对于每一个 $2 \sim n$ 的 $i$，都可以使用 $1$ 或 $2$ 操作（取决于 $d_i$ 的符号）来转换到 $d_1$。将答案再加上 $d_1$ 即可。  
上伪代码（使用 $\KaTeX$ 排版）：  
$
\begin{array}{l}
\textbf{input}~T \\
\textbf{for}~w=[1,T] \\
\qquad\textbf{input}~n,a_i \\
\qquad\textbf{for}~i=[1,n]\\
\qquad\qquad d_i\gets a_i-a_{i-1}\\
\qquad p \gets 0 \\
\qquad\textbf{for}~i=[2,n]\\
\qquad\qquad \textbf{if}~d_i<0 \\
\qquad\qquad\qquad p \overset-\gets a_i \\
\qquad\qquad\qquad a_1 \overset+\gets a_i \\
\qquad\qquad\textbf{else} \\
\qquad\qquad\qquad p \overset+\gets a_i \\
\qquad\textbf{output}~p+|a_1|
\end{array}
$

---

## 作者：清烛 (赞：1)

拿到题目，对于这种总体 +/- 的操作，第一时间考虑差分数组（令其为 $d$，$d_i = a_i - a_{i-1}$），然后三种操作可以分别被转化为：

- $d_1\leftarrow d_1 - 1$，$d_{i+1}\leftarrow d_{i+1} + 1$；
- $d_i\leftarrow d_i - 1$；
- $d_1\leftarrow d_1 + 1$。

而最后我们需要 $a_i$ 全部为 $0$，其等价于所有的 $d_i$ 全部为 $0$。

发现在这所有操作中 $d_1$ 的特殊性，所以我们先考虑让 $i\ge 2$ 的 $d_i$ 先清零。

具体的，对于 $<0$ 的 $d_i$，我们可以用 $|d_i|$ 次 $1$ 操作让 $d_1\leftarrow d_1 - |d_i|$ 的同时清零 $d_i$。然后对于 $>0$ 的 $d_i$，可以用 $d_i$ 次二操作将其赋为 $0$。

现在只剩下 $d_1$，分情况使用 $|d_1|$ 次 $2$ 操作或者 $3$ 操作即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
int n;
ll a[maxn], d[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i], d[i] = a[i] - a[i - 1];
        ll tmp = 0, ans = 0;
        FOR(i, 2, n) {
            if (d[i] < 0) tmp += -d[i];
            else ans += d[i];
        }
        ans += tmp;
        if (tmp > d[1]) ans += tmp - d[1];
        else ans += d[1] - tmp;
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1Fv4y137u9)

### 2 思路

首先将所有数字变成一样的，然后进行整体相加减到 $0$ 即可。

我们一个一个枚举。

如果 $a[i]>a[i+1]$，那么肯定要将 $1$ 到 $i$ 减去 $(a[i]-a[i+1])$；否则将 $(i+1)$ 到 $n$ 减去 $(a[i+1]-a[i])$。

然后我们统计一下这些操作之后 $a$ 数组的数字是多少，进行整体相加减操作即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define max_n 200000
int t;
int n;
long long a[max_n+2];
__int128 x;
__int128 mina;
__int128 ans;
void pr(__int128 x){
	if(!x)return;
	pr(x/10);
	putchar(x%10+'0');
}
__int128 absint128(__int128 x){
	if(x>=0)return x;
	return -x;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1700C_1.in","r",stdin);
	freopen("CF1700C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%lld",a+i);
		x=0;
		for(int i=1;i<n;++i){
			if(a[i]>a[i+1])x+=(a[i]-a[i+1])*(long long)i;
			else x+=(a[i+1]-a[i])*(long long)(n-i);
		}
		mina=a[1];
		for(int i=2;i<=n;++i){
			if(a[i]<mina)mina=a[i];
		}
		for(int i=1;i<=n;++i)x-=(a[i]-mina);
		ans=absint128(mina-x/n);
		for(int i=1;i<n;++i)ans+=abs(a[i]-a[i+1]);
		if(ans==0)putchar('0');
		else pr(ans);
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/77692712)

By **dengziyue**

---

