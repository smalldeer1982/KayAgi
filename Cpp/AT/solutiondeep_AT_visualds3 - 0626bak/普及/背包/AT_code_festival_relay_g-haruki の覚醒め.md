# 题目信息

# haruki の覚醒め

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-relay/tasks/code_festival_relay_g

haruki さんは朝に弱いことで有名です。haruki さんの家には目覚まし時計が $ n $ 個あり、$ i $ 番目の目覚まし時計の音量は $ a_i $ です。

   
haruki さんは鳴っている目覚まし時計の音量の合計が $ m $ 以上にならない限り、目を覚ますことはありません。しかしながら、必要以上に目覚まし時計をセットすると、うるさくて近所迷惑になってしまいます。

   
そこで、合計の音量が $ m $ 以上でかつ最小となるように目覚まし時計を選んだとき、その合計の音量を求めてください。

## 样例 #1

### 输入

```
3 30

25

10

23```

### 输出

```
33```

## 样例 #2

### 输入

```
4 101

10

20

30

40```

### 输出

```
-1```

# AI分析结果



# 算法分类选择
动态规划（背包问题）

# 综合分析与结论
## 核心思路与难点
**问题转化**是关键：将原问题转化为求容量为sum-m的背包最大价值问题。原问题要求选数总和≥m且最小，等价于从总和中剔除部分数使得剩余数总和≤sum-m，且尽可能大。最终答案即为sum减去最大可剔除量。

**算法实现要点**：
1. 计算所有数总和sum，若sum<m直接返回-1
2. 建立容量为sum-m的背包，物品价值与重量均为a[i]
3. 使用一维数组逆向填充的01背包解法
4. 最终结果=sum - 背包最大价值

**难点突破**：
- 逆向思维转换：原问题求最小值→转化为求最大值
- 空间优化：通过逆序遍历实现状态压缩
- 边界处理：总和校验与负数容量处理

## 可视化设计思路
**动态规划过程演示**：
1. 初始空背包（全灰格子）
2. 逐物品处理时，用不同颜色标记当前处理的物品
3. 背包容量从右向左更新，已更新格子高亮闪烁
4. 最终答案格用金色边框标注

**复古风格实现**：
```javascript
// 伪代码示例
const canvas = document.getElementById('pixel-canvas');
ctx.fillStyle = '#8B8B8B'; // 背包未填充颜色
ctx.fillRect(x, y, 16, 16); // 16x16像素格子

// 更新背包时播放音效
function playSound() {
  const osc = audioContext.createOscillator();
  osc.frequency.setValueAtTime(440, audioContext.currentTime);
  osc.connect(audioContext.destination);
  osc.start(); osc.stop(0.1);
}
```

# 题解清单 (≥4星)
1. **MattL（5星）**
   - 思路清晰，正确应用背包转化思想
   - 代码简洁高效，包含关键注释
   - 时间复杂度O(n*(sum-m))，空间O(sum)

2. **simonG（4星）**
   - 相同思路但变量命名更规范
   - 注释说明"正难则反"的思维转换
   - 输出处理稍显冗余

3. **cjZYZtcl（4星）**
   - 布尔型DP实现，直观展示可达性
   - 使用long long防止溢出
   - 包含输入优化与安全校验

# 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[55], sum;
int dp[1000005]; // 最大sum=1e6时仍可处理

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if(sum < m) {
        cout << -1 << endl;
        return 0;
    }
    int capacity = sum - m;
    
    // 01背包核心
    for(int i=1; i<=n; i++)
        for(int j=capacity; j>=a[i]; j--)
            dp[j] = max(dp[j], dp[j - a[i]] + a[i]);
    
    cout << sum - dp[capacity] << endl;
    return 0;
}
```

# 相似题目推荐
1. **P1048 采药**（基础背包）
2. **P1064 金明的预算方案**（依赖型背包）
3. **P2347 砝码称重**（布尔型背包）

# 可视化关键代码
```javascript
// 背包更新动画示例
function updateBackpack(item, capacity) {
  for(let j=capacity; j >= item; j--) {
    if(dp[j - item] + item > dp[j]) {
      dp[j] = dp[j - item] + item;
      // 高亮当前更新位置
      drawPixel(j, currentColor);
      playBeepSound(500 + j*10); // 音调随容量变化
    }
  }
}
```

# 个人心得摘录
"在背包问题中，当遇到求最小可行解时，可以考虑转化为求最大剔除量。这个思维转换就像把镜子翻转，让问题在另一个角度变得清晰可见。" —— MattL题解中的思维亮点

# 算法演示说明
**动画参数设置**：
- 速度调节：0.5x~3x可调
- 高亮规则：当前物品红色，更新位置黄色闪烁
- 音效反馈：每次更新播放8-bit音效，音高与容量正相关

**复古效果**：
1. 背包显示为16x16像素网格
2. 成功时显示8-bit风格烟花动画
3. 失败时屏幕抖动并播放经典FC错误音效

**AI自动演示**：
```javascript
function autoDemo() {
  let step = 0;
  const timer = setInterval(() => {
    if(step >= n) clearInterval(timer);
    processItem(items[step++]);
  }, 1000); // 每秒处理一个物品
}
```

---
处理用时：73.44秒