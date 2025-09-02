# 题目信息

# 「EZEC-9」GCD Tree

## 题目背景

规定 $\gcd(x,y)$ 表示 $x,y$ 的最大公约数，$\operatorname{lca}(x,y)$ 表示 $x$ 号节点和 $y$ 号节点的最近公共祖先。

## 题目描述

给你 $n$ 个点，编号分别为 $1,2,\ldots,n$，点权分别为 $a_1,a_2,\ldots,a_n$。

请你用这 $n$ 个点构造一棵树，使得 $\forall 1 \le i < j \le n$，$\gcd(a_i, a_j) = a_{\operatorname{lca}(i, j)}$。

若无解，报告之，否则输出树的形态。

## 说明/提示

**【数据规模与约定】**

**本题采用捆绑测试。**

-  Subtask 1（5 points）：$n = 2$。
-  Subtask 2（5 points）：所有 $a_i$ 均相等。
-  Subtask 3（5 points）：$n \le 5$。
-  Subtask 4（10 points）：保证有解。
-  Subtask 5（15 points）：$n \le 100$。
-  Subtask 6（15 points）：$n \le 10^3$。
-  Subtask 7（15 points）：$n \le 3 \times 10^3$。
-  Subtask 8（30 points）：无特殊限制。

对于 $100 \%$ 的数据，$2 \le n \le 10^5$，$1 \le a_i \le 10^6$。

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
0 1 1 2 1
```

## 样例 #2

### 输入

```
5
1 2 3 4 6
```

### 输出

```
-1
```

# AI分析结果



## 唯一算法分类
图论 - 树构造

---

## 综合分析与结论

### 核心思路与难点
本题要求构造满足特定 GCD-LCA 条件的树。核心思路是通过因数倍数关系建立树结构，并验证所有可能的 GCD 条件：

1. **缩点处理**：相同权值的节点必须形成链式结构，只保留一个代表节点参与树构造。
2. **贪心建树**：按权值从大到小处理节点，将每个节点的父节点设为最大的存在的因数对应的节点。
3. **合法性验证**：检查所有可能的 GCD 值，确保其对应的节点子树结构正确。

### 可视化设计思路
- **像素风格展示**：用 8-bit 网格表示权值分布，高亮当前处理的节点（如红色方块）。
- **父节点连接动画**：用绿色箭头动态连接节点与其父节点，展示倍数关系的处理过程。
- **验证阶段特效**：当检查某个 GCD 值时，用黄色闪烁标记所有该值的倍数节点，并显示子树范围。

---

## 题解清单 (≥4星)

### 1. 作者：littleKtian (⭐⭐⭐⭐⭐)
- **亮点**：高效处理倍数关系，通过哈希表快速查询节点，时间复杂度 O(n log n + V log V)
- **关键代码**：
```cpp
for(int i=N;i;i--)if(xh[i]){
  for(int j=i*2;j<=N;j+=i)if(xh[j]&&!fa[xh[j]])
    fa[xh[j]]=xh[i], tj(xh[i],xh[j]),++tt;
}
```

### 2. 作者：LZDQ (⭐⭐⭐⭐)
- **亮点**：通过质因数分解验证子树条件，用调和级数优化验证过程
- **关键代码**：
```cpp
for(int i=2; i<=m; i++){
  int s=0,t=0;
  for(int j=i; j<=m; j+=i)if(p[j]){
    if(dep[t]<dep[mx[j]]) t=mx[j];
  }
  while(t>1){
    if(t/fw[t]%i==0) s--;
    t=fw[t];
  }
  if(s) return puts("-1");
}
```

### 3. 作者：chenxinyang2006 (⭐⭐⭐⭐)
- **亮点**：利用倍增 LCA 快速验证子树合法性，树高 log V 特性优化验证
- **关键代码**：
```cpp
int LCA(int u,int v){
  if(dep[u]<dep[v]) swap(u,v);
  for(int i=4;i>=0;i--) if(dep[to[i][u]]>=dep[v]) u=to[i][u];
  return u==v ? u : to[0][u];
}
```

---

## 最优思路提炼

### 关键技巧
1. **因数链式构造**：每个节点的父节点选择其最大存在的因数节点，保证路径上的权值单调递减
2. **调和级数验证**：枚举每个可能的 GCD 值 d，检查其倍数节点是否构成单一子树
3. **质因数分治**：将验证问题转化为质数倍数的链式检查，避免暴力枚举所有点对

---

## 相似题目推荐
1. [P1364 医院设置](https://www.luogu.com.cn/problem/P1364) - 树结构性质应用
2. [P2421 质数分解](https://www.luogu.com.cn/problem/P2421) - 因数倍数关系的应用 
3. [CF1328E Tree Queries](https://codeforces.com/problemset/problem/1328/E) - 树路径验证技巧

---

## 可视化方案设计

### 核心动画逻辑
```javascript
// 伪代码示例
class TreeVisualizer {
  constructor() {
    this.canvas = initCanvas(); // 初始化像素画布
    this.nodes = []; // 节点坐标及颜色状态
    this.speed = 1; // 动画速度控制
  }

  buildTree() {
    // 分步演示缩点、父节点连接过程
    for (let val = MAX_VAL; val >= 1; val--) {
      highlight(val); // 红色高亮当前处理节点
      for (let multiple = val*2; multiple <= MAX_VAL; multiple += val) {
        drawArrow(val, multiple); // 绿色箭头连接父子
        delay(1000/this.speed);
      }
    }
  }

  validateGCD(d) {
    // 黄色闪烁显示所有d的倍数节点
    flashNodes(dMultiples, 'yellow'); 
    // 检查子树是否单连通
    if (disconnected) playFailSound(); 
  }
}
```

### 复古特效
- **音效设计**：
  - 连接父节点时播放 8-bit "beep" 音
  - 验证失败时播放短促下降音调
  - 背景音乐采用 FC 风格循环旋律

---

## 核心代码实现

### 缩点与建树关键逻辑
```cpp
unordered_map<int, int> xh; // 权值到节点的映射
for (int i = 1; i <= n; i++) {
  if (xh[a[i]]) fa[i] = xh[a[i]]; // 重复权值链式处理
  else xh[a[i]] = i;
}

for (int i = MAX_VAL; i >= 1; i--) {
  if (!xh[i]) continue;
  for (int j = 2*i; j <= MAX_VAL; j += i) { // 处理倍数
    if (xh[j] && !fa[xh[j]]) {
      fa[xh[j]] = xh[i]; // 设置父节点
      addEdge(xh[i], xh[j]); // 添加树边
    }
  }
}
```

### 合法性验证逻辑
```cpp
vector<bool> invalid(MAX_VAL+1);
for (int d = 1; d <= MAX_VAL; d++) {
  int cnt = 0, last = -1;
  for (int k = d; k <= MAX_VAL; k += d) {
    if (!xh[k]) continue;
    if (last == -1) last = xh[k];
    else last = lca(last, xh[k]); // 计算LCA
    cnt++;
  }
  if (cnt >= 2 && a[last] != d) 
    return -1; // 存在非法GCD
}
```

---

通过上述方案，可高效构造并验证满足条件的树结构，同时通过可视化手段直观展示算法关键步骤。

---
处理用时：97.32秒