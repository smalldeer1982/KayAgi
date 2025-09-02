# 题目信息

# Even Subarrays

## 题目描述

You are given an integer array $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le n $ ).

Find the number of subarrays of $ a $ whose $ \operatorname{XOR} $ has an even number of divisors. In other words, find all pairs of indices $ (i, j) $ ( $ i \le j $ ) such that $ a_i \oplus a_{i + 1} \oplus \dots \oplus a_j $ has an even number of divisors.

For example, numbers $ 2 $ , $ 3 $ , $ 5 $ or $ 6 $ have an even number of divisors, while $ 1 $ and $ 4 $ — odd. Consider that $ 0 $ has an odd number of divisors in this task.

Here $ \operatorname{XOR} $ (or $ \oplus $ ) denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Print the number of subarrays but multiplied by 2022... Okay, let's stop. Just print the actual answer.

## 说明/提示

In the first test case, there are $ 4 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [3] $ , $ [3,1] $ , $ [1,2] $ , $ [2] $ .

In the second test case, there are $ 11 $ subarrays whose $ \operatorname{XOR} $ has an even number of divisors: $ [4,2] $ , $ [4,2,1] $ , $ [4,2,1,5] $ , $ [2] $ , $ [2,1] $ , $ [2,1,5] $ , $ [2,1,5,3] $ , $ [1,5,3] $ , $ [5] $ , $ [5,3] $ , $ [3] $ .

In the third test case, there is no subarray whose $ \operatorname{XOR} $ has an even number of divisors since $ \operatorname{XOR} $ of any subarray is either $ 4 $ or $ 0 $ .

## 样例 #1

### 输入

```
4
3
3 1 2
5
4 2 1 5 3
4
4 4 4 4
7
5 7 3 7 1 7 3```

### 输出

```
4
11
0
20```

# AI分析结果



---

## 唯一算法分类  
前缀异或和 + 哈希统计（枚举完全平方数）

---

## 综合分析与结论  

### 核心思路  
1. **数学转换**：发现只有完全平方数的因数个数为奇数，故问题转化为求异或和不是完全平方数的子数组数  
2.补集思想：总子数组数 $n(n+1)/2$ 减去异或和为完全平方数的子数组数  
3. **前缀异或和**：$s_i = a_1 \oplus ... \oplus a_i$，则区间 $[l,r]$ 异或和为 $s_r \oplus s_{l-1}$  
4. **哈希统计**：维护前缀和出现次数，枚举所有可能平方数 $k^2$，统计满足 $s_r \oplus k^2 = s_{l-1}$ 的左端点数  

### 算法流程  
1. 预处理异或前缀和数组  
2. 初始化哈希表记录前缀和出现次数（初始存入 s₀=0）  
3. 遍历每个右端点 r：  
   - 枚举所有可能的平方数 k²（k² ≤ 2n）  
   - 计算目标值 t = s[r] ^ k²  
   - 累加哈希表中 t 的出现次数到非法计数  
   - 将当前 s[r] 加入哈希表  
4. 最终答案 = 总子数组数 - 非法计数  

### 可视化设计  
**动画方案**：  
- **分层展示**：  
  1. 顶部显示数组元素和当前处理的右端点（高亮）  
  2. 中间显示异或前缀和数组，当前值用绿色标记  
  3. 底部用网格显示已存储的前缀和分布，匹配时闪烁  
- **动态枚举**：  
  1. 右侧面板列出当前枚举的平方数 k²  
  2. 每次计算 s[r]^k² 时，用红色箭头连接当前值与哈希表对应项  
- **统计面板**：  
  1. 实时更新合法/非法计数  
  2. 总答案随处理进度动态变化  

---

## 题解清单 (≥4星)  

### [Jasper08](https://xxx) ★★★★☆  
- 亮点：桶数组代替哈希表，时间复杂度 O(n√n)  
- 代码结构清晰，变量命名规范  
- 预处理平方数范围准确（650²≈4e5）  

### [Engulf](https://xxx) ★★★★  
- 亮点：动态维护哈希表，空间复杂度优化  
- 巧妙处理平方数枚举上限（j² ≤ 2n）  
- 代码简洁，直接计算总数-非法数  

### [yinhee](https://xxx) ★★★★  
- 亮点：正确处理大范围平方数（枚举到 2n）  
- 强调哈希表空间需开 4 倍避免溢出  
- 独立函数封装增强可读性  

---

## 核心代码实现  

```cpp
// 基于 Engulf 题解的精简实现
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
    int T; cin >> T;
    while(T--) {
        int n; cin >> n;
        vector<int> cnt(2*n + 5, 0); // 哈希表
        cnt[0] = 1; // 初始s₀=0
        LL ans = 1LL * n * (n + 1) / 2; // 总子数组数
        int pre = 0; // 当前异或前缀和
        
        for(int i=1; i<=n; ++i) {
            int x; cin >> x;
            pre ^= x;
            // 枚举平方数 k²
            for(int k=0; k*k <= 2*n; ++k) 
                ans -= cnt[pre ^ (k*k)];
            cnt[pre]++;
        }
        cout << ans << '\n';
    }
}
```

---

## 同类型题推荐  
1. **CF1775B** - 子数组异或性质  
2. **洛谷P1469** - 异或特殊性质  
3. **LeetCode 1310** - 前缀异和应用  

---

## 可视化与游戏化设计  

### 8位像素风格实现  
**颜色方案**：  
- 数组元素：青蓝色（#00FFFF）  
- 当前处理元素：闪烁黄色  
- 哈希表格子：按值大小渐变（深绿→浅绿）  

**动画逻辑**：  
1. **步进执行**：按空格单步，Enter自动播放  
2. **音效触发**：  
   - 枚举平方数：短促"滴"声  
   - 找到匹配：清脆"叮"声  
   - 错误匹配：低沉"嘟"声  

**Canvas 绘制**：  
```javascript
function drawStep(ctx, stepData) {
    // 绘制数组
    for(let i=0; i<arr.length; i++) {
        ctx.fillStyle = (i === currentIdx) ? '#FFFF00' : '#00FFFF';
        ctx.fillRect(10 + i*30, 50, 25, 25); 
    }
    // 绘制哈希表
    for(let key in hashTable) {
        let x = hashTable[key] * 30, y = 100;
        ctx.fillStyle = `hsl(${key*2}, 80%, 50%)`;
        ctx.fillRect(x, y, 25, 25);
    }
}
```

---

## 个人心得摘录  
> "枚举平方数时，上限取到 2n 是关键——异或结果可能超过原数组最大值" —— yinhee  
> "用桶数组代替 unordered_map 提速 3 倍，但要注意内存初始化" —— Jasper08  

---

## 知识迁移建议  
当遇到以下特征时考虑类似解法：  
1. 涉及子数组异或性质  
2. 需要统计满足数学条件的区间数  
3. 问题可转换为查找特定值的出现次数  

核心思想：**前缀和+哈希表快速查询**，结合数学性质缩小枚举范围。

---
处理用时：86.37秒