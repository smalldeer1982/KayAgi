# [ABC407F] Sums of Sliding Window Maximum

## 题目描述

给你一个长度为 $N$ 的数列 $A=(A_1,\dots,A_N)$，请对于所有 $1\le k\le N$ 求解下面的问题：

- 求出 $A$ 长为 $k$ 的全部 $N-k+1$ 个连续子序列的最大值的和。

## 说明/提示

### 数据规模与约定

- $1 \le N \le 2 \times 10^{5}$
- $0 \le A_i \le 10^{7} (1 \le i \le N)$
- 输入的所有数字为整数。

## 样例 #1

### 输入

```
4
5 3 4 2```

### 输出

```
14
13
9
5```

## 样例 #2

### 输入

```
8
2 0 2 5 0 5 2 4```

### 输出

```
20
28
27
25
20
15
10
5```

## 样例 #3

### 输入

```
11
9203973 9141294 9444773 9292472 5507634 9599162 497764 430010 4152216 3574307 430010```

### 输出

```
61273615
68960818
69588453
65590626
61592799
57594972
47995810
38396648
28797486
19198324
9599162```

# 题解

## 作者：DengStar (赞：13)

这道题的套路非常典。（但我怎么不会？）

我们需要求出 $k = 1, 2, \cdots, n$ 的答案，考虑用某种方式同时更新整个答案序列。

用单调栈求出 $a_i$ 能作为最大值的极长区间 $[l_i, r_i]$（$l_i \le i \le r_i$）。由于可能有相同的元素，而我们希望每个区间只被统计一次，所以做如下规定：

- $[i, r_i]$ 中可以有和 $a_i$ 相同的元素。
- $[l_i, i]$ 中不可以有和 $a_i$ 相同的元素，即 $a_i$ 是此区间中的严格最大值。

可以发现这样规定确实不重不漏地统计了所有区间。

然后考虑每个 $a_i$ 对答案序列的贡献。对某个区间 $[x, y]$，如果 $l_i \le x \le i \le y \le r_i$，那么 $a_i$ 就是 $[x, y]$ 中的最大值。把这些区间分长度讨论，设区间长度为 $j$，统计有多少个长度为 $j$ 的区间的最大值为 $a_i$。具体地，设 $x_{\min}$ 和 $x_{\max}$ 分别为 $i - l_i + 1$ 和 $r_i - i + 1$ 中的较小值和较大值，$len = r_i - l_i + 1$，则

1. 若 $1 \le j < x_{\min}$，则 $ans_{j} \gets ans_{j} + j \cdot a_{i}$；
2. 若 $x_{\min} \le j < x_{\max}$，则 $ans_{j} \gets ans_{j} + x_{\min} \cdot a_{i}$；
3. 若 $x_{\max} \le j \le len + 1$，则 $ans_{j} \gets (len - j + 1) \cdot a_{i}$；
4. 其它情况对 $ans$ 无贡献。

以上几种情况画个图不难理解。

$a_{i}$ 对 $ans$ 的贡献可以写成如下序列（为了方便，忽略了所有的 $a_i$ 因子，只保留系数，同时 $ans$ 从 $0$ 开始标号）：
$$
0, {\color{red}{1, 2, \cdots, x_{\min} - 1,}} {\color{green}{x_{\min}, x_{\min}, \cdots, x_{\min},}} {\color{blue}{x_{\min} - 1, \cdots, 1, 0,}} 0
$$
这相当于把答案序列加上了三个等差数列（中间的序列公差为 $0$）。线段树可以维护等差数列，但我们不需要动态查询，因此有更简单的办法：把上面的序列差分一遍，得到
$$
0, {\color{red}{1, 1, \cdots, 1,}} {\color{green}{1, 0, \cdots, 0,}} {\color{blue}{-1, \cdots, -1, -1,}} 0
$$
再差分一遍：
$$
0, {\color{red}{1, 0, \cdots, 0,}} {\color{green}{0, -1, \cdots, 0,}} {\color{blue}{1, \cdots, 0, 0,}} -1
$$
于是在二阶差分序列上只用修改 $O(1)$ 个值。最后把二阶差分序列做两遍前缀和就得到了答案。时间复杂度 $O(n)$。

[代码](https://atcoder.jp/contests/abc407/submissions/66194192)

相似题目推荐：[P12498](https://www.luogu.com.cn/problem/P12498)

---

## 作者：xuanfeng101 (赞：10)

## 思路
首先题意要求**不同长度**的**每个子数组**的**最大值的和**，那么考虑最朴实的暴力想法，可以按照题意要求模拟，每次枚举一个长度求最大值，那么不就是题目标题的滑动窗口嘛，不过这样维护是 $O(n ^ 2)$ 的，显然不能过。

那么我们对于这个暴力的思路进行优化，其实这个思想就是枚举**每个长度中一个数**能在哪些区间有**贡献**，既然这样，我们就不考略枚举长度，而考虑其能产生的对于哪些区间的贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/a0kpesck.png)

如图，假设我们现在枚举到图中红色方块，我们记**其左边与它相邻比它大的元素坐标**（可以用单调栈找）为 $l[x]$， 同理右边为 $r[x]$（**此时如果遇到相同数也视为比其大**），那么我们可以找到这个元素对于答案的贡献。

![](https://cdn.luogu.com.cn/upload/image_hosting/4upwhhcs.png)

画图发现其对于区间的贡献是一个**先增再减的等差数列**，也就是说我们需要每次给答案区间加上这个**等腰梯形**，我们知道，直线型的这种区间加可以用差分，那么这种一次函数型的同理，我们只需要进行**二阶差分**，在答案数组里面求两次前缀和即可。

## 时间复杂度
$O(n)$

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, a[N];
int q[N], top;
int l[N], r[N];
int ans[N];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++ )
	{
		cin >> a[i];
		while (top && a[q[top]] <= a[i]) top -- ;
		l[i] = q[top];
		q[ ++ top] = i;
	}
	top = 0;
	for (int i = n; i >= 1; i -- )
	{
		while (top && a[q[top]] < a[i]) top -- ;
		r[i] = q[top] ? q[top] : n + 1;
		q[ ++ top] = i;
	}
	for (int i = 1; i <= n; i ++ )
	{
		ans[1] += a[i];
		ans[min(i - l[i], r[i] - i) + 1] -= a[i];
		ans[max(i - l[i], r[i] - i) + 1] -= a[i];
		ans[r[i] - i + i - l[i] + 1] += a[i]; 
	}
	for (int i = 1; i <= n; i ++ ) ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i ++ ) ans[i] += ans[i - 1];
	for (int i = 1; i <= n; i ++ ) cout << ans[i] << endl;
 	return 0;
}
```

---

## 作者：YBJ1006 (赞：7)

注意到分类讨论加二阶差分还是太吃操作了，这里给个无脑统计贡献的做法法。（最大点也是27ms，和线性一样？？）

先拆贡献，找一个极长的序列（左右不能再扩展）以 $a_i$ 为最大值，这一步可以用单调栈，RMQ加二分，等很多做法。那么 $a_i$ 贡献了哪些区间呢？

记这个极大区间为 $[l, r]$。可以考虑枚举这个区间的所有子区间，但是太慢了，所以我们考虑枚举子区间的左端点 $x$，那么右端点在 $[i, r]$ 中都合法。

所以长度为 $[i-x+1, r-x+1]$ 的区间都要加上贡献，这时候可以差分。

我们的瓶颈在于枚举左端点，但是枚举左还是右其实是一样的，所以每次枚举少的就好了，这个平均下来很好应该。

代码。
https://atcoder.jp/contests/abc407/submissions/66153501

---

## 作者：P2441M (赞：4)

## 题意
给定长度为 $n$ 的序列 $a$，对于每个 $1\leq k\leq n$，求

$$
\sum_{i=1}^{n-k+1}\max_{j=i}^{i+k-1}a_j
$$

$1\leq n\leq 2\times 10^5$，$0\leq a_i \leq 10^7$。

## 题解
简单题，赛时几乎秒出思路。

显然考虑拆贡献，对于每个 $a_i$，考察它对于每个 $k$，能作为多少个包含它的、长度为 $k$ 的子段的最大值。经典地，我们可以用单调栈 $\mathcal{O}(n)$ 处理出每个 $a_i$ 能作为最大值的极长区间 $[L_i,R_i]$。固定 $i,k$，考虑满足条件的区间 $[l,l+k-1]$ 的限制条件：

$$
\begin{cases}
l\geq L_i\\
l+k-1\leq R_i\\
l\leq i\\
l+k-1\geq i
\end{cases}
$$

解不等式，得到

$$
\max(L_i,i-k+1)\leq l\leq\min(i,R_i-k+1)
$$

也就是说 $a_i$ 对 $k$ 的贡献是

$$
\min(i,R_i-k+1)-\max(L_i,i-k+1)+1
$$

不难想到通过分类讨论去掉 $\max$ 和 $\min$：

$$
R_i-k+1\leq i\Leftrightarrow k\geq R_i-i+1\\
L_i\leq i-k+1\Leftrightarrow k\leq i-L_i+1
$$

下面令 $p_1=\min(i-L_i+1,R_i-i+1)$，$p_2=\max(i-L_i+1,R_i-i+1)$

### $1\leq k<p_1$
此时 $\min(i,R_i-k+1)$ 取 $i$，$\max(L_i,i-k+1)$ 取 $i-k+1$，因此 $a_i$ 的贡献为

$$
i-(i-k+1)+1=k
$$

于是我们给 $ans[1,p_1-1]$ 区间加上等差数列 $1,2,\cdots,p_1-1$ 即可。

### $p_1\leq k<p_2$
此时可能是 $\min(i,R_i-k+1)$ 的取值从 $i$ 变成了 $R_i-k+1$，也可能是 $\max(L_i,i-k+1)$ 的取值从 $i-k+1$ 变成了 $L_i$。注意到无论是哪种，$a_i$ 对 $ans[p_1,p_2-1]$ 的贡献都是固定的，于是代入 $k=p_1$ 计算出贡献 $v$，对 $ans[p_1,p_2-1]$ 做区间加 $v$ 即可。

### $p_2\leq k\leq R_i-L_i+1$
此时 $\min(i,R_i-k+1)$ 取 $R_i-k+1$，$\max(L_i,i-k+1)$ 取 $L_i$，因此 $a_i$ 的贡献为

$$
(R_i-k+1)-L_i+1=R_i-L_i+2-k
$$

和第一种 case 类似，对 $ans[p_2,R_i-L_i+1]$ 区间加上递减的等差数列

$$
R_i-L_i+2-p_2,R_i-L_i+1-p_2,\cdots,1
$$

即可。

---

于是我们只需要根据上述讨论，维护好区间加等差数列后的结果。二维差分即可，时间复杂度 $\mathcal{O}(n)$。

## 代码
```cpp
#include <iostream>

using namespace std;

#define int ll
#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5;

int n, a[N], L[N], R[N];
int top, stk[N];
ll d[N];

inline void add1(int l, int r, int v) {
	if (l > r) return;
	d[l] += v, d[r + 1] -= v;
}
inline void add2(int l, int r, int v, int d) {
	if (l > r) return;
	add1(l, l, v), add1(l + 1, r, d), add1(r + 1, r + 1, -v - (r - l) * d);
}
inline int calc(int i, int k) { return min(R[i] - k + 1, i) - max(L[i], i - k + 1) + 1; }

signed main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
    	while (top && a[stk[top]] <= a[i]) --top;
    	L[i] = stk[top] + 1, stk[++top] = i;
    }
    stk[top = 0] = n + 1;
    for (int i = n; i; --i) {
    	while (top && a[stk[top]] < a[i]) --top;
    	R[i] = stk[top] - 1, stk[++top] = i;
    }
    for (int i = 1; i <= n; ++i) {
    	int p1 = min(i - L[i] + 1, R[i] - i + 1);
    	int p2 = max(i - L[i] + 1, R[i] - i + 1);
    	int v1 = calc(i, p1) * a[i];
    	add2(1, p1 - 1, a[i], a[i]);
    	add2(p1, p2 - 1, v1, 0);
    	add2(p2, R[i] - L[i] + 1, v1, -a[i]);
    }
    for (int i = 1; i <= n; ++i) d[i] += d[i - 1];
    for (int i = 1; i <= n; ++i) d[i] += d[i - 1];
    for (int i = 1; i <= n; ++i) cout << d[i] << '\n';
    return 0;
}
```

---

## 作者：dami826 (赞：4)

灵感来源：[@Rainbow_qwq的P11364题解](https://www.luogu.com.cn/article/qwnc3p5p)

为表述方便，下称题目中的数列 $A$ 为 $A_1$。

用以下方法生成 $A_2$ 至 $A_N$：

- 对于任意 $1 \leq i \lt N,1 \leq j \lt |A_i|$，令 $A_{i+1_j}$ 为 $\max(A_{i_j},A_{i_{j+1}})$

发现一个固定的 $k$ 对应的答案就是数列 $A_k$ 的总和。

但显然直接暴力是 $O(n^2)$ 的，考虑优化。

观察这个操作过程，发现如果将数列分割成若干个内部数值相同的连续段 $s_1,s_2,\cdots,s_m$，并且它们的数值分别是 $v_1,v_2,\cdots,v_m$，那么每次操作之后连续段 $s_i$ 的长度变化 $d_i$ 即可由下式计算（将 $v_0$ 和 $v_{m+1}$ 视为 $+\infty$）：

  - $d_i=1-[v_{i-1} \gt v_i]-[v_{i+1} \geq v_i]$

其中 $[]$ 是艾佛森括号，括号内条件成立则取值为 $1$，否则为 $0$。

换句话说，$d_i$ 取决于 $s_i$ 两侧两个连续段中 $v$ 大于它的数量。

上式的正确性显然，此处不再赘述。（可以手模样例）

考虑直接用将每个连续段作为一个元素用线段树维护它们的 $d$、$d \cdot v$、长度 $siz$ 以及总和 $sum$，每次生成新数列时就对全局的 $siz$ 加 $d$，对全局的 $sum$ 加 $d \cdot v$。

由于 $d_i$ 在左右两个连续段没有变化时不变，而左右两个连续段变化当且仅当之前的连续段长度被减到 $0$，而一个连续段长度只能被减到 $0$ 一次，连续段个数又是 $O(n)$ 的，所以所有 $d_i$ 的变化次数是 $O(n)$ 的。

可以通过线段树维护每个 $d$ 为 $-1$ 的连续段长度的最小值 $mins$ 以及链表维护每个连续段当前的前驱和后继来实现 $O(\log n)$ 删除信息和更新被删区间的前驱和后继的 $d$。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define OK puts("OK");
using namespace std;
int n,s[200010],idx[200010],pre[200010],lst[200010];
struct node{
	int maxn,d,mins,siz,lazy,sum,vald;
};
struct segment_tree{
	node tree[800010];
	void pushdown(int index){
		if(tree[index].lazy){
			tree[index<<1].lazy+=tree[index].lazy;
			tree[index<<1|1].lazy+=tree[index].lazy;
			tree[index<<1].siz+=tree[index<<1].d*tree[index].lazy;
			tree[index<<1|1].siz+=tree[index<<1|1].d*tree[index].lazy;
			tree[index<<1].mins-=tree[index].lazy;
			tree[index<<1|1].mins-=tree[index].lazy;
			tree[index<<1].sum+=tree[index<<1].vald*tree[index].lazy;
			tree[index<<1|1].sum+=tree[index<<1|1].vald*tree[index].lazy;
			tree[index].lazy=0; 
		}
	}
	void pushup(int index){
		tree[index].maxn=max(tree[index<<1].maxn,tree[index<<1|1].maxn);
		tree[index].d=tree[index<<1].d+tree[index<<1|1].d;
		tree[index].mins=min(tree[index<<1].mins,tree[index<<1|1].mins);
//		printf("mins %lld %lld %lld %lld\n",index,tree[index].mins,tree[index<<1].mins,tree[index<<1|1].mins);
		tree[index].siz=tree[index<<1].siz+tree[index<<1|1].siz;
		tree[index].sum=tree[index<<1].sum+tree[index<<1|1].sum;
		tree[index].vald=tree[index<<1].vald+tree[index<<1|1].vald;
//		if(index==1){
//			printf("vald %lld %lld %lld %lld %lld\n",index,tree[index].d,tree[index].vald,tree[index<<1].vald,tree[index<<1|1].vald);
//		}
	}
	void build(int left,int right,int index){
		if(left==right){
			idx[left]=index;
			tree[index].maxn=s[left];
			tree[index].d=1-(s[left-1]>s[left])-(s[left+1]>=s[left]);
			tree[index].mins=(tree[index].d<0?1:LLONG_MAX);
			tree[index].siz=1;
			tree[index].lazy=0;
			tree[index].sum=s[left];
			tree[index].vald=s[left]*tree[index].d;
//			printf("--------------%lld %lld %lld\n",left,tree[index].d,tree[index].mins);
			return;
		}
		int mid=(left+right)>>1;
		build(left,mid,index<<1);
		build(mid+1,right,index<<1|1);
//		printf("pushup %lld %lld-%lld\n",index,left,right);
		pushup(index);
	}
	int ers(int left,int right,int index){
		if(left==right){
			return left;
		}
		int mid=(left+right)>>1;
		pushdown(index);
//		printf("%lld %lld mins %lld %lld %lld mins %lld\n",left,mid,tree[index<<1].mins,mid+1,right,tree[index<<1|1].mins);
		if(tree[index<<1].mins==0){
			return ers(left,mid,index<<1);
		}
		else{
			return ers(mid+1,right,index<<1|1);
		}
	}
	void push(int g,int left,int right,int index){
		if(left==right){
			return;
		}
		int mid=(left+right)>>1;
		pushdown(index);
		if(g<=mid){
			push(g,left,mid,index<<1);
		}
		else{
			push(g,mid+1,right,index<<1|1);
		}
	}
	void update(int x,int td){
		push(x,1,n,1);
		tree[idx[x]].d=td;
		tree[idx[x]].mins=(tree[idx[x]].d<0?tree[idx[x]].siz:LLONG_MAX);
		tree[idx[x]].vald=tree[idx[x]].maxn*tree[idx[x]].d;
//			printf("==============%lld %lld\n",x,tree[idx[x]].vald);
		int p=idx[x];
		while(p>>=1){
			pushup(p);
		}
	}
}tr;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&s[i]);
		pre[i]=i-1;
		lst[i]=i+1;
	}
	s[0]=s[n+1]=LLONG_MAX;
	tr.build(1,n,1);
	for(int i=1;i<=n;i++){
		printf("%lld\n",tr.tree[1].sum);
		if(i==n){
			break;
		}
		tr.tree[1].lazy++;
		tr.tree[1].siz+=tr.tree[1].d;
		tr.tree[1].mins--;
		tr.tree[1].sum+=tr.tree[1].vald;
		while(tr.tree[1].mins==0){
			int tmp=tr.ers(1,n,1);
//			printf("ers %lld\n",tmp);
			pre[lst[tmp]]=pre[tmp];
			lst[pre[tmp]]=lst[tmp];
			int p=idx[tmp];
			tr.tree[p]={0,0,LLONG_MAX,0,0,0,0};
			tr.update(tmp,tr.tree[p].d);
			if(pre[tmp]){
				int td=tr.tree[idx[pre[tmp]]].d;
				td+=(s[pre[tmp]]<=s[tmp]);
				td-=(s[pre[tmp]]<=s[lst[tmp]]);
				tr.update(pre[tmp],td);
			}
			if(lst[tmp]){
				int td=tr.tree[idx[lst[tmp]]].d;
				td+=(s[lst[tmp]]<s[tmp]);
				td-=(s[lst[tmp]]<s[pre[tmp]]);
				tr.update(lst[tmp],td);
			}
		}
	}
	return 0;
} 
```

---

## 作者：2012_Zhang_ (赞：4)

题外话：  
写了 F 的单调栈后才看的 E 题反悔贪心，一眼想到思路但赛后才写完 QWQ。  
# 思路解析
首先我们看一下暴力，枚举大小为 $$k$$ 的区间，显然是 $$N^2$$ 的，不可行。  
很多人此时可能都在想如何优化暴力，但不妨换个思路，不如考虑每个 $$A_i$$ 在哪些大小的区间里产生贡献。  
初步的思路有了，现在有两个问题：  
1. 每个 $$A_i$$ 在哪些大小的区间里产生贡献？
2. 对于每个大小的区间贡献是多少？

## Part 1
先来解决第一个问题。  
分析对于每个区间 $$A_i$$ 产生贡献且不会重复计算所需要满足的条件：
1. 记 $$l$$ 为 $$i$$ 左侧最大的 $$j$$ 使得 $$a_i < a_j$$，则左端点应在 $$l$$ 的右侧。
2. 记 $$r$$ 为 $$i$$ 右侧最小的 $$j$$ 使得 $$a_i \le a_j$$，则右端点应在 $$r$$ 的左侧。

这样既避免了区间中存在大于 $$A_i$$ 的数，又避免了重复计算贡献。  
这样一划分，$$A_i$$ 产生贡献的区间应在 $$[l+1,r-1]$$ 之内，且包含 $$i$$。  
这样的区间满足 $$1 \le k \le r-l+1$$。
## Part 2
接着再来看第二个问题。  
先记 $$p_1=i-l,p_2=r-i$$。  
$$p_1$$ 表示 $$l$$ 到 $$i$$ 之间的间隔数（含 $$i$$），$$p_2$$ 表示 $$i$$ 到 $$r$$ 之间的间隔数（含 $$i$$）。  

先讨论 $$1\le k\le \min(p_1,p_2)$$，  
显然对区间贡献的次数为 $$k$$，  
因为对于所有包含 $$i$$ 的长度为 $$k$$ 的区间，$$i$$ 恰好对应 $$k$$ 个点，形成 $$k$$ 次贡献
 
再来讨论 $$\min(p_1,p_2)<k\le p_1+p_2-\min(p_1,p_2)$$，  
显然对区间贡献的次数为 $$\min(p_1,p_2)$$，  
因为对于所有包含 $$i$$ 的长度为 $$k$$ 的区间，$$i$$ 恰好对应 $$\min(p_1,p_2)$$ 个点，形成 $$\min(p_1,p_2)$$ 次贡献。  

最后讨论 $$p_1+p_2-\min(p_1,p_2)<k\le p_1+p_2-1$$，  
 显然对区间贡献的次数为 $$p1+p2-k$$，  
 因为对于所有包含 $$i$$ 的长度为 $$k$$ 的区间，$$i$$ 恰好对应 $$p1+p2-k$$ 个点，形成 $$p1+p2-k$$ 次贡献。  

这个过程可以用差分实现，最后统计。  
## 复杂度分析
思路已经分析完毕，开始计算复杂度。  
单调栈与差分中复杂度均为 $$O(N)$$，总复杂度为 $$O(N)$$，可以较快的通过本题。
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=3e6;
int n,a[maxn],st[maxn],l[maxn],r[maxn],tot,d[maxn],d2[maxn];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		while(tot&&a[st[tot]]<=a[i]) tot--;
		if(tot) l[i]=st[tot];
		st[++tot]=i;
	}
	tot=0;
	for(int i=n;i>=1;i--){
		while(tot&&a[st[tot]]<a[i]) tot--;
		if(tot) r[i]=st[tot];
		else r[i]=n+1;
		st[++tot]=i;
	}
	for(int i=1;i<=n;i++){
		int R=r[i]-i,L=i-l[i];
		d[1]+=a[i],d[min(L,R)+1]-=a[i],d2[min(L,R)+1]+=min(L,R)*a[i],d2[L+R-min(L,R)+1]-=min(L,R)*a[i];
		d[L+R-min(L,R)+1]-=a[i],d[L+R]+=a[i],d2[L+R-min(L,R)+1]+=(L+R)*a[i],d2[L+R]-=(L+R)*a[i];
	}
	for(int i=1;i<=n;i++){
		d[i]+=d[i-1],d2[i]+=d2[i-1];
		cout<<d[i]*i+d2[i]<<endl;
	}
}
```
## THE END
望管理员大大给个通过。  
题解制作不易，留个赞再走吧。

---

## 作者：DHT666 (赞：2)

## 题意
一个长度为 $n$ 的序列 $a_i$，求其不同长度连续子序列的最大值和。

## 思路
如果不用分不同长度怎么做？

可以考虑每个数的贡献，用单调栈求出每个数的贡献区间，直接加和即可。

要分长度怎么做？

假设用单调栈求出当前讨论的 $a_i$ 的贡献区间是 $[l_i,r_i]$，即在这个区间内、包括了 $a_i$ 的连续子序列都会被 $a_i$ 贡献，我们只要求出每种长度的连续子序列被选了几次，与 $a_i$ 的乘积就是一次对答案的贡献。

其实就是在 $[l_i,i]$ 和 $[i,r_i]$ 中分别选一个数 $x$ 和 $y$，$[x,y]$ 就会被 $a_i$ 贡献。

我们设 $L$ 为 $[l_i,i]$ 的长度，$R$ 为 $[i,r_i]$ 的长度，$len$ 为 $[l_i,r_i]$ 的长度，$p=\min(L,R)$，$q=\max(L,R)$。

现在可以对要贡献的连续子序列的长度 $k$ 分类讨论了。

- 对于 $1\le k \le p$ 的情况，每种 $k$ 会有 $k$ 次被选，这时就是对答案数组的 $[1,p]$ 每个位置加 $i$，可以差分解决（具体地，先正常差分，然后在统计完做前缀和时，给位置 $i$ 乘上权重 $i$）。
- 对于 $p < k \le q$ 的情况，每种 $k$ 会有 $p$ 次被选，这时就是对答案数组的 $[p+1,q]$ 每个位置加 $p$，用典型的差分解决。
- 对于 $q < k \le len$ 的情况，每种 $k$ 会有 $len-k+1$ 次被选，这时就是对答案数组的 $[q+1,len]$ 每个位置加 $len-i+1$，此时就有些复杂了。分析发现，在区间内，所加的数是每次 -1 的，这时如果我们用差分去解决它，会在**差分数组**上呈现：加一个数，然后连续一串 -1，这一串 -1 就是在差分数组上区间修改，可以再用一次差分解决它。

基本就讨论完了，还有一个细节，上述对答案数组的修改时，没有带上权 $a_i$（答案要求的是最大值和而不是个数啊喂），写代码时注意一下。

## 代码
我觉得我写的有点乱，就只放链接了：[Code](https://atcoder.jp/contests/abc407/submissions/66136281)。

---

## 作者：huangyuze01 (赞：2)

### [ABC407 F - Sums of Sliding Window Maximum](https://atcoder.jp/contests/abc407/tasks/abc407_f) 

如果直接计算，即使使用单调队列也需 $O(n^2)$，无法通过，由于 $ans_k$ 的值是累加起来的和，因此考虑每个 $A_i$ 的贡献。

容易发现，记 $lt[i]$ 表示 $i$ 前面第一个比 $A_i$ 大的数的位置的下一个位置，没有则为 $1$，$rt[i]$ 同理。则 $A_i$ 可以贡献 $ans_1$ 到 $ans_{rt[i]-lt[i]+1}$。单调栈 $O(n)$ 计算即可。

此时有一个细节需要注意：相同的数可能会多贡献或者漏贡献。此时只需稍加修改，计算 $lt$ 时把 $ar[sta[top]]==ar[i]$ 的 $pop$ 掉，计算 $rt$ 时不 $pop$掉，就能做到不重不漏。**换句话说：$[lt_i,i]$ 中有和 $A_i$ 相同的数，$[i,rt_i]$ 没有与 $A_i$ 相同的数。** 

接下来我们考虑是怎样贡献的。
手玩几组数据可以发现，记 $pos = min(i-lt[i],rt[i]-i),len = rt[i]-lt[i]+1$。则  
1. 对于 $i\in[1,pos], ans_i = ans_i + i \times A_i$  
2. 对于 $i\in[pos+1,len-pos], ans_i = ans_i + (pos+1) \times A_i$  
3. 对于 $i\in[len-pos+1,len], ans_i = ans_i + (len-i+1) \times A_i$

对于 $1,2$ 操作，线段树可以维护，但是对于 $3$ 操作，线段树无法直接维护。此时有两种方法：  
1. 记 $C_i = ans_i-ans_{i-1}$，则只需维护 $C$ 的区间加操作，时间复杂度 $O(n \times \log n)$  
2. 又记 $D_i = C_i-C_{i-1}$，二次差分，则只需对 $D$ 进行单点修改，最后二次前缀和即可，时间复杂度 $O(n)$

这里给出个数据：$\{2,4,3,5,4\}$，大家可以手模一下  
代码自己写

---

## 作者：Getaway_Car (赞：1)

一眼题啊。设 $a_i$ 左侧第一个**不比它小**的数的位置为 $lft_i$，它右侧第一个**比它大**的数的位置为 $rgt_i$。（这样可以保证既不漏算又不重复计算。）那么对于 $a_i$，它可能作为最大值的极长区间显然是 $(lft_i, rgt_i)$。这个区间又被 $a_i$ 分为左右两段。设两段中较短的一段长度为 $mn = \min\{i - lft[i], rgt[i] - i\}$，较长一段长度为 $mx = \max\{i - lft[i], rgt[i] - i\}$，总长度为 $len = rgt_i - lft_i + 1$。那么 $a_i$ 可以带来以下贡献：

- $\forall k \in [1, mn], ans_k \leftarrow ans_k + k \cdot a_i$；

- $\forall k \in (mn, mx], ans_k \leftarrow ans_k + mn \cdot a_i$；

- $\forall k \in (mx, len], ans_k \leftarrow ans_k + (len + 1 - k) \cdot a_i$。

将第三组式子拆为：

- $\forall k \in (mx, len], ans_k \leftarrow ans_k + (len + 1) \cdot a_i, ans_k \leftarrow ans_k - k \cdot a_i$。

于是维护两个差分数组即可。第一个差分数组 $c1_i$ 维护的实际值就是 $c1_i$，第二个差分数组 $c2_i$ 维护的实际值是 $i \cdot c1_i$。

于是就做完了。

[提交记录](https://atcoder.jp/contests/abc407/submissions/66119295)。

---

## 作者：Exscallop64_ (赞：1)

## 题目简述

给定一个长度为 $n$ 的序列 $a_1, a_2,\dots,a_n$，定义 $f(l,r) = \max_{i=l}^{r} a_i$，并令 $ans_k$（$1 \le k \le n$）为 $\sum_{i=1}^{n-k+1} f(i,i+k-1)$，求出所有的 $ans_1,ans_2,\dots,ans_n$。

## 思路

我们不妨反过来考虑 $a_i$ 可以对那些 $k$ 造成贡献。

令 $l_i$ 表示 $1 \le j < i$ 且 $a_j > a_i$ 中最大的 $j$，若没有则为 $0$。$r_i$ 表示 $i < j \le n$ 且 $a_j \ge a_i$ 中最小的 $j$，若没有则为 $n+1$。

可以发现，对于所有的区间 $[L,R]$，若 $l_i < L \le i \le R < r_i$，则 $f(L,R)=a_i$。注意若 $l_i$ 的定义与 $r_i$ 相同都是 $\ge$ 则会重复计数。

现在我们考虑 $a_i$ 对当前 $ans_{len}$ 的贡献。令 $l_{min}$ 表示长度为 $len$ 的包含 $i$ 的区间左端点最小能取到的值，$l_{max}$ 表示长度为 $len$ 的包含 $i$ 的区间左端点最大能取到的值，显然对 $ans_{len}$ 的贡献为 $(l_{max} - l_{min} + 1)a_i$，分四类讨论。

> $l_i < i - len + 1,i + len - 1 < r_i$（即 $1 \le len \le \min(i - l_i, r_i - i)$）
>
> 显然此时 $l_{min} = i - len + 1$，$l_{max} = i$，则对其贡献为 $len \times a_i$。

> $l_i \ge i - len + 1,i + len - 1 < r_i$（即 $i - l_i + 1 \le len \le r_i - i$）
>
> 此时 $l_{min} = l_i + 1$，$l_{max} = i$，则对其贡献为 $(i - l_i) \times a_i$。

> $l_i < i - len + 1,i + len - 1 \ge r_i$（即 $r_i - i + 1 \le len \le i - l_i$）
>
> 此时 $l_{min} = i - len + 1$，$l_{max} = r_i - len$，则对其贡献为 $(r_i - i) \times a_i$。

> $l_i \ge i - len + 1,i + len - 1 \ge r_i$（即 $\max(i - l_i + 1,r_i - i + 1) \le len \le r_i - l_i - 1$）
>
> 此时 $l_{min} = l_i + 1$，$l_{max} = r_i - len$，则对其贡献为 $(r_i - l_i - len) \times a_i = (r_i - l_i) \times a_i - len \times a_i$。

分四类了后可以发现 $ans_k$ 一定可以写成 $x_i \times i + y_i$ 的形式，且每种讨论对应产生的贡献是一段区间，维护 $x$ 数组与 $y$ 数组的差分数组修改即可，至于 $l_i$ 与 $r_i$ 则可以使用单调栈求解。

注意第二类与第三类其实对应了 $i - l_i < r_i - i$ 与 $i - l_i > r_i - i$ 的情况，实际是一样的。

## 复杂度分析

+ 时间复杂度 $O(n)$。

+ 空间复杂度：$O(n)$。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 2e5 + 5;

int n, a[MAXN], stk[MAXN], tot, l[MAXN], r[MAXN];
ll d1[MAXN], d2[MAXN];

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; i++){
  	cin >> a[i];
  }
  tot = 0;
  fill(l + 1, l + 1 + n, 0);
  for(int i = n; i >= 1; i--){
  	for(; tot && a[stk[tot]] <= a[i]; tot--){
  	  l[stk[tot]] = i;	
	}
	stk[++tot] = i;
  }
  tot = 0;
  fill(r + 1, r + 1 + n, n + 1);
  for(int i = 1; i <= n; i++){
  	for(; tot && a[stk[tot]] < a[i]; tot--){
  	  r[stk[tot]] = i;	
	}
	stk[++tot] = i;
  }
  for(int i = 1; i <= n; i++){
  	int x = i - l[i], y = r[i] - i;
  	if(x > y) x ^= y, y ^= x, x ^= y;
  	d1[1] += a[i], d1[x] -= a[i];
  	d2[x] += 1ll * x * a[i], d2[y] -= 1ll * x * a[i];
	d1[y] -= a[i], d1[x + y] += a[i]; 
	d2[y] += 1ll * (x + y) * a[i], d2[x + y] -= 1ll * (x + y) * a[i]; 
  }
  for(int i = 1; i <= n; i++){
  	d1[i] += d1[i - 1], d2[i] += d2[i - 1];
  	cout << 1ll * d1[i] * i + d2[i] << "\n";
  }
  return 0;
}
``````

式子蒟蒻写时可能会有所差错，烦请巨佬指出。

---

## 作者：littlesnake (赞：1)

- 前言

[抄的很好，下次别抄了（这道的原题）](https://www.luogu.com.cn/problem/SP26308)。

听老师说是可以用线段树+单调栈维护做，我尝试了一个线段树，发现要 $O(n^2 \log{n})$ 的复杂度。[TLE 黑历史（AC 27 个点，TLE 10 个点）](https://atcoder.jp/contests/abc407/submissions/66147561)。

于是开始奋斗的历程。

- 思路

我们考虑对与每个数，求它在哪些区间会被作为最大值出现。

于是我们设 $L_i$ 为 $a_i$ 左边第一个**大于等于** $a_i$ 的数的下标（因为数有重复），设 $R_i$ 为 $a_i$ 右边第一个**大于** $a_i$ 的数的下标。

每一个区间都只会位于第一个出现的最大值处被枚举，就不会出现重复计算的情况。

然后我们的时间复杂度达到了 $O(n^2)$，可惜了，$n \le 2 \times 10^5$，在 SPJ 的题上更是 $\le 5 \times 10^5$，依旧 TLE。

我们可以考虑只枚举 $a_i$ 作为区间内第一个出现的最大值的所有可能区间的左端点，所以我们只需要从 $L_i+1$ 枚举到 $i$ 就可以了。然后右端点的范围就是从 $i$ 到 $R_i+1$，然后我们只需要将这个区间内都加上 $a_i$ 就行了。

因为是后查询，所以直接差分。然后枚举**右端点**就过了。

[AC 记录 QwQ](https://atcoder.jp/contests/abc407/submissions/66148422)。

- 答疑解惑

为什么要枚举右端点？因为右端点范围短。

时间复杂度是怎样的？$O(n \log n)$。

---

## 作者：Inv_day_in_R (赞：0)

前言：这道题我赛时写了个 $O(n\log^2n)$ 的 600ms 无差分做法，至于为什么是这个复杂度是大佬在[这个帖子](https://www.luogu.com.cn/discuss/1087864)里说明的，这里就不放了。（还要再乘个线段树的 $O(\log n)$）

其实我觉得这个做法很好想。

首先在 $a$ 数组两边加入无穷大，用单调栈预处理出 $a_i$ 左边第一个**大于等于**它的数的下标 $l_i$ 和右边第一个**大于**它的数的下标 $r_i$。（跟帖子里不太一样，但是代码是实现的这个，一个道理）

至于为什么一个是大于一个是大于等于，是为了后面避免重复计算。

然后考虑每一个 $a_i$ 的贡献。首先可以产生贡献的区间一定属于 $(l_i,r_i)$，并且包括 $i$。不妨枚举左端点 $l_i<j\leq i$，然后此时对长度为 $i-j+1$ 到 $r_i-j$ 的答案都有贡献。怎么处理呢？这时聪明的你一定脱口而出：~~差分！~~ 线段树。

可如果你就这么提交上去的话，那可就 TLE 了。（虽然我没交，但数据应该没那么弱）怎么办呢？不妨使用一个玄学优化，如果 $i$ 距离 $r_i$ 更近，那就枚举右端点，线段树处理左端点。然后这时你的复杂度就成了[这个帖子](https://www.luogu.com.cn/discuss/1087864)。

咦？怎么 RE 了？居然是我 copy 数据范围是 $10^5$ 的线段树模板？改完就对了。（突然发现线段树模板里我用的是空格而主函数里的是制表符）


```cpp
namespace AC{
int A[200010];
struct node{
    int l,r,sum,add;
}tr[800010];
void pushup(int p){
    tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
}
void pushdown(int p){
    tr[p<<1|0].add+=tr[p].add;
    tr[p<<1|1].add+=tr[p].add;
    tr[p<<1|0].sum+=tr[p].add*(tr[p<<1|0].r-tr[p<<1|0].l+1);
    tr[p<<1|1].sum+=tr[p].add*(tr[p<<1|1].r-tr[p<<1|1].l+1);
    tr[p].add=0;
}
void build(int s,int t,int p){
    tr[p].l=s,tr[p].r=t;
    if(s==t){
        tr[p].sum=A[s];
        return;
    }
    int mid=s+t>>1;
    build(s,mid,p<<1|0);
    build(mid+1,t,p<<1|1);
    pushup(p);
}
int query(int l,int r,int s,int t,int p){
    if(l<=s&&t<=r)return tr[p].sum;
    pushdown(p);
    int mid=s+t>>1,res=0;
    if(l<=mid)res+=query(l,r,s,mid,p<<1|0);
    if(r>mid)res+=query(l,r,mid+1,t,p<<1|1);
    return res;
}
void modify(int l,int r,int c,int s,int t,int p){
    if(l<=s&&t<=r){
        tr[p].add+=c;
        tr[p].sum+=c*(t-s+1);
        return;
    }
    pushdown(p);
    int mid=s+t>>1;
    if(l<=mid)modify(l,r,c,s,mid,p<<1|0);
    if(r>mid)modify(l,r,c,mid+1,t,p<<1|1);
    pushup(p);
}
int a[200010],l[200010],r[200010];
void solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	a[0]=a[n+1]=1e18;
	stack<int>st;
	for(int i=0;i<=n+1;i++){
		while(!st.empty()&&a[st.top()]<a[i])r[st.top()]=i,st.pop();
		st.push(i);
	}
	for(int i=n+1;i>=0;i--){
		while(!st.empty()&&a[st.top()]<=a[i])l[st.top()]=i,st.pop();
		st.push(i);
	}
	build(1,n,1);
	for(int i=1;i<=n;i++){
		if(i-l[i]>r[i]-i){
			for(int j=i;j<r[i];j++)modify(j-i+1,j-l[i],a[i],1,n,1);
		}
		else{
			for(int j=l[i]+1;j<=i;j++)modify(i-j+1,r[i]-j,a[i],1,n,1);
		}
	}
	for(int i=1;i<=n;i++)cout<<query(i,i,1,n,1)<<endl;
}
}
```

---

## 作者：A2_Zenith (赞：0)

这个题看上去好原啊。

定义 $L_i$ 为 $j \in [1,i)$ 中最靠右的 $a_j \ge a_i$ 的位置（不存在定义为 $0$）。定义 $R_i$ 为 $j \in (i,n]$ 中最左的 $a_i<a_j$ 的位置（不存在定义为 $n+1$） 。为什么这么定义呢，为了每个子段中只有最靠左的最大值产生贡献（去重）。

然后注意到，如果一个子段 $[l,r]$ 的最大值为 $a_i$，那么一定有 $i \in [l,r] \sube (L_i,R_i)$。

好的！这个时候可以尝试枚举子段长度 $k$ 计算贡献了。

先定义 $c_i = i-L_i,d_i = R_i - i$。不妨设 $c_i < d_i$，因为小于号反过来的情况是对称的。

对于 $k \in [1,c_i]$，$i$ 对于 $[l,r]$ 的相对位置是没有限制的。换个说法，从 $[i-k+1,i]$ 到 $[i,i+k-1]$ 的所有子段都满足 $[l,r] \sube (L_i,R_i)$ 的条件。于是，$i$ 对 $k (k \in [1,c_i])$ 的贡献为 $ka_i$。

对于 $k \in (c_i,d_i]$，可以取到区间 $[L_i+1,L_i+k]$ 到 $[i,i+k-1]$，于是，$i$ 对 $k (k \in (c_i,d_i])$ 的贡献为 $c_ia_i$。

对于 $k \in (d_i,c_i+d_i-1]$，这时注意到不管 $[l,r](r=l+k-1)$ 在 $(L_i,R_i)$ 中如何滑动，其都满足 $i \in [l,r]$ 的条件。答案是 $(c_i+d_i-k)a_i$。

发现只需要做区间加等差数列，二阶差分解决，$\mathcal{O}(n)$。

这里还是顺便提一下区间加等差数列怎么做吧。

令 ${\rm A}(l,r,x,D)$ 为 $\forall i \in [l,r],a_i \leftarrow a_i+x+(i-l)D$ 的操作。

$$[0,0,0 \cdots 0,x,x+D,x+2D \cdots X+(r-l)D,0,0,0 \cdots 0]$$

做一次差分得到

$$[0,0,0 \cdots 0,x,D,D \cdots D,-(X+(r-l)D),0,0 \cdots 0]$$

再做一次得到

$$[0,0,0 \cdots 0,x,x-D,0 \cdots 0,-(X+(r-l+1)D),(X+(r-l)D),0 \cdots 0]$$

是 $Ans_l \leftarrow Ans_l+x,Ans_{l+1} \leftarrow Ans_{l+1}+x-D,Ans_{r+1} \leftarrow Ans_{r+1}-(x+(r-l+1)D),Ans_{r+2} \leftarrow Ans_{r+2}+(x+(r-l)D)$。

结束。注意特判 $l=r$，和这个不大一样。

[Submission.](https://atcoder.jp/contests/abc407/submissions/66128928)

---

## 作者：zhangbo1000 (赞：0)

每次给一定区间内的数取 $\max$ 好像没有什么美妙的性质，考虑拆贡献，计算每个数 $A_i$ 会被哪几个区间视为最大值。

不妨设对于大小相等的数，左边的“小于”右边的，这样每个区间最大值就唯一了，不需要考虑去重。

我们可以针对每个 $A_i$ 计算前后各有多少个连续的数小于 $A_i$，分别记为 $l_i,r_i$，那么显然 $A_i$ 成为区间 $[a,b]$ 的最大值当且仅当 $a\ge i-l_i$ 且 $b\le i+r_i$。

注意我们需要对每个 $1\le k\le N$ 统计答案，于是容易想到按照区间长度分类讨论，设区间长度为 $j$，令 $x_1=\min(l_i,r_i),x_2=\max(l_i,r_i)$，$k=j$ 时的答案为 $s_i$。

- 若 $j>1+l_i+r_i$，显然该区间不可能符合要求。

- 若 $1\le j\le x1$，则区间完全不受左右端点限制，只需要包含 $A_i$ 就行，显然这样的区间有 $j$ 个，也就是说，对于所有 $1\le j\le x1$，$A_i$ 对 $s_i$ 有 $j\times A_i$ 的贡献。

- 若 $x_1<j\le x_2+1$，那么区间一头受限制，这样的区间只有 $x_1+1$ 个了，也就是说，对于所有 $x_1<j\le x_2$，$A_i$ 对 $s_i$ 有 $(x_1+1)\times A_i$ 的贡献。

- 若 $x_2+1<j\le 1+l_i+r_i$，那么区间两端点都受限制，容易发现这样的区间只剩下了 $2+x_1+x_2-j$ 个，也就是说，对于所有 $x_2+1<j\le 1+l_i+r_i$，$A_i$ 对 $s_i$ 有 $(2+x_1+x_2-j)\times A_i$ 的贡献。

这样贡献就考虑完了，我们分析下怎么算：

- $l_i,r_i$ 可以使用单调栈解决，被 $A_i$ 顶出去的数和被这个数顶出去的数的个数之和就是 $l_i$，$r_i$ 同理，可能有一些细节不同，我们可以用 `std::reverse` 翻转 $a$ 再跑一边然后翻回去。

- 计算贡献部分，我们需要对 $s$ 有以下操作（此处省略分析过程中对各个字母的定义）：
>
>  - 区间加 $j\times A_i$。
>  - 区间加 $(x_1+1)\times A_i$。
>  - 区间加 $(2+x_1+x_2-j)\times A_i$。
>
>这三种操作可以归结为：
>
>  - 区间加定值。
>  - 区间加等差数列。
>  - 在所有修改完成后进行单点查询。
>
>使用树状数组维护 $s$ 的差分数列可以完成操作 $1$，维护 $s$ 的差分数列的差分差分数列可以完成操作 $2$，查询就不用说了，当然其实也可以都使用后者维护（这也是官方解法的写法），是常数更优的。

然后就做完了。

[代码和评测记录（双树状数组写法）。](https://atcoder.jp/contests/abc407/submissions/66153458)

[代码和评测记录（全部二次差分）。](https://atcoder.jp/contests/abc407/submissions/66176748)

~~可惜昨晚没空打，不然我就蓝名了。~~

---

