# 「ALFR Round 4」D 罪人的终幕

## 题目背景

> 而我承诺你，一切都将在一场盛大的，如同戏剧般的审判中结束……  
> 小小地旋转，轻轻地跳跃，然后便是「罪人」的谢幕。

## 题目描述

定义函数 $a(x)$ 表示自然数 $x$ 的不同的质因子的和。

若 $x=\prod\limits_{p_i\in\mathbb{P}}p_i^{d_i}$，则 $a(x)=\sum\limits_{p_i\in \mathbb{P}}p_i\times[d_i\ge1]$，其中 $\mathbb{P}$ 是质数集，$a(1)=0$。

从诞生的第一天开始，Furina 便有了一个期待值 $m_1$。

在最终的审判来临前，她每天都会选择整理自己的心情，具体的方法如下：

假设今天是第 $i$ 天，Furina 会把今天的期待值 $m_i$ 定为 $\max\{\dfrac{m_j}{a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))}+k\}$，其中 $2\le i\le n$，$1\le j<i$，$k$ 是观看审判所获得的期待值。

请你求出 $\sum\limits_{i=1}^nm_i$。

## 说明/提示

### 样例解释

这 $4$ 天的期待值分别是 $4,7.285714,7.809524,8.952381$。

### 数据范围

| 子任务 | 分值 | 限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $30$ | $n,m_1,k\le10^3$，$w_i\le29$ |
| $1$ | $70$ | - |

对于 $100\%$ 的数据，$1\le n\le182376$，$1\le m_1\le10^7$，$0\le k\le10^6$，$2\le w_i\le182376$。

本题数据可能偏弱，欢迎大家提供对于错误做法的 hack。

## 样例 #1

### 输入

```
4 4 7
7 10 16 8```

### 输出

```
28.047619```

# 题解

## 作者：___Furina___ (赞：20)

感谢 @[PengAo](https://www.luogu.com.cn/user/513853) 对这篇题解的建议和修改。

### 题目大意
定义 $\operatorname{a}(n)=\sum_{p|n}p$，若 $m_i=\max_{j<i}\left\lbrace\frac{m_j}{\operatorname{a}(\operatorname{lcm}(w_i,w_j))+\operatorname{a}(\gcd(w_i,w_j))} \right\rbrace+k$，求 $\sum m_i$。
### 题解
下文以求方便，用 $f_i$ 表示 $m_i$：
$$
\begin{aligned}
f_i&=\max_{j<i}\left\lbrace\frac{f_j}{\operatorname{a}(\operatorname{lcm}(w_i,w_j))+\operatorname{a}(\gcd(w_i,w_j))}\right\rbrace+k\\
&=\min_{j<i}\left\lbrace\frac{\operatorname{a}(\operatorname{lcm}(w_i,w_j))+\operatorname{a}(\gcd(w_i,w_j))}{f_j}\right\rbrace^{-1}+k\\
&=\min_{j<i}\left\lbrace\frac{\operatorname{a}(w_iw_j)+\operatorname{a}(\gcd(w_i,w_j))}{f_j}\right\rbrace^{-1}+k\\
&=\min_{j<i}\left\lbrace\frac{\operatorname{a}(w_i)+\operatorname{a}(w_j)}{f_j}\right\rbrace^{-1}+k\\
&=\min_{j<i}\left\lbrace\frac{\operatorname{a}(w_i)}{f_j}+\frac{\operatorname{a}(w_j)}{f_j}\right\rbrace^{-1}+k\\
\end{aligned}
$$

注意到 $\min$ 里面可以用李超线段树维护，并且可以线性筛求出 $\operatorname{a}(n)$，从而 $O(n\log n) $ 解决。

关于变形的证明（以下的 $p_i$ 均为质数）：
$$
i=\prod_{p_k|i} p_k^{c_k},i'=\prod_{p_k|i} p_k,\\
\operatorname{a}(i)=\sum_{p_k|i} p_k,\operatorname{a}(i')=\sum_{p_k|i} p_k\Rightarrow \operatorname{a}(i)=\operatorname{a}(i')
$$
同理，$\operatorname{a}(j)=\operatorname{a}(j')$，设 $g'=\gcd(i',j'),g=\gcd(i,j)$，易得 $\gcd(g',\frac{i'}{g'})=1,\gcd(j',\frac{i'}{g'})=1$：
$$
\begin{aligned}
\operatorname{a}(i)+\operatorname{a}(j)&=\operatorname{a}(i')+\operatorname{a}(j')\\
&=\operatorname{a}(\frac{i'}{g'})+\operatorname{a}(j')+\operatorname{a}(g')\\
&=\operatorname{a}(i'j')+\operatorname{a}(g')\\
&=\operatorname{a}(\operatorname{lcm}(i,j))+\operatorname{a}(\gcd(i,j))
\end{aligned}
$$
证毕。

### 代码如下：
```cpp
#include<bits/stdc++.h>
#define N 200010
#define I_love_Furina return
#define forever 0
#define foreverr 1
#define Endl endl
#define endl '\n'
#define FIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define db long double
#define chc cout<<114514<<endl
#define int long long
#define lt (p<<1)
#define rt (p<<1|1)
#define mid (l+r>>1)
#define eps 1e-15
#define ma 1e9
#define day 182376
using namespace std;
int n,T,pr[N],num,w[N],t[N<<2];
db k,dp[N],d[N];
bool b[N];
struct line{db k,b;}li[N];
inline int cmp(db x,db y){
	if(fabs(x-y)<eps)I_love_Furina forever;
	I_love_Furina (x>y?1:-1);
}
inline void mk(int p){li[++num].k=1.0/dp[p],li[num].b=d[w[p]]/dp[p];}
inline db calc(int p,int x){I_love_Furina li[p].k*x+li[p].b;}
inline void upd(int p,int l,int r,int u){
	int &v=t[p],tp=cmp(calc(u,mid),calc(v,mid));
	if(tp<0)swap(u,v);
	int tpl=cmp(calc(u,l),calc(v,l)),tpr=cmp(calc(u,r),calc(v,r));
	if(tpl<0)upd(lt,l,mid,u);
	if(tpr<0)upd(rt,mid+1,r,u);
}
inline db query(int p,int l,int r,int x){
	if(l>x||r<x)I_love_Furina ma;
	db ans=calc(t[p],x);
	if(l==r)I_love_Furina ans;
	I_love_Furina min(ans,min(query(lt,l,mid,x),query(rt,mid+1,r,x)));
}
signed main(){
	IOS;//FIO("");
	n=2e5;
	d[1]=0;
	for(int i=2;i<=n;i++){
		if(!b[i])pr[++num]=i,d[i]=i;
		for(int j=1;j<=num&&i*pr[j]<=n;j++){
			b[i*pr[j]]=1;
			if(i%pr[j]==0){d[i*pr[j]]=d[i];break;}
			d[i*pr[j]]=d[i]+d[pr[j]];
		}
	}
	num=0;
	li[0].k=1145,li[0].b=100000000;
	cin>>n>>dp[1]>>k;
	for(int i=1;i<=n;i++)cin>>w[i];
	mk(1);
	//cout<<num<<" "<<li[1].k<<" "<<li[1].b<<endl;
	upd(1,1,day,1);
	for(int i=2;i<=n;i++)dp[i]=1/query(1,1,day,d[w[i]])+k,mk(i),upd(1,1,day,i);
	db sum=0;
	for(int i=1;i<=n;i++)sum+=dp[i];
	printf("%.6Lf",sum);
	I_love_Furina forever;
}
```
P.S. 本来出这道题不容易，还要求我给证明 qnq。

---

## 作者：违规用户名1425622 (赞：6)

### 1. 前言

你谷新人第一篇题解，不喜勿喷qwq。

感觉这个题挺简单也挺典的，可能是因为大部分人不会李超树所以过的人少吧，认为难度是 C>B>D>A。

### 2. 题意

$a(x)$ 表示 $x$ 的质因子和。

$m_i=\max\limits_{1 \le j <i} \frac{m_j}{a(\text{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))}+k$。

给定 $m_1$，求 $\sum\limits_{i=1}^n m_i$。

$1\le n\le182376$，$1\le m_1\le10^7$，$0\le k\le10^6$，$2\le w_i\le182376$。

### 3. 做法

先随便推一下式子，有：

$$
m_i = \max\limits_{1 \le j <i} \frac{m_j}{a(\text{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))}+k \\
=\max\limits_{1 \le j <i} \frac{m_j}{a(w_i)+a(w_j)}+k \\
=(\min\limits_{1 \le j < i} \frac{a(w_i)}{m_j}+\frac{a(w_j)}{m_j})^{-1}+k
$$

解释一下，第一步到第二步很显然，计算每个质因子贡献即可，第二步到第三步求倒数即可。

那么我们发现可以将 $\frac{a(w_j)}{m_j}$ 视为截距，$\frac{1}{m_j}$ 视为斜率，那么就相当于在一堆直线中找出一个位置上的最小点值，李超树维护即可。

还有，建议使用 `long double`。

### 4. Code

~~这个题代码这么短，不用放了吧。~~

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
#define double long double
using namespace std;
const double eps=1e-15;
int n,k;
int w[182400],p[182400],t,s[182400];
double a[182400];
bool st[182400];
pair<double,double> l[182400];
int tr[730010];
void get_prime(int x)
{
	for(int i=2;i<=x;i++){
		if(!st[i])p[++t]=i,s[i]=i;
		for(int j=1;p[j]*i<=x;j++){
			st[i*p[j]]=1;
			if(i%p[j]==0){s[i*p[j]]=s[i];break;}
			s[i*p[j]]=s[i]+p[j];
		}
	}
}
double sol(int x,int y){return l[x].x*y+l[x].y;}
int cmp(double x,double y)
{
	if(x-y>eps)return -1;
	if(y-x>eps)return 1;
	return 0;
}
void pushdown(int u,int L,int R,int num)
{
	int &x=tr[u],mid=L+R>>1;
	int m=cmp(sol(x,mid),sol(num,mid));
	if(m==-1)swap(x,num);
	int l=cmp(sol(num,L),sol(x,L)),r=cmp(sol(num,R),sol(x,R)); 
	if(l==1)pushdown(u<<1,L,mid,num);
	if(r==1)pushdown(u<<1|1,mid+1,R,num);
}
double query(int u,int L,int R,int x)
{
	if(L==R)return sol(tr[u],x);
	int mid=L+R>>1;
	double ans=sol(tr[u],x);
	if(x<=mid)ans=min(ans,query(u<<1,L,mid,x));
	else ans=min(ans,query(u<<1|1,mid+1,R,x));
	return ans;
}
inline void add(int x){l[x].x=1/a[x],l[x].y=w[x]/a[x];}
int main()
{
    ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int i;
	double ans=0;
	cin >> n >> a[1] >> k;
	get_prime(182376);
	for(i=1;i<=n;i++)cin >> w[i],w[i]=s[w[i]];
	l[0]={1e9,1e9};
	add(1);
	pushdown(1,0,182376,1);
	ans+=a[1];
	for(i=2;i<=n;i++){
		a[i]=1/query(1,0,182376,w[i])+k;
		add(i);
		pushdown(1,0,182376,i);
		ans+=a[i];
	}
	cout << fixed << setprecision(6) << ans;
}
```

---

## 作者：NATO (赞：4)

#### ~~锐评：~~

~~纯纯的唐题，感觉不是很有素质。~~

### 思路浅析：

观察到题目中的柿子，一个和 $j$ 有关的数除以一个和 $i,j$ 都有关的数，下面除掉一个和 $i,j$ 都有关的数是不好优化的，因此我们重点考虑 $a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))$ 这一坨是否能够拆成两个独立的、只和 $w_i$ 或 $w_j$ 有关的两个数的和。

$\operatorname{lcm},\gcd$ 两个函数的同时出现令我们警觉，考虑 $a(\operatorname{lcm}(w_i,w_j)),a(\gcd(w_i,w_j))$ 分别在干什么。

$a(\operatorname{lcm}(w_i,w_j))$ 计算了所有只在 $w_i$ 或 $w_j$ 中出现了的质因数的和 $1$ 次和同时在 $w_i$ 和 $w_j$ 都出现的质因数的和 $1$ 次；$a(\gcd(w_i,w_j))$ 计算了同时在 $w_i$ 和 $w_j$ 都出现的质因数的和 $1$ 次。

回过头来一看，这 TM 不就是 $w_i$ 所有质因数的和加上 $w_j$ 所有质因数的和吗！！！

我们就得到了 $a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))=a(w_i)+a(w_j)$。

剩下就可以乱做了，由于除掉一个和是不好做的，考虑改为取个倒数后取 $\min$（奇怪的是本人是被上面的 $a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))=a(w_i)+a(w_j)$ 骗了半年，取倒感觉就是很自然的想法），那么现在柿子是这样的：

$$m_i=\frac{1}{\min\limits_{j=1}^{i-1}\frac{a(w_j)+a(w_i)}{m_j}}+k$$

显然 $\min\limits_{j=1}^{i-1}\frac{a(w_j)+a(w_i)}{m_j}$ 是典型的斜率优化 $kx+b$ 的形式，令 $k=\frac{1}{m_j},b=\frac{a(w_j)}{m_j}$ 套上斜率优化即可。

#### 参考代码：

赛时因为几个神秘 $\le,<$ WA 了半天，乱改改就过了，为了偷懒直接拉了个李超树板子，时间复杂度 $n\log n$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
#define db long double
using namespace std;
const db eps=0;
ll n,k;
double m[182377];
bool vis[182377];
ll zs[182377],cnt,mz[182377],w[182377];
void init()
{
	for(ll i=2;i<=182376;++i)
	{
		if(!vis[i])zs[++cnt]=i,mz[i]=i;
		for(ll j=1;j<=cnt&&zs[j]*i<=182376;++j)
		{
			vis[zs[j]*i]=1;
			mz[zs[j]*i]=zs[j];
			if(i%zs[j]==0)break;
		}
	}
}
ll get_a(ll s)
{
	ll cot=0;
	while(s!=1)
	{
		cot+=mz[s];
		ll now=mz[s];
		while(s%now==0)s/=now;
	}
	return cot;
}
#define MAXN 182376
struct tree
{
	ll l,r;
	db k,b;
}tr[729505];
void build(ll id,ll l,ll r)
{
	tr[id].l=l;tr[id].r=r;
	tr[id].b=214748364719260817ll;
	if(l==r)return;
	ll mid=l+r>>1;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
}
db js(ll x,db k,db b)
{
	return (db)(x*1.00)*k+b;
}
struct px
{
	db y;
	px()
	{
	y=214748364719260817ll;
	}
};
px min(px a,px b)
{
	if(a.y+eps<=b.y-eps)return a;
	return b;
}
void pushdown(ll id,db k,db b)
{
	db yk=tr[id].k,yb=tr[id].b;
	ll mid=tr[id].l+tr[id].r>>1;
	db yl=js(tr[id].l,yk,yb),ymid=js(mid,yk,yb),yr=js(tr[id].r,yk,yb);
	db nl=js(tr[id].l,k,b),nmid=js(mid,k,b),nr=js(tr[id].r,k,b);
	if(nl-eps>yl+eps&&nr-eps>yr+eps)return;
	if(nl+eps<=yl-eps&&nr+eps<=yr-eps)
	{
		tr[id].k=k;tr[id].b=b;
		return;
	}
	if(nmid+eps<=ymid-eps)swap(tr[id].k,k),swap(tr[id].b,b),swap(yl,nl),swap(yr,nr);
	if(nl+eps<=yl-eps)
	pushdown(id*2,k,b);
	if(nr+eps<=yr-eps)
	pushdown(id*2+1,k,b); 
}
px query(ll id,ll ml)
{
	if(tr[id].l==tr[id].r)
	{
		px kkk;
		kkk.y=js(ml,tr[id].k,tr[id].b);
		return kkk;
	}
	px ans;
	ans.y=js(ml,tr[id].k,tr[id].b);
	if(ml<=tr[id*2].r)ans=min(ans,query(id*2,ml));
	else ans=min(ans,query(id*2+1,ml));
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init();build(1,1,MAXN);
	cin>>n>>m[1]>>k;
	for(ll i=1;i<=n;++i)cin>>w[i];
	pushdown(1,1.00/m[1],get_a(w[1])*1.00/(1.00*m[1]));
	for(ll i=2;i<=n;++i)
	{
		ll p=get_a(w[i]);
		m[i]=k+(1.00/query(1,p).y);
		pushdown(1,1.00/(m[i]*1.00),p*1.00/(1.00*m[i]));
	}
	db res=0;
	for(ll i=1;i<=n;++i)res+=m[i];
	cout<<fixed<<setprecision(10)<<res;
}
```

---

## 作者：bluedream (赞：2)

模板题。

显然 $a(\text{lcm}(i,j))+a(\gcd(i,j))=a(i)+a(j)$，可以线性筛求，我们只需要求 $m_i=\max_{j<i}\left(\dfrac{m_j}{a(w_j)+a(w_i)}\right)+k$。

令 $f_i(x)=\dfrac{m_i}{x+a(w_i)}$，这是反比例型函数，它满足任意两个不重合的此类函数的交点数量不超过 $1$ 且具有单调性，于是可以使用广义李超树维护它。

时间复杂度 $O(n\log v)$。

核心代码：
```cpp
//...
struct Func{//a/(x+b)
	db a,b;
	Func(){}
	Func(db A,db B){ a=A,b=B; }
	inline db cal(int x){
		return 1.0*a/(x+b);
	} 
}f[N];
inline int cmp(db x,db y){
	if(x-y>eps) return 1;
	if(y-x>eps) return -1;
	return 0; 
}
struct Segment_Tree{
	#define ls (rt<<1)
	#define rs (rt<<1|1)
	int ans[N<<2];
	inline int cmp(int x,int y,int p){
		if(!x||!y) return x+y;
		db f1=f[x].cal(p),f2=f[y].cal(p);
		int cm=::cmp(f1,f2);
		return cm?(cm==1?x:y):min(x,y);
	}
	inline void insert(int rt,int l,int r,int d){
		if(!ans[rt]){
			ans[rt]=d;
			return ;
		}
		int mid=l+r>>1;
		Func a=f[ans[rt]],b=f[d];
		if(cmp(ans[rt],d,mid)==d) swap(ans[rt],d);
		int fl=cmp(ans[rt],d,l),fr=cmp(ans[rt],d,r); 
		if(fl==ans[rt]&&fr==ans[rt]) return ;
		if(fl==d&&fr==d){
			ans[rt]=d;
			return ;
		}
		if(fl==d) insert(ls,l,mid,d);
		if(fr==d) insert(rs,mid+1,r,d);
	}
	inline int query(int rt,int l,int r,int p){
		int h=0;
		h=cmp(h,ans[rt],p);
		if(l==r) return h;
		int mid=l+r>>1;
		if(p<=mid) h=cmp(h,query(ls,l,mid,p),p);
		else h=cmp(h,query(rs,mid+1,r,p),p);
		return h;
	}
}T;
int main(){
//...
	f[1]=Func(m,w[1]);
	T.insert(1,1,V,1);
	s=m;
	for(int i=2;i<=n;i++){
		m=f[T.query(1,1,V,w[i])].cal(w[i])+k;
		f[i]=Func(m,w[i]);
		T.insert(1,1,V,i),s+=m;
	}
	printf("%.8Lf",s);
	flush();
}
```

---

## 作者：qnqfff (赞：2)

### 思路

注意到 $a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))$ 就等于 $a(w_i)+a(w_j)$ 证明显然，因为 $\gcd(w_i,w_j)$ 有的质因子相当于 $w_i$ 和 $w_j$ 的质因子的交集，$\operatorname{lcm}(w_i,w_j)$ 有的质因子相当于 $w_i$ 和 $w_j$ 的质因子的并集，所以两者加起来相等。

令 $p_i$ 表示 $a(w_i)$ 。

原式等于 $\max\{\dfrac{m_j}{p_i+p_j}+k\}$ 。

把那个分数取倒数变成 $\dfrac{1}{\min\{\dfrac{p_i}{m_j}+\dfrac{p_j}{m_j}\}}+k$ 。

容易看出分母是个一次函数形式，直接李超线段树维护即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9') p=p*10+c-'0',c=getchar();return p*flg;}
int n,k,w[200010],p[200010],cnt;double m[200010];struct line{double k,b;}t[1000010];
int a(int x){int res=0;for(int i=2;i*i<=x;i++) if(!(x%i)){res+=i;while(!(x%i)) x/=i;}if(x!=1) res+=x;return res;}
double calc(int u,int x){return t[u].k*x+t[u].b;}
#define lson now<<1
#define rson now<<1|1
void insert(int now,int l,int r,int u){
	if(!p[now]){p[now]=u;return ;}int mid=(l+r)>>1;
	if(calc(u,mid)<calc(p[now],mid)) swap(u,p[now]);
	if(calc(u,l)<calc(p[now],l)) insert(lson,l,mid,u);
	if(calc(u,r)<calc(p[now],r)) insert(rson,mid+1,r,u);
}
double query(int now,int l,int r,int x){
	if(!p[now]) return 1e18;
	int mid=(l+r)>>1;double res=calc(p[now],x);if(x<=mid) return min(res,query(lson,l,mid,x));else return min(res,query(rson,mid+1,r,x));
}
signed main(){
	n=read();m[1]=read();k=read();for(int i=1;i<=n;i++) w[i]=a(read());double ans=m[1];
	t[1]={1.0/m[1],1.0*w[1]/m[1]};insert(1,0,2e5,1);for(int i=2;i<=n;i++) m[i]=1.0/query(1,0,2e5,w[i])+k,t[i]={1.0/m[i],1.0*w[i]/m[i]},insert(1,0,2e5,i),ans+=m[i];printf("%.9Lf",ans);
    return 0;
}
```

---

## 作者：bluewindde (赞：1)

> 我芙伟大，无需多言。

upd 2024-09-02：LaTeX 炸了，已修。

题目定义的函数 $a$ 更常见的记法为 $\Omega$（[OEIS A008472](https://oeis.org/A008472)，容易说明其为加性函数），后文亦使用 $\Omega$。

为了好看，后文用 $a_i$ 代指题目中的 $m_i$。

题意即转化为：

> 给定整数 $n, a_1, k$ 和长为 $n$ 的整数序列 $w$，设
>
> $$a_i = \max\limits_{1 \leqslant j < i} \left\{ \frac {a_j} {\Omega(\operatorname{lcm}(w_i, w_j)) + \Omega(\gcd(w_i, w_j))} \right\} + k \qquad 2 \leqslant i \leqslant n$$
>
> 求
>
> $$\sum\limits_{i = 1}^n a_i$$
>
> $1 \leqslant n \leqslant 182376, 2 \leqslant w_i \leqslant 182376$。

对 $2 \leqslant i \leqslant n$，由（因为 $xy$ 和 $\operatorname{lcm}(x, y)$ 的质因子相同）

$$\Omega(xy) = \Omega(\operatorname{lcm}(x, y))$$

得

$$a_i = \max\limits_{1 \leqslant j < i} \left\{ \frac {a_j} {\Omega(w_i w_j) + \Omega(\gcd(w_i, w_j))} \right\} + k$$

由（容斥质因子可得）

$$\Omega(xy) = \Omega(x) + \Omega(y) - \Omega(\gcd(x, y))$$

得

$$
\begin{aligned}
a_i &= \max\limits_{1 \leqslant j < i} \left\{ \frac {a_j} {\Omega(w_i) + \Omega(w_j) - \Omega(\gcd(w_i, w_j)) + \Omega(\gcd(w_i, w_j))} \right\} + k \\
&= \max\limits_{1 \leqslant j < i} \left\{ \frac {a_j} {\Omega(w_i) + \Omega(w_j)} \right\} + k \\
\end{aligned}
$$

发现 $\Omega(w_i)$ 是定值，但位置在分母，通过取倒数让它移动到分子，即

$$
\begin{aligned}
a_i &= \max\limits_{1 \leqslant j < i} \left\{ \frac {a_j} {\Omega(w_i) + \Omega(w_j)} \right\} + k \\
&= \frac 1 {\min\limits_{1 \leqslant j < i} \left\{ \frac {\Omega(w_i) + \Omega(w_j)} {a_j} \right\}} + k \\
\end{aligned}
$$

考虑求

$$\min\limits_{1 \leqslant j < i} \left\{ \frac {\Omega(w_i) + \Omega(w_j)} {a_j} \right\}$$

发现这可以看作关于 $\Omega(w_i)$ 的一次函数，斜率为 $\frac 1 {a_j}$，截距为 $\frac {\Omega(w_j)} {a_j}$。

因为 $m_i$ 一定是正数，所以可能成为答案的一次函数的图像构成一个上凸包，李超线段树或者平衡树维护凸包即可。

时间复杂度 $O(n \log w)$，$w$ 为值域。

基于李超线段树的参考实现如下，注意本题对精度要求较高。

```cpp
#include <iomanip>
#include <iostream>

using namespace std;

typedef long double ld;

const int lim = 500 * 365;
const ld inf = 1e18;
const ld eps = 1e-15;

bool vis[lim + 5];
int pr[lim + 5], tail;
int Omega[lim + 5];

int n, k;
int w[lim];
ld a[lim];

struct line {
    ld k, b;
    inline ld get(int x) const { return k * x + b; }
} d[800005];
static inline void build(int s, int t, int p) {
    d[p].b = inf;
    if (s == t)
        return;
    int mid = (s + t) >> 1;
    build(s, mid, p << 1);
    build(mid + 1, t, p << 1 | 1);
}
static inline void insert(line nd, int s, int t, int p) {
    int mid = (s + t) >> 1;
    line l1 = nd;
    line &l2 = d[p];
    if (l1.get(mid) - l2.get(mid) < -eps)
        swap(l1, l2);
    if (l1.get(s) - l2.get(s) < -eps)
        insert(l1, s, mid, p << 1);
    if (l1.get(t) - l2.get(t) < -eps)
        insert(l1, mid + 1, t, p << 1 | 1);
}
static inline ld query(int x, int s, int t, int p) {
    ld ret = d[p].get(x);
    if (s == t)
        return ret;
    int mid = (s + t) >> 1;
    if (x <= mid)
        return min(ret, query(x, s, mid, p << 1));
    else
        return min(ret, query(x, mid + 1, t, p << 1 | 1));
}

static inline line make_line(int x) { return {1. / a[x], Omega[w[x]] / a[x]}; }

static inline void solve() {
    cin >> n >> a[1] >> k;
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    build(0, 2e5, 1);
    insert(make_line(1), 0, 2e5, 1);
    for (int i = 2; i <= n; ++i) {
        ld inv = query(Omega[w[i]], 0, 2e5, 1);
        a[i] = 1. / inv + k;
        insert(make_line(i), 0, 2e5, 1);
    }
    ld ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += a[i];
    cout << fixed << setprecision(12) << ans << endl;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("P11014.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Omega[1] = 0;
    for (int i = 2; i <= lim; ++i) {
        if (!vis[i]) {
            pr[++tail] = i;
            Omega[i] = i;
        }
        for (int j = 1; j <= tail && i * pr[j] <= lim; ++j) {
            vis[i * pr[j]] = 1;
            if (i % pr[j] == 0) {
                Omega[i * pr[j]] = Omega[i];
                break;
            }
            Omega[i * pr[j]] = Omega[i] + pr[j];
        }
    }
    solve();
    return 0;
}
```

---

## 作者：BPG_ning (赞：1)

标签有李超树，那自然是不能用李超树的（~~不会李超树~~）。

容易发现 $ a_i+a_j = a_{gcd(i,j)} +a_{lcm(i,j)} $ 。

证明很简单，因为都是 $ i,j $ 的质因子的贡献都会算两遍，只是一个的质因子的贡献都只会算一遍。

所以 $ \frac{m_j}{a_{gcd(w_i,w_j)}+a_{lcm(w_i,w_j)}} + k = \frac{m_j}{a_{w_j}+a_{w_i}} + k $ 。

令 $ a_i \gets a_{w_i} $ ,那么原式即为 $ \frac{m_j}{a_j+a_i}+k $ 。

考虑 $ \frac{m_j}{a_i+a_j} $ 的几何意义，是在平面上点 $ (a_j,m_j) $ 与点 $ (-a_i,0) $ 的斜率，显然使得斜率最大的这个点 $ (a_j,m_j) $ 在上凸包上，可以用cdq分治维护，且容易发现凸包上的决策在 $ -a_i $ 有序的情况下是单调的，可以双指针找最优决策点，时间复杂度为 $ n\log{n} $ 。

要注意的点是，维护凸包不能使用向量叉积，手算一下发现会爆，而且这题比较卡精度（对于我的做法来说），所以我们双指针过后不只对当前这个点取贡献，还要对前后 $ 2 $ 个点取贡献，就可以通过（~~颇有乱搞意味~~）。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double db;
typedef pair<int,int> pii;
const int N=2e5+10;
const db inf=1e18,eps=1e-8;
int cnt,p[N],vis[N];
int n,a[N];
db v,f[N];
int A[N],B[N];
void oula(){
    for(int i=2;i<N;i++){
        if(!vis[i]) p[++cnt]=i;
        for(int j=1;j<=cnt && 1LL*i*p[j]<N;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
void read(){
    cin>>n>>f[1]>>v;
    for(int i=1;i<=n;i++){
        int w,limw;
        cin>>w; limw=w;
        a[i]=0;
        for(int j=1;j<=cnt && 1LL*p[j]*p[j]<=limw;j++){
            if(w%p[j]==0) a[i]+=p[j];
            while(w%p[j]==0) w/=p[j];
        }
        if(w!=1) a[i]+=w;
    }
    for(int i=1;i<=n;i++) A[i]=i;
}
struct node{
    db x,y;
    node(db xx=0,db yy=0){x=xx; y=yy;}
    node operator + (const node &E) const {
        return node(x+E.x,y+E.y);
    }
    node operator - (const node &E) const {
        return node(x-E.x,y-E.y);
    }
    db operator * (const node &E) const {
        return x*E.y-y*E.x;
    }
};
db slope(node a,node b){
    if(a.x==b.x){
        if(a.y<b.y) return inf;
        else return -inf;
    }
    return (a.y-b.y)/(a.x-b.x);
}
int top;
node st[N];
bool cmp(int i,int j){
    if(a[i]<a[j]) return 1;
    if(a[i]>a[j]) return 0;
    return (f[i]<f[j]);
}
void sol(int l,int r){
    if(l==r) return ;
    int mid=(l+r)>>1,i,j;
    sol(l,mid);
    top=0;
    for(int k=l;k<=mid;k++){
        i=A[k];
        node p=node(a[i],f[i]);
        while(top>1 && slope(st[top-1],p)-slope(st[top-1],st[top])>eps) top--;
        st[++top]=p;
    }
    j=1;
    for(int k=mid+1;k<=r;k++){
        i=A[k];
        node p=node(-a[i],0);
        while(j<top && slope(st[j+1],p)-slope(st[j],p)>eps) j++;
        f[i]=max(f[i],slope(p,st[j])+v);
        if(j+1<=top) f[i]=max(f[i],slope(p,st[j+1])+v);
        if(j+2<=top) f[i]=max(f[i],slope(p,st[j+2])+v);
        if(j-1>=1) f[i]=max(f[i],slope(p,st[j-1])+v);
        if(j-2>=1) f[i]=max(f[i],slope(p,st[j-2])+v);
    }
    sol(mid+1,r);
    i=l; j=mid+1;
    for(int k=l;k<=r;k++){
        if(j==r+1 || (i!=mid+1 && cmp(A[i],A[j]))) B[k]=A[i++];
        else B[k]=A[j++];
    }
    for(int k=l;k<=r;k++) A[k]=B[k];
}
void out(){
    db ans=0;
    for(int i=1;i<=n;i++){
        ans+=f[i];
    }
    cout<<fixed<<setprecision(7)<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    freopen("nzq.in","r",stdin);
    freopen("nzq.out","w",stdout);
    oula();
    read();
    sol(1,n);
    out();
    cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
    return 0;
}
```

---

## 作者：operator_ (赞：0)

# P11014 「ALFR Round 4」D 罪人的终幕

[题目传送门](https://www.luogu.com.cn/problem/P11014)

## 题解

~~感觉出题人本意是想卡双 $\log$ 的，但还是被我艹过去了~~。

鉴定为板子。先把数论皮剥掉，容易发现 $a(\operatorname{lcm}(w_i,w_j))+a(\operatorname{gcd}(w_i,w_j))=a(w_i)+a(w_j)$，那么我们直接记 $x_i=a(w_i)$，这个 $x$ 随便求。

考虑式子 $m_i=\max\{\dfrac{m_j}{x_i+x_j}\}+k=\max\{\dfrac{m_j-0}{x_j-(-x_i)}\}+k$，其实就是认为每个 $i$ 对应一个点 $(x_i,m_i)$，然后求与 $(-x_i,0)$ 构成的斜率最大的直线。这个显然维护凸包即可，而像本题这种式子是经典的 cdq 分治，于是直接做就完了。直接实现是小常数双 $\log$，或许需要十分精细的实现才能做到单 $\log$。

后来被 hack 数据给整成 wa 了，于是把为了提升精度把代码改成了下面这个鬼样子：

```cpp
//Date: 2024-08-30 14:24:32
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
bool MBE;
namespace SOLVER {
int n,m,K,p[505],v[505],cnt,x[200005],id[200005];long double sum,y[200005];
void init(int N) {
	for(int i=2;i<=N;i++) {
		if(!v[i]) p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=N;j++) 
            {v[i*p[j]]=1;if(i%p[j]==0) break;}
	}
}
long double k(int i,int j) {return (y[i]-y[j])/(x[i]-x[j]);}
bool cmp(int i,int j) {return x[i]==x[j]?y[i]>y[j]:x[i]<x[j];}
int st[200005],top;
void solve(int l,int r) {
    if(l==r) return;int mid=(l+r)>>1;solve(l,mid);st[top=0]=0;
    for(int i=l;i<=mid;i++) {
        if(i!=l&&x[id[i]]==x[id[i-1]]) continue;
        while(top>=1&&(y[st[top]]-y[id[i]])*(x[st[top-1]]-x[st[top]])>(y[st[top-1]]-y[st[top]])*(x[st[top]]-x[id[i]])) top--;
        st[++top]=id[i];
    }
    for(int i=mid+1;i<=r;i++) {
        int ll=1,rr=top,pos=0;
        while(ll<=rr) {
            int mm=(ll+rr)>>1;
            if((y[st[mm-1]]-y[st[mm]])*(x[st[mm]]+x[id[i]])<=y[st[mm]]*(x[st[mm-1]]-x[st[mm]])) pos=mm,ll=mm+1;
            else rr=mm-1;
        }
        y[id[i]]=max(y[id[i]],y[st[pos]]/(x[st[pos]]+x[id[i]])+K);
    }
    solve(mid+1,r);sort(id+l,id+r+1,cmp);
}
void MAIN() {
    n=rd(),y[1]=rd(),K=rd();x[0]=0,y[0]=-1e18;
    for(int i=1;i<=n;i++) {
        int ret=rd();id[i]=i;
        for(int j=1;p[j]*p[j]<=ret;j++) if(ret%p[j]==0) 
            {while(ret%p[j]==0) ret/=p[j];x[i]+=p[j];}
        if(ret!=1) x[i]+=ret;
    }
    solve(1,n);
    for(int i=1;i<=n;i++) sum+=y[i];
    printf("%.10Lf\n",sum);
}
}
bool MED;
signed main() {
    SOLVER::init(500);
    for(int tt=1;tt;tt--) SOLVER::MAIN();
    cerr<<(&MBE-&MED)/1024<<" B, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
//183407.2374368
```

不过代码看个大概应该就行了吧。

---

## 作者：syp11 (赞：0)

赛时被我 AC 了，不过 T3 没有过，喜提300分（不嘻嘻）。

## 题目简述
定义 $a(x)$ 为 $x$ 所有质因子的和，给定 $m_1,k$ 和数组 $w$ ，定义 $\max\limits_{1\le j<i}\{\dfrac{m_j}{a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))}+k\}$，求 $\sum\limits_{i=1}^nm_i$。

## 题解
首先要证明一个事实 $a(\gcd(x,y))+a(\text{lcm}(x,y))=a(x)+a(y)$，这是因为对于某个质数 $p$：

1. 如果 $p$ 是 $x,y$ 的公因子，那么 $p$ 是 $\gcd(x,y)$ 和 $\text{lcm}(x,y)$ 的因子，在左式中要被加上两次，而在右式也会被加上两次。
1. 如果 $p$ 是 $x,y$ 其中一个的因子，那么 $p$ 是 $\text{lcm}(x,y)$ 的因子，但不是 $\gcd(x,y)$ 的因子，在左式中要被加上一次，而在右式也会被加上一次。
1. 如果 $p$ 不是 $x,y$ 其中任何一个的因子，那么 $p$ 不是 $\gcd(x,y)$ 和 $\text{lcm}(x,y)$ 其中任何一个的因子，在左右两式都不会被加上。

由于上述讨论对所有 $p$ 均成立，所以每个质数对左右两式的贡献相等，根据定义，等式得证。

这样我们就可以完成化简：
$$\max\limits_{1\le j<i}\{\dfrac{m_j}{a(\operatorname{lcm}(w_i,w_j))+a(\gcd(w_i,w_j))}+k\}=\max\limits_{1\le j<i}\{\dfrac{m_j}{a(w_i)+a(w_j)}\}+k$$
为了快速求出右侧 $\max$ 的结果，需要使用数据结构维护，但是维护分式并没有很好的方法，注意到对于每个固定的 $j$ ，分子是常数，不确定的值全部在分母，所以考虑对 $\max$ 取倒数得：
$$\begin{aligned}\max\limits_{1\le j<i}\{\frac{m_j}{a(w_i)+a(w_j)}\}+k&=(\min\limits_{1\le j<i}\{\frac{a(w_i)+a(w_j)}{m_j}\})^{-1}+k\\&=(\min\limits_{1\le j<i}\{\frac{a(w_i)}{m_j}+\frac{a(w_j)}{m_j}\})^{-1}+k\end{aligned}$$
这样就得到了维护直线方程的结果。

使用李超线段树，维护对于每个点直线 $\dfrac{a(w_j)}{m_j}+\dfrac{1}{m_j}x$ 的最小值，在得到每个新的 $m_j$ 以后把上述直线加入线段树即可。

## 复杂度分析
那么线段树维护的点的值域 $V$ 是多少呢？我们将要证明 $V\le182376$，即 $\forall n\le182376,有a(n)\le182376$，当然可以暴力枚举，但是这里有一个优雅的方法。

只需证明 $a(n)\le n$ 即可，不妨设 $n=\prod\limits_{p\in\mathbb{P}}p^{e_p}\ge\prod\limits_{p\in\mathbb{P}}p$，由于上述乘积是有限的，我们将每一项**降序**排列为 $p_1,p_2,\cdots,p_k$，只需证明 $\prod\limits_{i=1}\limits^{k}p_i\ge\sum\limits_{i=1}\limits^{k}p_i$ ，对 $k$ 使用数学归纳法。

当 $k=1$ 时显然成立，当命题对于 $k-1$ 成立时，有

$$\prod\limits_{i=1}\limits^{k}p_i=p_k\prod\limits_{i=1}\limits^{k-1}p_i\ge p_k\sum\limits_{i=1}\limits^{k-1}p_i\ge2\sum\limits_{i=1}\limits^{k-1}p_i\ge\sum\limits_{i=1}\limits^{k}p_i$$
此处第一个不等号成立是因为数学归纳法，第二个不等号成立是因为 $p_k$ 是质数，所以 $p_k\ge2$，第三个不等号成立是因为 $p_i$ 降序排列，所以 $\sum\limits_{i=1}\limits^{k-1}p_i\ge p_k$。因此证明了 $$\prod\limits_{i=1}\limits^{k}p_i\ge\sum\limits_{i=1}\limits^{k}p_i$$

综上所述
$$n=\prod\limits_{p\in\mathbb{P}}p^{e_p}\ge\prod\limits_{p\in\mathbb{P}}p=\prod\limits_{i=1}\limits^{k}p_i\ge\sum\limits_{i=1}\limits^{k}p_i=a(n)$$
命题证毕。

使用筛法求出所有 $a(w_i)$ 的结果，然后使用每次 $O(\log^2V)$ 复杂度的李超线段树递推求出 $m_i$ ，最后求和，整体时间复杂度 $O(n\log^2V)$，可以通过。（好吧，其实我没用筛法，不过问题不大）

开了`long double`，不开被炸精度了。

## 代码
```cpp
#include <bits/stdc++.h>
#define double long double
using namespace std;
const int N=2e5+10;
const double inf=1e9;
struct LC_SGT
{
	struct line
	{
		double k,b;
	}p[N];
	int cnt,s[N<<2];
	double calc(int i,double d)
	{
		return p[i].b+p[i].k*d;
	}
	int ls(int x)
	{
		return x<<1;
	}
	int rs(int x)
	{
		return x<<1|1;
	}
	void upd(int rt,int pl,int pr,int u)
	{
		int &v=s[rt];
		int mid=pl+pr>>1;
		if(calc(u,mid)<calc(v,mid))
		{
			swap(u,v);
		}
		if(calc(u,pl)<calc(v,pl))
		{
			upd(ls(rt),pl,mid,u);
		}
		if(calc(u,pr)<calc(v,pr))
		{
			upd(rs(rt),mid+1,pr,u);
		}
		return;
	}
	void update(int rt,int pl,int pr,int l,int r,int u)
	{
		if(l<=pl&&r>=pr)
		{
			upd(rt,pl,pr,u);
			return;
		}
		int mid=pl+pr>>1;
		if(l<=mid)
		{
			update(ls(rt),pl,mid,l,r,u);
		}
		if(r>mid)
		{
			update(rs(rt),mid+1,pr,l,r,u);
		}
		return;
	}
	double query(int rt,int l,int r,int d)
	{
		if(d>r||d<l)
		{
			return inf;
		}
		int mid=l+r>>1;
		double res=calc(s[rt],d);
		if(l==r)
		{
			return res;
		}
		return min({res,query(ls(rt),l,mid,d),query(rs(rt),mid+1,r,d)});
	}
}g;
int n,k,w[N],a[N];
double m[N],res;
int geta(int x)
{
	int r=0;
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0)
		{
			r+=i;
			while(x%i==0)
			{
				x/=i;
			}
		}
	}
	if(x!=1)
	{
		r+=x;
	}
	return r;
}
signed main()
{
	cin>>n>>m[1]>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		a[w[i]]=geta(w[i]);
	}
	g.p[0]={0.0,inf};
	g.p[++g.cnt]={1/m[1],a[w[1]]/m[1]};
	g.update(1,1,200000,1,200000,g.cnt);
	for(int i=2;i<=n;i++)
	{
		m[i]=k+1/g.query(1,1,200000,a[w[i]]);
		g.p[++g.cnt]={1/m[i],a[w[i]]/m[i]};
		g.update(1,1,200000,1,200000,g.cnt);
	}
	for(int i=1;i<=n;i++)
	{
		res+=m[i];
	}
	printf("%.15Lf",res);
	return 0;
}
```

---

