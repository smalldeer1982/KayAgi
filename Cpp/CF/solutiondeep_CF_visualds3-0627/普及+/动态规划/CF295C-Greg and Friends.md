# 题目信息

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
3 100
50 50 100
```

### 输出

```
5
2
```

## 样例 #3

### 输入

```
2 50
50 50
```

### 输出

```
-1
0
```

# AI分析结果



# 中文题目重写

## 题目描述

某日，Greg 和他的朋友们在森林中散步。总共有 $n$ 个人（包括 Greg）。他们来到一条河边，发现岸边有一条最多可承载 $k$ 公斤的小船。已知每个人的体重只能是 50 或 100 公斤，求将所有人运送到对岸所需的最小船次，以及对应最小船次的方案数（两种方案不同当且仅当某次乘船的人员集合不同）。若无解则输出 `-1 0`。

## 输入格式

第一行两个整数 $n$ 和 $k$  
第二行 $n$ 个整数（每个为 50 或 100）表示各人体重

## 输出格式

若可运送，输出两行：最小次数和方案数；否则输出 `-1` 和 `0`

## 样例

### 样例 1
输入：
```
1 50
50
```
输出：
```
1
1
```

### 样例 2
输入：
```
3 100
50 50 100
```
输出：
```
5
2
```

### 样例 3
输入：
```
2 50
50 50
```
输出：
```
-1
0
```

---

# 算法分类：线性DP

# 综合分析与结论

## 核心思路与难点
1. **状态设计**：以对岸剩余人数为状态维度  
   gesong 题解采用 $f_{i,j,k}$ 表示第 $i$ 个过程结束时，出发岸剩余 $j$ 个50kg、$k$ 个100kg 的方案数，利用奇偶性区分往返方向  
   zztqwq 使用双岸状态 $f(pos,j,k)$ 记录船的位置和对岸人数  

2. **状态转移**：  
   - **正向运输**（奇数步）：从出发岸选 $a$ 个50kg和 $b$ 个100kg组合  
     $$f_{i,j,k} += C_{剩余50}^a \times C_{剩余100}^b \times f_{i-1,j+a,k+b}$$  
   - **返程运输**（偶数步）：从对岸选人返回，组合数取出发岸剩余人数  
     $$f_{i,j,k} += C_{已到对岸50}^a \times C_{已到对岸100}^b \times f_{i-1,j-a,k-b}$$  

3. **组合数预处理**：  
   所有题解均预计算组合数 $C_n^k$ 以快速处理人员选择方式  

## 可视化设计
1. **动态矩阵展示**：  
   - 使用双层网格表示两岸人数状态，红色高亮当前更新的单元格  
   - 船图标在两岸间滑动，运输时显示选中的人员组合  

2. **复古像素风格**：  
   - 16色调色板：深蓝表示出发岸，绿色表示对岸，黄色闪烁标记有效转移  
   - 8-bit 音效：  
     - "叮" 声表示有效状态转移  
     - 长音效提示找到最优解  

3. **自动演示模式**：  
   - AI 自动枚举所有可能的人员组合，优先探索最小步数路径  
   - 连击奖励机制：连续找到有效转移时获得加速效果  

---

# 题解清单（≥4星）

## gesong（⭐⭐⭐⭐⭐）
**亮点**：  
- 状态定义清晰，利用过程奇偶性自然区分往返阶段  
- 组合数预处理与模运算处理规范  
- 代码结构分层明确，易读性强  

关键代码段：
```cpp
for(int i=1;i<=4*n;i++) {
    if(i&1){ // 正向运输
        for(int a=0; a<=剩余50; a++)
        for(int b=0; b<=剩余100; b++)
            f[i][j][k] += C[...] * f[i-1][...];
    } else { // 返程
        for(int a=0; a<=对岸50; a++)
        for(int b=0; b<=对岸100; b++)
            f[i][j][k] += C[...] * f[i-1][...];
    }
}
```

## zztqwq（⭐⭐⭐⭐）
**亮点**：  
- 双岸状态设计直观反映物理位置  
- 使用位运算加速奇偶判断  
- 完整处理模运算避免溢出  

**调试心得**：  
_"最初未考虑返程时组合数的选取方式，通过绘制状态转移图发现错误"_  

---

# 核心代码实现

gesong 题解状态转移核心：
```cpp
// 预处理组合数
for(int i=0;i<=n;i++) 
    C[i][0] = 1;
    for(int j=1;j<=i;j++) 
        C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;

// 主转移逻辑
for(int i=1; i<=max_step; i++){
    if(i%2 == 1){ // 去程
        for(int a : 可选50)
        for(int b : 可选100)
            dp[i][j][k] += C[剩余50][a] * C[剩余100][b] * dp_prev;
    } else { // 返程
        for(int a : 返回50) 
        for(int b : 返回100)
            dp[i][j][k] += C[对岸50][a] * C[对岸100][b] * dp_prev;
    }
}
```

---

# 相似题目推荐
1. **P1049 装箱问题** - 容量限制下的组合优化  
2. **P1064 金明的预算方案** - 状态压缩动态规划  
3. **P1156 垃圾陷阱** - 时间维度线性DP  

# 可视化代码片段（Canvas 绘制）
```javascript
// 绘制状态网格
function drawDPGrid(ctx, state) {
    const colors = ["#2c3e50", "#e74c3c", "#2ecc71"];
    for(let i=0; i<=max50; i++){
        for(let j=0; j<=max100; j++){
            const alpha = Math.log(state[i][j]+1)/10;
            ctx.fillStyle = `rgba(46, 204, 113, ${alpha})`;
            ctx.fillRect(i*30, j*30, 28, 28);
        }
    }
}

// 音效触发器
function playSound(type) {
    if(type === 'move') beep(440, 50);
    if(type === 'solve') beep(880, 500);
}
```

---
处理用时：93.19秒