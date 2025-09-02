# GCD Guess

## 题目描述

This is an interactive problem.

There is a positive integer $ 1 \le x \le 10^9 $ that you have to guess.

In one query you can choose two positive integers $ a \neq b $ . As an answer to this query you will get $ \gcd(x + a, x + b) $ , where $ \gcd(n, m) $ is the [greatest common divisor](<https://en.wikipedia.org/wiki/Greatest common divisor>) of the numbers $ n $ and $ m $ .

To guess one hidden number $ x $ you are allowed to make no more than $ 30 $ queries.

## 说明/提示

The first hidden number is $ 4 $ , that's why the answers for the queries are:

"? 1 2" — $ \gcd(4 + 1, 4 + 2) = \gcd(5, 6) = 1 $ .

"? 12 4" — $ \gcd(4 + 12, 4 + 4) = \gcd(16, 8) = 8 $ .

The second hidden number is $ 10^9 $ , that's why the answer for the query is:

"? 2000000000 1999999999" — $ \gcd(3 \cdot 10^9, 3 \cdot 10^9 - 1) = 1 $ .

These queries are made only for understanding the interaction and are not enough for finding the true $ x $ .

## 样例 #1

### 输入

```
2

1

8


1```

### 输出

```
? 1 2

? 12 4

! 4
? 2000000000 1999999999

! 1000000000```

# 题解

## 作者：听取MLE声一片 (赞：13)

简要题意：评测机给定一个正整数，不大于 $10^9$，你每次可以询问正整数 $a,b$，不大于 $2\times 10^9$，返回 $\gcd(x+a,x+b)$，你需要在不超过 30 步确定 x。

由于限制了 30 次，不难想到需要试出二进制下的每一位。从低位向高位询问，设当前答案为 ans，把要询问的 $a,b$ 都减去 ans，则能使 x 的后面位数全清零，方便处理。

假设我们现在处理到第 $i$ 位，假设 x 后面的位数全为 $0$,那么 $a,b$ 分别定为 $2^{i-1},2^i+2^{i-1}$，询问时减去 ans。如果返回的值是 $2^i$ 的倍数，则说明第 i 位是 1，ans 加上 $2^{i-1}$。这样就不会溢出。这就相当于在第 $i$ 位上同时加一个 1，就能测出这一位是否为 1。


代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int ask(int x,int y){
	printf("? %d %d\n",x,y);
	cout.flush();
	int z=read();
	return z;
}
int main()
{
	int T=read();
	while(T--){
		int ans=0;
		for(int i=1;i<=30;i++){
			int x=ask((1<<(i-1))-ans,(1<<i)+(1<<(i-1))-ans);
			if(x%(1<<(i))==0)
				ans=ans+(1<<(i-1));
		}
		printf("! %d\n",ans);
		cout.flush();
	}
	return 0;
}

```

---

## 作者：wrhaco (赞：11)

## 思路：

首先，我们需要找到一些正整数，使它们满足：

1.乘积在$10^9$到$2\times10^9$之间；

2.两两互质。

例如$ \{ 2,11,13,17,19,23,29,31 \}$ 就是一组满足条件的正整数。

设这些正整数的乘积为$X$，最大的正整数为$Y$，要猜的数为$n$.

然后，提出 $Y-1$ 次询问，第 $i$ 次询问中 $A=i,B=X+i$.

通过这些询问，我们可以知道 $n+1,n+2,…n+Y-1$分别是哪些正整数的倍数，从而可以推出 $n$ 对这些正整数取模的结果。

例如，我们通过询问得到了 $gcd(n+v,n+X+v)$ 是11的倍数，那么就有 $n \equiv -v \left(mod \; 11\right)$

$Y-1$次询问结束后，显然一定能得到关于每个正整数的同余方程。

利用中国剩余定理解同余方程，即可解出 $n$ 的值。

关于正整数，一种比较优秀的选法是：$\{ 16,9,7,11,13,17,19,23 \}$，可以做到22次询问出结果。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long NUM=1070845776;	//NUM是下面几个数的乘积 
const int P[10]={16,9,7,11,13,17,19,23};
int N;
long long M,A[11],m[11],t[11],Ans;
void exgcd(long long a,long long b,long long &x,long long &y){
	if(b==0){
		x=1;
		y=0;
	}else{
		exgcd(b,a%b,x,y);
		long long t=x;
		x=y;
		y=t-(a/b)*y;
	}
}
long long inv(long long a,long long p){
	a%=p;
	long long x,y;
	exgcd(a,p,x,y);
	return x>=0?x%p:x%p+p;
}
long long CRT(){	//中国剩余定理解同余方程 
	N=8,M=NUM;
	Ans=0;
	for(int i=0;i<N;i++){
		m[i]=M/P[i];
		t[i]=inv(m[i],P[i]);
		Ans=(((m[i]*t[i]%M)*A[i])%M+Ans)%M;
	}
	return Ans;
}

int T,n,cnt;
long long res;
void solve(){
	for(int i=0;i<8;i++){
		A[i]=0;		//A[i]初始化为0，后面询问没有赋值就说明n自己就是这个数的倍数 
	}
	for(int i=1;i<=22;i++){
		printf("? %d %lld\n",i,NUM+i);
		fflush(stdout);
		scanf("%lld",&res);
		for(int j=0;j<8;j++){
			if(res%P[j]==0){
				A[j]=(P[j]-(i%P[j]))%P[j];
			}
		}
	}
	printf("! %lld\n",CRT());
	return;
}
int main(){
	scanf("%d",&T);
	while(T--){
		solve();
		fflush(stdout);
	}
	return 0;
} 
```


---

## 作者：RedLycoris (赞：9)

前置知识：中国剩余定理

我们钦定 $a<b$，然后这个 $gcd(x+a,x+b)$ 根据辗转相减法就可以变为 $gcd(b-a,x+a)$

所以说，当 $gcd(x+a,x+b)$ 是 $b-a$ 的倍数的时候，要求 $x+a$ 是 $b-a$ 的倍数。

我们考虑如何充分利用这个性质。

构造一个数 $a=2\times 3\times 7 \times 11 \times 13 \times 17 \times 19 \times 23 \times 29$，和一个数组 $b={2,3,7,11,13,17,19,23,29}$，发现 $a$ 中是由好多素数构成的。

我们枚举 $i=0\dots28$，求 $gcd(x+i,x+a+i)$，记为 $r_i$。如果 $r_i$ 是某个 $b_j$ 的倍数，那么就可以得到 $x\mod b_j= b_j-i \mod b_j$。

为什么呢？

首先，$b$ 中的数两两互质，所以在 gcd 中互不影响。其次，$gcd(x+i,x+a+i)$ 是 $b_j$ 的倍数，那么就意味着 $x+i$ 是 $b_j$ 的倍数，所以 $x+i \mod b_j = 0$，移项就得到了上面那个式子。

最后发现这就是中国剩余定理的板子，直接套即可。

p.s. 这个 $a$ 正好处于 $10^9$ 和 $2\times 10^9$ 之间，所以我们选取这些数的积做为模数。


Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define reg register
int rem[29];
int pri[]={2,3,7,11,13,17,19,23,29};
ll n,a[16],m[16],Mi[16],mul=1,X;
void exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){x=1;y=0;return ;}
    exgcd(b,a%b,x,y);
    int z=x;x=y,y=z-y*(a/b);
}
inline void solve(){
	for(int i=1;i<=29;++i){
		cout<<"? "<<i<<' '<<1293938646+i<<endl;
		fflush(stdout);
		int x;cin>>x;fflush(stdin);
		for(int j=0;j<9;++j)if(x%pri[j]==0)rem[j]=pri[j]-(i%pri[j]);
	}
	n=9;mul=1;memset(m,0,sizeof(m));X=0;memset(Mi,0,sizeof(Mi));
    for(int t=1;t<=n;++t){
		m[t]=pri[t-1];
		mul*=m[t];
		a[t]=rem[t-1];
    }
    for(int t=1;t<=n;++t){
		Mi[t]=mul/m[t];
		ll x=0,y=0;
        exgcd(Mi[t],m[t],x,y);
        X+=a[t]*Mi[t]*(x<0?x+m[t]:x);
    }
    cout<<"! "<<X%mul<<'\n';
}
int main(){
//	ios_base::sync_with_stdio(false);
//	cin.tie(0),cout.tie(0);
	int T=1;
	cin>>T;
	for(;T--;)solve();
	return (0-0);
}
```

---

## 作者：jiangtaizhe001 (赞：2)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16126161.html)

Upd on 2022.6.29：更正了一处小错误。

### 题目大意
交互题，需要猜一个正整数 $x$（$x\le 10^9$），每次询问输出给出 $a,b$，你可以得到 $\gcd(x+a,x+b)$ 的值，询问此处不超过 $30$ 次。要求 $a,b\le 2\times 10^9$。

### 题目解析
显然 $\gcd(x+a,x+b)=\gcd(x+a,b-a)$。  
这样我们就可以猜出 $x$ 在二进制下的每一位。  

我们从低位到高位猜，假设现在猜的是从右往左第 $i$ 位，那么我们现在就已经知道了右边 $i-1$ 位，这些位的数值的和记作 $y$，令 $a=2^{i-1}-y$，$b=2^{i}+2^{i-1}-y$。假设返回的数是 $m$。 如果 $m=2^i$，也就是说，在第 $i$ 位加上了 $1$ 会产生进位，那么这一位就是 $1$，反之这一位就是 $0$。

代码：
```cpp
int x,tmp;
void work(){
	int i; x=0; for(i=1;i<=30;i++){
		cout<<"? "<<(1<<i-1)-x<<' '<<(1<<i-1)+(1<<i)-x<<endl; fflush(stdout);
		cin>>tmp; if(tmp==(1<<i)) x|=1<<(i-1);
		//cout<<x<<endl;
	} cout<<"! "<<x<<endl; fflush(stdout); return;
}
```

---

## 作者：LXcjh4998 (赞：1)

[Luogu 链接](https://www.luogu.com.cn/problem/CF1665D)  
[Codeforces 链接](https://codeforces.com/problemset/problem/1665/D)
# 题意
**这是一道 IO 交互题，请注意刷新缓冲区。**

---
> ### 题目描述
> 现在有一个正整数 $n$（$1\le n\le10^9$），你必须在 $30$ 次询问内将其猜出。
>
> 每次询问，你可以选择不同的正整数 $a$ 和 $b$，交互库将返回 $\gcd(n+a,n+b)$。
---
> ### 交互格式
> 多测，第一行读入一个整数 $T$（$1\le T\le1000$），代表有 $T$ 组数据。
>
> 每次询问的格式为 ```? a b```，返回值见**题目描述**。
>
> 当你确定答案时，请输出 ```! n```，**然后立即结束这组数据（进行下组数据或结束程序）。**
# 思路
注意到我们需要在 $30$ 次内猜出 $n$ 的值，可以猜测我们需要得到 $n$ 二进制下每一位的值。

为了方便计算，在判断第 $i$ 位（下标从右往左，从 $0$ 开始）的值时，先将第 $0$ 至 $i-1$ 位清空（$i=0$ 则不用清空）。

我们只需记录当前得到的 $ans$，把要询问的 $a$ 和 $b$ 都减去 $ans$，即可将第 $i$ 位以前的位清 $0$。

令 $n'=n-ans$，若 $2^{i+1}\mid\gcd(n'+2^i,n'+2^i+2^{i+1})$，则可以判断 $n'$ 的第 $i$ 位为 $1$。以下是对这一结论的简略证明：
> 首先有 $2^{i+1}\mid\gcd(n'+2^i,n'+2^i+2^{i+1})=\gcd(n'+2^i,2^{i+1})$，所以 $2^{i+1}\mid n'+2^i$。
>
> 若 $n'$ 第 $i$ 位为 $1$，则显然有 $2^{i+1}\mid n'+2^i$；若 $n'$ 第 $i$ 位为 $0$，则显然有 $2^{i+1}\nmid n'+2^i$。
>
> 所以，当且仅当 $n'$ 的第 $i$ 位为 $1$ 时，$2^{i+1}\mid\gcd(n'+2^i,n'+2^i+2^{i+1})$ 成立。

综上，在判断第 $i$ 位的值时，我们可以令 $a=2^i-ans,b=2^i+2^{i+1}-ans$，然后 ```? a b```，若返回值能被 $2^{i+1}$ 整除，则将 $ans$ 加上 $2^i$。

最后输出 ```! ans```。
# 程序
[AC 记录](https://codeforces.com/contest/1665/submission/309970382)
```cpp
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<iomanip>
#include<string>
#include<stack>
#include<random>
#include<utility>
#define re register
#define ll long long
#define ull unsigned long long
#define vl __int128
#define ld long double
#define LL 2e18
#define INT 1e9
#define INF 0x3f3f3f3f
#define MP make_pair
#define pb push_back
#define lb(x) (x&(-x))
#ifdef __linux__
#define gc getchar_unlocked
#define pc putchar_unlocked
#else
#define gc _getchar_nolock
#define pc _putchar_nolock
#endif
int T=1;
using namespace std;
pair<int*,int*> pair_int;pair<ll*,ll*> pair_ll;pair<ull*,ull*> pair_ull;pair<double*,double*> pair_double;pair<ld*,ld*> pair_ld;pair<char*,char*> pair_char;pair<bool*,bool*> pair_bool;
inline bool blank(const char x){return !(x^32)||!(x^10)||!(x^13)||!(x^9);}
template<typename Tp>inline void read(Tp &x){x=0;bool z=true;char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=(x<<1)+(x<<3)+(a^48);x=(z?x:~x+1);}
inline void read(double &x){x=0.0;bool z=true;double y=0.1;char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=x*10+(a^48);if(a!='.')return x=z?x:-x,void();for(a=gc();isdigit(a);a=gc(),y/=10)x+=y*(a^48);x=(z?x:-x);}
inline void read(ld &x){x=0.0;bool z=true;ld y=0.1;char a=gc();for(;!isdigit(a);a=gc())if(a=='-')z=false;for(;isdigit(a);a=gc())x=x*10+(a^48);if(a!='.')return x=z?x:-x,void();for(a=gc();isdigit(a);a=gc(),y/=10)x+=y*(a^48);x=(z?x:-x);}
inline void read(char &x){for(x=gc();blank(x)&&(x^-1);x=gc());}
inline void read(char *x){char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())*x++=a;*x=0;}
inline void read(string &x){x="";char a=gc();for(;blank(a)&&(a^-1);a=gc());for(;!blank(a)&&(a^-1);a=gc())x+=a;}
template<typename T>inline void read(pair<T*,T*> p){T *begin,*end,*i;begin=p.first,end=p.second;if(begin<end)for(i=begin;i<end;++i)read(*i);else for(i=begin-1;i>=end;--i)read(*i);}
template<typename T,typename ...Tp>inline void read(T &x,Tp &...y){read(x),read(y...);}
template<typename Tp>inline void write(Tp x){if(!x)return pc(48),void();if(x<0)pc('-'),x=~x+1;int len=0;char tmp[64];for(;x;x/=10)tmp[++len]=x%10+48;while(len)pc(tmp[len--]);}
inline void write(const double x){int a=6;double b=x,c=b;if(b<0)pc('-'),b=-b,c=-c;double y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);pc('.');for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}
inline void write(const ld x){int a=6;ld b=x,c=b;if(b<0)pc('-'),b=-b,c=-c;ld y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);pc('.');for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}
inline void write(const pair<int,double>x){int a=x.first;if(a<7){double b=x.second,c=b;if(b<0)pc('-'),b=-b,c=-c;double y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);a&&(pc('.'));for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}else printf("%.*lf",a,x.second);}
inline void write(const pair<int,ld>x){int a=x.first;if(a<7){ld b=x.second,c=b;if(b<0)pc('-'),b=-b,c=-c;ld y=5*powl(10,-a-1);b+=y,c+=y;int len=0;char tmp[64];if(b<1)pc(48);else for(;b>=1;b/=10)tmp[++len]=floor(b)-floor(b/10)*10+48;while(len)pc(tmp[len--]);a&&(pc('.'));for(c*=10;a;a--,c*=10)pc(floor(c)-floor(c/10)*10+48);}else printf("%.*Lf",a,x.second);}
inline void write(const char x){pc(x);}
inline void write(const bool x){pc(x?49:48);}
inline void write(char *x){fputs(x,stdout);}
inline void write(const char *x){fputs(x,stdout);}
inline void write(const string &x){fputs(x.c_str(),stdout);}
template<typename T>inline void write(pair<T*,T*> p){T *begin,*end,*i;begin=p.first,end=p.second;for(i=begin;i<end;++i)write(*i),write(' ');}
template<typename T>inline void write(pair<pair<T*,T*>,char> p){T *begin,*end,*i;begin=p.first.first,end=p.first.second;char c=p.second;for(i=begin;i<end;++i)write(*i),write(c);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x),write(y...);}
template<typename T>inline void init(T *begin,T *end,const T& val=T()){T* i;for(i=begin;i<end;++i)*i=val;}
template<typename T>inline T max(T *begin,T *end){T *ans,*i;for(i=begin;i<end;++i)if(i==begin||*ans<*i)ans=i;return *ans;}
template<typename T>inline T min(T *begin,T *end){T *ans,*i;for(i=begin;i<end;++i)if(i==begin||*i<*ans)ans=i;return *ans;}
template<typename T>inline T calc_sum(T *begin,T *end,const T& val=T()){T ans=val,*i;for(i=begin;i<end;++i)ans+=*i;return ans;}
template<typename T>inline bool is_equal(T *begin,T *end,const T& val=T()){T *i;for(i=begin;i<end;++i)if(*i!=val)return false;return true;}
template<typename T>inline T qp(T x,T y){T ans=1;while(y){if(y&1)ans=ans*x;x=x*x;y>>=1;}return ans;}
template<typename T>inline T qp(T x,T y,T z){T ans=1;while(y){if(y&1)ans=ans*x%z;x=x*x%z;y>>=1;}return ans;}
template<typename T>inline T abs(T x){return x>=0?x:-x;}

ll mod=0;
const int MAXN=1e5;
const int N=MAXN+10;
//#define DEBUG
#define more_text

int g,ans;

void ask(int a,int b,int &x){
	printf("? %d %d\n",a,b);fflush(stdout);
	scanf("%d",&x);
}
int answer(int a){
	printf("! %d\n",a);fflush(stdout);
}
void SOLVE(int _){
	ans=0;
	for(int i=0;i<30;++i){
		ask((1<<i)-ans,(3<<i)-ans,g);
		if(g%(2<<i)==0)ans+=1<<i;
	}
	answer(ans);
}
/*
Input:

Output:

Outline:

*/
int main(){
	#ifdef DEBUG
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	#ifdef more_text
	read(T);
	#endif 
	for(int i=1;i<=T;++i)SOLVE(i);
	#ifdef DEBUG
	fclose(stdin);fclose(stdout);
	#endif
	return 0;
}
```

---

## 作者：王熙文 (赞：1)

## 前言

我在 10.9 的时候做了这题，但是现在又不会了，想了半天才明白当时做法的正确性，发现与所有题解都不一样，于是来记录一下。

其实当时应该没有想清楚，只是碰巧过的。

## 思路

注：以下 $x$ 的第 $i$ 位指二进制下从右往左的第 $i$（$i\ge 1$）位。

看到 $30$ 次，可以想到用二进制依次确定这个数的每一位。

从小到大确定 $x$ 的每一位。设当前枚举到了 $i$（$0 \le i <30$），则已知 $x$ 的二进制下后 $i$ 位，设其为 $now$，此时要确定第 $i+1$ 位。

接下来我们要查询的是：$\gcd(x+(2^i-now),x+(2^i-now)+2^{30})$。$x+(2^i-now)$ 为 $x$ 去掉最后 $i$ 位，第 $i+1$ 位加了个 $1$ 时的数。为什么要加 $2^{30}$？因为左右两边不可能同时存在非 $2$ 的幂的因数。这样就限制 $\gcd$ 只能为 $2$ 的幂了。所以当 $\gcd\ge 2^{i+1}$ 时，表示 $x$ 的第 $i+1$ 位加了个 $1$ 后变成了 $0$（只有变成 $0$ 才可能让 $\gcd$ 比 $2^i$ 更大），即 $x$ 的第 $i+1$ 位为 $1$；否则，说明 $x$ 的第 $i+1$ 位加了个 $1$ 后变成了 $1$（这里变成 $1$，$\gcd=2^i$），即 $x$ 的第 $i+1$ 位为 $0$。这样就可以逐位确定 $x$ 了。

分析值域：最大的情况即为 $i=29,now=0$ 时了，此时 $b=2^{29}+2^{30} \le 2 \times 10^9$，所以满足要求。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
	int t; cin>>t; while(t--)
	{
		int now=0;
		for(int i=0; i<30; ++i)
		{
			cout<<"? "<<(1ll<<i)-now<<' '<<(1ll<<i)-now+(1ll<<30)<<endl;
			int x; cin>>x;
			if(x>=(1ll<<i+1)) now+=(1ll<<i);
		}
		cout<<"! "<<now<<endl;
	}
	return 0;
}
```

---

## 作者：cancan123456 (赞：1)

[翻译](https://www.luogu.com.cn/paste/tsxthg2u)

首先看到 $30$ 次询问确定一个 $10^9$ 的数，我们考虑依次确定每一位。

为了在确定高位的时候消除对低位的影响，我们从低位向高位依次确定。

现在我们考虑如何确定最低位。

考虑 $\gcd(x+2,x+4)$，容易发现，$+2$ 和 $+4$ 对 $x$ 的最低位都没有影响，所以如果 $\gcd(x+2,x+4)$ 的最低位是 $0$，那么就意味着 $x$ 的最低位是 $0$。

然后我们考虑倒数第 $i$ 位，设我们已经求出了 $x$ 的低 $i-1$ 位组成的数 $y$，那么我们同样考虑 $\gcd\left(x-y+2^{i+1},x-y+2^{i+2}\right)$，如果该数的第 $i$ 位是 $1$，那么就说明 $x$ 的第 $i$ 位是 $1$，反之亦然。

然后我们就可以写出这样的代码：

```cpp
void solve() {
	ll y = 0;
	for (ll i = 0; i < 30; i++) {
		ask((1ll << (i + 1)) - y, (1ll << (i + 2)) - y);
		y |= (((get() >> i) & 1) << i);
	}
	printf("! %lld\n", y);
	fflush(stdout);
}
```

然后我们发现，最后一次询问有可能是：`? 1073741823 2147483647`（这是 $x=1$ 的情况），就成功地炸掉了 $2\times10^9$

但是我们发现 $2\times10^9$ 可以承受住 $2^{29}+2^{28}$ 这个数，因此我们考虑 $\gcd\left(x-y+2^{29},x-y+2^{29}+2^{30}\right)$，通过分类讨论我们可以发现这个数的效果和 $\gcd\left(x-y+2^{30}+2^{31}\right)$ 是一样的，因此我们可以这样写：

```cpp
void solve() {
	ll y = 0;
	for (ll i = 0; i < 29; i++) {
		ask((1ll << (i + 1)) - y, (1ll << (i + 2)) - y);
		y |= (((get() >> i) & 1) << i);
	}
	ask((1ll << 29) - y, (1ll << 30) + (1ll << 29) - y);
	if (get() == 1 << 30) {
		y |= (1ll << 29);
	}
	printf("! %lld\n", y);
	fflush(stdout);
}
```

这样就做完了。

---

## 作者：SUNCHAOYI (赞：0)

由数据范围不难想到按位考虑，所以我们尽量把每次询问凑成 $2$ 的幂次相关的数。

在二进制条件下，设最低位为第 $0$ 位。目前要猜测第 $i$ 位的值，设 $t$ 表示前 $i - 1$ 位所贡献的值。令 $a < b$，则有（加粗表示第 $i$ 位）：

$$
\begin{cases}
t + a \text{\ changes to\ } \ \bm 10\cdots 0\\
t + b \text{\ changes to\ } 1\bm 10\cdots 0\
\end{cases}
$$

由公式 $\gcd (t + a,t + b) = \gcd (t + a,b - a)$ 可知（加粗表示第 $i$ 位）：

$$
\begin{cases}
t + a \text{\ changes to\ } \ \bm 10\cdots 0\\
b - a \text{\ changes to\ } 1\bm 000\cdots 0\
\end{cases}
$$

此时 $\gcd (t + a,b - a) = 2^i$。当实际 $x$ 的第 $i$ 位为 $1$ 时，会产生 $2$ 次进位，使得 $\gcd (t' + a,b - a) = 2^{i + 1}$。因此可以得到以下代码：

```cpp
for (int i = 0;i < 30;++i)//猜测第 i 位 
{
    int ans = query ((1 << i) - x,(1 << i) + (1 << (i + 1)) - x);
    if (ans == 1 << (i + 1)) x |= 1 << i;
}
```

---

## 作者：hh弟中弟 (赞：0)

首先能想到先判奇偶，发现只要给一个 $(1,3)$ 观察 $\gcd$ 是否为 $1$ 就行了，为啥能这么干，因为我们知道这一位后面没有别的数，所以这一位上操作不会有更低的位来影响，现在考虑依次确定 $x$ 的每一个二进制位，每次考虑将后面的影响消除，设已经得到的答案为 $ans$，对于从右往左第 $k$ 位，问 $(2^k-ans,2^{k+1}+2^k-ans)$，这样首先会给这一位加上 $1$，如果这一位本来是 $0$，一定会返回 $2^k$，否则返回更大的数。

---

## 作者：DaiRuiChen007 (赞：0)

# CF1665D 题解



## 思路分析

注意到 $\gcd(x+a,x+b)=\gcd(x+a,|a-b|)$，因此有一个朴素的想法，由于 $2\times3\times5\times7\times11\times13\times17\times19\times23\times29\ge 10^9$，所以求出 $x\bmod 2\sim x\bmod29$ 的值用 CRT 求解即可。

不过我们每次询问一个 $\gcd(x+r,p)$ 只能判断 $x\equiv -r\pmod p$ 是否成立，因此在最坏情况下我们需要依次检查在模每个质数的情况下的每个余数，显然会超过 $30$ 次的限制。

因此我们考虑如何压缩状态，比如对于 $p$ 和 $q$，我们询问 $\gcd(x+r,p\times q)$，可以同时得到 $x\equiv -r\pmod p$ 和 $x\equiv -r\pmod q$ 是否成立，那么如果我们把多个质数乘在一起，在确定最大的质数的余数时我们能够同时计算出较小的一些质数的余数。

所以直接将 $10$ 个质数乘在一起，然后枚举 $29$ 次，每次用 CRT 算出应该询问多少，使得对于每个模数每次都能排除一种可能的余数，这样的操作次数为 $29$ 次。

假设我们选用的所有质数乘积为 $P$，那么可能出现的最大的一对询问为 $(P,2\times P)$，这就需要我们保证 $P\le 10^9$，不过显然 $2$ 乘到 $29$ 超过了这个限制，因此我们需要在这个模数集合中去掉一些数使得 $P\le 10^9$。

但是如果 $P\le 10^9$，即使我们求出了合法的 $r$ 我们有可能将无法确定哪个 $r+kP$ 是答案。

显然，存在一种方法使得 $5\times 10^8 \le P\le 10^9$，那么这个时候 $k\in\{0,1\}$。

注意到我们只询问了 $29$ 次，而剩下的一次可以随意取这些模数这之外的一个质数 $t$，询问 $\gcd(x+(-r\bmod t),t)$，此时如果 $\gcd$ 为 $t$ 说明答案为 $r$，否则答案为 $r+P$。

给一组合法的构造：$P=3\times 7\times 11\times 13\times 17\times19\times23\times29\approx6.5\times 10^8,t=5$。

这样我们就可以在恰好 $30$ 次操作之后求出答案。

时间复杂度 $\Theta(1)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p[8]={3,7,11,13,17,19,23,29},MOD=646969323,LIM=1e9;
int unit[8];
inline int read(int a,int b) {
	cout<<"? "<<a<<" "<<b<<endl;
	int ret; cin>>ret; return ret;
}
inline int crt(const vector <int> &r) {
	int ret=0;
	for(int i=0;i<8;++i) ret=(ret+unit[i]*r[i])%MOD;
	return ret;
}
inline void solve() {
	vector <int> r[8];
	for(int i=0;i<8;++i) for(int j=0;j<p[i];++j) r[i].push_back(j);
	for(int t=0;t<29;++t) {
		vector <int> tmp(8);
		for(int i=0;i<8;++i) tmp[i]=(p[i]-r[i].back())%p[i];
		int q=crt(tmp);
		if(!q) q+=MOD;
		int x=read(q,q+MOD);
		for(int i=0;i<8;++i) if(x%p[i]!=0) r[i].pop_back();	
	}
	vector <int> ans(8);
	for(int i=0;i<8;++i) ans[i]=r[i].back();
	int d=crt(ans);
	int q=read((5-d%5)%5+5,(5-d%5)%5+10);
	if(q==1) cout<<"! "<<d+MOD<<endl;
	else cout<<"! "<<d<<endl;
}
signed main() {
	for(int i=0;i<8;++i) {
		int m=MOD/p[i];
		for(int r=0;r<p[i];++r) {
			if(m*r%p[i]==1) {
				unit[i]=m*r; //中国剩余定理的单位元
				break;
			}
		}
	}
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$
---
### 解题思路：

从最大猜测数量来看 $2^{30}=1073741824$ 恰好比 $10^9$ 大一点，可以往二的指数上想。

考虑一个引理，$\gcd(x,x+a)\le a$，且仅当 $a|x$ 的时候取等。引理的证明直接用辗转相除推一步即可。

结合以上两条，考虑如何在已知一个二进制位的后面所有位的情况下用题目给出的询问求出当前二进制位。不妨将后面的所有位上补至全为 $0$，询问补上后的数 $x'$ 和 $x'+2^{cur+1}$，式子中的 $cur$ 表示当前的二进制位数。

如果得到的答案是 $2^{cur+1}$，可以断定，当前位置原来一定是 $1$，否则一定是 $0$。这个结论可以结合之前的引理得到。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int T,x,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		ans=0;
		for(int i=0;i<30;i++){
			printf("? %d %d\n",(1<<i)-ans,(1<<i)-ans+(1<<(i+1)));
			fflush(stdout);
			scanf("%d",&x);
			if(x==(1<<(i+1)))ans+=(1<<i);
		}
		printf("! %d\n",ans);
	}
	return 0;
}
```


---

## 作者：Henry_C (赞：0)

# 题目大意
$\qquad$需要猜出 $t$($t \leq 10^3$) 个数的值，每个数 $x ≤ 10^9$ 。每个数最多可以询问 $30$ 次，每次询问的格式为 $?\ a\ b$ ，系统返回 $\gcd(x+a, x+b)$ 的值，猜到 $x$ 的值后，输出 $! x$ 。每次询问的数 $a,b$ 为正整数。
# 解题思路
$\qquad$看到30次询问，且 $x ≤ 10^9 $，容易想到求二进制数的每 $1$ bit 。根据 $\gcd$ 的性质（或者熟悉辗转相除法），$\gcd(x+a,x+b)=\gcd(x+a,\lvert b-a \rvert)$ （因为能整除 $x+a,x+b$ 的数，必然也能整除 ${\lvert x+a-(x+b)\rvert}$ )。

$\qquad$剩下的工作就是构造一个方法，每次求出 $x$ 中的每 $1$ bit 。从 $x$ 的二进制第 $0$ 位开始，若
$$ \gcd{(x,2)} = \begin{cases}
1 ,& x[0]=1\\
0 ,& x[0]=0
\end{cases}$$
其中 $x[i]$ 表示取二进制数 $x$ 的第 $i$ 位(最右侧是最低位——第 $0$ 位)。令 $y$ 表示 $x$ 的 0~$i-2$ 位二进制数构成的整数， $x-y$ 代表的二进制数 $0$~$i-2$ 位必然为 $0$ ，则
$$ \gcd{(x-y,2^i)} = \begin{cases}
2^{i-1} ,& x[i-1]=1\\
2^{i} ,& x[i-1]=0
\end{cases}$$
$\qquad$此时询问的数 $a=-y,b-a=2^i$ ，因此 $a=-y,b=2^i-y$ 。此外，要求 $a,b$ 为正整数，因为 $y≤ 2^{i-1}-1$ , 可以令 $a=2^{i-1}-y,b=2^i+2^{i-1}-y$ ，此时
$$ \gcd{(x+2^{i-1}-y,2^i)} = \begin{cases}
2^{i-1} ,& x[i-1]=0\\
2^{i} ,& x[i-1]=1 (\text{this value changed from above})
\end{cases}$$
**代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,y;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    for(int p=1; p<=t; p++){
        y = 0;
        for(int i=1; i<=30; i++){
            int a = (1<<(i-1))-y, b=(1<<i)+(1<<(i-1))-y;
            cout <<"?"<<" "<<a<<" "<<b<<" "<<endl;
            cout.flush();
            int v,k;
            cin >> v;
            if(v==(1<<i)) k=1;
            else k=0;
            y |= k<<(i-1);
        }
        cout<<"!"<<" "<<y<<endl;
        cout.flush();
    }
    return 0;
}
```


---

## 作者：只鹅烧烤二度 (赞：0)

题意：需要确定一个整数 $x$ ，可以询问若干次，每次询问给出 $a,b$ ，将会返回 $gcd(x+a,x+b)$ 的值，在 $30$ 次以内确定这个整数。

首先设 $a<b$ 有 $gcd(x+a,x+b)=gcd(x+a,b-a)$ 。

再考虑 $gcd(x+a,b-a)$ 的实质，相当于确定 $b-a$ 的因子种类中 $x+a$ 含有哪几种及其数量。如果固定住 $a$ 则这个问题较为棘手，因此考虑固定 $b-a$ 。

首先 $x+1,x+2...x+(b-a)$ 这 $b-a$ 个数当中必定有 $b-a$ 的倍数，基于此我们对于这 $b-a$ 个查询可以得到一个 $k$ 满足 $x+k$ 为 $b-a$ 的倍数，那么便相当于得到 $x$ 模 $b-a$ 的余数。

因此可以先给出一个较劣的做法，即对于 $b-a$ 为 $2$ 到 $29$ 的质数全部求出为多少的余数，最后用中国剩余定理合并得出答案。

然而注意到其实很多询问都是不必要的，因为我们可以直接将 $b-a$ 设定为质数的乘积，就可以在一次询问中得到多组解。

然而还有一个问题就是 $2$ 到 $29$ 的质数乘积是大于 $2e9$ 的由此我们舍弃若干个质数，取 $2,3,7,11,13,17,19,23,29$ 这些质数，满足乘积大于 $1e9$ 且小于 $2e9$ 就可以在 $30$ 次之内得出答案。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[15]={0,2,3,7,11,13,17,19,23,29},num[15];int T;
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0) {x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	ll t=x;x=y;y=t-a/b*y;
}
int main()
{
	scanf("%d",&T);
	ll b=1293938646;
	while(T--)
	{
		for(int i=1;i<=30;i++)
		{
			printf("? %lld %lld\n",i,b+i);
			fflush(stdout);ll x;
			scanf("%lld",&x);
			for(int k=1;k<=9;k++)
				if(x%a[k]==0)
					num[k]=((a[k]-i)%a[k]+a[k])%a[k];
		}
		ll ans=0;
		for(int i=1;i<=9;i++)
		{
			ll q=b/a[i],x,y;
			exgcd(q,a[i],x,y);
			ans+=num[i]*q*(x<0?x+a[i]:x);
		}
		printf("! %lld\n",ans%b);
	}
}

---

## 作者：I_am_Accepted (赞：0)

### Preface

为啥要 CRT 啊，二进制香啊。

### Analysis

由于 $a\ne b$，我们规定 $a<b$。

显然 $\gcd(x+a,x+b)=\gcd(b-a,x+a)$。

这样，假设我们知道了 $x\ \bmod 2^k=r$，我们询问 $a=2^k-r,b=2^{k+1}-r$ 就得到

$$\gcd(2^k,x-r+2^k)=(x-r)\ \text{AND}\ 2^k$$

（$\text{AND}$ 表示按位与）

即得到了 $x$ 二进制下的第 $k$ 位（从 $0$ 标号），进一步得到 $x\ \bmod 2^{k+1}$，递推做即可。

这样正好 $30$ 次询问，但是最后一次询问 $b$ 最大达到 $2^{31}>2\cdot10^9$。

若当前值 $r$ 加上 $2^{29}$ 大于 $10^9$，则这一位必然是 $0$，判掉。

若当前 $r=0$，则这一位必然是 $1$，判掉。（因为题目保证 $x>0$）

询问 $a=r+2^{29},b=2(r+2^{29})$，得到

$$\gcd(r+2^{29},x+r+2^{29})=\gcd(r+2^{29},x)$$

即可判断 $x$ 是否含有 $2^{29}$ 这一位。

而且此时 $b=2(r+2^{29})\le 2\cdot10^9$，满足。

### Code

[Link](https://codeforces.com/contest/1665/submission/153106978)

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N -1

const int inf=1e9;
inline int que(int x,int y){
	cout<<"? "<<x<<" "<<y<<endl;
	cout.flush();
	int res;
	cin>>res;
	return res;
}
void work(){
	int ans=0,res,x;
	For(i,0,28){
		x=(1ll<<(i+1))-ans;
		res=que(x,x+(1ll<<(i+1)));
		if(res==(1ll<<i)) ans+=(1ll<<i);
	}
	if(ans+(1ll<<29)<=inf){
		x=ans+(1ll<<29);
		if(!ans) ans=(1ll<<29);
		else if(que(x,x*2)==x){
			ans+=(1ll<<29);
		}
	}
	cout<<"! "<<ans<<endl;
	cout.flush();
}
signed main(){IOS;
	int T;cin>>T;
	while(T--)work();
return 0;}
```

---

## 作者：y0y68 (赞：0)

看到这个限制提问次数，显然要在 $\log n$ 次以内进行查询。

也就是说对于所有共 $30$ 个二进制位，我们要分别验证这位是 $1$ 还是 $0$。

然后构造提问方案就可以了。

下面第 $i$ 位表示代表 $2^i$ 的位。

假设所求数前 $i(0 \le i \le 29)$ 位的数值为 $ans$，那么我们可以询问 $2^i-ans,2^i-ans+2^{i+1}$，如果回答是 $2^{i+1}$，那么第 $i$ 位是 $1$。

理解一下就是把 $ans$ 的前 $i-1$ 位全部补成 $0$，如果第 $i$ 是 $1$，那么补齐后第 $i$ 位是 $0$，即变为 $2^{i+1}$ 的倍数，所以得到的回答一定是 $2^{i+1}$。

```
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	for(cin>>T;T;T--){
		int ans=0;
		for(int i=0;i<30;i++){
			printf("? %d %d\n",(1<<i)-ans,(1<<i)-ans+(1<<i+1));
			fflush(stdout);
			int x;
			scanf("%d",&x);
			if(x==(1<<i+1))ans|=(1<<i);
		}
		printf("! %d\n",ans);
		fflush(stdout);
	}
	return 0;
}
```

---

