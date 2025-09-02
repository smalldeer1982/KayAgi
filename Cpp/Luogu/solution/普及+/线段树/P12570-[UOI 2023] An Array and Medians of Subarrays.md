# [UOI 2023] An Array and Medians of Subarrays

## 题目描述

对于一个长度为 $(2 \cdot k + 1)$ 的数组，我们将其元素按非递减顺序排序后，第 $(k + 1)$ 位的数字称为该数组的**中位数**。例如，数组 $[1]$、$[4,2,5]$ 和 $[6,5,1,2,3]$ 的中位数分别是 $1$、$4$ 和 $3$。

给定一个长度为**偶数** $n$ 的整数数组 $a$。

判断是否可以将 $a$ 分割成若干个长度为**奇数**的子数组，使得所有这些子数组的中位数都相等。

形式化地说，你需要判断是否存在一个整数序列 $i_1, i_2, \ldots, i_k$，满足以下条件：

- $1 = i_1 < i_2 < \ldots < i_k = (n + 1)$；
- $(i_2 - i_1) \bmod 2 = (i_3 - i_2) \bmod 2 = \ldots = (i_k - i_{k - 1}) \bmod 2 = 1$；
- $f(a[i_1..(i_2-1)]) = f(a[i_2..(i_3-1)]) = \ldots = f(a[i_{k - 1}..(i_k - 1)])$，其中 $a[l..r]$ 表示由元素 $a_l, a_{l + 1}, \ldots, a_r$ 组成的子数组，$f(a)$ 表示数组 $a$ 的中位数。

## 说明/提示

在第一个样例中，数组 $[1,1,1,1]$ 可以分割为 $[1]$ 和 $[1,1,1]$，它们的中位数均为 $1$。

在第二个样例中，数组 $[1,2,3,3,2,1]$ 可以分割为 $[1,2,3]$ 和 $[3,2,1]$，它们的中位数均为 $2$。

在第三个样例中，数组 $[1,2,1,3,2,3]$ 无法被分割为若干个长度为奇数的子数组，且这些子数组的中位数相等。

### 评分标准

- （$3$ 分）：$n=2$；
- （$14$ 分）：对于 $1 \le i \le n$，$1 \le a_i \le 2$；
- （$12$ 分）：对于 $1 \le i < n$，$a_i \le a_{i+1}$；
- （$16$ 分）：对于 $1 \le i \le n$，$1 \le a_i \le 3$，且每个值在 $a$ 中出现的次数不超过 $\frac{n}{2}$；
- （$17$ 分）：$n \le 100$；
- （$18$ 分）：$n \le 2000$；
- （$20$ 分）：无额外限制。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
1 1 1 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
6
1 2 3 3 2 1```

### 输出

```
Yes```

## 样例 #3

### 输入

```
6
1 2 1 3 2 3```

### 输出

```
No```

# 题解

## 作者：WanderFreeFish (赞：2)

## Solution

这题有一个很重要的一点，就是最多分成两个序列。如果存在分成多个序列的解，那么一定可以合并变成两个。

对于多个中位数相同的序列 $a$，令这个中位数位置为 $pos$，每个序列排序之后，$pos$ 右边的数都大于等于 $a_{pos}$，左边的数都小于等于 $a_{pos}$，且这两个值一定相等。序列合并排序后这两个值分别求和，两边仍然相等，故中位数相等（拙劣的证明）。

于是题目变成了，把一个序列分成两个，使其中位数相等。考虑枚举分割线，判断左右两边的中位数是否相等。

## Specifically

中位数可以预处理，因为我们只需要前缀与后缀数组的中位数。从前往后遍历，先把当前位置的数加进去，然后求第 $k$ 小。那做法可太多了。由于我太菜了不会可持久化线段树，还是用平衡树吧。后缀的预处理同理。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#define lson tr[root].ls
#define rson tr[root].rs

const int MAXN = 2e5 + 10;

struct node {
	int ls, rs, sz, val, key;
	node () {
		ls = rs = sz = val = key = 0;
	}
};

struct fanhaoqiang {
public:
	std::vector <node> tr; int allroot, tot;
	
	fanhaoqiang () {
		allroot = tot = 0;
		tr.resize(1);
	}
	
private:
	int newnode (int val) {
		tr.push_back(node());
		tr[++tot].val = val;
		tr[tot].sz = 1;
		tr[tot].key = rand();
		return tot;
	}
	
	void split (int root, int &l, int &r, int val) {
		if (root == 0) {
			l = r = 0;
			return;
		}
		else if (tr[root].val <= val) {
			l = root;
			split(rson, rson, r, val);
		}
		else {
			r = root;
			split(lson, l, lson, val);
		}
		push_up(root);
	}
	
	void push_up (int root) {
		tr[root].sz = tr[lson].sz + tr[rson].sz + 1;
	}
	
	int merge (int l, int r) {
		if (!l || !r)
			return (l | r);
		else if (tr[l].key <= tr[r].key) {
			tr[l].rs = merge(tr[l].rs, r);
			push_up(l);
			return l;
		}
		else {
			tr[r].ls = merge(l, tr[r].ls);
			push_up(r);
			return r;
		}
	}
	
public:
	int rank_kth (int root, int k) {
		if (tr[root].sz < k) return -1;
		else if (tr[lson].sz + 1 == k) return tr[root].val;
		else if (tr[lson].sz >= k) return rank_kth(lson, k);
		else return rank_kth(rson, k - tr[lson].sz - 1);
	}
	
	void insert (int val) {
		int x, y;
		split(allroot, x, y, val - 1);
		allroot = merge(merge(x, newnode(val)), y);
	}
}twd, bwd; // toward,backward

int n, a[MAXN], pre[MAXN], suf[MAXN], flag;

int main () {
	std::cin >> n;
	
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	
	pre[1] = a[1];
	twd.insert(a[1]);
	for (int i = 3; i <= n; i += 2) { //因为只能分成奇数长度，所以每次加 2
		twd.insert(a[i - 1]);
		twd.insert(a[i]);
		pre[i] = twd.rank_kth(twd.allroot, i / 2 + 1);
	}
	
	suf[n] = a[n];
	bwd.insert(a[n]);
	for (int i = n - 2; i >= 1; i -= 2) {
		bwd.insert(a[i]);
		bwd.insert(a[i + 1]);
		suf[i] = bwd.rank_kth(bwd.allroot, (n - i + 1) / 2 + 1);
	}
	
	
	for (int i = 1; i <= n; i += 2)
		if (pre[i] == suf[i + 1])
			flag = 1;
	
	if (flag) std::cout << "Yes";
	else std::cout << "No";
	
	return 0;
}
```

## Other

但是这道题不管是主席树还是平衡树，都是蓝题，为什么这是一道绿题？

还有，这道题还可以跑得更快些。把范浩强换成红黑树就行。

由于篇幅以及洛谷剪贴板炸了，[暂且放在这里](https://netcut.cn/p/634d0f80b5234545)。

---

## 作者：wangyanjing (赞：1)

PS：记录一下自己的做法。   
# Think 
区间具有可合并性。
-
具体地：奇数个连续的区间可以合并为一个大区间。

证明：

记：共有 $m$ 个连续的合法区间，第 $i$ 个区间长度为 $len_i$，所有的区间的中位数均为 $X$。

对于第 $i$ 个区间：对大区间贡献至少 $\lfloor \frac{len_i}{2} \rfloor + 1$ 个 $\le X$ 的数。   
$X$ 在大区间的排名为：$\lfloor \frac{\sum_{i = 1}^m len_i}{2} \rfloor + 1$。  
所以我们发现存在以下不等式（~~人类智慧~~）：
$$\sum_{i = 1}^m (\lfloor \frac{len_i}{2} \rfloor + 1) \ge \lfloor \frac{\sum_{i = 1}^m len_i}{2} \rfloor + 1$$
即：

 $$2\sum_{i = 1}^m (\lfloor \frac{len_i}{2} \rfloor + 1) \ge 2(\lfloor \frac{\sum_{i = 1}^m len_i}{2} \rfloor + 1)$$
 
 证明为以下：
 $$\because \forall i,len_i \bmod 2 \equiv 1$$
 $$\therefore 2\sum_{i = 1}^m (\lfloor \frac{len_i}{2} \rfloor + 1) = 2\sum_{i = 1}^m \lfloor \frac{len_i}{2} \rfloor + 2m = \sum_{i = 1}^m (len_i-1) + 2m = m + \sum_{i = 1}^m len_i$$
 $$ 2(\lfloor \frac{\sum_{i = 1}^m len_i}{2} \rfloor + 1) = (-1+\sum_{i = 1}^m len_i) +2 = 1 +  \sum_{i = 1}^mlen_i$$

 $$\because m \ge 1$$
 $$\therefore m + \sum_{i = 1}^m len_i \ge 1+\sum_{i = 1}^mlen_i$$
 $$\therefore \sum_{i = 1}^m (\lfloor \frac{len_i}{2} \rfloor + 1) \ge \lfloor \frac{\sum_{i = 1}^m len_i}{2} \rfloor + 1$$
**证毕。**

由上述结论我们还可以推出：若每个区间的中位数相同，则这个数为原序列的中位数（将所有的区间合并为原序列，已证明）。

因为 $n$ 为偶数，所有的区间的长度为奇数，所以划分出的区间的个数也为偶数。

我们可把第一个区间看为 $[1,k]$，将剩下的区间合并为 $[k+1,n]$，看是否存在一个 $k$，使得 $[1,k]$ 和 $[k+1,n]$ 的中位数均为原序列的中位数 且 $k \bmod 2 \equiv 1$ 即可。

# Solution
先离散化，枚举两个区间的分割点，用可持久化线段树（主席树）维护区间第 $k$ 小即可。  
~~其实其他的数据结构也行。~~
# Code 

```cpp
#include<cstdio>
#include<algorithm>
const int N = 2e5+5,LogN = 20;
int a[N],tmp[N],len;
struct Segment_Tree{
	struct Tree{
		int lson,rson,siz;
	}tree[N*LogN];
	int root[N],total = 0;
	inline void push_up(int rt){
		tree[rt].siz = tree[tree[rt].lson].siz + tree[tree[rt].rson].siz;
	}
	inline void Update(int &rt,int last,int l,int r,int pos,int val){
		rt = ++total,tree[rt] = tree[last];
		if(l == r) return void(tree[rt].siz += val);
		int mid = l+r>>1;
		if(pos<=mid) Update(tree[rt].lson,tree[last].lson,l,mid,pos,val);
		else Update(tree[rt].rson,tree[last].rson,mid+1,r,pos,val);
		push_up(rt);
	}
	inline int Kth(int Lrt,int Rrt,int l,int r,int k){
		if(l == r) return l;
		int lsiz = tree[tree[Rrt].lson].siz - tree[tree[Lrt].lson].siz;
		int mid = l+r>>1; 
		if(lsiz>=k) return Kth(tree[Lrt].lson,tree[Rrt].lson,l,mid,k);
		else return Kth(tree[Lrt].rson,tree[Rrt].rson,mid+1,r,k-lsiz);
	}
	inline int Mid(int l,int r){
		int siz = r - l + 1;
		int k = siz + 1 >> 1;
		return Kth(root[l-1],root[r],1,len,k);
	}
}T;
int main(){
	int n;
	std::scanf("%d",&n);
	for(int i = 1;i<=n;++i){
		std::scanf("%d",a+i);
		tmp[i] = a[i];
	}
	std::sort(tmp+1,tmp+n+1);
	int X = tmp[n>>1]; 
	len = std::unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i = 1;i<=n;++i){
		a[i] = std::lower_bound(tmp+1,tmp+len+1,a[i])-tmp;
		T.Update(T.root[i],T.root[i-1],1,len,a[i],1);
	}
	for(int k = 1;k<n;k+=2)
		if(tmp[T.Mid(1,k)] == X && tmp[T.Mid(k+1,n)] == X){
			std::puts("Yes");
			return 0;
		}
	std::puts("No");
	return 0;
}

```
时空复杂度均为 $O(n \log n)$。

---

