# [ARC180D] Division into 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc180/tasks/arc180_d

長さ $ N $ の整数列 $ A=(A_1,A_2,\cdots,A_N) $ が与えられます． 以下の $ Q $ 個のクエリに答えてください．

- $ i $ 番目のクエリ: 整数 $ L_i,R_i $ が与えられる． $ B=(A_{L_i},A_{L_i+1},\cdots,A_{R_i}) $ に対して次の問題を解け．
  - $ B $ を $ 3 $ つの非空な連続部分列に分割する．各連続部分列についてその要素の最大値を求める．これらの値の総和としてあり得る最小値を求めよ． なお，問題の制約から $ B $ の長さは $ 3 $ 以上になるため，$ 3 $ つの非空な連続部分列に分割する方法は必ず $ 1 $ つ以上存在する．

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 250000 $
- $ 1\ \leq\ Q\ \leq\ 250000 $
- $ 1\ \leq\ A_i\ \leq\ 10^8 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- $ R_i-L_i\ \geq\ 2 $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ 1 $ つめのクエリについて説明します． $ B=(4,3,1,1,4,5,2) $ です． これを $ (4,3),(1,1),(4,5,2) $ と分解すると，各連続部分列の最大値は $ 4,1,5 $ となり，その総和は $ 10 $ になります． この総和が $ 10 $ より小さくなる方法は存在しないので，このクエリの答えは $ 10 $ になります．

## 样例 #1

### 输入

```
7 5
4 3 1 1 4 5 2
1 7
2 4
3 5
1 5
4 7```

### 输出

```
10
5
6
9
8```

## 样例 #2

### 输入

```
10 15
8 3 8 10 1 5 3 1 6 4
4 6
2 5
6 9
8 10
2 9
4 10
1 5
1 8
1 3
4 8
1 10
2 10
6 10
2 6
2 6```

### 输出

```
16
14
12
11
17
17
19
14
19
14
17
17
12
16
16```

# 题解

## 作者：小超手123 (赞：8)

### 题意：

给你一个长度为 $N$ 的整数序列 $A=(A_1,A_2,\cdots,A_N)$ 。请回答下列 $Q$ 个问题。

- $i$ \-th 查询：给定整数 $L_i$ 和 $R_i$ 。求解下面 $B=(A_{L_i},A_{L_i+1},\cdots,A_{R_i})$ 的问题。
  - 将 $B$ 分成三个非空的连续子序列。对于每个连续子序列，让我们找出其元素的最大值。求这些最大值之和的最小值。在这里，问题的限制条件迫使 $B$ 的长度至少为 $3$ ，因此总有至少一种方法将其分成三个非空的连续子序列。

### 分析：

设 $A,B,C$ 分别表示依次划分的三段区间，对于整个序列的最大值 $mx$，显然 $A,B,C$ 的代价至少有一个等于 $mx$。分类讨论拆解这个问题。

### $A=mx$：

不妨假设 $B$ 到 $C$ 的分界点被固定，因为 $A$ 的代价已经确定，那么 $B$ 长度越小，$B$ 的代价就越小，总代价就越小。因此 $B$ 的长度恰好为 $1$。记 $x$ 表示 $\min_{i=l}^{r}i[a_{i}=mx]$，那么总代价即为：
$$
mx+\min_{i=x+1}^{r-1}(a_{i}+\max_{j=i+1}^{r}a_{j})
$$
记 $f_{i}=a_{i}+\max_{j=i+1}^{r}a_{j}$，使用扫描线维护固定 $r$ 时，所有的 $f_{i}$（$1\le i < r$）。

配合单调栈使用，当 $r \leftarrow r+1$ 时，假设新加入单调栈的 $a_{r}$ 弹出了 $s_{top}$（$a_{r}\ge a_{s_{top}}$），那么在线段树上就是 $f_{i} \leftarrow f_{i}-a_{s_{top}}+a_{r}$，其中 $i \in [s_{top-1},s_{top})$。然后再单独更新一下 $f_{r-1}$。

### $B=mx$：

不难发现此时 $A,C$ 的长度为 $1$ 时，一定是最优的，因为 $A$ 的左端点，$B$ 的右端点都固定了，长度越小，代价越小。这是区间 RMQ 问题。ST 表或线段树就能解决。

### $C=mx$：

与 $A=mx$ 是对称问题，序列翻转后再使用 $A=mx$ 的算法即可。



时间复杂度 $O((n+Q) \log n)$，代码虽然长但不用动脑子。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 300005
using namespace std;

int n, Q;
int a[N], L[N], R[N], ans[N];

struct Tree1 { //区间加; 区间min 
	int c[N * 4], tag[N * 4];
	
	void clear() {
		memset(c, 0, sizeof(c));
		memset(tag, 0, sizeof(tag));
	}
	void pushup(int u) {
		c[u] = min(c[u * 2], c[u * 2 + 1]);
	}
	void maketag(int u, int x) {
		c[u] += x;
		tag[u] += x; 
	}
	void pushdown(int u) {
		if(!tag[u]) return;
		maketag(u * 2, tag[u]);
		maketag(u * 2 + 1, tag[u]);
		tag[u] = 0;
	}
	
	void update(int u, int L, int R, int l, int r, int x) {
		if(l <= L && R <= r) {
			maketag(u, x);
			return;
		}
		if(R < l || r < L) return;
		int mid = (L + R) / 2;
		pushdown(u);
		update(u * 2, L, mid, l, r, x);
		update(u * 2 + 1, mid + 1, R, l, r, x);
		pushup(u);
	}
	
	int query(int u, int L, int R, int l, int r) {
		if(l <= L && R <= r) return c[u];
		if(r < L || R < l) return 1e15;
		int mid = (L + R) / 2;
		pushdown(u);
		return min(query(u * 2, L, mid, l, r), query(u * 2 + 1, mid + 1, R, l, r));
	}
}t1;


struct node {
	int id, Max;
	friend node operator + (node A, node B) {
		if(A.Max > B.Max) return A;
		else if(A.Max < B.Max) return B;
		else return ((node){min(A.id, B.id), A.Max});
	}
};

struct Tree2 { //区间max 
	node c[N * 4];
	void pushup(int u) {
		c[u] = c[u * 2] + c[u * 2 + 1];
	}
	void build(int u, int L, int R) {
		if(L == R) {
			c[u].id = L;
			c[u].Max = a[L];
			return;
		}
		int mid = (L + R) /2;
		build(u * 2, L, mid);
		build(u * 2 + 1, mid + 1, R);
		pushup(u);
	}
	node query(int u, int L, int R, int l, int r) {
		if(l <= L && R <= r) return c[u];
		if(r < L || R < l) return (node){0, (int)-1e15};
		int mid = (L + R) / 2;
		return query(u * 2, L, mid, l, r) + query(u * 2 + 1, mid + 1, R, l, r);
	}
}t2;

vector<int>p[N];
int S[N], top;
void Sol1() { //解决 A=mx 或 C=mx 的问题 
	t1.clear();
	S[0] = 1; top = 0;
	for(int i = 1; i <= n; i++) p[i].clear();
	for(int i = 1; i <= Q; i++) p[R[i]].push_back(i);
	for(int i = 1; i <= n; i++) {
		while(top && a[i] >= a[S[top]]) {
			t1.update(1, 1, n, S[top - 1], S[top] - 1, -a[S[top]] + a[i]);
			top--;
		}
		S[++top] = i;
		if(i > 1) t1.update(1, 1, n, i - 1, i - 1, a[i - 1] + a[i]);
		for(auto Pos : p[i]) {
			node Get = t2.query(1, 1, n, L[Pos], R[Pos]);
			int x = Get.id;
			//cout << Get.Max << endl;
			//for(int z = x + 1; z <= i - 1; z++) cout << z << " : " << t1.query(1, 1, n, z, z) << endl;
			if(x + 1 <= i - 1) ans[Pos] = min(ans[Pos], Get.Max + t1.query(1, 1, n, x + 1, i - 1));
		}
	}
}


void Sol2() { //解决 B=mx 的问题 

	for(int i = 1; i <= Q; i++)
		ans[i] = min(ans[i], a[L[i]] + a[R[i]] + t2.query(1, 1, n, L[i] + 1, R[i] - 1).Max);
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> Q;	
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= Q; i++) {
		cin >> L[i] >> R[i];
		ans[i] = 1e18;
	}
	
	
	t2.build(1, 1, n);
	
	Sol1();
	
	Sol2();
	
	reverse(a + 1, a + n + 1);
	for(int i = 1; i <= Q; i++) {
		int l = L[i], r = R[i];
		L[i] = n - r + 1;
		R[i] = n - l + 1;
	}
	t2.build(1, 1, n);
	Sol1();
	
	for(int i = 1; i <= Q; i++) cout << ans[i] << endl;
	return 0;
}
/*
5 1
4 3 1 1 4
1 5
*/

/*
7 1
4 3 1 1 4 5 2
1 7
*/
```

---

## 作者：Exp10re (赞：5)

非常好题目，使我写出三百行线段树。

### 解题思路

考虑数列最大值，记为 $A_{mpos}$，又有 $A_{Lmpos}$ 为下标最小的最大值，$A_{Rmpos}$ 为下标最大的最大值在哪一个区间，根据区间分讨。

下记查询区间为 $[L,R]$，三个区间按照左右排列最大值分别为 $x_1,x_2,x_3$。

#### $A_{mpos}$ 在第二个区间。  

比较简单的分讨情况。

注意到此时 $x_2=A_{mpos}$，$x_1\geq A_L$，$x_3\geq A_R$，此时选择 $[L,L]$ 作为第一个区间，$[L+1,R-1]$ 作为第二个区间，$[R,R]$ 作为第三个区间一定最优，答案为 $A_{mpos}+A_{L}+A_{R}$。

#### $A_{mpos}$ 在第一个区间。  

此时 $x_1=A_{Lmpos}$，$x_3\geq A_R$，钦定第一个区间为 $[L,R_1]$，第二个区间为 $[R_1+1,R_2]$，则有 $R_1\geq Lmpos$。  

显然因为 $x_1$ 不会改变，故在不考虑第三个区间的情况下若确定 $R_2$ 则第二个区间取 $[R_2,R_2]$，第一个区间取 $R_1=R_2-1$ 一定最优。

考虑我们需要计算 $R_2$ 在区间 $[l,r]$ 内的结果需要做什么：

- 首先我们会得知 $\max\limits_{r\lt i \leq n} A_i$ 的值，记为 $sufmax_{r+1}$。
- 我们需要计算其中的一个边界值 $pos$，满足 $\max\limits_{pos\lt i \leq r} A_i \leq sufmax_{r+1}$ 且 $A_{pos} \gt sufmax_{r+1}$，这个值可能不存在，此时记为 $l-1$。
- 则 $R_2$ 在区间 $[l,r]$ 内的最大答案为：

$$\max(\min\limits_{pos\lt i \leq r} A_i+sufmax_{r+1},\min\limits_{l\leq i \leq pos} (A_i+\max\limits_{i\lt j \leq r} A_j))$$

- 考虑如何求得 $pos$：若我们可以得知 $[l,r]$ 中所有后缀最大值，$pos$ 可以二分求得。
- 提前对于每一个 $pos\in [l,r]$ 预处理 $\min\limits_{pos\lt i \leq r} A_i+sufmax_{r+1}$ 以及 $\min\limits_{l\leq i \leq pos} (A_i+\max\limits_{i\lt j \leq r} A_j)$ 可以在得知 $pos$ 的情况下 $O(1)$ 得知答案。
- 则时间复杂度为 $O(w\log n)$ 级别，其中 $w$ 为划分块的个数。不难发现可以使用线段树维护，将单次询问复杂度降到 $O(\log_2 n)$。

#### $A_{mpos}$ 在第三个区间。  

与 $A_{mpos}$ 在第一个区间相互对称，沿用即可。

如此我们便做到了 $O(n\log n)$ 预处理 $O(q\log_2 n)$ 查询。

实现较复杂，放一个代码上来。

[Submission.](https://atcoder.jp/contests/arc180/submissions/58594046)

---

## 作者：born_to_sun (赞：4)

提供一个树上倍增的做法。

### 性质观察
假设我们划分为的三个区间分别为 $[l_1,r_1], [l_2,r_2], [l_3,r_3]$，设 $mx=\max_{i=l}^r a_i$，即区间最大值，由于最大值一定在三个区间中的一个，并且最大值所在区间的权值必然为 $mx$，所以不妨按照 $mx$ 所在区间的位置进行分类讨论。
1. $mx$ 在区间 $[l_1,r_1]$ 中，与情况三相同，不再赘述。
2. $mx$ 在区间 $[l_2,r_2]$ 中。这时，$[l_1,r_1]$ 中一定包含 $a_l$，$[l_3,r_3]$ 中一定包含 $a_r$，所以要想最小化权值，只能令 $l_1=r_1, l_3=r_3$。
3. $mx$ 在区间 $[l_3,r_3]$ 中。类似的，如果我们在区间 $[l_1,r_2]$ 中寻找一个最大值，记为 $mx2$，既然我们想最小化权值，就一定会让其中一个区间长度为 $1$。如果 $l_1=r_1$，那么我们一定也会让 $l_2=r_2$，因为第二个区间至少需要包含 $l_2$，而最三个区间无论怎么变，权值都不变；如果 $l_2=r_2$，问题似乎变得非常棘手，我们需要借助其他算法求解。

以上所有情况中，除了第三点的最后一部分外，都可以 $O(1)$ 计算（使用 st 表），下面我们重点考虑最后这一步怎么办。

### 重难点
假设我们将 $i$ 向第一个满足 $a_i\geq a_j$ 且 $i\lt j$ 的 $j$ 连边，我们将得到一棵树。

在这棵树上，对于节点 $u$ 和父亲 $fa_u$，当 $r_1\in [u,fa_u)$ 时，第一个区间的权值不变，始终为 $a_u$，而第二个区间最优策略就是选择 $\min_{i=u+1}^{fa_u}a_i$，那么我们就可以指定树上这个点的答案为 $a_u+\min_{i=u+1}^{fa_u}a_i$。

而查询一定是一条树上的链，据此可以使用树上倍增维护。

时间复杂度 $O(m\log n)$
### 小技巧
+ 如果你觉得文章开头提到的第一种情况和第三种情况都写一遍很麻烦，可以尝试**将询问离线，然后对 $a$ 数组翻转，对查询翻转，再调用同一个函数计算**即可，这样可以大大降低代码长度，只是需要注意清空。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
const int S=5e5+5;
const int inf=1e9;
int a[N];
int n,m;
int st[N][20][2];
int Max(int x,int y){
	return (a[x]<a[y]? y: x);
}
int Min(int x,int y){
	return (a[x]<a[y]? x: y);
}
void st_init(){
	for(int i=1;i<=n;i++) st[i][0][0]=st[i][0][1]=i;
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j][0]=Min(st[i][j-1][0],st[i+(1<<(j-1))][j-1][0]);
			st[i][j][1]=Max(st[i][j-1][1],st[i+(1<<(j-1))][j-1][1]);
		}
	}
}
int st_q(int l,int r,int op){
	if(l>r&&!op) return 0;
	int k=log2(r-l+1);
	return (op? Max(st[l][k][op],st[r-(1<<k)+1][k][op]): Min(st[l][k][op],st[r-(1<<k)+1][k][op]));
}
struct no{
	int l,r,val;
}c[N],d[N];
int res[N];
struct NO{
	int ans,son;
}f[N][20];
int dep[N],fa[N][20];
int sk[N],top;
NO merge(NO x,NO y,int mid){
	return NO{min({x.ans,y.ans,a[x.son]+a[mid]}),y.son};
}
void init(){
	for(int j=1;(1<<j)<=n;j++){
		f[0][j]={inf,0};
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1];
			f[i][j]=merge(f[i][j-1],f[fa[i][j-1]][j-1],fa[i][j-1]);
		}
	}
}
int query(int u,int v){
	int k=log2(n);
	NO res={inf,0};
	for(int i=k;i>=0;i--){
		if(dep[u]-(1<<i)>=dep[v]){
			res=merge(res,f[u][i],u);u=fa[u][i];
		}
	}
	return res.ans;
}
void solve(){
	top=0;sk[++top]=0;
	a[0]=inf;dep[0]=1;
	for(int i=n;i>=1;i--){
		while(top&&a[sk[top]]<a[i]) top--;
		fa[i][0]=sk[top];dep[i]=dep[sk[top]]+1;
		f[i][0].ans=a[st_q(i+1,sk[top]-1,0)]+a[i];
		f[i][0].son=i;
		sk[++top]=i;
	}
	init();
	for(int i=1;i<=m;i++){
		if(!c[i].l) continue;
		int l=c[i].l,r=c[i].r,val=c[i].val;
		res[i]=min(res[i],val+query(l,r));
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	st_init();
	for(int i=1;i<=m;i++){
		res[i]=inf;
		int l,r;cin>>l>>r;
		int p=st_q(l,r,1);
		if(l+1<p){
			res[i]=min(res[i],a[l]+a[l+1]+a[p]);
			c[i]=no{l,p,a[p]};
		}
		if(p<r-1){
			res[i]=min(res[i],a[r]+a[r-1]+a[p]);
			d[i]=no{p,r,a[p]};
		}
		if(l<p&&p<r) res[i]=min(res[i],a[l]+a[r]+a[p]);
	}
	solve();
	reverse(a+1,a+1+n);
	st_init();
	for(int i=1;i<=m;i++){
		if(!d[i].l){c[i].l=0;continue;}
		c[i].r=n-d[i].l+1;c[i].l=n-d[i].r+1;c[i].val=d[i].val;
	}
	solve();
	for(int i=1;i<=m;i++) cout<<res[i]<<'\n';
	return 0;
}
```

---

## 作者：Hadtsti (赞：3)

### 题意简述

- 给定长为 $n$ 的正整数序列 $a_i$。$q$ 次询问将 $a_l,a_{l+1},\cdots,a_{r-1},a_r$ 分割为 $3$ 个连续的部分后每部分最大值之和的最小值。

- $1\le n,q\le 2.5\times10^5$。

### 题目分析

考虑从询问区间里的最大值入手，显然它一定为某一段的最大值。如果钦定其在第二段中（在合法的前提下），则第二段的最大值为该值，而一、三段显然在取得更短时其最大值不会更大，因此我们只需要给它们分别留下左右端点一个数，再将三个值加起来即可。

最大值在第一段和第三段中的情况是对称的，在此我们只考虑在第一段中的情况。不难发现第二段只留一个数是最优的，原因如下：若第二段有大于一个数，则把除了最右数之外的数划给第一段时，第一段最大值不变，而第二段最大值一定不会增加，显然更优。此时，问题就转化为第二段取哪一个数最优。设询问中的 $a_l\sim a_r$ 中最大值为 $a_{mx}$，则答案即为 $\displaystyle a_{mx}+\min_{i=mx+1}^{r-1}(a_i+\max_{j=i+1}^ra_j)$。

这个问题可用扫描线解决。回顾 [CF997E](https://www.luogu.com.cn/problem/CF997E) 那题，可以用类似的方法，对 $r$ 维扫描线，用线段树配合单调栈维护 $i$ 处的 $\displaystyle a_i+\max_{j=i+1}^ra_j$ 值，具体细节可参考那题。

最大值在第三段的情况只需要把上述过程反过来。至此我们解决了该题目，时间复杂度为 $O((n+q)\log n)$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,C,l,r,a[250010],st[250010][19],ans[250010],MX[250010];
int stk[250010],tp;
vector<pair<int,int> >Q[250010],P[250010];
int mn[1000010],tag[1000010];
void addtag(int p,int tg)
{
	mn[p]+=tg;
	tag[p]+=tg;
}
void pushdown(int p)
{
	if(tag[p])
	{
		addtag(p<<1,tag[p]);
		addtag(p<<1|1,tag[p]);
		tag[p]=0;
	}
}
void change1(int p,int x,int v,int l=1,int r=n)
{
	if(l==r)
	{
		mn[p]=v;
		return;
	}
	pushdown(p);
	int mid=l+r>>1;
	if(mid>=x)
		change1(p<<1,x,v,l,mid);
	else
		change1(p<<1|1,x,v,mid+1,r);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
void change2(int p,int L,int R,int v,int l=1,int r=n)
{
	if(L>R)
		return;
	L=max(L,1);
	R=min(R,n);
	if(l>=L&&r<=R)
		return addtag(p,v);
	pushdown(p);
	int mid=l+r>>1;
	if(mid>=L)
		change2(p<<1,L,R,v,l,mid);
	if(mid<R)
		change2(p<<1|1,L,R,v,mid+1,r);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
}
int query(int p,int L,int R,int l=1,int r=n)
{
	if(L>R)
		return 0x3f3f3f3f;
	L=max(L,1);
	R=min(R,n);
	if(l>=L&&r<=R)
		return mn[p];
	pushdown(p);
	int mid=l+r>>1,res=0x3f3f3f3f;
	if(mid>=L)
		res=query(p<<1,L,R,l,mid);
	if(mid<R)
		res=min(res,query(p<<1|1,L,R,mid+1,r));
	return res;
}
int ask(int l,int r)
{
	int k=__lg(r-l+1);
	return a[st[l][k]]>a[st[r-(1<<k)+1][k]]?st[l][k]:st[r-(1<<k)+1][k];
}
int main()
{
	scanf("%d%d",&n,&q);
	C=__lg(n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		st[i][0]=i;
	}
	for(int i=1;i<=C;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			st[j][i]=(a[st[j][i-1]]>a[st[j+(1<<i-1)][i-1]]?st[j][i-1]:st[j+(1<<i-1)][i-1]);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		int x=ask(l,r);
		ans[i]=(x>l&&x<r)?a[l]+a[r]+a[x]:0x3f3f3f3f;
		MX[i]=a[x];
		if(x<r-1)
			Q[r].push_back({x+1,i});
		if(x>l+1)
			P[l].push_back({x-1,i});
	}
	memset(mn,0x3f3f3f3f,sizeof mn);
	for(int i=1;i<=n;i++)
	{
		if(i>1)
			change1(1,i-1,a[i-1]+a[i]);
		while(tp&&a[stk[tp]]<a[i])
		{
			change2(1,stk[tp-1],stk[tp]-1,a[i]-a[stk[tp]]);
			tp--;
		}
		stk[++tp]=i;
		for(pair<int,int>j:Q[i])
			ans[j.second]=min(ans[j.second],query(1,j.first,i-1)+MX[j.second]);
	}
	memset(mn,0x3f3f3f3f,sizeof mn);
	memset(tag,0,sizeof tag);
	stk[tp=0]=n+1;
	for(int i=n;i>=1;i--)
	{
		if(i<n)
			change1(1,i+1,a[i]+a[i+1]);
		while(tp&&a[stk[tp]]<a[i])
		{
			change2(1,stk[tp]+1,stk[tp-1],a[i]-a[stk[tp]]);
			tp--;
		}
		stk[++tp]=i;
		for(pair<int,int>j:P[i])
			ans[j.second]=min(ans[j.second],query(1,i+1,j.first)+MX[j.second]);
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
} 
```

---

## 作者：KingPowers (赞：2)

好题，来一发题解。

不妨先分析下操作本身的性质，我们先单独把 $B$ 序列抽出来，假设为 $B_1,B_2,\ldots,B_M$，设 $B$ 序列中的最大值是 $B_P$，那么显然 $B_P$ 一定会成为某一段的最大值而贡献到答案中。

然后比较自然地想法就是分 $B_P$ 的位置进行讨论，设分成的三个子段从左到右分别为 $X,Y,Z$：

- 如果 $B_P$ 落在了 $Y$ 段中，是最好处理的，因为此时 $Y$ 中已经有了全局最大值，继续把 $Y$ 段扩大肯定答案不劣，所以我们可以把 $Y$ 一直扩大，$X$ 和 $Y$ 一定就只剩下序列的两端。

- 如果 $B_P$ 落在了 $X$ 段中，类似地分析，把 $X$ 段扩大答案一定不劣，此时一定可以让 $Y$ 段的长度为 $1$，否则可以再丢给 $X$，确定 $Y$ 的位置即可统计答案。

- 如果 $B_P$ 落在了 $Z$ 段中，同上，有 $Y$ 段长度为 $1$。

所以每次询问我们就需要考虑上面这三种情况，而对于第一种情况我们使用 ST 表维护出最大值的位置即可求出答案，第二种和第三种情况是完全对称的，因此下面主要讲解第二种情况。

假设询问的区间为 $[L,R]$，同样地我们需要找到最大值的位置 $P\in[L,R]$，那么对于第一种情况我们在 $[P+1,R]$ 中枚举 $Y$ 段的位置，贡献就是：

$$
A_P+\min_{j=P+1}^R\{A_j+\max_{k=j+1}^RA_k\}
$$

容易发现 $R$ 是定住的，因此我们考虑离线下来对 $R$ 做扫描线，开 vector 将每个询问挂在右端点上，然后扫描线枚举 $R$，用线段树配合单调栈维护出左边每个位置作为 $j$ 的答案，询问时直接取区间最小值即可。

对于上面的第三种情况，方法完全一致，换成倒着扫对 $L$ 做扫描线即可。

时间复杂度 $O(N\log N+Q\log N)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 5e5 + 5;
struct qry{int l, r, w, id;}; vector<qry> vec1[N], vec2[N];
int n, m, a[N], lg[N], st[20][N], top, stk[N], ans[N], L[N], R[N];
int tr[N << 2], tag[N << 2];
#define ls now << 1
#define rs now << 1 | 1
void pushup(int now){tr[now] = min(tr[ls], tr[rs]);}
void update(int now, int k){tr[now] += k; tag[now] += k;}
void pushdown(int now){
	if(tag[now]){
		tr[ls] += tag[now]; tag[ls] += tag[now];
		tr[rs] += tag[now]; tag[rs] += tag[now];
		tag[now] = 0;
	}
}
void build(int l, int r, int now){
	tr[now] = tag[now] = 0;
	if(l == r) return tr[now] = a[l], void();
	int mid = (l + r) >> 1;
	build(l, mid, ls); build(mid + 1, r, rs);
	pushup(now);
}
void modify(int x, int y, int k, int l, int r, int now){
	if(x <= l && r <= y) return update(now, k);
	pushdown(now); int mid = (l + r) >> 1;
	if(x <= mid) modify(x, y, k, l, mid, ls);
	if(y > mid) modify(x, y, k, mid + 1, r, rs);
	pushup(now);
}
int query(int x, int y, int l, int r, int now){
	if(x <= l && r <= y) return tr[now];
	pushdown(now); int mid = (l + r) >> 1, ans = 1e18;
	if(x <= mid) ans = min(ans, query(x, y, l, mid, ls));
	if(y > mid) ans = min(ans, query(x, y, mid + 1, r, rs));
	return ans;
}
#undef ls
#undef rs
int query(int l, int r){
	int k = lg[r - l + 1], lp = st[k][l], rp = st[k][r - (1 << k) + 1];
	return a[lp] > a[rp] ? lp : rp;
}
void Solve(){
	cin >> n >> m;
	For(i, 1, n) cin >> a[i], st[0][i] = i;
	for(int i = 1; (1 << i) <= n; i++)
		for(int j = 1; j + (1 << i) - 1 <= n; j++){
			int lp = st[i - 1][j], rp = st[i - 1][j + (1 << i - 1)];
			st[i][j] = a[lp] > a[rp] ? lp : rp; 
		}
	lg[0] = -1; For(i, 1, n) lg[i] = lg[i >> 1] + 1;
	For(i, 1, m){
		int l, r; cin >> l >> r;
		int p = query(l, r), res = 1e18;
		if(p != l && p != r) res = min(res, a[p] + a[l] + a[r]);
		if(p < r - 1) res = min(res, a[p] + a[r - 1] + a[r]);
		if(p > l + 1) res = min(res, a[p] + a[l + 1] + a[l]);
		ans[i] = res;
		if(p < r - 1) vec1[r].push_back({p + 1, r - 1, a[p], i});
		if(p > l - 1) vec2[l].push_back({l + 1, p - 1, a[p], i});
	}
	top = 0; build(1, n, 1);
	For(i, 1, n){
		while(top && a[stk[top]] < a[i]) modify(stk[top - 1] + 1, stk[top], -a[stk[top]], 1, n, 1), top--;
		stk[++top] = i; modify(stk[top - 1], i, a[i], 1, n, 1);
		for(auto [l, r, w, id] : vec1[i]) ans[id] = min(ans[id], w + query(l, r, 1, n, 1));
	}
	top = 0; build(1, n, 1);
	Rof(i, n, 1){
		while(top && a[stk[top]] < a[i]) modify(stk[top], stk[top - 1] - 1, -a[stk[top]], 1, n, 1), top--;
		stk[++top] = i; modify(i, stk[top - 1], a[i], 1, n, 1);
		for(auto [l, r, w, id] : vec2[i]) ans[id] = min(ans[id], w + query(l, r, 1, n, 1));
	}
	For(i, 1, m) cout << ans[i] << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：2020kanade (赞：2)

前情提要：因为过于劳累昏睡过头导致 unr 参加 ARC180，索性哪个题顺眼开哪个，但是赛后才出。

题目：ARC180D

考虑这个划分的性质：一个显然的点是，区间最大值所在的块的贡献是一定的，可以进对此行讨论。

考虑集合最值函数即 $\max$ 或 $\min$ 本身的性质：其一定随着集合元素增加而单调不劣化，反之，若不断取出元素，则其一定单调不优化。因此，显然当区间最大值落在中间这一块时，由于剩下的两块各有一个确定的一定存在的元素（区间头与区间尾），根据上述结论，我们极大化区间最大值所在的中间这一块即可，即此时的划分方式为区间头尾作为左右两块、剩余的一个区间作为中间一块。

那么，考虑区间最大值落在左右两块，即其产生贡献的区域为一个前缀或后缀的情况，显然这两种情况是对称的，只需要讨论一种，这里讨论落在前缀。

去掉区间最大值产生贡献的前缀后，问题拆解为将一个区间分为两段，最小化二者最大值之和。仿照上面的套路继续考虑这个区间最大值的贡献，答案显然是前缀或后缀分割出一个点（长度为一的前缀或后缀，下同），点之外的后缀或前缀包含区间最大值在内，二者取优。

进一步思考，发现后缀内部的两种划分情况可以合并：考虑后缀的划分形式为取一个长度为一的后缀分出，且此时为最优状态，设询问区间为 $[l,r]$，那么中间的一块的贡献一定 $\ge a_{r-1}$，考虑用前缀划分的形式再次取到这种情况，此时中间的一块一定只包含 $a_{r-1}$，答案一定不劣，证毕。由此我们只考虑前缀划分策略即可。

那么，枚举询问区间内部最大值所在前缀长度作为分界点，此时问题转化为询问若干后缀的答案的最优值，考虑如何维护。

较为形式化地，我们考虑维护 $ans_{i,r}$ 为以 $r$ 为右端点，$i$ 作为前缀划分方式下的中间块内唯一的点时，中间块和右侧块对答案的贡献，那么找到区间 $[l,r]$ 中最靠左的最大值下标 $pos$，这种情况下答案为 $\min_{i=l}^{i\le pos}\{a_i\}+\min_{i=pos+1}^{i\le r-1}\{ans_{i,r}\}$。取最左侧的最大值为 $pos$ 的原因是通过考虑更大的决策集合来保证总的决策集合不漏。

考虑 $r\leftarrow r+1$，拆解 $ans_{i,r}=a_i+\max_{j=i+1}^{j\le r}\{a_j\}$，每次新增的值影响的部分为 $\max_{j=i+1}^{j\le r}\{a_j\}$。考虑用区间加区间 $\min$ 线段树维护某个确定的 $r$ 下的所有 $ans_{i,r}$，用单调栈维护每个下标上一个值不小于它的位置，联动单调栈进行更新即可。

对于区间最大值落在后缀的情况，由于对称性，翻转序列和询问区间后做一遍前缀的情况即可。

每个询问的三种情况取最优者即为答案。

时间复杂度 $\Theta((n+q)\log n)$。

笔者比较懒，直接开了两颗线段树和两个 ST 表且包含大段复制粘贴，更优美的实现应该是存在的。

```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
struct xds
{
	int ls[N*2],rs[N*2];ll mx[N*2],tag2[N*2];
	void down(int x)
	{
		if(tag2[x])
		{
			mx[ls[x]]+=tag2[x],tag2[ls[x]]+=tag2[x];
			mx[rs[x]]+=tag2[x],tag2[rs[x]]+=tag2[x];
			tag2[x]=0;
		}
	}
	void up(int x)
	{
		mx[x]=min(mx[ls[x]],mx[rs[x]]);
	}
	int rt,ct;
	void build(int &x,int l,int r)
	{
		x=++ct;
		if(l==r) return;int mid=(l+r)>>1;
		build(ls[x],l,mid);build(rs[x],mid+1,r);
	}
	void change(int x,int l,int r,int ql,int qr,ll v2)
	{
		if(ql<=l&&r<=qr)
		{
			tag2[x]+=v2,mx[x]+=v2;return;
		}
		int mid=(l+r)>>1;down(x);
		if(ql<=mid) change(ls[x],l,mid,ql,qr,v2);
		if(mid+1<=qr) change(rs[x],mid+1,r,ql,qr,v2);
		up(x);
	}
	ll ask(int x,int l,int r,int ql,int qr)
	{
		if(ql<=l&&r<=qr) return mx[x];
		int mid=(l+r)>>1;down(x);ll ret=GEH;
		if(ql<=mid) ret=min(ret,ask(ls[x],l,mid,ql,qr));
		if(mid+1<=qr) ret=min(ret,ask(rs[x],mid+1,r,ql,qr));
		return ret;
	}
};
xds s1,s2;
struct stt
{
	ll st[22][N];int stp[22][N],_p;
	void init_st(ll *A,int _n)
	{
		_p=(__lg(_n))+1;
		for(int i=1;i<=_n;++i) st[0][i]=A[i],stp[0][i]=i;
		for(int i=1;i<=_p;++i) for(int j=1;j+(1<<i)-1<=_n;++j)
		{
			if(st[i-1][j]>=st[i-1][j+(1<<i-1)])
			{
				st[i][j]=st[i-1][j],stp[i][j]=stp[i-1][j];
			}
			else
			{
				st[i][j]=st[i-1][j+(1<<i-1)],stp[i][j]=stp[i-1][j+(1<<i-1)];
			}
		}
	}
	ll stask1(int l,int r)
	{
		int _q=__lg(r-l+1);
		return max(st[_q][l],st[_q][r-(1<<_q)+1]);
	}
	int stask2(int l,int r)
	{
		int _q=__lg(r-l+1);
		if(st[_q][l]>=st[_q][r-(1<<_q)+1]) return stp[_q][l];
		else return stp[_q][r-(1<<_q)+1];
	}
};
stt st1,st2;
struct asks
{
	int l,r,id;ll ans;
	bool operator <(const asks& a) const
	{
		return r<a.r;
	}
}as1[N],as2[N];
ll ans[N];
ll a1[N],a2[N];int lst1[N],lst2[N];int stk[N],top;
void solve()
{
	cin>>n>>q;
	for(int i=1;i<=n;++i) cin>>a1[i],a2[i]=a1[i];
	reverse(a2+1,a2+n+1);
	for(int i=1;i<=q;++i)
	{
		as1[i].id=as2[i].id=i;
		cin>>as1[i].l>>as1[i].r;
		as2[i].l=n-as1[i].r+1,as2[i].r=n-as1[i].l+1;
	}
	sort(as1+1,as1+q+1);int ptr=1;
	st1.init_st(a1,n);s1.build(s1.rt,1,n);
	for(int i=1;i<=n;++i)
	{
		s1.change(1,1,n,i,i,a1[i]);
		while(top&&a1[stk[top]]<a1[i])
		{
			if(stk[top]>1)
			s1.change(1,1,n,max(1,lst1[stk[top]]-1),stk[top]-1,-a1[stk[top]]);
			--top;
		}
		if(!top) lst1[i]=1;
		else lst1[i]=stk[top]+1;
		stk[++top]=i;
		if(i>1) s1.change(1,1,n,max(1,lst1[i]-1),i-1,a1[i]);
		while(ptr<=q&&as1[ptr].r<i) ++ptr;
		while(ptr<=q&&as1[ptr].r==i)
		{
			int nid=as1[ptr].id;int l=as1[ptr].l,r=as1[ptr].r;
			ans[nid]=a1[l]+a1[r]+st1.stask1(l+1,r-1);
			int pos=st1.stask2(l,r);if(pos>=r-1)
			{
				ans[nid]=min(ans[nid],st1.stask1(l,r-2)+a1[r-1]+a1[r]);
				++ptr;continue;
			}
			ans[nid]=min(ans[nid],st1.stask1(l,pos)+s1.ask(1,1,n,pos+1,r-1));
			++ptr;
		}
	}
	top=0,ptr=1;sort(as2+1,as2+q+1);
	st2.init_st(a2,n);s2.build(s2.rt,1,n);
	for(int i=1;i<=n;++i)
	{
		s2.change(1,1,n,i,i,a2[i]);
		while(top&&a2[stk[top]]<a2[i])
		{
			if(stk[top]>1)
			s2.change(1,1,n,max(1,lst2[stk[top]]-1),stk[top]-1,-a2[stk[top]]);
			--top;
		}
		if(!top) lst2[i]=1;
		else lst2[i]=stk[top]+1;
		stk[++top]=i;
		if(i>1) s2.change(1,1,n,max(1,lst2[i]-1),i-1,a2[i]);
		while(ptr<=q&&as2[ptr].r<i) ++ptr;
		while(ptr<=q&&as2[ptr].r==i)
		{
			int nid=as2[ptr].id;int l=as2[ptr].l,r=as2[ptr].r;
			int pos=st2.stask2(l,r);if(pos>=r-1)
			{
				ans[nid]=min(ans[nid],st2.stask1(l,r-2)+a2[r-1]+a2[r]);
				++ptr;continue;
			}
			ans[nid]=min(ans[nid],st2.stask1(l,pos)+s2.ask(1,1,n,pos+1,r-1));
			++ptr;
		}
	}
	for(int i=1;i<=q;++i) cout<<ans[i]<<endl;
}
int main()
{
 	t=1;
    //cin>>t;
    while(t--) solve();
    return 0;
}
/*
10 1
4 6 7 7 6 4 6 7 6 5 
2 9
*/
```

---

## 作者：Acoipp (赞：2)

## 分析

设最终 $[l,r]$ 分裂成了三个区间 $[l_1,r_1],[l_2,r_2],[l_3,r_3]$，并且 $[l,r]$ 的最大值在 $[l_2,r_2]$ 内，那么我们令 $l_2=l_1+1,r_1=l_1,r_2=r_3-1,l_3=r_3$，一定不会更劣，所以第一种可能的情况就是区间长度 $1,k,1$，这个可以直接 RMQ 解决。

然后若 $[l,r]$ 的最大值在 $[l_1,r_1]$ 或 $[l_3,r_3]$ 内，容易发现，后者与前者等价，只需要反转序列重做即可，所以下面考虑的是 $[l,r]$ 的最大值在 $[l_1,r_1]$ 中的情况。

这个时候，我们令 $l_3=l_2+1,r_2=l_2$，这样答案也一定不会更劣，于是 $l_2=r_2$。考虑求出这个最大值所在的位置 $pos$，那么 $r=r_3 \ge l_3 = l_2-1 \ge pos$。

于是我们用一个指针维护 $r$，然后开一棵线段树存储每个 $l_2$ 的答案，也即是 $ans_{l_2}=a_{l_2}+\max_{l_2<i \le r} a_i$，最后查询 $\min_{pos<i<r} ans_i$ 即可。

这一部分直接使用单调栈维护，然后用带区间修改的线段树辅助就可以了。代码中使用的方法是另外一种，不过殊途同归，时间复杂度均为 $O(n \log n)$。

## 代码

代码如下，仅供参考：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
using namespace std;
struct node{ll l,r,id,lt,mx;}p[N];
bool cmp(node a,node b){return a.r<b.r;}
ll n,q,i,j,top,sta[N],a[N],ans[N],st[N][21],st2[N][21],st3[N][21],tr[N<<2];
inline ll solve(ll l,ll r){
	ll c = log2(r-l+1);
	return max(st[l][c],st[r-(1<<c)+1][c]);
}
inline ll solve2(ll l,ll r){
	ll c = log2(r-l+1);
	if(st[l][c]>=st[r-(1<<c)+1][c]) return st2[l][c];
	else return st2[r-(1<<c)+1][c];
}
inline ll solve3(ll l,ll r){
	ll c = log2(r-l+1);
	return min(st3[l][c],st3[r-(1<<c)+1][c]);
}
inline void build(ll s,ll t,ll p){
	if(s==t){
		tr[p] = 0x3f3f3f3f3f3f3f3f;
		return ;
	}
	build(s,(s+t)/2,2*p),build((s+t)/2+1,t,2*p+1);
	tr[p] = min(tr[2*p],tr[2*p+1]);
}
inline void add(ll x,ll c,ll s,ll t,ll p){
	if(s==t){
		tr[p]=c;
		return ;
	}
	if(x<=(s+t)/2) add(x,c,s,(s+t)/2,2*p);
	else add(x,c,(s+t)/2+1,t,2*p+1);
	tr[p] = min(tr[2*p],tr[2*p+1]);
}
inline ll query(ll l,ll r,ll s,ll t,ll p){
	if(l<=s&&t<=r) return tr[p];
	if(l<=(s+t)/2&&r>(s+t)/2) return min(query(l,r,s,(s+t)/2,2*p),query(l,r,(s+t)/2+1,t,2*p+1));
	else if(l<=(s+t)/2) return query(l,r,s,(s+t)/2,2*p);
	else return query(l,r,(s+t)/2+1,t,2*p+1);
}
inline void solve(){
	for(i=n;i>=1;i--){
		st[i][0]=a[i],st2[i][0]=i,st3[i][0]=a[i];
		for(j=1;i+(1<<j)-1<=n;j++){
			if(st[i][j-1]>=st[i+(1<<j-1)][j-1]) st2[i][j]=st2[i][j-1];
			else st2[i][j]=st2[i+(1<<j-1)][j-1];
			st[i][j] = max(st[i][j-1],st[i+(1<<j-1)][j-1]);
			st3[i][j] = min(st3[i][j-1],st3[i+(1<<j-1)][j-1]);
		}
	}
	for(i=1;i<=q;i++) p[i].lt=solve2(p[i].l,p[i].r)+1;
	sort(p+1,p+q+1,cmp);
	build(1,n,1);
	for(i=1,j=1,top=0;i<=q;i++){
		while(j<=p[i].r){
			while(top&&a[sta[top]]<=a[j]) top--;
			sta[++top] = j;
			add(top,solve3(sta[top-1],sta[top]-1)+a[sta[top]],1,n,1);
			j++;
		}
		if(p[i].lt<=p[i].r){
			ll pos = lower_bound(sta+1,sta+top+1,p[i].lt)-sta+1;
			if(pos<=top) ans[p[i].id]=min(ans[p[i].id],query(pos,top,1,n,1)+p[i].mx);
			if(p[i].lt<sta[pos-1]) ans[p[i].id]=min(ans[p[i].id],solve3(p[i].lt,sta[pos-1]-1)+a[sta[pos-1]]+p[i].mx);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>q;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=n;i>=1;i--){
		st[i][0]=a[i];
		for(j=1;i+(1<<j)-1<=n;j++) st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
	for(i=1;i<=q;i++) cin>>p[i].l>>p[i].r,p[i].id=i;
	for(i=1;i<=q;i++) ans[i]=solve(p[i].l+1,p[i].r-1)+a[p[i].l]+a[p[i].r],p[i].mx=solve(p[i].l,p[i].r);
	solve();
	reverse(a+1,a+n+1);
	for(i=1;i<=q;i++) swap(p[i].l,p[i].r),p[i].l=n-p[i].l+1,p[i].r=n-p[i].r+1;
	solve();
	for(i=1;i<=q;i++) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：DerrickLo (赞：2)

对于每次询问，考虑讨论最大值在哪一段。

**如果最大值在中间**，那么显然对于左右两段选的越多最大值就会越大，所以左右两段都只选一个数就是最优的。

**如果最大值在左边**，那么我们考虑到当最右边的那段长度是定值时，中间那段的右端点是固定的，则中间的那段的最大值会随着长度变长而增加，所以中间那段的最优长度是 $1$！那么我们先找到区间内最小的 $x$，使得 $\displaystyle{a_x=\max_{i=l}^{r}a_i}$。假设中间那段取的是 $j$，那右边两段的和就是 $\displaystyle{a_j+\max_{i=j+1}^{r}a_i}$，也就是转化为求 $\displaystyle{\min_{j=x+1}^{r-1}(a_j+\max_{i=j+1}^{r}a_i)}$ 的值。

考虑离线后对 $r$ 扫描线，记 $\displaystyle{b_i=a_i+\max_{j=i+1}^{r}a_j}$，我们使用一个单调栈来维护最大值的变化。那么每弹出一个数 $st_x$，我们发现对于 $i\in[st_{x-1},st_x)$ 的 $b_i$ 都会改变，也就是 $b_i\overset{+}{\gets}a_r-a_{st_x}$，这个过程可以直接使用线段树维护，而对于询问直接求出区间最小值即可。

**如果最大值在右边** 可以直接把序列翻转后重新做一遍。

时间复杂度 $\mathcal O(n\log n)$。

[Submission Link](https://atcoder.jp/contests/arc180/submissions/55036941).

---

## 作者：__log__ (赞：1)

## [arc180d](https://www.luogu.com.cn/problem/AT_arc180_d)

在线倍增只有一篇题解就关了通道？

csp 的 day-1 写篇题解涨涨 rp（~~方便我抽周天哥~~）

## 题意

有一个序列，每次查询一个区间 $[l,r]$，然后把区间分成三个子段，给每个子段求 $\max$，问最小的子段 $\max$ 之和。

$n,q \le 2.5\times 10^5,a_i\le 10^8$

## 简单的分讨一下

注意到每个区间的最大值是必取的。所以可以根据最大值 $\max$ 在哪一个子段进行分讨。

### 1. $\max$ 在中间子段

考虑到左边子段必包含 $a_l$，所以左边子段的 $\max$ 一定大于等于 $a_l$，那我们就干脆让中间子段从 $l+1$ 开始。右边同理。

答案为 $\max_{i=l}^r a_i + a_l + a_r$。

### 2.  $\max$ 在右边子段

假设整个区间最大值位置在 $pos$。我们要找到两个断点 $p1,p2$，然后最小化 $\max_{i=l}^{p1}a_i+\max_{j=p1+1}^{p2}a_j+\max_{k=p2+1}^{r}a_k$，其中第三项恒等于 $a_{pos}$。

然后你发现这很蠢，因为如果中间子段的长度 $\ge 2$，就肯定不优于只取 $a_{p1+1}$。

所以我们现在只用找一个断点 $p$，使 $\max_{i=l}^{p}a_i+a_{p+1}+a_{pos}$ 最小化。

考虑枚举从 $l$ 开始的前缀最大值，发现在两个不同的前缀最大值之间一定是让其中的最小值变成中间子段是最优的，类似于如下东东。

![](https://cdn.luogu.com.cn/upload/image_hosting/i5w0921q.png)

红色是从 $l$ 开始的前缀最大值，蓝色是两个前缀最大值之间的小区间的最小值。如果我们一个一个找前缀最大值和小区间最小值，时间复杂度 $O(qn)$。

然后我高兴的发现要是能用什么乱七八糟的数据结构维护这坨东西，我今天就能十连三金了。

想想有什么办法可以加快找的速度。然后就想到了倍增。

假设每一个点后面第一个比它大的数是 $a_{nxt}$，那可以给每条红边赋一个权值 $a_i+\min_{j=i+1}^{nxt-1}a_j$，然后倍增地跳上去，直到跳到 $pos$。

复杂度显然是 $O(q\log n)$，预处理 $O(n\log n)$，细节较多，建议写个暴力慢慢对拍。

$\max$ 在左边子段同理。

## Code

总时间复杂度 $O(n \log n+q\log n)$。

预处理的瓶颈在 ST 表和倍增数组的预处理。

加个快读就可以冲到第二优解了。

感谢博客园 [Seaway-Fu](https://www.cnblogs.com/fusiwei/p/11457143.html) 的快读快写。

```cpp
// I love Furina forever
# include <bits/stdc++.h>
# define maxn 250100
# define inf 0x3f3f3f3f
# define mem(a, val) memset(a, val, sizeof(a))
# define rep(i, j, k) for(int i = j; i <= k; ++i)
# define per(i, j, k) for(int i = j; i >= k; --i)
using namespace std;

int n, q;
int a[maxn];
int stk[maxn], top;
int pre[maxn][20], nxt[maxn][20], c[maxn][20], d[maxn][20];

namespace ST {
    int Max[maxn][20], Min[maxn][20], _log[maxn];

    inline void init() {
        rep(i, 1, n) Max[i][0] = Min[i][0] = i;
        rep(i, 1, 19) rep(l, 1, n - (1 << i) + 1) {
            Max[l][i] = (a[Max[l][i - 1]] < a[Max[l + (1 << i - 1)][i - 1]]) ? Max[l + (1 << i - 1)][i - 1] : Max[l][i - 1];
            Min[l][i] = (a[Min[l][i - 1]] > a[Min[l + (1 << i - 1)][i - 1]]) ? Min[l + (1 << i - 1)][i - 1] : Min[l][i - 1];
        }
        rep(i, 0, 19) rep(j, (1 << i), min(n, (1 << i + 1) - 1)) _log[j] = i;
    }

    inline int query1(int l, int r) {int len = _log[r - l + 1], L = Max[l][len], R = Max[r - (1 << len) + 1][len]; return a[L] < a[R] ? R : L;}
    inline int query2(int l, int r) {int len = _log[r - l + 1], L = Min[l][len], R = Min[r - (1 << len) + 1][len]; return a[L] > a[R] ? R : L;}
} using namespace ST;

inline int solvel(int l, int pos) {
    if(a[l] == a[pos]) return a[l] + a[query2(l, pos)] + a[pos];
    int Min1 = a[l] + a[l + 1]; per(i, 19, 0) if(nxt[l][i] <= pos) Min1 = min(Min1, c[l][i]), l = nxt[l][i]; return Min1 + a[pos];
}

inline int solver(int pos, int r) {
    if(a[r] == a[pos]) return a[r] + a[query2(pos, r)] + a[pos];
    int Min1 = a[r] + a[r - 1]; per(i, 19, 0) if(pre[r][i] >= pos) Min1 = min(Min1, d[r][i]), r = pre[r][i]; return Min1 + a[pos];
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q; rep(i, 1, n) cin >> a[i]; init();
    a[n + 1] = inf; stk[++top] = n + 1; rep(i, 0, 20) c[n + 1][i] = inf, nxt[n + 1][i] = n + 1;
    per(i, n, 1) {while(top && a[i] > a[stk[top]]) top--; nxt[i][0] = stk[top]; stk[++top] = i;}
    top = 0; a[0] = inf; stk[++top] = 0; rep(i, 0, 20) c[0][i] = inf, pre[0][i] = 0;
    rep(i, 1, n) {while(top && a[i] > a[stk[top]]) top--; pre[i][0] = stk[top]; stk[++top] = i;}
    per(i, n, 1) rep(j, 1, 19) nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
    rep(i, 1, n) rep(j, 1, 19) pre[i][j] = pre[pre[i][j - 1]][j - 1];
    rep(i, 1, n) {
        if(nxt[i][0] != i + 1) c[i][0] = a[query2(i, nxt[i][0] - 1)] + a[i];
        else c[i][0] = inf;
        if(pre[i][0] != i - 1) d[i][0] = a[query2(pre[i][0] + 1, i)] + a[i];
        else d[i][0] = inf;
    }
    per(i, n, 1) rep(j, 1, 19) c[i][j] = min(c[i][j - 1], c[nxt[i][j - 1]][j - 1]);
    rep(i, 1, n) rep(j, 1, 19) d[i][j] = min(d[i][j - 1], d[pre[i][j - 1]][j - 1]);
    rep(i, 1, q) {
        int l, r, pos, ans = inf; cin >> l >> r; pos = query1(l, r);
        if(l < pos && pos < r) ans = a[pos] + a[l] + a[r];
        if(pos > l + 1) ans = min(ans, solvel(l, pos));
        if(pos < r - 1) ans = min(ans, solver(pos, r));
        cout << ans << '\n';
    }
    return 0;
}
```

### 乱写的

1. ![](https://cdn.luogu.com.cn/upload/image_hosting/of8w0fmp.png)

---

## 作者：Genius_Star (赞：1)

难度比[CF526F](https://www.luogu.com.cn/problem/CF526F)要高一些，建议评紫。

### 思路：

~~赛时口胡了下，没写。~~

考虑分类讨论计算。

若**最大值**在中间：

- 那么最优的分段肯定是 $A=\{a_l\},B=\{a_{l+1},\cdots,a_{r-1}\},C=\{a_r\}$。

- 因为如果 $A$ 往右延伸，$B$ 往左延伸，$\max A$ 与 $\max B$ 都是单调不下降的，故不会更优。

若**最大值**在左边：

- 注意到该区间最大值无论怎么分段都会算贡献，那么此时考虑求出区间最大值的位置，若有多个，则取最左边的，令其为 $pos$。

- 同理，若 $B$ 向右延伸，$\max B$ 也不会更优，故 $B$ 中只有一个元素，令其为 $a_i$。

- 则 $A=\{a_l,\cdots,a_{pos},\cdots,a_{i-1}\},B=\{a_i\},C=\{a_{i+1},\cdots,a_r\}$。

- 则 $\max A = a_{pos},\max B = a_i,\max C = \max\limits_{j=i+1}^r a_j$。

- 那么现在转化为求：

$$\min_{i=pos+1}^{r-1} (a_i + \max_{j=i+1}^r a_j)$$

- 考虑离线进行扫描线，然后用单调栈维护每个位置到 $r$ 的最大值，线段树维护区间最小值即可。

若**最大值**在右边：

- 将序列翻转再做一遍即可。

时间复杂度为 $O(N \log N)$。

### 扫描线：

这里来详细讲一下如何扫描线。

设单调栈栈顶为 $T_{Top}$，若 $a_{T_{Top}} < a_i$，则表示在区间 $[T_{Top},i-1]$ 中没有大于 $a_{T_{Top}}$ 的数（有的话 $T_{top}$ 就会被弹出）。

故当扫描线扫到区间 $[T_{top},i-1]$ 时（即右端点在这个区间时），那么对于区间 $[T_{Top-1}+1,T_{top}]$ 任意一个数到区间 $[T_{top},i-1]$ 任意一个数的区间最大值都是 $a_{T_{top}}$。

那么就可以拆为在 $T_{top}$ 处区间加，在 $i$ 处区间减将贡献去除。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=250005,M=21,INF=1e18;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
class St{
public:
	ll data;
	ll id;
	inline friend St add(St A,St B){
		St ans;
		ans.id=INF;
		ans.data=max(A.data,B.data);
		if(ans.data==A.data)
		  ans.id=min(ans.id,A.id);
		if(ans.data==B.data)
		  ans.id=min(ans.id,B.id);
		return ans;		
	}
}Max[N][M];
struct Node{
	ll l,r;
	ll Min;
	ll tag;
}X[N<<2];
ll n,q,pos,Top;
ll a[N],l[N],r[N],ans[N],T[N];
vector<pair<ll,ll>> Q[N];
vector<pair<pair<ll,ll>,ll>> E[N];
inline void pushup(ll k){
	X[k].Min=min(X[k<<1].Min,X[k<<1|1].Min);
}
inline void add(ll k,ll v){
	X[k].Min+=v;
	X[k].tag+=v;
}
inline void push_down(ll k){
	if(X[k].tag){
		add(k<<1,X[k].tag);
		add(k<<1|1,X[k].tag);
		X[k].tag=0;
	}
}
inline void build(ll k,ll l,ll r){
	X[k].l=l,X[k].r=r;
	X[k].tag=0;
	if(l==r){
		X[k].Min=a[l-1];
		return ;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
inline void update(ll k,ll l,ll r,ll v){
	if(X[k].l==l&&r==X[k].r){
		add(k,v);
		return ;
	}
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  update(k<<1,l,r,v);
	else if(l>mid)
	  update(k<<1|1,l,r,v);
	else{
		update(k<<1,l,mid,v);
		update(k<<1|1,mid+1,r,v);
	}
	pushup(k);
}
inline ll query(ll k,ll l,ll r){
	if(X[k].l==l&&r==X[k].r)
	  return X[k].Min;
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return query(k<<1,l,r);
	else if(l>mid)
	  return query(k<<1|1,l,r);
	else
	  return min(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
}
inline St Query_Max(ll l,ll r){
    ll k=log2(r-l+1);
    return add(Max[l][k],Max[r-(1<<k)+1][k]);
}
inline void solve(){
	for(int i=1;i<=n;i++){
		Max[i][0].data=a[i];
		Max[i][0].id=i;
	}
	for(int k=1;(1<<k)<=n;k++)
	  for(int i=1;i+(1<<k)-1<=n;i++)
	    Max[i][k]=add(Max[i][k-1],Max[i+(1<<(k-1))][k-1]);
	for(int i=1;i<=n+1;i++){
		while(Top&&a[T[Top]]<a[i]){
			ll l=T[Top],r=i-1;
			E[l].push_back({{T[Top-1]+1,T[Top]},a[T[Top]]});
			E[r+1].push_back({{T[Top-1]+1,T[Top]},-a[T[Top]]});
			Top--;
		}
		T[++Top]=i;
	}
	for(int i=1;i<=q;i++){
		ans[i]=min(a[l[i]]+Query_Max(l[i]+1,r[i]-1).data+a[r[i]],ans[i]);
		pos=Query_Max(l[i],r[i]).id;
		if(r[i]-pos>=2)
		  Q[r[i]].push_back({pos+1,i});
	}
	build(1,1,n);
	for(int i=1;i<=n;i++){
		for(auto t:E[i])
		  update(1,t.first.first,t.first.second,t.second);
		for(auto t:Q[i])
		  ans[t.second]=min(ans[t.second],a[t.first-1]+query(1,t.first+1,i));
	}
	Top=0;
	for(int i=1;i<=n;i++){
		E[i].clear();
		Q[i].clear();
	}
}
int main(){
	memset(ans,0x7f,sizeof(ans));
	n=read(),q=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	a[n+1]=a[0]=INF;
	for(int i=1;i<=q;i++)
	  l[i]=read(),r[i]=read();
	solve();
	for(int i=1;i<=q;i++){
		swap(l[i],r[i]);
		l[i]=n-l[i]+1,r[i]=n-r[i]+1;
	}
	reverse(a+1,a+n+1);
	solve();
	for(int i=1;i<=q;i++){
		write(ans[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：_lmh_ (赞：1)

显然至少一个连续段会包含 $[l,r]$ 的最大值，所以我们分四种情况考虑。

同时如果一个连续段包含最大值，那么它的左右两侧可以任意伸缩，不会影响答案。

1. 最大值出现了不止一次，且左边和右边两个连续段的最大值都是它

由于左右两边可以任意伸缩，所以显然可以让中间的连续段只有一个数。

开线段树记录最大值，最大值出现的最左边和最右边的位置，最小值，查询最大值之后查询两个位置中间的最小值即可。

2. 最大值在中间那个连续段出现过

中间的连续段左右两边可以任意伸缩，所以左右两边只包含一个值是最优的。

查询 $[l+1,r-1]$ 的最大值加上 $a_l,a_r$ 即可。

注意到如果最大值只在端点出现那么这种情况根本不可能出现，但该算法得到的还是一个合法方案。然而这样的话自动归约到第一或四种情况（取决于最大值在一端还是两端出现），所以最小值依然能求出。

3. 最大值只在左边的连续段或右边的连续段出现

不妨设是左边的连续段。记录它最后一次出现的位置（实际上随便哪次都行），如果右边只有 $\le 1$ 个数那么直接不考虑就行。

尝试钦定中间的连续段的最大值，左边的连续段可以伸缩所以这个最大值就是中间连续段的左端点。

注意到如果中间连续段长度大于 $1$，那么把最大值换成最右边的那个点显然不劣。

所以问题转换成多组询问，每次给定 $[L,R](L<R)$ 求 $\min\limits_{L\le i<R}\{a_i+\max\limits_{i<j \le R}a_j\}$。

考虑离线所有询问按照 $R$ 排序扫描线，单调栈动态维护后缀最大值，线段树维护结果。

每次栈弹出或者插入的时候算一下影响到的区间，在线段树上区间加即可。

查询询问等价于线段树上区间查询最小值，然后这个题就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define lson (u<<1)
#define rson (u<<1|1)
const ll N=250007;
ll n,m,a[N];
struct Query{ll l,r,ans;}qry[N];
struct query{ll pos,x,id,diff;}Q[2][N];
struct node{ll mx,mxl,mxr,mn;}tree[N<<2];
node operator +(const node& a,const node& b){
	return (node){max(a.mx,b.mx),(a.mx>=b.mx?a.mxl:b.mxl),(a.mx<=b.mx?b.mxr:a.mxr),min(a.mn,b.mn)};
}
void build(ll u,ll l,ll r){
	if (l==r){
		tree[u]=(node){a[l],l,l,a[l]};
		return;
	}
	ll mid=l+r>>1;
	build(lson,l,mid);build(rson,mid+1,r);
	tree[u]=tree[lson]+tree[rson];
}
node get(ll u,ll l,ll r,ll L,ll R){
	if (L<=l&&r<=R) return tree[u];
	ll mid=l+r>>1;
	if (R<=mid) return get(lson,l,mid,L,R);
	if (L>mid) return get(rson,mid+1,r,L,R);
	return get(lson,l,mid,L,R)+get(rson,mid+1,r,L,R);
}
namespace ns{
	vector<pair<pair<ll,ll>,ll> > q[N];
	ll mn[N<<2],tag[N<<2],stk[N],top,nQ;
	void pushup(ll u){mn[u]=min(mn[lson],mn[rson]);}
	void add(ll u,ll v){mn[u]+=v;tag[u]+=v;}
	void pushdown(ll u){
		if (tag[u]){
			add(lson,tag[u]);add(rson,tag[u]);tag[u]=0;return;
		}
	}
	void build(ll u,ll l,ll r){
		tag[u]=0;
		if (l==r){
			mn[u]=a[l];return;
		}
		ll mid=l+r>>1;
		build(lson,l,mid);build(rson,mid+1,r);
		pushup(u);
	}
	void modify(ll u,ll l,ll r,ll L,ll R,ll v){
		if (L<=l&&r<=R){
			add(u,v);return;
		}
		pushdown(u);
		ll mid=l+r>>1;
		if (L<=mid) modify(lson,l,mid,L,R,v);
		if (R>mid) modify(rson,mid+1,r,L,R,v);
		pushup(u);
	}
	ll query(ll u,ll l,ll r,ll L,ll R){
		if (L<=l&&r<=R) return mn[u];
		pushdown(u);
		ll mid=l+r>>1;
		if (R<=mid) return query(lson,l,mid,L,R);
		if (L>mid) return query(rson,mid+1,r,L,R);
		return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
	}
	void solve(){
		build(1,0,n);
		stk[top=0]=0;
		for (int i=1;i<=n;++i){
			ll lst=stk[top];
			while(top&&a[stk[top]]<a[i]){
				modify(1,0,n,stk[top-1],stk[top]-1,-a[stk[top]]);
				lst=stk[--top];
			}
			modify(1,0,n,lst,i-1,a[i]);
			stk[++top]=i;
			for (auto p:q[i]){
				qry[p.second].ans=min(qry[p.second].ans,query(1,0,n,p.first.first,i-1)+p.first.second);
			}
			q[i].clear();
		}
	}
}
int main(){
	cin>>n>>m;
	for (int i=1;i<=n;++i) cin>>a[i];
	build(1,1,n);
	for (int i=1;i<=m;++i){
		cin>>qry[i].l>>qry[i].r;qry[i].ans=a[qry[i].l]+a[qry[i].r]+get(1,1,n,qry[i].l+1,qry[i].r-1).mx;
		auto p=get(1,1,n,qry[i].l,qry[i].r);
		if (p.mxl<p.mxr-1) qry[i].ans=min(qry[i].ans,p.mx*2+get(1,1,n,p.mxl+1,p.mxr-1).mn);
		if (p.mxl>qry[i].l+1) Q[1][i]=(query){qry[i].l,p.mxl-1,i,p.mx};
		if (p.mxr<qry[i].r-1) Q[0][i]=(query){qry[i].r,p.mxr+1,i,p.mx};
	}
	for (int i=1;i<=m;++i) if (Q[0][i].pos) ns::q[Q[0][i].pos].push_back(make_pair(make_pair(Q[0][i].x,Q[0][i].diff),Q[0][i].id));
	ns::solve();
	reverse(a+1,a+1+n);
	for (int i=1;i<=m;++i) if (Q[1][i].pos){
		Q[1][i].pos=n+1-Q[1][i].pos;
		Q[1][i].x=n+1-Q[1][i].x;
	}
	for (int i=1;i<=m;++i) if (Q[1][i].pos) ns::q[Q[1][i].pos].push_back(make_pair(make_pair(Q[1][i].x,Q[1][i].diff),Q[1][i].id));
	ns::solve();
	for (int i=1;i<=m;++i) cout<<qry[i].ans<<'\n';
	return 0;
}
```

---

## 作者：xzf_200906 (赞：1)

首先不难发现，对于一个序列，其中的最大值一定被计入答案。

### 情况 1：中间的区间最大值为全序列最大值
对于这种情况，两端的区间显然越小越好，所以答案为 $A_l+A_r+\max_{l<i<r}\{A_i\}$。
### 情况 2：左边的区间最大值为全序列最大值
在此情况下，找到最大值从左到右第一次出现的位置 $pos$，则在最右边的区间确定的情况下，中间的区间显然越小越好，所以答案为 $A_{pos}+\min_{pos<i<r}\{A_i+\max_{i<j\leq r}\{A_j\}\}$。

考虑上式如何维护。注意到上式涉及区间内后缀最大值，考虑扫描线+单调栈。将询问挂在其右端点上，若在将 $i$ 进栈前栈顶元素为 $p$，则对所有的 $p\leq j <i$ 执行 $B_j\gets A_i$，遇到询问时查询 $\min_{pos<j<i}\{A_j+B_j\}$ 即可。不难用线段树维护。
### 情况 3：右边的区间最大值为全序列最大值
与情况 2 类似，不再赘述。
Code:
```c++
#include <bits/stdc++.h>
#define LL long long
using namespace std;
int a[1000000],ans[1000000],stk[1000000],top=0;
int minn[2500000],maxa[2500000],mina[2500000],posl[2500000],posr[2500000],tag[2500000];
vector<pair<int,int> > qryl[1000000],qryr[1000000];
void up(int p){
	minn[p]=min(minn[p<<1],minn[p<<1|1]);
}
void dn(int p){
	if(tag[p]!=-1){
		tag[p<<1]=tag[p<<1|1]=tag[p];
		minn[p<<1]=mina[p<<1]+tag[p];
		minn[p<<1|1]=mina[p<<1|1]+tag[p];
		tag[p]=-1;
	}
}
void build(int p,int l,int r){
	tag[p]=0;
	if(l==r){
		minn[p]=mina[p]=maxa[p]=a[l];
		posl[p]=posr[p]=l;
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	if(maxa[p<<1]==maxa[p<<1|1]) posl[p]=posl[p<<1],posr[p]=posr[p<<1|1];
	else if(maxa[p<<1]>maxa[p<<1|1]) posl[p]=posl[p<<1],posr[p]=posr[p<<1];
	else posl[p]=posl[p<<1|1],posr[p]=posr[p<<1|1];
	maxa[p]=max(maxa[p<<1],maxa[p<<1|1]);
	mina[p]=min(mina[p<<1],mina[p<<1|1]);
	up(p);
}
void change(int p,int l,int r,int ql,int qr,int val){
	if(ql>qr) return;
	if(ql<=l&&qr>=r){
		tag[p]=val;
		minn[p]=val+mina[p];
		return;
	}
	int mid=(l+r)>>1;
	dn(p);
	if(ql<=mid) change(p<<1,l,mid,ql,qr,val);
	if(qr>mid) change(p<<1|1,mid+1,r,ql,qr,val);
	up(p);
}
int query(int p,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r) return minn[p];
	int mid=(l+r)>>1,ret=INT_MAX;
	dn(p);
	if(ql<=mid) ret=query(p<<1,l,mid,ql,qr);
	if(qr>mid) ret=min(ret,query(p<<1|1,mid+1,r,ql,qr));
	return ret;
}
int queryl(int p,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r) return posl[p];
	int mid=(l+r)>>1;
	if(ql<=mid&&qr>mid){
		int ret1=queryl(p<<1,l,mid,ql,qr),ret2=queryl(p<<1|1,mid+1,r,ql,qr);
		if(a[ret1]>=a[ret2]) return ret1;
		else return ret2;
	}
	else if(ql<=mid) return queryl(p<<1,l,mid,ql,qr);
	else if(qr>mid) return queryl(p<<1|1,mid+1,r,ql,qr);
}
int queryr(int p,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r) return posr[p];
	int mid=(l+r)>>1;
	if(ql<=mid&&qr>mid){
		int ret1=queryr(p<<1,l,mid,ql,qr),ret2=queryr(p<<1|1,mid+1,r,ql,qr);
		if(a[ret1]>a[ret2]) return ret1;
		else return ret2;
	}
	else if(ql<=mid) return queryr(p<<1,l,mid,ql,qr);
	else if(qr>mid) return queryr(p<<1|1,mid+1,r,ql,qr);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	for(int i=1;i<=q;i++){
		int l,r;
		cin>>l>>r;
		ans[i]=a[l]+a[r]+a[queryl(1,1,n,l+1,r-1)];
		qryl[l].push_back({r,i});
		qryr[r].push_back({l,i});
	}
	for(int i=1;i<=n;i++){
		while(top&&a[stk[top]]<=a[i]) top--;
		change(1,1,n,max(1,stk[top]),i-1,a[i]);
		stk[++top]=i;
		for(auto it:qryr[i]){
			int pos=queryl(1,1,n,it.first,i);
			if(i-pos>=2) ans[it.second]=min(ans[it.second],query(1,1,n,pos+1,i-1)+a[pos]);
		}
	}
	top=0;
	stk[top]=n;
	build(1,1,n);
	for(int i=n;i>=1;i--){
		while(top&&a[stk[top]]<=a[i]) top--;
		change(1,1,n,i+1,min(n,stk[top]),a[i]);
		stk[++top]=i;
		for(auto it:qryl[i]){
			int pos=queryr(1,1,n,i,it.first);
			if(pos-i>=2) ans[it.second]=min(ans[it.second],query(1,1,n,i+1,pos-1)+a[pos]);
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Anonymely (赞：0)

介绍一个在线支持单点修改的做法，但是多了一只 $\log$。

询问区间最大值在第二段中是平凡的，第一段和第三段对称，考虑第一段的情况，则需要求的即为 $a_{mx}+\min_{j=mx+1}^{r-1}(a_j+ \max_{k=j+1}^r a_k)$。

注意到这是一个关于后缀最大值的东西，考虑一下能否直接维护，合并两个区间时，右区间的答案可以直接合并上来，而对于左区间，由于后缀最大值单调不增，与右区间最大值合并时相当于将一段后缀推平，直接线段树上二分即可。

或者考虑类似楼房重建的线段树，进入区间后判断右区间最大值与当前后缀最大值的关系，讨论即可做到每次往一侧递归，注意这里小细节是记录信息可能与楼房重建有点不同，因为最值没有可减性。

复杂度 $O(n \log^2 n)$，胜在带修和在线。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, T y) {x = min(x, y);}

const int inf = 1e9;
const int N = 2.5e5 + 5;
int n, q, a[N];
struct Tree {
    int mx, mn, f, rf, ff, rff, mxid;
} t[N << 2];
#define ls (p << 1)
#define rs (p << 1 | 1)

int up(int p, int l, int r, int w) {
    if (t[p].mx <= w) return t[p].mn + w;
    if (l == r) return t[p].mn + w;
    int mid = (l + r) / 2;
    if (t[rs].mx >= w) return min(t[p].ff, up(rs, mid + 1, r, w));
    else return min(t[rs].mn + w, up(ls, l, mid, w));
}

int rup(int p, int l, int r, int w) {
    if (t[p].mx <= w) return t[p].mn + w;
    if (l == r) return t[p].mn + w;
    int mid = (l + r) / 2;
    if (t[ls].mx >= w) return min(t[p].rff, rup(ls, l, mid, w));
    else return min(t[ls].mn + w, rup(rs, mid + 1, r, w));
}

void build(int p, int l, int r) {
    if (l == r) {
        t[p].mx = t[p].mn = a[l];
        t[p].mxid = l;
        t[p].f = t[p].rf = t[p].ff = t[p].rff = inf;
        return ;
    }
    int mid = (l + r) / 2;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    t[p].mx = max(t[ls].mx, t[rs].mx);
    if (t[p].mx == t[ls].mx) t[p].mxid = t[ls].mxid;
    else t[p].mxid = t[rs].mxid;
    t[p].mn = min(t[ls].mn, t[rs].mn);
    t[p].ff = up(ls, l, mid, t[rs].mx);
    t[p].f = min(t[rs].f, t[p].ff);
    t[p].rff = rup(rs, mid + 1, r, t[ls].mx);
    t[p].rf = min(t[ls].rf, t[p].rff);
}

int gmx(int u, int v) {return a[u] > a[v] ? u : v;}
int qmx(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return t[p].mxid;
    int mid = (l + r) / 2;
    if (L > mid) return qmx(rs, mid + 1, r, L, R);
    else if (mid >= R) return qmx(ls, l, mid, L, R);
    else return gmx(qmx(ls, l, mid, L, R), qmx(rs, mid + 1, r, L, R));
}

int now = inf, nmx;
void query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        if (nmx) ckmin(now, up(p, l, r, nmx));
        else ckmin(now, t[p].f);
        ckmax(nmx, t[p].mx);
        return ;
    }
    int mid = (l + r) / 2;
    if (mid < R) query(rs, mid + 1, r, L, R);
    if (L <= mid) query(ls, l, mid, L, R);
}

int rnow = inf, rnmx;
void rquery(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        if (rnmx) ckmin(rnow, rup(p, l, r, rnmx));
        else ckmin(rnow, t[p].rf);
        ckmax(rnmx, t[p].mx);
        return ;
    }
    int mid = (l + r) / 2;
    if (L <= mid) rquery(ls, l, mid, L, R);
    if (mid < R) rquery(rs, mid + 1, r, L, R);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    while (q--) {
        int l, r;
        cin >> l >> r;
        int mid = qmx(1, 1, n, l, r), ans = 1e9;
        if (mid != l && mid != r) ckmin(ans, a[l] + a[r] + a[mid]);
        if (mid != r) {
            now = inf, nmx = 0;
            query(1, 1, n, mid + 1, r);;
            ckmin(ans, a[mid] + now);
        }
        if (l != mid) {
            rnow = inf, rnmx = 0;
            rquery(1, 1, n, l, mid - 1);
            ckmin(ans, a[mid] + rnow);
        }
        cout << ans << '\n';
    }
    QwQ01AwA;
}
```

---

