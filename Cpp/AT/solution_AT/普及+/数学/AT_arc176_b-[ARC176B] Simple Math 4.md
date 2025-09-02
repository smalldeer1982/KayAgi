# [ARC176B] Simple Math 4

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc176/tasks/arc176_b

$ 2^N $ を $ 2^M\ -\ 2^K $ で割ったあまりの $ 1 $ の位を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ N\ \le\ 10^{18} $
- $ 1\ \le\ K\ <\ M\ \le\ 10^{18} $
- $ N,M,K $ は整数
 
### Sample Explanation 1

$ 1 $ 個目のテストケースについて、$ 2^9 $ を $ 2^6\ -\ 2^2 $ で割ったあまりは $ 32 $ です。よって $ 32 $ の $ 1 $ の位の $ 2 $ が答えです。

## 样例 #1

### 输入

```
5
9 6 2
123 84 50
95 127 79
1000000007 998244353 924844033
473234053352300580 254411431220543632 62658522328486675```

### 输出

```
2
8
8
8
4```

# 题解

## 作者：Register_int (赞：8)

我们可以每次只除一轮。如果 $n\ge m$，那么 $2^n=2^n-2^{n-m}(2^m-2^k)=2^n-2^n+2^{n-(m-k)}\equiv2^{n-(m-k)}$。那么本题的意义实际上就是一直做 $n\to n-(m-k)$ 直到 $n<m$。这个直接做就可以了。记得特判一些特殊情况，比如 $2^m-2^k$ 刚好是 $2$ 的幂这种。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

inline 
int qpow(int b, ll p) {
	int res = 1;
	for (; p; p >>= 1, b = b * b % 10) if (p & 1) res = res * b % 10;
	return res;
}

int T; ll n, m, k;

int main() {
	for (scanf("%d", &T); T--;) {
		scanf("%lld%lld%lld", &n, &m, &k);
		if (m - 1 == k) { printf("%d\n", m - 1 <= n ? 0 : qpow(2, n)); continue; }
		if (n < m) { printf("%d\n", qpow(2, n)); continue; }
		n = n - ((n - m) / (m - k) + 1) * (m - k);
		printf("%d\n", qpow(2, n));
	}
}
```

---

## 作者：xuezhiyu (赞：3)

# 题面

## 题目描述

输出 $2^N \mod(2^M-2^K)$ 的个位。

## 数据范围

$1 \le T \le 2 \times 10^5$

$1 \le N \le 10^{18}$

$1 \le K \le M \le 10^{18}$

$N,M,K \in N^+$

# 分析题目

对于这道题，我们需要分类讨论：

- $M=K+1~\wedge~N \ge K$，此时 $2^M-2^K=2^{K+1}-2^K=2^K$，因为 $N \ge K$，所以 $2^N \mod 2^K=0$，输出 $0$ 就行了。
- $M=K+1~\wedge~N<K$，那么 $2^N<2^K$，然后 $2^N \mod 2^K=2^N$，答案就是 $2^N$ 的最后一位了。
- $M \ne K+1~\wedge~N<M$，由于题目保证 $K < M$，所以 $2^M-2^K \ge 2^{M-1}$（$2^M-2^{M-1}=2^{M-1} \ge 2^K$）仅当 $M=K+1$ 是相等，又因为条件保证了 $M \ne K+1$，所以 $2^{M-1}<2^M-2^K$，推得 $\displaystyle \frac{2^{M-1}}{2^M-2^K}<1$ 又因为 $N \le M$ 所以 $\displaystyle \frac{2^N}{2^M-2^K}<1$，所以 $\lfloor \displaystyle \frac{2^{M-1}}{2^M-2^K} \rfloor=0$；又因为 $2^N \mod (2^M-2^K)=2^N-(2^M-2^K) \times \displaystyle \lfloor \frac{2^N}{2^M-2^K} \rfloor$，所以答案就是 $2^N$ 的个位。
- $M \ne K+1~\wedge~N \ge M$，这是一般情况，详细说说。

## 一般情况

对于模运算后面的式子 $\displaystyle \frac{2^N}{2^M-2^K}$，分子分母同时除以 $2^K$ 得到 $\displaystyle \frac{2^{N-K}}{2^{M-K}-1}$。

这是考虑转化成二进制：

$$2^{N-K}=(1\underbrace{00\dots00}_{N-K\text{个}0})_2$$

$$2^{M-K}-1=(\underbrace{11\dots11}_{M-K\text{个}1})_2$$

在考虑带余数除法的性质，其实就是一直让被除数减去除数或除数倍数，直到被除数小于被除数。这时我们把 $2^{N-K}$ 的第二高位于 $2^{M-K}-1$ 的最高位对其进行减法，一次操作后的结果是（$x$ 表示对齐了 $2^{M-K}-1$ 所需要右移的位数）：

$$2^{N-K}-(2^{M-K}-1) \times 2^x=(1\underbrace{00\dots00}_{N-M\text{个}0})_2$$

这样每次就会扔掉 $M-K$ 个 $0$，所以最后的结果就是 $2^{(N-K)\mod(M-K)}$。注意因为之前约掉了 $2^K$，所以还需要乘上 $2^K$。

---

然后就要计算 $2^X$ 的个位数，很明显是一个循环：$2,4,8,6$，直接 $O(1)$ 求就行了。

# 代码时间

```cpp
#include <iostream>
#define int long long

using namespace std;

int mods2[4] = {6, 2, 4, 8};

signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        if (m == k + 1) {
            if (n >= k) puts("0");
            else cout << mods2[n % 4] << endl;
        } else if (n < m) {
            cout << mods2[n % 4] << endl;
        } else {
            cout << (((mods2[((n - k) % (m - k)) % 4]) * mods2[k % 4]) % 10) << endl;
        }
    }
    return 0;
}
```

---

## 作者：hejianxing (赞：2)

[link](https://www.luogu.com.cn/problem/AT_arc176_b)

# 题意

求 $2^N\bmod (2^M-2^K)$ 十进制下的最后一位。

$T\le 2\times 10^5,N,M,K\le 10^{18}$。

# 题解

~~不妨把字母都变成小写。~~

当 $n<m$ 时显然有 $2^n\le 2^{m-1}=2^m-2^{m-1}\le 2^m-2^k$，那么直接快速幂求 $2^n\bmod {10}$ 即可。

当 $n\ge m$ 时，构造 $2^n\equiv 2^n-2^{n-m}(2^m-2^k)=2^{n-(m-k)}\pmod {(2^m-2^k)}$。通过不断 $n\gets n-(m-k)$ 就可以使 $n<m$，像上面一样求解即可。

注意到一种特殊情况：$m=k+1$ 时，$2^m-2^k=2^k$ 是 $2$ 的正整数幂，求 $2^n\bmod 2^k$ 要特殊处理。至于为什么，手摸发现。

时间复杂度 $O(T\log n)$。

# 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T;
LL n, m, k;
LL qpow(LL x, LL y, LL p) {
    LL sum = 1;
    while (y) {
        if (y & 1) sum = sum * x % p;
        x = x * x % p, y >>= 1;
    }
    return sum;
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld%lld", &n, &m, &k);
        if (m - k == 1) {
            if (n >= k) printf("0\n");
            else printf("%lld\n", qpow(2, n, 10));
            continue;
        }
        if (n >= m) n -= (n - m) / (m - k) * (m - k);
        if (n >= m) n -= (m - k);
        printf("%lld\n", qpow(2, n, 10));
    }
    return 0;
}
```

---

## 作者：Day_Tao (赞：1)

### 题目大意

求 $[2^N \bmod (2^M-2^K)] \bmod 10$。

多测，数据范围 $1\le T\le 2\times 10^5$，
$1\le N\le10^{18}$，$1\le K < M\le10^{18}$，$N,M,K \in \mathbb{N}$。

### Sol

首先考虑特殊情况：

- $M=K+1$ 且 $N\ge K$。这时的 $2^M-2^K=2^K$，假如说 $N\ge K$，那么就代表可以整除，直接输出 $0$。

- $M=K+1$ 但是 $N<K$。这时的答案就是 $2^N$ 的最后一位。容易发现对于正的次幂，对 $4$ 取模后的值为 $0,1,2,3$ 时整个数的末尾数字分别为 $6,2,4,8$。由于次幂取不到 $0$，所以也不用考虑 $2^0$ 的情况。答案也就很显然了。

- $M\ne K+1$且 $N<M$，由于保证 $K<M$，所以 $2^M-2^K\ge 2^{M-1}$，仅在 $M=K+1$ 时等号成立，但是又因为满足 $M\ne K+1$ ，所以无法取到等号。这种情况就说明 $\frac{2^N}{2^M-2^K}\le1$，答案也就是 $2^N$ 的最后一位。

然后我们考虑一般情况：对于式子 $\frac{2^N}{2^M-2^K}$ 可以上下同除以 $2^K$，得到 $\frac{2^{N-K}}{2^{M-K}-1}$，这时考虑转换为二进制形式：
$$2^{N-K}=1\underbrace{00\dots00}_ {\text{N - K 个 0}}$$ 
$$2^{M-K}-1=\underbrace{11\dots11}_ {\text{M - K 个 1}}$$

再考虑带余数除法的性质，其实就是一次次减去除数及其倍数，直到减了除数变成负数为止。这时我们把 $2^{N-K}$ 的第二高位于 $2^{M-K}-1$ 的最高位对齐进行减法，一次操作后的结果就是：（$x$ 表示对齐了 $2^{M-K}-1$ 所需右移的位数）

$$2^{N-K}-(2^{M-K}-1)\times 2^x=1\underbrace{00\dots00}_ {\text{N - M 个 0}}$$

一直这样运算，发现最后的结果就是 $2^{(N-K) \bmod (M-K)}$。这个数的末尾的情况在特殊情况中已经详细说明，这里也就不废话啦。但是注意到之前约掉了 $2^K$，所以说余数还要再乘上 $2^K$，其实也就是乘上 $2^K$ 的尾数，最后再让整个数对 $10$ 取模，就是最终答案啦。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod[4] = {6, 2, 4, 8};
int n, k, m, T;
signed main()
{
	scanf("%lld", &T);
	while (T--)
	{
		scanf("%lld%lld%lld", &n, &m, &k);
		if (m == k + 1)
		{
			if (n >= k)
				puts("0");
			else
				printf("%lld\n", mod[n % 4]);
			continue;
		}
		else if (n < m)
		{
			printf("%lld\n", mod[n % 4]);
			continue;
		}
		int x = m - k;
		n -= k;
		n %= x;
		n %= 4;
		n = mod[n];
		k %= 4;
		k = mod[k];
		n *= k, n %= 10; // 其实这边可以压个行，但是为了看着方便就这样啦
		printf("%lld\n", n);
	}
	return 0;
}
```

---
### END

---

## 作者：XYQ_102 (赞：0)

## 思路
显然的结论：
$$2^N\bmod(2^M-2^K)=2^{N-M+K}\bmod(2^M-2^K)$$

所以循环直到 $N<M$ 即可。这一步骤可以通过除法在 $\Theta(1)$ 的时间复杂度下解决。

接下来答案就是 $2^N\bmod10$，根据 $N\bmod4$ 的结果有 $4$ 种答案 $2,4,8,6$，同样是 $\Theta(1)$。

但是需要注意的是得特判一种情况：$(N=M-1) \wedge (M-K=1)$。这意味着原式等于 $2^N\bmod2^{M-1}$。因为 $N=M-1$，所以这种情况需要输出$0$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m,k;
int mo[4]={6,2,4,8};
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		if(n>=m) n-=((n-m)/(m-k)+1)*(m-k);
		if(m-k==1&&n==m-1) cout<<"0\n";
		else cout<<mo[n%4]<<"\n";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的绿题。

## 思路：

这是一道非常经典的数学问题。

题目中没明确规定 $m，n$ 的大小关系，所以我们需要继续要分类讨论。

当 $n \ge m$：

$2^n=2^n-2^{n-m}(2^m-2^k)=2^n-2^n+2^{n-(m-k)}=2^{n-(m-k)}$

最后一直循环直到 $n<m$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t;
long long a[4]={6,2,4,8};

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> t;
	while(t--){
		long long n,m,k;
		cin >> n >> m >> k;
		if(n>=m)
		{
			n=n-(n-m)/(m-k)*(m-k);
		}
		if(n>=m)
		{
			n=n-m+k;
		}
		if(n==m-1 && n==k)
		{
			cout << 0 << endl;
			continue;
		}
		cout << a[n%4] << endl;
	}
	return 0;
}
``````

---

## 作者：Zhl2010 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc176_b)

## 题目描述
很简单，一句话。

找出 $2^N$ 被 $2^M - 2^K$ 整除时的余数的最后一位。
## 数据分析

$1 \le T \le 2 \times 10^5$
 
$1 \le N \le 10^{18}$
 
$1 \le K < M \le 10^{18}$
 
$N$ ，$M$ ，$K$ 是整数。

------
看看庞大的数据，肯定并不能暴力，所以我们要用**数学的做法**。

数学的做法有一个特点：思路难想，代码却很简单，让我们一起来看一下思路。
## 思路
题目中没明确规定 $m$，$n$ 的大小关系，所以我们要分类讨论。

	如果n>=m：

$~ ~ ~ ~ ~ ~ ~ ~2^n=2^n-2^{n−m}(2^m−2^k)=2^n−2^n+2^{n−(m−k)}$
 $≡2^{n−(m−k)}\pmod{2^m−2^k}$
 
 关于余数的知识，这有点难理解。
 
 循环直到 $n<m$ 即可。
 
 ----
 	如果n<m：
$~ ~ ~ ~ ~ ~ ~ ~$ 意味着：$2^n$ 就是余数。但是有一种特殊情况：$n=m-1=k$ ，这种情况中 $2^m-2^k=2^n$，即 `n==m-1 && m-k==1` 时，答案为0。

----

**一个细节**：题目只要求求最后一位，所以我们找到$2$的幂的最后一位的规律：$2^1$ 是 $2$，$2^2$ 是 $4$，$2^3$ 是 $8$，$2^4$ 是 $6~\cdots$。$4$ 个数为一循环（暴力求解容易  `TLE` ）。

----
**注意：十年OI...，不开long long...**，开long long是个好习惯。

## 代码

 ```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int T;
	cin>>T;
	int a[4]={6,2,4,8};//记录最后一位
	while(T--){
		int n,m,k;
		cin>>n>>m>>k;
		if(n>=m){
			n=n-(n-m)/(m-k)*(m-k);//如果n>=m的情况
		}
		if(n>=m){
			n=n-m+k;//如果n>=m的情况
		}
		if(n==m-1&&n==k){//特判的情况
			cout<<0<<endl;
			continue;
		}
		cout<<a[n%4]<<endl;
	}
	return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
当 $M=K+1$ 时，如果 $N\geq k-1$，答案为 $0$，否则为 $2^N$ 的最后一位。

当 $M>N$ 时，$2^N$ 的最后一位。

接下来考虑其他情况。

观察原式不难发现：$2^N \bmod 2^M-2^K$ 中 $2^M-2^K$ 可以写成 $2^K(2^{M-K}-1)$，$2^N$ 可写成 $2^K2^{N-K}$。

根据同余的性质，$2^N \bmod (2^M-2^K)$ 等价于 $2^K(2^{N-K}\bmod (2^{M-K}-1))$。

对于 $2^{N-K}$，我们可以将它写成 $2^{(M-K)^{t}}2^{((N-K)\bmod (M-K))}$ 其中 $t\geq 0$。

有根据同余的乘方性，和 $2^{M-K}\equiv 1\bmod (2^{M-K}-1)$ 得知：

$2^{(M-K)^{t}}2^{((N-K) \bmod (M-K))}=2^{((N-K) \bmod (M-K))}$ 在 $\bmod(2^{M-K}-1)$ 意义下。

答案即为 $2^K$ 的第一位乘以 $2^{((N-K)\bmod (M-K))}$ 的第一位的第一位，可以根据规律 $O(1)$ 求出。

时间复杂度 $O(T)$。

淼。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[4]={2,4,8,6};
int main() 
{
    long long t;
    cin >> t;
    while (t--)
    {
        long long n, m, k, d1, d2, ans;
        cin >> n >> m >> k;
        if(m-k==1)
        {
            if(n>=k-1) cout<<0<<endl;
            else cout<<a[(n-1)%4]<<endl;
        }
        else if(m>n) cout<<a[(n-1)%4]<<endl;
        else 
        {
            d1=n-k,d2=m-k;
            if(d1%d2==0)ans=1;
            else ans=a[(d1%d2-1)%4];
            cout<<(ans*a[(k-1)%4])%10<<endl;
        }
    }
}
```

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_arc176_b)/[AtCoder](https://atcoder.jp/contests/arc176/tasks/arc176_b)

## 题目大意

给出三个数字 $N,M,K$，求 $\left[2^N\mod\left(2^M-2^K\right)\right]\mod 10$。

## 解题思路

$2^n\mod10,n\in\N^+$ 存在循环节：
$$2^n\mod10=\begin{cases}
2&,n\equiv1\pmod4\\
4&,n\equiv2\pmod4\\
8&,n\equiv3\pmod4\\
16&,n\equiv0\pmod4
\end{cases}$$

由 $K\leq M$ 可知，$2^M-2^K=2^K\left(2^{M-K}-1\right)\geq2^K$，当且仅当 $M=K+1$ 时不等式处取等号。

我们分两大类讨论：
- 若 $M=K+1$，则 $2^M-2^K=2^K$，分两小类讨论：
- - 若 $N\geq K$，则 $2^K | 2^M$，可得 $2^N\mod\left(2^M-2^K\right)=2^N\mod2^K=0$，输出 $0$；
- - 若 $N<K$，则 $2^N<2^K$，可得 $2^N\mod\left(2^M-2^K\right)=2^N\mod2^K=2^N$，输出 $2^N\mod10$。
- 若 $M>K+1$，则 $2^M-2^K=2^K\left(2^{M-K}-1\right)>2^K$，分两小类讨论：
- - 若 $N\leq K$，则 $2^N<2^M-2^K$，可得 $2^N\mod\left(2^M-2^K\right)=2^N$，输出 $2^N\mod10$；
- - 若 $N>K$，则 $2^K | 2^N$，则 $2^N\mod\left(2^M-2^K\right)=2^K\left[2^{N-K}\mod\left(2^{M-K}-1\right)\right]$，若 $N<M$，则 $2^{N-K}\mod\left(2^{M-K}-1\right)=2^{N-K}$，输出 $2^{N-K}\times2^K\mod10$；若 $N\geq M$，则$2^{N-K}=\left(2^{M-K}-1\right)2^{(N-K)-(M-K)}+2^{(N-K)-(M-K)}$，即 $2^{N-K}\equiv2^{(N-K)-(M-K)}\pmod{2^{M-K}-1}$，即 $2^{N-K}\equiv2^{(N-K)\mod(M-K)}\pmod{2^{M-K}-1}$，输出 $2^{(N-K)\mod(M-K)}\times2^K\mod10$，发现此形式也适用于 $N<M$ 的情况，所以 $N>K$ 时输出 $2^{(N-K)\mod(M-K)}\times2^K\mod10$。

## AC 代码
### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
long long Read(){
	char c=getchar();while(c<'0'||c>'9')c=getchar();
	long long r=0;while(c>='0'&&c<='9'){r=r*10+(c^48);c=getchar();}
	return r;
}
const int hi[4]={2,4,8,6};
int ti(long long i){
	return i?hi[(i-1)&3]:1;
}
int main(){
	int T=Read();
	while(T--){
		long long N=Read(),M=Read(),K=Read();
		if(M==K+1){
			if(N>=K)puts("0");
			else printf("%d\n",ti(N));
		}
		else printf("%d\n",N>K?ti((N-K)%(M-K))*ti(K)%10:ti(N));
	}
	return 0;
}
```
### Python
```python
T=int(input())

def ti(i):
    if i==0:
        return 1
    elif i%4==1:
        return 2
    elif i%4==2:
        return 4
    elif i%4==3:
        return 8
    else:
        return 6

for t in range(T):
    [N,M,K]=input().split()
    if int(M)==int(K)+1:
        if int(N)>=int(K):
            print('0')
        else:
            print(ti(int(N)))
    elif int(N)<=int(K):
        print(ti(int(N)))
    else:
        print(ti(int(K))*ti((int(N)-int(K))%(int(M)-int(K)))%10)
```

---

## 作者：coderJerry (赞：0)

### 题目描述
求 $2^N$ 除以 $2^M-2^K$ 的余数末位是多少。
### 题目分析
很好的分类讨论！

- $N<M$ 时，商一定为 $0$，故答案为 $2^N\operatorname{mod} 10$。

- $N>M$ 时，我们换个角度导一下：$2^N\equiv 2^N-2^{N-M}(2^M-2^K)$ $(\operatorname{mod} 2^M-2^K)$。这说明，每次用 $N-(M-K)$ 替换原来的 $N$，直到当前的 $N<M$，输出答案 $2^N\operatorname{mod} 10$ 即可。为了提高效率，我们直接 $O(1)$ 预处理（见下）：
```cpp
int tmp=(n-m)/(m-k)+1;//+1是因为必须保证 N<M
n=n-(m-k)*(tmp);
cout<<qpow(2,n,10)<<endl;
```
- 但是你再考虑上述代码，当 $m=k+1$ 时，除数就变成 $1$ 了，所以还要特判该情况。$n<k$ 时仍然是 $2^N\operatorname{mod} 10$，但 $N≥K$ 时，上下整除，直接输出 $0$ 即可。

解答到这里我们可以得到 $O(T\log N)$ 的算法，实际比赛中通过已经绰绰有余。

- 但是我们不能止步于此。注意到 $2$ 的次幂的末位是有规律的，所以你手玩一下便可得到：

| $N\operatorname{mod}4$ 的值  | $0$ | $1$ | $2$ | $3$| 
| :----------: | :----------: | :----------: | :----------: | :-:|
| **$2^N$ 的末位** | $6$ | $2$ | $4$ | $8$ |

于是我们便可以 $O(1)$ 处理每一次询问，总复杂度 $O(T)$。
### AC 代码
 | [$O(T\log N)$ 做法（149ms）](https://atcoder.jp/contests/arc176/submissions/52934245) | [$O(T)$ 做法（122ms）](https://atcoder.jp/contests/arc176/submissions/52934559) |
| :----------: | :----------: |

---

