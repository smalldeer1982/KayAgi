# Two Permutations (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the two versions is that you do not have to minimize the number of operations in this version. You can make hacks only if both versions of the problem are solved.

You have two permutations $ ^{\dagger} $ $ p_{1}, p_{2}, \ldots, p_{n} $ (of integers $ 1 $ to $ n $ ) and $ q_{1}, q_{2}, \ldots, q_{m} $ (of integers $ 1 $ to $ m $ ). Initially $ p_{i}=a_{i} $ for $ i=1, 2, \ldots, n $ , and $ q_{j} = b_{j} $ for $ j = 1, 2, \ldots, m $ . You can apply the following operation on the permutations several (possibly, zero) times.

In one operation, $ p $ and $ q $ will change according to the following three steps:

- You choose integers $ i $ , $ j $ which satisfy $ 1 \le i \le n $ and $ 1 \le j \le m $ .
- Permutation $ p $ is partitioned into three parts using $ p_i $ as a pivot: the left part is formed by elements $ p_1, p_2, \ldots, p_{i-1} $ (this part may be empty), the middle part is the single element $ p_i $ , and the right part is $ p_{i+1}, p_{i+2}, \ldots, p_n $ (this part may be empty). To proceed, swap the left and the right parts of this partition. Formally, after this step, $ p $ will become $ p_{i+1}, p_{i+2}, \ldots, p_{n}, p_{i}, p_{1}, p_{2}, \ldots, p_{i-1} $ . The elements of the newly formed $ p $ will be reindexed starting from $ 1 $ .
- Perform the same transformation on $ q $ with index $ j $ . Formally, after this step, $ q $ will become $ q_{j+1}, q_{j+2}, \ldots, q_{m}, q_{j}, q_{1}, q_{2}, \ldots, q_{j-1} $ . The elements of the newly formed $ q $ will be reindexed starting from $ 1 $ .

Your goal is to simultaneously make $ p_{i}=i $ for $ i=1, 2, \ldots, n $ , and $ q_{j} = j $ for $ j = 1, 2, \ldots, m $ .

Find any valid way to achieve the goal using at most $ 10\,000 $ operations, or say that none exists. Please note that you do not have to minimize the number of operations.

It can be proved that if it is possible to achieve the goal, then there exists a way to do so using at most $ 10\,000 $ operations.

 $ ^{\dagger} $ A permutation of length $ k $ is an array consisting of $ k $ distinct integers from $ 1 $ to $ k $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ k=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first example, we can achieve the goal within $ 2 $ operations:

1. In the first operation, choose $ i = 3 $ , $ j = 4 $ . After this, $ p $ becomes $ [3, 2, 1] $ and $ q $ becomes $ [3, 4, 5, 2, 1] $ .
2. In the second operation, choose $ i = 2 $ , $ j = 4 $ . After this, $ p $ becomes $ [1, 2, 3] $ and $ q $ becomes $ [1, 2, 3, 4, 5] $ .

In the third example, it is impossible to achieve the goal.

## 样例 #1

### 输入

```
3 5
2 1 3
5 2 1 4 3```

### 输出

```
2
3 4
2 4```

## 样例 #2

### 输入

```
4 4
3 4 2 1
2 4 1 3```

### 输出

```
5
4 2
3 3
1 4
3 2
4 1```

## 样例 #3

### 输入

```
2 2
1 2
2 1```

### 输出

```
-1```

# 题解

## 作者：xkcdjerry (赞：12)

很有意思题，爱来自瓷器。

我们暂时先假装只有一个数组需要我们排序，分别把两个做出来之后再想办法让它们长度匹配即可。

发现一个操作会让整个数组中大部分数的位置改变，对于任何类型的排序都很不友好，考虑想办法降低改变的数量。  
这道题可以采用把若干个操作捆绑起来当一个更容易分析的大操作看待。又因为我们在排序，所以尽量往插入或者交换的方向思考。

令 $A,B,C$ 分别表示一个串，$1,2$ 表示单个数字，方括号表示本轮选中方括号内的数进行操作，则：  
$\text{A[1]B2C}$ -> $\text{B2C1A}$  
$\text{B[2]C1A}$ -> $\text{C1A2B}$  
$\text{C[1]A2B}$ -> $\text{A2B1C}$  

至此，我们使用三次操作，在不影响其他数位置的情况下交换了 1,2 的位置。

然后由于我们可以使用 $n-1$ 次交换使任何数组有序，我们就可以使用至多 $3n-3$ 次操作将长度为 $n$ 的数组排序。

---

解决了排序问题之后考虑下一个问题：如何将两个数组的排序序列调整至相同长度。

这里令第一个字符串需要的操作序列为 $N$，第二个字符串需要的操作序列为 $M$，不失一般性的，我们假设 $|N| \geqslant |M|$：  

若 $|N|-|M|$ 为偶数，则在 $M$ 末尾不断插入 $1,m$ 直到 $|N|=|M|$，显然不会影响字符串的有序性。  

若 $|N|-|M|$ 为奇数，则两者可以被调整为相等**当且仅当** $n,m$ 中至少一个为奇数：   
若 $n$ 为奇数，则在 $N$ 的最后插入 $n$ 个 $n$，否则若 $m$ 为奇数，在 $M$ 的末尾插入 $m$ 个 $m$。  
（$|N|-|M|$ 为奇数且 $n,m$ 均为偶数的情况不可行原因稍后证明）

算一下操作次数：排序一个数列最多需要 $\max(|N|,|M|) \leqslant 3 \max(n,m)-3$ 次操作，若 $|N|,|M|$ 奇偶性不同还最多需要花 $\max(n,m)$ 次操作调整。所以共计操作数 $\leqslant 4 \max(n,m) -3$，能够通过本题。

---

$|N|-|M|$ 为奇数且 $n,m$ 均为偶数的情况的不可行原因：

考虑对于一个长度为偶数 $n$ 的数组进行一次操作时逆序对数的变化。令 $A,B$ 为长度分别为 $a,b$ 的串，$c$ 为单个数字，则：

交换前数组为 $\text{AcB}$，逆序对数为：

$$Orig=\sum_{i \in A} \sum_{j \in B} [i>j] + \sum_{i \in A} [i>c] + \sum_{i \in B} [i<c]$$

交换后数组为 $\text{BcA}$，逆序对数为：

$$New=\sum_{i \in A} \sum_{j \in B} [i<j] + \sum_{i \in A} [i<c] + \sum_{i \in B} [i>c]$$

又因为数组是排列，故元素两两不同：

$$New=\sum_{i \in A} \sum_{j \in B} 1-[i>j] + \sum_{i \in A} 1-[i>c] + \sum_{i \in B} 1-[i<c]$$
$$New=(ab-\sum_{i \in A} \sum_{j \in B} [i>j])+(a-\sum_{i \in A} [i>c])+(b-\sum_{i \in B} [i<c])$$
$$New=ab+a+b-Orig$$

又因为 $a+1+b=n$，所以 $a,b$ 一奇一偶，即 $ab+a+b$ 为奇数。

由此，得出结论：长度为偶数的序列一次操作后逆序对数量**奇偶翻转**。

那么由于任意序列的逆序对数量均是确定的，显然对于任意的给定的长度为偶数的起始和终止序列，操作数的奇偶性也是确定的，无法通过任何方式进行调整。



---

略加修订的[赛时代码](https://codeforces.com/contest/1882/submission/225148992)：

```c++
#include <cstdio>
#define N 3010
#define M 10010
#define ll long long
int n,m,a[N],b[N];
int s1[M],t1,s2[M],t2;
void swap(int &x,int &y) {int t=x;x=y;y=t;}
int main()
{
    scanf("%d%d",&n,&m); t1=t2=0;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=m;i++) scanf("%d",b+i);
    //如果开一个反向索引数组复杂度可以降低到 O(n)
    //但是 n^2 能过就别搞复杂玩意了万一写挂了就好玩了
    for(int i=1;i<=n;i++)
    {
        if(a[i]==i) continue;
        for(int j=i;j<=n;j++) if(a[j]==i)
        {
            //根据上面给出的交换方式推算每次操作的数的位置
            //那么这段应该不难理解
            int l1=i-1,l2=j-i-1,l3=n-j;
            s1[t1++]=l1+1;
            s1[t1++]=l2+1;
            s1[t1++]=l3+1;
            swap(a[i],a[j]); //记得更新数组
            break;
        }
    }
    
    //比赛没时间模块化了直接复制粘贴的
    //平时还是建议封装个函数方便调试修改
    for(int i=1;i<=m;i++)
    {
        if(b[i]==i) continue;
        for(int j=i;j<=m;j++) if(b[j]==i)
        {
            int l1=i-1,l2=j-i-1,l3=m-j;
            s2[t2++]=l1+1;
            s2[t2++]=l2+1;
            s2[t2++]=l3+1;
            swap(b[i],b[j]);
            break;
        }
    }
    //调整奇偶性
    if(t1%2!=t2%2)
    {
        if(n&1) for(int i=1;i<=n;i++) s1[t1++]=n;
        else if(m&1) for(int i=1;i<=m;i++) s2[t2++]=m;
        else return puts("-1"),0;
    }
    //补足偶数差
    while(t1<t2) s1[t1++]=1,s1[t1++]=n;
    while(t2<t1) s2[t2++]=1,s2[t2++]=m;
    //输出
    printf("%d\n",t1);
    for(int i=0;i<t1;i++) printf("%d %d\n",s1[i],s2[i]);
}
```

---

## 作者：EuphoricStar (赞：2)

考虑若是对一个排列进行操作，怎么做。

我们维护一个排列上的值域连续段 $[l, r]$，满足 $a_{l + 1} = a_l + 1, a_{l + 2} = a_{l + 1} + 1$，以此类推。初始 $l = r = 1$。

那么我们每次可以选择往外扩充一位 $l$ 还是 $r$。以扩充 $l$ 为例，我们把 $[l, r]$ 通过操作一次 $l - 1$ 换到 $[1, r - l + 1]$，然后找到 $a_l - 1$ 的位置 $p$，操作 $p$ 即可。

这样对于一个排列的操作次数是 $2n$。

对于两个排列，我们可以分别得到它们的操作序列。

如果它们长度奇偶性相同，可以把短的一直补 $1, n$ 直到和长的长度相等。

如果它们长度奇偶性不同：

- 如果 $n, m$ 有一个为奇数，不妨设 $n$ 为奇数，那么把第一个排列的操作序列补 $1, 2, \ldots, n$ 即可。
- 否则无解。

可以通过找不变（变化）量（逆序对奇偶性）证明 $n$ 为偶数时操作序列长度奇偶性固定。

当排列从 $abc$ 变成 $cba$ 时，变化的只有 $a \to c$ 的贡献，$a \to b$ 的贡献和 $a \to c$ 的贡献。设原排列 $a \to c$ 的逆序对数为 $p_1$，$a \to b$ 的逆序对数为 $p_2$，$b \to c$ 的逆序对数为 $p_3$，$a$ 部分的长度为 $k$。那么 $c$ 部分的长度为 $n - 1 - k$。

那么 $abc \to cba$ 造成的逆序对变化为 $k (n - 1 - k) - 2 p_1 + k - 2 p_2 + n - 1 - k - 2 p_3 = k (n - 1 - k) + n - 1 - 2 (p_1 + p_2 + p_3)$。容易发现这个变化为奇数，所以每一次操作，逆序对奇偶性都会变化。

[code](https://codeforces.com/contest/1882/submission/226248838)

---

## 作者：Milmon (赞：1)

## Easy Version

Easy Version 只需构造任意一种合法方案即可。

容易想到把两个排列分开考虑。

### 方案 1

对于一个排列，考虑每次让 $i+1$ 接在 $i$ 的后面：

- 若 $i$ 不在最后一个位置上，就对其后面的那个位置操作，此时 $i$ 一定在最后一个位置上；
- 对 $i+1$ 操作，此时 $i$ 被移动到 $i+1$ 前面，且 $1\sim i$ 总是有序排列。

此时我们发现对任意一个长度为 $n$ 的排列都可以在 $2n$ 次操作内做到符合题目要求。

### 方案 2

考虑对任意排列中两个不同的数 $x$ 和 $y$，考虑依次对 $x,\ y,\ x$ 操作，

$$
AxByC\to ByCxA\to CxAyB\to AyBxC
$$

就交换了这两个数。

而 $1\sim n$ 的排列可以通过类似冒泡排序的过程在 $n$ 次交换内完成排序，故至多用 $3n$ 次操作。 

（个人认为方案 1 更容易想到，方案 2 则是 CodeForces 提供的解法。）

考虑怎么使得两个排列操作次数相同。容易想到添加一段操作序列使得排列不变。

- 先对第一个位置操作，此时第一个位置上的数移动到最后一个位置，再对最后一个位置操作，则排列恢复原状；
- 设排列长度为 $n$，就重复 $n$ 次对第一个数操作，排列也恢复原状。

所以只需在操作次数奇偶性相同时用第一种方案补齐；奇偶性不同时则先用第二种方案对长度为奇数的排列操作，使得奇偶性相同，再用第一种方案补齐。否则一定不能成功，证明见题解末。

此时至多再操作 $n$ 次。总共不超过 $3n$ 次（方案 2 则是 $4n$ 次）。

## Hard Version

考虑在序列开头加一个 $0$，再把数列放到环上（即 $0$ 代表序列的开始）：

![](https://hydro.ac/file/3309/CF1882E-pic1.svg)

考虑对一个数进行操作，则容易发现操作在环上等价于 $0$ 与这个数交换之后再进行旋转。

![](https://hydro.ac/file/3309/CF1882E-pic2.svg)

于是问题转化为，在序列 $[0,\ p_1,\ p_2,\ \cdots,\ p_n]$ 上每次将 $0$ 与另一个数交换，使得序列变为 $[0,\ 1,\ 2,\ \cdots,\ n],\ [n,\ 0,\ 1,\ 2,\ \cdots,\ n-1],\ [n-1,\ n,\ 0,\ 1,\ 2,\ \cdots,\ n-2],\ \cdots$ 之一。

此时容易联想到另一个模型：在一个排列上，要用交换使得排列升序，将每个位置指向位置上数应该在的位置，形成一个图，则交换次数至少是 $n$ 减去环的个数。

我们的目标是将这个模型运用到这个问题上。容易想到对每个环，设环的大小为 $x$：

- 若环包含 $0$，则需要 $x-1$ 步即可完成；
- 若环不包含 $0$，可以先将 $0$ 与环上的数交换，再用 $x-1$ 步交换完成环上的数的还原，最后将 $0$ 与交换出去的那个数交换即可。共需要 $x+1$ 步（对环大小 $\geq 2$ 的环而言）。

枚举序列操作的 $n$ 种可能结果，计算最优解即可。

而对于两个序列同时操作，只需求最优解时分别求出奇数步操作和偶数步操作的最优解，然后取奇数偶数中更优的即可（如果不理解，可以参考代码）。

时间复杂度 $\Theta(n^2)$。

注：文末的代码为了方便，先求出了交换的数值的序列而非位置，再进行转换。

## 证明

求证：长度为偶数的序列 $a_1,\ a_2,\ \cdots,\ a_n$ 在操作后的逆序对数量奇偶性总是改变。这将得出操作序列的长度的奇偶性是确定的。

设对下标 $x$ 进行操作，则：

- $1\sim x-1$ 和 $x+1\sim n$ 中的逆序对数量保持不变；
- $1\sim x-1$ 中的一个数和 $x+1\sim n$ 构成的逆序对的数量的奇偶性也保持不变，因为总数 $(x-1)\cdot(n-x)$ 一定是偶数；
- $1\sim x-1$ 或 $x+1\sim n$ 中的一个数与 $x$ 构成的逆序对数量的奇偶性会改变，因为总数 $n-1$ 一定是奇数。

综上，逆序对的数量总是改变。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=100000;

struct SolveResult{
    int minEven,minOdd;
    vector<int> even,odd;
};

vector<int> solveOperations(vector<int> v,vector<int> op){
    vector<int> res;
    for(int x :op){
        int id=0;
        while(v[id]!=x)id++;
        res.push_back(id+1);
        vector<int> newv;
        for(int i=id+1;i<v.size();i++)newv.push_back(v[i]);
        newv.push_back(v[id]);
        for(int i=0;i<id;i++)newv.push_back(v[i]);
        v=newv;
    }
    return res;
}

SolveResult solve(vector<int> v){
    SolveResult res; res.minEven=res.minOdd=INF;
    int n=v.size();
    vector<int> a;
    a.push_back(0);
    for(int i=0;i<n;i++)a.push_back(v[i]);
    for(int k=0;k<=n;k++){
        vector<int> op;
        bool vis[2501]={};
        int pos[2501]={};
        pos[0]=k;
        for(int i=1;i<=k;i++)pos[n-k+i]=i-1;
        for(int i=k+1;i<=n;i++)pos[i-k]=i;
        for(int i=0;i<=n;i++){
            if(vis[i])continue;
            vector<int> t;
            vis[i]=true,t.push_back(i);
            int p=pos[a[i]];
            while(p!=i)t.push_back(p),vis[p]=true,p=pos[a[p]];
            if(i==0){
                for(int j=t.size()-1;j>0;j--)
                    op.push_back(a[t[j]]);
            }
            else{
                if(t.size()==1)continue;
                for(int j=t.size()-1;j>=0;j--)
                    op.push_back(a[t[j]]);
                op.push_back(a[*(t.rbegin())]);
            }
        }
        if(op.size()%2==0&&op.size()<res.minEven){
            res.minEven=op.size();
            res.even=op;
        }
        if(op.size()%2==1&&op.size()<res.minOdd){
            res.minOdd=op.size();
            res.odd=op;
        }
    }
    if(res.minOdd<INF)res.odd=solveOperations(v,res.odd);
    if(res.minEven<INF)res.even=solveOperations(v,res.even);
    return res;
}

int main(){
    int n,m;
    vector<int> a,b;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int x; scanf("%d",&x);
        a.push_back(x);
    }
    for(int i=1;i<=m;i++){
        int x; scanf("%d",&x);
        b.push_back(x);
    }
    SolveResult A=solve(a),B=solve(b);
    vector<int> opA,opB; int step=INF;
    if(A.minEven<=INF&&B.minEven<=INF
        &&(step==INF||step>max(A.minEven,B.minEven)))
        step=max(A.minEven,B.minEven),opA=A.even,opB=B.even;
    if(A.minOdd<=INF&&B.minOdd<=INF
        &&(step==INF||step>max(A.minOdd,B.minOdd)))
        step=max(A.minOdd,B.minOdd),opA=A.odd,opB=B.odd;
    if(step==INF)return printf("-1\n"),0;
    while(opA.size()<opB.size())
        opA.push_back(1),opA.push_back(n);
    while(opA.size()>opB.size())
        opB.push_back(1),opB.push_back(m);
    printf("%d\n",step);
    for(int i=0;i<step;i++)
        printf("%d %d\n",opA[i],opB[i]);
    return 0;
}
```

---

## 作者：nullqtr_pwp (赞：1)

**upd：原代码被同机房大佬 hack，此版代码无锅。**

题目描述：[link](https://codeforces.com/contest/1882/problem/E1)

可爱构造题。但我赛时 D 没调出来，喜提 $-71$ 喵。

这种题目，单个序列都不好操作时，先考虑单个序列的方案。

考虑对于单个序列如何操作合法。

注意到我们可以在 $3$ 次操作交换任意两个数 $x,y$，具体操作方案为：

```AxByC``` $\rightarrow$ ```ByCxA``` $\rightarrow$ ```CxAyB ```$\rightarrow$ ```AyBxC```。

设 $A,B,C$ 段的长度分别为 $a,b,c$，那么我们执行操作的位置分别为 $a+1,b+1,c+1$。

通过这样的交换方案，我们最多可以在 $3n$ 次操作内把一个序列变为合法。具体的，我们第 $i$ 次要将 $i$ 位置变为合法，找到 $a_j=i$ 的位置 $j$，对 $i$ 与 $j$ 进行交换操作。**注意，$i=j$ 时不能进行此操作。**

将排列 $p,q$ 都变为合法后，设在排列 $p$ 上执行了 $k_1$ 次交换操作，$q$ 上执行了 $k_2$ 次交换操作。让最后执行的操作次数是 $k_3,k_4$，我们必须要让 $k_3=k_4$。

对于 $k_1\equiv k_2(\bmod\texttt{ }2)$ 的情况，我们可以在排列 $p$ 上进行交换 $(p_1,p_2)$ 操作偶数次，或者在排列 $q$ 上进行交换 $(q_1,q_2)$ 操作偶数次。这样我们可以将 $k_1,k_2$ 操作至相等。

对于 $k_1\not\equiv k_2(\bmod\texttt{ }2)$ 的情况，需要分类讨论。

若 $n$ 为奇数，可以在 $p$ 排列上进行 $n$ 次在 $1$ 位置的原操作。这样 $n$ 次操作后排列不改变，但是 $k_1$ 的奇偶性会与 $k_2$ 相同，再执行交换 $(q_1,q_2)$ 的操作偶数次即可。

若 $m$ 为奇数，同理。在 $q$ 排列上进行 $m$ 在 $1$ 位置的原操作。再执行交换 $(p_1,p_2)$ 的操作偶数次。

对于 $n,m$ 都为偶数的情况，考虑**逆序对数量的奇偶性。** 答案序列的逆序对数量是 $0$，但容易发现每次操作都会改变逆序对数量的奇偶性。所以需要操作偶数次才能回到答案序列。因此初始 $k_1,k_2$ 奇偶不同时，一定不会存在满足条件的方案。

[CF Submission](https://codeforces.com/contest/1882/submission/225731387)。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define mx3(a,b,c) ((a>b?a:b)>c?(a>b?a:b):c)
#define mn3(a,b,c) ((a<b?a:b)<c?(a<b?a:b):c)
#define infll 1e16
#define inf 1e9
#define pii pair<int,int>
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define wh(lzm) while(lzm--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
#define vi vector<int>
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int mod=998244353,maxn=3005;
int a[maxn],b[maxn],p[maxn],q[maxn],n,m;
vector<pii>ans;
vector<int>v1,v2;
void swapa(int i,int j){
	if(i>j) swap(i,j);
	int lena=i-1,lenb=j-i-1,lenc=n-j;
	v1.pb(lena+1);
	v1.pb(lenb+1);
	v1.pb(lenc+1);
	swap(a[i],a[j]);
}
void swapb(int i,int j){
	if(i>j) swap(i,j);
	int lena=i-1,lenb=j-i-1,lenc=m-j;
	v2.pb(lena+1);
	v2.pb(lenb+1);
	v2.pb(lenc+1);
	swap(b[i],b[j]);
}
signed main(){
	n=read(),m=read();
	F(i,1,n) a[i]=read(),p[a[i]]=i;
	F(i,1,m) b[i]=read(),q[b[i]]=i;
	F(i,1,n){
		F(j,1,n) p[a[j]]=j;
		//i<->p[i]
		if(i==p[i]) continue;
		swapa(i,p[i]);
	}
	F(i,1,m){
		F(j,1,m) q[b[j]]=j;
		//i<->q[i]
		if(i==q[i]) continue;
		swapb(i,q[i]); 
	}
	int sza=v1.size(),szb=v2.size();
	sza/=3;
	szb/=3;
	if((sza&1)!=(szb&1)){
		if(n&1) F(i,1,n) v1.pb(1);
		else if(m&1) F(i,1,m) v2.pb(1);
		else return puts("-1"),0;
	}
	sza=v1.size(),szb=v2.size();
	sza/=3;
	szb/=3;
	if(sza<szb) F(i,1,szb-sza) swapa(1,2); 
	else if(sza>szb) F(i,1,sza-szb) swapb(1,2); 
	sza=v1.size(),szb=v2.size();
	F(i,0,sza-1) if(v1[i]&&v2[i]) ans.eb(v1[i],v2[i]);
	printf("%d\n",(int)ans.size());
	for(pii i:ans) printf("%d %d\n",i.fi,i.se);
}
```


---

## 作者：_lfxxx_ (赞：0)

下文令 $op(i)$ 表示选择 $i$ 进行操作。

先做一个排列。

初始想法是假设 $1\sim i$ 已经归位，把 $i+1$ 归位。

发现 $op(pos_i)$ 一下的话不对，反了，那我们就改成 $i \sim n$，把 $i-1$ 归位。

这时 $op(pos_i)$ 再 $op(pos_i - 1)$ 就对了。

现在考虑两个排列。

首先如果奇偶性相同，我们可以对其中一个排列重复 $op(1)$，$op(n)$ 就行了。

如果奇偶性不同，这要求我们构造出一个方案使长度是奇数且不改变原排列。

一个可行的就是 $n$ 次 $op(1)$，但要求 $n$ 要求奇数。

如果这时候 $n,m$ 都是偶数，那么无解。

简单的证明是偶数时操作必然改变逆序对奇偶性，两个排列相同前提是逆序对奇偶性相同，那么操作奇数次就必然不相同了。

想清楚构建代码还是很好写，很好调的。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define i128 __int128
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
bool be;
constexpr int N = 2505;
int n, m, a[N], b[N], c[N];
vector<int>va, vb;
void ope(int x, int *a, int n, vector<int>&v)
{
	copy(a + 1, a + 1 + n, c + 1);
	int cnt = 0;
	for (int i = x + 1; i <= n; ++i) {
		a[++cnt] = c[i];
	}
	a[++cnt] = c[x];
	for (int i = 1; i <= x - 1; ++i) {
		a[++cnt] = c[i];
	}
	// cerr << x << '\n';
	// for (int i = 1; i <= n; ++i) {
	// 	cerr << a[i] << ' ';
	// } cerr << '\n';
	v.emplace_back(x);
}
int pos(int x, int *a, int n)
{
	for (int i = 1; i <= n; ++i) {
		if (a[i] == x) {
			return i;
		}
	}
	return -1;
}
void solve(int *a, int n, vector<int>&v)
{
	int pn = pos(n, a, n);
	if (pn > 1) {
		ope(pn - 1, a, n, v);
	}
	for (int i = n - 1; i >= 1; --i) {
		int p = pos(i, a, n);
		ope(p, a, n, v);
		p = pos(i, a, n);
		if (p > 1) ope(p - 1, a, n, v);
	}
}
bool en;
int main()
{
	cerr << (&be - &en) / 1024.0 / 1024 << " MB\n--------------------------------" << endl;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= m; ++i) cin >> b[i];
	solve(a, n, va), solve(b, m, vb);
	if (va.size() % 2 != vb.size() % 2 && n % 2 == 0 && m % 2 == 0) {
		cout << "-1\n";
	} else {
		if (va.size() % 2 != vb.size() % 2) {
			if (n % 2) {
				for (int i = 1; i <= n; ++i) va.emplace_back(1);
			} else {
				for (int i = 1; i <= m; ++i) vb.emplace_back(1);
			}
		}
		while (va.size() < vb.size()) va.emplace_back(1), va.emplace_back(n);
		while (vb.size() < va.size()) vb.emplace_back(1), vb.emplace_back(m);
		cout << va.size() << '\n';
		for (int i = 0; i < va.size(); ++i) {
			cout << va[i] << ' ' << vb[i] << '\n';
		}
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

提供一种较好理解的方法，但可能不是很严谨。

首先，需要意识到题目的操作可以等价于任意交换两个数字，这一点别的题解已经写过了。

然后考虑把两个操作序列弄的长度一样，显然，当两者奇偶性相同时，我们可以在短的那一边反复加入形如 ``(1,n)(1,n)...`` 的操作，从而调整答案。

但是两者奇偶性不同时也可能存在答案，我们还有一种操作，就是反复选择第一个位置，这样在选择了 $n$ 次后原序列不变。

那么现在假设操作序列长度为 $c_a,c_b$，且 $c_a$ 为奇数，$c_b$ 为偶数。那么我们要么把 $c_a$ 变成偶数，也就是说我们要加上 $n$ 个一，这要求 $n$ 为奇数，要么把 $c_b$ 变成奇数，这要求 $m$ 为奇数。

综上，我们需要 $n,m$ 中的任意一个为奇数，修改奇数的那个即可改变奇偶性，反之无解。

前面三次操作交换两个数字，至多交换 $3(n-1)$ 次，后面加入 $n$ 个一，至多变成 $4n-3<10000$，可以通过此题。

[示例代码。](https://codeforces.com/contest/1882/submission/244477082)

---

## 作者：spdarkle (赞：0)



赛时除unr无人过E2，85人过E1，过于可怕。

~~为什么我瞎猜的E1结论是对的啊，为什么我当时没有打完啊，为什么我当时打了但是打错了就觉得结论是错的啊！！！！！~~

翻译：给定排列 $a_1\sim a_n,b_1\sim b_m,1\le n,m\le 2500$。

你每次可以进行一个操作，选择正整数 $i,j$，将 $a_1\sim a_{i-1}$ 与 $a_{i+1}\sim a_n$ 整体交换，同时对 $b$ 是相同操作。

不需要保证 $i,j$ 两边不为空。

求一个在 $10000$ 次内将两个排列都有序的方案。

无解输出负一。

首先可以手玩一下，容易发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/h9jhi8n4.png)

我们可以在 $3$ 次操作内交换任意两个数。

那么我们就可以在 $3len$ 次操作内，将一个长为 $len$ 的排列排序。

接着以上想法不难实现，关键在于如何同时取到解。

设按照这个做法，得出解的次数为 $c_1,c_2$。

若 $(c_2-c_1)\bmod 2=0$，此时显然选择较小的那个，不断交替对 $1,len$ 进行操作即可。

若 $(c_2-c_1)\bmod 2=1$，此时注意到，对于一个有序的数组，若对第一个位置执行操作，等价于让数组做循环左移。那么连续进行 $len$ 次，也同样可以得到相同数组。

所以，若 $n,m$ 中存在奇数，可以选择连续进行 $len$ 次，然后化为上面一种情况。这时候最大方案数仍然为 $4\max(n,m)\le 10000$。

那如果不存在呢？无解吗？

**赛上没有想到如何证明无解**。但赛下可以证明了。

注意到此时根据两个长度均为偶数，$c_1,c_2$ 奇偶性不同，可以得到 $c_1+c_2$ 为奇数。

而注意到，我们每次进行一个操作，若长度为偶数，则逆序对的奇偶性会发生变化，证明可以考虑分类讨论（左边右边一奇一偶）。

对于操作位置 $i$，与它相关的逆序对变化量为 $n-1-\Delta$，$n-1$ 为奇数，故 $\Delta$ 与 $n-1-\Delta$ 奇偶性是不同的。而两边的各自逆序对从奇到奇，从偶到偶，奇偶性不变。

从而我们可以得到，**对于长度为偶数的序列，每一次操作，会引起逆序对数奇偶性的变化**。

此时我们倒着来，当二者逆序对数都减为 $0$ 后，对其再次变成零必然会经过偶数次操作，这样并不能改变操作次数的奇偶性。

由上可知证毕。

---

