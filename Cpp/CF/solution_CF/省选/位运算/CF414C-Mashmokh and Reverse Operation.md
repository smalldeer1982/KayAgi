# Mashmokh and Reverse Operation

## 题目描述

Mashmokh's boss, Bimokh, didn't like Mashmokh. So he fired him. Mashmokh decided to go to university and participate in ACM instead of finding a new job. He wants to become a member of Bamokh's team. In order to join he was given some programming tasks and one week to solve them. Mashmokh is not a very experienced programmer. Actually he is not a programmer at all. So he wasn't able to solve them. That's why he asked you to help him with these tasks. One of these tasks is the following.

You have an array $ a $ of length $ 2^{n} $ and $ m $ queries on it. The $ i $ -th query is described by an integer $ q_{i} $ . In order to perform the $ i $ -th query you must:

- split the array into $ 2^{n-q_{i}} $ parts, where each part is a subarray consisting of $ 2^{q_{i}} $ numbers; the $ j $ -th subarray $ (1<=j<=2^{n-q_{i}}) $ should contain the elements $ a[(j-1)·2^{q_{i}}+1],a[(j-1)·2^{q_{i}}+2],...,a[(j-1)·2^{q_{i}}+2^{q_{i}}] $ ;
- reverse each of the subarrays;
- join them into a single array in the same order (this array becomes new array $ a $ );
- output the number of inversions in the new $ a $ .

Given initial array $ a $ and all the queries. Answer all the queries. Please, note that the changes from some query is saved for further queries.

## 说明/提示

If we reverse an array $ x[1],x[2],...,x[n] $ it becomes new array $ y[1],y[2],...,y[n] $ , where $ y[i]=x[n-i+1] $ for each $ i $ .

The number of inversions of an array $ x[1],x[2],...,x[n] $ is the number of pairs of indices $ i,j $ such that: $ i&lt;j $ and $ x[i]&gt;x[j] $ .

## 样例 #1

### 输入

```
2
2 1 4 3
4
1 2 0 2
```

### 输出

```
0
6
6
0
```

## 样例 #2

### 输入

```
1
1 2
3
0 1 1
```

### 输出

```
0
1
0
```

# 题解

## 作者：cirnovsky (赞：15)

## 题意简述

给出一个长度为 $2^n$ 的序列，$m$ 次操作，每次操作给出一整数 $q$，把该序列分成连续的长度均为 $2^q$ 的 $2^{n-q}$ 段后，把每段反转，并查询反转后整体的逆序对数。

## 题解

考虑一次反转后对整个序列造成的影响。

每次操作相当于把整个序列分成了 $2^{n-q}$ 个块，我们只需要考虑块内和块外。

考虑一个块对其他块的情况。

嗯。

没有影响，完。

那么我们只需要考虑如何快速计算出每个块内的变化即可。

像归并排序一样考虑问题，把序列分成 $n$ 层（把二叉树画出来）。

要反转区间 $[l,r]$ 就要翻转 $[l,m],[m+1,r],m=\lfloor\frac{l+r}{2}\rfloor$，以此类推。

然后就预处理出每一层顺序对逆序对即可。

```cpp
#include <cstdio>
#define LL long long

const int MAXN = ( 1 << 20 ) + 5, MAXM = 1e6 + 5;

LL rint () {
	LL x = 0, f = 1; char c = getchar ();
	for ( ; c < '0' || c > '9'; c = getchar () )	f = c == '-' ? -1 : f;
	for ( ; c >= '0' && c <= '9'; c = getchar () )	x = ( x << 3 ) + ( x << 1 ) + ( c & 15 );
	return x * f;
}

template<typename _T>
void wint ( _T x ) {
	if ( x < 0 )	putchar ( '-' ), x = ~ x + 1;
	if ( x > 9 )	wint ( x / 10 );
	putchar ( x % 10 ^ '0' );
}

template<typename _T> void swapp ( _T &x, _T &y ) { _T w = x; x = y; y = w; }

int n, m, ts, a[MAXN], fm[MAXN];
LL cnt[25][2];

void Merge ( const int l, const int r, const int x ) {
	if ( l >= r )	return;
	int mid = ( l + r ) >> 1;
	Merge ( l, mid, x - 1 ), Merge ( mid + 1, r, x - 1 );
	int i = l, j = mid + 1;
	for ( ; i <= mid && j <= r; ) {
		if ( a[i] < a[j] )	cnt[x][1] += r - j + 1, ++ i;
		else	++ j;
	}
	i = l, j = mid + 1;
	int s = 0;
	for ( ; i <= mid && j <= r; ) {
		if ( a[i] > a[j] )	cnt[x][0] += mid - i + 1, fm[s ++] = a[j ++];
		else	fm[s ++] = a[i ++];
	}
	for ( ; i <= mid; fm[s ++] = a[i ++] ) ;
	for ( ; j <= r; fm[s ++] = a[j ++] ) ;
	for ( int i = l; i <= r; ++ i )	a[i] = fm[i - l];
}

int main () {
	n = rint ();
	for ( int i = 1; i <= ( 1 << n ); ++ i )	a[i] = rint ();
	Merge ( 1, 1 << n, n );
	m = rint ();
	for ( int _ = 1; _ <= m; ++ _ ) {
		int x = rint ();
		LL res = 0;
		while ( x -- > 0 )	swapp ( cnt[x + 1][0], cnt[x + 1][1] );
		for ( int i = 1; i <= n; ++ i )	res += cnt[i][0];
		wint ( res ), putchar ( '\n' );
	}
	return 0;
}
```

---

## 作者：DarkMoon_Dragon (赞：6)

~~真的被楼上@Lucifer__X07的模板给震惊到了~~  
说实话，这道题至少是个紫题吧(甚至想用$splay$来写)
## description
给你$2^n$个数，每次操作将其分成$2^k$份，对于每一份内部的数进行翻转，每次操作完后输出操作后的$2^n$个数的逆序数。
### 样例解释：
原序列 2 1 4 3  
第一次每$2^1$交换变成$ 1 ~2 ~3~ 4$，$ans=0;$  
第二次$2^2$全部交换变成$ 4~ 3~ 2~ 1$，$ans=6;$  
第三次不变 $ans=0;$  
第四次再交换回来，$ans=0.$
### 关于思路
看到每次$2^n$操作，~~不难想到用分治~~  
然后将二叉树按题意画成分治树 
```            
                      层数k：
       [2,1,4,3]        3rd
      /         \  
    [2,1]      [4,3]    2nd
    /   \      /   \
    2   1      4   3    1st
```
如果按照每层运用**归排思想**的话每层答案便是**自身区间逆序对数和同级右边的区间逆序对数之和**，比如说第二层，[2,1]一对，2和后面0对，1和后面0对。  
然后通过模拟样例可以发现**同级小区间翻转不影响大区间答案**（即层数更高的答案以及右边的答案）,也**就相当于让你翻转2^k的区间只用把2^0~2^k的区间翻转就可以了**。  
便可以开一个`sum[k][0,1]`数组记录层数为k时，dep区间`[l,r)`中`[l,mid)`和`[mid,r)`的逆序对数,为什么左闭右开呢，`stl merge_sort:[l,mid),[mid,r)` 直接传三个参数就可以了  
但是仔细思考后不难发现（~~闭着眼睛发现~~）为什么要$merge$呢，不是直接$sort$吗
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define rr register int
using namespace std;
typedef long long ll;
inline int read(){
    char i=getchar();
    int f=1,res=0;
    while(i<'0'||i>'9'){if(i=='-')f=-1;i=getchar();}
    while(i>='0'&&i<='9'){res=res*10+i-'0';i=getchar();}
    return res*f;
}
const int N=20;
int a[1<<N],n,m;
ll sum[30][2];//0左儿子 1右儿子  
ll mi[30];
//翻转逆序对个数,即转化为1.两数都在各自儿子区间 2.两数在不同儿子区间 
inline void merge(int l,int r,int dep){//从高到低第几层，根节点最高 
    int mid=(l+r)>>1;
//  l,r 是[,) 
    if(l+1<r){
        merge(l,mid,dep-1);
        merge(mid,r,dep-1);
        ll cnt=0;
        for(rr i=l;i<mid;++i){
        	cnt+=lower_bound(a+mid,a+r,a[i])-a-mid;
        }
        sum[dep][0]+=cnt;
        cnt=0;
        for(rr i=mid;i<r;++i){
        	cnt+=lower_bound(a+l,a+mid,a[i])-a-l;
        }
        sum[dep][1]+=cnt;
        inplace_merge(a+l, a+mid, a+r);//stl merge_sort [l,mid),[mid,r)
        //这里sort也可以
    }
}
int main(){
    int n,q,u;
    mi[0]=1;
    for(rr i=1;i<30;++i) mi[i]=mi[i-1]<<1;
    scanf("%d",&n);
    for(rr i=0;i<mi[n];++i) a[i]=read();
    merge(0,mi[n],n);
    q=read();
    ll ans;
    while(q--){
        u=read();
        ans=0;
        while(u--) swap(sum[u+1][0],sum[u+1][1]);
        for(rr i=0;i<=n;++i) ans+=sum[i][0];
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：FreeTimeLove (赞：5)

## 一、题意

给定长为 $2^n$ 的序列 $a$，每次给定 $q$，将 $a$ 分为长度为 $2^q$ 的 $2^{n-q}$ 段并翻转每一段，求每次翻转后的序列逆序对数。

## 二、思路

如果将序列 $a$ 放在一棵**假想**线段树上，自下而上数第 $k$ 层恰为长度 $2^{k-1}$ 的段。观察一次操作，可以发现相当于**翻转**第 $1$ 至 $q+1$ 层。设 $b_{i ,0}$ 为第 $i+1$ 层的逆序对，$b_{i ,1}$ 为第 $i+1$ 层的顺序对，
那么翻转第 $1$ 至 $q+1$ 层相当于交换 $i\in[0,q]$ 的 $b_{i,0}$ 和 $b_{i,1}$。

如果我们能够预处理出每一层的逆序对数与顺序对数，那么操作时暴力修改即可。考虑在**假想树**的树形结构上进行**权值线段树合并**，合并一个节点的两个子节点即可求出两个子区间之间的逆序对数即顺序对数。

先假设所有数**两两不同**。如果左树为空，我们就将计数器加上右树的数值个数；如果右树为空，我们就将逆序对数加上左子树的数值个数与计数器之**积**。由于我们维护的是权值线段树，且合并时按数值大小升序合并，因此更新答案时左树的数值一定**大于**计数器记录的所有数的值。顺序对数
即为总对数减去逆序对数。

如果有的数相同，就需要额外给顺序对减去相等的对数（既不是逆序对又不是顺序对），即在叶节点计算左右子树数值个数之积。



### AC code

```cpp
//written_by_FTL
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#define ll long long
#define LD long double
#define i7 __int128
#define re return
#define con continue
using namespace std;
const int N=1048580+5;
int rd(){
	int ans=0,f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while(ch>='0'&&ch<='9')ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	re f?-ans:ans;
}
int n,q,m,rt[N<<1],nw,bk[25],d[N<<1],INF=1e9,P;
ll b[25][2],sum;
namespace SGT{
	#define t d[v]
	#define tx d[vx]
	#define vl t.sl
	#define vr t.sr
	#define tl d[vl]
	#define tr d[vr]
	#define mid ((L+R)>>1)
	int num=0;
	struct data{
		int sl=0,sr=0;int s=0;
	}d[N*35];
	void pu(int v){
		t.s=tl.s+tr.s;
	}
	void ud(int x,int L,int R,int &v){
		if(!v)v=++num;
		if(L==R){t.s++;re;}
		if(mid>=x)ud(x,L,mid,vl);
		else ud(x,mid+1,R,vr);
		pu(v);
	}
	void mg(int vx,int L,int R,int &v){
		if(!vx){b[P][0]+=(ll)t.s*nw;re;}
		if(!v){nw+=tx.s;v=vx;re;}
		if(L==R){b[P][0]+=(ll)t.s*nw,nw+=tx.s;b[P][1]-=(ll)t.s*tx.s;t.s+=tx.s;re;}
		mg(tx.sl,L,mid,vl),mg(tx.sr,mid+1,R,vr);
		pu(v);
	}
	#undef t
	#undef mid
}
void dfs(int u){
	if(d[u]==n){SGT::ud(rd(),1,INF,rt[u]);re;}
	for(int v=u<<1;v<=(u<<1|1);v++){
		d[v]=d[u]+1,dfs(v);
		if(v&1)P=n-d[u],nw=0,SGT::mg(rt[v],1,INF,rt[u]);
		else rt[u]=rt[v];
	}
}
int main(){
	n=rd(),q=1<<n;
	dfs(1);
	for(int i=1;i<=n;i++)b[i][1]+=(1ll<<(n+i-2))-b[i][0];
	m=rd();
	for(int i=1;i<=m;i++){
		bk[rd()]^=1;
		sum=nw=0;
		for(int j=n;j;j--)nw^=bk[j],sum+=b[j][nw];
		printf("%lld\n",sum);
	}
	re 0;
}
```

### $\text{The End.}$

---

## 作者：Lucifer_Bartholomew (赞：4)

# ~~逆序对模板~~
**手写归并排序，排序过程中计算逆序对**

不会的请：[逆序对归并排序实现](https://baike.baidu.com/item/%E9%80%86%E5%BA%8F%E5%AF%B9/11035554)
```
#include<cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long cnt[22][2];//cnt[][0]记录逆序对，cnt[][1]记录顺序对
int n,a[2000010],b[2000010],m,q;
void msort(int l,int r,int len)//归并排序
{
    if(l>=r)return;
    long long mid=(l+r)>>1;
    msort(l,mid,len-1);
    msort(mid+1,r,len-1);
    long long i=l,j=mid+1,res=0;
    while(i<=mid&&j<=r)
    {
        if(a[i]<a[j])
        {
            cnt[len][1]+=r-j+1;//求顺序对
            i++;
        }
        else j++;
    } 
    i=l;
    j=mid+1;
    while(i<=mid&&j<=r)
    {
        if(a[i]>a[j])
        {
            cnt[len][0]+=mid-i+1;//求逆序对
            b[res++]=a[j++];
        }
        else b[res++]=a[i++];
    }
    while(i<=mid)b[res++]=a[i++];
    while(j<=r)b[res++]=a[j++];
    for(int i=l;i<=r;++i)
        a[i]=b[i-l];
}
int main()
{
    scanf("%d",&n);
    {
        long long t=1<<n;
        for(long long i=1;i<=t;++i)
            scanf("%d",&a[i]);
        msort(1,t,n);
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d",&q);
            long long ans=0;
            for(int i=1;i<=n;++i)
            {
                if(i<=q)swap(cnt[i][0],cnt[i][1]);//序列反转，逆序对数和顺序对数相应交换
                ans+=cnt[i][0];
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}
```
~~我是蒟蒻~~

---

## 作者：MrcFrst (赞：2)

### $\text{Links}$

[cnblogs](https://www.cnblogs.com/MrcFrst-LRY/p/17871400.html)
[Luogu](https://www.luogu.com.cn/problem/CF414C)
[Codeforces](https://codeforces.com/problemset/problem/414/C)

--------------

### 题意

给定一个长为 $2^n$ $(n\le 20)$ 的序列 $a$，有 $m$ $(m\le 10^6)$ 次操作，每次操作给出 $q$ $(q\le n)$，表示将序列从左至右按 $2^q$ 一段分成连续的 $2^{n-q}$ 段，将每一段反转，然后询问此时序列的逆序对数。

-----------------------

### 题解

考虑把这个 $\text{reverse}$ 操作放到线段树上，相当于先 $\text{reverse}$ 它的左右两个子区间然后把它俩 $\text{swap}$。

第一步可以直接递归分治进行，考虑第二步对答案的影响。按块内和块间分开考虑，块内相当于原来的贡献是 $\sum [a_i>a_j,i\in left,j\in right]$，$\text{swap}$ 之后变成了 $\sum [a_i>a_j,i\in right,j\in left]$。

那么我们在原序列上进行归并排序，过程中记录 $cnt_{i,0/1}$，分别表示第 $i$ 层所有的左子区间对右子区间的贡献和右子区间对左子区间的贡献之和，即上面那两个式子。

每次操作相当于把 $q$ 及其以下的所有层的 $cnt_{0/1}$ $\text{swap}$，然后查询 $\sum_{x=1}^{n} cnt_{x,0}$。

于是就做完了，实际上并不需要用到线段树，只是利用了线段树上的分治思想。

时间复杂度为 $O((n+m)\log n)$，其中 $n$ 为序列长度，$m$ 为操作数。

#### $\text{Code}$

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2)?EOF:*p1++)
char buf[1<<22],*p1=buf,*p2=buf;
const int N=2e6;
int n,a[N],cnt[22][2],b[N],m;
il int read(){
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
il void solve(int l,int r,int dep){
    if(l==r)return;
    re int mid=(l+r)>>1,i=mid+1,j=l,pos=l;
    solve(l,mid,dep-1),solve(mid+1,r,dep-1);
    while(i<=r){
        while(j<=mid&&a[j]<a[i])b[pos++]=a[j++];
        cnt[dep][1]+=j-l;
        while(j<=mid&&a[j]==a[i])b[pos++]=a[j++];
        cnt[dep][0]+=mid-j+1;
        b[pos++]=a[i++];
    }
    while(j<=mid)b[pos++]=a[j++];
    for(re int i=l;i<=r;i++)a[i]=b[i];
}
signed main(){
    n=read();
    for(re int i=1;i<=(1<<n);i++)a[i]=read();
    solve(1,1<<n,n);
    m=read();
    while(m--){
        int q=read();
        while(q)swap(cnt[q][0],cnt[q][1]),q--;
        re int res=0;
        for(re int i=1;i<=n;i++)res+=cnt[i][0];
        cout<<res<<'\n';
    }
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：1)

## 思路

我们假象着建一颗线段树，定义**从下往上**为第 $1\sim n$ 行，第i行的每块长即为 $2^{i-1}$（其实就是你想象中的那种线段树）。

那么我们考虑对于一次询问 $q$，其操作后对我们的线段树的影响是什么。可以发现其实就是把我们的线段树从第 $q$ 行一直修改到第 $1$ 行。这里我们对第 $k$ 行的**修改**指的是把第 $k$ 行的每个节点的两个儿子交换。

现在我们来考虑一次询问 $q$ 如何求出答案。考虑子问题：若干我们要对线段树的第 $k$ 行进行修改，那么会对答案有多少贡献？如何快速求出这个贡献值？

我们可以考虑维护两个数组 $u_k,d_k$，分别表示第 $k$ 行的顺序对数量和逆序对数量。那么在我们修改第 $k$ 行时，就要把 $u_k,d_k$ 交换，然后把 $d_k$ 加入答案中。

下面我们给第 $k$ 行的逆序对数量下定义：我们定义一个块 $[l,r]$ 中的逆序对数量为二元组 $(x,y)$（$x,y$ 为下标）的数量，满足 $x\in[l,mid],y\in[mid+1,r]$ 且 $a_x>a_y$（$a_x$ 表示 $x$ 位置的值）。第 $k$ 行的逆序对数量即第k行中所有块的逆序对数量之和。

注意在预处理 $u_k,d_k$ 时要排除相等的数字。预处理使用线段树合并即可。当然归并也能做。

---

核心代码

```C++

namespace SGT{
	void pushup(int v){
		tr[v].sum=tr[tr[v].l].sum+tr[tr[v].r].sum;
	}
	void build(int x,int l,int r,int &v){
		if(!v)v=++idx;
		if(l==r){tr[v].sum++;return ;}
		int mid=l+r>>1;
		if(mid>=x)build(x,l,mid,tr[v].l);
		else build(x,mid+1,r,tr[v].r);
		pushup(v);
	}
	void merge(int x,int l,int r,int &v){
		if(!x){b[tmp][0]+=(ll)tr[v].sum*res;return ;}
		if(!v){res+=tr[x].sum;v=x;return ;}
		if(l==r){
			b[tmp][0]+=(ll)tr[v].sum*res;
			res+=tr[x].sum;
			
			b[tmp][1]-=(ll)tr[v].sum*tr[x].sum;
			tr[v].sum+=tr[x].sum;
			return ;
		}
		int mid=l+r>>1;

		merge(tr[x].l,l,mid,tr[v].l);
		merge(tr[x].r,mid+1,r,tr[v].r);

		pushup(v);
	}
}

using namespace SGT;

void dfs(int u){
	if(t[u]==n){
		build(rd,1,INF,rt[u]);
		return ;
	}
	for(int v=u<<1;v<=(u<<1|1);v++){
		t[v]=t[u]+1,dfs(v);
		if(v&1){
			tmp=n-t[u];
			res=0;
			merge(rt[v],1,INF,rt[u]);
		}
		else rt[u]=rt[v];
	}
}
```




---

## 作者：nullqtr_pwp (赞：0)

好套路啊。

长度为 $2^n$，每个截取的长度是 $2^x$，可以考虑分治树，也就是 $[l,r]$ 分治成 $[l,mid]$ 和 $[mid+1,r]$ 的线段。分治计算跨中点的逆序对数量。我们设每个线段 $[l,r]$ 的顺序对数量为 $a_{l,r}$，逆序对数量为 $b_{l,r}$。那么答案显然就是 $\sum_{[l,r]\in S}b_{l,r}$。其中 $S$ 是分治树上所有线段的集合。由于修改是这棵分治树上整体一层的修改，可以考虑 $c_{i,0/1}$ 表示第 $i$ 层上所有线段的顺序对与逆序对数量。

现在我们考虑修改，反转长度 $2^x$ 的只会造成这棵树倒数前 $x$ 层的所有线段交换 $a_{l,r}$ 与 $b_{l,r}$，而且一层是一起动的。这样可以直接 $O(n)$ 的修改与查询。

```cpp
int a[maxn],b[maxn];
ll cnt[22][2];
void solve(int l,int r,int x){
	if(l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid,x-1);
	solve(mid+1,r,x-1);
	int i=l,j=mid+1,p=0;
	while(i<=mid&&j<=r) (a[i]<a[j])?cnt[x][1]+=r-j+1,i++:j++;
	i=l,j=mid+1;
	while(i<=mid&&j<=r) (a[i]>a[j])?cnt[x][0]+=mid-i+1,b[p++]=a[j++]:b[p++]=a[i++];
	while(i<=mid) b[p++]=a[i++];
	while(j<=r) b[p++]=a[j++];
	F(i,l,r) a[i]=b[i-l];
}
signed main(){
	int n=read(),m=1<<n;
	F(i,1,m) a[i]=read();
	solve(1,m,n);
	int lzm=read();
	wh(lzm){
		int x=read();
		ll ans=0;
		F(i,1,x) swap(cnt[i][0],cnt[i][1]),ans+=cnt[i][0];
		F(i,x+1,n) ans+=cnt[i][0];
        printf("%lld\n",ans);
	}
}
```


---

## 作者：Rain_chr (赞：0)

### 题意翻译

给出一个长度为 $2^n$ 的序列，$m$ 次操作，每次操作给出一整数 $q$，把该序列分成连续的长度均为 $2^q$ 的 $2^{n-q}$ 段后，把每段反转，并查询反转后的逆序对。

（这题markdown炸了管理修一下）

### 分析做法

这题和[P3521](https://www.luogu.com.cn/problem/P3521)一样得运用一个性质：修改之后，块与块之间的逆序对个数不变，变的只能是块内的个数。

#### 证明
因为块与块的相对位置不变，所以逆序对个数不变，块内反之亦然。

有了这个性质，我们将每个块想成树上的一段区间（和P3521一样），然后就可以用线段树合并轻松解决了。

### 温馨提示

根节点数量不是 $2^{20}$，而是 $2^{21}$，因为你将区间也当成了点。

### 代码

```cpp
#include<bits/stdc++.h>
#define lt(i) tree[i].lt
#define rt(i) tree[i].rt
#define val(i) tree[i].val
using namespace std;
inline int read()
{
	char x=getchar();
	int ans=0,f=1;
	while(x>'9'||x<'0') 
	{
		if(x=='-')
			f=-f;
		x=getchar();
	}
	while(x>='0'&&x<='9') 
	{
		ans=(ans<<3)+(ans<<1)+(x^48);
		x=getchar();
	}
	return ans*f;
}
int a[(1<<20)+10];
int *sort_;
long long s[30],t[30]; 
struct Seg_Tree
{
	struct node
	{
		int lt,rt;
		long long val;
	}tree[(1<<20)*30];
	int root[(1<<20)*3],cnt;	
	void pushup(int x)
	{
		val(x)=val(lt(x))+val(rt(x));
	}
	int merge(int a,int b,int l,int r)
	{
		if(!a||!b)
			return a+b;
		if(l==r)
			val(a)+=val(b);
		else
		{
			int mid=(l+r)>>1;
			lt(a)=merge(lt(a),lt(b),l,mid);
			rt(a)=merge(rt(a),rt(b),mid+1,r);
			pushup(a);
		}
		return a;
	}
	void updata(int &x,int l,int r,int pos,int v)
	{
		if(!x)
			x=++cnt;
		if(l==r)
			val(x)+=v;
		else
		{
			int mid=(l+r)>>1;
			if(pos<=mid)
				updata(lt(x),l,mid,pos,v);
			else
				updata(rt(x),mid+1,r,pos,v);
			pushup(x);
		}
	}
	long long work(int a,int b,int l,int r)
	{
		if(l==r||!a||!b)
			return 0;
		else
		{
			int mid=(l+r)>>1;
			long long k=0;
			k+=work(lt(a),lt(b),l,mid);
			k+=work(rt(a),rt(b),mid+1,r);
			k+=val(rt(a))*val(lt(b));	
			return k;
		}
	}
}T;
int cnt=0,n;
void work(int x,int l,int r,int len)
{
	if(l==r)
		T.updata(T.root[x],1,1<<n,a[l],1);
	else
	{
		int mid=(l+r)>>1,left,right;
		work(left=++cnt,l,mid,len-1);
		work(right=++cnt,mid+1,r,len-1);
		s[len]+=T.work(T.root[left],T.root[right],1,1<<n);
		t[len]+=T.work(T.root[right],T.root[left],1,1<<n);
		T.root[x]=T.merge(T.root[x],T.root[left],1,1<<n);
		T.root[x]=T.merge(T.root[x],T.root[right],1,1<<n);
	}
}
signed main()
{
	n=read();
	sort_=new int[(1<<n)+10];
	for(int i=1;i<=(1<<n);i++)
		sort_[i]=a[i]=read();
	sort(sort_+1,sort_+1+(1<<n));
	for(int i=1;i<=(1<<n);i++)
		a[i]=lower_bound(sort_+1,sort_+1+(1<<n),a[i])-sort_;
	delete[] sort_;
	work(++cnt,1,1<<n,n);
	int q=read();
	while(q--)
	{
		int x=read();
		for(int i=0;i<=x;i++)
			swap(s[i],t[i]);
		long long ans=0;
		for(int i=0;i<=n;i++)
			ans+=s[i];
		printf("%lld\n",ans); 
	}
	return 0;
}
//恭喜，你又AC了一道紫题
```



---

## 作者：541forever (赞：0)

考虑对每个长度为 $2^x$ 的段内部产生的贡献单独计算，长度为 $2^x$ 段的贡献定义为它的左右两个长度为 $2^{x - 1}$ 的子区间产生的贡献，因此反转操作能影响的贡献的范围就只有长度为 $2^1, 2^2, 2^3 \ldots 2^q$ 的段。同时，我们可以发现反转操作的影响是使原序列的顺序对变为逆序对，逆序对变为顺序对，因此只要预处理出各个段的逆序对和顺序对，并记录被反转次数的奇偶性即可，只需归并排序即可实现。

代码十分简短。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch;
	do{
		ch=getchar();
		if(ch=='-'){
			f=-1;
		}
	}while(!(ch>='0'&&ch<='9'));
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return f*x;
}
int n,len,q,a[(1ll<<20)+5],f[2][25],op[25];
void prep(int l,int r,int dep){
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	prep(l,mid,dep-1);
	prep(mid+1,r,dep-1);
	int i=l,j=mid+1;
	while(i<=mid){
		while(j<=r&&a[j]<a[i]){
			f[0][dep]+=(mid-i+1);
			++j;
		}
		++i;
	}
	i=l,j=mid+1;
	while(j<=r){
		while(i<=mid&&a[j]>a[i]){
			f[1][dep]+=(r-j+1);
			++i;
		}
		++j;
	}
	inplace_merge(a+l,a+mid+1,a+r+1);
}//归并排序
signed main(){
    n=read();
	len=1ll<<n;
	for(int i=1;i<=len;++i){
		a[i]=read();
	}
	prep(1,len,n);
	q=read();
	while(q--){
		int x=read();
		for(int i=x;i;--i){
			op[i]^=1;
		}//翻转
		int ans=0;
		for(int i=1;i<=n;++i){
			ans+=f[op[i]][i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：FjswYuzu (赞：0)

考虑到这个序列长度的特殊性以及操作的特殊性，加上求逆序对，很容易想到归并排序。考虑将归并排序与这个操作联系上。

归并排序实质上是进行分治。想一下我们是如何求解一个序列的逆序对的。

对于当前枚举的区间，先二分处理左区间和右区间。考虑将两个区间合并起来，有两个指针 $i,j$，表示左区间处理到 $i$ 这个位置，右区间处理到 $j$ 这个位置。如果 $a_i > a_j$，说明 $a_i$ 大于右区间中含 $a_j$ 的右边的所有数。加上即可。

于是我们发现，对于当前这个区间的贡献，就是这个区间的所有分治出来的子区间加上当前分开的两个区间合并产生的逆序对。

再考虑反转操作。对于一个序列反转，就相当于对这个序列对应的节点的所有子节点的左右子树交换，按套路进行打标记。又根据题目的特殊性，如果一层中确定了一个节点有标记，那么这一层的所有结点都有标记。

考虑一下打了标记的区别是什么。对于一个节点，没有打标记的贡献就是其两个子节点合并产生的逆序对数；打了标记就相当于交换两个子树，相当于就是求两个子节点合并产生的顺序对数。这个是可以两次/一次归并排序解决的。

于是处理完每一个节点的顺序对与逆序对贡献之后，再处理一下每一层打标记和不打标记的贡献即可。

在计算答案的时候，因为操作的这一层及下面的所有层都要打一个标记，按层开数组存一下是否翻转即可。时间复杂度 $O((2^n+m)n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long LL;
ull a[(1<<20)+5],b[(1<<20)+5],c[(1<<20)+5];
LL q[1000005];
LL val1[(1<<20)+5],val2[(1<<20)+5];
#define lc(x) (x<<1)
#define rc(x) ((x<<1)|1)
#define Mm LL mid=(l+r)>>1
void mergeSort1(LL now,LL l,LL r)
{
	if(l>=r)	return ;
	Mm,i=l,j=mid+1,k=l;
	mergeSort1(lc(now),l,mid);
	mergeSort1(rc(now),mid+1,r);
	LL seq=0;
	while(i<=mid && j<=r)
	{
		if(a[i]<=a[j])	c[k++]=a[i++];
		else	seq+=mid-i+1,c[k++]=a[j++];
	}
	while(i<=mid)	c[k++]=a[i++];
	while(j<=r)	c[k++]=a[j++];
	val1[now]=seq;
	for(LL s=l;s<=r;++s)	a[s]=c[s];
}
void mergeSort2(LL now,LL l,LL r)
{
	if(l>=r)	return ;
	Mm,i=l,j=mid+1,k=l;
	mergeSort2(lc(now),l,mid);
	mergeSort2(rc(now),mid+1,r);
	LL seq=0;
	while(i<=mid && j<=r)
	{
		if(a[i]<a[j])	seq+=r-j+1,c[k++]=a[i++];
		else	c[k++]=a[j++];
	}
	while(i<=mid)	c[k++]=a[i++];
	while(j<=r)	c[k++]=a[j++];
	val2[now]=seq;
	for(LL s=l;s<=r;++s)	a[s]=c[s];
}
LL n,m,threshold,flr1[25],flr2[25];
bool rev[25];
ull getAns(LL mdf)
{
	mdf=n+1-mdf;
	ull ans=0;
	for(LL i=1;i<=n;++i)
	{
		if(mdf<=i)	rev[i]^=1;
		if(rev[i])	ans+=flr2[i];
		else	ans+=flr1[i];
	}
	return ans;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=(1<<n);++i)	scanf("%lld",&a[i]);
	memcpy(b,a,sizeof b);
	mergeSort1(1,1,(1<<n));
	memcpy(a,b,sizeof b);
	mergeSort2(1,1,(1<<n));
	for(LL i=0;i<n;++i)
	{
		for(LL j=(1<<i);j<=(1<<(i+1))-1;++j)
		{
			flr1[i+1]+=val1[j];
			flr2[i+1]+=val2[j];
		}
	}
	scanf("%lld",&m);
	for(LL i=1;i<=m;++i)
	{
		int p;
		scanf("%d",&p);
		printf("%llu\n",getAns(p));
	}
	return 0;
}
```

---

