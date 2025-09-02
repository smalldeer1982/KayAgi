# [AGC045F] Division into Multiples

## 题目描述

东海帝皇在赢下日本达比，夺得第二冠后，获得了 $X+Y$ 个球。其中 $X$ 个球上写着整数 $A$ ，另外 $Y$ 个球上写着整数 $B$ 。

东海帝皇将这些球分成了若干组。每个球恰好只属于其中的一组，且每组球的个数可以为一个或者多个（不能没有） 。

如果一组球中所有写在球上的整数之和是整数 $C$ 的倍数时，则该组被称为 **闪耀的组合** 。

她现在想知道将这堆球进行分组之后，得到的组合中最多能有多少个 **闪耀的组合** 。

## 样例 #1

### 输入

```
3
3 3 4 4 5
2 1 1 5 3
3 1 4 2 5```

### 输出

```
2
2
0```

# 题解

## 作者：jun头吉吉 (赞：3)

## 题意
给定 $A,X,B,Y,C$ 有 $X$ 个球上面数字是 $A$，$Y$ 个球上面数字是 $B$，一个组是好的当且仅当组不为空且内部的球的和是 $C$ 的倍数，求最多有几个好的组。

$T$ 组数据。

$1\le T\le 2\times 10^4,1\le A,B,C\le 10^9,A\ne B$。

## 题解

很厉害的题。但是比E清爽很多。

首先我们可以让 $A,B,C$ 互质，通过下面的步骤：

1. $d=\gcd(A,B),A\leftarrow A/d,B\leftarrow B/d,C\leftarrow (\mathrm{lcm}(C,d))/d$，此时 $\gcd(A,B)=1$
2. $d=\gcd(A,C)$，若 $Ax+By\equiv 0\pmod C$，所以 $Ax+By\equiv0\pmod d$，显然有 $Ax\equiv 0\pmod d$，因此 $By\equiv 0\pmod d$，也就是 $d|By$，因为 $\gcd(A,B)=1$，所以 $\gcd(d,B)=1$，所以 $d|y$。然后我们就可以 $A\leftarrow A/d,C\leftarrow C/d,Y\leftarrow\lfloor Y/d\rfloor$
3. 对 $B,C$ 重复上面的过程。

到现在，我们已经可以保证 $\gcd(A,B),\gcd(B,C),\gcd(A,C)$ 都是 $1$ 了。

记一个组为 $(i,j)$ 表示有 $i$ 个 $A$ 球和 $j$ 个 $B$ 球。

然后考虑一个好的组 $(i,j)$ 满足 $Ai+Bj\equiv 0\pmod C$，也就是 $j=-\frac ABi\bmod C$，记 $D=A/B\bmod C$，那么就是 $(0,C),(1,(-D)\bmod C),\dots,(i,(-iD)\bmod C)$。

如果存在 $(x_1,y_1),(x_2,y_2)$ 满足 $x_1< x_2,y_1\le y_2$，那么第二组就是没用的，换句话说我们要维护 $C,-D\bmod C,\dots,-iD\bmod C$ 的前缀最小值。

考虑如果当前 $C\ge D$，那么令 $t=\lfloor C/D\rfloor$，那么接下来就会是 $C,C-D,\dots,C-tD$。显然这一段都是前缀最小值。

然后我们令 $C'=C-tD=C\bmod D$，接下来只有在这一段内部的才会成为前缀最小值。考虑当前是 $0\le x\le C'$，那么下一次出现在在 $[0,C')$ 一定是 $(x-D)\bmod C'$，所以可以让 $D'=D\bmod C'$。注意如果 $D\bmod C'=0$ 则 $D'=C'$。然后就变成了 $C',(-D')\bmod C',\dots,(-iD')\bmod C'$ 的前缀最小值。这是一个子问题。

然后观察这个过程就是欧几里得，复杂度 $\mathcal O(\log C)$。所以所有前缀最小值被划分成了 $\mathcal O(\log C)$ 个等差数列，所有的点也形成 $\mathcal O(\log C)$ 个等差数列，并且每一段 $x$ 的公差和 $y$ 的公差都是递增的。（$x$ 的公差为正，$y$ 的公差为负）。

最后我们来证明答案一定可以在同一个等差数列上取到。考虑如果不是同一个，那么同时在 $i$ 和 $j$ 两段等差数列上有（$i<j$），分别是 $x$ 和 $y$（因为前一段的最后一个是后一段的第一个，我们钦定 $x$ 不能是最后一个，$y$ 不能是第一个），把 $x$ 后一一个点，$y$ 前移一个点，$\Delta X=dx_i-dx_j<0,\Delta Y=dy_i-dy_j<0$，都变得更优了。最后肯定可以把所有点都移动到同一段等差数列上。

所以我们只要求一段等差数列的情况即可。假设这个等差数列是 $(ax,ay),(ax+dx,ay-dy),\dots,(ax+cnt\times dx,ay-cnt\times dy)$，那么我们二分个数，假设当前是 $mid$，那么存在构造 $mid$ 组的方案当且仅当 $\exist t\in \mathbb N,t\le cnt\times mid,ax\times mid+t\times dx\le X,ay\times mid-t\times dy\le Y$，显然可以 $\mathcal O(1)$ 判断。

复杂度 $\mathcal O(T\log^2 V)$，其中 $V$ 是值域。

## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
#define pc putchar
#define chkmx(a,b) (a)=max((a),(b))
#define chkmn(a,b) (a)=min((a),(b))
#define fi first
#define se second
using namespace std;
template<class T>
void read(T&x){x=0;char c=getchar();bool f=0;for(;!isdigit(c);c=getchar())f^=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<class T,class ...ARK>void read(T&x,ARK&...ark){read(x);read(ark...);}
template<class T>void write(T x){if(x<0)pc('-'),x=-x;if(x>=10)write(x/10);pc(x%10+'0');}
template<class T,class ...ARK>void write(T x,ARK...ark){write(x);pc(' ');write(ark...);}
template<class ...ARK>void writeln(ARK...ark){write(ark...);pc('\n');}
typedef long long ll;
const int mod=998244353;
struct mint{
	int x;mint(int o=0){x=o;}mint&operator+=(mint a){return(x+=a.x)%=mod,*this;}mint&operator-=(mint a){return(x+=mod-a.x)%=mod,*this;}
	mint&operator*=(mint a){return(x=1ll*x*a.x%mod),*this;}mint&operator^=( int b){mint a=*this;x=1;while(b)(b&1)&&(*this*=a,1),a*=a,b>>=1;return*this;}
	mint&operator/=(mint a){return*this*=(a^=mod-2);}friend mint operator+(mint a,mint b){return a+=b;}friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}friend mint operator/(mint a,mint b){return a/=b;}friend mint operator^(mint a, int b){return a^=b;}
	mint operator-(){return 0-*this;}bool operator==(const mint b)const{return x==b.x;}
};
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rint(int l,int r){return uniform_int_distribution<int>(l,r)(rnd);}
#define lowbit(x) ((x)&-(x))
#define mid ((l+r)>>1)
#define lc (x<<1)
#define rc (x<<1|1)
int T,a,x,b,y,c,d,s,D,iD,ans;
//D=a/b,iD=b/a
void exgcd(int a,int b,int&x,int&y){
	if(!b)return x=1,y=0,void();
	exgcd(b,a%b,y,x);y-=(a/b)*x;
}
int inv(int x,int p){
	int a,b;exgcd(x,p,a,b);
	return (a%p+p)%p;
}
ll divup(ll x,int y){
	//x/y向上取整
	return x<=0?0:(x+y-1)/y;
}
ll divdw(ll x,int y){
	//x/y向下取整
	return x<0?-1:x/y;
}
void calc(int ay,int dy,int cnt){
	//ay,ay-dy,ay-dy*2,...,ay-dy*cnt
	//ax,ax+dx,ax+dx*2,...,ax+dx*cnt
	int ax=(c-1ll*ay*iD%c)%c;
	int dx=1ll*dy*iD%c;
	int l=0,r=x+y;
	while(l<=r){
		//是否存在t使得：
		//ax*mid+t*dx<=x
		//ay*mid-t*dy<=y
		//0<=t<=cnt*mid
		if(divup(1ll*ay*mid-y,dy)<=min(divdw(x-1ll*ax*mid,dx),1ll*cnt*mid))chkmx(ans,mid),l=mid+1;
		else r=mid-1;
	}
}
signed main(){
	read(T);while(T--){
		read(a,x,b,y,c);
		d=__gcd(a,b);
		c/=__gcd(c,d),a/=d,b/=d;
		d=__gcd(a,c);
		y/=d,a/=d,c/=d;
		d=__gcd(b,c);
		x/=d,b/=d,c/=d;
		if(c==1){writeln(x+y);continue;}
		D=1ll*a*inv(b,c)%c;
		iD=1ll*b*inv(a,c)%c;
		int cc=c,dd=D;ans=0;
		while(1){
			calc(cc,dd,cc/dd);
			cc%=dd;
			if(cc)dd=(dd-1)%cc+1;
			else break;
		}
		writeln(ans);
	}
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# AGC045F 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_agc045_f)

**题目大意**

> $q$ 组询问，给 $X$ 个数字 $a$ 和 $Y$ 个数字 $b$，求能将这些数字划分成多少组，使得的数字和都是 $c$ 的倍数的组尽可能多。
>
> 数据范围：$q\le 2\times 10^4,a,b,X,Y,C\le10^9$。

**思路分析**

首先观察，若 $\gcd(a,b)=d\ne 1$，那么可以构造子问题：$a\gets a/d,b\gets b/d, c\gets \mathrm{lcm}(c,d)/d$。

若 $\gcd(a,c)=d\ne 1$ 且 $\gcd(a,b)=1$，那么显然每一个组里 $b$ 的数量都是 $d$ 的倍数，那么可以构造子问题：$a\gets a/d,c\gets c/d,Y\gets \lfloor Y/d\rfloor$。

同理处理 $\gcd(b,c)\ne 1$ 的情况，最终可以构造一个等价问题使得 $a,b,c$ 两两互质。

记 $q=a\times b^{-1}\bmod c$，那么每一组里 $a,b$ 元素的个数一定形如：$(x,x\times q\bmod c)$（余数为 $0$ 时取 $c$）。

显然如果存在 $x_1<x_2$ 满足 $x_1\times q\bmod c<x_2\times q\bmod c$，那么 $x_2$ 一定不优，因此所有合法决策随着 $x$ 递增，$y$ 递减。

那么考虑最前面连续的一段：$(0,c)\sim (\lfloor q/c\rfloor ,c\bmod q)$，这一段里的元素构成等差数列，然后考虑下一个合法段的 $y$ 坐标：只需要考虑 $<c'=c\bmod q$ 的坐标，由因 $q\mid c-c'$，因此我们直接取 $q'=q\bmod c'$ 依然能求出所有合法的 $y$ 坐标，我们只要这样递归子问题即可。

容易发现这就是辗转相除法的过程，因此所有合法决策构成的等差数列是 $\mathcal O(\log V)$ 级别的，并且斜率递减，即构成下凸壳。

观察发现我们选定的所有决策一定在下凸壳的同一条边上，否则把两个决策相向调整可以得到两维都更优的解。

因此我们求出每个等差数列，对每个等差数列在上面二分一个阈值 $k$，设等差数列形如 $(x_0,y_0)\sim (x_0+n\Delta_x,y_0-n\Delta_y)$。

把所有 $\Delta$ 偏移量的和设为 $s$，合法条件就是：$s\le kn$，$kx_0+s\Delta_x\le X$ 且 $ky_0-s\Delta_y\le Y$，直接判断即可。

时间复杂度 $\mathcal O(q\log^2V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
void exgcd(ll a,ll b,ll &x,ll &y) {
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x),y-=(a/b)*x;
} 
ll inv(ll a,ll p) {
	ll x,y; exgcd(a,p,x,y);
	return (x%p+p)%p;
}
ll divceil(ll x,ll y) { return x<0?0:(x+y-1)/y; }
ll divfloor(ll x,ll y) { return x<0?-1:x/y; }
void solve() {
	ll a,x,b,y,c,d;
	cin>>a>>x>>b>>y>>c;
	d=__gcd(a,b),a/=d,b/=d,c/=__gcd(c,d);
	d=__gcd(a,c),a/=d,c/=d,y/=d;
	d=__gcd(b,c),b/=d,c/=d,x/=d;
	if(c==1) return cout<<x+y<<"\n",void();
	ll k=a*inv(b,c)%c,ik=inv(k,c),ans=0;
	function<ll(ll,ll,ll)> calc=[&](ll ay,ll dy,ll cnt) {
		ll ax=(c-ay*ik%c)%c,dx=dy*ik%c;
		ll l=0,r=x+y,res=0;
		function<bool(ll x)> check=[&](ll n) {
			//0<=p<=n*cnt, ax*n+p*dx<=x, ay*n-p*dy<=y
			return divceil(ay*n-y,dy)<=min(divfloor(x-ax*n,dx),n*cnt);
		};
		while(l<=r) {
			ll mid=(l+r)>>1;
			if(check(mid)) l=mid+1,res=mid;
			else r=mid-1;
		}
		return res;
	};
	for(ll u=c,v=k;;) {
		ans=max(ans,calc(u,v,u/v));
		u%=v; if(!u) break;
		v%=u; if(!v) v+=u;
	}
	cout<<ans<<"\n";
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

