# Another Problem About Dividing Numbers

## 题目描述

You are given two integers $ a $ and $ b $ . In one turn, you can do one of the following operations:

- Take an integer $ c $ ( $ c > 1 $ and  $ a $ should be divisible by $ c $ ) and replace $ a $ with $ \frac{a}{c} $ ;
- Take an integer $ c $ ( $ c > 1 $ and  $ b $ should be divisible by $ c $ ) and replace $ b $ with $ \frac{b}{c} $ .

Your goal is to make $ a $ equal to $ b $ using exactly $ k $ turns.

For example, the numbers $ a=36 $ and $ b=48 $ can be made equal in $ 4 $ moves:

- $ c=6 $ , divide $ b $ by $ c $ $ \Rightarrow $ $ a=36 $ , $ b=8 $ ;
- $ c=2 $ , divide $ a $ by $ c $ $ \Rightarrow $ $ a=18 $ , $ b=8 $ ;
- $ c=9 $ , divide $ a $ by $ c $ $ \Rightarrow $ $ a=2 $ , $ b=8 $ ;
- $ c=4 $ , divide $ b $ by $ c $ $ \Rightarrow $ $ a=2 $ , $ b=2 $ .

For the given numbers $ a $ and $ b $ , determine whether it is possible to make them equal using exactly $ k $ turns.

## 样例 #1

### 输入

```
8
36 48 2
36 48 3
36 48 4
2 8 1
2 8 2
1000000000 1000000000 1000000000
1 2 1
2 2 1```

### 输出

```
YES
YES
YES
YES
YES
NO
YES
NO```

# 题解

## 作者：Wuyanru (赞：8)

[题目](https://www.luogu.com.cn/problem/CF1538D)

对于这一题，其实我们只要求出满足题目要求的最多操作数和最小操作数就可以了。

最小操作数求法：分情况讨论：

1.  $ a=b $,此时不用操作就可以让他们相等，所以最小操作数为 $ 0 $；

2.  $ a\not=b $,此时令 $ num\gets \operatorname{lcm}\left(a,b\right) $,当 $ a\not=num $ 且 $ b\not=num $ 时最小操作数为 $ 2 $,否则为 $ 1 $。

最大操作数求法：

当最后 $ a=1 $ 且 $ b=1 $ 时操作数最大，我们只需要求出 $ a $ 与 $ b $ 的质因数个数之和就可以了。

最后，对于每一组数据，我们只需要看给出的 $ k $ 是否在最大操作数与最小操作数之间就可以了。

当然，我们要特别判断 $ a=b $ 且 $ k=1 $ 的情况，这时是不能满足要求的。

AC 代码：

```
#include<cstdio>
using namespace std;
int gong(int a,int b) {//辗转相除求最大公因数
	for(;;) {
		int t=a%b;
		a=b;
		b=t;
		if(b==0)
			return a;
	}
}
int zhi(int num) {//求质数个数
	int ans=0;
	for(int i=2; i*i<=num; i++)
		while(num%i==0) {
			num/=i;
			ans++;
		}
	if(num!=1)
		ans++;
	return ans;
}
int xiao(int a,int b) {//求最小操作数
	int ans=0;
	int num=gong(a,b);
	if(a!=num)
		ans++;
	if(b!=num)
		ans++;
	return ans;
}
int da(int a,int b) {//求最大操作数
	return zhi(a)+zhi(b);
}
int t,a,b,k;
int main() {
	scanf("%d",&t);
	while(t--) {//t组数据
		scanf("%d%d%d",&a,&b,&k);
		if((xiao(a,b)<=k&&k<=da(a,b))&&(a!=b||k!=1))
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
```

感谢观看！

---

## 作者：ZolaWatle (赞：7)

### CF1538D 题解

#### 题目大意

给定两个整数 $a, b$ 和一个操作数 $k$。对于每一次操作，你有如下两种选择：

- 选择一个能整除 $a$ 的大于一的整数 $c$，用 $\dfrac{a}{c}$ 替换 $a$。
- 选择一个能整除 $b$ 的大于一的整数 $c$，用 $\dfrac{b}{c}$ 替换 $b$。

然后询问，是否存在一种操作方法，使得在**恰好** $k$ 次操作后，$a=b$。

$1< a, b, k<1e9$。

#### 解题思路

我们设 $f(x)$ 代表对于一个数 $x$，对其进行唯一分解后的每一项的指数之和。举例来讲，例如 $60 = 2^2 \cdot 3^1 \cdot 5^1$，则 $f(60) = 2+1+1 = 4$。函数 $f(x)$ 的意义在于，对于 $a=x$，我们最多可以对 $a$ 进行 $f(x)$ 次操作。例如对于 $a=60$ 的情况，我们选择 $c_1=2, c_2=2, c_3=3, c_4=5$。经过这四次操作，$a=1$，操作便不能进行。由于我们由分解质因数而得出 $f(x)$，我们可以保证这样对其进行操作所需的操作数是最大的。

由此，我们知道，不断地对 $a, b$ 使用操作，最多能够操作的次数，也就只有 $mx=f(a)+f(b)$ 这么多次。

接下来我们考虑最小需要多少次操作，才能使 $a=b$。容易得出，最小操作数只有以下三种情况：

- 如果 $a=b$，它们天生就相等，最小操作数 $mn=0$。
- 如果 $a$ 或 $b$ 是对方的整数倍，最小操作数 $mn=1$。我们设 $a>b, x=\dfrac{a}{b}$，我们只需要令 $a$ 成为 $\dfrac{a}{x}$ 即可。
- 否则，我们简单粗暴将这两个数都除以它们本身，最小操作数 $mn=2$。

我们知道，当给定的操作数处于最大和最小操作数之间，即 $k\in[mn, mx]$ 时，可以达成题目要求。真的是这样吗？至少，我们可以明确，当 $k\notin [mn, mx]$ 时，一定不能满足题目要求。

得到了这样的思路后，我们将会遇到一个瓶颈。我们发现，在计算 $f(x)$ 时，由于需要预处理出 $1$ 到 $x$ 的素数，因而时间复杂度为 $\text{O}(x_{max})$。而这个最大值是 $1e9$ 的，跑不过去。但事实上，我们只需要计算出 $\sqrt x$ 规模的质数即可。下面给出这一结论的证明：

设 $x = p_1^{q_1}*p_2^{q_2}*\dots *p_m^{q_m}$。考虑此时最大的 $p$。由于乘积一定，我们知道指数越小底数越大。因此，我们令 $x' = p_1*p_2*\cdots *p_m$，则 $p_{max} = \sqrt[m]{x'}$。运用极限思想，可以得出当 $m=2$ 时，这个最大指数也只有 $\sqrt{1e9}$，大概 $1e5$ 的规模，做筛子时只需要筛到 $1e5$ 以内的质数即可。当 $m=1$ 时，$f(x)= 1$，就比较方便计算了。

回到前面的问题，当给定的操作数处于最大和最小操作数之间，即 $k\in[mn, mx]$ 时，可以达成题目要求。真的是这样吗？我们考虑这样一种特殊情况：当 $k=1$ 时，只允许进行一次操作。因此只有 $a$ 或 $b$ 为对方的整数倍的时侯才能实现，这需要特判。

关于实现的细节，详见我的 $\text{AC}$ 代码。

#### 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define re register int
#define rl register ll
#define rep(i,a,b) for(re i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(re i=(a),i##end=(b);i>=i##end;--i)
#define mem(x,val) memset(x,val,sizeof(x))
using namespace std;

const int N=1e5;
int T,a,b,k;
int tot,is[N],p[N];

inline int rint()
{
    re x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}

inline int mygcd(int x,int y){return !y?x:mygcd(y,x%y);}
inline int count_factor(int x)
{
	if(x==1) return 0;
	
	re ret=1,i=1;  //将返回值初始化为1，使得当枚举完所有1e5以内的质数后，可以得出“这是一个大质数，f(x)=1”的结论 
	while(x>1)
	{
		if(p[i]>=x||i>tot)
			break;
		if(x%p[i]==0)
		{
			++ret;
			x/=p[i];
		}
		else ++i;
	}
	
	return ret;
}

int main()
{
	T=rint();
	
	rep(i,2,N)
	{
		if(is[i]) continue;
		p[++tot]=i;
		for(re j=i+i;j<=N;j+=i)
			is[j]=1;
	}
	
	while(T--)
	{
		a=rint(),b=rint(),k=rint();
		if(a>b) swap(a,b);  //为了方便 
		re mx=0,mn=0;
		
		mx=count_factor(a)+count_factor(b);
		if(a==b) mn=0;
		else if(mygcd(a,b)==a) mn=1;  //等价于a是b的整数倍 
		else mn=2;
		
//		cout<<"mx: "<<mx<<' '<<"mn: "<<mn<<endl;
		
		if(mn>k||mx<k) puts("No");
		else
		{
			if(k!=1) puts("Yes");
			else
			{
				if(mn==1) puts("Yes");  //特判，必须整数倍 
				else puts("No");
			}
		}
	}

    return 0;
}
```

感谢阅读！

---

## 作者：王大神——A001 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1538D)

### 题目大意

给 $a$，$b$，$k$ 三个数在 $k$ 次操作后 $a=b$，输出 `YES`，否则输出 `NO`，每次操作可以让 $a$ 或 $b$ 整除一个大于 $1$ 的整数。

------------

### 分析
我们看这道题结合样例不难发现，我们可以求出一个范围，只要 $k\in[\min,\max]$ ，反之则不行。

那么我们先找范围 $\min$，首先我们知道两个不为 $1$ 的数， $k=2$ 是**一定可以**：可以让 $\frac{a}{a}=1$，再 $\frac{b}{b}=1$ 即可。

而如果 $a\mid b$ 或 $b\mid a$，$k_{\min}=1$，让大的数除到小的数即可 。

接着我们要找范围 $\max$，我们可以先将两个数的最大公约数求出，设 $f_i$ 为数的分解质因数后的质因数个数，这样我们可以求最大值了。

例子：

$4,4$

$k=2$ 时：$2,2$

$k=3$ 时：$1,1$

$k=3$ 时，因为每次可以除大于 $1$ 的整数，所以最大值可以是 $2\times f_i(\gcd(a,b))$（$a$ 贡献一次，$b$ 贡献一次）。

但这并不全面，因为我们让 $a$ 和 $b$ 直接除到他们的最大公因数，而在 $a$ 和 $b$ 除时，除的数也可以贡献最大值。

例子：

$36,48$

$a=12$ 和 $b=12$ 时，$\frac{a}{3}=12$，$\frac{b}{4}=12$，而 $4=2\times 2$，可以为最大值贡献 $2$。

所以 $\max={2\times f_i(\gcd(a,b))+f_i(\frac{a}{\gcd(a,b)})+f_i(\frac{b}{\gcd(a,b)})}$

------------

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#include<cmath>
using namespace std;
int t;//t组数据
int a,b,k; 
int m_i,m_a;//可以满足的最小值和最大值 
int gcd(int a,int b){//最大公约数 
	if(!b){
		return a;
	}
	gcd(b,a%b);
}
int f_i(int a){//分解质因子，求质因子的数量 
	int n_n=0;
	int a_a=a;
	for(int i=2;i*i<=a_a;i++){
		if(a==1)break;
		if(a%i==0){
			while(a%i==0){
				a/=i;n_n++;
			}
		}
	}
    if(a>1)n_n++;
	return n_n;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d %d",&a,&b,&k);
		if(a<b)swap(a,b);//方便求最大公约数 
		int g_c=gcd(a,b);
		if((g_c==a||g_c==b)&&a!=b)m_i=1;//特判 
		else m_i=2;
		m_a=2*f_i(g_c)+f_i(a/g_c)+f_i(b/g_c);//求k最大可以是多少 
		if(k>=m_i&&k<=m_a)cout<<"YES"<<endl;//输出 
		else cout<<"NO"<<endl;
	}
	return 0; 
}
```

---

## 作者：BHDwuyulun (赞：0)

### 1 题目描述
给定两个整数 $a, b$ 和一个操作数 $k$。对于每一次操作，你有如下两种选择：

- 选择1个能整除 $a$ 的大于1的整数 $c$，用 $\dfrac{a}{c}$ 替换 $a$。

- 选择1个能整除 $b$ 的大于1的整数 $c$，用 $\dfrac{b}{c}$ 替换 $b$。

然后询问是否存在一种操作方法，使得在**恰好** $k$ 次操作后，$a=b$。

数据范围：$1\lt a,b,k\lt{10}^9$。
### 2 大体思路
1. **对于 $k=1$ 的情况：**
   - 如果 $a$ 能乘除 $b$，且 $a$ 不等于 $b$，则可以通过一次操作使得它们相等。因此，输出``YES``。
   - 否则，便无法仅通过一次操作使它们相等，输出``NO``。

2. **对于 $k\gt1$ 的情况：**
   - 首先，通过质因数分解函数获取 $a$ 和 $b$ 的质因数个数，分别记为 $ka$ 和 $kb$。
   - 如果 $ka+kb<k$，则表示质因数个数不足以进行 $k$ 次操作，因为每次操作至少会使一个质因数被除去，输出``NO``。
   - 如果 $ka+kb\geq k$，则表示质因数个数足够进行 $k$ 次操作，因为总共有 $ka+kb$ 个质因数。输出``YES``。
### 3 AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define bug printf("---OK---")
#define pa printf("A: ")
#define pr printf("\n")
#define pi acos(-1.0)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
int fj(int x){//分解质因数
	int cnt=0;
	for(int i=2;i*i<=x;i++){
		while(x%i==0){
			x/=i;
			cnt++;
		}
	}
	if(x>1){
		cnt++;
	}
	return cnt;
}
int main(){
	ll t;
	cin>>t;
	while(t--){
		int a,b,k;
		cin>>a>>b>>k;
		ll ka=fj(a),kb=fj(b);
		if(k==1){
			if((a%b==0||b%a==0)&&a!=b){
				cout<<"YES";
			}
			else{
				cout<<"NO";
			}
		}
		else{
			if(ka+kb<k){
				cout<<"NO";
			}
			else{
				cout<<"YES";
			}
		}
		pr;
	}
	return 0;
}
```

---

## 作者：Xiphi (赞：0)

好题。考虑操作次数最多可以是多少。每次必须 $>1$，故每次除其最小质因子一定不劣，那么两边合起来就是最多 $d(a)+d(b)$ 次，$d(a)$ 是 $a$ 所有质因子的次数之和。那么最少可以是多少次呢？若一个数是另一个数的因数，则为 $1$；若两数相等，$0$ 次；其余情况均为 $2$。中间是必然可以处理的，因为对于中间的每个状态，都可以通过除一个数一步到位，达到减去部分步数的目的。

考虑优化算 $d(a)$ 的过程，预处理 $\sqrt {10^9}$ 以内所有质数即可。但我的代码只加了一些优化，就过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,k;
int gcd(int a, int b) {
    if(a%b==0) return b;
    else return gcd(b,a%b);
}
map<int,int> mp;
int count(int a){
	if(mp.count(a)) return mp[a];
	int t=a,cnt=0;
	for(int i=2;i*i<=a;++i){
		while(a%i==0){
			a/=i;
			cnt++;
			if(cnt>k) return k;
		}
	}
	if(a!=1) cnt++;
	mp[t]=cnt;
	return cnt;
}
int a,b;
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>T;
	while(T--){
		//1 4 2
		cin>>a>>b>>k;
		int maxn=count(a);
		if(k<=maxn){
			int minn=(gcd(a,b)!=a)+(gcd(a,b)!=b);
			if(minn<=k){
				if(a!=b||k!=1){
					cout<<"YES\n";
					continue;
				}
			}
		}
		maxn+=count(b);
		int minn=(gcd(a,b)!=a)+(gcd(a,b)!=b);
		if(minn<=k&&k<=maxn&&(a!=b||k!=1)){
			cout<<"YES\n";
		}else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

## 1. 题意

给定两个正整数 $a$，$b$ 和一个正整数 $k$。

现在你需要恰好执行 $k$ 次操作。

对于每一次操作，你可以从下面两种选择中选择一种执行：

+ 选择一个 $c$ 满足 $c>1$ 且 $a\bmod c=0$。然后让 $a=\frac{a}{c}$。
+ 选择一个 $c$ 满足 $c>1$ 且 $b\bmod c=0$。然后让 $a=\frac{b}{c}$。

问你是否可以让 $a=b$。

## 2. 题解

首先需要算出至少需要执行多少次操作才能让 $a=b$。

需要分类讨论：

+ 如果 $a=b$，那么不用执行任何的操作。
+ 否则，如果 $a\bmod b=0$，那么可以选择 $\frac{a}{b}$ 并让 $a=\frac{a}{\frac{a}{b}}=b$。只用执行一次操作。
+ 否则，如果 $b\bmod a=0$，那么 那么可以选择 $\frac{b}{a}$ 并让 $b=\frac{b}{\frac{b}{a}}=a$。只用执行一次操作。
+ 否则，设 $g=\gcd(a,b)$，那么可以让 $a=\frac{a}{\frac{a}{g}}=g$，$b=\frac{b}{\frac{b}{g}}=g$，$g=g$，需要执行两次操作。

然后计算最多需要执行多少次操作才能让 $a=b$。

容易发现，对于一个数 $x$，可以将这个数写成 ${a_1}^{b_1}\times {a_2}^{b_2}\times a_3^{b_3}\times \ldots\times {a_k}^{b_k}$ 的性质，其中 $a_1,a_2,a_3,\ldots,a_k$ 都是质数。

那么这个数 $x$ 最多可以执行 $b_1+b_2+b_3+\ldots+b_n$ 次操作，证明显然。

于是对于两个数 $x$ 和 $y$，设 $a$ 可以写成 ${a_1}^{b_1}\times {a_2}^{b_2}\times a_3^{b_3}\times \ldots\times {a_k}^{b_k}$，$b$ 可以写成 ${c_1}^{d_1}\times {c_2}^{d_2}\times c_3^{d_3}\times \ldots\times {c_l}^{d_l}$ 的形式，那么最多可以执行 $\sum_{i=1}^k b_i+\sum_{i=1}^l d_i$ 次操作。

设最小需要的步数为 $\zeta$，最大需要的步数为 $\xi$。

然后判断是否有 $\zeta\le k\le \xi$ 即可。

特殊情况：当 $k=1$ 的时候：

+ 如果 $a\bmod b\neq 0$ 且 $b\bmod a\neq 0$，那么一次操作无法使得 $a=b$。
+ 如果 $a=b$，那么一次操作无法使得 $a=b$。

## 3. 代码

[link](https://www.luogu.com.cn/paste/v35c4pk6)


---

## 作者：loser_seele (赞：0)

首先需要考虑操作次数的上限和下限，不难发现下限如果 $ a=b $ 则不需要操作，如果其中一个数等于两数 $ \gcd $ 则需要一次，否则需要两次。

操作次数的上限显然是将每个数变为 $ 1 $，则每次相当于除去一个质因子，答案为质因子的指数之和。

观察到两次操作可以合并为一次操作，那么首先 $ k $ 应该在上下限表示的区间内，然后特判一个数等于两数 $ \gcd $ 的情况下还需要额外满足 $ k=1 $ 即可。

分解质因数可以上 Pollard-rho 做到更优的复杂度，总时间复杂度 $ \mathcal{O}(Tn^\frac{1}{4}) $，其中 $ n=\max(a,b) $，可以通过。

[提交记录](https://codeforces.com/contest/1538/submission/193772637)

---

## 作者：wrzSama (赞：0)

## 思路

   我们只需要计算出使 $a$ 和 $b$ 相等的最多操作次数和最少操作次数，如果 $k$ 处于它们之间，就为可行的方案。我们可以看出，最多的操作次数为 $a$ 和 $b$ 的质因数个数之和，使两者最终都以最多操作次数变成了 $1$ 。而最少操作次数，则分为几种情况：当 $a$ 与 $b$ 相等时，最小操作次数为零且不能为 $1$ ；当 $a$ 是 $b$ 的因数或 $b$ 是 $a$ 的因数时，最小操作次数为 $1$ ；而其他的情况下，最小操作次数为 $2$ ，当 $a$ 和 $b$ 分别被一步除成 $1$ 时。所以我们只需要提前筛出所有小于等于 $\sqrt{10^9}$ 的质数，每次询问就可以用 $O(\sqrt n)$ 的时间复杂度求出 $a$ 和 $b$ 的质因数个数之和,可以卡过这道题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,n,m,k;
bool f[32005];
vector<ll>c;
int main()
{
	for(ll i=2;i<=32000;i++)
	{
		if(f[i]) continue;
		for(ll j=i+i;j<=32000;j+=i) f[j]=1;
		c.push_back(i);
	}
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld",&n,&m,&k);
		ll l=2,r=0;
		if(n%m==0||m%n==0) l=1;
		if(n==m&&k==1)
		{
			puts("NO");
			continue;
		}
		ll cnt=0;
		for(ll i=0;i<c.size()&&n>1;i++)
		{
			while(n%c[i]==0)
			{
				n/=c[i];
				r++;
			}
		}
		if(n>1) r++;
		for(ll i=0;i<c.size()&&m>1;i++)
		{
			while(m%c[i]==0)
			{
				m/=c[i];
				r++;
			}
		}
		if(m>1) r++;
		if(k<=r&&k>=l) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：123hh2 (赞：0)

--->[传送门](https://www.luogu.com.cn/problem/CF1538D)

---
### 题目大意
给定 $a$,$b$,$k$ 三数，要求我们通过恰好 $k$ 次操作，使得 $a=b$ 

其中，操作有两个：

- 选择一个能整除 $a$ 的大于 $1$ 的整数 $c$，用 $\dfrac{a}{c}$ 替换 $a$

- 选择一个能整除 $b$ 的大于 $1$ 的整数 $c$，用 $\dfrac{b}{c}$ 替换 $b$

多测，数据范围为 $1<a,b,k<10^9$

---
### 思路

首先我们能够知道，对于两个互质的数，他们能且仅能通过两次操作来实现 $a=b$ 

接下来分析不互质的情况，发现对于两个不互质的数，我们可以先使一个数一直操作直到该数变为 $1$，然后再让另一个数进行同样的操作，然后将两个数的操作数加起来，就是最大操作次数了，我们令这个数为 maxx

那么最小操作数呢？对于 $36$，$48$ 这两个数来说，可以通过互质的方法来获得最小操作次数，对于形如 $x,2x$ 这样的数，我们只需要通过一次操作就可以满足 $a=b$，剩下的就都需要两次操作了

这时我们会发现互质和不互质的情况 **差不多一样**，因为他们都有明确的上下界，所以我们在最后的时候可以将它们合并处理

---

### 代码

```cpp
#include<bits/stdc++.h>
#define ri register
#define _123hh2 0
using namespace std;
int gcd(int a,int b)
{
	if(!b)
	{
		return a;
	}
	else
	{
		gcd(b,a%b);
	}
}
inline int fen(int x)
{
	int sum=0,now=x;
	for(ri int i=2;i*i<=x;i++)
	{
		if(now==1)
		{
			break;
		}
		if(now%i==0)
		{
			while(now%i==0)
			{
				now/=i,sum++;
			}
		}
	}
	if(now>1)
	{
		sum++;
	}
	return sum;
}
int minn,maxx,a,b,k,t;
int main()
{
	scanf("%d",&t);
    while(t--)
    {
    	scanf("%d %d %d",&a,&b,&k);
    	if(a<b)//让 a 是最大的那个数
		{
			swap(a,b);
		}
    	int qwq=gcd(a,b);
    	//判断是否是整倍数
		if(qwq==b&&a!=b)
		{
			minn=1;	
		}
		else
		{
			minn=2;
		}
    	//求最大操作次数
    	maxx=2*fen(qwq)+fen(a/qwq)+fen(b/qwq);
		if(k>=minn&&k<=maxx)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
    return _123hh2;
}
//CF上交了一坨代码愣是超时了 
```
---

### 后记

我把三目运算符改成 if else 快读改成 scanf 和 printf 居然才能过，蒟蒻感到十分神奇

---

## 作者：xuanyuan_Niubi (赞：0)

# 题目大意
有 $ t $ 组数据，每组给定两个数 $ a $ 和 $ b $ 和操作次数 $ k $ 。

每次操作可以选 $ a $、$ b $ 中任意一个数，将其除以一个整数 $ c (c >1) $ ，要求必须是整除才可以操作。

问能否恰好操作 $ k $ 次使 $ a=b $ ，但并不要求在 $ k $ 次操作中不存在 $ a=b $ 。

数据范围: $ 1 \le t \le 10^4 , 1 \le a,b,k \le 10^9 $ 。
# 分析思路
对于两个数 $ a $ 、$ b $ ，什么时候会相等呢？因为并不要求除数 $ c $ 是质数，所以无论 $ a $ 、$ b $ 是多少，两个数各除以本身是一定可以使 $ a=b $ 的。此时操作次数 $ k=2 $ 。

但是如果 $ k=3 $ 呢？若 $ a $ 有 $ 2 $ 这个因子，那么将 $ a $ 先除以 $ 2 $ , 得到 $ a/2 $ 。再把 $ a/2 $ 除以 $ a/2 $ 就可得到 $ 1 $ 。$ b $ 还是除以自己得到 $ 1 $ 。

因此，发现 $ a $ 、 $ b $ 的每个质因子可以提供一次操作次数，只有 $ k \le $  $ a $ 、 $ b $ 的质因子总数才可以恰 $ k $ 次操作使 $ a=b $ 。（ $ c>1 $ ，所以 $ a $ 、 $ b $ 成了 $ 1 $ 之后不能再继续除下去了）

但是当操作次数 $ k=1 $  的时候呢？只可以操作 $ 1 $ 次，那么只有 $ a $ 是 $ b $ 的倍数或者 $ b $ 是 $ a $ 的倍数的时候才可以除 $ 1 $ 次就相等。（若不是倍数关系至少两个各除 $ 1 $ 次）

但是发现有 $ a=b,k=1 $ 的情况，这时候除 $ 1 $  次 $ a \ne b $ 。所以在 $ a=b $ 的时候，$ k $ 必须 $ \ge 2 $ 。（$ 2 \cdot 10^5 $ 是我胡诌的，应该是$ sqrt(10^9) $ ，不过影响不大）

现在还有一个最关键的问题，怎么分解质因子。先线性筛质数，筛到 $ 2 \cdot 10^5 $ 就够了，然后暴力除每个质因子。

但是如果 $ a $ 有 大于 $ 2 \cdot 10^5 $ 的因子怎么办？筛不出来啊。没有关系啊，我们先把所有小于 $ 2 \cdot 10^5 $ 的质因子全部除掉，剩下的大于 $ 2 \cdot 10^5 $ 的因子一定是个质因子。最后 $ +1 $ 就可以了。

# 贴代码
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int M=2e5+5;
inline int read(){
	char c=getchar();int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())if(c=='-')f=0;
	for(;c<='9'&&c>='0';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return f?x:-x;
}
inline void swap(int &a,int &b){a^=b^=a^=b;}
int pri[M],cnt;
bool is_pri[M*10];
inline void get_pri(){//线性筛质数 
	memset(is_pri,1,sizeof(is_pri));
	for(int i=2;i<=M;i++){
		if(is_pri[i])pri[++pri[0]]=i;
		for(int j=1;j<=pri[0]&&i*pri[j]<=M;j++){
			is_pri[i*pri[j]]=0;
			if(i%pri[j]==0)break;
		}
	}
}
inline void get_x(int a){//分解a的质因子，cnt是a b 的质因子个数之和 
	for(int i=1;i<=pri[0];i++){
		while(a%pri[i]==0)a/=pri[i],cnt++;
		if(a==1)break;
	}
	if(a!=1)cnt++;
}
inline void get_y(int b){
	for(int i=1;i<=pri[0];i++){
		while(b%pri[i]==0)b/=pri[i],cnt++;
		if(b==1)break;
	}
	if(b!=1)cnt++;
}
int main(){
	int T=read();
	get_pri();
	while(T--){
		int a=read(),b=read(),k=read();cnt=0;
		get_x(a),get_y(b);
		if(a==b){
			if(k>=2&&k<=cnt)printf("YES\n");//k既要>=2，又必须满足小于最大的操作次数 
			else printf("NO\n");
			continue;
		}
		if(k==1){
			if(a%b!=0)printf("NO\n");
			else printf("YES\n");
			continue;
		}
		if(k<=cnt)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

