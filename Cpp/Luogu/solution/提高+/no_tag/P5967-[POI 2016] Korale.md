# [POI 2016] Korale

## 题目描述

有 $n$ 个带标号的珠子，第 $i$ 个珠子的价值为 $a_i$。

现在你可以选择若干个珠子组成项链（也可以一个都不选），项链的价值为所有珠子的价值和。

给出所有可能的项链排序，先按权值从小到大排序，对于权值相同的，根据所用珠子集合的标号的字典序从小到大排序。

请输出第 $k$ 小的项链的价值，以及所用的珠子集合。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 10^6$，$1\le k\le 
\min(2^n,10^6)$，$1\le a_i\le 10^9$。

## 样例 #1

### 输入

```
4 10
3 7 4 3```

### 输出

```
10
1 3 4```

# 题解

## 作者：hs_black (赞：20)

# [POI2016]Korale题解

 题目链接: [P5967](https://www.luogu.com.cn/problem/P5967) 博客链接: [hs-black](https://www.cnblogs.com/Hs-black/p/12234065.html)

不妨把题目的分为两问

## Part1: 求出第k小的项链组合价值

思路类似超级钢琴, 先将价值排序, 用二元组$(sum, i)$ 描述前i个数选出若干数和为sum(必选第i个数), 利用小根堆不断取出堆顶, 并把$(sum + a[i+1], i+1)$和$(sum + a[i+1] - a[i], i + 1)$加入堆中. 这种方法可以将所有情况不重不漏遍历且具有单调性, 时间复杂度$\Theta(klogn)$

## Part2: 求出所用珠子集合

设上一问求出的答案为ans, 排名小于等于k且和为ans的个数为cnt

爆搜: 从前向后取数, 每次尽量取靠前的数, 从而保证字典序最小, 取数可以用线段树维护区间最小值, 用st表也是可以的, 因为取得集合排名一定小于等于k, 所以最多选出k次, 复杂的$\Theta(klogn)$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1005000;

template <typename T>
void read(T &x) {
    x = 0; bool f = 0;
    char c = getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=1;
    for (;isdigit(c);c=getchar()) x=x*10+(c^48);
    if (f) x=-x;
}

template <typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) write(x / 10);
    putchar('0' + x % 10);
}

int n, k;

int a[N], b[N];

struct node {
	ll sum, i;
	bool operator < (const node &i) const {
		return sum > i.sum;
	}
};

priority_queue <node> q;
ll ans, cnt;

#define p1 p << 1
#define p2 p << 1 | 1
int mn[N<<2];

inline int Mn(int a, int b) {return a > b ? b : a;}
	

void build(int l, int r, int p) {
	if (l == r) return mn[p] = a[l], void();
	int mid = (l + r) >> 1;
	build(l, mid, p1), build(mid + 1, r, p2);
	mn[p] = Mn(mn[p1], mn[p2]);
}

int query(int l, int r, int p, int ql, ll x) {
	if (ql <= l) {
		if (mn[p] > x) return 0;
		if (l == r) return l;
	}
	int mid = (l + r) >> 1;
	if (ql <= mid) {
		int t = query(l, mid, p1, ql, x);
		if (t) return t;
	}
	return query(mid + 1, r, p2, ql, x);
}

int top, st[N];
void dfs(int l, ll res) {
	if (!res) {
		cnt--;
		if (!cnt) {
			cout << ans << endl;
			for (int i = 1;i <= top; i++) 
				write(st[i]), putchar(' ');
			exit(0);
		}
	}
	for (int i = l + 1;i <= n; i++) {
		i = query(1, n, 1, i, res);
		if (!i) return;
		st[++top] = i;
		dfs(i, res - a[i]);
		top--;
	}
}

int main() {
	read(n), read(k); k--;
	if (k == 0) {
		cout << 0 << endl;
		return 0;
	}
	for (int i = 1;i <= n; i++) read(a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1); q.push((node){b[1], 1});
	for (int i = 1;i <= k; i++) {
		node tmp = q.top(); q.pop();
		if (tmp.sum == ans) cnt++;
		else ans = tmp.sum, cnt = 1;
		if (tmp.i == n) continue;
		tmp.i++, tmp.sum += b[tmp.i];
		q.push(tmp); tmp.sum -= b[tmp.i-1]; q.push(tmp);
	}
	build(1, n, 1); dfs(0, ans);
	return 0;
}
```



---

## 作者：lnwhl (赞：5)

## Solution
题目是让求代价第 $k$ 小的方案。典型的分裂搜索（Fracturing Search）的题，~~其实就是广搜~~。

首先解决第一问，方案的代价。

我们先将 $a$ 数组从小到大排一下序。定义状态 $(i,sum)$ 表示前 $i$ 个数（选第 $i$ 个数）代价为 $sum$。每次取队头元素扩展，状态 $(i,sum)$ 可以有两种扩展的方式。
1. 第一种是再加一个元素，因为 $a$ 数组已经有序，所以只需要扩展状态 $(i+1,sum+a_{i+1})$，因为增加其他其他元素一定没有当前更优。
2. 第二种是反悔操作，把第 $i$ 号删除，选择后面的一个元素。同上，也只需考虑选择第 $i+1$ 号元素的情况，扩展状态 $(i+1,sum+a_{i+1}-a_{i})$。

这个过程可以用一个优先队列维护。于是第一问就做完了，复杂度 $O(n\log n+k\log k)$（排序+优先队列）。

但是我们还是有一个问题，这样扩展并没有按照字典序。所以为了输出方案，我们还要用搜索找一下方案。

设上一问已经求出我们要找的是：答案为 $ans$，字典序第 $cnt$ 小的方案。我们用线段树维护一下区间最小值，每次选第一个可行的点扩展，这样就可以保证字典序最小。由于 $cnt \le k$，所以复杂度是 $O(k\log n)$。

总的时间复杂度是 $O(n\log n+k\log k+k\log n)$ 的，这题还是比较卡常的。~~我是开 O2 才过的。~~

代码如下，写了简单的注释。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e6+5;
struct node
{
	int id;ll sum;
	bool operator<(const node &whl)const
	{
		return sum>whl.sum;
	}//优先队列重载运算符，使队列内元素由小到大
};
priority_queue<node>q;
int n,k,a[maxn],t[maxn];
int Min[maxn<<2],cnt=0,stk[maxn],top=0;
ll ans=0;
struct seg
{
	inline int ls(int p){return p<<1;}
	inline int rs(int p){return p<<1|1;}
	void build(int l,int r,int p)//建树
	{
		if(l==r){Min[p]=a[l];return;}
		int mid=l+r>>1;
		build(l,mid,ls(p));build(mid+1,r,rs(p));
		Min[p]=min(Min[ls(p)],Min[rs(p)]);
	}
	inline int query(int l,int r,int p,int now,ll val)//为保证字典序，查找now右边第一个比val小的元素
	{
		if(now<=l)
		{
			if(Min[p]>val)return 0;
			if(l==r)return l;
		}
		int mid=l+r>>1;
		if(now<=mid)
		{
			int w=query(l,mid,ls(p),now,val);
			if(w)return w;
		}
		return query(mid+1,r,rs(p),now,val);
	}
}Seg;//线段树维护区间最小值
void cnt_ans(ll res,int pre)
{
	if(!res)//统计答案
	{
		cnt--;
		if(!cnt)
		{
			for(int i=1;i<=top;i++)
				printf("%d ",stk[i]);
			exit(0);
		}
		return;
	}
	for(int i=pre+1;i<=n;i++)
	{
		i=Seg.query(1,n,1,i,res);//查找i右边第一个比res小的元素
		if(!i)return;stk[++top]=i;//记录答案
		cnt_ans(res-a[i],i);top--;
	}
}
int main()
{
	scanf("%d%d",&n,&k);k--;
	if(k==0){cout<<0;return 0;}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),t[i]=a[i];
	Seg.build(1,n,1);sort(t+1,t+n+1);q.push(node{1,t[1]});
	for(int i=1;i<=k;i++)
	{
		node now=q.top();q.pop();//取队头元素扩展
		if(now.sum==ans)cnt++;
		else ans=now.sum,cnt=1;//统计答案为当前值的个数
		if(now.id==n)continue;
		q.push(node{now.id+1,now.sum+t[now.id+1]});
		q.push(node{now.id+1,now.sum+t[now.id+1]-t[now.id]});//扩展两个节点（见上文）
	}
	cout<<ans<<endl;cnt_ans(ans,0);//暴力搜索
	return 0;
}
```


---

## 作者：Llx2022 (赞：1)

# P5967 [POI2016] Korale

[P5967 [POI2016] Korale](https://www.luogu.com.cn/problem/P5967)

# **题意**

给定 $n$ 个物品，第 $i$ 个物品有价值 $a_i$，请求出第 $k$ 小的方案价值总和，及构成方案的集合，方案不同当且仅当价值以及集合元素不同。

注：
- 若价值相同，则按字典序排序。
- 空集也算是一种方案。

$1\le n\le 10^6$，$1\le k\le 
\min(2^n,10^6)$，$1\le a_i\le 10^9$。

考虑到很难同时求出方案集合和集合元素之和，因此我们不妨将两问分开求。

# **第一问：求第 $k$ 小方案的价值**

枚举的复杂度过于巨大，而他只是让求 $k$ 小，那我们可以类似于贪心的去考虑。

将 $a_i$ 按从小到大排序，次小的集合一定是由价值更小的得到的，我们可以借助小根堆，我们保证堆顶一定是当前最小，因此先往堆里放进最小元素，我们考虑集合得依赖关系，如果对于某个元素，只有该元素成为了前 $k$ 小，他才可能对后续元素有贡献，因此对每个元素 $a_{i+1}$ 有如下情况：
我们借助二元组 $(sum,i)$ 来表示一组集合。

- 加入 $(sum+a_{i+1},i+1)$
- 删除原先并加入 $(sum+a_{i+1}-a_i,i+1)$


我们可以把它考虑为一个 $01$ 串，$0$ 表示不选，$1$ 表示选。那么第一小肯定是 $10000$，经过若干轮，若当前堆顶成为了这样 $10010101$，考虑下一个元素，加入他可能会成为下一个前 $k$ 小，代替他也是可能会成为下一个前 $k$ 小，只有者两种情况会对前 $k$ 小可能有贡献，因此显然这一定是不重不漏的。

**注意这里空集也算一种方案，我们就先让他去掉即可。**

因此第一问我们求得了 $k$ 小价值，以及有几个集合都是这个价值。

# **第二问：求 $ans$ 价值下的第 $cnt$ 个方案**

考虑暴力搜索，如果是暴力的话我们肯定是枚举一个点是否加入集合，然后选编号更小的节点能构成答案的集合，这样枚举的复杂度过高，我们考虑用线段树优化。可以在线段树上二分，具体的就是每次选择离自己最近的且合法的点，因此线段树只需要保存区间最小值即可，如果区间内的最小值都 $>$ 当前需要的贡献，那一定是不合法的，肯定也就不加了，然后我们就可以找到了合法且满足字典序最小的位置，然后依次判断即可，每次找到一个合法的我们就减一下 $cnt$，到 $0$ 的时候一定也就是合法的。
考虑复杂度若某个点每次我们选择一定是最优的，不会超过 $\min(2^n,10^6)$（因为暴力枚举不就是 $2^n$ 次方，而优化相当于去掉了大量的不合法状态顶多也就是只有 $1e6$ 次），因此线段树上二分的复杂度是 $\log n$，然后依次枚举最多也只有 $k$ 次，因此复杂度就是 $k \log n$。

线段树二分具体如下：
```cpp
//我们要查询的是[x,n]合法的最左边的位置
int query(int u,int ql,int x){
    if(ql<=tr[u].l){
        //不合法跳过
        if(tr[u].mn>x) return 0;
        //找到了返回
        if(tr[u].l==tr[u].r) return tr[u].l;
    }
    //以下类似于二分
    int mid=tr[u].l+tr[u].r>>1;
    if(ql<=mid){
        int t=query(u<<1,ql,x);
        if(t) return t;
    }
    return query(u<<1|1,ql,x);
}

```
总的复杂度是 $O(n\log n + k \log k +k\log n)$


**记得开O2**
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1E6+8;
#define int long long
template<typename T>inline void read(T &x){
	x=0;T f=1;char ch=getchar();
	while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=getchar();}
	while(ch>=48&&ch<=57){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
template<typename T>inline void write(T x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+48);
}
int n,k;
int a[N],b[N];
struct node{
	int sum,i;
	bool operator<(const node &a)const{
		return sum>a.sum;
	}
};
priority_queue<node>q;
int ans,cnt;
struct tree{
    int l,r;
    int mn;
}tr[N<<2];
void pushup(int u){
    tr[u].mn=min(tr[u<<1].mn,tr[u<<1|1].mn);
}
void build(int u,int l,int r){
    tr[u].l=l;
    tr[u].r=r;
    tr[u].mn=0;
    if(l==r){
        tr[u].mn=a[l];
        return ;
    }
    int mid=l+r>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    pushup(u);
}
//查询[x,n]最左边的位置
int query(int u,int ql,int x){
    if(ql<=tr[u].l){
        //不合法跳过
        if(tr[u].mn>x) return 0;
        //找到了返回
        if(tr[u].l==tr[u].r) return tr[u].l;
    }
    //以下类似于二分
    int mid=tr[u].l+tr[u].r>>1;
    if(ql<=mid){
        int t=query(u<<1,ql,x);
        if(t) return t;
    }
    return query(u<<1|1,ql,x);
}
int top,st[N];
void dfs(int l,int res){
    if(!res){
        cnt--;
        if(!cnt){
            for(int i=1;i<=top;i++){
                write(st[i]),putchar(' ');
            }
            exit(0);
        }
    }
    for(int i=l+1;i<=n;i++){
        i=query(1,i,res);
        //找不到就返回重新进行查找
        if(!i) return ;
        st[++top]=i;
        dfs(i,res-a[i]);
        --top;
    }
}
signed main(){
	read(n),read(k);
	k--;//减去空集
	if(k==0){
		puts("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		read(a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+n+1);
	q.push({b[1],1});
    //一定是由小的更新大的，因此每次弹出最小，k次之后一定可以找到答案
    //还有是字典序最小
	for(int i=1;i<=k;i++)
	{
		node now=q.top();
        q.pop();
		if(now.sum==ans)cnt++;
		else ans=now.sum,cnt=1;
		if(now.i==n)continue;
        //选当前
		q.push({now.sum+b[now.i+1],now.i+1});
		//反悔操作
        q.push({now.sum+b[now.i+1]-b[now.i],now.i+1});
	}
    build(1,1,n);
    write(ans);
    putchar('\n');
    dfs(0,ans);
	return 0;
}
```

---

## 作者：_Diu_ (赞：1)

暴力做法。

我们发现 $k$ 很小，所以我们只需要暴力的时候保证搜到的每一个情况都是合法的就能保证复杂度。

首先我们考虑二分答案 $x$，要求 $\sum a_ip_i\le x$ 的情况总数，其中 $p_i=\{0,1\}$ 表示一个数选或不选。

我们发现这个事情和字典序、标号啥的没关系，所以可以先把 $a$ 排序（设排序后的是 $b$）。然后我们每次搜到 $x$，还有 $s$ 的额度可以减，那么肯定是比较小的一些点可以减去，比较大的一些点不可以，直接暴力枚举即可。

只要中途出现了 $cnt\ge k$ 就直接返回，保证每次复杂度都是 $O(k)$，这样这部分二分的答案就是 $O(k\log V)$。

```cpp
void dfs(int x,ll s){
	++cnt;
	if(cnt>=k)return;
	for(int i=x;i<=n;i++)
		if(b[i]<=s){
			dfs(i+1,s-b[i]);
			if(cnt>k)return;
		}else break;
}
//以下是二分
bool check(ll x){
	cnt=0;
	dfs(1,x);
	return cnt>=k;
}
ll l=0,r=sum;
while(l+1<r){
	ll mid=l+r>>1;
	if(check(mid))r=mid;
	else l=mid;
}
```

后面先把 $k$ 减去 $s\le r-1$ 的方案数，然后就是考虑字典序从小到大枚举 $s=k$ 的情况。

我们同样考虑枚举到第 $i$ 个数，还剩下 $s$ 的额度，那么能选的肯定是 $a_j\le s$ 的点，然后我们发现为了保证字典序最小，肯定要按照 $j$ 从小到大的顺序枚举。但是如果每次都全部判一遍复杂度会退化，所以考虑用个数据结构维护这件事。可以用倍增或者数据结构上二分每次找到下一个 $\le s$ 的点，也可以采用这届在线段树上找到区间内所有 $\le s$ 的点，时间复杂度都是 $O(k\log n)$。

完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
int n,k,a[N],b[N];
int cnt;
void dfs(int x,ll s){
	++cnt;
	if(cnt>=k)return;
	for(int i=x;i<=n;i++)
		if(b[i]<=s){
			dfs(i+1,s-b[i]);
			if(cnt>k)return;
		}else break;
}
int num[N],tp;
int mn[N<<2];
#define ls (o<<1)
#define rs (o<<1|1)
void build(int o,int l,int r){
	if(l==r)return void(mn[o]=a[l]);
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
	mn[o]=min(mn[ls],mn[rs]);
}
void dfs2(int x,ll s);
void query(int o,int l,int r,int x,int y,ll s){
	if(mn[o]>s)return;
	if(l==r)return dfs2(l,s-mn[o]);
	int mid=l+r>>1;
	if(x<=mid)query(ls,l,mid,x,y,s);
	if(y>mid)query(rs,mid+1,r,x,y,s);
}
void dfs2(int x,ll s){
	num[++tp]=x;
	if(!s){
		--k;
		if(k){--tp;return;}
		for(int i=1;i<=tp;i++)printf("%d ",num[i]);
		exit(0);
	}
	if(x!=n)query(1,1,n,x+1,n,s);
	--tp;
}
bool check(ll x){
	cnt=0;
	dfs(1,x);
	return cnt>=k;
}
signed main(){
	freopen("korale.in","r",stdin);
	freopen("korale.out","w",stdout);
	scanf("%d%d",&n,&k);
	if(k==1)return puts("0\n"),0;
	ll sum=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	ll l=0,r=sum;
	while(l+1<r){
		ll mid=l+r>>1;
		if(check(mid))r=mid;
		else l=mid;
	}
	cnt=0,dfs(1,r-1);
	k-=cnt;
	build(1,1,n);
	printf("%lld\n",r);
	for(int i=1;i<=n;i++)if(a[i]<=r)dfs2(i,r-a[i]);
}
```

---

## 作者：W_ater (赞：0)

[Link](https://www.luogu.com.cn/problem/P5967)

本题解不对题目全面分析，而是通过本题第一问：“求出第 $k$ 小的项链组合价值” 来讲**左孩子右兄弟表示法**这个对于**分裂搜索**的优化方案。

## 分裂搜索（Fracturing Search）

> 请输出第 $k$ 小的项链的价值，以及所用的珠子集合。

看到“第 $k$ 小” 的字眼，这是一道很经典的分裂搜索练习题。

### 要求

以下分裂搜索的要求引用了教练课件的内容。\
分裂搜索要求我们设计一种扩展规则 / 搜索树：

1. 初始状态是全选最小的。
2. 每个状态直接扩展的状态数量不多。（为了时间复杂度）
3. 每个状态直接扩展的状态都大于等于自己。
4. 每个状态都能从初始状态扩展到。
5. 每个状态被扩展的次数唯一。（这一条件并不强制要求，但可能需要哈希）

简而言之我们需要构造一种从最低价值出发，向更高价值的状态前进的不重不漏的搜索树。

### 做法

具体的，我们有一个优先队列，最开始队列里只有价值最小的状态。\
我们做 $k$ 次取出行为，每次我们取出队列里最小的状态，并放入由该状态可以进一步扩展的状态。

以下我每个节点使用一个数列展示当前节点所表示的状态，数字代表使用珠子的下标。\
对于该题，我们考虑 $n=4$ 时的实例：\
我们用朴素构造的搜索树如下：\
![](https://cdn.luogu.com.cn/upload/image_hosting/na8c891b.png)\
这样的搜索树不重不漏的考虑了所有的情况，但我们惊讶的发现它的复杂度是 $O(nk\log (nk))$ 的。\
它的每个节点所有的孩子数（也就是可以扩展的状态数）是 $O(n)$ 级别的~~十分恐怖~~，显然不符合**要求的第二条**，所以我们考虑用**分裂搜索**的好伴侣**孩子兄弟表示法**来优化搜索树。

## 左孩子右兄弟表示法

[OIwiki](https://oi-wiki.org/graph/tree-basic/#%E5%B7%A6%E5%AD%A9%E5%AD%90%E5%8F%B3%E5%85%84%E5%BC%9F%E8%A1%A8%E7%A4%BA%E6%B3%95)

### 简介

左孩子右兄弟表示法（孩子兄弟表示法，树的二叉树表示法……随意你怎么叫）是一种把一般的树转化成二叉树的做法。

### 做法

具体做法顾名思义，将原树上一个节点的第一个子节点作为二叉树中这个节点的左孩子，下一个兄弟节点作为二叉树上这个节点的右孩子。

### 作用

众所周知，二叉树这种特殊的结构拥有许多讨人喜的性质利用这些性质我们可以进一步优化算法。\
并且你在将树变形后，你会意外发现节点的 dfs 序相较于原树是不变的，从某些角度说你仍然拥有部分原树的结构与性质。（尽管在这题中并没有什么显著的作用）\
我们回到题目，将 $a$ 数组排序后我们又有了新的性质，这使得我们可以用孩子兄弟表示法优化搜索树：\
![](https://cdn.luogu.com.cn/upload/image_hosting/am3brswn.png)\
由于排序后我们的数组是单调不降的，这使得我们使用孩子兄弟表示法后的搜索树仍然满足**要求的第三条**，并且我们每个节点的孩子数最多不会超过 $2$，我们就将原本 $O(nk\log (nk))$ 的复杂度优化到了 $O(k\log k)$，第一问总体复杂度为 $O(n\log n+k\log k)$，在卡常后可以通过此题。

## 结

**左孩子右兄弟表示法**优化**分裂搜索**还可以解决更多类似“第 $k$ 小” 的题目，掌握后可以尝试下 [P2048 超级钢琴](https://www.luogu.com.cn/problem/P2048)

感谢阅读。

---

## 作者：qwer6 (赞：0)

## 1. Description

有 $n$ 个带标号的珠子，第 $i$ 个珠子的价值为 $a_i$，现在可以取出一个珠子的子集组成项链，将所有项链以权值为第一关键字，构成项链的珠子编号的字典序为第二关键字排序，求排名为 $k$ 的项链的价值与所用的珠子集合。

注意：空集也算一条项链。

## 2. Solution

这道题要是尝试将两问一起写的话是很难做的 ~~（你怎么知道我打模拟赛时拼尽全力只拿下 70 分？）~~。

所以我们考虑将两问分开写，首先求出排名为 $k$ 的项链的价值，这时的做法类似于使用可持久化左偏树的 $k$ 短路，我们首先将 $k$ 值减一，去掉空集的情况，然后将整个序列排序，使用一个堆维护当前拓展出的所有状态 $(sum,pre)$ 表示已经取得权值为 $sum$，而前一个取的珠子编号为 $pre$，那么在开始的时候向堆中放入一个二元组 $(a_1,1)$，然后每一次取出当前最小的状态 $(sum,pre)$，将其拓展为两个 $(sum+a_{pre+1},pre+1)$ 和 $(sum-a_{pre}+a_{pre+1},pre+1)$，重复 $k$ 次之后就可以得到排名为 $k$ 的项链的权值大小。

考虑证明这样做的正确性，首先证明每一次取出的都是当前未被考虑的所有状态中权值最小的那一个。

这个结论其实是显然的，类似于证明 Dijkstra 的正确性，因为我们已经将 $a$ 排序且所有权值均为正整数，所以根据我们的拓展方式， 由一个状态只能拓展出权值不小于当前状态的新状态，而我们取出了当前所有已经拓展出的状态中权值最小的一个状态，所以后面的状态不管如何拓展，都不可能拓展出一个权值比这个状态更小的新状态了，因此这一部分的正确性得以保证。

还需要证明，这样拓展会不重不漏，这很容易想到，因为对于两条不同的拓展路径，我们总是可以找到这两条不同的拓展路径最后一个相同的状态，因为两条拓展路径不同，而这是最后一个相同状态，因此两条拓展路径一个选择了 $(sum+a_{pre+1},pre+1)$ 一个选择了 $(sum-a_{pre}+a_{pre+1},pre+1)$，那么第一条路径的结果一定包含 $a_{pre}$，而第二条路径的结果一定不含 $a_{pre+1}$，那么这两条路径拓展出的结果就一定不会相同，也就不会重复。而显然，一个状态一定可以由这样的拓展方式得到，因为每一次决策相当于决策第 $pre$ 个珠子是否选择，因而一定可以得到任意的状态，那么就不会遗漏。

然后我们需要求出对应的方案，这里假设已经求出了和答案 $ans$ 权值相同且排名小于等于 $k$ 的方案数 $cnt$，这个可以在求解第一问时顺带求出，这里不过多赘述。

那么可以直接暴力搜索，设定两个参数：$now$ 和 $pre$，分别表示当前取出方案的权值和为 $now$，上一个取数 $pre$，那我们从 $pre+1$ 到 $n$ 依次枚举所有不超过 $ans-now$ 的所有值，尝试取并向后递归，当 $now=ans$ 时表示找到了一种权值与 $ans$ 相同的方案，那么我们把 $cnt$ 减一，如果此时 $cnt$ 等于 $0$，那么就说明已经找到排名为 $k$ 的方案，输出即可。

这么做的正确性显然，因为我们是从前到后枚举所有满足条件的值，所以先找到的方案字典序一定更小，由于权值相同，排名也就更小。

但是暴力枚举显然会 T，需要上个数据结构来维护，使用线段树或倍增 st 表均可。

这样做显然只会递归 $K$ 次，因为每一次递归相当于得到一条项链，这条项链的排名一定小于等于 $K$，那么也就只会递归 $K$ 次。

时间复杂度为 $O((k+n)\log n+k\log k)$。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源与快读快写*/
#define ll long long
#define Node pair<ll,int>
const int N=1e6+5;
int n,k,cnt;
ll ans;
int a[N],b[N],st[25][N];
bool vis[N];
priority_queue<Node,vector<Node>,greater<Node>>q;
int query(int l,int r){
	int j=__lg(r-l+1);
	return min(st[j][l],st[j][r-(1<<j)+1]);
}
int find(int L,int x){
	if(query(L,n)>x)return n+1;
	for(int i=min(20,__lg(n-L)+1);i>=0;i--){
		if(L+(1<<i)-1>n)continue;
		if(st[i][L]>x)
			L+=(1<<i);
	}
	return L;
}
void dfs(int now,int pre){
	if(now==0){
		 cnt--;
		 if(!cnt){
		 	for(int i=1;i<=n;i++)
		 		if(vis[i])write(i),Spa;
		 	Nxt,exit(0);
		 }
		 return ;
	}
	for(int i=pre+1,res;i<=n;i=res+1){
		res=find(i,now);
		if(res>n)return ;
		vis[res]=1;
		dfs(now-a[res],res);
		vis[res]=0;
	}
}
signed main(){
	read(n),read(k);
	for(int i=1;i<=n;i++)read(a[i]);
	if(k==1){
		puts("0");
		exit(0);
	}
	memcpy(b+1,a+1,sizeof(int)*n);
	sort(b+1,b+n+1);
	k--;
	q.push({b[1],1});
	ans=-1;
	while(k--){
		Node tmp=q.top();
		q.pop();
		if(tmp.first==ans)cnt++;
		else ans=tmp.first,cnt=1;
		if(tmp.second==n)continue;
		q.push({tmp.first+b[tmp.second+1],tmp.second+1});
		q.push({tmp.first-b[tmp.second]+b[tmp.second+1],tmp.second+1});
	}
	write(ans),Nxt;
	for(int i=1;i<=n;i++)st[0][i]=a[i];
	for(int i=1;i<=20;i++)
		for(int j=1;j+(1<<i)-1<=n;j++)
			st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i-1)]);
	dfs(ans,0);
}
```

---

## 作者：7KByte (赞：0)

给定 $n$ 个数，可以选则其中的若干个数，代价为选择的数之和。求第 $k$ 小代价和方案。代价相同比较方案的字典序。

首先对将数从小到大排序，然后用堆维护二元组 $(i,j)$ 表示代价为 $i$ ，上一个选择的是第 $j$ 个数。

那么有两种决策，第一种是选择第 $j+1$ 个数，转移到状态 $(i+a_{j+1},j+1)$。第二种是反悔操作，转移到状态 $(i+a_{j+1}-a_j,j+1)$ 。

然后考虑输出方案数。由于 $k\le 10^6$，考虑直接按字典序暴搜出所有前 $k$ 的方案。

那么我们需要支持查询区间中 $\le lim$ 的最左边的位置。

很经典的问题，直接线段树上二分即可。由于区间有一端为右端点，所以直接树状数组上倍增也可以，常数更小。

一个细节是第 $k$ 小的价值为 $Ans$ ，那么我们在 $k$ 中先减去 $<ans$ 的方案数，然后再在 $=ans$ 的方案中选择第 $k$ 个。

为什么要这样做？因为如果这些数比较集中，那么 $=ans$ 的方案数是指数级别的，找到所有 $\le ans$ 的方案再求第 $k$ 大是不现实的。

本题有一个加强版，有兴趣的读者可以思考一下[[CCO2020] Shopping Plans](https://www.luogu.com.cn/problem/P6646)。

时间复杂度 $\mathcal{O}(k\log k+k\log n)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 1000005
#define int long long
using namespace std;
typedef pair<int,int> Pr;
int n,k,u[N],c[N],ans,sta[N],top;
priority_queue<Pr>q;
#define F first
#define S second
struct node{
	int l,r,mn;
}a[N<<2];
#define L a[x].l
#define R a[x].r
#define ls (x<<1)
#define rs (ls|1)
#define M a[x].mn
void build(int x,int l,int r){
	L=l;R=r;
	if(l==r)M=u[l];
	else{
		int mid=(l+r)>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		M=min(a[ls].mn,a[rs].mn); 
	}
}
int ask(int x,int l,int r,int val){
	if(a[x].mn>val)return ~0;
	if(L>=l&&R<=r){
		if(L==R)return L;
		if(a[ls].mn<=val)return ask(ls,l,r,val);
		if(a[rs].mn<=val)return ask(rs,l,r,val);
		return ~0;
	}
	int mid=(L+R)>>1;
	if(mid>=l){
		int cur=ask(ls,l,r,val);
		if(~cur)return cur;
	}
	if(mid<r){
		int cur=ask(rs,l,r,val);
		if(~cur)return cur;
	}
	return ~0;
}
void calc(int x,int res){
	//cout<<"ww "<<res<<" "<<k<<endl;
	//rep(i,1,top)printf("%d ",sta[i]);putchar('\n');
	if(!res){
		k--;
		if(!k)return ;
	}
	if(x>n)return;
	while(x<=n){
		int cur=ask(1,x,n,res);
		if(-1==cur)return;
		sta[++top]=cur;
		calc(cur+1,res-u[cur]);
		if(!k)return;
		top--;
		x=cur+1;
	}
}
void dfs(int x,int res){
	//cout<<"cc "<<res<<endl;
//	rep(i,1,top)printf("%d ",sta[i]);putchar('\n');
	k--;if(!k)return;
	if(x>n)return;
	while(x<=n){
		int cur=ask(1,x,n,res);
		if(-1==cur)return;
		sta[++top]=cur;
		dfs(cur+1,res-u[cur]);
		if(!k)return;
		top--;
		x=cur+1;
	}
}
signed main(){
	scanf("%lld%lld",&n,&k);
	rep(i,1,n)scanf("%lld",&u[i]),c[i]=u[i];
	sort(c+1,c+n+1);
	q.push(make_pair(-c[1],1));
	rep(i,1,k-2){
		Pr cur=q.top();q.pop();
		if(cur.S<n){
			q.push(make_pair(cur.F-c[cur.S+1],cur.S+1));
			q.push(make_pair(cur.F+c[cur.S]-c[cur.S+1],cur.S+1));
		}
	}
	if(k>1)printf("%lld\n",ans=-q.top().F);else printf("%lld\n",ans=0);
	build(1,1,n);dfs(1,ans-1);
	//cout<<"ss "<<k<<endl;
	calc(1,ans); 
	rep(i,1,top)printf("%lld ",sta[i]);putchar('\n');
	return 0;
}
```



---

## 作者：Leasier (赞：0)

前置芝士：[ST 表](https://oi-wiki.org/ds/sparse-table/)

首先第一问不难想到可以先对 $a$ 排序，然后通过下述反悔贪心来解决：

- 维护一个优先队列，队列里每个元素形如 $(lst, sum)$，表示上一个选了 $a_{lst}$，当前和为 $sum$。
- 初始往里面 push 一个元素 $(0, 0)$。
- 循环 $k - 1$ 次，每次执行：
- 取出当前元素 $(lst, sum)$。先判掉 $lst = 0$，此时直接插入 $(1, a_1)$；否则，插入 $(lst + 1, sum + a_{lst + 1})$（即加上 $a_{lst + 1}$）和 $(lst + 1, sum + a_{lst + 1} - a_{lst})$（即加上 $a_{lst + 1}$，删除 $a_{lst}$）。

最终我们取出堆顶，其 $sum$ 即为第一问答案。

对于第二问，考虑抓出前 $k$ 小中子集和与第一问答案相等的方案数，然后由于一共只有至多 $k$ 种情况，我们直接爆搜 + ST 表 + 二分即可。

时间复杂度为 $O((n + k) \log n + n \log k)$。

代码：
```cpp
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef long long ll;

typedef struct Node_tag {
	int lst;
	ll sum;
	Node_tag(){}
	Node_tag(int lst_, ll sum_){
		lst = lst_;
		sum = sum_;
	}
} Node;

int top = 0;
int a[1000007], id[1000007], st[1000007][27], ansb[1000007];
pair<int, int> pr[1000007];
priority_queue<Node> q;

bool operator <(const Node a, const Node b){
	return a.sum > b.sum;
}

inline void init(int n){
	int m = log2(n);
	for (register int i = 1; i <= n; i++){
		st[i][0] = a[i];
	}
	for (register int i = 1; i <= m; i++){
		int id = i - 1, t1 = n - (1 << i) + 1, t2 = 1 << id;
		for (register int j = 1; j <= t1; j++){
			st[j][i] = min(st[j][id], st[j + t2][id]);
		}
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

void write_ll(ll n){
	if (n >= 10) write_ll(n / 10);
	putchar(n % 10 + '0');
}

void write_int(ll n){
	if (n >= 10) write_int(n / 10);
	putchar(n % 10 + '0');
}

inline int get_min(int l, int r){
	int t = log2(r - l + 1);
	return min(st[l][t], st[r - (1 << t) + 1][t]);
}

void dfs(ll val, int n, int &cnt){
	if (val == 0){
		if (--cnt == 0){
			for (int i = 1; i <= top; i++){
				write_int(ansb[i]);
				putchar(' ');
			}
			exit(0);
		}
		return;
	}
	for (int i = ansb[top] + 1; i <= n; ){
		int pos;
		if (val > 1e9){
			pos = i;
		} else {
			int l = i, r = n;
			pos = -1;
			while (l <= r){
				int mid = (l + r) >> 1;
				if (get_min(i, mid) <= val){
					r = mid - 1;
					pos = mid;
				} else {
					l = mid + 1;
				}
			}
			if (pos == -1) break;
		}
		ansb[++top] = pos;
		dfs(val - a[pos], n, cnt);
		top--;
		i = pos + 1;
	}
}

int main(){
	int n = read(), k = read(), cnt;
	ll ansa = 0x8000000000000000ll;
	Node cur;
	for (int i = 1; i <= n; i++){
		a[i] = pr[i].first = read();
		pr[i].second = i;
	}
	sort(pr + 1, pr + n + 1);
	for (int i = 1; i <= n; i++){
		id[pr[i].second] = i;
	}
	init(n);
	q.push(Node(0, 0));
	for (int i = 1; i < k; i++){
		cur = q.top();
		q.pop();
		if (ansa < cur.sum){
			ansa = cur.sum;
			cnt = 1;
		} else {
			cnt++;
		}
		if (cur.lst == 0){
			q.push(Node(1, pr[1].first));
		} else if (cur.lst < n){
			int lst_i = cur.lst + 1;
			q.push(Node(lst_i, cur.sum + pr[lst_i].first));
			q.push(Node(lst_i, cur.sum + pr[lst_i].first - pr[cur.lst].first));
		}
	}
	cur = q.top();
	if (ansa < cur.sum){
		ansa = cur.sum;
		cnt = 1;
	} else {
		cnt++;
	}
	write_ll(ansa);
	putchar('\n');
	dfs(ansa, n, cnt);
	return 0;
}
```

---

