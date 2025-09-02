# Prefix GCD

## 题目描述

Since Mansur is tired of making legends, there will be no legends for this task.

You are given an array of positive integer numbers $ a_1, a_2, \ldots, a_n $ . The elements of the array can be rearranged in any order. You need to find the smallest possible value of the expression $ $$$\gcd(a_1) + \gcd(a_1, a_2) + \ldots + \gcd(a_1, a_2, \ldots, a_n), $ $  where  $ \\gcd(a\_1, a\_2, \\ldots, a\_n) $  denotes the <a href="https://en.wikipedia.org/wiki/Greatest_common_divisor">greatest common divisor (GCD)</a> of  $ a\_1, a\_2, \\ldots, a\_n$$$.

## 说明/提示

In the first test case, the elements can be rearranged as follows: $ [2, 4, 2] $ . Then the answer will be $ \gcd(2) + \gcd(2, 4) + \gcd(2, 4, 2) = 2 + 2 + 2 = 6 $ .

In the third test case, the elements can be rearranged as follows: $ [6, 10, 15] $ . Then the answer will be $ \gcd(6) + \gcd(6, 10) + \gcd(6, 10, 15) = 6 + 2 + 1 = 9 $ .

## 样例 #1

### 输入

```
5
3
4 2 2
2
6 3
3
10 15 6
5
6 42 12 52 20
4
42 154 231 66```

### 输出

```
6
6
9
14
51```

# 题解

## 作者：HPXXZYY (赞：8)

$\color{blue}{\texttt{[Analysis]}}$

这题可以贪心。

正解就是把最小的 $a_{i}$ 放到最前面，然后每次选取和它的 $\gcd$ 最小的那一个数。

可是，为什么这样是对的？

先证明把最小的 $a_{i}$ 放在最前面最优。

> 先证明引理：若 $a<b$，有 $a+\gcd(a,b) \leq b$。
> 
> 我们知道 $\gcd(a,b)=\gcd(a,b-a)=\gcd(b,b-a)\leq (b-a)$，所以 $a+\gcd(a,b)=a+\gcd(a,b-a) \leq a+(b-a) = b$。

所以，如果将较大的 $a_{k}$ 放在前面的话，我们来看一张图（假设 $A$ 是最小的元素）：

![在这里插入图片描述](https://cdn.luogu.com.cn/upload/image_hosting/uom22c6l.png)

我们可以发现，上面蓝色部分对应的 $1,2,3$（代表算到这个数时的前缀 $\gcd$），会分别大于等于下面红色的 $1,2,3$。且上面蓝色算到 $A$ 的前缀 $\gcd$ 至少为 $1$。所以上面的蓝色的前缀 $\gcd$ 和为 $b+\color{blue}{1+2+3+4} \geq b+\color{blue}{1+2+3}\color{black}{+1}$。但是下面的前缀 gcd 的和为 $a+\gcd(a,b)+\color{red}{1+2+3} \color{black}{\leq b+}\color{blue}{1+2+3}$。所以显然下面的情况更优。

后面的贪心过程同理可以证明。

由于每次取 $\gcd$ 都会比上一次至少减少一半，所以时间复杂度为 $O(n \log \max\{a_{i}\})$。

$\color{blue}{\text{Code}}$

```cpp
const int N=1e5+100;
typedef long long ll;

const int inf=0x3f3f3f3f;

int n,a[N],lst,now,T;
ll ans;

int HPXXZYY(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	
	sort(a+1,a+n+1);
	
	if (n==1) return printf("%d\n",a[1]);
	
	now=a[1];
	for(int i=2;i<=n;i++)
		now=gcd(now,a[i]);
	
	ans=1ll*now*n+(a[1]-now);
	
	lst=a[1];
	int tmp=now;
	while (true){
		now=inf;
		for(int i=1;i<=n;i++)
			now=min(now,gcd(lst,a[i]));
		
		lst=now;
		ans+=lst-tmp;
		
		if (lst==tmp) break;
	}
	
	return printf("%lld\n",ans);
}

int main(){
	T=read();
	while (T--) HPXXZYY();
	
	return 0;
}
```

---

## 作者：缪凌锴_Mathew (赞：3)

记值域为 $V$，最终数组为 $b$，令 $pre_i=\gcd(b_1,b_2,\dots,b_i)$。

先把 $G=\gcd(a_1,a_2,\dots,a_n)$ 提出来，$a_i\gets \dfrac{a_i}{G}$，最后答案再乘上 $G$。

这样 $pre_n$ 肯定是 $1$，我们发现假如存在 $pre_i=pre_{i-1} \operatorname{and} pre_i\ne 1$，那么肯定不优。所以 $pre$ 除了前 $\log V$ 项应该都是 $1$。

于是可以开始 dp，$dp_{i,j}$ 表示 $pre_i=j$ 的 $\sum\limits_{k=1}^i pre_k$ 的最小值。

记 $f_{x,y}$ 为 $\exist i,\gcd(a_i,x)=y$。那么转移方程为：

$$dp_{i,j}=\min_{f_{k,j}=1}dp_{i-1,k}+j$$

记 $L=\min(n,\log V)$，答案为 $G\times (dp_{L,1}+n-L)$，加上的 $n-L$ 表示 $pre$ 剩下的全是 $1$ 的部分。

现在问题来了，如何求出 $f$ 数组？

观察 $\exist i,\gcd(a_i,x)=y$ 这个式子，显然 $y\nmid x$ 时 $f_{x,y}=0$。

枚举 $y$，处理出 $T$ 为是 $y$ 的倍数的 $a_i$ 的集合，$S=\{\dfrac{x}{y}|x\in T\}$，那么：

$$\exist i,\gcd(a_i,x)=y$$

相当于 

$$\exist t\in S,\gcd(x,t)=1$$

于是我们处理出 $g(x)$ 表示 $\sum\limits_d [(x\times d)\in S]$，那么 $f_{x,y}=[\sum\limits_{d|(y/x)}\mu(d)g(d)\ne0]$。

这是因为 $t$ 对 $x$ 的贡献为 $\sum\limits_{d|t,d|x}\mu(d)=\sum\limits_{d|\gcd(t,x)}\mu(d)=[\gcd(t,x)=1]$。

分析时间复杂度：

$$
\begin{aligned}
&\sum_{y=1}^V \sum_{d=1}^{\lfloor\frac{V}{y}\rfloor}\lfloor\frac{\lfloor\frac{V}{y}\rfloor}{d}\rfloor\\
=&\sum_{y=1}^V \lfloor\frac{V}{y}\rfloor\ln\lfloor\frac{V}{y}\rfloor\\
=&O(V\ln^2V)
\end{aligned}
$$

### Code


```cpp
#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=1e5+10;
const int N=1e5;
const int INF=0x3f3f3f3f;
const long long LINF=0x3f3f3f3f3f3f3f3f;
int n,m,mul,ans=0;
int a[MAXN];
bool* f[MAXN];
int cnt[MAXN],mob[MAXN];
bool vis[MAXN];
int dp[MAXN],lst[MAXN];//dp这里我加了滚动数组
basic_string <int> fac[MAXN];
inline void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    mul=a[1];
    for(int i=1;i<=n;i++)
    {
        mul=__gcd(mul,a[i]);
    }
    m=0;
    for(int i=1;i<=n;i++)
    {
        a[i]/=mul;
        m=max(m,a[i]);
    }
    memset(vis,false,sizeof(bool)*(m+1));
    for(int i=1;i<=n;i++)
    {
        vis[a[i]]=true;
    }
    for(int i=1;i<=m;i++)
    {
        memset(f[i],false,sizeof(bool)*(m/i+1));
        memset(cnt,0,sizeof(int)*(m/i+1));
        for(int j=1;j<=m/i;j++)
        {
            if(vis[i*j]){
                for(int x:fac[j])
                {
                    cnt[x]++;
                }
            }
        }
        for(int j=1;j<=m/i;j++)
        {
            int sum=0;
            for(int x:fac[j])
            {
                sum+=cnt[x]*mob[x];
            }
            if(sum){
                f[i][j]=true;
            }
        }
    }
    memset(dp,0x3f,sizeof(int)*(m+1));
    for(int i=1;i<=n;i++)
    {
        dp[a[i]]=a[i];
    }
    for(int i=2;i<=n&&i<=20;i++)
    {
        memcpy(lst,dp,sizeof(int)*(m+1));
        memset(dp,0x3f,sizeof(int)*(m+1));
        for(int x=1;x<=m;x++)
        {
            for(int y:fac[x])
            {
                if(f[y][x/y]){
                    dp[y]=min(dp[y],lst[x]+y);
                }
            }
        }
    }
    if(n<=20){
        printf("%lld\n",1ll*mul*dp[1]);
    }
    else{
        printf("%lld\n",1ll*mul*(dp[1]+n-20));
    }
}
inline void init(){
    for(int i=1;i<=N;i++)
    {
        f[i]=new bool[N/i+1];
        for(int j=i;j<=N;j+=i)
        {
            fac[j].push_back(i);
        }
    }
    mob[1]=1;
    for(int i=1;i<=N;i++)
    {
        for(int j=i+i;j<=N;j+=i)
        {
            mob[j]-=mob[i];
        }
    }
}
signed main(){
    init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：RAND_MAX (赞：1)

### 题意简述
给定一个序列 $a$，求将 $a$ 重排后前缀 $\gcd$ 和的最小值。
### 思路
我们先将 $a$ 除以整个数列的 $\gcd$，最终只需将修改后序列的答案乘 $\gcd$ 即可，不难证明两者等同。下文所述序列均为修改后序列。

由于序列中所有元素的 $\gcd=1$，我们又想要前缀 $\gcd$ 和最小，由于前缀 $\gcd$ 单调不降，故至多 $7$ 次便可以将前缀 $\gcd$ 变成 $1$。（$2\times 3\times 5\times 7\times 11\times 13\times 17=510510>V$）

给出一个结论：第一个数选序列最小值，之后只需选能使前缀 $\gcd$ 最小的即可。下面给出证明。

假设存在一种答案序列 $b$ 满足 $b_1\ne \min\limits_{i=1}^na_i$。假设 $b_k=\min\limits_{i=1}^na_i$，那么我们考虑另一种答案序列 $c$ 为把最小值提到序列首，其余不变。那么第 $k$ 位之后两序列的值及前缀 $\gcd$ 均不变。我们设前缀 $\gcd$ 序列分别为 $B,C$，下面只考虑序列的前 $k$ 位。\
给出一个定理：若 $x<y$，那么有 $x+\gcd(x,y)\le y$。\
由于 $c_{i+1}=b_i$，所以有 $C_{i+1}=\gcd(b_k,B_i)$，因为 $b_k+\gcd(b_k,b_1)\le b_1$，故 $C_1+C_2\le B_1$。由于 $\gcd(x,y)\le x$，所以有 $C_3\le B_2,C_4\le B_3,...,C_k\le B_{k-1}$。又因为 $B_k>0$，所以有 $\sum C_i\le \sum B_i$，当且仅当 $k=1$ 时取等。\
对于非第一位的策略，证明同上，不再赘述。于是我们就证明了上述结论。
### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
void write(int x)
{
	static int st[35],top=0;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	do
	{
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top)
	{
		putchar(st[--top]+48);
	}
	putchar('\n');
}
int T,n,ans,a[100010],sum,g,now; 
signed main()
{
	T=R;
	while(T--)
	{
		n=R;
		int GG=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=R;
			GG=__gcd(GG,a[i]);
		}
		sort(a+1,a+n+1);
		ans=g=a[1];
		for(int i=2;i<=n;i++)
		{
			if(g==GG) ans+=GG;
			else
			{
				for(int j=i+1;j<=n;j++)
				{
					if(__gcd(g,a[j])<__gcd(g,a[i])) swap(a[i],a[j]);
				}
				g=__gcd(g,a[i]);
				ans+=g;
			}
		}
		write(ans);
	}
 	return 0;
}

```
### 对于当 $x<y$ 时，$x+\gcd(x,y)\le y$ 的证明。
设 $\gcd(x,y)=k,x=a\times k,y=b\times k$。\
因为 $x<y$，所以 $a<b\Leftrightarrow a+1\le b$。所以 $x+\gcd(x,y)=a\times k+k=(a+1)\times k\le b\times k=y$。\
故上述结论成立。

---

## 作者：Eznibuil (赞：1)

容易发现，最后的一项必定是所有数的 gcd，只有这一项会重复。这是因为，如果中间有比这个大的重复了，那么一定可以把后面的数调换到前面来，让其不重复。

所以可以将题面改写为构造一个新的序列 $b_1,\dots,b_n$，其中对于所有 $b_i$ 都有 $b_i\in\{a_1,\dots,a_n\}$。可以证明答案和原问题相同。

然后注意到既然前面不会重复，后一项只能变成前一项真因数，设值域 $W$，则至多 $O(\log W)$ 项后即会变成所有数的 gcd。

另一个结论是如果有两个正整数 $a,b$ 满足 $a<b$，那么 $a+\gcd(a,b)\le b$。由此可以证明，如果当前选择的数无法最小化当前 gcd，那么再插入另外一个令当前 gcd 更小的数以后，即便是序列多了一项，也会小于等于原来的和，那么把多的一项砍掉就必定小于了，所以每一步都会选择最小化当前 gcd 的数。

于是贪心求解即可。时间复杂度 $O(\sum n\log^2W)$。
```cpp
#include<algorithm>
#include<iostream>
#include<numeric>
int a[100001];
int main()
{
	std::cin.tie(0)->sync_with_stdio(0);
	int t;
	std::cin>>t;
	while(t--)
	{
		int n,ga=0;
		std::cin>>n;
		for(int i=0;i<n;i++)
			std::cin>>a[i],ga=std::gcd(ga,a[i]);
		long long ans=0;
		int g=0;
		for(int i=0;i<n;i++)
		{
			int x=1e9;
			for(int j=0;j<n;j++)
				x=std::min(x,std::gcd(g,a[j]));
			ans+=g=x;
			if(g==ga)
			{
				ans+=(n-i-1ll)*g;
				break;
			}
		}
		std::cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

首先 $\gcd$ 有一个性质：在一个排列中去做 $\gcd$，做 $\log V$ 次就会变成 $1$。

首先对于这道题，第一个数贪心地要填最小的数。

对于剩下的数，考虑增量构造。假设当前构造完 $1 \sim i$，前缀 $\gcd$ 是 $g$。下一个数贪心地选择之前未选择的，并且与 $g$ 的 $\gcd$ 最小的数。如果对于剩下的所有的数 $a$，$\gcd(a, g)$ 都 与 $g$ 相同，后面的数就可以以任意顺序添加。

势能分析得复杂度线性对数。[Submission](https://codeforces.com/contest/2013/submission/282147447)。

---

## 作者：Defy_HeavenS (赞：0)

### 思路

首先要知道 $\gcd$ 有个很重要的性质，为 $\gcd(a,b)\le \min(a,b)$。

又因为我们要尽可能小，所以 $\gcd$ 最多做 $7$ 次（$2\times 3\times 5\times 7\times 11\times 13\times 17=510510>10^5$），剩下的不管怎样就全是 $\gcd_{i=1}^{n}a_i$ 了（换句话说是所有元素的 $\gcd$）。

能不能贪心地去做呢？答案是可以的。因为 $\gcd(a,b)\le \min(a,b)$，所以前面选一个最优的选法，后面更劣的选法就会被这个优的选法盖住（反正你模拟模拟样例就知道了）。

同理，可以证明第一个数选最小的数是最优的。

### 代码

```cpp
#include<bits/stdc++.h>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define pb push_back

using namespace std;
typedef long long LL;
typedef pair<LL,LL> PII;

const LL N=1e5+5;
LL n,a[N],b,ans,Gcd;

void solve(){
	ans=0;
	cin>>n;
	bitset<N>vis;
	for(LL i=1;i<=n;i++){
		cin>>a[i];
		Gcd=__gcd(Gcd,a[i]);
	}
	sort(a+1,a+1+n);
	b=ans=a[1];
	vis[1]=1;
	LL val=n-7;
	for(LL i=1,mi,k;i<=6;i++){
		mi=1e9,k=-1;
		for(LL j=2;j<=n;j++){
			if(!vis[j]&&__gcd(b,a[j])<mi){
				mi=__gcd(b,a[j]);
				k=j;
			}
		}
		if(k==-1){
			val=0;
			break;
		}
		b=mi;
		ans+=b;
		vis[k]=1;
	}
	cout<<ans+val*Gcd<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	LL t=1;cin>>t;
	while(t--) solve();
	return 0;
}
/*

*/
```

---

