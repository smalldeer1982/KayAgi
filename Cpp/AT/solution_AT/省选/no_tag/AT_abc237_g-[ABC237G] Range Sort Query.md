# [ABC237G] Range Sort Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc237/tasks/abc237_g

$ 1,2,\ldots,N $ を並び替えた長さ $ N $ の順列 $ P=(P_1,P_2,\ldots,P_N) $ と整数 $ X $ が与えられます。

また、$ Q $ 個のクエリが与えられます。 $ i $ 番目のクエリは $ 3 $ つの数の組 $ (C_i,L_i,R_i) $ で表されます。各クエリでは順列 $ P $ に対して次の操作を行います。

- $ C_i=1 $ のとき : $ P_{L_i},P_{L_i+1},\ldots,P_{R_i} $ を昇順に並び替える。
- $ C_i=2 $ のとき : $ P_{L_i},P_{L_i+1},\ldots,P_{R_i} $ を降順に並び替える。

クエリを $ 1 $ 番目から順に最後まで処理したとき、最終的な順列において $ P_i=X $ となる $ i $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X\ \leq\ N $
- $ (P_1,P_2,\ldots,P_N) $ は $ (1,2,\ldots,N) $ の並び替えである。
- $ 1\ \leq\ C_i\ \leq\ 2 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ N $
- 入力は全て整数である。

### Sample Explanation 1

最初、順列は $ P=[1,4,5,2,3] $ です。 これはクエリによって次のように変化します。 - $ 1 $ つめのクエリでは $ 3 $ 番目から $ 5 $ 番目の要素を昇順にソートします。順列は $ P=[1,4,2,3,5] $ となります。 - $ 2 $ つめのクエリでは $ 1 $ 番目から $ 3 $ 番目の要素を降順にソートします。順列は $ P=[4,2,1,3,5] $ となります。 最終的な順列において $ P_3=1 $ であるので、$ 3 $ を出力します。

### Sample Explanation 2

最終的な順列は $ P=[1,2,6,5,7,4,3] $ となります。

## 样例 #1

### 输入

```
5 2 1
1 4 5 2 3
1 3 5
2 1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
7 3 3
7 5 3 1 2 4 6
1 1 7
2 3 6
2 5 7```

### 输出

```
7```

# 题解

## 作者：small_john (赞：8)

## 思路

还是挺巧妙的。

这道题和 [P2824](https://www.luogu.com.cn/problem/P2824) 很像，都是对一个区间排序，唯一的区别就是这道题要求一个数 $x$ 的最终位置。

考虑沿用 [P2824](https://www.luogu.com.cn/problem/P2824) 的思想，我们把大于等于 $x$ 设为 $1$，小于 $x$ 的设为 $0$。对一个区间升序排序就是把区间变成一段 $0$ 和一段 $1$，降序也是同理的。这个可以用线段树维护。

那如何求出数 $x$ 的位置呢，总不能二分吧？

我们可以再做一遍，只不过第二次是大于 $x$ 设为 $1$，小于等于 $x$ 的设为 $0$。这两个序列的唯一区别就是等于 $x$ 的地方一个是 $1$，一个是 $0$。

所以每次把最终序列存入数组中，一个位置对应的两个数不同就是答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 2e5+5;
int n,q,p,a[N];
//线段树
struct node{
	int val,tag;
}t[N<<2];
#define ls (k*2)
#define rs (k*2+1) 
inline void pushup(int k)
{
	t[k].val = t[ls].val+t[rs].val;
}
inline void down(int k,int l,int r,int mid)
{
	if(!t[k].tag) return;
	if(t[k].tag==1) t[ls].val = mid-l+1,t[rs].val = r-mid;
	else t[ls].val = t[rs].val = 0;
	t[ls].tag = t[rs].tag = t[k].tag,t[k].tag = 0;
}
void build(int k,int l,int r,int x)//建树
{
	t[k].tag = 0;
	if(l==r) return t[k].val = (a[l]>=x),void();
	int mid = (l+r)/2;
	build(ls,l,mid,x),build(rs,mid+1,r,x);
	pushup(k);
}
void change(int k,int l,int r,int x,int y,int v)//区间覆盖
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return t[k].val = (r-l+1)*v,t[k].tag = v?1:-1,void();
	int mid = (l+r)/2;
	down(k,l,r,mid);
	change(ls,l,mid,x,y,v),change(rs,mid+1,r,x,y,v);
	pushup(k);
}
int ask(int k,int l,int r,int x,int y)//询问一个区间里有多少个一
{
	if(l>y||r<x) return 0;
	if(l>=x&&r<=y) return t[k].val;
	int mid = (l+r)/2;
	down(k,l,r,mid);
	return ask(ls,l,mid,x,y)+ask(rs,mid+1,r,x,y);
}
void dfs(int k,int l,int r,int *a)//把最终结果放入数组 a 中
{
	if(l==r) return a[l] = t[k].val,void();
	int mid = (l+r)/2;
	down(k,l,r,mid);
	dfs(ls,l,mid,a),dfs(rs,mid+1,r,a);
}
#undef ls
#undef rs
int _op[N],_l[N],_r[N],va[N],vb[N];
//对一个阈值排序
void work(int x,int *a)//传个指针，方便修改数组
{
	build(1,1,n,x);
	for(int i = 1,op,l,r;i<=q;i++)
	{
		op = _op[i],l = _l[i],r = _r[i];
		int len = ask(1,1,n,l,r);
		if(op==1) change(1,1,n,l,r-len,0),change(1,1,n,r-len+1,r,1);//升序就是一段零接上一段一
		else change(1,1,n,l,l+len-1,1),change(1,1,n,l+len,r,0);//降序就是一段一接上一段零
	}
	dfs(1,1,n,a);
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(q),read(p);
	for(int i = 1;i<=n;i++)
		read(a[i]);
	for(int i = 1;i<=q;i++)
		read(_op[i]),read(_l[i]),read(_r[i]);
	work(p,va),work(p+1,vb);//排两次序
	for(int i = 1;i<=n;i++)
		if(va[i]!=vb[i]) return write(i),0;//找不同
	return 0;
}


---

## 作者：Register_int (赞：4)

看到这道题的第一眼，我就想起了 [P2824](/problem/P2824)。不过，这提示要根据数来求位置，根本就没什么东西可以二分。~~所以我选择摆烂~~

考虑和那道典题一样的套路，将每个数重新赋值成 $0,1,2$ 中的一个，分别代表：小于 $x$，等于 $x$，大于 $x$。那么修改过后枚举找到 $1$ 就能确定 $x$ 的位置了。

然而还不是很好维护。能否化成 $0/1$ 串的操作呢？可以！一个串搞不定，把他拆成两串，$0,1,2$ 分别拆成 $0/0,0/1,1/1$。那么这样就可以直接将排序转化为区间赋值，直接按照原来的方法做就可以了。时间复杂度 $O(n\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int a[MAXN];

struct segtree {
	
	struct node {
		int l, r, sum, tag;
	} t[MAXN << 2];
	
	inline 
	int len(int p) {
		return t[p].r - t[p].l + 1;
	}
	
	inline 
	void pushup(int p) {
		t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
	}
	
	inline 
	void pushdown(int p) {
		if (!~t[p].tag) return ;
		t[p << 1].sum = t[p].tag * len(p << 1);
		t[p << 1 | 1].sum = t[p].tag * len(p << 1 | 1);
		t[p << 1].tag = t[p].tag, t[p << 1 | 1].tag = t[p].tag;
		t[p].tag = -1;
	}
	
	void build(int l, int r, int k, int p) {
		t[p].l = l, t[p].r = r, t[p].tag = -1;
		if (l == r) return t[p].sum = (a[l] >= k), void();
		int mid = l + r >> 1;
		build(l, mid, k, p << 1), build(mid + 1, r, k, p << 1 | 1);
		pushup(p);
	}
	
	void update(int l, int r, int k, int p) {
		if (l > r) return ;
		if (l <= t[p].l && t[p].r <= r) return t[p].sum = k * len(p), t[p].tag = k, void();
		pushdown(p);
		int mid = t[p].l + t[p].r >> 1;
		if (l <= mid) update(l, r, k, p << 1);
		if (r > mid) update(l, r, k, p << 1 | 1);
		pushup(p);
	}
	
	int query(int l, int r, int p) {
		if (l <= t[p].l && t[p].r <= r) return t[p].sum;
		pushdown(p);
		int mid = t[p].l + t[p].r >> 1, res = 0;
		if (l <= mid) res += query(l, r, p << 1);
		if (r > mid) res += query(l, r, p << 1 | 1);
		return res;
	}
	
	int get(int k, int p) {
		if (k == t[p].l && t[p].r == k) return t[p].sum;
		pushdown(p);
		int mid = t[p].l + t[p].r >> 1;
		return get(k, p << 1 | k > mid);
	}
} t1, t2;

int n, m, q;

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	t1.build(1, n, q, 1), t2.build(1, n, q + 1, 1);
	for (int opt, l, r, t; m--;) {
		scanf("%d%d%d", &opt, &l, &r);
		t = t1.query(l, r, 1);
		if (opt == 1) t1.update(l, r - t, 0, 1), t1.update(r - t + 1, r, 1, 1);
		else t1.update(l, l + t - 1, 1, 1), t1.update(l + t, r, 0, 1);
		t = t2.query(l, r, 1);
		if (opt == 1) t2.update(l, r - t, 0, 1), t2.update(r - t + 1, r, 1, 1);
		else t2.update(l, l + t - 1, 1, 1), t2.update(l + t, r, 0, 1);
	}
	for (int i = 1; i <= n; i++) if (t1.get(i, 1) != t2.get(i, 1)) return printf("%d", i), 0;
}
```

---

## 作者：ty_mxzhn (赞：4)

题目：给你一些子串排序的操作，最后求值为 $X$ 的数的位置。

我不会直接排序的线段树做法，所以考虑转化。

把值与 $X$ 的大小关系记录下来，记为 $\{b_i\}$ 这个序列。比如把大于记为 $2$ ，把小于记为 $0$ ，相等记为 $1$ 。

那么排序相当于直接排这个序列。反正所有小于 $X$ 的数之间的大小关系不重要，大于同理。这个做法显然是正确的。

先把 $[l,r]$ 间的数值和查询，把结果整除 $2$ 得到区间内大于 $X$ 的数的数量。推导再得到小于 $X$ 的数的数量。

随后只需要区间赋值即可。

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct stu{
	int data;
	int tag;
}tr[4*1000007];
int n,q,x,o,l,r,pos,d[1000007],c[1000007];
void build(int lb,int ub,int k){
	tr[k].tag=-1; 
	if(lb==ub){
		tr[k].data=c[lb];
		return;
	}
	int mid=lb+ub>>1;
	build(lb   ,mid,k<<1  );
	build(mid+1 ,ub ,k<<1|1);
	tr[k].data=tr[k<<1].data+tr[k<<1|1].data;
}
void dtag(int k,int lb,int ub){
	if(tr[k].tag>-1){
		tr[k<<1].tag=tr[k].tag;
	   tr[k<<1|1].tag=tr[k].tag;
	   int mid=lb+ub>>1;
	   tr[k<<1].data  =tr[k].tag*(mid-lb+1);
	   tr[k<<1|1].data=tr[k].tag*(ub-mid  );
	   tr[k].tag=-1;
	} 
}
int query(int a,int b,int lb,int ub,int k){
	if(k<=0) return 0;
	if(a<=lb&&ub<=b){
		return tr[k].data;
	}
	dtag(k,lb,ub);
	int mid=lb+ub>>1;
	int ans=0;
	if(a<=mid) ans=ans+query(a,b,lb   ,mid,k<<1  );
	if(b>mid)  ans=ans+query(a,b,mid+1 ,ub ,k<<1|1);
	return ans;
}
void upd(int a,int b,int x,int lb,int ub,int k){
	if(k<=0) return;
	if(a<=lb&&ub<=b){
		tr[k].tag=x;
		tr[k].data=x*(ub-lb+1);
		return ;
	}
	dtag(k,lb,ub);
	int mid=lb+ub>>1;
	if(a<=mid) upd(a,b,x,lb   ,mid,k<<1  );
	if(b>mid)  upd(a,b,x,mid+1 ,ub ,k<<1|1);
	tr[k].data=tr[k<<1].data+tr[k<<1|1].data;
}
int main(){
	scanf("%d%d%d",&n,&q,&x);
	for(int i=1;i<=n;i++){
		scanf("%d",&d[i]);
		if(d[i]<x)  c[i]=0;
		if(d[i]==x) c[i]=1;
		if(d[i]>x)  c[i]=2;
	}
	build(1,1000000,1);
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&o,&l,&r);
		if(l<0||r<0||l>n||r>n){
			printf("%d",0);
		}
		if(l>r) swap(l,r);
		int aa=query(l,r,1,1000000,1);
		int z=r-l+1-((aa+1)/2),t=(aa)/2;
		if(o==1){
			if(aa&1){
				if(z!=0) upd(l    ,l+z-1,0,1,1000000,1);
				upd(l+z  ,l+z  ,1,1,1000000,1);
				upd(l+z+1,r   ,2,1,1000000,1);
			}else{
				if(z!=0) upd(l    ,l+z-1,0,1,1000000,1);
				upd(l+z  ,r   ,2,1,1000000,1);
			}
		}else{
			if(aa&1){
				if(t!=0) upd(l    ,l+t-1,2,1,1000000,1);
				upd(l+t  ,l+t  ,1,1,1000000,1);
				upd(l+t+1,r   ,0,1,1000000,1);
			}else{
				if(t!=0) upd(l    ,l+t-1,2,1,1000000,1);
				upd(l+t  ,r   ,0,1,1000000,1);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(query(i,i,1,1000000,1)==1){
			printf("%d\n",i);
		}
	}
	return 0;
}
```

奇怪的码风主要是为了方便前后对比，不喜勿喷。



---

## 作者：C6H14 (赞：3)

## 题目大意

给一个 $1$ 到 $N$ 的排列 $\{ P_i \}$ 和一个数 $X$，维护两种操作：

- $1 \ L_i \ R_i$ 表示将 $P_{L_i},P_{L_i+1},\dots P_{R_i}$ 升序排序；

- $2 \ L_i \ R_i$ 表示将 $P_{L_i},P_{L_i+1},\dots P_{R_i}$ 降序排序；

问 $Q$ 次操作后 $X$所在位置的下标，$ x \leqslant n,q,n \leqslant 2 \times 10^5$。

## 思路

康康这道典题：[排序](https://www.luogu.com.cn/problem/P2824)。

由于我们只关心 $X$ 的位置，其他数是多少并不重要，所以可以将信息压缩：

我们将所有满足 $P_i < X$ 的 $P_i$ 都改为 $0$，所有满足 $P_i \geqslant X$ 的 $P_i$ 都改为 $1$。

但是这样 $X$ 也会被改为 $1$，随便一排序就找不到 $X$的位置了。

所以我们可以复制出另一个数组 $\{ P_i \}$，然后将所有满足 $P_i \leqslant X$ 的 $P_i$ 都改为 $0$，所有满足 $P_i > X$ 的 $P_i$ 都改为 $1$，这样每次操作后两个数组一定会有一个位置不一样，这个位置就是 $X$ 所在位置。

接下来考虑如何维护排序，其实就是将区间所有 $0$ 放一边，所有 $1$ 放另一边。

升序排序时直接统计区间内 $1$ 的数量，然后全部赋值为 $0$，再将末尾一段与 $1$ 个数相同的区间都赋值为 $1$，懒标记下传时注意一点就行。降序排序同理。

操作完后直接遍历线段树叶子结点，找不同即可，时间复杂度 $O(q \log n)$

## 代码

```cpp
struct tree
{
	int l,r,l1,l0,o;
} t[2][1600005];
void build(int ,int ,int );
int a1(int ,int ,int ,int );
void c1(int ,int ,int ,int );
void c0(int ,int ,int ,int );
void pushdown(int ,int );
void dfs(int );
ll n,a[200005],q,x;
int main()
{
	n=read(),q=read(),x=read();
	for (int i=1;i<=n;++i)
		a[i]=read();
	build(1,1,n);
	while (q--)
	{
		int l,r;
		if (read()==1)
		{
			l=read(),r=read();
			int tmp=a1(1,l,r,0);
			c0(1,l,r,0);
			c1(1,r-tmp+1,r,0);
			tmp=a1(1,l,r,1);
			c0(1,l,r,1);
			c1(1,r-tmp+1,r,1);
		}
		else
		{
			l=read(),r=read();
			int tmp=a1(1,l,r,0);
			c0(1,l,r,0);
			c1(1,l,l+tmp-1,0);
			tmp=a1(1,l,r,1);
			c0(1,l,r,1);
			c1(1,l,l+tmp-1,1);
		}
	}
	dfs(1);
	return 0;
}
void build(int no,int l,int r)
{
	t[0][no].l=t[1][no].l=l,t[0][no].r=t[1][no].r=r;
	if (l==r)
	{
		t[0][no].o=(a[l]>x);
		t[1][no].o=(a[l]>=x);
		return;
	}
	int mid=l+r>>1;
	build(no<<1,l,mid);
	build(no<<1|1,mid+1,r);
	t[0][no].o=t[0][no<<1].o+t[0][no<<1|1].o;
	t[1][no].o=t[1][no<<1].o+t[1][no<<1|1].o;
}
int a1(int no,int l,int r,int rt)
{
	if (t[rt][no].l>r || t[rt][no].r<l || l>r)
		return 0;
	if (t[rt][no].l>=l && t[rt][no].r<=r)
		return t[rt][no].o;
	pushdown(no,rt);
	return a1(no<<1,l,r,rt)+a1(no<<1|1,l,r,rt);
}
void c1(int no,int l,int r,int rt)
{
	if (t[rt][no].l>r || t[rt][no].r<l || l>r)
		return;
	pushdown(no,rt);
	if (t[rt][no].l>=l && t[rt][no].r<=r)
	{
		t[rt][no].o=t[rt][no].r-t[rt][no].l+1;
		t[rt][no].l1=1;
		return;
	}
	c1(no<<1,l,r,rt);
	c1(no<<1|1,l,r,rt);
	t[rt][no].o=t[rt][no<<1].o+t[rt][no<<1|1].o;
}
void c0(int no,int l,int r,int rt)
{
	if (t[rt][no].l>r || t[rt][no].r<l || l>r)
		return;
	pushdown(no,rt);
	if (t[rt][no].l>=l && t[rt][no].r<=r)
	{
		t[rt][no].o=0;
		t[rt][no].l0=1;
		return;
	}
	c0(no<<1,l,r,rt);
	c0(no<<1|1,l,r,rt);
	t[rt][no].o=t[rt][no<<1].o+t[rt][no<<1|1].o;
}
void pushdown(int x,int y)
{
	int l=x<<1,r=x<<1|1;
	if (t[y][x].l0)
	{
		t[y][l].l0=t[y][r].l0=1;
		t[y][l].l1=t[y][r].l1=t[y][x].l0=0;
		t[y][l].o=t[y][r].o=0;
	}
	else if (t[y][x].l1)
	{
		t[y][l].l1=t[y][r].l1=1;
		t[y][l].l0=t[y][r].l0=t[y][x].l1=0;
		t[y][l].o=t[y][l].r-t[y][l].l+1;
		t[y][r].o=t[y][r].r-t[y][r].l+1;
	}
}
void dfs(int no)
{
	if (t[0][no].l==t[0][no].r)
	{
//		write(t[0][no].l,' ');
//		write(t[0][no].o,' '),write(t[1][no].o,'\n');
		if (t[0][no].o!=t[1][no].o)
		{
			write(t[0][no].l);
			exit(0);
		}
		return;
	}
	pushdown(no,0);
	pushdown(no,1);
	dfs(no<<1);
	dfs(no<<1|1);
}
```


---

## 作者：ForgotDream_CHN (赞：1)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17461885.html)

## 思路

这道题跟 P2824 的思路是很相似的。

首先由于我们只需求一个特定的值在排序后的位置，而原序列又是一个排列，因此我们可以将序列中的所有数分为三种：

1. 大于 $X$ 的；
2. 等于 $X$ 的；
3. 小于 $X$ 的。

我们不关心除了 $X$ 之外的其他值的具体数字，而只关心其与 $X$ 的大小关系，那么可以将数列抽象为一个 $01$ 序列。将序列中所有**大于等于** $X$ 的数字赋为 $1$，而**小于** $X$ 的数字赋为 $0$。然后利用线段树分类讨论即可以做到 $O(n \log n)$ 模拟题目中的所有排序操作。

但是问题在于，题目是要求我们找到 $X$ 这一个数字的具体位置，而上述的转化方法不支持我们找到 $X$ 具体的位置，因为所有大于等于 $X$ 的数字均对应 $1$。这该怎么办呢？

解决方法也很简单，再做一次就好了嘛！只不过这次，我们将所有**小于等于** $X$ 的值赋为 $0$，**大于** $X$ 的值赋为 $1$。这样，$X$ 在第一个序列中对应的是 $1$ ，而在第二个序列中对应的是 $0$，然后原序列又是一个排列，即只存在一个 $X$，于是利用这个性质我们就可以找到 $X$。

那么具体的怎么用线段树来完成 $01$ 序列的排序操作呢？很简单，由于只存在 $01$ 两种数字，那么其实排序就是一个区间推平的问题。首先统计出带求区间中 $1$ 的个数，如果不存在 $1$ 我们直接跳过，如果存在的话，先把区间拍成 $0$，然后若是升序就把所有的 $1$ 丢到序列的末尾，若是降序就丢到开头，这也是可以直接用区间推平维护的。

那么总的时间复杂度就做到了 $O(n \log n)$。

## 代码

```cpp
#include <bits/stdc++.h>

using i64 = long long;

struct SegTree {
  int n;
  struct Node { 
    int sum, tag, l, r; 
    Node() { sum = l = r = 0, tag = -1; }
  };
  friend Node operator+(const Node &lhs, const Node &rhs) {
    Node res;
    res.l = lhs.l, res.r = rhs.r, res.sum = lhs.sum + rhs.sum;
    return res;
  }
  std::vector<Node> tree;
  std::vector<int> a;
  SegTree(int _n) { n = _n, tree.resize((n << 2) + 1); }
  void build(int l, int r, int u) {
    if (l == r) {
      tree[u].l = l, tree[u].r = r, tree[u].sum = a[l - 1];
      return;
    }
    int mid = (l + r) >> 1, lc = u << 1, rc = u << 1 | 1;
    build(l, mid, lc), build(mid + 1, r, rc);
    tree[u] = tree[lc] + tree[rc];
  }
  void build(const std::vector<int> &_a) {
    a = _a;
    build(1, n, 1);
  }
  void tagging(int u, int val) {
    tree[u].sum = (tree[u].r - tree[u].l + 1) * val;
    tree[u].tag = val;
  }
  void pushdown(int u) {
    if (tree[u].tag == -1) { return; }
    tagging(u << 1, tree[u].tag), tagging(u << 1 | 1, tree[u].tag);
    tree[u].tag = -1;
  }
  void assign(int l, int r, int u, int val) {
    int s = tree[u].l, t = tree[u].r;
    if (l <= s && t <= r) {
      tagging(u, val);
      return;
    }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    if (mid >= l) { assign(l, r, lc, val); }
    if (mid <  r) { assign(l, r, rc, val); }
    tree[u] = tree[lc] + tree[rc];
  }
  int query(int l, int r, int u) {
    int s = tree[u].l, t = tree[u].r;
    if (l <= s && t <= r) { return tree[u].sum; }
    pushdown(u);
    int mid = (s + t) >> 1, lc = u << 1, rc = u << 1 | 1;
    int res = 0;
    if (mid >= l) { res += query(l, r, lc); }
    if (mid <  r) { res += query(l, r, rc); }
    return res;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, p;
  std::cin >> n >> m >> p;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  SegTree t1(n), t2(n);
  std::vector<int> b(n), c(n);
  for (int i = 0; i < n; i++) { b[i] = (a[i] >= p), c[i] = (a[i] > p); }
  t1.build(b), t2.build(c);
  
  for (int i = 0; i < m; i++) {
    int opt, l, r;
    std::cin >> opt >> l >> r;

    int cnt1 = t1.query(l, r, 1), cnt2 = t2.query(l, r, 1);
    t1.assign(l, r, 1, 0), t2.assign(l, r, 1, 0);
    if (opt == 2) {
      if (cnt1) { t1.assign(l, l + cnt1 - 1, 1, 1); }
      if (cnt2) { t2.assign(l, l + cnt2 - 1, 1, 1); }
    } else {
      if (cnt1) { t1.assign(r - cnt1 + 1, r, 1, 1); }
      if (cnt2) { t2.assign(r - cnt2 + 1, r, 1, 1); }
    }
  }

  for (int i = 1; i <= n; i++) {
    if ((!!t1.query(i, i, 1)) && (!t2.query(i, i, 1))) {
      std::cout << i << "\n";
      return 0;
    }
  }

  return 0;
}
```

---

## 作者：WaterSun (赞：0)

[更好的阅读体验](https://watersun.top/[%E9%A2%98%E8%A7%A3]AT_abc237_g%20[ABC237G]%20Range%20Sort%20Query)

# 思路

将小于等于 $x$ 的元素赋为 $1$，其余的赋为 $0$。那么一个区间内小于等于 $x$ 的数量就是区间中 $1$ 的数量。

那么，将区间升序排列就是将 $1$ 先堆在前面，将 $0$ 堆到后面；降序排列同理。

考虑动态维护 $x$ 的位置，记其位置为 $t$。如果 $l \leq t \leq r$，则 $t$ 可能会改变；否则不会改变。

在升序排列中，$t$ 将会改变到最后一个 $1$ 的位置；在降序排序中，$t$ 将会改变到第一个 $1$ 的位置。然后维护 $0/1$ 可以用线段树维护。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,q,k,x;
int arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int sum,tag;
    }tr[N << 2];
    
    inline void calc(int u,int k){
        tr[u].sum = (tr[u].r - tr[u].l + 1) * k;
        tr[u].tag = k;
    }

    inline void pushup(int u){
        tr[u].sum = tr[ls(u)].sum + tr[rs(u)].sum;
    }

    inline void pushdown(int u){
        if (~tr[u].tag){
            calc(ls(u),tr[u].tag); calc(rs(u),tr[u].tag);
            tr[u].tag = -1;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r,0,-1};
        if (l == r) return tr[u].sum = (arr[l] <= k),void();
        int mid = l + r >> 1;
        build(ls(u),l,mid); build(rs(u),mid + 1,r);
        pushup(u);
    }
    
    inline void modify(int u,int l,int r,int k){
        if (l > r) return;
        if (l <= tr[u].l && tr[u].r <= r) return calc(u,k);
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    inline int query(int u,int l,int r){
        if (l <= tr[u].l && tr[u].r <= r) return tr[u].sum;
        pushdown(u);
        int res = 0;
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) res += query(ls(u),l,r);
        if (r > mid) res += query(rs(u),l,r);
        return res;
    }

    #undef ls
    #undef rs
}T;

int main(){
    n = read(),q = read(),k = read();
    for (re int i = 1;i <= n;i++){
        arr[i] = read();
        if (arr[i] == k) x = i;
    }
    T.build(1,1,n);
    while (q--){
        int op,l,r;
        op = read(),l = read(),r = read();
        if (op == 1){
            int a = T.query(1,l,r);
            if (l <= x && x <= r) x = l + a - 1;
            T.modify(1,l,l + a - 1,1); T.modify(1,l + a,r,0);
        }
        else{
            int a = (r - l + 1) - T.query(1,l,r);
            if (l <= x && x <= r) x = l + a;
            T.modify(1,l,l + a - 1,0); T.modify(1,l + a,r,1);
        }
    }
    printf("%d",x);
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

好像和某道叫排序的题差不多。注意到数值在本题中并不重要，重要的是数值之间的相对关系，考虑将 $< x$ 的标记为 $0$，$> x$ 的标记为 $2$，$= x$ 的标记为 $1$。

对一个区间的升序 / 降序排序，就是将这一段赋成 `00...00122...22` / `22...22100...00` 的过程。这一部分可以直接上一棵线段树维护区间赋值。

由于时间给到了八秒，使用 bit 压位实现也未尝不可。

时间复杂度 $O(q \log n)$，如果拿 bit 压位实现，复杂度就是 $O(\dfrac{nq}{\omega})$，其中 $\omega$ 取决于你压位使用什么东西。
```cpp
void up(int u) { rep(i, 0, 2) s[u][i] = s[ls][i] + s[rs][i]; }
void push(int u, int l, int r, int v) { 
	tag[u][(v + 1) % 3] = tag[u][(v + 2) % 3] = 0, tag[u][v] = 1;
	s[u][(v + 1) % 3] = s[u][(v + 2) % 3] = 0; s[u][v] = r - l + 1;
}
void down(int u, int l, int r) {
	if (tag[u][0]) push(lb, 0), push(rb, 0), tag[u][0] = 0;
	if (tag[u][1]) push(lb, 1), push(rb, 1), tag[u][1] = 0;
	if (tag[u][2]) push(lb, 2), push(rb, 2), tag[u][2] = 0;
}
void build(int u, int l, int r) {
	if (l == r) return void(s[u][p[r]] ++ );
	build(lb), build(rb); up(u); return;
}
void chg(int u, int l, int r, int L, int R, int v) {
	if (l > R or L > r) return; if (l >= L and r <= R) return push(u, l, r, v);
	down(u, l, r); chg(lb, L, R, v), chg(rb, L, R, v); up(u);
}
int ask(int u, int l, int r, int L, int R, int v) {
	if (l > R or L > r) return 0; if (l >= L and r <= R) return s[u][v];
	down(u, l, r); return ask(lb, L, R, v) + ask(rb, L, R, v);
}
signed main() {
	scanf("%d%d%d", &n, &q, &x); rep(i, 1, n) scanf("%d", &p[i]);
	rep(i, 1, n) p[i] = (p[i] == x ? 1 : (p[i] > x ? 2 : 0)); build(T);
	for (int i = 1, op, l, r; i <= q; i ++ ) {
		scanf("%d%d%d", &op, &l, &r);
		int t0 = ask(1, 1, n, l, r, 0), t1 = ask(1, 1, n, l, r, 1), t2 = ask(1, 1, n, l, r, 2);
		if (op & 1) chg(T, l, l + t0 - 1, 0), chg(T, l + t0, l + t0 + t1 - 1, 1), chg(T, l + t0 + t1, r, 2);
		else chg(T, l, l + t2 - 1, 2), chg(T, l + t2, l + t2 + t1 - 1, 1), chg(T, l + t2 + t1, r, 0);
	} rep(i, 1, n) if (ask(1, 1, n, i, i, 1) == 1) return printf("%d\n", i), 0;
}
```

---

## 作者：船酱魔王 (赞：0)

# [ABC237G] Range Sort Query

## 题意回顾

给定长度为 $ n $ 的排列和被跟踪值 $ x $，你需要支持区间升序排序、区间降序排序两种操作，最后输出被跟踪值的位置。

排列长度与操作数均不超过 $ 2 \times 10^5 $。

## 分析

维护整个排列的变化不太好做，我们考虑从题目特殊性质入手。

我们发现要求的不是整个排列的变化情况，只是待跟踪值的位置而已，所以我们只需要跟踪好 $ x $ 的变化就行。

对于排序操作，$ x $ 的位置只取决于区间内大于 $ x $ 的数的个数，小于 $ x $ 的数的个数，所以我们只需要把数分为大于 $ x $、等于 $ x $、小于 $ x $ 三类即可。

排序时，我们找到区间内三类数的总数，再按照类别顺序放回就行。

需要三棵支持区间求和、区间覆盖的线段树，这里为了代码更优雅美观使用结构体将三棵合并为一棵来写。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int n, q, x;
int a[N];
struct node {
	int c1;
	int c2;
	int c3;
} d[N * 4], zero;
int c[N * 4];
node operator+(node p1, node p2) {
	node res;
	res.c1 = p1.c1 + p2.c1;
	res.c2 = p1.c2 + p2.c2;
	res.c3 = p1.c3 + p2.c3;
	return res;
}
void build(int s, int t, int p) {
	if(s == t) {
		if(a[s] < x) {
			d[p].c1 = 1;
		} else if(a[s] == x) {
			d[p].c2 = 1;
		} else {
			d[p].c3 = 1;
		}
		return;
	}
	int mid = (s + t) >> 1;
	build(s, mid, p * 2);
	build(mid + 1, t, p * 2 + 1);
	d[p] = d[p * 2] + d[p * 2 + 1];
}
void pushdown(int s, int t, int p) {
	if(c[p] != 0) {
		int mid = (s + t) >> 1;
		d[p * 2].c1 = d[p * 2].c2 = d[p * 2].c3 = 0;
		d[p * 2 + 1].c1 = d[p * 2 + 1].c2 = d[p * 2 + 1].c3 = 0;
		if(c[p] == 1) {
			d[p * 2].c1 = mid - s + 1;d[p * 2 + 1].c1 = t - mid;
		} else if(c[p] == 2) {
			d[p * 2].c2 = mid - s + 1;d[p * 2 + 1].c2 = t - mid;
		} else {
			d[p * 2].c3 = mid - s + 1;d[p * 2 + 1].c3 = t - mid;
		}
		c[p * 2] = c[p * 2 + 1] = c[p];
	}
	c[p] = 0;
}
node query(int l, int r, int s, int t, int p) {
	if(l > r) return zero;
	if(l <= s && t <= r) {
		return d[p];
	}
	pushdown(s, t, p);
	int mid = (s + t) >> 1;
	node sum = zero;
	if(l <= mid) sum = sum + query(l, r, s, mid, p * 2);
	if(mid < r) sum = sum + query(l, r, mid + 1, t, p * 2 + 1);
	return sum;
}
void update(int l, int r, int v, int s, int t, int p) {
	if(l > r) return;
	if(l <= s && t <= r) {
		c[p] = v;
		d[p].c1 = d[p].c2 = d[p].c3 = 0;
		if(v == 1) {
			d[p].c1 = t - s + 1;
		} else if(v == 2) {
			d[p].c2 = t - s + 1;
		} else {
			d[p].c3 = t - s + 1;
		}
		return;
	}
	pushdown(s, t, p);
	int mid = (s + t) >> 1;
	if(l <= mid) update(l, r, v, s, mid, p * 2);
	if(mid < r) update(l, r, v, mid + 1, t, p * 2 + 1);
	d[p] = d[p * 2] + d[p * 2 + 1];
}
int main() {
	cin >> n >> q >> x;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	build(1, n, 1);
	int c, l, r;
	for(int i = 1; i <= q; i++) {
		cin >> c >> l >> r;
		node qwq = query(l, r, 1, n, 1);
		int c1, c2, c3;
		c1 = qwq.c1, c2 = qwq.c2, c3 = qwq.c3;
		if(c == 1) {
			update(l, l + c1 - 1, 1, 1, n, 1);
			update(l + c1, l + c1 + c2 - 1, 2, 1, n, 1);
			update(l + c1 + c2, r, 3, 1, n, 1);
		} else if(c == 2) {
			update(l, l + c3 - 1, 3, 1, n, 1);
			update(l + c3, l + c3 + c2 - 1, 2, 1, n, 1);
			update(l + c3 + c2, r, 1, 1, n, 1);
		} else {
			printf("dthkxy AK IOI\n");
		}
	}
	for(int i = 1; i <= n; i++) {
		if((query(1, i, 1, n, 1)).c2 == 1) {
			cout << i << endl;
			break;
		}
	}
	return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

从 P2824 过来，两道题其实很像，参考一下 P2824 的 trick：把大于等于 $x$ 的数看成 $1$，把小于 $x$ 的数看成 $0$，然后二分求 $x$。那么这道题是给定了 $x$，求位置，不妨把小于 $x$ 的数看成 $0$，把 $x$ 看成 $1$，最后把大于 $x$ 的数看成 $2$，因为大于或小于 $x$ 的数的内部位置对 $x$ 的位置没有影响，所以我们将区间排序变成区间赋值：升序排序时，$[l,l+w_0-1]$ 这段区间变为 $0$，$[l+w_0,l+w_0+w_1-1]$ 变为 $1$，$[l+w_0+w_1,r]$ 变为 $2$，降序同理，最后 $O(n)$ 看 $1$ 的位置即可。时间复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h> 
#define ll long long
#define x first 
#define y second 
#define debug() puts("-------") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=2e5+10; 
int x; 
int n,m;  
int a[N]; 
struct Node{ 
	int l,r; 
	int w[3],add; 
}tr[N<<2]; 
void pushup(int u){ 
	for(int i=0;i<=2;i++) tr[u].w[i]=tr[u<<1].w[i]+tr[u<<1|1].w[i]; 
} 
void pushdown(int u){ 
	if(tr[u].add==-1) return ; 
	for(int i=0;i<=2;i++){
		if(i!=tr[u].add) tr[u<<1].w[i]=tr[u<<1|1].w[i]=0; 
		else tr[u<<1].w[i]=tr[u<<1].r-tr[u<<1].l+1,tr[u<<1|1].w[i]=tr[u<<1|1].r-tr[u<<1|1].l+1; 
	} tr[u<<1].add=tr[u<<1|1].add=tr[u].add,tr[u].add=-1; 
} 
void build(int u,int l,int r){ 
	tr[u]={l,r}; tr[u].add=-1; 
	if(l==r){ 
		if(a[l]<x) tr[u].w[0]=1; 
		if(a[l]==x) tr[u].w[1]=1; 
		if(a[l]>x) tr[u].w[2]=1; return ; 
	} int mid=l+r>>1; 
	build(u<<1,l,mid),build(u<<1|1,mid+1,r); 
	pushup(u); 
} 
void modify(int u,int l,int r,int w){ 
	if(l>r) return ; 
	if(l<=tr[u].l&&tr[u].r<=r){ 
		for(int i=0;i<=2;i++){
			if(i!=w) tr[u].w[i]=0; 
			else tr[u].w[i]=tr[u].r-tr[u].l+1;  
		} tr[u].add=w; return ; 
	} pushdown(u); int mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) modify(u<<1,l,r,w); if(r>mid) modify(u<<1|1,l,r,w); 
	pushup(u); 
} 
int query(int u,int l,int r,int k){ 
	if(l>r) return 0; 
	if(l<=tr[u].l&&tr[u].r<=r) return tr[u].w[k]; 
	pushdown(u); int w=0,mid=tr[u].l+tr[u].r>>1; 
	if(l<=mid) w=query(u<<1,l,r,k); if(r>mid) w+=query(u<<1|1,l,r,k); 
	return w; 
} 
signed main(){ 
	scanf("%d%d%d",&n,&m,&x); 
	for(int i=1;i<=n;i++) scanf("%d",&a[i]); 
	build(1,1,n); while(m--){ 
		int opt,l,r,w[3]; 
		scanf("%d%d%d",&opt,&l,&r); 
		for(int i=0;i<=2;i++) w[i]=query(1,l,r,i);  
		if(opt==1){ 
			modify(1,l,l+w[0]-1,0); 
			modify(1,l+w[0],l+w[0]+w[1]-1,1); 
			modify(1,l+w[0]+w[1],r,2); 
		} else{ 
			modify(1,l,l+w[2]-1,2); 
			modify(1,l+w[2],l+w[1]+w[2]-1,1); 
			modify(1,l+w[2]+w[1],r,0);  
		} 
	} for(int i=1;i<=n;i++) if(query(1,i,i,1)==1){ printf("%d\n",i); return 0; }
	return 0; 
} /*
5 2 1
1 4 5 2 3
1 3 5
2 1 3

1 2 2 2 2 
*/
```

---

## 作者：DengDuck (赞：0)

这道题有一个经典的优化。

首先就是我们发现直接排序非常愚蠢，因为会时间爆炸。

但是呢，仔细观察，我们发现我们只关注一个数字的相对位置。

我们可以转换，将小于它的数字记作 $0$，它本身记作 $1$，大于它的数字记作 $2$。

维护三个数字的排序就很简单了，用一个线段树维护这一过程即可。
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e6+5;
struct node
{
	LL l,r,lz=-1,a[3]; 
}t[N];
LL n,q,x,a[N],op,l,r;
void tobe(LL pos,LL k)
{
	t[pos].lz=k;
	t[pos].a[0]=t[pos].a[1]=t[pos].a[2]=0;
	t[pos].a[k]=t[pos].r-t[pos].l+1;
}
void pushup(LL pos)
{
	LL lc=pos*2,rc=pos*2+1;
	if(t[lc].l==0)return; 
	t[pos].a[0]=t[lc].a[0]+t[rc].a[0];
	t[pos].a[1]=t[lc].a[1]+t[rc].a[1];
	t[pos].a[2]=t[lc].a[2]+t[rc].a[2];
} 
void down(LL pos)
{
	if(t[pos].lz==-1)return;
	LL lc=pos*2,rc=pos*2+1,k=t[pos].lz;
	tobe(lc,k),tobe(rc,k);
	t[pos].lz=-1;
}
void build(LL pos,LL l,LL r)
{
	t[pos].l=l;
	t[pos].r=r;
	if(l==r)
	{
		t[pos].a[a[l]]++;
		return;
	}
	LL mid=(l+r)/2;
	build(pos*2,l,mid);
	build(pos*2+1,mid+1,r);
	pushup(pos);
}
void change(LL pos,LL l,LL r,LL k)
{
	if(t[pos].r<l||r<t[pos].l)return;
	if(l<=t[pos].l&&t[pos].r<=r)
	{
		tobe(pos,k);
		return;
	}
	down(pos);
	change(pos*2,l,r,k);
	change(pos*2+1,l,r,k);
	pushup(pos);
}
LL query(LL pos,LL l,LL r,LL k)
{
	if(t[pos].r<l||r<t[pos].l)return 0;
	if(l<=t[pos].l&&t[pos].r<=r)return t[pos].a[k];
	down(pos);
	return query(pos*2,l,r,k)+query(pos*2+1,l,r,k);
}
int main()
{
	cin>>n>>q>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]>x)a[i]=2;
		else if(a[i]==x)a[i]=1;
		else a[i]=0;
	}
	build(1,1,n);
	while(q--)
	{
		cin>>op>>l>>r;
		LL cnt0=query(1,l,r,0),cnt1=query(1,l,r,1),cnt2=query(1,l,r,2); 
		if(op==1)
		{
			change(1,l,l+cnt0-1,0);
			change(1,l+cnt0,l+cnt0+cnt1-1,1);
			change(1,l+cnt0+cnt1,r,2);
		}
		else
		{
			change(1,l,l+cnt2-1,2);
			change(1,l+cnt2,l+cnt2+cnt1-1,1);
			change(1,l+cnt2+cnt1,r,0);		
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(query(1,i,i,1))
		{
			cout<<i<<endl;
			return 0; 
		}
	}
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc237_g)

# 前置知识

[珂朵莉树/颜色段均摊](https://oi-wiki.org//misc/odt/)

# 解法

观察到只有 $=x$ 的位置才是重要的，而其他位置上的数具体是什么并不重要，我们只需要关注其大小关系。

第一遍将 $\ge x$ 的数看做 $1$，将 $<x$ 的数看做 $0$。第二遍将 $>x$ 的数看做 $1$，将 $\le x$ 的数看做 $1$。

此时排序操作就容易通过查询 $1$ 的个数后进行推平来维护了，可以使用珂朵莉树/线段树实现。

查询时只需要找到一个位置使得第一遍中是 $1$ 而第二遍中是 $0$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
int a[200010],b[200010],c[200010];
struct ODT
{
	struct node
	{
		int l,r;
		mutable int col;
		bool operator < (const node &another) const
		{
			return l<another.l;
		}
	};
	set<node>s;
	void init(int n,int a[])
	{
		for(int i=1;i<=n;i++)
		{
			s.insert((node){i,i,a[i]});
		}
	}
	set<node>::iterator split(int pos)
	{
		set<node>::iterator it=s.lower_bound((node){pos,0,0});
		if(it!=s.end()&&it->l==pos)
		{
			return it;
		}
		it--;
		if(it->r<pos)
		{
			return s.end();
		}
		int l=it->l,r=it->r,col=it->col;
		s.erase(it);
		s.insert((node){l,pos-1,col});
		return s.insert((node){pos,r,col}).first;
	}
	void assign(int l,int r,int col)
	{
		set<node>::iterator itr=split(r+1),itl=split(l);
		s.erase(itl,itr);
		s.insert((node){l,r,col});
	}
	int query(int l,int r)
	{
		set<node>::iterator itr=split(r+1),itl=split(l);
		int ans=0;
		for(set<node>::iterator it=itl;it!=itr;it++)
		{
			ans+=it->col*(it->r-it->l+1);
		}
		return ans;
	}
	int ask(int pos)
	{
		set<node>::iterator it=s.lower_bound((node){pos,0,0});
		if(it!=s.end()&&it->l==pos)
		{
			return it->col;
		}
		it--;
		return it->col;
	}
}O[2];
int main()
{
// #define Isaac
#ifdef Isaac
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	int n,m,x,pd,l,r,i,j;
	cin>>n>>m>>x;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=(a[i]>=x);
		c[i]=(a[i]>x);
	}
	O[0].init(n,b);
	O[1].init(n,c);
	for(i=1;i<=m;i++)
	{
		cin>>pd>>l>>r;
		if(pd==1)
		{
			for(j=0;j<=1;j++)
			{
				pd=O[j].query(l,r);
				O[j].assign(l,r-pd,0);
				O[j].assign(r-pd+1,r,1);
			}
		}
		else
		{
			for(j=0;j<=1;j++)
			{
				pd=O[j].query(l,r);
				O[j].assign(l,l+pd-1,1);
				O[j].assign(l+pd,r,0);
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		if(O[0].ask(i)==1&&O[1].ask(i)==0)
		{
			cout<<i<<endl;
		}
	}
	return 0;
}
```

---

