# Computer Game

## 题目描述

Vova is playing a computer game. There are in total $ n $ turns in the game and Vova really wants to play all of them. The initial charge of his laptop battery (i.e. the charge before the start of the game) is $ k $ .

During each turn Vova can choose what to do:

- If the current charge of his laptop battery is strictly greater than $ a $ , Vova can just play, and then the charge of his laptop battery will decrease by $ a $ ;
- if the current charge of his laptop battery is strictly greater than $ b $ ( $ b<a $ ), Vova can play and charge his laptop, and then the charge of his laptop battery will decrease by $ b $ ;
- if the current charge of his laptop battery is less than or equal to $ a $ and $ b $ at the same time then Vova cannot do anything and loses the game.

Vova wants to complete the game (Vova can complete the game if after each of $ n $ turns the charge of the laptop battery is strictly greater than $ 0 $ ). Among all possible ways to complete the game, Vova wants to choose the one where the number of turns when he just plays is the maximum possible. It is possible that Vova cannot complete the game at all.

Your task is to find out the maximum possible number of turns Vova can just play or report that Vova cannot complete the game.

You have to answer $ q $ independent queries.

## 说明/提示

In the first example query Vova can just play $ 4 $ turns and spend $ 12 $ units of charge and then one turn play and charge and spend $ 2 $ more units. So the remaining charge of the battery will be $ 1 $ .

In the second example query Vova cannot complete the game because even if he will play and charge the battery during each turn then the charge of the notebook battery will be $ 0 $ after the last turn.

## 样例 #1

### 输入

```
6
15 5 3 2
15 5 4 3
15 5 2 1
15 5 5 1
16 7 5 2
20 5 7 3
```

### 输出

```
4
-1
5
2
0
1
```

# 题解

## 作者：wucstdio (赞：2)

$O(1)$题。

首先先特判不能打完的情况，如果$k\le nb$就直接输出$-1$。

否则考虑每把一局由连接充电器打变成直接打耗电就会增加$a-b$。

所以答案就是$\min\left(n,\left\lfloor\dfrac{(k-nb-1)}{a-b}\right\rfloor\right)$

单组询问时间复杂度$O(1)$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
ll t,k,n,a,b;
int main()
{
	scanf("%I64d",&t);
	while(t--)
	{
		scanf("%I64d%I64d%I64d%I64d",&k,&n,&a,&b);
		k-=b*n;
		if(k<=0)
		{
			printf("-1\n");
			continue;
		}
		printf("%I64d\n",min((k-1)/(a-b),n));
	}
	return 0;
}
```

---

## 作者：WydnksqhbD (赞：1)

# [CF1183C Computer Game](https://www.luogu.com.cn/problem/CF1183C) 题解
## 思路
经典鸡兔同笼。

设用了 $x$ 次 $a$，$y$ 次 $b$。则有
$$\begin{cases}
x+y=n\\
ax+by=k
\end{cases}$$
最终解得 $x=\frac{k-bn}{a-b}$。

注意！我们还需要特判特殊情况——输出 `-1`。此时 $bn>k$，加上特判即可。

然后要记住，$k$ 要减一，不然 $k$ 就 $\le0$ 了。

以及答案不可能超过 $n$，故最终答案为 $\min\{n,\lfloor\frac{k-bn}{a-b}\rfloor\}$。

时间复杂度 $O(q)$。
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int q,k,n,a,b;
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>q;
	while(q--)
	{
		cin>>k>>n>>a>>b;k--;
		if(b*n>k)puts("-1");
		else printf("%lld",min(n,(k-b*n)/(a-b)));
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：lbh666 (赞：1)

## 思路
题目请大家自行阅读，翻译已经通俗易懂了。
- 这道题非常像小学数学里的鸡兔同笼问题。
- 鸡兔同笼有很多解法，我在这里用的是**假设法**。
- 第一步，把脚少的拎出来，脚多的也可以，但是脚少的方便判断，这里数据小的一方是 $b$，如果 $n \times b \ge k$，直接输出 $-1$ 即可，最小的都减不了，最后的结果一定**不大于** $0$。
- 另一种情况，为了弥补到不了 $k$，把剩余的部分拿去除以 $a$ 和 $b$ 的差，如果大于 $n$，取 $n$ 即可。
- 这里感谢[zhouzihe](https://www.luogu.com.cn/user/798537)
的题解，给出了很不错的解释，解释如下。
> 为什么 $k$ 还要再减一呢？因为最终 $k$ 是要大于 $0$ 的，所以要至少留下 $1$。
- **注意事项**：不要开 `int`，要开 `long long`。

## 代码实现
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll t;

int main(){
	cin>>t;
	for(ll i=1;i<=t;++i){   //循环  
		ll k,n,a,b,ans;
		cin>>k>>n>>a>>b;    //输入每次询问的变量 
		if(n*b>=k){     //如果范围超了 
			cout<<"-1\n";  //直接输出-1 
	    }else{
			ans=min(n,(k-n*b-1)/(a-b)); //否则就按鸡兔同笼的步骤进行操作 
			cout<<ans<<"\n";        //将答案输出 
		}
	}
	return 0;
}
```

---

## 作者：XYzero (赞：1)

## 分析

首先看数据范围 $n\le1\times 10^9$，推测复杂度 $O(\log n)$，考虑 **二分**，再一看在 $k > 0$ 的情况下使答案最大，这不就是二分答案吗，而 $k > 0$ 就是 check 的条件，最后记得开 `long long`。 

my code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int q,k,n,a,b; 
bool check(int x){
	if((k - x * a - (n - x) * b) > 0){
		return true;
	}
	return false;
}
signed main(){
	scanf("%lld",&q);
	while(q--){
		int ans = -1;
		scanf("%lld %lld %lld %lld",&k,&n,&a,&b);
		int max_ans = n,min_ans = 1;
		int l = min_ans - 1,r = max_ans + 1;
		int tmp = min(a,b);
		if(k - n * tmp <= 0){
			printf("%lld\n",ans);
			continue;
		}
		while(l + 1 < r)
		{
		    int mid = l + r >> 1;
		    if(check(mid)) l = mid;
		    else r = mid;
		}
		ans = l;
		printf("%lld\n",ans);
	}
	
	
	return 0;
} 
```

---

## 作者：ztd___ (赞：0)

这么古老的题居然还能写题解。

题意应该很清楚，就不赘述了。

本文中将【让 $k$ 减 $a$】操作称为【$A$ 操作】，【让 $k$ 减 $b$】操作称为【$B$ 操作】。
### 分析
首先观察到数据范围非常巨大，所以考虑 $O(1)$ 解决。

先判断无解。

显然，每个回合至少也要消耗 $b$，所以 $n$ 个回合消耗的数量至少为 $n \times b$，明显这个数必须 $< k$。

然后开始快乐地推式子。

首先可以想到，对于每一回合，将一次 $B$ 操作改成 $A$ 操作需要**额外**消耗 $(a-b)$ 个单位。

然后将 $k$ 减去至少需要的 $n \times b$，剩下的就是可供**额外**消耗的。

一个整除就可以计算出最多可以进行几次修改了。

但是此题有两个坑点：
- 如果能正好消耗完 $k$，即 $(k - n \times b) \mid (a - b)$，回合数量需要减一。这是因为最后的剩余必须严格大于 $0$。
- 整除后的答案并不能直接输出，设其为 $ans$，则应输出 $\min(ans,n)$。这是因为最多只能改 $n$ 个回合。

然后代码也是非常的简洁。虽然比不上其他的一些题解，但是相对于鸡兔同笼可能更加容易理解。

### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int k, n, a, b;
		cin >> k >> n >> a >> b;
		if (n * b >= k) {
			cout << "-1\n";
			continue;
		}
		int g = k - n * b;
		int f = 0;
		if (g % (a - b) == 0) f = g / (a - b) - 1;
		else f = g / (a - b);
		f = max(f, 0ll);
		cout << min(n, f) << "\n";
	}
	return 0;
}
```

---

## 作者：卷王 (赞：0)

这题其实很简单。考虑二分答案，设当前为 $x$，我们必须用掉 $a \times x$，对于剩下的 $k-a \times x$，用 $b$ 来减，如果最后的操作数量 $\ge n$ 就满足要求。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, a, b, Q, T, _;
bool flag = 0;

inline bool check(int x) {
	if(a * x >= k) return 0;
	return (x + (k - a * x) / b - ((k - a * x) % b == 0)) >= n;
}

signed main() {
	Q = read();
	while(Q--) {
		k = read(), n = read(), a = read(), b = read();
		if(min(a, b) * n >= k) {
			printf("-1\n");
			continue;
		}
		int l = 0, r = n, mid, ans = 0;
		while(l <= r) {
			mid = (l + r) >> 1;
			if(check(mid)) l = mid + 1, ans = mid;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：_d_h_f (赞：0)

## Solution

首先介绍 $O(q \log n)$。

枚举左端点和右端点，运用二分答案的思想，假如说 $a \times mid + b \times (n - mid) < k$，则将右端点减一，否则左端点加一。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,k,n;
int q;
int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%lld%lld%lld%lld",&k,&n,&a,&b);
		ll l=0LL,r=1e9;
		while(l<=r){
			ll mid=l+r>>1LL;
			if(a*mid+b*(n-mid)<k)
				l=mid+1LL;
			else 
				r=mid-1LL;
		}
		printf("%lld\n",min(n,l-1LL));
	}
	return 0;
}

```

其次我们想想更快的方法，能不能将时间复杂度降到 $O(q)$。可以分段式考虑，假如说 $k \le b \times n$，也就是说就算答案为 $0$ 也不能成功使 $k>0$，那么就输出 $-1$，然后考虑其他情况，假设 $k$ 全部被 $b \times n$ 减去，然后我们将所有能够替代的 $b$ 全部换成 $a$，这样子就能求出最大答案，于是得出公式 $ans = \frac{k - b \times n}{a - b}$，简单来说就是一道鸡兔同笼题。

请注意：如果 $(k - b \times n) \bmod (a - b) = 0$，那么 $ans$ 就需要减去一，化简得出 $ans = \frac{k - b \times n - 1}{a - b}$，而且 $ans$ 需要小于或等于 $n$，也就是说 $ans = \min( \frac{k - b \times n - 1}{a - b},n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a,b,k,n;
int q;
int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%lld%lld%lld%lld",&k,&n,&a,&b);
		printf("%lld\n",k<=b*n?-1LL:min(n,(k-n*b-1LL)/(a-b)));
	}
	return 0;
}

```

---

## 作者：zhu_wen (赞：0)

# Computer Game
## [原题传送门](https://codeforces.com/problemset/problem/1183/C)
## 思路
本题就是一个结论题，除了 $q$ 组数据，我们解决的方式就为 $O(1)$，因此我们来找关系式。

$k\le n\times b $ 无解，输出 $-1$。如果要保证要玩完，需要的电量为 $k- n\times b-1$，我们就能够推出公式 $min(n,\frac{k-a\times b-1}{a-b} ) $，输出这个就为最终答案。

## 代码
```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wsp(int x) { write(x), putchar(' '); }
inline void wel(int x) { write(x), putchar('\n'); }

int q;
int k, n, a, b;

signed main()
{
    fst;
    q = read();
    while (q--)
    {
        k = read(), n = read(), a = read(), b = read();
        if (k <= n * b)
        {
            cout << -1 << endl;
        }
        else
        {
            int t = a - b;
            int w = k - n * b - 1;
            cout << min(n, w / t) << endl;
        }
    }
    return 0;
}
```


---

## 作者：__HHX__ (赞：0)

# 思路（小学数学）
首先考虑全选 $b$，那 $k$ 就要花掉 $n \times b$ 的价值。
 
如果要把 $b$ 转化成 $a$，需要花掉 $a - b$ 的价值。

所以我们只需把剩余价值 $k - n \times b$，除以转化价值 $a - b$ 就可以了。

当全选 $b$ 时，如果 $k$ 的值比 $n \times b$ 还小，那绝对为无解。

特别提醒：只能转化 $n$ 个数。
```cpp
#include<iostream>
using namespace std;

int main() {
	int q;
	cin >> q;
	while (q--) {
		long long n, k, a, b;
		cin >> k >> n >> a >> b;
		k -= n * b + 1;
		a -= b;
		cout << (k >= 0 ? (k / a >= n ? n : k / a) : -1) << '\n';
	}
} 
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现当 $k \leq n \times b$ 时，无解。应为 $k-a$ 是比 $k-b$ 多减去了 $a-b$，所以答案即为 $min(n,\frac{(k-n \times b-1)}{a-b})$。为什么 $k$ 还要再减一呢？因为最终 $k$ 是要大于 $0$ 的，所以要至少留下 $1$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int q,k,n,a,b;
int main(){
	cin>>q;
	while(q--){
		cin>>k>>n>>a>>b;
		if(k<=n*b){
			cout<<-1<<endl;
			continue;
		}
		cout<<min(n,(k-n*b-1)/(a-b))<<endl;
	}
	return 0;
}
```


---

## 作者：wnsyou (赞：0)

还算水的一道题。
## 题意
本题意为题面直接翻译的简化版，可能会比题目翻译要复杂。

有 $q$ 次询问，每次给出四个数，表示一开始的电亮为 $k$，有 $n$ 个回合，不插电玩一个回合则电量会减少 $a$，插电玩一个回合则电量会减少 $b$，电量在任何时刻都必须 **严格大于** $0$。

如果能玩完 $n$ 个回合，输出不插电玩的回合数的最大值；否则输出 $-1$。
## 思路
由于 $k$ 最大为 $10^9$，直接模拟肯定是不行的。

那么，这题怎样做呢？

首先，电量消耗最少的方案是每回合都插电玩，一共消耗 $n \times b$ 的电量，只有当 $k$ **严格大于** 它时才能玩完所有回合，否则就可以输出 $-1$。

如果在玩某一个回合时把电拔了，那么就要多用 $a - b$ 的电量。

要保证能玩完所有回合，可以用来自由分配的电量就只有 $k - n \times b - 1$，知道了这个，答案也可以很快地推出来了。

可以不插电玩的回合数的公式为：$\frac{k - n \times b - 1}{a - b}$。

由于总共只有 $n$ 个回合，所以答案是不能超过 $n$ 的，正确答案公式为 $\min(\frac{k - n \times b - 1}{a - b}, n)$。

时间复杂度：$O(q)$，轻松过。

#### 要开 `long long`。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

long long q, n, k, a, b;

int main() {
  for (cin >> q; q; q--) {
    cin >> k >> n >> a >> b;
    if (k <= n * b) { // 玩都玩不完
      cout << -1;
    } else {
      cout << min(n, (k - n * b - 1) / (a - b)); // 套上公式即可
    }
    cout << '\n';
  }
  return 0;
}
```

给个赞吧，管理大大求过。

---

## 作者：Abeeel51 (赞：0)

#### 题目大意
~~大水题~~
#### 解题思路
**小学鸡兔同笼问题**

每次打完会耗电 $a - b$，答案 $\min \Big ( n , \Big \lfloor \frac{k-1-nb}{a-b} \Big \rfloor \Big )$。

但是，不开 long long 就无啦。

还有个建议，这题的中文翻译是题面的解释版，去除了提取题目关键信息的步骤，如果有能力建议阅读英文题面。
#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, const char * argv[]) {
    // insert code here...
    ll q,k,n,a,b;
    scanf("%lld",&q);
    while(q--){
        scanf("%lld%lld%lld%lld",&k,&n,&a,&b);
        if((k-(n*b))<=0) printf("-1\n");
        else printf("%lld\n",min((k-1-(n*b))/(a-b),n));
    }
    return 0;
}
```


---

## 作者：Lates (赞：0)

设 $k-a$ 的操作数为 $t$。
那么 $k-at-b(n-t)>0$，化简完可以得到 $t<\dfrac{k-bn}{a-b}$。
然后注意到 $b\le a$，所以当 $k-\min(a,b)n=k-bn\le0$时无解。

然后要开longlong

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long 
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
int T,k,n,a,b,ans;
signed main(){
	T=read();
	while(T--){
		k=read(),n=read(),a=read(),b=read();
		if(k-min(a,b)*n<=0)puts("-1");
		else{
			if((k-b*n)%(a-b))ans=(k-b*n)/(a-b);
			else ans=(k-b*n)/(a-b)-1;
			ans=min(ans,n);
			printf("%lld\n",ans);
		} 
	}
	return 0;
}


```


---

## 作者：decoqwq (赞：0)

本题两种做法

第一种，二分答案，然后进行验证即可，复杂度$O(logn)$

```cpp
/**************************/
/*It is made by decoration*/
/*gzzkal   gzzkal   gzzkal*/
/*It is made by decoration*/
/**************************/
#include <bits/stdc++.h>
using namespace std;
#define int long long
main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int k,n,a,b;
		scanf("%lld%lld%lld%lld",&k,&n,&a,&b);
		int qaq=k/b;
		if(qaq==n&&qaq*b==k)
		{
			cout<<-1<<endl;
		}
		else
		{
			int l=0,r=qaq;
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(mid*a>=k)
				{
					r=mid;
				}
				if(ceil((double)(k-mid*a-b)/b)+mid>=n)
				{
					l=mid+1;
				}
				else
				{
					r=mid;
				}
			}
			if(ceil((k-l*a-b)/b)+l>=n)
			{
				cout<<min(l,n)<<endl;
			}
			else
			{
				cout<<min(l-1,n)<<endl;
			} 
		}
	}
} 
```

第二种，以鸡兔同笼思想即可，复杂度$O(1)$

ps：Orz sys

```
#include <bits/stdc++.h>
using namespace std;
int T,k,n,a,b;
int main()
{
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d%d%d%d",&k,&n,&a,&b);
    if(n*(long long)b>=k)
   		printf("-1\n");
    else
    	printf("%d\n",min(n,(k-n*b-1)/(a-b)));
  }
  return 0;
}
```

---

## 作者：AC_Dolphin (赞：0)

依然比上篇复杂度低。。。所以就不用卡时间了

设$x$为`just play`的次数，$y$为`play and charge`的次数

因为$a>b$，所以如果$b*n>=k$，那么最后剩下的`charge`肯定$<=0$，所以这个时候要输出$-1$

接下来我们知道$\left\{ \begin{matrix} ax+by<k\\x+y=n \end{matrix}\right.$（latex运用不熟练，见谅）

将2式左右两边同乘$b$，得$bx+by=bn$

1式-2式，得$(a-b)x<k-bn$

因为$a>b$，所以$a-b>0$

所以$x<\frac{k-bn}{a-b}$
**注意不是整除**

然而,因为$y>=0$，所以$x<=n$，$x$还要对$n$取$min$

最后有一个细节：因为上文不是整除，所以当$(k-bn)\%(a-b)=0$时，$x=min(\frac{k-bn}{a-b}-1,n)$，否则$x=min(\frac{k-bn}{a-b},n)$

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
#define int long long
int a,b,n,cnt,q,k;
inline int read(){
    int f(1),x(0);
    char ch(getchar());
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
signed main(){
    q=read();
    while(q--){
        k=read(),n=read(),a=read(),b=read();
        if(b*n>=k){
            cout<<-1<<endl;
            continue;
        }
        if((k-b*n)%(a-b)) cout<<min((k-b*n)/(a-b),n);
        else cout<<min((k-b*n)/(a-b)-1,n);
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：王权贵哥 (赞：0)

这道题唯一注意点就是卡时间，用二分就可以ac,注意不要枚举
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;
int k,n,a,b;
//判断最大just play值为num时可取
int solve(int num,int i){  
	num+=i/b;
	if(i%b==0)num--;
	i=i%b;
	if(num>=n){
		return true;
	}else
	return false;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int i,j,num=0;
		scanf("%d%d%d%d",&k,&n,&a,&b);
		if(k%b==0)j=k/b-1;
		else j=k/b;
		if(j<n)printf("-1\n");
		else{
			if(k%a==0)j=k/a-1;
			else j=k/a;
			int zuo=0;int you=j,mid,ans=0;
			while(zuo<=you){
				mid=zuo+(you-zuo)/2;
				if(solve(mid,k-mid*a)){
					zuo=mid+1;ans=mid;
				}else you=mid-1;
			}printf("%d\n",min(n,ans));
		}
	}
}
```


---

