# [ABC357F] Two Sequence Queries

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc357/tasks/abc357_f

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $, $ B=(B_1,B_2,\ldots,B_N) $ が与えられます。  
$ Q $ 個のクエリが与えられるので、順に処理してください。

クエリは次の $ 3 $ 種類です。

- `1 l r x` : $ A_l,\ A_{l+1},\ \ldots,\ A_r $ に $ x $ を加える。
- `2 l r x` : $ B_l,\ B_{l+1},\ \ldots,\ B_r $ に $ x $ を加える。
- `3 l r` : $ \displaystyle\sum_{i=l}^r\ (A_i\times\ B_i) $ を $ 998244353 $ で割った余りを出力する。

## 说明/提示

### 制約

- $ 1\leq\ N,Q\leq\ 2\times\ 10^5 $
- $ 0\leq\ A_i,B_i\leq\ 10^9 $
- $ 1\leq\ l\leq\ r\leq\ N $
- $ 1\leq\ x\leq\ 10^9 $
- 入力はすべて整数
- $ 3 $ 種類目のクエリが $ 1 $ つ以上存在する。

### Sample Explanation 1

最初、$ A=(1,3,5,6,8) $, $ B=(3,1,2,1,2) $ です。クエリは次の順で処理されます。 - $ 1 $ 個目のクエリでは $ (1\times\ 3)+(3\times\ 1)+(5\times\ 2)=16 $ を $ 998244353 $ で割った余りである $ 16 $ を出力します。 - $ 2 $ 個目のクエリでは $ A_2,A_3,A_4,A_5 $ に $ 3 $ を加えます。$ A=(1,6,8,9,11) $ となります。 - $ 3 $ 個目のクエリでは $ (1\times\ 3)+(6\times\ 1)+(8\times\ 2)=25 $ を $ 998244353 $ で割った余りである $ 25 $ を出力します。 - $ 4 $ 個目のクエリでは $ A_1,A_2,A_3 $ に $ 1 $ を加えます。$ A=(2,7,9,9,11) $ となります。 - $ 5 $ 個目のクエリでは $ B_5 $ に $ 2 $ を加えます。$ B=(3,1,2,1,4) $ となります。 - $ 6 $ 個目のクエリでは $ (2\times\ 3)+(7\times\ 1)+(9\times\ 2)+(9\times\ 1)+(11\times\ 4)=84 $ を $ 998244353 $ で割った余りである $ 84 $ を出力します。 よって、$ 1 $, $ 2 $, $ 3 $ 行目にはそれぞれ $ 16 $, $ 25 $, $ 84 $ を出力します。

### Sample Explanation 2

$ 3 $ 種類目のクエリでは $ 998244353 $ で割った余りを出力することに注意してください。

## 样例 #1

### 输入

```
5 6
1 3 5 6 8
3 1 2 1 2
3 1 3
1 2 5 3
3 1 3
1 1 3 1
2 5 5 2
3 1 5```

### 输出

```
16
25
84```

## 样例 #2

### 输入

```
2 3
1000000000 1000000000
1000000000 1000000000
3 1 1
1 2 2 1000000000
3 1 2```

### 输出

```
716070898
151723988```

# 题解

## 作者：Redamancy_Lydic (赞：7)

## 题意

维护一个数据结构，支持两个数列的区间求和，和查询区间内两数列各元素积的和。

## 分析

线段树万岁!

这道题要维护两个序列，所以线段树中要同时存储两个区间和。但还要在维护一个信息，是该区间内两序列元素积的和。大概长这样：

```cpp
struct no
{
	int l,r;
	int da,db,ab;
	int ta,tb;
}t[maxn<<2];
```

其他的更新就不讲了，主要说一说积的和信息的更新。

当更新一个序列时，该信息要传递的信息其实是另一盒序列的和乘上该序列的懒标记，这点很好想。

然后就没有什么问题了。但是注意这道题要取模，你少取一个就废了。

## Code

```cpp
#include<bits/stdc++.h>
//#include<atcoder/modint>
#define int long long
using namespace std;
//using mint=atcoder::modint998244353;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int maxn=1e6+10;
const int mod=998244353;
struct no
{
	int l,r;
	int da,db,ab;
	int ta,tb;
}t[maxn<<2];
int a[maxn],b[maxn],n,Q;
void upd(int p)
{
	t[p].da=(t[p*2].da+t[p*2+1].da)%mod;
	t[p].db=(t[p*2].db+t[p*2+1].db)%mod;
	t[p].ab=(t[p*2].ab+t[p*2+1].ab)%mod;
}
void build(int p,int l,int r)
{
	t[p].l=l,t[p].r=r;
	if(l==r)
	{
		t[p].da=a[l]%mod;t[p].db=b[l]%mod;
		t[p].ab=a[l]*b[l]%mod;
		return ;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	upd(p);
}
void spread(int p)
{
	if(t[p].ta)
	{
		t[p*2].da+=t[p].ta*(t[p*2].r-t[p*2].l+1)%mod;t[p*2].da%=mod;
		t[p*2+1].da+=t[p].ta*(t[1+p*2].r-t[1+p*2].l+1)%mod;t[p*2+1].da%=mod;
		t[p*2].ta+=t[p].ta;t[p*2].ta%=mod;
		t[p*2+1].ta+=t[p].ta;t[p*2+1].ta%=mod;
		t[p*2].ab+=t[p].ta*t[p*2].db%mod;t[p*2].ab%=mod;
		t[p*2+1].ab+=t[p].ta*t[p*2+1].db%mod;t[p*2+1].ab%=mod;
	}
	if(t[p].tb)
	{
		t[p*2].db+=t[p].tb*(t[p*2].r-t[p*2].l+1)%mod;t[p*2].db%=mod;
		t[p*2+1].db+=t[p].tb*(t[1+p*2].r-t[1+p*2].l+1)%mod;t[p*2+1].db%=mod;
		t[p*2].tb+=t[p].tb;t[p*2].tb%=mod;
		t[p*2+1].tb+=t[p].tb;t[p*2+1].tb%=mod;
		t[p*2].ab+=t[p].tb*t[p*2].da%mod;t[p*2].ab%=mod;
		t[p*2+1].ab+=t[p].tb*t[p*2+1].da%mod;t[p*2+1].ab%=mod;
	}
	t[p].ta=0;
	t[p].tb=0;
}
void changea(int p,int l,int r,int k)
{
	if(t[p].l>=l&&t[p].r<=r)
	{
		t[p].da+=k*(t[p].r-t[p].l+1)%mod;t[p].da%=mod;
		t[p].ta+=k;t[p].ta%=mod;
		t[p].ab+=k*t[p].db%mod;t[p].ab%=mod;
		return ;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid)changea(p*2,l,r,k);
	if(mid<r) changea(p*2+1,l,r,k);
	upd(p);
}
void changeb(int p,int l,int r,int k)
{
	if(t[p].l>=l&&t[p].r<=r)
	{
		t[p].db+=k*(t[p].r-t[p].l+1)%mod;t[p].db%=mod;
		t[p].tb+=k;t[p].tb%=mod;
		t[p].ab+=k*t[p].da%mod;t[p].ab%=mod;
		return ;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)>>1;
	if(l<=mid)changeb(p*2,l,r,k);
	if(mid<r) changeb(p*2+1,l,r,k);
	upd(p);
}
int ask(int p,int l,int r)
{
	if(t[p].l>=l&&t[p].r<=r)
	{
		return t[p].ab%mod;
	}
	spread(p);
	int mid=(t[p].l+t[p].r)>>1,sum=0;
	if(l<=mid)sum=(sum+ask(p*2,l,r)%mod)%mod;
	if(mid<r) sum=(sum+ask(p*2+1,l,r)%mod)%mod;
	return sum%mod;
}
signed main()
{
//  freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n>>Q;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	build(1,1,n);
	while(Q--)
	{
		int opt=read(),l=read(),r=read();
		if(opt==3)
		{
			printf("%lld\n",ask(1,l,r)%mod);
			continue;
		} 
		int x=read();
		if(opt==1)changea(1,l,r,x);
		if(opt==2)changeb(1,l,r,x);
	}
	return 0;
}

```

---

## 作者：zhlzt (赞：5)

### 题解
记 $\displaystyle\sum_{i=l}^r(A_i\times B_i)=sum_{l,r}$，$\displaystyle\sum_{i=l}^r A_i=suma_{l,r}$，$\displaystyle\sum_{i=l}^r B_i=sumb_{l,r}$。

分析执行修改操作时 $sum,suma,sumb$ 的值会发生哪些变化：
- `1 l r x` ：$suma_{l,r}\gets suma_{l,r}+x\times(r-l+1)$，$sum_{l,r}\gets sum_{l,r}+sumb_{l,r}\times x$。
- `2 l r x` ：$sumb_{l,r}\gets sumb_{l,r}+x\times(r-l+1)$，$sum_{l,r}\gets sum_{l,r}+suma_{l,r}\times x$。

线段树维护即可，注意 Lazy Tag 要清空，取模要及时，开多倍空间。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int z;
const int mod=998244353;
const int maxn=2e5+10;
int a[maxn],b[maxn];
int taga[maxn<<2],tagb[maxn<<2];
int sum[maxn<<2],suma[maxn<<2],sumb[maxn<<2];
void addtag(z p,z pl,z pr,z d,z k){
	if(k==1){
		(suma[p]+=1ll*d*(pr-pl+1)%mod)%=mod;
		(sum[p]+=1ll*sumb[p]*d%mod)%=mod;
		(taga[p]+=d)%=mod;
	} else {
		(sumb[p]+=1ll*d*(pr-pl+1)%mod)%=mod;
		(sum[p]+=1ll*suma[p]*d%mod)%=mod;
		(tagb[p]+=d)%=mod;
	}
}
void pushup(int p){
	(suma[p]=(suma[p<<1]+suma[p<<1|1])%mod)%=mod;
	(sumb[p]=(sumb[p<<1]+sumb[p<<1|1])%mod)%=mod;
	(sum[p]=(sum[p<<1]+sum[p<<1|1])%mod)%=mod;
}
void pushdown(int p,int pl,int pr){
	int mid=(pl+pr)>>1;
	if(taga[p]){
		addtag(p<<1,pl,mid,taga[p],1);
		addtag(p<<1|1,mid+1,pr,taga[p],1);
		taga[p]=0;
	}
	if(tagb[p]){
		addtag(p<<1,pl,mid,tagb[p],2);
		addtag(p<<1|1,mid+1,pr,tagb[p],2);
		tagb[p]=0;
	}
}
void build(int p,int pl,int pr){
	if(pl==pr){
		suma[p]=a[pl]%mod; sumb[p]=b[pl]%mod;
		sum[p]=1ll*a[pl]*b[pl]%mod; 
		taga[p]=tagb[p]=0; return;
	}
	int mid=(pl+pr)>>1;
	build(p<<1,pl,mid); 
	build(p<<1|1,mid+1,pr);
	pushup(p); return void();
}
void update(z l,z r,z p,z pl,z pr,z d,z k){
	if(l<=pl and pr<=r){addtag(p,pl,pr,d,k);return;}
	int mid=(pl+pr)>>1; pushdown(p,pl,pr);
	if(l<=mid) update(l,r,p<<1,pl,mid,d,k);
	if(r>mid) update(l,r,p<<1|1,mid+1,pr,d,k);
	pushup(p); return void();
}
int query(z l,z r,z p,z pl,z pr){
	if(l<=pl and pr<=r) return sum[p];
	int mid=(pl+pr)>>1; pushdown(p,pl,pr);
	int ans=0;
	if(l<=mid) (ans+=query(l,r,p<<1,pl,mid))%=mod;
	if(r>mid) (ans+=query(l,r,p<<1|1,mid+1,pr))%=mod;
	return ans;
}
int main(){
	int n,q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	build(1,1,n);
	while(q--){
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);
		if(opt==1 or opt==2){
			int d;scanf("%d",&d); update(l,r,1,1,n,d,opt);
		} else {
			printf("%d\n",query(l,r,1,1,n));
		}
	}
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：5)

[[ABC357F] Two Sequence Queries](https://atcoder.jp/contests/abc357/tasks/abc357_f)

Atcoder problems 评分：$\color{blue}{1793}$。

考虑线段树。

```cpp
struct Seg {
	int da, db, suma, sumb, sum;
	#define da(p) t[p].da // a 数组加的值
	#define db(p) t[p].db // b 数组加的值
	#define sa(p) t[p].suma // a 数组之和
	#define sb(p) t[p].sumb // b 数组之和
	#define sum(p) t[p].sum // 答案
}t[N << 4];
```

下传给左儿子（右边同理）：
```cpp
da (ls) = (da (ls) + da (p)) % mod, db (ls) = (db (ls) + db (p)) % mod;
// 更新加数
sum (ls) = (sum (ls) + sb (ls) * da (p) % mod + sa (ls) * db (p) % mod + da (p) * db (p) % mod * (mid - l + 1) % mod) % mod;
// 更新答案
sa (ls) = (sa (ls) + da (p) * (mid - l + 1) % mod) % mod;
// 更新 a 数组之和
sb (ls) = (sb (ls) + db (p) * (mid - l + 1) % mod) % mod;
// 更新 b 数组之和
```

查询和修改都是板子。

**温馨提示：所有地方都对 $998244353$ 取模！** 

[AC 代码](https://atcoder.jp/contests/abc357/submissions/54404993)，时间复杂度 $O(n\log n)$。

---

## 作者：fcy20180201 (赞：3)

省流：爆肝

## 题意

有两个数组 $A,B$，长度均为 $N$。现在执行 $Q$ 次操作，每次操作要么把其中一个数组的一个区间统一加上一个数，要么给定一个区间 $[l,r]$，输出 $\sum_{i=l}^r(A_i\times B_i)$。

考虑线段树。由于我太弱，觉得直接维护不行，就想着转化一下。

$$
\sum_{i=l}^r(A_i\times B_i)=\sum_{i=l}^r\frac{(A_i+B_i)^2-{A_i}^2-{B_i}^2}{2}
$$

很好理解对吧。

于是我们维护 $(A_i+B_i)^2,A_{i}^2,B_{i}^2$，答案就是 $\sum_{i=l}^r\frac{(A_i+B_i)^2-{A_i}^2-{B_i}^2}{2}$。

由于是区间加区间查询，需要打标记，于是下文中的“加上”都是指将标记向下转移时的操作。

假设 $A$ 加上 $V_A$，$B$ 加上 $V_B$，则
$$
((A_i+V_A)+(B_i+V_B))^2\\
=((A_i+B_i)+(V_A+V_B))^2\\
=(A_i+B_i)^2+2\times(A_i+B_i)\times(V_A+V_B)+(V_A+V_B)^2\\

(A_i+V_a)^2={A_i}^2+2\times A_i\times V_a+{V_a}^2
$$

$B_i$ 同理。

所以还需要额外维护区间和即可。

## 代码
~~Talk is cheap.Give me your code.~~

该平方的地方一定别忘了！~~我不会告诉你我赛时就是因为这个寄的。~~

```cpp
#include<bits/stdc++.h>
#define ls cur<<1
#define rs cur<<1|1
using namespace std;
using ll=long long;
const ll mod=998244353,pre=499122177;//pre 是模意义下的 1/2
int n,q,a[200005],b[200005];
struct Tree{
	int len;
	ll suma=0,sqa=0,sumb=0,sqb=0,ssq=0,tga=0,tgb=0;
	void putlz(ll val1,ll val2){//最难的一步打标记
		(tga+=val1)%=mod,(tgb+=val2)%=mod;
		(ssq+=len*(val1+val2)%mod*(val1+val2)%mod+2*(suma+sumb)%mod*(val1+val2)%mod)%=mod;
		(sqa+=val1*val1%mod*len%mod+2*suma%mod*val1%mod)%=mod,(suma+=val1*len%mod)%=mod;
		(sqb+=val2*val2%mod*len%mod+2*sumb%mod*val2%mod)%=mod,(sumb+=val2*len%mod)%=mod;
		return ;
	}
	ll calc(){return ((ssq-sqa-sqb)%mod+mod)%mod*pre%mod;}//算答案
}tr[800005];
void pushup(int cur){//更新父亲节点
	tr[cur].suma=(tr[ls].suma+tr[rs].suma)%mod;
	tr[cur].sumb=(tr[ls].sumb+tr[rs].sumb)%mod;
	tr[cur].sqa=(tr[ls].sqa+tr[rs].sqa)%mod;
	tr[cur].sqb=(tr[ls].sqb+tr[rs].sqb)%mod;
	tr[cur].ssq=(tr[ls].ssq+tr[rs].ssq)%mod;
	return ;
}
void pushdown(int cur){//向下转移标记
	tr[ls].putlz(tr[cur].tga,tr[cur].tgb);
	tr[rs].putlz(tr[cur].tga,tr[cur].tgb);
	tr[cur].tga=tr[cur].tgb=0;return ;
}
void build(int cur,int l,int r){//建树
	tr[cur].len=r-l+1;
	if(l==r){
		tr[cur].suma=a[l]%mod;
		tr[cur].sqa=1ll*a[l]*a[l]%mod;
		tr[cur].sumb=b[r]%mod;
		tr[cur].sqb=1ll*b[r]*b[r]%mod;
		tr[cur].ssq=1ll*(a[l]+b[r])*(a[l]+b[r])%mod;
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(cur);
	return ;
}
void update1(int cur,int l,int r,int ql,int qr,int val){//对 A 操作
	if(ql<=l && r<=qr){tr[cur].putlz(val,0);return ;}
	int mid=(l+r)>>1;pushdown(cur);
	if(ql<=mid)update1(ls,l,mid,ql,qr,val);
	if(qr>mid)update1(rs,mid+1,r,ql,qr,val);
	pushup(cur);
	return ;
}
void update2(int cur,int l,int r,int ql,int qr,int val){//对 B 操作
	if(ql<=l && r<=qr){tr[cur].putlz(0,val);return ;}
	int mid=(l+r)>>1;pushdown(cur);
	if(ql<=mid)update2(ls,l,mid,ql,qr,val);
	if(qr>mid)update2(rs,mid+1,r,ql,qr,val);
	pushup(cur);return ;
}
ll query(int cur,int l,int r,int ql,int qr){//查询
	if(ql<=l && r<=qr)return tr[cur].calc();
	int mid=(l+r)>>1;pushdown(cur);
	ll res=0;
	if(ql<=mid)(res+=query(ls,l,mid,ql,qr))%=mod;
	if(qr>mid)(res+=query(rs,mid+1,r,ql,qr))%=mod;
	pushup(cur);
	return res;
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	build(1,1,n);
	while(q--){
		int op,l,r,x;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1){
			scanf("%d",&x);
			update1(1,1,n,l,r,x);
		}
		else if(op==2){
			scanf("%d",&x);
			update2(1,1,n,l,r,x);
		}
		else printf("%lld\n",query(1,1,n,l,r));
	}
	return 0;
}

```

---

## 作者：EityDawn (赞：3)

# 思路：

线段树模板题。

维护 $A_i\times B_i$ 的和，$A_i$ 的和以及 $B_i$ 的和，两个区间加的 $tag$。

对于 1 操作，考虑它对 $A_i\times B_i$ 的和有什么影响。

由乘法分配律可知，$\sum_{i=l}^r(A_i+x)\times B_i=\sum_{i=l}^{r}A_i\times B_i+\sum_{i=l}^rx\times B_i$，在原来和的基础上加上了 $x\times \sum_{i=l}^rB_i$，维护一个 $B_i$ 的和以及区间加的 $tag$ 就行。

2 操作同理，需要维护 $A_i$ 的和与另一个 $tag$。

记得多取模，取模要彻底。

## code：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<climits>
#include<cmath>
#define int long long
using namespace std;
typedef long long ll;
const int inf=INT_MAX;
const int N=2e5+10;
const int mod=998244353;
int tot=0,rt=0;
int a[N],b[N];
struct node{
	ll A,B;
	ll AB;
	ll ad,bd;
	node(){A=B=AB=ad=bd=0;}
} t[N<<2];
#define A(i) t[i].A
#define B(i) t[i].B
#define AB(i) t[i].AB
#define ad(i) t[i].ad
#define bd(i) t[i].bd
#define ls i<<1
#define rs i<<1|1
int n,m,k;
void push_up(int i)
{
	A(i)=(A(ls)+A(rs))%mod;
	B(i)=(B(ls)+B(rs))%mod;
	AB(i)=(AB(ls)+AB(rs))%mod;
}
void add(int len,int val,int i,bool f)
{
	if(f) AB(i)=(AB(i)+A(i)*val%mod)%mod,B(i)=(B(i)+len*val%mod)%mod,(bd(i)+=val)%=mod;
	else AB(i)=(AB(i)+B(i)*val%mod)%mod,A(i)=(A(i)+len*val%mod)%mod,(ad(i)+=val)%=mod;
}
void push_down(int l,int r,int i)
{
	int mid=(l+r)>>1;
	if(ad(i)) add(mid-l+1,ad(i),ls,0),add(r-mid,ad(i),rs,0),ad(i)=0;
	if(bd(i)) add(mid-l+1,bd(i),ls,1),add(r-mid,bd(i),rs,1),bd(i)=0;
}
void add(int p,int q,int val,int l,int r,int i,bool f)
{
	if(p<=l&&q>=r) return add(r-l+1,val,i,f);
	push_down(l,r,i);
	int mid=(l+r)>>1;
	if(p<=mid) add(p,q,val,l,mid,ls,f);
	if(q>mid) add(p,q,val,mid+1,r,rs,f);
	push_up(i);
}
ll qsum(int p,int q,int l,int r,int i)
{
	if(p<=l&&q>=r) return AB(i);
	push_down(l,r,i);
	int mid=(l+r)>>1;
	ll ans=0;
	if(p<=mid) ans=(ans+qsum(p,q,l,mid,ls))%mod;
	if(q>mid) ans=(ans+qsum(p,q,mid+1,r,rs))%mod;
	return ans;
}
void build(int l,int r,int i)
{
	if(l==r){
		A(i)=a[l]%mod,B(i)=b[l]%mod;
		AB(i)=a[l]*b[l]%mod;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls),build(mid+1,r,rs);
	return push_up(i);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	build(1,n,1);
	int op,l,r;
	while(m--)
	{
		cin>>op>>l>>r;
		if(op==1) cin>>k,add(l,r,k,1,n,1,0);
		else if(op==2) cin>>k,add(l,r,k,1,n,1,1);
		else cout<<qsum(l,r,1,n,1)%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：2)

首先一看这题就是线段树题。题目要求区间 $A_i\times B_i$，肯定得维护这个信息。

但是随之问题就出现了：这个线段树是区间修改的，在维护懒标记时，我们怎么根据 $\displaystyle\sum_{i=l}^r A_i\times B_i$，求出 $\displaystyle\sum_{i=l}^r (A_i+x)\times (B_i+y)$ 呢？

首先根据多项式乘多项式，$\displaystyle\sum_{i=l}^r(A_i+x)\times (B_i+y)=\displaystyle\sum_{i=l}^rA_i B_i+A_iy+B_ix+xy=\displaystyle\sum_{i=l}^rA_i B_i+\displaystyle\sum_{i=l}^rA_iy+\displaystyle\sum_{i=l}^rB_ix+\displaystyle\sum_{i=l}^rxy$。

其中 $\displaystyle\sum_{i=l}^rA_i B_i$ 就是原来我们已知的值。然后 $\displaystyle\sum_{i=l}^rA_iy=y\displaystyle\sum_{i=l}^rA_i$。其中 $\displaystyle\sum_{i=l}^rA_i$ 是区间和，维护即可。$\displaystyle\sum_{i=l}^rB_ix$ 同理。对于 $\displaystyle\sum_{i=l}^rxy$，这个就更好求了。

所以我们需要维护 $3$ 个信息，区间 $A_i$，区间 $B_i$，区间 $A_i\times B_i$。同时维护两个懒标记，维护这个区间 $A_i$ 被加了多少，$B_i$ 加了多少。

由于我的屎山代码取模会挂，所以开了 `__int128`。

```cpp
#include<bits/stdc++.h>
#define int __int128
#define N 200005
#pragma GCC optimize("O3")
using namespace std;
struct Data{int l,r,sum,sum1,sum2,tag1,tag2;}t[N*4];
int n,q,a[N],b[N];
int read()
{
  char c=getchar();
  int x=0;
  while(c<'0'||c>'9') c=getchar();
  while(c>='0'&&c<='9')
  {
    x=(x<<1)+(x<<3)+(c^48);
    c=getchar();
  }
  return x;
}
void write(int x)
{
  if(x>9) write(x/10);
  putchar(x%10+'0');
  return;
}
void maketag(int k,int x,int y)//根据修改一个区间后，他的信息会怎么变化
{
  t[k].sum+=x*t[k].sum2+y*t[k].sum1+(t[k].r-t[k].l+1)*x*y;
  t[k].sum1+=x*(t[k].r-t[k].l+1);
  t[k].sum2+=y*(t[k].r-t[k].l+1);
  t[k].tag1+=x;
  t[k].tag2+=y;
  return;
}
void pushdown(int k)//下传懒标记
{
  maketag(k*2,t[k].tag1,t[k].tag2);
  maketag(k*2+1,t[k].tag1,t[k].tag2);
  t[k].tag1=t[k].tag2=0;
  return;
}
void pushup(int k)
{
  t[k].sum=t[k*2].sum+t[k*2+1].sum;
  t[k].sum1=t[k*2].sum1+t[k*2+1].sum1;
  t[k].sum2=t[k*2].sum2+t[k*2+1].sum2;
  return;
}
void build(int k,int l,int r)
{
  t[k].l=l,t[k].r=r;
  if(l==r)
  {
    t[k].sum=a[l]*b[l];
    t[k].sum1=a[l];
    t[k].sum2=b[l];
    return;
  }
  int mid=l+r>>1;
  build(k*2,l,mid);
  build(k*2+1,mid+1,r);
  pushup(k);
  return;
}
void update1(int k,int l,int r,int x)
{
  if(l<=t[k].l&&t[k].r<=r)
  {
    maketag(k,x,0);//由于是修改A数组，所以相当于B数组加0
    return;
  }
  pushdown(k);
  int mid=t[k].l+t[k].r>>1;
  if(l<=mid) update1(k*2,l,r,x);
  if(r>mid) update1(k*2+1,l,r,x);
  pushup(k);
  return;
}
void update2(int k,int l,int r,int x)
{
  if(l<=t[k].l&&t[k].r<=r)
  {
    maketag(k,0,x);
    return;
  }
  pushdown(k);
  int mid=t[k].l+t[k].r>>1;
  if(l<=mid) update2(k*2,l,r,x);
  if(r>mid) update2(k*2+1,l,r,x);
  pushup(k);
  return;
}
int query(int k,int l,int r)
{
  if(l<=t[k].l&&r>=t[k].r) return t[k].sum;
  pushdown(k);
  int mid=t[k].l+t[k].r>>1,ans=0;
  if(l<=mid) ans+=query(k*2,l,r);
  if(r>mid) ans+=query(k*2+1,l,r);
  return ans;
}
signed main()
{
  ios::sync_with_stdio(0);
  n=read(),q=read();
  for(int i=1;i<=n;i++) a[i]=read();
  for(int i=1;i<=n;i++) b[i]=read();
  build(1,1,n);
  while(q--)
  {
    int op,x,y,z;
    op=read(),x=read(),y=read();
    if(op==1)
    {
      z=read();
      update1(1,x,y,z);
    }
    if(op==2)
    {
      z=read();
      update2(1,x,y,z);
    }
    if(op==3) write(query(1,x,y)%998244353),putchar('\n');
  }
  return 0;
}
```

---

## 作者：Vitamin_B (赞：1)

# 思路
显然线段树。

首先肯定要维护一个 $mul$ 数组，表示 $\sum\limits_{i=l}^ra_i\times b_i$。然后看看如何在更新时更改这个值。

先让 $a_l\sim a_r$ 都加上一个 $x$，$b_l\sim b_r$ 加上 $y$，则新的值 $=\sum\limits_{i=l}^r(a_i+x)\times(b_i+x)=\sum\limits_{i=l}^r(a_i\times b_i+a_ix+b_iy+xy)=mul+[(\sum\limits_{i=l}^ra_i)\times y]+[(\sum\limits_{i=l}^rb_i)\times x]+xy\times(r-l+1)$，所以我们显然还要维护 $suma$ 和 $sumb$ 两个值。然后利用这个公式把两个懒标记同时 pushdown 即可。

[Code](https://atcoder.jp/contests/abc357/submissions/54399125)。

---

## 作者：Genius_Star (赞：1)

### 思路：

简单题。

考虑使用线段树维护区间 $A$ 的和 $s_1$，$B$ 的和 $s_2$，$A_i \times B_i$ 的按位和 $data$。

每次操作可能是如下两种：

$$\sum_{i=l}^r A_i \times (B_i + v) = data + s_1 \times v$$

$$\sum_{i=l}^r (A_i+v) \times B_i = data+s_2 \times v$$

懒标记维护即可。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=2e5+10,mod=998244353;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll l,r,len;
	ll s1,s2;
	ll data;
	ll tag1,tag2;
}X[N<<2];
ll n,q,op,l,r,x;
ll a[N],b[N];
void pushup(ll k){
	X[k].s1=(X[k<<1].s1+X[k<<1|1].s1)%mod;
	X[k].s2=(X[k<<1].s2+X[k<<1|1].s2)%mod;
	X[k].data=(X[k<<1].data+X[k<<1|1].data)%mod;
}
void add1(ll k,ll v){
	X[k].data=Add(X[k].data,(v*X[k].s2)%mod);
	X[k].s1=Add(X[k].s1,X[k].len*v%mod);
	X[k].tag1=Add(X[k].tag1,v);
}
void add2(ll k,ll v){
	X[k].data=Add(X[k].data,(v*X[k].s1)%mod);
	X[k].s2=Add(X[k].s2,X[k].len*v%mod);
	X[k].tag2=Add(X[k].tag2,v);
}
void push_down(ll k){
	if(X[k].tag1){
		add1(k<<1,X[k].tag1);
		add1(k<<1|1,X[k].tag1);
		X[k].tag1=0;
	}
	if(X[k].tag2){
		add2(k<<1,X[k].tag2);
		add2(k<<1|1,X[k].tag2);
		X[k].tag2=0;
	}
}
void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	X[k].len=r-l+1;
	if(l==r){
		X[k].s1=a[l];
		X[k].s2=b[l];
		X[k].data=a[l]*b[l]%mod;
		return ;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void update(ll k,ll l,ll r,ll v,bool f){
	if(X[k].l==l&&r==X[k].r){
		if(f)
		  add2(k,v);
		else
		  add1(k,v);
		return ; 
	}
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  update(k<<1,l,r,v,f);
	else if(l>mid)
	  update(k<<1|1,l,r,v,f);
	else{
		update(k<<1,l,mid,v,f);
		update(k<<1|1,mid+1,r,v,f);
	}
	pushup(k);
}
ll query(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].data;
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return query(k<<1,l,r);
	else if(l>mid)
	  return query(k<<1|1,l,r);
	else
	  return Add(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	for(int i=1;i<=n;i++)
	  b[i]=read();
	build(1,1,n);
	while(q--){
		op=read(),l=read(),r=read();
		if(op<=2)
		  update(1,l,r,read(),op-1);
		else{
			write(query(1,l,r));
			putchar('\n');
		}
	}
	return 0;
}
```

~~代码可读性够好了吧……~~

---

## 作者：wmrqwq (赞：0)

# 题目链接

[链接 (atcoder)](https://atcoder.jp/contests/abc357/tasks/abc357_f)

[链接 (luogu)](https://www.luogu.com.cn/problem/AT_abc357_f)

# 解题思路

数据结构板子题。

设 $ans_i = a_i \times b_i$（$a_i$ 和 $b_i$ 是此时的 $a_i,b_i$）。

设 $f1(i,j)$ 表示 $a_i + a_{i+1} + a_{i+2} + \dots + a_j$ 的值。

设 $f2(i,j)$ 表示 $b_i + b_{i+1} + b_{i+2} + \dots + b_j$ 的值。

设 $f3(i,j)$ 表示 $ans_i + ans_{i+1} + ans_{i+2} + \dots + ans_j$ 的值。

我们发现两个序列是可以单独维护的，

接下来分讨三种操作：

- 当进行操作一时，由乘法结合律可得操作一等价于于把 $ans_i$ 加上 $f2(l,r) \times x$。

- 当进行操作二时，由乘法结合律可得操作二等价于于把 $ans_i$ 加上 $f1(l,r) \times x$。

- 当进行操作三时，答案即为 $f3(l,r)$。

用分块维护每种操作即可，时间复杂度 $O(q \sqrt{n})$，时限 5s，不用担心被卡常。

这题要**时刻注意取模**，不然就会爆 `long long`。

如果你只 AC 了 $17$ 个点，不妨检查一下你哪里爆 `long long` 了。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n,q;
ll sq;
ll a[200010],b[200010];
ll sum1[200010],sum2[200010];
ll mul[200010];
ll L[200010],R[200010],bl[200010],tag1[200010],tag2[200010];
ll mod=998244353;
void upd(ll x)
{
	tag1[x]%=mod,tag2[x]%=mod;
	forl(i,L[x],R[x])
		a[i]+=tag1[x],b[i]+=tag2[x],a[i]%=mod,b[i]%=mod;
	tag1[x]=tag2[x]=0;
	ll su1=0,su2=0;
	forl(i,L[x],R[x])
		su1+=a[i],su2+=b[i];
	sum1[x]=su1%mod,sum2[x]=su2%mod;
	mul[x]=0;
	forl(i,L[x],R[x])
		mul[x]+=a[i]*b[i]%mod,mul[x]%=mod;
}
void add1(ll l,ll r,ll x)
{
	if(bl[l]==bl[r])
	{
		upd(bl[l]);
		forl(i,l,r)
			a[i]+=x,a[i]%=mod;
		upd(bl[l]);
		return ;
	}
	upd(bl[l]);
	forl(i,l,R[bl[l]])
		a[i]+=x;
	upd(bl[l]);
	upd(bl[r]);
	forl(i,L[bl[r]],r)
		a[i]+=x;
	upd(bl[r]);
	forl(i,bl[l]+1,bl[r]-1)
		tag1[i]+=x,tag1[i]%=mod,sum1[i]+=(R[i]-L[i]+1)*x%mod,sum1[i]%=mod,mul[i]+=x*sum2[i]%mod,mul[i]%=mod;
}
void add2(ll l,ll r,ll x)
{
	if(bl[l]==bl[r])
	{
		upd(bl[l]);
		forl(i,l,r)
			b[i]+=x,b[i]%=mod;
		upd(bl[l]);
		return ;
	}
	upd(bl[l]);
	forl(i,l,R[bl[l]])
		b[i]+=x;
	upd(bl[l]);
	upd(bl[r]);
	forl(i,L[bl[r]],r)
		b[i]+=x;
	upd(bl[r]);
	forl(i,bl[l]+1,bl[r]-1)
		tag2[i]+=x,tag2[i]%=mod,sum2[i]+=(R[i]-L[i]+1)*x%mod,sum2[i]%=mod,mul[i]+=x*sum1[i]%mod;
}
ll query(ll l,ll r)
{
	if(bl[l]==bl[r])
	{
		upd(bl[l]);
		ll ans=0;
		forl(i,l,r)
			ans+=(a[i]+tag1[bl[l]])*(b[i]+tag2[bl[l]])%mod,ans%=mod;
		return ans;
	}
	ll ans=0;
	upd(bl[l]);
	forl(i,l,R[bl[l]])
		ans+=(a[i]+tag1[bl[l]])*(b[i]+tag2[bl[l]])%mod,ans%=mod;
	upd(bl[r]);
	forl(i,L[bl[r]],r)
		ans+=(a[i]+tag1[bl[r]])*(b[i]+tag2[bl[r]])%mod,ans%=mod;
	forl(i,bl[l]+1,bl[r]-1)
		ans+=mul[i]%mod,ans%=mod;
	return ans;
}
void solve()
{
	cin>>n>>q;
	sq=sqrt(n);
	forl(i,1,n)
		cin>>a[i],a[i]%=mod;
	forl(i,1,n)
		cin>>b[i],b[i]%=mod;
	forl(i,1,n)
	{
		L[i]=R[i-1]+1;
		R[i]=min(sq*i,n);
		forl(j,L[i],R[i])
			bl[j]=i,sum1[i]+=a[j],sum2[i]+=b[j],mul[i]+=a[j]*b[j]%mod,mul[i]%=mod,sum1[i]%=mod,sum2[i]%=mod;
		if(R[i]==n)
			break;
	}
	while(q--)
	{
		ll opt,l,r,x;
		cin>>opt;
		if(opt==1)
		{
			cin>>l>>r>>x;
			add1(l,r,x);
		}
		else if(opt==2)
		{
			cin>>l>>r>>x;
			add2(l,r,x);
		}
		else
		{
			cin>>l>>r;
			cout<<query(l,r)<<endl;
		}
	}
}
int main()
{
	IOS;
	t=1;
//	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：YuYuanPQ (赞：0)

AtCoder 最近出的板子题有点多。

这熟悉的操作序号和经典的操作，使我们想到了线段树。

虽然参与计算的有 $2$ 个数组，但是没有影响。

在函数中传递 bool 类型的变量 $p$：

- $p=0$，更新 a 数组的。
- $p=1$，更新 b 数组的。

这样就不必分别写 $2$ 个函数了。

~~板子有什么好讲的~~

## Code

[Link](https://atcoder.jp/contests/abc357/submissions/54420914)

---

## 作者：f_hxr_ (赞：0)

老外会数据结构，老外会数据结构！

~~第一眼还以为是我自己出过的唐氏题，第二眼才发现求的是 $\sum$ 而不是 $\max$。~~

水题。考虑怎么维护懒标记及其下传。假设我们要为区间 $A_{L,R}$ 加上 $X$，$B_{L,R}$ 加上 $Y$，则我们要维护：

$$\sum_{i=L}^{R}(A_i+X)(B_i+Y)$$

将 $\sum$ 里面的一坨展开：

$$\sum_{i=L}^{R}(A_iB_i+A_iY+B_iX+XY)$$

分离一下：

$$\sum_{i=L}^{R}A_iB_i+\sum_{i=L}^{R}A_iY+\sum_{i=L}^{R}B_iX+\sum_{i=L}^{R}XY$$

将里面的常数拿出来：

$$\sum_{i=L}^{R}A_iB_i+Y\sum_{i=L}^{R}A_i+X\sum_{i=L}^{R}B_i+(R-L+1)XY$$

于是我们只需要用线段树维护 $\sum_{i=L}^{R}A_i$ 与 $\sum_{i=L}^{R}B_i$ 即可。

[AC ](https://www.luogu.com.cn/record/161802041)代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=3e5+7;
const LL MOD=998244353;
LL N,Q,temp_arr[maxn],temp_brr[maxn];
namespace SEG{
	LL ans[maxn<<2];
	LL suma[maxn<<2],sumb[maxn<<2];
	LL addv[maxn<<2],bddv[maxn<<2];
	inline void AddTag(int p,LL xx,LL Len){
		ans[p]=(ans[p]+(sumb[p]*xx%MOD))%MOD;
		suma[p]=(suma[p]+(xx*Len%MOD))%MOD;
		addv[p]=(addv[p]+xx)%MOD;
	}
	inline void BddTag(int p,LL xx,LL Len){
		ans[p]=(ans[p]+(suma[p]*xx%MOD))%MOD;
		sumb[p]=(sumb[p]+(xx*Len%MOD))%MOD;
		bddv[p]=(bddv[p]+xx)%MOD;
	}
	inline void pushup(int p){
		ans[p]=(ans[p<<1]+ans[p<<1|1])%MOD;
		suma[p]=(suma[p<<1]+suma[p<<1|1])%MOD;
		sumb[p]=(sumb[p<<1]+sumb[p<<1|1])%MOD;
	}
	inline void pushdown(int p,LL Len,LL Ren){
		if(addv[p]){
			AddTag(p<<1,addv[p],Len);
			AddTag(p<<1|1,addv[p],Ren);
			addv[p]=0;
		}
		if(bddv[p]){
			BddTag(p<<1,bddv[p],Len);
			BddTag(p<<1|1,bddv[p],Ren);
			bddv[p]=0;
		}
	}
	void build(int p,int L,int R,LL* arr,LL* brr){
		if(L>=R){
			suma[p]=arr[L];sumb[p]=brr[L];
			ans[p]=suma[p]*sumb[p]%MOD;
			return;
		}
		int mid=(L+R)>>1;
		build(p<<1,L,mid,arr,brr);build(p<<1|1,mid+1,R,arr,brr);
		pushup(p);
	}
	void ModifyRange(int p,int L,int R,int ql,int qr,LL xx){
		if(ql<=L&&R<=qr){AddTag(p,xx,R-L+1);return;}
		int mid=(L+R)>>1;pushdown(p,mid-L+1,R-mid);
		if(ql<=mid)ModifyRange(p<<1,L,mid,ql,qr,xx);
		if(mid+1<=qr)ModifyRange(p<<1|1,mid+1,R,ql,qr,xx);
		pushup(p);
	}
	void ModifyRbnge(int p,int L,int R,int ql,int qr,LL xx){
		if(ql<=L&&R<=qr){BddTag(p,xx,R-L+1);return;}
		int mid=(L+R)>>1;pushdown(p,mid-L+1,R-mid);
		if(ql<=mid)ModifyRbnge(p<<1,L,mid,ql,qr,xx);
		if(mid+1<=qr)ModifyRbnge(p<<1|1,mid+1,R,ql,qr,xx);
		pushup(p);
	}
	LL Query(int p,int L,int R,int ql,int qr){
		if(ql<=L&&R<=qr)return ans[p];
		int mid=(L+R)>>1;pushdown(p,mid-L+1,R-mid);
		LL ret=0;
		if(ql<=mid)ret=(ret+Query(p<<1,L,mid,ql,qr))%MOD;
		if(mid+1<=qr)ret=(ret+Query(p<<1|1,mid+1,R,ql,qr))%MOD;
		return ret;
	}
}
signed main(){
	scanf("%lld %lld",&N,&Q);
	for(int i=1;i<=N;i++)scanf("%lld",&temp_arr[i]);
	for(int i=1;i<=N;i++)scanf("%lld",&temp_brr[i]);
	SEG::build(1,1,N,temp_arr,temp_brr);
	while(Q--){
		int op,l,r;scanf("%d %d %d",&op,&l,&r);
		if(op==1){
			LL xx;scanf("%lld",&xx);
			SEG::ModifyRange(1,1,N,l,r,xx);
		}else if(op==2){
			LL xx;scanf("%lld",&xx);
			SEG::ModifyRbnge(1,1,N,l,r,xx);
		}else if(op==3){
			printf("%lld\n",SEG::Query(1,1,N,l,r));
		}
	}
	return 0;
}
```

---

## 作者：DrAlfred (赞：0)

摘要：数据结构，线段树，数学

[传送门：https://www.luogu.com.cn/problem/AT_abc357_f](https://www.luogu.com.cn/problem/AT_abc357_f)

## 题意

给定两个长度为 $N$ 的序列 $A_N, B_N$，现在需要维护 $Q$ 次以下三种操作：

- `1 l r x` 将 $A_l, A_{l + 1}, \cdots, A_r$ 全部加 $x$；
- `2 l r x` 将 $B_l, B_{l + 1}, \cdots, B_r$ 全部加 $x$；
- `3 l r` 求 $\sum_{i = l}^r A_i \times B_i \bmod 998244353$。

## 分析思路

区间加考虑线段树维护。我们以操作一为例进行一下分析。

如果区间 $A_l, A_{l + 1}, \cdots, A_r$ 全部加了 $x$，那么该区间查询的结果会变为：

$$
\begin{aligned}
ans &= \sum_{i = l}^r (A_i + x) \times B_i \\
&=  \sum_{i = l}^r A_i \times B_i + \sum_{i = l}^r x \times B_i \\
&= \sum_{i = l}^r A_i \times B_i + x \times \sum_{i = l}^r B_i
\end{aligned}
$$

也就是说，我们还需要维护 $B_l, B_{l + 1}, \cdots, B_r$ 的和，这样我们就能快速完成某段区间的操作一了。

操作二同理。记得进行操作前先进行 pushdown 操作。

时间复杂度 $O\left((n + q) \log n\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template <int mod>
inline uint64_t down(uint64_t x) { return x >= mod ? x - mod : x; }
template <int mod>
struct ModInt {
    uint64_t x;
    ModInt() = default;
    ModInt(uint64_t x) : x(x % mod) {}
    friend istream &operator>>(istream &in, ModInt &a) { return in >> a.x; }
    friend ostream &operator<<(ostream &out, ModInt a) { return out << a.x; }
    friend ModInt operator+(ModInt a, ModInt b) { return down<mod>(a.x + b.x); }
    friend ModInt operator-(ModInt a, ModInt b) { return down<mod>(a.x - b.x + mod); }
    friend ModInt operator*(ModInt a, ModInt b) { return (__int128)a.x * b.x % mod; }
    friend ModInt operator/(ModInt a, ModInt b) { return a * ~b; }
    friend ModInt operator^(ModInt a, int b) {
        ModInt ans = 1;
        for (; b; b >>= 1, a *= a)
            if (b & 1) ans *= a;
        return ans;
    }
    friend ModInt operator~(ModInt a) { return a ^ (mod - 2); }
    friend ModInt operator-(ModInt a) { return down<mod>(mod - a.x); }
    friend ModInt &operator+=(ModInt &a, ModInt b) { return a = a + b; }
    friend ModInt &operator-=(ModInt &a, ModInt b) { return a = a - b; }
    friend ModInt &operator*=(ModInt &a, ModInt b) { return a = a * b; }
    friend ModInt &operator/=(ModInt &a, ModInt b) { return a = a / b; }
    friend ModInt &operator^=(ModInt &a, int b) { return a = a ^ b; }
    friend ModInt &operator++(ModInt &a) { return a += 1; }
    friend ModInt operator++(ModInt &a, int) {
        ModInt x = a;
        a += 1;
        return x;
    }
    friend ModInt &operator--(ModInt &a) { return a -= 1; }
    friend ModInt operator--(ModInt &a, int) {
        ModInt x = a;
        a -= 1;
        return x;
    }
    friend bool operator==(ModInt a, ModInt b) { return a.x == b.x; }
    friend bool operator!=(ModInt a, ModInt b) { return !(a == b); }
};
using mint = ModInt<998244353>;
const int N = 400010;
struct Node {
    int l, r;
    mint sa, sb, sum, la, lb;
    inline int mid(void) { return (l + r) >> 1; }
    inline int len(void) { return r - l + 1; }
    inline void addA(mint x) {
        sum += sb * x, sa += len() * x, la += x;
    }
    inline void addB(mint x) {
        sum += sa * x, sb += len() * x, lb += x;
    }
} tr[N << 2];
int n, q, a[N], b[N], opt, l, r, x;
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return p << 1 | 1; }
inline void maintain(int p) {
    tr[p].sa = tr[ls(p)].sa + tr[rs(p)].sa;
    tr[p].sb = tr[ls(p)].sb + tr[rs(p)].sb;
    tr[p].sum = tr[ls(p)].sum + tr[rs(p)].sum;
}
inline void pushdown(int p) {
    if (tr[p].la != 0) {
        tr[ls(p)].addA(tr[p].la);
        tr[rs(p)].addA(tr[p].la);
        tr[p].la = 0;
    }
    if (tr[p].lb != 0) {
        tr[ls(p)].addB(tr[p].lb);
        tr[rs(p)].addB(tr[p].lb);
        tr[p].lb = 0;
    }
}
inline void build(int p, int l, int r) {
    tr[p] = {l, r};
    if (l == r) {
        tr[p] = {l, r, a[l], b[l], (mint)a[l] * b[l]};
        return;
    }
    int m = (l + r) >> 1;
    build(ls(p), l, m);
    build(rs(p), m + 1, r);
    maintain(p);
}
inline void addA(int p, int l, int r, mint x) {
    pushdown(p);
    if (l <= tr[p].l && tr[p].r <= r) {
        return tr[p].addA(x);
    }
    int m = tr[p].mid();
    if (l <= m) addA(ls(p), l, r, x);
    if (r > m) addA(rs(p), l, r, x);
    maintain(p);
}
inline void addB(int p, int l, int r, mint x) {
    pushdown(p);
    if (l <= tr[p].l && tr[p].r <= r) {
        return tr[p].addB(x);
    }
    int m = tr[p].mid();
    if (l <= m) addB(ls(p), l, r, x);
    if (r > m) addB(rs(p), l, r, x);
    maintain(p);
}
inline mint query(int p, int l, int r) {
    pushdown(p);
    if (l <= tr[p].l && tr[p].r <= r) {
        return tr[p].sum;
    }
    mint ans = 0;
    int m = tr[p].mid();
    if (l <= m) ans += query(ls(p), l, r);
    if (r > m) ans += query(rs(p), l, r);
    return ans;
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    build(1, 1, n);
    while (q--) {
        cin >> opt >> l >> r;
        if (opt == 1) {
            cin >> x, addA(1, l, r, x);
        } else if (opt == 2) {
            cin >> x, addB(1, l, r, x);
        } else {
            cout << query(1, l, r) << '\n';
        }
    }
    return 0;
}

```

---

## 作者：incra (赞：0)

### Solution
 简单数据结构题，赛时抽了，写了分块，事实上线段树更好写。
 
 考虑在一个块里维护 $suma,sumb,res$ 还有懒标记 $adda,addb$，这里提一下为什么要维护 $suma,sumb$：在修改操作中，修改完整的块的时候，如果第一种修改操作那么答案会加上 $d\times sumb$ 其中 $d$ 是增加的数，$sumb$ 是当前块的 $b_i$ 的总和。
 
 其他的实现都还挺简单的，具体可以看代码，注意暴力维护一个块的时候要注意先清空懒标记（类似线段树的 push\_down）然后再维护，这样做是因为懒标记不为 $0$ 的块不方便直接修改其中的数。
 ### Code
 ```
 #include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define puts(s) cout << s << endl
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
const int N = 200010,M = 1010,MOD = 998244353;
int n,q;
LL a[N],b[N];
int L[M],R[M];
int pos[N];
LL res1[N],res2[M];	// 分别维护一个下标的答案和一个块的答案
LL suma[M],sumb[M];
LL adda[M],addb[M];
void updata (int x) {	// 这里实现了清空懒标记并维护信息，类似于线段树的 push_down 和 push_up 操作
	for (int i = L[x];i <= R[x];i++) {
		a[i] = (a[i] + adda[x]) % MOD;
		b[i] = (b[i] + addb[x]) % MOD;
		res1[i] = a[i] * b[i] % MOD;
	}
	adda[x] = addb[x] = 0;
	suma[x] = sumb[x] = res2[x] = 0;
	for (int i = L[x];i <= R[x];i++) {
		res2[x] = (res2[x] + res1[i]) % MOD;
		suma[x] = (suma[x] + a[i]) % MOD;
		sumb[x] = (sumb[x] + b[i]) % MOD;
	}
}
void modifya (int l,int r,LL x) {
	int p = pos[l],q = pos[r];
	if (p == q) {
		updata (p);
		for (int i = l;i <= r;i++) a[i] = (a[i] + x) % MOD;
		updata (p);
		return ;
	}
	for (int i = p + 1;i <= q - 1;i++) {
		adda[i] = (adda[i] + x) % MOD;
		res2[i] = (res2[i] + x * sumb[i] % MOD) % MOD;
		suma[i] = (suma[i] + x * (R[i] - L[i] + 1) % MOD) % MOD;
	}
	updata (p);
	for (int i = l;i <= R[p];i++) a[i] = (a[i] + x) % MOD;
	updata (p);
	updata (q);
	for (int i = L[q];i <= r;i++) a[i] = (a[i] + x) % MOD;
	updata (q);
}
void modifyb (int l,int r,LL x) {
	int p = pos[l],q = pos[r];
	if (p == q) {
		updata (p);
		for (int i = l;i <= r;i++) b[i] = (b[i] + x) % MOD;
		updata (p);
		return ;
	}
	for (int i = p + 1;i <= q - 1;i++) {
		addb[i] = (addb[i] + x) % MOD;
		res2[i] = (res2[i] + x * suma[i] % MOD) % MOD;
		sumb[i] = (sumb[i] + x * (R[i] - L[i] + 1) % MOD) % MOD;
	}
	updata (p);
	for (int i = l;i <= R[p];i++) b[i] = (b[i] + x) % MOD;
	updata (p);
	updata (q);
	for (int i = L[q];i <= r;i++) b[i] = (b[i] + x) % MOD;
	updata (q);
}
LL query (int l,int r) {
	int p = pos[l],q = pos[r];
	if (p == q) {
		updata (p);
		LL ans = 0;
		for (int i = l;i <= r;i++) ans = (ans + res1[i]) % MOD;
		return ans;
	}
	LL ans = 0;
	for (int i = p + 1;i <= q - 1;i++) ans = (ans + res2[i]) % MOD;
	updata (p);
	for (int i = l;i <= R[p];i++) ans = (ans + res1[i]) % MOD;
	updata (q);
	for (int i = L[q];i <= r;i++) ans = (ans + res1[i]) % MOD;
	return ans;
}
int main () {
	cin >> n >> q;
	for (int i = 1;i <= n;i++) cin >> a[i],a[i] %= MOD;
	for (int i = 1;i <= n;i++) cin >> b[i],b[i] %= MOD;
	for (int i = 1;i <= n;i++) res1[i] = a[i] * b[i] % MOD;
	int len = sqrt (n);
	for (int i = 1;i <= len;i++) L[i] = (i - 1) * len + 1,R[i] = i * len;
	if (R[len] < n) len++,L[len] = R[len - 1] + 1,R[len] = n;
	for (int i = 1;i <= len;i++) {
		for (int j = L[i];j <= R[i];j++) {
			pos[j] = i;
			res2[i] = (res2[i] + res1[j]) % MOD;
			suma[i] = (suma[i] + a[j]) % MOD;
			sumb[i] = (sumb[i] + b[j]) % MOD;
		}
	}
	while (q--) {
		int op,l,r;
		cin >> op >> l >> r;
		if (op == 1) {
			int x;
			cin >> x;
			modifya (l,r,x);
		}
		else if (op == 2) {
			int x;
			cin >> x;
			modifyb (l,r,x);
		}
		else cout << query (l,r) << endl;
//		for (int i = 1;i <= n;i++) cout << a[i] << ' ';
//		cout << endl;
//		for (int i = 1;i <= n;i++) cout << b[i] << ' ';
//		cout << endl;
//		puts ("-----start-----");
//		for (int i = 1;i <= len;i++) {
//			cout << L[i] << ' ' << R[i] << ' ' << suma[i] << ' ' << sumb[i] << ' ' << res2[i] << endl;
//		}
//		puts ("------end------");
	}
	return 0;
}
 ```

---

## 作者：ttq012 (赞：0)

区间修改区间查询很显然的线段树。

考虑对于线段树的每一个结点维护 $A$ 的和，$B$ 的和，$A$ 的懒标记，$B$ 的懒标记，当前区间内的答案的和。

首先 `push_up` 的时候直接将 $A$，$B$ 的和和答案的和全部直接把左右儿子的值加起来即可。

修改的时候：

+ 若当前修改的是 $A$ 的值，则答案从 $a_l\times b_l+a_{l+1}\times b_{l+1}+\ldots+a_r\times b_r$ 变为了 $(a_l+v)\times b_l+(a_{l+1}+v)\times b_{l+1}+\ldots+(a+r+v)\times b_r$。显然后面的式子为 $(a_l\times b_l+a_{l+1}\times b_{l+1}+\ldots+a_r\times b_r)+v\times (b_l+b_{l+1}+b_{l+2}+\ldots+b_r)=(a_l\times b_l+a_{l+1}\times b_{l+1}+\ldots+a_r\times b_r)+v\times B$。所以更新答案的时候直接把 $A$ 加上 $(r-l+1)\times v$，总和加上 $v\times B$ 即可。
+ 若当前修改的为 $B$ 的值，则和 $A$ 的情况一样，$B$ 加上 $(r-l+1)\times v$，总和加上 $v\times A$ 即可。

下传标记直接按照 $A$，$B$ 的顺序下传即可，时间复杂度为 $O(n\log n)$。注意不要爆 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
#define said(...)
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;++i)
#define G(i,x,y) for(int i=x;i>=y;--i)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#define inf (7611257611378358090ll/2)
using namespace std;
const int N = 200100;
const int mod = 998244353;

int a[N], b[N];
struct Node {
    int l, r, a, b, taga, tagb, sum;
    void init(int p) {
        l = r = p;
        a = ::a[p];
        a %= mod;
        b = ::b[p];
        b %= mod;
        taga = tagb = 0;
        sum = a * b % mod;
    }
    void c1(int v) {
        v %= mod;
        taga += v, a += (r - l + 1) * v;
        sum += v * b; sum %= mod;
        taga %= mod, a %= mod;
        // sum += b * v;
    }
    void c2(int v) {
        v %= mod;
        tagb += v, b += (r - l + 1) * v;
        sum += v * a % mod; sum %= mod;
        tagb %= mod, b %= mod;
        // sum = a * b;
    }
} z[N << 2];
Node operator+(const Node &l, const Node &r) {
    Node res;
    res.l = l.l, res.r = r.r;
    res.a = l.a + r.a, res.b = l.b + r.b, res.sum = l.sum + r.sum;
    res.a %= mod, res.b %= mod, res.sum %= mod;
    res.taga = res.tagb = 0;
    return res;
}
void build(int l, int r, int rt) {
    if (l == r) {
        return z[rt].init(l);
    }
    int mid = l + r >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    z[rt] = z[rt << 1] + z[rt << 1 | 1];
}
void pud(int rt) {
    if (z[rt].taga != 0) {
        z[rt << 1].c1(z[rt].taga);
        z[rt << 1 | 1].c1(z[rt].taga);
        z[rt].taga = 0;
    }
    if (z[rt].tagb != 0) {
        z[rt << 1].c2(z[rt].tagb);
        z[rt << 1 | 1].c2(z[rt].tagb);
        z[rt].tagb = 0;
    }
}
void modify1(int l, int r, int rt, int ll, int rr, int v) {
    if (ll <= l && r <= rr) {
        return z[rt].c1(v);
    }
    int mid = l + r >> 1;
    pud(rt);
    if (ll <= mid) {
        modify1(l, mid, rt << 1, ll, rr, v);
    }
    if (mid < rr) {
        modify1(mid + 1, r, rt << 1 | 1, ll, rr, v);
    }
    z[rt] = z[rt << 1] + z[rt << 1 | 1];
}
void modify2(int l, int r, int rt, int ll, int rr, int v) {
    if (ll <= l && r <= rr) {
        return z[rt].c2(v);
    }
    int mid = l + r >> 1;
    pud(rt);
    if (ll <= mid) {
        modify2(l, mid, rt << 1, ll, rr, v);
    }
    if (mid < rr) {
        modify2(mid + 1, r, rt << 1 | 1, ll, rr, v);
    }
    z[rt] = z[rt << 1] + z[rt << 1 | 1];
}
int query(int l, int r, int rt, int ll, int rr, int v) {
    if (ll <= l && r <= rr) {
        return z[rt].sum;
    }
    int mid = l + r >> 1;
    pud(rt);
    int s = 0;
    if (ll <= mid) {
        s = (s + query(l, mid, rt << 1, ll, rr, v)) % mod;
    }
    if (mid < rr) {
        s = (s + query(mid + 1, r, rt << 1 | 1, ll, rr, v)) % mod;
    }
    return s % mod;
}
auto main() [[O3]] -> signed {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    build(1, n, 1);
    while (q--) {
        int o, l, r, x;
        cin >> o >> l >> r;
        if (o < 3) {
            cin >> x;
        }
        if (o == 1) {
            modify1(1, n, 1, l, r, x);
        } else if (o == 2) {
            modify2(1, n, 1, l, r, x);
        } else {
            cout << query(1, n, 1, l, r, x) << '\n';
        }
    }
}

```

---

## 作者：Starrykiller (赞：0)

平凡题。你 ABC 是没题出了吗（

考虑标记的下放。设标记 $(l,r)$ 为 $A$ 数组加上 $l$，$B$ 数组加上 $r$。

那么，下放标记的时候，对应：

$$\sum_{i} (A_i+l)(B_i+r)=\sum_{i} A_iB_i+r\sum_i A_i+l\sum_i B_i+\sum_i l\cdot r$$

注意到，改变后的答案只与原来的答案、$\sum A_i$、$\sum B_i$ 和 $l,r$（还有区间长度）有关。这启示我们记录这些信息。

于是，我们套路地设信息为 $(ans,\sum A_i,\sum B_i,len)$；标记的下放前面已经讨论过。

信息和标记的合并是平凡的。

时间复杂度 $\Theta(m\log n)$。

[My Submission](https://atcoder.jp/contests/abc357/submissions/54360662).

---

## 作者：Andy2035 (赞：0)

很板的一道题，考虑使用线段树。\
需要维护下列信息：
-  $ \displaystyle\sum_{i=l}^r\ A_i $
-  $ \displaystyle\sum_{i=l}^r\ B_i $
-  $ \displaystyle\sum_{i=l}^r\ (A_i\times\ B_i) $ 
  
可以考虑用一颗线段树维护，把 pushdown 写好就赢了,在更新 $ A $ 和 $ B $ 的同时更新 $ A_i\times\ B_i $ 。

代码如下：

```
#include<bits/stdc++.h>

#define ls(x) x << 1
#define rs(x) x << 1 | 1

using namespace std;

const int N = 200010;

typedef long long ll;

ll a[N],b[N];

const ll mod = 998244353;

struct info{
	int l,r;
	ll sa,sb,sab,ta,tb,tc;
}t[N * 4];

void pushup(int u){
	t[u].sa = (t[ls(u)].sa + t[rs(u)].sa) % mod;
	t[u].sb = (t[ls(u)].sb + t[rs(u)].sb) % mod;
	t[u].sab = (t[ls(u)].sab + t[rs(u)].sab) % mod;
}

void build(int u,int l,int r){
	t[u] = {l,r};
	if(l == r){
		t[u].sa = a[l],t[u].sb = b[l];
		t[u].sab = a[l] * b[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(u),l,mid),build(rs(u),mid + 1,r);
	pushup(u);
}

void maketag(int u,int x,int op){
	ll len = t[u].r - t[u].l + 1;
	if(op == 0){
		t[u].ta += x;
		t[u].sa += x * len;
		t[u].sab += t[u].sb * x;
		t[u].ta %= mod;
		t[u].sa %= mod;
		t[u].sab %= mod;
	}
	else if(op == 1){
		t[u].tb += x;
		t[u].sb += x * len;
		t[u].sab += t[u].sa * x;
		t[u].tb %= mod;
		t[u].sb %= mod;
		t[u].sab %= mod;
	}
}

void pushdown(int u){
	if(t[u].ta){
		maketag(ls(u),t[u].ta,0),maketag(rs(u),t[u].ta,0);
		t[u].ta = 0;
	}
	if(t[u].tb){
		maketag(ls(u),t[u].tb,1),maketag(rs(u),t[u].tb,1);
		t[u].tb = 0;
	}
}

void modify(int op,int u,int l,int r,ll x){
	if(t[u].l >= l && t[u].r <= r){
		maketag(u,x,op);
	}
	else if(t[u].l <= r && t[u].r >= l){
		pushdown(u);
		modify(op,ls(u),l,r,x);
		modify(op,rs(u),l,r,x);
		pushup(u);
	}
}

ll query(int u,int l,int r){
	if(t[u].l >= l && t[u].r <= r){
		return t[u].sab;
	}
	else if(t[u].r >= l && t[u].l <= r){
		pushdown(u);
		return query(ls(u),l,r) + query(rs(u),l,r);
	}
	return 0ll;
}

int main(){
	int n,q;cin>>n>>q;
	for(int i = 1;i<=n;i ++)cin>>a[i];
	for(int i = 1;i<=n;i ++)cin>>b[i];
	build(1,1,n);
	while(q --){
		int op,l,r;ll x;
		cin>>op>>l>>r;
		if(op < 3){
			cin>>x;
			modify(op - 1,1,l,r,x%mod);
		}
		else{
			cout<<query(1,l,r) % mod << endl;
		}
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：0)

板。

线段树可爱。

## 解题思路

考虑到 $a$ 或 $b$ 恒为 $1$ 的情况下是线段树板题，启发我们向线段树的方向思考。

先线段树维护 $a$ 和 $b$ 的区间和，记为 $sum_a,sum_b$ 然后考虑对于每个区间节点 $a\leftarrow a+c_1,b\leftarrow b+c_2$ 的情况怎么维护区间乘积和。

然后简略思考即可发现该次修改对区间乘积和的贡献为 $sum_a\times c_2+sum_b\times c_1+c_1\times c_2\times len$，接下来就很好维护了。

实现细节很多需要注意。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=250011,Moder_=998244353;
struct segtree
{
	long long l,r,suma,sumb,sum,lazya,lazyb;
};
segtree a[MAXN*4];
long long val[MAXN][2],n,m;
void pushup(long long x)
{
	a[x].suma=(a[x*2].suma+a[x*2+1].suma)%Moder_;
	a[x].sumb=(a[x*2].sumb+a[x*2+1].sumb)%Moder_;
	a[x].sum=(a[x*2].sum+a[x*2+1].sum)%Moder_;
	return;
}
void pushdown(long long x)
{
	if(a[x].lazya!=0||a[x].lazyb!=0)
	{
		a[x*2].lazya+=a[x].lazya;
		a[x*2].lazya%=Moder_;
		a[x*2].lazyb+=a[x].lazyb;
		a[x*2].lazyb%=Moder_;
		a[x*2].sum+=a[x].lazya*a[x*2].sumb;
		a[x*2].sum%=Moder_;
		a[x*2].suma+=a[x].lazya*(a[x*2].r-a[x*2].l+1);
		a[x*2].suma%=Moder_;
		a[x*2].sum+=a[x].lazyb*a[x*2].suma;
		a[x*2].sum%=Moder_;
		a[x*2].sumb+=a[x].lazyb*(a[x*2].r-a[x*2].l+1);
		a[x*2].sumb%=Moder_;
		//----------------------//
		a[x*2+1].lazya+=a[x].lazya;
		a[x*2+1].lazya%=Moder_;
		a[x*2+1].lazyb+=a[x].lazyb;
		a[x*2+1].lazyb%=Moder_;
		a[x*2+1].sum+=a[x].lazya*a[x*2+1].sumb;
		a[x*2+1].sum%=Moder_;
		a[x*2+1].suma+=a[x].lazya*(a[x*2+1].r-a[x*2+1].l+1);
		a[x*2+1].suma%=Moder_;
		a[x*2+1].sum+=a[x].lazyb*a[x*2+1].suma;
		a[x*2+1].sum%=Moder_;
		a[x*2+1].sumb+=a[x].lazyb*(a[x*2+1].r-a[x*2+1].l+1);
		a[x*2+1].sumb%=Moder_;
		//----------------------//
		a[x].lazya=a[x].lazyb=0;
	}
	return;
}
void build(long long x,long long l,long long r)
{
	a[x].l=l;
	a[x].r=r;
	if(l==r)
	{
		a[x].suma=val[l][0];
		a[x].sumb=val[l][1];
		a[x].sum=(val[l][0]*val[l][1])%Moder_;
		return;
	}
	long long mid=(a[x].l+a[x].r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	pushup(x);
	return;
}
void inca(long long x,long long l,long long r,long long c)
{
	if(a[x].l==l&&a[x].r==r)
	{
		a[x].sum=(a[x].sum+c*a[x].sumb)%Moder_;
		a[x].suma=(a[x].suma+(a[x].r-a[x].l+1)*c)%Moder_;
		a[x].lazya=(a[x].lazya+c)%Moder_;
		return;
	}
	pushdown(x);
	long long mid=(a[x].l+a[x].r)/2;
	if(l<=mid)
	{
		inca(x*2,l,min(mid,r),c);
	}
	if(r>=mid+1)
	{
		inca(x*2+1,max(l,mid+1),r,c);
	}
	pushup(x);
	return;
}
void incb(long long x,long long l,long long r,long long c)
{
	if(a[x].l==l&&a[x].r==r)
	{
		a[x].sum=(a[x].sum+c*a[x].suma)%Moder_;
		a[x].sumb=(a[x].sumb+(a[x].r-a[x].l+1)*c)%Moder_;
		a[x].lazyb=(a[x].lazyb+c)%Moder_;
		return;
	}
	pushdown(x);
	long long mid=(a[x].l+a[x].r)/2;
	if(l<=mid)
	{
		incb(x*2,l,min(mid,r),c);
	}
	if(r>=mid+1)
	{
		incb(x*2+1,max(l,mid+1),r,c);
	}
	pushup(x);
	return;
}
long long query(long long x,long long l,long long r)
{
	if(a[x].l==l&&a[x].r==r)
	{
		return a[x].sum;
	}
	pushdown(x);
	long long mid=(a[x].l+a[x].r)/2,ans=0;
	if(l<=mid)
	{
		ans+=query(x*2,l,min(r,mid));
	}
	if(r>=mid+1)
	{
		ans+=query(x*2+1,max(l,mid+1),r);
	}
	ans%=Moder_;
	return ans;
}
int main()
{
	long long i,j,ta,tb;
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&val[i][0]);
	}
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&val[i][1]);
	}
	build(1,1,n);
	long long opt,t;
	for(i=1;i<=m;i++)
	{
		scanf("%lld",&opt);
		if(opt==1)
		{
			scanf("%lld%lld%lld",&ta,&tb,&t);
			inca(1,ta,tb,t);
		}
		else if(opt==2)
		{
			scanf("%lld%lld%lld",&ta,&tb,&t);
			incb(1,ta,tb,t);
		}
		else
		{
			scanf("%lld%lld",&ta,&tb);
			printf("%lld\n",query(1,ta,tb));
		}
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

擦我赛时降智了。考场上瞪了四十分钟没调出来。

分块。对每个块维护 $a, b$ 上的加懒标记，表示 $a, b$ 的实际值分别是 $a + tag_a, b + tag_b$。由于 $(a + tag_a)(b + tag_b) = a \times b + a \times tag_b + b \times tag_a + tag_a \times tag_b$，还需要维护块内 $a \times b$ 的和，$a$ 的和，$b$ 的和（指不加懒标记的）。复杂度一个根号但是跑的飞快。[submission](https://atcoder.jp/contests/abc357/submissions/54380806)。

---

## 作者：No_Rest (赞：0)

# 思路

好像看过这道题，但是 pushdown 有一个变量忘传给右儿子，又把一个 $suma$ 写成 $sumb$，结果调我 $33$ 分钟，不光没时间写 E，还喜提赛后 $10$ 分钟过。菜。

一眼线段树（感觉这种裸板子比好多 D 都简单）。用 $suma,sumb$ 分别维护区间内 $a_i$ 和 $b_i$ 和，用 $sum$ 维护区间内 $a_i \times b_i$ 的和。

考虑如何更新。设我们将 $a_l \sim a_r$ 全部加 $v$，显然 $suma$ 的维护是板子。而 $sum$ 的变化量为 $\sum^r_{i=l}  [(a_i + v)\times b_i] - \sum^r_{i=l} (a_i \times b_i) = \sum^r_{i=l} v \times b_i = v \times \sum^r_{i=l} b_i = v \times sumb$，即 $sum \gets sum + v \times sumb$。将 $b_l \sim b_r$ 全部加 $r$ 时同理。然后就没了。

时间复杂度 $\mathcal O(n \log n)$。

易错点：

- 记得取模。

- 不要像我一样犯这样蠢的错误，还调半天。

# 代码

```cpp
#include<iostream>
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
typedef long long ll;
const ll maxn = 2e5 + 5;
const ll mod = 998244353;
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
struct st{
	ll l, r, sum, suma, sumb, taga, tagb;
}t[maxn << 2];
ll n = read(), q = read(), a[maxn], b[maxn];
void pushup(ll x){ t[x].sum = (t[ls].sum + t[rs].sum) % mod, t[x].suma = (t[ls].suma + t[rs].suma) % mod, t[x].sumb = (t[ls].sumb + t[rs].sumb) % mod; }
void build(ll x, ll l, ll r){
	t[x].l = l, t[x].r = r;
	if(l == r){
		t[x].sum = a[l] * b[l] % mod, t[x].suma = a[l] % mod, t[x].sumb = b[l] % mod;
		return;
	}
	ll mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	pushup(x);
}
void pushdown(ll x){
	if(t[x].taga){
		t[ls].suma = (t[ls].suma + t[x].taga * (t[ls].r - t[ls].l + 1) % mod) % mod, t[rs].suma = (t[rs].suma + t[x].taga * (t[rs].r - t[rs].l + 1) % mod) % mod;
		t[ls].sum = (t[ls].sum + t[x].taga * t[ls].sumb % mod) % mod, t[rs].sum = (t[rs].sum + t[x].taga * t[rs].sumb % mod) % mod;
		t[ls].taga = (t[ls].taga + t[x].taga) % mod, t[rs].taga = (t[rs].taga + t[x].taga) % mod;
		t[x].taga = 0;
	}
	if(t[x].tagb){
		t[ls].sumb = (t[ls].sumb + t[x].tagb * (t[ls].r - t[ls].l + 1) % mod) % mod, t[rs].sumb = (t[rs].sumb + t[x].tagb * (t[rs].r - t[rs].l + 1) % mod) % mod;
		t[ls].sum = (t[ls].sum + t[x].tagb * t[ls].suma % mod) % mod, t[rs].sum = (t[rs].sum + t[x].tagb * t[rs].suma % mod) % mod;
		t[ls].tagb = (t[ls].tagb + t[x].tagb) % mod, t[rs].tagb = (t[rs].tagb + t[x].tagb) % mod;
		t[x].tagb = 0;
	}
}
void update(ll x, ll l, ll r, ll v, ll op){
	if(l <= t[x].l && t[x].r <= r){
		if(op == 1){
			t[x].suma = (t[x].suma + v * (t[x].r - t[x].l + 1) % mod) % mod;
			t[x].sum = (t[x].sum + v * t[x].sumb % mod) % mod;
			t[x].taga = (t[x].taga + v) % mod;
		} else {
			t[x].sumb = (t[x].sumb + v * (t[x].r - t[x].l + 1) % mod) % mod;
			t[x].sum = (t[x].sum + v * t[x].suma % mod) % mod;
			t[x].tagb = (t[x].tagb + v) % mod;
		}
		return;
	}
	pushdown(x);
	ll mid = (t[x].l + t[x].r) >> 1;
	if(l <= mid) update(ls, l, r, v, op);
	if(r > mid) update(rs, l, r, v, op);
	pushup(x);
}
st query(ll x, ll l, ll r){
	if(l <= t[x].l && t[x].r <= r) return t[x];
	pushdown(x);
	ll mid = (t[x].l + t[x].r) >> 1;
	st ans, lans, rans;
	if(r <= mid) return query(ls, l, r);
	if(l > mid) return query(rs, l, r);
	lans = query(ls, l, r), rans = query(rs, l, r);
	ans.sum = (lans.sum + rans.sum) % mod, ans.suma = (lans.suma + rans.suma) % mod, ans.sumb = (lans.sumb + rans.sumb) % mod;
	return ans;
}
int main(){
	for(ll i = 1; i <= n; ++i) a[i] = read();
	for(ll i = 1; i <= n; ++i) b[i] = read();
	build(1, 1, n);
	for(ll op, x, y, v; q; --q){
		op = read(), x = read(), y = read();
		if(op != 3) v = read(), update(1, x, y, v, op);
		else printf("%lld\n", query(1, x, y).sum);
	}
    return 0;
}
```

---

## 作者：small_john (赞：0)

## 前言

F 题最简单的一集。赛时因为开小了加上没模干净吃了两发罚时。

## 思路

考虑序列 $a$ 的一个区间 $[l,r]$ 加上数 $x$ 会对答案产生怎样的影响：

$$\displaystyle\sum_{i=l}^r(a_i+x)b_i=\sum_{i=l}^{r}a_ib_i+xb_i=\sum_{i=l}^ra_ib_i+x\sum_{i=l}^r b_i$$

所以答案就是原来的答案加上 $x$ 乘区间内 $b$ 的和。对 $b$ 操作也是一样的。

所以用线段树维护区间内 $a$ 的和，$b$ 的和，答案以及对两个序列加的懒标记即可。时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 2e5+5,mod = 998244353;
int n,q,a[N],b[N];
struct node{
	int suma,sumb,ans,taga,tagb;
}t[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
inline void pushup(int k)
{
	t[k].suma = (t[ls].suma+t[rs].suma)%mod;
	t[k].sumb = (t[ls].sumb+t[rs].sumb)%mod;
	t[k].ans = (t[ls].ans+t[rs].ans)%mod;
}
inline void adda(int k,int v,int l,int r)
{
	(t[k].suma+=v*(r-l+1))%=mod;
	(t[k].ans+=v*t[k].sumb)%=mod;
	(t[k].taga+=v)%=mod;
}
inline void addb(int k,int v,int l,int r)
{
	(t[k].sumb+=v*(r-l+1))%=mod;
	(t[k].ans+=v*t[k].suma)%=mod;
	(t[k].tagb+=v)%=mod;
}
inline void down(int k,int l,int r,int mid)
{
	if(t[k].taga)
	{
		adda(ls,t[k].taga,l,mid),adda(rs,t[k].taga,mid+1,r);
		t[k].taga = 0;
	}
	if(t[k].tagb)
	{
		addb(ls,t[k].tagb,l,mid),addb(rs,t[k].tagb,mid+1,r);
		t[k].tagb = 0;
	}
}
void build(int k,int l,int r)
{
	if(l==r) return t[k].suma = a[l],t[k].sumb = b[l],t[k].ans = (a[l]*b[l])%mod,void();
	int mid = (l+r)/2;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void changea(int k,int l,int r,int x,int y,int v)
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return adda(k,v,l,r);
	int mid = (l+r)/2;
	down(k,l,r,mid);
	changea(ls,l,mid,x,y,v),changea(rs,mid+1,r,x,y,v);
	pushup(k);
}
void changeb(int k,int l,int r,int x,int y,int v)
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return addb(k,v,l,r);
	int mid = (l+r)/2;
	down(k,l,r,mid);
	changeb(ls,l,mid,x,y,v),changeb(rs,mid+1,r,x,y,v);
	pushup(k);
}
int ask(int k,int l,int r,int x,int y)
{
	if(l>y||r<x) return 0;
	if(l>=x&&r<=y) return t[k].ans;
	int mid = (l+r)/2;
	down(k,l,r,mid);
	return (ask(ls,l,mid,x,y)+ask(rs,mid+1,r,x,y))%mod;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(q);
	for(int i = 1;i<=n;i++)
		read(a[i]),a[i]%=mod;
	for(int i = 1;i<=n;i++)
		read(b[i]),b[i]%=mod;
	build(1,1,n);
	while(q--)
	{
		int op,l,r,v;
		read(op),read(l),read(r);
		if(op==1) read(v),changea(1,1,n,l,r,v);
		else if(op==2) read(v),changeb(1,1,n,l,r,v);
		else writen(ask(1,1,n,l,r));
	}
	return 0;
}
```

---

## 作者：lfxxx_ (赞：0)

## 前言
感谢[chat_jinxuan](https://www.luogu.com.cn/user/726525)对我的帮助！
## 思路
- 看到区间加和区间和，自然想到线段树。

- 我们定义 $A$ 为线段树这个节点所维护的区间的 $A$ 之和，$B$ 为这个节点所维护的区间的 $B$ 之和。

- 经过推理，我们发现，如果给这个节点的 $A$ 加上 $d$，则这个节点所维护的区间的答案由 $A \times B$ 变为了 $(A+d)\times B$，根据小学所学的乘法分配律可知，这个式子又可以变形为 $A\times B+d\times B$，就相当于在原来答案的基础上增加了一个 $d\times B$，若给 $B$ 加上 $d$，同理，答案加上 $d\times A$。
- 然后就是普通线段树的操作了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,mod=998244353;
struct node{
	int sum,sum1,sum2;
	int tag1,tag2;
}tr[N<<2];
int ls(int p){return p<<1;}
int rs(int p){return p<<1|1;}
void pushup(int p)
{
	tr[p].sum=(tr[ls(p)].sum+tr[rs(p)].sum)%mod;
	tr[p].sum1=(tr[ls(p)].sum1+tr[rs(p)].sum1)%mod;
	tr[p].sum2=(tr[ls(p)].sum2+tr[rs(p)].sum2)%mod;
}
void addtag(int p,int pl,int pr,int d,int ty)
{
	int len=pr-pl+1;d%=mod;
	if(ty==1)
	{
		tr[p].tag1=(tr[p].tag1+d)%mod;
		tr[p].sum1=(tr[p].sum1+(len*d)%mod)%mod;
		tr[p].sum=(tr[p].sum+(tr[p].sum2)%mod*d%mod)%mod;
	}
	else
	{
		tr[p].tag2=(tr[p].tag2+d)%mod;
		tr[p].sum2=(tr[p].sum2+(len*d)%mod)%mod;
		tr[p].sum=(tr[p].sum+(tr[p].sum1%mod)*d%mod)%mod;
	}
}
void pushdown(int p,int pl,int pr)
{
	int mid=pl+pr>>1;
	if(tr[p].tag1)
	{
		addtag(ls(p),pl,mid,tr[p].tag1,1);
		addtag(rs(p),mid+1,pr,tr[p].tag1,1);
		tr[p].tag1=0;
	}
	if(tr[p].tag2)
	{
		addtag(ls(p),pl,mid,tr[p].tag2,2);
		addtag(rs(p),mid+1,pr,tr[p].tag2,2);
		tr[p].tag2=0;
	}
}
void update(int p,int pl,int pr,int L,int R,int d,int t)
{
	if(L<=pl&&pr<=R)
	{
		addtag(p,pl,pr,d,t);
		return ;
	}
	if(R<pl||pr<L)
		return ;
	int mid=pl+pr>>1;
	pushdown(p,pl,pr);
	update(ls(p),pl,mid,L,R,d,t);
	update(rs(p),mid+1,pr,L,R,d,t);
	pushup(p);
}
int query(int p,int pl,int pr,int L,int R)
{
	if(L<=pl&&pr<=R)
		return tr[p].sum;
	if(R<pl||pr<L)
		return 0;
	int mid=pl+pr>>1;
	pushdown(p,pl,pr);
	return (query(ls(p),pl,mid,L,R)+query(rs(p),mid+1,pr,L,R))%mod;
}
signed main()
{
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;++i)
	{
		int x;
		cin>>x;
		update(1,1,n,i,i,x,1);
	}
	for(int i=1;i<=n;++i)
	{
		int x;
		cin>>x;
		update(1,1,n,i,i,x,2);
	}
	while(q--)
	{
		int op,l,r,d;
		cin>>op>>l>>r;
		if(op<=2)
		{
			cin>>d;
			update(1,1,n,l,r,d,op);
		}
		else
			cout<<query(1,1,n,l,r)<<'\n';
	}
} 

```

---

