# Tourist Problem

## 题目描述

Iahub is a big fan of tourists. He wants to become a tourist himself, so he planned a trip. There are $ n $ destinations on a straight road that Iahub wants to visit. Iahub starts the excursion from kilometer 0. The $ n $ destinations are described by a non-negative integers sequence $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ . The number $ a_{k} $ represents that the $ k $ th destination is at distance $ a_{k} $ kilometers from the starting point. No two destinations are located in the same place.

Iahub wants to visit each destination only once. Note that, crossing through a destination is not considered visiting, unless Iahub explicitly wants to visit it at that point. Also, after Iahub visits his last destination, he doesn't come back to kilometer 0, as he stops his trip at the last destination.

The distance between destination located at kilometer $ x $ and next destination, located at kilometer $ y $ , is $ |x-y| $ kilometers. We call a "route" an order of visiting the destinations. Iahub can visit destinations in any order he wants, as long as he visits all $ n $ destinations and he doesn't visit a destination more than once.

Iahub starts writing out on a paper all possible routes and for each of them, he notes the total distance he would walk. He's interested in the average number of kilometers he would walk by choosing a route. As he got bored of writing out all the routes, he asks you to help him.

## 说明/提示

Consider 6 possible routes:

- \[2, 3, 5\]: total distance traveled: |2 – 0| + |3 – 2| + |5 – 3| = 5;
- \[2, 5, 3\]: |2 – 0| + |5 – 2| + |3 – 5| = 7;
- \[3, 2, 5\]: |3 – 0| + |2 – 3| + |5 – 2| = 7;
- \[3, 5, 2\]: |3 – 0| + |5 – 3| + |2 – 5| = 8;
- \[5, 2, 3\]: |5 – 0| + |2 – 5| + |3 – 2| = 9;
- \[5, 3, 2\]: |5 – 0| + |3 – 5| + |2 – 3| = 8.

The average travel distance is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/46abd0367bb1ab89fd9e16a66d93ae130f1cb4b6.png) = ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/3ee5b4e2d0bb159e64987b0886cc8a870c2084a7.png) = ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF340C/1d6a962c150afd1c2b26fd73c34a41806e6a93af.png).

## 样例 #1

### 输入

```
3
2 3 5
```

### 输出

```
22 3```

# 题解

## 作者：DPair (赞：6)

## 【前言】
楼下那篇题解似乎用了树状数组，我再看看我自己的代码，怎么没有用咧？

下面介绍一下不用树状数组的解法，并对另一篇题解进行一些补充。

## 【思路】
思路其实差不多，首先把答案分成两部分，一部分是**起始点**的贡献，由于每个点都可以被选为起始点，且剩下$(n-1)$个点的全排列都符合条件，故这一部分贡献为：
$$
\sum_{i=1}^na[i]*(n-1)!
$$
另一部分是**中间段**的贡献，由于我们访问点的顺序显然为点集的**全排列**，因此排列中每一对**相邻的数**的距离会产生贡献。故我们只要枚举每一对点对，然后计算其贡献即可。

对于每一个点对，它可以在排列中的$(n-1)$个位置中，剩下$(n-2)$个点的全排列都符合题意，因此这一部分的贡献为：
$$
\sum_{i=1}^n\sum_{j=1}^n|a_i-a_j|*(n-1)*(n-2)!
$$
$$
=\sum_{i=1}^n\sum_{j=1}^n|a_i-a_j|*(n-1)!
$$
由于总排列数为$n!$，所以答案为
$$
\frac{(\sum_{i=1}^n\sum_{j=1}^n|a_i-a_j| + \sum_{i=1}^na[i])*(n-1)!}{n!}
$$
$$
=\frac{\sum_{i=1}^n\sum_{j=1}^n|a_i-a_j| + \sum_{i=1}^na[i]}{n}
$$
下面介绍怎么处理

## 【处理】
另一篇题解用了树状数组，个人觉得没什么必要。

我们考虑对$a$数组升序排序，使得：

$$
a_1 \leq a_2 \leq a_3 \leq ...... \leq a_n
$$

而
$$
\sum_{i=1}^n\sum_{j=1}^n|a_i-a_j|
$$
显然可以化为（$a_i=a_i$所以没必要统计，其它部分呢由于可以反过来，要$\times2$）
$$
2*\sum_{i=1}^n\sum_{j=1}^{i-1}|a_i-a_j|
$$
由于排过序了，该式便可以化为：
$$
2*\sum_{i=1}^n\sum_{j=1}^{i-1}(a_i-a_j)
$$
$$
=2*\sum_{i=1}^n(i-1)*a_i-\sum_{j=1}^{i-1}a_j
$$
设$a$的前缀和为$pre$
那么我们只需要求
$$
2*\sum_{i=1}^n(i-1)*a_i-pre_{i-1}
$$
即可

总复杂度$O(nlogn)$，查询$O(n)$（常数相对优秀）

## 【喜闻乐见的代码时间】
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;
LL a[200010];
LL ans1, ans2;
LL gcd(LL x, LL y){return !y? x : gcd(y, x % y);}
int main()
{
    scanf("%d", &n);
    ans2 = n;
    for (register int i = 1;i <= n;i ++) scanf("%lld", &a[i]), ans1 += a[i];
    sort(a + 1, a + n + 1);
    LL pre = 0;
    for (register int i = 1;i <= n;i ++)
    {
        ans1 += ((i - 1) * a[i] - pre) * 2;
        pre += a[i];
    }
    LL num = gcd(ans1, ans2);
    printf("%lld %lld\n", ans1 / num, ans2 / num);
}
```

---

## 作者：QianianXY (赞：3)



[传送门](https://www.luogu.com.cn/problem/CF340C)

## 前言

妄求给数学公式恐惧者良好的体验。

## 题目分析

排列组合题？

我们形象的理解为两个点之间为一条边。

那问题就变成了思考每条边分别要用多少次。

和边权乘起来就是答案了。

我们将排列分成位置 $1$ 和位置 $2$ 到 $n$ 两个部分。

后一个部分有 $n-1$ 个放边的位置。

定义 $E$ 为边集，对于任意不相同的 $E_{i,j}$，每放到一个位置，显然其余的位置有全排列 $(n-2)!$ 种放置方案。

所以一条边的贡献 $=$ 放边的位置 $\times$ 放置方案 $=(n-1)\times(n-2)! = (n-1)!$

又因为题目求平均长度，所以要答案要除去 $n!$ 种序列。而 $(n-1)!$ 又可以和 $n!$ 约去。

关于位置 $1$ 的处理，可以视作 $E_{i,0}$，直接加进答案即可。

$$ ans= \dfrac {\sum\limits_{i=1}^n \sum\limits_{j=1}^n E_{i,j}+\sum\limits_{i=1}^nE_{i,0}} n$$

现在问题是左上角那坨东西怎么处理。

为了免去处理绝对值的麻烦，我们将 $a_i$ 升序排序。

然后左上角部分就变成了

$$ 2\times \sum\limits_{i=1}^n \sum\limits_{j=1}^{i-1}(a_i-a_j)$$

乘 $2$ 是因为 $i,j$ 先后不同就是两条边。 

这样用前缀和优化掉 $j$ 一维就搞定了。



忽略排序，复杂度为 $O(n)$。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 100010
using namespace std;
typedef long long ll;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

ll n, a[N], sum, ans;

int main()
{
	//freopen("a.txt", "r", stdin);
	read(n);
	for (rei i = 1; i <= n; i++) read(a[i]), ans += a[i];
	sort(a + 1, a + 1 + n);
	for (rei i = 1; i <= n; i++)
		ans += (((i - 1) * a[i] - sum) << 1), sum += a[i];
	printf("%lld %lld", ans / __gcd(ans, n), n / __gcd(ans, n));
	return 0;
}
```


---

## 作者：MuYC (赞：3)

#### 水话:
这道题目，看上去就很找规律啊

看到题名顺便%%%%tourist神仙

#### 思路：
首先我打了一个暴力，什么暴力？

全排列的暴力。

然后我打出了几个矩阵：
```plain
5
0 24 24 24 24 
24 0 24 24 24 
24 24 0 24 24 
24 24 24 0 24 
24 24 24 24 0 
```

```plain
4
0 6 6 6 
6 0 6 6 
6 6 0 6 
6 6 6 0 
```

```plain
6
0 120 120 120 120 120 
120 0 120 120 120 120 
120 120 0 120 120 120 
120 120 120 0 120 120 
120 120 120 120 0 120 
120 120 120 120 120 0 

```

+ 称给出的序列为$s$

这几个矩阵的意义是什么？矩阵中的$a[i][j]$表示的就是对于一个序列，按照题目要求的样子，$|s[i] - s[j]|$应该被计算多少次。

同时没有打出来的$|s[i] - s[0]|$也是跟出现的非零数相等的，都等于$(n-1)!$

所以对于原序列中的$|s[i] - s[j]|$都要被计算$(n-1)!$次，同时答案加上序列中每一个数*$(n-1)!$因为$|s[i] - s[0]|$也要被计算$(n-1)!$次。

总的情况是$(n!)$种，所以最后的答案等于:
### $\frac{(\sum_{i = 1}^{i = n}\sum_{j = 0}^{j = n}{|s[i] - s[j]|}) * (n-1)!}{n!}$

化简一下就是:
### $\frac{(\sum_{i = 1}^{i = n}\sum_{j = 0}^{j = n}{|s[i] - s[j]|}) }{n}$

然后我们就可以得到一个$n^2$的做法了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5 +50;
int n;
int a[MAXN],Ans = 0;
int S = 1;

int gcd(int a,int b)
{
	if(a % b == 0)return b;
	else return gcd(b , a % b);
}

signed main()
{
	cin >> n;
	for(int i = 1 ; i <= n ; i ++)cin >> a[i];
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= n ; j ++)
		Ans += abs(a[i] - a[j]);
		Ans += a[i];
	}
	cout << Ans / gcd(Ans,n) << " " << n / gcd(Ans,n);
	return 0;
}
```

CF数据可以让你成功在第10个点就TLE.....

这个式子就好求了。

首先，我们把给出的序列按从小到大排序，然后维护一个前缀和。

因为是排好序的，绝对值那里就可以去掉了。

为什么呢？因为排好序后，前面的数一定比$s[i]要小$

所以计算所有绝对值差就可以变成这个式子:

$s[i] * (i - 1) - sum[i - 1]$

$sum[i - 1]$表示第一个数到第（$i-1$）个数的前缀和。



### $\frac{(\sum_{i = 1}^{i = n}\sum_{j = 0}^{j = n}{|s[i] - s[j]|}) }{n}$
根据这个式子可以知道我们计算完的结果还要*$2$，所以计算答案的式子就是:
$(s[i] * (i - 1) - sum[i - 1])$ * $2$

然后每次累加一下前缀和就行了。

得出答案后化简分数求一个gcd即可 。

记得开long long

这样子的话，时间复杂度是O$(nlog(n))$的（瓶颈在排序上），空间复杂度是O$(n)$的。

然后放上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5 +50;
int n;
int a[MAXN],Ans = 0;
int sum[MAXN];

int gcd(int a,int b)
{
	if(a % b == 0)return b;
	else return gcd(b , a % b);
}

inline int read()
{
	int x = 0 ,flag = 1;
	char ch = getchar();
	for ( ; ch > '9' || ch < '0' ; ch = getchar());
	for ( ; ch >= '0' && ch <= '9'; ch =getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

signed main()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++)a[i] = read();
	sort(a + 1 ,a + 1 + n );sum[1] = a[1];
	for(int i = 1 ; i <= n ; i ++)
		Ans += a[i];
	for(int i = 2 ; i <= n ; i ++)
	{
		Ans += 2 * (a[i] * (i - 1) - sum[i - 1]);
		sum[i] = sum[i - 1] + a[i];
	}
	cout << Ans / gcd(Ans,n) << " " << n / gcd(Ans,n);
	return 0;
}
```

---

## 作者：qzhwlzy (赞：1)

## 题目大意
给定 $a$，求对于 $a$ 的所有排列 $a_{p_1},a_{p_2},…,a_{p_n}$，$|a_{p_1}-0|+\sum\limits_{i=2}^{n}{|a_{p_i}-a_{p_{i-1}}\ |}$ 的值之和。

## 思路
考虑两部分分开考虑。

第一部分 $|a_{p_1}-0|$，显然对于每一个 $p_1$ 的贡献是 $a_{p_1}$，而 $p_2\sim p_n$ 有 $(n-1)!$ 种排列方式，所以这一部分对最终答案的贡献是 $\sum\limits_{i=1}^{n}{a_i\times(n-1)!}$；

第二部分，可以枚举所有相邻的点对 $i,j$，由于其可以在排列的任意 $(n-1)$ 个位置上，剩下的 $(n-2)$ 个点可以任意排列，所以这部分对最终答案的贡献为：$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}{|a_i-a_j|\times(n-1)\times(n-2)!} = \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}{|a_i-a_j|\times(n-1)!}$

最后我们把两部分加起来：

$$
\begin{aligned}
ans &= \dfrac{\sum\limits_{i=1}^{n}{a_i\times(n-1)!} + \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}{|a_i-a_j|\times(n-1)!}}{n!}\\
&= \dfrac{\sum\limits_{i=1}^{n}{a_i + \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}{|a_i-a_j|}}}{n}
\end{aligned}
$$

如果就这样的话，代码的复杂度应该是 $\mathcal{O}(n^2)$ 的，只能拿到 $40\,pts$，接下来考虑优化。

我们可以先将 $a$ 数组升序排序，这样我们就把绝对值去掉了：

$$
\begin{aligned}
ans &= \dfrac{\sum\limits_{i=1}^{n}{a_i + 2\times\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{i-1}{(a_i-a_j)}}}{n}\\
&= \dfrac{\sum\limits_{i=1}^{n}{a_i + 2\times\Big(\sum\limits_{i=1}^{n}{\big(a_i\times(i-1)\big) - \sum\limits_{j=1}^{i-1}{a_j}\Big)}}}{n}
\end{aligned}
$$

这个时候用前缀和优化掉 $j$ 的循环和最前面的求和即可。

最后答案用 $\gcd$ 维护最简分式即可。

时间复杂度为 $\mathcal{O}(n\log n)$（排序 $\mathcal{O}(n\log n)$，查询 $\mathcal{O}(n)$）。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 100005
#define ll long long
using namespace std;
int n; int a[maxn]; ll pre=0,ans=0;
ll gcd(ll xx,ll yy){return (yy==0)?xx:gcd(yy,xx%yy);}
int main(){
	scanf("%d",&n); for(int i=1;i<=n;i++) scanf("%d",&a[i]); sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){ans+=(2*(1LL*(i-1)*a[i]-pre)); pre+=a[i];} ans+=pre;
	ll div=gcd(ans,n); printf("%lld %lld",ans/div,n/div);
	return 0;
}

```

---

## 作者：XL4453 (赞：1)

### 解题思路：

提供一种奇怪的理解方式。

原题目中要求所有的路径的平均长度。发现对于另一个问题：求出每一个点都随机向一个没有走过的点走，求最后走过所有的点的期望走过的距离，这两个问题要求的东西是一样的。

那么就可以用全期望公式来求了，对于每一步都等概率的从其他的所有的点走过来，直接求复杂度是 $O(n^2)$，无法接受。

考虑用前缀和优化一下，复杂度是 $O(n)$ 的，但题目中没有说给出的序列是从小到大的,所以需要排一下序,复杂度是 $O(n \log n)$ 的，可以接受。

----
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long a[100005],n,sum,ans;
long long gcd(long long a,long long b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		ans+=((long long)i-1ll)*(long long)a[i]-sum;
		sum+=a[i];
	}
	ans*=2;
	for(int i=1;i<=n;i++)
	ans+=a[i];
	printf("%lld %lld",ans/(gcd(ans,n)),n/(gcd(ans,n)));
	return 0;
}
```


---

## 作者：liujiaxi123456 (赞：0)

## 关键词：排列组合
### 思路：
平均数，用总和除以方案数，方案数显然为 $n!$，重点在总和。

**贡献：单点贡献，点对贡献。**

解释一下，单点贡献指作为起点时的贡献，比较好计算：
- ${\textstyle \sum_{i=1}^{n}a_i\cdot (n-1)!}$
- 除以方案数后得：$\frac{{\textstyle \sum_{i=1}^{n}a_i}}{n}$。

点对贡献是相邻的两个点的贡献，如下：
- ${\textstyle \sum_{i=1}^{n} {\textstyle \sum_{j=1}^{n}}|a_i-a_j|\cdot (n-1)!}$
- 将 $a$ 排序后即可去掉绝对值。
- 除以方案数后得：$\frac{2\times{\textstyle \sum_{i=1}^{n} {\textstyle \sum_{j=i+1}^{n}}(a_j-a_i)}}{n}$。
- 后缀和即可解决。

最后记得对 $n$ 约一下分。
### 复杂度：
时间：$O(n)$。

空间：$O(n)$。
### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5;

namespace Josh_zmf {
	
	int N; ll a[Maxn], b[Maxn];

	inline int main() {
		cin>> N;
		for(int i=1; i<=N; i++)	cin>> a[i];
		sort(a+1, a+1+N);
		ll sum = 0;
		for(int i=N; i; i--) {
			b[i] = b[i+1] + a[i];
			sum += a[i] + 2*(b[i+1]-a[i]*(N-i));
		}
		ll gcdd = __gcd(sum, 1ll*N);
		cout<< sum/gcdd<< ' '<< N/gcdd;
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走吧。：）

---

## 作者：Pentiment (赞：0)

简单题。

贡献分两部分：一个点作为起点的贡献，和一对点的贡献。

第一部分的贡献为：
$$
\sum_{i=1}^n(n-1)!a_i
$$
第二部分的贡献为：
$$
\sum_{i=1}^n\sum_{j=1}^n(n-1)!|a_i-a_j|
$$
将 $a_i$ 排序即可去掉绝对值。

答案为：
$$
\dfrac{\sum_{i=1}^na_i+2\sum_{i=1}^{n-1}\sum_{j=i+1}^n(a_j-a_i)}{n}
$$
后半部分使用前缀和即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
int n, a[N];
ll sum, p, q, g;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + 1 + n);
	for (int i = n; i >= 1; i--) p += sum - ll(n - i) * a[i], sum += a[i];
	p *= 2, p += sum, q = n;
	g = __gcd(p, q), p /= g, q /= g;
	cout << p << ' ' << q;
}
```

---

## 作者：QWQ_123 (赞：0)

对于每对数字计算贡献。

考虑当前数字 $i$ 与数字 $j$ 的贡献为 $\left| a_i - a_j \right| (n-1)!$，因为就是绑定了 $(i,j)$，然后剩 $(n-1)$ 个数字任意排列。

然后最后的平均数就是 $\frac{(n-1)!(\sum \left| a_i-a_j \right|)}{n!}=\frac{\sum \left| a_i-a_j \right|}{n}$。

然后就是求 $\sum \left| a_i-a_j \right|$，考虑将 $a$ 排序，然后对于 $j\le i$，价值就是 $a_i-a_j$，然后对于 $j\ge i$，价值就是 $a_j-a_i$，然后分别用前缀后缀和维护即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
ll a[100010];
ll sum = 0, s = 0;

ll gcd(ll a, ll b) {
	return !b ? a : gcd(b, a % b);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);

	sort(a + 1, a + 1 + n);

	for (int i = 1; i <= n; ++i) {
		sum += 1ll * i * a[i] - s;
		s += a[i];
	} s = 0;
	for (int i = n; i >= 1; --i) {
		sum += s - (n - i) * a[i];
		s += a[i];
	}

	ll t = n, G = gcd(t, sum);
	t /= G, sum /= G;

	printf("%lld %lld\n", sum, t);

	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

考虑拆分贡献。

首先要选择一个开头点，即排列的第一个元素。每一个元素都可以被选择做为开头点，而选择完一个元素之后就还剩下 $n-1$ 个元素任意排列，选择每一个元素之后，都共计有 $(n-1)!$ 种选取开头点之后的方法。那么也就是说，若选取 $i$ 号点作为开头点，则 $i$ 点作为开头点的贡献就是 $a_i\times (n-1)!$。

然后考虑选择完开头点之后剩下的 $n-1$ 个点得到的贡献。发现在一个排列中只有相邻的两个点之间才会发生新的贡献，所以考虑枚举点对 $(i,j)$ 并计算她的贡献。

容易发现，每一个点对 $(i,j)$ 可以在排列的 $n-1$ 个相邻位置中剩下的 $(n-2)!$ 种排列方案种得到贡献。所以 $(i,j)$ 点对的贡献就是 $|a_i-a_j|\times (n-1)\times (n-2)!=|a_i-a_j|\times (n-1)!$。

也就是说所有的方案加起来得到的贡献就是 $\dfrac{\sum\limits_{i=1}^n \sum\limits_{j=1}^n |a_i-a_j|+\sum\limits_{i=1}^n a_i }{n!}\times (n-1)!=\dfrac{\sum\limits_{i=1}^n \sum\limits_{j=1}^n |a_i-a_j|+\sum\limits_{i=1}^n a_i }{n}=\dfrac{\sum\limits_{i=1}^n a_i}{n}+\dfrac{\sum\limits_{i=1}^n\sum\limits_{j=1}^n |a_i-a_j|}{n}$。

前半部分的处理是容易的，问题在于求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n |a_i-a_j|$ 的值。

发现 $a$ 数组中各个元素的相对位置之间没有直接的对答案的影响，所以考虑将 $a$ 数组从小到大排序，问题转化为求 $2\times \sum\limits_{i=1}^n\sum\limits_{j=1}^{i-1} (a_i-a_j)$ 的值。

其中 $a_i$ 的值在第二个 $\sum$ 中为定值，所以将 $a_i$ 提取出来，原式变为 $\sum\limits_{i=1}^n (i-1)\times a_i-\sum\limits_{i=1}^n \sum\limits_{j=1}^{i-1} a_j$。

发现式子的后半部分的查询为求一段连续区间的和，用前缀和优化即可。

总体的时间复杂度为 $O(n\log n)$，瓶颈在于将 $a$ 数组从小到大排序。但是 $\max a_i\le 10^7$ 所以考虑用桶来优化算法，时间复杂度优化到 $O(n+W)$，其中 $W=\max a_i$。

代码十分好写，但是还是[贴出来](https://www.luogu.com.cn/paste/a110lr63)。

---

## 作者：Fairicle (赞：0)

感觉还是挺需要一点数学能力的...

运动路径可以看成两个部分：第一个部分是从原点到第一个点的长度，第二部分是点和点之间动来动去的长度。记这两部分为$ans1,ans2$。

容易知道对于每个点，它作为第一个点的次数是 $(n-1)!$，那么$ans1=(a_1+a_2+...+a_n)*(n-1)!$

考虑计算 $ans2$，我们发现只需要求出每个区间的贡献和贡献次数即可。则计算从 $i$ 到 $j$ 的长度和出现次数。长度容易得到，为 $|a_i-a_j|$。接下来计算次数：对于其他的 $n-2$ 个点可以随意放置，有 $(n-2)!$ 种情况，$(i,j)$ 的 位置可以从 $(1,2)$ 到 $(n-1,n)$，又有 $n-1$ 种情况，那么 $ans2 = \sum|a_i-a_j|*(n-1)*(n-2)!\ (i!=j)$

$(ans1+ans2)/n!$ 就是最后的答案了。

code：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
#define pb push_back
char p[30]={'0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
inline ll rd(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 100010
int n;
ll a[N];ll ans1,ans2;
ll c[N][2];
inline int lowbit(int x){return x&(-x);}
inline void add(int x,ll v,int op){
	for(ri i=x;i<=n;i+=lowbit(i)) c[i][op]+=v;
}
inline ll sum(int x,int op){
	ll ans=0;
	for(ri i=x;i>0;i-=lowbit(i)) ans+=c[i][op];
	return ans;
}
inline ll get_gcd(ll x,ll y){
	while(y){
		ll tmp=x%y;
		x=y,y=tmp;
	}
	return x;
}
int main()
{
	n=rd();
	for(ri i=1;i<=n;++i) a[i]=rd(),ans1+=a[i];
	sort(a+1,a+1+n);
	for(ri i=1;i<=n;++i){
		add(i,1,0),add(i,a[i],1);
		ans2+=1ll*sum(i,0)*a[i]-sum(i,1);
	}
	ll g=get_gcd(ans1+ans2*2,n);
	ll x=(ans1+ans2*2)/g;n/=g;
	cout<<x<<" "<<n;
    return 0;
}
```


---

