# Résumé Review

## 题目描述

Uh oh! Applications to tech companies are due soon, and you've been procrastinating by doing contests instead! (Let's pretend for now that it is actually possible to get a job in these uncertain times.)

You have completed many programming projects. In fact, there are exactly $ n $ types of programming projects, and you have completed $ a_i $ projects of type $ i $ . Your résumé has limited space, but you want to carefully choose them in such a way that maximizes your chances of getting hired.

You want to include several projects of the same type to emphasize your expertise, but you also don't want to include so many that the low-quality projects start slipping in. Specifically, you determine the following quantity to be a good indicator of your chances of getting hired:

 $ $$$ f(b_1,\ldots,b_n)=\sum\limits_{i=1}^n b_i(a_i-b_i^2).  $ $ </p>     <p>Here,  $ b\_i $  denotes the number of projects of type  $ i $        you include in your résumé. Of course, you cannot include more       projects than you have completed, so you require  $ 0\\le b\_i \\le a\_i $  for all  $ i $ .</p>     <p>Your résumé only has enough room for  $ k $  projects, and you       will absolutely not be hired if your résumé has empty space, so       you require  $ \\sum\\limits\_{i=1}^n b\_i=k $ .</p>     <p>Find values for  $ b\_1,\\ldots, b\_n $  that maximize the value of        $ f(b\_1,\\ldots,b\_n)$$$ while satisfying the above two constraints.

## 说明/提示

For the first test, the optimal answer is $ f=-269 $ . Note that a larger $ f $ value is possible if we ignored the constraint $ \sum\limits_{i=1}^n b_i=k $ .

For the second test, the optimal answer is $ f=9 $ .

## 样例 #1

### 输入

```
10 32
1 2 3 4 5 5 5 5 5 5```

### 输出

```
1 2 3 3 3 4 4 4 4 4```

## 样例 #2

### 输入

```
5 8
4 4 8 2 1```

### 输出

```
2 2 2 1 1```

# 题解

## 作者：Karry5307 (赞：9)

### 题意

给定一个长度为 $n$ 的序列 $a$ 和一个整数 $k$，构造一个序列 $b$ 使得满足以下条件：

- $0\leq b_i\leq a_i$

- $\sum\limits_{i=1}^{n}b_i=k$

最大化 $\sum\limits_{i=1}^{n}a_ib_i-b_i^3$。

$\texttt{Data Range:}n\leq 10^5,k\leq 10^{14}$

### 题解

[不一定更好的阅读体验](https://www.cnblogs.com/Karry5307/p/13731799.html)

神仙题。

考虑先设 $b_i$ 为 $0$，相当于能操作 $k$ 次，每次能把某个 $b_i+1$。

考虑设 $f(i,x)=a_ix-x^3$，那么我们有

$$\Delta f(i,x)=a_i-3x^2+3x-1$$

注意到这东西在整数域上是单调递减的，于是可以按照求最大函数值的那个套路来，但是时间复杂度是 $O(k\log n)$ 的，无法通过。

注意到我们取出来的最大函数值值是单调不升的，所以可以考虑二分一下最后一次操作对答案的贡献是什么。对于当前考虑的值我们可以通过二分来解一下某个 $i$ 至少需要操作几次才能大于等于这个最大增量，最后 check 一下 $\sum b_i$ 就好了。

然后由于最大函数值单调不升而不是单调递减，所以外面的二分最好不要二分到一个确切的值，而是二分到一个长度为 $2$ 的区间，然后在 check 两个端点。

这样子可能有些时候操作次数还有剩余，于是就可以最后调整一下值就差不多了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=2e5+51,inf=1e18;
ll n,kk,l,r,mid,sm;
ll u[MAXN],v[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll f(ll u,ll x)
{
	return u==x?inf:u-3*x*x+3*x-1;
}
inline ll calc(ll x,ll lim)
{
	ll l=1,r=u[x],mid,res=u[x];
	while(l<=r)
	{
		mid=(l+r)>>1;
		f(u[x],mid)<=lim?r=mid-1,res=mid:l=mid+1;
	}
	return res;
}
inline ll check(ll mid)
{
	sm=0;
	for(register int i=1;i<=n;i++)
	{
		sm+=(v[i]=calc(i,mid));
	}
	return sm<kk;
}
int main()
{
	n=read(),kk=read();
	for(register int i=1;i<=n;i++)
	{
		u[i]=read(),l=min(l,f(u[i],u[i]-1)),r=max(r,f(u[i],0));
	}
	while(r-l>=2)
	{
		mid=(l+r)>>1;
		check(mid)?r=mid:l=mid;
	}
	r=check(l)?l:r,check(r),kk-=sm;
	for(register int i=1;i<=n;i++)
	{
		kk&&v[i]<u[i]&&f(u[i],v[i])==r?v[i]++,kk--:1;
	}
	for(register int i=1;i<=n;i++)
	{
		printf("%lld ",v[i]);
	}
}
```

---

## 作者：MatrixCascade (赞：8)

读完题：[这俩真的不是同一道题？](https://www.luogu.com.cn/problem/CF1661F)

定义 $f(x,i)=a_i\times x-x^3$，显然这是一个凸函数，也就意味着导数是单调的。

再定义 $g(x,i)=f(x,i)-f(x,i-1)$，导数单调因此得出 $g$ 这个函数是单减的，然后就可以用优先队列贪心的去一个一个加，先默认全取 $0$，然后堆里存 $g(x,i)$，每次取出最小的那个出队，再把 $g(x+1,i)$ 入队，直到取到 $k$ 个，但这样的复杂度是 $O(k\log n)$ 的，显然没法通过。  
我们考虑优化，先二分一个值 $t$，代表对于每一个 $i$，$g(b_i,i)\ge t$，考虑内层 check，就是要求出每一个 $i$ 的最大 $b_i$，使得 $g(b_i,i)\ge t$，由于凸性，内层找 $b$ 的过程可以再用一个二分去优化复杂度。算出每个 $b_i$ 后求个和，然后去和要求的 $k$ 作比较，找出使得 $\sum b_i\le k$ 的最大 $t$ 值即可。

由于你求的是 $\le k$ 的最大 $t$ 值，所以你的 $\sum b_i$ 有可能没到 $k$，因此你得先求出 $t-1$ 的 $\sum b_i$ 值，这个值一定是大于等于 $k$ 的，求完之后再对于当前每一项的 $b$ 去调整即可。（具体的，你需要对于每个 $i$ 求出 $g(x,i)=t$ 的 $x$ 的数量，这个可以用两次二分实现）  
复杂度 $O(n\log ^2 V)$

[代码](https://codeforces.com/contest/1344/submission/154840022)

---

## 作者：tommymio (赞：6)

> 一个长度为 $n$ 的数组 $a_i$，构造 **自然数** 数组满足：
>
> - $\forall i,b_i\in[0,a_i]$.
> - $\sum_{i=1}^n b_i=k$
>
> 在这个前提下，求令 $\sum_{i=1}^n b_i(a_i-b_i^2)$ 达到最大值的任意一组 $b_i$.

首先很容易想到暴力，设 $b_i$ 的值为 $x$ ，则 $b_i$ 增加 $1$ 对答案新增的贡献为 $\Delta_i=(x+1)\left(a_i-(x-1^2)\right)-x(a_i-x^2)=a_i-3x^2+3x-1$。

那么，初始时设所有 $b_i$ 都为 $0$ ，用一个堆维护，每次从堆中取出 $\Delta_i$ 最大的 $b_i$ 加 $1$，并记录下 $b_i$ ，最后得到的 $b_i$ 就是题目所求的 $b_i$ 。时间复杂度为 $O(k \log n)$，显然不能承受。

观察上述过程，我们发现在暴力过程中，由于每次都采取当前的最优策略，所以对于任意的 $y$，第 $y$ 次增加的值是 **固定的** ，并且是单调递减的。那么这样的一个增量便具有了单调性。

对于一个 $\Delta_i$，我们知道如果取这个 $i$ 把它对应的 $b_i$ 加 $1$，意味着其他位置上的 $\Delta$ 值并不会大于 $\Delta_i$，也就是说我们可以根据这个 $\Delta_i$ ，大概确定出所有的 $b_i$。我们称这个 $\Delta_i$ 为最大增量.

由于满足单调性，最大增量可以被二分出来，$\text{check}$ 函数也非常简单，根据最大增量求出每个 $b_i$ ，判断 $\sum_{i=1}^n b_i$ 是否大于 $k$ 即可。至于求 $b_i$ 的过程可以解方程，也可以直接二分，前者可以近似认为是 $O(n \log maxVal)$，而后者则是 $O(n \log^2 maxVal)$。

值得一提的是，由于最大增量 **非严格单调递减** ，以及二分后求出的 $b_i$ 不一定满足 $\sum b_i=k$ 的约束，我们规定二分求出的 $b_i$ 满足 $\sum b_i\leq k$，并且二分求出的 $\Delta$ 不是一个值，是一个长度为 $2$ 的区间，对边界进行控制，这样就不会遗漏任何情况。

**Show the Code**
```cpp
#include<cstdio>
#include<climits>
#define max(a,b) ((a)>(b)? (a):(b))
#define min(a,b) ((a)<(b)? (a):(b))
typedef long long ll;
ll n,m,sum=0;
ll a[100005],b[100005];
inline ll read() {
    register ll x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
//-3*y^2+3*y+x-1=-3(y-(1/2))^2+...
inline ll f(ll x,ll y) {return x==y? LLONG_MAX:x-3*y*(y-1)-1;}//对称轴x=1/2
inline ll calc(ll x,ll lim) {//f(a[x],b[x])<=lim
    ll l=1,r=a[x],res=a[x];
    while(l<=r) {
        int mid=l+r>>1;
        if(f(a[x],mid)<=lim) {r=mid-1;res=mid;}
        else {l=mid+1;} 
    }
    return res;
}
inline bool check(ll x) {
    sum=0;
    for(register int i=1;i<=n;++i) {
        b[i]=calc(i,x);
        sum+=b[i];
    }
    return sum<m;
}
int main() {
    n=read();m=read();
    ll l=0,r=0;
    for(register int i=1;i<=n;++i) {
        a[i]=read();
        l=min(l,f(a[i],a[i]-1));
        r=max(r,f(a[i],0));
    }
    while(l+1<r) {
        ll mid=l+r>>1;
        if(check(mid)) r=mid;
        else l=mid;
    }
    if(check(l)) r=l;
    check(r);
    m-=sum;
    for(register int i=1;i<=n;++i) if(m>0&&b[i]<a[i]&&f(a[i],b[i])==r) ++b[i],--m; 
    for(register int i=1;i<=n;++i) printf("%lld ",b[i]);
    return 0;
}
```





---

## 作者：cosmicAC (赞：6)

提供一个和官方题解不同的算法。

注意到如果把题目要求中的“整数”和$b_i\le a_i$这两个限制去掉，就是一个基本的求多元函数最大值的形式。所以可以先假设$b_i$可以取任何的非负实数，求出最优解，然后在其基础上调整出答案。

求可导的多元函数的最大值，一般都可以用[拉格朗日乘数法](https://baike.baidu.com/item/%E6%8B%89%E6%A0%BC%E6%9C%97%E6%97%A5%E4%B9%98%E6%95%B0%E6%B3%95)来搞（[维基百科](https://zh.wikipedia.org/wiki/%E6%8B%89%E6%A0%BC%E6%9C%97%E6%97%A5%E4%B9%98%E6%95%B0)）。对于这道题而言，可以列出这个方程组：

$$\frac{\mathrm{d}}{\mathrm{d}b_i}\left(\sum_{i=1}^{n}b_i\left(a_i-b_i^2\right)-\lambda\left(\sum_{i=1}^{n}b_i-k\right)\right)=0,i\in [1,n]$$

化简一下就是：

$$a_i-3b_i^2=\lambda,i\in [1,n]$$

发现因为$b_i\ge 0$，左边是单调的，这和标准解法利用的差分之后单调递减的性质差不多。

由于是单调的，可以二分$\lambda$，通过$\lambda$解出所有$b_i$，然后比较$\sum{b_i}$和$k$的大小决定该往哪半边走。这样简化版的问题就做完了，时间复杂度$O(n\log{(\max{a_i})})$。

然后考虑加回去$b_i\le a_i$的限制。把$a_i\lt b_i$和$a_i-3b_i^2=\lambda$联立，可以解出只有$a_i$小于某个值时才会超出限制。所以把$a$数组从小到大排序，不满足限制的一定是开头的一部分数。

如果在前一步二分的时候，把二分的下界定为$\max{(a_i-3a_i^2)}$，容易看出此时求得的方案一定满足$b_i\le a_i$的限制。然而这个二分出的方案**不一定是**合法解，因为如果最后求出的$\lambda$恰好等于下界时，此时可能$\sum b_i<k$。

所以我们在外层再套一个二分，二分最优解中是最小的$mid$个$b_i$卡到了上限，只求解$a[mid+1\dots n]$这些数，通过内层二分计算出的$\sum b_i$是否$<k-\sum_{i=1}^{mid}a_i$来判断该往哪半边走。

现在求出的方案是满足限制的实数最优解。感性理解一下就知道整数的最优解$ans_i\in \{\lfloor b_i\rfloor,\lceil b_i\rceil\}$（这个性质我不会严谨证明）。所以我们一开始先赋值$ans_i=\lfloor b_i\rfloor$，计算出$rest=k-\sum{ans_i}$，然后选择出$rest$个$ans_i$加上$1$。

这一步很简单，把每一个$ans_i+1$时对答案增加的贡献排个序，选择最大的$rest$个就可以了。要注意的是如果$ans_i=a_i$就不能再$+1$了。

最后把$ans$数组还原成输入时的顺序即可。时间复杂度$O(n\log{(\max{a_i})}\log{n})$。

这就是我比赛现场的做法。这个做法得到了TLE on test 10。赛后发现调整几个精度问题就过了：

-  内层二分的结束条件是$r-l\le\epsilon$，这个$\epsilon=1$。因为二分边界最大可以达到$3\times10^{18}$，此时`long double`的精度只到个位，如果$\epsilon$比精度还要小就会死循环。
- 最后一步按照增加的贡献排序时，不能用`long double`算出来两个贡献再相减，要手动化简一下式子。因为两个相近的大数相减会大大降低精度。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;
int n,_,pos[1<<17];ll k,a[1<<17],b[1<<17];
struct st{ll x;int y;}c[1<<17],q[1<<17];
int chk(int x){
	ld l=-1e20,r=1e20,ik=k;int ok=0;
	for(int i=1;i<=x;i++)ik-=a[i];
	if(ik<0)return 0;
	for(int i=x+1;i<=n;i++)l=max(l,(ld)a[i]-3*a[i]*a[i]),r=min(r,(ld)a[i]);
	while(r-l>1){
		ld mid=(l+r)/2,tot=0;
		for(int i=x+1;i<=n;i++)tot+=sqrtl((a[i]-mid)/3);
		if(tot>ik)l=mid,ok=1;else r=mid;
	}
	for(int i=x+1;i<=n;i++)b[i]=sqrtl((a[i]-l)/3);
	return !ok;
}
int main(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lld",a+i),c[i]={a[i],i};
	sort(c+1,c+1+n,[](st a,st b){return a.x<b.x;});
	for(int i=1;i<=n;i++)pos[c[i].y]=i;
	sort(a+1,a+1+n);
	int l=0,r=n+1,mid;
	while(l<r){
		mid=l+r>>1;
		if(chk(mid))l=mid+1;
		else r=mid;
	}
	for(int i=1;i<=l;i++)b[i]=a[i];
	chk(l);
	for(int i=1;i<=n;i++){k-=b[i];if(b[i]<a[i])q[++_]={a[i]-3*b[i]*b[i]-3*b[i],i};}
	sort(q+1,q+1+_,[](st a,st b){return a.x>b.x;});
	for(int i=1;i<=k;i++)b[q[i].y]++;
	for(int i=1;i<=n;i++)printf("%lld%c",b[pos[i]]," \n"[i==n]);
	return 0;
}
```

---

## 作者：狸狸养的敏敏 (赞：4)

一道 很 好 的 数学题  
首先不应该考虑一开始就构造成型的 $b_i$ ，而是考虑把 $k$ 个 $1$ 分配到每一个 $b_i$ 里去，那么，如果 $b_i+1=x$ ，则 
$$\Delta _{ans}=x(a_i-x^2)-(x-1)[a_i-(x-1)^2]=-3x^2+3x+a_i-1$$

这个时候，一个暴力的做法应该就出来了，每次 $O(N)$ 地去枚举每个 $1$ 给哪个 $b_i$ ，显然此时的 $\Delta_{ans}$ 应该是 $\max_{i=1}^{n} \Delta_{ans_i}$

但是这样的时间复杂度是 $O(NK)$ 的，咱们承受不起

这个时候，我们应该把 $-3x^2+3x+a_i-1$ 的图画一下：
![](https://i.loli.net/2020/05/27/3RNS2zpdo6KPbEW.png)

Q.这做蛇啊，这函数也没啥性质啊，爪巴  
A.$x\in N^*$,你爪巴

从上图我们可以看出，当 $x\in N^*$ 时，函数的值是递减的，因此，在暴力做法中，我们每次增加的 $\Delta_{ans}$ 一定也是递减的

```
简证：
若存在△ans>△lastans,且 i ≠ lasti，则上一次操作应该令b[i]+1,而非 b[lasti]+1
若 i=lasti，根据函数在[1,+∞)单调递减，肯定不存在
Q.E.D.
```

为此，我们不妨设最大的 $\Delta_{ans}=p$ ，也就是在暴力做法中第一次加的答案，意思是这 $k$ 次操作对最终答案的贡献都不会超过 $p$, 由此，我们可以求出满足条件的最大的每一个 $b_i$ ，而 $p$ 显然是可以二分的（单调可行性）

由此，我们直接二分 $p$ ，可以粗略的求出每一个 $b_i$， 求 $b_i$ 的过程可以用二分做，也可以用解一元二次方程的方法做。

但是，我们注意到这样做的结果不一定能保证 $\sum_{i=1}^{n}=k$，因此，剩下的一小部分，我们仍需要通过暴力的思路来分配给最优的 $b_i$，同时计算 $\Delta_{ans}$ 

```
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define reg register
#define int long long
#define db double
using namespace std;
int read(){int x=0,f=0;char ch=0;while(!isdigit(ch))f|=(ch=='-'),ch=getchar();while(isdigit(ch))(x*=10)+=(ch^48),ch=getchar();return f?-x:x;}
void Ot(int x){if(x<0)putchar('-'),x=-x;if(x>=10)Ot(x/10);putchar(x%10+48);}
void Print(int x,char til='\n'){Ot(x);putchar(til);}
int Max(int x,int y){return x>y?x:y;}
int Min(int x,int y){return x<y?x:y;}
int Abs(int x){return x<0?-x:x;}
const int MAXN=200050;
db f(int a,int x){return a-3.0*x*x+3.0*x-1.0;}
int n,k,a[MAXN],b[MAXN],ans;
struct Node{
	int val,pos;
	int vertigo;
	bool operator<(const Node &rhs)const {
		return vertigo>rhs.vertigo;
	}
}p[MAXN];
int mirage(int x){
	memset(b,0,sizeof(b));
	reg int sum=0;
	for(reg int i=1;i<=n;i++){
		int l=0,r=a[i];
		while(l<=r){
			reg int mid=(l+r)>>1;
			if(f(a[i],mid)>=x)b[i]=mid,l=mid+1;
			else r=mid-1;
		}
		sum+=b[i];if(sum>k)break;
	}
	return sum;
}
bool cmp(Node a,Node b){return a.pos<b.pos;}
signed main(){
	n=read(),k=read();
	for(reg int i=1;i<=n;i++)a[i]=read(),p[i].pos=i;
	reg int l=-4e18,r=1e18;
	while(l<=r){
		reg int mid=(l+r)>>1;
//		cerr<<mid<<" "<<mirage(mid)<<endl;
		(mirage(mid)<=k)?(ans=mid,r=mid-1):(l=mid+1);
	}
	reg int tmp=mirage(ans);
//	cerr<<tmp<<endl;
	for(reg int i=1;i<=n;i++)p[i].val=b[i],p[i].vertigo=f(a[i],b[i]+1);
	sort(p+1,p+n+1);
	for(reg int i=1;i<=n&&tmp<k;i++)if(p[i].val<a[p[i].pos])++p[i].val,++tmp;
	sort(p+1,p+n+1,cmp);
	for(reg int i=1;i<=n;i++)Print(p[i].val,' '); 
	return 0;
}


```

---

## 作者：zhylj (赞：2)

思路好像和大家不太一样。

先考虑没有 $b$ 的和为 $k$ 限制如何处理：

单独考虑每一项，考虑函数 $f(x) = x(a_i-x^2)$，容易得到其在 $[0,a_i]$ 上的极值点为 $x_{\max} = \dfrac {\sqrt{3a_i}}3$，所以我们可以暴力把 $\left\lfloor x_{\max}\right\rfloor$ 以及 $\left\lceil x_{\max}\right\rceil$ 代入得到每一项单独的极值。

这时候我们想，要是所有的极值点横坐标加起来刚好是 $k$，那岂不是太好了？

所以，我们考虑由于 $b_i$ 的和为定值 $k$，故而最小化 $\sum_{i=1}^n b_i(a_i-b_i^2)$ 等价于最小化 $ck + \sum_{i=1}^n b_i(a_i-b_i^2)$，也即最小化 $\sum_{i=1}^n b_i(a_i-b_i^2) + cb_i$，其中 $c$ 为任意常数。

此时我们的函数变为了 $f(x) = x(a_i - x^2 + c)$，容易得到其在 $[0,a_i]$ 上的极值点在：

$$x_{\max} = \left\{\begin{aligned}& \min\left\{\dfrac {\sqrt{3(a_i+c)}}3,a_i\right\} & ,a_i + c \ge 0\\& 0 & ,a_i + c < 0\\\end{aligned}\right.$$

我们注意到一个简单的事实，$x_{\max}$ 是随着 $c$ 增大逐渐向右移动的。而根据中值定理，则必然存在某个 $c$，使得 $\sum x_{\max} = k$。

这正是我们想要的！我们仍然要最小化一个函数，然而此时的全局最优值确恰好满足了我们要的性质。

然后我们又面临了一个新问题：$x_{\max}$ 都不是整数。

我们又注意到此时所有的 $b_i$ 都只在 $\left\lfloor x_{\max}\right\rfloor$ 和 $\left\lceil x_{\max} \right\rceil$ 中取，于是我们考虑先二分出最大的使得 $\sum \left\lfloor x_{\max}\right\rfloor \le k$ 的 $c$，然后按照 $f(\left\lceil x_{\max} \right\rceil) - f(\left\lfloor x_{\max}\right\rfloor)$ 从大到小贪心地选择，令一部分的极值点取大一点，使得所有极值点的和恰好为 $k$.

然后我们就做完了，时间复杂度为 $\mathcal O(n\log \max a_i)$.

```cpp
const int kN = 5e5 + 5, kInf = 0x3f3f3f3f;
const ll kInfLL = 0x3f3f3f3f3f3f3f3fLL;

int n, idx[kN]; ll k, A[kN], B[kN], d[kN];

bool Check(ll mid) {
	ll t = 0;
	for(int i = 1; i <= n; ++i) {
		ll x = sqrt(std::max(A[i] / 3.0 + mid, kEps));
		t += std::min(x, A[i]);
	}
	return t >= k;
}

int main() { 
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	int T = 1; //rd(T);
	while(T--) {
		rd(n, k);
		for(int i = 1; i <= n; ++i)
			rd(A[i]);
		ll l = -1e18, r = 1e18;
		while(l < r) {
			ll mid = (l + r + 1) >> 1;
			if(Check(mid)) r = mid - 1;
			else l = mid;
		}
		ll s = 0;
		for(int i = 1; i <= n; ++i) {
			B[i] = sqrt(std::max(A[i] / 3.0 + l, kEps));
			B[i] = std::min(B[i], A[i]);
			if(B[i] < A[i]) {
				d[i] = -3 * (B[i] * B[i] + B[i]) + A[i];
			} else d[i] = -kInfLL;
			s += B[i];
			idx[i] = i;
		}
		std::sort(idx + 1, idx + n + 1, [](const int &x, const int &y) {
			return d[x] > d[y];
		});
		for(int i = 1; i <= k - s; ++i) ++B[idx[i]];
		for(int i = 1; i <= n; ++i) printf("%lld ", B[i]);
		printf("\n");
	} return 0;
}

```

---

## 作者：Carnival (赞：1)

[CF1344D](https://www.luogu.com.cn/problem/CF1344D)，*2700，数学

闲话：为什么我和大多数题解思路类似，但是代码逻辑有一堆地方不一样啊？

首先令 $b_i=0$，则 $\sum b_i=k$ 相当于操作 $k$ 次，每次把某个 $b_i$ 加一。观察那个要求最大化的式子，考虑作差，定义关于 $b$ 的函数 $f(a,b)=b\times(a-b^2)-(b-1)\times(a-(b-1)^2)$，其含义是当 $a_i=a,b_i=b-1$ 时，把 $b_i$ 增加到 $b$ 造成的贡献，并规定 $f(a,a+1)=-\inf$，代表将 $b_i$ 增加到 $a_i$ 时就不能再增加了。化简一下得到 $f(a,b)=-3b^2+3b+a-1$，它在正整数域上单调递减，这意味着随着操作次数变多，每次操作对答案的贡献逐渐变小。于是一个朴素的解法就是维护一个堆，初始时放入 $f(a_i,1)$，每次取最大的 $f(a,b)$ 累加到答案中并将 $f(a,b+1)$ 放入堆，重复 $k$ 次。

上面那个做法会在第八个点 T 掉，考虑优化。考虑二分最后一次操作的贡献值 $m$，$m$ 越小，说明有越多比它大的贡献已经被累加到答案中了，所以贡献越小越优。当最后一次贡献值确定时，记此时的 $b_i=b$，则一定有 $f(a_i,k) \ge m(k=1,2,\cdots,b)$ 且 $f(a_i,b+1) \le m$。第一个条件说明对 $b_i$ 进行的所有操作的贡献值都大于等于 $m$，不然这次操作不可能早于 $m$ 对应的操作；第二个条件说明对 $b_i$ 的下一次操作（还未进行）不优于 $m$ 对应的操作，否则它已经执行了。注意两个条件都是决定性的：考虑 $f(4,1 \sim 4)=5,4,3,2,m=3$，则 $b = 1,2,3$ 符合第一个条件，而 $b=2,3,4$ 符合第二个条件，所以此时 $b_i=2$ 或 $3$。若 $b_i$ 有多个取值时怎么办呢？注意到 $b_i \in [0,a_i]$ 已被满足（$b_i=0$ 说明操作这个 $b_i$ 太劣，$b_i=a_i$ 说明操作这个 $b_i$ 太优，都无需特判），则规定 $\sum b_i\le k$，为了满足这个条件，应取较小的 $b$。不难发现这个值等于满足 $f(a_i,b)>m$ 的最大 $b$，那内层二分即可得出每个 $b_i$ 的取值。

外层二分结束后，记得出的最后一次操作的贡献值为 $m$，此时 $b_i$ 的状况其实是：所有贡献等于 $m$ 的操作都还没有被执行（注意观察上面 $b_i$ 的取值），则这个时候 $b_i$ 的总和其实是一定小于 $k$ 的（所以也可以规定 $\sum b_i<k$），那枚举每个 $b_i$，看下 $f(a_i,b_i+1)$ 是否恰好等于 $m$，是的话把 $b_i$ 加一即可，直到 $b_i$ 的和恰好等于 $k$ 时退出。

还有几个问题提一下：一是这种写法不需要考虑什么“外层二分分出长度为 $2$ 的区间就停下来”的奇怪限制，找到最小的 $m$ 满足 $\sum b_i\le k$，则这个 $m$ 就是最终的 $m$ 了；二是或许有人会像我有一样的疑惑，认为万一二分出来后 $b_i$ 的和太小，那最后那一步调整 $b_i$ 的和到 $k$ 不还是 $\Theta(k)$ 的吗？其实，距前面分析可得，最终每个 $b_i$ 至多只需要再操作一次，因为外层二分结束后，所有贡献等于 $m$ 的操作都还没有被执行，此时只需执行这些操作即可，而由于 $f$ 单调递减，因此对于一个特定的 $i$，$f(a_i,1 \sim a_i)$ 互不相同，则 $[1,a_i]$ 中至多有一个 $b$ 满足 $f(a_i,b+1)$ 等于 $m$，这个 $b$ 即为二分结束后 $b_i$ 的取值，那至多再操作一次这个 $b_i$ 就无法操作了。

```cpp
// Problem: D. Résumé Review
// Contest: Codeforces - Codeforces Round 639 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1344/D
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#define ll long long
using namespace std;
const int N=1e5+7;
const ll inf=1e18;
void init();
ll f(int a,ll b){
	if(a<b) return -inf;
	else return -3*b*b+3*b+a-1;
}
ll check(ll);
int a[N];
ll b[N];
int n;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	init();
	return 0;
}
void init(){
	int i;
	ll l=inf,r=-inf,k,ans;
	cin>>n>>k;
	for(i=1;i<=n;++i){
		cin>>a[i];
		l=min(l,f(a[i],a[i]));
		r=max(r,f(a[i],1));
	}
	ans=r;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(mid)<=k){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
		// 注意应尽量小, 所以符合条件时应令 r=mid!
	}
	// cout<<k<<' '<<l<<' '<<r<<'\n';
	k-=check(ans);
	for(i=1;i<=n&&k>0;++i)
		if(f(a[i],b[i]+1)==ans){
			b[i]++;
			k--;
		}
	for(i=1;i<=n;++i)
		cout<<b[i]<<' ';
	cout<<'\n';
}
ll check(ll m){
	ll sum=0;
	for(int i=1;i<=n;++i){
		int l=1,r=a[i];
		b[i]=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(f(a[i],mid)<=m) r=mid-1;
			else{
				// assert(b[i]<=mid);
				b[i]=mid;// b[i] 在二分过程中单调增.
				l=mid+1;
			}
		}
		sum+=b[i];
	}
	return sum;
}

---

## 作者：Fan_sheng (赞：1)

考虑令 $F(i,x)=b_i(a_i-b_i^2)$，再令 $F$ 的增量函数 $f(i,x)=F(i,x)-F(i,x-1)=a_i-3x^2+3x-1$。

这样的话，我们有一个暴力的想法：初始所有 $b_i=0$，每次贪心地选择最大的增量 $f(i,b_i+1)$ 计入贡献，并让 $b_i$ 加一，重复 $k$ 次。使用堆优化后复杂度 $\mathbb O(k\log n)$，不能通过。

当 $i$ 固定，$x\in N^+$ 时，$f(i,x)$ 单调递减。那么我们容易发现，每次选择的最大增量也是单调递减的。

有了单调性，可以考虑二分**最后一次**选择的最大增量 $lim$，并且因为它最大，满足 $\forall i,f(i,b_i)\le lim$，可以直接解方程或者二分解出最小的 $b_i$，满足 $\sum b_i\le k$ 就 check 成功。

内层二分的时候注意一下边界：有可能 $b_i=0$，那么此时一定有 $f(i,0)=f(i,1)\le lim$，因此把二分左边界设为 $0$ 即可。

最后得到的 $\sum b_i$ 有可能小于 $k$ （因为 $b_i\in N$，没有那么精准）。剩下的一小点选择次数我们就按照之前堆优化的思路暴力选择就可以了。

时间复杂度 $\mathbb O(n\log^2 V)$ 或 $\mathbb O(n\log V)$（解方程）。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll k,a[100005],b[100005],chance;
inline ll f(int i,ll x){return a[i]-3ll*x*x+3ll*x-1;}
inline bool check(ll lim){
	ll res=0;
	for(int i=1;i<=n;i++){
		ll l=0,r=a[i],mid;
		b[i]=r;
		while(l<=r){
			mid=(l+r)>>1;
			if(f(i,mid)<=lim)r=(b[i]=mid)-1;
			else l=mid+1;
		}res+=b[i];
	}return res<=k;
}
int main(){
	scanf("%d%lld",&n,&k);
	ll l=-2e18,r=2e18,mid,ans=2e18;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))r=(ans=mid)-1;
		else l=mid+1;
	}check(ans);
	priority_queue<pair<ll,int>>q;
	for(int i=1;i<=n;i++){
		if(b[i]<a[i])q.emplace(f(i,b[i]+1),i);
		chance+=b[i];
	}
	while(chance<k){
		int h=q.top().second;q.pop();
		++b[h],++chance;
		if(b[h]<a[h])q.emplace(f(h,b[h]+1),h);
	}
	for(int i=1;i<=n;i++)printf("%lld ",b[i]);return 0;
}
```


---

