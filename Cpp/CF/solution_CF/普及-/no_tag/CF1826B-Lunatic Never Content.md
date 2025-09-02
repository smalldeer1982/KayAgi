# Lunatic Never Content

## 题目描述

现在有一个数组 $a$，和 $n$ 个非负整数，定义 $f(a,x)=[a_1\bmod x,a_2\bmod x,\dots,a_n\bmod x]$，其中 $x$ 为正整数。现要你找到最大的 $x$，使得 $f(a,x)$ 是回文的。

这里，$a \bmod x$ 的含义为 $a$ 除以 $x$ 得到的余数。

我们认为一个数组是回文的，当且仅当从前往后读得到的结果和从后往前读得到的结果完全相同。换句话说，一个长度为 $n$ 的数组 $a$ 是回文的，当且仅当 $\forall 1\leq i \leq n$，有 $a_i=a_{n-i+1}$。

## 样例 #1

### 输入

```
4
2
1 2
8
3 0 1 2 0 3 2 1
1
0
3
100 1 1000000000```

### 输出

```
1
2
0
999999900```

# 题解

## 作者：_H17_ (赞：7)

## 题目分析

如果要让 $f(a,x)$ 是回文的，必须保证 $x$ 是任意满足 $1\le i < n \div 2$ 的 $a_i$ 和 $a_{n-i+1}$ 差的因数（不然取模之后就不一样了，于是就不能构成回文了）。

实现的话就让 $x$ 是所有满足 $1\le i < n \div 2$ 的 $a_i$ 和 $a_{n-i+1}$ 差的最大公因数。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long //以防万一
using namespace std;
int T,n,a[100001],ans;
signed main(){
    cin>>T;
    while(T--){//多组数据
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        ans=0;//初始化
        for(int l=1,r=n;l<=r;l++,r--)//从头尾开始来搞（因为我懒）
            ans=__gcd(ans,abs(a[l]-a[r]));//差进行最大公因数
        cout<<ans<<endl;//输出（勿忘换行）
    }
    return 0;
}
```

---

## 作者：Vct14 (赞：1)

### 题意翻译

现在有一个数组 $a$，和 $n$ 个非负整数，定义 $f(a,x)=[a_1\bmod x,a_2\bmod x,\dots,a_n\bmod x]$，其中 $x$ 为正整数。现要你找到最大的 $x$，使得 $f(a,x)$ 是回文的。

我们认为一个数组是回文的，当且仅当从前往后读得到的结果和从后往前读得到的结果完全相同。换句话说，一个长度为 $n$ 的数组 $a$ 是回文的，当且仅当 $\forall 1\leq i \leq n$，有 $a_i=a_{n-i+1}$。

### 题意分析、思路

因为 $f(a,x)$ 是回文的，所以 $x$ 应该满足 $a_i\bmod x=a_{n-i+1}\bmod x$，即 $a_i\equiv a_{n-i+1}(\bmod x)$，则 $\left| a_i-a_{n-i+1}\right|\bmod x=0$，那么 $x\mid \left|a_i-a_{n-i+1}\right|$。

求所有 $\left|a_i-a_{n-i+1}\right|$ 的最大公因数即可。

### 重点代码

```c++
long long gcd=abs(a[n]-a[1]);
for(int i=2; i<=n/2; i++) gcd=__gcd(gcd,abs(a[i]-a[n-i+1]));
cout<<gcd<<"\n";
```

---

## 作者：Night_sea_64 (赞：1)

题目其实就是让我们使得对于任意 $1\le i\le n$ 的正整数 $i$，都有 $a_i\bmod x=a_{n-i+1}\bmod x$，求最大的 $x$。

见到同余就想到要相减。因为余数具有可减性，所以 $|a_i-a_{n-i+1}|\bmod x=0$。

对于每一对数都应该是这样的，所以我们应该找到每对数差的绝对值的最大公约数就是 $x$ 了。懒得手写可以使用头文件 `#include<algorithm>` 中的 `__gcd(x,y)`，即可算出 $x,y$ 的最大公约数。按照这样的算法任何自然数与 $0$ 的最大公约数都是这个自然数，这样如果所有绝对值之差都是 $0$ 算出来的结果就自动会是 $0$ 了。代码短的可怜：

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int a[100010];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int x=0;
        for(int i=1;i<=n;i++)
            x=__gcd(x,abs(a[i]-a[n-i+1]));
        cout<<x<<endl;
    }
    return 0;
}
```

---

## 作者：Register_int (赞：1)

让他构成回文序列，即让首位对应的两个数相等。考虑在什么情况下 $x\equiv y\pmod n$，显然是在 $n\mid\text{abs}(x-y)$ 的时候。因此，求所有对应倍数的最小公倍数即可。

# AC 代码

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 1e5 + 10;
 
int t, n, a[MAXN];
 
int ans;
 
int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n), ans = 0;
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i < n - i + 1; i++) ans = ans ? __gcd(ans, abs(a[i] - a[n - i + 1])) : abs(a[i] - a[n - i + 1]);
		printf("%d\n", ans); 
	}
}
```

---

## 作者：Jerry_heng (赞：1)

（一）

如果 $x\bmod n=y\bmod n$，那么 $|x-y|$ 是 $n$ 的倍数。

所以这道题就变成了找没对数的差的最大公因数。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[100001];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		int ans=abs(a[n]-a[1]);
		for(int i=2;i<=n/2;i++)ans=__gcd(ans,abs(a[i]-a[n-i+1]));
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：zhuhongye (赞：0)

## 题目意思
这道题意思是：给定一个 $a$ 数组，现在要找一个最大的 $x$，使得 $a$ 数组各个元素取余 $x$ 是一个回文数列。

## 解题思路
这题我的思路是先用两个指针从两边进行搜索，不难发现两个数分别取余两个数的差时，它们的余数相等，所以我们每次就用一个变量 $ans$，$ans$ 一开始等于 $a_{1}$ 与 $a_{n}$ 的差，然后每次求 $ans$ 和 $a_{i}$ 与 $a_{j}$ 的差的最大公因数，最后输出 $ans$ 即可。

## 代码程序
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
long long t,n,a[1000005];
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>n;
		for(int j=1;j<=n;j++)
			cin>>a[j];
		long long ans=abs(a[1]-a[n]);//ans一开始设定为a[1]与a[n]的差
		for(int j=2,k=n-1;j<k;j++,k--)//两个指针两边搜索
			ans=__gcd(ans,abs(a[j]-a[k]));//求最大公因数
		cout<<ans<<"\n";//输出
	}
	return 0;
 } 
```


---

## 作者：大宝和小宝 (赞：0)

分析：
如果数组两侧对应的数不相等，则可以对两个数的差取模，若想满足每一对数，则对所有绝对值的差取`最大公约数`。

---------
```c
#include<iostream>
#include<iomanip>
#include<cstring>
#include<queue>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<deque>
#include<map>
#include<vector>
#include<stack>
#include<sstream>
#include<set>
#include<list>
#include<time.h>
#include<stdlib.h>
#include<ostream>
#define ll long long
#define eps 1e-14
#define INF 1e9
#define delta 0.996
#define T 3000
#define pi acos(-1.0)
#define li long double
#define ul unsigned long long
using namespace std;
int a[100010];
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<n;i++){
        	cin>>a[i];
		}
        int g=0;
        for(int i=0;i<=n;i++){
            g=__gcd(g,abs(a[i]-a[n-i+1]));
        }
        cout<<g<<endl;
    }
    return 0;
}


```


---

## 作者：Leaves_xw (赞：0)

若 $x \bmod n=y \bmod n$，则 $|x-y| \bmod n=0$。

也就是找出没对数的差的最大公因数（$\gcd$）。

寻找最大公因数可以用：`__gcd(ans,abs(a[i]-a[n-i+1]))`。

**核心代码：**

```
for(int i=1;i<=n;++i)cin>>a[i];
int ans=abs(a[n]-a[1]);
for(int i=2;i<=n/2;++i)ans=__gcd(ans,abs(a[i]-a[n-i+1]));
cout<<ans<<endl;
```

---

## 作者：zhang_kevin (赞：0)

# Solution

这道题不难，但解决前需要知道几个知识点：

1. 若 $a \bmod x = b \bmod x(a>b)$，则 $(a-b) \bmod x = 0$。

2. 若 $a \bmod x = 0$ 且 $x \bmod k = 0$，则 $a \bmod k = 0$

因此，这道题变成了找所有对数差的最大公因数。

除此之外，$x$ 可以为无限大的情况就是数组 $a$ 本身是回文的情况，需要特判输出 $0$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001];
inline void Solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	bool flag = true;
	for(int i = 1; i <= n / 2; i++){
		if(a[i] != a[n-i+1]){
			flag = false;
			break;
		}
	}
	if(flag){
		puts("0");
		return;
	}
	int ans = 0;
	for(int i = 1; i <= n / 2; i++) ans = __gcd(ans, abs(a[i]-a[n-i+1]));
	cout << ans << endl;
	return;
}
int main(){
	int t;
	cin >> t;
	while(t--) Solve();
	return 0;
}
```


---

## 作者：251Sec (赞：0)

在群里看到个群友发的 [逆天波特题解](/blog/zhangxuancheng123456/solution-cf1826b)，于是慕名而来写了下这题，题目不难。

对于每个位置 $i$，我们要求 $a_i \equiv a_{n-i+1} \pmod x$，于是可以转化为 $|a_i-a_{n-i+1}| \equiv 0 \pmod x$。

于是 $x$ 取所有的 $|a_i-a_{n-i+1}|$ 的最大公约数即可。

另外，$x$ 能取到无穷大当且仅当原序列已经是回文序列，注意到我们上面的操作在这里就是对一堆 $0$ 取 GCD，答案还是 $0$，所以可以不特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int n;
ll a[100005];
ll GCD(ll a, ll b) {
    return b ? GCD(b, a % b) : a;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        ll res = abs(a[1] - a[n]);
        for (int i = 2; i <= n / 2; i++) res = GCD(res, abs(a[i] - a[n - i + 1]));
        printf("%lld\n", res);
    }
    return 0;
}
```

---

## 作者：arrow_king (赞：0)

# 题意

现在有一个数组 $a$，和 $n$ 个非负整数，定义 $f(a,x)=[a_1\bmod x,a_2\bmod x,\dots,a_n\bmod x]$，其中 $x$ 为正整数。现要你找到最大的 $x$，使得 $f(a,x)$ 是回文的。

这里，$a\bmod x$ 的含义为 $a$ 除以 $x$ 得到的余数。

我们认为一个数组是回文的，当且仅当从前往后读得到的结果和从后往前读得到的结果完全相同。换句话说，一个长度为 $n$ 的数组 $a$ 是回文的，当且仅当 $\forall 1\leq i\leq n$，有 $a_i=a_{n-i+1}$。

# 思路

首先，想让这个数组为回文，需要使得对于 $\forall1\le i\le n$，都有 $a_i\bmod x=a_{n-i+1}\bmod x$。

不难发现这个 $x$ 一定是 $\left\vert a_i-a_{n-i+1}\right\vert$ 的因数。

>证明：这里假定 $a_i\ge a_{n-i+1}$。因为 $a_i\equiv a_{n-i+1}\pmod x$，所以可以令 $a_i=p_1x+r$，$a_{n-i+1}=p_2x+r$（$p_1\ge p_2$）。$\left\vert a_i-a_{n-i+1}\right\vert=(p_1-p_2)x$，所以 $x\big|\left\vert a_i-a_{n-i+1}\right\vert$，得证。

那么使得 $\forall1\le i\le n$，$a_i\equiv a_{n-i+1}$ 的最大正整数 $x$ 就一定是
$$\gcd\limits_{i=1}^{\lfloor\frac{n}{2}\rfloor}\left\vert a_i-a_{n-i+1}\right\vert$$
但这里要注意，如果 $a_i=a_{n-i+1}$，那么求 $\gcd$ 时会 RE，所以要跳过。当对于 $\forall1\le i\le n$，都有 $a_i=a_{n-i+1}$ 时，无论 $x$ 取何值，$a_i\equiv a_{n-i+1}\pmod x$恒成立，所以这时候输出 $0$。

线性扫一遍 $\mathcal O(n)$，求 $\gcd$ 是 $\mathcal O(\log\max\{a_i\})$，所以总时间复杂度是 $\mathcal O(n\log\max\{a_i\})$。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t;
ll n,a[100005];
il ll Abs(ll x) {
	return x>=0?x:-x;
}
il ll gcd(ll x,ll y) {
	if(x%y==0) return y;
	return gcd(y,x%y);
}
int main() {
	t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		if(n==1) {
			printf("0\n");
			continue;
		}
		ll ans=abs(a[1]-a[n]);
		for(int i=2;i<=n/2;i++) {
			if(a[i]!=a[n-i+1]) ans=gcd(ans,Abs(a[i]-a[n-i+1]));
		}
		if(ans!=1e18) printf("%lld\n",ans);
		else printf("0\n");
	}
	return 0;
}

```

---

## 作者：_5t0_0r2_ (赞：0)

# 分析：

$a_1 \bmod x = a_n \bmod x$，假设 $|a_n - a_1| = k$，根据同余的相关理论，$k \bmod x = 0$，即 $x$ 为 $k$ 的因数（$a_2,a_{n - 1}$ 等同理）。推出：

$x = \gcd(|a_n - a_1|,|a_{n - 1} - a_2|,...,|a_{n \div 2} - a_{n - n \div 2} + 1|)$。

特别的，如果 $a$ 数组本就是回文的，那么 $x$ 可以无限大，输出 ``0``。

---

## 作者：sunkuangzheng (赞：0)

**【题目描述】**

给定数组 $a$，找到最大的 $x$ 使得 $[a_1 \bmod x,a_2 \bmod x,...,a_{n-1} \bmod x,a_n \bmod x]$ 是回文串（即对于 $[1,n]$ 中的任意 $i$ 有 $a_i = a_{n-i+1}$），若无限大输出 $0$。$n \le 10^5,a_i \le 10^9$。

**【题目分析】**

我们知道 $a \equiv b \pmod x$ 成立的条件为 $(a-b)|x$，因此枚举 $n$ 对 $a_i-a_{n-i+1}$，他们的最大公约数即为答案。

**【赛时代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[100005],num[100005],cnt[100005],tt;
int gcd(int a,int b){
	return (b == 0?a:gcd(b,a%b));
}
int main(){
	cin >> t;
	while(t --){
		cin >> n;bool flag = 0;
		int mn = 1e9+7,mx = -1;
		for(int i = 1;i <= n;i ++) {cin >> a[i];mn = min(mn,a[i]);mx = max(mx,a[i]);}
		if(mn == mx){
			cout << "0\n";continue;
		}
		mx = 0;
		for(int i = 1;i <= n;i ++){
			int k = abs(a[i]-a[n-i+1]);
			if(k == 0){continue;}
			if(flag == 0) mx = k;
			flag = 1;
			mx = gcd(mx,k);
		}
		cout << mx << endl;
	}
 
	return 0;
}
```

---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1826B)

### [思路]

$x \bmod n=y \bmod n$，那 $n$ 可以被 $x-y$ 的绝对值整除。

这道题的做法也就变成了从没对数差的公因数中找出最大的那个。

### [代码]

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<map>
#include<ctime>
#include<string>
#include<cstring>
using namespace std;
typedef long long ll;
ll T,n,ans,a[100010];
int main()
{
	cin>>T;
	for(int l=1;l<=T;l++)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		ans=abs(a[n]-a[1]);
		for(int i=2;i<=n/2;i++)
		{
			ans=__gcd(abs(a[i]-a[n-i+1],ans));
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

