# 题目信息

# Rooks Defenders

## 题目描述

You have a square chessboard of size $ n \times n $ . Rows are numbered from top to bottom with numbers from $ 1 $ to $ n $ , and columns — from left to right with numbers from $ 1 $ to $ n $ . So, each cell is denoted with pair of integers $ (x, y) $ ( $ 1 \le x, y \le n $ ), where $ x $ is a row number and $ y $ is a column number.

You have to perform $ q $ queries of three types:

- Put a new rook in cell $ (x, y) $ .
- Remove a rook from cell $ (x, y) $ . It's guaranteed that the rook was put in this cell before.
- Check if each cell of subrectangle $ (x_1, y_1) - (x_2, y_2) $ of the board is attacked by at least one rook.

Subrectangle is a set of cells $ (x, y) $ such that for each cell two conditions are satisfied: $ x_1 \le x \le x_2 $ and $ y_1 \le y \le y_2 $ .

Recall that cell $ (a, b) $ is attacked by a rook placed in cell $ (c, d) $ if either $ a = c $ or $ b = d $ . In particular, the cell containing a rook is attacked by this rook.

## 说明/提示

Consider example. After the first two queries the board will look like the following picture (the letter $ R $ denotes cells in which rooks are located, the subrectangle of the query of the third type is highlighted in green):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/ed156665629e711ee2ed4626477b94d3794c1b66.png)Chessboard after performing the third and the fourth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/287c91194903b3f438014966a1c3ab50aa3053b1.png)Chessboard after performing the fifth and the sixth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/2450d8ada954d98a57be494097290cacc9d47393.png)Chessboard after performing the seventh and the eighth queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/860ee139e8d85a9e953e6218af254f9a2b04a395.png)Chessboard after performing the last two queries:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1679C/fa48f4457088559fa8b50c796cacdd0ae0609075.png)

## 样例 #1

### 输入

```
8 10
1 2 4
3 6 2 7 2
1 3 2
3 6 2 7 2
1 4 3
3 2 6 4 8
2 4 3
3 2 6 4 8
1 4 8
3 2 6 4 8```

### 输出

```
No
Yes
Yes
No
Yes```

# AI分析结果



## 算法分类
树状数组/线段树

---

## 题解思路与算法要点

### 核心思路
要判断子矩形是否全被攻击到，需满足以下两个条件之一：
1. **所有行被覆盖**：子矩形的每一行至少有一个车（行攻击覆盖）
2. **所有列被覆盖**：子矩形的每一列至少有一个车（列攻击覆盖）

### 数据结构选择
- **树状数组**：维护行/列是否被覆盖。每个位置存储 `1`（该行/列有车）或 `0`（无车）。
- **辅助数组**：记录每行/列的实际车数量，用于判断何时更新树状数组。

### 关键步骤
1. **添加车**：
   - 行 `x` 的车数量 `+1`，若从 `0→1`，树状数组对应行 `+1`
   - 列 `y` 同理处理
2. **移除车**：
   - 行 `x` 的车数量 `-1`，若变为 `0`，树状数组对应行 `-1`
   - 列 `y` 同理处理
3. **查询**：
   - 检查行区间 `[x1, x2]` 的总和是否等于区间长度（即全为 `1`）
   - 检查列区间 `[y1, y2]` 的总和是否等于区间长度
   - 若任一条件满足，输出 `Yes`，否则 `No`

---

## 题解评分（≥4星）

### 1. [panyanppyy] 4.5星
- **亮点**：代码简洁高效，使用树状数组直接维护覆盖状态，逻辑清晰。
- **核心代码**：
  ```cpp
  struct qjc{ ... }_x,_y; // 树状数组结构体
  if(_x.Q(x,X)==X-x+1 || _y.Q(y,Y)==Y-y+1) // 区间和判断
  ```

### 2. [Anguei] 4星
- **亮点**：详细推导覆盖条件，代码可读性强，附带示意图解释。
- **关键片段**：
  ```cpp
  Fenwick bitRow(n), bitCol(n); // 封装树状数组
  bool ok = bitRow.rangeSum(x1, x2) == rowLen || bitCol.rangeSum(y1, y2) == colLen;
  ```

### 3. [Rnfmabj] 4星
- **亮点**：强调树状数组的适用性，代码实现简明，注释清晰。
- **核心逻辑**：
  ```cpp
  if (cnt_1[x] == 1) add_1(x, 1); // 仅首次添加时更新
  ```

---

## 最优思路提炼
- **核心技巧**：通过树状数组快速判断区间全覆盖，用辅助数组跟踪实际车数量。
- **优化点**：仅在车数量 `0↔1` 变化时更新树状数组，减少不必要的操作。
- **思维角度**：将二维攻击范围拆解为行和列的一维覆盖问题，简化数据结构设计。

---

## 同类型题推荐
1. **P3368 树状数组 2**（区间修改+单点查询）
2. **P3374 树状数组 1**（单点修改+区间查询）
3. **CF1311F Moving Points**（二维静态区间统计）

---

## 可视化设计

### 动画方案
1. **棋盘绘制**：Canvas 绘制 `n×n` 网格，不同颜色标记车和攻击范围。
2. **操作高亮**：
   - **添加车**：红色闪烁格子，对应行/列变黄（覆盖状态）。
   - **移除车**：格子变灰，若行/列失去覆盖则恢复原色。
   - **查询矩形**：绿色边框，若条件满足则内部填充半透明绿/红。
3. **树状数组更新**：侧边显示行/列的树状数组结构，修改时高亮对应节点。

### 复古像素风格
- **8位调色板**：棋盘用深灰网格，车为亮红色，攻击范围浅黄，查询框绿色。
- **音效设计**：
  - `放置车`：短促“哔”声
  - `查询成功`：上升音阶
  - `查询失败`：下降音阶
- **自动演示**：按固定顺序执行添加、移除、查询操作，展示覆盖状态变化。

---

## 代码实现（树状数组版）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,q,cnt_row[N],cnt_col[N];
struct Fenwick {
    int t[N];
    void update(int x, int k) {
        for(; x<=n; x+=x&-x) t[x]+=k;
    }
    int query(int x) {
        int res=0;
        for(; x; x-=x&-x) res+=t[x];
        return res;
    }
    int range(int l, int r) {
        return query(r) - query(l-1);
    }
} row, col;

int main() {
    scanf("%d%d",&n,&q);
    while(q--) {
        int op,x,y,X,Y;
        scanf("%d%d%d",&op,&x,&y);
        if(op == 1) {
            if(++cnt_row[x] == 1) row.update(x,1);
            if(++cnt_col[y] == 1) col.update(y,1);
        } else if(op == 2) {
            if(--cnt_row[x] == 0) row.update(x,-1);
            if(--cnt_col[y] == 0) col.update(y,-1);
        } else {
            scanf("%d%d",&X,&Y);
            int row_cover = row.range(x,X) == X-x+1;
            int col_cover = col.range(y,Y) == Y-y+1;
            puts(row_cover || col_cover ? "Yes" : "No");
        }
    }
    return 0;
}
```

---
处理用时：81.23秒