# 题目信息

# [USACO18OPEN] Multiplayer Moo S

## 题目描述

奶牛们提出了一款创新性的新游戏，令人惊讶的是她们给这款游戏取了个最没创意的名字：“Moo”。  
Moo 游戏在一个由 $N \times N$ 个正方形格子组成的棋盘上进行。一头奶牛可以通过大叫一声“哞！”然后把她的数字编号写在这个格子里来占有这个格子。

在游戏结束时，每个格子中都包含一个数。此时，如果一头奶牛创建了一个由连通的格子组成的领域，且该领域的大小不小于其他所有领域，那么这头奶牛就获胜。一个“领域”被定义为一些具有相同数字编号的格子，其中每个格子都直接与另一个同一领域中的格子通过上、下、左或右相邻（对角线不计）。

由于以单牛形式进行游戏有点无聊，奶牛们也对双牛组队进行游戏感兴趣。同一队的两头奶牛可以创建一个领域，但现在领域中的格子可以属于队伍中的任一头奶牛。

给定游戏棋盘的最终状态，请帮助奶牛们计算：  
1. 任何单头奶牛占有的最大领域包含的格子数量。  
2. 任何两头奶牛组成的队伍占有的最大领域包含的格子数量。  

注意，两头奶牛占有的领域必须同时包含队伍中两头奶牛的编号，不能仅仅包含一头。

## 说明/提示

在这个例子中，单头奶牛占有的最大领域是由五个 $9$ 组成的。如果编号为 $1$ 和 $9$ 的奶牛组队，她们可以形成一个大小为 $10$ 的领域。

供题：Brian Dean

## 样例 #1

### 输入

```
4
2 3 9 3
4 9 9 1
9 9 1 7
2 1 1 9```

### 输出

```
5
10
```

# AI分析结果



### 算法分类
图论（连通块分析）

### 题解思路与算法要点
#### 第一问核心逻辑
所有题解均采用 Flood Fill 算法，通过 BFS/DFS 遍历所有连通块，时间复杂度 O(n²)。关键要点：
1. 使用 vis 数组标记已访问的格子
2. 每次遍历时统计连通块大小
3. 使用方向数组处理相邻格子

#### 第二问核心难点与解法对比
| 题解作者       | 核心思路                                                                 | 优化手段                         | 时间复杂度     |
|----------------|--------------------------------------------------------------------------|----------------------------------|----------------|
| xiwang         | 建立缩点邻接图，枚举颜色组合                                             | 使用 map 存储邻接关系            | O(k*m) k为颜色数|
| 狸狸养的敏敏   | 暴力枚举相邻颜色组合                                                     | unordered_map 去重              | O(n⁴)          |
| Aoki_灏        | 随机化遍历 + 时间戳优化                                                  | 随机排列格子、时间戳替代清空操作 | O(n²)~O(n⁴)   |
| Mandy          | 预处理连通块邻接关系，构建图结构后 BFS                                   | 边遍历优化、点遍历剪枝           | O(m²) m为块数 |
| Shunpower      | 并查集预处理单色块，枚举相邻块组合                                       | 颜色组合剪枝                     | O(n² + k)     |

### 题解评分（≥4星）
1. **Mandy（⭐⭐⭐⭐⭐）**  
   - 连通块缩点+邻接图构建，将棋盘问题转化为图论问题  
   - 创新性使用边遍历优化和点遍历剪枝  
   - 代码结构清晰，实践性强

2. **Shunpower（⭐⭐⭐⭐）**  
   - 并查集预处理极大提升效率  
   - 通过颜色组合剪枝避免重复计算  
   - 代码简洁易懂，适合竞赛场景

3. **Aoki_灏（⭐⭐⭐⭐）**  
   - 随机化+时间戳优化巧妙规避极端数据  
   - 通过时间戳替代 memset 提升性能  
   - 思路新颖，适合处理大数据量

### 最优技巧提炼
1. **缩点邻接图**（Mandy）  
   ```cpp
   struct gph { map<int,set<int>> g; map<int,int> nsz; };
   map<pii,gph> g2; // 存储颜色组合的图结构
   ```
   将每个单色连通块视为节点，建立跨颜色块的邻接关系，将棋盘问题转化为图遍历问题。

2. **时间戳优化**（Aoki_灏）  
   ```cpp
   int TIM_CNT = 0; 
   void bfs() {
       TIM_CNT++;
       if(flag[tx][ty] == TIM_CNT) return; 
   }
   ```
   用递增的时间戳替代 memset 清空数组，将 O(n²) 的清空操作优化为 O(1)。

3. **随机化遍历**（Aoki_灏）  
   ```cpp
   random_shuffle(rak+1, rak+1+cnt); // 随机排列遍历顺序
   while((double)clock()/CLOCKS_PER_SEC < 0.9) // 时间限制
   ```
   通过随机化避免最坏情况，配合时间限制实现概率性正确。

### 相似题目推荐
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141) - 连通块预处理
2. [P1501 矩阵](https://www.luogu.com.cn/problem/P1501) - 双色块扩展
3. [P3076 [USACO13FEB]Taxi G](https://www.luogu.com.cn/problem/P3076) - 图论优化

### 可视化设计
**动画方案（双色连通块扩展）：**
1. **像素风格渲染**  
   ```javascript
   const CELL_SIZE = 20; // 每个格子20x20像素
   const PALETTE = ["#FF6B6B", "#4ECDC4", "#556270"]; // 复古配色
   ```
   使用 Canvas 绘制棋盘，单色块用纯色填充，双色块用棋盘格纹理。

2. **扩展过程演示**  
   ```javascript
   function drawStep(queue) {
       queue.forEach((x,y) => {
           ctx.fillStyle = (step%2) ? PALETTE[1] : PALETTE[0];
           ctx.fillRect(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE);
       });
   }
   ```
   用闪烁边框标记当前扩展的队列，不同颜色块用不同动画模式（水平/垂直扫描线）。

3. **音效系统**  
   ```javascript
   const audioCtx = new AudioContext();
   function playTone(freq) {
       let oscillator = audioCtx.createOscillator();
       oscillator.type = 'square'; // 8位方波音效
       oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
       oscillator.connect(audioCtx.destination);
       oscillator.start(); oscillator.stop(0.1);
   }
   ```
   在以下事件触发音效：
   - 发现新连通块：440Hz 上行音阶
   - 扩展失败：220Hz 短促音
   - 找到最大块：880Hz 长音

### 核心代码片段（Mandy 邻接图优化）
```cpp
void addg2(int x1,int y1,int x2,int y2){
    int c1=a[x1][y1], c2=a[x2][y2], id1=id[x1][y1], id2=id[x2][y2];
    pii p = pii(min(c1,c2), max(c1,c2)); // 颜色有序存储
    add(g2[p], g1[c1].rid[id1], g1[c2].rid[id2]); // 添加邻接关系
}

int main(){
    // 预处理单色块
    for(所有相邻不同色块) addg2(...);
    // 处理双色块
    for(auto &[color_pair, graph] : g2){
        ans2 = max(ans2, floodfill(graph));
    }
}
```
通过邻接图将复杂度从 O(n⁴) 降为 O(m²)，其中 m 为连通块数量，在棋盘较均匀时 m ≈ n²/4。

---
处理用时：72.57秒