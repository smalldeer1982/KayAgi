# Beautiful Pair

## 题目描述

小 D 有个数列 $\{a\}$，当一个数对 $(i,j)$（$i \le j$）满足 $a_i$ 和 $a_j$ 的积不大于 $a_i, a_{i+1}, \ldots, a_j$ 中的最大值时，小 D 认为这个数对是美丽的。请你求出美丽的数对的数量。

## 说明/提示

**【样例解释 #1】**

五种可行的数对为 $(1,1), (1,2), (1,3), (1,4), (2,4)$。

**【样例解释 #2】**

只有数对 $(3,3)$ 不可行。

**【数据范围】**

对于 $100 \%$ 的数据，$1\le n\le{10}^5$，$1\le a_i\le{10}^9$。

## 样例 #1

### 输入

```
4
1 3 9 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
1 1 2 1 1
```

### 输出

```
14
```

# 题解

## 作者：FlierKing (赞：39)

我们考虑用分治的思想来解决这个问题。假设我们在计算区间$[l,r]$数对的数量，其中这个区间的最左端的最大值的位置为$mx$，那么我们可以先考虑处理$[l,mx-1]$区间数对的数量和$[mx+1,r]$区间数对的数量。

对于一个区间$[l,r]$，当我们确定了$a_l$时，只需要求$[mx+1,r]$中数字不大于$\frac {a_{mx}}{a_l}$的即是以$l$为左端点答案的对数（因为我们分区间是以最左端的最大值区分的），当确定了$a_r$时同理。此时我们可以枚举小的区间，然后确定另一边要查询的区间以及查询的值，记录下后离线查询。

可以证明，所有查询的区间数量不超过$n\ log\ n$个。考虑当进行一次长度为$len$的枚举时，那么此时被分开的区间长度必然大于$2\times len$，那么对于任意一个数字，它被枚举的次数必然不超过$log\ n$，每被枚举一次会形成一个询问区间，所以询问区间不超过$n\ log\ n$个。

考虑如果选定一个端点，那么可行的右端点的数量可以用树状数组查询。（查询 $[l,r]$ 中小于 $x$ 的数字数量可以用 $[1,r]$ 中小于 $x$ 的数字数量减去 $[1,l-1]$ 中小于 $x$ 的数字数量）

询问一个区间$[l,r]$小于等于$x$的数字数量可以用树状数组解决，用$[1,r]$中的小于等于$x$的数字数量减去$[1,l-1]$中的小于等于$x$的数字数量即为答案。

```
#include <bits/stdc++.h> 
#define ll long long
#define pr pair<int,int>
#define fi first
#define se second
#define pb push_back
#define MAXN 500005
using namespace std;
    int n,en,r,len;
    int a[MAXN],L[MAXN],R[MAXN],b[MAXN];
    pr s[MAXN];
    vector <int> g[MAXN];
    ll ans;
    ll tr[MAXN];
int inline read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline int abs(int x){return x>=0?x:-x;}
inline int find_ind(int x){return x>=b[n]?n:upper_bound(b+1,b+len+1,x)-b-1;}
inline int lowbit(int x){return x&-x;}
ll query(int x)
{
    ll res=0;
    while (x)
    {
        res+=tr[x];
        x-=lowbit(x);
    }
    return res;
}
void update(int x,int v)
{
    while (x<=n)
    {
        tr[x]+=v;
        x+=lowbit(x);
    }
}
int main()
{
    n=read();
    for (int i=1;i<=n;i++)
        b[i]=a[i]=read();
    for (int i=1;i<=n;i++)
    {
        while (en&&s[en].fi<a[i]) en--;
        L[i]=en?s[en].se+1:1;
        s[++en]=make_pair(a[i],i);
    }
    en=0;
    for (int i=n;i;i--)
    {
        while (en&&s[en].fi<=a[i]) en--;
        R[i]=en?s[en].se-1:n;
        s[++en]=make_pair(a[i],i); 
    }
    for (int i=1;i<=n;i++)
    {
        if (i-L[i]<=R[i]-i) 
        {
            g[i-1].pb(-1);
            g[R[i]].pb(1);
            for (int j=L[i];j<i;j++)
            {
                g[i-1].pb(-a[i]/a[j]);
                g[R[i]].pb(a[i]/a[j]);
            }
        }
        else
        {
            g[L[i]-1].pb(-1);
            g[i].pb(1);
            for (int j=i+1;j<=R[i];j++)
            {
                g[L[i]-1].pb(-a[i]/a[j]);
                g[i].pb(a[i]/a[j]);
            }
        }
    }
    sort(b+1,b+n+1);
    len=unique(b+1,b+n+1)-b-1;
    for (int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+len+1,a[i])-b;
    for (int i=1;i<=n;i++)
    {
        update(a[i],1);
        int to=g[i].size();
        for (int j=0;j<to;j++)
        {
            r=find_ind(abs(g[i][j]));
            g[i][j]<0?ans-=query(r):ans+=query(r);
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：nofind (赞：26)

## [题意](https://www.luogu.com.cn/problem/P4755)

考虑分治（这是套路，想不到只能说做题少~~别打我~~）。

对于当前区间$[ql,qr]$：

我们先判断区间长度是否为$1$，为$1$只需要特判当前这个数是不是$1$就可以了。  

否则我们找到区间最大值位置$mid$，这个可以用$ST$表。之后我们统计过$mid$的所有$[l,r]$，之后递归$[ql,mid-1],[mid+1,qr]$即可。

至于如何统计，我们可以枚举$mid$的一边。假设枚举的数是$a_i$，我们需要在$mid$的另一边找到一个$a_j$，满足$a_i*a_j\leqslant a_{mid}$，即$a_j\leqslant \lfloor\frac{a_{mid}}{a_i}\rfloor$。

现在问题变为统计一个区间内小于某个数的个数，我们用主席树解决即可。

但是现在有个问题，我们枚举一边再递归可以被卡成$O(n^2logn)$，这里我们运用启发式的思想，只枚举区间长度小的那边，就可以做到$O(nlog^2n)$

p.s 因为$a_i$很大，因此我们需要离散化。

code:
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
int n,num,tot;
int a[maxn],b[maxn],lg[maxn],root[maxn];
int st[maxn][20];
ll ans;
struct Seg
{
	#define lc(p) (seg[p].lc)
	#define rc(p) (seg[p].rc)
	#define sum(p) (seg[p].sum)
	int lc,rc,sum;
}seg[maxn*30];
void insert(int pre,int &p,int l,int r,int pos)
{
	p=++tot;
	seg[p]=seg[pre];sum(p)++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid)insert(lc(pre),lc(p),l,mid,pos);
	else insert(rc(pre),rc(p),mid+1,r,pos);
}
int query(int pre,int p,int l,int r,int ql,int qr)
{
	if(ql>r||qr<l)return 0;
	if(l>=ql&&r<=qr)return sum(p)-sum(pre);
	int mid=(l+r)>>1,res=0;
	if(ql<=mid)res+=query(lc(pre),lc(p),l,mid,ql,qr);
	if(qr>mid)res+=query(rc(pre),rc(p),mid+1,r,ql,qr);
	return res;
}
inline void ST()
{
	lg[0]=-1;
	for(int i=1;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)st[i][0]=i;
	for(int j=1;j<=17;j++)
		for(int i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=a[st[i][j-1]]>=a[st[i+(1<<(j-1))][j-1]]?st[i][j-1]:st[i+(1<<(j-1))][j-1];
}
inline int st_query(int l,int r)
{
	int t=lg[r-l+1];
	return a[st[l][t]]>=a[st[r-(1<<t)+1][t]]?st[l][t]:st[r-(1<<t)+1][t];
}
void solve(int ql,int qr)
{
	if(ql>qr)return;
	if(ql==qr){ans+=(b[a[ql]]==1);return;}
	int mid=st_query(ql,qr);
	if(mid-ql+1<=qr-mid)
		for(int i=ql;i<=mid;i++)
		{
			int k=upper_bound(b+1,b+num+1,b[a[mid]]/b[a[i]])-b-1;
			ans+=query(root[mid-1],root[qr],1,num,1,k);
		}
	else
		for(int i=mid;i<=qr;i++)
		{
			int k=upper_bound(b+1,b+num+1,b[a[mid]]/b[a[i]])-b-1;
			ans+=query(root[ql-1],root[mid],1,num,1,k);			
		}
	solve(ql,mid-1);solve(mid+1,qr);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);num=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+num+1,a[i])-b;
	for(int i=1;i<=n;i++)insert(root[i-1],root[i],1,num,a[i]);
	ST();
	solve(1,n);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：zzqDeco (赞：12)

突然想到写一下这个题的题解

实际上觉得有点像笛卡尔树的模型套上一个cdq分治的思想

建出一个笛卡尔树，可以发现，贡献都是$max$两边提供的，所以可以考虑像cdq分治一样考虑左右两边的影响：

1. $max$的左边的
1. $max$的右边的
1. $max$的右边的对左边的影响

最后发现这个不像cdq一样的规整（？），要考虑用小的区间来查找，保证复杂度，复杂度$O(nlog^{2}n)$

至于看到上面有人可持久化，不知道是不是降了一维的$log$

至于笛卡尔树的 $O(n)$ 建树和树状数组递归的技巧就看看代码吧

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;


int q[100010];

int ll[100010],rr[100010],top,root;

inline void build(long long a[],int n)
{
  int maxn=-0x3f3f3f3f;
  for(int i=1;i<=n;i++)
  {
    if(a[i]>maxn)
    {
      root=i;
      maxn=a[i];
    }
    while(!top==0&&a[q[top-1]]<a[i])
    {
      ll[i]=q[top-1];
      top--;
    }
    if(!top==0)
    {
      rr[q[top-1]]=i;
    }
    q[top++]=i;
  }
}

int n,size;

long long a[100010],c[100010],b[100010],ans;

inline void add(int x,long long v)
{
  for(;x<=n;x+=(x&-x)) c[x]+=v;
}

inline long long query(int x)
{
  long long ans=0;
  for(;x;x-=(x&-x)) ans+=c[x];
  return ans;
}

inline void dfs(int u,int l,int r)
{
  if(u==0) return ;
  if(u-l>r-u)
  {
    for(int i=u;i<=r;i++)
    {
      int now=upper_bound(b,b+size+1,b[a[u]]/b[a[i]])-b;
      if(now) ans-=query(now-1);
    }
    dfs(ll[u],l,u-1);
    add(a[u],1);
    for(int i=u;i<=r;i++)
    {
      int now=upper_bound(b,b+size+1,b[a[u]]/b[a[i]])-b;
      if(now) ans+=query(now-1);
    }
    dfs(rr[u],u+1,r);
  }
  else
  {
    for(int i=l;i<=u;i++)
    {
      int now=upper_bound(b,b+size+1,b[a[u]]/b[a[i]])-b;
      if(now) ans-=query(now-1);
    }
    dfs(rr[u],u+1,r);
    add(a[u],1);
    for(int i=l;i<=u;i++)
    {
      int now=upper_bound(b,b+size+1,b[a[u]]/b[a[i]])-b;
      if(now) ans+=query(now-1);
    }
    dfs(ll[u],l,u-1);
  }
}
/*
这个地方的树状数组如果单层都要暴力然后删除的话就会挂，因为复杂度就不能保证
所以考虑中序遍历，加入贡献。可以发现，如果之前树状数组有的数，就可以在进入的时候消除影响，左子树上来的时候再记录。然后再通过小区间查询，就可以保证复杂度
*/
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
    scanf("%d",&a[i]);
    b[i]=a[i];
  }
  sort(b+1,b+n+1);
  size=unique(b+1,b+n+1)-b-1;
  for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+size+1,a[i])-b;
  build(a,n);
  dfs(root,1,n);
  printf("%lld\n",ans);
}
```


---

## 作者：kcn999 (赞：10)

提供一种题解区没有的做法。

---

依然是考虑分治，但是不需要令 $mid$ 为最大值位置，而是直接令 $mid = \dfrac{l+r}{2}$。

对于一个区间 $[l,r]$，设 $max1_j = \max\limits_{j \leq k \leq mid} \{ a_k \},max2_i = \max\limits_{mid < k \leq i} \{ a_k \}$，那么显然对于一个区间 $[j,i]$（$l \leq j \leq mid < i \leq r$)，如果 $a_j \times a_i \leq \max \{ max1_j,max2_i \}$，那么对答案的贡献为 $1$，否则为 $0$。

显然，$\forall j < j',max1_{j} \geq max1_{j'},\forall i > i',max2_i \geq max2_{i'}$，也就是 $max1,max2$ 都满足单调性。

我们可以在 $(mid,r]$ 中从左到右枚举 $i$，然后把 $[l,mid]$ 分成两个子区间 $S_1,S_2$，满足 $\forall j \in S_1,max1_j \geq max2_i,\forall j \in S_2,max1_j < max2_i$。显然 $S_1,S_2$ 满足 $S_1 = [l,c],S_2 = (c,mid]$ 的形式，并且随着 $i$ 不断增大（向右移），$c$ 只可能不变或变小（不动或向左移）。

![](https://cdn.luogu.com.cn/upload/image_hosting/x9xoe064.png)

对于 $[j,i]$（$j \in S_1$），对答案贡献 $1$ 的条件为 $a_j \times a_i \leq max1_j \Leftrightarrow a_i \leq \dfrac{max1_j}{a_j} \Leftrightarrow a_i \leq \left\lfloor \dfrac{max1_j}{a_j} \right\rfloor$。

对于 $[j,i]$（$j \in S_2$），对答案贡献 $1$ 的条件为 $a_j \times a_i \leq max2_i \Leftrightarrow a_j \leq \dfrac{max2_i}{a_i} \Leftrightarrow a_j \leq \left\lfloor \dfrac{max2_i}{a_i} \right\rfloor$。

那么我们可以开两个树状数组，分别维护 $S_1$ 中的 $\left\lfloor \dfrac{max1_j}{a_j} \right\rfloor$ 以及 $S_2$ 中的 $a_j$。枚举 $i$ 的时候，每当 $c$ 左移一位变成 $c-1$，就在 $S_1$ 的树状数组中删去 $\left\lfloor \dfrac{max1_c}{a_c} \right\rfloor$，并在 $S_2$ 的树状数组中增加 $a_c$。

计算贡献的时候，求出维护 $S_1$ 的树状数组中大于等于 $a_i$ 的个数，求出维护 $S_2$ 的树状数组中小于等于 $\left\lfloor \dfrac{max2_i}{a_i} \right\rfloor$ 的个数即可。

注意，这里要离散化，考虑我们只用维护 $\left\lfloor \dfrac{max1_j}{a_j} \right\rfloor$ 和 $a_j$，并且查询的时候只会查询 $a_i$ 和 $\left\lfloor \dfrac{max2_i}{a_i} \right\rfloor$，则离散化后最多只有 $4n$ 种元素，可以接受。

总复杂度为 $O(n \log^2 n)$。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define MAX_N (100000 + 5)
#define lowbit(x) ((x) & -(x))
using std::lower_bound;
using std::unique;
using std::sort;
using std::max;
using std::min;

int n;
int a[MAX_N], b[MAX_N * 4];
int s1[MAX_N * 4], s2[MAX_N * 4], cnt;
long long ans;

template <typename T>
void Read(T &x) {
	x = 0;
	char ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
}

template <typename T>
void Write(T x) {
	if (x >= 10) Write(x / 10);
	putchar(x % 10 + '0');
}

void Insert(int *s, int pos) {
	for (; pos <= cnt; pos += lowbit(pos)) 
		++s[pos];
}

void Delete(int *s, int pos) {
	for (; pos <= cnt; pos += lowbit(pos))
		--s[pos];
}

int Count(int *s, int pos) {
	int res = 0;
	for (; pos; pos -= lowbit(pos))
		res += s[pos];
	return res;
}


void Solve(int l, int r) {
	if (l == r) {
		if (a[l] == 1) ++ans;
		return;
	}
	int mid = l + r >> 1;
	Solve(l, mid);
	Solve(mid + 1, r);
	// 离散化
	cnt = 0;
	for (int i = mid, max1 = 0; i >= l; --i) {
		max1 = max(max1, a[i]);
		b[++cnt] = max1 / a[i];
	}
	for (int i = mid + 1, max1 = a[mid], max2 = 0, j = mid; i <= r; ++i) {
		max2 = max(max2, a[i]);
		while (l <= j && max1 < max2) {
			b[++cnt] = a[j];
			max1 = max(max1, a[--j]);
		}
		b[++cnt] = a[i];
		b[++cnt] = max2 / a[i];
	}
	sort(b + 1, b + cnt + 1);
	cnt = unique(b + 1, b + cnt + 1) - b - 1;
	// 计算贡献
	for (int i = mid, max1 = 0; i >= l; --i) {
		max1 = max(max1, a[i]);
		Insert(s1, lower_bound(b + 1, b + cnt + 1, max1 / a[i]) - b);
	}
	for (int i = mid + 1, max1 = a[mid], max2 = 0, j = mid; i <= r; ++i) {
		max2 = max(max2, a[i]);
		while (l <= j && max1 < max2) {
			Delete(s1, lower_bound(b + 1, b + cnt + 1, max1 / a[j]) - b);
			Insert(s2, lower_bound(b + 1, b + cnt + 1, a[j]) - b);
			max1 = max(max1, a[--j]);
		}
		ans += Count(s1, cnt) - Count(s1, lower_bound(b + 1, b + cnt + 1, a[i]) - b - 1);
		ans += Count(s2, lower_bound(b + 1, b + cnt + 1, max2 / a[i]) - b);
	}
	// 清空树状数组
	for (int i = mid, max1 = 0; i >= l; --i) {
		max1 = max(max1, a[i]);
		Delete(s1, lower_bound(b + 1, b + cnt + 1, max1 / a[i]) - b);
	}
	for (int i = mid + 1, max1 = a[mid], max2 = 0, j = mid; i <= r; ++i) {
		max2 = max(max2, a[i]);
		while (l <= j && max1 < max2) {
			Insert(s1, lower_bound(b + 1, b + cnt + 1, max1 / a[j]) - b);
			Delete(s2, lower_bound(b + 1, b + cnt + 1, a[j]) - b);
			max1 = max(max1, a[--j]);
		}
	}
}

int main() {
	Read(n);
	for (int i = 1; i <= n; ++i) {
		Read(a[i]);
		b[i] = a[i];
	}
	Solve(1, n);
	Write(ans);
	return 0;
}
```

---

## 作者：奇米 (赞：8)

# 题解 - $\mathrm{P4755}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/P4755)

## $\mathrm{Sol}$

一道套路题，很多题都用到了这个套路。但由于主席树的总总原因调了好久。。。

首先我们用单调栈 $O(n)$ 求出对于一个数 $i$ ，左右两边第一个比他大的数的位置为 $l_i$ 和 $r_i$。

那么我们就要用到一个套路就是每次我们枚举长度较短的一边来计算长的一边，这样子均摊下来是 $\log n$ 的。于是假设我们现在在 $i$ 的左区间内枚举到 $j$ ，那么我们就要在右区间理找出有几个 $a_k$ 满足 $a_k\leq \frac{a_i}{a_j}$。这个就是个经典问题啦，直接用主席树维护区间 $[l,r]$ 中有几个数小于 $x$。

总体来说时间复杂度为 $O(n\log^2 n)$

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
#define int long long  
using namespace std;

struct IO
{
	#define MAXSIZE (1 << 20)
	#define isdigit(x) (x >= '0' && x <= '9')
  	char buf[MAXSIZE],*p1,*p2;
  	char pbuf[MAXSIZE],*pp;
  	IO():p1(buf),p2(buf),pp(pbuf){}
  	inline char gc() {
    	if (p1==p2) p2=(p1=buf)+fread(buf,1,MAXSIZE,stdin);
    	return p1==p2?' ':*p1++;
  	}
	inline bool blank(char ch) {return ch==' '||ch =='\n'||ch == '\r'||ch == '\t';}
  	template <class T>
  	inline void read(T &x)
	{
	    register double tmp=1;register bool sign=0; x=0;
	    register char ch=gc();
	    for (;!isdigit(ch);ch=gc()) if(ch=='-') sign=1;
	    for (;isdigit(ch);ch=gc()) x=x*10+(ch-'0');
	    if (ch=='.') for (ch=gc();isdigit(ch);ch=gc()) tmp/=10.0,x+=tmp*(ch-'0');
	    if (sign) x=-x;
  	}
  	inline void read(char *s)
	{
    	register char ch=gc();
		for (;blank(ch);ch=gc());
		for (;!blank(ch);ch=gc()) *s++=ch;
    	*s=0;
  	}
  	inline void read(char &c) {for(c=gc();blank(c);c=gc());}
  	template<class t> inline void write(t x){
		if(x<0) putchar('-'),write(-x);
		else{if(x>9) write(x/10);putchar('0'+x%10);}
	}
} io;

const int mod=1e9+7;
const int mo=998244353;
const int N=1e5+5;
const int M=5e6+1; 

int n,m,l[N],r[N],stak[N],a[N],b[N],Rt[N],top,ds;

struct Seg
{
	int ls,rs,sum;
};
Seg T[N*30];

inline void insert(int pre,int &p,int l,int r,int pos)
{
	p=++ds;
	T[p]=T[pre];
	T[p].sum++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(pos<=mid) insert(T[pre].ls,T[p].ls,l,mid,pos);
	else insert(T[pre].rs,T[p].rs,mid+1,r,pos);
}

inline int ask(int pre,int p,int l,int r,int ql,int qr)
{
	if(ql>r||qr<l) return 0;
	if(l>=ql&&r<=qr) return T[p].sum-T[pre].sum;
	int mid=(l+r)>>1;
	int res=0;
	if(ql<=mid) res+=ask(T[pre].ls,T[p].ls,l,mid,ql,qr);
	if(qr>mid) res+=ask(T[pre].rs,T[p].rs,mid+1,r,ql,qr);
	return res;
}

signed main()
{
	io.read(n);
	For(i,1,n) 
	{
		io.read(a[i]);
		b[i]=a[i];
		r[i]=n,l[i]=1;
	}
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	stak[top=1]=0;
	For(i,1,n) 
	{
		while(top&&a[stak[top]]<a[i]) top--;
		if(top) l[i]=stak[top]+1;
		stak[++top]=i;
	}
	stak[top=1]=n+1;
	Dow(i,n,1)
	{
		while(top&&a[stak[top]]<=a[i]) top--;
		if(top) r[i]=stak[top]-1;
		stak[++top]=i;
	}
	For(i,1,n) 
	{
		int p=lower_bound(b+1,b+m+1,a[i])-b;
		insert(Rt[i-1],Rt[i],1,m,p);
	}
	int ans=0;
	For(i,1,n) 
	{
		if(i-l[i]<r[i]-i)
		{
			For(j,l[i],i) 
			{
				int rem=(ceil)(a[i]/a[j]);
				int p=upper_bound(b+1,b+m+1,rem)-b-1;
				ans+=ask(Rt[i-1],Rt[r[i]],1,m,1,p);
			}
		}
		else 
		{
			For(j,i,r[i])
			{
				int rem=(ceil)(a[i]/a[j]);
				int p=upper_bound(b+1,b+m+1,rem)-b-1;
				int gs=0;
				ans+=ask(Rt[l[i]-1],Rt[i],1,m,1,p);
			}
		}
	}
	io.write(ans);
	return 0;
}
```



---

## 作者：Trinity (赞：5)

# P4755 Beautiful Pair 2018 洛谷7月月赛 T4
## 题目描述
小D有个数列{ $a$ }，当一个数对$(i,j)(i\leq j)$满足 $a_i$ 和 $a_j$ 的积不大于 $a_i$, $a_{i+1}$,$...$,$a_j$	  中的最大值时，小$D$认为这个数对是美丽的.请你求出美丽的数对的数量。  
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 1\leq n\leq 10^5$   
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ 1\leq a_i \leq10^9$  

------------

感谢蒟蒻（Faker）[ZhYic](https://www.luogu.org/blog/noipruoji2017/)对思路和代码的莫大帮助。


------------
## 分析
$1$ . 题目很简短，看似不难，我比赛时也是这么想的，直到仔细看了看数据范围，才终于发现这是一道毒瘤数据结构题，关键是怎么避开枚举数对的$O(n^2)$复杂度。  
$2$ . 本人比赛时亲测，线段树查询（太慢了）或是$RMQ$算法（数组开不下）都应该只有$15$分左右，还需要优化的思想，例如贪心或分治思想，我们的策略是分治，或者我觉得更像优雅的暴力，需要数据结构来维护（例如线段树，主席树，树状数组，树抛等)。  
$3$ . 数据很毒瘤，需要离散化。（ 反正离散后$RMQ$我是没实现过，理论上可以 )  
## 解答
$1$ . 首先，我们能花 $O(logn)$ 的时间处理数据，算出区间 $[l,r]$ 最左端的最大值，取出它的位置 $index $。显然，根据分治的思想，**我们知道** $[l,r]$ **中满足条件的数对的数量等于** $[l,index-1]$ **和** $[index+1,r] $**中数对数的和**，**因为** $index$ **位置对应最大值，满足这个条件。**有了这个性质，我选择了维护一棵线段树来完成这个过程的计算，$std$ 代码中$O(n)$搞出的，我们多了$logn$的复杂度，但问题不大，~~也就爆炸~~。  
$2$ . 然后我们怎么算出区间中满足条件的数对数呢？我们观察：
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ a_i \times a_j=max(from\ a_i\ to\ a_j)=x$  
变个型：
$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ a_i= \frac{x}{a_j}$  
有了这个式子，我们可以这样，对于区间 $[l,r]$ 我们在 $[l,index-1]$ 中枚举 $a_i$ , 我们可以在 $[index+1,r]$ 中找到小于等于 $ \frac{a_{index}}{a_i}$的数，有多少这样的数，区间$[index+1,r]$中就有多少满足条件的数对数；然后我们对于 $[index+1,r]$ 也如法炮制，就计算出解答 $1$中的数对数了。然后，我们缩小区间（类似于线段树），一边计算，一边储存。我们要查询的区间不会很多，和线段树的一样 $O(nlogn)$ , 而在其中要枚举 $logn$ 次的数字，常数可以接受。    
$3$ . 我们选左边的区间，右边区间查询可以查询，这一部分我们又用主席树（ 没有学过的用树状数组反而更好，因为常数更小，代码更简单易懂 ）维护，但是基于暴力出奇迹的基本原理，复杂度还是可以接受的。我们稍利用前缀和的思想，显然，$[1,r]$ 中小于 $x$ 的数，减去 $[1,l-1]$ 中小于 $x$的数，就得到了 $[l,r]$中的数量，还是主席树来维护。  
$4$ . 总体来说，标程的复杂度是 $O(nlog^2n)$，而我的复杂度估计（比较玄学）是 $O(nlog^3n)$吧，各种递归树的常数稍大，但不影响$AC$掉这题。  
上代码，真的长，开始解释（ 数据结构不会多解释 ）
```cpp
inline int read()//卡常必备快读。
{
  int f=1,x=0;char ch=getchar();
  while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
  while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
  return f*x;
}
LL ans;//其他可以不开long long，但是答案要开，不然只有60分。
int n,len,a[N],drt[N],from[N],root[N];//len->离散化数组的长度，drt->Discretization离散化数组，from->对应原数组的位置，root->记录主席树的数据。
inline int cal_pos(int x)
{
  return upper_bound(drt+1,drt+len+1,x)-drt-1;//计算出x在离散数组中的位置，方便后来的调用。
}
inline int compare(int pos_1,int pos_2)
{
  if(a[pos_1]<a[pos_2])return pos_2;
  return pos_1;//比较位置1和2对应a数组中值的大小，更新解答1中的操作。
}
inline void inti()
{
  sort(drt+2,drt+n+2);//记住把drt多移动一位，可以省着减一。
  len=unique(drt+2,drt+n+2)-drt-1;
  for(int i=1;i<=n;i++)from[i]=lower_bound(drt+1,drt+len+1,a[i])-drt;//离散化，记下原位置，如果没有，头皮发麻。
}
struct segment_tree
{
  int mx[N*4];//区间最值。
  inline void pushup(int p)
  {
    mx[p]=compare(mx[ls],mx[rs]);//只要左右区间的最大值。
  }
  inline void build(int p,int l,int r)
  {
    if(l==r){mx[p]=l;return ;}
    int mid=(l+r)/2;
    build(ls,l,mid);
    build(rs,mid+1,r);
    pushup(p);
   // cout<<mx[p]<<endl;
  }
  inline int query(int p,int l,int r,int s,int t)//s，t是需要查询的区间。
  {
    //cout<<p<<' '<<mx[p]<<' '<<s<<' '<<t<<endl;
    if(s==l&&t==r)return mx[p];
    int mid=(l+r)>>1;
    if(t<=mid)return query(ls,l,mid,s,t);
    else if(s>mid)return query(rs,mid+1,r,s,t);
    else return compare(query(ls,l,mid,s,mid),query(rs,mid+1,r,mid+1,t));
  }//查询和建树同理。
}sgm_t;
struct president_tree//主席数。
{
  int cnt,child[N*40][2];//节点数，左右儿子数。
  LL sum[N*40];
  inline void pushup(int p)
  {
    sum[p]=sum[child[p][0]]+sum[child[p][1]];
  }
  inline void _insert(int last,int &p,int l,int r,int x,int delta)//x->加上的位置，delta如字面义。
  {
      //cout<<p<<' '<<child[p][0]<<' '<<child[p][1]<<' '<<sum[p]<<endl;
    p=++cnt;
    child[p][0]=child[last][0],child[p][1]=child[last][1],sum[p]=sum[last];
    if(l==r){sum[p]+=delta;return ;}
    int mid=(l+r)/2;
    if(x<=mid)_insert(child[last][0],child[p][0],l,mid,x,delta);
    else _insert(child[last][1],child[p][1],mid+1,r,x,delta);//这两句我先前打反了，毕竟不熟悉数据结构。
    pushup(p);
  }
  inline LL query(int p,int l,int r,int s,int t)
  {
    if(s==l&&t==r)return sum[p];
    int mid=(l+r)/2;
    if(t<=mid)return query(child[p][0],l,mid,s,t);
    else if(s>mid)return query(child[p][1],mid+1,r,s,t);
    else return query(child[p][0],l,mid,s,mid)+query(child[p][1],mid+1,r,mid+1,t);
  }
}prsd_t;
inline void solve(int l,int r)//递归跑，实力慢。
{
  //cout<<ans<<' '<<l<<' '<<r<<endl;
  if(l==r){if(a[l]==1)ans++;return ;}
  int index=sgm_t.query(1,1,n,l,r);//查到解答中的index的值，也就是最大值在区间中的位置。
  if(fabs(index-l)>fabs(r-index))//如果左边的数多于右边，这样枚举量少一些。
  {
    if(index>l)solve(l,index-1);
    for(int i=index;i<=r;i++)
    {
      int x,y;
      x=prsd_t.query(root[index-1],1,len,1,cal_pos(a[index]/a[i]));//解答2中的操作。
      y=prsd_t.query(root[l-1],1,len,1,cal_pos(a[index]/a[i]));
      ans+=(x-y);//解答4的操作。
    }
    solve(index,r);
  }
  else
  {
    if(index<r)solve(index+1,r);
    for(int i=l;i<=index;i++)
    {
      int x,y;
      x=prsd_t.query(root[r],1,len,1,cal_pos(a[index]/a[i]));
      y=prsd_t.query(root[index],1,len,1,cal_pos(a[index]/a[i]));
      ans+=(x-y);
    }
    solve(l,index);//同理处理另一边（我先想着一起处理，爆炸）。
  }
}
int main()
{
  n=read();
  for(int i=1;i<=n;i++)a[i]=drt[i+1]=read();//再强调一遍，多移动一位。
  sgm_t.build(1,1,n);
  inti();
  for(int i=1;i<=n;i++)
    prsd_t._insert(root[i-1],root[i],1,len,from[i],1);//构建主席树。
  solve(1,n);
  printf("%lld\n",ans);
  return 0;
}
```
## 总结
$1$ . 这道题是省选难度无疑，不管是数据结构的应用，还是分治思想的形成，都很考验能力，所以写不出来正常，我们还是能写出几十分的暴力的。  
$2$ . 很皮的是，这题的小细节很有（zhi）趣（ming），两棵树，一步错，整题爆炸，很难调试，很可能重新再来，模板要熟（可是我很不熟）。  
希望我的解答对大家有一丝帮助，不喜勿喷（但是最后一个黑题我到底该不该做呢？）

---

## 作者：Ebola (赞：4)

首先对每个点求出左边第一个比它大的位置、右边第一个比它大的位置。分别记作L\[p\], R\[p\]。这个可以直接用单调栈求出，正反各一遍即可

这样，对于一个位置p，如果选取的左端点在(L\[p\], p]中，右端点在[p, R\[p\])中，那么位置p就是最大值了

假如我们枚举左端点l，那么[p, R\[p\])中的一个右端点r应该满足：a\[l\] \* a\[r\] <= a\[p\]。不妨换一种写法：a\[r\] <= a\[p\] / a\[l\]。对于一个枚举到的左端点，不等式右边的东西是全部已知的，于是问题就变成了求区间[p, R\[p\])中有多少个小于等于a\[p\] / a\[l\]的数，这是主席树的经典应用

如果我们枚举的是右端点，那做法和上面是几乎完全一样的

那么对于一个位置p，我们是该枚举左端点还是右端点？根据启发式的思想，当然是哪个区间短枚举哪个啦，反正算出来答案都是一样的

根据启发式思想分析一波复杂度，不难发现枚举端点均摊一个log，再套上主席树的一个log，最终复杂度是两个log

虽然这题不会出现0，但有0是一件非常好玩的事，我们来思考一下。除0会RE，于是我们从初始序列中把0抹除，并记下原数列中0的数量。因为0作为端点的任何区间都合法，因此可以贡献n \* cnt0的答案。因为两个端点都是0的状况被我们再每个0位置时都考虑了一遍，所以最后还要减去C(cnt0, 2)

```cpp
#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef pair<int,int> pii;
const int N=100010;
int a[N],cnt0=0,tot=0,n;
int ch[N*20][2],sum[N*20],sz=0,rt[N];
int L[N],R[N],Hash[N],hs=0;
stack<pii> st;

void prework()
{
    for(int i=1;i<=tot;i++)
    {
        while(!st.empty()&&st.top().FR<a[i]) st.pop();
        L[i]=st.empty()?1:st.top().SE+1;
        st.push(pii(a[i],i));
    }
    while(!st.empty()) st.pop();
    for(int i=tot;i>=1;i--)
    {
        while(!st.empty()&&st.top().FR<=a[i]) st.pop();
        R[i]=st.empty()?tot:st.top().SE-1;
        st.push(pii(a[i],i));
    }
}

void insert(int &o,int p,int l,int r,int k)
{
    sum[o=++sz]=sum[p]+1;
    if(l==r) return;
    ch[o][0]=ch[p][0];
    ch[o][1]=ch[p][1];
    int mid=(l+r)/2;
    if(k<=mid) insert(ch[o][0],ch[p][0],l,mid,k);
    else insert(ch[o][1],ch[p][1],mid+1,r,k);
}

int query(int L,int R,int l,int r,int x)
{
    if(l==r) return sum[R]-sum[L];
    int mid=(l+r)/2;
    if(x<=mid) return query(ch[L][0],ch[R][0],l,mid,x);
    else return sum[ch[R][0]]-sum[ch[L][0]]+query(ch[L][1],ch[R][1],mid+1,r,x);
}

void xi_jin_ping_is_good()
{
    long long ans=0;
    for(int i=1;i<=tot;i++) Hash[i]=a[i];
    sort(Hash+1,Hash+1+tot);
    hs=unique(Hash+1,Hash+1+tot)-(Hash+1);
    for(int i=1;i<=tot;i++)
        a[i]=lower_bound(Hash+1,Hash+1+hs,a[i])-Hash;
    for(int i=1;i<=tot;i++) insert(rt[i],rt[i-1],1,hs,a[i]);
    for(int i=1;i<=tot;i++)
    {
        if(i-L[i]<=R[i]-i)for(int j=L[i];j<=i;j++)
        {
            int d=Hash[a[i]]/Hash[a[j]];
            int x=lower_bound(Hash+1,Hash+1+hs,d)-Hash;
            if(Hash[x]>d) x--;
            if(x) ans+=query(rt[i-1],rt[R[i]],1,hs,x);
        }
        else for(int j=i;j<=R[i];j++)
        {
            int d=Hash[a[i]]/Hash[a[j]];
            int x=lower_bound(Hash+1,Hash+1+hs,d)-Hash;
            if(Hash[x]>d) x--;
            if(x) ans+=query(rt[L[i]-1],rt[i],1,hs,x);
        }
    }
    ans+=1ll*cnt0*n-1ll*cnt0*(cnt0-1)/2;
    printf("%lld\n",ans%998244353);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        int x=read();
        if(!x) cnt0++;
        else a[++tot]=x;
    }
    prework();
    xi_jin_ping_is_good();
    return 0;
}
```



---

## 作者：pikabi (赞：3)

## tip : 线段树合并

最近打了些线段树合并，看到这类题不免想到用线段树合并来完成。想练线段树合并的同学可以康康~

如同楼下讲的，Beautiful Pair 的对数显然是在一段区间最大值的两端，同时如果区间内有 $1$ , 则也可用最大值 $\times 1 = $ 最大值得到。所以我们总共需要三颗线段树，其一保存区间最大值，其二保存区间 $1$ 的个数，其三为每个数的权值线段树（当然需要动态开点了）。

对于区间 $(l, r) $ ：如果只有一个数， 则修改权值线段树，并判断是否本身是 $1$ 即可；否则，由线段树 $1$ 取得其最值下标 $mid$ ，加上区间内 $1$ 的个数，分别递归 $mid$ 左部和 $mid$ 右部，并枚举长度小的那一区间，在另外一区间的线段树内查找小于等于目标 $k$ 的个数，最后把左右及 $mid$ 所代表的权值线段树合并即可。

有一点需要注意，如果 $mid$ 在当前区间的两端，需要特判合并才行。

总复杂度为 $O(n \times log^2 n)$ ，和普遍的主席树无大差别。 

奉上代码 $-->$

```
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cctype>
#define ll long long
#define inf 1023456789

using namespace std;

inline int read(){
	int x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

struct node{
	int val, pos;
}a[1000005];

int d[1000005], N = 0;

struct Segment_Tree{
	int pos;
	int l, r;
}c[5000005];

int n, b[100005], tot, rt[100005];
ll ans = 0;

inline int ls(int p){
	return p << 1;
}

inline int rs(int p){
	return p << 1 | 1;
}

inline void update(int p){
	if(a[ls(p)].val > a[rs(p)].val )
	a[p].val = a[ls(p)].val , a[p].pos = a[ls(p)].pos ;
	else a[p].val = a[rs(p)].val , a[p].pos = a[rs(p)].pos ;
}

inline void build(int p, int l, int r){
	if(l == r){
		a[p].val = b[l];
		a[p].pos = l;
		return;
	}
	int mid = l + r >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	update(p); 
}

inline int query(int p, int l, int r, int L, int R){
	if(L <= l && r <= R){
		return a[p].pos ;
	}
	int mid = l + r >> 1;
	int u = 0, v = 0;
	if(L <= mid) u = query(ls(p), l, mid, L, R);
	if(mid < R) v = query(rs(p), mid + 1, r, L, R);
	if(b[u] > b[v]) return u;
	return v;
}

inline void update2(int p){
	d[p] = d[ls(p)] + d[rs(p)];
}

inline void build2(int p, int l, int r){
	if(l == r){
		if(b[l] == 1){
			d[p]++;
		}
		return ;
	}
	int mid = l + r >> 1;
	build2(ls(p), l, mid);
	build2(rs(p), mid + 1, r);
	update2(p);
}

inline int query2(int p, int l, int r, int L, int R){
	if(L <= l && r <= R){
		return d[p] ;
	}
	int mid = l + r >> 1;
	int res = 0;
	if(L <= mid) res += query2(ls(p), l, mid, L, R);
	if(mid < R) res += query2(rs(p), mid + 1, r, L, R);
	return res;
}

inline void update3(int p){
	c[p].pos = c[c[p].l ].pos + c[c[p].r ].pos ;
}

inline void modify3(int &p, int l, int r, int k){
	if(!p) p = ++tot;
	if(l == r){
		c[p].pos = 1;
		return ;
	}
	int mid = l + r >> 1;
	if(k <= mid) modify3(c[p].l , l, mid, k);
	else modify3(c[p].r , mid + 1, r, k);
	update3(p);
}

inline int query3(int p, int l, int r, int L, int R){
	if(!p) return 0;
	if(L <= l && r <= R){
		return c[p].pos ;
	}
	int mid = l + r >> 1, res = 0;
	if(L <= mid) res += query3(c[p].l , l, mid, L, R);
	if(mid < R) res += query3(c[p].r , mid + 1, r, L, R);
	return res;
}

inline int Merge(int u, int v){
	if(!u || !v) return u | v;
	c[u].pos += c[v].pos ;
	c[u].l = Merge(c[u].l , c[v].l);
	c[u].r = Merge(c[u].r , c[v].r);
	return u;
}

inline void find(int l, int r){//递归查找
	if(l > r) return ;
	if(l == r){
		modify3(rt[l], 1, N, b[l]);
		if(b[l] == 1) ans++;
		return ;
	}
	int mid = query(1, 1, n, l, r);
	ans += query2(1, 1, n, l, r);
	modify3(rt[mid], 1, N, b[mid]);
	int L = mid - l, R = r - mid;
	if(L < R){
		find(mid + 1, r);
		find(l, mid - 1);
		for(int i = l; i < mid; i++){
			ans += (ll)query3(rt[mid + 1], 1, N, 1, b[mid] / b[i]);
		}
	}
	else {
		find(mid + 1, r);
		find(l, mid - 1);
		for(int i = mid + 1; i <= r; i++){
			ans += (ll)query3(rt[l], 1, N, 1, b[mid] / b[i]);
		}
	}
	if(mid + 1 > r) rt[l] = Merge(rt[l], rt[mid]);//特判合并
	else if(mid - 1 < l) rt[l] = Merge(rt[mid], rt[mid + 1]);
	else rt[l] = Merge(Merge(rt[l], rt[mid]), rt[mid + 1]);	
}

int main(){
	n = read();
	for(int i = 1; i <= n; i++)
	b[i] = read(), N = max(b[i], N);//N保存最大值
	build(1, 1, n);//最大值线段树
	build2(1, 1, n);//保存1的个数的线段树
	find(1, n);
	printf("%lld\n",ans);
}

```

完结*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：SGColin (赞：3)

首先思路还是标算的想法~~，但是我智障的写了分治。~~

这里说一个小技巧，可以减少对边界的讨论。

在调试的时候注意到 $1$ 的存在，使得扫描的区间和查询的区间的讨论麻烦了很多。


考虑把序列中所有的 $1$ 去掉，贡献单独算。

考虑如果序列中只有一个 $1$ ，位置记作 $p$，那么他和所有位置都会产生 $1$ 的贡献：

+ 若改位置为与 $p$ 构成的区间最大值，显然 $1\times x=x$，所以合法。

+ 若该位置不为与 $p$ 构成的区间最大值，那么 $1\times x$ 显然还要小于最大值。

因此只有一个 $1$ 的贡献就是 $n$ 。

多个 $1$ 的话把重复计数的区间去掉就行了，设有 $cnt$ 个 $1$，那么这部分贡献为 $cnt\times n-{n\choose cnt}$ 。

把剩下的连起来还是按照标程的算法离线算一下就可以了。

**虽然答案不会超过** ```int```，**但是会在计算过程中超过！！！**

```C++
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 100005
#define M 2000005
#define inf 2000000000
using namespace std;
typedef long long ll;

inline ll rd() {
  ll x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = getchar();
  }
  return x;
}

ll n, m, mx[20][N], a[N];

inline ll mmax(ll x, ll y) {
  return a[x] > a[y] ? x : y;
}

inline void build() {
  for (int i = 1; i <= n; ++i) mx[0][i] = i;
  for (int t = 1; (1 << t) <= n; ++t)
    for (int i = 1; i <= n - (1 << t) + 1; ++i)
      mx[t][i] = mmax(mx[t - 1][i], mx[t - 1][i + (1 << (t - 1))]);
}

inline ll query(ll l, ll r) {
  ll t = log2(r - l + 1);
  return mmax(mx[t][l], mx[t][r - (1 << t) + 1]);
}

ll tot, tmp[M];

struct Q {ll op, p, x;} q[M];

inline bool cmp(Q x, Q y) {return x.p < y.p;}

inline void divide(ll l, ll r) {
  if (r <= l) return;
  ll pos = query(l, r);
  ll mx =a[pos];
  if (pos - l < r - pos) {
    for (int i = l; i < pos; ++i) {
      q[++tot] = (Q){-1, pos, mx / a[i]};
      q[++tot] = (Q){1, r, mx / a[i]};
    }
  }
  else {
    for (int i = pos + 1; i <= r; ++i) {
      if (l - 1) q[++tot] = (Q){-1, l - 1, mx / a[i]};
      if (pos - 1) q[++tot] = (Q){1, pos, mx / a[i]};
    }
  }
  divide(l, pos - 1); divide(pos + 1, r);
}

ll c[M], ans;

inline ll lowbit(ll x) {return x & -x;}

inline void add(ll p, ll x) {
  for (int i = p; i < M; i += lowbit(i)) c[i] += x;
}

inline ll query(ll p) {
  ll res = 0;
  for (int i = p; i; i -= lowbit(i)) res += c[i];
  return res;
}

int main() {
  n = rd();
  for (int i = 1, x; i <= n; ++i) {
    x = rd();
    if (x == 1) ++ans;
    if (x > 1) {
      ++tmp[0];
      tmp[tmp[0]] = a[tmp[0]] = x;
    }
  }
  ans = ans * n - ans * (ans - 1) / 2;
  n = tmp[0];
  tmp[++tmp[0]] = 0;
  tmp[++tmp[0]] = inf;
  build(); divide(1, n);
  sort(tmp + 1, tmp + 1 + tmp[0]);
  tmp[0] = unique(tmp + 1, tmp + 1 + tmp[0]) - tmp - 1;
  for (int i = 1; i <= n; ++i)
    a[i] = lower_bound(tmp + 1, tmp + 1 + tmp[0], a[i]) - tmp;
  for (int i = 1; i <= tot; ++i)
    q[i].x = upper_bound(tmp + 1, tmp + 1 + tmp[0], q[i].x) - tmp - 1;
  sort(q + 1, q + 1 + tot, cmp);
  for (int i = 1, ptr = 1; i <= n; ++i) {
    add(a[i], 1);
    while (q[ptr].p == i && ptr <= tot) {
      ans += q[ptr].op * query(q[ptr].x);
      ++ptr;
    }
  }
  printf("%lld\n", ans);
  return 0;
}

```


---

## 作者：妩媚的ak萝莉 (赞：3)

## 题解：
这题是个很好的分治练习题。

一看数据范围就知道肯定要固定式子里的一项，用$O(1)$或$O(log n)$的复杂度统计此情况的答案，而区间变化时，最大值很容易变化，所以我们考虑怎样固定最大值：

首先考虑，如果直接选出区间最大值，有多少区间的最大值是它呢，当然是横跨它的所有区间了，不横跨它的区间又自成子问题，所以想到分治做法：找到区间最大值的位置，位置左右分别递归求解，然后统计横跨这个位置的符合条件的区间个数。

怎么统计呢，当前最大值设为Maxv，枚举一边的点i，另一边选择的区间的另一个端点的取值当然就是0~$\lfloor \frac{Maxv}{a[i]} \rfloor$，用主席树统计就可以了.

但是因为最大值点不像二分点那样稳定，轻易就会被卡掉。但我们可以将计就计，利用它的不稳定性，规定只枚举区间长度小的一边，这样如果数据想卡我们，我们反而跑得更快。

严格可以这样证明复杂度，当每一个点对复杂度做贡献，它所在区间一定比上一次至少短了一半，加上主席树（找最大值位置用St表$O(1)$），复杂度为$O(nlog^2n)$

## 代码：
```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
#define N 100050
const int Len=1e9;
struct Node{
	Node* l;
	Node* r;
	int val;
	Node(){l=r=NULL;val=0;}
};
Node* NewNode(){return new Node();}
int n;
int ai[N],St_v[N][20],St_p[N][20],Log[N];
Node* Rt[N];

void update(Node* bef,Node* o,int l,int r,int k)
{
	if(bef==NULL) bef=Rt[0];
//	printf("%d %d %d %d %d\n",bef==NULL,o==NULL,l,r,k);
	o->val=bef->val+1;
	if(l==r) return;
	int mid=((l+r)>>1);
	if(k<=mid){
		if(o->l==NULL) o->l=NewNode();
		o->r=bef->r;
		update(bef->l,o->l,l,mid,k);
	}
	else{
		if(o->r==NULL) o->r=NewNode();
		o->l=bef->l;
		update(bef->r,o->r,mid+1,r,k);
	}
}

int query(Node* bef,Node* o,int l,int r,int le,int ri)
{
	if(bef==NULL) bef=Rt[0];
	if(le<=l && r<=ri)
		return o->val-bef->val;
	int mid=((l+r)>>1),ret=0;
	if(le<=mid && o->l!=NULL)
		ret+=query(bef->l,o->l,l,mid,le,ri);
	if(ri>mid && o->r!=NULL)
		ret+=query(bef->r,o->r,mid+1,r,le,ri);
	return ret;
}

inline int find(int l,int r){
	int a=Log[r-l+1];
	if(St_v[l][a]>St_v[r-(1<<a)+1][a])
		return St_p[l][a];
	return St_p[r-(1<<a)+1][a];
}

long long Solve(int l,int r)
{
	if(l>r) return 0;
	if(l==r) return ai[l]<=1;
	int Max_p=find(l,r),Max_v=ai[Max_p];
	long long ret=0;
	ret+=Solve(l,Max_p-1);
	ret+=Solve(Max_p+1,r);
	if(Max_p-l<r-Max_p){
		for(int i=l;i<=Max_p;i++){
			if(ai[i]==0) ret+=r-Max_p+1;
			else ret+=query(Rt[Max_p-1],Rt[r],0,Len,0,Max_v/ai[i]);
		}
	}
	else{
		for(int i=Max_p;i<=r;i++){
			if(ai[i]==0) ret+=Max_p-l+1;
			else ret+=query(Rt[l-1],Rt[Max_p],0,Len,0,Max_v/ai[i]);
		}
	}
	return ret;
}

void Test_St(){
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++)
			printf("%d ",find(i,j));
		printf("\n");
	}
}

void Test_Tree(){
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
			cout<<query(Rt[i-1],Rt[j],0,Len,2,4)<<" ";
		cout<<endl;
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
		Rt[i]=NewNode();
	int np=0;
	for(int i=1;i<=n;i++){
		Log[i]=np;
		if(i==(1<<(np+1)))
			np++;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai[i]);
		St_v[i][0]=ai[i];
		St_p[i][0]=i;
		update(Rt[i-1],Rt[i],0,Len,ai[i]);
	}
	for(int a=1;a<=18;a++)
		for(int i=1;i+(1<<a)-1<=n;i++)
		{
			if(St_v[i][a-1]<St_v[i+(1<<(a-1))][a-1]){
				St_v[i][a]=St_v[i+(1<<(a-1))][a-1];
				St_p[i][a]=St_p[i+(1<<(a-1))][a-1];
			}
			else{
				St_v[i][a]=St_v[i][a-1];
				St_p[i][a]=St_p[i][a-1];
			}
		}
	printf("%lld\n",Solve(1,n));
	return 0;
}
```

---

## 作者：y_immortal (赞：2)

这个题，看到题的第一想法就是QwQ，一看就是dp或者一些恶心的数据结构题，但是想了一会dp，发现不太可行。那么我们可以考虑通过**分治** 来解决这个问题

我们考虑，对于一个区间$[l,r]$，我们可以通过这个区间的$mx$（表示最大的$a_i$）来解决，因为要求乘积不能大于区间的最大值，所以我们在 计算区间的时候，$mx$一般情况下是不能和别的数进行组合的。所以说，按照mx来分组，那么当前区间的答案就是$[l,mx-1]$的答案加上$[mx+1,r]$，然后加上两个区间产生的贡献。
QwQ那么怎么求左右区间产生的贡献呢
<br>
我们考虑，对于一个固定的左端点$l$，我们需要在$[mx+1,r]$区间找出，小于$\lfloor \frac{mx}{a_l} \rfloor$的数的个数
然后我们枚举所有的左端点，然后数一数，最后考虑$mx$这个端点可以不可以跟左边的这个区间进行组合


那么我们应该怎么求一个区间内小于等于一个数的个数呢

QwQ
呀，BIT！树状数组 嗯！
我们考虑将每个数进行离散化，然后维护一个权值树状数组，然后我们每次只需要$query(find(\lfloor \frac{mx}{a_l} \rfloor))$就可以，其中$find$的函数的作用是，找到这个值离散化后的小于等于它的最大的值，其实可以直接lower_bound

记得离散化！



还有一些人会问，这个算法的时间复杂度可以保证吗？QwQ具体的证明我也不是很会呀，不过可以感性l理解

如果我们每次挑选的$mx$，都选择比较中间的，那么我们可以大致理解是$O(nlogn)$的

直接上代码

dfs版的分治

非常理解，个人敢接


```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<unordered_map>
using namespace std;

inline int read()
{
  int x=0,f=1;char ch=getchar();
  while (!isdigit(ch)) {if (ch=='-') f=-1;ch=getchar();}
  while (isdigit(ch)) {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
  return x*f;
}

const int maxn =  1e5+1e2;

int c[maxn];
int a[maxn];
int b[maxn];
int n,m;
int dp[maxn][23];
int p[maxn];
int tmp = 0;
unordered_map<int,int> mp;

struct Node{
    int id,val;
};

Node g[maxn];

int lowbit(int x)
{
    return (-x) & x;
}

void update(int x,int p)
{
    for (int i=x;i<=n;i+=lowbit(i)) c[i]+=p;
}

long long query(int x)
{
    long long ans=0;
    for (int i=x;i;i-=lowbit(i)) ans+=(long long)c[i];
    return ans;
}

int find(int x)
{
    if (x>p[n]) return tmp;
    return g[upper_bound(p+1,p+1+n,x)-p-1].id;
}

bool cmp(Node a,Node b)
{
    return a.val<b.val;
}

int countmax(int x,int y)
{
    int k = log2(y-x+1);
    return max(dp[x][k],dp[y-(1 <<k)+1][k]);
}

void init()
{
    for (int j=1;j<=21;j++)
      for (int i=1;i<=n;i++)
      {
      	 if (i+(1 << j)-1<=n)
      	 {
      	 	dp[i][j]=max(dp[i][j-1],dp[i+(1 << (j-1))][j-1]);
           }
      }	
}

long long solve(int l,int r)
{
    if (l>r) return 0;
    if (l==r)  {
      if (a[l]==1)return 1;
      else return 0;
    }
    long long cnt=0;
    int mid = (l+r) >> 1;
    int mx = countmax(l,r),pos=0;
    for (int i=l;i<=r;i++)
    {
        if (a[i]==mx) {
           if (!pos || abs(mid-i)<abs(mid-pos)) pos=i;
        }
    }
    cnt+=solve(l,pos-1);
    cnt+=solve(pos+1,r);
    for (int i=pos+1;i<=r;i++) update(b[i],1);
    for (int i=l;i<=pos;i++) cnt=cnt+(query(find(mx/a[i])));
    for (int i=pos+1;i<=r;i++) update(b[i],-1);
    //cout<<l<<" "<<r<<" "<<cnt<<endl;
    for (int i=l;i<=pos-1;i++) update(b[i],1);
     cnt=cnt+(query(find(mx/a[pos])));
    for (int i=l;i<=pos-1;i++) update(b[i],-1);	
    //out<<l<<" "<<r<<" "<<cnt<<endl;
    if (a[pos]==1) cnt++;
    return cnt;
}

int main()
{
  n=read();
  for (int i=1;i<=n;i++) a[i]=read(),g[i].id=i,g[i].val=a[i],dp[i][0]=a[i];
  init();
  sort(g+1,g+1+n,cmp);
  for (int i=1;i<=n;i++)
  {
  	 if (g[i].val!=g[i-1].val) tmp++;
  	 b[g[i].id]=tmp;
  	 mp[a[g[i].id]]=tmp;
  }
  //for (int i=1;i<=n;i++) cout<<b[i]<<" "; 
  memset(g,0,sizeof(g));
  for (int i=1;i<=n;i++) p[i]=a[i],g[i].val=a[i],g[i].id=b[i];
  sort(g+1,g+1+n,cmp);
  sort(p+1,p+1+n);
  //cout<<endl;
  long long ans=solve(1,n);
  cout<<ans;
  return 0;
}

``` 

---

## 作者：lemir3 (赞：1)

## 题目分析

计数题,考虑分治.

对于分治到的一个区间$(l,r)$,用st表取出其中最大值所在的位置mid,然后按照$(l,mid-1)$和$(mid+1,r)$分下去.

因为可以知道的是,当前区间$(l,r)$受到mid位置上的数的影响,所以考虑统计跨过mid位置的数对.

这里使用主席树,统计一个区间上小于a[mid]/a[i]的数的个数,即为答案.

因为值域太大需要离散化.

## 代码

```cpp
#include "iostream"
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "cmath"
#include "cctype"
#include "algorithm"
#include "set"
#include "queue"
#include "map"
#include "vector"
#include "stack"
#define lxl long long
#define R register
#define INF 0x3f3f3f3f
#define debug(x) printf("debug:%lld\n",x)
using namespace std;
const lxl maxn=200010;
lxl n,size,ans;
lxl a[maxn],h[maxn],st[maxn][20],lg[maxn];
struct _SegmentTreeNode
{
    _SegmentTreeNode *lson,*rson;
    lxl l,r,sum;
}*root[maxn];
struct _SegmentTree
{
    void BulitTree(_SegmentTreeNode *t,lxl l,lxl r)
    {
        lxl mid((l+r)>>1);
        t->l=l,t->r=r,t->sum=0;
        if(l==r)
        {
            t->lson=t->rson=NULL;
            return;
        }
        t->lson=new _SegmentTreeNode,t->rson=new _SegmentTreeNode;
        BulitTree(t->lson,l,mid),BulitTree(t->rson,mid+1,r);
    }
    _SegmentTreeNode *insert(_SegmentTreeNode *t,lxl l,lxl r,lxl x,lxl val)
    {
        lxl mid((l+r)>>1);
        _SegmentTreeNode *p=new _SegmentTreeNode;
        p->lson=t->lson,p->rson=t->rson,p->l=t->l,p->r=t->r,p->sum=t->sum+val;
        if(l==r)return p;
        if(x<=mid)p->lson=insert(t->lson,l,mid,x,val);
        else p->rson=insert(t->rson,mid+1,r,x,val);
    //  p->sum=p->lson->sum+p->rson->sum;
        return p;
    }
    lxl query(_SegmentTreeNode *pre,_SegmentTreeNode *t,lxl l,lxl r,lxl x,lxl y)
    {
        if(x>r||y<l)return 0;
        lxl mid((l+r)>>1),sum(0);
        if(x<=l&&y>=r)return t->sum-pre->sum;
        if(x<=mid)sum+=query(pre->lson,t->lson,l,mid,x,y);
        if(y>mid)sum+=query(pre->rson,t->rson,mid+1,r,x,y);
        return sum;
    }
}SegmentTree;
inline lxl read()
{
    char c=getchar();
    lxl f(1),x(0);
    for(;!isdigit(c);c=getchar())(c=='-')&&(f=-1);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    return f*x;
}
inline void ST()
{
    lg[0]=-1;
    for(R int i(1);i<=n;++i)lg[i]=lg[i>>1]+1;
    for(R int i(1);i<=n;++i)st[i][0]=i;
    for(R int j(1);j<=17;++j)
        for(R int i(1);i+(1<<j)-1<=n;++i)
            st[i][j]=a[st[i][j-1]]>=a[st[i+(1<<(j-1))][j-1]]?st[i][j-1]:st[i+(1<<(j-1))][j-1];
}
inline lxl STQuery(lxl l,lxl r)
{
    lxl t=lg[r-l+1];
    return a[st[l][t]]>=a[st[r-(1<<t)+1][t]]?st[l][t]:st[r-(1<<t)+1][t];
}
void go(lxl l,lxl r)
{
    if(l>r)return;
    if(l==r)
    {
        ans+=(h[a[l]]==1||h[a[l]]==0);
        return;
    }
    lxl mid=STQuery(l,r);
//  debug(l),debug(r),debug(mid);putchar('\n');
    if(r-mid+1<=mid-l+1)
        for(R int i(mid);i<=r;++i)
        {
            lxl pla=upper_bound(h+1,h+1+size,h[a[mid]]/h[a[i]])-h-1;
            ans+=SegmentTree.query(root[l-1],root[mid],1,size,1,pla);
        }
    else
        for(R int i(l);i<=mid;++i)
        {
            lxl pla=upper_bound(h+1,h+1+size,h[a[mid]]/h[a[i]])-h-1;
            ans+=SegmentTree.query(root[mid-1],root[r],1,size,1,pla);
        }
    go(l,mid-1),go(mid+1,r);
}
int main(void)
{
//  freopen("data.txt","r",stdin);
    n=read();
    for(R int i(1);i<=n;++i)a[i]=h[i]=read();
    sort(h+1,h+1+n);
    size=unique(h+1,h+1+n)-h-1;
    for(R int i(1);i<=n;++i)a[i]=lower_bound(h+1,h+1+size,a[i])-h;
    ST();
    root[0]=new _SegmentTreeNode;
    SegmentTree.BulitTree(root[0],1,size);
    for(R int i(1);i<=n;++i)root[i]=SegmentTree.insert(root[i-1],1,size,a[i],1);
    go(1,n);
    printf("%lld\n",ans);
    return 0;
}
```

---

