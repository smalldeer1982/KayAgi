# Deleting Numbers

## 题目描述

This is an interactive problem.

There is an unknown integer $ x $ ( $ 1\le x\le n $ ). You want to find $ x $ .

At first, you have a set of integers $ \{1, 2, \ldots, n\} $ . You can perform the following operations no more than $ 10000 $ times:

- A $ a $ : find how many numbers are multiples of $ a $ in the current set.
- B $ a $ : find how many numbers are multiples of $ a $ in this set, and then delete all multiples of $ a $ , but $ x $ will never be deleted (even if it is a multiple of $ a $ ). In this operation, $ a $ must be greater than $ 1 $ .
- C $ a $ : it means that you know that $ x=a $ . This operation can be only performed once.

Remember that in the operation of type B $ a>1 $ must hold.

Write a program, that will find the value of $ x $ .

## 说明/提示

Note that to make the sample more clear, we added extra empty lines. You shouldn't print any extra empty lines during the interaction process.

In the first test $ n=10 $ and $ x=4 $ .

Initially the set is: $ \{1,2,3,4,5,6,7,8,9,10\} $ .

In the first operation, you ask how many numbers are multiples of $ 4 $ and delete them. The answer is $ 2 $ because there are two numbers divisible by $ 4 $ : $ \{4,8\} $ . $ 8 $ will be deleted but $ 4 $ won't, because the number $ x $ will never be deleted. Now the set is $ \{1,2,3,4,5,6,7,9,10\} $ .

In the second operation, you ask how many numbers are multiples of $ 2 $ . The answer is $ 4 $ because there are four numbers divisible by $ 2 $ : $ \{2,4,6,10\} $ .

In the third operation, you ask how many numbers are multiples of $ 8 $ . The answer is $ 0 $ because there isn't any number divisible by $ 8 $ in the current set.

In the fourth operation, you know that $ x=4 $ , which is the right answer.

## 样例 #1

### 输入

```
10

2

4

0```

### 输出

```
B 4

A 2

A 8

C 4```

# 题解

## 作者：钓鱼王子 (赞：20)

出题人题解：

如果我们知道 $x$ 的所有质因数，可以用暴力枚举幂次找到答案。

可以对于每一个质数 $p$ 做一次询问 $B~p$，若得到答案和没有 $x$ 的答案不同，则说明 $x$ 有 $p$ 这一个质因子。

通过这样的方法，我们可以找到除最小质因子以外的质因子。

对于最小的质因子，可以采用分块，令 $m$ 为质数个数，每隔 $\sqrt m$ 次做一次 $A~1$ 询问，检查最小质因子是否在区间里，如果在，则扫描一遍区间对于每一个质因数找一次 $A~p$，即可得到所有质因数。

总操作次数：$m+2\sqrt m+\log n$，时间复杂度：$O(n\log n)$。

自我评价：是一道很不错的题目！

```
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
bool vis[100002];
int pri[100002],tot,n,x,sum,ans,ia;
signed main(){
	srand(19260817); 
	scanf("%lld",&n);
	for(re int i=2; i<=n; ++i) {
		if(!vis[i]) {
			pri[++tot]=i;
			if(i<=sqrt(n))
			for(re int j=i*i; j<=n; j+=i)vis[j]=1;
			}
	}
	memset(vis,0,sizeof(vis));
	re int k=sqrt(tot);sum=n;ans=1;
	for(re int i=1;i<=tot;++i){
	    if(i>=k&&ans*pri[i-k+1]>n)break;
		printf("B %lld",pri[i]);cout<<endl;
		re int num=0;
		for(re int j=pri[i];j<=n;j+=pri[i]){
			if(!vis[j]){
				++num;--sum;
				vis[j]=1;
			}
		}
		scanf("%lld",&x);
		if(x!=num){
			for(re int kk=pri[i];kk<=n;kk*=pri[i]){
					printf("A %lld",kk);cout<<endl;
					scanf("%lld",&x);
					if(x)ans*=pri[i];
					else break;
			}
		}
		if((i==tot||i%k==0)&&!ia){
			printf("A 1");cout<<endl;
			scanf("%lld",&x);
			if(x!=sum){
				for(re int j=i-k+1;j<=i;++j){
					for(re int kk=pri[j];kk<=n;kk*=pri[j]){
						printf("A %lld",kk);cout<<endl;
						scanf("%lld",&x);
						if(x)ans*=pri[j],ia=1;
						else break;
					}
					if(ia)break;
				}
			}
		}
	}
	printf("C %lld",ans);cout<<endl;
}
```


---

## 作者：duyi (赞：10)

[噜啦噜啦咧噜啦噜啦咧的阅读体验](https://www.cnblogs.com/dysyn1314/p/13963433.html)

# CF1406E Deleting Numbers

## 题目大意

交互题。

有一个未知的整数 $x$ ($1\leq x\leq n$)，你需要通过交互找出它。

初始时，交互库会告诉你 $n$。

有一个集合 $\{1,2,\dots ,n\}$。你可以进行不超过 $10^4$ 次操作。每次操作可以是如下三种之一：

- $\text{A }a$：向交互库询问，当前集合里有多少数是 $a$ 的倍数。
- $\text{B }a$：向交互库询问，当前集合里有多少数是 $a$ 的倍数。然后将所有 $a$ 的倍数删去。特别地：$x$ 将不会被删去，即使它是 $a$ 的倍数。此操作必须保证 $a > 1$。
- $\text{C }a$：向交互库报告你找出的 $x$。

请在规定操作次数内求出 $x$。

数据范围：$1\leq n\leq 10^5$。

## 本题题解

考虑一种暴力做法。枚举 $1\dots n$ 中每个质数 $p$，再枚举 $p$ 在 $n$ 以下的所有次幂 $p^k$。先用 $\text{B}$ 操作删除 $p^k$ 的倍数，再用 $\text{A}$ 操作查询集合里是否仍有 $p^k$ 的倍数。若有，说明 $x$ 是 $p^k$ 的倍数。这样，我们可以知道每个质数在 $x$ 里的最大次幂是多少，根据唯一分解定理，我们也就确定了 $x$。

设 $\pi(n)$ 为 $1\dots n$ 中的质数数量，$\tau(n)$ 为 $1\dots n$ 中的质数的幂的数量。打表发现，$\pi(10^5)=9592,\tau(10^5)=9700$。上述做法，需要 $2\tau(n)+1$ 次操作（最后一次操作是报告答案），无法通过本题。

一个小优化是，对每个质数 $p$，先用 $\text{B}$ 操作删除所有 $p$ 的倍数，再依次询问所有次幂。操作次数优化为 $\pi(n)+\tau(n)+1$，但仍无法通过本题。

有一个经典的技巧是，把质数分为 $\leq \sqrt{n}$ 的“小质数”和 $> \sqrt{n}$ 的“大质数”。小质数总共只有 $\pi(\sqrt{n})$ 个。而大质数在任何 $x$ 里至多只有 $1$ 个。

先用 $\pi(\sqrt{n})+\tau(\sqrt{n})\leq 238$ 次操作，求出 $x$ 中所有小质因子及其次幂。设 $x$ 的小质因子部分为 $x_{\text{small}}$。此时，集合里还剩下 $1$、$x$、以及所有大质数。我们要确定 $x$ 里还剩下的那 $1$ 个大质因子是谁（或者根本没有大质因子）。

在前面的朴素做法里，我们实际对每个大质数用了 $2$ 次询问，这样太多了。考虑减小这个次数。分两种情况：

- 如果 $x_{\text{small}} > 1$：我们对每个大质数 $p$，直接用 $\text{A}$ 操作询问 $p\times x_{\text{small}}$。如果结果为 $1$，说明 $x$ 就等于 $p\times x_{\text{small}}$（不然的话，这个数此时应该已经被删了）；如果结果为 $0$，说明 $p$ 不是 $x$ 的大质因子。这样，对每个大质因子只需要 $1$ 次操作。找出大质因子所需的操作次数等于大质因子的数量，为：$\pi(n)-\pi(\sqrt{n})$。加上小质数的部分，以及报告答案的操作，总次数为 $\pi(\sqrt{n})+\tau(\sqrt{n})+(\pi(n)-\pi(\sqrt{n}))+1=\pi(n)+\tau(\sqrt{n})+1\leq 9766$。
- 如果 $x_{\text{small}}=1$：此时 $p\times x_{\text{small}}$ 就是大质数 $p$ 本身，它本来就应该在集合里，所以直接询问是没有意义的。这种情况下，集合里只剩 $1$ 和大质数（因为 $x$ 本身也是 $1$ 或大质数）。考虑大质数序列分块。每块里，先依次用 $\text{B}$ 操作将本块的大质数全部删除，然后用 $\text{A}$ 操作对 $1$ 进行一次询问（也就是询问整个集合剩余的数的数量）。如果发现集合大小减少的量，少于我们删除的量，说明 $x$ 就在本块里，我们枚举本块中的数，依次询问。这样，设块的大小为 $S$，则找出大质数所需的操作次数为：$\pi(n)-\pi(\sqrt{n})+\lceil\frac{\pi(n)-\pi(\sqrt{n})}{B}\rceil+B$。取 $B = \lfloor\sqrt{\pi(n)-\pi(\sqrt{n})}\rfloor = 97$ 时，这部分的最大操作次数为 $9723$。加上小质数的部分，以及报告答案的操作，最大总次数为 $9962$。可以通过本题。

## 参考代码

[勇敢向前进，前进有奖品！！！](https://www.cnblogs.com/dysyn1314/p/13963433.html)



---

## 作者：zhoukangyang (赞：8)

## 蒟蒻语
蒟蒻这次 $CF$ 又双叒叕掉分了，$C$ 都没有调出来。![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)

还好再最后 $10$ 秒钟调了下 $E$ 块长 (块长 $100$ => $98$),才没有掉得那么惨。
## 蒟蒻解
$100000$ 里总共有 $9592$ 个质数。

(下文 $p_i$ 表示第 $i$ 个质数)

首先 $x$ 大于 $\sqrt n$ 的质因数最多一个。

对于大于 $\sqrt n$ 的质数数可以进行分块, 块长为 $B$。

每次把一个块里面的质数删完(`B p[i]`), 然后删完之后看看删掉的数的总数是否等于 `A 1` 答案的变化量。如果不相等，那么说明 $x$ 一定有一个质因数处于这个块内，暴力 `A p[i]` 判断是否为 $1$ 就行了。如果 `A p[i]` 为 $1$, 那么就说明 $x$ 大与 $\sqrt n$ 的质因数就是 $p_i$。

那么小于 $\sqrt n$ 的质数就很好弄了， 直接先删这个质数的倍数，然后一个个暴力判 $x$ 最多能整除该质数的几次方就好了。

## 蒟蒻码

不懂的看丑陋无比的代码吧

```cpp
#include<bits/stdc++.h>
#define N 100010
#define B 98
using namespace std;
int Ans = 1;
bool Prime[N];
int tot, p[N];
void xxs(int x) {
	for(int i = 2; i <= x; i++) { 
		if(!Prime[i]) p[++tot] = i;
		for(int j = 1; p[j] * i <= x && j <= tot; j++) {
			Prime[p[j] * i] = 1;
			if(i % p[j] == 0) break;
		} 
	} 
} 
int n, tt, maxn;
void get(int x) {
	int now = 1;
	printf("B %d\n", x);
	fflush(stdout);
	scanf("%d", &tt);
	while(1) {
		now *= x;
		if(now > n) break;
		printf("A %d\n", now);
		fflush(stdout);
		scanf("%d", &tt);
		if(tt == 0) break;
		Ans *= x;
	}
}
int main() {
	scanf("%d", &n);
	xxs(n);
	for(int i = 1; i <= tot; i++) if(p[i] <= sqrt(n)) maxn = i;
	int ssss = n, L = maxn, R = tot;
	for(int i = 1; i <= B; i++) { 
		int L = (i - 1) * B + 1, R = min(i * B, tot);
		for(int j = L; j <= R; j++) {
			if(j <= maxn) continue;
			printf("B %d\n", p[j]);
			fflush(stdout);
			scanf("%d", &tt);
			ssss -= tt;
		}
		printf("A 1\n");
		fflush(stdout);
		scanf("%d", &tt);
		if(ssss != tt) {
			for(int j = L; j <= R; j++) {
				if(j <= maxn) continue;
				
				printf("A %d\n", p[j]);
				fflush(stdout);
				scanf("%d", &tt);
				
				if(tt) {
					Ans = p[j];
					break;
				}
			}
			break;
		}
		if(R == tot) break;
	}
	
	for(int i = 1; i <= maxn; i++) get(p[i]);
	
	printf("C %d\n", Ans);
	fflush(stdout);
	return 0;
}
```

---

## 作者：honglan0301 (赞：7)

## 题意简述
原题链接：[CF1406E](https://www.luogu.com.cn/problem/CF1406E)  

交互库给定一个正整数 $n(n\leq 10^5)$。  
  
我们有一个正整数集合 $S=\{a|a\leq n\}$, 需要在至多 $10^4$ 次操作后找出未知数 $x(x\leq n)$ 的值。我们可以进行以下的几种操作。
- 输出 $A\ a:$ 询问集合 $S$ 中有多少个数是 $a$ 的倍数。

- 输出 $B\ a:$ 询问集合 $S$ 中有多少个数是 $a$ 的倍数，并在之后删去所有 $a$ 的倍数。**注意，要找的未知数不会被删除**。

- 输出 $C\ a:$ 给出答案 $x=a$ 。

## 题目分析
注意到 $10^5$ 以内的质数共有 $9592$ 个，与我们操作数的上限很接近。于是对于每个质数先删再问的暴力做法最多要 $9592\cdot 2+1=19185$ 次操作，不满足要求。我们下面来优化这个做法，尽量详细一些。

------------

我们考虑首先判断未知数 $x$ 是否为质数。  
  
因为任何一个合数 $m$ 必然含有一个 $\leq\sqrt m$ 的质因数，所以我们先处理 $\leq\sqrt n$ 的质数，对于每个质数 $p$ 先询问 $B\ p$, 再询问 $A\ p$。  
  
此时如果得到的答案为 $1$ 则说明 $p$ 是未知数 $x$ 的因数，那么继续询问 $A\ p^2$......$ A\ p^k$ 直到答案为 $0$ 为止。记录这些因数。  
  
之后就出现了两种情况：
1. 在 $\leq\sqrt n$ 的质数中找到了 $x$ 的因数。这说明 $x$ 要么是已经被找到的一个质数，要么是一个合数  

   这时的集合 $S$ 中只剩下了所有 $>\sqrt n$ 的质数以及 $x$, 所以我们只需要对每个 $>\sqrt n$ 的质数 $p$ 询问 $A\ p$, 如果得到的答案为 $2$ 则说明 $p$ 是 $x$ 的因数，而又因为 $p^2>n$ 所以只需记录 $p$。  
   
   遍历之后输出答案，经过计算，在这种情况下我们最多只会进行 $65\cdot2+9527+1=9658$ 次操作，符合题目要求。

1. 在 $\leq\sqrt n$ 的质数中没有找到 $x$ 的因数。这说明 $x$ 要么是 $1$, 要么是一个 $>n$ 的质数。  

   这时我们注意到题目要求的特殊处：进行 $A\ a$ 操作时，$a$ 的值**可以为 $1$。**  

   题解大部分都在这里用了分块的做法，但我并没有想到，而且二分的询问数量略优于分块，所以介绍这个类似二分的做法。  

   我们把 $>\sqrt n$ 的质数标号为 $p_1,p_2,...,p_k$, 只需要先删掉 $p_1...p_{k/2}$, 之后进行操作 $A$ 询问 $A\ 1$。如果得到的答案 $ans \neq k-k/2+1$, 则说明未知数 $x$ 就在被删掉的 $p$ 里面，于是对刚才删掉的每个 $p$ 再进行 $B\ p$ 操作即可找出答案；否则就对 $p_{k/2+1},...,p_k$ 继续进行二分。  

   特殊地，如果遍历完所有质数后依然没有找到 $x$ 那么说明 $x=1$, 输出答案即可。经过计算，这种情况里我们最多也只进行 $65\cdot 2+9527+\log9527+1+1=9673$ 次操作，同样满足题目要求。

---
## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n,ans,q,xnow=1,cntp,prime[10005];//xnow表示未知数的答案，cntp为质数个数 
bool prm[100005];
void ask(int tag,int x)//询问 
{
	cout<<(char)(tag+'A'-1)<<" "<<x<<endl;
	fflush(stdout);
	cin>>ans;
}
void init()//线性筛1~n的质数 
{
	memset(prm,1,sizeof(prm));
	prm[1]=0;
	for(int i=2;i<=n;i++)
	{
		if(prm[i])
		{
			cntp++;
			prime[cntp]=i;
		}
		for(int j=1;j<=cntp&&i*prime[j]<=n;j++)
		{
			prm[prime[j]*i]=0;
			if(!i%prime[j])
			{
				break;
			}
		}
	}
}
void solve1()//先处理小于等于根号n的质数 
{
	for(int i=1;i<=cntp;i++)
	{
		if(prime[i]*prime[i]>n)
		{
			q=i-1;
			break;
		}
		int nowask=prime[i];
		ask(2,nowask);
		ask(1,nowask); 
		while(ans==1)//处理它的k次幂 
		{
			nowask*=prime[i];
			if(nowask>n)
			{
				break;
			}
			ask(1,nowask);
		}
		xnow*=nowask/prime[i];
	}
}
void solve2()//在1~根号n中找到了x的因数 
{
	for(int i=q+1;i<=cntp;i++)
	{
		if(xnow*prime[i]>n)//很显然的判断，优化效率 
		{
			break;
		}
		ask(1,prime[i]);
		if(ans==2)
		{
			xnow*=prime[i];
		}
	}
}
void solve3()//x为1或者大质数 
{
	int l=q+1;
	while(l<=cntp)
	{
		int mid=(l+cntp)/2;
		for(int i=l;i<=mid;i++)
		{
			ask(2,prime[i]);
		}
		ask(1,1);
		if(ans==cntp-mid+1)
		{
			l=mid+1;
		}
		else
		{
			for(int i=l;i<=mid;i++)
			{
				ask(1,prime[i]);
				if(ans==1)//判断，找到大质数后立即返回 
				{
					xnow*=prime[i];
					return;
				}
			}
		}
	}
}
void solve()
{
	solve1();
	if(xnow!=1)
	{
		solve2();
	}
	else
	{
		solve3();
	}
	cout<<"C "<<xnow<<endl;
}
int main()
{
	cin>>n;
	init();
	solve();
}//目前最优解
```
如有问题，欢迎指出。

---

## 作者：123456zmy (赞：5)

题意：  
给你一个集合，其中元素为 $1$~$n$ 中所有的整数，你可以执行以下操作以得到 $x$ 的值：

- `A a`：查询目前集合中为 $a$ 的倍数的数的数量。
- `B a`：（$a>1$）输出 $A$ 操作的结果，并将这些数删去，特殊的，$x$ 不会被删去。
- `C a`：提交答案，$x=a$

你需要通过不超过 $10000$ 次操作得到 $x$ 的值。
___
首先可以想到一个比较显然的方法，对于每个质数 $p_i$ 删一遍再查是否还有，如果有，$p_i$ 就是 $x$ 的质因子，再查询 $p_i^2,p_i^3...,p_i^j$ 直到查询 $p_i^j$ 的结果为 $0$ 时将答案乘 $p_i^{j-1}$。但是 $10^5$ 以内的质数大概有 $9500$ 个，直接做会超过操作限制，考虑对其进行优化。

首先，我们可以用 $\sqrt{n}$ 之内的所有质数将所有合数删去，如果 $x$ 有这些质因子可以顺便将其计入答案。对于 $x$ 不存在 $\sqrt{n}$ 以内的质因子的情况，将质数进行分块，一次删 $100$ 个，再查询被删去的数是否为 $100$ 个，如果不是，那么其中一定有 $x$ 的质因子，就可以在其中暴力查每个数，查到后直接计入答案输出并结束；
对于 $x$ 存在 $\sqrt{n}$ 以内的质因子的情况就对于每个质因子 $p_i$ 查询是否有 $p_i\cdot ans$，如果有，这个数就是答案。
___
代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p[10001],pn,ans=1;
bitset<100001>p1;
int qa(int i)//查询 A i
{
	int tmp;
	printf("A %lld\n",i);
	cout<<flush;
	scanf("%lld",&tmp);
	return tmp;
}
int qb(int i)//查询 B i
{
	int tmp;
	printf("B %lld\n",i);
	cout<<flush;
	scanf("%lld",&tmp);
	return tmp;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=2;i<=n;i++)if(!p1[i])//筛质数
	{
		p[++pn]=i;
		for(int j=i*i;j<=n;j+=i)p1[j]=1;
	}
	if(pn<=4980)//暴力
	{
		for(int i=1;i<=pn;i++)
		{
			int tmp,tmp1;
			qb(p[i]),tmp1=qa(p[i]);
			tmp=p[i];
			while(tmp1&&(tmp*=p[i])<=n)tmp1=qa(tmp);
			ans=ans*tmp/p[i];
		}
		printf("C %lld\n",ans);
		cout<<flush;
		return 0;
	}
	else
	{
		for(int i=1;i<=100;i++)//sqrt(n)以内的质数
		{
			int tmp,tmp1;
			qb(p[i]);
			tmp1=qa(p[i]);
			tmp=p[i];
			while(tmp1&&(tmp*=p[i])<=n)tmp1=qa(tmp);
			ans=ans*tmp/p[i];
		}
		if(ans>1)//存在 sqrt(n) 以内的质因子的情况
		{
			for(int j=101;j<=pn&&p[j]*ans<=n;j++)if(qb(p[j]*ans))ans*=p[j];
			printf("C %lld",ans);
			cout<<flush;
			return 0;
		}
		else//不存在 sqrt(n) 以内的质因子的情况
		{
			int tmp1,tmp2=qa(1);
			for(int i=1;i<=(pn-1)/100+1;i++)//分块
			{
				for(int j=1+i*100;j<=min(i*100+100,pn);j++)qb(p[j]);
				tmp1=qa(1);
				if(tmp2-tmp1!=100)
				{
					for(int j=1+i*100;j<=min(i*100+100,pn);j++)if(qa(p[j])==1)
					{
						ans*=p[j];
						break;
					}
					printf("C %lld\n",ans);
					cout<<flush;
					return 0;
				}
				tmp2=tmp1;
			}
		}
	}
	printf("C %lld\n",ans);
	cout<<flush;
	return 0;
}
```

---

## 作者：chenxia25 (赞：3)

这是钓鱼王子出的好题哦~

> ### [洛谷题目页面传送门]( https://www.luogu.com.cn/problem/CF1406E ) & [CF 题目页面传送门]( https://codeforces.com/contest/1406/problem/E )
>
> 本题为交互题。给定 $n$，初始时有 $A=[1,n]\cap \mathbb Z$。你有 $3$ 种操作：
>
> 1. 查询 $A$ 中有多少个 $a$ 的倍数（$a\in [1,n]$）；
> 2. 查询 $A$ 中有多少个 $a$ 的倍数（$a\in[2,n]$），并将 $A$ 中所有 $a$ 的倍数删去，特殊地，如果 $x$ 是 $a$ 的倍数则不删；
> 3. 得出答案 $a$，操作之后立即结束。
>
> 你需要在不超过 $10^4$ 次操作内猜出某个预先设定好的 $x\in A$。
>
> $n\in\left[2,10^5\right]$。

思路在于，通过操作 $1$ 和操作 $2$ 的配合，实现查询 $x$ 是否是 $a$ 的倍数。

不难想到尝试将 $x$ 分解质因数~~，根据弱智的唯一分解定理可以确定 $x$~~。

最 naive 的想法是每个质数的幂都试一遍。打个表发现 $\pi(n)$ 大概是 $9500+$，然后质数的幂大概是 $9700$ 左右个。你可能会说，噫，好，这场 div. 2 我阿克了！哦上帝，瞧瞧这天真的声音。注意到操作 $2$ 是先返回结果再删除的，也就是说它的返回结果是个幌子，你想知道 $[a\mid x]$ 必须要先 $2$ 再 $1$，$2$ 步走。

想到寿司晚宴那题的一个结论：将质数分成小质数和大质数，则每个数最多含有一个大质因子。

那么先将小质因子随便毛搞搞，我们设 $\tau(m)$ 表示 $m$ 以内质数的幂的个数，那么是 $2\tau(\sqrt n)$ 步的。实际上可以进一步优化，对于每个质数，先将它给 $2$ 了，然后每个幂就可以直接查了。这样是 $\pi(\sqrt n)+\tau(\sqrt n)$ 的。别看这一步优化微不足道，其实她能决定你是否 AC。

现在把质因数分解式里的小质因子部分已经分解出来了，并且 $A$ 里显然只剩下 $1$ 和 $x$ 和所有大质数。接下来的任务就是要找出 $x$ 是否有大质因子，如果有的话是谁。

需要分出两种情况：

1. 小质因子部分 $>1$。那么显然 $x$ 是不属于那个大质数集的。那还怕个鬼啊，直接检查所有的大质数乘以小质因子部分是否剩一个数，剩的话大质因子就是他了乘上去，否则没有；
2. 小质因子部分 $=1$。此时就需要害怕了，因为你「检查所有的大质数乘以小质因子部分是否剩一个数」的话，那你任何一次检查结果都是「是」，就无语了。而此时问题变得更加简单，剩下来的集合就是 $1$ 和所有大质数，而你可以确定 $x$ 就在里面。考虑对大质数序列分块。每块整体删一下，然后如果集合大小减少数量不对劲就说明 $x$ 一定在这块里面，集中精力搞。由于块大小不大，可以直接逐个用操作 $1$ 排查。总操作次数大约为 $\pi(\sqrt n)+\tau(\sqrt n)+(\pi(n)-\pi(\sqrt n))+2\sqrt{\pi(n)-\pi(\sqrt n)}=\tau(\sqrt n)+\pi(n)+2\sqrt{\pi(n)-\pi(\sqrt n)}$，卡的死死的，出题人真是毒瘤。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
bool ispr(int x){
	if(x<2)return false;
	for(int i=2;i*i<=x;i++)if(x%i==0)return false;
	return true;
}
int A(int x){
	printf("A %d\n",x),fflush(stdout);
	cin>>x;return x;
}
int B(int x){
	printf("B %d\n",x);fflush(stdout);
	cin>>x;return x;
}
void C(int x){printf("C %d\n",x);fflush(stdout);exit(0);}
void mian(){
	int n;
	cin>>n;
	if(n==1)C(1);
	vector<int> pr;
	for(int i=2;i<=n;i++)if(ispr(i))pr.pb(i);
	int x=1,lim=sqrt(n);
	for(int i=0;pr[i]<=lim;i++){
		B(pr[i]);
		int now=1;
		while(now*pr[i]<=n)now*=pr[i];
		while(now>1){
			if(A(now)==1){x*=now;break;}
			now/=pr[i];
		}
	}
	vector<int> v;
	for(int i=0;i<pr.size();i++)if(pr[i]>lim)v.pb(pr[i]);
	if(x==1){
		int now=A(1);
		for(int i=0;i<v.size();i+=100){
			for(int j=i;j<i+100&&j<v.size();j++)B(v[j]);
			int res=A(1);
			if(now-res==min(i+100,int(v.size()))-i)now=res;
			else{
				for(int j=i;j<i+100&&j<v.size();j++)if(A(v[j])==1){x=v[j];break;}
				break;
			}
		}
	}
	else{
		for(int i=0;i<v.size();i++)if(1ll*x*v[i]<=n&&A(x*v[i])==1){x*=v[i];break;}
	}
	C(x);
}
int main(){
	int testnum=1;
//	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：pitiless0514 (赞：2)

## 题目大意

这是一道交互题。

已知 $n$，有一个未知数 $x$ （$1 \le x \le n$ ），你需要求出 $x$ 的值。

有一个集合 $S = \{1,2,\dots ,n\}$ 。你可以进行不超过 $10^4$ 次操作。每次操作可以是如下三种之一：

$\texttt{A:A a}$，表示求出 $S$ 中 $a$ 的倍数的个数 （$1\le a\le n$）。

$\texttt{B:B a}$，表示求出 $S$ 中 $a$ 的倍数的个数并将这些数从 $S$ 中删去（$x$ 是不会被删掉的） （$2\le a \le n$）。

$\texttt{C:C a}$，表示你知道了 $x = a$ （$1\le a \le n$）。

所有的 $a$ 均为整数。

## $\texttt{solution}$

交互题考虑分析操作和规模，对于 $\texttt{B}$ 操作，我们发现如果 $a$ 的倍数中有 $x$，那么最后删除的时候是不会删除 $x$ 的，但是我们又可以使用 $\texttt{A}$ 操作来得到集合中 $a$ 的倍数。

如果 $x$ 不是 $a$ 的倍数，那么使用 $\texttt{B}$ 操作之后再使用一次 $\texttt{A}$ 操作得到的回复应该是 $0$，否则为 $1$。

因此，我们有了一种暴力的思路，我们考虑对于 $10^5$ 内所有质数，都执行一遍上面的操作，然后我们可以确定出 $x$ 是由哪些质因子构成的，然后最后我们再询问这些质因子的次幂即可。

那么，这么做的操作次数为多少呢？

$10^5$ 范围内的质数有 $9592$ 个，我们至少对每个质数都执行了两遍操作，然后还有最后找出数 $x$ 又需要一些次数，超出规定的 $10^4$ 操作次数。

考虑优化我们的交互策略，对质数进行根号分治。

将大于 $316$ 的质数和小于 $316$ 的质数分别进行处理。

对于大于 $316$ 的质数，任何 $x$ 都最多只会有一个 $1$ 这么的质因数出现，否则就超出了值域 $10^5$。

对于小于 $316$ 的质数，只有 $65$ 个质数。

对于这些质数，我们先进行之前的策略，得到 $x$ 的小质数因子，并且询问出他应有的次幂。

可以计算出，这部分操作次数最多为 $238$ 次。

然后执行完之后只会有 $1,x$ 和 $x$ 的大质数因子。

然后对于大质数，还拥有 $9527$ 个。

假设之前得到的小质数因子乘积 $d$ 大于 $1$。

那么这个数是个合数，直接询问所有大质数 $p\times d$ 是否存在，如果存在那么 $x = p \times d$ 。

这部分的操作次数最多为 $238+9527+1=9766$。

如果 $d=1$ 的话，那么证明我们的数 $x$ 是个质数或者为 $1$，他就在后面的大质数因子中。

那么不能照搬上面的做法了，而直接暴力操作次数要乘二，就超了。

人类智慧，接下来的序列中只有 $1$ 和大质数。

对大质数进行分块，每 $100$ 个大质数分一块，每次连续删 $100$ 个大质数。

然后询问 $\texttt{A 1}$ 可以得到现在序列中数量，按理来说应该是每次减少一块长度个，如果有一次减少的个数少了 $1$，证明 $x$ 在这一块中，然后暴力递归找即可。

这部分的操作次数最终也不会超过 $10^4$ 。

实际上我调了一下块长为 $86$，因为我写丑了。

```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
// 德丽莎的可爱在于德丽莎很可爱，德丽莎为什么很可爱呢，这是因为德丽莎很可爱！
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define FOR(i, l, r) for(int i = (l); i <= r; ++i)
#define REP(i, l, r) for(int i = (l); i <  r; ++i)
#define DFR(i, l, r) for(int i = (l); i >= r; --i)
#define DRP(i, l, r) for(int i = (l); i >  r; --i)
#define FORV(i, ver) for(int i = 0; i < ver.size(); i++)
#define FORP(i, ver) for(auto i : ver)
template<class T>T wmin(const T &a, const T &b) {return a < b ? a : b;}
template<class T>T wmax(const T &a, const T &b) {return a > b ? a : b;}
template<class T>bool chkmin(T &a, const T &b) {return a > b ? a = b, 1 : 0;}
template<class T>bool chkmax(T &a, const T &b) {return a < b ? a = b, 1 : 0;}
inline int read() {
  int x = 0, f = 1;  char ch = getchar();
  while( !isdigit(ch) ) { if(ch == '-') f = -1;  ch = getchar();  }
  while( isdigit(ch) ) {  x = (x << 1) + (x << 3) + (ch ^ 48);  ch = getchar();  }
  return x * f;
}
const int N = 2e6;
int n, vis[N], pr[N], tot, c[N], num;
void prime(int n) {
  FOR (i, 2, n) {
    if (vis[i]) continue;
    pr[++tot] = i;
    for (int j = i; j <= n; j += i) vis[j] = 1;
  }
}
int A(int x) {
  cout << "A " << x << "\n";  cout.flush();
  int qwq;  cin >> qwq;  return qwq;
}
void B(int x) {
  cout << "B " << x << "\n";  cout.flush();
  int qwq;  cin >> qwq;
}
void C(int x) {
  cout << "C " << x << "\n";  cout.flush();  exit(0);
}
signed main () {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  n = read(); prime(n);
  if (n == 1) { C(1); }
  int now = 1;
  FOR (i, 1, tot) {
    if (pr[i] > 316) break;
    int x = pr[i];
    B(x);
    if ( A(x) == 1 ) {
      now = now * x;
      int gtr = x;
      while (1) {
        gtr *= x;
        if (gtr > n) break;
        if ( A(gtr) == 1 ) now *= x;
        else break;
      }
    }
  }
  if (now == 1) {
    int ans = 1;
    FOR (i, 1, tot) {
      if (pr[i] < 316) continue;
      c[++num] = pr[i];
    }
    int siz = 86, bel = (num - 1) / siz + 1;
    int cnt = A(1);
    FOR (i, 1, bel) {
      int l = (i - 1) * siz + 1;
      int r = wmin(num, i * siz);
      int len = r - l + 1;
      FOR (j, l, r) {
        int x = c[j];
        B(x);
      }
      int qaq = A(1);
      if (qaq == cnt - len) { cnt -= len;  continue;  }
      FOR (j, l, r) {
        int x = c[j];
        int qwq = A(x);
        if (qwq) C(x);
      }
    }
    C(1);
  }
  FOR (i, 1, tot) {
    if (pr[i] < 316) continue;
    int x = pr[i];
    if (x * now > n) break;
    if (A(x * now) == 1) C(x * now);
  }
  C(now);
  return 0;
}
```

---

## 作者：cmll02 (赞：2)

不用分块的一个显然做法。

考虑到 $x=\prod p_i^{c_i}$。

一个套路是把 $p_i$ 按照 $\sqrt n$ 分开来。

小的部分可以直接暴力做，对于每个 $p_i\le \sqrt n$，从大到小枚举 $c_i$，操作：（记 $k=p_i^{c_i}$）

```
B k
A k
```

如果第二次操作返回 $1$ 说明 $k|x$。

做完之后顺便把集合里 $p_i$ 的倍数删完。

那么接下来只剩下最多一个大于 $\sqrt n$ 的质因数，且集合里只有 $1,p_i (p_i>\sqrt n),x$。

如果 $x$ 有 $\le \sqrt n$ 的因数，显然询问 $x$ 的最后一个因数的时候返回值是 $2$。

如果没有，$x=1$ 或 $x\in prime$。

这个时候是不好做的，因为你就算询问到 $x$，返回值也是 $1$。

考虑二分。

把所有质数拉出来，先把前一半删掉，然后用 `A 1` 来询问剩余数量。

如果数量多了，说明删的里面有 $x$，在前面暴力找。

否则对于右边继续二分。

次数在 $x\log x + C$，$x$ 是质数个数，$C$ 在 $100\sim 300$ 之间，可过。

---

## 作者：SSerxhs (赞：2)

考虑枚举素数对 $x$ 进行因数分解

若 $p_i\le\sqrt x$，可以用 $B$ 暴力枚举 $p_i$ 及其倍数进行分解

若 $p_i>\sqrt x$，一个初步思路是用两次 $B$ 操作判断 $x$ 是否为 $p_i$ 的倍数，但是 $10^5$ 以内的素数有超过 $9600$ 个，显然不可以

这时我们会发现还没有使用过 $A$ 操作，考虑利用 $A$ 操作判断数字是否被删去，一个很自然的思路是连续 $B$ 一段素数之后用 $A$ 看看减少次数是否等于 $B$ 的次数，就可以判断连续 $B$ 的素数中是否含有 $x$

但是这对于 $x$ 不是素数但因数含有第二类情况素数的情况不适用，这种情况只需要看连续 $B$ 的区间内是否有返回值大于 $1$ 的就可以了

操作次数大概是卡着上界的，可以用二分做到更优

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+2;
int n,c,fh,i,x,y,j,m,ss[N],gs,ans=1,now,ksiz=100;
bool ed[N];
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(n);m=sqrt(n);while ((m+1)*(m+1)<=n) ++m;
	for (i=2;i<=m;i++)
	{
		if (!ed[i]) ss[++gs]=i;
		for (j=1;(j<=gs)&&(ss[j]*i<=m);j++)
		{
			ed[i*ss[j]]=1;
			if (i%ss[j]==0) break;
		}
	}
	for (i=1;i<=gs;i++)
	{
		printf("B %d\n",ss[i]);
		fflush(stdout);
		read(x);printf("B %d\n",ss[i]);
		fflush(stdout);
		read(x);y=ss[i];
		while (x)
		{
			y*=ss[i];if (y>n) break;
			printf("B %d\n",y);
			fflush(stdout);
			read(x);
		}
		ans*=y/ss[i];
	}
	memset(ed,0,sizeof(ed));x=gs;gs=0;
	for (i=2;i<=n;i++)
	{
		if (!ed[i]) ss[++gs]=i;
		for (j=1;(j<=gs)&&(ss[j]*i<=n);j++)
		{
			ed[i*ss[j]]=1;
			if (i%ss[j]==0) break;
		}
	}
	printf("A 1\n");
	fflush(stdout);
	gs-=ksiz;int now;read(now);
	for (i=x+1;i<=gs;i+=ksiz)
	{
		for (j=0;j<ksiz;j++)
		{
			printf("B %d\n",ss[i+j]);
			fflush(stdout);read(x);
			if (x>1) {printf("C %d",ans*ss[i+j]);fflush(stdout);return 0;}
		}
		printf("A 1\n");
		fflush(stdout);
		read(x);
		if (x!=now-ksiz)
		{
			for (j=i;j<i+ksiz;j++)
			{
				printf("B %d\n",ss[j]);
				fflush(stdout);
				read(x);if (x) {ans*=ss[j];break;}
			}
			printf("C %d",ans);fflush(stdout);return 0;
		}now=x;
	}gs+=ksiz;
	for (;i<=gs;i++)
	{
		printf("B %d\n",ss[i]);
		fflush(stdout);
		read(x);printf("B %d\n",ss[i]);
		fflush(stdout);
		read(x);if (x) {ans*=ss[i];break;}
	}
	printf("C %d",ans);
	fflush(stdout);
}
```

---

## 作者：AsunderSquall (赞：1)

# 题意  
交互题。  
你有一个含有 $1 \sim n$ 的集合，其中有一个选定的数 $x$，你需要在 $10000$ 次询问内得到 $x$ 的值。  
- A y 查询集合中有几个 $y$ 的倍数。  
- B y 查询集合中有几个 $y$ 的倍数并删去它们。特别的，$x$ 不会被删去。  
- C y 表明你已经知道了 $x$，输出它以结束交互。   

$n \le 10^5$
# 题解  
$3$ 个月前的我还只能瞪着这道题发呆，现在我已经能独立做出来了，这是不是我实力的一点进步呢？

注意到 $10^5$ 以内的质数共有 $9592$ 个。  
不妨设 $n$ 以内的质数有 $m$ 个。  
如果对 $317$以内的质数进行枚举，并且把直接把 $x$ 分解掉，需要的次数比较少，大概在 $200$ 以内。  
枚举方法：  
每次先 B p，再 A p，如果不为 $0$，说明 $p|x$，那么继续看 $p^2$，以此类推。  

剩下的情况都是在 $x$ 中出现次数不超过 $1$ 的质数  
对于剩下的情况，怎样用 $1$ 次询问判断一个质数是否存在？  
分两种情况讨论：  
- 如果 $x$ 没有 $317$ 以内质数，说明自身是个质数或者是 $1$。   
考虑利用类似分块的思想  
每次把 $\sqrt m$ 个质数删掉，然后询问一下是不是刚好删了 $\sqrt m$ 个数，如果不是，那么说明剩下有个质数是这 $\sqrt m$ 个数里面的，再逐个查询一遍，需要的额外次数为 $2\sqrt m+O(1)$ 级别，能过。    

- 如果有 $317$ 以内的质数，那么对后面的质数每次 A 一下，如果为 $2$ 说明 $x$ 有这个质数  

细节上还是有一点的。  
- 对于 $x$ 是个质数或 $1$ 的情况，如果枚举完了质数也要再查询一遍，而不仅仅是 $\sqrt m$ 的倍数。  
- 分解的时候 $p^k$ 不能超过 $n$，出现这种情况不能进行查询，直接`break`掉。  
- 在代码中我直接将 $\sqrt m$ 替换成了 $100$，关系不大。  

代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=1e5+5;
const int M=5005;
const int mod=998244353;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y){int ret=1;while (y){if (y&1) ret=(ret*x)%mod;x=(x*x)%mod;y>>=1;}return ret;}
int a[N];
int n;
int prim[N],vis[N],cnt;
int ans;
int YUE[N],CNT;
int ANS=1;
int A(int x){cout<<"A "<<x<<endl;cin>>ans;}
int B(int x){cout<<"B "<<x<<endl;cin>>ans;}
int C(int x){cout<<"C "<<x<<endl;exit(0);}
signed main()
{
	rd(n);
	for (int i=2;i<=n;i++)
	{
		if (!vis[i]) prim[++cnt]=i;
		for (int j=1;j<=cnt;j++)
		{
			if (i*prim[j]>n) break;
			vis[i*prim[j]]=1;
			if (i%prim[j]==0) break;
		}
	}
	//317是第67个质数
	for (int i=1;i<=min(cnt,66LL);i++) 
	{
		B(prim[i]);A(prim[i]);
		int tmp=prim[i];
		while (ans==1)
		{
			tmp*=prim[i];
			YUE[++CNT]=prim[i];if (tmp>n) break;
			B(tmp);A(tmp);
		}
	}
	if (CNT!=0) for (int i=1;i<=CNT;i++) ANS*=YUE[i];
	if (ANS!=1)
	{
		for (int i=67;i<=cnt;i++)
		{
			A(prim[i]);
			if (ans!=1) C(ANS*prim[i]);
		}
	} else 
	{
		A(1);
		int tot=ans,K=0;
		for (int i=67;i<=cnt;i++)
		{
			B(prim[i]);K++;
			if (K%100==0 || i==cnt)
			{
				A(1);
				if (ans==tot-K) tot=ans,K=0;
				else for (int j=i-K+1;j<=i;j++) {A(prim[j]);if (ans==1) C(prim[j]);}
			}
		}
	}
	C(ANS);
}

```

---

## 作者：极寒神冰 (赞：1)

首先考虑$x$是不是质数

$\sqrt{100000}\approx316$

可以通过筛选小于$316$得知$x$所有小于$316$的质因数。(part1

然后考虑是否筛出了质因数。

如果筛出来了，那么还可能存在某个大于$316$的质因数，对应part2检查即可

如果没有筛出来，那就说明$x$是一个质数，每尝试$100$个质数后用$A(1)$看看这个数中有没有数字删掉，没删掉的就是这个数了(part3

```
#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=1e5+10;
vector<int>pre1,pre2;
int n;

int unprime[N];
int prime[N/10],tot;
void init()
{
	unprime[1]=1;
	for(int i=2;i<N;i++)
	{
		if(!unprime[i]) 
		{
			prime[++tot]=i;
		}
		for(int j=1;j<=tot&&i*prime[j]<N;j++)
		{
			unprime[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}
int A(int x=1)
{
	if(x>n) return 0;
	printf("A %lld \n",x);
	fflush(stdout);
	int k;
	scanf("%lld",&k);
	return k;
}
int B(int x)
{
	if(x>n) return 0;
	printf("B %lld\n",x);
	fflush(stdout);
	int k;
	scanf("%lld",&k);
	return k;
}
int C(int x)
{
	printf("C %lld\n",x);
	fflush(stdout);
	exit(0);
}
//sqrt(100000)=316
signed main()
{
	init();
	n=read();
	for(int i=2;i<=n;i++)
	{
		if(!unprime[i])
		{
			if(i<=316) pre1.pb(i);
			else pre2.pb(i);
		}
	}
	int res=1;
	for(int x:pre1)//part1
	{
		B(x);
		for(int i=x;;i*=x)
		{
			if(A(i)) res*=x;
			else break;
		}
	}
	int tmp1=pre2.size();
	if(res!=1) //part2
	{
		for(int i=0;i<tmp1;i+=100)
		{
			int tmp2=min(tmp1,i+100);
			for(int j=i;j<tmp2;j++)
			{
				if(A(res*pre2[j])) C(res*pre2[j]);
			}
		}			
		C(res);

	}
	else //part3
	{
		int cnt=tmp1+1;
		for(int i=0;i<tmp1;i+=100)
		{
			int tmp2=min(tmp1,i+100);
			for(int j=i;j<tmp2;j++)
			{
				B(pre2[j]);
			}
			cnt-=min(100ll,tmp1-i);
			if(A(1)!=cnt)
			{
				for(int j=i;j<tmp2;j++)
				{
					if(A(pre2[j])) C(pre2[j]);
				}
			}
		}
		C(1);
	}
}
```


---

## 作者：Nerovix (赞：1)

## [题面](https://codeforces.com/contest/1406/problem/E)

~~键盘坏了+手速慢了没写完~~

做法很劣，~~9700+次玩的就是刺激~~

10000次操作，考虑1e5内的素数个数。打个表，发现有9592个，感觉就是从这里想了。考虑先求x的最大质因数。显然不能把素数从大到小每个都B一次再A一次，考虑分块。从大到小每个素数B一次，同时每隔$\sqrt{9592}$个素数就问一个A 1，检查答案跟你暴力模拟的结果是否相同。如果不相同，说明最大质因数就在上一个块内了。然后再$\sqrt{9592}$次询问把他找到就行了

最大质因数外的其他因子直接暴力去询问A，看返回的答案是0还是1就行了.

询问复杂度$O(9592+2\sqrt{9592}+log)$

```cpp

#include<stdio.h>
#include<bits/stdc++.h>
#define f(a,b,c) for(register int a=(b);a<=(c);++a)
#define ff(a,b,c) for(register int a=(b);a>=(c);--a)
#define ll long long
//#define int long long
char pbuf[1<<20],*pp1=pbuf;
inline void push(char c){*pp1=c;pp1=(pp1-pbuf==(1<<20)-1)?(fwrite(pbuf,1,1<<20,stdout),pbuf):(pp1+1);}
#define pc push
//#define pc putchar
#define pe pc('\n')
#define ps pc(' ')
#define wer rd()
char *p1,*p2,buf[1<<20];
#define GC (p1==p2&&(p1=buf,p2=buf+fread(buf,1,1<<20,stdin),p1==p2)?0:(*(p1++)))
//#define GC getchar()
using namespace std;
inline ll wer{
	ll ans;char t,k;
	while(((t=GC)!='-')&&(t>'9'||t<'0'));
	k=(t=='-');
	ans=k?0:(t-'0');
	while((t=GC)>='0'&&t<='9')ans=ans*10+t-'0';
	return k?-ans:ans;
}
inline void wt(ll k)
{
	if(k<0)pc('-'),wt(-k);
	else
	{
		if(k<10)pc('0'+k);
		else wt(k/10),pc('0'+k%10);
	}
	return;
}
const int maxn=100010;
int n;
int tg[maxn],pr,tt,alr,dd,p[maxn],mp[maxn];
main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		if(tg[i]==0){p[++pr]=i;
			for(int j=i*2;j<=n;j+=i)
			tg[j]=1;
		}
	}
	int j=pr,k=0;tt=n;
	memset(tg,0,sizeof tg);
	int timer=0
	,la=pr+1;
	for(;j>0;j--){
		++timer;
		for(int i=p[j];i<=n;i+=p[j])
		tt-=(tg[i]==0),tg[i]=1;
		printf("B %d\n",p[j]);
		fflush(stdout);
		scanf("%d",&dd);
		if(timer%(int)sqrt(pr)==0||j==1){
			printf("A 1\n");
			fflush(stdout);
			scanf("%d",&dd);
			if(dd!=tt){
				k=la-1;
				while(1){
					printf("A %d\n",p[k]);
		        	fflush(stdout);
		        	scanf("%d",&dd);
		        	if(dd)break;
					k--;
				}
			}
			la=j;
		}
		if(k!=0)break;
	}
	if(j==0)return puts("C 1"),0;
	ll ans=p[k];
	for(int i=1;i<=k;i++){
		ll j;
		for(j=ans*p[i];j<=n;j*=p[i]){
			printf("A %d\n",j);
			fflush(stdout);
			scanf("%d",&dd);
			if(dd==0)break;
		}
		ans*=j/ans/p[i];
	}
	printf("C %d",ans);
//	cerr<<pr<<"\n";
	fwrite(pbuf,1,pp1-pbuf,stdout);
	return 0;
}
```

## orzdeaf

![](https://cdn.luogu.com.cn/upload/image_hosting/y89hb7q2.png)

或许这就是[deaf](http://deafakioi.tql.moe/)akioi吧

---

## 作者：Plozia (赞：0)

宣传博客 $\to$ [link](https://www.cnblogs.com/Plozia/p/16246576.html)

一道 Idea 题，但是做过两道类似寿司晚宴的我还是没能想出这道题……

一个显然的思路是先枚举所有质数用 B 操作筛掉合数，然后用 A 操作知道有哪些质因子，枚举这些质因子的次幂得到这个数，但 100000 以内的质数个数是 9592，先筛合数再用 A 操作都已经超出限制了。

考虑按照 $\sqrt{n}$ 划分，首先线筛出所有的质数，然后利用所有小于等于 $\sqrt{n}$ 的质数筛掉所有合数，同时枚举次幂以得知 $x$ 小于等于 $\sqrt{n}$ 的质因子及其次幂，将这个结果记作 $s$（$s$ 初始化为 1）。

如果 $s>1$ 说明 $x$ 是个合数并且**可能**有一个大于 $\sqrt{n}$ 的质因数，此时用 A/B 操作枚举这些质数看一眼哪个返回值是 2 就知道最大质因数了。

如果 $s=1$ 说明 $x$ 是 1 或者是大于 $\sqrt{n}$ 的质数，考虑分块，每 100 个质数分成一块，对每一块首先利用 B 操作删掉质数，然后使用 `A 1` 可以得知这一块删了多少个数，便可得知 $s$ 是不是在这一块内，如果在就暴力用 A/B 操作查询即可。

几个注意点：

- 注意 $n=1,x=1$ 这样的询问。
- 任意时刻你向交互库输出的数不能大于 $n$。

GitHub：[CodeBase-of-Plozia](https://github.com/Plozia/CodeBase-of-Plozia/blob/main/%E6%9D%82%E9%A1%B9/%E6%80%9D%E7%BB%B4%E9%A2%98%2B%E4%BA%A4%E4%BA%92%E9%A2%98/CF1406E%20Deleting%20Numbers.cpp)

Code:

```cpp
/*
========= Plozia =========
	Author:Plozia
	Problem:CF1406E Deleting Numbers
	Date:2022/5/8
========= Plozia =========
*/

#include <bits/stdc++.h>

typedef long long LL;
const int MAXN = 1e5 + 5;
int n, Prime[MAXN], cntPrime, p, ans = 1;
bool book[MAXN];

int Read()
{
	int sum = 0, fh = 1; char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar()) fh -= (ch == '-') << 1;
	for (; ch >= '0' && ch <= '9'; ch = getchar()) sum = sum * 10 + (ch ^ 48);
	return sum * fh;
}
int Max(int fir, int sec) { return (fir > sec) ? fir : sec; }
int Min(int fir, int sec) { return (fir < sec) ? fir : sec; }

void init()
{
	for (int i = 2; i <= n; ++i)
	{
		if (!book[i]) Prime[++cntPrime] = i;
		for (int j = 1; j <= cntPrime; ++j)
		{
			if (i * Prime[j] > n) break ;
			book[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) break ;
		}
	}
}

int optA(int x) { printf("A %d\n", x); fflush(stdout); return Read(); }
int optB(int x) { printf("B %d\n", x); fflush(stdout); return Read(); }

int main()
{
	n = Read(); init(); for (p = 1; p * p <= n; ++p) ; --p; int i = 1;
	for (i = 1; Prime[i] <= p && i <= cntPrime; ++i)
	{
		optB(Prime[i]);
		int tmp = Prime[i];
		if (optA(Prime[i]) == 0) continue ;
		while (tmp * Prime[i] <= n) { if (optA(tmp * Prime[i]) == 0) break ; tmp *= Prime[i]; }
		ans = ans * tmp;
	}
	if (ans != 1)
	{
		for (; i <= cntPrime; ++i) 
			if (optA(Prime[i]) == 2) { ans *= Prime[i]; break ; }
	}
	else
	{
		int Last = i, Remain = optA(1);
		for(; i <= cntPrime; ++i)
		{
			optB(Prime[i]);
			if (i - Last + 1 == 100 || i == cntPrime)
			{
				int tmp = optA(1);
				if (Remain - tmp == i - Last + 1) { Last = i + 1; Remain = tmp; continue ; }
				for (int j = Last; j <= i; ++j)
				{
					if (optA(Prime[j]) == 1) { ans = Prime[j]; break ; }
				}
				break ;
			}
		}
	}
	printf("C %d\n", ans); fflush(stdout); return 0;
}
```

---

## 作者：MuYC (赞：0)

#### Solution

可以发现的性质：

+ $\leq 10^5$ 的数中一共有 $9592$ 个质数。

这道题的问题在于求出 $x$ 的所有质因子。

不难想到我们肯定可以先查询出 $x$ 的所有 $\leq \sqrt{n}$ 的质因子。

把小于 $\sqrt{n}$ 的质因子的所有倍数删掉之后剩下来就全都是质数。

接下来这里分两种情况讨论：

+ 如果 $x$ **不存在** $\leq \sqrt{n}$ 的质因子，这意味着 $x$ 是质数。

如果一个一个删掉剩下的所有质数再调用 `A` 操作显然会超出次数限制。

但是我们此刻的目的是：求出某一个位置没有被删掉。

那么可以很自然的想到，我们先删掉 $B$ 个质数之后，用**一次** `A 1`，判断跟上一次询问 `A 1` 的差是不是 $B$ ，如果不是则说明这 $B$ 个质数里面存在一个数是 $x$，然后我们就直接一个个用 `A` 操作求是不是这一位即可。

+ 如果 $x$ **存在** $\leq {\sqrt{n}}$ 的质因子，那么 $x$ 是合数。

可以直接查找所有 $> \sqrt{n}$ 的质数 $p$ 然后用 `A` 操作，如果目前 $p$ 倍数有 $1$ 个以上那么 $x$ 含有的剩下的一个质因子就是 $p$，直接求得答案。

#### 查询次数分析：

为了在求得所有质因子后求出质因子的幂次，需要预留 $30$ 次的询问。

对于前面求 $\leq \sqrt{n}$ 的质因子大概只会有 $260$ 次询问。

此刻我们还剩下大概 $9700$ 次询问。

对于 $x$ 是质数的情况，当 $B = 100$ 的时候，只会消耗 $9500$ 次询问。

对于 $x$ 是合数的情况，显然我们从小到大枚举质因子的话，询问次数不超过 $5200$ 次。

因此，此问题得到完美解决，同时如果调试遇到困难可以用讨论区中我提供的 grader。


#### AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, P[50005], tot, Ans = 1;
void Answer(int x) { cout << "C " << x, fflush(stdout); exit(0); }
int Ask(int x) {
    cout << "A " << x << "\n", fflush(stdout);
    int res; cin >> res;
    return res;
}
int Del(int x) {
    cout << "B " << x << "\n", fflush(stdout);
    int res; cin >> res;
    return res;
}
void GetPrime() {
    for(int i = 2, flag = 0; i <= 1e5 ; i ++, flag = 0) {
        for(int j = 2 ; j <= sqrt(i) ; j ++)
            if(i % j == 0) flag = 1;
        if(!flag) P[++ tot] = i;
    }
    return ;
}

int main() {
    cin >> n, GetPrime();
    int cnt = 0, lst = 0;
    for(int i = 1 ; i <= tot && P[i] <= n ; i ++) {
        if(P[i] <= 317) {
            Del(P[i]);
            if(Ask(P[i]) == 1) {
                int now = P[i]; Ans *= P[i];
                while(1) {
                    now *= P[i]; if(now > n) break; 
                    if(Ask(now)) Ans *= P[i]; else break;
                }
            }
            continue;
        }
        if(Ans == 1) {
            cnt ++; 
            if(cnt == 1) lst = Ask(1);
            Del(P[i]);
            if(i == tot || cnt == 100) {
                int now = Ask(1);
                if(lst - now != cnt) {
                    for(int j = i ; j >= i - cnt + 1 ; j --) 
                        if(Ask(P[j]) == 1) { Ans *= P[j]; break; }
                    break;
                }
                cnt = 0;
            }
        }
        else if(Ask(P[i]) == 2) { Ans *= P[i]; break; }
    } Answer(Ans);
    return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/1406/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1406E)

一道个人感觉挺有意思的交互题，本人一开始想了个奇奇怪怪的做法，还以为卡不进去，结果发现竟然过了，而且还是正解（

首先看到这类题目可以考虑每次删掉一个质数的倍数，即对某个 $pr_i$ 执行 B 操作，然后对 $pr_i$ 进行 A 询问，根据询问得到的值是否等于理论上删去这些数后 $pr_i$ 的倍数个数来判断 $pr_i$ 是否是 $x$ 的因数，如果是那么就枚举 $pr_i$ 的 $2,3,4,\cdots$ 次方，再对这些次方执行 A 询问，以此来判断 $x$ 质因数分解式中 $pr_i$ 的次数。

算下询问次数，询问 $pr_i$ 的 $2,3,4,\cdots$ 的次数显然与 $x$ 质因数分解式中 $x$ 每个质因数的次数之和有关，是 $\log$ 级别的，最多只有 $20$ 可以忽略，瓶颈在于每个质因数都要进行两次操作，打表可以发现 $10^5$ 以内质因数个数刚好比 $10^4$ 小个几百，因此 $2\pi(n)$ 是 $2\times 10^4$ 级别的，过不去。

考虑优化，很明显对于 B 操作而言，我们是可以在操作的同时问出 $x$ 的倍数的，而刚刚的解法中并没有利用这个性质，因此考虑从这个性质入手解题，我们还是从小到大枚举质因子，只不过与刚才不同的一点是，我们不每进行一次 B 询问都跟一个 A 询问，我们只做 B 询问，那么对于大多数质数，每次 B 询问时也可以根据结果知道该质数是否是 $x$ 的因子，只有一个例外——那就是 $x$ 的最小质因子，因此接下来我们只用找到 $x$ 的最小质因子及它的次数即可，这也是本题的难点所在，我就在这个地方卡了 20+min 后想到了这个解法。

注意到 A 操作起始下标是可以从 $1$ 开始的，而通过 $A\ 1$ 我们则可以知道刚才询问的数中是否出现了 $x$ 的质因子，因此我们考虑根分，每 100 次 B 询问来一次 A 1，那么我们可以把质因子按大小分为 $\lceil\dfrac{\pi(n)}{100}\rceil$，显然最小质因子就在最后一个 A 1 等于剩余数个数与第一个 A 1 不等于剩余数个数的位置之间，中间部分就暴力枚举质因子然后用 A 质因子判断即可，这样总操作次数为 $\pi(n)+100+\lceil\dfrac{\pi(n)}{100}\rceil+\log n$，实测询问次数最多 9700+ 次，刚好卡过。

```cpp
const int MAXN=1e5;
int n,pr[MAXN/5+5],prcnt=0;
bool vis[MAXN+5],is[MAXN+5],has[MAXN+5];
vector<int> fac[MAXN+5];
int cnt[MAXN+5];
void sieve(){
	for(int i=2;i<=n;i++){
		if(!vis[i]) pr[++prcnt]=i;
		for(int j=1;j<=prcnt&&pr[j]*i<=n;j++){
			vis[pr[j]*i]=1;
			if(i%pr[j]==0) break;
		}
	}
	for(int i=1;i<=n;i++) cnt[i]=n/i;
	for(int i=1;i<=prcnt;i++) for(ll j=pr[i];j<=n;j*=pr[i]) is[j]=1;
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j+=i) fac[j].pb(i);
}
void del(int x){for(int y:fac[x]) cnt[y]--;has[x]=1;}
void del_mul(int x){for(int i=x;i<=n;i+=x) if(!has[i]) del(i);}
int qr1(int x){printf("A %d\n",x);fflush(stdout);int res;scanf("%d",&res);return res;}
int qr2(int x){printf("B %d\n",x);fflush(stdout);int res;scanf("%d",&res);return res;}
int main(){
	scanf("%d",&n);sieve();
	int cur=1,mn=prcnt,cc=0,fst_blk=0;
	for(int i=1;i<=prcnt;i++){
		int t=qr2(pr[i]);
		if(t!=cnt[pr[i]]){
			if(cur==1) mn=i;del_mul(pr[i]);
			cur*=pr[i];
			for(ll x=1ll*pr[i]*pr[i];x<=n;x*=pr[i]){
				int num=qr1(x);//printf("%d %d\n",x,cnt[x]);
				if(num==cnt[x]) break;cur*=pr[i];
			}
		} else del_mul(pr[i]);
		++cc;
		if(cc==100&&!fst_blk){
			cc=0;int x=qr1(1);
			if(x!=cnt[1]) fst_blk=i;
		}
	} if(!fst_blk){int x=qr1(1);if(x!=cnt[1]) fst_blk=prcnt;}
	for(int j=(fst_blk-1)/100*100+1;j<=min(fst_blk,mn);j++){
		int x=qr1(pr[j]);
		if(x!=cnt[pr[j]]){
			cur*=pr[j];
			for(ll k=1ll*pr[j]*pr[j];k<=n;k*=pr[j]){
				int num=qr1(k);//printf("%d %d\n",x,cnt[x]);
				if(num==cnt[k]) break;cur*=pr[j];
			} break;
		}
	}
	printf("C %d\n",cur);fflush(stdout);
	return 0;
}
```



---

## 作者：STDquantum (赞：0)

这题一个很直接的思路就是直接拿质数来筛出 $x$，如果把 $x$ 的所有质因子和对应指数找到，那么就可以确定 $x$。

可以证明这么做平均是最快的。

那么具体怎么做呢？我们考虑把一个质数 $p$ 的所有倍数删去，若有一个数没有被删除成功，那就说明 $x$ 中有 $p$ 这个因子。

一种朴素的做法是直接删掉所有 $p$ 的倍数，然后查询 $p$ 的倍数有几个，如果是 $1$ 的话就说明有 $p$ 这个因子，然后接着二分 $p$ 的指数。

但是这样的操作次数是不对的，因为 $100000$ 以内的质数就有 $9592$ 个，一删一查次数就多了，所以考虑怎么优化这个暴力。

删质数的这一次是肯定要留着的，但是查询有大量的冗余操作，所以可以考虑分批查询。

这就有一些分块的思想了。

为了让复杂度尽可能稍微均摊一点，设质数的个数为 $num$，则分成 $\sqrt {num}$ 个块，先全部删掉所有块内的质数，然后查询一个`A 1`，就可以查看之前一共删了多少个数字。

如果这个数字和之前删质数时候查询个数的和一样，就说明 $x$ 中是没有这个块内的质因子的。

如果不一样，说明有这个质因子，一个一个试查询就好了。若确定有这个质因子就寻找其指数，然而我二分容易写锅，就直接一个一个乘上去查。

可以结合代码理解：

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace STDquantum {

typedef long long ll;
const int N = 2e6 + 10;
int num, prime[N];
bool isprime[N];
inline void Get(int n) { // 筛质数
    memset(isprime, 1, sizeof(isprime));
    isprime[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if (isprime[i]) prime[++num] = i;
        for (int j = 1; j <= num && i * prime[j] <= n; ++j) {
            isprime[i * prime[j]] = 0;
            if (i % prime[j] == 0) break;
        }
    }
}

int n, x;
ll ans = 1; // ans代表现在找到的数

inline void query(int type, int value) { // 询问和读入
    if (type == 1) {
        printf("A %d\n", value);
    } else if (type == 2) {
        printf("B %d\n", value);
    } else {
        printf("C %d\n", value);
        fflush(stdout);
        exit(0);
    }
    fflush(stdout);
    scanf("%d", &x);
}

inline void Find(int p) { // 找到x中p的指数
    while (ans * p <= n) {
        query(1, ans * p);
        if (x) {
            ans *= p;
        } else {
            break;
        }
    }
}

inline void main() {
    scanf("%d", &n), Get(n);
    int s = sqrt(num); // 分成s个块
    for (int i = 1, cur = n, sum; i <= num; i += s) { // 枚举块的左端点
        sum = 0;
        for (int j = 0; i + j <= num && j < s; ++j) { // 枚举块内第几个点
            query(2, prime[i + j]), sum += x; // 查询并加和
        }
        query(1, 1);
        int tmp = x; // 临时记录一下现在集合内还剩多少数
        if (sum > cur - x) { // 如果这次删去的数的总数大于实际减少的总数，就说明质因子在此块内出现过
            for (int j = 0; i + j <= num && j < s; ++j) {
                Find(prime[i + j]);
            }
        }
        cur = tmp; // 更新一下集合里当前数字个数
    }
    query(3, ans); // 输出答案，因为ans初始化就是1所以没必要特判了。
}

}   // namespace STDquantum

int main() {
    STDquantum::main();
    return 0;
}
```



---

