# 「CMOI R1」Bismuth / Linear Sieve

## 题目背景

![](bilibili:BV1qF4m157gc)

> Can you imagine find wakeless,like a satellite,in the black sky?
>
> Somewhere,like a star.
>
> We dream about things way beyond this atmosphere.
>
> At we're now,on the air.
>
> ……
>
> But I eventually evaporates in a blackhole…
>
> Will I just stick up there?……

## 题目描述

给定以下程序中的 $n$（即输入），求以下伪代码的输出结果。

```
Input n
For i := 1 to n
	is_not_prime[i] := 0
cntp := 0
counter := 0
For i := 2 to n {
	If is_not_prime[i] = 0 {
		cntp := cntp + 1
		primes[cntp] := i
	}
	For j := 1 to cntp {
		If i * primes[j] > n
			break
		is_not_prime[i * primes[j]] := 1
		If i Mod primes[j] > 0 // should be `If i Mod primes[j] = 0` in Sieve of Euler
			break
		counter := counter + 1
	}
}
Print cntp, counter
```
请注意此代码**不是线性筛**，差别在注释过的那一行。

## 说明/提示

**本题采用捆绑测试**，并且存在子任务依赖（只有你拿到了一个子任务前一个子任务的分，你才有可能拿到该子任务的分）。

## 数据范围

| $\text{Subtask}$ | 约束条件 | 分值 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $n\leq 10^7$ |$10$|
| $2$ | $n\leq 10^9$ |$40$|
| $3$ | $n\leq 10^{18}$ |$50$|

对于 $100\%$ 的数据，满足 $1\leq n\leq 10^{18}$。

## 样例 #1

### 输入

```
100```

### 输出

```
50 30```

## 样例 #2

### 输入

```
9876543```

### 输出

```
4938272 3092277```

## 样例 #3

### 输入

```
998877665544332211```

### 输出

```
499438832772166106 312742219398875473```

# 题解

## 作者：Shadows_of_Twilight (赞：3)

## 提示

本片题解用的是题面代码里的变量。

## 思路

我们可以先特判 $n$ 等于 $1$ 的情况，再讨论其他情况。

首先我们看样例。



---



- 我们会发现输出的第一个数是 $\lceil \frac{n}{2}\rceil$。


首先，第一个加入 $primes$ 数组里的是 $2$，而在后面筛数时只有当前数能整除 $2$ 才能接着用其他的 $primes$ 数组里的数筛，也就是说只有**偶数**才能用**除了 $2$** 的数筛，而**偶数乘任何整数还是偶数**，且**每个数都会筛掉自己的两倍**。综上，除 $2$ 以外的偶数都会被筛掉，奇数都不会筛掉，答案就显然了。



---



第二个输出的数没有那么简单了。虽然 $n$ 始终是第二个数的 $3.2$ 倍左右，但是倍数一直在变。

假设我们现在已经有一个无限长的 $primes$ 数组（数组内填了数）。

你考虑一下什么时候 $counter$ 才会加。显然，如果当前数是 $2$ 的倍数，那么在 $j = 1$ 时 $counter$ 会加；如果当前数是 $\operatorname{lcm}(2,3)$ 的倍数，那么在 $j = 2$ 时 $counter$ 会加……

我们可以预处理出 $primes$ 数组的数和前缀最小公约数（在前缀最小公约数小于 $n$ 的情况下），然后算出 $n$ 以内当前前缀最小公约数的倍数个数（注意要保证这些倍数乘 $primes$ 数组当前的数不超过 $n$）。把这些倍数个数加起来，就是答案了。

## AC CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, cnt, ans;
int p[10000005];

signed main()
{
    cin >> n;
    if (n == 1)
        return cout << 0 << ' '<< 0 << '\n', 0;
    cout << (n + 1) / 2 << ' ';
    int now = 2, ans = 0;
    ans = ans + (n / 2 / 2);
    for (int i = 3;; i += 2)
    {
        if ((__int128)(now / __gcd(now, i) * i > n))
            break;
        now = now / __gcd(now, i) * i;
        ans = ans + (n / i / now);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Grand_Dawn (赞：3)

### 第一个数

分析：打表 `primes` 数组可以发现形如 $[2,3,5,7,9,11,\cdots]$ 的样子，即 $2$ 后面跟了所有 $>2$ 的奇数。

以下对此进行证明：

显然 $2$ 会出现在 `primes` 数组内。

偶数 $x$ 除了 $2$ 不会出现在 `primes` 数组内。

证明：当 $i=\lfloor \frac{x}{2}\rfloor,j=1$ 时，使得 $x$ 不会出现在 `primes` 数组内。

所有奇数 $x$ 都会出现在 `primes` 数组内。

证明：

首先如果需要使 $x$ 不在 `primes` 数组内，则需要 $i\mid x$ 且 $i\neq x$。由 $x$ 为奇数，因此 $i$ 为奇数，且 $\frac{x}{i}>2$。

由 $i$ 为奇数，则当 $j=1$ 时就会跳出循环，因此不会更新 $x$ 为合数。

因此，第一个数的答案为 $\begin{cases}0\ &n=1\\\lceil \frac{n}{2}\rceil&n>1\end{cases}$，也可为 $\lceil \frac{n}{2}\rceil-[n=1]$。


### 第二个数

以下为了好看，定义 $p_k$ 为 `primes` 数组的第 $k$ 个数。

可以对每个 $i$ 第二个答案增加了多少进行统计。

若 $i$ 使得第二个答案至少增加了 $j$，则需要满足 $\forall k\leq j,p_k\mid i$ 且 $i\times p_j\leq n$。

即 $i$ 为 $\operatorname{lcm}(p_1,p_2,\cdots,p_j)$ 的倍数，且  $i\leq \frac{n}{p_j}$。

因此，使得第二个答案至少增加了 $j$ 有 $\lfloor\dfrac{n}{p_j\times \operatorname{lcm}(p_1,p_2,\cdots,p_j)}\rfloor$ 个数。

因此第二个答案为 $\sum\limits_j\lfloor\dfrac{n}{p_j\times \operatorname{lcm}(p_1,p_2,\cdots,p_j)}\rfloor$。

由于 $\operatorname{lcm}(p_1,p_2,\cdots,p_j)$ 是关于 $j$ 的（非严格）递增函数，所以当 $\operatorname{lcm}(p_1,p_2,\cdots,p_j)>n$ 时，之后的 $j$ 都有 $\lfloor\dfrac{n}{p_j\times \operatorname{lcm}(p_1,p_2,\cdots,p_j)}\rfloor=0$，即可以跳出循环不再枚举。

注意计算 $\operatorname{lcm}$ 先除后乘。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int gcd(int x,int y){
	return y?gcd(y,x%y):x;
} 
int n,ans,mul=1,tmp=2;
signed main(){
	cin>>n;
	while(mul<=n&&tmp<47){
		mul=mul/gcd(tmp,mul)*tmp;
		ans+=n/mul/tmp;
		tmp=tmp+2-(tmp==2);
	}
	cout<<(n+1)/2-(n==1)<<" "<<ans<<endl;
	return 0;
}
```

---

## 作者：Hopeful_Hunter (赞：2)

首先观察样例发现第一个样例一定是 $\lceil \frac{n}{2} \rceil$。

手推一下加入数字的过程：

当处理到数字二时，此时 $cntp = 1, counter = 1$，并将 $isnotprime_{4}$ 赋值为 $1$。

当处理到数字三时，此时 $cntp = 2, counter = 2$，并将 $isnotprime_{6}$ 赋值为 $1$。

......

首先大于所有大于 $1$ 的奇数而言更新其他数字是否被筛到时，则必然枚举到 $2$ 就停止了。

接着对于所有大于 $0$ 的偶数而言更新其他数字是否被筛到时，由于本身是偶数，所以其筛出的数也必然是偶数。

由于两种筛法都没有办法筛出奇数，而 $n$ 以内大于 $1$ 的奇数有 $\lceil \frac{n - 2}{2} \rceil$ 个，接着 $2$ 一开始没有被筛到，所以 $cntp$ 一定为 $\lceil \frac{n - 2}{2} \rceil + 1 = \lceil \frac{n}{2} \rceil$。

接着考虑计算 $counter$ 的值，对于每个未被筛到的元素单独考虑贡献，假设 $x$ 为筛倍数时筛到当前考虑的元素中某个 $i$，当前考虑元素为 $y$，$l$ 为未被筛到的元素中小于等于 $y$ 的 $\operatorname{lcm}$。

首先必然有 $x \times y \le n$，那么现在 $x$ 的范围在 $[1, \lfloor \frac{n}{2} \rfloor]$ 之内，那么 $x$ 整除 $l$，由于 $l$ 增长速度较快，所以需要考虑的元素数量较少，那么只需要考虑这些 $l \le n$ 中未被筛到的元素。

注意：

1. $n$ 可能为 $1$。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

long long n;

long long gcd(long long a, long long b){
  return !b ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b){
  return a / gcd(a, b) * b;
}

int main(){
  cin >> n;
  if(n == 1){
    cout << 0 << ' ' << 0;
    return 0;
  }
  cout << (n + 1) / 2 << ' ';
  long long ans = (n / 2) / 2;
  long long l = 2;
  for(long long i = 2; 2 * i - 1 <= n; i++){
    long long nw = 2 * i - 1;
    l = lcm(l, nw);
    if(l > n) break;
    ans += (n / nw) / l;
  }
  cout << ans;
  return 0;
}

```

---

## 作者：keatsli (赞：2)

首先注意到这里定义的“质数”是 $n$ 以内所有除了 $1$ 的奇数和 $2$，下面我们证明这一点：

显而易见，$2$ 一定被包含在里面，而对于所有形如 $2k$，$k\geq 2$ 的数，它会被 $k\times 2$ 筛掉，并且偶数只能筛掉偶数。

接下来，对于任何一个形如 $2k+1$ 的数，它能且仅能筛掉 $2(2k+1)=4k+2$，因为 $2\nmid 2k+1$，故在第一次循环就会跳出。

这时候它定义的“质数”的结构我们就清楚了，与之同时而出的就是第一问的答案。

接下来考虑第二问：

首先，如果 $2\nmid i$，则 $i$ 一定不会有贡献。

接下来，$i$ 的贡献就是 $i$ 整除 $2,3,5,...$ 中连续前多少个，并且要满足它不会退出循环。

考虑拆贡献：将整体贡献拆成 $2\mid i$，$\text{lcm}(2,3)\mid i$，$\text{lcm}(2,3,5)\mid i$ 等等，整整除一个贡献为 $1$。

我们可以容易地估计 $\text{lcm}(2,3,5,...,2k+1)$ 的下界：它大于等于把 $2k+1$ 以内的素数全乘起来，所以这玩意增长得非常快，跑一下极限数据可知复杂度上界。

于是我们对每个 $\text{lcm}(2,3,5,...,2k+1)$ 以及 $2$ 计算它造成的贡献，即得答案。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<10000010>isnp;
int pr[10000010],cntp,cnt;
int main(){
	long long n;cin>>n;
	long long sum=2;
	long long ans=0,ed=2;
	for(long long i=0;i<=1000;++i){
		sum=sum*(2*i+1)/__gcd(sum,2*i+1);
		if(__int128(sum)*ed>n)break;//这里乘ed的目的就是计算到多少的时候会直接在筛法内层循环break
		ans+=n/sum/ed;
		ed=2*(i+1)+1;
	}
	cout<<((n+1)/2-(n==1))<<" "<<ans<<endl;
	return 0;
}
```

第一问用 $\lfloor\dfrac{n+1}{2}\rfloor$ 计算是因为这东西代表的是 $n$ 以内奇数个数，但是其实“质数”没有 $1$，但是有 $2$，故 $n=1$ 时需要特判。

---

## 作者：M1KuM3yusQAQ (赞：2)

# P11169 「CMOI R1」Bismuth / Linear Sieve SOLUTION

## 题意

阅读程序，优化复杂度使程序在 500ms 内能通过 $n \le 10^{18}$ 规模的数据。

伪代码转 C++：
```c++
#include <bits/stdc++.h>
using namespace std;

unsigned long long n;
bool isNotPrime[10000005];
int primes[10000005];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		isNotPrime[i] = false;
	}

	long long cntp = 0;
	long long counter = 0;

	for (int i = 2; i <= n; i++) {
		if (!isNotPrime[i]) {
			cntp++;
			primes[cntp] = i;
		}

		for (int j = 1; j <= cntp; j++) {
			if (i * primes[j] > n)
				break;
			isNotPrime[i * primes[j]] = true;
			if (i % primes[j] > 0)
				break;
			counter++;
		}
	}

	cout << cntp << " " << counter;
	return 0;
}
```

## 分析

需要注意的是，此 `primes` 非彼质数，此 `isNotPrime` 也非筛去的合数，`cntp` 也非 count primes。为避免歧义，接下来的题解中称原题中的第一个输出 `cntp` 为 $r_1$，第二个输出 `counter` 为 $r_2$。

观察样例，注意到 $r_1$ 与 $n$ 近似成比例关系，猜想两者比值近似为定值。

不放写形似这样的调试代码来便于我们观察 $r_1$ 和 $r_2$ 的变化。

```c++
cout << "i = " << i << ", j = " << j << endl;
//////// ... ////////
cout << i * primes[j] << " is not a prime" << endl;
```

我们来考虑 $r_1$ 统计的内容。原程序用 $r_1$ 统计了 “质数” 的个数，何时原程序认为一个数是质数呢？原程序遍历已有的 “质数”，并标记其与 $i$ 的积为合数，可是当 $i$ 不为 $primes_j$ 的倍数时原程序跳出循环，由于**所有奇数都不是 $primes_j$ 第一个元素 $2$ 的倍数**，导致**所有为奇数的合数无法被筛出**，而任意一个数的两倍都在跳出循环前被标记为合数。结合打表可知，题中 `primes` 由 **【$2$ 和 $n$ 以下除 $1$ 以外的奇数】** 构成，由此可推导出 $r_1$ 的值：

- 当 $n = 1$ 时，$r_1 = 0$；
- 当 $n \not = 1$ 时，$r_1 = \lceil \frac{n}{2} \rceil$。

我们来考虑 $r_2$ 统计的内容。什么时候 $r_2$ 的值产生变化呢？**每次遍历到 $primes$ 中的元素直到 $i$ 不为 $primes_j$ 的倍数时。** 举个例子，假设先后遍历到 $primes_j$ 的值为 $2, 3, 5$，$i$ 的值为 $10$，虽然 $10$ 为 $2$ 和 $5$ 的倍数，但在遍历到 $3$ 时由于其非 $10$ 的倍数原程序已经跳出循环，所以 $r_2$ 的值只会增加 $1$。

发现了吗？原程序统计的是 $n$ 以内为 $2$ 的倍数的数，以及同时为 $2, 3$ 的倍数的数，同时为 $2, 3, 5$ 的倍数的数…… **同时为 $\text{lcm}(primes_1, primes_2, \dots, primes_{r_1})$ 的倍数的数！**

有了如上结论，原程序的算法和时间复杂度可以被瞬间简化。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

long long n;
long long cntp, counter = 0;
long long Div = 2;
long long p = 2;

int main() {
	cin >> n;
	cntp = n / 2;
	if (cntp * 2 < n) cntp++;
	if (n == 1) cntp = 0;
	
	while (n / p / Div) {
		counter += n / p / Div;
		
		if (p == 2) p = 3;
		else p += 2;
		Div = Div * p / __gcd(Div, p);
	}
	
	cout << cntp << " " << counter;
	
	
	
	return 0;
}
```
希望能帮到大家，请多指教！orz

---

## 作者：allen2010 (赞：1)

这个伪代码与线性筛十分相似，区别在于注释过的那一行。线性筛原本想要通过那一行来优化，但是这个伪代码的作用恰好相反（线性筛：如果这个数不是最小质因数就返回。这个伪代码：如果这个数是最小“质”因数就返回）。

根据代码分析，这样做会把除2外的偶数筛去，把除1外的奇数保留。如果把2当做1来统计，这样输出的第一个数相当于 $n$ 以内奇数的数量。

第二个数统计的是被重复筛的个数。如果一个数的“质”因数越多其被重复筛的次数越多。同时，要注意这句话：

```
If i * primes[j] > n
	break
```
说明一个数如果能为答案多贡献1还要满足其小于等于 $\lfloor\frac{n}{primes_j}\rfloor$ 。还有要注意的是，实际统计答案是因为伪代码统计的“质数”并非真正的质数，所以能被有些数整除可能已经被满足了（如15，已经在前面被3和5满足）。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt;
int main()
{
    unsigned long long n,ans=0;
    cin>>n;
    if(n==1)//注意要特判
    {
        cout<<"0 0";
        return 0;
    }
	int f=1;
	unsigned long long fac=2;
	for(unsigned long long i=3;i<=n;i+=2)
	{
		fac*=i/__gcd(i,fac);//这里要注意
		if(fac>n) break;//这里要注意
		ans+=n/i/fac;
	}
    cout<<n-n/2<<" "<<ans+n/4<<endl;
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# 解题报告

## 前言

赛时因为这题，红温导致浪费 $inf$ 小时。

其实很简单，但是我沉迷找规律无法自拔。

## 思路分析

为了方便表述，以下把题面给出的筛法叫错误筛。

首先容易发现错误筛筛出的质数为：$2,3,5,7,9,11,13,\cdots$。

然后第一问答案显然是 $\lfloor \frac{n}{2} \rfloor +[n \equiv 1 \pmod{2}]$。

重点在于求第二问。

不难发现，第二问的答案和 $i$ 有关。$i$ 形如 $2^{p_1}$ 对第二问答案的贡献为 $1$。形如 $2^{p_1} \cdot 3^{p_2}$ 贡献为 $2$。形如 $2^{p_1} \cdot 3^{p_2} \cdot 5^{p_3}$ 贡献为 $3$。以此类推。

所以答案为：

$$cnt_2= \sum_{i=1}^{n} \sum_{j=1}^{primesum} \prod_{k=1}^{j} [i \equiv 0 \pmod{p_k} \wedge i \cdot p_k \le n]$$

直接算是 $O(n \log n)$ 的。甚至不如暴力。

将这个柿子改变枚举顺序：

$$cnt_2= \sum_{i=1}^{primesum} \sum_{j=1}^{\lfloor \frac{n}{p_i }\rfloor} \prod_{k}^{i} [j \equiv 0 \pmod{p_k}] $$

然后再加一点优化：

$$cnt_2=\sum_{i=1}^{primesum} \sum_{j=1}^{\lfloor \frac{n}{p_i }\rfloor} [j \equiv 0 \pmod{\operatorname{lcm}(p_1,p_2,\cdots,p_i)}]$$

发现枚举 $j$ 是多余的：

$$cnt_2=\sum_{i=1}^{primesum} \lfloor \frac{\lfloor \frac{n}{p_i} \rfloor}{  \operatorname{lcm}(p_1,p_2,\cdots,p_i) } \rfloor$$

这样就好看了：

$$cnt_2=\sum_{i=1}^{primesum} \lfloor \frac{n}{p_i \cdot \operatorname{lcm}(p_1,p_2,\cdots,p_i)} \rfloor$$

预处理 $p$ 数组和前缀 $lcm$ 数组，可以做到 $O(\log n)$。

然后就做完了。可能需要特判 $n=1$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p[35]={0,2,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51},b[35]={0,2,6,30,210,630,6930,90090,90090,1531530,29099070,29099070,669278610,3346393050,10039179150,291136195350,9025222055850,9025222055850,9025222055850,333933216066450,333933216066450,13691261858724450,588724259925151350,178796613842716869,8403440850607692843,5940232058166813755,7803929787154675649,7779909097587673845,723977334400474861,4373219913407963845},cnt=29;
int get(){
	int ans=0;
	for(int i=1;i<=cnt;i++){
		if(!p[i] || !b[i]) break; 
		ans+=(n/p[i]/b[i]);
	}
	return ans;
}
signed main(){
	cin>>n;
	if(n==1) cout<<0<<' '<<0<<endl;
	else cout<<(n/2+n%2)<<' '<<get();
	return 0;
}
```

## 后记

挺简单的，应该反思自己为什么浪费了那么长时间找了个错误的规律。

数学没学好。

---

## 作者：Z_AuTwT (赞：0)

打个表可以发现，第一个答案就是 $\lceil \frac{n}{2} \rceil$。

那第二个答案是什么呢，依然是打表，发现好像很有规律的样子。

考虑每个数对答案的贡献，先筛出题目给出的伪代码的数，每次从低到高的最小公倍数可以被减几次就是这个数的贡献。

~~在暴力可以过的时候用暴力？~~

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long 
bool inp[11000000];
int pri[11000000];
main(){
	long long n;
	cin>>n;
	if(n<=1e7){
		int Cnt=0,Cnt1=0;
		for(int i=2;i<=n;i++){
			if(inp[i]==0){
				Cnt++;
				pri[Cnt]=i;
			}
			for(int j=1;j<=Cnt;j++){
				if(1LL*i*pri[j]>n) 
					break;
				inp[i*pri[j]]=1;
				if(i%pri[j])
					break;
				Cnt1++;
			}
		}
		cout<<Cnt<<" "<<Cnt1;
		return 0;
	}
	long long Cnt=0,Sum=1;
	int Cnt1=0;
	for(int i=2;i<=60;i++){
		if(inp[i]==0){
			Cnt1++;
			pri[Cnt1]=i;
		}
		for(int j=1;j<=Cnt1;j++){
			if(1LL*i*pri[j]>60) 
				break;
			inp[i*pri[j]]=1;
			if(i%pri[j])
				break;
		}
	}
	int tot=1;
	Sum=1;
	for(;Sum<=n;tot++){
//		cout<<pri[tot]<<"\n";
		Sum=Sum*pri[tot]/__gcd(Sum,pri[tot]);
		long long V=n/pri[tot]/Sum;
		Cnt+=V;
	}
	cout<<(n+1)/2<<" "<<Cnt;
}
```

---

