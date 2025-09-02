# Azuki loves coloring

## 题目描述

NEKOPARA Vol.3 发售之后，在新作中不是主角的 Azuki 终于可以休息了。为了打发时间，她开始给一个由 $n$ 个格子组成的序列涂色，每个格子可以涂黑白灰三种颜色之一。为了美观，Azuki 希望序列中没有两个黑色的格子相邻，也没有两个白色的格子相邻。这样的序列有很多，Azuki 定义每个序列的权值是其中一个黑色格子和一个白色格子相邻的情况的出现次数，如序列“灰黑白黑”的权值为 $2$。Azuki 想知道，对于满足 $0\le i\le k$ 的每一个 $i$，长度为 $n$ 且权值为 $i$ 的序列有多少种。由于答案很大，因此她只需要知道答案 $\text{mod }998244353$ 的值就可以了。Azuki 答应你，如果你解决了这个问题，她就可以给你做~~美味的蛋糕吃~~。


## 说明/提示

对于 $30\%$ 的测试点，$n,k\le 100$。

对于 $50\%$ 的测试点，$n,k\le 5000$，时限 $1s$。其余测试点时限 $5s$。

对于 $70\%$ 的测试点，$n,k\le 60000$。

对于 $100\%$ 的测试点，$n\le 10^{18},k\le 100000$。


## 样例 #1

### 输入

```
3 3```

### 输出

```
11 4 2 0```

## 样例 #2

### 输入

```
20 10```

### 输出

```
1398101 4582670 8103780 10126770 9931780 8075094 5618340 3422330 1841460 893790 383524```

# 题解

## 作者：11Dimensions (赞：8)

对于 $50\%$ 的数据，$n,k\le5000$。这一部分测试点可以递推（DP）解决。

首先可以注意到，对于任何一个序列，我们可以将其中的白色与黑色互换，得到的是一个权值与原序列相同的合法序列，因此白色与黑色的情况完全对称，不需要单独为其设计状态。

令 $f_{n,i},g_{n,i}$ 分别为长度为 $n$、权值为 $i$ 且最后一个格子分别为为黑色和灰色的合法序列的个数，则有如下递推式：

$$ \begin{aligned} f_{n,i}&=f_{n-1,i-1}+g_{n-1,i}\\g_{n,i}&=2f_{n-1,i}+g_{n-1,i}\end{aligned} $$

依以上两式可以在 $O(nk)$ 时间内计算出答案 $2f_{n,i}+g_{n,i}$。


对于 $100\%$ 的数据，我们要进一步思考。

首先，由以上递推式，有

$$g_{n-1,i}-g_{n-2,i}=2f_{n-2,i}$$

考虑 $f_{n,i}-f_{n-1,i}$，有

$$\begin{aligned} f_{n,i}-f_{n-1,i} &= f_{n-1,i-1}+g_{n-1,i}-f_{n-2,i-1}-g_{n-2,i}\\ &= f_{n-1,i-1}-f_{n-2,i-1}+2f_{n-2,i} \end{aligned}$$

即
$f_{n,i}=f_{n-1,i}+f_{n-1,i-1}-f_{n-2,i-1}+2f_{n-2,i}$

这样，我们就得到了一个 $f$ 关于自身的递推式。

令 $F_n(x)=\sum f_{n,i}x^i$，则上式等价于

$F_n(x)=(1+x)F_{n-1}(x)+(2-x)F_{n-2}(x)$

其中边界条件为 $F_0(x)=0,F_1(x)=1$。

仿照二阶线性递推数列通项公式的推导过程，我们可以猜想$F_n(x)$具有以下形式：

$F_n(x)=C_0(x)\Lambda_0(x)^n+C_1(x)\Lambda_1(x)^n$

其中 $C_0(x),C_1(x)$ 为待定幂级数，而 $\Lambda_0(x),\Lambda_1(x)$ 可由下式确定：

$$\Lambda(x)^2=(1+x)\Lambda(x)+(2-x)$$

可以得到

$$\begin{aligned}\Lambda_0(x)&=\frac{1+x+\sqrt{9-2x+x^2}}{2}\\ \Lambda_1(x)&=\frac{1+x-\sqrt{9-2x+x^2}}{2}\end{aligned}$$

并利用初始条件解出 $C_0(x),C_1(x)$，最终可以得到

$$F_n(x)=\frac{\left(\frac{1+x+\sqrt{9-2x+x^2}}{2}\right)^n-\left(\frac{1+x-\sqrt{9-2x+x^2}}{2}\right)^n}{\sqrt{9-2x+x^2}}$$

可以使用 NTT 在 $O(k\log k)$ 时间内计算 $F_n(x)$。

要计算 $g_{n,i}$，只需注意到

$$g_{n,i}-f_{n,i}=2f_{n-1,i}-f_{n-1,i-1}$$

就可以得到

$$g_{n,i}=f_{n,i}+2f_{n-1,i}-f_{n-1,i-1}$$

因此也只需计算 $F_n(x)$ 与 $F_{n-1}(x)$ 就可以计算出 $g$。


综上，我们在 $O(k\log k)$ 的时间内解决了这个问题。


---

## 作者：myee (赞：4)

### 前言

好吧其实这题时限略大，我暴力线性递推都跑过去了。

大概讲一下做法，代码就只放暴力的了。

---
### 思路

你考虑一个考虑：先搞黑白，再做黑白灰。

用二元生成函数表示状态。

第一维表示占位数，第二维表示贡献。

很容易写出就是：

$$
1+2\sum_kx^{k+1}y^{k}=1+{2x\over1-xy}
$$

再考虑枚举灰色个数，得到：

$$
f=\sum_kx^k(1+{2x\over1-xy})^{k+1}={1-x(y-2)\over1-x(y+1)+x^2(y-2)}
$$

$[x^ny^0]f,[x^ny^1]f,[x^ny^2]f,\dots,[x^ny^k]f$ 就是我们的答案。

于是以 $x$ 为主元来搞，考虑把含 $y$ 的多项式看做 $x$ 的系数，显然就是一个对于多项式的线性递推形式。

你大力卡常，跑过去了！复杂度 $O(k\log k\log n)$。

---
（下面都是口胡，没有写代码，应该是对的）

考虑正解。

上面的做法你放计算器里大力计算一下前 $21$ 项可以得到[这么个震撼的东西](https://www.luogu.com.cn/paste/o2sm79pd)（未排版），和样例吻合，所以思路应该没错。

考虑使用**有理分式的一般分解定理**做。

待定系数，设一设，可以分解成这种鬼样：

记 $\Delta=y^2-2y+9$

$$
f={1\over2\sqrt\Delta}\Bigg({y-5-\sqrt\Delta\over1-{y+1+\sqrt\Delta\over2}x}+{y-5+\sqrt\Delta\over1-{y+1-\sqrt\Delta\over2}x}\Bigg)
$$

于是 $[x^n]f$ 就是：

$${1\over2\sqrt\Delta}\Bigg(\Big(y-5-\sqrt\Delta\Big)\Big({y+1+\sqrt\Delta\over2}\Big)^n+\Big(y-5+\sqrt\Delta\Big)\Big({y+1-\sqrt\Delta\over2}\Big)^n\Bigg)$$

使用多项式 sqrt 搞 $\sqrt\Delta$，用 ln/exp 搞快速幂。

复杂度 $O(k\log k)$，（应该）可以轻松通过。

细节有点多，又没有写代码，如果算错了请在评论区指出，谢谢！

---
### Code

放第一种做法的卡常版本。

```cpp
// Problem: P3789 Azuki loves coloring
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3789
// Memory Limit: 500 MB
// Time Limit: 1000 ms

#include <algorithm>
#include <stdio.h>
#include <vector>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
template<typename T>T power(T base,T index,T mod){return((index<=1)?(index?base:1):(power(base*base%mod,index>>1,mod)*power(base,index&1,mod)))%mod;}
template<typename T>T lowbit(T n){return n&-n;}
template<typename T>T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T>T lcm(T a,T b){return(a!=0||b!=0)?a/gcd(a,b)*b:(T)0;}
template<typename T>T exgcd(T a,T b,T&x,T&y){if(!b)return y=0,x=1,a;T ans=exgcd(b,a%b,y,x);y-=a/b*x;return ans;}
template<const ullt p=998244353>
class mod_ullt
{
    private:
        ullt v;
        ullt chg(ullt w){return(w<p)?w:w-p;}
        mod_ullt _chg(ullt w){mod_ullt ans;ans.v=(w<p)?w:w-p;return ans;}
        voi _print(ullt v){if(v>=10)_print(v/10);putchar('0'+v%10);}
    public:
        mod_ullt():v(0){}
        mod_ullt(ullt v):v(v%p){}
        bol empty(){return!v;}
        ullt val(){return v;}
        bol friend operator<(mod_ullt a,mod_ullt b){return a.v<b.v;}
        bol friend operator>(mod_ullt a,mod_ullt b){return a.v>b.v;}
        bol friend operator<=(mod_ullt a,mod_ullt b){return a.v<=b.v;}
        bol friend operator>=(mod_ullt a,mod_ullt b){return a.v>=b.v;}
        bol friend operator==(mod_ullt a,mod_ullt b){return a.v==b.v;}
        bol friend operator!=(mod_ullt a,mod_ullt b){return a.v!=b.v;}
        mod_ullt friend operator+(mod_ullt a,mod_ullt b){return a._chg(a.v+b.v);}
        mod_ullt friend operator-(mod_ullt a,mod_ullt b){return a._chg(a.v+a.chg(p-b.v));}
        mod_ullt friend operator*(mod_ullt a,mod_ullt b){return a.v*b.v;}
        mod_ullt friend operator/(mod_ullt a,mod_ullt b){return b._power(p-2)*a.v;}
        mod_ullt friend operator-(mod_ullt a){return a._chg(p-a.v);}
        mod_ullt sqrt()
        {
            if(power(v,(p-1)>>1,p)!=1)return 0;
            mod_ullt b=1;do b++;while(b._power((p-1)>>1)==1);
            ullt t=p-1,s=0,k=1;while(!(t&1))s++,t>>=1;
            mod_ullt x=_power((t+1)>>1),e=_power(t);
            while(k<s)
            {
                if(e._power(1llu<<(s-k-1))!=1)x*=b._power((1llu<<(k-1))*t);
                e=_power(p-2)*x*x,k++;
            }
            return _min(x,-x),x;
        }
        mod_ullt inv(){return _power(p-2);}
        mod_ullt _power(ullt index){mod_ullt ans(1),w(v);while(index){if(index&1)ans*=w;w*=w,index>>=1;}return ans;}
        voi read(){v=0;chr c;do c=getchar();while(c>'9'||c<'0');do v=(c-'0'+v*10)%p,c=getchar();while(c>='0'&&c<='9');v%=p;}
        voi print(){_print(v);}
        voi println(){_print(v),putchar('\n');}
        mod_ullt operator++(int){mod_ullt ans=*this;return v=chg(v+1),ans;}
    public:
        ullt&operator()(){return v;}
        mod_ullt&operator+=(mod_ullt b){return*this=_chg(v+b.v);}
        mod_ullt&operator-=(mod_ullt b){return*this=_chg(v+chg(p-b.v));}
        mod_ullt&operator*=(mod_ullt b){return*this=v*b.v;}
        mod_ullt&operator/=(mod_ullt b){return*this=b._power(p-2)*v;}
        mod_ullt&operator++(){return v=chg(v+1),*this;}
};
template<const ullt p=998244353,const ullt g=3>
class poly_NTT
{
    public:
		typedef mod_ullt<p>modint;
	private:
		std::vector<modint>V;
	public:
		class NTT
		{
			private:
				std::vector<uint>T;std::vector<modint>G;
			public:
				uint size(){return T.size();}
				voi bzr(uint len)
				{
					uint n=1;while(n<len)n<<=1;
                    modint w=power(g,(p-1)/n,p);T.resize(n),G.resize(n),T[0]=0,G[0]=1;
					for(uint i=1;i<n;i++)T[i]=((i&1)?n|T[i>>1]:T[i>>1])>>1,G[i]=G[i-1]*w;
				}
				voi ntt(std::vector<modint>&x,bol op)
				{
					uint n=size();if(x.size()<n)x.resize(n);
                    for(uint i=0;i<n;i++)if(T[i]<i)std::swap(x[i],x[T[i]]);
					for(uint i=1;i<n;i<<=1)for(uint j=0;j<n;j+=i<<1)for(uint k=0;k<i;k++)
					{
						modint t=x[i+j+k]*G[n/(2*i)*k];x[i+j+k]=x[j+k]-t,x[j+k]+=t;
					}
					if(op)
					{
						for(uint i=1;i*2<n;i++)std::swap(x[i],x[n-i]);
						modint t=modint(n).inv();for(uint i=0;i<n;i++)x[i]*=t;
					}
				}
				modint Omega(uint n){return G[n];}
		};
	public:
		poly_NTT(){}
		poly_NTT(uint n){V.resize(n);}
		poly_NTT(std::vector<modint>V):V(V){}
		voi bzr(){V.clear();}
		voi push(modint v){V.push_back(v);}
		voi pop(){V.pop_back();}
		voi cut_zero(){while(!V.empty()&&V.back().empty())V.pop_back();}
		voi chg_siz(uint n){V.resize(n);}
		voi chg_deg(uint n){V.resize(n+1);}
		bol empty(){return cut_zero(),V.empty();}
		uint size(){return V.size();}
		uint deg(){return V.size()-1;}
		modint val(uint n){return(n<size())?V[n]:0;}
        std::vector<modint>GET(){return V;}
        poly_NTT reverse()
        {
            poly_NTT ans;for(uint i=size()-1;~i;i--)ans.push(V[i]);
            return ans;
        }
		friend poly_NTT operator+(poly_NTT a,poly_NTT b)
		{
			if(a.size()<b.size())a.chg_siz(b.size());
			for(uint i=0;i<b.size();i++)a[i]+=b[i];
			a.cut_zero();return a;
		}
		friend poly_NTT operator+(poly_NTT a,modint v)
		{
			if(!a.size())a.chg_siz(1);
			a[0]+=v;return a;
		}
		friend poly_NTT operator+(modint v,poly_NTT a)
		{
			if(!a.size())a.chg_siz(1);
			a[0]+=v;return a;
		}
		friend poly_NTT operator-(poly_NTT a){return a*modint(p-1);}
		friend poly_NTT operator-(poly_NTT a,poly_NTT b)
		{
			if(a.size()<b.size())a.chg_siz(b.size());
			for(uint i=0;i<b.size();i++)a[i]-=b[i];
			a.cut_zero();return a;
		}
		friend poly_NTT operator-(poly_NTT a,modint v)
		{
			if(!a.size())a.chg_siz(1);
			a[0]-=v;return a;
		}
		friend poly_NTT operator-(modint v,poly_NTT a)
		{
			if(!a.size())a.chg_siz(1);
			a[0]-=v;return-a;
		}
		friend poly_NTT operator*(poly_NTT a,poly_NTT b)
		{
            std::vector<modint>&A=a.V,&B=b.V;NTT s;s.bzr(A.size()+B.size());
            s.ntt(A,0),s.ntt(B,0);for(uint i=0;i<s.size();i++)A[i]*=B[i];
            s.ntt(A,1),a.cut_zero();return a;
		}
        friend poly_NTT operator*(poly_NTT A,modint b)
        {
            for(auto&s:A.V)s*=b;
            return A;
        }
        friend poly_NTT operator*(modint b,poly_NTT A)
        {
            for(auto&s:A.V)s*=b;
            return A;
        }
        friend poly_NTT operator<<(poly_NTT a,uint k)
        {
        	poly_NTT ans;ans.chg_siz(k);for(auto v:a.V)ans.push(v);
        	return ans;
        }
        friend poly_NTT operator>>(poly_NTT a,uint k)
        {
        	poly_NTT ans;for(uint i=k;i<a.size();i++)ans.push(a[i]);
        	return ans;
        }
        friend poly_NTT sub_mul(poly_NTT a,poly_NTT b)
        {
            uint len=(a=a.reverse()).size();
            std::vector<modint>&A=a.V,&B=b.V;
            NTT s;s.bzr(len+B.size());
            s.ntt(A,0),s.ntt(B,0);for(uint i=0;i<s.size();i++)A[i]*=B[i];
            s.ntt(A,1),a.chg_siz(len),a=a.reverse();return a;
        }
        poly_NTT inv(){return inv(size());}
        poly_NTT inv(uint prec)
        {
            std::vector<modint>ans;NTT s;ans.push_back(V[0].inv());
            for(uint tp=1;tp<=prec;tp<<=1)
            {
                std::vector<modint>f(tp<<1),t=ans;
                for(uint i=0;i<(tp<<1);++i)f[i]=val(i);
                s.bzr(tp<<1),s.ntt(f,0),s.ntt(t,0);
                for(uint i=0;i<(tp<<1);++i)f[i]=1-f[i]*t[i];
                s.ntt(f,1);
                for(uint i=0;i<tp;++i)f[i]=f[i+tp],f[i+tp]=0;
                s.ntt(f,0);
                for(uint i=(tp<<1)-1;~i;--i)f[i]*=t[i];
                s.ntt(f,1),ans.resize(tp<<1);
            	for(uint i=0;i<tp;++i)ans[i+tp]=f[i];
            }
            ans.resize(prec);return ans;
        }
        poly_NTT diff()
        {
            poly_NTT ans;for(uint i=1;i<size();i++)ans.push(i*V[i]);
            return ans;
        }
        poly_NTT inte()
        {
            if(!size())return*this;
            poly_NTT ans(size()+1);ans[1]=1;
            for(uint i=2;i<=size();i++)ans[i]=-ans[p%i]*(p/i);
            for(uint i=1;i<=size();i++)ans[i]*=V[i-1];
            return ans;
        }
        poly_NTT ln(){return ln(size());}
        poly_NTT ln(uint prec)
        {
            poly_NTT a=this->diff()*this->inv(prec);a.chg_siz(prec),a=a.inte(),a.chg_siz(prec);return a;
        }
        poly_NTT exp(){return exp(size());}
        poly_NTT exp(uint prec)
        {
            poly_NTT ans;std::vector<modint>Inv;ans.push(1),Inv.push_back(1);
            for(uint tp=1;tp<=prec;tp<<=1)
            {
                std::vector<modint>f,ff=ans.diff().V;
                for(uint i=0;i<(tp<<1);i++)f.push_back(val(i));
                f[0]=1;NTT s;s.bzr(tp<<2);s.ntt(ans.V,0),s.ntt(Inv,0);
                for(uint i=0;i<(tp<<2);i++)Inv[i]*=2-Inv[i]*ans[i];
                s.ntt(Inv,1),Inv.resize(tp);s.ntt(Inv,0);
                for(uint i=0;i<(tp<<2);i++)Inv[i]*=2-Inv[i]*ans[i];
                s.ntt(Inv,1),Inv.resize(tp<<1);s.ntt(Inv,0);s.ntt(ff,0);
                for(uint i=0;i<(tp<<2);i++)ff[i]*=Inv[i];
                s.ntt(ff,1);f=(f-poly_NTT(ff).inte()).V;s.ntt(f,0);
                for(uint i=0;i<(tp<<2);i++)ans[i]*=f[i];
                s.ntt(Inv,1),s.ntt(ans.V,1),ans.chg_siz(tp<<1);
            }
            ans.chg_siz(prec);return ans;
        }
        friend poly_NTT operator/(poly_NTT a,poly_NTT b)
        {
            a.cut_zero(),b.cut_zero();if(a.size()<b.size())return poly_NTT();
            poly_NTT ans=a.reverse()*b.reverse().inv(a.size()-b.size()+1);
            ans.chg_siz(a.size()-b.size()+1);return ans.reverse();
        }
        friend poly_NTT operator%(poly_NTT a,poly_NTT b){return a-a/b*b;}
	public:
		modint&operator[](uint n){return V[n];};
        poly_NTT&operator+=(poly_NTT b)
        {
			if(size()<b.size())chg_siz(b.size());
			for(uint i=0;i<b.size();i++)V[i]+=b[i];
			cut_zero();return*this;
        }
        poly_NTT&operator+=(modint v)
        {
        	if(!size())chg_siz(1);
        	V[0]+=v;return*this;
        }
        poly_NTT&operator-=(poly_NTT b)
        {
			if(size()<b.size())chg_siz(b.size());
			for(uint i=0;i<b.size();i++)V[i]-=b[i];
			cut_zero();return*this;
        }
        poly_NTT&operator-=(modint v)
        {
        	if(!size())chg_siz(1);
        	V[0]-=v;return*this;
        }
        poly_NTT&operator*=(poly_NTT b)
        {
            std::vector<modint>&A=V,&B=b.V;
            NTT s;s.bzr(A.size()+B.size());
            s.ntt(A,0),s.ntt(B,0);
            for(uint i=0;i<s.size();i++)A[i]*=B[i];
            s.ntt(A,1),cut_zero();return*this;
        }
        poly_NTT&operator*=(modint v)
        {
        	for(auto&t:V)t*=v;
			return*this;
        }
        poly_NTT&operator/=(poly_NTT b){return*this=*this/b;}
        poly_NTT&operator%=(poly_NTT b){return*this=*this%b;}
        poly_NTT&operator<<=(uint v){return*this=*this<<v;}
        poly_NTT&operator>>=(uint v){return*this=*this>>v;}
};
template<const ullt p=998244353,const ullt g=3>
class poly_eval
{
    public:
		typedef mod_ullt<p>modint;typedef poly_NTT<p,g>poly;
    private:
        std::vector<poly>G,User;std::vector<modint>X;
        voi mult_eval_dfs1(uint u,uint l,uint r)
        {
            if(l+1==r){G[u].push(1),G[u].push(-X[l]);return;}
            uint mid=(l+r)/2;mult_eval_dfs1(u<<1,l,mid),mult_eval_dfs1(u<<1|1,mid,r),G[u]=G[u<<1]*G[u<<1|1];
        }
        voi mult_eval_dfs2(uint u,uint l,uint r)
        {
            User.back().chg_siz(r-l);
            if(l+1==r){X[l]=User.back().val(0);return;}
            uint mid=(l+r)/2;
            User.push_back(sub_mul(User.back(),G[u<<1|1])),mult_eval_dfs2(u<<1,l,mid);
            User.back()=sub_mul(User[User.size()-2],G[u<<1]),mult_eval_dfs2(u<<1|1,mid,r);
            User.pop_back();
        }
    public:
        voi mult_eval(poly P,std::vector<modint>&X)
        {
            if(X.empty())return;
            G.resize(X.size()<<2),User.clear(),this->X=X;
            mult_eval_dfs1(1,0,X.size());
            User.push_back(sub_mul(P,G[1].inv(std::max<uint>(P.size(),X.size())+1)));
            mult_eval_dfs2(1,0,X.size());
            G.clear(),User.clear(),X=this->X,this->X.clear();
        }
};
template<const ullt p=998244353,const ullt g=3>
class poly_inter
{
    public:
		typedef mod_ullt<p>modint;typedef poly_NTT<p,g>poly;typedef poly_eval<p,g>eval;
    private:
        std::vector<poly>Lim,F,G;eval E;std::vector<modint>X,H;
        voi dfs(uint l,uint r)
        {
            if(l+1==r)
            {
                F.push_back(poly()),F.back().push(H[l]),G.push_back(poly()),G.back().push(-X[l]),G.back().push(1);return;
            }
            uint mid=(l+r)>>1;dfs(l,mid),dfs(mid,r);
            F[F.size()-2]=F[F.size()-2]*G.back()+F.back()*G[G.size()-2],F.pop_back(),G[G.size()-2]*=G.back(),G.pop_back();
        }
    public:
        poly fast_inter(std::vector<modint>X,std::vector<modint>Y)
        {
            uint n=std::min(X.size(),Y.size());if(!n)return poly();
            X.resize(n),Y.resize(n),this->X=X;poly P;Lim.clear();
            for(uint i=0;i<n;i++)
            {
                P.bzr(),P.push(-X[i]),P.push(1);
                uint w=lowbit(i+1);while(w>>=1)P*=Lim.back(),Lim.pop_back();
                Lim.push_back(P);
            }
            P=Lim.back(),Lim.pop_back();while(Lim.size())P*=Lim.back(),Lim.pop_back();
            E.mult_eval(P.diff(),X),H.resize(n);for(uint i=0;i<n;i++)H[i]=Y[i]/X[i];
            F.clear(),G.clear(),dfs(0,n);
            poly ans=F.back();F.clear(),G.clear(),this->X.clear(),H.clear();return ans;
        }
};
const ullt Mod=998244353,g=3;
typedef mod_ullt<Mod>modint;
typedef poly_NTT<Mod,g>poly;
typedef poly_eval<Mod,g>eval;
typedef poly_inter<Mod,g>inter;
// 高斯消元没有精神，暴力维护分式基才是你们的 老 大 哥！  -- E.I.
// 牛逼题，似乎只有二元生成函数推起来简单点。
// But it's still A DIRTY WORK!
// [x^ny^k](1+(2-y)x)/(1-x(y+1)+x^2(y-2))
// 苦痛。开始还试图暴力展开这个柿子。
// 结果前 21 项：
// 1
// +3*x
// +(2*y+5)*x^2
// +(2*y^2+4*y+11)*x^3
// +(2*y^3+4*y^2+14*y+21)*x^4
// +(2*y^4+4*y^3+18*y^2+32*y+43)*x^5
// +(2*y^5+4*y^4+22*y^3+44*y^2+82*y+85)*x^6
// +(2*y^6+4*y^5+26*y^4+56*y^3+130*y^2+188*y+171)*x^7
// +(2*y^7+4*y^6+30*y^5+68*y^4+186*y^3+324*y^2+438*y+341)*x^8
// +(2*y^8+4*y^7+34*y^6+80*y^5+250*y^4+492*y^3+834*y^2+984*y+683)*x^9
// +(2*y^9+4*y^8+38*y^7+92*y^6+322*y^5+692*y^4+1374*y^3+2028*y^2+2202*y+1365)*x^10
// +(2*y^10+4*y^9+42*y^8+104*y^7+402*y^6+924*y^5+2074*y^4+3552*y^3+4914*y^2+4852*y+2731)*x^11
// +(2*y^11+4*y^10+46*y^9+116*y^8+490*y^7+1188*y^6+2950*y^5+5636*y^4+9186*y^3+11620*y^2+10622*y+5461)*x^12
// +(2*y^12+4*y^11+50*y^10+128*y^9+586*y^8+1484*y^7+4018*y^6+8360*y^5+15418*y^4+22996*y^3+27218*y^2+23056*y+10923)*x^13
// +(2*y^13+4*y^12+54*y^11+140*y^10+690*y^9+1812*y^8+5294*y^7+11804*y^6+24042*y^5+40500*y^4+56966*y^3+62892*y^2+49762*y+21845)*x^14
// +(2*y^14+4*y^13+58*y^12+152*y^11+802*y^10+2172*y^9+6794*y^8+16048*y^7+35522*y^6+65844*y^5+105306*y^4+138632*y^3+144034*y^2+106796*y+43691)*x^15
// +(2*y^15+4*y^14+62*y^13+164*y^12+922*y^11+2564*y^10+8534*y^9+21172*y^8+50354*y^7+100932*y^6+178734*y^5+267972*y^4+333706*y^3+326852*y^2+228166*y+87381)*x^16
// +(2*y^16+4*y^15+66*y^14+176*y^13+1050*y^12+2988*y^11+10530*y^10+27256*y^9+69066*y^8+147860*y^7+284866*y^6+473088*y^5+673658*y^4+793788*y^3+736290*y^2+485448*y+174763)*x^17
// +(2*y^17+4*y^16+70*y^15+188*y^14+1186*y^13+3444*y^12+12798*y^11+34380*y^10+92218*y^9+208916*y^8+432502*y^7+781084*y^6+1236242*y^5+1669684*y^4+1870638*y^3+1647276*y^2+1029162*y+349525)*x^18
// +(2*y^18+4*y^17+74*y^16+200*y^15+1330*y^14+3932*y^13+15354*y^12+42624*y^11+120402*y^10+286580*y^9+631690*y^8+1224440*y^7+2113970*y^6+3178444*y^5+4093850*y^4+4369200*y^3+3663570*y^2+2174820*y+699051)*x^19
// +(2*y^19+4*y^18+78*y^17+212*y^16+1482*y^15+4452*y^14+18214*y^13+52068*y^12+154242*y^11+383524*y^10+893790*y^9+1841460*y^8+3422330*y^7+5618340*y^6+8075094*y^5+9931780*y^4+10126770*y^3+8103780*y^2+4582670*y+1398101)*x^20
// +...
// <del>验证了样例。</del>
// /yun
// 极度不可做。
// 于是退而求其次。
// 以 x 为主元搞。
// 观察到柿子形如分式。
// 系数可以线性递推 (在 y 的一元多项式环 P(y) 上)
// 可以上 常系数齐次线性递推 / 矩阵快速幂。
uint k;
std::vector<modint>base[2],ans[2]; // 主元式的二元多项式
int main()
{
	ullt n;uint k;
	scanf("%llu%u",&n,&k);
	base[0].resize(k+1),base[1].resize(k+1);
	ans[0].resize(k+1),ans[1].resize(k+1);
	ans[0][0]=1,base[1][0]=1;
	poly::NTT s;s.bzr((k+2)<<1);
	while(n)
	{
		s.ntt(base[0],0);
		s.ntt(base[1],0);
		if(n&1)
		{
			s.ntt(ans[0],0);
			s.ntt(ans[1],0);
			for(uint i=0;i<s.size();i++)
			{
				modint v=ans[1][i]*base[1][i];
				ans[1][i]=ans[1][i]*base[0][i]+ans[0][i]*base[1][i],
				ans[0][i]*=base[0][i];
				ans[1][i]+=v+v*s.Omega(i);
				ans[0][i]+=v*2-v*s.Omega(i);
			}
			s.ntt(ans[0],1);
			s.ntt(ans[1],1);
			ans[0].resize(k+1);
			ans[1].resize(k+1);
		}
		for(uint i=0;i<s.size();i++)
		{
			modint v=base[1][i]*base[1][i];
			base[1][i]*=2*base[0][i],
			base[0][i]*=base[0][i];
			base[1][i]+=v+v*s.Omega(i);
			base[0][i]+=v*2-v*s.Omega(i);
		}
		s.ntt(base[0],1);
		s.ntt(base[1],1);
		base[0].resize(k+1);
		base[1].resize(k+1);
		n>>=1;
	}
	for(uint i=0;i<=k;i++)(ans[0][i]+ans[1][i]*3).print(),putchar(" \n"[i==k]);
    return 0;
}
```



---

## 作者：ldxcaicai (赞：3)

来写一个 $\text{gf}$ 推法。

首先发现黑白格子不能连着俩一样，所以一定是形成一段黑白链加一段灰交替出现，不妨将灰格子和黑白链进行捆绑，考虑用 $x$ 记录已形成序列的长度，$y$ 记录当前序列的权值，这样的话可以列出单个捆绑对象的生成函数：$\frac{x}{1-x}*\frac{2x}{1-xy}=\frac{2x^2}{(1-x)(1-xy)}$

现在无非是想用捆绑对象来生成序列，所以先整上一个 $\frac{1}{1-\frac{2x^2}{(1-x)(1-xy)}}$，然后发现在这样拼接完后可以在尾部再填上灰色格子，遂再乘上 $\frac1{1-x}$，即求 $[x^{n+1}]\frac{1-xy}{(1-x)(1-xy)-2x^2}=[x^{n+1}]\frac{1-xy}{1-x(y+1)-x^2(2-y)}$

是一个系数为 $y$ 多项式的线性递推，可以直接做也可以尝试大力解二次方程做分式分解。

代码再说。

---

## 作者：NaCly_Fish (赞：3)

updated，补充说明 $\Theta(k)$ 的算法。

分别设 $f_{n,k}$ 和 $g_{n,k}$ 为 长度为 $n$、权值为 $k$，且最后一格为黑、灰色的方案数。

因为黑、白其实是等价的，考虑倒数第二格是否为灰色，分两种情况加起来能得到
$$f_{n,k}=f_{n-1,k-1}+g_{n-1,k} \quad(1)$$
$$g_{n,k}=2f_{n-1,k}+g_{n-1,k} \quad(2)$$
答案就是将两部分合并：$2f_{n,k}+g_{n,k}$

将 $(2)$ 式移项可以得到 $f$ 只关于 $g$ 的式子，即
$$2f_{n-1,k}=g_{n,k}-g_{n-1,k}$$
对 $f_n$ 做差分可以得到直接计算 $f$ 的式子
$$f_{n,k}-f_{n-1,k}=f_{n-1,k-1}-f_{n-2,k-1}+g_{n-1,k}-g_{n-2,k}$$
$$f_{n,k}-f_{n-1,k}=f_{n-1,k-1}-f_{n-2,k-1}+2f_{n-2,k}$$
设 $F_n(x)$ 为 $\{ f_{n,k} \}_{k=0}^\infty$ 的生成函数，很容易得出
$$F_n(x)=F_{n-1}(x)+xF_{n-1}(x)-xF_{n-2}(x)+2F_{n-2}(x)$$
$$F_n(x)=(1+x)F_{n-1}(x)+(2-x)F_{n-2}(x)$$
****
由于实数和多项式的运算是类似的，任意实数的等式，替换为多项式后依然成立。

所以就能照搬 实数线性递推求通项公式 的办法来做，设
$$F_n(x)=c_1u_1^n+c_2u_2^n$$
解特征方程
$$u^2-(1+x)u-(2-x)=0$$
$$u=\frac{1+x \pm \sqrt{x^2-2x+9}}{2}$$
根据 $F_0(x),F_1(x)$ 列方程组可以求 $c_1,c_2$  
（可以认为  $u_1$ 中取加号 ）
$$\begin{cases} c_1+c_2=0 \\ c_1u_1+c_2u_2=1\end{cases}$$
解得
$$F_n(x)=(x^2-2x+9)^{-1/2}(u_1^n-u_2^n)$$

再根据最初的递推式，整理可得答案的生成函数为
$$(2-x)F_n(x)+F_{n+1}(x)$$

所以只需要计算 $F_n(x)$ 和 $F_{n+1}(x)$ 的系数即可。使用一些多项式科技（多项式快速幂）来计算的话，$\Theta(k \log k)$ 的时间复杂度足以通过本题。

当然还可以更快，将在下文中介绍。
****
算 $F_n(x)$ 和 $F_{n-1}(x)$ 是很类似的，我们只用考虑算 $F_n(x)$ 的方法。由于 $u_1,u_2$ 均为代数幂级数，$F_n(x)$ 是微分有限的，其系数可以整式递推计算。

由于 $u_1$ 和 $u_2$ 来自同一个代数方程，$u_1^n$ 和 $u_2^n$ 所满足的常微分方程（ODE）也应该是相同的。

设 $h=x^n$，它满足 ODE $xh'=nh$。而 $u$ 可根据其代数方程得出（使用多项式 exgcd）

$$u'=\frac{(5-x)-(1-x)u}{9-2x+x^2}$$
设 $H=u^n$，相应的 ODE 为（计算的第二步中，把 $u'$ 用 $u$ 的整式代替；第三步中把 $1/u$ 用 $u$ 的整式代替，同样是使用 exgcd 来求出的）
$$\begin{aligned}uH' &= nu'H \\ (9-2x+x^2)uH' &= n((5-x)-(1-x)u)H \\ (9-2x+x^2)(-2+x)H' &= n((7+x)-(5-x)u)H \end{aligned}$$
对等式两边再求导，并把 $u'$ 用 $u$ 表示，$H'$ 用 $H$ 表示得到：
$$(2 - x)^2 (9 - 2x +x^2)^2H''=n(P_0(x)+P_1(x)u)H$$
其中
$$P_0(x)=-59 + 99 n+(11 - 31 n)x+(-5 + 13 n)x^2-(3 + n)x^3$$
$$P_1(x)=37 - 45 n+(-23 + 19 n)x+(11 - 7 n)x^2+(-1 + n)x^3$$
只需要将 $H'$ 和 $H''$ 线性组合后，得到的关于 $H$ 的式子不含 $u$ 就可以了：
$$\begin{aligned}(5 - x) (x-2) (9 -2x +x^2)H'' & + \\((37 - 45 n)+(-23 + 19 n)x+(11 - 7 n)x^2+(-1 + n)x^3)H' & + \\ ((-2 n + 10 n^2)-(2n+2n^2)x) H &= 0 \end{aligned}$$

当然还要算出 $A=(x^2-2x+9)^{-1/2}H$ 所满足的 ODE，由于前面乘的这个东西满足一阶 ODE，$A$ 和 $H$ 一样满足二阶 ODE。而这个的计算流程相对简洁，就是求导两次后把高阶导用低阶来代换，最终得到 $A$ 的 ODE。

递推式在代码中可以看出来，就不再写一遍了。时间复杂度为 $\Theta(k)$。
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define N 100005
#define ll long long
#define p 998244353
using namespace std;

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int inv[N];

int P[5][3];

inline int eval(const int& t,const int& x){
    return (((ll)P[t][2]*x+P[t][1])%p*x+P[t][0])%p;
}

void solve(int *f,ll _n,int k){
    int n = _n%p;
    P[0][0] = 1+n,P[0][1] = -2-n,P[0][2] = 1;
    P[1][0] = (2ll*n*n+n-1)%p,P[1][1] = 7ll*n%p,P[1][2] = -9;
    P[2][0] = (13-3ll*n-10ll*n*n)%p,P[2][1] = (24-19ll*n)%p,P[2][2] = 33;
    P[3][0] = (-57+45ll*n)%p,P[3][1] = (-140+45ll*n)%p,P[3][2] = -83;
    int pw = power(2,_n%(p-1))%p,sgn = (_n&1)?-1:1;
    f[0] = 332748118ll*(pw-sgn)%p;
    f[1] = ((2+3ll*n)*pw+2ll*sgn*(-1+6ll*n))%p*240318085%p;
    k = min((ll)k,_n-1);
    for(int i=0;i+2<=k;i++){
        int tmp = 0;
        for(int j=max(2-i,0);j<4;++j) tmp = (tmp+(ll)eval(j,i)*f[i-2+j])%p;
        f[i+2] = -144190851ll*tmp%p*inv[i+1]%p*inv[i+2]%p; // 144190851 is inverse of 90 (mod 998244353)
    }
}

int f[N],g[N];
ll n;
int k;

int main(){
    scanf("%lld%d",&n,&k);
    inv[1] = 1;
    for(int i=2;i<=k+1;++i) inv[i] = -(ll)(p/i)*inv[p%i]%p;
    solve(f,n,k),solve(g,n+1,k);
    for(int i=k;i;--i) f[i] = (2ll*f[i]-f[i-1]+g[i])%p;
    f[0] = (2ll*f[0]+g[0])%p;
    for(int i=0;i<=k;++i) printf("%d ",f[i]>=0?f[i]:f[i]+p);
    return 0; 
}


```

---

## 作者：SqrT_Pow (赞：0)

因为是黑题五题+CSDN100 赞纪念日，所以写一波题解。

[盐酸溶解黑题](https://blog.csdn.net/2401_82353457/article/details/150111829?spm=1001.2014.3001.5501)

由于本题明显涉及到了两个需要控制的变量，也就是序列长度和序列权值，我们引入**二元生成函数**，用 $x$ 的指数表示长度，用 $y$ 的指数表示权值。

序列上可以被划分成两种极长连续段的交错组合：**黑白段和灰色段**。**两个黑白段之间必然存在非空灰色段**，我们把灰色段和黑白段打包并写出**生成函数**：

$$F(x,y)=\frac{1}{1-x}\cdot\frac{2x}{1-xy}$$

生成函数就是这个样子：

$$\frac{1}{1-F}\cdot \frac{1}{1-x}=\frac{1-xy}{1-x(y+1)+(y-2)x^2)}$$

我们此时把问题简化成了这样：

$$[x^{n+1}]\frac{1-xy}{1-(y+1)x+(y-2)x^2}(\bmod\ y^{k+1})$$

**如果把 $x$ 看作是主元，则我们实际上算的就是一个常系数齐次线性递推数列的远处的值**，因此理论上来说可以直接套用那个算法。

但是，作为学过初中小蓝本的同学，我们应当可以熟练地对于分母进行因式分解并直接得到通项，就像处理 Fibonacci 数列的生成函数那样。

$$\Delta=y^2-2y+9$$
$$\phi=\frac{y+1+\sqrt{\Delta}}{2}$$
$$\hat{\phi}=\frac{y+1-\sqrt{\Delta}}{2}$$

用待定系数法求得：

$$\frac{1-xy}{1-(y+1)x+(y-2)x^2}=\frac{1}{2\sqrt{\Delta}}(\frac{\sqrt{\Delta}+1-y}{1-\phi x}+\frac{\sqrt{\Delta}+y-1}{1-\hat{\phi} x})$$

经过亿点点变换，得到：

$$\frac{1}{2\sqrt{\Delta}}((\sqrt{\Delta}+1-y)(\frac{y+1+\sqrt{\Delta}}{2})^{n+1}+(\sqrt{\Delta}+y-1)(\frac{y+1-\sqrt{\Delta}}{2})^{n+1}))(\bmod\ y^{k+1})$$

直接硬算即可，需要用到多项式开根和多项式快速幂，然而最终复杂度仍然是 $O(k\log k)$ 的。

小结：

1. 适时引入新的元来表达必须表达的信息；

2. 推生成函数，这种不太困难的主要就是看对于组合情景理解是否到位。基本功要扎实。

3. 这样的选主元的想法比较基础；关键在于选取哪一个作主元。

不过既然这里有明确的题目背景：要求关于 $y$ 的多项式，且这个多项式还是 $x$ 的远处系数，也就不难想到让 $x$ 成为主元。

想到这一点，之后的数学运算其实也就比较基础了。

---

