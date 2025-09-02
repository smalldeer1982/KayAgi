# Bobritto Bandito

## 题目描述

在 Bobritto Bandito 居住的家乡，有一条无限延伸的数轴，上面分布着无数栋房屋，分别位于 $ \ldots, -2, -1, 0, 1, 2, \ldots $ 的位置。在第 $0$ 天时，他通过让 $0$ 号房屋的居民感染病毒，引发了一场瘟疫。在接下来的每一天，瘟疫都会恰好蔓延到一个与已感染房屋相邻的健康房屋。可以证明，每一天被感染的房屋都会形成一个连续的区间。

我们用 $[l, r]$ 表示从第 $l$ 栋房屋到第 $r$ 栋房屋的区间。已知在第 $n$ 天时，区间 $[l, r]$ 被完全感染。请找出在第 $m$ 天（$m \le n$）时可能被感染的任意一个区间 $[l', r']$。

## 说明/提示

在第一个测试用例中，可能的情况是：
- 第 $1$ 天时感染区间为 $[-1,0]$
- 第 $2$ 天时为 $[-1,1]$
- 第 $3$ 天时为 $[-2,1]$

因此，$[-1,1]$ 是一个有效的输出。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 2 -2 2
4 1 0 4
3 3 -1 2
9 8 -6 3```

### 输出

```
-1 1
0 1
-1 2
-5 3```

# 题解

## 作者：GoldenSTEVE7 (赞：6)

## 题目大意
在一个小镇上，在一条无穷数线上有无数栋房子，房子的位置是 $\ldots, -2, -1, 0, 1, 2, \ldots$ 。在第 $0$ 天，他让房子 $0$ 的不幸居民感染了瘟疫。接下来的每一天，瘟疫都会传播到 $1$ 个相邻的健康家庭。
 
你知道在 $n$ 天后， $[l, r]$ 段被感染了。请找出可能在第 $m$ 天 $( m \le n )$ 被感染的线段 $[l', r']$ 。

## 思路
首先一定要清楚，瘟疫是从 $0$ 处开始传播的，那么最终答案也一定要包含 $0$，也就是 $0 \in [l', r']$。

那我们先假定 $l' = 0$, 这样就直接保证了上面的要求。而且很容易就能发现，$[l,r]$ 的长度，是比 $[l',r']$ 的长度小 $m-n$ 天的。这样我们就得到了答案。

但是要注意一点，$[l',r'] \subseteq [l,r]$。所以我们将答案区间向左平移，使上式成立。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int T; cin >> T;
    while(T--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        int y = d-a+b-c, x = 0; 
        while(y > d) x--, y--;
        cout << x << " " << y << "\n";
    }
    return 0;
}
```

---

## 作者：lemoned_qwq (赞：2)

# 题解：CF2094B
## 思路：
分类讨论两种情况即可。

情况一：当 $r > m$ 时：意味着在第 $m$ 天，感染区间还没有蔓延到 $r$ 这个位置。因为瘟疫是从 $0$ 号房屋开始蔓延的，所以在第 $m$ 天，最有可能的感染区间就是从 $0$ 开始，到 $m$ 结束，即 $[0, m]$ 。

情况二：当 $r ≤ m$ 时：表示在第 $m$ 天，感染区间已经包含了 $r$ 这个位置。为了保证感染区间的连续性，同时结合瘟疫蔓延的规则，第 $m$ 天的感染区间左端点 $l'$ 可以通过 $r - m$ 计算得到，右端点 $r'$ 就是 $r$ ，这个区间 $[r - m, r]$ 。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r;
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n >> m >> l >> r;
		if(r>m)
		{
			cout << "0 " << m << endl;
		}
		else
		{
			cout << r-m << " " << r << endl;
		}
	}
	return 0;
}
```

---

## 作者：linch (赞：1)

## Problem
一场瘟疫先感染了 $0$ 号房屋中的家庭，之后每天**有且仅有一个**健康的家庭被感染，且它与一个被感染的家庭相邻。已知第 $n$ 天有且仅有 $[l,r]$ 范围内的家庭被感染，求出任意一个第 $m$ 天可能的感染区间。

## Solution
显然每一时刻被感染的家庭总是形成一个区间。

于是我们从终止状态的 $[l,r]$ 开始，前一天就是在其中一边去掉一个端点，即 $l$ 加 $1$，或 $r$ 减 $1$。注意：由于瘟疫从 $0$ 开始，所以最终答案区间必须包含 $0$。

考虑重复 $n-m$ 次：在 $r>0$ 时，让 $r$ 减 $1$，即最右端家庭不感染。否则只能让 $l$ 加 $1$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main() {
	cin >> t;
	while (t--) {
		int n, m, l, r;
		cin >> n >> m >> l >> r;
		int x = n - m;
		for (int i = 1; i <= x; i++) {
			if (r > 0) r--;
			else l++;
		}
		cout << l << " " << r << "\n";
	}
	return 0;
}
```
[AC record](https://codeforces.com/contest/2094/submission/317244126)

---

## 作者：metrixgo_caozhendi (赞：1)

一道模拟题，但是不用真正模拟。观察以后发现，如果 $l$ 或者 $r$ 的绝对值大于等于 $m$，那么我们只需要让病毒沿着那一个方向走就行了，从 $0$ 开始到 $\pm m$ 满足题意。如果不是的话，那么就让病毒沿着任意一方向延伸到头，随后在另一端加上剩余部分即可，复杂度为 $O(1)$。当然，本题甚至可以直接模拟 $m$ 天，复杂度为 $O(m)$。

注：本题我认为描述不严谨，并不是输出在 $m$ 天中任意一个全被感染的段落，而是任意一个表示**所有被感染的房子**的段落。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,l,r;
string s;
int main()
{
   cin>>t;
	while(t--)
	{
		cin>>n>>m>>l>>r;
		if(r>=m) cout<<0<<" "<<m<<endl;
		else if(l<=-m) cout<<-m<<" 0\n";
		else cout<<l<<" "<<m+l<<endl;
	}
   return 0;
}
```

---

## 作者：yulinOvO (赞：0)

### 思考过程：

- 第 $0$ 天的人数：$1$。
 
- 第 $1$ 天的人数：$2$。
  
以此类推，第 $m$ 天的人数是 $m+1$。

也就是说，$r'-l'=m$，特判 $m≤r$ 的情况即可。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l,r;
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n >> m >> l >> r;
		if(r>m)  cout << "0 " << m << endl;//如果r>m，即l'=0,r'=m
		else cout << r-m << " " << r << endl;//否则r'和r相等，l'=r-m
	}
	return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### Solution
$l'$ 的下界：$l\ge\max(l,-m)$。

$l'$ 的上界：$l'\le\min(0,r-m)$。

此时我们可以构造 $l'=\max(l,-m)$，此时对应的 $r'=l'+ m$ 必定满足 $0\le r'\le r$，因为 $r=l+n$ 且 $m\le n$。
### Code

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 3e3 + 5;
signed main ()
{
	int T;
	cin >> T;
	while (T --)
	{
		int n,m,l,r;
		cin >> n >> m >> l >> r;
		cout << max (l,- m) << ' ' << max (l,- m) + m << endl;
	}
	return 0;
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
给定四个数 $n,m,l,r$ 其中 $r-l=n$，现在要你构造两个数 $l^{\prime},r^{\prime}$ 并且 $r^{\prime}-l^{\prime}=m,l\le l^{\prime}\le0<r^{\prime}\le r$。
## 题目解法
如果想满足 $l\le l^{\prime}<r^{\prime}\le r$，可以只改变其中一个数。但这样有一个风险，就是 $l^{\prime}$ 可能会大于 $0$，所以要判断一下如果 $l^{\prime}>0$ 就把 $l^{\prime}$ 和 $r^{\prime}$ 都减去 $l^{\prime}$ 即可，差不会改变。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, m, l, r;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--;) {
    cin >> n >> m >> l >> r, l += n - m;  // 先改变 l 不改变 r
    (l <= 0) ? (cout << l << ' ' << r << '\n') : (cout << "0 " << r - l << '\n');  // 判断两种输出情况
  }
  return 0;
}
```

---

## 作者：FXLIR (赞：0)

### 思路
设第 $m$ 天的左端点为 $l_1$，右端点为 $r_1$。

因为可以输出任何一种情况，不妨假设传染病的感染范围在从第 $m$ 天到第 $n$ 天的时间里一直在向左端点 $l$ 延伸，容易推出这样的话 $l_1$ 的值是 $l + n - m$。

但注意到，传染病是从 $0$ 点开始向两端延伸的，所以左端点必须 $\leq 0$，但是按照上面的假设，$l_1$ 有可能 $> 0$。

为解决这一问题，当 $l_1$，即 $l + n - m > 0$ 时，将 $l_1$ 设为 $0$，差的天数（$n - m - l$ 天）在右端点补齐，即当 $l_1$ 有可能 $>0$ 时，$r_1  = r - (n-m-l)$，否则 $r_1=r$。
### 代码
```cpp
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int N=1e5+5,INF=1e9;
int t,n,m,l,r,li,ri;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>l>>r;
		m=n-m,li=min(0ll,l+m),m=max(0ll,m-abs(l)),ri=r-m;
		cout<<li<<" "<<ri<<"\n";
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

在Bobritto Bandito的家乡，沿着一条无限的数轴有无数的房屋，房屋的位置是 $\ldots, -2, -1, 0, 1, 2, \ldots$。在第 $0$ 天，他通过给房屋 $0$ 的居民传染病而开始了这场疫情。随着时间的推移，每天疫情会传染给一个邻近的健康房屋。可以证明，每一天，感染的房屋形成一个连续的区间。

假设在第 $n$ 天时，感染区间是从房屋 $l$ 到房屋 $r$，即 $[l,r]$。现在，给定该区间 $[l, r]$，请你找出一个在第 $m$ 天 $(m \leq n)$ 可能出现的感染区间 $[l',r']$。

### 思路

因为第 $0$ 天有 $1$ 个人，第 $m$ 天有 $m+1$ 个人，所以 $r'-l'+1=m+1$，化简后得 $r'-l'=m$。

然后分类讨论：

- $m \le r$，直接 $l'=0,r'=m$。

- $m > r$，$r'=r,l'=r-m$。

做完了。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,l,r;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>l>>r;
		if(m<=r)  cout<<0<<" "<<m<<endl;
		else  cout<<r-m<<" "<<r<<endl;
	}
	return 0;
} 
```

---

