# 题目信息

# Tender Carpenter

## 题目描述

I would use a firework to announce, a wave to bid farewell, and a bow to say thanks: bygones are bygones; not only on the following path will I be walking leisurely and joyfully, but also the footsteps won't halt as time never leaves out flowing; for in the next year, we will meet again.

— Cocoly1990, [Goodbye 2022](https://www.luogu.com.cn/problem/P8941)



In his dream, Cocoly would go on a long holiday with no worries around him. So he would try out for many new things, such as... being a carpenter. To learn it well, Cocoly decides to become an apprentice of Master, but in front of him lies a hard task waiting for him to solve.

Cocoly is given an array $ a_1, a_2,\ldots, a_n $ . Master calls a set of integers $ S $ stable if and only if, for any possible $ u $ , $ v $ , and $ w $ from the set $ S $ (note that $ u $ , $ v $ , and $ w $ do not necessarily have to be pairwise distinct), sticks of length $ u $ , $ v $ , and $ w $ can form a non-degenerate triangle $ ^{\text{∗}} $ .

Cocoly is asked to partition the array $ a $ into several (possibly, $ 1 $ or $ n $ ) non-empty continuous subsegments $ ^{\text{†}} $ , such that: for each of the subsegments, the set containing all the elements in it is stable.

Master wants Cocoly to partition $ a $ in at least two different $ ^{\text{‡}} $ ways. You have to help him determine whether it is possible.

 $ ^{\text{∗}} $ A triangle with side lengths $ x $ , $ y $ , and $ z $ is called non-degenerate if and only if:

- $ x + y > z $ ,
- $ y + z > x $ , and
- $ z + x > y $ .

 $ ^{\text{†}} $ A sequence $ b $ is a subsegment of a sequence $ c $ if $ b $ can be obtained from $ c $ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

 $ ^{\text{‡}} $ Two partitions are considered different if and only if at least one of the following holds:

- the numbers of continuous subsegments split in two partitions are different;
- there is an integer $ k $ such that the lengths of the $ k $ -th subsegment in two partitions are different.

## 说明/提示

In the first test case, here are two possible partitions:

- $ [2, 3], [5, 7] $ , since 
  - $ [2, 3] $ is stable because sticks of lengths $ (2, 2, 2), (2, 2, 3), (2, 3, 3), (3, 3, 3) $ respectively can all form non-degenerate triangles.
  - $ [5, 7] $ is stable because sticks of lengths $ (5, 5, 5), (5, 5, 7), (5, 7, 7), (7, 7, 7) $ respectively can all form non-degenerate triangles.
- and $ [2], [3, 5], [7] $ , since 
  - $ [2] $ is stable because sticks of lengths $ (2, 2, 2) $ respectively can form a non-degenerate triangle.
  - $ [3, 5] $ is stable because sticks of lengths $ (3, 3, 3), (3, 3, 5), (3, 5, 5), (5, 5, 5) $ respectively can all form non-degenerate triangles.
  - $ [7] $ is stable because sticks of lengths $ (7, 7, 7) $ respectively can form a non-degenerate triangle.

Note that some other partitions also satisfy the constraints, such as $ [2], [3], [5], [7] $ and $ [2], [3], [5, 7] $ .

In the second test case, Cocoly can only partition each element as a single subsegment, resulting in $ [115], [9], [2], [28] $ . Since we only have one possible partition, the answer is $ \texttt{NO} $ .

In the third test case, please note that the partition $ [8, 4], [1], [6], [2] $ does not satisfy the constraints, because $ \{8, 4\} $ is not a stable set: sticks of lengths $ 4 $ , $ 4 $ , and $ 8 $ cannot form a non-degenerate triangle.

## 样例 #1

### 输入

```
5
4
2 3 5 7
4
115 9 2 28
5
8 4 1 6 2
6
1 5 4 1 4 7
2
100000 100000```

### 输出

```
YES
NO
NO
YES
YES```

# AI分析结果



---

**算法分类**: 贪心算法、预处理优化

### 综合分析与结论

**核心思路**  
题目要求将数组划分为连续子段，每个子段的集合必须满足稳定条件。稳定条件等价于：所有元素相同，或最大元素严格小于次大元素的两倍。问题转化为是否存在至少两个不同的划分方式。

**关键步骤**  
1. **预处理**：计算前缀和后缀数组，存储每个位置的最大值、次大值及是否全等。
2. **快速判断**：利用预处理数组，快速判断任意子段是否稳定。
3. **遍历分割点**：检查每个位置分割或合并是否均满足稳定条件，若存在则返回YES。

**可视化设计**  
- **动画方案**：展示前缀/后缀数组的构建过程，高亮当前处理的元素及其如何影响max和second_max。
- **颜色标记**：用不同颜色区分稳定与不稳定的子段，合并操作时突出相邻元素。
- **交互控制**：允许单步执行，观察每个分割点的判断逻辑。

### 最优思路提炼

1. **预处理优化**：通过前缀和后缀数组快速获取任意子段的最大、次大值，避免重复计算。
2. **条件简化**：稳定集合的判断简化为最大值与次大值的两倍关系，极大降低复杂度。
3. **关键点遍历**：仅需检查相邻元素的分割与合并情况，时间复杂度O(n)。

### 核心代码实现

```python
def solve():
    import sys
    input = sys.stdin.read
    data = input().split()
    idx = 0
    t = int(data[idx])
    idx += 1
    for _ in range(t):
        n = int(data[idx])
        idx +=1
        a = list(map(int, data[idx:idx+n]))
        idx +=n
        
        all_same = True
        first = a[0]
        for num in a[1:]:
            if num != first:
                all_same = False
                break
        if all_same:
            print("YES" if n >=2 else "NO")
            continue
        
        # Preprocess prefix
        prefix = [{} for _ in range(n)]
        prefix[0]['max'] = a[0]
        prefix[0]['second_max'] = -float('inf')
        prefix[0]['all_same'] = True
        for i in range(1, n):
            current = a[i]
            prev_max = prefix[i-1]['max']
            prev_second_max = prefix[i-1]['second_max']
            prev_all_same = prefix[i-1]['all_same']
            
            new_max = prev_max
            new_second_max = prev_second_max
            if current > prev_max:
                new_second_max = prev_max
                new_max = current
            elif current > prev_second_max:
                new_second_max = current
            
            new_all_same = prev_all_same and (current == prev_max)
            prefix[i]['max'] = new_max
            prefix[i]['second_max'] = new_second_max
            prefix[i]['all_same'] = new_all_same
        
        # Preprocess suffix
        suffix = [{} for _ in range(n)]
        suffix[-1]['max'] = a[-1]
        suffix[-1]['second_max'] = -float('inf')
        suffix[-1]['all_same'] = True
        for i in range(n-2, -1, -1):
            current = a[i]
            next_max = suffix[i+1]['max']
            next_second_max = suffix[i+1]['second_max']
            next_all_same = suffix[i+1]['all_same']
            
            new_max = next_max
            new_second_max = next_second_max
            if current > next_max:
                new_second_max = next_max
                new_max = current
            elif current > next_second_max:
                new_second_max = current
            
            new_all_same = next_all_same and (current == next_max)
            suffix[i]['max'] = new_max
            suffix[i]['second_max'] = new_second_max
            suffix[i]['all_same'] = new_all_same
        
        found = False
        for i in range(n-1):
            # Check split case
            left_ok = False
            if prefix[i]['all_same']:
                left_ok = True
            else:
                if prefix[i]['max'] < 2 * prefix[i]['second_max']:
                    left_ok = True
            
            right_ok = False
            if suffix[i+1]['all_same']:
                right_ok = True
            else:
                if suffix[i+1]['max'] < 2 * suffix[i+1]['second_max']:
                    right_ok = True
            
            # Check merge case
            merged_val1 = a[i]
            merged_val2 = a[i+1]
            max_merged = max(merged_val1, merged_val2)
            min_merged = min(merged_val1, merged_val2)
            merged_ok = (max_merged == min_merged) or (max_merged < 2 * min_merged)
            
            if left_ok and right_ok and merged_ok:
                found = True
                break
        
        print("YES" if found else "NO")

if __name__ == "__main__":
    solve()
```

### 同类型题目推荐

1. **P1115 最大子段和**：利用前缀和预处理快速求解。
2. **P1220 关路灯**：动态规划结合预处理优化。
3. **P1886 滑动窗口**：双端队列维护区间最值，类似滑动窗口的预处理思想。

---
处理用时：449.56秒