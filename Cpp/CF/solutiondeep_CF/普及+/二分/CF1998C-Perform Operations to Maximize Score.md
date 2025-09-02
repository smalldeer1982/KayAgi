# 题目信息

# Perform Operations to Maximize Score

## 题目描述

I see satyam343. I'm shaking. Please more median problems this time. I love those. Please satyam343 we believe in you.

— satyam343's biggest fan



You are given an array $ a $ of length $ n $ and an integer $ k $ . You are also given a binary array $ b $ of length $ n $ .

You can perform the following operation at most $ k $ times:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) such that $ b_i = 1 $ . Set $ a_i = a_i + 1 $ (i.e., increase $ a_i $ by $ 1 $ ).

Your score is defined to be $ \max\limits_{i = 1}^{n} \left( a_i + \operatorname{median}(c_i) \right) $ , where $ c_i $ denotes the array of length $ n-1 $ that you get by deleting $ a_i $ from $ a $ . In other words, your score is the maximum value of $ a_i + \operatorname{median}(c_i) $ over all $ i $ from $ 1 $ to $ n $ .

Find the maximum score that you can achieve if you perform the operations optimally.

For an arbitrary array $ p $ , $ \operatorname{median}(p) $ is defined as the $ \left\lfloor \frac{|p|+1}{2} \right\rfloor $ -th smallest element of $ p $ . For example, $ \operatorname{median} \left( [3,2,1,3] \right) = 2 $ and $ \operatorname{median} \left( [6,2,4,5,1] \right) = 4 $ .

## 说明/提示

For the first test case, it is optimal to perform $ 5 $ operations on both elements so $ a = [8,8] $ . So, the maximum score we can achieve is $ \max(8 + \operatorname{median}[8], 8 + \operatorname{median}[8]) = 16 $ , as $ c_1 = [a_2] = [8] $ . It can be proven that you cannot get a better score.

For the second test case, you are not able to perform operations on any elements, so $ a $ remains $ [3,3,3] $ . So, the maximum score we can achieve is $ 3 + \operatorname{median}[3, 3] = 6 $ , as $ c_1 = [a_2, a_3] = [3, 3] $ . It can be proven that you cannot get a better score.

## 样例 #1

### 输入

```
8
2 10
3 3
1 1
3 10
3 3 3
0 0 0
4 4
2 1 5 1
0 1 0 1
5 4
7 5 2 5 4
0 0 1 0 1
5 1
5 15 15 2 11
1 0 0 1 1
5 2
10 11 4 10 15
1 1 0 1 0
4 4
1 1 2 5
1 1 0 0
2 1000000000
1000000000 1000000000
1 1```

### 输出

```
16
6
8
13
21
26
8
3000000000```

# AI分析结果



# Perform Operations to Maximize Score

## 题目描述

给定一个长度为 $n$ 的数组 $a$ 和一个整数 $k$，以及一个长度为 $n$ 的二进制数组 $b$。你可以进行最多 $k$ 次操作：每次选择一个满足 $b_i=1$ 的索引 $i$，将 $a_i$ 增加 1。得分定义为 $\max\limits_{i=1}^{n} \left( a_i + \operatorname{median}(c_i) \right)$，其中 $c_i$ 是删除 $a_i$ 后的数组。求通过最优操作能获得的最大得分。

## 题解综合分析

### 核心思路
所有题解均围绕两个核心方向展开：
1. **贪心策略**：优先将操作次数用于可操作的（b[i]=1）最大元素，直接提升该元素值
2. **二分答案**：确定最大可能的中位数值，通过验证是否可用剩余次数达成该中位数

### 最优解法总结
1. **预处理排序**：将数组排序以便快速确定中位数位置
2. **关键结论**：当无操作时，最优解必为删除最大元素后的中位数与原最大值的和
3. **分情况处理**：
   - 存在可操作的最大元素时：直接最大化该元素值并计算得分
   - 无法操作最大元素时：二分查找可能的最大中位数值

---

## 高分题解选评（4星及以上）

### 1. BrotherCall（4星）
**核心亮点**：
- 严谨的数学推导证明无操作时的最优解性质
- 清晰的二分答案框架设计
- 处理了操作分配与中位数验证的边界条件

**关键代码**：
```cpp
bool chk(ll tg) {
    ll kk = k;
    // 复制数组并尝试通过操作使足够多的元素 >= tg
    for (ll i = n; i; --i) {
        if (a[i].first < tg && a[i].second) {
            ll f = min(kk, tg - a[i].first);
            a[i].first += f;
            kk -= f;
        }
    }
    sort(a + 1, a + n + 1);
    return a[n >> 1].first >= tg; // 验证中位数位置是否满足
}
```

### 2. liugh_（5星）
**核心亮点**：
- 代码简洁高效，时间复杂度优化到 O(n log V)
- 巧妙利用排序后的位置关系直接计算中位数
- 正确处理两种情况的优先级关系

**关键实现**：
```cpp
auto chk = [&](int mid)->bool {
    vector<int> t;
    int lst = (n-1)/2 + 1; // 需要满足的数量阈值
    for(int i=1; i<=n-1; i++){
        if(a[i].fi >= mid) lst--;
        else if(a[i].se) t.pb(a[i].fi);
    }
    // 贪心使用操作次数填充差值
    sort(t.rbegin(), t.rend());
    while(lst > 0 && !t.empty()) {
        int need = mid - t.back();
        if(k >= need) {
            k -= need;
            lst--;
            t.pop_back();
        } else break;
    }
    return lst <= 0;
};
```

### 3. yshpdyt（4星）
**核心亮点**：
- 明确区分三种得分情况（操作最大元素、操作其他元素、不操作）
- 使用双指针优化二分验证过程
- 完整处理边界条件的测试用例

---

## 关键技巧总结
1. **中位数性质利用**：排序后直接通过下标访问中位数位置
2. **贪心验证策略**：从大到小填充差值，最大化利用每次操作的收益
3. **二分答案框架**：
   ```python
   l, r = min_val, max_possible
   while l < r:
       mid = (l + r + 1) // 2
       if check(mid): l = mid
       else: r = mid - 1
   ```

## 同类型题目推荐
1. [P1168 中位数](https://www.luogu.com.cn/problem/P1168) - 动态维护中位数
2. [P1801 黑匣子](https://www.luogu.com.cn/problem/P1801) - 对顶堆维护动态中位数
3. [CF1343D Constant Palindrome Sum](https://codeforces.com/problemset/problem/1343/D) - 差分数组与贪心结合

## 调试心得摘录
1. **排序顺序陷阱**：多个题解强调必须升序排序才能正确计算中位数位置
2. **边界条件**：当操作后的最大值仍小于原最大值时，需要修正中位数位置
3. **贪心验证优化**：将需要填充的差值按降序处理，优先处理差值小的元素

---
处理用时：49.13秒