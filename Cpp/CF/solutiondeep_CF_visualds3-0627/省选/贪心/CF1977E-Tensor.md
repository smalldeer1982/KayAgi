# 题目信息

# Tensor

## 题目描述

This is an interactive problem.

You are given an integer $ n $ .

The jury has hidden from you a directed graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and some number of edges. You additionally know that:

- The graph only contains edges of the form $ i \leftarrow j $ , where $ 1 \le i < j \le n $ .
- For any three vertices $ 1 \le i < j < k \le n $ , at least one of the following holds $ ^\dagger $ : 
  - Vertex $ i $ is reachable from vertex $ j $ , or
  - Vertex $ i $ is reachable from vertex $ k $ , or
  - Vertex $ j $ is reachable from vertex $ k $ .

You want to color each vertex in either black or white such that for any two vertices $ i $ and $ j $ ( $ 1 \le i < j \le n $ ) of the same color, vertex $ i $ is reachable from vertex $ j $ .

To do that, you can ask queries of the following type:

- ? i j — is vertex $ i $ reachable from vertex $ j $ ( $ 1 \le i < j \le n $ )?

Find any valid vertex coloring of the hidden graph in at most $ 2 \cdot n $ queries. It can be proven that such a coloring always exists.

Note that the grader is not adaptive: the graph is fixed before any queries are made.

 $ ^\dagger $ Vertex $ a $ is reachable from vertex $ b $ if there exists a [path](https://en.wikipedia.org/wiki/Path_(graph_theory)) from vertex $ b $ to vertex $ a $ in the graph.

## 说明/提示

The hidden graph in the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1977E/d9f22ee8ab749a5ad0bef404d190145b53c9cc18.png)The hidden graph in the second test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1977E/eba30883018cd14dec28ecbab62d3af607fa7b41.png)The interaction happens as follows:

SolutionJuryExplanation2There are $ 2 $ test cases.4In the first test case, the graph has $ 4 $ vertices.? 1 2 YESThe solution asks if vertex $ 1 $ is reachable from vertex $ 2 $ , and the jury answers YES.? 2 3 YESThe solution asks if vertex $ 2 $ is reachable from vertex $ 3 $ , and the jury answers YES.? 1 3 YESThe solution asks if vertex $ 1 $ is reachable from vertex $ 3 $ , and the jury answers YES.? 1 4 NOThe solution asks if vertex $ 1 $ is reachable from vertex $ 4 $ , and the jury answers NO.? 2 4 NOThe solution asks if vertex $ 2 $ is reachable from vertex $ 4 $ , and the jury answers NO.? 3 4 NOThe solution asks if vertex $ 3 $ is reachable from vertex $ 4 $ , and the jury answers NO.! 0 0 0 1The solution has somehow determined a valid coloring and outputs it. Since the output is correct, the jury continues to the next test case.5In the second test case, the graph has $ 5 $ vertices.! 1 1 0 1 0The solution has somehow determined a valid coloring, and outputs it. Since the output is correct and there are no more test cases, the jury and the solution exit.Note that the line breaks in the example input and output are for the sake of clarity, and do not occur in the real interaction.

## 样例 #1

### 输入

```
2
4

YES

YES

YES

NO

NO

NO

5```

### 输出

```
? 1 2

? 2 3

? 1 3

? 1 4

? 2 4

? 3 4

! 0 0 0 1

! 1 1 0 1 0```

# AI分析结果



### 综合分析与结论

#### 核心思路与贪心策略
各题解核心思路均为维护两个主链（栈）和一个临时链，通过贪心选择将新顶点加入可达的链，解决关键问题如下：
1. **双链维护**：用两个栈维护两种颜色集合，保证栈顶元素互不可达（反链长度≤2）
2. **临时链处理**：当新顶点同时可达两个栈顶时，引入第三个栈暂存，后续遇到不可达点时合并临时链到合适主链
3. **Dilworth定理应用**：将问题转化为最大反链不超过2的链覆盖问题，确保最多两种颜色可行

#### 可视化设计思路
1. **像素化分屏**：左侧显示顶点编号（像素方块），右侧用三种颜色块表示三个栈
2. **动画演示**：
   - 新顶点闪烁黄光，与当前栈顶连线（绿/红表示可达）
   - 临时链顶点显示为蓝色方块，合并时触发爆炸粒子特效
3. **音效系统**：
   - 点击查询时播放8-bit电子音
   - 合并栈时播放升级音效
   - 错误操作时短促报警声

### 题解清单（≥4星）

| 题解作者 | 星级 | 核心亮点 |
|---------|-----|---------|
| sunkuangzheng | ★★★★★ | 三链维护策略清晰，势能分析严格证明查询次数 |
| haochengw920 | ★★★★☆ | 增量构造法代码简洁，栈操作直观 |
| yshpdyt | ★★★★ | Dilworth定理应用严谨，状态转移逻辑完备 |

### 代码实现与核心逻辑

#### 关键代码片段（sunkuangzheng解法）
```cpp
vector<int> st1, st2, tmp;
for(int i=2; i<=n; ++i){
    if(st2.empty()){
        if(query(st1.back(),i)) st1.push_back(i);
        else st2.push_back(i);
    } else if(tmp.empty()){
        bool f1=query(st1.back(),i), f2=query(st2.back(),i);
        if(f1 && f2) tmp.push_back(i);
        else if(f1) st1.push_back(i);
        else st2.push_back(i);
    } else {
        if(query(tmp.back(),i)) tmp.push_back(i);
        else if(query(st1.back(),i)){
            st1.push_back(i);
            st2.insert(st2.end(), tmp.begin(), tmp.end());
            tmp.clear();
        } else {
            st2.push_back(i); 
            st1.insert(st1.end(), tmp.begin(), tmp.end());
            tmp.clear();
        }
    }
}
```

#### 核心贪心逻辑
1. **初始状态**：第一个顶点默认加入链1
2. **单链阶段**：当链2为空时，只需判断新顶点是否可达链1末尾
3. **双链阶段**：
   - 新顶点可达双链顶 → 加入临时链
   - 仅可达单链 → 加入对应链
4. **临时链处理**：
   - 新顶点可达临时链顶 → 继续暂存
   - 不可达时根据主链可达性合并临时链

### 同类型题目推荐
1. **P1020 导弹拦截**：Dilworth定理经典应用
2. **P2512 糖果传递**：环形贪心策略
3. **P4053 建筑抢修**：带时限的贪心调度

### 可视化方案设计

#### 复古像素风格实现
```html
<canvas id="pixel-canvas"></canvas>
<script>
const COLORS = ['#FF5555', '#55FF55', '#5555FF']; // 红绿蓝三链
class PixelAnimator {
  constructor(n) {
    this.ctx = document.getElementById('pixel-canvas').getContext('2d');
    this.chains = [[], [], []]; // 三个链的顶点集合
    this.currentVertex = 1;
  }
  
  drawVertex(x, y, color) {
    this.ctx.fillStyle = color;
    this.ctx.fillRect(x*20, y*20, 18, 18);
  }

  async addToChain(chainIdx) {
    const y = this.chains[chainIdx].length;
    this.chains[chainIdx].push(this.currentVertex);
    this.drawVertex(chainIdx, y, COLORS[chainIdx]);
    await new Promise(r => setTimeout(r, 500)); // 动画延迟
  }
}
</script>
```

#### 交互功能
- **空格键**：单步执行算法
- **方向键**：调节动画速度
- **Q键**：显示当前查询状态
- **背景音乐**：循环播放8-bit风格BGM

### 个人心得摘录
> "当新顶点同时可达两个链顶时，必须引入临时链暂存，否则后续可能出现无法处理的顶点。这个洞见来自对多个反例的手工推演。" —— sunkuangzheng

> "合并临时链时要保证原链顶仍然互不可达，这个性质维护是算法正确的关键。" —— haochengw920

### 算法演示说明
1. **初始状态**：红链为[1]，其他链为空
2. **加入顶点2**：查询1→2可达，加入红链
3. **加入顶点3**：若1→3不可达则创建绿链
4. **冲突处理**：当顶点4同时可达红绿链顶时，暂存蓝链
5. **链合并**：后续顶点触发蓝链合并时播放爆炸特效

通过分步可视化，清晰展现贪心策略的决策过程和链结构演化，帮助理解复杂状态转移逻辑。

---
处理用时：62.62秒