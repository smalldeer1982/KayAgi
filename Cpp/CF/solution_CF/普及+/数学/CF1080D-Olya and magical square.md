# Olya and magical square

## 题目描述

最近 Olya 收到了一个边长为 $2^n$ 的魔法正方形。

她的姐姐认为一个正方形太无趣了，于是要求 Olya 进行 $k$ 次分割操作。

每次操作，Olya 会选择一个边长不为 $1$ 的正方形，并把这个正方形分割为四个等大的小正方形。

Olya 很开心能满足姐姐的请求，但是她自己也要开心。

Olya 是开心的，当且仅当能从左下角到右上角找到一条正方形边长相同，四联通的路径。

请你输出在这 $k$ 次切割后，路径上正方形的边长。

如果不论怎么切都不能找出一条四联通的正方形边长相同的路径，或者这个正方形不能被切割 $k$ 次，输出 `NO`

## 说明/提示

$1 \leq t \leq 10^3$

$1 \leq n \leq 10^9$

$1 \leq k \leq 10^{18}$

## 样例 #1

### 输入

```
3
1 1
2 2
2 12
```

### 输出

```
YES 0
YES 1
NO
```

# 题解

## 作者：Siyuan (赞：13)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Codeforces 1080D](https://codeforces.com/contest/1080/problem/D)

给你一个大小为 $2^n\times 2^n$ 的正方形，每次可以把一个正方形切割成 $4$ 个相同的正方形（田字形切割）。求是否可以切割恰好 $k$ 次，使得最终的图形可以从左下角经过若干相同边长的正方形走到右上角（只能往上和往右走）。如果可以，输出 `YES` 和 $\log_2{\texttt{路径上正方形的边长}}$（任意一个解）；否则输出 `NO`（多组数据）。

数据范围：$1\leqslant T\leqslant 10^3$，$1\leqslant n\leqslant 10^9$，$1\leqslant k\leqslant 10^{18}$

------

## Solution

我们首先可以观察到一个性质：如果 $n>31$，那么我们可以对整个正方形切割一次，再对左上角的正方形随意切割，显然左上角的正方形的能够被切割的次数一定不小于 $10^{18}$。因此当 $n>31$ 时直接输出 `YES` 和 $n-1$ 即可！

对于 $1\leqslant n\leqslant 31$ 的情况，我们枚举路径上的正方形的边长 $2^i$，计算出最少的切割次数 $L$ 和最多的切割次数 $R$，可以证明 $[L,R]$ 这个区间内的所有切割次数都可以被构造出来。只要有任何一个 $i$ 使得 $L\leqslant k\leqslant R$ 的时候则有解；否则无解。

如何计算最少的切割次数：考虑只切割出我们要走的路径的格子。每次只对边缘那一圈的格子切割，第一次需要切割 $1$ 次，第二次需要切割 $3$ 次，第三次需要切割 $7$ 次……因此最少的切割次数为 $\sum_{j=1}^{n-i}2^j-1$。

如何计算最多的切割次数：对于每个边长为 $2^i$ 的正方形预处理出它的最多切割次数，递推式为 $f(i)=4\times f(i-1)+1$，那么当路径上正方形边长为 $2^i$ 时，最多的切割次数为 $f(n)-(2\times 2^{n-i}-1)\times f(i)$ 即 $f(n)-(2^{n-i+1}-1)\times f(i)$（其中 $2\times 2^{n-i}-1$ 表示路径上的正方形个数）。

**时间复杂度**：$O(TN^2)$（其中 $1\leqslant N\leqslant 31$）

------

## Code

```cpp
#include <cstdio>

long long pw[35];

int check(int n,long long k) {
    for(int i=0;i<n;++i) {
        int p=n-i;
        long long l=0;
        for(int j=1;j<=p;++j) l+=(1LL<<j)-1;
        if(l>k) continue;
        long long r=pw[n]-((1LL<<(p+1))-1)*pw[i];
        if(r<k) continue;
        return i;
    }
    return -1;
}
int main() {
    int T;
    for(int i=1;i<=32;++i) pw[i]=4LL*pw[i-1]+1;
    for(scanf("%d",&T);T--;) {
        int n;
        long long k;
        scanf("%d%I64d",&n,&k);
        if(n>31) {
            printf("YES %d\n",n-1);
        } else {
            int ans=check(n,k);
            if(ans<0) puts("NO"); else printf("YES %d\n",ans);
        }
    }
    return 0;
}
```



---

## 作者：ouuan (赞：4)

首先我们可以发现，题目要求的这条通路在哪是无所谓的，所以不如就先从左下角走到右下角，再从右下角走到右上角。

先考虑无法进行 $k$ 次操作的情况，为判断这种情况，需要计算将一个 $2^n\times 2^n$ 的正方形全部变成 $2^{n-i}\times2^{n-i}$ 的正方形需要的操作次数 $a_i=1+4+16+\cdots+4^{i-1}$，可以快速预处理出来。而且 $a_{31}>10^{18}$，所以只用计算 $a_{1..31}$ 。

还需要预处理的是造出一条由 $2^{n-i}\times2^{n-i}$ 的正方形构成的通路需要的最少操作数 $b_i=1+3+7+\cdots+(2^i-1)$。 同样可以快速预处理出来。

那么，是不是只要 $b_i\le k\le a_n$，就可以输出 `YES n-i` 了呢？并不是。造出由 $2^{n-i}\times2^{n-i}$ 的正方形构成的通路进行的操作数是有上限的，实际上就是先造出这条通路，再将除这条通路外的正方形全部分割成 $1\times1$ 的正方形，总共需要的操作数： $a_i+a_{n-i}\times(2^i-1)^2$。其中 $a_i$ 代表先将 $2^n\times 2^n$ 的正方形全部变成 $2^{n-i}\times2^{n-i}$ 的正方形，$a_{n-i}$ 是将每个 $2^{n-i}\times2^{n-i}$ 的正方形分割成 $1\times1$ 的正方形，$(2^i-1)^2$ 是 $2^{n-i}\times2^{n-i}$ 的正方形的个数。

所以..看代码吧：

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

long long i,t,n,k,a[40],b[40];

int main()
{
	cin>>t;
	
	a[1]=1;
	b[1]=2;
	
	for (i=2;i<=32;++i)
	{
		a[i]=a[i-1]*4;
		b[i]=b[i-1]*2;
		a[i-1]+=a[i-2];
		b[i-1]+=b[i-2]-1;
	}
	
	while (t--)
	{
		cin>>n>>k;
		if (n>31)
		{
			cout<<"YES "<<n-1<<endl; //由于a[31]>1e18，n>31时一定可以先分割一次，剩下的操作全部用来分割左上角的正方形
		}
		else if (k>a[n])
		{
			puts("NO");
		}
		else
		{
			for (i=1;i<=n;++i)
			{
				if (k>=b[i]&&k<=a[i]+a[n-i]*((1<<i)-1)*((1<<i)-1))
				{
					break;
				}
			}
			if (i>n)
			{
				puts("NO"); //实际上这种情况有且仅有n=2,k=3
			}
			else
			{
				cout<<"YES "<<n-i<<endl;
			}
		}
	}
	
	return 0;
}
```

---

## 作者：waauto (赞：0)

看上去是一个非常非常简短的解法（迫真）。

我们纯数学玩家怎么你了。

由于这是矩阵，首先你先考虑直接一路上去再去右边。

先切割一次，就可以对着右下角反复切割。

具体来说，切割次数可以写作一下式子。

$$
\sum_{i=0}^{n-2}4^i=\frac{4^{n-1}-1}{3}
$$

其中 $i$ 枚举的是第多少次完全切割。

所以你 $n>31$ 的时候答案就是 $n-1$。

我们考虑 $n\le 31$。

我们首先枚举一个答案 $i$。

首先有个下界切割次数和一个上界切割次数，在这之间显然都是合法的。

对于下界来说，还是考虑枚举每一次切割。

$$
\sum_{j=1}^{n-i} 2^{j}-1=2^{n-i+1}-2-n+i
$$

对于上届来说，考虑全部打碎然后重组就行了。

$$
\sum_{j=0}^{n-1} 4^j -(2^{n-i+1}-1)\times \sum_{j=0}^{i-1}4^i=\frac{4^n-1}{3}-\frac{(4^i-1)\times(2^{n-i+1}-1)}{3}
$$

然后你暴力判断一下就好啦，但是其实这个东西是可以二分达到 $O(\log n)$ 的，但是没必要。

复杂度 $O(Tn)$。

代码贴一下。

```cpp
inline void mian(){
	ll n,k;
	cin>>n>>k;
	if(n>31){
		cout<<"YES "<<n-1<<endl;
		return;
	}
	else {
		F(i,0,n)if(k>=(1ll<<(n-i+1))-2-n+i and k+((1ll<<(n-i+1))-1)*(((1ll<<(2*i))-1)/3)<=((1ll<<(2*n))-1)/3){
				cout<<"YES "<<i<<endl;
				return;
			}
		cout<<"NO\n";
		return;
	}
}
```

---

## 作者：Ouaoan (赞：0)

题目：[Olya and magical square](https://www.luogu.org/problemnew/show/CF1080D)

---

[更好阅读体验？](https://blog.csdn.net/rabbit_ZAR/article/details/85277703)

---

思路：

首先，n>31时可以不用考虑，因为只需要划分左上角或右下角的正方形就足够了。

令$f[i]$表示把大长方形$2^n$划分成全部是边长为$2^{n-i}$小正方形的划分次数。

$g[i]$表示形成边长$2^{n-i}$通路需要的最小划分数。

$f[i]=2^{i*2-2}+f[i-1]$

$g[i]=2^i-1+g[i-1]$

所以所求的$k$需满足

$k>=g[i]$

且

$k<=f[i]+f[n-i]*(2^n-1)*(2^n-1)$

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long 
#define readll(x) scanf("%I64d",&x)
#define m 31
#define maxn 31

ll n,k;
ll f[maxn+5],g[maxn+5];

void init() {
	f[1]=g[1]=1;
	for(int i=2;i<=m;i++) {
		f[i]=(1LL<<i*2-2)+f[i-1];
		g[i]=(1LL<<i)-1+g[i-1];
	}
}

int main() {
	init();
	
	ll T;
	readll(T);
	while(T--) {
		readll(n),readll(k);
		if(n>m) { printf("YES\n%I64d\n",n-1); continue; }
		int flg=-1;
		for(int i=0;i<=n;i++) {
			if(k>=g[i]&&k<=f[i]+f[n-i]*((1LL<<i)-1)*((1LL<<i)-1)) {flg=i;break;}
		}
		if(~flg) printf("YES\n%I64d\n",n-flg);
		else printf("NO\n");
	}
	
	return 0;
}
```

---

