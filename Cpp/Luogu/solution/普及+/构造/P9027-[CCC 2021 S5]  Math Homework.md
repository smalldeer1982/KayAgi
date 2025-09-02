# [CCC 2021 S5]  Math Homework

## 题目描述

构造一个长度为 $N$ 的整数序列 $A$，使得：

1. $\forall i,1\leq A_i\leq 10^9$；
2. $\forall i,\gcd(A_{X_i},A_{X_i+1},\cdots,A_{Y_i})=Z_i$。

或者报告无解。

## 说明/提示

$$1\leq N\leq 150000,1\leq M\leq 150000,1\leq Z_i\leq 16$$

译自 [CCC2021 S5](https://cemc.math.uwaterloo.ca/contests/computing/past_ccc_contests/2021/ccc/seniorEF.pdf)。

spj 在附件里，发现锅了请联系[我](/user/90693)。

## 样例 #1

### 输入

```
2 2
1 2 2
2 2 6
```

### 输出

```
4 6```

## 样例 #2

### 输入

```
2 2
1 2 2
2 2 5
```

### 输出

```
Impossible```

# 题解

## 作者：_•́へ•́╬_ (赞：7)

## 思路

意识到每个质~~只~~因子是独立的，因此我们对每个质因子单独跑一遍，酱紫就能直接操作指数。

把 $\operatorname{gcd}$ 翻译到指数上，就是这一段区间的指数的最小值**恰好**等于 $Z$ 的指数。

考虑把恰好拆开，先构造使得对于所有区间都使得最小值 $\geq Z$ 的指数，再检查是否同时满足 $\leq$。

为了让 $\leq$ 更容易被满足，我们在构造的时候要选满足 $\geq$ 的最小值。即对于某个位置，恰好取所有覆盖到这个位置的限制的最大值（更大就不能很好地满足 $\leq$，更小就不能满足 $\geq$）。

感觉一会大于一会小于，逻辑关系有点混乱。。。

checker 之前锅了，谢罪。实际上 checker 是会忽略空白的，所以行末空格啥的不影响。~~会不会有人从 checker 里面贺 ST 表板子。~~

## code

```cpp
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<queue>
#define N 150000
#define LG 18
#define pr pair<int,int> 
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,m,lg[N],a[N],st[N][LG];
struct node
{
	int x,y,z,tmp;
	inline void in(){read(x);read(y);--x;--y;read(z);}
	inline bool operator<(const node&kkk)const{return x<kkk.x;}
}c[N];
inline int pw(const int&i,int j){int ans=1;for(;j--;ans*=i);return ans;}
inline int query(const int&l,const int&r)
{
	int i=lg[r-l];
	return min(st[l][i],st[r-(1<<i)+1][i]);
}
inline void f(const int&x)
{
	for(int i=0;i<m;++i)
	{
		c[i].tmp=0;
		for(int&j=c[i].z;!(j%x);j/=x,++c[i].tmp);//tmp是Z的指数
	}
	priority_queue<pr>q;
	for(int i=0,j=0;i<n;++i)
	{
		for(;j<m&&c[j].x<=i;++j)q.emplace(c[j].tmp,j);
		for(;q.size()&&c[q.top().second].y<i;q.pop());
		if(q.size())st[i][0]=q.top().first;
		else st[i][0]=0;
	}//用堆维护所有覆盖到这个位置的限制的最大值，进行构造
	for(int i=n-1;i>=0;--i)for(int j=1;j<LG;++j)
		if(i+(1<<j-1)<n)st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
		else st[i][j]=st[i][j-1];
	for(int i=0;i<m;++i)//检查
		if(query(c[i].x,c[i].y)^c[i].tmp)printf("Impossible"),exit(0);
	for(int i=0;i<n;++i)a[i]*=pw(x,st[i][0]);
}
main()
{
	read(n);read(m);for(int i=0;i<m;c[i++].in());sort(c,c+m);
	for(int i=2;i<n;lg[i]=lg[i>>1]+1,++i);
	for(int i=0;i<n;a[i++]=1);
	f(2);f(3);f(5);f(7);f(11);f(13);
	for(int i=0;i<n;printf("%d ",a[i++]));
}
```

---

## 作者：sgl654321 (赞：6)

### 题目大意
已经说的很清楚了。

### 解题思路
首先，如果 $\gcd(a_x,a_{x+1},\cdots,a_y)=z$，那么有 $\forall i\in[x,y],z|a_i$。我们可以据此把一个 $a_i$ 能整除的 $z_1,z_2\cdots$ 都标记出来，然后就有 $\text{lcm}(z_1,z_2,\cdots)|a_i$。

但是单单满足这个还不够，这只能保证 $z$ 是他们的公因数，不是最大公因数。

我们考虑贪心。显然，$\gcd(x,y)\le \gcd(k_1x,k_2y)$。 其中 $k_1,k_2$ 为正整数。考虑令所有的 $a_i=\text{lcm}(z_1,z_2,\cdots)$。如果此时的序列 $\{a\}$ 仍然不满足条件，那么如果 $a_i=k\text{lcm}(z_1,z_2,\cdots)$，那肯定就更不行了。

因此构造方案就是对于任意 $a_i$，把它能整除的 $z$ 都找出来，然后 $a_i$ 等于它们的最小公倍数。

接下来讲如何判断方案是否合法，即判断 `impossible` 的情况。由于 $\gcd$ 是有结合律的，我们可以考虑使用 ST 表来维护。具体的，设 $st_{i,j}$ 表示 $\text{lcm}(a_i,a_{i+1},\cdots a_{i+2^j-1})$。然后就可以用 $O(1)$ 的时间复杂度求出一个子串的 $\gcd$ 了。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 150010
using namespace std;
typedef long long ll;
struct node{
	ll x,y,z;
}ask[maxn];
ll n,a[maxn],m,x,y,z,f[maxn][20],b[maxn][20];
ll c[maxn],st[maxn][20],save,lo[maxn],num;
ll gcd(ll x,ll y){
	if(x==0)return y;
	return gcd(y%x,x);
}
ll lcm(ll x,ll y){
	return x/gcd(x,y)*y;
}
bool flag;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)c[i]=1;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		ask[i]=node{x,y,z};
		f[x][z]++;f[y+1][z]--;
	}
	for(int i=1;i<=16;i++)
		for(int j=1;j<=n;j++)
			b[j][i]=b[j-1][i]+f[j][i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=16;j++)
			if(b[i][j]>0)
				c[i]=lcm(c[i],j);
	for(int i=1;i<=n;i++)st[i][0]=c[i];
	for(int i=2;i<=n;i++)lo[i]=lo[i/2]+1; 
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			if(i+(1<<j)-1<=n)
				st[i][j]=gcd(st[i][j-1],st[i+(1<<j-1)][j-1]);
	flag=1;
	for(int i=1;i<=m;i++){
		x=ask[i].x;y=ask[i].y;z=ask[i].z;
		save=lo[y-x+1];
		num=gcd(st[x][save],st[y-(1<<save)+1][save]);
	//	cout<<num<<endl;
		if(num!=z)flag=0;
	}
	if(!flag)cout<<"Impossible"<<endl;
	else{
		for(int i=1;i<=n;i++)	
			cout<<c[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：SegTree (赞：5)

### 题意

构造一个长度为 $N$ 的整数序列 $A$，使得：

1. $\forall i,1\leq A_i\leq 10^9$；
2. $\forall i,\gcd(A_{X_i},A_{X_i+1},\cdots,A_{Y_i})=Z_i$。

或者报告无解。

### 题解

每个质因子分别考虑即可。记 $p_{i,c}$ 表示 $a_i$ 的质因子 $c$ 出现次数。$\gcd$ 如果分解成 $p_1^{b_1}\times p_2^{b_2}\cdots p_k^{b_k}$，那么就可以得出 $\min_{i=l}^rp_{i,c}=b_i$，显然这说明它们 $\ge b_i$。考虑维护一个 `set`，在 $l$ 插入贡献，在 $r+1$ 删除贡献，那么 $p_{i,c}$ 的最小值就是 `set` 里的最大值。显然它取到最小值时最优，因为它越大区间 $\min$ 显然不降，限制更不好成立。

那么我们先还原出 $p_{i,c}$ 然后就是 ST 表查询区间最小值判断是否合法即可。

```cpp
int n,m,pr[]={2,3,5,7,11,13};
struct node {
    int x,y,z;
}d[maxn];
int st[maxn][20][6],Log2[maxn],a[maxn];
vector<pi>v[maxn];
int query(int l,int r,int x){
    int k=Log2[r-l+1];
    return min(st[l][k][x],st[r-(1<<k)+1][k][x]);
}set<pi>s;
void slv(){
    n=read(),m=read();
    int fn=0;
    up(i,1,m){
        d[i].x=read(),d[i].y=read(),d[i].z=read();
    }up(i,1,n)a[i]=1;up(kk,0,5){
        up(i,1,n)v[i].clear();s.clear();
        up(i,1,m){
            int k=d[i].z,c=0;
            wi(k%pr[kk]==0)c++,k/=pr[kk];
            ++fn;
            v[d[i].x].p_b(m_p(c,fn)),v[d[i].y+1].p_b(m_p(c,-fn));
        }up(i,1,n){
            for(auto y:v[i]){
                if(y.p2<0){
                    y.p2=-y.p2;s.erase(m_p(y.p1,y.p2));
                }else {
                    s.insert(m_p(y.p1,y.p2));
                }
            }int x=(s.size()?((*(--s.end())).p1):0);
            st[i][0][kk]=x;wi(x--)a[i]=a[i]*pr[kk];
        }
    }for(int k=1;(1<<k)<=n;++k)up(i,1,n-(1<<k)+1){
        up(j,0,5)st[i][k][j]=min(st[i][k-1][j],st[i+(1<<(k-1))][k-1][j]);
    }up(i,2,n)Log2[i]=Log2[i>>1]+1;
    up(i,1,m){
        ll res=1;
        up(j,0,5){
            int w=query(d[i].x,d[i].y,j);
            wi(w--)res=res*pr[j];
        }if(res!=d[i].z){
            puts("Impossible");return;
        }
    }up(i,1,n)printf("%d ",a[i]);printf("\n");
}
```

---

## 作者：羊叫兽同学 (赞：4)

提供一种不带 $\log$ 的做法。

首先我们知道对于 $a=p_{1}^{a_{1}}p_{1}^{a_{2}}p_{3}^{a_{3}}...$ ， $b=p_{1}^{b_{1}}p_{1}^{b_{2}}p_{3}^{b_{3}}...$ ，则 $\gcd(a,b)=p_{1}^{\min(a_{1},b_{1})}p_{1}^{\min(a_{2},b_{2})}p_{3}^{\min(a_{3},b_{3})}...$ ，这是很基础的。

把所有的 $d$ 和 $a$ 分解质因数，显然不同的质数间不会产生影响，所以我们对于每一个 $16$ 以内的质数分别考虑，我们的限制就可以变成告诉你一个区间的 $\min$ 值，让你构造一种方案。

发现你被告知的那个 $\min$ 值最大也只能是 $4$ ，因为最小质数是 $2$ ，而 $\log_{2}16=4$ ，所以你可以用差分暴力维护出每一个点都有哪些限制，在这些限制中取最大值，为什么取最小值和其他题解做法取 $\operatorname{lcm}$ 一个道理。

验证方案是否合法时，我们甚至不需要写 st 表。虽然我们需要计算区间最小值，但是所有的数都 $\leq 4$ ，所以我们可以暴力前缀和分别维护出这一段区间有多少个 $0$ 和 $1$ 和 $2$ 和 $3$ 和 $4$ ，从而求出最小值。

这样做复杂度是不带 $\log$ 的，稍微优化后目前可以拿到最优解。

参考代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#define reg register
using namespace std;
const int N=2000000;
int n,m,s,l[N],ans[N],r[N],d[N],tag[N][6],val[N],sum[N][6],cnt[N],madep;
inline int read()
{
	char x=getchar();
	int ans=0;
	while(x<'0'||x>'9')
		x=getchar();
	while(x>='0'&&x<='9')
	{
		ans=(ans<<1)+(ans<<3)+(x^48);
		x=getchar();
	}
	return ans;
}
void solve(int p)
{
	madep=log(16)/log(p);//madep就是以p为底16的对数向下取整，也就是质数为p时的最大次幂，如果看着不顺眼也可以直接改成madep=4；
	for(reg int i=1;i<=n;++i)
		for(reg int j=0;j<=madep;++j)
			tag[i][j]=sum[i][j]=0;
	for(reg int i=1;i<=m;++i)
	{
		int x=d[i];
		cnt[i]=0;
		while(x%p==0)
		{
			++cnt[i];
			x/=p;
		}
      //求出cnt，差分
		++tag[l[i]][cnt[i]];
		--tag[r[i]+1][cnt[i]];
	}
	for(reg int i=1;i<=n;++i)
	{
		val[i]=0;
		for(reg int j=0;j<=madep;++j)
		{
			tag[i][j]+=tag[i-1][j];//求差分数组的前缀和
			if(tag[i][j])
				val[i]=j;//val[i]等于i处所有限制中最大，也就是最严格的那个
			sum[i][j]+=sum[i-1][j];//sum[i][j]表示前i个数中有多少个等于j
		}
		sum[i][val[i]]++;
	}
	for(reg int i=1;i<=m;++i)
	{
		int mi=0;
		for(reg int j=0;j<=madep;++j)
			if(sum[r[i]][j]-sum[l[i]-1][j])
			{
				mi=j;
				break;
			}
		if(cnt[i]!=mi)//不一样直接输出无解退出程序
		{
			puts("Impossible");
			exit(0);
		}
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=val[i];j>=1;--j)
			ans[i]*=p;//最后要把val累乘到ans去
}
void write(int x)
{
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
int main()
{
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		ans[i]=1;
	for(reg int i=1;i<=m;++i)
		l[i]=read(),r[i]=read(),d[i]=read();
	solve(2);
	solve(3);
	solve(5);
	solve(7);
	solve(11);
	solve(13);
	for(reg int i=1;i<=n;++i)
	{
		write(ans[i]);
		putchar(' ');
	}
}
```

---

## 作者：SuperCowHorse (赞：1)

这题太神奇啦。

首先我们发现，$1\le Z_i\le16$，由此可以得知，我们可以构造 $1\le a_i\le \operatorname{lcm}\{1,2,3,4,\dots,15,16\}=720720$。因此，对于题目中的第一个要求 $1\le a_i\le10^9$，是完全没有用的。

考虑如何进行区间操作。对于每一个区间 $[l,r]$，我们可以维护一个数组 $t$，表示 $a_i$ 需要有 $t_i$ 的因子，即满足 $t_i|a_i$ 的最大值。

例如第一个样例。

先插进来一个区间 $[1,2]$，区间内最大公约数为 $2$。我们将这个数 $2$ 标记在 $[1,2]$ 上，表示 $a_1,a_2$ 都需要被 $2$ 整除。

然后再插进来一个区间，$[2,2]$ 上最大公约数为 $6$。这时，我们可以将 $t_2$ 更新成 $\operatorname{lcm} \{t_2,6\}$。

然后，$t$ 数组就是一个解了。显然，这一过程可以用线段树 $O(n\log n)$ 求解。

无解怎么判断？只需要把每一个要求存下来，等到求出 $t$ 后，用一个 ST 表去特判是否满足每一个要求即可。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1.5e5+5;
int n,m;bool quittt;
struct query{int l,r,x;}q[maxn];
struct SegTree{
	int l,r,siz;ll tag;
	inline SegTree(){tag=1;}
}t[maxn<<2];
inline int ls(int p){return p<<1;}
inline int rs(int p){return p<<1|1;}
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
inline ll lcm(ll x,ll y){
	return x/__gcd(x,y)*y;
}
inline void update(int p){}
inline void Pushdown(int p){
	int l=ls(p),r=rs(p);
	t[l].tag=lcm(t[l].tag,t[p].tag);
	t[r].tag=lcm(t[r].tag,t[p].tag);
	return;
}
inline void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;t[p].siz=r-l+1;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(lson);build(rson);
	update(p);
}
inline void Modify(int p,int l,int r,int lx,int rx,ll x){
	if(quittt) return;
	if(lx<=l&&rx>=r){
		t[p].tag=lcm(t[p].tag,x);//每次取 lcm
		return;
	}
	Pushdown(p);
	int mid=(l+r)>>1;
	if(lx<=mid) Modify(lson,lx,rx,x);
	if(rx>mid)  Modify(rson,lx,rx,x);
	update(p);
}
inline ll Query(int p,int l,int r,int x){
	if(l==r){
		return t[p].tag;
	}
	Pushdown(p);
	int mid=(l+r)>>1;
	if(x<=mid) return Query(lson,x);
	if(x>mid)  return Query(rson,x);
	return 1;
}
ll a[maxn];
struct STable{//ST 表特判
	ll f[maxn][30];int lg[maxn];
	inline void init(){
		for(int i=2;i<=n;++i){
			lg[i]=lg[i>>1]+1;
		}
		for(int i=1;i<=n;++i){
			f[i][0]=a[i];
		}
		for(int j=1;j<=lg[n];++j){
			for(int i=1;i+(1<<j)-1<=n;++i){
				f[i][j]=__gcd(f[i][j-1],f[i+(1<<(j-1))][j-1]);
			}
		}
	}
	inline ll query(int l,int r){
		int k=lg[r-l+1];
		return __gcd(f[l][k],f[r-(1<<k)+1][k]);
	}
}s;
signed main(){
// 	freopen("math.in","r",stdin);
// 	freopen("math.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,l,r,x;i<=m;++i){
		scanf("%d%d%d",&l,&r,&x);
		q[i]=(query){l,r,x};
	}
	build(1,1,n);
	for(int i=1;i<=m;++i){
		int l=q[i].l,r=q[i].r,x=q[i].x;
		Modify(1,1,n,l,r,1ll*x);//线段树区间更新
	}
	for(int i=1;i<=n;++i){
		a[i]=Query(1,1,n,i);
	}
	s.init();
	for(int i=1;i<=m;++i){//判断是否满足每个要求
		if(s.query(q[i].l,q[i].r)!=q[i].x){
			printf("Impossible");
			return 0;
		}
	}
	for(int i=1;i<=n;++i){
		printf("%lld%c",a[i]," \n"[i==n]);
	}
	return 0;
}
```

---

CSP/NOIP 2024 rp++。

---

## 作者：Loser_Syx (赞：1)

结论：如果可以构造，则一个可能的 $A$ 数组满分 $A_x= \operatorname{lcm} z_i$。其中 $z_i$ 为满足 $z_i \in [1,16]$ 且存在任意一个限制 $2$ 满足 $x \in [X_j,Y_j]$ 且 $z_i = Z_j$ 的 $z_i$。

不会理性证明，但是可以感性理解：对于当前构造的 $A_x$，一定是满足了限制 $2$ 的情况，但是如果我们的 $A_x$ 更大的话，可能操作二的 $\gcd$ 就更大了，这样显然就不满足题意了。

然后考虑如何筛出来 $z_i$，考虑一个限制 $(X_j,Y_j,Z_j)$，因为 $Z_j \leq 16$，所以我们分别对于每个 $Z$ 在其对应数组差分即可。

当然构造出来不一定满足题意，需要重新检查每个限制 $2$，选择线段树维护 $\gcd$ 即可。

复杂度 $O(m \log n)$。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
const int N = 1e5 + 56789;
int a[N];
struct node {
	int x, y, z;
} ask[N];
int cf[N][17];
struct SegTree {
	struct tree {
		int l, r, gcd;
	} t[N << 2];
	#define ls (k << 1)
	#define rs (k << 1 | 1)
	#define mid (l + r >> 1)
	void build(int k, int l, int r) {
		t[k].l = l; t[k].r = r;
		if (l == r) {
			t[k].gcd = a[l];
			return ;
		}
		build(ls, l, mid);
		build(rs, mid+1, r);
		t[k].gcd = __gcd(t[ls].gcd, t[rs].gcd);
	}
	int query(int k, int L, int R) {
		int l = t[k].l, r = t[k].r;
		if (L <= l && R >= r) {
			return t[k].gcd;
		}
		int ans = 0;
		if (L <= mid) ans = query(ls, L, R);
		if (R > mid) {
			int res = query(rs, L, R);
			if (ans == 0) ans = res;
			else ans = __gcd(res, ans);
		}
		return ans;
	}
} seg;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> ask[i].x >> ask[i].y >> ask[i].z;
		cf[ask[i].x][ask[i].z] ++;
		cf[ask[i].y + 1][ask[i].z] --;
	}
	for (int j = 1; j <= 16; ++j) {
		for (int i = 1; i <= n; ++i) {
			cf[i][j] += cf[i-1][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		a[i] = 1;
		for (int j = 2; j <= 16; ++j) {
			if (cf[i][j]) {
				a[i] = a[i] * j / __gcd(a[i], j);
			}
		}
	}
	seg.build(1, 1, n);
	for (int i = 1; i <= m; ++i) {
		if (seg.query(1, ask[i].x, ask[i].y) != ask[i].z) return puts("Impossible"), 0;
	}
	for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
	return 0;
}
```

---

## 作者：wind_seeker (赞：1)

考虑 gcd 实际上是由质因子拼凑起来的，而题目所给的范围又较小，所以我们只需要对于每一个质因子维护一颗线段树即可。

具体操作如下：

1. 线段树每个节点维护的是 $[l,r]$ 这个区间内，该质因子在这些数质因数分解中出现的最小次数。
2. 修改时，对 $[x_i,y_i]$ 这个区间内与 $z_i$ 分解质因数得到的个数取 $\max$ 即可。
3. 最后重新查询每个限制中每个质因子的最小出现次数，乘起来判断是否等于 $z_i$ 即可。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5e4,inf=1e9+7;

int n,m,cnt;
int x[N],y[N],z[N];
int prime[20],id[20];

#define ls rt<<1
#define rs rt<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
struct TREE{
	int tr[N<<2],lazy[N<<2];
	void push_up(int rt){tr[rt]=min(tr[ls],tr[rs]);}
	void push_down(int rt){
		if(lazy[rt]){
			int k=lazy[rt];lazy[rt]=0;
			tr[ls]=max(tr[ls],k),tr[rs]=max(tr[rs],k);
			lazy[ls]=max(lazy[ls],k),lazy[rs]=max(lazy[rs],k);
		}
	}
	void update(int rt,int l,int r,int ul,int ur,int k){
		if(ul<=l&&r<=ur) return tr[rt]=max(tr[rt],k),lazy[rt]=max(lazy[rt],k),void();
		int mid=(l+r)>>1;push_down(rt);
		if(ul<=mid) update(lson,ul,ur,k);
		if(mid<ur) update(rson,ul,ur,k);
		push_up(rt);
	}
	int query(int rt,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return tr[rt];
		push_down(rt);int mid=(l+r)>>1,res=inf;
		if(ql<=mid) res=min(res,query(lson,ql,qr));
		if(mid<qr) res=min(res,query(rson,ql,qr));
		push_up(rt);return res;
	}
}t[20];

int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	prime[1]=2,prime[2]=3,prime[3]=5,prime[4]=7,prime[5]=11,prime[6]=13,cnt=6;
	id[2]=1,id[3]=2,id[5]=3,id[7]=4,id[11]=5,id[13]=6;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i]>>z[i];
		for(int j=1;j<=cnt;j++){
			int res=0,xx=z[i];
			while(xx%prime[j]==0) res++,xx/=prime[j];
			t[id[prime[j]]].update(1,1,n,x[i],y[i],res);
		}
	}
	for(int i=1;i<=m;i++){
		int res=1;
		for(int j=1;j<=cnt;j++){
			int sum=t[id[prime[j]]].query(1,1,n,x[i],y[i]);
			if(sum!=0) res=res*(int)pow(prime[j],sum);
		}
		if(res!=z[i]){
			puts("Impossible");
			return 0;
		}
	}
	for(int i=1;i<=n;i++){
		int res=1;
		for(int j=1;j<=cnt;j++){
			int sum=t[id[prime[j]]].query(1,1,n,i,i);
			if(sum!=0) res=res*(int)pow(prime[j],sum);
		}
		cout<<res<<" ";
	}
	return 0;
}
```

---

## 作者：shixiangtian (赞：1)

# 前言

偶然翻了一场比赛，偶然看到这道题，没有看到 $Z_i$ 的范围，于是口胡了一个 $O(n\cdot(\log n)^2)$ 的算法，用到的算法有线段树。

讲一下不用限制 $Z_i$ 范围的情况（限制了自然也能过）。

因为题目看的不仔细，所以不知道 $A_i$ 是否要一样，但感觉不一样的话太难了一点（或许是我没想到？），所以觉得是可以一样的（然后真的是可以一样的）。

# 正文

首先，假设已经得到了答案序列，判断是否有解可以用 ST 表或线段树（我没想到可以用 ST表），那我们就不讲判断的内容了。

看题，发现题中给出了 $n$ 个区间的 $\gcd$ 的限制，接下来给出一种构造方法，可以证明若有解，则其得出的必是可行解。

若一个限制形如 $X_i,Y_i,Z_i$ ，则 $A_{X_i},A_{X_i+1},\cdots,A_{Y_i}$ 都得是 $Y_i$ 的正因数（话说好像没有保证 $X_i\le Y_i$，不管了）。

即对于每个 $A_i$ ，$A_i=\operatorname{lcm}(Z_{j_1},Z_{j_2},\cdots,Z_{j_{m'}})\cdot K_i$ ，其中 $K_i$ 为正整数。

以上这些没有问题吧？

所以最后生成出来的序列，对于每个限制 $X_i,Y_i,Z_i$，$Z_i|\gcd(A_{X_i},A_{X_i+1},\cdots,A_{Y_i})$，其中 $|$ 代表前一个数是后一个数的因数。

这也没问题吧，唯一的问题就是 $\gcd$ 可能偏大，对吧？

那如果我们令每个 $K_i$ 都为 $1$，即每个 $A_i$ 都取最小值，是不是 $\gcd$ 一定取力所能及的最小值？

那如果最后没有满足限制，也没有办法，即无解，因为每个 $A_i$ 都已经是最小值了。

# 实现

对于每个区间的限制，我们已经把它拆成了对于区间每个数的因数限制，利用线段树分治，限制一下 $\min A_i$ 即可，不会的自己去学线段树分治。

建议加强数据。

# 代码

~~代码还没写，先咕着。~~

写好了。

```cpp
#include<cstdio>
#define rep(i,l,r) for(int i(l),i##end(r);i<=i##end;++i)
using namespace std;
typedef long long ll;
ll gcd(ll a,ll b) {
	if(!b) return a;
	return gcd(b,a%b);
}
constexpr int N = 2e5 + 9; 
int n,m;
ll tr[N<<2];
int rd() {
	char ch=getchar();
	int x=0;bool f=0;
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-') f=1,ch=getchar();
	while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
void build(int now,int l,int r) {
	tr[now]=1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
}
ll lcm(ll a,ll b) {
	return a/gcd(a,b)*b;
}
void limit(int now,int l,int r,int a,int b,ll v) {
	if(b<l||r<a) return;
	if(a<=l&&r<=b) {
		tr[now]=lcm(tr[now],v);
		return;
	}
	int mid=(l+r)>>1;
	limit(now<<1,l,mid,a,b,v);
	limit(now<<1|1,mid+1,r,a,b,v);
}
int ans[N],X[N],Y[N],Z[N];
void query(int now,int l,int r,ll v) {
	v=lcm(v,tr[now]);
	if(l==r) {
		ans[l]=v;
		return;
	}
	int mid=(l+r)>>1;
	query(now<<1,l,mid,v);
	query(now<<1|1,mid+1,r,v);
}
void rebuild(int now,int l,int r) {
	if(l==r) {
		tr[now]=ans[l];
		return;
	}
	int mid=(l+r)>>1;
	rebuild(now<<1,l,mid);
	rebuild(now<<1|1,mid+1,r);
	tr[now]=gcd(tr[now<<1],tr[now<<1|1]);
}
int Query(int now,int l,int r,int a,int b) {
	if(b<l||r<a) return 0;//注意是0而不是1！ 
	if(a<=l&&r<=b) return tr[now];
	int mid=(l+r)>>1;
	return gcd(Query(now<<1,l,mid,a,b),Query(now<<1|1,mid+1,r,a,b));
}
int main() {
// 	freopen("a.in","r",stdin);
// 	freopen("a.out","w",stdout);
	n=rd();m=rd();
//	printf("%d %d\n",n,m);
// 第一次交的时候调试代码忘删了
	build(1,1,n);
	rep(i,1,m) {
		X[i]=rd();
		Y[i]=rd();
		Z[i]=rd();
		limit(1,1,n,X[i],Y[i],Z[i]);
// 		千万注意，如果写成下面这种写法，因为 右结合特性(应该) 会有问题！！！！！！！！！！ 
//		limit(1,1,n,rd(),rd(),rd());
	}
	query(1,1,n,1);
	rebuild(1,1,n);
	rep(i,1,m) {
		if(Query(1,1,n,X[i],Y[i])!=Z[i]) {
			printf("Impossible\n");
			return 0;
		}
	}
	rep(i,1,n) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

假如有解，那么第 $i$ 个数为所有满足 $X_j \le i \le Y_j$ 的 $j$ 的 $Z_j$ 的最小公倍数这种方案一定是可行的。   
由于 $Z$ 的范围很小，考虑使用 $16$ 个差分数组维护某一个位置被哪些 $Z$ 的限制含盖，求出解后线段树维护并判断是否满足条件即可。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x[200010],y[200010],z[200010],a[20][200010],ans[200010];
struct node{int x,y,v;}tree[800010];
void init(int p,int l,int r)
{
	tree[p].x=l,tree[p].y=r;
	if(l==r)
	{
		tree[p].v=ans[l];
		return;
	}
	int mid=(l+r)/2;
	init(p*2,l,mid),init(p*2+1,mid+1,r);
	tree[p].v=__gcd(tree[p*2].v,tree[p*2+1].v);
}
int query(int p,int l,int r)
{
	if(l<=tree[p].x&&tree[p].y<=r)return tree[p].v;
	int mid=(tree[p].x+tree[p].y)/2;
	int res=0;
	if(l<=mid)res=(!res?query(p*2,l,r):__gcd(res,query(p*2,l,r)));
	if(mid<r)res=(!res?query(p*2+1,l,r):__gcd(res,query(p*2+1,l,r)));
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)cin>>x[i]>>y[i]>>z[i],a[z[i]][x[i]]++,a[z[i]][y[i]+1]--;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=16;j++)
		{
			a[j][i]+=a[j][i-1];
			if(a[j][i])
			{
				if(!ans[i])ans[i]=j;
				else ans[i]=ans[i]*j/__gcd(ans[i],j);
			}
		}
		if(!ans[i])ans[i]=1147434;
	}
	init(1,1,n);
	for(int i=1;i<=m;i++)
	{
		if(query(1,x[i],y[i])!=z[i])
		{
			cout<<"Impossible";
			return 0;
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
	return 0;
}
```

---

## 作者：SolIII (赞：0)

## 前言

[更好的阅读体验](https://www.luogu.com.cn/article/800ar5jf)

模拟赛的 T3，寄了，所以写篇题解。

## 题目分析

### 简化题意

原题已经简化的不能再简化了，这里直接上原题：

构造一个长度为 $N$ 的整数序列 $A$，使得：

1. $\forall i,1\leq A_i\leq 10^9$；
2. $\forall i,\gcd(A_{X_i},A_{X_i+1},\cdots,A_{Y_i})=Z_i$。

或者报告无解。

### 思路

考虑弱化：若将题目中的数据范围 $1\leq Z_i\leq 16$ 改为 $1\leq Z_i\leq 2$，该如何考虑？

因为弱化版的数据范围中，$Z_i$ 的取值只有可能是 $1$ 或 $2$，所以可以优先考虑值为 $2$ 的 $Z_i$，将其范围内的 $A$ 全部赋值为 $2$ 或者任意偶数，再考虑值为 $1$ 的 $Z_i$，看其范围内有没有空出的（即值不为 $2$ 的）地方可以放 $1$，若有，随便找一个地方放了，若没有则输出 `Impossible`。下面是弱化版的部分代码:
```cpp
    bool flagim = false;
    sort(a + 1, a + 1 + m, cmpsub1);
    for(int i = 1;i <= m;i++){
        if(a[i].x == 2){
            for(int j = a[i].l;j <= a[i].r;j++){
                b[j] = 2;
            }
        }
        else{
            bool flag = false;
            for(int j = a[i].l;j <= a[i].r;j++){
                if(b[j] == 1){
                    flag = true;
                    break;
                }
            }
            if(!flag){
                flag = false;
                for(int j = a[i].l;j <= a[i].r;j++){
                    if(b[j] == 0){
                        flag = true;
                        b[j] = 1;
                        break;
                    }
                }
                if(!flag) flagim = true;
            }
        }
    }
    if(flagim){
        printf("Impossible\n");
        return 0;
    }
    for(int i = 1;i <= n;i++){
        printf("%d ", b[i] ? b[i] : 1);
    }
    printf("\n");
```

现在回到本题，本题与弱化版的唯一区别在于其 $Z_i$ 的取值范围更大了。受弱化版的启示，我们可以想出本题的正解。

对于题目给定的每一个区间，标记此区间内必有的因子，标记完后，$A_i$ 的值就是它被标记的数字的最小公倍数的倍数（为了方便起见，在这里我们令它为最小公倍数的 $1$ 倍，即它的最小公倍数本身）。对于无解的情况，可以在构造 $A$ 后再次检验 $A$ 中的每个区间是否满足题目的要求。

考虑具体实现细节：
1. 打标记时进行的是区间操作，且标记的数 $X_i$ 很小，最大值仅为 $16$。所以可以建 $16$ 个差分数组，第 $i$ 个差分数组的第 $j$ 项 `d[i][j]` 表示 $A_j$ 是否要以 $i$ 为因子。
2. 对于验证 $A$ 是否满足要求，易发现不可以直接暴力遍历求最小公倍数，需要使用线段树、ST 表等算法（数据结构）求解。这里我是用的是 ST 表，`dp[i][j]` 表示从 $A_i$ 开始的 $2^j$ 个数的 gcd，转移方程是 $dp_{i, j} \gets \gcd(dp_{i, j - 1}, dp_{i + 2^{j - 1}, j - 1})$。
3. 因为题目中要求 $\forall i,1\leq A_i\leq 10^9$，所以未作要求的数字应赋值为 $1$ 到 $10^9$ 内的正整数。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR = 1.5e5;
const int MR = 16;
const int KR = 19;
struct Node{
    // 输入的构造要求
    int l, r, x;
}b[NR + 10];
int d[MR + 10][NR + 10]; // 差分数组
int dp[NR + 10][KR + 10]; // ST 表
int lcm(int x, int y){
    // 求最小公倍数的函数
    return (x * y) / __gcd(x, y);
}
int cal(int l, int r){
    // ST 表计算函数
    int k = log2(r - l + 1);
    return __gcd(dp[l][k], dp[r - (1 << k) + 1][k]); // 使用 c++ 自带的 gcd 函数
}

int main(){
    // freopen("math.in", "r", stdin);
    // freopen("math.out", "w", stdout);
    // 读入
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1;i <= m;i++){
        scanf("%d%d%d", &b[i].l, &b[i].r, &b[i].x);
        // 差分标记
        d[b[i].x][b[i].l]++;
        d[b[i].x][b[i].r + 1]--;
    }
    // 计算差分数组的前缀和
    for(int i = 1;i <= MR;i++){
        for(int j = 1;j <= n;j++){
            d[i][j] += d[i][j - 1];
        }
    }
    // 计算 A[i] 的值, 这里为节省空间未创建 A 数组, 直接用 dp[i][0] 表示 A[i]
    for(int i = 1;i <= n;i++){
        dp[i][0] = 1; // 未作要求的数字应赋值为 1 到 1e9 内的正整数。
        for(int j = 1;j <= MR;j++){
            // A[i] 的值就是它被标记的数字的最小公倍数的倍数(为了方便起见, 在这里我们令它为最小公倍数的 1 倍, 即它的最小公倍数本身)
            if(d[j][i]) dp[i][0] = lcm(dp[i][0], j);
        }
    }
    // ST 表初始化
    for(int j = 1;j <= log2(n) + 1;j++){
        for(int i = 1;i <= n;i++){
            dp[i][j] = __gcd(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
    // 判断 A 是否满足要求
    for(int i = 1;i <= m;i++){
        if(cal(b[i].l, b[i].r) != b[i].x){
            // 不满足要求, 直接输出后结束程序
            printf("Impossible\n");
            return 0;
        }
    }
    // 满足要求，输出 A 数组
    for(int i = 1;i <= n;i++){
        printf("%d ", dp[i][0]);
    }
    printf("\n");
    return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

### 题意回顾

构造一个序列，使得其满足一些区间 $ \gcd $ 要求。

序列长度及区间个数均在 $ 1.5 \times 10^5 $ 以内，$ \gcd $ 在 $ 16 $ 以内。

### 分析

考虑先让把 $ \gcd $ 这个因数加入到所有区间里的数，然后判断一遍区间 $ \gcd $ 是否正确。

但是 $ a_i = \operatorname{lcm}\{a_i,x\} $ 这个操作很难实现，考虑在值域上做文章，因为 $ \gcd $ 很小，我们可以状态压缩每个数被加入了哪些因数，然后如果区间状态压缩值的与里面有不应该包含的因数输出无解，最后还原出每个数即可。

### 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1.5e5 + 5;
int n, m;
int d[N * 4];
int c[N * 4];
int l[N], r[N], v[N];
inline void pushdown(int p) {
    d[p * 2] |= c[p];
    d[p * 2 + 1] |= c[p];
    c[p * 2] |= c[p];
    c[p * 2 + 1] |= c[p];
    c[p] = 0;
}
inline void pushup(int p) {
    d[p] = d[p * 2] & d[p * 2 + 1];
}
void update(int l, int r, int v, int s, int t, int p) {
    if(l <= s && t <= r) {
        d[p] |= (1 << v);
        c[p] |= (1 << v);
        return;
    }
    pushdown(p);
    int mid = (s + t) >> 1;
    if(l <= mid) update(l, r, v, s, mid, p * 2);
    if(mid < r) update(l, r, v, mid + 1, t, p * 2 + 1);
    pushup(p);
}
int query(int l, int r, int s, int t, int p) {
    if(l <= s && t <= r) return d[p];
    pushdown(p);
    int mid = (s + t) >> 1;
    int res = (1 << 17) - 1;
    if(l <= mid) res &= query(l, r, s, mid, p * 2);
    if(mid < r) res &= query(l, r, mid + 1, t, p * 2 + 1);
    pushup(p);
    return res;
}
int gcd(int x, int y) {
    return (y == 0) ? x : gcd(y, x % y);
}
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &l[i], &r[i], &v[i]);
        update(l[i], r[i], v[i], 1, n, 1);
    }
    for(int i = 1; i <= m; i++) {
        int t = query(l[i], r[i], 1, n, 1);
        for(int j = 1; j <= 16; j++) {
            if(v[i] % j != 0 && (t & (1 << j))) {
                t = -1;
                break;
            }
        }
        if(t == -1) {
            puts("Impossible");
            return 0;
        }
    }
    for(int i = 1; i <= n; i++) {
        int t = query(i, i, 1, n, 1);
        int whr = 1;
        for(int j = 1; j <= 16; j++) {
            if(t & (1 << j)) whr = whr / gcd(whr, j) * j;
        }
        printf("%d ", whr);
    }
    puts("");
    return 0;
}

```

---

