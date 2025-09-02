# 最適二分探索木

## 题目描述

# 题描述
### 我想制作一个有 n叶的有序二叉树。该二叉树的成本定义如下。
![1](https://baiwhiter.github.io/images/FireShot%20Capture%20006%20-%20AT1358%20%E6%9C%80%E9%81%A9%E4%BA%8C%E5%88%86%E6%8E%A2%E7%B4%A2%E6%9C%A8%20-%20%E6%B4%9B%E8%B0%B7%20-%20%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%A7%91%E5%AD%A6%E6%95%99%E8%82%B2%E6%96%B0%E7%94%9F%E6%80%81%20-%20www.luogu.org.png)
------------
### 然而,depth(i),从在该二进制树的左表示第i片叶子的深度。W_i重量是作为输入给出的。请找到最低成本。

## 说明/提示

### 部分测试点
```
n ≦ 1 0 0 如果你回答的数据集满意， 50分给出。
n ≦ 3,000 n ≦ 3，0 0 0 如果您在回答数据集令人满意的，除了50分中给出。
如果在没有其他约束的情况下更正数据集，则与上述分开 有一点是给出。
```
# 输入样例
```
6
1 2 3 4 9 3
```
# 输出样例
```
53
```
### 下图中显示的二叉树是最佳的。
![2](https://cdn.luogu.org/upload/vjudge_pic/AT1358/bade4c459cea1a03aea22be87f432e68bb065698.png)
### 等效于样本输入和输出的二叉树
### 如果你制作这样的二叉树，那么成本是53。

# 题解

## 作者：sunkuangzheng (赞：5)

这题确实符合比赛名称 Atcoder Typical Contest，只不过我感觉这题更偏向 Technology /hsh

> - 这个问题和[石子合并问题](https://www.luogu.com.cn/problem/P5569)本质相同，为了方便我们以下讨论石子合并问题。
> - 为什么本质相同？石子合并问题中，合并两个相邻石子相当于本题给两个相邻节点连到一个父亲上。合并相邻石子会导致每个石子贡献次数 $+1$，对应在本题恰好是深度 $+1$。因此石子合并问题的答案即为本题的答案。

求解石子合并问题有两个经典算法：Garsia-Wachs 算法和 Hu-Tucker 算法。介绍前者的博客已经很多，这里我们主要介绍后者。

> **算法流程**
> - 算法执行 $n - 1$ 轮，每一轮合并两堆石子。
> - 每一轮选择第 $i,j$ 堆石子，满足 $i,j$ 间**不存在**一堆初始就存在的石子（即，不是由两堆石子合并而来的）。在此基础上，要求 $a_i + a_j$ 的值尽量小，如果有相同的，要求 $i$ 尽量小。
> - 删去 $a_i,a_j$，在 $i,j$ 中间的任意位置插入一堆石子 $a_i+a_j$。

比起 Garsia-Wachs 算法，该算法的贪心过程应该更容易感性理解；当然，严格证明其正确性可能同样困难。

容易发现暴力模拟上述流程的时间复杂度是 $\mathcal O(n^2)$。

考虑用数据结构优化上述过程。

我们对于每个合并过的石子的连通块，维护其最小和次小值。如果我们某一次合并取出了 $i$ 这堆石子：

- 如果 $i$ 是已合并过的，那么将其从连通块中删除即可。
- 否则，合并 $i$ 两端的连通块。

每次合并完成后，将 $a_i+a_j$ 加入连通块中。

对于合并操作完成后的一个连通块（最小次小值为 $x,y$），两边是 $a_i,a_j$，其可以产生的比较优的选法有 $a_i+a_j,a_i+x,a_j+x,x+y$。我们额外开一个堆维护这些选法即可。

支持加删元素，维护最小值的数据结构可以采用可并堆，维护连通块只需要维护每个连通块的左右端点。总时间复杂度即为 $\mathcal O(n \log n)$。

---

## 作者：DengDuck (赞：2)

一种基于 DFS 实现的 Garsia-Wachs 算法，是 $\mathcal O(n^2)$ 的，但是跑得飞快。

简单来说，在这种实现中，石子是依次在末尾加入的，由于这个算法的步骤是找最前面的一个 $a<c$ 然后合并，再插入到前面，所以知道一个前缀是可以先做着的。

那么每次在末尾加入的时候：

- 首先长度会尽量小，所以删除元素，插入元素会快一点。
- 其次能够合并的组数会尽量少，我们只需要跟踪插入的元素——这是前缀中唯一的变量，也是唯一有可能产生新的 $a<c$ 的地方，如果可以合并我们递归下去处理即可。

这是一种感性的理解方式，主要是 Garsia-Wachs 算法比较神秘我研究不会，据说可以证是 $\mathcal O(n\log n)$。 

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
#define LowBound lower_bound
#define UpBound upper_bound
//#define Fi first
//#define Se second
//#define Ls(x) (x<<1)
//#define Rs(x) (x<<1|1)
//#define Ls(x) t[x].Lson
//#define Rs(x) t[x].Rson
using namespace std;
//const LL Inf;
const LL N=2e5+5;
//const LL M;
//const LL Mod;
//const LF eps;
//const LL P;
LL TOT,Ans,n,A[N];
void Mrg(LL x)
{
	LL K=A[x]+A[x-1];
	Ans+=K;
	for(int i=x;i<TOT;i++)A[i]=A[i+1];
	LL j;
	for(j=x-1;A[j-1]<K&&j>1;j--)A[j]=A[j-1];
	A[j]=K;
	K=--TOT;
	while(j>2&&A[j-2]<=A[j])Mrg(j-1),j-=K-TOT;
}
int main()
{
	while(~scanf("%lld",&n))
	{
		if(n==0)return 0;
		TOT=Ans=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&A[i]);
			A[++TOT]=A[i];
			while(TOT>2&&A[TOT-2]<=A[TOT])Mrg(TOT-1);
		}
		while(TOT>1)Mrg(TOT);
		printf("%lld\n",Ans);
	}
	return 0;
}
//RP++
```

---

