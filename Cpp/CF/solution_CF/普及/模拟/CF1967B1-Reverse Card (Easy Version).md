# Reverse Card (Easy Version)

## 题目描述

The two versions are different problems. You may want to read both versions. You can make hacks only if both versions are solved.

You are given two positive integers $ n $ , $ m $ .

Calculate the number of ordered pairs $ (a, b) $ satisfying the following conditions:

- $ 1\le a\le n $ , $ 1\le b\le m $ ;
- $ a+b $ is a multiple of $ b \cdot \gcd(a,b) $ .

## 说明/提示

In the first test case, only $ (1,1) $ satisfies the conditions.

In the fourth test case, $ (1,1),(2,1),(2,2),(3,1),(4,1),(5,1),(6,1),(6,2),(6,3),(7,1),(8,1),(9,1),(10,1),(10,2) $ satisfy the conditions.

## 样例 #1

### 输入

```
6
1 1
2 3
3 5
10 8
100 1233
1000000 1145141```

### 输出

```
1
3
4
14
153
1643498```

# 题解

## 作者：w9095 (赞：4)

[CF1967B1 Reverse Card (Easy Version)](https://www.luogu.com.cn/problem/CF1967B1)

我们发现 $b\times\gcd(a,b)$ 必然为 $b$ 的倍数，那么 $b\times\gcd(a,b)$ 的倍数 $a+b$ 也必然为 $b$ 的倍数。所以，$a$ 必然为 $b$ 的倍数。因为 $a$ 为 $b$ 的倍数，所以 $\gcd(a,b)=b$，原式可化为 $a+b=xb^2$，其中 $x$ 为正整数。

考虑枚举 $b$，原式可化为 $a=xb^2-b$。又因为 $a\le n$，则 $xb^2-b\le n$。则 $x$ 的最大值为 $\lfloor\frac{n+b}{b^2}\rfloor$，共有 $\lfloor\frac{n+b}{b^2}\rfloor$ 种取值，对应的，$a$ 也有 $\lfloor\frac{n+b}{b^2}\rfloor$ 种取值。

注意最后有 $a=1,b=1$ 这种情况会算重，需要减去 $1$。

代码实现与讲解略微不同，但本质一样。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,m;
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long ans=0;
	   	scanf("%lld%lld",&n,&m);
	   	for(int i=1;i<=m;i++)
	   	    {
	   	    if(n<(i-1)*i)break;
		    ans=ans+(n-(i-1)*i)/(i*i)+1;
		    }
	   	printf("%lld\n",ans-1);
	   }
	return 0;
} 
```

---

## 作者：破壁人罗辑 (赞：1)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/CF1967B1)/[Codeforces 1967B1](https://codeforces.com/contest/1967/problem/B1)/[Codeforces 1972D1](https://codeforces.com/contest/1972/problem/D1)

## 题意简述

给出两个数 $n,m$，求满足 $1\leq a\leq n,1\leq b\leq m,b\cdot\gcd(a,b)|a+b$ 的数对 $(a,b)$ 的数量。

## 解题思路

因为 $b\cdot\gcd(a,b)|a+b$，故 $b|a+b$，故 $b|a$，即 $\gcd(a,b)=b$。

设 $a=kb,k\geq 1$，则 $b^2|(k+1)b$，即 $b|k+1$，对于任意的 $b\in[2,\min(m,n)]$，任意的 $\frac{k+1}{b}\in\left[1,\lfloor\frac{n+b}{b^2}\rfloor\right]$ 且 $\frac{k+1}{b}\in\N^+$ 都是合法的。而 $b=1$ 时任意 $a\in[1,n]$ 都是合法的。故从 $2$ 到 $m$ 枚举 $b$，累计 $ans$ 再加上 $n$ 即可，时间复杂度 $O(\min(m,n))$。

## AC 代码
### C++
```cpp
#include<stdio.h>
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&n,&m);
		long long ans=0;
		for(int b=1;b<=m;b++)
			ans+=(n+b)/(b*(long long)b)-1/b;
		printf("%lld\n",ans);
	}
	return 0;
}
```
### Python
```python
t=int(input())
for T in range(t):
    [n,m]=input().split()
    [n,m]=[int(n),int(m)]
    ans=n
    for b in range(2,min(n,m)+1):
        ans=ans+(n+b)//(b*b)
    print(ans)
```

---

## 作者：aeiouaoeiu (赞：1)

要让 $b\cdot\gcd(a,b)|a+b$，显然有 $b|a+b$。又因为 $b|b$，故 $b|a$，则 $\gcd(a,b)=b$，所以 $b^2|a+b$。

令 $kb^2=a+b$，则 $1\le a=kb^2-b\le n$，得 $1+b\le kb^2\le n+b$。

当 $b\ge 2$ 时，$b^2>b+1$，则合法 $k$ 数量为 $\lfloor\dfrac{n+b}{b^2}\rfloor$。当 $b=1$ 时，合法 $k$ 数量显然为 $n$（也可以是 $\lfloor\dfrac{n+b}{b^2}\rfloor-1$）。

枚举 $b$ 即可做到 $\mathcal{O}(m)$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef long double db;
const ll maxn=200007,ee=1000000000000000007ll;
ll n,m,ans;
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll Tccs=1;
	cin>>Tccs;
	for(int tcs=1;tcs<=Tccs;tcs++){
	    cin>>n>>m; ans=0;
	    for(ll i=1;i<=m;i++) ans+=(n+i)/(i*i)-(i==1);
	    cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Gapple (赞：0)

首先考虑第二个条件：$(b \cdot \gcd(a, b)) \mid (a + b)$，其中 $A \mid B$ 表示 $B$ 是 $A$ 的倍数。因为 $b \mid (b \cdot \gcd(a, b))$，所以 $b \mid (a + b)$，所以 $b \mid a$。

设 $a = kb$，则 $\gcd(a, b) = b, b^2 \mid ((k + 1)b)$，则 $b \mid (k + 1)$。

同时因为 $a \le n$，所以 $kb \le n$，于是 $k \le \lfloor n / b \rfloor$。此时共有 $\lfloor \dfrac{\lfloor n / b \rfloor + 1}{b} \rfloor$ 个满足条件的 $k$，故将答案加上述值。

于是我们枚举 $b$，分别计算贡献计入答案。注意最后答案会多算 $a = b = 1$ 的情况，故让答案减 $1$ 即可。

----

下附代码：

```cpp
#include <iostream>

using namespace std;
using i64 = long long;

void solve_test()
{
    int n, m;
    cin >> n >> m;

    i64 ans = 0;

    for (int b = 1; b <= m; ++b)
        ans += (n / b + 1) / b;

    cout << ans - 1 << '\n';
}

int main()
{
    int t;
    cin >> t;

    while (t-- > 0)
        solve_test();

    return 0;
}
```

---

## 作者：_Yonder_ (赞：0)

很简单的一道题。

$\because b\cdot\gcd(a,b)\mid a+b,\therefore b\mid a+b,\therefore b\mid a.$

$\because b\le a,\therefore \gcd(a,b)=b,\therefore b^2\mid a+b.$

令 $kb^2=a+b$。

$\because 1\le a\le n,\therefore 1\le k\le\tfrac{n+b}{b^2}.$

枚举 $b$ 即可，还有要减去 $k=\gcd(a,b)=1$ 的特殊条件。

# Code
```
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;int ans=0;
        for(int i=1;i<=m;i++)
            ans+=(n+i)*1ll/(i*1ll*i);
        cout<<ans-1<<endl;
    }
    return 0;
}
```

---

## 作者：MrPython (赞：0)

来点依靠注意力的解法。

很容易写出一份暴力程序。打开一个 python 交互式终端，写一份打表程序：
```python
In [1]: from math import gcd

In [2]: def f(n,m):
   ...:     for i in range(1,n+1):
   ...:         for j in range(1,m+1):
   ...:             if (i+j)%(j*gcd(i,j))==0:
   ...:                 print(i,j)
   ...:
```
然后，调用 `f`，尝试一些样例：
```python
In [3]: f(20,20)
```
输出为：
```
1 1
2 1
2 2
3 1
4 1
5 1
6 1
6 2
6 3
7 1
8 1
9 1
10 1
10 2
11 1
12 1
12 4
13 1
14 1
14 2
15 1
15 3
16 1
17 1
18 1
18 2
19 1
20 1
20 5
```
很容易注意到，$(b\times\gcd(a,b))\mid(a+b)$ 成立的其中一个必要不充分条件是 $b\mid a$。

让我们充分发挥想象力。$b\mid a$ 可得到 $\gcd(a,b)=b$。因此，原式等价于 $b^2\mid(a+b)$。枚举 $b$ 依次计算完全可行。

```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n,m;cin>>n>>m;
        uli ans=n;
        for (uli b=2;b<=m;++b)
            ans+=(n+b)/(b*b);
        cout<<ans<<'\n';
    }
    return 0;
}
```

这样，我们通过人类智慧的方式，避免了任何复杂数论知识，在 CF 紧张的赛时时间快速解决本题。

---

## 作者：I_will_AKIOI (赞：0)

### 题目大意

给定两个正整数 $n,m$，求满足以下条件的数对个数。

- $ 1\le a\le n $ , $ 1\le b\le m $；
- $ a+b $ 是 $ b \cdot \gcd(a,b) $ 的倍数。

由于 $a+b$ 是 $ b \cdot \gcd(a,b) $ 的倍数，所以 $a+b$ 是  $b$ 的倍数。所以可以枚举 $b$，再枚举 $a+b$ 是 $b$ 的几倍，复杂度便能大大降低。容易发现复杂度是调和级数复杂度。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
void solve()
{
  int ans=0;
  cin>>n>>m;
  for(int i=1;i<=m;i++)
  {
	for(int j=i+i;j<=i+n;j+=i)//枚举a+b
	{
		int a=j-i,b=i;//计算a和b
		if((a+b)%(b*__gcd(a,b))==0) ans++;//满足要求
	}
  }
  cout<<ans<<"\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：Day_Tao (赞：0)

### 题目大意

给定 $n,m$，求满足 $1\le a\le n,1\le b \le m (1\le n,m,\sum n,\sum m\le2\times 10^6),(b\times\gcd(a,b))\mid(a+b)$ 的数对 $(a,b)$ 的组数。

### Sol

注意到 $\gcd(a,b)\mid a$ 且 $\gcd(a,b)\mid b$，即 $\gcd(a,b)\mid (a+b)$，结合条件的式子可得 $b\mid (a+b)$，即 $b\mid a$。现在令 $a=k\times b$，带入条件式子可得 $(b\times\gcd(b,k\times b))\mid (k\times b+b)$，即 $b\mid (k+1)$，求满足条件的 $k+1$ 的个数。而 $k\times b\le n$，即 $k\le \lfloor\frac{n}{b}\rfloor$，所以 $k+1\le \lfloor\frac{n}{b}\rfloor+1$。所以只需要枚举 $b$ 的值，然后对于每一个 $b$ 计算出所有的 $k+1$ 的可能，即求 $\sum\limits _ {b=1}^m \lfloor \frac{\lfloor\frac{n}{b}\rfloor+1}{b} \rfloor$。最后还要将这个值减一，减去 $k=0$ 的情况。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pqg priority_queue<int, vector<int>, greater<int>>
#define pql priority_queue<int, vector<int>, less<int>>
#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)
#define ls root << 1
#define rs root << 1 | 1
#define scnaf scanf
#define rt register int
#define int long long
const int MAX = 2e5 + 5;
const int INF = 0x7fffffff;
int T, n, m, ans;
signed main()
{
	scanf("%lld", &T);
	while (T--)
	{
		scanf("%lld%lld", &n, &m);
		ans = 0;
		for (int b = 1; b <= m; ++b)
			ans += (n / b + 1) / b;
		printf("%lld\n", ans - 1);
	}
	system("pause");
	return 0;
}
```
---

### END

---

## 作者：yyz1005 (赞：0)

题目大意：给定 $n,m$，求满足 $1 \le a \le n,1 \le b \le m,b \cdot \gcd(a,b) | a+b$ 的 $(a,b)$ 组数。

不妨设 $\gcd(a,b) = x,a = px,b = qx$。

有 $qx^2|(p+q)x$。

故 $qx|p+q$。

注意到 $(p,q) = 1$，那么 $q = 1,x | p+q$。

所以 $a = px,b = x,x|p+1$。

做法很多，代码里是枚举 $b$ 再枚举 $a$。是 $O(n \ln n)$ 的。

[Code](https://codeforces.com/contest/1972/submission/258894194)

---

## 作者：锦依卫小生 (赞：0)

# CF1967B1
## 分析过程
设 $a$，$b$ 的最大公因数为 $g$。则 $a + b = t \cdot b \cdot g$  
$\Rightarrow p + q = t \cdot b$(其中 $p$，$q$ 互质)。    
进一步得到 $p + q = t \cdot g \cdot q$  
$$\Rightarrow p = (t \cdot g - 1)q$$
不难发现，在 $p$，$q$ 互质的情况下前者仍可以写成后者的倍数的形式。因此，得到当且仅当 $q = 1$ 时等式可能成立。
$$b = g$$  
$$a = g(t \cdot g - 1)$$  
$$ b \le m$$  
$$ a \le n$$  
## 算法实现
综合上述分析，可以枚举 $g$，对所有可能的 $t$ 的个数求和。
$$ t \le \frac{(n + g)}{g^{2}}  $$
## 注意
$t = 1$ 且 $g = 1$ 为特殊情况，并不满足条件应减去。
## 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
long long ans;
void solve(){
	ans=0;
	cin>>n>>m;
	for(long long i=1;i<=m;++i)
		ans+=(i+n)/(i*i);
	cout<<ans-1<<endl;
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
}
```

---

