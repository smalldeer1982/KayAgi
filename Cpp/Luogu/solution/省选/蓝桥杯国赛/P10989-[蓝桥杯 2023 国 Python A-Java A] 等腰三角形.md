# [蓝桥杯 2023 国 Python A/Java A] 等腰三角形

## 题目背景

Python 用户建议使用 PyPy3 提交本题。

## 题目描述

给定一个包含 $n$ 个数的序列 $A_i$，每次操作可以选择其中任意一个数将其
$+1$ 或 $−1$。

我们要让这个序列满足能够从中任选三个数，这三个数对应长度的三条边总能组成一个等腰三角形。问最少需要多少次操作才能让序列满足条件。


## 说明/提示

对于 $40\%$ 的评测用例，$n \le 5000,A_i \le5000$；

对于 $70\%$ 的评测用例，$n \le 2 \times 10^5,A_i \le 10^6$；

对于所有评测用例，$1 \le n \le 2 \times 10^5,1 \le A_i \le 10^9$。

#### 样例解释

将原序列修改为 $4, 4, 4, 7, 7$ 即可。


## 样例 #1

### 输入

```
5
3 3 5 7 7
```

### 输出

```
3
```

# 题解

## 作者：北文 (赞：10)

upd:8.29一个细节挂了被撤回了。  
根据等腰三角形的性质，满足的序列一定只有一种数字，两种不同的数字。一种数字比较 trivial，下面只考虑两种数字的。设这两种数字分别为 $x,y$，不防钦定大小关系 $x<y$，
则还需要满足 $x+x>y$。  

假设我们一开始就钦定最终的 $x,y$ ，那么需要的代价是 
$$\sum_i \min(|a_i-x|, |a_i-y|)$$  

我们把数字全放在数轴上，这个式子的含义就是：在这个数轴上选取两个原点 (也就是上文中的$x,y$)，求和数轴上的点到这两个原点距离的较小值。  
一个显然的想法是，一定能分成两部分，使得左半部分到达 $x$ 点更近，而右半部分到达 $y$ 更近。  
我们枚举这个分界线，对于左边部分，显然是取到中位数的点最优，右半部分同理。  
为什么要取中位数？学过初中的零点分段都知道....  

如果满足 $x+x>y$ 则直接更新答案，但这样得出的 $x,y$ 并不一定满足 $x+x>y$ 的要求。  
 
如果不满足，则我们需要 $x$ 向右调整，或者 $y$ 向左调整。
如果 $x$ 向右调整了 $k$ 格，那么 $y$ 能取到的范围可以确定，即  
$$y<2\times(x+k)$$   
而由于越靠近中位数，所求式子越小，我们可以直接令   
$$y'=\min(y, 2\times(x+k)-1)$$  
因此我们把调整后的代价看做一个函数 $f(k)$ ，通过人类智慧可以猜出他是单谷函数，因此可以用三分解决。  
既然这是题解那我们还是需要证明一下的。  
考虑设   
$$f(k)=L(k)+R(k)$$  
$L(k),R(k)$ 分别表示左右部分的贡献。当我们将 $x$ 向右移动的时候， $x$ 左边的点会不断增多，也就是说 $L'(k)$ （ $L$ 函数的导函数，增量）是**单调不减**的。这里可能有一点难理解，你可以试着想想在一个数轴上移动 $x$，距离和的**增量**会不断变大。同理，$R(k)$ 函数类似 $L(k)$ 函数反过来，通过同样的分析可以得到 $R'(k)$ 也是**单调不减**的，因此原函数的导函数 $f'(k)=L'(k)+R'(k)$ 也是**单调不减**的，所以 $f(k)$ 是单谷函数。  
直到这里，我们可以设计程序了。  
1.枚举一个分割点，分成左部分和右部分。  
2.求出两部分的中位数，看看是否合法。  
3.若合法，直接更新答案，否则三分求出最小的点，再更新。  
但这题还有一个 corner case，若最终变成的 $x,y$ 其中**成为** $x$ 的只有一个数，则不需要 $x+x<y$ 的限制，特判掉即可。  
有点省选联考 D1T1 的感觉。  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5, inf=1e9;
using ll=long long;
int n, a[N];
ll ans=1ll*inf*inf, s[N];
ll calc(int l, int r, int x) {
	int f=upper_bound(a+l, a+r+1, x)-a-1;
	ll lp=f-l+1, rp=r-f;
	return (lp*x-(s[f]-s[l-1]))+(s[r]-s[f]-rp*x);
}
void solve(int mid, int x, int y) {
	int l=0, r=inf;
	while(l+20<=r) {
		int lp=l+(r-l)/3;
		int rp=lp+(r-l)/3;
		ll lans=(calc(1, mid, x+lp)+calc(mid+1, n, min(x+lp+x+lp-1, y))), 
		   rans=(calc(1, mid, x+rp)+calc(mid+1, n, min(x+rp+x+rp-1, y)));
		if(lans<rans) r=rp;
		else l=lp;
	}
	ll res=1ll*inf*inf;
	for(int i=l; i<=r; i++) {
		res=min(res, calc(1, mid, x+i)+calc(mid+1, n, min(x+i+x+i-1, y)));
	}
		
	ans=min(ans, res);
	return ;
}
int main() {
	scanf("%d", &n);
	for(int i=1; i<=n; i++)
		scanf("%d", &a[i]);
	sort(a+1, a+1+n);
	for(int i=1; i<=n; i++)
		s[i]=s[i-1]+a[i];
	
	for(int i=1; i<n; i++) {
		int x=a[i/2+1], y=a[(n-i+1)/2+i];
		if(x+x>y) ans=min(ans, calc(1, i, x)+calc(i+1, n, y));
		else solve(i, x, y);
	}
	ans=min(ans, calc(2, n, a[1+(n-1)/2]));
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Amadeus004 (赞：4)

挺好的一道整数三分。

根据题目要求，操作后的数列中只有不多于两种数。一种数的情况可以归入两种数，不作讨论。设这两种分别为 $x,y(x<y)$。

我们要做的事就很明显了：先排序，枚举一个分界点，将分界点前的数跟分界点后的数分别推平为 $x,y$，计算推平的代价并选出最小值。

推平的代价很好计算。预处理出 $a_i$ 的前缀和 $pre_i$，假设我们要将 $[l,r]$ 推平为 $x$，二分出一个点 $pos$，使 $\forall i<pos,a_i<x$，则推平的代价为 
$$g(l,r,x)=(pos-l)x-pre_{pos-1}-pre_{l-1}+pre_r-pre_{pos-1}-(r-pos+1)x$$

现在的问题是如何选取合适的 $x$ 和 $y$。考虑函数
$$y=\sum_{i=1}^n |x-a_i|$$
它是下凸函数，图像由若干段一次函数拼接而成，如下图

![](https://cdn.luogu.com.cn/upload/image_hosting/lijk7s2s.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

注意到当 $x$ 取 $\{a\}$ 的中位数时，$y$ 有最小值，证明如下：
由不等式 
> $|x-a|+|x-b|\ge b-a(a<b)$，当且仅当 $x\in[a,b]$ 时等号成立

可知 $y$ 取最小值时不等式组 
$$\begin{array}
|x-a_1|+|x-a_n|\ge a_n-a_1\\
|x-a_2|+|x-a_{n-1}|\ge a_{n-1}-a_2\\
\cdots
\end{array}$$

等号同时成立，即
$$\begin{cases}
x=a_{\frac{n+1}{2}},n为奇数 \\
x\in[a_{\frac{n}{2}},a_{\frac{n}{2}+1}],n为偶数
\end{cases}$$
也就是 $x$ 取 $\{a\}$ 的中位数时 $f(x)$ 取最小值。

设推平的分界点为 $pos$，按照这个结论，我们不妨令 $x$ 为 $[1,pos]$ 的中位数，$y$ 为 $[pos+1,n]$ 的中位数，对 $x$ 与 $y$ 的关系进行分讨：
1. 若 $x$ 为等腰三角形的底边：
	 $x$ 与 $y$ 间没有任何约束条件，数列中有且仅有一个 $x$，令 $x=a_1,y=a_{\frac{n-1}{2}+1}$，计算将 $[2,n]$ 推平为 $y$ 的代价即可。
2. 若 $x$ 为等腰三角形的腰：
	此时需要满足 $2x>y$，若 $x$ 与 $y$ 已经满足该条件，则直接计算答案；若不满足，则意味着我们需要对 $x,y$ 进行调整。

    同时对 $x,y$ 调整较为麻烦，由于只调整 $x$ 与只调整 $y$ 是等价的，考虑只调整 $x$。

   将 $x$ 向右调整为 $x'$。调整的过程中存在调整后仍不满足条件的情况，此时可以将 $y$ 向左调整，即 $y'=2x'-1$。

   统一一下，则有 $y'=\min(y,2x'-1)$。
	调整后的代价为 $f(x)=g(1,pos,x')+g(pos+1,n,y')$，由上文可知，该函数是下凸的，所以可以用三分解决调整的过程。

## _**Code**_
```cpp
#include<bits/stdc++.h>
namespace solve{
	#define ll long long
	inline ll read(){
		ll x=0,t=1;
		char a;
		while(!isdigit(a=getchar()))t=a=='-'?-1:t;
		do{x=(x<<3)+(x<<1)+(a^48);}while(isdigit(a=getchar()));
		return x*t;
	}
	inline void write(ll x){
		if(x<0)putchar('-'),x=-x;
		if(x>9)write(x/10);
		putchar(x%10+48);
	}
	const ll N=1e6+5,mod=998244353,LEN=450;
	int n,m;
	ll a[N],pre[N],ans=1e18;
	inline ll calc(int l,int r,ll x){
		int pos=std::upper_bound(a+l,a+r+1,x)-a;
		return (pos-l)*x-(pre[pos-1]-pre[l-1])+pre[r]-pre[pos-1]-(r-pos+1)*x;
	}
	inline ll f(int pos,ll x,ll y){
		ll ans=1e18,l=x,r=y;
		while(r-l>=114){
			ll lmid=l+(r-l)/3,rmid=r-(r-l)/3,lans=calc(1,pos,lmid)+calc(pos+1,n,std::min(y,(lmid<<1ll)-1)),
			rans=calc(1,pos,rmid)+calc(pos+1,n,std::min(y,(rmid<<1ll)-1));
			lans>rans?l=lmid:r=rmid;
		}
		for(ll i=l;i<=r;i++)ans=std::min(ans,calc(1,pos,i)+calc(pos+1,n,std::min(y,(i<<1ll)-1)));
		return ans;
	}
	inline void main(){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		std::sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)pre[i]=pre[i-1]+a[i];
		for(int i=1;i<=n;i++){
			ll x=a[(i>>1)+1],y=a[i+(n-i+1>>1)];
			if((x<<1ll)>y)ans=std::min(ans,calc(1,i,x)+calc(i+1,n,y));
			else ans=std::min(ans,f(i,x,y));
		}
		ans=std::min(ans,calc(2,n,a[1+(n-1>>1)]));
		write(ans);
	}
}
int main(){return solve::main(),0;}
```

---

