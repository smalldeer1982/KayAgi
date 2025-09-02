# 题目信息

# Counting Kangaroos is Fun

## 题目描述

There are $ n $ kangaroos with pockets. Each kangaroo has a size (integer number). A kangaroo can go into another kangaroo's pocket if and only if the size of kangaroo who hold the kangaroo is at least twice as large as the size of kangaroo who is held.

Each kangaroo can hold at most one kangaroo, and the kangaroo who is held by another kangaroo cannot hold any kangaroos.

The kangaroo who is held by another kangaroo cannot be visible from outside. Please, find a plan of holding kangaroos with the minimal number of kangaroos who is visible.

## 样例 #1

### 输入

```
8
2
5
7
6
9
8
4
2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8
9
1
6
2
6
5
8
3
```

### 输出

```
5
```

# AI分析结果



# 数袋鼠很有趣

## 题目描述

有 $n$ 只袋鼠，每只袋鼠有一个大小（整数）。当且仅当一只袋鼠的大小至少是另一只袋鼠的两倍时，较大的袋鼠可以将较小的袋鼠装入自己的口袋。每只袋鼠最多装一只袋鼠，被装入的袋鼠不能再装其他袋鼠。求最少可见的袋鼠数量（即尽可能多的袋鼠被装入其他袋鼠的口袋）。

## 样例 #1

### 输入

```
8
2 5 7 6 9 8 4 2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
8
9 1 6 2 6 5 8 3
```

### 输出

```
5
```

---

**算法分类**：贪心

---

## 题解分析与结论

各题解核心思路高度一致，均采用 **排序+双指针贪心策略**。将袋鼠排序后，尝试用后半段较大的袋鼠装前半段较大的袋鼠，通过双指针匹配最大可装入数量，最终剩余可见袋鼠数为 $n - 最大匹配数$。

### 最优思路总结
1. **排序数组**：将袋鼠按大小升序排列
2. **双指针配对**：左指针从中间开始，右指针从末尾开始，尝试匹配 $a[left] \times 2 \leq a[right]$
3. **时间复杂度**：$O(n \log n)$（排序）+ $O(n)$（双指针遍历）

---

## 高星题解推荐

### 1. [Jr_Zlw] ⭐⭐⭐⭐
**亮点**：  
- 图示辅助理解指针移动过程  
- 代码包含防越界处理和详细注释  
- 强调数组大小开够的踩坑经验  

**关键代码**：
```cpp
sort(a+1, a+n+1);
int mid = (1+n)>>1, l = mid, r = n, ans = 0;
while(r > mid && l > 0) {
    if(a[l] * 2 > a[r]) l--;
    else { l--; r--; ans++; }
}
cout << ans + (n - mid); //剩余未匹配的后半段袋鼠均可见
```

### 2. [wind_whisper] ⭐⭐⭐⭐
**亮点**：  
- 给出二分法变种思路  
- 严谨证明贪心正确性（前 $n/2$ 小袋鼠必不可能装其他袋鼠）  
- 分析套娃式装入的数学性质  

**证明片段**：  
> "若某袋鼠装了一只不在前 $n/2$ 小的袋鼠，改为装该段中未被装的袋鼠仍可行"

### 3. [fmdd_szx] ⭐⭐⭐⭐
**亮点**：  
- 代码极简（仅15行）  
- 变量命名清晰（`m` 维护可用大袋鼠位置）  
- 使用位运算加速输入输出  

```cpp
sort(a+1, a+n+1);
int m = n, s = 0;
for(int i = n/2; i >= 1; i--)
    if(a[m] >= a[i]*2) m--, s++;
cout << n - s;
```

---

## 拓展与心得

### 调试经验
- **数组越界**：多位作者提到首次提交时数组开小导致RE（如 `a[500001]` 而非 `a[500000]`）
- **边界处理**：中点计算 `mid = (n+1)/2` 避免奇偶性问题
- **输入优化**：`ios::sync_with_stdio(false)` 加速大量数据读入

### 相似题目推荐
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094) - 贪心配对  
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 单调栈+贪心  
3. [P1233 木棍加工](https://www.luogu.com.cn/problem/P1233) - 二维偏序贪心

---
处理用时：54.55秒