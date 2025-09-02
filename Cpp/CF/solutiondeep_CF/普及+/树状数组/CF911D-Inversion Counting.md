# 题目信息

# Inversion Counting

## 题目描述

A permutation of size $ n $ is an array of size $ n $ such that each integer from $ 1 $ to $ n $ occurs exactly once in this array. An inversion in a permutation $ p $ is a pair of indices $ (i,j) $ such that $ i>j $ and $ a_{i}<a_{j} $ . For example, a permutation $ [4,1,3,2] $ contains $ 4 $ inversions: $ (2,1) $ , $ (3,1) $ , $ (4,1) $ , $ (4,3) $ .

You are given a permutation $ a $ of size $ n $ and $ m $ queries to it. Each query is represented by two indices $ l $ and $ r $ denoting that you have to reverse the segment $ [l,r] $ of the permutation. For example, if $ a=[1,2,3,4] $ and a query $ l=2 $ , $ r=4 $ is applied, then the resulting permutation is $ [1,4,3,2] $ .

After each query you have to determine whether the number of inversions is odd or even.

## 说明/提示

The first example:

1. after the first query $ a=[2,1,3] $ , inversion: $ (2,1) $ ;
2. after the second query $ a=[2,3,1] $ , inversions: $ (3,1) $ , $ (3,2) $ .

The second example:

1. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
2. $ a=[3,4,2,1] $ , inversions: $ (3,1) $ , $ (4,1) $ , $ (3,2) $ , $ (4,2) $ , $ (4,3) $ ;
3. $ a=[1,2,4,3] $ , inversion: $ (4,3) $ ;
4. $ a=[1,4,2,3] $ , inversions: $ (3,2) $ , $ (4,2) $ .

## 样例 #1

### 输入

```
3
1 2 3
2
1 2
2 3
```

### 输出

```
odd
even
```

## 样例 #2

### 输入

```
4
1 2 4 3
4
1 1
1 4
1 4
2 3
```

### 输出

```
odd
odd
odd
even
```

# AI分析结果

### 题目翻译
# 逆序对计数

## 题目描述
一个长度为 $n$ 的排列是一个长度为 $n$ 的数组，使得从 $1$ 到 $n$ 的每个整数在这个数组中恰好出现一次。排列 $p$ 中的一个逆序对是一对索引 $(i, j)$，满足 $i > j$ 且 $a_{i} < a_{j}$。例如，排列 $[4, 1, 3, 2]$ 包含 $4$ 个逆序对：$(2, 1)$，$(3, 1)$，$(4, 1)$，$(4, 3)$。

给定一个长度为 $n$ 的排列 $a$ 以及对它的 $m$ 次查询。每次查询由两个索引 $l$ 和 $r$ 表示，意味着你需要将排列中 $[l, r]$ 区间的元素反转。例如，如果 $a = [1, 2, 3, 4]$，执行查询 $l = 2$，$r = 4$ 后，得到的排列是 $[1, 4, 3, 2]$。

每次查询后，你需要确定逆序对的数量是奇数还是偶数。

## 说明/提示
第一个样例：
1. 第一次查询后 $a = [2, 1, 3]$，逆序对：$(2, 1)$；
2. 第二次查询后 $a = [2, 3, 1]$，逆序对：$(3, 1)$，$(3, 2)$。

第二个样例：
1. $a = [1, 2, 4, 3]$，逆序对：$(4, 3)$；
2. $a = [3, 4, 2, 1]$，逆序对：$(3, 1)$，$(4, 1)$，$(3, 2)$，$(4, 2)$，$(4, 3)$；
3. $a = [1, 2, 4, 3]$，逆序对：$(4, 3)$；
4. $a = [1, 4, 2, 3]$，逆序对：$(3, 2)$，$(4, 2)$。

## 样例 #1
### 输入
```
3
1 2 3
2
1 2
2 3
```
### 输出
```
odd
even
```

## 样例 #2
### 输入
```
4
1 2 4 3
4
1 1
1 4
1 4
2 3
```
### 输出
```
odd
odd
odd
even
```

### 综合分析与结论
这些题解的核心思路都是先求出初始序列的逆序对数量的奇偶性，再根据每次翻转区间内数对数量的奇偶性来判断整个序列逆序对数量奇偶性是否改变。具体实现上，对于初始逆序对数量的计算，有的采用暴力法，有的采用归并排序或树状数组；对于判断翻转后逆序对奇偶性的变化，都利用了翻转区间内数对数量的奇偶性这一关键性质。

### 所选题解
- **Muruski（4星）**
    - **关键亮点**：思路清晰，代码中有详细解释，虽然使用暴力法求初始逆序对数量，但能通过本题。
    - **个人心得**：提到数据范围大，直接暴力会超时，尝试多种方法后找到合适思路。
- **Arghariza（4星）**
    - **关键亮点**：给出逆序对性质的证明，使用归并排序求初始逆序对数量，复杂度更优。
- **⚡current⚡（4星）**
    - **关键亮点**：详细分析了逆序对与顺序对的关系，使用树状数组求初始逆序对数量，代码实现完整。

### 重点代码
#### Muruski的代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
int n,m;
int lenth,part;
int l,r;
int f;
int a[1550];
int main()
{
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        scanf("%d",&m);
        lenth=0;
        for(int i=1;i<n;i++)
            for(int j=i+1;j<=n;j++)
                if(a[i]>a[j]) lenth++;//暴力求这个区间的逆序对数量
        if(lenth%2==0) f=1;
        else f=0;
        while(m--)
        {
            scanf("%d%d",&l,&r);
            part=r-l+1;
            if((part*(part-1)/2)%2==1)
                f=!f;
            if(f)
                printf("even\n");
            else
                printf("odd\n");
        }
    }
    return 0;
}
```
**核心实现思想**：先暴力计算初始序列的逆序对数量，得到其奇偶性。对于每次查询，计算翻转区间的长度，根据区间内数对数量的奇偶性判断逆序对奇偶性是否改变。

#### Arghariza的代码
```cpp
int mergesort(int l, int r, int s[], int q[]) {// 归并排序求逆序对
    int res = 0;
    if (l == r) return 0;
    int mid = (l + r) >> 1;
    res += mergesort(l, mid, s, q);
    res += mergesort(mid + 1, r, s, q);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (s[i] <= s[j]) q[k++] = s[i++];
        else {
            q[k++] = s[j++];
            res += mid - i + 1;
        }
    }
    while (i <= mid) q[k] = s[i], k++, i++;
    while (j <= r) q[k] = s[j], k++, j++;
    for (int i = l; i <= r; i++) s[i] = q[i];
    return res;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i++) s[i] = read();
    cnt = mergesort(1, n, s, q);
    flag = !(cnt % 2);// 初始逆序对奇偶性
    m = read();
    for (int i = 1; i <= m; i++) {
        int l = read(), r = read();
        int t = (r - l + 1) * (r - l) / 2;// 数对个数
        if (t % 2 == 1) flag = !flag;
        if (flag == 0) puts("odd");
        else puts("even");
    }
    return 0;
}
```
**核心实现思想**：使用归并排序计算初始序列的逆序对数量，得到其奇偶性。对于每次查询，计算翻转区间的数对数量，根据其奇偶性判断逆序对奇偶性是否改变。

#### ⚡current⚡的代码
```c++
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int m, x, y, num;

int read() {
    int x = 0; char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x;
}

#define lowbit(x) x&-x

int n, a[600000], b[600000], c[600000];

void add(int x) {
    for(int i = x; i <= n; i += lowbit(i)) ++c[i];
} 

long long sum(int x) {
    long long ans = 0;
    for(int i = x; i; i -= lowbit(i)) ans += c[i];
    return ans;
}

int main(void) {
    long long ans = 0;
    cin >> n;
    for(int i = 1; i <= n; ++i) a[i] = b[i] = read();
    sort(b + 1, b + n + 1);
    for(int i = 1; i <= n; ++i) a[i] = n - (lower_bound(b + 1, b + n + 1, a[i]) - b) + 1; 
    for(int i = 1; i <= n; ++i) {
        ans += sum(a[i] - 1);
        add(a[i]);
    }
    ans &= 1;
    m = read();
    while(m--)
    {
        x = read();
        y = read();
        num = y-x+1;
        num = num*(num-1)/2;
        if((num)&1) ans = (ans+1)&1;
        if(ans) puts("odd");
        else puts("even");
    }
}
```
**核心实现思想**：使用树状数组计算初始序列的逆序对数量，得到其奇偶性。对于每次查询，计算翻转区间的数对数量，根据其奇偶性判断逆序对奇偶性是否改变。

### 最优关键思路或技巧
- **思维方式**：抓住只需要判断逆序对数量奇偶性这一关键，通过分析翻转区间内数对数量的奇偶性来判断整个序列逆序对数量奇偶性的变化，避免了每次都计算逆序对的具体数量。
- **算法优化**：使用归并排序或树状数组计算初始逆序对数量，将时间复杂度从暴力法的 $O(n^2)$ 优化到 $O(n\log n)$。

### 拓展思路
同类型题或类似算法套路：
- 涉及区间操作和逆序对相关的题目，可先考虑逆序对的性质，再结合区间操作的特点进行分析。
- 对于需要判断奇偶性的问题，可尝试通过数学推导找到判断奇偶性变化的规律，避免复杂的计算。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：经典的逆序对问题，可使用归并排序或树状数组求解。
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)：树状数组的基础应用，可帮助掌握树状数组的实现。
- [P1637 三元上升子序列](https://www.luogu.com.cn/problem/P1637)：涉及逆序对和组合计数，需要综合运用多种算法。

### 个人心得总结
- **Muruski**：提到数据范围大，直接暴力会超时，尝试多种方法后找到合适思路，提醒我们在做题时要根据数据范围选择合适的算法。
- **⚡current⚡**：仔细读题，明确题目要求，避免理解错误。对于复杂问题，可通过分析关键性质来简化问题。

---
处理用时：51.14秒