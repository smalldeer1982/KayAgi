# Min-Max Array Transformation

## 题目描述

给你一个升序数组 $a_1,a_2,...,a_n$。你要通过以下步骤去得到数组 $b_1,b_2,...,b_n$ ：

1. 生成数组 $d$，由$n$个非负整数组成。
2. 通过 $b_i=a_i+d_i$ 计算每一个 $b_i$。
3. 给 $b$ 进行升序排序。

你现在又知道了结果 $b$，你要算出每一个 $d_i$ 可能的最小值和最大值（每个 $d_i$ 的最值可以是由不同的数组 $d$ 满足的）。

## 说明/提示

第一个样例中，$d=[5,10,6]$ 满足 $d_1^{min}=5,b=[2+5,3+10,5+6]=[7,13,11]=[7,11,13]$。

第一个样例中，$d=[9,4,8]$ 满足 $d_2^{min}=4,b=[2+9,3+4,5+8]=[11,7,13]=[7,11,13]$。

## 样例 #1

### 输入

```
4
3
2 3 5
7 11 13
1
1000
5000
4
1 2 3 4
1 2 3 4
4
10 20 30 40
22 33 33 55```

### 输出

```
5 4 2
11 10 8
4000
4000
0 0 0 0
0 0 0 0
12 2 3 15
23 13 3 15```

# 题解

## 作者：xfrvq (赞：14)

还是纪念一下淦出四题的一场 $\tt Edu$。

前言：非常短的做法，两个 $\tt task$ 分别是结论和贪心。

## 题意

有两个序列 $a,b$。对于每个 $a_i$，你需要对 $b$ 进行重排，使得 $\forall k,b_k-a_k\ge0$。问这时 $b_i-a_i$ 最小、最大分别可能是多少。

多组询问，$\sum n\le2\times10^5$。

下面的讨论，记 $c$ 为重排后的 $b$。

## task 1 

最小其实很好做。如果没有确定的思考方向，可以发挥 $\tt CF$ 上非常实用的盲猜法。

对于 $a_i$ 而言，单纯要让重排后 $c_i-a_i$ 最小，可以直接让 $c_i=b$ 中大于等于 $a_i$ 且最小的数，即后继。

这个结论是对的。考场上直接输出后继就完了，接下来我给个证明。

因为题目保证有解，所以最起码对于原来的 $a,b$ 有 $\forall k,a_k\le b_k$。

我们令 $b_j$ 为 $b$ 中 $a_i$ 后继，此时定有 $b_j\le b_i$，所以 $j\le i$。

然后考虑这样的构造（$c$ 为重排后的 $b$）：

$$c_k=\begin{cases}
b_k&k\in[1,j)\\
b_{k+1}&k\in[j,i)\\
b_j&k=i\\
b_k&k\in(i,n]
\end{cases}$$

## task 2

有一个关键性质，就是 $\forall j\le i$，$c_j$ 的选择不会影响 $c_i$ 的选择。原因是根据上面 $\forall k,b_k\ge a_k$，$b_{1\cdots i-1}$ 可以解决 $a_{1\cdots i-1}$，不会影响 $a_i$。

所以如果你想让单个的 $c_i-a_i$ 最大，只需要解决 $i+1\cdots n$ 的影响即可。

然后就是一个贪心的思想。如果 $c_i$ 尽量的大，那么就要让 $c_{i+1\cdots n}$ 都尽量的小。

所以我们用一个 `set` 存下所有的 $b$，倒序遍历 $a$，然后删除 `set` 中 $a_i$ 的后继。删除之前的 `set` 的最大值就是答案。

## Code

```cpp
const int N = 3e5 + 5;

int a[N],b[N];
multiset<int> s;
int d[N];

int main(){
    int T = read();
    while(T--){
        s.clear();
        int n = read();
        for(int i = 1;i <= n;++i) a[i] = read();
        for(int i = 1;i <= n;++i) s.insert(b[i] = read());
        for(int i = 1;i <= n;++i)
            printf("%d ",*lower_bound(b + 1,b + n + 1,a[i]) - a[i]);
        printf("\n");
        for(int i = n;i >= 1;--i){
            d[i] = *prev(s.end());
            s.erase(s.lower_bound(a[i]));
        }
        for(int i = 1;i <= n;++i) printf("%d ",d[i] - a[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Dry_ice (赞：6)

题链：[cf](https://codeforces.ml/contest/1721/problem/C) [luogu](https://www.luogu.com.cn/problem/CF1721C)

[cnblogs浏览](https://www.cnblogs.com/dry-ice/p/cf1721c.html)

## Description
给你两个长度为 $n$ 的数组 $a$ 和 $b$，存在一个长度为 $n$ 的数组 $d$，满足 $a_i+d_i=b_i$，让你求对于每个 $a_i$，找到可能匹配的最小和最大 $b_i$，输出 $b_i-a_i$ 的最小和最大可能值。每个 $a_i$ 求得值相互独立，最小和最大值也相互独立。

## Analysis
最小的应该很简单了，就是找到 $b$ 中第一个不小于 $a_i$ 的数 $b_j$，输出 $b_j - b_i$。为了实现高效的查找，由于原本给出的 $a$ 和 $b$ 即是非降的，可以使用二分查找，```c++``` 党亦可使用 ```lower_bound``` 函数。

难点在找最大，因为原数组 $a$ 和 $b$ 非降，且长度均为 $n$，可以考虑如下思路：

从后向前遍历，我们任然通过二分找到 $b$ 中第一个不小于 $a_i$ 的数 $b_j$，当第一次发现 $i=j$ 时，则 $a_i$ 到 $a_n$ 必须匹配 $b_i$ 到 $b_n$，此时 $a_i$ 到 $a_n$ 均可与 $b_n$ 相匹配，但由于 $d$ 非负，因此 $a_1$ 到 $a_{i-1}$ 不可能匹配到 $b_i$ 到 $b_n$ 中的任何一个数，记录此时匹配位置 $lst=i=j$。

下一次再找到 $i=j$ 时直接使 $a_i$ 到 $a_{lst}$ 与 $b_{lst}$ 匹配，而 $a_1$ 到 $a_{i-1}$ 不可能匹配到 $b_i$ 到 $b_{lst}$ 中的任何一个数，再记录新的 $lst$。直到遍历到开头。

综上所述，反映了**分段思想**，即通过**分段处理**来判断能否匹配、可能匹配的最大值。

## Code
此处展示 ```c++``` 党代码。

```cpp
#include <stdio.h>
#include <algorithm>
const int N = (int)2e5 + 5;
int n, a[N], b[N], c[N];
int main(void) {
    int t; for (scanf("%d", &t); t--; ) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
        for (int i = 1; i <= n; ++i) {
            int l = std:: lower_bound(b + 1, b + 1 + n, a[i]) - b; //二分
            printf("%d ", b[l] - a[i]); //最小直接输出
        }
        putchar('\n');
        int l, lst = n + 1;
        for (int i = n; i >= 1; --i) {
            l = std:: lower_bound(b + 1, b + 1 + n, a[i]) - b; //二分
            if (l == i) { //即 Analysis 中所述 i = j
                for (int i = l; i < lst; ++i) c[i] = b[lst - 1] - a[i]; 
                lst = l; //由于是倒序遍历，只能记录答案，后面再输出
            }
        }
        for (int i = 1; i <= n; ++i) printf("%d ", c[i]); putchar('\n'); //打印最大
    }
    return 0;
}
```

## The end. Thanks.

~~(路过点点~~

---

## 作者：XiaoQuQu (赞：3)

最大最小分开来考虑。

最小值很简单，对于每个 $a_i$，找到一个最小的 $x$ 使得 $b_x \ge a_i$，那么有 $d=b_x-a_i$。

最大值即为考虑找到一个 $j$，使得 $\forall t\in[i+1,j]$ 有 $b_{t-1}\ge a_t$ 即可，答案即为 $b_j-a_i$。

我们从 $n$ 到 $1$ 枚举 $i$，就能得到满足的 $j$ 最大值了。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2e5 + 5;
int n, a[MAXN], b[MAXN], mind[MAXN], maxd[MAXN];

void work()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    int j = n;
    for (int i = n; i >= 1; --i)
    {
        int x = lower_bound(b + 1, b + 1 + n, a[i]) - b;
        // cout << x << endl;
        mind[i] = b[x] - a[i];
        maxd[i] = b[j] - a[i];
        if (x == i)
            j = i - 1;
    }
    for (int i = 1; i <= n; ++i) cout << mind[i] << ' ';
    cout << endl;
    for (int i = 1; i <= n; ++i) cout << maxd[i] << ' ';
    cout << endl;
}

signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        work();
    }
    return 0;
}
```


---

## 作者：wimg6_ (赞：2)

## CF1721C 题解

### 题目简述

$t$ 组数据。

对于每组数据：给定 $len_a=len_b=n$ 且给定 $a$ 数组和 $b$ 数组。求对应的 $d$ 数组中每一项的最值，使 $\forall\ d_i,d_i=b_w-a_q$ 且 $\forall\ d_i,a_q,b_w\geq0$，其中 $i,w,q\in [1,n]$。

### 解题过程

不难发现，$d^{min}_i$ 应是 $a_i$ 在数列 $b$ 中首次出现可以使得 $a_i\leq b_i$ 的位置的数值减 $a_i$。亦不难发现，$d^{max}_i$ 应为 $\max\{a_jx-a_i\}$，即需满足 $\forall\ i,j:i\leq j,a_{i+w}\leq b_{i+w-1},w\in [1,|x-i-1|]$。

### 完整代码

```
#include<bits/stdc++.h>
using namespace std;
long long n,t,a[200010],b[200010],t1[200010],t2[200010];
vector<long long>g;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		g.clear();
		for(long long i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		for(long long i=1;i<=n;i++)
			scanf("%lld",&b[i]);
		for(long long i=1;i<=n;i++)
			t1[i]=*lower_bound(b+1,b+n+1,a[i])-a[i];
		long long i1=2,i2=1;
		for(i1;i1<=n;i1++,i2++)
			if(a[i1]>b[i2])
				g.push_back(i2);
		if(a[i1]<=b[i2] || a[i1]<=b[i2+1]) g.push_back(n);
		for(long long i=1;i<=n;i++)
		{
			auto it=lower_bound(g.begin(),g.end(),i);
			if(it==g.end()) t2[i]=t1[i];
			else t2[i]=b[*it]-a[i];
		}
		for(long long i=1;i<=n;i++)
			printf("%lld ", t1[i]);
		printf("\n");
		for (long long i=1;i<=n;i++)
			printf("%lld ", t2[i]);
		printf("\n");
	}
	return 0;
}
```

### 更新日志

$2022.8.29$ 提交题解。

$2022.8.30$ 修改了翻译。

---

## 作者：WilliamFranklin (赞：2)

### 主要思路

首先很容易得出：$d_i^{min}$ 就是在 $b$ 数组中最接近 $a_i$ 的那一个数减去 $a_i$，所以用 lower_bound 即可。

那么难点就在于怎么找出 $d_i^{max}$。

其实也很简单！

首先将 $a_i$ 都匹配到 $b_i$ 上。再只要看一看 $a_i$ 最大能匹配到哪一个位置还是合法的即可。

那么就可以发现一点：如果 $a_i > b_{i - 1}\left(i > 1\right)$ 那么这个位置 $i$ 到上一个不合法位置这一段区间中的最多延伸匹配到 $i - 1$ 这个位置上。

因为如果 $i$ 前面的某一个位置 $x$, 如果 $a_x$ 匹配的是 $b_i$ 的话，最好的情况也就是 $a_{x + 1}$ 到 $a_{i}$ 这些位置的匹配位置向前挪动一位，但 $a_i$ 这时候就“生气”了，因为这时候的 $d_i$ 就要变成负数了，题目是不允许的。

具体为什么 $d_i$ 要变成负数了，原因是 $a_i > b_{i - 1}\left(i > 1\right)$ 了。

好啦，贴代码！

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005], b[200005], fa[200005];
void init(int n) {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		init(n);
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= n; i++) {
			cin >> b[i];
		}
		for (int i = 1; i <= n; i++) {
			int w = (lower_bound(b + 1, b + n + 1, a[i]) - b);
			cout << b[w] - a[i] << ' ';
		}
		cout << endl;
		int last = n + 1;
		for (int i = n; i >= 1; i--) {
			fa[i] = last;
			if (a[i] > b[i - 1]) {
				last = i;
			}
		}
		for (int i = 1; i <= n; i++) {
			cout << b[fa[i] - 1] - a[i] << ' ';
		}
		cout << endl;
	}
}
```

可能会有不足的地方，请各路大佬指出，谢谢！

---

## 作者：Alex_Wei (赞：1)

> [CF1721C Min-Max Array Transformation](https://codeforces.com/contest/1721/problem/C)

相当于一个 $a_i$ 匹配一个 $b_j$，满足 $a_i \leq b_j$，$d_i$ 即 $b_j - a_i$。因为原序列有解，所以 $a_i\leq b_i$。

检查是否存在 $a_i$ 匹配 $b_j$ 的方案，只需删去 $a_i$ 和 $b_j$ 后检查是否仍有 $a_i \leq b_i$。

对于 $d_i$ 最小值，求出最小的 $b_j$，则 $b_j - a_i$ 即为所求，满足 $b_j\geq a_i$ 且对于任意 $p\in [j, i - 1]$ 均有 $a_p \leq b_{p + 1}$。条件二必然成立，只需二分或指针维护条件一。

对于 $d_i$ 最大值，求出最大的 $b_j$，则 $b_j - a_i$ 即为所求，满足 $b_j\geq a_i$ 且 对于任意 $p\in [i + 1, j]$ 均有 $a_p\leq b_{p - 1}$。因为 $b_i$ 满足条件，所以条件一必然成立，直接预处理 $lst_i$ 表示从 $i$ 开始第一个 $a_p > b_{p - 1}$ 的位置 $p$ 即可维护条件二。

时间复杂度 $\mathcal{O}(n)$ 或 $\mathcal{O}(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 5;
int n, a[N], b[N], lst[N];
void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= n; i++) cin >> b[i];
  lst[n + 1] = n + 1;
  for(int i = n; i > 1; i--) {
    if(a[i] <= b[i - 1]) lst[i] = lst[i + 1];
    else lst[i] = i;
  }
  for(int i = 1; i <= n; i++) cout << b[lower_bound(b + 1, b + n + 1, a[i]) - b] - a[i] << " ";
  cout << "\n";
  for(int i = 1; i <= n; i++) cout << b[lst[i + 1] - 1] - a[i] << " ";
  cout << "\n";
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：Deft_t (赞：1)

## 思路
- 对于 $d_i^{min}$ ，只需要找到一个最小的 $b_j$ 满足 $b_j \geq a_i$ ， $d_i^{min}$ 就等于 $b_j - a_i$ 。可以用双指针求出。  
证明：因为题目保证了有解，所以满足 $\forall i \in [1,n] , a_i \leq b_i$ 。假设找到的 $j \leq i$ ，可得 $a_j \leq b_i$ 。此时一定存在一个把 $a_j$ 加上一定值， $a_i$ 加上 $d_i^{min}$ 的方案（可结合样例 $1$ 第 $4$ 组数据看）。

- 对于 $d_i^{max}$ ，只要满足 $a[i] <= b[i-1]$ ，那么就存在把 $a_{i-1}$ 变成 $b_i$ ，把 $a_i$ 变成 $b_{i-1}$ 的方案。可以发现这个方案存在传递性，要找到 $d_i^{max}$ ，相当于找到能一直传递到最右边哪个位置。可以反过来想，从右向左传递就可以 $O(n)$ 解决啦。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,a[200005],b[200005];
int l[200005],r[200005];
int main()
{
	cin>>t;
	while(t--){
		cin>>n;
		for(int i = 1;i <= n;i++) cin>>a[i];
		for(int i = 1;i <= n;i++) cin>>b[i];
		int pos = 1;
		for(int i = 1;i <= n;i++){
			while(pos+1 <= n && b[pos] < a[i] ) pos++;
			l[i] = pos; //l[i]表示大于等于a[i]的最小值是b[l[i]]
		}
		pos = n;
		r[n] = n;
		for(int i = n;i >=1 ;i--){
			//满足a[i]<=b[i-1]，那么a[i-1]就可以和a[i]换着变,从右往左传递 
			if(a[i]<=b[i-1]) r[i-1] = r[i]; 
			else r[i-1] = i-1;
		}
		for(int i = 1;i <= n;i++) cout<<b[l[i]]-a[i]<<" ";
		cout<<endl;
		for(int i = 1;i <= n;i++){
			cout<<b[r[l[i]]]-a[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
/*
1
3
3 8  9 
8 10 13 
*/

```


---

## 作者：Charles_Fan (赞：1)

我们先证明能从序列 $a$ 生成序列 $b$ 的充要条件是 $a_i \leq b_i$。

必要性显然。对于充分性使用反证法。

假设存在 $i$ 使 $a_i > b_i$，设 $b_i = a_j + d_j$，则有 $a_i > a_j + d_j \geq a_j$，由 $a$ 的单调性知 $j < i$。

从 $a$ 中删去 $a_j$，记为 $a'$；$b$ 中删去 $b_i$，记为 $b'$，则显然可以从 $a'$ 生成 $b'$。而 $a'_{i-1} = a_i > b_i \geq b_{i-1} = b'_{i-1}$，令 $a$ 表示 $a'$，$b$ 表示 $b'$，重复以上操作 $i-1$ 次可使 $a_1 > b_1$，从而不存在对应的 $j$，矛盾。

先计算 $d_i^{min}$。设 $a_i + d_i = b_j$，则 $b_j \geq a_i$，故找到最小的 $b_j \geq a_i$，则 $d_i$ 可能取到的最小值为 $b_j - a_i$。由 $b_i \geq a_i$ 和 $b$ 的单调性可知 $j \leq i$。令 $d_k = \begin{cases} b_k - a_k, & k < j\textrm{ or } k>i \\ b_{k+1} - a_k, & j \leq k < i \\ b_j - a_i, & j=i \end{cases}$，显然 $d_k \geq 0$，故 $d_i$ 可以取到 $b_j - a_i$，即 $d_i^{min} = b_j - a_i$。

再计算 $d_i^{max}$。设 $a_i + d_i = b_j$，从 $a$ 中删去 $a_i$ 记为 $a'$，$b$ 中删去 $b_j$ 记为 $b'$，则 $a'_i \leq b'_i$，可得对于 $i \leq k < j$ 的 $k$ 有 $a_{k+1} \leq b_k$。故如果存在 $l > i$ 使 $b_{l-1} < a_l$，则 $j < l$，而如果不存在 $l$，则有 $i < j \leq n$，故 $d_i^{max} = \begin{cases} b_{l-1} - a_i, & l\textrm{ exists} \\ b_n - a_i, & \textrm{otherwise} \end{cases}$。显然 $l$ 随着 $i$ 的增加而增加，故用双指针可以对每个 $i$ 找到对应的 $l$。

时间复杂度为 $\Theta(n)$。

参考实现：

```cpp
#include <stdio.h>
#include <vector>
#include <algorithm>

int T;

void solve() {
    int n; std::vector<int> a, b;
    scanf("%d", &n);
    for (int i = 0, x; i < n; ++i) scanf("%d", &x), a.push_back(x);
    for (int i = 0, x; i < n; ++i) scanf("%d", &x), b.push_back(x);
    for (int i = 0, j = 0; i < n; ++i) {
        while (b[j] < a[i]) ++j;
        printf("%d ", b[j] - a[i]);
    }
    putchar('\n');
    for (int i = 0, j = 0; i < n; ++i) {
        if (j < i) j = i;
        while (j < n - 1 && a[j + 1] <= b[j]) ++j;
        printf("%d ", b[j] - a[i]);
    }
    putchar('\n');
}

int main() {
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) solve();
    return 0;
}
```

---

## 作者：happybob (赞：1)

先考虑最小值：

显然地，$d_i$ 的最小值应该是 $a_i$ 在 $b$ 里面的 `lower_bound`。由于每一个 $d_i$ 都是非负的，所以 $a_i$ 不可能加上 $d_i$ 后比原来的小。那为什么 `lower_bound` 一定满足题意？假设 $d_i$ 取 `lower_bound` 会导致无法构造一组 $d$，而 $d_i$ 取 `lower_bound` 后面的元素可以构造。假设原来的 `lower_bound` 分配给了 $a_x$，那么将后面的元素给 $a_x$，`lower_bound` 给 $a_i$ 一定也可以满足要求。

接着考虑最大值：

对于每个 $a_i$，其 $d_i$ 的最大值应为最大的 $a_x-a_i$，满足 $x \geq i$，$a_{i+1} \leq b_i, a_{i+2} \leq b_{i+1}, \cdots, a_{x} \leq b_{x-1}$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 2e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, a[N],b[N],minn[N],maxn[N],t;
vector<int> p;

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	t=read();
	while(t--)
	{
		n=read();
		p.clear();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++) b[i]=read();
		for(int i=1;i<=n;i++)
		{
			minn[i]=*lower_bound(b+1,b+n+1,a[i])-a[i];
		}
		int x=2,y=1;
		for(x;x<=n;x++,y++)
		{
			if(!(a[x]<=b[y]))
			{
				p.push_back(y);
			}
		}
		if(a[x]<=b[y]||a[x]<=b[y+1])p.push_back(n);
		for(int i=1;i<=n;i++)
		{
			auto it=lower_bound(p.begin(),p.end(),i);
			if(it==p.end()) maxn[i]=minn[i];
			else maxn[i]=b[*it]-a[i];
		}
		for(int i=1;i<=n;i++) printf("%d ", minn[i]);
		printf("\n");
		for (int i=1;i<=n;i++) printf("%d ", maxn[i]);
		printf("\n");
	}
	return 0;
}


```


---

## 作者：2018ljw (赞：0)

首先不难发现，我们与其对每个 $a_i$ 确定其 $d_{\max}$ 和 $d_{\min}$，不如考虑这个 $a_i$ 能配对的最大和最小的 $b$。

考虑一对点对 $(a_i,b_j)$ 可以配对的充要条件：$a_i
\le b_j$ 且其余位置均能够配对。

对第一件事，不妨记一个数 $p_i$，表示最小的 $a_i\le b_{p_i}$ 的位置。那么 $p_i\dots n$ 中每个位置，都可能成为 $a_i$ 配对位。

考虑如何满足第二件事：贪心的考虑，对于每个 $a_i$，我们让其和剩余且第一个不小于其的 $b$ 配对。反过来，我们让每个 $a_i$ 和 $b_{p_i}$ 配对即可。因此 $d_{\min}=b_{p_i}-a_i$。第一问解决。

再来看第二件事。不妨对 $b$ 开一个辅助数组 $w_i$ 表示 $b_i$ 匹配完后剩余多少个闲余的 $a$。那么显然匹配失败的充要条件为存在 $b_i<0$。根据定义，对每个 $a_i$，我们让 $w_{p_i}...w_n+1$。对每个 $b_i$，我们让 $w_i\dots w_{n}-1$。当我们试图匹配 $(a_i,b_j)$ 时，将其贡献赋成 0 即可。

根据这个模型我们也可以看出为什么第一问直接取 $p_i$ 是正确的。

发现对于一个 $i$，$a_i$ 贡献赋 $0$ 是恒定的，$b$ 的贡献赋 $0$ 是一段后缀，并且 check 只需要检查全局 $\min$ 非负。所以可以直接二分位置+线段树维护。

[AC 记录](https://codeforces.com/contest/1721/submission/169845575)

---

## 作者：Lib_Zhang (赞：0)

#### 题意简述:
给定一个序列 $ a $ ，和一个从小到大排序的最终 (与构造序列 $d$ 的 序列 $b$ 的顺序不同) 的序列 $ b $ ，每个数都是非负整数，然后按照 $b$ 构造一个序列 $d$ ， 使 $ b_i=a_i+d_i $ .

对于每个 $i$ ，求 $d_i$ 的最大值和最小值。

#### 分析:
因为序列 $b$ 是有序的,很容易在计算最小值的时候联想到二分。
只需二分查找出序列 $b$ 中大于等于 $a_i$ 的数中最小的数 $x$ ，答案即为 $x - a_i$

最大值因为不能和其他数必须选的序列 $b$ 中的某一个值，所以可以双指针的做法。
通过双指针做法，维护区间最大值，如果被选中就弹出。

### 代码:

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<set>
#include<stack>
#include<map>
#include<queue>
#include<cstdlib>
#include<iomanip>
#include<utility>
#define mid (l+r>>1)
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pai;
const double eps = 1e-10;
const int base = 13331;
const long long mod = 998242353;
long long maxn = -2147483647-1,minn = 0x7f7f7f7f;
ll t,n,a[200005],b[200005],op,ans[200005];
int main(){
	//freopen("filename.in","r",stdin);
	//freopen("filename.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		memset(ans,0,sizeof(ans));
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}
		for(int i=1;i<=n;++i){
			cin>>b[i];
		}
		for(int i=1;i<=n;++i){
			ans[i] = b[lower_bound(b+1,b+1+n,a[i])-b]-a[i];
		}
		for(int i=1;i<=n;++i){
			cout<<ans[i]<<" ";
		}
		cout<<endl;
		for(int i=1,op = 1;i<=n;++i){
			op = max(op,i);
			while(op<n&&a[op+1]<=b[op]){
//				if(a[op+1]<=b[op]){
//					break;
//				}
				++op;
			}
			ans[i] = b[op]-a[i];
		}
		for(int i=1;i<=n;++i){
			cout<<ans[i]<<" ";
		}
		cout<<endl;
		
		
	}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}


```

#### 总结:
最小值的二分做法比较好想，最大值需要进行一定的转移和维护。



---

