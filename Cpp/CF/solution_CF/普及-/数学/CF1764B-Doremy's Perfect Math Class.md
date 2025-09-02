# Doremy's Perfect Math Class

## 题目描述

"Everybody! Doremy's Perfect Math Class is about to start! Come and do your best if you want to have as much IQ as me!" In today's math class, Doremy is teaching everyone subtraction. Now she gives you a quiz to prove that you are paying attention in class.

You are given a set $ S $ containing positive integers. You may perform the following operation some (possibly zero) number of times:

- choose two integers $ x $ and $ y $ from the set $ S $ such that $ x > y $ and $ x - y $ is not in the set $ S $ .
- add $ x-y $ into the set $ S $ .

You need to tell Doremy the maximum possible number of integers in $ S $ if the operations are performed optimally. It can be proven that this number is finite.

## 说明/提示

In the first test case, no such $ x $ and $ y $ exist. The maximum possible number of integers in $ S $ is $ 2 $ .

In the second test case,

- $ S=\{5,10,25\} $ at first. You can choose $ x=25 $ , $ y=10 $ , then add $ x-y=15 $ to the set.
- $ S=\{5,10,15,25\} $ now. You can choose $ x=25 $ , $ y=5 $ , then add $ x-y=20 $ to the set.
- $ S=\{5,10,15,20,25\} $ now. You can not perform any operation now.

After performing all operations, the number of integers in $ S $ is $ 5 $ . It can be proven that no other sequence of operations allows $ S $ to contain more than $ 5 $ integers.

## 样例 #1

### 输入

```
2
2
1 2
3
5 10 25```

### 输出

```
2
5```

# 题解

## 作者：kimidonatsu (赞：9)

# CF1764B Doremy's Perfect Math Class 题解

题意简述就省去吧，题目翻译已经很简洁了。

## 思路分析

对于整数集合 $\mathbf{S}$，我们可以通过分析数据来找一下规律：

对于第一组样例：由于是一个只有两个元素的 $\mathbf{S} = \{ 1, 2 \}$，由于 $2 - 1 = 1$，而 $1$ 已在集合中，那么只能输出其长度 $2$。

对于第二组样例：$\mathbf{S} = \{ 5, 10, 25 \}$，选择 $25 - 10 = 15$ 并加入集合中，得到新集合 $\mathbf{S} = \{ 5, 10, 15, 25 \}$，再选择 $25 - 5 = 20$ 并加入集合中，得到 $\mathbf{S} = \{ 5, 10, 15, 20, 25 \}$，可以发现当前集合已无法继续操作，所以输出长度 $5$。

易得，我们需要将集合 $\mathbf{S}$ 减成一个 **等差数列**。

---

接下来我们给出数学证明：

因为集合 $\mathbf{S}$ 是一个等差数列，意味着其元素从小到大依次为 $\mathbf{S} = \{ s_1, s_2, s_3, s_4, s_5 \cdots \}$。

所以 $s_2 - s_1$ 一定在集合中。

$\because s_2 - s_1 < s_2 \ \therefore s_2 - s_1 = s_1$。

同理可得 $s_3 - s_2 = s_2$ 或者 $s_3 - s_2 = s_1$。而我们可以发现 $s_3 - s_2 = s_1$ 是不可能存在的，如果这样，那么 $s_2 = 2 \times s_1, s_3 = 2 \times s_2 = 4 \times s_1$。

那么 $s_3 - s_1 = 3 \times s_1$，因为 $s_2 < s_3$ 且集合具有非负性，所以 $s_2$ 和 $s_3$ 之间不可能还有一个 $3 \times s_1$ 的值存在。

将发现推广一下，可以发现 $s_i - s_{i - 1} = s_1$，这就是我们要找的等差数列。

---

有思路了，但是代码的实现呢？

我们可以从每次新加的数 $x - y$ 来找思路。难道不觉得 [眼熟](https://oi-wiki.org/math/number-theory/gcd/) 吗？可以发现，集合序列中数字的公差正是它们的 **最大公约数**，那么每个数我们都可以表示成 $a \times gcd$，最小值则是 $1 \times gcd$，最大值就是 $\max \times gcd$，那么我们输出的答案就是 $\dfrac{s_i}{gcd}$。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n, p, gcd;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		scanf("%d", &p);
		gcd = p;
		for (int i = 1; i <= n - 1; i++) {
			scanf("%d", &p);
			gcd = __gcd(gcd, p);
		}
		printf("%d\n", p / gcd);
	}
	return 0;
}

```

代码小注：

* 由于有现成的 `__gcd`，便直接引用来求最大公约数。
* 数据范围是 $2 \times 10^5$，所以完全不需要开 `long long`。
* 先读入第一个元素 $p$，并设置当前 $gcd$ 为 $p$ 的原因是，之后我们每次读入新 $p$，只需统计新 $p$ 的 $gcd$ 并在输出时直接使用上述公式 $\dfrac{s_i}{gcd}$，这可以省去一个数组的空间。


---

## 作者：loser_seele (赞：3)

upd：修正了错别字。

考虑能得到的数的性质：设数列中所有数的 $ \gcd $ 为 $ a $，最大数为 $ S $，则这个数一定能表示为 $ ka $ 的形式，其中 $ k $ 为正整数且 $ ka \leq S $。

证明：由于 $ \gcd $ 的差分性质，满足条件的数一定能被这样表示：由某两个数辗转相除出 $ \gcd $，然后再用 $ S $ 减若干次即可。

可以证明只有这样的数才满足条件，因为两个能被 $ \gcd $ 整除的数相减后得到的数不可能不能被其整除。

因此答案即为 $ \frac{S}{a} $，注意数列中最小的数为 $ 0 $ 的时候答案 $ +1 $，因为能多一个 $ 0 $。

---

## 作者：NaOHqwq (赞：1)

笔者读题读了半个小时，看了题解才恍然大悟，于是也来水一篇。

题意给的很明确，这里就不多解释了。

## 思路

可以先对样例进行观察：

通过观察第 $1$ 组样例可以发现最终结果是 $2$，与该集合中最大的元素大小相同。

接下来观察样例 $2$ 可以发现最终结果是 $5$，也就是集合中最大的元素 $25$ 除以 $5$ 的结果，而 $5$ 又是该集合中所有元素的最大公约数。

我们还发现样例 $2$ 得出的结论也可以用在样例 $1$ 中，样例 $1$ 中的结果 $2$ 恰好是集合中最大元素 $2$ 除以集合中元素的最大公因数 $1$ 得到的结果。

通过构造多组样例验证可得上述结论在大部分条件下是可成立的。所以得出结论：集合中的最大元素除以集合中所有元素的最大公约数等于集合最终的最大长度。

结论有了，代码自然就呼之欲出了。

## 代码

注：`__gcd` 是求最大公约数的系统函数。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[100001];
int main(){
	ll n, m;
	cin >> n;
	while(n--){
		ll _gcd = 0;
		memset(a, 0, sizeof(a));
		cin >> m;
		for(ll i = 1;i <= m;i++){
			cin >> a[i];
		}	
		_gcd = __gcd(a[1], a[2]);
		for(ll i = 3;i <= m;i++){
			_gcd = __gcd(a[i], _gcd); //求最大公约数 
		}	
		for(ll i = 1;i <= m;i++){
			a[i] /= _gcd; //根据结论计算 
		}
		cout << a[m] << endl;
	}
	return 0;
}
```

---

## 作者：chlchl (赞：1)

~~又来水估值了。~~

## 题意简述
题目翻译很清楚，故不再提供。

## 做法
观察样例，易得只需要减到是一个等差数列就行了。

简单证明：假设最后集合 $S$ 从小到大依次为 $a_1,a_2,\cdots,a_n$。

则 $a_2-a_1$ 在集合中。因为 $a_2-a_1<a_2$，所以 $a_2-a_1$ 只能为 $a_1$。

此时 $a_3-a_2$ 也必定在集合中，由上述过程可以得 $a_3-a_2=a_1$ 或 $a_3-a_2=a_2$。

仔细推敲，你会惊人地发现，$a_3-a_2$ 不可能等于 $a_2$。因为这样，$a_2=2a_1,a_3=2a_2$，进而 $a_3=4a_1$。

有什么问题呢？$a_3-a_1=3a_1$，就不在集合中了（因为是从小到大排列的，$a_2$ 与 $a_3$ 之间不可能再有值存在）。

所以 $a_3-a_2=a_1$。推广一下，$a_i-a_{i-1}=a_1$，就是等差数列啦！

并且我们通过证明，还能发现要求的就是给定的数能凑出的最小值。并且因为 $a_1$ 是公差，所以用 $a_n\div a_1$ 就能得到项数（第 $i$ 项是 $a_1$ 的 $i$ 倍）。

也就是说，我们要先做差，再做差，又双叒叕作差，一直到减出来等于较小数（即 $x-y=y$ 的形式）。

你不觉得这有点熟悉吗？对，辗转相除！

因此，我们要求的是所有差中的最大公因数 $d$，这同时也是 $a_1$。

看到这里，你就去打代码了，交上去之后就 WA 了。

为什么呢？不妨看个例子：

$S=\{3,5,7,9\}$，您的程序输出多少呢？

显然答案是 $9$，因为我们可以凑出 $1,2$，进而凑出其他的数。

造成差异的，就是公差 $2$ 出来之后，与 $3$ 的差不为 $2$（即它们的公差已不满足）。

如你所见，光算差还不行，因为减出来之后想保证公差与原数列仍保持等差，所以数列中的每个数都得是公差的倍数。

所以统计所有数和相邻差的最大公因数就行了。

为什么相隔的不用考虑呢？因为求最大长度，求的就是最小公差。相隔的差显然不是最小的，且一定是最小公差的倍数，故不用考虑。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
int T, n;
ll a[N];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		ll d = 0;
		for(int i=1;i<=n;i++){
			scanf("%lld", &a[i]);
			if(!d)
				d = a[i];//初始化 
			else
				d = __gcd(d, a[i]);
		}
		sort(a + 1, a + 1 + n);//从小到大排序 
		for(int i=2;i<=n;i++)
			d = __gcd(d, a[i] - a[i - 1]);//算差 
		printf("%lld\n", a[n] / d);//这是项数 
	}
	return 0;
}
```


---

## 作者：郑朝曦zzx (赞：1)

### 题目突破口
如果您没做出来这代题目您可以先考略一下以下问题：

- 新加的数是 $a - b$，这和辗转相除法（欧几里得算法）有什么相似点？

### 题解

根据欧几里得算法和辗转相除法，$\gcd(a, b)=\gcd(b, a \bmod b)$，新插入的所有数的最大公约数和原序列的最大公约数是一样的。

那么对于原序列的所有数，我们都可以把它表示为 $a \times GCD$，其中最小的数为 $1 \times GCD$，最大的数为 $k \times GCD$，那么对于 $i \times GCD (1\le i \le k)$ 我们都可以构造出来。所以答案就是 $k$。

时间复杂度：$O(n + \log(A))$ 其中 $A$ 表示原序列的最大值。

### 代码
```cpp
#include <cstdio>
int T, n, GCD, a;
int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}
int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &n, &a);
		GCD = a;
		for (int i = 2; i <= n; ++i)
		{
			scanf("%d", &a);
			GCD = gcd(GCD, a);
		}
		printf("%d\n", a / GCD);
	}
	return 0;
}
```


---

## 作者：wimg6_ (赞：1)

## CF1764B 题解

### 题目简述

给定集合 $S$，$S$ 有序，要往集合里添加集合内已有任意两个数的差，要求集合满足互异性，问集合中最多有多少个数。

### 思路

通过样例 $1$，不难发现最终的结果为集合 $S$ 内现有的最大的元素的值。

再观察样例 $2$，发现 $S$ 内最大元素 $25$ 除以 $5$ 的结果为 $5$，为最终需要输出的内容。而 $5$ 恰为 $S$ 内所有现有元素的最大公约数。

不难猜测：答案即 $S$ 内最大元素除以 $S$ 所有现有元素的值的最大公约数即可。构造样例可以发现结论在大部分情况下正确。

证明：因为 $S$ 内所有元素为正，故 $x-y>\max(x,y)$ 恒成立，则总数量一定不超过 $S$ 内最大元素。因为 $S$ 内两个数的差一定不会不为他们的最大公约数，所以元素总个数为 $S$ 现有元素的最大值减去非 $S$ 现有元素最大值内所有不为 $S$ 内所有元素最大公约数的个数。

### 代码

有序序列不需要 sort。

```
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[100010];
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		long long gcd=0;
		memset(a,0,sizeof(a));
		scanf("%lld",&n);
		for(long long i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		gcd=__gcd(a[1],a[2]);
		for(long long i=3;i<=n;i++)
			gcd=__gcd(a[i],gcd);
		for(long long i=1;i<=n;i++)
			a[i]/=gcd;
		printf("%lld\n",a[n]);
	}
	return 0;
}
```


---

## 作者：氧少Kevin (赞：0)

## CF1764B - Doremy's Perfect Math Class
- https://codeforces.com/contest/1764/problem/B

### 题意
给定一个正整数集合 $S$。对于 $S$，你可以执行以下操作若干次：
- 从集合中选两个数 $x$ 和 $y$，使得 $x$ 和 $y$ 满足 $x>y$ 并且 $x-y$ 不在集合 $S$ 中
- 将 $x-y$ 作为一个新元素加入到集合中
求出：无法操作时集合 $S$ 的最大长度。题目保证结果有限

### 思路
- 根据 $\gcd$ 的性质 $\gcd(x,y)=\gcd(x,y-x)$ 可知，
- 设刚开始的集合为 $S$，最后的集合为 $S'$，那么 $\gcd(S) = \gcd(S')$
- 我们又能发现，最后的集合 $S'$ 中：
    - $\max(S')=\max(S)$
    - $\min(S')=\gcd(S)=\gcd(S')=$ $S$中任意两个元素差值的最小值
- $ans=\frac{\max(S')-\min(S')}{\gcd(S')}+1$

---

## 作者：luo_shen (赞：0)

## 题意描述
有一个集合，每次操作可以任取集合中的两个数 $x,y$ 且 $x>y$，若 $x-y$ 在集合中没有出现过，将 $x-y$ 加入到集合中，问集合中最多能有多少数。
## 题目分析
看见 $x,y$ 和 $x-y$ 可以想到求最大公约数时的 $\gcd(x,y)=\gcd(y,x\bmod y)$，那考虑往这个方向想一想。

因为 $a\bmod b$ 本质上其实是进行很多次 $a=a-b$ 的操作，直到 $a<b$。所以对于两个数 $a,b$ 且 $a>b$，能够产生的最小的数是 $\gcd(a,b)$，而 $a,b$ 又未被从集合中删去，所以对于所有的 $k\in [1,\frac{a}{\gcd(a,b)}]$，$k\times\gcd(a,b)$ 都可以由 $a$ 经过 $k-1$ 次 $a=a-\gcd(a,b)$ 得到。

那么拓展到多个数上时，令 $g$ 位所有数的 $\gcd$，$mx$ 为所有数中最大值，那么对于所有 $k\in [1,\frac{mx}{g}]$，$k\times g$ 都可以被得到。所以集合中最多能有的数的个数为 $\frac{mx}{g}$。
## Code
```cpp
void solve(){
    read(n);
    for(int i=1;i<=n;i++){
        read(a[i]);
    }
    int g=a[1];
    for(int i=2;i<=n;i++){
        g=__gcd(a[i],g);
    }
    write(a[n]/g);
}
```

---

## 作者：honglan0301 (赞：0)

## 题目分析
模拟一下容易发现，最终能出现的数就是 $\gcd(a_1,a_2,...,a_n)$ 的 $\leq \max(a_i)$ 的倍数。下面来证明这件事。  

首先, $S$ 是正数集合，用大减小的方式不可能减出比 $\max(a_i)$ 更大的数。其次，因为每个数都是 $\gcd$ 的倍数，它们相减之后一定不会出现非 $\gcd$ 倍数的数。而又因为可以通过辗转相减法在集合中得到 $\gcd$, 用集合中最大的数不断减去 $\gcd$ 就能得到所有可出现的数了。  
 
## 代码
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int t,n,a[200005];
inline int read()
{
	int now=0,nev=1; char c=getchar();
	while(c<'0' || c>'9') { if(c=='-') nev=-1; c=getchar();}
	while(c>='0' && c<='9') { now=(now<<1)+(now<<3)+(c&15); c=getchar(); }
	return now*nev;
}
inline int gcd(int a,int b) 
{    
    return b>0 ? gcd(b,a%b):a;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		int maxx=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			maxx=max(maxx,a[i]);
		}
		int gcdnow=gcd(a[1],a[2]);
		for(int i=3;i<=n;i++)
		{
			gcdnow=gcd(gcdnow,a[i]);
		}
		printf("%d\n",maxx/gcdnow);
	}
}
```

---

