# Vika and Price Tags

## 题目描述

Vika came to her favorite cosmetics store "Golden Pear". She noticed that the prices of $ n $ items have changed since her last visit.

She decided to analyze how much the prices have changed and calculated the difference between the old and new prices for each of the $ n $ items.

Vika enjoyed calculating the price differences and decided to continue this process.

Let the old prices be represented as an array of non-negative integers $ a $ , and the new prices as an array of non-negative integers $ b $ . Both arrays have the same length $ n $ .

In one operation, Vika constructs a new array $ c $ according to the following principle: $ c_i = |a_i - b_i| $ . Then, array $ c $ renamed into array $ b $ , and array $ b $ renamed into array $ a $ at the same time, after which Vika repeats the operation with them.

For example, if $ a = [1, 2, 3, 4, 5, 6, 7] $ ; $ b = [7, 6, 5, 4, 3, 2, 1] $ , then $ c = [6, 4, 2, 0, 2, 4, 6] $ . Then, $ a = [7, 6, 5, 4, 3, 2, 1] $ ; $ b = [6, 4, 2, 0, 2, 4, 6] $ .

Vika decided to call a pair of arrays $ a $ , $ b $ dull if after some number of such operations all elements of array $ a $ become zeros.

Output "YES" if the original pair of arrays is dull, and "NO" otherwise.

## 说明/提示

In the first test case, the array $ a $ is initially zero.

In the second test case, after the first operation $ a = [1, 2, 3], b = [0, 0, 0] $ . After the second operation $ a = [0, 0, 0], b = [1, 2, 3] $ .

In the third test case, it can be shown that the array $ a $ will never become zero.

## 样例 #1

### 输入

```
9
4
0 0 0 0
1 2 3 4
3
1 2 3
1 2 3
2
1 2
2 1
6
100 23 53 11 56 32
1245 31 12 6 6 6
7
1 2 3 4 5 6 7
7 6 5 4 3 2 1
3
4 0 2
4 0 2
3
2 5 2
1 3 4
2
6 1
4 2
2
0 0
0 3```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES```

# 题解

## 作者：pur_lin (赞：19)

# CF1848C Vika and Price Tags

## 题目描述

给定 $ n $ ( $ 1 \le n \le 1\times10^5 $ ) 对整数 $ a,b $ ( $ 1\le a,b \le 1\times10^9 $ )，每次使 $a \gets b$，$b \gets |a-b|$，求是否能实现让所有的 $a$ 在有限次同步操作后都变为 $0$。

## 思路

显然，这道题在进行一种类似“辗转相减法”的操作。既然是辗转相减，就自然而然地想到一个关键词：$\gcd$。

我们知道，对于 $a,b$ 的最大公约数 $\gcd(a,b)$，有：

$\gcd(a,b)=\gcd(b,a-b)$

那么在辗转相减的过程当中，$\gcd(a,b)$ 显然不会改变。

而本题的要求是让 $a = 0$，此时的 $\gcd(a,b)$ 显然为 $b$。

所以最终满足题目条件的序列一定是这样的：


| $0$ | $0$ | $0$ | ...... |
| :----------: | :----------: | :----------: | :----------: |
| $\gcd(a_1,b_1)$ | $\gcd(a_2,b_2)$ | $\gcd(a_3,b_3)$ | ...... |



**我们只需要讨论所有的 $\gcd(a_i,b_i)$ 能不能同时出现。**

对于一对满足条件的数 $(0,b)$，在操作过程中它所有的状态可能是：$(0,b),(b,b),(b,0)$，并且不断在这三种状态中有序循环。

因此猜想，任意数对 $(a,b)$ 可以被分为 $3$ 类，只要序列中所有的数对都属于同一类，就说明它们总能在一定次数的操作变为满足条件的序列。

首先考虑简化，对于数对 $(a,b)$，如果在 $k$ 次操作后可以形成 $(0,z)$ 这种满足条件的数对，则 $(ia,ib)$ 也可以在 $k$ 此操作后形成满足条件的数对，且一定为 $(0,iz)$，因为在所有的相减操作中 $i$ 可以作为公因数提出。

同理，数对 $(a,b)$ 与数对 $(\frac{a}{\gcd(a,b)},\frac{b}{\gcd(a,b)})$ 也一定是等价的。

接下来对互质数对 $(a,b)$ 进行分类，一个显而易见的事实是，当 $a$ 与 $b$ 互质，会有 $\{a$ 为奇，$b$ 为偶 $\}$，$\{a$ 为偶，$b$ 为奇 $\}$，$\{a$ 为奇，$b$ 为奇 $\}$ 三种情况。

如何证明以上三种情况就是我们想要的三种分类呢？

我们先设 $a=2k,b=2k+1$，得到以下过程：

| $a$ | $2k$ | $2k+1$ | $1$ | $2k$ | $2k-1$ | $1$ | $2k-2$ | ... |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $b$ | $2k+1$ | $1$ | $2k$ | $2k-1$ | $1$ | $2k-2$ | $2k-3$ | ... |


发现数对 $(a,b)$ 总是在我们给出的以上三种情况中反复循环。

即便把 $b$ 换成 $2k+2x+1$ 等任何奇数，也同样成立。

以奇偶，奇奇开始同理。

所以我们证明了，数列能否合法，只与其间数对的奇偶性有关。如果数对的奇偶性有且仅有唯一的一种，那么就能成立。

当然也需要考虑特殊情况，比如全为 $(0,0)$ ，此时无法计算 $\gcd$ ，可以特判，或者认为其没有任何一种奇偶性。

以上。

## 最终代码

```cpp
#include<iostream>
using namespace std;
const int N=2e5+10;
int a[N],b[N],sum[5];
int gcd(int x,int y){
    if(y==0) return x;
    return gcd(y,x%y);
}
int check(int x,int y){
    int t=gcd(x,y);
    x/=t;y/=t;
    if(x%2==0) return 0;
    if(y%2==0) return 1;
    return 2;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
    	for(int i=1;i<=n;i++) cin>>a[i];
    	for(int i=1;i<=n;i++) cin>>b[i];
    	int res;
        sum[0]=sum[1]=sum[2]=0;
    	for(int i=1;i<=n;i++){
            if(a[i]==0&&b[i]==0) continue;
            res=check(a[i],b[i]);
            sum[res]=1;
    	}
    	if(sum[0]+sum[1]+sum[2]<=1) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```

### 建议评黄

蒟蒻第一篇题解，求管理大大开恩 qwq。

curlin 2023.7.17

---

## 作者：Phartial (赞：15)

每组 $(a_i,b_i)$ 之间相互独立，于是我们只需要考虑一对数 $(a,b)$。

首先 $(0,0)$ 的情况是平凡的。考虑我们需要的状态 $(0,b)$，它的变化过程是这样的：$(0,b)\to(b,b)\to(b,0)\to(0,b)$，所以是三轮一个循环，且除了 $(0,b)$ 之外另外两组状态都不合法。我们求出每组 $(a_i,b_i)$ 变成 $(0,x)$ 需要的步数 $s_i$，那么答案为 `YES` 当且仅当对所有 $1\le i,j\le n$ 都有 $s_i\equiv s_j\pmod 3$，证明是显然的。

那么问题变成了怎么快速求出 $s_i$，我们参考辗转相除法，假设 $a<b$，那么可以将 $b$ 表示成 $b=ka+p$，其中 $0\le p<a$，于是状态变化如下：

$$
(a,ka+p)\to(ka+p,(k-1)a+p)\to((k-1)a+p,a)\to(a,(k-2)a+p)
$$

发现三次操作后 $k$ 变成了 $k-2$，又因为我们只在乎 $s_i\bmod 3$ 的值，所以可以直接将 $k$ 对 $2$ 取模。取模后如果 $k=1$，那么变化流程如下：$(a,a+p)\to(a+p,p)\to(p,a)$，我们使用 $2$ 次操作将其变成 $(p,a)$，该状态可以递归处理；否则直接递归处理 $(a,p)$。

若 $a>b$，变化是类似的，三步操作使 $k$ 减二，最后如果 $k=1$，变化流程如下：$(b+p,b)\to(b,p)$，一次操作将其变成 $(b,p)$ 后递归处理。

最后递归终止状态为 $a=0$ 或 $b=0$，这两种情况是 trival 的。

时间复杂度证明和辗转相除法一样，总时间复杂度为 $\mathcal{O}(n\log v)$。

```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 1e5 + 1;

int t, n, a[kN], b[kN], c[3];

int C(int a, int b) {
  if (!a || !b) {
    return !!a;
  }
  if (a < b) {
    int k = b / a, p = b % a;
    return (k & 1) ? 2 + C(p, a) : C(a, p);
  } else {
    int k = a / b, p = a % b;
    return (k & 1) ? 1 + C(b, p) : C(p, b);
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
      cin >> b[i];
    }
    c[0] = c[1] = c[2] = 0;
    for (int i = 1; i <= n; ++i) {
      if (a[i] || b[i]) {
        ++c[C(a[i], b[i]) % 3];
      }
    }
    cout << (count(c, c + 3, 0) >= 2 ? "YES" : "NO") << '\n';
  }
  return 0;
}
```


---

## 作者：Jasper08 (赞：5)

显然 $x,y$ 经过一系列辗转相减后一定会变成 $0$，最后进入 $d,d,0,d,d,0,\cdots$ 的循环，其中 $d=\gcd(x,y)$。所以我们只需要判断 $a_i,b_i$ 辗转相减得到的操作序列模 $3$ 的余数是否相同即可。那么我们可以将操作序列中的所有数都除以 $d$，将奇数视为 $0$，将偶数视为 $1$，那么一定会变为 $\cdots,1,1,0,1,1,0$ 的循环。

观察这个循环可以发现，若 $x,y$ 在序列中为 $1,1$，则操作序列长度模 $3$ 余 $0$；若 $x,y$ 在序列中为 $1,0$，则操作序列长度模 $3$ 余 $2$；若 $x,y$ 在序列中为 $0,1$，则操作序列长度模 $3$ 余 $1$。注意特判 $x=y=0$ 的情况。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1e5+10;

int t, n, cnt = -1, a[N], b[N];

int main() {
	scanf("%d", &t);
	while (t -- ) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for (int i = 1; i <= n; ++i) scanf("%d", &b[i]);
		
		bool check = 1; cnt = -1;
		for (int i = 1; i <= n; ++i) {
			int mod;
			if (!a[i] && !b[i]) continue;
			if (!a[i]) mod = 1;
			if (!b[i]) mod = 2;
			else {
				int d = __gcd(a[i], b[i]), x = a[i]/d, y = b[i]/d;
				if (x % 2) x = 1; else x = 0;
				if (y % 2) y = 1; else y = 0;
				if (!x && y) mod = 1; else if (x && y) mod = 0; else mod = 2;
			}
			if (cnt == -1) cnt = mod;
			else if (cnt != mod) check = 0;
		} 
		(check) ? puts("YES") : puts("NO");
	}
	return 0;
}
```

---

## 作者：winter2020 (赞：4)

给一个较新的做法（？感觉推导过程不是很一样。

发现想要 $a_i$ 全部变为 $0$，必须在同一时间所有的 $a_i$ 都是偶数且都为 $0$（废话）。

直接考虑 $a_i$ 和 $b_i$ 的奇偶性，进行分讨。

统一规定：在奇偶性推导过程中奇数代指为 $1$，偶数代指为 $0$。

1.$a_i$ 为偶数，$b_i$ 为奇数，则奇偶性变化过程如下：

`0 1` $\rightarrow$ `1 1` $\rightarrow$ `1 0` $\rightarrow$ `0 1`

2. $a_i$ 为奇数，$b_i$ 为偶数，则奇偶性变化过程如下：

`1 0` $\rightarrow$ `0 1` $\rightarrow$ `1 1` $\rightarrow$ `1 0` $\rightarrow$ `0 1`

3. $a_i$，$b_i$ 都为奇数，则奇偶性变化过程如下：

`1 1` $\rightarrow$ `1 0` $\rightarrow$ `0 1` $\rightarrow$ `1 1` $\rightarrow$ `1 0` $\rightarrow$ `0 1`

$a_i$，$b_i$ 都为偶数的情况暂时跳过，在上面三种情况里，发现经过有限次操作后肯定能得到形如 $0\ x$ 的样式，其中 $0\ x$ 经过 $3$ 次操作后可以变回 $0\ x$。

在操作次数对 $3$ 取模意义下，第二种情况比第一种情况多 $1$ 次操作，第三种情况比第一种情况多 $2$ 次操作，**故三种情况只能出现一种**。

继续考虑一下两个数都是偶数的情况，思考后可以发现将 $a_i$ 和 $b_i$ 都除 $2$ 后答案不变。可以理解为将过程中每一步的数都除了 $2$。

于是可以直接将两个数不断除 $2$，直至两个数有一个数是奇数为止，然后就可以归纳进前面的情况。

记得特判两个数都是 $0$ 的情况即可。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int n;
int a[N], b[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    bool st[3] = {0, 0, 0};
    for (int i = 1; i <= n; i ++ ) {
        cin >> b[i];
        if (!a[i] && !b[i]) continue;
        if (a[i] || b[i]) {
            while (a[i] % 2 == 0 && b[i] % 2 == 0) a[i] /= 2, b[i] /= 2;
        }
        if (a[i] % 2 == 0) st[0] = true;
        else if (b[i] % 2 == 0) st[1] = true;
        else st[2] = true;
    }
    int cnt = 0;
    for (int i = 0; i < 3; i ++ ) cnt += st[i];
    if (cnt > 1) puts("No");
    else puts("Yes");
    return;
}

int main() {
    int T;
    cin >> T;
    while (T -- ) solve();
    return 0;
}
```

---

## 作者：revolutionary_oier (赞：1)

## 题目描述
https://www.luogu.com.cn/problem/CF1848C
## 思路点拨
首先原题每次操作使：
- $a_i=b_i$
- $b_i=|a_i-b_i|$
( $2$ 操作同时进行。)
这个操作本身就是属于**九章算术**里的**更相减损术**，最终当 $a_i=0$ 时，同理 $b_i=\gcd(a_i,b_i)$，这就证明了对于 $\forall i \in [1,n]$ 均能通过数次操作之后满足 $a_i=0$。

当 $a_i=0$ 后，我们会发现一个周期性现象如下：
$a_i$|$b_i$
-------- | -----
$0$|$\gcd(a_i,b_i)$
$\gcd(a_i,b_i)$|$\gcd(a_i,b_i)$
$\gcd(a_i,b_i)$|$0$
$0$|$\gcd(a_i,b_i)$
$\gcd(a_i,b_i)$|$\gcd(a_i,b_i)$
……|……

由此进入长度为 $3$ 的循环，之后发现当 $a_i$ 和 $b_i$ 的奇偶性所组成的数对决定了到底在第 $m \bmod 3$ 次出现 $a_i=0$ 的情况。
还有 $2$ 点需要注意：
- $a_i=b_i=0$ 满足任意情况。
- $a_i \equiv 0 \pmod 2$ 且 $b_i \equiv 0 \pmod 2$ 将 $a_i,b_i$ 同时除 $2$ 直到其中一方没有因子 $2$。

AC

## 题目收获
分类

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;

const int maxn=1e5+10;
int t,n;
int a[maxn],b[maxn],f[maxn];
inline void input(){
    scanf("%lld",&n);
    for(register int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(register int i=1;i<=n;i++)scanf("%lld",&b[i]);
}
inline bool check(){
    for(int i=1;i<=n;i++){
        if(a[i]==b[i]&&a[i]==0){
        	f[i]=-1;
			continue; 
		}
        while(a[i]%2==0&&b[i]%2==0)a[i]/=2,b[i]/=2;
        if(a[i]%2==1&&b[i]%2==1)f[i]=1;
        else if(a[i]%2==1&&b[i]%2==0)f[i]=2;
        else f[i]=3;
    }
    sort(f+1,f+n+1);
    for(int i=1;i<n;i++){
        if(f[i]==-1)continue;
        if(f[i]!=f[i+1])return false;
    }
    return true;
}
inline void solve(){
    if(check())printf("YES\n");
    else printf("NO\n");
}
signed main(){
    scanf("%lld",&t);
    while(t--){
        input();
        solve();
    }
    return 0;
}
```

---

## 作者：StarLbright40 (赞：1)

>[C. Vika and Price Tags](https://codeforces.com/contest/1848/problem/C)
>
>给出长为 $n$ 的数组 $\{a\},\{b\}$，执行如下流程：
>- 若数组 $\{a\}$ 全零，退出；
>- 构造长为 $n$ 的数组 $\{c\}$ 满足 $c_i=|a_i-b_i|$；
>- 将 $\{b\}$ 复制到 $\{a\}$，将 $\{c\}$ 复制到 $\{b\}$;
>- 如此循环。
>
>询问是否能够退出。
>
>$T$ 组数据。$1\le T\le10^4,1\le\sum n\le10^5,0\le a_i,b_i\le 10^9$。

注意到每个下标是独立的，拆开考虑。于是数组相当于 $n$ 组独立的变量 $(a,b)$。

注意到当 $a$ 取得 $0$ 时，$a$ 沿时间轴的值将会按 $\{0,b,b,0,b,b,\cdots\}$ 变化。这启发我们关注 $a$ 取得 $0$ 的时间 $\bmod~3$ 的值。此时 $a=b=0$ 的情况平凡。

操作类似于辗转相减，所以对于一组 $(a,b)$，$a$ 总能取到 $0$。

在操作 $\bmod~3$ 意义下，可以将 $a,b$ 中的较大值对较小值的两倍取模，加速模拟。判断是否存在一个下标 $\bmod~3$ 的余数能使所有数对取到即可。时间复杂度 $\mathcal O((\sum n)\log V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
int T,n,a[N],b[N],c[3];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	for(cin>>T;T--;){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=n;++i) cin>>b[i];
		for(int i=1;i<=n;++i){
			if(!a[i]&&!b[i]){++c[0],++c[1],++c[2];continue;}
			int cnt=0;
			if(a[i]&&b[i]) a[i]>b[i]?a[i]%=b[i]*2:b[i]%=a[i]*2;
			for(;a[i];++cnt){
				tie(a[i],b[i])=make_pair(b[i],abs(a[i]-b[i]));
				if(a[i]&&b[i]) a[i]>b[i]?a[i]%=b[i]*2:b[i]%=a[i]*2;
			}
			++c[cnt%3];
		}
		cout<<(max({c[0],c[1],c[2]})==n?"YES\n":"NO\n");
		c[0]=c[1]=c[2]=0;
	}
	return 0;
}
```

注意到，将 $a,b$ 同时除以 $\gcd(a,b)$ 不会影响上面的模拟过程，而此时 $a,b$ 一定不会同为偶数。手玩操作过程发现此时一定有“偶奇 $\to$ 奇奇 $\to$ 奇偶 $\to$ 偶奇”这样的循环，而 $a=0$ 时显然为“偶奇”。

于是我们可以省去模拟的过程，直接按奇偶性来计算余数。

但到此为止并没有优化复杂度。可以发现除以奇质因数不会影响数的奇偶性，所以我们可以仅将 $\gcd(a,b)$ 中 $2$ 的部分除去，也就是仅计算 $a,b$ 中 $2$ 的幂次。使用 `__builtin_ctz()` 函数即可解决。时间复杂度 $\mathcal O(\sum n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
int T,n,a[N],b[N],c[3];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	for(cin>>T;T--;){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=n;++i) cin>>b[i];
		for(int i=1,x;i<=n;++i){
			if(!a[i]&&!b[i]){++c[0],++c[1],++c[2];continue;}
			x=min(a[i]?__builtin_ctz(a[i]):30,b[i]?__builtin_ctz(b[i]):30);
			++c[(a[i]>>x&1)*2+(b[i]>>x&1)-1];
		}
		cout<<(max({c[0],c[1],c[2]})==n?"YES\n":"NO\n");
		c[0]=c[1]=c[2]=0;
	}
	return 0;
}
```


---

## 作者：luckydrawbox (赞：1)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1848C)

## 题意

给定两个长度为 $n$ 的数组 $a_{1\sim n}$，$b_{1\sim n}$，每次可以进行如下操作：

- 对于每个 $i\in[1,n]$，$a_i\leftarrow |a_i-b_i|$。
- 对于每个 $i\in[1,n]$，交换 $a_i,b_i$。

求多次操作后是否能使所有 $b_i$ 变成 $0$。

## 分析

假如 $a_i=5,b_i=3$，可以发现它们是这样变化的：$(5,3)\rightarrow(3,2)\rightarrow(2,1)\rightarrow(1,1)\rightarrow(1,0)\rightarrow(0,1)\rightarrow(1,1)\rightarrow(1,0)\rightarrow(0,1)\rightarrow\dots\dots$

在 $(a_i,b_i)$ 变成 $(x,0)$ 后，它就会开始循环：$(x,0)\rightarrow(0,x)\rightarrow(x,x)\rightarrow(x,0)$，循环节为 $3$，于是我们就可以记录 $c_{i,j}$ 表示 $(a_i,b_i)$ 经过 $3k+j(k\in N_+)$ 次操作后，$b_i$ 能否变成 $0$，若存在 $j$ 满足 $c_{i,j}(i\in[1,n])$ 全为 $1$，那么就可以使所有 $b_i$ 变成 $0$。

如果直接暴力计算出 $b_i$ 求 $c_{i,j}$ 的话，肯定会超时，需要优化。我们假设 $a_i$ 远大于 $b_i$，那么 $a_i-b_i$ 一定是正的，假设如果连续多次减法都不出现负数的话，变化的过程就是这样的 $(a_i,b_i)\rightarrow(b_i,a_i-b_i)\rightarrow(a_i-b_i,a_i-2b_i)\rightarrow(a_i-2b_i,b_i)\rightarrow(b_i,a_i-3b_i)\rightarrow(a_i-3b_i,a_i-4b_i)\rightarrow(a_i-4b_i,b_i)\rightarrow(b_i,a_i-5b_i)\rightarrow\dots\dots$

可以发现从 $(b_i,a_i-b_i)$ 开始也有一个类似循环 $(b_i,a_i-(2k-1)b_i)\rightarrow(a_i-(2k-1)b_i,a_i-2kb_i)\rightarrow(a_i-2kb_i,b_i)\rightarrow(b_i,a_i-(2k+1)b_i)$。所以我们可以一次性将 $(a_i,b_i)$ 变为 $(b_i,a_i-(2k+1)b_i)$，即一次性将 $a_i$ 减去奇数个 $b_i$，当然前提是这个差大于 $0$，最终操作次数会增加 $3k+1$ 步。每次用最大的 $k$ 来操作，令值域为 $S$，复杂度就为 $O(n\log S)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+10;
int t,n,a[N],b[N],c[N][3];
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			c[i][0]=c[i][1]=c[i][2]=0;
		}
		for(int i=1;i<=n;i++){
			b[i]=read();
			c[i][0]=c[i][1]=0;
		}
		int ans1=1,ans2=1,ans3=1;
		for(int i=1;i<=n;i++){
			if(a[i]==0&&b[i]==0){
				c[i][0]=c[i][1]=c[i][2]=1;
			}
			else{
				int u=0,d;
				while(b[i]){
					if(a[i]<=b[i]||a[i]/b[i]<2){
						d=abs(a[i]-b[i]);
						a[i]=b[i];
						b[i]=d;
						u=(u+1)%3;
					}
					else{
						int p=a[i]/b[i],q;
						if((p&1)==0)
							p--;
						u=(u+(p-1)/2*3+1)%3;
						q=a[i]-p*b[i];
						a[i]=b[i];
						b[i]=q;
					}
				}
				c[i][u]=1;
			}
			ans1&=c[i][0];
			ans2&=c[i][1];
			ans3&=c[i][2];
		}
		if(ans1||ans2||ans3)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

显然是分开来做，然后看是不是一样的就可以了。

那么，我们的任务就是求 $a,b$，用多少次上面的操作可以变成 $0,gcd$ 或者 $gcd,0$ 的形式（反正两者只差一步，判就好了）。

注：上面的 $gcd$ 指的是 $a,b$ 的最大公约数。

显然辗转相减，但是会 TLE。

而且，如果我们手摸一下下面这一组样例：

```
7
1 2 3 4 5 6 7
7 6 5 4 3 2 1
```

发现辗转相减法的次数不好直接计算。

继续模拟，发现初始 $a,b$ 关系确定的时候有一些规律。

不妨 $a>b$，而且 $\dfrac{a}{b}\rightarrow\inf$。

那么，我们可以列出下面的表格。为了方便辨认，令初始时 $x=a,y=b$。

那么，我们令 $x-ny$ 表示第 $n$ 次相减，最后的 $n$ 可以轻松算出。

| 次数 | $0$ | $1$ | $2$ |$3$  | $4$ |$5$|$6$|$7$|
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |-:|-:|-:|
| $a$ |$x$  |$y$  |$x-y$  |$x-2y$  | $y$ |$x-3y$|$x-4y$|$y$|
| $b$ |$y$  |$x-y$  |$x-2y$  |$y$  | $x-3y$ |$x-4y$|$y$|$x-5y$|
|备注|初始|第一次相减||第二次相减|第三次相减||第四次相减||

发现了吗，是差为 $1,2,1,2,\dots$ 进行排列的。

但是我代码里写的是 $a<b$ 的情况，枚举会发现差是 $2,1,2,1,\dots$ 排列的。

下面按我代码中情况为准。

所以，如果 $n=\left\lfloor\dfrac{b}{a}\right\rfloor$，那么差为 $1$ 的就是 $\left\lfloor\dfrac{n}{2}\right\rfloor$，差为 $2$ 的有 $\left\lceil\dfrac{n}{2}\right\rceil$ 个。

同时可以发现，如果 $n$ 是奇数，那么最后是 $y$（较小数）的应该是 $b$，否则是 $a$。

因为我举例和代码取相反，所以建议大家自己画一下，对你有帮助。

如果 $a>b$，因为懒，不想判断，所以减到 $a<b$ 即可。

那么，为什么直接减到 $a<b$ 的复杂度是正确的呢？

如果 $a>b$，进行一次操作之后，$a'=b,b'=a-b$，如果还有 $a'>b'$，说明 $b>a-b$，则说明 $2b<a$，那么，我们进行了一次折半的操作，复杂度还是 $O(\log n)$。

[code](https://codeforces.com/contest/1848/submission/239452608)

---

