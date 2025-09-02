# Ice Cream Balls

## 题目描述

Tema decided to improve his ice cream making skills. He has already learned how to make ice cream in a cone using exactly two balls.

Before his ice cream obsession, Tema was interested in mathematics. Therefore, he is curious about the minimum number of balls he needs to have in order to make exactly $ n $ different types of ice cream.

There are plenty possible ice cream flavours: $ 1, 2, 3, \dots $ . Tema can make two-balls ice cream with any flavours (probably the same).

Two ice creams are considered different if their sets of ball flavours are different. For example, $ \{1, 2\} = \{2, 1\} $ , but $ \{1, 1\} \neq \{1, 2\} $ .

For example, having the following ice cream balls: $ \{1, 1, 2\} $ , Tema can make only two types of ice cream: $ \{1, 1\} $ and $ \{1, 2\} $ .

Note, that Tema do not need to make all the ice cream cones at the same time. This means that he making ice cream cones independently. Also in order to make a following cone $ \{x, x\} $ for some $ x $ , Tema needs at least $ 2 $ balls of type $ x $ .

Help Tema answer this question. It can be shown that answer always exist.

## 说明/提示

In the first sample, it is enough to have following balls types: $ \{1, 1\} $ . Note, that set $ \{1\} $ if not enough since we need at least $ 2 $ balls of a type $ 1 $ in order to make such cone $ \{1, 1\} $ .

In the second sample, it is not possible to make it with $ 2 $ balls, but it can be done with these balls: $ \{1, 2, 3\} $ .

In the third sample, $ \{1, 2, 3, 4\} $ is optimal answer, so we can get following ice cream cones: $ \{1, 2\} $ , $ \{1, 3\} $ , $ \{1, 4\} $ , $ \{2, 3\} $ , $ \{2, 4\} $ , $ \{3, 4\} $ .

## 样例 #1

### 输入

```
5
1
3
6
179
1000000000000000000```

### 输出

```
2
3
4
27
2648956421```

# 题解

## 作者：sunkuangzheng (赞：9)

**【题目分析】**

考虑贪心。我们先通过 $x$ 个不相同的冰激淋球制造出 $\dfrac{x(x-1)}{2}$ 种口味的冰激凌，剩下的几种用相同的冰激凌制作。例如，当 $n=8$ 时，我们的构造方案是 $1\;1\;2\;2\;3\;4$。

第一步是一个解一元二次方程，套求根公式得 $x = \dfrac{1+\sqrt{8n+1}}{2}$（舍去负解）。然后我们令 $y = \lfloor x \rfloor,k = \dfrac{y(y-1)}{2}$，那么 $k$ 就是当前我们已经有了的冰激凌种类。于是还需要 $n-k$ 个相同的冰激凌球，即答案为 $y+n-k$。

**【代码】**

核心代码只有一行。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,x;
signed main(){
    for(cin >> t;t -- && cin >> n;cout <<k + n - x<<"\n")k=(1+sqrt(8*n+1))/2,x = k*(k-1)/2;
}
```

---

## 作者：Shadow_T (赞：5)

首先，不难发现 $k$ 个**不同的冰淇淋球**可以做 $k(k-1)\div2$。

首先先二分找出满足方案小于等于 $n$ 且最大的 $k$；然后对于后面剩下的部分，就把原先的数在加一遍即可，即加上 $n-k(k-1)\div2$ 即可，时间复杂度为对数级。

十年 OI 一场空，开了 long long 见祖宗！

```cpp
#include<bits/stdc++.h>
using namespace std;
void read(__int128 &a)
{
	a=0;
	char c=getchar();
	while(c<'0'||c>'9')
	c=getchar();
	while(c>='0'&&c<='9')
	{
		a=a*10+(c-'0');
		c=getchar();
	}
}
void print(__int128 x)
{
	if(x<0)
	{
	  putchar('-'); 
	  x=-x;
	}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
void solve()
{
	__int128 n;
	read(n);
	__int128 l=1,r=1e11,mid;
	while(l<r)
	{
		mid=(l+r+1)/2;
		if(mid*(mid-1)/2>n) r=mid-1;
		else l=mid;
	}
	print(l+(n-(l-1)*l/2));
	cout<<"\n";
}
signed main()
{
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：ax_by_c (赞：4)

# 题意描述

这题的题意卡了我半个小时，所以来讲一下。

就是一个人有一个数列，然后他可以选择数列中的两个元素构成一个二元组。

现在问你要构成 $n$ 个**不同的二元组**，原先的数列中至少需要多少元素？

# 解题思路

因为数是可以重复的，所以加入一个新的数有 $2$ 种贡献。

1. 该数曾经出现过

再加入一个相同的数，因为原先已经有这个数了，所以和其他数的二元组都已经出现过了，那么就只能和原先的数构成一个二元组了，贡献为 $1$。

如果该元素已经出现过至少 $2$ 次，则和原先的数构成的二元组已经出现过了，则没有贡献。
2. 该数没有出现过

那么贡献就是当前数列中的元素个数 （当前数还未被加入）。

得出结论：

1.  一个数至多出现 $2$ 次

2.  选新数的贡献更大。

那么就不难想到二分了。

先二分一个最大的数列元素数量，其中元素互不相同，且总贡献不超过 $n$。

然后可能还差一些贡献，那么此时不能加新数了，所以就把每个原先的数再加一遍即可。

Q : 这样加，不会把一个数加上 $3$ 遍吗？

A : 因为如果加了 $3$ 遍，则所有数都被加了至少一遍，那么其实就和二分过程时的加一是一样的。显而易见，二分时加一更优。

核心代码：

```cpp
cin>>n;
int res=0;
int l=0,r=2648956421;
while(l<=r)
{
	int mid=l+((r-l)>>1);
	if((mid*(mid-1)/2)<=n)
	{
		if(mid>res)
		{
			res=mid;
		}
		l=mid+1;
	}
	else
	{
		r=mid-1;
	}
}
res+=n-(res*(res-1)/2);
cout<<res<<'\n';
```

---

## 作者：MrPython (赞：1)

先考虑如果每个冰淇淋球不相同时的情况数。设有 $m$ 种不同的冰淇淋球，显然有：方案数 $n=\frac{m\left(m-1\right)}{2}$。

现在已知 $n$，直接求解这个关于 $m$ 的方程的正数解，即 $m=\frac{\sqrt{8n+1}+1}{2}$。

但是在大部分情况下，这个式子并不能得到一个正整数解。也就是说，冰激凌球会有重复的。想一想如何知道要有几个重复的呢？

看一下这个例子：$\left\{1,1,2,3,4\right\}$。他能做出几种不同的冰淇淋？  
这里有 $2$ 个 $1$，不管选用哪个都是一样的。我们先将它们看为 $1$ 个，这样就变成了 $4$ 个互不相同的冰淇淋球，有 $\frac{4\times\left(4-1\right)}{2}=6$ 种。但是初始时的 $2$ 个 $1$ 也可以做成一种冰淇淋，因此总的方案数还要 $+1$，即 $7$ 种。

从上述过程能看出来，有几组重复的冰淇淋球，方案数 $n$ 就会多几。

我们在上面讨论的只有 $2$ 个相同的冰淇淋球，那么可能会出现 $3$ 个或更多相同的冰淇淋球吗？  
如果有 $3$ 个相同的冰淇凌球，答案的贡献仍然只会 $+1$，但是却浪费了一个冰淇凌球！这与题目要求的最小化 $m$ 不符合，因此不会出现 $3$ 个或更多的重复冰淇凌球。

由此我们就可以尝试推导通式了。先根据 $n$ 求方程 $n=\frac{m\left(m-1\right)}{2}$ 的正数解，即 $m=\frac{\sqrt{8n+1}+1}{2}$。设 $k=\left\lfloor m\right\rfloor$。当 $k$ 个冰淇凌球互不相同时，总共的方案数为 $\frac{k\left(k-1\right)}{2}$，但是这可能不足 $n$，我们需要相同的冰淇凌球来补全剩下的。每多一组相同的冰淇凌球方案数会 $+1$，我们只需要再变出 $n-\frac{k\left(k-1\right)}{2}$ 个与前面有重复的冰淇淋球即可让最终的方案数等于 $n$。这些冰淇凌球贡献出了 $n-\frac{k\left(k-1\right)}{2}$ 种方案，早已构造出的方案数为 $k$，则最终答案为 $k+\left[n-\frac{k\left(k-1\right)}{2}\right]$。

稍微有些混乱，设输入为 $n$，这是最后的结论：
$$
\begin{matrix}
k=\left\lfloor \frac{\sqrt{8n+1}+1}{2}\right\rfloor,
\\
ans=k+\left[n-\frac{k\left(k-1\right)}{2}\right]
\end{matrix}
$$ 
结论题应该就不用给代码了吧……

最后注意精度，建议 `long double`，就可以愉快通过了。

---

## 作者：sjr3065335594 (赞：1)

## 题意简述

选出若干个可以重复的数，给定一个数量，要求用这些数正好能组成这个数量的二元组，求最少需要几个数。

## 思路

我们可以发现几个性质：

1. 一个数最多有两个，如果再多选一个不会对答案有贡献，不会更优。
2. 尽量多选不同的数，这样可以使总的情况数最多。

好了到这里我们就可以开始贪心，找到一个最大的 $k$，满足 $\dfrac{k\times (k-1)}{2}\le n$，这就是先选 $k$ 个不同的数的情况数量，必须要小于等于 $n$，否则就不满足题意了。此时对于它小于 $n$ 的部分，我们每选一个相同的数，会使总的情况数加一，所以最终的答案就是 $k+n-\dfrac{k\times (k-1)}{2}$。

为了防止精度和平方数的问题，我还加了个循环。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mkp(x,y) make_pair(x,y)
using namespace std;
int t;
ll n;
int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%lld",&n);
		ll x=sqrt(2*n),res,sqr;//这里开n*2就可以把除以二去掉
		for(ll i=max(1ll,x-10);i<=x+10;i++) {
			if(i*(i-1)/2>n) {
				sqr=i-1;
				break;
			}
		}
		res=(sqr*(sqr-1))/2;
		printf("%lld\n",sqr+n-res);
	}
	return 0;
}



```


---

## 作者：2huk (赞：1)

[CF1862D](https://www.luogu.com.cn/problem/CF1862D)

## Descrition

你需要构造一个集合 $s$，使得其所有大小为 $2$ 的不同的子集数为 $n$。求最小的集合大小。

例如，集合 $\{1, 1, 2\}$ 有 $2$ 个大小为 $2$ 的不同的子集：$\{1, 1\}$，$\{1, 2\}$。

## Solution

首先一个比较显然的结论是，最终构造出来的集合中相同元素不可能有 $3$ 个及以上。比如对于集合 $\{1, 1, 1, 2\}$，它与 $\{1, 1, 2\}$ 的贡献是相同的，但却比它多了一个元素，是不优的。因此一个元素在集合中只能出现 $1$ 次或 $2$ 次。

换个角度思考问题，假如我们知道了集合中的元素**种类数**（也即，不同的元素的数量），那么这个集合能否成为答案呢？

设集合种类数为 $m$，其中出现了 $2$ 次的元素数量为 $x$，显然首先需要保证 $x \ge 0$，其次我们需要计算这个集合中包含几个大小为 $2$ 的不同子集。

- 对于两个**不同**的种类，是可以任意搭配的，也就是说方案数为 $\dbinom m2$；
- 对于两个**相同**的种类，首先这个种类的出现次数为 $2$。对于每一个出现次数为 $2$ 的种类，都可以将其子集搭配，构成新的子集，也就是说方案数为 $x$。

所以这样的集合包含 $\dbinom m2 + x$ 个大小为 $2$ 的子集。也就是说我们需要保证 $\dbinom m2 + x = n$。

在实现上，我们并不需要真正的把 $x$ 进行枚举，只需要求出是否存在一个合法的 $x$，也就是计算 $n - \dbinom m2$ 的值是否合法。这里的「是否合法」指的就是上面说的 $x \ge 0$，即 $n - \dbinom m2  \ge 0$。

容易发现，$m$ 值是具有单调性的。因此二分即可。

## Code

注意 `__int128`。

```cpp
#define int __int128

int T, n;

int Solve()
{
	n = read();

	int l = 1, r = n, res = -1;

	while (l <= r)		// 二分元素种类
	{
		int mid = l + r >> 1;
		int k = mid * (mid - 1) / 2;		// k = C(mid, 2)
		int x = n - k;			// 出现了 2 次的元素数量，同上面的分析

		if (x >= 0)
		{
			res = mid + x;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}

	return res;
}
```



---

## 作者：saixingzhe (赞：1)

# 分析
介绍两种方法：

1.可以直接二分，我们发现，选择 $n$ 个球有最少有 $\frac{n\times(n-1)}{2}$ 种方法，最多有 $\frac{n\times(n-1)}{2}+n$ 种。

所以我们二分 $m$ 使得 $\frac{n\times(n-1)}{2} \leq m \leq \frac{n\times(n-1)}{2}+n$ 即可。

2.可以解一个一元二次方程，我们先用 $x$ 个不同的冰淇淋球制造出 $\frac{x\times(x-1)}{2}$ 种冰淇淋，所以 $x$ 就等于 $\lfloor\frac{1+\sqrt{8n+1}}{2}\rfloor$，答案就等于用 $x$ 加上剩下用相同冰淇淋球补的 $n-\frac{x\times(x-1)}{2}$ 个。

---

## 作者：Rain_javalearner (赞：1)

题目要求 `Exactly`，表示恰好 $n$ 个。不难发现“性价比”最高的是形如 $1,2,\dots ,k-1,k$ 的格式，这样 $k$ 个 `Ice Cream Balls` 就可以搞出 $\frac{k(k+1)}{2}$ 种双球，我们用这种方式**接近** $n$。

这样还有 $n-\frac{k(k+1)}{2}$ 种双球需要我们去创造，有两种选择：

- 添加一个 $c \notin [1,k]$，产生 $k$ 种双球，结果会大于 $n$，不可取；
- 添加一个 $c \in [1,k]$，产生 $1$ 种双球，可以一个一个接近 $n$，因为 $n-\frac{k(k+1)}{2} \le k$，可取。

所以找出最接近的 $k$，答案就是 $k+(n-\frac{k(k+1)}{2})$。二分答案即可。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
typedef __int128 i128;
typedef long long i64;
 
int t;
i64 n;
 
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &n);
		i128 l = 1, r = 2648956420;
		i128 ans = 0;
		while(l <= r) {
			i128 mid = (l+r) >> 1;
			if(mid*(mid+1)/2 <= n)l = mid+1, ans = mid;
			else r = mid-1;
		}
		printf("%lld\n", (i64)ans+1ll+(i64)(n-ans*(ans+1)/2));
	}
}
```




---

## 作者：Wf_yjqd (赞：1)

比较简单的数学题。

------------

考虑共买 $m$ 种尺寸的球，那最少也有 $\frac{m\times(m-1)}{2}$ 种方案。

如果一种球买不止一个，则会多贡献 $1$ 种方案。

所以最多有 $\frac{m\times(m-1)}{2}+m$ 种方案。

二分出 $m$ 满足 $\frac{m\times(m-1)}{2}\le n\le\frac{m\times(m-1)}{2}+m$ 即可。

复杂度 $\operatorname{O}(\log n)$。

------------

没啥好说的。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,l,r,mid,ans,anss;
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        l=0;
        r=2e9;
        while(l<=r){
            mid=l+r>>1;
            if(mid*(mid-1)/2+mid<=n){
                l=mid+1;
                ans=mid;
            }
            else
                r=mid-1;
        }
        anss=0x3f3f3f3f3f3f3f3f;
        if(ans*(ans-1)/2+ans>=n)
            anss=min(anss,ans+n-ans*(ans-1)/2);
        if(ans*(ans+1)/2<=n&&ans*(ans+1)/2+ans+1>=n)
            anss=min(anss,ans+1+n-ans*(ans+1)/2);
        printf("%lld\n",anss);
    }
    return 0;
}
//哀太可爱辣
```


---

## 作者：liangjindong0504 (赞：0)

**【题目大意】**

有一个集合，它有**恰好** $n$ 个不重复的元素个数为 $2$ 的子集。给出 $n$，求出这个集合元素最小个数。

**【主要思路】**

~~CF 真喜欢靠玄学思维题啊。~~

首先，我们考虑两种情况：

首先，假设此集合中的元素各不相同，若集合长度为 $m$，那么不重复的元素个数为 $2$ 的子集就是 $C_{m}^{2}$，即为 $\frac{m \cdot (m-1)}{2}$。对于这种情况，我们考虑用二分查找的方法解决（找到与 $n$ 最接近的 $m$）。

这时候，考虑再加一个之前已经有过的元素，如果该元素是第二次出现，那么它对答案的贡献是 $1$，即为两个该元素。若该元素出现次数超过 $2$，则无法贡献（只能是两个元素）。

**【实现】**

第一步：找到一个 $m$，使得 $\frac{m \cdot (m-1)}{2}$ 最接近 $n$。注意：$\frac{m \cdot (m-1)}{2}$ 必须小于或等于 $n$，这里使用二分查找的方法解决。
```cpp
while(l<=r){
	mid=l+(r-l)/2;
	if(mid*(mid-1)/2<=n){
		l=mid+1;
		ans=mid;
	}else{
		r=mid-1;
	}
}
```
第二部，就是计算答案了。因为每次增加的必须是以前有的（不然答案肯定比 $n$ 大），所以每增加一个元素只会使最终结果增加 $1$，这样，答案即为 ```ans+n-ans*(ans-1)/2```。

**【结尾】**

CF 喜欢考玄学数学，做题时一定不能急于给出结论（对于我这种蒟蒻）。本题并不是很难，个人觉得难度介于橙到黄之间。

---

## 作者：qiuzijin2026 (赞：0)

# Ice Cream Balls

## [洛谷题面](https://www.luogu.com.cn/problem/CF1862D)

## [原题题面](https://codeforces.com/contest/1862/problem/D)

## 思路

一道数学题。

优先考虑用 $x$ 个球组成双球，用二分找到最大的 $x$ 使得 $x\times (x+1)<=n$。

剩下的 $n-x\times (x+1)$ 种我们就用两颗相同的球组。

总的球数就是 $x+n-x\times (x+1)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t; 
long long n;
long long l,r,m;
long long tmp;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&t); 
	while(t--){
		scanf("%lld",&n);
		l=1;
		r=INT_MAX;
		while(l<=r){
			m=(l+r)>>1;
			if(m*(m+1)/2>n) r=m-1;
			else{
				l=m+1;
				tmp=m;
			} 
		}
		printf("%lld\n",tmp+n-(tmp+1)*tmp/2);
	}
	return 0;
}
```

---

## 作者：tbdsh (赞：0)

# 题意简述
[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1862d)

[洛谷原题](/problem/cf1862d)

[CodeForces 原题](https://codeforces.com/contest/1862/problem/D)

有 $t$ 组数据。每组数据给定 $n(1\le n\le 10^{18})$。

你可以使用任意两个数字组成一个二元组。

两个二元组被认为是不同的，那么这两个二元组中的元素在经过调换顺序后不同。例如，$\{1,2\}=\{2,1\},\{1,1\}\ne\{1,2\}$。

现在请你求出至少要**多少个数字**才能**刚好**得到 $n$ 个不同的二元组。

保证答案一定存在。

# 分析
因为要让答案最小，所以我们考虑二分选择的数字数量。

容易发现，如果我们选择了 $x$ 个不同的数字，那么我们可以得到 $x\times (x-1)\div 2$ 个不同的二元组。

那么我们就可以二分找到一个 $x$ 使得 $x\times (x-1)\div 2$ 最接近 $n$。

但是，我们可能还差一些才能得到答案。

如果我们选择 $y(y\le x)$ 个已经选过的数字，那么二元组的数量就会增加 $y$。

所以，我们只需要二分出 $x$，最后输出 $x + n - x\times (x-1) \div 2$ 即可。

但注意，$x\times (x-1)\div 2$ 是会炸 `int` 的。所以要开 `long long`。~~但我很懒直接用 `__int128`。~~

时间复杂度：$O(\log_2 n)$。

空间复杂度：$O(1)$。

# Code
```cpp
#include<bits/stdc++.h>
#define int __int128

using namespace std;
const int MAXN = 2e5 + 5;
int read(){
  int cnt = 0;
  string s;
  cin >> s;
  for (int i = 0; i < s.size(); i++){
    cnt = cnt * 10 + s[i] - '0';
  }
  return cnt;
}
void print(int x){
  if (x < 10){
    signed p = x;
    cout << p;
    return ;
  } 
  print(x / 10);
  signed p = x % 10;
  cout << p;
}
void Solve(){
  int n;
  n = read();
  int l = 0, r = 1e10, cnt = 2e18, p;
  while (l < r){
    int mid = (l + r) >> 1;
    if (mid * (mid - 1) / 2 <= n && n - mid * (mid - 1) / 2 <= cnt){
      cnt = n - mid * (mid - 1) / 2;
      p = mid;
    }
    if (mid * (mid - 1) / 2 < n){
      l = mid + 1;
    }else {
      r = mid;
    }
  }
  if (l * (l - 1) / 2 <= n && n - l * (l - 1) / 2 <= cnt){
    cnt = n - l * (l - 1) / 2;
    p = l;
  }
  print(p + cnt);
  cout << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  t = read();
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：Kedit2007 (赞：0)

### 简要题意

构造一个序列，使从中任选两个数**恰巧**能构成 $n$ 种不同的集合，求序列最短长度。

### 思路

首先有一个简单的结论，当序列中**有且仅有** $a$ 个元素时，能够构成的不同的集合数为 $\sum^{a - 1}_{i = 1}i = \frac{a(a-1)}{2}$。这里给出一个简单的证明：假设当序列中有且仅有 $i$ 个元素时能够构成的不同集合数为 $m_i$，则当有且仅有 $i + 1$ 个元素，即新加入一个元素时，新加入的元素可以和先前的每一个元素都构成一个集合，故 $m_{i + 1} = m_i + i$；又有 $m_1 = 0$，二者结合即可推出上式。

但是题目要求**恰巧**能构成 $n$ 种，那么我们不妨先解决**最多**能构成 $n$ 种集合的最短**无重复元素**序列的长度。方法比较多，可以考虑二分。将这个问题的结果记为 $k$。

接下来考虑增加一个序列中有且仅有一个的数 $i$，对于任意一个序列中不等于 $i$ 的数 $j$，集合 $\{i, j\}$ 一定已经在之前被计算过，只会新增一个集合 ${i, i}$。所以在这种情况下，只能构成 $1$ 个新的集合。

于是，我们只需要再增加 $n - k$ 个不同的，且已经构造出来的序列中存在的数即可解决问题。

### 参考代码

```cpp
void work()
{
	int n;
	cin >> n;
	int l = 1, r = n + 3, ans;
	while (l <= r)
	{
		int mid = l + (r - l) / 2;
		if (n * 2 / mid <= mid - 1)
		{
			if (n * 2 / mid == mid - 1)
			{
				ans = mid;
				break;
			}
			r = mid - 1;
		}
		else
		{
			ans = mid;
			l = mid + 1; 
		}
	}
	ans += n - (ans * (ans - 1) / 2);
	cout << ans << endl;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

容易发现如果长度为 $x$ 的序列 $a$ 中每个数都不一样，那么无论数是什么，方案数总是一样，这种情况下方案数是 $\frac{x\times (x-1)}2$。

我们再对序列 $a$ 添加一些已经存在的数，如果添加了一个 $k$，则会方案数会加 $1$，也就是多了一个 $\{k,k\}$ 的方案，而且其他的方案是存在的，如果再添加一个 $k$ 则方案数不会增加，所以添加两个及以上的相同数字是无意义的。

所以我们可以通过添加一些已经存在且不同的数来使答案增加，最多可以新添加 $x$ 个数，也就是总方案数为 $\frac{x\times (x-1)}2+1 \sim \frac{x\times (x-1)}2 +x=\frac{x\times (x-1)+2\times x}2=\frac{x\times (x+1)}2$ 之间的数都可以，而 $\frac{x\times (x+1)}2$ 还可以用长度为 $x+1$ 的每个数都不同的序列得到，再大一点的方案数就又可以在长度为 $x+1$ 的新序列加若干个已存在的不同的数得到。

所以对于每个 $n$ 都存在答案。

那么，我们再来思考如何得到答案。

对于 $n=\frac{x\times (x-1)}2$ 的情况，答案为 $x$。

考虑如何得到 $x$。

首先不考虑 $n$ 是完全平方数的情况，则有 $\lfloor \sqrt n \rfloor^2 < n < \lceil \sqrt n \rceil ^2$，且 $\lfloor \sqrt n \rfloor +1 = \lceil \sqrt n \rceil$。

令 $s=\lfloor \sqrt n \rfloor$，如果 $n=s\times(s+1)$ 那么答案就是 $s+1$。

否则，我们需要找到小于 $n$ 形如 $x=t\times (t+1)$ 中最大的 $x$。

我们可以用 $t+1$ 个不同的数再多加 $n-x$ 个已存在不同的数达成方案数为 $n$ 的情况，答案就是 $t+1+n-x$。

再考虑 $n$ 为完全平方数的情况，则 $n$ 一定不能通过若干个不同的数构成的序列达到，那么也是第二种情况，解法也与第二种一样。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%lld",&n);
		long long s=sqrt(1llu*n*2);
		if(s*(s+1)/2==n) printf("%lld\n",s+1);
		else
			for(long long j=s-3;;++j)
				if(j*(j+1)/2>n)//找到最小的x
				{
					printf("%lld\n",j+(n-(j-1)*j/2));break;//注意：此时的x=j*(j-1)/2，所以答案是j+(n-x)不要搞错了。
				}
	}
}
```

---

