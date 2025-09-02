# 题目信息

# [ABC087D] People on a Line

## 题目描述

在一根数轴上站有 $n$ 个人，我们称第 $i$ 个人的坐标为 $x_i(x_i\in [0,10^{9}],x_i\in Z)$，同一个坐标点上可能有多个人。

你现在手上有 $m$ 条信息，第 $i$ 条信息形如 $(li,ri,di)$，含义是第 $r_i$ 个人在第 $l_i$ 个人右数第 $d_i$ 个坐标点上，换言之，$x_{r_i} - x_{l_i} = d_i$。

不幸的是，这 $m$ 条信息中的一些可能有误，请你求出是否存在一组 $x (x_1,x_2,x_3,\dots ,x_n)$ 满足所有信息。

## 说明/提示

全部的输入数据满足以下条件：

-  $1 \le n \le 100000$；
-  $0 \le m \le 200000$；
- $1\le l_i,r_i\le n (1\le i\le m)$；
- $0\le d_i\le 10000 (1\le i\le m)$；
- $l_i \ne r_i (1 \le i \le m)$；
- 如果 $i\le j$，则有 $(l_i,r_i)\ne (l_j,r_j),(l_i,r_i)\ne (r_j,l_j)$；
- $d_i$ 为整数。


$(0,1,2)$ 与 $(101,102,103)$ 都是合法的解。


若前两条信息是正确的，则有 $x_3 - x_1 = 2$，那么第三条信息就是错误的。

感谢@fbhou  提供的翻译

## 样例 #1

### 输入

```
3 3

1 2 1

2 3 1

1 3 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3

1 2 1

2 3 1

1 3 5```

### 输出

```
No```

## 样例 #3

### 输入

```
4 3

2 1 1

2 3 5

3 4 2```

### 输出

```
Yes```

## 样例 #4

### 输入

```
10 3

8 7 100

7 9 100

9 8 100```

### 输出

```
No```

## 样例 #5

### 输入

```
100 0```

### 输出

```
Yes```

# AI分析结果



## 唯一算法分类  
**带权并查集**

---

## 综合分析与结论  
### 核心思路与难点  
题目本质是判断多个约束条件（形如 x_r - x_l = d）是否存在矛盾。关键难点在于：  
1. 动态维护节点间的相对距离  
2.快速判断新增约束是否与已有约束冲突  

带权并查集通过维护每个节点到其根节点的距离差值（dis数组）实现：  
- **路径压缩**时更新距离（dis[x] += dis[旧父节点]）  
- **合并集合**时调整根节点间距离（dis[rl] = d + dis[r] - dis[l]）  
- 冲突判断：当两个节点已连通时，检查其距离差是否等于约束值  

### 可视化设计要点  
采用**8位像素风格**展示并查集森林：  
1. 每个节点显示为不同颜色的方块，父节点用箭头连接  
2. **路径压缩**时：  
   - 当前节点闪烁黄色  
   - 路径上所有节点向根节点聚拢，箭头动态重绘  
3. **合并操作**时：  
   - 两个根节点之间出现虚线连接  
   - 数值变化用绿色（增加）/红色（减少）弹跳动画  
4. **冲突检测**时：  
   - 冲突节点闪烁红色，播放短促警报音效  
5. 背景音乐采用循环的8位电子音，每次成功操作伴随不同音高

---

## 题解清单 (≥4星)  
### 1. Doraven ⭐⭐⭐⭐⭐  
**亮点**：  
- 完美实现带权并查集核心逻辑  
- 代码简洁（仅50行）  
- 时间复杂度 O(mα(n))，适应最大数据量  

### 2. CreeperLordVader ⭐⭐⭐⭐  
**亮点**：  
- 创新性地用DFS代替SPFA检测负环  
- 通过双重标记（vis/use）避免重复访问  
- 处理不连通图的完整方案  

### 3. Wen_kr ⭐⭐⭐⭐  
**亮点**：  
- 标准差分约束实现模板  
- 引入坐标范围剪枝（1e9约束）  
- 队列实现SPFA的清晰演示  

---

## 最优思路与代码示例  
### 带权并查集核心代码  
```cpp
int find(int x) { // 路径压缩+距离更新
    if(fa[x] != x) {
        int nf = fa[x];
        fa[x] = find(fa[x]);
        dis[x] += dis[nf]; // 关键！叠加父节点距离
    }
    return fa[x];
}

void merge(int l, int r, int d) {
    int rl = find(l), rr = find(r);
    if(rl == rr) {
        if(dis[l] - dis[r] != d) ok = 0;
    } else {
        fa[rl] = rr;
        dis[rl] = d + dis[r] - dis[l]; // 关键！调整根节点距离
    }
}
```

---

## 相似题目推荐  
1. [P2024 食物链](https://www.luogu.com.cn/problem/P2024)（经典带权并查集）  
2. [P1993 小K的农场](https://www.luogu.com.cn/problem/P1993)（差分约束系统）  
3. [P4185 [USACO18JAN]MooTube G](https://www.luogu.com.cn/problem/P4185)（离线查询+并查集）  

---

## 调试心得摘录  
> "最初忘记在路径压缩时更新dis数组，导致WA。通过单步调试发现旧父节点的距离未累加，加入dis[x] += dis[nf]后解决。" —— Doraven题解评论区  

---

## 复古动画JS核心逻辑（伪代码）  
```javascript
class PixelUF {
  constructor(n) {
    this.nodes = Array(n).fill().map((_,i) => ({
      x: i*50%800, y: Math.floor(i/16)*50, 
      parent: i, dis: 0, color: COLORS[i%8]
    }));
  }

  find(x) {
    if(this.nodes[x].parent != x) {
      let oldParent = this.nodes[x].parent;
      this.find(oldParent);
      this.nodes[x].dis += this.nodes[oldParent].dis; // 高亮黄色
      this.nodes[x].parent = this.nodes[oldParent].parent;
      playSound('blip'); // 8位音效
    }
    return this.nodes[x].parent;
  }
}
```

---

## 核心难点突破  
当处理约束 (l,r,d) 时：  
1. **路径压缩**确保l和r直接指向当前根节点  
2. 合并时通过 `dis[rl] = d + dis[r] - dis[l]` 建立新关系  
3. 该公式推导：  
   - 原式 x_r - x_l = d  
   - 转换为 x_rl = x_rr - dis[r] + d + dis[l]  
   - （其中x_rl表示原l的根节点到新根节点rr的偏移量）

---
处理用时：67.08秒