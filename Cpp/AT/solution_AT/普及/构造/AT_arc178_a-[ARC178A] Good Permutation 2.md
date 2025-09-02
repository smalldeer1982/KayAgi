# [ARC178A] Good Permutation 2

## 题目描述

给定一个正整数 $N$ 和一个长度为 $M$ 的正整数序列 $A=(1,2,\cdots,A_M)$。

其中，$A$ 中的所有元素都是介于 $1$ 和 $N$ 之间的不同整数。（即 $A$ 是 $N$ 的一个排列）

定义：
- 排列 $P=(P_1,P_2,\cdots,P_N)$ 是一个**好排列**，当且仅当：$P$ 没有连续子序列是 $A=(1,2,⋯ ,A_i)$ 的排列，其中 $1\le i\le M$。


确定是否存在这样的**好排列**，如果存在，找到**字典序最小**的好排列。

## 说明/提示

- $ 1\leq\ M\leq\ N\leq\ 2\times\ 10^{5} $
- $ 1\leq\ A_{i}\leq\ N $
- $ A $ 中的所有元素都是不同的。
- 所有输入值都是整数。

 
### 样例解释1
例如，$(4,2,1,3)$ 不是一个 好排列，因为它包含 $(2,1)$  作为连续子序列。

其他非好排列包括 $(1,2,3,4)$ 和 $(3,4,2,1)$。

一些好排列包括 $(4,1,3,2)$ 和 $(2,3,4,1)$。其中，字典序最小的排列是 $(1,3,2,4)$。

### 样例解释2
好排列的示例包括 $(3,1,4,5,2)$、$(2,4,5,3,1)$ 和 $(4,1,5,2,3)$。

非好排列的示例包括 $(1,2,5,3,4)$、$(2,3,4,1,5)$ 和$(5,3,1,2,4)$。

### 样例解释3
不存在好排列，输出 `-1`。

## 样例 #1

### 输入

```
4 1
2```

### 输出

```
1 3 2 4```

## 样例 #2

### 输入

```
5 3
4 3 2```

### 输出

```
1 3 4 5 2```

## 样例 #3

### 输入

```
92 4
16 7 1 67```

### 输出

```
-1```

## 样例 #4

### 输入

```
43 2
43 2```

### 输出

```
-1```

# 题解

## 作者：yedalong (赞：2)

很不错的一道策略题。

## Solution

我们可以先考虑答案为 $-1$ 的情况。我们可以发现，当有 $A_i$ 中出现 $1$ 或 $N$ 时，不管怎么排列，都会没法达成条件，所以，当 $A_i$ 中出现了 $1$ 或 $N$ 时，答案为 $-1$。

接着我们可以先假设答案为 $1,2,…,N$，对于每一个 $A_i$，我们考虑怎样操作答案序列才能够使得字典序最小。很快就能发现，交换答案序列的第 $A_i$ 个位置和第 $A_{i+1}$ 个位置能够使得字典序最小。那怎样才能够判断当前的 $A_i$ 是否需要对答案序列进行操作呢？当我们从小到大排序完 $A$ 序列后，我们处理完 $A_i$ 后，对于 $A_{i+1}$ 来说，前面的只是换了一种排列而已，还需要操作，因此，连判断都不用判断了。。。

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[200005],ans[200005];
int main(){
    cin>>n>>m;
    for(int i = 1;i<=m;i++) cin>>a[i];
    sort(a+1,a+1+m);
    for(int i = 1;i<=n;i++) ans[i]=i;
    if(a[1]==1||a[m]==n) cout<<-1;
    else{
        for(int i = 1;i<=m;i++) swap(ans[a[i]],ans[a[i]+1]);
        for(int i = 1;i<=n;i++) cout<<ans[i]<<' ';
    }
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# AT_arc178_a [ARC178A] Good Permutation 2 题解

### 解析

首先考虑无解情况，易知 $\left \{ a \right \} $ 中含 $1$ 或 $n$ 一定无解。

题目中要求字典序最小，所以考虑贪心，并将 $\left \{ a \right \}$ 排序。

当遇到不行的情况时，将当前处理到的最后一个数与下一个数换位置即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5; 
int n,m;
int a[N],ans[N];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
		if(a[i]==1||a[i]==n){
			cout<<"-1"; return 0;
		}
	}
	for(int i=1;i<=n;i++){
		ans[i]=i;
	}
	sort(a+1,a+m+1);
	int pos=1;
	for(int i=1;i<=n;i++){
		if(a[pos]==i){ 
			swap(ans[i],ans[i+1]),pos++;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
return 0;
}
```

---

## 作者：Dtw_ (赞：1)

[at](https://atcoder.jp/contests/arc178/tasks/arc178_a)
# 题目大意
给定一个 $N$ 和 $M$ 个正整数 $A = (A_1,A_2,...A_M)$ 其中 $A_i$ 都是 $1$ 到 $N$ 之间不同的整数，求一个排列，满足他的任意连续子序列都不是 $(1,2,...A_i)$ 的排列。求这个字典序最小的满足要求的排列。

# 思路
首先，我们先判断他是否可以构造出来，那显然如果 $A_i = 1$ 或 $A_i = N$ 就是不行的，输出 $-1$。

然后现在就一定是可以构造出来一个合法的序列了。

因为要求字典序最小，所以我们应尽可能的按 $1$ 到 $N$ 的顺序去放，所以把 $A$ 排序。

接着，我们处理不行的情况。如果出现不行的情况，那么我们只要将这里面的任意一个数给踢出去就满足了。因为希望字典序最小，所以我们把最后一个数和他的下一个数交换，然后这个数就满足条件了。所以当一个区间不行的时候，我们将这个区间的最后一个数字去和他下一个数字交换，就行了。

时间复杂度：$O(m \log m + n)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

#define TRACE 1
#define tcout TRACE && cout

#define IN(o) insert(o)

#define fi first
#define se second

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, m;

int a[N];

int ans[N];

signed main()
{
	cin >> n >> m;
	for(int i=1; i<=m; i++)
	{
		cin >> a[i];
	}
	sort(a + 1, a + m + 1);
	if(a[1] == 1 || a[m] == n)
	{
		cout << -1;
		return 0;
	}
	for(int i=1; i<=n; i++)
	{
		ans[i] = i;
	}
	int j = 1;
	for(int i=1; i<=n; i++)
	{
		if(a[j] == i)
		{
			swap(ans[i], ans[i + 1]);
			j++;
		}
	}
	for(int i=1; i<=n; i++)
	{
		cout << ans[i] << " ";
	}
	return 0;
}



```

---

## 作者：ilibilib (赞：1)

## 分析：

我们容易想到当存在 $A_i=1$ 或 $A_i=n$ 时必然不存在可行解，直接输出 `-1`，这一点通过小样例可以验证。

然后要求字典序最小，我们考虑贪心，看每一位最小能放什么数。

为什么能贪心呢？

如果存在 $A_i=x$，肯定是放到第 $x$ 位再考虑，我们发现只要前 $x$ 位的最大值大于 $x$ 就能满足不是排列了。那么只要 $x\neq n$，必然能摆出一个大于 $n$ 的数，所以我们贪心不会导致不存在解了。

贪心策略：

序列由前到后生成，如果不存在 $A_i=x$，$x$ 位就摆没摆过的最小值，如果存在 $A_i=x$，判断一下当前最大值是不是大于 $x$，如果不是，摆出 $x+1$ 即可。

（最后我选择用 `bitset` 维护，喜提最劣解）

## code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N];
bool t[N];
bitset<N>b;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m,x,mx=1;
    bool f=true;
    cin>>n>>m;
    for(int i=1;i<=m;++i)
    {
        cin>>a[i];
        t[a[i]]=true;
        if(a[i]==n) f=false;
        if(a[i]==1) f=false;
    }
    if(!f) {cout<<-1;return 0;};
    cout<<1<<' ';
    b.set();
    b.reset(0);
    b.reset(1);
    for(int i=2;i<=n;++i)
    {
        x=b._Find_first();
        mx=max(mx,x);
        if(t[i]&&mx<=i) x=b._Find_next(i),mx=max(mx,x);
        cout<<x<<' ',b.reset(x);
    }
    cout<<endl;
    return 0;
}
```

---

## 作者：Heldivis (赞：1)

# ARC178A

由于询问最小字典序，考虑贪心。

将答案数组赋初值为 $1,2,\dots,n$，将约束条件 $a_i$ 从小到大排序。

对于每一个 $x\in a$，因为每一个排列必须包含 $1$，所以就让 $res_1,res_2\dots,res_x$ 不是一个排列。

每次交换 $res_x$ 和 $res_{x+1}$ 可以保证符合要求，且字典序最小。

再考虑无解的情况。

- 如果 $x = n$，则对于整个答案排列，一定是一个不符合这一要求的。
- 如果 $x=1$，则对于答案中子序列 $\{1\}$，同样无法满足。

*Code:*

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int read() {...}
signed main() {
  int n = read(), m = read();
  vector<int> a(m), res(n);
  for (int &i : a) {
    i = read();
    if (i == 1 || i == n)
      return 0 * printf("-1");
  }
  sort(a.begin(), a.end());
  for (int i = 0; i < n; i++)
    res[i] = i + 1; 
  for (int i : a)
    swap(res[i], res[i - 1]);
  for (int i : res)
    printf("%lld ", i);
  return 0;
}
```

---

## 作者：xk2013 (赞：0)

题目传送门：[AT_arc178_a [ARC178A] Good Permutation 2](/problem/AT_arc178_a)

## 前置知识
- 贪心。

## 题意简述
本题要求我们构造出符合要求的字典序最小的“好排列”。

## 解题思路
首先考虑无解的情况，注意到 $a$ 中含有 $1$ 或 $n$ 时，无论如何构造最终的排列总是会包含 $1$ 或 $n$ 的排列，此时就无解。

然后考虑如何构造。因为要求是字典序最小，所以我们可以把 $a$ 升序排序，这样构造出的排列字典序是最小的。接着，我们先按照 $1 \sim n$ 存下答案，然后判断是否符合条件，这个步骤需要解决两个问题：
1. 怎么判断是否符合条件？
2. 不符合条件怎么修改答案？

首先回答第一个问题，由于我们排过序了，因此我们设一个变量 $pos$，表示当前要寻找的排列，这样子不会遗漏情况。当 $a_{pos} = i$ 时说明前 $i$ 位就是 $a_{pos}$ 的排列，说明答案不合法。

那不符合条件怎么修改答案呢？把它和后一位交换即可，这样前 $i$ 位就不构成 $a_i$ 的排列了，且这样也是字典序最小的。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <algorithm>
#include <cstdio>

const int N = 2e5 + 5, M = 2e5 + 5;
int n, m, pos = 1, a[M], ans[N];

int main(void)
{
	scanf("%d %d", &n, &m);
	
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &a[i]);
		
		if (a[i] == 1 || a[i] == n) // 判断无解
		{
			printf("-1");
			return 0;
		}
	}
	
	for (int i = 1; i <= n; i++) // 初始化答案
	{
		ans[i] = i;
	}
	
	std::sort(a + 1, a + m + 1); // 排序
	
	for (int i = 1; i <= n; i++)
	{
		if (a[pos] == i) // 判断
		{
			std::swap(ans[i], ans[i + 1]);
			pos++; // 记得加一
		}
	}
	
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", ans[i]);
	}
	
	return 0;
}

```
----------------------
这是本五年级蒟蒻小学生的第 20 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2025/01/05：初版。

---

## 作者：fydj (赞：0)

## 思路

当 $A$ 中存在 $1$ 或 $N$​，无解，否则考虑贪心。

把 $1$ 到 $N$ 中的数放进 ```set``` 里面，从前往后填。

假设填到第 $i$ 位，如果有 $A_i$ 这个限制，那么这一位填大于 $i$​ 的最小的数（没有这样的数就无解，但不会有这种情况）；反之填可以填的最小的数。

## 代码

```cpp
int n,m,a[N]={},ans[N]={}; set<int> S={}; bool is[N]={};
int main()
{
	int i;
	read(n,m);
	for(i=1;i<=m;++i)
		read(a[i]),is[a[i]]=true;
	if(is[1]||is[n]) {
		printf("-1\n");
		return 0;
	}
	for(i=1;i<=n;++i)
		S.insert(i);
	for(i=1;i<=n;++i)
		if(is[i]) {
			auto its=S.lower_bound(i+1);
			if(its==S.end()) {
				printf("-1\n");
				return 0;
			}
			ans[i]=*its,S.erase(its);
		} else {
			auto its=S.begin();
			ans[i]=*its,S.erase(its);
		}
	for(i=1;i<=n;++i)
		printf("%d ",ans[i]);
	printf("\n");
	return 0;
}
```

---

## 作者：Sirkey (赞：0)

做法很简单，主要思路是贪心。

先把 $a$ 数组给排个序，我们就可以线性的搞。

开一个数组 $b$，其中第 $i$ 个就等于 $i$。考虑依照题目进行修改。

$a$ 中出现的数在 $b$ 中可以说是都满足了，我们让他不满足。只需要将 $b$ 中的第 $a_i$ 个换到后面去。

很明显这是最小的字典序，因为我们每一次都挪动的最小的。另外可以反证，所有数分为被移动过和没被移动过。没被移动过的向前移一定不会更优，移动过的向前移一定不满足。故最优。

另外就是判是否无解，很显然，当 $a$ 数组总存在 $n$ 或者 $1$ 的时候无法通过任何方式得到答案。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define debug(x) cout<<#x<<":"<<x,puts("");
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
//
//
//
using namespace std;
inline ll read() {
	ll f = 0, t = 0;
	char c = getchar();
	while (!isdigit(c)) t |= (c == '-'), c = getchar();
	while (isdigit(c)) f = (f << 3) + (f << 1) + c - 48, c = getchar();
	return t ? -f : f;
}
const int MX = 3e5 + 10;
int a[MX];
int b[MX];
int main() {
	ios::sync_with_stdio(0), cout.tie(0);
	int n = read(), m = read();
	FOR(i, 1, m) {
		a[i] = read();
		if (a[i] == 1 || a[i] == n)  return cout << -1, 0;
	}
	sort(a + 1, a + m + 1);
	int walk = 1;
	FOR(i, 1, n) b[i] = i;
	FOR(i, 1, n) {
		if (a[walk] == i) swap(b[i], b[i + 1]), walk++;
	}
	FOR(i, 1, n) cout << b[i] << " ";
	return 0;
}

```

——end——

---

