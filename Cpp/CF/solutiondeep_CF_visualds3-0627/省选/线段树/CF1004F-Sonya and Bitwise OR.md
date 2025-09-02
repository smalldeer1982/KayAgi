# 题目信息

# Sonya and Bitwise OR

## 题目描述

Sonya has an array $ a_1, a_2, \ldots, a_n $ consisting of $ n $ integers and also one non-negative integer $ x $ . She has to perform $ m $ queries of two types:

- $ 1 $ $ i $ $ y $ : replace $ i $ -th element by value $ y $ , i.e. to perform an operation $ a_{i} $ := $ y $ ;
- $ 2 $ $ l $ $ r $ : find the number of pairs ( $ L $ , $ R $ ) that $ l\leq L\leq R\leq r $ and bitwise OR of all integers in the range $ [L, R] $ is at least $ x $ (note that $ x $ is a constant for all queries).

Can you help Sonya perform all her queries?

Bitwise OR is a binary operation on a pair of non-negative integers. To calculate the bitwise OR of two numbers, you need to write both numbers in binary notation. The result is a number, in binary, which contains a one in each digit if there is a one in the binary notation of at least one of the two numbers. For example, $ 10 $ OR $ 19 $ = $ 1010_2 $ OR $ 10011_2 $ = $ 11011_2 $ = $ 27 $ .

## 说明/提示

In the first example, there are an array \[ $ 0 $ , $ 3 $ , $ 6 $ , $ 1 $ \] and queries:

1. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 3 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ );
2. on the segment \[ $ 3\ldots4 $ \], you can choose pair ( $ 3 $ , $ 4 $ );
3. the first number is being replacing by $ 7 $ , after this operation, the array will consist of \[ $ 7 $ , $ 3 $ , $ 6 $ , $ 1 $ \];
4. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 3 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ );
5. on the segment \[ $ 1\ldots3 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), and ( $ 2 $ , $ 3 $ );
6. on the segment \[ $ 1\ldots1 $ \], you can choose pair ( $ 1 $ , $ 1 $ );
7. the third number is being replacing by $ 0 $ , after this operation, the array will consist of \[ $ 7 $ , $ 3 $ , $ 0 $ , $ 1 $ \];
8. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 1 $ ), ( $ 1 $ , $ 2 $ ), ( $ 1 $ , $ 3 $ ), and ( $ 1 $ , $ 4 $ ).

In the second example, there are an array \[ $ 6 $ , $ 0 $ , $ 3 $ , $ 15 $ , $ 2 $ \] are queries:

1. on the segment \[ $ 1\ldots5 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 4 $ ), ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 4 $ ), ( $ 3 $ , $ 5 $ ), ( $ 4 $ , $ 4 $ ), and ( $ 4 $ , $ 5 $ );
2. the fourth number is being replacing by $ 4 $ , after this operation, the array will consist of \[ $ 6 $ , $ 0 $ , $ 3 $ , $ 4 $ , $ 2 $ \];
3. on the segment \[ $ 1\ldots5 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 1 $ , $ 5 $ ), ( $ 2 $ , $ 4 $ ), ( $ 2 $ , $ 5 $ ), ( $ 3 $ , $ 4 $ ), and ( $ 3 $ , $ 5 $ );
4. on the segment \[ $ 3\ldots5 $ \], you can choose pairs ( $ 3 $ , $ 4 $ ) and ( $ 3 $ , $ 5 $ );
5. on the segment \[ $ 1\ldots4 $ \], you can choose pairs ( $ 1 $ , $ 3 $ ), ( $ 1 $ , $ 4 $ ), ( $ 2 $ , $ 4 $ ), and ( $ 3 $ , $ 4 $ ).

## 样例 #1

### 输入

```
4 8 7
0 3 6 1
2 1 4
2 3 4
1 1 7
2 1 4
2 1 3
2 1 1
1 3 0
2 1 4
```

### 输出

```
5
1
7
4
1
4
```

## 样例 #2

### 输入

```
5 5 7
6 0 3 15 2
2 1 5
1 4 4
2 1 5
2 3 5
2 1 4
```

### 输出

```
9
7
2
4
```

# AI分析结果



---

### 算法分类  
**线段树、位运算、分治**

---

### 题解思路与解决难点  
**核心思路**  
1. **线段树维护 OR 段**：利用 OR 运算的单调性（添加元素只会使值不变或增大），每个线段树节点维护前缀 OR 段和后缀 OR 段（最多 $\log a$ 段）。
2. **分治合并**：合并两个子区间时，用双指针统计跨区间的贡献（两子区间的前缀和后缀段配对），时间复杂度 $O(\log a)$。
3. **高效更新与查询**：单点修改时更新叶子节点并逐层合并；查询时递归合并覆盖区间的贡献，总复杂度 $O(m \log n \log a)$。

**关键难点**  
- **正确维护 OR 段**：合并前缀/后缀段时需确保只保留不同 OR 值的段。
- **部分覆盖查询处理**：当查询区间仅覆盖部分子节点时，需动态调整双指针范围，仅统计有效段的贡献。

---

### 题解评分  
1. **duyi（5星）**：代码清晰，注释完整，双指针逻辑简洁，维护前缀/后缀段的方式高效。  
2. **reyik（4星）**：实现简洁，直接通过结构体封装合并逻辑，适合快速理解核心思路。  
3. **Piwry（4星）**：代码模块化，通过结构体 `interval` 封装合并逻辑，可读性较强。

---

### 最优思路与技巧  
1. **OR 段压缩**：利用 OR 值的单调性，将前缀/后缀压缩为 $O(\log a)$ 个段。  
2. **双指针合并**：在线段树合并时，用双指针快速统计跨区间的合法子区间数目。  
3. **动态范围调整**：查询时处理部分覆盖区间，仅计算有效范围内的段对。

---

### 类似题目与算法  
- **相似算法**：区间统计满足特定条件的子区间数（如 GCD、AND、XOR 等位运算）。  
- **同类题目**：  
  - [CF 242E XOR on Segment](https://codeforces.com/problemset/problem/242/E)  
  - [LeetCode 1521. Find a Value in a Sorted Array](https://leetcode.com/problems/find-a-value-in-a-sorted-array/)  
  - [洛谷 P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)

---

### 可视化与算法演示  
**核心动画设计**：  
1. **线段树结构**：以网格展示线段树节点，高亮当前合并的区间。  
2. **OR 段变化**：用不同颜色标记前缀/后缀段，动态显示合并时的段压缩过程。  
3. **双指针移动**：在合并界面展示左右子节点的段配对，双指针移动时播放音效。  

**复古像素风格**：  
- **颜色方案**：8-bit 色调（如红、蓝、绿）区分 OR 段和操作类型。  
- **音效触发**：  
  - 段合并成功时播放上扬音效；  
  - 查询结束时播放胜利音效；  
  - 错误操作时播放短促低音。  

**交互控制**：  
- **步进执行**：允许逐帧查看双指针移动和段合并过程。  
- **自动演示**：模拟 AI 自动执行查询/修改，展示算法流程。

---

### 核心代码实现  
**线段树节点合并逻辑（以 duyi 代码为例）**  
```cpp
void push_up(int p) {
    int ls = p<<1, rs = p<<1|1;
    ans[p] = ans[ls] + ans[rs];
    // 双指针统计跨区间贡献
    for (int i=0, j=SZ(suf[ls])-1; i<SZ(pre[rs]); ++i) {
        int nxt = (i+1 < SZ(pre[rs])) ? pre[rs][i+1].fi : tr[p]+1;
        while (j >=0 && (suf[ls][j].se | pre[rs][i].se) >= X) j--;
        if (j+1 < SZ(suf[ls])) 
            ans[p] += (suf[ls][j+1].fi - tl[p]+1) * (nxt - pre[rs][i].fi);
    }
    // 合并前缀和后缀段
    pre[p] = pre[ls];
    for (auto seg : pre[rs]) {
        int val = pre[p].back().se | seg.se;
        if (val != pre[p].back().se) pre[p].pb(mk(seg.fi, val));
    }
    suf[p] = suf[rs];
    for (auto seg : suf[ls]) {
        int val = suf[p].back().se | seg.se;
        if (val != suf[p].back().se) suf[p].pb(mk(seg.fi, val));
    }
}
```

---

### 个人心得  
- **调试关键**：确保合并前缀/后缀段时正确更新 OR 值，避免重复或遗漏段。  
- **思维突破**：利用 OR 的单调性压缩段数是降低复杂度的核心。

---
处理用时：90.78秒