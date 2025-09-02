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



# 算法分类
**动态规划（DP） + 前缀和优化**

---

## 题解思路与核心难点分析

### 核心思路
所有题解均基于动态规划，核心思路为：
1. **状态定义**：`dp[i][j]` 表示第 `j` 次移动后到达楼层 `i` 的方案数
2. **转移方程**：`dp[i][j] = sum(所有能转移到i的楼层)` - `dp[i][j-1]`（排除原地停留）
3. **优化手段**：通过前缀和/差分将 O(n²k) 的时间复杂度优化至 O(nk)

### 解决难点
- **转移区间计算**：根据约束条件 `|x-y| < |x-b|`，推导出每个楼层 `i` 的合法转移区间 `[l, r]`
- **对称转换**：将楼层坐标转换为以 `b` 为分割点的单侧模型，简化区间计算（如将 `a > b` 的情况转换为 `a < b` 的镜像问题）
- **滚动数组**：通过复用数组空间将空间复杂度优化至 O(n)

---

## 可视化与算法演示设计

### 核心算法动态展示方案
**动画方案**：
1. **楼层状态条**：用水平色块表示每个楼层的 DP 值，颜色深浅表示数值大小
2. **当前操作高亮**：
   - 红色框线标记当前处理的楼层 `j`
   - 蓝色半透明覆盖层表示转移区间 `[l, r]`
3. **前缀和数组**：在楼层下方显示前缀和数组的实时值，用绿色箭头表示前缀和计算方向
4. **滚动效果**：每完成一轮转移后，旧状态向左淡出，新状态从右滑入

**交互功能**：
- 步进控制：支持逐帧播放/暂停，观察单次转移细节
- 速度调节：0.5x~5x 倍速调节动画速度
- 对比模式：并列展示前缀和优化与差分优化两种实现方式的状态变化

### 复古像素风格实现（示例）
```javascript
// Canvas 初始化
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const GRID_SIZE = 16; // 16x16 像素方块
const COLORS = ['#000000', '#FF0000', '#00FF00', '#0000FF']; // 黑、红、绿、蓝

// 绘制单个楼层状态
function drawFloor(floor, value, isCurrent) {
  const x = floor * GRID_SIZE;
  ctx.fillStyle = COLORS[isCurrent ? 1 : 0];
  ctx.fillRect(x, 0, GRID_SIZE-1, GRID_SIZE-1);
  
  // 数值用颜色深度表示
  ctx.fillStyle = `rgba(0,255,0,${value/MAX_VALUE})`;
  ctx.fillRect(x+2, 2, GRID_SIZE-5, GRID_SIZE-5);
}

// 播放8位音效
function playBeep(frequency) {
  const oscillator = audioCtx.createOscillator();
  oscillator.type = 'square';
  oscillator.frequency.setValueAtTime(frequency, audioCtx.currentTime);
  oscillator.connect(audioCtx.destination);
  oscillator.start();
  oscillator.stop(audioCtx.currentTime + 0.1);
}
```

---

## 题解评分与推荐

### ★★★★★ 题解推荐
1. **gxy001 的题解**  
   - 亮点：首创对称转换思想，将问题简化为单侧模型；使用滚动数组优化空间
   - 关键代码：
     ```cpp
     // 对称转换处理
     if(a>b) n-=b,a-=b;
     else n=b-1,a=b-a;
     // 前缀和滚动优化
     for(int j=1;j<=n;j++) f[j]=(s[n]-s[j>>1]-f[j]+mod+mod)%mod;
     ```

2. **XTianShuo 的题解**  
   - 亮点：差分优化实现，用未来状态更新思路提升计算效率
   - 关键代码：
     ```cpp
     // 差分处理转移区间
     f[i+1][l] = (f[i+1][l] + f[i][j]) % P;
     f[i+1][r] = ((f[i+1][r] - f[i][j]) % P + P) % P;
     ```

3. **zhaozixu2006 的题解**  
   - 亮点：完整保留原始坐标系的处理，适合理解原始问题本质
   - 关键代码：
     ```cpp
     // 差分排除当前楼层
     if(l <= j && j <= r) {
       dp[i + 1][j] = (dp[i + 1][j] - dp[i][j] + mod) % mod;
       dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % mod;
     }
     ```

---

## 同类型题目推荐
1. **CF466C Number of Ways**  
   （前缀和优化计数问题）
2. **Luogu P1091 合唱队形**  
   （双向动态规划与区间处理）
3. **LeetCode 1223. Dice Roll Simulation**  
   （带约束条件的动态规划优化）

---

## 核心代码实现（gxy001 版）
```cpp
#include<cstdio>
#include<algorithm>
int const mod=1000000007;
long long n,k,a,b,f[5010],s[5010];
int main(){
    scanf("%lld%lld%lld%lld",&n,&a,&b,&k);
    // 对称转换处理
    if(a>b) n-=b,a-=b;
    else n=b-1,a=b-a;
    
    f[a]=1;
    for(int i=a;i<=n;i++)s[i]=1;
    
    // 动态规划主循环
    for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++) 
            f[j]=(s[n] - s[j>>1] - f[j] + 2*mod) % mod;
        for(int j=1;j<=n;j++)
            s[j]=(s[j-1]+f[j])%mod;
    }
    printf("%lld",s[n]);
    return 0;
}
```

---

## 关键思路提炼
1. **问题转换**：将 `b` 层作为分割点，转化为单侧问题消除绝对坐标影响
2. **转移区间计算**：通过数学推导得出 `l = j>>1 + 1` 的简洁表达式
3. **滚动优化**：使用单数组交替存储当前状态与下一状态
4. **负数取模**：通过 `+ 2*mod` 确保减法后结果非负

---

## 个人心得摘录
> "考试时忘记处理负数取模导致 WA 了两发，以后遇到减法必须 `+mod%mod`" —— _H17_  
> 调试经验：当 `n=5, a=3, b=4` 时，转移区间计算需特别注意边界条件

---
处理用时：96.65秒