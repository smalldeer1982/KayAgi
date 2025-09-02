# 题目信息

# Orangutan Approved Subarrays

## 题目描述

Suppose you have an array $ b $ . Initially, you also have a set $ S $ that contains all distinct elements of $ b $ . The array $ b $ is called orangutan-approved if it can be emptied by repeatedly performing the following operation:

- In one operation, select indices $ l $ and $ r $ ( $ 1 \leq l \leq r \leq |b| $ ) such that $ v = b_l = b_{l+1} = \ldots = b_r $ and $ v $ is present in $ S $ . Remove $ v $ from $ S $ , and simultaneously remove all $ b_i $ such that $ l \leq i \leq r $ . Then, reindex the elements $ b_{r+1}, b_{r+2}, \ldots $ as $ b_l, b_{l+1}, \ldots $ accordingly.

You are given an array $ a $ of length $ n $ and $ q $ queries.

Each query consists of two indices $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ), and you need to determine whether or not the subarray $ a_{l}, a_{l+1}, \ldots, a_r $ is orangutan-approved.

## 说明/提示

In the first query of the first testcase, the answer is YES.

- Initially, $ S=\{1,2\} $ and $ b=[1,2,2,1] $
- Select $ l=2 $ and $ r=3 $ . Since $ b_2=b_3=2 $ is in $ S $ , we may erase $ b_2 $ and $ b_3 $ from the array, as well as erasing $ 2 $ from $ S $ . The set $ S $ becomes $ \{1\} $ and the array becomes $ [1,1] $ .
- Select $ l=1 $ and $ r=2 $ . Since $ b_1=b_2=1 $ is in $ S $ , we may erase $ b_1 $ and $ b_2 $ from the array, as well as erasing $ 1 $ from $ S $ . The set $ S $ becomes $ \{\} $ and the array becomes $ [] $ .
- Since the array is now empty, we can say the original array is orangutan-approved.

In the first query of the second testcase, the answer is NO, because it can be shown that the subarray $ [2,1,2,1] $ cannot become empty through any sequence of valid operations.

## 样例 #1

### 输入

```
3
4 2
1 2 2 1
1 4
1 3
5 3
1 2 1 2 1
2 5
3 5
1 3
8 4
1 2 3 2 1 3 2 3
1 5
2 8
3 5
6 8```

### 输出

```
YES
YES
NO
YES
YES
YES
NO
YES
YES```

# AI分析结果



---

## 唯一算法分类

**双指针 + 线段树**

---

## 综合分析与结论

### 核心思路
题目要求判断子数组能否通过特定操作清空。核心在于**区间合法性判定**：任何颜色的首次出现区间必须包含后续同色区间，且各颜色区间不能相交。关键结论是：合法区间的子区间必然合法。

### 算法流程
1. **预处理 nxt 数组**：记录每个元素下一个同色位置。
2. **双指针维护合法区间**：右指针 `r` 扫描数组，左指针 `l` 动态调整至最大合法左端点。
3. **线段树辅助查询**：维护当前区间的 `nxt` 最大值，确保所有元素的后续同色位置不超过 `r`。
4. **预处理最小左端点**：对于每个 `r`，记录对应的最小合法 `l`，查询时直接判断。

### 可视化设计
- **双指针动画**：用红色（左指针）和蓝色（右指针）标记移动过程。
- **线段树高亮**：当右指针移动时，高亮新增的 `nxt[r]` 节点；左指针移动时，灰色标记被移除的节点。
- **冲突检测**：当线段树查询最大值超过 `r` 时，触发红色警示并移动左指针。
- **像素风格**：用 8-bit 网格表示数组，每个元素显示颜色和 `nxt` 值，线段树以二叉树形式动态更新。

---

## 题解清单 (≥4星)

1. **Hoks（⭐⭐⭐⭐⭐）**  
   - 核心：利用合法区间的单调性，双指针+线段树维护极大合法区间。
   - 亮点：清晰证明子区间合法性，高效预处理极大区间。

2. **lfxxx（⭐⭐⭐⭐）**  
   - 核心：预处理 `nxt` 数组，双指针动态维护线段树。
   - 亮点：简洁的线段树删除操作，直观处理区间冲突。

---

## 核心代码实现

### lfxxx 的关键代码
```cpp
int nxt[maxn]; // 下一个同色元素位置
vector<int> vec[maxn]; // 存储需要删除的节点

void work() {
    // 预处理nxt数组
    for(int i=1;i<=n;i++) cnt[i]=0;
    for(int i=n;i>=1;i--){
        nxt[i]=cnt[a[i]];
        cnt[a[i]]=i;
        vec[nxt[i]].push_back(i); // 记录需要删除的位置
    }

    // 双指针预处理合法区间
    int l=n+1, r=n+1;
    while(r>1) {
        r--;
        // 删除超过当前右端点的nxt
        for(int x:vec[r+1]) del(1,1,n,x);
        // 调整左指针直到合法
        while(l>1 && query(1,1,n,l-1, nxt[l-1]-1) > r) l--;
        minl[r] = l; // 记录当前r对应的最小合法l
    }
}

// 查询处理
while(q--) {
    int ql, qr;
    cin >> ql >> qr;
    cout << (ql >= minl[qr] ? "YES\n" : "NO\n");
}
```

---

## 最优思路提炼

1. **双指针极值维护**：固定右端点，动态调整左端点至最大合法位置。
2. **nxt 数组预处理**：快速定位每个元素的后续同色位置。
3. **线段树区间查询**：高效判断是否存在跨区间的 `nxt` 冲突。
4. **离线删除优化**：通过 `vec` 存储待删除节点，减少线段树操作次数。

---

## 同类题目推荐

1. **CF522D Closest Equals**  
   - 利用预处理相邻相同元素位置，线段树维护区间最小值。

2. **洛谷 P1972 [SDOI2009] HH的项链**  
   - 离线查询+树状数组维护最后出现位置。

3. **CF1000F One Occurrence**  
   - 线段树维护区间内只出现一次的元素。

---

## 可视化算法演示

### 动画设计
1. **像素网格**：数组元素显示为不同颜色方块，上方标注数值和 `nxt`。
2. **双指针移动**：红色（左）和蓝色（右）箭头标记当前扫描位置。
3. **线段树更新**：每次右指针移动，对应 `nxt` 值插入树中；左指针移动时，旧值变灰。
4. **冲突提示**：当线段树最大值超过 `r`，当前区间闪烁红色边框，左指针右移。

### 复古音效
- **操作音效**：插入/删除节点时播放 "beep" 音效。
- **成功音效**：合法区间显示时播放 8-bit 胜利旋律。

---

**答案**

```plaintext
---

## 唯一算法分类

**双指针 + 线段树**

---

## 综合分析与结论

### 核心思路
题目要求判断子数组能否通过特定操作清空。核心在于**区间合法性判定**：任何颜色的首次出现区间必须包含后续同色区间，且各颜色区间不能相交。关键结论是：合法区间的子区间必然合法。

### 算法流程
1. **预处理 nxt 数组**：记录每个元素下一个同色位置。
2. **双指针维护合法区间**：右指针 `r` 扫描数组，左指针 `l` 动态调整至最大合法左端点。
3. **线段树辅助查询**：维护当前区间的 `nxt` 最大值，确保所有元素的后续同色位置不超过 `r`。
4. **预处理最小左端点**：对于每个 `r`，记录对应的最小合法 `l`，查询时直接判断。

### 可视化设计
- **双指针动画**：用红色（左指针）和蓝色（右指针）标记移动过程。
- **线段树高亮**：当右指针移动时，高亮新增的 `nxt[r]` 节点；左指针移动时，灰色标记被移除的节点。
- **冲突检测**：当线段树查询最大值超过 `r` 时，触发红色警示并移动左指针。
- **像素风格**：用 8-bit 网格表示数组，每个元素显示颜色和 `nxt` 值，线段树以二叉树形式动态更新。

---

## 题解清单 (≥4星)

1. **Hoks（⭐⭐⭐⭐⭐）**  
   - 核心：利用合法区间的单调性，双指针+线段树维护极大合法区间。
   - 亮点：清晰证明子区间合法性，高效预处理极大区间。

2. **lfxxx（⭐⭐⭐⭐）**  
   - 核心：预处理 `nxt` 数组，双指针动态维护线段树。
   - 亮点：简洁的线段树删除操作，直观处理区间冲突。

---

## 核心代码实现

### lfxxx 的关键代码
```cpp
int nxt[maxn]; // 下一个同色元素位置
vector<int> vec[maxn]; // 存储需要删除的节点

void work() {
    // 预处理nxt数组
    for(int i=1;i<=n;i++) cnt[i]=0;
    for(int i=n;i>=1;i--){
        nxt[i]=cnt[a[i]];
        cnt[a[i]]=i;
        vec[nxt[i]].push_back(i); // 记录需要删除的位置
    }

    // 双指针预处理合法区间
    int l=n+1, r=n+1;
    while(r>1) {
        r--;
        // 删除超过当前右端点的nxt
        for(int x:vec[r+1]) del(1,1,n,x);
        // 调整左指针直到合法
        while(l>1 && query(1,1,n,l-1, nxt[l-1]-1) > r) l--;
        minl[r] = l; // 记录当前r对应的最小合法l
    }
}

// 查询处理
while(q--) {
    int ql, qr;
    cin >> ql >> qr;
    cout << (ql >= minl[qr] ? "YES\n" : "NO\n");
}
```

---

## 最优思路提炼

1. **双指针极值维护**：固定右端点，动态调整左端点至最大合法位置。
2. **nxt 数组预处理**：快速定位每个元素的后续同色位置。
3. **线段树区间查询**：高效判断是否存在跨区间的 `nxt` 冲突。
4. **离线删除优化**：通过 `vec` 存储待删除节点，减少线段树操作次数。

---

## 同类题目推荐

1. **CF522D Closest Equals**  
   - 利用预处理相邻相同元素位置，线段树维护区间最小值。

2. **洛谷 P1972 [SDOI2009] HH的项链**  
   - 离线查询+树状数组维护最后出现位置。

3. **CF1000F One Occurrence**  
   - 线段树维护区间内只出现一次的元素。

---

## 可视化算法演示

### 动画设计
1. **像素网格**：数组元素显示为不同颜色方块，上方标注数值和 `nxt`。
2. **双指针移动**：红色（左）和蓝色（右）箭头标记当前扫描位置。
3. **线段树更新**：每次右指针移动，对应 `nxt` 值插入树中；左指针移动时，旧值变灰。
4. **冲突提示**：当线段树最大值超过 `r`，当前区间闪烁红色边框，左指针右移。

### 复古音效
- **操作音效**：插入/删除节点时播放 "beep" 音效。
- **成功音效**：合法区间显示时播放 8-bit 胜利旋律。
```

---
处理用时：159.74秒