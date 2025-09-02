# [BalkanOI 2018] Popa

## 题目背景

翻译自 BalkanOI 2018 Day2 T2「Popa」

> *"He's an outlaw and he's famous*  
> *Andrii Popa the courageous.*  
> *Day and night he rides,*  
> *He takes his tribute from the main road*  
> *And everywhere in the country*  
> *The thief catchers are running away as fast as they can"*
> 
> *\- ["Andrii Popa", Phoenix](https://music.163.com/song?id=508736536)*

## 题目描述

Ghiță 有一个下标从 $0$ 开始的正整数序列 $S$。因为他是喀尔巴阡的国王，所以他想要构造一个节点编号为 $0,1,\ldots ,N-1$ 的二叉树，满足：

- 树的中序遍历按节点编号升序排列。二叉树的中序遍历由以根的左子节点（如果存在）为根形成的子树的中序遍历，根的节点编号和以根的右子节点（如果存在）为根形成的子树的中序遍历顺次连接组成。  
- 如果 $x$ 是 $y$ 节点的父亲，那么 $S_x$ 整除 $S_y$。

二叉树是一种树形结构，每个节点最多有两个子节点，分别称为左子节点和右子节点。

不幸的是，著名的亡命之徒 Andrii Popa 偷走了序列 $S$，Ghiță 不能直接获取到。但对于任意两个连续的子序列 $[a,b]$ 和 $[c,d]$，他可以使用最先进的技术（他的手机）求出 $\gcd[a,b]$ 是否等于 $\gcd [c,d]$，其中 $\gcd[x,y]$ 指 $S_x,S_{x+1},S_{x+2},\ldots ,S_y$ 的最大公因数。不幸的是，这项技术十分昂贵——如果 Ghiță 使用超过 $Q$ 次，他将会支付一大笔罚金。请帮他在使用这项技术最多 $Q$ 次的情况下构建出他想要的树。保证这是可能的。任何合法的构建方案都可以被接受。

### 交互

本题只支持 C++ 语言使用函数交互。选手代码并不需要也不能包含 `popa.h`。

选手需实现如下函数：

```cpp
int solve(int N, int* Left, int* Right);
```

函数需返回树的根节点，并且将 `Left[i]` 和 `Right[i]` 分别赋值为 $i$ 的左子节点和右子节点。如果节点 $i$ 没有左子节点，则 `Left[i]` 应被赋为 $-1$，如果节点 $i$ 没有右子节点，则 `Right[i]` 应被赋为 $-1$。`Left` 和 `Right` 分别指向两个空间已被分配好且长度恰好为 $N$ 的数组。

函数 `solve` 在一次运行中会被调用最多 $5$ 次。我们建议谨慎使用全局变量。

选手可以调用如下函数（注意，选手须在代码中声明此函数）：

```cpp
int query(int a, int b, int c, int d);
```

这个函数当且仅当 $\gcd[a,b]=\gcd[c,d]$ 时返回 $1$，其中 $0\le a\le b<n,0\le c\le d<N$，否则返回 $0$。


### 样例

例如 $S=[12, 4, 16, 2, 2, 20]$，一组交互过程如下：

| 调用 `solve` | 调用 `query` | 调用 `solve` 之后 |
| :-----------: | :-----------: | :-----------: |
| `solve(6, Left, Right)` |  |  |
|  | `query(0, 1, 3, 5)` 返回 $0$ |  |
|  | `query(4, 5, 1, 3)` 返回 $1$ |  |
|  |  | `solve` 返回值为 $3$；`Left` 指向 $[-1, 0, -1, 1, -1, -1]$；`Right` 指向 $[-1, 2, -1, 4, 5, -1]$ |

样例中，Ghiță 国王想要的树形态如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/y5whph6a.png)


## 说明/提示

### 数据范围

| 子任务编号 | 限制 | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $N=100,Q=10^4$ | $37$ |
| $2$ | $N=10^3,Q=2\times 10^4$ | $24$ |
| $3$ | $N=10^3,Q=2\times 10^3$ | $39$ |


# 题解

## 作者：晴空一鹤 (赞：1)

题意是构造一棵树，满足第 $i$ 号节点权值为 $S_i$，且树的节点标号的中序遍历为 $1,2,...,n$，且树上每个儿子的权值都是他父亲的倍数，保证有解。你不知道 $S$ 数组的具体情况，但你可以询问一段 $S_i$ 的 $\gcd$ 是否等于另一段 $S_i$ 的 $\gcd$。

初看非常神秘，于是使用加点法观察。

假设我们已经对于前 $i$ 个节点构造了一棵符合条件的树，现在我们要加入节点 $i+1$。

考虑中序遍历的条件，我们发现这个点只能要么放在当前根的父亲（把根作为该节点的左儿子），要么挂在根节点开始的连续右链上（把下一个节点扳成左儿子），其他地方这个点都不会成为最后一个被遍历的。

我们维护右链，从链底向根依次尝试挂上去，由于每次挂点最多使右链长度加一，每一次尝试失败就会使右链长度减一，那我们总的尝试的规模大概为 $2n$ 次，刚好符合限制。

把尝试对应到询问上，我们要了解该点权值与链上节点是否有倍数关系，设处理到的链上节点为 $x$，那么这等价于 $\gcd(S_x,S_{i+1})=S_x=\gcd(S_x,S_x)$，用 $query$ 函数查即可。

有的读者可能会说，$query$ 只能查连续区间的 $\gcd$ 吧，但众所周知倍数具有传递关系，且中序遍历这一限制使得 $x+1$ 到 $i$ 这一堆节点都是 $x$ 节点直接或间接的子结点，所以这一段的 $\gcd$ 就等于 $S_x$ 和 $S_{i+1}$ 的 $\gcd$。

要注意的……哦，首先这题询问次数限制很严格，因此我们直接只判第二种情况，因为保证有解，第二种失败了那第一种不用查询肯定成功。

还有注意本题节点下标**从 0 开始**。

#### solve 部分代码

```cpp
int solve(int N, int* Left, int* Right) {
    int l[1005],r[1005],g=1,op[3005],cnt=0,ma=0;
    for(int i=1;i<=2*N;i++)op[i]=0;
    for(int i=1;i<=N;i++)
    l[i]=r[i]=-1;
    for(int i=2;i<=N;i++){
      op[0]=g;ma=0;
      for(int j=cnt;j>=0;j--)if(query(op[j]-1,i-1,op[j]-1,op[j]-1))
      {l[i]=r[op[j]];r[op[j]]=i-1;cnt=j+1;op[cnt]=i;ma=1;break;}
      if(!ma){l[i]=g-1;g=i;cnt=0;}    
     }
    for(int i=1;i<=N;i++)Left[i-1]=l[i],Right[i-1]=r[i];
    return g-1;
}
```

---

## 作者：x383494 (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/x383494/p/17616686.html)

[原题传送门](https://www.luogu.com.cn/problem/P9507)

## 题目描述

Ghiță 有一个下标从 $0$ 开始的正整数序列 $S$。因为他是喀尔巴阡的国王，所以他想要构造一个节点编号为 $0,1,\ldots ,N-1$ 的二叉树，满足：

- 树的中序遍历按节点编号升序排列。二叉树的中序遍历由以根的左子节点（如果存在）为根形成的子树的中序遍历，根的节点编号和以根的右子节点（如果存在）为根形成的子树的中序遍历顺次连接组成。  
- 如果 $x$ 是 $y$ 节点的父亲，那么 $S_x$ 整除 $S_y$。

二叉树是一种树形结构，每个节点最多有两个子节点，分别称为左子节点和右子节点。

不幸的是，著名的亡命之徒 Andrii Popa 偷走了序列 $S$，Ghiță 不能直接获取到。但对于任意两个连续的子序列 $[a,b]$ 和 $[c,d]$，他可以使用最先进的技术（他的手机）求出 $\gcd[a,b]$ 是否等于 $\gcd [c,d]$，其中 $\gcd[x,y]$ 指 $S_x,S_{x+1},S_{x+2},\ldots ,S_y$ 的最大公因数。不幸的是，这项技术十分昂贵——如果 Ghiță 使用超过 $Q$ 次，他将会支付一大笔罚金。请帮他在使用这项技术最多 $Q$ 次的情况下构建出他想要的树。保证这是可能的。任何合法的构建方案都可以被接受。

## 数据范围

| 子任务编号 | 限制 | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $N=100,Q=10^4$ | $37$ |
| $2$ | $N=10^3,Q=2\times 10^4$ | $24$ |
| $3$ | $N=10^3,Q=2\times 10^3$ | $39$ |

## 思路

分析条件。

> 树的中序遍历按编号升序排列。

想到 BST。

> 如果 $x$ 是 $y$ 节点的父亲，那么 $S_x$ 整除 $S_y$。

发现整除具有传递性，想到笛卡尔树。

## $O(n \log n)$ 做法

注意到树根一定是所有树的 $\gcd$，可以二分树根所在的区间，$\Theta(\log s)$ 次询问，其中 $s$ 为区间长度。

找到树根后，两边递归建树。

```cpp
namespace O_n_log_n{ // }{{{
int findroot(int l, int r){
	while(r-l > 1){
		int mid = (l+r)/2;
		if(query(l, mid-1, l, r-1)){
			r = mid;
		} else {
			l = mid;
		}
	}
	return l;
}
int build(int l, int r, int *left, int *right){
	if(l == r) return -1;
	int rt = findroot(l, r);
	left[rt] = build(l, rt, left, right);
	right[rt] = build(rt+1, r, left, right);
	return rt;
}
int solve(int in, int *left, int *right){
	return build(0, in, left, right);
}
} // {}}}
```

## $\Theta(n)$ 做法

回忆笛卡尔树的 $\Theta(n)$ 建树：维护目前全树的右链。

考虑右链末端点 $u$，及将要加入树中的点 $v$。发现 $\gcd(u,v)=v$，则 $v$ 为 $u$ 的祖先一定满足题意，类似笛卡尔树，将 $u$ 出栈即可。

对于 $u$ 出栈后的点 $u'$，发现 $u'$ 和 $v$ 不相邻，但 $u'$ 到 $v$ 均为 $u'$ 的后代，它们的 $\gcd$ 为 $u'$，因此询问 $u'$ 到 $v$ 的 $\gcd$ 等价于询问 $\gcd(u',v)$。

```cpp
namespace O_n{ // }{{{
std::stack<int> todo;
int solve(int in, int *left, int *right){
	UP(i, 0, in){
		left[i] = right[i] = -1;
		if(todo.empty()){
			todo.push(i);
		} else {
			while(!todo.empty()){
				if(query(i, i, todo.top(), i)) {
					left[i] = todo.top();
					todo.pop();
				} else break;
			}
			if(!todo.empty()){
				right[todo.top()] = i;
			}
			todo.push(i);
		}
	}
	int rt;
	while(!todo.empty()){
		rt = todo.top();
		todo.pop();
	}
	return rt;
}
} // {}}}
```

---

完整代码：

```cpp
#include <stack>
#define UP(i,s,e) for(auto i=s; i<e; ++i)
int query(int a, int b, int c, int d);
namespace solution{ // }{{{
constexpr int N = 1e3;
namespace O_n_log_n{ // }{{{
int findroot(int l, int r){
	while(r-l > 1){
		int mid = (l+r)/2;
		if(query(l, mid-1, l, r-1)){
			r = mid;
		} else {
			l = mid;
		}
	}
	return l;
}
int build(int l, int r, int *left, int *right){
	if(l == r) return -1;
	int rt = findroot(l, r);
	left[rt] = build(l, rt, left, right);
	right[rt] = build(rt+1, r, left, right);
	return rt;
}
int solve(int in, int *left, int *right){
	return build(0, in, left, right);
}
} // {}}}
namespace O_n{ // }{{{
std::stack<int> todo;
int solve(int in, int *left, int *right){
	UP(i, 0, in){
		left[i] = right[i] = -1;
		if(todo.empty()){
			todo.push(i);
		} else {
			while(!todo.empty()){
				if(query(i, i, todo.top(), i)) {
					left[i] = todo.top();
					todo.pop();
				} else break;
			}
			if(!todo.empty()){
				right[todo.top()] = i;
			}
			todo.push(i);
		}
	}
	int rt;
	while(!todo.empty()){
		rt = todo.top();
		todo.pop();
	}
	return rt;
}
} // {}}}
} // {}}}
int solve(int in, int *left, int *right){
	return solution::O_n::solve(in, left, right);
}
```


---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9507)。

## 思路

首先若 $\gcd[l,r]=a_r$，那么 $\forall i\in[l,r],a_r\mid a_i$。

本题要构造的二叉搜索树满足：对于一个点 $v$，其父亲为 $u$，有 $S_u\mid S_v$。

由于整除有传递性，不难想到在偏序集 $(S,\mid)$ 上构建笛卡尔树，和构建普通笛卡尔树的过程一样，我们维护一条最右链。

假设当前要插入的节点为 $u$。

- 如果 $S_u$ 刚好可以被最右链末端的权值 $w$ 整除，那么将 $u$ 加到最右链末端中。


- 否则在最右链上找到一个点 $j$ 使得 $S_j\mid S_u$，让 $j$ 的右儿子当做 $u$ 的左儿子，$j$ 的右儿子为 $u$。

- 如果两者都不满足，那么将 $u$ 作为该树的根节点。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int query(int a,int b,int c,int d);
int solve(int N,int *Left,int *Right){
    stack<int>stk;
    
    for(int i=0;i<N;i++) Left[i]=Right[i]=-1;

    stk.push(0);
    for(int i=1;i<N;i++){
        while(!stk.empty()){
            if(query(i,i,stk.top(),i)) Left[i]=stk.top(),stk.pop();
            else break;
        }
        if(!stk.empty()) Right[stk.top()]=i;
        stk.push(i);
    }
    int rt;
    while(!stk.empty()) rt=stk.top(),stk.pop();
    return rt;
}

```

---

## 作者：Populus_euphratica (赞：0)

## 思路

这个中序遍历等于序列本身我们似乎在哪里见过，一想，诶，这不笛卡尔树的一个要求吗。

那先来思考一下笛卡尔树 $O(n)$ 建树的方法。

对于笛卡尔树，我们维护了一个从根节点一直走右儿子形成的一条链，每次新加入一个元素 $x$，就找到链上第一个比 $x$ 大的元素 $y$，将 $x$ 的左儿子设为 $y$，然后把 $y$ 及 $y$ 后的元素删除，将 $x$ 加入链中，设 $x$ 为 $x$ 前面那个元素的右儿子。

维护这条链可以使用单调栈，每个元素只会入栈和出栈一次，时间复杂度 $O(n)$。

说起来比较绕，看代码会清晰的多，代码如下：

```cpp
for(int i = 1 ; i <= n ; i++){
	if(stk.empty()){
		stk.push(i);
		continue;
	}
	while(!stk.empty() && a[stk.top()] > a[i]){
		lson[i] = stk.top();
		stk.pop();
	}
	if(!stk.empty()) rson[stk.top()] = i;
	stk.push(i);
}
```

至于正确性问题，我这里就简单口胡一下。

首先我们要明确，原序列是一定有解的。

然后，我们每次插入一个 $x$ 元素，删掉的 $y$ 及后面的那一部分其实就是一条右儿子的链，所以可以直接接到 $x$ 后面，同时也满足性质。

那么留下来的 $x$ 的前面的元素一定都比 $x$ 小，所以可以将 $x$ 接到前一个元素后做右儿子。

简单说一下怎么找根，这个栈最后就是一条右儿子的链，栈底其实就是根节点。

那来看看笛卡尔树和这道题的联系。

这道题要求儿子可以被父亲整除，同时也和笛卡尔树的一样，中序遍历等于序列本身，那么考虑能否使用和笛卡尔树一样的建树方法进行维护。

同样的，我们维护一个右儿子链，那么考虑在加入 $x$ 的时候怎么维护。

设 $y$ 为现在的栈顶，如果 $x$ 可以作为 $y$ 的父亲，那么 $\gcd(x, y) = y$，这样就可以把 $y$ 作为 $x$ 的左儿子，删掉 $y$。

设 $y'$ 为现在的栈顶，如果 $x$ 可以作为 $y$ 的父亲，那么 $\gcd(x, y) = y$，这样就可以把 $y'$ 作为 $x$ 的左儿子，但是，我们知道我们维护的是一条右儿子链，也就是说，其实 $y'$ 是 $y$ 的父亲，那么就是说 $\gcd(y, y')$ 就等于 $y'$，所以这个问题就解决了，按照笛卡尔树那么跑就行。

这时可能就有个问题，为啥我们可以不判栈顶直接把新加入元素作为现栈顶的右儿子呢？

我们想，这个序列是有唯一解的，也就是说，如果不能把新加入元素作为现栈顶的右儿子那么这个东西就无解了，所以可以直接这么搞。

代码非常小清新，注意下交互题的格式就行。

```cpp
#include<bits/stdc++.h>
int query(int a, int b, int c, int d);
int stk[10010];
int solve(int n, int *lson, int *rson){
	int cnt = 0;
	for(int i = 0 ; i < n ; i++)
		lson[i] = rson[i] = -1;
	for(int i = 0 ; i < n ; i++){
		if(!cnt){
			stk[++cnt] = i;
			continue;
		}
		while(cnt){
			if(query(i, i, stk[cnt], i)){
				lson[i] = stk[cnt];
				cnt--;
			}else break;
		}
		if(cnt) rson[stk[cnt]] = i;
		stk[++cnt] = i;
	}
	return stk[1];
}
```

---

