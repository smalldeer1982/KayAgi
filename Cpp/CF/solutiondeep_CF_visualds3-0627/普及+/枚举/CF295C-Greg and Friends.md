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



## 唯一算法分类：动态规划（状态转移与组合数学结合）

---

### 综合分析与结论

**核心思路**：  
- **状态设计**：以当前岸剩余人数（50kg、100kg）与船的位置为状态，结合过程次数奇偶性区分往返方向。  
- **组合数学**：预处理组合数，每次转移计算不同人数组合的方案数贡献。  
- **最短次数**：动态规划按步骤递增，找到第一个合法状态即为最小次数。

**难点与解决**：  
1. **状态转移方向**：通过奇偶性确定是运送过去还是返回，枚举满足载重条件的组合。  
2. **方案数计算**：组合数相乘累加，确保乘法原理正确应用。  
3. **无解判定**：设定最大尝试次数（如4n），超过则判定无解。

**可视化设计**：  
- **状态网格**：用Canvas绘制出发岸与对岸的人数网格，50kg/100kg以不同颜色方块表示。  
- **船动画**：箭头指示移动方向，每次转移高亮船上乘客方块。  
- **音效**：成功运送时播放8-bit音效，失败时低沉音效。  
- **自动演示**：按步骤播放最优解的运送过程，可调节速度观察状态变化。

---

### 题解清单（≥4星）

1. **gesong（5星）**  
   - **亮点**：状态设计清晰，奇偶性区分往返，组合数预处理高效。  
   - **代码**：结构简洁，预处理组合数避免重复计算，快速找到最优解。

2. **zztqwq（4星）**  
   - **亮点**：三维状态记录船位置，转移方程直观，组合数动态计算。  
   - **优化**：使用滚动数组减少内存消耗。

3. **SevenDawns（4星）**  
   - **亮点**：BFS结合状态转移，直观模拟运送过程，适合教学演示。  
   - **心得**：提到“步数相同时需累加方案数”，避免遗漏合法路径。

---

### 核心代码实现（以gesong题解为例）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=60,mod=1e9+7;
int f[4*N][N][N],C[N][N],x,y,n,m;

main(){
    // 预处理组合数
    C[0][0]=1;
    for(int i=1;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=n;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    
    // 动态规划转移
    f[0][x][y]=1;
    for(int i=1;i<=4*n;i++)
        for(int j=0;j<=x;j++)
            for(int k=0;k<=y;k++){
                if(i&1){ // 运到对岸
                    for(int a=0;a<=x-j;a++)
                    for(int b=0;b<=y-k;b++)
                        if(a+b>0 && 50*a+100*b<=m)
                            f[i][j][k]=(f[i][j][k] + f[i-1][j+a][k+b]*C[j+a][a]%mod*C[k+b][b]%mod)%mod;
                    if(f[i][0][0]) return 0; // 找到最优解
                } else { // 返回出发岸
                    for(int a=0;a<=j;a++)
                    for(int b=0;b<=k;b++)
                        if(a+b>0 && 50*a+100*b<=m)
                            f[i][j][k]=(f[i][j][k] + f[i-1][j-a][k-b]*C[x-j+a][a]%mod*C[y-k+b][b]%mod)%mod;
                }
            }
}
```

**实现思想**：  
- **组合数预处理**：C[i][j]存储组合数C(i,j)的模值。  
- **状态转移**：按奇偶步数枚举运送/返回的人数组合，累加方案数。  
- **及时终止**：发现f[i][0][0]不为零时立即输出最优解。

---

### 同类型题与拓展

1. **过河问题变种**：如《狼羊菜过河》，需处理状态约束。  
2. **最短路径计数**：如迷宫中的最短路径方案数，结合BFS与DP。  
3. **组合优化问题**：如背包问题中求方案数，动态规划与组合结合。

---

### 推荐相似题目

1. **P1004 方格取数**（动态规划状态设计）  
2. **P3956 棋盘**（BFS与状态转移结合）  
3. **P1433 吃奶酪**（状态压缩动态规划）

---

### 可视化与游戏化设计

**复古像素动画**：  
- **Canvas绘制**：  
  - 左岸/右岸用不同背景色区分，50kg用绿色方块，100kg用红色方块。  
  - 船用8-bit风格小船图标，移动时添加水波动画。  
- **音效设计**：  
  - 运送成功：短促“叮”声（Web Audio合成）。  
  - 无解：低沉“哔”声。  
- **自动演示模式**：  
  - 按最优解步骤自动播放，可暂停/加速，显示当前运送人数组合。  

**交互示例**：  
```javascript
// 伪代码：船移动动画
function animateStep(step) {
    highlightBoat();
    playSound('move');
    updateShoreColors(fromShore, toShore);
    setTimeout(() => nextStep(), speed);
}
```

---

### 个人心得摘录

> “**组合数的预处理是关键**，否则每次计算会超时。在状态转移时，特别注意奇偶步的方向差异，否则会错误累加方案数。” —— gesong题解调试经验

> “**BFS中的状态去重需要特殊处理**，同一状态可能以不同步数到达，需保留最小步数的方案数。” —— SevenDawns代码注释

---
处理用时：144.17秒