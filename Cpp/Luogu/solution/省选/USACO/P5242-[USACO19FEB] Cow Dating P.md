# [USACO19FEB] Cow Dating P

## 题目描述

由于目前可供奶牛们使用的约会网站并没有给 Farmer John 留下深刻印象，他决定推出一个基于新匹配算法的奶牛交友网站，该算法可基于公牛和母牛间的共同兴趣对公牛和母牛进行匹配。

Bessie 在寻找情人节 Barn Dance 的合作伙伴时，决定试用这个网站。在注册账户之后，FJ 的算法为他给出了一个长度为 $ N $（$1 \leq N \leq 10^6$） 的匹配列表，列表上每头公牛接受她舞蹈邀请的概率为 $ p $（$0 < p < 1$）。

Bessie 决定向列表中的一个连续区间内的奶牛发送邀请，但Bessie希望**恰好只有一个奶牛**接受邀请。请帮助 Bessie 求出**恰好只有一个奶牛**接受邀请的最大概率是多少。

## 说明/提示

样例的最优方案是向第二和第三只奶牛发送邀请。

子任务：对于 $ 25\% $ 的数据， $ N \leq 4000 $ 。

## 样例 #1

### 输入

```
3
300000
400000
350000
```

### 输出

```
470000```

# 题解

## 作者：w4p3r (赞：24)

## 1.前言
做完这道题，我一看题解就懵了，这些都是什么神仙三分，神仙做法。
## 2.做法
我的做法也是决策单调性，但是我们要证明一下，这个东西为什么有决策单调性。

$l-r$这段区间的算出来的值是：

$\sum_{i=l}^{r}p_i \prod_{j=l,j!=i}^{r} {(1-p_j)}$

假设$S_l^r=\prod_{i=l}^{r}{(1-p_i)}$

则原式$=\sum_{i=l}^{r}\frac{p_i}{1-p_i}S_l^r=S_l^r\sum_{i=l}^{r}\frac{p_i}{1-p_i}$

为了方便，现在假设$a_i=1-p_i,b_i=\frac{p_i}{1-p_i}$

则$l-r$算出来的值为:$\prod_{i=l}^r a_i\sum_{i=l}^rb_i$

我们考虑把$r$变成$r+1$会发生什么

再次为了方便，假设$A=\prod_{i=l}^r a_i,B=\sum_{i=l}^rb_i$

则$r$变成$r+1$后，答案变成：

$(A*a_{r+1})(B+b_{r+1})$

$=A(a_{r+1}B+a_{r+1}b_{r+1})$

$=A(a_{r+1}B+p_{r+1})$(不知道为什么回去看看$a,b$的定义)

我们假设答案变大，康康会发生什么

即假设$a_{r+1}B+p_{r+1}>B$

根据$a$的定义，可以得到$(1-p_{r+1})B+p_{r+1}>B$

等式变形之后，可以得到$B<1$

$B<1????$

这样问题就变得十分简单了，对于每个$l$，你找到最远的$r$,使得$\sum_{i=l}^{r}b_i<1$即可

这当然可以二分,时间复杂度$O(nlogn)$

但是显然的，这个是具有单调性的，所以你可以直接用单调性做，时间复杂度$O(n)$

**(因此其实主要原因不是答案决策有单调性（答案的确也有单调性），而是找到最远的r使b的和<1具有单调性，使得答案也有单调性)**

## 3.代码

我写的是$O(n)$的单调性

```cpp
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define N 1000010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
double A=1,B;
int n,R=0;
double p[N],ans;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	for(register int i=1;i<=n;i++)p[i]=read(),p[i]/=1e6,ans=max(ans,p[i]);
	//L左端点，R右端点 
	for(register int L=1;L<=n;L++)
	{
		while(R<n&&B<1){R++;B+=p[R]/(1-p[R]);A*=(1-p[R]);}//单调性 
		ans=max(ans,A*B);//统计答案 
		A/=(1-p[L]);B-=p[L]/(1-p[L]);//把L变成L+1 
	}
	printf("%d\n",int(ans*1e6));
	return 0;
}

```

~~（我10行头文件被说：很遗憾，您上传的题解【题解 P5242 【[USACO19FEB]Cow Dating】】因为【拒绝: 请勿在代码前添加超长预编译指令】未能通过审核。）了？？~~


**如果认为我这篇题解对你有帮助的可以给我点一下赞qwq。如果有任何疑问，或者认为我的题解有什么问题的话，请务必私信我，感激不尽！我会努力把我的题解写得最好的!**



---

## 作者：cosmicAC (赞：8)

令$p_i$表示第i个位置是1的概率，$s_i=\prod_{k=1}^{i}(1-p_k)$,$t_i=\sum_{k=1}^{i}\frac{p_k}{1-p_k}$

显然区间$[l,r]$的答案为
$$\frac{s_r}{s_{l-1}}(t_r-t_{l-1})$$

固定右端点r，直观感觉到随着l的左移，乘积第二项变大，乘积第一项变小。所以猜到这个式子是凸的（我太菜了不会证），于是枚举右端点，整数三分左端点即可。

然而$s_i$太小了，会发生除零错。这个容易解决，把式子取个对数，
$$\log(\frac{s_r}{s_{l-1}}(t_r-t_{l-1}))=\log{s_r}-\log{s_{l-1}}+\log(t_r-t_{l-1})$$

最后把答案再exp一下，然后精度就不会有任何问题了。时间复杂度$O(n\log n)$。

常数太大了过不去怎么办？三分时判断语句里移一下项，运用$\log{a}-\log{b}=\log\frac{a}{b}$，就可以只做一次`log`运算，常数除以2。

有一个有趣的事情：对于随机的数据，答案很接近$\frac{1}{e}$。$e$这个神奇的常数居然又一次在貌似无关的地方出现了。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
using ld=long double;
int n;ld a[1<<20],s[1<<20],t[1<<20],ans=-INFINITY;
inline ld calc(int i,int j){return s[j]-s[i]+log(t[j]-t[i]);}
ld tri(int l,int r,int p){
	if(l==r)return calc(l,p);
	int mid=l+r>>1;
	if(-s[mid]+s[mid+1]<log((t[p]-t[mid+1])/(t[p]-t[mid])))return tri(mid+1,r,p);
	return tri(l,mid,p);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		a[i]=x/1e6;
		t[i]=t[i-1]+a[i]/(1-a[i]);
	}
	for(int i=1;i<=n;i++)s[i]=s[i-1]+log(1-a[i]);
	for(int i=1;i<=n;i++)ans=max(ans,tri(0,i-1,i));
	printf("%d\n",int(exp(ans)*1e6));
	return 0;
}
```

下面是来自不会高中数学的本蒟蒻的证明

首先随便输入几个数据就会发现当$p_i\to 0$时最接近$\frac{1}{e}$，于是设x趋向于0，k为所需的序列长度

$$\lim_{x \to +0} (1-x)^kk\frac{x}{1-x}$$
$$(1-x)^kk\frac{x}{1-x}=(1-x)^{k-1}kx$$
$$((1-x)^{k-1}kx)'=x(k(1-x)^{k-1}\ln{(1-x)}+(1-x)^{k-1})$$
令上式=0，得$k\ln{(1-x)}=-1$，$k=-\frac{1}{\ln{(1-x)}}$

带入$\lim_{x \to +0} (1-x)^kk\frac{x}{1-x}$中

$$\textrm{原式}=\exp{(k\ln{(1-x)}+\ln(kx)-\ln{(1-x)})}$$
$$=\exp({-1+\ln{(\frac{x}{-\ln{(1-x)}})}-\ln{(1-x)}})$$

显然$\ln({1-x})$趋向于0，另外考虑把$-\ln{(1-x)}$泰勒展开，得到
$$-\ln{(1-x)}=x+\frac{x^2}{2}+\frac{x^3}{3}+\frac{x^4}{4}+\ldots$$
后面都是高阶无穷小，所以
$$\lim_{x \to +0}\frac{x}{-\ln{(1-x)}}=1$$
于是该极限的值就是$e^{-1}$

---

## 作者：felixwu (赞：3)

通过观察数据，我们可以发现，右端点的取值是单调递增的。于是，我们可以极限一波，用一个双指针法，类似于队列。  
右端点的取值满足以下公式：   
(1-p1)(1-p2)..(1-pn) * (p1/(1-p1) + p2/(1-p2) + ... + pn/(1-pn))  
记录两个变量，表示和和积即可。    
                  tmp1为积，tmp2为和
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long double llf;
int n;
llf p[1000001],ans=0,tmp1=1,tmp2;//tmp1一定要赋值为1，如果是0的话大家都知道下场
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		cin>>p[i];
		p[i]/=1e6;
		ans=max(ans,p[i]);
	}
	int j=1;                             
	for(int i=1;i<=n;i++) {
		while(j<=n&&tmp1*tmp2<tmp1*(1-p[j])*(tmp2+p[j]/(1-p[j]))){//根据公式判断 
			tmp1*=(1-p[j]);
			tmp2+=p[j]/(1-p[j]);//更新两个变量
			j++;
		}
		ans=max(ans,tmp1*tmp2);//更新答案
		tmp1/=(1-p[i]);
		tmp2-=p[i]/(1-p[i]);
	} 
	printf("%d",(int) (1e6*ans));
	return 0;
}
```


---

## 作者：Mariposa (赞：1)

好像题解都比较神秘，那我来写一篇小白向的。

考虑区间 $[l,r]$ 正好一个的概率：$\sum\limits_{i=l}^r P_i\prod\limits_{j\in [l,r],j\neq i}(1-P_j)$

记前缀积为 $S1$，前缀和为 $S2$，则上式为 $\dfrac{S1_{r}}{S1_{l-1}}(S2_{r}-S2_{l-1})$

这是个典型的斜率优化的式子，这题成为了板子题。

具体的我们令上式为 $f(r)$，变型后有 

$$\dfrac{S2_{l}}{S1_{l}}=S2_{r}\dfrac 1{S1_{l}}+S1_{r}S2_{r}-f(r)$$

则 $y=\frac{S2_{l}}{S1_{l}},x=\frac 1{S1_{l}},k=S2_{r},b=S1_{r}S2_{r}-f(r)$

我们希望 $b$ 尽量小，而 $k$ 递增，故我们维护一个下凸包即可。

时间复杂度 $O(n)$

```
#include<bits/stdc++.h>
using namespace std;
#define double long double
#define inf 1e9
const int maxn=1e6+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n,m,q[maxn];
double P[maxn],S1[maxn],S2[maxn],ans;
inline double X(int x){return 1/S1[x];}
inline double Y(int x){return S2[x]/S1[x];}
inline double slope(int x,int y){
	return (Y(y)-Y(x))/(X(y)-X(x));
}
int main(){
	n=read(),S1[0]=1;
	for(int i=1;i<=n;i++){
		P[i]=read()/1000000.0;
		S1[i]=S1[i-1]*(1-P[i]);
		S2[i]=S2[i-1]+P[i]/(1-P[i]);
	}int l,r;q[l=r=1]=0;
	for(int i=1;i<=n;i++){
		while(l<r&&slope(q[l],q[l+1])<S2[i])l++;
		ans=max(ans,S1[i]/S1[q[l]]*(S2[i]-S2[q[l]]));
		while(l<r&&slope(q[r-1],q[r])>slope(q[r],i))r--;
		q[++r]=i;
	}printf("%d\n",(int)(ans*1000000));
	return 0;
}
```

---

## 作者：vectorwyx (赞：1)

神仙题awa

$O(n^2)$ 个区间信息求 $\max$，一般有两种思路：分治，或固定左端点观察所有可能右端点的性质。

先来考虑怎么对给定的一段区间 $[l,r]$ 求恰好只有一个奶牛接受邀请的概率。朴素式子是 $\prod_{i=l}^r(p_i\cdot\prod_{j\not=i}(1-p_j))$，令 $S=\prod (1-p_i)$，则 $p_i\cdot\prod_{j\not=i}(1-p_j)=S\cdot\frac{p_i}{1-p_i}$，提一个 $S$ 出来即为 $S\sum{\frac{p_i}{1-p_i}}$。

这个式子初看可能没有什么感觉，还记得一开始提到的两种思路吗？我们固定左端点，考虑右端点从 $r-1$ 向右拓展一位变成 $r$ 后这个式子发生的变化。首先 $S$ 会变成 $S\cdot (1-p_{r})$，然后右面的这个和式，姑且叫她 $T$ 吧，会变成 $T+\frac{p_{r}}{1-p_r}$。那么 $S\cdot T$ 就会变成 $S\cdot(1-p_r)(T+\frac{p_r}{1-p_r})=ST(1-p_r)+Sp_r=ST-STp_r+Sp_r$，它与 $ST$ 相比增加了 $Sp_r-STp_r=Sp_r(1-T)$。而 $S,p_r$ 都是正的，所以这个式子的正负只与 $1-T$ 有关！

换句话说，当 $T<1$ 时，这个式子 $>0$，否则 $\le0$。由 $T$ 的定义，显然对于每个固定的左端点 $l$，$T$ 是单增的，所以随着右端点向右拓展，式子的值先增加后减少，即所有右端点对应的区间的值单峰，那我们可以二分出最优决策点，这样做的复杂度为 $O(n\log n)$。同时，随着 $l$ 左移，最优决策点一定只可能右移，所以可以用双指针代替二分，时间复杂度 $O(n)$



代码如下：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) printf("%d ",*(a+i));puts("");}

const int N=1e6+5;
db a[N],b[N];
int n; 

signed main(){
	cin>>n;
	fo(i,1,n){
		db x=read()/1000000.0;
		a[i]=1-x;
		b[i]=x/(1-x);
	}
	db sum=0,mul=1,ans=0;int R=1;
	fo(i,1,n){
		big(R,i);
		while(R<=n&&sum<1) mul*=a[R],sum+=b[R++];
		big(ans,sum*mul);
		sum-=b[i];
		mul/=a[i];
	}
	cout<<(int)floor(ans*1000000);
	return 0;
}
/*
-------------------------------------------------
*/
```


---

## 作者：Great_Influence (赞：1)

先拆式子。

设 $f_{l,r}$ 表示选择 $l$ 到 $r$ 的答案是多少，则

$$f_{l,r}=[\prod_{i=l}^r (1-p_i)]\sum_{i=l}^r\frac{p_i}{1-p_i}$$

$$=(1-p_r)[\prod_{i=l}^{r-1} (1-p_i)]\sum_{i=l}^{r-1}\frac{p_i}{1-p_i}+p_r[\prod_{i=l}^{r-1} (1-p_i)]$$

$$=(1-p_r) f_{l,r-1}+p_r\prod_{i=l}^{r-1} (1-p_i)$$

可以知道，当任何一个 $p$ 大于 $0.5$ 的时候，选择一段的答案不比选择这一个的答案大。因此直接特判这种情况。

下面 $p$ 全部都 $<0.5$ 。

考虑什么时候会从 $f_{l,r-1}$ 拓展到 $f_{l,r}$ 。

$$f_{l,r}>f_{l,r-1}$$

$$\rightarrow (1-p_r) f_{l,r-1}+p_r\prod_{i=l}^{r-1} (1-p_i)>f_{l,r-1}$$

$$\rightarrow \prod_{i=l}^{r-1} (1-p_i)>f_{l,r-1}$$

这样，我们只需要记录 $\prod_{i=l}^{r-1} (1-p_i)$ 和 $f_{l,r-1}$ 然后再作比较，双指针法向右拓展即可。

时间复杂度 $O(n)$ 。

另附 $f_{l,r}$ 转到 $f_{l+1,r}$ 的方法:

$$(1-p_l)f_{l+1,r}+p_l\prod_{i=l+1}^r (1-p_i)=f_{l,r}$$

$$f_{l+1,r}=\frac{f_{l,r}-p_l\prod_{i=l+1}^r (1-p_i)}{1-p_l}$$

代码:

```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
	const uint32 Buffsize=1<<15,Output=1<<24;
	static char Ch[Buffsize],*S=Ch,*T=Ch;
	inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
	static char Out[Output],*nowps=Out;
	
	inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

	template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

void file(void)
{
	FILE*DSD=freopen("water.in","r",stdin);
	FILE*CSC=freopen("water.out","w",stdout);
}

const int MAXN=1e6+7;

static int n,p[MAXN],ans;

inline void Chkmax(int&u,int v){u<v?u=v:0;}

inline void init()
{
	read(n);
	Rep(i,1,n)read(p[i]),Chkmax(ans,p[i]);
}

inline void solve()
{
	if(ans>=500000)cout<<ans<<endl,exit(0);
	static long double sm=p[1],prd=1000000-p[1];
	static int rb=1;
	while(rb<n&&sm<prd)
	{
		++rb,sm=sm*(1000000-p[rb])/1000000+p[rb]*prd/1000000;
		prd=prd*(1000000-p[rb])/1000000;
	}
	Chkmax(ans,(int)sm);
	Rep(i,2,n)
	{
		prd=prd*1000000/(1000000-p[i-1]);
		sm=(sm*1000000-p[i-1]*prd)/(1000000-p[i-1]);
		while(rb<n&&sm<prd)
		{
			++rb,sm=sm*(1000000-p[rb])/1000000+p[rb]*prd/1000000;
			prd=prd*(1000000-p[rb])/1000000;
		}
		Chkmax(ans,(int)sm);
	}
	cout<<ans<<endl;
}

int main()
{
	file();
	init();
	solve();
	return 0;
}
```

---

## 作者：liugh_ (赞：0)

## [P5242 [USACO19FEB] Cow Dating P](https://www.luogu.com.cn/problem/P5242)

> 给定 $n$ 个物品和每一个被选中的概率 $p_i$，选一个区间使得区间内选且仅选一个物品的概率最大，求这个最大值。
>
> $n\le 10^6$。

容易得到一个区间 $[l,r]$ 的答案
$$
\large h(l,r)=\sum_{i=l}^{r} \frac{\displaystyle \prod_{j=l}^{r}(1-p_j)}{1-p_i}p_i=\left(\prod_{i=l}^{r}(1-p_i)\right)\left(\sum_{i=l}^{r}\frac{p_i}{1-p_i}\right)
$$
考虑记录前缀积 $\displaystyle f_i=\prod_{j=1}^{i} (1-p_j)$，前缀和 $\displaystyle g_i=\sum_{j=1}^{r} \frac{p_j}{1-p_j}$，于是有
$$
\large h(l,r)=\frac{f_r}{f_{l-1}}(g_r-g_{l-1})
$$
观察函数，对于固定的 $l$，当 $r$ 向右移时，$f_r$ 变小，$g_r$ 变大，加上画图和手模，我们猜一个结论：$h$ 是单峰的（证明待补）。于是考虑枚举左端点，三分 $h$ 的顶点，最后取所有左端点的答案的最大值即可。实现上我采用了在导数上二分的写法，此外还有一些细节在代码中给出。

时间复杂度 $O(n\log n)$，常数较小，目前最优解第一页。

```cpp
#include<iostream>
#include<algorithm>
#ifdef ONLINE_JUDGE
#define getchar() (p_==q_&&(q_=(p_=b_)+fread(b_,1,s_,stdin),p_==q_)?-1:*p_++)
#define putchar(x_) ((r_-o_<s_)?(*r_++=x_):(flush(),r_=o_,*r_++=x_))
bool t_=(std::cin.tie(0),std::cout.tie(0),std::ios_base::sync_with_stdio(0));
#endif
#define flush() (fwrite(o_,r_-o_,1,stdout),fflush(stdout),0)
#define exit(_) exit(flush())
using namespace std;constexpr int s_=1<<20;char b_[s_],o_[s_],*p_=b_,*q_=b_,*r_=o_;template<class T_>bool fr(T_&x_){x_=0;char c_=0,f_=0;do{if(c_=='-')f_=1;if((c_=getchar())==-1)return 0;}while(c_<48||c_>57);do {x_=x_*10+c_-48;if((c_=getchar())==-1)break;}while(c_>47&&c_<58);if(f_)x_=-x_;return 1;}template<class T_>void fw(T_ x_){char d_[40],l_=-1;if(x_<0)x_=-x_,putchar('-');do d_[++l_]=x_%10+48;while(x_/=10);do putchar(d_[l_]);while(~--l_);}

#define db long double // 此处应用long double，否则会因精度造成除以0的问题
constexpr int maxn=1e6+10;

int n;
db p[maxn],ans;
db f[maxn],g[maxn];

signed main(){
    fr(n);
    for(int i=1;i<=n;i++){
        int x;fr(x); // 此处应用int读入，否则会很慢
        p[i]=x/1e6;
    }
    f[0]=1;g[0]=0;
    for(int i=1;i<=n;i++)f[i]=f[i-1]*(1-p[i]);
    for(int i=1;i<=n;i++)g[i]=g[i-1]+p[i]/(1-p[i]);
    for(int i=1;i<=n;i++){
        auto h=[&](int x){return f[x]/f[i-1]*(g[x]-g[i-1]);};
        int l=i,r=n,res=n; // 此处res的默认值应为n，因为h(n+1)未定义，二分到n时不一定能得到正确的答案
        while(l<=r){
            int mid=(l+r)>>1;
            if(h(mid)>h(mid+1))res=mid,r=mid-1;else l=mid+1;
        }
        ans=max(ans,h(res));
    }
    fw((int)(ans*1e6));
    exit(0);
}
```

---

## 作者：ZhongYuLin (赞：0)

通过拆解式子，我们不难得到如下朴素代码：

```cpp
for(int i=1;i<=n;++i){
    double f=0,g=1;
    for(int j=i;j<=n;++j){
        f=(1-p[j])*f+p[j]*g;
        g*=1-p[j];
        ans=max(ans,f);
    }
}
```

看起来就很决策单调。拆一下式子：

$$(1-p_i)f+p_ig<f$$

$$f>g$$

也就是说 $f>g$ 时，下一次操作必定使答案变小。

然后我们大胆猜想，这个地方就是决策最优点，然后套一个双指针上去。你会发现你精度爆了，因为你去除区间左端点的时候要除法。然后套个线段树或是倍增，就过了。

~~总感觉能被叉掉。~~

```cpp
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using ll=long long;
using namespace std;
const int N=1e6+3,P=1e6;
struct Mat{
    double a,b,c,d;
    friend Mat operator*(const Mat &x,const Mat &y){
        return {x.a*y.a+x.b*y.c,x.a*y.b+x.b*y.d,
                x.c*y.a+x.d*y.c,x.c*y.b+x.d*y.d};
    }
}t[N<<2];
double p[N];
double ans;
int n;
void push_up(int p){
    t[p]=t[rs]*t[ls];
}
void build(int l=1,int r=n,int p=1){
    if(l==r){t[p]={1-::p[l],::p[l],0,1-::p[l]};return;}
    int mid=l+r>>1;
    build(l,mid,ls);
    build(mid+1,r,rs);
    push_up(p);
}
Mat query(int x,int y,int l=1,int r=n,int p=1){
    if(x<=l&&r<=y)return t[p];
    int mid=l+r>>1;
    if(y<=mid)return query(x,y,l,mid,ls);
    if(x>mid)return query(x,y,mid+1,r,rs);
    return query(x,y,mid+1,r,rs)*query(x,y,l,mid,ls);
}
int main(){
    ios::sync_with_stdio(cin.tie(0));
    cin>>n;
    for(int i=1;i<=n;++i)cin>>p[i],p[i]/=1e6;
    int it=1;double f=0,g=1;build();
    for(int i=1;i<=n;++i){
        for(;it<=n;++it){
            f=(1-p[it])*f+p[it]*g;
            g*=1-p[it];
            ans=max(ans,f);
            if(f>g)break;
        }
        if(i+1>it-1)f=0,g=1;
        else{
            auto x=query(i+1,it-1);
            f=x.b,g=x.d;
        }
    }
    printf("%d\n",(int)(ans*P));
    return 0;
}
```

---

## 作者：Querainy (赞：0)

尝试从斜率优化的角度解释一下。

恰好一个奶牛接受邀请的概率，设 $s=\prod\limits_i(1-p_i)$，那么也就是 $s\sum\limits_i\frac{p_i}{1-p_i}$。那么考虑前缀的 $s$ 和前缀的 $\sum\frac{p_i}{1-p_i}$，设它们是 $a$ 和 $b$，那么我们就是要最大化 $\frac{a_r(b_r-b_l)}{a_l}$，这是 $(a_rb_r,a_r)$ 和 $(\frac{1}{a_l},-\frac{b_l}{a_l})$ 的点积，可以用李超树维护。

但是这里前缀和和前缀积的精度很爆炸（不过好像前缀积老哥也过了）。还是考虑凸壳，这里是求一个右上凸壳，首先斜率 $\frac{a_r}{a_rb_r}$ 是递减的，也就是说我们是顺时针扫凸壳，而 $\frac{1}{a_l}$ 是递增的，也就是说我们是从左往右加点。那么这是决策单调的，可以决策单调性分治。

更劲爆的事情是，每个点都在凸壳上。证明考虑改为枚举左端点，因为右端点一侧形式好一点，其实两边是对称的。相邻三个点 $i,i+1,i+2$ 的叉积是 $(a_{r+1}b_{r+1}-a_rb_r)(a_{r+2}-a_r)-(a_{r+2}b_{r+2}-a_rb_r)(a_{r+1}-a_r)=a_{r+1}a_{r+2}(b_{r+1}-b{r+2})+a_rb_r(a_{r+2}-a_{r+1})-a_r(a_{r+1}b_{r+1}-a_{r+2}b_{r+2})=-a_{r+1}a_{r+2}\frac{p_{r+2}}{1-p_{r+2}}-a_ra_{r+1}b_rp_{r+2}-a_ra_{r+1}p_{r+2}(b_{r+1}+1)<0$，所以相邻三个点总是顺时针转的，所以每个点都在凸壳上。那么我们不需要再求凸壳，直接在序列上双指针即可。这里每个点的答案至少是 $10^{-6}$ 级别，所以精度就好很多啦。复杂度是 $O(n)$。

---

## 作者：muller (赞：0)

考虑如何快速计算一个区间 [l,r] 的价值。

定义二元组 (x,y) 来描述一个区间， 

x表示区间中恰好有一个关键点的概率， 

y表示区间中没有关键点的概率。

显然，对于两个区间 (x1,y1),(x2,y2) (x_1,y_1),(x_2,y_2)
，

上述信息是可以合并的，即 (x1,y1)+(x2,y2)=(x1y2+x2y1,y1y2) 

并且，该运算存在逆运算，

 区间 [l,r] 应的二元组即为 sr−sl−1 s_r-s_{l-1}s 


考虑枚举 r，最优化 l的选取，即我们需要找到 l ，最大化ans

是单调的，因此采用朴素的斜率优化即可。

但这题有更简单的写法：

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
double tmp1 = 1, tmp2 = 0, ans = 0, p[N];
int main() {
	ios :: sync_with_stdio(false);
	int n, t, i;
	cin >> n;
	for (i = 1; i <= n; ++i) {
		cin >> p[i]; p[i] /= (1e6 * 1.0);
		ans = max(ans, p[i]);
	}
	t = 1;
	for (i = 1; i <= n; ++i) {
		while (t <= n && tmp1 * tmp2 < tmp1 * (1 - p[t]) * (tmp2 + p[t] / (1 - p[t]))) {
			tmp1 *= (1 - p[t]); tmp2 += p[t] / (1 - p[t]); ++t;
		}
		ans = max(ans, tmp1 * tmp2);
		tmp1 /= (1 - p[i]); tmp2 -= p[i] / (1 - p[i]);
	}
	cout << (int)(ans * 1e6) << endl;
	return 0;
}

```



---

