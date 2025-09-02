# 题目信息

# Riding in a Lift

## 题目描述

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 说明/提示

Imagine that you are in a building that has exactly $ n $ floors. You can move between the floors in a lift. Let's number the floors from bottom to top with integers from $ 1 $ to $ n $ . Now you're on the floor number $ a $ . You are very bored, so you want to take the lift. Floor number $ b $ has a secret lab, the entry is forbidden. However, you already are in the mood and decide to make $ k $ consecutive trips in the lift.

Let us suppose that at the moment you are on the floor number $ x $ (initially, you were on floor $ a $ ). For another trip between floors you choose some floor with number $ y $ ( $ y≠x $ ) and the lift travels to this floor. As you cannot visit floor $ b $ with the secret lab, you decided that the distance from the current floor $ x $ to the chosen $ y $ must be strictly less than the distance from the current floor $ x $ to floor $ b $ with the secret lab. Formally, it means that the following inequation must fulfill: $ |x-y|<|x-b| $ . After the lift successfully transports you to floor $ y $ , you write down number $ y $ in your notepad.

Your task is to find the number of distinct number sequences that you could have written in the notebook as the result of $ k $ trips in the lift. As the sought number of trips can be rather large, find the remainder after dividing the number by $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
5 2 4 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 2 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 3 4 1
```

### 输出

```
0
```

# AI分析结果



# 电梯乘坐问题

## 题目内容

### 题目描述

假设你在一栋有恰好 $n$ 层的建筑物中，可以通过电梯在不同楼层间移动。楼层从下到上编号为 $1$ 到 $n$。你当前在第 $a$ 层。由于感到无聊，你决定进行 $k$ 次连续的电梯旅行。

每次移动时（假设当前在第 $x$ 层），选择的楼层 $y$ 必须满足以下条件：
1. $y \neq x$（不能停留在原地）
2. $|x-y| < |x-b|$（移动距离严格小于当前楼层到禁止层 $b$ 的距离）

要求计算经过 $k$ 次移动后可能形成的不同楼层序列总数，结果对 $10^9+7$ 取模。

### 输入样例
样例1：
```
5 2 4 1
```
样例2：
```
5 2 4 2
```
样例3：
```
5 3 4 1
```

### 输出样例
样例1：
```
2
```
样例2：
```
2
```
样例3：
```
0
```

---

## 算法分类：线性DP

## 题解核心分析

### 动态规划核心思想
定义 $dp[i][j]$ 表示经过 $i$ 次移动到达第 $j$ 层的方案数。转移方程基于以下观察：
- 每个楼层 $j$ 的合法前驱楼层构成连续区间
- 使用前缀和优化区间求和操作

#### 状态转移方程
$$ dp_{i,j} = \sum_{k \in valid(j)} dp_{i-1,k} - dp_{i-1,j} $$
其中 $valid(j)$ 表示能转移到 $j$ 的楼层区间

### 关键优化技巧
1. **坐标转换**：将禁止层 $b$ 映射为坐标原点，转化为单侧问题
2. **前缀和数组**：使用 $sum[i] = \sum_{j=1}^i dp[j]$ 加速区间查询
3. **滚动数组**：仅保留相邻两层的状态节省空间

### 复杂度对比
| 方法          | 时间复杂度 | 空间复杂度 |
|---------------|------------|------------|
| 朴素DP        | O(n²k)     | O(nk)      |
| 前缀和优化    | O(nk)      | O(n)       |

---

## 五星级题解推荐

### 题解1：gxy001（★★★★★）
**核心亮点**：
- 巧妙的坐标转换简化区间计算
- 滚动数组实现空间优化
- 代码简洁高效（15行核心逻辑）

**关键代码片段**：
```cpp
for(int i=1;i<=k;i++){
    for(int j=1;j<=n;j++) 
        f[j]=(s[n]-s[j>>1]-f[j]+mod+mod)%mod;
    for(int j=1;j<=n;j++) 
        s[j]=(s[j-1]+f[j])%mod;
}
```

### 题解2：XTianShuo（★★★★☆）
**创新点**：
- 差分数组实现区间更新
- 动态维护有效区间范围
- 包含详细图示说明

**差分优化逻辑**：
```cpp
f[i+1][l] = (f[i+1][l] + f[i][j]) % MOD;
f[i+1][r] = (f[i+1][r] - f[i][j] + MOD) % MOD;
```

---

## 可视化设计方案

### 动态规划矩阵演示
**实现方案**：
1. 使用HTML5 Canvas绘制n×k的网格
2. 每个单元格表示dp[i][j]的值
3. 颜色映射：深蓝→低值，亮黄→高值

**交互功能**：
- 步进控制：空格键单步执行
- 速度调节：滑块控制动画速度（100ms-2s）
- 高亮显示：当前更新的单元格闪烁红光

### 复古像素风格实现
```javascript
// Canvas初始化
const canvas = document.getElementById('dp-grid');
const ctx = canvas.getContext('2d');
const PALLETE = ['#2c3e50', '#3498db', '#e74c3c', '#f1c40f'];

function drawGrid(dp) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for(let i = 0; i < dp.length; i++) {
        for(let j = 0; j < dp[0].length; j++) {
            const color = PALLETE[dp[i][j] % 4];
            ctx.fillStyle = color;
            ctx.fillRect(j*20, i*20, 18, 18);
        }
    }
}
```

### 音效设计
- **状态更新**：8-bit "beep" 音效（440Hz方波）
- **错误提示**：短促降调音（200Hz三角波）
- **完成提示**：上升琶音（C大调三和弦）

---

## 相似题目推荐
1. **P1091 合唱队形**（线性DP+双向LIS）
2. **P1216 数字三角形**（经典DP+路径记录）
3. **P1434 滑雪**（记忆化搜索+方向转移）

---

## 核心代码实现
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int MOD = 1e9+7;
long long n, k, a, b;
long long dp[5010], prefix[5010];

int main() {
    scanf("%lld%lld%lld%lld", &n, &a, &b, &k);
    
    // 坐标转换
    if(a > b) n -= b, a -= b;
    else n = b-1, a = b - a;
    
    dp[a] = 1;
    for(int i=a; i<=n; i++) 
        prefix[i] = prefix[i-1] + dp[i];
        
    for(int step=1; step<=k; step++) {
        // 计算新状态
        for(int j=1; j<=n; j++) 
            dp[j] = (prefix[n] - prefix[j/2] - dp[j] + 2*MOD) % MOD;
        
        // 更新前缀和
        for(int j=1; j<=n; j++)
            prefix[j] = (prefix[j-1] + dp[j]) % MOD;
    }
    
    printf("%lld", prefix[n]);
    return 0;
}
```

---

通过将动态规划与高效的前缀和优化相结合，本方案在O(nk)时间复杂度内解决了问题，配合直观的可视化设计，可帮助学习者深入理解线性DP的优化技巧。

---
处理用时：99.48秒