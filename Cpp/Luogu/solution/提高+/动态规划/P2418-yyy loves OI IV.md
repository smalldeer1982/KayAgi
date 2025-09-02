# yyy loves OI IV

## 题目背景

某校 2015 届有两位 OI 神牛，yyy 和 c01。


## 题目描述

全校除他们以外的 $N$ 名学生，每人都会膜拜他们中的某一个人。现在老师要给他们分宿舍了。但是，问题来了：

同一间宿舍里的人要么膜拜同一位大牛，要么膜拜 yyy 和 c01 的人数的差的绝对值不超过 $M$。否则他们就会打起来。

为了方便，老师让 $N$ 名学生站成一排，只有连续地站在一起的人才能分进同一个宿舍。

假设每间宿舍能容纳任意多的人，请问最少要安排几个宿舍？


## 说明/提示

| 测试点编号 | $N$ 的范围 | $M$ 的范围 |
| :-----------: | :-----------: | :-----------: |
| $1 \sim 3$ | $\le 2500$ | $\le 10$ |
| $4 \sim 5$ | $\le 5\times 10 ^ 5$ | $\le 10$ |
| $6 \sim 10$ | $\le 5\times 10 ^ 5$ | $\le 2000$ |



## 样例 #1

### 输入

```
5 1
1
1
2
2
1```

### 输出

```
1```

# 题解

## 作者：Created_equal1 (赞：10)

设F[i]表示将前i个人处理完毕所要用的最少寝室个数

考虑暴力的O(n^2)的转移，我们会发现，时间大多数用在了寻找最小且满足条件的情况

可以考虑分情况讨论，对于都是膜拜一个人的情况用数组记录，对于膜拜人数的绝对值不大于M的情况，化简得到一个不等式，然后用线段树（单点修改，区间最值）记录。

具体分析看我的代码和代码开头的注释。

```cpp

//j~i可以放在一间宿舍(j<=i)  c01[i]表示前i个人中膜拜c01的人数，yyy[i]同理
//情况1：c01[j - 1] = c01[i]
//情况2：yyy[j - 1] = c01[i]
//情况3：设a = yyy[i] - yyy[j - 1]   b = c01[i] - c01[j - 1]
//       |a - b| <= M
//需满足：①a - b <= M 
//        =>(yyy[i] - yyy[j - 1]) - (c01[i] - c01[j - 1]) <=M
//        =>yyy[i] - yyy[j - 1] - c01[i] + c01[j - 1] <= M
//        =>c01[j - 1] - yyy[j - 1] <= M + c01[i] - yyy[i] 
//      ②b - a <= M
//        =>yyy[j - 1] - c01[j - 1] <= M + yyy[i] - c01[i]
//        =>c01[j - 1] - yyy[j - 1] >= c01[i] - yyy[i] - M
//整理可得 情况3等价于：
// c01[i] - yyy[i] - M <= c01[j - 1] - yyy[j - 1] <= M + c01[i] - yyy[i]

//情况1和情况2用数组记录，情况3用线段树处理 时间复杂度O(nlogn) 

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const size_t Max_N(500050);
const int Add(500000);
const int INF(0X3F3F3F3F);

void Get_Val(int &Ret)
{
    Ret = 0;
    char ch;
    while ((ch = getchar()), (ch > '9' || ch < '0'))
        ;
    do
    {
        (Ret *= 10) += ch - '0';
    }
    while ((ch = getchar()), (ch >= '0' && ch <= '9'));
}

struct node
{
    int l, r;
    int Min;
};

struct Segment_Tree
{
    node segt[Max_N << 3];
    void build_tree(const int&, const int&, const int&);
    void change(const int&, const int&, const int &);
    int rmq_min(const int&, const int&, const int&);
    inline
    void pushup(const int &cur)
    {
        segt[cur].Min = min(segt[cur << 1].Min, segt[(cur << 1) | 1].Min);
    }
};
Segment_Tree Space;

void Segment_Tree::build_tree(const int &cur, const int &l, const int &r)
{
    segt[cur].l = l, segt[cur].r = r, segt[cur].Min = INF;
    if (l == r)
        return;
    int mid = l + ((r - l) >> 1);
    build_tree(cur << 1, l, mid);
    build_tree((cur << 1) | 1, mid + 1, r);
}

void Segment_Tree::change(const int &cur, const int &i, const int &x)
{
    if (segt[cur].l == i && segt[cur].r == i)
    {
        segt[cur].Min = x;
        return;
    }
    int mid = segt[cur].l + ((segt[cur].r - segt[cur].l) >> 1);
    if (i <= mid)
        change(cur << 1, i, x);
    else
        change((cur << 1) | 1, i, x);
    pushup(cur);
}

int Segment_Tree::rmq_min(const int &cur, const int &l, const int &r)
{
    if (segt[cur].l == l && segt[cur].r == r)
        return segt[cur].Min;
    int mid = segt[cur].l + ((segt[cur].r - segt[cur].l) >> 1);
    if (r <= mid)
        return rmq_min(cur << 1, l, r);
    else
        if (l > mid)
            return rmq_min((cur << 1) | 1, l, r);
        else
            return min(rmq_min(cur << 1, l, mid), rmq_min((cur << 1) | 1, mid + 1, r));
}

int N, M;
int c01[Max_N], yyy[Max_N];

int F[Max_N];
int c01_dp[Max_N], yyy_dp[Max_N];
int Minus[Max_N << 1];

void init()
{
    int v;
    Get_Val(N), Get_Val(M);
    for (int i = 1;i <= N;++i)
    {
        Get_Val(v);
        yyy[i] = yyy[i - 1] + (v == 1);
        c01[i] = c01[i - 1] + (v == 2);
    }
}

void dp()
{
    memset(c01_dp, 0X3F, sizeof(c01_dp));
    memset(yyy_dp, 0X3F, sizeof(yyy_dp));
    memset(Minus, 0X3F, sizeof(Minus));
    Minus[0 + Add] = c01_dp[0] = yyy_dp[0] = F[0] = 0;
    Space.build_tree(1, -500000, 500000);
    Space.change(1, 0, 0);
    int a, b, c;
    for (int i = 1;i <= N;++i)
    {
        a = c01_dp[c01[i]];
        b = yyy_dp[yyy[i]];
        c = Space.rmq_min(1, c01[i] - yyy[i] - M, M + c01[i] - yyy[i]);
        F[i] = min(min(a + 1, b + 1), min(c + 1, F[i - 1] + 1));
        c01_dp[c01[i]] = min(c01_dp[c01[i]], F[i]);
        yyy_dp[yyy[i]] = min(yyy_dp[yyy[i]], F[i]);
        if (F[i] < Minus[c01[i] - yyy[i] + Add])
        {
            Minus[c01[i] - yyy[i] + Add] = F[i];
            Space.change(1, c01[i] - yyy[i], F[i]);
        }
    }
    printf("%d", F[N]);
}

int main()
{
    init();
    dp();
    return 0;
}

```

---

## 作者：LlLlCc (赞：7)

由题意可知，只有两种人（？），不妨把支持yyy神仙的人看成$-1$，把支持c01神仙的人看成$1$

设：$\large sum_i:$前$i$个人值的前缀和

根据定义，不难发现，$L$到$R$之间两种人数的差为$\large \left | sum_R-sum_{L-1} \right |$

不难发现这题是个DP，考虑如何定义转移方程

设：$\large f_i:$前$i$个人最少分几组

转移方程非常显然：

$\Large f_i=\min(f_j)+1\;[\; \left | sum_R-sum_L \right |\leq M]$

朴素的$O(n^2)DP$肯定是过不去，接下来考虑如何优化

不妨将式子拆开，得：

$$\Large [\; \left | sum_R-sum_L \right |\leq M]$$

- 如果$\large sumR \leq sumL$,则$\large sum_L\leq sum_R+M$

- 如果$\large sumR > sumL$,则$\large sum_L\geq  sum_R-M$

即：

$$\Large sum_R-M\leq sum_L\leq sum_R+M$$

也就是说$\large f_i$等于在所有满足这个式子的$L$中取$f_L$最小的再$+1$

所以说如何找有哪些$L$满足这个式子？

我们可以把$sum_i$当成$i$的坐标，然后用一个数组来存

单点修改，区间查询你想到了什么呢？

没错，线段树可以完美支持

不过这里有一个问题，因为$sum_i$可能会出现负数，也就会数组越界。因为$n$为$500000$,所以$sum_i$最小值为$-500000$，因为还有$-M$的操作，所以我们可以整体向右移$700000$，这样就避免了数组越界

## code
```
#include<bits/stdc++.h>
#define maxn 2000005
using namespace std;
const int T=7e5,INF=1<<30;
int n,Now,LL,RR,L,R,y,x,Ans,f[maxn],sum[maxn],M,a[maxn],Lst;
struct lc{
	int L,R,x,k;
}tree[8000005],Tree[maxn];
struct IO{
	static const int S=1<<21;
	char buf[S],*p1,*p2;int st[105],Top;
	~IO(){clear();}
	inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
	inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
	inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n');return *this;}
	template<typename T> IO&operator >> (T&x){
		x=0;bool f=0;char ch=gc();
		while(ch<'0'||ch>'9'){if(ch=='-') f^=1;ch=gc();}
		while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=gc();
		f?x=-x:0;return *this;
	}
	IO&operator << (const char c){pc(c);return *this;}
	template<typename T> IO&operator << (T x){
		if(x<0) pc('-'),x=-x;
		do{st[++st[0]]=x%10,x/=10;}while(x);
		while(st[0]) pc('0'+st[st[0]--]);return *this;
	}
}fin,fout;
inline int min(int a,int b){return a<b? a:b;}
inline int max(int a,int b){return a>b? a:b;}
inline void build(int k,int L,int R){
	tree[k].L=L,tree[k].R=R;
	if (L==R){tree[k].k=tree[k].x=INF;return;}
    int mid=L+R>>1;
    build(k<<1,L,mid);build(k<<1|1,mid+1,R);
    tree[k].k=tree[k].x=INF;
}
inline void Build(int k,int L,int R){
	Tree[k].L=L,Tree[k].R=R;
	if (L==R){Tree[k].k=Tree[k].x=INF;return;}
    int mid=L+R>>1;
    Build(k<<1,L,mid);Build(k<<1|1,mid+1,R);
    Tree[k].k=Tree[k].x=INF;
}
inline void down(int k){
	tree[k<<1].x=min(tree[k<<1].x,tree[k].k);
	tree[k<<1].k=min(tree[k<<1].k,tree[k].k);
	tree[k<<1|1].x=min(tree[k<<1|1].x,tree[k].k);
	tree[k<<1|1].k=min(tree[k<<1|1].k,tree[k].k);
	tree[k].k=INF;
}
inline void Down(int k){
	Tree[k<<1].x=min(Tree[k<<1].x,Tree[k].k);
	Tree[k<<1].k=min(Tree[k<<1].k,Tree[k].k);
	Tree[k<<1|1].x=min(Tree[k<<1|1].x,Tree[k].k);
	Tree[k<<1|1].k=min(Tree[k<<1|1].k,Tree[k].k);
	Tree[k].k=INF;
}
inline void Get(int k){
	if (tree[k].L>=L&&tree[k].R<=R){Now=min(Now,tree[k].x);return;}
	down(k);
	int mid=tree[k].L+tree[k].R>>1;
	if (L<=mid) Get(k<<1);
	if (R>mid) Get(k<<1|1);
	tree[k].x=min(tree[k<<1].x,tree[k<<1|1].x);
}
inline void GET(int k){
	if (Tree[k].L>=L&&Tree[k].R<=R){Now=min(Now,Tree[k].x);return;}
	Down(k);
	int mid=Tree[k].L+Tree[k].R>>1;
	if (L<=mid) GET(k<<1);
	if (R>mid) GET(k<<1|1);
	Tree[k].x=min(Tree[k<<1].x,Tree[k<<1|1].x);
}
inline void change(int k){
	if (tree[k].L==tree[k].R&&tree[k].L==x){tree[k].x=min(tree[k].x,y);tree[k].k=min(tree[k].k,y);return;}
	down(k);
	int mid=tree[k].L+tree[k].R>>1;
	if (x<=mid) change(k<<1);
	else change(k<<1|1);
	tree[k].x=min(tree[k<<1].x,tree[k<<1|1].x);
}
inline void Change(int k){
	if (Tree[k].L==Tree[k].R&&Tree[k].L==x){Tree[k].x=min(Tree[k].x,y);Tree[k].k=min(Tree[k].k,y);return;}
	Down(k);
	int mid=Tree[k].L+Tree[k].R>>1;
	if (x<=mid) Change(k<<1);
	else Change(k<<1|1);
	Tree[k].x=min(Tree[k<<1].x,Tree[k<<1|1].x);
}
int main(){
	freopen("wyy.in","r",stdin);
	freopen("wyy.out","w",stdout);
	fin>>n>>M;sum[0]=LL=RR=T;
	for (int i=1;i<=n;i++){
		fin>>a[i];sum[i]=sum[i-1];f[i]=INF;
		if (a[i]==1) sum[i]--;
		else sum[i]++; 
		LL=min(LL,sum[i]),RR=max(RR,sum[i]);
	}
	build(1,LL,RR);Build(1,0,n);Change(1);
    for (int i=1;i<=n;i++){
    	if (abs(T-sum[i])<=M){
	    	f[i]=0;
            if (a[i]!=a[i-1]) Lst=i-1;
		}
		else{
			Now=INF;
        	if (a[i]!=a[i-1]) Lst=i-1;
    		L=Lst,R=i-1,GET(1);
			L=sum[i]-M,R=M+sum[i];Get(1);
        	if (Now!=INF) f[i]=Now;
        	else f[i]=f[i-1];
    	}
		f[i]++;x=sum[i],y=f[i];
    	change(1);x=i;Change(1);
	}
	fout<<f[n];
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：6)

感觉还是有点淦，$WA$ 了无数发才过掉了这道题。    
这道题首先我们不难看出是一个 $dp$ ，而且是个很经典的分组 $dp$ ，我们只要根据题意模拟一下这个 $dp$ 即可，橙 $dp$ 不想细讲。  
时间复杂度 $O(n ^ 2)$ 交上去后你会不出意外地 $T$ 掉七个点。  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 5e5 + 5;
int n,m,dp[Len],a[Len],sum[Len][3],num_two,num_one;
int Iabs(int x){return x >= 0 ? x : -x;}
bool check(int l,int r)
{
	num_one = sum[r][1] - sum[l - 1][1] , num_two = sum[r][2] - sum[l - 1][2];
	if(num_one == (r - l + 1) || (num_two == (r - l + 1)) || Iabs(num_one - num_two) <= m) return true;
	return false; 
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)
	{
		int x;scanf("%d",&x);
		sum[i][1] = sum[i - 1][1] + (x == 1);
		sum[i][2] = sum[i - 1][2] + (x == 2);
	}
	memset(dp , 0x3f , sizeof dp);
	dp[0] = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 0 ; j < i ; j ++)
			if(check(j + 1 , i)) dp[i] = min(dp[i] , dp[j] + 1);
	}
	printf("%d\n",dp[n]);
	return 0;
}
```    
于是我们考虑优化这个 $dp$ ，很明显我们可以对我们的 $check$ 部分进行一定的优化：    
- 对于全部为 $1$ 或者全部为 $2$ 的情况直接维护即可，这里可以再开个线段树，亦或可以直接动态维护，我就没有再开线段树了。    
- 对于比较棘手的人数相差的绝对值控制在 $m$ 以内，我们可以发现当我们此时 $dp$ 转移到第 $i$ 位时，我们的右端点是确定的，所以我们只需要把我们的式子展开，即 $sum[r][1] - sum[r][2] + sum[l - 1][2] - sum[l - 1][1]$ ，当前可以计算 $sum[r][1] - sum[r][2]$ ，所以我们维护后面这一坨东西打入线段树然后通过绝对值的概念计算出查询区间查询最小值即可。
  
 可能还是有点不好理解，所以这里以样例举个例子：    
```
5 1
1
1
2
2
1
```
为了方便行文，令 $sum[r][1] - sum[r][2] = calc(r)$ ，$sum[l][2] - sum[l][1] = Tot(l)$ 。  
初始化 $dp[0] = 0$ ，接着循环 $1 \sim n$：    
- 转移到第一个数，$calc(i) = 1$ ，需要查询的 $Tot()$ 区间为 $-2 \sim 0$ ；     
- 转移到第二个数，$calc(i) = 2$ ，需要查询的 $Tot()$ 区间为 $-3 \sim -1$ ；   
- 转移到第三个数，$calc(i) = 1$ ，同第一个数的查询区间；    
- 转移到第四个数，$calc(i) = 0$ ，需要查询的 $Tot()$ 区间为 $-1 \sim 1$ ；    
- 转移到第五个数，$calc(i) = 1$ ，同第一个数的查询区间。    

至于这个查询的区间涉及到负数，再~~瞪~~一下原题，我们不难发现我们此时维护的区间的值域只会在 $-n \sim n$之间，离散一下就好了。    
对于第一种第二种操作，我们开两个变量维护一下当前的连续区间是哪种数，以及区间的最小 $dp$ 值是多少，如果当前这个数已经打破了连续的区间就删除原先数据重新维护，否则就直接维护最小值即可。   
这道题讲到这里差不多已经完了，这里需要注意几个细节：    
1.线段树空间开八倍，因为你此时离散出来后有 $2n + 1$ 个数；    
2.维护一二操作时，也许你会习惯性地认为这个 $dp$ 值是严格不下降的，实际上你随手画几个样例就可以把这个结论推翻，所以一定要维护区间最小值。   
3.由于 我们计算出来的查询区间有可能会跑出 $-n \sim n$ ，所以查询之前缩一下这个区间控制在 $-n \sim n$ 之间，不然有可能越界。   

附代码，帮助一下调不过这道题的同志们，其实题不难，细节多，评个紫题也说得过去。    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
//单独维护全是一种人的情况
//我们把我们的减法展开一下，发现我们只要维护一下相对差值就行了，+1的话线段树里面维护的值就需要-1，所以我们只需要开一个2 * n的线段树，然后离散一下查询即可。 
using namespace std;
const int Len = 5e5 + 5;
int num_c[Len],n,m,dp[Len],a[Len],sum[Len][3],num_two,num_one,now_c[Len];
int ans[Len << 3];
int Iabs(int x){return x >= 0 ? x : -x;}
int deC(int num){return num + n + 1;}
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){ans[x] = min(ans[ls(x)] , ans[rs(x)]);}
void build(int p,int l,int r)
{
	ans[p] = n + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
}
void update(int p,int l,int r,int idx,int w)
{
	if(l == r) 
	{
		ans[p] = min(ans[p] , w);
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx , w);
	if(idx > mid) update(rs(p) , mid + 1 , r , idx , w);
	push_up(p);
}
int query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return ans[p];
	int mid = (l + r) >> 1;int res = n + 1;
	if(nl <= mid) res = min(res , query(ls(p) , l , mid , nl , nr));
	if(nr > mid) res = min(res , query(rs(p) , mid + 1 , r , nl , nr));
	return res;
}
int main()
{
	scanf("%d %d",&n,&m);
	int lim = (n << 1) + 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d",&a[i]);
		sum[i][1] = sum[i - 1][1] + (a[i] == 1);
		sum[i][2] = sum[i - 1][2] + (a[i] == 2);
	}
	for(int i = 0 ; i <= n ; i ++) num_c[i] = sum[i][2] - sum[i][1];
	build(1 , 1 , lim);
	memset(dp , 0x3f , sizeof dp);
	dp[0] = 0;
	update(1 , 1 , lim , deC(num_c[0]) , dp[0]);
	int lst = 0 , preans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{	
		int nums = sum[i][1] - sum[i][2];
		int l = -m - nums , r = m - nums;
		l = deC(max(l , -n)) , r = deC(min(r , n));
		if(lst != a[i])
		{
			lst = a[i];
			preans = dp[i - 1];
		}
		dp[i] = min(preans , query(1 , 1 , lim , l , r)) + 1;
		update(1 , 1 , lim , deC(num_c[i]) , dp[i]);
		preans = min(preans , dp[i]);
		//printf("%d %d %d %d\n",lst,lstidx,preans,dp[i]);
	}
	printf("%d\n",dp[n]);
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

看过几位ac本题的题解后，我只能说代码看他们的，我来把思路说得明确一些。

纯区间动规只能30分，数据结构的限制；暴力70分（我想吐血）；现在说一下ac的线段树+单调子序列+区间动规（注意不是单调最长子序列）。

首先建树，查询，修改三个函数必须打上，再加上每个区间的价值。总区间的价值为该次遍历所得到的的区间所具有的**较**小房间数，这样就方便了接下来的操作，因为我们每次先修改总区间的价值，再用查询函数找出已知的**最**小价值并用一个数组进行记录，该数组第i项即为从1到i的区间最小价值（所谓的的最小价值实际上是[1,1][1,2][1,3][1,4]...中最小的较小价值，来比较是否应该对记录进行大规模的更新）。

建完树后，记录下每个区间（[1,1][1,2][1,3]...）的两种人数之差，在输入时找出单调序列并以此进行更新（此处用到区间动规的思想，[1,i]区间最小房间数由[1,j]的最小房间数（这是真的最小房间数）加上确保为一个集合的[j+1,i]（[1,i]==min([1,j]+1,[1,i]),j<i）推出），每次用最小价值与[1,i]推出新的最小价值（保证最小价值不会干扰到区间中[1,j]与[j,i]的合并，因为[j,i]可能尚未推出最小房间数），最后注意输出这个数组的最后一项而非记录的最小价值，因为整个区间的末端可能并不满足[j+1,i]小于最小价值。


---

