# Keep the Sum

## 题目描述

You are given an integer $ k $ and an array $ a $ of length $ n $ , where each element satisfies $ 0 \le a_i \le k $ for all $ 1 \le i \le n $ . You can perform the following operation on the array:

- Choose two distinct indices $ i $ and $ j $ ( $ 1 \le i,j \le n $ and $ i \neq j $ ) such that $ a_i + a_j = k $ .
- Select an integer $ x $ satisfying $ -a_j \le x \le a_i $ .
- Decrease $ a_i $ by $ x $ and increase $ a_j $ by $ x $ . In other words, update $ a_i := a_i - x $ and $ a_j := a_j + x $ .

Note that the constraints on $ x $ ensure that all elements of array $ a $ remain between $ 0 $ and $ k $ throughout the operations.

Your task is to determine whether it is possible to make the array $ a $ non-decreasing $ ^{\text{∗}} $ using the above operation. If it is possible, find a sequence of at most $ 3n $ operations that transforms the array into a non-decreasing one.

It can be proven that if it is possible to make the array non-decreasing using the above operation, there exists a solution that uses at most $ 3n $ operations.

 $ ^{\text{∗}} $ An array $ a_1, a_2, \ldots, a_n $ is said to be non-decreasing if for all $ 1 \le i \le n - 1 $ , it holds that $ a_i \le a_{i+1} $ .

## 说明/提示

In the first test case, the array is already non-decreasing, so we do not need to perform any operations.

In the second test case, we can perform an operation with $ i=4 $ , $ j=1 $ , and $ x=1 $ . $ a_4 $ decreases by $ 1 $ to become $ 5 - 1 = 4 $ while $ a_1 $ increases by $ 1 $ to become $ 1 + 1 = 2 $ . After the operation, the array becomes $ [2, 2, 3, 4, 4] $ , which is non-decreasing.

Note that there are other ways to make the array non-decreasing, all of which would be considered correct as long as they do not use more than $ 3 \cdot n = 15 $ operations.

In the third test case, it is not possible to make the array non-decreasing. This is because there are no distinct pairs of indices $ i $ and $ j $ where $ a_i + a_j = 7 $ , so no operation can be done on the array.

In the fourth test case, the array is transformed as follows:

1. $ [\textbf{0}, 5, 3, 2, 7, 3, 1, \textbf{10}, 4, 0] $
2. $ [0, 5, \textbf{1}, 2, \textbf{9}, 3, 1, 10, 4, 0] $
3. $ [0, 5, 1, 2, \textbf{6}, 3, \textbf{4}, 10, 4, 0] $
4. $ [0, 5, 1, 2, \textbf{3}, 3, 4, 10, \textbf{7}, 0] $
5. $ [0, 5, 1, 2, 3, 3, 4, \textbf{5}, 7, \textbf{5}] $
6. $ [0, \textbf{1}, 1, 2, 3, 3, 4, 5, 7, \textbf{9}] $

## 样例 #1

### 输入

```
4
5 100
1 2 3 4 5
5 6
1 2 3 5 4
5 7
7 1 5 3 1
10 10
2 5 3 2 7 3 1 8 4 0```

### 输出

```
0
1
4 1 1
-1
6
1 8 2
3 5 2
5 7 3
5 9 3
8 10 5
2 10 4```

# 题解

## 作者：wanggk (赞：2)

[cnblogs](https://www.cnblogs.com/wanggk/p/18846511)

### 题意

给你一个整数 $K$ 和长度为 $n$ 的序列 $a$，$a_i \in [0,K]$。你可以进行如下操作不超过 $3n$ 次：

- 首先，选择两个下标 $i \not = j$，要求 $a_i+a_j=K$。
- 再选择一个 $x$，将 $a_i$ 减少 $x$，将 $a_j$ 增加 $x$。
- 要求每次操作完上一步后仍满足 $a_i,a_j \in [0,K]$。

是否能将 $a$ 序列变为不降的？输出方案或判断无解。$n \leq 2 \times 10^5,K \leq 10^9$。

### 题解

下文称两个数**匹配**等价于两数之和为 $K$。

由排序想到，是否能间接地达成 $Swap(a_i,a_j)$ 的操作。

当 $a_i+a_j=K$ 时可以（废话）。当存在 $k$ 使得 $a_i,a_k$ 匹配也是可以的：

先操作 $(a_i,a_k)$ 把 $a_i$ 变成和 $a_j$ 相等，再操作 $a_j,a_k$ 把 $a_j$ 变成最初的 $a_i$，完成了交换。

可惜其他情况我们没法实现交换。所以我们要想办法使那些不能匹配的变成能匹配的。

先任意找一对匹配的数 $a_x,a_y$，把 $a_x$ 与 $a_1$ 交换，$a_y$ 与 $a_n$ 交换，（此时 $a_1,a_n$ 就匹配了）再操作 $(a_1,a_n)$ 使得 $a_1=0,a_n=K$。

这时候我们发现，$i \in [2,n-1]$ 的所有 $a_i=0$ 和 $a_i=K$ 都有匹配了（即 $a_1$ 或 $a_n$），只需要把所有 $a_i=0$ 加入到 $a_1$ 的后面，所有 $a_n$ 加入到 $a_n$ 的前面。再把加入的最后一个 $0$ 和加入的最后一个 $K$ 改成 $(1,K-1)$，我们就可以加入剩下所有的 $a_i=1$ 和 $a_i=K-1$……

于是，任意时刻，排好序的部分都是一段前缀和一段后缀，每次加入能加入的数即可。

### 细节

无解的判断：原序列不是有序的，且不存在一对匹配的 $a_x,a_y$。

$K$ 很大，所以注意离散化，离散化的时候要把 $a_i$ 和 $K-a_i$ 都丢进去，这样离散化前后配对的值才能保持不变。

快速维护值和下标的映射关系可以用 `set`。在交换的时候同步维护位置。

实现一个 $Swap(x,y)$ （表示交换 $a_x,a_y$）函数会让代码简洁很多。特判 $Swap(i,i)$ 的情况，要直接退出。这种操作会被认为是不合法的。

### 代码

[提交记录](https://codeforces.com/contest/2103/submission/316908668)

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define For(i,il,ir) for(int i=(il);i<=(ir);++i)
using namespace std;
const int maxn=2e5+10;

int K,n;
int a[maxn];
int h[maxn<<1],px,py;
set<int> st[maxn<<1];
vector<int> ai,aj,ax;

#define Print(ii,jj,xx) ai.pb(ii),aj.pb(jj),ax.pb(xx)
#define Insert(p) st[a[p]].insert(p)
#define Erase(p) st[a[p]].erase(p)
void Swap(int x,int to,int y){
	if(x==to) return;
	Print(x,y,h[a[x]]-h[a[to]]);
	Print(to,y,h[a[to]]-h[a[x]]);
	Erase(x),Erase(to),swap(a[x],a[to]);
	Insert(x),Insert(to);
}
void solve()
{
	For(i,1,n) h[i-1]=a[i],h[i+n-1]=K-a[i];
	sort(h,h+n+n),K=unique(h,h+n+n)-h-1;

	px=py=-1;
	For(i,1,n){
		a[i]=lower_bound(h,h+K+1,a[i])-h;
		if(st[K-a[i]].size())
			px=*st[K-a[i]].begin(),py=i;
		Insert(i);
	}
	if(px==-1){ puts("-1");return; }

	Swap(px,1,py); px=1;
	Swap(py,n,px); py=n;
	Erase(1),Erase(n);

	for(int v=0;v<K-v;v++){
		Print(px,py,h[a[px]]-h[v]);
		a[px]=v,a[py]=K-v;
		while(!st[v].empty())
			Swap(*st[v].begin(),++px,py),Erase(px);
		while(!st[K-v].empty())
			Swap(*st[K-v].begin(),--py,px),Erase(py);
	}
	printf("%d\n",(int)ai.size());
	for(int i=0;i<ai.size();i++)
		printf("%d %d %d\n",ai[i],aj[i],ax[i]);
}
void clear(){
	For(i,0,K) st[i].clear();
	ai.clear(),aj.clear(),ax.clear();
}
signed main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&K);
		bool flag=true;
		For(i,1,n) 
			scanf("%d",&a[i]),flag&=(a[i]>=a[i-1]);
		if(flag) puts("0");
		else solve(),clear();
	}
	return 0;
}
```

---

## 作者：liangbob (赞：1)

## CF2103E 题解

[更差的阅读体验](https://www.cnblogs.com/sslbj/p/18859495)。

不难**注意到题目所述操作的本质**是：对一对满足 $a_i+a_j=k$ 的 $(a_i,a_j)$，在和不变，且分配后仍然有 $0\le a_i,a_j \le k$ 的情况下重新进行分配。

比如 $a_i=2,a_j=7,k=9$ 时，一次操作可以让 $(a_i,a_j)$ 变为 $(0,9)$ 或 $(1,8)$ 或 $(2,7)$ 或 $(3,6)$ 等等。

分析题目条件。发现操作次数不多于 $3n$ 且要让数组单调不降。**考虑进行 $n$ 次在 $3$ 步之内交换数组中的两个数，使得原数组从小到大排序**。

假设要交换 $a_x$ 和 $a_y$。当 $a_x+a_y=k$ 时，操作是简单的。

考虑 $a_x+a_y\neq k$ 的情况。**发现我们必须借助另外一组 $a_i+a_j=k$ 来交换 $a_x$ 和 $a_y$**。

如何借助呢？回顾交换的本质，我们要需要先把 $a_x$ 放到一个临时变量里。对应到这题，**我们需要把 $a_i$ 或 $a_j$ 中的一个换成 $a_x$**。之后的操作就变得显然了。

令 $px=a_x$，$py=a_y$，$pi=a_i$，$pj=p_j$。我们可以按如下方式交换：

| 操作次数   | 此时 $a_x$ | 此时 $a_y$ | 此时 $a_i$ | 此时 $a_j$ | 操作的 $(i,j,k)$ |
| ---------- | ---------- | ---------- | ---------- | ---------- | ---------------- |
| 初始       | $px$       | $py$       | $pi$       | $pj$       | 无               |
| 第一次操作 | $px$       | $py$       | $px$       | $k-px$     | $(i,j,pi-px)$    |
| 第二次操作 | $py$       | $py$       | $px$       | $k-py$     | $(x,j,px-py)$    |
| 第三次操作 | $py$       | $px$       | $px$       | $k-px$     | $(y,j,py-px)$    |

**发现此时 $a_i+a_j=k$ 依然成立，因此我们可以多次借助 $a_i$ 和 $a_j$ 进行操作**。

但是有一个问题：在我们对其它数排完之后，剩下的 $a_i$ 和 $a_j$ 还没有排序到位。而我们的操作次数已经快要用完了。

怎么办呢？**如果这两个数再操作一步就可以使得整个序列有序就好了。于是我们考虑让 $a_1$ 和 $a_n$ 相加等于 $k$**。这样只需一次操作使得 $a_1=0,a_n=k$ 就可以了。

跟交换数一样，我们**考虑借助一组 $a_i+a_j=k$ 来让 $a_1$ 和 $a_n$ 相加等于 $k$**。这个比较显然，这里直接给出方案（令 $pa = a_1,pb=a_n$）：

| 操作次数   | 此时 $a_1$ | 此时 $a_n$ | 此时 $a_i$ | 此时 $a_j$ | 操作的 $(i,j,k)$ |
| ---------- | ---------- | ---------- | ---------- | ---------- | ---------------- |
| 初始       | $pa$       | $pb$       | $pi$       | $pj$       | 无               |
| 第一次操作 | $pa$       | $pb$       | $pb$       | $k-pb$     | $(i,j,pi-pb)$    |
| 第二次操作 | $pa$       | $k-pa$     | $pb$       | $pa$       | $(n,j,pa+pb-k)$  |

所以，我们先进行上表所述操作。接着对 $2$ 到 $n-1$ 利用交换进行排序，最后通过操作让 $a_1=0,a_n=k$（这个很显然了，具体怎么操作留给各位思考）即可。

问题来了：给定一个数组，每次可以交换任意两个数，如何通过不超过 $n$ 次交换进行排序呢？这是个很经典的问题，参考 [CF489A](https://codeforces.com/problemset/problem/489/A) 的 $O(n)$ 做法即可。

于是原问题获得顺利的解决。

[代码](https://codeforces.com/contest/2103/submission/318316400)。

---

