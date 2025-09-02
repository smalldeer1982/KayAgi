# 题目信息

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314
```

### 输出

```
2
```

## 样例 #2

### 输入

```
625
```

### 输出

```
0
```

## 样例 #3

### 输入

```
333
```

### 输出

```
-1
```

# AI分析结果



# Make a Square 题解分析

## 一、算法分类
**枚举 + 子序列匹配**

---

## 二、题解思路与核心难点
### 核心思路
1. **逆向枚举平方数**：从 sqrt(n) 向下枚举每个可能的平方数，判断其数字序列是否为原数的子序列
2. **DFS 生成子序列**：深度优先遍历所有可能的保留数字组合，验证是否构成平方数
3. **前导零处理**：确保生成的数字不以零开头（除非数字本身就是0）

### 解决难点对比
| 方法               | 优点                          | 难点处理关键点                     |
|--------------------|-----------------------------|----------------------------------|
| 逆向枚举（GusyNight） | O(√n) 时间复杂度，高效          | 逆序存储原数字，子序列匹配时顺序对齐       |
| DFS（Andy_Li）      | 直观，覆盖所有可能情况          | 剪枝前导零路径，避免无效递归分支         |
| 暴力全排列（__Hachey__） | 无遗漏可能性                  | 需要处理排列组合而非子序列的严格顺序      |

---

## 三、题解评分（≥4★）
1. **GusyNight（★★★★☆）**
   - 亮点：逆向枚举思路巧妙，代码简洁高效（7行核心逻辑）
   - 优化点：原数逆序存储需特别注意子序列匹配方向
   ```cpp
   for(int i=sqrt(n);i>=1;i--){  // 逆向枚举关键点
       // 子序列双指针匹配逻辑...
   }
   ```
   
2. **QianianXY（★★★★★）**
   - 亮点：DFS剪枝策略优秀，前导零处理干净利落
   - 关键代码：
   ```cpp
   if(c[k] == '0' && !tot) return;  // 前导零剪枝
   ```

3. **Wf_yjqd（★★★★☆）**
   - 亮点：双指针匹配算法清晰，复杂度控制优秀
   - 核心逻辑：
   ```cpp
   for(j=1,k=1; j<=wn && k<=cnt; j++)  // 同步推进双指针
       if(a[j]==b[k]) k++;
   ```

---

## 四、最优思路提炼
### 关键技巧
1. **平方数逆向枚举**：从 sqrt(n) 向下遍历，第一个匹配的即为最优解
2. **双指针子序列匹配**：O(n) 时间验证候选平方数
3. **位运算剪枝**：通过保留位数快速排除不可能解

### 思维模型
```
原数数字序列 → 候选平方数 → 子序列匹配 → 计算删除次数
```

---

## 五、同类题目推荐
1. [CF1029B](https://codeforces.com/problemset/problem/1029/B) - 最长连续子序列
2. [洛谷 P1706](https://www.luogu.com.cn/problem/P1706) - 全排列问题
3. [LeetCode 279](https://leetcode.com/problems/perfect-squares/) - 完全平方数分解

---

## 六、可视化设计
### 算法演示方案
**复古像素风格交互演示**  
![演示示意图](https://pic.imgdb.cn/item/665d4a06d9c307b7e9f5a8e8.gif)

1. **视觉元素**
   - 8-bit 风格数字块（16色 palette）
   - 高亮匹配的数字序列（绿色像素块）
   - 候选平方数以滚动字幕形式展示

2. **交互逻辑**
   ```javascript
   // 伪代码示例
   function animateCheck(candidate, original) {
       let ptr = 0;
       original.forEach((num, idx) => {
           if(num === candidate[ptr]) {
               highlightBlock(idx, COLOR_GREEN);
               ptr++;
               playSound('blip.wav');
           }
       });
       if(ptr === candidate.length) playSuccessFanfare();
   }
   ```

3. **音效设计**
   - 匹配成功：FC 风格8-bit "coin" 音效
   - 匹配失败：短促下降音阶
   - 最终解：经典《超级马里奥》过关音效

---

## 七、核心代码实现
### GusyNight 题解关键片段
```cpp
vector<int> a, b;
// 逆序存储原数字
while(n) a.push_back(n%10), n /= 10; 

for(int i=sqrt(origin); i>=1; i--) {
    long long square = i*i;
    // 存储候选平方数（逆序）
    while(square) b.push_back(square%10), square /= 10;
    
    // 双指针匹配
    int p = 0;
    for(auto digit : a) {
        if(p < b.size() && digit == b[p]) p++;
    }
    if(p == b.size()) return a.size() - b.size();
}
```

---

## 八、个人心得摘录
> "DFS方法中前导零处理是最大陷阱，当保留数字长度为0时遇到0必须立即剪枝，否则会产生像101→01这样的非法解" —— QianianXY

> "逆向枚举时要注意原数字的存储顺序，子序列匹配必须保持候选平方数的数字顺序与原数出现顺序一致" —— GusyNight调试笔记

---

## 九、扩展思考
当 n 达到 1e18 时，可将候选平方数的生成改为**数位DP模式**：
1. 预计算所有可能位数的平方数范围
2. 使用 Trie 树存储平方数数位特征
3. 通过有限状态机进行快速匹配

复杂度可优化至 O(√n * logn)，适用于极大数值场景。

---
处理用时：73.95秒