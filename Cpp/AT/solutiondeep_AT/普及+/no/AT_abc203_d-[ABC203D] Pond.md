# 题目信息

# [ABC203D] Pond

## 题目描述

### 题目大意

给定一个 $n\times n$ 的矩阵 $A$，再给定一个数 $k$，求矩阵中所有大小为 $k\times k$ 的子矩阵的中位数的最小值。

一个 $k\times k$ 的矩阵的中位数被定义为将矩阵中的所有数从大到小排序后的第 $\lfloor\frac{k^2}{2}\rfloor+1$ 个数。

## 说明/提示

$1\le k\le n\le 800,0\le A_{i,j}\le 10^9$。

Translated by \_Ponder_

## 样例 #1

### 输入

```
3 2

1 7 0

5 8 11

10 4 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3

1 2 3

4 5 6

7 8 9```

### 输出

```
5```

# AI分析结果

### 题目内容重写
【题目内容】
# [ABC203D] Pond

## 题目描述

### 题目大意

给定一个 $n\times n$ 的矩阵 $A$，再给定一个数 $k$，求矩阵中所有大小为 $k\times k$ 的子矩阵的中位数的最小值。

一个 $k\times k$ 的矩阵的中位数被定义为将矩阵中的所有数从大到小排序后的第 $\lfloor\frac{k^2}{2}\rfloor+1$ 个数。

## 说明/提示

$1\le k\le n\le 800,0\le A_{i,j}\le 10^9$。

Translated by \_Ponder_

## 样例 #1

### 输入

```
3 2

1 7 0

5 8 11

10 4 2```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3

1 2 3

4 5 6

7 8 9```

### 输出

```
5```

### 算法分类
二分、前缀和

### 题解分析与结论
题目要求找到所有 $k \times k$ 子矩阵的中位数的最小值。直接暴力枚举所有子矩阵并排序求中位数的时间复杂度为 $O(n^2k^2\log k)$，显然无法通过。因此，优化思路是使用二分答案结合二维前缀和来判断某个值是否能成为某个子矩阵的中位数。

### 所选高分题解
#### 题解1：_RainCappuccino_ (4星)
**关键亮点**：
- 使用二分答案结合二维前缀和，时间复杂度为 $O(n^2\log n)$。
- 通过将矩阵转化为01矩阵，利用前缀和快速计算子矩阵中大于某个值的元素个数。

**核心代码**：
```cpp
bool check(int x) {
    int z;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            b[i][j] = a[i][j] > x;
            b[i][j] = b[i][j - 1] + b[i - 1][j] - b[i - 1][j - 1] + b[i][j];
        }
    }
    bool flag = 0;
    for (int i = 1; i <= n - k + 1; i++) {
        for (int j = 1; j <= n - k + 1; j++) {
            z = b[i + k - 1][j + k - 1] - b[i - 1][j + k - 1] - b[i + k - 1][j - 1] + b[i - 1][j - 1];
            if (z <= kpow) {
                flag = 1;
                break;
            }
        }
        if (flag) break;
    }
    return flag;
}
```

#### 题解2：刘辰雨 (4星)
**关键亮点**：
- 同样使用二分答案和二维前缀和，但代码结构更加清晰。
- 通过统计每个子矩阵中大于某个值的元素个数来判断中位数的可能性。

**核心代码**：
```cpp
int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i<= n ; i++) {
        for(int j = 1 ; j<= n ; j++) {
            scanf("%d", &mp[i][j]);
            minv = min(mp[i][j], minv);
            maxv = max(mp[i][j], maxv);
        }
    }
    int l = minv, r = maxv, ans = maxv;
    while(l <= r) {
        int mid = (l+r) >> 1;
        for(int i = 1 ; i <= n ; i++) {
            for(int j = 1 ; j<= n ; j++) {
                pre[i][j] = 0;
                if(mp[i][j] > mid) pre[i][j] = 1;
                pre[i][j] = pre[i][j]+pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
            }
        }
        maxv = 0, minv = 1e9;
        bool F = false;
        for(int i = 1 ; i+k-1 <= n ; i++) {
            for(int j = 1 ; j+k-1 <= n ; j++) {
                int o = i+k-1;
                int p = j+k-1;
                int num = pre[o][p]-pre[o][j-1]-pre[i-1][p]+pre[i-1][j-1];
                if(num == k*k/2) F = true;
                maxv = max(maxv, num);
                minv = min(minv, num);
            }
        }
        if(F) ans = mid, r = mid-1;
        else if(minv > k*k/2) l = mid+1;
        else r = mid-1;
    }
    printf("%d\n", ans);
    return 0;
}
```

### 最优关键思路或技巧
- **二分答案**：通过二分法快速缩小中位数的可能范围。
- **二维前缀和**：通过预处理二维前缀和，快速计算子矩阵中大于某个值的元素个数，从而判断中位数的可能性。

### 可拓展之处
- 类似的问题可以扩展到更高维度的矩阵中，使用类似的前缀和技巧。
- 二分答案结合前缀和的思路可以应用于其他需要快速统计子矩阵性质的问题。

### 推荐相似题目
1. [P1527 矩阵中位数](https://www.luogu.com.cn/problem/P1527)
2. [P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216)
3. [P3396 哈希冲突](https://www.luogu.com.cn/problem/P3396)

---
处理用时：36.83秒