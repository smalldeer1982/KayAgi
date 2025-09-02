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



## 唯一算法分类
**图论-连通性（并查集/DFS）**

---

## 综合分析与结论
### 核心思路与难点
- **建模转换**：将每个元素 $(r,c)$ 视为连接行节点 $r$ 与列节点 $c$ 的边，构造一个包含 $n+m$ 个节点的二分图。
- **连通性规则**：若三个元素构成矩形三个角，则第四个角元素可生成。此过程不影响图的连通性，但确保连通分量内所有可能的边最终存在。
- **关键结论**：答案等于初始图的连通分量数减一。通过并查集或DFS统计连通分量数即可。

### 算法流程与可视化设计
- **变量初始化**：将行和列节点统一编号，初始化并查集或访问标记数组。
- **合并操作**：遍历每个元素 $(r,c)$，合并对应的行和列节点。
- **统计连通分量**：统计所有节点的根节点数量（并查集）或DFS遍历次数。
- **可视化要点**：
  - **动态合并**：用动画展示行和列节点的合并过程，高亮当前操作的边。
  - **连通块标记**：不同连通分量用不同颜色区分，合并时显示颜色统一。
  - **像素风格**：用8位像素网格表示节点，合并时播放复古音效，连通块数减少时触发得分动画。

---

## 题解评分（≥4星）
1. **小粉兔（5星）**  
   - **亮点**：官方证明引用，DFS实现简洁，代码可读性极佳。  
   - **核心代码**：DFS遍历所有节点，统计连通分量数。

2. **zhaotiensn（5星）**  
   - **亮点**：并查集实现高效，代码注释清晰，时间复杂度更优。  
   - **核心代码**：路径压缩并查集，合并行和列节点。

3. **derta（4星）**  
   - **亮点**：图文结合解释生成规则，并查集实现完整。  
   - **核心代码**：带按秩合并的并查集，优化合并效率。

---

## 最优思路与代码实现
### 关键技巧
- **二分图建模**：将二维元素转换为边，行和列作为节点，利用连通性简化问题。
- **并查集路径压缩**：优化合并操作，时间复杂度接近 $O(\alpha(n))$。
- **统一编号**：行用 $1 \sim n$，列用 $n+1 \sim n+m$，避免冲突。

### 代码片段（并查集实现）
```cpp
#include <iostream>
using namespace std;
const int MAXN = 400001;
int fa[MAXN];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n + m; ++i) fa[i] = i;
    while (q--) {
        int r, c;
        cin >> r >> c;
        int fr = find(r), fc = find(n + c);
        if (fr != fc) fa[fr] = fc;
    }
    int cnt = 0;
    for (int i = 1; i <= n + m; ++i)
        if (fa[i] == i) cnt++;
    cout << cnt - 1 << endl;
    return 0;
}
```

---

## 同类题目与推荐
1. **P5089 [eJOI2018] 元素周期表**  
   - **相似点**：同一题目，双倍经验。
   
2. **P1330 封锁阳光大学**  
   - **相似点**：二分图建模，判断连通性。

3. **P1525 关押罪犯**  
   - **相似点**：并查集处理矛盾关系，连通性优化。

---

## 可视化与复古动画设计
### 实现要点
- **Canvas绘制**：  
  - 行节点显示在左侧网格，列节点在右侧，边为连接线。
  - 每次合并时，高亮对应行和列节点，播放“哔”音效。
  
- **自动演示模式**：  
  - 初始随机生成元素，自动执行合并，展示连通块数变化。
  - 结束条件：连通块数为1，播放胜利音效。

- **8位风格**：  
  - 使用复古调色板（如#FF0000红、#00FF00绿）。
  - 节点用像素方块表示，合并时方块闪烁。

### 代码片段（伪代码）
```javascript
// Canvas初始化与节点绘制
function drawNode(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x * 20, y * 20, 18, 18);
}

// 合并动画
function animateMerge(r, c) {
    playSound('merge'); // 播放合并音效
    highlight(r, n + c); // 高亮行和列节点
    setTimeout(() => mergeNodes(r, c), 500);
}
```

---

## 个人心得摘录
- **芦苇林**：通过观察生成规则的图形结构，发现连通分量的重要性，顿悟建模方法。
- **KevinYu**：调试时发现数组开小导致RE，强调初始化范围的重要性。

---
处理用时：96.26秒