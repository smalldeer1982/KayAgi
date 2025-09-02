# Index and Maximum Value

## 题目描述

Index 在生日派对上收到了另一个整数数组 $a_1,a_2,\dots,a_n$。随后，她准备对这个数组进行一些操作。

形式化地，她决定对这个数组执行 $m$ 次操作。有两种操作类型：
- 第一种操作形如 $\texttt{+ l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i+1$。
- 第二种操作形如 $\texttt{- l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i-1$。

举个例子，如果给定的数组 $a$ 初始为 $[7,1,3,4,3]$，在执行操作 $\texttt{+ 2 4}$ 后，数组变为 $a=[7,1,4,5,4]$。然后，在执行操作 $\texttt{- 1 10}$ 后，数组变为 $a=[6,0,3,4,3]$。

Index 对 $a$ 数组的最大值很好奇。在每次操作之后，请告诉她 $a$ 数组中的最大值。

## 样例 #1

### 输入

```
5
5 5
1 2 3 2 1
+ 1 3
- 2 3
+ 1 2
+ 2 4
- 6 8
5 5
1 3 3 4 5
+ 1 4
+ 2 3
- 4 5
- 3 3
- 2 6
5 5
1 1 1 1 1
+ 2 3
- 4 5
+ 1 6
- 2 5
+ 1 8
1 1
1
- 1 1
1 1
1000000000
+ 1000000000 1000000000```

### 输出

```
4 4 4 5 5
5 5 4 4 3
1 1 2 1 2
0
1000000001```

# 题解

## 作者：wangzhaohan2910 (赞：5)

## 分析

没错，你没看错，它就是一道橙题。妥妥的一道诈骗题。

仔细思考，不难得出，只要求出了原序列的最大值，后面只用计算与最大值有关的操作就行了。因为别的数不可能在不进行与最大值有关的操作的情况下超过最大值，最大值那一档的数被减小了以后也不会有数比它大。

**结论**：只考虑最大值。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int r[100005];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m,maxn{};
		cin>>n>>m;
		for(int i{1};i<=n;i++)
		{
			cin>>r[i];
			if(r[i]>maxn)
				maxn=r[i];
		}
		while(m--)
		{
			char c;
			int l,r;
			cin>>c>>l>>r;
			if(l<=maxn&&r>=maxn)
				if(c=='+')
					maxn++;
				else
					maxn--;
			cout<<maxn<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Lfz312g (赞：2)

# CF2007B Index and Maximum Value
## 题意简析
给出一个长度为 $n$ 的数列 $a$，对其进行 $m$ 次操作，每次选择两个整数 $l$ 和 $r$，使所有 $l\le a_i \le r$，加 $1$ 或减 $1$，求每次操作后数列 $a$ 的最大值。
## 题目分析
诈骗题。每次进行操作后必定和原数列的最大值有关。  
所有小于最大值的数，在经过若干次操作后必定无法超过最大值，因为当其与最大值相等时，该数必定和最大值同时受到操作影响。  
## 代码实现
记录下最大值，简单模拟即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void solve()
{
	int n,m;
	ll mx=-1;
	cin>>n>>m;
	for (int i=1;i<=n;i++) 
	{
		ll x;
		cin>>x;
		mx=max(mx,x);
	}
	while (m--)
	{
		char opt;
		int l,r;
		cin>>opt>>l>>r;
		if (mx>=l&&mx<=r) 
		{
			mx+=(opt=='+'?1:-1);
		}
		cout<<mx<<" ";
	}
	putchar('\n');
}
int main()
{
	int t;
	cin>>t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：chenxi2009 (赞：2)

# 思路

纯诈骗题。

只有当一次操作中，$l\le \max a\le r$ 时，题目所求的最大值才会受影响。所以我们先找出最大值，然后舍弃 $a$，每次判断操作是否改变了最大值即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[100001],mx,l,r;
char c;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%d%d",&n,&m);
		mx = 0;
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
			mx = max(mx,a[i]);
		}
		for(int i = 1;i <= m;i ++){
			c = 0;
			while(c != '+' && c != '-'){
				c = getchar();
			}
			scanf("%d%d",&l,&r);
			if(l <= mx && r >= mx){
				mx += c == '+' ? 1 : -1;
			}
			printf("%d ",mx);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：lichenxi111 (赞：1)

一道很好的思维题。

## 题意

两种操作：

- 第一种操作形如 $\texttt{+ l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i+1$。
- 第二种操作形如 $\texttt{- l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i-1$。

问每执行完一次操作后序列中的最大值。

## 思路

输出最大值，那么考虑最大值有什么性质，发现对于相等的数，无论是操作 $1$ 还是操作 $2$，这些相等的数还是相等，因为它们都同样地 $+1$ 或 $-1$，推而广之，当一个不是最大值的数，无论他怎样地 $+1$，他肯定在某次操作后，变为最大值，而根据上文的结论，他之后会一直与最大值相等，对于其他数亦是如此，那么得：所有数不会超过最大值。

我们只需要维护最大值，答案也一定是这个值。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int n,m;
		cin >> n >> m;
		int ans = 0;
		for(int i = 1;i <= n;i++)
		{
			int x;
			cin >> x;
			ans = max(ans,x);
		}
		while(m--)
		{
			char op;
			int l,r;
			cin >> op;
			cin >> l >> r;
			if(op == '+')
			{
				if(l <= ans && ans <= r)
				{
					ans++;
				}
			}
			else
			{
				if(l <= ans && ans <= r)
				{
					ans--;
				}
			}
			cout << ans << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF2007B)

纯诈骗题，看着挺难，其实非常的 water。

### 题目大意
现在有一个长度为 $n$ 的数组 $a$，有 $m$ 次询问，对于每一次询问，将所有的 $a_i$ 满足 $l \le a_i \le r$ 都 $+1$ 或 $-1$，求每次操作后的最大值。

### 解题思路
首先容易想到每次操作都跟最大值有关。设操作前最大值为 $k$。易得出结论：
+ 若 $l \le k \le r$，则最大值为 $k \pm 1$；
+ 若 $k \gt r$，则最大值为 $k$。

下面给出证明：

第一条结论不难理解。

对于第二条结论，设当前满足 $a_i \le r$ 的 $a_i$ 的最大值为 $g$，显然 $g \lt k$。则在操作后，若 $g=k$，则接下来的最大值仍然为 $k$；若 $g<k$，最大值显然也为 $k$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,x,maxn,l,r;
char op;
int main(){
	cin>>T;
	while(T--){
		maxn=0;
		cin>>n>>m;
		while(n--){
			cin>>x;
			maxn=max(maxn,x);
		}
		while(m--){
			cin>>op>>l>>r;
			if(maxn>=l&&maxn<=r){
				if(op=='+') maxn++;
				else maxn--;
			}
			cout<<maxn<<' ';
		}
		cout<<endl;
	}
}
```

---

## 作者：__Immorta__ (赞：0)

## 纯文字题解

前言：楼上大佬的正解已经够多，蒟蒻就不多叙述了，这里提供一个详细的思维逻辑，仅供参考。

**题目大意：**

- 输入 $n$ 和 $m$ ，然后给定 $n$ 个数字。
- 循环 $m$ 次，每次输入一个字符，两个数字 $a$ 和 $b$ 。
- 当字符为 $+$ 号，数组区间 $a$ 到 $b$ 的数字 $+1$ 。
- 当字符为 $-$ 号，数组区间 $a$ 到 $b$ 的数字 $-1$ 。
- 输出每次操作后数组内的最大值。
- **一共有 $T$ 组测试**

**特殊要求：**

数组下标从 $0$ 开始！

**输入格式：**

首先输入一个整数 $T$ ，代表一共 $T$ 组数据。
- 接下来分为 $T$ 组，每组输入 $n,m,c,a,b$ ，分别代表了数组长度 $(n)$ 、加减的次数 $(m)$ 、加或减的操作 $(c)$ 、区间操作起点 $(a)$ 、区间操作终点 $(b)$ 。

**输出格式：**

每组数据输出一行。

分别代表 $m$ 次操作中每次操作后当前数组的最大值

**思维分析：**

- 输入以后，使用一个循环，依次循环 $T$ 次，每次输入 $n$ 和 $m$ ，分别循环 $n$ 和 $m$ 次，输入数组和增减数据。

- 每次根据输入的 $c$ 来确定是做增加操作还是减少操作，这里有三种思路：差分前缀和 $or$ 暴力 $or$ 数组。

- 小优化/偷懒方法/容易理解：可以使用一个数组 $sum$ 。因为只需要输出当前数组的最大值，可以在输入的时候先找出原数组最大值，然后在每次增减的时候判断，如果在范围内，$sum$ 增加或者减少，以此方法输出最大值。

**基础代码：**

```c
#include <bits/stdc++.h>
using namespace std;
int ans[1000005];
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		int n,m;
		cin>>n>>m;
		for(int j=1;j<=n;j++){//输入数组 
			cin>>ans[i];
		}
		for(int j=1;j<=m;j++){//输入 
			int c,a,b;
			cin>>c>>a>>b;
		}
	}
	return 0;
}

```

**仅供参考**

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF2007B](https://www.luogu.com.cn/problem/CF2007B) || [CodeForces 2007 B](https://codeforces.com/contest/2007/problem/B)

### 简要题意

维护一个序列，每次给定 $[l,r]$，表示将值在 $[l,r]$ 内的数都 $+1$ 或 $-1$，并查询全局最大值。

### 思路

显然原序列中的最大值在操作后同为最大值，所以只需要对最大值进行操作模拟即可。

证明如下：

选取一个小于等于最大值的元素 $a_x(a_x\le a_{max})$。

- 如果是 $x = a_{max}$，那么 $x = a_{max}$ 在操作之后仍然成立。
- 否则为 $x < a_{max}$。

那么，$a_{max}$ 仍然是最大值。

时间复杂度：$\mathcal O(n + q)$。

```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n,m,maxx=0,x, l, r;
        char c;
        cin >> n >> m;
        while(n--) 
        {
            cin >> x;
            maxx=max(maxx,x);
        }
        while(m--)
        {
            cin >> c >> l >> r;
            if (maxx >= l && maxx <= r)
                if (c == '+') maxx++;
                else maxx--;
            cout << maxx << ' ';
        }
    }
}
```

---

## 作者：Link_Cut_Y (赞：0)

这道题能放在第二题，说明这不会是数据结构题。

只要求求出最大值，这是一个提示。

考虑操作：如果当前数组的最大值 $> r$，则该操作对最大值没有影响。如果当前数组的最大值 $< l$，则该操作对最大值没有影响。这是显然的。

对于当前最大值在 $l \sim r$ 范围内的情况，等价于对最大值进行操作。这是因为，设 $m = \max\{a_i\}$。如果是加操作，则 $\forall a_i < m$，$a_i + 1 \le m$。同样的，如果是减操作，$\forall a_i \le m, a_i - 1 \le m - 1$。

复杂度线性。[Submission](https://codeforces.com/contest/2007/submission/278789859)。

---

## 作者：Pollococido (赞：0)

小模拟。
### 题目链接
[here](https://www.luogu.com.cn/problem/CF2007B)

### 分析
操作只有两种。

要么是 $\texttt{+ l r}$ 或 $\texttt{- l r}$。

假设 $\max_{i=1}^{n} a_i = maxx$。

则有以下几种情况。
### 第一种
$maxx \notin [l,r]$。

则 $maxx$ 无变化。
### 第二种
输入为 $\texttt{+ l r}$ 且 $maxx \in [l,r]$。

那么 $maxx \gets maxx+1$。
### 第三种
输入为 $\texttt{- l r}$ 且 $maxx \in [l,r]$。

那么 $maxx \gets maxx-1$。

---------------分割一下---------------

现在就可以~~愉悦的~~写代码了。

**△Code**

码风自认为良好。
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, q, l, r;
int x;
char opt;

int main() {
    cin >> t;
    while (t--) {
        int maxx = -0x3f3f3f3f;
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> x, maxx = max(maxx, x);
        while (q--) {
            cin >> opt >> l >> r;
            if (l <= maxx && r >= maxx) {
                if (opt == '+') maxx++;
                else maxx--;
            }
            cout << maxx << " ";
        }
        cout << endl;
    }
    return 0;
}
```

照抄小心 cz 暴政。

---

## 作者：YangXiaopei (赞：0)

## Solution:

考虑到只要求最大值，而且数的改变也是在值域上的。

也就是说，一个比最大值小的数，一旦变得和最大值一样后，最大值也会和它一起变动，也就是说不会有任何数会在原来比最大值小的情况下变得比最大值大。

所以我们只要记录最大值的变动情况即可。

时间复杂度 $\mathcal{O}(T(m + n))$。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T, n, m, l, r, maxn, a[100005];
char ch;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T--){
		cin >> n >> m;
		int maxn = 0;
		for(int i = 1; i <= n; i++){
			cin >> a[i];
			maxn = max(maxn, a[i]);
		}
		while(m--){
			cin >> ch >> l >> r;
			if(l <= maxn && maxn <= r){
				if(ch == '+'){
					maxn++;
				}
				else{
					maxn--;
				}
			}
			cout << maxn << " ";
		}
		cout << "\n";
	}
	return 0;
}

```

---

## 作者：mc_xiexie (赞：0)

### 题意

给你个序列 $a_1,a_2,\dots,a_n$。对它进行操作。

- $\texttt{+ l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i+1$。

- $\texttt{- l r}$。给定两个正整数 $l,r$，将所有满足 $1\le i\le n,l\le a_i\le r$ 的 $a_i$ 的值改为 $a_i-1$。

注意是 $1\le i\le n,l\le a_i\le r$，这卡我 $5$ 分钟。

既然是将值在 $1\le i\le n,l\le a_i\le r$，所以在最大值以下的值不管怎么样都没法超过最大值，我们就只要看最大值的变化就好了。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
    int T;
    cin>>T;
    while(T--){
        int n,m,maxn=-1;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            maxn=max(maxn,x);
        }
        while(m--){
            char c;
            int l,r;
            cin>>c>>l>>r;
            if(c=='-' && maxn>=l && maxn<=r){
               	maxn--;
            }
            if(c=='+' && maxn>=l && maxn<=r){
               	maxn++;
        	}
            cout<<maxn<<" ";
        }
        cout<<"\n";
    }
    return 0;
}

```

---

## 作者：masonxiong (赞：0)

# 题目分析

假设我们已知 $a$ 数组目前的最大值 $maxv$，那一次操作就可以分成四种情况。

---

## 情况 1

$$ \texttt{+ l r}(l\le maxv\le r) $$

此时最大值变为 $maxv+1$。

证明：

首先，因为 $l\le maxv\le r$ 所以 $maxv$ 肯定被修改了，其新值 $maxv+1$ 肯定在 $a$ 中，因此**新最大值不可能比 $maxv+1$ 小。**

其次，假设存在 $v+1>maxv+1$，则有 $v>maxv$，与我们的假设矛盾，因此**新最大值不可能比 $maxv+1$ 大。**

---

## 情况 2

$$ \texttt{- l r}(l\le maxv\le r) $$

此时最大值变为 $maxv-1$。

证明：

首先，因为 $l\le maxv\le r$ 所以 $maxv$ 肯定被修改了，其新值 $maxv-1$ 肯定在 $a$ 中，因此**新最大值不可能比 $maxv-1$ 小。**

其次，假设存在 $v-1>maxv-1$，则有 $v>maxv$，与我们的假设矛盾，因此**新最大值不可能比 $maxv+1$ 大。**

---

## 情况 3

$$ \texttt{+ l r}(maxv<l\lor r<maxv) $$

此时最大值仍然为 $maxv$。

证明：

首先，因为 $maxv<l\lor r<maxv$ 所以 $maxv$ 没有被修改，其新值 $maxv$ 肯定在 $a$ 中，因此**新最大值不可能比 $maxv$ 小。**

其次，假设存在 $v+1>maxv$，则有 $v\ge maxv$，与我们的假设矛盾，因此**新最大值不可能比 $maxv$ 大。**

---

## 情况 4

$$ \texttt{- l r}(maxv<l\lor r<maxv) $$

此时最大值仍然为 $maxv$。

证明：

首先，因为 $maxv<l\lor r<maxv$ 所以 $maxv$ 没有被修改，其新值 $maxv$ 肯定在 $a$ 中，因此**新最大值不可能比 $maxv$ 小。**

其次，假设存在 $v-1>maxv$，则有 $v\ge maxv+1$，与我们的假设矛盾，因此**新最大值不可能比 $maxv$ 大。**

---

# 题目做法

根据刚刚的分析，我们知道：
- **如果我们知道了数组 $a$ 目前的最大值，对于一次操作后，数组 $a$ 新的最大值我们能够非常容易地得到。**

因此我们只需要一直维护数组 $a$ 的最大值即可。

分析一下时空复杂度：
- 时间复杂度：$O(\sum n+\sum m)$。因为每一次操作后我们更新最大值的时间复杂度是 $O(1)$ 的，读入是 $O(n)$ 的。
- 空间复杂度：$O(1)$。我们并不需要存储数组，只需要维护最大值就行。

---

# 代码

压行有点严重。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	char option;
	int t, n, m, a, v, l, r;
	for (cin >> t; t--; cout << '\n') {
		v = 0;
		for (cin >> n >> m; n--; cin >> a, v = max(v, a));
		while (m--) {
			cin >> option >> l >> r;
			if (l <= v && v <= r)
				v += option == '+' ? 1 : -1;
			cout << v << ' ';
		}
	}
	return 0;
}
```

---

