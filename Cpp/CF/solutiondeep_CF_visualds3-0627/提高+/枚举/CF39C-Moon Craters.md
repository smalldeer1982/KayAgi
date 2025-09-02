# 题目信息

# Moon Craters

## 题目描述

There are lots of theories concerning the origin of moon craters. Most scientists stick to the meteorite theory, which says that the craters were formed as a result of celestial bodies colliding with the Moon. The other version is that the craters were parts of volcanoes.

An extraterrestrial intelligence research specialist professor Okulov (the namesake of the Okulov, the author of famous textbooks on programming) put forward an alternate hypothesis. Guess what kind of a hypothesis it was –– sure, the one including extraterrestrial mind involvement. Now the professor is looking for proofs of his hypothesis.

Professor has data from the moon robot that moves linearly in one direction along the Moon surface. The moon craters are circular in form with integer-valued radii. The moon robot records only the craters whose centers lay on his path and sends to the Earth the information on the distance from the centers of the craters to the initial point of its path and on the radii of the craters.

According to the theory of professor Okulov two craters made by an extraterrestrial intelligence for the aims yet unknown either are fully enclosed one in the other or do not intersect at all. Internal or external tangency is acceptable. However the experimental data from the moon robot do not confirm this theory! Nevertheless, professor Okulov is hopeful. He perfectly understands that to create any logical theory one has to ignore some data that are wrong due to faulty measuring (or skillful disguise by the extraterrestrial intelligence that will be sooner or later found by professor Okulov!) That’s why Okulov wants to choose among the available crater descriptions the largest set that would satisfy his theory.

## 样例 #1

### 输入

```
4
1 1
2 2
4 1
5 1
```

### 输出

```
3
1 2 4
```

# AI分析结果



---

## 唯一算法分类  
**动态规划（区间DP）**

---

## 综合分析与结论  

### 核心问题与算法思路  
1. **问题转化**：将圆形陨石坑转化为数轴上的区间（左端点=中心-半径，右端点=中心+半径），问题等价于选择最多的区间，满足任意两个区间要么嵌套（含内切）要么相离（含外切）。  
2. **动态规划核心**：  
   - **状态定义**：`f[i][j]` 表示处理左端点≤i且右端点≤j的区间时的最大选择数。  
   - **转移方程**：  
     - 不选当前区间：`f[i][j] = f[i+1][j]`  
     - 选当前区间：`f[i][j] = f[i+1][k] + f[k][j] + 1`，其中k是当前区间的右端点。  
   - **预处理**：排序区间（左端点升序、右端点降序），预处理每个区间的后续区间位置（`nxt`数组）。  
3. **关键优化**：离散化端点压缩空间，排序后利用状态转移避免重复计算。

### 可视化设计思路  
- **像素动画**：  
  1. **区间绘制**：在Canvas中以不同颜色块表示区间，选中区间高亮为绿色，未选中为灰色。  
  2. **状态转移演示**：每次选择区间时，动态分割左右子区间，显示递归过程。  
  3. **音效触发**：选中区间时播放清脆音效，分割区间时播放“切割”音效。  
- **8位风格**：使用16色调色板，区间块用复古像素边框，背景音乐为8位循环曲目。  

---

## 题解清单 (≥4星)  

### 1. 封禁用户（★★★★☆）  
- **亮点**：状态设计巧妙，预处理`nxt`数组优化转移，代码结构清晰。  
- **核心代码**：  
  ```cpp
  for(int i=n-1; ~i; --i)
    for(int j=0; j<n; ++j){
      dp[i][j] = dp[i+1][j]; // 不选当前区间
      if(node[i].r <= R[j]) // 选当前区间
        getMax(dp[i][j], dp[i+1][Rid[i]] + dp[nxt[i]][j] + 1);
    }
  ```

### 2. Durante（★★★★☆）  
- **亮点**：从内部最大数出发，排序保证子问题顺序，代码简洁。  
- **核心代码**：  
  ```cpp
  for(int i=1; i<=n+1; ++i){
    memset(dp,0,sizeof(dp));
    for(int j=a[i].l+1; j<=a[i].r; ++j){
      dp[j] = dp[j-1];
      for(auto id : v1[j]) // 处理右端点为j的区间
        dp[j] = max(dp[j], dp[a[id].l] + w[id]);
    }
    w[i] = dp[a[i].r] + 1;
  }
  ```

### 3. 信息向阳花木（★★★☆☆）  
- **亮点**：直观区间DP，离散化处理，但复杂度较高。  

---

## 最优思路提炼  

### 关键技巧  
1. **排序策略**：按左端点升序、右端点降序排序，确保处理大区间时其子区间已就绪。  
2. **预处理优化**：预先计算每个区间的后续位置（`nxt[i]`），加速状态转移。  
3. **离散化压缩**：将端点映射到连续整数，降低空间复杂度。  

### 代码实现片段（封禁用户版）  
```cpp
// 预处理nxt数组
for(int i=0; i<n; ++i){
  nxt[i] = n; // 默认无后续区间
  for(int j=0; j<n; ++j)
    if(node[i].r <= node[j].l){
      nxt[i] = j; break;
    }
}
```

---

## 同类型题推荐  
1. **P2305 最长回文子序列**（区间DP）  
2. **P1880 石子合并**（环形区间DP）  
3. **P1043 数字游戏**（区间分割DP）  

---

## 可视化与游戏化设计  

### 动画流程  
1. **初始化**：绘制数轴，离散化后的区间按排序位置显示。  
2. **递归选择**：高亮当前处理的区间，播放音效，递归分裂左右子区间。  
3. **动态更新**：用颜色区分已选/未选区间，右侧面板显示当前最大数量。  

### 复古元素  
- **调色板**：深蓝背景，亮绿选中块，红色分割线。  
- **音效**：选择区间（方波音），错误（噪音短音）。  

---

**通过上述分析与实现，可高效解决该问题并深入理解区间DP的核心思想。**

---
处理用时：86.71秒