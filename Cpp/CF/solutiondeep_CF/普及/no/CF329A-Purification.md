# 题目信息

# Purification

## 题目描述

You are an adventurer currently journeying inside an evil temple. After defeating a couple of weak zombies, you arrived at a square room consisting of tiles forming an $ n×n $ grid. The rows are numbered $ 1 $ through $ n $ from top to bottom, and the columns are numbered $ 1 $ through $ n $ from left to right. At the far side of the room lies a door locked with evil magical forces. The following inscriptions are written on the door:

 The cleaning of all evil will awaken the door!Being a very senior adventurer, you immediately realize what this means. You notice that every single cell in the grid are initially evil. You should purify all of these cells.

The only method of tile purification known to you is by casting the "Purification" spell. You cast this spell on a single tile — then, all cells that are located in the same row and all cells that are located in the same column as the selected tile become purified (including the selected tile)! It is allowed to purify a cell more than once.

You would like to purify all $ n×n $ cells while minimizing the number of times you cast the "Purification" spell. This sounds very easy, but you just noticed that some tiles are particularly more evil than the other tiles. You cannot cast the "Purification" spell on those particularly more evil tiles, not even after they have been purified. They can still be purified if a cell sharing the same row or the same column gets selected by the "Purification" spell.

Please find some way to purify all the cells with the minimum number of spells cast. Print -1 if there is no such way.

## 说明/提示

The first example is illustrated as follows. Purple tiles are evil tiles that have not yet been purified. Red tile is the tile on which "Purification" is cast. Yellow tiles are the tiles being purified as a result of the current "Purification" spell. Green tiles are tiles that have been purified previously.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329A/04b73f6bd6d4f5c1ba16b8072ebad28ccdfa62cc.png)In the second example, it is impossible to purify the cell located at row $ 1 $ and column $ 1 $ .

For the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329A/8ffcc7f3e4ed4b4242d89f880e88ffce0ed4e4ab.png)

## 样例 #1

### 输入

```
3
.E.
E.E
.E.
```

### 输出

```
1 1
2 2
3 3
```

## 样例 #2

### 输入

```
3
EEE
E..
E.E
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
EE.EE
E.EE.
E...E
.EE.E
EE.EE
```

### 输出

```
3 3
1 3
2 2
4 4
5 3```

# AI分析结果



# 净化术

## 题目描述

你是一名冒险者，正身处一个邪恶神殿中。在击败几个弱小的僵尸后，你来到一个由 $ n×n $ 网格组成的方形房间。行从上到下编号为 $ 1 $ 到 $ n $，列从左到右编号为 $ 1 $ 到 $ n $。房间远端有一扇被邪恶魔法力量锁住的门，门上的铭文写道：

"净化所有邪恶将唤醒门扉！"

你立即意识到需要净化所有网格。每个网格初始都是邪恶的。"净化"法术的规则是：选择一个非 E 的格子，该行和该列的所有格子将被净化（包含选中格）。求最少施法次数完成净化的方案，否则输出 -1。

## 算法分类
构造

---

## 题解对比与结论

### 核心思路
1. **可行性判定**：若同时存在全E行和全E列，则它们的交叉点无法被净化，直接输出-1
2. **构造方案**：
   - 检查是否存在可用的行方案（每行至少一个可净化点）
   - 检查是否存在可用的列方案（每列至少一个可净化点）
3. **最优选择**：选择行或列中满足条件的一种方案，每行（或列）选一个点即可达到最小操作数 $n$

### 最优题解

#### 题解作者：Nuclear_Fish_cyq（★★★★☆）
**关键亮点**：
1. 使用双重标记数组 `flagr` 和 `flagc` 分别记录每行每列是否存在可净化点
2. 通过逻辑与运算快速判断行列方案的可行性
3. 代码结构清晰，通过二维数组遍历直接构造解

**核心代码**：
```cpp
int main() {
    // 初始化标记数组
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            a[i][j] = (t == '.'); // 转换为布尔矩阵
            flagr[i] = flagr[i] || a[i][j]; // 行标记
            flagc[j] = flagc[j] || a[i][j]; // 列标记
        }
    }
    
    // 判断方案可行性
    bool r = true, c = true;
    for(int i = 0; i < n; i++) {
        r = r && flagr[i];
        c = c && flagc[i];
    }
    
    // 构造解
    if(r) { // 行方案
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(a[i][j]) {
                    cout << i+1 << " " << j+1 << endl;
                    break;
                }
            }
        }
    } else { // 列方案
        for(int j = 0; j < n; j++) {
            for(int i = 0; i < n; i++) {
                if(a[i][j]) {
                    cout << i+1 << " " << j+1 << endl;
                    break;
                }
            }
        }
    }
}
```

#### 题解作者：SpringFullGarden（★★★☆☆）
**亮点**：使用预存坐标数组优化查询效率  
**核心思路**：在读取输入时提前记录每行每列第一个可用点的坐标  
**代码片段**：
```cpp
for(int i = 1; i <= n; i++) {
    string s; cin >> s;
    for(int j = 0; j < n; j++) 
        if(s[j] == '.') {
            a[i][j+1] = 1; 
            row[i] = j+1; // 记录行第一个可用点
            col[j+1] = i; // 记录列第一个可用点
        }
}
```

---

## 举一反三

### 关键技巧
1. **双向标记法**：同时维护行列可用性标记
2. **构造思维**：通过可行性判断直接推导解的结构
3. **预处理优化**：在输入阶段提前记录关键信息

### 相似题目
1. [CF 177B2 - Rectangular Game](https://codeforces.com/problemset/problem/177/B2)  
   （矩形操作与行列覆盖）
2. [洛谷 P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)  
   （贪心策略与线性操作）
3. [洛谷 P1219 八皇后](https://www.luogu.com.cn/problem/P1219)  
   （行列对角线覆盖问题）

---
处理用时：81.17秒