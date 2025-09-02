# 题目信息

# Chemical table

## 题目描述

Innopolis University scientists continue to investigate the periodic table. There are $ n·m $ known elements and they form a periodic table: a rectangle with $ n $ rows and $ m $ columns. Each element can be described by its coordinates $ (r,c) $ ( $ 1<=r<=n $ , $ 1<=c<=m $ ) in the table.

Recently scientists discovered that for every four different elements in this table that form a rectangle with sides parallel to the sides of the table, if they have samples of three of the four elements, they can produce a sample of the fourth element using nuclear fusion. So if we have elements in positions $ (r_{1},c_{1}) $ , $ (r_{1},c_{2}) $ , $ (r_{2},c_{1}) $ , where $ r_{1}≠r_{2} $ and $ c_{1}≠c_{2} $ , then we can produce element $ (r_{2},c_{2}) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/a1ec2b34980f17dea8ef9d5c32f5d591ae712bba.png)Samples used in fusion are not wasted and can be used again in future fusions. Newly crafted elements also can be used in future fusions.

Innopolis University scientists already have samples of $ q $ elements. They want to obtain samples of all $ n·m $ elements. To achieve that, they will purchase some samples from other laboratories and then produce all remaining elements using an arbitrary number of nuclear fusions in some order. Help them to find the minimal number of elements they need to purchase.

## 说明/提示

For each example you have a picture which illustrates it.

The first picture for each example describes the initial set of element samples available. Black crosses represent elements available in the lab initially.

The second picture describes how remaining samples can be obtained. Red dashed circles denote elements that should be purchased from other labs (the optimal solution should minimize the number of red circles). Blue dashed circles are elements that can be produced with nuclear fusion. They are numbered in order in which they can be produced.

Test 1

We can use nuclear fusion and get the element from three other samples, so we don't need to purchase anything.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/d0188b7b484eed4ec50dd63bc64a04ce06b65611.png)Test 2

We cannot use any nuclear fusion at all as there is only one row, so we have to purchase all missing elements.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/ba8b5c94cc17a4604dd0e58fb6a66f6e2487526e.png)Test 3

There are several possible solutions. One of them is illustrated below.

Note that after purchasing one element marked as red it's still not possible to immidiately produce the middle element in the bottom row (marked as 4). So we produce the element in the left-top corner first (marked as 1), and then use it in future fusions.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1012B/5273513fe4bf0485a76591391c8b08a7edf8e9af.png)

## 样例 #1

### 输入

```
2 2 3
1 2
2 2
2 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 5 3
1 3
1 1
1 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 3 6
1 2
1 3
2 2
2 3
3 1
3 3
```

### 输出

```
1
```

# AI分析结果



**唯一算法分类**  
图论-连通性（二分图）

---

### **综合分析与结论**  
该题核心在于将元素坐标转化为二分图边，通过连通性分析确定最小购买数。关键思路是将行、列视为独立节点，每个元素为连接行与列的边。核聚变规则隐含连通性：同一连通块内任意行、列组合均可生成。最终所需购买数等于连通块数减一。

**核心流程**：  
1. **建模**：行号（1~n）为左部点，列号（n+1~n+m）为右部点。  
2. **连边**：初始元素连接对应行、列节点。  
3. **统计连通块**：DFS或并查集计算总连通块数。  
4. **答案计算**：连通块数 - 1。

**可视化设计**：  
- **像素动画**：行、列节点显示为不同色块，元素边以连线表示。初始元素闪烁后连线显示，合并连通块时播放合成音效。  
- **高亮步骤**：每次合并时，被合并的节点闪烁，连通块颜色渐变统一。  
- **复古风格**：8-bit音效（合成成功时“叮”，合并时“嘟”），背景循环芯片音乐。

---

### **题解清单 (≥4星)**  
1. **小粉兔 (5星)**  
   - **亮点**：DFS遍历清晰，代码极简，官方思路复现。  
   - **核心代码**：  
     ```cpp  
     void D(int u) {  
         for(int i=h[u];i;i=nxt[i]) if(!v[to[i]])  
             v[to[i]]=1, D(to[i]);  
     }  
     ```  
2. **zhaotiensn (5星)**  
   - **亮点**：并查集实现高效，路径压缩优化。  
   - **核心代码**：  
     ```cpp  
     fa[find(y)] = find(x); // 合并行与列  
     ```  
3. **芦苇林 (4星)**  
   - **亮点**：详细证明连通块生成逻辑，配图辅助理解。  

---

### **最优思路提炼**  
**关键技巧**：  
- **二分图建模**：将二维坐标转化为行、列节点的边，利用连通性覆盖所有组合。  
- **并查集优化**：路径压缩快速维护连通块，时间复杂度接近O(1)。  

**思维突破**：  
- 将矩形生成条件转化为图的连通性，通过维护全局连通状态替代局部推导。

---

### **类似题目推荐**  
1. **P5089 [eJOI2018]元素周期表**（同一题，双倍经验）  
2. **P1197 [JSOI2008] 星球大战**（动态维护连通块数）  
3. **P1525 [NOIP2010 提高组] 关押罪犯**（二分图性质应用）

---

### **代码实现示例**  
```cpp
#include <iostream>
using namespace std;
const int MAXN = 4e5+5;
int fa[MAXN];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    int n, m, q; 
    cin >> n >> m >> q;
    for(int i=1; i<=n+m; i++) fa[i] = i;
    
    while(q--) {
        int x,y; cin >> x >> y;
        int fx = find(x), fy = find(n+y);
        if(fx != fy) fa[fy] = fx;
    }
    
    int cnt = 0;
    for(int i=1; i<=n+m; i++) 
        if(fa[i] == i) cnt++;
    cout << cnt - 1;
    return 0;
}
```

---

### **可视化算法演示**  
**动画设计**：  
1. **初始化**：左侧红色块（行节点），右侧蓝色块（列节点）。  
2. **元素添加**：点击元素(2,3)时，2号红块与3号蓝块间画黄色连线。  
3. **连通合并**：当两节点属不同连通块时，播放"嘟"声，合并后统一为绿色。  
4. **最终统计**：所有连通块以不同颜色区分，底部显示答案公式"连通块-1"。

**交互功能**：  
- **速度调节**：滑动条控制合并动画速度（0.5x~3x）。  
- **单步模式**：空格键逐步执行合并操作。  
- **音效开关**：可关闭8-bit音效。

**像素风格**：  
- 使用16色调色板，节点为16x16像素方块，边用虚线像素动画连接。  
- 背景音乐：芯片版《致爱丽丝》循环播放。

---
处理用时：63.29秒