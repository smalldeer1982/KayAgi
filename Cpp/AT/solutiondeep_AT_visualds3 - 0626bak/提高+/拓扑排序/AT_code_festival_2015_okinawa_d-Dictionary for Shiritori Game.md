# 题目信息

# Dictionary for Shiritori Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-okinawa-open/tasks/code_festival_2015_okinawa_d



## 说明/提示

### Problem

In a country where $ N $ different kinds characters are being used, there is a dictionary that contains $ M $ entries, each entry is a definition for a word. All the kinds of characters are listed as character $ 1 $, character $ 2 $, ..., character $ N $. The $ i_{th} $ entry (as a word) of this dictionary begins with the letter $ p_i $, and ends with the letter $ q_i $.

 Cat Snuke and Wolf Sothe will use this dictionary to play a game called **Shiritori** . (Please note that Shiritori in this game is different from a normal Shiritori game.)

- The first move will be made by Cat Snuke, then two players will move alternately.
- For the first move, the player in turn has to say a word the begins with character $ 1 $. If there are no any words that begin with character $ 1 $, the player in turn loses.
- For the rest moves, the player of that turn has to say any word that begins with the last character of the word being said in the previous move from the dictionary. If there is not any appropriate word, the player in turn loses.
- **Any word can be said any number of times** .

There should be some dictionaries that two players can not change the result of the game even if they tried their best. For these dictionaries, in this case, we want to find out if the first player or the second player will win, or even the game will never halt.

All the words in the dictionary will be given. We can assume that the two players will try their best. Please decide if the first player (Cat Snuke) or the second player (Wolf Sothe) will win, or even the game will never halt.

### Sample Explanation 1

\- For the first move, Cat Snuke has to say the first word. - For the second move, if Wolf Sothe said the 6th word, Cat Snuke will have no appropriate word to say for the next move, thus Wolf Sothe wins.

### Sample Explanation 4

Please note that for the first move it is possible that there is no appropriate word that can be said.

## 样例 #1

### 输入

```
6 5

1 2

2 3

3 4

4 2

2 5```

### 输出

```
Sothe```

## 样例 #2

### 输入

```
6 6

1 2

2 3

3 4

4 2

2 5

5 6```

### 输出

```
Draw```

## 样例 #3

### 输入

```
6 8

1 2

1 3

3 4

3 5

2 1

4 5

4 6

5 6```

### 输出

```
Snuke```

## 样例 #4

### 输入

```
4 8

2 3

2 3

3 4

4 1

3 1

2 2

4 2

4 3```

### 输出

```
Sothe```

# AI分析结果



---

**唯一算法分类**  
博弈论+拓扑排序

---

**综合分析与结论**  

**核心思路**  
1. **反向建图**：将单词的结尾字符视为父节点，开头字符视为子节点建立反向边（p_i → q_i 转换为 q_i → p_i）。  
2. **拓扑排序**：从出度为0的节点（原图中无法继续接龙的字符）开始，这些节点初始状态为必败态。  
3. **状态传播**：  
   - 若当前节点必败（玩家无法获胜），其所有父节点变为必胜态（玩家可选择走到此节点使对手必败）  
   - 若当前节点必胜，则父节点的入度减1；当父节点的所有子节点均必胜时，父节点变为必败态  
4. **环处理**：未被拓扑排序处理的节点构成环，此时游戏可能无限进行（平局）  

**解决难点**  
- **环的判断**：通过未处理的节点状态为-1，巧妙区分平局场景  
- **逆向推导**：反向建图使必败态能向上传播，避免直接处理原图可能遇到的复杂环逻辑  

**可视化设计**  
1. **动态拓扑图**：  
   - 初始时所有节点为灰色，出度为0的节点变为蓝色（必败态）并入队  
   - 队列节点弹出时，若状态为必败（蓝色），将其父节点染红（必胜态）；若状态为必胜（红色），父节点入度减1  
   - 环内节点保持灰色，弹出时显示特殊动画（如闪烁）  
2. **像素风格**：  
   - 使用 8-bit 风格渲染节点（16x16 像素块）与箭头  
   - 必败态节点显示「💀」图标，必胜态显示「🏆」，平局节点显示「∞」  
3. **音效系统**：  
   - 节点状态变化时播放「嘟」声（8-bit 音效）  
   - 发现环时播放经典 FC 游戏中的「失败」音效  

---

**题解清单 (≥4星)**  

1. **Daniel_7216（4.5星）**  
   - 亮点：通过原图状态转移的直观解释，代码中 `vis` 数组逻辑清晰  
   - 核心代码：  
     ```cpp
     void bfs(){
         while (!q.empty()){
             x = q.front(); q.pop();
             for (邻接节点 y){
                 if (x必败) 标记y为必胜  
                 else if (y的入度归零) 标记y为必败  
             }
         }
     }
     ```

2. **YY_rainbow（4.5星）**  
   - 亮点：明确反向图拓扑排序的逻辑，注释详细  
   - 关键实现：  
     ```cpp
     void topo(){
         for (所有入度0节点初始化)...  
         while (队列非空){
             if (当前节点必败) 父节点标记必胜  
             else if (父节点入度归零) 标记必败  
         }
     }
     ```

3. **AutumnKite（4星）**  
   - 亮点：高效的状态标记（0/1/2），内存优化  
   - 核心逻辑：  
     ```cpp
     if (f[u] == 2) // 当前必败  
         for (父节点) f[父] = 1;  
     else // 当前必胜  
         if (父节点入度归零) f[父] = 2;  
     ```

---

**最优思路提炼**  
1. **反向图拓扑排序**：避免原图复杂环处理，通过入度传播状态  
2. **必胜/必败态判定规则**：  
   - 若存在至少一个必败态子节点 → 当前节点必胜  
   - 若所有子节点均必胜 → 当前节点必败  
3. **入度计数技巧**：通过维护剩余未处理的必胜子节点数量判断状态  

---

**同类型题推荐**  
1. [洛谷 P6560](https://www.luogu.com.cn/problem/P6560)（几乎同一模型）  
2. [Codeforces 1033C](https://codeforces.com/problemset/problem/1033/C)（博弈+图论）  
3. [Atcoder ARC059-D](https://atcoder.jp/contests/arc059/tasks/arc059_d)（博弈+状态压缩）  

---

**代码实现（核心逻辑）**  
```cpp
// 以 YY_rainbow 的代码为基础
void topo(){
    queue<int> q;
    for(int i=1; i<=n; i++) 
        if(deg[i]==0) q.push(i), ans[i]=0; // 必败态初始化
    
    while(!q.empty()){
        int x = q.front(); q.pop();
        for(int y : G[x]){ // G为反向图
            deg[y]--;
            if(ans[x]==0){ // x必败 → y必胜
                if(ans[y]==-1){
                    ans[y] = 1;
                    q.push(y);
                }
            } else if(deg[y]==0 && ans[y]==-1){ // y所有子节点必胜 → y必败
                ans[y] = 0;
                q.push(y);
            }
        }
    }
}
```

---

**可视化算法演示**  
**动画步骤**：  
1. **初始化阶段**：  
   - 所有节点显示为灰色方块，边为浅灰色箭头  
   - 检测出度为0的节点 → 变为蓝色方块，加入队列时播放「滴」声  

2. **处理队列节点**：  
   - 弹出队列头节点x，高亮为黄色  
   - 遍历x的所有父节点y：  
     - 若x为蓝色（必败）：将y染红（必胜），边x→y闪烁红色  
     - 若x为红色（必胜）：y的入度减1，显示剩余入度值  
     - 当y的入度归零且未标记 → 染蓝并入队  

3. **环检测**：  
   - 最终未被处理的节点保持灰色，显示「∞」符号  
   - 触发循环音效（类似经典游戏中的Boss出场音乐）  

**交互功能**：  
- **速度调节**：滑动条控制动画速度（0.5x~5x）  
- **单步执行**：点击「Next Step」逐步观察状态传播  
- **AI自动演示**：点击后自动完成全过程，关键步骤暂停0.5秒  

---

**复古游戏化设计**  
1. **视觉元素**：  
   - 使用 NES 调色板（#6B6B6B 背景，#FF0000 必胜节点，#0030FF 必败节点）  
   - 节点用 16x16 像素块渲染，边用虚线箭头表示  

2. **音效设计**：  
   - 状态变化：8-bit 短音（C大调音符）  
   - 队列操作：经典 FC 菜单选择音效  
   - 发现环：FC 游戏中「Game Over」音效片段  

3. **积分系统**：  
   - 每处理一个节点 +10 分  
   - 发现环时获得「∞ Bonus」+50 分  
   - 最高分记录保存至 localStorage  

---

通过此设计，学习者可直观理解拓扑排序在博弈论中的应用，同时复古风格增强学习趣味性。

---
处理用时：93.87秒