# 题目信息

# Snow Footprints

## 题目描述

There is a straight snowy road, divided into $ n $ blocks. The blocks are numbered from 1 to $ n $ from left to right. If one moves from the $ i $ -th block to the $ (i+1) $ -th block, he will leave a right footprint on the $ i $ -th block. Similarly, if one moves from the $ i $ -th block to the $ (i-1) $ -th block, he will leave a left footprint on the $ i $ -th block. If there already is a footprint on the $ i $ -th block, the new footprint will cover the old one.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF298A/67d5fe232964f55b35f1d37315e4e2b333131dd5.png)At the beginning, there were no footprints. Then polar bear Alice starts from the $ s $ -th block, makes a sequence of moves and ends in the $ t $ -th block. It is known that Alice never moves outside of the road.

You are given the description of Alice's footprints. Your task is to find a pair of possible values of $ s,t $ by looking at the footprints.

## 说明/提示

The first test sample is the one in the picture.

## 样例 #1

### 输入

```
9
..RRLL...
```

### 输出

```
3 4
```

## 样例 #2

### 输入

```
11
.RRRLLLLL..
```

### 输出

```
7 5
```

# AI分析结果



# Snow Footprints

## 题目描述

有一条笔直的雪路，被划分为 $n$ 个块，编号从 1 到 $n$。当从第 $i$ 块移动到第 $(i+1)$ 块时，会在第 $i$ 块留下右脚印（R）；若从第 $i$ 块移动到第 $(i-1)$ 块，则会在第 $i$ 块留下左脚印（L）。新脚印会覆盖旧脚印。已知 Alice 从起点 $s$ 出发，经过一系列移动后停在终点 $t$，且移动路径不超出道路。根据最终的脚印序列，求可能的 $s$ 和 $t$。

## 算法分类
构造、模拟

## 题解对比与总结

### 关键思路
1. **合法序列结构**：脚印序列只能是全 R、全 L 或 R 后接 L 的形式（如 `RRRLLL`）。若存在交替（如 `RLR` 或 `LRL`），则无解。
2. **起点与终点确定**：
   - 全 R：起点为第一个 R 的位置，终点为最后一个 R 的位置 +1。
   - 全 L：起点为最后一个 L 的位置，终点为第一个 L 的位置 -1。
   - R 后接 L：起点为第一个 R 的位置，终点为第一个 L 的位置 -1。

### 高分题解（≥4星）

#### 题解：Night_sea_64（4星）
- **亮点**：通过记录 R 和 L 的左右端点，分情况输出，逻辑清晰，代码简洁。
- **代码核心**：
  ```cpp
  int Rl=0, Rr=0, Ll=0, Lr=0;
  for (int i=1; i<=n+1; i++) {
      if (a[i]=='R' && a[i-1]!=a[i]) Rl=i;  // R 左端点
      if (a[i]=='L' && a[i-1]!=a[i]) Ll=i;  // L 左端点
      if (a[i-1]=='R' && a[i-1]!=a[i]) Rr=i-1;  // R 右端点
      if (a[i-1]=='L' && a[i-1]!=a[i]) Lr=i-1;  // L 右端点
  }
  if (全 R) cout << Rl << " " << Rr+1;
  else if (全 L) cout << Lr << " " << Ll-1;
  else cout << Rl << " " << Ll-1;
  ```

#### 题解：_Violet_Evergarden（4星）
- **亮点**：直接处理 R 和 L 的首次和末次出现位置，逻辑简洁。
- **代码核心**：
  ```cpp
  for (int i=1; i<=n; i++) {
      if (a[i]=='R') {
          if (!fr) fr = i;
          lr = i;
      }
      if (a[i]=='L') {
          if (!fl) fl = i;
          ll = i;
      }
  }
  if (全 R) cout << fr << " " << lr+1;
  else if (全 L) cout << ll << " " << fl-1;
  else cout << fr << " " << fl-1;
  ```

### 通用技巧
1. **边界处理**：在字符串前后添加哨兵字符（如 `.`）以简化端点判断。
2. **覆盖规则**：最后的移动方向决定每个块的最终脚印，需保证 R 和 L 的连续性。

## 拓展与相似题目
1. **类似构造题**：
   - [CF1144F. Graph Without Long Directed Paths](https://www.luogu.com.cn/problem/CF1144F)（构造路径方向）
   - [CF1328C. Ternary XOR](https://www.luogu.com.cn/problem/CF1328C)（字符序列构造）
   - [CF977D. Divide by three, multiply by two](https://www.luogu.com.cn/problem/CF977D)（序列构造与覆盖逻辑）

---
处理用时：366.19秒