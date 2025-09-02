# べき表現

## 题目描述

给定一个整数 $n(1\le n\le 10^{15})$，请输出一个长为 $m(1\le m\le 100)$ 的整数数列 $a$，满足：

- $\sum a_i=n$；
- $|a_i|\le 10^{18}$，且当 $i\neq j$ 时，$|a_i|\neq|a_j|$；
- 对于每一个满足 $1\le i\le m$ 的整数 $i$，$|a_i|=3^x$，其中 $x$ 为自然数。

数据保证，在本题数据范围下，数列 $a$ 一定存在。若有多解，输出任一解即可。

## 样例 #1

### 输入

```
6```

### 输出

```
2
9 -3```

## 样例 #2

### 输入

```
9193```

### 输出

```
9
2187 27 1 -243 3 9 -81 6561 729```

## 样例 #3

### 输入

```
10120190919012```

### 输出

```
16
-1594323 9 -177147 -531441 1162261467 -4782969 387420489 -6561 -2187 2541865828329 -27 7625597484987 3486784401 10460353203 -94143178827 31381059609```

# 题解

## 作者：Sacred_Konnyaku_mMr (赞：2)

# 题意简述
这是一道构造题，题目会给定一个正整数 $n$，我们需要构造一个长度为 $m$ 的序列，使得这个序列满足 $3$ 个条件，如下：
- 这些数的和必须为 $n$（即 $\sum_{i=1}^n \ a_i = n$）。
- 这些 $a_i$ 的绝对值互不相同。
- 每一个 $a_i$ 的绝对值都是 $3$ 的次幂。
# 思路简述
我们发现题目要求每一个 $a_i$ 都必须是 $3$ 的次幂，且和为 $n$，我们就可以联想到三进制，因为三进制是满足这个条件的。

我们可以将给定的 $n$ 变成三进制的形式，如果是 $1$，就将此位所代表的 $3$ 的次幂保存在一个答案数组中，并将答案长度加一，如果是 $0$，就跳过此位。

但是，如果是 $2$ 呢？

我们发现如果将某一个 $3$ 的次幂乘上 $2$，那么它就不再是 $3$ 的次幂了，也就不满足条件 $3$ 了。

这时我们就可以将这个值转换一下。我们假设当前在三进制中是第 $i$ 位。那么我们就可以将 $2 \times 3^i$ 转换成
 $-3^{i} + 3^{i+1}$。
 
 而这一位我们存 $-3^{i}$，然后将下一位在三进制下的值加一。这一步我们可以用打标记的形式来完成。

到这儿这道题就解完了。

# 参考代码
```cpp
#pragma G++ optimize(3, "Ofast", "inline")
#pragma G++ optimize(2)
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <queue>
#include <set>
#include <climits>
#include <random>
#include <bitset>
#include <unordered_map>
#define $ putchar('\n');
#define INF (1e18+3)
#define C(y,x) fac[y]*inv_fac[(y)-(x)]*inv_fac[x]
#define _max(a,b) (a>b?a:b)
#define _min(a,b) (a<b?a:b)
#define orz %
#define ll long long
#define int long long
#define pii std::pair<int, int>
#define fi first
#define se second
#define eb emplace_back
#define pb push_back
#define m_p std::make_pair
#define pq std::priority_queue<int>
#define pq_min std::priority_queue<int, std::vector<int>, std::greater<int> >
#define pq_min_pii std::priority_queue<pii, std::vector<pii>, std::greater<pii> >
#define open(x); freopen(#x".in", "r", stdin);freopen(#x".out", "w", stdout);
#define test(x); cout << "Test: " << x << '\n'
#define close fclose(stdin);fclose(stdout);
#define ull unsigned long long
#define debug(); printf("Skmqwq\n");

namespace Fast_Skm {

	template <typename T>
	inline void read(T &x) {
		T s = 0, w = 1;
 		char c = getchar();
		while(!isdigit(c)) {
			if(c == '-')  w  = -1;
			c = getchar();
		}
		while(isdigit(c))
			s = (s << 1) + (s << 3) + (c & 0xcf), c = getchar();
			
		x = s * w;
		return ;
	}

	template <typename T, typename... Arp>
	inline void read(T &x, Arp &...arp) {
		read(x), read(arp...);
        return ;
	}

	template <typename T>
	inline void write(T x) {
		if(x < 0) x = -x, putchar('-');
		int p = 0;
		static char s[100];
		do {
			s[++p] = x orz 10 + '0';
			x /= 10;
		} while (x);
		while(p) putchar(s[p--]);
		putchar(' ');
	}

	template <typename T, typename... Arp>
	inline void write(T &x, Arp &...arp) {
		write(x), write(arp...);
		return ;
	}

	template <typename S, typename T>
	inline void smax(S &x, T y) {
		x = (x > y) ? x : y;
	}

	template <typename S, typename T>
	inline void smin(S &x, T y) {
		x = (x < y) ? x : y;
	}

	inline void quit() {
		exit(0);
		return ;
	}
	
	inline ll quick_pow(ll a, ll b, ll P) {
		ll ans = 1;
		while(b >= 1) {
			if(b & 1) {
				ans = ans * a % P;
			}
			a = a * a % P;
			b >>= 1;
		}
		return ans;
	}
	
	template <typename T>
	inline T exgcd(T a, T b, T &x, T &y) {
		if(b == 0) {
		 	x = 1; y = 0;
		 	return a;
		}
		int gcd = exgcd(b, a % b, x, y);
		int tmp = y;
		y = x - a / b * y;
		x = tmp;
		return gcd;
	}

} using namespace Fast_Skm;

const int N = 35;
int n, m = 0, ans[N], step = 0;

signed main() {

	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> n;
	
	int f = 0;
	while (n != 0 || f != 0) {
		int now = n % 3;
		n /= 3;
		now += f, f = 0;
		if (now == 0) {
			++step;
			continue ;
		} else if (now == 1) {
			ans[++m] = quick_pow(3, step, INF);
		} else if (now == 2) {
			ans[++m] = -quick_pow(3, step, INF);
			f = 1;
		} else if (now == 3) {
			f = 1;
		}
		++step;
	}

	write(m);
	$
	for (int i = 1; i <= m; ++i) {
		write(ans[i]);
	}

	return 0;
}

```

---

## 作者：chl090410 (赞：1)

## The Solution to AT_past202107_g べき表現

### Description 

构造一个长度为 $m$ 的数列 $a$，使得：
- $\sum a_i=n$，$|a_i|\le10^{18}$；
- 对于任意 $i\ne j$，$|a_i|\ne|a_j|$；
- 对于任意一个整数 $i\in[1,m]$，有 $|a_i|=3^x$，其中 $x$ 为自然数。

给定 $n$，请输出 $m$ 与数列 $a$。

### Solution

因为 $a$ 的每一项的绝对值都是 $3$ 的 $x$ 次方，而其和为 $n$，所以考虑将 $n$ 转为 $3$ 进制（转换方法类似于 $10$ 进制转 $2$ 进制）。

$n$ 的三进制数是由 $0,1,2$ 组成的，若从右往左数第 $s$ 位为 $k$，则代表 $k\times3^{s-1}$，而所有位置上所代表的数之和就为 $n$，至此，我们构造的数列已满足了条件 $1,3$。

但 $k=2$ 时，若输出两个 $3^{s-1}$ 就不满足条件 $2$ 了，因为只是要求 $a_i$ 的绝对值等于 $3^x$，所以可以将 $2\times3^{s-1}$ 转化成 $3^s-3^{s-1}$，再将 $3^s$ 进到前一位即可。注意进位后可能使前一位变成 $3$，此时需要接着向前进位。

至此，我们就构造出了题目中要求的数列，接下来就是输出了。每次输出 $a_i\times3^{i-1}$ 即可。注意若 $a_i=0$，此时不要输出 $0$，直接跳过即可。因为要先输出数列中的数的个数，所以我们要先统计数列中不为 $0$ 的数的个数。

### AC code 如下：

```
#include <bits/stdc++.h>
#define int long long
#define N 1005
using namespace std;
int n,m,a[N],k,b[N],mk;
void zyass(int x){
	while(x>0){
		a[++k]=x%3;
		x/=3;
	}
}
int qsort(int a,int b){
	int ans=1;
	while(b>0){
		if(b%2==1){
			ans=ans*a;
		}
		a=a*a;
		b/=2;
	}
	return ans;
}
signed main(){
	cin>>n;
	zyass(n);
	for(int i=1;i<=k;i++){
		m=i;
		while(a[m]>=2){
			if(a[m]==2){
				a[m+1]++;
				a[m]=-1;
			}else{
				a[m+1]++;
				a[m]=0;
			}
			m++;
		}
	}
	for(int i=1;i<=k+1;i++){
		if(a[i]!=0){
			mk++;
		}
	}
	cout<<mk<<endl;
	for(int i=1;i<=k+1;i++){
		if(a[i]!=0){
			cout<<a[i]*qsort(3,i-1)<<" ";
		}
	}
	return 0;
}

---

## 作者：yanxu_cn (赞：0)

题意应该已经相当明了了，就不做解释了。

考虑什么东西和 $3^x$ 有关，自然而然的考虑到 $3$ 进制。

以下位数从低往高，且最低位是第 $0$ 位。

+ 如果第 $k$ 位上是 $0$，自然不用进行任何操作；
+ 如果第 $k$ 位上是 $1$，就输出 $3^k$；
+ 如果第 $k$ 位上是 $2$，由于我们不能输出两个 $3^k$，所以先输出 $-3^k$ 再向 $k+1$ 位加一。

易得出代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
//3 的 k 次方。
constexpr long long pow3[]={};
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	long long n;
	vector<long long>ansv;
	cin>>n;
	for(int i=0;n;i++)
	{
		switch(n/pow3[i]%3)
		{
			case 1:
				ansv.push_back(pow3[i]);
                n-=pow3[i];
				break;
			case 2:
				ansv.push_back(-pow3[i]);
				n+=pow3[i];
				break;
		}
	}
	cout<<ansv.size()<<'\n';
	for(auto i:ansv)
	{
		cout<<i<<' ';
	}
	return 0;
}
```

---

## 作者：0x00AC3375 (赞：0)

## 前言
本题可以视为[平衡三进制](https://baike.baidu.com/item/%E5%B9%B3%E8%A1%A1%E4%B8%89%E8%BF%9B%E5%88%B6/9370144?fr=ge_ala)的模版题。

## 1. 前置知识 - 平衡三进制
平衡三进制是一种以 $3$ 为基数，以 $-1,0,1$ 为基本数码的三进制计数体系。为便于书写，一般会将平衡三进制某一位上的 $-1$ 用字母 $\text Z$ 来表示。将一个平衡三进制数转化为十进制，只需要将对应数位上的数乘以 $3$ 的幂次累加即可，计算方法和常规三进制的计算方法相同。

例如要将平衡三进制下的数字 $1\text Z101$ 转化为十进制，计算方法为：

$(1\text Z101)_{\text{balance3}}=1\times3^4+(-1)\times3^3+1\times3^2+0\times3^1+1\times3^0=64$

从上面的计算流程中我们很容易看出，**对于一个给定的十进制数字 $n$，只需要将其转化为平衡三进制，根据这个由 $-1,0,1$ 构成的序列，就可以将其拆分为满足题意的正负 $3$ 的幂次的组合**。

由于平衡三进制不同于常规的[三进制](https://www.luogu.com.cn/problem/B3619)，其涉及到负数的数位，因此直接将十进制转化为平衡三进制可能有些困难，为此我们可以先将**十进制转化为常规三进制，再转化为平衡三进制**。

## 2. 十进制转化为常规三进制
十进制转化为普通三进制，只需要重复“模 $3$ 然后整除 $3$”的流程, 将给定的整数转化为一串由数字 $0,1,2$ 构成的序列即可，参考代码如下：
```
int tp[100];
void dec2base3(long long t) //将十进制转化为普通三进制, 使用数组存储每一位, 下标小的表示低位, 下标大的表示高位
{
	int index = 0;//当前的数位
	while (t)
	{
		tp[index] = t % 3;
		t /= 3;
		index += 1;
	}
	return;
}
```

## 3. 常规三进制转化为平衡三进制
由于 $3-1=2$，因此将常规三进制转化为平衡三进制时，需要将三进制上为 $2$ 的位变成 $-1$，然后进位。如果这个进位导致前一位变成 $3$，也需要进位，以此类推，参考代码如下：
```
void base2balance3()//将普通三进制转化为平衡三进制, 平衡三进制的每一位由-1, 0或1构成
{
	for (int i = 0; i <= 99; i += 1)
	{
		if (tp[i] == 2)//如果某一位是2, 这一位就变成-1, 然后高位增加1
		{
			tp[i] = -1;
			tp[i + 1] += 1;
		}
		if (tp[i] == 3)//如果某一位是3, 和普通三进制一样, 要进位
		{
			tp[i] = 0;
			tp[i + 1] += 1;
		}
	}

}
```

## 4. 输出
按照平衡三进制的序列，输出 $1$ 或 $-1$ 乘以 $3$ 的幂次即可。需要注意的是**如果平衡三进制的某一位为 $0$，答案中不能输出 $0$，直接跳过**。由于输出的第一行是个数，因此需要统计平衡三进制中不为零的数位个数。

参考代码：
```
for (index = 99; index >= 0; index -= 1) if (tp[index]) break;//找到第一个不为零的数位
for (int i = index; i >= 0; i -= 1) if (tp[i]) tot += 1;/*平衡三进制如果某一位是0, 就不输出, 所以要判断总共要输出多少位!*/
printf("%d\n", tot);
for (int i = index; i >= 0; i -= 1) if(tp[i]) printf("%.0Lf ", powl(3.L, i) * tp[i]);
```

## 5. 完整代码
```
#pragma warning(disable:4996)
#include <cstdio>
#include <algorithm>
#include <cmath>
long long n, index, tot = 0;
int tp[100];
void dec2base3(long long t) //将十进制转化为普通三进制, 使用数组存储每一位, 下标小的表示低位, 下标大的表示高位
{
	int index = 0;//当前的数位
	while (t)
	{
		tp[index] = t % 3;
		t /= 3;
		index += 1;
	}
	return;
}
void base2balance3()//将普通三进制转化为平衡三进制, 平衡三进制的每一位由-1, 0或1构成
{
	for (int i = 0; i <= 99; i += 1)
	{
		if (tp[i] == 2)//如果某一位是2, 这一位就变成-1, 然后高位增加1
		{
			tp[i] = -1;
			tp[i + 1] += 1;
		}
		if (tp[i] == 3)//如果某一位是3, 和普通三进制一样, 要进位
		{
			tp[i] = 0;
			tp[i + 1] += 1;
		}
	}

}
int main()
{
	scanf("%lld", &n);
	dec2base3(n);
	base2balance3();
	/*调试用代码块 - 一般用Z表示-1, 倒序输出即可得到输入整数的平衡三进制的序列
	for (int i = 99; i >= 0; i -= 1)
	{
		if (tp[i] == 0) putchar('0');
		if (tp[i] == -1) putchar('Z');
		if (tp[i] == 1) putchar('1');
	}
	*/
	for (index = 99; index >= 0; index -= 1) if (tp[index]) break;
	for (int i = index; i >= 0; i -= 1) if (tp[i]) tot += 1;/*平衡三进制如果某一位是0, 就不输出, 所以要判断总共要输出多少位!*/
	printf("%d\n", tot);
	for (int i = index; i >= 0; i -= 1) if(tp[i]) printf("%.0Lf ", powl(3.L, i) * tp[i]);
}
```

---

