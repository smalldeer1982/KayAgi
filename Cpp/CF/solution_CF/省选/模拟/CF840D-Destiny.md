# Destiny

## 题目描述

Once, Leha found in the left pocket an array consisting of $ n $ integers, and in the right pocket $ q $ queries of the form $ l $ $ r $ $ k $ . If there are queries, then they must be answered. Answer for the query is minimal $ x $ such that $ x $ occurs in the interval $ l $ $ r $ strictly more than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF840D/c2e8ec3f500434412245cc8e8d90787dc635e07f.png) times or $ -1 $ if there is no such number. Help Leha with such a difficult task.

## 样例 #1

### 输入

```
4 2
1 1 2 2
1 3 2
1 4 2
```

### 输出

```
1
-1
```

## 样例 #2

### 输入

```
5 3
1 2 1 3 2
2 5 3
1 2 3
5 5 2
```

### 输出

```
2
1
2
```

# 题解

## 作者：Zimse (赞：25)



#### 介绍一种不用主席树的做法

### 类似于根号分治




发现k很小 所以 $\frac{r-l+1}{k}$ 会比较大

于是乎 对 $(r-l+1)$ 的大小进行分治



------------


###  $(r-l+1)\le\sqrt{2.5n}$

这时候暴力扫一遍

------------

###  $(r-l+1)>\sqrt{2.5n}$

此时可能满足出现次数大于 $\frac{r-l+1}{k}$ 次的数最少出现  $\frac{\sqrt{2.5n}}{5}$ 次

这种数最多存在 $2.5\sqrt{n}$ 个

维护每个值在整个序列中的出现次数 再用vector存出现位置 从大到小排序

对于询问从出现次数多的开始考虑

一但在整个序列的出现次数都小于 $\frac{r-l+1}{k}$ 那么就不存在

最多考虑 $2.5\sqrt{n}$ 个数

对于每个数 二分算出他在询问区间的出现次数

$O(2.5\sqrt{n}logn)$

实际上跑的最慢的点不超过 $2$ 秒 大多数 $(r-l+1)$ 都比较大  $\frac{r-l+1}{k}$ 就比较大 需要考虑的数很少

------------


```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int read(){
	int __x=0,__y=1;char __c=' ';
	while(__c<'0'||__c>'9'){__c=getchar();if(__c=='-'){__y=-1,__c=getchar();break;}}
	while(__c>='0'&&__c<='9')__x=__x*10+__c-'0',__c=getchar();
	return __x*__y;}

const int N=3e5+7,INF=1e9+7;
int n,q,a[N],t[N],l,r,k,len,ans;

struct Val{
	int cnt,num;
	vector<int> v;
	bool operator <(const Val& A)const{return cnt>A.cnt;}
}s[N];

int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read(),s[a[i]].v.push_back(i),++s[a[i]].cnt,s[a[i]].num=a[i];
	sort(s+1,s+n+1);
	
	while(q--){
		l=read(),r=read(),k=read(),ans=-1,len=r-l+1;
		
		if(len<=1500){
			for(int i=l;i<=r;i++)++t[a[i]];
			for(int i=l;i<=r;i++){
				if(t[a[i]]*k>len)if(ans==-1||a[i]<ans)ans=a[i];
				t[a[i]]=0;
			}
			printf("%d\n",ans);
			continue;
		}
		
		for(int i=1;i<=n&&s[i].cnt*k>len;i++){
			int _L=-1,_R=-1;
			
			int L=0,R=s[i].cnt-1;
			while(L<=R){
				int M=(L+R)/2;
				if(l<=s[i].v[M])_L=M,R=M-1;
				else L=M+1;
			}
			
			L=0,R=s[i].cnt-1;
			while(L<=R){
				int M=(L+R)/2;
				if(r>=s[i].v[M])_R=M,L=M+1;
				else R=M-1;
			}
			
			if(_L!=-1&&_R!=-1&&(_R-_L+1)*k>len)if(ans==-1||s[i].num<ans)ans=s[i].num;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Alex_Wei (赞：21)

> [题目传送门](https://www.luogu.com.cn/problem/CF840D)。

> 题意简述：多次询问求出一个区间最小的出现次数严格大于 $\frac{r-l+1}{k}\ (2\leq k\leq 5)$ 的最小的数。无解输出 $-1$。

> [在我的 cnblogs 中查看](https://www.cnblogs.com/alex-wei/p/CF840D.html)。

---

注意到这个 $k$ 很小，那么就要让正解尽量往上靠：设 $d$ 为严格大于 $\frac{r-l+1}{k}$ 的最小数。如果一个数 $x$ 出现了 $d$ 次，那么我们从小到大每隔 $d-1$ 个数取出一个数（即取出第 $1,1+d,1+2d,\cdots$ 小的数 ），$x$ 必定出现在所有取出的数中。这个结论是显然的，因为如果 $x$ 没有出现，那么 $x$ 在整个区间的出现次数最多为 $d-1$。

这样就将题目转化为了区间 kth + 区间出现次数的主席树裸题。时间复杂度 $\mathcal{O}(kn\log n)$。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

const int N=3e5+5;

int n,m,node,rt[N],val[N<<5],ls[N<<5],rs[N<<5];
void upd(int x){
	val[x]=val[ls[x]]+val[rs[x]];
}
void ins(int l,int r,int p,int &x,int pre){
	val[x=++node]=val[pre];
	if(l==r)return val[x]++,void();
	int m=l+r>>1;
	if(p<=m)ins(l,m,p,ls[x],ls[pre]),rs[x]=rs[pre];
	else ins(m+1,r,p,rs[x],rs[pre]),ls[x]=ls[pre];
	upd(x);
}
int query(int l,int r,int k,int x,int y){
	if(l==r)return l;
	int m=l+r>>1,sz=val[ls[y]]-val[ls[x]];
	if(sz<k)return query(m+1,r,k-sz,rs[x],rs[y]);
	return query(l,m,k,ls[x],ls[y]);
}
int check(int l,int r,int p,int x,int y){
	if(l==r)return val[y]-val[x];
	int m=l+r>>1;
	if(p<=m)return check(l,m,p,ls[x],ls[y]);
	return check(m+1,r,p,rs[x],rs[y]);
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)ins(1,n,read(),rt[i],rt[i-1]);
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),k=read();
		int rk=1,ans=-1,nd=(r-l+1)/k+1;
		while(rk<=r-l+1){
			int q=query(1,n,rk,rt[l-1],rt[r]);
			if(check(1,n,q,rt[l-1],rt[r])>=nd){
				ans=q;
				break;
			} rk+=nd;
		} printf("%d\n",ans);
	}
	return 0;
}

---

## 作者：MY（一名蒟蒻） (赞：13)

[CF840D Destiny](https://www.luogu.com.cn/problem/CF840D)

[P3567 [POI2014]KUR-Couriers](https://www.luogu.com.cn/problem/P3567)的加强版。

看到这题我第一反应是莫队来着。

---

## 主席树

由于这题非常模板所以我来介绍一下这玩意是啥。

以下摘自本人的[题解 P6166 【[IOI2012]scrivener】](https://www.luogu.com.cn/blog/nizhuan/solution-p6166)

- [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)
- [P3834 【模板】可持久化线段树 2（主席树）](https://www.luogu.com.cn/problem/P3834)

主席树，又名函数式线段树。由于发明人黄嘉泰的名字缩写和某位中国共产党领导人是一样的，故名主席树。

实现可持久化使用复制节点的方式，由于一次修改最多修改 $\log n$ 个节点，于是需要开 $n\log n$ 的空间。

---

又叫可持久化线段树，顾名思义可持久。

这个东西可以在一个数列中挖出一段来做 $\log n$ 的操作。

本题依靠权值线段树。

## 权值线段树

就是节点维护的不是区间的信息，而是值域上的信息。

每一个节点对应的是值域上的一段区间。

所以离散化是值域线段树经典操作。

## 建树

边插入边建树，每次对树的形态产生更改时复制节点。

这里不能再使用线段树访问左右儿子的方式，要记录下每个节点的左右儿子。

插入时从内存池中取一块内存给复制的节点，每一次插入建立在上一个版本上。

## 询问

先来看弱化版的询问咋搞。

因为这题权值线段树每个数字的贡献是所在区间的个数加一，所以如果我们用 $R$ 版本的数据减去 $L-1$ 版本的数据就是这个区间的对应数据了。

那么如果左子区间有数字出现次数超过一半就递归查左子，否则右子。

**注意这里的左子区间是值域线段树上的左子区间。**

递归的时候要把区间的左右端点一起传下去，注意这里的区间指的是数列上的区间。

可能很绕啊，放一下代码吧。

## Code 弱化版

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N=5e5+10;

int n,m,a,cnt,rt[N];
struct node {int l,r,sum;} hjt[N << 5];//32倍空间
inline int clone(int o) {hjt[++cnt]=hjt[o]; return cnt;}//复制节点

int build(int o,int l,int r,int p)//边插入边建树
{
	o=clone(o); hjt[o].sum++;//权值线段树对应区间个数++
	if(l == r) return o;
	int mid=(l+r) >> 1;
	if(p <= mid) hjt[o].l=build(hjt[o].l,l,mid,p);
	else hjt[o].r=build(hjt[o].r,mid+1,r,p);
	return o;
}

int query(int l,int r,int L,int R,int size)
{
	if(l == r) return l;
	int mid=(l+r) >> 1;//有点像差分
	if((hjt[hjt[R].l].sum-hjt[hjt[L].l].sum)<<1 > size) return query(l,mid,hjt[L].l,hjt[R].l,size);
	if((hjt[hjt[R].r].sum-hjt[hjt[L].r].sum)<<1 > size) return query(mid+1,r,hjt[L].r,hjt[R].r,size);
	return 0;
}

int main()
{
// 	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {scanf("%d",&a); rt[i]=build(rt[i-1],1,n,a);}
	int l,r;
	while(m--)
	{
		scanf("%d%d",&l,&r);
		printf("%d\n",query(1,n,rt[l-1],rt[r],r-l+1));
	}
// 	fclose(stdin); fclose(stdout);
	return 0;
}
```

## Code real

我根据这题的描述把 $query$ 函数改成了这个样子。

```cpp
int query(int l,int r,int L,int R,int size)
{
	if(l == r) return l;
	int mid=(l+r) >> 1;
	if(hjt[hjt[R].l].sum-hjt[hjt[L].l].sum > size) return query(l,mid,hjt[L].l,hjt[R].l,size);
	if(hjt[hjt[R].r].sum-hjt[hjt[L].r].sum > size) return query(mid+1,r,hjt[L].r,hjt[R].r,size);
	return -1;
}
```

[但是这个玩意WA了#6](https://www.luogu.com.cn/record/50208884)。

因为如果当前你判断左边的区间满足条件，但是答案不一定在左边。左边只是总次数满足条件，但是答案也可能在右边。

接下来直接放代码。不再注释。

```cpp
/*
主席树 P3567加强版 
边插入边建树
经典操作边递归边减 
与弱化版的区别在于没有一个性质：具有唯一解 
也就是说，当前你判断左边的区间满足条件，但是答案不一定在左边
所以如果左边无解，要考虑右边是否有解 
*/
#include <cstdio>
#include <iostream>

using namespace std;

const int N=3e5+10;

int n,m,k,cnt,rt[N];
struct node {int l,r,sum;} hjt[N << 5];
inline int clone(int o) {hjt[++cnt]=hjt[o]; return cnt;}

int build(int o,int l,int r,int p)
{
	o=clone(o); hjt[o].sum++;
	if(l == r) return o;
	int mid=(l+r) >> 1;
	if(p <= mid) hjt[o].l=build(hjt[o].l,l,mid,p);
	else hjt[o].r=build(hjt[o].r,mid+1,r,p);
	return o; 
}

int query(int l,int r,int L,int R,int size)
{
	if(l == r) return l;
	int mid=(l+r) >> 1,res;
	if((hjt[hjt[R].l].sum-hjt[hjt[L].l].sum)*k > size)
	{
		res=query(l,mid,hjt[L].l,hjt[R].l,size);
		if(~res) return res;
	} 
	if((hjt[hjt[R].r].sum-hjt[hjt[L].r].sum)*k > size) return query(mid+1,r,hjt[L].r,hjt[R].r,size);
	return -1;
}

int main()
{
//	freopen("work.in","r",stdin); freopen("work.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++) {scanf("%d",&x); rt[i]=build(rt[i-1],1,n,x);}
	int l,r;
	while(m--)
	{
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",query(1,n,rt[l-1],rt[r],r-l+1));
	}
//	fclose(stdin); fclose(stdout);
	return 0;
}
```

希望对您学OI有帮助！

## $Thank\ you\ for\ your\ reading!$

---

## 作者：皎月半洒花 (赞：12)

比较推荐的一道主席树入门题。

我们思考主席树的本质，其实就是可以刨出一个区间$l,r$让我们可以在树高复杂度$log$的基础上进行一波常规线段树不能进行的、权值查找操作。那么由于主席树本质上是一棵权值线段树，所以直接$return$的$val$一定是最小的（只要我们保证先查找左子树）。

然后…然后就没有然后了qwq

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define il inline
#define MAXN 500510
#define mid ((l + r) >> 1)

using namespace std ;
int a, b, c ;
int pos, N, base[MAXN], aft[MAXN], M, i ;
int cnt, Len, T[MAXN << 5], L[MAXN << 5], R[MAXN << 5], sum[MAXN << 5] ;

il int qr(){
    int k = 0, f = 1; 
    char c = getchar() ;
    while(!isdigit(c)){
        if (c == '-') f = -1 ;
        c = getchar() ;
    }
    while(isdigit(c)){
        k = (k << 1) + (k << 3) + c - 48 ;
        c = getchar() ;
    } 
    return k * f;
}
il int build(int l, int r){
    int rt = ++ cnt ;
    sum[rt] = 0 ;
    if(l < r){
        L[rt] = build(l, mid) ;
        R[rt] = build(mid + 1, r) ;
    }
    return rt;
}
il int update(int last, int l, int r, int x){
    int rt = ++ cnt ;
    sum[rt] = sum[last] + 1 ;
    R[rt] = R[last] ;
    L[rt] = L[last] ;
    if (l < r){
        if (x <= mid) L[rt] = update(L[last], l, mid, x) ;
        else  R[rt] = update(R[last], mid + 1, r, x) ;
    }
    return rt ;
}
il int query(int Left, int Right, int l, int r, int k){
    if (l == r) return aft[l] ; int qwq ;
    // if (sum[Right] - sum[Left] <= k) return -1 ;
    int x = sum[L[Right]] - sum[L[Left]], y = sum[R[Right]] - sum[R[Left]] ;
    if (x > k) 
        if ((qwq = query(L[Left], L[Right], l, mid, k)) > 0) return qwq ;
    if (y > k) 
        if ((qwq = query(R[Left], R[Right], mid + 1, r, k)) > 0) return qwq ;
    return -1 ;
}
int main(){
    cin >> N >> M;
    for(i = 1; i <= N; i ++){
        base[i] = qr() ;
        aft[i] = base[i] ;
    }
    sort(aft + 1, aft + N + 1) ;
    Len = unique(aft + 1, aft + N + 1) - (aft + 1) ; 
    T[0] = build(1, Len) ;
    for(i = 1; i <= N; i ++){
        pos = lower_bound(aft + 1, aft + Len + 1, base[i]) - aft;
        T[i] = update(T[i - 1], 1, Len, pos) ;
    }
    for(i = 1; i <= M; i ++){
        scanf("%d%d%d", &a, &b, &c) ; int k = (b - a + 1) / c ;
        cout << query(T[a - 1], T[b], 1, Len, k) << endl ; 
    }
    return 0 ; 
}
```

---

## 作者：离散小波变换° (赞：8)

提供一个极其简单并且正确性高的随机化做法。

## 题解

注意到 $k\le 5$，于是如果答案存在，那么它占 $[l, r]$ 的比例一定不小于 $\dfrac{1}{5}$。考虑随机检查 $[l, r]$ 区间里的 $h$ 个数字，再检查它的出现次数是否大于 $\dfrac{r-l+1}{k}$。这 $h$ 次检查里，检查到答案的概率为 $1-\left(\dfrac{k-1}{k}\right)^h$。当 $h=100$ 时，出错概率约为 $10^{-10}$。

在另外一篇随机化题解里，它使用了莫队统计 $[l, r]$ 区间里每一个数字出现的次数。不过实际上，我们可以避免莫队统计元素个数的过程。因为，**我们只关心**某个数字出现次数是否大于等于某个值 $p=1+\left\lfloor\dfrac{r-l+1}{k}\right\rfloor$。

依然是将询问离线，枚举询问的右端点 $r$，接着用 $n$ 个 $\text{vector}$ 维护每个元素出现的位置。用 $E_a$ 表示元素 $a$ 出现的位置的下标 $\{E_{a}(0),E_{a}(1),\cdots,E_{a}(k)\}$。

当我们检查元素 $v$ 时，如果 $E_v$ 的大小比 $p$ 小，显然 $v$ 不合法；否则取出 $E_v$ 里倒数第 $p$ 个元素（即，倒数第 $p$ 个值为 $v$ 的元素的下标），如果其值小于 $l$，显然不合法，否则合法。

时间复杂度为 $\mathcal O(n+mh)$。下文代码取了 $h=100$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 3e5 + 3;
int A[MAXN], B[MAXN], h = 100;
vector <int> E[MAXN];
vector <int> F[MAXN];
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
mt19937 MT;
vector <tuple<int, int, int> > Q[MAXN];
int main(){
    int n = qread(), m = qread();
    up(1, n, i) A[i] = qread();
    up(1, m, i){
        int l = qread(), r = qread(), k = qread();
        Q[r].push_back(make_tuple(l, k, i));
    }
    up(1, n, i){
        F[A[i]].push_back(i);
        for(auto &q : Q[i]){
            int l = get<0>(q);
            int r = i;
            int k = get<1>(q);
            int x = get<2>(q);
            int t = (r - l + 1) / k + 1;
            int ans = INF;
            uniform_int_distribution <int> U(l, r);
            up(1, h, j){
                int p = A[U(MT)], g;
                if((g = F[p].size()) >= t && F[p][g - t] >= l){
                    if(p < ans)
                        ans = p;
                }
            }
            if(ans == INF)
                B[x] = -1;
            else
                B[x] = ans;
        }
    }
    up(1, m, i)
        printf("%d\n", B[i]);
    return 0;
}
```

---

## 作者：Fading (赞：7)

首先你要做过一道题目，$\texttt{
P3567
[POI2014]KUR-Couriers}$

那道题$K=2$，但是这道题$K\in [2,5]$。

怎么办呢？考虑那道题的做法，主席树维护$[1,x]$内值域区间有多少个数。

然后线段树上二分，首先如果左子树的和$\text{sum}_{lson}\leq \frac 12\text{sum}$，那么$\text{sum}_{rson}\geq \frac 12\text{sum}$。所以那个大往那个子树走即可。

这个题怎么办呢？我们采取**暴力**，如果$\text{su}\text{m}_{lson}\geq \frac 1K\text{su}\text{m}$，往左子树走。如果左子树没有答案（即仅仅是和$\geq\frac 1K$），那么往右子树走。

看似时间复杂度不对，实际上是$O(nK\log_2 n)$的。

下面是复杂度分析：

一次如果$\text{su}\text{m}_{lson}\geq x\frac 1K\text{su}\text{m}(x \in N^*)$，那么$\text{su}\text{m}_{rson}\leq  (K-x)\frac{1}{K}\text{su}\text{m}$。左子树最多就有$x$个答案，最多搜索$x\log_2n$次，同理右边最多搜索$(K-x)\log_2n$次。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
int n,m,cnt;
struct node{
    int l,r,sum;
}seg[20202020];
int root[1010101],a[1010101];
#define mid ((lb+rb)>>1)
void update(int &rt,int lb,int rb,int num){
    seg[++cnt]=seg[rt];rt=cnt;seg[rt].sum++;
    if (lb==rb) return;
    if (num<=mid) update(seg[rt].l,lb,mid,num);
    else update(seg[rt].r,mid+1,rb,num);
}
int query(int i,int j,int lb,int rb,int len,int K){
    if (lb==rb) return (seg[j].sum-seg[i].sum>len/K?lb:-1);
    int ans=-1;
 	if (seg[seg[j].l].sum-seg[seg[i].l].sum>len/K) ans=query(seg[i].l,seg[j].l,lb,mid,len,K);
 	if (~ans) return ans;
 	if (seg[seg[j].r].sum-seg[seg[i].r].sum>len/K) ans=query(seg[i].r,seg[j].r,mid+1,rb,len,K);
	return ans;
}	
int main(){
    n=read(),m=read();
    for (int i=1;i<=n;i++){
        a[i]=read();
    }
    for (int i=1;i<=n;i++){
        root[i]=root[i-1];
        update(root[i],1,n,a[i]);
    }
    int left,right,K;
    for (int i=1;i<=m;i++){
        scanf("%d%d%d",&left,&right,&K);
        printf("%d\n",query(root[left-1],root[right],1,n,right-left+1,K));
    }
    return 0;
}
```


---

## 作者：xkcdjerry (赞：7)

看了下题解里基本都是权值线段树/随机化/根号算法，这里提供一个 $O(nk)$ 空间，$O(nk^2 \log n)$ 时间的清新易写线段树做法。

---

前置知识：[Misra–Gries 算法/扩展摩尔投票](https://www.luogu.com.cn/blog/298051/misragries-suan-fa-kuo-zhan-ma-er-tou-piao)

该算法能够给出一个包含 $k-1$ 个元素的**可合并** summary，且保证原数组中出现频率严格大于 $\dfrac1k$ 的一定在该 summary 内。  

---

由于 summary 有可加性但是没有可减性，所以采用线段树来维护区间询问。

由于只是保证了原数组中 $\text{k-heavy}$ 的数一定在 summary 中，没有保证 summary 中所有数都是 $\text{k-heavy}$ 的，所以还需要遍历一遍 summary 检查是否真的出现 $>\dfrac{n}k$ 次。  
由于一共只需要查询 $O(kq)$ 次，所以可以建立 $n$ 个 `vector` 存贮每个值的出现位置，通过两次二分计算出区间内指定值的出现次数即可。  

时间复杂度：  
预处理：初始化线段树 $O(nk^2)$，初始化 `vector` $O(n)$。  
询问：线段树查询 $O(k^2 \log n)$，`vector` 二分 $O(k \log n)$。

总复杂度 $O(nk^2+qk^2 \log n)$，$n,q$ 同阶的情况下等于 $O(nk^2 \log n)$。


代码：~~你看这多好写的我都不知道该怎么错~~
```c++
#include <cstdio>
#include <vector>
#include <algorithm>
#define N 300010
#define inf 0x3f3f3f3f
int n,a[N];
namespace Moore
{
    // k<=5 所以 summary 里最多只需要保存 4 个数，赛场上不放心可以多开点
    #define K 4
    struct summary
    {
        int val[K],cnt[K];
        void ins(int x,int v)
        {
            for(int i=0;i<K;i++) if(val[i]==x) {cnt[i]=cnt[i]<0?v:cnt[i]+v; return;}
            for(int i=0;i<K;i++) if(cnt[i]<=0) {val[i]=x; cnt[i]=v; return;}
            int mn=v;
            for(int i=0;i<K;i++) if(cnt[i]<mn) mn=cnt[i];
            v-=mn; for(int i=0;i<K;i++) cnt[i]-=mn;
            if(v) for(int i=0;i<K;i++) if(cnt[i]<=0) {val[i]=x; cnt[i]=v; return;}
        }
        summary operator+(summary b)
        {
            summary ans=*this;
            for(int i=0;i<K;i++) if(b.cnt[i]>0)
                ans.ins(b.val[i],b.cnt[i]);
            return ans;
        }
    };
    struct seg
    {
        int l,r; summary v;
    }T[N*4];
    void init(int l,int r,int o)
    {
        T[o].l=l,T[o].r=r;
        if(l==r) {T[o].v.ins(a[l],1); return;}
        int mid=(l+r)/2;
        init(l,mid,o<<1), init(mid+1,r,o<<1|1);
        T[o].v=T[o<<1].v+T[o<<1|1].v;
    }
    summary ask(int l,int r,int o)
    {
        if(T[o].l==l&&T[o].r==r) return T[o].v;
        int mid=(T[o].l+T[o].r)/2;
        if(r<=mid) return ask(l,r,o<<1);
        else if(l>mid) return ask(l,r,o<<1|1);
        else return ask(l,mid,o<<1)+ask(mid+1,r,o<<1|1);
    }
}
namespace Counter
{
    using std::vector;
    vector<int> pos[N];
    void init() {for(int i=1;i<=n;i++) pos[a[i]].push_back(i);}
    int count(int l,int r,int x)
    {
        return std::upper_bound(pos[x].begin(),pos[x].end(),r)-std::lower_bound(pos[x].begin(),pos[x].end(),l);
    }
}
void init()
{
    Moore::init(1,n,1);
    Counter::init();
}
int ask(int l,int r,int k)
{
    Moore::summary val=Moore::ask(l,r,1);
    int ans=inf;
    for(int i=0;i<K;i++) if(val.cnt[i]>0)
    {
        if(Counter::count(l,r,val.val[i])>(r-l+1)/k&&val.val[i]<ans) ans=val.val[i];
    }
    return ans==inf?-1:ans;
}
int main()
{
    int m; scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    init(); while(m--)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",ask(l,r,k));
    }
}
```

后记：  

若把线段树换为猫树能够以空间变成 $O(nk \log n)$ 的代价将 summary 部分变为 $O(nk \log n)$ 预处理 $O(k^2)$ 查询。  
总复杂度降低至 $O(nk \log n+qk(\log n+k))$，$n,q$ 同阶的情况下等于 $O(nk^2+nk\log n)$。


---

## 作者：1saunoya (赞：7)

模板题，提供两种思路。

1.考虑它求得是 出现个数$>\lfloor \frac{r-l+1}{k}\rfloor$ 的最小值

那么我们可以根据如果大于这个数那么你把这个区间数列**排好序**然后分段，分成 $k$ 段，每次上下整都取，方便处理.webp

因为 $k\leq5$ 所以上下整都取不会超过 $10$ 个数字，依次查询，取个 $\min$ ，没了。

2.考虑主席树本身的性质，他就是个权值线段树，直接放进来查询就完事了，左边的权值一定比右边的权值小，如果左边的出现个数大于 $\lfloor \frac{r-l+1}{k} \rfloor$ 那么很显然这边是有可能的，暴力找下试试看，如果不行的话，向右找，如果可以的话，这样依次找，直到找到了，一定是最小值，如果变成最大值的话，就从右边开始取

```cpp
// powered by c++11
// by Isaunoya
#include<bits/stdc++.h>
#define rep(i , x , y) for(register int i = (x) ; i <= (y) ; ++ i)
#define Rep(i , x , y) for(register int i = (x) ; i >= (y) ; -- i)
using namespace std ;
using db = double ;
using ll = long long ;
using uint = unsigned int ;
#define int long long
using pii = pair < int , int > ;
#define ve vector
#define Tp template
#define all(v) v.begin() , v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back
#define fir first
#define sec second
// the cmin && cmax
Tp < class T > void cmax(T & x , const T & y) { if(x < y) x = y ; }
Tp < class T > void cmin(T & x , const T & y) { if(x > y) x = y ; }
// sort , unique , reverse
Tp < class T > void sort(ve < T > & v) { sort(all(v)) ; }
Tp < class T > void unique(ve < T > & v) { sort(all(v)) ; v.erase(unique(all(v)) , v.end()) ; }
Tp < class T > void reverse(ve < T > & v) { reverse(all(v)) ; }
const int SZ = 0x191981 ;
struct FILEIN {
	~ FILEIN () {} char qwq[SZ] , * S = qwq , * T = qwq , ch ;
	char GETC() { return (S == T) && (T = (S = qwq) + fread(qwq , 1 , SZ , stdin) , S == T) ? EOF : * S ++ ; }
	FILEIN & operator >> (char & c) { while(isspace(c = GETC())) ; return * this ; }
	FILEIN & operator >> (string & s) {
		while(isspace(ch = GETC())) ; s = ch ;
		while(! isspace(ch = GETC())) s += ch ; return * this ;
	}
	Tp < class T > void read(T & x) {
		bool sign = 1 ; while((ch = GETC()) < 0x30) if(ch == 0x2d) sign = 0 ;
		x = (ch ^ 0x30) ; while((ch = GETC()) > 0x2f) x = x * 0xa + (ch ^ 0x30) ;
		x = sign ? x : -x ;
	}
	FILEIN & operator >> (int & x) { return read(x) , * this ; }
	FILEIN & operator >> (signed & x) { return read(x) , * this ; }
	FILEIN & operator >> (unsigned & x) { return read(x) , * this ; }
} in ;
struct FILEOUT { const static int LIMIT = 0x114514 ;
	char quq[SZ] , ST[0x114] ; signed sz , O ;
	~ FILEOUT () { sz = O = 0 ; }
	void flush() { fwrite(quq , 1 , O , stdout) ; fflush(stdout) ; O = 0 ; }
	FILEOUT & operator << (char c) { return quq[O ++] = c , * this ; }
	FILEOUT & operator << (string str) {
		if(O > LIMIT) flush() ; for(char c : str) quq[O ++] = c ; return * this ;
	}
	Tp < class T > void write(T x) {
		if(O > LIMIT) flush() ; if(x < 0) { quq[O ++] = 0x2d ; x = -x ; }
		do { ST[++ sz] = x % 0xa ^ 0x30 ; x /= 0xa ; } while(x) ;
		while(sz) quq[O ++] = ST[sz --] ; return ;
	}
	FILEOUT & operator << (int x) { return write(x) , * this ; }
	FILEOUT & operator << (signed x) { return write(x) , * this ; }
	FILEOUT & operator << (unsigned x) { return write(x) , * this ; }
} out ;

int n , q ;
const int maxn = 3e5 + 10 ;
int a[maxn] , rt[maxn] ;
int ls[maxn << 5] , rs[maxn << 5] , val[maxn << 5] ;
int cnt = 0 ;
void upd(int & p , int pre , int l , int r , int x) {
	p = ++ cnt ;
	val[p] = val[pre] + 1 ;
	ls[p] = ls[pre] , rs[p] = rs[pre] ;
	if(l == r) return ; 
	int mid = l + r >> 1 ;
	if(x <= mid) 
		upd(ls[p] , ls[pre] , l , mid , x) ;
	else 
		upd(rs[p] , rs[pre] , mid + 1 , r , x) ;
}
//int kth(int a , int b , int l , int r , int k) {
//	if(l == r) return l ;
//	int x = val[ls[b]] - val[ls[a]] ;
//	if(x <= k)
//		return kth(ls[a] , ls[b] , l , mid , k) ;
//	else 
//		return kth(rs[a] , rs[b] , mid + 1 , r , k - x) ;
//}
//int count(int a , int b , int l , int r , int x) {
//	if(l == r)
//		return val[b] - val[a] ;
//	int mid = l + r >> 1 ;
//	if(x <= mid) 
//		return count(ls[a] , ls[b] , l , mid , x) ;
//	else 
//		return count(rs[a] , rs[b] , mid + 1 , r , x) ;
//}

int qry(int a , int b , int l , int r , int k) {
	if(l == r) return l ;
	int x = val[ls[b]] - val[ls[a]] ;
	int y = val[rs[b]] - val[rs[a]] ;
	int mid = l + r >> 1 , ans = -1 ;
	if(x > k) {
		ans = qry(ls[a] , ls[b] , l , mid , k) ;
	}
	if(~ ans) return ans ;
	if(y > k) {
		ans = qry(rs[a] , rs[b] , mid + 1 , r , k) ;
	}
	return ans ;
}
signed main() {
#ifdef _WIN64
	freopen("testdata.in" , "r" , stdin) ;
#else
	ios_base :: sync_with_stdio(false) ;
	cin.tie(nullptr) , cout.tie(nullptr) ;
#endif
// code begin.
	in >> n >> q ;
	rep(i , 1 , n) {
		in >> a[i] ;
	}
	rep(i , 1 , n) {
		upd(rt[i] , rt[i - 1] , 1 , n , a[i]) ;
	}
	while(q --) {
		int l , r , k ;
		in >> l >> r >> k ;
		k = (r - l + 1) / k ;
		out << qry(rt[-- l] , rt[r] , 1 , n , k) << '\n' ;
	}
	return out.flush() , 0 ;
// code end.
}
```

---

## 作者：CQ_Bob (赞：4)

## 分析

为什么要随机化。

考虑莫队。

对于询问 $i$ 的一个可行数 $x$，其条件为：$cnt_x > \frac{r_i-l_i+1}{k_i}$。我们可以求出来第一个比 $\frac{r_i-l_i+1}{k_i}$ 大的**整数** $s$，就有 $cnt_x \ge s$。

然后就是一个蓝题。求区间出现次数不小于 $s$ 的最小整数。记录 $Cnt_x$ 表示 $x$ 在区间中的出现次数，$cnt_x$ 表示出现次数为 $x$ 的最小整数。如果用回滚莫队，$Cnt_x$ 大小为不减的，所以在每次 $Cnt_x$ 增加 $1$ 之后都更新一下 $cnt_{Cnt_x}$ 就能保证 $x$ 这个数在 $cnt_1 \sim cnt_{Cnt_x}$ 都有更新。第 $i$ 个询问的答案很显然就是 $cnt_{s_i}$。

复杂度 $O(n \sqrt{n})$，不用随机化。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define il inline
#define pii pair<int,int>
#define x first
#define y second
#define gc getchar()
#define rd read()
#define debug() puts("------------")

namespace yzqwq{
	il int read(){
		int x=0,f=1;char ch=gc;
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
		while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
		return x*f;
	}
	il int qmi(int a,int b,int p){
		int ans=1;
		while(b){
			if(b&1) ans=ans*a%p;
			a=a*a%p,b>>=1;
		}
		return ans;
	}
	il auto max(auto a,auto b){return (a>b?a:b);}
	il auto min(auto a,auto b){return (a<b?a:b);}
	il int gcd(int a,int b){
		if(!b) return a;
		return gcd(b,a%b);
	}
	il int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	il void exgcd(int a,int b,int &x,int &y){
		if(!b) return x=1,y=0,void(0);
		exgcd(b,a%b,x,y);
		int t=x;
		x=y,y=t-a/b*x;
		return ;
	}
	mt19937 rnd(time(0));
}
using namespace yzqwq;

const int N=1e6+10,inf=1e8;
int n,m,a[N];
int len,ans[N];
struct node{
	int l,r,k,id;
	il bool operator <(const node &b)const{
		if((l-1)/len!=(b.l-1)/len) return l<b.l;
		return r<b.r;
	}
}q[N];
int cnt1[N],cnt2[N];//大于等于i的最小数
int Cnt1[N],Cnt2[N];//数的出现次数
int del1[N],vis1[N],del2[N],vis2[N],idx1,idx2;

il int get(int x){
	return (x-1)/len+1;
}

il void solve(){
	n=rd,m=rd,len=sqrt(n);
	for(re int i=1;i<=n;++i) a[i]=rd;
	for(re int i=1;i<=m;++i){
		int l=rd,r=rd,s=rd,k;
		k=(r-l+1-1)/s+1;
		if(k==(double)((r-l+1)*1.0/s)) ++k;
		q[i]={l,r,k,i};
	}
	int l=1,r=0,lbk=0;
	sort(q+1,q+m+1);
	for(re int i=0;i<N;++i) ans[i]=inf,cnt1[i]=cnt2[i]=inf,Cnt1[i]=Cnt2[i]=0,vis1[i]=vis2[i]=0;
	idx1=idx2=0;
	for(re int i=1;i<=m;++i){
		int bl=get(q[i].l),br=get(q[i].r);
		if(bl==br){
			for(re int j=q[i].l;j<=q[i].r;++j)
				++Cnt2[a[j]],cnt2[Cnt2[a[j]]]=cnt2[Cnt2[a[j]]]>a[j]?a[j]:cnt2[Cnt2[a[j]]];
			ans[q[i].id]=cnt2[q[i].k];
			for(re int j=q[i].l;j<=q[i].r;++j)
				cnt2[Cnt2[a[j]]]=inf,--Cnt2[a[j]];
			continue;			
		}
		if(bl!=lbk){
			for(re int j=1;j<=idx1;++j) vis1[del1[j]]=0,cnt1[del1[j]]=inf;
			for(re int j=1;j<=idx2;++j) vis2[del2[j]]=0,Cnt1[del2[j]]=0;
			idx1=idx2=0;
			l=min(n,bl*len)+1,r=min(n,bl*len);
			lbk=bl;
		}
		while(r<q[i].r){
			++r;
			++Cnt1[a[r]];
			if(!vis1[Cnt1[a[r]]]) vis1[Cnt1[a[r]]]=1,del1[++idx1]=Cnt1[a[r]];
			if(!vis2[a[r]]) vis2[a[r]]=1,del2[++idx2]=a[r];
			cnt1[Cnt1[a[r]]]=cnt1[Cnt1[a[r]]]>a[r]?a[r]:cnt1[Cnt1[a[r]]];
		}
		int l_=l;
		while(l_>q[i].l){
			--l_;
			++Cnt2[a[l_]];
			cnt2[Cnt1[a[l_]]+Cnt2[a[l_]]]=cnt2[Cnt1[a[l_]]+Cnt2[a[l_]]]>a[l_]?a[l_]:cnt2[Cnt1[a[l_]]+Cnt2[a[l_]]];
		}
		ans[q[i].id]=min(cnt1[q[i].k],cnt2[q[i].k]);
		while(l_<l){
			cnt2[Cnt1[a[l_]]+Cnt2[a[l_]]]=inf;
			--Cnt2[a[l_]],++l_;		
		}
	}
	for(re int i=1;i<=m;++i)
		if(ans[i]<inf) printf("%d\n",ans[i]);
		else printf("-1\n");
	return ;
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t=1;while(t--)
	solve();
	return 0;
}
```

---

## 作者：hater (赞：4)

Is au noya 已经把两种思路都说了 

这里具体补充一下第一种解法 

k 很小 , 从 k 下手考虑

首先 如果 k=2 的话 这个答案一定是区间的众数 

那我们猜想一下 k=3 4 5 是否也可以以此类推 

假如 k=3 的话 我们可能要求区间次小众数 

本身区间众数就不是什么好弄的玩意 次小更行不通 

所以我们换个思路 

我们先把区间排序 

以 $(r-l+1)/k$ 为单位长度 

把区间划分为 k 个单位长度 

可以发现 如果一个数的出现次数符合题目要求 

这个数**必然**会在 单位分割线 处 出现1次 

（ 如果不符合要求也可能会出现 ） 

这是很显然的 不理解自行理解 （可手玩样例） 

~~不要再问 再问自杀~~ ~~窝也8会说~~ 

之后我们暴力枚举 单位分割线 旁的数 （显然很少） 

再判断一波是否出现次数 $ > (r-l+1)/k$  就OK了

code : 

```cpp
#include<bits/stdc++.h> 
#define Rg register 
#define N 300005 
#define IL inline 
using namespace std ; 
int a[N] , b[N] , n , q  , cnt , rot[N] , lis[105] , tot ; ; 
struct node { int L , R , siz ; } A[N<<5] ;  
IL int build( Rg int l , Rg int r ) { 
   int rt = ++cnt , mid = l+r >> 1 ; A[rt].siz = 0 ; 
   if( l == r ) { return rt ; }  
   A[rt].L = build( l , mid ) ; 
   A[rt].R = build( mid+1 , r ) ; 
   return rt ;  
}
IL int Ins( Rg int p , Rg int l ,Rg int r , Rg int whe ) { 
   int rt = ++cnt , mid = l+r >> 1 ; 
   A[rt] = A[p] ; A[rt].siz ++ ; 
   if( l == r ) return rt ; 
   if( whe <= mid ) A[rt].L = Ins( A[p].L , l , mid , whe ) ;  
     else A[rt].R = Ins( A[p].R , mid+1 , r , whe ) ; 
   return rt ; 
} 
IL int query( int p , int q , int l , int r , int k ) { 
    if( l == r ) return l ; 
    int mid = l+r >> 1 , mis = A[A[q].L].siz - A[A[p].L].siz ; 
    if( mis < k ) return query( A[p].R , A[q].R , mid+1 , r , k-mis ) ; 
	  else return query( A[p].L , A[q].L , l , mid , k ) ;  
} 
IL int hac( int p , int q , int l , int r , int whe ) { 
    if( l == r ) return A[q].siz - A[p].siz ; 
    int mid = l+r >> 1 ; 
    if( whe <= mid ) return hac( A[p].L , A[q].L , l , mid , whe ) ; 
      else return hac( A[p].R , A[q].R , mid+1 , r , whe ) ; 
}
signed main( ) { 
    Rg int l , r , k , tlen , block ; Rg bool flag ;  
    ios::sync_with_stdio(false) ; 
    cin.tie(0) ; cout.tie(0) ; 
    cin >> n >> q ; 
    for(Rg int i=1; i<=n; i++) cin >> a[i] ; 
	rot[0] = build( 1 , n ) ;  
	for(Rg int i=1; i<=n; i++) 
	   rot[i] = Ins( rot[i-1] , 1 , n  , a[i] ) ; 
	for(Rg int i=1; i<=q; i++) { 
		cin >> l >> r >> k ; 
		tlen = r-l+1 , block = tlen/k ; tot = 0 ; flag = 0 ; 
		lis[++tot] = query( rot[l-1] , rot[r] , 1 , n , 1 ) ; 
		if( tlen < k ) { cout << lis[1] << '\n' ; continue ; } 
		for(Rg int j=block; j<=tlen; j+=block) { 
		  lis[++tot] = query( rot[l-1] , rot[r] , 1 , n , j ) ; 
		  if( j+1 > tlen ) break ; 
		  lis[++tot] = query( rot[l-1] , rot[r] , 1 , n , j+1 ) ; 
		} 
		for(Rg int j=1; j<=tot; j++) 
		 if( j == 1 || lis[j] != lis[j-1] ) 
		  if( hac( rot[l-1] , rot[r] , 1 , n , lis[j] ) * k > tlen  ) 
		   { flag = 1 ; cout << lis[j] << '\n' ; break ;  } 
		if( !flag ) cout << "-1" << '\n' ; 
	} 
    return 0 ; 
}
```


---

## 作者：DPair (赞：3)

提供一种与概率（~~欧气~~）有关的解法，而且 $CF$ 官方给的算法标签里似乎也有“概率”。

~~跑的很慢。~~

## 【思路】
区间？出现次数？第一反应当然是莫队。

然后我们就记录了区间中每一个数的出现次数。

然而这个出现次数 **严格大于** $\lfloor \frac{r-l+1}{k}\rfloor$ 怎么搞啊？

有一种基于随机化的思路，就是随机一堆数字，看看随机出来的这些数字在区间内出现次数是否符合要求。如果随机次数达到一定的值就认为无解。

诶诶诶？你这个正确性能保证吗？

其实是可以的。

我们随机在区间内取一个数，若区间有解，这个数不是解的概率显然为 $\frac{k-1}{k}$ 。

我们注意到 $k\le 5$。

因此这个概率最大也不过只有 $\frac{4}{5}$ 。

那么，我们要是跑 $100$ 遍呢？

概率几乎为 $0$ 。

所以如果 $100$ 遍之后仍然无解，我们就可以认为它无解了。

然后交上去一看，发现 $WA$ 了，我们不至于这么非导致接近于 $0$ 的概率都让我们碰上了，于是我们意识到我们的随机数不够优秀。

~~于是我就对着随机数板子打了一遍。然后就能 A 了。~~

推荐一篇关于随机数的[日报](https://www.luogu.com.cn/blog/muxii/wu-shuo-ren-zai-xun-zhao-gui-lv-di-sui-ji-shuo)，里面有很详细的生成优秀随机数的代码。（~~我就对着这篇日报打了一遍~~）

## 【代码】
随机数使用 “梅森旋转算法”，详见上文中提到的日报。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
template <typename T>
inline T mn(T x, T y) {return x < y ? x : y;}
template <typename T>
inline T mx(T x, T y) {return x > y ? x : y;}
template <typename T>
inline void chmin(T &x, T y) {(x > y) && (x = y);}
template <typename T>
inline void chmax(T &x, T y) {(x < y) && (x = y);}

namespace My_Rand{
    int index, MT[624];
    inline void srand(int seed){
        index = 0;
        MT[0] = seed;
        for (register int i = 1;i < 624;i ++){
            int t = 1812433253 * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
            MT[i] = t & 0xffffffff;
        }
    }
    inline void rotate(){
        for (register int i = 0;i < 624;i ++){
            int tmp = (MT[i] & 0x80000000) + (MT[(i + 1) % 624] & 0x7fffffff);
            MT[i] = MT[(i + 397) % 624] ^ (tmp >> 1);
            if(tmp & 1) MT[i] ^= 2567483615;
        }
    }
    inline int rand(){
        if(!index) rotate();
        int ret = MT[index];
        ret = ret ^ (ret >> 11);
        ret = ret ^ ((ret << 7) & 2636928640);
        ret = ret ^ ((ret << 15) & 4022730752);
        ret = ret ^ (ret >> 18);
        index = (index + 1) % 624;
        return ret;
    }
} // namespace My_Rand

int n, m;
const int block = 500;
int a[300005];

inline int idb(int x){return (x / block);}

struct QUEST{
    int l, r, k;
    int id;
    inline bool operator <(const QUEST &tmp) const{
        return (idb(l) ^ idb(tmp.l)) ?(l > tmp.l) : ((idb(l) & 1)? r < tmp.r : r > tmp.r);
    }
}q[300005];

int ans, cnt[300005];
int ret[300005];

int main(){
    My_Rand :: srand(time(NULL));
    read(n);read(m);
    for (register int i = 1;i <= n;++ i) read(a[i]);
    for (register int i = 1;i <= m;++ i) {read(q[i].l);read(q[i].r);read(q[i].k);q[i].id = i;}
    sort(q + 1, q + m + 1);
    int l = q[1].l, r = l - 1;
    for (register int i = 1;i <= m;++ i){
        while(l > q[i].l) cnt[a[-- l]] ++;
        while(r < q[i].r) cnt[a[++ r]] ++;
        while(l < q[i].l) cnt[a[l ++]] --;
        while(r > q[i].r) cnt[a[r --]] --;
        int TIM = 200;
        ans = -1;
        while(TIM --){
            int x = My_Rand :: rand() % (r - l + 1) + l;
            if(cnt[a[x]] > ((r - l + 1) / q[i].k)){
                if(~ans) chmin(ans, a[x]);
                else ans = a[x];
            }
        }
        ret[q[i].id] = ans;
    }
    for (register int i = 1;i <= m;++ i) {fprint(ret[i], 10);}
    return 0;
}
```

---

## 作者：lytqwq (赞：1)

**这是一篇非正解**

本题弱化版： [$P3567$](https://www.luogu.com.cn/problem/P3567) 

那道题是询问区间出现次数大于区间大小一半的数，我们随机区间的一个数，有  $ \large \frac{1}{2}$ 的 概率是答案，我们随机上 $20$ 个数，看在区间里出现的次数是不是大于区间大小一半，每次用 $vector$ 存数的位置，在里面二分，时间复杂度 $O(20 \times qlogn)$ ，勉强卡过去 。

现在 $2\le k \le 5$ ，每次随机的数可能只有  $ \large \frac{1}{5}$ 的 概率是答案，我们再这样随机正确性爆炸，而如果增加随机的个数的话时间复杂度爆炸 ，没有强制在线，我们可以改用莫队，每次能预处理出这一个区间的每个数出现的次数，然后我们随机 $100$ 个数 $O(1)$ 看在区间里出现的次数是不是满足条件 。

时间复杂度 $O(n\sqrt{m}+100m)$

注意 在windows下，RAND_MAX的值为32767

而在linux下，RAND_MAX的值则是2147483647

CF在windows下评测，所以我用两个rand乘了起来（

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
int n,q,a[N],Csize,ans[N],ovo[N];
struct d{
	int l,r,k,ku,nam;
	bool operator < (const d &x) const{if(ku!=x.ku)return ku<x.ku;else return ku%2==0?r<x.r:r>x.r;}
}qwq[N];
void add(int x){ans[a[x]]++;}
void del(int x){ans[a[x]]--;}
int main(){
	srand(time(NULL));
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	Csize=n/sqrt(q+1)+1;
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&qwq[i].l,&qwq[i].r,&qwq[i].k);
		qwq[i].ku=qwq[i].l/Csize;qwq[i].nam=i;
	}
	sort(qwq+1,qwq+q+1);
	int L=1,R=0;
	for(int i=1;i<=q;i++){
		while(R<qwq[i].r)add(++R);
		while(L>qwq[i].l)add(--L);
		while(R>qwq[i].r)del(R--);
		while(L<qwq[i].l)del(L++);
		int ansnow=-1;
		for(int v=1;v<=100;v++){
			int kk=rand()*rand()%(R-L+1)+L;
			if(ans[a[kk]]*qwq[i].k>R-L+1){
				if(ansnow==-1||ansnow>a[kk])ansnow=a[kk];
			}
		}
		ovo[qwq[i].nam]=ansnow;
	}
	for(int i=1;i<=q;i++)printf("%d\n",ovo[i]);
	
}
```



---

## 作者：Vidoliga (赞：1)

# 题解

~~这不是主席树裸体?~~

我们直接打出主席树$QwQ$

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
const int maxn=2e6+10;
const int logg=20;
int T[maxn],L[maxn*logg],R[maxn*logg],sum[maxn*logg];
//sz[]为原序列，h[]为离散化后序列
int sz[maxn],h[maxn];
int n,m,ql,qr,k,tot=0;
inline int read(){
	register int d=0,f=1;char ch = getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		d = (d<<1)+(d<<3)+(ch^48);
		ch = getchar();
	}
	return d*f;
}
void writes(int x){
	if(x>9) writes(x/10);
	putchar(x%10+48);
}
inline void write(int &x){
	if(x<0) putchar('-'),writes(-x);
	else writes(x);
	putchar('\n');
}
void build(int &rt,int l,int r){
	rt=++tot;
	sum[rt]=0;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(L[rt],l,mid);
	build(R[rt],mid+1,r);
}
//对所有前缀更新树
void update(int &rt,int l,int r,int pre,int x){
	rt=++tot; 
	L[rt]=L[pre];R[rt]=R[pre];
	sum[rt]=sum[pre]+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) update(L[rt],l,mid,L[pre],x);
	else update(R[rt],mid+1,r,R[pre],x);
}
int query(int node1,int node2,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int ans=sum[L[node1]]-sum[L[node2]];//左子树的节点个数 
	if(k<=ans) return query(L[node1],L[node2],l,mid,k);
	else return query(R[node1],R[node2],mid+1,r,k-ans);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		sz[i]=read();
		h[i]=sz[i];
	}
	sort(h+1,h+n+1);
	int num=unique(h+1,h+n+1)-(h+1);
	build(T[0],1,num);
	for(int i=1;i<=n;i++){
		update(T[i],1,num,T[i-1],lower_bound(h+1,h+num+1,sz[i])-h);
	}
	while(m--){
		ql=read(),qr=read(),k=read();
		int ans = query(T[qr],T[ql-1],1,num,k);
		//printf("%d\n",h[ans]);
		write(h[ans]);
	}
	return 0;
}
```
打完后才发现他要求的不是第$\frac{r-l+1}{k}$个数$,$那咋办呢$???$

不急$,$我们改一下$query$函数就好了

$AC$代码$:$

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
const int maxn=5e5+600+20;
const int logg=32;
int T[maxn],L[maxn*logg],R[maxn*logg],sum[maxn*logg];
int sz[maxn],h[maxn];
int n,m,ql,qr,k,tot=0;
inline int read(){
	register int d=0,f=1;char ch = getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		d = (d<<1)+(d<<3)+(ch^48);
		ch = getchar();
	}
	return d*f;
}
void writes(int x){
	if(x>9) writes(x/10);
	putchar(x%10+48);
}
inline void write(int &x){
	if(x<0) putchar('-'),writes(-x);
	else writes(x);
	putchar('\n');
}
void build(int &rt,int l,int r){
	rt=++tot;
	sum[rt]=0;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	build(L[rt],l,mid);
	build(R[rt],mid+1,r);
}
void update(int &rt,int l,int r,int pre,int x){
	rt=++tot; 
	L[rt]=L[pre];R[rt]=R[pre];
	sum[rt]=sum[pre]+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) update(L[rt],l,mid,L[pre],x);
	else update(R[rt],mid+1,r,R[pre],x);
}
int query(int node1,int node2,int l,int r,int k){
	if(l==r)return l;
	int mid=(l+r)>>1;
	int res=maxn,temp;
	int ans1=sum[L[node1]]-sum[L[node2]],ans2=sum[R[node1]]-sum[R[node2]];
	if(ans1>k){
		temp=query(L[node1],L[node2],l,mid,k);
		if(temp!=-1) res=min(res,temp);
	} 
	if(ans2>k){
		temp=query(R[node1],R[node2],mid+1,r,k);
		if(temp!=-1) res=min(res,temp);
	}
	if(res==maxn) return -1;
	else return res;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		sz[i]=read();
	}
	int num=n;
	build(T[0],1,num);
	for(int i=1;i<=n;i++){
		update(T[i],1,num,T[i-1],sz[i]);
	}
	while(m--){
		ql=read(),qr=read(),k=read();
		int ans = query(T[qr],T[ql-1],1,num,(qr-ql+1)/k);
		write(ans);
	}
	return 0;
}//话说有没有人知道为啥我加上去重会WA呢???不去重就可以AC呢???QwQ
```

完结撒花$QwQ$

---

## 作者：do_while_true (赞：0)

[$\text{更佳的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13882042.html)

# $\mathcal{Translate}$

给定长度为 $n$ 的序列 $a_1,a_2,...,a_n$，共 $q$ 次询问，每次询问给定 $l,r,k$，询问区间 $a_l,a_{l+1},...,a_{r}$ 的最小的出现次数严格大于 $\frac{r-l+1}{k}$ 的数的值。

$1\leq n,q \leq 3\times 10^5,1\leq a_i\leq n,1\leq l\leq r\leq n,2\leq k\leq 5$

# $\mathcal{Solution}$

总思路：根号分治卡常数。

设 $M$ 为一个分界线，询问区间小于等于 $M$ 的直接暴力扫一遍找，可以使用 ```unordered_map``` 做到一次扫 $\mathcal{O}(M)$。对于大于 $M$ 的询问区间，通过记录**某些出现次数可以当做答案的数**的前缀出现次数和，遍历这些数，如果出现次数合法就更新答案。

那么那些出现次数可以当做答案的数有多少个呢？

只有区间大于等于 $M$ 的才需要查询，也就是说区间长度最少为 $M+1$ （后文当作 $M$，影响不大），而这个询问长度最少是 $M$，询问的 $k$ 为 $5$ 的时候需要的出现次数最少，需要的出现次数为 $\frac{M}{5}$，这些数最多有 $\frac{n}{\frac{M}{5}}=\frac{5n}{M}$。$q$ 次查询的复杂度为 $\mathcal{O}(q\times \max\{M,\frac{5n}{M}\})$。

考虑让里面那个 $\max$，尽可能小，画出 $y=x-\frac{5n}{x}$ 的[图表](https://www.desmos.com/calculator/yno4fkhw47)可知，$x=\pm1224.745$ 时 $y=0$，也就是 $M$ 取值为 $1225$ 最优，但是注意前缀和的空间消耗是很大的，即使选择记录下这个数在只需要记录的那些数中的排名，空间消耗也达到了 $n\times \frac{5n}{M}$ 的级别，会超出空间限制，然而调大 $M$ 过多又会超出时间限制。

减少空间使用可以考虑前缀出现次数用 ```vector``` 来存储，动态开内存，用多少开多少。$M$ 我调到 $2200$ 差不多是可以的。

计 $M_2=\frac{M}{5}$

时间复杂度 $\mathcal{O}(nM\log M_2+q\times \max(M,M_2))$

如果 $M$ 值取的比较好的话就是 $\mathcal{O}(n^{1.5}\log{\sqrt{n}+q\sqrt{n}})$

# $\mathcal{Code}$

借用了 CYJian 的快读。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<string>
#include<unordered_map>
#define ll long long
#define pb push_back
#define re register
using namespace std;
#define Min(x, y) (x < y ? x : y)
namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;
const int N = 300010;
int M = 2200, M2 = M/5 - 1;
int n, q;
int a[N], cnt[N], num;
vector<int>sum[N];
vector<int>vec;
unordered_map<int, int>vis;
int main() {
	gi(n); gi(q);
	for(re int i = 1; i <= n; ++i) {
		gi(a[i]), ++cnt[a[i]];
		if(cnt[a[i]] == M2 + 1) {
			vec.pb(a[i]);
			++num;
		}
	}
	sort(vec.begin(), vec.end());
	re int x;
	for(int j = 0; j <= num; ++j) sum[0].pb(0);
	for(re int i = 1; i <= n; ++i) {
		sum[i].pb(0);
		for(re int j = 1; j <= num; ++j) {
			sum[i].pb(0);
			sum[i][j] += sum[i-1][j];
		}
		if(cnt[a[i]] > M2) {
			x = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
			++sum[i][x];
		}
	}
	while(q--) {
		int l, r, k, sumq = -1;
		gi(l); gi(r); gi(k);
		if(r - l + 1 <= M) {
			vis.clear();
			for(re int i = l; i <= r; ++i) {
				x = ++vis[a[i]];
				if(x > (r - l + 1) / k) sumq = sumq == -1 ? a[i] : Min(sumq, a[i]);
			}
		}
		else {
			for(int i = num; i >= 1; --i)
				if(sum[r][i] - sum[l-1][i] > (r - l + 1) / k)
					sumq = sumq == -1 ? vec[i-1] : Min(sumq, vec[i-1]);
		}
		print(sumq);pc('\n');
	}
	return 0;
}
```

---

## 作者：kouylan (赞：0)

## CF840D Destiny 题解

### 【题意】
给你长$n$一个序列$a$，$1<=a_i<=n$。每一次询问在$[l,r]$内出现次数大于$(r-l+1)/k$的最小数，否则输出$-1$。

### 【分析】
一看就是到主席树题，$insert$部分一样，关键看$query$
```cpp
int query(int l,int r,int x,int y,int k)
{
	if(l==r)
		return l;
	if(dat[y].sum-dat[x].sum<=k) //不合法
		return -1;
	int res;
	if(dat[dat[y].l].sum-dat[dat[x].l].sum>k) //先搜左子树(保证答案最小)
	{
		res = query(l,mid,dat[x].l,dat[y].l,k);
		if(res>0)
			return res;
	}
	if(dat[dat[y].r].sum-dat[dat[x].r].sum>k) //再搜右子树
	{
		res = query(mid+1,r,dat[x].r,dat[y].r,k);
		if(res>0)
			return res;
	}
	return -1; //没有合法情况
}
```
下面是AC代码
```cpp
/*
luogu CF840D
*/
#include <bits/stdc++.h>
using namespace std;

#define mid (l+r>>1)

int n,q;
int root[300005],cnt;
struct hjtree{
	int l,r,sum;
}dat[300005<<5];

void insert(int &o,int l,int r,int pre,int x)
{
	o = ++cnt;
	dat[o] = dat[pre];
	dat[o].sum++;
	if(l==r)
		return;
	if(x<=mid)
		insert(dat[o].l,l,mid,dat[pre].l,x);
	else
		insert(dat[o].r,mid+1,r,dat[pre].r,x);
}

int query(int l,int r,int x,int y,int k)
{
	if(l==r)
		return l;
	if(dat[y].sum-dat[x].sum<=k)
		return -1;
	int res;
	if(dat[dat[y].l].sum-dat[dat[x].l].sum>k)
	{
		res = query(l,mid,dat[x].l,dat[y].l,k);
		if(res>0)
			return res;
	}
	if(dat[dat[y].r].sum-dat[dat[x].r].sum>k)
	{
		res = query(mid+1,r,dat[x].r,dat[y].r,k);
		if(res>0)
			return res;
	}
	return -1;
}

int main()
{
	cin>>n>>q;
	for(int i=1,x;i<=n&&cin>>x;i++)
		insert(root[i],1,n,root[i-1],x);
	while(q--)
	{
		int l,r,k;
		scanf("%d %d %d",&l,&r,&k);
		k = (r-l+1)/k;
		printf("%d\n",query(1,n,root[l-1],root[r],k));
	}
	
	return 0;
}
```
祝大家AC愉快！

---

