# 题目信息

# [ABC254F] Rectangle GCD

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc254/tasks/abc254_f

正整数 $ N $ と長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ と $ B=(B_1,B_2,\dots,B_N) $ が与えられます。

$ N\ \times\ N $ のマス目があります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と呼びます。$ 1\ \le\ i,j\ \le\ N $ を満たす整数の組 $ (i,j) $ に対し、マス $ (i,j) $ に $ A_i\ +\ B_j $ が書かれています。以下のクエリを $ Q $ 個処理してください。

- $ 1\ \le\ h_1\ \le\ h_2\ \le\ N,1\ \le\ w_1\ \le\ w_2\ \le\ N $ を満たす整数の組 $ h_1,h_2,w_1,w_2 $ が与えられる。左上隅が $ (h_1,w_1) $、右下隅が $ (h_2,w_2) $ である矩形領域に含まれる整数の最大公約数を求めよ。

## 说明/提示

### 制約

- $ 1\ \le\ N,Q\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i,B_i\ \le\ 10^9 $
- $ 1\ \le\ h_1\ \le\ h_2\ \le\ N $
- $ 1\ \le\ w_1\ \le\ w_2\ \le\ N $
- 入力はすべて整数である。

### Sample Explanation 1

マス $ (i,j) $ に書かれている整数を $ C_{i,j} $ とします。 $ 1 $ 個目のクエリについて、$ C_{1,2}=4,C_{1,3}=6,C_{2,2}=6,C_{2,3}=8 $ なのでこれらの最大公約数の $ 2 $ が答えとなります。

## 样例 #1

### 输入

```
3 5
3 5 2
8 1 3
1 2 2 3
1 3 1 3
1 1 1 1
2 2 2 2
3 3 1 1```

### 输出

```
2
1
11
6
10```

## 样例 #2

### 输入

```
1 1
9
100
1 1 1 1```

### 输出

```
109```

# AI分析结果



## 唯一算法分类
线段树 / ST表（区间 GCD 查询）

---

## 题解思路与算法要点

### 核心思路
利用更相减损术性质，将二维矩形 GCD 查询转化为三个部分的 GCD 合并：
1. 矩阵左上角初始值 `A[h1] + B[w1]`
2. 行差分数组 `A[h1+1..h2]` 的区间 GCD
3. 列差分数组 `B[w1+1..w2]` 的区间 GCD

### 关键步骤
1. **差分数组预处理**：计算两个数列的差分数组 `dA[i]=A[i]-A[i-1]` 和 `dB[j]=B[j]-B[j-1]`
2. **区间 GCD 维护**：使用 ST 表或线段树维护差分数组的区间 GCD
3. **查询组合**：对每个查询计算三部分的 GCD 合并

### 解决难点
- 二维问题降维处理：通过差分将二维矩阵转化为一维数组的区间查询
- 区间无效情况处理：当查询行或列仅有一个元素时，跳过差分查询

---

## 题解评分（≥4星）

### Gyc_Fisher（★★★★☆）
- 思路清晰，详细推导数学性质
- 提供线段树实现，代码结构清晰
- 包含快速 GCD 优化代码

### Powerless233（★★★★☆）
- 使用 ST 表实现，代码简洁高效
- 数学推导简明扼要，适合快速理解
- 预处理部分采用倍增思想

### liangbowen（★★★★★）
- 代码最简洁，仅 40 行实现核心逻辑
- 使用 ST 表预处理，查询时间复杂度最优
- 完美处理边界条件，包含绝对值处理

---

## 最优思路提炼

### 关键技巧
1. **差分降维法**：将二维矩阵 GCD 转化为三个一维 GCD 的合并
2. **ST表优化**：预处理时间 O(nlogn)，查询时间 O(1)
3. **边界处理**：使用 `if (x != y)` 跳过无效区间查询

### 实现要点
```cpp
int ans = A[x1] + B[y1];
if (x1 < x2) ans = gcd(ans, ST_A.query(x1+1, x2));
if (y1 < y2) ans = gcd(ans, ST_B.query(y1+1, y2));
```

---

## 类似题目推荐
1. [P1890 GCD区间](https://www.luogu.com.cn/problem/P1890)（一维区间 GCD）
2. [P5278 算术天才⑨与等差数列](https://www.luogu.com.cn/problem/P5278)（区间差分性质应用）
3. [P6242 线段树](https://www.luogu.com.cn/problem/P6242)（区间操作与 GCD 结合）

---

## 算法可视化设计

### 动画方案设计
1. **网格绘制**：绘制 N×N 矩阵，初始显示 A[i]+B[j] 的值
2. **差分高亮**：用不同颜色标记行差分（红色）和列差分（蓝色）
3. **查询演示**：
   - 闪烁显示查询矩形左上角（黄色）
   - 横向展开显示行差分查询过程（红色箭头）
   - 纵向展开显示列差分查询过程（蓝色箭头）
4. **结果合并**：三部分 GCD 值以气泡形式弹出，最终结果高亮显示

### 复古像素风格
- **调色板**：8-bit 风格（#FF0000 红、#0000FF 蓝、#FFFF00 黄）
- **音效设计**：
  - 差分计算：8-bit "哔"声
  - 查询完成：经典 FC 过关音效
- **自动演示**：贪吃蛇式自动路径扫描查询区域

---

## 核心代码实现（ST表版）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;
int A[MAXN], B[MAXN], dA[MAXN], dB[MAXN];
int stA[MAXN][20], stB[MAXN][20];

void build(int n, int arr[], int st[][20]) {
    for(int i=1; i<=n; ++i) st[i][0] = abs(arr[i]);
    for(int j=1; (1<<j)<=n; ++j)
        for(int i=1; i+(1<<j)-1<=n; ++i)
            st[i][j] = gcd(st[i][j-1], st[i+(1<<(j-1))][j-1]);
}

int query(int st[][20], int l, int r) {
    if(l > r) return 0;
    int k = log2(r - l + 1);
    return gcd(st[l][k], st[r-(1<<k)+1][k]);
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    
    for(int i=1; i<=n; ++i) scanf("%d", A+i);
    for(int i=1; i<=n; ++i) scanf("%d", B+i);
    
    for(int i=2; i<=n; ++i) dA[i] = A[i] - A[i-1];
    for(int i=2; i<=n; ++i) dB[i] = B[i] - B[i-1];
    
    build(n, dA, stA);
    build(n, dB, stB);
    
    while(q--) {
        int h1,h2,w1,w2;
        scanf("%d%d%d%d",&h1,&h2,&w1,&w2);
        int ans = A[h1] + B[w1];
        ans = gcd(ans, query(stA, h1+1, h2));
        ans = gcd(ans, query(stB, w1+1, w2));
        printf("%d\n", abs(ans));
    }
    return 0;
}
```

---
处理用时：80.00秒