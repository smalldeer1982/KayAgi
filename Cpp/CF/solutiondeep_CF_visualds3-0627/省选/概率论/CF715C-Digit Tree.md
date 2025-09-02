# 题目信息

# Digit Tree

## 题目描述

ZS the Coder has a large tree. It can be represented as an undirected connected graph of $ n $ vertices numbered from $ 0 $ to $ n-1 $ and $ n-1 $ edges between them. There is a single nonzero digit written on each edge.

One day, ZS the Coder was bored and decided to investigate some properties of the tree. He chose a positive integer $ M $ , which is coprime to $ 10 $ , i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/9b5bdec4cb6231baa1f3fcb57eb25703ae0eed8f.png).

ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting when if he would follow the shortest path from vertex $ u $ to vertex $ v $ and write down all the digits he encounters on his path in the same order, he will get a decimal representaion of an integer divisible by $ M $ .

Formally, ZS consider an ordered pair of distinct vertices $ (u,v) $ interesting if the following states true:

- Let $ a_{1}=u,a_{2},...,a_{k}=v $ be the sequence of vertices on the shortest path from $ u $ to $ v $ in the order of encountering them;
- Let $ d_{i} $ ( $ 1<=i&lt;k $ ) be the digit written on the edge between vertices $ a_{i} $ and $ a_{i+1} $ ;
- The integer ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/72be647436ef167ccaba4334e08ad71c22afc6b4.png) is divisible by $ M $ .

Help ZS the Coder find the number of interesting pairs!

## 说明/提示

In the first sample case, the interesting pairs are $ (0,4),(1,2),(1,5),(3,2),(2,5),(5,2),(3,5) $ . The numbers that are formed by these pairs are $ 14,21,217,91,7,7,917 $ respectively, which are all multiples of $ 7 $ . Note that $ (2,5) $ and $ (5,2) $ are considered different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/08c05395fdf8f9a998abf43b020555e6b5471bd5.png)In the second sample case, the interesting pairs are $ (4,0),(0,4),(3,2),(2,3),(0,1),(1,0),(4,1),(1,4) $ , and $ 6 $ of these pairs give the number $ 33 $ while $ 2 $ of them give the number $ 3333 $ , which are all multiples of $ 11 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF715C/8a71025758e81b9cf19889885872aec3ca3f5ffc.png)

## 样例 #1

### 输入

```
6 7
0 1 2
4 2 4
2 0 1
3 0 9
2 5 7
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 11
1 2 3
2 0 3
3 0 3
4 3 3
```

### 输出

```
8
```

# AI分析结果



# Digit Tree 题解分析

## 1. 算法分类  
**点分治**

---

## 2. 题解思路与核心算法  

### **算法要点**  
1. **分治思想**：  
   - 通过点分治处理树上的路径统计问题，每次选择重心作为分治中心，统计经过该中心的路径，递归处理子树。  
   - 路径分为两类：从分治中心到子树的路径（`d1`）和从子树到分治中心的路径（`d2`），通过公式变形转化为模运算匹配问题。  

2. **模运算与逆元**：  
   - 路径拼接公式为 `d1 * 10^len(d2) + d2 ≡ 0 (mod M)`，变形为 `d1 ≡ -d2 * 10^{-len(d2)} (mod M)`。  
   - 预处理 `10^x` 和其逆元 `10^{-x}`，使用扩展欧几里得求逆元。  

3. **数据结构与优化**：  
   - 使用 `map` 或哈希表存储路径值的出现次数，避免重复计算。  
   - 在点分治中通过容斥排除同一子树内的重复贡献。  

---

### **解决难点**  
- **逆元处理**：由于 `M` 可能与 `10` 不互质，必须使用扩展欧几里得求逆元。  
- **路径拼接的数学变形**：将路径拼接问题转化为模等式匹配，需预处理 `10^x` 的幂次和逆元。  
- **避免重复统计**：在分治过程中需排除同一子树内的路径组合，采用先减后加的容斥策略。  

---

## 3. 题解评分（≥4星）  

### **orangejuice（5星）**  
- **亮点**：使用 DSU on Tree 高效合并子树信息，代码结构清晰，注释详细。  
- **核心代码**：  
  ```cpp
  void dfs_getans(int u,int f,int h) {
      for(int i=head[u]; ~i; i=e[i].nxt)
          if(e[i].to!=f&&e[i].to!=son[u])
              dfs_getans(e[i].to,u,0);
      if(son[u]) dfs_getans(son[u],u,1);
      for(int i=head[u]; ~i; i=e[i].nxt) 
          if(e[i].to!=f&&e[i].to!=son[u]) {
              Upd(e[i].to,u,u,1); // 统计轻子树贡献
              Upd(e[i].to,u,u,0); // 合并轻子树信息
          }
      Calc(u,u); // 计算以 u 为 LCA 的路径
      Add(u);    // 将当前点加入全局 map
  }
  ```

### **MikukuOvO（4.5星）**  
- **亮点**：点分治模板清晰，利用公式变形简化统计，代码可读性强。  
- **核心代码**：  
  ```cpp
  void solve(int u) {
      vis[u] = 1, ans += calc(u, 0); // 统计经过 u 的路径
      for(int i=head[u]; i; i=e[i].nxt) {
          int v = e[i].to;
          if(vis[v]) continue;
          ans -= calc(v, e[i].w); // 容斥排除同一子树
          getrt(v, u, size[v]);   // 找新重心
          solve(rt);              // 递归处理子树
      }
  }
  ```

### **Super_Cube（4星）**  
- **亮点**：代码简洁，使用 `map` 实现路径匹配，注释详细。  
- **核心代码**：  
  ```cpp
  void calc(int u) {
      for(auto &[v,w]: G[u]) {
          if(vis[v]) continue;
          get_path(v, u, w, w, 1); // 获取子树路径信息
          for(auto [d1,d2,dep]: paths) {
              ans += cnt[ (-d1 * inv_p10[dep] % mod + mod) % mod ];
          }
          for(auto [d1,d2,dep]: paths) 
              cnt[d2]++; // 将子树路径加入全局统计
      }
  }
  ```

---

## 4. 最优思路提炼  
- **分治策略**：点分治分解路径，统计经过重心的合法路径。  
- **数学变形**：利用逆元将路径拼接公式转化为模等式匹配问题。  
- **高效统计**：使用 `map` 或哈希表存储中间结果，避免暴力枚举路径。  

---

## 5. 类似题目推荐  
1. **P2634 [国家集训队] 聪聪可可**（树上路径模 3 计数）  
2. **P3806 点分治模板**（统计路径长度等于 k 的路径数）  
3. **P4149 [IOI2011]Race**（统计边权和为 k 的最短路径）  

---

## 6. 可视化与算法演示  

### **动画设计**  
1. **分治中心分解**：  
   - 以像素风格显示树结构，当前分治中心高亮为红色。  
   - 递归分解子树时，子树区域渐变为不同颜色。  

2. **路径匹配演示**：  
   - 显示从分治中心到子节点的路径 `d1`（蓝色箭头）和反向路径 `d2`（绿色箭头）。  
   - 当 `d1` 和 `d2` 满足模等式时，路径端点闪烁黄色。  

3. **音效与交互**：  
   - **关键操作音效**：路径匹配成功时播放“叮”声，分治中心切换时播放“咔嚓”声。  
   - **自动演示模式**：按空格键切换手动/自动模式，自动模式下分治过程逐步播放。  

---

## 7. 核心代码实现  
```cpp
// 预处理 10^x 和逆元
void precompute() {
    pow10[0] = inv10[0] = 1;
    for(int i=1; i<=n; i++) {
        pow10[i] = pow10[i-1] * 10 % mod;
        inv10[i] = inv(pow10[i]); // 扩展欧几里得求逆元
    }
}

// 点分治核心逻辑
void solve(int u) {
    vis[u] = true;
    ans += calc(u, 0); // 统计经过 u 的路径
    for(auto [v,w] : adj[u]) {
        if(vis[v]) continue;
        ans -= calc(v, w); // 容斥排除同一子树
        get_root(v, u, size[v]); // 找新重心
        solve(root); // 递归处理子树
    }
}
```

---

## 8. 个人心得  
- **调试经验**：在处理逆元时，需注意负数取模，例如 `-d % mod` 应写为 `(mod - d % mod) % mod`。  
- **优化技巧**：预处理 `10^x` 和逆元可大幅减少计算量，避免重复调用扩展欧几里得算法。  
- **思维突破**：将路径拼接问题转化为模等式匹配是核心，需熟练掌握模运算的变形技巧。

---
处理用时：84.79秒