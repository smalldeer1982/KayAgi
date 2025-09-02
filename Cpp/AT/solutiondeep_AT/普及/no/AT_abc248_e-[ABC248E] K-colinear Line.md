# 题目信息

# [ABC248E] K-colinear Line

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc248/tasks/abc248_e

座標平面上の $ N $ 個の点が与えられます。 $ 1\leq\ i\leq\ N $ について、$ i $ 番目の点の座標は $ (X_i,\ Y_i) $ です。

座標平面上の直線であって、$ N $ 個の点のうち $ K $ 個以上の点を通るものの個数を求めてください。  
ただし、そのようなものが無数に存在する場合は `Infinity` を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 300 $
- $ \lvert\ X_i\ \rvert,\ \lvert\ Y_i\ \rvert\ \leq\ 10^9 $
- $ i\neq\ j $ ならば $ X_i\neq\ X_j $ または $ Y_i\neq\ Y_j $
- 入力はすべて整数

### Sample Explanation 1

$ x=0 $, $ y=0 $, $ y=x\pm\ 1 $, $ y=-x\pm\ 1 $ の $ 6 $ 本の直線が条件をみたします。 例えば、$ x=0 $ は、$ 1 $, $ 3 $, $ 5 $ 番目の $ 3 $ 個の点を通ります。 よって、$ 6 $ を出力します。

### Sample Explanation 2

原点を通る直線は無数に存在します。 よって、`Infinity` を出力します。

## 样例 #1

### 输入

```
5 2
0 0
1 0
0 1
-1 0
0 -1```

### 输出

```
6```

## 样例 #2

### 输入

```
1 1
0 0```

### 输出

```
Infinity```

# AI分析结果



【中文题目重写】

# [ABC248E] K-colinear Line

## 题目描述

给定坐标平面上的 $ N $ 个点。对于 $ 1\leq\ i\leq\ N $，第 $ i $ 个点的坐标为 $ (X_i,\ Y_i) $。

请求出坐标平面上满足以下条件的直线数量：该直线至少经过 $ N $ 个点中的 $ K $ 个点。若存在无限多条这样的直线，则输出 `Infinity`。

## 说明/提示

### 约束条件
- $ 1\ \leq\ K\ \leq\ N\ \leq\ 300 $
- $ \lvert\ X_i\ \rvert,\ \lvert\ Y_i\ \rvert\ \leq\ 10^9 $
- 所有点的坐标互不相同
- 输入均为整数

### 样例解释
样例1中有6条符合条件的直线，样例2因$K=1$输出无限条。

---

【算法分类】
数学、枚举

---

【题解分析与结论】

### 核心思路
通过枚举两点确定直线，统计每条直线的共线点数。关键点包括：
1. **三点共线判断**：使用叉积公式避免浮点误差
2. **去重机制**：标记已处理的点对防止重复统计
3. **特判处理**：$K=1$时直接输出`Infinity`

### 最优解关键
- **向量叉积法**：用 $(x_b-x_a)(y_c-y_a) = (x_c-x_a)(y_b-y_a)$ 判断共线
- **标记矩阵优化**：使用二维数组记录已处理的点对，保证每条直线只计算一次
- **批量标记技巧**：当发现新直线时，将其上所有点对标记为已访问

---

【精选题解】

1. **FFTotoro（4星）**
- **亮点**：清晰的标记逻辑与简洁的代码结构
- **核心代码**：
```cpp
bool pd(int a,int b,int c){
    return (y[b]-y[a])*(x[c]-x[a]) == (x[b]-x[a])*(y[c]-y[a]);
}

for(int i=1;i<n;i++) {
    for(int j=i+1;j<=n;j++) {
        if(!f[i][j]){
            vector<int> v = {i,j};
            for(int k=j+1;k<=n;k++)
                if(pd(i,j,k)) v.push_back(k);
            // 标记所有点对
            for(int x : v) for(int y : v) 
                if(x < y) f[x][y] = true;
            if(v.size() >= K) ans++;
        }
    }
}
```

2. **VelvetChords（4星）**
- **亮点**：结构化的数据存储与完整的状态跟踪
- **调试心得**：通过预处理更小的点对来避免重复枚举
- **核心片段**：
```cpp
struct Node { ll x,y; };
bool cmp(Node i, Node j, Node k) {
    return (k.y-j.y)*(k.x-i.x) == (k.y-i.y)*(k.x-j.x);
}

for(int i=1;i<n;i++) {
    for(int j=i+1;j<=n;j++) {
        if(!ok[i][j]) {
            int cnt = 2;
            vector<int> points = {i,j};
            // 统计共线点
            for(int l=1;l<=n;l++) {
                if(l==i||l==j) continue;
                if(cmp(a[i],a[j],a[l])) {
                    cnt++;
                    points.push_back(l);
                }
            }
            // 批量标记
            for(int x : points) 
                for(int y : points)
                    ok[x][y] = true;
            if(cnt >= K) ans++;
        }
    }
}
```

---

【举一反三】

### 关键技巧扩展
- **几何哈希**：将直线参数标准化后哈希存储，适用于更大数据量
- **极角排序**：在处理射线类问题时，可用极角排序优化共线判断

### 推荐习题
1. [P2789 直线交点数](https://www.luogu.com.cn/problem/P2789) - 直线交点的组合数学
2. [P1355 神秘大三角](https://www.luogu.com.cn/problem/P1355) - 点与几何图形的位置关系
3. [P1257 平面上的最接近点对](https://www.luogu.com.cn/problem/P1257) - 分治算法在几何中的应用

---
处理用时：90.46秒