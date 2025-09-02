# Koishi Loves Construction

## 题目描述

Koishi 决定走出幻想乡成为数学大师！

Flandre 听说她数学学的很好，就给 Koishi 出了这样一道构造题：

Task1：试判断能否构造并构造一个长度为 $n$ 的 $1 \dots n$ 的排列，满足其 $n$ 个前缀和在模 $n$ 的意义下互不相同。

Task2：试判断能否构造并构造一个长度为 $n$ 的 $1 \dots n$ 的排列，满足其 $n$ 个前缀积在模 $n$ 的意义下互不相同。

按照套路，Koishi 假装自己根本不会捉，就来找你帮忙辣。

## 说明/提示

对于每组数据：

1. 如果您对于构造的存在性判断正确，您将会得到 $30\%$ 的分数，若您的构造符合题意或者确实不存在符合题意的构造，您将会得到剩余的 $70\%$ 的分数。
2. 如果您对于构造的存在性判断不正确，您将不会得到任何分数。

对于每组测试点，您的得分将是本组数据点中得分的最小值。

测试点类型 $1$：$10$ 分，满足 $X = 1$，$1 \leq n \leq 10$。  
测试点类型 $2$：$40$ 分，满足 $X = 1$，$1 \leq n \leq {10}^5$。  
测试点类型 $3$：$10$ 分，满足 $X = 2$，$1 \leq n \leq 10$。  
测试点类型 $4$：$40$ 分，满足 $X = 2$，$1 \leq n \leq {10}^5$。

对于所有测试点，满足 $1 \leq T \leq 10$。

## 样例 #1

### 输入

```
1 1
8```

### 输出

```
2 8 7 6 5 4 3 2 1```

## 样例 #2

### 输入

```
2 1
11```

### 输出

```
2 1 2 3 5 10 6 7 4 9 8 11```

# 题解

## 作者：George1123 (赞：69)

# 题解-Koishi Loves Construction

**[博客中阅读](https://www.cnblogs.com/Wendigo/p/12497075.html)**

**前缀知识**
> 质数
> 逆元
> 暴搜

---

> [Koishi Loves Construction](https://www.luogu.com.cn/problem/P3599)

> 给定 $X$，$T$ 组测试数据，每次给一个 $n$。
> 1. 如果 $X=1$，构造一个 $1\sim n$ 的排列使得前缀和模 $n$ 互不相同。
> 2. 如果 $X=2$，构造一个 $1\sim n$ 的排列使得前缀积模 $n$ 互不相同。

> 数据范围：$1\le T\le 10$，$1\le n\le 10^5$，$X\in\{1,2\}$。

---

属于“思维体操”，做之前会异常兴奋，做之后会只想睡觉。

---

设序列为 $a\{n\}$，前缀和/积为 $sum\{n\}$。

分类讨论：

## $X=1$

**初步发现：**

1. 不能有区间 $[L,R](L\neq 1)$ 和是 $n$ 的倍数，否则 $sum_{L-1}\equiv sum_R\pmod n$。

2. 设 $a_i=n$，必须 $i=1$，否则 $sum_i\equiv sum_{i-1}\pmod n$。

3. $\therefore n\in \mathbb{even}\cup {1}$，因为如果 $n\in \mathbb{odd}$：

$$\sum\limits_{i=1}^{n-1}=\frac{(1+n-1)\times(n-1)}{2}=n\times(\frac{n-1}{2})\equiv 0\pmod n$$

然后由此判断输出 $0\&1$，交了一发，$15$ 分——很明显判断对了。

**于是开始打暴力：**

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define lng long long
#define lit long double
#define re register
#define kk(i,n) " \n"[i==n]
const int inf=0x3f3f3f3f;
const lng Inf=0x3f3f3f3f3f3f3f3f;

//&Data
const int N=1e5;
int a[N+10],n;
bool vis[N+10],use[N+10];
void dfs(int x,int sm){
    if(x==n+1){
        for(int i=1;i<=n;i++)
            printf("%d%c",a[i],kk(i,n));
        return ;
    }
    for(int i=1;i<=n;i++)
    if(!use[i]){
        use[i]=1;
        if(!vis[(sm+i)%n]){
            vis[(sm+i)%n]=1;
            a[x]=i;
            dfs(x+1,(sm+i)%n);
            vis[(sm+i)%n]=0;
        }
        use[i]=0;
    }
}

//&Main
int main(){
    scanf("%d",&n);
    dfs(1,0);
    return 0;
}


/***
input
6
output
6 1 4 3 2 5
6 2 5 3 1 4
6 4 1 3 5 2
6 5 2 3 4 1
***/
```

输入 $6$ 后，看这个输出：

```cpp
6 1 4 3 2 5
```

得出规律：

1. 如果 $i\in \mathbb{odd}$，$a_i=n+1-i$。
2. 如果 $i\in \mathbb{even}$，$a_i=i-1$。


```cpp
//&Solve1
void solve1(){
    memset(a,0,sizeof a);
    memset(sum,0,sizeof sum);
    if((n&1)&&(n^1)) return puts("0"),void();
    else {
        putchar('2'),putchar(' ');
        for(int i=1;i<=n;i++)
            printf("%d%c",(i&1)?n+1-i:i-1,kk(i,n));
    }
}
```

提交后得到 $50$ 分，说明对了。

**证明：**

模 $n$ 意义下，上述序列可以看成：

``` cpp
0 1 -2 3 -4 5
```

很明显：

1. 如果 $i\in\mathbb{odd}$，$sum_i\in\{0,-1,-2,...\}$。
2. 如果 $i\in\mathbb{even}$，$sum_i\in\{1,2,3,...\}$。

最后在模 $n$ 意义下还原成正数，

$$\{sum_1,sum_2,...,sum_n\}=\{1,2,...,n\}$$

## $X=2$

**初步发现：**

1. 不能有区间 $[L,R](L\neq 1)$ 的积 $\equiv 1\pmod n$。
2. 不能有区间 $[L,R](R\neq n)$ 的积 $\equiv 0\pmod n$。
3. $\therefore a_1=1$。
4. $\therefore a_n=n$。
5. 还有如果 $n|\prod\limits_{i=1}^{n-1}i$ 也不行，很明显。 

然后由此判断输出 $0\&1$，交了一发，$65$ 分——很明显判断对了

**至于序列长什么样，暴力再来一发：**

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define lng long long
#define lit long double
#define re register
#define kk(i,n) " \n"[i==n]
const int inf=0x3f3f3f3f;
const lng Inf=0x3f3f3f3f3f3f3f3f;

//&Data
const int N=1e5;
int a[N+10],n;
bool vis[N+10],use[N+10];
void dfs(int x,int sm){
    if(x==n+1){
        for(int i=1;i<=n;i++)
            printf("%d%c",a[i],kk(i,n));
        return ;
    }
    for(int i=1;i<=n;i++)
    if(!use[i]){
        use[i]=1;
        if(!vis[(sm*i)%n]){
            vis[(sm*i)%n]=1;
            a[x]=i;
            dfs(x+1,(sm*i)%n);
            vis[(sm*i)%n]=0;
        }
        use[i]=0;
    }
}

//&Main
int main(){
    scanf("%d",&n);
    dfs(1,1);
    return 0;
}
/***
input
7
output
1 2 5 6 3 4 7
1 3 4 6 2 5 7
1 4 3 6 5 2 7
1 5 2 6 4 3 7
input
11
output
try it by yourself!
***/
```

进一步推测：如果 $n$ 是质数或者 $n=1$ 或者 $n=4$，可以构造。

由此判断输出 $0\& 1$ 提交一发，$65$ 分，很明显对了（然而没什么用啊。

> 然后我下了一下数据，竟然发现输出数据只有 $0\&1$。
> 
> 再进一步发现：第二个数只能是 $2$，没用。

这时看输出（我看了 $20$ 分钟）

```cpp
1 2 5 6 3 4 7

//前缀积%n：
1 2 3 4 5 6 0
```

有一个发现： $sum_i\equiv i\pmod n$。

然后我茅塞顿开：可以试试逆元求序列使得 $sum_i\equiv i\pmod n$（当然 $1$ 或 $4$ 要特判）：

```cpp
void solve2(){
	if(np[n]&&(n^1)&&(n^4)) return puts("0"),void();
	else {
		if(n==1) return puts("2 1"),void();
		if(n==4) return puts("2 1 3 2 4"),void();
		putchar('2');
		for(int i=1,tmp=1,sum=1;i<=n-1;i++){
			printf(" %d",tmp);
			tmp=1ll*Pow(sum,n-2)*(i+1)%n;
			sum=1ll*sum*tmp%n;
		}
		printf(" %d",n),putchar('\n');
	}
}
```

提交了一发，$\texttt{AC}$ 了。

**证明：**

$$\because (i-1)\times a_i\equiv i\pmod n$$

很明显，对于每个 $i$，$a_i$ 是唯一的，只需证明：对于每个 $a_i$，$i$ 是唯一的。

反证：假设对于每个 $a_i$，$i$ 不唯一，设 $a_x=a_y=k(x>y)$。

$$\therefore k(x-1)\bmod n=x,k(y-1)\bmod n=y$$

$$\therefore k(x-y)\bmod n=(x-y)$$

因为 $(x-y)\in\{1,2,...,n\}$，所以必定有 $k(x-y)\bmod n=(x-y+1)$。

**矛盾！**故对于每个 $a_i$，$i$ 是唯一的。

## $\texttt{code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define lng long long
#define lit long double
#define re register
#define kk(i,n) " \n"[i==n]
const int inf=0x3f3f3f3f;
const lng Inf=0x3f3f3f3f3f3f3f3f;

//&Data
const int N=1e5;
int X,T,n;

//&Solve1
void solve1(){
	if((n&1)&&(n^1)) return puts("0"),void();
	else {
		putchar('2'),putchar(' ');
		for(int i=1;i<=n;i++)
			printf("%d%c",(i&1)?n+1-i:i-1,kk(i,n));
	}
}

//&Solve2
bitset<N+10> np;
int p[N+10],cnt;
void Prime(){
	np[1]=true;
	for(int i=1;i<=N;i++){
		if(!np[i]) p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=N;j++)
			np[i*p[j]]=1;
	}
}
int Pow(int a,int x){
	int res=1;
	for(;x;a=1ll*a*a%n,x>>=1)
		if(x&1) res=1ll*res*a%n;
	return res;
}
void solve2(){
	if(np[n]&&(n^1)&&(n^4)) return puts("0"),void();
	else {
		if(n==1) return puts("2 1"),void();
		if(n==4) return puts("2 1 3 2 4"),void();
		putchar('2');
		for(int i=1,tmp=1,sum=1;i<=n-1;i++){
			printf(" %d",tmp);
			tmp=1ll*Pow(sum,n-2)*(i+1)%n;
			sum=1ll*sum*tmp%n;
		}
		printf(" %d",n),putchar('\n');
	}
}

//&Main
int main(){
	scanf("%d%d",&X,&T);
	if(X==2) Prime();
	for(int ti=1;ti<=T;ti++){
		scanf("%d",&n);
		if(X==1) solve1();
		else solve2();
	}
	return 0;
}
```

---

**祝大家学习愉快！**


---

## 作者：断清秋 (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/P3599)

神仙构造题，大概还是 OI-Wiki 上例题。


## Task 1

据说是一道 MO 原题。

由于 $n$ 个前缀和模 $n$ 互不相同，那么 $n$ 必然只能放在第一个，否则就重了。

那么我们考虑无解的情况，容易发现 $n$ 为奇数时，第 $n$ 个前缀和为 $\dfrac{n(n+1)}{2}$，然后 $\dfrac{n(n+1)}{2} \equiv0\pmod n$，与题意矛盾，因此 $n$ 为奇数时无解。

但是要注意特判 $n=1$ 的情况！

考虑 $n$ 为偶数，由于直接按模 $n$ 的一个完全剩余系去构造并不可取，可以考虑构造模 $n$ 意义下 $0,1,-1,2,-2…$ 的数列，那么显然可以构造出 $n,1,n-2,3,n-4…2,n-1$ 这样的数列，易知是满足题意的。

归纳一下，可以得到答案数列的第 $i$ 项为 $\begin{cases}n-i+1,i \equiv1\pmod 2\\i-1,i \equiv0\pmod 2\end{cases}$

## Task 2

要求 $n$ 个前缀积模 $n$ 互不相同，因此 $n$ 显然要放到最后一位。

然后依然考虑无解的情况，因为 $n$ 为合数时必然存在 $p,q<n,p \ne q$，使得 $pq \equiv0\pmod n$ ，因此 $n$ 为合数时必然无解。

但是要特判 $n=1$ 和 $n=4$ 的情况。（由于 $4=2 \times 2$，不存在合法的 $p,q$）

那么考虑 $n$ 为质数的情况，由于前缀积模 $n$ 的结果没啥特征，所以考虑构造最一般的模 $n$ 意义下的数列 $1,2,3,…n-1,0$。

这个整数数列我依然不会构造，但是如果推广到有理数数列，那么显然的构造是 $1,\dfrac{2}{1},\dfrac{3}{2},\dfrac{4}{3},…\dfrac{n}{n-1}$。

然后把分数变成整数，自然想到求逆元。由于模数 $n$ 为质数，可以利用费马小定理大力求逆元即可。

事实上，这样求出的 $n$ 个数是 $0∼n-1$ 中所有数模 $n$ 的逆元 $+1$，所以显然数列中的元素非重。

于是就做完了。

时间复杂度 $O(Tnlogn)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
using namespace std;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
ll ksm(ll a,ll b,ll p)
{
	ll ans=1,base=a;
	while(b)
	{
		if(b&1)
			ans=ans*base%p;
		base=base*base%p;
		b/=2;
	}
	back ans;
}
int t,x;
int check(int x)
{
	if(x==0||x==1)
		back 0;
	if(x==2)
		back 1;
	if(x%2==0)
		back 0;
	for(ri i=3;i*i<=x;i+=2)
		if(x%i==0)
			back 0;
	back 1;
}
int main()
{
	x=read(),t=read();
	while(t--)
	{
		int n;
		n=read();
		if(x==1)
		{
			if(n==1)
			{
				cout<<2<<" "<<1<<"\n";
				continue;
			}
			if(n%2==1)
			{
				cout<<0<<"\n";
				continue;
			}
			cout<<2<<" ";
			for(ri i=1;i<=n;i++)
				if(i%2==1)
					cout<<n-i+1<<" ";
				else
					cout<<i-1<<" ";
			cout<<"\n";
		}
		if(x==2)
		{
			if(n==1)
			{
				cout<<2<<" "<<1<<"\n";
				continue;
			}
			if(n==2)
			{
				cout<<2<<" "<<1<<" "<<2<<"\n";
				continue;
			}
			if(n==4)
			{
				cout<<2<<" "<<1<<" "<<3<<" "<<2<<" "<<4<<"\n";
				continue;
			}
			if(!check(n))
				cout<<0<<"\n";
			else
			{
				cout<<2<<" "<<1<<" ";
				for(ri i=2;i<=n-1;i++)
					cout<<i*ksm(i-1,n-2,n)%n<<" ";
				cout<<n<<"\n";
			}
		}
	}
	back 0;
}
```

---

## 作者：oscar (赞：9)

**Task 1:** $> 1$ 的奇数无解，$1$ 的解显然

偶数的一种可行解为 $0,1,-2,3,-4,\cdots,n-1$ 把 $\leq 0$ 的数 $+n$ 即可

**Task 2:** 我想不出来官方题解那么妙的构造怎么办？

可以转化为Task1解决。

$>4$ 的合数无解，$1,2,4$ 的解显然

对于奇质数的情况根据某定理恰有 $\varphi(n-1)$ 个原根，（通过随机+暴力判定可以较高效地）任取一个原根，设其为 $g$ 

将 $g^0,g^1,\cdots,g^{n-2}$ 一一映射到 $0,1,\cdots,n-2$ 即可转化为 $n'=n-1$ 版本的Task1（显然 $n-1$ 是偶数）

在以上结果的结尾添加一个 $n$ 就是Task2的一种构造

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int ty,T,n;
std::mt19937 ran;
int pw[111111],fl[111111];//pw存原根的幂
bool ok(int g)//暴力检验是否为原根
{
	memset(fl,0,sizeof(fl));
	pw[0]=1;fl[1]=1;
	for(int i=1;i<n-1;i++)
	{
		pw[i]=1ll*pw[i-1]*g%n;
		if(fl[pw[i]])return false;
		fl[pw[i]]=1;
	}
	return true;
}
int main()
{
	ios_base::sync_with_stdio(false);
	ran.seed(0);
	cin>>ty>>T;
	while(T--)
	{
		cin>>n;
		if(ty==1)
		{
			if(n==1)cout<<"2 1"<<endl;
			else if(n%2==0)
			{
				cout<<2<<' '<<n;
				for(int i=1;i<n;i++)cout<<' '<<(i%2?i:n-i);
				cout<<endl;
			}
			else cout<<0<<endl;
		}
		else
		{
			if(n==1)cout<<"2 1"<<endl;
			else if(n==2)cout<<"2 1 2"<<endl;
			else if(n==4)cout<<"2 1 3 2 4"<<endl;
			else
			{
				int zz=1;//是否质数
				for(int i=2;i*i<=n;i++)
				{
					if(n%i==0)
					{
						zz=0;
						break;
					}
				}
				if(!zz)cout<<0<<endl;
				else
				{
					int g=ran()%(n-1)+1;
					while(!ok(g))g=ran()%(n-1)+1;
					cout<<2<<' '<<pw[0];
					for(int i=1;i<n-1;i++)cout<<' '<<(i%2?pw[i]:pw[n-1-i]);
					cout<<' '<<n<<endl;
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：loceaner (赞：4)


## 思路

一道构造好题。

### Task1

能够看出两点：

- 第一个数必须是 $n$。

  因为有 $x+n\equiv x(\bmod n)$，如果第一个数不是 $n$，必然会有两个相邻的前缀和模 $n$ 的值相等。

- 除了 $1$ 之外的奇数都不存在正确构造。

  当 $n$ 为奇数时，有 

  $$\sum\limits_{i=1}^{n-1}i\mod n=\dfrac{n\times(n-1)}{2}\mod n=0$$

  因为已经确定了第一个数为 $n$，所以一定会冲突。

剩下的 $n-1$ 个数，可以找到一种为 $\text{1 -2 3 -4 5...}$ 的方案，保证 $1\sim n - 1$ 的所有数都能出现，因为这样的话前缀和在模 $n$ 意义下获得的数就是 $1\sim n - 1$，然后负数要转化为正数，最后的序列就能够保证每个数只出现了一次。

代码里的实现是先输出第一个数 $n$，然后输出第 $2\sim n$ 个数，如果 $i\mod2 = 1$ 则输出 $n+1-i$，否则输出 $i-1$。

### Task2

容易看出：

- $n$ 只能是最后一个数。

  若 $n$ 不为最后一个数，那么在 $n$ 之后的前缀积在模 $n$ 意义下一定为 $0$，必定会冲突。

剩下的数，我们的目标是构造一个在模 $n$ 意义下前缀积连续递增的序列。

那么一种可行的构造方案是 $1,\frac{2}{1},\frac{3}{2}...\frac{n}{n-1}$，因此我们只需要求出每个数的逆元，输出即可。

但是会有无解的情况，那就是不为 $4$ 的合数一定无解，因为如果 $n$ 是合数，那么一定存在小于 $n$ 的两个数乘积为 $n$，所以只有 $1,4$ 和所有的质数有解。

注意看特判 $1$ 和 $4$ 的情况，因为 $4\nmid 3!$。

## 代码

```cpp
/*
  Name: P3599 Koishi Loves Construction
  Author: Loceaner
  Date: 08/09/20 11:24
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int opt, T, inv[A];

inline bool judge(int x) {
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}

signed main() {
  opt = read(), T = read();
  while (T--) {
    int n = read();
    if (opt == 1) {
      if (n % 2 && n != 1) puts("0");
      else {
        cout << 2 << " ";
        cout << n << " ";
        for (int i = 2; i <= n; i++) {
          if (i % 2) cout << n + 1 - i << " ";
          else cout << i - 1 << " ";
        }
        puts("");
      }
    }
    if (opt == 2) {
      if (n == 1) {
        puts("2 1");
        continue;
      }
      if (n == 4) {
        puts("2 1 3 2 4");
        continue;
      }
      if (!judge(n)) puts("0");
      else {
        int mod = n;
        inv[0] = inv[1] = 1;
        for (int i = 2; i < n; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
        cout << 2 << " ";
        for (int i = 1; i < n; i++) cout << i * inv[i - 1] % mod << " ";
        cout << n << '\n';
      }
    }
  }
}

```

---

## 作者：w (赞：4)

官方题解： https://www.luogu.org/discuss/show?postid=7867


---

## 作者：超级玛丽王子 (赞：2)

有趣的小构造。

# Task 1

> 构造一个 $\{a_n\}$ 使得 $\nexists\ i,j\in[1,n],\sum\limits_{k=1}^i a_k\equiv\sum\limits_{k=1}^ja_k\pmod n$

首先考虑比较特别的 $n$。注意到如果 $n$ 的位置不在第一个而在第 $i$ 个 $(i>1)$，则会有 $S_i=S_{i-1}+n\equiv S_{i-1}\pmod n$。因此，$n$ 必须要放在第一个。

接下来考虑构造前缀和序列。发现形如

$$0,1,-1,2,-2\cdots$$

的前缀和序列是易于构造的，即只需构造

$$0,1,-2,3,-4,\cdots$$

即可。

要注意的是如果 $n>1\land 2\nmid n$ 那么势必存在 $S_n=\dfrac{n(n+1)}{2}\equiv S_1\equiv0\pmod n$，是不合法的。

由于需要构造 $1-n$ 的排列，对于非正数要加上一个 $n$。

# Task 2

> 构造一个 $\{a_n\}$ 使得 $\nexists\ i,j\in[1,n],\prod\limits_{k=1}^i a_k\equiv\prod\limits_{k=1}^ja_k\pmod n$

首先注意到当 $n$ 是 $1$ 时，构造 $1$ 即可；

接下来发现如果 $n$ 是合数，那么会存在他的两个因子相乘模 $n$ 为 $0$，也就会出现两个相同的前缀积。这里要注意的是 $4$ 是一个很特别的合数，很多题目都要特判 $4$，这里也是，$4$ 可以构造出 $1,3,2,4$

最后来研究一下 $n$ 是质数的情况。不妨考虑一个类似连锁约分的东西，即

$$1,\dfrac 2 1,\dfrac 3 2,\dfrac 4 3,\cdots,n$$

不难发现前缀积满足要求。

此外还需要注意，要求的是 $1-n$ 的排列，还需要证明以上构造满足条件。

注意到这列数分别是 $0,\cdots,n-1$ 模 $n$ 的逆元再加上 $1$，所以构造一定成立。

由于 $T\le 10,n\le10^5$，所以判断质数可以直接采用 $O(\sqrt n)$ 的判断，比 $O(n)$ 筛一遍快。此外，乘法逆元用 $O(n)$ 递推，就不需要 $n\log n$ 的快速幂或者扩欧了。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	int x=0;
	while(ch>='0'&&ch<='9') x=(x*10)+(ch^48),ch=getchar();
	return x;
}
inline void write(int x) {
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
inline void wr(int x, char ch=' ') {
	write(x);
	putchar(ch);
}
bool isprime(int num) {
	for(int i=2;i*i<=num;++i) if(!(num%i)) return false;
	return true;
}
typedef long long ll;
ll inv[100050];
int main(void) {
	int x=read(),t=read();
	while(t--) {
		int n=read();
		if(x==1) {
			if(n&1&&(n^1)) wr(0,'\n');
			else {
				wr(2);
				for(int i=0;i<n;++i) {
					if(i&1) wr(i);
					else wr(n-i);
				}
				putchar('\n');
			}
		}
		else {
			if(isprime(n)) {
				wr(2),wr(1);
				inv[1]=1;
				for(int i=2;i<n;++i) inv[i]=1ll*(n-n/i)*inv[n%i]%n,wr((1ll*inv[i-1]*i+n)%n);  //乘法逆元递推
				if(n^1) wr(n,'\n');
 			}
 			else if(n==4) wr(2),wr(1),wr(3),wr(2),wr(4,'\n');
 			else wr(0,'\n');
		}
	}
	return 0;
}


```

---

## 作者：pomelo_nene (赞：2)

## Task  1

考虑前缀和数列而不是考虑原数列。

我们发现 $p+n \equiv p (\bmod \ n)$，因此 $n$ 放在除首位的任何地方，都会导致出现两个前缀和相等。所以 $n$ 放在首位，$sum_1 \bmod n=0$，$0$ 这个位置就被占了。

这个时候我们就可以排除大部分情况：如果 $n$ 为奇数，一定无解。

证明：

$$\displaystyle \sum_{i=1}^{n-1} i =\dfrac{n\times(n-1)}{2} \bmod n =0$$

此时一定会冲突。

再考虑剩下的。我们发现模 $n$ 意义下互不相同，实际上相当于模 $n$ 意义下的结果为 $1,-1,2,-2,\dots$（不一定按此序），并且可以和 $1,2,\dots,n-1$ 互相对应。这个时候我们就会有一个构造方案：

首先放下模 $n$ 为 $1$ 的数，然后放下模 $n$ 为 $-2$ 的数，接下来放下模 $n$ 为 $3$ 的数，以此类推。显然这样可以覆盖 $1,2,\dots ,n-1$ 中的所有的数。这个构造方案就是合理的。

注意特判 $1$ 的情况。

## Task 2

考虑构造一个序列，使得前缀积在模 $n$ 意义下递增。很显然可以有 $1,\dfrac{2}{1},\dfrac{3}{2},\dots,\dfrac{n-1}{n-2},\dfrac{n}{n-1}$。这个序列显然是合法的。

完了吗？考虑无解情况。如果 $n$ 为合数，那么在构造前缀积的过程中，一定存在两个数 $p,q$ 使得 $pq \bmod n =0$，此时无解。如果是质数就不会存在这样的情况了。

注意特判 $1$ 和 $4$ 的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL inv[100005];
int main(){
	LL T,task;
	scanf("%lld %lld",&task,&T);
	if(task==2)
	{
		while(T-->0)
		{
			LL mod;
			LL n;
			scanf("%lld",&n);
			if(n==1)
			{
				puts("2 1");
				continue;
			}
			if(n==4)
			{
				puts("2 1 3 2 4");
				continue;
			}
			for(LL i=2;i*i<=n;++i)
			{
				if(n%i==0)
				{
					puts("0");
					goto fail;
				}
			}
			putchar('2');
			mod=n;
			inv[0]=inv[1]=1;
			for(LL i=2;i<=n-1;++i)	inv[i]=mod-(mod/i)*inv[mod%i]%mod;
			for(LL i=1;i<=n-1;++i)	printf(" %lld",i*inv[i-1]%mod);
			printf(" %lld\n",n);
			fail:;
		}
		return 0;
	}
	while(T-->0)
	{
		LL n;
		scanf("%lld",&n);
		if(n==1)
		{
			puts("2 1");
			continue;
		}
		if(n&1)
		{
			puts("0");
			continue;
		}
		printf("2 %lld",n);
		for(LL i=1;i<n;++i)
		{
			if(i&1)	printf(" %lld",n-i);
			else	printf(" %lld",i);
		}
		puts("");
	}
	return 0;
}
```

---

