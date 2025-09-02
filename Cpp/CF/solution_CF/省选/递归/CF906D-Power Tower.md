# Power Tower

## 题目描述

Priests of the Quetzalcoatl cult want to build a tower to represent a power of their god. Tower is usually made of power-charged rocks. It is built with the help of rare magic by levitating the current top of tower and adding rocks at its bottom. If top, which is built from $ k-1 $ rocks, possesses power $ p $ and we want to add the rock charged with power $ w_{k} $ then value of power of a new tower will be $ {w_{k}}^{p} $ .

Rocks are added from the last to the first. That is for sequence $ w_{1},...,w_{m} $ value of power will be

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF906D/a7b9adfbee151f2e3ef09f9dbad2cf6b657882ca.png)After tower is built, its power may be extremely large. But still priests want to get some information about it, namely they want to know a number called cumulative power which is the true value of power taken modulo $ m $ . Priests have $ n $ rocks numbered from $ 1 $ to $ n $ . They ask you to calculate which value of cumulative power will the tower possess if they will build it from rocks numbered $ l,l+1,...,r $ .

## 说明/提示

 $ 3^{27}=7625597484987 $

## 样例 #1

### 输入

```
6 1000000000
1 2 2 3 3 3
8
1 1
1 6
2 2
2 3
2 4
4 4
4 5
4 6
```

### 输出

```
1
1
2
4
256
3
27
597484987
```

# 题解

## 作者：C20203030 (赞：20)

## 一、题目

[点此看题](https://www.luogu.org/problem/CF906D)

## 二、解法

好像是一个欧拉降幂版题，但仔细想想时间复杂度是$O(n^2)$。

考虑$\varphi$的下降速度，有一个结论，当$n>2$时，$\varphi(n)$是偶数。

证明可以考虑更相减损术，$\gcd(i,n)=\gcd(n-i,n)$，所以$i$和$n-i$要么同时互质，要么同时不互质。

由于$\varphi(n)=n\prod\frac{p_i-1}{p_i}$，而$n$又含有一个偶数因子，所以$\varphi$的下降是$\log$级的，时间复杂度就有了保证，因为我们在模数为$1$的时候就可以停止迭代。

但是欧拉降幂的写法我们还是需要注意，一定要严格遵循下列公式：

$a^c=\begin{cases}
a^c & c<\varphi(b)\\
a^{c\%\varphi(b)+\varphi(b)} & otherwise
\end{cases}\mod b$

原因是当$\gcd(a,b)\not =1$是$a^{\varphi(b)}=1 \mod b$不一定成立，这也是欧拉降幂的一大难点，代码中会写详细的注释。


```cpp
#include <cstdio>
#include <cmath>
#include <map>
using namespace std;
#define int long long
const int MAXN = 100005;
int read()
{
	int x=0,flag=1;char c;
	while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
	while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*flag;
}
int n,m,q,l,r,a[MAXN];
map<int,int> ph;
int phi(int n)//算欧拉函数
{
	int t=sqrt(n),res=n;
	for(int i=2;i<=t;i++)
	{
		if(n%i==0)
		{
			res/=i;res*=(i-1);
			while(n%i==0) n/=i;
		}
	}
	if(n>1) res/=n,res*=(n-1);
	return res;
}
int qkpow(int a,int b,int MOD)
{
	int res=1;
	while(b>0)
	{
		if(b&1) {res=res*a;if(res>=MOD) res=res%MOD+MOD;}
		a=a*a;if(a>=MOD) a=a%MOD+MOD;
		//这里要注意，如果中途出现了>=MOD的情况我们要加上MOD，以满足欧拉降幂的公式
		b>>=1;
	}
	return res;
}
int dfs(int x,int p)
{
	if(x==r+1 || p==1)//出口，p=1时要返回1，因为我们要加上p，也就是上一层的phi[p]
		return 1;
	int t=dfs(x+1,ph[p]);//默认返回的值是满足公式的，qkpow需要维护
	return qkpow(a[x],t,p);
}
signed main()
{
	n=read();m=read();
	int cur=m;
	while(cur!=1) ph[cur]=phi(cur),cur=ph[cur];
	ph[cur]=1;//预处理所有可能用到的phi，存map
	for(int i=1;i<=n;i++)
		a[i]=read();
	q=read();
	while(q--)
	{
		l=read();r=read();
		printf("%lld\n",dfs(l,m)%m);
	}
}
```



---

## 作者：suxxsfe (赞：10)

[先安利我的博客](https://www.cnblogs.com/suxxsfe/p/12637571.html)  

## 扩展欧拉定理  
[CF906D Power Tower](http://codeforces.com/problemset/problem/906/D)  


洛谷交的第二个黑题  

## 题意  

给出一个序列$w-1,w_2,\cdots,w_n$，以及$q$个询问  
每个询问给出$l,r$，求：  
$$w_l^{w_{l+1}^{w_{l+2}^{\cdots^{w_r}}}}\bmod p$$  

$w_i\le 10^9,p\le 10^9,n\le 10^5,q\le 10^5$  

-------------  

相似题：[P4139 上帝与集合的正确用法](https://www.luogu.com.cn/problem/P4139)  
都是用扩展欧拉定理，如果你不知道扩展欧拉定理是啥，[看这里](https://www.cnblogs.com/suxxsfe/p/12527200.html)  
和那题一样，递归的处理指数，和$p$取模，然后每递归一层，就让$p\leftarrow \varphi(p)$  
然后这样一层层递归下去，直到$p=1$或者$l=r$  

对于任意一个偶数$p$，总有$\varphi(p)\le \dfrac{p}{2}$，因为在小于等于它的数中，一定会有$\dfrac{p}{2}$个数是二的倍数，不和他互质  
然后又因为对于$p>2$，总有$\varphi(p)$为偶数，原因是当$\gcd(d,p)=1,\gcd(p-d,p)=1$（这个可以由反证法很容易的得出）  

所以，对于任意一个$p$，先经过一次给他变成$\varphi(p)$，然后只要$\log$次就可以把它变成$1$，所以递归最多$O(\log p)$层  

但是要开一个`map`来记录已经算出的$\varphi$，否则$O(q\log p\sqrt p)$跑不出来  

还有一个问题，就是扩展欧拉定理的应用条件是$b\ge \varphi(p)$，$b$是指数  
所以要判断一下$b$和$\varphi(p)$的大小关系，然而那个上帝与集合的题不用这样，因为那个是无限个$2$在指数上，显然$b>\varphi(p)$  
但是，我们在下一层递归中返回的，已经是对$\varphi(p)$取模以后$b$的值了，不是真实值，无法比较  
如果同时记录真实值和取模后的值又比较麻烦，所以考虑每次取模，都是如果大于等于模数，就让他取模后再加上模数，如果小于模数当然就不管  

结束递归回溯的时候也要取模  

$\texttt{code.}$  
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<map>
#define reg register
#define EN std::puts("")
#define LL long long
inline LL read(){
	register LL x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
int w[100006];
std::map<LL,LL>map;
inline LL get_phi(LL n){
	if(map.find(n)!=map.end()) return map[n];
	LL ret=n;
	for(reg LL i=2;i*i<=n;i++){
		if(!(n%i)) ret=ret/i*(i-1);
		while(!(n%i)) n/=i;
	}
	if(n>1) ret=ret/n*(n-1);
	map[n]=ret;
	return ret;
}
inline LL mo(LL x,LL mod){
	return x<mod?x:(x%mod+mod);
}
inline LL power(LL a,LL b,LL mod){
	LL ret=1;
	while(b){
		if(b&1) ret=mo(ret*a,mod);
		a=mo(a*a,mod);b>>=1;
	}
	return ret;
}
LL work(int l,int r,LL p){
	if(l==r||p==1) return mo(w[l],p);
	return power(w[l],work(l+1,r,get_phi(p)),p);
}
int main(){
	LL n=read(),p=read(); 
	for(reg int i=1;i<=n;i++) w[i]=read();
	int q=read();while(q--){
		int l=read(),r=read();
		std::printf("%lld\n",work(l,r,p)%p);
	}
	return 0;
}
```

---

## 作者：OldVagrant (赞：5)

## 题意
[题意传送门](https://www.luogu.com.cn/problem/CF906D)
## Solution
欧拉定理降幂板子题。   
前置知识：欧拉定理，快速幂，求单个数的欧拉函数值。   
（~~当然你不会也没事，不过不会的应该不大可能来做这种题~~）。   
题目让我们求 $w_l^{w_{l+1}^{w_{l+2}^.......^{w_r}}}\pmod p$,显然暴力快速幂会TLE掉，考虑使用欧拉定理。         
由欧拉定理得：   
当 $b\geq\varphi(p)$ 时，$a^b\equiv a^{b\bmod \varphi(p)+\varphi(p)} \pmod p$，这里 $\gcd(a,p)$ 可以不为 1。如果 $b<\varphi(p)$,此时无需降幂，直接快速幂计算即可。  
定义函数 $G(l,r,p)=w_l^{w_{l+1}^{w_{l+2}^.......^{w_r}}}\pmod p$。   
由欧拉定理，上式可以转换为：$G(l,r,p)=w_l^{G(l+1,r,\varphi(p))+\varphi(p)}\pmod p\  (w_{l+1}^{w_{l+2}^.......^{w_r}}\ge \varphi(p))$ 或 $G(l,r,p)=w_l^{G(l+1,r,\varphi(p))}\pmod p\  (w_{l+1}^{w_{l+2}^.......^{w_r}}< \varphi(p))$。  
可以观察到，每往下递归一次，模数就会变成上一次的模数的欧拉函数值，而经过 $\log(p)$ 次后模数就会为1，下面给出证明。   
由欧拉函数的定义得：
$\varphi(m)=m\prod\limits_{p|m}\frac{p-1}{p}$       
当 $m$ 无素因子 2 时,一个奇素因子一定会产生素因子 2,因为 $p-1$ 是偶数。
当 $m$ 有素因子 2 时,$\varphi(m)\leq \frac{m}{2}$,值至少减半。
综上，经过 $\log(p)$ 次后模数会变为 1，递归计算即可。    
但还有一个问题，如何判断 $w_{l+1}^{w_{l+2}^.......^{w_r}}$ 和 $\varphi(p)$ 的大小？  
考虑让快速幂和 $G$ 函数返回一个二元组 $(val,flag)$,$val$ 为计算结果,$flag$ 为 $w_{l+1}^{w_{l+2}^.......^{w_r}}$ 是否比 $\varphi(p)$ 大，快速幂进行取模的时候判断一下取模前的数和模数的大小关系并更新 $flag$ 的值，$G(l,r,p)$ 进行快速幂时是否需要加上 $\varphi(p)$ 就取决于上一层返回的 $flag$ 值，模数为 1 时直接返回 $(0,true)$, 底数为 1 时直接返回 $(1,false)$ (前面已经判断过模数为 1 的情况，所以模数一定大于 1），当 $l=r$ 时还要判断一下 $w_l$ 和模数的关系，如果 $w_l\geq p$ 就返回 $(w_l\bmod p,1)$ (注意不是 $\varphi(p)$) ，否则返回 $(w_l,0)$。   
欧拉函数的值可以直接暴力计算，用一个哈希表记录下来（可以选择 ```unordered_map``` ）,后面要用的时候直接取即可。    
单次询问的复杂度为 $O(\log^2p)$，总复杂度 $O(m\log^2p)$（计算欧拉函数值的复杂度不计）,可以通过此题。
## Code
计算欧拉函数的地方和上面写的有点区别，其他没什么，注释掉的部分为快读快写，可以不加。
```c
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rint register int
#define gc getchar
#define pc(x) putchar(x)
int a[100001],n,m,p,l,r,k,ph[1001],cnt,fk;
/*const int LEN=1<<21;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
void pc(char x){
	if(Pout==Pout_last) fwrite(PUF,1,Pout-PUF,stdout),Pout=PUF;
	*Pout++=x;
}*/
int read(){
	int x=0;
	char ch=gc();
	while(ch<'0'||ch>'9') ch=gc();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=gc();
	return x;
}
void write(int a){
	if(a>9) write(a/10);
	pc(a%10+48);
}
struct flag{//big即为判断大小关系的属性，val即为计算结果
	int val;
	bool big;
};
int getphi(int x){//暴力计算欧拉函数值
	int a=x;
	if(!(x&1)){
		a>>=1,x>>=1;
		while(!(x&1)) x>>=1;
	}for(rint i=3;i*i<=x;i+=2){
		if(!(x%i)){
			a/=i,x/=i,a*=i-1;
			while(!(x%i)) x/=i;
		}
	}if(x>1) a/=x,a*=x-1;
	return a;
}
flag qpow(int a,int b,int p){
	int ans=1,ans1=1,la=a,z=0;
	flag tmp;
	while(b){
		if(b&1){
			ans=(ll)ans*a%p;
			if(ans1>ans) z=1;//如果上一次的值比这一次的大，那么一定是取模了，因为a为非负整数
			ans1=ans;
		}a=(ll)a*a%p,b>>=1;
		if(la>a) z=1;//同理
		la=a;
	}tmp.big=z,tmp.val=ans;
	return tmp;
}
flag G(int x,int y,int p,int dep){//dep为深度，或者说要把p变成phi（p）多少次
	flag f;
	if(p<2){//模数为1直接返回（0,1）
		f.val=0,f.big=1;
		return f;
	}if(a[x]<2){//底数为1直接返回（1，0）
		f.val=1,f.big=0;
		return f;
	}if(x==y){//达到边界要判断一下当前数与模数的关系
		a[x]<p?(f.val=a[x],f.big=0):(f.val=a[x]%p,f.big=1);
		return f;
	}f=G(x+1,y,ph[dep],dep+1);//上一层的结果
	if(f.big) f.val+=ph[dep];//如果比phi(p)大就加上
	return qpow(a[x],f.val,p);
}
signed main(){
	n=read(),p=read(),fk=p;
	while(fk>1) fk=getphi(fk),ph[++cnt]=fk;//这里不断把p变为phi(p)，因为每组数据只有一个p，所以每次递归时的模数是可以预处理出来的
    ph[++cnt]=1;
	for(rint i=1;i<=n;i++) a[i]=read();
	m=read();
	while(m--) l=read(),r=read(),write(G(l,r,p,1).val),pc('\n');
	//fwrite(PUF,1,Pout-PUF,stdout);
	return 0;
}
```


---

## 作者：VenusM1nT (赞：4)

扩展欧拉定理。

在了解这东西之前，我们首先要知道欧拉定理是什么。

本文同步发表于笔者的博客：[题解 CF906D Power Tower / 欧拉定理 & 扩展欧拉定理学习笔记](https://venusnero.github.io/2019/03/04/solution_cf906d_euler_theorem_note/)

欧拉定理：

$$\text{当}\ \gcd(a,p)=1 \ \text{时，有}\ a^{\varphi(p)}\equiv1\ (\text{mod}\ p)$$

所以可以得：

$$a^b\equiv a^{b\ \text{mod}\ \varphi(p)}\ (\text{mod}\ p)$$

但是因为有一个 $\gcd(a,p)=1$ 的限制，所以不能对所有情况适用，此时我们就需要引入扩展欧拉定理了。

$$\text{当}\ b≥\varphi(p)\ \text{时，有}\ a^b\equiv a^{b\ \text{mod}\ \varphi(p)+\varphi(p)}\ (\text{mod}\ p)$$

$b<\varphi(p)$ 时就正常算就行了。

知道这个之后我们可以怎么做呢？显然，我们可以递归求解一些形如 $a^b\ \text{mod}\ p$ 的问题了，对于这题，也可以不递归，递推即可。

当然，因为 $m\leq1e9$，所以线筛 $\varphi$ 的办法是刑不通的，我们可以直接暴力算，然后开一个 map 存下我们算的值，重复调用时可以省下很多复杂度。

```cpp
#include<bits/stdc++.h>
#define MAXN 100000
#define int long long
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
using namespace std;
int n,m,Mod,a[MAXN+5];
map <int,int> phi;
template <typename T> void Read(T &x)
{
	x=0;
	int fu=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') fu=-1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch-48);
	x*=fu;
}
int Phi(int x)
{
	int res=x,pos=x;
	if(phi.count(x)) return phi[x];
	for(int i=2;i<=sqrt(x);i++)
	{
		if(!(x%i))
		{
			res=res/i*(i-1);
			while(!(x%i)) x/=i;
		}
	}
	if(x>1) res=res/x*(x-1);
	return phi[pos]=res;
}
int Mo(int x,int p)
{
	return x<p?x:(x%p+p);
}
int QuickPow(int x,int y,int p)
{
	int res=1;
	while(y)
	{
		if(y&1) res=Mo(res*x,p);
		x=Mo(x*x,p);
		y>>=1;
	}
	return res;
}
int Dfs(int l,int r,int p)
{
	return (l==r || p==1)?Mo(a[l],p):QuickPow(a[l],Dfs(l+1,r,Phi(p)),p);
}
signed main()
{
	freopen("data.in","r",stdin);
	Read(n);
	Read(Mod);
	for(int i=1;i<=n;i++) Read(a[i]);
	Read(m);
	while(m--)
	{
		int x,y;
		Read(x);
		Read(y);
		printf("%lld\n",Dfs(x,y,Mod)%Mod);
	}
	return 0;
}
```

---

## 作者：Styx (赞：1)

**做这道题，欧拉定理已经不够了，因为无法保证a与mod互质
此处引出扩展欧拉定理**


![](https://images2018.cnblogs.com/blog/1188068/201804/1188068-20180419204041495-690697661.png)

**然后我们尝试展开a^b^c**

![](https://images2018.cnblogs.com/blog/1188068/201804/1188068-20180419204511929-2060606896.png)

**再往下也是一样的,我们可以先预处理出phi[p],phi[phi[p]]……**

**大概要处理几层呢?logn层,为什么呢?**

**假设phi[now]=1了**

**那么之上不管多少层**

**x=1,2,3,4,5……**

**这些数模一都是0**

**所以就成了欧拉函数的衰变速度(我瞎糊的名词,意思是经过几次phi,p会变成1)**

**这个复杂度是logn的,我们可以对这进行一发dfs,加上快速幂的logn复杂度,总复杂度是loglogn的,值得一提的是,快速幂中也要改成扩展欧拉定理的形式,否则小心炸掉~**

**顺便安利一下同类题：bzoj3884 上帝与集合的正确用法**

**以及被我们魔改的不成样子的U23882 天真♂哲学家♂树(Naive Philosopher Tree)**

**嗯，代码如下：**

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int a[100010],phi[100],n,m,mod;

int get(int x)
{
    int ans=x;
    for(int i=2;i*i<=x;i++)
    {
        if(x%i==0)
        {
            ans=ans/i*(i-1);
            while(x%i==0)
            {
                x/=i;
            }
        }
    }
    if(x!=1)
    {
        ans=ans/x*(x-1);
    }
    return ans;
}

int gg(long long x,int p)
{
    return x>=p?x%p+p:x;
}

int kasumi(int a,int b,int p)
{
    int ans=1;
    while(b)
    {
        if(b&1)
        {
            ans=gg(1ll*ans*a,p);
        }
        a=gg(1ll*a*a,p);
        b>>=1;
    }
    return ans;
}

int dfs(int l,int r,int i)
{
    if(l==r||phi[i]==1)
    {
        return gg(a[l],phi[i]);
    }
    return kasumi(a[l],dfs(l+1,r,i+1),phi[i]);
}

int main()
{
    scanf("%d%d",&n,&mod);
    phi[0]=mod;
    for(int i=1;i<=30;i++)
    {
        phi[i]=get(phi[i-1]);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",dfs(l,r,0)%mod);
    }
    return 0;
}
```

---

## 作者：功在不舍 (赞：1)

我直接对着代码详细讲一下细节吧。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
typedef long long ll;
ll w[100001],n,p,m,x,y;
ll fastpow(ll di,ll zhi,ll p)//快速幂
{
	ll yu=1,flag=0;
	while(zhi>0)
	{
		if(zhi%2==1)yu=yu*di;
		di=di*di;//这里和普通的快速幂不同 ，先不要对di和yu取模，
		//因为扩展欧拉定理的使用需要指数大于模数的欧拉函数值，而在我们递归调用solve的时候
		//fastpow()就是上一层solve的指数！（它的p是上一层的欧拉函数值）所以要判断是否能达到p。 
		if(yu>=p)flag=1,yu%=p;//小于p的话没必要取余数，
		if(di>=p)flag=1,di%=p;//大于等于p的话就可以欧拉降幂了
		zhi=zhi/2;
	}//如果达到了p，根据扩展欧拉定理，还要把yu加上p 
	if(flag)yu+=p;
	return yu;
}
//欧拉函数定义：phi(N)=小于等于N的正整数中与N互质的数的个数
//这里直接通过通项公式sqrt(N)时间内求解phi(N),不知道的直接取查百度
map <ll,ll> tab;
ll phi(ll x)//用一个map来避免重复计算
{
	if(tab[x])return tab[x];
	ll phi=x,s=x;
	for(ll i=2;i*i<=x;i++)//枚举因数 
	{
		if(x%i==0)//i一定是x的一个质因数，道理看下面 
		{
			while(x%i==0)x/=i;//这里去掉了x里所有的i因子，而我们是从小到大枚举的因数， 
			//如果此时i是一个合数因子，那么他的最小质因子应该早就被while循环给排除了 
			phi=phi/i*(i-1);
		}
	}
	if(x!=1)phi=phi/x*(x-1);//一个数有可能拥有一个大于sqrt(N)的质因子，而且最多只会有一个
	//x如果不是1，那么它必定是一个质因子，因为它在上面的循环中没有被排出，说明它没有2-sqrt(N)之间因子，是一个质数。 
	return tab[s]=phi;//存着下次用
}
//看似是最坏O（n）的dfs，其实最多执行log层
//对一个数字不停求欧拉函数，求logn次就会变成1
//例如phi(100)->phi(40)->phi(16)->phi(8)->phi(4)-phi>(2)->1
//因为gcd(i,n)=gcd(n-i,n)每次求欧拉函数都是折半的
//扩展欧拉定理，不知道的建议取做 欧拉定理 那个题目 
ll solve(ll l,ll r,ll p)
{
	if(l==r||p==1)return w[l]>=p?w[l]%p+p:w[l];//注意边界有两个：p已经降到了1或者序列已经取完，还是判断w[l]和p的大小关系 
    return fastpow(w[l],solve(l+1,r,phi(p)),p);//递归调用solve，注意不要取余数，这可能会导致fastpow里最后加上的p白加了 
}
int main()
{
	scanf("%lld%lld",&n,&p);
	for(int i=1;i<=n;i++)scanf("%lld",&w[i]);
	scanf("%lld",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&x,&y);
		printf("%lld\n",solve(x,y,p)%p);//注意这里还要%p，因为fastpow()最后一次执行的时候可能加上了P，而solve里是不能取余数的 
	}
	return 0;
}
```cpp

---

## 作者：Simphoni (赞：1)

# Idea
欧拉定理:  
$ (a,b)=1 \ \Rightarrow \ a^{\varphi(p)} \equiv 1 \pmod p $ 所以 $(a,b)=1 \ \Rightarrow \ a^{b} \equiv a^{b \ mod \ \varphi(p)} \pmod p $  
对于$(a,b)\neq 1$,有扩展定理:
$ b \ge \varphi(p) \ \Rightarrow \ a^{b} \equiv a^{b \ mod \ \varphi(p)+\varphi(p)} \pmod p $
注意到对一个数不停求$phi$,最多经过log步,我们可以预处理出对k不断求$phi$的值.
对于每一个询问,从l开始递归求指数部分,复杂度O(Nlog^2N).
注意递归下去时,如果指数小于phi,要按照原定理而不是扩展定理.
因此快速幂的时候要对此加以处理
# Code
```cpp
inline int pow(int x, int exp, int mod) {
  int r = 1;
  for (; exp; exp >>= 1) {
    if (exp & 1) {
      if (1LL * r * x >= mod) r = 1LL * r * x % mod + mod;
      else r *= x;
    }
    if (1LL * x * x >= mod) x = 1LL * x * x % mod + mod;
    else x *= x;
  }
  return r;
}
inline int work(int l, int r, int p) {
  if (l == r) return a[l] >= step[p] ? (a[l] % step[p]) + step[p] : a[l];
  if (step[p] == 1) return 1;
  int res = pow(a[l], work(l + 1, r, p + 1), step[p]);
  if (res >= step[p]) res = res % step[p] + step[p];
  return res;
}
```

---

## 作者：Supor__Shoep (赞：0)

这道题就只是一道小小的扩展欧拉定理而已。

首先我们可以用一下欧拉降幂公式：

$$n^x \ mod \ m=n^{\phi(m)+x \ mod \ \phi(m)} \ [x>\phi(m)]$$

如此一来，这个过程变成了一个递归，每一个数字的指数都等于后一个数字到右端点的幂。也就是题目中提示到的内容。即：

$$x_1=a,x_2=b^{x_1},x_3=c^{x_2}…$$

可是这个递归有多少层呢？

大概就有 $\log n$ 层。先假设 $\phi(now)=1$，那么不管往上多少层，对于其中 $x$ 的值都是模一得一。

接着考虑到 $a^b$ 这样的幂，我们需要一个快速幂的函数，带上取模，前提是一定满足欧拉降幂定理。更重要的是，在取模时，必须实在取模之后加上模数，不能忽略欧拉降幂。

一直迭代后，如果模数变成了 $1$，那么我们就只能结束搜索，因为任何整数模 $1$ 的结果都是 $0$。

最后不要忘记记忆化，记忆化这个东西就特别好，在极端条件下还是不容易超时。更何况这是一道考验压缩时间的题。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int a[100005],s[105];
int n,m,mod;
int get(int x)
{
    int ans=x;
    for(int i=2;i*i<=x;i++)
    {
        if(x%i==0)
        {
            ans=ans/i*(i-1);
            while(x%i==0)
            {
                x/=i;
            }
        }
    }
    if(x!=1)
    {
        ans=ans/x*(x-1);
    }
    return ans;
}
int pk(long long x,int p)
{
    return x>=p?x%p+p:x;
}
int Pow(int a,int b,int p)
{
    int ans=1;
    while(b)
    {
        if(b&1)
        {
            ans=pk(1ll*ans*a,p);
        }
        a=pk(1ll*a*a,p);
        b>>=1;
    }
    return ans;
}
int dfs(int l,int r,int i)
{
    if(l==r||s[i]==1)
    {
        return pk(a[l],s[i]);
    }
    return Pow(a[l],dfs(l+1,r,i+1),s[i]);
}
int main()
{
    cin>>n>>mod;
    s[0]=mod;
    for(int i=1;i<=30;i++)
    {
        s[i]=get(s[i-1]);
    }
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    cin>>m;
    while(m--)
    {
        int l,r;
        cin>>l>>r;
        cout<<dfs(l,r,0)%mod<<endl;
    }
    return 0;
}
```

---

## 作者：BzhH (赞：0)

一道比较裸的扩欧模板题。

扩展欧拉定理 $a^c=\begin{cases}a^{c~mod`\phi(p)},gcd(a,p)=1\\a^c,gcd(a,p) \ne1,c < \phi(p)\\a^{c~mod~\phi(p)+\phi(p)},gcd(a,p)=1,c\ge \phi(p)\end{cases}$

具体证明就不再这里讲解了~~主要是不会~~。

很明显,可以直接用欧拉定理递归降幂,那么怎么保证时间复杂度是对的呢？

我们将m分解为 $\prod\limits_{i=1}^k p_i^{q_i}$，

那么 $\phi(m)=\phi(\prod\limits_{i=1}^k p_i^{q_i})=\prod\limits_{i=1}^k (p_i-1)p_i^{q_i-1}$。

到这里就可以看出,每迭代一遍欧拉函数,就相当于把 $m$ 中的所有质因子全部取出来减个一再乘回去,

要得到 $\phi(m)=1$,只需要迭代 $m$ 中每个质因子可以取出来的2的数量,时间复杂度是 $log$ 级的。

对于题目中的每一个 $\phi$ 可以先预处理一遍,用 $map$ 存起来。

代码
```
#include<iostream>
#include<cstdio>
#include<unordered_map>
using namespace std;
const int N = 1e5 + 5;
typedef long long ll;

unordered_map<ll, ll> phi;
ll w[N];

ll pi(ll p)
{
    ll res = p;
    for (ll i = 2; i * i <= p; i++)
    {
        if (p % i == 0)
            res -= res / i;
        while (p % i == 0)
            p /= i;
    }
    if (p > 1)
        res -= res / p;
    return res;
}

ll qmi(ll a, ll b, ll c)
{
    ll res = 1;
    bool flag = false;
    while (b)
    {
        if (b & 1)
        {
            res *= a;
            if (res >= c)
                flag = true;
            res %= c;
        }
        a *= a;
        if (a >= c)
            flag = true;
        a %= c;
        b >>= 1;
    }
    if (flag)
        res += c;//需要满足欧拉定理
    return res;
}

ll dfs(ll l, ll r, ll p)
{
    if (l == r + 1 || p == 1)
        return 1;
    return qmi(w[l], dfs(l + 1, r, phi[p]), p);
}

int main()
{
    ll n, p;
    scanf("%lld%lld", &n, &p);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &w[i]);
    ll now = p;
    while (now != 1)
        phi[now] = pi(now), now = phi[now];
    phi[now] = 1;
    ll q;
    scanf("%lld", &q);
    while (q--)
    {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", dfs(l, r, p) % p);
    }
    return 0;
}
```

---

## 作者：pomelo_nene (赞：0)

拓展欧拉定理板题。有如下定理：

若 $\gcd(a,m)\not = 1$，满足：

$$
a^p=
\begin{cases}
a^p\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ p<\varphi(m)\\

a^{p \bmod \varphi(m)+\varphi(m)} \ \ \ \ \operatorname{otherwise}
\end{cases}
$$

所以可以直接欧拉定理降幂。注意快速幂中的答案（即后来的指数）也要满足拓展欧拉定理，当答案 $p$ 大于 $m$ 时，$p=p \bmod m + m$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
LL read()
{
	LL x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
void write(LL x)
{
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
LL varphi(LL n)
{
    LL ans=n;
    for(LL i=2;i*i<=n;++i)
    {
        if(n%i==0)
        {
            ans-=ans/i;
            while(n%i==0)	n/=i;
        }
    }
    if(n>1)	ans-=ans/n;
    return ans;
}
map<LL,LL> phi;
LL n,m,w[100005],q;
LL QuickPow(LL a,LL x,LL mod)
{
	LL base=a,ans=1;
	while(x)
	{
		if(x&1)	ans*=base,ans=(ans>=mod?ans%mod+mod:ans);
		x>>=1;
		base*=base;
		if(base>=mod)	base%=mod,base+=mod;
	}
	return ans;
}
LL dfs(LL now,LL r,LL mod)
{
	if(now==r+1 || mod==1)	return 1;
	LL p=dfs(now+1,r,phi[mod]);
	return QuickPow(w[now],p,mod);
}
int main(){
	n=read(),m=read();
	LL tmp=m;
	while(tmp>1)	phi[tmp]=varphi(tmp),tmp=phi[tmp];
	phi[1]=1;
	for(LL i=1;i<=n;++i)	w[i]=read();
	q=read();
	while(q-->0)
	{
		LL l=read(),r=read();
		write(dfs(l,r,m)%m);
		puts("");
	}
	return 0;
}
```

$\ \ \ $

---

## 作者：shao0320 (赞：0)

欧拉降幂板子

由扩展欧拉定理得

当$c>p$时，$b^c\%p=b^{c\%\phi(p)+\phi(p)}$。

而由于$\phi(p)$的下降速度是$log$级别的，因此直接暴力算就好了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<cmath>
#define N 1000005
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,a[N],q,l,r;
map<int,int>mp;
int ksm(int a,int b,int mod)
{
	int r=1;
	while(b)
	{
		if(b&1)
		{
			r*=a;
			if(r>=mod)r=r%mod+mod;
		}
		a*=a;
		if(a>=mod)a=a%mod+mod;
		b>>=1;
	}
	return r;
}
inline int phi(int x)
{
	int u=sqrt(x),res=x;
	for(int i=2;i<=u;i++)
	{
		//cout<<i<<endl;
		if(x%i==0)
		{
			res/=i;res*=(i-1);
			while(x%i==0)x/=i;
		}
	}
	if(x>1)res/=x,res*=(x-1);
	return res;
}
int dfs(int now,int p)
{
	//cout<<now<<" "<<r<<" "<<p<<" "<<phi(p)<<endl;
	if(now==r+1||p==1)return 1;
	return ksm(a[now],dfs(now+1,mp[p]),p);
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	int now=m;
	while(now!=1)mp[now]=phi(now),now=mp[now];
	mp[now]=1;
	while(q--)
	{
		l=read();r=read();
		printf("%lld\n",dfs(l,m)%m);
	}
	return 0;
}
```



---

