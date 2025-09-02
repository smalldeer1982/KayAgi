# Replace and Keep Sorted

## 题目描述

Given a positive integer $ k $ , two arrays are called $ k $ -similar if:

- they are strictly increasing;
- they have the same length;
- all their elements are positive integers between $ 1 $ and $ k $ (inclusive);
- they differ in exactly one position.

You are given an integer $ k $ , a strictly increasing array $ a $ and $ q $ queries. For each query, you are given two integers $ l_i \leq r_i $ . Your task is to find how many arrays $ b $ exist, such that $ b $ is $ k $ -similar to array $ [a_{l_i},a_{l_i+1}\ldots,a_{r_i}] $ .

## 说明/提示

In the first example:

In the first query there are $ 4 $ arrays that are $ 5 $ -similar to $ [2,4] $ : $ [1,4],[3,4],[2,3],[2,5] $ .

In the second query there are $ 3 $ arrays that are $ 5 $ -similar to $ [4,5] $ : $ [1,5],[2,5],[3,5] $ .

## 样例 #1

### 输入

```
4 2 5
1 2 4 5
2 3
3 4```

### 输出

```
4
3```

## 样例 #2

### 输入

```
6 5 10
2 4 6 7 8 9
1 4
1 2
3 5
1 6
5 5```

### 输出

```
8
9
7
6
9```

# 题解

## 作者：11D_Beyonder (赞：6)

### Idea

&emsp;&emsp;对于 $a_{l},a_{l+1},\cdots,a_r$，我们只考虑更换其中一个位置的值，使得原序列仍然保持严格递增的性质，就能得到 $k-\text{similar}$ 的数组 $b$。

&emsp;&emsp;对于 $l<i<r$，$a[i]$ 可更换为 $a_{i-1}+1,\cdots,a_{i}-1,a_{i}+1,\cdots,a_{i+1}-1$，共 $a_{i+1}-a_{i-1}-2$ 种方案；累加得，$\sum\limits_{i=l+1}^{r-1}(a_{i+1}-a_{i-1}-2)=a_r+a_{r-1}-a_{l-1}-a_l-2\times(r-l-1)$。

&emsp;&emsp;对于 $a_l$，需要在 $1\sim a_{l+1}-1$ 中挑一个数字，讨论 $a_l$ 是否为 $1$，得到的方案数都为 $a_{l+1}-2$；对于 $a_r$，需要在 $a_{r-1}+1\sim k$ 中挑选一个数字，讨论 $a_r$ 是否为 $k$，得到的方案数都为 $k-a_{r-1}-1$。

&emsp;&emsp;综上所述，总方案数为 $a_r-a_l-2\times(r-l)+k-1$。

### Code
```cpp
/******************************************************************
Copyright: 11D_Beyonder All Rights Reserved
Author: 11D_Beyonder
Problem ID: CF1485B
Date: 2021 Feb. 28th
Description: Math
*******************************************************************/
#include<iostream>
using namespace std;
const int N=100005;
int n,q,k;
int a[N];
int main(){
	cin>>n>>q>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		cout<<a[r]-a[l]-2*(r-l)+k-1<<endl;
	}
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：3)

## 题解 CF1485B 【Replace and Keep Sorted】

### 题意

+ 给定 $k$ 和长度为 $n$ 的严格递增数列 $a$，$a_i\le k$；
+ 两个数列 $k$ 相同当且仅当：两个数列长度相等，都严格递增，有且仅有一个数不同；
+ $q$ 次询问，求有 $a_l,a_{l+1},\dots,a_{r}$ 和多少个数列 $k$ 相同。

### 做法

其实可以看成在 $a_l,a_{l+1},\dots,a_{r}$ 中修改一个数，使其还是严格递增，有多少种方案。

因为只修改一个数，所以每个位置对答案的贡献独立，根据加法原理，就可以计算每个数可以修改为多少个数，然后加起来，注意特判两端。

时间复杂度 $O(qn)$，显然无法通过。

---

然后很多大佬就开始做什么前缀和优化，然后推出一个在我这种蒟蒻看来很复杂的式子。

---

但我这里有一种更好理解的算法。

只修改一个数，每个位置对答案的贡献独立；只修改出一个新的数，所以每个修改出的数也对答案的贡献独立。

对于任意 $j=a_i(l\le i\le r)$，$j$ 的贡献为 $0$。因为如果改的是 $a_i$，绝不可能还是 $j$；如果不是 $a_i$，改成 $j$，严格递增就被破坏了。

对于任意 $j(a_l\le j\le a_r,j\ne a_i)$，$j$ 的贡献为 $2$，分别是从它左右两边的数修改而成，如果从其他数修改，也会破坏严格递增。

对于任意 $j(j<a_l \operatorname{or} a_r<j)$，显然 $j$ 的贡献为 $1$。

那式子就不难推出了。

### 代码

```cpp
#include <cstdio>

using namespace std;

const int N = 1e5 + 5;

int arr[N];

void run() {
	int n, q, k;
	scanf("%d%d%d", &n, &q, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i]);
	}
	for (int i = 1; i <= q; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		int ans = arr[l] + k - arr[r] - 1;
		ans += ((arr[r] - arr[l] + 1) - (r - l + 1)) * 2;
		printf("%d\n", ans);
	}
}

int main() {
	run();
}
```

---

## 作者：wei2013 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF1485B)
## 题目大意：
- 给定 $k$ 和一个长度为 $n$ 的数列，数列保证递增，且  $a_i \le k$。
- 两个数列 $k$ 相同当且仅当：两个数列长度相等，都严格递增，有且仅有一个数不同。
- $q$ 次询问，每次输入 $l$，$r$，问 $a_l$ 到 $a_r$ 和多少个 $k$ 相等。

## 思路：
暴力，时间复杂度 $\mathcal{O(nq)}$，肯定不行，需要考虑优化。

发现区间二字，立刻考虑前缀和，再仔细观察也验证了猜想，使用前缀和优化。

对于数列第 $i$ 项：

当 $l \le i \le r$ 时：若 $a_i$ 不等于 $b_i$，则有 $a_{i+1}-a_{i-1}-2$ 种方案，也同时能在这个情况下维护前缀和。

当 $i=l$ 时：有 $a_{l+1}-2$ 种方案。

当 $i=r$ 时：有 $k-a_{r-1}-1$ 种方案。

既然已求出公式问题自然也就迎刃而解了。

## code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
	int n,q,k;
	cin>>n>>q>>k;
	for (int i=1;i<=n;i++) {
		cin>>a[i];
	}
	for (int i=1;i<=q;i++) {
		int l,r;
		cin>>l>>r;
		int ans=a[l]+k-a[r]-1;
		ans+=((a[r]-a[l]+1)-(r-l+1))*2;
		cout<<ans<<endl;
	}
}
```
望审核通过！

---

## 作者：yhx0322 (赞：1)

## 题目简述
- 给定一个整数 $k$。
- 我们定义两个数列是 $k$ 相同的，当且仅当这两个数列长度相同，严格递增，元素都在 $[1,k]$ 之间，且恰好存在一个数不同。

现在给出一个长度为 $n$ 的严格递增的数列 $A$，每次询问一个区间 $[L,R]$，求出 $A_l \sim A_r$ 这个数列有多少个与其 $k$ 相同的数列。

## 思路
暴力枚举时间复杂度为 $O(nq)$，考虑如何优化。

对于下标 $i$：
- $l < i < r$，如果 $A_i \neq B_i$，那么方案数总共有 $A_{i + 1} - A_{i - 1} - 2$ 种可能。
- $i = l$，方案数为 $A_{i + 1} - 2$ 种可能。
- $i = r$，方案数有 $k - A_{i - 1} - 1$ 种可能。

所以当 $l < i < r$ 时，维护前缀和数组。

其余的情况特判。

## 代码
```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, q, k, a[N];
int l, r;

int main() {
	scanf("%d%d%d", &n, &q, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d", &l, &r);
		int ans = a[l] + k - a[r] - 1;
		ans += ((a[r] - a[l] + 1) - (r - l + 1)) * 2;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1485B)

对于一个数列 $a_l,a_{l+1},a_{l+2},\cdots,a_r$，只要改变其中的一个数就可以得到一个与之 $k$ 相同的数列。

对于 $a_{l+1}$，它可能的取值范围是 $(a_l,a_{l+2})$，除去 $a_{l+1}$ 本身，就会有 $a_{l+2}-a_l-2$ 种方案。

同样，对于所有 $l < i < r$，改变它的方案数是 $a_{i+1}-a_{i-1}-2$。

所以，改变除 $a_l$ 和 $a_r$ 的元素的总方案数为：$\sum_{i = l+1}^{r-1} (a_{i+1}-a_{i-1}-2) = a_r+a_{r-1}-a_l-a_{l+1}-2(r-l-1)$。

对于 $a_l$，它的取值范围为 $[1,a_{l+1})$，除去 $a_l$ 本身就有 $a_{l+1}-2$ 种方案。同理可得改变 $a_r$ 有 $k-1-a_{r-1}$ 种方案。

最终的总方案数为：$[a_r+a_{r-1}-a_l-a_{l+1}-2(r-l-1)]+(a_{l+1}-2)+(k-1-a_{r-1})=a_r-a_l-2(r-l)+k-1$。

输出 $a_r-a_l-2(r-l)+k-1$ 即可。

$\mathbb{S}\mathfrak{h}\text{o}\mathsf{w}\ \mathcal{M}\gamma\ \complement o\texttt{d}\mathbf{e}$：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q, k, a[100001];
int main(){
	scanf("%d%d%d", &n, &q, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= q; i++){
		int l, r; scanf("%d%d", &l, &r);
		printf("%d\n", a[r] - a[l] - 2 * (r - l) + k - 1);
	}
	return 0;
}
```

---

## 作者：zhengpie (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1485B)

### 1.思路

首先考虑暴力，但是时间复杂度 $\Theta(nq)$，肯定超时。

看到题目出现“区间”二字，你会想起什么？

~~线段树！~~ 前缀和优化！

考虑下标 $i \in [l,r]$，显然有 $3$ 种情况，分别是：

1. $i \in (l,r)$，如果 $a_i \neq b_i$，那么会有 $a_{i+1} - a_{i -1} - 2$ 种情况。
2. $i = l$，显然有 $a_{l + 1} - 2$ 种不同情况。
3. $i = r$，有 $k - a_{r - 1} - 1$ 种不同情况。

于是就得到对于 $i \in [l,r]$，有 $(a_{i+1} - a_{i -1} - 2) + (a_{l + 1} - 2) + (k - a_{r - 1} - 1)$ 种不同的情况。

然后直接套公式即可。

### 2.完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q,k,a[114514];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>q>>k;
	for(int i = 1;i <= n;i++) cin>>a[i];
	for(int i = 1,l,r;i <= q;i++)
	{
		cin>>l>>r;
		cout<<a[r] - a[l] - 2 * (r - l) + k - 1<<endl;//套公式
	}
	return 0;
}
```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1485B)

看到这道题我的第一个想法是暴力，但很明显暴力的时间复杂度为 $O(nq)$，那只能优化了。

这一道题可以用前缀和，再加一点优化时间复杂度就能达标。

那么分类讨论一下，对于数列第 $i$ 项：

1. 当 $i=l$ 时，有 $a_{l+1}-2$ 种方案。

2. 当 $i=r$ 时，有 $k-a_{r-1}-1$ 种方案。

3. 当 $l\le i\le r$ 同时 $a_i \ne b_i$ 时 ，那么就有 $a_{i+1}-a_{a-1}-2$ 种方案。

上代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,q,k,a[N],l,r;
signed main() 
{
	cin>>n>>q>>k;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
	}
	for(int i=1;i<=q;i++) 
	{
		cin>>l>>r;
		int ans=a[l]+k-a[r]-1+((a[r]-a[l]+1)-(r-l+1))*2;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Rookie_t (赞：0)

首先，可以根据题意去暴力，枚举所有可能的情况，时间复杂度为 $O(nq)$，超时。

不过我们可以对暴力进行一些优化。

对于 $a_i$，当 $l \leq i \leq r$ 时，如果 $a_i \neq b_i$，就有 $a_{i+1}-a_{i-1}-2$ 种不同情况。

如果 $i = l$，就有 $a_{l+1}-2$ 种不同情况。

如果 $i = r$，就有 $k-a_{r-1}-1$ 种不同情况。

后面就根据规律推导即可。 

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100010;
ll a[MAXN];
int n,q,k,l,r,ans;
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>q>>k;
	for(int i = 1;i<=n;i++){
		cin>>a[i];
	}
	for(int i = 1;i<=q;i++){
		cin>>l>>r;
		ans = a[l]+k-a[r]-1;
		ans += ((a[r]-a[l]+1)-(r-l+1))*2;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：YangXiaopei (赞：0)

## 思路

我们可以发现，询问次数达到了 $2 \times 10 ^ 5$ 级别。

而多次询问的这重循环又是必不可少的，所以除非是 $\log$ 级别的神仙做法，循环内基本肯定为 $\mathcal{O}(1)$ 了。

那我们基本可以肯定，输出只跟左右端点有关了。

然后就是长达 $3$ 小时的找规律，终于发现，当找出的式子为 $ans = a[r] - a[l] + (l - r) \times 2$ 时，答案与式子所得差 $k - 1$。

然后，就切了。

## 证明

如果 $a_i$ 最开始为 $x$，那改完后 $a_i$ 不可能还是 $x$，那么 $x$ 对答案是没用的。

如果 $a_l \le x \le a_r $ 且 $x \ne a_i$，那 $a_i$ 可变为两边的数，$x$ 可让答案增加 $2$。

其他的 $x$ 则只能让 $a_i$ 向两边中的一边变，只能让答案增加 $1$。

那最终的答案即为 $ans = a[l] + k - a[r] - 1 + (((a[r] - a[l] + 1) - (r - l + 1)) \times 2)$。

我们把括号展开，正好也是我们最初的 $ans = a[r] - a[l] + (l - r) \times 2 + k - 1$，那我们就切掉这题了。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k, a[200005];
signed main(){
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	while(m--){
		int l, r;
		cin >> l >> r;
		cout << a[r] - a[l] + (l - r) * 2 + k - 1 << "\n";
	}
	return 0;
}
```

---

## 作者：huangzhixia (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF1485B)**

## 题意

现在给我们一个整数 $k$ 与一个长度为 $n$ 的序列，保证序列里的 $n$ 个元素都在 $[1,k]$ 之间，并且严格递增。现在我们有一个操作次数 $q$，每次给出两个数 $L$ 和 $R$，要求 $a_L$ 到 $a_R$ 的序列中有多少个与 $k$ 相等。

## 思路

先思考最~~无脑~~省事的暴力。

先枚举个 $q$，套一层 for，来看对于每次操作。然后再从 $1$ 枚举到 $n$，看一下，再统计答案。这样的时间复杂度很明显 $O(qn)$，显然会 TLE。

这里可以看到，对于下标 $f$，我们每次操作的 $L$ 和 $R$ 得到以下几点：

- 当 $f = L$，答案就要加上 $a_{f+1} - 2$。 

- 当 $f = R$，答案就要加上 $k + a_{f-1}-1$。

- 当 $a_f \ne b_f$ 并且 $L < f < r$，答案要加上 $a_{i+1} - a_{i-1} - 2$。

现在我们按照上述说的做就行了。

## Code:

```cpp
#include <bits/stdc++.h>
#define hh; puts("");             
using namespace std;

int n, q, k, a[100001];

inline void solve() {
	int l, r, answer = 0;
	scanf("%d%d", &l, &r);
	answer += a[l] + k - a[r] - 1 + ((a[r] - a[l] + 1) - (r - l + 1)) * 2;
	printf("%d", answer);
	hh;	
}

int main() {
	scanf("%d%d%d", &n, &q, &k);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	while (q--) 
		solve();
}
```


---

## 作者：fanfansann (赞：0)

整套题目全部题解链接：[Codeforces Round #701 (Div. 2) A ~ F ，6题全，超高质量良心题解【每日亿题】2021/2/13](https://fanfansann.blog.csdn.net/article/details/113799739) 

**Problem B Replace and Keep Sorted**

![在这里插入图片描述](https://img-blog.csdnimg.cn/2021021317194813.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80NTY5Nzc3NA==,size_16,color_FFFFFF,t_70)
**Translation**

对于一个正整数 $k$ ，规定两个序列是 **“$k$ 相似序列”** 需要满足以下要求：

- 两个序列**严格递增**
- 两个序列有相同的长度
- 两个序列的元素的取值 $\in[1,k]$
- 两个序列仅有一个位置的元素不同

给定一个正整数 $k$，一个严格递增的序列 $a$ ，将会有 $q$ 次询问，每次询问一个区间 $l$ ，$r$ ，你的任务是每次输出有多少种 $b$ 序列是序列 $a_l,a_{l+1},a_{l+2}\cdots,a_r$ 的 **“$k$ 相似序列”** 。

**Word**
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210213172557425.png)


**Solution**

签到题 ~ 

注意一个重要的性质：严格递增

因为元素的取值只能是 $[1,k]$ ，并且两个序列必须只能有一个不同的元素，由于序列一定严格递增，求总的方案数，实际上对于每一个序列来说，每次只能有一个位置不同，而对于这个位置来说，手算一下发现，对于每一个区间里的数，一共有 $a[i+1]-a[i-1]-2$ 种选法，对于区间的边界来说，一共有 $a[i+1]-a[i-1]-2$ 种选法，设每一个位置 $i$ 的选法就是 $i$ 的权值，由加法原理可知，总方案数就是区间权值和，所以我们直接使用一个前缀和维护一下即可。

**Code**
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
typedef int itn;
const int N = 2e5 + 7;
const ll INF = 4e18;

int n, m, t, q, k;

ll val[N], a[N];
ll sum[N];

int main()
{
    scanf("%d%d%d", &n, &q, &k);
    for(int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
    }
    a[0] = 1, a[n + 1] = k;
    for(int i = 1; i <= n; ++ i) {
        val[i] = a[i + 1] - a[i - 1] - 2;
        sum[i] = sum[i - 1] + val[i];
    }
    while(q -- ) {
        int l, r;
        scanf("%d%d", &l, &r);
        ll ans = sum[r - 1] - sum[l];
        ans += a[l + 1] - 1 - 1;
        ans += k - a[r - 1] - 1;
        printf("%lld\n", ans);
    }
    return 0;

}

```


---

## 作者：wgyhm (赞：0)

## B. Replace and Keep Sorted

### 题意

* 给你一个正整数 $k$ ，称两个数组是 $k$ 相似的，当且仅当两个数组 $a,b$ **等长、严格递增、 $1\le a_i,b_i\le k$ **且**只有一个位置的数字不同**。
* 给你一个长度 $n$ 的正整数序列 $a$，为$q$ 次询问，每次给出一个区间 $[l,r]$。求与 $a$ 的子数组 $[a_l,a_{l+1},...,a_r]$ $k$ 相似的数组 $b$ 个数。

### 题解

对于 $l<i<r$ ，如果 $a_i$ 与 $b_i$ 不同，那么共有 $a_{i+1}-a_{i-1}-2$ 种可能，因为要除去 $a_{i+1}$ 保证递增和 $a_i$ 保证不同。

对于 $i=l$ ，一共有 $a_{i+1}-2$ 中可能；对于 $i=r$ ，共有 $k-a_{i-1}-1$ 种可能。

所以当 $l<i<r$ 时，可以前缀和搞。 $i=l$ 或 $i=r$ 特判处理。

### Code

```cpp
#define int long long
#define maxn 100005
int a[maxn],sum[maxn];
signed main(){
    rg int n,q,k,l,r,i;
    read(n);read(q);read(k);
    for (i=1;i<=n;i++) read(a[i]);a[n+1]=k;
    for (i=1;i<=n;i++) sum[i]=sum[i-1]+a[i+1]-a[i-1]-2;
    while (q--){
    	read(l);read(r);
        printf("%lld\n",sum[r-1]-sum[l]+a[l+1]-2+k-1-a[r-1]);
    }
    return 0;
}
```

完整题解 [Codeforces Round #701](https://www.luogu.com.cn/blog/51569/codeforces-round-701-post)。

---

## 作者：Doubeecat (赞：0)

> [B. Replace and Keep Sorted](https://codeforces.ml/contest/1485/problem/B)
> 
> 定义 $b$ 与 $a$ 相似当且仅当：
> 
> $a,b$ 为**严格单调递增**的**等长**正数序列
> 
> $a,b$ 中的每个元素都在 $[1,k]$ 中，$a,b$只有一个元素不同。
> 
> 有 $q$ 个询问，每次询问与 $a$ 的一个子段相似的 $b$ 有多少个。
> 
> $n,q \leq 10^5$

## Solution:

注意到，两个相似的序列中只有一个数不同，所以我们对于每个数依次考虑，直接利用加法原理统计答案即可。

那么考虑每一位怎么统计答案，比如 `2 4 7` 我们考虑中间 $4$ 这位。因为是严格单调递增，所以可取的值显然是 $3,5,6$ （注意要去掉自己），我们可以推导出公式，设 $f_i$ 为第 $i$ 位修改方案数，则有 $f_i = a_{i+1} - a{i-1} - 2$，这个东西可以前缀和优化掉。

但是注意一点，每一个序列的最开始那个数的取值范围是 $[1,a_2)$，最后一个数的取值范围是 $(a_{len} - 1,k]$,最后得到的式子就是 $ans = pre_{r-1} - pre_{l} + a_{l+1} - 2 + k - a_{r-1} -1$

## Code:

```cpp
signed main() {
	read(n,m,q);
    for (int i = 1;i <= n;++i) {
        read(a[i]);
    }
    a[0] = 0;a[n+1] = q;
    pre[1] = ans[1] = a[2] - 2;
    for (int i = 2;i <= n;++i) {
        ans[i] = (a[i+1]-1) - (a[i-1]+1);
        pre[i] = pre[i-1] + ans[i]; 
        //printf("%d %d\n",ans[i],pre[i]);
    }
    while (m--) {
        int l,r;read(l,r);
        if (l == r) {
            printf("%d\n",q-1);
        }
        else {
            printf("%d\n",pre[r-1] - pre[l] + a[l+1] - 2 + q - a[r-1] -1);
            //printf("%d\n",pre[r] - pre[l] + a[l]-1);
        }
    }   
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1485B)

------------
# 思路：
每次只能变动原序列一个元素，且这个元素变动范围在其前后两元素之间。

位于开头的元素需要 $\ge 1$，位于末尾的元素需要 $\le k$，其余中间的元素 $a_i$ 需要 $a_{i-1}$ 小于 $a_i$ 小于 $a_{i+1}$。

所以利用差分和，设差分为 ```d[i]=a[i]-a[i-1]```，则每个元素（非首尾元素）可以有 ```d[i]-1+d[i+1]-1``` 种可行情况
临界分析：对于首尾元素，```a[1]``` 有 ```d[1]-1+a[1]-1``` 种可行情况，```a[n]``` 有 ```d[n]-1+k-a[n]``` 种可行情况。

把所有可行情况加起来就可以了，算 $sum$ 的时候用到差分和，避免重复计算超时。

------------
代码：
```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<deque>
#include<stack>
#include<map>
#include<list>
using namespace std;
const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 1e6;
#define LL long long

int a[N] , n , t , k , num[N];

int main(){
	cin >> n >> t >> k;
	for(int i = 1 ; i <= n ; i++){
		cin >> a[i];
	}
	a[0] =0 , a[n + 1] = k;
	for(int i = 1 ; i <= n ; i++){
		num[i] = (a[i] - 1 - a[i - 1]) + (a[i + 1] - a[i] - 1);
	}
	for(int i = 1 ; i <= n ; i++){
		num[i] += num[i - 1];
	}
	while(t--){
		int l , r;
		cin >> l >> r;
		LL ans;
		if(l == r){
			ans = k - 1;
		}else {
			ans= num[r - 1] - num[l];
			ans += a[l + 1] - 2 + k - 1 - a[r - 1];
		}
		cout << ans << endl;
	}
    return 0;
}
```

---

