# K-good

## 题目描述

We say that a positive integer $ n $ is $ k $ -good for some positive integer $ k $ if $ n $ can be expressed as a sum of $ k $ positive integers which give $ k $ distinct remainders when divided by $ k $ .

Given a positive integer $ n $ , find some $ k \geq 2 $ so that $ n $ is $ k $ -good or tell that such a $ k $ does not exist.

## 说明/提示

$ 6 $ is a $ 3 $ -good number since it can be expressed as a sum of $ 3 $ numbers which give different remainders when divided by $ 3 $ : $ 6 = 1 + 2 + 3 $ .

 $ 15 $ is also a $ 3 $ -good number since $ 15 = 1 + 5 + 9 $ and $ 1, 5, 9 $ give different remainders when divided by $ 3 $ .

 $ 20 $ is a $ 5 $ -good number since $ 20 = 2 + 3 + 4 + 5 + 6 $ and $ 2,3,4,5,6 $ give different remainders when divided by $ 5 $ .

## 样例 #1

### 输入

```
5
2
4
6
15
20```

### 输出

```
-1
-1
3
3
5```

# 题解

## 作者：sunset_breeze (赞：12)

[题目传送门](https://www.luogu.com.cn/problem/CF1656D)

## 做法

奇偶性判定好题。

### $Case1:$ $n$ 为奇数

很显然，$n$ 为奇数时一定可以拆分成**两个数** $x$ 和 $y$，且 $x$ 为奇数，$y$ 为偶数，发现 $x \mod 2=1,y\mod 2=0$，$k$ 也刚好位 $2$，所以当 $n$ 为奇数时就直接输出 $2$。

### $Case2:$ $n$ 为偶数

设 $k$ 个数为 $a_1,a_2,...,a_k$，所以有 $a_1+a_2+..+a_k=n$，由于题目说 $a_1\mod k,a_2 \mod k,...,a_k\mod k$ 互不相同，所以这些数 $\mod k$ 一定为 $0,1,2,...,k-1$ 且不重不漏。

那么考虑拆分 $a_i$，设 $a_i=b_i\times k+c_i(c_i=a_i \mod k)$，那么 $a_1+a_2+...+a_k=n$ 就可以转化为 $(b_1\times k+b_2 \times k+...+b_k\times k)+(c_1+c_2+...+c_k)$。

因为 $c_1+c_2+...+c_k$ 一定等于 $0+1+...+k-1$，等差数列求和得 $\frac{(0+k-1)\times k}{2}=\frac{(k-1)\times k}{2}$，再把 $b_1\times k+b_2\times k+...+b_k\times k$ 提取公因式得 $k\times(b_1+b_2+...+b_k)$，再设 $b_1+b_2+...+b_k=x$，所以 $b_1\times k+b_2\times k+...+b_k\times k=k\times x$。

所以 $n=\frac{(k-1)\times k}{2}+k\times x$，将上式化简得 $2\times n=k\times(k+2\times x-1)$，然后我们发现一个结论：$k$ 和 $k+2\times x-1$ 中一定有一个为偶数，一个为奇数，因为 $2\times x-1$ 一定为奇数，所以如果 $k$ 为偶数，那么 $k+2\times x-1$ 就一定为奇数，上述结论肯定成立，如果 $k$ 为奇数，那么 $k+2\times x-1$ 一定为偶数，
故得证。

所以我们把 $2\times n$ 拆成 $2^{p}+q$，使得 $2^{p}|2\times n-q$，而 $2^{p+1}\nmid 2\times n-q$ 且 $q< 2^{p}$，那么这样做显然 $q$ 为奇数，这样拆是把这个数拆成偶数乘奇数的形式。

设 $a=2^{p},b=q$，**那么可以证明 $k$ 一定可以等于 $\min (a,b)$**，如果这样拆后 $\min (a,b) \le 1$ 就说明**无解（因为题目中说的是 $2\le k$，与题目矛盾）**，输出 $-1$，否则就输出 $a$ 和 $b$ 中较小的一个（为什么要输出较小的一个？是因为 $k\le2\times x-1+k$，两个数 $a$ 和 $b$ 就相当于 $k$ 和 $2\times x-1+k$，所以较小的一个就为 $k$）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long n;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld",&n);
		if(n%2==1)//n为奇数时直接特判
		{
			printf("2\n");
			continue;
		}
		else//n为偶数
		{
			long long a=1,b=0,x=2*n;
			while(x%2==0)
			{
				x/=2;a*=2;//将2*n这个数拆分成奇数乘偶数的形式
			}
			b=(2*n)/a;
			if(min(a,b)<2)printf("-1\n");//a、b的最小值小于2，无解
			else if(a<b)printf("%lld\n",a);//输出较小的一个数
			else if(a>b)printf("%lld\n",b);
		}
	}
	return 0;
}
```


---

## 作者：hyman00 (赞：11)

## 001 思路

题意不用再说了吧。

容易知道，当 $n$ 是 $k-good$ 当且仅当 $n=kp+\frac{k(k+1)}{2}$ ，$p$ 是非负整数。

### 思路1

枚举 $k$ ，$O(t\sqrt n)$，喜提TLE！

### 思路2

考虑变形：
$$
2n=k(2p+k+1)
$$

这时，$k$ 和 $k+1$ 一奇一偶，即 $2n$ 里面所有质因子 $2$ 都在同一边。

我们把 $2n$ 分解成 $a\times b$，$a$ 是 $2$的次幂，$b$ 是奇数。

然后分情况讨论：

$a<b$ : $k=a$

$a>b$&&$b\ne0$ : $k=b$

$b=0$ : $k=-1$

可以做到 $O(t\log n)$

## 002 代码
```c++
#include <bits/stdc++.h>
using namespace std;
signed main()
{
	int tc=1;
	cin>>tc;
	while(tc--){
		long long n,m=2;
		cin>>n;
		while(!(n&1))n>>=1,m<<=1;
		if(n>m)cout<<m<<"\n";
		else if(n>1)cout<<n<<"\n";
		else cout<<"-1\n";
	}
	return 0;
}
```

完结撒花！

---

## 作者：Zelotz (赞：7)

## 分析
因为 $n$ 可以表示成 $k$ 个除以 $k$ 的余数互不相同的数之和，且除以 $k$ 的余数只有 $0\sim k-1$ 一共 $n$ 个，所以这 $k$ 个数必然是连续的 $k$ 个数。

连续 $k$ 个数的和可以表示为 
$$(1+p)+(2+p)+(3+p)+...+(k+p)=\frac{k\times (k+1)}{2}+k\times p$$
$p$ 为非负整数。

所以
$$
\begin{aligned}
n=\frac{k\times (k+1)}{2}+k\times p\\
2\times n=(2p+k+1)\times k
\end{aligned}
$$
其中 $k$ 和 $k+1$ 一奇一偶，$2\times p$ 为偶数，$2\times n$ 为偶数，$2\times p+k+1 > p$ 。

设 $2\times n=a \times b$ ，其中 $a$ 是 $2$ 的次幂，则 $a$ 是偶数，$b$ 是奇数。

这样有了两种可能情况：
- $k$ 是奇数：$k=b$
- $k$ 是偶数：$k=a$

但是 $2\times p+k+1 > p$，所以

- $a>b$：$k=b$
- $a<b$：$k=a$
- $a=b$：由于 $a$ 为奇数，$b$ 为偶数，矛盾

题目中限制 $k \geq 2$，所以如果 $k=1$ 则无解。

所以这道题就解决了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define srand srand(time(NULL))
#define random(x) rand() % (x)
#define il inline
#define ptc putchar
#define reg register
#define mp make_pair
typedef __int128 LL;
typedef long long ll;
typedef pair<int, int> PII;
namespace zzz {
	template <typename T>
	il void read(T &x) {
		x = 0; T f = 1; char ch;
		while (!isdigit(ch = getchar())) f -= (ch == '-') << 1;
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar(); x *= f;
	}
	template <typename T, typename ...L>
	il void read(T &x, L &...y) {read(x); read(y...);}
	template <typename T>
	il void write(T x) {
		if (x < 0) ptc('-'), x = -x;
		if (x > 9) write(x / 10);
		ptc(x % 10 + '0');
	}
}
using namespace zzz; 
const int N = 2e5 + 5;
#define int long long
int t, n, a[(int)1e5 + 5];
signed main() {
	read(t);
	while (t--) {
		read(n);
		n <<= 1;
		int a = 1, b, k;
		while (!(n & 1)) n >>= 1, a <<= 1;
		b = n;
		if (a > b) k = b; 
		else k = a; 
		if (k == 1) k = -1;
		write(k), ptc('\n');
	}
	return 0;
}

---

## 作者：Erica_N_Contina (赞：2)

## 思路

题意很简单啊，一道数论的题目。

我们考虑 $k$ 个除以 $k$ 的余数互不相同的正整数的性质。我们把这些数记为 $a_1\sim a_k$，那么很显然 $n=\sum a=pk+\frac{(k-1)k}{2},p\in \N$。那么如果 $k$ 是奇数则 $\sum a$ 是 $k$ 的倍数。

特别说明一下，因为 $a_i$ 是正整数，所以 $p≥1$。

我们把式子进行一下变形。

$2n=2pk+(k-1)k=k(2p+k-1)$

我们知道 $k,2p+k-1$ 中一个是奇数一个是偶数。所以我们把 $2n$ 的所有 $2$ 因子提取出来。

我们把 $2n$ 拆分成 $2n=a+b,a=2^i,i\in \N,b\in \N$。其中 $b$ 一定为奇数。

然后我们就考虑一下 $a,b$ 之间的关系。

- $a<b$，则 $k=a$，因为我们知道 $p≥1$，所以 $k<2p+k-1$。

- $a>b$ 且 $b≠1$，则 $k=b$。

- $a>b$ 且 $b=1$，则无解，输出 $-1$。因为此时 $k=1$ 但不满足题目要求。

注意本题答案可能不唯一。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double
#define rtn return
using namespace std;

const int N=2e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e5;

int n,m,p,T,a[N],ans;

void solve(){
	cin>>n;
	n<<=1;
	int a=1;
	while(n%2==0){
		a*=2;
		n/=2;
	}
	int b=n;
	if(a<b)cout<<a<<endl;
	else if(b!=1)cout<<b<<endl;
	else cout<<-1<<endl;
}
signed main(){
	cin>>T;
	while(T--)solve();
	return 0;
}
```




---

## 作者：__LiChangChao__ (赞：1)

### 思路

因为 $k$ 个数对 $k$ 取模有 $k$ 种不同的结果，所以其余数只有下面这种情况：

$$0,1,\dots,k-1$$

所以拆一下这个 $n$，当 $n$ 为 $k$ 好时，有：

$$
n=(0+a_{1}k)+(1+a_{2}k)+\dots+(k-1+a_{k}k)
$$

$a_{i}\ge 0$ 且为整数，化简得：

$$
n=\sum_{i=0}^{k+1}i+\sum_{i=1}^{k}a_{i}k = \frac{(k+1)k}{2}+\sum_{i=1}^{k}a_{i}k
$$

里面有一个 $\frac{}{2}$ 所以为了好处理，推式子先 $\times 2$。

$$2n=(k+1)k+2\sum_{i=1}^{k}a_{i}k=k(k+1+2\sum_{i=1}^{k}a_{i})$$

此时发现 $k$ 与 $k+1$ 一奇一偶，$2\sum_{i=1}^{k}a_{i}$ 一定是偶数，所以考虑拆分 $n$ 成一个奇数一个偶数。

但是发现 $k(k+1)\le n$，所以 $k$ 应当尽量小来满足这个性质，所以直接将 $n$ 中的所有 $2$ 的因子提出来，得到 $n=ans_{1}ans_{2}=2^{m}ans_{2}(ans_{2}\mod 2=1)$，答案为 $\min(ans_{1},ans_{2})$，注意要满足 $ans_{2}>1$，否则就输出 `-1`。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
long long n,ans;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%lld",&n);ans=2;
		while(n%2==0)n>>=1,ans<<=1;//还可以直接 ans = lowbit n * 2
			 if(n>1	  )	printf("%lld\n",min(n,ans));
		else 			printf("%lld\n",-1ll	  );
	}
}
```

---

## 作者：Meteor_ (赞：1)

# CF1656D K-good 题解

## 题目大意

给出 $t$ 个整数 $n$，对于每一个 $n$ 找出一个大于等于 $2$ 的整数 $k$，使得 $n$ 可以表示成 $k$ 个对 $k$ 取模的结果互不相同的正整数之和。

$1 \le t \le 10^5, 2 \le n \le 10^{18}$。

## 题解

**单次复杂度 $O(1)$，它来啦！**

我们先将题意再次化简，可以得到，我们实际上就是要找一个 $k$，使得 $n = p \cdot k + \frac{k(k + 1)}{2}$（$p$ 为非负整数）。

我们通过观察可以发现，$n$ 为奇数还是偶数，与它的性质和最终答案有直接联系，所以我们分情况讨论。

### $n$ 为奇数

当 $n$ 为奇数时，我们不难发现，只要令 $k = 2$ 就可以满足条件。因为任意一个奇数都能写成 $2p + 1$ 即 $2 \cdot p + \frac{1 \times 2}{2}$ 的形式。所以对于 $n$ 为奇数的情况，直接输出 $2$ 即可。

---

### $n$ 为偶数

当 $n$ 为偶数时，我们可以将 $n$ 换一种写法，写作 $x \cdot 2^y$（$x$ 为奇数，$y$ 为正整数）。

可是我们为什么要这么写呢？这么写有什么用呢？

其实，在瞪眼观察法后，我们可以非常容易地明白：这个题奇数与偶数的解决方法不太一样，所以这就是我们的切入点。而 $x \cdot 2^y$ 就很好地将一个数的奇数与偶数部分分开了。那么我们利用这个式子继续往下走：

$$\begin{aligned}

n &= p \cdot k + \frac{k(k + 1)}{2}\\

x \cdot 2^y &= p \cdot k + \frac{k(k + 1)}{2}\\

x \cdot 2^{y + 1} &= 2p \cdot k + k(k + 1)\\

x \cdot 2^{y + 1} &= k(2p + k + 1)\\

\end{aligned}$$

到了这里，我们就可以继续利用奇偶数分情况讨论的方法，进一步进行化简：

#### 当 $k = x$ 时：

$$\begin{aligned}

x \cdot 2^{y + 1} &= x(2p + x + 1)\\

2^{y + 1} &= 2p + x + 1\\

\end{aligned}$$

因为 $x$ 为奇数，所以 $x + 1$ 为偶数，又因为 $2p$ 为偶数，所以只要保证 $x + 1 \le 2^{y + 1}$，就一定有 $2p + x + 1 = 2^{y + 1}$。此时我们的 $k = x$，也就是说只要 $x \le 2^{y + 1}$，答案就是 $x$。

---

#### 当 $k = 2^{y + 1}$ 时：

$$\begin{aligned}

x \cdot 2^{y + 1} &= 2^{y + 1}(2p + 2^{y + 1} + 1)\\

x &= 2p + 2^{y + 1} + 1\\

\end{aligned}$$

因为 $2^{y + 1}$ 为偶数，所以 $2^{y + 1} + 1$ 为奇数，又因为 $2p$ 为偶数，所以只要保证 $2^{y + 1} \le x$，就一定有 $2p + 2^{y + 1} + 1 = x$。此时我们的 $k = 2^{y + 1}$，也就是说只要 $2^{y + 1} \le x$，答案就是 $2^{y + 1}$。

---

#### 综上所述：

答案就是 $x$ 与 $2^{y + 1}$ 中的较小值。所以我们对于每一个 $n$，可以在 $O(1)$ 的时间复杂度里计算出它的答案。怎么求呢？

$$\begin{aligned}

2^y &= \operatorname{lowbit}(x) = x \& (-x) \\

2^{y + 1} &= 2 \cdot \operatorname{lowbit}(x) \\

x &= \frac{n}{2^y} = \frac{n}{\operatorname{lowbit}(x)} \\

\end{aligned}$$

所以答案就是 $\min(2 \cdot \operatorname{lowbit}(x), \frac{n}{\operatorname{lowbit}(x)})$。

可是如果你就这样交上去，会喜提一个 WA。

为什么呢？

注意题里所说的 $2 \le k$，所以你还需要特判一下 $\min = 1$ 的情况，并输出 $-1$，这样就能愉快地 AC 啦。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int T, n;

signed main() {
    ios::sync_with_stdio(0);
    cin >> T;
    for(int i = 1; i <= T; ++ i) {
        cin >> n;
        if((n & 1) == 1)
            cout << 2 << '\n';
        else {
            int lowbit = n & (-n), minn = min(lowbit * 2, n / lowbit);
            if(minn != 1) cout << minn << "\n";
            else cout << "-1\n";
        }
    }
}
```

---

## 作者：I_am_Accepted (赞：1)

### Preface

稍微长但是思路很顺的解法。（有证明）

### Analysis

容易发现，$n$ 是「$k$ 好的」的充要条件为

$$n=\frac{k(k+1)}{2}+kt\quad(t\in\mathbb{N})$$

发现这个分母 $2$ 比较难搞，我们将 $k$ 按奇偶分类。

------------

#### 偶数（$k=2q$）

$$n=q(2q+1)+2qt=q(2q+2t+1)$$

设 $o=2q+2t+1$，则要满足 $o\ge 2q+1=\frac{2n}{o}+1$。

所以只要找到的 $n$ 的奇因数（$\ne1$）$o$ 使得上文不等式成立，即有答案 $k=\frac{2n}{o}$。

#### 奇数（$k=2q+1$）

$$n=(2q+1)(q+1)+(2q+1)t=(2q+1)(q+t+1)$$

设 $o=2q+1$，则要满足 $o\le 2(q+t+1)-1=\frac{2n}{o}-1$。

所以只要找到的 $n$ 的奇因数（$\ne1$）$o$ 使得上文不等式成立，即有答案 $k=o$。

------------

我们发现 $\frac{2n}{o}$ 为偶数，不可能等于 $o$，所以只要 $n$ 有非 $1$ 奇因数，就一定能通过上面的分类找到答案。

否则（即 $n=2^l(l\in\mathbb{N^+})$ 时），不存在 $k$（答案为 $-1$）。**无解性的证明：**

不论是在奇数还是偶数的分类中，$o$ 必然是 $1$，此时得到 $q\le0$ 或 $q=0$，得到 $k\le 2q+1\le 1<2$，矛盾。$\blacksquare$

### Code

[Link](https://codeforces.com/contest/1656/submission/150891512)

---

## 作者：User_Authorized (赞：0)

## 题意
给定正整数 $n$，询问是否存在 $k \ge 2$，使得 $n$ 可以表示成 $k$ 个对 $k$ 取模后的结果互不相同的正整数之和。

（$1 \le T \le 10^5, 2 \le n \le 10^{18}$）。

## 题解
**本题存在常数复杂度处理单次查询的算法。**


通过分析可得，对于正整数 $n$，$k$ 满足要求的充要条件为 

$$\begin{aligned}
n &= kp + \dfrac{k \left(k + 1\right)}{2} &\left(p \in \mathbb{N}\right)
\end{aligned}$$

按 $k$ 的奇偶性进行分类讨论，设 $n = x \cdot 2^y$，其中 $x$ 为奇数。

---

### $k$ 为偶数
那么上式可化为 

$$\begin{aligned}
n &= \dfrac{k}{2}\left(2p + k + 1\right) &\left(p \in \mathbb{N}\right)
\end{aligned}$$

容易发现 $2p + k + 1$ 为奇数。可得上式成立当且仅当 $x = 2p + k + 1 \land \dfrac{k}{2} = y \Rightarrow k = 2^{y + 1}$。观察什么时候会无解，如果不存在 $p \in \mathbb{N}$ 使得 $2p + k + 1 = x$ 即 $k + 1 > x$，那么无解。

### $k$ 为奇数
那么上式可化为

$$\begin{aligned}
n &= {k}\left(p + \dfrac{k + 1}{2}\right) &\left(p \in \mathbb{N}\right)
\end{aligned}$$

通过分析可以得出该式有解的充要条件为存在 $p \in \mathbb{N}$ 使得 $p + \dfrac{k + 1}{2} = \dfrac{n}{k}$ 且 $k \geqslant 2$，其中 $\dfrac{k + 1}{2} \leqslant \dfrac{n}{k} \Leftrightarrow k\left(k + 1\right) \leqslant 2n$。

现在将两种情况合并到一起考虑，可以发现，如果 $x \geqslant 2^{y + 1}$，那么 $k$ 为偶数的情况一定有解。如果 $x < 2^{y + 1}$，那么

$$x < 2^{y + 1} \Leftrightarrow x + 1 \leqslant 2^{y + 1} \Leftrightarrow x \left(x + 1\right) \leqslant x \cdot 2^{y + 1} = 2n$$

所以该种情况无解当且仅当 $x = 1$。

综上所述

- 如果 $n = 2^y$，那么无解；
- 如果 $n = x \cdot 2^y \land x \geqslant 2^{y + 1}$，那么 $k = 2^{y + 1}$ 有解；
- 如果 $n = x \cdot 2^y \land x < 2^{y + 1}$，那么 $k = x$ 有解；

观察到 $2^y$ 为 $\operatorname{lowbit}(n)$，可以 $\mathcal{O}(1)$ 求解。

## Code
```cpp
//Codeforces - 1656D
#include <bits/stdc++.h>

typedef long long valueType;

valueType lowBit(valueType x) {
    return x & -x;
}

int main() {
    valueType T;

    std::cin >> T;

    for (valueType testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        valueType const bit = lowBit(N);

        valueType const x = N / bit, y = bit << 1;

        if (x == 1) {
            std::cout << -1 << '\n';
        } else {
            std::cout << std::min(x, y) << '\n';
        }
    }

    std::cout << std::flush;

    return 0;
}
```

---

## 作者：冰冻罗非鱼 (赞：0)

### 题意：
>给定一个整数 $n$，请找出一个大于等于 $2$ 的整数 $k$，使得 $n$ 可以表示成 $k$ 个除以 $k$ 的余数互不相同的数之和。

注意**$k$个除以 $k$ 的余数互不相同的数之和**这一句话。容易想到，这就相当于是对 $k$ 的一个完全剩余系求和使得和为 $n$。
因为除以 $k$ 所能得到的余数只能为 $0$ 到 $k - 1$，并且，任意一个数减去余数部分，剩下的部分都可以被表示为 $xk$，其中 $x$ 为整数。
因此，我们设这些余数互不相同的数的和为 $pk + \frac{k(k - 1)}{2}=n$。有了这个式子，我们不难想到枚举 $k$并将结果与 $n$ 进行比较，自然，~~收获TLE~~。
将柿子变形，又有：
$$k(2p + k - 1) = 2n$$
其中，$2p$ 为偶数，$k$ 和 $k-1$ 各为偶数或奇数，易证， $2n$ 为偶数，且 $k$ 和 $(2p+k-1)$ 各有一个为奇数或偶数，且后者在题目情况中恒大于前者。
因此将 $2n$ 进行分解，把它分解为一个 $2$ 的次幂 $a$ 和一个奇数 $b$，因此得到这个柿子：
$$k = \min(a,b)$$

### AC代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k,n,t;
signed main(){
	cin >> t;
	while(t--){
		cin >> n;
		k = 2;
		bool flag = 0;
		int j = 1;
		n *= 2;
		while(n % 2 == 0){
			j *= 2;
			n /= 2;
		}
		if(n == 1){
			cout << "-1\n";
		}
		else{
			cout << min(n,j) << "\n";
		}
	}
	
}
```

---

## 作者：max67 (赞：0)

## 前言

我好菜啊！那么菜的数学题都不会做。

## 正文

给定一个数 $n$，你要求一个数 $k$，满足存在一组 $k$ 个正整数，满足他们的和为 $n$，且模 $k$ 的值互不相同。

$$
2\le n\le 10^{18}
$$
$$
k\ge 2
$$
## 题解
因为在模 $k$ 意义下的剩余系是 $k$ 个，所以题目可以写成以下形式：
$$
\frac{k(k-1)}{2}+dk=n,d>0,
$$
其中 $d$ 也是整数。将两边 $\times 2$：
$$
k(k-1)+2dk=2n
$$
$$
(k-1)+2d=\frac{2n}{k}
$$
显然，必须满足 $k|2n$。

先随便带几个值，将 $k=2$ 带入，有：$1+2d=n$。
显然，$n$ 为奇数的时候取 $k=2$ 满足条件。

接下来，考虑 $n$ 为偶数的形式，我们把 $n$ 写成如下形式：$n=tm$，其中 $m$ 为奇数。

考虑化一下上面的式子，有:

$$
d=\frac{n}{k}-\frac{k-1}{2}
$$
（注意，这里只考虑了 $k$ 为奇数的情况。）

考虑数据范围，显然我们最多拥有 $log$ 的时间去求 $k$，那么考虑最大（最容易求出来）的 $k$ 为 $m$。此时，若 $t-\frac{\frac{n}{t}-1}{2}=t-\frac{n-t}{2t}>0$，则这个取值是合法的。

再来考虑 $k$ 为偶数的情况，这时候取特殊值显然不大行（毕竟已经取过了），那么考虑 $t$ 也是偶数，我们将 $t$ 带入 $k$。

$$
\frac{t(t-1)}{2}+dt=tm
$$

这时你会发现 $t$ 可以约掉，但 $\frac{t-1}{2}$ 显然不合法，考虑给他人为地乘上一个 $2$，即 $k$ 取 $2t$：

$$
\frac{2t(2t-1)}{2}+2dt=tm
$$
$$
2t-1+2d=m
$$
$$
2t+2d=m+1
$$
即当 $m+1-2t\ge2$ 时，$k=2t$ 的取值合法。

其次，如果你取任何 $q=2i,i\in N^+,q\le t$，那么显然 $q$ 包含的 $2$ 的因子个数小于等于 $t$，化一下式子，有 ：
$$
\frac{q}{p}\times \frac{q-1}{2}+2dq=\frac{t}{p}m
$$
其中 $\frac{q}{p}$ 是奇数，那么 $\frac{q-1}{2}$ 是分数，$\frac{t}{p}$ 是整数，肯定不合法。

即满足条件的最小的为偶数的 $k=2t$ 。


这时候，大胆猜想一下，只用考虑他们两个的范围即可（毕竟这是 $D$ 题）。更严谨的说明如下

* **1.** 考虑 $n=2^i$ 的情况，$n=tm,t=2^i,m=1$。则最大的奇数 $k$ 为 $1$，不合法;最小的偶数 $k$ 为 $2^{i+1}$，不合法。因此肯定不合法。

* **2.** 考虑两个限制条件：

$$
m+1-2t\ge2,t-\frac{n-t}{2t}>0
$$
化一下，有 $\frac{n}{t}-1\ge 2t,n\ge 2t^2+t$；$2t^2+t>n$。他们的并显然对每一个数都满足条件。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n;
signed main()
{
    int _;scanf("%lld",&_);
    while(_--)
    {
        scanf("%lld",&n);
        if(n&1){puts("2");continue;}
        int tmp=n,t=1;
        while(!(tmp&1))tmp/=2,t*=2;
        if(tmp==1){puts("-1");continue;}
        if((tmp+1-2*t)>=2){printf("%lld\n",2*t);continue;}
        if(n/tmp>(tmp-1)/2){printf("%lld\n",tmp);continue;}
    }
    return 0;
}
```

## 后记

我好菜啊！别人用 $10$ 分钟 $A$ 掉，我用 $2$ 个小时 $A$ 掉（WA 了五六发）。

---

## 作者：bulijoijiodibuliduo (赞：0)

这场比赛我没打，错失上分好机会

这题是真的水

直接根据题意列出式子：
$n=\frac{k(k-1+2t)}{2}$ 其中 $t$ 为正整数

稍微变一下形：
$2n=k(k+1+2s)$ 其中 $s$ 为自然数

于是就变成了将 $2n$ 分为两个奇偶不同的数的乘积，我们只要把 $2n$ 里所有的 $2$ 拿出来就行了，然后把两个值取一个最小值就是 $k$ 了，其中 $k\neq1$

于是就有了代码：
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	int n,a,b;
	cin>>n;
	n*=2;
	a=1,b=n;
	while(b%2==0)b/=2,a*=2;
	if(b==1)cout<<"-1\n";
	else cout<<min(a,b)<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)solve();
}
```

---

## 作者：LG_ljc2022 (赞：0)

## Solution

题目已经描述的很精确了，在此不再赘述。

不妨按照题意模拟，设 $n = a_1 + a_2 + a_3 + … + a_k$。

把 $a_x$ 对 $k$ 取模的不同余数提出来，得到：

$$

\begin{aligned}

  n &= a_1 - a_1 \% k + a_1 \% k + … + a_k - a_k \%k + a_k \% k  \\
  
   &= x \times k + \frac{k \times (k - 1)}{2} \\
   
   &= \frac{2x \times k + k \times (k - 1)}{2} \\
   
   &= \frac{k \times (k + 2x - 1)}{2} 
                 
\end{aligned}

$$

由此可得 $2n = k \times(2x + k - 1)$。

而由于 $2n$ 为偶数，所以 $k \times(2x + k - 1)$ 为偶数，又因为 $2x$ 为偶数，则 $\tt{k}$ 和 $\tt{k - 1}$ 一奇一偶。

此时只需要在输入时将 $\tt{n}$ 拆分，把所有的因子 2 提取出来，即可保证拆分的数一奇一偶。由于 $k < k \times(2x + k - 1)$ 输出时判断谁小且 $\ge 2$ 就行了。不满足的话输出 $-1$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
long long n;
//2n = k * (2x + k - 1)
//k, k - 1 + 2x:一奇一偶

int main()
{
	
	scanf("%d", &T);
	while (T--)
	{
		scanf("%lld", &n);
		long long tx = 1;
		n *= 2;
		while (n % 2 == 0)
		{
			n /= 2;
			tx *= 2;
		}
		//分离所有的2i因子，把2变为n和tx，一奇一偶的形式
		//k >= 2, x >= 0   ->   k < 2x + k - 1
		if (n < tx && n >= 2) printf("%lld\n", n); //k为奇数
		else if (n > tx) printf("%lld\n", tx); //k为偶数
		else printf("-1\n");
	}
	
	return 0;
}
``````

---

