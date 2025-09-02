# Bitwise Balancing

## 题目描述

# 位运算平衡


给定三个非负整数 $ b $ 、$ c $ 和 $ d $ 。

请找到一个非负整数 $ a \in [0, 2^{61}] $ 使得 $ (a\, |\, b)-(a\, \&\, c)=d $ ，其中 $ | $ 和 $ \& $ 分别表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)和[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

如果存在这样的 $ a $ ，请输出它的值。如果没有解，请输出整数 $ -1 $ 。如果存在多个解，输出其中任意一个。

## 说明/提示

在第一个测试用例中，$ (0\,|\,2)-(0\,\&\,2)=2-0=2 $ 。因此，$ a = 0 $ 是一个正确答案。

在第二个测试用例中，没有任何值 $ a $ 满足方程。

在第三个测试用例中，$ (12\,|\,10)-(12\,\&\,2)=14-0=14 $ 。因此，$ a = 12 $ 是一个正确答案。

## 样例 #1

### 输入

```
3
2 2 2
4 2 6
10 2 14```

### 输出

```
0
-1
12```

# 题解

## 作者：postpone (赞：9)

对于这类带加减法的位运算，可以先看看有没有进位退位的情况，再按位判断。

观察题目要求实现的等式 $(a\, |\, b)-(a\, \&\, c)=d$，可以发现是没有退位的情况的，由于与运算和或运算的性质， $(a\ |\ b)$ 一定不比 $(a\ \&\ c)$ 小。

按位看，列出真值表，这题就做出来了。

| $b$ | $c$ | $d$ | $a = f(b, c, d)$ |
|:-:|:-:|:-:|:-:|
|0|0|0|0|
|0|0|1|1|
|0|1|0|任意|
|0|1|1|不行|
|1|0|0|不行|
|1|0|1|任意|
|1|1|0|1|
|1|1|1|0|

因为只有三个自变量，可以直接分类讨论，如下：
```cpp
// 其中 a[], b[], c[], d[] 为 a, b, c, d 的拆位
bool ok = true;
for (int i = 0; i < 64; i++) {
    if (b[i] == 0 and c[i] == 0 and d[i] == 0) {
        a[i] = 0;
    } else if (b[i] == 0 and c[i] == 0 and d[i] == 1) {
        a[i] = 1;
    } else if (b[i] == 0 and c[i] == 1 and d[i] == 0) {
        a[i] = 1;
    } else if (b[i] == 0 and c[i] == 1 and d[i] == 1) {
        ok = false;
    } else if (b[i] == 1 and c[i] == 0 and d[i] == 0) {
        ok = false;
    } else if (b[i] == 1 and c[i] == 0 and d[i] == 1) {
        a[i] = 1;
    } else if (b[i] == 1 and c[i] == 1 and d[i] == 0) {
        a[i] = 1;
    } else if (b[i] == 1 and c[i] == 1 and d[i] == 1) {
        a[i] = 0;
    }
}
```

还可以从真值表中化简，得到更优雅的结论：
```cpp
void solve() {
    ll b, c, d;
    cin >> b >> c >> d;

    ll a = b ^ d;
    if ((a | b) - (a & c) == d) {
        cout << a << "\n";
    } else {
        cout << -1 << "\n";
    }
}
```

---

## 作者：Meickol (赞：1)

一道打表分类讨论找规律的二进制拆位题。

对于这类带加减法的位运算，首先分析使用二进制拆位的做法是否会存在借位的情况。

根据与运算和或运算的性质，$(a\ |\ b)\ge a，(a\ \&\ c) \le a$，因而 $(a\, |\, b)$ 一定不小于 $(a\, \&\, c)$。

因而不存在退位的情况，直接用二进制拆位解决即可。



考虑二进制拆位，枚举二进制下各个变量对应的第 $i$ 位二进制数。

因为 $a$ 的值是我们需要构造出来的，我们可以任意控制 $a$ 在第 $i$ 位的选值。不难发现：

- 当 $d$ 的第 $i$ 位为 $1$ 时：
  - 若 $b$ 的第 $i$ 位为 $1$：
    - 若 $a$ 在第 $i$ 位的值选 $0$，这时无论 $c$ 在第 $i$ 位的值如何都可以构成答案。
    - 若 $a$ 在第 $i$ 位的值选 $1$，这时 $c$ 在第 $i$ 位的值必须为 $0$，否则无解。
  - 若 $b$ 的第 $i$ 位为 $0$：
    - 若 $a$ 在第 $i$ 位的值选 $1$，这时 $c$ 在第 $i$ 位的值必须为 $0$，否则无解。
    - 若 $a$ 在第 $i$ 位的值选 $0$，无解。
- 当 $d$ 的第 $i$ 位为 $0$ 时：
  - 若 $b$ 的第 $i$ 位为 $0$：
    - 若 $a$ 在第 $i$ 位的值选 $0$，这时无论 $c$ 在第 $i$ 位的值如何都可以构成答案。
    - 若 $a$ 在第 $i$ 位的值选 $1$，这时 $c$ 在第 $i$ 位的值必须为 $1$，否则无解。
  - 若 $b$ 的第 $i$ 位为 $1$：
    - 若 $a$ 在第 $i$ 位的值选 $0$，无解。
    - 若 $a$ 在第 $i$ 位的值选 $1$，则 $c$ 在第 $i$ 位的值必须为 $1$，否则无解。



你当然可以直接分类讨论将上述过程模拟实现。

但是为了优雅地解决本题，故决定再从中寻找一些规律。

不难发现：

- 当 $d$ 和 $b$ 在第 $i$ 位上的值相等时，我们直接让 $a$ 在第 $i$ 位的值选 $0$ 即可，这样不需要关注 $c$ 的情况。
- 当 $d$ 和 $b$ 在第 $i$ 位上的值不相等时，$a$ 在第 $i$ 位上的值只能选 $1$，且 $c$ 在第 $i$ 位上的值必须和 $b$ 的情况相同。



于是可以写出下方代码：

```cpp
#define per(x,y,z) for(int x=y;x>=z;x--)
typedef long long LL;
LL b,c,d;
void solve(){
	LL a=0;
	cin>>b>>c>>d;
	per(i,61,0){
		if( ((d>>i)&1) != ((b>>i)&1) ){
			if( ((b>>i)&1) != ((c>>i)&1) ) return cout<<-1,void();
			else a|=(1LL<<i);
		}
	}
	cout<<a;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

由于 $a\ |\ b\ge a$，$a\ \&\ c\le a$，减法也不会出现借位情况。

枚举二进制下的第 $i$ 位。若 $d$ 的第 $i$ 位为 $1$，此时如果 $b$ 的第 $i$ 位也为 $1$，那么 $a$ 的第 $i$ 位为 $0$；否则 $a$ 的第 $i$ 位必须为 $1$，此时如果 $c$  的第 $i$ 位为 $1$ 则无解。若 $d$ 的第 $i$ 位为 $0$，此时如果 $b$ 的第 $i$ 位也为 $0$，那么 $a$ 的第 $i$ 位为 $0$；否则 $a$ 的第 $i$ 位必须为 $1$，此时如果 $c$  的第 $i$ 位为 $0$ 则无解。

# Code

```cpp
#include<bits/stdc++.h>
int T;
long long a,b,c,d;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&b,&c,&d);
		a=0;
		for(int i=61;~i;--i)
			if((d>>i&1)^(b>>i&1))
				if((c>>i&1)^(b>>i&1))a=-1,i=0;
				else a|=1ll<<i;
		printf("%lld\n",a);
	}
	return 0;
}
```

上面的代码可以简化成下面这个。

```cpp
#include<bits/stdc++.h>
int T;
long long b,c,d;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&b,&c,&d);
		if(((b^d)&b)^((b^d)&c))puts("-1");
		else printf("%lld\n",b^d);
	}
	return 0;
}
```

---

## 作者：yangxikun (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF2020C) [CF](https://codeforces.com/problemset/problem/2020/C)

### 题目大意

给你三个非负整数 $b$，$c$，和 $d$。

请找出一个非负整数 $a \in [0, 2^{61}]$，使得 $(a\operatorname{OR}b)-(a\operatorname{AND}c)=d$。

如果存在 $a$，请输出其值。如果没有解，则输出 $-1$。如果有多个解，则打印任意一个。

### 解法

一道二进制题。

可以对每一位进行考虑。把 $b$，$c$，$d$ 三个数每一位取出来，这样 $a$ 的每一位只有两种可能：$0$ 或 $1$，再判断两种情况是否可以，即把原先对数的判断转换为对每一个 bit 的判断。

具体细节请参见代码。

### 代码

[CF 提交记录](https://codeforces.com/contest/2013/submission/284727060)\
（代码块展示 solve 函数部分，ll 为 long long。）
```cpp
void solve(){
	ll b,c,d;
	cin>>b>>c>>d;
	ll a=0;
	bool fail=0;//记录是否未找到
	for(int bit=0;bit<60;bit++){//循环每一位
		int bb=(b>>bit)&1;//取出b从右往左第bit+1位
		int cc=(c>>bit)&1;//同上
		int dd=(d>>bit)&1;//同上
		vector<int> v;
		if((0|bb)-(0&cc)==dd)v.push_back(0);
		if((1|bb)-(1&cc)==dd)v.push_back(1);
		if(v.empty()){
			fail=1;
			break;
		}//判断是否成立
		a|=ll(v[0])<<bit;//记得类型转换，否则可能会溢出
	}
	cout<<(fail?-1:a)<<endl;//输出答案
}
```

---

## 作者：qfy123 (赞：1)

# CF2020C
[CF传送门](https://codeforces.com/contest/2020/problem/C)
## Solution
### 赛时思路
先将 $b,c,d$ 按二进制位拆出来。发现对于二进制下的每一位，都要满足这个等式，记 $x$ 当前的二进制位的值为 $nowx$，那么，我们分情况讨论：

1. $nowd = 0$。那对于这个二进制位，考虑能否构造形如 $1 - 1 = 0$ 或 $0 - 0 = 0$ 这样的等式。为此，当且仅当 $\exist nowa \in [0,1]$，满足 $nowa\operatorname{or} nowb=nowa\operatorname{and} nowc=1$ 或 $nowa\operatorname{or}nowb=nowa\operatorname{and}nowc=0$ 其中一个条件时，才有解，否则无解。
2. $nowd = 1$。此时要判断这个二进制位能否构造出形如 $1 - 0 = 1$ 的等式，同上分类讨论即可。

时间复杂度 $O(T \log V)$。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define PB push_back
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int mx = 2305843009213693952LL;
int T,b,c,d;
signed main(){
	T = R();
	while(T--){
		b = R(), c = R(), d = R();
		int ans = 0;
		bool f = 0;
		rep(i,0,62){
			int nowb = (b >> i) & 1, nowc = (c >> i) & 1, nowd = (d >> i) & 1, nowa = 0;
        	if((nowb | nowa) - (nowc & nowa) != nowd){
				if(nowd){
					if(!nowb && nowc){f = 1; break;}//发现这种情况下无论如何都构造不出来形如 1 - 0 = 0 的等式，所以无解。
					else if(!nowb && !nowc) nowa = 1;//当nowb = nowc = 0 时，当且仅当 nowa = 1，才能够构造出形如 1 - 0 = 0 的等式 
				}else{
					if(nowb && !nowc){f = 1; break;}// 发现这种情况下无法构造出形如 1 - 1 = 0 或 0 - 0 = 0 的等式，因此无解。
					else if(nowb && nowc) nowa = 1; //当nowb = nowc = 1 时，当且仅当 nowa = 1，才能构造出形如 1 - 1 = 0 的等式。
				}
        	}
        	ans |= (nowa << i);
		}
		if(f || ans > mx) out(-1, 2);
		else out(ans, 2);
	}
	return 0;
}
```
### 另一种解法
手玩几个样例发现，如果有解，那么就一定有 $\forall nowa$，满足 $nowa = nowb \operatorname{xor} nowd$。于是直接令 $a = b \operatorname{xor} d$，然后判断这个 $a$ 是否满足条件即可。

时间复杂度 $O(T)$。
### Code

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
 
signed main(){
	int T = R();
	while(T--){
		int b = R(), c = R(), d = R();
		int ans = b ^ d; //直接令 a = b ^ d
		if(((ans | b) - (ans & c)) == d) out(ans, 2);//满足条件就输出 a 
		else out(-1, 2);//否则无解，输出 -1
	}
 
	return 0;
}
```

---

