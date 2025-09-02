# Circular RMQ

## 题目描述

You are given circular array $ a_{0},a_{1},...,a_{n-1} $ . There are two types of operations with it:

- $ inc(lf,rg,v) $ — this operation increases each element on the segment $ [lf,rg] $ (inclusively) by $ v $ ;
- $ rmq(lf,rg) $ — this operation returns minimal value on the segment $ [lf,rg] $ (inclusively).

Assume segments to be circular, so if $ n=5 $ and $ lf=3,rg=1 $ , it means the index sequence: $ 3,4,0,1 $ .

Write program to process given sequence of operations.

## 样例 #1

### 输入

```
4
1 2 3 4
4
3 0
3 0 -1
0 1
2 1
```

### 输出

```
1
0
0
```

# 题解

## 作者：Siyuan (赞：11)

> ## 这题评分是 **省选/NOI-**？明明是 **普及+/提高** 的裸题！

## 本题思路：
1. 很明显，这是一道 **线段树** 裸题。因此线段树的实现就不讲了吧。。。
2. 细节方面的问题：因为是一个 **环形数列**，每次读入后需要判断$\ l$和$\ r$的大小！
- 如果$\ l<=r$（满足一般关系）：则直接$\ update(l,r)$即可。
- 如果$\ l>r$（为一个环形关系）：则需要$\ update(l,n)\ +\ update(1,r)$。
3. 代码中有一些 **细节实现**，可以略作参考（如变量$\ space$处理参数数量等）。

### 代码奉上：
PS：关于线段树的具体实现和写法，详见 [洛谷 - P3372 【模板】线段树 1](https://www.luogu.org/problemnew/show/P3372)

```
#include<cstdio>
#define C const
#define ls rt<<1
#define rs rt<<1|1
#define ll long long
#define INF 0x7f7f7f7f7f7f7f7f
using namespace std;

const int MAXN=200000+5;
int n,m;
bool space;
ll a[MAXN],tree[MAXN<<2],tag[MAXN<<2];

inline ll read_long()
{
	space=0;
	register ll s=0,w=1;
	register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9')s=(s<<1)+(s<<3)+c-48,c=getchar();
	if(c==' ')  space=1;
	return s*w;
}
inline int read_int()
{
	space=0;
	register int s=0,w=1;
	register char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9')s=(s<<1)+(s<<3)+c-48,c=getchar();
	if(c==' ')  space=1;
	return s*w;
}
inline ll min(C ll &a,C ll &b){return(a<b?a:b);}

inline void build(C int &rt,C int &l,C int &r)
{
	if(l==r){tree[rt]=a[l];return;}
	C int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	tree[rt]=min(tree[ls],tree[rs]);
}
inline void update(C int &nl,C int &nr,C int &rt,C int &l,C int &r,C ll &v)
{
	if(nl<=l&&r<=nr)
	{
		tag[rt]+=v;
		return;
	}
	C int mid=(l+r)>>1;
	if(nl<=mid)  update(nl,nr,ls,l,mid,v);
	if(mid<nr)  update(nl,nr,rs,mid+1,r,v);
	tree[rt]=min(tree[ls]+tag[ls],tree[rs]+tag[rs]);
}

inline ll query(C int &nl,C int &nr,C int &rt,C int &l,C int &r)
{
	if(nl<=l&&r<=nr)  return tree[rt]+tag[rt];
	C int mid=(l+r)>>1;
	register ll left=INF,right=INF;
	if(nl<=mid)  left=query(nl,nr,ls,l,mid);
	if(mid<nr)  right=query(nl,nr,rs,mid+1,r);
	return min(left,right)+tag[rt];
}

int main()
{
	n=read_int();
	for(register int i=1;i<=n;i++)  a[i]=read_long();
	build(1,1,n);
	m=read_int();
	register int l,r;
	register ll v;
	while(m--)
	{
		l=read_int();  r=read_int();
		l++;  r++;
		if(space)
		{
			v=read_long();
			if(l>r)  update(l,n,1,1,n,v),update(1,r,1,1,n,v);
			else  update(l,r,1,1,n,v);
		}else{
			if(l>r)  printf("%lld\n",min(query(l,n,1,1,n),query(1,r,1,1,n)));
			else  printf("%lld\n",query(l,r,1,1,n));
		}
	}
	return 0;
}
```

---

## 作者：Fido_Puppy (赞：4)

## Segment Tree

这就是一道线段树的题（废话， 题目不是在那里摆着吗？）。 相信有很多小盆友还不会线段树（会了还用我写题解吗？）。 那么我们先来了解一下线段树。

线段树， 顾名思义， 就是一棵保存线段的树。 那么保存的内容有很多种形式， 比如最小值， 最大值， 区间和等等。

### 一、	建树

假设一个节点的下标为 $\texttt{x}$， 那么它的左儿子的下标就是 $\texttt{2x}$， 它的右儿子的下标就是 $\texttt{2x+1}$。 那么我们从下标 $\texttt{1}$ 开始， 一直递归， 建树就完成了。

#### NOTICE:

记得最后要更新父节点。
    
### 代码君：
```cpp
void build(ll p,ll l,ll r) {
	t[p].l=l; t[p].r=r; t[p].add=0;
	if (l==r) {
		t[p].data=a[l];
		t[p].Min=a[l];
		return ;
	}
	ll mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].data=t[p*2].data+t[p*2+1].data;
	t[p].Min=min(t[p*2].Min,t[p*2+1].Min);
}
```

### 二、	区间修改

  假如你更新了线段 $\texttt{1}$ ~ $\texttt{4}$， 那么线段 $\texttt{1}$ ~ $\texttt{2}$ 也得更新， 假如一个节点的值要加 $\texttt{k}$，那么它的儿子节点都要加 $\texttt{k}$，可是一个一个更新太慢了， 能不能一起更新呢？ $\texttt{Of course, why not?}$ 这里就需要加入一个 $\texttt{pushdown}$ 的概念了。

首先， 我们可以加一个 $\texttt{add}$， 那么我们只需要在用之前 $\texttt{pushdown}$ 一下就行辣。

### 代码君：

```cpp
void pushdown(ll p) {
	t[p*2].data+=(t[p*2].r-t[p*2].l+1)*t[p].add;
	t[p*2].Min+=t[p].add;
	t[p*2].add+=t[p].add;
	t[p*2+1].data+=(t[p*2+1].r-t[p*2+1].l+1)*t[p].add;
	t[p*2+1].Min+=t[p].add;
	t[p*2+1].add+=t[p].add;
	t[p].add=0;
}
```

假如它就在所要求的区间之内， 就可以直接更新， 每个数都加上 $\texttt{k}$， 相当于一共加上 $\texttt{(r-l+1)}$ $\times$ $\texttt{k}$。 $\texttt{add}$ 也要加上 $\texttt{k}$。每一个数都加上 $\texttt{k}$， 区间内的大小关系不变， 最小值也要加上 $\texttt{k}$。 其实思路与上面的 $\texttt{pushdown}$ 是差不多的。

区间修改的代码也很快就能写出来辣。

#### NOTICE:
最后记得更新一下。

### 代码君：
```cpp
void change(ll p,ll x,ll y,ll k) {
	if (t[p].l>=x&&t[p].r<=y) {
		t[p].data+=(t[p].r-t[p].l+1)*k;
		t[p].Min+=k;
		t[p].add+=k;
		return ;
	}
	pushdown(p);
	ll mid=(t[p].l+t[p].r)/2;
	if (x<=mid) change(p*2,x,y,k);
	if (mid<y) change(p*2+1,x,y,k);
	t[p].data=t[p*2].data+t[p*2+1].data;
	t[p].Min=min(t[p*2].Min,t[p*2+1].Min);
}
```

### 三、	区间查询

只要它就在所要求的区间内， 直接返回值， 别忘了在求最小值之前 $\texttt{pushdown}$ 一下。 $\texttt{ans}$ 刚开始要初始化。

### 代码君：
```cpp
ll query(ll p,ll x,ll y) {
	if (t[p].l>=x&&t[p].r<=y) return t[p].Min;
	pushdown(p);
	ll ans=1e16,mid=(t[p].l+t[p].r)/2;
	if (x<=mid) ans=min(ans,query(p*2,x,y));
	if (mid<y) ans=min(ans,query(p*2+1,x,y));
	return ans;
}
```

就这样，我们完成了线段树的一波操作。

#### 环形的解决方法：

如果 $\texttt{l}$ <= $\texttt{r}$ ， （$\texttt{l}$ ， $\texttt{r}$）。

如果 $\texttt{l}$ >= $\texttt{r}$ ， （$\texttt{l}$ ， $\texttt{n}$） ； （$\texttt{1}$ ， $\texttt{r}$）。

#### 输入的解决方法：

用一个快读判断输入空格的个数（无奈啊！）。

### 代码君：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define Maxn 1000001
typedef long long ll;
struct node {
	ll data,l,r,Min,add;
}t[4*Maxn]; //记得要开4倍的空间
ll a[Maxn],n,m,len,b[10],space=0;
ll read() {
	ll res=0,f=1;
	char c=getchar();
	while (!isdigit(c)) {if (c=='-') f=-1;c=getchar();}
	while (isdigit(c)) res=res*10+c-48,c=getchar();
	if (c==' ') ++space; //空格的个数
	return res*f;
}
void build(ll p,ll l,ll r) {
	t[p].l=l; t[p].r=r; t[p].add=0;
	if (l==r) {
		t[p].data=a[l];
		t[p].Min=a[l];
		return ;
	}
	ll mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p].data=t[p*2].data+t[p*2+1].data;
	t[p].Min=min(t[p*2].Min,t[p*2+1].Min);
}
void pushdown(ll p) {
	t[p*2].data+=(t[p*2].r-t[p*2].l+1)*t[p].add;
	t[p*2].Min+=t[p].add;
	t[p*2].add+=t[p].add;
	t[p*2+1].data+=(t[p*2+1].r-t[p*2+1].l+1)*t[p].add;
	t[p*2+1].Min+=t[p].add;
	t[p*2+1].add+=t[p].add;
	t[p].add=0;
}
void change(ll p,ll x,ll y,ll k) {
	if (t[p].l>=x&&t[p].r<=y) {
		t[p].data+=(t[p].r-t[p].l+1)*k;
		t[p].Min+=k;
		t[p].add+=k;
		return ;
	}
	pushdown(p);
	ll mid=(t[p].l+t[p].r)/2;
	if (x<=mid) change(p*2,x,y,k);
	if (mid<y) change(p*2+1,x,y,k);
	t[p].data=t[p*2].data+t[p*2+1].data;
	t[p].Min=min(t[p*2].Min,t[p*2+1].Min);
}
ll query(ll p,ll x,ll y) {
	if (t[p].l>=x&&t[p].r<=y) return t[p].Min;
	pushdown(p);
	ll ans=1e16,mid=(t[p].l+t[p].r)/2;
	if (x<=mid) ans=min(ans,query(p*2,x,y));
	if (mid<y) ans=min(ans,query(p*2+1,x,y));
	return ans;
}
int main() {
	cin>>n;
	for(ll i=1;i<=n;i++) cin>>a[i];
	build(1,1,n);
	cin>>m;
	for(ll i=1;i<=m;i++) {
		ll l,r,k;
		space=0; //记得每次要清空
		l=read();r=read();++l;++r; //由于它的下标是0到n-1， 所以要先把下标+1
		if (space==2) {
			k=read();
			if (l<=r) change(1,l,r,k);else {change(1,l,n,k);change(1,1,r,k);}
		}
		else {
			if (l<=r) cout<<query(1,l,r)<<endl;else cout<<min(query(1,l,n),query(1,1,r))<<endl;
		}
	}
	return 0;
}
```

完结撒花！！


---

## 作者：云浅知处 (赞：4)

线段树裸题一个。写一个支持区间加，区间取 $\min$ 的线段树即可。

这里说一下处理环形的方法。其实也不是那么难想啦qwq。

- 如果 $l\le r$，那么就是正常区间，直接处理即可。
- 如果 $l>r$，则区间成环形，处理一下 $[l,n]$ 和 $[1,r]$ 即可。并不需要什么高科技。

顺便提一句，判断是 $\operatorname{rmq}$ 还是 $\operatorname{inc}$ 的时候，其实只需要加快读，在 `read()` 里面加上一个 `space` 的判断即可。

当然，用类似 `while(cin>>x);` 之类的写法也是没问题的。

PS：如果不会线段树，可以左转 [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)，题解区大佬讲的十分清楚，包教包会（

------------

下面，上代码：

```cpp
#include<bits/stdc++.h>

#define int long long
#define lson(o) (o<<1)
#define rson(o) (o<<1|1)
#define MAXN 200005

using namespace std;

int a[MAXN],n;

struct SMT{//线段树 
	
	int m[MAXN<<2],plz[MAXN<<2];
	//m表示区间最小值，plz是懒标记 
	
	inline void pushup(int o){
		m[o]=min(m[lson(o)],m[rson(o)]);
	}
	
	inline void build(int l,int r,int o){
		plz[o]=0;
		if(l==r){
			m[o]=a[l];
			return ;
		}
		int mid=(l+r)>>1;
		build(l,mid,lson(o));
		build(mid+1,r,rson(o));
		pushup(o);
	}
	//建树 
	
	inline void pushdown(int ql,int qr,int o){
		int mid=(ql+qr)>>1;
		if(plz[o]){
			m[lson(o)]+=plz[o];
			m[rson(o)]+=plz[o];
			plz[lson(o)]+=plz[o];
			plz[rson(o)]+=plz[o];
			plz[o]=0;
		}
	}
	
	inline int querymin(int l,int r,int ql,int qr,int o){
		if(l<=ql&&qr<=r)return m[o];
		pushdown(ql,qr,o);
		int mid=(ql+qr)>>1,ans=0x7fffffff;
		if(l<=mid)ans=min(ans,querymin(l,r,ql,mid,lson(o)));
		if(r>mid)ans=min(ans,querymin(l,r,mid+1,qr,rson(o)));
		return ans;
	}
	//区间查询最小值 
	
	inline void add(int l,int r,int k,int ql,int qr,int o){
		if(l<=ql&&qr<=r){
			m[o]+=k;
			plz[o]+=k;
			return ;
		}
		pushdown(ql,qr,o);
		int mid=(ql+qr)>>1;
		if(l<=mid)add(l,r,k,ql,mid,lson(o));
		if(r>mid)add(l,r,k,mid+1,qr,rson(o));
		pushup(o);
	}
	//区间加
	 
};
//都是线段树的基本操作，就不多说了。 

SMT tree;

int spc=0;//用于判断是否还有下一个数 
inline int read(){
	spc=0;//每次快读时记得初始化，我因为这个调了十几分钟=_= 
	int w=0,f=1;
	char c=getchar();
	while(!isdigit(c))if(c=='-')f=-1,c=getchar();
	while(isdigit(c))w=(w<<1)+(w<<3)+(c^48),c=getchar();
	if(c==' ')spc=1;
	//原理其实大概是读入完一个数之后
	//由于 while 的特性会多读入一个字符
	//如果这个是空格则说明后面还有数。 
	return w*f;
}

signed main(void){

	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	tree.build(1,n,1);
	
	int m=read();
	while(m--){
		int l=0,r=0,v=0;
		l=read(),r=read();
		l++,r++;
		if(spc){//spc 就是快读里面的那个 
			v=read();
			if(l>r)tree.add(l,n,v,1,n,1),tree.add(1,r,v,1,n,1);
			//成环形 
			else tree.add(l,r,v,1,n,1);
			//普通的线形 
		}
		else{
			if(l>r)printf("%lld\n",min(tree.querymin(l,n,1,n,1),tree.querymin(1,r,1,n,1)));
			else printf("%lld\n",tree.querymin(l,r,1,n,1));
			//同上 
		}
	}

	return 0;
}

```


---

## 作者：cyy233 (赞：2)

# 又来水一发题解

题目：给你一个**环形**，让你做区间修改，区间查询一段

区间的**最小值**

千万不要被**环形**二字吓坏了，其实很好处理

在 ${7,2,3,5,5,8,7,2}$ 中，求从$3$号到$6$号的最小值

直接线段树求解。。。

如果从$6$号绕一圈到$3$号呢

其中经历了$6$号，$7$号，$8$号，$1$号,$2$号，$3$号，
最小值为$2$

我们可以看作答案是从区间$[6,8]$和区间$[1,3]$合并而来

所以我们可以分别处理两端情况

换言之，若给出左端点$l>$右端点$r$，答案从$[l,n]$和$[1,r]$

线段树维护区间最小值。。。。。。


还有，

**1**.输入没告诉你操作，但是我们可以在每次输入完后看

看该数后有几个空格，有两个即为修改（查询是$1$个空格+$1$个

换行）
 
**2**.由于从$0$~$n-1$,所以输入时$l$和$r$各加1

**以上**

```
#include<bits/stdc++.h>
#define LL long long
#define inf LONG_LONG_MAX
#define re register
#define he(x) for(register int i=head[x];i;i=e[i].nxt)
using namespace std;
LL n,m,opt;
struct CCF{
	LL l,r,mi,add;
}t[800010];
template <class frd> inline void read(frd &a)
{
    bool f=0;a=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')a=(a<<1)+(a<<3)+(ch^48),ch=getchar();
    if(ch==' ')opt++;//有几个空格
    if(f)a=-a;
}
template<typename T>inline void readc(T &x){
    while(x=getchar(),!islower(x)&&!isupper(x));
}
inline string read1()
{
	char ch=getchar();
	string st1="";
	while(!((ch>='a')&&(ch<='z')||(ch>='A')&&(ch<='Z')))
	  ch=getchar();
	while((ch>='a')&&(ch<='z')||(ch>='A')&&(ch<='Z'))
	  st1+=ch,ch=getchar();
	return st1;
}
template<typename T>inline void print(T x,char c='\n'){
    static int buf[40];
    if(x==0){
        putchar('0');
        putchar(c);
        return;
    }
    if(x<0)putchar('-'),x=-x;
    for(buf[0]=0;x;x/=10)buf[++buf[0]]=x%10+48;
    while(buf[0])putchar((char)buf[buf[0]--]);
    putchar(c);
}
inline void pushdown(LL x){
	t[x<<1].add+=t[x].add;
	t[x<<1|1].add+=t[x].add;
	t[x<<1].mi+=t[x].add;
	t[x<<1|1].mi+=t[x].add;
	t[x].add=0;
}//懒人标记
inline void build(LL x,LL l,LL r){
	t[x].l=l;t[x].r=r;
	if(l==r){
		read(t[x].mi);
		return;
	}
	LL mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	t[x].mi=min(t[x<<1].mi,t[x<<1|1].mi);
}
inline void update(LL x,LL l,LL r,LL k){
	if(t[x].l>=l&&t[x].r<=r){
		t[x].add+=k;
		t[x].mi+=k;
		return;
	}
	if(t[x].add)pushdown(x);
	LL mid=(t[x].l+t[x].r)>>1;
	if(mid>=l)update(x<<1,l,r,k);
	if(mid<r)update(x<<1|1,l,r,k);
	t[x].mi=min(t[x<<1].mi,t[x<<1|1].mi);
}
inline LL query(LL x,LL l,LL r){
	if(t[x].l>=l&&t[x].r<=r)return t[x].mi;
	if(t[x].add)pushdown(x);
	LL mi=INT_MAX,mid=(t[x].l+t[x].r)>>1;
	if(mid>=l)mi=min(mi,query(x<<1,l,r));
	if(mid<r)mi=min(mi,query(x<<1|1,l,r));
	return mi;
}
int main()
{
	read(n);
	build(1,1,n);
	read(m);
	while(m--){
		opt=0;
		LL l,r,k;
		read(l),read(r);l++;r++;//由于从0~n-1,l和r++
		if(opt==2){
			read(k);
			if(l<=r)update(1,l,r,k);
			else {
				update(1,l,n,k);
				update(1,1,r,k);
  				//更新l>r的情况
			}
		}
		else{
			if(l<=r)print(query(1,l,r));
			else {
				print(min(query(1,l,n),query(1,1,r)));
                                       //查询l>r的情况
			}
		}
	}
    return 0;
}

```


---

## 作者：NotaKoala (赞：2)

我jio楼上dalao说的没错，这就是一道
#### 线段树裸题

线段树的操作大家可以看看模板一的

~~我太懒了~~

### so我不想多解释了放一下代码供参考

#### 注意：我的操作 都是 [l ,  r) 的

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

const int MAX_N = 2e5 + 233;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll n, m;
ll a[MAX_N];

struct rmq {
    // dat1 是懒标
	ll dat0[MAX_N * 4], dat1[MAX_N * 4];
    
    // 建树
	void build(int k, int l, int r) {
		if (r - l == 1) {
			dat0[k] = a[l];
			return ;
		}
		build(k * 2 + 1, l, (l + r) / 2);
		build(k * 2 + 2, (l + r) / 2, r);
		dat0[k] = min(dat0[k * 2 + 1], dat0[k * 2 + 2]);
	}
	// 查询 [a, b) 之间的最小值
	ll query(int a, int b, int k, int l, int r) {
		if (b <= l || r <= a) { // [l, r) 与 [a, b) 没有相交的部分
			return INF;
		} else if (a <= l && r <= b) {
		// [a, b) 完全包含 [l, r)
			return dat0[k] + dat1[k];
		} else {
		// [a, b) 和 [l, r) 有交集就分治查询左右儿子
			int ma = query(a, b, k * 2 + 1, l, (l + r) / 2);
			int mb = query(a, b, k * 2 + 2, (l + r) / 2, r);
			return min(ma, mb) + dat1[k];
		}
	}
	// 对 [a, b) 加 x
	void add(int a, int b, int k, ll x, int l, int r) {
		if (a <= l && r <= b) { // [a, b) 完全包含 [l, r)
			dat1[k] += x;
			return ;
		} else if (b <= l || r <= a) {
			return ;
		} else {
			add(a, b, k * 2 + 1, x, l, (l + r) / 2);
			add(a, b, k * 2 + 2, x, (l + r) / 2, r);
		}
		dat0[k] = min(dat0[k * 2 + 1] + dat1[k * 2 + 1], dat0[k * 2 + 2] + dat1[k * 2 + 2]);
	}	
} tree;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	tree.build(0, 0, n);
	cin >> m;
	ll l, r, x, ans;
	char ch;
	for (int i = 0; i < m; i++) {
		cin >> l >> r;
		ch = getchar();
		if (ch == '\n') {
			if (l <= r) {
				ans = tree.query(l, r + 1, 0, 0, n);
			} else {
				ans = min(tree.query(0, r + 1, 0, 0, n), tree.query(l, n, 0, 0, n));
			}
			cout << ans << endl;
		} else {
			cin >> x;
			if (l <= r) {
				tree.add(l, r + 1, 0, x, 0, n);
			} else {
				tree.add(l, n, 0, x, 0, n);
				tree.add(0, r + 1, 0, x, 0, n);
			}
		}
	} 
	return 0;
} 
```

刚开始提交总是wa了第23个点，就是忘加了个 long long

这种细节还是要注意一下

---

## 作者：xiaohuang (赞：1)

[更好的阅读体验](https://xiaohuang888.github.io/2019/12/11/%E3%80%8CCF52C%E3%80%8DCircular%20RMQ/)

### Solution

我们可以用线段树来解决区间`RMQ`问题，我们在线段树上维护一个最小值与懒标记，这样问题就解决了。

读入的时候我们可以判断后面一个字符是不是空格，可以直接在快速读入里判断，这样就可以判断出一行有三个数还是两个数。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

using namespace std;

const int MAXN = 200005;
int n, m, l, r, val, a[MAXN];
bool opt;
namespace Segtree {
    #define ls rt << 1
    #define rs rt << 1 | 1
    typedef long long LL;
    const LL Seg_INF = 1e18;
    const int Seg_MAXN = 1000005;
    struct SMT {
        LL Min, tag;
    } tree[Seg_MAXN];
    inline void build(int rt, int l, int r) {//建立线段树
        if (l == r) {
            tree[rt].Min = a[l];
            return ;
        }
        int mid = l + r >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        tree[rt].Min = min(tree[ls].Min, tree[rs].Min);
    }
    inline void update(int rt, int l, int r, int ansl, int ansr, int val) {//线段树修改
        if (ansl <= l && r <= ansr) {
            tree[rt].tag += val;
            return ;
        }
        int mid = l + r >> 1;
        if (ansl <= mid) update(ls, l, mid, ansl, ansr, val);
        if (mid < ansr) update(rs, mid + 1, r, ansl, ansr, val);
        tree[rt].Min = min(tree[ls].Min + tree[ls].tag, tree[rs].Min + tree[rs].tag);
    }
    inline LL query(int rt, int l, int r, int ansl, int ansr) {//线段树查询
        if (ansl <= l && r <= ansr) return tree[rt].Min + tree[rt].tag;
        int mid = l + r >> 1;
        LL ret = Seg_INF;
        if (ansl <= mid) ret = min(ret, query(ls, l, mid, ansl, ansr));
        if (mid < ansr) ret = min(ret, query(rs, mid + 1, r, ansl, ansr));
        return ret + tree[rt].tag;
    }
}

using namespace Segtree;

inline int read() {
    opt = 0;
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if (ch == ' ') opt = 1;//判断空格
    return x * f;
}
int main() {
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    build(1, 1, n);
    m = read();
    for (int i = 1; i <= m; i++) {
        l = read(); r = read(); l++; r++;
        if (!opt) {
            if (l <= r) printf("%lld\n", query(1, 1, n, l, r)); else printf("%lld\n", min(query(1, 1, n, l, n), query(1, 1, n, 1, r)));
        } else {
            val = read();
            if (l <= r) update(1, 1, n, l, r, val); else {
                update(1, 1, n, l, n, val);
                update(1, 1, n, 1, r, val);
            }
        }
    }
    return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

这道题目是个线段树模板题。

首先，我们对于区间修改操作，分成两种情况：

$i\le j$ 和 $j< i$ 。

第一种 $i\le j$ 的情况可以直接区间修改，使用标记永久化/懒标记下传解决问题；

第二种情况就要把要修改的区间断成两段，一段是 $[i,n]$ ，一段是 $[1,j]$ ，在上面继续区间修改。


区间查询也是如法炮制，如果 $j<i$，答案就是$\max(rmq(1,j),rmq(i,n))$ 。（`rmq`是求区间最值函数）

不然直接返回 $rmq(l,r)$ 。

然后注意题目给出的区间端点 $l,r$ 是要额外加上 $1$ 的。

注意一些线段树实现的细节。

---

## 作者：Suuon_Kanderu (赞：0)

我们可以看出，这是一个区间操作问题。

可以用线段树，但我喜欢用**分块**—优雅的暴力

**分块是一种很容易理解数据结构，他可以维护很多的东西**~~当然我都不会~~，本题解旨在让只能得暴力分的同学AC本题！学会分块的思想以及方法，会比较详细。

- 分块的思想

	所谓分块，顾名思义，就是把一组数据分为若干块，从而提高效率。
    
    举个例子：来看一组数据1,5,6,4,5。
    我们把他分成$\sqrt{n}$个块（不同的情况块的数量不同，就是这样)
 
| 编号 | 数值 | 块的编号 |
| ----------- | ----------- | ----------- |
| 1 | 1 | 1 |
| 2 | 5 | 1 |
| 3 | 6 | 2 |
| 4 | 4 | 2 |
| 5 | 5 | 3 |

如果我们要让编号一到五加1，可以这样做：
	
    1. 把第一块（1）的值 暴力 加1
    
    2. 把中间块（2）的每个块的标记+1
    （如何打标记？只要再开一个数组，记录每一块的统一加的值即可，相信学过线段树的同学一定很熟悉）
    
    3. 把最后一块（3）的数值 暴力 加1

然后就是这样




|编号 | 数值 | 块的编号 |
| ----------- | ----------- | ----------- | ----------- |
| 1 | 2（1+1） |1  | 
| 2 | 6 （5+1）| 1 | 
| 3 | 6 | 2 |  |
| 4 | 4 | 2 |  |
| 5 | 6 （5+1）|3  |

|第几块  | 标记 |
| ----------- | ----------- |
| 1 | 0 |
| 2 | 1（0+1） |
| 3 | 0 |


区间查询同理，只是暴力加 val 的时候要把每个块的标记也加 val。

单点查询就是把标记 和 数值加起来就OK。

- 具体实现
	
    实现时我们要考虑一些细节。
    假设我们要维护 x1 到 x2 的序列
    1. 先维护两边的不完整块。我们要从起始点 x1 到 x1 所在块的末尾，手算可得，每个块的第一个元素为$L \times [rank(x1)-1]$，其中 L 为块的大小，rank(x1) 为当前块的编号。这样我们就暴力的维护了不完整块。
    2. 再维护中间整块，注意块的编号为$~~randk(x1)+1~~~to~~~rank(x2-1) $。 因为两边的散块都被处理过了
    3. 要注意操作的序列在一个块内的时候，我们可以只维护左边的块，特判一下，就完了。
    4. 对于此题。如果 $x1 > x2$，我们可以处理 x1 到 N，再处理 1 到x2。
    5. 由于此题的毒瘤输入，我没想出怎么搞。很抱歉。
    
 [参考代码](https://www.luogu.com.cn/paste/ugvnm4uw)
 
 


---

## 作者：PrincessYR✨～ (赞：0)

一道线段树的类似模板题。

首先来讲一下线段树。

1. 建树：

先来看一下线段树长啥样

![](https://bkimg.cdn.bcebos.com/pic/0e2442a7d933c895d47476f7db1373f082020037?x-bce-process=image/crop,x_120,y_37,w_1504,h_992/watermark,g_7,image_d2F0ZXIvYmFpa2UxODA=,xp_5,yp_5)

（注：图片来自百度百科）

最下面一层是我们要读入的数组a[i]。

我们从顶端开始建树，根据二叉树的性质我们可以知道一棵树的左儿子的序号为父亲的序号乘二，右儿子为乘二加一。

我们一直往下递推，知道左端点等于右端点，及一个区间只包含一个数。及搜到最后一层，我们便将a数组的只赋给线段树，当回到父节点是在根据需要判断。

例如这道题要求最小值，我们使父亲节点取字节点的最小值（如果求和，则将子节点的值加起来）。

建树代码：

```
void build(int k,int l,int r)//k为结点编号，l为区间的左端，r为右端
{
	lazy[k]=0;
	if(l==r)
	{
		sum[k]=a[l];
		return ;
	}
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	sum[k]=min(sum[k*2],sum[k*2+1]);
}
```

2. 加减标记：

一般来说加减就一直搜，将所有点都改一遍。然而这样时间复杂度十分高，十分容易超时。

那么我们就引入了懒惰标记，lazy。

lazy就是将我们要更改的只存储起来，不向下传，等到什么时候要求这个区间的值时，再将值更改。

代码：

```
void pushdown(int k)
{
	lazy[k*2]+=lazy[k];//将lazy传给左儿子
	lazy[k*2+1]+=lazy[k];//将lazy传给右儿子
	sum[k*2]+=lazy[k];//左儿子加上lazy
	sum[k*2+1]+=lazy[k];//右儿子加上lazy
	lazy[k]=0;//将父亲节点的lazy清零
}


void gx(int L,int R,int e,int l,int r,int k)
{
	if(L<=l&&R>=r)//如果当前查询的区间完全包含在内
	{
		lazy[k]+=e;//lazy记录
		sum[k]+=e;//当前节点加e
		return ; 
	}
	pushdown(k);//将lazy传给子节点
	int mid=(l+r)/2;
	if(L<=mid)//如果左节点有要查询的值
	{
		gx(L,R,e,l,mid,k*2);//查询左边
	}
	if(mid<R)//如果右节点有要查询的值
	{
		gx(L,R,e,mid+1,r,k*2+1);//查询右边的值
	}
	sum[k]=min(sum[k*2],sum[k*2+1]);
}
```
2. 最小值查询：
```
long long qh(long k,int l,int r,int L,int R)//注意，本代码中sum求的是最小值
{
	if(L<=l&&R>=r)//如果包含在内，直接返回最小值
	{
		return sum[k];
	}
	else 
	{
		pushdown(k);//更新子节点，将lazy下传
		long long re=2147483647485;
		int mid=(l+r)/2;
		if(L<=mid)//如果在左半只
		re=min(re,qh(k*2,l,mid,L,R));
		if(R>mid)//如果在右半只
		re=min(re,qh(k*2+1,mid+1,r,L,R));
		return re;
	}
}
```

有关线段树其他操作，[看这篇文章](https://www.luogu.com.cn/blog/Hakurei-Reimu/seg-beats)

温馨提示：

 _**long long**_ 
 
 最后贴上代码：
 
 ```
#include<bits/stdc++.h>
using namespace std;
long long a[200005],sum[200005<<2],lazy[200005<<2];
long long q,w,e;
int n,m;
void build(int k,int l,int r)
{
	lazy[k]=0;
	if(l==r)
	{
		sum[k]=a[l];
		return ;
	}
	int mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	sum[k]=min(sum[k*2],sum[k*2+1]);
}
void pushdown(int k)
{
	lazy[k*2]+=lazy[k];
	lazy[k*2+1]+=lazy[k];
	sum[k*2]+=lazy[k];
	sum[k*2+1]+=lazy[k];
	lazy[k]=0;
}
long long qh(long k,int l,int r,int L,int R)
{
	if(L<=l&&R>=r)
	{
		return sum[k];
	}
	else 
	{
		pushdown(k);
		long long re=2147483647485;
		int mid=(l+r)/2;
		if(L<=mid)
		re=min(re,qh(k*2,l,mid,L,R));
		if(R>mid)
		re=min(re,qh(k*2+1,mid+1,r,L,R));
		return re;
	}
}
void gx(int L,int R,int e,int l,int r,int k)
{
	if(L<=l&&R>=r)
	{
		lazy[k]+=e;
		sum[k]+=e;
		return ; 
	}
	pushdown(k);
	int mid=(l+r)/2;
	if(L<=mid)
	{
		gx(L,R,e,l,mid,k*2);
	}
	if(mid<R)
	{
		gx(L,R,e,mid+1,r,k*2+1);
	}
	sum[k]=min(sum[k*2],sum[k*2+1]);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	cin>>a[i];
	build(1,1,n);
	cin>>m;

	for(int i=1;i<=m;i++)
	{
		cin>>q>>w;
		char ew=getchar();
		if(ew=='\n')
	    {
	    	if(q<=w)
	    	cout<<qh(1,1,n,q+1,w+1)<<endl;
	    	else 
	    	{
	    		cout<<min(qh(1,1,n,q+1,n),qh(1,1,n,1,w+1))<<endl;
			}
		}
        else 
		{
			cin>>e;
			if(q<=w)
			{
				gx(q+1,w+1,e,1,n,1);
			}
			else 
			{
				gx(q+1,n,e,1,n,1);
				gx(1,w+1,e,1,n,1);
			}
		}
	}
	return 0;
}
```


---

## 作者：YuRuiH_ (赞：0)

这道题看大家都用递归线段树

我就来一发$zkw$线段树把

这道题读入是真的恶心，~~卡了我半天~~

[广告](https://www.avg.cx)


$zkw$是真的快，除了榜一大佬那个可能有$Bug$外，~~应该是第二快了吧~~


------------
利用差分的思想来维护：

现在，我们线段树上的节点将不再存对应区间的关键值了。我们需要用$zkw$线段树来维护原关键值的差分值，若原来的$a[i]$代表节点i所代表区间的最大值，则现在我们需要维护的$a[i]=a[i]-a[i<<1]$，特殊地，$a[1]$仍代表整个区间的最大值。

可以这么理解：$a[i]$代表i节点所在区间的最大值比其父亲节点所在区间最大值大多少(可能负数)。

所以剩下的直接上呆码把

```

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define LL long long 
#define rg register

using namespace std;

template<class T>
inline void read(T &o) {
		o=0;
		int w=1;
		char c=getchar();
		while(c<'0'||c>'9') {
			if(c=='-')w*=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9') {
			o=(o<<3)+(o<<1)+(c^48);c=getchar();
		}
		o*=w;
	}


const int MAXN=550000;

int n,m,l,r,k;

struct SegTree
{
    LL tree[MAXN];
    int N;

    inline void Built()
    {
    	N=1;
        memset(tree,0,sizeof tree);
        for(;N<=n+1;N<<=1);
        for(rg int i=N+1;i<=N+n;i++)
            read(tree[i]);
        for(rg int i=N-1;i>=1;i--)
            tree[i]=min(tree[i<<1],tree[i<<1|1]);
        for(rg int i=n+N;i>=1;i--)
            tree[i]=tree[i]-tree[i>>1];
    }

    inline void Update(int l,int r,int val)
    {
        LL tmp;
        for(l+=N-1,r+=N+1;l^r^1;l>>=1,r>>=1)
        {
            if(~l&1)
                tree[l^1]+=val;
            if(r&1)
                tree[r^1]+=val;

            tmp=min(tree[l],tree[l^1]);
            tree[l]-=tmp;
            tree[l^1]-=tmp;
            tree[l>>1]+=tmp;

            tmp=min(tree[r],tree[r^1]);
            tree[r]-=tmp;
            tree[r^1]-=tmp;
            tree[r>>1]+=tmp;
        }
        for(;l!=1;l>>=1)
        {
            tmp=min(tree[l],tree[l^1]);
            tree[l]-=tmp;
            tree[l^1]-=tmp;
            tree[l>>1]+=tmp;
        }
    }

    inline LL query(int l,int r)
    {
        LL lnum=0,rnum=0;
        l+=N,r+=N;
        if(l!=r)
        {
            for(;l^r^1;l>>=1,r>>=1)
            {
                lnum+=tree[l],rnum+=tree[r];
                if(~l&1)
                    lnum=min(lnum,tree[l^1]);
                if(r&1)
                    rnum=min(rnum,tree[r^1]);
            }
        }
        LL ans=min(lnum+tree[l],rnum+tree[r]);
        while(l>1)
            ans+=tree[l>>=1];
        return ans;
    }
}a;

//char str;

int main()
{
    read(n);
    a.Built();
    read(m);
    while(m--)
    {
//        gets(str);
      	scanf("%d%d",&l,&r);
      	char str=getchar();
        if(str=='\n')
        {
			if(l>r)
                printf("%lld\n",min(a.query(l+1,n),a.query(1,r+1)));
            else
                printf("%lld\n",a.query(l+1,r+1));
        }
        else
        {
            read(k);
            if(l>r)
            {
				a.Update(l+1,n,k);
				a.Update(1,r+1,k);
			}	
            else
                a.Update(l+1,r+1,k);   
        }
    }
}

---

## 作者：wanghanjun (赞：0)

区间修改，区间求最小值肯定用线段树做。

线段树部分和板子没什么区别，mina记录最小值，上移改成取最小值，查询取左右区间最小值即可。

还有就是破环为链，查询、修改是判断一下区间是否在两边，不是就直接修改，是则修改两次。

输入写一个快读，顺便看接下来是空格还是换行，以此判断操作类型。

贴上代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;//开long long
const int MAXN=200005;
struct tree{
	ll left,right;
	ll mina,lazy;
}t[MAXN<<2];//数组开4倍
ll a[MAXN],n,m;
bool s;

ll read(){
	ll res=0,x=1;
	char c;
	c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-'){
			x=-1;
		}
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		res=res*10+c-'0';
		c=getchar();
	}
	if(c==' '){
		s=1;
	}//判空格
	else{
		s=0;
	}//判换行
	return res*x;
}//快读

void buildtree(ll id,ll l,ll r){
	t[id].left=l;t[id].right=r;
	t[id].lazy=0;
	if(l==r){
		t[id].mina=a[r];
		return;
	}//判断叶子结点
	ll mid=(l+r)>>1;
	buildtree(id<<1,l,mid);
	buildtree(id<<1|1,mid+1,r);
	t[id].mina=min(t[id<<1].mina,t[id<<1|1].mina);//上移
}建树

void change(ll id,ll l,ll r,ll c){
	if(t[id].left==l&&t[id].right==r){
		t[id].lazy+=c;
		return;
	}//判断目标和结点是否对应
	if(t[id].lazy){
		t[id<<1].lazy+=t[id].lazy;
		t[id<<1|1].lazy+=t[id].lazy;
		t[id].lazy=0;
	}//下移
	if(r<=t[id<<1].right){
		change(id<<1,l,r,c);
	}//只有左半部分
	else if(l>=t[id<<1|1].left){
	    change(id<<1|1,l,r,c);
	}//只有右半部分
	else{
		change(id<<1,l,t[id<<1].right,c);
		change(id<<1|1,t[id<<1|1].left,r,c);
	}//左右都有
	t[id].mina=min(t[id<<1].mina+t[id<<1].lazy,t[id<<1|1].mina+t[id<<1|1].lazy);//上移
}

ll query(ll id,ll l,ll r){
	if(t[id].left==l&&t[id].right==r){
		return t[id].mina+t[id].lazy;
	}//判断目标和结点是否对应
	if(t[id].lazy){
		t[id].mina+=t[id].lazy;
        //此处注意change中由于有上移操作没有加这一行，而此处没有，所以要加
		t[id<<1].lazy+=t[id].lazy;
		t[id<<1|1].lazy+=t[id].lazy;
		t[id].lazy=0;
	}//下移
	if(r<=t[id<<1].right){
		return query(id<<1,l,r);
	}//只有左半部分
	else if(l>=t[id<<1|1].left){
	    return query(id<<1|1,l,r);
	}//只有右半部分
	else{
		return min(query(id<<1,l,t[id<<1].right),query(id<<1|1,t[id<<1|1].left,r));
	}//左右都有
}

int main(){
	n=read();
	for(ll i=1;i<=n;i++){
		a[i]=read();
	}
	buildtree(1,1,n);
	m=read();
	while(m--){
		ll l,r,v;
		l=read();r=read();
		l++;r++;
		if(s==1){
			v=read();
			if(r<l){
				change(1,l,n,v);
				change(1,1,r,v);
			}//两段
			else{
				change(1,l,r,v);
			}//一段
		}
		else{
			if(r<l){
				printf("%lld\n",min(query(1,l,n),query(1,1,r)));
			}两段
			else{
				printf("%lld\n",query(1,l,r));
			}一段
		}
	}
	return 10211314334486875731;
}
```


---

