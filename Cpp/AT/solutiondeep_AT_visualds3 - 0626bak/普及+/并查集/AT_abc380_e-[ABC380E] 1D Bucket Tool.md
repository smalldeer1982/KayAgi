# 题目信息

# [ABC380E] 1D Bucket Tool

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc380/tasks/abc380_e

$ 1 $ から $ N $ の番号がついた $ N $ 個のマスが一列に並んでいます。  
$ 1\ \leq\ i\ <\ N $ について、マス $ i $ とマス $ i+1 $ は隣接しています。

最初、マス $ i $ は色 $ i $ で塗られています。

クエリが $ Q $ 個与えられるので、順に処理してください。クエリは次の $ 2 $ 種類のいずれかです。

- `1 x c`: マス $ x $ から始めて「いまいるマスと同じ色に塗られている隣接するマス」への移動を繰り返すことで到達可能なマスを全て色 $ c $ に塗り替える
- `2 c`: 色 $ c $ で塗られているマスの個数を答える

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 1 $ 種類目のクエリにおいて、$ 1\ \leq\ x\ \leq\ N $
- $ 1,2 $ 種類目のクエリにおいて、$ 1\ \leq\ c\ \leq\ N $
- $ 2 $ 種類目のクエリが少なくとも $ 1 $ つ存在する
- 入力は全て整数である

### Sample Explanation 1

クエリにより、マスの色は図のように塗り替えられていきます。 
![図](https://img.atcoder.jp/abc380/c3bf3eec819a7b7fcbfd21065c06bab2.png)

## 样例 #1

### 输入

```
5 6
1 5 4
1 4 2
2 2
1 3 2
1 2 3
2 3```

### 输出

```
3
4```

# AI分析结果



## 算法分类
并查集

---

## 题解思路与核心难点

### 算法要点
1. **并查集扩展结构**：每个连通块维护左端点、右端点、颜色、大小四个属性
2. **颜色统计优化**：通过维护全局颜色计数器，在合并时同步更新颜色计数
3. **双向合并策略**：修改颜色后，检查左右相邻块的颜色是否相同，进行合并操作

### 解决难点对比
| 题解特点               | liluhexuan 解法          | Moya_Rao 解法             | 线段树解法           |
|----------------------|--------------------------|--------------------------|--------------------|
| 合并触发条件           | 通过 min/max 端点判断相邻块 | 显式维护块结构的左右边界     | 二分查找同色区间      |
| 颜色统计方式           | 使用 sum 数组记录块大小     | 直接在结构体中记录块长度     | 维护颜色桶数组       |
| 时间复杂度           | O(α(N))                | O(α(N))                | O(log²N)         |
| 空间复杂度           | O(N)                   | O(N)                   | O(N)             |
| 实现复杂度           | 中等（需维护多个辅助数组）   | 中等（结构体封装属性）       | 高（需实现区间查询）  |

---

## 题解评分（≥4星）

### 1. liluhexuan（⭐⭐⭐⭐）
- **亮点**：完整注释、处理合并逻辑清晰
- **核心代码**：
```cpp
void join(int x,int y){
    x=find(x),y=find(y);
    if(x!=y) sum[x]+=sum[y],p[y]=x;
    mx[x]=max(mx[x],mx[y]); 
    mn[x]=min(mn[x],mn[y]);
}
```

### 2. Moya_Rao（⭐⭐⭐⭐）
- **亮点**：结构体封装块属性、合并逻辑简洁
- **核心代码**：
```cpp
if(p[fid].c==p[fsm].c)
    fa[fsm]=fid,p[fid].l=p[fsm].l;
```

### 3. BrSt_Spike（⭐⭐⭐⭐）
- **亮点**：变量命名清晰、维护逻辑直观
- **核心代码**：
```cpp
siz[col[fx]] -= r - l + 1;
col[fx] = c;
siz[c] += r - l + 1;
```

---

## 最优思路提炼
1. **双向合并策略**：修改颜色后，检查左右相邻块颜色是否相同
2. **端点维护技巧**：每个块记录 min/max 端点，快速定位相邻块
3. **O(1) 颜色统计**：维护全局颜色计数器数组，避免遍历统计

---

## 相似题目推荐
1. [洛谷 P3367 - 并查集模板](https://www.luogu.com.cn/problem/P3367)
2. [洛谷 P3402 - 可持久化并查集](https://www.luogu.com.cn/problem/P3402)
3. [洛谷 P2147 - 洞穴勘测](https://www.luogu.com.cn/problem/P2147)

---

## 可视化设计

### 动画方案
```html
<div id="canvas-container">
  <canvas width="800" height="200"></canvas>
  <div class="controls">
    <button onclick="stepBack()">←</button>
    <span id="step-count">Step 0</span>
    <button onclick="stepNext()">→</button>
    <input type="range" id="speed" min="1" max="5" value="3">
  </div>
</div>

<script>
// 示例数据结构
let blocks = [
  { l:1, r:5, color:'#FF0000', parent:1 },
  { l:6, r:8, color:'#00FF00', parent:6 }
];

function drawBlock(ctx, block) {
  // 绘制方块主体
  ctx.fillStyle = block.color;
  ctx.fillRect(block.l*50, 50, (block.r-block.l+1)*50, 100);
  
  // 绘制端点标记
  ctx.strokeStyle = '#000';
  ctx.strokeRect(block.l*50, 50, 50, 100); // 左端点
  ctx.strokeRect(block.r*50, 50, 50, 100); // 右端点
}

function highlightMerge(ctx, block1, block2) {
  // 闪烁效果实现
  let alpha = 0;
  const animate = () => {
    ctx.fillStyle = `rgba(255,255,0,${alpha})`;
    ctx.fillRect(block1.l*50, 50, (block1.r-block1.l+1)*50, 100);
    ctx.fillRect(block2.l*50, 50, (block2.r-block2.l+1)*50, 100);
    alpha = (alpha + 0.1) % 1;
    requestAnimationFrame(animate);
  };
  animate();
}
</script>
```

### 复古风格实现
1. **颜色方案**：使用 8-bit 风格的 16 色调色板
2. **音效设计**：
   - 合并时播放 8-bit "blip" 音效（[JSFiddle](https://jsfiddle.net/6spj1059/)）
   - 查询操作时播放 MIDI 音阶上升音
3. **自动演示模式**：通过预设操作序列演示典型测试用例

---

## 核心代码实现
```cpp
const int N = 5e5+10;
struct Block {
    int l, r, color, parent;
} block[N];

int find(int x) {
    if(block[x].parent != x)
        block[x].parent = find(block[x].parent);
    return block[x].parent;
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return;
    
    // 维护颜色计数器
    colorCount[block[x].color] -= (block[x].r - block[x].l + 1);
    
    // 合并块属性
    block[x].r = max(block[x].r, block[y].r);
    block[x].l = min(block[x].l, block[y].l);
    block[y].parent = x;
    
    // 更新相邻块检测
    checkAdjacent(x);
}

void checkAdjacent(int x) {
    // 左邻检测
    if(block[x].l > 1) {
        int left = find(block[x].l-1);
        if(block[left].color == block[x].color)
            merge(x, left);
    }
    // 右邻检测
    if(block[x].r < n) {
        int right = find(block[x].r+1);
        if(block[right].color == block[x].color)
            merge(x, right);
    }
}
```

---

## 调试心得摘录
> "合并时必须通过端点查找相邻块，直接查x±1会导致中间块判断错误" —— liluhexuan  
> "颜色计数器要在合并前更新，否则会导致重复计算" —— Moya_Rao  
> "维护左右端点比维护整个区间更高效" —— BrSt_Spike

---

通过并查集维护动态连通性，结合端点检测实现高效合并，该方案在时间复杂度与空间复杂度上达到最优，是此类区间合并问题的通用解法。

---
处理用时：102.86秒