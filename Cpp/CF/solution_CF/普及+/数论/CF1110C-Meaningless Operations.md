# Meaningless Operations

## 题目描述

Can the greatest common divisor and bitwise operations have anything in common? It is time to answer this question.

Suppose you are given a positive integer $ a $ . You want to choose some integer $ b $ from $ 1 $ to $ a - 1 $ inclusive in such a way that the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ a \oplus b $ and $ a \> \& \> b $ is as large as possible. In other words, you'd like to compute the following function:

 $ $$$f(a) = \max_{0 < b < a}{gcd(a \oplus b, a \> \& \> b)}. $ $ </p><p>Here  $ \\oplus $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#XOR">bitwise XOR operation</a>, and  $ \\& $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#AND">bitwise AND operation</a>.</p><p>The greatest common divisor of two integers  $ x $  and  $ y $  is the largest integer  $ g $  such that both  $ x $  and  $ y $  are divided by  $ g $  without remainder.</p><p>You are given  $ q $  integers  $ a\_1, a\_2, \\ldots, a\_q $ . For each of these integers compute the largest possible value of the greatest common divisor (when  $ b$$$ is chosen optimally).

## 说明/提示

For the first integer the optimal choice is $ b = 1 $ , then $ a \oplus b = 3 $ , $ a \> \& \> b = 0 $ , and the greatest common divisor of $ 3 $ and $ 0 $ is $ 3 $ .

For the second integer one optimal choice is $ b = 2 $ , then $ a \oplus b = 1 $ , $ a \> \& \> b = 2 $ , and the greatest common divisor of $ 1 $ and $ 2 $ is $ 1 $ .

For the third integer the optimal choice is $ b = 2 $ , then $ a \oplus b = 7 $ , $ a \> \& \> b = 0 $ , and the greatest common divisor of $ 7 $ and $ 0 $ is $ 7 $ .

## 样例 #1

### 输入

```
3
2
3
5
```

### 输出

```
3
1
7
```

# 题解

## 作者：AThousandSuns (赞：9)

在我的博客上看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/10355991.html)

这可能是我打那么多次CF比赛时，做出来的最难的一道题了……而且这题也是个绝世好题……

打几个表，我们发现如果 $a$ 的二进制表示中含有 $0$，比如 $100101100...$，也就是说不能表示成 $2^k-1$，那么他的答案就是所有 $2^k-1$ 中比 $a$ 大的最小的一个。

~~（虽然这个规律不是我打表找到的，是自己推出来的）~~

为什么呢？如果我们令 $b$ 为 $a$ 的位取反，那么 $a\&b=0,a\oplus b=2^k-1$。所以答案就是 $2^k-1$。可以证明答案不可能超过 $2^k-1$。

那么 $a=2^k-1=(11111...)_2$ 怎么办呢？似乎大多数人都是暴力打出一个表然后直接调用的……

我的做法是：我们发现对于一个 $1\le b<a$，有 $a\&b=b,a\oplus b=a-b$。

那么 $\gcd(a\&b,a\oplus b)=\gcd(b,a-b)=\gcd(a,b)$！！！

$\gcd(a,b)$ 的最大值？就是 $a$ 的最大因数（不包括 $a$ 自己）。

总复杂度 $O(q\sqrt{a})$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	char ch=getchar();int x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int q,n;
int main(){
	q=read();
	while(q--){
		n=read();
		int c=1;
		while(c<=n) c<<=1;
		if(n!=c-1) printf("%d\n",c-1);
		else{
			bool flag=false;
			for(int i=2;i*i<=n;i++)
				if(n%i==0){printf("%d\n",n/i);flag=true;break;}
			if(!flag) printf("1\n");
		} 
	}
}
```

---

## 作者：lsy_41 (赞：4)

拿到题目，映入眼帘的是 $a_i$ 巨大的范围，同时还有多组输入，那这样看来，一定是有什么规律了，但规律是啥不知道，那就可以先打个表看看。
```cpp
#include <bits/stdc++.h>
using namespace std;
int gcd(int n, int m) {
	return m == 0 ? n : gcd(m, n % m);
}
int main() {
	for (int a = 1; a < 100; a++) {
		int ans = 0;
		for (int b = 1; b < a; b++) {
			ans = max(ans, gcd(a ^ b, a & b));
		}
		cout << a << " " << ans << endl;
	}
	return 0;
}
```
拿到输出一看，许多都是连续的相同的数，而且可以大胆猜测，就是将其二进制全部补成 $1$ 然后再减去 $1$ ，但这好像并不是对于所有数，再一看发现，不满足的数都是 $2^k\,-\,1$ ，而 $k$ 最多只到 $2\,5$ ，这样一来，只要处理这些数不久好了嘛。

但是我们通过大眼观察法得到的结论到底对不对呢，其实稍加思考就可以证明，当 $b$ 为 $a$ 按位取反时，此时 $a$ ^ $b$ 最大，为 $2^k\,-\,1$ ，同时 $a$ & $b$ 等于 $0$ ，这时 $\gcd$ 刚好就是 $2^k\,-\,1$ ，同时对于等于 $2^k\,-\,1$ 的数来说，$b$ 应该为 $0$ ，但取不到，所以就打表处理就好啦。

人性化的打表程序：
```cpp
#include <bits/stdc++.h>
using namespace std;
int gcd(int n, int m) {
	return m == 0 ? n : gcd(m, n % m);
}
int main() {
	cout << "int F[100] = { 0";
	for (int n = 1; n <= 25; n++) {
		int ans = 0, a = pow(2, n) - 1;
		for (int b = 1; b < a; b++) {
			ans = max(ans, gcd(a ^ b, a & b));
		}
		cout << "," << ans;
	}
	cout << "};";
	return 0;
}
```

最后就是提交的代码啦。
```cpp
#include <bits/stdc++.h>
using namespace std;
int T, a;
int F[100] = { 0,0,1,1,5,1,21,1,85,73,341,89,1365,1,5461,4681,21845,1,87381,1,349525,299593,1398101,178481,5592405,1082401 };
int main() {
	cin >> T;
begin:
	cin >> a;
	int x = log2(a + 1) + 1;
	if (!(a & (a + 1))) {
		cout << F[x - 1] << endl;
	}
	else {
		cout << (1 << x) - 1 << endl;
	}
if (--T) goto begin;
	return 0;
}
```

一定要自己体验打表的乐趣哦。

完结撒花！

---

## 作者：ChthollyTree (赞：3)

题意 

多组询问 一个数a 求出一个 b (1 <= b < a)使得gcd(a xor b,a and b)最大，输出最大值

经过打表可以知道 大多数情况最大值都是 $2^{[log_{2}a]+1} $-1 （[]表示向下取整）

具体原因是因为我们可以找到一个b，在a的二进制最高位及以下全部按位取反 因为此时b比a少一位，所以b 一定小于a

这时候 a xor b就为$2^{[log_{2}a]+1} $-1 ，a and b为 0 

则答案就是$2^{[log_{2}a]+1} $-1

而又因为 a xor b , a and b 都是不可能大于 $2^{[log_{2}a]+1} $-1的（不然二进制就多一位了）

所以$2^{[log_{2}a]+1} $-1一定是最大值

看起来挺合理的，但是总是有意外。当a 为 $2^{k} - 1$时，我们无法按照上面的做法找到一个b

不过由于这样的数最多25个，我们可以暴力打表


打表程序
```
#include<bits/stdc++.h>
using namespace std;
 
int n,m;

int gcd(int x,int y)
{
	if(y == 0) return x;
	return gcd(y,x%y);
}

int f(int x)
{
	int ans = 0;
	int o = 0;
	for(int i = 1; i < x; i ++)
	{
		if(gcd(x^i,x&i) > ans)
			o = i;
		ans = max(ans,gcd(x^i,x&i));
	}
	return ans;
}
int main()
{
	int x;
	for(int i = 1; i <= 25; i ++)
	{
		int x = (1<<i)-1;
		cout<<"s["<<x<<"]="<<f(x)<<";\n";
	}
	return 0;
}
```

提交程序

```
#include<bits/stdc++.h>
using namespace std;

map<int,int>s;
int T,n,m; 

int main()
{
	cin >> T;

s[1] = 0;
s[3] = 1;
s[7] = 1;
s[15] = 5;
s[31] = 1;
s[63] = 21;
s[127] = 1;
s[255] = 85;
s[511] = 73;
s[1023] = 341;
 ... //剩下是打表，略

	
	while(T --)
	{
		int n ;
		cin >> n;
		if(s.count(n))
		{
			cout<<s[n]<<"\n";
		} else {
			cout<<(1<<(((int)(log2(n)))+1))-1<<"\n";; 
		}
	}
	return 0;
}
```



---

## 作者：仁和_童博扬 (赞：2)

## 题目大意：
定义函数$ f(a) $为 $$ f(a)=\max_{0<b<a}\gcd(a\oplus b,a\ \&\ b) $$
给出 $q$  个询问，每个询问为一个整数$ a_i $。你需要对于每个询问，求出 $ f(a_i)$ 的值。

## 思路
看到这道题，我的第一反应是打表，不管打不打得下表，都得先打暴力，于是有了以下这个暴力的程序：
```cpp
//Sooke & LJC00118 bless me
//memset0 & lijian3256 ddjxd
//iWApD3 & Spfa tql
//LJB00125 & LJB00127 吊打 LJB00126
//wangyujia will help me
#include<bits/stdc++.h>
using namespace std;
int a[1005];
int gcd(int a, int b){ return a == 0 ? b : gcd(b % a, a);}
//忽略这个gcd函数ovo，本来打算用的，结果想想还是__gcd()好用QwQ
int main()
{
	int q;
	scanf("%d",&q);
	for(int i = 1; i <= q; i++)
	{
		scanf("%d",&a[i]);
		int ans = 0;
		for(int b = 1; b < a[i]; b++)
		{
			int x = a[i] | b, y = a[i] & b;
			int u = __gcd(x,y);
			ans = max(ans,u);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
还抱着试试看的心理交了一下，没想到：  
`00:55:03  Time limit exceeded on pretest 2 [pretests] → 49582424`  
数据居然这么强？！  
好吧，乖乖打表。。。   
打表的程序跑啊跑，我去看D。  
结果D看完了，不会，再看E，写完，交上去，WA。  
打表的程序还没跑完……   
等不及了，关掉它，打开生成的txt。  
一看。What!怎么这么多一样的？   
### 表1：  
0,3,1,7,7,7,1,15,15,15,15,15,15,15,5,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,1,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,21,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,1,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255……  
肯定有规律，写了个程序，打出更加高级的表：  
### 表2： 
```
[开始的编号-结束的编号](重复的次数) 该数字
[1-1](1) 0
[2-2](1) 3
[3-3](1) 1
[4-6](3) 7
[7-7](1) 1
[8-14](7) 15//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[15-15](1) 5
[16-30](15) 31//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[31-31](1) 1
[32-62](31) 63//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[63-63](1) 21
[64-126](63) 127//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[127-127](1) 1
[128-254](127) 255//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[255-255](1) 85
[256-510](255) 511//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[511-511](1) 73
[512-1022](511) 1023//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[1023-1023](1) 341
[1024-2046](1023) 2047//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[2047-2047](1) 89
[2048-4094](2047) 4095//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[4095-4095](1) 1365
[4096-8190](4095) 8191//重复的次数为前一个非重复数字的编号，且前一个非重复数字出现且仅出现一次
[8191-8191](1) 1
……
```
哇！好像找到规律了~（见表里的注释）  
## ~~这道题的本质——复读机~~   
于是简单轻松快乐地打出了这样一个程序~~~   
```cpp
//Sooke & LJC00118 bless me
//memset0 & lijian3256 ddjxd
//iWApD3 & Spfa tql
//LJB00125 & LJB00127 吊打 LJB00126
//wangyujia will help me
#include<bits/stdc++.h>
using namespace std;
int wyj[25] = {3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767,65535,131071,262143,524287,1048575,2097151,4194303,8388607,16777215,33554431,67108863};
bool check[67108869];
int ans(int x)
{
	if(x == 1)	return 0;
	if(x == 2)	return 3;
	if(check[x])
	{
		int a = x, out = 0;
		for(int b = 1; b < a; b++)
		{
			int x = a | b, y = a & b;
			int u = __gcd(x,y);
			out = max(out,u);
		}
		return out;
	}
	else
		for(int i = 0; i < 25; i++)
			if(x <= wyj[i])
				return wyj[i];
	return -1;
}
int main()
{
	for(int i = 0; i < 25 ; i++)
		check[wyj[i]] = 1;
	int q, tby;
	scanf("%d",&q);
	for(int i = 1; i <= q; i++)
	{
		scanf("%d",&tby);
		printf("%d\n",ans(tby));
	}
	return 0;
}
```
结果得到了`01:52:10  Time limit exceeded on pretest 3 [pretests] → 49595216`   
这数据也太TMD强了o(╥﹏╥)o  
好吧，我投降。算出每个转折点的$ans$单独记录进数组里，然后特判。  
最后`01:56:13  Accepted [main tests] → 49596255`的代码：
```cpp
//Sooke & LJC00118 bless me
//memset0 & lijian3256 ddjxd
//iWApD3 & Spfa tql
//LJB00125 & LJB00127 吊打 LJB00126
//wangyujia will help me
#include<bits/stdc++.h>
using namespace std;
int wyj[25] = {3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767,65535,131071,262143,524287,1048575,2097151,4194303,8388607,16777215,33554431,67108863};
int qwq[25] = {1,1,5,1,21,1,85,73,341,89,1365,1,5461,4681,21845,1,87381,1,349525,299593,1398101,178481,5592405,1082401,22369621};
bool check[67108869];
int ans(int x)
{
	if(x == 1)	return 0;
	if(x == 2)	return 3;
	if(check[x])
	{
		for(int i = 0; i < 25; i++)
			if(wyj[i] == x)
				return qwq[i]; 
	}
	else
		for(int i = 0; i < 25; i++)
			if(x <= wyj[i])
				return wyj[i];
	return -1;
}
int main()
{
	for(int i = 0; i < 25 ; i++)
		check[wyj[i]] = 1;
	int q, tby;
	scanf("%d",&q);
	for(int i = 1; i <= q; i++)
	{
		scanf("%d",&tby);
		printf("%d",ans(tby));
	}
	return 0;
}
```
### ~~嗯，这真是一道打表的好题啊！！！~~  
（挖了个小小的坑，代码被我拿掉了两个字符qwq）

---

## 作者：Hooch (赞：0)

读了题之后，我们看样例。

样例解释里面有个很离谱的东西是 $\operatorname{gcd}(0,x)=x$。

~~于是我们就可以愉快地乱搞了。~~

可以发现 $\max(a\oplus b, a\ \&\ b)$ 中的 $b$ 为 $a$ 的取反时，这将会是最大的，此时值为 $a+b$。

然后这个时候 $a\ \&\ b=0$。

所以 $\max(a\oplus b, a\ \&\ b) = a + b$。

当然还有一种情况，就是 $a=2^k-1$ 时。

这个时候 $a$ 的取反 $b$ 是 $0$，题目中不允许这个情况。

推不出任何结论，~~于是就打了个表~~。

暴力打表：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i(j); i <= n; ++i)
#define rep2(i, j, n) for (int i(j); i >= n; --i)
#define il inline
using namespace std;
template <typename T>
il void read(T &x) {
   x = 0; T f = 1; char ch = getchar();
   while (!isdigit(ch)) x = (ch == '-') << 1, ch = getchar();
   while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar();
   x *= f;
}
const int N = 1e5 + 5, inf = 0x3f3f3f3f;
il int gcd(int x, int y) {
	if (y % x == 0) return x;
	else return gcd(y % x, x);
} //gcd
main() {
	for (int i = 2; i <= 25; ++i) {
		int j = (1 << i) - 1; int ans = 0;
		for (int k = 1; k < j; ++k) ans = max(ans, gcd(min(k ^ j, k & j), max(k ^ j, k & j))); //暴力打答案
		printf("%lld, ", ans); //输出后复制
	}
}
```

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (int i(j); i <= n; ++i)
#define rep2(i, j, n) for (int i(j); i >= n; --i)
#define il inline
using namespace std;
template <typename T>
il void read(T &x) {
   x = 0; T f = 1; char ch = getchar();
   while (!isdigit(ch)) x = (ch == '-') << 1, ch = getchar();
   while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar();
   x *= f;
}
const int N = 1e5 + 5, inf = 0x3f3f3f3f;
int q, x, f[30] = {0, 0, 1, 1, 5, 1, 21, 1, 85, 73, 341, 89, 1365, 1, 5461, 4681, 21845, 1, 87381, 1, 349525, 299593, 1398101, 178481, 5592405, 1082401}; //表
main() {
	read(q);
	while (q--) {
		read(x); double y = log2(x + 1);
		if (ceil(y) == y) printf("%d\n", f[(int)y]); //判断是不是 2^i-1的情况
		else {
			int k = (int)ceil(y), p = (1 << k) - x - 1;
			printf("%d\n", p ^ x);
		}
	}
}
```

---

## 作者：Mr_Wu (赞：0)

我们设$\lceil \log_2 a \rceil=t$，可以理解为$a$在二进制下有$t$位。

第一个结论是

$$gcd(a \oplus b, a \, \& \, b) \le 2^t-1$$

，因为$a \oplus b\le 2^t-1$，$a \,\&\, b\le 2^t-1$所以有此结论。

第二个结论是

> 当$b$在二进制下每一位都和$a$是反的时，$gcd$能取到$2^t-1$

因为此时$a \,\&\, b=0$，$a \oplus b=2^t-1$

举个例子，$a$在二进制下表示为$110$，此时$b$取$001$，$\gcd$取到最大$111$

而我们又发现如果$a$能表示为$2^k-1$，此时$b=0$，不满足$0<b<a$

所以我们一开始将$2^1-1,2^2-1,\cdots,2^{25}-1$的数记下来，就能每次$\log a$处理(求$\log$是$\log$复杂度吧..?）

总结一下：$\lceil \log_2 a \rceil=t$，如果$a$不能表示为$2^k-1$，直接输出$2^t-1$，否则将预处理的表中的值输出。

以上结论比赛时可以通过打表找规律得出。

---

## 作者：dudubao2007 (赞：0)

本蒟蒻第一次发题解~~，格式我就不管了~~。

题目要求f(a):当整数b取遍1到a-1的所有值时，gcd(a Xor b,a And b)的最大值。

我做的时候，首先做了一件很有意思的事：

利用恒等式a Xor b=a+b-2*a And b

为什么？大家开动脑筋自己去想：a Xor B和a+b到底有什么联系？具体我就不说破了，大家自己想，公式都摆在了上面。

那好，gcd(a Xor b,a And b)=gcd(a Xor b+2*a And b,a And b)=gcd(a+b,a And b)

于是有两种情况：
第一种：a的二进制的所有数码都是1

比如说a=1111（十进制15）

那么显然就有a And b=b

所以求的是gcd(a+b,b)也就是gcd(a,b)的最大值啦，也就是a的非a的最大约数啦。那么如果a是质数，答案就是1，否则，就先找它非1的最小约数，用a一除，搞定！

还有一种：a的二进制的所有数码不都是1

比如说a=1110（十进制14）

那么显然就有gcd(a+b,a And b)<=a And b<a

但是如果a And b=0的话就十分有趣了，那么gcd(a+b,a And b)=a+b！采取这种方法效果一定好！那么a+b的最大值就是比a大的最小的二进制所有数码都是1的数（对于a=1110，这个数是1111），这就是答案。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f(int x)
{
    int i;
    for (i=1;i*2<=x+1;i*=2);
    if (i==x+1) 
	{
		for (int j=2;j*j<=x;j++)
		  if (x%j==0) return x/j;
		return 1;
	} 
    else
      return 2*i-1;
} 
int main()
{
	int n;
	cin>>n;
	for (int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		cout<<f(x)<<endl;
	}
	return 0;
}

```

---

## 作者：onglu (赞：0)

## 题意
给定$q$个数，要求每个数$a$找到一个$b(1\le b< a)$使得$gcd(a$ $xor$ $b,a$ $and$ $b)$最大。

## 分析
我们分两类讨论。

第一类：$a$不是$2^k-1$时，这时候我们发现我们只要让$a$ $and$ $b=0$，$a$ $xor$ $b=2^k-1$就可以了。

重点在第二类：打表找规律，发现如果$a$是质数时，答案为$1$，否则答案为$a$的最大真因子。

我怕$a$很大又是质数的时候可能会超时，用的是Miller-Rabbin算法判断的质数。

## 代码 
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll test[109]={2,3,5,7,11,61,24251,13,17,23};
ll read(){
	char c;ll num,f=1;
	while(c=getchar(),!isdigit(c))if(c=='-')f=-1;num=c-'0';
	while(c=getchar(), isdigit(c))num=num*10+c-'0';
	return f*num;
}
ll Pow(ll a,ll p,ll mod){
    ll ans=1;
    for(;p;p>>=1,a=1ll*a*a%mod)
        if(p&1)ans=1ll*ans*a%mod;
    return ans;
}
bool check(ll P){
    if(P==1)return 0;
    ll k=0,t=P-1;
    while(!(k&1))k++,t>>=1;
    for(int i=0;i<10;i++){
        if(P==test[i])return 1;
        ll a=Pow(test[i],t,P),nxt;
        for(int j=1;j<=k;j++){
            nxt=(1ll*a*a)%P;
            if(nxt==1&&a!=1&&a!=P-1)return 0;
            a=nxt;
        }
        if(a!=1)return 0;
    }
    return 1;
}
int ct(ll x){
	ll t=1;int flag=0;
	while(t<=x){
		if((x&t)==0)flag=1;
		t<<=1;
	}
	if(flag)return t;
	else return -1;
}
int main()
{
	int q=read();
	for(int i=1;i<=q;i++){
		ll a=read();
		ll b=ct(a);
		if(!(~b)){
			if(check(a))printf("1\n");
			else {
				for(ll i=2;i<a;i++){
					if(a%i==0){
						cout<<(a/i)<<endl;
						break;
					}
				}
			}
		}else cout<<(b-1)<<endl;
	}
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

首先将$a$分两种情况讨论：  
1. $a=2^k-1(k\in N^*)$
2. $a\not=2^k-1(k\in N^*)$

对于第一种情况，我们发现$a$的二进制是$111...1$，那么在$[1,a-1]$之间任取一个整数$b$，$a\oplus b$和$a\& b$的和是$a$，而且他们对$a$是互补（$a\&b$取$a$中的某些$1$，$a\oplus b$就是另一些1）的，所以我们很容易得到一个结论（不会证QAQ）：$a\oplus b$与$a\& b$成倍数关系，也就是说他们的$GCD$是二者的较小值，因此我们枚举最小的质因数$x$就可以得出答案是$a/x$。  

对于第二种情况，这种情况更为简单，因为$a$的形式是$1$和$0$混杂，我们只需要$b$中将$a$里面所有是$0$的位置取$1$，那么$a\&b=0$，而$a\oplus b=2^k-1$（这里的$2^k-1$指的是$a$最高位的$1$以下的位全是$1$的数），此时最小的$GCD$就是$2^k-1$。  

综合上述结论，这题就做完了。   
复杂度$O(q\sqrt{a})$
```cpp
#include <bits/stdc++.h>
#define jh(x,y) x^=y^=x^=y
#define lowbit(x) (x&-x)
#define rg register
#define inl inline
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
using namespace std;
namespace fast_IO {
    inl ll read()
    {
        rg ll num = 0;
        rg char ch;
        rg bool flag = false;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        if (ch == EOF)return ch; if (ch == '-')flag = true; else num = ch ^ 48;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            num = (num << 1) + (num << 3) + (ch ^ 48);
        if (flag)return -num; return num;
    }
    inl int chread(rg char s[])
    {
        rg int len = 0;
        rg char ch;
        while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\r');
        s[len++] = ch;
        while ((ch = getchar()) != ' '&&ch != '\n'&&ch != '\r'&&~ch)
            s[len++] = ch;
        s[len] = 0;
        return len;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg long long x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
};
map<ll, bool>mp;

int main(void)
{
    rg int q = fast_IO::read();
    for (rg int i = 1; i <= 25; ++i)mp[(1 << i) - 1] = true;
    while (q--)
    {
        rg ll a = fast_IO::read();
        if (!mp[a])
        {
            rg ll tmp = a, first = 0;
            while (tmp)tmp >>= 1, ++first;
            fast_IO::write((1 << first) - 1);
        }
        else
        {
            rg int minn = a;
            for (rg ll i = 3; i*i <= a; i += 2)
                if (a%i == 0) { minn = i; break; }
            fast_IO::write(a / minn);
        }
        putchar('\n');
    }
    return 0;
}

```

---

## 作者：xukuan (赞：0)

数学题&&暴力打表法+瞪眼法找规律，类似NOIP2018tgD2T2

最大公约数的定义应该是这样的：

```cpp
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
```

## 对于每一个输入，把他们转换成二进制

1.如果不全是1，把它变成1，直接输出（大家都知道）

2.如果全是1，输出他除本身外的最大因子（这里直接证明比较烦，应该写一个程序辅助一下,类似NOIP2018tgD2T2）

辅助程序
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}

int main(){
	ll x=3;
    //输入肯定不会是1，所以(11)2=(3)10
	while(1){
		ll ans=0;
		for(ll i=1; i<x; i++){//穷举1到x-1
			ans=max(ans,gcd(x&i,x^i));//判断
		}
		printf("%lld %lld\n",x,ans);//输出
		x=(x+1)*2-1;//x被扩大
	}
}
```

运行上面的程序，结果如下：
```pascal
3 1
7 1
15 5
31 1
63 21
127 1
255 85
511 73
1023 341
2047 89
4095 1365
8191 1
16383 5461
32767 4681
65535 21845
131071 1
262143 87381
524287 1
1048575 349525
2097151 299593
4194303 1398101
8388607 178481
16777215 5592405
268435455 89478485
```

运用暴力打表法+瞪眼法算出规律。

这样节省时间，在codeforces两个小时解决8题的情况下最划算

最终AC代码：(codeforces评测id：49590919)，我的比赛代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll q;

int main(){
	cin>>q;
	while(q--){
		ll x;
		scanf("%I64d",&x);
		ll y=1;//y从1开始倍增
		while(y<=x) y*=2;//y一路翻倍，我不喜欢用位运算
		y--;
		if(y==x){//如果全是1
			ll TOP=ceil(sqrt(x));//sqrt这种东西直接放到循环终止条件中，时间会变大很多
			bool bo=true;
			for(ll i=2; i<=TOP; i++){
				if(x%i==0){//能被整除
					printf("%I64d\n",x/i);
					bo=false;
					break;
				}
			}
			if(bo) printf("1\n");//一个质数，除本身外的最大因子是1，输出1
		}
		else printf("%I64d\n",y);//如果不全是1，直接输出y
	}
	
	return 0;
}
```

---

