# [ABC223F] Parenthesis Checking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc223/tasks/abc223_f

以下のいずれかの条件を満たす文字列を**正しい括弧列**と定義します。

- 空文字列
- ある**正しい括弧列** $ A $ が存在して、`(`, $ A $, `)` をこの順に連結した文字列
- ある空でない**正しい括弧列** $ A $, $ B $ が存在して、$ A $, $ B $ をこの順に連結した文字列

`(` と `)` のみからなる長さ $ N $ の文字列 $ S $ があります。

$ Q $ 個のクエリ $ \text{Query}_1,\text{Query}_2,\ldots,\text{Query}_Q $ が与えられるので、順番に処理してください。クエリには $ 2 $ 種類があり、入力形式とクエリの内容は以下の通りです。

- `1 l r` : $ S $ の $ l $ 文字目と $ r $ 文字目を入れ替える。
- `2 l r` : $ S $ の $ l $ 文字目から $ r $ 文字目までの連続部分文字列が**正しい括弧列**であるか判定する。

## 说明/提示

### 制約

- $ 1\ \leq\ N,Q\ \leq\ 2\ \times\ 10^5 $
- $ S $ は `(` と `)` のみからなる長さ $ N $ の文字列
- $ 1\ \leq\ l\ <\ r\ \leq\ N $
- $ N,Q,l,r $ はいずれも整数
- 各クエリは `1 l r`、`2 l r` のいずれかの形式で与えられる。
- `2 l r` の形式のクエリは $ 1 $ つ以上与えられる。

### Sample Explanation 1

$ 1 $ つ目のクエリにおいて、`(())` は\*\*正しい括弧列\*\*です。 $ 2 $ つ目のクエリにおいて、`((` は\*\*正しい括弧列\*\*ではありません。 $ 3 $ つ目のクエリにおいて、`)(` は\*\*正しい括弧列\*\*ではありません。

### Sample Explanation 2

$ 1 $ つ目のクエリにおいて、`(())` は\*\*正しい括弧列\*\*です。 $ 2 $ つ目のクエリによって、$ S $ は `)()((` となります。 $ 3 $ つ目のクエリにおいて、`)()(` は\*\*正しい括弧列\*\*ではありません。

## 样例 #1

### 输入

```
5 3
(())(
2 1 4
2 1 2
2 4 5```

### 输出

```
Yes
No
No```

## 样例 #2

### 输入

```
5 3
(())(
2 1 4
1 1 4
2 1 4```

### 输出

```
Yes
No```

## 样例 #3

### 输入

```
8 8
(()(()))
2 2 7
2 2 8
1 2 5
2 3 4
1 3 4
1 3 5
1 1 4
1 6 8```

### 输出

```
Yes
No
No```

# 题解

## 作者：2huk (赞：9)

# Parenthesis Checking

## Description

给出一个长度为 $n$ 的括号串，$q$ 次以下两种操作：

+ 输入 $1\ l\ r$，代表交换第 $l$ 和第 $r$ 个位置上的字符；
+ 输入 $2\ l\ r$，判断区间 $[l,r]$ 子串是否是合法括号序列。

$n, q \le 2 \times 10^5$。

## Solution

一个括号序列是合法的有这样一个 trick：

- 总共的左括号和右括号数量相等；
- 任意前缀的左括号数量 $\ge$ 右括号数量。

若将序列中左括号看作 $1$，右括号看作 $-1$，则两个条件变成了：

- 总和为 $0$；
- 任意前缀和 $\ge 0$。

---

那么考虑仅有 $2$ 操作的这个问题。每次判断某个区间是否合法也就是看这个区间的每个前缀和是否合法。具体的，若我们将上述求得的括号序列前缀和定义为 $\{s_i\}$，则需要满足：

- $s_r - s_{l - 1} = 0$ 也就是 $s_r = s_{l - 1}$；
- 任意 $k \in [l, r]$，都有 $s_k -s_{l - 1} \ge 0$ 也就是 $s_k \ge s_{l - 1}$。

对于第二个条件，我们可以将其转化为 $\min_{i = l}^r (s_i) \ge s_{l = 1}$。因为只要最小值比它大那么所有值就都比它大了。

因此若这个问题不带修，这样就已经可以了。首先求出括号序列的前缀和，并用数据结构（比如 ST 表）维护这个前缀和数组上的区间最小值，然后根据这两个条件判断即可。

---

若带修，我们可以用线段树维护。用线段树维护**括号序列前缀和数组**的值，额外维护一个区间最小值，那么在每次交换两个位置时分类：

- 若原来 $l$ 和 $r$ 位置上的元素（指原始括号序列）相同，则不做处理；
- 否则，若原来 $l$ 上为左括号，$r$ 上为右括号，则在前缀和数组上应该是 $[l, n]$ 这一段整体减 $2$，$[r, n]$ 这一段整体加 $2$，然后在原序列上交换；
- 再否则，若原来 $l$ 上为右括号，$r$ 上为左括号，则在前缀和数组上应该是 $[l, n]$ 这一段整体加 $2$，$[r, n]$ 这一段整体减 $2$，然后在原序列上交换。

例如，若要将 $4, 5$ 位置上的括号交换：

![](https://cdn.luogu.com.cn/upload/image_hosting/qral7e6z.png)

那么很显然的 $4$ 位置上原来的值 $-1 \to 1$ 也就是多了 $2$，$5$ 位置上原来的值 $1 \to -1$ 也就是少了 $2$。而一个值的变化会影响前缀和数组上当前位置以后的所有位置：

![](https://cdn.luogu.com.cn/upload/image_hosting/86jf6hl7.png)

然后修改就完成了。

---

在实现上，你需要维护一颗支持区间加，单点查询，区间求最小值的线段树。其中的单点查询可以偷懒成长度为 $1$ 的区间最小值。

还需要注意，在判断当前区间是否合法时，第一个条件用到了 $l - 1$ 位置上的值，此时若 $l = 1$ 则会访问不到。因此需要特判若 $l = 1$ 时 $s_{l - 1} = 0$。否则你会挂在 case\_28 上。

## Code

[这里](https://atcoder.jp/contests/abc223/submissions/46483754)。

---

## 作者：_ZML_ (赞：3)

# Parenthesis Checking 题解

今天模拟赛第二题，本来就已经切掉，而且对拍了也没问题，结果一交只有 $60$ 分。原来是查询的时候写成 `query(p*2+1,mid+1,r)` 了，痛失 $40$ 分。

## 思路

一眼线段树，先来讲一下是否是符合要求的括号序列的判定。

我们把左括号看成 $-1$，右括号看成 $1$。那么一个括号序列 $s$ 就可以变成一个 $01$ 序列。我们对它求一个前缀和，他一定要满足任意 $s_i\ge0$ 且 $s_n=0$。

所以我们的线段树就要维护两个东西，一个是区间 $[l,r]$ 的和，还有一个就是当前区间前缀和的最小值，这里记作 $sum$ 和 $mn$。

所以 `pushup` 函数也就很简单了：

```cpp
tree[p].sum=tree[p*2]+tree[p*2+1];// 左右儿子和相加
tree[p].mn=min(tree[p*2].mn,tree[p*2].sum+tre[p*2+1].mn);// 前缀和:可以选左儿子的最小前缀和，也可以是右儿子的最小前缀和加上左儿子的和
```

修改函数可以对点进行更新，然后一层一层地递归更新到 $1$ 号节点：

```cpp
void change(int p,int x,int d) {
	if(l(p)==r(p)) {
		sum(p)=mn(p)=d;
		return;
	}
	int mid=(l(p)+r(p))/2;
	if(x<=mid) change(p*2,x,d);
	else change(p*2+1,x,d);
	pushup(p);
}
```



询问函数有一点复杂，我细讲一下思路。



这个函数的类型是 `pair<int,int>` 的，第一个存的是 $sum$，第二个存的是 $mn$。若当前子节点被询问区间覆盖，则返回当前节点的 $sum$ 和 $mn$。否则，先对左右儿子进行询问，记作 $L$，$R$，将他们两个像 `pushup` 一样合并成 $ans$：

```cpp
ans.first=L.first+R.first;
ans.second=min(L.second,L.first+R.second);
```

该讲的都讲了。上代码！

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define l(p) tree[p].l
#define r(p) tree[p].r
#define sum(p) tree[p].sum
#define mn(p) tree[p].mn
const int maxn=2e5;
struct Seg{
	int l,r,mn,sum;
	Seg() {
		l=r=sum=0;
		mn=1e18;
	}
}tree[maxn*6];
int a[maxn];
void pushup(int p) {
	sum(p)=sum(p*2)+sum(p*2+1);
	mn(p)=min(mn(p*2),sum(p*2)+mn(p*2+1));
}
void build(int p,int l,int r) {
	l(p)=l, r(p)=r;
	if(l==r) {
		sum(p)=mn(p)=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	pushup(p);
}
void change(int p,int x,int d) {
	if(l(p)==r(p)) {
		sum(p)=mn(p)=d;
		return;
	}
	int mid=(l(p)+r(p))/2;
	if(x<=mid) change(p*2,x,d);
	else change(p*2+1,x,d);
	pushup(p);
}
pair<int,int> query(int p,int l,int r) {
	if(l<=l(p)&&r(p)<=r) {
		pair<int,int> tmp={tree[p].sum,tree[p].mn};
		return tmp;
	}
	int mid=(l(p)+r(p))/2;
	pair<int,int> L,R,ans;	
	if(l<=mid) L=query(p*2,l,r);
	if(r>mid) R=query(p*2+1,l,r);
	ans.first=L.first+R.first;
	ans.second=min(L.second,L.first+R.second);
	return ans;
}
int main() {
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) {
		char c;cin>>c;
		a[i]=(c=='('?1:-1);
	}
	build(1,1,n);
	while(q--) {
		int k,l,r;
		cin>>k>>l>>r;
		if(k==1) {
			swap(a[l],a[r]);
			change(1,l,a[l]);
			change(1,r,a[r]);
		}
		else {
			pair<int,int> x=query(1,l,r);
			if(x.second>=0&&x.first==0) {
				cout<<"Yes\n";
			}
			else cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：OPEC (赞：3)

# [[ABC223F] Parenthesis Checking](https://www.luogu.com.cn/problem/AT_abc223_f)

这道题有两个操作

1. 让你求 $l$ 到 $r$ 区间的括号合不合法
2. 让你调换交换第 $l$ 和第 $r$ 个位置上的字符

这道题第一思路是用栈来看是否合法，但 $1\le N,Q\le 2\times10^5$

看见这里，会发现 $O(N^2)$ 的复杂度会超时

于是，这个数值让我想起了万能的线段树

我们可以把栈简化一下

1. $($ 是 $+1$
2. $)$ 是 $-1$

如果 $a_l$ 是 $0$ 那么这就是合法的

但新的问题又来了：

如果是 $)($ 的话，但 $a_2$ 是零，但不成立

此时就要用到前缀和，如果这一段的前缀和最小值小于零，就说明一定有右括号在前，左括号在有的情况

接着用线段树来维护前缀和就好了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q;
char a[200005];
int s[200005];
#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((r+l)>>1)
struct Node
{
	int l,r;
	int v;
	int lazy;//懒标记
}tr[800005];
void pushup(int rt)//回溯
{
	tr[rt].v=min(tr[lson].v,tr[rson].v);
}
void pushdown(int rt)//懒标记++
{
	tr[lson].v+=tr[rt].lazy;
	tr[lson].lazy+=tr[rt].lazy;
	tr[rson].v+=tr[rt].lazy;
	tr[rson].lazy+=tr[rt].lazy;
	tr[rt].lazy=0;
}
void build(int rt,int l,int r)//建造一棵线段树
{
	tr[rt]={l,r,0,0};
	if(l==r)
	{
		tr[rt].v=s[l];
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(rt);
}
void update(int rt,int sp,int ep,int k)//加数
{
	int l=tr[rt].l;
	int r=tr[rt].r;
	if(sp<=l&&r<=ep)
	{
		tr[rt].v+=k;
		tr[rt].lazy+=k;
		return;
	}
	pushdown(rt);
	if(sp<=mid)
		update(lson,sp,ep,k);
	if(ep>mid)
		update(rson,sp,ep,k);
	pushup(rt);
}
Node query(int rt,int sp,int ep)//求值
{
	int l=tr[rt].l;
	int r=tr[rt].r;
	if(sp<=l&&r<=ep)
	{
		return tr[rt];
	}
	pushdown(rt); 
	if(ep<=mid)
		return query(lson,sp,ep);
	if(sp>mid)
		return query(rson,sp,ep);
	Node L=query(lson,sp,ep);
	Node R=query(rson,sp,ep);
	Node res;
	res.v=min(L.v,R.v);
	return res; 
}
#undef lson
#undef rson
#undef mid
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)//前缀和
	{
		cin>>a[i];
		if(a[i]=='(')//左括号
			s[i]=s[i-1]+1;
		if(a[i]==')')//右括号
			s[i]=s[i-1]-1;
	}
	build(1,0,n);
	while(q--)
	{
		int t,x,y;
		cin>>t>>x>>y;
		if(t==1)
		{
			if(a[x]!=a[y])//如果一样就不用交换
			{
				if(a[x]=='(')
				{
					update(1,x,n,-2);
					update(1,y,n,2);
					swap(a[x],a[y]);//原数组也要交换
				}
				else if(a[x]==')')//必须用else if否则前面该过去后面又将该回去
				{
					update(1,x,n,2);
					update(1,y,n,-2);
					swap(a[x],a[y]);
				}
			}
		}
		if(t==2)
		{
			auto L=query(1,x-1,x-1);//他前面一个
			auto M=query(1,x,y);//区间和
			auto R=query(1,y,y);//最后一位
			if(L.v==R.v&&M.v>=L.v)
			{
				cout<<"Yes\n";
			}
			else
			{
				cout<<"No\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：harmis_yz (赞：1)

## 分析

考虑合法括号匹配性质：对于任意位置 $i$，$1$ 到 $i$ 的左括号数量不少于右括号数量；当 $i=|S|$ 时，左括号数量等于右括号数量。

令左括号为 $1$，右括号为 $-1$。则只要序列总和为 $0$，任意前缀和 $\ge 0$ 就是合法括号匹配。

区间查询，考虑线段树。记录当前区间的区间和与区间前缀最小值，在上传的父节点时，由于右边那个儿子的前缀和都会再加上左边儿子的区间和，所以父节点的最小值为左儿子最小值与右儿子最小值加上左儿子区间和的最小值。询问区间是合法括号匹配即满足区间和为 $0$，最小值非负。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}

const int N=2e5+10,inf=1e18;
int n,m;
int a[N];
struct Tree{
	int l,r,mi,s;
}tr[N<<2];

il void up(int now){
	tr[now].s=tr[now<<1].s+tr[now<<1|1].s;
	tr[now].mi=min(tr[now<<1].mi,tr[now<<1].s+tr[now<<1|1].mi);
	return ;
}
il void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(l==r) return tr[now].s=tr[now].mi=a[l],void(0);
	int mid=l+r>>1;
	build(now<<1,l,mid),build(now<<1|1,mid+1,r);
	return up(now),void(0);
}
il void insert(int now,int x,int k){
	if(tr[now].l==tr[now].r) return tr[now].s=tr[now].mi=k,void(0);
	int mid=tr[now].l+tr[now].r>>1;
	if(x<=mid) insert(now<<1,x,k);
	else insert(now<<1|1,x,k);
	return up(now),void(0);
}
il Tree query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r) return tr[now];
	Tree ans={0,0,inf,0};
	int mid=tr[now].l+tr[now].r>>1;
	if(l<=mid){
		ans=query(now<<1,l,r);
		if(mid<r){
			Tree ans2=query(now<<1|1,l,r);
			ans.mi=min(ans.mi,ans.s+ans2.mi),ans.s+=ans2.s;
		}
	}
	else if(mid<r) ans=query(now<<1|1,l,r);
	return ans;
}

il void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		char ch;cin>>ch;
		if(ch=='(') a[i]=1;
		else a[i]=-1;
	}
	build(1,1,n);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1) swap(a[l],a[r]),insert(1,l,a[l]),insert(1,r,a[r]);
		else{
			Tree ans=query(1,l,r);
			if(ans.s!=0||ans.mi<0) printf("No\n");
			else printf("Yes\n");
		}
	}
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：AlicX (赞：1)

## Solution 

先考虑如果没有交换操作的情况，对于区间 $[l,r]$，如果这是一个合法的序列串：说明左括号的数量等于右括号，且从左往右左括号的数量一定大于等于右括号的数量。

于是考虑另 $s$ 为字符数组 $a$ 的前缀和数组，则判断条件为 $s_r-s_{l-1}=0$ 且 $\min_{i=l}^{r} s_i \geq s_{l-1}$，线段数维护即可。

现在考虑加入交换操作，只需要区间加减即可，时间复杂度为 $O(n\log n)$。


---

## 作者：Cosine_Func (赞：0)

考虑将括号序列转换为 $1$ 和 $-1$。则括号序列匹配的条件为：
- 区间和为 $0$
- 区间前缀和的最小值不小于 $0$

可以使用线段树维护。每个节点维护区间前缀和的最小值和区间和。

建树：
```cpp
void build(int p,int l,int r){
	l(p)=l,r(p)=r;
	if(l==r){
		sum(p)=minn(p)=a[l];
		return;
	}
	int mid=(l+r)/2;;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	push_up(p);
}
```
查询：
```cpp
pi query(int p,int l,int r){
	if(l<=l(p) and r(p)<=r)
		return make_pair(t[p].sum,t[p].minn);
	int mid=(l(p)+r(p))/2;
	pi L,R,ans;
	if(l<=mid)L=query(p*2,l,r);
	if(r>mid)R=query(p*2+1,l,r);
	ans.first=L.first+R.first;
	ans.second=min(L.second,L.first+R.second);
	return ans;
}
```
修改：
```cpp
void update(int p,int x,int k){
	if(l(p)==r(p)){
		sum(p)=minn(p)=k;
		return;
	}
	int mid=(l(p)+r(p))/2;
	if(x<=mid)update(p*2,x,k);
	else update(p*2+1,x,k);
	push_up(p);
}
```
[参考代码](https://atcoder.jp/contests/abc223/submissions/60792270)

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc223_f)
## 思路
首先，括号串匹配当切仅当左括号和右括号数量相等，且任意子串 $[1,x]$（$1\le x\le |S|$）左括号数量减右括号数量都 $\ge 0$。

令左括号贡献值为 $1$，右括号贡献值为 $-1$，$sum_i$ 代表子串 $[1,i]$ 贡献的和。

那对于任意子串，其为合法括号匹配串的充分必要条件为：

1. 串内左括号和右括号数量相等，即 $sum_r = sum_{l-1}$；
2. 对于任意 $i$（$l \le i \le r$），都有 $sum_i \ge 0$，即 $$\begin{aligned} \min _ {l \le i \le r}sum_i \ge 0\end{aligned}$$。

那我们就可以用线段树维护贡献前缀和的最小值。对于第一个性质，每次单点查询 $2$ 次，然后看是否相等。对于第 $2$ 个性质，区间查询 $[l, r]$ 的最小值。
## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

int n, q;
int t[N];
char s[N];

struct seg_tree
{
	struct node
	{
		int l, r, minn, lazy;
	} tr[4 * N];
	void push_up(int p)
	{
		tr[p].minn = min(tr[p * 2].minn, tr[p * 2 + 1].minn);
	}
	void push_down(int p)
	{
		if (tr[p].lazy)
		{
			tr[p * 2].lazy += tr[p].lazy;
			tr[p * 2 + 1].lazy += tr[p].lazy;
			tr[p * 2].minn += tr[p].lazy;
			tr[p * 2 + 1].minn += tr[p].lazy;
			tr[p].lazy = 0;
		}
	}
	void build(int p, int l, int r)
	{
		tr[p] = {l, r, (int)(2e9), 0};
		if (l == r)
		{
			tr[p].minn = t[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(p * 2, l, mid);
		build(p * 2 + 1, mid + 1, r);
		push_up(p);
	}
	void update(int p, int l, int r, int x)
	{
		if (tr[p].r < l || tr[p].l > r) return; 
		if (tr[p].l >= l && tr[p].r <= r)
		{
			tr[p].minn += x;
			tr[p].lazy += x;
			return;
		}
		push_down(p);
		int mid = (l + r) >> 1;
		if (l <= mid) update(p * 2, l, r, x);
		if (r > mid) update(p * 2 + 1, l, r, x);
		push_up(p);
	}
	int query(int p, int l, int r)
	{
		if (tr[p].r < l || tr[p].l > r) return (int)(2e9); 
		if (tr[p].l >= l && tr[p].r <= r) return tr[p].minn;
		push_down(p);
		int mid = (tr[p].l + tr[p].r) >> 1, res = (int)(2e9);
		if (l <= mid) res = min(res, query(p * 2, l, r));
		if (r > mid) res = min(res, query(p * 2 + 1, l, r));
		return res;
	}
} ST;

signed main()
{
	scanf("%lld%lld%s", &n, &q, s + 1);
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == '(') t[i] = t[i - 1] + 1;
		else t[i] = t[i - 1] - 1;
	}
	ST.build(1, 1, n);
	while (q--)
	{
		int op, l, r;
		scanf("%lld%lld%lld", &op, &l, &r);
		if (op == 1)
		{
			if (s[l] == s[r]) continue;
			if (s[l] == '(')
			{
				ST.update(1, l, n, -2);
				ST.update(1, r, n, 2);
			}
			else
			{
				ST.update(1, l, n, 2);
				ST.update(1, r, n, -2);
			}
			swap(s[l], s[r]);
		}
		else
		{
			int k1 = 0, k2 = ST.query(1, r, r), k3 = ST.query(1, l, r);
			if (l == 1) k1 = 0;
			else k1 = ST.query(1, l - 1, l - 1);
			if (k1 == k2 && k3 >= k1) puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
```

---

## 作者：2020luke (赞：0)

# [[ABC223F] Parenthesis Checking](https://www.luogu.com.cn/problem/AT_abc223_f) 题解

## 思路解析

在开始之前，首先我们需要知道合法括号序列的判断方法。我们可以给每个括号打上权值，设左括号权值为 $1$，右括号权值为 $-1$，这样一个 $\texttt{(()())}$ 括号串用数字存下就是 $1,1,-1,1,-1,-1$，这时我们再给序列计算一下前缀和就成了 $1,2,1,2,1,0$。此时我们发现序列有一个性质就是元素全部大于等于 $0$，同时结尾的元素一定为 $0$。而例如我们找一个括号序列 $\texttt{)()(}$，它的前缀和数组为 $-1,0,-1,0$，可见虽然结尾是 $0$，但中间有元素小于 $0$，因此该括号序列并不合法。

现在我们已经知道了如何通过序列的前缀和数组判断该序列是否合法，接下来我们就考虑如何修改。我们可以先把前缀和数组存下来，然后考虑每一次交换会对这个数组产生怎样的影响。首先，若交换 $l,r$ 两个位置上的括号，我们可以发现区间 $[1,l-1]$ 和 $[r,n]$ 是没有影响的，真正有影响的只有 $[l,r-1]$ 这个区间。接下来我们分两种情况考虑：

- 若 $l$ 位上的括号交换前是左括号时，可见由于第 $l$ 位从 $1$ 改成了 $-1$，所以就会对该区间加上 $-2$ 的权值。
- 若 $l$ 位上的括号交换前是右括号时，可见由于第 $l$ 位从 $-1$ 改成了 $1$，所以就会对该区间加上 $2$ 的权值。

最后考虑如何实现，我们需要做到区间求最小值，单点查询，区间加三种操作，可以想到使用线段树维护。注意由于我们存的值是前缀和，所以需要减去 $l-1$ 位置上的值才能得到正确的值。记得特判 $l-1=0$ 时的情况。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 8e5 + 10;
string str;
int n, q, a[N], s[M], t[M];
void push_up(int p) {
	int ls = (p << 1), rs = (p << 1) + 1;
	s[p] = min(s[ls], s[rs]);
}
void build(int p, int l, int r) {
	if(l == r) {
		s[p] = a[l];
		return;
	}
	int m = l + ((r - l) >> 1), ls = (p << 1), rs = (p << 1) + 1;
	build(ls, l, m);
	build(rs, m + 1, r);
	push_up(p);
}
void addt(int p, int l, int r, int k) {
	s[p] += k;
	t[p] += k;
}
void push_down(int p, int l, int r) {
	if(!t[p]) return;
	int m = l + ((r - l) >> 1), ls = (p << 1), rs = (p << 1) + 1;
	addt(ls, l, m, t[p]);
	addt(rs, m + 1, r, t[p]);
	t[p] = 0;
}
void add(int p, int l, int r, int x, int y, int k) {
	if(r < x || l > y) return;
	if(l >= x && r <= y) {
		addt(p, l, r, k);
		return;
	}
	push_down(p, l, r);
	int m = l + ((r - l) >> 1), ls = (p << 1), rs = (p << 1) + 1;
	add(ls, l, m, x, y, k);
	add(rs, m + 1, r, x, y, k);
	push_up(p);
}
int ask(int p, int l, int r, int x, int y) {
	if(r < x || l > y) return 2e9;
	if(l >= x && r <= y) return s[p];
	push_down(p, l, r);
	int m = l + ((r - l) >> 1), ls = (p << 1), rs = (p << 1) + 1;
	return min(ask(ls, l, m, x, y), ask(rs, m + 1, r, x, y));
}
int main() {
	cin >> n >> q;
	cin >> str;
	str = ' ' + str;
	for(int i = 1; i <= n; i++) {
		a[i] = a[i - 1];
		if(str[i] == '(') a[i]++;
		else a[i]--;
	}
	build(1, 1, n);
	while(q--) {
		int op, l, r;
		cin >> op >> l >> r;
		if(op == 1) {
			if(str[l] != str[r]) {
				if(str[l] == '(') add(1, 1, n, l, r - 1, -2);
				else add(1, 1, n, l, r - 1, 2);
				swap(str[l], str[r]);
			}
		}
		else {
			int tmp = ask(1, 1, n, l - 1, l - 1);
			if(l == 1) tmp = 0;
			int t1 = ask(1, 1, n, l, r - 1) - tmp, t2 = ask(1, 1, n, r, r) - tmp;
			if(t1 >= 0 && t2 == 0) cout << "Yes\n";
			else cout << "No\n";
		}
	}
	return 0;
}
```

---

## 作者：xz001 (赞：0)

- 首先我们把左括号转化为 $1$，右括号看作 $-1$。
- 我们用线段树维护这样转化后的前缀和的最小值和区间和，修改的话按照情况改一下就可以了，重要的是查询，合法括号序列经转化后必须保证其任意前缀非负且其总和为 $0$，就是说如果这一段区间的最小值大于等于 $sum_{l-1}$ 并且其区间和为 $0$，则为合法括号序列，否则不是。

- 代码如下：

```cpp
#include<bits/stdc++.h>
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define fa(x) ((x)>>1)
#define int long long
using namespace std;

const int N = 200005;

struct node {
	int l, r, minn, sum, add;
};

node t[4 * N];

int a[N];

char s[N];

inline void push_up (int p) {
	t[p].minn = min(t[ls(p)].minn, t[rs(p)].minn);
	t[p].sum = t[ls(p)].sum + t[rs(p)].sum;
	return;
}

inline void build (int l, int r, int p) {
	t[p].l = l;
	t[p].r = r;
	if (l == r) {
		t[p].sum = a[l];
		t[p].minn = a[l];
		return;
	}
	int mid = l + r >> 1;
	build (l, mid, ls(p));
	build (mid + 1, r, rs(p));
	push_up(p);
	return;
}

inline void lazy_tag (int p, int add) {
	t[p].sum += (t[p].r - t[p].l + 1) * add;
	t[p].minn += add;
	t[p].add += add;
	return;
}

inline void push_down (int p) {
	lazy_tag (ls(p), t[p].add);
	lazy_tag (rs(p), t[p].add);
	t[p].add = 0;
	return;
}

inline void update (int l, int r, int p, int add) {
	if (l <= t[p].l && t[p].r <= r) {
		lazy_tag (p, add);
		return;
	}
	push_down(p);
	int mid = t[p].l + t[p].r >> 1;
	if (l <= mid) update (l, r, ls(p), add);
	if (r > mid) update (l, r, rs(p), add);
	push_up(p);
	return;
}

inline int query1 (int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r) {
		return t[p].sum;
	}
	push_down(p);
	int mid = t[p].l + t[p].r >> 1, sum = 0;
	if (l <= mid) sum += query1 (l, r, ls(p));
	if (r > mid) sum += query1 (l, r, rs(p));
	return sum;
}

inline int query2 (int l, int r, int p) {
	if (l <= t[p].l && t[p].r <= r) {
		return t[p].minn;
	}
	push_down(p);
	int mid = t[p].l + t[p].r >> 1, sum = 1e18;
	if (l <= mid) sum = min(sum, query2 (l, r, ls(p)));
	if (r > mid) sum = min(sum, query2 (l, r, rs(p)));
	return sum;
}

signed main() {
	int n, m;
	scanf("%lld%lld%s", &n, &m, s + 1);
	for (int i = 1; i <= n; ++ i) a[i] = a[i - 1] + (s[i] == '(' ? 1 : -1);
	build (1, n, 1);
	while (m -- ) {
		int op, l, r;
		scanf("%lld%lld%lld", &op, &l, &r);
		if (op == 1) {
		    if (s[l] == s[r]) continue;
		    if (s[l] == '(') {
		    	update (l, n, 1, -2);
		    	update (r, n, 1, 2);
			} else {
				update (l, n, 1, 2);
				update (r, n, 1, -2);
			}
			swap(s[l], s[r]);
		} else {
			int ll = (l == 1) ? 0 : query1 (l - 1, l - 1, 1);
			int sum = query2 (l, r, 1);
			if (sum >= ll && query1 (r, r, 1) - ll == 0) printf("Yes\n");
			else printf("No\n");
		}
	}
	return 0;
} 
```


---

## 作者：qiuzijin2026 (赞：0)

# [ABC223F] Parenthesis Checking

## [题面](https://www.luogu.com.cn/problem/AT_abc223_f)

## 思路
本题使用线段树。

我们会发现一个序列如果合法那么一定满足：

- 左括号与右括号数量相等。

- 每个位置之前的右括号数量小于等于左括号数量。

我们令左括号为 $ 1 $，右括号为 $ -1 $。则两个条件就变成了：

- 整个序列的和为 $ 0 $。

- 每个位置之前的和都大于 $ 0 $。

于是我们就可以用一棵线段树来维护之前的和。

对于第一种操作，直接暴力单点修改：

- 如果两个位置的字符相等，直接忽略本次操作，因为交换两个相同的字符相当于没交换。

- 如果两个位置的字符不等，``(`` 的位置 $ -2 $，``)`` 的位置 $ +2 $。

对于第二种操作，查询区间 ``l`` 到 ``r``，并在查询中判断每个位置之前的和即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
string s;
long long a[200005];
long long w[800005];
long long tag[800005];
long long minn[800005];
long long tmpmin;
long long cnt;
long long tp;
void maketag(long long u,long long l,long long k){
	tag[u]+=k;
	w[u]+=l*k;
	return;
}


void pushup(long long u){
	w[u]=w[u<<1]+w[(u<<1)+1];
	minn[u]=min(minn[u<<1],w[u<<1]+minn[(u<<1)+1]);
	return;
}


void pushdown(long long u,long long l,long long r){
	long long m=(l+r)>>1;
	maketag(u<<1,m-l+1,tag[u]);
	maketag((u<<1)+1,r-m,tag[u]);
	tag[u]=0;
}


void build(long long u,long long l,long long r){
	if(l==r){
		w[u]=a[l];
		return ;
	}
	long long m=(l+r)>>1;
	build(u<<1,l,m);
	build((u<<1)+1,m+1,r);
	pushup(u);
}


void query(long long u,long long yl,long long yr,long long l,long long r){
	if(l<=yl && yr<=r){
		tmpmin=min(tmpmin,cnt+minn[u]);
		cnt+=w[u];
		return ;
	} 
	if(l>yr || r<yl) return;
	long long m=(yl+yr)>>1;
	pushdown(u,yl,yr);
	query(u<<1,yl,m,l,r);
	query((u<<1)+1,m+1,yr,l,r);
}


void update(long long u,long long yl,long long yr,long long l,long long r,long long k){
	if(l<=yl && yr<=r){
		maketag(u,yr-yl+1,k);
		return;
	}
	if(l>yr || r<yl) return ;
	long long m=(yl+yr)>>1;
	pushdown(u,yl,yr);
	update(u<<1,yl,m,l,r,k);
	update((u<<1)+1,m+1,yr,l,r,k);
	pushup(u);
}


int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	tp=scanf("%lld%lld",&n,&m);
	cin>>s;
	for(long long i=0;i<n;i++) 
		if(s[i]=='(') a[i+1]=1;
		else a[i+1]=-1;
	build(1,1,n);
	for(long long i=1,tmp,x,y;i<=m;i++){
		tp=scanf("%lld%lld%lld",&tmp,&x,&y);
		if(tmp==1){
			if(s[x-1]=='(' && s[y-1]==')'){
				update(1,1,n,x,x,-2);
				update(1,1,n,y,y,2);
			} 
			else if(s[x-1]==')' && s[y-1]=='('){
				update(1,1,n,x,x,2);
				update(1,1,n,y,y,-2);
			} 
			swap(s[x-1],s[y-1]);
		} 
		else{
			tmpmin=0x7fffffffffffffff;
			cnt=0;
			query(1,1,n,x,y);
			if(tmpmin!=0 || cnt!=0) printf("No\n");
			else printf("Yes\n"); 
		} 
	}
	return 0;
}

```
因为是套的模板，所以里面没有单点操作都是区间操作。

---

## 作者：ttq012 (赞：0)

这题不得蓝？[同类题](https://www.luogu.com.cn/problem/SP61)

首先考虑暴力。

一个序列是括号序列的充要条件是：

+ 左括号和右括号的数量恰好相等。
+ 在任意时刻左括号的数量都不小于右括号的数量。

考虑把问题抽象化。令左括号为 $1$，右括号为 $-1$。问题转化为了给一个序列判断这个序列的和是否是 $0$ 并且序列的前缀和 $s'$ 满足 $s'$ 的任意一项的值都 $\ge 0$。

单组询问好处理，考虑 Middle 版本多组询问但是没有修改。

首先定义一段区间 $[l,r]$ 的“左最小和”是 $\min_{i=l}^r \sum_{j=l}^i a_j$。也就是从最左边开始到区间中任意一个点这一段的和得到的最小值。

发现考虑用一个线段树来维护。

线段树维护一段区间的和和一段区间的“左最小和”。

一段区间 $[l,r]$ 是一个合法的括号序列当且仅当 $[l,r]$ 这一段区间的“左最小和”为 $0$ 且一段区间的和恰好为 $0$。

按照套路维护一下即可。

Hard Version（本题）：发现有修改操作，修改操作是交换两个位置的值。

考虑把修改的交换操作修改成修改两个位置的值。这样就变成了单点修改问题，套路维护一下即可。

时间复杂度是 $O(n\log n)$ 的，可过。

---

## 作者：_zzzzzzy_ (赞：0)

# 思路
如果这一道题把修改操作去掉就成了一个很简单的题，我们考虑怎么判定一段区间合法符合的条件。

- 左括号和右括号的个数相等。
- 在遍历的过程中左括号的数量始终大于等于右括号。

我们可以把左括号看成 $1$，右括号看成 `-1`，那么最后如果这一段区间是合法的，这一段区间的和一定是 $0$。

我们再来考虑怎么判断序列是否满足第二个，如果左括号的个数在遍历过程中小于了右括号，那么在求和中的表现就是出现了负数，我们可以维护一个最小值，当查询的时候这个最小值小于 $0$ 时，表示不满足第二个条件。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define lc(x)(x<<1)
#define rc(x)(x<<1|1)
using namespace std;
const int maxn=10000000;
char str[maxn];
int mn,sum;
struct node{
	int l,r,sum,mn;
}tr[maxn<<2];
void pushup(int x){
	tr[x].sum=tr[lc(x)].sum+tr[rc(x)].sum;
	tr[x].mn=min(tr[lc(x)].mn,tr[lc(x)].sum+tr[rc(x)].mn);
}
void build(int x,int l,int r){
	tr[x].l=l,tr[x].r=r;
	if(l==r){
		tr[x].sum=str[l]=='('?1:-1;
		return;
	}
	int mid=(l+r)>>1;
	build(lc(x),l,mid),build(rc(x),mid+1,r);
	pushup(x);
}
void update(int x,int id,int val){
	if(tr[x].l==tr[x].r){
		tr[x].sum=val;
		return;
	}
	int mid=(tr[x].l+tr[x].r)>>1;
	if(id<=mid)update(lc(x),id,val);
	else update(rc(x),id,val);
	pushup(x);
}
void query(int x,int l,int r){
	if(l<=tr[x].l&&r>=tr[x].r){
		mn=min(mn,sum+tr[x].mn);
		sum+=tr[x].sum;
		return;
	}
	int mid=(tr[x].l+tr[x].r)>>1;
	if(l<=mid)query(lc(x),l,r);
	if(r>mid)query(rc(x),l,r);
}
signed main(){
	int n,m;
	cin>>n>>m>>(str+1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1){
			if(str[l]!=str[r]){
				if(str[l]=='(')update(1,l,-1),update(1,r,1);
				if(str[l]==')')update(1,l,1),update(1,r,-1);
				swap(str[l],str[r]);
			}
		}
		else{
			mn=INT_MAX,sum=0;
			query(1,l,r);
			if(mn==0&&sum==0)cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}
```

---

