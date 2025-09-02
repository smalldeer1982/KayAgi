# 题目信息

# Physical Education

## 题目描述

Vasya is a school PE teacher. Unlike other PE teachers, Vasya doesn't like it when the students stand in line according to their height. Instead, he demands that the children stand in the following order: $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the height of the $ i $ -th student in the line and $ n $ is the number of students in the line. The children find it hard to keep in mind this strange arrangement, and today they formed the line in the following order: $ b_{1},b_{2},...,b_{n} $ , which upset Vasya immensely. Now Vasya wants to rearrange the children so that the resulting order is like this: $ a_{1},a_{2},...,a_{n} $ . During each move Vasya can swap two people who stand next to each other in the line. Help Vasya, find the sequence of swaps leading to the arrangement Vasya needs. It is not required to minimize the number of moves.

## 样例 #1

### 输入

```
4
1 2 3 2
3 2 1 2
```

### 输出

```
4
2 3
1 2
3 4
2 3
```

## 样例 #2

### 输入

```
2
1 100500
1 100500
```

### 输出

```
0
```

# AI分析结果

### 题目中文重写
# 体育

## 题目描述
Vasya 是一名学校的体育老师。与其他体育老师不同，Vasya 不喜欢学生们按照身高排队。相反，他要求孩子们按照以下顺序站立：$ a_{1},a_{2},...,a_{n} $，其中 $ a_{i} $ 是队伍中第 $ i $ 个学生的身高，$ n $ 是队伍中学生的数量。孩子们很难记住这个奇怪的排列顺序，今天他们按照以下顺序排好了队：$ b_{1},b_{2},...,b_{n} $，这让 Vasya 非常生气。现在 Vasya 想重新排列孩子们，使最终的顺序变为 $ a_{1},a_{2},...,a_{n} $。在每次移动中，Vasya 可以交换队伍中相邻的两个人。请帮助 Vasya 找到能得到他所需排列的交换序列。不需要最小化移动次数。

## 样例 #1
### 输入
```
4
1 2 3 2
3 2 1 2
```
### 输出
```
4
2 3
1 2
3 4
2 3
```

## 样例 #2
### 输入
```
2
1 100500
1 100500
```
### 输出
```
0
```

### 综合分析与结论
这些题解的核心思路都是将数组 `b` 变换为数组 `a`，且每次只能交换相邻元素，由于 `n` 的范围较小（$1 \leq n \leq 300$），大部分题解采用了 $O(n^2)$ 的算法。
- **思路对比**：多数题解是从 `a` 数组的第一个元素开始，在 `b` 数组中找到对应元素，然后通过相邻交换将其移动到正确位置；部分题解采用给元素打标记，对标记进行排序的方式。
- **算法要点**：主要是两层循环，外层遍历 `a` 数组，内层在 `b` 数组中查找元素并进行交换操作。
- **解决难点**：关键在于保证每次交换不会影响之前已经排列好的元素，通过从当前位置往后查找并交换的方式可以实现。

### 题解评分
| 作者 | 评分 | 理由 |
| --- | --- | --- |
| Siyuan | 4星 | 思路清晰，代码简洁，使用位运算交换元素，有一定优化 |
| drop | 3星 | 思路详细，通过表格展示交换过程，但代码使用 `vector` 增加了一定复杂度 |
| Supor__Shoep | 3星 | 思路和代码都比较常规，对算法原理有一定解释 |
| fls233666 | 3星 | 思路独特，通过打标记和冒泡排序解决问题，但代码相对复杂 |
| _edge_ | 3星 | 思路直接，代码实现简单，但有部分注释代码未清理 |
| _Weslie_ | 2星 | 思路有错误，时间复杂度分析不准确，代码存在语法错误 |
| 开始新的记忆 | 2星 | 思路和代码实现有混淆，交换的是 `a` 数组而非 `b` 数组 |
| lixiao189 | 3星 | 思路和 `fls233666` 类似，通过打标记排序，但代码结构稍显复杂 |

### 所选题解
- **Siyuan（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用位运算交换元素，减少了函数调用开销。
    - **核心代码**：
```cpp
for(register int i=1;i<=n;i++)
{
    register int k;
    for(register int j=i;j<=n;j++)
        if(b[j]==a[i]){k=j;break;}
    for(register int j=k;j>=i+1;j--)
    {
        b[j]^=b[j-1],b[j-1]^=b[j],b[j]^=b[j-1];
        ans[++cnt]=j;
    }
}
```
**核心实现思想**：外层循环遍历 `a` 数组，内层第一个循环在 `b` 数组中找到与 `a[i]` 相等的元素位置 `k`，然后通过内层第二个循环将该元素从位置 `k` 交换到位置 `i`，并记录交换位置。

### 最优关键思路或技巧
- **按顺序匹配交换**：从 `a` 数组的第一个元素开始，在 `b` 数组中找到对应元素，然后通过相邻交换将其移动到正确位置，这样可以保证每次交换不会影响之前已经排列好的元素。
- **打标记排序**：给 `a` 数组的元素打上有序标记，将标记映射到 `b` 数组中，然后对映射后的标记进行排序，也能实现将 `b` 数组变换为 `a` 数组的目的。

### 可拓展之处
同类型题可能会要求最小化交换次数，此时可以考虑使用逆序对、归并排序等算法来解决。类似算法套路还可以应用于字符串的变换、数组的重排等问题。

### 推荐洛谷题目
- [P1116 车厢重组](https://www.luogu.com.cn/problem/P1116)
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [P5737 【深基7.例3】闰年展示](https://www.luogu.com.cn/problem/P5737)

### 个人心得摘录与总结
- **_Weslie_**：萌新第一次写题解，发现有错误并进行了修改，提醒我们在写题解和解题时要仔细检查，避免出现错误。 

---
处理用时：36.82秒