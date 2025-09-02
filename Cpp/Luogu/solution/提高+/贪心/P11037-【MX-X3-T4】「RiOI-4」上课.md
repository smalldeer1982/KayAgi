# 【MX-X3-T4】「RiOI-4」上课

## 题目背景

原题链接：<https://oier.team/problems/X3E>。

---

一天，小 M 在宿舍 $6:53$ 起床，而早自习 $7:00$ 开始。

## 题目描述

给定正整数 $n,q$ 和 $n$ 个区间 $[l_i,r_i]$。

有 $q$ 组询问，每次询问给定一个整数 $x$。在每个区间内选择一个整数 $a_i$（$l_i\leq a_i\leq r_i$），使得所选整数的总和等于 $x$，并使得选出的 $a$ 序列的方差最小。输出方差最小值，对 $998\,244\,353$ 取模。保证存在至少一种合法的选取方案。

关于方差的有关定义参照此[云剪切板](https://www.luogu.com.cn/paste/dpptrubn)，有理数取模参照[【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)。


## 说明/提示

**【样例解释 #1】**

询问一方差最小的选择方案为 ${1,2,3}$，最小方差为 $\frac{2}{3}$，有 $665\,496\,236\times3\equiv 2\pmod{998\,244\,353}$，故输出 $665\,496\,236$。

询问二方差最小的选择方案为 ${3,3,3}$，最小方差为 $0$，有 $0\times1\equiv 0\pmod {998\,244\,353}$，故输出 $0$。

询问三方差最小的选择方案为 ${3,3,5}$，最小方差为 $\frac{8}{9}$，有 $554\,580\,197\times9\equiv 8\pmod{998\,244\,353}$，故输出 $554\,580\,197$。

**【数据范围】**

**本题开启捆绑测试。**

|子任务|分数|$n$|$q$|特殊性质|
|:-:|:-:|:-:|:-:|:-:|
|$1$|$9$|$\le5$|$\le5$|$r_i\le5$|
|$2$|$13$|$\le2\times10^3$|$\le2\times10^3$|$r_i\le2\times10^3$|
|$3$|$16$|$\le10^6$|$=1$||
|$4$|$25$|$\le10^5$|$\le10^5$|$r_i\le10^5$|
|$5$|$37$|$\le10^6$|$\le10^6$||

对于所有数据，满足 $1\leq n,q\leq 10^6$，$0\leq l_i\leq r_i\leq 10^{6}$，对于每个 $x$ 保证存在一种合法的方案。

## 样例 #1

### 输入

```
3 3
1 3
2 3
3 5
6
9
11```

### 输出

```
665496236
0
554580197```

## 样例 #2

### 输入

```
4 3
1 4
11 12
3 9
6 10
21
29
26```

### 输出

```
811073551
811073543
748683272```

# 题解

## 作者：Wf_yjqd (赞：11)

怎么评蓝的？怎么评蓝的？怎么评蓝的？

---

平均数 $\bar x=\frac{\sum\limits_{i=1}^n x_i}{n}$。

方差简单的变形，$\frac{\sum\limits_{i=1}^n(x_i-\bar x)^2}{n}=\frac{\sum\limits_{i=1}^n x_i^2}{n}-(\bar x)^2$。

显然对于每个询问，平均数是固定的，所以题目相当于最小化平方和。

假设一开始所有 $a_i$ 都取到 $l_i$，只需要以此为基础将一些 $a_i$ 的值增加。

若将 $x-1$ 增加到 $x$，平方和增加 $x^2-(x-1)^2=x\times2-1$。

所以显然每次将最小值增加 $1$ 最优。

将询问离线，记录可以增加到每个数的数的个数，双指针维护即可。

复杂度 $\operatorname{O}(n\log n)$，瓶颈在于排序。

---

建议评黄。。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=1e6+26,mx=1e6,mod=998244353;
struct Query{
    ll x,id,ans;
    friend bool operator<(Query xy,Query zb){
        return xy.x<zb.x;
    }
}qq[maxn];
ll n,q,invn,l[maxn],r[maxn],cnt[maxn],ans,ansx;
inline ll Pow(ll x,ll y){
    if(!y)
        return 1;
    if(y&1)
        return Pow(x,y^1)*x%mod;
    return Pow(x*x%mod,y>>1);
}
int main(){
    scanf("%lld%lld",&n,&q);
    invn=Pow(n,mod-2);
    for(ll i=1;i<=n;i++){
        scanf("%lld%lld",&l[i],&r[i]);
        ans+=l[i]*l[i];
        ansx+=l[i];
        cnt[l[i]+1]++;
        cnt[r[i]+1]--;
    }
    for(ll i=0;i<=mx;i++)
        cnt[i]+=cnt[i-1];
    for(ll i=1;i<=q;i++){
        scanf("%lld",&qq[i].x);
        qq[i].id=i;
    }
    sort(qq+1,qq+q+1);
    for(ll i=1,j=0;i<=q;i++){
        while(ansx<qq[i].x){
            if(qq[i].x-ansx<cnt[j]){
                cnt[j]-=(qq[i].x-ansx);
                (ans+=(qq[i].x-ansx)*(j*2-1)%mod)%=mod;
                ansx=qq[i].x;
                break;
            }
            ansx+=cnt[j];
            (ans+=cnt[j]*(j*2-1)%mod)%=mod;
            j++;
        }
        qq[i].ans=ans;
        qq[i].x%=mod;
    }
    sort(qq+1,qq+q+1,[](Query xy,Query zb){
        return xy.id<zb.id;
    });
    for(ll i=1;i<=q;i++)
        printf("%lld\n",(qq[i].ans*invn%mod-qq[i].x*qq[i].x%mod*invn%mod*invn%mod+mod)%mod);
    return 0;
}
```

---

## 作者：听取MLE声一片 (赞：5)

拆方差的式子，方差等于平方的平均减平均的平方。因为总和固定，所以平均的平方固定，所以最小化平方和即可。

假设当前对于 $x$ 已求出最小方差的序列，要求 $x+1$ 的最小方差。因为要最小化平方和，所以要把最小的能加的位置加一。原因是平方和公式增加的量是两倍的原数，所以要原数尽可能小。

把初始状态全部取 $l_i$，然后考虑增量即可。

每次把 $x$ 加上一太慢了，考虑对区间按位处理。记录当前位置有多少个区间可以用来加一，这样时间复杂度为 $O(V)$。

将询问离线后排序，从小到大增量，复杂度即可做到 $O(n+V+q
\log q)$。如果记录每位的状态，可以做到在线。

可以做到值域无关，比较麻烦所以没搞。

```#include<iostream>
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
#include<ctime>
#include<random>
#define int long long
#define ll long long
#define min(x,y) ((x)<=(y)?(x):(y))
#define rep(i, f, t) for (int i = (f), ed##i = (t); i <= ed##i; ++i)
namespace FastIO {
	const int SZ=(1<<25)+1;
	struct I {
		char ibuf[SZ],*iS,*iT,c;int f,_eof;FILE*fi;
		I(FILE*f):fi(f){}
		inline char Gc(){return iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SZ,fi),(iS==iT?EOF:*iS++)):*iS++;}
		inline ll operator()(){ll x;operator()(x);return x;}
		inline I&operator()(char&x){x=Gc();return*this;}
		inline I&operator()(char*s){for(c=Gc();c<32||c>126||c==' ';)c=Gc();for(;c>31&&c<127&&c!=' '&&c!='\n'&&c!='\r';++s,c=Gc())*s=c;*s=0;return*this;}
		template<class T>inline I&operator()(T&x){_eof=0;for(f=1,c=Gc();(c<'0'||c>'9')&&!_eof;c=Gc()){if(c=='-')f=-1;_eof|=c==EOF;}for(x=0;c<='9'&&c>='0'&&!_eof;c=Gc())x=x*10+(c&15),_eof|=c==EOF;x*=f;return*this;}
		template<class T>I&operator()(T*x,const int&n,const int&st=1){rep(i,st,n){operator()(x[i]);}return*this;}
	} in(stdin);
	struct O {
		char obuf[SZ],*oS=obuf,*oT=oS+SZ-1,qu[55];int f,qr;FILE*fi;
		O(FILE*f):fi(f){}
		~O(){Flush();}
		inline void Flush(){fwrite(obuf,1,oS-obuf,fi),oS=obuf;}
		inline O&operator()(char x){*oS++=x;if(oS==oT)Flush();return*this;}
		inline O&operator()(const char*s){int len=strlen(s);for(f=0;f<len;++f)operator()(s[f]);return*this;}
		template<class T>inline O&operator()(T x){if(!x)operator()('0');if(x<0)operator()('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)operator()(qu[qr--]);return*this;}
		template<class T>O&operator()(T*x,const int&n,const char&ed=' ',const int&st=1){rep(i,st,n)operator()(x[i])(ed);return*this;}
	} out(stdout);
}
using FastIO::in;using FastIO::out;
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e6+10;
const int mod=998244353;
inline int modd(int x){
	if(x>=mod)return x-mod;
	return x;
}
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
inline int inv(int x){
	return ksm(x,mod-2);
}
struct que{
	int x,w,s,id;
}q[N];
int cmp(que a,que b){
	return a.x<b.x;
}
int n,m,k,V,sum,a[N],b[N],s1[N],s2[N],Ans[N];
vector<int>e[N];
int f(int x,int y){
	return x*x*y%mod;
}
signed main()
{
//	freopen("025.in","r",stdin);
//	freopen("025.out","w",stdout);
	in(n)(m);
	for(int i=1;i<=n;i++){
		in(a[i])(b[i]);
		k+=a[i];
		V=max(V,b[i]);
		s1[a[i]]++;
		s2[b[i]]++;
		sum=modd(sum+a[i]*a[i]%mod);
	}
	for(int i=1;i<=m;i++){
		in(q[i].w);
		q[i].x=q[i].w-k;
		q[i].id=i;
		q[i].w%=mod;
	}
	sort(q+1,q+m+1,cmp);
	int pos=1,res=0,s=0;
	for(int i=0;i<=V;i++){
		while(pos<=m&&q[pos].x<=s+res){
			q[pos].s=(sum-f(i-1,q[pos].x-s)+f(i,q[pos].x-s)+mod)%mod;
			pos++;
		}
		s+=res;
		sum=modd(sum+res*(2*i-1)%mod);
		res+=s1[i]-s2[i]; 
	}
	int inv_n=inv(n);
	for(int i=1;i<=m;i++)
		Ans[q[i].id]=inv_n*(q[i].s-inv_n*q[i].w%mod*q[i].w%mod+mod)%mod;
	for(int i=1;i<=m;i++)
		out(Ans[i])('\n');
	return 0;
}
```

---

## 作者：ykzzldz (赞：2)

简单题，不懂为啥评蓝，评个黄得了。

这里默认大家都会方差的式子 $\frac{\sum x_i^2}{n}-(\frac{\sum x_i}{n})^2$，后面一项是固定的，题目即求 $\sum x_i^2$ 的最小值。首先，我们贪心地选取每个区间的左端点，此时还需要增大一些数，使得所有数之和达到题目的要求。

考虑将 $x-1$ 变为 $x$，对答案的增量为 $2x-1$，所以每次加最小的即可。实现时只要将询问离线下来双指针维护可加的数即可，复杂度为 $O(q\log q)$。

---

## 作者：Hanggoash (赞：2)

# P11037 【MX-X3-T4】「RiOI-4」上课

本文主要解释不断 $+1$ 的过程如何快速实现的具体流程。
## 题意
给定正整数 $n,q$ 和 $n$ 个区间 $[l_i,r_i]$ 。

有 $q$ 组询问，每次询问给定一个整数 $x$ 。在每个区间内选择一个整数 $a_i$（$l_i\leq a_i\leq r_i$），使得所选整数的总和等于 $x$ ，并使得选出的 $a$ 序列的方差最小。输出方差最小值，对 $998\,244\,353$ 取模。保证存在至少一种合法的选取方案。

## Solution

### 核心思想

最重要的一个式子，有点类似于高中时学回归方程的时候学过的 $\frac{\sum(x_i-\overline{x_i})^2}{\sum(y^2_i-\overline{y_i})^2}$ ，其中 ${\sum(x_i-\overline{x})^2}=\sum{x_i^2}-2\sum x_i\cdot{\overline x}+n\cdot \overline{x}^2=\sum{x_i^2}-2n\cdot \overline{x}^2+n\cdot \overline{x}^2$ ，也就是  $\sum{x_i^2}-n\cdot \overline{x}^2$ 。

所以本题中的方差可以变成 $\frac{\sum x_i^2}{n}-\overline x^2$ ，对于每一个询问的 $\overline x^2$  是固定的，所以要最小化的就是平方和 $\sum x_i^2$ ，为了达到这个目的很显然的一个贪心就是让所有 $a_i$ 取最小值 $l_i$ ，设此时他们的和为 $S_0$ ，那么我们还剩下 $x-S_0$ 的数值要分配给这些 $a_i$ ，那么只用把 $x-S_0$ 依次分配给最小的 $a_i$ 即可。

注意这里可能有理解上的偏差，并不能在排序过后按照  $l_1,l_2...l_n$ 的顺序依次将他们变成 $r_1,r_2...r_n$ ，直到不能操作为止，因为每次 $+1$ 之后最小值都有可能变化。而是应该取出每次给最小值  $a_{min}$ 加上 $1$ 之后的序列中的最小值 $a'_{min}$ 循环地动态进行该操作，否则就只能在 subtask1 上 AC 两个点。

按照该过程手玩一下样例就会发现这实际上类似于一个倒水的过程，拿样例一举个例子的话（红线为初始值），可以具象为如下模型：

![](https://cdn.luogu.com.cn/upload/image_hosting/h6xckrr1.png)

现在如果倒水进去，把最高液面的高度变为 $4$ ，也就相当于对 $a_i$ 们进行若干次操作后使得 $\max a_i=4$，就会变成这样 ：

![](https://cdn.luogu.com.cn/upload/image_hosting/hfhgs94g.png)

其中我们花费的代价为 $4$ ，也就是 $4$ 个红格子。

那在这个问题中，我们一共需要花费的代价是 $x-S_0$ ，很显然的是这个最后的最高高度是具有单调性的，也就是说总是存在一个 $h$ ，使得在花费完 $x-S_0$ 的代价后，最高液面 （最大的 $a_i$ ）能够达到 $h$ ，但无法达到 $h+1$ ，所以可以采取二分。（注意最高一层的液面不一定都能恰好取到最大值，因为“液面”高度是用整数而不是小数来衡量的，比如下图这种 $x-S_0=5$ 的情况）

![](https://cdn.luogu.com.cn/upload/image_hosting/c0d7a22g.png)

至于在二分内部的判断方式，我们可以定义一个 $sum[h]$ 数组，表示将所有 $l_i$ 提高到 $\min{(h,r_i)}$ 的代价，可以想到维护 $sum[h]$ 数组的方式就是根据 $[l_i,r_i]$ 依次在 $sum[h]$ 内进行区间内每个数 $+1$ 的操作 ，最后算出每个位置对应的值，再前缀和即可，可以在读入的时候就维护差分数组，再做两次前缀和的方式实现，不会的话请移步 P2367 。

### 统计答案

显然是不能够暴力枚举的，思考一下发现，如果我们现在算出了最大高度为 $h$ ：

​	对于 $r_i<h$ 的所有（显而易见，不可取等）区间 ：其对应的 $a_i$ 必取 $r_i$ ，对答案的贡献为 $r_i^2$ 。

​	对于 $h\le l_i$ 的所有（显而易见，可以取等）区间：其对应的 $a_i$ 必取 $l_i$ ，贡献为 $l_i^2$ 。

​	对于其他的所有区间：

​			其  $a_i$ 的可能取值为 $h$ 或 $h-1$ ，有 $sum[h]-(x-S_0)$ 个 $h-1$ ， $(x-S_0)-sum[h-1]$ 个 $h$ ，可以  $O(1)$ 地统计。

前两种情况可以定义 $Rans[h]$ 为高度为 $h$ 时，$\sum_i^{r_i<h} r_i^2$ 。 $Lans[h]$ 亦是如此。

由于一个 $r_i$ 可以对所有比它大的高度产生贡献，符合区间加的特性，所以同样可以用差分的方式预处理求出。

### 小细节 

涉及到逆元的最好开个 long long ，尤其是在模数比较大的情况下，任何可能会爆的地方最好都取个模。

然后由于 $sum[h],Lans[h],Rans[h]$ 的下标都对应的是高度而不是编号 ，所以枚举的时候应该是从 $L_{min}$ 到 $R_{max}$ 。

### Code

代码仅供参考，有些小地方的实现可能不同，不过不影响。

```c++
#include<bits/stdc++.h>
#define int long long
#define rr register 
using namespace std;
const int MOD=998244353;
template<typename T>inline void re(T &x)
{
	x=0;
	int f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}
template<typename T>inline void wr(T x)
{
	if(x>9)wr(x/10);
	putchar(x%10^48); 
}
inline int power(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)ans=ans*a%MOD;
		a=a*a%MOD;
		b/=2;
	}
	return ans%MOD;
}
const int N=1e6+10;
pair<int,int> q[N];
int sum[N],lsum[N],rsum[N],lcnt[N],rcnt[N];
int L=1e6+10,R=-1;
int n,tn,Q,S;
inline void add(int l,int r)
{
	sum[l]++,sum[r]--;
 } 
inline void pre()
{
	re(n),re(Q);	
	//sum
	for(rr int i=1;i<=n;++i)
				re(q[i].first),re(q[i].second),add(q[i].first,q[i].second),L=min(L,q[i].first),R=max(R,q[i].second),S+=q[i].first;		
	for(rr int i=L;i<=R;++i)sum[i]=sum[i-1]+sum[i];
	for(rr int i=L;i<=R;++i)sum[i]=sum[i-1]+sum[i];
	//cnt&sum_ans
	int l,r,tmp;
	for(rr int i=1;i<=n;++i)
	{
		l=q[i].first,r=q[i].second;
		rcnt[r+1]++,rcnt[R+1]--;
		lcnt[L]++,lcnt[l+1]--;
		tmp=l*l%MOD,lsum[L]=(lsum[L]+tmp)%MOD,lsum[l+1]=(lsum[l+1]-tmp+MOD)%MOD;
		tmp=r*r%MOD,rsum[r+1]=(rsum[r+1]+tmp)%MOD,rsum[R+1]=(rsum[R+1]-tmp+MOD)%MOD;
	}
	for(rr int i=L;i<=R;++i)
	{
		lcnt[i]+=lcnt[i-1],rcnt[i]+=rcnt[i-1];
		lsum[i]+=lsum[i-1],lsum[i]%=MOD;
		rsum[i]+=rsum[i-1],rsum[i]%=MOD;
	}
	//n^(-1)	
	tn=power(n,MOD-2);
}
//第一个大于等于 
inline int find(int x,int l,int r)
{
	if(l>=r)return l;
	int mid=(l+r)/2;
	if(sum[mid-1]>=x)return find(x,l,mid);
	else return find(x,mid+1,r);
}
inline int solve(int x)
{
	int ans1,ans2;
	int h=find(x-S,L,R);
	int res=n-rcnt[h]-lcnt[h],cnt=sum[h-1]-x+S;
	ans1=(rsum[h]+lsum[h])%MOD,ans1+=(h-1)*(h-1)%MOD*cnt%MOD+h*h%MOD*(res-cnt)%MOD,ans1=ans1%MOD*tn%MOD;
	ans2=(MOD-power(x%MOD,2)*power(tn,2)%MOD)%MOD;
	return (ans1+ans2)%MOD;
}
signed main()
{
	pre();
	int x;
	while(Q--)
	{
		re(x);
		wr(solve(x)),putchar('\n');
	}
	return 0;
}
```

---

## 作者：N0_1 (赞：2)

## 题意
给定 $n$ 个区间 $[L_i, R_i]$，和 $q$ 次询问 $x_i$，在**每个**区间中选择一个整数 $a_i$，满足 $\sum_{i=1}^n a_i = x$，求序列 $a$ 最小的方差值，结果对 $998 244 353$ 取模。数据保证有解。

## 思路
令 $n$ 倍的方差为 $\sum_{i=1}^n (a_i-\bar x)^2$，则有：$\sum_{i=1}^n (a_i-\bar x)^2 = \sum_{i=1}^n a_i^2 - n \bar x^2$，所以方差为 $\cfrac{\sum_{i=1}^n a_i^2 }{n}-\bar x^2$。则**题意转化为**求解最小的 $\sum_{i=1}^n a_i^2 $。

令一开始所有的 $a_{i}$ 均为 $L_i$，

若将某一个 $a_{i}-1$ 增加到 $a_i$，则 $\sum_{i=1}^n a_i^2 $ 增加 $a_i^2 - (a_i-1)^2$，即增加 $2\times a_i - 1$，一个显而易见的结论是每次将最小的 $a_{i} + 1$ 为最优情况。

离线查询所有的 $x_i$（**从小到大排序**），记当前的 $\sum_{i=1}^n a_i$ 为 $sum$，用双指针的思想**贪心**计算 $sum$ 增加到 $x_i$ 后 $\sum_{i=1}^n a_i^2 $ 的变化即可（前缀和预处理每个数的个数）。

[code](https://www.luogu.com.cn/paste/9yc9vwq7)

---

## 作者：meyi (赞：2)

怎么评蓝的？这样评蓝的。。。

首先简单推一下方差式子发现答案可以转化成 $\frac{\sum a_i^2}{n}-(\frac{x}{n})^2$，最小化这个等价于最小化 $\sum a_i^2$。

将区间按 $l_i$ 从小到大排序，初始所有 $a_i$ 都取 $l_i$，那么 $a_i$ 单调不降。显然当 $x$ 增大时 $a_i$ 的最小值也相应增大，不妨假设有多个最小值的时候增大最右边的，那么在任何时刻有 $a_i$ 单调不降。

由于每次增大的都是最小值，所以考虑被增大的这段区间，显然它是个前缀，在增大后这段前缀必定最多只剩两种数，于是势能增量是常数，可以用 `std::set` 甚至是个栈去进行前缀推平。

Q：但是还有 $r_i$ 的限制，怎么办？？？

A：别急，计算出最后剩的数是啥，如果 $r_i$ 不超过这个数那我干脆直接把 $a_i$ 拉满到 $r_i$，因为这样做一定不劣。然后删数的时候找第一个值不小于 $l_i$ 的区间并删个数就行，一定可以通过某些操作恰好令 $a_i$ 属于这个区间。然后如果你前面用栈维护的那么这里就哈哈了，所以必须得用 `std::set`。

Q：但是我不会算最后剩的是哪两种数怎么办？？？

A：别急，开两个值域树状数组，分别求前缀 $a_i$ 数量、前缀 $a_i$ 之和。那么将所有不超过 $k$ 的数增大到 $k$ 会让和增加 $k\times 不超过\ k\ 的\ a_i\ 数量\ -\ 不超过\ k\ 的\ a_i\ 之和$，也就是两个树状数组维护的东西。当前的和加上 $k$ 的贡献恰好不小于 $x_i$ 时，$k$ 就是要求的数，但是发现可能大于 $x_i$，所以还有一段前缀的值会是 $k-1$。

Q：但是 $k$ 咋求呢，直接二分不是 $\log^2$ 的吗？？？

A：别急，[P6619 [省选联考 2020 A/B 卷] 冰火战士](https://www.luogu.com.cn/problem/P6619)。

总时间复杂度 $O((n+q)\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#define ALL(v) v.begin(),v.end()
#define For(i,_) for(int i=0,i##end=_;i<i##end;++i) // [0,_)
#define FOR(i,_,__) for(int i=_,i##end=__;i<i##end;++i) // [_,__)
#define Rep(i,_) for(int i=(_)-1;i>=0;--i) // [0,_)
#define REP(i,_,__) for(int i=(__)-1,i##end=_;i>=i##end;--i) // [_,__)
typedef long long ll;
typedef unsigned long long ull;
#define V vector
#define pb push_back
#define pf push_front
#define qb pop_back
#define qf pop_front
#define eb emplace_back
typedef pair<ll,int> pli;
#define fi first
#define se second
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}},inf=0x3f3f3f3f,mod=998244353;
const ll infl=0x3f3f3f3f3f3f3f3fll;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
int init=[](){return cin.tie(nullptr)->sync_with_stdio(false),0;}();
static char pbuf[1000000],*p1=pbuf,*p2=pbuf,obuf[1000000],*o=obuf;
#define getchar() p1==p2&&(p2=(p1=pbuf)+fread(pbuf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (o-obuf<1000000)?(*o++=(x)):(fwrite(obuf,o-obuf,1,stdout),o=obuf,*o++=(x))
inline int qr(){
	int in=0;char ch;
	while(!isdigit(ch=getchar()));
	do in=(in<<1)+(in<<3)+(ch^48);while(isdigit(ch=getchar()));
	return in;
}
inline ll qrl(){
	ll in=0;char ch;
	while(!isdigit(ch=getchar()));
	do in=(in<<1)+(in<<3)+(ch^48);while(isdigit(ch=getchar()));
	return in;
}
template<class T>
void qw(T out){
	if(out>9)qw(out/10);
	putchar(out%10|48);
}
struct flusher{~flusher(){fwrite(obuf,o-obuf,1,stdout);}}autoflush;
struct pii{
    int fi;
    mutable int se;
    inline pii(int x=0,int y=0):fi(x),se(y){}
    inline bool operator<(const pii &rhs)const{return fi<rhs.fi;}
};
int main(){
    int t_case=1;
    //scanf("%d",&t_case);
    while(t_case--){
        int n=qr(),q=qr();
        auto qpow=[&](int x,int y){
            int z=1;
            for(;y;x=1ll*x*x%mod,y>>=1)if(y&1)z=1ll*z*x%mod;
            return z;
        };
        const int inv=qpow(n,mod-2);
        V<int>c1,l(n),r(n);
        V<ll>c2;
        int m=0;
        V<int>p(n);
        set<pii>s;
        ll sum=0;
        int sum2=0;
        auto ins=[&](int x,int y){
            ll xy=1ll*x*y;
            for(int i=x+1;i<=m;i+=i&-i)c1[i]+=y,c2[i]+=xy;
            auto it=s.lower_bound(x);
            if(it!=s.end()&&it->fi==x)it->se+=y;
            else it=s.insert(it,{x,y});
            sum+=xy;
            sum2=(sum2+xy%mod*x)%mod;
            return it;
        };
        auto insp=[&](set<pii>::iterator it,int x,int y){
            ll xy=1ll*x*y;
            for(int i=x+1;i<=m;i+=i&-i)c1[i]+=y,c2[i]+=xy;
            if(it!=s.end()&&it->fi==x)it->se+=y;
            else s.insert(it,{x,y});
            sum+=xy;
            sum2=(sum2+xy%mod*x)%mod;
        };
        {
            For(i,n)l[i]=qr(),ckmax(m,r[i]=qr());
            ++m;
            V<int>(m+1).swap(c1),V<ll>(m+1).swap(c2);
            V<int>id(n);
            iota(ALL(id),0);
            sort(ALL(id),[&](int x,int y){return l[x]<l[y];});
            For(i,n){
                int j=i+1;
                while(j<n&&l[id[i]]==l[id[j]])++j;
                int x=l[id[i]],y=j-i;
                ll xy=1ll*x*y;
                for(int i=x+1;i<=m;i+=i&-i)c1[i]+=y,c2[i]+=xy;
                s.insert(s.end(),{x,y});
                sum+=xy,sum2=(sum2+xy%mod*x)%mod;
                i=j-1;
            }
            iota(ALL(p),0);
            sort(ALL(p),[&](int x,int y){return r[x]>r[y];});
        }
        V<ll>x(q);
        For(i,q)x[i]=qrl();
        V<int>ans(q),id(q);
        iota(ALL(id),0);
        sort(ALL(id),[&](int u,int v){return x[u]<x[v];});
        int lg=__lg(m)+1;
        auto qry=[&](int k){
            int ret1=0;ll ret2=0;
            for(int i=k+1;i>=s.begin()->fi;i&=i-1)ret1+=c1[i],ret2+=c2[i];
            return 1ll*ret1*k-ret2;
        };
        for(int i:id){
            while(p.size()&&qry(r[p.back()]-1)<x[i]-sum){
                auto it=s.lower_bound(l[p.back()]);
                auto [x,y]=*it;
                for(int i=x+1;i<=m;i+=i&-i)--c1[i],c2[i]-=x;
                sum-=x,sum2=(sum2-1ll*x*x)%mod;
                if(sum2<0)sum2+=mod;
                if(y==1)s.erase(it);
                else --it->se;
                int R=r[p.back()];
                sum+=R,sum2=(sum2+1ll*R*R)%mod;
                p.qb();
            }
            if(sum<x[i]){
                int nw=0,tot1=0;
                ll tot2=0;
                Rep(j,lg){
                    int nxt=nw|(1<<j);
                    if(nxt<=m&&(nxt<=s.begin()->fi||1ll*(tot1+c1[nxt])*(nxt-1)-(tot2+c2[nxt])<x[i]-sum))nw=nxt,tot1+=c1[nw],tot2+=c2[nw];
                }
                tot1=tot2=0;
                for(int i=nw+1;i>=s.begin()->fi;i&=i-1)tot1+=c1[i],tot2+=c2[i];
                ll ex=1ll*tot1*nw-tot2-(x[i]-sum);
                assert(0<=ex&&ex<tot1);
                while(s.size()&&s.begin()->fi<=nw){
                    auto [x,y]=*s.begin();
                    ll xy=1ll*x*y;
                    for(int i=x+1;i<=m;i+=i&-i)c1[i]-=y,c2[i]-=xy;
                    sum-=xy,sum2=(sum2-xy%mod*x)%mod;
                    if(sum2<0)sum2+=mod;
                    s.erase(s.begin());
                }
                if(ex)insp(next(ins(nw-1,ex)),nw,tot1-ex);
                else ins(nw,tot1-ex);
            }
            ans[i]=sum2;
        }
        For(i,q)qw((ans[i]+mod-(x[i]%mod)*(x[i]%mod)%mod*inv%mod)*inv%mod),putchar(10);
    }
    return 0;
}
/*
(sum (ai-avg)^2)/n=(sum (ai^2-2*avg*ai+avg^2))/n=(sum ai^2)/n-avg^2
本质就是求最小平方和
将区间按l从小到大排序，将总和增加看成倒水，令没到r的数不降，那么一次操作会将一个前缀推平成两个区间
这个东西可以用栈或珂朵莉树维护
开两个大小为max ri的树状数组，分别表示前缀数量和前缀和
每次判断会不会有数到最小的 ri，如果有的话直接给 i 加到 ri 并且丢掉就行，找到第一个 >= li 的区间然后丢
这个丢掉是栈没法做的，所以要用珂朵莉树
然后树状数组上二分就行
*/
```

你可能发现了这份代码里有很多抽象操作，这是因为倪潤東大帝使用 400iq 之力开了 1s 的时限导致哥们卡了一整页常才卡过，同时喜提最劣解，尽管这份代码是单 $\log$ 的。。。@[听取MLE声一片](https://www.luogu.com.cn/user/253738) 我澡称冯福的。

---

## 作者：strcmp (赞：1)

感觉看到题马上就会了，但场切的人（对比难度）有点少的说。

有 $n$ 个整数的序列 $a$，方差乘以 $n^2$ 是 $n \times \left(\sum\limits_{i=1}^na_i^2\right) - \left(\sum\limits_{i=1}^na_i\right)^2$，证明略，想看证明可以去 P7962，这是典中典结论了。

因为总和和长度固定，于是问题自然而然变成了最小化选出数的平方和。

注意到我们不能每次都贪心取 $l_i$ 的原因就是，总和必须等于 $x$。

但这也启发我们先全部取 $l_i$，然后贪心调整，称当前进行贪心调整的序列为 $b$ 序列。

平方和显然是互相独立的，因此可以贪心。考虑 $f(x) = x^2$ 的斜率单调递增，肯定考虑从最小的数开始增加调整。

初始钦定 $b_i = l_i$，咱考虑每次取最小的 $b_i$ 让它加一，让答案加上 $2b_i + 1$，当然前提是 $b_i \ne r_i$。

不妨枚举 $\min b = y$，当然这里能算进 $\min$ 的前提是没有顶到上界。同时维护 $y$ 的出现次数 $c$。对 $l_i$ 标记加一，对 $r_i$ 标记减一。然后每次根据 $x$ 判断能否使得全部 $b_i = y$ 且没顶上界的数加一。然后让 $x$ 减。

发现至少是 $\Theta(qv)$ 的复杂度，$v$ 是值域为 $10^6$。

过不了，怎么办。

然后你发现可以将 $x$ 排序离线下来，维护一个减法标记，每次就不用重新算前面的部分了。

时间复杂度 $\Theta(q \log q + v)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define X first
#define Y second
using namespace std;
typedef long long int ll;
using pli = pair<ll, int>;
constexpr int maxn = 1e6 + 10, inf = 1e9, mod = 998244353;
inline ll ksm(ll a, int b = mod - 2) {
	ll ls = 1;
	while (b) {
		if (b & 1) ls = ls * a % mod;
		a = a * a % mod; b >>= 1;
	}
	return ls;
}
int n, Q, l[maxn], r[maxn], c[maxn], mi = 1e9, mx = 0; pli a[maxn]; ll ans[maxn], len[maxn];
int main() {
    scanf("%d%d", &n, &Q); ll rev = ksm((ll)n * n % mod); ll now = 0, s = 0;
    for (int i = 1; i <= n; i++) scanf("%d%d", &l[i], &r[i]), mx = max(mx, r[i]), mi = min(mi, l[i]), ++c[l[i]], --c[r[i]], s += l[i], now = (now + (ll)l[i] * l[i] % mod) % mod;
    for (int i = 1; i <= Q; i++) scanf("%lld", &a[i].X), len[i] = a[i].X % mod, a[i].Y = i; a[Q + 1].X = 1e18;
    sort(a + 1, a + Q + 1); int p = 1; 
    for (int i = mi; i <= mx; i++) {
    	c[i] += c[i - 1];
    	while (a[p].X - s <= c[i]) ans[a[p].Y] = (now + (2LL * i + 1) * (a[p].X - s) % mod) % mod, ++p;
    	now = (now + (2LL * i + 1) * c[i] % mod) % mod; s += c[i];	
	}
	for (int i = 1; i <= Q; i++) printf("%lld\n", (ans[i] * n % mod - len[i] * len[i] % mod + mod) % mod * rev % mod); 
    return 0;
}
```

---

## 作者：SFlyer (赞：1)

首先推柿子，发现方差等于 $\frac{a_1^2+a_2^2+\cdots +a_n^2}{n}+\frac{\sum^2 a_i}{n^2}$。第二项是定的，所以优化第一项。

$22$ 分很简单，直接优先队列维护即可，每一次给最小的没有到达 $r$ 的数加一。

尝试优化这个过程。发现其实过程被 $l_i,r_i$ 分成了 $\mathcal{O}(n)$ 个段，每一个段内是一个相同的集合内的数在轮流加一。这个我们直接离散化一下就可以了。

```c++
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e6+6;
const ll mod = 998244353;

ll pw(ll x,ll y){
	ll res=1;
	while (y){
		if (y&1){
			res=res*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return res;
}

struct node {
	ll l,r;
} a[N];

ll n,Q;
ll qys[N],vis[N];

struct quy {
	ll x,id;
	bool operator < (const quy &y) const {
		return x<y.x;
	}
} ac[N];

ll cal(ll cur,ll x){
	ll res=(cur+mod)%mod;
	res=res*pw(n,mod-2)%mod;
	x%=mod;
	res=(res-x%mod*(x%mod)%mod*pw(n*n%mod,mod-2)%mod)%mod;
	return (res+mod)%mod;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>Q;
	vector<ll> v;
	for (int i=1; i<=n; i++){
		cin>>a[i].l>>a[i].r;
		vis[a[i].l]++;
		vis[a[i].r]--;
		v.push_back(a[i].l);
		v.push_back(a[i].r);
	}
	for (int i=1; i<=Q; i++){
		ll x;
		cin>>x;
		ac[i]={x,i};
	}
	sort(ac+1,ac+1+Q);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	ll ans=0,sum=0,cnt=0,pos=1;
	for (int i=1; i<=n; i++){
		sum+=a[i].l;
		ans+=a[i].l*a[i].l;
	}
	for (int i=0; i+1<v.size(); i++){
		cnt+=vis[v[i]];
		ll len=v[i+1]-v[i];
		ll ad=cnt*(v[i+1]-v[i]);
		while (pos<=Q && ac[pos].x>=sum && ac[pos].x<=sum+ad){
			ll it=ans;
			ll nd=ac[pos].x-sum;
			ll md=nd/cnt,r=nd%cnt;
			md+=v[i];
			md%=mod;
			it=it+md*md%mod*(cnt-r)%mod+(md+1)*(md+1)%mod*r%mod;
			it=it-v[i]*v[i]%mod*cnt%mod;
			it%=mod;
			qys[ac[pos].id]=cal(it,ac[pos].x);
			pos++;
		}
		sum+=ad;
		ans+=cnt*((v[i+1])*(v[i+1])-v[i]*v[i]);
	}
	for (int i=1; i<=Q; i++){
		cout<<qys[i]<<"\n";
	}
	return 0;
}
```

---

## 作者：Xiphi (赞：0)

一种比 std 好理解但是码量略大的算法。另外感觉 B>>>>C。

首先我们观察方差的定义，感性理解一下就是所有数尽量接近其平均数。容易发现平均数对于每个询问是固定的。

我们想到对于每个询问二分一个数 $z$，然后根据这个 $z$ 构造出一个 $a$ 数组，对于每个区间，若其包含 $z$，则该 $a_i$ 等于 $z$；若其左端点大于 $z$，$a_i$ 等于其左端点；若其右端点小于 $z$，则 $a_i$ 等于其右端点。设这个二分出来的 $z$ 的“值”为所有 $a_i$ 的和，设其为 $s$。不难证明 $s$ 随着 $z$ 的增大单调递增。

我们发现，对于这样构造出的 $a$ 数组，**如果** 询问所有 $a_i$ 和为 $s$ 的答案最小如何构造，那此时的构造一定不劣。 

我们二分出 $x \le s$ 的最小的 $s$ 和其对应的 $z$。现在我们要做的就是把当前构造出的 $a$ 数组所有数之和调整到 $x$。我们发现题目中保证 $x$ 是可以构造出的，也就是说，我们一定可以只通过将包含 $z$ 的区间中，若干个不同 $i$ 对应 $a_i$ 的值减一达到 $x$。

这样题目就变得简单了，我们直接算出一个数减一的对应贡献然后将它成上 $s-x$ 即可。

接下来的问题就变成了如果快速求一个 $z$ 的对应贡献，由于域值很小，我们直接预处理即可。至于具体需要预处理什么，读者自想不难。

代码直接引用了 [happybob](/user/332914) 的[实现](https://www.luogu.com.cn/paste/9imdda4x)。happybob Orz。

---

## 作者：DerrickLo (赞：0)

先将方差的式子拆成 $\displaystyle{\frac{1}{n^2}((\sum_{i=1}^{n}a_i^2)\times n-(\sum_{i=1}^{n}a_i)^2)}$，你注意到 $\displaystyle{\sum_{i=1}^{n}a_i}$ 是给定的，所以也就是要求 $\displaystyle{\sum_{i=1}^{n}a_i^2}$ 的最小值。

然后你考虑暴力做法。先将每个 $a_i$ 初始化成 $l_i$ 然后每次贪心地将当前最小的那个 $a_i$ 加上 $1$，一直加到总和 $=x$ 就是答案了。

然后你发现这样的操作在很多时候都可以看成将若干个 $a_i$ 集体加上 $1$，只有某个 $a_i$ 加不了的时候或者某个 $a_i$ 新加进来的时候才会发生改变。那么你先将所有询问排个序后就只考虑改变的这些点，只需要维护目前 $a_i$ 的最小值、最小值个数、目前的平方和、目前的和即可。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,m,l[2000005],r[2000005],x[2000005],cnt,ans[2000005],now=1,cntt,num,sum,sum2;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
struct query{
	int x,id;
	friend bool operator<(const query&a,const query&b){
		return a.x<b.x;
	}
}q[2000005];
struct nd{
	int x,op;
	friend bool operator<(const nd&a,const nd&b){
		return a.x<b.x;
	}
}a[2000005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i],a[++cnt]={l[i],1},a[++cnt]={r[i],-1};
	sort(a+1,a+cnt+1);
	for(int i=1;i<=m;i++)cin>>q[i].x,q[i].id=i,x[i]=q[i].x;
	sort(q+1,q+m+1);
	for(int i=1;i<=n;i++)sum+=l[i]*l[i],sum2+=l[i];
	for(int i=1;i<=cnt;i++){
		while(now<=n&&q[now].x>=sum2&&q[now].x<=sum2+cntt*(a[i].x-a[i-1].x)){
			if(cntt==0){
				ans[q[now].id]=sum,now++;
				continue;
			}
			int aa=(q[now].x-sum2)/cntt,bb=(q[now].x-sum2)%cntt;
			ans[q[now].id]=sum+bb*((num+aa+1)*(num+aa+1)-num*num)+(cntt-bb)*((num+aa)*(num+aa)-num*num);
			now++;
		}
		sum+=cntt*(a[i].x*a[i].x-num*num),sum2+=cntt*(a[i].x-num),num=a[i].x;
		if(a[i].op==1)cntt++;
		else cntt--;
	}
	for(int i=1;i<=m;i++)ans[i]%=mod;
	for(int i=1;i<=m;i++)cout<<(ans[i]*n%mod-(x[i]%mod)*(x[i]%mod)%mod+mod)%mod*ksm(n,mod-2)%mod*ksm(n,mod-2)%mod<<"\n";
}
```

---

## 作者：sgl654321 (赞：0)

## 题目大意

- 给定 $n$ 个区间，$q$ 次询问，每次给定一个数 $x$。

- 你需要在这 $n$ 个区间中，每个区间选一个数，使得这些数的和恰好为 $x$。
- 在此基础上，最小化选出的 $n$ 个数的方差。输出方差最小值。

## 解题思路

### 化简代数式

方差的定义式为 $s ^ 2 = \dfrac{1}{n}\sum(a_i-\bar{a})^2$，将平方展开之后我们就有：

$s^2 = \dfrac{\sum a_i^2 -2\bar{a}\sum a_i + n\times \bar{a}^2}{n}$。

而在本题中 $\sum a_i = x$，$\bar{a} = \dfrac{x}{n}$。容易发现方差式子的大小只与 $\sum a_i^2$ 这一项有关。且这个东西越小，方差越小。

### 考虑选择方案

如果 $x = \sum l_i$ 那么显然就是全选 $l_i$，没有任何其他情况。但如果 $x$ 变得更大了呢？

可以证明，每次我们把尽量小的数自增 $1$，这样可以保证最后的方差一定最小。

为什么呢？分析其正确性。我们想要让 $\sum a_i^2$ 尽可能小。如果你把 $a_i$ 变成了 $a_i + 1$，那么这个平方和就增大了 $2\times a_i + 1$。所以你选择自增的 $a_i$ 越小，你的 $\sum a_i ^2$ 也就增大的越少。

因此，设 $del  = x - \sum l_i$，我们只需要按照如上步骤自增 $del$ 次，同时处理方差即可。

这样我们如果暴力去这样自增的话，时间复杂度可以到达 $O(qx)$。非常恐怖。

### 优化自增过程

但是我们发现，假设当前序列是 $\{1,1,1,1,1,2\}$，你如果不把所有 $1$ 都先变成 $2$，你是不会特意去把 $2$ 变成 $3$ 的。

因此容易想到处理出把 $i$ 变成 $i + 1$ 的可行的数的个数，记录为 $b_i$。对于每一个区间 $[l,r]$，我们都把这个区间的 $b_i(i\in[l,r])$ 统一加上 $1$ 即可。同时处理出 $b_i$ 的前缀和数组 $s_i$。

然后我们在 $b_i$ 内进行二分，看看 $s_{mid}$ 是否小于你要自增的值 $del$。我们找到最后一个小于 $del$ 的 $s_{mid}$。这就意味着，我们先会把小于等于 $mid$ 的数都自增到 $\min(r_i, mid + 1)$，之后你还会剩下 $del - s_{mid}$ 步，是你还要把一些 $mid + 1$ 变成 $mid + 2$ 的步数。

这样我们就用一个 $O(\log V)$ 的二分代替了暴力自增的过程。

另外，我们如何处理出平方和的变化呢？我们可以令 $d_i = b_i \times (i \times 2 + 1)$，表示把所有可行的 $i$ 变为 $i + 1$ 平方和会增大多少。初始时，平方和为 $\sum l_i^2$。你二分的结果是 $mid$，这意味着你的平方和增大了 $\sum_{j = 1}^{mid} d_i$。最后我们还有 $del - s_{mid}$ 步用来把 $mid + 1$ 变为 $mid + 2$，那你再把平方和加上 $(del - s_{mid})\times (2 \times (mid + 1) + 1)$ 这样即可。

求出了最小的平方和，在套入计算方差的那个代数式，我们就可以输出最后的答案了。

### 注意点

注意到输入的 $x$ 最大会达到 $10^{12}$ 级别。我们不能直接将 $x$ 取模，否则 $del$ 的计算以及二分的过程会受到影响。

但是如果你不把 $x$ 取模，你在使用逆元求解 $\bar{a} = \dfrac{x}{n}$ 就可能会爆 `long long`。笔者就被这一点给坑了。

所以说，这题取模与否，取模是否及时都是实现的关键之处，务必注意。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
#define endl '\n'
using namespace std;
typedef long long ll;
const ll mod = 998244353;
struct node{
	ll l, r;
} a[maxn];
ll n, q, b[maxn], x, xba, now, sta, s[maxn], ans, sta2, ivn, s2[maxn], l, r, mid, pos, del;
ll now2;

ll qpow(ll x, ll y){
	ll ret = 1;
	while(y){
		if(y & 1) ret = ret * x % mod;
		x = x * x % mod; 
		y >>= 1;
	} return ret;
}
ll inv(ll x){return qpow(x, mod - 2);}
ll work(ll tmp, ll ba, ll sum){
	tmp %= mod; ba %= mod; sum %= mod;
	ll ret = tmp - 2 * ba % mod * sum % mod + ba * ba % mod * n % mod;
	ret = (ret % mod + mod) % mod;
	ret = ret * inv(n) % mod;
	return ret;
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> q; 
	for(int i = 1; i <= n; i++) 
		cin >> a[i].l >> a[i].r, b[a[i].l] ++, b[a[i].r]--, sta += a[i].l,
		sta2 += a[i].l * a[i].l % mod, sta2 %= mod;
	for(int i = 1; i <= 1e6 + 5; i++) b[i] += b[i - 1], s[i] = s[i - 1] + b[i];
	for(int i = 1; i <= 1e6 + 5; i++)
		s2[i] = s2[i - 1] + b[i] * (2 * i + 1) % mod, s2[i] %= mod; 
//	for(int i = 1; i <= 10; i++) cout << s[i] << ' ';
//	cout << endl;
	
	while(q--){
		cin >> x; xba = x % mod * inv(n) % mod;
		if(x == sta){
			cout << work(sta2, xba, x) << endl;
			continue;
		}
		del = x - sta;
		
		l = 1; r = 1e6 + 5; pos = 0;
		while(l <= r){
			mid = (l + r) >> 1;
			if(s[mid] <= del) pos = mid, l = mid + 1;
			else r = mid - 1;
		}
		now2 = sta2 + s2[pos]; now2 %= mod; 
		// b[pos + 1] 是你这个位置还能加的数的个数，你现在还需要加 del - s[pos] 个数。 
		now2 += (del - s[pos] ) * (2 * (pos + 1) + 1) % mod; now2 %= mod;
		cout << work(now2, xba, x) << endl;
	}
	

	return 0;
}

```

---

## 作者：xiaoliebao1115 (赞：0)

方差套路题，简单推式子。
$$\mu=\frac{1}{n}\sum\limits_{i=1}^{n} a_i$$
$$s^2=\frac{1}{n}\sum\limits_{i=1}^{n} (a_i-\mu)^2$$
$$s^2=\frac{1}{n}\sum\limits_{i=1}^{n}(a_i^2-2\times a_i\times \mu+\mu^2)$$
$$s^2=\frac{1}{n}\sum\limits_{i=1}^{n}a_i^2-\frac{2\times\mu}{n}\times\sum\limits_{i=1}^{n}a_i+\mu^2$$
由于 $\sum\limits_{i=1}^{n}a_i=\mu\times n$，所以有下面式子。
$$s^2=\frac{1}{n}\sum\limits_{i=1}^{n}a_i^2-\mu^2$$
所以我们可以把 $x$ 排序，然后每次把最小的加 $1$。

按照这样的顺序，所有的 $l$ 和 $r$ 会把所有的分成 $O(n)$ 段，每一段可加的都是一样的，可以轮流对这些数加，可以进行离散化处理，代码不是很好写。

---

## 作者：02Ljh (赞：0)

### [$P_{11037}$](https://www.luogu.com.cn/problem/P11037)

~~赛时唐完了秒 b 然后这题死活不会~~

直接对着 $x$ 不好贪心构造方案，那么考虑先找到一个 $x$ 最优的方案，根据询问的 $x$ 不同调整。

那么不妨钦定最初的 $x=\sum l$，是最小的可能值，方案也只有一种。那么每次向上推 $x$ 要在最小的值上加一（不超过 $r$）。这样时间会炸，考虑推很多次可以浓缩为让一行的值只要在 $l,r$ 范围内的都 $+1$，可以差分求出有对于固定的值能推动多少个。推的时候显然可以拆一下方差维护，是 $O(\max r)$ 的。

对于每次询问，我们可以二分在那两个推层之间，然后把上一个比他小的推层的一部分加上一维护方差即可。

实现时注意差分不能把 $l_i$ 计算到因为本来的选值就是 $l_i$ 相当于没推，另外 $\sum l$ 不能取模，但是在乘上别的东西（如算平均的 $n$ 的逆元）前要取模。

```cpp
// 前を向け 終わらないさ 
// 一生僕らは生きて征け
#include <bits/stdc++.h>
using namespace std;
#define INF 100000000001
#define ull unsigned long long
#define ll long long
#define WA cerr<<"meowww!\n";
#define eps 1e-5
#define none -1145141919
#define pii pair<int,int>
#define Y cout<<"Yes\n";
#define N cout<<"No\n";
#define H cout<<"\n";
#define WH cerr<<"\n";
#define fi first
#define se second
#define C continue;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
#define ROF(i,a,b) for(int i=(a);i>(b);--i)
#define G(i,p) for(auto i:pq[p])
#define VG(i,p) for(int i=0;i<pq[p].size();i++)
#define pb push_back
#define pk pop_back
#define WR(x) cerr<<(x)<<"\n";
#define MAXN 2000001
#define int long long
const int MOD=998244353;
void MD(int &x) { x%=MOD; if(x<0) x+=MOD; if(x>=MOD) x%=MOD; return ; }
void Umn(int &x,int y) { if(x>y) x=y; return ; }
void Umx(int &x,int y) { if(x<y) x=y; return ; }
int n,q; pii a[MAXN];  int tg[MAXN],ef[MAXN]; int m=0;
int avg[MAXN],vl[MAXN]; int bx[MAXN];
int ksm(int x,int y) { int rt=1; 
while(y) { rt=(y%2)?(rt*x%MOD):(rt); x=x*x%MOD; y>>=1; } return rt%MOD; }
int ny;
int st=INF;
struct upd{int sum,ag,val;};
upd Upd(upd x,int num,int an)
{
    upd rt;
    rt.sum=x.sum+num; rt.ag=((x.ag*n)%MOD+num)%MOD*ny%MOD;
    rt.val=x.val+(num*((2*(an-1)%MOD+1-2*(x.ag)%MOD+MOD)%MOD)%MOD)%MOD*ny%MOD;
    MD(rt.val);
    rt.val+=((rt.sum*2%MOD-((x.ag+rt.ag)%MOD*n%MOD)%MOD+MOD)%MOD)%MOD*(x.ag-rt.ag+MOD)%MOD*ny%MOD;
    MD(rt.val);
    return rt;
}
int qans(int x)
{
    int ps=lower_bound(ef,ef+m-st+1,x)-ef;
    if(ef[ps]>x) --ps; //WR(ef[ps]);
    assert(ps+st+1>=0&&x-ef[ps]>=0&&ps>=0);
    upd tp=Upd({ef[ps],avg[ps],vl[ps]},x-ef[ps],ps+st+1);
    return tp.val;
}
 main()
{
    //freopen("in2.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin>>n>>q; ny=ksm(n,MOD-2); For(i,1,n) { cin>>a[i].fi>>a[i].se; Umn(st,a[i].fi); 
    ef[0]+=a[i].fi; Umx(m,a[i].se); tg[a[i].fi+1]++,tg[a[i].se+1]--; }
    For(i,0,m) tg[i]+=tg[i-1];
    avg[0]=ef[0]%MOD*ny%MOD; For(i,1,n) { int kk=abs(a[i].fi-avg[0])%MOD; vl[0]+=(kk*kk)%MOD; MD(vl[0]); }
    vl[0]=(vl[0]*ny)%MOD;
    int PP=numeric_limits<long long>::max();
    For(i,1,m-st) { 
        upd t=Upd({ef[i-1],avg[i-1],vl[i-1]},tg[i+st],i+st);
        ef[i]=t.sum,avg[i]=t.ag,vl[i]=t.val;
    }    
    For(i,1,q) { int p; cin>>p; cout<<qans(p)%MOD<<"\n"; }
    return 0;
}
/*
Need check before submit

1.INF=1e9 check if the val>=1e9 and only 0x3f3f3f3f and 0 can be memset!!!
2.Don't using getchar() unless is NESSASARY!!!
3.Enough size for the array!!!
4.Notice double's precision
5.CHECK UR LL OR ULL!!!
6.READ THE PROBLEM AGAIN AND AGAIN!!!
7.Check if for() is over int

*/
```

---

