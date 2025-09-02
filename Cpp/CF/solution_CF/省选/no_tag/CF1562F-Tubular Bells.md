# Tubular Bells

## 题目描述

Do you know what tubular bells are? They are a musical instrument made up of cylindrical metal tubes. In an orchestra, tubular bells are used to mimic the ringing of bells.

Mike has tubular bells, too! They consist of $ n $ tubes, and each of the tubes has a length that can be expressed by a integer from $ l $ to $ r $ inclusive. It is clear that the lengths of all the tubes are different (it makes no sense to make the same tubes). It is also known that $ r-l+1 = n $ .

Formally, we can say that Mike's tubular bells are described by a permutation $ a $ of length $ n $ that contains all numbers from $ l $ to $ r $ inclusive, with $ a_i $ denoting the length of the $ i $ -th tube.

You are offered an interesting task: to guess what Mike's instrument looks like. Simply, you must guess the permutation.

Mike won't tell you $ l $ or $ r $ . He will only tell you $ n $ , and will allow you to ask no more than $ n + 5000 $ queries.

In each query, you name two positive integers $ x $ , $ y $ such that $ 1 \le x, y \le n, x \neq y $ . In response to this query, the program written by Mike will give you $ \mathrm{lcm}(a_x, a_y) $ , where $ \mathrm{lcm}(c,d) $ denotes the least common multiple of $ c $ and $ d $ .

Solve Mike's problem!

## 样例 #1

### 输入

```
3
5
8 10 7 6 9
5
24 25 28 27 26
7
1 2 3 4 5 6 7```

### 输出

```
? 1 2
40
? 2 5
90
? 3 1
56
? 4 5
18
! 8 10 7 6 9
? 1 5
312
? 2 4
675
! 24 25 28 27 26
? 1 4
4
? 2 5
10
? 3 7
21
? 6 2
6
? 2 5
10
? 1 2
2
? 1 2
2
? 1 2
2
? 1 2
2
? 1 2
2
! 1 2 3 4 5 6 7```

# 题解

## 作者：dead_X (赞：8)

## 小范围暴力
显然我们询问完 $O(n^2)$ 次之后我们一定可以知道整个序列的信息。

一种构造方法：找到最大值和次大值（它们的 $\text{lcm}$ 一定是最大的），然后将这两个值和剩下的取 $\text{lcm}$ 之后将集合进行比较即可。

找到次大值之后，继续尝试在剩下的数中找出最大的，依旧利用 $\text{lcm}(x,x-1)=x(x-1)$ 即可。

这样大概可以用附加的 $5000$ 次询问解决 $n\leq 100$ 的情况。
## 大范围随机
我们发现，如果有一个数和所有数的 $\text{lcm}$ 都是两数的乘积，我们在推断出来这个数之后就可以用 $n-1$ 次询问求出其它所有的数了。

这个条件就显然等于它和每个数的 $\gcd$ 都等于 $1$，也就是说这个数应该是一个质数 $p$，且 $2p$ 不存在于序列中。也就是说，$p$ 是 $\geq\frac{r}{2}$ 的质数。

$2\times 10^5$ 内素数的密度可以大致看成 $\frac{1}{10}$，也就是说，符合要求的数大概有 $\geq10^5\times\frac{1}{2}\times\frac{1}{10}=500$ 个。

知道了这一点，我们考虑我们在 $5000$ 次询问中能覆盖 $10000$ 个数，而其中有符合要求的数的概率就很大了。

现在我们考虑，如果询问的两个数中其中一个数合法，返回的 $\text{lcm}$ 有什么特征。很好发现的是，这里面一定有一个巨大的因数 $p$。

因此我们直接对于所有询问，找到答案中最大质因子最大的，就可以默认那一对中存在答案了。

找到这一对数 $(x,y)$ 之后，我们另外找一个数 $z$ 与 $x$ 询问，如果答案含有这个巨大因数，那么 $a_x=p,a_y=\frac{\text{lcm}(a_x,a_y)}{p}$，反之亦然。

于是你就找到这个 $p$ 了，直接每个查询一遍即可。

为什么这个东西在小范围不能用呢？因为范围内两个质数之间的最大距离大概为 $90$，所以小范围内可能根本不存在符合要求的数。
## 代码
贴了个 pollard-rho 所以比较长。

```cpp
//And in that light,I find deliverance.
#include<bits/stdc++.h>
using namespace std;
#define li inline
#define re register
#define ll __int128
#define abs(a) ((a)>0?(a):-(a))
namespace Miller_Rabin
{
	const int Pcnt=12;
	const ll p[Pcnt]={2,3,5,7,11,13,17,19,61,2333,4567,24251};
	li ll pow(re ll a,re ll b,re ll p)
	{
		re ll ans=1;
		for(;b;a=a*a%p,b>>=1)if(b&1)ans=ans*a%p;
		return ans;
	}
	li bool check(re ll x,re ll p)
	{
		if(x%p==0||pow(p%x,x-1,x)^1)return true;
		re ll t,k=x-1;
		while((k^1)&1)
		{
			t=pow(p%x,k>>=1,x);
			if(t^1&&t^x-1)return true;
			if(!(t^x-1))return false;
		}return false;
	}
	inline bool MR(re ll x)
	{
		if(x<2)return false;
		for(re int i=0;i^Pcnt;++i)
		{
			if(!(x^p[i]))return true;
			if(check(x,p[i]))return false;
		}return true;
	}
}
namespace Pollard_Rho
{
	#define Rand(x) (1ll*rand()*rand()%(x)+1)
	li ll gcd(const ll a,const ll b){return b?gcd(b,a%b):a;}
	li ll mul(const re ll x,const re ll y,const re ll X)
	{
		ll k=(1.0L*x*y)/(1.0L*X)-1,t=x*y-k*X;
		while(t<0)t+=X;return t;
	}
	li ll PR(const re ll x,const re ll y)
	{
		re int t=0,k=1;re ll v0=Rand(x-1),v=v0,d,s=1;
		while(true)
		{
			v=(mul(v,v,x)+y)%x,s=mul(s,abs(v-v0),x);
			if(!(v^v0)||!s)return x;
			if(++t==k){if((d=gcd(s,x))^1)return d;v0=v,k<<=1;}
		}
	}
	li void Resolve(re ll x,re ll&ans)
	{
		if(!(x^1)||x<=ans)return;
		if(Miller_Rabin::MR(x)){if(ans<x)ans=x;return;}
		re ll y=x;while((y=PR(x,Rand(x)))==x);while(!(x%y))x/=y;
		Resolve(x,ans);Resolve(y,ans);
	}
	li long long check(ll x)
	{
		re ll ans=0;Resolve(x,ans);
		return ans;
	}
}
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int p[100030],cnt=0;
bool vis[200003];
void init(int n=200000)
{
    for(int i=2; i<=n; ++i) if(!vis[i])
    {
        p[++cnt]=i;
        for(int j=2; i*j<=n; ++j) vis[i*j]=1;
    }
    //printf("%lld\n",cnt);
    return ;
}
int a[100003];
int f[103][103];
bool t[100003];
int query(int x,int y){
    printf("? %lld %lld\n",x,y);
    fflush(stdout);
    return read();
}
int Lcm(int x,int y){
    return x/__gcd(x,y)*y;
}
signed main()
{
    init();
	for(int T=read();T--;)
	{
		int n=read();
        if(n<=90)
        {
            for(int i=1; i<=n; ++i) t[i]=0;
            for(int i=1; i<n; ++i)
                for(int j=i+1; j<=n; ++j)
                    f[i][j]=f[j][i]=query(i,j);
            int s=-1,A=0,B=0;
            for(int i=1; i<n; ++i)
                for(int j=i+1; j<=n; ++j)
                    if(f[i][j]>s) s=f[i][j],A=i,B=j;
            int r=(sqrt(s*4+1)+1)/2,l=r-n+1;
            multiset<int> s1,s2,s3;
            for(int i=l; i<=r-2; ++i) s3.insert(Lcm(i,r));
            for(int i=1; i<=n; ++i) if(i!=A&&i!=B) s1.insert(f[i][A]);
            for(int i=1; i<=n; ++i) if(i!=A&&i!=B) s2.insert(f[i][B]);
            assert(s1!=s2);
            int pos,val=r-1;
            if(s1==s3) a[A]=r,a[B]=r-1,pos=B;
            else a[A]=r-1,a[B]=r,pos=A;
            t[A]=t[B]=1;
            while(val>l)
            {
                for(int i=1; i<=n; ++i) if(!t[i]&&f[i][pos]==val*(val-1))
                {
                    a[i]=val-1;
                    t[i]=1;
                    pos=i;
                    break;
                }
                --val;
            }
        }
        else
        {
            mt19937 rnd(time(0));
            int A=0,B=0,C=0,D=0;
            for(int i=1; i<=4900; ++i)
            {
                int x=rnd()%n+1,y=rnd()%n+1;
                while(x==y)
                {
                    x=rnd()%n+1,y=rnd()%n+1;
                }
                int g=query(x,y),q=Pollard_Rho::check(g);
                if(q>D) D=q,C=g,A=x,B=y;
            }
            //C is lcm,D is the largest d
            int ano=rnd()%n+1;
            while(ano==A||ano==B) ano=rnd()%n+1;
            int tmp=query(ano,A),va,vb,qqq;
            if(tmp%D==0)
            {
                va=D,vb=C/D,qqq=A;
            }
            else va=C/D,vb=D,qqq=B;
            for(int i=1; i<=n; ++i)
            {
                if(A==i)
                {
                    a[i]=va;
                }
                else if(B==i)
                {
                    a[i]=vb;
                }
                else
                {
                    if(qqq==A) a[i]=query(i,A)/D;
                    else a[i]=query(i,B)/D;
                }
            }
        }
        printf("! ");
        for(int i=1; i<=n; ++i) printf("%lld ",a[i]);
        puts("");
        fflush(stdout);
	}
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：4)

注意到所有数排序后是数轴上的连续正整数段，值域的范围比 $n$ 大。

首先我们知道 $x\times y= \operatorname{lcm}(x,y) \times \gcd(x,y)$。

如果我们有一个大于最大值一半的素数，显然可以一遍跑出来。

打表发现范围内最长不出现素数的区间不大，为 $85$。

考虑特别处理长度小的情况。

以下数若无特殊说明均指正整数。

首先证明一个东西，对于任意一个数 $x$ 满足 $\gcd(\operatorname{lcm}(x,x+1),\operatorname{lcm}(x,x+2))=x$。

我们知道，相邻两个数必然互素，相邻两个奇数必然互素，相邻两个偶数的 $\gcd$ 必然为 $2$。

分情况讨论，如果 $x$ 为奇数，两个 $\operatorname{lcm}$ 分别是 $x\times (x+1)$ 和 $x\times (x+2)$，显然 $\gcd$ 等于 $x$。

如果 $x$ 为偶数，两个 $\operatorname{lcm}$ 分别是 $x\times (x+1)$ 和 $\frac{x\times (x+2)}{2}$，显然 $x+1$ 和 $\frac{x+2}{2}$ 互素，那么 $\gcd$ 也等于 $x$。

同理，$\gcd(\operatorname{lcm}(x,x-1),\operatorname{lcm}(x,x-2))=x$，但是 $x$ 需要大于 $2$。

一个数和任意一个数取 $\operatorname{lcm}$ 显然是这个数的倍数，所以说把第 $i$ 个数与所有与它不同的数求 $\operatorname{lcm}$ 并取 $\gcd$ 就能得到第 $i$ 个数。

对于 $n=3$ 特判，因为中间数是没有 $x+2$ 或 $x-2$ 的。这个数按照上面算出来的结果要么是 $x$ 要么是 $2x$，剩下两个数应该绝对值差为 $2$，直接两两比对即可。 

注意要记忆化一下卡一下询问次数。

然后考虑怎么 $5000$ 次找到一个大于一半的素数。$n$ 与值域同阶，所以期望有 $\frac{n}{2\ln n}$ 个素数，$n=10^5$ 时素数密度约为 $0.043429$，最低的区间也有 $0.01$。随机 $P=250$ 次选到大于一半的素数的概率非常大。

问题是判断一个数是否是大于一半的素数并求出值。

现有要确定值 $x$，考虑随机 $Q=20$ 个 $y$。对于每个 $y$，$\operatorname{lcm}=x\times \frac{y}{\gcd(x,y)}$。对所有的 $\operatorname{lcm}$ 取 $\gcd$，发现只需要满足所有 $\frac{y}{\gcd(x,y)}$ 的 $\gcd$ 为 $1$ 即可。

$\gcd(x,y)$ 不等于 $1$ 时满足条件的概率显然比等于 $1$ 的要大，所以仅考虑 $x,y$ 互素即可。 

随机 $k$ 个数 $\gcd=1$ 的概率是 $\frac{1}{\zeta(k)}$，当 $k$ 取 $20$ 时满足条件的概率非常大。

事先筛出素数，然后每次判断找出来的是不是素数，如果是素数再取最大值即可。

这时满足 $P\times Q \leq 5000$，符合要求。

最后得出来的最大素数跑一遍即可得到所有数。

其实可以适当提高 $P$ 降低 $Q$ 可以进一步提高准确率，可以进行一下平衡。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
const int M=90;
int n,a[N],b[M][M],prime[N];
int rnd(){
	return ((rand()*rand())^(rand()*rand()))%n+1;
}
int gcd(int x,int y){
	if(!x)
		return y;
	return __gcd(x,y);
}
int ask(int x,int y){
	if(n<=85){
		if(x>y)
			swap(x,y);
		if(b[x][y]!=0)
			return b[x][y];
		cout<<"? "<<x<<' '<<y<<endl;
		b[x][y]=read();
		return b[x][y];
	}
	cout<<"? "<<x<<' '<<y<<endl;
	int p=read();
	return p;
}
void print(){
	cout<<"! ";
	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	cout<<endl; 
	for(int i=1;i<=n;i++)
		a[i]=0;
	memset(b,0,sizeof(b));
}
int get(int x){
	int res=0;
	for(int i=1;i<=n;i++){
		if(i==x)
			continue;
		int p=ask(i,x);
		if(!res)
			res=p;
		else res=__gcd(res,p);
	}
	return res;
}
signed main()
{
	for(int i=2;i<N;i++){
		if(prime[i])
			continue;
		for(int j=i+i;j<N;j+=i)
			prime[j]=1;		
	}
	int T=read();
	while(T--){
		n=read();
		if(n<=85){
			if(n==3){
				for(int i=1;i<=n;i++)
					a[i]=get(i);
				if(abs(a[1]-a[2])==2)
					a[3]=(a[1]+a[2])/2;
				else if(abs(a[1]-a[3])==2)
					a[2]=(a[1]+a[3])/2;
				else if(abs(a[2]-a[3])==2)
					a[1]=(a[2]+a[3])/2;
				print();
				continue;
			}	
			for(int i=1;i<=n;i++)
				a[i]=get(i);
			print();
			continue;
		}
		int t=250,res=0,index=0;
		while(t--){
			int x=rnd(),p=0;
			for(int i=1;i<=20;i++){
				int y=rnd();
				while(x==y)
					y=rnd();
				p=gcd(p,ask(x,y));
			}
			if(prime[p])
				continue;
			if(p>res){
				res=p;
				index=x;
			}
		}
		a[index]=res;
		for(int i=1;i<=n;i++){
			if(i==index)
				continue;
			a[i]=ask(i,index)/res;
		}
		print();
	}
	return 0;
}
```



---

## 作者：船酱魔王 (赞：1)

## 题意回顾

未知的长度为 $ n $ 的一个连续自然数排列，每次查询两个数的 $ \operatorname{lcm} $，请求出这个序列。

$ 3 \le n \le 10^5 $，**询问次数 $ n+5000 $**。

## 分析

考虑如何一次扫描确定所有数？如果有一个质数的话，可以用它和所有数取 $ \operatorname{lcm} $ 得出那些数的值，注意这个质数必须大于值域的一半，否则无法正确处理它的倍数。

暴力枚举可知，$ 1 \sim 2 \times 10^5 $ 中最多有连续 $ 85 $ 个数不出现质数，考虑 $ n > 200 $ 时必然有满足条件的质数，并且出现频率不低。

如何判断一个数是什么？考虑随机 $ 20 $ 个位置与它取 $ \operatorname{lcm} $，再取这些 $ \operatorname{lcm} $ 的 $ \gcd $ 即可。错判只有这些随机的位置的 $ \gcd $ 大于 $ 1 $ 的情况，概率大概是 $ (1-\frac{1}{2^{20}})(1-\frac{1}{3^{20}})(1-\frac{1}{5^{20}})  \cdot \cdot \cdot \approx 1-\frac{1}{2^{19}} $ 左右，可以接受。

我们可以随机找 $ 250 $ 个位置判断，取最大的一个质数，再进行一次扫描即可。

$ n \le 200 $ 时，直接用单点求值的方式暴力计算即可。

$ n=3 $ 时，可能有两个偶数夹一个奇数的情况，需要特判。

### 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <utility>
#include <cstring>
#include <set>
using namespace std;
const int N = 1e5 + 5;
int T;
int n;
int ans[N];
int rnd() {
    return ((rand() % 32768) << 15) | (rand() % 32768);
}
long long gcd(long long x, long long y) {
    return (y == 0) ? x : gcd(y, x % y);
}
map<pair<int, int>, long long> mp;
long long getlcm(int x, int y) {
    if(x > y) swap(x, y);
    if(mp.find((pair<int, int>){x, y}) != mp.end()) return mp[(pair<int, int>){x, y}];
    cout << "? " << x << " " << y << endl;
    long long tx;
    cin >> tx;
    return mp[(pair<int, int>){x, y}] = tx;
}
int chk[N * 2];
bool check(int x) {
    if(chk[x] != -1) return chk[x];
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) return chk[x] = false;
    }
    return chk[x] = true;
}
int getval(int x) {
    long long gyr = 0;
    set<int> se;
    se.clear();
    for(int i = 1; i <= min(20, n - 1); i++) {
        int t = rnd() % n + 1;
        if(x == t || se.find(t) != se.end()) {
            i--;
            continue;
        }
        se.insert(t);
        if(!gyr) gyr = getlcm(x, t);
        else gyr = gcd(gyr, getlcm(x, t));
    }
    return gyr;
}
int main() {
    memset(chk, -1, sizeof(chk));
    srand(38388844);
    cin >> T;
    for(int ti = 1; ti <= T; ti++) {
        cin >> n;
        mp.clear();
        if(n <= 250) {
            int mi = 1e9 + 5;
            for(int i = 1; i <= n; i++) {
                ans[i] = getval(i);
                mi = min(mi, ans[i]);
            }
            if(n == 3) {
                for(int i = 1; i <= n; i++) {
                    if(ans[i] / 2 > mi) ans[i] /= 2;
                }
            }
        } else {
            int pos, val;
            val = 0, pos = 0;
            for(int i = 1; i <= 250; i++) {
                int t = rnd() % n + 1;
                int thi = getval(t);
                if(check(thi)) {
                    if(thi > val) {
                        val = thi;
                        pos = t;
                    }
                }
            }
            ans[pos] = val;
            for(int i = 1; i <= n; i++) {
                if(i != pos) ans[i] = getlcm(i, pos) / val;
            }
        }
        cout << "! ";
        for(int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}

```

---

## 作者：Leap_Frog (赞：1)

### Link.
[Codeforces](https://codeforces.com/contest/1562/problem/F)  
[Luogu](https://www.luogu.com.cn/problem/CF1562F)  
[更卡哇伊的阅读体验](https://www.cnblogs.com/pealfrog/p/15203614.html)  

### P.S.
和滴叉思路差不多，主要来补充一点注意点

### Description.
给定一个长度为 $n$ 的序列，是一个 $[l,\dots,r]$ 的排列。  
给定 $n$，每次可以询问任意不同两个的 $\text{lcm}$，要在 $n+5000$ 的复杂度内问出序列。  

### Solution.
#### 小数据暴力
首先有个很显然的询问数 $\frac {n\cdot(n-1)}2$ 的做法。  
解一下方程发现 $\frac{n\cdot (n-1)}2=n+5000$ 的解大概是 `101.511249367`。  
所以有一个显然的 $O(n^3)$ 做法，找到最大的数，它必定是 $(r-1)\cdot r$。  
然后每次找到没标记过的 $i\cdot (i-1)$ 即可。  
#### 大数据随机
我们发现在长度比较长的情况下，质数分布概率是比较高的，大概是 $\frac 1{\log n}\ge\frac 1{20}$。  
考虑随机 rand $10000$ 个数，其中没有质数的概率是 $1-\left(\frac {19}{20}\right)^{10000}$，已经很小了。  
然后对于一个质数和其他数 $\text{lcm}$ 显然有一个很大的质因子。  
我们对于每个询问，找到最大质因子的最大值就可以假装它是原序列的一个数。  
然后我们找到了质数的情况下，可以直接去问它和任意数的 $\text{lcm}$ 然后就可以 $n-1$ 次询问得到整个序列。  

### Attention.
1. 他妈多组询问的交互题就是屑，一个点 WA 会导致后面的 tests TLE，然后让我以为我质因数分解太慢了，调了一年。
2. 大概就有一段长度为 $85$ 的区间 $[155922,156006]$ 里面没有一个质数，所以小数据暴力一定要开尽量大。
3. 因为这题很显然我们需要分解的数虽然很大，但是它 $2,3$ 等较小数出现概率比较高，所以直接暴力分解是可以的。  

### Coding.
这份代码是在是有点怪，发在这里有点污染题解版面。  
建议去 [blog](https://www.cnblogs.com/pealfrog/p/15203614.html) 阅读qwq。

---

## 作者：Purslane (赞：0)

# Solution

考虑在答案区间 $[l+1,l+n]$ 中，**最大的质数**必然满足 $p \le l+n < 2p$。那么再这个区间里面除了 $p$ 以外所有的数都有：$\text{lcm}(a,p) = ap$。事实上，任何一个质数满足 $ l < p \le l+n < 2p$ 都有这个性质。

但是这么做有一个逻辑漏洞：有可能 $[l+1,l+n]$ 中**一个素数都没有**。打表发现，这样区间的不会超过 $100$ 的长度。而这时候我们反而就可以用 $\dfrac{n(n-1)}{2}$ 次操作找到两两下标之间的答案，其中的最大数必然就等于 $(l+n)(l+n-1)$，然后就确定了 $r=l+n$ 和它的两个可能的位置。然后由于 $(r-1)(r-2)$ 只能是 $r-1$ 和 $r-2$ 它们的最小公倍数，所以你确定了 $r$，$r-1$ 和 $r-2$ 分别在哪里。

然后看一看 $r-2$ 和剩下的数的最小公倍数，利用 $(r-2)(r-3)$ 的位置唯一确定一下 $r-3$ 的位置，然后依次推到 $l+1$。

当 $n$ 比较大的时候，考虑用 $5000$ 次操作随机出一个大的质数。

这时候你可以先随 $250$ 个位置，比如其中一个是 $i$，每个位置再随 $20$ 个其他的位置，比如其中一个是 $j$，把所有的 $\text{lcm} (x_i,x_j)$ 取最大公约数，这样得到了一个 $x_i$ 的倍数。如果他是质数，那么就可以假装 $x_i$ 就是这个数（还是有可能有 $x_i=1$。但是这要求另外 $20$ 个数都是这个质数的倍数。在质数比较大的时候不大可能发生。）

考虑符合要求的质数差不多有 $\dfrac{n}{2 \ln n}$ 个，那么随机 $250$ 个数很有可能就压进去一个。我们选取所有找到的质数中的最大值即可。

Submission Link：[Here](https://codeforces.com/contest/1562/submission/241901623)

---

## 作者：IdnadRev (赞：0)

## 题意

有一个长度为 $n$ 值域连续的数组 $a$，你可以进行若干次询问，每次询问两个位置上的数的 $\text{lcm}$ 在 $n+5000$次 询问内猜出数列。

$3\leqslant n\leqslant 10^5$，数组的最小值不超过 $2\times 10^5$。

## 分析

当区间内没有素数时，计算可得 $n\leqslant 85$，考虑暴力求解：

我们求出所有询问的答案，那么 $n>3$ 时有：（原因是 $\gcd(x,x+1)=1$）

$$a_i=\gcd\{\text{lcm}(a_i,a_j)\}$$

$n=3$ 的时候特判一手，直接枚举答案即可。

当 $n>85$ 时区间内一定有素数。

$n+5000$ 这个操作次数提示我们需要询问出一个大于最大值除二的素数，用这个数确定其他位置的答案。

由于素数分布密度比较高，我们考虑随机 $200$ 个下标，那么这些下标没有素数的概率非常低，对于每个下标，我们随机 $25$ 个位置，将这个下标与这些位置的 $\text{lcm}$ 取 $\gcd$，将这些 $\gcd$ 取 $\max$。

这样能取到我们需要的素数的概率不低于：

$$(1-(1-\frac{1}{2\ln n})^{200})\prod_p(1-(\frac{n}{p})^{25})$$

肉眼可见正确率十分高，足以通过本题。

## 代码

看很多题解代码冗长无比，这种做法代码很小清新。
```
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define int long long
const int maxn=86,maxN=200005;
int T,n,flg;
int res[maxn][maxn],ans[maxN],c[maxN];
int query(int a,int b) {
	printf("? %lld %lld\n",a,b),fflush(stdout);
	int res;
	scanf("%lld",&res);
	return res;
}
int gcd(int a,int b) {
	return b==0? a:gcd(b,a%b);
}
int lcm(int a,int b) {
	return a/gcd(a,b)*b;
}
void check(int a,int b,int c) {
	if(flg==0&&lcm(a,b)==res[1][2]&&lcm(b,c)==res[2][3]&&lcm(a,c)==res[1][3])
		flg=1,printf("! %lld %lld %lld\n",a,b,c),fflush(stdout);
}
signed main() {
	srand(time(0));
	scanf("%lld",&T);
	c[1]=1;
	for(int i=1; i<=200000; i++)
		if(c[i]==0)
			for(int j=i+i; j<=200000; j+=i)
				c[j]=1;
	while(T--) {
		scanf("%lld",&n);
		if(n<=85) {
			for(int i=1; i<=n; i++)
				for(int j=i+1; j<=n; j++)
					res[i][j]=query(i,j),res[j][i]=res[i][j];
			if(n==3) {
				flg=0;
				for(int i=1; flg==0&&i<=200000; i++)
					check(i,i+1,i+2),check(i,i+2,i+1),check(i+1,i,i+2),check(i+1,i+2,i),check(i+2,i,i+1),check(i+2,i+1,i);
				continue;
			}
			printf("!");
			for(int i=1; i<=n; i++) {
				int g=0;
				for(int j=1; j<=n; j++)
					if(i!=j)
						g=gcd(g,res[i][j]);
				printf(" %lld",g);
			}
			puts(""),fflush(stdout);
		} else {
			int pos=0,val=0;
			for(int i=1; i<=200; i++) {
				int p=rand()%n+1,g=0;
				for(int j=1; j<=25; j++) {
					int q=rand()%n+1;
					while(p==q)
						q=rand()%n+1;
					g=gcd(g,query(p,q));
				}
				if(c[g]==0&&g>val)
					val=g,pos=p;
			}
			for(int i=1; i<=n; i++)
				ans[i]=i==pos? val:(query(i,pos)/val);
			printf("!");
			for(int i=1; i<=n; i++)
				printf(" %lld",ans[i]);
			puts(""),fflush(stdout);
		}
	}
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：0)

**Upd 2021-9-8** 修改了不严谨的表达。

此思路来自一位评论区小哥 [jeroenodb](https://codeforces.com/blog/entry/94278?#comment-833416)。

### 小范围暴力

多小呢？$n<86$。

因为 $\leqslant2e5$ 的数中相邻素数差最大为 $86$，也就是说小范围内不保证落有素数。

所以暴力枚举 $0<i<j\leqslant n$，皆求 $\operatorname{lcm}(a_i,a_j)$，即可得所有数的值。（注意 $n=3$ 时要特判）

$O(n^2\log n)$ 时间复杂度。

### 大范围随机

多大呢？$n\geqslant86$。

此时范围内保证落有素数，频率至少为 $\dfrac{n}{100}$。

显然，出现 $l\leqslant p\leqslant r \quad and \quad 2p > r \quad and \quad p\in prime$ 的频率至少为 $\dfrac{n}{200}$。

所以我们选 $\min(\dfrac{n}{2},5000)$ 个原序列的位置的 $pair$，进行询问。

找到所有回答中所有素因数最大的那个，设为 $p$，就假设它在原序列中存在，且就在那个位置上，且序列中不存在 $p$ 的其他倍数。（因为概率极高） 

那么由于 $\operatorname{lcm}(x,p)=x\times p \quad (p\in prime)$，所以可以通过 $n-1$ 次询问 $\operatorname{lcm}(i,p)\quad (1\leqslant i\leqslant n)$ 得到所有数值。

[非常不雅观的代码](https://codeforces.com/contest/1562/submission/128132975)

---

