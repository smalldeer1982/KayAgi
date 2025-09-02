# 题目信息

# Geometry Horse

## 题目描述

Vasya plays the Geometry Horse.

The game goal is to destroy geometric figures of the game world. A certain number of points is given for destroying each figure depending on the figure type and the current factor value.

There are $ n $ types of geometric figures. The number of figures of type $ k_{i} $ and figure cost $ c_{i} $ is known for each figure type. A player gets $ c_{i}·f $ points for destroying one figure of type $ i $ , where $ f $ is the current factor. The factor value can be an integer number from $ 1 $ to $ t+1 $ , inclusive. At the beginning of the game the factor value is equal to 1. The factor is set to $ i+1 $ after destruction of $ p_{i} $ $ (1<=i<=t) $ figures, so the $ (p_{i}+1) $ -th figure to be destroyed is considered with factor equal to $ i+1 $ .

Your task is to determine the maximum number of points Vasya can get after he destroys all figures. Take into account that Vasya is so tough that he can destroy figures in any order chosen by him.

## 说明/提示

In the first example Vasya destroys three figures first and gets $ 3·1·10=30 $ points. Then the factor will become equal to $ 2 $ and after destroying the last two figures Vasya will get $ 2·2·10=40 $ points. As a result Vasya will get $ 70 $ points.

In the second example all $ 8 $ figures will be destroyed with factor $ 1 $ , so Vasya will get $ (3·8+5·10)·1=74 $ points.

## 样例 #1

### 输入

```
1
5 10
2
3 6
```

### 输出

```
70```

## 样例 #2

### 输入

```
2
3 8
5 10
1
20
```

### 输出

```
74```

# AI分析结果



# Geometry Horse

## 题目描述

瓦夏在玩几何战马游戏。游戏目标是通过摧毁几何图形获取分数，每个图形类型有特定数量和分数值。摧毁第i类图形的单个得分为当前因子f乘以该图形的固定分数c_i。因子初始为1，当累计摧毁p₁个图形后变为2，再摧毁p₂个变为3，直到因子变为t+1。

给定n种图形（k_i表数量，c_i表单值）、t个阶段阈值p₁~p_t，求可获取的最大总分数。

## 算法分类
贪心

## 题解分析与结论

各题解均采用贪心思路：按c_i从小到大处理图形，使低价值图形优先在低因子阶段被摧毁。核心难点在于高效处理阶段转换时的批量计算，避免逐个处理导致超时。最优解法使用分段批量计算，时间复杂度O(n+t)。

---

### 精选题解

#### 1. yuzhechuan（⭐⭐⭐⭐⭐）
**核心亮点**：  
- 通过`how=min(剩余数量, 当前阶段容量)`实现批量计算  
- 使用p[m+1]=INF避免边界判断  
- 时间复杂度最优的O(n+t)实现  

**关键代码**：
```cpp
sort(a+1,a+1+n,cmp); // 按c_i升序排序
p[m+1] = 0x7fffffffffff; 
int pt=0, f=1; // 当前已摧毁数、当前因子
for(int i=1;i<=n;i++) {
    for(int j=1;j<=a[i].k;){
        int how = min(a[i].k-j+1, p[f]-pt); 
        ans += f*a[i].c*how;
        pt += how;
        while(pt >= p[f] && f <= m) f++;
        j += how;
    }
}
```

#### 2. 傅天宇（⭐⭐⭐⭐）
**核心亮点**：  
- 阶段阈值预处理为差值数组，简化计算逻辑  
- 使用j+=x-1跳过已处理数量，避免重复循环  

**关键代码**：
```cpp
sort(G+1, G+1+n, cmp); 
p[t+1] = 1e11+5; 
FOR(i,1,n) {
    FOR(j,1,G[i].K) {
        int x = min(G[i].K-j+1, p[F]-Sum);
        Ans += F*G[i].C*x;
        Sum += x;
        while(Sum >= p[F] && F <= t) F++;
        j += x-1; // 跳过已处理区间
    }
}
```

#### 3. 泠小毒（⭐⭐⭐⭐）
**核心亮点**：  
- 将阶段阈值转换为增量数组，使每个阶段只需处理固定数量  
- 代码简洁，变量命名清晰  

**关键代码**：
```cpp
for(int i=m;i>1;i--) p[i]-=p[i-1]; 
p[m+1]=inf;
sort(a+1,a+1+n,cmp);
for(int i=1;i<=n;i++) {
    while(a[i].k > p[nw]) { // 完全填充当前阶段
        ans += 1ll*nw*a[i].c*p[nw];
        a[i].k -= p[nw];
        nw++;
    }
    ans += 1ll*nw*a[i].c*a[i].k; // 处理剩余部分
    p[nw] -= a[i].k;
}
```

---

## 关键思路总结
1. **贪心排序**：按c_i升序排列，确保低价值物品优先被处理  
2. **阶段批量处理**：通过`min(剩余量, 阶段容量)`一次性计算可处理数量，避免逐一遍历  
3. **边界处理**：在p数组末尾添加极大值，统一处理最后阶段的剩余数量  
4. **数据类型**：全程使用long long防止溢出  

---

## 同类型拓展
- 阶段式资源分配问题（如不同时段价格变化的股票买卖）  
- 带权重的时间窗口调度问题  

## 推荐练习题
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）  
2. P1208 [USACO1.3] 混合牛奶 Mixing Milk（价值排序+批量处理）  
3. P5019 [NOIP2018 提高组] 铺设道路（差分+阶段处理）

---
处理用时：68.00秒