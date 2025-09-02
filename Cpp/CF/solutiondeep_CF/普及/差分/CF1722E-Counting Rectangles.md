# 题目信息

# Counting Rectangles

## 题目描述

You have $ n $ rectangles, the $ i $ -th rectangle has height $ h_i $ and width $ w_i $ .

You are asked $ q $ queries of the form $ h_s \ w_s \ h_b \ w_b $ .

For each query output, the total area of rectangles you own that can fit a rectangle of height $ h_s $ and width $ w_s $ while also fitting in a rectangle of height $ h_b $ and width $ w_b $ . In other words, print $ \sum h_i \cdot w_i $ for $ i $ such that $ h_s < h_i < h_b $ and $ w_s < w_i < w_b $ .

Please note, that if two rectangles have the same height or the same width, then they cannot fit inside each other. Also note that you cannot rotate rectangles.

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722E/eea41631a59a3be709b240003a8697e693220564.png)In the first test case, there is only one query. We need to find the sum of areas of all rectangles that can fit a $ 1 \times 1 $ rectangle inside of it and fit into a $ 3 \times 4 $ rectangle.

Only the $ 2 \times 3 $ rectangle works, because $ 1 < 2 $ (comparing heights) and $ 1 < 3 $ (comparing widths), so the $ 1 \times 1 $ rectangle fits inside, and $ 2 < 3 $ (comparing heights) and $ 3 < 4 $ (comparing widths), so it fits inside the $ 3 \times 4 $ rectangle. The $ 3 \times 2 $ rectangle is too tall to fit in a $ 3 \times 4 $ rectangle. The total area is $ 2 \cdot 3 = 6 $ .

## 样例 #1

### 输入

```
3
2 1
2 3
3 2
1 1 3 4
5 5
1 1
2 2
3 3
4 4
5 5
3 3 6 6
2 1 4 5
1 1 2 10
1 1 100 100
1 1 3 3
3 1
999 999
999 999
999 998
1 1 1000 1000```

### 输出

```
6
41
9
0
54
4
2993004```

# AI分析结果

### 题目内容重写

你有 $n$ 个矩形，第 $i$ 个矩形的高度为 $h_i$，宽度为 $w_i$。你需要回答 $q$ 次询问，每次询问给出四个整数 $h_s, w_s, h_b, w_b$，要求输出所有满足 $h_s < h_i < h_b$ 且 $w_s < w_i < w_b$ 的矩形的面积之和。注意，如果两个矩形的高度或宽度相同，则它们不能相互嵌套。此外，矩形不能旋转。

请注意，某些测试用例的答案可能无法用 32 位整数表示，因此你应使用至少 64 位整数类型（如 C++ 中的 `long long`）。

### 样例 #1

#### 输入

```
3
2 1
2 3
3 2
1 1 3 4
5 5
1 1
2 2
3 3
4 4
5 5
3 3 6 6
2 1 4 5
1 1 2 10
1 1 100 100
1 1 3 3
3 1
999 999
999 999
999 998
1 1 1000 1000
```

#### 输出

```
6
41
9
0
54
4
2993004
```

### 题解分析与结论

本题的核心问题是在二维平面上快速查询满足特定条件的矩形面积之和。由于 $h_i$ 和 $w_i$ 的范围较小（$1 \leq h_i, w_i \leq 1000$），因此可以通过预处理二维前缀和来优化查询效率。

#### 关键思路与技巧

1. **二维前缀和**：通过预处理二维前缀和，可以在 $O(1)$ 时间内查询任意矩形区域内的面积之和。这是本题的核心优化点。
2. **边界处理**：由于查询条件是开区间（$h_s < h_i < h_b$ 且 $w_s < w_i < w_b$），因此在计算前缀和时需要注意边界处理，确保查询结果不包含边界。
3. **数据类型**：由于面积之和可能很大，需要使用 `long long` 类型来存储结果。

### 所选高星题解

#### 题解1：ScottSuperb (5星)

**关键亮点**：
- 使用二维前缀和优化查询效率，代码简洁明了。
- 边界处理清晰，确保了查询结果的正确性。

**核心代码**：
```cpp
ll s[1005][1005];

int main() {
    int t = read(), n, q, h, w, hs, ws, hb, wb;
    while (t--) {
        n = read(), q = read();
        for (int i = 1; i <= 1000; ++i)
            for (int j = 1; j <= 1000; ++j)
                s[i][j] = 0;
        while (n--)
            h = read(), w = read(), s[h][w] += h * w;
        for (int i = 1; i <= 1000; ++i)
            for (int j = 1; j <= 1000; ++j)
                s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        while (q--)
            hs = read(), ws = read(), hb = read(), wb = read(), 
            write(s[hb - 1][wb - 1] - s[hb - 1][ws] - s[hs][wb - 1] + s[hs][ws]);
    }
    return 0;
}
```

#### 题解2：Lantrol (4星)

**关键亮点**：
- 同样使用二维前缀和，代码结构清晰，易于理解。
- 强调了数据类型的重要性，避免了潜在的溢出问题。

**核心代码**：
```cpp
int n,q;
long long juz[1010][1010];

void solve(){
    memset(juz,0,sizeof(juz));
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int h,w;
        cin>>h>>w;
        juz[h][w]+=h*w;
    }
    for(int i=1;i<=1000;i++){
        for(int j=1;j<=1000;j++){
            juz[i][j]+=juz[i-1][j]+juz[i][j-1]-juz[i-1][j-1];
        }
    }
    while(q--){
        int xs,ys,xb,yb;
        cin>>xs>>ys>>xb>>yb;
        xs++;ys++;xb--;yb--;
        cout<<juz[xb][yb]-juz[xs-1][yb]-juz[xb][ys-1]+juz[xs-1][ys-1]<<endl;
    }
}
```

#### 题解3：hayzxjr (4星)

**关键亮点**：
- 详细解释了二维前缀和的推导过程，帮助理解其原理。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
int t, n, q, h, w;
ll m[M][M], ans;
int h1, w1, h2, w2;

int main() {
    scanf("%d", &t);
    for(int z = 1; z <= t; z++){
        memset(m, 0, sizeof m);
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i++){
            scanf("%d%d", &h, &w);
            m[h][w] = m[h][w] + h * w;
        }
        for(int i = 1; i <= M + 2; i++)
          for(int j = 1; j <= M + 2; j++)
            m[i][j] = m[i][j] + m[i - 1][j] + m[i][j - 1] - m[i - 1][j - 1];
        for(int i = 1; i <= q; i++){
            scanf("%d%d%d%d", &h1, &w1, &h2, &w2);
            ans = m[h2 - 1][w2 - 1] - m[h1][w2 - 1] - m[h2 - 1][w1] + m[h1][w1];
            printf("%lld\n", ans);
        }
    }
    return 0;
}
```

### 推荐题目

1. **P1719 最大加权矩形**：考察二维前缀和的应用，适合练习类似技巧。
2. **P2280 [HNOI2003]激光炸弹**：利用二维前缀和解决区域内的最大值问题。
3. **P3397 地毯**：通过二维差分解决区域覆盖问题，与本题的二维前缀和思想类似。

### 总结

本题的核心在于通过二维前缀和优化查询效率，关键在于预处理和边界处理。掌握这一技巧后，可以轻松应对类似的二维区间查询问题。

---
处理用时：53.01秒