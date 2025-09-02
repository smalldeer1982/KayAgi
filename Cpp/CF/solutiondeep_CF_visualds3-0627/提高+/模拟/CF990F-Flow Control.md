# 题目信息

# Flow Control

## 题目描述

You have to handle a very complex water distribution system. The system consists of $ n $ junctions and $ m $ pipes, $ i $ -th pipe connects junctions $ x_i $ and $ y_i $ .

The only thing you can do is adjusting the pipes. You have to choose $ m $ integer numbers $ f_1 $ , $ f_2 $ , ..., $ f_m $ and use them as pipe settings. $ i $ -th pipe will distribute $ f_i $ units of water per second from junction $ x_i $ to junction $ y_i $ (if $ f_i $ is negative, then the pipe will distribute $ |f_i| $ units of water per second from junction $ y_i $ to junction $ x_i $ ). It is allowed to set $ f_i $ to any integer from $ -2 \cdot 10^9 $ to $ 2 \cdot 10^9 $ .

In order for the system to work properly, there are some constraints: for every $ i \in [1, n] $ , $ i $ -th junction has a number $ s_i $ associated with it meaning that the difference between incoming and outcoming flow for $ i $ -th junction must be exactly $ s_i $ (if $ s_i $ is not negative, then $ i $ -th junction must receive $ s_i $ units of water per second; if it is negative, then $ i $ -th junction must transfer $ |s_i| $ units of water per second to other junctions).

Can you choose the integers $ f_1 $ , $ f_2 $ , ..., $ f_m $ in such a way that all requirements on incoming and outcoming flows are satisfied?

## 样例 #1

### 输入

```
4
3 -10 6 1
5
1 2
3 2
2 4
3 4
3 1
```

### 输出

```
Possible
4
-6
8
-7
7
```

## 样例 #2

### 输入

```
4
3 -10 6 4
5
1 2
3 2
2 4
3 4
3 1
```

### 输出

```
Impossible
```

# AI分析结果



## 算法分类
图论（生成树构造）

---

## 题解分析

### 核心思路
所有题解均基于以下关键点：
1. **流量守恒验证**：所有节点的流量差总和必须为 0。但更严格的条件是**每个连通块的流量差总和必须为 0**，否则无解。
2. **生成树构造**：通过生成树（DFS/BFS）自底向上传递流量需求，父节点累积子节点的流量差。
3. **边流量计算**：在遍历生成树时，子节点的流量需求由父节点通过边传递，根据边的方向决定流量的正负。

### 解决难点对比
| 题解差异点               | Porsche 题解                                                                 | 肖翔题解                                                                 |
|--------------------------|------------------------------------------------------------------------------|--------------------------------------------------------------------------|
| 连通块处理               | 仅检查全局总和，未处理多连通块情况（潜在错误）                               | 显式遍历每个连通块，检查每个块的总和（正确）                             |
| 边方向处理               | 通过邻接表奇偶性判断方向                                                     | 使用映射表记录边的正反向                                                 |
| 生成树构建               | 用并查集合并生成树                                                           | 直接通过 DFS 遍历树                                                     |

### 结论
**正确性关键**在于显式检查每个连通块的总和是否为 0（如肖翔题解）。生成树构造后，通过后序遍历自底向上传递流量需求是核心算法。

---

## 高星题解推荐 (≥4★)
1. **肖翔（5★）**  
   - 亮点：显式处理多连通块总和，代码清晰  
   - 关键代码：
     ```cpp
     for(int i=1;i<=n;i++) if(!vis[i]){
         dfs(i); // 计算连通块总和
         if(sum[i] != 0) return puts("Impossible");
     }
     ```
2. **yuzhechuan（4★）**  
   - 亮点：简洁的邻接表遍历，通过奇偶性处理方向  
   - 代码片段：
     ```cpp
     ans[i>>1] = (i&1 ? -1 : 1) * a[y]; // 通过边编号奇偶性判断方向
     ```
3. **Warriors_Cat（4★）**  
   - 亮点：显式分离生成树与非树边，处理多连通块  

---

## 最优思路提炼
1. **连通块总和检查**：遍历所有未访问节点，检查每个连通块的总和。
2. **生成树流量传递**：DFS 后序遍历子节点，将子节点的流量需求累加到父节点。
3. **边方向处理**：通过邻接表奇偶性或映射表记录边的正反向，动态设置流量正负。

---

## 同类型题
- **POJ 1273 Drainage Ditches**：最大流问题，但构造性思路类似。
- **LeetCode 778. Swim in Rising Water**：生成树应用。
- **洛谷 P1361 最小割**：流量分配与图连通性结合。

---

## 可视化设计
### 动画演示
1. **网格表示**：用像素方块表示节点，颜色深浅表示当前流量差（红色为需流入，蓝色为需流出）。
2. **高亮路径**：DFS 路径用黄色高亮，当前处理的边用绿色闪烁。
3. **流量传递**：子节点向父节点传递流量时，用箭头动画表示流量方向和数值变化。

### 复古像素风格
- **颜色方案**：16 色调色板，节点用 8x8 像素块表示，边用低分辨率线条。
- **音效设计**：
  - 流量分配成功：8-bit 短促“叮”声。
  - 无解：长低音蜂鸣。

### 交互功能
- **步进控制**：按空格键单步执行 DFS。
- **自动演示**：AI 自动遍历生成树，按连通块分阶段执行。

---

## 核心代码示例（肖翔题解）
```cpp
void dfs(int x) {
    vis[x] = 1;
    for (auto e : G[x]) {
        int y = e.first, id = e.second;
        if (!vis[y]) {
            dfs(y);
            ans[abs(id)] = (id > 0 ? 1 : -1) * a[y];
            a[x] += a[y];
        }
    }
}
```

---

## 相似题目推荐
1. **P1231 教辅的分配**（流量分配与图匹配）
2. **P3376 网络流模板**（流量控制基础）
3. **P1343 地震逃生**（连通性与流量限制）

---
处理用时：165.37秒