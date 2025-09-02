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



---
# 💡 Kay的C++算法解析：Greg and Friends 深入学习指南 💡

<introduction>
今天我们来一起分析“Greg and Friends”这道C++编程题。题目要求我们计算一群人（体重只有50kg或100kg）用一艘载重有限的船过河所需的最少次数，以及对应的方案数。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：动态规划(DP) 结合状态转移

🗣️ **初步分析**：
解决这道题的关键在于用动态规划（DP）跟踪不同时间点两岸的人数状态（50kg和100kg的数量）及船的位置，从而找到最少渡河次数和方案数。动态规划就像“记录每一步的可能状态”，比如“现在出发岸有a个50kg和b个100kg，船在出发岸”，然后通过状态转移推导出下一步的状态。

- **题解思路**：多数题解采用三维DP数组，记录“第i次过程后剩余j个50kg、k个100kg的方案数”，或“船在pos岸时对岸有j个50kg、k个100kg的方案数”。核心是枚举每次乘船的人数（50kg和100kg的组合），满足载重限制，并通过组合数计算方案数。
- **核心难点**：状态定义需同时考虑船的位置和剩余人数；状态转移需枚举所有可能的乘船组合（非零且总重≤k）；方案数计算需结合组合数（选择哪些人上船）。
- **可视化设计**：采用8位像素风格动画，用不同颜色像素块区分50kg（绿色）和100kg（红色）的人，船（蓝色方块）在两岸移动。动画中高亮当前乘船的人，显示剩余人数和船的位置，关键步骤（如到达对岸）伴随“叮”的音效，自动播放时模拟“最优路径”演示。

---

## 2. 精选优质题解参考

<eval_intro>
经过对思路清晰度、代码规范性、算法有效性等维度的评估，以下两道题解因逻辑清晰、代码规范且高效，被选为优质参考（评分≥4星）：
</eval_intro>

**题解一：gesong（来源：洛谷题解）**
* **点评**：此题解思路非常清晰，状态定义为`f[i][j][k]`（第i次过程后，出发岸剩余j个50kg、k个100kg的方案数），转移逻辑明确区分“去对岸”和“返回”两种情况。代码规范（如预处理组合数表`C`，变量名含义明确），边界条件处理严谨（初始状态`f[0][x][y]=1`），且通过枚举过程数（最多`4n`次）确保效率。实践价值高，可直接用于竞赛。

**题解二：zztqwq（来源：独立题解）**
* **点评**：此题解状态定义为`f[pos][j][k]`（船在pos岸，对岸有j个50kg、k个100kg的方案数），更直观体现船的位置变化。代码结构简洁（使用位运算`i&1`切换状态），组合数计算通过预处理阶乘和逆元实现，效率高。转移逻辑覆盖所有可能的乘船组合，边界条件处理正确（初始状态`f[0][0][0]=1`），适合学习状态转移与组合数结合的技巧。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这道题的过程中，我们通常会遇到以下核心难点。结合优质题解的共性，我们提炼出关键策略：
</difficulty_intro>

1.  **关键点1：状态的定义**
    * **分析**：状态需同时记录“剩余在出发岸的50kg和100kg人数”及“船的位置”。例如，`f[i][j][k]`中`i`表示过程次数，`j`和`k`表示剩余人数，船的位置由`i`的奇偶性决定（奇数为到对岸，偶数为返回）。这样定义能覆盖所有可能的转移路径。
    * 💡 **学习笔记**：状态定义需包含“影响后续决策的所有关键信息”，本题中船的位置和剩余人数是核心。

2.  **关键点2：状态转移的条件**
    * **分析**：每次乘船的人数必须非零（至少1人），且总重量≤k。需枚举所有可能的50kg人数`c5`和100kg人数`c1`，满足`50*c5 + 100*c1 ≤k`。例如，去对岸时，出发岸剩余人数减少`c5`和`c1`；返回时，出发岸剩余人数增加`c5`和`c1`（因船从对岸带回人）。
    * 💡 **学习笔记**：状态转移需严格检查约束条件（非零、载重限制），避免无效状态。

3.  **关键点3：方案数的计算**
    * **分析**：方案数需计算“从当前剩余的人中选择`c5`个50kg和`c1`个100kg”的方式数，这需要预处理组合数表。例如，去对岸时，选择方式为`C[j+a][a] * C[k+b][b]`（`j+a`是出发岸原有人数）。
    * 💡 **学习笔记**：组合数预处理能显著提高计算效率，是处理“选择问题”的常用技巧。

### ✨ 解题技巧总结
- **状态压缩**：用奇偶性表示船的位置（如`i&1`），减少状态维度。
- **组合数预处理**：提前计算组合数表，避免重复计算，提升效率。
- **边界条件优先**：初始状态（所有人在出发岸）和终止状态（所有人到对岸）需明确，避免逻辑错误。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个能够完整解决本题的通用核心C++实现参考。这有助于我们对整体解题框架有一个把握。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了gesong和zztqwq的题解思路，采用三维DP数组记录过程次数、剩余人数及方案数，预处理组合数表，逻辑清晰且高效。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MOD = 1e9 + 7, N = 60;
    int f[4 * N][N][N], C[N][N]; // f[i][j][k]表示第i次过程后，出发岸剩余j个50kg、k个100kg的方案数
    int n, k, x, y; // x:50kg人数，y:100kg人数

    int main() {
        cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            int w; cin >> w;
            if (w == 50) x++;
            else y++;
        }
        k /= 50; // 转换为50kg单位，简化计算（100kg=2单位）

        // 预处理组合数表
        C[0][0] = 1;
        for (int i = 1; i < N; ++i) {
            C[i][0] = 1;
            for (int j = 1; j <= i; ++j)
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }

        f[0][x][y] = 1; // 初始状态：0次过程，所有人在出发岸
        for (int i = 1; i <= 4 * n; ++i) {
            for (int j = 0; j <= x; ++j) {
                for (int l = 0; l <= y; ++l) {
                    if (i % 2 == 1) { // 奇数过程：去对岸，出发岸减少c5和c1
                        for (int c5 = 0; c5 <= x - j; ++c5) {
                            for (int c1 = 0; c1 <= y - l; ++c1) {
                                if (c5 + 2 * c1 == 0 || c5 + 2 * c1 > k) continue; // 非零且载重≤k
                                f[i][j + c5][l + c1] = (f[i][j + c5][l + c1] + 
                                    1LL * f[i - 1][j][l] * C[x - j][c5] % MOD * C[y - l][c1] % MOD) % MOD;
                            }
                        }
                    } else { // 偶数过程：返回，出发岸增加c5和c1（船从对岸带回）
                        for (int c5 = 0; c5 <= j; ++c5) {
                            for (int c1 = 0; c1 <= l; ++c1) {
                                if (c5 + 2 * c1 == 0 || c5 + 2 * c1 > k) continue;
                                f[i][j - c5][l - c1] = (f[i][j - c5][l - c1] + 
                                    1LL * f[i - 1][j][l] * C[j][c5] % MOD * C[l][c1] % MOD) % MOD;
                            }
                        }
                    }
                }
            }
            if (f[i][0][0]) { // 所有人到达对岸
                cout << i << "\n" << f[i][0][0] % MOD << endl;
                return 0;
            }
        }
        cout << "-1\n0" << endl; // 无解
        return 0;
    }
    ```
* **代码解读概要**：
    代码首先读取输入并统计50kg和100kg的人数，将载重转换为50kg单位（简化计算）。预处理组合数表`C`用于计算选择方式数。核心DP数组`f[i][j][k]`记录第`i`次过程后出发岸剩余`j`个50kg、`k`个100kg的方案数。通过遍历过程次数（最多`4n`次），根据过程奇偶性分别处理“去对岸”和“返回”的状态转移，最终检查是否所有人到达对岸（`f[i][0][0]`非零）。

---
<code_intro_selected>
接下来，我们将剖析优质题解的核心代码片段，点出各自的亮点和关键思路。
</code_intro_selected>

**题解一：gesong（来源：洛谷题解）**
* **亮点**：状态定义清晰，转移逻辑明确区分奇偶过程，组合数预处理高效。
* **核心代码片段**：
    ```cpp
    for (int i = 1; i <= 4 * n; i++)
        for (int j = 0; j <= x; j++)
            for (int k = 0; k <= min(y, n - j); k++) {
                if (i & 1) { // 去对岸
                    for (int a = 0; a <= x - j; a++)
                        for (int b = 0; b <= y - k; b++)
                            if (!(a == 0 && b == 0) && 50 * a + 100 * b <= m)
                                f[i][j][k] = (f[i][j][k] + f[i - 1][j + a][k + b] * C[j + a][a] % mod * C[k + b][b] % mod) % mod;
                    if (f[i][0][0]) { /* 输出结果 */ }
                } else { // 返回
                    for (int a = 0; a <= j; a++)
                        for (int b = 0; b <= k; b++)
                            if (!(a == 0 && b == 0) && 50 * a + 100 * b <= m)
                                f[i][j][k] = (f[i][j][k] + f[i - 1][j - a][k - b] * C[x - j + a][a] % mod * C[y - k + b][b] % mod) % mod;
                }
            }
    ```
* **代码解读**：
    这段代码是状态转移的核心。`i&1`判断当前过程是奇数（去对岸）还是偶数（返回）。去对岸时，枚举从出发岸带走的50kg人数`a`和100kg人数`b`，要求总重≤k且非零，方案数通过组合数`C[j+a][a]`（从原出发岸的`j+a`个50kg中选`a`个）计算。返回时类似，但枚举的是从对岸带回的人数，组合数计算基于对岸的剩余人数。
* 💡 **学习笔记**：奇偶过程的区分是关键，确保船的位置正确变化；组合数的正确应用是方案数计算的核心。

**题解二：zztqwq（来源：独立题解）**
* **亮点**：状态定义更直观（船的位置`pos`直接记录），使用位运算`i&1`切换状态，代码简洁。
* **核心代码片段**：
    ```cpp
    for(int i=1;i<=4*n;i++){
        for(int j=0;j<=tot5;j++)
            for(int k=0;k<=tot1;k++)
                f[i&1][j][k]=0;
        for(int j=0;j<=tot5;j++){
            for(int k=0;k<=tot1;k++){
                if(i&1){ // 去对岸（pos=1）
                    for(int c5=0;c5<=tot5-j;c5++){
                        for(int c1=0;c1<=tot1-k;c1++){
                            if(!c5&&!c1)continue;
                            if(50*c5+100*c1>K) continue;
                            f[1][j+c5][k+c1]=(f[1][j+c5][k+c1]+1LL*binom(tot5-j,c5)*binom(tot1-k,c1)%mod*f[0][j][k])%mod;
                        }
                    }
                } else { // 返回（pos=0）
                    for(int c5=0;c5<=j;c5++){
                        for(int c1=0;c1<=k;c1++){
                            if(!c5&&!c1)continue;
                            if(50*c5+100*c1>K) continue;
                            f[0][j-c5][k-c1]=(f[0][j-c5][k-c1]+1LL*binom(j,c5)*binom(k,c1)%mod*f[1][j][k])%mod;
                        }
                    }
                }
            }
        }
        if(f[i&1][tot5][tot1]){ /* 输出结果 */ }
    }
    ```
* **代码解读**：
    这段代码通过`i&1`切换船的位置（`pos=1`为去对岸，`pos=0`为返回）。`f[pos][j][k]`表示船在`pos`岸时，对岸有`j`个50kg、`k`个100kg的方案数。去对岸时，从出发岸带走`c5`和`c1`人，对岸人数增加；返回时，从对岸带回`c5`和`c1`人，对岸人数减少。组合数`binom`计算选择方式数，确保方案数正确。
* 💡 **学习笔记**：位运算简化了状态切换，使代码更简洁；明确“对岸人数”的变化是状态转移的关键。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了更直观地理解动态规划的状态转移过程，我们设计一个“像素过河小冒险”动画，用8位复古风格展示每次渡河的细节！
</visualization_intro>

  * **动画演示主题**：`像素过河小冒险`
  * **核心演示内容**：展示船从出发岸到对岸的往返过程，动态更新两岸的50kg（绿色方块）和100kg（红色方块）人数，高亮当前乘船的人，同步显示DP状态（剩余人数、过程次数、方案数）。
  * **设计思路简述**：8位像素风格（FC红白机色调）营造轻松氛围；关键步骤（如船移动、人数变化）伴随“叮”或“嘟嘟”音效，强化操作记忆；自动播放模式模拟最优路径，帮助学习者观察状态转移规律。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化**：
          - 屏幕分为左右两岸，用蓝色波浪线分隔。出发岸（左）显示所有50kg（绿）和100kg（红）的像素方块；对岸（右）初始为空。
          - 控制面板：单步/自动按钮、速度滑块（1-5倍速）、重置按钮。
          - 背景播放8位风格的轻快BGM（如《超级玛丽》经典旋律变奏）。

    2.  **过程开始**：
          - 初始状态：出发岸有`x`绿块、`y`红块，船（蓝色方块）在左岸边，显示“过程0：出发岸”。
          - 点击“开始”，动画进入自动播放模式，或通过“单步”逐次执行。

    3.  **去对岸（奇数过程）**：
          - 船从左岸出发，枚举可能的`c5`（绿块）和`c1`（红块）上船（如选2绿块）。
          - 上船的绿块和红块闪烁（黄色边框），伴随“唰”的音效，船载着它们向右岸移动（水平滑动动画）。
          - 到达右岸后，右岸新增`c5`绿块和`c1`红块，左岸减少对应数量，显示“过程1：到达对岸”，方案数更新（如`C[x][c5]*C[y][c1]`）。

    4.  **返回（偶数过程）**：
          - 船从右岸出发，枚举可能的`c5`（绿块）和`c1`（红块）下船（如选1绿块返回）。
          - 下船的绿块闪烁（粉色边框），船载着它们向左岸移动（水平滑动动画）。
          - 到达左岸后，左岸新增`c5`绿块和`c1`红块，右岸减少对应数量，显示“过程2：返回出发岸”。

    5.  **目标达成**：
          - 当左岸人数为0（所有块到右岸），船停在右岸，播放“胜利”音效（上扬的“叮铃”声），屏幕显示“最少次数：i”和“方案数：f[i][0][0]”。
          - 若超过`4n`次仍未完成，显示“无解”，播放短促“滴滴”提示音。

    6.  **交互提示**：
          - 单步模式下，每点击一次“下一步”，动画执行一个过程，同步高亮代码中的当前转移行（如`f[i][j][k] += ...`）。
          - 速度滑块调整动画流畅度（慢速适合观察细节，快速适合整体流程）。

<visualization_conclusion>
通过这样的像素动画，我们能直观看到每次渡河的人数变化、船的位置转移，以及方案数的累积过程，让抽象的动态规划状态“动起来”！
</visualization_conclusion>

-----

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的动态规划+状态转移思路，适用于多种“过河”“运输”类问题，关键是识别状态变量（如人数、位置）和转移条件（载重、非零）。
</similar_problems_intro>

  * **通用思路/技巧迁移**：
      - 运输类问题：如“狼羊菜过河”（状态需记录两岸物品）、“多船运输”（增加船的数量维度）。
      - 资源分配问题：如“货车运货”（载重限制，求最少次数）、“任务调度”（状态记录已完成任务数）。
      - 路径计数问题：如“网格路径”（状态记录当前位置，转移为上下左右移动）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P1006** - `传纸条`
          * 🗣️ **推荐理由**：经典动态规划题，需记录两人路径状态，锻炼多维状态转移能力。
    2.  **洛谷 P1140** - `相似基因`
          * 🗣️ **推荐理由**：状态定义为两个序列的位置，转移涉及匹配得分，与本题组合数计算类似。
    3.  **洛谷 P1216** - `[USACO1.5] 数字三角形 Number Triangles`
          * 🗣️ **推荐理由**：基础动态规划题，适合巩固状态转移和边界条件处理。

-----

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
本次分析的题解中未发现明确的作者个人心得分享部分，但通过观察优质题解的代码，我们可以总结：
</insights_intro>

> 调试时，建议打印关键状态（如`f[i][j][k]`的值），观察是否符合预期；组合数预处理时，需注意数组大小（本题最多n人，预处理到50即可）；边界条件（如初始状态`f[0][x][y]=1`）是易错点，需反复检查。

-----

<conclusion>
本次关于“Greg and Friends”的C++解题分析就到这里。希望这份指南能帮助你理解动态规划在状态转移问题中的应用，以及如何通过组合数计算方案数。记住，多动手调试、观察状态变化，是掌握这类问题的关键！下次我们再一起探索新的编程挑战！💪
</conclusion>

-----

---
处理用时：168.55秒