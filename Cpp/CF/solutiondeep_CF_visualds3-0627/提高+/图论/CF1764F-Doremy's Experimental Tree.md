# 题目信息

# Doremy's Experimental Tree

## 题目描述

Doremy has an edge-weighted tree with $ n $ vertices whose weights are integers between $ 1 $ and $ 10^9 $ . She does $ \frac{n(n+1)}{2} $ experiments on it.

In each experiment, Doremy chooses vertices $ i $ and $ j $ such that $ j \leq i $ and connects them directly with an edge with weight $ 1 $ . Then, there is exactly one cycle (or self-loop when $ i=j $ ) in the graph. Doremy defines $ f(i,j) $ as the sum of lengths of shortest paths from every vertex to the cycle.

Formally, let $ \mathrm{dis}_{i,j}(x,y) $ be the length of the shortest path between vertex $ x $ and $ y $ when the edge $ (i,j) $ of weight $ 1 $ is added, and $ S_{i,j} $ be the set of vertices that are on the cycle when edge $ (i,j) $ is added. Then,
 $$ f(i,j)=\sum_{x=1}^{n}\left(\min_{y\in S_{i,j}}\mathrm{dis}_{i,j}(x,y)\right).  $$
 
 Doremy writes down all values of  $ f(i,j) $  such that  $ 1 \leq j \leq i \leq n $ , then goes to sleep. However, after waking up, she finds that the tree has gone missing. Fortunately, the values of  $ f(i,j) $  are still in her notebook, and she knows which  $ i $  and  $ j $  they belong to. Given the values of  $ f(i,j)$, can you help her restore the tree?

It is guaranteed that at least one suitable tree exists.

## 说明/提示

In the first test case, the picture below, from left to right, from top to bottom, shows the graph when pairs $ (1,1) $ , $ (1,2) $ , $ (1,3) $ , $ (2,2) $ , $ (2,3) $ , $ (3,3) $ are connected with an edge, respectively. The nodes colored yellow are on the cycle.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764F/65b459471236cb3c4f73ac2ff04b74120b42f624.png)

## 样例 #1

### 输入

```
3
7
3 5
0 2 8```

### 输出

```
2 3 3
1 2 2```

## 样例 #2

### 输入

```
9
8081910646
8081902766 8081903751
8081902555 8081903540 8081905228
3090681001 3090681986 3090681775 7083659398
7083657913 7083658898 7083658687 2092437133 15069617722
1748216295 1748217280 1748217069 5741194692 749972427 10439821163
2377558289 2377559274 2377559063 6370536686 1379314421 5028071980 8866466178
1746983932 1746984917 1746984706 5739962329 748740064 10438588800 5026839617 10448447704
2341942133 2341943118 2341942907 6334920530 1343698265 4992455824 8830850022 4991223461 9115779270```

### 输出

```
1 2 985
2 3 211
2 4 998244353
2 5 998244853
4 6 671232353
6 8 1232363
4 7 356561356
7 9 35616156```

# AI分析结果



# 算法分类
**树的重建**

---

## 题解思路与核心难点分析

### 核心思路
通过计算任意两点间的路径长度，构建最小生成树还原原树结构。关键公式：  
$$dis(i,j) = \frac{f(i,i) + f(j,j) - 2f(i,j)}{n}$$  
原树为该距离图的最小生成树（边权为计算出的距离）。

### 解决难点
1. **路径长度推导**：通过环的性质与各点贡献推导出路径长度的计算式。
2. **生成树性质**：证明原树是该距离图的唯一生成树，确保结构正确。
3. **边权计算**：直接使用公式得出的距离作为生成树边权。

---

## 高星题解推荐（≥4星）

### 1. Leasier（4.5星）
- **亮点**：通过排序与父子关系确定树结构，巧妙利用子树大小计算边权。
- **关键代码**：
  ```cpp
  for (int i = 2; i <= n; i++) {
    int pos = -1;
    for (int j = 1; j < i; j++) {
      if (pos == -1 || f[pr[i].second][pos] < f[pr[i].second][pr[j].second]) 
        pos = pr[j].second;
    }
    fa[pr[i].second] = pos;
  }
  ```

### 2. MSqwq（4.5星）
- **亮点**：直接计算距离后构建最小生成树，代码简洁高效。
- **关键代码**：
  ```cpp
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      e[++num] = {i, j, (a[i][i] + a[j][j] - 2 * a[i][j]) / n};
    }
  }
  sort(e + 1, e + 1 + num, cmp);
  ```

### 3. spdarkle（4星）
- **亮点**：公式推导清晰，最小生成树思路普适性强。
- **核心思想**：通过点对距离公式生成完全图的最小生成树。

---

## 最优思路提炼
1. **距离公式**：计算所有点对的路径长度 $dis(i,j)$。
2. **生成树构建**：使用 Kruskal 或 Prim 算法生成最小生成树。
3. **边权直接确定**：生成树的边权即为 $dis(i,j)$。

---

## 同类型题目套路
- **树重建问题**：通过特定函数（如距离和、路径特征）逆向构造树结构。
- **生成树应用**：利用生成树性质（唯一路径、最小性）还原隐藏结构。

---

## 推荐练习题
1. **P3366**（最小生成树模板）
2. **P1395**（树的重心与路径计算）
3. **P2299**（最短路与生成树结合）

---

## 可视化设计
### 动画方案
1. **像素风格界面**：  
   - **节点**：8-bit 方块，不同颜色表示是否在生成树中。  
   - **边**：绿色表示已加入生成树，红色表示未选中。  
2. **关键步骤**：  
   - **计算距离**：显示公式推导过程，高亮当前处理点对。  
   - **生成树构建**：逐步添加边，播放“点击”音效，加入时绿色闪烁。  
3. **交互功能**：  
   - **速度调节**：滑块控制动画速度（0.5x~3x）。  
   - **步进模式**：按空格键单步执行 Kruskal 的边选择。  

### 代码片段（Canvas 绘制）
```javascript
function drawEdge(edge, color) {
  ctx.strokeStyle = color;
  ctx.beginPath();
  ctx.moveTo(nodes[edge.u].x, nodes[edge.u].y);
  ctx.lineTo(nodes[edge.v].x, nodes[edge.v].y);
  ctx.stroke();
}
```

---

## 核心代码实现（MSqwq）
```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
struct edge{int u,v,w;} e[4000005];
int fa[2005],n,cnt;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            ll f; scanf("%lld",&f);
            if(i==j) continue;
            e[++cnt]=(edge){j,i,(f*2-(ll)i*i-(ll)j*j)/(-n)}; // 公式变形
        }
    }
    sort(e+1,e+cnt+1,[](edge a,edge b){return a.w<b.w;});
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=cnt;i++){
        int fu=find(e[i].u),fv=find(e[i].v);
        if(fu!=fv) fa[fu]=fv,printf("%d %d %d\n",e[i].u,e[i].v,e[i].w);
    }
    return 0;
}
```

---
处理用时：92.49秒