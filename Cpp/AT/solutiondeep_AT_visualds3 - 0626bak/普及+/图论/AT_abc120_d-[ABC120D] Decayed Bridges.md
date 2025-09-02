# 题目信息

# [ABC120D] Decayed Bridges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc120/tasks/abc120_d

$ N $ 個の島と $ M $ 本の橋があります。

$ i $ 番目の橋は $ A_i $ 番目の島と $ B_i $ 番目の島を繋いでおり、双方向に行き来可能です。

はじめ、どの $ 2 $ つの島についてもいくつかの橋を渡って互いに行き来できます。

調査の結果、老朽化のためこれら $ M $ 本の橋は $ 1 $ 番目の橋から順に全て崩落することがわかりました。

「いくつかの橋を渡って互いに行き来できなくなった $ 2 $ つの島の組 $ (a,\ b) $ ($ a\ <\ b $) の数」を**不便さ**と呼ぶことにします。

各 $ i $ $ (1\ \leq\ i\ \leq\ M) $ について、$ i $ 番目の橋が崩落した直後の不便さを求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- $ (A_i,\ B_i) $ の組は全て異なる。
- 初期状態における不便さは $ 0 $ である。

### Sample Explanation 1

例えば、$ 1 $ から $ 3 $ 番目の橋が崩落したとき、$ (1,\ 2),\ (1,\ 3),\ (2,\ 4),\ (3,\ 4) $ の島の組について行き来できなくなるので不便さは $ 4 $ です。

## 样例 #1

### 输入

```
4 5

1 2

3 4

1 3

2 3

1 4```

### 输出

```
0

0

4

5

6```

## 样例 #2

### 输入

```
6 5

2 3

1 2

5 6

3 4

4 5```

### 输出

```
8

9

12

14

15```

## 样例 #3

### 输入

```
2 1

1 2```

### 输出

```
1```

# AI分析结果



# 算法分类  
**并查集**

---

# 题解思路与难点分析  
## 核心思路  
所有题解均采用 **逆向处理 + 并查集维护连通块** 的算法：  
1. **逆向建边**：将删边操作逆转为加边操作，便于并查集维护连通性  
2. **连通块贡献计算**：每次合并两个连通块时，减少的不便值为 `size[x] * size[y]`  
3. **倒序递推**：初始不便值设为所有点独立时的对数 `C(n,2)`，依次累减连通块贡献  

## 解决难点  
1. **逆向思维转换**：正序删边难以维护，逆序加边可通过并查集高效处理  
2. **贡献动态计算**：用并查集的 `size` 数组实时维护连通块大小，确保每次合并时能快速计算对数变化  
3. **数据溢出处理**：所有题解强调使用 `long long` 存储结果，避免 `n=1e5` 时的溢出问题  

---

# 题解评分（≥4星）  
1. **ElmPoplar（★★★★★）**  
   - 亮点：代码简洁，初始化逻辑清晰，注释明确  
   - 核心代码段：  
     ```cpp  
     ans[m] = (long long)n * (n - 1) / 2;  
     for (int i = m; i > 1; i--) {  
         if (x == y) ans[i-1] = ans[i];  
         else ans[i-1] = ans[i] - (long long)Size[x] * Size[y];  
     }  
     ```  

2. **HMZHMZHMZ（★★★★）**  
   - 亮点：使用结构体存储边，代码模块化程度高  
   - 核心优化：通过 `add` 函数封装合并与贡献计算  

3. **徐晨轩（★★★★）**  
   - 亮点：变量命名直观，`merge` 函数直接操作并查集父子关系  
   - 关键实现：  
     ```cpp  
     void merge(int x,int y) {  
         siz[find(y)] += siz[find(x)];  
         f[find(x)] = find(y);  
     }  
     ```  

---

# 最优技巧提炼  
1. **逆向操作思维**：将动态删边问题转化为静态加边问题  
2. **贡献预计算**：初始不便值为 `C(n,2)`，通过合并连通块逐步减少  
3. **并查集 size 维护**：实时记录连通块大小，快速计算对数变化  

---

# 同类题目推荐  
1. **P1197 [JSOI2008]星球大战**（逆向并查集应用）  
2. **P6121 [USACO16OPEN]248 G**（动态合并与贡献计算）  
3. **P4185 [USACO18JAN]MooTube G**（离线查询与并查集结合）  

---

# 个人心得摘录  
> - *“正着不好想，反着想思路就打开了”* —— ElmPoplar  
> - *“一场 OI 一场空，不开 long long 见祖宗”* —— ElmPoplar（强调数据溢出风险）  
> - *“合并顺序影响父子关系，必须确保 size 正确累加”* —— 紊莫  

---

# 可视化算法演示  
## 动画设计  
1. **Canvas 动态演示**：  
   - **初始状态**：所有节点独立显示为不同颜色方块  
   - **倒序加边**：每次高亮当前处理的边（如红色边框），合并连通块时播放“连接音效”  
   - **连通块合并**：合并后统一颜色，显示 `size[x] * size[y]` 的数值浮动  
   - **答案更新**：右侧面板实时显示当前不便值 `ans[i]`  

2. **8位像素风格**：  
   - **颜色方案**：使用 16 色调色板，每个连通块分配唯一颜色  
   - **音效设计**：  
     - 合并成功：8-bit 上升音效  
     - 无需合并：短促“滴”声  
   - **自动演示**：按固定时间间隔执行步骤，可暂停/加速  

## 关键代码片段（JS伪代码）  
```javascript  
class UnionFindViz {  
  constructor(n) {  
    this.parent = [...Array(n+1).keys()];  
    this.size = Array(n+1).fill(1);  
    this.ans = [n*(n-1)/2];  
  }  

  merge(x, y) {  
    let fx = this.find(x), fy = this.find(y);  
    if (fx !== fy) {  
      this.ans.push(this.ans.last - this.size[fx] * this.size[fy]);  
      this.size[fy] += this.size[fx];  
      this.parent[fx] = fy;  
      playSound('merge_success'); // 触发合并音效  
    } else {  
      playSound('no_action');  
    }  
  }  
}  
```  

---

# 完整题解代码（ElmPoplar版）  
```cpp  
#include <bits/stdc++.h>  
using namespace std;  
const int N = 100005;  
int n, m, u[N], v[N], fa[N], Size[N];  
long long ans[N];  

int find(int x) {  
    return fa[x] == x ? x : fa[x] = find(fa[x]);  
}  

int main() {  
    scanf("%d%d", &n, &m);  
    for (int i = 1; i <= m; i++)  
        scanf("%d%d", &u[i], &v[i]);  

    for (int i = 1; i <= n; i++) fa[i] = i, Size[i] = 1;  

    ans[m] = (long long)n * (n - 1) / 2;  
    for (int i = m; i >= 1; i--) {  
        int x = find(u[i]), y = find(v[i]);  
        if (x != y) {  
            ans[i-1] = ans[i] - (long long)Size[x] * Size[y];  
            fa[y] = x;  
            Size[x] += Size[y];  
        } else ans[i-1] = ans[i];  
    }  

    for (int i = 1; i <= m; i++)  
        printf("%lld\n", ans[i]);  
    return 0;  
}  
```

---
处理用时：69.19秒