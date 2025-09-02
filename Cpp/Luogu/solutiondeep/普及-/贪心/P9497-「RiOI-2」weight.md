# 题目信息

# 「RiOI-2」weight

## 题目背景

在小树林间坐落着一个幻想的城堡。这里是 E 国的领地，而小 E，则是 E 国之王。

树木，是 E 国抵挡袭击的法宝。树木越高，越能蒙蔽敌人的视线。

可是，随着自然条件的退化，小 E 却不知怎么处理。怎么办呢？

## 题目描述

给定一个 $n$ 行 $n$ 列 的矩阵 $a$。

有 $q$ 组询问，每次给定一个 $v$，请将矩阵每一行任意重排（可以不重排），最大化**最大值不小于** $v$（也就是说，至少有一个不小于 $v$ 的数）的列数。请输出这个列数。

询问之间相互独立。换言之，每次询问前可以重新排列。


## 说明/提示

### 样例解释

原矩阵为 $\begin{bmatrix}9&9&8\\2&4&4\\3&5&3\end{bmatrix}$。

对于第一次询问，每一列的最大值 $9,9,8$ 均不小于 $v=5$，所以每一列都符合条件，答案为 $3$。显然无论怎么重排都不可能超过 $3$ 列（因为总共只有 $3$ 列），所以答案为 $3$。

### 数据规模与约定

**本题开启捆绑测试。**

| $\text{Subtask}$ | 分值 | $n \leq$ | $q \leq$ |
| :--------------: | :--: | :------: | :------: |
| $0$ | $10$ | $3$ | $10$ |
| $1$ | $40$ | $100$ | $10^3$ |
| $2$ | $50$ | $10^3$ | $5\times 10^5$ |

对于所有数据，$1 \leq n \leq 10^3$，$1 \leq q \leq 5\times 10^5$，$1 \leq a_{i,j}, v \leq 10^9$。

## 样例 #1

### 输入

```
3 3
9 9 8
2 4 4
3 5 3
5
9
10```

### 输出

```
3
2
0```

# AI分析结果



### 题解综合分析结论
本题核心在于统计矩阵中不小于给定值v的元素个数k，并取k与n的较小值。正确解法需将矩阵元素排序后利用二分法快速查询，时间复杂度为O(n² log n + q log n)。

---

### 精选题解及核心代码

#### 1. 作者：251Sec（5星）
**关键亮点**：思路简洁，直接使用STL的`lower_bound`，代码高效清晰。
```cpp
#include <bits/stdc++.h>
using namespace std;
int w[1000005], n, q;

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n * n; i++) scanf("%d", w + i);
    sort(w + 1, w + n * n + 1);
    while (q--) {
        int x;
        scanf("%d", &x);
        int pos = lower_bound(w + 1, w + n * n + 1, x) - w;
        printf("%d\n", min(n, n * n - pos + 1));
    }
    return 0;
}
```

#### 2. 作者：Aegleseeker_（5星）
**关键亮点**：代码规范，使用快速IO优化，处理边界情况明确。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,q,a[N*N];

int main(){
    scanf("%d%d",&n,&q);
    for(int i=0;i<n*n;i++) scanf("%d",&a[i]);
    sort(a,a+n*n);
    while(q--){
        int v; scanf("%d",&v);
        int p = lower_bound(a,a+n*n,v) - a;
        printf("%d\n", (p == n*n) ? 0 : min(n, n*n - p));
    }
    return 0;
}
```

#### 3. 作者：include13_fAKe（4星）
**关键亮点**：预处理优化，优先检查最大值区域，减少二分范围。
```cpp
void solve(int v){
    int l = n*(n-1)+1, r = n*n;
    if (v <= a[l]) { printf("%d\n",n); return; }
    if (v > a[r]) { printf("0\n"); return; }
    int mid = (l + r) >> 1;
    while (l < r) {
        if (v <= a[mid]) r = mid;
        else l = mid + 1;
        mid = (l + r) >> 1;
    }
    printf("%d\n", n*n + 1 - l);
}
```

---

### 关键思路总结
1. **降维处理**：将矩阵展平为一维数组，避免二维操作。
2. **排序预处理**：通过排序将问题转化为可二分查找的结构。
3. **二分加速**：利用`lower_bound`快速定位阈值位置，计算有效元素数量。
4. **贪心决策**：每列最多一个有效元素，答案由总数与n的较小值决定。

---

### 相似题目推荐
1. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（二分答案）
2. [P2440 木材加工](https://www.luogu.com.cn/problem/P2440)（二分应用）
3. [P1182 数列分段](https://www.luogu.com.cn/problem/P1182)（贪心+二分）

---
处理用时：183.43秒