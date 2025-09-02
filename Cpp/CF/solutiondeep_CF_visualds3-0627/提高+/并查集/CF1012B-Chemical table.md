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



## 【唯一算法分类】
并查集

## 【综合分析与结论】
题目要求通过核聚变规则补全矩阵，关键在于将行列建模为二分图的连通性问题。每个元素(r,c)视为连接行r和列c的边，当行列连通时可通过规则生成所有相关元素。最终答案转化为计算初始连通块数减一。

**核心难点**在于如何将二维网格问题转化为图论模型，并利用并查集高效维护连通性。**解决方案**是通过将行列视为节点，元素作为边，核聚变规则等价于连通分量的合并。最终连通块数减一即为需要补充的元素数目。

**可视化设计**：可展示行列为左右两部分节点，初始元素作为边连接。每次合并时高亮对应行列节点，动态显示连通块数量变化。复古像素风格可设计为行节点与列节点以不同颜色表示，合并时播放“连接”音效，最终连通块数减一以闪烁提示。

## 【题解清单 (≥4星)】
1. **小粉兔（5星）**  
   - 思路清晰，通过二分图连通性模型简洁解决问题。DFS遍历连通块，代码简洁高效。
2. **zhaotiensn（5星）**  
   - 使用并查集实现，逻辑严密，代码可读性强。详细解释模型转换思路。
3. **derta（4星）**  
   - 图文结合说明棋盘格转化边的过程，直观展示核聚变规则的等价性。

## 【最优思路提炼】
将行和列视为二分图节点，元素(r,c)作为边连接行r与列c。通过并查集维护连通性，最终连通块数减一即为答案。**关键证明**：同一连通块内所有行与列组合均能被生成。

## 【同类型题推荐】
1. P1197 [JSOI2008] 星球大战（并查集动态删边）
2. P2024 [NOI2001] 食物链（带权并查集）
3. P3367 【模板】并查集（基础应用）

## 【个人心得摘录】
- **zhaotiensn**提到将列+n处理避免冲突，简化并查集实现。
- **芦苇林**通过图示说明边生成过程，辅助理解连通性推导。

## 【核心代码实现】
```cpp
#include <iostream>
using namespace std;

const int MAXN = 400005;
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

## 【可视化算法演示】
**动画设计**：
1. **初始化**：左侧显示n个行节点（蓝色），右侧m个列节点（绿色）
2. **添加元素**：当处理输入元素(r,c)时，绘制红边连接行r和列c，播放"click"音效
3. **合并连通块**：高亮当前合并的行列节点，展示并查集的路径压缩过程
4. **统计结果**：最终以不同颜色区分连通块，显示"连通块数-1"的闪烁文字

**复古风格**：
- 使用8-bit音效：连接成功时播放NES风格音效，合并时发出"哔"声
- 像素化节点：行节点显示为方形，列节点圆形，边为黄色像素线
- 自动演示模式：按空格键逐步执行合并操作，Esc键显示最终结果

**交互功能**：
- 速度调节：方向键控制动画速度
- 单步执行：回车键逐步执行每个元素的处理
- 连通块高亮：鼠标悬停显示所属连通块的所有行列

---
处理用时：64.01秒