# [GCJ 2019 #2] New Elements: Part 1

## 题目描述

**本题的前两段（不包括本段）与“New Elements: Part 2”完全相同。除此之外，这两道题可以独立解决；你无需阅读或解决其中一道即可理解或解决另一道。**

Muriel 正在探索两种新元素，并将它们命名为 Codium 和 Jamarium。她尚未能够分离出这两种元素，但她希望通过间接方法研究它们的一些重要性质，比如它们的原子量。由于 Muriel 只研究 Codium 和 Jamarium 的单一同位素，因此它们的原子量都是严格正整数。

Muriel 成功合成了 $\mathbf{N}$ 种不同的分子，每种分子都只包含一种或多种 Codium 原子和一种或多种 Jamarium 原子，不含其他元素。对于每种分子，她都知道其中包含的每种元素的原子数。分子的分子量等于其所含所有原子的原子量之和。

为了进一步确定分子的精确分子量以及两种元素的原子量，Muriel 首先希望将这些分子按分子量严格递增的顺序排序。为了评估这个任务的难度，她想知道在当前信息下，有多少种排序方式是有效的。一个分子的排序被认为是有效的，当且仅当存在 Codium 和 Jamarium 的原子量的取值，使得该排序下分子的分子量严格递增。

举个例子，我们用每个分子中 Codium 和 Jamarium 原子的数量对其进行表示。如果 Muriel 有 3 个分子，分别为 $(1, 1)$、$(2, 1)$ 和 $(1, 2)$，则有两种可能的排序可以使分子量严格递增：$(1, 1)$、$(1, 2)$、$(2, 1)$ 和 $(1, 1)$、$(2, 1)$、$(1, 2)$。第一种排序在 Codium 比 Jamarium 重时成立，第二种排序在 Jamarium 比 Codium 重时成立。剩下的唯一情况是 Codium 和 Jamarium 的原子量相等，此时 $(1, 2)$ 和 $(2, 1)$ 的分子量相等，因此无法得到严格递增的排序。

## 说明/提示

**样例解释**

样例 1 已在题目描述中解释。

在样例 2 中，两种有效的排序分别为 $(1, 2)$、$(2, 1)$、$(2, 4)$、$(4, 2)$ 和 $(2, 1)$、$(1, 2)$、$(4, 2)$、$(2, 4)$。注意，排序 $(1, 2)$、$(2, 1)$、$(2, 4)$、$(4, 2)$、$(2, 4)$ 是无效的，因为如果 $(1, 2)$ 的分子量严格小于 $(2, 1)$，那么 $(2, 4)$（正好是 $(1, 2)$ 的两倍）也必须严格小于 $(4, 2)$（正好是 $(2, 1)$ 的两倍）。

**数据范围**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- $1 \leqslant \mathbf{C_i} \leqslant 10^9$，对所有 $i$。
- $1 \leqslant \mathbf{J_i} \leqslant 10^9$，对所有 $i$。
- 对于所有 $i \neq j$，$(\mathbf{C_i}, \mathbf{J_i}) \neq (\mathbf{C_j}, \mathbf{J_j})$（所有分子都不同）。

**测试点 1（8 分，可见）**

- $2 \leqslant \mathbf{N} \leqslant 6$。

**测试点 2（14 分，隐藏）**

- $2 \leqslant \mathbf{N} \leqslant 300$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
3
1 1
1 2
2 1
4
1 2
2 4
2 1
4 2
3
1 2
1 3
2 3```

### 输出

```
Case #1: 2
Case #2: 2
Case #3: 1```

# 题解

## 作者：shunshun111029 (赞：3)

## 题意
有 $N$ 个不同的分子，每种分子包含两种原子（一个或多个），每个分子的分子量就是这个分子的原子量之和，一个有效的分子的排序当且仅当存在两种的原子量的取值，使得该排序下分子的分子量严格递增。已知每种分子中两种原子的数量，求有效的排序的个数。   
## 分析
设 $C_i$ 表示第 $i$ 个分子中第一种分子的数量，$J_i$ 表示第二种分子的数量，$W_i$ 表示第 $i$ 个分子的分子量。已知第一种分子的分子量为 $C$，第二种分子的分子量为 $J$。那么分子量可以表示为：
$$
W_i=C_i\times C+J_i\times J
$$
设比例 $q=\dfrac{C}{J}$，则分子量可以改写为：
$$
W_i=J\times(J_i\times q+C_i)
$$
由于 $J$ 是一个正的常数，不影响分子之间的相对顺序，因此我们只需要考虑 $J_i\times q+C_i$ 的部分。对于两个分子 $i$ 和 $j$，当它们的分子量相等时，有：
$$
W_i=W_j\implies J_i\times q+C_i=J_j\times q+C_j
$$
整理得到：
$$
(J_i-J_j)q=C_j-C_i
$$
解得：
$$
q=\dfrac{C_j-C_i}{J_i-J_j}
$$
这里 $q$ 必须为正数（因为 $C>0$ 且 $J>0$）。因此，所有满足 $\dfrac{C_j-C_i}{J_i-J_j}>0$ 的 $q$ 值将构成分子量顺序变化的临界点。这些临界点将正实数轴 $q>0$ 分割成若干区间，每个区间内分子的排列顺序是固定的。
设这些不同的正临界点共有 $\text{ans}$ 个，那么分子的排列顺序在这些临界点之间保持不变，因此总的不同的有效排列数为：
$$
\text{ans}+1
$$
**注意**：所有考虑的临界点 $q$ 必须为正数。
## 实现
考虑枚举 $i$ 和 $j$，通过一个 set 来记录边界（可能是分数），时间复杂度为 $O(Tn^2\log^2n)$。   
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=305;
int T,n,id;
struct node{
	int d,k,s;
}a[N];
set<pair<int,int>>vis;
void work(){
	vis.clear();
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i].d>>a[i].k;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<i;++j){
			int z=a[i].d-a[j].d;
			int m=a[j].k-a[i].k;
			if(!m) continue;
			if(z*1.0/m*1.0<=0) continue;
			int g=__gcd(z,m);
			z=abs(z/g),m=abs(m/g);
			vis.insert(make_pair(z,m));
		}
	}
	cout<<"Case #"<<++id<<":"<<" ";
	cout<<vis.size()+1<<"\n";
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) work();
	return 0;
}
```
记得注意除数不为零。

---

## 作者：yanrs1019 (赞：2)

# 题解：P13115 [GCJ 2019 #2] New Elements: Part 1  
## 分析问题  
设 Codium 原子重 $x$，Jamarium 重 $y$。  
当两个分子 $i$ 和 $j$，分子 $i$ 排在分子 $j$ 前，当且仅当 $C_i\times x+J_i\times y<C_j\times x+J_j\times y$。  
整理得 $(C_i-C_j)\times x<(J_i-J_j)\times y$。  

为了方便观察，我们称 $dC=C_i-C_j,dJ=J_i-J_j$。    

进行分类讨论： 
- $dC=0$，条件变为 $dJ>0$；
- $dJ=0$，条件变为 $dC<0$；
- $dC>0,dJ>0$，条件变为 $\frac{x}{y}<\frac{dC}{dJ}$；
- $dC<0,dJ<0$，条件变为 $\frac{x}{y}>\frac{\vert dC\vert}{\vert dJ\vert}$；
- $dC>0,dJ<0$，不等式不成立；
- $dC<0,dJ>0$，不等式恒成立。  

注意到 $dC$ 与 $dJ$ 同号时，我们有一个重要的比值 $\frac{\vert dC\vert}{\vert dJ\vert}$，我们称其为 $k$。  
$k$ 将 $x$ 正半轴分割成若干个区域。在每个区域里，所有分子对的相对顺序固定。  
不同的比值 $k$ 的数量为 $m$ 时，有序排序数量为 $m+1$。  

## 实现方法  
1. 枚举分子对 $(i,j)(i<j)$，计算 $dC,dJ$；
2. 如果 $dC,dJ$ 同号，计算比值 $k$，并化为最简形式；
3. 使用 set 对比值 $k$ 去重；
4. 设集合大小 $s$，答案为 $s+1$。

## ACcode  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define N 305
set<pair<LL,LL> >st;
struct node{
	LL x,y;
}a[N];
void init(){
	st.clear();
}
void solve(){
	init();
	LL n;
	scanf("%lld",&n);
	for(LL i=1;i<=n;i++)scanf("%lld%lld",&a[i].x,&a[i].y);
	for(LL i=1;i<=n;i++){
		for(LL j=1;j<i;j++){
			LL fenzi=a[i].x-a[j].x;
			LL fenmu=a[j].y-a[i].y;
			if(fenmu==0||fenzi*1.0/fenmu<=0)continue;
			LL temp=__gcd(fenzi,fenmu);
			fenzi/=temp;
			fenmu/=temp;
			fenzi=abs(fenzi);
			fenmu=abs(fenmu);
			st.insert({fenzi,fenmu});
		}
	}
}
int main(){
	LL T;
	scanf("%lld",&T);
	for(LL i=1;i<=T;i++){
		solve();
		printf("Case #%lld: %lld\n",i,st.size()+1);
	}
	return 0;
}
```

---

