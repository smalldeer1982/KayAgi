# [ARC165A] Sum equals LCM

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc165/tasks/arc165_a

正整数 $ N $ が与えられます。

$ 2 $ 個以上の (相異なるとは限らない) 正整数 $ A_1,A_2,\dots,A_n\ (2\ \leq\ n) $ であって、以下の条件をすべて満たすものが存在するか判定してください。

- $ A_1+A_2+\dots+A_n=N $
- $ A_1,A_2,\dots,A_n $ の最小公倍数は $ N $
 
$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 100 $
- $ 2\ \leq\ N\ \leq\ 10^{9} $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ 1 $ つ目のテストケースについて、例えば $ 3 $ 個の正整数 $ (A_1,A_2,A_3)=(1,2,3) $ は、 $ A_1+A_2+A_3=1+2+3=6 $ であり、 $ A_1,A_2,A_3 $ の最小公倍数は $ 6 $ であるため条件を満たしています。 $ 2 $ つ目のテストケースについて、条件を満たすような $ 2 $ 個以上の正整数は存在しません。

## 样例 #1

### 输入

```
4
6
4
998244353
367291763```

### 输出

```
Yes
No
No
Yes```

# 题解

## 作者：reclusive (赞：7)

[my blog](https://www.cnblogs.com/reclusive2007/p/17713640.html)

前天的晚上打这道题，和同学一起想出了思路，开心。

------------

## 题意描述

给你一个数 $N$，问你存不存在一个数列 $A_1,A_2, \ldots,A_n(2 \le n)$，使得 $\sum_{i=1}^n A_i=N$ 并且 $\operatorname{lcm}(A_1,A_2,\ldots,A_n)=N$。

## 具体思路

首先显然，一个质数 $N$ 的因数只有 $1$ 和 $N$。

若选 $N$，那么个数不符合要求，

若选 $1$ 和 $N$，那么和比 $N$ 大，不符合要求。

因此质数肯定是不符合要求的。

考虑不是质数的情况。

我们从样例出发，$6=2 \times 3$，因此我们令 $A_1=2,A_2=3$。

但是我们发现和并不符合要求，而同时发现给数列中添加 $1$ 并不会影响最后的最小公倍数。

因此我们令 $A_3=1$ 即可。

想到这里你好像懂了什么，继续往下看。

样例中还有一个 $4$，它是不符合要求的，为什么？

由于我们可以通过补 $1$ 的方式来保证和为 $N$，因此可以不用考虑和。

我们对 $4$ 进行质因数分解，发现它只有 $2$ 这一个质因子。

说明我们如果把它和 $6$ 一样分成两个数相乘，由于它只有 $2$ 这一个质因子，那么这两个数一定同时可以被 $2$ 整除。

设这两个数分别为 $a,b$，其中 $a \times b=4$。

那么 $\operatorname{lcm}(a,b)=\frac{a \times b}{\gcd(a,b)}=\frac{a \times b}{2}=\frac{4}{2}=2$。

我们发现最后答案不是 $4$。

一般的 $N=p^c$，有 $\operatorname{lcm}(a,b)=\frac{a \times b}{\gcd(a,b)}=\frac{a \times b}{p}=\frac{N}{p}$。

于是我们得出**结论**：

- 若 $N$ 为质数，没有符合条件的数列。

- 若 $N$ 不为质数且只有一个质因子，没有符合条件的数列。

- 若 $N$ 不为质数且质因子个数 $>1$，有符合条件的数列。

## Code

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		int cnt=0;
		for(int i=2;i*i<=n;i++){
			if(n%i==0){
				cnt++;
				while(n%i==0)n/=i;
			}
		}
		if(n>1)cnt++;
		if(cnt>1)puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：Dws_t7760 (赞：3)

如果对一个 $N$ 构造一个满足条件的数列，我们可以给出首先给出两个大于 $1$ 的整数 $a$，$b$，使 $a \times b = N$，且两者互质，其余部分用 $1$ 填充。判断这样的 $a$ 和 $b$ 是否存在，我们可以判断 $N$ 是否有至少 $2$ 个不同的质因数，如果达到，那么必然存在这样的 $a$ 和 $b$，否则不存在。

AC 代码：

```
#include<iostream>
using namespace std;
long long t,n,s;
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int i=0;i<t;i++) {
		cin>>n,s=0;
		for(long long j=2;j*j<=n&&s<=2;j++) {
			if(n%j==0) {
				s++;
				while(n%j==0) n/=j;
			} 
		}
		if(n!=1) s++;
		cout<<(s>=2?"Yes\n":"No\n");
	}
	return 0;
}
```

---

## 作者：__Star_Sky (赞：2)

## Description

给出 $T$ 组询问，每次询问给出一个正整数 $n$，是否存在一个长度大于等于 $2$ 的正整数数列 $x_1,x_2,x_3 \dots x_k$，使得该数列满足满足以下条件：

1. $x_1+x_2+\dots+x_k=n$

2. $\operatorname{lcm}(x_1,x_2,x_3,\dots x_n)=n$

3. 数列中的元素可以重复，也可以不重复

如果存在，输出 Yes，否则输出 No。

其中 $T\le100,n\le10^9$。

## Solution

对于第一个条件，显然往数列后面补 $1$ 即可使数列满足该条件。难点在于第二个条件。

我们知道，如果两个整数 $x,y$ 满足 $\gcd(x,y)=1$，也就是这两个整数互质，那么一定满足 $\operatorname{lcm}(x,y)=x\times y$。于是对于整数 $n$，如果存在两个互质的因数 $d_1$，$d_2$ 使 $d_1\times d_2=n$，将它们写入数列中，此时数列就满足第二个条件了。由于将 $1$ 写入数列不影响整个数列的最小公倍数，因此只需要向数列后面补 $1$ 直到数列的和等于 $n$ 即可使数列同时满足两个条件。于是问题转化为判断 $n$ 是否存在两个互质的因数 $d_1$，$d_2$ 使 $d_1\times d_2=n$。

由唯一分解定理，我们知道 $n$ 可以被唯一分解成 $p_1^{a_1}p_2^{a_2}p_3^{a_3}\dots$ 的形式，其中 $p$ 表示 $n$ 的质因子。当 $n$ 的质因子数量为 1 时，对于这个质因子 $p$，$\frac{n}{p}$显然一定是它的倍数，两个数的最小公倍数是 $\frac{n}{p}$，显然不满足第二个条件。但是当 $n$ 有两个或以上质因数时，就能满足条件了。设 $p_1$，$p_2$ 是 $n$ 的两个质因数，由于 $p_1$，$p_2$ 互质，$p_1^{a_1}$ 和 $p_2^{a_2}$ 显然也互质。它们就是两个互质的因数。如果还存在其它质因子 $p_3,p_4\dots$ 也没关系，将它们乘到 $p_2$ 上即可。由于质因数两两之间不存在公因数，所以 $p_1^{a_1}$ 和 $p_2^{a_2}p_3^{a_3}p_4^{a_4}\dots$ 也是互质的，它们就是 $n$ 的两个互质的因数，并且相乘等于 $n$。

于是，只要 $n$ 存在两个或以上质因子即可满足条件。将 $n$ 分解质因数，如果质因数数量大于等于 2 则输出 Yes，否则输出 No。

## Code
```
#include<bits/stdc++.h>
using namespace std;
bool div(int n)
{
	int res=0;
	for(int i=2;i<=n/i;i++)
	{
		if(n%i==0) res++;
		if(res>1) return 1;
		while(n%i==0) n/=i;
	}
	if(n>1) res++;
	if(res>1) return 1;
	return 0;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		if(div(n)) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：hjqhs (赞：1)

容易想到，可以用两个互质的 $N$ 的因数使得 lcm 为 $N$。由于对序列长度没有限制，所以剩下的都用 $1$ 来填充使得和达到 $N$。所以问题就转化成了判断 $N$ 有没有两个互质的因数。  
[code](https://atcoder.jp/contests/arc165/submissions/45671544)。

---

## 作者：_sunkuangzheng_ (赞：1)

纪念第一场 ARC 捏。

**【题目分析】**

结论：当 $n$ 有大于等于 $2$ 个不同的质因子时有解。

设 $n = \prod\limits_{i=1}^kp_i^{c_i}$，我们首先选数字 $p_1^{c_1},p_2^{c_2},\ldots,p_k^{c_k}$，这些数字两两互质，显然它们的 $\operatorname{lcm}$ 肯定等于 $n$。因为这些数字是大于等于 $2$ 的质数，所以一定有 $\sum\limits_{i=1}^kp_i^{c_i} \le \prod\limits_{i=1}^kp_i^{c_i}$。剩余的和不够的部分，因为数组长度不限，我们可以直接全填 $1$。

为什么一个数字只有一个质因子时无解？设 $n = p^c$，若想选出**两个以上**的数字使得其 $\operatorname{lcm} = n$，则一个数字必然是 $n$。又因为另一个数字肯定不小于 $1$，所以和大于 $n$，无解。

**【代码】**

[submission](https://atcoder.jp/contests/arc165/submissions/45670220)。

---

## 作者：Larry76 (赞：1)

由于是省流版，所以这里没有前言。

## 题目分析

首先肯定的是质数无解。

然后考虑当 $a, b \gt 1$ 的时候，有不等式 $a + b \le ab$。

这样就简单了，我们考虑对数 $n$ 进行唯一分解，则有 $\prod p_i^{k_i} = n \ge \sum p_i^{k_i}$。考虑不够 $n$ 的部分用 $1$ 来补齐，且 $1$ 的加入不影响 $\operatorname{lcm}$，然后可以得出结论：

> 若 $n$ 是由若干个质数的幂的乘积构成的，则一定有解。
>
> 否则一定无解。

然后做完了本题。

## 代码实现

```cpp
void solve(){
	int n = read();
	int cnt = 0;
	int buf = n;
	for(int i = 2; i * i <= n; i++) {
		if(buf % i == 0) {
			++cnt;
		}
		while(buf % i == 0) {
			buf /= i;
		}
	}
	if(buf != 1) {
		++cnt;
	}
	if(cnt >= 2) {
		puts("Yes");
	} else {
		puts("No");
	}
}

void main() {
	int T = read();
	while(T--) {
		solve();
	}
	return void();
}
```

---

## 作者：wanghaoran00 (赞：1)

### 思路
判断是否存在不同的质数因子，证明如下，$a+b\leq ab$ 得到 $\frac{1}{a}+\frac{1}{b}\leq 1$，此时 $a,b$ 为正整数，易知 $a,b\ne 1$，其他情况均满足，构成的序列中即 $a,b$ 两个因子，序列其他数均为 $1$。因此当质数因子的数量大于 $1$ 时成立。

AC code
```
#include<bits/stdc++.h>
using namespace std;
int t,ans,s,b1,b2;
int main(){
    cin>>t;
    while(t--){
        ans=0,b1=0,b2=0;
        scanf("%d",&s);
        for(int i=2;i<=sqrt(s)+1;i++){
            if(s%i==0){
                if(b1==0){
                    b1++;
                    b2=i;
                }
                else if(i%b2!=0||s/i!=i){
                    printf("Yes\n");
                    b1=2;
                    break;
                }
                while(s%i==0){
                    s=s/i;
                }
                if(s!=i&&s!=1){
                    printf("Yes\n");
                    b1=2;
                    break;
                }
            }
        } 
        if(b1<=1){
            printf("No\n");
        }
    }
    return 0;
}
```

---

## 作者：_Robin_ (赞：0)

### 题目描述

给定一个 $N$，现在要求你构造一个长度至少为 $2$ 的序列，且要满足，所有元素的和以及所有元素的最小公倍数为 $N$。

### 正片即将开始

考虑一下几点：

- 首先，$N$ 一定不能是素数，因为至少出现一个 $N$ 的情况下，一定有 $N+x>N$（$x$ 为其他所有数的和）。

- 其次，序列里的数**必须且仅能**把 $N$ 的所有质因子出现至少 $1$ 次；  
  剩下的空可以交给 $+\infty$ 个 $1$ 去选填;

- 最后，通过观察样例 $1$ 中的 $N=4$，发现，如果一个数可以表示为 $p^x$，那么它等价与一个"**素数**"，至少出现一个 $N$ 才行；  


代码非常简短
```cpp

namespace R{

    template <typename Love>
    inline void read(Love &x){
        x=0;bool f(true);char c=getchar();
        for(;!isdigit(c);c=getchar()) if(c=='-') f=false;
        for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^48);
        return x*=f?1:-1,void();
    }

    template <typename Love>
    void write(Love x){
        if(x<0) putchar('-'),x=-x;
        if(x>9) write(x/10);
        putchar('0'+x%10);
    }

}

using namespace R;

namespace Play{

    int stck[1600],top;

    void getprime(int x){
        top=0;
        int t=sqrt(x);
        for(int i(2);i<=t;i++){
            if(x%i==0){
                stck[++top]=i;
                while(x%i==0) x/=i;
            }
        }
        if(x!=1) stck[++top]=x;
        if(top<=1) return puts("No"),void();
        else puts("Yes"),void();
    }

}

int main(){
    int x,T;
    R::read(T);
    while(T--){
        R::read(x);
        Play::getprime(x);
    }
}
```

---

## 作者：Epoch_L (赞：0)

## Solution

若 $x$ 为质数的若干次幂，显然无解。

否则一定能分解 $x=ab$，其中 $\gcd(a,b)=1,a\ge 2,b\ge 2$。

则令答案数组 $A_1=a,A_2=b$，此时已经满足了最小公倍数的限制，并且我们发现 $a+b \le ab=x$，并没有满足和的条件，我们只需要在后面添加适量的 $1$ 即可，因为 $1$ 不影响最小公倍数。

所以最终的结论为：若 $x$ 能分解为两个或以上质数的若干次幂的乘积，则有解。

---

