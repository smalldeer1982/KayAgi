# [POI 2008] KLO-Building blocks

## 题目描述

有 $n$ 柱砖，每柱砖有一个高度，我们现在希望有连续 $k$ 柱的高度是一样的。

你可以选择以下两个动作：

1. 从某柱砖的顶端拿一块砖出来,丢掉不要了。
2. 从仓库中拿出一块砖，放到某一柱，仓库是无限大的。

现在希望用最小次数的动作完成任务，除此之外你还要求输出结束状态时，每柱砖的高度。

## 说明/提示

本题 SPJ 的提示说明（按照 SPJ 判断顺序给出）：

`Out of Range`：输出的数字不在答案可能的范围内。

`Wrong Solution`：输出方案中不包含连续 $k$ 个相同高度的柱。

`Wrong Result`：提交的程序的步数和输出方案的步数不相等。

`Expected cost = a,found cost = b`：期望步数为 $a$，程序的步数为 $b$。

`OK!Correct Answer!`：答案正确。

## 样例 #1

### 输入

```
5 3
3
9
2
3
1```

### 输出

```
2
3
9
2
2
2```

# 题解

## 作者：communist (赞：22)

容易想到，我们可以枚举所有长度为$k$的区间，算出把这段区间全部变成一个值的代价，对于所有区间取最小值即可

### 1，把这段区间变成几

可能能够猜出变成中位数，别人都是显然，只有我证了证（太弱了），给出一个简单的证明

对于一个序列$S$，设它的中位数为$x$

设序列中有$a$个数小于$x$，$b$个数大于$x$，$c$个数等于$x$

设将这段区间变为$x$的代价为$W$

考虑把这段区间变为$x+1$，新代价为$W+a+c-b$，因为

$$a+c>=k/2\text{（中位数嘛）}$$

$$a+b+c=k$$

$$a+c>=b$$

，所以新代价大于等于原代价

变为$x-1$同理

考虑两个中位数不同，选哪个

设序列中有$c$个数等于较小中位数$x$，较大中位数为$y$

考虑上式，两个中位数不同，对于满足$x+tmp<=y$，$a,b,c$是不变的，$a+c=b=k/2$，新代价等于旧代价

这样，我们知道了不仅两个中位数代价相同，而且两个中位数之间所有数代价相同

### 2，具体求代价

序列和与中位数乘序列长度作差？

直接作差不行，对于大于等于中位数的数求和减去中位数乘它们的个数

对于小于中位数的数，中位数乘它们的个数减去它们的和，两项求和即可

选择一个支持这些操作（中位数，小于和，插入删除）的数据结构吧，我选择了主席树

然后就是暴力打码了，不解释了

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1e5+10,maxv=1e6+1;
struct tree{
    int v,ls,rs,sum;
}a[25*maxv];
int n,k,rt[maxn],cnt,v[maxn],ans=1e15,p,all,ave;
void insert(int pre,int cur,int p,int l,int r)
{
    if(l==r)
    {
        a[cur].v=a[pre].v+1;
        a[cur].sum=a[pre].sum+l;
        return;
    }
    int m=l+r>>1;
    if(p<=m)
    {
        a[cur].ls=++cnt;
        a[cur].rs=a[pre].rs;
        insert(a[pre].ls,a[cur].ls,p,l,m);
    }
    else
    {
        a[cur].rs=++cnt;
        a[cur].ls=a[pre].ls;
        insert(a[pre].rs,a[cur].rs,p,m+1,r);
    }
    a[cur].v=a[a[cur].ls].v+a[a[cur].rs].v;
    a[cur].sum=a[a[cur].ls].sum+a[a[cur].rs].sum;
}
int kth(int x,int y,int k,int l,int r)
{
    if(l==r)
        return l;
    int m=l+r>>1,num=a[a[y].ls].v-a[a[x].ls].v;
    if(num>=k)
        return kth(a[x].ls,a[y].ls,k,l,m);
    else
        return kth(a[x].rs,a[y].rs,k-num,m+1,r);
}
int sum(int x,int y,int k,int l,int r)
{
    if(l==r)
        return min(k,a[y].v-a[x].v)*l;
	int m=l+r>>1,num=a[a[y].ls].v-a[a[x].ls].v;
	//printf("%d %d %d\n",m,num,k);
    if(num>=k)
    	return sum(a[x].ls,a[y].ls,k,l,m);
    else
        return a[a[y].ls].sum-a[a[x].ls].sum+sum(a[x].rs,a[y].rs,k-num,m+1,r);
}
signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<k;i++)
    {
    	scanf("%lld",&v[i]);
        rt[i]=++cnt,all+=v[i];
        insert(rt[i-1],rt[i],v[i],0,1e6);
	}
    for(int i=k;i<=n;i++)
    {
        scanf("%lld",&v[i]);
        rt[i]=++cnt,all+=v[i]-v[i-k];
        insert(rt[i-1],rt[i],v[i],0,1e6);
        int pos=k+1>>1,tmp=kth(rt[i-k],rt[i],pos,0,1e6),res=sum(rt[i-k],rt[i],pos,0,1e6);
        res=all-2*res-(k-pos)*tmp+pos*tmp;
        if(res<ans)
        {
        	ans=res;
        	p=i,ave=tmp;
		}
    }
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++)
    	if(p<i+k&&p>=i)
    		printf("%lld\n",ave);
    	else
    		printf("%lld\n",v[i]);
    return 0;
}
```

---

## 作者：kczno1 (赞：13)

枚举要求最终一样的长度为$k$的区间$[l,r]$

则需要选择一个$x$，最小化$sigma_{i=l}^{r} |x-a[i]|$。
显然$x$要取中位数。


那么我们需要支持插入、删除、查询$k$大、求$<x$的数的和、求$>x$的数的和。

$zkw$线段树即可。

时间$O(nlogn)$

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
const int N=1e5+5,U=1e6+5;
int n,k,a[N],dy[U],ndy[N];
int half;
namespace ZKW
{
#define cl (i*2)
#define cr (cl+1)
ll s[N*3];
int sz[N*3],d;
void init(int n)
{
    d=1;while(d<n)d<<=1;d-=1;
}
void add(int x,int w)
{
    int i=dy[x]+d;
    while(i){sz[i]+=w;s[i]+=w*x;i>>=1;}
}
int m;
ll get()
{
    int i=1;
    int x=half;
    while(i<=d)
    if(x<=sz[cl])i=cl;
    else {x-=sz[cl];i=cr;}
    m=ndy[i-d];
    ll ans=(ll)m*((half-x)-(k-(half-x+sz[i])));
    while(i>1)
    {
        if(i&1)ans-=s[i-1];
        else ans+=s[i+1];
        i>>=1;
    }
    return ans;
}
};

int main()
{
    freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    n=read();k=read();
    rep(i,1,n)dy[a[i]=read()]=1;
    
    rep(i,1,U-1)dy[i]+=dy[i-1];
    ZKW::init(dy[U-1]);
    rep(i,1,n)ndy[dy[a[i]]]=a[i];
    
    rep(i,1,k)ZKW::add(a[i],1);
    half=k+1>>1;
    ll ans=ZKW::get();int ansm=ZKW::m,ansi=k;
    rep(i,k+1,n)
    {
        ZKW::add(a[i-k],-1);ZKW::add(a[i],1);
        ll now=ZKW::get();
        if(now<ans)
        {
            ans=now;ansm=ZKW::m;ansi=i;
        }
    }
    printf("%lld\n",ans);
    rep(i,ansi-k+1,ansi)a[i]=ansm;
    rep(i,1,n)printf("%d\n",a[i]);
}
```

---

## 作者：skydogli (赞：10)

这题怎么人均$fhq$啊，让$STL$选手情何以堪？

于是就来一发$priority$_$queue$~~+map~~的题解吧（突然发现map好慢啊）。

思路上面几位都说得比较清晰了，就是动态维护中位数，然后每次求最小代价，当时我脑袋一热，就想到了对顶堆，就是定义1个小根堆和1个大根堆，每次判断当前的数如果小于大根堆顶，就加入大根堆，否则加入小根堆，这样的话大根堆里的所有的数都比小根堆里的数小了，维护2个堆的大小相差不超过1后，就可以很容易取出中位数了。于是码码码之后发现：
### 好像要支持删除啊...
不过还有办法，支持搞出删除的堆的套路有2种（~~pb_ds的走开~~）：

一是把删除的数塞到另一个堆里面，如果2个堆顶相同，就同时删除（注意必须**都是**小根堆或大根堆）

第二是把数直接放入$map$中，**每次取出时要特判**。

本来本蒟蒻用的是$map$，结果不开$O_2$勇夺最优解倒数第二，实在是不敢看，所以改成了第一种方法。因为对顶堆是一个大根堆一个小根堆，所以删除的堆也要2个。

然后是计算代价的部分了，我们因为是计算绝对值，所以我们是不能把区间的数加起来再减去中位数乘区间数的。但是也好办，我们只要统计大根堆中的数的和$sum_1$,数的个数$size_1$以及小根堆的数的和$sum_2$,数的个数$size_2$,那么代价为：
$$Cost=mid*size_1-sum_1+sum_2-mid*size_2$$
原因也很好理解，因为大根堆中的数都小于等于中位数，所以可以一起加减，小根堆的数都大于等于中位数，所以同理。

### 代码（开$O_2$后跑到了最优解$Rank1$)：

```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define int long long
//答案可能会爆int
inline void read(int &x){
    x=0;int fh=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')fh=-1; c=getchar();}
    while('0'<=c&&c<='9'){
        x=x*10+c-48;
        c=getchar();
    }
    x*=fh;
}//快读
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
priority_queue<int>Q1,Q2,D1,D2;
//分别表示大根堆、小根堆、用于删除的2个堆
//因为本蒟蒻记不住pq的格式，就把Q2里的数全部加负号来当成小根堆用，所以下文也会加负号还原
int n,k,a[100005],siz1,siz2,sum1,sum2,ans,Begin,ANS;
//siz1和siz2表示在Q1和Q2中有多少数应被删除但还在堆里
void balance(){
    while(Q1.size()-siz1>Q2.size()-siz2+1){
        if(!D1.empty()&&D1.top()==Q1.top()){D1.pop();Q1.pop();siz1--;continue;}
        sum2+=Q1.top();
        sum1-=Q1.top();
        Q2.push(-Q1.top());
        Q1.pop();
    }
    while(Q1.size()-siz1<Q2.size()-siz2){
        if(!D2.empty()&&D2.top()==Q2.top()){D2.pop();Q2.pop();siz2--;continue;}
        sum1+=-Q2.top();
        sum2-=-Q2.top();
        Q1.push(-Q2.top());
        Q2.pop();
    }

}
//保持2个堆的平衡，为了方便，我们钦定大根堆数量大于等于小根堆数量，那么我们取中位数就可以在大根堆里取了
signed main(){
    ans=1e17;
    read(n);read(k);
    for(int i=1;i<=n;++i)read(a[i]);
    for(int i=1;i<=n;++i){
        if((!Q1.empty()&&a[i]>Q1.top())){Q2.push(-a[i]);sum2+=a[i];}
        else {Q1.push(a[i]);sum1+=a[i];}
        balance();
        if(i>=k){
            int mid=-1;
            while(mid==-1){
                balance();
                if(Q1.size()-siz1>=Q2.size()-siz2){
                    if(!D1.empty()&&D1.top()==Q1.top()){D1.pop();Q1.pop();siz1--;}
                        else mid=Q1.top();
                }
            }
            //找中位数
            if(ans>(Q1.size()-siz1)*mid-sum1+sum2-(Q2.size()-siz2 )*mid){
                ans=(Q1.size()-siz1)*mid-sum1+sum2-(Q2.size()-siz2 )*mid;
                Begin=i-k+1;
                ANS=mid;
            }
            //求最小代价
            if(Q1.top()>=a[i-k+1]){
                siz1++;
                D1.push(a[i-k+1]);
                sum1-=a[i-k+1];
            }
            else{
                siz2++;
                D2.push(-a[i-k+1]);
                sum2-=a[i-k+1];
            }
            //删除
        }
    }
    printf("%lld\n",ans);
    for(int i=1;i<=n;++i)if(i>=Begin&&i<Begin+k)printf("%lld\n",ANS);
    else printf("%lld\n",a[i]);
    return 0;
}



```

---

## 作者：CodyTheWolf (赞：6)

## 解法：$FHQ_Treap$
## 当然也不是裸的Treap $QwQ$
## 先行提醒：记得开longlong $QwQ$
------------
## 根据题意，很想出步骤：
-	1.枚举一个**长度为k**的区间（从$[1,k]$到$[n-k+1,n]$)

-	2.计算中位数。

-	3.将**中位数左边**的数分别加到中位数，**右边的数**分别减到中位数

	当然，这个**不需要模拟**，纯计算就好，设左边的元素有$l$个，右边有$r$个,左边的元素为$Al$，右边的元素为$Ar$（**左右都不包括中位数**）,中位数为$m$，那么这个区间对应的答案就是：
    
    ### $ans=(l*m-\sum Al)+(\sum Ar-r*m)$
    
    计算两边**需要补上**和**丢掉**的砖块，这个式子应该很好理解的 $QwQ$

------------
## 解法很多：对顶堆，线段树和平衡树……
## 这里讲讲单棵平衡树怎么做
-	其实非常简单，只需要加入一个sum数组**记录子树和**就好，**size更新的时候sum跟着更新**，很简单：

	### $sum[now]=sum[lson]+sum[rson]+val[now]$;

-	每次**固定平衡树有k个元素**，也就是我们需要枚举的区间，移动区间时，我们在Treap上**删掉最左的数**，加入**最右边+1**（也就是待加入区间）的数。

-	中位数用求**排名的方法**很好做到，注意如果**k为奇数偶数**计算中位数的区别（小学知识，不知道就自己百度吧QwQ）

-	知道了中位数，我们把堆**分成x,y,z三个堆**，**使（x堆所有元素）<mid**，（**y堆所有元素）==mid**，**（z堆所有元素）>mid**，代码如下：

	### $split(root,mid,x,z),split(x,mid-1,x,y);$

-	因为我们有**sum和size数组**，很容易能得到**左右的元素个数**分别是$size[x],size[z]$，**左右元素**和分别是$sum[x],sum[z]$。查询完记得合并堆。再按照上面算ans的式子算一下，和最终答案取min就好。

-	计算完如果比最终答案小的话**记得记录区间$[l,r]$和中位数$m$**，最后输出最后状态的时候**直接把原数组输出**，到$[l,r]$的时候记得**全部换成$m$**即可。

------------
## CODE
```cpp
// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
const long long maxn=2e5+5,INF=0x7fffffffffffff;
long long a[maxn];
long long n,k;
long long l,r;
long long ans_mid,ans_l,ans_r,ans=INF;

struct Fhq_Treap
{
	long long l[maxn],r[maxn],sz[maxn],val[maxn],heap[maxn],sum[maxn];
	long long num,root,x,y,z;
	
	inline void update(long long pst) 
	{
		sz[pst]=sz[l[pst]]+sz[r[pst]]+1;
		sum[pst]=sum[l[pst]]+sum[r[pst]]+val[pst];
		return;
	}
	
	inline long long new_node(long long key) 
	{
		sz[++num]=1,sum[num]=val[num]=key,heap[num]=rand();
		return num;
	}
	
	inline void split(long long pst,long long key,long long &x,long long &y)
	{
		if(!pst)
		{
			x=y=0;
			return;
		}
		if(val[pst]<=key)
			x=pst,split(r[pst],key,r[pst],y);
		else 
			y=pst,split(l[pst],key,x,l[pst]);
		update(pst);
		return;
	}
	
	inline long long merge(long long x,long long y)
	{
		if(!x||!y)
			return x+y;
		if(heap[x]<heap[y])
		{
			r[x]=merge(r[x],y),update(x);
			return x;
		}	
		else
		{
			l[y]=merge(x,l[y]),update(y);
			return y;
		}	
	}
	
	inline long long kth(long long pst,long long rak)
	{
		if(rak<=sz[l[pst]])
			return kth(l[pst],rak);
		if(rak==sz[l[pst]]+1)
			return val[pst];
		return kth(r[pst],rak-sz[l[pst]]-1);
	}
	
	inline void add(long long key)
	{
		split(root,key,x,y);
		root=merge(x,merge(new_node(key),y));
		return;
	}
	
	inline void del(long long key)
	{
		split(root,key,x,z),split(x,key-1,x,y);
		y=merge(l[y],r[y]);
		root=merge(x,merge(y,z));
		return;
	}
	
	inline long long query(long long key)
	{
		split(root,key,x,z),split(x,key-1,x,y);
		long long sz1=sz[x],sz2=sz[z];
		long long ans1=sum[x],ans2=sum[z];
		root=merge(x,merge(y,z));
		long long l=sz1*key-ans1,r=ans2-sz2*key;
		return l+r;
	}
	
}FT;

signed main(void)
{
	scanf("%lld %lld",&n,&k);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&a[i]);
		
	for(long long i=0;i<k;i++)
		FT.add(a[i]);
	
	l=0,r=k-1;
	for(long long i=k,mid;i<=n;i++)
	{
		l++,r++;
		FT.del(a[l-1]),FT.add(a[r]);
		if(k&1)
			mid=FT.kth(FT.root,(k>>1)+1);
		else
			mid=(FT.kth(FT.root,k>>1)+FT.kth(FT.root,(k>>1)+1))>>1;
		long long temp=FT.query(mid);
		if(temp<ans)
			ans=temp,ans_mid=mid,ans_l=l,ans_r=r;
	}
	
	printf("%lld\n",ans);
	for(long long i=1;i<ans_l;i++)
		printf("%lld\n",a[i]);
	for(long long i=ans_l;i<=ans_r;i++)
		printf("%lld\n",ans_mid);
	for(long long i=ans_r+1;i<=n;i++)
		printf("%lld\n",a[i]);
		
	return 0;
}
```
------------
### 小广告：自己的模板库，有各种~~标准~~模板，想学什么都可以来看看呀qwq
### [专供神犇点击的链接](https://yu123123.blog.luogu.org/mu-qian-di-mu-ban-ku)


---

## 作者：Iscream2001 (赞：5)

楼下孔爷的题解太强啦。。居然只用线段树就秒了此题%%%

这里提供一个不同的思路。。维护一个动态的中位数。。用平衡树的做法就很显然了。。直接暴力插入，删除，查询中位数就好了。。

记得要开longlong

代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<vector>
#include<map>
#define N 100050
#define mod 100003
#define ept 1e-10
#define LL long long
#define inf 2000000000
using namespace std;
inline int Read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,K,hash=1,siz=0,rt;
int pjs,L,R;
LL ans,Lsum,Rsum;
int a[N];
struct date{
    int l,r,v,w,siz,rnd;
    LL sum;
}tr[N];
int Hash(){
    hash=hash*1009%mod;return hash;
}
void lturn(int &k){
    int t=tr[k].r;tr[k].r=tr[t].l;tr[t].l=k;tr[t].siz=tr[k].siz;
    tr[k].siz=tr[tr[k].l].siz+tr[tr[k].r].siz+tr[k].w;
    tr[t].sum=tr[k].sum;tr[k].sum=tr[tr[k].l].sum+tr[tr[k].r].sum+(LL)tr[k].w*tr[k].v;
    k=t;
}
void rturn(int &k){
    int t=tr[k].l;tr[k].l=tr[t].r;tr[t].r=k;tr[t].siz=tr[k].siz;
    tr[k].siz=tr[tr[k].l].siz+tr[tr[k].r].siz+tr[k].w;
    tr[t].sum=tr[k].sum;tr[k].sum=tr[tr[k].l].sum+tr[tr[k].r].sum+(LL)tr[k].w*tr[k].v;
    k=t;
}
void insert(int &k,int x){
    if(!k){k=++siz;tr[k].siz=tr[k].w=1;tr[k].sum=tr[k].v=x;tr[k].rnd=Hash();return;}
    tr[k].siz++;tr[k].sum+=(LL)x;
    if(tr[k].v==x) tr[k].w++;
    else if(tr[k].v<x){
        insert(tr[k].r,x);
        if(tr[tr[k].r].rnd<tr[k].rnd) lturn(k);
    }
    else{
        insert(tr[k].l,x);
        if(tr[tr[k].l].rnd<tr[k].rnd) rturn(k);
    }
}
void del(int &k,int x){
    if(!k)return;
    if(tr[k].v==x){
        if(tr[k].w>1) {tr[k].w--;tr[k].sum-=(LL)x;tr[k].siz--;return;}
        if(tr[k].l*tr[k].r==0) k=tr[k].l+tr[k].r;
        else if(tr[tr[k].l].rnd<tr[tr[k].r].rnd){rturn(k);del(k,x);}
        else {lturn(k);del(k,x);}
    }
    else if(x>tr[k].v){tr[k].sum-=(LL)x;tr[k].siz--;del(tr[k].r,x);}
    else {tr[k].sum-=(LL)x;tr[k].siz--;del(tr[k].l,x);}
}
int query_num(int k,int x){
    if(!k)return 0;
    if(x<=tr[tr[k].l].siz) {
        Rsum+=(LL)tr[k].v*(LL)tr[k].w+tr[tr[k].r].sum;
        return query_num(tr[k].l,x);
    }
    else if(x>tr[tr[k].l].siz+tr[k].w){
        Lsum+=(LL)tr[k].v*(LL)tr[k].w+tr[tr[k].l].sum;
        return query_num(tr[k].r,x-tr[tr[k].l].siz-tr[k].w);
    }
    else {
        Lsum+=tr[tr[k].l].sum+(LL)(x-tr[tr[k].l].siz-1)*(LL)tr[k].v;
        Rsum+=tr[tr[k].r].sum+(LL)(tr[tr[k].l].siz+tr[k].w-x)*(LL)tr[k].v;
        return tr[k].v;
    }
}
int main(){
    n=Read();K=Read();
    for(int i=1;i<=n;i++)a[i]=Read();
    for(int i=1;i<=K;i++) insert(rt,a[i]);
    int kk=K+1>>1;
    Lsum=Rsum=0;
    pjs=query_num(rt,kk);L=1;R=K;
    ans=(LL)((LL)(kk-1)*(LL)pjs-Lsum+Rsum-(LL)(K-kk)*(LL)pjs);
    for(int i=K+1;i<=n;i++){
        insert(rt,a[i]);del(rt,a[i-K]);
        Lsum=Rsum=0;
        int j=query_num(rt,kk);LL S=(LL)((LL)(kk-1)*(LL)j-Lsum+Rsum-(LL)(K-kk)*(LL)j);
        if(S<ans){ans=S;pjs=j;L=i-K+1;R=i;}
    }
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++){
        if(i>=L&&i<=R) printf("%d\n",pjs);
        else printf("%d\n",a[i]);
    }
    return 0;
}
```

---

## 作者：devout (赞：2)

来一发$splay$的题解

首先我们要枚举区间$[l,r]$，取让这个区间变成一样的的步数的最小值。

那么这个区间变成一样的变成多少呢？

我们可以感性证明——他是中位数

那么我们需要设计一种数据结构，他可以访问静态区间第K大，我们想到了主席树。

但是既然我是搜着$splay$的标签进来的，那就打个$splay$吧

每次都让$splay$中的数量为k，向右移的时候插入删除就可以了

注意访问左右子树的大小的时候要注意顺序，先加再改变u的值

```cpp
# define int long long

int n,k,p,ans,ls,rs;
int a[N];
int fa[N],son[N][2],siz[N],key[N],recy[N],sum[N];
int rt,sz;

void clear(int x){
	fa[x]=son[x][0]=son[x][1]=siz[x]=key[x]=recy[x]=sum[x]=0;	
}

bool locate(int x){
	return son[fa[x]][1]==x;	
}

void update(int x){
	if(x){
		siz[x]=recy[x];
		sum[x]=key[x]*recy[x];
		if(son[x][0])siz[x]+=siz[son[x][0]],sum[x]+=sum[son[x][0]];
		if(son[x][1])siz[x]+=siz[son[x][1]],sum[x]+=sum[son[x][1]];
	}
}

void rotate(int x){
	int faz=fa[x],grand=fa[faz],side=locate(x);
	son[faz][side]=son[x][side^1],fa[son[faz][side]]=faz;
	son[x][side^1]=faz,fa[faz]=x;
	fa[x]=grand;
	if(grand)son[grand][son[grand][1]==faz]=x;
	update(faz),update(x);	
}

void splay(int x){
	for(int faz;faz=fa[x];rotate(x))
		if(fa[faz])
			rotate(locate(x)==locate(faz)?faz:x);
	rt=x;	
}

void find(int x){
	int u=rt;
	if(!u)return;
	while(son[u][x>key[u]]&&key[u]!=x)u=son[u][x>key[u]];
	splay(u);
}

int pre(){
	int x=son[rt][0];
	while(son[x][1])x=son[x][1];
	return x;		
}

void insert(int x){
	if(!rt){
		sz++;
		fa[sz]=son[sz][0]=son[sz][1]=0;
		siz[sz]=recy[sz]=1;
		key[sz]=sum[sz]=x;
		rt=sz;
		return;
	}
	int u=rt,faz=0;
	while(1){
		if(x==key[u]){
			recy[u]++;
			sum[u]+=key[u];
			update(u),update(faz);
			splay(u);
			return;	
		}
		faz=u,u=son[u][x>key[u]];
		if(!u){
			sz++;
			son[sz][0]=son[sz][1]=0;
			siz[sz]=recy[sz]=1;
			key[sz]=sum[sz]=x;
			fa[sz]=faz;
			son[faz][x>key[faz]]=sz;
			update(faz);
			splay(sz);
			return;	
		}
	}
}

void erase(int x){
	find(x);
	if(recy[rt]>1){
		recy[rt]--;
		sum[rt]-=key[rt];
		update(rt);
		return;
	}
	if(!son[rt][0]&&!son[rt][1]){
		clear(rt);
		rt=0;
		return;	
	}
	if(!son[rt][0]){
		int old=rt;
		rt=son[rt][1];
		fa[rt]=0;
		clear(old);
		return;	
	}
	if(!son[rt][1]){
		int old=rt;
		rt=son[rt][0];
		fa[rt]=0;
		clear(old);
		return;	
	}
	int old=rt,lft=pre();
	splay(lft);
	son[rt][1]=son[old][1];
	fa[son[old][1]]=rt;
	clear(old);
	update(rt);
}

int kth(int x){
	int u=rt;
	while(1){
		if(son[u][0]&&x<=siz[son[u][0]]){
			rs+=recy[u]*key[u]+sum[son[u][1]];
			u=son[u][0];
		}
		else if(x>siz[son[u][0]]+recy[u]){
			ls+=recy[u]*key[u]+sum[son[u][0]];
			x-=siz[son[u][0]]+recy[u];
			u=son[u][1];//这里，我开始的时候把u=son[u][1]写到上面去了导致出错
		}
		else{
			ls+=sum[son[u][0]]+key[u]*(x-siz[son[u][0]]-1);
			rs+=sum[son[u][1]]+key[u]*(siz[son[u][0]]+recy[u]-x);
			return key[u];	
		}
	}
}

signed main()
{
	read(n),read(k);
	Rep(i,1,n)read(a[i]);
	p=k+1>>1;
	Rep(i,1,k)insert(a[i]);
	int l=1,r=k;
	ls=0,rs=0;
	int mid=kth(p);
	ans=(p-1)*mid-ls+rs-(k-p)*mid;
//	printf("%d %d %d %d\n",ls,rs,mid,ans);
	Rep(i,k+1,n){
//		Rep(i,1,n)printf("%d ",sum[i]);
//		puts("");
		insert(a[i]),erase(a[i-k]);
		ls=0,rs=0;
		int newmid=kth(p);
		int newans=(p-1)*newmid-ls+rs-(k-p)*newmid;

//		printf("%d %d %d %d\n",ls,rs,newmid,newans);
		if(newans<ans){
			ans=newans;
			mid=newmid;
			l=i-k+1,r=i;
		}
	}
	printf("%lld\n",ans);
	Rep(i,1,n)
		if(i>=l&&i<=r)printf("%d\n",mid);
		else printf("%d\n",a[i]);
	return 0;
}
```


---

## 作者：FarmerJohn (赞：2)

如果我们已知是在哪一个区间 显然选取的中间点是中位数 


而计算答案时 把后一半求和-前一半求和即可 

因为k是固定的 所以一共O(n)个区间 考虑两个区间端点 每次右移

1.加入一个数 

2.删除一个数 

3.维护中位数并计算 

开两个set表示有序的左边一半和右边一半 新加入的一个数字和中位数比较 然后判一下加入哪一半 删除同理

---

## 作者：夏色祭 (赞：2)

思路孔爷讲的很清楚了。

我来补一发fhq treap的代码。

```
//by zykykyk
#include<cstdio>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<string>
#include<set>
#include<vector>
#include<queue>
#include<map>
#define rg register
#define il inline
#define vd void
#define ll long long
#define N 100010
#define For(i,x,y) for (int i=(x);i<=(y);i++)
#define Dow(i,x,y) for (int i=(x);i>=(y);i--)
#define cross(i,k) for (int i=first[k];i;i=last[i])
using namespace std;
il int read(){
    int x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
il vd print(ll x){
    if (x<0) putchar('-'),x=-x;
    if (x>=10) print(x/10),putchar(x%10+'0');
        else putchar(x+'0');
}
int n,m,x,y,z,mid,ans_l,ans_r,ans_mid,a[N];
ll ans;

int root,tot,pri[N],size[N],son[N][2];
ll sum[N],val[N];
il int make_node(int v){
	size[++tot]=1;
	pri[tot]=rand();
	sum[tot]=val[tot]=v;
	return tot;
}
il vd pushup(int u){
	size[u]=size[son[u][0]]+size[son[u][1]]+1;
	sum[u]=sum[son[u][0]]+sum[son[u][1]]+val[u];
}
il vd Split(int u,int v,int &x,int &y){
	if (!u) x=y=0;
	else {
		if (val[u]<=v) x=u,Split(son[u][1],v,son[u][1],y);
		else y=u,Split(son[u][0],v,x,son[u][0]);
		pushup(u);
	}
}
il int Merge(int x,int y){
	if (!x||!y) return x+y;
	if (pri[x]<pri[y]){
		son[x][1]=Merge(son[x][1],y);
		pushup(x);
		return x;
	}
	else {
		son[y][0]=Merge(x,son[y][0]);
		pushup(y);
		return y;
	}
}
il int Kth(int u,int k){
	while (2333){
		if (size[son[u][0]]+1<k) k-=size[son[u][0]]+1,u=son[u][1];
		else if (size[son[u][0]]>=k) u=son[u][0];
		else return u;
	}
}
il vd insert(int v){
	Split(root,v,x,y);
	root=Merge(Merge(x,make_node(v)),y);
}
il vd Delete(int v){
	Split(root,v,x,z),Split(x,v-1,x,y);
	y=Merge(son[y][0],son[y][1]);
	root=Merge(Merge(x,y),z);
}
int main(){
	srand(time(0));
	n=read(),m=read();
	For(i,1,n) a[i]=read();
	ans=2333333333333333;
	For(i,1,n){
		insert(a[i]);
		if (i<m) continue;
		if (i!=m) Delete(a[i-m]);
		mid=val[Kth(root,(m>>1)+1)];
		Split(root,mid,x,z),Split(x,mid-1,x,y);
		ll Sum=1ll*mid*size[x]-sum[x]+sum[z]-1ll*mid*size[z];
		if (Sum<ans){
			ans=Sum;
			ans_l=i-m+1,ans_r=i,ans_mid=mid;
		}
		root=Merge(Merge(x,y),z);
	}
	print(ans),putchar('\n');
	For(i,1,n)
		if (i>=ans_l&&i<=ans_r) print(ans_mid),putchar('\n');
		else print(a[i]),putchar('\n');
}
```

---

## 作者：梧桐灯 (赞：1)

这里提供一个树状数组的做法（[双倍经验](https://www.luogu.org/problem/P2263)）

由于我先写的是链接的题，那题要用离散化，所以此题我直接把代码搬了过来没有改，但本题由于高度不大无需离散化。

考虑一个有序数列的中位数是第x个数，共有n个数

那么移动次数为（中位数-a1) + (中位数-a2) + …… + （中位数-ax） + (ax+1 - 中位数) + …… + （an - 中位数）

公式长这样：

$\sum_{i=1}^{x-1} ax-ai + \sum_{i=x+1}^{n} an-ax$

如果我们已经知道了中位数，那么上面的求和可以用树状数组的前缀和来维护，那么怎么求中位数呢？

可以考虑每一个数对于长度的贡献是1，那么第(k + 1 >> 1)的数就是中位数，这样我们可以在树状数组中二分找出第一个长度大于等于（k + 1 >> 1）的。

（大于等于是因为有些数相等可能导致长度有断裂）

代码：

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

template <typename T>
inline void read (T& s) {
	s = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c & 15), c = getchar ();
	return ;
}

int qu[53];
template <typename T>
inline void write (T s) {
    if (!s) {putchar ('0'); return ;}
    if (s < 0) {
        putchar ('-');
        s = -s;
    }
    int v = 0;
    while (s) qu[++v] = s % 10, s /= 10;
    while (v) putchar (qu[v--] + '0');
    return ;
}

const int N = 100003;
int n, k, m, pos[N], num[N], lastl, lasth;
int h[N], a[N];
ll sum[N], ans = (1ll << 62);

inline void add (int x, ll y, int z) {
	for (; x <= m; x += x & (x ^ x - 1)) {
		sum[x] += y;
		num[x] += z;
	}
	return ;
}

inline int ask1 (int x) {int ans = 0; for (; x; x &= x - 1) ans += num[x]; return ans;}
inline ll ask2 (int x) {ll ans = 0; for (; x; x &= x - 1) ans += sum[x]; return ans;}

inline void work (int sx) {
	int L = 1, R = m, mid, x = (1 << 30), t, e = (k + 1 >> 1), now;
	while (L <= R) {
		mid = L + R >> 1;
		t = ask1 (mid);
		if (t >= e) {
			x = min (x, mid);
			now = t;
			R = mid - 1;
		} //二分查找第一个长度大于等于(k+1>>1)的
		else L = mid + 1;
	}
	ll zh = a[x]; //zh是中位数
	ll tot = zh * now - ask2 (x) + (ask2 (m) - ask2 (x) - zh * (k - now)); //now表示中位数的在数组中的排名
    if (tot < ans) {
        ans = tot;
        lastl = sx;
        lasth = zh;
    }
	return ;
}

int main () {
	read (n), read (k);
	int i, j; for (i = 1; i <= n; ++i) {
		read (h[i]);
		a[i] = h[i];
	}
	sort (a + 1, a + 1 + n);
	m = unique (a + 1, a + 1 + n) - a - 1;
	for (i = 1; i <= n; ++i) pos[i] = lower_bound (a + 1, a + 1 + m, h[i]) - a; //请无视离散化操作
	for (i = 1; i < k; ++i) add (pos[i], h[i], 1);
	for (i = 1; i + k - 1 <= n; ++i) {
		j = i + k - 1;
		add (pos[j], h[j], 1); //第i~到i+k-1个数入树状数组
		work (i);
		add (pos[i], -h[i], -1); //第i个数出去
	}
	cout << ans << '\n';
    for (i = 1; i < lastl; ++i) write (h[i]), putchar ('\n');
    for (i = lastl; i <= lastl + k - 1; ++i) write (lasth), putchar ('\n');
    for (i = lastl + k; i <= n; ++i) write (h[i]), putchar ('\n');
	return 0;
}

```


---

## 作者：G我就是菜G (赞：1)

## 本题 $FHQ\;Treap$ 写法

题目意思就是，给定 $n$ 个数字，可以将一个数加一或者减一，要最小的代价使得有 $m$ 个连续相同的数字

每次枚举一个区间，将这个区间的每个数都变成这个区间的中位数

证明如下：

**将这个区间的每个数都变成 $x$**

**令比 $x$ 小的数的个数为 $siz1$，比 $x$ 大的数的个数为 $siz2$**

**比 $x$ 小的数的和为 $add1$，比 $x$ 大的数的和为 $add2$**

**则代价为 $add3=add2-siz2\times x+x\times siz1-add1$**

**当 $x$ 为中位数的时候，有 $siz1=siz2$，则 $add3=add2-add1$，代价最小**

当 $m$ 为偶数的情况，由于我们要求的中位数为整数，为了避免麻烦（有些情况下要加上 $x$ 或减去 $x$），还是分别求出了 $siz1$ 和 $siz2$，用上述公式计算

### 代码如下

```cpp
#include <bits/stdc++.h>
#define int long long
#define random(x) rand()*100%x
#define INF 20040121
#define N 4000010
using namespace std;

int size[N],t[N],sum[N],heap[N],son[N][2],a[N];
int cnt,root,n,m,add1,add2,ans,x,k,x1,add3,siz1,siz2;

void add(int val){t[++cnt]=val,size[cnt]=1,sum[cnt]=val,heap[cnt]=random(INF);}

void update(int x)
{
    size[x]=size[son[x][0]]+size[son[x][1]]+1;
    if (t[x]!=INT_MAX) sum[x]=sum[son[x][0]]+sum[son[x][1]]+t[x];
    else sum[x]=sum[son[x][0]]+sum[son[x][1]];
}

void split(int now,int &a,int &b,int val)
{
    if (!now) {a=b=0;return;}
    if (t[now]<=val) a=now,split(son[now][1],son[a][1],b,val);
    else b=now,split(son[now][0],a,son[b][0],val);
    update(now);
}

void merge(int &now,int a,int b)
{
    if (a==0 || b==0) {now=a+b;return;}
    if (heap[a]<heap[b]) now=a,merge(son[now][1],son[a][1],b);
    else now=b,merge(son[now][0],a,son[b][0]);
    update(now);
}

void insert(int val)
{
    int x=0,y=0;
    add(val);
    int o=cnt;
    split(root,x,y,val);
    merge(x,x,o);merge(root,x,y);
}

void del(int val)
{
    int x=0,y=0,o=0;
    split(root,x,y,val);split(x,x,o,val-1);
    merge(o,son[o][0],son[o][1]);
    merge(x,x,o);merge(root,x,y);
}

int findnum(int now,int x)
{
    if (size[son[now][0]]+1==x) return t[now];
    if (size[son[now][0]]>=x) return findnum(son[now][0],x);
    else return findnum(son[now][1],x-size[son[now][0]]-1);
}

void query1(int now,int val)
{
    int x=0,y=0;
    split(root,x,y,val-1);  \\按 val-1 劈成两棵树，以 x 为根子树的 size 值就是siz1，其 sum 值就是add1
    add1=sum[x];
    siz1=size[x];
    merge(root,x,y);
}

void query2(int now,int val)
{
    int x=0,y=0;
    split(root,x,y,val);   \\同上
    add2=sum[y];
    siz2=size[y]-1;
    merge(root,x,y);
}

signed main()
{
    srand((int)(time(0)));
    scanf("%lld%lld",&n,&m);
    ans=100000000001ll;    \\由于这个初始值出锅，炸了好久
    add(INT_MAX);root=1;heap[root]=-INT_MAX;sum[root]=0;
    for (int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        insert(a[i]);
        if (i>m) del(a[i-m]);
        else if (i<m) continue;
        x=findnum(root,(m+1)/2);
        query1(root,x);query2(root,x);
        add3=add2-x*siz2+x*siz1-add1;
        if (add3<ans) ans=add3,k=i,x1=x;  \\用 k 记录区间的最后一个位置，方便求出修改后的数列
    }
    for (int i=k-m+1;i<=k;i++)
        a[i]=x1;
    printf("%lld\n",ans);
    for (int i=1;i<=n;i++)
        printf("%lld\n",a[i]);
    return 0;
}
```

---

## 作者：G_hz (赞：1)

本题解仅供参考，无法通过本题

由题意可知，这个题的题意就是把某段长度为k的数段改为bb，使得该段中abs（ai-bb）的和最大，我们想到了满足该性质的数是该段序列的中位数，由于需要维护某段连续区间的中位数，而作为蒟蒻又不会写主席树这样的高大上数据结构，因此写了一棵SBT，一边删除，一边插入，使得区间总保持在k个数。


代码如下：

```cpp
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<stdlib.h>
#include<algorithm>
#define min(a,b)(a<b?a:b)
#include<assert.h>
#define int long long
int li[1000010],s[1000000],b[1000000],ans=1e17+1;
typedef struct Node{
    Node *l,*r;
    int val,size,cnt,sum;
}SBT,*LE;
LE Null,root;
void L_Rotate(LE&k){
    LE tmp=k->r;
    k->r=tmp->l;
    tmp->l=k;
    tmp->size=k->size;
    tmp->sum=k->sum;
    k->size=k->l->size+k->r->size+k->cnt;
    k->sum=k->l->sum+k->r->sum+k->val*k->cnt;
    k=tmp;
}
void R_Rotate(LE&k){
    LE tmp=k->l;
    k->l=tmp->r;
    tmp->r=k;
    tmp->size=k->size;
    tmp->sum=k->sum;
    k->size=k->l->size+k->r->size+k->cnt;
    k->sum=k->l->sum+k->r->sum+k->cnt*k->val;
    k=tmp;
}
void Insert(LE&k,int val){
    if(k==Null){
        k=new Node;
        k->size=k->cnt=1;
        k->val=k->sum=val;
        k->l=k->r=Null;
        return;
    }
    k->size++;
    k->sum+=val;
    if(val<k->val){
        Insert(k->l,val);
        if(k->l->l->size>k->r->size)
            R_Rotate(k);
    }
    else
    if(val>k->val){
        Insert(k->r,val);
        if(k->r->r->size>k->l->size)
            L_Rotate(k);
    }
    else
    if(val==k->val){
        k->cnt++;
        return;
    }
}
void Delete(LE&k,int val,int cnt){
    k->sum-=val;
    if(k==Null)return;
    k->size-=cnt;
    if(k->val<val){
        Delete(k->r,val,cnt);
        return;
    }
    else
    if(k->val>val){
        Delete(k->l,val,cnt);
        return;
    }
    else
    if(k->val==val){
        k->cnt-=cnt;
        if(k->cnt)return;
        if(!k->cnt){
            if(k->l==Null){
                k=k->r;
            }
            else if(k->r==Null){
                k=k->l;
            }
            else{
            //    assert(Null != k);
                LE tmp=k->l;
                while(tmp->r!=Null)
                    tmp=tmp->r;
            k->val=tmp->val;
            k->cnt=tmp->cnt;
            Delete(k->l,k->val,k->cnt);
            }
        }
    }
}
int Query(LE k,int rank){
    //assert(k->l);
    if(k==Null)return 1;
    if(rank<=k->l->size)
        return Query(k->l,rank);
    if(rank<=k->l->size+k->cnt)
        return k->val;
    rank-=k->l->size+k->cnt;
    return Query(k->r,rank);
}
int Query_sum_1(LE k,int val){//da
//assert(k->l);
    if(val<k->val){
        return Query_sum_1(k->l,val)+k->val*k->cnt+k->r->sum;
    }
    if(val>k->val){
        return Query_sum_1(k->r,val);
    }
    if(val==k->val){
        return k->r->sum;
    }
}
int Query_sum_2(LE k,int val){//xiao
//assert(k->l);
    if(val<k->val){
        return Query_sum_2(k->l,val);
    }
    if(val>k->val){
        return Query_sum_2(k->r,val)+k->cnt*k->val+k->l->sum;
    }
    if(val==k->val){
        return k->l->sum;
    }
}
signed main()
{
    int n,k;
    Null=new Node;
    Null->size=Null->cnt=0;
    Null->sum=0;
    Null->val=-1;
    root=Null;
    //cin>>n>>k;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
        //cin>>li[i];
        scanf("%lld",&li[i]);
    }
    for(int i=1;i<=k;i++){
        Insert(root,li[i]);
    }
    int head=k,tail=0;
    int bb=k/2+1;
    while(head<=n){
        int cc=Query(root,bb);
        int aa=Query_sum_1(root,cc);
        int dd=Query_sum_2(root,cc);
        int mm=aa-(k-bb)*cc+(bb-1)*cc-dd;
        ans=min(ans,mm);
        Delete(root,li[++tail],1);
        Insert(root,li[++head]);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：GNAQ (赞：0)

怎么没有用主席树的。

首先我们考虑，这个问题就是区间上的中点问题。

$$\mathrm{cost} = \sum | \overline{x} - a_i |$$

然后事情就变得很简单了。

权值主席树 -> 查询区间第 $\mathrm{k}$ 大可以求得中点。

注意考虑区间长度是偶数的问题。。这个我们去取平均值就好了。

求出来位置之后我们在主席树上走一遍，对于不包含中点的区间我们直接可以算出贡献，包含的递归进去算就好了。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<iterator>
#include<queue>
#include<map>
#include<set>
#define ll long long
#define LCH PGT[inx].ch[0]
#define RCH PGT[inx].ch[1]
#define NLCH PGT[newx].ch[0]
#define NRCH PGT[newx].ch[1]
using namespace std;

struct Pre_Tree
{
    int ch[2];
    ll val,siz;
}PGT[1000010*22];
int tsiz=0,troo[1000010];
ll _val,lx,rx,_pos,kv;

ll n,K,seq[1000010];

void readx(ll& x)
{
    x=0; ll k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

void Upd(int inx,int& newx)
{
    newx=++tsiz;
    PGT[newx].val=PGT[inx].val+_val;
    PGT[newx].siz=PGT[inx].siz+1;
    if (lx==rx) return;
    
    NLCH=LCH; NRCH=RCH;
    int mid=(lx+rx)>>1;
    if (_val<=mid) { rx=mid; Upd(LCH,NLCH); }
    else { lx=mid+1; Upd(RCH,NRCH); }
}

ll k_th(int inx,int newx)
{
    if (lx==rx) return lx;
    kv=PGT[NLCH].siz-PGT[LCH].siz;
    int mid=(lx+rx)>>1;
    if (kv>=_val) { rx=mid; return k_th(LCH,NLCH); }
    else { _val-=kv; lx=mid+1; return k_th(RCH,NRCH); }
}

ll qry(int inx,int newx)
{
    if (lx==rx) return 1LL*abs(lx-_pos)*(PGT[newx].siz-PGT[inx].siz);
    int mid=(lx+rx)>>1;
    if (_pos<=mid)
    {
        ll ret=(PGT[NRCH].val-PGT[RCH].val)-(_pos*(PGT[NRCH].siz-PGT[RCH].siz));
        rx=mid;
        return qry(LCH,NLCH)+ret;
    }
    else
    {
        ll ret=(_pos*(PGT[NLCH].siz-PGT[LCH].siz))-(PGT[NLCH].val-PGT[LCH].val);
        lx=mid+1;
        return qry(RCH,NRCH)+ret;
    }
}

int get_mid(int l,int r)
{
    int len=(r-l+1);
    if (len&1) 
    {
        lx=1; rx=1000001; _val=len/2+1;
        return k_th(troo[l-1],troo[r]);
    }
    else
    {
        lx=1; rx=1000001; _val=len/2;
        ll ret=k_th(troo[l-1],troo[r]);
        lx=1; rx=1000001; _val=len/2+1;
        ret+=k_th(troo[l-1],troo[r]);
        return ret/2;
    }
}

int main()
{
    readx(n); readx(K);
    for (int i=1;i<=n;i++) readx(seq[i]);
    for (int i=1;i<=n;i++)
    {
        seq[i]++;
        lx=1; rx=1000001; _val=seq[i];
        Upd(troo[i-1],troo[i]);
    }
    ll ans=1e18,ans2=0,pos;
    for (int i=1;i+K-1<=n;i++)
    {
        _pos=get_mid(i,i+K-1); lx=1; rx=1000001;
        ll tmp=qry(troo[i-1],troo[i+K-1]);
        if (tmp<ans) 
        {
            ans=tmp; ans2=_pos;
            pos=i;
        }
    }
    printf("%lld\n",ans);
    for (int i=1;i<=n;i++)
    {
        if (i>=pos && i<=pos+K-1) printf("%lld\n",ans2-1);
        else printf("%lld\n",seq[i]-1);
    }
}
```

---

## 作者：cirnovsky (赞：0)

## 题意简述

给定一个长度为 $n$ 的序列，支持单点减一，单点加法的操作，问把一个长度为 $k$ 的区间里的值变成同样的最小操作数。

## 题解

挺好的一道平衡树练手+猜结论题。（雾

化简一下题意，我们需要找到一个值 $m$ 且 $m$ 使得 $\sum_{i=1}^{r}\mid a_{i}-x\mid$ 最小。

其中 $r-l+1=k$。

大约可以猜到这里需要取中位数。

感性理解一下，把 $a_{l},a_{l+1},\cdots,a_{r}$ 排序后如果每个数要取最小只能取中位数。

可以当成一个结论式的东西积累起来。

那么我们就需要一个数据结构，支持插入，删除，查 $k_{th}$。

这里我选择的是Zip-Tree，也就是国内常说的FHQ-Treap。

具体的做法是，枚举每个长度为 $k$ 的区间 $[l,r]$，首先我们把 $a_{1},a_{2},\cdots,a_{k}$ 插入平衡树，然后根据 $k$ 的奇偶性用 $k_{th}$ 操作找到中位数（序列的中位数根据序列的长度奇偶性不同有区别）。

然后计算贡献即可，顺手记录一下区间的位置，方便输出答案。

贡献的计算可以分成大于中位数，小于中位数，等于中位数的情况。

```cpp
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#define int long long

const int Maxn = 1e5 + 5;
int n, k, rt, tot, isa[Maxn];
struct Treap
{
	int l, r, siz, sum, key, val;
} t[Maxn];

int newnode(int val)
{
	t[++tot].val = val;
	t[tot].sum = val;
	t[tot].key = rand();
	t[tot].siz = 1;
	return tot;
}

void maintain(int x)
{
	t[x].siz = t[t[x].l].siz + t[t[x].r].siz + 1;
	t[x].sum = t[t[x].l].sum + t[t[x].r].sum + t[x].val;
}

void Split(int now, int val, int &x, int &y)
{
	if (now == 0)	x = y = 0;
	else
	{
		if (val >= t[now].val)
		{
			x = now;
			Split(t[now].r, val, t[now].r, y);
		}
		else
		{
			 y = now;
			 Split(t[now].l, val, x, t[now].l);
		}
		maintain(now);
	}
}

int Merge(int x, int y)
{
	if (x == 0 || y == 0)	return x + y;
	else
	{
		if (t[x].key > t[y].key)
		{
			t[x].r = Merge(t[x].r, y);
			maintain(x);
			return x;
		}
		else
		{
			t[y].l = Merge(x, t[y].l);
			maintain(y);
			return y;
		}
	}
}

int rt1, rt2, rt3;
void Insert(int val)
{
	Split(rt, val, rt1, rt2);
	rt = Merge(rt1, Merge(newnode(val), rt2));
}

void Remove(int val)
{
	Split(rt, val, rt1, rt3);
	Split(rt1, val - 1, rt1, rt2);
	rt2 = Merge(t[rt2].l, t[rt2].r);
	rt = Merge(rt1, Merge(rt2, rt3));
}

int Find_Kth(int rnk)
{
	int now = rt;
	while (now)
	{
		if (t[t[now].l].siz + 1 == rnk) 	break;
		else if (t[t[now].l].siz >= rnk) 	now = t[now].l;
		else
		{
			rnk -= t[t[now].l].siz + 1;
			now = t[now].r;
		}
	}
	return t[now].val;
}

int Query(int mid)
{
	Split(rt, mid, rt1, rt3);
	Split(rt1, mid - 1, rt1, rt2);
	int lth = rt1, mth = rt3;
	int cont_l = t[lth].siz * mid - t[lth].sum;
	int cont_r = t[mth].sum - t[mth].siz * mid;
	rt = Merge(rt1, Merge(rt2, rt3));
	return cont_l + cont_r;
}

signed main()
{
	srand((unsigned)(time(NULL)));
	int MID, LEFT, RIGHT, ANS = LONG_LONG_MAX;
	scanf("%lld %lld", &n, &k);
	for (int i = 1; i <= n; ++i)	scanf("%lld", &isa[i]);
	for (int i = 1; i <= k; ++i) 	Insert(isa[i]);
	int l = 1, r = k;
	for (int i = k; i <= n; ++i)
	{
		int mid;
		if (k & 1)	mid = Find_Kth((k >> 1) + 1);
		else 	mid = (Find_Kth(k >> 1) + Find_Kth((k >> 1) + 1)) >> 1;
		int xxx = Query(mid);
		if (ANS > xxx)
		{
			ANS = xxx;
			MID = mid;
			LEFT = l - 1;
			RIGHT = r + 1;
		}
		l++, r++;
		Remove(isa[l - 1]);
		Insert(isa[r]);
	}
	printf("%lld\n", ANS);
	for (int i = 1; i <= LEFT; ++i) 	printf("%lld\n", isa[i]);
	for (int i = LEFT + 1; i <= RIGHT - 1; ++i) 	printf("%lld\n", MID);
	for (int i = RIGHT; i <= n; ++i) 	printf("%lld\n", isa[i]);
	return 0;
}
```

---

