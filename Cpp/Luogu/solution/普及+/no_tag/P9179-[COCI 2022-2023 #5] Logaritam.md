# [COCI 2022/2023 #5] Logaritam

## 题目描述

定义对数序列为一个长为 $n$ 的对数序列 $(a_1,a_2,\ldots,a_n)$，满足对于所有正整数 $x,y$ 且 $xy\le n$，有 $a_{xy}=a_x+a_y$。一个长为 $6$ 的对数序列例子为 $0,1,\pi,2,0.7,1+\pi$。

有 $q$ 个长度为 $n$ 的对数序列，但是现在每个序列都恰好有一个元素被改掉了。给你序列个数 $q$，序列长度 $n$ 和每个序列被改动的元素位置 $x_i$，对于每个序列，输出在不改动已经更改的元素的情况下，至少要修改序列中多少个位置的元素才能使这个序列仍然是对数序列。

注：可以证明对于任意的初始对数序列，改动同一位置后，在不改动这个位置的情况下将序列变为对数序列的最小改动数都是相等的。

## 说明/提示

样例 $1$ 解释：

假设初始序列是 $0,1,\pi,2,0.7,1+\pi$，修改第四个元素为 8，那就可以把第二个元素改为 $4$，把第六个元素改为 $4+\pi$，这样序列变成 $0,4,\pi,8,0.7,4+\pi$，又变成了对数序列。

|子任务编号|	附加限制|	分值|
|:-:|:-:|:-:|
|$0$|	是样例	|$0$|
|$1$|	$n\le 20,q\le 20$	|$17$|
|$2$|	$q\le 8$	|$24$|
|$3$|	$n\le 10^4$	|$26$|
|$4$|	无附加限制	|$33$|

## 样例 #1

### 输入

```
6 6
1
2
3
4
5
6
```

### 输出

```
-1
2
1
2
0
1
```

## 样例 #2

### 输入

```
20 5
7
8
2
19
12
```

### 输出

```
1
9
9
0
5
```

## 样例 #3

### 输入

```
10000 4
1234
2345
3456
7890
```

### 输出

```
15
148
3332
37
```

# 题解

## 作者：lottle1212 (赞：5)

# [[COCI2022-2023#5] Logaritam](https://www.luogu.com.cn/problem/P9179) 题解

## 题目大意

定义长度为 $n(1 \leq n \leq 10 ^ 8)$ 的对数序列 $a$，对于 $1 \leq i,j,i \times j \leq n$，有 $a_{i \times j} = a_i + a_j$。

给定 $q$ 个询问，给出位置 $x$。求修改 $x$ 后使序列仍是对数序列最少操作次数，操作中不能再修改 $x(1 \leq x \leq n)$。若无方案，输出 $-1$。

## 解题思路

首先，我们可以试着构造一个对数序列。因为 $x = x \times 1$，所以 $a_x = a_x + 1$，因此 $a_1 = 0$。在此基础上，最简单构造的当然是 $a = \{0, 0, \dots, 0\}$。为了让它有更好的性质，对于一个位置 $x$，如果其不随着比它小的数（除 $1$ 外）变化而变化，那么设其为 $1$。容易发现，为 $1$ 的数为质数。
则 $a$ 形如 $\{0, 1, 1, 2, 1, 2, 1, 3, 2, 2, \dots \}$。

观察上面的数列，为了使 $x$ 变化，$x$ 的其中一个因数也要改变。设 $y$ 是 $x$ 的因数，若 $y$ 变化使 $x$ 变化，那么为了使 $y$ 变化，同样要使 $y$ 的因数变化。这么递归下来，最终的 $y$ 一定是个质数，因为质数不受比它小的数牵连。既然改变了这个质数，其倍数也会一同修改。然后问题就转换成了 $1 \sim n$ 中，有多少个数是这个质因数的倍数。根据贪心思想，这个质数就是 $x$ 的最大质因数。

最后考虑什么情况无解。对于一个数，因为只需改变其最大质因数即其倍数，所以都有解，而对于 $1$ 有特殊约束 $a_1 = 0$，即当 $x = 1$ 时无解，输出 $-1$。

一共有 $q$ 次询问，每一次都要对 $x$ 分解质因数，因此时间复杂度为 $O(q \sqrt{n})$。

## 代码实现

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int rd() {
	int res = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
	while (ch >= '0' && ch <= '9') res = (res << 1) + (res << 3) + (ch ^ 48), ch = getchar();
	return f ? -res : res;
}
signed main() {
	int n = rd(), q = rd();
	while (q --) {
		int x = rd(), y = 0;
		if (x == 1) { puts("-1"); continue; } //判断x = 1的情况。
		for (int i = 2; i <= sqrt(x); ++ i)
			if (x % i == 0) {
				y = i;
				while (x % i == 0) x /= i;
			}
		if (x > 1) y = x; //找到最大质因数
		printf("%lld\n", n / y - 1); //其倍数个数，其中x不算
	}
	return 0;
}
```

---

## 作者：LZC_AK_CRZ (赞：4)

# Solution

一、思考过程

$a)$ 无解情况：  
$\because a_i=a_{1*i}=a_1+a_i$  
$\therefore a_1=0$  
即当修改下标 $x=1$ 时，无解（输出 $-1$）。

$b)$ 有解情况：  
修改下标为 $x$ 的元素时，以 $x$ 的因数为下标的元素中必然会有至少一个被修改。设其中一个的下标为 $x_1$，同理则以 $x_1$ 的因数为下标的元素中必然会有至少一个被修改。显然这是一个递归过程，而终止条件则是得到的某一个因数 $x_k$ 为质数。那么贪心策略告诉我们，当 $x_1$ 为质数，即 $x_1$ 为 $x$ 的质因数时，需要的修改次数是最少的。  
但是，当以 $x_1$ 为下标的元素被修改时，以 $x_1$ 的倍数为下标的元素也必然会被修改。所以总的修改个数为 $n/x_1-1$。又因为 $x_1$ 越大，修改个数越小，所以我们得到 $x_1$ 为 $x$ 的最大质因数。

二、复杂度分析

时间复杂度最大开销是寻找最大质因数的过程，我们可以用质因数分解解决，时间复杂度 $O(\sqrt n)$。又因为有 $q$ 次询问，所以总的时间复杂度 $O(q\sqrt n)$。瞄一眼数据范围，$1 \le q \le 10^4$, $1 \le n \le 10^8$,  $q\sqrt n$ 最大 $10^8$，可以通过。  
空间复杂度 $O(1)$。

三、代码


```cpp
#include <iostream>
#define int long long //心里踏实
using namespace std;
int n, q, x;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    while (q--) {
        cin >> x;
        if (x == 1) {
            cout << -1 << '\n';
            continue;
        }
        int maxt = 0;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) maxt = i;
            while (x % i == 0) x /= i;
        }
        if (x != 1) maxt = x;
        cout << (n - maxt) / maxt << '\n';
    }
    return 0;
}
```

---

## 作者：DYYqwq (赞：3)

模拟赛签到题，但是我是最后一个切出来的。

这种题一看就是结论题或者找规律题，于是尝试构造出一个对数序列。对于 $i=1$，容易发现 $a_{i \times j}=a_i+a_j \Rightarrow a_j=a_i+a_j \Rightarrow a_i=a_1=0$。进而发现如果一个数 $i$ 是质数，那么 $a_{1 \times i}=a_1+a_i$，于是得到 $0=0$，这意味着 $a_i$ 的值自然是任意的。不妨设其为 $1$。于是其他值便被唯一确定。最终构造出来的对数序列如下：$\{0,1,1,2,1,2,1,3,2,2,1,3,\cdots \}$。

之所以我列到第 $12$ 个数，是因为 $12=3 \times 4=2 \times 6$，考虑如果它被修改了，如何使产生的影响最小？考虑到改变较大的数自然更优，但是 $6=2 \times 3,4 = 2 \times 2$，本质上还是在 $2,3$ 中选。于是考虑把 $12$ 质因数分解，$12=2^2 \times 3^1$，于是选择修改 $3$。多手玩几组数据，就可以发现每次都应选择这个数的最大质因子修改。不妨设这个最大质因子为 $k$，则答案就是 $\left \lfloor \frac{n}{k} \right \rfloor -1$。$-1$ 的原因是自己无需修改。

总时间复杂度为 $O(q \sqrt n)$。

然后这道题就做完了。没有什么细节。代码见下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , q;
int get_max_prime(int x)
{
	int ans = 1;
	for(int i = 2 ; i <= sqrt(x) ; i ++)
	{
		if(x % i == 0)
		{
			ans = max(ans , i);
			while(x % i == 0) x /= i;
		}
	}
	return max(ans , x);
}
int main()
{
// 	freopen("ds.in" , "r" , stdin);
// 	freopen("ds.out" , "w" , stdout);
	scanf("%d%d" , &n , &q);
	while(q --)
	{
		int x;
		scanf("%d" , &x);
		printf("%d\n" , (x == 1) ? -1 : (n / get_max_prime(x) - 1));
	}
	return 0;
}
```

---

## 作者：xyzqwq (赞：2)

## 题意

定义对数序列为一个长为 $n$ 的序列 $\{a_n\}$，满足对于所有正整数 $x,y$ 且 $xy\le n$，有 $a_{xy}=a_x+a_y$。

每次询问，对于一个对数序列（题目告诉你这个序列的选取与答案无关），若改动其中一个数，问需要再改动多少个数才能使其再次成为一个对数序列。

## 题目分析

首先来研究对数序列的一些性质。

首先，$a_1=a_1+a_1$，故在任何对数序列里，$a_1$ 都只能是 0。故若要改动 $a_1$ 使其不为 0，$a_n$ 就不可能再变回一个对数序列。

另外对于一个质数 $p$，它没有非平凡的因子，故它的更改不会影响到比其小的数，只会影响到 $p$ 的倍数。

这样我们不妨构造一个平凡的对数序列，由于质数的大小互不干扰，故可以把它们都设成 1，这样其他数上的值也就随之生成。



|1|2|3|4|5|6|7|8|9|10|11|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|0|1|1|2|1|2|1|3|2|2|1|

在生成这个数列的时候，很容易发现，每个数上所对应的值其实就是它的素因子个数（计算重数），这启发我们，对数数列的性质与素因子分解有关。

任取一个正整数 $N$，对其进行素因子分解，有

$$
N=p_1^{k_1}p_2^{k_2}p_3^{k_3}\cdots p_n^{k_n}
$$

由对数序列的定义，我们有

$$
a_N=k_1a_{p_1}+k_2a_{p_2}+k_3a_{k_3}\cdots+k_na_{p_n} 
$$

考虑对这个 $a_N$ 进行修改，设这个修改是 $a_N+k,k\in \mathbb Z$，对于任意一个 $a_{p_i}$，只需令 $a_{p_i}'=a_{p_i}+\frac{k}{k_i}$，就可以得到对 $a_N$ 的合适修改，而由于这个 $p_i$ 是质数，还不会对除了其倍数外的其他数产生干扰，所以只需要修改 $p_i$ 的所有倍数即可。修改的次数为 $\lfloor{\frac{n}{p_i}}\rfloor$，由于这些修改里包括修改 $a_N$，故统计答案是秩序统计 $\lfloor \frac{n}{p_i} \rfloor-1$。最终答案就是对于所有 $p_i$ 取答案最小的那个。

## 代码实现

根据上文的分析，我们只需要对每次输入的数分解质因数并统计答案即可。若使用试除法，最终的复杂度就是 $O(q\sqrt n)$，可以通过这道题。

```cpp
//主要代码
int work(int x){
    if(x==1) return -1;//无解情况
	int ans=0x3f3f3f3f;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			while(x%i==0) x/=i;
			ans=min(ans,(n/i)-1);
		}
	}
    if(x>1) return  min(ans,n/x-1);
	return ans;
}
```

---

## 作者：zhujiahao114514 (赞：0)

## 做法

首先我们考虑无解的情况。

当 $a_{1}$ 被改变的时候，那么答案就是无解。可以证明：

$a_{i}=a_{1\times i}=a_{1} + a_{i}\\$

移项得：$a_{1}=0$。

所以 $a_{1}$ 必须是零。

其他所有的情况都是有解的了。

我们来考虑有解的情况。我们可以知道，当 $a_{i}$ 被修改时，他的因数和他的倍数都要修改若干个。当他的因数被修改的时候，他的因数的因数也会被修改，以此类推，直到推到素数为止。所以最后被修改的次数就是 $\frac{n}{x}-1$，其中 $x$ 时 $i$ 的一个质因数。因为这是一个反比例函数，修改次数随着 $x$ 的增大而减小，所以如果想让修改次数最小，那么 $x$ 就应该最大。所以 $x$ 就是 $i$ 的最大的质因数。

这就很简单了，直接上代码。

## code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') 
	{
		if(c=='-') f=-1;
		c=getchar(); 
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int n,q,x,sum,ans;
signed main()
{ 
	n=read(),q=read();
	while(q--)
	{
		x=read();
		if(x==1) 
		{
			cout<<-1<<endl;
			continue;
		}
		ans=0;
		for(int i=2;i<=sqrt(x);i++)
		{
			if(x%i==0) ans=max(ans,i);
			while(x%i==0) x/=i;	
		}
		if(x!=1) ans=max(ans,x);
		sum=n/x-1;
        if(ans) ans=n/ans-1;
		if(ans) cout<<ans<<endl;
		else cout<<sum<<endl;
	}
	return 0;
}
```

完结撒花。

---

## 作者：ni_ju_ge (赞：0)

## 思路
首先，由于要求 $a_{xy} = a_x + a_y$，所以 $a_{x \times 1} = a_x + a_1$，因此 $a_1 = 0$，所以当 $x = 1$ 时无解。

然后，当一个对数数列中的第 $x$ 项改变时，$x$ 的因数项也需要改变，同样，这个因数的因数也要随之改变。显然，最后需要改变的是一个质数。而改变了这个质数之后，这个质数的全部倍数都需要随之改变，所以要想改变的次数最小，那么这个质数一定是 $x$ 最大的质数，设这个质数为 $y$，那么方案数就是 $\left\lfloor\dfrac{n}{k}\right\rfloor - 1$（因为 $x$ 不用再次修改了，所以要减去一）。
## 代码
```cpp
#include<iostream>
using namespace std;
int n,x,y,t;
int main()
{
	cin>>n>>t;
	for(int i=1;i<=t;i++)
	{
		y=0;
		cin>>x;
		if(x==0)
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=2;i*i<=x;i++)
		{
			if(x%i==0)y=i;
			while(x%i==0)x/=i;
		}
		if(x>1)y=x;
		cout<<n/y-1<<endl;
	}
}
```

---

## 作者：arrow_king (赞：0)

# 题意

定义一个数列是**对数数列**当且仅当对于任意一组 $x,y\ (xy\le n)$ 都有 $a_{xy}=a_x+a_y$。现在有一个长度为 $n$ 的有理数对数数列，有 $q$ 次询问，每次将 $a_x$ 修改为 $\pi$，求在不修改 $a_x$ 的前提条件下修改别的数使得 $a$ 重新变为对数数列（不强制是有理数）。

$n\le10^8,q\le10^4$。

# 思路

修改 $1$ 的时候输出 $-1$ 特判一下。

注意到 $n$ 比较大而 $q$ 比较小，发现 $\mathcal O(q\sqrt n)$ 能过。

首先考虑强制修改 $x$ 后哪些下标必须修改，容易发现如果 $x$ 发生变化，那么 $x$ 的一个因数位置也要变化才能调整 $x$。如果这个位置是 $y$，那么 $y$ 也需要有一个因数发生变化……可以发现选择质因数最优。

选择哪个质因数？最大的质因数就好了。

实现上我是筛出了 $1\sim\sqrt n$ 的所有质数进行判断，时间复杂度 $\mathcal O(q\sqrt n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long
#define il inline
#define Prime 10000
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
bool f[Prime+5];
int p[Prime+5],cnt;
int main() {
	int n=read(),q=read();
	for(int i=2;i*i<=n;i++) {
		if(!f[i]) p[++cnt]=i;
		for(int j=1;j<=cnt&&i*i*p[j]*p[j]<=n;j++) {
			f[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
	while(q--) {
		int x=read();
		if(x==1) {
			printf("-1\n");
			continue;
		}
		int maxn=0;
		for(int i=1;i<=cnt&&p[i]*p[i]<=x;i++) {
			if(x%p[i]!=0) continue;
			while(x%p[i]==0) x/=p[i];
			maxn=max(maxn,p[i]);
		}
		if(x!=1) maxn=max(maxn,x);
		if(maxn!=0) printf("%d\n",n/maxn-1);
		else printf("%d\n",n/x-1);
	}
	return 0;
}

```

---

## 作者：slzx2022YuYihan (赞：0)

# Solution
首先了解一下对数序列.

$a_{xy}=a_x+a_y$.

这就很类似对数函数的性质:$log_{xy}=log_x+log_y$.

若 $p\in prime$,那么 $a_p=a_1+a_p\implies a_1=0$.

因此,如果询问中 $x=1$,那么直接输出 $\mathbb -1$.

然后开始手动模拟.

如果 $x=12$,而 $12=2\times 6=3\times 4$,究竟改变哪个?

*	如果改变 $\mathbb 2$,那么 $\mathbb 2$ 的倍数都要改变
*	如果改变 $\mathbb 3$,那么 $\mathbb 3$ 的倍数都要改变
*	如果改变 $\mathbb 6$,而 $6=2\times 3$,改变 $\mathbb 3$ 的倍数最优
*	如果改变 $\mathbb 4$,而 $4=2\times 2$,只能改变 $\mathbb 2$ 的倍数

可以发现,我们相当于在对 $x$ 进行分解质因数,改变最大质因子的倍数是最优解.那么答案就是 $n$ 除以最大质因子减去 $\mathbb 1$(自己本身不算),这题就做完了.

分解质因数复杂度 $O(\sqrt{n})$,总复杂度 $O(q\sqrt{n})$.

另外,此题还是灰的,建议管理员给这道题评个绿及以下.

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>inline void read(T& x){
    x = 0; T w = 1; char ch = getchar();
    while (!isdigit(ch)){if (ch == '-')	w = -1; ch = getchar();}
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    x *= w;
}
template<typename T>inline void write(T x){
    if (x < 0)	putchar('-'), x = ~(x - 1);
    if (x > 9)	write(x / 10);
    putchar(x % 10 ^ 48);
}

ll n, q;

int main(){
    //ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    read(n), read(q);
    while (q--){
        ll x;
        read(x);
        if (x == 1){
            puts("-1");
            continue;
        }
        ll maxin;
        for (ll i = 2; i * i <= x; ++i)
            if (x % i == 0){
                maxin = i;
                while (x % i == 0)  x /= i;
            }
        if (x > 1)  maxin = x;
        write(n / maxin - 1), putchar('\n');
    }

    return 0;
}
```

---

