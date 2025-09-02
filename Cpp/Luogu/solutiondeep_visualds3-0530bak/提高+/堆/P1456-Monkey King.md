# 题目信息

# Monkey King

## 题目描述

曾经在一个森林中居住着 $N$ 只好斗的猴子。在最初他们我行我素，互不认识。但是猴子们不能避免争吵，且两只猴子只会在不认识对方时发生争吵，当争吵发生时，双方会邀请它们各自最强壮的朋友并发起决斗（决斗的为各自最强壮的朋友）。当然，在决斗之后两只猴子和他们各自的伙伴都认识对方了（成为朋友），虽然他们曾经有过冲突，但是他们之间绝不会再发生争吵了。

假设每只猴子有一个强壮值，强壮值将在一场决斗后减少为原先的一半（例如  $10$ 会减少到  $5$，而  $5$ 会减少到  $2$，即向下取整）。

我们也假设每只猴子都认识它自己（是自己的朋友）。即当他是他朋友中最强壮的，他自己就会去决斗。

## 说明/提示

$N,M\leq 100000$，$s_{i}\leq 32768$

## 样例 #1

### 输入

```
5
20
16
10
10
4
5
2 3
3 4
3 5
4 5
1 5
```

### 输出

```
8
5
5
-1
10
```

# AI分析结果



---

## 【唯一算法分类】  
左偏树（可并堆）

---

## 【题解思路与核心难点】  
### 算法共性  
所有题解均需解决两个核心问题：  
1. **动态维护最大值**：通过可并堆快速获取群体最强猴子  
2. **群体合并操作**：将两个独立群体的堆结构高效合并  

### 关键实现差异对比  

| 题解类型       | 数据结构       | 合并时间复杂度 | 减半操作处理                           | 额外空间复杂度 |  
|----------------|----------------|----------------|----------------------------------------|----------------|  
| 左偏树         | 左偏树+并查集  | O(logn)        | 弹出根节点→减半→重构堆→合并            | O(n)           |  
| 配对堆（pbds）| STL配对堆      | O(1)均摊       | 直接修改堆顶元素（依赖库特性）         | O(n)           |  
| 启发式合并     | 普通堆+并查集  | O(nlogn)       | 暴力提取最大值→减半→重新插入堆         | O(n)           |  

### 核心难点解决方案  
**减半操作处理**：  
1. **左偏树**：将根节点弹出→值减半→合并其左右子树→将减半后的节点作为新节点插入  
2. **配对堆**：直接修改堆顶元素值，依赖库的隐式维护（实际需要删除重建）  
3. **启发式合并**：将原堆所有元素取出→减半最大值→重新构建堆  

**群体合并优化**：  
1. 左偏树通过**保持左子树高度≥右子树**的特性，确保合并路径长度最坏O(logn)  
2. 并查集**路径压缩**加速群体归属查询  

---

## 【题解评分 (≥4星)】  
1. **George1123（★★★★★）**  
   - 完整图解左偏树合并过程  
   - 包含路径压缩优化代码  
   - 函数模块化清晰（`weak()`处理减半）  

2. **xht（★★★★☆）**  
   - 代码高度简洁（仅60行核心逻辑）  
   - 独立处理删除操作函数`pop()`  
   - 附带论文推荐与模板链接  

3. **asd_a（★★★★☆）**  
   - 利用pbds库实现10行核心逻辑  
   - 展示STL黑盒的便捷性  
   - 适合竞赛快速解题  

---

## 【最优思路提炼】  
### 左偏树实现模板  
```cpp
int merge(int x, int y) { // 合并核心函数
    if(!x || !y) return x | y;
    if(v[x] < v[y]) swap(x, y);
    rs[x] = merge(rs[x], y);
    if(dep[ls[x]] < dep[rs[x]]) swap(ls[x], rs[x]);
    dep[x] = dep[rs[x]] + 1;
    return x;
}

void weaken(int x) { // 处理减半操作
    v[x] /= 2;
    int new_root = merge(ls[x], rs[x]); // 合并原左右子树
    ls[x] = rs[x] = dep[x] = 0;         // 清空原根节点
    merge(new_root, x);                  // 插入减半后的节点
}
```

### 关键优化点  
- **路径压缩**：并查集查询时直接指向堆根节点  
- **左偏特性维护**：合并时保证左子树深度≥右子树  

---

## 【同类题目推荐】  
1. [P3377【模板】左偏树/可并堆](https://www.luogu.com.cn/problem/P3377)  
2. [P2713 罗马游戏](https://www.luogu.com.cn/problem/P2713)  
3. [P1456 Monkey King（本题）](https://www.luogu.com.cn/problem/P1456)  

---

## 【可视化设计】  
### 动画演示方案  
**数据结构呈现**：  
- 每个猴子群体显示为**左偏树结构**，根节点高亮为金色  
- 并查集关系用虚线箭头表示（路径压缩时动态更新）  

**关键操作演示**：  
1. **合并操作**：  
   - 用红色箭头标记待合并的右子树路径  
   - 展示左右子树交换过程（当右子树深度>左子树时）  

2. **减半操作**：  
   - 根节点变为半透明→分裂为三个元素（原值、左子树、右子树）  
   - 新值插入时显示绿色闪光特效  

**交互控制**：  
- 速度调节滑块（1x/2x/5x）  
- 单步执行按钮（Step Merge/Step Weaken）  

### 复古像素风格实现  
```javascript
// Canvas绘制左偏树节点示例
function drawNode(x, y, value, isRoot) {
    ctx.fillStyle = isRoot ? '#FFD700' : '#00FF00'; // 根节点金色
    ctx.fillRect(x-15, y-15, 30, 30); // 30x30像素方块
    ctx.fillStyle = '#000';
    ctx.font = '10px "Press Start 2P"'; // 8-bit字体
    ctx.textAlign = 'center';
    ctx.fillText(value, x, y+5);
}

// 合并动画帧
function animateMerge(nodeA, nodeB) {
    if (!nodeA) return nodeB;
    // 显示红色右子树合并路径
    drawPath(nodeA.rightChild, '#FF0000'); 
    // 播放8-bit合并音效
    playSound('merge_sound.wav');
}
```

---

## 【核心代码实现】  
### 左偏树+并查集完整代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;

int ls[N], rs[N], v[N], dep[N], fa[N];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int merge(int x, int y) {
    if(!x || !y) return x^y;
    if(v[x] < v[y]) swap(x, y);
    rs[x] = merge(rs[x], y);
    if(dep[ls[x]] < dep[rs[x]]) swap(ls[x], rs[x]);
    dep[x] = dep[rs[x]] + 1;
    return x;
}

void weaken(int x) {
    v[x] >>= 1;
    int rt = merge(ls[x], rs[x]);
    ls[x] = rs[x] = dep[x] = 0;
    fa[rt] = fa[x] = merge(rt, x);
}

int main() {
    int n, m;
    while(~scanf("%d", &n)) {
        for(int i=1; i<=n; ++i) {
            scanf("%d", v+i);
            fa[i] = i, ls[i] = rs[i] = dep[i] = 0;
        }
        scanf("%d", &m);
        while(m--) {
            int a, b; scanf("%d%d", &a, &b);
            a = find(a), b = find(b);
            if(a == b) puts("-1");
            else {
                weaken(a), weaken(b);
                fa[a] = fa[b] = merge(a, b);
                printf("%d\n", v[fa[a]]);
            }
        }
    }
}
```

---
处理用时：90.75秒