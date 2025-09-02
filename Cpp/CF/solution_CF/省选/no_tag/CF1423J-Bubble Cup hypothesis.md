# Bubble Cup hypothesis

## 题目描述

The Bubble Cup hypothesis stood unsolved for $ 130 $ years. Who ever proves the hypothesis will be regarded as one of the greatest mathematicians of our time! A famous mathematician Jerry Mao managed to reduce the hypothesis to this problem:

Given a number $ m $ , how many polynomials $ P $ with coefficients in set $ {\{0,1,2,3,4,5,6,7\}} $ have: $ P(2)=m $ ?

Help Jerry Mao solve the long standing problem!

## 说明/提示

In first case, for $ m=2 $ , polynomials that satisfy the constraint are $ x $ and $ 2 $ .

In second case, for $ m=4 $ , polynomials that satisfy the constraint are $ x^2 $ , $ x + 2 $ , $ 2x $ and $ 4 $ .

## 样例 #1

### 输入

```
2
2 4```

### 输出

```
2
4```

# 题解

## 作者：Querainy (赞：9)

好奇妙的题啊/kk

一道核心代码一行的2500题（

题意 : 有$1e5$次询问，每次给出一个$m$，求

$$
x_02^0+x_12^1+x_22^2+x_32^3+\cdots=m\space (0\leq x_i\leq 7)
$$

的整数解组数。

看到这个$0$到$7$，容易想起八进制。

于是可以写出如下柿子 : 

$$
\begin{aligned}
&x_02^0+x_12^1+x_22^2+x_32^3+x_42^4+x_52^5+x_62^6+x_72^7+x_82^8+\cdots\\
=&x_02^0+2x_12^0+4x_22^0+x_32^3+2x_42^3+4x_52^3+x_62^6+2x_72^6+4x_82^6+\cdots\\
=&(x_08^0+x_38^1+x_68^2+\cdots)+2(x_18^0+x_48^1+x_78^2+\cdots)+4(x_28^0+x_58^1+x_88^2+\cdots)
\end{aligned}
$$

于是，三个括号里面是三个八进制数，设它们为$a,b,c$，那么原问题就变成了$a+2b+4c=m$的自然数解组数。

先考虑$a=m$的解数，显然是$1$。

$a+2b=m$的解数，对于每个$0\leq b\leq\lfloor\frac{m}{2}\rfloor$，$a$都有一个满足方程的取值，所以这东西解数是$\lfloor\frac{m}{2}\rfloor+1$。

同理，对于$a+2b+4c=m$，解数是

$$
\begin{aligned}
&\sum_{c=0}^{\lfloor\frac{m}{4}\rfloor}(\lfloor\frac{m-4c}{2}\rfloor+1)\\
=&\sum_{c=0}^{\lfloor\frac{m}{4}\rfloor}(\lfloor\frac{m}{2}-2c\rfloor+1)\\
=&\sum_{c=0}^{\lfloor\frac{m}{4}\rfloor}(\lfloor\frac{m}{2}\rfloor-2c+1)\\
=&(\lfloor\frac{m}{4}\rfloor+1)\lfloor\frac{m}{2}\rfloor-\lfloor\frac{m}{4}\rfloor(\lfloor\frac{m}{4}\rfloor+1)+\lfloor\frac{m}{4}\rfloor+1\\
=&(\lfloor\frac{m}{4}\rfloor+1)(\lfloor\frac{m}{2}\rfloor-\lfloor\frac{m}{4}\rfloor+1)
\end{aligned}
$$

就做完了。

```cpp
#include<stdio.h>

const long long p=1e9+7;

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		long long m;
		scanf("%lld",&m);
		printf("%d\n",(m/4+1)%p*((m/2-m/4+1)%p)%p);
	}
}
```

(一定记得先膜再乘)

---

## 作者：chenxia25 (赞：3)

本来是想刷水题过日子来着，就随便开了个 2400，结果发现是个神仙题/kk

---

**[Portal]( https://www.luogu.com.cn/problem/CF1423J )**

首先注意到，当 $2^{0\sim i}$ 的系数都填上 $7$ 时，这时候的结果等于 $7\sum\limits_{j=0}^i2^j=7\left(2^{i+1}-1\right)$，最小的严格覆盖它的 $2$ 的整次幂是 $2^{i+4}$，也就是最多会超出 $2^i$ 三位。于是我们可以从低位往高位 DP，任意时刻需要满足前 $i$ 位都符合了，因为以后再也不可能影响到它们了，然后需要记录后面三位是多少。转移的时候就直接枚举状态，减一下，看当前系数是否在 $[0,8)$ 内，然后加上去。于是我们得到了一个 $\mathrm O\!\left(T\cdot 60\times 8^2\right)$ 的算法，算一下是 1e9，但是只有加法，写个快模常数会非常小，于是考虑莽一波。

```cpp
for(int i=1;i<=60;i++)for(int j=0;j<8;j++){
	int shd=(j<<1)+((x>>i-1)&1);
	dp[i][j]=0;
	for(int k=0;k<8;k++)
		0<=shd-k&&shd-k<8&&add(dp[i][j],dp[i-1][k]);
}
```

显然会 T，$n=10^5$ 的时候已经 $889\mathrm{ms}$ 了。接下来考虑施展卡常大法/cy

首先手动 O3，`fread` / `fwrite` 快读快写走起。然后发现 `#define int long long` 会严重降低效率，于是只把读入设成 `ll` 其他都用 `int`。然后将 `for(k)` 这层循环展开，注意到 `dp[i][j]` 多次使用，于是取个引用避免多次计算地址。

```cpp
for(int i=1;i<=60;i++)for(int j=0;j<8;j++){
	const int shd=(j<<1)+((x>>i-1)&1);int &d=dp[i][j]=0;
	0<=shd&&shd<8&&(d+=dp[i-1][0])>=mod&&(d-=mod),
	1<=shd&&shd<9&&(d+=dp[i-1][1])>=mod&&(d-=mod),
	2<=shd&&shd<10&&(d+=dp[i-1][2])>=mod&&(d-=mod),
	3<=shd&&shd<11&&(d+=dp[i-1][3])>=mod&&(d-=mod),
	4<=shd&&shd<12&&(d+=dp[i-1][4])>=mod&&(d-=mod),
	5<=shd&&shd<13&&(d+=dp[i-1][5])>=mod&&(d-=mod),
	6<=shd&&shd<14&&(d+=dp[i-1][6])>=mod&&(d-=mod),
	7<=shd&&shd<15&&(d+=dp[i-1][7])>=mod&&(d-=mod);
}
```

目前 $n=10^5$ 已经降低到 $404\mathrm{ms}$，继续卡。我们考虑将 `for(j)` 这层也展开。这下好了，发现新大陆了。发现对于每次转移，能够转移的条件是关于 $j=0$ 时的 $shd$ 的一个不等式，而它是个 $0/1$，不像 $j>0$ 的时候还要加上 `j<<1`。然后还有，全部展开的话，会发现对于某些 $j,k$ 根本无论如何也不可能转移，这样可以直接手动删除。于是这样展开后，转移分为三类：仅 $shd=0$ 时，仅 $shd=1$ 时，所有时。总共的转移量只有 $36$，比原来的 $8^2=64$ 要少了一半。顺便再把 $dp_{i,0\sim 7}$ 一起取个引用，发挥通常情况下循环展开的作用。

```cpp
for(int i=1;i<=60;i++){
	const bool shd=(x>>i-1)&1;
	int &d0=dp[i][0],&d1=dp[i][1],&d2=dp[i][2],&d3=dp[i][3],&d4=dp[i][4],&d5=dp[i][5],&d6=dp[i][6],&d7=dp[i][7];
	#define add(x,y) (d##x+=dp[i-1][y])>=mod&&(d##x-=mod)
	shd||(add(4,1),add(5,3),add(6,5),add(7,7)),
	add(3,0),add(4,2),add(5,4),add(6,6),
	add(3,1),add(4,3),add(5,5),add(6,7),
	add(2,0),add(3,2),add(4,4),add(5,6),
	add(2,1),add(3,3),add(4,5),add(5,7),
	add(1,0),add(2,2),add(3,4),add(4,6),
	add(1,1),add(2,3),add(3,5),add(4,7),
	add(0,0),add(1,2),add(2,4),add(3,6),
	shd&&(add(0,1),add(1,3),add(2,5),add(3,7));
}
```

此时 $n=10^5$ 需要跑 $280\mathrm{ms}$，算一下 $n=5\times 10^5$ 的时候是 $1.4\mathrm s$，快成功了。进一步，根据一堆寻址，如果按照地址连续寻址会更快这个理论，我们把中间一堆所有时的转移按照第一维排个序，快了大概 $0.1\mathrm s$。然后注意到 $dp_{i,0\sim 7}$ 多次使用，虽然已经取引用了，但还有更快的访问方法：存到寄存器里（只有 $8$ 个，寄存器装得下）。注意 `register int &d0=dp[i][0];` 是卵用没有的，因为它到底还是取了引用，那么就不可能把这个变量从原来处于的地方给重新装到寄存器里。于是必须重新定义变量，在一开始定义的时候就装到寄存器里，算完之后再赋到 `dp` 数组里。

```cpp
for(int i=1;i<=60;i++){
	bool shd=(x>>i-1)&1;
	register int d0=0,d1=0,d2=0,d3=0,d4=0,d5=0,d6=0,d7=0;
	#define add(x,y) (d##x+=dp[i-1][y])>=mod&&(d##x-=mod)
	add(0,0),add(1,0),add(1,1),add(1,2),add(2,0),add(2,1),add(2,2),add(2,3),add(2,4),add(3,0),add(3,1),add(3,2),add(3,3),add(3,4),add(3,5),add(3,6),add(4,2),add(4,3),add(4,4),add(4,5),add(4,6),add(4,7),add(5,4),add(5,5),add(5,6),add(5,7),add(6,6),add(6,7),
	shd||(add(4,1),add(5,3),add(6,5),add(7,7)),shd&&(add(0,1),add(1,3),add(2,5),add(3,7));
	dp[i][0]=d0,dp[i][1]=d1,dp[i][2]=d2,dp[i][3]=d3,dp[i][4]=d4,dp[i][5]=d5,dp[i][6]=d6,dp[i][7]=d7;
}
```

这个寄存器的效果是真的惊人，直接给我最大点跑了 $608\mathrm{ms}$。至此这道题被我野蛮的 AC 了。所以这道题是一个练习卡常的好题（×

---

显然上面那个不是正解，而是我自己瞎 yy 的，所以接下来讲正解。

考虑将一组系数 $x_{0\sim n}$ 满足条件的式子写出来：
$$
\sum\limits_{i=0}^n2^ix_i=m
$$
注意到 $x_i\in[0,8)$，想到八进制，考虑将这么多项三个分一组：
$$
\sum_{i=0}^{\frac n3}8^i(x_{3i}+2x_{3i+1}+4x_{3i+2})=m
$$
$$
\sum_{i=0}^{\frac n3}8^ix_{3i}+2\sum_{i=0}^{\frac n3}8^ix_{3i+1}+4\sum_{i=0}^{\frac n3}8^ix_{3i+2}=m
$$
这时候注意到，这三项等价于八进制数，也就是值与 $x$ 一一对应，于是我们只要计算关于正整数 $a,b,c$ 的方程 $a+2b+4c=m$ 的解的组数即可。这个就非常简单了：
$$
\begin{aligned}ans&=\sum_{i=0}^{\left\lfloor\frac m4\right\rfloor}\sum_{j=0}^{\left\lfloor\frac{m-4i}2\right\rfloor}1\\&=\sum_{i=0}^{\left\lfloor\frac m4\right\rfloor}\left(\left\lfloor\dfrac{m-4i}2\right\rfloor+1\right)\\&=\sum_{i=0}^{\left\lfloor\frac m4\right\rfloor}\left(\left\lfloor\dfrac m2\right\rfloor+1-2i\right)\\&=\left(\left\lfloor\dfrac m4\right\rfloor+1\right)\left(\left\lfloor\dfrac m2\right\rfloor+1\right)-\left\lfloor\dfrac m4\right\rfloor\left(\left\lfloor\dfrac m4\right\rfloor+1\right)\end{aligned}
$$


---

## 作者：LXcjh4998 (赞：2)

[Luogu 链接](https://www.luogu.com.cn/problem/CF1423J)

[Codeforces 链接](https://codeforces.com/problemset/problem/1423/J)
# 题意
给定一正整数 $y$（$1\le y\le10^{18}$），求有多少不同的多项式 $P$，使得：
- $P(2)=y$。
- 多项式 $P$ 的任意一项的系数 $a$ 都有：$a\in\mathbb Z$，且 $0\le a<8$。

由于答案可能很大，你只需输出其对 $10^9+7$ 取模后的值。

多测，组数 $T\le5\times10^5$。
# 思路
看到 $8$，不妨往八进制上想一想。

首先设此多项式为：
$$a_0\times x^0+a_1\times x^1+a_2\times x^2+\cdots$$

令 $x=2$，则有：
$$\begin{aligned}
y&=a_0\times2^0+a_1\times2^1+a_2\times2^2+\cdots\\
&=(a_0\times8^0+a_3\times8^1+\cdots)+2\times(a_1\times8^0+a_4\times8^1+\cdots)+4\times(a_2\times8^0+a_5\times8^1+\cdots)
\end{aligned}$$

因此，我们可以将括号内的三个八进制数设为 $a$、$b$、$c$，问题就转化为求 $a+2\times b+4\times c=y$ 的自然数解的组数。

考虑 $a+2\times b=y'$ 时，此时显然 $b$ 取 $0$ 至 $\lfloor\dfrac{y'}{2}\rfloor$ 的所有整数都符合条件，所以组数为 $\lfloor\dfrac{y'}{2}\rfloor+1$。

令 $y'=y-4\times c$，显然 $c$ 可以取 $0$ 至 $\lfloor\dfrac{y}{4}\rfloor$ 的所有整数，所以总的组数为：
$$\begin{aligned}
\sum_{c=0}^{\lfloor\frac{y}{4}\rfloor}(\lfloor\dfrac{y-4\times c}{2}\rfloor+1)&=\sum_{c=0}^{\lfloor\frac{y}{4}\rfloor}(\lfloor\dfrac{y}{2}\rfloor -2\times c+1)\\
&=\lfloor\dfrac{y}{2}\rfloor\times(\lfloor\dfrac{y}{4}\rfloor+1)-\lfloor\dfrac{y}{4}\rfloor\times(\lfloor\dfrac{y}{4}\rfloor+1)+(\lfloor\dfrac{y}{4}\rfloor+1)\\
&=(\lfloor\dfrac{y}{2}\rfloor-\lfloor\dfrac{y}{4}\rfloor+1)\times(\lfloor\dfrac{y}{4}\rfloor+1)
\end{aligned}$$
# 程序
[AC 记录](https://codeforces.com/contest/1423/submission/312186787)
```cpp
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<iomanip>
#include<string>
#include<stack>
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define ls rt<<1
#define rs rt<<1|1
#define lb(x) (x&-x)
#define pb push_back
using namespace std;
const ll mod=1e9+7;
//#define use_file
#define more_test
//#define need_init
#ifdef more_test
int T;
#endif

ll y;

void SOLVE(/*int test_id*/){
	scanf("%lld",&y);
	printf("%lld\n",((y>>2)+1)%mod*(((y>>1)-(y>>2)+1)%mod)%mod);
}
int main(){
	#ifdef use_file
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	#ifdef need_init
	init();
	#endif
	#ifdef more_test
	scanf("%d",&T);
	for(int i=1;i<=T;++i)SOLVE(/*i*/);
	#else
	SOLVE(/*1*/);
	#endif
	return 0;
}
```

---

## 作者：Gokix (赞：2)

[CF1423J](https://www.luogu.com.cn/problem/CF1423J)

是 qyc 爷爷(@[华山抡剑](https://www.luogu.com.cn/user/152213))选为我们社团的纳新题和校内模拟赛题。

我的做法没有 qyc 爷爷的那么简洁，但我还是分享一下。其实到最后本质是一样的？

------------

考虑把 $8$ 进制数拆成 $3$ 位 $2$ 进制数，然后写成竖式的形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/x2ffq5si.png)

我们假设 $m$ 是个 $7$ 位 $2$ 进制数，然后各项 $x$ 的系数位 $a_i$。

注意到除了第一位（我们把数的位倒过来说，比如 $110$ 的第一位是 $0$）有一个数加起来、第二位有两个数加起来，更高为都是三个数加起来。所以我们不妨把这一堆 $2$ 进制数拍扁成 $3$ 个 $2$ 进制数：

![](https://cdn.luogu.com.cn/upload/image_hosting/szd6wxf6.png)

注意到第一位不会对答案个数有影响，因为它只能是 $m$ 的第一位。

第二位讨论一下。如果 $m$ 的第二位是 $1$，那么加起来的方式有两个($0 \space 1$ 和 $1 \space 0$)，不会对更高位造成影响。最终答案个数即为最高位的答案个数乘 $2$。

如果 $m$ 的第二位是 $0$，则两种方式($0 \space 0$ 和 $1 \space 1$)不同。$0 \space 0$ 不会对更高位产生影响。但 $1 \space 1$ 会产生进位，处理方法是在更高位统计时先把答案(及下文 $M$)减 $2$。最终答案个数为这两种方式答案个数之和。

考虑在第三位之上的如何统计。现在我们的问题转化为了：$3$ 个未知有序位数相等的 $2$ 进制数加起来等于一已知同位数二进制数(即 $\lfloor \frac{m}{4} \rfloor$，记作 $M$)的方法有多少种。

通过推式子或者模拟暴力过程可以很明显地看出答案个数是 $\frac{(M+1)(M+2)}{2}$，然后这题就结束了。

------------

或许讨论半天其实综合起来答案好像就是 $(\lfloor \frac{m}{4} \rfloor +1)(\lfloor \frac{m}{2} \rfloor - \lfloor \frac{m}{4} \rfloor + 1)$，但我的心路历程不一样，所以还是写了出来。不过这个做法好像有个常数，导致得卡卡常才能过。

```cpp
#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

long long t,m,n,M,a[100],ans;
const long long P=1e9+7;

void init(){
	n=0;ans=0;
}
inline long long read(){
    char ch=getchar(); long long x=0,f=1;
    while(ch<'0' || ch>'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    } 
    while('0'<=ch && ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    } 
    return x*f;
}
inline void write(long long x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

int main(){
	//freopen("tears.in","r",stdin);
	//freopen("tears.out","w",stdout);
	long long i,j,u,v;
	t=read();
	while(t--){
		m=read();
		init();
		u=m;
		a[1]=m%2;
		a[2]=m/2%2;
		if(n==1){
			ans=1;
		}
		else if(n==2){
			if(a[2]==1) ans=2;
			else ans=1;
		}
		else{
			if(a[2]&1){
				ans=2;
				M=m>>2;
				M%=P;
				ans*=(M+1)*(M+2)/2;
			}
			else{
				M=m>>2;
				M%=P;
				ans=(M+1)*(M+2)/2;
				M=(m-2)>>2;
				M%=P;
				ans+=(M+1)*(M+2)/2;
			}
		}
		write(ans%P);putchar('\n');
	}
	return 0;
}
```


---

