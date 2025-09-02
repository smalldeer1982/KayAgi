# 题目信息

# Sequence Transformation

## 题目描述

You are given a sequence $ a $ , initially consisting of $ n $ integers.

You want to transform this sequence so that all elements in it are equal (i. e. it contains several occurrences of the same element).

To achieve this, you choose some integer $ x $ that occurs at least once in $ a $ , and then perform the following operation any number of times (possibly zero): choose some segment $ [l, r] $ of the sequence and remove it. But there is one exception: you are not allowed to choose a segment that contains $ x $ . More formally, you choose some contiguous subsequence $ [a_l, a_{l + 1}, \dots, a_r] $ such that $ a_i \ne x $ if $ l \le i \le r $ , and remove it. After removal, the numbering of elements to the right of the removed segment changes: the element that was the $ (r+1) $ -th is now $ l $ -th, the element that was $ (r+2) $ -th is now $ (l+1) $ -th, and so on (i. e. the remaining sequence just collapses).

Note that you can not change $ x $ after you chose it.

For example, suppose $ n = 6 $ , $ a = [1, 3, 2, 4, 1, 2] $ . Then one of the ways to transform it in two operations is to choose $ x = 1 $ , then:

1. choose $ l = 2 $ , $ r = 4 $ , so the resulting sequence is $ a = [1, 1, 2] $ ;
2. choose $ l = 3 $ , $ r = 3 $ , so the resulting sequence is $ a = [1, 1] $ .

Note that choosing $ x $ is not an operation. Also, note that you can not remove any occurrence of $ x $ .

Your task is to find the minimum number of operations required to transform the sequence in a way described above.

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
5
3
1 1 1
5
1 2 3 4 5
5
1 2 3 2 1
7
1 2 3 1 2 3 1
11
2 2 1 2 3 2 1 2 3 1 2```

### 输出

```
0
1
1
2
3```

# AI分析结果

### 题目内容重写
# 序列变换

## 题目描述

给定一个初始包含 $n$ 个整数的序列 $a$。

你希望通过变换使序列中的所有元素都相等（即序列中只包含某个元素的多次出现）。

为了实现这一目标，你可以选择一个在序列 $a$ 中至少出现一次的整数 $x$，然后执行以下操作任意次数（包括零次）：选择一个不包含 $x$ 的连续子序列 $[l, r]$ 并将其删除。删除后，序列中剩余元素的编号会重新排列，即删除后的序列会紧凑排列。

注意，一旦选择了 $x$，之后的操作中不能更改 $x$。

你的任务是找到使序列中所有元素相等所需的最小操作次数。

你需要回答 $t$ 个独立的测试用例。

## 样例 #1

### 输入

```
5
3
1 1 1
5
1 2 3 4 5
5
1 2 3 2 1
7
1 2 3 1 2 3 1
11
2 2 1 2 3 2 1 2 3 1 2
```

### 输出

```
0
1
1
2
3
```

### 算法分类
贪心

### 题解分析与结论
1. **核心思路**：所有题解的核心思路都是通过选择某个数 $x$，然后计算将序列中所有非 $x$ 的元素删除所需的最小操作次数。关键在于如何高效地计算这些操作次数。
2. **难点对比**：
   - **封禁用户**的题解通过统计每个数的出现次数，并根据 $x$ 在序列中的位置（是否在开头或结尾）来计算操作次数，思路清晰但代码实现稍显复杂。
   - **fls233666**的题解通过压缩连续相同的数，简化了序列的处理，并详细解释了如何根据 $x$ 的位置来计算操作次数，代码简洁且高效。
   - **KSToki**的题解通过压缩序列并分类讨论 $x$ 的位置，直接计算操作次数，思路清晰且代码简洁。
3. **最优思路**：**fls233666**的题解通过压缩序列并统计每个数的出现次数，结合 $x$ 的位置来计算操作次数，思路清晰且代码简洁，是最优的解决方案。

### 高星题解推荐
#### 1. fls233666 (★★★★★)
**关键亮点**：
- 通过压缩序列简化了问题，减少了不必要的计算。
- 详细解释了如何根据 $x$ 的位置来计算操作次数，思路清晰。
- 代码简洁且高效，易于理解和实现。

**核心代码**：
```cpp
for(rgt i=1;i<=lxa;i++){  //按上述规则统计
    if(!cnt[xa[i]]){    //特判第一次出现
        if(i>1)  //不在开头，左侧有数组，划分段数++
            cnt[xa[i]]++;
        len++;   //加入最终的答案筛选数组
        ap[len]=xa[i];
    }
    if(i<lxa)  //不在结尾，划分段数++
        cnt[xa[i]]++;
}
```

#### 2. KSToki (★★★★☆)
**关键亮点**：
- 通过压缩序列并分类讨论 $x$ 的位置，直接计算操作次数。
- 思路清晰且代码简洁，易于理解和实现。

**核心代码**：
```cpp
for(int i=1;i<=tmp;++i)
    ans=min(ans,cnt[a[i]]+1);
```

### 关键思路与技巧
1. **序列压缩**：通过压缩连续相同的数，简化序列处理，减少计算量。
2. **分类讨论**：根据 $x$ 在序列中的位置（开头、结尾、中间）来计算操作次数，确保计算准确。
3. **贪心策略**：每次删除尽可能长的非 $x$ 子序列，以减少操作次数。

### 拓展与举一反三
- 类似问题：在处理序列问题时，压缩连续相同的元素是一个常见的优化技巧，可以减少问题的复杂度。
- 推荐题目：
  1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
  2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
  3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

### 个人心得摘录
- **fls233666**：通过压缩序列简化了问题，减少了不必要的计算，代码简洁且高效。
- **KSToki**：分类讨论 $x$ 的位置，直接计算操作次数，思路清晰且代码简洁。

---
处理用时：35.03秒