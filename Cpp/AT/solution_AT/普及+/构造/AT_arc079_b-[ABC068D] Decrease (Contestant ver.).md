# [ABC068D] Decrease (Contestant ver.)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc068/tasks/arc079_b

長さ $ N $ の非負整数列 $ a_i $ に対し、数列の最大値が $ N-1 $ 以下になるまで以下の操作を繰り返し行うことを考えます。

- 数列のうち最も大きい要素を求める、複数ある場合はどれか $ 1 $ つ選ぶ。この要素の値を $ N $ 減らす。これ以外の要素の値を $ 1 $ 増やす。

なお、この操作を行い続けると、いつかは数列の最大値が $ N-1 $ 以下になることが証明できます。

ここで、整数 $ K $ が与えられるので、この操作を行う回数がちょうど $ K $ 回になるような数列 $ a_i $ を $ 1 $ つ求めてください。なお、この問題の入出力の制約下では、かならず $ 1 $ つは条件を満たすような数列が存在することが示せます。

## 说明/提示

### 制約

- $ 0\ ≦\ K\ ≦\ 50\ \times\ 10^{16} $

### Sample Explanation 3

\\\[2, 2\\\] -&gt; \\\[0, 3\\\] -&gt; \\\[1, 1\\\] と、$ 2 $ 回操作を行います。

## 样例 #1

### 输入

```
0```

### 输出

```
4
3 3 3 3```

## 样例 #2

### 输入

```
1```

### 输出

```
3
1 0 3```

## 样例 #3

### 输入

```
2```

### 输出

```
2
2 2```

## 样例 #4

### 输入

```
3```

### 输出

```
7
27 0 0 0 0 0 0```

## 样例 #5

### 输入

```
1234567894848```

### 输出

```
10
1000 193 256 777 0 1 1192 1234567891011 48 425```

# 题解

## 作者：STARSczy (赞：3)

# 思路：
设答案的序列为 $a$，长度为 $n$。因为这个答案序列 $a$ 不要求顺序，怎么排顺序都行；为方便讲解，设序列是一个从大到小的有序序列。

因为每次 $a_1$ 是这个序列里最大的数，因此它要减去 $n$，然后为了维持 $a$ 的有序性，因此它要在序列 $a$ 里面插入，但是与其在里面无法预测地插入，不如插入到最后，因此，我们需要构造一个不断循环的序列。

为方便描述，举出几个例子：

当输入 `0` 时，输出为：
```
50
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49
```

可以看到，输出结果就是从 $0 \sim 49$，这里仅作铺垫。


当输入 `2` 时，输出仅需改成为：
```
50
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 49 50
```

即“$1 \sim 47\ 49\ 50$”。下面是验证。

操作一次的结果为：
```
50
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 50
```
操作两次的结果为：
```
50
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49
```
这个过程实际上是一个循环。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n;

signed main(){
	cin>>n;
	cout<<50<<endl;
	for(int i=0;i<50;i++) cout<<i+(n+i)/50<<" ";
	cout<<endl;
	return 0;
}
```

---

## 作者：123asdf123 (赞：2)

[在我的博客查看](https://www.cnblogs.com/i-akioi/p/18715564)

一道绿题写了一个半小时……

[**题目**](https://www.luogu.com.cn/problem/AT_arc079_b)

看到这道题，直接一看，$N=1$、$a_1=x$ 就完事了？交了发现题面写了 $2 \le N$……

不难发现，无论 $N$ 是多少，每次 $N-1$ 个数 $+1$，一个数 $-N$，总和每次 $-1$。那么总和至少为 $K$ 才行。

直接想 $N=2$ 的，因为总和至少为 $2$ 才能操作，假设 $a_1=K+1$。然后有可能 $\begin{cases}a_1=1\\a_2=1\end{cases}$，此时总和 $\ge 2$ 但仍然不能操作，于是这种情况 $a_2=1$ 即可。交上去发现又 WA 了。一看题面：$K \le 50 \times 10^{16}$，但 $a_i \le 10^{16}+1000$。

首先先写个代码，来看给定 $N,a$ 时的 $K$ 值（即这场比赛下一道题的暴力）：
```
#include<bits/stdc++.h>
using namespace std;
namespace estidi{
	int a[53];
	int main(){
		int n,x=0,cnt,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		while(1){
			cnt=0;
			for(int i=1;i<=n;i++)
				if(a[cnt]<a[i])
					cnt=i;
			if(a[cnt]<n)
				break;
			ans++;
			a[cnt]-=n+1;
			for(int i=1;i<=n;i++)
				a[i]++;
		}
		cout<<ans<<endl;
		for(int i=1;i<=n;i++)
			cout<<a[i]<<" ";
		return 0;
	}
}
int main(){
	estidi::main();
	return 0;
}
```

因为 $N \le 50$，而 $K$ 又专门把 $50$ 提出来，没写 $5\times 10^{17}$，自然想到最终答案 $N=50$、$a_i \le \frac{K}{50}+1000$。

先考虑 $N=2$ 时怎么使 $a_i$ 在 $\frac{K}{2}$ 附近。乱找规律发现当 $a_1=a_2=x+1$ 时，答案为 $2x$。再总结发现 $a_1=a_2=\dots=a_N=x+N-1$ 时，答案为 $x\times N$！

但这样还只能得出 $50\mid x$ 时的结论，继续观察，再次假设 $N=2$，发现当 $\begin{cases}a_1=x\\a_2=x+2\end{cases}$ 时，答案为 $2x+1$。但这个结论不好推至 $N=50$ 时的情况，于是考虑 $N=3$ 时的来找规律。发现 $\begin{cases}a_1=x+1\\a_2=x+1\\a_3=x+4\\K=3x+1\end{cases}$、$\begin{cases}a_1=x\\a_2=x+4\\a_3=x+4\\K=3x+2\end{cases}$。

后面当时是怎么乱想的我忘了，反正式子推错又 WA 了好几次。现在我发现：$\begin{cases}a_1=x+N+1\\a_2=x+N+1\\\dots\\a_y=x+N\\a_{y+1}=x+N-1-y\\\dots\\a_N=x+N-1-y\\K=Nx+y\end{cases}$。$N$ 取 50 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace estidi{
	int main(){
		long long k,kk;
		scanf("%lld",&k);
		kk=k%50;
		k/=50;
		printf("50\n");
		for(int i=1;i<=kk;i++)
			printf("%lld ",k+51);
		for(int i=kk+1;i<=50;i++)
			printf("%lld ",k+49-kk);
		return 0;
	}
}
int main(){
	estidi::main();
	return 0;
}
```

---

## 作者：Krimson (赞：2)

这次NOIP之后感觉构造题还是有必要去写的  


------------
发现有这样一个限制:$k<50*1e16$,$a<1e16+1000$  
可见不能去通过直接构造一个长度为$2$的序列水过去,而且在数据比较大的时候必须要卡满$N=50$  
那么干脆就直接用$N=50$的情况来构造出所有的情况来  
(如果对于不同级别的数据分类讨论,会很麻烦)  

首先不难得到,当$K<50$的时候,构造一个这样的数列${50,49...(50-K+1),0,0,0,0,0...}$  
是可以达成要求的  
而且当这个数列的每一位都被填上的时候,满足$50$次操作之后所有元素的值都减$1$  
例如$51,50...2$,在操作$50$之后就变成了$50,49...1$  
并且对于这样的数列,对前$x$个元素每个加$1$之后,就可以多操作$x$次  
设$t=\lfloor\frac{k}{50}\rfloor-1$,$x=k\ mod\ 50$  
那么只要构造一个数列  
$50+t+1,49+t+1...(50-x+1)+t+1,(50-x)+t...2+t,1+t$  
就可以满足操作$K$次了    

以下是代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
ll k,a[55];
int main(){
    k=read();
    puts("50");
    for(ri i=1;i<=50;++i){
        a[i]=50-i+1;
    }
    if(k<=50){
        for(ri i=1;i<=k;++i){
            write(a[i]),putchar(' ');
        }
        for(ri i=k+1;i<=50;++i){
            write(0),putchar(' ');
        }
    }
    else{
        k-=50;
        for(ri i=1;i<=50;++i){
            a[i]+=k/50;
        }
        k%=50;
        for(ri i=1;i<=k;++i){
            a[i]++;
        }
        for(ri i=1;i<=50;++i){
            write(a[i]),putchar(' ');
        }
    }
    return 0;
}
```



---

## 作者：Ryo_Yamada (赞：1)

挺妙的

考虑反着做。先随意构造一个初始序列 $a$ 使 $\forall a_i < n$，随后进行 $k$ 次操作。每次操作选一个 $i$ 并使 $a_i = a_i + n$，并将其它数 $-1$。需要满足：

- 操作后 $i$ 的整个序列的最大值；
- $\forall a_i \ge 0$。

如下简称以上操作为 反操作。

若 $k$ 次反操作均符合限制条件，则最后的序列 $a$ 需要的操作次数一定 $=k$。

---------

我们发现对于一个长度为 $n$ 且形似 $\{x, x+1, \ldots , x+n-1 \}$ 的序列，对 $i$ 从 $1$ 到 $n$ 顺序做 $n$ 次操作后等价于序列整体 $+1$。

所以可以令初始序列 $a = \{ 0, 1, \ldots , n-1 \}$。

随后做 $\lfloor \dfrac{k}{n} \rfloor$ 次序列全体 $+1$，然后剩余操作次数为 $k = k \bmod n$。

然后对于 $i$ 从 $1$ 到 $k$ 顺序做 $k$ 次操作即可。显然满足反操作的限制条件。

---------

题目限制 $k \le 50 \times 10^{16}$，$0 \le a_i \le 10^{16} + 1000$，从而可能会卡满 $n=50$。对于一个 $k$，$n$ 的下限是 $\max(2, \, \lceil \dfrac{k}{10^{16}} \rceil)$。所以我们构造这个 $n$ 的答案即可。当然也可以直接构造 $n=50$ 的答案。

```cpp
int n;
ll a[55];

int main() {
	ll k; qread(k);
	n = max(2, (int)ceil(1.0 * k / 1e16));
	rep(i, 1, n) a[i] = i - 1;
	rep(i, 1, n) a[i] += k / n;
	k %= n;
	rep(i, 1, k) {
		a[i] += n;
		rep(j, 1, n) if(j != i) --a[j];
	}
	cout << n << endl;
	rep(i, 1, n) cout << a[i] << ' ';
	return 0;
}
```

---

## 作者：ty_mxzhn (赞：0)

NOIP2024 要到了，写篇简单构造题的题解。

首先，操作一次以后序列的和会减小 $1$，而我们要构造 $k\le 50\times 10^{16}$，则我们的构造一定要满足 $n=50$。

构造题一般都要加强限制。对于这题，我们加强如下限制：每次减少完最大值以后，这个数一定是原数列的最小值。

先考虑 $k=1$。我们构造 $0,1,\dots,n-2,n$。此时操作一次正好是 $0,1,\dots,n-1,n$。

再考虑 $k=2$，我们构造 $0,1,\dots,n-3,n-1,n$。此时操作一次正好变成了刚才提到的数列。

考虑 $k=50$，我们构造 $1,2,\dots,n-1,n$。此时操作 $50$ 次正好复原。

考虑 $k=51$，我们构造 $1,2,\dots,n-1,n+1$。同理可得正解数据范围下的构造。

---

## 作者：Yesod (赞：0)

# 思路

看到这题的数据范围 $1\leq k\leq 10^{16}$ 我们在数据大的时候可能构造 $ k \leq 49$ 的数列会爆，所以我们可以从当 $ k $ 等于 $ 50 $ 的时候构造。我们发现每次进行操作会使总大小减 $ 1 $ 所以每个循环节为 $ 50 $ 时，整个序列可以从 $ 1,2,3,4,5......50 $ 变为 $ 0,1,2,3,4......49 $ 那么我们可以单独枚举 $ k\bmod50 $ 的次数最后输出答案。 

# code
```
#include <bits/stdc++.h>
using namespace std;
long long n,r,a[55];
int main(){
	cin>>n,r=n%50;
	cout<<50<<endl;
	for(long long i=1;i<=50;i++)//构造整数部分
		a[i]=n/50+i-1;
	for(long long i=1;i<=r;i++)//构造余数部分
		cout<<a[i]+50-r+1<<" ";
	for(long long i=r+1;i<50;i++)
		cout<<a[i]-r<<" ";
	cout<<a[50]-r;
return 0;
}



---

