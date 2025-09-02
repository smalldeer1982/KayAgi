# Cool loves touli

## 题目背景

Cool 一直都很崇拜 touli。


## 题目描述

有一天 Cool 和 touli 在打多校，突然开始讨论怎么样的阵容比较厉害。Cool 觉得一个阵容，将他们的等级从低到高排序后，攻击力应该是递增的。Cool 就问 touli 这个阵容最多有几个人。

不过 touli 觉得这个问题实在太 SB，就改变了条件，他认为等级从低到高排序后，对于任意两个排序后相邻的英雄，等级低的英雄的攻击力应该不大于等级高的英雄的力量，等级高的英雄的攻击力应当不小于等级低的英雄的智力。

现在 Cool 想知道若干个英雄中，最多能选出多少个英雄加入阵容。

## 说明/提示

选择第 $1$ 个和第 $3$ 个英雄，符合条件。对于第 $1$ 个和第 $2$ 个英雄，第 $2$ 个英雄的攻击力小于第 $1$ 个英雄的智力，所以不能同时存在。

$n\leq 10^5$，$l,s,w,a\le10^8$，$l$ 互不相同。

## 样例 #1

### 输入

```
3
1 2 3 1
2 1 2 2
3 1 3 3```

### 输出

```
2```

# 题解

## 作者：spire001 (赞：7)

## P3364题解

### 题目大意
这个题的题面讲的十分清楚，只是你需要注意是什么大于什么，不然这种错误很不容易调试出来。

### 解题思路

这个题很模板，总结一下规律，解题流程是：
1. 写出偏序关系（状态转移方程）。
2. 打出暴力（熟练的话可以忽略）。
3. 套用 cdq 分治模板。
  
对于这个题，我们分别记题目中的等级、力量、智力、攻击力为 $a,b,c,d$。

那么等级从低到高排序保证了 $a$ 关键字重复不影响答案。
剩下的关系照着题目可以写出来，它们是 $i< j$，$d_i\le b_j$，$c_i\le d_j$。


然后就可以套用 cdq 分治优化 dp 模板了。


### AC代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define lowbit(x) (x & -(x))

using namespace std;

constexpr int N = 1e5 + 2;
constexpr int M = N * 3; // 离散化后三倍空间
int n, b[N << 2], ln, c[M], ans = 1;

struct node{
  int a, b, c, d, dp, id; // id 方便排序回初始状态
} a[N];

inline void add(const int x, const int val) { for (int i = x; i < M; i += lowbit(i)) c[i] = max(c[i], val); return; } // 树状数组
inline int ask(const int x) { int res = 0; for (int i = x; i; i &= i - 1) res = max(res, c[i]); return res; }
inline void clear(const int x) { for (int i = x; i < M; i += lowbit(i)) c[i] = 0; return; } // 清空树状数组
inline void fun(int &x) { x = lower_bound(b + 1, b + ln + 1, x) - b; return; } // 离散化

/*
i < j
ai <= aj
di <= bj
ci <= dj
偏序关系
*/

void cdq(int l, int r)
{
  if (l == r)
  {
    a[l].dp = max(a[l].dp, 1); // 这里取 max 而非直接赋值
    return;
  }

  const int mid = (l + r) >> 1;
  cdq(l, mid); 

  sort(a + l, a + mid + 1, [&](const node &A, const node &B) {
    return A.d < B.d;
  }); // 按照第二重偏序关系排序

  sort(a + mid + 1, a + r + 1, [&](const node &A, const node &B) {
    return A.b < B.b;
  }); // 按照第二重偏序关系排序

  int i = l, j = mid + 1;

  while (j <= r) // 双指针
  {
    while (i <= mid && a[i].d <= a[j].b)
    {
      add(a[i].c, a[i].dp); // 按照第三重偏序关系加入树状数组
      i++;
    }
    a[j].dp = max(a[j].dp, ask(a[j].d) + 1);
    // 按照第三重偏序关系更新答案
    ans = max(ans, a[j].dp); j++;
  }

  for (int p = l; p != i; p++) clear(a[p].c); // 清空树状数组

  sort(a + mid + 1, a + r + 1, [&](const node &A, const node &B) {
    return A.id < B.id;
  }); // 排序回原始状态

  cdq(mid + 1, r);

  return;
}
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n;

  for (int i = 1; i <= n; i++)
  {
    cin >> a[i].a >> a[i].b >> a[i].c >> a[i].d; 
    // b[++ln] = a[i].a; 
    b[++ln] = a[i].b; b[++ln] = a[i].c; b[++ln] = a[i].d; // 离散化
  }

  sort(b + 1, b + ln + 1); ln = unique(b + 1, b + ln + 1) - b - 1;

  for (int i = 1; i <= n; i++)
  {
    // fun(a[i].a); 
    fun(a[i].b); fun(a[i].c); fun(a[i].d);
  }

  sort(a + 1, a + n + 1, [&](const node &A, const node &B) {
    return A.a < B.a; // a 关键字直接排序可不需要离散化
  });

  for (int i = 1; i <= n; i++) a[i].id = i; // id 方便排序回去

  cdq(1, n);

  // for (int i = 1; i <= n; i++) cout << a[i].dp << ' ';
  
  cout << ans; // 对 dp 取 max 并输出答案

  return 0;
}

/*
begin: 2024年6月5日17:28:02
debug: 2024年6月5日18:23:49
finish: 2024年6月5日19:00:08
*/
```

---

## 作者：hgzxwzf (赞：5)

## 解题思路：
暴力 DP 很好想，先把所有的英雄排序，$dp_i$ 表示以第 $i$ 个英雄结尾选的最多的英雄，$dp_i=max(dp_j+1) (a_j \le s_i,w_j\le a_i)$。

转移要求 $l_j<l_i,a_j\le s_j,w_i\le a_j$。

诶！这不是三维偏序吗？用 cdq 分治维护！

如果你不知道什么是 cdq 分治，请前往[我的 cdq 分治笔记](https://www.luogu.com.cn/blog/Kok-kok/cdq-fen-zhi-xue-xi-bi-ji)。

处理区间 $[l,r]$ 时，首先把区间按 $l$ 从大到小排序，再把 $[l,mid]$ 按 $a$ 从小到大排序，$[mid+1,r]$ 按 $s$ 从小到大排序，这样就可以使用单指针扫描法了。

不过这题的分治方式和普通的 cdq 分治有所不同，我们要先去处理 $[l,mid]$，然后用 $[l,mid]$ 的答案更新 $[mid+1,r]$ 的答案，再去处理 $[mid+1,r]$，原因很简单，暴力时从左到右，这里也要从左到右，而不能先左右再合并。

## 代码：

```cpp
#include<cstdio>
#include<algorithm>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
#define LL long long
using namespace std;
const int N=1e5+10,M=4e5+10;
struct hero
{
	int l,s,w,a,dp;
}h[N];
bool comp1(const hero &P,const hero &Q) {return P.l<Q.l;}
bool comp2(const hero &P,const hero &Q) {return P.a<Q.a;}
bool comp3(const hero &P,const hero &Q) {return P.s<Q.s;}
int lis[M];
int t[M],tot;
inline void add(int i,int x) {while(i<=tot) t[i]=max(t[i],x),i+=i&-i;}
inline int query(int i) {int sum=0;while(i) sum=max(sum,t[i]),i-=i&-i;return sum;}
inline void clean(int i) {while(i<=tot) t[i]=0,i+=i&-i;}
void CDQ(int l,int r)
{
	if(l==r) return ;
	int mid=l+r>>1;
	sort(h+l,h+r+1,comp1);
	CDQ(l,mid);
	sort(h+l,h+mid+1,comp2);
	sort(h+mid+1,h+r+1,comp3);
	int L=l;
	rep(i,mid+1,r)
	{
		while(L<=mid&&h[L].a<=h[i].s) add(h[L].w,h[L].dp),L++;
		h[i].dp=max(h[i].dp,query(h[i].a)+1);
	}
	rep(i,l,L-1) clean(h[i].w);
	CDQ(mid+1,r);
}
int main()
{
	int n;
	scanf("%d",&n);
	rep(i,1,n)
	{
		scanf("%d%d%d%d",&h[i].l,&h[i].s,&h[i].w,&h[i].a);
		lis[++tot]=h[i].s,lis[++tot]=h[i].w,lis[++tot]=h[i].a;
	}
	sort(lis+1,lis+1+tot);
	tot=unique(lis+1,lis+1+tot)-lis-1;
	rep(i,1,n)
	{
		h[i].dp=1;
		h[i].w=lower_bound(lis+1,lis+1+tot,h[i].w)-lis;
		h[i].s=lower_bound(lis+1,lis+1+tot,h[i].s)-lis;
		h[i].a=lower_bound(lis+1,lis+1+tot,h[i].a)-lis;
	}
	CDQ(1,n);
	int ans=0;
	rep(i,1,n) ans=max(ans,h[i].dp);
	printf("%d",ans);
	return 0;
}
```


---

## 作者：moosssi (赞：4)

经典的cdq分治优化dp。

很容易地得到转移方程:$f[i]=max(f[j]+1,f[i])$ $(a_j<a_i,d_j\le b_i,c_j\le d_i)$。

直接套模板：把整个区间按照a关键字排序，递归处理左边。

左右区间分别按照d，b关键字排序，双指针枚举，用树状数组记录前缀最大值。

处理左右区间之间的数据，更新最大值，还原树状数组，递归处理右边。

最后记得把输入的离散化。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) -x&x
using namespace std;
const int N=3e5+5;
struct nod{
	int a,b,c,d,res;
}q[N];
int li[N],h,n;
int tr[N],ans;
bool cmp(nod x,nod y){return x.a<y.a;}
bool cmp1(nod x,nod y){return x.b<y.b;}
bool cmp2(nod x,nod y){return x.d<y.d;}
void add(int x,int v){
    for(int i=x;i<N;i+=lowbit(i)){
        tr[i]=max(v,tr[i]);
    }
}
int query(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i)){
        res=max(res,tr[i]);	
    }
    return res;
}
void clean(int x){
    for(int i=x;i<N;i+=lowbit(i)){
    	tr[i]=0;
    }
}
void merg_sort(int l,int r){
	if(l>=r)return ;
	int mid=(l+r)/2;
	sort(q+l,q+r+1,cmp);
	merg_sort(l,mid);
	sort(q+l,q+mid+1,cmp2);
	sort(q+mid+1,q+r+1,cmp1);
	int i=l,j=mid+1;
	while(i<=mid&&j<=r){
		if(q[i].d<=q[j].b)add(q[i].c,q[i].res),i++;
		else q[j].res=max(q[j].res,query(q[j].d)+1),j++;
	}
	while(i<=mid)add(q[i].c,q[i].res),i++;
	while(j<=r)q[j].res=max(q[j].res,query(q[j].d)+1),j++;
	for(int i=l;i<=mid;i++){
		clean(q[i].c);
	}
	sort(q+mid+1,q+r+1,cmp);
	merg_sort(mid+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&q[i].a,&q[i].b,&q[i].c,&q[i].d);
		li[++h]=q[i].b,li[++h]=q[i].c,li[++h]=q[i].d;
		q[i].res=1;
	}
	sort(li+1,li+h+1);
	h=unique(li+1,li+h+1)-li-1;
	for(int i=1;i<=n;i++){
		q[i].b=lower_bound(li+1,li+h+1,q[i].b)-li;
		q[i].c=lower_bound(li+1,li+h+1,q[i].c)-li;
		q[i].d=lower_bound(li+1,li+h+1,q[i].d)-li;	
	}
	sort(q+1,q+n+1,cmp);
	merg_sort(1,n);
	for(int i=1;i<=n;i++){
		ans=max(ans,q[i].res);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Yesod (赞：2)

### 前置知识 K-D Tree
DP 方程很好想在这就不提及，直接讲述 K-D Tree 优化过程，先将等级从小到大排序。发现转移条件是相邻两个英雄满足 $ a_j \le s_i , w_j \le a_i $ ，一个典型的偏序问题,将每个英雄抽象成一个平面的点 $ (w_i,a_i) $ 点值为 $ dp_i $ 每次转移就是在矩阵 $ [(-\infty , -\infty) , (a_i , s_i)] $ 内查找最大值，然后将最大值加1插入至该点内。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,z[N],q,po[2],po1[2],root,res,ans;
struct node{
	int x[2],z,mxz,mn[2],mx[2],l,r,fa;
}kd[N];
struct node1{
	int p,x,y,z;
}a[N];
bool cmp(node1 i,node1 j)
{
	return i.p<j.p;
}
bool cmp1(int i,int j)
{
	return kd[i].x[q]<kd[j].x[q];
}
inline void gx(int i)
{
	for(int j=0;j<2;++j)
	{
		kd[i].mn[j]=kd[i].mx[j]=kd[i].x[j];
		if(kd[i].l) kd[i].mn[j]=min(kd[kd[i].l].mn[j],kd[i].mn[j]),kd[i].mx[j]=max(kd[kd[i].l].mx[j],kd[i].mx[j]);
		if(kd[i].r) kd[i].mn[j]=min(kd[kd[i].r].mn[j],kd[i].mn[j]),kd[i].mx[j]=max(kd[kd[i].r].mx[j],kd[i].mx[j]);
	}
} 
int build(int l,int r,int id)
{
	if(l>r) return 0;
	int mid=(l+r)/2;
	q=id,nth_element(z+l,z+mid,z+r+1,cmp1);
	int k=z[mid];
	kd[k].l=build(l,mid-1,id^1),kd[k].r=build(mid+1,r,id^1);
	kd[kd[k].l].fa=kd[kd[k].r].fa=k;
	gx(k);
	return k;
}
void cz(int i)
{
	if(!i||res>=kd[i].mxz) return;
	int k=0;
	for(int j=0;j<2;++j) k|=(!(po[j]<=kd[i].mn[j]&&kd[i].mx[j]<=po1[j]));
	if(!k)
	{
		res=kd[i].mxz;
		return;
	}
	for(int j=0;j<2;++j) if(po[j]>kd[i].mx[j]||kd[i].mn[j]>po1[j]) return;
	k=0;
	for(int j=0;j<2;++j) k|=(!(po[j]<=kd[i].x[j]&&kd[i].x[j]<=po1[j]));
	if(!k)
		res=max(res,kd[i].z);
	cz(kd[i].l),cz(kd[i].r);
}
void pushup(int i)
{
	if(!i) return;
	kd[i].mxz=max(kd[kd[i].l].mxz,max(kd[i].mxz,kd[kd[i].r].mxz));
	pushup(kd[i].fa);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i].p>>a[i].x>>a[i].y>>a[i].z;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
		z[i]=i,kd[i]={a[i].y,a[i].z,0};
	root=build(1,n,0);//建树
	po[0]=-1e9,po[1]=-1e9;
	for(int i=1;i<=n;++i)
	{
		po1[0]=a[i].z;
		po1[1]=a[i].x;
		res=0;
		cz(root);//查询
		++res;
		kd[i].z=res;
		kd[i].mxz=max(kd[i].mxz,res);
		pushup(i);//插入点值
		ans=max(ans,res);
	}
	cout<<ans;
	return 0;
  }

---

## 作者：Saber_Master (赞：2)

[P3364 Cool loves touli](https://www.luogu.com.cn/problem/P3364)

$cdq$优化$dp$

转移条件者有三：

$$a_j<a_i$$

$$d_j\leq b_i$$

$$c_j \leq d_i$$

记得把$b,c,d$全部离散.

然后$cdq$维护一下即可.

还有就是记得及时排序.

```cpp
const ll N=3e5+5;

ll n;

struct node{
	ll a, b, c, d, res;
}q[N];
ll lsh[N], h;
namespace bit{
	ll f[N];
	inline void add(ll x, ll val){
		for (; x<=h; x+=x&-x) chkmax(f[x], val);
	}
	
	inline ll ask(ll x){
		ll res=0;
		for (; x; x-=x&-x) chkmax(res, f[x]);
		return res;
	}
	
	inline void del(ll x){
		for (; x<=h; x+=x&-x) f[x]=0;
	}
}

inline bool cmp1(node x, node y){
	return x.a<y.a;
}

inline bool cmp2(node x, node y){
	return x.b<y.b;
}

inline bool cmp3(node x, node y){
	return x.c<y.c;
}

inline bool cmp4(node x, node y){
	return x.d<y.d;
}


inline void cdq_solve(ll l, ll r){
	if (l==r) return (void)(chkmax(q[l].res, 1));
	ll mid=l+r>>1;
	stable_sort(q+l, q+r+1, cmp1);
	cdq_solve(l, mid);
	stable_sort(q+l, q+mid+1, cmp4);
	stable_sort(q+mid+1, q+r+1, cmp2);
	ll nowl=l, nowr=mid+1;
	while (nowr<=r){
		while (nowl<=mid && q[nowl].d<=q[nowr].b) bit::add(q[nowl].c, q[nowl].res), ++nowl;
		chkmax(q[nowr].res, bit::ask(q[nowr].d)+1);
		++nowr;
	}
	while (--nowl>=l) bit::del(q[nowl].c);
	cdq_solve(mid+1, r);
}

ll ans;
int main(){
	read(n);
	for (R ll i=1; i<=n; i++){
		read(q[i].a); read(q[i].b); read(q[i].c); read(q[i].d);
		lsh[++h]=q[i].b; lsh[++h]=q[i].c; lsh[++h]=q[i].d;
	}
	sort(lsh+1, lsh+h+1); h=unique(lsh+1, lsh+h+1)-lsh-1;
	for (R ll i=1; i<=n; i++){
		q[i].b=lower_bound(lsh+1, lsh+h+1, q[i].b)-lsh;
		q[i].c=lower_bound(lsh+1, lsh+h+1, q[i].c)-lsh;
		q[i].d=lower_bound(lsh+1, lsh+h+1, q[i].d)-lsh;
	}
	stable_sort(q+1, q+n+1, cmp1);
	cdq_solve(1, n);
	for (R ll i=1; i<=n; i++) chkmax(ans, q[i].res);
	writeln(ans);
}
```


---

## 作者：kczno1 (赞：2)

新学cdq分治，因为sort(l,r)时忘了写成sort(l,r+1)卡了很久。。。



```cpp
#include<bits/stdc++.h>
using namespace std;

void chmax(int &x,int y)
{
    if (x<y) x=y;
}

const int max_n=100000+5;
struct elem
{
    int a,b,c,f;
};
elem a[max_n],*now[max_n];
int i;

const int mtop=max_n*3;int top,num;
int c[mtop],*dy[mtop];

bool f_xiao(const elem &x,const elem &y)
{
    return x.f<y.f;
}
bool xiao(const elem &x,const elem &y)
{
    return x.a<y.a;
}
bool now_xiao(const elem *x,const elem *y)
{
    return x->b<y->b;
}

void jia(int i,int w)
{
    for (;w>c[i]&&i<=top;i+=i&(-i)) c[i]=w;
}
void clear(int i)
{
    for (;c[i]&&i<=top;i+=i&(-i)) c[i]=0;
}
int qiu(int &f,int i)
{
   for (;i;i-=i&(-i)) chmax(f,c[i]);
}

int j,low;
void cdq(int l,int r)
{
    if (l==r) return ;
    int mid=(l+r)>>1;
    cdq(l,mid);//先(l,mid)再考虑左对右的影响再考虑(mid+1,r)
                  //原因是用x更新y时必须保证x已经被完全更新
    
    sort(&a[l],&a[mid+1],xiao);//左边按a 
    for (i=mid+1;i<=r;++i) now[i]=&a[i];
    i=mid+1,j=l;
    sort(&now[i],&now[r+1],now_xiao);//右边按b 
    
    for (;i<=r;++i)
    {
        low=now[i]->b;//下界 
      for (;a[j].a<=low&&j<=mid;++j) //所有a<=low 加入 
        jia(a[j].c,a[j].f+1);//将f+1在c点加入 
      qiu(now[i]->f,now[i]->a);//用1-a前缀max更新f 
    }
    for (j=l;j<=mid;++j) clear(a[j].c);//消除影响 
    
    cdq(mid+1,r);
}

bool dy_xiao(int *x,int *y)
{
    return *x<*y;
}
int main()
{ freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int n;
    scanf("%d",&n);
    for (i=1;i<=n;++i) 
      scanf("%d%d%d%d",&a[i].f,&a[i].b,&a[i].c,&a[i].a);//题意即c[l]<=a[i]<=b[r]    
    sort(&a[1],&a[n+1],f_xiao);//按等级排序
    
        //对a,b,c一起进行离散
    for (i=1;i<=n;++i) 
    {
         a[i].f=0;
        dy[++num]=&a[i].a;dy[++num]=&a[i].b;dy[++num]=&a[i].c;
    }
    sort(&dy[1],&dy[num+1],dy_xiao);
    int now=1<<30;
    for (i=1;i<=num;++i) 
    {
     if (now!=*dy[i]) {++top;now=*dy[i];}
     *dy[i]=top;
        }

    cdq(1,n);
    int ans=a[1].f;
    for (i=2;i<=n;++i) chmax(ans,a[i].f);
    printf("%d",ans+1);
}
```

---

## 作者：koukilee (赞：1)

比较板的四维偏序。

根据题目，不难推出以下 $dp$ 转移式：

$$
dp_i = \max \limits_{l_j \le l_i,a_j \le s_i,w_j\le a_i} dp_j + 1
$$

先按照第一维排序，剩下的做一个三维偏序即可。

可以使用 K_D Tree 维护。

主要思考的地方在于查询。

如果 $x$ 整颗子树内的 $\max \limits_{y=son_x} a_y \le s_i$ 且 $\max \limits_{y=son_x} w_y \le a_i$，那么说明子树内的点都**可以**被选到，直接更新最大值即可返回。

如果 $x$ 整颗子树内的 $\min \limits_{y=son_x} a_y > s_i$ 或 $\min \limits_{y=son_x} w_y > a_i$，那么说明子树内的点都**不能**被选到，直接返回即可。

代码如下：

```c++
inline i64 in (i64* A, i64* B) noexcept { return A[3] <= B[1] && A[2] <= B[3];}

void query (i64 x, i64 v) noexcept {
    /*mdp 是子树内 dp 最大值，d[1]是s, d[2]是w, d[3]是a*/
	if (!x || tree[x].mdp <= ans || !in (tree[x].mn, s[v].d)) return;
		
	if (in (tree[x].ma, s[v].d)) {
		ans = tree[x].mdp;
		return;
	}
		
	if (tree[x].d[3] <= s[v].d[1] && tree[x].d[2] <= s[v].d[3])
		ans = std::max (ans, tree[x].dp);
		
	query (ls, v), query (rs, v);
}
```

Finish.

[Code](https://www.luogu.com.cn/record/196675439)

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3364)

# 前置知识

[将动态问题转化为静态问题](https://oi-wiki.org//misc/cdq-divide/#%E5%B0%86%E5%8A%A8%E6%80%81%E9%97%AE%E9%A2%98%E8%BD%AC%E5%8C%96%E4%B8%BA%E9%9D%99%E6%80%81%E9%97%AE%E9%A2%98) | [树状数组](https://oi-wiki.org//ds/fenwick/)

# 解法

先将英雄按 $\{ l \}$ 升序排序，从而减少一维偏序。

设 $f_{i}$ 表示以 $i$ 结尾的最长合法序列长度，状态转移方程为 $f_{i}=\max\limits_{j=1}^{i-1}\{ [a_{j} \le s_{i} \land w_{j} \le a_{i}] \times f_{j}+1 \}$ 。

然后就是 CDQ 分治优化 DP 的板子题了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	int l,s,w,a,id;
}q[100010];
struct BIT
{
	int c[100000010];
	int lowbit(int x)
	{
		return (x&(-x));
	}
	void add(int n,int x,int val)
	{
		for(int i=x;i<=n;i+=lowbit(i))
		{
			c[i]=max(c[i],val);
		}
	}
	int getsum(int x)
	{
		int ans=0;
		for(int i=x;i>=1;i-=lowbit(i))
		{
			ans=max(ans,c[i]);
		}
		return ans;
	}
	void del(int n,int x)
	{
		for(int i=x;i<=n;i+=lowbit(i))
		{
			c[i]=0;
		}
	}
}T;
int f[100010];
bool cmpl(node a,node b)
{
	return a.l<b.l;
}
bool cmps(node a,node b)
{
	return a.s<b.s;
}
bool cmpa(node a,node b)
{
	return a.a<b.a;
}
bool cmpid(node a,node b)
{
	return a.id<b.id;
}
void cdq(int l,int r,int k)
{
	if(l==r)
	{
		return;
	}
	int mid=(l+r)/2,x,y;
	cdq(l,mid,k);
	sort(q+l,q+mid+1,cmpa);
	sort(q+mid+1,q+r+1,cmps);
	for(x=l,y=mid+1;y<=r;y++)
	{
		for(;q[x].a<=q[y].s&&x<=mid;x++)
		{
			T.add(k,q[x].w,f[q[x].id]);
		}
		f[q[y].id]=max(f[q[y].id],T.getsum(q[y].a)+1);
	}
	x--;
	for(int i=l;i<=x;i++)
	{
		T.del(k,q[i].w);
	}
	sort(q+mid+1,q+r+1,cmpid);
	cdq(mid+1,r,k);
}
int main()
{
	int n,ans=0,i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>q[i].l>>q[i].s>>q[i].w>>q[i].a;
		f[i]=1;
	}
	sort(q+1,q+1+n,cmpl);
	for(i=1;i<=n;i++)
	{
		q[i].id=i;
	}
	cdq(1,n,100000000);
	for(i=1;i<=n;i++)
	{
		ans=max(ans,f[i]);
	}
	cout<<ans<<endl;
	return 0;
}
```

# 后记

多倍经验： [luogu P4093 [HEOI2016/TJOI2016] 序列](https://www.luogu.com.cn/problem/P4093)

---

## 作者：IkunTeddy (赞：0)

# 题目分析

题意就是求三维 LIS。偏序问题考虑 cdq 分治求解。

设 $f_i$ 表示以 $i$ 结尾的 LIS 长度。

在递归时，先遍历左边，再用左边的 $f$ 数组更新右边，继续递归右边。

更新时，排序+值域树状数组即可，所以需要离散化。

非常简单就切掉了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
//
const int maxn=3e5+10;
int n,ans,N;
int disc[maxn];
int f[maxn];
//
int ft[maxn];
int lowbit(int x){return -x&x;}
void update(int x,int k,int op){
	for(int i=x;i<=N;i+=lowbit(i)){
		if(op==0)ft[i]=k;
		else ft[i]=max(ft[i],k);
	}
}
int ask(int x){
	int res=0;
	for(int i=x;i>=1;i-=lowbit(i))res=max(res,ft[i]);
	return res;
}
//
struct node{
	int l,s,w,a,id;
}s[maxn];
bool cmp1(node x,node y){
	if(x.l==y.l){
		return x.a<=y.s;
	}else{
		return x.l<y.l;
	}
}
bool cmp2(node x,node y){return x.s<y.s;}
bool cmp3(node x,node y){return x.a<y.a;}
void cdq(int l,int r){
	if(l==r)return ;
	int mid=(l+r)>>1;
	cdq(l,mid);
	sort(s+l,s+mid+1,cmp3);
	sort(s+mid+1,s+r+1,cmp2);
	int pl=l,pr=mid+1;
	for(;pr<=r;pr++){
		while(pl<=mid&&s[pl].a<=s[pr].s){
			update(s[pl].w,f[s[pl].id],1);
			pl++;
		}
		f[s[pr].id]=max(f[s[pr].id],ask(s[pr].a)+1);
	}
	for(int i=l;i<=pl;i++)update(s[i].w,0,0);
	sort(s+l,s+r+1,cmp1);
	cdq(mid+1,r);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		f[i]=1;
		cin>>s[i].l>>s[i].s>>s[i].w>>s[i].a;
		disc[++N]=s[i].s;
		disc[++N]=s[i].w;
		disc[++N]=s[i].a;
		s[i].id=i;
	}
	sort(disc+1,disc+N+1);
	N=unique(disc+1,disc+N+1)-disc-1;
	for(int i=1;i<=n;i++){
		s[i].s=lower_bound(disc+1,disc+N+1,s[i].s)-disc;
		s[i].w=lower_bound(disc+1,disc+N+1,s[i].w)-disc;
		s[i].a=lower_bound(disc+1,disc+N+1,s[i].a)-disc;
	}
	sort(s+1,s+n+1,cmp1);
	cdq(1,n);
	for(int i=1;i<=n;i++)ans=max(ans,f[i]);
	cout<<ans<<'\n';

	return 0;
}

```

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：三维偏序，CDQ 分治，整体 DP
### 思路：
先写式子，将等级、力量、智力、攻击力分别记为 $a,b, c, d$。

则需要满足下列关系式：
- $ a_i \le a_j $
- $ d_i \le b_j $
- $ c_i \le d_j $

然后就是 CDQ 分治整体 DP 的模板了。
### 实现：
先对第一维排序。

在 CDQ 分治的过程中，先递归左边，再用左边更新右边，最后递归右边。

更新过程中，先通过排序降掉第二维，第三维用树状数组+双指针解决。
### 复杂度：
时间：$ O(n\log^2n)$\
空间：$ O(n)$
### Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5;
int M;

class BinaryIndexedTree {
private:
	int tree[Maxn];
	inline int lowbit(const int &t) { return t&-t; }
public:
	inline void ins(int t, int val) { for(; t<=M; t+=lowbit(t)) tree[t] = max(tree[t], val); }
	inline void del(int t) { for(; t<=M; t+=lowbit(t)) tree[t] = 0; }
	inline int Ask(int t) { int res = 0; for(; t; t-=lowbit(t)) res = max(res, tree[t]); return res; }
} bit;

namespace Josh_zmf {
	
	int N, f[Maxn], hash[Maxn];
	struct node { int a, b, c, d, dd; } a[Maxn];

	inline void solve(int l, int r) {
		if(l == r)	return f[l]++, void();
		int mid = (l+r)>>1;
		solve(l, mid);
		sort(a+l, a+mid+1, [](const node &a, const node &b) { return a.d < b.d; } );
		sort(a+mid+1, a+r+1, [](const node &a, const node &b) { return a.b < b.b; } );
		for(int i=l, j=mid+1; j<=r; j++) {
			for(; i<=mid && a[i].d<=a[j].b; i++)	bit.ins(a[i].c, f[a[i].a]);
			f[a[j].a] = max(f[a[j].a], bit.Ask(a[j].dd));
		}
		for(int i=l; i<=mid; i++)	bit.del(a[i].c);
		sort(a+l, a+mid+1, [](const node &a, const node &b) { return a.a < b.a; } );
		sort(a+mid+1, a+r+1, [](const node &a, const node &b) { return a.a < b.a; } );
		solve(mid+1, r);
	}

	inline int main() {
		cin>> N;
		for(int i=1; i<=N; i++) {
			cin>> a[i].a>> a[i].b>> a[i].c>> a[i].d;
			hash[++M] = a[i].c;
		}
		sort(a+1, a+1+N, [](const node &a, const node &b) { return a.a < b.a; } );
		sort(hash+1, hash+1+M), M = unique(hash+1, hash+1+M) - (hash+1);
		for(int i=1; i<=N; i++) {
			a[i].a = i;
			a[i].c = lower_bound(hash+1, hash+1+M, a[i].c) - hash;
			a[i].dd = upper_bound(hash+1, hash+1+M, a[i].d) - hash-1;
		}
		solve(1, N); int ans = 0;
		for(int i=1; i<=N; i++)	ans = max(ans, f[i]);
		cout<< ans;
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走吧。：）

---

## 作者：complete_binary_tree (赞：0)

很板的 $\text{cdq}$ 优化 $\text{dp}$。

首先，我们设 $f_i$ 为选第 $i$ 个英雄为结尾时最长的长度。

显然，如果英雄 $j$ 能放在英雄 $i$ 后面，那么 $f_j = f_i + 1$。

怎么写呢？

- 首先按照 $l$ 排序。

- 然后 $\text{cdq}$ 分治：

  - 首先分治左半边，因为你的的转移从左半边来。
  
  - 然后左半边按 $a$ 排序，右半边按 $s$ 排序。
  
  - 然后计算左半部分对右半部分的贡献。此时需要将 $w$ 存入权值线段树中。
  
  - 然后排序回来，清空权值线段树（直接在线段树上 $\text{dfs}$），最后再分治右半部分。

- 由于 $w$ 要存入线段树，所以 $w$ 要离散化；然而，$w$ 和 $a$ 有偏序关系，$a$ 和 $s$ 同样有。所以要一起离散化。

然后线段树要注意清空，清空边界条件要判，还有偏序条件要看清。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, tmp[N * 3], dp[N];

struct node{ int l, s, w, a, id; } a[N];
bool cmp( node x, node y ){ return x.l < y.l; }
bool cmp2( node x, node y ){ return x.a == y.a ? x.l < y.l : x.a < y.a; }
bool cmp3( node x, node y ){ return x.s == y.s ? x.l < y.l : x.s < y.s; }

struct tree{ int l, r, max; };
struct st{
	tree t[N << 4];
	void build( int x, int l, int r ){
		t[x].l = l, t[x].r = r;
		if( l == r ) return ;
		int mid = ( l + r ) >> 1;
		build( 2 * x, l, mid ), build( 2 * x + 1, mid + 1, r );
	}
	void add( int x, int pos, int val ){
		if( t[x].l == t[x].r ){ t[x].max = val; return ; }
		int mid = ( t[x].l + t[x].r ) >> 1;
		if( pos <= mid ) add( 2 * x, pos, val ); else add( 2 * x + 1, pos, val );
		t[x].max = max( t[2 * x].max, t[2 * x + 1].max );
	}
	int find( int x, int l, int r ){
		if( t[x].l > r || t[x].r < l ) return 0;
		if( l <= t[x].l && r >= t[x].r ) return t[x].max;
		return max( find( 2 * x, l, r ), find( 2 * x + 1, l, r ) );
	}
	void clear( int x ){
		if( !t[x].max ) return ;
		t[x].max = 0;
		if( t[x].l == t[x].r ) return ;
		clear( 2 * x ), clear( 2 * x + 1 );
	}
} t1;

void cdq( int l, int r ){
	if( l == r ) return ;
	int mid = ( l + r ) >> 1;
	cdq( l, mid );
	sort( a + l, a + mid + 1, cmp2 ), sort( a + mid + 1, a + r + 1, cmp3 );
	int j = l;
	for( int i = mid + 1; i <= r; ++i ){
		while( j <= mid && a[j].a <= a[i].s ) t1.add( 1, a[j].w, dp[a[j].id] ), ++j;
		int ans = t1.find( 1, 1, a[i].a );
		if( ans + 1 > dp[a[i].id] ) dp[a[i].id] = ans + 1;
	}
	t1.clear( 1 );
	sort( a + l, a + mid + 1, cmp ), sort( a + mid + 1, a + r + 1, cmp );
	cdq( mid + 1, r );
}

int main(){
	scanf( "%d", &n );
	t1.build( 1, 1, 3 * n );
	for( int i = 1; i <= n; ++i ){
		scanf( "%d%d%d%d", &a[i].l, &a[i].s, &a[i].w, &a[i].a );
		tmp[3 * i - 2] = a[i].s, tmp[3 * i - 1] = a[i].w, tmp[3 * i] = a[i].a;
		dp[i] = 1, a[i].id = i;
	}
	sort( tmp + 1, tmp + 3 * n + 1 );
	int len = unique( tmp + 1, tmp + 3 * n + 1 ) - tmp - 1;
	for( int i = 1; i <= n; ++i ) a[i].s = lower_bound( tmp + 1, tmp + len + 1, a[i].s ) - tmp, a[i].a = lower_bound( tmp + 1, tmp + len + 1, a[i].a ) - tmp, a[i].w = lower_bound( tmp + 1, tmp + len + 1, a[i].w ) - tmp;
	sort( a + 1, a + n + 1, cmp );
	cdq( 1, n );
	int mxans = 0;
	for( int i = 1; i <= n; ++i ) mxans = max( mxans, dp[i] );
	printf( "%d", mxans );
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑 DP。

我们令 $a_i,b_i,c_i,d_i$ 为每名英雄的四个属性，顺序如输入格式所描述。

显然有 $f_i = \max \limits_{j|a_j<a_i \land d_j \leq b_i\land c_j \leq d_i} f_j + 1$。

$\land$ 是逻辑与运算符。

经典的三维偏序，CDQ 分治优化 DP 即可。时间复杂度 $O(n \log^2 n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <cassert>
#include <vector>
using namespace std;

const int N = 1e6 + 5;

class Bit
{
public:
	int tr[N];
	int lowbit(int x)
	{
		return x & -x;
	}
	void ins(int x, int v)
	{
		while (x < N)
		{
			tr[x] = max(tr[x], v);
			x += lowbit(x);
		}
	}
	int query(int x)
	{
		int res = 0;
		while (x)
		{
			res = max(res, tr[x]);
			x -= lowbit(x);
		}
		return res;
	}
	void CLEAR(int x)
	{
		while (x < N)
		{
			tr[x] = 0;
			x += lowbit(x);
		}
	}
}tr;

int f[N];
int n;
struct Node
{
	int a, b, c, d, id;
	bool operator<(const Node& g) const
	{
		return a < g.a;
	}
}p[N];
vector<int> b;

bool cmp1(const Node& x, const Node& y)
{
	return x.d < y.d;
}

bool cmp2(const Node& x, const Node& y)
{
	return x.b < y.b;
}

void cdq(int l, int r)
{
	if (l > r) return;
	if (l == r)
	{
		f[p[l].id] = max(f[p[l].id], 1);
		return;
	}
	sort(p + l, p + r + 1);
	int mid = l + r >> 1;
	cdq(l, mid);
	sort(p + l, p + mid + 1, cmp1);
	sort(p + mid + 1, p + r + 1, cmp2);
	int i = l, j = mid + 1;
	while (j <= r)
	{
		while (i <= mid && p[i].d <= p[j].b)
		{
			tr.ins(p[i].c, f[p[i].id]);
			i++;
		}
		f[p[j].id] = max(f[p[j].id], tr.query(p[j].d) + 1);
		j++;
	}
	for (int i = l; i <= mid; i++)
	{
		tr.CLEAR(p[i].c);
	}
	cdq(mid + 1, r);
}

int main()
{
	//freopen("D:\\P3364_1.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", &p[i].a, &p[i].b, &p[i].c, &p[i].d);
		p[i].id = i;
		b.emplace_back(p[i].a);
		b.emplace_back(p[i].b);
		b.emplace_back(p[i].c);
		b.emplace_back(p[i].d);
	}
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	for (int i = 1; i <= n; i++)
	{
		p[i].a = lower_bound(b.begin(), b.end(), p[i].a) - b.begin() + 1;
		p[i].b = lower_bound(b.begin(), b.end(), p[i].b) - b.begin() + 1;
		p[i].c = lower_bound(b.begin(), b.end(), p[i].c) - b.begin() + 1;
		p[i].d = lower_bound(b.begin(), b.end(), p[i].d) - b.begin() + 1;
	}
	cdq(1, n);
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, f[i]), assert(f[i] >= 1);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：zjy1412 (赞：0)

本题里面各种量的比较关系很容易让人想到多维偏序。再加上一眼可见的dp，很容易想到cdq分治优化dp来解决。

题目的简化版：$l[i]\geq l[j]\ \ \ s[i]\geq a[j]\ \ \ a[i]\geq w[j]$ 求最多能选多少个英雄。

dp方程很显然是：$f[i]=max(f[j])+1$ 其中j要满足题意。其实就是类似[拦截导弹](https://www.luogu.com.cn/problem/P2487)
的做法，但是要注意离散化，更要注意除了等级的三个量要一起离散。(因为这个调了好久)接下来是喜闻乐见的代码环节。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<set>
#include<vector>
#include<cstdlib>
using namespace std;
#define int long long
#define R register
#define lp (p<<1)
#define rp (p<<1|1)
int read(){
	int a=0,b=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')b=-1;c=getchar();}
	while(isdigit(c)){a=a*10+c-'0';c=getchar();}
	return a*b;
}
void write(int x){
	if(x<0){putchar('-');x=-x;}
	if(x<=9){putchar(x+'0');return;}
	write(x/10);putchar(x%10+'0');
}
void writesp(int x){
	write(x);putchar(' ');
}
void writeln(int x){
	write(x);putchar('\n');
}
const int N=3e5+50;
int n,f[N],h,lsh[N];
struct node{
	int l,s,w,a,id;
	void init(){
		l=read();s=lsh[++h]=read();
		w=lsh[++h]=read();a=lsh[++h]=read();
	}
}e[N];
bool cmpl(node x,node y){
	return x.l<y.l;
}
bool cmpa(node x,node y){
	return x.a<y.a;
}
bool cmps(node x,node y){
	return x.s<y.s;
}
bool cmpid(node x,node y){
	return x.id<y.id;
}
namespace seg{
	int dat[N<<2];
	void change(int p,int l,int r,int k,int z){
		if(l==r){
			dat[p]=max(dat[p],z);
			return;
		}
		int mid=(l+r)>>1;
		if(k<=mid)change(lp,l,mid,k,z);
		else change(rp,mid+1,r,k,z);
		dat[p]=max(dat[lp],dat[rp]);
	}
	int query(int p,int l,int r,int u,int v){
		if(l>=u&&r<=v)return dat[p];
		int mid=(l+r)>>1,val=0;
		if(u<=mid)val=max(val,query(lp,l,mid,u,v));
		if(v>mid)val=max(val,query(rp,mid+1,r,u,v));
		return val;
	}
	void clear(int p,int l,int r){
		if(!dat[p])return;
		dat[p]=0;
		if(l==r)return;
		int mid=(l+r)>>1;
		clear(lp,l,mid);clear(rp,mid+1,r);
	}
}
void cdq(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	sort(e+l,e+r+1,cmpid);
	cdq(l,mid);
	sort(e+l,e+mid+1,cmpa);
	sort(e+mid+1,e+r+1,cmps);
	seg::clear(1,1,h);
	for(R int i=l,j=mid+1;j<=r;j++){
		while(i<=mid&&e[i].a<=e[j].s)seg::change(1,1,h,e[i].w,f[e[i].id]),i++;
		f[e[j].id]=max(f[e[j].id],seg::query(1,1,h,1,e[j].a)+1);
	}
	cdq(mid+1,r);
}
signed main(){
	n=read();
	for(R int i=1;i<=n;i++){
		f[i]=1;
		e[i].init();
	}
	sort(lsh+1,lsh+h+1);
	h=unique(lsh+1,lsh+h+1)-lsh-1;
	for(R int i=1;i<=n;i++){
		e[i].w=lower_bound(lsh+1,lsh+h+1,e[i].w)-lsh;
		e[i].a=lower_bound(lsh+1,lsh+h+1,e[i].a)-lsh;
		e[i].s=lower_bound(lsh+1,lsh+h+1,e[i].s)-lsh;
	}
	sort(e+1,e+n+1,cmpl);
	for(R int i=1;i<=n;i++)e[i].id=i;
	cdq(1,n);
	int ans=0;
	for(R int i=1;i<=n;i++)ans=max(ans,f[i]);
	writeln(ans);
	return 0;
}
```


---

