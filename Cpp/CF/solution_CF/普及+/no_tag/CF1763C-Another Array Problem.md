# Another Array Problem

## 题目描述

You are given an array $ a $ of $ n $ integers. You are allowed to perform the following operation on it as many times as you want (0 or more times):

- Choose $ 2 $ indices $ i $ , $ j $ where $ 1 \le i < j \le n $ and replace $ a_k $ for all $ i \leq k \leq j $ with $ |a_i - a_j| $

Print the maximum sum of all the elements of the final array that you can obtain in such a way.

## 说明/提示

In the first test case, it is not possible to achieve a sum $ > 3 $ by using these operations, therefore the maximum sum is $ 3 $ .

In the second test case, it can be shown that the maximum sum achievable is $ 16 $ . By using operation $ (1,2) $ we transform the array from $ [9,1] $ into $ [8,8] $ , thus the sum of the final array is $ 16 $ .

In the third test case, it can be shown that it is not possible to achieve a sum $ > 18 $ by using these operations, therefore the maximum sum is $ 18 $ .

## 样例 #1

### 输入

```
3
3
1 1 1
2
9 1
3
4 9 5```

### 输出

```
3
16
18```

# 题解

## 作者：tZEROちゃん (赞：7)

分类讨论和简单思维。

显然，为了使和最大化，我需要使的所有元素都等于序列中的最大元素。

无论给定的数组是怎样的，都可以通过使最后两个元素 $(n-1,n)$ 进行两次操作，使他变成 $0$，然后对 $[m,n]$ 进行运算，使其所有元素等于 $mx$。

然后再让前两个元素 $(1,2)$ 为零，再对整个数组操作，使所有元素都等于 $mx$。因此，最终数组的最大和总是 $n\cdot mx$（当 $m$ 恰好等于 $n-1$ 或 $n$，也是同理的，可以先从左边开始操作。

考虑 $n\le 3$ 的情况。

$n=2$ 时，要么操作让所有元素都变成 $|a_1-a_2|$，要么就啥都不干保持 $a_1,a_2$，答案就是 $\max(a_1+a_2,2\cdot|a_1-a_2|)$。

$n=3$ 时，当最大元素是 $a_1$ 或 $a_3$，我们还是可以将所有元素都变成最大，当最大元素是 $a_2$ 时，有以下几种情况：

1. 选择 $(1,2)$ 操作，此时每个数的最大值为 $\max(a_3,|a_1-a_2|)$。
2. 选择 $(2,3)$ 操作，此时每个数的最大值为 $\max(a_1,|a_3-a_2|)$。
3. 选择 $(1,3)$ 操作，所有元素变成 $|a_3-a_1|$，显然不需要这个，因为我们的讨论是在 $a_2>a_1,a_3$ 之上的，而 $a_2 - \min(a_1,a_3) > \max(a_1, a_3) - \min(a_1, a_3)$。


考虑情况 $1$ 和情况 $2$，如果操作完和还变小了，那操作就没用，干脆就别操作了。

所以 $n=3$ 时答案是 $\max(3\cdot a_1, 3\cdot a_3, 3\cdot |a_2-a_1|, 3\cdot |a_3-a_2|, a_1+a_2+a_3)$。


核心代码（完整代码见 [此](https://www.luogu.com.cn/paste/d76i3xcu)）：

```cpp
void solve() {
   int n; cin >> n;
   rep (i, 1, n) cin >> a[i];
   if (n == 1) printf("%d\n", a[1]);
   else if (n == 2) {
      printf("%lld\n", max(2 * abs(a[1] - a[2]), a[1] + a[2]));
   } else if (n == 3) {
      printf("%lld\n", max({3 * abs(a[1] - a[2]), 3 * abs(a[3] - a[2]), 3 * a[1], 3 * a[3], a[1] + a[2] + a[3]}));
   } else { sort(a + 1, a + n + 1);
      printf("%lld\n", a[n] * n);
   }
}
```

---

## 作者：CSP_Sept (赞：2)

复健，复健。复健！

## 描述

给定长度为 $n$ 的数列，进行任意次操作：

- 选定 $1\le i<j\le n$，对于 $\forall k\in[i,j]$，进行 $a_k\gets |a_i-a_j|$。

最终得到数列 $b$，求 $\sum_{i=1}^nb_i$ 的最大值。

多测，$1\le n\le 2\times 10^5$，$1\le a_i\le 10^9$。

## 解答

研究 $n=2$，显然答案为 $\max\{a_1+a_2,2\cdot|a_1-a_2|\}$。

记操作 $i=i_0,j=j_0$ 为 $(i,j)$。继续研究 $n=3$：

- 进行 $(1,2)$，得到 $[|a_1-a_2|,|a_1-a_2|,a_3]$。
- 接下来有两种方案：
   1. - 进行 $(1,2)$，得到 $[0,0,a_3]$。
      - 进行 $(1,3)$，得到 $[a_3,a_3,a_3]$。
   2. - 进行 $(2,3)$，得到 $[|a_1-a_2|,\left||a_1-a_2|-a_3\right|,\left||a_1-a_2|-a_3\right|]$。
      - 进行 $(2,3)$，得到 $[|a_1-a_2|,0,0]$。
      - 进行 $(1,3)$，得到 $[|a_1-a_2|,|a_1-a_2|,|a_1-a_2|]$。

综上，我们能得到的和有 $3\cdot |a_1-a_2|,3\cdot a_3$。

同理，我们能得到的和还有 $3\cdot |a_3-a_2|,3\cdot a_1$。

于是答案为 $\max\{a_1+a_2+a_3,3\cdot a_1,3\cdot a_3,3\cdot |a_1-a_2|,3\cdot |a_3-a_2|\}$。

接着考虑 $n\ge 4$。

通过上面的讨论我们发现，对于操作过程中序列中出现的数 $x$，可以通过某种方式，让序列全都变成 $x$。

那么答案显然是

$$\max\left\{\sum_{i=1}^na_i,n\cdot\max_{i=1}^n\{a_i\}\right\}$$

然而我懒得分讨，对于每个 $1\le i\le n-2$ 计算 $v_i=\text{Ans}([a_i,a_{i+1},a_{i+2}])$，把情况退化成 $n=3$。答案就是

$$
\max\left\{\sum_{i=1}^na_i,n\cdot\max_{i=1}^{n-2}\{v_i\}\right\}
$$

请亮出你的代码 /xk

## 代码

_[186097699](https://codeforces.com/contest/1763/submission/186097699)_

---

## 作者：qiuzijin2026 (赞：1)

# Another Array Problem

## [题面](https://www.luogu.com.cn/problem/CF1763C)

## 思路

这道题分类讨论。

我们发现如果 $n\ge 4$，设 $\max\{a_i\}$ 的位置是 $x$。

那么必有 $x-1\ge 2$ 或 $n-x\ge 2$ 成立。

我们对区间 $[1,x-1]$ 进行两次操作后，
区间 $[1,x-1]$ 就全变成了 $0$。
我们再对区间 $[1,x]$ 做一次操作，
区间 $[1,x]$ 就全变成了 $\max\{a_{i}\}$。

区间 $[x,n]$ 同理，所以说所有元素的最大和就是 $n \times \max\{a_i\}$。

我们再了讨论其他情况：

- $n=2$ 时，

这种情况下要么不操作，要么只操作一次，答案就是 $\max(a_{1} + a_{2},2 \times \mid a_{1} - a_{2}\mid)$。

- $n=3$ 时，
	
当最大元素是 $a_{1}$ 或 $a_{3}$ 时我们还可以把他们都变成最大，当最大元素是 $a_{2}$ 时则分情况讨论。

所以说 $n=3$ 时答案为 $\max(3 \times a_{1},3 \times a_{3}
,3 \times \mid a_{2} - a_{1} \mid,3 \times \mid a_{3} - a_{2} \mid,a_{1}+a_{2}+a_{3})$。

按情况分类做即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n;
long long a[200005];
long long maxx;
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		maxx=0;
		for(long long i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			maxx=max(a[i],maxx);
		}
		if(n>=4) printf("%lld\n",maxx*n);
		else if(n==3)  printf("%lld\n",max(max(3*abs(a[1]-a[2]),3*abs(a[3]-a[2])),max(max(3*a[1],3*a[3]),a[1]+a[2]+a[3])));
		else if(n==2) printf("%lld\n",max(2*abs(a[1]-a[2]),a[1]+a[2]));
		else if(n==1) printf("%lld\n",a[1]);;
	}
	return 0;
}
```

---

## 作者：lilong (赞：1)

Update on 2023.8.17：修正了一处小错误。

分析题目可知，答案至少为 $\sum_{i=1}^{n} a_i$。接下来考虑怎样使答案更大。

可以对 $n$ 分成如下几类情况讨论：

- $n=2$

这种情况十分简单，如果选择操作最多一次，否则两次就会变为 $0$。用 $ \left| a_1 - a_2 \right | \times 2$ 判断是否能更新答案即可。

- $n=3$

这种情况较为复杂，再细分成几种情况：

1. $a_1$ 为最大值。此时对区间 $[2,3]$ 进行两次操作，将其全部变为 $0$，再对区间 $[1,3]$ 进行一次操作，即可将整个序列都变为 $a_1$。用 $a_1 \times n$ 判断是否能更新答案即可。

2. $a_3$ 为最大值。与情况 $1$ 同理。

3. $a_2$ 为最大值。选择 $[1,2]$ 或 $[2,3]$ 区间进行一次操作，再选择 $[1,3]$ 区间进行一次操作，对每次操作后的序列都求和并判断是否能更新答案。

- $n>3$

易证，经过若干次操作后，答案最大能更新为 $ \max \{a\} \times n$，读者如果感兴趣可以模拟序列 $[1,2,3,2]$ 的变换过程，体会其原理。

上代码，具体实现详见下面。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

int n,a[1000001],ans,mx;

signed main()
{
	int T;
	cin >> T;
	while( T -- )
	{
		ans = 0;
		mx = 0;
		cin >> n;
		for( int i = 1 ; i <= n ; i ++ )
		{
			cin >> a[i];
			ans += a[i];
			mx = max( mx , a[i] );
		}
		if( n == 2 ) cout << max( ans , abs( a[1] - a[2] ) * 2 ) << endl;
		if( n == 3 ) cout << max( ans , max( max( a[1] * 3 , a[3] * 3 ) , max( max( abs( a[1] - a[2] ) * 2 + a[3] , abs( a[3] - a[2] ) * 2 + a[1] ) , max( abs( a[1] - a[2] ) * 3 , abs( a[3] - a[2] ) * 3 )) ) ) << endl; 
		if( n > 3 ) cout << max( ans , mx * n ) << endl;
	}
	return 0;
}
```


---

## 作者：baoziwu2 (赞：1)

当 $n≤3$ 时，直接分类讨论：

$$
ans = \begin{cases}
a_1 & n = 1 \\
\max(a_1+a_2,2|a_1-a_2|) &n = 2\\
\max (3a_1,3a_2,3|a_1-a_2|,3|a_2-a_3|,\sum a_i)&n=3
\end{cases}
$$

当 $n≥4$ 时，我们有结论为答案一定是 $n \times \max\{a_i\}$。

尝试证明一下：

首先所有 $a_i$ 都是正数，也就是说 $|a_{\max} - a_i| ≤ a_{\max}$ 一定成立，即答案一定不会大于 $n \times \max\{a_i\}$。

令最大的元素 $a_{\max}$ 的位置为 $p$，那么 $p - 1 ≥ 2,n - p ≥ 2$ 至少有一个成立，否则 $n$ 不能满足 $n≥4$ 的条件。

为了方便，下文将 $a_1$ 或 $a_n$ 称为数组边界 $a_{side}$，将 $a_{p - 1}$ 或 $a_{p+1}$(如果存在)称为 $a_{\max}$ 的邻接项 $a_{adjacent}$。

选择 $p$ 距离数组边界大于 $2$ 的一个方向，用 $3$ 次操作将 $a_{\max}$ 到 $a_{side}$ 的值全部变为 $a_{\max}$:

1. 执行操作 $(adjacent, side)$(这里的区间不包含 $a_{p}$)，此时操作后的区间变为 $|a_{adjacent}- a_{side}|$。
2. 再执行一次，操作后区间全变为 $0$。
3. 执行操作 $(p, side)$ 操作后的区间全为 $a_{\max}$。

然后对另一边执行操作 $(side_{ano}, p)$ 执行两次后再执行一次操作 $(1, n)$ 即可使得所有序列值为 $a_{\max}$，按照上面的步骤一定可以实现。

综上，我们证明了答案既不会大于 $n \times \max\{a_i\}$，也不会小于 $n \times \max\{a_i\}$，即 $ans = n \times \max\{a_i\}$，证明完毕。

复杂度为 $O(\sum n)$。

代码（贪图简单就用 python 实现了）：

```Python
T = int(input())
for _ in range(T):
	n = int(input())
	a = list(map(int, input().split()))
	if(n == 1): print(a[0]);
	elif(n == 2): print(max(2 * abs(a[0] - a[1]), a[0] + a[1]))
	elif(n == 3): print(max(3 * abs(a[0] - a[1]), 3 * abs(a[2] - a[1]), 3 * a[0], 3 * a[2], a[0] + a[1] + a[2]))
	else: print(max(a) * n)
	

```

---

## 作者：Priestess_SLG (赞：0)

第一眼感觉这题一脸厉害，然后打表之后发现 $n\ge 4$ 是简单的？？？

考虑 $n\ge 4$，则最前面两个元素和最后面两个元素之中必然有一个不包含全部的最大值，则对这个区间做两次操作让她们全都变为 $0$，然后加上最大值做操作，另一半同理。于是整个序列的值都变成了最大值。答案即为 $n\max a_i$。

现在只剩下 $n<4$ 的情况（即 $n\in\lbrace 2,3\rbrace$）。

+ $n=2$。则要么整体做一次操作要么保持原样。
+ $n=3$。则若最大元素不位于 $a_2$ 则还原 $n\ge 4$ 的情况，否则直接暴力枚举所有可能的操作，即可计算出答案。

代码十分好写，这里就不放出来了。

---

## 作者：The_jester_from_Lst (赞：0)

简易思维题。

可以发现，对于每两个数，进行操作 $2$ 次后它们就都会变 $0$。既然如此变成 $0$ 后我们再将其与数列最大值进行操作，就能将整个序列变为最大值。

注意 $n$ 小于 $4$ 时需特判。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
	int jya=0,ysc=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')ysc=-1;ch=getchar();}
	while(isdigit(ch)){jya=jya*10+(ch-'0');ch=getchar();}
	return jya*ysc;
}
inline void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int t,a[200086],n,maxn;
signed main(){
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	t=rd();
	while(t--){
		n=rd();
		maxn=0;
		for(int i=1;i<=n;i++){
			a[i]=rd();
			maxn=max(a[i],maxn);
		}
		if(n>=4)wr(maxn*n);
		else if(n==3)wr(max(max(3*abs(a[1]-a[2]),3*abs(a[3]-a[2])),max(max(3*a[1],3*a[3]),a[1]+a[2]+a[3])));
		else if(n==2)wr(max(2*abs(a[1]-a[2]),a[1]+a[2]));
		else if(n==1)wr(a[1]);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Robin_kool (赞：0)

分类讨论题。

$n=1$，直接输出 $a_1$。

$n=2$，显然可以选择不操作或者操作一次，答案为 $a_1+a_2$ 和 $\left|a_1-a_2\right|\times2$ 的最大值。

$n=3$，需要分讨，可以不操作、操作前两个、操作后两个、操作整个序列，具体实现看代码。

$n\geq4$，可以以最大值为分界线，让左右两边都变成 $0$，那么就能让整个序列变为最大值，乘以 $n$ 即可。

代码：

```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
ll n, maxn, a[N];
int T; 
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	//freopen("CF1763C.in", "r", stdin);
	//freopen("CF1763C.out", "w", stdout);
	T = read();
	while(T --){
    	n = read(), maxn = 0; 
    	for(int i = 1; i <= n; ++ i) a[i] = read(), maxn = max(maxn, a[i]);
		if(n >= 4) write(maxn * n);
		else if(n == 1) write(a[1]);
		else if(n == 2) write(max(a[1] + a[2], abs(a[1] - a[2]) << 1));
		else if(n == 3) write(max(a[1] * 3, max(a[3] * 3, max(abs(a[2] - a[3]) * 3, max(abs(a[1] - a[2]) * 3, a[1] + a[2] + a[3])))));
		puts("");
	}
	return 0;
}

```


---

## 作者：yingkeqian9217 (赞：0)

## 前言
这道题让我认识到了一句古老的真理——十年 OI 一场空，不开 long long 见祖宗！(doge

## 题目描述

你有一个长度为 $n$ 的数组 $a$, 你可以对它进行以下操作任意多次：

- 选择两个下标 $i, j$, 满足 $1\leq i<j\leq n$, 将 $a_i \sim a_j$ 之间的所有元素替换成 $|a_i-a_j|$。

求数组能经过若干次操作以后达到的所有元素的最大和。

数据范围：$2\leq n, \sum n\leq 2\times 10^5, 1\leq a_ i\leq 10^9$。

## 分析

显然一次操作之后，区间内的所有数都会变成一个新的 $\ge 0$ 的数。而对于一个区间，很显然是左右端点的差越大，对答案的贡献就越大。

不妨假定当前区间右端点更大，那么我们就要让左端点尽量小。尽量小是多少呢？我们联系前面的结论，会发现最小应该是 $0$。

如何让一个数成为 $0$ 呢？显然关于它的操作区间左右端点要相同，不难发现，只要对一个区间连续进行两次操作，就可以使区间内所有数成为 $0$。具体来说就是从 $a_i,a_{i+1},...,a_j$ 到 $|a_i-a_j|,|a_i-a_j|,...,|a_i-a_j|$，最后就是 $0,0,...,0$。

这时再来考虑右端点，容易证明，最大肯定是取到原数组的最大值。那么问题就简单了，我们只要先把除了最大值以外的区间清零，然后对左右分别进行操作即可，最终答案是 $\max\{a\}\times n$。

但是如果区间大小有限，我们就无法有效的对其中一个区间清零，所以我们就要特判总的 $n\le 3$ 的情况。而 $\ge 4$ 的，容易构造出答案为 $\max\{a\}\times n$ 的方法。

具体来说，$\le 3$ 的情况下我们枚举所有操作可能即可。当然你直接暴力循环也是可以的。详见代码。

## AC CODE
```
#include<bits/stdc++.h>
#define maxn 1000001
#define int long long//不开long long见祖宗！
using namespace std;
int T,n,sum,maxx,a[maxn];
void solve(){
    maxx=sum=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),sum+=a[i],maxx=max(maxx,a[i]);//统计
    if(n==2) printf("%lld\n",max(sum,2*abs(a[1]-a[2])));//n=2的情况
    else if(n==3) printf("%lld\n",max(n*max(max(a[1],a[n]),max(a[2]-a[1],a[2]-a[n])),sum));
    else printf("%lld\n",maxx*n);//n=1的情况的结果也可以使用这个式子计算
}
signed main(){
    scanf("%lld",&T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1763C 题解



### 思路分析

注意到如下的观察：

> 观察：
>
> 对于任意一个 $i\in(2,n]$ 的 $i$，存在一种方法将子序列 $[1,i]$  全部赋值成 $a_i$。
>
> 首先连续操作 $[1,2]$：$(a_1,a_2) \to(|a_1-a_2|,|a_1-a_2|)\to(0,0)$。
>
> 然后操作 $[1,i]$，此时整个子序列都会变成 $a_i$。

运用上面的方法，对于 $n\ge 4$ 的情形我们可以将序列 $\max$ 推平到整个序列上，因此此时答案为 $n\times \max\{a_i\}$。

- $n=1$ 的情况：显然，答案为 $a_1$。
- $n=2$ 的情况：有意义的操作至多一次，因此答案为 $\max(a_1+a_2,2\times|a_1-a_2|)$。
- $n=3$ 的情况：如果 $a_2$ 不是严格最大值，答案为 $n\times \max\{a_i\}$，否则显然先操作 $a_2$ 和 $a_1,a_3$ 中较小的一个得到 $\{a'_i\}$，然后我们可以将答案推平为 $n\times a'_1$ 或 $n\times a'_3$，最终答案为 $\max\{a_1+a_2+a_3,3\times a'_1,3\times a'_2\}$。

时间复杂度 $\Theta(n)$。

### 代码呈现

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
const int MAXN=2e5+1;
int a[MAXN];
inline void solve() {
	int n,k=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]),k=max(k,a[i]);
	if(n==1) printf("%lld\n",a[1]);
	else if(n==2) printf("%lld\n",max(a[1]+a[2],2*abs(a[1]-a[2])));
	else if(n==3) {
		if(a[1]<a[2]&&a[2]>a[3]) {
			int ans=a[1]+a[2]+a[3];
			if(a[1]>a[3]) swap(a[1],a[3]);
			a[1]=a[2]=abs(a[1]-a[2]);
			ans=max(ans,3*max(a[1],a[3]));
			printf("%lld\n",ans);
		} else printf("%lld\n",n*k);
	} else printf("%lld\n",n*k);
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：loser_seele (赞：0)

首先考虑 $ n \geq 4 $ 的情况：这种情况下，把数组分为最大值，最大值左边的部分，最大值右边的部分，则显然除了最大值，两边的部分至少有一个长度为 $ 2 $，则最优策略显然是将这个长度 $ \geq 2 $ 的区间执行两次修改，第一次使得区间内的数完全相同，第二次修改全部修改为 $ 0 $，然后将这个区间先全部改为最大值，这样数组中出现了至少 $ 3 $ 个连续的最大值和一个连续区间，将这个连续区间和一个最大值如法炮制上述操作即可全部修改为最大值，不难发现这一定最优，因为任何修改都不可能使得修改后的数比原数列中的最大值更大。

证明：若 $ \mid a_i-a_j \mid>a_i $ 则 $ a_j < 0 $，但题目保证这种情况不会发生，且修改过程中由于绝对值总是 $ \geq 0 $ 的性质也不会满足。所以任何修改都不可能让其比出现在数列中的最大值增加。

对于 $ n \leq 3 $ 的情况简单分类讨论即可。

时间复杂度 $ \mathcal{O}(\sum{n}) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
int main() 
{
    int T;
    cin >> T;
    while (T--) 
    {
        long long n;
        cin >> n;
        vector<long long> a(n);
        long long mx = 0;
        for (int i = 0; i < n; i++) 
        {
            cin >> a[i];
            mx = max(mx, a[i]);
        }
        if (n >= 4) 
        {
            cout << mx * n << endl;
            continue;
        }
        if (n == 2) 
        {
            cout << max(a[0] + a[1], abs(a[0] - a[1]) * 2) << endl;
            continue;
        }
        long long ans = max(a[0], a[2]) * 3;
        ans = max(ans, abs(a[1] - a[0]) * 3);
        ans = max(ans, abs(a[1] - a[2]) * 3);
        ans = max(ans, a[0] + a[1] + a[2]);
        cout << ans << endl;
    }
}

```


---

