# 愤怒的XiaoX

## 题目背景

### 答疑请到 https://www.luogu.org/discuss/show?postid=79498

在几天前的模拟赛上，$XiaoX$又双叒叕$AK$了

他想卡一卡大家，于是他出了下面的一道题：

## 题目描述

给定一个序列，你要维护下列操作：

$1$ $l$ $r$ $k$，表示从$l$到$r$的数字最后$k$位按位取反

$2$ $l$ $r$ $k$，表示从$l$到$r$的数字最后$k$位进行翻转

$3$ $w$ 表示查询$w$这个位置的值

为了降低这道题的难度，我们做出以下规定：

对于序列的操作，我们的$k$在一定范围内是一定的

我们一共会有$t$个$k$

每个$k$后面跟着一些操作

这些操作的$k$（修改的位数）都是相同的

###  按位取反定义：

比如说，一个数的二进制表示是：

```
10100111
```

对后5位取反后变成：

```
10111000
```

###  翻转定义：

比如说，一个数的二进制表示是：

```
10100111
```

对后5位翻转后变成：

```
10111100
```

## 说明/提示

对于$10$%的数据，没有$1,2$操作

对于另$10$%的数据，没有$1$操作

对于另$10$%的数据，没有$2$操作

对于$50$%的数据，$t<=1$

对于$70$%的数据，$t<=2$

对于$100$%的数据，$t<=5$,$1<=n<=50000,1<=q_i<=20000,k<=25$,初始序列制造方式为$rand()*rand()$(windows下)

感谢@swhsz验题

## 样例 #1

### 输入

```
5 2
665667089 948925818 1118302620 288255565 1682529647 
5 2
1 3 4
3 1
2 3 5
2 2 4
3 4
5 25
1 3 3
1 3 4
3 1
2 1 5
2 1 3```

### 输出

```
665667089
288255566
665667089```

# 题解

## 作者：ztz11 (赞：2)

## 思路：
这道题其实就是一道双Lazy线段树裸题

因为我们知道，当k一定时，取反偶数次最后k位等于不取反

同理，当k一定时，翻转偶数次最后k位等于不取反

我们使用双Lazy分别存下这两个东西

同时一直对2取模

同时我们使用标记永久化

向下传参Lazy

单点查询到这个点时，判断是否需要取反即可

取反和翻转是位运算基本知识

大家可以看代码

## 代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rij register int j
#define rii register int i
#define rs 65536
using namespace std;
struct tree{
    int fz,qf,val;
}x[250005];
int n,k,q,t,bs[50];
void ycl()
{
    bs[0]=1;
    for(rii=1;i<=25;i++)
    {
        bs[i]=bs[i-1]*2;
    }
}
void cf(int val)
{
    unsigned int kkk=val;
    while(kkk!=0)
    {
        cout<<kkk%2<<" ";
        kkk/=2;
    }
    cout<<endl;
}
int qf(int val)
{
    int bs=(1<<k);
    int ltt=val%bs;
    val-=ltt;
    ltt=-ltt;
    ltt--;
    unsigned kkk=ltt;
    kkk%=bs;
    return val+kkk;
}
int fz(int val)
{
    int bis=(1<<k);
    int ltt=val%bis;
    int v=0;
    val-=ltt;
    for(rii=1;i<=k;i++)
    {
        v+=(ltt%2)*bs[k-i];
        ltt/=2;
    }
    return val+v;
}
void add(int wz,int nl,int nr,int val,int bh)
{
    if(wz==nl&&wz==nr)
    {
        x[bh].val=val;
        return;
    }
    int mid=(nl+nr)/2;
    if(wz<=mid)
    {
        add(wz,nl,mid,val,bh*2);
    }
    else
    {
        add(wz,mid+1,nr,val,bh*2+1);
    }
}
void change1(int l,int r,int nl,int nr,int bh)
{
    if(l<nl)
    {
        l=nl;
    }
    if(r>nr)
    {
        r=nr;
    }
    if(l==nl&&r==nr)
    {
        x[bh].qf++;
        x[bh].qf%=2;
        return;
    }
    int mid=(nl+nr)/2;
    if(l<=mid)
    {
        change1(l,r,nl,mid,bh*2);
    }
    if(r>mid)
    {
        change1(l,r,mid+1,nr,bh*2+1);
    }
}
void change2(int l,int r,int nl,int nr,int bh)
{
    if(l<nl)
    {
        l=nl;
    }
    if(r>nr)
    {
        r=nr;
    }
    if(l==nl&&r==nr)
    {
        x[bh].fz++;
        x[bh].fz%=2;
        return;
    }
    int mid=(nl+nr)/2;
    if(l<=mid)
    {
        change2(l,r,nl,mid,bh*2);
    }
    if(r>mid)
    {
        change2(l,r,mid+1,nr,bh*2+1);
    }
}
int query(int wz,int nl,int nr,int bh,int lazy1,int lazy2)
{
    lazy1%=2;
    lazy2%=2;
    if(wz==nl&&wz==nr)
    {
        lazy1+=x[bh].qf;
        lazy2+=x[bh].fz;
        int ltt=x[bh].val;
        if(lazy1==1)
        {
            ltt=qf(ltt);
        }
        if(lazy2==1)
        {
            ltt=fz(ltt);
        }
        return ltt;
    }
    int mid=(nl+nr)/2;
    if(wz<=mid)
    {
        return query(wz,nl,mid,bh*2,lazy1+x[bh].qf,lazy2+x[bh].fz);
    }
    else
    {
        return query(wz,mid+1,nr,bh*2+1,lazy1+x[bh].qf,lazy2+x[bh].fz);
    }
}
void pd(int wz,int l,int r)
{
    if(l==r)
    {
        if(x[wz].fz!=0)
        {
            x[wz].fz=0;
            x[wz].val=fz(x[wz].val);
        }
        if(x[wz].qf!=0)
        {
            x[wz].qf=0;
            x[wz].val=qf(x[wz].val);
        }
        return;
    }
    if(x[wz].fz!=0)
    {
        x[wz*2].fz++;
        x[wz*2].fz%=2;
        x[wz*2+1].fz++;
        x[wz*2+1].fz%=2;
    }
    if(x[wz].qf!=0)
    {
        x[wz*2].qf++;
        x[wz*2].qf%=2;
        x[wz*2+1].qf++;
        x[wz*2+1].qf%=2;
    }
    x[wz].qf=0;
    x[wz].fz=0;
    int mid=(l+r)/2;
    pd(wz*2,l,mid);
    pd(wz*2+1,mid+1,r);
}
int main()
{
//     freopen("XiaoX10.in","r",stdin);
//     freopen("XiaoX10.out","w",stdout);
    ycl();
    scanf("%d%d",&n,&t);
    for(rii=1;i<=n;i++)
    {
        int val;
        scanf("%d",&val);
        add(i,1,rs,val,1);
    }
    for(rii=1;i<=t;i++)
    {
        if(i!=1)
        {
            pd(1,1,rs);
        }
        scanf("%d%d",&q,&k);
        int pid,l,r,wz;
        for(rij=1;j<=q;j++)
        {
            scanf("%d",&pid);
            if(pid==1)
            {
                scanf("%d%d",&l,&r);
                change1(l,r,1,rs,1);
            }
            if(pid==2)
            {
                scanf("%d%d",&l,&r);
                change2(l,r,1,rs,1);
            }
            if(pid==3)
            {
                scanf("%d",&wz);
                int ltt=query(wz,1,rs,1,0,0);
                printf("%d\n",ltt);
            }
        }
    }
    k=4;
}
```

---

## 作者：hovny (赞：1)

## 解题思路

**线段树**，只不过要维护两个标记

### 分析

 · 操作 $1$，对每位取反，直接异或上 `(1<<k)+1` 即可

 · 操作 $2$，翻转二进制比较复杂，貌似也没有直接翻转的函数，就只能手写

再深究发现，其实两个操作是**互不影响**的，因此只需维护两个 $tag$ 即可，再看题目中的 $k$ 的限制，一系列操作的 $k$ 值相同，因此 $tag$ 维护的信息应为 $bool$ 类型，表示上述操作是否做了（因为同一个操作做两次就是无效的

又有 $t$ 小于 $5$，所以在 $k$ 值改变，也就是做下一组询问的时候，可以直接暴力把先前的标记全部下传

关于查询，其实只要把 对查询的点有影响的标记 下传即可，都不用维护区间

### warning

貌似没有什么特别坑的地方，复制粘贴的时候记得改函数名就好了~~（尴尬~~

## Code

```cpp
#include<bits/stdc++.h>
#define rgt register
#define rint rgt int
#define LL long long
#define rll rgt LL
#define inf 0x7f7f7f7f
#define N 50003
using namespace std;
template<class K>inline bool cmax(K&a,const K&b){return (a<b)?a=b,1:0;}
template<class K>inline bool cmin(K&a,const K&b){return (a>b)?a=b,1:0;}
inline int read() {
	rint s=0;
	rgt char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) s=(s<<1)+(s<<3)+c-'0',c=getchar();
	return s;
}
int n,m,T,K,b[N],L,R,pos,y;
bool tag[N<<2],rev[N<<2];
inline void push(rint k,rint l,rint r) {//下传标记
	if(l==r) {//如果已经到了某个位置，直接修改
		if(tag[k]) b[l]^=y;//反转直接异或(1<<k)-1
		if(rev[k]) {//翻转要自己写
			rint i,c=b[l]&y,s=0;b[l]-=c;
			for(i=0;i<K;++i) {
				if(c&(1<<i)) s+=1<<(K-i-1);
			}b[l]+=s;
		}
	}
	else {//否则下传标记
		rint ls=k<<1;
		if(tag[k]) tag[ls]^=1,tag[ls|1]^=1;
		if(rev[k]) rev[ls]^=1,rev[ls|1]^=1;
	}
	tag[k]=rev[k]=0;
}
inline void Modify(rint k,rint l,rint r) {//打反转标记
	push(k,l,r);if(r<L||R<l) return;
	if(L<=l&&r<=R) {tag[k]^=1;return push(k,l,r);}
	rint m=(l+r)>>1,ls=k<<1;
	Modify(ls,l,m),Modify(ls|1,m+1,r);
}
inline void Flip(rint k,rint l,rint r) {//打翻转标记
	push(k,l,r);if(r<L||R<l) return;
	if(L<=l&&r<=R) {rev[k]^=1;return push(k,l,r);}
	rint m=(l+r)>>1,ls=k<<1;
	Flip(ls,l,m),Flip(ls|1,m+1,r);
}
inline void Query(rint k,rint l,rint r) {//查询 即将有影响的标记下传
	push(k,l,r);if(l==r) return;
	rint m=(l+r)>>1,ls=k<<1;
	(pos<=m)?Query(ls,l,m):Query(ls|1,m+1,r);
}
inline void Update(rint k,rint l,rint r) {//暴力下传所有标记
	push(k,l,r);if(l==r) return;
	rint m=(l+r)>>1,ls=k<<1;
	Update(ls,l,m),Update(ls|1,m+1,r);
}
int main() {
	rint i,op;
	n=read(),T=read();
	for(i=1;i<=n;i++) b[i]=read();
	while(T--) {
		m=read(),K=read(),y=(1<<K)-1;//取反异或用
		while(m--) {
			op=read();
			if(op==3) pos=read(),Query(1,1,n),printf("%d\n",b[pos]);//下传标记后直接输出当前值
			else {
				L=read(),R=read();
				if(op==1) Modify(1,1,n);
				else Flip(1,1,n);
			}
		}Update(1,1,n);//暴力下传标记
	}
	return 0;
}
```

---

## 作者：__builtin_orz (赞：0)

蒟蒻不会标记永久化，想看标记永久化的可以跳过了。

好像就是一道线段树裸题。

~~虽然有两个标记，但相互不影响，不如线段树二，建议降绿。~~

建树，维护区间中两种标记，更换 $k$ 时下传所有标记，修改叶子结点。

难点可能在于二进制数翻转，可以参考十进制数的翻转。

具体见代码。


```cpp
#include<cstdio>
#include<utility>
#define _N_ 50004
#define int unsigned long long
int inv(int val,int k){//二进制数后k位取反
	return val=val^((1llu<<k)-1llu);
}
int rev(int val,int k){//二进制数后k位翻转
	int h=val&~((1llu<<k)-1llu);
	int l=0;
	for(int i=1llu,x=val;i<=k;i++,x>>=1llu)
		l=l<<1llu|x&1llu;
	val=h|l;
	return val;
}
int a[_N_];
struct Seg{//比较特别的一种线段树写法，不喜欢的可以只参考思想，然后自己实现。（虽然本来就应该这样）
	int l,r;//线段左右端点
	Seg *lc,*rc;//左右儿子指针
	int val;//值（只有叶子结点的值有意义）
	bool tag_inv,tag_rev;//取反标记与翻转标记
	Seg(int L,int R){//构造函数
		tag_inv=tag_rev=false;
		l=L,r=R;
		if(L==R){//叶子结点
			val=a[L];
			lc=rc=nullptr;
		}else{
			int M=(L+R)/2;
			lc=new Seg(L,M);
			rc=new Seg(M+1,R);
		}
	}
	void make_tag_inv(){tag_inv=!tag_inv;}//打上取反标记
	void make_tag_rev(){tag_rev=!tag_rev;}//打上翻转标记
    //上面两个函数有过度封装的嫌疑，但是在标记比较多的时候可以避免spread函数过长
	void spread(){//下放标记
		if(tag_inv){
			lc->make_tag_inv();
			rc->make_tag_inv();
			tag_inv=false;
		}
		if(tag_rev){
			lc->make_tag_rev();
			rc->make_tag_rev();
			tag_rev=false;
		}
	}
	bool in(int L,int R){//该区间是否在修改区间内
		return L<=l&&r<=R;
	}
	bool out(int L,int R){//该区间是否在修改区间内
		return R<l||r<L;
	}
	void modify_inv(int L,int R){//区间取反
		if(in(L,R))make_tag_inv();
		else if(!out(L,R)){
			spread();
			lc->modify_inv(L,R);
			rc->modify_inv(L,R);
		}
	}
	void modify_rev(int L,int R){//区间翻转
		if(in(L,R))make_tag_rev();
		else if(!out(L,R)){
			spread();
			lc->modify_rev(L,R);
			rc->modify_rev(L,R);
		}
	}
	std::pair<bool,bool> query(int id){//询问一个数的两个标记情况，这里导致主函数中的询问有点啰嗦，读者可自行改进
		if(l==r)return std::make_pair(tag_inv,tag_rev);
		spread();
		if(id<=lc->r)return lc->query(id);
		return rc->query(id);
	}
	void flat(int k){//下放所有标记
		if(l==r){
			if(tag_inv)val=inv(val,k);
			if(tag_rev)val=rev(val,k);
			tag_inv=tag_rev=false;
			a[l]=val;
		}else{
			spread();
			lc->flat(k);
			rc->flat(k);
		}
	}
};
signed main(){//主函数
//读入
	int n,t;
	scanf("%llu%llu",&n,&t);
	for(int i=1llu;i<=n;i++)
		scanf("%llu",a+i);
//建树
	Seg* root=new Seg(1llu,n);
	while(t--){
		int m,k;
		scanf("%llu%llu",&m,&k);
		while(m--){
			int op;
			scanf("%llu",&op);
			if(op==3){//询问
				int id;
				scanf("%llu",&id);
				int val=a[id];
				std::pair<bool,bool>state=root->query(id);
				if(state.first)val=inv(val,k);
				if(state.second)val=rev(val,k);
				printf("%llu\n",val);
			}else{//修改
				int l,r;
				scanf("%llu%llu",&l,&r);
				if(op==1)root->modify_inv(l,r);
				if(op==2)root->modify_rev(l,r);
			}
		}
		root->flat(k);//记得下放（有的人以为多测要清空）
	}
	return 0;
}
```

---

