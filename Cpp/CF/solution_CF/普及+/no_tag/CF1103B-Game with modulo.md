# Game with modulo

## 题目描述

This is an interactive problem.

Vasya and Petya are going to play the following game: Petya has some positive integer number $ a $ . After that Vasya should guess this number using the following questions. He can say a pair of non-negative integer numbers $ (x, y) $ . Petya will answer him:

- "x", if $ (x \bmod a) \geq (y \bmod a) $ .
- "y", if $ (x \bmod a) < (y \bmod a) $ .

We define $ (x \bmod a) $ as a remainder of division $ x $ by $ a $ .

Vasya should guess the number $ a $ using no more, than 60 questions.

It's guaranteed that Petya has a number, that satisfies the inequality $ 1 \leq a \leq 10^9 $ .

Help Vasya playing this game and write a program, that will guess the number $ a $ .

## 说明/提示

In the first test, you should play $ 3 $ games with Petya's numbers $ 1 $ , $ 2 $ and $ 3 $ .

In the first game, Petya will answer "x" (without quotes) to any question, because $ (x \bmod 1) = 0 $ for any integer $ x $ .

In the second game, if you will ask pair $ (0, 0) $ , the answer will be "x" (without quotes), because $ (0 \bmod 2) \geq (0 \bmod 2) $ . But if you will ask pair $ (2, 5) $ , the answer will be "y" (without quotes), because $ (2 \bmod 2) < (5 \bmod 2) $ , because $ (2 \bmod 2) = 0 $ and $ (5 \bmod 2) = 1 $ .

## 样例 #1

### 输入

```
start
x
x
start
x
x
y
start
x
x
y
y
end
```

### 输出

```
? 0 0
? 10 1
! 1
? 0 0
? 3 4
? 2 5
! 2
? 2 4
? 2 5
? 3 10
? 9 1
! 3
```

# 题解

## 作者：shucai (赞：7)

# [题目传送门](https://www.luogu.com.cn/problem/CF1103B)
## 题意
让你猜一个数 $a$ ，你每次可以猜两个数 $x$ 和 $y$ ，如果若 $(x\bmod a) ≥ (y \bmod a)$ 返回 $x$，否则返回 $y$ 。

## 思路
猜数字升级版。

我们想到猜数字是每次猜最中间的那个数 $mid$ ，比我们要猜的数大就把猜测范围从 $(l,r)$ 缩小到  $(l,mid)$ ,比他小就缩小到 $(mid,r)$ 。那么我们这题可以借鉴这个思路，题目是让我们给两个数，那我们可不可以利用这两个数，缩小猜测范围呢？

答案是肯定的，我们每次可以猜 一个$2x$，一个 $x$，如果 $(2x\bmod a) ≥ (x \bmod a)$ ， 那么我们就能确定 $x <= a <= 2x$ ，具体实现可以用到二分答案。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
int len;
inline void check(int &l, int &r) {
    do {
        printf("? %lld %lld\n", l, r);
        cin >> s;

        if (s[0] == 'y') {
            l = r;
            r <<= 1;
        }
    } while (s[0] == 'y');
}
signed main() {


    cin >> s;

    while (s.size() != 3 && s.size() != 7) {
        int l = 0, r = 1;
        check(l, r);

        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            printf("? %lld %lld\n", mid, l);
            cin >> s;

            if (s[0] == 'x')
                l = mid;
            else
                r = mid;
        }

        printf("! %lld\n", l + 1);
        cin >> s;
    }

    return 0;
}

```


---

## 作者：PPL_ (赞：2)

# 前言

人生第一道交互题，竟是加强版猜数字？

想想交互就好~~激动~~DT呢

# 题目

[洛谷](https://www.luogu.com.cn/problem/CF1103B)

[CF](http://codeforces.com/problemset/problem/1103/B)

# 讲解

首先我们考虑无解的情况，假设当前位为$i(1\le i\le \frac{n}{2})$，则对面为$i+\frac{n}{2}$，如果他们相隔的距离为奇数，则永远不可能相等，因为相邻两个数的差的绝对值是$1$

如果相隔距离是奇数，则$\frac{n}{2}$是奇数，则$n$不是$4$的倍数(题目已给$n$是偶数)

接下来我们考虑解法

$1e9$的范围，$100$次询问？

那就是$O(log(n))$呀

**倍增**！(别问我怎么想到的)

我们需要找到一个$x$，使得$x<a\le 2x$

假设你询问$?\ x\ 2x$

如果回答$x$，则$x<a\le 2x$

如果回答$y$，则$x<2x<a$，继续倍增

如果$a\le x$怎么办？

你就是从前面倍增过来的，会这样吗？

当然，在最开始的时候要特判$1$

得到了$x$，使得$x<a\le 2x$之后，我们怎么找呢？

记得$O(log(n))$吗？

**二分**！

当然$l=x,r=2x$

如果$Ask(l,mid)==x$，说明什么？

说明$l>mid\pmod a$，但是实际上$l < mid$，所以$l<a\le mid$，$r=mid$(赋值)

反之，$l=mid$

搞定

# 代码
```cpp
//12252024832524
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std; 

typedef long long LL;
const int MAXN = 15;
const int MAXA = 1000000000;
int n;
char opt[MAXN];

int Read()
{
	int x = 0,f = 1;char c = getchar();
	while(c > '9' || c < '0'){if(c == '-')f = -1;c = getchar();}
	while(c >= '0' && c <= '9'){x = (x*10) + (c^48);c = getchar();}
	return x * f;
}
void Put1(int x)
{
	if(x > 9) Put1(x/10);
	putchar(x%10^48);
}
void Put(int x,char c = -1)
{
	if(x < 0) putchar('-'),x = -x;
	Put1(x);
	if(c >= 0) putchar(c);
}
template <typename T>T Max(T x,T y){return x > y ? x : y;}
template <typename T>T Min(T x,T y){return x < y ? x : y;}
template <typename T>T Abs(T x){return x < 0 ? -x : x;}

bool Ask(int x,int y)
{
	printf("? %d %d\n",x,y);fflush(stdout);
	scanf("%s",opt);
	return opt[0] == 'x';
}

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	while(520)
	{
		scanf("%s",opt);
		if(!strcmp(opt,"end")) break;
		if(Ask(0,1))
		{
			printf("! 1\n");fflush(stdout);
			continue;
		}
		int l,r;
		for(int i = 1;i <= MAXA;i <<= 1)
		{
			if(Ask(i,Min(i << 1,MAXA << 1)))
			{
				l = i;
				r = Min(i << 1,MAXA << 1);
				break;
			}
		}
		while(l + 1 < r)
		{
			int mid = (l+r) >> 1;
			if(Ask(l,mid)) r = mid;
			else l = mid;
		}
		printf("! %d\n",r);fflush(stdout);
	}
	return 0;
}
```

---

## 作者：miaokehao (赞：2)

首先log2(1e9)=29~30

所以我们询问次数复杂度约为2*log(a)

所以就类似二分的思路如果出现第一组(2x mod A)<(x mod A)，就可以确定x<=A<=2x，然后在里面二分，具体实现看代码
```
#include <bits/stdc++.h>
#define res register int
#define len s.size()
using namespace std;
string s;
inline int read(){
	res w=0,X=0;register char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){X=(X<<1)+(X<<3)+(ch^48);ch=getchar();}
	return w?-X:X;
}
inline void exact(res &l,res &r){
	do{
		printf("? %d %d\n",l,r);
		cin>>s;
		if(s[0]=='y') l=r,r<<=1;
	}while(s[0]=='y');
}
int main(){
    cin>>s;
    while(len!=3&&len!=7){
    	res l=0,r=1;
    	exact(l,r);
//    	printf("%d %d\n",l,r);
    	while(l+1<r){
    		res mid=l+r>>1;
    		printf("? %d %d\n",mid,l);
    		cin>>s;
    		if(s[0]=='x') l=mid;
    		else  r=mid;
		}
		printf("! %d\n",l+1);
		cin>>s;
	}
	return 0;
}

```

---

## 作者：_sys (赞：2)

首先考虑，我们如果得知$x \mod a \geq 2x \mod a$，那么$\lfloor \frac{2x}{a} \rfloor \geq 1$ 所以$a \leq 2x$

于是我们只要找到一个区间满足$x \leq a \leq 2x$即可二分

若$2mid \mod a \leq mid \mod a$,就向下二分，否则向上

这个区间我们可以通过倍增查找

我们首先令$x = 1$，每次$x$扩倍询问$x$和$2x$，便可以找到这个区间。

注意特判$1$，其实也可以在前面判

倍增至多$30$次，二分至多$29$次（因为是$l=x$，$r=2x$）
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,l,r,cnt; 
string str,res;
int main()
{
	cin>>str;
	while(str!="end")
	{
		cnt=0;
		for(long long i=1;;i<<=1)
		{
			printf("? %lld %lld\n",i,min(2000000000LL,i*2)),cnt++;
			fflush(stdout);
			cin>>res;
			if(res=="x")
			{
				l=i,r=(int)min(1000000000LL,i*2);
				break;
			}
		}
		while(l+1<=r)
		{
			int mid=(l+r)/2;
			printf("? %d %d\n",2*mid,mid),cnt++;
			fflush(stdout);
			cin>>res;
			if(res=="x")
				r=mid;
			else l=mid+1;
		}
		if(l==2)
		{
			printf("? 2 1\n");
			fflush(stdout);
			cin>>res;
			if(res=="x")
			{
				printf("! 1\n");
				fflush(stdout);
				goto A;
			}
			else
			{
				printf("! 2\n");
				fflush(stdout);
				goto A;
			}
		}
		printf("! %d\n",l);
		fflush(stdout);
		A:cin>>str;
	}
	return 0;
}
```


---

## 作者：acniu (赞：1)

贡献一波随机化乱搞做法。

容易发现，若 $x<y$ 且 $x\bmod a\ge y\bmod a$ ，则 $(x,y]$ 内一定有 $a$ 的倍数。因此若 $x=y-1$ 则一定 $a|y$ 。

因此，我们先随机几次，找出满足条件的一对 $x,y$ （成功概率应该至少 $1/4$ ？），然后找出 $[x,y]$ 中点 $m$，那么 $(x,m)$ 与 $(m,y)$ 中一定至少有一个合法的数对，于是可以在 $O(\log)$ 次查询内定位到一个 $a$ 的倍数 $w$。

然后对于 $w$ 的每个质因子，二分其在 $a$ 中的出现次数。这里蒟蒻盲猜 $10$ 次左右应该能完事。

实测 $a$ 取 $10^9$ 时貌似最容易被卡，平均需要
 $40$ 次询问， $10^4$ 次测试中一般只有不到 $30$ 次会询问过多，最大询问次数一般不超过 $80$。
 
代码：
```cpp
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int query(int x, int y) {
	printf("? %d %d\n", x, y);
	fflush(stdout);
	char str[100];
	scanf("%s", str);
	if (*str == 'e')
		exit(0);
	return *str == 'x';
}
void quit(int x) {
	printf("! %d\n", x);
	fflush(stdout);
}

#define ll long long

int p[100], c[100], tot;
void factorize(int n) {
	tot = 0;
	for (ll i = 2; i * i <= n; i++) if (n % i == 0) {
		p[++tot] = i, c[tot] = 0;
		while (n % i == 0)
			c[tot]++, n /= i;
	}
	if (n > 1)
		p[++tot] = n, c[tot] = 1;
}

//#define rand() rand() & 0x7fff
inline int rnd__() {
	ll x = rand();
	x = x * (RAND_MAX + 1ll) + rand();
	x = x * (RAND_MAX + 1ll) + rand();
	return x & 0x7fffffff;
}
inline int rnd() {
	int x = rnd__();
	while (x > 2000000000)
		x = rnd__();
	return x;
}

void solve() {
	int x, y;
	while (1) {
		x = rnd(), y = rnd();
		if (x > y) swap(x, y);
		if (query(x, y))
			break;
	}
	while (x < y - 1) {
		int m = (0ll + x + y) >> 1;
		if (query(x, m))
			y = m;
		else
			x = m;
	}
	factorize(y);
	int answer = y;
	for (int i = 1; i <= tot; i++) {
		int tmp[100] = {1};
		for (int j = 1; j <= c[i]; j++)
			tmp[j] = tmp[j - 1] * p[i];
		int l = 1, r = c[i], ans = 0;
		while (l <= r) {
			int m = (l + r) >> 1;
			if (query(y / tmp[m] - 1, y / tmp[m]))
				ans = m, l = m + 1;
			else
				r = m - 1;
		}
		answer /= tmp[ans];
	}
	quit(answer);
}

int main() {
	srand(time(0));
	char str[100];
	while (1) {
		scanf("%s", str);
		if (*str != 's')
			break;
		solve();
	}
}
```

测试代码：
```cpp
...
int cnt = 0, a;
int query(int x, int y) {
	cnt++;
	return x % a >= y % a;
}
...
int main() {
	srand(time(0));
	int sum = 0, mx = 0, num = 0;
	for (int i = 1; i <= 10000; i++) {
		a = 1000000000;
		solve();
		sum += cnt;
		mx = max(mx, cnt);
		if (cnt > 60)
			num++, printf("%d %d\n", a, 2000000000 % a);
		cnt = 0;
	}
	printf("%d %d %d\n", sum, mx, num);
}
```

---

## 作者：golden_brick (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1103B)

---

### 题目大意

未知一个数 $a$，让你每次猜两个数 $y$ 和 $y$，若 $(x\bmod a)\ge (y\bmod a)$ 返回 $x$，否则返回 $y$。

让你猜测次数少于 60 次的时候猜出数 $a$。

---

### 思路

我们可以先二分猜一个 $x$，如果 $(2x\bmod a) \le (x \bmod a)$ ，那么我们就能确定 $x \le a \le 2x$。
找到 $a$ 范围后，可以再来一个二分求出 $a$。

具体见代码。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define il inline
#define INF 0x3f3f3f3f
#define I using
#define love namespace
#define bianbian std
I love bianbian;
#define int long long
const int N = 1e3 + 5;
string s;
signed main()
{
    cin >> s;
    while (s.size() != 3 && s.size() != 7)
    {
        int l = 0, r = 1;
        do
        {
            printf("? %lld %lld\n", l, r);
            cin >> s;
            if (s[0] == 'y')
            {
                l = r;
                r <<= 1;
            }
        } while (s[0] == 'y');
        while (l + 1 < r)
        {
            int mid = (l + r) >> 1;
            printf("? %lld %lld\n", mid, l);
            cin >> s;
            if (s[0] == 'x')
                l = mid;
            else
                r = mid;
        }
        printf("! %lld\n", l + 1);
        cin >> s;
    }
    return 0;
}
```

---

## 作者：orz_z (赞：0)

### 题目大意

未知一个数 $a$，让你每次猜两个数 $x$ 和 $y$，若 $(x\bmod a)\ge (y\bmod a)$ 返回 `x`，否则返回 `y`。

让你猜测次数少于 $60$ 次的时候猜出数 $a$。

### 解题思路

我们可以先二分猜一个 $x$，如果 $(2x\bmod a) ≥ (x \bmod a)$ ， 那么我们就能确定 $x \leq a \leq 2x$。

找到 $a$ 的范围后，可以再来一个二分求出 $a$。

具体见代码。

### CODE

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

string s;

int len;

signed main()
{
    cin >> s;
    while (s.size() != 3 && s.size() != 7)
    {
        int l = 0, r = 1;
        do
        {
            printf("? %lld %lld\n", l, r);
            cin >> s;
            if (s[0] == 'y')
            {
                l = r;
                r <<= 1;
            }
        } while (s[0] == 'y');
        while (l + 1 < r)
        {
            int mid = (l + r) >> 1;
            printf("? %lld %lld\n", mid, l);
            cin >> s;
            if (s[0] == 'x')
                l = mid;
            else
                r = mid;
        }
        printf("! %lld\n", l + 1);
        cin >> s;
    }
    return 0;
}
```



---

