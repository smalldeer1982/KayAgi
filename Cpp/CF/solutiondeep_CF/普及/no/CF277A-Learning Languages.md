# 题目信息

# Learning Languages

## 题目描述

The "BerCorp" company has got $ n $ employees. These employees can use $ m $ approved official languages for the formal correspondence. The languages are numbered with integers from $ 1 $ to $ m $ . For each employee we have the list of languages, which he knows. This list could be empty, i. e. an employee may know no official languages. But the employees are willing to learn any number of official languages, as long as the company pays their lessons. A study course in one language for one employee costs $ 1 $ berdollar.

Find the minimum sum of money the company needs to spend so as any employee could correspond to any other one (their correspondence can be indirect, i. e. other employees can help out translating).

## 说明/提示

In the second sample the employee $ 1 $ can learn language $ 2 $ , and employee $ 8 $ can learn language $ 4 $ .

In the third sample employee $ 2 $ must learn language $ 2 $ .

## 样例 #1

### 输入

```
5 5
1 2
2 2 3
2 3 4
2 4 5
1 5
```

### 输出

```
0
```

## 样例 #2

### 输入

```
8 7
0
3 1 2 3
1 1
2 5 4
2 6 7
1 3
2 7 4
1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2 2
1 2
0
```

### 输出

```
1
```

# AI分析结果



# 学习语言

## 题目描述

BerCorp 公司有 $n$ 名员工，他们可以使用 $m$ 种经批准的官方语言进行正式通信。语言以 $1$ 到 $m$ 的整数编号。每个员工掌握若干种语言（可能为空）。公司可为员工支付学习语言的费用（每人每学一种语言需花费 1 Ber元）。求使所有员工能够直接或间接交流的最小总费用。

## 说明/提示

- 样例 2 中：员工 1 学习语言 2，员工 8 学习语言 4
- 样例 3 中：员工 2 必须学习语言 2

## 样例 #1

### 输入
```
5 5
1 2
2 2 3
2 3 4
2 4 5
1 5
```
### 输出
```
0
```

---

### 算法分类
并查集

---

### 题解综合分析

题目核心是构建人员与语言的关系网络，通过连通性分析计算最小学习次数。最优解法采用**并查集将人员与语言节点合并**，统计连通块数目。关键技巧包括：
1. 将语言建模为虚拟节点（编号n+1~n+m）
2. 通过并查集合并人员与其掌握的所有语言
3. 统计以人员为根的连通块数量
4. 全无语言时的特判处理

---

### 精选题解

#### ⭐⭐⭐⭐⭐ 题解作者：⚡LZSY01_XZY (20 赞)
**核心思路**：将人员与语言视为并查集节点，合并人员及其掌握的语言，最后统计以人员为根的连通块数。
```cpp
// 并查集核心逻辑
void together(int x, int y) {
    int r1 = find(x), r2 = find(y);
    if (r1 != r2) f[r1] = r2;
}

// 主处理逻辑
for (每个员工i) {
    读取该员工掌握的语言k;
    for (每个语言) together(i, n+语言编号);
}

// 统计连通块
int ans = 0;
for (每个员工i) 
    if (find(i) == i) ans++;
if (无任何语言) ans = n;
else ans -= 1;
```
**亮点**：虚拟语言节点设计巧妙，通过根节点类型判断避免统计纯语言连通块。代码简洁高效，时间复杂度O(α(n))。

#### ⭐⭐⭐⭐ 题解作者：Zvelig1205 (3 赞)
**优化点**：采用路径压缩+按秩合并的优化并查集，处理大规模数据更高效。代码中通过`find`操作自动路径压缩：
```cpp
int find(int x) { 
    return f[x] == x ? x : f[x] = find(f[x]);
}
```
**特殊处理**：单独标记全不会语言的边界情况，确保答案正确性。

---

### 关键思路总结
1. **虚拟节点建模**：将语言扩展为独立节点（编号n+1~n+m），建立人员-语言二分图
2. **连通性分析**：人员与语言的连通等价于可交流性
3. **根节点筛选**：统计时只考虑以人员为根的连通块，自动过滤纯语言集合
4. **边界处理**：全无语言时答案为n，否则答案为连通块数-1

---

### 拓展应用
类似连通性问题可考虑：
1. 社交网络中的群体划分（CF1242B 0-1 MST）
2. 像素连通区域检测（LeetCode 200.岛屿数量）
3. 电路连接检查（洛谷 P2330）

---

### 推荐习题
1. [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)  
2. [CF1242B 0-1 MST](https://www.luogu.com.cn/problem/CF1242B)  
3. [P2330 [SCOI2005] 繁忙的都市](https://www.luogu.com.cn/problem/P2330)

---
处理用时：63.33秒