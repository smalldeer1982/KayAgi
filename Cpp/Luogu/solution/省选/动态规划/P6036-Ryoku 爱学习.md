# Ryoku 爱学习

## 题目背景

Ryoku 继承了 Riri 在学习方面的天赋，所以她非常热爱学习。但是，不管再怎么热爱学习，Ryoku 也会疲倦的。

## 题目描述

Ryoku 在第 $i$ 时刻会了解到有一个新知识 $i$，这个新知识的实际价值为 $w_i$，由于 Ryoku 爱学习，所以她不会选择不学习知识，但她只有 $p_i$ 的概率能成功掌握这个知识。

然而如果 Ryoku 同时掌握了太多知识，由于 Ryoku 内心的疲倦等因素，Ryoku 感受到的对知识的喜爱程度会改变，我们用一个数值 $R$ 来描述**喜爱程度**的大小。具体而言，设 $R=f(l,r)$ 代表 Ryoku **连续掌握**时刻 $l$ 至时刻 $r$ 的知识时对这些知识的喜爱程度的总和，有参数 $a, b$（$0 < a, b<1$），则有：

$$ f(l,r)=a^{b(r-l)}  \sum_{i=l}^r w_i$$

Ryoku 想要知道她期望能**掌握的每一段连续时刻的知识**的喜爱程度之和是多少（需要注意的是，这里所说的连续时刻的知识不能被一段更长的所包含）。你能帮帮她吗？


## 说明/提示

**【样例 1 说明】**

掌握知识 $1$、知识 $2$、知识 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 2}(2+3+3)=4$。

掌握知识 $1$、知识 $2$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 1}(2+3)=\dfrac {5\sqrt2}2\approx 3.536$。

掌握知识 $1$、知识 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 2 +\left(\dfrac 12\right)^{\frac12\times 0}\times 3  = 5$。

掌握知识 $2$、知识 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 1}(3+3)=3\sqrt 2\approx 4.243$。

只掌握知识 $1$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 2  = 2$。

只掌握知识 $2$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 3  = 3$。

只掌握宝物 $3$ 时，每一段连续掌握知识的喜爱程度之和为 $\left(\dfrac 12\right)^{\frac12\times 0}\times 3  = 3$。

什么都不掌握时，每一段连续掌握知识的喜爱程度之和为 $0$。

以上 $8$ 种情况出现的概率均为 $\dfrac 18$，所以答案约为：

$$(4+3.536+5+4.243+2+3+3+0)\times \dfrac 18\approx3.0973$$

---

**【数据规模与约定】**

对于 $20\%$ 的数据，$n \le 18$。  
对于另外 $15\%$ 的数据，$w_i = 1$。  
对于 $55\%$ 的数据，$n \le 10^3$。  
对于另外 $15\%$ 的数据，$w_i = 1$。  
对于另外 $15\%$ 的数据，$b_i \le 0.2$。  

此外，对于 $100\%$ 的数据，$0<n\le10^5$，$0<a,b,p_i<1$，$0<w_i\le10^3$。保证输入数据的精度不超过 $10^{-2}$。

**本题使用 Special Judge，如果某个测试点中你的答案与标准答案相差小于等于 $10^{-3}$，你就可以通过该测试点。**


## 样例 #1

### 输入

```
3 0.5 0.5
2 3 3
0.5 0.5 0.5
```

### 输出

```
3.097```

## 样例 #2

### 输入

```
6 0.8 0.2
1 1 4 5 1 4
0.9 0.6 0.7 0.7 0.6 0.8
```

### 输出

```
10.521```

# 题解

## 作者：hhoppitree (赞：5)

### 题意简述：  

求一个期望，经过转化，发现，也就是求：  

$$\sum_{1\le l\le r\le n}a^{r-l}(1-p_{l-1})(1-p_{r+1})\prod\limits_{i=l}^{r}p_i\sum\limits_{i=l}^{r}w_i$$  

### 题目解法：  

首先，本题解并不是一篇普通的题解，这是一篇 **卡常题解**。  

做法推荐看 [大佬 $\rm z7z-Eta$ 的](https://www.luogu.com.cn/blog/z7z-Eta/solution-p6036)，本文也是采用 TA 这种做法。  

算是对这篇题解的补充吧。

我们发现，在这位大神的题解里，TA 开了许多数组，实际上只要开 $w$ 这一个数组就行了，如果改一改输入格式甚至空间复杂度能做到 $\mathcal{O}(1)$ 的（$w$ 只是个存数据的工具数组）~~正解：用修改输入文件格式让输入文件成为工具人~~。  

具体点，在 TA 的题解中，递推式要维护数组 $t$ 和 $f$，但这两个数组递推维护一下就行了。  

然后还要用到 $p_{i-1},p_{i},p_{i+1}$，滚动数组一下就行了，具体见代码。  

然后就最优解了（截止本文写作日期 $[2021/1/8]$）（包括空间吧）。  

然后就没有然后了。  

还是看代码吧。  

哦，如果您要问快的原因，**过多的数组调用需要耗费时间**。  

顺便说些小细节：**不要用 $\rm cin$，读入 $w_i$ 时不要手滑用 $\rm \%lf$（我开始就是这样所以速度只有 $\rm rank\;2$，后来看了 $\rm rank\;1$ 的代码才发现，这说明 $\rm \%lf$ 比少开数组重要）** 

### 正确代码：  

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int res=0;
	bool zf=0;
	char c;
	while(((c=getchar())<'0'||c>'9')&&c!='-');
	if(c=='-')zf=1;
	else res=c-'0';
	while((c=getchar())>='0'&&c<='9')res=(res<<3)+(res<<1)+c-'0';
	if(zf)return -res;
	return res;
}
int w[100005];
signed main(){
	int n=read();
	double a,b;
	scanf("%lf%lf",&a,&b);
	a=pow(a,b);
	double ans=0,t=0,f=0,p1=0.0,p2,p3;
	for(register int i=1;i<=n;++i){
		scanf("%d",&w[i]);
	}
	scanf("%lf",&p2);
	for(register int i=1;i<=n;++i){
		if(i!=n)scanf("%lf",&p3);else p3=0;
		t=a*p2*t+p2*(1-p1);
		f=a*p2*f+t*w[i];
		ans+=(1-p3)*f;
		p1=p2;p2=p3;
	}
	printf("%lf\n",ans);
	return 0;
}
```

最后，还是那句话：  

如果您没有看懂这篇题解，可以在评论区问我，我将会回答您的问题并且修改这篇题解，使它变得更加通俗易懂，服务更多的 $\text{OIer}$。  
如果您看懂了这篇题解，可以点个赞，使这篇题解的排名上升，服务更多的 $\text{OIer}$。  

---

## 作者：WYXkk (赞：5)

先膜拜出题人的神奇的多项式近似。这里说说我的奇怪的期望 $dp$ 做法。

给这个 $a,b$ 有啥用吗，直接给 $t=a^b$ 不好吗。$a^{b(r-l)}=(a^b)^{r-l}=t^{r-l}$，单独的 $a,b$ 没有作用。

首先肯定是设 $dp_i$ 为前 $i$ 个知识点的答案。

那么 $dp_{i}=(1-p_i)dp_{i-1}+\cdots$ 我们发现写不下去了。

所以设 $end_i$ 为前 $i$ 个知识点中最后一段产生的贡献（如果最后一段包含 $i$），

那么我们就可以得到 $dp_i=(1-p_i)dp_{i-1}+p_i(dp_{i-1}-end_{i-1})+end_i$。

接下来考虑 $end_i$ 如何递推。

$$\begin{aligned}end_i&=p_i(1-p_{i-1})w_it^0\\&+p_ip_{i-1}(1-p_{i-2})(w_{i-1}+w_i)t^1\\&+p_ip_{i-1}p_{i-2}(1-p_{i-3})(w_{i-2}+w_{i-1}+w_i)t^2\\&+\cdots\end{aligned}$$

注意到这里有一段与 $end_{i-1}$ 想等的部分，所以可以拿出来：

$$\begin{aligned}end_i&=p_iend_{i-1}+w_ip_i\times\\&(1-p_{i-1})+p_{i-1}(1-p_{i-2})t+p_{i-1}p_{i-2}(1-p_{i-3})t^2+\cdots\end{aligned}$$

这个时候，如果我们设 $P_i=(1-p_{i-1})+p_{i-1}(1-p_{i-2})t+p_{i-1}p_{i-2}(1-p_{i-3})t^2+\cdots$，那么

$$end_i=p_i(end_{i-1}+w_iP_i)$$

考虑 $P_i$ 如何递推。

很显然地我们有 $P_i=1-p_{i-1}+p_{i-1}P_{i-1}t$。

于是这么递推一下就 $O(n)$ 搞定了。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

typedef long double ld;
const int N=100005;
ld dp[N],end[N];
ld a,b,p[N],t,P[N];
int n,w[N];
int main()
{
	scanf("%d%Lf%Lf",&n,&a,&b);t=pow(a,b);
	F(i,1,n) scanf("%d",w+i);
	F(i,1,n) scanf("%Lf",p+i);
	dp[0]=end[0]=p[0]=0;
	F(i,1,n)
	{
		P[i]=t*p[i-1]*P[i-1]+1-p[i-1];
		end[i]=p[i]*(t*end[i-1]+P[i]*w[i]);
		dp[i]=(1-p[i])*dp[i-1]+p[i]*(dp[i-1]-end[i-1])+end[i];
	}
	printf("%.2Lf",dp[n]);
	return 0;
}
```



---

## 作者：FZzzz (赞：2)

这里给出我（并不能过）的玄学算法。

首先我们发现题目要求的东西不好搞，我们可以试着转化一下。

考虑每个区间的贡献，我们发现每个区间 $[l,r]$ 被算进答案中的概率是 $(1-p_{l-1})(1-p_{r+1})\prod\limits_{i=l}^rp_i$（之间每一个都要有，由于区间不能被更大的包含所以两边的不能有）。

然后我们预处理 $p$ 的前缀积，$w$ 的前缀和，即可 $O(1)$ 计算贡献。枚举左右端点，总复杂度 $O(n^2)$。

code：
```cpp
#include<cmath>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=1e5+5;
typedef long double ld;
int n,w[maxn];
ld a,b,p[maxn];
int sw[maxn];
ld sp[maxn];
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    scanf("%Lf%Lf",&a,&b);
    for(int i=1;i<=n;i++) w[i]=readint();
    for(int i=1;i<=n;i++) scanf("%Lf",&p[i]);
    p[0]=p[n+1]=0;
    sw[0]=0;
    for(int i=1;i<=n;i++) sw[i]=sw[i-1]+w[i];
    sp[0]=1;
    for(int i=1;i<=n;i++) sp[i]=sp[i-1]*p[i];
    ld ans=0;
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
    	if(sp[i-1]==0) continue;
    	ans+=sp[j]*(1-p[i-1])*(1-p[j+1])*pow(a,b*(j-i))*(sw[j]-sw[i-1])/sp[i-1];
	}
	printf("%Lf\n",ans);
    return 0;
}
```
然后我们考虑优化这个代码。

发现这一行：
```cpp
ans+=sp[j]*(1-p[i-1])*(1-p[j+1])*pow(a,b*(j-i))*(sw[j]-sw[i-1])/sp[i-1];
```
我们可以去考虑固定 $j-i$，发现这个后面这一长串式子可以化成一个幂（可看作定值）乘上两个一大堆关于 $i$ 和 $j$ 的式子的积的差。

我们把其中一列反过来，这样就变成了两个卷积的差乘一个定值的形式。

然后就上 FFT，复杂度 $O(n\log n)$。

不过这东西要跑六次 FFT，常数飞起。而且不知道是我的问题还是做法问题，大一点的数据就直接崩掉了，输出 `-inf`……

所以代码就不放了，但是这个算法理论上是可行的（

---

## 作者：z7z_Eta (赞：2)

> 推荐在[博客](https://www.luogu.com.cn/blog/z7z-Eta/solution-p6036)查看

补篇题解QAQ

当初比赛时真的羞涩, 看到公式就已经傻了, 不敢想。。

~~其实挺简单一题，大力推公式上dp过了那种~~

-------

各路神仙做题前可以顺便切下这道[P1654 OSU!](https://www.luogu.com.cn/problem/P1654)有些帮助。

## 期望dp

说白了就是用期望的形式写式子, 然后dp递推一下QAQ（

由期望的线性可加, 我们珂以对题中所说的每个**连续掌握时刻**求和

也就是:

$$Ans=\sum_{1\le l \le r \le n}a^{b(r-l)}(1-p_{l-1})(1-p_{r+1})\prod{p_{l\dots r}}\sum{w_{l\dots r}}$$

稍加整理:

$$
Ans=\sum_{r=1}^{n}(1-p_{r+1})\sum_{l=1}^{r}a^{b(r-l)}(1-p_{l-1})\prod{p_{l\dots r}}\sum{w_{l\dots r}}
$$

我们把后面一堆设掉:

$$
f_i=\sum_{l=1}^{i}a^{b(i-l)}(1-p_{l-1})\prod{p_{l\dots i}}\sum{w_{l\dots i}}
$$

这样$Ans=\sum(1-p_{i+1})f_i$

把$w_i$和它的系数提出, 发现其他的项和$f_{i-1}$有关, 得到:

$$
f_i=f_{i-1}\ a^b\ p_i+w_{i}\ \sum_{l=1}^{i}a^{b(i-l)}(1-p_{l-1})\prod{p_{l\dots i}}
$$

后面的再设一个:

$$
t_i=\sum_{l=1}^{i}a^{b(i-l)}(1-p_{l-1})\prod{p_{l\dots i}}
$$

式子和$f$很像, 而且一样可以递推...

这样$f_i=f_{i-1}\ a^b\ p_i+w_{i}\ t_i$

写$t_i$怎么递推:

$$
t_i=t_{i-1}\ a^b\ p_i+p_i(1-p_{i-1})
$$

大功告成！

### The code time：

```cpp
// Etavioxy
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#define il inline
#define ll long long
#define rep(i,s,t) for(register int i=(s);i<=(t);i++)
#define rev_rep(i,s,t) for(register int i=(s);i>=(t);i--)
#define each(i,u) for(int i=head[u];i;i=bow[i].nxt)
#define file(s) freopen(s".in" ,"r",stdin),freopen(s".out","w",stdout)
#define pt(x) putchar(x)
using namespace std;
il int ci(){
	register char ch;int f=1;
	while(!isdigit(ch=getchar()))f=ch=='-'?-1:1;
	register int x=ch^'0';
	while(isdigit(ch=getchar()))x=(x*10)+(ch^'0');
	return f*x;
}

enum{N=100023};

double f[N],t[N],p[N];
int w[N];

int main(){
	int n=ci(); double a,b;
	scanf("%lf%lf",&a,&b);
	double x=pow(a,b);
	rep(i,1,n) w[i]=ci();
	rep(i,1,n) scanf("%lf",&p[i]);
	double ans = 0;
	rep(i,1,n){
		t[i] = x*p[i]*t[i-1]+p[i]*(1-p[i-1]);
		f[i] = x*p[i]*f[i-1]+t[i]*w[i];
		ans += (1-p[i+1])*f[i];
	}
	printf("%lf\n",ans);
	return 0;
}

```
-----

虽然所有的推导都不够灵性。~~但是乱用公式却意外地好理解qwq~~。嗯嗯谔谔nya nya nya ~

确定不是您看错了? (公式没问题的啊

---

## 作者：nofind (赞：1)

## [题意](https://www.luogu.com.cn/problem/P6036)

考虑答案是什么：  
$ans=\sum\limits_{1\leqslant l\leqslant r\leqslant n}a^{b(r-l)}(\sum\limits_{i=l}^rw_i)(1-p_{l-1})(1-p_{r+1})\prod\limits_{i=l}^rp_i$  
$=\sum\limits_{l=1}^n(1-p_{l-1})\sum\limits_{r=l}^na^{b(r-l)}(1-p_{r+1})(\sum\limits_{i=l}^rw_i)\prod\limits_{i=l}^rp_i$

考虑枚举$l$，计算后面那一堆东西：  
设$f_l=\sum\limits_{r=l}^na^{b(r-l)}(1-p_{r+1})(\sum\limits_{i=l}^rw_i)\prod\limits_{i=l}^rp_i$。  
考虑从$f_{l+1}$推到$f_l$：  
$f_{l+1}=\sum\limits_{r=l+1}^na^{b(r-l-1)}(1-p_{r+1})Sum(l+1,r)P(l+1,r)$  
$f_l=\sum\limits_{r=l}^na^{b(r-l)}(1-p_{r+1})Sum(l,r)P(l,r)$  
设$g_l=\sum\limits_{r=l}^{n}a^{b(r-l)}(1-p_{r+1})P(l,r)$  
$f_l=f_{l+1}*a^b*p_l+g_{l}*w_l$  
$g_l=g_{l+1}*a^b*p_l+(1-p_{l+1})p_l$

code:
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n;
int w[maxn];
double a,b,c,ans;
double p[maxn],f[maxn],g[maxn];
inline int read()
{
    char c=getchar();int res=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
    return res*f;
}
int main()
{
	n=read();
	scanf("%lf%lf",&a,&b);c=pow(a,b);
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
	f[n]=w[n]*p[n],g[n]=p[n];
	for(int l=n-1;l;l--)
	{
		g[l]=g[l+1]*c*p[l]+(1-p[l+1])*p[l];
		f[l]=f[l+1]*c*p[l]+g[l]*w[l];
	}
	for(int l=1;l<=n;l++)ans+=(1.0-p[l-1])*f[l];
	printf("%lf",ans);
	return 0;
}
```


---

## 作者：yurzhang (赞：1)

更好的阅读体验 -> [推销博客](https://nikaidou-shinku.github.io/%E3%80%90%E9%A2%98%E8%A7%A3%E3%80%91-Luogu6036-Ryoku%E7%88%B1%E5%AD%A6%E4%B9%A0/)

---

# 前言

这个题出的就很怪，感觉没有出好。

我比赛的时候玩了一下午式子没整出来，心态很炸。但是正当我想为什么这个题不取模的时候，我突然发现出题人把精度从 $0.8$ 改成了 $1$。于是我仔细观察了一波数据范围，乱搞把这个题过了。

---

# 正文

## 部分分

首先考虑一个区间对答案的贡献。显然，当一个区间 $[l,r]$ 对答案有贡献的时候一定是从 $l$ 到 $r$ 的每一个知识都被成功掌握**并且 $l-1$ 和 $r+1$ 都没有被成功掌握**。

于是有下面的式子
$$Ans=\sum_{l=1}^{n}{\sum_{r=l}^{n}{f(l,r)\times((1-p_{l-1})(1-p_{r+1})\prod_{i=l}^{r}{p_i})}}$$
预处理 $a$ 的各次幂、$w$ 的前缀和以及 $p$ 的前缀积之后，发现 $f(l,r)$ 与后面的一坨概率都可以 $O(1)$ 计算。于是我们有了一个 $O(n^2)$ 的算法：
```cpp
#include <cstdio>
#include <cmath>

#define N 100010
#define re register
typedef double f64;

int n,w[N],s[N];
f64 a,b,p[N],pp[N]={1.};
f64 ab[N]={1.},ans;

inline f64 f(int l,int r) {
    return ab[r-l]*(s[r]-s[l-1]);
}

int main() {
    scanf("%d%lf%lf",&n,&a,&b);
    for(re int i=1;i<=n;++i) {
        scanf("%d",w+i);
        s[i]=s[i-1]+w[i];
    } for(re int i=1;i<=n;++i) {
        scanf("%lf",p+i);
        pp[i]=pp[i-1]*p[i];
    } ab[1]=pow(a,b);
    for(re int i=2;i<=n;++i)
        ab[i]=ab[i-1]*ab[1];
    for(re int i=1;i<=n;++i)
        for(re int j=i;j<=n;++j)
            ans+=f(i,j)*pp[j]/pp[i-1]*(1-p[j+1])*(1-p[i-1]);
    printf("%.2lf",ans);
    return 0;
}
```
愉快地交一发之后你获得了 $20$ 分的[好成绩](https://www.luogu.com.cn/record/29912091)。

之所以没有得到 $55$ 分是因为 $p$ 的前缀积精度丢失太严重了。我们考虑一个经典套路：对 $p$ 取 $\ln$ 之后存前缀和。于是你获得了 $55$ 分的[好成绩](https://www.luogu.com.cn/record/29912994)。

## ~~伪~~正解

我在考场上把这个式子接下来用各种方式展开变形，耗费了大量时间也没有获得能在更优复杂度内计算的算法。正当我疯狂自闭的时候我们发现：
$$0.5\leqslant a\leqslant0.9$$
看到没有？题目保证了 $a$ 是小于 $1$ 的，这意味着当区间长度变长之后 $a^{b(r-l)}$ 会变得非常非常小，以至于乘上 $\sum{w_i}$ 之后都无法对答案产生较大影响。

这启发我们不要傻乎乎地枚举所有区间计算贡献，只需要枚举比较短的区间计算贡献即可。于是我[一发](https://www.luogu.com.cn/record/29915021)过了这个题。

## 如何卡掉

这个乱搞应该不是很难卡，只要让长区间也能对答案造成较大影响即可。我们又发现：
$$0<b\leqslant0.8$$
于是我们只要造一组 $a$ 较大 $b$ 较小的数据，这个做法应该就会当场暴毙。

---

# 最后

至于正解的递推，我考场上也考虑过，不过由于我没能想到用多项式近似表示 $a^{bx}$，式子也不是很好推，最后什么也没弄出来，就放弃了。

应该也有其它神仙做法~~或乱搞~~，大概会比这个做法好到不知到哪里去了。这个题把数据再加强下应该会是道好题。

---

## 作者：JohnVictor (赞：1)

做出来了也没发现那个$a,b$是干哈的，直接给$a^b$不就行了，这是WYXKK大佬说的.
实际上，就是这样的.

我们考虑期望dp,记$f[i]$为只有前$i$个人时的答案，那么本题的答案就是$f[n]$.

我们考虑使用$f[1],f[2],...,f[i]$去计算$f[i+1]$,分类讨论：

第一种情况，没有掌握第$i+1$种知识，概率为$1-p_{i+1}$,期望就是$f[i]$.

第二种情况，掌握了第$i+1$种知识，概率为$p_{i+1}$，下面计算期望.

记$j$为第$i+1$种知识所在的连续段的长度，那么出题人巨佬掌握了第$i+2-j,...,i+1$种知识且没有掌握第$i+1-j$种知识，这个的概率是$(1-p_{i+1-j})p_{i+2-j}...p_{i+1}$,所以这种情况的期望就是

$(1-p_{i+1-j})p_{i+2-j}...p_{i+1}(a^{b(j-1)}(w_{i+2-j}+...+w_{i+1})+f_{i-j})$

而总的期望就是对于$j$求和.

式子推到这里了，但是还是不能暴力求，否则就退化到$o(n^2)$了，所以我们把上面那个式子打开，变成

$(1-p_{i+1-j})p_{i+2-j}...p_{i+1}a^{b(j-1)}(w_{i+2-j}+...+w_{i+1})$+$f_{i-j}(1-p_{i+1-j})p_{i+2-j}...p_{i+1}$

再对$j$求和，设左边那个东西对$j$求和后叫做$g[i]$,右边那个叫做$h[i]$，那么这两个都可以递推求解，（式子不难推，看代码即可）最后$f[i]=g[i]+h[i]$我们就$o(n)$把这道（代码不到20行的）紫题水过去了.

我提交的时候才发现，cout会被卡精度，看来我的习惯还是太差了qwq.
由于幂函数常数大，直接在前面把$a^b$算出来就行了.
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
double p[maxn],a,b,f[maxn],g[maxn],h[maxn],dp[maxn];
int n,w[maxn];
int main(){
	cin>>n>>a>>b;double x=pow(a,b);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1]*x*p[i]+p[i]*(1-p[i-1]);
		g[i]=g[i-1]*p[i]+f[i-1]*(1-p[i]);
		h[i]=h[i-1]*x*p[i]+w[i]*dp[i];
		f[i]=g[i]+h[i];
	}
	printf("%.10lf",f[n]);
	return 0;
}
```


---

## 作者：Phobia (赞：0)

搞个不一样的做法。

容易发现区间 $[l,r]$ 的贡献是:

$$a^{b(r-l)}\left(\sum_{i=l}^rw_i\right)\left(\prod_{i=l}^rp_i\right)\left(1-p_{l-1}\right)\left(1-p_{r+1}\right)$$

证明的话考虑区间 $[l,r]$ 为极大的概率然后乘上他的贡献，不难写出答案就是:

$$\sum_{1\le l\le r\le n}a^{b(r-l)}\left(\sum_{i=l}^rw_i\right)\left(\prod_{i=l}^rp_i\right)\left(1-p_{l-1}\right)\left(1-p_{r+1}\right)$$

把里面的 $w_i$ 提出来就是:

$$\sum_{i=1}^nw_i\sum_{1\le l\le i\le r\le n} a^{b(r-l)}\left(\prod_{j=l}^rp_j\right)\left(1-p_{l-1}\right)\left(1-p_{r+1}\right)$$

然后发现 $[l,i)$ 和 $(i,r]$ 的贡献独立，于是接着提出来：

$$\sum_{i=1}^n\frac{w_i}{p_i}\left(\sum_{1\le l\le i}a^{b(i-l)}\left(\prod_{j=l}^ip_j\right)\left(1-p_{l-1}\right)\right)\left(\sum_{i\le r\le n} a^{b(r-i)}\left(\prod_{j=i}^rp_j\right)\left(1-p_{r+1}\right)\right)$$

用前后缀和分别维护两坨东西，然后就做完了。

时间复杂度 $O(n)$，空间复杂度 $O(n)$。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int maxn = 100005;

int n, w[maxn];

double a, b, m, ans, p[maxn], pre[maxn], suf[maxn];

int main()
{
	scanf("%d%lf%lf", &n, &a, &b);
	m = pow(a, b);
	for (int i = 1; i <= n; ++i)
		scanf("%d", w + i);
	for (int i = 1; i <= n; ++i)
		scanf("%lf", p + i);
	for (int i = 1; i <= n; ++i)
		pre[i] = (pre[i - 1] * m + (1 - p[i - 1])) * p[i];
	for (int i = n; i >= 1; --i)
		suf[i] = (suf[i + 1] * m + (1 - p[i + 1])) * p[i];
	for (int i = 1; i <= n; ++i)
		ans += w[i] * pre[i] * suf[i] / p[i];
	printf("%.3lf\n", ans);
	return 0;
}
~~~

---

## 作者：zerc (赞：0)

## [Problem](https://www.luogu.com.cn/problem/P6036)

求期望能掌握的每一段连续时刻的知识的喜爱程度之和是多少（需要注意的是，这里所说的连续时刻的知识不能被一段更长的所包含）。

$$ f(l,r)=a^{b(r-l)}  \sum_{i=l}^r w_i$$

## Solution

不难将题意转化为：

$$
\sum_{l=1}^{n}\sum_{r=l}^{n}a^{b(r-l)}(1-p_{l-1})(1-p_{r+1})\left(\prod_{i=l}^{r}p_{i}\right)\left(\sum_{i=l}^{r}w_{i}\right)
$$

注意乘上 $l-1$，$r+1$ 不选的概率。

前缀和优化+暴力枚举时间复杂度 $O(n^2)$，

由数据范围可知正解的时间复杂度应是 $O(n)$ 或 $O(n\log n)$，

因此考虑单独枚举 $l$，递推求解后面的式子：

$$
\sum_{l=1}^{n}(1-p_{l-1})\sum_{r=l}^{n}a^{b(r-l)}(1-p_{r+1})\left(\prod_{i=l}^{r}p_{i}\right)\left(\sum_{i=l}^{r}w_{i}\right)
$$

简便起见，我们设：

$$
\boxed{f_l=\sum_{r=l}^{n}a^{b(r-l)}(1-p_{r+1})\left(\prod_{i=l}^{r}p_{i}\right)\left(\sum_{i=l}^{r}w_{i}\right)}
$$

考虑如何由 $f_{l+1}$ 推 $f_l$：

$$
f_{l+1}=\sum_{r=l+1}^{n}a^{b(r-l-1)}(1-p_{r+1})\left(\prod_{i=l+1}^{r}p_{i}\right)\left(\sum_{i=l+1}^{r}w_{i}\right)
$$

先乘上 $a^b\cdot p_l$：

$$
f_{l+1}\cdot a^b\cdot p_l=\sum_{r=l+1}^{n}a^{b(r-l)}(1-p_{r+1})\left(\prod_{i=l}^{r}p_{i}\right)\left(\sum_{i=l+1}^{r}w_{i}\right)
$$

简便起见，我们设：

$$
g_{l+1}=\sum_{r=l+1}^{n}a^{b(r-l-1)}(1-p_{r+1})\left(\prod_{i=l+1}^{r}p_{i}\right)
$$

乘上 $a^b\cdot p_l\cdot w_l$ 并与上面的式子合并：

$$
f_{l+1}\cdot a^b\cdot p_l+g_{l+1}\cdot a^b\cdot p_l\cdot w_l=\sum_{r=l+1}^{n}a^{b(r-l)}(1-p_{r+1})\left(\prod_{i=l}^{r}p_{i}\right)\left(\sum_{i=l}^{r}w_{i}\right)
$$

再加上 $r=l$ 的情况：

$$
g_l=g_{l+1}\cdot a^b\cdot p_l+p_{l}\cdot (1-p_{l+1})
$$

所以

$$
\boxed{f_{l+1}\cdot a^b\cdot p_l+g_{l}\cdot w_l=\sum_{r=l}^{n}a^{b(r-l)}(1-p_{r+1})\left(\prod_{i=l}^{r}p_{i}\right)\left(\sum_{i=l}^{r}w_{i}\right)}
$$

由此我们得到了 $f$ 和 $g$ 的递推式：

$$
f_l=f_{l+1}\cdot a^b\cdot p_l+g_{l}\cdot w_l
$$

$$
g_l=g_{l+1}\cdot a^b\cdot p_l+p_{l}\cdot (1-p_{l+1})
$$

回归最初的式子，得到：

$$
ans=\sum_{l=1}^{n}(1-p_{l-1})\cdot f_i
$$

然后你就可以 $O(n)$ 解决这个问题了。

## Code


```cpp
double p[maxn], a, b, z;
int n, w[maxn];

int main() {
    scanf("%d %lf %lf", &n, &a, &b);
    a = pow(a, b);
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);
    double f = p[n] * w[n];
    double g = p[n];
    for (int i = n - 1; i >= 0; i--) {
        z += (1.0 - p[i]) * f;
        g = g * a * p[i] + (1 - p[i + 1]) * p[i];
        f = f * a * p[i] + g * w[i];
    }
    printf("%lf\n", z);
    return 0;
}
```

## AD

[blog](https://zerc.tk)

---

