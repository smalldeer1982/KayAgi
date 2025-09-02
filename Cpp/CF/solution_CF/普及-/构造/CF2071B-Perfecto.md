# Perfecto

## 题目描述

若一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$ 满足：对于每个下标 $i$（$1 \le i \le n$），前 $i$ 个元素的和 $p_1 + p_2 + \ldots + p_i$ 不是完全平方数 $^{\text{†}}$，则称该排列为完美排列。

你需要构造完美排列。给定正整数 $n$，找出一个长度为 $n$ 的完美排列，若不存在则输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是排列，但 $[1,2,2]$ 不是排列（数字 $2$ 重复出现），$[1,3,4]$ 也不是排列（当 $n=3$ 时出现数字 $4$）。

$^{\text{†}}$ 完全平方数是指某个整数的平方，例如 $9=3^2$ 是完全平方数，但 $8$ 和 $14$ 不是。

## 说明/提示

第一个测试用例中，当 $n = 1$ 时唯一可能的排列是 $p = [1]$，但它不满足完美条件：
- $p_1 = 1 = x^2$（当 $x = 1$ 时成立）。

第二个测试用例中，当 $n = 4$ 时一个可能的完美排列是 $p = [2, 4, 1, 3]$：
- $p_1 = 2 \neq x^2$；
- $p_1 + p_2 = 2 + 4 = 6 \neq x^2$；
- $p_1 + p_2 + p_3 = 2 + 4 + 1 = 7 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 = 2 + 4 + 1 + 3 = 10 \neq x^2$。

第三个测试用例中，当 $n = 5$ 时一个可能的完美排列是 $p = [5, 1, 4, 3, 2]$：
- $p_1 = 5 \neq x^2$；
- $p_1 + p_2 = 5 + 1 = 6 \neq x^2$；
- $p_1 + p_2 + p_3 = 5 + 1 + 4 = 10 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 = 5 + 1 + 4 + 3 = 13 \neq x^2$；
- $p_1 + p_2 + p_3 + p_4 + p_5 = 5 + 1 + 4 + 3 + 2 = 15 \neq x^2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
1
4
5```

### 输出

```
-1
2 4 1 3
5 1 4 3 2```

# 题解

## 作者：sLMxf (赞：4)

# 简述题意
判断是否存在一个排列：
- 长度为 $n$；
- $\forall i(1\le i\le n),k\in \text N^+,a_1+a_2+\cdots+a_i\ne k^2$。

存在则输出。
# 算法分析
很容易判断无解：如果 $\dfrac{n(n+1)}{2}$ 为完全平方数，那么无解。

接下来判断如何输出一个解。

首先 $\sum n\le10^6$ 告诉我们这题是 $O(n)$ 的。

所以先构造 $a_i=i$。

很显然，当前不为一个正解。

我们发现，前 $i$ 个数包含 $[1,i]$ 的所有数。

那么前 $i-1$ 个数的和为 $\dfrac{i(i-1)}{2}$。如果这个数不为完全平方数，跳过；否则，交换 $i-1$ 和 $i$。

因为令 $\dfrac{i(i-1)}{2}=k^2$，第 $i-1$ 个数为 $z$。那么新方案前 $i-1$ 个数和为 $k^2+i-z$，如果 $k^2+i-z=K^2$，则有 $K=k+1$（不然和会超过），即 $i-z=2k+1$。

显然 $k$ 是 $\sqrt 2i$ 级别的，不存在 $i-z\ge 2k+1$，那么 $k^2+i-z$ 不为完全平方数。

这样我们就找到了一个方案使得有解。
# 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[114514*10],sum[114514*10];
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		if((n+1)*n/2==(int)sqrt((n+1)*n/2)*(int)sqrt((n+1)*n/2)) cout<<"-1\n";
		else
		{
			for(int i=1;i<=n;i++) a[i]=i;
			for(int i=1;i<=n;i++)
			{
				sum[i]=sum[i-1]+a[i];
				if(sum[i]==(int)sqrt(sum[i])*(int)sqrt(sum[i])) swap(a[i],a[i+1]);
				sum[i]=sum[i-1]+a[i];
			}
			for(int i=1;i<=n;i++) cout<<a[i]<<' ';
			cout<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Pyrf_uqcat (赞：2)

有生之年看到了能写题解的橙题，今晚第六篇题解。

想到一个灵活的思路：先把 $a_i$ 设成 $i$，后面进行反复交换值，就不怕有数出现多次了。每次都判断和是不是平方数，如果不是就把 $a_i$ 和 $a_{i+1}$ 交换。因为平方数之间的差大于一，所以平方数加一肯定不是平方数。

判断不存在：从 $1$ 加到 $n$ 的和是平方数，随便怎么改都无法。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include <bits/stdc++.h>
#define int long long 

using namespace std;

const int N=2e6+5;

int n,a[N];

bool check(int x)
{
	return x==(int)sqrt(x)*(int)sqrt(x);
}

inline void init()
{
	for(int i=1;i<=n;i++)
	{
		a[i]=i;
	}
}

signed main()
{
	int t;cin>>t;
	while(t--)
	{
		cin>>n;
		init();
		if(check((1+n)*n/2))
		{
			cout<<-1<<endl;
			continue;
		}
		int sum=0;
		for(int i=1;i<=n;i++)
		{
			if(check(sum+a[i])) swap(a[i],a[i+1]);
			sum+=a[i];
		}
		for(int i=1;i<=n;i++) cout<<a[i]<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：ztrztr (赞：1)

## 思路
首先，可以通过暴力看出来只有很少的数满足 $\frac{n \times (n + 1)}{2}$ 是完全平方数，所以我们可以先设定一个原始的排序方式，就是从 $1$ 到 $n$。

我们先判断，如果 $\frac{n \times (n + 1)}{2}$ 是完全平方数，那么直接判断为无解，因为没有任何方法的排序，能让这个排序的总和是完全平方数。

如果不是无解，那么我们需要从 $1$ 开始往后遍历，来判断如果从 $1$ 加到现在是不是完全平方数。

如果发现加到 $i$ 是完全平方数，那么我们需要一个调换的方法，把这个数换掉，但是改动的要尽量少，不然我们后面的有很多要处理的。

这个方法就是调换 $i$ 和 $i + 1$，因为假设 $\frac{i \times (i + 1)}{2}$ 是完全平方数 $x ^2$，那么 $x ^ 2 + 1$ 就绝对不是完全平方数，因为下一个离 $x ^ 2$ 最近且大于 $x ^ 2$ 的完全平方数就是 $(x + 1) ^ 2$。而 $(x + 1) ^ 2 - x ^ 2 = (x+1-x) * (x+1+x) = 2 \times x + 1$，也就是只有当 $x = 0$ 的时候调换后还是完全平方数，而由于 $i$ 从 $1$ 开始的，所以 $x$ 不可能等于 $0$，调换后也就不可能是完全平方数了。

这个方法就是还有一个问题，就是如果 $1$ 加到 $i + 1$ 还是完全平方数的话也不行。假设 $\frac{n \times (n + 1)}{2} = x ^ 2$ 且 $\frac{(n + 1) \times (n + 2)}{2} = y ^ 2$，那么 $(y - x) \times (y + x) = n + 1$。又因为 $n = \sqrt{ x^2 + x ^ 2 + n} < 2x$，但是 $y \geq x + 1$，所以 $(y - x) \times (y + x) > n + 1$，所以不存在任何一个 $y$ 满足条件。所以如果 $1$ 加到 $i$ 是完全平方数的情况下，$1$ 加到 $i + 1$ 不会是完全平方数。

既然证明了，我们就可以按照以下步骤完成程序：
1. 让 $p$ 数组初始的时候设为从 $1$ 到 $n$。
2. 从 $1$ 开始遍历，如果遇到加到现在的和是完全平方数，那么就交换 $i$ 和 $i + 1$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
	int _T; cin >> _T;
	while (_T --) {
		long long x; cin >> x;
		long long cnt = x * (x + 1) / 2;
		if (x < 2 || (int)(ceil(sqrt(cnt)) * ceil(sqrt(cnt))) == cnt) cout << "-1\n";
		else {
//			cout << (int(ceil(sqrt(cnt)) * ceil(sqrt(cnt))) == cnt) << "\n";
			vector <int> v;
			long long sum = 2;
			cout << "2 ";
			for (int i = 1; i <= x; i ++) {
				if (i == 2) continue;
					sum += i;
				if ((int)(sqrt(sum)) * (int)(sqrt(sum)) == sum) {
					
					sum += i + 1;
					cout << i + 1 << " " << i << " ";i ++;
					
				} else cout << i << " ";
				
			}
		cout << "\n";}
	
	}
}
```

CF 上的[通过记录](https://codeforces.com/problemset/submission/2071/309907754)。

---

## 作者：masonxiong (赞：1)

# 题目简述

给定一个 $1\sim n$ 的排列 $p$，若其满足 $\forall i\in[1,n],k\in\N,\sum_{j=1}^ip_i\ne k^2$，则其合法。给定 $n$，请构造一个合法的排列，无解输出 `-1`。

# 题目分析

构造是困难的，但是乱搞是简单的。因为满足 $\frac{x(x+1)}{2}$ 是完全平方数的 $x$ 好像并不多，我们可以信仰猜测大部分的排列都是合法的。为了验证我们的猜测，我们可以写一个简单的 Python 程序验证一下数据范围内的这样的数的个数：

```python
n = 10 ** 6

for i in range(1, n + 1):
    if (i * (i + 1) / 2) ** 0.5 == int((i * (i + 1) / 2) ** 0.5):
        print(i)
```

结果如下：

```
1
8
49
288
1681
9800
57121
332928
```

因此我们可以考虑随机。

# 题目做法

随机出若干个排列并判合法，若合法直接输出，如果全都不合法就认为是无解的。将这个随机的次数设置在 $40$ 是一个比较稳妥的做法。

# 代码实现

```cpp
#include <bits/stdc++.h>
 
constexpr int Maxn = 5e5 + 5;
 
int t, n;
std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
std::array<long long, Maxn> A, S;
 
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    for (std::cin >> t; t--; ) {
        bool tag = false;
        std::cin >> n, std::iota(A.begin(), A.begin() + n, 1ll);
        for (int testTime = 40; testTime--; ) {
            std::shuffle(A.begin(), A.begin() + n, rng), std::partial_sum(A.begin(), A.begin() + n, S.begin());
            if ((tag |= std::all_of(S.begin(), S.begin() + n, [](long long i) -> bool { return (long long)sqrt(i) * (long long)sqrt(i) != i; })))
                break;
        }
        tag ? (std::for_each(A.begin(), A.begin() + n, [](long long i) -> void { std::cout << i << ' '; }), std::cout << '\n') : std::cout << "-1\n";
    }
    return 0;
}
```

---

## 作者：c_legg (赞：1)

## 题意 [$\color{#404040}\scriptsize\textsf{B. Perfecto}$](https://codeforces.com/contest/2071/problem/B)

给出一个正整数 $n$，要构造一个长度为 $n$ 的排列 $a$，使得对 $a$ 的所有前缀和 $s$ 都不是完全平方数。

如果无法构造，输出 `-1`。

## 思路 [$\color{#404040}\scriptsize\textsf{随机猜测}$](https://codeforces.com/blog/entry/126875)

考虑一种十分简单的方法：不断在现有的排列后面加数，如果加上这个数后为完全平方数，就从还没有选的数里找一个最小数的使得加上这个数之后的前缀和不是完全平方数。同时想到 $n=1$ 时一定不行，输出 `-1`。

- [ ] [代码，但是 Wrong answer on test $2$](https://codeforces.com/contest/2071/submission/308512845)

有点问题，我们多测试一下就不难发现，不仅是 $n=1$，$n=8$ 或其它值时也是不行的，所以考虑用一个 `list` 来维护排列 $a$，用 $\text{cnt}$ 来维护这个 `list` 的长度，如果 $\text{cnt}\neq n$，也要输出 $-1$。

- [ ] [代码，但是 Wrong answer on test $3$](https://codeforces.com/contest/2071/submission/308513277)

？？？仔细一看，是这里：

``` cpp
if(vis[i] || (sum+i)==[](int x) {return x*x;}((ll)sqrt(sum+i))) {
```

整型溢出了，不知道为什么，但是改掉好了：

``` cpp
if(!vis[j] && (sum+j)!=[](ll x) {return x*x;}((ll)sqrt(sum+j))) {
```

- [x] [代码，但是 Accepted](https://codeforces.com/contest/2071/submission/308513456)

---

## 作者：zzy10124 (赞：0)

这是蒟蒻的第一篇题解。

### 思路

先考虑 `-1` 的情况：$\sum_{i=1}^n$ 是平方数，怎么改最后都还是平方数。

考虑到每个数只可以输出一次，我们不妨把所有 $a_i$ 设成 $i$。每次都判断和是不是平方数，如果不是就把 $a_i$ 和 $a_{i+1}$ 交换。

证明交换后肯定不是平方数：交换后和减小或变大了一，平方数减一或加一后肯定不是完全平方数。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,p[2000001],t;
bool check(int x){
	return x==(int)sqrt(x)*(int)sqrt(x);
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) p[i]=i;
		if(check((1+n)*n/2)){
			cout<<-1<<endl;
			continue;
		}
		int sum=0;
		for(int i=1;i<=n;i++){
			if(check(sum+p[i])) swap(p[i],p[i+1]);
			sum+=p[i];
		}
		for(int i=1;i<=n;i++) cout<<p[i]<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：gdz0214_and_zxb0214 (赞：0)

## 思路
首先特判一下若 $1+2+3+\cdots+n$ 仍为完全平方数时则输出无解。

然后想到完全平方数中 $n^2$ 与 $(n+1)^2$ 相差 $(2n+1)$。

则想到若是当前为完全平方数，则想到找一个与当前数相减后小于 $(2n+1)$ 的数。

那么可以先建一个按大小排序的形为 $1,2,3,\dots,n$ 的序列。

随后对于 $i$，若 $\sum_{j=1}^{i-1} a_j$ 为完全平方数，则可以让它的后面的数中，$a_x-a_j\le 2\times\sqrt{\sum_{j=1}^{i-1} a_j}+1$ 的数，代替它。

则发现它后面的数比它多 $1$，可以使用。

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int check(int x){
	return x==(int)(sqrt(x))*(int)(sqrt(x));
}
int ans[500010],n,sum=0;
int solve(){
	sum=0; 
	scanf("%lld",&n);
	if(check(n*(n+1)/2)){
		printf("-1\n");
		return 0;
	} 
	for(int i=1;i<=n;i++){
		ans[i]=i;
	} 
	for(int i=1;i<=n;i++){
		if(check(sum+ans[i])){
			swap(ans[i],ans[i+1]);
		}
		sum+=ans[i];
		printf("%lld ",ans[i]);
	}
	printf("\n");
	return 0;
}
signed main(){
	int _;
	scanf("%lld",&_);
	while(_--){
		solve();
	}
	return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{48}$ 篇题解。

# $\mathbf{0x01}$ 承

求一个 $n$ 的排列，使得它的前缀和数组没有完全平方数，若不存在则输出 $-1$。

# $\mathbf{0x02}$ 转

首先考虑什么情况会无解。容易发现当 $\sum\limits_{i=1}^na_i=\frac{n(n+1)}2=k^2$ 时无解。

以 $n=9$ 为例，可能的一种排列如下：

$$2,1,3,4,5,6,7,9,8$$

可以看出只需要找到所有满足上式解的 $i$，并将 $a_i$ 与 $a_{i+1}$ 交换位置即可。

由于多组数据的限制，我们需要预处理：直接求出 $n=5\times10^5$ 时的数列即可。但是由于交换了位置导致某个区间的值域并不是 $[1,n](n\in\mathbb{N})$，所以需要特判：如果输出的最后一个数不是 $n$，直接输出 $n$。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,a[500005],g[500005]; 
int main(){
	cin>>T;
	for(ll i=1;i<=500004;i++){
		a[i]=i;//1 2 3 4
		g[i]=g[i-1]+a[i];
	}
	for(ll i=1;i<=500004;i++){
//		cout<<"g["<<i<<"]="<<g[i]<<endl;
		if(ll(sqrt(g[i]))*ll(sqrt(g[i]))==g[i]){
			swap(a[i],a[i+1]);
			g[i]++,g[i+1]--;
		}
	}
	while(T--){
		cin>>n;
		if(ll(sqrt(n*(n+1)/2))*ll(sqrt(n*(n+1)/2))==n*(n+1)/2){
			cout<<-1<<endl;
			continue;
		}
		for(ll i=1;i<=n;i++){
			if(i==n&&a[i]>n)cout<<n<<endl;
			else cout<<a[i]<<" ";
		}
		cout<<endl;
	}
}


```

---

## 作者：chatoudp (赞：0)

提供一种比官方题解短得多的方法。

先说结论：先将排列初始化为 $1,2,\dots,n$，然后遍历排列若前 $i$ 项的前缀和为完全平方和，则交换 $a_i,a_{i+1}$，若 $i$ 为 $n$ 则无解。

首先我们可以证明不会存在一个正整数 $i$，满足交换了 $a_i,a_{i+1}$ 又交换了 $a_{i+1},a_{i+2}$。也就相当于不存在 $1+2+\dots+i$ 为完全平方数，$1+2+\dots+(i+1)$ 也为完全平方数。

我们令 $s_i$ 表示 $1+2+\dots+i$。

若有 $s_n=A^2$，其中 $A$ 为正整数，则若还需满足 $s_{n+1}$ 为完全平方数，则它的值一定为 ${(A+B)}^2$，其中 $B$ 为正整数。而 $y=\sqrt{s_{x+1}}-\sqrt{s_x}$ 的却为这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/w2av9yy2.png)
因为平方数比 $s$ 的增长速度快，所以初始 $y=1$，后来会越来越少就不会是正整数，故得证。

因此每次遇到 $s_i$ 为完全平方数，总会交换的是 $i$ 与 $i+1$，交换后必定不是完全平方数。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,n,a[500005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) a[i]=i;
		long long sum=0;
		for(int i=1;i<=n;i++){
			sum+=a[i];
			if(floor(sqrtl(sum))*sqrtl(sum)==sum){
				if(i==n){printf("-1\n"); goto G;}
				else swap(a[i],a[i+1]),sum++;
			}
		}
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		printf("\n");
		G: ;
	}
	return 0;
}

```

---

## 作者：Magallan_forever (赞：0)

#### 简要说明题意：

现在存在一个长度为 $n$ 的全排列 $p$，如果 $p$ 满足 $\displaystyle{\sum_{j=1}^ip_i}$ 不是完全平方数对 $1 \leq i \leq n$ 成立，那么 $p$ 是一个完美的全排列。

给出 $n$，构造符合定义的全排列。

#### 题目分析：

脑子不好不会构造，提供一个邪道做法：

注意到 $\frac{n*(n+1)}{2}$ 好像经常不是完全平方数，那我们通过这段 `Python` 代码跑一下 $1 \leq n \leq 500000$ 看看结果：

```py
import numpy
for i in range(1,500001):
    if numpy.sqrt(i*(i+1)/2)==numpy.floor(numpy.sqrt(i*(i+1)/2)):
        print(i)
```

结果如下：

![](https://s21.ax1x.com/2025/03/03/pEGWvbn.png)

既然只有这么一点，那完全可以对这一点数特判：

对于 $n$ 等于这些数的情况，答案就是 $-1$，否则对于 $i=1,2,\dots,n$，如果 $i$ 等于这些数就先填 $i+1$ 再填 $i$，否则就直接填 $i$。

然后就行了：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        if(n==1||n==8||n==49||n==288||n==1681||n==9800||n==57121||n==332928) printf("-1\n");
        else{
            for(int i=1;i<=n;++i)
                if(i==1||i==8||i==49||i==288||i==1681||i==9800||i==57121||i==332928) printf("%d %d ",i+1,i),++i;
                else printf("%d ",i);
            putchar('\n');
        }
    }
    return 0;
}
```

---

