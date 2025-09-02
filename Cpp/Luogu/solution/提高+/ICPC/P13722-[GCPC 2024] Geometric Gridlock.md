# [GCPC 2024] Geometric Gridlock

## 题目描述

*Pentominous* 是一个基于十二种五连块（pentomino）的网格逻辑谜题。五连块是由五个大小相等的正方形通过边相连组成的多边形。

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/dwgeqnjb.png)

图 G.1：十二种五连块（考虑镜像和旋转后唯一）及其名称。
:::

本谜题的目标是将一个网格划分为若干个大小为 $5$ 的区域（即五连块），使得任意两个有公共边的区域形状不同。
你可以旋转和翻转五连块，但这些旋转和翻转都算作同一种形状。
十二种可能的形状如图 G.1 所示。

在普通的 *Pentominous* 谜题中，玩家会被给出一些预填充的格子，这些格子的区域形状已经确定。
而在本题中，你需要处理一个完全空白、尺寸为 $h\times w$ 的网格，你的任务是构造任意一种合法的五连块划分方案。

## 说明/提示

:::align{center}

| ![](https://cdn.luogu.com.cn/upload/image_hosting/xzo3g55c.png) | ![](https://cdn.luogu.com.cn/upload/image_hosting/arn3qmip.png) | ![](https://cdn.luogu.com.cn/upload/image_hosting/e6kfe7wa.png) |
|:-:|:-:|:-:|
| 样例输出 1 的示意图。 | 样例输出 2 的示意图。 | 样例输出 4 的示意图。 |


| [![](https://cdn.luogu.com.cn/upload/image_hosting/5c9kokf9.png)](https://puzz.link/p?pentominous/10/10/s9967k09h77j4o4o1h157jbjbj00h87k30a8s) | [![](https://cdn.luogu.com.cn/upload/image_hosting/dz1q9nmw.png)](https://puzz.link/p?pentominous/10/10/s5558k95h78j4o5o3o4o42h61k88a6s) |
|:-:|:-:|
| [![](https://cdn.luogu.com.cn/upload/image_hosting/ung8r57e.png)](https://puzz.link/p?pentominous/10/10/r44a44k4j4j7j4j44454k4o3o4o4i47r) | [![](https://cdn.luogu.com.cn/upload/image_hosting/8ltajbb5.png)](https://puzz.link/p?pentominous/10/10/s3327k22h71j1o7l1h1l1h2o21h11k7337s) |


比赛结束后你可以尝试的 *Pentominous* 谜题示例。

:::

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 5```

### 输出

```
yes
UUXUU
UXXXU
UUXUU```

## 样例 #2

### 输入

```
2 10```

### 输出

```
yes
LLLLNNNPPP
LIIIIINNPP```

## 样例 #3

### 输入

```
99 17```

### 输出

```
no```

## 样例 #4

### 输入

```
6 10```

### 输出

```
yes
IPPYYYYVVV
IPPXYLLLLV
IPXXXFZZLV
ITWXFFFZUU
ITWWNNFZZU
TTTWWNNNUU```

## 样例 #5

### 输入

```
1 5```

### 输出

```
yes
IIIII```

# 题解

## 作者：cosf (赞：0)

为了尊重每一个题目中的块，构造中每一个都有可能出现。

显然有 $5 | (n \times m)$，否则无法摆放。不妨设 $5 | m$。

![](https://cdn.luogu.com.cn/upload/image_hosting/n3vj0buw.png)

对于 $n = 1$，显然只有 $m=5$ 时可行。对于 $n=2$，显然 $m=5$ 无法构造，否则可以类似图中的方法拓展下去。

否则可以把 $n$ 写成 $3k + r$，其中 $r \in \{3, 4, 5\}$。我们可以用 $k \times \frac{m}{5}$ 个 $3 \times 5$ 的块以及 $\frac{m}{5}$ 个 $r \times 5$ 的块拼起来。注意 $3 \times 5, 4 \times 5$ 需要交替摆放。

```cpp line-numbers
#include <iostream>
using namespace std;

#define MAXN 105

string P[4] = {"PPP\nPP ", "PPP\n PP", " PP\nPPP", "PP\nPP\n P"};
string N[2] = {" NNN\nNN  ", "NN  \n NNN"};
string Y[3] = {"  Y \nYYYY", "YYYY\n  Y ", " Y\nYY\n Y\n Y"};
string U[2] = {"UU\nU \nUU", "UU\n U\nUU"};
string X[1] = {" X \nXXX\n X "};
string T[1] = {"T  \nTTT\nT  "};
string L[1] = {"   L\nLLLL"};
string I[1] = {"IIIII"};
string F[1] = {" F \nFF \n FF"};
string W[1] = {" WW\nWW \nW  "};
string V[1] = {"V  \nV  \nVVV"};
string Z[1] = {"Z  \nZZZ\n  Z"};

char mp[MAXN][MAXN];

inline char gc(string s, int sx, int sy, int px, int py)
{
    return s[px * (sy + 1) + py];
}

void draw(string S, int px, int py, int sx, int sy) // S, pos, size
{
    for (int i = 0; i < sx; i++)
    {
        for (int j = 0; j < sy; j++)
        {
            char ch = gc(S, sx, sy, i, j);
            if (ch != ' ')
            {
                mp[i + px][j + py] = ch;
            }
        }
    }
}

void draw2(int w) // 这些顺序与图中一致。
{
    draw(P[0], 0, 0, 2, 3);
    int n = (w / 5) - 1;
    for (int i = 0; i < n; i++)
    {
        draw(N[i & 1], 0, 5 * i + 2, 2, 4);
        draw(Y[i & 1], 0, 5 * i + 4, 2, 4);
    }
    draw(P[((n + 1) & 1) + 1], 0, 5 * n + 2, 2, 3);
}

void draw30(int px, int py)
{
    draw(U[0], px, py, 3, 2);
    draw(X[0], px, py + 1, 3, 3);
    draw(U[1], px, py + 3, 3, 2);
}

void draw31(int px, int py)
{
    draw(T[0], px, py, 3, 3);
    draw(Y[1], px, py + 1, 2, 4);
    draw(L[0], px + 1, py + 1, 2, 4);
}

void (*draw3[2])(int, int) = {draw30, draw31};

void draw40(int px, int py) // 这两个理论上要和图中对换一下
{
    draw(U[0], px, py, 3, 2);
    draw(F[0], px, py + 1, 3, 3);
    draw(P[3], px, py + 3, 3, 2);
    draw(I[0], px + 3, py, 1, 5);
}

void draw41(int px, int py)
{
    draw(I[0], px, py, 1, 5);
    draw(U[0], px + 1, py, 3, 2);
    draw(F[0], px + 1, py + 1, 3, 3);
    draw(P[3], px + 1, py + 3, 3, 2);
}

void (*draw4[2])(int, int) = {draw40, draw41};

void draw5(int px, int py)
{
    draw(P[0], px, py, 2, 3);
    draw(W[0], px, py + 2, 3, 3);
    draw(V[0], px + 2, py, 3, 3);
    draw(Z[0], px + 2, py + 1, 3, 3);
    draw(Y[2], px + 1, py + 3, 4, 2);
}

int n, m;

bool swp;

int main()
{
    cin >> n >> m;
    if (n * m % 5)
    {
        cout << "no\n";
        return 0;
    }
    if (m % 5)
    {
        swap(n, m);
        swp = true;
    }
    if (n == 1)
    {
        if (m > 5)
        {
            cout << "no\n";
            return 0;
        }
        draw(I[0], 0, 0, 1, 5);
    }
    else if (n == 2)
    {
        if (m == 5)
        {
            cout << "no\n";
            return 0;
        }
        draw2(m);
    }
    else
    {
        for (int i = 0; i + 5 < n; i += 3)
        {
            for (int j = 0; j < m; j += 5)
            {
                draw3[(i + j) & 1](i, j);
            }
        }
        int px = n % 3 + 3;
        if (px == 3)
        {
            int i = n - px;
            for (int j = 0; j < m; j += 5)
            {
                draw3[(i + j) & 1](i, j);
            }
        }
        else if (px == 4)
        {
            int i = n - px;
            for (int j = 0; j < m; j += 5)
            {
                draw4[(i + j) & 1](i, j);
            }
        }
        else
        {
            int i = n - px;
            for (int j = 0; j < m; j += 5)
            {
                draw5(i, j);
            }
        }
    }
    cout << "yes\n";
    if (swp)
    {
        for (int j = 0; j < m; j++)
        {
            for (int i = 0; i < n; i++)
            {
                cout << mp[i][j];
            }
            cout << '\n';
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << mp[i][j];
            }
            cout << '\n';
        }
    }
}

```

---

