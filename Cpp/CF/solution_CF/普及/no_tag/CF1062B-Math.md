# Math

## 题目描述

JATC的数学老师为了不让同学们感到厌倦，总是出一些有趣的题目。今天的题目是这样的：  
给定一个整数`n`，您可以对它进行如下操作：  
* 乘以`x`：把n乘上x（x是任意正整数）。
* 开方：把n的值更新为$\sqrt{n}$ (前提是$\sqrt{n}$必须为整数)。  
您可以对这些操作进行零次至任意次。那么n可以达到的最小值是多少 ？达到最小值需要进行操作的次数又是多少？  
显然，班里没有同学能够解决这个问题，您能够帮帮他吗？

## 说明/提示

在样例1中，可以先乘上5得到100，再开方得到10。  
在样例2中，可以先开方得到72，再乘18得到1296，最后再开方两次，最终得到6。
注意，即使$n$小于等于$10^6$，它仍然可以在一次或数次操作后超过$10^6$。

## 样例 #1

### 输入

```
20
```

### 输出

```
10 2```

## 样例 #2

### 输入

```
5184
```

### 输出

```
6 4```

# 题解

## 作者：Insouciant21 (赞：4)

要使最终 $n$ 的值最小，就要尽可能多的进行开方（因为 $x\geq 1$ ，所以  $n\times x\geq n$ ）

对 $n$ 进行质因数分解，得到 $n=p_1^{k_1}p_2^{k_2}\cdots p_m^{km}$

此时得到了次数，便于进行开方。

容易发现，开方后得到的最小结果为 $ans=\prod_{i=1}^mp_i$

因为开方操作每次将每一项的次数减半，所以需要先进行一次乘法来使每一项的次数都可以表示为 $2^n$ 。

最后进行多次开方即可。

取开方次数，即求最小的 $x$ 使 $ans^x\geq n$

当 $ans^x>n$ 时，还需进行一次乘法。

AC代码

```
#include <bits/stdc++.h>

using namespace std;

int n;
int ans = 1;

void factor(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            ans *= i;
        }
    }
    if (n > 1)
        ans *= n;
}

int main() {
    scanf("%d", &n);
    factor(n);
    long long res = ans;
    int step = 0;
    while (res % n != 0) {
        res *= res;
        step++;
    }
    if (res > n)
        step++;
    printf("%d %d", ans, step);
    return 0;
}
```

当然也可以记录质因数的最大次数 $k$ ，求最接近 $k$ 且大于 $k$ 的 $2$ 的幂即为开方次数。





---

## 作者：过氧化氢_syq0057 (赞：1)

题目翻译其实有问题。

应该是输出 $n$ 能达到最小值和需要的最小步数。

考虑最后得到的 $n$ 最小。

首先将 $n$ 质因数分解，得 $n=a_1^{p_1} a_2^{p_2} ... a_k^{p_k}$。

最后最小的 $n=a_1 a_2 ... a_n$。

然后考虑最小的步数。

首先如果 $n$ 是个素数，那直接不用操作了，最小值就是本身，输出```n 0```。

否则先将 $n$ 能开几次根就开几次。

如果 $n$ 开根后各个指数均为 $1$，那直接返回，操作次数=开根次数。

否则就乘以一个数 $x$ 将各个指数都补至 $2^i,i \in N^{+}$，再开根 $i$ 次得到最小值。

思路十分简单.

### Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
const int N = 505;
const int M = 1000000;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
ll n;
int ans = 1, num;
bool vis[M + 5];
int prime[M + 5], op;
void oula() {
	vis[1] = 1;
	for (int i=1; i<=M; i++) {
		if (!vis[i]) prime[++op] = i;
		else continue;
		for (int j=i+i; j<=M; j+=i)
			vis[j] = 1;
	}
}//筛素数
int solve(ll x) {
	int cnt = 0, res = 0, i = 1;
	while (x != 1 && (ll)pow(x, 0.5) * (ll)pow(x, 0.5) == x) x = pow(x, 0.5), cnt++;
	if (x == 1) {
		num = cnt;
		return 0;
	}//直接开根到了最小值就结束。
	num += 1 + cnt;//加上乘x的1次
	while (x != 1) {
		cnt = 0;
		while (x % prime[i] == 0) x /= prime[i], cnt++;
		if (cnt) ans *= prime[i];//累乘答案
		i++;
		res = (res > cnt ? res : cnt);
	}//找最大指数
	if (res == 1) num--;//如果最大指数为1那就可以省掉那次乘x
	return res > 1 ? res : 0;//res==1时不用继续开根，否则继续
}
bool isprime(ll x) {
	for (int i=1; i<=op; i++)
		if (prime[i] == x)
			return 1;
	return 0;
}
int main() {
	oula();
	scanf("%lld", &n);
	if (n == 1 || isprime(n)) {
		printf("%lld %d\n", n, 0);
		return 0;
	}
	int s = solve(n);
	for (ll i=1; s; i++) {
		if ((1ll << i) >= s) {
			num += i;//找共同需要补至的2^i，然后开根i次
			break;
		}
	}
	printf("%d %d\n", ans, num);
	return 0;
}
```

完结散花qaq

---

## 作者：__Hacheylight__ (赞：1)

本题居然没有题解，我来写一篇

我们发现如果一个数$x$的分解质因数结果中有一些因数的质数不为零，我们总能够通过乘再开根使得他变为零，但不可能消失

于是第一个答案就是该数的所有质因子的积$y$

对于第二问，我们也就是要求从$x$到$y$的变化次数

我们发现只会有一次乘法，因为只需要一次乘法+多次开根就可以搞定

那我们只需要每次把$y$平方一下，如果是$x$的倍数的话就break

特判正好等于$x$的情况

然后就做完了

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define per(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define enter cout << endl
#define SZ(x) ((int)x.size())
typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 100010 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

ll n, tot, ans, tmp, num = 1 ;

int main() {
    scanf("%lld", &n) ; tot = n ;
    for (int i = 2; i <= n; i++) {
        if (tot % i == 0) {
            num *= i ;
            while (tot % i == 0) tot /= i ;
        }
    }
    ll ans = 0, tmp = num ;
    while (num % n) {
        num *= num ;
        ans++ ;
    }
    printf("%lld %lld\n", tmp, num > n ? ans + 1 : ans) ;
}

```

---

## 作者：leo120306 (赞：0)

题面良心地给了翻译。

有乘法，有开方，显然与素因数分解有关。设 $n=\prod p_i^{a_i}$（$p_i$ 为素数，$a_i$ 为正整数），那么要使值最小，就要尽量开方。$p_i$ 都是素数，当然没有办法进一步开方。开方的本质是将每一个指数 $a_i$ 除以 $2$，那么令所有 $a_i$ 均为 $2^k$（$k$ 为正整数）时，可以进行 $k$ 次开方操作，使 $n=\prod p_i$，值最小。因此第一问的答案即为 $n=\prod p_i$。

第二问中，我们如何令 $n=\prod (p_i)^{2^k}$？显然，将 $n$ 乘上 $\prod (p_i)^{(2^k-a_i)}$ 即可。因此，乘法**最多**进行一次，因为当乘数为 $1$ 时可以不进行乘法。然后进行 $k$ 次开方。那么要让总操作次数最小，就要让 $k$ 尽量小。但又注意到 $k$ 还需满足 $2^k-(\max a_i) \geq 0$。我们解这个不等式得 $k\geq \log_2 (\max a_i)$，即最小整数解为 $k=\lceil\log_2 (\max a_i)\rceil$。第二问的答案也呼之欲出。

---
细节：
1. 要特判 $1$。上面的讨论都自动排除了 $1$ 这种特殊情况。
2. 仔细思考什么时候不用进行乘法操作。
```cpp
#include <cstdio>
#include <cmath>
using namespace std;

int times[1000005];

int main(){
	int n,nn;
	scanf("%d",&n);
	if(n==1){
		printf("1 0");
		return 0;
	}
	int maxtm=0,tmcnt=0;
	nn=n;
	for(int i=2;i<=n;i++){
		while(!(nn%i)){
			nn/=i;
			times[i]++;
		}
		if(times[i]>maxtm)maxtm=times[i];
	}
	for(int i=2;i<=n;i++)
		if(times[i]<maxtm&&times[i])
			tmcnt++;
	if(maxtm==1){
		printf("%d 0",n);
	}else{
		int ans1=1;
		for(int i=2;i<=n;i++)
			if(times[i])
				ans1*=i;
		int ans2=ceil(log2(maxtm));
		if(pow(2,ans2)!=maxtm||tmcnt) ans2++;
//		printf("[Debug]%d %d\n",maxtm,tmcnt);
		printf("%d %d",ans1,ans2);
	}
	
	return 0;
}
```

---

## 作者：King_duck (赞：0)

通过分解 $n$，我们得到 $n=p1^{a1}$ $p2^{a2}$ $\ldots pk^{ak}$（$k$ 是质因数的个数）。因为我们不能去掉这些质因数所以最小的 $n$ 是 $p_1$ $p_2\ldots p_k$。对于每一个 $a_i$，令 $ui$ 为正整数，使 $2u_i\ge a_i > 2u_i$ $−$ $1$。设 $U$ 为 $\operatorname{max}(u_i)$ 很明显，我们必须应用“平方根”运算至少 $U$ 次，因为每次我们应用它时，所有 $i$ 都除以 $2$。如果对于所有 $i$，$a_i=2U$ 那么答案显然是 $U$。否则，我们需要使用“$mul$”运算 $1$ 次，使所有的 $a_i$ 等于 $2U$，现在答案是 $U+1$。 复杂度：$O(\sqrt N)$。

代码就不贴了（逃）。

---

