# 题目信息

# Rudolf and 121

## 题目描述

Rudolf has an array $ a $ of $ n $ integers, the elements are numbered from $ 1 $ to $ n $ .

In one operation, he can choose an index $ i $ ( $ 2 \le i \le n - 1 $ ) and assign:

- $ a_{i - 1} = a_{i - 1} - 1 $
- $ a_i = a_i - 2 $
- $ a_{i + 1} = a_{i + 1} - 1 $

Rudolf can apply this operation any number of times. Any index $ i $ can be used zero or more times.

Can he make all the elements of the array equal to zero using this operation?

## 说明/提示

In the first example, the original array is $ [1, 3, 5, 5, 2] $ , to make all its elements zero, Rudolf can act as follows:

- apply the operation at $ i=4 $ and get the array $ [1, 3, 4, 3, 1] $ ;
- apply the operation at $ i=3 $ and get the array $ [1, 2, 2, 2, 1] $ ;
- apply the operation at $ i=2 $ and get the array $ [0, 0, 1, 2, 1] $ ;
- apply the operation at $ i=4 $ and get the array $ [0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7
5
1 3 5 5 2
5
2 4 4 5 1
5
0 1 3 3 1
6
5 6 0 2 3 0
4
1 2 7 2
3
7 1 0
4
1 1 1 1```

### 输出

```
YES
NO
YES
NO
NO
NO
NO```

# AI分析结果



# Rudolf and 121 的题目翻译

## 题目描述

鲁道夫有一个包含 $n$ 个整数的数组 $a$，元素编号从 $1$ 到 $n$。

在一次操作中，他可以选择一个下标 $i$（$2 \le i \le n - 1$）并进行如下赋值：
- $a_{i - 1} = a_{i - 1} - 1$
- $a_i = a_i - 2$
- $a_{i + 1} = a_{i + 1} - 1$

鲁道夫可以执行任意次数的操作。任何下标 $i$ 都可以被使用零次或多次。

他能否通过这些操作使数组的所有元素都变为零？

## 说明/提示

第一个样例中，原始数组为 $[1, 3, 5, 5, 2]$，操作步骤如下：
1. 在 $i=4$ 执行操作，得到 $[1, 3, 4, 3, 1]$
2. 在 $i=3$ 执行操作，得到 $[1, 2, 2, 2, 1]$
3. 在 $i=2$ 执行操作，得到 $[0, 0, 1, 2, 1]$
4. 在 $i=4$ 执行操作，得到全零数组。

---

# 题解分析与结论

### 核心思路
所有高效解法均基于**贪心策略**：从左到右遍历数组，对每个位置 $i$ 进行尽可能多的操作，使其变为零，并同步修改后续元素。关键点如下：
1. **操作转化**：将原操作等价转换为对 $i, i+1, i+2$ 的影响（如 `a[i+1] -= 2*a[i]; a[i+2] -= a[i]`）。
2. **顺序处理**：处理完的左侧元素不再被修改，确保操作的确定性。
3. **即时校验**：若中间出现负数或最终两元素非零，则判定不可行。

### 最优题解（评分4星及以上）

#### 1. 作者：littlebug（5星）
**关键亮点**：
- 将操作转化为对后续元素的修改，实现线性遍历。
- 代码简洁高效，时间复杂度 $O(n)$。
- 完整处理边界条件（最后两元素单独校验）。

**核心代码**：
```cpp
for(int i=1; i<=n-2; ++i) {
    if(a[i] < 0) return "NO";
    a[i+1] -= a[i] * 2;
    a[i+2] -= a[i];
}
return (a[n-1]==0 && a[n]==0) ? "YES" : "NO";
```

#### 2. 作者：hhce2012（4星）
**关键亮点**：
- 使用 `goto` 跳出多重循环提升代码可读性。
- 显式处理操作后数组的全零校验。

**个人心得**：
> "注意循环过程中变成负数要直接跳出，否则后续减法会导致错误。"

---

# 关键技巧总结
1. **贪心顺序处理**：从左到右依次消除元素，避免回溯。
2. **操作等价转换**：将操作影响后移，简化实现逻辑。
3. **即时错误检测**：处理时检查负数，提前终止无效计算。
4. **边界条件处理**：单独校验最后两个元素是否为零。

---

# 类似题目推荐
1. [CF978B File Name](https://www.luogu.com.cn/problem/CF978B) - 贪心处理连续字符
2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106) - 贪心选择删除策略
3. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049) - 动态规划与贪心结合

---
处理用时：56.88秒