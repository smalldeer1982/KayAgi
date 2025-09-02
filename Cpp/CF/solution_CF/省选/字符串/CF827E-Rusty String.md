# Rusty String

## 题目描述

Grigory loves strings. Recently he found a metal strip on a loft. The strip had length $ n $ and consisted of letters "V" and "K". Unfortunately, rust has eaten some of the letters so that it's now impossible to understand which letter was written.

Grigory couldn't understand for a long time what these letters remind him of, so he became interested in the following question: if we put a letter "V" or "K" on each unreadable position, which values can the period of the resulting string be equal to?

A period of a string is such an integer $ d $ from $ 1 $ to the length of the string that if we put the string shifted by $ d $ positions to the right on itself, then all overlapping letters coincide. For example, $ 3 $ and $ 5 $ are periods of "VKKVK".

## 说明/提示

In the first test case from example we can obtain, for example, "VKKVK", which has periods $ 3 $ and $ 5 $ .

In the second test case we can obtain "VVVVVV" which has all periods from $ 1 $ to $ 6 $ .

In the third test case string "KVKV" has periods $ 2 $ and $ 4 $ , and string "KVKK" has periods $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
3
 
5
V??VK
 
6
??????
 
4
?VK?
```

### 输出

```
2
3 5
6
1 2 3 4 5 6
3
2 3 4
```

# 题解

## 作者：tzc_wk (赞：4)

经典的 $FFT$ 字符串匹配

如果没做过 P4173 的建议移步至 P4173

顺便给我的 blog 打个广告：[FFT&NTT 学习笔记](https://www.luogu.com.cn/blog/et2006/fftntt-xue-xi-bi-ji)

将这个字符串看作一个多项式 $\sum\limits_{i=0}^{n-1}s(x)\times x^i$。由于存在通配符，那么将通配符 $?$ 设为编号 $0$，$V,K$ 分别设为 $1,2$，那么第 $i$ 位上的字符与第 $j$ 位上的字符完全匹配当且仅当 $(s(i)-s(j))^2\times s(i) \times s(j)=0$。

定义完全匹配函数 $P(x)$：如果 $s$ 的前 $x$ 为与后 $x$ 位完全匹配，那么返回值为 $0$，否则返回值非零。那么 $P(x)=\sum\limits_{i=0}^{x-1}(s(i)-s(n-x+i))^2\times s(i)\times s(n-x+i)$。很明显，如果 $s$ 的前 $x$ 位与后 $x$ 位完全匹配，那么就有一个周期 $n-x$。

接下来我们的任务就是求出所有的 $P(x)$。老套路，我们翻转 $s$，假设翻转过后的串为 $t$，那么 $P(x)$ 可改写为 $P(x)=\sum\limits_{i=0}^{x-1}(t(n-i-1)-s(n-x+i))^2\times t(n-i-1)\times s(n-x+i)$。将括号打开， $P(x)=\sum\limits_{i=0}^{x-1}t(n-i-1)\times s(n-x+i)^3+t(n-i-1)^3\times s(n-x+i)-2 \times t(n-i-1)^2\times s(n-x+i)^2$。由于 $(n-i-1)+(n-x+i)=2n-x-1$，又可以改为：$\sum\limits_{i+j=2n-x-1}t(i)s(j)^3+t(i)^3s(j)-2t(i)^2s(j)^2$。容易发现上面三项都是卷积的形式，使用多项式乘法求出它们的值就完了。

什么？完了？

如果你按照上面的方式写的话，你~~十有八九~~ 百分之百连样例都没有过。在第一组数据中，你的程序跑出来是

```cpp
3
2 3 5
```

而答案是：

```cpp
2
3 5
```

~~感谢良心的出题人提供这么一组样例~~。

我们再来看一下。

```
V**VK
  V**VK
```

在这个例子中，当 $d=2$ 的时候，第三个字符（"?"）在上面与 'V' 匹配，而在下面与 'K' 匹配。而一个 '?' 不能同时既是 'V' 也是 'K'。毕竟，它只是一个不确定的符号，而不是通配符。它不能与通配符等价。

~~此时此刻，你的心是不是在滴血？~~

~~然而希望就在前方，The silver lining is just ahead!~~

我们先证明一个引理：如果 $k$ 为合法的周期，那么所有 $k$ 的倍数也是合法的周期。反过来，如果 $k$ 不是合法的周期，那么肯定存在一个它的倍数也不是合法的周期。

证明：如下图（图来自于 [xtx1092515503](https://www.luogu.com.cn/user/123369) 巨佬的 [这篇博客](https://www.luogu.com.cn/blog/Troverld/fft-xue-xi-bi-ji)）：

![](https://cdn.luogu.com.cn/upload/image_hosting/h3b0egnj.png)

那么，所有红线的位置都相等，绿线的位置也相等。也就是说如果有一个周期为 $k$，存在一种将 '?' 变为 'V' 或 'K' 的方式，使得对于所有 $i \equiv j \pmod{k}$，$s_i=s_j$，因此，$k$ 的倍数也是一个合法的 $period$。

我们证明另外一个引理：假设有一个周期 $k$，由于把 '?' 被当成了通配符被我们算进去了，那么必存在一个周期 $k'=\lambda k$，$\lambda$ 为整数，满足这个压根儿没有没我们算进去。

证明：当周期为 $k$ 的时候，'?' 被当成了一个通配符，那么必有 $k<\frac{n}{2}$（由于有重叠部分）。

根据引理 $1$，肯定存在一个周期 $k''=\lambda'' k$ 满足它不是一个合法的 $period$（注：“不是一个合法的周期”不等于“没有被我们算进去”，那些由于我们把 '?' 当成通配符被我们算进去的，实际上也不是合法的周期）。接下来又两种情况：

1. $k'' \geq \frac{n}{2}$，那么它肯定没有被我们算进去，因为没有重叠部分，满足条件。

2. $k'' \leq \frac{n}{2}$，又可以分出两小点：

- $k''$ 没有被我们算进去，满足条件

- $k''$ 由于我们将 '?' 当成通配符，被我们算进去了。那么肯定还存在一个 $k''$ 的倍数 $k'''$ 不是一个合法的周期，直到回到前两个情况。由于 $k'''>k''$，因此 $k'''$ 总有一天会达到 $\frac{n}{2}$ 的，因此得证。

这样一来就简单了。我们将没有被我们算进去的周期扔进一个 $vector$，然后枚举其因数，如果这个因数被我们算进去了，那么就说明我们由于把 '?' 当成通配符将原来不合法的看成合法了，把它扔掉就完了。

~~这次是真的完了。~~

```cpp
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
const double Pi=acos(-1.0);
struct comp{
	double x,y;
	comp(){x=y=0;}
	comp(double a,double b){x=a;y=b;}
	inline comp operator +(comp c){return comp(x+c.x,y+c.y);}
	inline comp operator -(comp c){return comp(x-c.x,y-c.y);}
	inline comp operator *(comp c){return comp(x*c.x-y*c.y,x*c.y+y*c.x);}
} a[1<<22],b[1<<22],p[1<<22];
int rev[1<<22];
inline void FFT(int len,comp* a,int type){
	for(int i=0;i<len;i++){
		if(i<rev[i])	swap(a[i],a[rev[i]]);
	}
	for(int mid=1;mid<len;mid<<=1){
		comp W(cos(Pi/mid),type*sin(Pi/mid));
		for(int j=0;j<len;j+=mid<<1){
			comp w(1,0);
			for(int k=0;k<mid;k++){
				comp x=a[j+k],y=w*a[j+mid+k];
				a[j+k]=x+y;
				a[j+mid+k]=x-y;
				w=w*W;
			}
		}
	}
}
int pt1[1<<22],pt2[1<<22];
inline int id(char c){
	if(c=='?')	return 0;
	if(c=='K')	return 1;
	if(c=='V')	return 2;
}
char s[1<<22],_s[1<<22];
int len=1;
int n;
inline void match(){
	for(int i=0;i<len;i++)	a[i]=b[i]=p[i]=comp(0,0),pt1[i]=pt2[i]=0;
	for(int i=0;i<n;i++)	pt1[i]=id(s[i]);
	for(int i=0;i<n;i++)	pt2[i]=id(_s[i]);
	for(int i=0;i<len;i++)	a[i]=comp(pt1[i]*pt1[i]*pt1[i],0);
	for(int i=0;i<len;i++)	b[i]=comp(pt2[i],0);
	FFT(len,a,1);FFT(len,b,1);
	for(int i=0;i<len;i++)	p[i]=p[i]+a[i]*b[i];
	for(int i=0;i<len;i++)	a[i]=comp(pt1[i],0);
	for(int i=0;i<len;i++)	b[i]=comp(pt2[i]*pt2[i]*pt2[i],0);
	FFT(len,a,1);FFT(len,b,1);
	for(int i=0;i<len;i++)	p[i]=p[i]+a[i]*b[i];
	for(int i=0;i<len;i++)	a[i]=comp(pt1[i]*pt1[i],0);
	for(int i=0;i<len;i++)	b[i]=comp(pt2[i]*pt2[i],0);
	FFT(len,a,1);FFT(len,b,1);
	for(int i=0;i<len;i++)	p[i]=p[i]-comp(2,0)*a[i]*b[i];
	FFT(len,p,-1);
	set<int> ans;
	vector<int> unans;
	for(int i=n;i<=n*2-1;i++){
		int t=int(p[i].x/len+0.5);
		if(t==0)	ans.insert(n-(2*n-1-i));
	}
//	cout<<ans.size()<<endl;
	for(int i=1;i<=n;i++)	if(ans.find(i)==ans.end()){
		unans.push_back(i);
	}
	foreach(it,unans){
		int tmp=*it;
		vector<int> fac;
		for(int i=1;i*i<=tmp;i++){
			if(tmp%i==0){
				fac.push_back(i);
				if(i!=tmp/i){
					fac.push_back(tmp/i);
				}
			}
		}
		foreach(i,fac){
			int x=*i;
			if(ans.find(x)!=ans.end())	ans.erase(ans.find(x));
		}
	}
	cout<<ans.size()<<endl;
	foreach(it,ans)	cout<<*it<<" ";puts("");
}
inline void solve(){
	n=read();cin>>s;
	len=1;
	int num=0;
	while(len<=(n<<1))	len<<=1,num++;
	for(int i=0;i<len;i++)	rev[i]=0;
	for(int i=0;i<len;i++)	rev[i]=(rev[i>>1]>>1)|((i&1)<<(num-1));
	for(int i=0;i<len;i++)	_s[i]=0;
	fz(i,0,n-1)	_s[i]=s[i];
	reverse(_s,_s+n);
	match();
}
int main(){
	int T=read();
	while(T--)	solve();
	return 0;
}
```

---

## 作者：shadowice1984 (赞：4)

人傻常数大说的就是我~

1e6的fft也是醉了……

________________

这题是个套路题，多项式乘法优化带通配符的字符串匹配

题目意思简单明了，给你一个字符集为2的字符串，带不确定符，求每一个可能出现的“period”长度，“period”长度为d意思是如果将这个字符串右移d位之后这个字符串和原来的字符串是否可以匹配

那么我们来看一下这道题……

假设我们要确定这个串是否有长度为d的"period",实际上就是在确定这个式子是否为0(显然这是一个暴力式子)

$$\sum_{i}[S_{i} \neq S_{i+d}]$$

然后我们将整个串翻转一下得到一个串$S^{'}$

$$\sum_{i}[S_{i} \neq S_{n-1-i-d}^{'}]$$

重新写一下变成了

$$\sum_{i+j=n-1-d}[S_{i} \neq S_{j}^{'}]$$

似乎这式子非常像卷积？~~(不，就是卷积)~~

问题来了我们怎么将不等号写成乘法的形式呢？

$$\sum_{i+j=n-1-d}[S_{i}==V][S_{j}^{'}==K ]+[S_{i}==K][S_{j}^{'}==V ]$$

反正字符集只有两个，暴力枚举一下就行了

然后你愉快的打了个fft/ntt然后算了两遍卷积加起来却发现自己连样例都没过……

~~excuse me?~~

然后我们发现其实

$$[S_{i} \neq S_{j}^{'}] \neq [S_{i}==V][S_{j}^{'}==K ]+[S_{i}==K][S_{j}^{'}==V ]$$

为什么呢？

因为我们的问号是不确定的字符，并不是通配符，请注意这两个东西是不一样的，**未知不等于通配**

煮个栗子

V？？VK

@@V？？VK

可以看到如果是?是通配符的话这个字符串是有2的“period”的

但是由于?不是通配符，所以第二个?由于在匹配的时候既是V又是K所以凉掉了

~~笑容逐渐凝固~~

然后我们发现这种特例还是可以抢救一下的，发现一个性质是如果出现了这种假的匹配情况的话，他的倍数中至少有一个连假的"period"都不是

这个性质的证明可以自己画图理解一下

所以就是卷积两遍加起来然后判一下每位置是不是假的"period"就行了

~~fft忘了写的ntt~~

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=1048576+10;typedef unsigned long long ll;const ll mod=998244353;
const int U=1048576;int rv[N];ll rt[2][22];int n;char mde[N];int T;
inline ll po(ll a,ll p){ll r=1;for(;p;p>>=1,a=a*a%mod)if(p&1)r=r*a%mod;return r;}
inline void ntt(ll* a,int o,int len)
{
    for(int i=0;i<len;i++)if(i<rv[i])swap(a[i],a[rv[i]]);
    for(int k=1,j=1;k<len;k<<=1,j++)
        for(int s=0;s<len;s+=(k<<1))
            for(int i=s,w=1;i<s+k;i++,w=w*rt[o][j]%mod)
                {ll a0=a[i];ll a1=a[i+k]*w%mod;a[i]=(a0+a1)%mod,a[i+k]=(a0+mod-a1)%mod;}
    if(o){ll inv=po(len,mod-2);for(int i=0;i<len;i++)(a[i]*=inv)%=mod;}
}ll f1[N];ll f2[N];ll f3[N];
inline void solve()
{
    scanf("%d",&n);scanf("%s",mde);//构造多项式之后卷积两遍加起来
    int d=0;int le=1;for(;le<(n<<1);le<<=1,d++);
    for(int i=0;i<le;i++)rv[i]=(rv[i>>1]>>1)|((i&1)<<(d-1));
    for(int i=0;i<n;i++)f1[i]=(mde[i]=='V');
    for(int i=0;i<n;i++)f2[i]=(mde[n-1-i]=='K');
    ntt(f1,0,le);ntt(f2,0,le);for(int i=0;i<le;i++)(f1[i]*=f2[i])%=mod;
    ntt(f1,1,le);reverse(f1,f1+n);for(int i=0;i<n;i++)f3[i]+=f1[i];
    for(int i=0;i<le;i++)f1[i]=0;for(int i=0;i<le;i++)f2[i]=0;
    for(int i=0;i<n;i++)f1[i]=(mde[i]=='K');
    for(int i=0;i<n;i++)f2[i]=(mde[n-i-1]=='V');
    ntt(f1,0,le);ntt(f2,0,le);for(int i=0;i<le;i++)(f1[i]*=f2[i])%=mod;
    ntt(f1,1,le);reverse(f1,f1+n);for(int i=0;i<n;i++)f3[i]+=f1[i];
    int cnt=0;
    for(int i=1;i<=n;i++)//特判一下特殊情况
        for(int j=2*i;j<=n;j+=i)if(f3[j]!=0){f3[i]=-1;break;}
    for(int i=1;i<=n;i++)cnt+=(f3[i]==0);printf("%d\n",cnt);
    for(int i=1;i<=n;i++)if(f3[i]==0)printf("%d ",i);printf("\n");
    for(int i=0;i<=n;i++)f3[i]=0;
    for(int i=0;i<le;i++)f1[i]=0;for(int i=0;i<le;i++)f2[i]=0;
}
int main()
{
    for(int j=1,t=(mod-1)/2;j<=20;t>>=1,j++)rt[0][j]=po(3,t);
    for(int j=1,t=(mod-1)/2;j<=20;t>>=1,j++)rt[1][j]=po(332748118,t);//拜拜程序~
    scanf("%d",&T);for(int z=1;z<=T;z++)solve();return 0;
}
```










---

## 作者：辰星凌 (赞：2)

# **【题解】Rusty String [CF827E]**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12377227.html)

传送门：[$\text{Rusty String}$](https://www.luogu.com.cn/problem/CF827E) [$\text{[CF827E]}$](http://codeforces.com/problemset/problem/827/E)

## **【题目描述】**

多组数据，每组数据给出一个由 $V,K,?$ 三种字符组成的字符串，其中 $?$ 可以替换为 $V,K$ 中的任意一个，求替换后的字符串可以存在的循环周期有哪些。

## **【分析】**

乍一看像是带通配符的字符串匹配（不会的强烈建议去康康[这个](https://www.luogu.com.cn/blog/Ebola-Emperor/solution-p4173)），由于字符集不大，按照套路就应该枚举两个字符 $a \ne b\in\{V,K\}$，然后设 $f(i)=[A[i]=a],$ $g(i)=[A[i]=b]$

则有： $PA(k)=\sum_{i=1}^{n}f(i)g(i+k)$，翻转 $f$ 得到：$PA(k)=\sum_{i=1}^{n}f(n-i+1)g(i+k)$ $=\sum_{i+j=n+k+1}f(i)g(j)$

很明显是个 $\text{FFT}$ 的板子，把式子卷起来就可以了。

按照以往的“经验”，或者说惯性思维，多半会这样做（比如说我），但写出来却发现酱紫连第一个样例都过不了。

那么问题出在哪儿了呢？

注意：当 $PA(k) \ne 0$ 时说明在某个地方出现了 $'V'$ 与 $'K'$ 相对应的情况，以 $k$ 作为周期肯定不合法，但 $PA(k) = 0$ 并不能说明 $k$ 一定是合法周期，因为这道题中的特殊符号不是通配符，而是未知字符，通配符可以任意匹配，但未知字符只能匹配一种。

比如样例 $1$，用上面的错误算法多输出了一个 $2$，在这种情况下 $S_3('?')$ 分别与 $S_1('V'),S_5('K')$ 进行了匹配，因此以 $2$ 作为周期是不合法的。

考虑改进算法：

之前的做法错在算出来的式子只进行了一周目的匹配判断，那么我们只要将二周目、三周目……全部都判断一下就好了呀，正巧序列 $PA$ 完美的包含了所有长度的循环情况，所以直接暴力枚举周期的倍数即可（复杂度为 $O(\frac{n}{1}+\frac{n}{2}+\frac{n}{3} \cdots \frac{n}{n})=O(n\ln n)$）。

总时间复杂度为：$O(n\log n)$ 。

你说啥？卡常？玄学优化减少调用次数？不存在的，我写了这么久的 $\text{NTT}$，还从未被卡过（~~小骄傲~~）。

$\text{emm...}$

等等，还没完，仔细看题啊：“_保证输入字符串总长不超过500000_ 。” 注意是输入总长，所以不要偷懒用 $\text{memset}$！

## **【Code】**

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#define LL long long
#define Re register int
using namespace std;
const int N=1048576+3,P=998244353,G=3;
int n,T,ans,invG,f[N],g[N],tr[N],PA[N],can[N];char A[N];
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
inline int mi(Re x,Re k){
    Re s=1;
    while(k){
        if(k&1)s=(LL)s*x%P;
        x=(LL)x*x%P,k>>=1;
    }
    return s;
}
inline int inv(Re x){return mi(x,P-2);}
inline void NTT(Re *f,Re n,Re op){
    for(Re i=0;i<n;++i)if(i<tr[i])swap(f[i],f[tr[i]]);
    for(Re p=2;p<=n;p<<=1){
        Re len=p>>1,w1=mi(op?invG:G,(P-1)/p);
        for(Re st=0;st<n;st+=p)
            for(Re j=st,base=1;j<=st+len-1;++j){
                Re tmp=(LL)base*f[j+len]%P;
                f[j+len]=(f[j]-tmp+P)%P,(f[j]+=tmp)%=P;
                base=(LL)base*w1%P;
            }
    }
}
inline void sakura(Re *f,Re n,Re *g,Re m){//卷卷卷
    Re n_=n;
    for(m+=n,n=1;n<=m;n<<=1);Re invn=inv(n);
    for(Re i=n_+1;i<=n;++i)f[i]=g[i]=0;//注意初始化
    for(Re i=1;i<n;++i)tr[i]=(tr[i>>1]>>1)|((i&1)?n>>1:0);
    NTT(f,n,0),NTT(g,n,0);
    for(Re i=0;i<n;++i)f[i]=(LL)f[i]*g[i]%P;
    NTT(f,n,1);
    for(Re i=0;i<=m;++i)f[i]=(LL)f[i]*invn%P;
}
int main(){
//    freopen("123.txt","r",stdin);
    in(T),invG=inv(G);
    while(T--){
        in(n),scanf("%s",A+1),ans=0;
        for(Re i=1;i<=n;++i)PA[i]=0;//注意初始化
        for(Re i=1;i<=n;++i)f[n-i+1]=(A[i]=='K'),g[i]=(A[i]=='V');
        sakura(f,n,g,n);
        for(Re i=1;i<n;++i)PA[i]+=f[i+n+1];//PA[n]可以不用管，因为一定合法
        for(Re i=1;i<=n;++i)f[n-i+1]=(A[i]=='V'),g[i]=(A[i]=='K');
        sakura(f,n,g,n);
        for(Re i=1;i<n;++i)PA[i]+=f[i+n+1];
        for(Re i=1;i<=n;++i){
            can[i]=1;
            for(Re j=i;j<=n&&can[i];j+=i)can[i]&=(!PA[j]);//枚举倍数依次判断
            ans+=can[i];
        }
        printf("%d\n",ans);
        for(Re i=1;i<=n;++i)if(can[i])printf("%d ",i);puts("");
    }
}
```

最后还是忍不住吐槽一下，这题不至于黑吧，顶多紫。


---

## 作者：FutaRimeWoawaSete (赞：1)

考场没有想到循环的性质，直接就把这玩意儿往式子里面扔结果死翘翘了。              

首先我们老套路的把原字符串变成两倍作为文本串 B ，原字符串作为模式串 A,这时侯我们之后我们直接用 A 来匹配 B 即可。配对函数 $P(x)$ 表示在文本串里面末位置为 x 时是否配对：         

当字符为 ? 时取 0 ， 其余两种情况各取 1 , 2。

$P(x) = \sum_{i = 0} ^ m (A(i) - B(x - m + 1 + i)) ^ 2 A(i)B(x - m + 1 + i)$        

接着展开后，令 $A(i) = S(m - i - 1) , a = S(i) , b = B(x - m + 1 + i)$ 得到：        

$P(x) = \sum_{i = 0} ^ m a^3b + ab^3 - 2 a^2b^2$          

$P(x) = \sum_{i + j == m} a^3b + \sum_{i + j == m} ab^3 - 2 \times \sum_{i + j == m} a^2b^2$           

把上面式子卷积一下就好了，至此为止这道题都还是很板。           

接着我们发现这样搞根本过不掉，因为我们的 ? 并不是通配符，所以这样就有可能导致同一个位置的 ? 填入字符不一处理不掉然后就死翘翘了。                  

接着我们发现我们接下来需要判断一下当前字符串的所有位置相同的 ? ，不过这里我们巧妙的发现，如果我们要去判断当前所有位置相同的 ? ，其实就是看后面 $P(x + x) , P(x + 2x) ……$ 的情况，因为这些信息相当于就已经给你处理好了，所以我们只要去遍历它即可。            

不过需要注意下这里我们需要先把上一段中的 $P(x)$ 转化为以 x 为始位置时的含义。    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int Len = 4e6 + 5;
const double Pi = acos(-1);
int Print[Len];
struct CP {
	double x,y;
	CP(double xx = 0 , double yy = 0) {
		x = xx , y = yy;
	}
	CP operator + (const CP &B) const {
		return CP(x + B.x , y + B.y);
	}
	CP operator - (const CP &B) const {
		return CP(x - B.x , y - B.y);
	}
	CP operator * (const CP &B) const {
		return CP(x * B.x - y * B.y , x * B.y + y * B.x);
	}
	CP operator / (double B) const {
		return CP(x / B , y / B);
	}
	inline void clear() {
		x = 0.0 , y = 0.0;
	}
} f[Len] , g[Len] , P[Len];
int Rd[Len],PPer[Len],tot;
void FFT(CP *f , int lens , bool flag) {
	for(register int i = 0 ; i < lens ; i ++) if(i < Rd[i]) swap(f[i] , f[Rd[i]]);
	for(register int p = 2 ; p <= lens ; p <<= 1) {
		int len = p >> 1;
		CP mul(cos(2 * Pi / p) , sin(2 * Pi / p));
		if(flag) mul.y *= -1;
		for(int k = 0 ; k < lens ; k += p) {
			CP buf(1 , 0);
			for(int l = k ; l < k + len ; l ++) {
				CP tt = buf * f[len + l];
				f[len + l] = f[l] - tt;
				f[l] = f[l]	+ tt;
				buf = buf * mul;
			}
		}
	}
	if(flag) for(register int i = 0 ; i < lens ; i ++) f[i] = f[i] / (1.0 * lens);
}
bool per[Len];
int n,m,Lens = 1;
double A[Len] , B[Len];
char s[Len] , ss[Len];
signed main() {
	int t;
	scanf("%d",&t);
	while(t --) {
		scanf("%d",&n);
		scanf("%s",s);
		Lens = 1;
		tot = 0;
		m = n;
		n = n << 1;
		for(register int i = 0 ; i < m ; i ++) {
			if(s[i] == '?') A[i] = 0.0;
			else if(s[i] == 'V') A[i] = 1.0;
			else A[i] = 2.0;
		}
		for(register int i = 0 ; i < n ; i ++) {
			if(i >= m || s[i] == '?') B[i] = 0.0;
			else if(s[i] == 'V') B[i] = 1.0;
			else B[i] = 2.0;
		}
		reverse(A , A + m);
		while(Lens <= (n + m)) Lens <<= 1;
		for(register int i = 0 ; i < Lens ; i ++) P[i].clear();
		for(register int i = 0 ; i < Lens ; i ++) Rd[i] = (Rd[i >> 1] >> 1) | ((i & 1) ? Lens >> 1 : 0);

		for(register int i = 0 ; i < Lens ; i ++) f[i] = g[i] = CP(0 , 0);
		for(register int i = 0 ; i < m ; i ++) f[i] = CP(A[i] * A[i] * A[i] , 0);
		for(register int i = 0 ; i < n ; i ++) g[i] = CP(B[i] , 0);
		FFT(f , Lens , 0) , FFT(g , Lens , 0);
		for(register int i = 0 ; i < Lens ; i ++) P[i] = P[i] + f[i] * g[i];

		for(register int i = 0 ; i < Lens ; i ++) f[i] = g[i] = CP(0 , 0);
		for(register int i = 0 ; i < m ; i ++) f[i] = CP(A[i] , 0);
		for(register int i = 0 ; i < n ; i ++) g[i] = CP(B[i] * B[i] * B[i], 0);
		FFT(f , Lens , 0) , FFT(g , Lens , 0);
		for(register int i = 0 ; i < Lens ; i ++) P[i] = P[i] + f[i] * g[i];

		for(register int i = 0 ; i < Lens ; i ++) f[i] = g[i] = CP(0 , 0);
		for(register int i = 0 ; i < m ; i ++) f[i] = CP(A[i] * A[i] , 0);
		for(register int i = 0 ; i < n ; i ++) g[i] = CP(B[i] * B[i] , 0);
		FFT(f , Lens , 0) , FFT(g , Lens , 0);
		for(int i = 0 ; i < Lens ; i ++) P[i] = P[i] - CP(2 , 0) * f[i] * g[i];

		FFT(P , Lens , 1);

		int cnt = 0;
		for(int i = 1 ; i <= m ; i ++) per[i] = 0;
		for(int i = m ; i < n ; i ++)
			if(fabs(P[i].x) < 0.5) per[i - m + 1] = 1;
		for(register int i = 1 ; i <= m ; i ++) {
			bool flag = true;
			if(!per[i]) continue;
			for(int j = i ; j <= m ; j += i)
				if(!per[j]) {
					per[i] = 0;
					break;
				}
			if(per[i]) PPer[++ tot] = i;
		}

		printf("%d\n",tot);

		for(int i = 1 ; i <= tot ; i ++) printf("%d " , PPer[i]);

		puts("");
	}
	return 0;
}
```

---

## 作者：729hao (赞：0)

[**luogu 传送门**](https://www.luogu.com.cn/problem/CF827E) [**codeforces 传送门**](https://codeforces.com/problemset/problem/827/E)


---
字符串下标从 $0$ 开始。

## 思路
考虑位移了 $i$ 位，那么对于任意的正整数 $r\ (0\le r < i)$，原第 $r$ 位与第 $i+r$ 位重叠，原第 $i+r$ 位与第 $2i+r$ 位重叠，以此类推。

要想重叠部分一样，则有 $s_r=s_{i+r}$，$s_{i+r}=s_{2i+r}$，$s_{2i+r}=s_{3i+r}$ ……

即 $s_r=s_{i+r}=s_{2i+r}=s_{3i+r}=\cdots$，即下标 $\bmod\ i$ 相同的位置除开 `?` 外应该相同。

  换而言之，若存在 $l,r\ (l<r)$，使得 $s_l\ne\ $`?`$\ \land s_r\ne\ $`?`$\ \land\ s_l\ne s_r$，那么 $r-l$ 以及 $r-l$ 的因数都不符合条件。

剩下的部分就是 [P4173](https://www.luogu.com.cn/problem/P4173) 了，NTT 求每个位移是否完全匹配即可。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace cs{
	#define LL long long
	#define fir first
	#define sec second
	typedef pair<int,int> PII;
	const int N=5e5;
	const int NF=1<<21;
	const LL Mod=998244353;
	LL fastpow(LL a,LL x){
		LL rtn=1ll;
		while(x){
			if(x&1) rtn=rtn*a%Mod;
			a=a*a%Mod;
			x>>=1;
		}
		return rtn;
	}
	int rev[NF+5];
	LL F[NF+5],G[NF+5],F2[NF+5],G2[NF+5],F3[NF+5],G3[NF+5];
	void change(LL* y,int len){
		for(int i=1;i<len;i++){
			rev[i]=rev[i>>1]>>1;
			if(i&1) rev[i]|=len>>1;
			if(i<rev[i]) swap(y[i],y[rev[i]]);
		}
	}
	void NTT(LL* f,int len,int I){
		change(f,len);
		LL cur,step,f0,cf1;
		for(int nowl=2;nowl<=len;nowl<<=1){
			step=fastpow(3,I==-1?Mod-1-(Mod-1)/nowl:(Mod-1)/nowl);
			for(int i=0;i<len;i+=nowl){
				cur=1ll;
				for(int j=i;j<i+(nowl>>1);j++){
					f0=f[j]%Mod;
					cf1=cur*f[j+(nowl>>1)]%Mod;
					f[j]=f0+cf1;
					f[j+(nowl>>1)]=f0-cf1;
					cur=cur*step%Mod;
				}
			}
		}
		if(I==-1){
			LL inv=fastpow(len,Mod-2);
			for(int i=0;i<len;i++){
				f[i]=f[i]*inv%Mod;
			}
		}
	}
	int T,n,alen;
	string s;
	vector<int> ans;
	bitset<N+5> flag;
	int Map(char c){
		if(c=='V') return 1;
		if(c=='K') return 2;
		return 0;
	}
	void Init(){
		for(int i=0;i<alen;i++){
			F[i]=F2[i]=F3[i]=0;
			G[i]=G2[i]=G3[i]=0;
		}
		ans.clear();
		for(int i=1;i<=n;i++){
			flag[i]=0;
		}
	}
	int main(){
		ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
		cin>>T;
		while(T--){
			Init();
			cin>>n>>s;
			alen=1<<(__lg(3*n-1)+1);
			for(int i=0;i<n;i++){
				F[i]=G[n-1-i]=Map(s[i]);
				F2[i]=G2[n-1-i]=Map(s[i])*Map(s[i]);
				F3[i]=G3[n-1-i]=Map(s[i])*Map(s[i])*Map(s[i]);
			}
			NTT(F,alen,1);
			NTT(F2,alen,1);
			NTT(F3,alen,1);
			NTT(G,alen,1);
			NTT(G2,alen,1);
			NTT(G3,alen,1);
			for(int i=0;i<alen;i++){
				G3[i]=G3[i]*F[i]%Mod;
				G2[i]=G2[i]*F2[i]%Mod;
				G[i]=G[i]*F3[i]%Mod;
			}
			NTT(G3,alen,-1);
			NTT(G2,alen,-1);
			NTT(G,alen,-1);
			for(int i=1;i<=n;i++){
				if((G3[n-1+i]+G[n-1+i]-2*G2[n-1+i])%Mod==0) flag[i]=1;
			}
			for(int i=1;i<=n;i++){
				if(!flag[i]) continue;
				for(int j=i;j<=n;j+=i){
					if(!flag[j]){
						flag[i]=0;
						break;
					}
				}
				if(flag[i]) ans.push_back(i);
			}
			cout<<ans.size()<<"\n";
			for(auto u:ans){
				cout<<u<<" ";
			}
			cout<<"\n";
		}
		return 0;
	}
}
int main(){
	cs::main();
	return 0;
}
```

---

