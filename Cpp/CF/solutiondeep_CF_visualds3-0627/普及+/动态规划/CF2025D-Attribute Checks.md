# 题目信息

# Attribute Checks

## 题目描述

Imagine a game where you play as a character that has two attributes: "Strength" and "Intelligence", that are at zero level initially.

During the game, you'll acquire $ m $ attribute points that allow you to increase your attribute levels — one point will increase one of the attributes by one level. But sometimes, you'll encounter a so-called "Attribute Checks": if your corresponding attribute is high enough, you'll pass it; otherwise, you'll fail it.

Spending some time, you finally prepared a list which contains records of all points you got and all checks you've met. And now you're wondering: what is the maximum number of attribute checks you can pass in a single run if you'd spend points wisely?

Note that you can't change the order of records.

## 说明/提示

In the first test, it's optimal to spend each point in Strength, so you'll fail $ 2 $ Intelligence checks but pass $ 3 $ Strength checks.

In the second test, you'll fail both checks, since the first point you get comes after the checks.

In the third test, one of the optimal strategies is:

1. spend the first point on Intelligence;
2. spend the second point on Strength;
3. spend the third point on Strength;

 As a result, you'll pass $ 2 $ Intelligence checks $ r_3 $ and $ r_9 $ and $ 2 $ Strength checks $ r_7 $ and $ r_8 $ .

## 样例 #1

### 输入

```
10 5
0 1 0 2 0 -3 0 -4 0 -5```

### 输出

```
3```

## 样例 #2

### 输入

```
3 1
1 -1 0```

### 输出

```
0```

## 样例 #3

### 输入

```
9 3
0 0 1 0 2 -3 -2 -2 1```

### 输出

```
4```

# AI分析结果



---

## 题目翻译

# 属性检查

## 题目描述

想象你扮演一个初始属性值为零（"力量"和"智力"）的游戏角色。游戏中你将获得 $ m $ 个属性点，每个属性点可以提升力量或智力 1 级。过程中会遇到"属性检查"：若对应属性达标则通过检查，否则失败。

你整理了一个包含所有属性点获取和检查事件的序列，求通过最大化检查次数的策略。

## 说明/提示

样例1解释：最优策略将所有属性点分配给力量，通过3次力量检查，失败2次智力检查。

样例2解释：所有检查都在获得第一个属性点之前发生，无法通过任何检查。

样例3解释：分配策略为智力+1、力量+2，通过2次智力检查和2次力量检查。

## 样例 #1

### 输入

```
10 5
0 1 0 2 0 -3 0 -4 0 -5
```

### 输出

```
3
```

---

## 唯一算法分类
线性DP

---

## 综合分析与结论

### 核心思路与难点
1. **状态压缩**：通过滚动数组将二维DP压缩为一维
2. **差分优化**：利用差分数组处理区间加减操作，将$O(nm)$复杂度优化为$O(m^2)$
3. **暴力转移**：遇到属性点分配时（r=0）暴力处理max操作，维护正确的DP状态

### 关键状态转移方程
```cpp
// 处理检查时（r≠0）
if(r > 0): dp[x] += 1  (x >= r)
if(r < 0): dp[x] += 1  (x <= total_points + r)

// 处理属性点分配时（r=0）
for j from current_points downto 1:
    dp[j] = max(dp[j], dp[j-1])
```

### 可视化设计要点
1. **像素风格展示**：
   - 使用16色系（#FF0000红/#00FF00绿/#0000FF蓝为主色调）
   - Canvas绘制DP数组为方格矩阵，每个格子显示当前得分
2. **动画效果**：
   - 红框高亮当前处理的序列元素
   - 蓝框标记正在更新的DP区间
   - 绿色闪烁表示得分增加
3. **音效系统**：
   - "哔"声表示属性点分配
   - "叮"声表示检查通过
   - 8-bit风格背景音乐循环播放

---

## 题解清单（4星及以上）

### 1. Super_Cube（5星）
**亮点**：
- 差分数组与暴力转移的完美结合
- 代码精简（仅30行）且效率最优
- 滚动数组实现空间复杂度O(m)

**核心代码**：
```cpp
if(x==0){
    ++s;dp[0]+=d[0];
    for(int j=1;j<=s;++j)dp[j]+=(d[j]+=d[j-1]);
    for(int j=s;j;--j)dp[j]=std::max(dp[j],dp[j-1]);
    memset(d,0,s+1<<2);
}
```

### 2. Phrvth（4星）
**亮点**：
- 完整的状态转移理论推导
- 线段树优化思路的可行性分析
- 清晰的滚动数组实现说明

---

## 核心代码实现

### 差分优化+暴力转移
```cpp
int dp[5005], d[5005];
for(int i=1,x,s=0;i<=n;++i){
    scanf("%d",&x);
    if(x>0){ // 智力检查
        if(x<=s) ++d[x], --d[s+1];
    }else if(x){ // 力量检查 
        if(0<=s+x) ++d[0], --d[s+x+1];
    }else{ // 属性点分配
        ++s;
        dp[0] += d[0];
        for(int j=1;j<=s;j++) dp[j] += (d[j]+=d[j-1]);
        for(int j=s;j;j--) dp[j] = max(dp[j],dp[j-1]);
        memset(d,0,sizeof(int)*(s+2));
    }
}
```

---

## 相似题目推荐
1. **P1091 合唱队形**（线性DP+双向LIS）
2. **P1944 最长括号匹配**（区间DP+栈优化）
3. **P1541 乌龟棋**（多维线性DP+滚动数组）

---

## 可视化代码片段（Canvas绘制DP状态）
```javascript
function drawDP() {
    ctx.clearRect(0,0,canvas.width,canvas.height);
    for(let j=0; j<=currentPoints; j++) {
        ctx.fillStyle = getColor(dp[j]); // 根据得分值映射颜色
        ctx.fillRect(20+j*50, 100, 45, 45);
        ctx.fillText(dp[j], 30+j*50, 130);
    }
    // 高亮当前操作
    if(currentOpType == 'CHECK') {
        ctx.strokeStyle = '#FF0000';
        ctx.strokeRect(20+currentCheckValue*50, 100, 45, 45);
    }
}
```

---

## 调试心得摘录
> "最初尝试用树状数组维护max操作，发现无法处理转移中的取max操作，最终回归暴力转移+差分的组合，这是本题的关键突破点" —— litjohn

---

## 算法演示控制面板
```html
<div class="control-panel">
    <button onclick="stepBack()">← 回退</button>
    <input type="range" id="speed" min="100" max="2000" value="500">
    <button onclick="togglePlay()">▶/⏸</button>
    <button onclick="stepNext()">前进 →</button>
</div>
<style>
.control-panel {
    background: #8B8B83;
    padding: 10px;
    border-radius: 8px;
    box-shadow: 2px 2px #404038;
}
</style>
```

---
处理用时：74.67秒