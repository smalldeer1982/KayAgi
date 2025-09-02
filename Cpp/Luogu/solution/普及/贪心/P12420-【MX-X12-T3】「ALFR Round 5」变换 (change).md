# 【MX-X12-T3】「ALFR Round 5」变换 (change)

## 题目背景

原题链接：<https://oier.team/problems/X12C>。

## 题目描述

本题有 $T$ 组测试数据。

有一个长度为 $n$ 的非负整数序列 $a$ 和两个参数 $m,k$。

你可以对序列 $a$ 进行任意次数的操作，对于每次操作，你都需要：

- 选取一个非负整数 $x$ 使得 $x \ \& \ m = x$，选取一个下标 $i \in [1,n]$，将 $a_i \gets a_i \ | \  x$，然后你需要将 $m \gets m - x$ 或者花费 $k$ 的代价使得 $m$ 不变。

记你花费的代价为 $s$，你需要求出 $(\oplus_{i=1}^{n} a_i) - s$ 的最大值。 

其中 $|$ 代表按位或运算，$\&$ 表示按位与运算，$\oplus$ 表示按位异或运算。

## 说明/提示

**【样例解释 #1】**

进行操作 $i = 1$，$x = 2$，然后将 $a_1 \gets a_1 \ | \ 2$，然后选择花费 $k = 0$ 的代价将 $m$ 不变，在此之后 $m = 2$，容易发现之后的所有操作不会将答案变大，因此最大值为 $a_1 - s = 3 - 0 = 3$。

**【数据范围】**

**本题使用捆绑测试。**

对于 $100\%$ 的数据，$1 \le T \le 10^6$，$1 \le n,\sum n \le 10^6$，$0 \le a_i,m,k \le 10^9$。

| 子任务编号 | $n \le$ | $m \le$ | $k \le$ | $a_i \le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $1$ | $10^9$ | $10^9$ | $10^9$ | 无 | $11$ |
| $2$ | $10^6$ | $0$ | $10^9$ | $10^9$ | 无 | $7$ |
| $3$ | $10^6$ | $10^9$ | $0$ | $10^9$ | 无 | $17$ |
| $4$ | $10^6$ | $10^9$ | $10^9$ | $0$ | 无 | $12$ |
| $5$ | $10$ | $10^6$ | $10^6$ | $10^6$ | $T = 1$ | $13$ |
| $6$ | $10^3$ | $10^6$ | $10^6$ | $10^6$ | $T = 1$ | $17$ |
| $7$ | $10^6$ | $10^9$ | $10^9$ | $10^9$ | 无 | $23$ |

## 样例 #1

### 输入

```
1
1 2 0
1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
7 354 480097
1 794 0 19 45 45 1
5 109588 312
1 16 34 375 47
1 333 0
646640```

### 输出

```
875
109951
646653```

# 题解

## 作者：blm_xxc (赞：14)

### [题目传送门](https://www.luogu.com.cn/problem/P12420)

## 思路

容易证明，每次操作总会选择 $m\gets x-m$ ，而不会选择花费 $k$ 的代价保持 $m$ 不变，因为最后要进行异或运算时，只关注每个 $a$ 在每一位上出现 $1$ 的次数的奇偶性，而不是次数(即不是次数越多越好)，所以对于 $m$ 的每一位 $1$，只需要使用一次即可。

**所以，本题的 $k$ 是没有用的！！！**

可以看作先将预处理出 $a$ 的异或和 $sum$，再将 $sum$ 与 $m$ 进行或运算。

但这么做并没有得到满分，why？

注意到，当每一个 $a$  在某一位上均为 $1$ 时，此时该位出现 $1$ 的次数无法改变(因为进行与运算只会使 $1$ 的个数越来越多，而无法减少)，所以当这一位的异或和为 $0$ 时，无法通过和  $m$  的与运算将其变为 $1$。

所以，我们要判断是否存在某些位，所有 $a$ 在这些位上均为 $1$。

此时，只需要增加一个变量 $p$ ，将其初始化为 $2^{31}-1$，每次输入时与 $a$ 进行与运算，即可判断在哪些位上所有 $a$ 均为 $1$。

最后，如何通过 $sum$，$m$ 和 $p$ 得出最后的答案 $ans$？

注意到，当某一位上 $sum$ 为 $1$ 时，$ans$ 在这一位上一定为 $1$；若 $sum$ 为0，则只有 $m$ 在这一位上为 $1$，p 在这一位上为 $0$ 时，$ans$ 才为$1$，由此可得：

-   $ans=sum|((m \oplus p)\&m)$ 

有了这个，本题就迎刃而解。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,k,ans,p;
inline int read(){
	int p=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') p=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return p*k;
}
int main(){
	T=read();
	while(T--){
		n=read(),m=read(),k=read(),ans=0,p=2147483647;
		for(int i=0;i<n;++i){
			int a;
			a=read();
			ans^=a;
			p&=a;
		}
		ans=ans|((m^p)&m);
		printf("%d\n",ans);
	}
	return 0;
}
```
加入快读以后可以跑到 100~200ms 哦！awa

---

## 作者：_hud (赞：10)

# 题解：[P12420 【MX-X12-T3】「ALFR Round 5」变换](https://luogu.com.cn/problem/p12420)

## 题目大意
给定非负整数序列 $a$ 以及参数 $m$ 和 $k$。每次操作选择一个非负整数 $x$ 满足 $x \ \& \ m = x$ 和一个下标 $i$，将 $a_i \gets a_i \ | \  x$。之后可以选择将 $m$ 减去 $x$ 或花费 $k$ 代价使得 $m$ 不变。求操作后数组的异或和减去总代价的最大值。

## 思路分析
由题意，本题的核心目标：
**通过操作改变 $a$ 的异或和，最大化 $(\oplus_{i=1}^{n} a_i) - s$。**

显然地，我们可以对这两部分分别进行分析。

### 异或和

根据异或的定义，不难得出以下性质：
**某二进制位异或和的结果由对应 $a$ 中该位 $1$ 个数的奇偶性决定。若该位 $1$ 个数是奇数，该位异或和的结果为 $1$；反之为 $0$**。

再次审题，注意到条件 $x \ \& \ m = x$。假设每次操作后都会选择 $m \gets m - x$，将上述公式转化为通俗一点的语言，即：

**在 $m$ 中取出任意为 $1$ 的数位，并添加到 $a_i$ 的对应数位上**。

进一步的，由上述性质可知，若 $a_i$ 的数位改变，相当于改变了 $a$ 中该位 $1$ 个数的奇偶性。如果改变后为奇数，且原来为偶数，那么这一位就成功对答案造成了贡献。分析到这里，不难想到这是**贪心**。具体来说：
 
>从高位到低位遍历：  
>   - 若 $m$ 的当前位 $b$ 为 $1$（允许操作该位）：  
>     - 检查初始异或结果第 $b$ 位是否为 $0$。  
>     - 检查是否存在 $a_i$ 第 $b$ 位为 $0$（即是否存在 $0$ 可以更改，如果全是 $1$ ，操作后 $a_i$ 的数位并不会发生改变）。  
>   - 若以上两个条件均满足，则操作该位一次，即将异或结果的 $b$ 位翻转，答案增加 $2^b$。

### 总代价

直接给出结论：**最优选择下，总代价恒等于 $0$**。

这个结论是显然的。根据上述性质，最后要进行异或运算时，只关注每个 $a$ 在每一位上 $1$ 出现次数的奇偶性，而不是次数（即不是次数越多越好）。所以每次操作总会选择 $m \gets m - x$。那么总代价自然也恒等于 $0$。

那么，这道题就迎刃而解了。实现可以看代码。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
// #define DEBUG 1
struct IO { // 快读快写模板
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
	inline char gc() {
#if DEBUG
      return getchar();
#endif
      if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
      return p1 == p2 ? ' ' : *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	template <class T>
	inline T read(T &x) {
		double tmp = 1; bool sign = 0;
		x = 0;
		char ch = gc();
		for(; !isdigit(ch); ch = gc())
			if (ch == '-') sign = 1;
    	for(; isdigit(ch); ch = gc()) x = x * 10 + (ch & 15);
    	if(ch == '.')
    		for(ch = gc(); isdigit(ch); ch = gc())
    			tmp /= 10.0, x += tmp * (ch - '0');
    	if(sign) x = -x;
		return x;
	}
  	inline void read(char *s) {
    	char ch = gc();
    	for(; blank(ch); ch = gc());
    	for(; !blank(ch); ch = gc()) *s++ = ch;
    	*s = 0;
  	}
  	inline void read(char &c) { for(c = gc(); blank(c); c = gc()); }
  	inline void push(const char &c) {
#if DEBUG
    	putchar(c);
#else
    	if(pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    	*pp++ = c;
#endif
  	}
	template <class T>
	inline void write(T x) {
		if (x < 0) x = -x, push('-');
    	static T sta[35];
    	T top = 0;
    	do {
      		sta[top++] = x % 10, x /= 10;
    	} while(x);
    	while(top) push(sta[--top] + '0');
  	}
  	template <class T>
  	inline void write(T x, char lastChar) {
    	write(x), push(lastChar);
  	}
} io;
int a[1000010], z[32];
inline void solve() {
	memset(z, 0, sizeof z); // 多测要清空
	int n, m, k, tmp = 0, res;
	io.read(n), io.read(m), io.read(k);
	for(int i = 1; i <= n; i++) 
		io.read(a[i]), tmp ^= a[i];
    // 统计每个位 '0' 的个数
	for(int b = 0; b <= 31; b++)
		for(int i = 1; i <= n; i++)
			z[b] += (!(a[i] & (1 << b)));
	res = tmp; // tmp 为原数组初始异或和
	for(int b = 0; b <= 31; b++) {
		if(!(m & (1 << b))) continue;
		if(!(tmp & (1 << b)) && z[b] >= 1) // 当前位可以对答案造成贡献且存在可操作数
			res += (1 << b);
	}
	io.write(res, '\n');
}
signed main() {
	int T; io.read(T);
	while(T--) solve();
	return 0;
}
```

## 进一步优化
注：本部分思路由同机房巨佬 [@blm_xxc](https://www.luogu.com.cn/user/189495) 提出。

根据原代码，不难观察到最耗时的部分是分别统计 $a$ 每位上的 $0$ 个数。故我们可以反方向思考：有没有更快捷的方法判断出是否存在某些位，而所有 $a_i$ 在这些位上均为 $1$ 呢？我们可以定义一个常量 $p$，将其每一二进制位上均设置为 $1$，每次输入进行 $a_i \ \operatorname{and} \ p$，即可判断在哪些位上所有 $a_i$ 均为 $1$。

综上，可得公式：

 $ans = sum \ \operatorname{or} \ ((m \ \operatorname{xor} \ p)\ \operatorname{and} \ m)$，其中 $sum$ 是原数组初始异或和。

这样写代码跑的飞快，在快读的加成下可以跑到 $146ms$。

## 优化后代码（部分）
```cpp
const int p = (1 << 31) - 1;
inline void solve() {
    int n, m, k, ans = 0;
    io.read(n), io.read(m), io.read(k);
    for(int i = 0; i < n; i++) {
        int x; io.read(x);
        ans ^= x, p &= x;
    }
    ans |= ((m ^ p) & m);
    io.write(ans, '\n');
}
```

---

## 作者：wmrqwq (赞：5)

出题人题解。

# 题目链接

[「ALFR Round 5」C 变换](https://www.luogu.com.cn/problem/P12420)

# 题意简述

有一个长度为 $n$ 的非负整数序列 $a$ 和两个参数 $m,k$。

你可以对序列 $a$ 进行任意次数的操作，对于每次操作，你都需要：

- 选取一个非负整数 $x$ 使得 $x \ \& \ m = x$，选取一个下标 $i \in [1,n]$，将 $a_i \gets a_i \ | \  x$，然后你需要将 $m \gets m - x$ 或者花费 $k$ 的代价使得 $m$ 不变。

记你花费的代价为 $s$，你需要求出 $(\oplus_{i=1}^{n} a_i) - s$ 的最大值。 

其中 $|$ 代表按位或运算，$\&$ 表示按位与运算，$\oplus$ 表示按位异或运算。

# 解题思路

首先注意到你操作后一定会选择 $m \gets m - x$，下面给出证明：

对于每个单独的二进制位，如果你在操作中选择了这一位，那么此时这一位的异或和显然为 $0$，否则你不操作这一位更优，那么操作后这一位的异或和变为 $1$，**不过前提条件是 $a$ 序列中这一位有至少一个 $0$**，否则你对这一位操作没有意义，所以对于每个单独的二进制位**最多**使用一次就可以达成最优情况。

因此给出的 $k$ 没有任何意义。

因此直接按位贪心即可，具体的，如果这一位上全为 $1$ 或者 $m$ 这一位为 $0$，直接统计这一位，因为此时你的任何操作都对这一位没有意义，否则你**一定**可以把这一位的异或和变为 $1$，直接统计即可。

时间复杂度 $O(n \log V)$，其中 $V$ 为值域。

# 参考代码

```cpp
ll n,m,k;
ll a[1000010];
ll ans,S;
void solve()
{
    cin>>n>>m>>k;
    forl(i,1,n)
        cin>>a[i];
    forr(i,35,0)
    {
        ll S=0;
        forl(j,1,n)
            S+=a[j]>>i&1;
        if(S==n)
        {
            if(S&1)
                ans+=pw(i);
            continue;
        }
        if((S&1) || (m>>i&1))
            ans+=pw(i);
    }
    cout<<ans<<endl;
    ans=0;
}
```

---

## 作者：Sunset_afterglow (赞：5)

### update（2025/5/6）：新增一组 Hack。

~~T3 好像只有大概普及组 T2 的难度。交了六发才过~~
# 思路
动动你聪明的小脑瓜想一想，$k$ 其实没有任何作用，毕竟重复操作题目中的运算，对答案并不会产生增加，去掉一个 $k$，题目是不是简单多了。  
一开始我想到的是，用 $m$ 的二进制的 $1$ 去对  $\oplus_{i=1}^{n} a_i$ 的二进制中对应位置的 $0$ 补位。你想想，这不就是按位或吗？此时你会发现好像是过不去的，因为我 60pts 卡了两发。  
这里我给出一组 Hack（感谢 [@YAOhc2012](https://www.luogu.com.cn/user/812227)）
```
input:
1
2 1 114514
1 1
output:
0
```
另外感谢 [Y_QWQ_Y ](https://www.luogu.com.cn/user/677091)提供一组新 Hack：
```
input:
1
4 7 1919810
1 3 5 7
output:
6
```
如果所有 $a_i$ 的二进制的第 $u$ 位都是 $1$，那么 $m$ 对此位的补位是无效的，注意当 $n$ 为偶数时，这种情况才会出现，解决办法，就是把都是 $1$ 的这一位（或是多位），从答案中减去。
# 代码
## 60pts
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
  int x = 0 ,f = 1;
  char ch = getchar();
  while('0' > ch || ch > '9'){
    if(ch == '-') f = -1;
    ch = getchar();
  }
  while('0' <= ch && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch & 15);
    ch = getchar();
  }
  return x * f;
}
const int N = 1e6 + 5;
int T ,n ,m ,k ,sum ,ans ,a[N];
void sovle() {
  ans = sum = 0 ,n = read() ,m = read() ,k = read();
  for(int i = 1;i <= n;++ i) {
    a[i] = read();
  }
  for(int i = 1;i <= n;++ i) sum ^= a[i];
    cout << (sum | m) << '\n';
  return ;
}
signed main() {
  T = read();
  while(T --)sovle();
  return 0;
}
```
## 100pts
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
  int x = 0 ,f = 1;
  char ch = getchar();
  while('0' > ch || ch > '9'){
    if(ch == '-') f = -1;
    ch = getchar();
  }
  while('0' <= ch && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch & 15);
    ch = getchar();
  }
  return x * f;
}
const int N = 1e6 + 5;
int T ,n ,m ,k ,tum ,sum ,ans ,a[N];
void sovle() {
  ans = sum = 0 ,n = read() ,m = read() ,k = read();
  for(int i = 1;i <= n;++ i) {
    a[i] = read();
  }
  for(int i = 1;i <= n;++ i) sum ^= a[i];
  int ans = (sum | m);
  if(!(n & 1)) {
    tum = a[1] & m;
    for(int i = 2;i <= n;++ i)tum &= a[i];
    ans -= tum;
  }
  cout << ans << '\n';
  return ;
}
signed main() {
  T = read();
  while(T --)sovle();
  return 0;
}
```

---

## 作者：jojo222 (赞：3)

题目里的与和或有点不太规范哈，我这里用 $\land$ 和 $\lor$。

首先，如果满足这三个条件：
1. $m$ 第 $k$（$1\le k\le30$）位二进制上为 $1$；
2. $\oplus_{i=1}^{n}a_i$ 这一位为 $0$ 的话
3. 有一个下标 $i \in [1,n]$ 使得 $a_i$ 这一位为 $0$，就相当于 $\land_{i=1}^{n}a_i$ 这一位为 $0$。

那可以用 $m$ 的这一位把原来的结果变为新的 $\oplus_{i=1}^{n}a_i\lor 2^k$。

所以，不需要花费任何代价！

这是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, k, a[1000001];
int main()
{
	cin >> t;
	while(t--)
	{
		scanf("%d%d%d", &n, &m, &k);
		int s = INT_MAX, ans = 0;
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]), s &= a[i], ans ^= a[i];
		for(int i = 1; i <= m; i <<= 1)
			if((m | i) == m && (ans | i) > ans && (s | i) > s)
				ans ^= i;
		printf("%d\n", ans);
	}
	return 0;
}
```

谢谢观看，求点赞。

---

## 作者：entelecheia_and_3 (赞：3)

### 前言
这题看着挺难，但是经过思考其实还好。~~在赛时似乎是个挺有区分度的题？~~

### 正文
题意还是挺好理解的，此处不赘述。后文关于位的概念均基于二进制。

要求 $(\oplus_{i=1}^{n} a_i) - s$ 的最大值，显然的是需要 $(\oplus_{i=1}^{n} a_i)$ 尽量大，$s$ 尽量小。考虑如何让异或和最大，对于每一位分别考虑，如果第 $x$ 位在答案中的异或和是 $0$，且 $m$ 第 $x$ 位是 $1$ 的话，我们可以随机对 $a$ 中一个第 $x$ 位为 $0$ 的数进行 $| 2^x$ 操作，这样相当于给异或和也 $| 2^x$。因此，我们需要一个 `workable` 数组，用以记录某一位是否可以进行 $|$ 操作，要求 $a$ 中至少存在一个数该位为 $0$。

再考虑是否要花费 $k$ 的代价使得 $m$ 不变。该操作的作用在于使得下次操作能够继续使用 $x$ 中所含的 $1$。但是由于异或的性质，这是没有意义的，$a$ 中两个某一位为 $0$ 的数进行 $|$ 操作，对答案并没有贡献。于是得出一个非常重要的结论：

* 一定不会花费 $k$ 的代价恢复 $m$，这样 $s$ 便是 $0$ 了。

### 一些细节
* 对于一个数最高位以上的位，均可以进行操作，只需考虑最小的数，代码中用 `maxi` 记录。
* `workable` 数组的大小只需要 $32$ 即可，不要开大，记得要清空。

```cpp
#include<bits/stdc++.h>
#define rise(i,l,r) for(int i=l;i<=r;i++)
#define pii pair<int,int>
#define div cout<<"\n____________________\n";
#define db cout<<"work\n";
using namespace std;
const int maxn=1e6+10;
int t,a[maxn],n,m,k,ans,maxi;
bool workable[40];

void divid(int x) {
    int i=0;
    while(x) {
        if((x&1)==0) workable[i] = true;
        i++;
        x >>=1;
    }
    maxi = min(maxi, i-1);
}

void in() {
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        ans ^= a[i];
        divid(a[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin >> t;
    while(t--) {
        maxi = INT_MAX;
        ans = 0;
        memset(workable, false, sizeof workable);
        in();
        for(int i=0; m; m >>=1, i++) {
            if(((m & 1) == 0) || ((ans >> i) & 1)) continue;
            if(workable[i]) ans |= (1 << i);
        }
        cout << ans << endl;
    }
    return 0;
}

---

## 作者：guoshengyu1231 (赞：2)

# 前言
一看到这题，映入眼帘的首先就是那密密麻麻的符号。即使读懂了题目也很难找到突破口。甚至感觉像一道深奥的数学题一样。但这题却只评了黄，那是不是说这题其实很简单？答案是正确的，我可以很认真的告诉你，这题其实就是到大水题！看着如此复杂的题面其实这是为了掩盖它水的本质！只要看透了这题究竟是让我们干什么，其实就跟一道模拟水题差不多。话不多说，直接上思路。
# 思路
首先题目中出现的或运算、与运算和异或运算都是基于二进制的，那我们干脆将所有的数都转换成二进制。那我们在来看题目，题目中要求我们选取一个非负整数 $ x $ 使得 $x$ $\land$ $m=x$。其实就是让我们选出一个二进制集合 $x$，使得 $m\supseteq x$。因为如果集合 $x$ 中所有的 $1$ 在集合 $m$ 中都有，那他们进行按位与一下依然不会变。接下来让我们选取一个下标 $i\in [1,n]$，将 $a_i\gets a_i\lor x$。其实就是让我们将 $a_i$ 的某一位置 $1$。然后就是让我们求所有数异或一下的值。
 $\\$ 

接下来我们需要进一步理解题意，因为我们是要看透题目的意思。如果光看表面这题是很难找到突破口的。啥? 你说 $k$ 有什么用，你仔细去读题，其实 $k$ 就是来误导我们的，他根本就没什么用，因为我们根本就不需要让 $m$ 不变。我为什么这么说，因为我们想让 $m$ 不变无非就是想让选取的一个 $x$ 可以操作多次。但每一位异或最终肯定只会有两种值，要么是 $0$，要么是其他的。我们要改变这一位，只是不想让这一位异或后做出的贡献为 $0$，那么最多肯定只需要一次就行了。所以输入的 $k$ 纯纯是来误导我们的，我们根本就不用管。 $\\$ 

回到正题，既然我们要选取一个集合 $x$ 来改变所有数的总异或值，那我们可以枚举所有二进制位，来判断一下当前位究竟要不要改变。如果要改变，记录改变后的答案。枚举完全部二进制位后，输出答案，这题就做完了。
# 实现
大致思路已经有了，接下来我们需要思考如何将我们的思路用代码实现。
-  首先，每次输入一个数，先将答案与这个数进行异或，然后就是将其转化为二进制的形式。
   -  对于这个二进制数的每一位，如果这一位是 $0$，说明这一位是可以进行改变的。这时候就需要一个布尔数组 $f$ 来记录第 $i$ 位是否可以改变。
-  接下来，枚举 $i$ 为所有的位，需要判断以下情况：
   -  如果当前答案中这一位异或已经有值了，那我们直接跳过。
   -  如果 $i\notin m$，那也是直接跳过。
   -  如果此时 $f_i$ 的值为假，说明这一位没有 $0$，照样直接跳过。
   -  只有当以上三个条件都不成立，那么才能更新答案。
  
**注意事项：** 每一个数最高位以上的位均为 $0$，所有均可以进行操作。所以应该在第一步枚举每个数的二进制位时应该枚举所有二进制位，而不是单单只枚举每个数有限的二进制位。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
void solve()
{
	int n,m,k,x,ans=0;
	bool f[40];
	memset(f,0,sizeof f);
	cin>>n>>m>>k;
	while(n--)
	 {
	 	cin>>x;ans^=x;
	 	int bit=0;
	 	for(int i=1;i<=35;i++)//这里千万不能写成while(x)
	 	 {
	 	 	if((x&1)==0) f[bit]=true;
	 	 	x>>=1;bit++;
		 }
	 }
	for(int i=0;(1<<i)<=m;i++)
	 {
	 	if((ans>>i)&1) continue;
	 	if(((m>>i)&1)&&f[i]) ans|=(1<<i);
	 }
	cout<<ans<<"\n";
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Invisible_H (赞：1)

## P12420 【MX-X12-T3】「ALFR Round 5」变换

### Problem
给定 $n,m,k$ 和序列 $a$，你可以进行任意次操作：选取一个非负整数 $x$ 使得 $x \ \& \ m = x$，选取一个下标 $i \in [1,n]$，将 $a_i \gets a_i \ | \  x$，然后你需要将 $m \gets m - x$ 或者花费 $k$ 的代价使得 $m$ 不变。

记你花费的代价为 $s$，你需要求出 $(\oplus_{i=1}^{n} a_i) - s$ 的最大值。 

### Solution


首先你会发现 $k$ 没啥用，因为选相同的 $m$ 一定不会优。

然后考虑二进制拆位和贪心，最优策略就是把 $a_i$ 中的 $0$ 变成 $1$，所以你会发现 $a_i$ 没啥用，只有 $a_i$ 的异或和还有与和有用。记与和为 $A$，枚举二进制位，如果 $A$ 的某一位为 $0$ 并且 $m$ 的某一位为 $1$，那么就可以改，可以直接或出代价和，设这是二进制下第 $i$ 位，这一次操作的代价就是 $2^i$，把前面的异或和或上 $2^i$，最后就是最小代价。

### Code
注意判二进制位是 $1$ 和 $0$ 的时候的括号，被这个卡了一会。


```cpp
inline void solve() {
	Fastio::cin >> n >> m >> k;
	int A = (1ll << 31) - 1, B = 0;
	for(int i = 1; i <= n; i++){
		Fastio::cin >> a[i]; 
		A &= a[i];
		B ^= a[i];
	}
	for(int i = 0; i < 31; i++){
		if((((m >> i) & 1) == 1) && (((A >> i) & 1) == 0)){
			B |= (1ll << i);
		}
	}
	Fastio::cout << B << '\n';
}
```

---

## 作者：MnZnOIer (赞：1)

本场第 9 名庆祝一下发个题解（实际上是因为太久没写题解开始掉社贡导致的）。

#### 解题思路
看到了二进制操作，按位考虑。我们可以先不考虑代价,令 $\bigoplus_{i=1}^n{a_i}$ 最大，再考虑代价最小。我们先将 $\bigoplus_{i=1}^n{a_i}$ 算出来，记为 $s$。显然，如果二进制下某一位不为 1 并且 $m$ 在二进制下这一位为 1，显然可以通过操作把答案中的这一位变成 1。我们顺着这个思路，把所有的能用的都用成一次就可以令结果最大，答案即为 $s | m$。至此，我们可以发现，只需要一次操作就可以了，再操作也对答案没有影响。

但这个是对的吗？答案是，错的。显然可以找到反例：$n$ 为偶数并且所有 $a_i$ 的某一位都为 1，$m$ 的这一位也为 1，那么你无论怎么给 $a_i$ 或都无法使答案中这一位为 1。所以把 $s|m$ 减去多算的所有 $a_i$ 的与和与上 $m$，当且仅当 $n$ 为偶数时。

#### 代码部分
那么我们就得到了正解，下面给出代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, m, k, a;
void solve ()
{
    cin >> n >> m >> k;
    int s = 0, sy = m;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a;
        s ^= a;
        sy &= a;
    }
    cout << (s | m) - (! (n & 1)) * sy << '\n';
}
signed main ()
{
    ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
    cin >> t;
    while (t --)solve ();
    return 0;
}
```
###### 说句闲话，由于数据太水，上面说的错解能拿 60 pts，并且达到只错两个点的境界。

---

## 作者：BennyT (赞：1)

# 题解：P12420 【MX-X12-T3】「ALFR Round 5」变换
## 思路
首先可以发现 $x$ 一定是 $m$ 所包含的 $2$ 的幂次相加，因为题目中所进行的运算都是位运算，所以每一个 $2$ 的幂次无法影响其他 $2$ 的幂次，所以我们可以将每一位分开处理。

可以先将原本 $a_i$ 的异或和算出来，然后看 $m$ 可以补哪一位，因为每一位都是分开来算，所以题目中的“花费 $k$ 的代价使得 $m$ 不变”实际上是没有作用的，有原本 $m$ 无法补的 $2$ 的幂次无法通过这个操作补齐。

举个例子，比如 $a_i$ 的异或和为 $1010$（使用二进制表示），$m$ 为 $1100$，在补足 $2^2$ 后最终答案为 $1110$，我们无法通过任何操作使答案的 $2^0$ 的幂次被补足，不信的自己试试。

还有一个细节，就是如果每个 $a_i$ 都拥有某个 $2$ 的幂次，则该幂次无法被补足，因为 $m$ 进行的是按位或运算。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,m,k,a[1000010];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		ll num=0,y=(1ll<<30)-1;//y为记录所以a_i所拥有的2的幂次（不会有人像我一样把y初始化为0或a_1而只拿了60分吧）
		for(int i=1;i<=n;i++){
			cin>>a[i];
			num^=a[i];//记录异或和
			y&=a[i];
		}
		for(int i=0;(1ll<<i)<=m;i++){//枚举异或和的每一位
			if((((1ll<<i)&y)==0)&&((1ll<<i)&m)){//如果该位可以被补足
				num|=(1ll<<i);
			}
		}
		cout<<num<<'\n';//endl曾使我的代码的时间翻了20倍导致超时
	}
	return 0;
}
```

---

## 作者：LittleAcbg (赞：1)

这道题其实入手点很多，有比较多的性质。例如答案式 $\oplus_{i=1}^na_i$，可以考虑二进制拆位，每一位都独立考虑。这时就可以注意到，二进制每一位在整个序列中都只需要做最多一次有效按位或运算。

有效按位或运算就是把二进制从 $0$ 变成 $1$ 的过程。上述结论的证明也很简单，因为每次有效或运算会导致序列异或和该位从 $0$ 变 $1$ 或从 $1$ 变 $0$。而为了使异或和最大，我们显然不希望从 $1$ 变 $0$ 的情况出现，所以这一位只需要做一次有效或运算即可。

那么，考虑贪心的思想，我们同时需要最小化 $s$ 即操作代价，所以能省操作就省操作，我们尽量保证每次或运算都是有效的。

再观察题目中给出的操作。由于每一个二进制位最多或一次（假设有效），那么题目中的 $k$ 就没有用了，每个二进制位或完就不用了，不需要使用 $k$ 的代价去保持 $m$ 的值。

现在我们只需要保证每次或运算有效就行。每次操作都只取 $m$ 的一个二进制位，然后找到一个没有这个二进制位（即这一位上是 $0$）的 $a_i$ 并对其操作。我们开局处理好异或和，然后对每个异或和没有的二进制位进行这个操作就行了。

这时还有一个问题，怎么找到（或确定是否存在）没有某个二进制位的 $a_i$？这个题目没有要求输出操作方案，只需要判断是否存在。我们可以计算出所有 $a_i$ 的按位与，如果按位与这一位是 $0$，那就存在没有这一位的 $a_i$。

代码实现上参考点：

1. 使用 `scanf` 的 `%*d`，输入 $k$ 但不存储。
2. 按位与的初始值必须有足够多的二进制 $1$，`INT_MAX` 就是一个很好的选择。
3. 不用判断异或和的某一位是不是 $0$，能操作的位直接或上就可以了。这样的话，这一位如果本来是 $1$ 就不受影响，本来是 $0$ 就能变 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a;
void mian()
{
    scanf("%d%d%*d", &n, &m); // k 无效，不存储
    int xsum = 0,asum = INT_MAX; // INT_MAX 是 2^31-1，可以作为 & 操作的 INF
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a);
        xsum ^= a; // 计算异或和与 & 和
        asum &= a;
    }
    for (int i = 0; i <= 30; ++i) if ((m >> i & 1) && (asum >> i & 1 ^ 1)) // 如果 m 有这一位并且存在某个 a 没有这一位
        xsum |= (1 << i); // 这一位强制变 1（如果本来已经是 1 了也没关系）
    printf("%d\n", xsum);
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i) mian(); // 多组测试数据处理
    return 0;
}
```

---

## 作者：swate114514 (赞：1)

## 题意
给定非负整数序列 $a$，参数 $m, k$，通过以下操作最大化目标值 $ans$：  
$$ans = \left( \bigoplus_{i=1}^n a_i \right) - s$$  
其中 $s$ 为总代价。操作规则为：  
1. 选择满足 $x \ \& \ m = x$ 的非负整数 $x$，将 $a_i \gets a_i \ | \ x$。  
2. 选择扣除 $m$（$m \gets m - x$）或花费代价 $k$ 保留 $m$。

## 思路
读完题，容易想到这道题可以用贪心去实现。关键在于贪心策略。

我们观察一下异或运算的每一位独立贡献最终结果。设初始异或和为：  
$$X_{\text{init}} = a_1 \oplus a_2 \oplus \dots \oplus a_n$$  
目标是最大化每一位的贡献，高位优先处理（权重为 $2^j$）。

统计每个二进制位 $j$ 上未被设置的 $a_i$ 数量：  
$$\text{cnt}[j] = \sum_{i=1}^n \left[ (a_i \ \& \ 2^j) = 0 \right]$$  
其中，中括号中为指示函数，条件成立时值为 1。

从高位到低位遍历每个二进制位 $j$：  
- $m$ 的第 $j$ 位可用（$m \ \& \ 2^j \neq 0$）。  

- 当前异或和的第 $j$ 位为 0（$X \ \& \ 2^j = 0$）。  

- 存在可设置的 $a_i$（$\text{cnt}[j] > 0$）。  


当满足上述条件时，翻转该位：  
$$X \gets X \oplus 2^j$$  
并扣除 $m$ 的该位（等价于 $m \gets m - 2^j$ 或位运算优化 $m \gets m \oplus 2^j$）。

将 $2^j$ 设置到奇数个 $a_i$ 上（通常选 1 个元素）。  

  设修改后的异或和为：  
  $$X_{\text{new}} = X_{\text{init}} \oplus 2^j$$  
  增益为 $2^j$（原异或和该位为 0）。  

扣除 $m$ 的 $j$ 位后，后续操作无法使用更高位的资源，需确保当前决策的局部最优性。

若每次操作选择花费 $k$ 保留 $m$，需满足：  
$$2^j - k > 0$$
即
$$2^j > k$$  
否则选择扣除 $x$。原代码隐含假设 $k=0$（总选择不花费代价），此时最优策略无需考虑代价。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 30; // 处理最高30位

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(n);
        int xors = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            xors ^= a[i];
        }
        
        vector<int> cnt(N + 1, 0);
        for (int j = 0; j <= N; ++j) {
            int mask = 1 << j;
            for (int x : a) {
                if ((x & mask) == 0) cnt[j]++;
            }
        }
        
        // 从高位到低位贪心处理
        for (int j = N; j >= 0; --j) {
            int bit_mask = 1 << j;
            if (!(m & bit_mask)) continue;    // 条件1：m的j位可用
            int cur_bit = (xors >> j) & 1;
            if (cur_bit == 1) continue;       // 条件2：异或和j位为0
            if (cnt[j] == 0) continue;        // 条件3：存在可设置的a_i
            
            xors ^= bit_mask;                // 翻转异或位
            m ^= bit_mask;                   // 扣除资源（等价于m -= bit_mask）
        }
        
        cout << xors << '\n';
    }
    return 0;
}
```

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12420)。
## 思路
注意到让 $m$ 反复改变结果的同一个二进制位不会产生更多的贡献，所以花费 $k$ 的代价是没有意义的。

于是可以进一步发现，若 $a_i$ 的异或和中某一位为零而 $m$ 这一位为 $1$ 时，就可以通过让一个这一位为零的 $a_i$ 或上它以对答案产生贡献。

实现的时候要注意，需记录 $a_i$ 异或和的那些位是可以改变的，否则会误改，导致答案错误。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5,P=35;
int t,n,m,k;
int a[N],s1[P],s2[P],F[P],J[P];
//J 记录哪些位可以被改变
int main() {
	cin>>t;
	while(t--) {
		cin>>n>>m>>k;
		int ans=0,mnl=114514;
		for(int i=1;i<P;i++) J[i]=1;
		for(int i=1;i<=n;i++) {
			cin>>a[i];
			int f=a[i],l=0;
			while(f) J[++l]&=(f%2),f/=2;//对 a_i 拆位
			mnl=min(mnl,l);
			ans^=a[i];
		}
		int f=ans,l=0,f2=m,l2=0;
		while(f) s1[++l]=f%2,f/=2;//对异或和拆位
		while(f2) s2[++l2]=f2%2,f2/=2;//对 m 拆位
		ans=0;
		for(int i=max(l,l2);i>=1;i--) {//计算答案
			ans=ans*2+s1[i];
			if(s1[i]==0&&s2[i]==1&&(J[i]==0||i>mnl)) ans++; 
		}
		cout<<ans<<endl;
		for(int i=1;i<=max(l,l2);i++) s1[i]=s2[i]=0;//多测清空
	}
}
```

---

## 作者：r1sing (赞：0)

## 前言
很有趣的一道题，但是样例有点水（TAT）。
## 正篇
首先题面是要求 $x~\&~m = x$，那么也就是在二进制下 $x$ 为 $1$ 的位置，在 $m$ 的对应位置也必须是 $1$。那么考虑枚举 $m$ 的二进制的 $1$ 的位置，对于每一位计算可以产生的贡献并计算答案。首先，知周所众，异或这个运算相同为 $0$ 不同为 $1$。那么肯定要么在某一位进行一次操作，要么不进行操作（因为偶数次操作就等于不做操作，奇数次操作等于做一次操作）。那么如果现在这一位异或起来为 $0$ 那么就需要做一次操作，来使其变为 $1$ 来增加答案，如果已经是 $1$ 了就不需要做操作了，根据这个结论就可以写出满分代码了。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll t;
ll n, m, k;
ll a[1000006];
void work()
{
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	ll x = 0;
	for(int i = 0; i < 31; i++)
	{
		if((m & (1 << i)) == 0)
			continue;
		ll cnt = 0;
		for(int j = 1; j <= n; j++)
			cnt += ((a[j] & (1 << i)) > 0);
		if(cnt % 2 == 0)
    		for(int j = 1; j <= n; j++)
                if((a[j] & (1 << i)) == 0)
                {
                    a[j] |= (1 << i);
                    break;
                }
	}
	ll ans = 0;
	for(int i = 1; i <= n; i++)
	    ans ^= a[i];
	cout << ans << "\n";
	return ;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);     cout.tie(0);
	ll t;
	cin >> t;
	while(t--)
		work();
	return 0;
}
```

---

