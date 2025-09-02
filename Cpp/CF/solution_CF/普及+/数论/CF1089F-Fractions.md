# Fractions

## 题目描述

给定一个$n$，确定一些分数，使得这些分数的分母是$n$的因数，且$<n$，并且这些分数都是真分数，这些分数的和+$\frac{1}{n}=1$。

## 样例 #1

### 输入

```
2
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
6
```

### 输出

```
YES
2
1 2
1 3
```

# 题解

## 作者：TonyYin (赞：3)

[My Blog](https://www.tonyyin.top/2021/10/cf1089f/)

## 题意

给定正整数 $n\leq 10^9$，需要构造出不超过 $10^5$ 个真分数，满足：

- $\frac{a_1}{b_1}+\frac{a_2}{b_2}+\cdots+\frac{a_t}{b_t}+\frac{1}{n}=1$.
- 对每个分数，$b_i<n$ 且 $b_i\mid n$.

若无解，输出 $-1$，否则给出一组可行解。

## 分析

先将 $n$ 质因数分解，分下列情况讨论。

### 一

首先考虑特殊情况。$n = p^m$，其中 $p$ 是质数。

要选一个因数作为分母，发现 $n$ 的任意一个**因数** $b$，都一定是 $p^a$ 的形式。

因为分母为 $1$ 时不合题意，所以在 $1$ 之外，我们任选 $n$ 的两个因子，不妨设为 $c, d$，一定有 $\gcd(c, d)\neq 1$.

又因为 $\gcd(n-1, n)=1$，而 $\gcd(c, d)\neq 1$。以 $c, d$ 作为分母，一定不合法。

也就是说，**当 $n=p^m$ 时，不存在合法解**。

### 二

对于其他情况，$n$ 一定可以被表示为**两个互质的数的乘积**。一种构造方法是：

将 $n$ 质因数分解，不妨 $n=p_1^{m_1}p_2^{m2}\cdots p_t^{m_t}$，令 $x=p_1^{m_1}$，$y=p_2^{m_2}\cdots p_t^{m_t}$，显然 $xy=n$ 且 $\gcd(x, y)=1$.

为了方便，我们钦定 $x\leq y$。如果按照上面的方法得到的 $x>y$，交换 $x, y$ 即可。

当 $k=2$ 时，设题目所求的 $\frac{a_1}{b_1}=\frac{c}{x}$，$\frac{a_2}{b_2}=\frac{d}{y}$.

我们需要求出一组 $(c, d)$ 满足 $\frac{c}{x}+\frac{d}{y}=1-\frac{1}{n}\Rightarrow \frac{c\cdot y+d\cdot x}{xy}=\frac{n-1}{n}$.

因为 $xy=n$，这等价于**满足：**
$$
c\cdot y+d\cdot x=n-1
$$
继续整理，把 $c\cdot y$ 移到右侧，得到：
$$
d=\frac{n-1-cy}{x}
$$
注意 $c, d\in \Bbb{Z}^+$。

**先不考虑 $d$ 的正负性**。由于 $x\mid n$，有：
$$
d\in \Bbb{Z}\Rightarrow x\mid(n-1-c\cdot y)\Rightarrow x\mid (1+c\cdot y)
$$
想要找到满足 $x\mid (1+c\cdot y)$ 的 $c$，考虑**直接枚举**。

注意到 $\gcd(x, y)=1$。当 $c$ 取 $1, 2, \cdots x-1$ 时，都有 $x\nmid (c\cdot y)$，所以 $c\cdot y$ 的取值构成 $\operatorname{mod} x$ 的完全剩余系。

也就是说，当 $c$ 遍历 $1\sim x-1$ 时，$c\cdot y\bmod x$ 的取值两两不同，也**恰好完全覆盖**了 $1\sim x-1$.

因此，一定存在 $c\in[1, x-1]$ 满足 $x\mid (c\cdot y+1)$.

**再看 $d$ 的正负性**。由于 $1+c \cdot y \leq 1+(x-1) \cdot y=1+xy-y=n-(y-1) < n$，所以 $n-(1\cdot y)>0$.

因此，一定有 $d=\frac{n-1-cy}{x}>0$.

## 综上

我们先按照 $x=p_1^{m_1}$，$y=p_2^{m_2}\cdots p_t^{m_t}$ 的方法找到 $(x, y)$.

之后，在范围 $1\sim x-1$ 中枚举 $c$，找到满足 $x\mid(c\cdot y+1)$ 的 $c$，计算出 $d=\frac{n-1-cy}{x}$。

$(\frac{c}{x}, \frac{d}{y})$ 即为满足题意的两个分数。

## 时间复杂度

找到 $(x, y)$ 的部分，需要对 $x$ 分解质因数，时间复杂度为 $\mathcal{O}(\sqrt{n})$.

枚举 $c$ 的部分，因为我们钦定了 $x\leq y$，把 $[1, x-1]$ 看作 $x$ 个数，那么：
$$
x=\sqrt{x\cdot x}\leq \sqrt{x\cdot y}=\sqrt{n}
$$
所以总时间复杂度是 $\mathcal{O}(\sqrt{n})$ 的。

## 代码

```cpp
int n;
vector<int> fac;
int main() {
	scanf("%d", &n);
	int p1 = -1;
	for(int i = 2; i * i <= n; i++) {
		if(n % i == 0) {p1 = i; break;}
	}
	if(p1 == -1) p1 = n;
	int x = p1, y = n / p1;
	while(y % p1 == 0) y /= p1, x *= p1;
	if(y == 1) {
		cout << "NO" << endl;
		return 0;
	}
	int ansc, ansd;
	for(int c = 1; c <= x - 1; c++) {
		if((c * y + 1) % x == 0) {
			ansc = c; ansd = (n - 1 - c * y) / x;
			break;
		}
	}
	cout << "YES\n2\n" << ansc << " " << x << "\n" << ansd << " " << y << endl;
	return 0;
}
```



---

## 作者：Acfboy (赞：2)

数论渣渣做数论题，没有题解就来写一篇。

题目要求的等价于找出若干个 $n$ 的约数（除了 $1$）使得存在给每个配上一个系数让和为 $n-1$。

想想什么情况没有解，若选的约数都不互质那没救了，因为 $n-1$ 肯定和 $n$ 是互质的，而选出来的这些数都是 $n$ 的约数，它们加起来肯定是和 $n$ 有除了 $1$ 以外的因子的，而 $n-1$ 和 $n$ 没有，所以不可能。而若一个数只有单一质因子，那选出来的肯定互质不了。

那么一个质因子不行就想想两个可不可以做到。

就是要求出一个 $ax + by = n-1$, 且满足 $x, y | n$。将 $b$ 移到一边，变成 $b = \frac{n-1-ax}{y}$，那么要求就变成要让这个式子的里的每个数都是正整数是否可行。因为 $y > 0$, 所以 $n-1-ax > 0$； 因为是整数，所以 $y | n-1-ax$。

对于后面一个条件，因为 $y$ 是 $n$ 的约数，所以 $ax+1$ 也得是 $y$ 的约数，又因为 $x$ 和 $y$ 是互质的，所以 $ax$ 在模 $y$ 意义下循环节长度是 $y$，所以当 $a$ 取 $[0, y-1]$ 时  $[0, y-1]$ 恰好都被取到一次，也就是一定会有一个 $ax \equiv y-1 \pmod y$。

再看前一个条件，等价于 $ax < n-1$, 因为 $a$ 在 $[0, y-1]$ 范围内时一定有满足后面条件的，所以一定存在满足条件的同时满足 $ax < (y-1)x < xy - x$, 因为 $xy = n, x > 1$, 所以满足另一个条件的也一定满足 $ax < n-1$。

所以题目里什么 $10^5$ 都是骗人的，只要两个就可以了。

具体地，先暴力找出 $n$ 的所有质因子，然后选俩质因子枚举并判断是否满足条件就好了。

代码。

```cpp
#include <cstdio>
int n, fac[105], m;
int main() {
	scanf("%d", &n);
	int n_ = n;
	for(int i = 2; i*i <= n; i++)	
		if(n_ % i == 0) {
			fac[++m] = i;
			while(n_ % i == 0) n_ /= i;
		}
	if(n_ != 1) fac[++m] = n_;
	if(m <= 1) return puts("NO"), 0;
	
	puts("YES\n2");
	
	int a, b, x = fac[1], y = fac[2];
	for(a = 1; a <= y-1; a++)
		if((a*x+1) % y == 0) { b = (n-1-a*x)/y; break; }
	printf("%d %d\n%d %d", a, n/x, b, n/y);
	return 0;
}
```

---

## 作者：1234567890sjx (赞：1)

首先（并不）容易发现 $k$ 的范围十分的诈骗，其实 $k=2$ 就可以满足全部的范围。

然后容易发现若 $n=p^k$，其中 $p\in\text{prime}$ 则无解，否则一定有解。

然后问题在于构造一组 $k=2$ 的解。考虑先枚举分母再枚举分子。容易发现这样一定会超时。考虑先选取 $n$ 的质因数集合 $S$，则因为 $n$ 不是质数则 $\max S\le \sqrt n$ 即 $\max S$ 不会超过 $10^5$，直接枚举就不会超时了。但是这样又会 WA。怎么回事呢。

通过观察力发现这样选取集合是不优秀的，如 $n=10^9$ 时 $S=\lbrace2,5\rbrace$ 均不存在合法的解。因此考虑在 $S$ 中加入一些 $n$ 的因数。令集合 $P$ 为 $n$ 中非质的因数。显然直接选取集合 $P$ 又回到了一开始会超时的做法，因此只选取 $P$ 中一部分元素并额外加入集合 $S$ 中。考虑选取集合 $P$ 中所有 $\le \text{lim}$ 的元素，在给定范围内能够符合要求即可。经过尝试得出 $\text{lim}\ge 20000$ 即可以保证正确性。所以直接做，注意 $\text{lim}$ 不要选择太大即可。

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给定一个 $n$，确定一些分数，使得这些分数的分母是 $n$，这些分数都是真分数，这些分数的和 $+ \frac{1}{n}=1$。
## 分析
凑几个分数使得和是 $\frac{n-1}{n}$，由于要求分母都是 $b$ 的因数，我们不妨将这些分数都通分，就又变成 $n-1$ 分成一些不和 $n$ 互质的数之和。

举个栗子，输入 $6$，我们就把 $5$ 分成 $2+3$，接下来就可以轻易得到：
$$
\frac{5}{6}=\frac{2+3}{6}=\frac{2}{6}+\frac{3}{6}=\frac{1}{3}+\frac{1}{2}
$$
这里不可以背包不然超时概不负责。

可以发现，所有不和 $n$ 互质的数至少是 $n$ 的一个质因数的倍数。然后我们可以把这些不和 $n$ 互质的大数拆成某个质因数的几倍。

再举个栗子，比如说输入 $100$ 其中一个不和 $100$ 互质的数是 $98$，$100$ 的质因数有 $2,5$，所以我们就可以把它拆成 $49$ 个 $2$。

所以要减少数量。我们会发现，一个大的质数 $t$ 一定可以用两个小的质数 $a,b$ 通过叠加凑出来。

证明在这：因为 $a,b,t$ 都是质数，所以肯定是两两互质的。然后相当于解方程 $ax+by=t$，有解的条件是 $t$ 是 $\gcd(a,b)$ 的倍数。由于 $\gcd(a,b)=1$，所以 $t$ 是 $\gcd(a,b)$ 的倍数，包有解的。

有了这个之后，我们考虑用 $n$ 最小的两个质因数去凑所有的答案。

这一步可以这样：当 $a,b$ 均为质数的时候，我们会用某函数求解 $ax+by=1$，把 $x,y$ 乘以 $t$，但是显然我们这里要求正整数解，所以我们接下来的一个问题就是要把 $x,y$ 配成正整数。如果两个都正了，就直接返回；否则不可能两个都是负的，要不然加起来 $t$ 也是负的了。所以肯定是一个正，一个负。不妨令 $y$ 是正的那个，然后我们会发现，如果 $x,y$ 是一个满足条件的解，那么 $x+b,y-a$ 也是一个满足条件的解，只需要将 $y$ 不停 $-a$，$x$ 不停 $+b$，就可以把它配成正的。

然后这样我们就求出来了一个正整数解。

太过于复杂后你将会发现出题人是 joker，只需输出 $\frac{ax}{n}+\frac{bx}{n}$ 就行。主要是你够聪明就行。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Genshin{//拿不到瑞幸原神联名后的愤怒
    #define int long long
    int n;
    void exgcd(int a,int b,int &x,int &y){
        if (b==0){
            x=1,y=0;return;
        }
        else{
            int x_,y_;
            exgcd(b,a%b,x_,y_);
            x=y_;
            y=x_-a/b*y_;
            return;
        }
    }
    pair<int,int> calc(int a,int b,int k){
        int x,y;
        exgcd(a,b,x,y);
        x*=k;
        y*=k;
        if (x>=0&&y>=0){
            return make_pair(x,y);
        }
        bool flag=0;
        if(x>=0&&y<0){
            swap(x,y);
            swap(a,b);
            flag=1;
    	}
        int cnt=y/a;
        y=y-cnt*a;
        x=x+cnt*b;
        return flag?make_pair(y,x):make_pair(x,y);
    }
    int d[100],p[100];
    void Decompose(int x){
        int cnt=0;
        for(int i=2;i*i<=x;++i){
            if (x%i==0){
                ++cnt;
                d[cnt]=i;p[cnt]=0;
                while(x%i==0){
                    ++p[cnt];
                    x/=i;
                }
            }
        }
        if (x!=1){
            ++cnt;
            d[cnt]=x,p[cnt]=1;
        }
        return;
    }
    void putfrac(int a,int b){
        int g=__gcd(a,b);
        printf("%I64d %I64d\n",a/g,b/g);
    }
    void Solve(){
        Decompose(n);
        if (d[2]==0 and p[2]==0){
            puts("NO");
			return;
        }
        int a=d[1],b=d[2];
        pair<int,int>tmp=calc(a,b,n-1);
        int x=tmp.first,y=tmp.second;
        puts("YES\n2");
        putfrac(a*x,n);
        putfrac(b*y,n);
    }
    void Main(){
        if(0){
            freopen("","r",stdin);
            freopen("","w",stdout);
        }
        scanf("%I64d",&n);
        Solve();
    }
    #undef int 
};
main(){
    Genshin::Main();
    return 0;
}
```

---

## 作者：loser_seele (赞：0)

来一个人看得懂的版本，理论时间复杂度更优秀，喜提最优解。

首先 $ n=p^m $ 的情况肯定是无解的，因为通分之后分子之和总能被 $ p $ 整除，而 $ \gcd(n-1,n)=1 $，所以无解。

接下来证明两个分数一定能构造出解。

Pollard-rho 分解质因数之后随便拉出来一个质因子 $ x $，将 $ n $ 中所有 $ x $ 除尽得到 $ y $，将 $ x $ 设为满足 $ x^m \mid n $ 的最大的 $ x^m $，则通分后有 $ cx+dy=n-1,\gcd(x,y)=1 $，不难发现这显然有解。

化简之后得到 $ d=\frac{(n-1-cy)}{x} $，因为 $ d $ 为整数且 $ x $ 是 $ n $ 的因子，则不难有 $ x \mid (cy+1) $，等价于 $ cy \equiv x-1 \pmod {x} $，直接求逆元即可。

但是这里出现了一个问题：$ x^m $ 不是质数，直接套费马小定理不行。观察到 $ \gcd(y,x^m)=1 $，则由扩展欧拉定理解得 $ c=y^{\varphi(x^m)-1} \times (x-1) \bmod x $，其中 $ \varphi(x^m) $ 显然可以直接算。这样就避免了其他题解里写的暴力跳过程。

于是整个算法的瓶颈在分解质因数的 Pollard-rho，总时间复杂度 $ \mathcal{O}(n^\frac{1}{4}) $，可以通过。

[提交记录](https://codeforces.com/contest/1089/submission/193407293)

---

