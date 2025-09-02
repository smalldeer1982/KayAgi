# p-binary

## 题目描述

### 题意简述

给定整数 $n,p$，求最小的 $x$ 使得其满足

$$\sum_{1}^{x} (2^k+p)=n$$

其中 $k$ 可以是任意自然数。

## 样例 #1

### 输入

```
24 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
24 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
24 -1
```

### 输出

```
4
```

## 样例 #4

### 输入

```
4 -7
```

### 输出

```
2
```

## 样例 #5

### 输入

```
1 1
```

### 输出

```
-1
```

# 题解

## 作者：robin12138 (赞：7)

[**CF1225C P-binary**](https://codeforces.com/problemset/problem/1225/C)

[**更好的阅读体验请戳这里**](https://www.cnblogs.com/wmq12138/p/11748932.html)

**题意**：

给定 $n,p$,且$n \leqslant 10^9,p\in [-1000,1000]$，请你构造出$m$个非负整数$a_i$(可以重复)，满足$\sum_{i=1}^m 2^{a_i}+p = n$，求$m$的最小值

**题解**

用$cnt(x)$表示$x$的二进制位上为$1$的个数,

发现对$cnt(x)\leqslant y \leqslant x$

都能构造出 $x = \sum_{i=1}^y 2^{a_i},a_i\geqslant 0$

那么 从小到大枚举$i$，看 $cnt(n-i*p) \leqslant i \leqslant n-k*i$ 是否成立即可

```cpp
int m,n,p;
il int cnt(int x) 
{ 
    int ret=0; 
    while(x) x-=x&-x,++ret; return ret; 
}
int main()
{
    n=read(); p=read();
    for(int i=1;i<=n-i*p;++i)
        if(i>=cnt(n-i*p))
            printf("%d\n",i),exit(0); 
    puts("-1");
    return 0;
}
```

---

## 作者：Froggy (赞：5)

枚举大法好!

枚举答案即可(雾)

设现在枚举到的答案是$cnt$

设$x=n+p \times cnt$

显然,若此时$x \le 0$ 直接输出-1走人

否则要看能否把$x$分解成$cnt$个$2^k(k \in N)$的和

这个...怎么验证呢?

先求出$x$在2进制下1的个数,计为$e$,若$e \le cnt$就成立了

完了???呵呵,我在考场上这样A了,但最后$FST$了,(~~呜呜呜~~,跟积分说goodbye)

有一个反例:`151 50`

应该输出-1,可是如果按上述做法会输出2

分析一下:当cnt=2时,x=1,不能分解成2个$2^k$,但$e=1,e \le cnt$

**所以,我们还要判断必须满足$cnt \le x$**

这样才算做完!

*code*

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
ll n,p,cnt;
ll Get(ll x){
	ll e=0;
	while(x){
		if(x&1)++e;
		x>>=1;
	}
	return e;
}
int main(){
	n=read(),p=read();
	while(n>0){
		cnt++;
		n-=p;
		if(n<=0)break;
		if(Get(n)<=cnt&&cnt<=n){
			cout<<cnt<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}

```


---

## 作者：Ofnoname (赞：4)

比赛时被这道题打爆了，虽然大体思路非常好想，但是一直没有想出怎么判断`-1`，现在看了官方题解，顿觉极妙。

比较好想的第一步：设拆分为`i`个数，将`p`全部移到左边去，那么左边就是$N-p*i$，右边就是一个可以随意赋值的`i`个2的次幂和，我们知道`i`个2的次幂刚好可以组合出所有二进制下1的个数为`i`的数，而本题里的指数`k`可以重复，那么二进制下1的个数小于`i`的数也都可以组合出来，但是组合不出1个数大于`i`的数。我们枚举这个`i`，看$N-p*i$中1的个数是否小于等于`i`，如果是的话，答案就是`i`。

怎么判断无解呢？原来指数`k`是自然数，最小是$2^0=1$，那么左边最小值就是`i`，所以枚举的上界就是`i <= N - p*i`，超过就无解。

```cpp
#include <cstdio>
#define popcnt __builtin_popcount

int N, p;

int main()
{
	scanf("%d%d", &N, &p);
	for (int i = 0; i <= N - p * i; i++)
		if (i >= popcnt(N - p * i))
		{ 
			printf("%d\n", i);
			return 0;
		}
	puts("-1");
}
```

---

## 作者：超级玛丽王子 (赞：3)

考虑将 $n$ 表示为 $k$ 个 `p-binary` 数，那么必然有一组 $\large\{x_1,x_2,x_3,\cdots,x_k\}$ 使得 $\large n=\sum\limits_{i=1}^k (2^{x_i}+p)$。将所有 $p$ 移项至左边得 $\large n-kp=\sum\limits_{i=1}^k 2^{x_i}$。特别地，$n-kp\ge k$。

考虑 $n-kp$ 的二进制表示。如果其有超过 $k$ 位是 $1$，那么不可能分拆为 $k$ 个 $2$ 的幂。否则我们总能将它分拆为两个较小的 $2^{}$ 的幂。从小到大检查所有的 $k$ 即可。

---

## 作者：傅思维666 (赞：1)


## 题解：

对于一个给定的$n,p$，试求一个最小的$k$，使得存在：
$$
\sum_{i=1}^{k}{(2^{a_i}+p)}
$$
那么对于题意，我们很容易发现，这个数就是多加了$i$个$p$，如果把这$i$个$p$去掉，那么就显然可以把这个数$n-i\times p$进行二进制拆分，拆成很多个二的整数次幂之和，我们要求出这个最小的加数数量。

根据二进制拆分的原则，我们把这个数$n-i\times p$用二进制表示，其中有$1$对应的第$i$位就是$2^{i-1}$（根据位运算的性质）。

那么，我们算出来这个数$n-i\times p$的二进制表示中1的个数，如果这个个数比$i$大，那么就不合法（这是显然的）。并且，如果$n-i\times p<i$，那么也不合法。

那么我们从小到大枚举，判断一下即可。

如有对lowbit运算不太了解的同学，可参考本蒟蒻的这篇博客：

[浅谈lowbit运算](https://www.cnblogs.com/fusiwei/p/11752540.html)

代码：

```cpp
#include<cstdio>
using namespace std;
int n,p,ans,flag;
int lowbit(int x)
{
    int ret=0;
    while(x)
    {
        x-=x&-x;
        ret++;
    }
    return ret;
}
int main()
{
    scanf("%d%d",&n,&p);
    for(int i=1;;i++)
    {
        if(n-i*p<i)
            break;
        if(lowbit(n-i*p)>i)
            continue;
        ans=i;
        flag=1;
        break;
    }
    if(flag)
    {
        printf("%d",ans);
        return 0;
    }
    else
    {
        printf("-1");
        return 0;
    }
}
```



---

## 作者：songhn (赞：1)

### 1.题目大意：
定义一个p-binary数为$2^i+p$ 给定$n$和$p$求出至少需要几个p-binary数可以表示出$n$ 如果不能表示则输出$-1$

### 2.题解：
我们可以按需要几个数来从小到大搜索 假如需要$i$个数 那么

$n = (2^{t_1}+p)+(2^{t_2}+p)+\cdots+(2^{t_i}+p)$

即

$n-i\cdot p=2^{t_1}+2^{t_2}+\cdots+2^{t_i}$

那我们把$n-i\cdot p$用二进制表示 假如二进制表示后1的个数比i大的话 那么肯定是无法表示的 因为这是表示出$n-i\cdot p$最少需要的2的次幂 那表示出$n-i\cdot p$最多需要的2的次幂即每个都是$2^0$那么就需要$n-i\cdot p$个 所以上界就是$n-i\cdot p$ 

因为上界是$n-i\cdot p$ 下界是$bitnum(n-i\cdot p)$(bitnum指二进制中1的个数)只要我们需要的数的个数即$i$在这个范围内即可

即$n-i\cdot p\leq i\leq bitnum(n-i\cdot p)$ 

我们可以循环往上 注意当$n-i\cdot p<i$时 $i$往上上界也永远比$i$小 所以永远不成立 直接break即可

### 3.AC代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=200050;
inline int read()
{
	int x=0,t=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*t;
}
int n,p;
int lowbit(int x){return x&-x;}
int getnum(int x)
{
	int res=0;
	while(x) x-=lowbit(x),res++;
	return res;
}
int main()
{
	cin>>n>>p;
	int flag=0,ans=0;
	for(int i=1;;i++)
	{
		if(n-i*p<i) break;
		if(getnum(n-i*p)>i) continue;
		ans=i;
		flag=1;
		break;
	}
	if(flag) cout<<ans<<endl;
	else puts("-1");
	return 0;
}

```

---

## 作者：big_news (赞：1)

简化一下题意：给定 $p,s$ ，试求得一个最小的 $n$ ，使得存在一组 $\begin{Bmatrix} k_1,k_2,...,k_n \end{Bmatrix}$ ，满足 $\sum\limits_{i=1}^n 2^{k_i} + np = s$ 。

把 $np$ 移到右边去，变形成 $\sum\limits_{i=1}^n 2^{k_i} = s-np$ 。枚举 $n$ 之后， $s-np$ 就变成了一个定值，于是很自然的联想到可以把 $s-np$ 这个数表示成二进制下的和的形式，也就是 $s-np=\sum\limits_{(s-np) \And 2^i} 2^i$ 。

那么这实际上就是一种可行的拆分方案，我们只需要 check 一下 $(s-np)  \And  2^i$ 成立的数量是否恰好等于 $n$ 即可，也就是判断 $s-np$ 在二进制下 $1$  的数量是否恰好等于 $n$ ，这是 $O(\log)$ 的。

但是这并不能涵盖所有的方案。事实上，对于一个正整数 $k$，总有 $2^k=2\times(2^{k-1})=2^{k-1} + 2^{k-1}$ ，也就是说有一些项我们依然可以继续拆分。

考虑 $2^k$ 能拆出的项数的范围：最少只有它自己，也就是一项；最多呢？
考虑把上面拆分的过程看作一棵二叉树，不难发先我们总可以拆出两项，三项，...，直到 $k$ 项。那么对于任意的 $2^k$ ，它总可以被拆分一项，两项，...， $k$ 项，也就是说它“能拆出的项数的范围”是 $[1,k]$ 。

考虑 $s-np=\sum\limits_{(s-np) \And 2^i} 2^i$ 中，后面那些部分能变成多少项。显然，任意 $2^i$ 能拆出的项数的范围是 $[1,i]$ ，那么设 $s-np = 2^{i_1}+2^{i_2}+...+2^{i_k} $ ，其中后面那一部分共有 $k$ 项，即可推出 $s-np$ 能拆出的项数的范围就是 $[k,i_1+i_2+...+i_k]$ 。

于是我们要做的就变成了 check 一下 $n\in [k,i_1+i_2+...+i_k]$ 是否成立，若成立则我们找到了一个可行解。这个判断还是 $O(\log)$ 的，那么只需要在 $10^6$ 内枚举 $n$ 就好了。

然后还有一些小细节，比赛的时候把我卡死了。。。具体看代码。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

#define LL long long

const int N = 1e6; // 枚举的边界，实际上还可以更小

LL n,p,ans = -1;
bool checker(LL u,int k){
    if(!u) return false; // 特判 u 为 0 时一定无解
    int lb = 0,rb = 1,i = 0; // rb 一定要初始化为 1, 因为至少有一项
    while(u){
        if(u & 1) lb++,rb += i;
        u >>= 1,i++;
    }
    return lb <= k && k <= rb;
}
 
int main()
{
    scanf("%I64d%I64d",&n,&p);
    for(int k=1;k<=N;k++){
        LL c = n - 1ll * k * p;
        if(c < 0) break;
        if(checker(c,k)){
            ans = 1ll * k;
            break;
        }
    }
    printf("%I64d",ans);
}
```

---

## 作者：Vidoliga (赞：0)

# 题解

$\text{本题求}n=\sum\limits_{i=1}^m(a_i+p) \text{中}m\text{的最下值}$

$\text{即求}n=\sum\limits_{i=1}^ma_i+mp \text{中}m\text{的最下值}$

$\text{不难变化得到:}n-mp=\sum\limits_{i=1}^ma_i$

$\text{我们只要暴枚m即可}$

$\text{本蒟蒻的代码:}$

```cpp
#include<cstdio>
inline int lowbit(int x){
	return x&(-x);
}
inline int get(int x){
	int ans=0;
	while(x) x-=lowbit(x),ans++;
	return ans;
}
int main(){
	int n,p;
	scanf("%d%d",&n,&p);
	for(int i=1,j=n-p;i<=j;i++,j-=p){
		if(i>=get(j)){
			printf("%d",i);
			return 0;
		}
	}
	putchar('-'),putchar('1');
	return 0;
}
```

$\text{完结撒花,}$ $QwQ$

---

