# Beautiful Array

## 题目描述

Stanley defines the beauty of an array $ a $ of length $ n $ , which contains non-negative integers, as follows: $ $$$\sum\limits_{i = 1}^{n} \left \lfloor \frac{a_{i}}{k} \right \rfloor, $ $  which means that we divide each element by  $ k $ , round it down, and sum up the resulting values.</p><p>Stanley told Sam the integer  $ k $  and asked him to find an array  $ a $  of  $ n $  non-negative integers, such that the beauty is equal to  $ b $  and the sum of elements is equal to  $ s$$$. Help Sam — find any of the arrays satisfying the conditions above.

## 说明/提示

In the first, the second, the fifth and the sixth test cases of the example it is possible to show that such array does not exist.

In the third testcase of the example $ a = [0, 0, 19] $ . The sum of elements in it is equal to 19, the beauty of it is equal to $ \left ( \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{0}{6} \right \rfloor + \left \lfloor \frac{19}{6} \right \rfloor \right ) = (0 + 0 + 3) = 3 $ .

In the fourth testcase of the example $ a = [0, 3, 3, 3, 29] $ . The sum of elements in it is equal to $ 38 $ , the beauty of it is equal to $ (0 + 0 + 0 + 0 + 7) = 7 $ .

## 样例 #1

### 输入

```
8
1 6 3 100
3 6 3 12
3 6 3 19
5 4 7 38
5 4 7 80
99978 1000000000 100000000 1000000000000000000
1 1 0 0
4 1000000000 1000000000 1000000000000000000```

### 输出

```
-1
-1
0 0 19
0 3 3 3 29
-1
-1
0
0 0 0 1000000000000000000```

# 题解

## 作者：liangbowen (赞：20)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1715B)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1715b)

看起来挺难，其实一分钟就能想出来。

## 思路

首先考虑什么时候无解。由于 $k \times \left\lfloor\dfrac{a}{k}\right\rfloor \le a \le \left\lfloor\dfrac{a}{k}\right\rfloor + (k - 1)$，$a$ 与 $k$ 是自然数。'

所以可得下式。（看起来很复杂，其实很简单，要耐心看！）

$$k \times \sum\limits_{i=1}^n\lfloor\frac{a_i}{k}\rfloor \le\sum\limits_{i=1}^na_i \le k \times \sum\limits_{i=1}^n\lfloor\frac{a_i}{k}\rfloor + n \times (k - 1)$$

用原题中的 $b$ 和 $k$ 表示。

$$k \times b \le s \le k \times b + n \times (k - 1)$$

不在这个范围内，就是无解了。

继续思考：在这个范围内就是有解，那怎么构造解呢？

我们可以先满足 $b$，再满足 $s$。

满足 $b$ 非常简单，我们可以直接让 $a_1 = k \times b$。然后计算用掉 $a_1$ 后剩下的 $s$。

接下来，每一个 $a_i$ 都可以再塞 $0$ 到 $(k - 1)$。由于范围限制，最后一定是可以塞完的。那这题就做完啦。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define space putchar(' ')
#define endl putchar('\n')
using namespace std;
typedef long long LL;
typedef long double LD;
void fastio()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
LL read()
{
	char op = getchar(); LL x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(LL x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
LL a[100005];
void solve()
{
	LL n = read(), k = read(), b = read(), s = read();
	if (b * k <= s && s <= b * k + n * (k-1))
	{
	    a[1] = b * k;
		LL left = s - b * k;
		for (int i = 1; i <= n; i++, space)
		{
			if (left >= k - 1) write(a[i] + k - 1), left -= (k - 1);
			else if (left != 0) write(a[i] + left), left = 0;
			else write(a[i]);
		}
		endl;
	}
	else puts("-1");
}
int main()
{
	int T = read();
	while (T--) solve();
	return 0;
}
```

其实也可以不用数组，思路是一样的。[代码](https://codeforces.com/contest/1715/submission/169474963)也差不了多少。

希望能帮助到大家！

---

## 作者：Dregen_Yor (赞：6)

[博客食用效果更佳](https://www.cnblogs.com/Dregen-Yor/p/16612989.html)。

# 思路

根据题意，不难看出，当 $b>\dfrac{s}{k}$ 时，一定无解，因为无论怎样分配 $s$，最终的结果一定不会比 $\dfrac{s}{k}$ 更大。

然后再来考虑当 $b\le\dfrac{s}{k}$ 时，什么情况下有解什么情况下无解。

因为 $b=\sum\limits_{i=1}^n\lfloor\dfrac{a_i}{k}\rfloor$ 我们一开始可以直接把其中一位赋值成 $s$，其它位置皆为 $0$。若这时不满足条件，我们可以考虑从 $s$ 中减去一部分数分到其它位置。根据贪心的思想，我们每次都让 $s$ 减去的那一部分数尽可能的大，这样才最有可能满足题目的条件。因为 $\lfloor\dfrac{k-1}{k}\rfloor=0$，所以直接令减去的部分为 $k-1$ 即可。

每次减去 $k-1$ 后，判断当前的 $s$ 是否满足条件。若满足，直接输出构造方案即可，当运行到每一位上都是 $k-1$ 时，说明没有任何一种情况满足条件，直接输出 $-1$ 即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
int t, n, k, b, s, ans[100010];

signed main() {
	scanf("%lld", &t);

	while (t--) {
		scanf("%lld%lld%lld%lld", &n, &k, &b, &s);
		memset(ans, 0, sizeof(ans));
		int top = 1;

		while (s / k != b && top <= n) {
			s -= (k - 1);
			ans[top] = (k - 1);
			top++;
		}

		if (s / k == b && top <= n) {
			ans[top] = s;
		} else {
			puts("-1");
			continue;
		}

		for (int i = 1; i <= n; ++i) {

			printf("%lld ", ans[i]);
		}

		putchar('\n');
	}

	return 0;
}


```


---

## 作者：Haber (赞：4)

### 题目大意：

你需要构造一个长度为 $n$ 的非负整数序列，并且满足：

1. $\sum\limits_{i=1}^n a_i=s$

2. $\sum\limits_{i=1}^n \left\lfloor\dfrac{a_i}{k}\right\rfloor=b$

### 解题方案

一道比较常规的构造题，难度不大，但是有很多的细节要思考。

首先我们发现，这个序列有两个约束条件。容易发现，如果从条件一入手的话有太多种情况了，所以优先考虑条件二，因为它的约束强度要大一些。

由于要除下来的商的和为 $b$ ，那我们很容易想到一种构造方法 $[k\times b+c_1,c_2,c_3\dots,c_n]$。其中 $\forall i\in [1,n],c_i <k$。

显然，第 $2$ 项到第 $n$ 项对于商的总和 $b$ 是没有贡献的，唯一的贡献来源就是第 $1$ 项，刚好是 $b$。

好了，第二个约束条件考虑好了。那么来看第一个条件。要求序列元素和为 $s$。

在前面处理第二个条件的时候，我们是给我们自己留出了一点调整的空间的，每个元素后方都加上了一个 $c_i$。当然，这个调整的空间也是有限度的，很容易得出，这个 $s$ 最小就是当所有 $c_i=0$，即 $[k\times b,0,0,\dots,0]$ 时，此时 $s=k\times b$。而最大的情况，即所有 $c_i=k-1$时，序列长这样：$[k\times b+k-1,k-1,k-1,\dots,k-1]$，此时 $s=k\times b+(k-1)\times n$。所以，如果 $s$ 不在这个范围内的话，那就无解，输出 `-1`。

### 代码实现

已经分析好了，那么怎么码出来？

按照之前的思路，我们可以算出 $\sum c_i=s-k\times b$ 即我们需要调整的量的大小。然后再将这些量进行分配。对于每一个元素，能分多少分多少。

在代码中我们使用 `res` 来记录剩余我们要分配的量，初始值为 $\sum c_i$。每个元素分配到最大量，即 $\min(k-1,res)$。

然后就行了。~~实现还挺简单~~

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t;
ll n,b,k;
ll s;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>b>>s;
		if(k*b>s||k*b+n*(k-1)<s){
			cout<<-1<<endl;
			continue;
		}
		ll res=s-b*k;
		ll now=min(res,k-1);
		cout<<k*b+now<<" ";
		res-=now;
		for(int i=2;i<=n;i++){
			now=min(res,k-1);
			cout<<now<<" ";
			res-=now;
		}
		cout<<endl;
	}
	return 0;
} 
```

还是那句话：十年OI一场空，不开【】见祖宗。

---

## 作者：Awsdkl (赞：3)

[原题传送门](https://codeforces.com/contest/1715/problem/B)  
# 分析
首先， $s$ 一定要大于或等于 $k \times b$ (除数乘上它所有的商之和),即 $k \times b \le s$ 时才有答案。  

然后我们思考， $s$ 最大是多少。  
 $s$ 如果最大，首先肯定包含了 $k \times b$ ，为了保证 $s$ 最大但美不变，我们就要让所有的数都加上 $k - 1$ ，因为 $\lfloor (k - 1 ) \div k \rfloor = 0$ ，那么一共就加上了 $(k - 1) \times n$。  
那么我们就可以得到一下的式子： $s \le k \times b + (k - 1) \times n$ 。
 
综合上述，我们可以得到有答案的条件，即 $k \times b \le s \le k \times b + (k - 1) \times n$ 。

如果存在答案的话，我们就可以用一下思路：  

首先将 $k \times b$ 这个数存到有 $n$ 长度的数组  
然后遍历整个数组，将每一格加上 $\min(s,k - 1)$ ，(假定 $s$ 已减去前面加的数)。  
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
long long n,k,b,s;
long long a[100005];  //用于存储答案的数组

int main()
{
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof(a));
		cin>>n>>k>>b>>s;
		a[0] = k * b;
		s -= k * b;
		if(s < 0) cout<<"-1\n"; //判断 s 是否小于k × b
		else
		{
			for(int i = 0;i < n;i++)
			{
				int now = min(k - 1,s);
				a[i] += now;
				s -= now;
			}
			if(s > 0) cout<<"-1\n"; //判断 s 是否大于k × b + (k − 1) × n 
			else
			{
				for(int i = 0;i < n;i++)
				{
					cout<<a[i]<<' ';
				}
				puts("");
			}
		}
	}
	
	return 0;
}
```


---

## 作者：Epi4any (赞：2)

>$1 \leq t \leq 10^3 , 1 \leq n \leq 10^5$
 
### 切记！切记！切记！先看数据范围！！！
很明显，这题是一个构造加数学题，优化算法到 $O(nt)$，即 $O(n)$ 构造。

经过一些简单的计算，我们可以得到一个关键的关系式：
> $b \times k + $ 余数 $= s$

于是我们只需要贪心的构造，从第一个数起，每一个数都给他分配尽量大的值，然后假如还有剩余那就说明其无解。

具体构造方法见代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define int long long

int t, n, k, b, s;
int ans[100005], pos;

void solve() {
	memset(ans, 0, sizeof(ans));
	pos = 0;
	cin >> n, cin >> k, cin >> b, cin >> s;
	int tmp = b * k; //暂时记录可能的最小值
	if (s < tmp) {
		cout << -1 << endl;
		return;
	}

	s -= tmp;//记录所需余数
	for (int i = 1; i <= n; i++) {//每一次给他赋上可能的最大余数
		if (s > k - 1) ans[++pos] = k - 1, s -= (k - 1); //如果一次性扣不完，那就尽可能扣多点
		else ans[++pos] = s, s = 0;//如果一次性能扣完，那就归零
	}

	if (s != 0) cout << -1 << endl;//如果还有剩余，那就无解
	else {
		ans[1] += tmp;//把第一项附上没有余数的和，一次性处理掉
		for (int i = 1; i <= n; i++) cout << ans[i] << " ";//输出
		cout << endl;
	}
}

signed main() {
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```

---

## 作者：xiaomuyun (赞：2)

- [洛谷传送门](https://www.luogu.com.cn/problem/CF1715B)
- [CodeForces 传送门](https://codeforces.com/contest/1715/problem/B)

## 思路分析

首先我们可以发现，$s$ 是不可能小于 $k\times b$ 的，而且 $s$ 不可能大于 $k\times b+n\times(k-1)$（为了使数组的美丽值恰好等于 $b$，数组的和在 $k\times b$ 的基础上最多只能增加 $n\times(k-1)$）。所以这就是判断是否有解的条件。

为了简便，我们不妨让 $a_n=k\times b$，这样可以省去将 $b$ 个 $k$ 分解到 $a$ 中每个元素的操作。然后，就将 $s$ 中剩下的 $s-k\times b$ 的部分分解到 $a$ 的各个元素中即可。**不过要注意，分解时每个元素都不能增加超过 $k-1$，否则就会改变这个数组的美丽值。**

## 代码实现

```cpp
#include<cstring>
#include<cstdio>
#define int long long
using namespace std;
int t,n,k,b,s,a[100001];
signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(a,0,sizeof a);//注意一定要初始化
		scanf("%lld%lld%lld%lld",&n,&k,&b,&s);
		if(k*b>s||k*b+n*(k-1)<s){//判断无解
			printf("-1\n");
			continue;
		}
		a[n]=k*b,s-=a[n];//提前处理k*b的部分
		int cur=n;
		while(cur){
			//这一部分是贪心，让后面的数（实际上顺序可以随便定，从1开始也可以）尽可能的多加（也就是能加到k-1就加到k-1，s<k-1了再说）
			if(s<k-1){
				a[cur]+=s;
				break;
			}
			//使当前的数增加k-1，然后让s减少k-1
			a[cur]+=k-1,s-=k-1,--cur;
		}
		for(int i=1;i<=n;++i) printf("%lld ",a[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：2)

简单构造题。

对于每个数据，先将 $a_{1\sim n-1}$ 变成 $0$，然后将 $a_n$ 变成 $k(b+1)-1$（注意要对 $s$ 取 $\min$）。这样，我们就让 $\lfloor\frac{a_n}{k}\rfloor=b$ 同时 $a_n$ 最大了。

我们已经满足了 $b$，但是 $s$ 还没满足。

可以显然地发现，我们只要将 $a_{1\sim n-1}$ 尽可能地赋成 $k-1$ 就可以了。

对于无解的情况，只有赋 $a_n$ 时发现 $s$ 过小或赋完 $a_{1\sim n-1}$ 时 $s$ 过大两种情况。

---

AC Code（删去了赛时代码的部分无意义内容）：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[100005];

signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k,b,s;
		scanf("%lld%lld%lld%lld",&n,&k,&b,&s);
		for(int i=1;i<n;i++)
		{
			a[i]=0;
		}
		a[n]=min(s,b*k+k-1);
		s-=a[n];//减去 a[n]
		if(!s&&a[n]/k<b)//s 过小
		{
			puts("-1");
			continue;
		}
		for(int i=n-1;i&&s;i--)
		{
			a[i]=min(k-1,s);
			s-=min(k-1,s);//减去 a[i]
			//注意对 s 取 min
		}
		if(s)//s 过大
		{
			puts("-1");
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			printf("%lld ",a[i]);
		}
		puts("");
	}
 	return 0;
}
```

---

## 作者：happybob (赞：1)

## 题意

定义一个 $n$ 个元素的序列 $a$ 的价值为 $\sum\limits_{i = 1}^{n} \left \lfloor \dfrac{a_{i}}{k} \right \rfloor$。现在给定 $k$，序列价值 $b$，序列每个数的总和 $s$，请你还原一种序列，或者输出 $-1$ 表示不存在。

## 解法

先说个笑话，赛时这题我一眼看上去不会做去做 C 了，C 过了之后回来切了，结果 $\div \, 0$ 没有特判 fst 了，从 $2000$ 名掉到 $4000$ 名。

先考虑第一个数放 $s$，其他放 $0$。那么价值应该为 $\lfloor \dfrac{s}{k} \rfloor$。分情况讨论：

1. 若 $\lfloor \dfrac{s}{k} \rfloor < b$，无解，因为第一个就放 $s$ 已经最大化了价值。

1. 若 $\lfloor \dfrac{s}{k} \rfloor = b$，则直接构造第一个 $s$，其他 $0$。

1. 若 $\lfloor \dfrac{s}{k} \rfloor > b$，考虑在某些位置填 $k-1$。具体细节看代码。

```cpp
#pragma GCC optimize("-Ofast") 
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5, INF = 2e9, MOD = 1e9 + 7;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, k, b,s,t;

signed main()
{
	// freopen("*.in", "r", stdin);
	//freopen("1.txt", "w", stdout);
	t=read();
	while(t--)
	{
		n=read(),k=read(),b=read(),s=read();
		if(k==1) // 赛时没加特判，fst
		{
			if(s/k!=b) printf("-1\n");
			else
			{
				printf("%lld ",s);
				for(int i=2;i<=n;i++) printf("0 ");
				printf("\n");
			}
		}
		else if(s/k<b)
		{
			printf("-1\n");
		}
		else if(s/k==b)
		{
			printf("%lld ",s);
			for(int i=2;i<=n;i++) printf("0 ");
			printf("\n");
		}
		else
		{
			int ret=b*k+s%k;
			int left = s-ret;
			int need=ceil(left*1.0/(k-1));
			if(need<n)
			{
				printf("%lld ", ret);
				int sum=0; 
				for(int i=1;i<need;i++) printf("%lld ", k - 1),sum+=k-1;
				printf("%lld ", left-sum);
				for (int i = need+2;i<=n;i++) printf("0 ");
				printf("\n");
			}
			else if (need==n)
			{
				int lp=left%(k-1);
				if(lp==0) lp=k-1;
				if(s%k+lp<k)
				{
					ret=b*k+s%k+lp;
					printf("%lld ", ret);
					for(int i=1;i<need;i++) printf("%lld ", k - 1);
					printf("\n");
				} // 3
				else printf("-1\n");
			}
			else printf("-1\n");
		}
	}
	return 0;
}


```


---

## 作者：Lyrella (赞：0)

# 题意
给你 $n,k,b,s$，让你构造一个长度为 $n$ 的序列，使序列所有元素之和为 $s$，使序列所有元素除以 $k$ 向下取整之和为 $b$。
# 思路
## 无解
## Situation 1
先试着满足 $s=\sum_{i=1}^{n}a_i$，再满足 $b$。吴姐情况就有：
$$k\times b > s$$
### 证明
设 
$$b=\sum_{i=1}^{n} \left \lfloor\frac{a_i}{k}\right \rfloor$$
则有 
$$k\times b\leq \sum_{i=1}^{n}a_i$$
$$k\times b\leq s$$
所以 $k\times b>s$ 吴姐。

## Situation 2
如果满足 $b=\sum_{i=1}^{n}\left \lfloor\frac{a_i}{k}\right \rfloor$，再满足 $s$。吴姐情况就有：
$$\sum_{i=1}^{n}a_i<s$$
### 证明
令 $a_i$ 为满足 $b=\sum_{i=1}^{n}\left \lfloor\frac{a_i}{k}\right \rfloor$ 时的最大值，则：
$$\max\sum_{i=1}^{n}a_i=\sum_{i=1}^{n}\left \lfloor\frac{a_i}{k}\right \rfloor\times k+(k-1)$$
$$\max\sum_{i=1}^{n}a_i\geq s$$
所以 $\sum_{i=1}^{n}a_i<s$ 吴姐。

## 有姐
## Situation 3
直接**贪心**，对于每个 $a_i$，填当前可填最大值。
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, n, k, b, s, a[100005];
signed main()
{
	cin >> T;
	while(T--)
	{
		memset(a, 0, sizeof a);
		scanf("%lld %lld %lld %lld", &n, &k, &b, &s);
		if(k * b > s){puts("-1"); continue;}
		int t = k * b + k - 1;
		t += (n - 1) * (k - 1);
		if(t < s){puts("-1"); continue;}
		a[n] = min(s, k * b + k - 1); s -= a[n];
		for(int i = n - 1; i; i--)
		{
			if(s == 0)break;
			a[i] = min(k - 1, s);
			s -= a[i];
		}
		for(int i = 1; i <= n; i++)printf("%lld ", a[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：cachejtt (赞：0)

## 题意
给你四个正整数 $n,k,b,s$。要求你构造一序列长度为 $n$，使得：

- $\sum\limits_{i=1}\limits^{n}a_i=s$
- $\sum\limits_{i=1}\limits^{n}\lfloor\dfrac{a_i}{k}\rfloor=b$

若不存在输出 $-1$。

## 思路
先考虑判断可行条件。我们优先满足条件 $2$，观察数列和的范围。

数列和取最小值时，数列为 $b\times k,0,0,\dots$，此时和为 $b\times k$。此时将任意大于零的一项减少一，都将不满足条件 $2$，故其为最小值。

数列和取最大值时，数列为 $b\times k+k-1,k-1,k-1,\dots$，此时和为 $b\times k+n\times (k-1)$。此时无论将哪一项加上 $1$，都将不满足条件 $2$，故其为最大值。

故当 $b \times k\le s\le b\times k+n\times (k-1)$ 时有解。只需先将第一个数加上 $b\times k$，然后把剩余数对整个数组随便分配即可，只需保证每个数再分到不超过 $k-1$，即为答案。

### 正确性证明
由于我们是分配 $s$，故 $s$ 一定正确。

对于 $b$，分配方法保证了：

- $b \times k\le a_1< b\times (k+1)$
- $0\le a_i<k-1$（$1\le i\le n$）

故 $a_1$ 对 $b$ 的贡献为 $b$，后面所有数对 $b$ 的贡献为 $0$，即可保证 $b$ 正确。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ms(x, i) memset((x),(i),sizeof x)
#define int long long
#define endl "\n"
using namespace std;
int t=1,n,k,b,s,a[100005];
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>k>>b>>s;
    ms(a,0);
    if(k*b>s || k*b+n*(k-1)<s){
      cout<<"-1"<<endl;
    }
    else{
      s-=b*k;
      a[1]=b*k;
      rep(i,1,n){
        if(s>=0){
          a[i]+=min(k-1,s);
          s-=min(k-1,s);
        }
      }
      rep(i,1,n)cout<<a[i]<<" ";
      cout<<endl;
    }
  }
  return 0;
}
```

---

## 作者：xzy090626 (赞：0)

# CF1715B 题解
## 前言
这可能是目前为止写得最用心的题解。

赛时因为犯了个【】错误而没能场切，警钟长鸣。

让我们一起继续努力。

希望大家可以点个赞鼓励一下我吖！

---
另外，之前作为萌新看 dalao 们的题解都写得非常难懂，对像我这样的 trash 就十分不友好，因此我会写得非常详细~~啰嗦~~。

因此，本题解将会详细介绍解题步骤以及正确性的证明。

尽管题解较为冗长，但是其实都是干货。
## 题意
给你四个数 $n,k,b,s$，你需要构造一个长为 $n$ 的序列 $a$，使得序列元素和为 $s$，且所有元素除以 $k$ 下取整之和为 $b$。如果无解则输出 $-1$。
## 分析
乍一看，又是恶心的构造。但是第一个要点来了！

CF 的题目一般样例和 hints 是非常有用的，大部分解法都可以从它们中获取。

我们可以观察几个有解的样例，发现它们有一个共同点：前面都有几个 $0$，后面才是正整数。

当然，很容易发现元素顺序对于结果没有影响。

因此当然可以不关心顺序，但这里为了方便我们就先按照样例来做。

打 CF 的时候不会做的原因一般是碰到了瓶颈。这时我们可以先找到这个瓶颈。

那么我们目前面对的问题就是没有办法确定如何给序列分配这个 $s$ 和 $b$。（~~不要多想~~）

这时，我们可以先尝试一种不一定正确的思路，如果不行就放弃而选择另一种，就很像 DFS 一样。
### 贪心的尝试
我们不妨先将所有的 $s$ 给其中一个数，就像样例一样，先让 $a_n = s$。

一个问题随之而来：如果 ${s\over k}$ 与 $b$ 不相等怎么办？

我们发现，这个题目的主要问题就在这里了：如何同时满足这两个条件？

这个问题我们可以先放到一边。

我们做题时也可以先不考虑主要问题，转而讨论何时无解。

首先是最明显的一种情况，即 $k \times b > s$，此时无论如何继续分配，也无法满足条件；

其次，我们刚刚考虑了 $s$ 由于太小而无解的情况，现在同样可以考虑 $s$ 太大的情况。

但是这种情况就很难考虑了。

要使得 $s$ 过大而无解，我们首先要使得 $a_i$ 之和最大。怎么做呢？

这时，我们就以一个更加全面、清晰的角度面对了刚刚那个问题。
 
我们可以先继续按照刚刚贪心的思路，即先将 $a_n$ 赋上一个很大的值，让 $\lfloor{a_n \over k}\rfloor = b$。容易发现，$a_n \in [k\times b,k\times b+k)$ 时，满足这一条件。

接着，我们可以根据 $s$ 的范围，决定 $a_n$ 的取值。

具体地，
- 当 $s$ 在 $a_n$ 的取值区间内的时候，直接让 $a_n = s$ 即可；

- 当 $s$ 大于 $a_n$ 的上界时，我们可以让 $a_{[1,n-1]}$ 帮助它解决这个问题。也就是，由于必须满足 $0\le a_i < k$，因此我们可以给它们赋值，从而使得序列和为 $s$；

- 当 $s$ 小于 $a_n$ 的下界时，和上面说的一样，很明显是无解的。
### 正确性证明
我们注意上面的第二条，仔细观察，是不是发现我们可以通过它获取 $s$ 的最大取值！

那么 $s$ 由于太大而无解的情况就是 $s>k\times (b+1)-1+(n-1)\times(k-1)$，化简一下（其实没有必要）就是 $s>n\times (k-1) + k\times b$。

其实赛时想到这里就可以开始写了，但是既然是题解当然要有正确性的证明啦！

我们可以再注意第一、三条，发现它们其实都是我们贪心思想的产物。

也就是说，我们必须保证贪心的正确性。

回顾一下贪心的具体内容，其实就是说，把 $s$ 赋给一个值和均匀赋给其他地方是等价的。

---
我们先给出一个引理：
$$ \lfloor {x\over k}\rfloor + 1 = \lfloor{{x+k}\over k}\rfloor$$ 
且
$$ \lfloor {x\over k}\rfloor + 1 > \lfloor{{x+k-1}\over k}\rfloor$$ 

通俗地说，就是对于任意一个正整数 $x$，要想使得 $\lfloor {x \over k}\rfloor$ 加一，至少要让 $x = x+k$。

---
那么把这个引理带回本题，我们惊奇地发现，最终 $b$ 的值原来只与 $k$ 有关，而与加在谁身上无关！！

那么我们的贪心显然是对的，因为我们可以把能加到 $a_{[1,n-1]}$ 身上的全部加在 $a_n$ 上，而这是不改变 $b$ 的结果的。

那么，对于 $b$ 的贡献完全可以只放在 $a_n$ 上，而对于 $s$ 的贡献可以分配给 $a_{[1,n-1]}$ 一些。

本题的分析就这样结束了，具体做法见下方解释。
## 实现
### 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 7;
int a[N];
void solve(){
    int n,k,b,s;
    cin>>n>>k>>b>>s;
	int t = k*b;
	if(s<t||s>n*(k-1)+t){
		cout<<"-1\n";
		return ;
	}
	if(s>=k*b&&s<=k*(b+1)-1){
		for(int i=1;i<n;++i) cout<<"0 ";
		cout<<s<<'\n';
		return ;
	}
	a[n] = k*b+k-1;
	t = s - a[n];
	for(int i=1;i<n;++i){
		if(t>k-1){
			cout<<k-1<<' ';
			t -= k-1;
		}
		else{
			cout<<t<<' ';
			t = 0;
		}
	}
	cout<<a[n]<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```
时间复杂度 $O(n)$。

[AC 记录](https://codeforces.com/contest/1715/submission/169216350)
### 实现解释
代码非常简短，但是重点是思维。

我们先按照刚才解出的 $s$ 的合法范围进行判断是否合法。

接着，判断 $s$ 是否在 $a_n$ 的取值范围内。如果在，那么直接输出。

接下来面对的局面就是 $s$ 合法，但是剩余的贡献交给 $a_{[1,n-1]}$ 来解决。

这样就完美地解决了问题。
## 总结
### 总结 $\to$ 前言
其实我觉得打了一场比赛，无论正式与否；乃至于做了一道题目，总结才是最重要的部分，因为这道题目几乎不可能作为原题给你带来什么，但是你除了获得的一点点做题经验之外，通过总结可以获得更多的教训。

因此，我希望大家可以读一读我花了很长时间写的总结。
### 正式总结
这道题非常细节，很多的细节其实可以修改，但是都一样。

难点其实就在于这个贪心。

对于在我这个段位的 trash 而言，直接通过直觉想出这种题的正解的概率为 $0\%$。

但是，通过观察样例/hints 而得出解法的做法非常有用，不仅是在 CF，在 CSP/NOIP 等比赛里仍然有效，因为很多小 tricks 都带有贪心的思想。

比如这题，我们贪心的思路就是直接把 $b$ 的贡献给 $a_n$，而让 $a_{[1,n-1]}$ 仅仅分配 $s$ 的贡献。

这种方法在构造序列的题目当中非常好用。

我们不仅可以总结构造题目的经验，甚至可以上升到所有题目当中去：

当没有思路/无从下手时，可以先寻找一种更可能正确或者更容易实现的解法，对其进行延展思考，然后判断其正确性。

这种解法也不一定是贪心，当然仅仅对于 CF 而言，Div.2ABC 甚至 D 都带有贪心的思想，而且甚至是纯贪心（构造）。

因此，**不会做不一定是真的不会做，可以先找找方法，而不是不断地告诉自己不会做。**

### 总结的总结
感谢您的观看，祝您 CSP 2022 rp++，CF 早日上 LGM！


---

## 作者：ExplodingKonjac (赞：0)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1715B)**

## 题目分析

答案的每个 $a_i$ 都可以拆成 $k\cdot c_i+d_i\ (0\le d_i<k)$ 的形式。不难发现所有 $c_i\ (i>1)$ 都可以累加到 $c_1$ 上而不影响答案。

所以就有这样的构造方案：令 $a_1\gets k\cdot b,\ s\gets s-a_1$，再把剩下的 $s$ 分配到 $d_i$ 里，且满足 $0\le d_i<k$。显然如果 $k\cdot b<s$ 或者分配完后 $s>0$ 就无解。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

LL T,n,k,b,s,a[100005];
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>k>>b>>s;
		fill(a+1,a+n+1,0);
		s-=(a[1]=k*b);
		if(s<0)
			qout<<-1<<'\n';
		else
		{
			for(int i=1;i<=n;i++)
			{
				if(!s) break;
				a[i]+=min(s,k-1);
				s=max(0ll,s-k+1);
			}
			if(s>0)
				qout<<-1<<'\n';
			else
			{
				for(int i=1;i<=n;i++)
					qout<<a[i]<<' ';
				qout<<'\n';
			}
		}
	}
	return 0;
}
```


---

