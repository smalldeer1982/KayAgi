# Guess Divisors Count

## 题目描述

This is an interactive problem.

We have hidden an integer $ 1 \le X \le 10^{9} $ . You don't have to guess this number. You have to find the number of divisors of this number, and you don't even have to find the exact number: your answer will be considered correct if its absolute error is not greater than 7 or its relative error is not greater than $ 0.5 $ . More formally, let your answer be $ ans $ and the number of divisors of $ X $ be $ d $ , then your answer will be considered correct if at least one of the two following conditions is true:

- $ | ans - d | \le 7 $ ;
- $ \frac{1}{2} \le \frac{ans}{d} \le 2 $ .

You can make at most $ 22 $ queries. One query consists of one integer $ 1 \le Q \le 10^{18} $ . In response, you will get $ gcd(X, Q) $ — the greatest common divisor of $ X $ and $ Q $ .

The number $ X $ is fixed before all queries. In other words, interactor is not adaptive.

Let's call the process of guessing the number of divisors of number $ X $ a game. In one test you will have to play $ T $ independent games, that is, guess the number of divisors $ T $ times for $ T $ independent values of $ X $ .

## 说明/提示

Why the limitation for number of queries is 22 exactly? Maybe the problem author is a Taylor Swift fan.

Let's look at the example.

In the first game $ X = 998\,244\,353 $ is hidden. Would be hard to guess this, right? This number is prime, so the number of its divisors is 2. The solution has made several random queries, and all the responses turned out to be 1 (strange things, not even one of three random numbers is divisible by $ 998\,244\,353 $ ). It's fare to assume that the hidden number doesn't have many divisors, so the solution has answered 5. Why not. This answer will be considered correct since $ | 5 - 2 | = 3 \le 7 $ .

In the second game $ X = 4\,194\,304 = 2^{22} $ is hidden, it has 23 divisors. The solution has made queries $ 1024 =       2^{10} $ , $ 1\,048\,576 =2^{20} $ , $ 1\,073\,741\,824 =       2^{30} $ and got responses $ 1024 = 2^{10} $ , $ 1\,048\,576       =2^{20} $ , $ 4\,194\,304 = 2^{22} $ , respectively. Then the solution got completely confused and answered the answer to The Ultimate Question of Life, the Universe, and Everything. This answer will be considered correct since $ \frac{1}{2} \le       \frac{42}{23} \le 2 $ .

## 样例 #1

### 输入

```
2

1

1

1


1024

1048576

4194304```

### 输出

```
? 982306799268821872

? 230856864650023977

? 134690134760714371

! 5
? 1024

? 1048576

? 1073741824

! 42```

# 题解

## 作者：gyh20 (赞：11)

交互题？限制这么松？乱搞？

先讲一下做法，然后给证明。

枚举每一个质数，幂次初始为 $1$ ，加入优先队列，以幂次降序为第一关键字，质数大小升序为第二关键字，每次从队首取出，询问这些幂次的乘积，越大越好，如果包含这个幂次则令这个幂次 $+1$ 重新加入队列否则不加入，执行 $22$ 次，最后输出答案 $\times 2$。

证明？

$1.$操作在 $22$ 以内。

说得很清楚，执行 $22$ 次。

$2.$时间复杂度？

$22$ 次，每次选十几个，再加上最初加几万个到优先队列，但只有 $100$ 组数据，没问题。

$3.$正确性？

首先，一般情况下，这个程序能用到的最大质数大概在 $900$ 左右（不信你自己试），那么我们默认 $850$ 以下的质因子都搞定了（这个绝对不过分）。

那么剩下的情况：

$(1)~~1$，最终答案只多乘了 $2$，没有问题。

$(2)~$ 质数，最终答案乘了 $2$，刚好。

$(3)~$ 质数的平方，答案应该乘 $3$，但只乘了 $2$，差距没问题。

$(4)~$ 质数乘质数，应该乘 $4$，少乘了 $2$，没问题。

$(5)~$ 三个质数相乘，但我们发现，如果是三个 $850$ 以上质数相乘那不可能有其他质因子（$\times 2$ 就大于 $10^9$ 了），那么答案至多为 $8$，然而我们输出的 $2$ 也在可接受范围之内。

所以这样是正确的。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
inline int read() {
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,ans,p[40002],tot,a[40002];
bool ip[40002];
long long ss;
struct node{
	int x,y,z;
	bool operator <(const node a)const{
		return a.y==y?a.x<x:a.y>y;
	}
}b[40002];
priority_queue<node>q;
inline int gcd(re int x,re int y){
	return y?gcd(y,x%y):x;
}
signed main() {
	t=read();
	n=4e4;
	for (int i=2; i<=n; ++i) {
		if (!ip[i])p[++tot]=i;
		for(int j=1; j<=tot&&i*p[j]<=n; ++j) {
			ip[i*p[j]]=1;
			if(i/p[j]*p[j]==i)break;
		}
	}
	while(t--){//re int kkk=read();
		while(!q.empty())q.pop();ans=1;
		for(re int i=1;i<=tot;++i)q.push((node){p[i],1,p[i]});
		for(re int jj=1;jj<=22;++jj){
			re int x=1,cnt=0;
			while(!q.empty()){
				node tmp=q.top();q.pop();
				if(1.0*x*tmp.x>1e18){q.push(tmp);break;}
				b[++cnt]=tmp,x*=tmp.x;
			}
			printf("? %lld\n",x);
			fflush(stdout);
			ss=read();
			for(re int i=1;i<=cnt;++i){
				if(ss%b[i].x==0){
					ans/=b[i].y;
					++b[i].y;
					ans*=b[i].y;
					b[i].x*=b[i].z;
					q.push(b[i]);
				}
			}
		}
		printf("! %lld\n",ans*2);
		fflush(stdout);
	}
}
```


---

## 作者：brealid (赞：7)

翻译自官方题解 https://codeforces.com/blog/entry/77491

---

If X=pα11⋅pα22⋅…⋅pαkk then d(X)=(α1+1)⋅(α2+1)⋅…⋅(αk+1).

我们知道，如果有 $X=p^{α_1}_1⋅p^{α_2}_2⋅…⋅p^{α_k}_k$ 则有 $d(X)=(α_1+1)⋅(α_2+1)⋅…⋅(α_k+1)$（$d(X)$ 表示数 $X$ 的因数个数）。

---

If X has prime p in power α and Q has p in power β then gcd(X,Q) will have p in power γ=min(α,β). If γ<β then α=γ, otherwise γ=β and α≥γ. We don't know X, but we can choose Q. If we'll choose Q with known prime factorization then we'll be able to extract all the information from query fast (in O(logQ)).

如果数 $X$ 有因数 $p^α(p,α\in N_+\ |\ Prime(p))$ 并且数 $Q$ 有因数 $p^β(p,β\in N_+\ |\ Prime(p))$，那么 $\gcd(X, Q)$ 有因数 $p^γ(p,γ\in N_+\ |\ γ=\min(α, β))$。因此我们可以得到 : 当 $γ<\beta$ 时 $\alpha=\gamma$，当 $γ=\beta$ 时 $\alpha\ge\gamma$。我们不知道 $X$，但我们可以自由选择 $Q$。如果我们用一种已知的质因数分解构造 $Q$ ，那么我们将会很容易地在 $O(logQ)$ 的时间复杂度内得到一些必要的信息（$\alpha$ 的取值或取值范围）

---

After all the queries for each prime p we'll know either the exact power in which X has it, or lower bound for it. We can get upper bound from the fact that X≤109.

在对每个质数 $p$ 进行所有必要的查询之后，我们将知道 $X$ 的确切乘方或 $X$ 的下界。 同时, 我们可以从 $X\le 10^9$ 的事实中获得 $X$ 的上限。

---

It is clear that we cannot get information about all primes — there are too many of them and too few queries. We want to somehow use the fact that we don't have to find the exact answer...

显然，我们无法获取有关所有素数的信息——素数的个数太多，提供的查询次数很少。 我们需要以某种方式利用**我们不必找到确切答案的事实**...

---

Suppose we have figured out that X=X1⋅X2 where we know X1 exactly and we also know that X2 has no more than t prime factors (including multiplicity). Then d(X1)≤d(X)≤d(X1)⋅d(X2)≤d(X1)⋅2t. If t≤1 then our answer will have relative error no more than 0.5...

假设我们已经知道 $X = X_1⋅X_2$，我们确切地知道 $X_1$，并且我们还知道 $X_2$ 的素数因子个数（包括重复的）不超过 $t$。 则 $d(X_1)≤d(X)≤d(X_1)⋅d(X_2)≤d(X_1)⋅2^t$。 如果 $t≤1$，那么我们的答案的相对误差将不超过 $0.5$ ...

---

One of the ways to guarantee that X2 has few prime factors is to show that it cannot have small prime factors. That means that we have to calculate the exact power for all small primes. This gives an overall idea for the solution: let's make a query Q=pβ for all primes p≤B (for some bound B) where β is chosen in such a way that pβ>109. This allows us to know the exact power in which X has p.

保证 $X_2$ 有很少个数的素数的一种方法是证明它不能有很小的素数。 这意味着我们必须计算所有小素数的精确**整数次幂**。 这给出了解决方案的整体思路：让我们查询 $Q =p^β$ （$p$ 为 $p≤B$（$B$ 是某个边界）的素数，并且 $\beta$ 足够大以至于 $p^β> 10^9$）。 这使我们知道 $X$ 具有 $p$ 的确切幂。

---

This basic idea can be improved in several ways:

这个 $naive$ 的想法可以用如下方案改进：

1. X has no more than 9 different prime factors, so for most primes its power is 0. If we could exclude these redundant primes fast it could speed up the solution significantly. And there is a way: we could make a query Q=p1p2…ps for s different primes, after that we will know which of them are factors of X;  
   
   ---
   $X$ 的素因子种类不超过 9 （因为 $2⋅3⋅5⋅7⋅9⋅11⋅13⋅17⋅19 < 10^9 < 2⋅3⋅5⋅7⋅9⋅11⋅13⋅17⋅19⋅23$），因此对于大部分的素数因子，其在 $X$ 中的幂为 $0$（感性理解）。如果我们可以快速排除这些多余的质数，则可以大大加快解决问题的速度。有一种方法：我们可以查询 $Q = p_1p_2 ... p_s$ 以查询 $s$ 个不同的素数，然后我们就能知道其中哪些是 $X$ 的因子；
2. β can be chosen such that p^β+1>109, because even if γ=β and α≥γ=β we will know that α≤β since otherwise X>109;
   
   ---
   选择 $\beta$ 需满足 $p^{\beta + 1}>10^9$，因为即使 $\alpha \ge \gamma = \beta$ 我们也能清楚的知道 $\alpha\le\beta$，不然 $X$ 将大于 $10^9$（即 $\alpha=\beta$）
3. From the previous point follows that we can find the exact power for two primes simultaneously, just make a query with a product of two respective numbers.
   
   ---
   从前面的步骤中我们可以同时地知道两个质数的准确**幂次**，方法是查询 $Q = p_1^{\beta_1}·p_2^{\beta_2}(p_1,p_2$ 是质数 $, \beta_1,\beta_2\in N_+\ |\ p_1^{\beta_1 + 1}>10^9,p_2^{\beta_2 + 1}>10^9)$

---


How to choose B? Apparently we want B2>109. But actually t≤2 is ok for us: if we know that L≤d(X)≤4L then we can answer 2L and the relative error will be no more than 0.5. That means we want B3>109 or B=1001.

怎么选择 $B$？显然我们希望 $B^2>10^9$。但事实上，$t\le2$ 对我们来说也是可以的：如果我们知道 $L≤d(X)≤4L$ 那么我们就可以回答 $2L$ 并且答案的倍数误差不会大于 $0.5$。从这个角度来说，我们需要的是 $B^3>10^9$ 即 $B = 1001$

---

We are close: there are 168 primes less than 1001, we can check 6 primes (for being a factor of X) in one query since 10006≤1018, so we need 28 queries.

更进一步地说：小于 $1001$ 的素数有 $168$ 个。如果我们 $6$ 个素数一组地查询（因为 $1000^6\le10^{18}$）。但这样需要 $28$ 次查询。

---

Let's note that if we have found some prime factors of X (let's say their product is X1) then X2≤109X1. Suppose we have checked all the primes not greater than p and X1⋅p3>109. That means that X2 has no more than 2 prime divisors and we are good.

我们注意到，如果我们有 $X$ 的一些素因子（假设这些素因子的乘积是 $X_1$）那么 $X_2\le\frac{10^9}{X_1}$。假设我们已经检验了所有不大于 $p$ 的素数并且 $X_1·p^3>10^9$.这就意味着 $X_2$ 的素因子个数没有超过 $2$，我们达成了目标。

--- 

What is left is to use our right to have absolute error: if X1≤3 we can just print 8! Either X1≤3 and we are fine with X2 having 3 prime factors, or X1≥4 and we have to check all primes up to 109/4−−−−−√3<630. There are 114 such primes, so we need only 19 queries.

剩下应该做的是保证绝对值误差：如果 $X_1\le3$ 我们可以简单地把 $8$ 作为答案输出！若 $X_1\le3$，我们可以确定 $X_2$ 最多有 $3$ 个质因数；若 $X_1\ge4$ 我们需要检查所有小于 $\ ^3\!\!\!\!\sqrt{\dfrac{10^9}{4}}<630$ 的质数。这里有 114 个这样的质数，所以我们只需要 19 次查询。

---

We will also need some queries to find out the exact power for those small prime factors of X we have found. If we have found no more than 2 prime factors, we'll need 1 query, otherwise we'll have to check primes only up to 109/(2⋅3⋅5)−−−−−−−−−−−√3<330, of which there are only 66 so the first part of the solution spends no more than 11 queries.

我们还需要一些询问去找到一些小素数的准确幂次。如果我们发现 $X$ 的素因数个数没有超过 $2$，我们只需要查询 $1$ 次。其他情况我们只需要查询所有小于 $\ ^3\!\!\!\!\sqrt{\dfrac{10^9}{2·3·5}}<330$ 的质数。这个范围内有 $66$ 个质数，所以解决方案的第一部分花费的查询数不超过 $11$

--- 

So we have shown that the solution spends no more than 20 queries. We did some rough estimations, the actual bound for this solution is 17 queries.

到这里我们证明了这个解决方案花费的查询数不会大于 $20$。经过详细的册数，我们发现实际的上限是 $17$ 次。

---

Author's solution: 80407360

出题人的提交记录：[CF-R80407360](https://codeforces.ml/contest/1355/submission/80407360)


---

## 作者：夏子汐 (赞：5)

[在我的博客中查看](https://158593.blog.luogu.org/solution-cf1355f)

# 题意
要求猜一个$1$到$10^9$之间的一个数$X$。

你可以询问一个数$Q$（$1\le Q\le10^{18}$），然后读取到$\gcd(X,Q)$。

在不多于$22$次猜测，得到$X$的质因数个数。

注意：设你的答案为$d$，标准答案为$ans$，只要满足$|ans-d|\le7$或$\frac12\le\frac{ans}{d}\le2$即算正确。

输入格式：

询问："? Q"；猜测："! d"。（注意每次输出后要刷新缓冲区）。

# 个人的做法
既然每次返回$\gcd$，可以利用$\gcd$来得到原来的数的因数。

根据**唯一分解定理**，可设$X=\prod_{i=1}^{n}p_i^{a_i}$，则因数个数为$\prod_{i=1}^n(a_i+1)$。

## 方法一
每次询问问$p_i^{a_i}$，且$p_i^{a_i+1}>10^9$。

e.g.
```
? 536870912			//=2^29（注意这里的"^"是乘方的意思）
? 387420489			//=3^18
? 244140625			//=5^12
```
要在$22$次以内，就只能问到$79$，不可取。

因为$Q\le10^{18}$，可以问$2^{29}\times3^{18}$，但这样也只能问到$139$，无法判别。
## 方法二
“方法一”中的大量询问都会返回$1$，考虑优化这个方法。

每次询问$\prod_{i=last+1}^k{p_i}$，其中$last$指上次询问的$k$，而且$\prod_{i=last+1}^{k+1}{p_i}>10^{18}$，例如第一次询问为

$2\times3\times5\times7\times11\times...\times47=614889782588491410$

如果答案有2这个因数，问$2^{29}$（也可以两个因数一起问），返回$2^w$，那么这个数就有$2$这个因数，且次数为$w$（令$ans$为已知的约数个数，例如知道$2^{19}$后，$ans=19+1=20$）。（这样的询问不会超过$9$次，而且越往后次数越少）

然后可以询问$53\times59\times...\times83$，按照类似的方法。（此次询问$p_i^{a_i}$最多只要$5$次，因为$53\times59\times61\times67\times71\times73>10^9$）

一些解释：

1. 当询问到一个数$X$后（例如第一次后为$47$），如果下一个质数为$p'$，那么若**剩下的数**（指$10^9$除以已知的质因数及其次数，例如已知$2^2$，那么“最大的数”即$2.5\times10^8$）$X'$满足$X'<p'^3$，即可直接输出$2~ans$，因为$X'$一定是由大于等于$p'$的两个质数相乘（**或单独一个质数，或者$X'=1$**）得到，答案为$ans$或$2~ans$或$4~ans$，输出$2~ans$即可。
2. 枚举到$631$剩下的数大于$p'^3$时，分两组情况：如果$ans=1$或$ans=2$，剩下的数最多由$3$个质数相乘，因数个数最多为$2\times8=16$，最少为$1$，输出8即可；否则就输出$2~ans$，因为当$ans>2$时，剩下的数最多为$2\times10^8$，而$631^3=‭251239591‬$，所以最多是由$2$个质数相乘的，1. 中已解释。

## Code

```cpp
#include<iostream>
#define ll long long
using namespace std;
const ll q[22]={2ll*3*5*7*11*13*17*19*23*29*31*37*41*43*47,//每次询问 
				53ll*59*61*63*67*71*73*79*83,
				89ll*97*101*103*107*109*113*127,
				131ll*137*139*149*151*157*163,
				167ll*173*179*181*191*193*197,
				199ll*211*223*227*229*233*239,
				241ll*251*257*263*269*271*277,
				281ll*283*293*307*311*313*317,
				331ll*337*347*349*353*359*367,
				373ll*379*383*389*397*401,
				409ll*419*421*431*433*439,
				443ll*449*457*461*463*467,
				479ll*487*491*499*503*509,
				521ll*523*541*547*557*563,
				569ll*571*577*587*593*599,
				601ll*607*613*617*619*631};
const ll cnt[22]={53,89,131,167,199,//每次询问最大的质数的后面一个 
				241,281,331,373,409,
				443,479,521,569,601,
				641};
const ll prime[205]={2,3,5,7,11,13,17,19,23,29,//质数表 
					31,37,41,43,47,53,59,61,67,71,
				73,79,83,89,97,101,103,107,109,113,
				127,131,137,139,149,151,157,163,167,173,
				179,181,191,193,197,199,211,223,227,229,
				233,239,241,251,257,263,269,271,277,281,
				283,293,307,311,313,317,331,337,347,349,
				353,359,367,373,379,383,389,397,401,409,
				419,421,431,433,439,443,449,457,461,463,
				467,479,487,491,499,503,509,521,523,541,
				547,557,563,569,571,577,587,593,599,601,
				607,613,617,619,631,641,643,647,653,659};
int main(){
	ll t;cin>>t;
	for(ll ans,now,mx;t;--t){
		ans=1,now=0,mx=1000000000;
		for(ll i=0,gcd;i<16;++i){
			cout<<"? "<<q[i]<<endl,cin>>gcd;//询问 
			for(ll g;prime[now]<cnt[i];++now)
				if(gcd%prime[now]==0){
					ll num=1,que=1;cerr<<prime[now]<<endl;
					while(que<mx)que*=prime[now];//计算存在的质因数的次数（e.g. 2^29） 
					cout<<"? "<<que<<endl,cin>>g,mx/=g;//此处是大于1e9的最小数 
					while(g%prime[now]==0)++num,g/=prime[now];//得到次数 
					cerr<<num<<endl;//注：cerr会输出到标准错误输出流，
					//不会被交互程序读取，但是在本地运行时可以看见 
					ans*=num;
				}
			if(mx<cnt[i]*cnt[i]*cnt[i]){//X'>p'^3 
				cout<<"! "<<ans*2<<endl;
				goto N;//跳过跳过后面的特判 
			}
		}
		if(ans==1 || ans==2)cout<<"! 8"<<endl;//绝对值之差小于等于7 
		else cout<<"! "<<ans*2<<endl;N:;//答案在标准答案的二分之一到两倍之间 
	}
}
```

**虽然你用这个代码可以AC，但请不要抄！**

---

## 作者：皎月半洒花 (赞：5)

场外选手。说一说自己的乱搞做法。

一个比较直接的暴力是考虑对每个 $\leq \sqrt{10^9}$ 的素数的最大幂进行 check，然后二分出指数。但是这样做需要 $3300+$ 次的询问…然后考虑如何把状态压一压。发现只需要最多 $10^9$ ，但是可以询问 $10^{18}$，于是可以把相邻状态压一压。~~然后发现还是 WA on 5~~ .

然后又有一个更压的方法，就是考虑每次选取相邻几个质数的最小公倍数，然后这样筛过一遍就可以知道有哪些数要去筛。然后再把这里面的相邻组合…大概就是在上面一个方法外面套一个分组。但这样需要调整分界线。然后…然后就过了 XD


```cpp
#include <cmath>
#include <bitset>
#include <cstdio>
#include <iostream>

using namespace std ;

typedef long long ll ;

const int Mp = 4000 ;

const int Mx = 1000000000 ;

int T, used ;
int pos[Mp], res ;

template <typename T>
void debug(T x, char c = '\n'){ cerr << x << c ; }

template <typename T>
void debug(T *const tp, int minn, int maxn, char v = ' ', char c = '\n'){
    for (int i = minn ; i <= maxn ; ++ i) debug(tp[i], v) ;  cerr << c ;
}

namespace Euler{
	#define MAXN 51000
	bitset <MAXN> vis ;
	int pr[MAXN], A, i, j, cnt ;
	void Ego(){
        int N = sqrt(Mx) ;
		vis[1] = vis[0] = 1 ;
		for (i = 2 ; i <= N ; ++ i){
			if (!vis[i]) pr[++ cnt] = i ;
			for (j = 1 ; j <= cnt ; ++ j){
				if (i * pr[j] > N) break ;
				vis[i * pr[j]] = 1 ;
				if (!(i % pr[j])) break ;
			}
		}
	}
}

int tp ;
int ng ;
int tot ;
ll gp[Mp] ;
int stk[Mp] ;
int lrg[Mp] ;
int rrg[Mp] ;

int main(){
    cin >> T ;
//    for (int i = 1 ; i <= 44 ; ++ i)
//        cout << num[i] << '\n' ;
    Euler :: Ego() ;
    lrg[tot = 1] = 1 ;
    using namespace Euler ;
    int x, y, z, q1, q2 ; ll o = 1 ;
    for (int i = 1 ; i <= cnt ; ++ i)
        pos[i] = log(Mx) / log(pr[i]) ;
    for (int i = 1 ; i <= cnt ; ++ i){
        if (1.0 * o * pr[i] > 1e18)
            gp[tot] = o, rrg[tot] = i - 1, lrg[++ tot] = i, o = 1 ;
        o *= pr[i] ;
    }
//    debug(gp, 1, tot) ;
//    debug(lrg, 1, tot) ;
//    debug(rrg, 1, tot) ;
    while (T --){
        ng = 1 ;
        res = 1 ;
        used = 0 ;
        do {
            tp = 0 ; ++ used ;
            cout << "? " << gp[ng] << endl, cin >> y ;
            for (int i = lrg[ng] ; i <= rrg[ng] ; ++ i)
                if (y % pr[i] == 0) stk[++ tp] = i ; //cout << tp << '\n' ;
            for (int i = 1 ; i <= tp ; ){
                if (used >= 22) break ;
                q1 = 0, q2 = 0 ; x = 1, z = 1 ;
                x = pow(pr[stk[i]], pos[stk[i]]) ;
                if (i < tp)
                    z = pow(pr[stk[i + 1]], pos[stk[i + 1]]) ;
                cout << "? " << 1ll * x * z << '\n' ;
                cin >> y ; ++ used ;
                while (y % pr[stk[i]] == 0)
                    ++ q1, y /= pr[stk[i]] ;
                if (i < tp)
                    while (y % pr[stk[i + 1]] == 0)
                        ++ q2, y /= pr[stk[i + 1]] ;
                res *= (q1 + 1) * (q2 + 1) ; i += 2 ;
//                cout << res << '\n' ;
            }
            ++ ng ;
//            cout << used << "#\n " ;
        } while(used < 22) ;
        cout << "! " << max(res * 2, res + 7) << endl ;
    }
    return 0 ;
}
```

大概算了 一下，发现这个不是很容易卡掉。证明方式大概可以考虑分类讨论 $\approx 10^3$ 的质数个数。

发现这样最多只能 check 到前 $153$ 个质数。考虑此时质数大小已经是 $900$ ，而 $10^9$ 至多分成 $3$ 个在 $10^3$ 左右的质数之积，考虑如果三个质数都没筛到那么 $res=1$ ，在 $+7$ 之后必然符合误差范围；如果只剩下一个质数没被筛到那么 $\times 2$ 之后必然合法；如果剩两个质数没被筛到，那么除去这两个较大的剩下的最大也只有 $1200$ 左右，而 $\leq 1200$ 的数最多含有 $4$ 个不同的质因子，同时用到超过第一个块(即超过前 $15$ 个质数)的最多会有 $1$ 个，毛估估一下发现 $22$ 次是绰绰有余的。 

> 



---

## 作者：MarSer020 (赞：1)

使用了巨大抽象做法，怎么题解区做法看不懂啊？？？？？？？？？

破防实录：

![](https://pic1.imgdb.cn/item/67ced68f066befcec6e27765.png)

$\Large\text{Solution}$

考虑给的 $\frac{1}{2}\le\frac{ans}{d}\le2$ 是什么意思。

观察到一个 $[1,10^9]$ 中的数至多有两个质因子在 $[10^3,10^9]$，于是我们只要求出其在 $[1,10^3]$ 中的所有质因子之积的因子个数 $w$，输出 $2w$ 必然满足条件。

那么题意转化为求出 $n$ 在 $[1,10^3]$ 中的所有质因子。于是我们对于每个 $p_i\le10^3$ 询问 $\gcd\{p_i^{\lfloor\log_{p_i}10^3\rfloor},X\}$ 就可以得到了。发现这样询问次数很多，考虑可以一次询问多个质数，每组从大到小贪心选。

那这样做能不能得到分组数量在 $22$ 以内的构造呢？事实上 $\prod p_i^{\lfloor\log_{p_i}10^3\rfloor}$ 就已经达到了 $10^{432}$ ，所以是不可行的。

考虑优化这个做法。对于一个阈值 $B$，先询问出所有 $[1,B]$ 中的质因子。如果有就再做上面的，否则可以直接认为它的因数个数是少的。观察到 $\sqrt[3]{5\times10^8}\approx788$，这个范围内的质数是可以直接使用上述做法卡进限制的。

那么现在考虑 $B$ 应当取多少。注意到如果一个数因数个数 $d\in[1,15]$，我们可以直接回答 $8$。那么我们只要保证 $B^4\le10^9$ 即可。这样如果不存在 $[1,B]$ 中的质因子，那么因数个数必然 $\le15$。于是我们取 $B=177$，再套用上面的做法，发现我们分出了恰好 $22$ 组。可以通过此题。注意有一些边界。

$\Large\text{Code}$

找出分组代码：

```cpp
#include<bits/stdc++.h>
#define int int64_t
using namespace std;
const int inf=1e18;
int n=788,p[1005],m,mmul=1,cnt,K=40,c[1005];
bool np[1005];
int32_t main(){
	ios::sync_with_stdio(0),cin.tie(0);
	for(int i=2;i<=n;i++){
		if(!np[i])
			p[++m]=i;
		for(int j=1;j<=m&&i*p[j]<=n;j++){
			np[i*p[j]]=1;
			if(!(i%p[j]))
				break;
		}
	}
	for(int i=1,mul=1;i<=K;i++,mul=1){
		while(mul*p[i]<=n)
			mul*=p[i];
		if(p[i]<=50&&(double)mul*mul*mul*p[i]<=1e9)
			mul*=p[i];
		if((__int128)mmul*mul>inf)
			cnt++,cout<<mmul<<',',mmul=1;
		mmul*=mul;
	}
	if(mmul!=1)
		cout<<mmul<<',',mmul=1,cnt++;
	while(1){
		mmul=1;
		for(int i=m;i>K;i--)
			if(!c[i]&&(__int128)mmul*p[i]<=inf)
				mmul*=p[i],c[i]++;
		if(mmul==1)
			break;
		cout<<mmul<<',',cnt++;
	}
	cout<<'\n'<<cnt;
	return 0;
}
```

找到分组后：

```cpp
#include<bits/stdc++.h>
#define int int64_t
using namespace std;
const int a[]={0,1491000255360000,32937398311276511,478743671264220917,70746471270782959,31249487656358033,2312213044985741,202395587171454013,149158072733691997,99637302530329493,72410448629704357,51159497847369007,36738834719671459,22861092512071133,13425528102933757,8517511016337023,977254189227797933,972774662802362507,535829090346428891,166996819598798201,61247129307885343,18506541671175721,34189};
int n=1000,T,mul,x,m,p[1005];
bool np[1005];
int calc(int x){
	int ret=1;
	for(int i=1,cnt;i<=m&&p[i]<=x;i++){
		cnt=0;
		while(!(x%p[i]))
			cnt++,x/=p[i];
		ret*=cnt+1;
	}
	return ret;
}
int32_t main(){
	ios::sync_with_stdio(0),cin.tie(0),cin>>T;
	for(int i=2;i<=n;i++){
		if(!np[i])
			p[++m]=i;
		for(int j=1;j<=m&&i*p[j]<=n;j++){
			np[i*p[j]]=1;
			if(!(i%p[j]))
				break;
		}
	}
	while(T--){
		mul=1;
		for(int i=1;i<=5;i++)
			cout<<"? "<<a[i]<<endl,cin>>x,mul*=calc(x);
		if(mul==1){
			cout<<"! 8"<<endl;
			continue;
		}
		for(int i=6;i<=22;i++)
			cout<<"? "<<a[i]<<endl,cin>>x,mul*=calc(x);
		cout<<"! "<<(mul<<1)<<endl;
	}
	return 0;
}
```

---

## 作者：int08 (赞：1)

## 前言
这是我近期看到最 cute 的一道题。

# Solution

容易发现本题最特殊的一点：

> 设你的答案为 $d$，标准答案为 $ans$，只要满足 $|ans-d|\le 7$ 或 $\frac{1}{2}\le \frac{ans}{d} \le 2$ 即算正确。

想一下这两条有什么用。

前者感觉是解决当 $ans$ 很小的情况，具体怎么解决我也不知道，先看后面吧。
### 第二条作用

根据约数个数公式：$X=p_1^{a_1}p_2^{a_2}\dots p_k^{a_k},d(X)=(a_1+1)(a_2+1)\dots(a_k+1)$，其中 $d(X)$ 是约数个数函数。

容易发现，一个较大的质数对约数个数的影响最大就是乘 $2$，如果它之前出现过这个影响还会变小，那么我们可以用上面这个式子忽略一些较大的质数，具体能忽略几个呢？

假如说我们已经考虑了比较小的一些约数并求出了只考虑它们下约数个数的答案为 $x$，那么最少情况就是外面真的没有约数，答案就是 $x$，所以我们猜测 $2x$ 显然最好，这样答案是 $4x$ 也能通过，我们可以允许外面出现两个我们没找到的质数。

这样的话我们只需要找到 $X$ 所有小于等于 $\sqrt[3]{10^9}=1000$ 的质因子，没找到的最多两个。

### 找质因子

分为两步，先确定质因子是哪些，再确定次数。

我们可以把所有质数分成许多个乘积接近 $10^{18}$ 的块，每次询问一个块。

得到了所有质因子之后，我们对于某个质因子 $p$，询问小于 $10^9$ 里最大的 $p^x$ 就能得到 $p$ 的次数，由于询问值域为 $[1,10^{18}]$ 还可以把两个询问乘起来一次搞定。

计算发现最多 $9$ 个质因子，此时由于最后一个不可能出现次数大于 $1$，故后半段只需要 $4$ 次询问。

留给确定质因子还有 $18$ 次询问，发现只能问到 $700$ 左右，还差一些。

我开始还以为可以把范围优化到开四次方，但是似乎并不能，咋办？第一条该发挥作用了。

### 第一条作用

$|ans-d|\le7$ 显然是给 $ans$ 较小时候准备的，比如我们只考虑了较小约数时候答案为 $x$，当 $x=1,2$ 等的时候我们不必乖乖猜测 $2x$，可以改用 $x+7$。

作用就是当 $x\le2$ 的时候，这种策略允许外面出现三个质因子了。

那会不会当 $x\ge 3$ 的时候，由于较小部分已经有一些质因子，外面就取不出三个了呢？

还真是，考虑最坏情况下 $x=3$，较小部分只找到了 $2^2=4$，外面最多还剩 $\frac{10^9}{4}=2.5\times 10^8$，发现 $\sqrt[3]{2.5\times10^8}≈630$，小于我们之前说过的能问到的 $700$ 左右。

这道题目就得到了解决。

## AC Code

那一长串数字是提前打表的结果。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool isp(int x)
{
	for(int i=2;i*i<=x;i++) if(x%i==0) return 0;
	return 1;
}
int i,T;
vector<int> prime;
int x,yz[20],yzs,yzn[20],q17[20]={0,614889782588491410,38655288426304091,22125549654501673,316773187163046517,9879251463499721,39049078408188253,108538288030848139,309619196508457007,796229312542859009,4064625951224869,6860596063872959,10626236358872441,17092564102090369,30150641449095443,43889293834596251,60888412234461547,83850965748659689};
int getmx(int x)
{
	int ans=1;
	while(ans*x<=1000000000) ans*=x;
	return ans;
}
signed main()
{
	for(i=2;i<=1000;i++) if(isp(i)) prime.push_back(i);
	cin>>T;
	while(T--)
	{
		for(i=1;i<=17;i++)
		{
			cout<<"? "<<q17[i]<<endl;
			cin>>x;
			if(x>1)
				for(auto p:prime) if(x%p==0)
					x/=p,yz[++yzs]=p;	
		}
		for(i=1;i<yzs;i+=2)
		{
			cout<<"? "<<getmx(yz[i])*getmx(yz[i+1])<<endl;
			cin>>x;
			while(x%yz[i]==0) x/=yz[i],yzn[i]++;
			while(x%yz[i+1]==0) x/=yz[i+1],yzn[i+1]++;
		}
		if(i==yzs)
		{
			cout<<"? "<<getmx(yz[i])<<endl;
			cin>>x;
			while(x%yz[i]==0) x/=yz[i],yzn[i]++;
		}
		int ans=1;
		for(i=1;i<=yzs;i++) ans*=(yzn[i]+1);
		if(ans<=2) cout<<"! "<<ans+7<<endl;
		else cout<<"! "<<ans*2<<endl;
		for(i=1;i<=yzs;i++) yzn[i]=yz[i]=0;yzs=0;
	}
	return 0;
}
```
# The End.

---

## 作者：OrezTsim (赞：1)

[CF1355F Guess Divisors Count](https://www.luogu.com.cn/problem/CF1355F) 对于一个正整数 $x \space (1 \le x \le 10^9)$ 的因数个数，每一次可以询问一个正整数 $Q \space (1 \le Q \le 10^{18})$，交互库会返回 $\gcd(x,Q)$。最多可以询问 $22$ 次。最后需要你给出这个数的因数个数，若你给出的 $ans$ 与精确答案 $d$ 满足以下两个条件中的任意一个则视为正确。

- $|ans-d| \le 7$
- $\dfrac{1}{2} \le \dfrac{ans}{d} \le 2$

---

求因数个数，根据唯一分解定理，对于正整数 $x$ 有 $ans=\prod\limits_{i=1}^n(p_i+1)$，其中 $p_i$ 表示 $x$ 的第 $i$ 个质因子的指数。考虑从这个意义上枚举质因子，最后算乘积就好了。

但是，由于询问次数不能超过 $22$，考虑对询问的过程进行优化。

---

1. 怎么快速得到某个质因子的指数？

朴素做法显然是把每一个可能的指数询问一遍。但是想想就知道，对于一个确定存在的质因子 $P$，不如直接用 $P^k$ 去询问 $\gcd$：这里的 $k$ 表示第一个满足 $P^k\ge x_{\max}$ 的正整数。同时，这里的 $x_{\max}$ 直接设为上界 $10^9$ 即可，询问 $Q=P^k$ 就可以快速得到它的指数。

2. 怎么快速得到 “ 确定存在的质因子 $P$ ”？

由于允许的询问数量极小，所以考虑批量询问。由于$Q \space (1 \le Q \le 10^{18})$，想到把一串质数压成一个大数进行询问，这样就可以得到存在的质因子：从而可以通过 1 中做法进行处理。

3. 但是即使是这样优化了也跑不进 $22$ 次啊？

还没完呢！由于这道题需要给出模糊答案，我们就可以进行模糊的处理。

先前的过程中，每一次询问完压成的大数的段，我们都可以发现，如果当前剩余的 $\dfrac{x_{\max}}{\prod P}$ 小于这一段后第一个数（不妨设为 $g$，当前得到的答案为 $ans$）的立方，即 $g^3$，此时的因数个数一定会被控制在 $[ans,(3+1)ans]$，即 $[ans,4ans]$ 间，因为 $g^3$ 对于答案的贡献为 $4$，而最坏情况为当前剩余的数无法产生新的贡献（即为 $1$），所以折中输出 $2ans$，必定正确。

处理完后，我们发现，还没有用上差不超过 $7$ 的条件。

所以考虑设置一个阈值使得答案可以通过特判得到。

由于上述处理时，立方可以保证 $\dfrac{1}{2}d \le ans \le 2d$，得到阈值范围在三次方根内。

充分发扬人类智慧发现这种方法取到 $700$ 左右可以通过，下面分两种情况讨论。

- 如果当前 $ans=1$ 或 $ans=2$：剩下的数最多由三个质数相乘得到，最终答案最少为 $1 \times 1 = 1$，最多为 $2 \times 2^3=16$，输出 $8$ 可以折中。
- 如果当前答案不为 $1$ 或 $2$：考虑最坏情况，当前答案为 $3$，前面取到 $2^2=4$。此时剩余的数最多为 $2.5 \times 10^8$。发现无法承受立方级别的新增质因子积（由于值域为 $700$ 左右往上），所以最多为平方级别的贡献。此时答案最少为 $ans$，最多为 $(1+1)^2ans=4ans$。折中为 $2ans$ 即可。

这题就做完了，实现细节有点多。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int Lim = 1e9;
const int nxt[30] = {53, 89, 131, 167, 199, 241, 281, 331, 373, 409, 443, 479, 521, 569, 601, 641};
const int quer[30] = {614889782588491410, 27362732256821997, 15031861979012587, 1436339604664397, 6797529210792599, 27105383499717587, 82562146564818163, 220730699740396663, 628272447786387869, 3352982574921113, 5910838774210927, 9060769122162619, 14632963178572339, 25286434350286931, 39088031966400007, 53892559501986383};
const int p[300] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659};

int T, ans, Limit;
inline void ask(int x) { cout << "? " << x << endl; }
inline void guess(int x) { cout << "! " << x << endl; }

signed main() {
  cin >> T;
  while (T--) {
    Limit = Lim, ans = 1; int pos = 0; bool ok = false;
    for (int i=0; i<16; ++i) {
      ask(quer[i]); int gcd; cin >> gcd;
      for (; p[pos]<nxt[i]; ++pos) {
        if (gcd%p[pos]) continue;
        int pw = 1, bas = 0; while (pw<Limit) pw *= p[pos];
        ask(pw); int res; cin >> res, Limit /= res;
        while (!(res%p[pos])) ++bas, res /= p[pos]; ans *= (bas+1);
      }
      if (Limit<nxt[i]*nxt[i]*nxt[i]) {
        guess(ans*2); ok = true;
        goto xde;
      }
    }
    if (ok) continue;
    if (ans<=2) guess(8); else guess(ans*2);
    xde:;
  }
  return 0;
}
```

---

## 作者：qinyubo (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1355F)

大概题意：交互库想一个 $[1,10^9]$ 的数 $X$，你可以给定一个 $[1,10^{18}]$ 的数 $Q$，交互库返回 $\gcd(X,Q)$。要你在 $22$ 次之内得到 $X$ 的因数个数。

设你的答案为 $d$，标准答案为 $ans$，只要满足 $|ans-d|\le7$ 或 $\dfrac12\le\dfrac{ans}{d}\le2$ 即算正确。

思维题。

容易想到的是对于每个 $X$ 的质因数确定其次数，再把次数加一乘起来就可以了。

具体操作是对于每个质数询问其最大的小于 $10^9$ 的幂次，得到的结果的次数就是 $X$ 包含的这个质数的次数。一个没什么用的优化是把两个质数的最大幂乘起来，一次询问两个质数。

但是 $10^9$ 的质数实在是太多了，而对于大多数质数 $X$ 询问的值都会返回 $1$，所以考虑先求出 $X$ 有哪些质因子。

我们把一些质数乘起来（比如 $2\times3\times5\times7\times11\times\cdots$），一直乘到刚好不超过 $10^{18}$，询问后求出 $X$ 包含哪些质因数再询问这些质因数的次数。

但是还是不能在 $22$ 次询问完，发现可以不用求出具体的值，即只要满足 $\dfrac12\le\dfrac{ans}{d}\le2$ 即算正确。

那么我们相当于有 $4$ 倍的误差空间。因此想到留两个质因子不询问，即只暴力询问到 $1000$ 以内的质数，$X$ 剩下不超过两个质因子，剩下的质因子对答案的贡献不超过 $4$ 倍，输出当前答案的两倍就可以过了。

但是还是不能在 $22$ 次询问完，考虑用上 $|ans-d|\le7$ 的条件。

如果求出来的答案超过 $2$，则答案至少是 $3$，前面的质数乘起来至少是 $2^2=4$，剩下来的质因子之积至多是 $10^9\div4=2.5\times10^8$，所以可以把质数的上界调到 $\sqrt[3]{2.5\times10^8}\approx630$，这时剩下来不超过两个质因子，对答案的贡献不超过 $4$ 倍，折中输出当前答案的两倍就行了。

如果求出来的答案不超过 $2$，那么有可能剩下来 $3$ 个质因子，答案最小是 $1$，最大是 $2\times2^3=16$，折中输出 $8$ 就行了。

通过打表可得，使用 $630$ 以内的质数不超过 $10^{18}$ 的连乘积求出 $X$ 有哪些质因子需要 $16$ 次询问，$X$ 不超过 $9$ 个质因子（$2\times3\times5\times7\times11\times13\times17\times19\times23\times29>10^9$），结合把两个质数最大幂乘起来询问的方法可以用 $5$ 次求出其最大幂，加起来 $21$ 次询问，可以通过。

代码里 `p[]` 存的是质数，`q[]` 存的是质数的 $16$ 个连乘积，`r[]` 存的是 $16$ 个连乘积的分隔点（即 $q_x=\prod\limits_{i=r_{_{x-1}}}^{r_{_x}-1}p_i$）`s[]` 存的是质数的最大幂。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
namespace QYB {
    ll p[] = {
        1000000007ll, 2ll,   3ll,   5ll,   7ll,   11ll,  13ll,  17ll,  19ll,
        23ll,  29ll,  31ll,  37ll,  41ll,  43ll,  47ll,  53ll,  59ll,  61ll,
        67ll,  71ll,  73ll,  79ll,  83ll,  89ll,  97ll,  101ll, 103ll, 107ll,
        109ll, 113ll, 127ll, 131ll, 137ll, 139ll, 149ll, 151ll, 157ll, 163ll,
        167ll, 173ll, 179ll, 181ll, 191ll, 193ll, 197ll, 199ll, 211ll, 223ll,
        227ll, 229ll, 233ll, 239ll, 241ll, 251ll, 257ll, 263ll, 269ll, 271ll,
        277ll, 281ll, 283ll, 293ll, 307ll, 311ll, 313ll, 317ll, 331ll, 337ll,
        347ll, 349ll, 353ll, 359ll, 367ll, 373ll, 379ll, 383ll, 389ll, 397ll,
        401ll, 409ll, 419ll, 421ll, 431ll, 433ll, 439ll, 443ll, 449ll, 457ll,
        461ll, 463ll, 467ll, 479ll, 487ll, 491ll, 499ll, 503ll, 509ll, 521ll,
        523ll, 541ll, 547ll, 557ll, 563ll, 569ll, 571ll, 577ll, 587ll, 593ll,
        599ll, 601ll, 607ll, 613ll, 617ll, 619ll, -1ll
    }, q[] = {
        0ll, 614889782588491410ll, 38655288426304091ll, 22125549654501673ll, 316773187163046517ll,
        9879251463499721ll, 39049078408188253ll, 108538288030848139ll, 309619196508457007ll,
        796229312542859009ll, 4064625951224869ll, 6860596063872959ll, 10626236358872441ll,
        17092564102090369ll, 30150641449095443ll, 43889293834596251ll, 234118799ll, -1ll
    }, r[] = {
        1ll, 16ll, 25ll, 33ll, 41ll, 48ll, 55ll, 62ll, 69ll, 76ll, 82ll, 88ll, 94ll, 100ll, 106ll, 112ll, 115ll, -1ll
    }, s[] = {
        1ll, 536870912ll, 387420489ll, 244140625ll, 282475249ll, 214358881ll, 815730721ll,
        410338673ll, 893871739ll, 148035889ll, 594823321ll, 887503681ll, 69343957ll,
        115856201ll, 147008443ll, 229345007ll, 418195493ll, 714924299ll, 844596301ll,
        20151121ll, 25411681ll, 28398241ll, 38950081ll, 47458321ll, 62742241ll, 88529281ll,
        104060401ll, 112550881ll, 131079601ll, 141158161ll, 163047361ll, 260144641ll,
        294499921ll, 352275361ll, 373301041ll, 492884401ll, 519885601ll, 607573201ll,
        705911761ll, 777796321ll, 895745041ll, 5735339ll, 5929741ll, 6967871ll, 7189057ll,
        7645373ll, 7880599ll, 9393931ll, 11089567ll, 11697083ll, 12008989ll, 12649337ll,
        13651919ll, 13997521ll, 15813251ll, 16974593ll, 18191447ll, 19465109ll, 19902511ll,
        21253933ll, 22188041ll, 22665187ll, 25153757ll, 28934443ll, 30080231ll, 30664297ll,
        31855013ll, 36264691ll, 38272753ll, 41781923ll, 42508549ll, 43986977ll, 46268279ll,
        49430863ll, 51895117ll, 54439939ll, 56181887ll, 58863869ll, 62570773ll, 64481201ll,
        68417929ll, 73560059ll, 74618461ll, 80062991ll, 81182737ll, 84604519ll, 86938307ll,
        90518849ll, 95443993ll, 97972181ll, 99252847ll, 101847563ll, 109902239ll, 115501303ll,
        118370771ll, 124251499ll, 127263527ll, 131872229ll, 141420761ll, 143055667ll,
        158340421ll, 163667323ll, 172808693ll, 178453547ll, 184220009ll, 186169411ll,
        192100033ll, 202262003ll, 208527857ll, 214921799ll, 217081801ll, 223648543ll,
        230346397ll, 234885113ll, 237176659ll
    }, ans;
    int main() {
        int t; scanf("%d", &t);
        while (t--) {
            ans = 1; vector<ll> v;
            for (int i = 1; ~q[i]; i++) {
                printf("? %lld\n", q[i]); fflush(stdout);
                ll res; scanf("%lld", &res);
                for (int j = r[i - 1]; j < r[i]; j++) {
                    if (res % p[j] == 0) v.push_back(j);
                }
            } if (v.size() & 1) v.push_back(0); // 由于后面要把质数最大幂两两乘在一起询问，如果由奇数个质因子就塞进去一个不会出现的大质数
            // v 里面存的是 X 所有质因数的编号
            for (int i = 0; i < v.size(); i += 2) {
                printf("? %lld\n", s[v[i]] * s[v[i + 1]]); fflush(stdout); // 两两组合询问
                ll cnt = 1, res; scanf("%lld", &res);
                while (res % p[v[i]] == 0) {
                    res /= p[v[i]]; ++cnt;
                } ans *= cnt; cnt = 1;
                while (res % p[v[i + 1]] == 0) {
                    res /= p[v[i + 1]]; ++cnt;
                } ans *= cnt;
            } if (ans <= 2) printf("! 8\n"); // 特判
            else printf("! %lld\n", ans * 2);
        } return 0;
    }
} int main() {
    return QYB::main();
}
```

---

## 作者：RockyYue (赞：0)

### 1355F

要求猜一个 $1$ 到 $10^9$ 之间的一个数 $X$。

你可以询问一个数 $Q$（$1\le Q\le10^{18}$），然后得到 $\gcd(X,Q)$。

请你在不多于 $22$ 次询问后算出 $X$ 的因数个数。

注意：设你的答案为 $d$，标准答案为 $ans$，只要满足 $|ans-d|\le7$ 或 $\dfrac12\le\dfrac{ans}{d}\le2$ 即算正确。

### Sol

- 因数个数考虑指数加一连乘，需要知道其分解后每个质因数的指数。
- 想到对每个质因数分别处理，枚举质数 $p$，找最大的 $a_i$ 使得 $p_i^{a_i}\le 10^9$，询问 $p_i^{a_i}$ 即可得到 $X$ 中 $p$ 的次数。
  - 这种方法不优的原因在于，需要枚举的质数集过大，真正需要的只有是 $X$ 因数那部分，且没有合理利用误差范围。

- 不妨先找出 $X$ 分解中含有的质数：将质数从小到大排列，然后分段，要求每段尽量长且乘积 $\le 10^{18}$，每次询问一段，再对得到 $\gcd$ 中含有的质数进行上述询问，这种询问至多 $8$ 次（前 $9$ 个质数乘积 $10^9$）。
  - 想减少整段询问次数，利用大质数在 $X$ 中次数不会高。一次幂对因数个数贡献为 $\times 2$，二次为 $\times 3$，如果可以知道最大几个质数的幂次，可以利用第二种误差估计。
  - 估计上界，看当前得到的，前若干个质数在 $X$ 中贡献，再至多乘多少保证结果 $\le 10^9$，设为 $lim$，这个数大于等于后面更大质数贡献，设为 $c$（有可能 $c=1$）。
  - 不知道具体分解形式，只能通过值来估计，设当前计算过贡献的最大质数为 $P$。
    1. $lim<P^2$，则 $c$ 是一个更大质数或 $1$，继续尝试更优。
    2. $lim< P^3$，则 $c$ 表示成 $1$ 或 $p$ 或 $p_1\cdot p_2$ 或 $p^2$，其对因数个数的贡献在 $\times 1$ 到 $\times 4$ 之间，对当前答案 $\times 2$ 输出即可。

- 到这里，一段的询问至多 $16$ 次。
- 若最终的 $lim>P^3$，即可能有三个及以上质数相乘。
  - 得到此时 $P=631$，后三个质数乘积略大于 $2.6e8$，故前面至多一个质数贡献过，前面答案记录为 $1$ 或 $2$。
  - 利用误差，最终答案至多为 $2\times 2^3=16$，则输出 $8$ 可以将 $[1,16]$ 囊括在误差范围内。

---

## 作者：Inui_Sana (赞：0)

一个有点乱搞感觉的做法。

直接讲结论：每次取出最小的若干个乘积 $<10^{18}$ 的质数相乘询问，每次如果问出 $p\mid x$ 就再问一次判断有几个 $p$ 的因子，更新当前 $ans$ 和剩下因数乘积的上界 $lim$。如果全部询问用完就输出 $\left\lfloor\dfrac{9\times ans}{2}\right\rfloor$，如果枚举到的质数 $p^3>\lim$ 就输出 $ans\times 2$。

先讲后一种回答为什么是对的：在这种情况下，$\ge p$ 的质数对答案的贡献最多是 $\times 4$，最少是 $\times 1$，则输出 $ans\times 2$ 一定两倍范围内。

第一种回答就要复杂一点，其满足的是 $|ans-d|\le 7$ 这种情况。容易发现，我们一定是可以将 $\sqrt[4]{10^9}$ 内的质数问完的（只需要 $5$ 次），所以真实答案一定在 $[ans,ans\times 8]$ 的范围内。于是我们就需要保证回答时 $ans\le 2$。

此时发现若 $ans>2$，$\sqrt[3]{lim}\le630$，$\le 630$ 的质数需要 $16$ 次问完，也就是说这种情况**会直接用第二种回答**！如果 $lim$ 再变小，虽然可能前面需要的询问也会变多，但是毛估估一下 $lim$ 下降的很快，所以是可以保证 $ans>2$ 时全部都是用第二种回答的。

后来又想到，其实 $ans=2$ 时似乎也可以只用第二种回答？因为 $\sqrt[3]{5\times10^8}<800$ 只用 $20$ 次，加上前面问 $2$ 的幂次的 $1$ 次也是够的，更大就更不用说了。不过 $ans=1$ 的情况也是要用第一种处理的。

code：

```cpp
int n,m;
vector<int> g;
bool isPrime(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			return 0;
		}
	}
	return 1;
}
il ll ask(int op,ll x){
	if(op==1){
		printf("! %lld\n",x);
		fflush(stdout);
		return 0;
	}
	printf("? %lld\n",x);
	fflush(stdout);
	ll ret;scanf("%lld",&ret);
	return ret;
}
void Yorushika(){
	m=1e9;int cnt=0,ans=1;ll sum=1;
	const ll mx=1e18;
	g.clear();
	rep(i,2,1000){
		if(isPrime(i)){
			if(sum>mx/i){
				ll x=ask(0,sum);
				cnt++;
				if(cnt==22){
					ask(1,ans*9/2);
					return;
				}
				for(int j:g){
					if(x%j==0){
						ll y=j;
						while(y<1e9){
							y*=j;
						}
						ll x=ask(0,y),z=0;
						m=m/x+1;
						while(x>1){
							x/=j,z++;
						}
						ans*=(z+1);
						if(++cnt==22){
							ask(1,ans*9/2);
							return;
						}
					}
				}
				if(1ll*i*i*i>m){
					ask(1,ans*2);
					return;
				}
				sum=i,g.clear(),g.eb(i);
			}else{
				sum*=i,g.eb(i);
			}
		}
	}
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：happybob (赞：0)

介绍一个比较好想的做法。

如果我们能问出所有质因数的次数就可以直接得到因子数，然而我们不可能问这么多质数。

一个想法是考虑比较大的质数我们可以不用询问，因为我们并不要求准确答案。

一个直接想法是只询问 $10^3$ 以内的质数，这样 $10^3$ 以上的质数最多也只会出现两个，对答案的贡献是 $4$ 倍。我们只需要输出前面这些质数算出的因子数量乘以 $2$ 即可。

但事实上可以发现 $10^3$ 以内的质数有点多了，询问次数至少要 $25$ 次。无法通过。我们考虑 $\sqrt[3]{\dfrac{10^9}{4}} \approx 629$ 以内的质数，事实上经过计算只考虑这以内的质数询问次数是符合条件的。但是后面造成的误差呢？考虑分情况讨论：

1. $629$ 以内没有质因数，注意到 $630^4>10^9$，所以原数最多有 $8$ 个因数，直接输出 $8$ 即可。

2. $629$ 以内只有一个质因数，质因数次数为 $1$。那么至少是 $2$。此时后面最多有三个质因数，因数个数最多是 $16$，至少是 $2$，直接取答案为 $9$ 即可满足限制。

3. $629$ 以内有大于 $1$ 个质因数，或者有一个质因数但次数为 $2$。此时前面乘积 $\geq 4$。注意到 $630^3 \times 2^2 > 10^9$，所以后面至多只有 $2$ 个质因数，即 $4$ 倍贡献。直接输出前面因数个数乘以 $2$ 即可。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#ifndef ONLINE_JUDGE
#include <__msvc_int128.hpp>
#endif // !ONLINE_JUDGE
#include <queue>
using namespace std;

const int N = 1005;

using ll = long long;
vector<int> prime;
bool vis[N];

void Init()
{
	for (int i = 2; i <= 629; i++)
	{
		if (!vis[i]) prime.emplace_back(i);
		for (auto& j : prime)
		{
			if (j * i > 629) break;
			vis[i * j] = 1;
			if (i % j == 0) break;
		}
	}
}

#ifndef ONLINE_JUDGE
#define i128 _Signed128
#else
#define i128 __int128_t
#endif

ll query(ll x)
{
	cout << "? " << x << "\n";
	cout.flush();
	ll y;
	cin >> y;
	return y;
}

int t;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	Init();
	cin >> t;
	while (t--)
	{
		int cnt = 0;
		i128 res = 1;
		vector<int> ve, exist;
		for (auto& i : prime)
		{
			res = res * i;
			if (res > (ll)1e18)
			{
				ll y = query((ll)(res / i));
				for (auto& j : ve)
				{
					if (y % j == 0)
					{
						exist.emplace_back(j);
					}
				}
				res = i;
				ve.clear(), ve.shrink_to_fit();
			}
			ve.emplace_back(i);
		}
		ll y = query((ll)(res));
		for (auto& j : ve)
		{
			if (y % j == 0)
			{
				exist.emplace_back(j);
			}
		}
		int ans = 1;
		for (int i = 0; i + 1 < exist.size(); i += 2)
		{
			ll v1 = exist[i], v2 = exist[i + 1];
			while (v1 * exist[i] <= (ll)1e9) v1 *= exist[i];
			while (v2 * exist[i + 1] <= (ll)1e9) v2 *= exist[i + 1];
			int k1 = 1, k2 = 1;
			ll y = query(v1 * v2);
			ll c1 = exist[i], c2 = exist[i + 1];
			while (y % (c1 * exist[i]) == 0) c1 *= exist[i], k1++;
			while (y % (c2 * exist[i + 1]) == 0) c2 *= exist[i + 1], k2++;
			ans = ans * (k1 + 1) * (k2 + 1);
		}
		if (exist.size() & 1)
		{
			ll v1 = exist.back();
			while (v1 * exist.back() <= (ll)1e9) v1 *= exist.back();
			int k1 = 1;
			ll y = query(v1);
			ll c1 = exist.back();
			while (y % (c1 * exist.back()) == 0) c1 *= exist.back(), k1++;
			ans = ans * (k1 + 1);
		}
		if (ans == 1) cout << "! 8" << "\n";
		else
		{
			if (ans == 2) cout << "! 9\n";
			else cout << "! " << ans * 2 << "\n";
		}
		cout.flush();
	}
	return 0;
}
```

---

