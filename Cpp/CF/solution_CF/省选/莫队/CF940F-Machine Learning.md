# Machine Learning

## 题目描述

You come home and fell some unpleasant smell. Where is it coming from?

You are given an array $ a $ . You have to answer the following queries:

1. You are given two integers $ l $ and $ r $ . Let $ c_{i} $ be the number of occurrences of $ i $ in $ a_{l:r} $ , where $ a_{l:r} $ is the subarray of $ a $ from $ l $ -th element to $ r $ -th inclusive. Find the Mex of $ {c_{0},c_{1},...,c_{10^{9}}} $
2. You are given two integers $ p $ to $ x $ . Change $ a_{p} $ to $ x $ .

The Mex of a multiset of numbers is the smallest non-negative integer not in the set.

Note that in this problem all elements of $ a $ are positive, which means that $ c_{0} $ = 0 and $ 0 $ is never the answer for the query of the second type.

## 说明/提示

The subarray of the first query consists of the single element — $ 1 $ .

The subarray of the second query consists of four $ 2 $ s, one $ 3 $ and two $ 1 $ s.

The subarray of the fourth query consists of three $ 1 $ s, three $ 2 $ s and one $ 3 $ .

## 样例 #1

### 输入

```
10 4
1 2 3 1 1 2 2 2 9 9
1 1 1
1 2 8
2 7 1
1 2 8
```

### 输出

```
2
3
2
```

# 题解

## 作者：ouuan (赞：34)

其实这题根本不用把数字也分块..

如果不会带修莫队的话可以到网上找教程，也可以看[我写的教程](https://www.cnblogs.com/ouuan/p/MoDuiTutorial.html)

首先将数列中原本的数字以及所有修改中的数字全部离散化，然后就是普通的带修莫队，不同之处在于更新答案时不是记录某个数字出现了几次，而是在更新数字出现的次数的同时更新“数字出现的次数”出现的次数，即：

```
void add(int x)
{
	--tot[cnt[x]];
	++tot[++cnt[x]];
}

void del(int x)
{
	--tot[cnt[x]];
	++tot[--cnt[x]];
}
```

然后是为什么可以暴力求mex：

考虑答案为 $x$，那么存在出现了 $1$ 次的数、出现了 $2$ 次的数……出现了 $x-1$ 次的数。所以，$\sum\limits_{i=1}^{x-1}i<=n$，就是说答案是 $O(\sqrt{n})$ 级别的，暴力求解的复杂度为 $O(n\sqrt{n})$，而带修莫队的复杂度为 $O(n^{\frac{5}{3}})$，也就是说暴力求mex完全不影响总复杂度。

所以一行求mex就好了：

```
for (ans[q[i].id]=1;tot[ans[q[i].id]]>0;++ans[q[i].id]);
```

完整代码：

```
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

inline int read()
{
    char c;int out=0;
    for (c=getchar();c<'0'||c>'9';c=getchar());
    for (;c>='0'&&c<='9';c=getchar()){out=(out<<3)+(out<<1)+c-'0';}
    return out;
}
void write(int x)
{
    if (x>9){write(x/10);}
	putchar(x%10+'0');
}

const int B=2154;

struct Query
{
	int l,r,t,id;
	bool operator<(Query& y)
	{
		return l/B==y.l/B?(r/B==y.r/B?t<y.t:r<y.r):l<y.l;
	}
} q[100010];

struct Change
{
	int p,x;
} c[100010];

void add(int x);
void del(int x);
void modify(int ti,int qu);

int n,m,a[100010],b[200010],cnt[200010],tot[100010],qcnt,ccnt,qaq,now,ans[100010];

int main()
{
	int i,j,l=1,r=0,type;
	
	n=read();
	m=read();
	
	for (i=1;i<=n;++i)
	{
		b[qaq++]=a[i]=read();
	}
	
	for (i=0;i<m;++i)
	{
		type=read();
		if (type==1)
		{
			q[++qcnt].l=read();
			q[qcnt].r=read();
			q[qcnt].t=ccnt;
			q[qcnt].id=qcnt;
		}
		else
		{
			c[++ccnt].p=read();
			b[qaq++]=c[ccnt].x=read();
		}
	}
	
	sort(b,b+qaq);
	qaq=unique(b,b+qaq)-b;
	
	for (i=1;i<=n;++i)
	{
		a[i]=lower_bound(b,b+qaq,a[i])-b;
	}
	
	for (i=1;i<=ccnt;++i)
	{
		c[i].x=lower_bound(b,b+qaq,c[i].x)-b;
	}
	
	sort(q+1,q+qcnt+1);
	
	for (i=1;i<=qcnt;++i)
	{
		while (l>q[i].l)
		{
			add(a[--l]);
		}
		while (r<q[i].r)
		{
			add(a[++r]);
		}
		while (l<q[i].l)
		{
			del(a[l++]);
		}
		while (r>q[i].r)
		{
			del(a[r--]);
		}
		while (now<q[i].t)
		{
			modify(++now,i);
		}
		while (now>q[i].t)
		{
			modify(now--,i);
		}
		for (ans[q[i].id]=1;tot[ans[q[i].id]]>0;++ans[q[i].id]);
	}
	
	for (i=1;i<=qcnt;++i)
	{
		write(ans[i]);
		putchar('\n');
	}
	
	return 0;
}

void add(int x)
{
	--tot[cnt[x]];
	++tot[++cnt[x]];
}

void del(int x)
{
	--tot[cnt[x]];
	++tot[--cnt[x]];
}

void modify(int ti,int qu)
{
	if (c[ti].p>=q[qu].l&&c[ti].p<=q[qu].r)
	{
		del(a[c[ti].p]);
		add(c[ti].x);
	}
	swap(c[ti].x,a[c[ti].p]);
}
```

---

## 作者：NaCly_Fish (赞：19)

这题太**了。。理解题意都用了半天。  

此处补一下样例解释：  
对于第二次查询，区间$[2,8]$中出现了：  
$4$个2，$2$个1，$1$个3。  
$1,2,4$都出现了，最小没有出现的正整数是$3$，所以第二个询问输出`3`。  
****
下面是题解：  

考虑莫队，我们需要写一个update函数，用来维护区间中增加/减少一个数带来的影响。  
首先开一个数组$\text{cnt}_1$，其中$\text{cnt}_1[i]$表示原数组区间中数字$i$的出现次数，在update的时候对应项$+1/-1$即可。  
然后再开一个数组$\text{cnt}_2$，$\text{cnt}_2[i]$表示$\text{cnt}_1$中$i$的出现次数。  
现在要做的，就是在$\text{cnt2}$中求$\text{mex}$了。  

在$\text{cnt}_1$中删除了一个数$x$时(也就是$\text{cnt}_2[x]$减少了$1$)，若$\text{cnt}_2[x]$为$0$，那说明$x$在$\text{cnt}_1$中没有出现过。这时需要把答案和$x$取$\min$。  
类似的，若$\text{cnt}_1$中多了一个数$x$，就暴力地找比$x$大且最小的、没有在$\text{cnt}_1$中出现过的数。  

剩下的，就是写带修莫队的板子上去。注意$a_i$的范围$[1,10^9]$，需要离散化一下。  
我在这里原本用的是`unordered_map`，然后就完美TLE了。。这里一定要注意。  

你也许会说：“每次暴力地找$\text{mex}$，时间复杂度显然为$\text{O}(n)$啊？”   
这里可以(但我不会)证明，每次update操作是均摊$\Theta(1)$的，每次询问就是均摊$\Theta(n^\frac23)$。  
这个好像lxl说过？具体我也找不着了QAQ  

参考代码：  
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 400003
#define reg register
using namespace std;

struct query{
    int l,r,t,id;
    query(int l=0,int r=0,int t=0,int id=0):l(l),r(r),t(t),id(id){}
};

struct change{
    int pos,last,next;
    change(int pos=0,int last=0,int next=0):pos(pos),last(last),next(next){}
};

query q[N];
change c[N];
int a[N],be[N],dt[N],ans[N],cnt[N],lsh[N],mp[N];
int n,m,unit,qc,res,l,r;

inline void read(int &x);
void print(int x);
inline bool cmp(query x,query y); //莫队的询问排序
inline void modify(int i,int t); //修改
inline void update(int i,int t); //更新
void discretization(); //离散化

int main(){
    int op,t = 0;
    read(n),read(m);
    unit = pow(n,0.666666666);
    for(reg int i=1;i<=n;++i){
        read(a[i]);
        lsh[i] = dt[i] = a[i];
        be[i] = i/unit+1;
    }
    for(reg int i=1;i<=m;++i){
        read(op),read(l),read(r);
        if(op==1){
            ++qc;
            q[qc] = query(l,r,t,qc);
        }else{
            c[++t] = change(l,dt[l],r);
            lsh[n+t] = dt[l] = r;
        }
    }
    discretization();
    sort(q+1,q+1+qc,cmp);
    l = 1;
    r = t = 0;
    cnt[0] = n<<2; //一开始全部是0,所以要把cnt[0]设的很大
    for(reg int i=1;i<=qc;++i){
        while(t<q[i].t) modify(c[t+1].pos,c[t+1].next),++t;
        while(t>q[i].t) modify(c[t].pos,c[t].last),--t;
        while(l<q[i].l) update(a[l],-1),++l;
        while(l>q[i].l) update(a[l-1],1),--l;
        while(r<q[i].r) update(a[r+1],1),++r;
        while(r>q[i].r) update(a[r],-1),--r;
        ans[q[i].id] = res;
    }
    for(reg int i=1;i<=qc;++i){
        print(ans[i]);
        putchar('\n');
    }
    return 0;
}

void discretization(){
    sort(lsh+1,lsh+1+n+t);
    int len = unique(lsh+1,lsh+n+t+1)-lsh-1;
    for(reg int i=1;i<=n;++i)
        a[i] = lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
    for(reg int i=1;i<=t;++i){  
        c[i].last = lower_bound(lsh+1,lsh+len+1,c[i].last)-lsh;
        c[i].next = lower_bound(lsh+1,lsh+len+1,c[i].next)-lsh;
    }
}

inline void update(int i,int t){
    int x = mp[i];
    --cnt[x];
    if(cnt[x]==0) res = min(res,x);
    mp[i] += t;
    if(x+t>=0) ++cnt[x+t];
    x = res;
    while(cnt[x]>0) ++x; //这里是均摊O(1)的
    res = x;
}

inline void modify(int i,int t){
    if(l<=i&&i<=r){
        update(a[i],-1);
        update(t,1);
    }
    a[i] = t;
}

inline bool cmp(query x,query y){
    if(be[x.l]==be[y.l]){
        if(be[x.r]==be[y.r]) return x.t < y.t;
        return x.r < y.r;
    }
    return x.l < y.l;
}

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
```

---

## 作者：juju527 (赞：12)

upd on 2021.4.1 修了个代码可能re的锅

### 带修莫队

求 $\text{mex}$ 是莫队的经典操作

不带修改的求区间内数值的 $\text{mex}$ 用回滚莫队可以解决

这里是出现次数的 $\text{mex}$

我们想这样一个小结论

我们有 $n$ 个数字，假如用这些数字能构成的最大的出现次数 $\text{mex}$ 是多少

假如我们的 $\text{mex}$ 达到 $k$ ，那么应该有$\frac{k*(k+1)}2$这么多个数字

那么这个 $\text{mex}$ 应该是$\sqrt n$级别的

那我们就不要担心了

直接跑带修莫队

维护每个数的出现次数

再拿一个桶记录每个出现次数有多少个值

等跑完这个区间，我们从1开始往后扫

由于最 $\text{mex}$ 最大就$\sqrt n$

故复杂度取带修莫队的$O(n^\frac 5 3)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,maxm=100005,maxw=200005;
int base;
struct query{
	int id;
	int x,y,t;
	bool operator <(query i)const{
		return x/base==i.x/base?(y/base==i.y/base?t<i.t:y<i.y):x<i.x;
	}
}q[maxm];
struct node{
	int id,s;
	bool operator <(node i)const{
		return s<i.s;
	}
}b[maxn+maxm];
int c[maxn];
int a[maxm][2];
int l,r,p;
int ans=0;
int ANS[maxm];
int cnt[maxw];
int st[maxn];
bool vis[maxm];
inline int read(){
	register int x=0,y=1;
	register char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*y;
}
inline void write(register int x){
	if(!x)return ;
	write(x/10);
	putchar(x%10+'0');
	return ;
}
inline void ins(register int x){
	st[cnt[c[x]]]--;
	cnt[c[x]]++;
	st[cnt[c[x]]]++;
	return ;
}
inline void del(register int x){
	st[cnt[c[x]]]--;
	cnt[c[x]]--;
	st[cnt[c[x]]]++;
	return ;
}
inline void change(register int x){
	if(a[x][0]>=l&&a[x][0]<=r)del(a[x][0]);
	swap(c[a[x][0]],a[x][1]);
	if(a[x][0]>=l&&a[x][0]<=r)ins(a[x][0]);
	return ;
}
int main(){
	register int n,m;
	n=read();m=read();
	base=pow(n,0.66666);
	for(register int i=1;i<=n;i++){
		b[i].id=i;
		b[i].s=read();
	}
	register int tot=0,tim=0;
	for(register int i=1;i<=m;i++){
		register int opt,x,y;
		opt=read();x=read();y=read();
		if(opt==1){
			tot++;
			vis[i]=1;
			q[tot].id=i;
			q[tot].x=x;
			q[tot].y=y;
			q[tot].t=tim;
		}
		else{
			tim++;
			a[tim][0]=x;
			b[tim+n].id=tim+n;
			b[tim+n].s=y;
		}
	}
	sort(b+1,b+n+tim+1);
	int w=0;
	for(int i=1;i<=n+tim;i++){
		if(b[i].s>b[i-1].s)w++;
		if(b[i].id<=n)c[b[i].id]=w;
		else a[b[i].id-n][1]=w;
	}
	sort(q+1,q+tot+1);
	l=1;r=0;p=0;
	for(register int i=1;i<=tot;i++){
		int x=q[i].x,y=q[i].y,t=q[i].t;
		while(l>x)ins(--l);
		while(r<y)ins(++r);
        while(l<x)del(l++);
		while(r>y)del(r--);
		while(p<t)change(++p);
		while(p>t)change(p--);
		ans=0;
		while(st[ans+1])ans++;//暴力扫
		ANS[q[i].id]=ans+1;
	}
	for(register int i=1;i<=m;i++){
		if(!vis[i])continue;
		write(ANS[i]);
		if(!ANS[i])putchar('0');
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：louhao088 (赞：5)

## 一道带修莫队

若不会带修莫队，可以先做一下[P1903 [国家集训队]数颜色 / 维护队列](https://www.luogu.com.cn/problem/P1903)

由于题中要求$mex$,而$mex$最大为$(-1+sqrt(1+8n))/2$

简单证明：

若$mex$为$x$,则至少需要$1+2+3+...+x$个元素，即$(1+x)*x/2$个

$(1+x)*x/2=n$,又因$x>0$解得$x=(-1+sqrt(1+8n))/2$

故求$mex$是$O(sqrt(n))$,可以暴力

```
int getans()
{
	for(int i=1;i<=n;i++)
    	if(!si[i])return i;
}
```


其余就按带修莫队一样做即可

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
const int maxn=200005;
struct node
{
	int l,r,id,pre;
}b[maxn];
int m,n,x,y,a[maxn],t,id[maxn],ans[maxn],sum=0,k,l,r,num=0,s[maxn],si[maxn],now,d[maxn];
int opt,tot=0,c[maxn],c2[maxn],qnum=0,cnt=0;
bool cmp(node a,node b)
{
	if(id[a.l]!=id[b.l])return id[a.l]<id[b.l];
	else if(id[a.r]!=id[b.r])return id[a.r]<id[b.r];
	return a.pre<b.pre;
}
int add(int x){si[s[x]]--,s[x]++,si[s[x]]++;}
int cut(int x){si[s[x]]--,s[x]--,si[s[x]]++;}
int change(int x,int l,int r)
{
	if(c[x]>=l&&c[x]<=r)
	{
		si[s[a[c[x]]]]--,s[a[c[x]]]--,si[s[a[c[x]]]]++;
		si[s[c2[x]]]--,s[c2[x]]++,si[s[c2[x]]]++;
	}swap(c2[x],a[c[x]]);
}
int getans(){for(int i=1;i<=n;i++)if(!si[i])return i;}
signed main()
{
	n=read();
   t=pow(n,0.6666666);//感觉这样快一些
   m=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=d[++cnt]=read(),id[i]=(i-1)/t+1;
	}
	for(int i=1;i<=m;i++)
	{
		opt=read();
		if(opt==1)b[++qnum].l=read(),b[qnum].r=read(),b[qnum].id=qnum,b[qnum].pre=tot;
		else if(opt==2)c[++tot]=read(),c2[tot]=d[++cnt]=read();
	}
	sort(d+1,d+cnt+1);
	int un=unique(d+1,d+1+cnt)-d-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(d+1,d+1+un,a[i])-d;
	for(int i=1;i<=tot;i++) c2[i]=lower_bound(d+1,d+1+un,c2[i])-d;
	sort(b+1,b+qnum+1,cmp);l=b[1].l,r=b[1].r;now=0;
	for(int i=b[1].l;i<=b[1].r;i++)add(a[i]);
	while(now<b[1].pre)change(++now,b[1].l,b[1].r);ans[b[1].id]=getans();//cout<<b[1].id<<endl;
	for(int i=2;i<=qnum;i++)
	{
		while(l<b[i].l)cut(a[l++]);
		while(l>b[i].l)add(a[--l]);//cout<<si[1]<<endl;
		while(r<b[i].r)add(a[++r]);
		while(r>b[i].r)cut(a[r--]);//cout<<si[1]<<" "<<b[i].id<<" "<<r+1<<" "<<s[2]<<" "<<s[3]<<" "<<s[1]<<endl;//cout<<now<<" "<<b[i].id<<endl;
		while(now>b[i].pre)change(now--,b[i].l,b[i].r);
		while(now<b[i].pre)change(++now,b[i].l,b[i].r);
		ans[b[i].id]=getans();
	}
	for(int i=1;i<=qnum;i++)printf("%d\n",ans[i]);
	return 0;
} 
```

最后，最重要一点是要开优化~~洛谷优化没用，要手动开~~，这样才能A





---

## 作者：龙神哈迪斯 (赞：4)

这不就是离散化+带修改莫队吗？

大家可以去找一下这个题目其实就是两个题目混合而成
[[国家集训队]数颜色](https://www.luogu.org/problemnew/show/P1903)+[Rmq Problem / mex](https://www.luogu.org/problemnew/show/P4137)，出现次数就是裸的数颜色，然后套个桶去数$mex$，然后就能暴力AC了(此话来源于机房大佬[$yl$](http://www.cnblogs.com/cjoieryl/p/8468558.html),~~欢迎接受Ta的小迷弟和小迷妹~~)

吐槽一下：
$mex$
值开桶暴力求就能过了

我的做法：
把数字也分块，计算$mex$时，找到第一个不满的块，再在块内找的那个$mex$值

上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
#define RG register
#define MAX 200000
inline int read()
{
    RG int x=0,t=1;RG char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar(); 
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
struct Event
{
    int id;
    int l,r,blk;
    int lst;
}Q[MAX],P[MAX];
int ans[MAX];
int S[MAX<<1],ss,n,m,a[MAX],b[MAX],blk=3000,tot,q;
int sum[MAX],Sum[MAX];
int Blk[MAX];
bool cmp(Event a,Event b){
    if(a.blk!=b.blk) return a.blk<b.blk;
    if((a.r-1)/blk!=(b.r-1)/blk)return (a.r-1)/blk<(b.r-1)/blk;
    return a.lst<b.lst;
}
void Change(int num,int w)
{
    Sum[sum[num]]--;
    if(Sum[sum[num]]==0)Blk[(Sum[sum[num]]-1)/500]--;
    sum[num]+=w;
    Sum[sum[num]]++;
    if(Sum[sum[num]]==1)Blk[(Sum[sum[num]]-1)/500]++;
}
int GetAns()
{
    for(int i=0;;++i)
    {
        if(Blk[i]==blk)continue;
        for(int j=1;j<=blk;++j)
            if(!Sum[i*blk+j])return i*blk+j;
    }
}
void Modify(int st,int now,int l,int r)
{
    if(st==now)return;
    if(now<st)
        for(int i=now+1;i<=st;++i)
        {
            a[P[i].l]=P[i].r;
            if(P[i].l>=l&&P[i].l<=r)
            {
                Change(P[i].lst,-1);
                Change(P[i].r,1);
            }
        }
    else 
        for(int i=now;i>st;--i)
        {
            a[P[i].l]=P[i].lst;
            if(P[i].l>=l&&P[i].l<=r)
            {
                Change(P[i].r,-1);
                Change(P[i].lst,1);
            }
        }
}
void Work(int pos,int w)
{
    Change(a[pos],w);
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n;++i)b[i]=a[i]=read(),S[++ss]=a[i];
    for(int i=1;i<=m;++i)
    {
        int opt=read(),l=read(),r=read();
        if(opt==1){Q[++q]=(Event){q,l,r,(l-1)/blk,tot};}
        else
        {
            P[++tot]=(Event){tot,l,r,0,b[l]};
            b[l]=r;
            S[++ss]=r;
        }
    }
    
    sort(&S[1],&S[ss+1]);
    ss=unique(&S[1],&S[ss+1])-S-1;
    for(int i=1;i<=n;++i)a[i]=lower_bound(&S[1],&S[ss+1],a[i])-S;
    for(int i=1;i<=tot;++i)
    {
        P[i].r=lower_bound(&S[1],&S[ss+1],P[i].r)-S;
        P[i].lst=lower_bound(&S[1],&S[ss+1],P[i].lst)-S;
    }
    sort(&Q[1],&Q[q+1],cmp);

    int md=0,l=1,r=0;
    for(int i=1;i<=q;++i)
    {
        while(r<Q[i].r)Work(++r,1);
        while(l>Q[i].l)Work(--l,1);
        while(r>Q[i].r)Work(r--,-1);
        while(l<Q[i].l)Work(l++,-1);
        Modify(Q[i].lst,md,l,r);
        md=Q[i].lst;
        ans[Q[i].id]=GetAns();
    }
    for(int i=1;i<=q;++i)
        printf("%d\n",ans[i]);
    return 0;
}

```

---

## 作者：BFqwq (赞：4)

其实这个题有严格 $\operatorname{O}(n\sqrt n)$ 的做法（好像 ouuan 大佬就是这么做的）。

我们只维护一个存在次数对应的数有几个，这就是一个简单的莫队。

然后我们有一个非常优秀的性质：

考虑最坏情况，当在序列中有一种数出现 $1$ 次，一种数出现 $2$ 次……时，$\operatorname{mex}$ 显然是最大的。

但是即使是这样，我们也只能出现约 $\sqrt n$ 种不同的数据（因为这个序列中最多十万个数）。

于是我们在每次询问后查询答案，其复杂度严格 $\sqrt n$。

故可以严格通过。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	register int x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register int x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=233333;
int n,m,a[maxn],res,len,lst[maxn],sum[maxn];
int bl,ans[maxn],lsh[maxn],cnt[maxn],l,r,now;
struct query{
	int l,r,tim,id;
	friend bool operator <(query a,query b){
		if(a.l/bl!=b.l/bl) return a.l<b.l;
		if(a.r/bl!=b.r/bl) return a.r<b.r;
		return a.tim<b.tim;
	}
}q[maxn];
struct change{
	int pos,val,lst;
}c[maxn];
void add(int v){    
    cnt[sum[v]]--;
    sum[v]++;
    cnt[sum[v]]++;
}
void del(int v){
    cnt[sum[v]]--;
    sum[v]--;
    cnt[sum[v]]++;
}
void upd(int i,int v){
    if(l<=i&&i<=r){
        del(a[i]);
        add(v);
    }
    a[i]=v;
}
signed main(){
	len=n=read();m=read();bl=pow(n,0.666666666);
	for(int i=1;i<=n;i++)
		lsh[i]=lst[i]=a[i]=read();
	int qnum=0,cnum=0;
	for(int i=1;i<=m;i++){
		int opt=read();
		if(opt==1){
            q[++qnum].l=read();
            q[qnum].r=read();
            q[qnum].tim=cnum; 
            q[qnum].id=qnum;        
        }
        else{
            c[++cnum].pos=read();
            c[cnum].lst=lst[c[cnum].pos];
            c[cnum].val=lsh[++len]=lst[c[cnum].pos]=read();
        }
    }
	sort(q+1,q+qnum+1);
	sort(lsh+1,lsh+len+1);
	len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;++i)
        a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
    for(int i=1;i<=cnum;++i){
        c[i].lst=lower_bound(lsh+1,lsh+len+1,c[i].lst)-lsh;
        c[i].val=lower_bound(lsh+1,lsh+len+1,c[i].val)-lsh;
    }
	l=1,r=0,now=0;
	cnt[0]=n<<3;
    for(int i=1;i<=qnum;i++){
    	while(now<q[i].tim)++now,upd(c[now].pos,c[now].val);
        while(now>q[i].tim)upd(c[now].pos,c[now].lst),now--;
		while(l>q[i].l)add(a[--l]);
		while(r<q[i].r)add(a[++r]);
		while(l<q[i].l)del(a[l++]);
        while(r>q[i].r)del(a[r--]);
        for(int j=1;j<=maxn;j++){
        	if(!cnt[j]){
				ans[q[i].id]=j;	
        		break;
			}
		} 
    }
    for(int i=1;i<=qnum;i++){
    	print(ans[i]);
	}
	return 0;
}
```


---

## 作者：Islauso (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF940F)

---

这道题不算特别难，基本算得上是带修莫队的板子题，首先应该想到的是统计每个数字出现的次数，不过这道题比较有趣的一点是，要求查询的是每个数字出现次数的 Mex，所以还应该统计一个出现次数的出现次数，具体来说，我们用一个 $cnt$ 数组来统计数字出现次数，然后再用一个 $cnt2$ 数组来统计 $cnt$ 数组内每个数字的出现次数，在更新 $cnt$ 的时候顺便也更新一下 $cnt2$ 就可以了。

但有一点不太好想的是如何求这个出现次数的 Mex，一开始，我想的是可以跟着 $cnt2$ 数组一起更新，但这样会有很多问题，因为我们无法判断如果 $cnt2_{ans}$ 不为 $0$ 了，那么答案应该是多少，所以我采用了一个很玄学的方法，用一个 bitset 来统计哪些出现次数是没有出现过的，最后找一个最小的就可以了，这样我们只需要在更新 $cnt2$ 的时候判断一下这个被更新的值是否从 $0$ 到 $1$ 或是从 $1$ 到 $0$，然后相对应地把 bitset 也更新一下就好了。而在找的时候，可以用 bitset 的一个成员函数`_Find_first`，它的作用是寻找这个 bitset 中第一个 $1$，并且返回它的位置，也就是所有数字出现次数的 Mex。

对了，这道题由于值域为 $[1,10^9]$，所以需要离散化，在离散化时要注意，不仅对于 $a$ 数组要离散化，对于修改操作中要求改成的那些数也要进行离散化，而且应该是一起进行，否则有可能会 RE，同时，由于这两部分是一起离散化的，所以最终离散后的值域应该是 $[1,2\times n]$，记得要把数组大小开够，否则也会 RE。

参考代码：

```cpp
#include<bits/stdc++.h>
#define N 200010//数组大小开够！
using namespace std;
int n,m,p,len,k,k1,lastc,l=1,r,t,ans[N],cnt[N],cnt1[N],a[N];
struct Query
{
	int x;
	int y;
	int z;
	int id;
	bool operator < (Query const &a) const
	{
		return ((x/len)^(a.x/len)) ? x/len<a.x/len : ((y/len)^(a.y/len)) ? y/len<a.y/len : z<a.z;
        //带修莫队不像普通莫队，在排序时应当以左端点所在的块为第一关键字，右端点所在的块为第二关键字，时间为第三关键字
	}
};
struct Change
{
	int p;
	int v;
};
Query q[N];
Change c[N];
vector<int> rec;//用来离散的数组，为了方便用了 vector
bitset<N> num;//统计答案的 bitset
void add(int i)
{
	cnt1[cnt[a[i]]]--;
	if(!cnt1[cnt[a[i]]])//先把当前数字出现次数的出现次数减一
		num[cnt[a[i]]]=1;
	cnt[a[i]]++;
	if(!cnt1[cnt[a[i]]])//再把当前数字出现次数的出现次数加一
		num[cnt[a[i]]]=0;
	cnt1[cnt[a[i]]]++;
}
void del(int i)
{
	cnt1[cnt[a[i]]]--;
	if(!cnt1[cnt[a[i]]])//操作基本同上
		num[cnt[a[i]]]=1;
	cnt[a[i]]--;
	if(!cnt1[cnt[a[i]]])
		num[cnt[a[i]]]=0;
	cnt1[cnt[a[i]]]++;
}
int main()
{
	scanf("%d%d",&n,&m);
	len=(int)pow(n,2.0/3.0);//这也是要注意的一点，带修莫队的块长应该为n^(2/3)
	rec.push_back(0);//防止离散后的值为 0（其实不加也能 AC，但我觉得要更严谨一点）
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		rec.push_back(a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		int op,l,r;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1)
			q[++k]=Query{l,r,lastc,k};
		else
		{
			k1++;
			lastc=k1;
			rec.push_back(r);
			c[k1]=Change{l,r};
		}
	}
	sort(rec.begin(),rec.end());
	rec.erase(unique(rec.begin(),rec.end()),rec.end());
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(rec.begin(),rec.end(),a[i])-rec.begin();
	for(int i=1;i<=k1;i++)
		c[i].v=lower_bound(rec.begin(),rec.end(),c[i].v)-rec.begin();
	sort(q+1,q+1+k);
	cnt1[0]=0x3f3f3f3f;//由于答案一定不为 0，所以可以把 cnt1[0] 设为无穷大
	num.set();//bitset 成员函数之一，把所有值设为 1
	num[0]=0;
	for(int i=1;i<=k;i++)
	{
		while(l>q[i].x)
			add(--l);
		while(r<q[i].y)
			add(++r);
		while(l<q[i].x)
			del(l++);
		while(r>q[i].y)
			del(r--);
		while(t<q[i].z)
		{
			t++;
			if(l<=c[t].p&&r>=c[t].p)
			{
				del(c[t].p);
				swap(a[c[t].p],c[t].v);
				add(c[t].p);
			}
			else
				swap(a[c[t].p],c[t].v);
		}
		while(t>q[i].z)
		{
			if(l<=c[t].p&&r>=c[t].p)
			{
				del(c[t].p);
				swap(a[c[t].p],c[t].v);
				add(c[t].p);
			}
			else
				swap(a[c[t].p],c[t].v);
			t--;
		}
		ans[q[i].id]=num._Find_first();//上面讲过了，获取出现次数的 Mex
	}
	for(int i=1;i<=k;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```



---

## 作者：Strelitzia (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF940F)

---

这道题目看到时，是想到了这道[Rmq Problem / mex](https://www.luogu.com.cn/problem/P4137)。

就是维护出现次数，再对出现次数分块，但这里是不必要的。


因为区间数字出现次数的和最多为 n，所以就算数字出现次数分布非常平均，

这个 mex 也应该是 $\sqrt{n}$ 这个范围的，所以就可以不用对出现次数分块。

首先，本题需要修改，要用带修莫队，其次这里求的是**数字出现**次数的 mex。


注意：因为有更改操作，离散化数组要开到两倍。

还有啊，$cnt$ 数组要记得将之前的出现次数减掉。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	T f = 1;x = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 200005;

int n,m,a[maxn],cnt1,cnt2,ans[maxn],res,vis[maxn],cnt[maxn],num[maxn],pos[maxn],tot,b[maxn],L[maxn],R[maxn],t;

struct Query {
	int l,r,now,id;
	Query() {}
	Query(int L,int R,int N,int I) {l = L,r = R,now = N,id = I;}
}ask[maxn];

struct Maintain {
	int p,c;
	Maintain() {}
	Maintain(int P,int C) {p = P,c = C;}
}up[maxn];

bool cmp(Query x,Query y) {
	if (pos[x.l] ^ pos[y.l]) return x.l < y.l;
	if (pos[x.r] ^ pos[y.r]) return x.r < y.r;
	return x.now < y.now;
}

void Change(int x,int y) {
	if (ask[y].l <= up[x].p && up[x].p <= ask[y].r) {
		cnt[vis[up[x].c]] --;		//注意哦
		cnt[++ vis[up[x].c]] ++;
		cnt[vis[a[up[x].p]]] --;
		cnt[-- vis[a[up[x].p]]] ++;
	}
	swap(a[up[x].p],up[x].c);
}

void Add(int x) {
	cnt[vis[a[x]]] --;
	cnt[++ vis[a[x]]] ++;
}

void Sub(int x) {
	cnt[vis[a[x]]] --;
	cnt[-- vis[a[x]]] ++;
}

int op[maxn],x[maxn],y[maxn];

int main () {
	read(n);read(m);
	t = pow(n,0.66666667);
	for (int i = 1 ; i <= n ; ++ i) read(a[i]),b[i] = a[i],pos[i] = i / t;
	tot = n;
	for (int i = 1 ; i <= m ; ++ i) {
		read(op[i]);read(x[i]);read(y[i]);
		if (op[i] == 2) b[++ tot] = y[i];
	}
	sort(b + 1,b + 1 + tot);
	tot = unique(b + 1,b + 1 + tot) - b - 1;
	for (int i = 1 ; i <= n ; ++ i) a[i] = lower_bound(b + 1,b + 1 + tot,a[i]) - b;
	for (int i = 1 ; i <= m ; ++ i) {
		if (op[i] == 2) y[i] = lower_bound(b + 1,b + 1 + tot,y[i]) - b;
		if (op[i] == 1) ++ cnt1,ask[cnt1] = Query(x[i],y[i],cnt2,cnt1);
		if (op[i] == 2) up[++ cnt2] = Maintain(x[i],y[i]);
	}
	sort(ask + 1,ask + 1 + cnt1,cmp);
	int l = 1,r = 0,tm = 0;
	for (int i = 1 ; i <= cnt1 ; ++ i) {
		while (l > ask[i].l) Add(-- l);
		while (r < ask[i].r) Add(++ r);
		while (l < ask[i].l) Sub(l ++);
		while (r > ask[i].r) Sub(r --);
		while (ask[i].now > tm) Change(++ tm,i);
		while (ask[i].now < tm) Change(tm --,i);
		ans[ask[i].id] = 1;
		while (cnt[ans[ask[i].id]]) ans[ask[i].id] ++;
	}
	for (int i = 1 ; i <= cnt1 ; ++ i) print(ans[i]),putchar('\n');
	return 0;
}
```

---

## 作者：Others (赞：1)

**先吐槽一波：** 这题题目描述太惊人了，内个 mex 的定义是靠样例理解的...
# 题目大意
对一个线形存储的数据进行修改和查询。

这里给一个对 mex 的好理解的定义（我也不知道题目里的到底对不对...）：在区间里出现的“数字的次数”的次数最小的未出现的数字。
# 分析（思路）
这题就是一个裸的带修莫队，不懂的可以去先学学。

最难的一点就是如何处理 mex，本来我是想打值域分块的，但是我真的~~太懒了~~。于是就试了一下暴力，没想到真的过了，介绍一下暴力，这题首先开一个 $cnt$ 数组存每个数字出现的次数，再开一个 $ccnt$ 数组存 $cnt$ 数组里数字出现的次数，在离散化就行了，然后你会发现修改也要离散化，于是离散化的数组和 $cnt$ 和 $ccnt$ 都要开 $2*n$ 的长度。

最后的 $ans$ 就枚举 $ccnt$ 里的最早为 0 的下标就行了。

重点都讲完了，上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void qr(register int &ret){register int x=0,f=0;register char ch=getchar();while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();ret=f?-x:x;}
const int maxn=100005;
int n,m,s,l=1,r,t,tot,cntq,cntr,Q,idx[maxn],a[maxn],cnt[maxn<<1],ccnt[maxn<<1],ans[maxn],flag[maxn<<1],top;
struct node{
	int l,r,ti,id; 
	bool operator<(const node ot)const{//比较函数，记得分块排序 
		return idx[l]==idx[ot.l]?(idx[r]==idx[ot.r]?ti<ot.ti:r<ot.r):l<ot.l;
	}
}p[maxn];
struct edon{int i,from,to;}c[maxn];//change修改数组 
void add(int x){
	--ccnt[cnt[x]];
	++ccnt[++cnt[x]];
}
void del(int x){
	--ccnt[cnt[x]];
	++ccnt[--cnt[x]];
}
int main() {
	qr(n),qr(m);
	s=pow(n,2.0/3);//块长 
	for(int i=1;i<=n;++i){
		qr(a[i]);
		idx[i]=(i+s-1)/s;
		flag[++top]=a[i];
	}
	for(int i=1;i<=m;++i){
		qr(Q);
		if(Q==1){
			++cntq;
			qr(p[cntq].l),qr(p[cntq].r);
			p[cntq].id=cntq;
			p[cntq].ti=cntr;
		}else{
			++cntr;
			qr(c[cntr].i),qr(c[cntr].to);
			c[cntr].from=a[c[cntr].i],a[c[cntr].i]=c[cntr].to,flag[++top]=c[cntr].to;//记得修改数组 
		}
	}
	for(int i=cntr;i>=1;--i) a[c[i].i]=c[i].from;//还原数组 
	sort(flag+1,flag+top+1);
	top=unique(flag+1,flag+top+1)-flag-1;//离散化 
	for(int i=1;i<=n;++i) a[i]=lower_bound(flag+1,flag+top+1,a[i])-flag;
	for(int i=1;i<=cntr;++i) c[i].from=lower_bound(flag+1,flag+top+1,c[i].from)-flag,c[i].to=lower_bound(flag+1,flag+top+1,c[i].to)-flag;
	sort(p+1,p+cntq+1);
	for(int i=1;i<=cntq;++i){//莫队板板，如果这都不会，你为什么要来做这道题呢？ 
		while(t>p[i].ti) {
			if(c[t].i>=l&&c[t].i<=r) add(c[t].from),del(c[t].to);
			a[c[t].i]=c[t--].from;
		}
		while(t<p[i].ti) {
			if(c[++t].i>=l&&c[t].i<=r) add(c[t].to),del(c[t].from);
			a[c[t].i]=c[t].to;
		}
		while(l>p[i].l) add(a[--l]);
		while(r<p[i].r) add(a[++r]);
		while(l<p[i].l) del(a[l++]);
		while(r>p[i].r) del(a[r--]);
		for(int j=1; ;++j){//暴力枚举 
			if(ccnt[j]==0){
				ans[p[i].id]=j;
				break;
			}
		}
	}
	for(int i=1;i<=cntq;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：KEBrantily (赞：1)

要查询的是区间中每个数字出现次数的 mex，考虑到这个 mex 的判断是基于出现次数的，所以我们维护每个数字的出现次数和每种出现次数对应的数字。

当删除或加入某个数时，我们将这个数对应的出现次数增减，同时将对应次数的数的个数也增减。

每次询问的答案不是在增减过程中求出，也无法在增减过程中求出。
处理完当前区间所有数对应的次数后，我们从小到大枚举次数，第一个出现的没有对应数字的次数就是当前询问的答案。

至于修改操作，则与普通带修莫队无异，可以看[这里](https://www.cnblogs.com/KnightL/p/14130517.html)，这里不多赘述。

```cpp
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 1000010
//#define int long long

using namespace std;

int a[maxn],b[maxn];
int n,m,Ans,len,L=1,R;
int all,cntq,cntc,Now,id;
int cnt[maxn],num[maxn],ans[maxn];
struct question{int l,r,t,now;}q[maxn];
struct change{int pos,val;}c[maxn];

int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<1)+(s<<3)+ch-'0',ch=getchar();
	return s*w;
}

bool cmp(question a,question b){
    return (a.l/len)^(b.l/len)?a.l<b.l:(a.r/len)^(b.r/len)?a.r<b.r:a.t<b.t;
}

void Add(int x){
    num[cnt[x]]--;
    num[++cnt[x]]++;
}

void Del(int x){
    num[cnt[x]]--;
    num[--cnt[x]]++;
}

void Modify(int ti,int x){
    if(c[ti].pos>=q[x].l&&c[ti].pos<=q[x].r)
        Del(a[c[ti].pos]),Add(c[ti].val);
    swap(a[c[ti].pos],c[ti].val);
}

int main(){
    n=read();m=read();len=pow(n,2.0/3);
    for(int i=1;i<=n;i++)b[++id]=a[i]=read();
    for(int i=1,opt;i<=m;i++){
        opt=read();
        if(opt==1){
            q[++cntq].l=read();q[cntq].r=read();
            q[cntq].t=cntc;q[cntq].now=cntq;
        }
        else c[++cntc].pos=read(),c[cntc].val=read();
    }
    sort(b+1,b+id+1);all=unique(b+1,b+id+1)-b-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+all+1,a[i])-b;
    sort(q+1,q+cntq+1,cmp);
    for(int i=1;i<=cntq;i++){
        while(L<q[i].l) Del(a[L++]);
        while(L>q[i].l) Add(a[--L]);
        while(R<q[i].r) Add(a[++R]);
        while(R>q[i].r) Del(a[R--]);
        while(Now<q[i].t) Modify(++Now,i);
        while(Now>q[i].t) Modify(Now--,i);
        for(ans[q[i].now]=1;num[ans[q[i].now]]>0;ans[q[i].now]++);
    }
    for(int i=1;i<=cntq;i++) printf("%d\n",ans[i]);
    return 0;
}
```


---

## 作者：hxdts (赞：1)

# 带修莫队+值域分块
值域分块是把值分块，进行查询，这样单次查询计数器就是$O(\sqrt n)$，与**普通莫队**单次移动复杂度差不多是**同级**的,虽然这题是求$mex$暴力复杂度也是$O(\sqrt n)$。

但由于做了[曼哈顿交易](https://www.luogu.com.cn/problem/P3730)，导致一开始就想到了值域分块+带修莫队。~~所以只要查询第k小的出现次数就可以卡掉暴力了~~
___

## 1.带修莫队
带修莫队就是普通莫队加一个时间指针，每次查询记录上一次修改的编号，
每次除了移动$l,r$指针以外再移动$pre$指针，就可以了。

### 1.1 奇偶排序
虽然这是带修莫队，但是个人在模板[[国家集训队]数颜色 / 维护队列](https://www.luogu.com.cn/problem/P1903)里面发现奇偶排序还是要比普通排序要快的~~别说是测评姬波动~~
根据[日报](https://www.luogu.com.cn/blog/codesonic/Mosalgorithm)所说：
> 这样能快是因为指针移到右边后不用再跳回左边，而跳回左边后处理下一个块又要跳回右边，这样能减少一半操作，理论上能快一倍

所以大部分莫队题我都用**奇偶排序**
```cpp
return l/size==x.l/size&&r/size==x.r/size?pre<x.pre:l/size^x.l/size?l<x.l:l/size&1?r<x.r:r>x.r;
```
### 1.2 块长
带修莫队玄学块长
```cpp
size=ceil(exp((log(n)+log(m))/3));
```
___
## 2.值域分块
除了计数器以外，再维护每一块的信息，每次上传计数器的同时上传块的信息，查询的时候如果整一块都不符合要求，就直接跳过。
___

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,z,size,v[100010],cnta,cntb,cnt[200010],ans[100010],sum1[10010]={1},sum2[100010]={1},q[200010],cnt2,len,r,w;
//sum2维护的是单点信息，sum1维护的是块信息 记得cnt开两倍！因为修改的个数加上原来数的个数会不只n个数调了半天 
char ch;
int read()
{
	ch=getchar(),r=0,w=1;
	while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
	while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
	return r*w;
}
struct ina
{
	int l,r,pre,id;
	bool operator<(const ina &x)const
	{
		return l/size==x.l/size&&r/size==x.r/size?pre<x.pre:l/size^x.l/size?l<x.l:l/size&1?r<x.r:r>x.r;
		//奇偶排序 
	}
}a[100010];
struct inb
{
	int wz,x;
}b[100010];
void insert(int x,int k)//值域分块插入 
{
	if(x<=0)
	return;
	sum2[x]+=k;
	if(sum2[x]==1&&k==1||!sum2[x]&&k==-1)
	sum1[x/100]+=k;
}
void add(int x)
{
	insert(cnt[v[x]],-1);
	insert(++cnt[v[x]],1);
}
void del(int x)
{
	insert(cnt[v[x]],-1);
	insert(--cnt[v[x]],1);
}
void change(int x,int l,int r)//带修莫队时间指针移动 
{
	if(b[x].wz>=l&&b[x].wz<=r)
	{
		del(b[x].wz);
		swap(b[x].x,v[b[x].wz]);
		add(b[x].wz);
		return;
	}
	swap(b[x].x,v[b[x].wz]);
}
int ask()//值域分块查询 
{
	int i;
	for(i=0;sum1[i]==100;i++);
	for(i=i*100;sum2[i];i++);
	return i;
}
int main()
{
	n=read(),m=read();
	size=ceil(exp((log(n)+log(m))/3));//带修莫队的玄学块长 
	for(int i=1;i<=n;i++)
	q[++cnt2]=v[i]=read();
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read(),z=read();
		if(x==1)
		a[++cnta]={y,z,cntb,cnta};
		else
		b[++cntb]={y,z},q[++cnt2]=z;
	}
	sort(q+1,q+cnt2+1);
	len=unique(q+1,q+cnt2+1)-q;
	for(int i=1;i<=n;i++)
	v[i]=lower_bound(q+1,q+len,v[i])-q;//离散化 
	for(int i=1;i<=cntb;i++)
	b[i].x=lower_bound(q+1,q+len,b[i].x)-q;
	sort(a+1,a+cnta+1);
	int left=1,right=0,now=0;
	for(int i=1;i<=cnta;i++)
	{
		int l=a[i].l,r=a[i].r,x=a[i].pre;
		while(l<left) add(--left);
		while(r>right) add(++right);
		while(l>left) del(left++);
		while(r<right) del(right--);
		while(now<x) change(++now,l,r);
		while(now>x) change(now--,l,r);
		ans[a[i].id]=ask();
	}
	for(int i=1;i<=cnta;i++)
	printf("%d\n",ans[i]);
}
```

---

## 作者：1saunoya (赞：1)

[Problem](https://codeforces.com/contest/940/problem/F)

给出 数组 $a\{\}$

$q$次操作

1、查询区间$l$ ~ $r$ 中每个数字`出现次数`的 $mex$
2、单点修改。

`出现次数的mex` 注意不是数值的 mex

$1 \leq a_i \leq 10^9$

考虑离散化 因为数字较大 $map$ 自带 $\log$ 和 大常数。。
然后用带修莫队维护的复杂度就会变成 $n^{5/3}* log n$
显然是跑不过去的。。

离散化有一个问题 就是你要把询问中的修改的数值也离散化

然后 用一个 $cntt_i$ 记录 $i$ 出现的次数 $tot_i$ 记录出现 $i$ 次的个数

带修莫队有一个时间戳 排序应该是按 $l$所在的块 -> $r$所在的块 -> 当前修改的时间戳。。

带修莫队的块大小应该是 $n^{2/3}$

对于这道题还有一个不太严谨的结论：求$mex$的复杂度每次扫一遍不会超过 $\sqrt n$

$n\sqrt n \le n^{5/3}$

```cpp
#include<bits/stdc++.h>
using namespace std ;
int n , Q ;
vector < int > v , b ;
const int N = 2e5 + 10 ;
int bl[N] ;
struct node { int l , r , id , t ; } q[N] ;
struct change { int x , val ; } c[N] ;
int tot[N] , cntt[N] ;
inline void add(int x) {
  -- tot[cntt[x]] ;
  ++ tot[++ cntt[x]] ;
}
inline void del(int x) {
  -- tot[cntt[x]] ;
  ++ tot[-- cntt[x]] ;
}
inline void modify(int now , int i) {
  if(q[i].l <= c[now].x && c[now].x <= q[i].r) {
    del(v[c[now].x]) ;
    add(c[now].val) ;
  } swap(v[c[now].x] , c[now].val) ;
}
int ans[N] ;
signed main() {
  ios :: sync_with_stdio(false) ;
  cin.tie(nullptr) ; cout.tie(nullptr) ;
  cin >> n >> Q ; int unt = pow(n , 2.0 / 3.0) ;
  for(register int i = 0 ; i < n ; i ++) { int x ; cin >> x ; v.push_back(x) ; }
  for(register int i = 0 ; i < n ; i ++) { b.push_back(v[i]) ; bl[i] = (i - 1) / unt + 1 ; }
  int cnt , cnt2 ; cnt = cnt2 = 0 ;
  for(register int i = 0 ; i < Q ; i ++) { int opt , x , y ; cin >> opt >> x >> y ;
    if(opt == 1) { ++ cnt ; q[cnt] = {-- x , -- y , cnt , cnt2} ; }
    if(opt == 2) { ++ cnt2 ; c[cnt2] = { -- x , y } ; b.push_back(y) ; }
  }
  sort(b.begin() , b.end()) ; b.erase(unique(b.begin() , b.end()) , b.end()) ;
  for ( int & x : v ) x = lower_bound(b.begin() , b.end() , x) - b.begin() ;
  for(register int i = 1 ; i <= cnt2 ; i ++) { c[i].val = lower_bound(b.begin() , b.end() , c[i].val) - b.begin() ; }
  sort(q + 1 , q + cnt + 1 , [] (node x , node y) {
    if(bl[x.l] ^ bl[y.l]) return x.l < y.l ;
    if(bl[x.r] ^ bl[y.r]) return x.r < y.r ;
    return x.t < y.t ;
  }) ;
  int l = 1 , r = 0 , now = 0 ;
  for(register int i = 1 ; i <= cnt ; i ++) {
    while(l > q[i].l) add(v[-- l]) ;
    while(r < q[i].r) add(v[++ r]) ;
    while(l < q[i].l) del(v[l ++]) ;
    while(r > q[i].r) del(v[r --]) ;
    while(now < q[i].t) modify(++ now , i) ;
    while(now > q[i].t) modify(now -- , i) ;
    for(ans[q[i].id] = 1 ; tot[ans[q[i].id]] > 0 ; ++ ans[q[i].id]) ;
  } for(register int i = 1 ; i <= cnt ; i ++) cout << ans[i] << '\n' ;
  return 0 ;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定 $n$ 个数的序列 $a$，有 $m$ 次操作，每次操作有单点修改和询问区间 $a_l, a_{l+1}, \cdots, a_r$ 中每个数的出现次数的 mex。

## 解法

考虑莫队维护。

我们要维护 mex，并且是带修莫队，所以回滚莫队用不了。我们考虑在获得答案时暴力。

考虑维护两个数组，分别是 $ca$ 和 $cb$，$ca$ 记录每个数出现次数，$cb$ 记录每个 $ca$ 的出现次数。

询问答案时从 $1$ 到 $\infty$ 暴力枚举，复杂度是可以接受的。

代码：

```cpp
#pragma GCC optimize("-Ofast")
#pragma GCC target("avx,sse,sse2,sse3,sse4")
#pragma unroll 10
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

const int N = 2e5 + 10;

int a[N], len, ans[N];
vector<int> b;

int n, m, cnta, cntb;

int ca[N], cb[N];

struct Query
{
	int id, l, r, k;
}q[N];

struct Modify
{
	int x, y;
}g[N];

inline int read()
{
	register char ch = getchar();
	register int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x;
}

inline bool cmp(const Query& x, const Query& y)
{
	register int xl = x.l / len, xr = x.r / len;
	register int yl = y.l / len, yr = y.r / len;
	if (xl ^ yl) return xl < yl;
	if (xr ^ yr) return xr < yr;
	return x.k < y.k;
}

inline void add(int x)
{
	--cb[ca[a[x]]];
	++cb[++ca[a[x]]];
}

inline void del(int x)
{
	--cb[ca[a[x]]];
	++cb[--ca[a[x]]];
}

inline void change(int x, int l, int r)
{
	int rem = 0;
	if (g[x].x >= l && g[x].x <= r)
	{
		--cb[ca[a[g[x].x]]];
		++cb[--ca[a[g[x].x]]];
		--cb[ca[g[x].y]];
		++cb[++ca[g[x].y]];
	}
	swap(a[g[x].x], g[x].y);
}

int main()
{
	n = read();
	m = read();
	for (register int i = 1; i <= n; ++i)
	{
		a[i] = read();
		b.push_back(a[i]);
	}
	for (register int i = 1; i <= m; ++i)
	{
		register int opt = read(), l = read(), r = read();
		if (opt == 1)
		{
			++cnta;
			q[cnta] = { cnta, l, r, cntb };
		}
		else
		{
			++cntb;
			b.push_back(r);
			g[cntb] = { l, r };
		}
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	for (register int i = 1; i <= n; ++i)
	{
		a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
	}
	for (register int i = 1; i <= cntb; ++i)
	{
		g[i].y = lower_bound(b.begin(), b.end(), g[i].y) - b.begin();
	}
	len = pow(n, 2.0 / 3);
	sort(q + 1, q + cnta + 1, cmp);
	register int nl = 1, nr = 0, now = 0;
	for (register int i = 1; i <= cnta; ++i)
	{
		int l = q[i].l, r = q[i].r, k = q[i].k, ansk = 0;
		while (nl < l) del(nl++);
		while (nl > l) add(--nl);
		while (nr < r) add(++nr);
		while (nr > r) del(nr--);
		while (now < k) change(++now, l, r);
		while (now > k) change(now--, l, r);
		for (register int j = 1; ; ++j)
		{
			if (!cb[j])
			{
				ansk = j;
				break;
			}
		}
		ans[q[i].id] = ansk;
	}
	for (register int i = 1; i <= cnta; ++i) printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：gyyyyx (赞：0)

# Machine Learning 题解

前置芝士：[带修莫队](https://www.luogu.com.cn/blog/s19418/mu-dui-xue-xi-bi-ji)

首先看到这题是区间问题，第一个想到线段树。但是看到了要求mex，立刻否定此想法。

一般的mex都是用莫队做的，所以考虑用莫队。

看到有修改那肯定是带修莫队。

但是莫队求mex一般是用回滚莫队，难道要用“带修回滚莫队”（什么鬼）？

但是看到是求这个区间里数字出现次数的mex，感觉有蹊跷。

想想暴力如何求mex，枚举每个数，看看出现没有，知道这个数没有就输出。

假设mex最大取 $x$，显然数字最多有 $\frac{x(x+1)}{2}$ 个（即类似这样的数列：$1223334444...$）。

因为数列大小 $n\leq 10^5$，所以 $\frac{x(x+1)}{2}\leq 10^5$，那 $x$ 应该是 $\sqrt{n}$ 级别的。

那枚举的话就要枚举 $\sqrt{n}$ 次，时间复杂度就是 $O(n^\frac{5}{3}+n^\frac{2}{3})=O(n^\frac{5}{3})$，能在规定时间内运行。

于是代码就来咯：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 100005
int n,m,a[N],h[N<<1],len;
struct Query{int l,r,pre,id;} q[N];
struct Change{int p,c;} c[N];
int qnum,cnum;
int block,pos[N];
int cnt[N<<1],cnt2[N<<1],l,r,t;
int res,ans[N];
#undef N

inline int read(){
    int x(0),y(1);
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*y;
}

inline void Hash(){
    sort(h+1,h+1+len);len=unique(h+1,h+1+len)-h-1;
    for(int i(1);i<=n;++i) a[i]=lower_bound(h+1,h+1+len,a[i])-h;
    for(int i(1);i<=cnum;++i) c[i].c=lower_bound(h+1,h+1+len,c[i].c)-h;
}
inline void Add(int x){
    --cnt2[cnt[x]];
    ++cnt2[++cnt[x]];
}
inline void Del(int x){
    --cnt2[cnt[x]];
    ++cnt2[--cnt[x]];
}
inline void Update(int x){
    if(c[x].p>=l&&c[x].p<=r){
        Add(c[x].c);
        Del(a[c[x].p]);
    }
    swap(c[x].c,a[c[x].p]);
}
inline void Setblock(){
    block=pow(n,2.0/3.0);
    for(int i(1);i<=n;++i) pos[i]=(i-1)/block+1;
}
inline bool cmp(const Query& a,const Query& b){
    if(pos[a.l]!=pos[b.l]) return pos[a.l]<pos[b.l];
    if(pos[a.r]!=pos[b.r]) return pos[a.l]&1?pos[a.r]<pos[b.r]:pos[a.r]>pos[b.r];
    return pos[a.r]&1?a.pre<b.pre:a.pre>b.pre;
}
inline void Solve(){
    sort(q+1,q+1+qnum,cmp);
    for(int i(1);i<=qnum;++i){
        while(l<q[i].l) Del(a[l++]);
        while(r<q[i].r) Add(a[++r]);
        while(l>q[i].l) Add(a[--l]);
        while(r>q[i].r) Del(a[r--]);
        while(t<q[i].pre) Update(++t);
        while(t>q[i].pre) Update(t--);
        for(res=1;cnt2[res];++res);
        ans[q[i].id]=res;
    }
    for(int i(1);i<=qnum;++i) cout<<ans[i]<<endl;
}

int main(){
    n=read();m=read();
    for(int i(1);i<=n;++i) a[i]=h[++len]=read();
    for(int i(1);i<=m;++i){
        int op;cin>>op;
        if(op==1){
            ++qnum;
            q[qnum].l=read();q[qnum].r=read();
            q[qnum].pre=cnum;
            q[qnum].id=qnum;
        } else{
            ++cnum;
            c[cnum].p=read();c[cnum].c=read();
            h[++len]=c[cnum].c;
        }
    }
    Hash();
    Setblock();
    Solve();
    return 0;
}
```

---

## 作者：智子 (赞：0)

## 思路

一道带修莫队模板题。

看到题意中“单点修改，区间查询数字出现次数 $mex$” 的操作后，不难想到用带修莫队维护，但时间复杂度的正确性需要证明。

假设区间当前区间的 $mex$ 为 $n$，则这个区间的数的个数至少为 

$$\sum\limits_{i = 1}^{n}i = \dfrac{n(n + 1)}{2}$$

所以任何区间的答案肯定在 $O(\sqrt{n})$ 级别，可以直接暴力查找 $mex$。

代码中也有一些要注意的细节：$x_i$ 最大可以为 $10^9$，所以序列中的数和修改中的数都必须离散化。

统计时开两个数组，一个数组 `cnt` 统计每个数出现了几次，`tot` 统计这个出现次数出现了几次。由于 `add` 和 `del` 操作都会使 `tot` 数组改变两次，所以每次操作都要更新两遍 $mex$。具体操作如下：

```cpp
void add(int x) {
    tot[cnt[x]]--;
    if(tot[cnt[x]] == 0) {
        mex = min(mex, cnt[x]); //可能出现了更小的答案
    }
    cnt[x]++;
    tot[cnt[x]]++;
    if(tot[cnt[x]] == 1 && mex == cnt[x]) { //当前答案已经出现，向上寻找符合要求的 mex
        for(int i = mex; i <= siz; i++) {
            if(tot[i + 1] == 0) {
                mex = i + 1;
                break;
            }
        }
    }
}

void del(int x) {
    tot[cnt[x]]--;
    if(tot[cnt[x]] == 0) {
        mex = min(mex, cnt[x]); //可能出现了更小的答案
    }
    cnt[x]--;
    tot[cnt[x]]++;
    if(tot[cnt[x]] == 1 && mex == cnt[x]) { //当前答案已经出现，向上寻找符合要求的 mex
        for(int i = mex; i <= siz; i++) {
            if(tot[i + 1] == 0) {
                mex = i + 1;
                break;
            }
        }
    }
}
```

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, t, id;
};

struct Change {
    int pos, v;
};

const int MAXN = 100000 * 2 + 5;

Query q[MAXN];
Change c[MAXN];
int v[MAXN], cnt[MAXN], tot[MAXN], ans[MAXN], a[MAXN];
int cntQ, cntC;
int n, m, t, siz, mex = 1;

bool cmp(Query& a, Query& b) {
    if(a.l / t != b.l / t) {
        return a.l < b.l;
    }
    if(a.r / t != b.r / t) {
        return a.r < b.r;
    }
    return a.t < b.t;
}

void add(int x) {
    tot[cnt[x]]--;
    if(tot[cnt[x]] == 0) {
        mex = min(mex, cnt[x]);
    }
    cnt[x]++;
    tot[cnt[x]]++;
    if(tot[cnt[x]] == 1 && mex == cnt[x]) {
        for(int i = mex; i <= siz; i++) {
            if(tot[i + 1] == 0) {
                mex = i + 1;
                break;
            }
        }
    }
}

void del(int x) {
    tot[cnt[x]]--;
    if(tot[cnt[x]] == 0) {
        mex = min(mex, cnt[x]);
    }
    cnt[x]--;
    tot[cnt[x]]++;
    if(tot[cnt[x]] == 1 && mex == cnt[x]) {
        for(int i = mex; i <= siz; i++) {
            if(tot[i + 1] == 0) {
                mex = i + 1;
                break;
            }
        }
    }
}

void modify(int i, int t) {
    if(q[i].l <= c[t].pos && c[t].pos <= q[i].r) {
        del(a[c[t].pos]);
        add(c[t].v);
    }
    swap(a[c[t].pos], c[t].v);
}

int main() {
    scanf("%d%d", &n, &m);
    t = pow(n, 2.0 / 3);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        v[++siz] = a[i];
    }
    for(int i = 1; i <= m; i++) {
        int op;

        scanf("%d", &op);
        if(op == 1) {
            cntQ++;
            scanf("%d%d", &q[cntQ].l, &q[cntQ].r);
            q[cntQ].t = cntC;
            q[cntQ].id = cntQ;
        } else {
            cntC++;
            scanf("%d%d", &c[cntC].pos, &c[cntC].v);
            v[++siz] = c[cntC].v;
        }
    }
    sort(v + 1, v + siz + 1);
    siz = unique(v + 1, v + siz + 1) - (v + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = lower_bound(v + 1, v + siz + 1, a[i]) - v;
    }
    for(int i = 1; i <= cntC; i++) {
        c[i].v = lower_bound(v + 1, v + siz + 1, c[i].v) - v;
    }
    sort(q + 1, q + cntQ + 1, cmp);
    int l = 1, r = 0, t = 0;
    for(int i = 1; i <= cntQ; i++) {
        while(l > q[i].l) add(a[--l]);
        while(r < q[i].r) add(a[++r]);
        while(l < q[i].l) del(a[l++]);
        while(r > q[i].r) del(a[r--]);
        while(t < q[i].t) modify(i, ++t);
        while(t > q[i].t) modify(i, t--);
        ans[q[i].id] = mex;
    }
    for(int i = 1; i <= cntQ; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}

```

---

## 作者：轻绘 (赞：0)

# 题意

 询问区间内 **最小** 未出现的**数字次数**
 
 具体可看下文中 $cnt$ 数组定义

# 算法

普通的带修莫队，再维护一个区间内出现相同次数的数字个数。

[题目传送门](https://www.luogu.com.cn/problem/CF940F)

[个人博客](https://www.luogu.com.cn/blog/yanhangyn/)

# 具体思路

带修莫队的基本常识在此不再赘述。

[关于莫队很好的一篇博客](https://www.cnblogs.com/WAMonster/p/10118934.html)

当我们再移动 $l,r$ 时，对于要新加入区间数，我们要修改两个数组。

1. $used$ 数组，该数组用于统计区间 $[l,r]$ 之间数字 $i$ 出现的次数。

2. $cnt$ 数组，该数组用于统计区间 $[l,r]$ 之间出现 $j$ 次的数字个数。

如在 $ 1,2,3,1,1,2,2,2,9,9$ 数列中，当 $l=2,r=8$ 时

$used[1]=2$，$used[2]=4$，$used[3]=1$，$used[4]=0$，
$used[5]=0$，$used[6]=0$，$used[7]=0$，$used[8]=0$，$used[9]=0$ $......$

$cnt[1]=1$，$cnt[2]=1$，$cnt[3]=0$，$cnt[4]=1$，$cnt[5]=0$ $......$

而此时在 $cnt$ 中 “最小的未出现的自然数” 就是 $3$ 

# 如何维护

首先对所有输入的数据进行离散化，包括原数列，要修改的数。

**对于 $used$ 数组**，和普通莫队一样维护

```cpp
while(r<b[o].r)	ans+=!used[a[++r]]++;
while(r>b[o].r)	ans-=!--used[a[r--]];
while(l<b[o].l)	ans-=!--used[a[l++]];
while(l>b[o].l)	ans+=!used[a[--l]]++;
```

**对于 $cnt$ 数组** 

假设原本序列中有 $k$ 个数等于 $a_i$
,那么

**当一个数 $a_i$ 加进来时，**

$cnt[k]--$

$cnt[k+1]++ $

**减去一个 $a_i$ 时**

$cnt[k+1]--$

$cnt[k]++$ 

代码见下

```cpp
while(r<b[o].r)	--cnt[used[a[r+1]]],++cnt[used[a[r+1]]+1];
while(r>b[o].r)	--cnt[used[a[r]]],++cnt[used[a[r]]-1];
while(l<b[o].l)	--cnt[used[a[l]]],++cnt[used[a[l]]-1];
while(l>b[o].l)	--cnt[used[a[l-1]]],++cnt[used[a[l-1]]+1];
```
**对于时间 $t$ 维护**，

因为改变 $t$ 而修改一个数时，先判断该数是不是在 $[l,r]$ 之间

若不在，则直接修改

本处将原数与要改成的数交换，因为将时间倒回时，要将数还原。具体可以自己代入分析。

**若在区间内**

修改一个数等于减去一个数，再加上一个数

则重复类似上面对于 $cnt$ 的操作，先减去被修改数，再加上改成的数。

**注：$c[i].num$ 代表要修改数位置， $c[i].col$ 代表要改成的数**

```cpp
int nnn=c[tim].num;
--cnt[used[a[nnn]]];
++cnt[used[a[nnn]]-1];
ans-=!--used[a[nnn]];
swap(a[nnn],c[tim].col);
--cnt[used[a[nnn]]];
++cnt[used[a[nnn]]+1];
ans+=!used[a[nnn]]++;
```

**综上所述 关键代码为**：

```cpp
while(p--){
	while(r<b[o].r)	--cnt[used[a[r+1]]],++cnt[used[a[r+1]]+1],ans+=!used[a[++r]]++;
	while(r>b[o].r)	--cnt[used[a[r]]],++cnt[used[a[r]]-1],ans-=!--used[a[r--]];
	while(l<b[o].l)	--cnt[used[a[l]]],++cnt[used[a[l]]-1],ans-=!--used[a[l++]];
	while(l>b[o].l)	--cnt[used[a[l-1]]],++cnt[used[a[l-1]]+1],ans+=!used[a[--l]]++;
	while(tim<b[o].t){
		if(c[++tim].num>=b[o].l && c[tim].num<=b[o].r){
			int nnn=c[tim].num;
			--cnt[used[a[nnn]]];
			++cnt[used[a[nnn]]-1];
			ans-=!--used[a[nnn]];
			swap(a[nnn],c[tim].col);
			--cnt[used[a[nnn]]];
			++cnt[used[a[nnn]]+1];
			ans+=!used[a[nnn]]++;
		}
		else	swap(a[c[tim].num],c[tim].col);
	}
	while(tim>b[o].t){
		if(c[tim].num>=b[o].l && c[tim].num<=b[o].r){
			int nnn=c[tim].num;
			--cnt[used[a[nnn]]];
			++cnt[used[a[nnn]]-1];
			ans-=!--used[a[nnn]];
			swap(a[nnn],c[tim].col);
			--cnt[used[a[nnn]]];
			++cnt[used[a[c[tim--].num]]+1];
			ans+=!used[a[nnn]]++;
		}
		else	swap(a[c[tim].num],c[tim].col),tim--;
	}
	int c=0;
	while(cnt[++c]);
	la[b[o].num]=c,++o;
}	
```
**部分说明：$d$ 数组，$cha$ 等用于离散化**

代码较丑，各位见谅

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar(); 
	while(!isdigit(ch)){
		if(ch=='-')	f=-1;
		ch=getchar(); 
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int n,m,q;
int a[200000];
int used[200000],cnt[200000];
struct node{
	int l,r,num,lk,rk,t;
}b[200000];
struct node2{
	int num,col;	
}c[200000];
struct node3{
	bool f;
	int v,num;
}d[500000];
inline bool cmp2(node3 x,node3 y){
	return x.v<y.v;
}
inline bool cmp(node x,node y){
	if(x.lk==y.lk){
		if(x.rk==y.rk)	return x.t<y.t;
		return x.rk<y.rk;
	} 
	return x.lk<y.lk;
}
int la[200000];
int l,r,ans,o=1,pro,cha,tim,tot;
int main(){
	n=read(),m=2500,q=read();
	for(register int i=1;i<=n;++i)
		d[i].v=read(),d[i].f=1,d[i].num=i;
	for(register int i=1;i<=q;++i){
		int z;
		int x,y;
		z=read();
		x=read(),y=read();
		if(z==1){
			++pro;
			b[pro].l=x;
			b[pro].r=y;
			b[pro].lk=(b[pro].l-1)/m+1;
			b[pro].rk=(b[pro].r-1)/m+1;
			b[pro].num=pro; 
			b[pro].t=cha;
		} 
		else{
			++cha;
			c[cha].num=x;
			c[cha].col=y;
			d[n+cha].v=y;
			d[n+cha].f=0;
			d[n+cha].num=cha;
		}
	}
	sort(d+1,d+n+cha+1,cmp2);
	for(int i=1;i<=n+cha;++i){
		if(d[i-1].v!=d[i].v)	++tot;
		if(d[i].f)
			a[d[i].num]=tot;
		else
			c[d[i].num].col=tot;
	}
	sort(b+1,b+pro+1,cmp);
	l=b[1].l,r=b[1].l-1;
	int p=pro;
	while(p--){
		while(r<b[o].r)	--cnt[used[a[r+1]]],++cnt[used[a[r+1]]+1],ans+=!used[a[++r]]++;
		while(r>b[o].r)	--cnt[used[a[r]]],++cnt[used[a[r]]-1],ans-=!--used[a[r--]];
		while(l<b[o].l)	--cnt[used[a[l]]],++cnt[used[a[l]]-1],ans-=!--used[a[l++]];
		while(l>b[o].l)	--cnt[used[a[l-1]]],++cnt[used[a[l-1]]+1],ans+=!used[a[--l]]++;
		while(tim<b[o].t){
			if(c[++tim].num>=b[o].l && c[tim].num<=b[o].r){
				int nnn=c[tim].num;
				--cnt[used[a[nnn]]];
				++cnt[used[a[nnn]]-1];
				ans-=!--used[a[nnn]];
				swap(a[nnn],c[tim].col);
				--cnt[used[a[nnn]]];
				++cnt[used[a[nnn]]+1];
				ans+=!used[a[nnn]]++;
			}
			else	swap(a[c[tim].num],c[tim].col);
		}
		while(tim>b[o].t){
			if(c[tim].num>=b[o].l && c[tim].num<=b[o].r){
				int nnn=c[tim].num;
				--cnt[used[a[nnn]]];
				++cnt[used[a[nnn]]-1];
				ans-=!--used[a[nnn]];
				swap(a[nnn],c[tim].col);
				--cnt[used[a[nnn]]];
				++cnt[used[a[c[tim--].num]]+1];
				ans+=!used[a[nnn]]++;
			}
			else	swap(a[c[tim].num],c[tim].col),tim--;
		}
		int c=0;
		while(cnt[++c]);
		la[b[o].num]=c,++o;
	}	
	for(register int i=1;i<=pro;i++)	printf("%d\n",la[i]);
	return 0;
}
```


---

## 作者：moosssi (赞：0)

这道题带修莫队+离散化（一开始，我懒得打离散化，用的map但超时了。。。）

带修莫队的模板这里不再赘述，主要考虑$add$，$del$这两个函数还有答案如何记录。
这个$mex$我看了好一会才弄明白是什么，就用样例举例：对于第二查询，出现了1个3，2个1和4个2，每个数出现的次数中，3是未出现的最小自然数，这就是样例的由来。我们就可以定两个数组$cnt[i]$,表示$i$这个数出现了多少次，$dcnt[i]$,表示出现i次的次数是多少（这里需要仔细思考），后具操作见代码。

找答案时，可以暴力从一开始枚举，最坏的情况会枚举$\sqrt{n}$次,具体证明不再赘述。

最后记得加上离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int a[N],dt[N],ans[N];
int mc,mq,len,n,m;
int b[2*N],dc;
int cnt[2*N],dcnt[2*N];
struct nod{
	int id,l,r,t;
}q[N];
struct chang{
	int p,c;
}ch[N];
bool cmp(const nod& x,const nod& y){
	int xl=dt[x.l],xr=dt[x.r];
	int yl=dt[y.l],yr=dt[y.r];
	if(xl!=yl)return xl<yl;
	if(xr!=yr)return xr<yr;
	return x.t<y.t;
}
int find(){
	int i=1;
	while(i){
		if(!dcnt[i])return i;
		i++;
	}
}
void add(int x){//更新区间cnt和dcnt的值，这里需要仔细体会 
	dcnt[cnt[x]]--;
	cnt[x]++;
	dcnt[cnt[x]]++;
}
void del(int x){
	dcnt[cnt[x]]--;
	cnt[x]--;
	dcnt[cnt[x]]++;
}
int main(){
	scanf("%d%d",&n,&m);
	len=pow(n,2.0/3);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		dt[i]=(i-1)/len+1;
		b[++dc]=a[i]; 
	}
	int x,y,z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&z,&x,&y);
		if(z==1)mq++,q[mq].id=mq,q[mq].t=mc,q[mq].l=x,q[mq].r=y;
		else mc++,ch[mc].p=x,b[++dc]=ch[mc].c=y;
	}
	sort(b+1,b+dc+1);//离散化 
	int le=unique(b+1,b+dc+1)-b-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+le+1,a[i])-b;	
	for(int i=1;i<=mc;i++){
		ch[i].c=lower_bound(b+1,b+le+1,ch[i].c)-b;
	}
	sort(q+1,q+mq+1,cmp);
	int l=1,r=0,t=0;
	for(int i=1;i<=mq;i++){//带修莫队模板 
		while(l>q[i].l)add(a[--l]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		while(r<q[i].r)add(a[++r]);
		while(t<q[i].t){
			t++;
			if(ch[t].p>=l&&ch[t].p<=r){
				del(a[ch[t].p]);
				add(ch[t].c);
			}
			swap(ch[t].c,a[ch[t].p]);			
		}
		while(t>q[i].t){
			if(ch[t].p>=l&&ch[t].p<=r){
				del(a[ch[t].p]);
				add(ch[t].c);
			}
			swap(ch[t].c,a[ch[t].p]);
			t--;
		}
		ans[q[i].id]=find();//暴力枚举答案 
	}
	for(int i=1;i<=mq;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```




---

## 作者：Demoe (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF940F)

## 题意

- 给定一个序列，有两种操作。

- 第一种 修改某位数值。

- 第二种 查询区间内各数的出现次数之中最小的没出现过的正数（显然 $0$ 不可能存在）。

## Sol

带修莫队模板。

因为可以发现每个值具体是啥没啥用，我们关注的是它的**出现次数**。

所以需要**离散化**，不然会 $\text{MLE}$。

修改操作寻常，记录时间维度即可。

我们考虑查询操作。

我们发现在每一次修改时，我们没办法 $O(1)$ 更新答案。/kk

比如 $\text{1 0 1 1 0} \to \text{1 1 1 1 0}$。

那么我们考虑在所有修改及移动完成后，在最后暴力求答案。

就是 $1$ 开始枚举，一直枚举到第一个满足要求的数。

听上去是不是特别暴力。（就是这么暴力

我们来分析每次的复杂度。

对于每个出现次数，我们考虑**最劣情况**，发现一种出现次数只有 $1$ 个才是最劣的。

通过这个 $\sum\limits^{\sqrt n}_{i=1}i=\dfrac{\sqrt n \times (\sqrt{n}+1)}{2}$ 删去常数后约为 $n$。

可得答案严格小于 $\sqrt {2n}$，约为 $\sqrt n$。

那么一次求答案复杂度最高即为 $\sqrt n$。

那么最终复杂度即为 $O(n^{\frac{5}{3}}+m\sqrt n)$。

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
#define re register int
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,m,ans[N],a[N],l=1,r,len,cnt[N],nw,qaq,qwq,lsh[N],cntcnt[N];
struct Question{int id,l,r,pl,pr,t;}q[N];
struct change{int x,to,pre;}mo[N];
template <typename T> inline void rd(T &x){
	int fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(int x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
inline bool cmp(Question x,Question y){
	if(x.pl^y.pl) return x.pl<y.pl;
	if(x.pr^y.pr) return x.pr<y.pr;
	return x.t<y.t; 
}
inline void update(int x,int op){
	cntcnt[cnt[a[x]]]--,cnt[a[x]]+=op,cntcnt[cnt[a[x]]]++;
}
inline void modify(int x,int op){
	if(mo[x].x>=l&&mo[x].x<=r){
		if(op==1){
			cntcnt[cnt[a[mo[x].x]]]--;
			cnt[a[mo[x].x]]--;
			cntcnt[cnt[a[mo[x].x]]]++;
			mo[x].pre=a[mo[x].x];a[mo[x].x]=mo[x].to;
			cntcnt[cnt[a[mo[x].x]]]--;
			cnt[a[mo[x].x]]++;
			cntcnt[cnt[a[mo[x].x]]]++;
		}
		else{
			cntcnt[cnt[a[mo[x].x]]]--;
			cnt[a[mo[x].x]]--;
			cntcnt[cnt[a[mo[x].x]]]++;
			a[mo[x].x]=mo[x].pre;
			cntcnt[cnt[a[mo[x].x]]]--;
			cnt[a[mo[x].x]]++;
			cntcnt[cnt[a[mo[x].x]]]++;
		}
	}
	else{
		if(op==1) mo[x].pre=a[mo[x].x],a[mo[x].x]=mo[x].to;
		else a[mo[x].x]=mo[x].pre;
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0);
	rd(n);rd(m);
	len=(int)pow(n,2./3.);
	for(re i=1;i<=n;i++) rd(a[i]),lsh[i]=a[i];
	for(re i=1;i<=m;i++){
		int op;rd(op);
		if(op==2) ++qaq,rd(mo[qaq].x),rd(mo[qaq].to),lsh[qaq+n]=mo[qaq].to;
		else if(op==1) ++qwq,rd(q[qwq].l),rd(q[qwq].r),q[qwq].id=qwq,q[qwq].pl=(q[qwq].l-1)/len+1,q[qwq].pr=(q[qwq].r-1)/len+1,q[qwq].t=qaq;
	}
	sort(q+1,q+qwq+1,cmp);sort(lsh+1,lsh+n+qaq+1);
	ll awa=unique(lsh+1,lsh+n+qaq+1)-lsh-1;
	for(re i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+awa+1,a[i])-lsh;
	for(re i=1;i<=qaq;i++) mo[i].to=lower_bound(lsh+1,lsh+awa+1,mo[i].to)-lsh; 
	for(re i=1;i<=qwq;i++){
		while(l>q[i].l) --l,update(l,1);
		while(r<q[i].r) ++r,update(r,1);
		while(l<q[i].l) update(l,-1),l++;
		while(r>q[i].r) update(r,-1),r--;
		while(nw<q[i].t) ++nw,modify(nw,1);
		while(nw>q[i].t) modify(nw,-1),nw--;
		for(re k=1;k<N;k++)
			if(cntcnt[k]==0){
				ans[q[i].id]=k;
				break;
			}
	}
	for(re i=1;i<=qwq;i++) wr(ans[i]),puts("");
	return 0;
}
```

---

## 作者：Bosun (赞：0)

这是一道带修莫队的模板题，具体细节不再赘述，但是有一些实现时候的技巧要注意一下。

对于每次的时光倒流、推移操作，首先得放在区间移动后面做(因为放在前面做改的就是上一个区间的值，但是修改对它是没有影响的)。网上有一种广为流传的做法是：swap(原值，修改值)
这样的话推移一次再倒流回来，结果是一样的。

还有，对于mex操作复杂度的证明，我有一种感性想法:Σmex[i]=n,并且对于每次移动区间，修改的mex[i]都不会很多，所以我认为mex[i]最后会趋近于平均化，也就是sqrt(n)级别的

code：
```cpp
#include <bits/stdc++.h>   
#define N 300005    
#define ll long long  
#define setIO(s) freopen(s".in","r",stdin) 
using namespace std;      
int n,m,tot,opcnt,qcnt,B,now;          
int a[N],A[N],output[N],cnt[N],mex[N];            
struct query
{
    int l,r,id,t;    
    query(int l=0,int r=0):l(l),r(r){} 
    bool operator<(query b) const 
    {
        return l/B==b.l/B?(r/B==b.r/B?t<b.t:r<b.r):l<b.l;       
    }
}q[N]; 
struct change
{
    int p,x;   
    change(int p=0,int x=0):p(p),x(x){}  
}c[N];   
void add(int num) 
{     
    --mex[cnt[num]];           
    ++mex[++cnt[num]];         
}
void del(int num) 
{   
    --mex[cnt[num]];  
    ++mex[--cnt[num]];             
}
void update(int id,int t) 
{
    if(c[t].p>=q[id].l&&c[t].p<=q[id].r) 
    {
        del(a[c[t].p]);  
        add(c[t].x);        
    }   
    swap(c[t].x, a[c[t].p]);     
}
int getans() 
{
    int i,j; 
    for(i=1;mex[i]>0;++i);   
    return i;    
}
int main() 
{ 
    int i,j,l=2,r=1;       
    // setIO("input");       
    scanf("%d%d",&n,&m);   
    B=pow(n,0.6666);   
    for(i=1;i<=n;++i) 
    {
        scanf("%d",&a[i]); 
        A[++tot]=a[i];   
    }
    for(i=1;i<=m;++i) 
    {
        int op,a,b;    
        scanf("%d%d%d",&op,&a,&b);    
        if(op==1) 
        {
            ++qcnt;       
            q[qcnt]=query(a,b);  
            q[qcnt].id=qcnt; 
            q[qcnt].t=opcnt;   
        }
        else 
        {
            ++opcnt;   
            c[opcnt]=change(a,b);    
            A[++tot]=b;     
        }
    }
    sort(A+1,A+1+tot);   
    for(i=1;i<=n;++i) a[i]=lower_bound(A+1,A+1+tot,a[i])-A;     
    for(i=1;i<=opcnt;++i) c[i].x=lower_bound(A+1,A+1+tot,c[i].x)-A;       
    sort(q+1,q+1+qcnt);    
    for(i=1;i<=qcnt;++i) 
    {
        for(;l>q[i].l;) add(a[--l]);     
        for(;r<q[i].r;) add(a[++r]);   
        for(;l<q[i].l;) del(a[l++]);   
        for(;r>q[i].r;) del(a[r--]);   
        for(;now<q[i].t;) update(i, ++now);     
        for(;now>q[i].t;) update(i, now--);   
        output[q[i].id]=getans();    
    }
    for(i=1;i<=qcnt;++i) printf("%d\n",output[i]);   
    return 0;     
}
```


---

