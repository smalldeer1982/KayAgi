# 题目信息

# [ARC162C] Mex Game on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc162/tasks/arc162_c

頂点に $ 1 $ から $ N $ の番号がついた $ N $ 頂点の根付き木が与えられます。頂点 $ 1 $ が根であり、頂点 $ i\ (2\leq\ i\ \leq\ N) $ の親は $ P_i $ です。

根付き木の何個かの頂点には $ 0 $ 以上 $ N $ 以下の整数が書かれています。この情報は数列 $ A=(A_1,A_2,\ldots,A_N) $ で与えられ、$ A_i\ \neq\ -1 $ の場合頂点 $ i $ に整数 $ A_i $ が書かれており、$ A_i=-1 $ の場合頂点 $ i $ には整数が書かれていないことを意味しています。

Alice と Bob でゲームをします。Alice が先手で、全ての頂点に整数が書かれるまで以下の操作を交互に繰り返します。

- 整数が書かれていない頂点を $ 1 $ 個選び、 $ 0 $ 以上 $ N $ 以下の整数を書く。
 
操作終了後の各頂点 $ v $ に対して、 $ f(v) $ を「頂点 $ v $ の部分木に含まれるどの頂点（$ v $ 含む）にも書かれていないような最小の非負整数」と定めます。

$ f(v)\ =\ K $ を満たす頂点 $ v $ が存在する場合 Alice の勝利、そうでない場合 Bob の勝利となります。両者が最適な行動を行う場合、どちらが勝つか判定してください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^3 $
- $ 2\ \leq\ N\ \leq\ 10^3 $
- $ 0\ \leq\ K\ \leq\ N $
- $ 1\ \leq\ P_i\ <\ i\ (2\leq\ i\leq\ N) $
- $ -1\ \leq\ A_i\ \leq\ N\ (1\leq\ i\leq\ N) $
- 入力される数値は全て整数
- $ 1 $ つの入力に含まれるテストケースについて、$ N $ の総和は $ 2\times\ 10^3 $ 以下
 
### Sample Explanation 1

$ 1 $ 番目のテストケースについては、Alice が頂点 $ 2 $ に $ 0 $ を書き込むと、Bob の操作に依らず $ f(2)\ =\ 2 $ となります。そのため、Alice は勝つことができます。 $ 2 $ 番目のテストケースについては、Bob が上手く書き込む整数を選ぶことで、 $ f(v)\ =\ 4 $ なる頂点が存在しないようにできます。

## 样例 #1

### 输入

```
2

4 2

1 1 2

-1 -1 3 1

6 4

1 2 2 1 3

-1 -1 -1 -1 -1 -1```

### 输出

```
Alice

Bob```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一棵有 $N$ 个顶点的根树，顶点编号为 $1$ 到 $N$，根为顶点 $1$。对于每个顶点 $i\ (2\leq\ i\ \leq\ N)$，其父节点为 $P_i$。

树中的某些顶点上写有 $0$ 到 $N$ 之间的整数，这些信息通过数列 $A=(A_1,A_2,\ldots,A_N)$ 给出。如果 $A_i\ \neq\ -1$，表示顶点 $i$ 上写有整数 $A_i$；如果 $A_i=-1$，表示顶点 $i$ 上没有写整数。

Alice 和 Bob 进行游戏，Alice 先手。游戏进行到所有顶点都写有整数为止，双方轮流执行以下操作：

- 选择一个没有写整数的顶点，并在其上写一个 $0$ 到 $N$ 之间的整数。

游戏结束后，对于每个顶点 $v$，定义 $f(v)$ 为“顶点 $v$ 的子树中所有顶点（包括 $v$）上没有出现过的最小非负整数”。如果存在某个顶点 $v$ 满足 $f(v)\ =\ K$，则 Alice 获胜；否则 Bob 获胜。双方都采取最优策略，判断谁会获胜。

给定 $T$ 个测试用例，分别输出每个测试用例的结果。

#### 说明/提示

##### 约束

- $1\ \leq\ T\ \leq\ 10^3$
- $2\ \leq\ N\ \leq\ 10^3$
- $0\ \leq\ K\ \leq\ N$
- $1\ \leq\ P_i\ <\ i\ (2\leq\ i\leq\ N)$
- $-1\ \leq\ A_i\ \leq\ N\ (1\leq\ i\leq\ N)$
- 输入中的所有数均为整数
- 单个输入文件中所有测试用例的 $N$ 总和不超过 $2\times\ 10^3$

##### 样例解释

第一个测试用例中，Alice 可以在顶点 $2$ 上写 $0$，这样无论 Bob 如何操作，$f(2)\ =\ 2$，因此 Alice 获胜。第二个测试用例中，Bob 可以通过合理选择写入的整数，使得不存在 $f(v)\ =\ 4$ 的顶点，因此 Bob 获胜。

#### 样例 #1

##### 输入

```
2

4 2

1 1 2

-1 -1 3 1

6 4

1 2 2 1 3

-1 -1 -1 -1 -1 -1```

##### 输出

```
Alice

Bob```

### 题解分析与结论

#### 题解对比

1. **作者：_•́へ•́╬_**  
   - **思路**：判断是否存在子树已经填满且 $\operatorname{mex}$ 为 $K$，或者子树只剩一个空位且填数后 $\operatorname{mex}$ 为 $K$。其他情况 Bob 胜。
   - **难点**：理解 Bob 的最优策略是填 $K$，从而破坏 Alice 的胜利条件。
   - **评分**：4星  
   - **亮点**：简洁明了地提出了 Alice 获胜的条件，并指出 Bob 的最优策略是填 $K$。

2. **作者：Lucky_Xiang**  
   - **思路**：将问题转化为 Alice 和 Bob 在可能的获胜子树上进行操作，判断是否存在子树的空位数量不超过 1。
   - **难点**：将问题转化为更简单的博弈模型，并分析了 Alice 和 Bob 的操作策略。
   - **评分**：4星  
   - **亮点**：通过转化问题，简化了判断条件，并提出了暴力枚举的解法。

3. **作者：WhisperingWillow**  
   - **思路**：Bob 的最优策略是不断填 $K$，Alice 必须在一次操作内完成，否则会被 Bob 破坏。
   - **难点**：理解 Bob 的最优策略，并分析 Alice 的操作限制。
   - **评分**：4星  
   - **亮点**：明确指出 Bob 的最优策略，并简化了 Alice 的获胜条件。

#### 最优关键思路

- **Bob 的最优策略**：Bob 应尽可能在子树中填 $K$，从而破坏 Alice 的胜利条件。
- **Alice 的获胜条件**：Alice 必须在一次操作内使某个子树的 $\operatorname{mex}$ 为 $K$，或者子树已经满足 $\operatorname{mex}$ 为 $K$。

#### 代码实现

```cpp
#include<stdio.h>
#include<bitset>
#define N 1009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	bool t=0;char c=nc();for(;c<'0'||'9'<c;t|=c=='-',c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());if(t)x=-x;
}
int t,n,m,f[N],x[N],cnt[N];bitset<N>a[N];
struct __readt__{inline __readt__(){read(t);}}_readt___;
main()
{
	read(n);read(m);for(int i=1;i<n;++i)read(f[i]),--f[i];
	for(int i=0;i<n;read(x[i++]));
	for(int i=0;i<n;cnt[i]=0,a[i++].set());
	for(int i=n-1;i>=0;--i)
	{
		if(~x[i])a[i][x[i]]=0;
		else++cnt[i];
		if(!cnt[i])if(a[i]._Find_first()==m){printf("Alice\n");goto nxt;}
		if(cnt[i]==1)if(a[i]._Find_first()==m||
			a[i]._Find_next(a[i]._Find_first())==m){printf("Alice\n");goto nxt;}
		if(i)a[f[i]]&=a[i],cnt[f[i]]+=cnt[i];
	}
	printf("Bob\n");
	nxt:if(--t)main();
}
```

#### 可拓展之处

- **类似题目**：可以考虑其他与 $\operatorname{mex}$ 相关的博弈问题，或者树上的博弈问题。
- **算法优化**：对于更大的 $N$，可以考虑使用更高效的数据结构来维护子树信息。

#### 推荐题目

1. [P3174 [HAOI2009]毛毛虫](https://www.luogu.com.cn/problem/P3174)
2. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)
3. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

---
处理用时：51.89秒