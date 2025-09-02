# 题目信息

# Zrz_orz Loves Secondary Element

## 题目背景

zrz_orz赘喜欢二次元辣！！

## 题目描述

众所周知的是，zrz_orz是全机房最强的死宅。~~他甚至使用嘴遁使得Samcompu不得不在自己的网站上挂上时崎狂三~~。(话说Samcompu好像醒悟了又把狂三给去掉了。)作为新一代死宅的一员，从电脑壁纸到输入法皮肤，到处都是二次元的痕迹。所以，他经常在梦里梦见一些二次元的角色。

zrz_orz的梦，是由$n$个点和$n-1$条边构成的连通图。其中有$m$个节点上有一个二次元的角色。对于zrz_orz来说，每一个二次元的角色都有一个对应的$pos_i$和$val_i$表示这个角色在图上的哪一个节点以及与之聊天对zrz_orz来说会增加多少愉悦值。(由于某种原因，聊天的过程可以不用计入时间。)可惜的是，zrz_orz每一次做梦都只会做$tim_i$个单位时间。现在请你告诉他，他每一次做梦最多能获得多少愉悦值。

注：

1.zrz_orz每一次做梦都只会从1号节点开始走！

2.每一次做梦后zrz_orz梦境中的图都不会改变！

**3.每一次做完梦之后zrz_orz就必须要回到1号节点，否则他就会迷失在梦境里！**

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/25600.png)

第一天哪里都去不了。

第二天1->3->6->7->6->3->1获得最大愉悦值为7。

第三天所有的地方都可以走一遍。

Subtask 1(20 pts): 

$ 1 \leqslant T \leqslant 10 \qquad 1 \leqslant N \leqslant 1000 \qquad 1 \leqslant M \leqslant 20 \qquad 1 \leqslant  tim_k \leqslant 1000$

Subtask 2(40 pts):

$ 1 \leqslant T \leqslant 10^5 \qquad 1 \leqslant N \leqslant 10^5 \qquad 1 \leqslant M \leqslant 20 \qquad 1 \leqslant  tim_k \leqslant 10^5$

Subtask 3(40 pts):

$ 1 \leqslant T \leqslant 5*10^4 \qquad 1 \leqslant N \leqslant 5000 \qquad 1 \leqslant M \leqslant 100 \qquad 1 \leqslant  tim_k \leqslant 100 \qquad 1 \leqslant w_i \leqslant 5$

For all test points:

$ 1 \leqslant pos_j,u_i,v_i \leqslant N \qquad 1 \leqslant \sum val_j \leqslant 2e9 \qquad 1 \leqslant w_i \leqslant 20 \qquad 1 \leqslant tim_k \leqslant 10^5 $

注意: 标记的分数就是这个Subtask的分数，每一个Subtask必须全对才能得分。Subtask 2的时限为1.5s。

$$ \color{white} \text{NOIP 2合1} $$

## 样例 #1

### 输入

```
7 3 3
1 2 2
1 3 1
2 4 1
2 5 10
3 6 1
6 7 2
4 5
5 50
7 7
1
10
100
```

### 输出

```
0
7
62```

# AI分析结果



---

**算法分类**: 树形动态规划（Tree DP）与状态压缩（Submask Enumeration）

---

### **综合分析与结论**

**核心思路**：  
1. **往返时间处理**：所有路径边权×2，转化为单向时间计算。  
2. **分治策略**：  
   - **m≤20**：枚举所有角色组合（状压），计算路径时间并预处理最大值。  
   - **m较大**：树形DP，按子树合并背包状态，时间复杂度与时间限制相关。  
3. **虚树优化**：减少关键节点数，仅保留角色点及其LCA，降低DP复杂度。

**难点与解决方案**：  
- **路径时间计算**：通过虚树或预处理LCA快速求两点间距离。  
- **背包合并**：树形DP中子树状态需分组合并，避免重复计算。  
- **离线处理**：对状压方案按时间排序，结合二分快速响应查询。

**可视化设计要点**：  
- **树结构展示**：以Canvas绘制树节点，高亮虚树构建过程（关键节点与LCA）。  
- **状态转移动画**：动态演示DP背包合并过程，颜色区分不同子树贡献。  
- **复古像素风格**：使用8位色块表示节点，背包容量变化时播放“收集”音效。

---

### **题解清单 (≥4星)**

1. **CQ_Bob (4.5★)**  
   - **亮点**：虚树优化降低节点规模，分组背包实现高效DP。  
   - **代码**：通过`dfs2`递归合并子树状态，预处理前缀最大值加速查询。

2. **mrsrz (4.0★)**  
   - **亮点**：分情况处理m大小，新树构建减少无效节点。  
   - **代码**：`rebuild`函数动态生成虚树，状压枚举预处理所有组合。

3. **ztlh (4.0★)**  
   - **亮点**：结合dfn序优化LCA查询，分组背包实现简洁。  
   - **心得**：“枚举lowbit优化状态转移”显著减少计算量。

---

### **核心代码实现**

**CQ_Bob的树形DP关键片段**：  
```cpp
il void dfs2(int u,int s){
    siz[u]=0;
    if(s==0){
        dp1[u][0]=val[rev[u]];
        for(auto v:E[u]){
            dfs2(v.x,s);
            // 背包合并：当前子树与子节点子树
            for(re int w=min(M,siz[u]+v.y+siz[v.x]);w>=0;--w)
            for(re int x=0;x<=min(w-v.y,siz[u]);++x)
                dp1[u][w]=max(dp1[u][w],dp1[u][x]+dp1[v.x][w-v.y-x]);
            siz[u]+=v.y+siz[v.x];
        }
        // 前缀最大值预处理
        for(re int i=1;i<=M;++i)
            dp1[u][i]=max(dp1[u][i],dp1[u][i-1]);
    }
    // 类似处理dp2...
}
```

**mrsrz的状压预处理关键逻辑**：  
```cpp
void dfs(int now,int zt,int value){
    if(now==m){
        ++G.tot;
        int tim=0;
        // 计算该状态的总时间
        for(int i=zt,nx;i;i^=1<<nx){
            nx=__builtin_ctz(i);
            tim+=G.color(G.pos[nx]); // 路径时间计算
        }
        p[zt]=(zzt){value,tim<<1}; // 存储结果
    }else{
        dfs(now+1,zt,value); // 不选当前角色
        dfs(now+1,zt|(1<<now),value+val[now]); // 选当前角色
    }
}
```

---

### **同类型题推荐**

1. **P2014 [CTSC1997]选课** - 树形背包基础。  
2. **P1273 有线电视网** - 分组背包与树形DP结合。  
3. **P3959 宝藏** - 状压枚举与树结构优化。

---

### **个人心得摘录**

> “枚举所有可能的角色组合时，按dfn序排序能快速找到LCA，避免重复计算路径时间。” —— ztlh  
> “虚树构建后，DP状态仅需处理关键节点，极大降低复杂度。” —— CQ_Bob

---

### **可视化与算法演示**

**动画设计**：  
1. **树构建阶段**：  
   - 原树节点以绿色像素块显示，角色节点高亮为红色。  
   - 虚树构建时，动态绘制新增的LCA节点（蓝色），边权显示为黄色数字。  

2. **状压枚举演示**：  
   - 每个子集对应路径在Canvas上以闪烁线条显示，时间与价值实时更新。  
   - 音效：选择角色时播放“哔”声，路径计算完成时播放“叮”声。  

3. **树形DP过程**：  
   - 背包容量条动态增长，子树合并时高亮对应区域。  
   - 单步执行模式可观察每个节点的状态转移细节。  

**复古风格控制面板**：  
- **速度调节**：滑动条控制动画速度（1x至5x）。  
- **自动演示**：AI按最优路径逐步展开，背景播放8位风格BGM。  
- **积分系统**：正确完成某个子任务（如虚树构建）获得积分奖励。

---
处理用时：87.73秒