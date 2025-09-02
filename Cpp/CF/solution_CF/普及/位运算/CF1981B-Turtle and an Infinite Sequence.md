# Turtle and an Infinite Sequence

## 题目描述

There is a sequence $ a_0, a_1, a_2, \ldots $ of infinite length. Initially $ a_i = i $ for every non-negative integer $ i $ .

After every second, each element of the sequence will simultaneously change. $ a_i $ will change to $ a_{i - 1} \mid a_i \mid a_{i + 1} $ for every positive integer $ i $ . $ a_0 $ will change to $ a_0 \mid a_1 $ . Here, $ | $ denotes [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

Turtle is asked to find the value of $ a_n $ after $ m $ seconds. In particular, if $ m = 0 $ , then he needs to find the initial value of $ a_n $ . He is tired of calculating so many values, so please help him!

## 说明/提示

After $ 1 $ second, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [1, 3, 3, 7, 7, 7] $ .

After $ 2 $ seconds, $ [a_0, a_1, a_2, a_3, a_4, a_5] $ will become $ [3, 3, 7, 7, 7, 7] $ .

## 样例 #1

### 输入

```
9
0 0
0 1
0 2
1 0
5 2
10 1
20 3
1145 14
19198 10```

### 输出

```
0
1
3
1
7
11
23
1279
19455```

# 题解

## 作者：Louis_lxy (赞：14)

## 前言

比较简单的一道题，可惜场上没想到。

看到各位大佬各种神奇做法，蒟蒻表示看不懂，只能自己想了（话说今天想到发题解突然发现多了一个跟我思路类似的题解？不过他好像没写啥……所以我就再写一篇啦）。

## 思路

很显然，对于此题，每进行一次操作，对最后一个的修改显然只有前一个会影响到，而前一个又只有前一个的前一个会影响到，以此类推，所以结果一定是 $n-m$ 到 $n+m$ 的按位或和（如果 $n-m<0$ 的话就变成 $0$，因为不可能会再有变化）。

考虑如果快速求结果，毕竟暴力是 $O(n)$ 的。

首先，令 $l=\max(n-m,0),r=n+m$，显然假设 $l$ 与 $r$ 相同的最后一位是 $a$，显然它之后的每一位都必然是 $1$。因为 $l$ 到 $r$ 的所有数一定能填满所有 $a$ 之后的二进制位。

然后有暴力求的（代码为 1），时间复杂度 $O(\log n)$。

还有 $O(1)$ 的（代码 2）。

然后顺便讲一下怎么求快速位运算。

### 快速或

刚才题目思路已经讲了，就是把第一个不相同的后面的都变成 $1$，同时，也可以 $O(1)$ 的计算，先构造一个长度为 $l$ 异或 $r$ 加一 的二进制数，只有第一位是 $1$，其他为 $0$，也就是 $2^{l\oplus r+1}$，因为 $l$  异或 $r$ 的最高位一定是第一位不同的二进制位。然后减 $1$ 一定是长度为 $l\oplus r$ 的二进制数，每一位都是一，然后用它与 $l$ 按位或。

### 快速与

显然，结果一定是 $l$ 与 $r$ 相同的部分加一串 $0$，因为后面的部分一定会被若干个数清零。

与上面一样，最后用 $l$ 与它做按位与即可，这样就可以清零后面的位了。

### 快速异或

打表找规律比较简单，由于篇幅不够直接写结论了，想知道证明过程可以去百度。

求 $1,2,3...x$ 的异或和，跟 $x\mod 4$ 的结果有关。具体如下：

- $x\mod 4=0$，结果为 $x$。
- $x\mod 4=1$，结果为 $1$。
- $x\mod 4=2$，结果为 $x+1$。
- $x\mod 4=3$，结果为 $0$。

## AC CODE

### 1

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		int l = max(0, n - m), r = n + m, sum = 0;
		while ((l | sum) < r) sum <<= 1, sum |= 1;
		printf("%d\n", l | sum);
	}
}
```

### 2

```cpp
#include <bits/stdc++.h>
using namespace std;

int getor(int l, int r)
{
	if (l == r) return l;
	return l | ((1 << ( __lg(l ^ r) + 1)) - 1);
}

int getand(int l, int r)
{
	if (l == r) return l;
	return l & ((1ll << ( __lg(l ^ r) + 1)) - 1);
}

int getxor(int x)
{
	if (x < 0) return 0;
	if (x % 4 == 0) return x;
	if (x % 4 == 1) return 1;
	if (x % 4 == 2) return x + 1;
	if (x % 4 == 3) return 0;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m;
		scanf("%d %d", &n, &m);
		printf("%d\n", getor(max(0, n - m), n + m));
	}
}
```

---

## 作者：ikunTLE (赞：8)

**题目描述**

在每个元素 $ a_i $ 上执行更新操作，其中 $ a_i $ 在 $ m $ 秒后变为 $ a_{i - 1} \operatorname{or} a_i \operatorname{or} a_{i + 1} $，而 $ a_0 $ 在 $ m $ 秒后变为 $ a_0 \operatorname{or} a_1 $。

**解题思路**

本题的 $n,m \le 10^9$，想要循环一次都不可能，所以本题的正解是位运算。

每一个点每次最多移动一格，所以我们要求的范围是从 $\max(0,n-m)$ 到 $n+m$。所以对于每一次特判，我们需要判断是否在上述的范围内。

我们可以从高位到低位一位位地判断，每一次发现符合条件就更新一次答案。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		ans=0;
		scanf("%d%d",&a,&b);
		for(int i=30;i>=0;--i)
			if((a+b)>>i&1||max(0,a-b)>>i&1||(a+b-max(0,a-b)>=(1<<i)))//特判
				ans|=(1<<i);//更新答案
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：linjunye (赞：5)

### 题目大意
给定一个无限长的序列 $a_0,a_1,a_2\cdots$，在第 $0$ 秒时，$a_i=i$。

每过一秒，序列将**同时发生变化**。对于 $i>0$，$a_i=a_{i-1}|a_i|a_{i+1}$（这里 $|$ 表示的是按位或），$a_0=a_0|a_1$。

请求出 $m$ 秒后，$a_n$ 的值。

$0\le n,m\le 10^9$。
### 初步思路
我们以 $0$ 到 $7$ 为例：
```
0 1 2 3 4 5 6 7
```

假装我们要求一秒后 $4$ 的值，这个数该怎么变化呢？

```
0 1 2 3 4 5 6 7
4->3|4|5
```

这里一定要理清思路，**这些数时同时发生变化的！**

所以，$3$ 和 $5$ 一秒后的值不用求。

然后，求第二秒时的 $4$。

```
0|1 0|1|2 1|2|3 2|3|4 3|4|5 4|5|6 5|6|7 6|7|8
4->(new 3)|(new 5)
4->(2|3|4)|(4|5|6)
4->2|3|4|4|5|6
4->2|3|4|5|6
```

现在，是不是转变成了求 $n-m|n-m+1|\cdots|n+m-1|n+m$ 的值？
### 关键部分
如何快速求 $l|l+1|\cdots|r$？

首先，根据或的性质：只要有一个为 $1$，结果为 $1$（**指二进位上的 $1$**）。

那么，我们枚举一下 $r$ 的所有二进制位，若此位是 $0$，我们就去从 $l$ 到 $r-1$ 中寻找有没有此位，如果有，就加上。

那么，问题又转变为：**如何快速从 $l$ 到 $r-1$ 中找到一个数，它的二进制下的第 $i$ 位是 $1$？**

我们分类讨论：

如果 $l$ 二进制下的第 $i$ 位已经是 $1$，那么返回 $l$。

否则，我们找到一个最小满足的数，再与 $r$ 比较。

现在，问题又转变成：**如何找到一个最小的数，满足 $>l$？**

这个很简单，先把 $l$ 的二进制下的第 $i$ 位设置成 $1$，然后再将后面都设置成 $0$。

我们是不是可以通过左移运算、右移运算快速将后面设置成 $0$。

最终，再逐次往回看，发现问题得解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
bool pd(int l,int r,int p){//查询l~r中有没有数的二进制位的第p+1位是1 
	int num=1<<p;
	if((l&num)!=0)return 1;//l本身就有，位运算优化 
	l>>=p;
	l<<=p;
	//上面方法就是快速将后面设置成0（右移将后面的1都消掉了，再左移就添加0，相当于把所有1变成0） 
	l|=num;//位运算优化 
	//计算满足上述条件并且>l的第一个数
	if(l<=r)return 1;//没有越界
	return 0;//越界了
}
int range_or(int l,int r){
	int res=r;//返回值 
	int t=r;//用来遍历的数 
	int p=0;//位数 
	while(t){
		if(t%2==0&&pd(l,r,p))//此位是0并且查到此区间内有数满足这一位是1 
			res|=(1<<p);//加上，这里是位运算优化 
		p++;
		t>>=1;//位运算优化 
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//求区间或和
	cin>>t;
	while(t--){
		cin>>n>>m;
		int l=max(0,n-m);
		int r=n+m;
		cout<<range_or(l,r)<<"\n";
	}
	return 0;
}
```

---

## 作者：OIratrace (赞：4)

### 题目意思
给定一个 ${0 \sim n}$ 的序列，求经过 $m$ 次与相邻两个数按位或之后的第 $n$ 个数。
#### 注意
1. 不能和负数按位或。
2. $n$ 可以和大于 $n$ 的数按位或。
### 思路
| 次数 | $n$ |
| :----------: | :----------: |
| 1 | $n-1\mid n \mid n+1$ |
| 2 | $n-2\mid n-1\mid n \mid n+1 \mid n+2$ |
| ... |  |
| m | $n-m \mid n-m+1 \dots n+m-1 \mid n+m$ |
#### 注意
因为不能和负数按位或，所以在进行按位或求和时，左端点应不小于 $0$ 。\
所以左端点应添加特判。
```cpp
l=max(0,n-m)
  ```
### 按位或快速求和
```cpp
int hsum(int l,int r)
{
	while (r>l)
	{
		l|=(l+1);
	}
	return l;
}
```
这里直接放代码了，大家可以自己推一下。
### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int hsum(int l,int r)
{
	while (r>l)
	{
		l|=(l+1);
	}
	return l;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while (t--)
	{
		cin>>n>>m;
		int l=max(0,n-m),r=n+m;
		cout<<hsum(l,r)<<'\n';
	}
	return 0;
}
```
**最后，希望大家能点个赞。**

---

## 作者：EuphoricStar (赞：3)

答案的每一个二进制位互相独立，所以可以分别计算答案在每个二进制位的取值。

设当前在考虑第 $d$ 个二进制位，那么 $a_i = \left\lfloor\frac{i}{2^d}\right\rfloor \bmod 2$。

每过一秒，一个 $1$ 会往左边和右边“扩散”$1$ 格。

如果 $a_n$ 一开始就是 $1$ 那么答案的这一位就是 $1$。

否则 $a_n$ 处于一个 $0$ 的连续段中，我们需要计算这个连续段左边的 $1$ 和右边的 $1$ 能否“扩散”到 $a_n$。设 $x = n \bmod 2^{d + 1}$，那么 $0 \le x \le 2^d - 1$。左边的 $1$ 扩散到 $a_n$ 需要 $x + 1$ 秒，右边的 $1$ 扩散到 $a_n$ 需要 $2^d - x$ 秒。所以若 $\min(x + 1, 2^d - x) \le m$ 那么 $a_n$ 就能变成 $1$。特别地，若 $n < 2^d$ 那么左边没有 $1$，所以这种情况若 $2^d - x \le m$ 那么 $a_n$ 就能变成 $1$。

时间复杂度：每个测试用例 $O(\log (n + m))$。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<ll, ll> pii;

void solve() {
	ll n, m;
	scanf("%lld%lld", &n, &m);
	ll ans = 0;
	for (int i = 0; i <= 30; ++i) {
		ll x = n & ((1LL << (i + 1)) - 1);
		ll t = (1LL << i) - x;
		if (n >= (1LL << i)) {
			t = min(t, x + 1);
		}
		if (x >= (1LL << i) || t <= m) {
			ans |= (1LL << i);
		}
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：2)

# 思路
容易发现每一秒每个格子的或区间会左右各延伸一格（最多到 $0$），例如 $3$ 号点在 $5$ 秒后变成了 $0|1|2|3|4|5|6|7|8$，$n$ 号节点在 $m$ 秒后会变成 $\max(n-m,0)\sim n+m$ 的按位或和。

至于 $l\sim r$ 的按位或和怎么求，那我们不放先假设 $l=1011001,r=1011100$（此处均表示二进制，下同），则 $l\sim r$ 一定包含 $1011011$，此时只要拿这个数和 $r$ 做一次或就可得到 $1011111$。同理，只要知道 $l=x0a,r=x1b$（$a$ 和 $b$ 位数相同），则得数就是 $x0111\dots|r$。

[代码奉上](https://codeforces.com/problemset/submission/1981/263703343)。

---

## 作者：imsbNR (赞：2)

# 题解：CF1981B Turtle and an Infinite Sequence

## 题意简述

给定 $t$ 次询问，每次询问给两个整数 $n$ 和 $m$ 求 $\max(n - m, 0) \sim n + m$ 的区间或。

## 如何区间或

举个例子，求 $52 \sim 56$ 的区间或，只需要看 $52$ 和 $56$ 两个数即可。

我们只需要对比两数的二进制位，从最高位找起，找第一个不同位，并将这一位以及后面的位上的数都变成 $1$ 后，与最左的端点或一下就好了。

可能说的比较抽象，看图吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/0h0c0kvo.png)

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m, ans, x, t, q, l, r;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> q;
	while (q--)
	{
		cin >> n >> m;
		l = max(0, n - m);
		r = n + m;
		if (l == r)
		{
			cout << l << endl;
			continue;
		}
		for (int i = 30; i >= 0; i--)
		{
			if ((l >> i & 1) != (r >> i & 1))
			{
				cout << (l | ((1 << (i + 1)) - 1)) << endl;
				break;
			}
		}
	}
	return 0;
}
```

谢谢观看

---

## 作者：2huk (赞：1)

模拟不难发现所求为 $\operatorname{or}_{i=l}^r i$，其中 $l=\max(0, n - m), r = n + m$。

逐位考虑 $i = 0, 1, \dots$，然后考虑计算：

> 是否存在一个数 $x \in [l, r]$ 并且 $x$ 的第 $i$ 个二进制位为 $1$。

不好解决。若令 $\ge l$ 的最小的第 $i$ 个二进制位为 $1$ 的数为 $f(l)$，那么上一个问题等价于是否 $f(l) \le r$。现在的问题是：

> 求 $\ge l$ 的最小的第 $i$ 个二进制位为 $1$ 的数 $f(l)$。

分类讨论：

- 若 $l$ 的第 $i$ 个二进制位为 $1$，$f(l) = l$。
- 否则，$f(l) = \left\lfloor \dfrac l{2^i} \right\rfloor \times 2^i + 2^i$，表示先将 $l$ 的第 $i-1,i-2,\dots,0$ 个二进制位设为 $0$，再将第 $i$ 个二进制位设为 $1$。

做完了。

```cpp
int calc(int x, int y) {
	// >= y 的第一个有 x 二进制位的数
	if (y >> x & 1) return x;
	return ((y >> x) << x) | (1ll << x);
}

bool chk(int x, int l, int r) {
	// [l, r] 中是否存在一个二进制位 x
	return calc(x, l) <= r;
}

void Luogu_UID_748509() {
	int n, m;
	fin >> n >> m;
	if (!m) fout << n << '\n';
	else {
		int l = max(0ll, n - m), r = n + m;
		int res = 0;
		for (int i = 0; i < 63; ++ i )
			if (chk(i, l, r)) res |= (1ll << i);
		fout << res << '\n';
	}
}
```

---

## 作者：qzmoot (赞：1)

# 题解：CF1981B Turtle and an Infinite Sequence
## 题意
这道题给我们了 $a_n$ 然后求 $m$ 次变化后的值。
## 分析
其实十分容易，我们发现 $a_n$ 在经过 $m$ 次后，值为 $a_{n-m}|a_{n-m+1}|\ldots|a_{n+m-1}|a_{n+m}$。 这是为什么呢？

我们可以看出左边界就是 $a_{n-m}$ 因为每次变化就向两边扩散一格，右边界同理，其中有很多相同的数字可以直接消除。注意 $n-m$ 要大于等于 $0$，这里被卡了好久。

注意上面的 $a_i$ 都是指原来的数组，你可以就理解为 $i$。

分析完成之后我们要知道一个个地或肯定超时，所以我们考虑枚举每一位。

因为 $a_{n-m}$ 与 $a_{n+m}$ 是存在一个差值的，所以二进制中必定有进位，所以我们先拆分一遍，如果 $a_{n-m}$ 或者 $a_{n+m}$ 的那一位上有 $1$ 说明结果一定有 $1$。否则，我们则查看这两个数差值的最高位为多少，那么最高位以后的位数一定出现过 $1$，接着累计算出答案即可。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>
void read(T& x)
{
	x=0;
	int f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
template<typename T,typename... Args>
void read(T& first,Args&... args)
{
	read(first),read(args...);
}
int T;
int n,m;
/*
1
10 1
 
*/
int main()
{
	read(T);
	while(T--)
	{
		read(n,m);
		if(m==0)//无聊地特判
		{
			printf("%d\n",n);
			continue;
		}
		int l=max(0,n-m),r=n+m,x=0,hi;//计算差的最高位
		for(int k=30;k>=0;k--)
		{
			int no=(r-l)>>k;
			if(no&1)
			{
				hi=k;
				break;
			}
		}
		for(int k=30;k>=0;k--)
		{
			int lx=l>>k,rx=r>>k;
			if((lx&1) || (rx&1))//如果边界就有1直接累计
				x+=1<<k;
			else
				if(hi>=k)//否则最高位比现在大才累计
					x+=1<<k;
		}
		printf("%d\n",x);//输出答案
	}
	return 0;
}
```

---

## 作者：OPEC (赞：0)

# [CF1981B Turtle and an Infinite Sequence](https://www.luogu.com.cn/problem/CF1981B)

这道题的答案是范围 $\left [\max(0,n-m),n+m \right ]$ 的按位或，设 $l$ 为 $\max(0,n-m)$，$r$ 为 $n+m$。

会发现 $l$ 每次都会加一位，$r$ 每次都会减一位，也就会有 $3$ 种情答案的二进制的第 $i$ 位为 $1$。

- 如果 $l$ 的二进制的第 $i$ 为 $1$ 的话，那么答案的二进制的第 $i$ 位为 $1$。

- 如果 $r$ 的二进制的第 $i$ 为 $1$ 的话，那么答案的二进制的第 $i$ 位为 $1$。

- 如果 $\frac{l}{2^{i+1}} \neq \frac{r}{2^{i+1}}$ 说明变了两次或以上，所以答案的二进制的第 $i$ 位为 $1$。

时间复杂度 $O(t\times\log(n+m))$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t,n,m,l,r,ans;
void solve()
{
	ans=0;
	cin>>n>>m;
	l=max(0ll,n-m);
	r=n+m;
	for(int i=31;~i!=0;i--)
	{
		if(l&1<<i||r&1<<i||l>>i+1!=r>>i+1)
		{
			ans|=1<<i;
		}
	}
	cout<<ans<<'\n';
}
signed main()
{
    fst
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：sbno333 (赞：0)

众所周知，$a\mid b\mid b=a\mid b$。

对于第二次操作，发现 $a'_i\mid a'_{i-1}\mid a'_{i+1}=a_{i-2}\mid a_{i-1}\mid a_i\mid a_{i+1}\mid a_{i+2}$，对于第 $k$ 次操作，有 $a^{k}_i=\mid_{j=-k}^k a_{i+j}=(\mid_{j=0}^k a_{i+j})\mid(\mid_{j=0}^k a_{i-k+j})$。

当然，对于 $(\mid_{j=0}^k a_{i-k+j})$，还需要处理一下最低为负数的情况，这是容易处理的，即如果会变成负数，变成 $(\mid_{j=0}^i a_j)$。

我们考虑区间或，可以拆位统计，对于每一位，计算至少需要加多少才能得到 $1$，这是容易的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int orr(int l,int m){
	int ans;
	ans=0;
	for(int i=0;i<=40;i++){
		if(l&(1ll<<i)){
			ans+=(1ll<<i);
		}else{
			int zz;
			zz=l&((1ll<<(i+1))-1);
			zz=(1ll<<i)-zz;
			if(zz<=m){
				ans+=(1ll<<i);
			}
		}
	}
	return ans;
}
void _main(){
	int n,m;
	cin>>n>>m;
	int ans;
	ans=orr(n,m);
	if(n-m>=0){
		ans|=orr(n-m,m);
	}else{
		ans|=orr(0,n);
	}
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## 题目描述

有一个无限长度的序列 $ a_0, a_1, a_2, \ldots $。最初对于每个非负整数 $ i $，$ a_i = i $。

每秒钟，序列中的每个元素同时改变。对于每个正整数 $ i $，$ a_i $ 将会改变为 $ a_{i - 1} \mid a_i \mid a_{i + 1} $。对于 $ a_0 $，它将会改变为 $ a_0 \mid a_1 $。

输出经过 $ m $ 秒后的 $ a_n $ 的值。特别地，如果 $ m = 0 $，那么需要输出 $ a_n $ 的初始值。

## 思路

本题可以用位运算解决。

每一个点每次最多移动一格，所以范围是 $\max(0,n−m) \sim n+m$。

所以每一次我们只需要判断是否在上述的范围内就可以决定是否更新答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,ans;
void solve(){
	cin>>a>>b;
	for(int i=30;i>=0;--i){
		if((a+b)>>i&1||max(0,a-b)>>i&1||(a+b-max(0,a-b)>=(1<<i))){//在范围内
			ans|=(1<<i);//更新答案
		}
	}
	cout<<ans<<endl;
}
signed main(){
	cin>>t;
	while(t--){
		ans=0;
		solve();
	}
	return 0;
}
```

**注意：多测不清空，爆 $0$ 泪两行。**

---

