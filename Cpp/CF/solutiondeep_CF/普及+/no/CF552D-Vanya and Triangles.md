# 题目信息

# Vanya and Triangles

## 题目描述

Vanya got bored and he painted $ n $ distinct points on the plane. After that he connected all the points pairwise and saw that as a result many triangles were formed with vertices in the painted points. He asks you to count the number of the formed triangles with the non-zero area.

## 说明/提示

Note to the first sample test. There are $ 3 $ triangles formed: $ (0,0)-(1,1)-(2,0) $ ; $ (0,0)-(2,2)-(2,0) $ ; $ (1,1)-(2,2)-(2,0) $ .

Note to the second sample test. There is $ 1 $ triangle formed: $ (0,0)-(1,1)-(2,0) $ .

Note to the third sample test. A single point doesn't form a single triangle.

## 样例 #1

### 输入

```
4
0 0
1 1
2 0
2 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
0 0
1 1
2 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1
1 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Vanya和三角形

## 题目描述
Vanya觉得无聊，于是在平面上画了 $n$ 个不同的点。之后，他将所有点两两相连，发现由此形成了许多以这些点为顶点的三角形。他请你计算形成的面积不为零的三角形的数量。

## 说明/提示
第一个样例测试的说明。形成了 $3$ 个三角形：$(0,0)-(1,1)-(2,0)$ ；$(0,0)-(2,2)-(2,0)$ ；$(1,1)-(2,2)-(2,0)$ 。

第二个样例测试的说明。形成了 $1$ 个三角形：$(0,0)-(1,1)-(2,0)$ 。

第三个样例测试的说明。单个点无法形成三角形。

## 样例 #1
### 输入
```
4
0 0
1 1
2 0
2 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3
0 0
1 1
2 0
```
### 输出
```
1
```

## 样例 #3
### 输入
```
1
1 1
```
### 输出
```
0
```

### 算法分类
数学

### 综合分析与结论
所有题解核心思路均基于三角形构成条件，即三点不共线则可构成三角形。主要通过计算三点共线情况，用总组合数减去不构成三角形的情况数得到答案。不同之处在于计算三点共线情况的方式和时间复杂度。
1. **暴力枚举法**：直接枚举所有三个点组合，通过斜率公式判断是否共线，时间复杂度为 $O(n^3)$。
2. **排序优化法**：枚举一个点，计算该点与其他点连线斜率并排序，统计斜率相同点对数，进而得出不能构成三角形的情况数，时间复杂度为 $O(n^2 \log n)$。
3. **线性统计法**：对每个点，枚举其与其他点斜率并计数，再枚举点对计算不合法三角形个数，时间复杂度为 $O(n^2)$。

### 所选的题解
- **作者：mcyqwq (赞：3)  星级：4星**
    - **关键亮点**：提出优化枚举过程，通过排序斜率减少时间复杂度至 $O(n^2 \log n)$。
    - **重点代码 - 核心实现思想**：先计算所有点对斜率并排序，再统计斜率相同点对数，最后用总组合数减去不能构成三角形的情况数。
```cpp
long double slope(point a, point b) {
    if(a.x - b. x == 0) return 1e5;
    return (long double)1.0 * (a.y - b.y) / (a.x - b.x);
}
//...
for(int i = 1, cnt, now; i <= n; i++) {
    cnt = 0, now = 1;
    for(int j = i + 1; j <= n; j++) {
        s[++cnt] = slope(a[i], a[j]);
    }
    std :: sort(s + 1, s + cnt + 1);
    for(int j = 2; j <= cnt; j++) {
        if(s[j] == s[j - 1]) now++;
        else sum += (1ll * now * (now - 1) / 2), now = 1; 
    }
    sum += (1ll * now * (now - 1) / 2); 
}
printf("%lld", 1ll * n * (n - 1) * (n - 2) / 6 - sum);
```
- **作者：Exp10re (赞：0)  星级：4星**
    - **关键亮点**：给出 $O(n^2)$ 做法，通过统计斜率相同点对数计算不合法三角形个数。
    - **重点代码 - 核心实现思想**：先将斜率化为最简分数并计数，再通过双重循环计算不合法三角形个数，最后用总组合数减去不合法数。
```cpp
slope getslope(long long x1, long long y1, long long x2, long long y2) {
    // 计算最简分数形式的斜率
}
//...
for(i = 1;i <= n;i++) {
    for(j = 1;j <= n;j++) {
        if(j == i) {
            continue;
        }
        t = getslope(a[i][0], a[i][1], a[j][0], a[j][1]);
        book[i][t.x][t.y+Delta]++;
    }
}
for(i = 1;i <= n;i++) {
    for(j = 1;j <= n;j++) {
        if(i!= j) {
            t = getslope(a[i][0], a[i][1], a[j][0], a[j][1]);
            dec+=(book[i][t.x][t.y+Delta]-1);
        }
    }
}
printf("%lld",ans-dec/6);
```

### 最优关键思路或技巧
Exp10re 的 $O(n^2)$ 做法通过将斜率化为最简分数并用三维数组统计，避免了排序操作，从而降低时间复杂度。这种方法在处理大量数据时更具优势，核心在于巧妙利用数组统计斜率相同的点对数。

### 可拓展之处
此类题目属于平面几何中关于点与三角形关系的计数问题。类似算法套路常应用于判断图形的构成、计算图形数量等。例如，给定多个点判断能构成多少凸多边形，思路可能是先确定点的位置关系，再通过组合数学方法计算满足条件的多边形数量。

### 洛谷相似题目推荐
1. [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：涉及组合数学与多项式展开系数计算，与本题都需要运用数学知识解决计数问题。
2. [P2671 求和](https://www.luogu.com.cn/problem/P2671)：通过对数据的分析和数学推导来求解，锻炼数学思维，与本题在利用数学原理解题方面类似。
3. [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)：运用递归、递推等数学方法解决整数划分的计数问题，与本题在计数思路上有相通之处。 

---
处理用时：53.18秒