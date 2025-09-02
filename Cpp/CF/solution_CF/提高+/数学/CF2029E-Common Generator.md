# Common Generator

## 题目描述

For two integers $ x $ and $ y $ ( $ x,y\ge 2 $ ), we will say that $ x $ is a generator of $ y $ if and only if $ x $ can be transformed to $ y $ by performing the following operation some number of times (possibly zero):

- Choose a divisor $ d $ ( $ d\ge 2 $ ) of $ x $ , then increase $ x $ by $ d $ .

For example,

- $ 3 $ is a generator of $ 8 $ since we can perform the following operations: $ 3 \xrightarrow{d = 3} 6 \xrightarrow{d = 2} 8 $ ;
- $ 4 $ is a generator of $ 10 $ since we can perform the following operations: $ 4 \xrightarrow{d = 4} 8 \xrightarrow{d = 2} 10 $ ;
- $ 5 $ is not a generator of $ 6 $ since we cannot transform $ 5 $ into $ 6 $ with the operation above.

Now, Kevin gives you an array $ a $ consisting of $ n $ pairwise distinct integers ( $ a_i\ge 2 $ ).

You have to find an integer $ x\ge 2 $ such that for each $ 1\le i\le n $ , $ x $ is a generator of $ a_i $ , or determine that such an integer does not exist.

## 说明/提示

In the first test case, for $ x=2 $ :

- $ 2 $ is a generator of $ 8 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 4} 8 $ ;
- $ 2 $ is a generator of $ 9 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 3} 9 $ .
- $ 2 $ is a generator of $ 10 $ , since we can perform the following operations: $ 2 \xrightarrow{d = 2} 4 \xrightarrow{d = 2} 6 \xrightarrow{d = 2} 8 \xrightarrow{d = 2} 10 $ .

In the second test case, it can be proven that it is impossible to find a common generator of the four integers.

## 样例 #1

### 输入

```
4
3
8 9 10
4
2 3 4 5
2
147 154
5
3 6 8 25 100000```

### 输出

```
2
-1
7
3```

# 题解

## 作者：_lmh_ (赞：6)

### 引理 1：$2$ 可以生成任意合数。

证明：归纳法。显然 $2$ 可以生成 $4$。

对于更大的合数 $x=pq\ge 6(p,q>1)$，假设 $<x$ 的合数都能被生成。

如果 $2|x$，则 $2|x-2$，可以通过 $x-2(\ge 4)$ 生成 $x$。

否则，$p\ge 3$，可通过 $(p-1)q$ 生成 $x$。

### 引理 2：质数只能被它自己生成。

证明：假设 $0<q<p$ 可以生成质数 $p$，则 $p=q+d(d|q)$，$p=d(1+\frac{q}{d})$，而 $d\ge 2$，所以 $p$ 为合数，矛盾。

### 正解 Part 1：没有质数或有多于一种质数

由引理，没有质数时显然 $2$ 满足条件，多于一种质数无解。

### 引理 3：偶数 $x$ 可以被质数 $p$ 生成的充要条件是 $2p\le x$。

证明：如果 $2p\le x$，那么由 $p$ 生成 $2p$，由 $2p$ 生成 $2p+2,2p+4$ 一直到 $x$。

如果 $2p>x$，但是由 $p$ （一次操作）只能生成 $2p$，且每次操作之后数单调增，所以不可能生成小于 $2p$ 的数，就无法生成 $x$。

### 引理 4：设奇合数 $x$ 的最小质因子为 $p_0$，则它可以被质数 $p$ 生成的充要条件是 $2p\le x-p_0$。

证明：显然 $x-p_0$ 为偶合数。

如果 $2p\le x-p_0$，那么由引理 3，$p$ 可以生成 $x-p_0$，而 $p_0|x$，所以 $p_0|x-p_0$，可以生成 $x$。

如果 $2p>x-p_0$，那么 $p$ 一步只能生成 $2p$，显然其 $\neq x$。

考虑可以通过一步操作生成 $x$ 的数 $y$，说明 $\exist d|y$ 使得 $y+d=x$，也就是说 $\exist d|x$ 使得 $y=x-d$。

但 $p_0$ 为 $x$ 最小质因子，因此 $d\ge p_0$，$y \le x-p_0$。

所以对于任意可以生成 $x$ 的数 $z$，满足 $z\le y \le x-p_0$。

然而 $2p>x-p_0$，说明它无法生成 $x$。

所以，$p$ 无法生成 $x$。

### 正解 Part 2：判断一个质数的合法性

现在序列中有恰好一种质数，我们只需要判断其合法性即可。

根据引理 3 和引理 4，我们实际上只需要将质数 $p$ 和 $\frac{a_i}{2}$ 或是 $\frac{a_i-p_i}{2}$ 比较（其中 $p_i$ 为 $a_i$ 最小质因子），可以用线性筛预处理这个值。

至此，我们在 $O(n+V)$（$V$ 为值域）的时空复杂度内解决了这个问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=400007;
ll T,n,a[N],prime[N],nP,x,rem[N];
bool ok[N];
void initPrime(ll n=N-1){
	ok[1]=1;
	for (int i=2;i<N;++i){
		if (!ok[i]) prime[++nP]=i;
		for (int j=1;j<=nP&&i*prime[j]<=n;++j){
			ll o=i*prime[j];
			ok[o]=1;
			if (o%2==0) rem[o]=o/2;
			else rem[o]=prime[j]*(i-1)/2;
			if (i%prime[j]==0) break;
		}
	}
}
int main(){
	initPrime();
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;x=0;
		for (int i=1;i<=n;++i) cin>>a[i];
		for (int i=1;i<=n;++i) if (!ok[a[i]]){
			if (x==0||x==a[i]) x=a[i];else x=-1;
		}
		if (x==-1){
			cout<<x<<'\n';continue;
		}
		if (x==0){
			cout<<"2\n";continue;
		}
		for (int i=1;i<=n;++i) if (x!=a[i]&&rem[a[i]]<x) x=-1;
		cout<<x<<'\n';
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：5)

CF 第一次过 E + 第一次写出 *2100 + 上分最多的一场，故写题解纪念。

首先看到这题显然是没有任何思路的，不妨打表给出答案，赛时我根据打表找出了规律，这里附上打表代码给各位做参考，该代码的功能是求出 $2\sim N$ 的每个数能被生成的最小数字，可以根据实际情况做更改。

```cpp
#include<bits/stdc++.h>
#define N 100
using namespace std;
int st,f[N+5],b[N+5],vis[N+5];
vector<int>d[N+5];
void dfs(int k)
{
	f[k]=st;
	vis[k]=1;
	for(int now:d[k]) if(k+now<=N&&vis[k+now]==0) dfs(k+now);
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	for(int i=1;i<=N;i++) for(int j=1;j*j<=i;j++)
	{
		if(i%j) continue;
		if(j!=1) d[i].push_back(j);
		if(j*j<i) d[i].push_back(i/j);
	}
	for(int i=2;i<=N;i++) if(!vis[i]) st=i,dfs(i);
	for(int i=2;i<=100;i++) cout<<i<<" "<<f[i]<<"\n";
	return 0;
}
```

如果你想求出 $x$ 能生成的数，那么可以把代码改成这样：

```cpp
#include<bits/stdc++.h>
#define N 100
using namespace std;
int st,f[N+5],b[N+5],vis[N+5];
vector<int>d[N+5];
void dfs(int k)
{
	f[k]=st;
	vis[k]=1;
	for(int now:d[k]) if(k+now<=N&&vis[k+now]==0) dfs(k+now);
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int x;
	for(int i=1;i<=N;i++) for(int j=1;j*j<=i;j++)
	{
		if(i%j) continue;
		if(j!=1) d[i].push_back(j);
		if(j*j<i) d[i].push_back(i/j);
	}
	cin>>x;
	st=x,dfs(x);
	for(int i=2;i<=100;i++) cout<<i<<" "<<f[i]<<"\n";
	return 0;
}
```

根据打表代码一，我们会发现两个结论：

+ 结论一：如果 $x$ 为质数，那么 $x$ 只能被 $x$ 生成。
+ 结论二：$2$ 可以生成除质数外的所有正整数。

接着予以证明：

+ 结论一证明：若 $x$ 为质数，能被 $y$ 生成（$x\neq y$），则 $(x-y)\bmod y=0$。因为 $y\bmod y=0$，所以 $[(x-y)+y]\bmod y=0$，即 $x\bmod y=0$，因为 $x\neq y$，所以 $x$ 不是质数，与条件矛盾，因此 $x$ 只能被 $x$ 生成。

+ 结论二证明：$2$ 可以生成 $2,4,6,8,10\dots$，接着 $6$ 可以生成 $3$ 的倍数，$10$ 又可以生成 $5$ 的倍数，类似于质数筛，$2$ 可以生成除质数外的所有正整数。

这两个结论有什么用呢？我们可以根据这两个结论对答案分类讨论。

+ 如果 $a$ 中出现了超过 $1$ 个质数，那么根据结论一，这两个质数只能被自己生成，因此无解。

+ 如果 $a$ 中没有质数，根据结论二，$2$ 可以生成除质数外的所有正整数，因此直接输出 $2$。

+ 如果 $a$ 中有一个质数 $p$，那么根据结论一，$p$ 只能被自己生成，接着只需要 $p$ 能否生成 $a$ 中的其他数，如果能则输出 $p$，否则输出 $-1$。

那么接下来问题就到了如何判断第三种情况的质数 $p$，能否生成其他数字，利用打表代码二，可以发现在 $[1,2p+1]$
 中只有质数和 $2p$ 可以生成，其他都不行。但是如果你这样想就会 WA #21，考虑 $11$ 这个质数，打表出来后会发现 $25$ 生成不出来。设 $x$ 的最小值因子为 $low_x$，我赛时就想到了若 $y\neq 2p$ 且 $y\neq p$ 且 $y-low_y<p$，$p$ 就无法生成 $y$。但是由于我实力太菜，无法证明，所以就只能直接写结论了。

 
于是用线性筛求出 $low_x$，接着每次遍历一遍数组 $a$ 判断即可。时间复杂度为 $O(n+V)$，其中 $V$ 为 $a$ 的值域。

[code](https://codeforces.com/contest/2029/submission/290751086)

---

## 作者：Xy_top (赞：3)

观察到偶数总有因数 $2$，所以小的偶数一定能转移到大的偶数，那么奇数呢？

观察到奇数不可能有偶数因子，所以奇数进行一步操作后会变回偶数，显然变的偶数越小越优，因为这样可以转移到更多的偶数。

所以说对于每一个奇数 $a_i$，如果选择的 $x$ 不是 $a_i$，

我们可以考虑先将 $x$ 变为偶数（如果它是奇数），然后再进行若干次 $+2$ 得到另一个偶数，最后再一次操作变为奇数。

这就启发我们对于每个奇数 $y$，预处理最大能一步到它的偶数。

对于某种奇数，没有偶数能一步到它，那么 $x$ 只能设为这个奇数，然后枚举一下因数看看 $x$ 能到的最小偶数是谁。

如果有超过两个这种奇数，答案显然为 $-1$。否则答案可以为 $2$。

[record](https://codeforces.com/contest/2029/submission/290748679)

---

## 作者：ny_jerry2 (赞：1)

## 前言
好题，实在是一道很好的数学题。

本文主要参考了 [这篇题解](https://www.luogu.com.cn/article/bj8tcza8)。
## 思路
看到这种题，特别是和因数相关，就可以往质数这一块多想想。

下面要证明一些定理。

>引理 1：对于合数来说，$2$ 永远是满足条件的生成器。
>

>证明：采用归纳法。  
>假设当前数为 $x$，小于 $x$ 的合数都满足条件，那么可以分两种情况：
>
>- 对于偶合数，有：$2 \mid x$，那显然也有 $2 \mid (x-2)$，因此可以从 $x-2$ 转移过来。
>- 对于奇合数，$x$ 也一定可以表示成 $x=pq$ 的形式（其中 $p$ 为最小的质因子）。
>
>     因为 $x$ 为合数，所以 $q>1$（根据因数定理可知）。
>
>     又因为 $x$ 不为偶数，所以不含有偶数因子，那么 $p \ge 3$。所以，$(p-1)q$ 也一定是一个合数。根据前置的条件，$(p-1)q$ 可以被表示，而 $p$ 是质数，所以 $pq$ 即 $x$ 可以表示为 $(p-1)q + p$。因此能被表示。
>
> 得证。

考虑完了合数的情况，再考虑一下质数。

> 引理 2：质数只能由本身来生成。

> 证明：反证法。  
> 如果一个质数 $p$ 可以由 $q$ 生成而来（$q<p$），那么一定有：$p=q+d$，其中 $d \mid q$ 并且 $d > 1$。
>
> 因为 $q=n \times d$，所以：$p = q + d = (n+1)d$。  
> $\because$ $n+1 \ge 2$ 且 $d \ge 2$。  
> $\therefore$ $p$ 是一个合数，矛盾。
>
> 得证。

到这里就有一个整体的思路了。

- 序列中没有质数。根据 **引理 1**，直接输出 $2$ 即可。
- 序列中有不同的质数。根据 **引理 2**，不管选择哪一个都不能满足所有的数，因此无解。
- 序列中有且只有一个质数。还要再讨论一下。

发现只能选这个质数，于是探讨一下选它满不满足其他的合数。

> 引理 3：对于偶合数 $p$，质数 $q$ 能表示它必须满足 $2q \le p$。

> 证明：考虑是否为充分必要条件。
> 
> 充分性：若 $2q \le p$，根据 **引理 2** 可知，$q$ 只能一步到达 $2q$。因为 $2|2q$，所以$2|(p-2q)$。因此后面只要全用 $2$ 就好了。
> 
> 必要性：若 $2q > p$，因为 $q$ 只有先到 $2q$，而此时已经超过了 $p$，后面再操作只会变大，距离 $p$ 越来越远，不可能表示出 $q$。
>
> 因此，该条件是充分必要条件，得证。

接着，考虑一下奇数的情况。

> 引理 4：对于奇合数 $p$，质数 $q$ 能表示它必须满足 $2q \le p - low_p$。其中 $low_p$ 表示 $p$ 的最小质因子。

> 证明：还是考虑充分必要条件。
> 
> 充分性：若 $2q \le p-low_p$，根据 **引理 2** 可知，$q$ 只能一步到达 $2q$。因为 $p$ 为奇数，所以 $low_p$ 也为奇数，所以 $p - low_p$ 为偶数。根据 **引理 3** 可知是合法的。
>
> 必要性：若 $2q > p-low_p$，因为 $q$ 只有先到 $2q$，可知此时 $2q \ne p$，因为奇偶性都不同。考虑能否到达 $p$。
> 
> $\ \ \ \ \ \ \ \ \ \ \ \ \ $ 假设一个数 $x$ 可以**一步**到达 $q$，则跨越的数值 $d=q-x$ 一定为 $x$ 以及 $q$ 的因数。可知此时 $d \ge low_p$，所以当 $x \le p-low_p$ 才满足条件。可是$2q > p-low_p$，矛盾。
> 
> $\ \ \ \ \ \ \ \ \ \ \ \ \ $  因此此时不可能到达 $p$。
>
> 所以该条件为充分必要条件，得证。

因此，只有一个质数的情况利用 **引理3** 以及 **引理4** 判断就好了。

## 代码
```cpp
#include<iostream>
using namespace std;
int t,n;
const int N=5e5+10;
bool v[N];
int p[N],cnt;
int num[N];
void prime(){
	v[1]=1;
	for(int i=2;i<N;i++){
		if(!v[i]){
			p[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*p[j]<N;j++){
			int next=i*p[j];
			v[next]=1;
			if(next&1){
				num[next]=next-p[j];
			}else{
				num[next]=next;
			}
			if(i%p[j]==0){
				break;
			}
		}
	}
}

int a[N];
int main(){
	prime();
	cin>>t;
	while(t--){
		scanf("%d",&n);
		int x=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(x==-1){
				continue;
			}
			if(!v[a[i]]){
				if(!x){
					x=a[i];
				}else{
					x=-1;
				}
			}
		}
		if(x==-1){
			puts("-1");
		}else if(!x){
			puts("2");
		}else{
			for(int i=1;i<=n;i++){
				if(a[i]!=x&&num[a[i]]<2*x){
					x=-1;
					break;
				}
			}
			cout<<x<<endl;
		}
	}
}

```

---

## 作者：Magallan_forever (赞：1)

#### 简要说明题意：

若对于整数 $x,y \geq 2$，定义一次操作为 $x+d=x_1$ ，其中 $d|x$，同理可以得到 $x_2,x_3,...$。若 $k$ 次操作后， $x_k+d = y$，则称 $x$ 是 $y$ 的一个生成器。

现在给出一个数组 $\{a_n\}$，求出 $x$ 使 $x$ 是 $a_i (1 \leq i \leq n)$ 的生成器。

#### 题目分析：

注意到当 $x\leq y,\gcd(x,y)>1$ 时 $x$ 就可以生成 $y$。

证明：设 $c=\gcd(x,y) , x=ca , y=cb$。则 $y=x+c(b-a)$。

因此，只要答案 $x$ 能通过一定操作得到 $x'$ 使得 $\gcd(x',a_i)>1,x' \leq a_i$ 即可。

所以可以先得到无解的一个充分不必要条件：至少存在两个质数，这样无论如何都有至少一个数 $a_i$ 与 $x$ 互质且 $\gcd(x',a_i)>1 \Leftrightarrow x'\geq xa_i$。

然后开始判定有解。

如果 $x$ 与 $a_i$ 互质，那么假设 $a_i$ 的最小质因数是 $p_i$（可以用埃式筛或者欧拉筛很容易地做到），那么只要 $xp_i \leq a_i$ 即可。

从贪心的角度，我们需要让 $x$ 尽可能小，那么如果 $a_i$ 均为合数（这又需要质数筛）， $x$ 直接为 $2$ ，如果有唯一质数那么 $x$ 就为这个质数，然后逐一检验 $xp_i \leq a_i$。

但这样其实有点问题。

考虑 $x=19,a_i=63$。按照这个逻辑，这似乎不成立，但实际上可以 $19 \rightarrow 38 \rightarrow 42 \rightarrow 63$。（我因为这个问题 `wa` 了一次）

也就是说在错解中 $d$ 一直是一个相同的数。但实际上 $d$ 可以变化。可以出现如下变化：

$$x \xrightarrow{d=x} k \xrightarrow{d|k} k_1\xrightarrow{d=p_i} a_i$$

那么可以贪心地制定策略，由于 $k,k_1$ 增大不会导致答案更优，$k,k_1$ 越小越好。

所以 $k=2x , k_1+2t=t_1p_i , k_1 \leq a_i , \gcd(k_1,a_i)>1$ ，那么 $k_1=a_i$ 或 $k_1 \leq a_i-p_i$。

对于偶数，考虑 $2x > a_i$，对于奇数则考虑 $2x>a_i-p_i$，这两种情况确定无解。~~如果这是`OI`赛制估计很容易错~~

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int mark[400001],a[100001];
int main(){
    int T,n,cntp,ans;
    for(register int i=2;i<=400000;++i) if(!mark[i]) for(register int j=(i<<1);j<=400000;j+=i) if(!mark[j]) mark[j]=i;//当时不会写欧拉筛，不过埃式筛同样可以胜任功能:D
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n),cntp=0;
        for(register int i=0;i<n;++i){
            scanf("%d",a+i);
            if(!mark[a[i]]) ++cntp,ans=a[i];
        }
        if(cntp>1) ans=-1;
        else{
            if(!cntp) ans=2;
            for(register int i=0;i<n;++i){
                if(ans^a[i]&&!(a[i]&1)&&(ans<<1)>a[i]){
                    // printf("ans=%d a[i]=%d 0\n",ans,a[i]);
                    ans=-1;
                    break;
                }
                if(ans^a[i]&&(a[i]&1)&&a[i]-mark[a[i]]<(ans<<1)){
                    // printf("ans=%d a[i]=%d 1\n",ans,a[i]);
                    ans=-1;
                    break;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：KaisuoShutong (赞：1)

## CF2029E Common Generator

### 题目描述

称一次操作为，对一个数 $x_0$ 加上其任意大于 $1$ 的因数得到 $x_1$。

若某数 $x$ 做任意次操作可以得到数 $y$，则称 $x$ 生成了 $y$。

现给定 $n$ 个不同的数 $a_i$，求是否存在一个 $x\gt 1$ 使得 $x$ 可以生成所有的 $a_i$。无解输出 `-1`。

$n\le 1\times 10^5$，$a_i\le 4\times 10^5$。

### 解法

显然一个质数只能被其自身生成，而任意合数均可被 $2$ 生成。

那么分类讨论，如果存在两个以上的质数，一定无解；

如果存在一个质数，则需判断其能否生成所有数；

如果不存在质数，$2$ 一定是一个合法解。

下面阐释如何判断某质数 $p$ 能否生成数 $x$。

该质数的第一步只能是 $p\to 2p$，则要求 $x\ge 2p$。此时 $2p$ 已然可以生成所有比它大的偶数。那么若 $x$ 为一个偶数，结束。

否则，考虑最大的可以生成 $x$ 的数。显然其为 $x-p_x$，其中 $p_x$ 为 $x$ 最大的质因数。容易发现这个数一定为一个偶数。因此此时只需 $2p\le x-p_x$ 即可。

由以上讨论，正确性是容易证明的。

时间复杂度 $O(n+V)$。

---

## 作者：Super_Cube (赞：1)

# Solution

首先以 $2$ 作为基底可以生成所有合数，因为如果是偶数那就一直加 $2$，否则让其减去最小质因子，就会变为一个偶数。而质数只能由其本身生成（这个应该不用细说）。

于是若存在两个不同质数，直接无解。若不存在质数，直接输出 $2$。

现在只剩下一个质数 $p$。对其翻倍就能得到因子 $2$，那之后的工作就跟第一段写的差不多，所以若有偶数小于 $2p$ 就会无解，或奇合数减去其最小质因子小于 $2p$ 也会无解。

# Code

```cpp
#include<bits/stdc++.h>
int g[400005];
inline void sieve(int n){
	for(int i=2;i*i<=n;++i)
		if(!g[i])for(int j=i*i;j<=n;j+=i)if(!g[j])g[j]=i;
}
int a[100005];
int T,n,v;
int main(){
	sieve(4e5);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;scanf("%d",&a[i++]));
		v=0;
		for(int i=1;i<=n;++i)
			if(!g[a[i]]){
				if(!v)v=a[i];
				else if(v!=a[i]){
					puts("-1");
					goto nxt;
				}
			}
		if(!v){
			puts("2");
			continue;
		}
		for(int i=1;i<=n;++i){
			if(a[i]==v)continue;
			if(a[i]-(a[i]&1?g[a[i]]:0)<(v<<1)){
				puts("-1");
				goto nxt;
			}
		}
		printf("%d\n",v);
		nxt:;
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：1)

我很喜欢这一场的 E 和 F，有一种独特的 CNOI 味道。

也就是，如果你按部就班一步一步进行推导，写出这一类题目不会太难。

## 解题思路

根据定义，我们可以得到一个基础结论：若 $p$ 能被表示，则所有满足 $\operatorname{gcd}(p,q)\ne 1$ 且 $q\gt p$ 的 $q$ 都能被表示。

观察样例可以得到若干结论，我们尝试对其一一进行证明。

---

### 引理 1：

若原数列中存在质数，且其不是唯一最小的一个数，则无解。

若原数列中存在质数，则你必须选择这个质数，否则无解。

### 证明 1：

考虑到你选取的数一定是你能生成的数中最小的一个，故你不可能选取比 $\min\limits_{1\leq i \leq n} a_i$ 大的数。

根据基础结论，你必须选择某个质数，才能构造该质数，故若存在大于等于两个质数，则无解，否则你必须选择该质数，根据上面的小结论，如果这个质数不是最小值，则无解。

综上所述，引理得证。

---

问题转化为你选取了一个固定的数，对每个数你需要判断该数能否被生成。

考虑你选取了质数 $p$ 之后，下一个能生成的数必定是 $2p$，并且不难发现，小于 $2p$ 的数一定不能被生成，大于等于 $2p$ 的偶合数一定可以被生成。

接下来考虑大于 $2p$ 的奇合数能否被生成。

---

### 引理 2：

记 $l_x$ 表示 $x$ 的最小质因子，一个奇合数 $k$ 能被生成，当且仅当 $k-l_k\geq 2p$。

### 证明 2：

先考虑充分性：若 $k-l_k\geq 2p$ 成立，那么一条成立的生成路径是 $p\rightarrow 2p \rightarrow k-l_k \rightarrow k$。

再考虑必要性：考虑该引理必要性的等价命题：若 $k-l_k\lt 2p$，则奇合数 $k$ 不能被生成。

考虑到生成 $k$ 必须先生成一个数 $t$ 满足：$t\lt k$ 且 $\operatorname{gcd}(t,k)\ne 1$。

尝试证明与之相关的两个小引理：

---

#### 引理 2.1：

对于任意奇合数 $d$，均有：任意能通过一次操作生成 $d$ 的偶数 $t$ 都满足 $t\leq d-l_d$。

#### 证明 2.1：

考虑反证法：假设 $t\gt d-l_d$ 且能通过一次操作生成 $d$ 的偶数 $t$ 存在，则有 $\operatorname{gcd}(t,d)=\operatorname{gcd}(d-t,d)\ne 1$。

$\operatorname{gcd}(d-t,d)\ne 1$ 意味着 $d$ 存在一个小于等于 $d-t$ 的因子，又有 $l_d\gt d-t$，两者矛盾，故假设不成立，引理得证。

#### 引理 2.2：

对于任意奇合数 $d$，均有：任意能通过一次操作生成 $d$ 的奇数 $t$ 都能通过一次操作生成一个偶数 $k$ 满足 $k$ 能通过一次操作生成 $d$。

#### 证明 2.2：

$\operatorname{gcd}(d,t)$ 为奇数，故 $t+\operatorname{gcd}(d,t)$ 是一个偶数，且由于 $\operatorname{gcd}(d,t)$ 是一个奇数，$d-t$ 是一个偶数，$\operatorname{gcd}(d,t)$ 是 $d-t$ 的一个因子，故 $\frac {d-t} {\operatorname{gcd}(d,t)}\geq 2$ 为偶数，由此可得 $t+\operatorname{gcd}(d,t)\lt d$ 为偶数。

由于 ${\operatorname{gcd}(t+\operatorname{gcd}(d,t),d)}=\operatorname{gcd}(d,t)\ne 1$ 且 $t+\operatorname{gcd}(d,t)\leq d$，取 $k=t+\operatorname{gcd}(d,t)$ 一定符合条件，引理得证。

---

一个根据定义可证的命题是：若所有能一步生成 $d$ 的 $t$ 均满足 $t\lt 2p$，则奇合数 $d$ 不能被生成。

根据这两个引理，又可以得知：所有能一步生成 $d$ 的 $t$ 都能在若干步内生成 $d-l_d$，故上面的命题等价于：若 $d-l_d\lt 2p$，则奇合数 $d$ 不能被生成。

由此，必要性得证。

此时充分性以及必要性均得证，原命题得证。

---

这两个命题得证后，就可以对于每一个 $a_i$ 判断其是否能被生成，具体的：若 $a_i\mid 2$ 且 $a_i\geq 2p$ 成立或 $a_i\nmid 2$ 且 $a_i-l_{a_i}\geq 2p$ 成立，则 $a_i$ 可以被生成。

由此我们考虑完了质数个数 $\geq 1$ 的情况，考虑全为合数的情况。

---

### 引理 3：

若 $a$ 全为合数，则 $2$ 是一个解。

### 证明 3：

对于任意合数 $x$，若 $x\mid 2$，则根据引理 2.1 可以得知：若 $x\geq 4$ 则 $x$ 可被表示，而最小的偶合数即为 $4$，故若 $x\mid 2$ 则 $x$ 可被表示。

若 $x\nmid 2$，则根据引理 2.2 可以得知：若 $x-l_x\geq 4$ 则 $x$ 可被表示。

一个结论是：若 $x\mid t$ 且 $t\ne x$，则 $t\leq \frac x 2$，则有 $x-l_x\geq \frac x 2$，故若 $\frac x 2\geq 4$ 则 $x$ 可被表示。

而最小的奇合数即为 $9$，任意大于等于 $9$ 的奇合数均满足 $\frac x 2\geq 4$，故若 $x\nmid 2$ 则 $x$ 可被表示。

综上所述，$2$ 能表示所有合数。

---

至此所有情况都能被判断，结束。

---

## 作者：tai_chi (赞：1)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18538159) 中阅读。

#### 题意

定义对 $x$ 的一次操作为：

- 选择 $x$ 的一个因数 $d$ ($d \ge 2$)，$x \leftarrow x+d$。

称 $x$ 是 $y$ 的生成器当且仅当 $x$ 能通过若干次操作变成 $y$。

给一个数组 $a$ 满足 $a_i \ge 2$，找到一个整数 $x \ge 2$，使得每个 $1 \le i \le n$ 中的 $x$ 都是 $a_i$ 的生成器，或者报告这样的整数不存在。

#### 分析

手玩一下发现几个性质：

- 任何质数都无法从其他数操作得来；
- $2$ 是任何非质数的生成器。

对于性质二有一个简单的说明：偶数只需每次 $x \leftarrow x+2$，非质数奇数可以先减掉最小质因子 $d$，此时原数化归为偶数情况。

于是大体思路如下：

- 有两个或以上质数直接无解；
- 一个质数的答案要么是这个质数，要么无解；
- 没有质数的答案是 $2$。

那我们只要快速判定一个数 $x$ 是否可以被另一个质数 $p$ 生成出来即可。

对于一个偶数 $x$，可以被 $p$ 生成的充要条件是 $x \ge p \times 2$。显然可以构造出 $p \leftarrow p \times 2$，$p \leftarrow p+2 \dotsb$ 的方案以说明。

对于一个奇数 $x$，可以被 $p$ 生成的充要条件是 $x-d(x) \ge p \times 2$，同样可以构造出 $p \leftarrow p \times 2$，$p \leftarrow p+2 \dotsb$，$p \leftarrow p+d(p) \dotsb$ 的方案。

处理质数和一个数的最小质因子可以同时用线性筛预处理。

```cpp
int pr[N],tot,d[N];
bool vis[N];
void init()
{
	vis[1]=1;
	for(int i=2;i<=4e5;i++)
	{
		if(!vis[i]) pr[++tot]=i;
		for(int j=1;j<=tot&&i*pr[j]<=4e5;j++)
		{
			vis[i*pr[j]]=1; d[i*pr[j]]=pr[j];
			if(i%pr[j]==0) break;
		}
	}
}
void solve()
{
	int n; cin>>n;
	vector<int> a(n+5);
	for(int i=1;i<=n;i++) cin>>a[i];
	int cnt=0,p=0;
	for(int i=1;i<=n;i++) if(!vis[a[i]]) cnt++, p=a[i];
	if(cnt>=2) {cout<<-1<<"\n";return;}
	if(cnt==0) {cout<<2<<endl;return;}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==p) continue;
		if(a[i]&1)
		{
			if(a[i]-d[a[i]]<2*p) {cout<<-1<<"\n";return;}
		}
		else
		{
			if(a[i]<2*p) {cout<<-1<<"\n";return;}
		}
	}
	cout<<p<<endl;
}
```

---

