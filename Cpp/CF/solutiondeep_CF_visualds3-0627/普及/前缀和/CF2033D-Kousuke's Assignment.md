# 题目信息

# Kousuke's Assignment

## 题目描述

After a trip with Sakurako, Kousuke was very scared because he forgot about his programming assignment. In this assignment, the teacher gave him an array $ a $ of $ n $ integers and asked him to calculate the number of non-overlapping segments of the array $ a $ , such that each segment is considered beautiful.

A segment $ [l,r] $ is considered beautiful if $ a_l + a_{l+1} + \dots + a_{r-1} + a_r=0 $ .

For a fixed array $ a $ , your task is to compute the maximum number of non-overlapping beautiful segments.

## 样例 #1

### 输入

```
3
5
2 1 -3 2 1
7
12 -4 4 43 -3 -5 8
6
0 -4 0 3 0 1```

### 输出

```
1
2
3```

# AI分析结果



---

**算法分类**  
前缀和 + 贪心 / 动态规划

---

### **题解思路与解决难点**

#### **核心思路**
- **前缀和性质**：子段和为0等价于前缀和相等（即 $s_r = s_{l-1}$）。
- **贪心策略**：从左到右扫描，遇到可分割的最早位置立即分割，重置前缀和与集合，确保不重叠且最大化后续机会。
- **动态规划**：维护 `dp[i]` 表示前 `i` 个元素的最优解，利用 `map` 记录每个前缀和最后出现的位置，通过状态转移方程 $dp[i] = \max(dp[i-1], dp[last[s_i]] + 1)$ 计算。

#### **难点对比**
1. **贪心策略**  
   - **关键点**：分割后清空集合，保证剩余部分独立处理，时间复杂度 $O(n \log n)$。
   - **正确性**：每次选择最早分割点，确保剩余部分尽可能长，可能包含更多分割点。
   - **适用性**：代码简洁，但需证明贪心选择的正确性（已通过样例验证）。

2. **动态规划**  
   - **关键点**：利用 `map` 维护前缀和最后出现的位置，通过状态转移覆盖所有可能的分割点。
   - **正确性**：显然正确，但需维护 `dp` 数组和 `map`，代码稍复杂。
   - **适用性**：通用性强，可处理更复杂的子段条件。

---

### **题解评分 (≥4星)**

1. **chenxi2009（5星）**  
   - **亮点**：贪心策略代码简洁，时间复杂度低，正确性通过样例验证。
   - **代码**：利用 `set` 快速判断前缀和是否重复，分割后重置逻辑清晰。

2. **Super_Cube（5星）**  
   - **亮点**：动态规划思路清晰，状态转移方程明确，使用 `map` 优化查找效率。
   - **代码**：`dp` 数组维护最优解，兼容所有可能分割方式。

3. **The_foolishest_OIer（4星）**  
   - **亮点**：动态规划代码简洁，注释清晰，强调多测清空的重要性。
   - **改进点**：变量命名可更直观。

---

### **最优思路提炼**
1. **贪心分割**：遇到前缀和重复时立即分割，清空集合并重置前缀和，确保剩余部分独立处理。
2. **动态规划优化**：记录前缀和最后出现的位置，通过 `dp[i] = max(dp[i-1], dp[last[s_i]] + 1)` 实现高效转移。
3. **数据结构选择**：优先使用 `map` 而非 `unordered_map` 避免哈希冲突导致的性能问题。

---

### **同类型题与算法套路**
- **通用思路**：前缀和 + 哈希表优化，适用于子段和计数、最大不重叠区间等问题。
- **类似题目**：
  1. [LeetCode 325. Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/)
  2. [LeetCode 560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)
  3. [洛谷 P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)

---

### **个人心得摘录**
- **避免 `unordered_map`**：在 Codeforces 等平台中，`unordered_map` 可能因哈希冲突退化，需改用 `map`。
- **多测清空**：动态规划或贪心算法中，忘记清空全局变量（如 `map` 或 `set`）会导致错误。

---

### **可视化与算法演示**
#### **贪心策略动画设计**
1. **前缀和生成**：用进度条显示当前扫描位置，右侧显示实时前缀和。
2. **集合操作**：高亮当前前缀和，若在集合中存在，触发分割动画（红色分割线），清空集合并重置前缀和。
3. **颜色标记**：已处理部分（绿色），当前扫描元素（黄色），分割线（红色）。

#### **动态规划动画设计**
1. **状态转移**：逐步填充 `dp` 数组，高亮 `dp[i]` 的两种来源（继承 `dp[i-1]` 或从 `map` 中获取）。
2. **前缀和映射**：用 `map` 的树状结构展示键值对，每次更新时高亮最新插入的位置。
3. **交互控制**：支持单步执行，观察 `dp` 和 `map` 的联动变化。

---

### **核心代码实现**
#### **贪心策略（chenxi2009）**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100001],ans;
long long sum;
set<long long>s;
int main(){
    scanf("%d",&T);
    while(T --){
        ans = 0,sum = 0,s.clear(),s.insert(0);
        scanf("%d",&n);
        for(int i = 1;i <= n;i ++){
            scanf("%d",&a[i]);
            sum += a[i];
            if(s.count(sum)){
                sum = 0,ans ++,s.clear(),s.insert(0);
            }
            else s.insert(sum);
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

#### **动态规划（Super_Cube）**
```cpp
#include<bits/stdc++.h>
std::map<long long,int>mp;
int dp[100005];
int T,n;
long long s;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        mp.clear(); mp[0]=0; s=0;
        for(int i=1,x;i<=n;++i){
            scanf("%d",&x); s+=x;
            dp[i]=dp[i-1];
            if(mp.count(s)) dp[i]=std::max(dp[i],dp[mp[s]]+1);
            mp[s]=i;
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
```

---

**总结**：贪心与动态规划均能高效解题，前者代码简洁，后者更易理解。核心在于利用前缀和性质，通过哈希结构快速查找分割点。

---
处理用时：307.43秒