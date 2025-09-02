# COUNTARI

## 题目描述

给定一个长度为 $n$ 的数组 $a$，求有多少对 $i,j,k(1\leq i<j<k\leq n)$，满足 $a_k-a_j=a_j-a_i$。

## 说明/提示

数据保证，$1\leq n\leq 10^5$，$1\leq a_i\leq 3\times 10^4$。

## 样例 #1

### 输入

```
10
3 5 3 6 3 4 10 4 5 2```

### 输出

```
9```

# 题解

## 作者：wangyizhi (赞：5)

[**题目传送门**](https://www.luogu.com.cn/problem/P10666)

神秘做法。

## 题目分析

记 $c_i$ 表示 $i$ 的出现次数。

首先我们先不算三个数相等的情况，最后再加上去。这样方便后面处理。

先不考虑位置顺序的限制，发现是好求的。~~您都开到这道题了那一定会的对吧！~~。记 $s$ 表示 $c$ 自己卷起来的结果，那这一部分的答案就是 $\sum c_i(s_i-c_i)$。但发现其实每个都算了两次，不过问题不大。

考虑减掉多算的部分，发现只有两种情况：$x-d,x+d,x$ 或 $x,x-d,x+d$，其中 $d \neq 0$。第二种其实和第一种是类似的，只要翻转一下重新求即可。下面考虑求第一种情况。

记现在处理到 $p$，之前每个数的出现个数为 $f_i$，那么我们有两种求法：

+ 将 $f$ 自己卷起来，得到 $h$，答案为 $h_{2a_p}$。

+ 枚举前面的每个数，逐个求出答案，为 $\sum f_{2a_p-a_i}$。

发现上面两种方法都是很慢的。将两种方法结合一下，类似于分块，我们可以快速将前几个块末求出的 $h$ 与这块内的散点合并。具体地，记前面几个整块末求出的个数为 $f$，自己卷积的结果为 $h$，这块内每个数的出现次数为 $g$，则答案为 $h_{2a_p}-f_{a_p}^2+\sum_{i>R} 2f_{2a_p-a_i}+g_{2a_p-a_i}$。（乘 $2$ 是因为和其它的统一一下也算两次）。

设块长为 $B$。则卷积部分复杂度为 $O(\frac{n}{B}n \log n)$，枚举计算部分为 $O(nB)$。于是 $B$ 取 $\sqrt{n\log n}$ 时最小，但由于卷积常数很大，可以再取大些。

于是就做完啦。

## Code

```cpp
// by wangyizhi(571247)
#include<bits/stdc++.h>
//#include<bits/extc++.h>
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<int,int>;
//bool Mst;
namespace wyzmath
{
	/*complex*/
	template<typename _Tp=double>
	class complex
	{
	public:
		typedef _Tp vtype;
		vtype x,y;
		complex(vtype _x=0,vtype _y=0):x(_x),y(_y){}
		vtype length(){return std::sqrt(x*x+y*y);}
	}; // class complex
	/*about complex*/
	template<typename _Tp=double>
	complex<_Tp> operator+(complex<_Tp> a,complex<_Tp> b)
	{return complex<_Tp>(a.x+b.x,a.y+b.y);}
	template<typename _Tp=double>
	complex<_Tp> operator-(complex<_Tp> a,complex<_Tp> b)
	{return complex<_Tp>(a.x-b.x,a.y-b.y);}
	template<typename _Tp=double>
	complex<_Tp> operator*(complex<_Tp> a,complex<_Tp> b)
	{return complex<_Tp>(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
	template<typename _Tp=double>
	complex<_Tp> operator+=(complex<_Tp> &a,complex<_Tp> b){return a=a+b;}
	template<typename _Tp=double>
	complex<_Tp> operator-=(complex<_Tp> &a,complex<_Tp> b){return a=a-b;}
	template<typename _Tp=double>
	complex<_Tp> operator*=(complex<_Tp> &a,complex<_Tp> b){return a=a*b;}
}
using namespace std;
using ld=long double;
using compld=wyzmath::complex<ld>;
const compld I(1,0);
const int N=1<<21,V=3e4,VV=6e4,B=5000;
const ld PI=3.141592653589793;
int rev[N];
ll a[N],c[N],s[N],d[N],e[N],p[N];
void FFT(compld *a,int n,int op)
{
	for(int i=0;i<n;i++) if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	for(int mid=1;mid<n;mid<<=1)
	{
		compld omega(cos(PI/mid),op*sin(PI/mid));
		for(int len=mid<<1,i=0;i<n;i+=len)
		{
			compld o(1,0),x,y;
			for(int j=0;j<mid;j++,o=o*omega)
				x=a[i+j],y=o*a[i+j+mid],a[i+j]=x+y,a[i+j+mid]=x-y;
		}
	}
}
void conv(ll *a,ll *b,ll *c,int n)
{
	static compld tmpa[N],tmpb[N];
	int sz=1,l=0;
	while(sz<n) sz<<=1,l++;
	for(int i=1;i<sz;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	for(int i=0;i<sz;i++) tmpa[i]=a[i],tmpb[i]=b[i];
	FFT(tmpa,sz,1),FFT(tmpb,sz,1);
	for(int i=0;i<sz;i++) tmpa[i]=tmpa[i]*tmpb[i];
	FFT(tmpa,sz,-1);
	for(int i=0;i<sz;i++) c[i]=(ll)(tmpa[i].x/sz+0.5);
	for(int i=n;i<sz;i++) c[i]=0;
}
//bool Med;
signed main()
{
//	cerr<<"Memory Size: "<<abs((&Med)-(&Mst))/1024.0/1024<<" MB\n";
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
//	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	int n;ll ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[i]--,c[a[i]]++;
	conv(c,c,s,VV);
	for(int i=0;i<V;i++) s[i<<1]-=c[i]*c[i];
	for(int i=0;i<V;i++) ans+=s[i<<1]*c[i];
//	cout<<ans<<"\n";
	auto sol=[&]()->void
	{
		for(int i=0;i<VV;i++) s[i]=0;
		for(int i=0;i<V;i++) d[i]=e[i]=0;
		for(int i=1,le=0;i<=n;i++)
		{
			ans-=s[a[i]*2]-d[a[i]]*d[a[i]];
			for(int j=le+1;j<=i;j++) if(a[i]!=a[j]&&a[i]*2>=a[j])
				ans-=d[a[i]*2-a[j]]*2+e[a[i]*2-a[j]];
			e[a[i]]++;
			if(i%B==0&&i!=n)
			{
				for(int j=0;j<V;j++) d[j]+=e[j],e[j]=0;
				conv(d,d,s,VV);
				le=i;
			}
		}
	};
	sol();reverse(a+1,a+n+1);sol();ans/=2;
	for(int i=0;i<V;i++) ans+=c[i]*(c[i]-1)*(c[i]-2)/6;
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：nb_jzy (赞：4)

# 题意
给你一个长度为 $n$ 的数列，统计满足 $1\le i < j < k\le n,a_i-a_j=a_j-a_k$ 的三元组 $(i,j,k)$ 的数量。

# 思路
如果打过[这场 ABC](https://atcoder.jp/contests/abc392/tasks/abc392_g)，并且没有学过多项式乘法，然后看着 752 通过的同学肯定对这道题记忆犹新。而如果学过了多项式乘法，那这道题就变得简单了。

先思考 ABC 上的弱化版怎么做，即去掉 $i,j,k$ 的顺序限制，只考虑 $a_i,a_j,a_k$ 构成的三元组。

化简可以得到：
$$
\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{k=1}^n[a_i-a_j=a_j-a_k]=\sum_{j=1}^{n}\sum_{i=1}^{n}\sum_{k=1}^n[a_i+a_k=2\times a_j]
$$
相当于是要统计值为某个 $c$ 的 $a_i+a_k$ 有多少对，而不难发现，如果将 $a_i,a_k$ 变成多项式的指数，即 $x^{a_i},x^{a_k}$。那么这就**相当于在做多项式乘法**，我们定义 $f(x)=\sum_{i=1}^{n}x^{a_i}$，那么计算 $f$ 自卷积的结果，就可以得到 $a_i+a_k=c$ 的答案了。当然 $a_i+a_k$ 和 $a_k+a_i$ 以及 $a_j+a_j$ 会被多算，去掉就好了。
# 解法
而如果加上顺序限制呢？

似乎就不太好做了，将多项式设为全局的值就不行了。因为内层循环变成了：
$$
\sum_{j=2}^{n-1}\sum_{i=1}^{j-1}\sum_{k=j+1}^n[a_i+a_k=2\times a_j]
$$
这样严格的下标顺序让我们很难搞。

当然，对于单独一个 $j$ 来说，答案还是比较好算的，我们只需要将 $f$ 赋成 $a_1\sim a_{j-1}$ 的值，$g$ 赋成 $a_{j+1}\sim a_n$ 的值，然后计算 $f$ 和 $g$ 的卷积就行了。设 $w$ 为 $a_i$ 的值域，单次这样的操作是 $\mathcal O(w\times \log w)$ 的。总复杂度就变成了 $\mathcal O(n\times w \times \log w)$，无法承受。

但是会发现，**如果将很多 $j$ 一起计算贡献**，少算的部分就是**他们之间所产生的的三元组个数**，而这显然是可以做到 $\mathcal O(n^2)$ 的。

把两种思路整合在一起，那么就是**分块**了！其实，对于这种下标关系很烦的东西，分块不乏是一种考虑的方式。

具体的，对于第 $i$ 块的数，可以用一遍多项式乘法算出来第 $1\sim i-1$ 和 $i+1\sim len$ 块之间的二元组算出来。

发现这样计算会算少**右端点在块内的贡献**和**左端点在块内的贡献**，那么分别从前往后和从后往前扫一遍，记录一下每个 $a_i$ 的值有多少个，然后枚举右端点，查询 $2\times a_j-a_k$ 的值有多少个就行了。注意，**左右端点都在块内的贡献**只能算一次。

分析一下时间复杂度：

设块长为 $S$，那么第一部分多项式乘法的复杂度即 $\mathcal O(\lfloor\frac{n}{S}\rfloor\times w \times \log w)$，第二部分统计的复杂度为 $\mathcal O (n\times S)$。

那么平衡一下时间复杂度：
$$
\lfloor\frac{n}{S}\rfloor\times w \times \log w=n\times S
$$
解出来：
$$
S=\sqrt{w \times \log w}
$$
取 $S=1024$ 跑得比较快。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,M=66005,S=320;
const double pi2=2.0*acos(-1);
int n,a[N],ans,len=(1<<16),siz,st[S],ed[S],id[N],cnt[M];
struct cp{
	double a,b;
	cp operator + (const cp &x){
		return {a+x.a,b+x.b};
	}
	cp operator - (const cp &x){
		return {a-x.a,b-x.b};
	}
	cp operator * (const cp &x){
		return {a*x.a-b*x.b,a*x.b+b*x.a};
	}
}f[M],g[M],w[M];
void fft(cp a[],int n,int ty){
	for(int i=0,j=0;i<n;i++){
		if(i<j)swap(a[i],a[j]);
		for(int k=n>>1;(j^=k)<k;k>>=1); 
	}
	w[0]={1.0,0.0};
	for(int p=1;p<n;p<<=1){
		cp now={cos(pi2/(p*2)),ty*sin(pi2/(p*2))};
		for(int i=(p<<1)-2;i>=0;i-=2){
			w[i]=w[i>>1];w[i+1]=w[i]*now; 
		}
		for(int i=0;i<n;i+=(p<<1)){
			for(int j=i;j<i+p;j++){
				cp x=a[j],y=w[j-i]*a[j+p];
				a[j]=x+y,a[j+p]=x-y;
			}
		}
	}
	if(ty==-1){
		double c=1.0/n;
		for(int i=0;i<n;i++)a[i].a*=c,a[i].b*=c;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	siz=1024;
	for(int i=1;i<=n;i++){
		id[i]=id[i-1];
		if((i-1)%siz==0){
			id[i]++;st[id[i]]=i;
		}
		ed[id[i]]=i;
	}
	for(int i=1;i<=id[n];i++){
		if(i>1&&i<id[n]){
			for(int j=0;j<len;j++){
				f[j].a=f[j].b=g[j].a=g[j].b=0;
			}
			for(int j=1;j<st[i];j++){
				f[a[j]].a+=1.0;
			}
			for(int j=ed[i]+1;j<=n;j++){
				g[a[j]].a+=1.0;
			}
			fft(f,len,1),fft(g,len,1);for(int j=0;j<len;j++)f[j]=f[j]*g[j];
			fft(f,len,-1);
           // 计算第 i 块的贡献
		}
		for(int j=st[i];j<=ed[i];j++){
			if(i>1&&i<id[n]){
				ans+=(int)(f[2*a[j]].a+0.5);
			}
			for(int k=ed[i];k>j;k--){
				if(2*a[j]-a[k]>=0){
					ans+=cnt[2*a[j]-a[k]];//左端点在块内
				}
			}
			cnt[a[j]]++;//左右都在块内只能算一遍
		}
	}
	for(int i=0;i<=len;i++)cnt[i]=0;
	for(int i=id[n];i>=1;i--){
		for(int j=ed[i];j>=st[i];j--){
			for(int k=j-1;k>=st[i];k--){
				if(2*a[j]-a[k]>=0){
					ans+=cnt[2*a[j]-a[k]];//右端点在块内
				}
			}
		}
		for(int j=ed[i];j>=st[i];j--){
			cnt[a[j]]++;
		}
	}
	cout<<ans;
	return 0;
}
```

---

