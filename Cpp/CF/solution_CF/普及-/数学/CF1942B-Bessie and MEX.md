# Bessie and MEX

## 题目描述

[MOOO! - Doja Cat](https://soundcloud.com/amalaofficial/mooo)

⠀



Farmer John has a permutation $ p_1, p_2, \ldots, p_n $ , where every integer from $ 0 $ to $ n-1 $ occurs exactly once. He gives Bessie an array $ a $ of length $ n $ and challenges her to construct $ p $ based on $ a $ .

The array $ a $ is constructed so that $ a_i $ = $ \texttt{MEX}(p_1, p_2, \ldots, p_i) - p_i $ , where the $ \texttt{MEX} $ of an array is the minimum non-negative integer that does not appear in that array. For example, $ \texttt{MEX}(1, 2, 3) = 0 $ and $ \texttt{MEX}(3, 1, 0) = 2 $ .

Help Bessie construct any valid permutation $ p $ that satisfies $ a $ . The input is given in such a way that at least one valid $ p $ exists. If there are multiple possible $ p $ , it is enough to print one of them.

## 说明/提示

In the first case, $ p = [0, 1, 4, 2, 3] $ is one possible output.

 $ a $ will then be calculated as $ a_1 = \texttt{MEX}(0) - 0 = 1 $ , $ a_2 = \texttt{MEX}(0, 1) - 1 = 1 $ , $ a_3 = \texttt{MEX}(0, 1, 4) - 4 = -2 $ , $ a_4 = \texttt{MEX}(0, 1, 4, 2) - 2 = 1 $ , $ a_5 = \texttt{MEX}(0, 1, 4, 2, 3) - 3 = 2 $ .

So, as required, $ a $ will be $ [1, 1, -2, 1, 2] $ .

## 样例 #1

### 输入

```
3
5
1 1 -2 1 2
5
1 1 1 1 1
3
-2 1 2```

### 输出

```
0 1 4 2 3 
0 1 2 3 4 
2 0 1```

# 题解

## 作者：luobotianle (赞：6)

由题意得 $p$ 满足从 $0$ 到 $n-1$ 的每个整数各出现一次，所以有 $\operatorname{MEX}\{p_1,p_2,\ldots,p_n \}=n$，所以  $p_n=n-a_n$；然后从后往前更新，推出 $p$ 数组即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N],p[N]; 
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int mex=n;
		for(int i=n;i>=1;i--){
			p[i]=mex-a[i];
			mex=min(mex,p[i]);
		}
		for(int i=1;i<=n;i++)cout<<p[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

## 题解：CF1942B Bessie and MEX
## 思路
由题意可知，$p$ 满足从 $1$ 到 $n - 1$ 的每个整数各出现一次，且变量 $mex$ 是非负最小值，所以 $p_n =  mex-a_n$，我们从后往前倒推出 $p$ 数组即可。
## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
#define pb emplace_back
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;

ll T, n, i, j;
ll a[MAXN], p[MAXN];

int main()
{
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
    while (T--)
    {
    	cin>>n;
		for (i = 1; i <= n; i++)
		{
			cin >> a[i];
		} 
		ll mex = n;
		for (i = n; i >= 1; i--)
		{
			p[i] = mex - a[i];
			mex = min(p[i], mex);
		}
		for (i = 1; i <= n; i++)
		{
			cout << p[i] << " ";
		}
		cout << endl;
	}
	return 0;
}

```

---

## 作者：zhanglh (赞：1)

序列 $p_1, p_2, ..., p_n$ 满足 $0$ 到 $n - 1$ 的每个整数恰好出现一次（$p_i \in [0, n - 1]$），所以必然有 $\text{MEX}\{p_1, p_2, ..., p_n\} = n$。

因为 $a_i = \text{MEX}\{p_1, p_2, ..., p_i\} - p_i$，所以 $p_i = \text{MEX}\{p_1, p_2, ..., p_i\} - a_i$。因此 $p_n = n - a_n$，唯一确定。

考虑从后往前做，这样每个位置就是唯一确定的了。时间复杂度 $O(n)$。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>

using namespace std;

const int N = 200010;

int n, a[N], p[N];
set<int> s;

void solve()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);
    memset(p, 0, sizeof p);
    p[n - 1] = n - a[n - 1];
    s.clear();
    s.insert(p[n - 1]);
    for (int i = n - 2; i >= 0; i -- )
    {
        p[i] = *s.begin() - a[i];
        s.insert(p[i]);
    }
    for (int i = 0; i < n; i ++ ) printf("%d ", p[i]);
    puts("");
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T -- ) solve();
    return 0;
}
```

---

## 作者：Furina_Hate_Comma (赞：0)

一道**构造**题。

使用 `set` 维护 $\mathrm{mex}$ 值。

每次按照式子算出当前 $p_i$，但是此时如果加入 $p_i + 1$ 后 $\mathrm{mex}$ 改变，则重新计算并判断是否等于 $p_i + 1$。否则就直接加入 $p_i$。

code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010;

int a[N], ans[N];
void solve(){
	set<int> st;
	int n, mx = 0;
	cin >> n;
	for(int i = 0 ; i <= n + 5 ; i ++) st.insert(i); 
	for(int i = 1 ; i <= n ; i ++) cin >> a[i];
	for(int i = 1 ; i <= n ; i ++){
		int p = mx - a[i], tmp = mx;
		st.erase(mx);
		ans[i] = mx;
		mx = *st.begin();
		// cout << mx << '\n';
		if(mx - a[i] == tmp)
			continue;
		st.insert(tmp);
		ans[i] = p;
		st.erase(p);
		mx = *st.begin();
	}
	for(int i = 1 ; i <= n ; i ++) cout << ans[i] << ' ';
	cout << '\n';
}

signed main(){
	int t;
	cin >> t;
	while(t --)
		solve();

	return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

给定一个长度为 $n$ 的数组 $a$，让你构造一个等长的排列 $p$，其中从 $0$ 到 $n-1$ 的每个整数恰好出现一次。满足对于每一个位置 $a_i=\texttt{MEX}(p_1,p_2, \ldots, p_i) - p_i$，其中数组的 $\texttt{MEX}$ 是不在该数组中出现的最小非负整数。

## 题目分析

我们发现正着做并不是十分好做，依据**正难则反**的思想，我们考虑倒着做。

我们首先考虑构造 $p_n$。为了方便一些，我们令 $mex_i=\texttt{MEX}(p_1, p_2, \ldots, p_i)$。因为 $p$ 是一个从 $0$ 到 $n-1$ 的排列，所以 $mex_n=n$，由于 $a_i=mex_i-p_i$，所以可以推出 $p_n=mex_n-a_n$，这样我们就知道了 $p_n$ 的值。对于其他的 $p_i$，我们也可以效仿这种方法。现在，我们只需要知道 $mex_i$ 就可以了。

我们考虑如何求解 $mex_i$，首先，我们求 $p_i$ 的值的时候，肯定已经知道了 $p_{i+1} \sim p_n$ 的值了，由于 $p$ 是一个排列，所以在 $p_1 \sim p_i$ 中 $p_{i+1} \sim p_n$ 一定没有出现过且不可能出现大于 $p_{i+1} \sim p_n$ 的数，再根据 $\texttt{MEX}$ 的定义，我们便可知 $mex_i=\min_{i+1 \leq j \leq n~}{p_j}$。然后这道题就做完了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,a[N],p[N],mex;
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	} 
	mex=n;
	for(int i=n;i>=1;i--)
	{
		p[i]=mex-a[i];
		mex=min(p[i],mex);
	}
	for(int i=1;i<=n;i++)
	{
		cout<<p[i]<<" ";
	}
	cout<<"\n";
	return;
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>T;
    while(T--)
    {
    	solve();
	}
	return 0;
}
```

---

## 作者：王逸辰 (赞：0)

# CF1942B Bessie and MEX 题解
## 思路
由题意可知，$p$ 从 $0$ 到 $n-1$ 各出现一次，又因 mex 是非负最小值，所以我们只需从 $n-1$ 倒推即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200010],s[200010],mex;
int main(){
	scanf("%d",&T);
	for(int ii=(0); ii<T; ii++){
		scanf("%d",&n);
		mex=n;
		for(int i=(0); i<n; ++i)
			scanf("%d",a+i);
		for(int i=(n-1); i>=0; --i)
			s[i]=mex-a[i],mex=min(mex,s[i]);
		for(int i=(0); i<n; ++i)
			printf("%d ",s[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：L_xcy (赞：0)

[Bessie and MEX](https://codeforces.com/problemset/problem/1942/B)

---

### 题目大意

有一个排列 $p_1$ 到 $p_n$，其中 $0$ 到 $n-1$ 正好出现一次。

定义 $a_i$ 表示 $\textrm{MEX}(p_1,\cdots ,p_n)$ (不知道 $\textrm{MEX}$ 的可以看 [这篇文章](https://zhuanlan.zhihu.com/p/448147128) )，再给出 $a_i$，求 $p_i$。

---

### 解题思路

很明显 $\textrm{MEX}$ 肯定是不降的，我用一个 $ans$ 数组表示 $\textrm{MEX}(p_1,\cdots ,p_n)$，此时就可以用 $\textrm{MEX}$ 的性质求 $ans_i$。

当 $a_i < 0$ 时，$ans_i = ans_{i-1}$。

当 $a_i > 0$ 时，$ans_i = ans_{i-1} + a_i$。

最后输出 $ans_i - a_i$ 即可。

时间复杂度为 $O(n)$。

---

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void solve() {
	int n,a[200005],ans[200005];
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		if(a[i]<0) {
			ans[i]=ans[i-1];
		}
		else {
			ans[i]=ans[i-1]+a[i];
		}
	}
	for(int i=1;i<=n;i++) {
		cout<<ans[i]-a[i]<<' ';
	}
	cout<<'\n';
} 
int main() {
	cin>>T;
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：ylch (赞：0)

[Luogu - CF1942B](https://www.luogu.com.cn/problem/CF1942B) 

## part1. 题目大意

有一个**排列** $p_{1},p_{2},p_{3},\cdots,p_{n}$，其中每个 $0 \sim n-1$ 的数刚好出现一次。现有长度为 $n$ 的数组 $a$，满足 $a_i=\operatorname{MEX}\{p_{1},p_{2},\cdots,p_{i}\}-p_{i}$，要求根据 $a$ 构造 $p$。

## part2. 解题思路

题目给定 $a_{i}=\operatorname{MEX}\{p_{1},p_{2},\cdots,p_{i}\}-p_{i}$，

观察题目中样例数据：

$a=[1,1,-2,1,2]$

$p=[0,1,4,2,3]$

$mex=[1,2,2,3,5]$

先考虑前缀 $\operatorname{MEX}$ 的性质，一定是不降的，具有一定的单调性。

设 $mex_{i}=\operatorname{MEX}\{p_{1},p_{2},\cdots,p_{i}\}$

考虑 $\operatorname{MEX}$ 一定不可能等于其中的元素，所以 $mex_{i} \neq p_{i}$, 只有可能大于或小于。

考虑 $a_{i}<0$ 时，$mex_{i}<p_{i}$, 此时 $mex_{i}=mex_{i-1}$；

若 $a_{i}>0$，此时 $0 \sim p_{i}$ 一定全部集齐，$mex_{i}>p_{i}$, $mex_{i}=mex_{i-1}+a_{i}$。

## part3. 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

void solve()
{
	int n;
	cin >> n;
	vector <int> a(n + 1), mex(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		if(a[i] < 0) mex[i] = mex[i - 1];
		else mex[i] = mex[i - 1] + a[i]; // a[i]>0
	}
	for(int i = 1; i <= n; i ++){
		// a[i]=mex[i]-p[i] -> p[i]=mex[i]-a[i]
		cout << mex[i] - a[i] << ' ';
	}
	cout << "\n";
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T; cin >> T;
	while(T --) solve();
	return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！

---

## 作者：hyman00 (赞：0)

### 题意

对于一个排列 $\set{p_n}$，其中 $0,1,\dots,n-1$ 恰好出现一次。

定义数列 $a_i=\operatorname{MEX}(p_1,\dots,p_i)-p_i$，给定数列 $\set{a_i}$，请求出 $\set{p_i}$，保证有解。

$1\le n\le 2\times10^5,-n\le a_i\le n$ 

### 做法

方法一：

可以从后往前求出答案

对于 $a_{n}$，一定有 $\operatorname{MEX}(p_1,\dots,p_{n})=n$，就可以求出 $p_n$，接着就可以求出 $\operatorname{MEX}(p_1,\dots,p_{n-1})$ 的值……

就可以唯一确定答案，复杂度 $O(n)$。

方法二（赛时思路）：

从做往右求答案，用一个 set 维护当前没有用过的数，记当前没用过的最小的数为 $c$。

如果 $a_i<0$，则 $\operatorname{MEX}(p_1,\dots,p_i)=c,p_i=c-a_i$，否则 $\operatorname{MEX}(p_1,\dots,p_i)=c+a_i,p_i=c$，并从 set 里删除 $p_i$ 。

### 推广

赛时没有看到一定是排列的限制，这题还能做吗？

考虑继续用方法二的思路，记当前没用过的最小的数为 $c$，第二小的为 $d$。

如果 $a_i<0$ 是相同的，那么 $p_i=c-a_i$。

否则，就有两种决策，要么 $p_i=c-a_i$，要么 $p_i=c$，这要求 $d=c+a_i$，这里应尽可能选第二种。可以感性理解就是让以后的 $c$  尽量大，以防出现 $a_i$ 负得很多的情况。

复杂度 $O(n\log n)$。

##### 赛时代码

```c++
int n,a[200005],s[200005];
set<int>st;
void run(){
	cin>>n;
	st.clear();
	rep(i,n+2)st.insert(i);
	rep(i,n){
		cin>>a[i];
		if(a[i]<0){
			s[i]=(*st.begin())-a[i];
		}
		else{
			int s1=(*st.begin()),s2=*next(st.begin());
			if(s2-s1==a[i])
				s[i]=s1;
			else
				s[i]=s1-a[i];
		}
		st.erase(s[i]);
	}
	rep(i,n){
		cout<<s[i]<<" ";
	}
	cout<<"\n";
}
```

---

## 作者：天使宝贝 (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF1942B)

### 思路&分析

通过分析题面不难看出，$p$ 从 $0$ 到 $n - 1$ 各出现了一次，mex 是非负最小值，因此我们只需要从后往前推，就能轻松地推出 $p$ 数组。

### CODE
```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0), cout.tie(0)
using namespace std;
const int MAXN = 2e5 + 5;
int T, n, a[MAXN], p[MAXN];
int main()
{
    IOS;
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        int mex = n;
        for (int i = n; i >= 1; i--)
        {
            p[i] = mex - a[i];
            mex = min(mex, p[i]);
        }
        for (int i = 1; i <= n; i++)
            cout << p[i] << " ";
        cout << "\n";
    }
    return 0;
}
```

---

