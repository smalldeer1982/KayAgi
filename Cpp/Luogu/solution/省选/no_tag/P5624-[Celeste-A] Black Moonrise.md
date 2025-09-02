# [Celeste-A] Black Moonrise

## 题目背景

> 幽灵
>
> 不属于这个世界
> 
>但因这个世界而诞生
>
>潜藏在秩序之外
>
>$$
>
> 醒来吧，我的心是堡垒
>
>在梦中我易受伤害

## 题目描述

在 Madeline 的梦境中，城市的边境是由大大小小的宇宙碎片构成的

每个宇宙碎片都有一定的能量值，由于碎片的大小有一定的差异，因此它们的能量值也有大有小

Madeline 很享受在碎片之间穿梭，她每次都会选择两个宇宙碎片，并获得它们能量值的最大公约数的愉悦值。注意这两个宇宙碎片可以相同

宇宙碎片构成了一段序列$a_1,a_2,\cdots,a_n$，每次 Madeline 都会选择它的一个区间，对于这个区间里面的任意两个宇宙碎片$(u,v)$，她都会进行一次穿梭。注意这里的$(u,v)$是有序对

形式化地，Madeline 每次获得的愉悦值为

$$\sum_{i=l}^r\sum_{j=l}^r \gcd(a_i,a_j)$$

当 Madeline 从她的梦中被唤醒时，她发现所有的宇宙碎片都消失了。她不记得在梦中每次穿梭时获得的愉悦值是多少，只依稀记得她选择的区间了。

于是她找到了你——一个信息学大佬，请你根据她每次选择的区间，还原她当时的愉悦值


## 说明/提示

对于$10\%$的数据，满足$n,q\leq 200$

对于$20\%$的数据，满足$n,q\leq 2250$

对于$40\%$的数据，满足$n,q\leq 4000$

对于$100\%$的数据，满足$n,q,a_i\leq 10^5$

**保证数列和询问均为随机生成**

## 样例 #1

### 输入

```
5 2
1 2 3 4 5
1 2
2 3```

### 输出

```
5
7```

# 题解

## 作者：ArrTue (赞：3)

##### update: 修正了错误代码。

[题目传送门](https://www.luogu.com.cn/problem/P5624)

#### 前置知识：

欧拉函数，分块。

#### 题意：

- 给出 $n$ 个数 $a_{1\dots n}$，$q$ 次询问，每次给出 $l,r$，求 $\sum\limits_{i=l}^r\sum\limits_{j=l}^r\gcd(a_i,a_j)$。

- 保证数列、询问均随机生成，$n,q,a_i\le10^5$。

#### 分析：

$\begin{aligned}
&\sum\limits_{i=l}^r\sum\limits_{j=l}^r\gcd(a_i,a_j)\\
=&\sum\limits_{i=l}^r\sum\limits_{j=l}^r\sum\limits_{d\mid a_i\land d\mid a_j}\varphi(d)&(1)\\
=&\sum\limits_{d=1}^{\max(a)}\varphi(d)\sum\limits_{i=l}^r\sum\limits_{j=l}^r[d\mid a_i\land d\mid a_j]\\
=&\sum\limits_{d=1}^{\max(a)}\varphi(d)(\sum\limits_{i=l}^r[d\mid a_i])^2
\end{aligned}$

其中 $(1)$ 用到了欧拉函数的性质 $n=\sum\limits_{d\mid n}\varphi(d)$（也可用莫反推出一个新函数 $f(d)$，实际上 $f$ 就是 $\varphi$）

官方解法中使用了莫队维护 $\sum\limits_{i=l}^r[d\mid a_i]$（不会莫队可以跳过这一段）：由于 $a_i$ 随机生成，故其因数个数期望较少（另一篇题解中认为是一个常数 $\alpha$，本题解认为是值域内的总因子个数 $v\ln v$ 除以值域 $v$，即 $\ln v$），移动莫队指针时可以直接枚举所有 $a_i$ 的因数 $d$ 并更新对应的 $\sum\limits_{i=l}^r[d\mid a_i]$。期望复杂度 $\mathcal O(n\sqrt n\ln v)$，~~惊人地~~可过。

但~~翻了 AC 代码，发现~~本题实际上有一种期望 $\mathcal O((n+q)\sqrt n)$ 的分块写法。

首先对值域分块，所有不大于 $V$ 的 $d$ 直接暴力求出 $[d\mid a_i]$ 的前缀和，询问时 $\mathcal O(V)$ 即可处理这一部分的数，总复杂度 $\mathcal O((n+q)V)$。

对于大于 $V$ 的 $d$，由于值比较大，所以随机情况下 $a$ 中 $d$ 的倍数较少。假设所有为 $d$ 的倍数的 $a$ 为 $a_{k_1},a_{k_2},\dots,a_{k_m}$。当询问左端点 $l\in(k_{x-1},k_x]$，右端点 $r\in[k_y,k_{y+1})$ 时，$\sum\limits_{i=l}^r[d\mid a_i]$ 即为 $y-x+1$；对答案贡献为 $\varphi(d)(y-x+1)^2$。对于每一个询问，显然不能循环每一个 $d$ 计算 $x,y$。但注意到因为 $m$ 较小，有序对 $(x,y)$ 只有 $\mathcal O(m^2)$ 种情况，可以从这里入手。

不妨将询问按右端点排序，对于 $y$ 相同的询问，$d$ 的贡献只与左端点有关。而左端点落在一个区间内时，贡献都是一样的。考虑差分，则 $d$ 只对 $y+1$ 个位置有影响。每次 $y$ 改变只需修改这几处的值即可。总修改次数为 $\mathcal O(m^2)$。

可以证明 $m^2$ 的期望为 $\mathcal O(\dfrac{n^2}{d^2})$（[证明 link](https://www.luogu.com.cn/paste/p21ynwum)）。则对于所有 $d$，总修改次数期望为 $\mathcal O(\sum\limits_{d=V}^{\max(a)}\dfrac{n^2}{d^2})=\mathcal O(\dfrac{n^2}V)$。

对每个询问需要计算出差分数组的前缀和。考虑分块，使修改 $\mathcal O(1)$，查询 $\mathcal O(\sqrt n)$。总时间复杂度 $\mathcal O((n+q)V+\dfrac{n^2}V+q\sqrt n)$，取 $V=\sqrt n$，复杂度即为 $\mathcal O((n+q)\sqrt n)$。

#### 思路：

1. 求欧拉函数。

2. 对值域分块，分别处理。

---

具体说明值域分块后大于 $V$ 的 $d$ 如何处理。

开 $\max(a)$ 个 vector，存下每个 $d$ 的 $k_i$。考虑右端点所在区间由 $[k_{y_0},k_{y_0+1})$ 到 $[k_{y_0+1},k_{y_0+2})$，差分数组如何变化：$\forall x\in[1,y_0+1]$，左端点在 $(k_{x-1},k_x]$ 的贡献由 $\varphi(d)(y_0-x+1)^2$ 变为 $\varphi(d)(y_0-x+2)^2$，增加 $\varphi(d)(2(y_0-x+1)+1)$。

在差分数组上，体现为位置 1 增加 $\varphi(d)(2y_0+1)$，位置 $k_x+1\ (x\in[1,y_0])$ 减少 $2\varphi(d)$，位置 $k_{y_0}+1$ 减少 $\varphi(d)$。

分块求和，记得处理对应位置块和。

---

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i=l, _=r; i<=_; ++i)
typedef long long ll;
using namespace std;
inline int read() {
	int res=0; bool k=1; char ch;
	while(!isdigit(ch=getchar())) k=ch^45;
	do res=(res<<1)+(res<<3)+(ch&15); while(isdigit(ch=getchar()));
	return k? res: -res;
}
const int mN=1e5+9, mP=1e4, mL=320;
int n, q, L, V, a[mN], sum[mN][mL];
ll ans[mN];

int pri[mP], cntp, phi[mN];
inline void init(int n) {
	phi[1]=1;
	for(int i=2, j, u; i<=n; ++i) {
		if(!phi[i]) pri[++cntp]=i, phi[i]=i-1;
		for(j=1; (u=pri[j]*i)<=n && i/pri[j]*pri[j]^i; ++j) phi[u]=phi[i]*(pri[j]-1);
		if(u<=n) phi[u]=phi[i]*pri[j];
	}
}

struct Que {int x, y, id;} qn[mN];
bool operator < (Que q1, Que q2) {return q1.y<q2.y;}

ll b[mN], sumb[mL];	//b 为差分数组，sumb 为分块的差分数组
vector<int> num[mN];	//用于存 ki
inline void sol(int x, int p) {
	if(x<=V) return ++sum[p][x], void();	//小于 V，直接前缀和
	int y0=(int) num[x].size(), t=phi[x];
	b[1]+=(ll) (y0<<1|1)*t, sumb[0]+=(ll) (y0<<1|1)*t;
	b[p+1]-=t, sumb[(p+1)/L]-=t;
	t<<=1;
	for(int i=y0-1; i>=0; --i) b[num[x][i]+1]-=t, sumb[(num[x][i]+1)/L]-=t;
	num[x].push_back(p);
}

inline ll sqr_(int x) {return (ll) x*x;}

int main() {
	init(1e5), n=read(), q=read(), L=sqrt(n), V=sqrt(1e5);
	if(L<2) L=2;
	rep(i, 1, n) a[i]=read();
	rep(i, 1, q) qn[i].x=read(), qn[i].y=read(), qn[i].id=i;
	sort(qn+1, qn+q+1);

	rep(i, 1, q) {
		rep(r, qn[i-1].y+1, qn[i].y) {	//扩展 y
			memcpy(sum[r], sum[r-1], sizeof sum[r]);
			for(int j=1; j*j<=a[r]; ++j) if(a[r]%j==0) {
				sol(j, r);
				if(j*j^a[r]) sol(a[r]/j, r);
			}
		}
		int x=qn[i].x, y=qn[i].y, id=qn[i].id;
		rep(j, 0, x/L-1) ans[id]+=sumb[j];	//大于 V，值域分块
		rep(j, x/L*L, x) ans[id]+=b[j];
		rep(v, 1, V) ans[id]+=phi[v]*sqr_(sum[y][v]-sum[x-1][v]);	//小于 V，直接前缀和差分
	}
	rep(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：Fading (赞：2)

没写暴力失去AC祭

如果正解真的是$O(n\sqrt n\alpha)$的话（$\alpha$表示随机条件下的约数个数），我就会用腐朽的声带喊出：

出题人你数据造的真水...数据随机居然随机卡不掉常数（$\alpha$算常数）这么大的$O(n\sqrt n)$？？？

随机也不至于这么搞笑吧？？？

恕我直言，$O(n\sqrt n\alpha)$真的很好想~~就是暴力~~。

其实就是自己太菜...

$a_i$这么小

而且有一道题目叫做[$P3246$](https://www.luogu.org/problemnew/show/P3246)

然后我就想到了莫队

然后我就开始推转移式

然后我就发现我推出来的式子不可以$O(1)$转移

然后我就懵逼了

然后我就发现自己被坑了。。。

假设我们之前已经获得了区间$[l,r]$的信息，如何得到$r+1$呢？

很显然增加的答案就是

$$2\times \sum_{i=l}^{r}\gcd(a_i,a_{r+1})+a_{r+1}$$

我们考虑如何求出

$$\sum_{i=l}^{r}\gcd(a_{i},a_{r+1})$$

由于自己被$\mu$坑了几次，我直接上了$\varphi$

$$=\sum_{i=l}^{r}\sum_{d|a_i,d|a_{r+1}}\varphi(d)$$

$$=\sum_{d|a_{r+1}}\sum_{i=l}^r\varphi(d)[d|a_i]$$

$$=\sum_{d|a[r+1]}\varphi(d)\sum_{i=l}^r[d|a_i]$$

注意到$\sum_{i=l}^r[d|a_i]$不好求出，我们可以考虑在莫队的同时暴力算出来

我们加入一个数的时候，就开一个数组把$d$的倍数个数记录下来

这样答案就可以算了。但是这样插入复杂度多了一个$O(\alpha)$

那我们将错就错，暴力枚举$a_{r+1}$的约数，然后算$\varphi(d)$

具体实现可以把每一个$a_i$的约数预处理到一个$\texttt{vector}$里面

然后复杂度就是$O(n\sqrt n\alpha)$了。。。

---

## 作者：zifanwang (赞：0)

考虑莫队。

记数 $i$ 的个数为 $c_i$，套路地用莫比乌斯函数容斥，发现答案为 $\sum_{i=1}^{10^5}\frac{c_i(c_i+1)}2\sum_{d|i}\mu(\frac i d)d$。

先预处理出前面的常数和每个数的因子，每次移动端点枚举因子更新答案即可。

因为数是随机的，所以时间复杂度 $\mathcal O(n\sqrt n \ln n)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 100003
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
struct node{
	int l,r,i;
}e[mxn];
int n,q,t,a[mxn],d[mxn],p[mxn],ps[mxn],c[mxn],mu[mxn];
ll ans,f[mxn],as[mxn];
vector<int>s[mxn];
void init(int n){
	mu[1]=1;
	rep(i,2,n){
		if(!d[i])d[i]=p[++t]=i,mu[i]=-1;
		rep(j,1,t){
			if(p[j]>d[i]||p[j]>n/i)break;
			d[p[j]*i]=p[j];
			mu[p[j]*i]=i%p[j]?-mu[i]:0;
		}
	}
	rep(i,1,n)for(int j=i;j<=n;j+=i){
		f[j]+=mu[j/i]*i;
		s[j].pb(i);
	}
}
inline void add(int x){
	for(int i:s[x]){
		c[i]++;
		ans+=(c[i]*2-1)*f[i];
	}
}
inline void del(int x){
	for(int i:s[x]){
		ans-=(c[i]*2-1)*f[i];
		c[i]--;
	}
}
signed main(){
	init(1e5);
	scanf("%d%d",&n,&q);
	const int b=sqrt(n);
	rep(i,1,n)scanf("%d",&a[i]),ps[i]=(i+b-1)/b;
	rep(i,1,q)scanf("%d%d",&e[i].l,&e[i].r),e[i].i=i;
	sort(e+1,e+q+1,[](node x,node y){
		return ps[x.l]!=ps[y.l]?x.l<y.l:ps[x.l]&1?x.r<y.r:x.r>y.r;
	});
	int l=1,r=0;
	rep(i,1,q){
		while(l>e[i].l)add(a[--l]);
		while(r<e[i].r)add(a[++r]);
		while(l<e[i].l)del(a[l++]);
		while(r>e[i].r)del(a[r--]);
		as[e[i].i]=ans;
	}
	rep(i,1,q)printf("%lld\n",as[i]);
	return 0;
}
```

---

## 作者：dAniel_lele (赞：0)

考虑莫队。

不难发现 $\gcd(i,j)=\sum\limits_{k\mid i,k\mid j}\varphi(k)$。预处理出 $\varphi(k)$。

在莫队移动端点的时候，将 $k\mid a_i$ 全部加入或移除。对于某个数 $x$，如果目前出现次数为 $cnt_x$，则贡献为 $cnt_x^2\times\varphi(x)$。

由于数据随即生成，总复杂度 $O(n\sqrt q\ln n)$。（$\ln n$ 是因为调和级数）

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int a[100005];
vector<int> vc[100005];
int isp[100005],phi[100005],prm[100005],tot,cnt[100005],l,r,ret[100005],ans;
struct qry{
	int l,r,pos;
}b[100005];
bool cmp(qry x,qry y){
	return (x.l/300==y.l/300)?x.r<y.r:x.l<y.l;
}
void modifypos(int v,int cg){
	ans-=phi[v]*cnt[v]*cnt[v];
	cnt[v]+=cg;
	ans+=phi[v]*cnt[v]*cnt[v];
}
void modify(int pos,int cg){
	for(auto v:vc[pos]) modifypos(v,cg);
}
void move(int tol,int tor){
	while(r<tor) modify(++r,1);
	while(l>tol) modify(--l,1);
	while(r>tor) modify(r--,-1);
	while(l<tol) modify(l++,-1);
}
signed main(){
	phi[1]=1;
	for(int i=2;i<=100000;i++) isp[i]=1;
	for(int i=2;i<=100000;i++){
		if(isp[i]) phi[i]=i-1,prm[++tot]=i;
		for(int j=1;j<=tot&&i*prm[j]<=100000;j++){
			isp[i*prm[j]]=0;
			if(i%prm[j]==0){
				phi[i*prm[j]]=phi[i]*prm[j];
				break;
			}
			phi[i*prm[j]]=phi[i]*phi[prm[j]];
		}
	}
	int n,q; cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=1;j*j<=a[i];j++){
			if(a[i]%j==0){
				vc[i].push_back(j);
				if(j*j!=a[i]){
					vc[i].push_back(a[i]/j);
				}
			} 
		}
	}
	for(int i=1;i<=q;i++) cin>>b[i].l>>b[i].r,b[i].pos=i;
	sort(b+1,b+q+1,cmp);
	l=1,r=0;
	for(int i=1;i<=q;i++){
		move(b[i].l,b[i].r);
		ret[b[i].pos]=ans;
	}
	for(int i=1;i<=q;i++) cout<<ret[i]<<"\n";
	return 0;
}
```

---

