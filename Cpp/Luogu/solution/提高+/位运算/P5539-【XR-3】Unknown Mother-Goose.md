# 【XR-3】Unknown Mother-Goose

## 题目描述

小 X 得到了一个正整数 $n$ 和一个正整数集合 $S$，他想知道有多少个正整数 $x$ 满足以下所有条件：

- $3 \le x \le n$
- 存在 $a \in S, x \equiv 0 \pmod a$
- 存在 $b \in S,x-1 \equiv 0 \pmod b$
- 存在 $c \in S,x-2 \equiv 0 \pmod c$

请你帮小 X 求出来。

## 说明/提示

【样例 $1$ 说明】

只有当 $x = 6$ 时：

- $x \equiv 0 \pmod 2$
- $x \equiv 1 \pmod 5$
- $x \equiv 2 \pmod 4$

满足条件。

## 样例 #1

### 输入

```
10 3
2 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
100000 6
14 47 31 233 666 59
```

### 输出

```
91
```

# 题解

## 作者：NaCly_Fish (赞：14)

出题人怎么一直不发题解啊，，  
那我就来水一篇好了（

首先，这题看起来时什么 $\Theta(2^{|S|})$ 之类的做法，然而实际上就是 $\Theta(n|S|/w)$ 的 bitset 大暴力。

做法也就是开一个 $10^9$ 的数组，对于 $S$ 中的每个数 $k$，把 $k$ 的倍数都设为 $1$，统计数组中有多少组 $3$ 个连续的 $1$ 即是答案。

然后把这个过程用 bitset 优化一下就可以了（  
另外要注意的一点，$x$ 是正整数，或许要把第 $0$ 项的贡献判掉

ps：这个东西和分块的思想很像，不过是基于CPU的运算优化的。

代码：
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 1000000003
#define reg register
using namespace std;

unsigned long long bs[(N>>6)+10];
unsigned long long tmp[65];
int n,m,s,l,ans;

inline int count(unsigned long long x){
    reg int res = 0;
    while(x){
        res += x&1;
        x >>= 1;
    }
    return res;
}

int main(){
    scanf("%d%d",&n,&s);
    m = (n>>6)+1;
    while(s--){
        scanf("%d",&l);
        if(l<64){ //两种情况判一下,保证加入的复杂度是 n/w
            memset(tmp,0,sizeof(tmp));
            for(reg int i=0;i<(l<<6);i+=l)
                tmp[i>>6] |= 1ull<<(i&63); //加入的数比较小,开另一个数组,作为重复单元
            for(reg int i=0;i<=m;i+=l)
            for(reg int j=0;j<l;++j)
                bs[i+j] |= tmp[j];    
        }else{
            for(reg int i=0;i<=n;i+=l)
                bs[i>>6] |= 1ull<<(i&63);
        }
    }
    --m;
    if((n&63)!=63) bs[m] &= (1ull<<(n+1-(m<<6)))-1; //特判一下最后一块
    bs[0] &= -2ull; //除去第 0 项
    for(reg int i=0;i<=m;++i) ans += count(bs[i]&(bs[i]<<1)&(bs[i]<<2));
    for(reg int i=1;i<=m;++i) ans += count(bs[i]&(bs[i-1]>>62)&((bs[i-1]>>63)|(bs[i]<<1)));
    printf("%d",ans);
    return 0;
}
```

---

## 作者：123456zmy (赞：10)

先转化一下题意，题目要求的是把 $S$ 集合中所有的数的倍数标记之后，连续 $3$ 个都被标记的位置的数量，于是可以得到一个 $O(n|S|)$ 的做法，考虑进行二进制压位优化~~手写 `bitset`。~~

对于集合中不小于 $64$ 的元素 $x$，枚举其倍数进行标记复杂度为 $\frac{n}{x}$，因为 $x\ge64$，故最坏情况复杂度为 $\frac{n}{64}$。

对于集合中小于 $64$ 的元素 $x$，把要进行标记的位置压进 `unsigned long long`，循环节的长度一定不大于 $x$，所以可以把一个循环节处理出来然后对标记数组或上这个循环节就可以做到 $O(64+x+\frac{n}{64})$。

原数组和其左移 $1$ 位的数组和左移 $2$ 位的数组或起来之后 $1$ 的个数就是答案，然后使用 `unsigned long long` 可以达到 $O(\frac{n}{64})$。

总时间复杂度(最坏情况) $O(128|S|+\frac{n(|S|+1)}{64})$，算出来大概 $3.3\times10^8$，因为内存访问还是比较连续的所以能过。
___
现在过的应该都类似于这种做法，大部分时间都是在 $\frac{n(|S|+1)}{U}$，造成运行时间差异的主要原因是代码的常数，这里就讲一下怎么卡常。

此题输入输出量并不大，所以 IO 复杂度可以忽略~~写了 fread 也没关系~~；可能因为开了 O2，`inline` 和 `register` 优化也不大。下面是几个常数优化比较大的地方：

#### 尽量避免循环内除法、取模运算。  
众所周知，除法、取模是非常慢的，特别是还放在循环里面跑满了 $\frac{n|s|}{64}$ 遍。  
比如下面的两段代码是等效的，但是前者对应的是 [$15.42s$](https://www.luogu.com.cn/record/40772267)，而后者是 [$8.13s$](https://www.luogu.com.cn/record/40768881)，比前面的快了 $7.29s$。
```cpp
int r=(n>>6)/k*k;
for(int i=0;i<r;i++)vis[i]|=tmp[i%k];//15.42s
```

```cpp
int r=(n>>6)/k*k;
for(int i=0;i<r;i+=k)for(int j=0;j<k;j++)vis[i+j]|=tmp[j];//8.13s

```

#### 使用较快的统计 $1$ 的个数的方式。  
统计二进制 $1$ 的个数有几种方式，下面放一下本地测试情况，测试数据为随机 $01$ 串，长度为 $10^9$，重复计算 $10$ 次取时间和。  

1. 每次去除最低位，递归实现。代码：`f(i){return i?f(i&(i-1))+1:0;}`  
运算时间和 $1$ 的位数相关，最慢，$3300ms$ 左右。
2. 每次去除最低位，循环实现。代码：`while(i)++cnt,i&=i-1;`  
运算时间还是和 $1$ 的个数相关，很慢，$3100ms$ 左右。
3. 转 bitset 使用 `count` 函数。代码：`vis.count();`  
因为使用 bitset，常数降为 $\frac{1}{64}$，较快，$600ms$ 左右。
4. 使用位运算加速的某种 $\log\log n$ 的做法。
```cpp
int f(unsigned long long i)
{
	i=(i&0x5555555555555555)+(i>>1&0x5555555555555555),
	i=(i&0x3333333333333333)+(i>>2&0x3333333333333333),
	i=(i&0x0f0f0f0f0f0f0f0f)+(i>>4&0x0f0f0f0f0f0f0f0f),
	i=(i&0x00ff00ff00ff00ff)+(i>>8&0x00ff00ff00ff00ff),
	i=(i&0x0000ffff0000ffff)+(i>>16&0x0000ffff0000ffff);
	return i+(i>>32);
}//450ms
```
5. 玄学东西，`__builtin_popcountll(i)`  
运行速度最快，$300ms$ 以内，但是有双下划线所以联赛不能用。

___
经过卡常，可以做到总时间卡进 [$6.94s$](https://www.luogu.com.cn/record/40778215)，[代码](https://www.luogu.com.cn/paste/t015lt13)，下面再放一些更玄学的东西：
```cpp
#include<immintrin.h>
#pragma GCC target("avx2")
```
~~没错就是要用指令集。~~ 注意，平常用可以，**正式比赛的时候千万别用**，~~用了会原地AFO~~。

加了指令集头文件之后，就可以使用指令集了，~~不知道为什么总有些人指令集头文件乱加，加完又不用指令集还说加了指令集~~，这里指令集主要用在优化打标记的过程，可以做到在一次运算的时间内对 $256$ 位进行或运算，也就是这句话：`vism[i+j]=_mm256_or_si256(vism[i+j],tmpm[j])`。

经过指令集优化之后，复杂度变为 $O(\frac{n|S|}{256}+\frac{n}{64})$，可以在上面的基础上再优化 $1.23s$，放上[目前最优解](https://www.luogu.com.cn/record/40782718)[代码](https://www.luogu.com.cn/paste/fn1n8elu)~~前面说过的优化不大的东西还是加上去了~~。

---

## 作者：tobie (赞：7)

~~这题我第一眼觉得是中国剩余定理~~

考虑使用手写 bitset。我们通过 $\dfrac{n}{64}$ 个 `unsigned long long` 整型来储存 bitset 的每一位，其中第 $i$ 位表示 $i$ 能否被 $S$ 中的任何一个数字整除，则答案用位运算统计即可。

现在就出现了一个问题：当 $a_i$ 数值过小时，$\dfrac{n}{a_i}$ 最大可以达到 $10^9$ 量级，时间复杂度吃不消。

所以我们对 $a_i\le64$ 与 $a_i>64$ 进行分类讨论：

1. 若 $a_i\le64$，我们考虑循环节。因为 $64\times a_i≡0\pmod{64}$，所以只考虑 $a_i$ 的情况下，每 $a_i$ 个 `ull` 数组出现一次循环，那么我们可以再开一个数组统计，然后统一赋值。时间复杂度为 $O\left(64+\dfrac{n}{64}\right)$。

2. 若 $a_i>64$，暴力统计即可。

以下是代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define ull unsigned long long
ull bitset[15625009],cs[70];
int n,m;
signed main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		if(x>64)
		{
			for(int j=0;j<=n;j+=x)
			bitset[j/64]|=(1ull<<(j%64));
		}
		else
		{
			for(int j=0;j<=x;j++) cs[j]=0ull;
			for(int j=0;j<=64;j++)
			cs[j*x/64]|=(1ull<<(j*x%64));
			for(int j=0;j<=n/64;j++)
			bitset[j]|=cs[j%x];
		}
	}
	for(int i=n+1;i/64==n/64;i++) bitset[i/64]=((bitset[i/64]|(1ull<<(i%64)))^(1ull<<(i%64)));
	bitset[0]=((bitset[0]|1)^1);
	int ans=0;
	for(int i=0;i<=n/64;i++)
	{
//		cout<<bitset[i]<<" ";
//		for(int j=0;j<63;j++)
//		if(bitset[i]&(1ull<<j)) printf("%d ",i*64+j);cout<<endl;
		ull fuck=bitset[i];
		fuck=fuck&(fuck>>1)&(fuck>>2);
		while(fuck) ans+=(fuck&1),fuck>>=1;
	}
	for(int i=1;i<=n/64;i++)
	{
		if((bitset[i]&1)&&(bitset[i-1]&(1ull<<63))&&(bitset[i-1]&(1ull<<62))) ans++;
		if((bitset[i]&1)&&(bitset[i]&2)&&(bitset[i-1]&(1ull<<63))) ans++;
	}
	printf("%d\n",ans);
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：4)

前言：今天是最后一个可以用编译指令的日了，默哀

条件 $f(i)=\exists a\in S:i\equiv0\pmod a$ 是一个是或者否，并且每一个 $a$ 都会独立的贡献一些函数值边成 $1$。自然想到二进制压缩维护 $f$ 的值，因为 $O(|S|n/\omega)$ 时间 $O(n/\omega)$ 内存看的很可行。  
我们需要保证任何元素更新时间不会超过 $O(n/\omega)$。显然当 $\omega\le a$ 的时候暴力修改所有倍数也会保证时间复杂度，问题现在就在于 $\omega>a$ 的时候。  
我们可以把“所有倍数都变成 $1$"看做把所有块按位或某个特殊数。发现这个特殊数序列周期必定不大于 $a$，构造是 $O(\omega)$，暴力按位或起来即可。

时间复杂度 $O(|S|(\omega+n/\omega))$，手写一个 bitset 即可。  
在最后几个小数允许绕过编译指令检测，抢到目前最优解。

```cpp
// writer: w33z8kqrqk8zzzx33
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

uint64_t __b[15625002], *b = &__b[1];
uint64_t tmp[64];
int n, lastblock;

void apply(int x) {
	if(x >= 64) for(int i=0; i<=n; i+=x) b[i>>6] |= (1ull<<(i&63));
	else {
		rep(i, 64) tmp[i] = 0;
		rep(i, 64) tmp[(x*i)>>6] |= (1ull<<((x*i)&63));
		for(int i=0; i<=lastblock; i+=x) {
			int h = min(i+x,lastblock+1);
			for(int j=i; j<h; j++) b[j] |= tmp[j-i];
		}
	}
}

int calc() {
	if(b[0] & 1) b[0] ^= 1;
	iter(i, lastblock<<6, (lastblock+1)<<6) if((b[i>>6]&(1ull<<i)) && n < i) b[i>>6] ^= (1ull<<i);
	int ans = 0;
	rep(i, lastblock+1)
		ans = ans + __builtin_popcountll(b[i] & ((b[i]<<1) | (b[i-1]>>63)) & ((b[i]<<2) | (b[i-1]>>62)));
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	lastblock = n>>6;
	int q; cin >> q;
	set<int> v;
	rep(i, q) { int t; cin >> t; v.insert(t); }
	for(int t:v) apply(t);
	cout << calc();
}
```

---

## 作者：spire001 (赞：3)

## Unknown Mother-Goose 题解

其他题解将思路讲到位了，这个题解主要讲讲代码中用于优化的位运算的原理。。。

这个题是个大暴力，相当于手写一个 `bitset`，将原题的目标转化为二进制位中连续的三个 $1$，但是有很多细节。

题是好题，几乎将所有位运算技巧都考察到了。。。

1. 对特殊数取模 

   $a \operatorname{mod} 2^k=a\operatorname{and}(2^k-1)$。其中 $\operatorname{and}$ 指的是按位和运算。

   因为对 $2^k$ 取模后，删去了这个数字中所有大于 $2^k-1$ 的部分。

   在二进制位中 $2^k$ 是只有第 $k+1$ 位（从第 $1$ 位开始计数）为 $1$ 其他位都为 $0$ 的。

   那么 $2^k-1$ 就是除了第 $1$ 位到第 $k$ 位都为 $1$ 其他位都为 $0$ 的。

   根据按位和定义，就可以得到 $a \operatorname{mod} 2^k=a\operatorname{and}(2^k-1)$ 这条性质。。。

2. 判断两数是否相等

   $a$ 与 $b$ 相等的充要条件是 $a\operatorname{xor} b=0$。其中 $\operatorname{xor}$ 指的是异或运算。

   根据定义很容易理解。。

3. 对特殊数做除法

   移位运算没必要再详细解释。。

4. 除去二进制位的最后一位

   假设正整数 $a$ 的二进制位最后一位 为 $1$，那么 $a-1$ 的二进制位最后一位 为 $0$。

   如果 $a$ 的二进制位最后一位 为 $0$，那么由于退位 $a-1$ 的二进制位最后一位 为 $0$。

   所以将 $a$ 与 $a-1$ 做按位和可以实现除去二进制位的最后一位。

掌握了上文技巧，于是可以写出代码：

```cpp
# include <iostream>
# include <climits>
# include <charconv>
# include <cstring>
# include <algorithm>
# include <vector>
# include <cstdio>
# include <bitset>
# pragma GCC target("avx2")
# define num1 __builtin_popcountll//编译器内建函数，很快
using namespace std;
constexpr int N = 30, M = 1e9 + 1;
int n, m;
unsigned long long box[(M >> 6) + 65], tmp[65];
//避免加一带来的巨大常数
//下标从 0开始 
void print(unsigned long long x)
{
	if(x > 1ull) print(x >> 1);
	cerr << ((x & 1ull) ^ 48);
}
void printall(int l, int r)//调试用函数
{
	for(int i = l; i <= r; i++)
	{
		unsigned long long tmp = box[i];
		for(int j = 1; j <= 64; j++) 
			cerr << (tmp & 1ull), tmp >>= 1;
		cerr << ' ';
	}
	cerr << '\n';
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	int ln = n >> 6;ln++; 
	//长度，注意下标从 0 开始
	
	for(int i = 1; i <= m; i++) 
	{
		int x;
		cin >> x;
		if(x >= 64)
		{
			for(int i = 0; i <= n; i += x)
				box[i >> 6] |= 1ull << (i & 63ull); 
			//box[i / 64] = box[i / 64] + pow(2, i % 64)
            //肉眼可见的优化
		}
		else//小于 64 需要特判一下
		{
			memset(tmp, 0, sizeof tmp);
			for(int i = 0, j = (x << 6); i < j; i += x)
				tmp[i >> 6] |= 1ull << (i & 63ull);
			for(int i = 0; i < ln; i += x)
				for(int j = 0; j < x; j++)
					box[i + j] |= tmp[j];
		}
	}
	box[0] &= box[0] - 1ull;//去掉末尾的 0  
//	printall(0, ln);
	int ans = 0;
	//除掉最后 0 ~ 63个数里面大于 n 的部分。
	if((n & 63) != 63) box[ln - 1] &= (1ull << ((n & 63) + 1)) - 1;
//	printall(0, ln);
    //连续的三个 1 
	for(int i = 0; i < ln; i++) ans += num1(box[i] & (box[i] >> 1) & (box[i] >> 2));
	//还有一种可能，两相邻的 64 位可能对答案做出贡献
	for(int i = 1; i < ln; i++)
	{
		ans += (box[i] & 1ull) & (!((box[i - 1] >> 62) ^ 3ull));//左 2 右 1
		ans += (!((box[i] & 3ull) ^ 3ull)) & (box[i - 1] >> 63 & 1ull);//左 1 右 2
	}
	cout << ans;
	return 0;
}
```

还有一些细节，比如说数据类型要开 `unsigned long long`，位运算时根据数据类型选择 `1ull` 或 `1`。

---

## 作者：_ayaka_ (赞：0)

### 前言

>世界があたしを拒んでも，
>
> 今、愛の唄 歌わせてくれないかな？

### 思路

首先有一个显然的暴力，设集合 $S$ 中的第 $i$ 个数为 $a_i$，那我们只需要把所有小于等于 $n$ 的 $a_i$ 的倍数全部用一个 bool 数组记录下来，再看这个 bool 数组内有多少组连续 $3$ 个的 $1$ 即可。

虽然这样是可行的，但这个方法显然最坏是 $O(n|S|)$，在 $n\le 10^9$ 的数据下并不能通过，就算不论时间复杂度，空间也不能接受。

不过如果你会 bitset 的话，显然能想到这个方法可以使用 bitset 优化空间。bitset 的原理就是对一个整型变量，将其的每一个二进制位都当作一个 bool 来使用。使用 bitset 处理的空间复杂度为 $O(\frac{n}{w})$，其中 $w$ 为 bitset 所优化的位数。使用 STL 中的 bitset，$w=32$。但我们可以使用手写 bitset 的方式来把 $w$ 优化到 $64$。

但是这样仍然无法通过，因为如果 $a_i=1$，这意味着我们仍要循环 $n$ 次来找到所有倍数，我们的时间复杂度在 bitset 里也依然为 $O(n|S|)$。什么方法来优化呢？有的，我们可以分类讨论。

- 当 $a_i<w$ 时，我们很容易可以知道 $a_i$ 倍数在 bitset 中的循环节为 $a_i$ 个一循环，那我们只需要在 $O(w)$ 的复杂度内造出 $a_i$ 的循环节，再用最坏 $O(\frac{n}{w})$ 的复杂度把循环节和用于标记的 bitset 或起来就好了。
- 当 $a_i\ge w$ 时，我们只需要暴力枚举 $a_i$ 倍数的位置即可。最坏时间复杂度是 $O(\frac{n}{w})$。

输出时，分类为全部在同一个整型内，一个在左边的整型而两个在右边的整型，两个在左边的整型而一个在右边的整型这三种情况解决即可。具体可以看代码的输出部分。

最后总时间复杂度最坏为 $O(\frac{n}{w}|S|)$。在 $w=64$ 的情况下，大约等于 $3\times 10^8$，大致可以卡过去。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
unsigned long long p[16500005], h[70];
int n, s, u, m, ans;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> s;
	m = n >> 6;//bitset 的整型数量
	while (s--) {
		cin >> u;
		if (u < 64) {//处理 < 64 的部分
			for (int i = 0; i < (u << 6); i += u) {
				h[i >> 6] |= 1ull << (i & 63);//这里相当于 %64，但是 &63 比 %64 快不少
			}
			for (int i = 0; i <= m + 1; i += u) for (int j = 0; j < u; j++)p[i + j] |= h[j];
			for (int i = u - 1; i >= 0; i--) {
				h[i] = 0;
			}
		} else {//处理 >= 64 的部分
			for (int i = 0; i <= n; i += u) {
				p[i >> 6] |= 1ull << (i & 63);
			}
		}
	}
	p[0] &= p[0] - 1;//去掉第0位
	if ((n & 63) != 63) p[m] &= (1ull << ((n & 63) + 1)) - 1;//去掉第n位以外的位
	for (int i = 0; i <= m; i++) ans +=  __builtin_popcountll((p[i]) & (p[i] >> 1) & (p[i] >> 2));//在同一整型内 
	for (int i = 1; i <= m; i++) ans +=  __builtin_popcountll((p[i]) & (p[i - 1] >> 62) & ((p[i] << 1) | p[i - 1] >> 63));//不在同一整型内
	// __builtin_popcountll() 可以在 O(1) 的时间复杂度内求出一个 long long 的二进制里 1 的数量 
	cout << ans;
	return 0;
}
```

---

