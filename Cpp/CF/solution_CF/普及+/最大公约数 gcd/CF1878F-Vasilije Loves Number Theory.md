# Vasilije Loves Number Theory

## 题目描述

Vasilije is a smart student and his discrete mathematics teacher Sonja taught him number theory very well.

He gave Ognjen a positive integer $ n $ .

Denote $ d(n) $ as the number of positive integer divisors of $ n $ , and denote $ gcd(a, b) $ as the largest integer $ g $ such that $ a $ is divisible by $ g $ and $ b $ is divisible by $ g $ .

After that, he gave Ognjen $ q $ queries, and there are $ 2 $ types of queries.

- $ 1 $ , $ x $ — set $ n $ to $ n \cdot x $ , and then answer the following question: does there exist a positive integer $ a $ such that $ gcd(a, n) = 1 $ , and $ d(n \cdot a) = n $ ?
- $ 2 $ — reset $ n $ to its initial value (before any queries).

Note that $ n $ does not get back to its initial value after the type 1 query.

Since Ognjen is afraid of number theory, Vasilije promised him that after each query, $ d(n) \le 10^9 $ , however, even with that constraint, he still needs your help with this problem.

## 说明/提示

In the first test case, we initially have $ n=1 $ .

After the first query: $ n=1 $ , $ d(n)=1 $ , so by taking $ a = 1 $ , $ d(n \cdot a) = n $ , and the answer to this query is "YES".

After the second query: $ n=2 $ , $ d(n)=2 $ , we can, again, take $ a = 1 $ , $ d(n \cdot a) = n $ , and the answer to this query is "YES".

After the third query $ n=1 $ , and this is a type $ 2 $ query so we don't answer it.

After the fourth query: $ n=8 $ , and by taking $ a=3 $ , $ d(n \cdot a) = d(24) = 8 = n $ , so the answer is "YES".

After the fifth query: $ n=72 $ , now we can take $ a=637 $ to get $ n \cdot a = 45864 $ , and $ d(n \cdot a) = 72 = n $ , so the answer is "YES".

In the second test case, we initially have $ n=20 $ .

After the first query: $ n=60 $ , and the answer is "YES".

After the second query: $ n=20 $ , this is a type $ 2 $ query, so we don't answer it.

After the third query: $ n=140 $ , and it can be proven that no matter which positive integer $ a $ we take, $ d(n \cdot a) $ will never be equal to $ n $ , so the answer to this query is "NO".

After the fourth query: $ n=1680 $ . It can be proven that there exists a positive integer $ a $ , such that $ d(n \cdot a) = n $ , so the answer is "YES".

## 样例 #1

### 输入

```
7
1 5
1 1
1 2
2
1 8
1 9
20 4
1 3
2
1 7
1 12
16 10
1 6
1 6
1 10
1 9
1 1
1 9
1 7
1 3
1 2
1 10
9 1
1 3
8 1
1 2
8 3
1 5
1 8
1 10
11 5
1 8
1 2
1 1
1 3
1 1```

### 输出

```
YES
YES
YES
YES

YES
NO
YES

YES
NO
YES
YES
YES
NO
YES
NO
YES
YES

NO

NO

YES
NO
NO

YES
NO
NO
NO
NO```

# 题解

## 作者：ran_qwq (赞：16)

结论：问题可转化为 $n$ 是否能被 $d(n)$ 整除。

---

证明：

考虑这两个条件。

1. $\gcd(a,n)=1$。

设 $f(x,p)$ 为满足 $p^y\mid x$ 的最大非负整数 $y$，其中 $p$ 为质数。也就是 $x$ 中质数 $p$ 的个数。

则对于每个质数 $p$，$f(a,p)=0$ 或 $f(n,p)=0$。否则 $p\mid a,p\mid n$，$\gcd(a,n)\ne1$。

2. $d(n\cdot a)=n$。

根据唯一分解定理，$d(x)=\prod\limits_{p\mid x,p\in prime}f(x,p)+1$。

又因 $\gcd(a,n)=1$，所以不存在质数 $p$ 使得 $f(a,p)\ne0,f(n,p)\ne0$。

所以 $d(n\cdot a)=d(n)\cdot d(a)$。

如果 $d(n)\nmid n$，则无论 $a$ 是多少都无法使 $d(n\cdot a)\mid n$。

如果 $d(n)\mid n$，则 $d(a)=\dfrac{n}{d(n)}$。$a$ 可以是任一个满足 $\gcd(a,n)=1$ 的，可以表示为一质数 $p$ 的 $\dfrac{n}{d(n)}-1$ 次方的数。

---
题目又保证了在任何时候，$d(n)\le10^9$。所以可以开个 map 记录初始时每个质数 $p$ 的 $f(n,p)$，算出 $d(n)$。

$1$ 操作更新 $f(n,p)$ 和 $d(n)$。$2$ 操作把 $f(n,p)$ 和 $d(n)$ 设为初始状态。

询问时判断是否有质数 $p$ 满足 $p\mid d(n),f(d(n),p)>f(n,p)$ 即可。

如果有就表明 $d(n)\nmid n$，输出 NO，否则输出 YES。

这些可以用类似分解质因数的方法实现，时间复杂度 $O(q\sqrt V\log\sqrt V)$，其中 $V$ 表示值域，小于等于 $10^9$。

---
[CF 提交记录](https://codeforces.com/contest/1878/submission/228775133)

---

## 作者：StayAlone (赞：5)

## 题意

令 $d(x)$ 表示 $x$ 的正因子数量，给定 $n,q$。现有两种操作：

1. 给定 $x$，令 $n\gets n\cdot x$。同时询问是否存在一个正整数 $a$ 满足 $\gcd(a,n)=1$ 且 $d(n\cdot a)=n$。

2. 将 $n$ 还原为最初的值。

数据保证任何时刻，$d(n)\leq 10^9$。

## 思路

容易发现，若 $\gcd(a,b)=1$，则 $d(a\cdot b) = d(a)\cdot d(b)$。

那么考虑维护 $d(n)$，合法的 $a$ 存在，当且仅当现在的 $d(n)$ 是 $n$ 的因数。

注意到任何时刻，$d(n)\leq 10^9$。每多**一种**质因数，$d(n)$ 至少翻一倍，所以最多只有 $\log v$ 种不同的质因数，考虑用 map 维护。

$d(n)$ 直接使用指数加一再连乘即可算出，接下来需要计算 $n\bmod d(n)$。由于 $a\times b\bmod p = (a\bmod p)\times (b\bmod p)\bmod p$，只需要遍历一遍 map，对于 $p_i^{k_i}$，可以直接暴力乘（因为指数同样最多是 $\log v$ 的）或者快速幂。

由于每次更新 map 需要分解质因数，时间复杂度大概是 $\mathcal O(q(\sqrt v + \log v\log\log v))$。跑得飞快，15 ms。

[AC record](https://codeforces.com/contest/1878/submission/225445082)

```cpp
int n, q;
map <int, int> now, org;
 
il int qpow(ll a, int b, int mod) {
	ll ans = 1;
	while (b) {
		if (b & 1) (ans *= a) %= mod;
		(a *= a) %= mod; b >>= 1;
	} return ans;
}
 
int main() {
	for (int T = read(), op, t; T--; puts("")) {
		read(n, q); now.clear(); int x = n;
		rep1(i, 2, sqrt(x)) {
			while (x % i == 0) x /= i, ++now[i];
		}
		if (x > 1) ++now[x];
		x = n; org = now;
		
		while (q--) {
			read(op);
			if (op == 2) now = org;
			else {
				read(t);
				rep1(i, 2, sqrt(t)) {
					while (t % i == 0) t /= i, ++now[i];
				}
				if (t > 1) ++now[t];
				int ans = 1; ll mod = 1;
				for (auto v : now) ans *= v.snd + 1;
				for (auto v : now) (mod *= qpow(v.fst, v.snd, ans)) %= ans;
				puts(mod % ans ? "NO" : "YES");
			}
		}
	}
	rout;
}
```

考虑加强。令 $q=10^6$，只需要换上 $\mathcal O(v)$ 筛法预处理，$\mathcal O(\log v)$ 分解质因数的方法，即可做到 $\mathcal O(q\log v\log\log v)$。

~~再强行上个哈希表代替 map，时间复杂度成为 $\mathcal O(q\log v)$~~。

---

## 作者：WrongAnswer_90 (赞：3)

[CF1878F Vasilije Loves Number Theory](https://www.luogu.com.cn/problem/CF1878F)

首先约数个数是积性函数，题目中要求 $\gcd(n,a)=1$，所以 $a$ 和 $n$ 互质，$n=d(a)d(n)$ ,于是问题转化为 $n$ 是否整除 $d(n)$。

观察题目，$n$ 可能会非常大，但这也启发我们把它质因数分解来存储，而对于 $d(n)$ 直接用一个变量 $ans$ 存下来，考虑 $n\times x$ 之后 $ans$ 会有什么变化。

设操作前 $n=p_1^{c_1}p_2^{c_2}\cdots p_k^{c_k}$，则 $ans=(c_1+1)(c_2+1)\cdots(c_k+1)$，直接乘 $x$ 是不好算的，考虑把 $x$ 也拆成若干个质数依次计算，对于 $x$ 的每个质因子 $p_i$，$ans$ 会变成 $(c_1+1)(c_2+1)\cdots(c_i+2)\cdots(c_k+1)$，所以贡献是好计算的。

代码细节比较多，不太好写，实际实现可以用 map 存储每一位质因数的位置，对于操作 $2$ 直接记下开始的状态暴力 memset 即可，复杂度 $\mathcal O(q(\log n+\sqrt x))$。

```cpp
int T,q,n,ans,prans,cnt,stcnt,all,pr[2001],st[2001],p[2001],now[2001];
map<int,int> mp1,mpr;
void mian()
{
	read(T);int x,y;
	while(T--)
	{
		read(n,q),ans=1,memset(st,0,sizeof(st)),mp1.clear(),mpr.clear(),cnt=0;
		for(int i=2;i*i<=n;++i)
		{
			if(n%i==0)
			{
				pr[++cnt]=i,mpr[i]=cnt;
				while(n%i==0)n/=i,++st[cnt];
				ans*=(st[cnt]+1);
			}
		}
		if(n!=1)pr[++cnt]=n,mpr[n]=cnt,st[cnt]=1,ans*=2;
		stcnt=cnt,prans=ans,mp1=mpr,memcpy(now,st,sizeof(st)),memcpy(p,pr,sizeof(p));
		while(q--)
		{
			read(x);
			if(x==2)cnt=stcnt,ans=prans,mp1=mpr,memcpy(now,st,sizeof(now)),memcpy(p,pr,sizeof(pr));
			else
			{
				read(y);
				for(int i=2;i*i<=y;++i)
				{
					if(y%i==0)
					{
						if(!mp1[i])p[++cnt]=i,mp1[i]=cnt;
						int pos=mp1[i];
						while(y%i==0)ans+=ans/(now[pos]+1),++now[pos],y/=i;
					}
				}
				if(y!=1)
				{
					if(!mp1[y])p[++cnt]=y,mp1[y]=cnt;
					int pos=mp1[y];
					ans+=ans/(now[pos]+1),++now[pos];
				}
				int flag=1,x=ans;
				for(int i=1;i<=cnt;++i)
				{
					int sum=0;
					while(x%p[i]==0)x/=p[i],++sum;
					if(sum>now[i])flag=0;
				}
				if(x!=1)flag=0;
				puts(flag?"yes":"no");
			}
		}
		puts("");
	}
}
```

---

## 作者：ydzr00000 (赞：3)

考虑条件 $\gcd(a,n)=1$，这启发我们证明 $d(n)$ 是积性函数。

具体证明：

$d(a)\cdot d(b) = (\underset{k\mid a}{\sum} 1) (\underset{k\mid b}{\sum} 1)$。

当 $\gcd(a,b)=1$ 时，取 $a$ 的一约数 $x$，取 $b$ 的一约数 $y$，则 $xy$ 是 $ab$ 的约数，且因为 $a,b$ 的约数只有 $1$ 相同，故任意两个 $xy$ 不重。

故 $d(a)\cdot d(b) = (\underset{k\mid a}{\sum} 1) (\underset{k\mid b}{\sum} 1) = \underset{k\mid ab}{\sum} 1 = d(ab)$。

所以 $d(n)$ 为积性，原条件化为 $d(n)\cdot d(a) = n$，所以条件成立，一定有 $d(n)\mid n$。

对于 $d(n)$ 的具体值，令 $n$ 的质因数分解形式为 $p_1^{c_1}p_2^{c_2}\cdots p_k^{c_k}$，那么对于每一个质因子 $p_i$，我们取一个指数 $t_i(0\leq t_i\leq c_i)$，那么 $p_1^{t_1}p_2^{t_2}\cdots p_k^{t_k}$ 唯一对应一个正整数 $m$，且 $m$ 是 $n$ 的约数，而 $t_i$ 有 $c_i+1$ 种取法，由乘法原理得 $d(n) = (c_1+1)(c_2+1) \cdots (c_k+1)$。

在 $10^6$ 以内的质数总共有约 $T=7.8\times 10^4$ 个，所以 $O(Tq)$ 的时间复杂度是合理的。

于是考虑动态维护 $n$ 的每一个质因子的数量。
1. 对于 $1$ 类操作，将 $n$ 乘 $x$ 的时候直接将 $x$ 的质因数添加进 $n$ 的质因数即可。
2. 对于 $2$ 类操作，将 $n$ 替换成最初时 $n$ 的质因数分解形式。

由于保证 $d(n)\leq 10^9$，所以用一个变量（记为 $y$）记录当前的 $d(n)$ 未尝不可，每一次判断 $y$ 的质因数分解形式中每一个质因子的指数是否都比 $n$ 的对应指数小即可。

事实上，$d(n)$ 的质因子形式也可以维护，但在本题中并不需要。

附上代码：

```c++
#include<bits/stdc++.h>
using namespace std;
int pri[100001],tot=0,onum[100001],num[100001];
bool flag[1000001];
inline void init(int n)	//线性筛
{
	for(int i=2;i<=n;i++)
	{
		if(!flag[i])
			pri[++tot]=i;
		for(int j=1;j<=tot&&i*pri[j]<=n;j++)
		{
			flag[i*pri[j]]=true;
			if(i%pri[j]==0)
				break;
		}
	}
}
int main(){
	init(1000000);
	
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,q,odn=1;
		scanf("%d %d",&n,&q);
		memset(onum,0,sizeof(onum));
		for(int j=1;j<=tot;j++)
			while(n%pri[j]==0)
			{
				odn=odn/(onum[j]+1);
				onum[j]++;
				odn=odn*(onum[j]+1);
				n/=pri[j];
			}
		int dn=odn;
		for(int j=1;j<=tot;j++)
			num[j]=onum[j];
		while(q--)
		{
			int op;
			scanf("%d",&op);
			if(op==1)
			{
				int x;
				scanf("%d",&x);
				for(int j=1;j<=tot;j++)
					while(x%pri[j]==0)
					{
						dn=dn/(num[j]+1);
						num[j]++;
						dn=dn*(num[j]+1);
						x/=pri[j];
					}
				int val=dn;
				bool valid=true;
				for(int j=1;j<=tot;j++)
				{
					int pw=0;
					while(val%pri[j]==0)
					{
						val/=pri[j];
						pw++;
					}
					if(pw>num[j])
						valid=false;
				}
				if(val>1)
					valid=false;
				if(valid)
					puts("YES");
				else
					puts("NO");
			}
			else
			{
				dn=odn;
				for(int j=1;j<=tot;j++)
					num[j]=onum[j];
			}
		}
	}

	return 0;
}
```

---

## 作者：_HCl_ (赞：2)

不是很难的一道数论。但关于数据范围的细节有几个，还是调了我有一段时间的。

# CF1878F 题解

**题意简述**

给定 $n$，对于每次操作：

1. $op=1$，则将 $n$ 修改为 $n\cdot x$，并判断是否存在与 $n$ 互质的 $a$ 使得 $n\cdot a$ 的正因子个数为 $n$。
1. 复原 $n$。

**思路引导**

根据数论的知识，当 $\gcd(a,b)=1$ 时，有 $\tau(a\cdot b)=\tau(a)\cdot\tau(b)$。其中 $\tau(x)$ 是 $x$ 的正因子个数。该结论过于显然，证明略。

因此，不难证明：

$$\exists a \ \ \text{s.t.}\ \tau(a\cdot n)=n\Leftrightarrow \tau(n)|n$$

因为很容易构造出 $a$ 满足 $\tau(a)=\dfrac{n}{\tau(n)}$。

故只需要判断 $\tau(n)$ 是否整除 $n$ 即可。

然而，需要注意的是，$\tau(n)\leq 10^9$，其对应的 $n$ 也会非常大，`long long` 是存不下的。所以我们要通过存储其唯一分解来储存 $n$，并且在判断是否整除时，要边乘边取模。由于值域较大，使用 `map` 来记录质因数分解的结果（即 `mp[p]` 记录 $p$ 的指数）。

另外还有一些细节会在实现部分和代码里呈现。

**实现**

对于每一组数据：

1. 读入，将 $n$ 分解质因数，存储在原始结果 $o\_mp$ 中。
1. 赋初值，将 $o\_mp$ 赋给 $mp$。
1. 询问

对于每一个询问：

1. 读入，如果 $op=2$，将 $o\_mp$ 赋给 $mp$。
1. 如果 $op=2$，分解 $x$。
1. 遍历 $mp$ ，计算 $d$ 的值，即 $\tau(n)$。
1. 计算 $n$ 是否被 $d$ 整除，输出。

还有要注意的是，当 $d=1$ 时，需要特判 `YES`。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
map<int,int> o_mp,mp;
int qpow(int a,int b,int p){
	int ans=1%p;
	for(;b;b>>=1){
		if(b&1)ans=ans*a%p;
		a=(long long)a*a%p;//注意long long 
	}
	return ans;
}
void solve(){
	o_mp.clear();//注意初始化 
	cin>>n>>q;
	for(int i=2;i*i<=n;++i)
		while(n%i==0)o_mp[i]++,n/=i;//分解n 
	if(n>1)o_mp[n]++;//不要把最后一个质因数落下了 
	mp=o_mp;//赋初值 
	while(q--){
		int op;
		scanf("%d",&op);
		if(op==1){
			int x;
			scanf("%d",&x); 
			for(int i=2;i*i<=x;++i)
				while(x%i==0)mp[i]++,x/=i;//分解x 
			if(x>1)mp[x]++;
			int d=1;long long now=1;
			map<int,int>::iterator p;
			for(p=mp.begin();p!=mp.end();++p)d*=(*p).second+1;//遍历mp，计算d 
			for(p=mp.begin();p!=mp.end();++p){
				now*=qpow((*p).first,(*p).second,d);
				now%=d;//计算n，边计算边取模 
				if(!now)break;//小小的优化，没啥用 
			}
			if(d>1&&now)cout<<"NO\n";//注意特判 
			else cout<<"YES\n";
		}
		else mp=o_mp;//还原n 
	}
} 
int main(){
	int T;
	cin>>T;
	while(T--)solve(); 
	return 0;
}

```


---

## 作者：iiiiiyang (赞：2)

[神秘的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17732039.html)

[题目链接](https://www.luogu.com.cn/problem/CF1878F)

若 $a$ 与 $n$ 互质，因为 $d$ 是积性函数，所以 $d(n \cdot a) = d(n) \cdot d(a) = n$，于是只需要判断是否 $d(n) \mid n$ 来得到 $d(a)$。现在需要动态维护 $n$ 和 $d(n)$。考虑 $d(n)$ 的定义，如果 $n = p_1^{k_1} \times p_2^{k_2} \times \cdots \times p_c^{k_c}$，则有 $d(n) = \Pi_{i = 1}^{c} (k_i + 1)$，可以使用 map 来动态维护当前 $n$ 的质因数及个数，因为题目保证了任何时刻 $d(n) \leq 10^9$，所以可以直接爆乘。还有一个问题是不能直接维护 $n$，但是我们在维护 $d(n)$ 的同时维护了 $n$ 的所有质因数，用这些数来对 $d(n)$ 进行试除即可，显然这个量级远远小于 $q \log V$。接下来再回来思考一下为什么上面的条件是充要的，因为 $a$ 并没有范围限制，而 $d$ 的计算方法取决于 $k$ 而并非 $p$，所以总可以找到若干个质数不属于 $n$ 的约数，然后叠指数来构造和 $n$ 的拆解方式指数位置相同的形式。

瓶颈在于 map 的使用和质因数分解，筛子预处理一下每个数的**最小约数**后不用试除法，每次值都至少减少一半。这样大概就做到了 $\mathcal O(n \log V)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=max(a,b);}
    TT inline void cmin(T &a,T b) {a=min(a,b);}
    TA inline void cmax(T &a,T b,Args... args) {a=max({a,b,args...});}
    TA inline void cmin(T &a,T b,Args... args) {a=min({a,b,args...});}
    TT inline void Madd(T &a,T b) {a=a+b>=Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=2000010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    
    int T,n,q,ans,op,x;
    map<int,int> m;
    
    namespace Sieve
    {
    	constexpr int N=1000000;
    	int d[N+10];
    	inline void Work()
    	{
    		for(int i=2;i<=N;++i)
    		{
    			if(d[i]) continue;
    			for(int j=i;j<=N;j+=i) d[j]=i;
			}
		}
	}
	using namespace Sieve;

    inline void lmy_forever()
    {
    	read(T),Sieve::Work();
    	while(T--)
    	{
    		auto getd=[&](int k,int tmp)->void
    		{
    			if(!tmp) m.clear(),ans=1;
    			while(k!=1)
    			{
    				int div=d[k],cnt=0;
    				while(k%div==0) k/=div,++cnt;
    				if(tmp) ans/=(m[div]+1),m[div]+=cnt,ans*=(m[div]+1); else m[div]=cnt,ans*=(cnt+1);
				}
			};
			read(n,q),getd(n,0);
    		for(int i=1;i<=q;++i)
    		{
    			read(op);
    			if(op==1)
    			{
    				read(x),getd(x,1);
    				int tmp=ans;
    				for(auto [div,tim]:m) while(tim&&ans%div==0) ans/=div,--tim;
    				puts(ans==1?"YES":"NO");
    				ans=tmp;
				}
				if(op==2) getd(n,0);
			}
			puts("");
		}
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}

```

---

## 作者：Kedit2007 (赞：2)

Update 09/29/23: 修改了一处错误。

## 思路

首先证明一个结论：当且仅当 $n$ 是 $d(n)$ 的倍数时，存在一个 $a$ 使得 $\gcd(n, a) = 1$ 且 $d(n \cdot a) = n$。

当 $n = 1$ 时结论显然成立。

否则，假设 $m$ 是 $a$ 的一个因数，由于 $\gcd(n, a) = 1$，所以不存在 $n$ 的两个不同因数 $i, j$ 使得 $i \cdot m = j$，而显然 $a$ 的任意两个因数乘上 $n$ 的因数后不会出现重复的答案，进而 $m$ 对 $d(n \cdot a)$ 的贡献为 $d(n)$。由此，若 $a$ 的因数个数为 $k$，则 $d(n \cdot a) = k\cdot d(n)$。而要构造出这样的一个 $a$，只需要找到一个 $m$ 使得 $m \gt 1$ 且 $\gcd(n, m) = 1$，令 $a = m^k$ 即可。而对于任意 $n \gt 1$，都有一个满足条件的 $m$。
 
简单证明完结论后，考虑如何快速求出每个 $d(n)$。将 $n$ 质因数分解，假设 $n = p_1^{a_1}p_2^{a_2}\cdots p_k^{a_k}$，则 $d(n) = (a_1 + 1)(a_2 + 1)\cdots(a_k + 1)$。对于相乘操作，假设 $x = p_1^{b_1}p_2^{b_2}\cdots p_k^{b_k}$，则 $n \cdot x = p_1^{a_1+b_1}p_2^{a_2+b_2}\cdots p_k^{a_k+b_k}$，可以快速求出每个 $d(n)$。

而判断 $n$ 是否为 $d(n)$ 倍数时，可以考虑将 $d(n)$ 质因数分解，若 $n$ 的质因数分解沿用上段中的表达，$d(n)=p_1^{c_1}p_2^{c_2}\cdots p_k^{c_k}$，则若 $n$ 为 $d(n)$ 的倍数，那么 $c_i \le a_i$ 对任意的 $i$ 均成立。

## 参考代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> primes;
const int MAXN = 2e6;

struct number
{
	map<int, int> factors;
	
	number() = default;
	
	// 质因数分解
	// 时间复杂度 O(log(n))
	number(int x)
	{
		for (const auto& p : primes)
		{
			if (p > x) break;
			int cnt = 0;
			while (x % p == 0)
			{
				x /= p;
				cnt++;
			}
			if (cnt == 0) continue;
			factors[p] = cnt;
		}
	}
};

// 乘两个质因数分解后的数
// 时间复杂度 O(log(n) * log(log(n)))
number combine(const number& lhs, const number& rhs)
{
	number ret;
	ret.factors = lhs.factors;
	for (const auto& pe : rhs.factors)
	{
		ret.factors[pe.first] += pe.second;
	}
	return ret;
}

// 判断是否整除
// 时间复杂度 O(log(n) * log(log(n)))
bool divisible(const number& numerator, const number& denominator)
{
	for (const auto& pe : denominator.factors)
	{
		auto iter = numerator.factors.find(pe.first);
		if (iter == numerator.factors.end()) return false;
		if (iter->second < pe.second) return false;
	}
	return true;
}

// 线性筛
void prime()
{
	vector<bool> visited(MAXN + 1);
	for (int i = 2; i <= MAXN; i++)
	{
		if (!visited[i])
		{
			primes.push_back(i);
		}
		for (const auto& p : primes)
		{
			if (p * i > MAXN) break;
			visited[p * i] = true;
			if (i % p == 0) break;
		}
	}
}

void work()
{
	int n, q;
	cin >> n >> q;
	number ori = number(n), cur = ori;
	while (q--)
	{
		int opr;
		cin >> opr;
		if (opr == 1)
		{
			int x;
			cin >> x;
			cur = combine(number(x), cur);
			int d = 1;
			for (const auto& pe : cur.factors)
			{
				d *= pe.second + 1;
			}
			number dn = number(d);
			if (divisible(cur, dn))
			{
				cout << "Yes" << '\n';
			}
			else
			{
				cout << "No" << '\n';	
			}
		}
		else
		{
			cur = ori;
		}
	}
}

int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	prime();
	int q;
	cin >> q;
	while (q--)
	{
		work();
	}
}
```

---

## 作者：chatoudp (赞：1)

# CF1878F Vasilije Loves Number Theory 题解

~~$1.0$ 小闲话~~

~~本人第 $6$ 篇题解，如有不当请指出。~~

## $1.0$ 前置知识

因数个数定理：

$n=p_1^{a_1} \times p_2^{a_2} \times \dots \times p_{n-1}^{a_{n-1}}\times p_n^{a_n}$，则 $d(n)=(a_1+1)\times(a_2+1)\times\dots\times(a_{n-1}+1)\times(a_n+1)$。

（$\operatorname{d}(n)$ 表示 $n$ 的因数个数）。

## $1.1$ 如何判断乘上数后 $\operatorname{d}(n)$ 是否能等于 $n$

### 结论

#### $n$ 是 $\operatorname{d}(n)$ 的倍数。

### 原因

根据因数个数定理：
$\operatorname{d}(n) =(a_1+1)\times(a_2+1)\times\dots\times(a_{n-1}+1)\times(a_n+1)$。

然后因为 $\gcd(a,n)=1$，所以 $n$ 乘上 $a$ 后的质因数分解形式一定为：
$n=p_1^{a_1} \times p_2^{a_2} \times \dots \times p_{n-1}^{a_{n-1}}\times p_n^{a_n}\times P_1^{A_1} \times P_2^{A_2} \times \dots \times P_{m-1}^{A_{m-1}}\times P_m^{A_m}$。

$P_1^{A_1} \times P_2^{A_2} \times \dots \times P_{m-1}^{A_{m-1}}\times P_m^{A_m}$ 为 $a$ 的质因数分解形式。

然后算出 $n\times a$ 有几个因数：
$\operatorname{d}(n \times a)=(a_1+1)\times(a_2+1)\times\dots\times(a_{n-1}+1)\times(a_n+1)\times(A_1+1)\times(A_2+1)\times\dots\times(A_{n-1}+1)\times(A_n+1)$。

也就是：$\operatorname{d}(n)\times(A_1+1)\times(A_2+1)\times\dots\times(A_{n-1}+1)\times(A_n+1)$。

然而，$(A_1+1)\times(A_2+1)\times\dots\times(A_{n-1}+1)\times(A_n+1)$ 可以表示大于等于零的任何数，所以
我们需要满足的条件就是 $\operatorname{d}(n)\times x=n$，也就是 $n$ 是 $\operatorname{d}(n)$ 的倍数。

## $1.2$ AC time

本代码怕 $n$ 爆 long long，所以存的是它的分解质因数的结果。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,q;

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&q);
		map<int,int> now,p;
		for(int i=2;i<=sqrt(n);i++)
			while(n%i==0){
				n/=i;
				now[i]++;
				p[i]++;
			}
		if(n!=1){
			now[n]++;
			p[n]++;
		}
		int op,x;
		while(q--){
			scanf("%d",&op);
			if(op==1){
				scanf("%d",&x);
				for(int i=2;i<=sqrt(x);i++)
					while(x%i==0){
						x/=i;
						now[i]++;
					}
				if(x!=1)
					now[x]++;
				map<int,int> k;
				for(auto p:now){
					int q=p.second+1;
					for(int i=2;i<=sqrt(q);i++)
						while(q%i==0){
							q/=i;
							k[i]++;
						}
					if(q!=1)
						k[q]++;
				}
				bool f=1;
				for(auto p:k)
					if(p.second>now[p.first]){
						f=0;
						break;
					}
				if(f) printf("yEs\n");
				else printf("nO\n");
			}else
				now=p;
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：xzf_200906 (赞：1)

Update on 2024/2/21：补充了一个证明

---
因为最终的 $n$ 可以很大，所以我们无法存储 $n$ 的值，但是可以存储它的质因子。记值域为 $V$。

+ 对于小于 $\sqrt{V}$ 的质因子，它们至多有 $\sqrt{V}$ 个，可以暴力枚举，使用桶存储。
+ 对于大于 $\sqrt{V}$ 的质因子，由于每次操作 `1` 所乘上的 $x$ 最多有一个这样的质因子，所以这种质因子最多有 $q$ 个，使用 `vector` 存储，用桶统计出现次数和去重。

所以，在任何时刻，$n$至多有 $\sqrt{V}+q$ 种质因子，可以在 $\mathcal{O}(\sqrt{V}+q)$ 的时间内计算出 $d(n)$，即 $n$ 的约数个数。

容易发现，有符合题意的 $a$ 存在，当且仅当 $d(n)$ 为 $n$ 的约数。所以可以对 $d(n)$ 分解质因子，判断 $d(n)$ 中的每个质因子是否被 $n$ 包含即可。

复杂度：$\mathcal{O}(q(\sqrt{V}+q))$。

+ 为什么有符合题意的 $a$ 存在，当且仅当 $\operatorname{d}(n)$ 为 $n$ 的约数？
	+ 众所周知的，设 $x=\prod^{k}_{i=1}p_i^{c_i}$，其中 $p_i$ 为质数，则 $d(x)=\prod^{k}_{i=1}(c_i+1)$，又因为 $\gcd(a,n)=1$，所以 $a$ 和 $n$ 没有相同的质因子，所以 $\operatorname{d}(a \times n)=\operatorname{d}(a) \times \operatorname{d}(n)$，当 $\operatorname{d}(n)$ 为 $n$ 的约数时，取任意质因子 $p \nmid n$ 并令 $a=p^{\frac{n}{\operatorname{d}(n)}-1}$即可。否则无论 $\operatorname{d}(a)$ 取何值 $\operatorname{d}(a \times n)$ 都不可能等于 $n$。

---
```cpp
#include<bits/stdc++.h>
using namespace std;
short d[1005],buc[1000005];
vector<int> di;
const int cap=1000;
void mul(int x){
	for(int i=2;i<=cap;i++){
		while(x%i==0){
			d[i]++;
			x/=i;
		}
	}
	if(x>1){
		if(buc[x]==0) di.push_back(x);
		buc[x]+=1;
	}
}
void load(int n){
	for(auto it:di) buc[it]=0;
	di.clear();
	for(int i=1;i<=cap;i++) d[i]=0;
	mul(n);
}
bool judgefac(int x){
	if(x==0) return 0;
	for(int i=2;i<=cap;i++){
		if(x%i==0){
			int num=0;
			while(x%i==0){
				num++;
				x/=i;
			}
			if(num>d[i]) return 0;
		}
	}
	if(x>1){
		if(buc[x]==0) return 0;
	}
	return 1;
}
bool judge(){
	int cnt=1;
	for(int i=2;i<=cap;i++){
		if(d[i]) cnt*=(d[i]+1);
	}
	for(auto it:di) cnt*=(buc[it]+1);
	return judgefac(cnt);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,q;
		cin>>n>>q;
		load(n);
		while(q--){
			int op;
			cin>>op;
			if(op==1){
				int x;
				cin>>x;
				mul(x);
				cout<<(judge()?"YES\n":"NO\n");
			}
			else load(n);
		}
		cout<<'\n';
	}
}
```

---

## 作者：zhangli828 (赞：0)

## 题目大意
你得到了一个整数 $n$ 你有两种操作：

1. 你得到一个正整数 $x$，并把 $n$ 乘上 $x$，求是否有数与 $n$ 互质并且它们的乘积的因子个数为 $n$ 的因数。
2. 把 $n$ 变为初始值。
## 题目解法
我们发现 $d(n\times x)=d(n)\times d(x)$，所以只要 $d(n)$ 是 $n$ 的因数就可以满足条件。为了快速求出因数数量，我们可以原来 $n$ 的质因数集合，再把 $x$ 的质因数集合加入即可。

但要注意一点因为 $n$ 可能很大，所以我们可以算出 $d(n)$ 后通过因子来计算 $n\bmod d(n)$ 的结果。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, q, id, v;
map<int, int> mp, mp2;

void Push(map<int, int> &mp, int x) {
  for (int i = 2, y = x; i * i <= y; i++) {
    for (; !(x % i); x /= i, mp[i]++);
  }
  (x > 1) && (mp[x]++);
}

int Pow(int x, int y, int kMod) {
  int z = 1;
  for (; y; (y & 1) && (z = z * x % kMod), y >>= 1, x = x * x % kMod);
  return z;
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; cout << '\n') {
    cin >> n >> q, mp.clear(), Push(mp, n), mp2 = mp;
    for (; q--;) {
      cin >> id;
      if (id == 2) {
        mp = mp2;
      } else {
        cin >> v, Push(mp, v);
        int mul = 1, mul2 = 1;
        for (map<int, int>::iterator i = mp.begin(); i != mp.end(); i++) {
          mul *= (i->second + 1);
        }
        for (map<int, int>::iterator i = mp.begin(); i != mp.end(); i++) {
          mul2 = mul2 * Pow(i->first, i->second, mul) % mul;
        }
        cout << (mul2 % mul ? "NO\n" : "YES\n");
      }
    }
  }
  return 0;
}
```

---

## 作者：lgx57 (赞：0)

简单题。

由数论知识可知，$d(n)$ 是积性函数。也就是说，对于任意的 $\gcd(x,y)=1,d(x)d(y)=d(xy)$。

因此，$d(a\cdot n)=d(n)d(a)$。

至此，问题转化为判断 $d(n)\mid n$ 的正确性。

显然，如果每一次暴力乘会溢出，所以可以想到质因数分解。

首先，用素数筛把素数都筛出来，然后考虑质因数分解，相信大家都会，就简单的放一下代码：

```cpp
void gt(int x,int a[]){
	for (int i=1;i<=cnt;i++){
		while (x%pr[i]==0) x/=pr[i],a[i]++;
		if (x==1) break;
	}
}
```

请注意，如果在函数中直接 memset 是无法在全局清空数组的。（为此调了 10 min）

然后计算 $d(n)$。设 $n$ 的质因数分解为 $n=p_1^{\alpha_1}p_2^{\alpha_2}\cdots p_{cnt}^{\alpha_{cnt}}$，那么 $d(n)=(\alpha_1+1)(\alpha_2+1)\cdots(\alpha_{cnt}+1)$。

```cpp
int calc(int a[]){
	int ans=1;
	for (int i=1;i<=cnt;i++){
		ans*=(a[i]+1);
	}
	return ans;
}
```

剩下的事情就简单了，只要判断一个数是否整除另一个数即可。

[完整代码](https://codeforces.com/contest/1878/submission/288424884)

---

## 作者：OIer_Hhy (赞：0)

# Part 1 前言

在 jc 书院学数论，刷题偶遇……

# Part 2 思路

首先，根据算术基本定理，$n=p _ {1} ^ {a_{1}} \times p _ {2} ^ {a_{2}} \times \cdots \times p _ {k} ^ {a_{k}}$，可得 $d(n)=\prod _ {i=1} ^ k (1+a_i)$

其次，因为 $\gcd(a,n)=1$，可得 $d(a\times n)$ 有一个因子为 $d(n)$。

我们每次暴力算出 $d(a\times n)$ 与 $d(n)$，如果 $d(n) \mid d(a\times n)$，说明存在，输出 `YES`；反之亦然。

但是……你会 `WA on test #4`。

查看一下 CF，你会发现 `signed interger overflow`。

题目说的是 $d(n) \le 10^9$，不是 $d(a\times n) \le 10^9$ 啊！

我们得优化。

把每次的 $x$ 存入一个 `vector` 里，每次要求 $d(n) \mid d(a\times n)$ 时，把两边的数用最大公因数约分掉，就不会爆 `long long` 了。

# Part 3 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q,x,opt;
set<int> st;
multiset<int> st2;
map<int,int> mp;
void func(int x){
	st2.insert(x);
	int k=2;
	while(x>1){
		while(k*k<=x&&x%k!=0) k++;
		if(k*k>x) break;
		if(!st.count(k)) st.insert(k);
		while(x%k==0){
			mp[k]++;
			x/=k;
		}
	} 
	if(x>1){
		st.insert(x);
		++mp[x];
	}
}
bool d(){
	vector<int> v1,v2;
	int k=1,k2=1;
	for(auto x:st)
		v1.emplace_back(mp[x]+1);
	for(auto x:st2)
		v2.emplace_back(x);
	for(int i=0;i<v1.size();i++){
		for(int j=0;j<v2.size();j++){
			int GCD=__gcd(v1[i],v2[j]);
			v1[i]/=GCD;
			v2[j]/=GCD;
		}
	}
	for(auto x:v1){
		if(x!=1) return 0;
	}
	return 1;
}
void solve(){
	st.clear();
	st2.clear();
	mp.clear();
	cin>>n>>q;
	int pre_n=n;
	func(n);
	while(q--){
		cin>>opt;
		if(opt==1){
			cin>>x;
			func(x);
			int res=d();
			if(res) puts("YES");
			else puts("NO");
		}else{
			st.clear();
			st2.clear();
			mp.clear();
			n=pre_n;
			func(n);
		}	
	}
	puts("");
}
signed main(){
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1878f-vasilije-loves-number-theory-de-ti-jie/)
## 题目大意
令 $d(x)$ 表示 $x$ 的正因子数量，给定 $n,q$。现有两种操作：
1. 给定 $x$，令 $n\gets n\cdot x$。同时询问是否存在一个正整数 $a$ 满足 $\gcd(a,n)=1$ 且 $d(n\cdot a)=n$。
2. 将 $n$ 还原为最初的值。

数据保证任何时刻，$d(n)\leq 10^9$。
## 思路
因为题目其实并没有要求输出 $a$ 具体的值，所以我们并不需要真正的将 $a$ 求解出来，而只需要判断存在性就可以了。

因为 $n$ 可能会很多次被乘以 $x$，所以我们就可以储存 $n$ 的所有的质因子。

假设 $n$ 在质因数分解之后有 $k$ 个质因子，而且第 $i$ 个质因子出现了 $x_i$ 次，那么总共的因子数量就是 $\prod_{i=1}^{k} x_i+1$。

对于这个性质，我们可以感性的理解一下：对于每一个质因子，我们可以选 $num\in[0,x_i]$ 个，即有 $x_i+1$ 种可能性。通过乘法原理就可以得到因子数量为 $\prod_{i=1}^{k} x_i+1$。

如果满足 $d(n)|n$ 就一定可以找到满足条件的 $a$ 反之就不可能，理由如下：

对于 $a$ 取任何数一定满足 $d(a\cdot n)|d(n)$。

因为 $d(n)=\prod_{i=1}^{k} x_i+1$，$d(a\cdot n)=\prod_{i=1}^{k} x_i+y_i+1$，其中 $y_i$ 以 $i$ 为 $a$ 的质因子的个数。

对于 $d(a\cdot n)$ 一定可以找到一个 $a$ 使 $d(n)\cdot q=d(n)$，此时的 $a=s^{q-1}$，其中 $s$ 是一个极大质数。

因为题目要求 $\gcd(a,n)=1$，所以只要满足 $s$ 并非 $n$ 的质因子即可。

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
map<int,int> mp,mp1;
void solve() {
	cin>>n>>q;
	for(int i=2;i*i<=n;i++) {
		while(n%i==0){
			mp[i]++;
			n/=i;
		}
	}
	if(n>1){
		mp[n]++;
	}
	mp1=mp;
	for (int i=1,op,x;i<=q;i++){
		std::cin>>op;
		if(op==2){
			mp=mp1;
			continue;
		}
		cin>>x;
		for(int j=2;j*j<=x;j++) while(x%j==0) mp[j]++,x/=j;
		if(x>1) mp[x]++;
		int cnt=1;
		for(auto i:mp) cnt*=(i.second+1);
		bool flag=1;
		for(int j=2;j*j<=cnt;j++){
			int sum=0;
			while(cnt%j==0) sum++,cnt/=j;
			if(sum>mp[j]){
				flag=0;
				break;
			}
		} 
		if(cnt>1&&!mp[cnt]||!flag) cout<<"NO\n";
		else cout<<"YES\n";
	}
	mp.clear();
	cout<<'\n';
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# Vasilije Loves Number Theory 题解

## 思路

问题在于如何化简 $d(na)= n$，就这么看的话十分难受。

可以推出一个式子：
$$d(xy)= d(x)\times d(y)$$

因为太简单所以不给证明了，手玩几组数据也可以看出来。

所以以上的式子可以化简为 $d(na)= d(n)\times d(a)= n$。

即 $d(a)= \dfrac{n}{d(n)}$。

我们只考虑 $a$ 是否存在，并且只要 $d(a)$ 存在那么 $a$ 就存在，所以实际上只需判断 $d(n)$ 是否能被 $n$ 整除就可以了。

直接算的话复杂度是极高的，最坏情况可以超过$O(\sqrt{10^{6000}})$。

考虑优化。

可以想到对 $d(n)$ 与 $n$ 质因数分解，然后遍历 $d(n)$ 的质因数，如果存在某一项的指数大于分解后 $n$ 相应的质因数的指数，说明不符合条件，否则符合。

---

对于 $n\gets n\times x$ 这个操作，我们不需要重新计算 $n$ 的质因子，只需要将 $x$ 的质因子加入 $n$ 中就可以了。

这样我们每次都只需处理新加入的 $x$，运行时间大大缩短。

最后因为质因数太大需要一个 map 维护。



## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define il inline
#define db double
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
int n,q;
int ddd,now;//ddd为初始d(n),now为现在d(n) 
std::map<int,int> t,cs;//cs为n质因子的初始状态，t为现在n质因子的状态 
bool pd()
{
	int tmp=now;
	for(int i=2;i*i<=tmp;i++)
	{
		if(tmp%i==0)
		{
			int cnt=0;
			while(tmp%i==0) cnt++,tmp/=i;
			if(cnt>t[i]) return 0;//如果d(n)有一个质因子的指数比n分解后的这个质因子的指数大，说明不符合要求 
		}
	}
	if(tmp!=1&&!t[tmp]) return 0;//同理，不符合条件 
	return 1;
}
il void init()//处理两个初始状态 
{
	ddd=1;//需要初始化为1方便后续乘法 
	for(int i=2;i*i<=n;i++)//处理n的质因子 
	{
		if(n%i==0)
		{
			int cnt=0;//cnt为相应质因子的指数 
			while(n%i==0) cnt++,n/=i;
			ddd*=cnt+1,cs[i]=cnt;//因子的个数就是质因子的指数+1的乘积 
		}
	}
	if(n>1) ddd*=2,cs[n]++;//还剩下一个质数 
	now=ddd,t=cs;
}
il void pri(int x)
{
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0)
		{
			now/=t[i]+1;
			while(x%i==0) t[i]++,x/=i;
			now*=t[i]+1;
		}
	}
	if(x>1)
	{
		now/=t[x]+1;
		t[x]++;
		now*=t[x]+1;
	}
}
void solve()
{
	t.clear(),cs.clear();
	n=read(),q=read();
	init();
	int op,x;
	while(q--)
	{
		op=read();
		if(op==2) t=cs,now=ddd;//变为初始状态 
		else
		{
			x=read();
			pri(x);//将x的质因数加入 
			puts(pd()?"YES":"NO");
		}
	}
	puts("");//多输出一个空格  
}
signed main()
{
	int T;
	T=read();
	while(T--) solve();
}
```





---

## 作者：thdlrt (赞：0)

- 若 $n = p_1^{a_1}p_2^{a_2}\dots p_k^{a_k}$ ，则显然有 $d(n) = (a_1 + 1)(a_2 + 1)\dots(a_k + 1)$ 。
- 能整除 $n$ 的元素实际上就是使用 $n$ 的质因数可以组合出多少个不同的数，而每个数字中每个质因数的数目可以是 $0, 1, \dots, a_i$ ，共 $a_i + 1$ 种选择。
- 若 $\gcd(a, n) = 1$ 说明没有相同的素因数，那么显然有 $d(an) = d(a)d(n)$ ，这是一个积性函数。因此 $d(an) = n$ 的条件是 $d(n) \mid n$ 。
- 对于本题，由于 $n \cdot x$ 没有大小上限，可能会非常大，因此并不能维护 $n \cdot x$ 的大小。$x \mid y$ 其实等价于对于每一个质因数 $p_i$ 有 $a_{ix} \leq a_{iy}$ ，所以我们只需要维护质因数分解的结果即可。
  - 提示：$xy = p_1^{a_{1x}+a_{1y}} \dots$

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T &a)
{
    T s = 0, w = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        s = (s << 1) + (s << 3) + (c ^ 48);
        c = getchar();
    }
    a = s * w;
}
const int N= 1e6 + 5;
int minp[N],prime[N];
//欧拉筛预处理用于质因数分解
void init_prim()
{
    for (int i = 2; i < N; i++)
        minp[i] = i;
    int cnt = 0;
    for (int i = 2; i < N; i++)
    {
        if (minp[i] == i)
            prime[cnt++] = i;
        for (int j = 0; j < cnt && prime[j] * i < N; j++)
        {
            minp[prime[j] * i] = prime[j];
            if (i % prime[j] == 0)
                break;
        }
    }
}
//获取质因数分解结果
unordered_map<int,int> cal_prim(int num){
    unordered_map<int,int> res;
    for(int i=2;i<sqrt(num)&&num>=N;i++){
        while(num%i==0){
            res[i]++;
            num/=i;
        }
    }
    if(num>=N){
        res[num]++;
        return res;
    }
    while (num != 1)
    {
        int p = minp[num];
        res[p]++;
        if(p==0)
            cout<<"!!!";
        num /= p;
    }
    return res;
}
//计算d(n)
int cal_d(unordered_map<int,int>&mp){
    int res=1;
    for(auto&a:mp)
        res*=(a.second+1);
    return res;
}
int main()
{
    int t;
    init_prim();
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        unordered_map<int,int>mp=cal_prim(n);
        while (q--)
        {
            int t;
            bool state=true;
            read(t);
            //重置
            if (t == 2)
                mp=cal_prim(n);
            else
            {
                int x;
                read(x);
                //维护n的质因数分解
                auto tmp=cal_prim(x);
                for(auto&a:tmp)
                    mp[a.first]+=a.second;
                //计算并分解d(n)
                int d=cal_d(mp);
                auto tmp2=cal_prim(d);
                for(auto&a:tmp2){
                    if(mp[a.first]<a.second){
                        state=false;
                        cout<<"NO"<<endl;
                        break;
                    }
                }
                if(state)
                    cout<<"YES"<<endl;
            }
        }
    }
    return 0;
}
```



---

