# [ARC138A] Larger Score

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc138/tasks/arc138_a

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ があります． 以降この問題では，$ A $ の先頭 $ K $ 項の和を **スコア** と呼ぶことにします． また，入力で与えられた $ A $ のスコアを $ s $ と置くことにします．

あなたは，以下の操作を好きな回数繰り返すことができます．

- $ A $ のある隣接する $ 2 $ 要素を選び，それらの値を入れ替える．

あなたの目標は，スコアを $ s+1 $ 以上にすることです． 目標が達成可能であるかどうか判定し，また可能であるなら必要な最小の操作回数を求めてください．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 4\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N-1 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力される値はすべて整数

### Sample Explanation 1

まず，$ s=2+1=3 $ です． 以下のように操作することで，スコアを $ 4 $ 以上にすることができます． - $ (2,1,1,2)\ \to\ (A_3 $ と $ A_4 $ の値を入れ替える $ )\to\ (2,1,2,1)\ \to\ (A_2 $ と $ A_3 $ の値を入れ替える $ )\to\ (2,2,1,1) $ $ 1 $ 回の操作では目標を達成できないため，必要な最小の操作回数は $ 2 $ になります．

## 样例 #1

### 输入

```
4 2
2 1 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
3 1
3 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
20 13
90699850 344821203 373822335 437633059 534203117 523743511 568996900 694866636 683864672 836230375 751240939 942020833 865334948 142779837 22252499 197049878 303376519 366683358 545670804 580980054```

### 输出

```
13```

# 题解

## 作者：Fated_Shadow (赞：3)

# ARC138A Larger Score 题解

## 前言

[题目传送门](https://www.luogu.com.cn/problem/AT_arc138_a)，到[博客](https://www.luogu.com.cn/blog/622466/arc138a-larger-score-ti-xie)食用

@Split_shadow 特荐我此题，现记录题目（已知），贪心方法（求证）与思路（证明），附上暴力思路（代码解析）。

只能说是一道~~用数据结构~~或~~神奇二分~~的~~神仙~~ 贪心题

## 思路证明
### 已知
现存在一个长度为 $n$ 的数列 $a_{1},a_{2},a_{3},a_{4}\dots a_{n}$，给定数 $k$，求最少的交换次数 $times$ 使得交换后的数列 $b$ 中 $(\sum_{i=1}^{k}b_{i})>(\sum_{i=1}^{k}a_{i})$。

（规定交换为 $\operatorname{swap}(a_{i},a_{i+1})$，且 $(1\le i<n)$）。

### 求证
为使 $times$ 尽量小，则所有交换操作和并起来应该是一次不比较大小的冒泡操作（即在 $a_{1}$ 到 $a_{k}$ 中仍有 $k-1$ 个不考虑位置的数不变）。

### 证明

假设在 $times$ 最小时，前 $k$ 个数中变换后不变的数（不考虑位置）小于 $k-1$ 个，即变化的数大于 $2$ 个。

先就 $2$ 个的情况讨论。

设在前 $k$ 个数中 $a_{x},a_{y}$ 在冒泡操作后被替换为 $a_{m},a_{n}(1\le x,y\le k<m,n)$。

则有：$a_{x}+a_{y}<a_{m}+a_{n}$

不妨令 $a_{x}<a_{m}$（这个是一定存在的），且在 $a_{x},a_{y}$ 与 $a_{m},a_{n}$ 两组中，非同组元素互换时，$a_{x}$ 与 $a_{m}$ 互换冒泡所费次数最少。

则存在一种方案，使 $a_{x}$ 与 $a_{m}$ 互换冒泡符合题意，且比当前方案花费次数更优（如果要 $4$ 个元素互换，那么必然比 $2$ 个元素互换花费次数更多），与假设矛盾，则可以证得该结论。


至于变化的数更多的情况，依次推理即可证得。

## 实现解析

### 暴力（30.5 pts）

假令 $a_{x}$ 与 $a_{m}$ 交换冒泡，最小花费 $m-x$ 的次数。

那么便可枚举 $a_{i}(k+1\le i\le n)$，找的最大的 $j$ 使得 $a_{i}>a_{j}(1\le j\le k)$。

其中 $i$ 从小到大枚举，$j$ 则从大到小枚举。

然后在此等条件下，$ans=\min(i-j)$。

笔者现提供一种暴力优化~~wtcl 不会打正解~~：

枚举时，如果当前最优答案的 $i$ 为 $i_{0}$ 且 $p>i_{0},a_{i_{0}}\ge a_{p}$，则可以跳过 $p$ 寻找下一个 $i$。（$i$ 的含义与上同）。

同理，对于 $j$ 也可记录最优答案 $j_{0}$，则每次寻找下一个 $j$ 的范围为 $j_{0}<j\le k$。

理论上时间复杂度可从 $O(n^{2})$ 优化到 $O(m^{2})(0<m\le n)$。~~（然鹅好像没什么卵用）~~。

贴一下贪心暴力部分代码。
```
l = 0, r = n + 1;
for(int i = k + 1; i <= n; ++ i)
{
	if(a[r] >= a[i]) continue;
	for(int j = k; j > l; -- j)
	{
		if(i - j > ans) break;
		if(a[j] < a[i])
		{
			r = i, l = j;
			break;
		}
	}
	ans = r - l;
}
```

### 二分（100 pts）

不难发现，在寻找 $j$ 时，本质上是寻找最后一个比 $a_{i}$ 小的 $a_{j}$。

那么先求一遍 $a_{1}$ 到 $a_{k}$ 后缀最小值，我们发现，现在的后缀最小值满足单调性，那么就可以高高兴兴地套上二分来求最后一个满足条件地后缀最小值的位置了。


那么再用二分维护一下，期望 $O(n\log_{2}{n})$。

## AC代码

贴上 AC 链接：[link](https://www.luogu.com.cn/record/106181398)（跑得有点慢）

```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<string>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#define put putchar
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b
using namespace std;

const int N = 4e5 + 10;
const int INF = 1e9;
const int mod = 1e9 + 7;

int n, k;
int a[N];
int ans = INF, l, r;
int sum[N];

inline long long read(){
	long long res = 0, f = 1;
	char c = getchar();
	while(! isdigit(c)){
		if(c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) res = (res << 1) + (res << 3) + c - 48, c = getchar();
	return res * f;
}
inline void write(long long x){
	if(x >= 10) write(x / 10);
	put(x % 10 + 48);
	return ;
}
inline void print(long long x){
	if(x < 0) x = -x, put('-');
	write(x);
	return ;
}

int change(int x)
{
	if(sum[1] >= x) return 0;
	int l = 1, r = k, mid;
	int res;
	while(l <= r)
	{
		mid = l + r >> 1;
		if(sum[mid] >= x) r = mid - 1;
		else l = mid + 1, res = mid;
	}
	return res;
}

bool tp()
{
	if(n == k) return true;
	int mina = INF, maxa = -INF;
	for(int i = 1; i <= k; ++ i)
		mina = min(mina, a[i]);
	for(int i = k + 1; i <= n; ++ i)
		maxa = max(maxa, a[i]);
	if(maxa <= mina) return true;
	return false;
}

int main()
{
	memset(sum, 0x3f3f3f3f, sizeof sum);
	n = read(), k = read();
	for(int i = 1; i <= n; ++ i)
		a[i] = read();
	for(int i = k; i ; -- i)
		sum[i] = min(a[i], sum[i + 1]);
	if(tp())
	{
		print(-1);
		return 0;
	}
	int w;
	for(int i = k + 1; i <= n; ++ i)
	{
		w = change(a[i]);
		if(! w) continue;
		ans = min(ans, i - w);
	}
	print(ans);
	return 0;
}
```



## 后记

懒得想了，就只给出一种暴力优化与二分思路。

我觉得就以各位 dalao 的实力，应该能做出来更快做法。

（其实正解是二分，但是 Split_shadow 巨佬竟然用线段树过了？）

—— _Fated_Shadow_

---

## 作者：Alvin_Wang (赞：2)

## 题目分析

题目要求每次交换相邻的两个数，使得最后结果前 $k$ 个数大于原来的前 $k$ 个数。求最少的操作次数

简单分析一下题目，要求交换后前 $k$ 个的和变大，且操作次数最少。其实就是要在尽量少的次数内将前 $k$ 个中的一个数与后 $k$ 个中一个比它大的数交换。

## 如何实现

那么，要怎么实现呢？

最暴力的枚举方式，就是遍历前 $k$ 个数中的 $a_i$ 和后 $k$ 个数中的 $a_j$，使得 $a_i < a_j$ 且 $j -i$ 最小。时间复杂度是 $O(n^2)$ 的。

那现在就要思考怎么将这个复杂度降下来。

思考一下，再前 $k$ 个数里，如果两个数 $a_i < a_j$ 且 $i > j$ 那么 $a_i$ 肯定是比 $a_j$ 更优的，在选择数的时候是就不必选 $a_j$。

同理。后 $k$ 个数中，如果两个数 $a_i > a_j$ 且 $i < j$ 则 $a_i$ 肯定是比 $a_j$ 更优，在选择是就不必选 $a_j$。

这时，我们就想到了一个很好用的东西：单调队列

具体实现就看下面的代码啦

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, k, ans = INT_MAX;
int a[400005];
priority_queue<int, vector<int>, greater<int> > q;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i ++){
        cin >> a[i];
    }
    for(int i = k ; i >= 1 ; i --){
        if(q.empty() || a[i] < a[q.top()]){ // 将编号靠前，然而值更大的数抛弃掉
            q.push(i);
        }
    }
// 处理完之后，我们就得到了一个从前往后单调递增的数列
    for(int i = k + 1 ; i <= n ; i ++){
        while(!q.empty() && a[q.top()] < a[i]){ //如果满足条件，记录一下答案，并尝试往前尝试看能否可以更小
            ans = min(ans, i - q.top());
            q.pop();
        }
    }
    if(ans == INT_MAX){ // 没有记录过答案，说明后面的值都比原先前 k 个数小则无解
        cout << -1 << '\n';
    }
    else{
        cout << ans << '\n';
    }
    return 0;
}
```

这时蒟蒻的第一篇题解 qwq

如果有误欢迎指出谢谢大佬们 awa

---

## 作者：Bobi2014 (赞：2)

这题是一道~~可爱~~的二分。

首先，我们思考时间复杂度为 $O(n^2)$ 的朴素算法，我们可以枚举要被替换的数，再枚举替换成什么数，设替换的数位置为 $i$，举替换成什么数的位置为 $j$，那么就需要移动 $j - i$ 次。

然后我们发现时间复杂度为 $O(n^2)$ 的算法会超时，所以我们可以二分，但我们又发现这个序列不具有单调性，无法二分，这时我们可以定义一个 $va$ 与 $id$ 分别存储剩下 $n - m$ 个可以替换的数中最大的数与它的下标，这里的 $va$ 就拥有了单调递增性，我们就可以二分它，得到第一个满足 $> a_i$ 在 $va$ 中的位置，设为 $x$，那么它在原数组的位置就是 $id_x$，在套用刚才讲到的距离计算公式就可以了，最终时间复杂的 $O(n \log n)$。

---

## 作者：_shine_ (赞：2)

## 题目大意
现在有 $n$ 个数，问你在前 $k$ 个数之内能否通过相邻之间的交换小于后 $k$ 个数。
## 思路
我们可以发现，对于每一个下标小于等于 $k$ 的数 $a_i$，那么，这个数的最佳答案其实就是每一个下标大于 $k$ 的数 $a_j$，使得 $a_i < b_j$，并且使得 $j$ 为第一个使得 $a_i < b_j$ 的下标。那么，这道题同理，操作的最优方案为第一个下标小于等于 $k$ 的 $a_i$ 和第一个下标大于 $k$ 的 $a_j$，使得 $a_i<a_j$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;ch=getchar();
	}
    while(ch>='0'&&ch<='9'){
    	s=s*10+ch-'0';
		ch=getchar();
	}
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
priority_queue<int,vector<int>,greater<int> >q;//使用优先队列储存我们从小到大的编号
int n,k;
int a[maxn];
int ans=INT_MAX;
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
	}
	for(int i=k;i>=1;--i){
		if(q.size()==0 || a[i]<a[q.top()]){
			q.push(i);
		}
	}//从小到大编入序列
	for(int i=k+1;i<=n;++i){
		while(q.size()>=1 && a[q.top()]<a[i]){//判断是否a[i]<a[j]，这里因为用了优先队列，前面较小的不行，显然后面较大的也没有满足。
			ans=min(ans,i-q.top());
			q.pop();
		}
	}//计算代价
	if(ans==INT_MAX)ans=-1;
	cout << ans << endl;
	return 0;
}

```


---

## 作者：sybs1145 (赞：1)

# [[ARC138A] Larger Score](https://www.luogu.com.cn/problem/AT_arc138_a) 题解

## 题目大意

给定一个长度为 $ n $ 的序列，求最少能通过几次邻项交换，使得原序列的前 $ k $ 个数之和严格小于新序列的前 $ k $ 个数之和，如果无解输出 -1。

## 思路

本题的贪心策略是比较明显的，我们只需要找到序列中前 $ k $ 个数中尽量靠后的一个数，使其严格小于后 $n-k$ 个数中尽量靠前的一个数。

但数据范围决定了我们不可能使用 $ n^2 $ 的暴力通过此题。

所以我们必须使用一种更高效的算法。

不难发现，这样的贪心思路很容易使人联想到二分。

我们可以枚举第 $k+1$ 到第 $n$ 个数，然后通过二分找到前 $k$ 个数中的目标数。

不过题目所给的序列并不具有单调性，在二分之前我们还需要预处理一下。

可以发现，对于任意一组 $i,j(i < j < k)$，如果 $A_i > A_j$，则 $A_i$ 就不可能成为我们要找的数，我们可以额外开一个数组来维护这个具有单调性的序列，再对其进行二分即可。

### Tips

记得特判输出 -1。

## AC code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 4e5 + 5;
int n, k, a[N], u[N], ans = INT_MAX; //a即为原数组，u是用来二分的具有单调性的序列
void init() //预处理
{
    for (int i = 1; i <= k + 1; i++)
        u[i] = INT_MAX;
    for (int i = k; i > 0; i--)
        u[i] = min(a[i], u[i + 1]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    init();
    for (int i = k + 1; i <= n; i++)
    {
        int l = 1, r = k, mid, res = 0;
        while (l <= r)
        {
            mid = (l + r) / 2;
            if (u[mid] >= a[i])
                r = mid - 1;
            else
                l = mid + 1, res = mid;
        }
        if (!res)
            continue;
        ans = min(ans, i - res);
    }
    cout << (ans == INT_MAX ? -1 : ans) << '\n'; //特判&输出
    return 0;
}
```

---

## 作者：Scean_Tong (赞：0)


## 题意简述

给定一个长度为 $n$ 的正整数序列，你可以交换序列中任意相邻的两个数字（每一次交换操作可以交换 $a_i$ 和 $a_{i+1}$ 这两个数），使得原序列中前 $k$ 个数字的和严格小于交换后的前 $k$ 个数字的和，求最小操作次数。

## 题目分析

首先注意到题目中的“每一次”交换。注意到“每一次”交换，这启示我们存在某种贪心策略。

考虑朴素的贪心，即每次将当前前 $k$ 个数中最小的数字与它后面的一个数交换（选择后面的数字进行交换的原因在后面会有详细解释，这里先按这个贪心进行分析），直到第 $k+1$ 个数字比它前面的数字都大为止。也就是说，我们总是选择当前的最小数字与后面一个数字进行交换。如果该最小数字比它前面的数字都小，那么继续向后交换；如果该最小数字比它的前面的数字至少有一个大，那么停止交换。这个贪心策略即为本题最朴素的贪心做法。

现在需要证明这个贪心策略是正确的。

## 贪心策略证明

假设在朴素贪心策略中某次交换的过程中，最小的第 $i$ 个数和它后面的一个数字 $a_j$ 进行了交换（$i\in[1,k], j \in [i+1,n]$）。

现在，记交换前的前 $i$ 个数的和为 $P$，后 $n-i$ 个数字的和为 $Q$，即

$$
P=\sum_{p=1}^i a_p, \ \ Q=\sum_{q=i+1}^n a_q
$$

现在需要证明，经过一次以 $a_i$ 为左边的右测的数字 $a_j$ 进行交换的操作后，前 $i$ 个数的和会严格增加，并且是不劣操作（即不存在进行更少的操作就能得到更优解的操作）。

为了不失一般性，我们需要考虑 $i=1$ 和 $i\in[2,k]$ 两个情况。在后一种情况下，假设经过朴素贪心算法之后的目标序列（也就是每次将最小数字与其后面的数字进行交换所得到的序列，以下称此序列为“目标序列”）为 $\{b_i\}$。

Case 1 $(i=1)$:

此时它和目标序列中的 $a_j$ 进行交换，得到一个新的序列 $\{c_i\}$。

可以直接计算，不难证明，交换后目标序列的第 $i$ 个数字 $b_1$ 的增加量比 $a_1$ 要小，并且交换前后 $\{a_i\}$ 和 $\{b_i\}$ 序列之间的大小顺序关系没有发生改变。也就是说，此时交换后得到的 $c_1 > b_1 > a_1$，同时有 $b_2 \le a_2, b_3 \le a_3, ..., b_n \le a_n$

Case 2 $(i\in[2,k])$:

根据“以当前前 $k$ 个最小的数中最小的数向后快速贪心”得到的目标序列，有 $b_1 \le a_1, b_2 \le a_2$ 并且 $\forall j\in[3,k], b_j < a_j$

这里 $b_1$ 是“以 $a_1$ 向后快速贪心”得到的目标序列中的第 1 个数字（这个特殊记号将后面会多次用到），第 $k$ 个数即为 $a_i$。此时如果需要进行交换，那么只有两种情况：$j = 2$ 或 $j > 2$。下面对这两种情况展开讨论。

当 $j=2$ 时：

此时最小的数字是 $b_1$，也就是“以当前前 $k$ 个最小的数中最小的数向后快速贪心”得到的目标序列中的第一个数字。此时我们需要比较 $b_1$ 和 $a_i$ 的大小关系。

- 当 $a_i > b_1$ 时：

这种情况下，显然是进行不劣交换。假设向左的元素是 $a_l$，那么显然 $a_i$ 可以与 $a_l$ （$l \in [1, i)$）中的某一个进行交换，从而获得更小的和。因此，每次交换时的贡献都必然是最优的。

- 当 $a_i \le b_1$ 时：

这种情况下，由于目标序列中，$b_1$ 已经作为当前前 $k$ 个最小的数中最小的数了，并且在 $\{b_i\}$ 和 $\{a_i\}$ 中的位置都是已经排序的，因为对于任意 $1<j<k$ 来说，都有 $b_j<b_{j+1}$ 和 $a_j<a_{j+1}$。

此时 $b_1 \le a_i \le b_2$，也就是说要想让 $a_i$ 进入前 $k$ 个数中，只有一种情况（显然）：将 $a_i$ 和 $b_2$ 进行交换。

殊途同归，经过这次交换得到的新列表 $\{c_i\}$ 与之前的情况也非常类似，前两项在 $b_1$ 和 $a_i$ 中的相对大小之间变化，后面的数字都依然满足 $c_j \le b_j$。

当 $j>2$时：

此时我们进行的是比上一种情况更为复杂的交换，需要进行逐一分析。

- $b_1 \le a_i \le b_j, j\in [3,k]$：

显然，$a_i$ 与目标数组中的 $b_2, b_3, ..., b_{j-1}$ 都不可能进行交换。随着 $j$ 的增大，$b_j$ 的排名会越来越靠后，此时会发现 $b_1\ge b_2\ge ... \ge b_{j-1}\ge a_i$，根据目标数组已经排好序的性质，这里的不等式是成立的。也就是说，当 $j \ge i+1$ 时，$\{b_i\}$ 和 $\{a_i\}$ 排名相同的数字之间的对应关系不会发生改变。

因此，对于 $j \in [i+1, k]$，我们可以将 $a_i$ 直接与 $a_{j-1}$（注意此时 $j>2$）进行交换，从而取得更优解。

- $a_i > b_1$ 且 $a_i > b_j, j\in [i+1,k]$：

交换 $a_i$ 和 $a_{j-1}$（这里 $j > 2$），可以让 $a_i$ 直接到达 $b_1$ 和 $b_2$ 之间，然后变为对其它区间的 $b$ 数组去做“以 $b_1$ 向后快速贪心”，而新的区间是 $[b_2, b_{j-1}]$。这是一个和“以 $a_1$ 向后快速贪心”完全类似的贪心过程，结论与 $j\in [3,k]$ 的情况相同。

- $a_i \le b_1$ 且 $a_i < b_j, j\in [i+2,k]$：

这种情况可以直接合并上一种情况，得到

$$
a_i \le b_1 < b_2 \le ... \le b_{j-2} < b_{j-1} < ... \le b_k
$$

与上一种情况类比， $a_i$ 与目标数组中的 $b_2, ..., b_{j-1}$ 都不可能交换。显然，$b_{j-1}$ 排名靠后，因此，只有将 $a_i$ 与 $a_{j-2}$ 进行交换，否则 $a_i$ 是不可能进到前 $k$ 个数中。于是我们可以将新的区间定义为 $[b_{j-1}, b_{k}]$，进一步迭代下去。由此，也就完成了贪心操作的全部证明。

最后，还需说明的是：为什么我们之前的贪心策略会选择后面的数字进行交换？这是因为如果选择当前前 $k$ 个数中的一个与后面的数字进行交换，得到的新数字可能仍然不满足每个数字都大于前面的数字。因此会导致这个过程无法停止。而如果选择后面的数字进行交换，则可以确保每次交换都会使目标序列变为合法的。

## 实现

我们可以先把原数组中所有下标和它们的元素都保存起来，将这些元素按递增顺序排序，并记录下它们在排序后的位置。对于每个 $i$，我们分别记录它在排序后数组中左侧最近的未匹配元素和右侧最近的未匹配元素。然后一遍扫描每个元素，若左侧最近的未匹配元素在当前位置左侧且比当前元素还要大，则说明此时需要交换。因为当前位置它的左侧前缀没有更小的可供交换的数字了，因此需要向右扩展统计交换次数。



---

## 作者：_zhx (赞：0)

# AT_arc138_a [ARC138A] Larger Score 题解

## 题目大意

现在有 $n$ 个数，问你在前 $k$ 个数之内能否通过相邻之间的交换小于后 $k$ 个数，可以就输出最少次数，否则输出 $-1$。

### 思路

对于每一个下标小于等于 $k$ 的数 $a_i$，这个数的最佳答案其实就是每一个下标大于 $k$ 的数 $pq_j$，且满足 $a_i<pq_j$，并使 $j$ 为第一个使得    $a_i<pq_j$  的下标。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
priority_queue<int,vector<int>,greater<int> >pq;
int n,k,a[N],x=0x3f3f3f3f;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=k;i>=1;i--) if(pq.size()==0||a[i]<a[pq.top()]) pq.push(i);
	for(int i=k+1;i<=n;i++)
	{
		while(pq.size()>=1&&a[pq.top()]<a[i])//判断是否a[pq.top()]<a[i]，优先队列，前面小的不行，后面大的肯定不满足。
		{
			x=min(x,i-pq.top());
			pq.pop();
		}
	}
	if(x==0x3f3f3f3f) cout<<"-1\n";
	else cout<<x<<'\n';
	return 0;
}
```


---

## 作者：WaterSun (赞：0)

# 思路

不难发现：对于每一个 $i(1 \leq i \leq k)$，如果能在 $(k + 1) \sim n$ 中找到任何一个 $j$，满足 $a_j > a_i$ 就算满足条件。

进一步思考，为了使操作数最小，对于每一个 $1(1 \leq i \leq k)$，都找一个在 $(k + 1) \sim n$ 中第一个大于 $a_i$ 的数，便于它交换。

那么，这样的代价为 $(j - i)$（读者可自行模拟）。

然后，我们看到这个结论，我们就能想到 `upper_bound`。然而，这个序列不一定是有序的，所以，我们就要使得它有序。

我们考虑维护一个 $a_{(k + 1) \sim n}$ 的前缀最大值，因为我们要找的只能是第一个比它大的，如果 $a_j$ 比 $a_{j - 1}$ 大，那么是没有影响的；否则，结果已经在 $a_{j - 1}$ 的时候出现了，根本不会受 $a_j$ 的影响。

这样我们就维护好了这个序列的单调性，最后就能切掉了。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 4e5 + 10,inf = 1e9 + 10;
int n,k,ans = inf;
int arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	n = read();
	k = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = k + 1;i < n;i++) arr[i + 1] = max(arr[i],arr[i + 1]);//前缀最大值 
	arr[n + 1] = inf;//设置哨兵 
	for (re int i = 1;i <= k;i++){//枚举 
		int t = upper_bound(arr + 1 + k,arr + 1 + n,arr[i]) - arr;//找一个比 a[i] 大的第一个数的下标 
		if (t == n + 1) continue;//如果没有直接 continue 
		ans = min(ans,t - i);//更新答案 
	}
	if (ans == inf) puts("-1");//无解 
	else printf("%d",ans);
	return 0;
}
```

---

