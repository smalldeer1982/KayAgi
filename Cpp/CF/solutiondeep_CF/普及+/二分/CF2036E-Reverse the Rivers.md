# 题目信息

# Reverse the Rivers

## 题目描述

A conspiracy of ancient sages, who decided to redirect rivers for their own convenience, has put the world on the brink. But before implementing their grand plan, they decided to carefully think through their strategy — that's what sages do.

There are $ n $ countries, each with exactly $ k $ regions. For the $ j $ -th region of the $ i $ -th country, they calculated the value $ a_{i,j} $ , which reflects the amount of water in it.

The sages intend to create channels between the $ j $ -th region of the $ i $ -th country and the $ j $ -th region of the $ (i + 1) $ -th country for all $ 1 \leq i \leq (n - 1) $ and for all $ 1 \leq j \leq k $ .

Since all $ n $ countries are on a large slope, water flows towards the country with the highest number. According to the sages' predictions, after the channel system is created, the new value of the $ j $ -th region of the $ i $ -th country will be $ b_{i,j} = a_{1,j} | a_{2,j} | ... | a_{i,j} $ , where $ | $ denotes the [bitwise "OR"](http://tiny.cc/bitwise_or) operation.

After the redistribution of water, the sages aim to choose the most suitable country for living, so they will send you $ q $ queries for consideration.

Each query will contain $ m $ requirements.

Each requirement contains three parameters: the region number $ r $ , the sign $ o $ (either " $ < $ " or " $ > $ "), and the value $ c $ . If $ o $ = " $ < $ ", then in the $ r $ -th region of the country you choose, the new value must be strictly less than the limit $ c $ , and if $ o $ = " $ > $ ", it must be strictly greater.

In other words, the chosen country $ i $ must satisfy all $ m $ requirements. If in the current requirement $ o $ = " $ < $ ", then it must hold that $ b_{i,r} < c $ , and if $ o $ = " $ > $ ", then $ b_{i,r} > c $ .

In response to each query, you should output a single integer — the number of the suitable country. If there are multiple such countries, output the smallest one. If no such country exists, output $ -1 $ .

## 说明/提示

In the example, the initial values of the regions are as follows:

  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 4 $  $ 6 $  $ 5 $  $ 3 $  $ 2 $  $ 1 $  $ 2 $  $ 7 $ After creating the channels, the new values will look like this:

  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 1 | 4 $  $ 3 | 6 $  $ 5 | 5 $  $ 9 | 3 $  $ 1 | 4 | 2 $  $ 3 | 6 | 1 $  $ 5 | 5 | 2 $  $ 9 | 3 | 7 $  $ \downarrow $  $ 1 $  $ 3 $  $ 5 $  $ 9 $  $ 5 $  $ 7 $  $ 5 $  $ 11 $  $ 7 $  $ 7 $  $ 7 $  $ 15 $ In the first query, it is necessary to output the minimum country number (i.e., row) where, after the redistribution of water in the first region (i.e., column), the new value will be greater than four and less than six, and in the second region it will be less than eight. Only the country with number $ 2 $ meets these requirements.

In the second query, there are no countries that meet the specified requirements.

In the third query, only the country with number $ 3 $ is suitable.

In the fourth query, all three countries meet the conditions, so the answer is the smallest number $ 1 $ .

## 样例 #1

### 输入

```
3 4 4
1 3 5 9
4 6 5 3
2 1 2 7
3
1 > 4
2 < 8
1 < 6
2
1 < 8
2 > 8
1
3 > 5
2
4 > 8
1 < 8```

### 输出

```
2
-1
3
1```

# AI分析结果



### 中文题目重写
#### 题目描述
古代智者密谋通过改变河流的走向来便利自己，但他们在实施宏伟计划前决定仔细推敲策略。  
存在 $n$ 个国家，每个国家有 $k$ 个区域。对于第 $i$ 个国家第 $j$ 个区域，其初始水量为 $a_{i,j}$。  

智者计划在相邻国家的相同区域间建立渠道。由于所有国家位于斜坡上，水流向编号更大的国家。建立渠道后，第 $i$ 个国家第 $j$ 个区域的新水量 $b_{i,j}$ 将是 $a_{1,j} | a_{2,j} | \dots | a_{i,j}$（按位或运算的累积结果）。  

处理 $q$ 次查询，每次查询包含 $m$ 个约束条件。每个条件形如 $(r, o, c)$，要求选中的国家在区域 $r$ 的值必须严格大于（若 $o$ 为 ">"）或严格小于（若 $o$ 为 "<"）$c$。需找出满足所有条件的最小国家编号，若无解输出 -1。

---

### 题解分析与结论

#### 核心思路
1. **单调性观察**：每列的前缀或值单调非减，允许使用二分法快速确定满足条件的区间。
2. **区间交集法**：对每个约束条件，通过二分确定其允许的国家范围，维护全局可行区间的左右边界。
3. **高效查询**：预处理每列的前缀或数组，利用 STL 的二分函数（`lower_bound`/`upper_bound`）快速定位边界。

---

### 精选题解

#### 题解1：fanminghao000（⭐⭐⭐⭐⭐）
**亮点**：  
- 简洁直观，直接利用 STL 二分函数处理边界  
- 预处理时将列作为主维度，优化内存访问  
```cpp
vector<vector<int>> a(k, vector<int>(n));
// 预处理前缀或
for (int i = 0; i < n; i++) 
    for (int j = 0; j < k; j++) 
        if (i >= 1) a[j][i] |= a[j][i-1];

// 处理每个约束条件
int st = 0, en = n-1;
while (ci--) {
    int r; char op; int c;
    if (op == '>') {
        int x = upper_bound(a[r].begin(), a[r].end(), c) - a[r].begin();
        st = max(st, x);
    } else {
        int x = lower_bound(a[r].begin(), a[r].end(), c) - a[r].begin();
        en = min(en, x-1);
    }
}
// 检查区间有效性
if (st <= en) cout << st+1 << endl;
```

---

#### 题解2：The_Elation_Aha（⭐⭐⭐⭐）
**亮点**：  
- 明确行列转换处理，避免二维数组越界  
- 边界条件处理严谨，增加越界检测  
```cpp
vector<ll> aa[N], a[N];
// 预处理时行列转换
for (int j = 0; j < m; ++j) 
    for (int i = 0; i < n; ++i) 
        if (i) a[j][i] |= a[j][i-1];

// 处理约束条件时进行范围裁剪
ll lx = 1, rx = n;
if (op == '<') {
    p = lower_bound(a[r].begin(), a[r].end(), c) - a[r].begin();
    rx = min(rx, p);
} else {
    p = upper_bound(a[r].begin(), a[r].end(), c) - a[r].begin();
    lx = max(lx, p + 1);
}
```

---

#### 题解3：xvl_（⭐⭐⭐⭐）
**亮点**：  
- 代码简洁高效，直接维护左右边界  
- 利用 vector 动态管理内存  
```cpp
vector<int> vec[K];
// 预处理每列前缀或
for (int j = 1; j <= k; j++) 
    for (int i = 1; i < n; i++) 
        vec[j][i] |= vec[j][i-1];

// 处理每个条件并更新区间
int l = 1, r = n;
if (op == '>') 
    l = max(l, upper_bound(vec[a].begin(), vec[a].end(), b) - vec[a].begin() + 1);
else 
    r = min(r, lower_bound(vec[a].begin(), vec[a].end(), b) - vec[a].begin());
```

---

### 关键技巧总结
1. **单调性利用**：前缀或的单调性使得二分法成为可能，极大降低查询复杂度。  
2. **区间交集维护**：将多个约束条件转化为区间的左右边界调整，最终求交集。  
3. **行列转换优化**：将列作为主维度存储，提升缓存命中率，加速预处理。  

---

### 拓展练习
1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)（二分答案+区间划分）  
2. [P3743 kotori的设备](https://www.luogu.com.cn/problem/P3743)（二分时间+资源管理）  
3. [P1419 寻找段落](https://www.luogu.com.cn/problem/P1419)（单调队列+二分平均值）

---
处理用时：119.52秒