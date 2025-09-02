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



**唯一算法分类**  
动态规划（状态转移与组合数学结合）

---

### **综合分析与结论**  
**核心思路**：  
题目要求最少渡河次数及对应方案数，需考虑每次运送的合法组合（总重量≤k）及不同选择的组合数。核心算法为动态规划，状态需记录当前两岸的人数及船的位置，通过奇偶步骤区分运送方向，结合组合数学计算方案数。

**难点与解决方案**：  
1. **状态建模**：需记录当前岸的50kg和100kg人数，以及船的位置（出发岸或对岸）。  
2. **方向区分**：奇数步骤为运送到对岸，偶数步骤为返回，分别处理不同方向的人员选择。  
3. **组合数计算**：每次选择的人员组合需乘以组合数，确保方案数的正确累积。  

**可视化设计**：  
- **像素动画**：用方格表示两岸人数，绿色为50kg，红色为100kg，船用箭头图标动态移动。  
- **高亮操作**：当前运送的人员方格闪烁，船移动时播放划船音效，成功时播放胜利音效。  
- **交互控制**：支持暂停、步进、自动播放（速度可调），Canvas 动态更新状态。  

---

### **题解清单 (≥4星)**  
1. **gesong（4星）**  
   - **亮点**：清晰区分奇偶步骤，动态规划状态转移简洁，代码结构清晰。  
   - **代码可读性**：预处理组合数，循环嵌套合理。  

2. **zztqwq（4星）**  
   - **亮点**：将船的位置纳入状态，状态转移逻辑直观，预处理逆元优化组合数计算。  
   - **优化点**：使用模逆元加速组合数取模，适合大规模数据。  

3. **SevenDawns（4星）**  
   - **亮点**：BFS 结合动态规划，优先搜索最短路径，适合状态空间较小的情况。  
   - **交互性**：队列模拟广搜，实时更新最短步数。  

---

### **核心代码实现**  
```cpp
// 以 gesong 的代码为例（关键部分）
int f[4*N][N][N], C[N][N], x, y, n, m;

// 预处理组合数
C[0][0] = 1;
for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= n; j++)
        C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
}

// 动态规划转移
for (int i = 1; i <= 4*n; i++) {
    for (int j = 0; j <= x; j++) {
        for (int k = 0; k <= y; k++) {
            if (i % 2 == 1) { // 运送到对岸
                for (int a = 0; a <= x-j; a++) {
                    for (int b = 0; b <= y-k; b++) {
                        if (50*a + 100*b > m || (a==0 && b==0)) continue;
                        f[i][j][k] += f[i-1][j+a][k+b] * C[j+a][a] * C[k+b][b];
                    }
                }
            } else { // 返回出发岸
                for (int a = 0; a <= j; a++) {
                    for (int b = 0; b <= k; b++) {
                        if (50*a + 100*b > m || (a==0 && b==0)) continue;
                        f[i][j][k] += f[i-1][j-a][k-b] * C[x-j+a][a] * C[y-k+b][b];
                    }
                }
            }
        }
    }
}
```

---

### **同类型题与套路**  
- **通用解法**：状态动态规划 + 组合数学，适用于需计数且状态转移涉及选择组合的问题。  
- **类似题目**：  
  1. **洛谷 P1044 [过河卒](https://www.luogu.com.cn/problem/P1002)**（动态规划 + 路径计数）  
  2. **洛谷 P1025 [数的划分](https://www.luogu.com.cn/problem/P1025)**（组合数 + 动态规划）  
  3. **洛谷 P1077 [摆花](https://www.luogu.com.cn/problem/P1077)**（有限制条件的组合计数）  

---

### **复古游戏化动画设计**  
- **像素风格**：8-bit 色调，方格代表人员，船为 16x16 像素图标。  
- **Canvas 动画**：  
  - 初始化两岸人数，船在左侧，点击“开始”后自动执行步骤。  
  - 每次运送时，高亮选中方格，船移动动画伴随划船音效。  
- **音效设计**：  
  - 划船音效：`beep` 短音（Web Audio API 生成）。  
  - 成功音效：8-bit 胜利旋律，失败时播放低沉音效。  
- **交互功能**：滑动条调节动画速度，按钮控制暂停/继续。  

```javascript
// 伪代码：Canvas 绘制人员方格
function drawPeople(ctx, x, y, count50, count100) {
    // 绘制 50kg 人员（绿色方块）
    for (let i = 0; i < count50; i++) {
        ctx.fillStyle = '#00FF00';
        ctx.fillRect(x + i*10, y, 8, 8);
    }
    // 绘制 100kg 人员（红色方块）
    for (let i = 0; i < count100; i++) {
        ctx.fillStyle = '#FF0000';
        ctx.fillRect(x + i*10, y + 10, 8, 8);
    }
}
```

---
处理用时：82.00秒