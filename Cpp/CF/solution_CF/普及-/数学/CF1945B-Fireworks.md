# Fireworks

## 题目描述

One of the days of the hike coincided with a holiday, so in the evening at the camp, it was decided to arrange a festive fireworks display. For this purpose, the organizers of the hike bought two installations for launching fireworks and a huge number of shells for launching.

Both installations are turned on simultaneously. The first installation launches fireworks every $ a $ minutes (i.e., after $ a, 2 \cdot a, 3 \cdot a, \dots $ minutes after launch). The second installation launches fireworks every $ b $ minutes (i.e., after $ b, 2 \cdot b, 3 \cdot b, \dots $ minutes after launch).

Each firework is visible in the sky for $ m + 1 $ minutes after launch, i.e., if a firework was launched after $ x $ minutes after the installations were turned on, it will be visible every minute from $ x $ to $ x + m $ , inclusive. If one firework was launched $ m $ minutes after another, both fireworks will be visible for one minute.

What is the maximum number of fireworks that could be seen in the sky at the same time?

## 说明/提示

In the first set of input data, the fireworks are visible in the sky for $ 5 $ minutes. Since the first installation launches fireworks every $ 6 $ minutes, and the second one every $ 7 $ minutes, two fireworks launched from the same installation will not be visible in the sky at the same time. At the same time, after $ 7 $ minutes from the start of the holiday, one firework from the first and one from the second camp will be visible. Thus, it is possible to see no more than $ 2 $ fireworks simultaneously.

In the third set of input data, $ 17 $ fireworks will be visible after $ 112 $ minutes:

- $ 9 $ fireworks launched from the first installation at times \[ $ 56, 63, 70, 77, 84, 91, 98, 105, 112 $ \];
- $ 8 $ fireworks launched from the second installation at times \[ $ 56, 64, 72, 80, 88, 96, 104, 112 $ \].

## 样例 #1

### 输入

```
6
6 7 4
3 4 10
7 8 56
5 6 78123459896
1 1 1
1 1 1000000000000000000```

### 输出

```
2
7
17
28645268630
4
2000000000000000002```

# 题解

## 作者：spfa_ (赞：6)

[CF1945B Fireworks](https://www.luogu.com.cn/problem/CF1945B)

### 题目翻译

有两个烟花发射装置，其中一个在 $a$ 的倍数的时刻发射烟花，另一个在 $b$ 的倍数的时刻发射一个烟花，持续 $m+1$ 时刻，问一个时刻最多能看到多少个烟花。

### 题目分析

一个烟花持续 $m+1$ 的时刻，那么在任意长度为 $m+1$ 的区间内发射的烟花是都可以在右端点处看见的，所以问题相当于转化为：一个长度为 $m+1$ 的区间，$a$ 的倍数的个数和 $b$ 的个数之和最大为多少。那么答案显然为 $\lfloor \dfrac{m}{a} \rfloor+\lfloor \dfrac{m}{b} \rfloor+2$。

[code](https://codeforces.com/contest/1945/submission/252297008)

---

## 作者：tanzicheng (赞：2)

## [CF1945B] Fireworks 题解
### 题目翻译
现在开始放烟花，有两箱烟花，第一箱每 $a$ 分钟发射一次，第一箱每 $b$ 分钟发射一次，一个烟花会持续 $m$ 分钟。

现在同时燃放两箱烟花，问天空中最多能看到多少发烟花。
### 解题思路
一道数学题，可以看一下下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/3c4q2oj1.png)
可以发现两条时间线分别是两个个等差数列，而结果是 $m$ 以内 $a$ 的倍数加 $m$ 以内 $b$ 的倍数加 $2$，因为算倍数时没有计算最开始的两个烟花。
### 具体实现
直接计算即可。

时间复杂度：$O(1)$

[AC](https://www.luogu.com.cn/record/151761481) code:
```cpp
#include<bits/stdc++.h>
using namespace std;
void code(){
	long long a,b,m;    //数据范围很大，要开long long
	cin >>a>>b>>m;
	cout <<m/a+m/b+2<<endl;    //m以内a的倍数加m以内b的倍数加2
}
int main(){
	int t;
	cin >>t;
	while(t--){    //多测
		code();
	}
  return 0;
} 
```

---

## 作者：littlebug (赞：2)

## Description

给你 $2$ 种烟花，第一种每隔 $a$ 分钟发射一次，第二种每隔 $b$ 分钟发射一次。设在 $x$ 分钟发射了一个烟花，则这个烟花可以在第 $x$ 至第 $x+m$ 分钟内可见（即可以存在 $m+1$ 分钟），求最多可以在同一分钟看见几个烟花。

## Solution

设 $T={\rm lcm}(a,b)$。

因为 $a~|~T$，$b~|~T$，所以这时 $A$ 和 $B$ 两种烟花同时发射一次（设为第 $x$ 次），并在 $T+m$ 分钟时依然存在，而在这时第 $x$ 次之前的烟花一定都已经不可见，所以只讨论第 $x$ 次后 $m$ 分钟内的烟花数量即为答案，因为在 $m+1$ 分钟是第 $x$ 次发射的烟花就已经不可见了。

在第 $T+1$ 至第 $T+m$ 分钟内，因为 $a~|~T$，$b~|~T$，所以 $A$ 共发射了 $\displaystyle\lfloor\frac{m}{a}\rfloor$ 个烟花，$B$ 共发射了 $\displaystyle\lfloor\frac{m}{b}\rfloor$ 个烟花，再加上在 $T$ 分钟内发射的烟花，则答案为：

$$\lfloor\frac{m}{a}\rfloor+\lfloor\frac{m}{b}\rfloor + 2$$

还有就是因为 $a,b,m\le10^{18}$，所以要开 `long long`。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
#define ll long long
using namespace std;
ll a,b,m;
il void solve()
{
	cin>>a>>b>>m;
	cout<<m/a+m/b+2<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：Otue (赞：1)

我们找到最佳的起始点 $x$ 使得 $x$ 到 $x+m$ 烟花最多。

根据样例解释 3，最佳情况是，$x$ 时刻有两个烟花同时放出。则 $x$ 可以取 $\operatorname{lcm}(a,b)$。

求出 $x$ 后就可以直接计算烟花数量了。

但是 $a,b\leq 10^{18}$，两者的 lcm 会超过 long long。`__int128` 在 CF 评测机上会 CE。（以前不会的，现在是）。

所以直接上 python。

```cpp
import fractions

t = int(raw_input())
for _ in xrange(t):
    a, b, c = map(int, raw_input().split())
    if a > b:
        a, b = b, a
    w = a * b / fractions.gcd(a, b)
    t = ((w + c) / a) * a
    t1 = ((w + c) / b) * b
    ans = (t - w) / a + 1
    if t1 >= w:
        ans += (t1 - w) / b + 1
    print ans

```

---

## 作者：T_TLucas_Yin (赞：1)

有点像那个两人交替拍手的红题。容易想到，最优情况下在第一分钟两个发射器同时发射烟花，这样一开始的烟花总数最多。此后在这两个烟花存在的最后 $m$ 分钟内，两个发射器发射的烟花都会同时被看见。这段时间内第一个装置发射了 $\lfloor \frac m a \rfloor$ 个烟花，第二个装置发射了 $\lfloor \frac m b \rfloor$ 个烟花，将这两个数相加，再加上一开始发射的两枚烟花，就是最多同时看到的烟花总数。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a,b,m;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%lld %lld %lld",&a,&b,&m);
        printf("%lld\n",2+m/a+m/b);
    }
    return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1945B)

## 解题思路
数学题。

一个烟花可以从 $x$ 分钟放到第 $x+m$ 分钟，也就是放了 $m+1$ 分钟。

题目问天空中最多可以同时看到多少枚烟花，那肯定是第一次最多。第一个装置在 $m+1$ 分钟内放了 $\lfloor \dfrac{m}{a} \rfloor +1$ 个烟花，第二个装置在 $m+1$ 分钟内放了 $\lfloor \dfrac{m}{b} \rfloor +1$ 个烟花。加起来，也就是 $\lfloor \dfrac{m}{a} \rfloor + \lfloor \dfrac{m}{b} \rfloor + 2$ 个烟花。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long //记得开 long long！
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int a,b,m;
		cin>>a>>b>>m;
		cout<<2+m/a+m/b<<'\n';
	}
	return 0;
}

```

---

## 作者：Weekoder (赞：0)

### 思路

将问题转化为在一个长度为 $m+1$ 的数轴上最多有多少个 $a$ 的倍数和 $b$ 的倍数。不过，还要加上最开始的 $2$ 个烟花。

那么，答案显然为 $\lfloor \frac{m}{a}\rfloor+\lfloor \frac{m}{b}\rfloor+2$。

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int T;

ll a, b, m;

int main() {
	cin >> T;
	while (T --) {
		cin >> a >> b >> m;
		cout << m / a + m / b + 2 << "\n";
	}
	return 0;
} 
```

---

## 作者：Sternenlicht (赞：0)

思路：

注意到数据范围是 $1 \le a,b,m \le 10^{18}$，可以判断出此题是一道数学题。

由题可知，一个烟花可持续 $m + 1$ 个时刻，即在数轴上表示出的区间范围是 $m + 1$。那么问题可以转换为：在长度为 $m+1$ 的区间中，最多有多少个 $a$ 的倍数和 $b$ 的倍数。

则答案为 $\lfloor \frac{m}{a} \rfloor + \lfloor \frac{m}{b} \rfloor + 2$，加 $2$ 是因为计算倍数时没有把最开始的两个烟花算上。

```cpp
#include <bits/stdc++.h>
#define il inline
namespace Fast_IO {
	template <typename T> il void read(T &x) {
		x = 0; int f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + (ch - 48), ch = getchar();
		x = f ? -x : x;
	}
	template <typename T, typename ...Args>
	il void read(T &x, Args& ...args) {read(x), read(args...);}
	template <typename T> il void write(T x, char c = '\n') {
		if (x) {
			if (x < 0) x = -x, putchar('-');
			char a[30]; short l;
			for (l = 0; x; x /= 10) a[l++] = x % 10 ^ 48;
			for (l --; l >= 0; l --) putchar(a[l]);
		} else putchar('0');
		putchar(c);
	}
} using namespace Fast_IO;
using namespace std;

#define int long long

signed main() {
	int T; read(T);
	while (T --) {
		long long a, b, m; read(a, b, m);
		write(m / a + m / b + 2);
	}
	return 0;
}
```

---

## 作者：OPEC (赞：0)

# [CF1945B Fireworks](https://www.luogu.com.cn/problem/CF1945B)
 仔细读题后会发现你最多能看到所有在 $0$ 到 $m$ 区间发射的烟花。只需要输出 $0$ 到 $m$ 区间发射的数量。公式是  $m\div a+m\div b+2$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int unsigned long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
void solve()
{
 	//不要抄题解 QAQ
	int a,b,m;
	cin>>a>>b>>m;
	int fi=m/a;
	int se=m/b;
	cout<<fi+se+2<<'/n';
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

## 作者：_Mortis_ (赞：0)

### [CF1945B Fireworks 题目传送门](https://www.luogu.com.cn/problem/CF1945B)
一道数学题，建议评红。
## 思路
由题目可知，一个烟花在 $a$ 的倍数时刻发射，另一个在 $b$ 的倍数时刻发射，一个烟花可以持续 $m+1$ 个时刻，所以问题可以转化成在长度为 $m+1$ 的区间中，最多有多少个 $a$ 的倍数和 $b$ 的倍数。答案是 $\lfloor \frac{m}{a} \rfloor  + \lfloor  \frac{m}{b} \rfloor + 2$。
### CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,m;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(cin>>T;T;T--){
		cin>>a>>b>>m;
		cout<<m/a+m/b+2<<"\n";
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/152809311)

---

