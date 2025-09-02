# 题目信息

# Checkposts

## 题目描述

你的城市有 $n$ 个路口。路口之间有一条单程道路。作为城市的市长，你必须确保所有路口的安全。

为了确保安全，你必须建造一些警察检查站。一个检查站只能建在一个路口。 如果有一个检查站在 $i$ 路口，保护 $j$ 的条件是：$i==j$ 或者警察巡逻车可以从 $i$ 走到 $j$，并且能回到 $i$。

建造检查站要花一些钱。 由于城市的某些地区比其他地区更昂贵，在某些路口修建检查站可能比其他路口花费更多的钱。

你需要找到使所有路口安全的最低花费，以及花费与最低价格相等的方案数。

如果其中任何一个路口包含其中一个检查点而不包含在另一个路口中，则两种方式是不同的。

方案数模 $10^9+7$。

## 说明/提示

$1 \leq n \leq 10^5,0 \leq m \leq 3 \times 10^5,0 \leq a_{i} \leq 10^9$。

$1<=u_{i},v_{i}<=n,u≠v$。

**最小花费不需要取模，方案数需要取模。**

## 样例 #1

### 输入

```
3
1 2 3
3
1 2
2 3
3 2
```

### 输出

```
3 1
```

## 样例 #2

### 输入

```
5
2 8 0 6 0
6
1 4
1 3
2 4
3 4
4 5
5 1
```

### 输出

```
8 2
```

## 样例 #3

### 输入

```
10
1 3 2 2 1 3 1 4 10 10
12
1 2
2 3
3 1
3 4
4 5
5 6
5 7
6 4
7 3
8 9
9 10
10 9
```

### 输出

```
15 6
```

## 样例 #4

### 输入

```
2
7 91
2
1 2
2 1
```

### 输出

```
7 1
```

# AI分析结果


### 💡 Kay的C++算法解析：Checkposts 深入学习指南 💡

**题目解读与核心算法识别**  
✨ **本题主要考察**：强连通分量（SCC）与图论缩点技术  
🗣️ **初步分析**：  
> 本题的关键在于识别图中的强连通分量（SCC）。想象城市路口是游戏地图中的像素点，单向道路是管道，SCC就是通过管道相互连通的封闭区域。在每个区域只需建一个最便宜的检查站（最小点权），就能保护整个区域。  
- **核心难点**：  
  1. 高效分解SCC（Tarjan算法）  
  2. 动态维护SCC内最小点权及其出现次数  
- **解决方案**：  
  - 使用Tarjan算法在O(n+m)时间内分解SCC  
  - 缩点时同步更新最小点权`min_cost`和计数器`count`  
- **可视化设计**：  
  - 像素动画中，节点用8位色方块表示，SCC形成时染成同色  
  - 最小点权节点闪烁金色，计数器随选择更新时播放"叮"音效  
  - 自动演示模式可调速，展示栈操作和low值更新过程  

---

### 2. 精选优质题解参考
**题解一（来源：KEBrantily）**  
* **点评**：  
  思路直击本质——SCC分解后取最小点权。代码规范：  
  - 链式前向星存图，变量名清晰（`sum[]`存最小点权，`siz[]`存计数）  
  - Tarjan中实时更新最小点权，避免二次遍历  
  - 空间优化（O(n)），边界处理严谨，可直接用于竞赛  

**题解二（来源：Kalium）**  
* **点评**：  
  突出方案数计算原理，强调long long重要性。亮点：  
  - 独立函数`mina`避免标准库调用  
  - 清晰的变量分层（`newv[]`存SCC最小点权，`num[]`存计数）  
  - 调试提示（作者强调不开long long易出错）  

**题解三（来源：__Hacheylight__）**  
* **点评**：  
  Vector存图实现简洁，教学价值高：  
  - 分离SCC存储便于理解（`link[]`数组）  
  - 二次遍历统计最小点权，逻辑更易理解  
  - 完整测试样例注释，帮助调试  

---

### 3. 核心难点辨析与解题策略
1. **SCC识别与实时维护**  
   * **分析**：Tarjan中需同步更新最小点权。当节点弹出栈时，比较当前点权与`min_cost[SCC_id]`，若更小则重置计数器  
   * 💡 **学习笔记**：递归栈顶节点即为SCC的入口，是更新数据的黄金时机  

2. **方案数统计的数学原理**  
   * **分析**：每个SCC的方案数=最小点权出现次数。根据乘法原理，总方案数=Π(count[i])  
   * 💡 **学习笔记**：仅当同权值点存在时才影响方案，若更新最小值则计数器必须重置为1  

3. **图不连通的处理**  
   * **分析**：需遍历所有未访问节点启动Tarjan。缩点后形成DAG，每个SCC独立贡献  
   * 💡 **学习笔记**：`for (i=1 to n) if(!dfn[i])`确保不漏点  

### ✨ 解题技巧总结
- **问题转化**：将"保护关系"转化为SCC，用图论模型抽象现实问题  
- **同步更新**：在Tarjan递归栈弹出时立即更新数据，避免额外O(n)遍历  
- **边界防御**：  
  - 点权范围[0,1e9]，初始化最小值用`0x3f3f3f3f`  
  - 方案数取模：每步乘法后立即`% 1e9+7`  

---

### 4. C++核心代码实现赏析
**本题通用核心实现**  
```cpp
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
const int N=1e5+5, MOD=1e9+7;

long long ans_cost, ans_ways=1;
int dfn[N], low[N], min_cost[N], cnt[N];
bool in_stack[N];
stack<int> stk;
vector<int> graph[N], cost;

void tarjan(int u) {
    static int idx = 0;
    dfn[u] = low[u] = ++idx;
    stk.push(u); in_stack[u] = true;
    
    for(int v : graph[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(in_stack[v]) 
            low[u] = min(low[u], dfn[v]);
    }
    
    if(low[u] == dfn[u]) {
        int comp_min = 1e9, comp_cnt = 0;
        while(true) {
            int x = stk.top(); stk.pop();
            in_stack[x] = false;
            // 核心：实时比较最小点权
            if(cost[x] < comp_min) {
                comp_min = cost[x];
                comp_cnt = 1;
            } else if(cost[x] == comp_min) 
                comp_cnt++;
            if(x == u) break;
        }
        ans_cost += comp_min;
        ans_ways = (ans_ways * comp_cnt) % MOD;
    }
}
```

**题解一核心片段**  
```cpp
// 在Tarjan回溯时更新SCC数据
if(dfn[x]==low[x]){
    ++t; int pre;
    do {
        pre = stk.top(); stk.pop();
        if(val[pre] < min_cost[t]) {
            min_cost[t] = val[pre];  // 更新最小值
            cnt[t] = 1;              // 重置计数器
        } else if(val[pre]==min_cost[t]) 
            cnt[t]++;
    } while(pre != x);
}
```
* **学习笔记**：在SCC形成的瞬间更新数据，避免后续遍历  

**题解二创新点**  
```cpp
// 独立最小值函数避免STL依赖
inline int mina(int a, int b) { 
    return (a < b) ? a : b; 
}
```
* **学习笔记**：减少标准库调用可提升性能，竞赛中可用  

---

### 5. 算法可视化：像素动画演示  
**主题**：8位机风格的"迷宫组件探险"  
**核心设计**：  
- **像素节点**：圆形像素块，初始灰色，访问中变黄，属于SCC后染随机8位色  
- **动态栈**：右侧像素柱体模拟栈，节点入栈时上升并播放"咔嗒"音效  
- **SCC形成特效**：当`dfn==low`时，当前SCC节点闪烁3次，播放胜利音效  
- **数据面板**：实时显示：  
  - 当前SCC最小点权（金色数字）  
  - 全局累计花费（绿色数字）  
  - 方案数（蓝色数字，带取模特效）  

**交互控制**：  
```javascript
// 伪代码示例
class SCCVisualizer {
    constructor() {
        this.speed = 500;   // 毫秒/步
        this.stackAnim = new PixelStack(0xFF00FF); // 紫色栈
    }
    highlightNode(id, color) {
        nodes[id].setColor(color); 
        playSound('select');  // 8位音效
    }
    onSCCFormed(nodes) {
        nodes.forEach(node => node.blink(3)); 
        playSound('victory');
    }
}
```

---

### 6. 拓展练习与相似问题  
**通用技巧迁移**：  
- SCC分解用于解决：环检测/依赖解析/状态机简化  
- 缩点+DAG性质适用于：网络流量控制/任务调度  

**洛谷推荐**：  
1. **P2194 HXY烧情侣**  
   🗣️ 双倍经验题，直接应用本题解法  
2. **P3387 缩点**  
   🗣️ 练习缩点后DAG上的DP，强化图论思维  
3. **P2741 USACO4.4 重叠图像**  
   🗣️ SCC在拓扑排序中的进阶应用  

---

### 7. 学习心得  
> **KEBrantily的调试经验**：  
> *"初始化和边界处理是关键，特别是栈操作后`in_stack`标志必须立即更新"*  
>   
> **Kay总结**：  
> 多组数据时重置全局变量易漏，建议封装Tarjan：  
> ```cpp
> void solve() {
>   for(int i=1; i<=n; i++) 
>       if(!dfn[i]) tarjan(i); 
> }
> ```  
> 避免静态变量残留问题！

通过像素化的算法演示和清晰的代码解剖，相信大家能直观理解SCC分解的精髓。继续加油，少年们！💪🏻

---
处理用时：124.14秒