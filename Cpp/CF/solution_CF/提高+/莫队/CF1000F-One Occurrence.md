# One Occurrence

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$，以及 $q$ 个查询。第 $i$ 个查询由两个整数 $l_i$ 和 $r_i$ 表示。对于每个查询，你需要在数组 $a$ 的第 $l_i$ 到第 $r_i$ 个位置（即子数组 $a[l_i], a[l_i+1], \dots, a[r_i]$）中，找出任意一个恰好出现一次的整数。如果不存在这样的整数，则输出 $0$。

例如，若 $a = [1, 1, 2, 3, 2, 4]$，对于查询 $(l_i = 2, r_i = 6)$，对应的子数组为 $[1, 2, 3, 2, 4]$，可能的答案有 $1$、$3$ 和 $4$；对于查询 $(l_i = 1, r_i = 2)$，对应的子数组为 $[1, 1]$，没有任何元素恰好出现一次。

你能回答所有的查询吗？

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
1 1 2 3 2 4
2
2 6
1 2
```

### 输出

```
4
0
```

# 题解

## 作者：feecle6418 (赞：34)

这题用莫队的话，显然要尽量减少移动指针的常数。Nacly_Fish 的做法需要卡常，是因为没有平衡好移动指针和查询的常数。

考虑值域分块维护，这样查询变为 $O(\sqrt{n})$，但是移动指针常数大大减小，只需要在块内做一次修改即可，因此快了不少，完全不需卡常（scanf 读入）就能过。我的块大小设的 1000。

简短的代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[500005],cnt[500005],bel[500005],ans[500005],st[5005],ed[5005],sum[5005];
struct Query{
	int l,r,id;
	bool operator <(const Query y) const {
		return bel[l]!=bel[y.l]?bel[l]<bel[y.l]:(bel[l]&1?r<y.r:r>y.r);
	}
}q[500005];
int Q(){
	for(int i=bel[500000];i;i--){
		if(!sum[i])continue;
		for(int j=ed[i];bel[j]=i;j--)if(cnt[j]==1)return j;
	}
	return 0;
}
void Add(int x){
	if(cnt[x]==1)sum[bel[x]]--;
	if(cnt[x]==0)sum[bel[x]]++;
	cnt[x]++;
}
void Del(int x){
	if(cnt[x]==1)sum[bel[x]]--;
	if(cnt[x]==2)sum[bel[x]]++;
	cnt[x]--;
}
int main(){
	scanf("%d",&n);
	for(int i=1,c=1000;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(int i=1,c=1000;i<=500000;i++)bel[i]=i/c+1,ed[bel[i]]=i;
	for(int i=1;i<=m;i++)scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1);
	int nowl=1,nowr=0;
	for(int i=1;i<=m;i++){
		while(nowl<q[i].l)Del(a[nowl++]);
		while(nowl>q[i].l)Add(a[--nowl]);
		while(nowr<q[i].r)Add(a[++nowr]);
		while(nowr>q[i].r)Del(a[nowr--]);
		ans[q[i].id]=Q();
	}
	for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：NaCly_Fish (赞：30)

蒟蒻表示并不会线段树的做法，于是用莫队硬是卡了过去。。   
莫队的板子就不说了，讲一下思路吧。

首先当然是要记录区间中每个数的出现次数。  
若更新后这个数的出现次数变为$1$，就$\text{add}$一下(下面具体说)  
如果以前是$1$，现在不是了，就$\text{del}$掉。

这里我用了一个类似栈的东西，每$\text{add}$进来一个数，就堆到顶上去，同时记录下来这个数的位置。  
每次$\text{del}$一个数时，把栈顶的元素移到被删的数的位置。  
对于每次查询的答案，直接取栈顶元素即可。   
如果栈为空也不用担心，这时取出来的就是$0$，不影响答案正确性。  

可以看出，上面的操作是$\Theta(1)$的。  
然后大力莫队+卡常，这题就可以通过啦qwq  

最后注意一点：  
对询问排序，一定要用奇偶排序优化！  
常数可以小大约一半。  

时间复杂度：$\Theta(n^\frac{3}{2})$

上代码：  
```cpp
#pragma GCC optimize (3)
#pragma GCC optimize ("Ofast")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 500007
#define reg register
using namespace std;

struct query{
	int l,r,id;
}q[N];

int a[N],cnt[N],pos[N],be[N];
int stk[N],ans[N];
int n,m,top,unit;

inline void read(int &x);
void print(int x);
inline bool cmp(query x,query y);
inline void add(int t);
inline void del(int t);
inline char gc();

int main(){
	reg int l,r;
	read(n);
	unit = sqrt(n);
	for(reg int i=1;i<=n;++i){
        read(a[i]);
        be[i] = i/unit+1;
    }
	read(m);
	for(reg int i=1;i<=m;++i){
		read(q[i].l),read(q[i].r);
		q[i].id = i;
	}
	sort(q+1,q+1+m,cmp);
	l = r = 1;
	add(a[1]);
	for(reg int i=1;i<=m;++i){
		while(r<q[i].r) add(a[++r]);
		while(r>q[i].r) del(a[r--]);
		while(l<q[i].l) del(a[l++]);
		while(l>q[i].l) add(a[--l]);
		ans[q[i].id] = stk[top];
	}
	for(reg int i=1;i<=m;++i){
		print(ans[i]);
		putchar('\n');
	}
	return 0;
} 

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}

inline void add(int t){
    ++cnt[t];
	if(cnt[t]==1){
		stk[++top] = t; //放到栈顶
		pos[t] = top; //更新栈顶元素所在位置
	}else if(cnt[t]==2){
		stk[pos[t]] = stk[top]; //栈顶元素替换t的位置
		pos[stk[top]] = pos[t]; //把位置更新一下
		stk[top--] = pos[t] = 0; //原来的地方要清0
	}
}

inline void del(int t){
    --cnt[t];
	if(cnt[t]==1){
		stk[++top] = t;
		pos[t] = top;
	}else if(!cnt[t]){
		stk[pos[t]] = stk[top];
		pos[stk[top]] = pos[t];
		stk[top--] = pos[t] = 0;
	}
}

inline bool cmp(query a,query b){ 
    return (be[a.l]^be[b.l])?a.l<b.l:((be[a.l]&1)?a.r<b.r:a.r>b.r); //传说中的奇偶排序优化
}

inline void read(int &x){
	x = 0;
	char c = gc();
	while(c<'0'||c>'9') c = gc();
	while(c>='0'&&c<='9'){
		x = (x<<3)+(x<<1)+(c^48);
		c = gc();
	}
} 

void print(int x){
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
```

---

## 作者：ExplodingKonjac (赞：26)

### [原题链接](https://www.luogu.com.cn/problem/CF1000F)

## 解题思路

我们有一个询问区间 $[l,r]$，题目要求你找出其中只出现了一次的数。

我们单独考虑某个数 $x$，假设其在 $[l,r]$ 中出现的**下标最大的位置**为 $p$。那么，$x$ 在区间 $[l,r]$ 只出现了一次等价于 $p$ 存在并且相对于 $p$，$x$ 上一次出现的位置 $<l$。

可以在每一个位置 $i$ 维护 $a_i$ 上一次出现的位置。在查询 $[l,r]$ 的时候如果该区间上的最小值 $<l$，则一定有数只出现了一次。用线段树维护，同时记录一下最小值对应的数是什么即可。

为了保证在最靠右的 $x$ 处记录信息，我们需要将询问按照右端点排序，离线处理。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[500005],pos[500005],ans[500005];
const int INF=0x7fffffff;
inline int read()
{
	char ch;int res=0;
	while(isspace(ch=getchar()));
	for(;isdigit(ch);res=res*10+ch-'0',ch=getchar());
	return res;
}
struct Data
{
	int val,id;
	Data(int v,int i): val(v),id(i){}
	inline bool operator <(const Data &b)const
		{ return val<b.val; }
}infdata(INF,0);
struct TreeNode
{
	Data mn;
	TreeNode *lc,*rc;
	TreeNode(int x,int i): mn(x,i)
		{ lc=rc=nullptr; }
}*rt;
typedef TreeNode *pNode;
inline void pushup(pNode i)
	{ i->mn=min(i->lc->mn,i->rc->mn); }
void build(int l,int r,pNode &i=rt)
{
	i=new TreeNode(INF,0);
	if(l!=r)
	{
		int mid=(l+r)>>1;
		build(l,mid,i->lc),build(mid+1,r,i->rc);
	}
}
void modify(int p,Data x,pNode i=rt,int l=1,int r=n)
{
	if(l==r)	i->mn=x;
	else
	{
		int mid=(l+r)>>1;
		if(mid>=p)	modify(p,x,i->lc,l,mid);
		else	modify(p,x,i->rc,mid+1,r);
		pushup(i);
	}
}
Data query(int lq,int rq,pNode i=rt,int l=1,int r=n)
{
	if(r<lq || l>rq)	return infdata;
	if(l>=lq && r<=rq)	return i->mn;
	int mid=(l+r)>>1;
	return min(query(lq,rq,i->lc,l,mid),
			   query(lq,rq,i->rc,mid+1,r));
}
struct Edge{ int to,w,nxt; }e[500005];
int cnt,head[500005];
inline void addEdge(int u,int v,int w)
	{ e[++cnt]=(Edge){v,w,head[u]},head[u]=cnt; }
int main()
{
	n=read();
	for(int i=1;i<=n;i++)	a[i]=read();
	m=read();
	for(int i=1;i<=m;i++)
	{
		int l=read(),r=read();
		addEdge(r,l,i);
	}
	build(1,n);
	for(int i=1;i<=n;i++)
	{
		int x=a[i];
		if(pos[x])
			modify(pos[x],infdata),modify(i,Data(pos[x],x));
		else
			modify(i,Data(0,x));
		pos[x]=i;
		for(int j=head[i];j;j=e[j].nxt)
		{
			Data y=query(e[j].to,i);
			ans[e[j].w]=(y.val<e[j].to)?y.id:0;
		}
	}
	for(int i=1;i<=m;i++)	printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：zhaotiensn (赞：20)

跟上面大佬讲的已经差不多，只不过我用的是主席树，所以可以在线查询。

大致思路：

对于每一个数维护它的最近出现的位置和上一次出现的位置。只有当一个数最近出现的位置在所查询的区间里并且它上一次出现的位置不在这个区间里时，这个数只出现一次。

所以我们只要对于上一次出现的位置维护一个区间最小值和最小值的数值就可以了，假如区间最小值小于左端点，那么这个区间内就有数只出现一次。

然后因为上一次出现的位置是在不断更新的，只有当更新到右端点时才可以进行查询。

之后就是用线段树离线维护，或者主席树记录每一个版本的最小值。

主席树：
```
#include <iostream>
#include <cstdio>

#define Max 500005

using namespace std;

inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define gc getchar
inline int read(){
    int x=0;char ch=gc();bool positive=1;
    for(;!isdigit(ch);ch=gc())if(ch=='-')positive=0;
    for(;isdigit(ch);ch=gc())x=x*10+ch-'0';
    return positive?x:-x;
}

inline void write(int x){
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}

inline void writeln(int x){
    write(x);puts("");
}//以上都是没用的快读快输

struct Tree{
    int id,ls,rs,num,minn;
    //num是最小值的位置，minn是最小值
}ct[Max*50];//内存一定要开够大，我的写法20倍不够用。。

int n,m,l,r,cnt,a[Max],vis[Max],last[Max],root[Max];

inline Tree update(int id,Tree l,Tree r){//更新操作
    Tree ans;
    ans.id=id;
    ans.ls=l.id;
    ans.rs=r.id;
    if(l.minn<r.minn){
        ans.num=l.num;
        ans.minn=l.minn;
    }else{
        ans.num=r.num;
        ans.minn=r.minn;
    }
    return ans;
}

inline void build(int&now,int l,int r){//建树
    now=++cnt;
    ct[now].id=cnt;
    if(l==r){
        ct[now].num=l;
        ct[now].minn=1e9;//一开始将最小值赋值成最大，表示没有出现过
        return;
    }
    int mid=(l+r)>>1;
    build(ct[now].ls,l,mid);
    build(ct[now].rs,mid+1,r);
    ct[now]=update(now,ct[ct[now].ls],ct[ct[now].rs]);
}

inline void change(int&now,int old,int l,int r,int id,int num){修改操作
    now=++cnt;
    ct[now]=ct[old];
    ct[now].id=cnt;
    if(l==r){
        ct[now].minn=num;
        return;
    }
    int mid=(l+r)>>1;
    if(id<=mid){
        change(ct[now].ls,ct[old].ls,l,mid,id,num);
    }else{
        change(ct[now].rs,ct[old].rs,mid+1,r,id,num);
    }
    ct[now]=update(now,ct[ct[now].ls],ct[ct[now].rs]);
}

inline Tree query(int now,int l,int r,int L,int R){//查询操作
    if(l>=L&&r<=R){
        return ct[now];
    }
    int mid=(l+r)>>1;
    if(R<=mid){
        return query(ct[now].ls,l,mid,L,R);
    }else{
        if(L>mid){
            return query(ct[now].rs,mid+1,r,L,R);
        }else{
            return update(1,query(ct[now].ls,l,mid,L,R),query(ct[now].rs,mid+1,r,L,R));
        }
    }
}

int main(){
    n=read();
    build(root[0],1,n);
    for(int i=1;i<=n;i++){
        a[i]=read();
        root[i]=root[i-1];//更新最近出现的位置和上一次出现的位置
        if(vis[a[i]]){
            change(root[i],root[i],1,n,vis[a[i]],1e9);
            last[a[i]]=vis[a[i]];
            change(root[i],root[i],1,n,i,last[a[i]]);
            vis[a[i]]=i;
        }else{
            vis[a[i]]=i;
            change(root[i],root[i],1,n,i,0);
        }
    }
    m=read();
    for(int i=1;i<=m;i++){
        l=read();r=read();
        Tree ans=query(root[r],1,n,l,r);
        if(ans.minn>=l){//判断并输出
            puts("0");
        }else{
            writeln(a[ans.num]);
        }
    }
    return 0;
}

```

---

## 作者：Chancylaser (赞：16)

## $\mathcal{Preface}$

我今天一整个晚上使用了主席树，想了很多种实现方式，但是怎么做都有点问题，最终从以前做过的 [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)  找到了思路，其实这两道题实现方式挺像的，可以说双倍经验。

## $\mathcal{Solution} $

这是一篇主席树的题解。

题目要求我们输出一个区间 $[l,r]$ 内任意一个出现次数有且仅有一次的数。

----------

考虑如何暴力实现。

观察数据范围，可以发现数的范围不大，完全可以开下一个值域的数组。于是我们可以对于每个询问，暴力枚举每一个数，并统计出现次数。统计完成后再次枚举一遍，如果某个数出现的次数为 $1$，则输出即可。

然而时间复杂度为 $\mathcal{O(nq)}$，考虑优化。

----------------------------

思考暴力的本质，即我们如果发现区间 $[l,r]$ 内一个数出现的次数大于 $1$，那么一定不合法。所以我们只需要记录一个数 $x$ 之前出现的位置 $lst_x$ 即可。如果 $lst_x \ge l$，即此区间内 $x$ 的出现次数至少为 $2$，那么我们的答案就一定不会为 $x$。

一个显而易见的思路是，我们维护一个建立在数组下标上的主席树，每个节点维护此节点范围内所有数中最小的 $lst_x$ 及其对应的 $x$。然而，直接这样做并不能保证正确性。一个区间 $[l,r]$ 中，数 $x$ 可能出现多次，区间内第一个 $x$ 所对应的 $lst_x$ 自然小于 $l$，但是如果我们在主席树的 $pushup$ 操作中更新父节点的是这个第一个 $x$，那么最后查询的时候就会出错。 

如何解决这个问题？再次仔细思考，发现每次出现一个新的 $x$ 的时候，将 $lst_x$ 位置的 $lst_{x^{'}}$ 修改为 $INF$ 即可。这样做的话，我们一定不会访问到之前的一个 $x$，使得其 $lst_x$ 小于区间左端点了。即，如果我们需要判断答案是否可以为 $x$，则一定会访问最新的出现 $x$ 的位置。

然后查询的时候，返回此区间内 $lst_x$ 最小值，如果小于区间左端点则输出对应的 $x$，否则输出 $0$ 即可。

时间复杂度 $\mathcal{O(n\log n + q \log n)}$。  
将序列最大值看作与 $n$ 同阶，则空间复杂度 $\mathcal{O(n\log n)}$。

------

* 注意，由于我们每次可能有两次修改操作，所以数组大小需要乘二。

## $\mathcal{Code} $
如有细节问题不会实现，可以参考下面的代码，自认为写得比较好看。

```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
#define F first
#define S second
using namespace std;
typedef long long LL;
const int N=5e5+5,M=41 ,INF=1e9,MX=5e5;
 
int n,Q;
int a[N];
 
struct qwq{
	int ls,rs;
	int mn,wh; 
	// mn 为此主席树节点包含所有下标最小的 lst_x，wh 为其对应的 x。 
	qwq(){
		ls=rs=0;
		mn=INF; wh=0;
		// mn 初始需要设置为正无穷。 
	}
}t[N*M];
int rt[N],cnt;
 
qwq pushup(qwq c,qwq a,qwq b){
	if(a.mn < b.mn){
		c.mn=a.mn;
		c.wh=a.wh;		
	}
	else{
		c.mn=b.mn;
		c.wh=b.wh;			
	}
	return c;
}
 
void Insert(int p,int &q,int l,int r,int x,int val){
	q=++cnt;
	t[q]=t[p];
	if(l==r){
		t[q].mn=val;
		t[q].wh=a[x];
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) Insert(t[p].ls,t[q].ls,l,mid,x,val);
	else Insert(t[p].rs,t[q].rs,mid+1,r,x,val);
	t[q]=pushup(t[q],t[t[q].ls],t[t[q].rs]);
}
 
qwq query(int p,int l,int r,int x,int y){
	if(l>=x && r<=y) return t[p];
	int mid=(l+r)>>1;
	if(y<=mid) return query(t[p].ls,l,mid,x,y);
	else if(x>mid) return query(t[p].rs,mid+1,r,x,y);
	else return pushup(t[p],query(t[p].ls,l,mid,x,y),query(t[p].rs,mid+1,r,x,y));
}
 
int lst[N];
 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(lst[a[i]]){
			Insert(rt[i-1],rt[i],1,MX,lst[a[i]],INF);
			Insert(rt[i],rt[i],1,MX,i,lst[a[i]]);
		}
		else Insert(rt[i-1],rt[i],1,MX,i,0);
		lst[a[i]]=i;
	}
	
	scanf("%d",&Q);
	int l,r;
	while(Q--){
		scanf("%d%d",&l,&r);
		qwq ans=query(rt[r],1,MX,l,r);
		if(ans.mn<l) printf("%d\n",ans.wh);
		else printf("0\n"); 
	}
	return 0;
}
```


---

## 作者：1jia1 (赞：8)

提供一个莫队+栈（懒删除）的做法。

核心思路：用莫队维护区间每个数出现次数。维护一个deltag[]的删除标记。如果一个数出现次数变成1，就塞到栈顶。如果一个数x出现次数从1变成0或2，就deltag[x]++，表示删除一次，不直接在栈中操作。查询时，如果栈顶的数的deltag>0，说明它要删掉，就弹出栈，然后deltag--，一直弹到栈顶的数没有被标记懒删除为止。

```cpp
#include <algorithm>
#include <cstdio>
#include <cmath>
#define N 500001
using namespace std;
int n,m,num[N], pos[N],size,cnt[N],sum,out[N],deltag[N],stack[N<<2],top=0;//deltag:懒删除 
inline void read(int &out)
{
	out=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while('0'<=c&&c<='9')out=out*10+c-'0',c=getchar();
	return;
}
struct doby{
	int l,r,id;
}ask[N];
inline bool cmp(doby a,doby b)
{
	return pos[a.l]^pos[b.l]?pos[a.l]<pos[b.l]:(pos[a.l]&1?a.r<b.r:a.r>b.r);
}
inline void add(int x)
{
	if(cnt[x]==1)deltag[x]++;//懒删除标记
	cnt[x]++;
	if(cnt[x]==1)
		if(deltag[x])deltag[x]--;//次数变成1，就可以把懒删除标记减少1，来代替入栈操作
		else stack[++top]=x;
	return;
}
inline void remove(int x)
{
	if(cnt[x]==1)deltag[x]++;
	cnt[x]--;
	if(cnt[x]==1)
		if(deltag[x])deltag[x]--;
		else stack[++top]=x;
	return;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)read(num[i]);
	read(m);
	size=n/sqrt(m*2.0/3);
	for(int i=1,l,r;i<=m;i++)
	{
		read(ask[i].l),read(ask[i].r);
		ask[i].id=i;
		pos[i]=(i-1)/size+1;
	}
	sort(ask+1,ask+m+1,cmp);
	int ql=1,qr=0;
	for(int i=1;i<=m;i++)
	{
		while(ql<ask[i].l)remove(num[ql++]);
		while(ql>ask[i].l)add(num[--ql]);
		while(qr<ask[i].r)add(num[++qr]);
		while(qr>ask[i].r)remove(num[qr--]);
		while(deltag[stack[top]]&&top)deltag[stack[top]]--,top--;//弹出栈顶的被标记懒删除的元素
		out[ask[i].id]=stack[top];
	}
	for(int i=1;i<=m;i++)printf("%d\n",out[i]);
	return 0;
}
```

---

## 作者：critnos (赞：7)

我们维护一个 pre 和 nxt 数组，对于 $i$ 表示满足 $j<i$ 且 $a_i=a_j$ 的 $j$ 的最大值和满足 $j>i$ 且 $a_i=a_j$ 的 $j$ 的最小值。如果没有满足条件的 $j$ 则 $pre_i=0$，$nxt_i=\inf$。

那么现在问题就转化为了求区间中的一个 $a_i$ 满足 $pre_i<l$ 且 $nxt_i>r$。

思考一个在线做法。这么鬼畜的东西感觉用树套树搞起来比较稳。。（但其实似乎是个三维偏序。。）

一贯的套路，线段树套一个 vector 里面上二分。vector 里面保存三个东西：$pre_i,nxt_i,a_i$。按照 $pre_i$ 排序，然后第一个条件 $pre_i<l$ 二分一下就搞定了。第二个 $nxt_i>r$ 因为有第一个限制条件所以就是从 $0$ 开始存一下最大值就可以了。

我把这个 $2\log$ 的做法写到常数巨大。naive 的我直接用了 vector，然后跑的和莫队差不多。

---

## 作者：attack (赞：5)

首先把询问离线，预处理每个数的$pre, nxt$，同时线段树维护$pre$(下标是$pre$，值是$i$)，同时维护一下最大值

那么每次在$(1, l - 1)$内查询最大值，如果最大值$>= l$，那么说明合法

但是$pre$可能会有相同的情况(0)，直接开个set维护一下

然后用vector对$nxt$维护一个类似差分的东西，在$nxt_i$的位置删除掉$i$的影响


```cpp
// luogu-judger-enable-o2
/*
*/
#include<bits/stdc++.h> 
#define LL long long
#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second 
using namespace std;
const int MAXN = 2e6 + 10;
template <typename A, typename B> inline bool chmin(A &a, B b){if(a > b) {a = b; return 1;} return 0;}
template <typename A, typename B> inline bool chmax(A &a, B b){if(a < b) {a = b; return 1;} return 0;}
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int N, M, a[MAXN], pre[MAXN], nxt[MAXN], ans[MAXN], date[MAXN], num = 0;
vector<Pair> q[MAXN];
void Des() {
    for(int i = 1; i <= N; i++) date[i] = a[i];
    sort(date + 1, date + N + 1);
    num = unique(date + 1, date + N + 1) - date - 1;
    for(int i = 1; i <= N; i++) a[i] = lower_bound(date + 1, date + num + 1, a[i]) - date;
}
void Get() {
    static int las[MAXN];
    for(int i = 1; i <= N; i++) pre[i] = las[a[i]], las[a[i]] = i;
    for(int i = 1; i <= N; i++) las[i] = N + 1;
    for(int i = N; i >= 1; i--) nxt[i] = las[a[i]], las[a[i]] = i;
}
#define Getmid ((T[k].l + T[k].r) >> 1)
#define ls k << 1
#define rs k << 1 | 1
struct Node {
    int l, r, mx;
}T[MAXN];
void update(int k) {
    T[k].mx = max(T[ls].mx, T[rs].mx);
}
void Build(int k, int ll, int rr) {
    T[k].l = ll; T[k].r = rr; T[k].mx = 0;
    if(ll == rr) return ;
    int mid = Getmid;
    Build(ls, ll, mid); Build(rs, mid + 1, rr);
}
void Modify(int k, int pos, int v) {
    if(T[k].l == T[k].r) {T[k].mx = v; return ;}
    int mid = Getmid;
    if(pos <= mid) Modify(ls, pos, v);
    if(pos  > mid) Modify(rs, pos, v);
    update(k);
}
int Query(int k, int ll, int rr) {
    if(ll <= T[k].l && T[k].r <= rr) return T[k].mx;
    int mid = Getmid, ans = 0;
    if(ll <= mid) chmax(ans, Query(ls, ll, rr));
    if(rr  > mid) chmax(ans, Query(rs, ll, rr));
    return ans;
}
#undef ls
#undef rs 
#undef Getmid
void Solve() {
    set<int> s;
    static vector<int> v[MAXN];
    for(int i = 1; i <= N; i++) {
        for(int j = 0; j < v[i].size(); j++) {
            if(!pre[v[i][j]]) 
                s.erase(v[i][j]);
            else Modify(1, pre[v[i][j]], 0);
        }
        if(!pre[i]) 
            s.insert(i);
        else Modify(1, pre[i], i);
            
        v[nxt[i]].push_back(i);
        for(int j = 0; j < q[i].size(); j++) {
            int t = Query(1, 1, q[i][j].fi - 1);
            if(t >= q[i][j].fi) ans[q[i][j].se] = date[a[t]];
            if(!s.empty()) {
                set<int>::iterator it = s.end(); it--;
                if(*it >= q[i][j].fi) ans[q[i][j].se] = date[a[*it]];
            }
            
        }
            
    }
}
signed main() {
    N = read();
    for(int i = 1; i <= N; i++) a[i] = read();
    Des();
    Get();
    Build(1, 1, N + 1);
    M = read();
    for(int i = 1; i <= M; i++) {
        int l = read(), r = read();
        q[r].push_back(MP(l, i));
    }
    Solve();
    for(int i = 1; i <= M; i++) printf("%d\n", ans[i]);
    return 0;
}
/*
5
1 2 2 1 1
2
1 5
2 3 


10
5 9 6 4 8 7 4 9 7 6
1
4 8
*/
```


---

## 作者：Zachary_Cloud (赞：5)

Problem [CF1000F One Occurrence](https://www.luogu.com.cn/problem/CF1000F)

---

### 题目分析

我们可以用莫队。（废话）

用一个变量 $now$ 来记录当前区间内出现一次的数的数量。

每次判断时，如果 $now = 0$，则输出 $0$；如果不是呢？麻烦就来了。

于是我们用一个数组记录**到目前为止**次数为 $1$ 的数。

但依然有麻烦。

当莫队两侧 $l, r$ 跳来跳去的时候，会产生对数字次数的加减，而这个数组如果为桶，虽然方便了数字次数的加减，但对去找一个次数为 $1$ 的数的操作会极大地增加时间复杂度，不可取；如果为一个类似栈的数组，虽方便了寻找操作，但加减依然有麻烦，也不可取。

那怎么办呢？

我们定义这个数组为**记录出现次数为一次的数的栈**，再定义一个桶，为桶的下标的那个数在栈中的位置。

这样，我们就可以近几乎完美地同时解决了两个问题。

$\large\color{red}\texttt{划重点}:$

当有新的次数为 $1$ 的数字时，进栈。

当原为次数 $1$ 的数现不为 $1$ 时，通过桶来寻找这个数在栈中的下标，然后把栈顶放入这个位置，再弹出栈顶。如果是同一个数也无妨。

具体见代码。

## 代码

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

//不好意思，不开 O2 优化还真的过不去（也有可能是我常数太大），（反正这是 CF，没禁 O2）

#include <bits/stdc++.h>
using namespace std;

#define maxn 500010
int n, m, size, l = 1, r, now, len = 0; //now 表示当前符合要求的总数，len 表示栈内元素数
int a[maxn], b[maxn], c[maxn], blo[maxn], cnt[maxn], ans[maxn]; //b[] 栈，c[] 标号
struct node {
	int l, r, id;
} q[maxn];

typedef long long ll;
static char buf[100000],*p1=buf,*p2=buf;
#define gc p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
inline ll read() {ll res=0,w=0; char c=gc; while (!isdigit(c)) w|=c=='-',c=gc; while (isdigit(c)) res=(res<<1)+(res<<3)+(c^48),c=gc; if (w) res=-res; return res;}
inline void write(ll x) {static int sta[50],top=0; if (x<0) putchar('-'),x=-x; do {sta[top++]=x%10,x/=10;}while (x); while (top) putchar(sta[--top]+48); putchar('\n');}

//超级快读快输

bool cmp(node a, node b) {
	return blo[a.l] ^ blo[b.l] ? blo[a.l] < blo[b.l] : blo[a.l] & 1 ? a.r < b.r : a.r > b.r;
} //奇偶性排序

inline void add(int x) {
	if (cnt[a[x]] == 1) { //如果要减掉一个数
		--now; //总数--
		b[c[a[x]]] = b[len]; //取栈顶，自己想一下
		c[b[len]] = c[a[x]];
		b[len] = c[a[x]] = 0;
		len--;
	}
	++cnt[a[x]];
	if (cnt[a[x]] == 1) {
		++now; //总数++
		++len;
		b[len] = a[x]; //加栈顶
		c[a[x]] = len;
	}
}
inline void del(int x) {
	if (cnt[a[x]] == 1) {
		--now;
		b[c[a[x]]] = b[len];
		c[b[len]] = c[a[x]];
		b[len] = c[a[x]] = 0;
		len--;
	}
	--cnt[a[x]];
	if (cnt[a[x]] == 1) {
		++now;
		++len;
		b[len] = a[x];
		c[a[x]] = len;
	}
}

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	m = read();
	for (int i = 1; i <= m; ++i) q[i].l = read(), q[i].r = read(), q[i].id = i; //普通莫队是离线算法，需标记序号
	size = (int)sqrt(n);
	for (int i = 1; i <= n; ++i) blo[i] = (i - 1) / size + 1;
	sort(q + 1, q + m + 1, cmp);
	for (int i = 1; i <= m; ++i) {
		while (l < q[i].l) del(l++); //普
		while (l > q[i].l) add(--l); //通
		while (r < q[i].r) add(++r); //莫
		while (r > q[i].r) del(r--); //队
		if (!now) ans[q[i].id] = 0;
		else ans[q[i].id] = b[len]; //取栈顶
	}
	for (int i = 1; i <= m; ++i) write(ans[i]), putchar('\n');
	return 0;
}
```

## 后记

1. 写完才发现思路跟绒布球几乎一致 ~~（飘了）~~

2. ~~（事实证明：对于区间 l, r 乱七八糟搞来搞去的东西一般莫队都能水过）~~

3. 人生中第一篇紫题题解！

4. A story:


    你第一眼看到题目就可以发现：这道题可以用莫队！

   ~~（摩拳擦掌准备水题）~~


   然而，你接着看题目——区间内**仅存在一次**的数……

   ~~（沉默）~~

   A few minutes later.

   这该怎么做啊啊啊啊啊啊啊啊

   ~~（抓狂）~~

   A few hours later.

   `Wrong answer on test 2.`

   A few hours later again.
   
   `Time limit exceeded on test 65.`
   
   A few hours later again and again.

   `Accepted`

   QwQ

   $\color{grey}\texttt{The above is a true story.}$

---


---

## 作者：makerlife (赞：4)

[更好的阅读体验](https://blog.makerlife.top/post/solution-CF1000F) | [Problem Link](https://www.luogu.com.cn/problem/CF1000F) | [CodeForces Link](https://codeforces.com/problemset/problem/1000/F)

一发线段树的做法。

## Solution

最初的想法是维护每个元素上次出现的下标 $last$ 数组，以样例 `1 1 2 3 2 4 ` 为例，维护出来的结果即为 `0 1 0 0 3 0`，答案就是查找区间 $[l,r]$ 内是否有 $last_i<l$ 的元素。

但这样会出现一个问题：当区间内有元素出现了多次，统计结果会变得不正确。以样例第二组询问为例，$a_1=a_2=1$，而 $last_1=0<1$，看上去可行但实际则出现了两个 $1$。

一个可行的解决措施是只保留**每个数最后一次出现的 $last$ 值**，而将前面的值作废。经过这样的操作，样例处理结果即为（下标从 $1$ 开始）：
$$
\begin{aligned}
a=&\{1,&1,&2,&3,&2,&4\}\\
last=&\{\text{INF},&1,&\text{INF},&0,&3,&0\}
\end{aligned}
$$
由于在维护靠后的 $last$ 时会对前面已经维护的 $last$ 造成影响，故我们需要将询问离线，并按区间右端点排序。保证处理当前询问 $[l,r]$ 区间时 $last_r$ 没有被作废。

则程序为单点修改 $last$ 区间查询 $last$ 的最值。值得注意的是维护线段时应保存区间 $last$ 的最小值和**该值的下标**。区间最小值是为了判断最小的 $last$ 是否在区间内，不是则证明区间内有最小值。最小值下标是为了输出结果。

相比其他做法码量稍大，但维护 $last$ 的 trick 还是有些用处的。

## Core Code

```cpp
const int N=5e5+10;
int n,m;
int a[N];
int last[N];
int t[N];
int ans[N];
struct qs
{
    int l,r,id;
}q[N];
int cmp(qs x,qs y)
{
    return x.r<y.r;
}
struct tree
{
    int val,pos;
};
struct node
{
    int val[N*4],pos[N*4],siz[N*4];
    void pushup(int p)
    {
        if(val[p*2]<val[p*2+1]) val[p]=val[p*2],pos[p]=pos[p*2];
        else val[p]=val[p*2+1],pos[p]=pos[p*2+1];
    }
    void build(int p,int l,int r)
    {
        if(l==r)
        {
            val[p]=INF;
            pos[p]=l;
            return ;
        }
        int mid=(l+r)>>1;
        build(p*2,l,mid);
        build(p*2+1,mid+1,r);
        pushup(p);
    }
    void modify(int p,int l,int r,int x,int w)
    {
        if(l==r)
        {
            val[p]=w;
            return ;
        }
        int mid=(l+r)>>1;
        if(x<=mid) modify(p*2,l,mid,x,w);
        else modify(p*2+1,mid+1,r,x,w);
        pushup(p);
    }
    tree query(int p,int l,int r,int x,int y)
    {
        if(x<=l && r<=y)
        {
            return {val[p],pos[p]};
        }
        int mid=(l+r)>>1;
        tree res={INF,0};
        if(x<=mid)
        {
            tree tmp=query(p*2,l,mid,x,y);
            if(tmp.val<res.val)
            {
                res.val=tmp.val;
                res.pos=tmp.pos;
            }
        }
        if(y>=mid+1)
        {
            tree tmp=query(p*2+1,mid+1,r,x,y);
            if(tmp.val<res.val)
            {
                res.val=tmp.val;
                res.pos=tmp.pos;
            }
        }
        return res;
    }
}g;
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        last[i]=t[a[i]];
        t[a[i]]=i;
    }
    m=read();
    for(int i=1;i<=m;i++)
    {
        q[i].l=read();q[i].r=read();q[i].id=i;
    }
    sort(q+1,q+m+1,cmp);
    g.build(1,1,n);
    int j=1;
    for(int i=1;i<=n;i++)
    {
        g.modify(1,1,n,i,last[i]);
        if(last[i]!=0) g.modify(1,1,n,last[i],INF);
        while(q[j].r==i && j<=m)
        {
            tree res=g.query(1,1,n,q[j].l,q[j].r);
            if(res.val<q[j].l) ans[q[j].id]=a[res.pos];
            else ans[q[j].id]=0;
            j++;
        }
    }
    for(int i=1;i<=m;i++)
    {
        cout<<ans[i]<<endl;
    }
    return 0;
}
```

---

## 作者：银河AI (赞：3)

### 解题思路

根据题目大意，我们可以很快想出来用莫队或主席树解

对于主席树？我不会，于是我用了莫队

莫队在这道题中实际相当于一个板子

我们用一个 $sum$ 数组来记录该区间内只出现一次有几个数

用 $cnt$ 数组来记录该区间内某个数出现了几次

接下来就是简单的分块了

块的大小我设成了 $2137$（题解里有人设为 $1000$）

设一个 $last$ 数组代表这个块内最后一个元素

为了减少花费时间，我选择用奇偶排序优化（是这个名字吗？）

```cpp
inline bool cmp(query a,query b){return (bel[a.l]^bel[b.l])?a.l<b.l:((bel[a.l]&1)?a.r<b.r:a.r>b.r);}

```

在具体的添加操作中，需要特判当一个数出现 $2$ 次或出现 $1$ 次

在具体的删除操作中，需要特判当一个数出现 $1$ 次或 $0$ 次

即

```cpp
void add(int x){
	if(cnt[x]==1) sum[bel[x]]--;
	if(cnt[x]==0) sum[bel[x]]++;
	cnt[x]++;
}
void del(int x){
	if(cnt[x]==1) sum[bel[x]]--;
	if(cnt[x]==2) sum[bel[x]]++;
	cnt[x]--;
}
```

莫队左右指针来回跳动，我就不说了（莫队的基本操作？）

但是要提一点的是查询操作

因为我没有想到题解里面的“桶操作”

所以我用了暴力搜索（带一点小小的剪枝）

就是说，先询问每一个块，如果当前块无出现一次的时候，就跳过

否则就查找这个块中出现过一次的那个，建议从结尾往前扫，因为之前我们已经用 $last$ 数组存过每个块的最后一次位置了

然后？就没了吧，应该就注意这么多吧

不过我想提一句，尽管我用了搜索+剪枝来查询，但我没开 $O_2$ 仍没 $TLE$（神奇）


### AC代码（注释版本）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+1;
int n,m,block,len;
int a[N],cnt[N],bel[N],ans[N],last[N],sum[N];//这些数组的具体含义写在解题思路里了 
struct query{//莫队的结构体 
	int l,r,id;
}q[N];
inline bool cmp(query a,query b){return (bel[a.l]^bel[b.l])?a.l<b.l:((bel[a.l]&1)?a.r<b.r:a.r>b.r);}//奇偶优化排序 
int ask(){//查询操作 
	for(int i=bel[N-1];i;i--){
		if(!sum[i]) continue;
		for(int j=last[i];j;j--) if(cnt[j]==1) return j;
	}
	return 0;
}
void add(int x){//增加操作 
	if(cnt[x]==1) sum[bel[x]]--;
	if(cnt[x]==0) sum[bel[x]]++;
	cnt[x]++;
}
void del(int x){//删除操作 
	if(cnt[x]==1) sum[bel[x]]--;
	if(cnt[x]==2) sum[bel[x]]++;
	cnt[x]--;
}
void init(){for(int i=1;i<=N-1;i++) bel[i]=i/block+1,last[bel[i]]=i; }//分块 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	block=2137;//块的大小 
	init();//预处理，即分块 
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1,cmp);//排序 
	int l=1,r=0;
	for(int i=1;i<=m;i++){ 
		int ql=q[i].l,qr=q[i].r;
		while(l<ql) del(a[l]),l++;
		while(l>ql) l--,add(a[l]);
		while(r<qr) r++,add(a[r]);
		while(r>qr) del(a[r]),r--;
		ans[q[i].id]=ask();
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}
```

### AC代码（无注释版）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+1;
int n,m,block,len;
int a[N],cnt[N],bel[N],ans[N],last[N],sum[N];
struct query{
	int l,r,id;
}q[N];
inline bool cmp(query a,query b){return (bel[a.l]^bel[b.l])?a.l<b.l:((bel[a.l]&1)?a.r<b.r:a.r>b.r);} 
int ask(){
	for(int i=bel[N-1];i;i--){
		if(!sum[i]) continue;
		for(int j=last[i];j;j--) if(cnt[j]==1) return j;
	}
	return 0;
}
void add(int x){
	if(cnt[x]==1) sum[bel[x]]--;
	if(cnt[x]==0) sum[bel[x]]++;
	cnt[x]++;
}
void del(int x){
	if(cnt[x]==1) sum[bel[x]]--;
	if(cnt[x]==2) sum[bel[x]]++;
	cnt[x]--;
}
void init(){for(int i=1;i<=N-1;i++) bel[i]=i/block+1,last[bel[i]]=i; } 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	block=2137; 
	init(); 
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+m+1,cmp); 
	int l=1,r=0;
	for(int i=1;i<=m;i++){ 
		int ql=q[i].l,qr=q[i].r;
		while(l<ql) del(a[l]),l++;
		while(l>ql) l--,add(a[l]);
		while(r<qr) r++,add(a[r]);
		while(r>qr) del(a[r]),r--;
		ans[q[i].id]=ask();
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}
```
第一篇紫题题解呢，管理大大请通过啦

---

## 作者：cirnovsky (赞：3)

## 题意简述

给定一个序列，每次询问输出一个区间 $[l,r]$ 中只出现一次的数。

## 题解

这道题其实比较有意思。他让你输出只出现一次的数，讲道理你让我维护个数都还好办，这个就比较好玩了。

我这里给出一种不用吸氧的卡常莫队做法。

其实莫队需要维护的东西很简单，就是一个数的出现次数，我们用一个数组 `cnt` 来记录。

每次我们算加贡献的时候，`cnt` 的计算方法很显然。我们同时维护一个栈，算加贡献的时候如果这个数的出现次数为1，我们就把他放到栈顶上去。我们顺手维护一个数组 `pos` 表示这个数在栈里的位置。

算减贡献的时候 `cnt` 的计算方法依旧显然。我们把栈顶元素放到删除的数的位置上即可。

每次询问的答案就是栈顶元素，由于不合法的情况输出零，所以没必要特判。

光这样是过不了的，会T飞。

我们需要一个针对于莫队的优化，叫做奇偶性排序优化（瞎编的一个名字），具体来说就是在对询问排序的时候分块的奇偶性，具体实现看代码。这种排序的方式理论来说有 $\Theta(\frac{1}{2})$ 的常数。

这样还是会T。容易发现输出答案的循环可以用unroll循环展开，我设的unroll的参是10，已经能过了。

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int Maxn = 5e5 + 5, Each = 720;
int n, m, top, isa[ Maxn ], cnt[ Maxn ], pos[ Maxn ], htl[ Maxn ], ans[ Maxn ];
struct Query_Node
{
	int l, r, id, pos;
	Query_Node( int L = 0, int R = 0, int ID = 0 ) { l = L, r = R, id = ID; }
} Q[ Maxn ];

inline int read( )
{
	int a = 0, minus = 0;
	char ch = getchar( );
	while( !isdigit( ch ) )
	{
		if( ch == '-' )	 minus = 1;
		ch = getchar( );
	}
	while( isdigit( ch ) )
	{
		a = a * 10 + ch - '0';
		ch = getchar( );
	}
	if( minus )	 return -a;
	else	return a;
}

inline void write( int x )
{
	if( x < 0 )
	{
		x = -x;
		putchar( '-' );
	}
	if( x > 9 ) 	write( x / 10 );
	putchar( x % 10 + '0' );
}

inline bool cmp( Query_Node rhs, Query_Node shr )
{
	if( rhs.pos != shr.pos )	return rhs.l < shr.l;
	else if( rhs.pos & 1 )	return rhs.r < shr.r;
	else 	return rhs.r > shr.r;
}

inline void Make_Cont( int x, int t )
{
	x = isa[ x ];
	if( t == 1 ) ++ cnt[ x ];
	else	-- cnt[ x ];
	if( cnt[ x ] == 1 )
	{
		htl[ ++ top ] = x;
		pos[ x ] = top;
	}
	else if( ( t == 1 ) ? ( cnt[ x ] == 2 ) : ( cnt[ x ] == 0 ) )
	{
		htl[ pos[ x ] ] = htl[ top ];
		pos[ htl[ top ] ] = pos[ x ];
		pos[ x ] = htl[ top -- ] = 0;
	}
}

inline void Contribute( )
{
	int l = 1, r = 0;
	for( int i = 0; i < m; ++ i )
	{
		while( l < Q[ i ].l )	Make_Cont( l ++, 0 );
		while( l > Q[ i ].l )	Make_Cont( -- l, 1 );
		while( r < Q[ i ].r )	Make_Cont( ++ r, 1 );
		while( r > Q[ i ].r )	Make_Cont( r --, 0 );
		ans[ Q[ i ].id ] = htl[ top ];
	}
}

signed main( )
{
	n = read( );
	for( int i = 1; i <= n; ++ i ) 		isa[ i ] = read( );
	m = read( );
	for( int i = 0; i < m; ++ i )
	{
		Q[ i ].l = read( );
		Q[ i ].r = read( );
		Q[ i ].id = i;
		Q[ i ].pos = Q[ i ].l / Each;
	}
	sort( Q, Q + m, cmp );
	Contribute( );
	if( m <= 10 )
	{
		for( int i = 0; i < m; ++ i )		write( ans[ i ] ), putchar( '\n' );
		return 0;
	}
	#pragma unroll 10
	for( int i = 0; i < m; ++ i )		write( ans[ i ] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：2)

类似小H的项链的做法。

这题可以用莫队但很麻烦，要卡常

线段树就是每次更关心一下pos数组，维护一下

主席树大概可以在线？

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef pair<int ,int > pa; 
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=5e5+5;
struct qu{
	int l,r,id;
}q[N];
int n,m,num[N];
inline void init(){
	n=read();
	for (int i=1;i<=n;i++) num[i]=read();
	m=read();
	for (int i=1;i<=m;i++) q[i]=(qu){read(),read(),i};
}
inline bool cmp(qu A,qu B){return A.r<B.r;}
const int INF=1e9;
int las[N],pos[N],ans[N];
pa mn[N<<2];
inline void pushup(int k){mn[k]=min(mn[k<<1],mn[k<<1|1]);}
void build(int k,int l,int r){
	mn[k]=pa(INF,0);
	if (l==r) return;
	int mid=(l+r)>>1; build(k<<1,l,mid); build(k<<1|1,mid+1,r);
}
void upd(int k,int l,int r,int x){
	if (l==r){
		mn[k]=pa(pos[x],x);
		return;	
	}
	int mid=(l+r)>>1;
	if (mid>=x) upd(k<<1,l,mid,x); else upd(k<<1|1,mid+1,r,x);
	pushup(k);
}
pa query(int k,int l,int r,int x,int y){
	if (l==x&&r==y) return mn[k];
	int mid=(l+r)>>1;
	if (mid>=y) return query(k<<1,l,mid,x,y);
		else if (mid<x) return query(k<<1|1,mid+1,r,x,y);
			else return min(query(k<<1,l,mid,x,mid),query(k<<1|1,mid+1,r,mid+1,y));
}
inline void solve(){
	sort(q+1,q+1+m,cmp);
	for (int i=1;i<=n;i++){
		las[i]=pos[num[i]];
		pos[num[i]]=i;
	}
	build(1,1,n); memset(pos,0,sizeof(pos)); int now=0;
	for (int i=1;i<=m;i++){
		int L=q[i].l,R=q[i].r;
		while (now!=R){
			++now;
			if (las[now]){
				pos[las[now]]=INF;
				upd(1,1,n,las[now]);
			}
			pos[now]=las[now];
			upd(1,1,n,now);
		}
		pa tmp=query(1,1,n,L,R);
		if (tmp.first<L) ans[q[i].id]=num[tmp.second];
	}
	for (int i=1;i<=m;i++){
		writeln(ans[i]);
	}
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：Eon_Sky (赞：0)

莫队做法，只需要一个奇怪的离散化即可。

我设 $t_i$ 表示数字 $i$ 在目前区间出现的次数，$re$ 数组用来存在目前区间出现只有一次的数， $res_i$ 表示数字 $i$ 在 $re$ 数组中的位置，如果数字 $i$ 没有在 $re$ 数组中，那么 $res_i$ 为 $0$。我们保证 $re$ 数组是向左端靠拢的，这样就可以做到 $re_1$ 为答案，如果没有元素（没有答案）， $re_1$ 就会为 $0$。

不理解的可以代码里的注释。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e6+1;
struct Que
{
	int id;
	int l,r;
}que[N];
int n,q;
int len;
int l=1,r;
int cnt;
int re[N];
int res[N];
int a[N];
int t[N];
int c[N];
int ans[N];

inline int read()//快读
{
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}

bool cmp(Que x,Que y)
{
	return (c[x.l]^c[y.l])?c[x.l]<c[y.l]:((c[x.l]&1)?x.r<y.r:x.r>y.r);
}

inline void add(int x)
{
	if(t[a[x]]==1)//说明现在这个数字出现次数不是1了
	{
		re[res[a[x]]]=re[cnt];//将数组尾端数字移到这里，覆盖当前值，保证数组向左端靠拢
		res[re[cnt]]=res[a[x]];//更新刚才的尾端数字的res
		re[cnt]=0;//清零现在的
		res[a[x]]=0;
		cnt--; //数组长度改变
	}
	if(t[a[x]]==0)//添加新元素更好理解
	{
		re[++cnt]=a[x];
		res[a[x]]=cnt;
	}
	++t[a[x]];
	return;
}

inline void sub(int x)//同上，其他就是正常莫队了
{
	if(t[a[x]]==1)
	{
		re[res[a[x]]]=re[cnt];
		res[re[cnt]]=res[a[x]];
		re[cnt]=0;
		res[a[x]]=0;
		cnt--; 
	}
	if(t[a[x]]==2)
	{
		re[++cnt]=a[x];
		res[a[x]]=cnt;
	}
	--t[a[x]];
	return;
}

int main()
{
	n=read();
	len=sqrt(n);
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
		c[i]=i/len+1;
	}
	q=read();
	for(int i=1;i<=q;++i)
	{
		que[i].l=read();
		que[i].r=read();
		que[i].id=i;	
	}
	sort(que+1,que+1+q,cmp);
	for(int i=1;i<=q;++i)
	{
		while(que[i].l<l)
			add(--l);
		while(que[i].r>r)
			add(++r);
		while(que[i].l>l)
			sub(l++);
		while(que[i].r<r)
			sub(r--);	
		ans[que[i].id]=re[1];
	}
	for(int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

