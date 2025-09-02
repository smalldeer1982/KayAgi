# 题目信息

# [USACO08FEB] Hotel G

## 题目描述

The cows are journeying north to Thunder Bay in Canada to gain cultural enrichment and enjoy a vacation on the sunny shores of Lake Superior. Bessie, ever the competent travel agent, has named the Bullmoose Hotel on famed Cumberland Street as their vacation residence. This immense hotel has N (1 ≤ N ≤ 50,000) rooms all located on the same side of an extremely long hallway (all the better to see the lake, of course).

The cows and other visitors arrive in groups of size Di (1 ≤ Di ≤ N) and approach the front desk to check in. Each group i requests a set of Di contiguous rooms from Canmuu, the moose staffing the counter. He assigns them some set of consecutive room numbers r..r+Di-1 if they are available or, if no contiguous set of rooms is available, politely suggests alternate lodging. Canmuu always chooses the value of r to be the smallest possible.

Visitors also depart the hotel from groups of contiguous rooms. Checkout i has the parameters Xi and Di which specify the vacating of rooms Xi ..Xi +Di-1 (1 ≤ Xi ≤ N-Di+1). Some (or all) of those rooms might be empty before the checkout.

Your job is to assist Canmuu by processing M (1 ≤ M < 50,000) checkin/checkout requests. The hotel is initially unoccupied.

第一行输入 $n,m$，$n$ 代表有 $n$ 个房间 $(1\leq n \leq 50,000)$，编号为 $1 \sim n$，开始都为空房，$m$ 表示以下有 $m$ 行操作 $(1\leq m < 50,000)$，以下每行先输入一个数 $i$ ，表示一种操作：

若 $i$ 为 $1$，表示查询房间，再输入一个数 $x$，表示在 $1,2,...,n$ 房间中找到长度为 $x$ 的连续空房，输出连续 $x$ 个房间中左端的房间号，尽量让这个房间号最小，若找不到长度为 $x$ 的连续空房，输出 $0$。若找得到，在这 $x$ 个空房间中住上人。

若 $i$ 为 $2$，表示退房，再输入两个数 $x,y$ 代表房间号 $x \sim x+y-1$ 退房，即让房间为空。

你需要对每个输入 $1$ 输出对应的答案。

## 样例 #1

### 输入

```
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6
```

### 输出

```
1
4
7
0
5
```

# AI分析结果



# 【算法分类】  
线段树（维护区间连续空房）

---

# 【题解思路与难点对比】  
**核心思路**：  
线段树维护每个区间的最大连续空房数（sum）、左端最长连续空房（lmax）、右端最长连续空房（rmax）及懒标记（lazy）。  
- **入住操作**：将指定区间标记为占用（sum/lmax/rmax 置零）。  
- **退房操作**：将指定区间标记为空闲（sum/lmax/rmax 恢复为区间长度）。  
- **查询操作**：递归查找满足长度的最左连续空房，优先检查左子树、中间跨子树、右子树。

**难点对比**：  
1. **区间合并逻辑**：需处理左子树的右端与右子树的左端合并情况（如 Chemist 题解中的 `renew` 函数）。  
2. **懒标记下传**：Owen 题解通过三目运算符简化标记处理，而 amstar 题解通过 `pushdown` 分情况更新子节点。  
3. **查询优先级**：所有题解均遵循「左→中间→右」的查询顺序以保证最左解。

---

# 【题解评分 (≥4星)】  
1. **Chemist (★★★★☆)**  
   - **亮点**：详细注释 + 变量命名清晰，懒标记逻辑明确，维护 `lmax/rmax` 的合并策略完整。  
   - **代码片段**：  
     ```cpp  
     void renew(int p) {  
         t[p].sum = max(t[p*2].rmax + t[p*2+1].lmax, max(t[p*2].sum, t[p*2+1].sum));  
     }  
     ```  
2. **Owen_codeisking (★★★★☆)**  
   - **亮点**：代码简洁，使用三目运算符优化条件判断，结构体宏定义提高可读性。  
   - **代码片段**：  
     ```cpp  
     lmax(rt) = (lmax(lson) == len(lson)) ? len(lson) + lmax(rson) : lmax(lson);  
     ```  
3. **amstar (★★★★☆)**  
   - **亮点**：变量命名直观，`pushup/pushdown` 函数逻辑清晰，适合新手理解。  

---

# 【最优思路提炼】  
**关键技巧**：  
1. **线段树节点设计**：维护 `sum/lmax/rmax` 以支持连续区间合并。  
2. **懒标记优化**：通过标记快速更新整段区间状态，避免递归到叶子节点。  
3. **查询优先级策略**：优先左子树确保最左解，中间跨子树直接计算起始位置。  

---

# 【类似题目推荐】  
1. [P2572 [SCOI2010] 序列操作](https://www.luogu.com.cn/problem/P2572)  
   - **相似点**：线段树维护连续区间，需处理区间赋值和翻转。  
2. [P3870 [TJOI2009] 开关](https://www.luogu.com.cn/problem/P3870)  
   - **相似点**：区间翻转操作，维护开关状态。  
3. [P1471 方差](https://www.luogu.com.cn/problem/P1471)  
   - **相似点**：线段树维护复杂区间统计量（均值、方差）。  

---

# 【可视化设计】  
**动画方案**：  
1. **线段树节点展示**：每个节点显示 `sum/lmax/rmax`，颜色区分占用（红色）和空闲（绿色）。  
2. **查询过程高亮**：  
   - **左子树**：蓝色边框高亮。  
   - **中间跨子树**：黄色区域标记合并区间。  
   - **右子树**：紫色边框高亮。  
3. **复古像素风格**：  
   - **Canvas 绘制**：线段树以网格形式呈现，节点用 8x8 像素块表示。  
   - **音效触发**：查询成功时播放「滴」声，标记下传时播放「咔嚓」声。  

**交互功能**：  
- **步进控制**：按钮控制动画速度（慢/中/快）。  
- **自动演示**：AI 模式自动执行入住/退房操作，动态展示线段树更新。  

---

# 【代码实现（核心逻辑）】  
**线段树查询函数**：  
```cpp  
int query(int p, int len) {  
    if (t[p].sum < len) return 0;  
    if (t[p].l == t[p].r) return t[p].l;  
    pushdown(p);  
    if (t[p*2].sum >= len) return query(p*2, len);  
    if (t[p*2].rmax + t[p*2+1].lmax >= len)  
        return t[p*2].r - t[p*2].rmax + 1;  
    return query(p*2+1, len);  
}  
```  

**懒标记下传**：  
```cpp  
void pushdown(int p) {  
    if (t[p].lazy == 1) {  // 入住标记  
        t[p*2].lmax = t[p*2].rmax = t[p*2].sum = 0;  
        t[p*2+1].lmax = t[p*2+1].rmax = t[p*2+1].sum = 0;  
    } else if (t[p].lazy == 2) {  // 退房标记  
        t[p*2].lmax = t[p*2].rmax = t[p*2].sum = t[p*2].len;  
        t[p*2+1].lmax = t[p*2+1].rmax = t[p*2+1].sum = t[p*2+1].len;  
    }  
    t[p*2].lazy = t[p*2+1].lazy = t[p].lazy;  
    t[p].lazy = 0;  
}  
```  

---

# 【总结】  
线段树通过维护区间连续空房属性，高效解决了动态区间覆盖与最左查询问题。核心在于合并策略与懒标记优化，适合处理大规模区间操作。

---
处理用时：75.96秒