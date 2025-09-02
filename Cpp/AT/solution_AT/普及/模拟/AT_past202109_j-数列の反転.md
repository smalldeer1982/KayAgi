# 数列の反転

## 题目描述

维护一个长度为 $2n$ 的序列 $a$。开始时，对于每个满足 $1 \le a \le 2n$ 的整数 $i$，都有 $a_i=i$。

给出 $q$ 次操作，每次操作都为以下两种形式中的一种：

- `1 k`：输出 $a_k$ 的值并换行。保证 $1 \le k \le 2n$。
- `2 k`：反转 $[n-k+1,n+k]$ 这个区间。反转后，原来的第 $p$ 个元素被换到了第 $2n-p+1$ 个元素的位置。保证 $1 \le k \le n$。

请按顺序执行操作。

## 说明/提示

#### 数据规模与约定

$1 \le n,q \le 2 \times10^5$，$1 \le t_i \le 2$。

## 样例 #1

### 输入

```
3 2
2 2
1 4```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
2 3
1 3
1 1```

### 输出

```
4
6```

## 样例 #3

### 输入

```
5 6
2 2
2 1
2 1
2 3
1 2
2 3```

### 输出

```
2```

# 题解

## 作者：tjtdrxxz (赞：7)

一眼丁真 fhq treap。

好，相信大家都会 split 和 merge 操作。那就直接看题，题目要求我们反转区间，以及输出第 $ k $ 个数。

输出第 $ k $ 个数是很轻松的，只用判断左子树大小 $ +1 $ 是不是等于 $ k $，等于的话就直接返回当前结点的值，因为此时当前节点就是第 $ k $ 大，如果左子树大小 $ \ge k $ 说明第 $ k $ 大在左子树，不然 $ k $ 就减去左子树大小和此节点大小的和，然后在右子树中找。

区间反转其实很简单，先把下标 $ l \to r $ 的子树分裂出来（$ 1 \to l - 1 $，$ l \to r $，$ r + 1 \to n $），然后把分裂出的子树的根节点打上懒标记（直接异或 $ 1 $，因为如果一个区间反转过两次，那就没有反转的必要，最快的判断方法就是异或捏），然后重新把三个子树合并。

注意下传懒标记！！！

code:
```cpp
# include "bits/stdc++.h"
# define int long long 
using namespace std;
namespace chtholly
{
	template <typename T>
	class tree
	{
		public :
			int boot;
			struct node
			{
				int left, right, size;
				int val, tag, weight;
			}s[400012];
			inline void push (int x)//更新 
			{
				s[x].size = s[s[x].left].size + s[s[x].right].size + 1;
			}
			void add (int x)//加入新节点 
			{
				s[x].val = x;
				s[x].tag = false;
				s[x].left = 0;
				s[x].right = 0;
				s[x].weight = rand () % 998244353;
				s[x].size = 1;
			}
			void check (int x)
			{
				if (s[x].tag)
				{
					s[x].tag = 0;
					swap (s[x].left, s[x].right);
					s[s[x].right].tag ^= 1;
					s[s[x].left].tag ^= 1;
				}
			}
			void split (int now, int k, int& x, int& y)//当前节点，按k划分(这里是按下标划分)
			{
				if (!now)
				{
					x = 0;
					y = 0;
					return;
				}
				check (now);
				if (s[s[now].left].size < k)
				{
					x = now;
					split (s[now].right, k - s[s[now].left].size - 1, s[now].right, y);//类比树上二分 
				}
				else
				{
					y = now;
					split (s[now].left, k, x, s[now].left);
				}
				push (now);
			}
			int merge (int x, int y)
			{
				if (!x or !y) return x + y;
				if (s[x].weight < s[y].weight)
				{
					check (x);
					s[x].right = merge (s[x].right, y);
					push (x);
					return x;
				}
				else
				{
					check (y);
					s[y].left = merge (x, s[y].left);
					push (y);
					return y;
				}
			}
			void reverse (int x, int y)
			{
				int l = 0, r = 0, p = 0;
				split (boot, y, l, r);
				split (l, x - 1, l, p);
				s[p].tag ^= 1;
				boot = merge (merge (l, p), r);
			}
			void print (int now)
			{
				check (now);
				if (s[now].left) print (s[now].left);
				printf ("%lld ", s[now].val);
				if (s[now].right) print (s[now].right);
			}
			void insert (int i)
			{
				add (i);
				boot = merge (boot, i);
			}
			int find (int x, int k)
			{
				if (!s[x].left and !s[x].right) return s[x].val;
				check (x);
				if (k == s[s[x].left].size + 1) return s[x].val;
				else if (k < s[s[x].left].size + 1) return find (s[x].left, k);
				return find (s[x].right, k - s[s[x].left].size - 1);
			}
			int find_val (int k)
			{
				return find (boot, k);
			}
	};
};
using namespace chtholly;
tree <int> s;
int n, m, l, r, p, x, y;
signed main ()
{
	scanf ("%lld %lld", &n, &m);
	for (int i = 1; i <= n * 2; i ++) s.insert (i);
	for (int i = 1; i <= m; i ++)
	{
		int op, len;
		scanf ("%lld %lld", &op, &len);
		if (op == 1) printf ("%lld\n", s.find_val (len));
		if (op == 2) s.reverse (n - len + 1, n + len);
	}
}
```

---

## 作者：angiing1222 (赞：1)

来一个暴力做法。

首先，这道题要求我们翻转序列以及查询单点。很轻易地就能想到[P3391 文艺平衡树](/problem/P3391)一题。本人在此采用 FHQ-Treap 进行实现，在此不多赘述。关键在于如何进行单点查询的操作。~~实际上也不难。~~

在 P3391 中我们使用平衡树的中序遍历来维护原数列，且利用子树的大小维护平衡树的二叉搜索树性质，我们便可以利用以上特性在平衡树中进行搜索。

设当前搜索到的点为 $x$，要查找的点为当前子树中的第 $y$ 项。定义 $size_a$ 指平衡树上以 $a$ 为根的子树的大小，$b_l$ 指 $b$ 的左儿子，$b_r$ 指 $b$ 的右儿子。

- 若要查找的点就是 $x$，则返回 $x$ 所对应的值；

- 若要查找的点在 $x$ 的左子树上，即 $y<size_{x_l}+1$，则将 $x$ 改为 $x_l$，不改变 $y$，继续进行搜索；

- 若要查找的点在 $x$ 的右子树上，即 $y>size_{x_l}+1$，则将 $x$ 改为 $x_r$，将 $y$ 减去 $size_{x_l}+1$，继续进行搜索。

思路基本上和 fhq 的 split 函数一样。

另外：**别忘了加懒标记下传！**

单点查询的部分就完成了，相信各位神犇对于剩下的部分已经十分熟练了吧，那就直接上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
mt19937 rnd(time(0));
struct hyfakioi{
	int l,r,key,value,size;
	bool t;
}tree[N];
int cnt=0,root,dl,dr;
int add(int x){
	tree[++cnt].key=x;
	tree[cnt].value=rnd();
	tree[cnt].size=1;
	tree[cnt].t=0;
	return cnt;
}
void pushup(int x){
	tree[x].t=0;
	swap(tree[x].l,tree[x].r);
	tree[tree[x].l].t=!tree[tree[x].l].t;
	tree[tree[x].r].t=!tree[tree[x].r].t;
} 
void split(int x,int pos,int& l,int& r){
	if(!pos){
		l=r=0;
		return;
	}
	if(tree[pos].t)pushup(pos);
	if(tree[tree[pos].l].size<x){
		l=pos;
		split(x-tree[tree[pos].l].size-1,tree[pos].r,tree[pos].r,r);
	}
	else{
		r=pos;
		split(x,tree[pos].l,l,tree[pos].l);
	}
	tree[pos].size=tree[tree[pos].l].size+tree[tree[pos].r].size+1;
}
int merge(int l,int r){
	if(!l||!r)return l|r;
	if(tree[l].value<=tree[r].value){
		if(tree[l].t)pushup(l);
		tree[l].r=merge(tree[l].r,r);
		tree[l].size=tree[tree[l].l].size+tree[tree[l].r].size+1;
		return l;
	}
	else{
		if(tree[r].t)pushup(r);
		tree[r].l=merge(l,tree[r].l);
		tree[r].size=tree[tree[r].l].size+tree[tree[r].r].size+1;
		return r;
	}
}
void insert(int x){
	split(x-1,root,dl,dr);
	root=merge(merge(dl,add(x)),dr);
}
void reverse(int l,int r){
	int sbno;
	split(l-1,root,dl,dr);
	split(r-l+1,dr,dr,sbno);
	tree[dr].t=!tree[dr].t;
	root=merge(dl,merge(dr,sbno));
}//以上代码为 P3391 模板
int getfa(int pos,int x){
	if(tree[pos].l==0&&tree[pos].r==0)return tree[pos].key;
	if(tree[pos].t)pushup(pos);
	if(x==tree[tree[pos].l].size+1)return tree[pos].key;
	else if(x<tree[tree[pos].l].size+1)return getfa(tree[pos].l,x);
	else return getfa(tree[pos].r,x-tree[tree[pos].l].size-1);
}//查询位置
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=2*n;++i)insert(i);
	while(m--){
		int op,k;
		cin>>op>>k;
		if(op==1)cout<<getfa(root,k)<<"\n";
		else reverse(n-k+1,n+k);
	}
	return 0;
}
```

---

## 作者：SamHH0912 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202109_j)

### 分析

考虑使用一种数据结构维护题目中各区间的反转次数。用 $c_p$ 表示原数列下标为 $n-p+1$ 和 $n+p$ 的数的反转次数。

由于 $2$ 操作是反转了原数列最中间的长为 $2k$ 的子数列，所以 $c$ 中区间 $[1,k]$ 的值要 $+1$。

再来看 $1$ 操作。定义 $p$ 在 $k\gt n$ 时为 $k-n$，$k\le n$ 时为 $n-k+1$。计算 $c_p$ 是否为偶数。如果是，输出 $k$（原位）；否则，输出 $2n-k+1$（反转后）。

观察过程，发现 $1$ 操作本质上是单点查询，$2$ 操作本质上是区间加，所以我们果断选用差分树状数组来解决本题（差分树状数组模板：[P3368](https://www.luogu.com.cn/problem/P3368)）。

最后再提一小句，因为一开始没有区间被反转，所以差分树状数组就不用初始化了！

### 参考代码

#### 操作 1

单点查询函数：（返回 $1$ 表示反转了，$0$ 表示归位了）

```cpp
inline bool flip(int x){
	bool res=0;
	for(;x;x-=lowbit(x)) res^=c[x]&1;//只需计算所有要加的 c[x] 共有多少个是奇数即可
	return res;
}
```

主函数内：

```cpp
		if(t==1){
			int p=k>n?k-n:n-k+1;
			if(flip(p)) printf("%d\n",2*n+1-k);
			else printf("%d\n",k);
		}
```

#### 操作 2

区间加函数：

```cpp
inline void add(int x,int d){
	for(;x<=n;x+=lowbit(x)) c[x]+=d;
}
```

主函数内：

```cpp
		if(t==2){
			add(1,1);
			if(k<n) add(k+1,-1);//这个 if 可以去掉
		}
```

**感谢您的阅读！**

---

## 作者：zhuohongyuan (赞：0)

### 题意简述
给定一个数列要求对他进行一些操作。

- `1 k`：输出 $a_k$ 的值并换行。
- `2 k`：反转 $[n-k+1,n+k]$ 这个区间。反转后，原来的第 $p$ 个元素被换到了第 $2n-p+1$ 个元素的位置。

$1 \le n,q \le 2 \times10^5$，$1 \le t_i \le 2$。

### 思路

看完题目后我们可以很容易的发现操作一是单点查询，操作二区间修改。

可以想到线段树，但是操作二不好处理。

于是我们可以用一个线段树维护每个数反转的次数，每次将 $[n-k+1,n+k]$ 这一段区间的反转次数 +1。

查询的时候查询反转次数即可，如果是偶数，就直接输出，奇数就输出反转后的值。

---

## 作者：lzh_juruo (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_past202109_j)


---

观察操作 2 可知，由于被反转区间的中点始终不变，所以，当一个数 $i$ 被反转了偶数次后，它总是会反转会来，下标依旧是 $i$ ，反之等同于反转了一次。

我们可以用线段树维护序列中每一个数反转的次数，每一次将 $[n-k+1,n+k]$ 这一段序列的反转次数 $+1$ ,查询时只需查询反转次数，若是偶数则不变，奇数则输出反转后的值。

 AC 代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,op,x,tr[1600003],tg[1600003];
void tadd(int o,int l,int r,int d){
	tg[o]+=d;
	tr[o]+=d*(r-l+1);
}
void pd(int o,int l,int r,int m){
	if(tg[o]==0) return;
	tadd(o*2,l,m,tg[o]);
	tadd(o*2+1,m+1,r,tg[o]);
	tg[o]=0;
}
void upd(int o,int l,int r,int x,int y,int d){
	if(l>y||r<x) return;
	if(x<=l&&r<=y){
		tadd(o,l,r,d);
		return;
	}
	int mid=l+r>>1;
	pd(o,l,r,mid);
	upd(o*2,l,mid,x,y,d);
	upd(o*2+1,mid+1,r,x,y,d);
	tr[o]=tr[o*2]+tr[o*2+1];
}
int ch(int o,int l,int r,int x){
	if(x>r||x<l) return 0;
	if(l==x&&r==x) return tr[o];
	int mid=l+r>>1;
	pd(o,l,r,mid);
	return ch(o*2,l,mid,x)+ch(o*2+1,mid+1,r,x);
}
signed main(){
	cin>>n>>q;
	while(q--){
		cin>>op>>x;
		if(op==1){
			if(ch(1,1,n*2,x)%2==1){
				if(x<=n) cout<<n+(n-x)+1<<"\n";
				else cout<<n-(x-n)+1<<"\n";
			}else cout<<x<<"\n";
		}else upd(1,1,n*2,n-x+1,n+x,1);
	}
	return 0;
}
```

---

## 作者：HUANGRUI11 (赞：0)

建议升绿。

 读完题后看到 $n$ 的范围最大为 $2e5$ 后就想到了用树状数组解题。

定义一个 $a$ 数组为每个数的交换次数。

 因为 $a_i=i$，所以操作 $2$ 中翻转了序列最中间长度为 $2k$ 的子序列，其实就是相当于在 $a$数组的 区间 $\begin{bmatrix}1 , k \end{bmatrix}$ 中的值每个加 $1$。

操作 $2$ 时，先计算出要输出数的位置 $p$，即在 $k$ 大于 $n$ 时，$p$ 为 $n-k$，否则则为 $n-k+1$。然后判断第 $k$个数的 $a_p$ 值是否是偶数，如果是说明数位置仍为 $k$，否则是 $2n-k+1$。

操作 $1$ 和 $2$ 均符合树状数组的单点查询和区间求和。

代码如下。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,x,y,a[1000001];
int lowbit(int x)
{
	return x & (-x);
}
inline bool dfs(int x)
{
	bool res=0;
	while(x>0)
	{
		res^=a[x]&1;
		x-=lowbit(x);
	}
	return res;
}
void add(int x,int k)
{
	while(x<=n)
	{
		a[x]+=k;
        x+=lowbit(x);
	}
}
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>x>>y;
		if(x==1) 
		{
			int p=y>n?y-n:n-y+1;
			if(dfs(p)) cout<<2*n+1-y<<"\n";
			else cout<<y<<"\n";
		}
		else 
		{
			add(1,1);
			add(y+1,-1);
		}
	}
	return 0;
} 
```

完结散花。

---

