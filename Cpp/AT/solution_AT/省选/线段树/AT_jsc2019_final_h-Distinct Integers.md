# Distinct Integers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_h

長さ $ N $ の数列 $ A_0,A_1,\cdots,A_{N-1} $ があります。 $ Q $ 個のクエリに答えてください。 具体的には、クエリ $ i $ ($ 0\ \leq\ i\ \leq\ Q-1 $) では整数 $ T_i,X_i,Y_i $ が与えられるので、以下のことをしてください。

- $ T_i=0 $ の時: $ A_{X_i} $ を $ Y_i $ で置き換える。
- $ T_i=1 $ の時: 次の条件をみたす整数の組 $ l,r $ ($ X_i\ \leq\ l\ <\ r\ \leq\ Y_i $) の個数を答える。
  - $ A_{l},A_{l+1},\cdots,A_{r-1} $ が全て異なる。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 5\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ N-1 $
- $ 0\ \leq\ T_i\ \leq\ 1 $
- $ 0\ \leq\ X_i\ \leq\ N-1,\ 0\ \leq\ Y_i\ \leq\ N-1 $ ($ T_i=0 $)
- $ 0\ \leq\ X_i\ <\ Y_i\ \leq\ N $ ($ T_i=1 $)
- $ T_i=1 $ をみたす $ i $ が少なくとも $ 1 $ つ存在する。
- 入力される値はすべて整数である。

### Sample Explanation 1

例としてクエリ $ 4 $ を考えます。 このクエリが与えられた時、$ A=(0,1,4,3,4) $ です。 また、条件をみたす $ l,r $ の組は、$ (l,r)=(2,3),(2,4),(3,4),(3,5),(4,5) $ の $ 5 $ 個です。

## 样例 #1

### 输入

```
5 5
0 1 2 1 4
1 0 4
0 3 3
1 0 5
0 2 4
1 2 5```

### 输出

```
8
15
5```

## 样例 #2

### 输入

```
30 30
14 24 18 7 20 10 0 27 27 29 27 20 23 29 27 0 11 10 0 12 19 7 21 12 11 7 27 11 21 0
1 6 21
1 27 29
0 23 21
1 1 5
0 3 24
1 3 6
1 9 16
1 16 26
1 0 11
0 29 27
0 25 29
0 4 24
1 10 23
1 18 24
0 22 14
0 13 10
1 2 29
0 7 12
0 27 14
1 18 20
0 23 7
0 15 20
1 1 24
0 24 7
0 24 20
1 7 16
0 15 27
0 23 10
1 11 13
1 4 8```

### 输出

```
53
3
10
6
23
34
31
57
16
116
3
94
28
3
10```

# 题解

## 作者：qczrz6v4nhp6u (赞：4)

### Solution

好像不难，为啥 *4242。

首先考虑单组询问怎么做。考虑扫描线，扫的时候维护左端点最远能到哪里，然后直接统计即可。

思考一下我们究竟在干什么。设 $p_i$ 表示 $a_i$ 上一次出现的位置（若没有则为 $0$），那么答案即为：

$$\sum_{i=l}^r i-\max(\max_{j=1}^ip_j,l-1)$$

然后就是套路了。

首先 $\sum i$ 和 $\sum \max$ 拆开算，$\sum i$ 是简单的。

然后考虑 $\sum \max$。二分一个 $pos$，满足 $p_{pos}$ 是第一个比 $l-1$ 大的数，这左边的按 $l-1$ 算，右边按 $\max_{j=1}^ip_j$ 算。

现在我们要算的是 $\sum_{i=l}^r\max_{j=1}^ip_j$ 的形式，直接兔队线段树就好了。

时间复杂度 $O(n\log^2 n)$。[submission](https://atcoder.jp/contests/jsc2019-final/submissions/59304073)。

---

## 作者：suzhikz (赞：4)

### 本文主要是对巨佬 UniGravity 做法中的 query 进一步的解说。

> 首先，这个对于答案的转换是好想的，也是好维护的，只需要用 set 对于每个值维护下标，即可做到 $\log n$ 的插入删除，这是简单的。

> 难点在于那个查询，我们并不能像楼房查询一样直接输出根节点，而是应该把对应的查询区间先拆成若干个在线段树上的线段，见下面的代码。

```cpp
void query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r){
		b.push_back(x);c.push_back(l);d.push_back(r);
		return;
	}
	int mid=(l+r)/2;
	if(ql<=mid)query(x*2,l,mid,ql,qr);
	if(qr>mid)query(x*2+1,mid+1,r,ql,qr);
	
}
```

> 这些线段的个数级别是 $\log$ 的，然后显然这些最大值要和 $l-1$ 取 max，所以我们从小到大扫一遍这些区间，并对前面的区间中记录 $\max$，然后对正在统计答案的区间做一次类似于 pushup 的操作，这个操作也是 $\log$ 的，总时间复杂度为 $O(n \log ^2n)$，可以通过。
>
> 然后放下自认为良好的马蜂。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define db double
#define il inline
using namespace std;
void read(int &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
void read(ll &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
const int N=5e5+5;
int n,m;
int a[N];
int pre[N];
ll tree[N*4],maxx[N*4];
ll push2(int x,int l,int r,ll ma){
//	cout<<x<<' '<<l<<' '<<r<<' '<<ma<<endl;
	if(l==r){
		if(l==5){
//			cout<<555<<' '<<maxx[x]<<endl;
		}
		return max(ma,maxx[x]);
	}
	if(maxx[x*2]<ma){
		int mid=(l+r)/2;
//		cout<<ma*(mid-l+1)<<' '<<push2(x*2+1,mid+1,r,ma)<<endl;
		return ma*(mid-l+1)+push2(x*2+1,mid+1,r,ma);
	}else{
		return push2(x*2,l,(l+r)/2,ma)+tree[x]-tree[x*2];
	}
}
void push_up(int x,int l,int r){
	maxx[x]=maxx[x*2];tree[x]=tree[x*2];
	tree[x]+=push2(x*2+1,(l+r)/2+1,r,maxx[x]);
	maxx[x]=max(maxx[x],maxx[x*2+1]);
}
void update(int x,int l,int r,int p,int w){
//	cout<<"aaaaaa"<<x<<' '<<l<<' '<<r<<' '<<p<<' '<<w<<endl; 
	if(l==r){
		maxx[x]=w;
		tree[x]=w;
		return;
	}
	int mid=(l+r)/2;
	if(p<=mid)update(x*2,l,mid,p,w);
	else update(x*2+1,mid+1,r,p,w);
	push_up(x,l,r);
}
void build(int x,int l,int r){
	if(l==r){
		maxx[x]=pre[l];
		tree[x]=pre[l];
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	push_up(x,l,r); 
}
vector<int>b,c,d;
void query(int x,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r){
		b.push_back(x);c.push_back(l);d.push_back(r);
		return;
	}
	int mid=(l+r)/2;
	if(ql<=mid)query(x*2,l,mid,ql,qr);
	if(qr>mid)query(x*2+1,mid+1,r,ql,qr);
	
}
ll query(int l,int r){
	b.clear();c.clear();d.clear();
	query(1,1,n,l,r);
	ll re=0,pre=l-1;
	for(int i=0;i<b.size();i++){
		re+=push2(b[i],c[i],d[i],pre);
//		cout<<"a"<<b[i]<<' '<<c[i]<<' '<<d[i]<<endl;
		pre=max(pre,maxx[b[i]]);
	}
	return re;
}
set<int>s[N];
int main(){
	set<int>::iterator it;
	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(a[i]);
		if(!s[a[i]].empty()){
			it=s[a[i]].end();
			it--;
			pre[i]=*it; 
		}
		s[a[i]].insert(i);
		
	}
//	for(int i=1;i<=n;i++)cout<<pre[i]<<' ';
//	cout<<endl;
	build(1,1,n);
	while(m--){
		int op,l,r;
		read(op);read(l);read(r);
		l++;
		if(op==0){
			s[a[l]].erase(l);
			it=s[a[l]].lower_bound(l);
			if(it!=s[a[l]].end()){
				if(it==s[a[l]].begin())
				update(1,1,n,*it,0);
				else {
					it--;
					int u=*it;
					it++;
					update(1,1,n,*it,u);
				}
			}
			a[l]=r;
			s[r].insert(l);
			it=s[r].lower_bound(l);
//				cout<<"abcd";
			if(it==s[r].begin())update(1,1,n,l,0);
			else{
				it--;
				int u=*it;
				it++;
				update(1,1,n,*it,u);
			}
			it++;
			if(it!=s[r].end()){
				update(1,1,n,*it,l);
			}
		}else{
//			cout<<endl<<endl<<endl;
			printf("%lld\n",1ll*(l+r)*(r-l+1)/2-query(l,r));
		}
	}
//	for(int i=1;i<=n;i++)cout<<a[i]<<endl;
	return 0;
}
```

---

## 作者：UniGravity (赞：3)

## Solution AT_jsc2019_final_h Distinct Integers
起因是在讨论区遇到了这个问题，然后发现了原题。   
感谢提供做法的 @[Accelessar](https://www.luogu.com.cn/user/476985)。   
此做法**无需分块**。

### 题意
给定一个序列 $a$，$q$ 次操作分别为单点修改和查询 $[l,r]$ 内有多少子区间满足该区间内不存在相等的数。   
同时为了方便规定下标从 $1$ 开始。

### 解法
对于值相等的题有一个套路：使用 set 维护 $pre_i$ 表示上一个与 $i$ 相等的值的下标。

考虑将点 $i$ 作为右端点有多少个满足条件的区间。   
先处理询问 $[1,n]$ 的子区间有多少满足。

我们发现如果没有值不能相同的限制，显然有 $i$ 的区间数就是 $i$。  
如果加入相同的限制呢？此时 $i$ 的区间数为 $i-\max_{j\le i}pre_j$，也就是左端点不能小于前缀的 $pre$ 最大值。

到区间 $[l,r]$ 上，答案则为 $\frac{(l+r)(r-l+1)}{2}-\sum_{i=l}^r\max_{j\le i}pre_j$。我们只需要求出区间内前缀最大值的和即可。

说到前缀最大值，可以想到经典题[楼房重建](https://www.luogu.com.cn/problem/P4198)。只需再记一个 $mx$ 表示区间最大值，线段树 pushup 时二分即可。

```cpp
int mx[N*5];ll sum[N*5];
il ll getval(int x,int l,int r,int lim){
    if(l==r)return max(mx[x],lim);
    int mid=(l+r)>>1;
    if(mx[x<<1]<lim)return 1ll*(mid-l+1)*lim+getval(x<<1|1,mid+1,r,lim);
    else return getval(x<<1,l,mid,lim)+sum[x]-sum[x<<1];
}
il void pushup(int x,int l,int r){
    int mid=(l+r)>>1;
    sum[x]=sum[x<<1]+getval(x<<1|1,mid+1,r,mx[x<<1]);
    mx[x]=max(mx[x<<1],mx[x<<1|1]);
}
```

对于查询操作，还需要注意的是前缀最大值还要与询问的 $l-1$ 取 max。

```cpp
struct Dat{int x,l,r;};
vector<Dat>v;
il void query(int x,int l,int r,int bg,int ed){
    if(bg<=l&&r<=ed){v.eb((Dat){x,l,r});return;}
    int mid=(l+r)>>1;
    if(bg<=mid)query(x<<1,l,mid,bg,ed);
    if(mid<ed)query(x<<1|1,mid+1,r,bg,ed);
}
il ll query(int bg,int ed){
    v.clear();query(1,1,n,bg,ed);
    ll sum=0;
    int premax=bg-1;
    forv(i,v.size()){
        sum+=getval(v[i].x,v[i].l,v[i].r,premax);
        premax=max(premax,mx[v[i].x]);
    }
    return sum;
}
```

其它的操作在[完整代码](https://www.luogu.com/paste/wztir8fg)里。

---

## 作者：Purslane (赞：0)

# Solution

线段树单侧递归板子题。

先考虑如果 $q=1$，怎么做到线性。

对于每个位置，记 $lst_p$ 为上一个和 $a_p$ 相同的值出现的位置，记其前缀最大值数组 $LST_p = \max_{i \le p} lst_i$。

则 $\sum_{p=1}^n p -LST_p$ 就是答案。正确性是显然的。

发现原题等价于：给定 $lst$ 数组，进行单点修改，或者查询 $\sum_{i=l}^r \max\{p,\max_{l \le j \le i}lst_j\}$。

看到前缀最大值这种东西，考虑“单侧递归线段树”（套用不了 after god 了 /ll）。

发现和楼房重建简直一模一样，直接维护即可。

怎么有人写线段树不 build 的，你省选就是因为这个调了一年啊啊啊啊。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10;
int n,q,a[MAXN],lst[MAXN];
set<int> st[MAXN];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
int mx[MAXN<<2];
ll sum[MAXN<<2];
inline ll calc(int k,int l,int r,int p) {
	if(l==r) return max(p,lst[l]);
	if(p>mx[k]) return 1ll*p*(r-l+1);
	if(p>mx[lson]) return 1ll*p*(mid-l+1)+calc(rson,mid+1,r,p);
	return sum[k]-sum[lson]+calc(lson,l,mid,p);
}
void push_up(int k,int l,int r) {return mx[k]=max(mx[lson],mx[rson]),sum[k]=sum[lson]+calc(rson,mid+1,r,mx[lson]),void();}
void build(int k,int l,int r) {
	if(l==r) return mx[k]=sum[k]=lst[l],void();
	build(lson,l,mid),build(rson,mid+1,r);
	return push_up(k,l,r),void();
}
int MX;ll ANS;
void query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return ANS+=calc(k,l,r,MX),MX=max(MX,mx[k]),void();
	if(x<=mid) query(lson,l,mid,x,y);
	if(y>mid) query(rson,mid+1,r,x,y);
	return ;
}
void modify(int k,int l,int r,int pos,int v) {
	if(l==r) return mx[k]=lst[l]=sum[k]=v,void();
	if(pos<=mid) modify(lson,l,mid,pos,v);
	else modify(rson,mid+1,r,pos,v);
	return push_up(k,l,r),void();
}
int calc_lst(int pos) {
	auto it=st[a[pos]].find(pos);
	if(it==st[a[pos]].begin()) return 0;
	return *(--it);	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i],st[a[i]].insert(i);
	ffor(i,0,n-1) {int lid=0;for(auto id:st[i]) lst[id]=lid,lid=id;}
	build(1,1,n);
	ffor(i,1,q) {
		int op,x,y;
		cin>>op>>x>>y;
		if(op==0) {
			vector<int> cg;
			x++,cg.push_back(x);
			auto it=st[a[x]].find(x);
			if(it!=--st[a[x]].end()) cg.push_back(*(++it));
			st[a[x]].erase(x),a[x]=y,st[a[x]].insert(x);
			it=st[a[x]].find(x);
			if(it!=--st[a[x]].end()) cg.push_back(*(++it));
			for(auto id:cg) modify(1,1,n,id,calc_lst(id));
		}
		else {
			x++,MX=x-1,ANS=0;
			query(1,1,n,x,y);
			cout<<1ll*(x+y)*(y-x+1)/2-ANS<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：JPGOJCZX (赞：0)

节选自：[线段树进阶应用学习笔记（四）：单侧递归问题](https://www.luogu.com.cn/article/j32irhv0)

[安利一下我的博客](https://www.cnblogs.com/JPGOJCZX/p/18752595)

~~第一届日本最强程序员学生锦标赛决赛~~

首先，这道题目要求的是区间有多少个子区间没有重复数字，如果我们记录一下每个数字 $i$ 前一次出现的位置 $pre_i$，那么问题就变成了有多少个子区间包括 $i$ 但不包括 $pre_i$，由于区间内每个数字都不能重复出现，于是固定住 $r$，$l$ 最左就只能到 $\max_{i = L}^r pre_i + 1$，此时对于答案的贡献就是 $r - l + 1$，于是答案就变成了 $\displaystyle\sum_{i = L}^R (i - \max_{j = L}^i pre_j) = \frac{(L + R)(R - L + 1)}{2} - \sum_{i = L}^R \max_{j = L}^i pre_j$，于是问题就变成了求区间 $[l, r]$ 中前缀 $pre$ 的最大值的和。

现在我们将问题转化成了区间前缀最大值问题，依然考虑使用线段树单侧递归的写法。考虑 $id$ 的两个儿子以及 $id$ 的右儿子的两个儿子 $ls$ 和 $rs$，如果 $id$ 的左儿子的区间最大值比 $id$ 的右儿子的大，那么 $id$ 的右儿子的所有前缀最大值都无法对答案造成贡献，于是 $id$ 的答案就是 $id$ 的左儿子的答案加上 $id$ 的右儿子的长度乘以 $id$ 的左儿子的区间最大值。

考虑 $ls$ 的区间最大值小于 $id$ 的左儿子的这种情况，此时 $ls$ 的所有前缀最大值都无法保留，于是答案加上 $ls$ 的长度乘上 $id$ 的左儿子的区间最大值，往 rs 递归即可。

最后考虑 $ls$ 的区间最大值大于 $id$ 的左儿子的这种情况，由于如果 $rs$ 的一个前缀最大值大于 $ls$ 的区间最大值，那么一定会在 $id$ 的前缀最大值中被保留下来，而且 $id$ 的左儿子的答案等于 $ls$ 的答案加上在 $ls$ 遮挡下 $rs$ 的答案，因此将答案加上 `t[id << 1 | 1].ans - t[ls].ans`，往 $ls$ 递归即可。

修改操作可以给每种值开一个集合，记录这种值出现的下标。将 $a_x$ 修改为 $y$ 时，只用将 $x$ 在 $a_x$ 集合中的后继的 $pre$ 修改为 $x$ 的前驱，并将 $x$ 的 $pre$ 修改为它在 $y$ 集合中的前驱，将 $x$ 后继的 $pre$ 修改为 $x$ 即可。

注意一下，如果最大的 $pre_i$ 都小于 $L$，那么 $l$ 只能取到 $L$，不能更小，因此需要特判一下。那么这道题就在 $O(n \log^2 n)$ 的时间复杂度内解决。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e5 + 9;
struct Node{
	int ans, maxn;
} t[N << 2];
int a[N], pre[N], n, q;
int prequery(int id, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr)
		return t[id].maxn;
	int mid = (l + r) >> 1, ans = 0;
	if(ql <= mid)
		ans = prequery(id << 1, l, mid, ql, qr);
	if(qr > mid)
		ans = max(ans, prequery(id << 1 | 1, mid + 1, r, ql, qr));
	return ans;
}
int pushup(int now, int l, int r, int cmp){
	int res = 0;
	while(true){
		if(l == r){
			res += max(t[now].maxn, cmp);
			break;
		}
		int mid = (l + r) >> 1;
		if(cmp > t[now << 1].maxn){
			res += (mid - l + 1) * cmp;
			now = now << 1 | 1;
			l = mid + 1;
		} else {
			res += t[now].ans - t[now << 1].ans;
			now = now << 1; 
			r = mid;
		}
	}
	return res;
}
void build(int id, int l, int r){
	if(l == r){
		t[id].maxn = t[id].ans = pre[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
	t[id].maxn = max(t[id << 1].maxn, t[id << 1 | 1].maxn);
	t[id].ans = t[id << 1].ans + pushup(id << 1 | 1, mid + 1, r, t[id << 1].maxn);
}
void modify(int id, int l, int r, int q, int qx){
	if(l == r){
		t[id].ans = t[id].maxn = qx;
		return;
	}
	int mid = (l + r) >> 1;
	if(q <= mid)
		modify(id << 1, l, mid, q, qx);
	else
		modify(id << 1 | 1, mid + 1, r, q, qx);
	t[id].maxn = max(t[id << 1].maxn, t[id << 1 | 1].maxn);
	t[id].ans = t[id << 1].ans + pushup(id << 1 | 1, mid + 1, r, t[id << 1].maxn);
}
int query(int id, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr)
		return pushup(id, l, r, l - 1 ? prequery(1, 1, n, 1, l - 1) : 0);
	int mid = (l + r) >> 1, ans = 0;
	if(ql <= mid)
		ans += query(id << 1, l, mid, ql, qr);
	if(qr > mid)
		ans += query(id << 1 | 1, mid + 1, r, ql, qr);
	return ans;
}
vector <int> s[N];
signed main(){
	scanf("%lld%lld", &n, &q);
	for(int i = 1; i <= n; i++)
		s[i].push_back(0);
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
		a[i]++;
		s[a[i]].insert(lower_bound(s[a[i]].begin(), s[a[i]].end(), i), i);
		pre[i] = *--lower_bound(s[a[i]].begin(), s[a[i]].end(), i);
	}
	build(1, 1, n);
	while(q--){
		int opt, x, y;
		scanf("%lld%lld%lld", &opt, &x, &y);
		x += 1;
		y += !opt;
		if(opt == 0){
			if(upper_bound(s[a[x]].begin(), s[a[x]].end(), x) != s[a[x]].end()){
				modify(1, 1, n, *upper_bound(s[a[x]].begin(), s[a[x]].end(), x), *--lower_bound(s[a[x]].begin(), s[a[x]].end(), x));
				pre[*upper_bound(s[a[x]].begin(), s[a[x]].end(), x)] = *--lower_bound(s[a[x]].begin(), s[a[x]].end(), x);
			}
			s[a[x]].erase(lower_bound(s[a[x]].begin(), s[a[x]].end(), x));
			s[y].insert(lower_bound(s[y].begin(), s[y].end(), x), x);
			pre[x] = *--lower_bound(s[y].begin(), s[y].end(), x);
			modify(1, 1, n, x, *--lower_bound(s[y].begin(), s[y].end(), x));
			if(upper_bound(s[y].begin(), s[y].end(), x) != s[y].end()){
				modify(1, 1, n, *upper_bound(s[y].begin(), s[y].end(), x), x);
				pre[*upper_bound(s[y].begin(), s[y].end(), x)] = x;
			}	
			a[x] = y;
		} else {
			modify(1, 1, n, x, x - 1);
			printf("%lld\n", (x + y) * (y - x + 1) / 2 - query(1, 1, n, x, y));
			modify(1, 1, n, x, pre[x]);
		}
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

$\textbf{AT\_jsc2019\_final\_h}$

> - 给定序列 $a$ 和 $q$ 次操作，操作有两种类型：
>    - 修改：给定 $x,y$，将 $a_x$ 修改为 $y$。
>    - 查询：给定 $L,R$，查询有多少对 $(l,r)$ 满足 $L \le l \le r \le R$ 且 $a_{l,l+1,\ldots,r}$ 两两不同。
> - $1 \le n,q \le 5 \cdot 10^5$，时间限制 $10.0$ 秒。

这道题在 clist 上的评分是 $^*4200$，但是感觉真实难度不到 $^*2700$。

先考虑一个暴力一些的做法，思考如何在 $\mathcal O(nq)$ 的时间复杂度内解决。

考虑扫描线扫 $r$，则合法的 $l$ 应满足 $l > \max\limits_{j=L}^r \{lst_j\}$，否则就会有重复的数字（$lst_j$ 指最大的 $p < j$ 满足 $a_p = a_j$）。我们扫的过程中维护 $t = \max\limits_{j=L}^r \{lst_j\}$ 即可，单组询问 $\mathcal O(n)$，修改用 set 快速修改 $lst$ 的值，时间复杂度 $\mathcal O(\log n)$。

这个东西线段树维护起来好像比较困难，官方题解给出了 $\mathcal O(\log^2 n)$ 处理单组询问的方法，但是写的比较抽象加上是全日文的我完全没看懂。那我们考虑暴力一些的算法：**分块**。

设块长为 $B$，散块显然直接暴力。当前到了一个整块，且已经维护好了一个 $t$。分讨块内的 $\max$：

- $\max \le t$。此时的贡献直接是块长乘以 $t$。
- $\max > t$。找到分界点 $p$，此时后半部分的计算与 $t$ 无关，可以维护块内答案的后缀和直接计算，前半部分贡献为 $(p - al +1) \cdot t$，其中 $al$ 是块的左端点。找 $p$ 可以线段树二分。

那么总复杂度即为 $\mathcal O(n\log n + qB + \dfrac{qn \log n}{B})$，取 $B = \sqrt {n \log n}$ 的复杂度即为 $\mathcal O(n \log n + q \sqrt{n \log n})$，~~跑得比 $\text{poly log}$ 的官方题解还快~~。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 27.03.2024 14:13:34
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
#include <atcoder/segtree>
using ll = long long;
const int N = 5e5+5,B = 1600;
using namespace std;
int T,n,q,a[N],l,r,op,lst[N],al[N],ar[N],id[N],sum[N],pre[N],t; set<int> s[N];
int po(int a,int b){return max(a,b);} int e(){return 0;}
bool f(int x){return x <= t;}
int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> q;
    for(int i = 1;i <= n;i ++) cin >> a[i],id[i] = (i - 1) / B + 1,
        al[id[i]] = (al[id[i]] ? al[id[i]] : i),ar[id[i]] = i;
    atcoder::segtree<int,po,e> seg(n + 3);
    for(int i = 0;i <= n;i ++) s[i].insert(0),s[i].insert(n + 1);
    for(int i = 1;i <= n;i ++) s[a[i]].insert(i);
    for(int i = 1;i <= n;i ++) seg.set(i,pre[i] = (*--s[a[i]].lower_bound(i)));
    auto init = [&](int d){
        sum[al[d]] = pre[al[d]] + 1; int mx = pre[al[d]] + 1;
        for(int i = al[d] + 1;i <= ar[d];i ++) mx = max(mx,pre[i] + 1),
            sum[i] = sum[i-1] + mx;
    }; for(int i = 1;i <= id[n];i ++) init(i);
    while(q --){
        cin >> op >> l >> r, ++ l;
        if(!op){
            auto upd = [&](int l,int r){
                int d = id[l];
                pre[l] = r,seg.set(l,r),init(d); 
            };
            auto &x = s[a[l]]; x.erase(l); auto it = x.lower_bound(l),ti = it --;
            upd(*ti,*it),a[l] = r; 
            auto &y = s[r]; auto itt = y.lower_bound(l),tii = itt --;
            upd(l,*itt),upd(*tii,l),y.insert(l);
        }else {
            t = l - 1; ll ans = 1ll * (l + r + 2) * (r - l + 1) / 2;
            int p = id[l],q = id[r];
            auto bf = [&](int l,int r){
                for(int i = l;i <= r;i ++) t = max(t,pre[i]),ans -= t + 1;
            };
            if(p == q)
                bf(l,r),cout << ans << "\n";
            else{
                bf(l,ar[p]);
                for(int i = p + 1;i <= q - 1;i ++){
                    int pos = seg.max_right<f>(al[i]);  
                    if(pos > ar[i])
                        ans -= 1ll * (t + 1) * (ar[i] - al[i] + 1);
                    else ans -= 1ll * (t + 1) * (pos - al[i]),t = seg.prod(pos,ar[i] + 1),
                         ans -= sum[ar[i]] - (pos == al[i] ? 0 : sum[pos - 1]);
                }bf(al[q],r);
                cout << ans << "\n";
            }
        }
    }
}
```

---

