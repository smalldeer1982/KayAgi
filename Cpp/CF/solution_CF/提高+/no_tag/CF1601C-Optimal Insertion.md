# Optimal Insertion

## 题目描述

### 题目大意

给定两个序列 $a,b$，长度分别为 $n,m(1\leq n,m\leq 10^6)$。接下来将 $b$ 中的所有元素以**任意方式**插入序列 $a$ 中**任意位置**，请找出一种插入方式使结果序列中的逆序对数量最小化，并输出这个最小值。

**关于插入**：任意方式插入任意位置的示例如下。

例如 $a=\{1,2,3,4\},b=\{4,5,6\}$,则 $c=\{4,\underline1,5,\underline2,\underline3,\underline4,6\},\{\underline1,\underline2,6,5,\underline3,4,\underline4\}\dots$ 均为合法的插入方式。但你不能修改 $a$ 的顺序。

## 样例 #1

### 输入

```
3
3 4
1 2 3
4 3 2 1
3 3
3 2 1
1 2 3
5 4
1 3 5 3 1
4 3 6 1```

### 输出

```
0
4
6```

# 题解

## 作者：Godのfather (赞：10)

## 题解：CF1601C Optimal Insertion

> 翻译自 codeforces 官方题解，修改了其中部分谬误，增加了 std

首先将 b 数组从小到大排序，保持相对顺序不变插入 a 中。容易证明，排序一定比不排序更优。

假设 b 插入到 a 中的位置为 $p_1,p_2,\dots,p_m$。（ $p_i=j$ 表示 $b_i$ 插在 $a_i$ 前面，特别地，$p_i=n+1$ 表示 $b_i$ 插在 a 数组的最后）

考虑分治求 p 数组。

设 ${\rm solve}(l_1,r_1,l_2,r_2)$ 表示将 $b_{l_1},b_{l_1+1},\dots,b_{r_1}$ 插入到 a 数组的区间 $[l_2,r_2]$ 中。

1. 若 $l_1 > r_1$ 不操作直接返回

2. 令 ${\rm mid}=\left\lfloor\frac{l_1+r_1}{2}\right\rfloor$，

   则 $b_{\rm mid}$ 对整个序列的贡献 ${\rm all}=[a_i>b_{\rm mid}](i\leq p_{\rm mid})+[a_i<b_{\rm mid}](i>p_{\rm mid})$ 

   对区间 $[l_2,r_2]$ 的贡献 ${\rm par}=[a_i>b_{\rm mid}](l_2\leq i\leq p_{\rm mid})+[a_i<b_{\rm mid}](p_{\rm mid}<i\leq r_{2})$

   容易发现，${\rm all} - {\rm par}$ 是一个常数，因此要使全局贡献最小化，只需要最小化 ${\rm par}$。

   ${\rm par}$ 最小时，$p_{\rm mid}$ 可以在 $\Theta(l_2-r_2)$ 的时间复杂度内求出。

3. 递归解决 ${{\rm solve}(l_1,mid-1,l_2,p_{\rm mid})},{\rm solve}(mid+1,r_1,p_{\rm mid},r_2)$

这个函数的复杂度是 $\Theta(n\log m)$ ，因为一共递归了 $\log m$ 层，每层操作都是 $\Theta (n)$ 的。

最后，根据求出来的 p 数组，我们将获得插入后完整的序列，然后求得逆序对数。

总时间复杂度：$\Theta((n+m)\log (n+m))$

除此之外，还有一种用线段树的方法也在相同的时间复杂度下解决此题。

code（树状数组求逆序对）：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int w = 0, f = 1;
    char ch = getchar();
    while (ch < '0' or ch > '9')
    {
        if (ch == '-')
            f = -f;
        ch = getchar();
    }
    while (ch >= '0' and ch <= '9')
        w = w * 10 + ch - '0', ch = getchar();
    return w * f;
}
const int maxn = 1e6 + 5, INF = 1e9 + 7;
int n, m, a[maxn], b[maxn], p[maxn], sum1[maxn], sum2[maxn], uni[maxn << 1], cnt, t[maxn << 1];
vector<int> c[maxn];
void solve(int l1, int r1, int l2, int r2)
{
    if (l1 > r1)
        return;
    int mid = (l1 + r1) >> 1;
    sum1[l2 - 1] = sum2[l2 - 1] = 0;
    for (int i = l2; i <= r2; i++)
    {
        sum1[i] = sum2[i] = 0;
        if (a[i] > b[mid])
            sum1[i]++;
        if (a[i] < b[mid])
            sum2[i]++;
    }
    for (int i = l2 + 1; i <= r2; i++)
        sum1[i] += sum1[i - 1];
    for (int i = r2 - 1; i >= l2; i--)
        sum2[i] += sum2[i + 1];
    p[mid] = 0;
    for (int i = l2; i <= r2; i++)
        if (sum1[i - 1] + sum2[i] < sum1[p[mid] - 1] + sum2[p[mid]] or p[mid] == 0)
            p[mid] = i;
    solve(l1, mid - 1, l2, p[mid]), solve(mid + 1, r1, p[mid], r2);
}
int Find(int x)
{
    return lower_bound(uni + 1, uni + cnt + 1, x) - uni;
}
void add(int x, int y)
{
    for (; x <= cnt; x += x & -x)
        t[x] += y;
}
int ask(int x)
{
    int ans = 0;
    for (; x; x -= x & -x)
        ans += t[x];
    return ans;
}
int main()
{
    int _ = read();
    while (_--)
    {
        n = read(), m = read();
        cnt = 0;
        for (int i = 1; i <= n; i++)
            a[i] = read(), uni[++cnt] = a[i], c[i].clear();
        for (int i = 1; i <= m; i++)
            b[i] = read(), uni[++cnt] = b[i];
        sort(b + 1, b + m + 1);
        sort(uni + 1, uni + cnt + 1);
        cnt = unique(uni + 1, uni + cnt + 1) - uni - 1;
        solve(1, m, 1, n + 1);
        int tot = m;
        for (int i = n + 1; i >= 0; i--)
        {
            c[i].clear();
            if (i <= n)
                c[i].emplace_back(Find(a[i]));
            while (p[tot] == i and tot)
                c[i].emplace_back(Find(b[tot--]));
        }
        for (int i = 0; i <= cnt; i++)
            t[i] = 0;
        long long ans = 0;
        for (int i = n + 1; i >= 1; i--)
            for (auto it : c[i])
            {
                ans += ask(it - 1);
                add(it, 1);
            }
        printf("%lld\n", ans);
    }
    return 0;
}
```



---

## 作者：iamzq (赞：10)

### 前置知识：贪心，线段树

 贪心需要用到两个易证结论：
 
 1.将 $b$ 插入 $a$ 时，$b$ 是以从小到大的顺序插入
 
 证明：不妨设 $b$ 中插入的两个数 $x$ 和 $y$($x \leq y$)，现在考虑交换两个数。显然交换前后与 $x$ 左边的和 $y$ 右边的对答案没有影响，现在考虑两数中间的数，假设有一个数 $z$。
 
 ①$z \leq x$ 或 $z \geq y$，显然对答案还是没有影响。$ans+1$。
 
 ②$x < z < y$，$ans+3$。
 
 所以答案无论怎样都会增大。
 
 如果 $b$ 中只有一个数 $x$，将 $x$ 先插在 $a$ 最左边并计算当前逆序对数，之后将 $x$ 向后交换。如果与之交换的数比 $x$ 大，则答案会 $+1$ ；相等则不变；小，则 $-1$。于是容易想到新建一个由 $+1$，$0$ 和 $-1$ 构成的数列，求其最小前缀。称其最小前缀对应的点为$x$的最优决策点。
 
 2.若 $x<y$，则 $x$ 的最优决策点 $\leq y$ 的最优决策点。
 
 证明：当 $x$ 变成 $y$ 后，新建数列中只会有一些数变小，因此最优决策点只有可能会往后移。
 
 所以先把 $b$ 中的数排序，放在 $a$ 左边，计算逆序对后依次加上 $b$ 中每一个数对应数列的最小前缀就ok了。
 
 这个可以使用线段树来维护，时间复杂度 $O(n\log n)$。
 
 ## Code
 ```
#include <bits/stdc++.h>
#define ll long long
#define lc (rt<<1)
#define rc (rt<<1|1)
#define mid (l+r>>1)
using namespace std;
const int M=1e6+5;
ll a[M], b[M];
struct S{ll s, p; bool operator < (const S &a) const{return s<a.s;}}sa[M];
//sa表示排完序后的a，供后续维护用
int read()
{
	int s=0, t=1; char ch=getchar();
	for (; !isdigit(ch); ch=getchar()) if (ch=='-') t=-1;
	for (; isdigit(ch); ch=getchar()) s=s*10+ch-'0';
	return s*t;
}
struct Segment{int s, la;}t[M<<2];
//线段树里存所有位置的前缀和
void pushup(int rt){t[rt].s=min(t[lc].s, t[rc].s);}
void build(int rt, int l, int r)
{
	t[rt].la=0;
	if (l==r) return (void)(t[rt].s=l);
	build(lc, l, mid); build(rc, mid+1, r);
	pushup(rt);
}
void pushdown(int rt)
{
	t[lc].s+=t[rt].la; t[rc].s+=t[rt].la;
	t[lc].la+=t[rt].la; t[rc].la+=t[rt].la;
	t[rt].la=0;
}
void modify(int rt, int l, int r, int x, int y, int z)
{
	if (x<=l&&r<=y) return (void)(t[rt].s+=z, t[rt].la+=z);
	if (t[rt].la) pushdown(rt);
	if (x<=mid) modify(lc, l, mid, x, y, z);
	if (y>mid) modify(rc, mid+1, r, x, y, z);
	pushup(rt);
}
int query(int rt, int l, int r, int x, int y)
{
	if (x<=l&&r<=y) return t[rt].s;
	if (t[rt].la) pushdown(rt);
	int res=1e9;
	if (x<=mid) res=min(res, query(lc, l, mid, x, y));
	if (y>mid) res=min(res, query(rc, mid+1, r, x, y));
	return res;
}
ll tr[M<<1], n, m, li[M<<1], tot;
void add(int x){for (; x<=n+m; x+=x&-x) tr[x]++;}
int ask(int x){ll res=0; for (res; x; x-=x&-x) res+=tr[x]; return res;}
int lsh(int x)
{
	int l=1, r=tot;
	while (l<=r)
	{
		if (li[mid]==x) return mid;
		if (li[mid]<x) l=mid+1;
		else r=mid-1; 
	}
	return -1;
}
int init()
{
	for (int i=1; i<=n; i++) li[++tot]=a[i];
	for (int i=1; i<=m; i++) li[++tot]=b[i];
	sort(li+1, li+tot+1); tot=unique(li+1, li+tot+1)-li-1;
	for (int i=1; i<=n; i++) a[i]=lsh(a[i]);
	for (int i=1; i<=m; i++) b[i]=lsh(b[i]);
}
int main()
{
	int T=read();
	while (T--)
	{
		n=read(), m=read();
		for (int i=1; i<=n; i++) a[i]=read();
		for (int i=1; i<=m; i++) b[i]=read();
		init();//离散化
		for (int i=1; i<=n; i++) sa[i]=S{a[i], i};
		sort(b+1, b+m+1); sort(sa+1, sa+n+1);
		build(1, 1, n);
		ll ans=0; sa[n+1].s=1e9;
		for (int i=1, j=1; i<=n+1; i++) while (j<=m&&b[j]<=sa[i].s) ans+=i-1, j++;
		for (int i=n; i>=1; i--) ans+=ask(a[i]-1), add(a[i]);
  	//此时ans已记录b放a左边后的逆序对总数
		for (int i=1, j=1; i<=m; i++)
		{
			if (b[i]!=b[i-1])
			{
				while (j<=n&&sa[j].s<b[i])
				{
					if (sa[j].s==b[i-1]) modify(1, 1, n, sa[j].p, n, -1);
					else modify(1, 1, n, sa[j].p, n, -2);
					j++;
				}
				int k=j;
				while (k<=n&&sa[k].s==b[i])
					modify(1, 1, n, sa[k].p, n, -1), k++;
			}//将<=b的数对应位置变为0或-1
			ans+=min(0, query(1, 1, n, 1, n));
		}
		printf("%lld\n", ans);
		for (int i=1; i<=n+m; i++) tr[i]=0;
		tot=0;
	}
}
```


---

## 作者：little_sheep917 (赞：8)

> 给出一个长度为 $n$ 的序列 $a$ 和长度为 $m$ 的序列 $b$ .
>
> 你可以把 $b$ 以任意的顺序插入 $a$ 的任意位置 ，得到一个长度为 $n+m$ 的序列 $c$ .
>
> 求 $c$ 最少有多少个逆序对 .
>
> 多测，有 $t$ 组数据 .
>
> $1\leq t\leq 10^4,1\leq n,m\leq 10^6,1\leq a_i\leq 10^9,1\leq b_i\leq 10^9,\sum n\leq 10^6,\sum m\leq 10^6$ 

首先考虑 $b$ 的插入顺序 . 猜测 $b$ 是按照从小到大顺序插入的 . 

考虑对于当前插入 , 存在位置 $b_i>b_{i+1}$ ，插入的位置是 $p_1$ 和 $p_2$考 ,虑交换两个数 .

交换前的 $a$ 产生的代价是区间 $[0,p_1-1]$ 中 $a_j>b_i$ 数的个数 $+$ 区间 $[p_2+1,n-1]$ 中 $a_j<b_i$ 数的个数 $+$ 区间 $[0,p_1-1]$ 中 $a_j>b_i$ 的个数 $+$ 区间 $[p_2+1,n-1]$ 中 $a_j<b_i$ 数的个数 $+$ $[p_1,p_2]$ 中 $a_j<b_i$

 数的个数 $+$ $[p_1,p_2]$ 中 $a_j>b_{i+1}$ 数的个数 .

交换后的 $a$ 产生的代价是区间 $[0,p_1-1]$ 中 $a_j>b_i$ 数的个数 $+$ 区间 $[p_2+1,n-1]$ 中 $a_j<b_i$ 数的个数 $+$ 区间 $[0,p_1-1]$ 中 $a_j>b_i$ 的个数 $+$ 区间 $[p_2+1,n-1]$ 中 $a_j<b_i$ 数的个数 $+$ $[p_1,p_2]$ 中 $a_j<b_{i+1}$

 数的个数 $+$ $[p_1,p_2]$ 中 $a_j>b_{i}$ 数的个数 . 

前面很长一段都是相同的 ，对于后面的部分 ，因为 $b_i>b_{i+1}$ ，所以必定有 :

- $[p_1,p_2]$ 中 $a_j<b_i$ 数的个数 $\geq$​  $[p_1,p_2]$ 中 $a_j<b_{i+1}$ 数的个数 
- $[p_1,p_2]$ 中 $a_j>b_{i+1}$ 数的个数 $\geq$ $[p_1,p_2]$ 中 $a_j>b_{i}$ 数的个数 

所以，交换之后不会更劣 .

因此，从小到大插入是最优的 .

将 $b$ 排完序之后是 $b_0$ 到 $b_{n-1}$ . 对于 $b_i$ 来说，$b_{i-1}$ 最优插入位置集合中最左端的位置必定小于等于 $b_i$ 最优插入位置集合中最左端的位置 . 

考虑证明， $b_{i-1}$ 最优插入位置集合中最左端的位置为 $p_1$ ，$b_i$ 最优插入位置集合中最左端的位置为 $p_2$ .

那么，$p_1$ 点 $a$ 产生的代价是 $[0,p_1-1]$ 中 $a_j>b_{i-1}$ $+$ $[p_1,n-1]$ 中 $a_j<b_{i-1}$ .

将 $b_i$ 放到 $p_1$ 上面，$[0,p_1]$ 产生的代价必然是不增的，$[p_1,n-1]$ 中产生的代价必然是是不降的 . 

考虑对于 $b_i$ ，如果向左移动决策点 ，原本在 $[b_{i-1},b_i-1]$ 的数 $1\to 1$ ，代价不变，在 $[0,b_{i-1}]$ 的数会产生 $0\to 1$ 的代价 ，$[b_{i}+1,\infty)$ 的数产生的代价由 $1\to 0$ . 

考虑对于 $b_{i-1}$ ，如果向左移动决策点，原本在 $[b_{i-1},b_i-1]$ 的数 $1\to 0$ ，代价减 $1$ ，在 $[0,b_{i-1}]$ 的数会产生 $0 \to 1$ 的代价，$[b_i+1,\infty]$ 的数产生的代价是 $1\to 0$ .

唯一的区别在于 $[b_i,b_i-1]$ 的点，$b_i$ 不变化  $b_{i-1}$ 是减一，考虑用反证法简单证明一下， $p_1\leq p_2$ 必然成立 . 

因此，$p_0\leq p_1\leq \cdots \leq p_{n-1}$ 必然成立 . 也就是每个 $b_i$ 都能放到最优位置上 .

接下来有两种不同的方法处理 .

#### sol1 

建立一棵线段树，每个位置维护插入位置 $i$ 新增加的逆序对数 .

新增加的逆序对数由两部分组成，前面比 $x$ 大的 $+$ 后面比 $x$ 小的 .

从小到大依次插入 $b$ ，那么 $x$ 也从小变到大 . 

当 $x$ 变到 $y$ 的时候 ， $x<y$ , 考虑对于线段树的影响 .

对于 $a$ 中 ，在区间 $[x+1,y]$ 的值对后面位置的影响会消失，操作为区间减一 .

对于 $a$ 中，在区间 $[x,y-1]$ 的值对前面位置会开始有影响，操作为区间加一 .

因为证明了最有位置最小值递增，所以每个 $b_i$ 都能取到最小值 .

所以，只需要区间修改，全局最大值即可 .

时间复杂度 : $O(n\log n)$

空间复杂度 : $O(n)$


```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(long long res){
	if(res==0){
		putchar('0');
		return;
	}
	int a[20],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)
		putchar(a[i]+'0');
}
int t;
int n,m;
int a[1000010],b[1000010];
class node{public:int tag,val;}ts[1000010<<2];
int P[1000010];
int bit[1000010],c[1000010],cnt=0;
inline void pd(int x){	
	if(ts[x].tag==0)return;
	ts[x<<1].val+=ts[x].tag;
	ts[x<<1].tag+=ts[x].tag;
	ts[x<<1|1].val+=ts[x].tag;
	ts[x<<1|1].tag+=ts[x].tag;
	ts[x].tag=0;
}
void build(int x,int l,int r){
	if(l==r){
		ts[x].val=ts[x].tag=0;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	ts[x].val=ts[x].tag=0;
}
void upd(int x,int l,int r,int cl,int cr,int val){
	if(l==cl&&r==cr){
		if(l!=r)pd(x);
		ts[x].val+=val;
		ts[x].tag+=val;
		return;
	}
	pd(x);
	int mid=(l+r)>>1;
	if(cr<=mid)upd(x<<1,l,mid,cl,cr,val);
	else if(mid+1<=cl)upd(x<<1|1,mid+1,r,cl,cr,val);
	else{
		upd(x<<1,l,mid,cl,mid,val);
		upd(x<<1|1,mid+1,r,mid+1,cr,val);
	}
	ts[x].val=min(ts[x<<1].val,ts[x<<1|1].val);
}
int qry(int x,int l,int r,int pos){
	if(l==r)return ts[x].val;
	pd(x);
	int mid=(l+r)>>1;
	if(pos<=mid)return qry(x<<1,l,mid,pos);
	else return qry(x<<1|1,mid+1,r,pos);
}
int upd(int i){
	while(i){
		bit[i]++;
		i-=i&-i;
	}
}
int qry(int i){
	int res=0;
	while(i<=n){
		res+=bit[i];
		i+=i&-i;
	}
	return res;
}
void init(){
	for(int i=0;i<=n;i++)bit[i]=0;
}
void solve(){
	init();
	n=read();m=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<m;i++)b[i]=read();
	sort(b,b+m);
	vector<pair<int,int> >v;
	for(int i=0;i<n;i++)v.push_back(make_pair(a[i],i));
	sort(v.begin(),v.end());
	build(1,0,n);
	for(int i=0;i<(int)v.size();i++){
		int pos=v[i].second;
		upd(1,0,n,pos+1,n,1);
	}
	int p1=0,p2=0;
	while(p1<(int)v.size()&&v[p1].first<b[0]){
		upd(1,0,n,0,v[p1].second,1);
		p1++;
	} 
	while(p2<(int)v.size()&&v[p2].first<=b[0]){
		upd(1,0,n,v[p2].second+1,n,-1);
		p2++;
	}
	long long ans=0;
	ans+=ts[1].val;
	for(int i=1;i<m;i++){
		while(p1<(int)v.size()&&v[p1].first<=b[i]-1){
			upd(1,0,n,0,v[p1].second,1);
			p1++;
		}
		while(p2<(int)v.size()&&v[p2].first<=b[i]){
			upd(1,0,n,v[p2].second+1,n,-1);
			p2++;
		}
		ans+=ts[1].val;
	}
	cnt=0;
	for(int i=0;i<(int)v.size();i++)c[cnt++]=v[i].first;
	sort(c,c+cnt);
	cnt=unique(c,c+cnt)-c;
	for(int i=0;i<n;i++){
		int id=lower_bound(c,c+cnt,a[i])-c;
		ans+=qry(id+2);
		upd(id+1);
	}
	print(ans);
	putchar('\n');
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
/*inline? ll or int? size? min max?*/
/*
1
3 3
3 2 1
1 2 3
*/
```

#### sol2

考虑分治 .

$solve(l_1,r_1,l_2,r_2)$ 处理出 $a$ 的区间 $[l_1,r_1]$ ，$b$ 的值域在 $[l_2,r_2]$ 的最小逆序对数 .

因为每个 $b$ 都能取到最优的最小位置 .

令 $mid=\lfloor \frac{l_2+r_2}{2}\rfloor$ .

考虑 $b_{mid}$ 在区间 $a$ 的 $[l_1,r_1]$ 中的位置，可以 $O(r_1-l_1)$ 地计算出 ，钦定为位置 $p$ .

那么，分治成 $solve(l_1,p,l_2,mid)$ 和 $solve(p,r_1,mid,r_2)$ .

递归 $\log n$ 层 .

时间复杂度 : $O(n\log n)$

空间复杂度 : $O(n)$


```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(long long res){
	if(res==0){
		putchar('0');
		return;
	}
	int a[20],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)
		putchar(a[i]+'0');
}
const int inf=1e9+10;
int t;
int n,m;
int a[1000010],b[1000010];
vector<int>v[1000010];
int cnt1[1000010],cnt2[1000010];
int bit[2000010],c[2000010],cnt=0;
void init(){
	for(int i=0;i<=n;i++)v[i].clear();
	for(int i=0;i<=cnt;i++)bit[i]=0;
	cnt=0;
}
void solve(int lb,int rb,int la,int ra){
	for(int i=la;i<=ra;i++)cnt1[i]=cnt2[i]=0;
	int mid=(lb+rb)>>1;
	for(int i=la;i<=ra-1;i++){
		if(a[i]>b[mid])cnt1[i+1]++;
		if(a[i]<b[mid])cnt2[i]++;
	}
	for(int i=ra-1;i>=la;i--)cnt2[i]+=cnt2[i+1];
	for(int i=la+1;i<=ra;i++)cnt1[i]+=cnt1[i-1];
	int mn=inf;
	for(int i=la;i<=ra;i++)mn=min(mn,cnt1[i]+cnt2[i]);
	for(int i=la;i<=ra;i++){
		if(cnt1[i]+cnt2[i]==mn){
			v[i].push_back(b[mid]);
			if(lb<=mid-1)solve(lb,mid-1,la,i);
			if(mid+1<=rb)solve(mid+1,rb,i,ra);
			return;
		}
	}
}
int upd(int i){
	while(i){
		bit[i]++;
		i-=i&-i;
	}
}
int qry(int i){
	int res=0;
	while(i<=cnt){
		res+=bit[i];
		i+=i&-i;
	}
	return res;
}
void solve(){
	init();
	n=read();m=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<m;i++)b[i]=read();
	sort(b,b+m);
	solve(0,m-1,0,n);
	for(int i=0;i<n;i++)c[cnt++]=a[i];
	for(int i=0;i<m;i++)c[cnt++]=b[i];
	sort(c,c+cnt);
	cnt=unique(c,c+cnt)-c;
	long long ans=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<(int)v[i].size();j++){
			int id=lower_bound(c,c+cnt,v[i][j])-c;
			ans+=qry(id+2);
		}
		for(int j=0;j<(int)v[i].size();j++){
			int id=lower_bound(c,c+cnt,v[i][j])-c;
			upd(id+1);
		}
		if(i<n){
			int id=lower_bound(c,c+cnt,a[i])-c;
			ans+=qry(id+2);
			upd(id+1);
		}
	}
	print(ans);
	putchar('\n');
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
/*inline? ll or int? size? min max?*/
/*
1
5 8
1 3 2 4 3
8 2 3 4 2 3 2 1
*/
```
写在最后，也可以去我的cnblog看一看哦
[link](https://www.cnblogs.com/suadwm/p/15509811.html)

---

## 作者：Alex_Wei (赞：8)

> CF1601C. [Optimal Insertion](https://www.luogu.com.cn/problem/CF1601C) *2300

首先一个结论是插入的 $b$ 一定有序，调整法可证。那么从小到大考虑所有 $b$，贪心地选择最优位置，因为$b_i$ 之间互不影响。预处理出 $p_i\ (i\in [0,n])$ 表示将 $b_1$ 插入位置 $i$ 后面的代价，考虑从 $b_i$ 变化至 $b_{i+1}$ 的过程会产生什么影响：所有位置 $j$ 满足 $b_i\leq a_j<b_{i+1}$ 的 $j$ 对前缀 $0\sim j-1$ 有 $+1$ 的贡献；所有位置 $j$ 满足 $b_i<a_j\leq b_{i+1}$ 的 $j$ 对后缀 $j\sim n$ 有 $-1$ 的贡献，可以线段树维护区间加并求全局最小值。时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
ll n,m,a[N],b[N],c[N],d[N],e[N],id[N],ans;
struct BIT{
	int c[N];
	void add(int x){while(x<=n)c[x]++,x+=x&-x;}
	int query(int x){int s=0;while(x)s+=c[x],x-=x&-x;return s;}
}tr;
struct SegTree{
	int laz[N<<2],val[N<<2];
	void build(int l,int r,int x){
		if(l==r)return val[x]=d[l],void();
		int m=l+r>>1;
		build(l,m,x<<1),build(m+1,r,x<<1|1);
		val[x]=min(val[x<<1],val[x<<1|1]);
	}
	void push(int x){
		if(laz[x]){
			val[x<<1]+=laz[x],val[x<<1|1]+=laz[x];
			laz[x<<1]+=laz[x],laz[x<<1|1]+=laz[x],laz[x]=0; 
		}
	}
	void modify(int l,int r,int ql,int qr,int x,int v){
		if(ql<=l&&r<=qr)return val[x]+=v,laz[x]+=v,void();
		int m=l+r>>1; push(x);
		if(ql<=m)modify(l,m,ql,qr,x<<1,v);
		if(m<qr)modify(m+1,r,ql,qr,x<<1|1,v);
		val[x]=min(val[x<<1],val[x<<1|1]);
	}
}tr2;
void solve(){
	n=read(),m=read(),mem(tr.c,0,n+5),d[0]=e[n+1]=0;
	mem(tr2.laz,0,n+5<<2),mem(tr2.val,0,n+5<<2),ans=0;
	for(int i=1;i<=n;i++)a[i]=read(),c[i]=a[i],id[i]=i;
	for(int i=1;i<=m;i++)b[i]=read();
	sort(c+1,c+n+1),sort(b+1,b+m+1);
	sort(id+1,id+n+1,[](int x,int y){return a[x]<a[y];});
	for(int i=1;i<=n;i++)a[i]=lower_bound(c+1,c+n+1,a[i])-c;
	for(int i=1;i<=n;i++)ans+=i-1-tr.query(a[i]),tr.add(a[i]);
	for(int i=1;i<=n;i++)a[i]=c[a[i]];
	for(int i=1;i<=n;i++)d[i]=d[i-1]+(a[i]>b[1]);
	for(int i=n;i;i--)e[i]=e[i+1]+(a[i]<b[1]),d[i-1]+=e[i];
	tr2.build(0,n,1); int p1=1,p2=1;
	while(p1<=n&&a[id[p1]]<=b[1])p1++;
	while(p2<=n&&a[id[p2]]<b[1])p2++;
	for(int i=1;i<m;i++){
		ans+=tr2.val[1];
		while(p1<=n&&a[id[p1]]<=b[i+1])tr2.modify(0,n,id[p1],n,1,-1),p1++;
		while(p2<=n&&a[id[p2]]<b[i+1])tr2.modify(0,n,0,id[p2]-1,1,1),p2++;
	}
	cout<<ans+tr2.val[1]<<endl;
}
```

---

## 作者：天梦 (赞：3)

这个题其实并不是很难，但是看了题解才恍然大悟。我们发现，$b$ 一定是一个升序的数组，所以逆序对个数一定出自 $a,b$ 两个序列之间以及 $a$ 序列内部。$a$ 序列内部的逆序对已经确定了，我们考虑两个序列之间的怎么算。

我们考虑 $b$ 中的每个元素放进 $a$ 中时是独立的，且位置是递增的，所以我们可以直接扫一遍，然后用树状数组维护逆序对，但这样实现难度较大。

我们考虑用分治，先解决中间，然后再做两边，同时维护值域，这样就可以做完了，复杂度 $(n+m)\log n$，最后用树状数组统计答案。

代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define int long long
#define uint unsigned int
#define ull unsigned long long
#define N 1000100
#define M number
using namespace std;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int posi[N],a[N],b[N],n,m,c[N<<1],tail,t,Pre[N],Suf[N];

struct BIT{
    int p[N<<1];
    inline int lowbit(int x){return x&(-x);}
    inline void PreAdd(int w,int x){
        for(int i=w;i<=tail;i+=lowbit(i)) p[i]+=x;
    }
    inline int PreAsk(int w){
        int res=0;for(int i=w;i>=1;i-=lowbit(i)) res+=p[i];return res;
    }
    inline void SufAdd(int w,int x){
        for(int i=w;i>=1;i-=lowbit(i)) p[i]+=x;
    }
    inline int AskSuf(int w){
        int res=0;for(int i=w;i<=tail;i+=lowbit(i)) res+=p[i];return res;
    }
    inline void Clear(int n){
        for(int i=1;i<=n;i++) p[i]=0;
    }
}bit;

inline void Init(){
    read(n);read(m);
    for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=m;i++) read(b[i]);
    for(int i=1;i<=n;i++) c[++tail]=a[i];
    for(int i=1;i<=m;i++) c[++tail]=b[i];
    sort(c+1,c+tail+1);int len=unique(c+1,c+tail+1)-c-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(c+1,c+len+1,a[i])-c;
    for(int i=1;i<=m;i++) b[i]=lower_bound(c+1,c+len+1,b[i])-c;
    sort(b+1,b+m+1);a[n+1]=INF;
}

inline void Solve(int l,int r,int Rl,int Rr){
    if(r<l) return;
    int mid=(l+r)>>1;
    Pre[Rl]=0;
    for(int i=Rl+1;i<=Rr;i++){
        Pre[i]=Pre[i-1];
        if(a[i-1]>b[mid]) Pre[i]++;
    }
    Suf[Rr]=0;
    for(int i=Rr-1;i>=Rl;i--){
        Suf[i]=Suf[i+1];
        if(b[mid]>a[i]) Suf[i]++;
    }
    int minn=INF,minp=-1;
    for(int i=Rl;i<=Rr;i++){
        if(minn>Pre[i]+Suf[i]){
            minn=Pre[i]+Suf[i];
            minp=i;
        }
    }
    posi[mid]=minp;
    Solve(l,mid-1,Rl,minp);
    Solve(mid+1,r,minp,Rr);
}

inline int GetAns(){
    // for(int i=1;i<=m;i++) printf("%d ",posi[i]);puts("");
    int now=0,ans=0;
    for(int i=1;i<=m;i++){
        while(now<posi[i]-1){
            now++;
            bit.SufAdd(a[now],1);
        }
        ans+=bit.AskSuf(b[i]+1);
    }
    // printf("ans=%d\n",ans);
    bit.Clear(tail);
    now=n+1;
    for(int i=m;i>=1;i--){
        while(now>posi[i]){
            now--;
            bit.PreAdd(a[now],1);
        }
        ans+=bit.PreAsk(b[i]-1);
    }
    // printf("ans=%d\n",ans);
    bit.Clear(tail);
    for(int i=n;i>=1;i--){
        ans+=bit.PreAsk(a[i]-1);
        bit.PreAdd(a[i],1);
    }
    // printf("ans=%d\n",ans);
    bit.Clear(tail);
    tail=0;
    return ans;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        Init();Solve(1,m,1,n+1);
        printf("%lld\n",GetAns());
    }
    return 0;
}
```

## 

---

## 作者：二gou子 (赞：3)

## Sol

看到有大佬写了堆的奇妙做法，但是并没看懂，所以就写了题解的分治做法。

首先其实很容易想到一个结论：$b$ 的位置随值的增加递增。原因也很显然，设 $p[i]$ 为 $b[i]$ 的位置，即 $b[i]$ 在 $a[p[i]]$ 之前。那么如果存在 $b[i]<b[j],p[i]>p[j]$ ，那么交换 $p[i],p[j]$ 一定不会使答案更劣，这个比较显然也没法证明。

有了上面那个结论，很自然可以想到先把 $b$ 按照升序排序，然后根据经验，我们可以根据前面求出的答案从而快速求出后面的答案。所以无非就只有两种做法：递推和分治。

官方题解就是采用了分治的思想：设一个函数 $solve(Lb,Rb,La,Ra)$ ，表示当前我们处理的区间为 $a$ 数组中的 $[La,Ra]$ ，$b$ 数组中的 $[Lb,Rb]$ 。然后我们先确定 $p[mid]$ 的值，也就是 $\frac{Lb+Rb}{2}$ 的位置。$p[mid]$ 的位置就限定在 $[La,Ra]$ 中。

由于我们已经确定了 $b[mid]$ 的值，所以在 $[La,Ra]$ 的区间内找到最佳位置的时间复杂度就是 $O(Ra-La)$ ，只要扫一遍即可。当我们确定了 $b[mid]$ 的位置，再接着往下处理左右两边，即 $solve(Lb,mid-1,La,p[mid]),solve(mid+1,Rb,p[mid],Ra)$ 。

我们发现最多递归 $\log m$ 层，每一层的复杂度是 $O(n)$ 。再加上离散化和最后插好的数组求逆序对，总时间复杂度 $O((n+m)\log (n+m))$ 。这个分治的精髓就是通过限定在 $a$ 数组中的位置从而减小时间复杂度，思想还是很妙的。

## Code

代码有一点细节，就是 $n$ 个数是有 $n+1$ 个空可以插的，所以一开始递归的初始化边界是 $1,n+1$ ，中间计算的时候也要注意这一点

```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e6+5;
int T,n,m,tot,cnt;
int a[N],b[N],A[N],c[N],li[N],p[N];
void lisan(){
	sort(li+1,li+1+tot);
	cnt=unique(li+1,li+1+tot)-li-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(li+1,li+1+cnt,a[i])-li;
	for(int i=1;i<=m;i++) b[i]=lower_bound(li+1,li+1+cnt,b[i])-li;
}
int lowbit(int x){
	return x&(-x);
}
void upd(int x){
	for(;x<=cnt;x+=lowbit(x)) c[x]++;
}
ll qry(int x){
	ll summ=0;
	for(;x;x-=lowbit(x)) summ+=c[x];
	return summ;
}
ll calc(){
	ll summ=0;
	for(int i=1;i<=tot;i++){
		summ+=qry(cnt)-qry(A[i]);
		upd(A[i]);
	}
	return summ;
}
void solve(int Lb,int Rb,int La,int Ra){
	if(Lb>Rb) return;
	int mid=(Lb+Rb)>>1;
	int val=b[mid];	
	int minn=2e9,summ1=0,summ2=0;
	
	for(int i=Ra-1;i>=La;i--){
		if(a[i]<val) summ2++;
	}
	minn=summ2;p[mid]=La;
	for(int i=La+1;i<=Ra;i++){
		if(a[i-1]<val) summ2--;
		if(a[i-1]>val) summ1++;
		if(summ1+summ2<minn){
			minn=summ1+summ2;
			p[mid]=i;
		}
	}
	

	solve(Lb,mid-1,La,p[mid]);
	solve(mid+1,Rb,p[mid],Ra);
}
int main()
{
	scanf("%d",&T);
	while(T--){
		tot=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			li[++tot]=a[i];
		}
		for(int i=1;i<=m;i++){
			scanf("%d",&b[i]);
			li[++tot]=b[i];
		}
		
		sort(b+1,b+1+m);
		
		lisan();
		
		for(int i=1;i<=cnt;i++) c[i]=0;
		
		solve(1,m,1,n+1);
		
		tot=0;
		int nowb=1;
		for(int i=1;i<=n;i++){
			while(p[nowb]==i&&nowb<=m){
				A[++tot]=b[nowb];
				nowb++;
			}
			A[++tot]=a[i];
		}
		while(nowb<=m){
			A[++tot]=b[nowb];
			nowb++;
		}
		
		printf("%lld\n",calc());
	}
	return 0;
}
```

---

## 作者：摸鱼酱 (赞：2)

考虑是把 $b$ 里的元素任意插到 $a$ 序列中，则 $b$ 序列插入的相对位置一定是小的在前，大的在后，否则交换则可以减少至少一对逆序对，则 $b$ 的插入只会和 $a$ 中元素构成逆序对。

两个序列一起离散化后先计算 $a$ 中逆序对，然后对 $a$ 序列建立线段树，枚举指针 $v$，$<v$ 的设为 $1$，否则设为 $0$，那么在 $pos$ 后插入 $v$ 的花费就是 $[1,pos]$ 中 $1$ 的个数加上 $(pos,n]$ 中 $0$ 的个数，记为 $d_{pos}$，我们要求的就是把 $v$ 移到 $b_i$ 后最小的 $d_{pos}$，线段树也实际维护的是 $d_{0\cdots pos}$。

实际上把 $p$ 位置的 $0$ 改为 $1$ 对应的就是给 $[p,n]$ 减一，$[0,p)$ 加一。注意特殊处理一下相等的情况即可。

时间复杂度 $O(m\log n)$。

[code](https://codeforces.com/contest/1601/submission/133017168)。

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2300}$
---
### 解题思路：

大概可以从两个角度出发。

#### 数据结构

对于只存在大小关系的情况，可以直接考虑离散化。之后就发现这里面一共只有 $O(n)$ 个“关键数值”了。

对于一个特定的 $b$ 计算贡献，考虑某一个时刻将 $b$ 向后交换一个位置，发现如果被交换的数 $k$ 比 $b$ 小则产生 $-1$ 的贡献，比 $b$ 大则产生 $1$ 的贡献，相等不会变化。对于这个变化量求一个前缀和就能得到每一个位置上的结果。

若 $b$ 产生变化，需要对于每一个变化的位置进行更改。每一次求结果则需要对于所有前缀和求最小值。

直接随便用个什么数据结构维护一下就好了。

#### 分治

观察到 $b$ 是随意插入 $a$ 的，不妨让 $b$ 从小到大排序，很容易感觉到 $b$ 在从小到大的顺序的情况下，插入的顺序应当是递增的。 

然后发现对于一个 $b_i$，它的最佳位置和其它的所有 $b_i$ 之间是无关的。每一次算出对于 $b_L$ 到 $b_R$ 之间所有值的插入位置都应当在 $a_l$ 到 $a_r$ 之间，求出中间的一个位置的位置就能一下子缩小一半的范围了。

复杂度都是 $O(n\log n)$ 的。


---

## 作者：syzf2222 (赞：1)

结论1：$b$ 应排序后顺序插入。正确性显然。

结论2：每次贪心地选择最优位置放入。正确性可以感性理解。

这样的话，我们只需要维护一个线段树，类似于扫描线，我们从小到大考虑 $b_i$ ，发现要把它放在它前面大的减小的最小的地方。

于是我们令 $a_i<b_j$ 的 $i$ 的值为 $-1$， $a_i=b_j$ 的值为 $0$ ，大于的值为 $1$，每次后缀修改，区间查询最小值即可。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e6+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int T,n,m,a[maxn],b[maxn],c[maxn],id[maxn],fw[maxn];
long long ans;vector<int>v[maxn];int cur[maxn];
#define pii pair<int,int>
#define fi first
#define se second
#define mkp make_pair
#define pb push_back
struct node{int laz;pii val;}tr[maxn<<2];
inline void build(int h,int l,int r){
	tr[h].laz=0;int mid=(l+r)>>1;
	if(l==r)return void(tr[h].val=mkp(l,l));
	build(h<<1,l,mid);build(h<<1|1,mid+1,r);
	tr[h].val=min(tr[h<<1].val,tr[h<<1|1].val);
}
inline void pushup(int h,int z){
	tr[h].laz+=z;tr[h].val.fi+=z;
}
inline void pushdown(int h){
	if(!tr[h].laz)return;
	pushup(h<<1,tr[h].laz);
	pushup(h<<1|1,tr[h].laz);
	tr[h].laz=0;
}
inline void modify(int h,int l,int r,int x,int y,int z){
	if(l>y||r<x)return;
	if(l>=x&&r<=y)return void(pushup(h,z));
	pushdown(h);int mid=(l+r)>>1;
	modify(h<<1,l,mid,x,y,z);
	modify(h<<1|1,mid+1,r,x,y,z);
	tr[h].val=min(tr[h<<1].val,tr[h<<1|1].val);
}
inline void change(int x,int y){
	if(cur[x]==y)return;
	for(int i=0;i<v[x].size();i++)
		modify(1,0,n,v[x][i],n,y-cur[x]);
	cur[x]=y;
}
inline pii query(int h,int l,int r,int x,int y){
	if(l>y||r<x)return mkp(n+1,n+1);
	if(l>=x&&r<=y)return tr[h].val;
	pushdown(h);int mid=(l+r)>>1;
	return min(query(h<<1,l,mid,x,y),query(h<<1|1,mid+1,r,x,y));
}
inline void work(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=c[i]=read();
	for(int i=1;i<=m;i++)
		b[i]=c[n+i]=read();
	sort(c+1,c+1+n+m);
	int tot=unique(c+1,c+1+n+m)-c-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(c+1,c+1+tot,a[i])-c;
	for(int i=1;i<=m;i++)
		b[i]=lower_bound(c+1,c+1+tot,b[i])-c;
	sort(b+1,b+1+m);ans=0;
	for(int i=1;i<=n+m;i++)fw[i]=0;
	for(int i=n;i;--i){
		for(int j=a[i]-1;j;j-=j&(-j))ans+=fw[j];
		for(int j=a[i];j<=tot;j+=j&(-j))++fw[j];
	}
	for(int i=1;i<=m;i++)
		for(int j=b[i]-1;j;j-=j&(-j))ans+=fw[j];
	build(1,0,n);
	for(int i=1;i<=n;i++)
		v[a[i]].pb(i),cur[a[i]]=1;
	for(int i=1,las=1,lst=0;i<=m;i++){
		while(las<b[i])change(las,-1),++las;
		change(b[i],0);pii res=query(1,0,n,lst,n);ans+=res.fi;lst=res.se;
	}printf("%lld\n",ans);
	for(int i=1;i<=tot;i++)v[i].clear();
}
int main(){
	T=read();
	while(T--)work();
    return 0;
}
```

深深地感到自己的弱小。

---

## 作者：Prean (赞：1)

> 赛时一小时，赛后十分钟。

题意：给定一个序列 $ a $ 和一个集合 $ b $，问将 $ b $ 中所有元素插入 $ a $ 后逆序对最少是多少。

观察样例解释，发现 $ b $ 已经被排序过了，于是就猜想一个结论：

设排序后 $ b_i $ 在 $ x_i-1 $ 和 $ x_i $ 之间被插入，那么对于 $ i < j $ 时一定有 $ x_i \leq x_j $。

证明：邻项交换，假如交换两个相邻元素，相当于令 $ b_i $ 变大，$ b_j $ 变小，这样一来 $ x_i $ 右边的元素对 $ b_i $ 的贡献就变大了，$ x_j $ 左边的元素同理。

于是将 $ b $ 排序后依次插入 $ a $。考虑在线地插入 $ b $。那么对于 $ a $ 上的每一个位置得维护当前左边比该元素大的个数和当前右边比该元素小的个数。

由于已经将 $ b $ 排序了，所以可以考虑维护 $ s_i $ 表示 $ [1,i) $ 比当前的 $ b $ 大的元素个数与 $ [i,n] $ 不大于当前 $ b $ 的元素个数之和。将 $ a $ 也排序即可。

这样就可以动态地统计答案了。
```cpp
#include<algorithm>
#include<cstdio>
const int M=1e6+5;
int T,n,m,t,a[M],b[M],id[M],mi[M*21];int len,lsh[M<<1];int tim[M*21],tag[M*21];
inline void upd(const int&u,const int&id){
	tim[u]^t&&(mi[u]=id-1,tim[u]=t,tag[u]=0);
}
inline void update(const int&u){
	mi[u]=mi[u<<1|mi[u<<1]>mi[u<<1|1]];
}
inline void pushdown(const int&u,const int&L,const int&R){
	if(!tag[u])return;upd(u<<1,L);upd(u<<1|1,(L+R>>1)+1);
	mi[u<<1]+=tag[u];mi[u<<1|1]+=tag[u];tag[u<<1]+=tag[u];tag[u<<1|1]+=tag[u];tag[u]=0;
}
void Modify(const int&u,const int&l,const int&r,const int&val,const int&L=1,const int&R=n+1){
	if(upd(u,L),l>R||L>r)return;if(l<=L&&R<=r)return mi[u]+=val,tag[u]+=val,void();pushdown(u,L,R);
	int mid=L+R>>1;Modify(u<<1,l,r,val,L,mid);Modify(u<<1|1,l,r,val,mid+1,R);update(u);
}
namespace BIT{
	int t,tim[M<<1],sum[M<<1];
	inline void Add(int x){
		for(;x<=len;x+=x&-x)tim[x]^t&&(sum[x]=0,tim[x]=t),++sum[x];
	}
	inline int Query(int x){
		int ans(0);
		for(;x>=1;x-=x&-x)tim[x]^t&&(sum[x]=0,tim[x]=t),ans+=sum[x];
		return ans;
	}
}
signed main(){
	int i,x,y;long long sum;scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);++t;++BIT::t;sum=len=0;x=y=1;
		for(i=1;i<=n;++i)scanf("%d",a+i),lsh[++len]=a[id[i]=i];
		for(i=1;i<=m;++i)scanf("%d",b+i),lsh[++len]=b[i];std::sort(b+1,b+m+1);
		std::sort(id+1,id+n+1,[](const int&x,const int&y){return a[x]<a[y];});
		std::sort(lsh+1,lsh+len+1);len=std::unique(lsh+1,lsh+len+1)-lsh-1;
		for(i=1;i<=n;++i)a[i]=std::lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
		for(i=1;i<=m;++i)b[i]=std::lower_bound(lsh+1,lsh+len+1,b[i])-lsh;
		for(i=n;i>=1;--i)sum+=BIT::Query(a[i]-1),BIT::Add(a[i]);mi[1]=0;
		for(i=1;i<=m;++i){
			while(a[id[x]]<b[i]&&x^n+1)Modify(1,1,id[x++],1);
			while(a[id[y]]<=b[i]&&y^n+1)Modify(1,id[y++]+1,n+1,-1);sum+=mi[1];
		}
		printf("%lld\n",sum);
	}
}
```

---

## 作者：JerryZiruiZhang (赞：0)

提供一个线段树解法。

离散化后，对于一个数 $b_i$ 对于大于它的每个数 $a_i$，将区间 $[i+1,n]$ $+1$，否则将 $[1,i-1]$ $-1$，求最小值即可。

非常显然，这可以用线段树维护。

具体实现可以把 $b$ 中的元素排序，用双指针扫一遍。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 2e6 + 10;
struct UPD { int a, pos; } sta[maxn]; int top = 0;
int n, m;
int a[maxn], b[maxn], t[maxn << 1];
int mn[maxn << 2], lz[maxn << 2];
inline void pushup(int id) { mn[id] = min(mn[id << 1], mn[id << 1 | 1]); }
inline void change (int id, int v) {
	lz[id] += v;
	mn[id] += v;
}
inline void pushdown(int id) {
	if(lz[id]) {
		change(id << 1, lz[id]);
		change(id << 1 | 1, lz[id]);
		lz[id] = 0;
	}
}
inline void update(int id, int l, int r, int x, int y, int v) {
	if(x <= l && r <= y) {
		change(id, v);
		return; 
	}
	pushdown(id);
	int mid = (l + r) >> 1;
	if(x <= mid) update(id << 1, l, mid, x, y, v);
	if(y > mid) update(id << 1 | 1, mid + 1, r, x, y, v);
	pushup(id);
}
bool cmp (UPD A, UPD B) { return A.a < B.a; }
int mm;
inline void init() {
	scanf("%d%d", &n, &m);
	int cnt = 0;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]), t[++cnt] = a[i];
	for(int i = 1; i <= m; i++) scanf("%d", &b[i]), t[++cnt] = b[i];
	sort(t + 1, t + cnt + 1);
	mm = unique(t + 1, t + cnt + 1) - t - 1;
	for(int i = 1; i <= n; i++) a[i] = lower_bound(t + 1, t + mm + 1, a[i]) - t;
	for(int i = 1; i <= m; i++) b[i] = lower_bound(t + 1, t + mm + 1, b[i]) - t;
	top = 0;
	for(int i = 1; i <= n; i++) sta[++top].a = a[i], sta[top].pos = i;
	sort(sta + 1, sta + top + 1, cmp);
}
ll c[maxn << 1];
inline void upd(int x, int v) { for(int i = x; i <= mm + 1; i += (i & (-i))) c[i] += v; }
inline ll qur(int x) { ll res = 0; for(int i = x; i > 0; i -= (i & (-i))) res += c[i]; return res; }
inline ll init_ans(int mm) {
	ll ans = 0;
	for(int i = 1; i <= n; i++) {
		ans += i - 1 - qur(a[i]);
		upd(a[i], 1);
	}
	for(int i = 1; i <= n; i++) {
		upd(a[i], -1);
	} 
	return ans;
}
inline ll work(ll ans) {
	for(int i = m + 1; i <= m + 10; i++) b[i] = 0;
	sort(b + 1, b + m + 1);
	for(int i = 1; i <= n; i++) update(1, 1, n + 1, i + 1, n + 1, +1);
	for(int i = 1, j = 1; i <= top, j <= m; j++) {
		while(i <= top && sta[i].a < b[j]) {
			update(1, 1, n + 1, sta[i].pos + 1, n + 1, -1);
			update(1, 1, n + 1, 1, sta[i].pos, +1);
			i++;
			if(i > top) break;
		}
		int ii = i, val = b[j];
		while(i <= top && sta[i].a == val) {
			update(1, 1, n + 1, sta[i].pos + 1, n + 1, -1);
			i++;
			if(i > top) break;
		}
		ans += mn[1];
		while(b[j] == b[j + 1]) j++, ans += mn[1];
		while(ii <= top && sta[ii].a == val) {
			update(1, 1, n + 1, 1, sta[ii].pos, +1);
			ii++;
			if(ii > top) break;
		}
	}
	for(int i = 1; i <= ((n + 1) << 2); i++) mn[i] = lz[i] = 0;
	return ans;
}
int main () {
	int C03; scanf("%d", &C03);
	while(C03--) {
		init();
		ll ans = init_ans(mm);
		printf("%lld\n", work(ans));
	}
	return 0;
}

```

---

