# Factory Repairs

## 题目描述

A factory produces thimbles in bulk. Typically, it can produce up to $ a $ thimbles a day. However, some of the machinery is defective, so it can currently only produce $ b $ thimbles each day. The factory intends to choose a $ k $ -day period to do maintenance and construction; it cannot produce any thimbles during this time, but will be restored to its full production of $ a $ thimbles per day after the $ k $ days are complete.

Initially, no orders are pending. The factory receives updates of the form $ d_{i} $ , $ a_{i} $ , indicating that $ a_{i} $ new orders have been placed for the $ d_{i} $ -th day. Each order requires a single thimble to be produced on precisely the specified day. The factory may opt to fill as many or as few of the orders in a single batch as it likes.

As orders come in, the factory owner would like to know the maximum number of orders he will be able to fill if he starts repairs on a given day $ p_{i} $ . Help the owner answer his questions.

## 说明/提示

Consider the first sample.

We produce up to $ 1 $ thimble a day currently and will produce up to $ 2 $ thimbles a day after repairs. Repairs take $ 2 $ days.

For the first question, we are able to fill $ 1 $ order on day $ 1 $ , no orders on days $ 2 $ and $ 3 $ since we are repairing, no orders on day $ 4 $ since no thimbles have been ordered for that day, and $ 2 $ orders for day $ 5 $ since we are limited to our production capacity, for a total of $ 3 $ orders filled.

For the third question, we are able to fill $ 1 $ order on day $ 1 $ , $ 1 $ order on day $ 2 $ , and $ 2 $ orders on day $ 5 $ , for a total of $ 4 $ orders.

## 样例 #1

### 输入

```
5 2 2 1 8
1 1 2
1 5 3
1 2 1
2 2
1 4 2
1 3 2
2 1
2 3
```

### 输出

```
3
6
4
```

## 样例 #2

### 输入

```
5 4 10 1 6
1 1 5
1 5 5
1 3 2
1 5 2
2 1
2 2
```

### 输出

```
7
1
```

# 题解

## 作者：RedStoneShark (赞：6)

### solution:


这一题相对来说比较线段树板子。用线段树存下来 $\min(b,t_i)$ $\min(a,t_i)$ 和 $t_i$。然后单点修改，区间求值就行了（甚至用不着 `Lazy_tag`）。

### code：
```cpp

// Problem: Factory Repairs
// Contest: Luogu
#include<bits/stdc++.h>
using namespace std;
int n,a,b,k,q;
struct aa{
	int zrz,yrz,amin,bmin,num;
}xds[400030];
int cnt=1;
void pushup(int u){
	xds[u].amin=xds[xds[u].zrz].amin+xds[xds[u].yrz].amin;
	xds[u].bmin=xds[xds[u].zrz].bmin+xds[xds[u].yrz].bmin;
}
void build(int u,int l,int r){
	if(l==r){
		xds[u].num=0;
		xds[u].amin=0;
		xds[u].bmin=0;
		return;
	}
	int mid=(l+r)>>1;
	xds[u].zrz=++cnt;
	build(cnt,l,mid);
	xds[u].yrz=++cnt;
	build(cnt,mid+1,r);
	pushup(u);
}
void update(int u,int l,int r,int x,int val){
	if(l==r){
		xds[u].num+=val;
		xds[u].amin = min(a,xds[u].num);
		xds[u].bmin = min(b,xds[u].num);
		return;
	}
	int mid = (l+r)>>1;
	if(x<=mid){
		update(xds[u].zrz,l,mid,x,val);
	}else{
		update(xds[u].yrz,mid+1,r,x,val);
	}
	pushup(u);
}
int query(int u,int sl,int sr,int l,int r,int x){
	if(sl>sr){
		return 0;
	}
	if(sl==l && r==sr){
		if(x==1){
			return xds[u].amin;
		}
		else{
			return xds[u].bmin;
		}
	}
	int mid=(l+r)>>1;
	if(sr<=mid){
		return query(xds[u].zrz,sl,sr,l,mid,x);
	}
	else if(sl>mid){
		return query(xds[u].yrz,sl,sr,mid+1,r,x);
	}
	else{
		int lef=query(xds[u].zrz,sl,mid,l,mid,x);
		int rig=query(xds[u].yrz,mid+1,sr,mid+1,r,x);
		return lef+rig;
	}
}
int main(){
	cin>>n>>k>>a>>b>>q;
	build(1,1,n);
	while(q--){
		int op,a,b;
		cin>>op;
		if(op==1){
			cin>>a>>b;
			update(1,1,n,a,b);
		}
		else{
			cin>>a;
			cout<<query(1,1,a-1,1,n,2)+query(1,a+k,n,1,n,1)<<endl;
		}
	}
	return 0;
}


```

---

## 作者：yingjingxu_NaS2O3 (赞：4)

## 思路

考虑使用线段树，则操作 $1$ 为线段树的单点修改，操作 $2$ 为线段树的区间询问。

利用线段树分别维护 $\sum\limits_{i=1}^{x-1} \min(b,t_i)$ 和 $\sum\limits_{i=x+k}^{n} \min(a,t_i)$，则可得到如下代码：

```cpp
void Update(int l,int r,int x,int y,int iid)
{
    if(l==r)
    {
        tr[iid]=min(b,tr[iid]+y);
        return;
    }
    int mid=l+r>>1;
    if(x<=mid)
        Update(l,mid,x,y,iid<<1);
    else
        Update(mid+1,r,x,y,iid<<1|1);
    tr[iid]=tr[iid<<1]+tr[iid<<1|1];
    return;
}
// 与 a 比较同理
```

注意到 $tr_{iid}$ 的取值为 $\min(b,tr_{iid}+y)$，即加上 $y$ 后与 $b$ 比较大小，若 $tr_{iid}$ 已被更新为 $b$，则 $\min(b,b+y)=b$，对结果无影响。

可以观察到 $\sum\limits_{i=1}^{x-1} \min(b,t_i)$ 在 $x=1$ 时，其对应区间为不合法区间，应当特判，直接将该值变为 $0$，则得到如下代码：

```cpp
printf("%d\n",(x==1?0:Query(1,n,1,x-1,1))+Query_a(1,n,x+k,n,1)); // 三目运算符

if(x==1)
	printf("%d\n",Query_a(1,n,x+k,n,1)); 
else
	printf("%d\n",Query(1,n,1,x-1,1)+Query_a(1,n,x+k,n,1)); // if-else
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a,b,q;
int tr[800005],sum[800005]; // tr 和 sum 分别维护与 b 和 a 的最小值 
inline int _Read() // 快读  
{
    int s=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-f;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        s=s*10+ch-48;
        ch=getchar();
    }
    return s*f;
}
void Update(int l,int r,int x,int y,int iid)
{
    if(l==r)
    {
        tr[iid]=min(b,tr[iid]+y);
        return;
    }
    int mid=l+r>>1;
    if(x<=mid)
        Update(l,mid,x,y,iid<<1);
    else
        Update(mid+1,r,x,y,iid<<1|1);
    tr[iid]=tr[iid<<1]+tr[iid<<1|1];
    return;
}
void Update_a(int l,int r,int x,int y,int iid)
{
    if(l==r)
    {
        sum[iid]=min(a,sum[iid]+y);
        return;
    }
    int mid=l+r>>1;
    if(x<=mid)
        Update_a(l,mid,x,y,iid<<1);
    else
        Update_a(mid+1,r,x,y,iid<<1|1);
    sum[iid]=sum[iid<<1]+sum[iid<<1|1];
    return;
}
int Query(int l,int r,int x,int y,int iid)
{
    if(x<=l&&r<=y)
    	return tr[iid];
    int mid=l+r>>1;
    int ans=0;
    if(x<=mid)
		ans+=Query(l,mid,x,y,iid<<1);
    if(y>mid)
		ans+=Query(mid+1,r,x,y,iid<<1|1);
    return ans;
}
int Query_a(int l,int r,int x,int y,int iid)
{
    if(x<=l&&r<=y)
    	return sum[iid];
    int mid=l+r>>1;
    int ans=0;
    if(x<=mid)
		ans+=Query_a(l,mid,x,y,iid<<1);
    if(y>mid)
		ans+=Query_a(mid+1,r,x,y,iid<<1|1);
    return ans;
}
int main()
{
	n=_Read();
	k=_Read();
	a=_Read();
	b=_Read();
	q=_Read(); // 注意读入顺序 
	while(q--)
	{
		int op,x,y;
		op=_Read();
		if(op==1)
		{
			x=_Read();
			y=_Read();
			Update(1,n,x,y,1);
			Update_a(1,n,x,y,1); //单点修改 
		}
		else
		{
			x=_Read();
			printf("%d\n",(x==1?0:Query(1,n,1,x-1,1))+Query_a(1,n,x+k,n,1)); // 特判 
		}
	}
	return 0;
}
```

---

## 作者：QCurium (赞：3)

[洛谷原题链接](https://www.luogu.com.cn/problem/CF627B)

[视频讲解（顺便点个赞吧](https://www.bilibili.com/video/BV1Kp4y1775t/?vd_source=a8f2ca9bd086cb49d933fb93cb7409c0)

## 题意

输入 $n,k,a,b,q$，再进行 $q$ 次询问，有两种询问。

- $1$ $x$ $y$，将 $t_{x}$ 增加 $y$。


- $2$ $x$，求出 $\left(\sum\limits_{i=1}^{x-1} \min(b,t_i)\right) + \left(\sum\limits_{i=x+k}^{n} \min(a,t_i)\right)$。


## 题目分析

因为有 $\min(a,t_i)$ 和 $\min(b,t_i)$，我们可以用一颗线段树来存一下 $\min(a,t_i)$、$\min(b,t_i)$ 和 $t_i$ 的值，操作 $2$ 的时候就和正常线段树一样。

## Code

```cpp
#include<bits/stdc++.h>
#define int long 
using namespace std;
const int N=2e5+5;
int n,aaa,bbb,k,q,ii[N];
struct node{
	int l,r;
	int suma,vala;//其实可以开一个val，打的时候脑子短路了，打了两个
	int sumb,valb;
}a[N*4];
void build(int aa,int l,int r){//建树
	a[aa].l=l;
	a[aa].r=r;
	a[aa].suma=a[aa].sumb=0;
	a[aa].vala=a[aa].valb=0;
	if(l==r){
		ii[l]=aa;
		return ;
	}
	int mid=(l+r)>>1;
	build(aa*2,l,mid);
	build(aa*2+1,mid+1,r);
	
	return ;
}
void pushup(int aa){//更新区间和
	a[aa].suma=a[aa*2].suma+a[aa*2+1].suma;
	a[aa].sumb=a[aa*2].sumb+a[aa*2+1].sumb;
	return ;
}
void modify(int aa,int lr,int z){
	if(a[aa].l==a[aa].r&&a[aa].l==lr){
		a[aa].vala+=z;
		a[aa].valb+=z;
		a[aa].suma=min(a[aa].vala,aaa);//维护子节点的值
		a[aa].sumb=min(a[aa].valb,bbb);
		return ;
	}
	int mid=(a[aa].l+a[aa].r)>>1;
	if(lr<=mid)
		modify(aa*2,lr,z);
	else
		modify(aa*2+1,lr,z);
	pushup(aa);
	return ;
}
int querya(int aa,int l,int r){
	if(a[aa].l>=l&&a[aa].r<=r)
		return a[aa].suma;
	int ans=0,mid=(a[aa].l+a[aa].r)>>1;
	if(l<=mid)
		ans+=querya(aa*2,l,r);
	if(r>mid)
		ans+=querya(aa*2+1,l,r);
	return ans;
}
int queryb(int aa,int l,int r){
	if(a[aa].l>=l&&a[aa].r<=r)
		return a[aa].sumb;
	int ans=0,mid=(a[aa].l+a[aa].r)>>1;
	if(l<=mid)
		ans+=queryb(aa*2,l,r);
	if(r>mid)
		ans+=queryb(aa*2+1,l,r);
	return ans;
}
signed main(){
    ios::sync_with_stdio(false);//关同步流，可以是cin cout比scanf printf快
    cin.tie(0),cout.tie(0);
    cin>>n>>k>>aaa>>bbb>>q;
    build(1,1,n);
    while(q--){
    	int op,x,y;
    	cin>>op>>x;
    	if(op==1){
    		cin>>y;
    		modify(1,x,y);
		}
		else
			cout<<queryb(1,1,x-1)+querya(1,x+k,n)<<'\n';
	}
	return 0;
}

```


---

## 作者：yizhiming (赞：2)

## 题目大意

给定 $n,k,a,b,q$（注意读入顺序）。

表示一个长度为 $n$ 的序列 $t_i$，初始值为 $0$。

$q$ 次操作：

- `1 i x`：将 $t_i$ 增加 $ x$。

- `2 x`：查询 $\sum\limits_{i=1}^{x-1} \min(b,t_i) + \sum\limits_{i=x+k}^{n} \min(a,t_i)$。


## 题目分析

首先注意到 $a,b$ 是开始给定的，所以，$t_i$ 与 $a,b$ 的大小关系就是确定的。

同时，我们发现修改只有单点修改。所以，我们每次修改，只会影响一个位置，我们在线段树上找到这一个端点，由于修改操作是修改值而不是替换，所以我们要记录每一个点的当前值。

由于 $a,b$ 值不同，所有我们要将 $t_i$ 与 $a,b$ 的式子分开计算，我们设 $sum1,sum2$ 分别表示 $t_i$ 与 $a$ 的式子，$t_i$ 与 $b$ 的式子，设当前单点值为 $num$，那么对于单点：

$sum1 = \min(sum1,num)$，$sum2 = \min(sum2,num)$  

而其它节点，直接由子节点上传上去即可。

最后答案就是 $\sum\limits_{i=1}^{x-1} sum2_i + \sum\limits_{i=x+k}^{n} sum1_i$

这东西可以直接用线段树查询。

最后放一下代码，有点丑勿喷。

## Code


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
int read(){
	int x=0,f=1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch = getchar();}
	while(ch>='0'&&ch<='9'){x = x*10+ch-'0';ch = getchar();}
	return x*f;
}
const int N = 2e5+5;
int n,a,b,k,q;
struct aa{
	int lc,rc,sum1,sum2,num;//sum1表示与a取最小值,sum2表示与b取最小值 
}node[N*2];
int tot=1;
void pushup(int u){
	node[u].sum1 = node[node[u].lc].sum1+node[node[u].rc].sum1;
	node[u].sum2 = node[node[u].lc].sum2+node[node[u].rc].sum2;
}
void build(int u,int l,int r){
	if(l==r){
		node[u].sum1 = 0;node[u].sum2 = 0;node[u].num = 0;
		return;
	}
	int mid = (l+r)/2;
	node[u].lc = ++tot;
	build(tot,l,mid);
	node[u].rc = ++tot;
	build(tot,mid+1,r);
	pushup(u);
}
void upd(int u,int l,int r,int x,int val){
	if(l==r){
		node[u].num+=val;
		node[u].sum1 = min(a,node[u].num);
		node[u].sum2 = min(b,node[u].num);
		return;
	}
	int mid = (l+r)/2;
	if(x<=mid){
		upd(node[u].lc,l,mid,x,val);
	}else{
		upd(node[u].rc,mid+1,r,x,val);
	}
	pushup(u);
}
int query(int u,int l,int r,int ll,int rr,int x){
	if(ll>rr){
		return 0;
	}
	if(ll==l&&r==rr){
		if(x==1){
			return node[u].sum1;
		}else{
			return node[u].sum2;
		}
	}
	int mid = (l+r)/2;
	if(rr<=mid){
		return query(node[u].lc,l,mid,ll,rr,x);
	}else if(ll>mid){
		return query(node[u].rc,mid+1,r,ll,rr,x);
	}else{
		return query(node[u].lc,l,mid,ll,mid,x)+query(node[u].rc,mid+1,r,mid+1,rr,x);
	}
}
int main(){
	n = read();k = read();a = read();b = read();q = read();
	build(1,1,n);
	int opt,x,y;
	while(q--){
		opt = read();
		if(opt==1){
			x = read();y = read();
			upd(1,1,n,x,y);
		}else{
			x = read();
			cout<<query(1,1,n,1,x-1,2)+query(1,1,n,x+k,n,1)<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：TerryHan_Su (赞：1)

# CF627B题解

## 题目链接：[Link](https://www.luogu.com.cn/problem/CF627B)。
## 简要题意：



您将获得一个长度为 $n$ 的数组 $t$，另有三个数 $a$，$b$，$k$。初始时数列每一项均为 $0$。

有 $q$ 次操作，每次操作有两种可能：

`1 x y`：将 $t_x$ 增加 $y$。


`2 x`：求出 $\left(\sum\limits_{i=1}^{x-1} \min(b,t_i)\right) + \left(\sum\limits_{i=x+k}^{n} \min(a,t_i)\right)$。


您需要在每一次第二种操作后输出正确的答案。

## 解题思路：
通过观察题目，我们可以知道其要求我们进行**单点修改**与**区间查询**操作，其分别对应为操作1与操作2。

据此，我们可以想到用线段树或树状数组去维护。以下为线段树做法。

 - 操作1，为基本的单点修改，不必多说。
 
 
 - 操作2，对于 $\left(\sum\limits_{i=1}^{x-1} \min(b,t_i)\right) + \left(\sum\limits_{i=x+k}^{n} \min(a,t_i)\right)$，我们思考如何去解决。
 
 我们通过观察公式，发现其与一般的区间求和差别不大，只是对于每个 $t_i$ 要分别对 $a$ 与 $b$ 取 $\min$。据此，我们可以想到在单点修改时，进行以下操作去解决该问题：建立两颗线段树，分别维护 $\left(\sum\limits_{i=1}^{x-1} \min(b,t_i)\right)$ 与 $\left(\sum\limits_{i=x+k}^{n} \min(a,t_i)\right)$。每次在单点修改时，分别将所修改的数对 $a$ 与 $b$ 取 $\min$。
 具体操作如下。
 
```cpp
void update1(int pos,int l,int r,int x,int k)
{
    if(l==x && x==r) 
	{
		t1[pos].sum+=k;
		t1[pos].sum=min(b,t1[pos].sum);
		return ;
	}
    if(x<=mid) update1(lson,l,mid,x,k);
    else update1(rson,mid+1,r,x,k);
    pushup1(pos);
	return ;
}
```

```cpp
void update2(int pos,int l,int r,int x,int k)
{
    if(l==x && x==r) 
	{
		t2[pos].sum+=k;
		t2[pos].sum=min(a,t2[pos].sum);
		return ;
	}
    if(x<=mid) update2(lson,l,mid,x,k);
    else update2(rson,mid+1,r,x,k);
    pushup2(pos);
	return ;
}
```

最后，分别对所对应区间进行查询并相加。

**注意**：如果在进行操作2时，若其所给 $x=1$，那么对于$\left(\sum\limits_{i=1}^{x-1} \min(b,t_i)\right)$，其所对应的区间为 $1$ 至 $0$，非合法区间，应进行特判。具体操作详见代码部分。


## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lson (pos<<1)
#define rson (pos<<1|1)
#define mid ((l+r)>>1)
const int maxn=2e5+10;
int n,K,a,b,q;
struct seg
{
    int sum;
}t1[maxn<<2],t2[maxn<<2];
void pushup1(int pos){ t1[pos].sum=t1[lson].sum+t1[rson].sum;}
void pushup2(int pos){ t2[pos].sum=t2[lson].sum+t2[rson].sum;}
void build(int pos,int l,int r)
{
    if(l==r) {t1[pos].sum=0;t2[pos].sum=0;return ;}
    build(lson,l,mid);build(rson,mid+1,r);
    pushup1(pos);pushup2(pos);return;
}
void update1(int pos,int l,int r,int x,int k)
{
    if(l==x && x==r) {t1[pos].sum+=k;t1[pos].sum=min(b,t1[pos].sum);return ;}
    if(x<=mid) update1(lson,l,mid,x,k);
    else update1(rson,mid+1,r,x,k);
    pushup1(pos);return ;
}
void update2(int pos,int l,int r,int x,int k)
{
    if(l==x && x==r) {t2[pos].sum+=k;t2[pos].sum=min(a,t2[pos].sum);return ;}
    if(x<=mid) update2(lson,l,mid,x,k);
    else update2(rson,mid+1,r,x,k);
    pushup2(pos);return ;
}
int query1(int pos,int l,int r,int l1,int r1)
{
    if(l1<=l && r<=r1) return t1[pos].sum;
    int res=0;if(l1<=mid) res+=query1(lson,l,mid,l1,r1);
    if(r1>mid) res+=query1(rson,mid+1,r,l1,r1);
    return res;
}
int query2(int pos,int l,int r,int l1,int r1)
{
    if(l1<=l && r<=r1) return t2[pos].sum;
    int res=0;if(l1<=mid) res+=query2(lson,l,mid,l1,r1);
    if(r1>mid) res+=query2(rson,mid+1,r,l1,r1);
    return res;
}
signed main()
{
    //freopen("CF627B.in","r",stdin);
    //freopen("CF627B.out","w",stdout);
    cin>>n>>K>>a>>b>>q;
    build(1,1,n);
    for(int i=1,op,x,y;i<=q;i++)
    {
        cin>>op;
        if(op==1)
        {
            cin>>x>>y;
            update1(1,1,n,x,y);
            update2(1,1,n,x,y);
        }
        if(op==2)
        {
            cin>>x;
            if(x==1) cout<<query2(1,1,n,x+K,n)<<endl;//特判
            else cout<<query1(1,1,n,1,x-1)+query2(1,1,n,x+K,n)<<endl;
        }
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

```

---

## 作者：charleshe (赞：1)

写在前面：这题翻译是我写的，当我反应过来翻译错误时已经过审了，可以参考[这里](https://www.luogu.com.cn/discuss/459851)。

UPD：管理已经修改了，另外由于我翻译时忘记翻译输入顺序导致做题人对题意的疑惑，感谢帖中指出。这题第一行输入顺序是 $n$，$k$，$a$，$b$，$q$。

思路一：暴力，这里不插嘴。

思路二：用一个线段树或者树状数组维护这个序列，当遇到第二种操作时暴力去比较，但是仔细分析数据范围，明显超时。

思路三（正解）：

观察到第二题的式子中有 $\min(b,t_i)$ 和 $\min(a,t_i))$，再结合思路二失败的例子，不难想到使用两个树状数组，分别维护 $\min(b,t_i)$ 和 $\min(a,t_i))$，此时操作二的效率有着显著的提高，考虑处理操作一。

由于第一种操作是单点修改，因此我们可以把所修改的点的值直接从两个树状数组中提取出来，修改完以后判断有没有小于各自的 $a$ 和 $b$，如果没小于直接重新修改进去（单点增加给定的 $y$），否则需要修改为 $a$（或 $b$）。

注意这里提到的“修改为 $a$（或 $b$）”这一步，显然普通树状数组无法进行推平操作，但由于这里只是单点操作，所以我们设原本这个位置的数是 $t$，直接对该点增加 $a - t$（或 $b - t$）即可（显然 $t + a - t = a$）。

这样我们就需要维护两个可以进行单点修改，单点查询，区间查询的树状数组，而单点可以理解为一个长度为 $1$ 的区间，所以我们只需要维护两个可以进行单点修改和区间查询的树状数组即可。显然这是树状数组基本操作。不会的左转[树状数组模板](https://www.luogu.com.cn/problem/P3374)。

关于初始化：初始数组每一项均为 $0$，所以我们不用初始化，直接进行后面的操作即可。

代码：

```cpp
#include <iostream>
using namespace std;
int n,k,a,b,q;
int op,x,y;
int c1[200002],c2[200002];
int lowbit(int x){
	return x&(-x);
}
int sum1(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)) ans+=c1[i];
	return ans;
}
int sum2(int x){
	int ans=0;
	for(int i=x;i;i-=lowbit(i)) ans+=c2[i];
	return ans;
}
void add1(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)) c1[i]+=y;
}
void add2(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)) c2[i]+=y;
}//两个树状数组
int main(){
	cin>>n>>k>>a>>b>>q;
	for(int i=1;i<=q;i++){
		cin>>op;
		if(op==1){
			cin>>x>>y;
			int sum=sum1(x)-sum1(x-1);
			if(sum!=b){
				if(sum+y>b) add1(x,b-sum);
				else add1(x,y);
			}
			sum=sum2(x)-sum2(x-1);
			if(sum!=a){
				if(sum+y>a) add2(x,a-sum);
				else add2(x,y);
			}//对两个树状数组分别进行上述判断
		}
		else{
			cin>>x;
			cout<<sum1(x-1)+sum2(n)-sum2(x+k-1)<<endl;//操作二的式子
		}
	}
	return 0;
}
```

---

## 作者：wfc284 (赞：0)

用的是树状数组。  
一句话，修改的时候不要直接修改值，要修改其对答案的贡献。  
例：要将 $v$ 加上 $y$，不要 `add(y)`，要 `add(min(v+y, a)-v, y)`。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define re register
using namespace std;
const int N = 2e5+2,

int n, a, b, k, q;
int t1[N], t2[N];

int lowbit(int x) { return x & -x; }
class Fenwick {
	public:
		vector<int> c;
		Fenwick() { }
		Fenwick(int n) { c.resize(n+1); }
	
	public:
		void add(int idx, int v) { for(; idx <= n; idx += lowbit(idx)) c[idx] += v; }
		int query(int idx) {
			int res = 0;
			for(; idx; idx -= lowbit(idx)) res += c[idx];
			return res;
		}
		int query(int l, int r) { return l <= r? query(r) - query(l-1): 0; }
} tr1, tr2;

signed main() {
	cin >> n >> k >> a >> b >> q;
	tr1 = tr2 = Fenwick(n);
	while(q--) {
		int opt, x, y;
		scanf("%d%d", &opt, &x);
		if(opt == 1) {
			scanf("%d", &y);
			tr1.add(x, min(t1[x]+y, b) - t1[x]), tr2.add(x, min(t2[x]+y, a) - t2[x]);
			t1[x] = min(t1[x]+y, b), t2[x] = min(t2[x]+y, a);
		}
		else printf("%d\n", tr1.query(1, x-1) + tr2.query(x+k, n));
	}
	return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
给你一个数组 $t$，并有两种操作，一个是单点修改，一个求是区间一个奇怪操作的和，具体看题目，很好理解但很难绷，输出就是第二个操作的结果。
## 大体思路
这道题很板，但是我们需要两个树状数组，分别维护题目中那两个奇怪的算式 $\sum^{x-1}_ {i=1}\min(b,t_i)$ 和 $\sum^{n}_ {i=x+k}\min(a,t_i)$，思路也很好想，因为这是这个数组 $t$ 的两段，维护两个显然更方便。

观察到最后查询的时候是数组当前的数和 $b$ 或 $a$ 的最小值，由题意可知 $y\geq 0$，所以我们在单点修改的时候可以判断一下，如果 $+y$ 后大于 $b$ 或 $a$，我们就赋值成 $b$ 或 $a$，否则就直接加进去。

最后直接查询题目所给的式子即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,k,q;
int t1[200005],t2[200005];
int lowbit(int x){
	return x&(-x);
}
int cx1(int x){//对第一个树状数组的查询 
	int ans=0;
	while(x){
		ans+=t1[x];
		x-=lowbit(x);
	}
	return ans;
}
int cx2(int x){//对第二个树状数组的查询 
	int ans=0;
	while(x){
		ans+=t2[x];
		x-=lowbit(x);
	}
	return ans;
}
void xg1(int x,int y){//对第一个树状数组的查询修改 
	while(x<=n){
		t1[x]+=y;
		x+=lowbit(x);
	}
}
void xg2(int x,int y){//对第二个树状数组的查询 
	while(x<=n){
		t2[x]+=y;
		x+=lowbit(x);
	}
}
int main(){
	cin>>n>>k>>a>>b>>q;
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x,y;
			cin>>x>>y;
			int xx1=cx1(x)-cx1(x-1);
			if(xx1+y>b){
				xg1(x,b-xx1);
			}
			else{
				xg1(x,y);
			}//分别对第一个（上面）树状数组和第二个（下面）树状数组进行修改 
			int xx2=cx2(x)-cx2(x-1);
			if(xx2+y>a){
				xg2(x,a-xx2);
			}
			else{
				xg2(x,y);
			}
		}
		else{//查询那个奇怪的式子 
			int x;
			cin>>x;
			cout<<cx1(x-1)+cx2(n)-cx2(x+k-1)<<endl; 
		} 
	}
    return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF627B)

### 思路

本题的考察点是线段树。

因为题目的询问操作要求我们查询两段区间的和，题目需要我们完成两个操作，一个操作是单点修改，另一个操作是一个区间求和，其中单点修改并没有什么区别，下面主要说一下区间修改这个操作。

#### 区间求和

题目让我求两个区间的和，但其中查询的内容却并不相同，第一个让我们查询的内容是 $\sum\limits_{i=1}^{x-1} \min(b,t_i)$，而另一段则是 $\sum\limits_{i=x+k}^{n} \min(a,t_i)$，因此我们需要**两个不同的函数**，来实现区间和的操作，同时在线段树存储的变量中，我们也需要对这两个变量进行**分开处理**，这样我们就可以顺利地完成这个操作了。


### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

long long a, b;

struct node{
	int l, r;
	long long vala, valb, x;
}tree[N * 4];

void pushup(int i){
	tree[i].vala = tree[i << 1].vala + tree[i << 1 | 1].vala;
	tree[i].valb = tree[i << 1].valb + tree[i << 1 | 1].valb;
}

void build(int i, int l, int r){//建树。
	tree[i].l = l; tree[i].r = r;
	if(l == r){
		tree[i].x = 0;
		tree[i].vala = min(a, tree[i].x); tree[i].valb = min(b, tree[i].x);
		return ;
	}
	int mid = l + r >> 1;
	build(i << 1, l, mid);
	build(i << 1 | 1, mid + 1, r);
	pushup(i);
}

void add(int i, int l, int r, int k){//单点增加。
	if(tree[i].l == tree[i].r){
		tree[i].x += k;
		tree[i].vala = min(a, tree[i].x); tree[i].valb = min(b, tree[i].x);
		return ;
	}
	if(tree[i << 1].r >= l)add(i << 1, l, r, k);
	else add(i << 1 | 1, l, r, k);
	pushup(i);
}

long long find1(int i, int l, int r){//找第二段的和。
	if(tree[i].l >= l && tree[i].r <= r)return tree[i].vala;
	long long sum = 0;
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid)sum += find1(i << 1, l, r);
	if(r >= mid + 1)sum += find1(i << 1 | 1, l, r);
	return sum;
}

long long find2(int i, int l, int r){//找第一段的和。
	if(tree[i].l >= l && tree[i].r <= r)return tree[i].valb;
	long long sum = 0;
	int mid = tree[i].l + tree[i].r >> 1;
	if(l <= mid)sum += find2(i << 1, l, r);
	if(r >= mid + 1)sum += find2(i << 1 | 1, l, r);
	return sum;
}

int main(){
	int n, k, q;
	cin >> n >> k >> a >> b >> q;
	build(1, 1, n);
	while(q--){
		int op, x, y;
		cin >> op >> x;
		if(op == 1){
			cin >> y;
			add(1, x, x, y);
		}else{
			cout << (find2(1, 1, x - 1) + find1(1, x + k, n)) << endl;//查询答案。
		}
	}
}
```

---

## 作者：VitrelosTia (赞：0)

少有的自己写出来的数据结构题，虽然是板，但还是写篇题解纪念一下。

你发现这个 $a$ 和 $b$ 是固定的，那不妨维护和这两个查询时需要的信息 $\sum_i \min(a, t_i)$ 和 $\sum_i \min(b, t_i)$，这个东西维护起来非常简单，pushup 的时候从 ls 和 rs 合起来就行了。其他的就是板子了。

[Submission](https://codeforces.com/contest/627/submission/251680752)

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF627B)

题目中式子的含义：从 $t_1$ 到 $t_{x-1}$ 间所有数取 $\min(t_i,b)$ 的**和** $+$ 从 $t_{x+k}$ 到 $t_n$ 间所有数取 $\min(t_i,a)$ 的**和**。$(1\le i\le n)$

## 思路

一眼看起来这题就可以用线段树做。

**操作一**

最基本的线段树单点修改，可以看作一个长度为 $1$ 的区间进行修改。

```cpp
void add(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		tr[i].sum+=k;//sum 记录当前线段的和。
		tr[i].a=min(tr[i].sum,a);//a 与 b 方便接下来直接求值。
		tr[i].b=min(tr[i].sum,b);
		return ;
	}
   //上面是叶子节点修改，不用进行 push_down 操作。
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)add(i<<1,l,r,k);
	if(mid<r)add(i<<1|1,l,r,k);
    
   //上面是叶子节点修改，所以 push_up 操作不用比大小。
	tr[i].a=tr[i<<1].a+tr[i<<1|1].a;
	tr[i].b=tr[i<<1].b+tr[i<<1|1].b;
	return ;
}
```

**操作二**

分为两个函数进行，一个查询 

$$\sum^{x-1}_{i=1}\min(t_i,b)$$

另一个查询 

$$\sum^{n}_{i=x+k}\min(t_i,a)$$

上面操作一的代码已经判断了 $\min(t_i,a)$ 与 $\min(t_i,b)$ $(1\le i\le n)$，不用再进行其他操作。这样，我们就可以把这个表达式转化为两段线段树区间求和。

```cpp
ll qa(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].a;
	int mid=tr[i].l+tr[i].r>>1;
	ll res=0;
	if(l<=mid)res+=qa(i<<1,l,r);
	if(mid<r)res+=qa(i<<1|1,l,r);
	return res;
}
ll qb(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].b;
	int mid=tr[i].l+tr[i].r>>1;
	ll res=0;
	if(l<=mid)res+=qb(i<<1,l,r);
	if(mid<r)res+=qb(i<<1|1,l,r);
	return res;
}
```

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
void print(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    print(x/10);
	putchar(x%10+'0');
    return ;
}
const int N=2e5+10;
int n,k,q;
ll a,b;
struct node{
	int l,r;
	ll a,b,sum;
}tr[N<<2];
void build(int i,int l,int r){
	tr[i].l=l;
	tr[i].r=r;
	if(l==r)return ;
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	return ;
}
void add(int i,int l,int r,ll k){
	if(l<=tr[i].l&&tr[i].r<=r){
		tr[i].sum+=k;
		tr[i].a=min(tr[i].sum,a);
		tr[i].b=min(tr[i].sum,b);
		return ;
	}
	int mid=tr[i].l+tr[i].r>>1;
	if(l<=mid)add(i<<1,l,r,k);
	if(mid<r)add(i<<1|1,l,r,k);
	tr[i].a=tr[i<<1].a+tr[i<<1|1].a;
	tr[i].b=tr[i<<1].b+tr[i<<1|1].b;
	return ;
}
ll qa(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].a;
	int mid=tr[i].l+tr[i].r>>1;
	ll res=0;
	if(l<=mid)res+=qa(i<<1,l,r);
	if(mid<r)res+=qa(i<<1|1,l,r);
	return res;
}
ll qb(int i,int l,int r){
	if(l<=tr[i].l&&tr[i].r<=r)return tr[i].b;
	int mid=tr[i].l+tr[i].r>>1;
	ll res=0;
	if(l<=mid)res+=qb(i<<1,l,r);
	if(mid<r)res+=qb(i<<1|1,l,r);
	return res;
}
int main(){
	cin>>n>>k>>a>>b>>q;
	build(1,1,n);
	while(q--){
		int op=read(),x=read();
		if(op==1){
			ll k=read();
			add(1,x,x,k);
		}
		else printf("%lld\n",qb(1,1,x-1)+qa(1,x+k,n));
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/144202550)

---

## 作者：COsm0s (赞：0)

题面本身明显是一道数据结构。

我们观察数据范围，$n\leq 2\times 10^5$ 很容易让人想到线段树或者分块之类的维护。

由于前者的理论复杂度更小，所以本题解采用前者。

注意到 $a,b$ 是给定的，所以，$t_i$ 与 $a,b$ 的大小关系就是唯一的。

同时，我们发现修改只有单点修改。所以，我们每次修改，只会影响一个位置，我们在线段树上找到这一个端点，由于修改操作是修改值而不是替换，所以我们要记录每一个点的当前值。

那么设当前点真实值为 $x$，则答案为 $\min(a,x)$ 或 $\min(b,x)$，注意分开维护，这东西直接放在线段树就行了。

所以每次查询时只要指定 $a,b$ 的影响，就可以在 $\Theta(\log n)$ 的时间内求解了。

总复杂度 $\Theta(q\log n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
namespace Jelly {
	int n, a, b, k, q;
	struct Seg_tree {
		int val, a_val, b_val;
	} tree[N << 2];
	void UpDate(int l, int r, int x, int aim, int val) {
		if (l == r) {
			tree[x].val += val;
			tree[x].a_val = min(a, tree[x].val);
			tree[x].b_val = min(b, tree[x].val);
			return ;
		}
		int mid = l + r >> 1;
		if (mid >= aim) UpDate(l, mid, x << 1, aim, val);
		else UpDate(mid + 1, r, x << 1 | 1, aim, val);
		tree[x].val = tree[x << 1].val + tree[x << 1 | 1].val;
		tree[x].a_val = tree[x << 1].a_val + tree[x << 1 | 1].a_val;
		tree[x].b_val = tree[x << 1].b_val + tree[x << 1 | 1].b_val;
	}
	int get(Seg_tree x, bool flag) {
		if (flag) return x.a_val;
		return x.b_val;
	}
	int Query(int l, int r, int L, int R, int x, bool p) {
		if (R < l || r < L || L > R) return 0;
		if (L <= l && r <= R) return get(tree[x], p);
		int mid = l + r >> 1;
		return Query(l, mid, L, R, x << 1, p) + Query(mid + 1, r, L, R, x << 1 | 1, p);
	}
	int main() {
		cin >> n >> k >> a >> b >> q;
		while (q --) {
			int opt, x, y;
			cin >> opt >> x;
			if (opt == 1) cin >> y, UpDate(1, n, 1, x, y);
			else cout << Query(1, n, 1, x - 1, 1, 0) + Query(1, n, x + k, n, 1, 1) << '\n';
		}
		return 0;
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Jelly::main();
	return 0;
}
```


---

## 作者：Maysoul (赞：0)

## 简述思路：

暴力枚举每一个数再与之比较显然会超时，我们考虑对区间的操作。

想到区间操作，那么线段树必然是不二之选。

操作 $1$ 是单点修改自然没什么好说，这题的主要难度体现在另外一个操作上。

它要求我们求出 $\left(\sum\limits_{i=1}^{x-1} \min(b,t_i)\right) + \left(\sum\limits_{i=x+k}^{n} \min(a,t_i)\right)$。

把这个式子翻译一下，也就是求出区间 $\left [ 1 ,x-1\right ]$ 中数组元素与 $b$ 的最小值之和，加上 $\left [ x+k,n \right ]$ 中数组元素与 $a$ 最小值之和。

显然，在这个数组中，只有当前元素 $ > a $ 或者 $>b$ 的时候，才会对结果产生贡献，那么我们只需要在修改的时候，将当前元素与 $a$ 和 $b$ 分别比较一下大小即可。

具体的，我们需要维护两个值，他们分别映射了 $\sum\limits_{i=l}^{r} \min(b,t_i)$ 和 $ \sum\limits_{i=l}^{r} \min(a,t_i)$，在每一个叶子节点中，当元素比 $a$ 或 $b$ 小的时候，它的值为 $a$ 或 $b$，反之更新为当前元素即可。

## CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+10;
int num,ans;
struct node{
	int l,r;
	int bsum,asum,sum;
	int acnt,bcnt;
	node(){
		l=r=-1;
		bsum=asum=sum=0;//分别维护
		acnt=bcnt=0;
		sum=0;
	}
}ts[4*MAXN+5];
int a,b,k,n,q;
void build(int id,int l,int r)
{
	ts[id].l=l;
	ts[id].r=r;
	if(l!=r){
		int mid=l+(r-l)/2;
		int lcid=id*2;
		int rcid=lcid+1;
		build(lcid,l,mid);
		build(rcid,mid+1,r);
	} 
}
void putup(int id,int lcid,int rcid)
{
	ts[id].acnt=ts[lcid].acnt+ts[rcid].acnt;
	ts[id].bcnt=ts[lcid].bcnt+ts[rcid].bcnt;
	ts[id].asum=ts[lcid].asum+ts[rcid].asum;
	ts[id].bsum=ts[lcid].bsum+ts[rcid].bsum;
}
void update(int id,int goal,int val)
{
	if(ts[id].l==ts[id].r){
		if(ts[id].l==goal){
			ts[id].sum+=val;
			if(ts[id].sum<=a) ts[id].asum=ts[id].sum;//判断更新
			else ts[id].asum=a;
			if(ts[id].sum<=b) ts[id].bsum=ts[id].sum;
			else ts[id].bsum=b;
		}
		return;
	}
	int mid=(ts[id].l+ts[id].r)/2;
	int lcid=id*2;
	int rcid=lcid+1;
	if(goal<=mid) update(lcid,goal,val);
	if(goal>mid) update(rcid,goal,val);
	putup(id,lcid,rcid);
	return;
}
int show(int id,int l,int r,bool ab)
{
	if(l>r) return 0;
	if(ts[id].l>=l&&ts[id].r<=r){
		if(ab==1) return ts[id].bsum;
		else return ts[id].asum;
	}
	int mid=(ts[id].l+ts[id].r)/2;
	int lcid=id*2;
	int rcid=lcid+1;
	int tot=0;
	if(l<=mid) tot+=show(lcid,l,r,ab);
	if(r>mid) tot+=show(rcid,l,r,ab);
	return tot;
}
int main()
{
	cin>>n>>k>>a>>b>>q;
	build(1,1,n);
	int opt,x,y;
	for (int i=1;i<=q;i++){
		cin>>opt;
		if(opt==1){
			cin>>x>>y;
			update(1,x,y);
		}
		else{
			cin>>x;
			cout<<show(1,1,x-1,1)+show(1,x+k,n,0)<<endl;
		}
	}
}
```



---

## 作者：_JF_ (赞：0)

## CF627B Factory Repairs 

考虑当前每个数的贡献，下面以 $a$ 举例。

- 如果当前的 $x> a$，那它对于答案的贡献就是 $a$。

- 如果当前的 $x \le a$，那它对答案的贡献就是 $x$。

不难发现，对于大于等于 $a$ 的数，他对答案的贡献与出现次数有关系。而对于小于 $a$ 的数，用数据结构维护它的和就好。

所以答案就出来了，我们只用维护大于等于 $a$ 的数的个数以及小于 $a$ 的数的和。

具体的实现方式看代码即可。直接在 $t$ 数组上改。然后根据我们的定义具体实现即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=1e6+10;
#define int long long 
int t[INF<<1];
template <class T,const int N> class treeA{
	struct node{
		int sum,num;
	}Tree[N<<2];
	public:
		void updateSum(int l,int r,int s,int t,int p,int val){
			if(l<=s&&t<=r){
				Tree[p].sum+=val;
				return ;
			}
			int mid=(s+t)>>1;
			if(l<=mid)	updateSum(l,r,s,mid,p<<1,val);
			if(r>mid)	updateSum(l,r,mid+1,t,p<<1|1,val);
			Tree[p].sum=Tree[p<<1].sum+Tree[p<<1|1].sum;
		}
		void updateNum(int l,int r,int s,int t,int p){
			if(l<=s&&t<=r){
				Tree[p].num++;
				return ;
			}
			int mid=(s+t)>>1;
			if(l<=mid)	updateNum(l,r,s,mid,p<<1);
			if(r>mid)	updateNum(l,r,mid+1,t,p<<1|1);
			Tree[p].num=Tree[p<<1].num+Tree[p<<1|1].num;
		}
		T Querynum(int l,int r,int s,int t,int p){
			if(l<=s&&t<=r)	return Tree[p].num;
			int mid=(s+t)>>1,ans=0;
			if(l<=mid)	ans+=Querynum(l,r,s,mid,p<<1);
			if(r>mid)	ans+=Querynum(l,r,mid+1,t,p<<1|1);
			return ans;
		}
		T Querysum(int l,int r,int s,int t,int p){
			if(l<=s&&t<=r)	return Tree[p].sum;
			int mid=(s+t)>>1,ans=0;
			if(l<=mid)	ans+=Querysum(l,r,s,mid,p<<1);
			if(r>mid)	ans+=Querysum(l,r,mid+1,t,p<<1|1);
			return ans;
		}
		
};
signed main(){
	treeA<int,INF>TreeA,TreeB;
	int n,k,a,b,q;
	cin>>n>>k>>a>>b>>q;
	while(q--){
		int opt,x,y;
		cin>>opt;
		if(opt==1){
			cin>>x>>y;
			if(t[x]<a&&t[x]+y>a)	
				TreeA.updateSum(x,x,1,n,1,-t[x]),TreeA.updateNum(x,x,1,n,1);
			if(t[x]<b&&t[x]+y>b)	
				TreeB.updateSum(x,x,1,n,1,-t[x]),TreeB.updateNum(x,x,1,n,1);
			if(t[x]<a&&t[x]+y<a)	
				TreeA.updateSum(x,x,1,n,1,y);
			if(t[x]<b&&t[x]+y<b)	
				TreeB.updateSum(x,x,1,n,1,y);
			t[x]+=y;
			if(t[x]==a)	TreeA.updateSum(x,x,1,n,1,-t[x]),TreeA.updateNum(x,x,1,n,1);
			if(t[x]==b)	TreeB.updateSum(x,x,1,n,1,-t[x]),TreeB.updateNum(x,x,1,n,1);
		}
		else{
			cin>>x;
			int num1=0,Sum1=0,num2=0,Sum2=0;
			if(x-1>0)
				num1=TreeB.Querynum(1,x-1,1,n,1),Sum1=TreeB.Querysum(1,x-1,1,n,1);
			if(x+k<=n)
				num2=TreeA.Querynum(x+k,n,1,n,1),Sum2=TreeA.Querysum(x+k,n,1,n,1); 
			cout<<Sum1+Sum2+num1*b+num2*a<<endl;
//			cout<<Sum1<<" "<<Sum2<<" "<<num1<<" "<<num2<<endl;
		}
	}
}
//Sum: 比a,b小的数的和，num：比a,b的数值大于等于的数的个数 
```


---

## 作者：technopolis_2085 (赞：0)

分析：

先考虑暴力。

很好做，$O(1)$ 修改，$O(n)$ 查询。

代码不给出了。

正解：

观察题面，单点修改，区间查询，可以用树状数组做。

开一个标记数组记录当前每个数组中的元素值。

直接开 $6$ 个树状数组，分别是从左往右的前缀和，超过 $b$ 的数的和，和超过 $b$ 的数的个数。从右往左的同理。

对于每次修改，考虑先对前缀和数组加上增加值 $y$，然后比较增加后的值与 $a$ 或 $b$ 的大小。

右边更新同理。

输出时：

以左边为例。

先将答案记为 $t_1$ 到 $t_{x-1}$ 的和，减去大于等于 $b$ 的数的和，再加上大于等于 $b$ 的数的个数乘上 $b$。

右边的同理。

记得开 long long。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=2e5+10;
int suml[maxn],suml1[maxn],cntl[maxn];
int sumr[maxn],sumr1[maxn],cntr[maxn];
int num[maxn];
int n,k,a,b,q;

int lowbit(int x){
	return x&(-x);
}

void modify_l(int i,int x,int op){
	while (i<=n){
		if (op==1) suml[i]+=x;
		else if (op==2) suml1[i]+=x;
		else cntl[i]+=x;
		
		i+=lowbit(i);
	}
}

void modify_r(int i,int x,int op){
	while (i>=1){
		if (op==1) sumr[i]+=x;
		else if (op==2) sumr1[i]+=x;
		else cntr[i]+=x;
		
		i-=lowbit(i);
	}
}

int query_l(int i,int op){
	int ans=0;
	while (i>=1){
		if (op==1) ans+=suml[i];
		else if (op==2) ans+=suml1[i];
		else ans+=cntl[i];
		
		i-=lowbit(i);
	}
	
	return ans;
}

int query_r(int i,int op){
	int ans=0;
	
	while (i<=n){
		if (op==1) ans+=sumr[i];
		else if (op==2) ans+=sumr1[i];
		else ans+=cntr[i];
		
		i+=lowbit(i);
	}
	
	return ans;
}

signed main(){
	scanf("%lld%lld%lld%lld%lld",&n,&k,&a,&b,&q);
	swap(a,b);
	
	while (q--){
		int op;
		scanf("%lld",&op);
		
		if (op==1){
			int x,y;
			scanf("%lld%lld",&x,&y);
			
			modify_l(x,y,1);
			modify_r(x,y,1);
			
			if (num[x]<a&&num[x]+y>a){
				modify_l(x,num[x]+y,2);
				modify_l(x,1,3);
			}else if (num[x]>a&&num[x]+y<=a){
				modify_l(x,-num[x],2);
				modify_l(x,-1,3);
			}else if (num[x]>=a&&num[x]+y>=a){
				modify_l(x,y,2);
			}
			
			if (num[x]<b&&num[x]+y>=b){
				modify_r(x,num[x]+y,2);
				modify_r(x,1,3);
			}else if (num[x]>b&&num[x]+y<=b){
				modify_r(x,-num[x],2);
				modify_r(x,-1,3);
			}else if (num[x]>=b&&num[x]+y>=b){
				modify_r(x,y,2);
			}
			
			num[x]+=y;
		}else{
			int x;
			scanf("%lld",&x);
			
			int ans=0;
			ans+=query_l(x-1,1);
			int num=query_l(x-1,3);
			
			if (num>0){
				ans-=query_l(x-1,2);
				ans+=num*a; 
			}
			
			x+=k;
			
			ans+=query_r(x,1);
			num=query_r(x,3);
			
			if (num>0){
				ans-=query_r(x,2);
				ans+=num*b;
			}
			
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```


---

