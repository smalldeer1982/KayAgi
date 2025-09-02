# 题目信息

# Kuriyama Mirai's Stones

## 题目描述

Kuriyama Mirai has killed many monsters and got many (namely $ n $ ) stones. She numbers the stones from $ 1 $ to $ n $ . The cost of the $ i $ -th stone is $ v_{i} $ . Kuriyama Mirai wants to know something about these stones so she will ask you two kinds of questions:

1. She will tell you two numbers, $ l $ and $ r (1<=l<=r<=n) $ , and you should tell her ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF433B/a68d6654cf2b25883008b776a62307a377b6be58.png).
2. Let $ u_{i} $ be the cost of the $ i $ -th cheapest stone (the cost that will be on the $ i $ -th place if we arrange all the stone costs in non-decreasing order). This time she will tell you two numbers, $ l $ and $ r (1<=l<=r<=n) $ , and you should tell her ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF433B/81f5c65268118775753c7eebcdd998c0bae9a99d.png).

For every question you should give the correct answer, or Kuriyama Mirai will say "fuyukai desu" and then become unhappy.

## 说明/提示

Please note that the answers to the questions may overflow 32-bit integer type.

## 样例 #1

### 输入

```
6
6 4 2 7 2 7
3
2 3 6
1 3 4
1 1 6
```

### 输出

```
24
9
28
```

## 样例 #2

### 输入

```
4
5 5 2 3
10
1 2 4
2 1 4
1 1 1
2 1 4
2 1 2
1 1 1
1 3 3
1 1 3
1 4 4
1 2 2
```

### 输出

```
10
15
5
15
5
5
2
12
3
5
```

# AI分析结果



# Kuriyama Mirai的石头

## 题目描述

Kuriyama Mirai 杀死了许多怪物并获得了许多（即 $n$ 个）石头。她将石头从 $1$ 到 $n$ 编号，第 $i$ 块石头的成本为 $v_i$。Kuriyama Mirai 想了解这些石头的某些信息，因此她会向你提出两种问题：

1. 给定两个数字 $l$ 和 $r$（$1 \leq l \leq r \leq n$），请计算 $\sum_{i=l}^r v_i$。
2. 令 $u_i$ 表示第 $i$ 便宜的石头成本（即将所有石头成本按非降序排列后第 $i$ 位的值），给定两个数字 $l$ 和 $r$（$1 \leq l \leq r \leq n$），请计算 $\sum_{i=l}^r u_i$。

对于每个问题，你需要给出正确答案，否则 Kuriyama Mirai 会变得不开心。

## 说明/提示

注意答案可能超出 32 位整型范围。

## 算法分类
前缀和

---

### 题解综合分析

所有题解均采用 **双前缀和** 的核心思路：  
1. 预处理原数组的前缀和数组  
2. 预处理排序数组的前缀和数组  
3. 两种查询分别对应两种前缀和的差值计算  

线段树解法虽然正确但效率较低，暴力解法必然超时。前缀和方案以 $O(n \log n)$ 预处理 + $O(1)$ 查询的复杂度完美适配题目规模。

---

### 精选题解

#### 1. 作者：liuyi0905（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 使用二维数组同时存储两种前缀和，代码结构紧凑  
- 通过排序原数组的副本生成有序版本的前缀和  
- 处理输入输出简洁高效  

**核心代码**：
```cpp
long long n,m,v[100001],pre[3][100001];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        pre[1][i]=pre[1][i-1]+v[i];
    }
    sort(v+1,v+n+1);
    for(int i=1;i<=n;i++)pre[2][i]=pre[2][i-1]+v[i];
    // ... 处理查询部分
}
```

#### 2. 作者：Eason_AC（⭐⭐⭐⭐）
**关键亮点**：  
- 明确分离原数组与排序数组的存储空间  
- 详细推导前缀和数学原理，增强可读性  
- 使用独立数组存储不同版本数据  

**核心代码**：
```cpp
int a1[100007],a2[100007];
long long sum[3][100007];
// ...
sort(a2 + 1, a2 + n + 1);
for(int i = 1; i <= n; ++i)
    sum[1][i] = sum[1][i - 1] + a1[i], sum[2][i] = sum[2][i - 1] + a2[i];
```

#### 3. 作者：wxzzzz（⭐⭐⭐⭐）
**关键亮点**：  
- 使用两个独立前缀和数组，逻辑清晰  
- 变量命名直观体现功能差异  
- 代码结构简洁，无冗余操作  

**核心代码**：
```cpp
int a[1000005], s[1000005], ss[1000005];
// ...
sort(a + 1, a + 1 + n);
for(int i = 1; i <= n; i++){
    ss[i] = ss[i - 1] + a[i];
}
```

---

### 最优技巧总结
1. **双前缀和预处理**：通过原数组和排序数组的双重预处理，将区间和查询转化为常数时间操作  
2. **数组副本排序**：复制原数组后排序，保留原始数据的同时生成有序版本  
3. **长整型防溢出**：使用 `long long` 类型存储前缀和，避免大数溢出  

---

### 拓展思考
类似问题可扩展为多维度预处理，例如：  
- 维护区间最大值/最小值的前缀统计  
- 动态版本需结合树状数组等数据结构  
- 带权重的前缀和计算  

---

### 推荐习题
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115) - 前缀和经典应用  
2. [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406) - 差分与前缀和的结合  
3. [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671) - 前缀和在分奇偶场景中的应用

---
处理用时：62.02秒