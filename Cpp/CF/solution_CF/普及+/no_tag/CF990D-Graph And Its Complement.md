# Graph And Its Complement

## 题目描述

Given three numbers $ n, a, b $ . You need to find an adjacency matrix of such an undirected graph that the number of components in it is equal to $ a $ , and the number of components in its complement is $ b $ . The matrix must be symmetric, and all digits on the main diagonal must be zeroes.

In an undirected graph loops (edges from a vertex to itself) are not allowed. It can be at most one edge between a pair of vertices.

The adjacency matrix of an undirected graph is a square matrix of size $ n $ consisting only of "0" and "1", where $ n $ is the number of vertices of the graph and the $ i $ -th row and the $ i $ -th column correspond to the $ i $ -th vertex of the graph. The cell $ (i,j) $ of the adjacency matrix contains $ 1 $ if and only if the $ i $ -th and $ j $ -th vertices in the graph are connected by an edge.

A connected component is a set of vertices $ X $ such that for every two vertices from this set there exists at least one path in the graph connecting this pair of vertices, but adding any other vertex to $ X $ violates this rule.

The complement or inverse of a graph $ G $ is a graph $ H $ on the same vertices such that two distinct vertices of $ H $ are adjacent if and only if they are not adjacent in $ G $ .

## 样例 #1

### 输入

```
3 1 2
```

### 输出

```
YES
001
001
110
```

## 样例 #2

### 输入

```
3 3 3
```

### 输出

```
NO
```

# 题解

## 作者：zmxqs (赞：4)

# 题解：

目录
+ 补图的概念、性质

+ 关于本题的生成

+ Code

Step1：

概念：一个图和他的补图把边加起来是一张完全图

通俗来讲，就是把每个点与点之间的边异或 1 （有边变成无边，无边则变成有边）

性质：一个图与它的补图，一定存在这样的关系

令原图的连通块个数为 $a$，它的补图的连通块个数为 $b$

1°$a=1,b=1$

通过举例可以得出，原图必为一条链

但是要注意在点数为 2,3 时是不成立的

2° $a>1,b>1$

没有任何一张图能满足次条件

3°$a>1,b=1$

或

4°$a=1,b>1$

可以证明在这两种情况下一定存在这样的图

Step2：

这题是一道构造的图论题，在解决掉1、2种情况后我们来到第三、四种情况

如何生成这个图？

我们考虑把$1\rightarrow a-1$个点独立（没有任何的边与其相连），$a\rightarrow n$个点相互连边，组成一个连通块

第四种情况，与第三种情况类似，只要用第三种方法，最后把边取反即可

但是有一点要注意，自己到自己是没有路径滴

Step3：

Coding Time ~

如果理解后看着代码自然不难。我的代码把几个过程直接合并输出，所以常数非常的小，位居最优解第三名。

注意不要使用没开 ios 的 cin/cout，特别建议使用 putchar 并非 scanf

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n , a , b ;
int main() {
	scanf("%d%d%d",&n,&a,&b) ;
	if(a > 1 && b > 1) {
		printf("NO\n") ;
		return 0 ;
	}
	if(a == 1 && b == 1) {
		if(n == 2 || n == 3) {
			printf("NO\n") ;
			return 0 ;
		} else {
			printf("YES\n") ;
			for(int i=1; i<=n; ++i) {
				for(int j=1; j<=n; ++j) {
					if(i == j + 1 || i + 1 == j) {
						putchar('1') ;
					} else {
						putchar('0') ;
					}
				}
				putchar('\n') ;
			}
			return 0 ;
		}
	}
	else if(a > 1) {
		printf("YES\n") ;
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=n;++j) {
				if(i >= a && j >= a && (i == j + 1 || i + 1 == j)) {
					putchar('1') ;
				}
				else {
					putchar('0') ;
				}
			}
			putchar('\n') ;
		}
	}
	else if(b > 1) {
		printf("YES\n") ;
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=n;++j) {
				if(i == j) {
					putchar('0') ;
				}
				else if(i >= b && j >= b  && (i == j + 1 || i + 1 == j)) {
					putchar('0') ;
				}
				else {
					putchar('1') ;
				}
			}
			putchar('\n') ;
		}
	}
	return 0 ;
}
```

---

## 作者：lmy_2011 (赞：1)

### 算法思想
从此题面可直接看出，这题就是一个稍微有一些细节的图论
### 主体思路
首先我们知道图论的基本定论：任何一个图，不管分成多少块，经过题目中的操作后，必然变成一个联通图。

既然会相连，就说明题目中的 $a$ 和 $b$ 中，起码有 $1$ 个的数量是为 $1$ 的。

我们分 $3$ 类进行讨论：

- $b$ 为 $1$ 的情况，我们将图分成 $a$ 块，直接另前 $a-1$ 块都只有一个节点，最后 $1$ 块包含剩下的节点就行了。

- $a$ 为 $1$ 的情况，我们就把他当作 $b$ 为 $1$ 的情况，再将输出反过来即可。

- $a$ 与 $b$ 均为 $1$ 的情况，我们再特殊讨论。当 $n$ 为 $2$ 或 $3$ 时，就无法构造出图，输出 $\texttt{NO}$，否则输出 $\texttt{YES}$。


---

## 作者：ttq012 (赞：0)

考虑分类讨论。若 $a>1$ 且 $b>1$ 则显然无解。

若 $a=1$ 且 $b=1$ 则：

+ 若 $n\in\lbrace2,3\rbrace$ 则无解。
+ 否则有解，可以构造 $i\to i+1$ 这样一条链。

若 $a>1$ 且 $b=1$ 则令 $a=1$ 且 $b>1$ 讨论。考虑构造让前 $b-1$ 个点全都不连边，$b$ 到 $n$ 个点中任意两个点都相互连边。那么显然满足条件。

时间复杂度为 $O(n^2)$。

---

