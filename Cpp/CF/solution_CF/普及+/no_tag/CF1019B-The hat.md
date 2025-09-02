# The hat

## 题目描述

This is an interactive problem.

Imur Ishakov decided to organize a club for people who love to play the famous game «The hat». The club was visited by $ n $ students, where $ n $ is even. Imur arranged them all in a circle and held a draw to break the students in pairs, but something went wrong. The participants are numbered so that participant $ i $ and participant $ i+1 $ ( $ 1<=i<=n-1 $ ) are adjacent, as well as participant $ n $ and participant $ 1 $ . Each student was given a piece of paper with a number in such a way, that for every two adjacent students, these numbers differ exactly by one. The plan was to form students with the same numbers in a pair, but it turned out that not all numbers appeared exactly twice.

As you know, the most convenient is to explain the words to the partner when he is sitting exactly across you. Students with numbers $ i $ and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1019B/59f224a8151ecadc368b840c31ed2d1a88e25415.png) sit across each other. Imur is wondering if there are two people sitting across each other with the same numbers given. Help him to find such pair of people if it exists.

You can ask questions of form «which number was received by student $ i $ ?», and the goal is to determine whether the desired pair exists in no more than $ 60 $ questions.

## 说明/提示

Input-output in statements illustrates example interaction.

In the first sample the selected sequence is $ 1,2,1,2,3,4,3,2 $

In the second sample the selection sequence is $ 1,2,3,2,1,0 $ .

## 样例 #1

### 输入

```
8

2

2
```

### 输出

```

? 4

? 8

! 4
```

## 样例 #2

### 输入

```
6

1

2

3 

2

1

0```

### 输出

```

? 1

? 2

? 3

? 4

? 5

? 6

! -1```

# 题解

## 作者：Piwry (赞：2)

## 解析

设 $d(i)$ 表示第 $i$ 位和他对面位置的数字的差，那么我们要找的就是 $d(i)=0$ 的位置

首先发现 $n$ 无法被 $4$ 整除时一定无解。只需考虑此时每个人和对面相差的位数是奇数，因此他们的数字的奇偶性一定不同

（下面仅考虑 $n$ 被 $4$ 整除的情况）

接着考虑 $d(i)$ 的性质。不难发现当 $i$ 变化 $1$ 时，$d(i)$ 仅能变化 $\{-2, 0, 2\}$，于是 $d(i)$ 的奇偶性不会变

（不难发现若有某个 $d(i)$ 不为偶数，那么一定无解；不过其实这就等价于 $n$ 无法被 $4$ 整除）

我们考虑先询问出 $d(1)$（即询问 $1$ 与 $\frac n 2 +1$）；可以发现 $d(1)$ 一定为偶数（因为 $n$ 可被 $4$ 整除，因此每个 $i$ 和对面的位置差一定为偶数，于是数字差也是偶数）

如果 $d(1)=0$，那么我们显然就得到了解

否则因为有 $d(\frac n 2 +1)=-d(1)$，于是 $d(1), d(\frac n 2 +1)$ 的值域跨度中包含 $0$，因此一定有解

而这时可以考虑二分找到解的位置

具体来说，初始设 $l=1, r=\frac n 2 +1$；每次询问 $\texttt{mid}$ 时，若 $d(\texttt{mid})$ 非 $0$，我们就取值域跨度包含 $0$（与 $d(\texttt{mid})$ 符号不同的那个端点；可以证明每时刻的 $d(l), d(r)$ 的符号一定是不同的，因此 $d(l), d(r)$ 一定有一个与 $d(\texttt{mid})$ 符号不同）的那个区间继续二分。由于解存在，这样二分下去一定能找到解

关于二分时 $d(l), d(r)$ 的符号，可以证明一定是不同的。首先初始时应有 $d(l), d(r)$ 符号不同；每次缩小区间时，我们选择的端点的符号和 $d(\texttt{mid})$ 的符号也是不同的，于是下次的 $d(l), d(r)$ 的符号也是不同的

这里的二分的实现的一些细节可能和一般的二分不太一样，具体可参考代码

## CODE

```cpp
#include <cstdio>

const int MAXN =1e5+20;

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

int n;
int a[MAXN];
bool vis[MAXN];

inline void Ask(const int &i){
	printf("? %d\n", i);
	fflush(stdout);
	a[i] =read();
}

inline int get_b(const int &x){
	if(!vis[x])
		Ask(x), vis[x] =1;
	if(!vis[(x-1 + n/2)%n+1])
		Ask((x-1 + n/2)%n+1), vis[(x-1 + n/2)%n+1] =1;
	return a[(x-1 + n/2)%n+1]-a[x];
}

int main(){
	n =read();
	if(n%4 != 0)
		puts("! -1");
	else{
		if(get_b(1) == 0)
			printf("! %d\n", 1);
		else{/*显然应有 b(1)*b(n/2) < 0*/
			int l =1, r =n/2+1;
			while(l < r){/*应当一定有解*/
				int mid =(l+r)>>1;
				if(get_b(mid) == 0){
					printf("! %d\n", mid);
					break;
				}
				else if(get_b(l)*get_b(mid) < 0)
					r =mid;
				else
					l =mid;
			}
		}
	}
}
```

---

## 作者：Mihari (赞：2)

@kkksc03 管理员大大，我已经在本题讨论区给出本题翻译及 `markdown` 源码，请注意查收！

# 题目

## 背景

这是一道交互题。

一共有 $n$ 个人做成一圈，他们的编号从 $1$ 到 $n$。

现在每个人的手里面都有一个数字 $a_i$ ，并且保证每个人与他周围两个人的数字差为 $1$ ，即 $\mid a_i-a_{i\pm 1}\mid =1$ ，特别地，编号为 $1$ 与 $n$ 的人也满足这个规则。

在这个圈里面，编号为 $i$ 的人的对面坐着的是编号为 $i+\frac{n}{2}$ 的人（其中 $i\le \frac{n}{2}$），现在要你找到哪个人与他对面坐着的那个人手中的数字一样。

## 程序输出

在最开始，交互程序会给你一个 $n(2\mid n, n\le 10^5)$ ，表示这个圈里面的人数，然后你可以输出以下两种格式的操作：

1. `? x` 表示你想询问位置为 $x$ 的人手中的数字，询问不可执行超过 $60$ 次；
2. `! x` 表示你的程序的答案，即满足 $a_x=a_{x+\frac{n}{2}}(x\le \frac{n}{2})$ ，特别地，如果找不到答案，则输出 `! -1` ；

## 交互程序输入

对于操作 $1$ ，交互程序会输出一个整数 $a_x$ 表示 $x$ 编号的人手中的数字。

对于操作 $2$ ，如果你的答案是错误的，程序会直接退出，且测试结果为 `Wrong Answer` ，否则**若无其他问题**则测试结果为 `Accepted` 。

# 题解

一道十分有思维含量的好题 ~~我太弱了，想了一个小时~~ 。

首先，若 $n=4k+2$ ，那么 $\frac{n}{2}=2k+1$ ，即对于位置 $i$ ，它对面的位置 $i+\frac{n}{2}=i+2k-1$ ，可以发现他们相差**奇数个**位置，那么一定有他们的奇偶性不同，即他们一定不同，所以当 $n=4k+2$ 时一定无解，至于 $n=4k+1$ 或者 $n=4k+3$ ，那是不可能的，题目保证 $2\mid n$ 。

所以，只有当 $4\mid n$ 时才有解，现在我们考虑如何快速求解。

对于位置 $i,i\in [1,n]$ ，我们设它对面的位置为 $i'$ ，再记 $a_i-a_{i'}=t_i$ ，那么一定有 $2\mid t_i$ 且 $t_i-t_{i+1}=\pm 2 或 0$，下面给出后者的解释：

1.  当 $a_i=a_{i+1}+1$ ，且 $a_{i'}=a_{(i+1)'}+1$ 时，$t_{i+1}=a_i-1-a_{i'}+1=a_i-a_{i'}$ ，即 $t_i-t_{i+1}=0$ ；
2. 3. 种情况可以用上面的方法自行思考

现在我们要求的，就是一个位置 $i$ 能够满足 $d_i=0$ 。

而我们已经证明 $t_i$ 之间的差为 $\pm 2 或 0$ ，那么，假设我们枚举一个区间到一个区间 $[l,r]$ ，如果 $t_l$ 与 $t_r$ 异号，则满足 $t_i=0$ 的 $i$ 一定属于区间 $[l,r]$ 。

如果还有一些问题，可见程序。

[程序看这里](https://www.cnblogs.com/Arextre/p/12260753.html) ~~很不要脸地安利自己地博客~~

---

## 作者：Iam1789 (赞：1)

这是个水题，~~但我还是调了半天~~

首先判断无解，不难发现当且仅当 $n/2$ 为奇数时是无解的，下面给出证明：

为了方便，下面称加减 $1$ 为一次操作。

令 $l=1,r=1+n/2$，因为 $n/2$ 为奇数，$a_r$ 一定是由 $a_l$ 通过奇数次操作得到，所以 $a_l,a_r$ 的奇偶性是相反的。因此，将 $a_l,a_r$ 进行 $x$ 操作后得到的数，奇偶性也是相反的，显然不可能相等。反之，若 $n/2$ 为偶数，之间一定有数相等。

接下来就是找出相等的 $l,l+n/2$，~~一开始我还以为有什么精妙的技巧~~，后来发现 $l$ 左边的数与对面数的大小关系和另一边是相反的，我们直接二分或者倍增找就可以。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
inline int Ask(int x)
{
	printf("? %d\n",x);
	fflush(stdout);
	scanf("%d",&x);
	return x;
}
inline void Ans(int x)
{
	printf("! %d\n",x);
	fflush(stdout);
}
int main()
{
	scanf("%d",&n);
	if((n>>1)&1)
	{
		Ans(-1);
		return 0;
	}
	int l=1,r=1+n/2;
	int a=Ask(l),b=Ask(r);
	if(a==b)
	{
		Ans(l);
		return 0;
	}
	long long cc=a-b;
	int p=1;
	while(p<n/2)
	{
		p*=2;
	}
	p>>=1;
	while(1)
	{
		a=Ask((l+p-1)%n+1);
		b=Ask((r+p-1)%n+1);
		if(a==b)
		{
			Ans((l+p-1)%n+1);
			return 0;
		}
		int qwq=a-b;
		if(cc*qwq>0)
		{
			l=(l+p-1)%n+1;
			r=(r+p-1)%n+1;
		}
		p>>=1;
	}
	return 0;
}
```


---

## 作者：Priestess_SLG (赞：0)

标题倒着读有彩蛋（

这怎么才绿啊？？？？？？这很难啊！！！！！

**首**先考虑对 $n$ 分类讨论：

+ 若 $n\equiv 2(\bmod\ 4)$，则 $2\nmid\frac{n}{2}$，此时：
  + 有一个长度为偶数的序列，令其长度为 $2p$，相邻两项的值的差的绝对值为 $1$。此时有 $2p-1$ 个间隔，因为加一和减一的奇偶性相同，因此该序列首尾两项的奇偶性不同，也就是说序列首尾两项的值一定不同。此时一定不存在一个合法的 $x$ 满足编号为 $x$ 和编号为 $x+\frac{n}{2}$ 的人的编号相同。因此无解。

因此只需要考虑 $n=4k$（$k\in\mathbb{N}_+$）的情况。此时可以证明，若 $n\equiv 0(\bmod\ 4)$，即 $2\mid\frac{n}{2}$，则此时必然至少存在一个 $x$ 满足编号为 $x$ 和编号为 $x+\frac{n}{2}$ 的人的编号相同。（证明的话可以感性理解一下，其实是我不会证只会猜）

然后考虑设 $F(i)$ 表示 $|a_i-a_{i+\frac{n}{2}}|$。因为 $4\mid n$，所以可以证明 $2\mid F(i)$：因为 $4\mid n$ 所以间隔数量必然是偶数，奇偶性一定相同，她们的差也就必然是偶数啦 qwq

但是干巴巴的设一个 $F(i)$ 的用途等同于~~掷骰子掷出来一个可爱班花殷浩宝~~没有，所以分析她的性质！！！

性质 $1$：对于 $F(i)$ 和 $F(i+1)$，容易发现 $F(i)\equiv F(i+1)(\bmod\ 2)$。因为 $a_i$ 和 $a_{i+1}$ 之间变化的值为 $-1$ 或 $1$，$a_{i+1}$ 和 $a_{i+2}$ 之间变化的值也为 $-1$ 或 $1$，以此类推……因此可以开心的发现 $\forall i\in[1,n],F(i)$ 的奇偶性相同。

性质 $2$：$F(i)=-F(i+\frac{n}{2})$，这还是很显然的（

有了上面两个性质就可以做题啦！！考虑先询问 $F(1)$ 的值。令 $x=F(1)$，则：

+ $x=0$，则说明 $a_1-a_{\frac{n}{2}+1}=0$，即 $a_1=a_{\frac{n}{2}+1}$。此时 $i=1$ 即是问题一组合法的解。
+ 否则 $F(x)>0>F(x+\frac{n}{2})$ 或 $F(x)<0<F(x+\frac{n}{2})$。

然后考虑一个逆天的在环上二分！因为刚刚的分析，考虑破换成链，只需要在 $1\sim \frac{n}{2}+1$（即左半环）上二分答案。令 $l=1$，$r=\frac{n}{2}+1$。则此时二分答案 $\text{mid}$。令 $X=F(\text{mid})$，则：

+ $X=0$，则 $i=\text{mid}$ 即为一组合法的答案。
+ $X\neq 0$，则 $[l,\text{mid})$ 和 $(\text{mid}
  ,r]$ 两个区间内必然至少存在一个 $p\in\mathbb{N}_+$ 满足 $F(p)=0$。且可以证明另一个函数 $G(x)=\frac{F(x)}{2}$ 在整数集上连续，因此考虑看 $F(x)$、$F(y)$ 中哪一个和 $X$ 符号不一致。找出不一致的那一侧继续二分，容易证明该段区间内必然至少存在一组解。

然后我们就以 $O(n)$ 的时间复杂度，$\log$ 级别的询问次数完成了这个题。可以证明做法正确。

代码（真心好写）：

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define eb emplace_back
#define pb push_back
using namespace std;
const int N=1000100;int n;
inline int ask(int x){cout<<"? "<<x<<endl;int o;cin>>o;return o;}
inline void qd(int x){cout<<"! "<<x<<endl;}
int a[N];inline int Task(int x){if(~a[x])return a[x];return a[x]=ask(x);}
inline int Fask(int x){int pw=x+n/2;if(pw>n)pw-=n;return Task(x)-Task(pw);}
signed main(){
    memset(a,-1,sizeof a);cin>>n;
    if(n%4==2){qd(-1);return 0;}
    int os=Fask(1);if(os==0){qd(1);return 0;}
    int l=1,r=n/2+1;
    while(l<=r){
        int mid=l+r>>1,mv=Fask(mid);
        if(!mv){qd(mid);return 0;}
        int ml=Fask(l);if(ml*mv<0)r=mid-1;else l=mid+1;
    }
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

询问次数 $60$，而 $n\le 10^5$，大胆猜一手在 $k\log n$ 这样。

题目已经给了相邻的 $a_i$ 恰好相差 $1$，我们由此挖掘性质。不难想到奇数位置的数和 $1$ 的奇偶性相同，偶数位置则相反。证明显然。这个结论等价于两个数相等的必要条件是位置的奇偶性相同。

因为 $2\mid n$，所以 $n=4m+2$ 或 $n=4m$，其中 $m$ 为正整数。

对于 $n=2m+2$，我们需要找到 $a_i=a_{i+2m+1}$，那么，这两个位置的奇偶性不同，无解！

好，现在只剩 $n=4m$ 的情况了。相当于 $a_i=a_{i+2m}$。由于 $a_i-a_{i+1}\in \{-1,1\}$，$a_{i+2m}-a_{i+2m+1}\in \{-1,1\}$，那么高明的性质就被发现了：



+ 设 $F(i)=\left\{
\begin{array}{rcl}
a_x-a_{x+2m}       &      & {1\le x\le 2m}\\
a_x-a_{x-2m}     &      & {2m<x\le 4m}\\
\end{array} \right.
$

+ 则有性质 $F(i+2m+1)-F(i+2m)\in \{-2,0,2\}$，证明分类讨论 $a_i-a_{i+1}$ 和 $a_{i+2m}-a_{i+2m+1}$ 即可。

更加具体的，$F(i)-F(i-1)\in\{-2,0,2\}$！而我们要找的，就是某个 $F(i)=0$。

考虑一下，如果我们知道了 $F(x)$ 和 $F(x+2m)$，能否找到那个 $0$？答案是可以！由 $F$ 定义我们知道，$F(i)+F(i+2m)=0$ 对吧，如果两个都是 $0$
 就是找到了，否则只有前者正后者负，或者前者负后者正两种可能。大概是什么样呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/g12ez5wo.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/x1xfh49u.png)

不难发现，由于 $F(i+2m+1)-F(i+2m)\in \{-2,0,2\}$，所以，如果两者不同号，则区间内必然存在 $0$！

配上一个二分即可，而我们可以两次查询查出 $F(i)$，所以最后的次数是 $2\log$ 级别，$60$ 太稳了！


```cpp 
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define clr() fflush(stdout);
const int N=1e5+5; int a[N], F[N];
int i, j, n, l, r, mid;
inline void qry(int x) {printf("? %d\n", x); clr(); scanf("%d", a+x);}
int main()
{
	scanf("%d", &n);
	if(n&3) {puts("! -1"); clr(); return 0;}
	l=1; r=n/2; qry(l); qry(l+n/2); qry(r); qry(r+n/2); F[l]=a[l]-a[l+n/2]; F[r]=a[r]-a[r+n/2];
	if(F[l]==0 || F[r]==0)
	{
		printf("! %d\n", (!F[l])*l+(!F[r])*r);
		clr();
	}else
	{
		while(l<r)
		{
			mid=l+r>>1;
			qry(mid); qry(mid+n/2);
			F[mid]=a[mid]-a[mid+n/2];
			if(F[mid]==0)
			{
				printf("! %d\n", mid); clr();
				break;
			}
			else if(F[l]*F[mid]<0) r=mid;
			else l=mid;
		} if(F[mid]) {puts("! -1"); clr();}
	}
	return 0;
}
```

---

