# Nested Segments

## 题目描述

You are given $ n $ segments on a line. There are no ends of some segments that coincide. For each segment find the number of segments it contains.

## 样例 #1

### 输入

```
4
1 8
2 3
4 7
5 6
```

### 输出

```
3
0
1
0
```

## 样例 #2

### 输入

```
3
3 4
1 5
2 6
```

### 输出

```
0
1
1
```

# 题解

## 作者：xiezheyuan (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF652D)

## 题面

在一条直线上有 $n$ 条线段，每条线段用 $(l,r)$ 表示，求每条线段包含多少条其他的线段。

## 思路

### 线段的包含

首先，怎么样的线段是包含关系？

答案：对于一个线段 $(l_1,r_1)$ 与另一个线段 $(l_2,r_2)$，若 $l_1 \ge l_2$ 且 $r_1 \le r_2$，那么这 $(l_1,r_1)$ 就被 $(l_2,r_2)$ 包含。

这很好证明，请读者在草稿纸上画一个数轴（什么，你竟然说你没学过数轴？），自己探究一下。

### 处理数据

首先，如果线段序列按照 $r$ 单一关键字进行升序排序，那么一定有 $r_{i-1} \le r_{i}$，且根据上面的理论， $(l_i,r_i)$ 一定只能包含不超过 $i-1$ 条线段。前面的线段若 $l_j \ge l_i$ 即 $j$ 被 $i$ 包含（当然，这里 $j \lt i$）。

$l$挺大的（$-10^{9} \le l_{i} \lt r_{i} \le 10^{9}$）。 所以需要离散化来缩小范围到$n$的范围（$1 \le n \le 2 \times 10^{5}$）。另外，离散化也可以为之后的求逆序对创造有利条件。

#### 还是不懂为什么要离散化？

树状数组需要开的数组，如果没有离散化那么要开 $2 \times 10^9 $ 以上大小的数组，肯定会MLE。

#### 如何初始化

先创建一个 $l$ 数组的副本，然后每次用二分寻找原来的数组 $l_i$ 的位置替换原来的真实值。

离散化的思想与HASH类似，都是缩小数据范围的一种有力的方法。

### 树状数组出场

经过上面的分析，就能够知道这就是一个求前面有多少个小于这个数的问题（逆序对），可以使用树状数组解答（当然，神犇们用线段树我也不阻止了）。

归并排序每一次都会重新计算，可能会过不去（请读者们试一试）。

至此，我们已经解决该问题，时间复杂度为 $O(n \log n)$。

## 贴上源代码

```cpp
#include <bits/stdc++.h>
#define SIZE int(2*(1e5)+5)
#define inti int i
using namespace std;

int n,yl[SIZE],tree[SIZE],result[SIZE];
struct Segment{
	int l,r,id;
	bool operator<(const Segment csgt) const {
		return (this->r)<(csgt.r);
	}
} sgts[SIZE];

namespace BIT{ // 树状数组求逆序对板子
	int lowbit(int x){
		return x&-x;
	}
	void add(int p, int val){
		while(p<=n) {
			tree[p]+=val;
			p+=lowbit(p);
		}
		return;
	}
	int query(int p){
		int sum=0;
		while(p){
			sum+=tree[p];
			p-=lowbit(p);
		}
		return sum;
	}
}


void lisanhua(){
	sort(yl+1,yl+n+1);
	for(inti=1;i<=n;++i){
		sgts[i].l=lower_bound(yl+1,yl+n+1,sgts[i].l)-yl;
	} 
	sort(sgts+1,sgts+1+n);
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>sgts[i].l>>sgts[i].r;
		sgts[i].id=i;
		yl[i]=sgts[i].l;
	}
	lisanhua();
	for(int i=1;i<=n;i++){
		BIT::add(sgts[i].l,1);
		result[sgts[i].id]=i-BIT::query(sgts[i].l-1);
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",result[i]-1);
	}
	return 0;
}
```
最后啰嗦一句，看样例可以知道，这道题“包含”不包括自己与自己包含，所以一定要减一！

$\color{green}\textbf{AC}$ 了！

---

## 作者：Natsume_Rin (赞：6)

**正解：树状数组**

我们可以考虑一个很 $\text{nice}$ 的解法。

一条线段 $[l_1,r_1]$ 可以包含一条线段 $[l_2,r_2]$，当且仅当 $l_1 \leq l_2 \leq r_2 \leq r_1$。

也就是说，$l$ 和 $r$ 都有限制。所以经常性的一个套路就是将右端点 $r$ 按照升序排列（当然，左端点也可以）。

那么，现在就在有 $r_i \leq r_{i+1}$。那么一条线段 $[l_i,r_i]$ 必定只能包含前面的 $i-1$ 条线段。（因为后面的线段右端点都比它大）。

那么前面的 $i-1$ 条线段如果满足 $l_j  \geq l_i$ 就说明 $j$ 被 $i$ 包含。

观察到 $l$ 比较大，可以离散化之后丢到树状数组中。

每一次查询前面有多少条线段的左端点小于当前的这一条线段的左端点。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int MAXN = 2e5+5;
int sum;
int tree[MAXN], n;
int A[MAXN], len, B[MAXN];
int Len;
int now;
int ans[MAXN];
struct Seg{
	int l, r, id;
	bool friend operator < (const Seg &x, const Seg &y){
		return x.r<y.r;
	}
}s[MAXN];
inline int lowbit(const int x){return x&-x;}
inline void add(int pos, const int val){
	while(pos<=n) tree[pos]+=val, pos+=lowbit(pos);
	return ;
}
inline int ask(int pos){
	sum=0;
	int d=pos;
	while(pos){sum+=tree[pos], pos-=lowbit(pos);}
	return sum;
}
inline int find(const int x){return lower_bound(A+1,A+1+Len,x)-A;}
int main(){
	scanf("%d",&n);
	for(RI i=1;i<=n;++i){
		scanf("%d%d",&s[i].l,&s[i].r);s[i].id=i;
		A[++len]=s[i].l;
	}
	sort(A+1,A+1+len);
	Len=unique(A+1,A+1+len)-A-1;
	for(RI i=1;i<=n;++i) s[i].l=find(s[i].l);
	sort(s+1,s+1+n);now=1;
	for(RI i=1;i<=n;++i){
		add(s[i].l,1);
		ans[s[now].id]=i-ask(s[now].l-1);
		++now;
	}
	
	for(RI i=1;i<=n;++i) printf("%d\n",ans[i]-1);
	return 0;
} 
/*
按照右端点从小到大排序 
4
2 3
3 7
4 6
1 8
0 1 0 0 0 0 0 0
*/
```

---

## 作者：灵茶山艾府 (赞：6)

将区间按右端点从小到大排序，每遍历一个区间就将其左端点添加进权值树状数组中，这样只需统计每个区间的左端点的右侧有多少个已记录的左端点即可。

由于数据范围很大，需要将区间左右端点离散化后再做统计。

AC 代码（Golang）：

```go
package main
import("bufio";."fmt";"os";"sort")

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	Fscan(in, &n)
	ps := make([]struct{ v, i int }, n*2)
	for i := range ps {
		Fscan(in, &ps[i].v)
		ps[i].i = i
	}
	sort.Slice(ps, func(i, j int) bool { return ps[i].v < ps[j].v })
	kth := make([]int, n*2)
	for i, p := range ps {
		kth[p.i] = i + 1
	}

	type pair struct{ l, r, i int }
	a := make([]pair, n)
	for i := range a {
		a[i] = pair{kth[i*2], kth[i*2+1], i}
	}
	sort.Slice(a, func(i, j int) bool { return a[i].r < a[j].r })
	ans := make([]int, n)
	tree := make([]int, n*2+1)
	for i, p := range a {
		c := i
		for j := p.l; j > 0; j &= j - 1 {
			c -= tree[j]
		}
		ans[p.i] = c
		for j := p.l; j <= n*2; j += j & -j {
			tree[j]++
		}
	}
	for _, v := range ans {
		Fprintln(out, v)
	}
}
```


---

## 作者：wfycsw (赞：5)

- ## 大致题意

给出直线上$ n $条线段，询问每条线段包含多少条其他的线段
其中 $n\le200000$ 。

由于 $n$ 十分的大，而且每条线段的序号不影响答案，所以我们可以考虑先将所有线段整理一下，把它们**按 $r_i$ 从大到小排序**，此时我们可以发现这是一个类似于求每个数的**逆序对的**问题， $l_i$ 就是每个数的值。

对于求每个数的逆序对，我们不难想到用**树状数组**来维护。因为每个数的之太大 ($ -10^9\le l \le10^9 )$,便先将   $l_i$ **离散化**,再用树状数组求解即可。

最后奉上AC代码：

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int N=2e5+2;
struct fn{
	int l,r;
}x[N];
struct wu{
	int x,id;
}y[N];
int n,f[N],ans[N];
inline void add(int x,int s){while(x<=n) f[x]+=s,x+=x&-x;}
inline int sum(int x){RI ans=0;while(x) ans+=f[x],x^=x&-x;return ans;}
inline bool cmp(fn x,fn y){return x.r<y.r;}
inline bool cp(wu x,wu y){return x.x<y.x;}
int main(){
	scanf("%d",&n);
	for(RI i=1;i<=n;i=-~i)
		scanf("%d%d",&y[i].x,&x[i].r),y[i].id=i;
	sort(y+1,y+n+1,cp);//排序离散化
	for(RI i=1;i<=n;i=-~i)
		x[y[i].id].l=i;
	sort(x+1,x+n+1,cmp);
	for(RI i=1;i<=n;i=-~i){//求解
		add(x[i].l,1);
		ans[y[x[i].l].id]=i-sum(x[i].l);//记录答案
	}
	for(RI i=1;i<=n;i=-~i)
		printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：wuwenjiong (赞：4)

最近在学数据结构，好不容易做了一道紫题，发个题解纪念一下。

### [题目传送门](https://www.luogu.com.cn/problem/CF652D)
## 思路：
我们一步步来，首先看题目，线段包含关系，画个图，找一下特点。

![](https://cdn.luogu.com.cn/upload/image_hosting/vker2lm4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

由图可知，若线段 $j$ 被线段 $i$ 包含，则需满足 $l_i\le l_j\le r_j\le r_i$ 。

接着想， $l_i\le r_i$ 和 $l_j\le r_j$ 是一定满足的，即我们只需要保证 $l_i\le l_j$ 和 $r_j\le r_i$ 。

一个条件总是要比两个要好求，那么我们不妨将这些线段的左端点或者右端点排一下序，这样就可以提前满足两个条件之一。

继续，排序后怎样维护左端点？（我这里是按右端点排序，排左端点也是同理）先看数据范围， $-10^9\le l_i,r_i\le 10^9$ ，很大，所以要离散化。离散化后就有点类似于一个区间和的问题，用树状数组维护就可以了。

代码如下：
```cpp
#include<iostream>
#include<algorithm>
#define lowbit(x) (x&(-x)) 
using namespace std;
const int MAXN=2e5+2;
struct lfxxx{
	int l,r,op;
}a[MAXN];
int n,k,tree[MAXN<<1],b[MAXN],ans[MAXN];//注意所开数组空间
void add(int x){//树状数组基本修改操作
	for(;x<=n;x+=lowbit(x))
		tree[x]++;
}
int ask(int x){//树状数组查询
	int ans=0;
	for(;x;x-=lowbit(x))
		ans+=tree[x];
	return ans;
}
int find_(int l,int r,int x){//离散化二分查找
	while(l<r){
		int mid=((l+r+1)>>1);
		x<b[mid]?r=mid-1:l=mid;
	}
	return l;
}
bool cmp(lfxxx x,lfxxx y){//按右端点排序
	return x.r<y.r;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;a[i].op=i;//输入，并记录位置
		b[i]=a[i].l;
	}
	sort(b+1,b+n+1);
	k=unique(b+1,b+n+1)-b-1;//STL基本离散化
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		a[i].l=find_(1,k,a[i].l);
	for(int i=1;i<=n;i++){
		ans[a[i].op]=i-ask(a[i].l-1)-1;
		add(a[i].l);
	}
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```
谢谢！！！

---

## 作者：EuphoricStar (赞：2)

## 思路

考虑如果线段 $i$ 能包含线段 $j$ 需要满足什么条件：$l_i \le l_j$ 且 $r_j \le r_i$。所以可以先将所有线段按照左端点从大到小排序，这样就只用考虑第二个条件了。

假设现在遍历到第 $i$ 条线段，想要快速查询前面有多少条线段满足 $r_j \le r_i$，我们可以离散化后使用权值树状数组维护。

然后这题就做完了。时间复杂度 $O(n \log n)$

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 400100;

int n, tot, c[maxn], b[maxn], ans[maxn];
struct node {
	int a, b, id;
} a[maxn];

bool cmp(node a, node b) {
	return a.a > b.a;
}

int lowbit(int x) {
	return x & (-x);
}

void update(int x, int d) {
	for (int i = x; i <= tot; i += lowbit(i)) {
		c[i] += d;
	}
}

int query(int x) {
	int res = 0;
	for (int i = x; i; i -= lowbit(i)) {
		res += c[i];
	}
	return res;
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].a, &a[i].b);
		a[i].id = i;
		b[++tot] = a[i].a;
		b[++tot] = a[i].b;
	}
	sort(b + 1, b + tot + 1);
	tot = unique(b + 1, b + tot + 1) - b - 1;
	for (int i = 1; i <= n; ++i) {
		a[i].a = lower_bound(b + 1, b + tot + 1, a[i].a) - b;
		a[i].b = lower_bound(b + 1, b + tot + 1, a[i].b) - b;
	}
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; ++i) {
		ans[a[i].id] = query(a[i].b);
		update(a[i].b, 1);
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d\n", ans[i]);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：_Yoimiya_ (赞：1)

[题目传送门。](https://www.luogu.com.cn/problem/CF652D)

解题思路：
- 看到线段覆盖，自然而然地想到了数据结构。  

- 众所周知，线段覆盖要满足两个条件，假设线段 $x$ 覆盖了线段 $y$ ，则 $x$ 的左端点必定小于等于 $y$ ， $x$ 的右端点必定大于等于 $y$。  

- 考虑从这个性质入手，先将线段的左端点排个序，这样就满足第一个条件：左端点较小。  

- 枚举左端点，找到右端点中比这条线段小的，自然想到平衡树。  

- 因为不能重复计算右端点，所以每枚举一个左端点，就要删掉对应的右端点。

- 不用平衡树的话，也可以在离散化后选用权值线段树或树状数组。

- 平衡树的时间复杂度为 $O (n \log n)$，可以通过本题。

 AC 代码
 ```cpp
 #include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
const int M(2e5+1);
const double bal_alpha(0.765);
struct node{int l,r,value,size,pos;};
node t[M];int tot,cnt;
vector<int> v;
struct fhq_treap {
	int root;
	inline void data(int p){t[p].size=t[t[p].l].size+t[t[p].r].size+1;return;}
	inline int merge(int x,int y) {
		if(!x||!y) return x+y;
		if(t[x].pos<t[y].pos){t[x].r=merge(t[x].r,y);data(x);return x;}
		else{t[y].l=merge(x,t[y].l);data(y);return y;}
	}
	inline void split(int p,int val,int &u,int &v){
		if(!p){u=v=0;return;}
		if(t[p].value>val){
			v=p;split(t[p].l,val,u,t[p].l);
		}
		else{
			u=p;split(t[p].r,val,t[p].r,v);
		}data(p);
		return;
	}
	inline int newnode(int val) {
		t[++tot].value=val;
		t[tot].pos=rand();
		t[tot].size=1;
		return tot;
	}
	int x,y,z,k;
	inline void ins(int val) {
		split(root,val,x,y);
		root=merge(merge(x,newnode(val)),y);return ;
	}
	inline void del(int val){
		split(root,val,x,z);
		split(x,val-1,x,y);
		y=merge(t[y].l,t[y].r);
		root=merge(merge(x,y),z);
		return ;
	} 
	inline int getrank(int val){
		split(root,val-1,x,y);
		int ans=t[x].size+1;
		root=merge(x,y);return ans;
	}
	inline int gets(int p, int rank) {
		if(rank<=t[t[p].l].size) return gets(t[p].l,rank);
		if(rank==t[t[p].l].size+1) return t[p].value;
		return gets(t[p].r,rank-t[t[p].l].size-1);
	}
	int pre(int val){
		split(root,val-1,x,y);
		int ans=x;while(t[ans].r) ans=t[ans].r;k=t[ans].value;
		root=merge(x,y);
		return ans?k:-inf;
	}
	int nxt(int val){
		split(root,val,x,y);
		int ans=y;while(t[ans].l) ans=t[ans].l;k=t[ans].value;
		root=merge(x,y);
		return ans?k:inf;
	}
};fhq_treap Yoimiya;
struct asks{
	int l,r,id;
};asks q[M];
int n,m,ans[M];
inline bool cmp(asks x,asks y){
	return x.l<y.l;
}
signed main(){
	srand(time(0));
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i(1);i<=n;++i){
		cin>>q[i].l>>q[i].r;q[i].id=i;
		Yoimiya.ins(q[i].r);
	}
	sort(q+1,q+n+1,cmp);
	for(int i(1);i<=n;++i){
		ans[q[i].id]=Yoimiya.getrank(q[i].r)-1;	
		Yoimiya.del(q[i].r);
	}
	for(int i(1);i<=n;++i)
		cout<<ans[i]<<'\n';return 0;
}
 ```

---

## 作者：ollo (赞：1)

-  ### 题意
 在平面上有 $n$ 条线段，问么条直线包含多少条其他线段 ($0 \le\ n \le\ 200000$)。
 
------------

- ### 思路

首先，让我们考虑一个问题，什么叫做包含？

直线 $i$ 包含直线 $j$ 需要满足：

1. $l_i \le l_j$。


2. $r_j \le r_i$。

那么，把每条直线的左端点排序，这样第一个条件就一定会被满足。

对于第二个条件，假设现在遍历到第 $i$ 条线段，想要快速查询前面有多少条线段满足 $r_j \le r_i$，我们可以使用树状数组维护。但是右端点最大会大到 $10^9$，所以还要使用离散化。总时间复杂度 $O(n \log n)$。

------------

- ### 代码如下

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 114;

struct S{
	int x, y;
	int id;
}a[N];

int ans[N], t[N * 4];
int n;

bool cmp1(S a, S b){
	return a.x < b.x;
}

bool cmp2(S a, S b){
	return a.y < b.y;
}
void add(int x,long long l){
	while(x<=n){
		t[x]+=l;
		x+=x&-x;
	}
}

int query(int x){
	int sum=0;
	while(x){
		sum += t[x];
		x-=((x)&(-x));
	}
	return sum;
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i].x >> a[i].y;
		a[i].id = i;
	}
	sort(a + 1, a + n + 1, cmp1);
	for(int i = 1; i <= n; i++){
		a[i].x = i;
	}
	sort(a + 1, a + n + 1, cmp2);
	for(int i = 1; i <= n; i++){
		ans[a[i].id] = (i - 1) - query(a[i].x - 1);
		add(a[i].x, 1);
	}
	for(int i = 1; i <= n; i++){
		cout << ans[i] << '\n';
	}
	return 0;
}
```


---

## 作者：_121017_ (赞：1)

# 思路
这道题首先可以将区间按右端点排序，这样就可以保证 $R_i>R_{i-1}$，这样就可以消除右端点对区间的影响。

接着我们考虑满足一个区间包含另一个区间的条件，不难发现，只有当 $L_i<L_j$ 且 $R_j<R_i$。

$$Ans = \sum_{j=i}^1 L_j>L_i$$

如何快速求出 $Ans$ 呢？显然可以对每个 $L_i$ 离散化，每次就只要求出 $1$ ~ $L_i-1$ 中数的个数，可以利用树状数组或权值线段树。

时间复杂度：$O(n\log n)$。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,ans[N];
struct node{
	int l;
	int r;
	int id;
}in[N];
bool cmp(node a,node b){
	return a.r<b.r;
}
int t[N*4];
int lowbit(int x){
	return x&(-x);
}
void add(int x,int c){
	while(x<=n){
		t[x]+=c;
		x+=lowbit(x);
	}
}
int query(int x){
	int ret=0;
	while(x>0){
		ret+=t[x];
		x-=lowbit(x);
	}
	return ret;
}
bool cmp1(node a,node b){
	return a.l<b.l;
}
void discretization(){
	sort(in+1,in+1+n,cmp1);
	for(int i=1;i<=n;i++){
		in[i].l=i;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&in[i].l,&in[i].r);
		in[i].id=i;
	}
	discretization();
	sort(in+1,in+1+n,cmp);
	for(int i=1;i<=n;i++){
		ans[in[i].id]=i-1-query(in[i].l-1);
		add(in[i].l,1);
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：Epoch_L (赞：0)

## Solution
不难想到对所有线段按右端点排序，那么对于一个线段 $i$ 来说，只有在 $i$ 前面且左端点大于等于 $i$ 才会被包含。形式化来说，求 $j<i$ 且 $l_i\le l_j$ 的数量，这和逆序对很相似，于是将 $l$ 离散化利用树状数组求逆序对即可。

## Code
```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
using namespace std;
using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using ull=unsigned long long;
inline void read(int &x){
  char ch=getchar();
  int r=0,w=1;
  while(!isdigit(ch))w=ch=='-'?-1:1,ch=getchar();
  while(isdigit(ch))r=(r<<1)+(r<<3)+(ch^48),ch=getchar();
  x=r*w;
}
const int N=2e5+7;
struct node{
  int l,r,id;
  bool operator<(const node &b)const{
    return r<b.r;
  }
}a[N];
int n,b[N],len,c[N],ans[N];
int getid(int x){return lower_bound(b+1,b+len+1,x)-b;}
int lowbit(int x){return x&-x;}
void add(int x,int k){
  while(x<=len)c[x]+=k,x+=lowbit(x);
}
int query(int x){
  int ans=0;
  while(x>=1)ans+=c[x],x-=lowbit(x);
  return ans;
}
void init(){
  for(int i=1;i<=n;i++)b[i]=a[i].l;
  sort(b+1,b+n+1);
  len=unique(b+1,b+n+1)-b-1;
}
int main(){
  read(n);
  for(int i=1;i<=n;i++)read(a[i].l),read(a[i].r),a[i].id=i;
  sort(a+1,a+n+1);init();
  for(int i=1;i<=n;i++){
    int k=getid(a[i].l);
    ans[a[i].id]=i-1-query(k-1);
    add(k,1);
  }
  for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
  return 0;
}
```

---

## 作者：蒟蒻炒扇贝 (赞：0)

先来思考一个线段 $[l_1,r_1]$ 被线段 $[l_2,r_2]$ 包含的充要条件是什么。很明显，是 $l_2\le l_1\le r_1\le r_2$。考虑快速求解所有满足这个条件的两条线段的数量。

由于数据保证 $l_i\le r_i$，所以我们只需要考虑满足 $l_2\le l_1$  且 $r_1\le r_2$ 的两条线段即可。对于这种有两种不等式条件约束的题目，我们都有一种类似树状数组求逆序对的套路。

考虑将所有线段按右端点从小到大排序，那我们就能保证对于每一个 $i∈[1,n-1]$，都有 $r_i\le r_{i+1}$。我们再考虑维护一个桶 $b$ ，用 $b_x$ 表示左端点为 $x$ 的线段的出现次数。将排序过的线段依次入桶，由于我们保证 $r_i\le r_{i+1}$，那么目前所有入桶的元素必定满足 $r_1\le r_2$ 这一约束条件。

接下来的问题转化为对于所有桶内的元素，一共有多少 $x$，使得 $x<i$ 且 $l_x\ge l_i$。考虑每次对桶做一个前缀和，设这个前缀和数组为 $pre$，那么 $pre_i$ 便表示桶内元素小于等于 $i$ 的元素个数，$pre_{i-1}$ 便表示桶内元素小于 $i$ 的元素个数。由于我们知道目前桶里的元素总数为 $i-1$，所以 $i-1-pre_{l_i-1}$ 便是所有满足 $l_x\ge l_i$ 的 $x$ 的数量。

用值域树状数组维护这个桶即可，由于 $l_i$ 较大，需要离散化一下。

时间复杂度为 $\mathop{O(n\log n)}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
struct node
{
	int l,r,id;
}a[MAXN];
int cmp(node a,node b)
{
	return a.r<b.r;
}
int n,ans[MAXN],b[MAXN*2],cntb;
struct BIT
{
	int tr[MAXN];
	int lowbit(int x)
	{
		return x&-x;
	}
	void add(int x)
	{
		for(int i=x;i<=cntb;i+=lowbit(i))tr[i]++;
	}
	int ask(int x)
	{
		int ans=0;
		for(int i=x;i;i-=lowbit(i))ans+=tr[i];
		return ans;
	}
}tr;
int gtnum(int x)
{
	return lower_bound(b+1,b+1+cntb,x)-b;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r,a[i].id=i,b[++cntb]=a[i].l;
	sort(b+1,b+1+cntb);
	cntb=unique(b+1,b+1+cntb)-b-1;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		ans[a[i].id]=i-1-tr.ask(gtnum(a[i].l)-1);
		tr.add(gtnum(a[i].l));
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
}
```


---

## 作者：hukk (赞：0)

题目： [CF652D Nested Segments](https://www.luogu.com.cn/problem/CF652D)

-----

题意很简单，不重复。

## 思路

> 对于一条线段 $(L,R)$，查找满足条件 $L \le l \le r \le R$ 的线段 $(l,r)$ 数目 $s_{[L,R]}$。

考虑下面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/eakme2x7.png)

如图，把线段按照右端点排序依次处理，这样就能保证 $r \le R$，我们只需要关注在 $[L,R]$ 区间内**已处理**的线段左端点数目即可。

不难发现这是一个可以通过前缀和处理的数据，即 $s_{[L,R]} = s_{[1,R]} - s_{[1,L-1]}$。

那么，可以快速维护前缀和的数据结构——树状数组就能派上用场了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int tree[200010]; //树状数组
int n;
inline void add(int pos,int num){
	while(pos<=n){
		tree[pos]+=num;
		pos+=pos&(-pos);
	}
}
inline int ask(int pos){
	int ans=0;
	while(pos>=1){
		ans+=tree[pos];
		pos-=pos&(-pos);
	}
	return ans;
}
struct seg{ //表示线段的结构体
	int l,r; //线段左右端点
   int pos; //线段编号（输出答案要用）
	inline bool operator < (seg&b)const{ //重载运算符，sort 要用
		return r<b.r; //按右端点升序
	}
}a[200010];
int ans[200010];
int lisanhua[200010],tot; //离散化
int lsh(int k){ 
	return lower_bound(lisanhua+1,lisanhua+tot+1,k)-lisanhua;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
		a[i].pos=i;
		lisanhua[++tot]=a[i].l;
	}
	sort(a+1,a+n+1); //排序
	sort(lisanhua+1,lisanhua+n+1);
	tot=unique(lisanhua+1,lisanhua+n+1)-lisanhua-1; //离散化去重
	for(int i=1;i<=n;i++){
		ans[a[i].pos]=ask(n)-ask(lsh(a[i].l)-1); //先查询，后添加，答案为已加入的减去不满足要求的
		add(lsh(a[i].l),1); //查询完毕，将该线段加入树状数组
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：huangkerui (赞：0)

放一个线段树的方法。~~（我是不会告诉你我没学好树状数组的。）~~

## [题目](https://www.luogu.com.cn/problem/CF652D)大意：

给出直线上 $ n $ 条线段 $ (l,r) $ ,求每条线段包含多少条其他的线段。


## 分析:

我们思考一下线段 $i$ 满足什么情况下包含线段 $j$ ?

显然，答案为：当 **$ L_i≤L_j≤R_j≤R_i $** 时。

那么，我们可以将 $n$ 条线段按右端点升序排序，那么对于线段 $k$ ,要求的就是在线段 $k$ 左边并且左端点比线段 $k$ 左端点大的线段的个数。即：

 **$ \sum_{i=1}^{k} L_k<L_i $**

由于数据范围较大，所以我们可以在此之前对 $n$ 个线段的左端点离散化。

最后建一个线段树，逐个插入到他们的相对位置，同时统计右端点比它大的线段树即可。


## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define run(i,f,t) for(int i=f;i<=t;i++)
const int N=2e6+10;
struct TREE{
	int l,r,da;
}t[N<<2];
struct READ{
	int l,r,id,p;
}a[N];
int n,ans[N],m;
inline int read(){
	int x=0;bool f=1;char c;c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9')	x=x*10+c-'0',c=getchar();
	return f?x:-x;
}
void build(int p,int l,int r){
	t[p]=TREE{l,r,0};
	if(l==r) return ;
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
}
int charu(int p,int x){
	t[p].da++;
	if(t[p].l==x&&t[p].r==x)	return 0;
	if(t[p<<1].r>=x) return charu(p<<1,x)+t[p<<1|1].da;
	return charu(p<<1|1,x);
}
bool cmp1(READ a,READ b){return a.l<=b.l;}
bool cmp2(READ a,READ b){return a.r<=b.r;}
int main(){
	n=read();
	run(i,1,n){
		a[i].l=read();
		a[i].r=read();
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp1);
	run(i,1,n) a[i].p=i;
	sort(a+1,a+n+1,cmp2);
	build(1,1,n);
	run(i,1,n)	ans[a[i].id]=charu(1,a[i].p);
	run(i,1,n)	cout<<ans[i]<<endl;
	return 0;
}
```


---

