# 题目信息

# Find Marble

## 题目描述

Petya and Vasya are playing a game. Petya's got $ n $ non-transparent glasses, standing in a row. The glasses' positions are indexed with integers from $ 1 $ to $ n $ from left to right. Note that the positions are indexed but the glasses are not.

First Petya puts a marble under the glass in position $ s $ . Then he performs some (possibly zero) shuffling operations. One shuffling operation means moving the glass from the first position to position $ p_{1} $ , the glass from the second position to position $ p_{2} $ and so on. That is, a glass goes from position $ i $ to position $ p_{i} $ . Consider all glasses are moving simultaneously during one shuffling operation. When the glasses are shuffled, the marble doesn't travel from one glass to another: it moves together with the glass it was initially been put in.

After all shuffling operations Petya shows Vasya that the ball has moved to position $ t $ . Vasya's task is to say what minimum number of shuffling operations Petya has performed or determine that Petya has made a mistake and the marble could not have got from position $ s $ to position $ t $ .

## 样例 #1

### 输入

```
4 2 1
2 3 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 3 3
4 1 3 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 3 4
1 2 3 4
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3 1 3
2 1 3
```

### 输出

```
-1
```

# AI分析结果



### 题目重述
# 寻找弹珠

## 题目描述

Petya和Vasya在玩游戏。Petya有 $n$ 个不透明杯子排成一列，位置编号从 $1$ 到 $n$。Petya先将弹珠放在位置 $s$ 的杯子下，然后进行若干次（可能零次）洗牌操作。每次洗牌操作将位置 $i$ 的杯子移动到位置 $p_i$（所有杯子同时移动）。弹珠会跟随其所在杯子移动。最终弹珠停在位置 $t$，求最少需要多少次洗牌操作，若不可能则输出 $-1$。

### 样例
（此处保持原样例不变）

---

### 算法分类
模拟

---

### 题解对比与结论
**核心思路**：模拟弹珠的移动过程，每次将当前位置 $s$ 更新为 $p[s]$，直到找到 $t$ 或检测到循环。  
**关键技巧**：  
1. **循环检测**：置换操作形成环，若操作次数超过 $n$ 次仍未找到 $t$，则必定陷入循环。  
2. **空间优化**：无需记录访问位置，利用置换环的性质，通过操作次数或初始位置判断循环。  
3. **特判优化**：优先处理初始 $s = t$ 的情况，避免冗余循环。

---

### 推荐题解
#### 题解作者：zzx114514（⭐⭐⭐⭐⭐）
**亮点**：  
- 直接特判初始 $s = t$，逻辑简洁。  
- 用操作次数是否超过 $n$ 判断循环，无需额外空间。  
- 代码清晰，时间复杂度严格 $O(n)$。  
**核心代码**：
```cpp
int main() {
    cin >> n >> s >> t;
    if (s == t) { cout << 0; return 0; }
    for (int i = 1; i <= n; i++) cin >> p[i];
    while (cnt < n) {
        s = p[s];
        cnt++;
        if (s == t) break;
    }
    cout << (cnt < n ? cnt : -1);
}
```

#### 题解作者：残阳如血（⭐⭐⭐⭐）
**亮点**：  
- 记录初始位置 $ps$，通过是否回到起点判断循环。  
- 无额外空间，利用置换环的唯一性简化逻辑。  
**核心代码**：
```cpp
int main() {
    cin >> n >> s >> t;
    int ps = s;
    while (true) {
        s = p[s], cnt++;
        if (s == t) { cout << cnt; return 0; }
        if (s == ps) { cout << -1; return 0; }
    }
}
```

#### 题解作者：Dws_t7760（⭐⭐⭐⭐）
**亮点**：  
- 使用访问数组标记已遍历位置，准确检测循环。  
- 循环条件综合判断，覆盖所有边界情况。  
**核心代码**：
```cpp
int main() {
    // 初始化与输入略
    while (!v[s] && s != t && ans <= n) {
        v[s] = true;
        s = a[s], ans++;
    }
    cout << (s == t ? ans : -1);
}
```

---

### 拓展与心得
**同类问题**：  
- 置换环相关问题（如计算置换分解后的环结构）。  
- 路径循环检测（如链表判环）。  
**个人心得**：  
- 置换操作必形成若干独立环，每个元素属于唯一环，此性质可用于优化循环判断。  
- 初始特判可减少不必要的计算。  
- 避免使用 `vector` 或数组时越界，注意索引从1开始的情况。

---

### 相似题目推荐
1. [P2921 Trick or Treat on the Farm](https://www.luogu.com.cn/problem/P2921)  
2. [P1037 产生数](https://www.luogu.com.cn/problem/P1037)  
3. [P1553 数组变换](https://www.luogu.com.cn/problem/P1553)

---
处理用时：260.22秒