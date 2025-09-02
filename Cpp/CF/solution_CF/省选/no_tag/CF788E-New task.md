# New task

## 题目描述

On the 228-th international Uzhlyandian Wars strategic game tournament teams from each country are called. The teams should consist of $ 5 $ participants.

The team of Uzhlyandia will consist of soldiers, because there are no gamers.

Masha is a new minister of defense and gaming. The prime duty of the minister is to calculate the efficiency of the Uzhlandian army. The army consists of $ n $ soldiers standing in a row, enumerated from $ 1 $ to $ n $ . For each soldier we know his skill in Uzhlyandian Wars: the $ i $ -th soldier's skill is $ a_{i} $ .

It was decided that the team will consist of three players and two assistants. The skills of players should be same, and the assistants' skills should not be greater than the players' skill. Moreover, it is important for Masha that one of the assistants should stand in the row to the left of the players, and the other one should stand in the row to the right of the players. Formally, a team is five soldiers with indexes $ i $ , $ j $ , $ k $ , $ l $ , $ p $ , such that $ 1<=i&lt;j&lt;k&lt;l&lt;p<=n $ and $ a_{i}<=a_{j}=a_{k}=a_{l}>=a_{p} $ .

The efficiency of the army is the number of different teams Masha can choose. Two teams are considered different if there is such $ i $ such that the $ i $ -th soldier is a member of one team, but not a member of the other team.

Initially, all players are able to be players. For some reasons, sometimes some soldiers become unable to be players. Sometimes some soldiers, that were unable to be players, become able to be players. At any time any soldier is able to be an assistant. Masha wants to control the efficiency of the army, so she asked you to tell her the number of different possible teams modulo $ 1000000007 $ ( $ 10^{9}+7 $ ) after each change.

## 说明/提示

In the first example, after the first change the only team consists of soldiers $ [1,2,4,5,6] $ . After the second change any five soldiers can form a team.

In the first example after the first change the only team is soldiers $ [1,2,3,7,8] $ . After the second change the possible teams are: $ [1,2,3,5,7] $ , $ [1,2,3,5,8] $ , $ [1,2,3,7,8] $ , $ [1,2,5,7,8] $ , $ [1,3,5,7,8] $ , $ [2,3,5,7,8] $ . After the third change the possible teams are: $ [1,3,5,7,8] $ , $ [2,3,5,7,8] $ .

## 样例 #1

### 输入

```
6
1 1 1 1 1 1
2
1 3
2 3
```

### 输出

```
1
6
```

## 样例 #2

### 输入

```
8
3 4 4 2 4 5 4 1
3
1 5
2 5
1 2
```

### 输出

```
1
6
2
```

# 题解

## 作者：zcxxnqwq (赞：5)

读完题发现两个特殊条件：从始至终 $a$ 没有变以及 $p_1$ 和 $p_5$ 的选择与 $b$ 无关。

我们考虑把 $p_1p_2$、$p_4p_5$ 分别看作一个整体，分别记为 $a$ 和 $c$（原谅我的变量重名），那么固定的 $p_2$ 和 $p_4$ 能组成的 $a$ 和 $c$ 的个数是一定的，可以预处理。记 $p_3$ 为 $b$，由于 $a_{p2}=a_{p3}=a_{p4}$，而 $a$ 始终不变，就可以想到对 $a_i$ 相同的点分别开动态开点线段树即可维护。

具体地，将数组 $a$ 离散化之后，用树状数组求出 $pre[i]=\sum\limits_{j=1}^{i-1}(a[j]\le a[i])$ 和 $nxt[i]=\sum\limits_{j=i+1}^n(a[j]\le a[i])$，线段树上 `pushup` 维护 $a,b,c,ab,bc,abc$ 的个数，时间复杂度 $O(n\log n)$ 带上几倍常数，跑的还是挺快的。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ff(i,s,e) for(int i=(s);i<=(e);++i)
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int N=1e5+5,mod=1e9+7;
int n,a[N],b[N],m,pre[N],nxt[N];
struct BIT{
	int t[N];
	inline int lowbit(int x){return x&(-x);}
	inline void upd(int x,int val){
		for(int i=x;i<=n;i+=lowbit(i)) t[i]+=val;
	}
	inline int query(int x){
		int res=0;
		for(int i=x;i;i-=lowbit(i)) res+=t[i];
		return res;
	}
}t1;
int rt[N],tot;
struct qwq{
	int ls,rs,a,ab,abc,b,bc,c;
}t[N*50];
#define ls(k) t[k].ls
#define rs(k) t[k].rs
inline void add(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline void pushup(int k){
	qwq &res=t[k],l=t[ls(k)],r=t[rs(k)];
	res.a=(l.a+r.a)%mod,res.b=(l.b+r.b)%mod,res.c=(l.c+r.c)%mod;
	res.ab=(1ll*l.a*r.b%mod+l.ab+r.ab)%mod;
	res.bc=(1ll*l.b*r.c%mod+l.bc+r.bc)%mod;
	res.abc=(1ll*l.ab*r.c%mod+1ll*l.a*r.bc%mod+l.abc+r.abc)%mod;
}
void upd(int &k,int l,int r,int x,int val){
	if(!k) k=++tot;
	if(l==r){
		if(val) t[k].a=pre[x],t[k].c=nxt[x],t[k].b=1;
		else t[k].a=t[k].b=t[k].c=0;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) upd(ls(k),l,mid,x,val);
	else upd(rs(k),mid+1,r,x,val);
	pushup(k);
}
signed main(){
	n=read();
	ff(i,1,n) a[i]=b[i]=read();
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	ff(i,1,n){
		a[i]=lower_bound(b+1,b+m+1,a[i])-b;
		pre[i]=t1.query(a[i]),t1.upd(a[i],1);
	}
	ff(i,1,n) t1.t[i]=0;
	for(int i=n;i>=1;--i){
		nxt[i]=t1.query(a[i]),t1.upd(a[i],1);
		upd(rt[a[i]],1,n,i,1);
	}
	int ans=0;
	ff(i,1,m) add(ans,t[rt[i]].abc);
	m=read();
	while(m--){
		int op=read(),x=read(),tmp=t[rt[a[x]]].abc;
		if(op==1) upd(rt[a[x]],1,n,x,0);
		else upd(rt[a[x]],1,n,x,1);
		ans=(ans+t[rt[a[x]]].abc-tmp)%mod;
		if(ans<0) ans+=mod;
		printf("%d\n",ans);
	}
}
```


---

## 作者：warzone (赞：3)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/wangrx/solution-cf788e)

## 题目大意

给定一长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$，  
其中每个数 $a_i$ 有一个 $0/1$ 属性 $b_i$，初始 $b_1,b_2,\cdots,b_n$ 全为 $1$。  
$m$ 次操作，每次修改一个元素的 $b_i$ 值，修改后输出满足  
$p_1<p_2<p_3<p_4<p_5,\ a_{p_1}\le a_{p_2}=a_{p_3}=a_{p_4}\le a_{p_5},$  
$b_{p_2}=b_{p_3}=b_{p_4}=1$ 的五元组 $(p_1,p_2,p_3,p_4,p_5)$ 的个数对 $10^9+7$ 取模的结果。 

$\texttt{Data Range: }1\le n,m\le 10^5,1\le a_i\le 10^9$。

## 题解
纯粹的堆砌条件的题。

注意到结果只与 $a_i$ 的大小关系有关，与其确切的值无关，  
因此首先将 $a_i$ 离散化。

之后发现结果与 $b_{p_1},b_{p_5}$ 无关，  
因此先用树状数组计算 $\displaystyle\mathrm{prev}_k=\sum_{i<k}[a_i\le a_k],\mathrm{sufv}_k=\sum_{i>k}[a_i\ge a_k]$，  
此时结果就是 $\displaystyle\sum_{\scriptsize\begin{matrix}p_2<p_3<p_4\\a_{p_2}=a_{p_3}=a_{p_4}\\b_{p_2}=b_{p_3}=b_{p_4}=1\end{matrix}}\mathrm{prev_{p_2}\mathrm{sufv}_{p_4}}$，五元组被优化为三元组。

------------

考虑修改操作产生的贡献：  
设 $\mathrm{pre}_k=\displaystyle\sum_{i<k,a_i=a_k}b_i\mathrm{prev}_i,\mathrm{suf}_k=\sum_{i>k,a_i=a_k}b_i\mathrm{sufv}_i$，  
修改的元素标号为 $k$，则
- $k$ 作为 $p_2$ 时，对答案产生 $\displaystyle\mathrm{prev}_k\sum_{i>k,a_i=a_k}b_i\mathrm{suf}_i$ 的贡献。
- $k$ 作为 $p_4$ 时，对答案产生 $\displaystyle\mathrm{sufv}_k\sum_{i<k,a_i=a_k}b_i\mathrm{pre}_i$ 的贡献。
- $k$ 作为 $p_3$ 时，对答案产生 $\mathrm{pre}_k\mathrm{suf}_k$ 的贡献。

同时，$k$ 会对 $\mathrm{pre}_i(i>k,a_i=a_k)$ 产生 $\mathrm{prev}_k$ 的贡献，  
会对 $\mathrm{suf}_i(i<k,a_i=a_k)$ 产生 $\mathrm{sufv}_k$ 的贡献。

由于 $a_i$ 不同的元素其贡献的计算相互分离，  
对每组 $a_i$ 相同的元素开一棵平衡树维护 $\mathrm{pre},\mathrm{suf}$ 及其区间和。

然后就做完了，细节啥的上面都有。

## Code
```cpp
/*
this code is made by warzone
2021-6-20 10:34
*/
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<random>
#include<algorithm>
typedef unsigned long long ull;
typedef unsigned int word;
typedef unsigned short hword;
typedef unsigned char byte;
struct READ{//快读
	char c;
	inline READ(){c=getchar();}
	template<typename type>
	inline READ& operator >>(register type& num){
		while('0'>c||c>'9') c=getchar();
		for(num=0;'0'<=c&&c<='9';c=getchar())
			num=num*10+(c-'0');
		return *this;
	}
}cin;
const word mod=1e9+7;
std::mt19937 RAND(time(0));
struct treap{
	treap *l,*r;
	word value,size,blc;
	word pre,presum,pretag;
	word suf,sufsum,suftag;
	inline treap(){size=1,blc=RAND();}
	inline void preplus(word in){//pre 区间加
		if((pre+=in)>=mod) pre-=mod;
		if((pretag+=in)>=mod) pretag-=mod;
		if((presum+=(ull)(in)*size%mod)>=mod)
			presum-=mod;
	}
	inline void sufplus(word in){//suf 区间加
		if((suf+=in)>=mod) suf-=mod;
		if((suftag+=in)>=mod) suftag-=mod;
		if((sufsum+=(ull)(in)*size%mod)>=mod)
			sufsum-=mod;
	}
	inline void pushdown(){//标记下传
		if(pretag){
			if(l) l->preplus(pretag);
			if(r) r->preplus(pretag);
			pretag=0;
		}
		if(suftag){
			if(l) l->sufplus(suftag);
			if(r) r->sufplus(suftag);
			suftag=0;
		}
	}
	inline void pushup(){//结果上传
		size=1,presum=pre,sufsum=suf;
		if(l){
			size+=l->size;
			if((presum+=l->presum)>=mod) presum-=mod;
			if((sufsum+=l->sufsum)>=mod) sufsum-=mod;
		}
		if(r){
			size+=r->size;
			if((presum+=r->presum)>=mod) presum-=mod;
			if((sufsum+=r->sufsum)>=mod) sufsum-=mod;
		}
	}
}p[100010],*root[100010];
inline treap* merge(treap *l,treap *r){//treap 合并
	if(l==0) return r;
	if(r==0) return l;
	if(l->blc<=r->blc){
		l->pushdown();
		l->r=merge(l->r,r);
		return l->pushup(),l;
	}
	r->pushdown();
	r->l=merge(l,r->l);
	return r->pushup(),r;
}
// treap 分裂 (<=value 的被保留，>value 的除去)
inline treap* split(word value,treap *&root){
	if(root==0) return 0;
	treap *out;
	if(root->pushdown(),value<root->value){
		out=split(value,root->l);
		register treap *swap=root->l;
		root->l=out,out=swap;
		swap=root,root=out,out=swap;
		return out->pushup(),out;
	}
	out=split(value,root->r);
	return root->pushup(),out;
}
struct BIT{//树状数组
	word sum[100010];
	inline void operator()(){
		memset(sum,0,sizeof(sum));}
	#define lowbit(x) ((x)&-(x))
	inline word operator()(register word id){
		register word ans=0;
		for(;id;id&=~lowbit(id)) ans+=sum[id];
		return ans;
	}
	inline void operator()(
		register word id,register word num){
		for(;id<=100000;id+=lowbit(id))
			sum[id]+=num;
	}
}tree;
word n,m,ans;
word prev[100010],sufv[100010],num[100010];
inline bool cmp(register word a,register word b){
	return prev[a]<prev[b];}
byte b[100010];
inline void push(word in){//b_i=1
	treap *left=root[num[in]];
	treap *right=split(in,left);
	b[in]=1,p[in].pretag=p[in].suftag=0;
	if(left){//作为 p_4 的贡献
		if((ans+=(ull)(left->presum)*sufv[in]%mod)>=mod) ans-=mod;
		left->sufplus(sufv[in]);
		treap* bef=left;//计算自身的 pre
		while(bef->pushdown(),bef->r) bef=bef->r;
		p[in].presum=p[in].pre=(bef->pre+prev[bef->value])%mod;
	}else p[in].presum=p[in].pre=0;
	if(right){//作为 p_2 的贡献
		if((ans+=(ull)(right->sufsum)*prev[in]%mod)>=mod) ans-=mod;
		right->preplus(prev[in]);
		treap* next=right;// 计算自身的 suf
		while(next->pushdown(),next->l) next=next->l;
		p[in].sufsum=p[in].suf=(next->suf+sufv[next->value])%mod;
	}else p[in].sufsum=p[in].suf=0;
	if((ans+=(ull)(p[in].pre)*p[in].suf%mod)>=mod) ans-=mod;//作为 p_3 的贡献
	root[num[in]]=merge(merge(left,p+in),right);
}
inline void pop(word in){//b_i=0，同上
	treap *left=root[num[in]];
	treap *right=split(in,left);
	b[in]=0,split(in-1,left);
	if(left){
		if((ans+=mod-(ull)(left->presum)*sufv[in]%mod)>=mod) ans-=mod;
		left->sufplus(mod-sufv[in]);
	}
	if(right){
		if((ans+=mod-(ull)(right->sufsum)*prev[in]%mod)>=mod) ans-=mod;
		right->preplus(mod-prev[in]);
	}
	if((ans+=mod-(ull)(p[in].pre)*p[in].suf%mod)>=mod) ans-=mod;
	root[num[in]]=merge(left,right);
}
int main(){
	cin>>n;
	for(register word i=1;i<=n;++i)
		cin>>prev[i],sufv[i]=p[i].value=i;
	std::sort(sufv+1,sufv+n+1,cmp);
	for(register word i=1;i<=n;++i)
		if(prev[sufv[i]]==prev[sufv[i-1]])
			num[sufv[i]]=num[sufv[i-1]];
		else num[sufv[i]]=num[sufv[i-1]]+1;
	//离散化

	for(register word i=1;i<=n;++i)
		prev[i]=tree(num[i]),tree(num[i],1);
	tree();
	for(register word i=n;i;--i)
		sufv[i]=tree(num[i]),tree(num[i],1);
	//树状数组计算 prev,sufv

	for(register word i=1;i<=n;++i) push(i);
	word opt,x;
	for(cin>>n;n;--n){
		cin>>opt>>x,--opt;
		if(opt!=b[x]) opt? push(x):pop(x);
		printf("%u\n",ans);
	}
	return 0;
}
```

---

## 作者：shao0320 (赞：2)

#### CF788E New task

数据结构好题！

注意到这个五元组的条件非常的对称，因此考虑搞第三个数。

先不考虑$B$的值和修改，也就是求出最开始的答案，一个比较简单的思路是对于一个位置$x$，记录一下前边有多少个$A[x]$以及其方案数之和，后边也类似，最后乘起来。

我们设这个五元组为$(a,b,c,d,e)$，那么注意到我们刚刚的操作实际上是统计了$(a,b)$和$(d,e)$的答案，然后枚举$c$乘起来。然后我们发现一个比较优秀的性质就是说，这个$a$和$e$的$B$值实际上是无所谓的，因此我们只需要考虑这个$b$和$d$，对于一个位置$x$，其作为$b$和$d$的方案数显然比较好求，可以拿树状数组预处理出来。

那么关键就是统计答案，注意到两个区间合并为一个大区间的时候其实比较好转移，那么考虑线段树维护一下，对于相同的权值$v$，我们搞一棵线段树，把权值为$v$的都搞进去，维护这些$v$在原序列中的位置，线段树$pushup$的时候合并两个子区间的答案。即可方便的计算$c=v$的答案。

修改的话就对于$B$值变为0的地方我们直接把这个点暂时删掉即可。

但是这样做会有个问题，空间开不下，将权值线段树动态开点即可。

这是这一类问题的比较经典的题目，对于两个区间答案合并起来不是很困难的问题，都可以考虑用线段树解决。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 600005
#define mod 1000000007
#define lowbit(x) x&-x
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,q,A[N],a[N],pre[N],suf[N],ans;
struct BIT
{
	int c[N];
	void init(){memset(c,0,sizeof(c));}
	void modify(int x,int k){for(;x<=m;x+=lowbit(x))c[x]+=k;}
	int query(int x){int res=0;for(;x;x-=lowbit(x))res+=c[x];return res;}
}t;
struct Segment_Tree
{
	int cnt,ls[N<<2],rs[N<<2],sum[N<<2],B[N<<2],D[N<<2],BC[N<<2],CD[N<<2],BCD[N<<2];
	void push_up(int k)
	{
		sum[k]=(sum[ls[k]]+sum[rs[k]])%mod;
		B[k]=(B[ls[k]]+B[rs[k]])%mod;
		D[k]=(D[ls[k]]+D[rs[k]])%mod;
		BC[k]=(BC[ls[k]]+BC[rs[k]]+B[ls[k]]*sum[rs[k]]%mod)%mod;
		CD[k]=(CD[ls[k]]+CD[rs[k]]+sum[ls[k]]*D[rs[k]]%mod)%mod;
		BCD[k]=(BCD[ls[k]]+BCD[rs[k]]+B[ls[k]]*CD[rs[k]]%mod+BC[ls[k]]*D[rs[k]]%mod)%mod;
	}
	void modify(int k,int l,int r,int x,int Pre,int Suf,int val)
	{
		//printf("----%d %d %d %d %d %d %d\n",k,l,r,x,Pre,Suf,val);
		if(l==r){B[k]=Pre;D[k]=Suf;sum[k]+=val;return;}
		int mid=(l+r)>>1;
		if(x<=mid){if(!ls[k])ls[k]=++cnt;modify(ls[k],l,mid,x,Pre,Suf,val);}
		else{if(!rs[k])rs[k]=++cnt;modify(rs[k],mid+1,r,x,Pre,Suf,val);}
		push_up(k);
	}
}T;
signed main()	
{
	n=read();
	for(int i=1;i<=n;i++)A[i]=a[i]=read();
//	cout<<"!!!!!!"<<endl;
	sort(a+1,a+1+n);m=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=n;i++)A[i]=lower_bound(a+1,a+1+m,A[i])-a;
	for(int i=1;i<=n;i++)pre[i]=t.query(A[i]),t.modify(A[i],1);
	t.init();
	for(int i=n;i>=1;i--)suf[i]=t.query(A[i]),t.modify(A[i],1);
//	for(int i=1;i<=n;i++)
//	{
//		printf("%d %d\n",pre[i],suf[i]);
//	}
	T.cnt=m;
	for(int i=1;i<=n;i++)T.modify(A[i],1,n,i,pre[i],suf[i],1);
	for(int i=1;i<=m;i++)ans+=T.BCD[i],ans%=mod;;
	//cout<<ans<<endl;
	q=read();
	while(q--)
	{
		int opt=read(),x=read();
		ans=(ans+mod-T.BCD[A[x]])%mod;
		if(opt==1)T.modify(A[x],1,n,x,0,0,-1);
		else T.modify(A[x],1,n,x,pre[x],suf[x],1);
		ans=(ans+T.BCD[A[x]])%mod;
//		for(int i=1;i<=T.cnt;i++)
//		{
//			printf("%d %d %d %d %d %d %d\n",i,T.B[i],T.sum[i],T.D[i],T.BC[i],T.CD[i],T.BCD[i]);
//		}
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
有一个长度为 $n$ 的数列 $a_i$，第 $i$ 个数有一个零一属性 $b_i$，初始所有的 $b$   都为 $1$.  
$m$ 次操作，分为两种：

>$1 \space x$ ：令 $b_x=0$.  
>$2 \space x$ ：令 $b_x=1$

每次操作后输出满足条件的 $p_1<p_2<p_3<p_4<p_5$，满足 $a_{p_1} \le a_{p_2} =a_{p_3}=a_{p_4} \ge a_{p_5}$ 且 $b_{p_2}=b_{p_3}=b_{p_4}=1$ 的个数.  
对 $10^9+7$ 取模的值.  
（保证每次修改后的 $b_i$ 都与原来不同）

## $\text{Solution}$
很适合练手的数据结构题.  
一开始只想到树套树死卡空间然后被 @24KH 一语点破根本不用套.%%%  
本题的关键就是动态统计加入一个点的贡献.  
设 $l_i$ 表示满足 $j<i,a_j\le a_i$ 的 $j$ 的个数.  
$r_i$ 表示满足 $j>i,a_j\le a_i$ 的 $j$ 的个数.  
那么我们考虑加入一个点 $p$ 时的贡献：  
### p 作为中间元素  
增加的方案数为：

$$
\large
\sum_{i<p<j \land a_i=a_p=a_j}l_i\times r_j
$$
也就是：
$$
\large
\sum_{i<p \land a_i=a_p}l_i\times \sum_{j>p \land a_j=a_p}r_j
$$
### p 作为两端元素
由于对称，单举 $p$ 在最左侧为例.  
增加的方案数为：
$$
\large
\sum_{p<i\land a_i=a_p}l_p\times r_i\times\sum_{p<j<i}[a_j=a_p]
$$
换句话说就是 $(p,i)$ 之间每有一个权值相等的点，$(p,i)$ 作为相等的两端就能产生一次贡献.  
### 统计
离散化后对每个权值建一棵线段树.  
$\sum l_i/r_i$ 统计较为简单.  
比较困难的就是统计：
$$
\large
\sum_{p<i\land a_i=a_p}r_i\times\sum_{p<j<i}[a_j=a_p]
$$
这一项.  
设 $rans$ 为这一项的答案，$lans$ 为这一项对称的答案,同时记录数的个数 $siz$，$\sum l_i,\sum r_i$  
合并左右儿子时：
$$siz_{ls}+siz_{rs}\to siz_{fa}$$
$$lsum_{ls}+lsum_{rs}\to lsum_{fa}$$
$$rsum_{ls}+rsum_{rs}\to rsum_{fa}$$
$$lans_{ls}+lans_{rs}+lsum_{ls}\times siz_{rs}\to lans_{fa}$$
$$rans_{ls}+rans_{rs}+rsum_{rs}\times siz_{ls}\to rans_{fa}$$
即可.

## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e5+100;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
ll le[N],ri[N];
int id[N],bac[N];

#define mid ((l+r)>>1)
struct node{
  ll siz;
  ll lsum,rsum;
  ll lans,rans;
};
node merge(node a,node b){
  return (node){a.siz+b.siz,(a.lsum+b.lsum)%mod,(a.rsum+b.rsum)%mod,
      (a.lans+b.lans+a.lsum*b.siz)%mod,(a.rans+b.rans+a.siz*b.rsum)%mod};
}
struct tree{
  node o;
  int ls,rs;
}tr[N<<5];
int rt[N],tot;
inline int copy(int x){
  ++tot;tr[tot]=tr[x];
  return tot;
}
void add(int &k,int l,int r,int p,int w){
  if(!k) k=copy(k);
  if(l==r){
    tr[k].o.siz+=w;
    tr[k].o.lsum+=w*le[l];
    tr[k].o.rsum+=w*ri[l];
    return;
  }
  if(p<=mid) add(tr[k].ls,l,mid,p,w);
  else add(tr[k].rs,mid+1,r,p,w);
  tr[k].o=merge(tr[tr[k].ls].o,tr[tr[k].rs].o);
  //printf("  k=%d (%d %d) l")
}
//op=1:lsum
//op=2:lans
//op=3:rsum
//op=4:rans
node ask(int k,int l,int r,int x,int y){
  if(!k||x>y) return (node){0,0,0,0,0};
  if(x<=l&&r<=y) return tr[k].o;
  if(y<=mid) return ask(tr[k].ls,l,mid,x,y);
  else if(x>mid) return ask(tr[k].rs,mid+1,r,x,y);
  else return merge(ask(tr[k].ls,l,mid,x,y),ask(tr[k].rs,mid+1,r,x,y));
}

int q[N],cnt,a[N];
int f[N];
inline void Add(int p){
  for(;p<=cnt;p+=p&-p) ++f[p];
  return;
}
inline int Ask(int p){
  int res(0);
  for(;p;p-=p&-p) res+=f[p];
  return res;
}

inline ll calc(int pl){
  int o=rt[a[pl]];
  node L=ask(o,1,n,1,pl-1),R=ask(o,1,n,pl+1,n);
  return (L.lsum*R.rsum%mod+L.lans*ri[pl]%mod+R.rans*le[pl]%mod)%mod;
}
ll tt;
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=n;i++) q[i]=a[i]=read();
  sort(q+1,q+1+n);
  cnt=unique(q+1,q+1+n)-q-1;
  for(int i=1;i<=n;i++) a[i]=lower_bound(q+1,q+1+cnt,a[i])-q;
  for(int i=1;i<=n;i++){
    le[i]=Ask(a[i]);Add(a[i]);
  }
  memset(f,0,sizeof(f));
  for(int i=n;i>=1;i--){
    ri[i]=Ask(a[i]);Add(a[i]);
  }
  for(int i=1;i<=n;i++) id[i]=++bac[a[i]];
  //for(int i=1;i<=n;i++) printf("i=%d a=%d le=%lld ri=%lld id=%d\n",i,a[i],le[i],ri[i],id[i]);
  for(int i=1;i<=n;i++){
    tt+=calc(i);tt%=mod;
    add(rt[a[i]],1,n,i,1);
  }
  m=read();
  for(int i=1;i<=m;i++){
    int op=read(),x=read();
    if(op==1){
      add(rt[a[x]],1,n,x,-1);tt-=calc(x);
    }
    else{
      tt+=calc(x);add(rt[a[x]],1,n,x,1);
    }
    tt+=mod;tt%=mod;
    printf("%lld\n",tt);
  }
  return 0;
}
/*


*/

```


---

## 作者：daniEl_lElE (赞：0)

由于 $a_{p_1},a_{p_5}$ 没有 $b_{i}$ 的限制，故优先对于每个位置 $i$ 求出 $j<i$ 且 $a_j\leq a_i$，$j>i$ 且 $a_j\leq a_i$ 的 $j$ 个数。此时，我们可以将 $a_{p_1},a_{p_5}$ 分别跟着 $a_{p_2},a_{p_4}$ 一起计算。

容易发现 $a_i$ 不会改变，于是对于不同 $a_i$ 分开处理。对每个 $a_i$ 建一棵动态开点线段树。维护每个区间选出 $a_{p_x\sim p_y}$（$2\leq x\leq y\leq 4$）的方案数（注意，$p_1,p_5$ 分别跟 $p_2,p_4$ 一起计算，也就是说，选出 $p_2$ 的实际方案数是在前面再选择一个 $p_1$ 的方案数，$p_5$ 同理）。即可在 $O((n+m)\log n)$ 的复杂度内解决问题。笔者使用了矩阵去维护。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int a[100005],lsh[100005],pcnt[100005],scnt[100005],rt[100005],pos[100005];
vector<int> vc[100005];
struct bit{
	int f[100005];
	void add(int i){
		while(i<=100000){
			f[i]++;
			i+=lowbit(i); 
		}
	}
	int qry(int i){
		int ans=0;
		while(i){
			ans+=f[i];
			i-=lowbit(i);
		}
		return ans;
	}
}bitree;
struct node{
	int a[3][3];
}ept;
node merge(node x,node y){
	node z=ept;
	for(int i=0;i<3;i++){
		for(int j=i;j<3;j++){
			(z.a[i][j]+=x.a[i][j]+y.a[i][j])%=mod;
			for(int k=j+1;k<3;k++){
				(z.a[i][k]+=x.a[i][j]*y.a[j+1][k])%=mod;
			}
		}
	}
	return z;
}
node makenode(int x,int y,int z){
	node ans=ept;
	ans.a[0][0]=x,ans.a[1][1]=y,ans.a[2][2]=z;
	return ans;
}
struct sgt{
	node f[400005];
	int tl[400005],tr[400005],cnt;
	int build(int i,int l,int r){
		if(!i) i=++cnt;
		if(l==r){
			return i;
		}
		tl[i]=build(0,l,mid);
		tr[i]=build(0,mid+1,r);
		return i;
	}
	void change(int i,int l,int r,int pos,node cg){
		if(l==r){
			f[i]=cg;
			return ;
		}
		if(pos<=mid) change(tl[i],l,mid,pos,cg);
		else change(tr[i],mid+1,r,pos,cg);
		f[i]=merge(f[tl[i]],f[tr[i]]);
	}
}tree;
signed main(){
	int n; cin>>n; for(int i=1;i<=n;i++) cin>>a[i],lsh[i]=a[i]; sort(lsh+1,lsh+n+1); int m=unique(lsh+1,lsh+n+1)-lsh-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+m+1,a[i])-lsh,vc[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		pcnt[i]=bitree.qry(a[i]);
		bitree.add(a[i]);
	}
	memset(bitree.f,0,sizeof(bitree.f));
	for(int i=n;i>=1;i--){
		scnt[i]=bitree.qry(a[i]);
		bitree.add(a[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(vc[i].size()){
			rt[i]=tree.build(0,1,vc[i].size());
			int it=0;
			for(auto v:vc[i]){
				it++;
				pos[v]=it;
				tree.change(rt[i],1,vc[i].size(),it,makenode(pcnt[v],1,scnt[v]));
			}
			(ans+=tree.f[rt[i]].a[0][2])%=mod;
		}
	}
	int q; cin>>q; 
	for(int i=1;i<=q;i++){
		int opt,x; cin>>opt>>x;
		if(opt==1){
			(ans+=mod-tree.f[rt[a[x]]].a[0][2])%=mod;
			tree.change(rt[a[x]],1,vc[a[x]].size(),pos[x],makenode(0,0,0));
			(ans+=tree.f[rt[a[x]]].a[0][2])%=mod;
		}
		if(opt==2){
			(ans+=mod-tree.f[rt[a[x]]].a[0][2])%=mod;
			tree.change(rt[a[x]],1,vc[a[x]].size(),pos[x],makenode(pcnt[x],1,scnt[x]));
			(ans+=tree.f[rt[a[x]]].a[0][2])%=mod;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

[Codeforces 题目传送门](https://codeforces.com/contest/788/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF788E)

~~这是一道 *2900 的 D1E，而且被！我！自！己！搞！出！来！了！~~

~~虽然我承认它难度及摆放的位置异常异常虚高，并且就算我到了现场也不可能切掉~~

下记 $t_x$ 表示 $x$ 是否可以被选择。

首先题目要我们统计五元组 $(a,b,c,d,e)$ 的个数，但稍微观察下就能发现 $a,e$ 的个数是很好维护的，并且它不受到 $t_x$ 的值的影响，因此我们可以提前把它预处理出来，记 $pre_i=\sum\limits_{j=1}^{i-1}[a_j\le a_i]$，$nxt_i=\sum\limits_{j=i+1}^n[a_j\le a_i]$，那么显然对于固定的三元组 $(b,c,d)$ 合法的 $a$ 的个数为 $pre_b$，合法的 $e$ 的个数为 $nxt_d$，也就是说要求的这东西等价于 $\sum\limits_{1\le b\le c\le d\le n}pre_b·nxt_d·[a_b=a_c=a_d]$

其次考虑一次修改对答案的影响，显然每次将某个点 $x$ 由可选状态设为不可选状态，答案的变化量为包含 $x$ 的三元组 $(b,c,d)$ 的贡献的相反数；反之也同理。因此我们只需维护包含 $x$ 的三元组 $(b,c,d)$ 的贡献之和。这个可以分三种情况：

- $c=x$，由于 $b$ 与 $d$ 的贡献相互独立，故可算出 $b,d$ 的贡献后用乘法原理将其乘起来，即 $\sum\limits_{b=1}^{x-1}pre_b[a_b=a_x\land t_b=1]\times\sum\limits_{d=x+1}^nnxt_d[a_d=a_x\land t_d=1]$。
- $b=x$，我们记 $s_i=\sum\limits_{j=1}^i[a_j=a_i\land t_j=1]$，考虑枚举 $d$，那么合法的 $c$ 的个数即为 $s_d-s_x-1$，即 $\sum\limits_{d=x+1}^n(s_d-s_x-1)\times nxt_d\times[a_d=a_x\land t_d=1]$

- $d=x$，与 $b=x$ 的情况类似，这里就不再赘述了。

考虑怎样维护这个东西。我们将 $a_i$ 离散化并对每个 $a_i$ 建一棵动态开点线段树。具体来说假设对于 $x$ 这个值存在 $k_x$ 个 $a_t=x$ 的 $t$，从小到大依次是 $p_1,p_2,\dots,p_{k_x}$，那么我们就建一棵长度为 $k_x$ 的线段树，线段树上每一个区间 $[l,r]$ 维护以下五个值：

- $pre0:\sum\limits_{i=l}^rpre_{p_i}\times t_{p_i}$
- $nxt0:\sum\limits_{i=l}^rnxt_{p_i}\times t_{p_i}$
- $pre1:\sum\limits_{i=l}^rpre_{p_i}\times t_{p_i}\times s_{p_i}$
- $nxt1:\sum\limits_{i=l}^rnxt_{p_i}\times t_{p_i}\times s_{p_i}$
- $cnt:\sum\limits_{i=l}^rt_{p_i}$

那么 $c=x$ 的情况我们只需查一遍 $pre0,nxt0$ 即可，$b=x$ 的情况我们可将询问改写成 $\sum\limits_{d=x+1}^ns_d\times nxt_d\times t_d\times[a_d=a_x]-(s_x+1)\times\sum\limits_{d=x+1}^ns_d\times t_d\times[a_d=a_x]$，这样我们只需查一遍 $cnt,nxt0,nxt1$ 即可。$d=x$ 的情况也可以采用类似的改写方式，只需查一遍 $cnt,pre0,pre1$ 即可，这样我们即可在对数时间内求出包含 $x$ 的三元组 $(b,c,d)$ 的贡献。

最后考虑修改对线段树维护的五个值的影响，显然最初所有的 $s_{p_i}=i,t_{p_i}=1$，所以我们令所有叶子节点 $[i,i]$ 的 $pre0$ 为 $pre_{p_i}$，$nxt0$ 为 $nxt_{p_i}$，$pre1$ 为 $pre_{p_i}\times i$，$nxt1$ 为 $nxt_{p_i}\times i$，$cnt$ 为 $1$，而对于一次修改操作，假设我们修改了 $x$ 的状态，那么显然我们需要进行两次操作：

- 令 $t_x=0$ 或 $t_x=1$
- 假设 $x$ 在 $a_x$ 的线段树上的位置为 $p$，那么我们需令 $[p+1,k_{a_x}]$ 的 $s$ 值加 $1$ 或减 $1$

第一个操作显然就递归到叶子节点单调修改即可。第二个操作就在对应区间上执行区间加操作，假设我们要对 $[l,r]$ 区间的 $s$ 值执行 $+x$ 操作，那么我们显然就令 $pre_1\leftarrow pre_1+pre_0\times x$，$nxt_1\leftarrow nxt_1+nxt_0\times x$，直接打个懒标记就行了。

时间复杂度 $n\log n$，常数有亿点大，~~因此又一次荣膺了最劣解~~

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1e5;
const int MOD=1e9+7;
const int INV3=333333336;
int n,qu,a[MAXN+5],key[MAXN+5],uni[MAXN+5],num=0;
int t[MAXN+5],pre[MAXN+5],nxt[MAXN+5];
void add(int x,int v){for(int i=x;i<=num;i+=(i&-i)) t[i]+=v;}
int ask(int x){int ret=0;for(int i=x;i;i&=(i-1)) ret+=t[i];return ret;}
vector<int> pos[MAXN+5];int where[MAXN+5],cnt[MAXN+5];
struct node{
	int ch[2];
	int lz_pre,lz_nxt,cnt;
	int pre0,pre1;
	int nxt0,nxt1;
} s[MAXN*4+5];
int rt[MAXN+5],ncnt=0;
void pushup(int k){
	s[k].pre0=(s[s[k].ch[0]].pre0+s[s[k].ch[1]].pre0)%MOD;
	s[k].pre1=(s[s[k].ch[0]].pre1+s[s[k].ch[1]].pre1)%MOD;
	s[k].nxt0=(s[s[k].ch[0]].nxt0+s[s[k].ch[1]].nxt0)%MOD;
	s[k].nxt1=(s[s[k].ch[0]].nxt1+s[s[k].ch[1]].nxt1)%MOD;
	s[k].cnt=s[s[k].ch[0]].cnt+s[s[k].ch[1]].cnt;
}
void build(int &k,int l,int r,int v){
	k=++ncnt;
	if(l==r){
		s[k].cnt=1;
		s[k].pre0=pre[pos[v][l-1]];s[k].pre1=1ll*l*s[k].pre0%MOD;
		s[k].nxt0=nxt[pos[v][l-1]];s[k].nxt1=1ll*(cnt[v]-l+1)*s[k].nxt0%MOD;
		return;
	} int mid=l+r>>1;
	build(s[k].ch[0],l,mid,v);build(s[k].ch[1],mid+1,r,v);
	pushup(k);
}
void pushdown(int k){
	if(s[k].lz_pre){
		s[s[k].ch[0]].pre1=(s[s[k].ch[0]].pre1+1ll*s[k].lz_pre*s[s[k].ch[0]].pre0%MOD)%MOD;
		s[s[k].ch[0]].lz_pre=(s[s[k].ch[0]].lz_pre+s[k].lz_pre)%MOD;
		s[s[k].ch[1]].pre1=(s[s[k].ch[1]].pre1+1ll*s[k].lz_pre*s[s[k].ch[1]].pre0%MOD)%MOD;
		s[s[k].ch[1]].lz_pre=(s[s[k].ch[1]].lz_pre+s[k].lz_pre)%MOD;
		s[k].lz_pre=0;
	} if(s[k].lz_nxt){
		s[s[k].ch[0]].nxt1=(s[s[k].ch[0]].nxt1+1ll*s[k].lz_nxt*s[s[k].ch[0]].nxt0%MOD)%MOD;
		s[s[k].ch[0]].lz_nxt=(s[s[k].ch[0]].lz_nxt+s[k].lz_nxt)%MOD;
		s[s[k].ch[1]].nxt1=(s[s[k].ch[1]].nxt1+1ll*s[k].lz_nxt*s[s[k].ch[1]].nxt0%MOD)%MOD;
		s[s[k].ch[1]].lz_nxt=(s[s[k].ch[1]].lz_nxt+s[k].lz_nxt)%MOD;
		s[k].lz_nxt=0;
	}
}
int query_cnt(int k,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return s[k].cnt;
	pushdown(k);int mid=l+r>>1;
	if(qr<=mid) return query_cnt(s[k].ch[0],l,mid,ql,qr);
	else if(ql>mid) return query_cnt(s[k].ch[1],mid+1,r,ql,qr);
	else return query_cnt(s[k].ch[0],l,mid,ql,mid)+query_cnt(s[k].ch[1],mid+1,r,mid+1,qr);
}
int query_pre0(int k,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return s[k].pre0;
	pushdown(k);int mid=l+r>>1;
	if(qr<=mid) return query_pre0(s[k].ch[0],l,mid,ql,qr);
	else if(ql>mid) return query_pre0(s[k].ch[1],mid+1,r,ql,qr);
	else return (query_pre0(s[k].ch[0],l,mid,ql,mid)+query_pre0(s[k].ch[1],mid+1,r,mid+1,qr))%MOD;
}
int query_pre1(int k,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return s[k].pre1;
	pushdown(k);int mid=l+r>>1;
	if(qr<=mid) return query_pre1(s[k].ch[0],l,mid,ql,qr);
	else if(ql>mid) return query_pre1(s[k].ch[1],mid+1,r,ql,qr);
	else return (query_pre1(s[k].ch[0],l,mid,ql,mid)+query_pre1(s[k].ch[1],mid+1,r,mid+1,qr))%MOD;
}
int query_nxt0(int k,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return s[k].nxt0;
	pushdown(k);int mid=l+r>>1;
	if(qr<=mid) return query_nxt0(s[k].ch[0],l,mid,ql,qr);
	else if(ql>mid) return query_nxt0(s[k].ch[1],mid+1,r,ql,qr);
	else return (query_nxt0(s[k].ch[0],l,mid,ql,mid)+query_nxt0(s[k].ch[1],mid+1,r,mid+1,qr))%MOD;
}
int query_nxt1(int k,int l,int r,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return s[k].nxt1;
	pushdown(k);int mid=l+r>>1;
	if(qr<=mid) return query_nxt1(s[k].ch[0],l,mid,ql,qr);
	else if(ql>mid) return query_nxt1(s[k].ch[1],mid+1,r,ql,qr);
	else return (query_nxt1(s[k].ch[0],l,mid,ql,mid)+query_nxt1(s[k].ch[1],mid+1,r,mid+1,qr))%MOD;
}
void modify(int k,int l,int r,int p,int x,int ps,int ss,int v){
	if(l==r){
		if(v==-1){
			s[k].cnt=s[k].pre0=s[k].pre1=0;
			s[k].nxt0=s[k].nxt1=0;
		} else {
			s[k].cnt=1;
			s[k].pre0=pre[x];s[k].pre1=1ll*pre[x]*ps%MOD;
			s[k].nxt0=nxt[x];s[k].nxt1=1ll*nxt[x]*ss%MOD;
		} return;
	} pushdown(k);int mid=l+r>>1;
	if(p<=mid) modify(s[k].ch[0],l,mid,p,x,ps,ss,v);
	else modify(s[k].ch[1],mid+1,r,p,x,ps,ss,v);
	pushup(k);
}
void modify_pre(int k,int l,int r,int ql,int qr,int x){
	if(ql>qr) return;
	if(ql<=l&&r<=qr){
		s[k].pre1=(s[k].pre1+1ll*x*s[k].pre0%MOD)%MOD;
		s[k].lz_pre=(s[k].lz_pre+x)%MOD;return;
	} pushdown(k);int mid=l+r>>1;
	if(qr<=mid) modify_pre(s[k].ch[0],l,mid,ql,qr,x);
	else if(ql>mid) modify_pre(s[k].ch[1],mid+1,r,ql,qr,x);
	else modify_pre(s[k].ch[0],l,mid,ql,mid,x),modify_pre(s[k].ch[1],mid+1,r,mid+1,qr,x);
	pushup(k);
}
void modify_nxt(int k,int l,int r,int ql,int qr,int x){
	if(ql>qr) return;
	if(ql<=l&&r<=qr){
		s[k].nxt1=(s[k].nxt1+1ll*x*s[k].nxt0%MOD)%MOD;
		s[k].lz_nxt=(s[k].lz_nxt+x)%MOD;return;
	} pushdown(k);int mid=l+r>>1;
	if(qr<=mid) modify_nxt(s[k].ch[0],l,mid,ql,qr,x);
	else if(ql>mid) modify_nxt(s[k].ch[1],mid+1,r,ql,qr,x);
	else modify_nxt(s[k].ch[0],l,mid,ql,mid,x),modify_nxt(s[k].ch[1],mid+1,r,mid+1,qr,x);
	pushup(k);
}
int get(int x){
	if(!query_cnt(rt[a[x]],1,cnt[a[x]],where[x],where[x])) return 0;
	int ret=0;
	ret=(ret+1ll*query_pre0(rt[a[x]],1,cnt[a[x]],1,where[x]-1)*
				 query_nxt0(rt[a[x]],1,cnt[a[x]],where[x]+1,cnt[a[x]]))%MOD;
	ret=(ret+1ll*nxt[x]*
		(1ll*(query_cnt(rt[a[x]],1,cnt[a[x]],1,where[x])-1)*
			  query_pre0(rt[a[x]],1,cnt[a[x]],1,where[x]-1)%MOD-
			  query_pre1(rt[a[x]],1,cnt[a[x]],1,where[x]-1)+MOD))%MOD;
	ret=(ret+1ll*pre[x]*
		(1ll*(query_cnt(rt[a[x]],1,cnt[a[x]],where[x],cnt[a[x]])-1)*
			  query_nxt0(rt[a[x]],1,cnt[a[x]],where[x]+1,cnt[a[x]])%MOD-
			  query_nxt1(rt[a[x]],1,cnt[a[x]],where[x]+1,cnt[a[x]])+MOD))%MOD;
	return ret;
}
void toggle(int x,int v){
	if(v==-1){
		modify(rt[a[x]],1,cnt[a[x]],where[x],x,0,0,-1);
		modify_pre(rt[a[x]],1,cnt[a[x]],where[x]+1,cnt[a[x]],MOD-1);
		modify_nxt(rt[a[x]],1,cnt[a[x]],1,where[x]-1,MOD-1);
	} else {
		int ps=query_cnt(rt[a[x]],1,cnt[a[x]],1,where[x]-1);
		int ss=query_cnt(rt[a[x]],1,cnt[a[x]],where[x]+1,cnt[a[x]]);
		modify(rt[a[x]],1,cnt[a[x]],where[x],x,ps+1,ss+1,1);
		modify_pre(rt[a[x]],1,cnt[a[x]],where[x]+1,cnt[a[x]],1);
		modify_nxt(rt[a[x]],1,cnt[a[x]],1,where[x]-1,1);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),key[i]=a[i];
	sort(key+1,key+n+1);
	for(int i=1;i<=n;i++) if(key[i]^key[i-1]) uni[++num]=key[i];
	for(int i=1;i<=n;i++) a[i]=lower_bound(uni+1,uni+num+1,a[i])-uni;
	for(int i=1;i<=n;i++) add(a[i],1),pre[i]=ask(a[i])-1;memset(t,0,sizeof(t));
	for(int i=n;i;i--) add(a[i],1),nxt[i]=ask(a[i])-1;
	for(int i=1;i<=n;i++) pos[a[i]].push_back(i),where[i]=pos[a[i]].size();
	for(int i=1;i<=n;i++) cnt[a[i]]++;
	for(int i=1;i<=num;i++) build(rt[i],1,cnt[i],i);
	int ans=0;
	for(int i=1;i<=n;i++) ans=(ans+get(i))%MOD;
	ans=1ll*ans*INV3%MOD;
	int qu;scanf("%d",&qu);
	while(qu--){
		int opt,x;scanf("%d%d",&opt,&x);
		if(opt==1){
			ans=(ans-get(x)+MOD)%MOD;
			toggle(x,-1);
		} else {
			toggle(x,1);
			ans=(ans+get(x))%MOD;
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
9
3 4 4 2 4 5 4 4 1
3
1 5
2 5
1 2
*/
```



---

