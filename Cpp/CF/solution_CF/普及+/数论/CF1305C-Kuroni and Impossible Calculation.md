# Kuroni and Impossible Calculation

## 题目描述

To become the king of Codeforces, Kuroni has to solve the following problem.

He is given $ n $ numbers $ a_1, a_2, \dots, a_n $ . Help Kuroni to calculate $ \prod_{1\le i<j\le n} |a_i - a_j| $ . As result can be very big, output it modulo $ m $ .

If you are not familiar with short notation, $ \prod_{1\le i<j\le n} |a_i - a_j| $ is equal to $ |a_1 - a_2|\cdot|a_1 - a_3|\cdot $ $ \dots $ $ \cdot|a_1 - a_n|\cdot|a_2 - a_3|\cdot|a_2 - a_4|\cdot $ $ \dots $ $ \cdot|a_2 - a_n| \cdot $ $ \dots $ $ \cdot |a_{n-1} - a_n| $ . In other words, this is the product of $ |a_i - a_j| $ for all $ 1\le i < j \le n $ .

## 说明/提示

In the first sample, $ |8 - 5| = 3 \equiv 3 \bmod 10 $ .

In the second sample, $ |1 - 4|\cdot|1 - 5|\cdot|4 - 5| = 3\cdot 4 \cdot 1 = 12 \equiv 0 \bmod 12 $ .

In the third sample, $ |1 - 4|\cdot|1 - 9|\cdot|4 - 9| = 3 \cdot 8 \cdot 5 = 120 \equiv 1 \bmod 7 $ .

## 样例 #1

### 输入

```
2 10
8 5```

### 输出

```
3```

## 样例 #2

### 输入

```
3 12
1 4 5```

### 输出

```
0```

## 样例 #3

### 输入

```
3 7
1 4 9```

### 输出

```
1```

# 题解

## 作者：皎月半洒花 (赞：8)

发现直接做不容易并且 $m$ 很小，于是选择观察性质。考虑鸽笼原理，当 $n>m$ 时，必有两项 $a_i,a_j$ 模 $m$ 同余。所以如果 $n>m$ 答案就是 $0$，否则暴力即可。

```cpp
int main(){
    cin >> n >> m ;
    for (int i = 1 ; i <= n ; ++ i)
        scanf("%lld", &base[i]) ;
    if (n > m) return puts("0"), 0 ;
    for (int i = 1 ; i <= n ; ++ i)
        for (int j = i + 1 ; j <= n ; ++ j)
            (ans *= (LL)abs(base[i] - base[j])) %= m ;
    cout << ans << endl ;
}
```

---

## 作者：xht (赞：3)

这个绝对值看起来不太好搞，那么我们排序一下，就一定是后面减前面了。

依次考虑每个数与前面的数对答案的贡献，但我们显然不能 $\mathcal O(n^2)$ 枚举。

注意到这个模数非常小，因此我们对前面的数开一个桶，记录每个余数的个数。

那么我们只需要 $\mathcal O(nm)$ 就可以求出每个可能的差的数量，最后快速幂一下就能求出答案了。

什么，你问 $\mathcal O(nm)$ 不是 $2 \times 10^8$ 吗，怎么能过？

你要相信 CF 神机一秒跑十亿不成问题。

```cpp
const int N = 2e5 + 7, M = 1e3 + 7;
int n, a[N], c[M];
ll f[M];
modint ans = 1;

int main() {
	rd(n), rd(P), rda(a, n);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] %= P;
		for (int j = 0; j < P; j++)
			f[(a[i]-j+P)%P] += c[j];
		c[a[i]]++;
	}
	for (int i = 0; i < P; i++) ans *= (modint)i ^ f[i];
	print(ans);
	return 0;
}
```

---

## 作者：No21 (赞：3)

## 题意分析

$n\leqslant 2\times 10^5$，因此枚举 $i$ 和 $j$ 显然是行不通的，但是我们发现模数 $m\leqslant 1000$。考虑运用**鸽巢原理**，若 $n$ 大于 $m$，则至少有一个模数会被取两次及以上。证明如下：

一个正整数对于 $m$ 取模后有 $m$ 种可能的答案，即在最劣情况下，前 $m$ 个数取模后答案各不相同，则第 $m+1$ 个数取模后答案必定与之前某个答案相同。

对于 $\prod\limits_{1\leqslant i<j\leqslant n}^{}\left\vert a_i-a_j\right\vert$ 来说，若 $a_i=a_j$，则答案为 $0$，因此，在 $n>m$ 时，答案为 $0$。当 $n\leqslant m$ 时，$n\leqslant 1000$，直接暴力枚举 $i$ 和 $j$。

上代码

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
	const int N=5021;
	int n,m;
	long long ans=1;
	int a[N];
	int mian()
	{
		cin>>n>>m;
		if(n>m)
		{
			cout<<0<<'\n';
			return 0;
		}
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<n;i++)
		{
			for(int j=i+1;j<=n;j++)
				ans=abs(ans*(a[i]-a[j]))%m;
		}
		cout<<ans;
		return 0;
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	return TO::mian();
}
```

---

## 作者：LB_tq (赞：2)

# Solution
注意到模数m很小。

- 当 $n\le m$时，可以$O(n^2)$暴力解决；

- 当 $n>m$时，由抽屉原理可知必定存在 $a_i$与$a_j$使得
$a_i\equiv a_j\pmod{m}$，即$\left\vert a_i -a_j\right\vert\bmod m=0$。故此时答案必定为$0$。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const int maxn=2e5+10;
int n,m,a[maxn],s[maxn];
ll ans=1;
int main(){
    cin>>n>>m;
    if(n<=m){
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                ans=(ans*abs(a[j]-a[i])%m)%m;
        cout<<ans;
    }
    else
        cout<<"0";
    return 0;
}
```


---

## 作者：gyh20 (赞：1)

这道题第一眼看上去以为是 $O(m^2)$ 的做法，但怎么也想不出来，只想的出来 $O(nm)$ 的做法，然而我不会卡常，浪费了两次机会。

考虑到一个性质 $0$ 乘任何数等于 $0$。

也就是说，只要出现一个 $0$ 那么结果就一定是 $0$。

那复杂度呢？因为是模 $m$，所以至多有 $m$ 种不相等情况，也就是说，至多进行 $m$ 次。

所以总复杂度从 $O(nm)$ 变成了 $O(m^2)$

```cpp
#pragma GCC optimize(2,3,4,5)
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int n,x,y,a[200002],f,m,lst,q[1002],v[1002],tp,lstans[1002];
inline int ksm(re int x,re int y){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%m;
		x=x*x%m;
		y>>=1;
	}
	return ans;
}
inline int abs(re int x){
	return x>0?x:-x;
}
int main(){
	f=1;
	n=read();m=read();
for(re int i=1;i<=n;++i)a[i]=read();
sort(a+1,a+n+1);
++v[a[1]%m];q[++tp]=a[1]%m;
for(re int i=2;i<=n;++i){
	for(re int j=1;j<=tp;++j)lstans[abs(a[i]-q[j])%m]+=v[q[j]];
	a[i]%=m;
	if(!v[a[i]])q[++tp]=a[i];
	++v[a[i]];
	if(lstans[0])break;
}
for(re int i=0;i<m;++i)f=1ll*f*ksm(i,lstans[i])%m;
printf("%d",f);
}
```


---

## 作者：Fantasy_Segment_Tree (赞：0)

## 题意

求 $\prod\limits_{1\le i<j\le n}
|a_i-a_j| \bmod m$ 的值。

## 思路

$x \bmod m$ 只有 $0$ 至 $m - 1$ 共 $m$ 种情况，所以当 $n > m$ 的时候，显然至少有一对 $i$ 和 $j$，使得 $a_i \equiv a_j \pmod b$，直接输出 $0$ 即可，否则直接暴力计算。

## 代码

```
#include <iostream>
#include <cmath>
using namespace std;
long long n, ans = 1, m, a[200005];

int main() {
	cin >> n >> m;
	if(n > m) cout << "0";
	else {
		for(long long i = 1; i <= n; i++) {
			cin >> a[i];
			for(long long j = 1; j < i; j++) {
				ans = (ans * abs(a[i] - a[j])) % m;
			}
		}
		cout << ans;
	}
}
```

---

## 作者：SpringFullGarden (赞：0)

## 题意

求 $\prod\limits_{1\le i<j\le n}
|a_i-a_j| \bmod m$。

## 思路

暴力 $+$ 特判。

当 $n > m$ 时，根据抽屉原理，$x \bmod m$ 的结果只有 $m$ 种情况，所以一定有 $\left | a_i - a_j \right| \bmod m = 0$，任意数 $\times 0 = 0$，输出 $0$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define sp() putchar(' ')
#define et() putchar(' \n')
//#pragma GCC optimize(2)
using namespace std;

inline ll rd() {
    ll x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}
inline void wt(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) wt(x / 10);
    putchar(x % 10 + '0');
    return;
}

ll a[200005];

int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
	ll n = rd(), m = rd();
	for(ll i = 1; i <= n; i++) a[i] = rd();
	if(n > m) return puts("0"), 0;
	ll ans = 1;
	for(ll i = 1; i <= n; i++) 
		for(ll j = i + 1; j <= n; j++)
			ans = ans * abs(a[i] - a[j]) % m;
	wt(ans);
    return 0;
}

```

---

## 作者：fedoralxy (赞：0)

## 解题思路

本题，我们先观察数据范围不难发现 $n$ 的范围很大，然而 $m$ 的范围却很小，于是我们考虑利用该特点解题。

进一步思考，我们利用抽屉原理：

- 当 $m$ 小于 $n$ 时，必有 $a_i\equiv a_j \pmod m$。

- 剩余情况，利用 $m$ 数据较小，暴力枚举即可

最后注意一点：

数据较大，请开**长整型**。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll long long
using namespace std;
const int N=2e5+10;
struct cplus
{
	ll n,m,total;
	ll a[N];
	void init()
	{
		total=1;
	}
}goin;
int main()
{
	goin.init();
	scanf("%d%d",&goin.n,&goin.m);
	for(int i=1;i<=goin.n;i++)
		scanf("%d",&goin.a[i]);
	if(goin.n>goin.m)
	{
		printf("0\n");
		goto FIN;
	}
	for(int i=1;i<=goin.n;i++)
		for(int j=i+1;j<=goin.n;j++)
			goin.total=(goin.total*(ll)abs(goin.a[i]-goin.a[j]))%goin.m;
	printf("%d",goin.total);
	FIN:;
	return 0;
}
```

---

## 作者：Wander_E (赞：0)

这题其实只需要考虑余数可乘性，核心公式为 $S \times m \equiv 0 \pmod m$，换句话说只要存在数对 $(i,j)$ 使得 $\lvert a_i-a_j \rvert \bmod m = 0$，答案即为 $0$ 特判加循环中判断即可。

附上 AC 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m;
int a[N];
map<int, int> mp;

signed main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		mp[a[i] % m]++;
	}
	for(auto it: mp)
	{
		if(it.second >= 2)
		{
			cout << 0 << endl;
			return 0;
		}
	}
	int sum = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			sum *= abs(a[i] - a[j]);
			if(sum % m == 0)
			{
				cout << 0 << endl;
				return 0;
			}
			sum %= m;
		}
	}
	cout << sum << endl;
	return 0;
}

```

---

## 作者：Buried_Dream (赞：0)

## Solution	

我们观察到这个 $m$ 很小。

当序列个数比模数大的时候，答案一定为 $0$。

证明一下，如果没有重复元素，肯定会出现俩个数同余的情况。

如果有重复元素，答案里乘了个 $0$，肯定还是 $0$。

所以当 $n > m$ 的时候直接输出 $0$。

否则暴力做，复杂度 $\mathcal{O}(m^2)$。

```cpp
int a[N], ans = 1;

signed main() 
{
	int n = read(), m = read();
	if(n > m) return puts("0"), 0;
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			ans = (ans * abs(a[i] - a[j])) % m;
		}
	}
	return print(ans), 0;
	return 0;
}
```

---

