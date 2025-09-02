# 题目信息

# Desk Disorder

## 题目描述

A new set of desks just arrived, and it's about time! Things were getting quite cramped in the office. You've been put in charge of creating a new seating chart for the engineers. The desks are numbered, and you sent out a survey to the engineering team asking each engineer the number of the desk they currently sit at, and the number of the desk they would like to sit at (which may be the same as their current desk). Each engineer must either remain where they sit, or move to the desired seat they indicated in the survey. No two engineers currently sit at the same desk, nor may any two engineers sit at the same desk in the new seating arrangement.

How many seating arrangements can you create that meet the specified requirements? The answer may be very large, so compute it modulo $ 1000000007=10^{9}+7 $ .

## 说明/提示

These are the possible assignments for the first example:

- 1 5 3 7
- 1 2 3 7
- 5 2 3 7
- 1 5 7 3
- 1 2 7 3
- 5 2 7 3

## 样例 #1

### 输入

```
4
1 5
5 2
3 7
7 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
1 10
2 10
3 10
4 10
5 5
```

### 输出

```
5
```

# AI分析结果



# 算法分类
无算法分类

# 题解分析与结论
## 核心思路与难点
**核心思路**：将每个工程师的座位变迁建模为有向边，形成若干连通图。通过分析连通图类型（树/环/基环树/自环）计算方案数：
1. **树结构**：方案数为树的大小（每个节点到根链式移动的可能性）
2. **环或基环树**：方案数为2（整个环移动或不移动）
3. **自环**：方案数为1（无法移动）

**难点**：
- 如何高效检测连通图类型（使用并查集维护连通性）
- 处理自环的特殊情况（需单独标记）
- 正确统计每个连通块对总方案数的贡献（乘法原理）

## 题解评分（≥4星）
1. **作者：是个汉子（⭐⭐⭐⭐⭐）**  
   - 亮点：分类讨论清晰，代码变量命名规范，通过`sf_cir`标记自环，通过`cir`数组标记环  
   - 代码可读性：高（使用注释说明关键逻辑）  
   - 实践性：直接给出完整代码，适合快速实现  

2. **作者：yuhaocheng（⭐⭐⭐⭐）**  
   - 亮点：通过示例图辅助理解，详细证明基环树的不可移动性  
   - 代码可读性：中等（存在冗余变量如`ish`和`iszh`）  
   - 实践性：提供完整代码，但合并逻辑稍显复杂  

3. **作者：chengni（⭐⭐⭐⭐）**  
   - 亮点：代码简洁，通过`loop`和`c`数组分别处理自环和环  
   - 代码可读性：高（变量命名直观，无冗余操作）  
   - 实践性：适合快速实现，但缺少详细注释  

# 最优思路与技巧
1. **并查集维护连通性**：合并新旧座位时检测环，合并后维护集合大小  
2. **自环特殊处理**：若`x == y`直接标记自环，避免误判为普通环  
3. **贡献分类计算**：  
   ```cpp
   if (自环存在) continue;          // 贡献1，不改变总结果  
   else if (环或基环树) ans *= 2;   // 贡献2  
   else ans *= 树大小;             // 贡献siz[i]
   ```

# 同类型题与算法套路
1. **常见图论问题**：检测环的存在性（如洛谷P2661 信息传递）  
2. **连通块贡献计算**：通过乘法原理合并独立子问题的解  
3. **并查集高级应用**：维护附加信息（如集合大小、环标记）

# 推荐题目
1. [洛谷P2661] 信息传递（最小环检测）  
2. [洛谷P3387] 缩点（强连通分量处理）  
3. [CF455D] 图的动态连通性维护  

# 个人心得摘录
- **自环处理教训**：若未单独标记自环，可能导致将自环误判为普通环，错误计算贡献为2  
- **并查集优化**：路径压缩时需同步更新附加信息（如`sf_cir`标记的或操作）  
- **调试技巧**：构造包含树、环、自环的测试用例验证各部分逻辑  

# 可视化与算法演示
## 核心逻辑演示
**动画设计**：  
1. **节点与边绘制**：用不同颜色区分树（绿色）、环（红色）、自环（黄色）  
2. **并查集操作**：合并节点时显示连通块边界，检测到环时高亮显示  
3. **贡献计算**：右侧面板实时显示总方案数，每次连通块处理时更新  

**复古像素风格**：  
- **颜色方案**：8位色（#00FF00树、#FF0000环、#FFFF00自环）  
- **音效设计**：  
  - 合并成功：短促“滴”声  
  - 检测到环：低音“咚”声  
  - 自环标记：高音“叮”声  

**AI自动演示**：  
```javascript
// 伪代码：自动遍历所有边并合并节点
function autoRun() {
  edges.forEach((edge, index) => {
    setTimeout(() => merge(edge.u, edge.v), index * 1000);
  });
}
```

# 关键代码片段（作者：是个汉子）
```cpp
for(int i=1,x,y;i<=n;i++){
    scanf("%d%d",&x,&y);
    if(x==y) sf_cir[x]=1;
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        f[fx]=fy;
        sf_cir[fy]|=sf_cir[fx]; // 合并自环标记
        siz[fy]+=siz[fx];
    } else cir[fx]=1; // 标记环
}

ll ans=1;
for(int i=1;i<=2*n;i++){
    if(find(i)==i && !sf_cir[i]){ // 排除自环
        if(cir[i]) ans = ans*2%mod; // 环贡献2
        else ans = ans*siz[i]%mod; // 树贡献siz
    }
}
```

---
处理用时：71.70秒