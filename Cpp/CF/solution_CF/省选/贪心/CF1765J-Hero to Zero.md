# Hero to Zero

## 题目描述

There are no heroes in this problem. I guess we should have named it "To Zero".

You are given two arrays $ a $ and $ b $ , each of these arrays contains $ n $ non-negative integers.

Let $ c $ be a matrix of size $ n \times n $ such that $ c_{i,j} = |a_i - b_j| $ for every $ i \in [1, n] $ and every $ j \in [1, n] $ .

Your goal is to transform the matrix $ c $ so that it becomes the zero matrix, i. e. a matrix where every element is exactly $ 0 $ . In order to do so, you may perform the following operations any number of times, in any order:

- choose an integer $ i $ , then decrease $ c_{i,j} $ by $ 1 $ for every $ j \in [1, n] $ (i. e. decrease all elements in the $ i $ -th row by $ 1 $ ). In order to perform this operation, you pay $ 1 $ coin;
- choose an integer $ j $ , then decrease $ c_{i,j} $ by $ 1 $ for every $ i \in [1, n] $ (i. e. decrease all elements in the $ j $ -th column by $ 1 $ ). In order to perform this operation, you pay $ 1 $ coin;
- choose two integers $ i $ and $ j $ , then decrease $ c_{i,j} $ by $ 1 $ . In order to perform this operation, you pay $ 1 $ coin;
- choose an integer $ i $ , then increase $ c_{i,j} $ by $ 1 $ for every $ j \in [1, n] $ (i. e. increase all elements in the $ i $ -th row by $ 1 $ ). When you perform this operation, you receive $ 1 $ coin;
- choose an integer $ j $ , then increase $ c_{i,j} $ by $ 1 $ for every $ i \in [1, n] $ (i. e. increase all elements in the $ j $ -th column by $ 1 $ ). When you perform this operation, you receive $ 1 $ coin.

You have to calculate the minimum number of coins required to transform the matrix $ c $ into the zero matrix. Note that all elements of $ c $ should be equal to $ 0 $ simultaneously after the operations.

## 说明/提示

In the first example, the matrix looks as follows:

 111000111You can turn it into a zero matrix using $ 2 $ coins as follows:

- subtract $ 1 $ from the first row, paying $ 1 $ coin;
- subtract $ 1 $ from the third row, paying $ 1 $ coin.

In the second example, the matrix looks as follows:

 221001221You can turn it into a zero matrix using $ 5 $ coins as follows:

- subtract $ 1 $ from the first row, paying $ 1 $ coin;
- subtract $ 1 $ from the third row, paying $ 1 $ coin;
- subtract $ 1 $ from the third row, paying $ 1 $ coin;
- subtract $ 1 $ from $ a_{2,3} $ , paying $ 1 $ coin;
- add $ 1 $ to the third column, receiving $ 1 $ coin;
- subtract $ 1 $ from the first row, paying $ 1 $ coin;
- subtract $ 1 $ from $ a_{2,3} $ , paying $ 1 $ coin.

## 样例 #1

### 输入

```
3
1 2 3
2 2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 1 3
1 1 2```

### 输出

```
5```

## 样例 #3

### 输入

```
2
1 0
2 1```

### 输出

```
2```

## 样例 #4

### 输入

```
2
1 4
2 3```

### 输出

```
4```

## 样例 #5

### 输入

```
4
1 3 3 7
6 9 4 2```

### 输出

```
29```

# 题解

## 作者：周子衡 (赞：3)

注意到操作的顺序无关紧要。我们可以把所有行上的操作合并，变成给第 $i$ 行减去某个值 $x_i$，需要付出 $x_i$ 的代价；所有列上的操作合并，变成给第 $j$ 行减去某个值 $y_j$，需要付出 $y_j$ 的代价。需要满足

$$x_i+y_j\leq c_{i,j},\forall i,j\in[1,n]$$

需要付出的总代价为

$$\sum_{i=1}^nx_i+\sum_{j=1}^ny_j+\sum_{i=1}^n\sum_{j=1}^n(c_{i,j}-x_i-y_j)=(\sum c_{i,j})-(n-1)(\sum x_i+\sum y_j)$$

我们希望总代价尽可能小，也就是 $\sum x_i+\sum y_j$ 尽可能大。线性规划中的一个经典结论告诉我们，这个最大值是

$$\sum_{i=1}^nc_{i,p_i}$$

的最小值，其中 $(p_1,...,p_n)$ 取遍 $(1,...,n)$ 的所有排列。

由于 $c_{i,j}=|a_i-b_j|$，假设 $a,b$ 都是升序的，最小的一组排列显然就是 $p_i=i$。计算 $\sum c_{i,j}$ 也非常简单。总时间复杂度 $O(n\log n)$。

---

## 作者：SentoAyaka (赞：2)

考虑线性规划：
$$
\begin{aligned}
\min\ \ \ \sum_i H_i+\sum_j L_j+\sum_{i,j} &P_{i,j}\\
s.t.\ \ \ \ \ \ \forall i,j,H_i+L_j+P_{i,j}&=|a_i-b_j|\\
H_i,L_j\in R,P_{i,j}&\ge 0
\end{aligned}
$$
设约束对偶成变量 $y_{i,j}$，得到：
$$
\begin{aligned}
\max\ \sum_{i,j}|a_i-b_j|&\times y_{i,j}\\
s.t.\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ y_{i,j}&\le 1\\
\sum_i y_{i,j}&=1\\
\sum_j y_{i,j}&=1
\end{aligned}
$$
其中两个等式限制由无限制变量 $H_i,L_j$ 得到。

---

对于对偶后的线性规划，转成二分图，先将所有 $y_{i,j}$ 取到上界，即变成完全图。

对于等式限制就是每个点度数为 $1$，即对每个点删 $n-1$ **次** 边。

将 $a,b$ 排序后考虑二分图性质，显然 **若删去的边交叉一定不优** 。

于是我们将 $(i,i')$ 边删 $n-1$ 次即可。 

---

code：

```cpp
#include<bits/stdc++.h>
#define db double
#define int ll
#define ll long long
#define ull unsigned long long
#define pb emplace_back
#define MP make_pair
#define pii pair<int, int>
#define vec vector<int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define CLK (double)clock()/(double)CLOCKS_PER_SEC
using namespace std;
mt19937 rnd(time(0));
inline int read(){
    register int x=0,f=1;
    register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void write(register int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N=2e5+5;
int n,a[N],b[N],suma[N],sumb[N],ans;
void MAIN(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();sort(a+1,a+1+n);
    for(int i=1;i<=n;i++)b[i]=read();sort(b+1,b+1+n);
    for(int i=1;i<=n;i++)suma[i]=suma[i-1]+a[i],sumb[i]=sumb[i-1]+b[i];
    int j=0;
    for(int i=1;i<=n;i++){
        while(j<n&&b[j+1]<a[i])j++;
        ans+=a[i]*j-sumb[j]+(sumb[n]-sumb[j])-a[i]*(n-j);
    }
    for(int i=1;i<=n;i++)ans-=abs(a[i]-b[i])*(n-1);
    cout<<ans;
}
signed main(){
//    freopen("read.in","r",stdin);
//	freopen("write.out","w",stdout);
    int T=1;while(T--)MAIN();
//  printf("\nTIME:%lf\n",(double)clock()/CLOCKS_PER_SEC);
    return 0;
}
```


---

## 作者：Graphcity (赞：2)

来点更加暴力的线性规划做法。

设第 $i$ 行被减 $h_i$ 次，加 $H_i$ 次；第 $j$ 列被减 $l_j$ 次，被加 $L_j$ 次；位置 $(i,j)$ 被减 $w_{i,j}$ 次。列出线性规划的式子：

$$
\begin{aligned}
& \min\sum_i h_i-H_i+\sum_j l_j-L_j+\sum_{i,j}w_{i,j} \\
& \forall i,j\in [1,n],\  h_i-H_i+l_j-L_j+w_{i,j}=c_{i,j}
\end{aligned}
$$

将它对偶，设 $c_{i,j}$ 所在约束对偶后为 $p_{i,j}$：

$$
\begin{aligned}
& \min_{i,j}p_{i,j}c_{i,j}\\
& \sum_j p_{i,j}\ge -1, \ \sum_j-p_{i,j}\ge 1\\
& \sum_i p_{i,j}\ge -1,\ \sum_i -p_{i,j}\ge 1\\
& p_{i,j}\ge -1
\end{aligned}
$$

化简得到：

$$
\begin{aligned}
& \min_{i,j}p_{i,j} | a_i-b_j | \\
& \sum_j p_{i,j}=-1\\
& \sum_i p_{i,j}=-1\\
& p_{i,j}\ge -1
\end{aligned}
$$

我们先假设所有的 $p_{i,j}$ 均为下界 $-1$。那么此时所有行和所有列的和均为 $-n$，距离约束还差 $-(n-1)$。我们每次给 $p_{i,j}$ 增加一，就相当于连接上二分图中 $i\to j'$ 的一条权值为 $|a_i-b_j|$ 的边。我们要求二分图中每个点的度数均为 $n-1$，且权值之和最小。

注意到一个性质：将序列 $a$ 和 $b$ 从小往大排序之后，不可能出现两条边相交的情况。因为你把相交的两条边的右端点交换一下，显然不劣于原来的答案。

所以最终的匹配必然是 $a_i$ 和 $b_i$ 连接 $n-1$ 次。答案就很好算了。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,ans,a[Maxn+5],b[Maxn+5];

signed main()
{
    n=read();
    For(i,1,n) a[i]=read();
    For(i,1,n) b[i]=read();
    sort(a+1,a+n+1),sort(b+1,b+n+1);
    For(i,1,n) ans+=abs(a[i]-b[i])*(n-1);
    for(int i=1,it=0;i<=n;++i)
    {
        while(it<n && b[it+1]<=a[i]) it++;
        ans-=a[i]*(it-(n-it));
    }
    for(int i=1,it=0;i<=n;++i)
    {
        while(it<n && a[it+1]<b[i]) it++;
        ans-=b[i]*(it-(n-it));
    }
    cout<<-ans<<endl;
    return 0;
}
```

---

## 作者：Alex_Wei (赞：1)

操作顺序无关，因此设 $x_i$ 表示将第 $i$ 行所有数减去 $x_i$，$y_i$ 表示将第 $j$ 行所有数减去 $y_j$。

如果 $x = y = 0$，则代价为 $\sum c_{i, j}$，$x_i$ 或 $y_j$ 每增加 $1$，代价减小 $n - 1$，但 $x_i + y_j$ 不能超过 $c_{i, j}$。

因此，相当于找到一组 $x, y$，使得 $x_i + y_j \leq c_{i, j}$ 并最大化 $\sum x_i + y_i$。注意到这很像最大权完美匹配的 KM 算法中的顶标，不过不等号限制换了一个方向。这启发我们猜测 $\sum x_i + y_i$ 的最大值即 $i, j$ 之间连边 $c_{i, j}$ 的二分图的最小权完美匹配。

证明：最大不会超过最小权完美匹配是显然的，能达到该值则可借助 KM 算法证明。

综上，我们将问题转化为求 $\sum |a_i - b_{p_i}|$ 的最小值，其中 $p$ 是 $1\sim n$ 的排列。从小到大排序后对应匹配即可。初始 $\sum c_{i, j}$ 也容易求。

时间复杂度 $\mathcal{O}(n\log n)$，瓶颈在排序。[代码](https://codeforces.com/contest/1765/submission/185466990)。

---

