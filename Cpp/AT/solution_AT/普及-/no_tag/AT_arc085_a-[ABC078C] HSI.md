# [ABC078C] HSI

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc078/tasks/arc085_a

高橋くんはプログラミングコンテストに出ていますが， `YES` か `NO` で答える問題でTLEしてしまいました。

提出の詳細を見ると，テストケースは全てで $ N $ ケースあり，そのうち $ M $ ケースでTLEしていました。

そこで高橋くんは, $ M $ ケースではそれぞれ実行に $ 1900 $ ms かかって $ 1/2 $ の確率で正解し， 残りの $ N-M $ ケースではそれぞれ実行に $ 100 $ ms かかって必ず正解するプログラムへ書き換えました。

そして，以下の操作を行います。

- このプログラムを提出する。
- 全てのケースの実行が終わるまで待機する。
- もし $ M $ ケースのうちどれかで不正解だった場合，もう一度プログラムを提出する。
- これを，一度で全てのケースに正解するまで繰り返す。

この操作が終了するまでの，プログラムの実行時間の総和の期待値を $ X $ msとした時，$ X $ を出力してください。

なお，$ X $ は整数で出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ M\ \leq\ {\rm\ min}(N,\ 5) $

### Sample Explanation 1

この入力だとケースは $ 1 $ ケースだけであり，$ 1900 $ ms かかって $ 1/2 $ の確率で正解するプログラムを投げ続けます。 つまり $ 1 $ 回で正解する確率は $ 1/2 $, $ 2 $ 回で正解する確率は $ 1/4 $, $ 3 $ 回で正解する確率は $ 1/8 $ です。 よって答えは $ 1900\ \times\ 1/2\ +\ (2\ \times\ 1900)\ \times\ 1/4\ +\ (3\ \times\ 1900)\ \times\ 1/8\ +\ ...\ =\ 3800 $ です。

### Sample Explanation 2

$ 2 $ ケースで $ 1900 $ ms かかり，$ 10-2=8 $ ケースで $ 100 $ ms かかるプログラムを投げ続けます。 全てのケースで正解する確率は $ 1/2\ \times\ 1/2\ =\ 1/4 $ です。

## 样例 #1

### 输入

```
1 1```

### 输出

```
3800```

## 样例 #2

### 输入

```
10 2```

### 输出

```
18400```

## 样例 #3

### 输入

```
100 5```

### 输出

```
608000```

# 题解

## 作者：Heliox (赞：5)

我们首先要明确：总耗时 $=$ 期望提交次数 $\times$ 每次等待时间。

其中每次等待的时间为 $1900m+100 \times (n - m) = 1800m + 100n$。

其中 $m$ 个测试点，每个测试点 AC 的概率为 $\frac{1}{2}$，那么 AC 率就是 $(\frac{1}{2})^m=\frac{1}{2^m}$，期望提交次数为 $2^m$。

根据上面的公式，我们可得总耗时为 $2^m \times (1800m + 100n)$。

可得以下 $O(n)$ 复杂度的代码：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int n; cin >> n;
    int m; cin >> m;
    cout << (pow(2, m) * (1800 * m + 100 * n));
    return 0;
}
```

---

## 作者：wimg6_ (赞：2)

# AT3670 题解

题目指标 [[ARC085A] HSI](https://www.luogu.com.cn/problem/AT3670) .

该文章同步发表于 [我的博客](https://www.luogu.com.cn/blog/Kingson123456/) 内。

审核一经通过，他人不得盗用博客。若为通过，引用时需注明出处，并私信作者。

### 正解

首先，从题目角度来看，我们可以非常容易得到以下内容：

总耗时 （ 以下简称 ${at}$ ） = 提交次数 （ 以下简称 $hmt$ ) × 每次提交等待时间 ( 以下简称 $ot$ ）

通过题意，我们可以求出

$ot = 1900m\ + 100 \times (n-m) = 1900m+100n-100m = 1800m+100n$ .

其中， 1900m 表示我们需要在 1900s 内 AC 总共 $m$ 个会 TLE 的点。

接着，我们需要继续在 $100s$ 内 AC 总共 $(n-m)$ 个不会 TLE 的点。

再回到题目中阅读题意，可以轻松发现如下规则：

会 TLE 的点只有两种状态： AC 和 TLE .

故每个子测试点 TLE 的概率为 50% .

同样，每个子测试点 AC 的概率也为 50% ， 即 $\dfrac{1}{2}$ .

又因为总共有 $m$ 个会让高桥君 TLE 的点。

所以我们可以求出一道题 AC 的概率为： $({\dfrac{1}{2}})^m$ .

化简可得： $hmt=({\dfrac{1}{2}})^m = \dfrac{1}{2^m}$ .

没学过这一类知识的可以去看看初中课本中 幂的运算 相关内容，在此不做解释。

因此，我们可以得到高桥君最多需要提交 $2^m$ 次。

于是，我们就可以得到：

$${at}=hmt\times{ot}=2^m\times{(1800+100n)}$$

时间复杂度 $O(1)$，对这题而言绰绰有余。

### 代码

在本份代码中，出现一个位运算的知识点：

$$1<<m=2^m$$

这样可以将原本需要 $O(m)$ 时间复杂度的幂运算转为只需要 $O(1)$ 时间复杂度的位运算。有兴趣的同学可以到网上查一下。


```
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
long long n,m;
int main()
{
    scanf("%d%d",&n,&m);
    return !printf("%d",(1800*m+100*n)*(1<<m));
    //1<<m=2^m
}
```


---

## 作者：清清老大 (赞：2)

## 思路

每次提交等待时间 $ = m$ 个 TLE 的点所用时间 $ + n − m $ 个点所用时间 $= 1900m+100(n - m)$ 毫秒。

每个 TLE 的点 AC 概率 $= \frac{1}{2}$。

所有 TLE 的点 AC 概率 $= (\frac{1}{2})^m=\frac{1}{2^m}$。

所以期望提交次数 $= 2^m$。

期望提交时间 $=$ 期望提交次数 $\times$ 每次提交等待时间 $=[1900m+100(n-m)]\times2^m=(1800m+100n)\times2^m$ 毫秒。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    long long m,n;//本题建议开long long
    cin >> n >> m;//输入n,m
    cout << (1800 * m + 100 * n) * (1 << m);
    // (1 << m)这里的<<是左移运算符,(1 << m)相当于2^m。
}
```


---

## 作者：Buried_Dream (赞：1)

## 题意：

总共有 $n$ 个测试点，有 $m$ 个会 `TLE`，题目只会输出 `YES` 和 `NO`，所以他有一半的概率能答对这个测试点，问答对所有测试点的期望时间。

## 思路：

期望时间 $=$ 提交次数 $\times$ 测评时间

一次测评时间就是 $1900 \times m + 100 \times (n -m) = 1800 \times m + 100 \times n$。

提交次数就是：

每一道题都有一半的概率能对，总共 $m$ 道题，同时对的概率就是 $\frac{1}{2^m}$。	

所以最后答案就是 $\frac{1}{2^m} \times (1800 \times m + 100 \times n)$。

## AC code:

```cpp
/*
work by: TLE_Automation
Time: O(轻轻松松过)
knowledge: 垃圾算法
*/
#include<bits/stdc++.h>
#define il inline
#define re register
#define Orz puts("Szt Lps Fjh AK IOI!");
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
//#define int long long
using namespace std;

const int INF = 1e9 + 7, mod = 1e9 + 7;
const int maxn = 2e5 + 10, MAXN = 3e3 + 10, N = 1e6 + 10;

namespace IO {
inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int s = 0, w = 1;char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}}

using namespace IO;

signed main() {
	int tests = 1; // tests = read();
	while(tests--) {
		int n = read(), m = read();
		print((1 << m) * (1800 * m + 100 * n));
	}
}

```

---

## 作者：精神小伙！ (赞：1)

## 思路

总耗时 $ = $ 期望提交次数 $ \times $ 每次等待时间。

首先求每次等待时间。

每次等待时间 $ = 1900 m  + 100 ( n - m ) = 1800m + 100n$。

接下来求期望提交次数。

由于每个点 AC 和 TLE 的几率均为 $ 50\% $，并且会有 $ m $ 个点会 TLE，所以 AC 的概率为 $ (\dfrac{1}{2})^m = \dfrac{1}{2^m} $，可以得出高桥君的期望提交次数为 $ 2^m $ 次。

所以总耗时就等于 $ 2^m \times ( 1800m + 100n ) $ 毫秒。

可以用位运算优化。

## 代码

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	cout<<(1<<m)*(1800*m+100*n)<<endl;
	return 0;
}

```

---

## 作者：高雍博 (赞：1)

水题，~~恶意评级？~~

入门题。推导过程楼下讲的很清楚，我就简单提一下：

单点单次 $AC$ 概率：$\dfrac{1}{2}$。

每次全部 $AC$ 概率：$\dfrac{1}{2^m}$。所以期望的情况（运气不好不坏）就是交$2^m$次。 ~~（浪费评测资源？）~~

每交一次耗时 $1900×m+100×(n-m)$ 毫秒。

总耗时 $[1900×m+100×(n-m)]×2^m$ 毫秒。

代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)//吸一口臭氧
using namespace std;
long long int n,m;
unsigned long long int sum;//答案 

//重点 
unsigned long long int quickPower(int a, int b)//快速幂，是求a的b次方
{
    unsigned long long int ans=1,base=a;//ans为答案，base为a^(2^n)
    while(b>0)//b是一个变化的二进制数，如果还没有用完
    {
        if(b&1)//&是位运算，b&1表示b在二进制下最后一位是不是1，如果是：
            ans*=base;//把ans乘上对应的a^(2^n)
		base*=base;//base自乘，由a^(2^n)变成a^(2^(n+1))
        b=b>>1;//位运算，b右移一位，如101变成10（把最右边的1移掉了），10010变成1001。现在b在二进制下最后一位是刚刚的倒数第二位。结合上面b & 1食用更佳
    }
    return ans;
}

int main()
{
	scanf("%lld%lld",&n,&m);
	sum=quickPower(2,m)*(m*1900+(n-m)*100);
	printf("%ull",sum);
	return 0;
}
```
快速幂更快（废话），而且使代码高大上，并且锻炼了模板的运用。通常自带函数是可以的，但是保险起见，遇到涉及幂次方的题目尽量还是用快速幂。

---

## 作者：nanatsuhi (赞：1)

入门难度题，完全不考验编程水平，学过小学数学都会做。

由于每次提交互不影响，所以每次AC的概率都是$(1/2)^m$，所以期望次数就是$2^m$。

每次的时间都是$1900*m+100*(n-m)$,所以期望时间就是：

### $[1900*m+100*(n-m)]*2^m$

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    cout<<(1900*m+100*(n-m))*(pow(2,m))<<endl; //c++自带的幂函数
    return 0;
}
```


---

