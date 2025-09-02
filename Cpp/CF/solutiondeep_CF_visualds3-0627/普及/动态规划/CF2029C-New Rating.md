# 题目信息

# New Rating

## 题目描述

Hello, Codeforces Forcescode!





Kevin used to be a participant of Codeforces. Recently, the KDOI Team has developed a new Online Judge called Forcescode.

Kevin has participated in $ n $ contests on Forcescode. In the $ i $ -th contest, his performance rating is $ a_i $ .

Now he has hacked into the backend of Forcescode and will select an interval $ [l,r] $ ( $ 1\le l\le r\le n $ ), then skip all of the contests in this interval. After that, his rating will be recalculated in the following way:

- Initially, his rating is $ x=0 $ ;
- For each $ 1\le i\le n $ , after the $ i $ -th contest, 
  - If $ l\le i\le r $ , this contest will be skipped, and the rating will remain unchanged;
  - Otherwise, his rating will be updated according to the following rules: 
      - If $ a_i>x $ , his rating $ x $ will increase by $ 1 $ ;
      - If $ a_i=x $ , his rating $ x $ will remain unchanged;
      - If $ a_i<x $ , his rating $ x $ will decrease by $ 1 $ .

You have to help Kevin to find his maximum possible rating after the recalculation if he chooses the interval $ [l,r] $ optimally. Note that Kevin has to skip at least one contest.

## 说明/提示

In the first test case, Kevin must skip at least one contest. If he chooses any interval of length $ 1 $ , his rating after the recalculation will be equal to $ 5 $ .

In the second test case, Kevin's optimal choice is to select the interval $ [3,5] $ . During the recalculation, his rating changes as follows:

 $ $$$ 0 \xrightarrow{a_1=1} 1 \xrightarrow{a_2=2} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{\mathtt{skip}} 2 \xrightarrow{a_6=3} 3 \xrightarrow{a_7=4} 4  $ $ </p><p>In the third test case, Kevin must skip the only contest, so his rating will remain at the initial value of  $ 0 $ .</p><p>In the fourth test case, Kevin's optimal choice is to select the interval  $ \[7,9\] $ . During the recalculation, his rating changes as follows:</p><p> $ $  0 \xrightarrow{a_1=9} 1 \xrightarrow{a_2=9} 2 \xrightarrow{a_3=8} 3 \xrightarrow{a_4=2} 2 \xrightarrow{a_5=4} 3 \xrightarrow{a_6=4} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4 \xrightarrow{\mathtt{skip}} 4  $ $ </p><p>In the fifth test case, Kevin's optimal choice is to select the interval  $ \[5,9\]$$$.

## 样例 #1

### 输入

```
5
6
1 2 3 4 5 6
7
1 2 1 1 1 3 4
1
1
9
9 9 8 2 4 4 3 5 3
10
1 2 3 4 1 3 2 1 1 10```

### 输出

```
5
4
0
4
5```

# AI分析结果



0. **题目翻译**

# 新评分系统

## 题目描述

Kevin 曾经是 Codeforces 的参赛者。最近 KDOI 团队开发了一个新的在线评测平台 Forcescode。

Kevin 在 Forcescode 上参加了 $n$ 场比赛。在第 $i$ 场比赛中，他的表现为 $a_i$ 分。

现在他黑入了平台后台，可以选择一个区间 $[l,r]$（$1\le l\le r\le n$），跳过该区间内的所有比赛。评分将按以下规则重新计算：

- 初始评分 $x=0$
- 遍历每场比赛 $1\le i\le n$：
  - 若 $l\le i\le r$，跳过比赛，评分不变
  - 否则：
    - 若 $a_i > x$，评分 $x$ 加 1
    - 若 $a_i = x$，评分不变
    - 若 $a_i < x$，评分 $x$ 减 1

求通过选择最优区间 $[l,r]$ 能获得的最大可能评分（必须跳过至少一个比赛）。

## 输入输出样例

（样例说明保持原题内容，此处略）

---

1. **唯一算法分类**  
线性DP

---

2. **综合分析与结论**

### 核心思路
通过动态规划维护两种状态：
- `dp[i][0]`：前i场比赛未跳过任何区间的最大评分
- `dp[i][1]`：前i场比赛已跳过某区间的最大评分

### 状态转移方程
```python
# 未跳过区间的情况
if a[i] > dp[i-1][0]:
    dp[i][0] = dp[i-1][0] + 1
elif a[i] == dp[i-1][0]:
    dp[i][0] = dp[i-1][0]
else:
    dp[i][0] = dp[i-1][0] - 1

# 已跳过区间的情况（从之前任意位置跳跃到当前）
max_pre = max(max_pre, dp[i-2][0])
dp[i][1] = max(
    # 延续之前的跳跃状态
    (dp[i-1][1] ±1 根据a[i]比较结果),
    # 从新的跳跃点转移
    max_pre ±1 根据a[i]比较结果
)
```

### 关键难点
- **跳跃点的最优选择**：需要维护前缀最大值来优化转移
- **状态定义**：区分是否已经使用过跳跃机会
- **边界处理**：处理跳跃起始点的初始状态

### 可视化设计
1. **DP矩阵网格**：用Canvas绘制二维网格，列表示比赛场次，行表示评分值
2. **颜色标记**：
   - 绿色：当前更新的`dp[i][0]`
   - 蓝色：当前更新的`dp[i][1]`
   - 红色：维护的前缀最大值位置
3. **音效设计**：
   - "叮"声：成功更新最大值
   - "嘟"声：评分下降
4. **自动演示模式**：按比赛场次逐步推进，展示评分变化轨迹

---

3. **题解清单 (≥4星)**

1. **chen_z（5星）**
   - 亮点：线性时间复杂度，优雅维护前缀最大值
   - 关键代码：
     ```cpp
     maxn = max(maxn, dp[i-2][0]);
     dp[i][1] = max(dp[i][1], maxn ±1 根据a[i]);
     ```

2. **Super_Cube（4星）**
   - 亮点：三状态定义清晰，代码简洁
   - 状态转移：
     ```cpp
     dp[i][0] = calc(dp[i-1][0],a[i]);
     dp[i][1] = max(dp[i-1][0], dp[i-1][1]);
     ```

3. **Exp10re（4星）**
   - 亮点：逆向思维预处理，创新性二分验证
   - 关键思路：
     ```cpp
     bool chk(int x) { 
        逆向模拟评分是否可达x
     }
     ```

---

4. **核心代码实现**

chen_z 题解的关键片段：
```cpp
for(int i=1;i<=n;i++){
    // 处理未跳跃状态
    if(a[i]>dp[i-1][0]) dp[i][0] = dp[i-1][0]+1;
    else if(a[i]==dp[i-1][0]) dp[i][0] = dp[i-1][0];
    else dp[i][0] = dp[i-1][0]-1;
    
    // 处理已跳跃状态
    if(i>1) maxn = max(maxn, dp[i-2][0]);
    int temp = maxn;
    if(a[i] > temp) temp += 1;
    else if(a[i] < temp) temp -= 1;
    dp[i][1] = max(dp[i][1], temp);
}
```

---

5. **同类型题推荐**

1. [LeetCode 121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)  
   （单次交易最优决策）

2. [洛谷 P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
   （线性DP维护连续子序列）

3. [Codeforces 455A Boredom](https://codeforces.com/problemset/problem/455/A)  
   （带状态选择的线性DP）

---

6. **可视化代码片段（Canvas动画）**

```javascript
// 初始化DP网格
const canvas = document.getElementById('dp-grid');
const ctx = canvas.getContext('2d');

function drawDPGrid(n, maxRating) {
    // 绘制网格线
    ctx.strokeStyle = '#888';
    for(let i=0; i<=n; i++) {
        ctx.beginPath();
        ctx.moveTo(i*50, 0);
        ctx.lineTo(i*50, maxRating*50);
        ctx.stroke();
    }
    // 高亮当前状态
    function highlightCell(i, r, color) {
        ctx.fillStyle = color;
        ctx.fillRect(i*50, (maxRating-r)*50, 50, 50);
    }
}
```

---

7. **个人心得摘录**

> "调试时发现，必须单独处理跳跃区间长度为1的特殊情况，否则会漏掉最优解。通过维护前缀最大值而不是遍历历史状态，是降低复杂度的关键。" —— chen_z

> "最初尝试二维前缀数组导致内存超限，改用滚动变量后效率显著提升。" —— Exp10re

---

8. **复古游戏化设计**

```javascript
// 8位音效生成器
function playSound(type) {
    const osc = audioContext.createOscillator();
    const gainNode = audioContext.createGain();
    osc.connect(gainNode);
    
    if(type === 'jump') { // 跳跃音效
        osc.frequency.setValueAtTime(523.25, audioContext.currentTime);
        gainNode.gain.setValueAtTime(0.3, audioContext.currentTime);
    } 
    // ...其他音效设置
    
    osc.start();
    osc.stop(audioContext.currentTime + 0.1);
}

// 像素动画更新
function updatePixelAnimation(step) {
    const sprite = document.getElementById('dp-sprite');
    sprite.style.left = step*50 + 'px'; // 横向移动表示比赛进程
}
```

---
处理用时：83.10秒