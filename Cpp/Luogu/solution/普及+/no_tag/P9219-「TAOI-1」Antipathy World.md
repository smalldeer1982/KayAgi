# 「TAOI-1」Antipathy World

## 题目背景

> 簡単なことも解らないわ \
> あたしって何だっけ \
> それすら夜の手に絆されて \
> 愛のように 消える 消える \
> さようならも言えぬ儘泣いた フォニイ フォニイ フォニイ \
> 嘘に絡まっているあたしはフォニイ \
> **ANTIPATHY WORLD**

## 题目描述

**这是一道 IO 交互题。**

可不有 $n$ 朵花，每朵花有一个正整数美丽度。

她发现，有一朵花的美丽度不小于其它任何一朵花的美丽度的两倍。

你想知道这朵花是哪一朵，于是你可以进行至多 $k$ 次询问，每次询问你给出两个正整数 $i,j \in [1, n]$，可不会告诉你第 $i$ 朵和第 $j$ 朵花的美丽度之差的绝对值。

你想运用这些询问的答案，得到最美丽的花是第几朵。

### 交互格式

**本题有多组数据**。

第一行交互库给出一个整数 $T$，表示数据组数。

对于每组数据，第一行输入两个正整数 $n,k$。

对于你的每组询问，你输出 `? i j`，交互库会返回一个非负整数，表示第 $i$ 朵和第 $j$ 朵花的美丽度之差。

如果你已经得到答案，输出 `! i` 代表你得到第 $i$ 朵花为最美丽的花。在此之后你应该开始对下一组数据的处理。

每次你输出之后，请**刷新缓冲区**。

你可以使用如下语句来清空缓冲区：

- 对于 C/C++：`fflush(stdout)`；
- 对于 C++：`std::cout << std::flush`；
- 对于 Java：`System.out.flush()`；
- 对于 Python：`stdout.flush()`；
- 对于 Pascal：`flush(output)`；
- 对于其他语言，请自行查阅对应语言的帮助文档。

特别的，对于 C++ 语言，在输出换行时如果你使用 `std::endl` 而不是 `'\n'`，也可以自动刷新缓冲区。

## 说明/提示

样例中给出了一种可能的交互方式，其中花的美丽度为 $\{4,1,2\}$。

---

**本题采用捆绑测试**。

- Subtask 1（20 points）：$k=\dfrac{n(n-1)}{2}$，$n \le 200$。
- Subtask 2（30 points）：$k=n$。
- Subtask 3（50 points）：$k=\left\lfloor\dfrac{n}{2}\right\rfloor+2$。

对于所有测试数据，设所有花的美丽度为 $a_i$，$1 \le T \le 25$，$3 \le n \le 5 \times 10^4$，$1 \le a_i \le 10^8$。

## 样例 #1

### 输入

```
1
3 114514

3

2

1
```

### 输出

```


? 1 2

? 1 3

? 2 3

! 1```

# 题解

## 作者：irris (赞：4)

## Preface

```text
【管理员】你说得对，但是 2023/5/27 21:20:06
TAOI-1 也没见人考证啊。

【管理员】iRrrrrrrrrrrrris 2023/5/27 21:20:11


【管理员】iRrrrrrrrrrrrris 2023/5/27 21:20:14
椎名真昼

【管理员】iRrrrrrrrrrrrris 2023/5/27 21:20:18
这都写到脸上了

【管理员】iRrrrrrrrrrrrris 2023/5/27 21:20:21
考证 nm 呢

【管理员】iRrrrrrrrrrrrris 2023/5/27 21:20:32
剩下的全是歌曲

【管理员】你说得对，但是 2023/5/27 21:20:33
T3 没写到脸上！

【管理员】你说得对，但是 2023/5/27 21:20:35
别的确实！
```

フォニイ。

## Solution

入门级交互题，~~为啥出题人一开始只出了 $\sout{k = n - 1}$ 捏~~
。

一个很自然的想法是由于假花和其它花美丽度之差最小为 $2v - v = v$，而其它花之间最大为 $v - 1$，所以可以打擂台找出来假花。

**但是每次比较 $\bm{a, b}$ 和 $\bm{a, c}$ 是很浪费的**。更优雅的想法是每次比较 $a, b$ 和 $c, d$，这样一定能同时排除 $a, b$ 或 $c, d$ 中的一方。

重复直到 $n = 3$，如果一开始是偶数导致排除到了 $n = 2$ 随便拉一朵花进来变成 $n = 3$。手玩即可 $2$ 次解决这里的 bound issues。

## Code

这里提供一个比较简洁的写法。

```cpp
#include <bits/stdc++.h>

void solve() {
	int N, K, b, v; std::cin >> N >> K;
	for (int i = 1, x; i < N; i += 2) {
		std::cout << "? " << i << ' ' << i + 1 << std::endl, std::cin >> x;
		if (i == 1 || x > v) b = i, v = x;
	}
	int t = (b == N - 1 ? 1 : N), x1, x2;
	std::cout << "? " << t << ' ' << b << std::endl, std::cin >> x1;
	std::cout << "? " << t << ' ' << b + 1 << std::endl, std::cin >> x2;
	std::cout << "! " << ((N & 1) && (x1 > v && x2 > v) ? N : x1 > x2 ? b : b + 1) << std::endl;
}

int main() {
	int T; std::cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：251Sec (赞：3)

## Subtask 1

$$k=\dfrac{n(n-1)}{2}$$

可以把每组数的差都问出来，于是乱搞。

## Subtask 2

$$k=n$$

我们花费 $n-1$ 次询问求出第一个数和其它所有数的差，考虑差最大的那个数，设为 $x$，可以发现最终最大的数一定是 $a_1$ 或 $a_x$。

于是我们再问一次 $|a_x-a_2|$ 和 $|a_1-a_2|$ 比较即可。

## Subtask 3

$$k=\left\lfloor\dfrac{n}{2}\right\rfloor+2$$

注意到上一种做法十分浪费，我们实际上可以把这些数两两分组，询问 $|a_1-a_2|,|a_3-a_4|,|a_5-a_6|,\cdots$。于是差最大的一组中一定有一个是最大的数（如果总共有奇数个数，那么最后剩下一个数没询问也有可能）

分两种情况：

- $n$ 为偶数：我们设差最大的一组为 $a_x,a_{x+1}$，我们随便找一个其他的数 $a_y$ 比较 $|a_x-a_y|$ 和 $|a_{x+1}-a_y|$ 即可。
- $n$ 为奇数：我们设差最大的一组为 $a_x,a_{x+1}$，剩下的一个数为 $a_y$，我们询问 $|a_x-a_y|$ 和 $|a_{x+1}-a_y|$，而我们已经知道了 $|a_x-a_{x+1}|$，于是我们可以得出这三个数的相对差值。然后我们就知道三个数哪个在中间，于是比较另外两个数和中间这个数的差即可得到答案。

自此，本题完成。

如果硬实现的话可能会有一大堆恶臭分讨，但是注意到很多的询问的对称性，事实上代码可以写得很短。这里给出一种实现（By [0x3b800001 ](/user/306090)）：

```cpp
#include <iostream>
#include <algorithm>
using ll = long long;

int ask(int i, int j) {
  std::cout << "? " << i << ' ' << j << std::endl;
  int r;
  std::cin >> r;
  return r;
}
void ans(int x) { std::cout << "! " << x << std::endl; }
void solve() {
  int n, k;
  std::cin >> n >> k;
  int d = -1, I = 0;
  for (int i = 1; i + 1 <= n; i += 2) {
    int w = ask(i, i + 1);
    if (w > d) I = i, d = w;
  }
  int t = I + 1 == n ? 1 : n;
  int x[3] = {ask(I + 1, t), ask(I, t), d};
  int a[3] = {I, I + 1, t};
  for (int i = 0; i < 3; ++i) {
    std::rotate(x, x + 1, x + 3), std::rotate(a, a + 1, a + 3);
    if (x[0] != x[1] + x[2]) continue;
    if (x[1] > x[2])
      ans(a[2]);
    else
      ans(a[1]);
    return;
  }
}
int main() {
  int t;
  std::cin >> t;
  while (t--) solve();
  return 0;
}
```

---

## 作者：LHQing (赞：2)

#### 思路分析

交互题。

直接看到 $k=\lfloor\dfrac n2\rfloor+2$。这是很明显的提示：每次询问都是二元的，序列中每次询问两个没有询问过的，次数为 $\lfloor\dfrac n2\rfloor$；加上了 $2$ 意味着我们可以再询问两次。

设 $m$ 为序列中最大值，$m'$ 为次大值。由题目得到 $m\ge 2m'$。

容易得到，当 $n$ 为偶数时，询问 $2i-1$ 与 $2i$，若其中一个为最大值 $m$，则得到的答案 $\ge m-m'\ge m'$。如果不是最大值，则得到的答案 $\lt m'$。所以我们两两询问后，得到取得答案最大值的两个位置，随便找一个不同的位置，将两个位置和这个不同位置的差再比较一次，取较大的即可。

若 $n$ 为奇数时，询问会剩下一个元素。与差最大值的两个位置结合，分别询问两次。相当于数轴上三个点，两两距离已知，并且最大的不比次大的两倍小，求最大的一个。于是我们根据距离分类讨论三种情况，也就是三个值分别在中间的情况，然后根据所获得的值直接判断大小从而输出答案即可。

#### 代码

```
#include <bits/stdc++.h>

using namespace std;

const int maxn = 5e4 + 10;

int t, n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> n >> k;
        int p = 1, q = 0, d;
        for (int i = 1; i + 1 <= n; i += 2) {
            cout << "? " << i << " " << i + 1 << endl;
            cin >> d;
            if (d > q) p = i, q = d;
        }
        if (n & 1) {
            int x, y;
            cout << "? " << p << " " << n << endl;
            cin >> x;
            cout << "? " << p + 1 << " " << n << endl;
            cin >> y;
            /*
            p------------p+1  q
            p------------n    x
            p+1------------n  y
            */
            if (q + y == x) { // p + 1 is mid
                cout << "! " << (y > q ? n : p) << endl;
            } else if (q + x == y) { // p is mid
                cout << "! " << (x > q ? n : p + 1) << endl;
            } else if (x + y == q) { // n is mid
                cout << "! " << p + (x <= y) << endl; 
            }
        } else {
            int x, y, z = (p == 1 ? 3 : 1);
            cout << "? " << p << " " << z << endl;
            cin >> x;
            cout << "? " << p + 1 << " " << z << endl;
            cin >> y;
            cout << "! " << p + (x <= y) << endl;
        }
    }
    return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：2)

为方便表述，记 $b_{i,j}=|a_i-a_j|$，$\max\{a_i\}=a_A$。

显然，$a_A - \min\{a_i\}$ 是 $b$ 的最大值。

把所有 $b_{i,j}$ 都查出来，找到最大的那个值，不妨记为 $b_{x,y}$。  
那么 $A\in\{x,y\}$。

考虑如何应用 $A$ 不小于其余每一个数的两倍这个条件。

发现，$\forall i,j$ 且 $a_i \le a_j$，有 $b_{A,i}\ge b_{A,j}\ge b_{j,i}$，$b_{j,i}+b_{j,A}=b_{A,i}$。

随便找一个异于 $x,y$ 的数 $z$ 判断一下，这样就能过 Sub1。

再考虑两倍的条件：我们发现 $b$ 的前 $n-1$ 大必然都是形如 $b_{i,A}$。  
可以代数变形证，也可以感性理解为 $a_A$ 与其他的数都离很远，而其他的数都集中于 $\frac{a_A}2$ 以下。

那只需要对每一个数问一次。

不难想到奇偶分组。

对 $n$ 奇偶性讨论：

- $n=2m,m\in \mathbb Z^* $：找到最大的数，然后按 Sub1 类似地判一下就好了。

- $n=2m+1,m\in \mathbb Z^* $：此时多出一个数 $a_n$。把 $a_n$ 和前面找到的最大的一组做判断即可。

一个实现小技巧：用 `std::rotate` 函数实现轮换式的处理：  
向 `std::rotate` 中传入三个迭代器，第 $1$、$3$ 个分别是要被旋转的序列的始末位置（左闭右开），第二个是旋转后成为首位的数的位置。

细节看代码。
```cpp
#include<cstdio>
#include<algorithm>
#define re register
#define il inline
#define ast(yx,wt) (yx)||(exit(wt),7)
#define rd(yx) scanf("%d",&yx)
#define prt(w,t) printf("%d%c",w,t)
il int Query(re int x,re int y)
{
	re int z;
	return printf("? %d %d\n",x,y),fflush(stdout),rd(z),z;
}
il void Reply(re int x){return printf("! %d\n",x),fflush(stdout),void();}
int n,k;
namespace Sub_1
{
	const int N=203;
	int x,y,z,a[N][N];
	il int F()
	{
		re int b[]={a[x][y],a[y][z],a[x][z]},c[]={z,x,y};
		for(re int i=0;i<3;++i)
		{
			std::rotate(b,b+1,b+3),std::rotate(c,c+1,c+3);
			if(b[0]==b[1]+b[2]) return b[1]>b[2]?c[2]:c[1];
		}
		return ast(0,7);
	}
	void Solve()
	{
		x=y=0;
		for(re int i=1;i<=n;++i)
			for(re int j=1;j<i;++j)
				a[j][i]=a[i][j]=Query(i,j),a[i][j]>a[x][y]&&(x=i,y=j);
		x>y&&(std::swap(x,y),7);
		if(x^1) z=1;
		else z=y^2?2:3;
		return Reply(F());
	}
}
namespace Sub_2
{
	int res,s,y;
	il int F(re int x,re int y,re int z)
	{
		re int b[]={Query(y,z),Query(x,z),s},c[]={x,y,z};
		for(re int i=0;i<3;++i)
		{
			std::rotate(b,b+1,b+3),std::rotate(c,c+1,c+3);
			if(b[0]==b[1]+b[2]) return b[1]>b[2]?c[2]:c[1];
		}
		return ast(0,7);
	}
	void Solve()
	{
		res=s=0;
		for(re int i=1,w;i<=n/2;++i) w=Query((i<<1)-1,i<<1),w>s&&(s=w,res=(i<<1)-1);
		return Reply(F(res,res+1,n&1?n:(res+1^n)?n:1));
	}
}
void Solve(){return rd(n),rd(k),k==n*(n-1)/2?Sub_1::Solve():Sub_2::Solve();}
main()
{
//	freopen("1.in","r",stdin);
	re int T;
	for(rd(T);T--;Solve());
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：1)

交互有趣。

先讲 $50$ 分做法。

首先，因为最美丽的花（设其美丽度为 $2x$）比其它花一定至少多 $x$（因为其它美丽度最大的就是 $x$）。而其它花的最大的美丽度比其它花最小的美丽度至多多 $x-1$（因为其它的最小 $1$，最大 $x$）。

所以我们就明确做法了：

首先，用 $k-1$ 次操作分别选 $1$ 和 $2,3,4,\cdots ,n$，此时我们一定会找到最大的差值，设最大差的两段分别是 $1$ 和 $x$，则最美丽的花一定是 $1$ 或 $x$，此时，我们可以用最后一次操作来随便找一个数 $y$，比较 $x$ 和 $y$。这样，$1,x,y$ 都被互相比较过，形成了一种“三角关系”。于是，同时包含最大的两个差值的数即为答案。

可是这样会询问 $k$ 次，会超。

------------

$100$ 分做法。

我们考虑两两分一组，即 $(i,i+1)$ 分一组来询问。

这时已经进行了 $\lfloor\frac{n}{2}\rfloor$ 次操作了，还有 $2$ 次操作。

我们断定，最美的花一定在差最大的一组中，设其是 $(x,x+1)$，接下里来是个小分讨：

- $n\bmod 2=0$：随便找一个其他的下标 $y$，询问 $(x,y),(x+1,y)$。我们发现，这样又构成了一个“三角关系”，根据 $50$ 分做法询问即可。
- $n\bmod 2=1$：其实就是将 $n\bmod 2=0$ 中“随便找的数”设置成 $n$ 即可，处理“三角关系”时，找到同时包含最大和次大的花即可

---

## 作者：E1_de5truct0r (赞：1)

首先观察到有一个数 $x$ 大于其他所有的数的两倍。所以 $a_x>2 \times \max_{i \neq x} a_i$。

那么我们选择任意一个 $y$，一定有:

$$a_x-a_y>2 \times \max_{i\neq x} a_i-a_y$$

$$2 \times \max_{i\neq x} a_i-a_y\geq 2 \times \max_{i\neq x} a_i-\max_{i\neq x}a_i$$

$$ 2 \times \max_{i\neq x} a_i-\max_{i\neq x}a_i=\max_{i\neq x} a_i$$

也就是 $\forall y \neq x,a_x-a_y>\max_{i \neq x} a_i$。

而我们选择其他的两个数，显然差值不会超过这个。

因此我们可以花费 $\lfloor n/2 \rfloor$ 次操作，直接相邻的两个数作差。

- 如果 $n$ 为偶数，那么差最大的两个数 $a_x,a_{x+1}$ 一定有一个是最大的。我们可以选一个其他的 $y$ 比较一下，显然差更大的那个就是我们要找的。

- 如果 $n$ 为奇数，那么我们选择最后剩下来的那个 $a_y$，以及目前差最大的两个数 $a_x,a_{x+1}$，它们两两作差，找到差最大的。

	然后分类讨论一下是哪两个数最大。由于我们已经知道了它们之间两两的差，所以分讨一下就转化成上面 $n$ 为偶数的情况了。

---

## 作者：masonpop (赞：1)

这题赛时一眼秒杀，但是被教练拖过去上课了，有点遗憾。赛后来补一发题解。

首先发现，对于那个特别大的数 $x$，它和任意一个数的绝对差都会大于另外一对不包含它的数的绝对差。因此，一个朴素的做法是两两询问一次，找出那两个最大的差值对，它们的公共下标就是答案。但是这样是 $O(n^2)$ 的，只能得到 $20$ 分。

发现这样明显多了许多冗余询问。我们不妨这样：设 $k=[\frac{n}{2}]$，那么我们把 $n$ 个数分成 $k$ 组，其中分组为 $(1,2)(3,4)...(2k-1,2k)$，先不考虑可能剩余一个数，那么最大的数或者为这些对的绝对差中最大的一个对的某一个数，或者为最后一个数。设最大的一对为 $(a,b),$ 那么分别对 $(a,n)(b,n)$ 做一次询问，在找它们中最大的两对，公共元素即为答案。

刚好用完 $k+2$ 次询问机会。注意奇数和偶数的情况略有不同，注意细节。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=5e4+10;
int t,n,k;
struct query{
	int a,b;
	int sum;
	bool operator<(const query &o)const{
		return sum<o.sum;
	}
}a[maxn];
int tot;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		tot=0;
		int t=n/2;
		int maxx=0,A,B;
		for(int i=1;i<=t;i++)
		{
			printf("? %d %d\n",2*i-1,2*i);
			fflush(stdout);
			scanf("%d",&a[++tot].sum);
			a[tot].a=2*i-1;a[tot].b=2*i;
			if(a[tot].sum>maxx)
			{
				maxx=a[tot].sum;
				A=2*i-1;
				B=2*i;
			}
		}
		if(n%2==1)
		{
			printf("? %d %d\n",A,n);
			fflush(stdout);
			scanf("%d",&a[++tot].sum);
			a[tot].a=A;a[tot].b=n;
			printf("? %d %d\n",B,n);
			fflush(stdout);
			scanf("%d",&a[++tot].sum);
			a[tot].a=B;a[tot].b=n;
		}
		else if(A==n-1 && B==n)
		{
			printf("? %d %d\n",A,1);
			fflush(stdout);
			scanf("%d",&a[++tot].sum);
			a[tot].a=A;a[tot].b=1;
			printf("? %d %d\n",B,1);
			fflush(stdout);
			scanf("%d",&a[++tot].sum);
			a[tot].a=B;a[tot].b=1;
		}
		else
		{
			printf("? %d %d\n",A,n);
			fflush(stdout);
			scanf("%d",&a[++tot].sum);
			a[tot].a=A;a[tot].b=n;
			printf("? %d %d\n",B,n);
			fflush(stdout);
			scanf("%d",&a[++tot].sum);
			a[tot].a=B;a[tot].b=n;
		}
		sort(a+1,a+tot+1);
		int ans=0;
		if(a[tot].a==a[tot-1].b)ans=a[tot].a;
		if(a[tot].a==a[tot-1].a)ans=a[tot].a;
		if(a[tot].b==a[tot-1].b)ans=a[tot].b;
		if(a[tot].b==a[tot-1].a)ans=a[tot].b;
		printf("! %d\n",ans);
		fflush(stdout);
	}
	return 0;
}
```


---

## 作者：是青白呀 (赞：1)

观察到 $k=\left\lfloor\dfrac{n}{2}\right\rfloor+2$，考虑先用 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 次询问两两之间差值，有结论：**最美丽的花一定存在于差值最大的一组中，或是未被询问到**（只在 $n$ 为奇数的情况存在）。


简单证明一下：最美丽的花一定不小于次美丽的花的两倍，故最美丽的花与任意的另一朵花的差一定不小于次美丽的花的美丽值。由于美丽值是正整数，则不可能存在另一组花使得差值不小于次美丽的花的美丽值。

若 $n$ 为偶数，则最美丽的花判断范围已经缩小为 $2$ 朵，设为 $a,b$。此时任意选择一个非范围内的花 $c$，并分别询问 $a$、$c$ 和 $b$、$c$ 之间的差值，则由前面的证明过程可以推知，较大的两个差值所对应的花中共有的花即为最美丽的花。

若 $n$ 为奇数，则一定会有一朵花未被询问到，最后两次判断时选择原差值最大的两朵花和未询问到的一朵花即可。
```
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
using namespace std;
const int N=5e4+5,inf=1e9+7;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
//create by Qingbai666
int t,n,k;
int c[N];
void solve(){
	read(n),read(k);
	int maxn=0,maxid;
	rep(i,1,n/2){
		printf("? %d %d\n",i*2-1,i*2);
		fflush(stdout);
		read(c[i]);
		if(c[i]>maxn){
			maxn=c[i];
			maxid=i;//i*2-1 i*2
		}
	}
	if(n%2){//讨论 i*2-1 i*2 n 
		int c1,c2; 
		printf("? %d %d\n",maxid*2-1,n);
		fflush(stdout);
		read(c1);
		printf("? %d %d\n",maxid*2,n);
		fflush(stdout);
		read(c2);
		if(maxn>c1&&c2>c1)printf("! %d\n",maxid*2);
		else if(c1>c2&&maxn>c2)printf("! %d\n",maxid*2-1);
		else printf("! %d\n",n);
		fflush(stdout);
	}
	else{//讨论 i*2-1 i*2 oth
		int c1,c2,oth; 
                if(maxid==1)oth=n;
                else oth=1;
		printf("? %d %d\n",maxid*2-1,oth);
		fflush(stdout);
		read(c1);
		printf("? %d %d\n",maxid*2,oth);
		fflush(stdout);
		read(c2);
		if(maxn>c1&&c2>c1)printf("! %d\n",maxid*2);
		else if(c1>c2&&maxn>c2)printf("! %d\n",maxid*2-1);
		fflush(stdout);
	}
}
int main(){
	read(t);
	while(t--)
	    solve();
	return 0; 
}
```


---

## 作者：Ag2WO4 (赞：0)

看别人没写，出一个 Python 的题解罢。

注意重点：**有一朵花的美丽度不小于其它任何一朵花的美丽度的两倍。** 这表明最美的花减去他者至少是第二美的花自身，自然也大于他者之间相减。于是和之前的其他题解一样成对比较，最大的一对单找一朵比较花掉最后的两次比较。

这时问题来了：如果 $n$ 是奇数呢？简单，前面 $\lfloor\frac{n}{2}\rfloor$ 对比完比最后一朵（答案必然在三者之间）；同理如果 $n$ 是偶数就随便另找一朵即可。这里讲一下具体比法：**由于是三朵花里有一朵是答案，三对差值里最小的那对一定是非答案的两朵形成的，就能直接排除得到最终答案。** 形式化地，设先前成对差值的最大值为 $k$ 且和参比花朵分别为 $p$ 和 $q$ 那么有

- 如果 $k$ 最小则答案为参比花朵；
- 否则答案为只参与 $p$ 和 $q$ 中更大者对应比较的那朵花。

写的时候注意一点，如果你默认了某个固定参比位置，比如最后一个，注意特判防止是最后一对最大。
#### 最终代码
```python
for i in range(int(input())):
    n,k=map(int,input().split());k=l=0
    for i in range(n//2):
        m=int(input(f'? {2*i+1} {2*i+2}\n'))
        if m>k:k=m;l=i
    if 2*l+2==n:n=1
    p=int(input(f'? {2*l+1} {n}\n'));q=int(input(f'? {2*l+2} {n}\n'));print('!',n if p>k<q else(1 if p>q else 2)+2*l)
```
最后吐槽一句，绝大部分 IO 交互库貌似都是看换行符 ```\n``` 结尾判定输入，实际上不要忘记输出换行符即可，不需要清空缓存区。

---

## 作者：liuyi0905 (赞：0)

注意到题目中有这样一句话：最美丽的花的美丽度不小于其它任何一朵花的美丽度的两倍。

设第二美丽的花的美丽度为 $v$，则最美丽的花美丽度至少为 $2v$，两者相差最小为 $v$；因为 $a_i\ge1$，所以其他花中相差最大为 $v-1$。因此最美丽的花一定在相差最大的两朵花之间。

我们还会发现，不一定要将两两的差求出来，只需要问 $|a_1-a_2|,|a_3-a_4|,\cdots|a_{n-1}-a_n|$，这样问会包含所有的点，没有遗漏，花费次数 $\lfloor\frac{n}{2}\rfloor$。

设相差最大的组为 $(p,p+1)$，则最美丽的花一定是 $p$ 或 $p+1$，最后只需询问这两朵花与另一朵花的差，再比较一次大小就行。

这样很容易写出代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k;
int main() {
  for (cin >> t; t; t--) {
    cin >> n >> k;
    int r = -1e9, p;
    for (int i = 1, x; i < n; i += 2) {
      cout << "? " << i << " " << i + 1 << endl;
      cin >> x, x > r && (r = x, p = i);
    }
    int v = (p != 1 ? 1 : n), x, y;
    cout << "? " << v << "  " << p << endl, cin >> x;
    cout << "? " << v << "  " << p + 1 << endl, cin >> y;
    cout << "! " << (x > y ? p : p + 1) << "\n";
  }
  return 0;
}
```
~~很高兴的 WA 了最后一个点~~

因为每次是两个两个询问的，所以当 $n$ 为奇数时，最后一个点没有问到，剩下两个点要与 $n$ 求差，设为 $x$ 和 $y$，如果 $x$ 和 $y$ 都大于其他任何两点的差，说明答案就是 $n$。

因此可以修改代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k;
int main() {
  for (cin >> t; t; t--) {
    cin >> n >> k;
    int r = -1e9, p;
    for (int i = 1, x; i < n; i += 2) {
      cout << "? " << i << " " << i + 1 << endl;
      cin >> x, x > r && (r = x, p = i);
    }
    int v = (p == n - 1 ? 1 : n), x, y;
    cout << "? " << v << " " << p << endl, cin >> x;
    cout << "? " << v << " " << p + 1 << endl, cin >> y;
    cout << "! " << (n % 2 && x > r && y > r ? n : x > y ? p : p + 1) << "\n";
  }
  return 0;
}
```
这样我们就愉快的 AC 了。

---

