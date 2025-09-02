# [ICPC 2014 WF] Pachinko

## 题目描述

有一个宽度为 $w$ 高度为 $h$ 的方格纸， $ w \times h$ 的格子中，有一些是空的，有一些是洞，有一些是障碍物。从第一行的空的格子中随机选一个放置一个球，向上下左右移动的概率比为 $p_u : p_d : p_l : p_r$（满足 $p_u + p_d + p_l + p_r = 100$），不能移动到有障碍物的格子上。对于每个洞，输出落入该洞的概率。$w \le 20, h \le 10000$。保证第一行没有洞。

## 样例 #1

### 输入

```
3 2
20 20 20 40
X.X
T.T
```

### 输出

```
0.333333333
0.666666667
```

## 样例 #2

### 输入

```
4 5
12 33 28 27
....
.XX.
....
T..T
XTTX
```

### 输出

```
0.435853889
0.403753221
0.081202502
0.079190387
```

# 题解

## 作者：Helenty (赞：3)

显然的高斯消元，但要优化。

消元时可以只消第 $i$ 行上下 $m$ 行，消元时也只消有元的那 $m$ 列，复杂度是 $O(nm^3)$。

注意消元时如果使用高斯约旦消元的话，那么会破坏矩阵性质，要用有会带的那种消元。

在记录的时候可以把矩阵 $i$ 行 $j$ 列记到 $i,j-i+m$ 这样子就只用记录 $2nm$ 个值。

在矩阵消元时如果遇到 $0$，当且仅当这个点和第一行不连通，可以 `continue` 。回代时也是，输出时可能要特判。

代码如下，轻松最优解前三。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 21, M = 10005;
const double eps = 1e-9; 

int n, m, c;              
char s[M][N];             
double u, d, l, r;     
double mp[N*M][N*4];      
double ans[N*M];    
double p; 

int main() {

    scanf("%d%d%lf%lf%lf%lf", &m, &n, &u, &d, &l, &r);
    
    for (int i = 1; i <= n; i++)
        scanf("%s", s[i] + 1);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'X') { 
                mp[(i-1)*m + j][m] = 1;
            } else {
                if (i == 1) c++; 
                
                double g = 0; 
                if (s[i][j] == '.') {
                    if (i != n && s[i+1][j] != 'X') g += d;
                    if (i != 1 && s[i-1][j] != 'X') g += u;
                    if (j != 1 && s[i][j-1] != 'X') g += l;
                    if (j != m && s[i][j+1] != 'X') g += r;
                    
                    if (i != n && s[i+1][j] != 'X')
                        mp[(i)*m + j][0] = d / g;
                    if (i != 1 && s[i-1][j] != 'X')
                        mp[(i-2)*m + j][2*m] = u / g;
                    if (j != 1 && s[i][j-1] != 'X')
                        mp[(i-1)*m + j-1][m+1] = l / g;
                    if (j != m && s[i][j+1] != 'X')
                        mp[(i-1)*m + j+1][m-1] = r / g;
                }
                
                mp[(i-1)*m + j][m] = -1;
            }
        }
    }
    
    for (int i = 1; i <= m; i++)
        if (s[1][i] == '.')
            ans[i] = -1.0 / c;
    
    // 带状高斯消元（前向消元）
    for (int i = 1; i <= n*m; i++) {
        if (fabs(mp[i][m]) <= eps)
            continue; // 跳过零行
        
        // 消去下方m行内的元素
        for (int j = i + 1; j <= min(i + m, n*m); j++) {
            double ratio = mp[j][m - j + i] / mp[i][m];
            
            // 更新系数矩阵
            for (int k = m; k <= 2*m; k++)
                mp[j][k - j + i] -= ratio * mp[i][k];
            
            // 更新解向量
            ans[j] -= ans[i] * ratio;
        }
    }
    
    // 回代求解
    for (int i = n*m; i >= 1; i--) {
        for (int j = i + 1; j <= min(i + m, n*m); j++)
            ans[i] -= mp[i][m + j - i] * ans[j];
        
        if (fabs(mp[i][m]) > eps)
            ans[i] /= mp[i][m]; // 归一化
        else
            ans[i] = 0;         // 零行处理
    }
    
    // 输出结果并校验概率总和
    p = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (s[i][j] == 'T')
                printf("%.10lf\n", ans[(i-1)*m + j]), p += ans[(i-1)*m + j];
    
    // 概率总和校验
    assert(fabs(1 - p) <= eps);
    
    return 0;
}
```

---

## 作者：XiaoJuRuoUP (赞：3)

[~~不会更好的阅读体验~~](https://www.cnblogs.com/XiaoJuRuoUP/p/-/lnsyoj4079_luoguP6899)
## 题意
一个包括空地、障碍和空洞的 $H\times W$ 地图，从第一列随机选取空地作为起始位置，到达某个空洞后停止运动。给定向上下左右移动的概率比 $p_u:p_d:p_l:p_r$，求在每个空洞停止运动的概率为多少。
## sol
由于每次到达空洞后即会停止运动，因此到达空洞的期望次数即为到达每个空洞的概率。记 $f_{i,j}$ 表示到达 $(i,j)$ 的次数的期望，就可以很容易的推出转移方程：
$$f_{i,j}= f_{i+1,j}\cdot \frac{p_u}{psum} + f_{i-1,j}\cdot \frac{p_d}{psum} + f_{i,j+1}\cdot \frac{p_l}{psum} + f_{i,j -1}\cdot\frac{p_r}{psum} + [i=1]\cdot \frac{1}{stcnt}$$
（$stcnt$ 为第一行空地的数量，$psum$ 为可以转移到的方向的概率比之和）

需要注意一点：当出现某一列全为 $0$ 无法消元时，对答案并无影响，因此 `continue` 即可。

这样，我们只需要对列出的方程进行高斯消元即可解出答案……吗？

我们发现，这样一来，我们所求的未知数数量为 $HW$ 个，而高斯消元的复杂度是 $O(n^3)$ 的，因此时间复杂度就达到了 $O((HW)^3)$，空间复杂度达到了 $O((HW)^2)$，无法接受。

不过，我们的增广矩阵中，最多只会在对角线向左和向右 $W$ 格的位置出现非零数字，这是一个非常经典的 `band-matrix` 优化。在消元和回代时，只向后修改 $W$ 列即可，即使是矩阵中出现 $0$，需要换行时，也最多只需修改 $(2W)\times W$ 的矩阵即可，而不需要修改整个矩阵；而且，我们可以为每一个可能出现非零数字的位置记录一个偏移量，这样时间复杂度就优化到了 $O(HW^3)$，空间复杂度优化到了 $O(HW^2)$。

注意：如果 $\color{red}{\text{WA}}$ on #9, Line 13，说明是被卡精度了；如果结果输出了  `-nan`，请改变写法，不要直接使用 $im+j$ 作为编号存储，而是对每一个非障碍方格进行编号。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 25, M = 10005;
const long double eps = 1e-10;

int n, m, p[4];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int pfrom[4] = {1, 0, 3, 2};
long double coeff[N * M][N * 4];
long double ans[N * M];
int psum[N * M];
int id[M][N];
char g[M][N];
int idx;

long double &c(int a, int b){
    return coeff[a][b - max(0, a - 2 * m)];
}

void gauss(){
    for (int i = 1; i <= idx; i ++ ){
        if (abs(c(i, i)) <= eps) continue;
        int ed = min(idx, i + 2 * m);
        ans[i] /= c(i, i);
        for (int j = ed; j >= i; j -- )
            c(i, j) /= c(i, i);
        for (int j = i + 1; j <= min(i + m, idx); j ++ ){ 
            
            ans[j] -= c(j, i) * ans[i];
            for (int k = ed; k >= i; k -- ) c(j, k) -= c(j, i) * c(i, k);
        }


    }

    for (int i = idx; i; i -- ){
        for (int j = i + 1; j <= min(idx, i + 2 * m); j ++ )
            ans[i] -= c(i, j) * ans[j];
    }
}

int main(){
    scanf("%d%d", &m, &n);
    for (int i = 0; i < 4; i ++ ) scanf("%d", &p[i]);
    for (int i = 0; i < n; i ++ ) scanf("%s", g[i]);

    int stcnt = 0;
    for (int i = 0; i < m; i ++ ) stcnt += (g[0][i] == '.');

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ ){
            id[i][j] = (g[i][j] == 'X') ? -1 : ++ idx;
            if (id[i][j] == -1) continue;
            for (int u = 0; u < 4; u ++ ) {
                int sx = i + dx[u], sy = j + dy[u];
                if (sx < 0 || sx >= n || sy < 0 || sy >= m || g[sx][sy] == 'X') continue;
                psum[id[i][j]] += p[u];
            }
        }

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ ){
            if (id[i][j] == -1) continue;
            if (!i && g[i][j] == '.') ans[id[i][j]] = (long double) 1 / stcnt;
            for (int u = 0; u < 4; u ++ ){
                int sx = i + dx[u], sy = j + dy[u];
                int px = pfrom[u];
                if (sx < 0 || sx >= n || sy < 0 || sy >= m || g[sx][sy] == 'X' || g[sx][sy] == 'T') continue;
                int sid = id[sx][sy];
                c(id[i][j], sid) = (long double) -p[px] / psum[sid];
            }
            c(id[i][j], id[i][j]) = 1;
        }

    gauss();

    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < m; j ++ )
            if (g[i][j] == 'T') printf("%.9Lf\n", ans[id[i][j]]);

    return 0;
}
```

---

## 作者：RuSun (赞：2)

经典的随机游走模型。

$f _ i$ 表示 $i$ 可以分给周围的点的概率，显然可以从周围四个点转移，以及第一行的初始概率。按照从上到下从左到右的顺序编号，可以保证方程为一个带长度不超过 $w$ 的带状矩阵，每次在范围内消元即可保证时间复杂度，将矩阵映射到一个集中的空间可以保证空间复杂度。

更多带状矩阵的题目可以看[蒟蒻的博客](https://rusunoi.github.io/tags/带状矩阵高斯消元/)

注意到一个坑点，例如数据：

```
3 2 25 25 25 25
.XX
.XT
```

此时方程有：
$$
\begin {cases}
f _ 1 = f _ 2 + 1 \\\\
f _ 2 = f _ 1 \\\\
f _ 3 = 0
\end {cases}
$$
我们需要的答案为 $f _ 3$ ，显然可以直接得到答案，但是发现 $f _ 1, f _ 2$ 消元时是无解的，如果没有处理好，我们会得到 $nan$ 的答案。如果出现这样的情况，在图上的体现就是一个点在第一行，和若干的点形成一个连通块，但是这个连通块没有洞，这对答案是没有影响的，所以一旦遇到直接 ``continue`` 。


```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
template <class Type>
void read(Type &x)
{
    char c;
    bool flag = false;
    while ((c = getchar()) < '0' || c > '9')
        c == '-' && (flag = true);
    x = c - '0';
    while ((c = getchar()) >= '0' && c <= '9')
        x = (x << 3) + (x << 1) + c - '0';
    flag && (x = ~x + 1);
}
template <class Type>
void write(Type x)
{
    x < 0 && (putchar('-'), x = ~x + 1);
    x > 9 && (write(x / 10), 0);
    putchar(x % 10 + '0');
}
const double eps = 1e-10;
const int N = 1e4 + 10, M = 30, dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
bool q[N][M];
int n, m, tot, mv[N * M], id[N][M];
double tA[N * M][M << 1], B[N * M];
double &A (int x, int y)
{
    return tA[x][y - mv[x]];
}
bool inside (int a, int b)
{
    return a >= 0 && b >= 0 && a < n && b < m;
}
void Gauss ()
{
    for (int k = 0; k < tot; k++)
    {
        if (fabs(A(k, k)) < eps)
            continue;
        int t = min(tot - 1, k + m);
        B[k] /= A(k, k);
        for (int i = t; i >= k; i--)
            A(k, i) /= A(k, k);
        for (int i = k + 1; i <= t; i++)
        {
            B[i] -= B[k] * A(i, k);
            for (int j = t; j >= k; j--)
                A(i, j) -= A(k, j) * A(i, k);
        }
    }
    for (int i = tot - 1; ~i; i--)
        for (int j = i + 1; j <= min(tot - 1, i + m); j++)
            B[i] -= A(i, j) * B[j];
}
int main ()
{
    read(m), read(n);
    int p[4];
    for (int i = 0; i < 4; i++)
        read(p[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            char c = getchar();
            while (c != 'X' && c != 'T' && c != '.')
                c = getchar();
            id[i][j] = c != 'X' ? tot++ : -1;
            c == 'T' && (q[i][j] = true);
        }
    for (int i = 0; i < tot; i++)
        mv[i] = max(0, i - m);
    double st = 0;
    for (int i = 0; i < m; i++)
        st += id[0][i] != -1;
    st = 1 / st;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (id[i][j] == -1)
                continue;
            int &t = id[i][j];
            !i && (B[t] = st);
            A(t, t) = 1;
            if (q[i][j])
                continue;
            int ps = 100;
            for (int k = 0; k < 4; k++)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (!inside(nx, ny) || id[nx][ny] == -1)
                    ps -= p[k];
            }
            for (int k = 0; k < 4; k++)
            {
                int nx = i + dx[k], ny = j + dy[k];
                if (inside(nx, ny) && ~id[nx][ny])
                    A(id[nx][ny], t) = -(double)p[k] / ps;
            }
        }
    Gauss();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            q[i][j] && printf("%.9lf\n", B[id[i][j]]);
    return 0;
}
```

---

## 作者：FangZeLi (赞：1)

**upd：增加了具体的方程和关于优化消元过程的具体描述**

## Link

[[ICPC2014 WF]Pachinko]([P6899 [ICPC2014 WF\]Pachinko - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P6899))

## Solution

首先这题的模型其实非常经典，就是一个网格图上随机游走。那么我们的算法也很明确，就是高斯消元。方程就是当前点的概率等于从四周来的概率之和，然后在第一列加一下初始的概率。
$$
f_{i,j} = uf_{i-1,j}+lf_{i,j-1}+df_{i+1,j}+rf_{i,j+1}+[初始概率]
$$
但是看到这个数据范围，你崩溃了：高斯消元根本不可能跑过去。

但是其实你的心中应该也有策略了：我们必然要对消元过程进行优化。

注意到每个方程未知数的数量都非常少，因此这个矩阵实际上相当稀疏，所以直接优化稀疏矩阵消元的过程，由于这个矩阵有值的区域是一个带状的东西，直接逐行消去即可。

具体来说，我们将格子 $(i, j)$ 编号为 $i \times w + j$，这样的话，我们考虑对每个格子列出的方程。由于和一个格子相关的仅有相邻的格子，相邻的格子只有四个。其中，编号相差最大的格子正是上方的和下方的，相差了一个 $w$ ，因此，我们在选定主元之后开始消元的过程中只需要考虑上面 $w$ 行与下面 $w$ 行（因为其他的行该元的系数一定是零），这样的话消元的复杂度就被优化到了 $\mathcal{O}(w^2h)$，就可以通过了。

## Code

本来想贴代码的，但是神M_sea的写的比我的好看太多了[捂脸]。

方法也差不多，~~出于保护大家的眼睛~~，大家还是看他的比较好。

## Inspiration

我认为这题总体上说是有迹可循的一道题，关键就是在稀疏矩阵消元的一步可能会比较依赖于经验。

关键结论：

1. 网格图的此类期望问题往往可以用高斯消元解决。
2. 高斯消元的复杂度不可接受时不妨利用矩阵的特殊性质对消元算法进行优化。

---

## 作者：Your_Name (赞：0)

### 题解
设 $f_{i,j}$ 表示球到这个点的概率。

设 $g_{i,j}$ 为 $(i,j)$ 走到周围的总概率，即为四个方向不是障碍点的概率之和。

设 $cnt$ 为第一行的空格总数。

显然有以下转移：
$$
f_{i,j}=\frac{p_d}{g_{i-1,j}}f_{i-1,j}+\frac{p_u}{g_{i+1,j}}f_{i+1,j}+\frac{p_r}{g_{i,j-1}}f_{i,j-1}+\frac{p_l}{g_{i,j+1}}f_{i,j+1}+[i=1]\frac{1}{cnt}
$$

当然前提是每个点不为障碍或洞。

直接消肯定是 $O((nm)^3)$，绝对过不了。发现这个矩阵是带状矩阵，即第 $i$ 行只有第 $[i-m,i+m]$ 列有值，第 $j$ 列只有 $[j-m,j+m]$ 行有值。

考虑每次只消最近的 $m$ 行 $m$ 列，就能使复杂度变为 $O(nm^3)$ 可以通过。

但是时间复杂度是对了，空间还是 $O((nm)^2)$，怎么办呢？

一种简单的做法是直接开 $nm$ 个 `unordered_map`，但这道题会被卡。于是我们继续找性质，发现我们遍历到的所有点 $a_{i,j}$，都满足 $abs(i-j)\le m$。于是我们直接把 $a_{i,j}$ 映射到 $a_{i,j-i+m}$ 即可。空间复杂度降为 $O(nm^2)$，可以通过。当然要记得最后一列的值还要单独开个数组记录。
### AC_Code
朴素的板子跑得还挺快的。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, M = 1e4 + 10;
int n, m, fx[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}, cnt, d;
char c[M][21];
unordered_map<int, int> ma;
double a[N][50], ans[N], p[4], eps = 1e-10, sum[N], ff[4];
int get(int x, int y){return (x - 1) * m + y;}
int main(){
	scanf("%d%d%lf%lf", &m, &n, &p[0], &p[1], &p[2], &p[3]);
	d = n * m;
	p[0] /= 100.0, p[1] /= 100.0, p[2] /= 100.0, p[3] /= 100.0;
	ff[0] = p[1], ff[1] = p[0], ff[2] = p[3], ff[3] = p[2];
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			scanf("%c", c[i][j]);
			if(i == 1)if(c[i][j] == '.')cnt ++;
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			if(i == 1 && c[i][j] == '.')ans[get(i, j)]= 1.0 / (1.0 * cnt);//第一行特判
			if(c[i][j] != 'X'){
				a[get(i, j)][m] = 1;//自己的系数
				for(int k = 0; k < 4; k ++){
					int xx = i + fx[k][0], yy = j + fx[k][1];
					if(xx < 1 || xx > n || yy < 1 || yy > m || c[xx][yy] == 'X')continue;
					sum[get(i, j)] += ff[k];//能走到的概率和
				}
			}
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			if(c[i][j] != 'X'){
				for(int k = 0; k < 4; k ++){
					int xx = i + fx[k][0], yy = j + fx[k][1];
					if(xx < 1 || xx > n || yy < 1 || yy > m || c[xx][yy] == 'X' || c[xx][yy] == 'T')continue;
					a[get(i, j)][get(xx, yy) - get(i, j) + m] -= p[k] / sum[get(xx, yy)];//如上文转移
				}
			}
		}
	}
	for(int i = 1; i <= d; i ++){
		int t = i;
		for(int j = i + 1; j <= min(d, i + m); j ++)if(fabs(a[j][i - j + m]) > fabs(a[t][i - t + m]))t = j;//找最大
		if(fabs(a[t][i - t + m]) < eps)continue;//优化
		for(int j = i; j <= min(d, i + m); j ++)swap(a[i][j - i + m], a[t][j - t + m]);//换元
		swap(ans[i], ans[t]);
		ans[i] /= a[i][m];//最后一列单独处理
		for(int j = min(d, i + m); j >= i; j --)a[i][j - i + m] /= a[i][m];//归一
		for(int j = i + 1; j <= min(d, i + m); j ++){
			ans[j] -= a[j][i - j + m] * ans[i];
			for(int k = min(d, i + m); k >= i; k --)a[j][k - j + m] -= a[j][i - j + m] * a[i][k - i + m];//消
		}
	}
	for(int i = d; i > 1; i --)for(int j = i - 1; j >= max(1, i - m); j --)ans[j] -= a[j][i - j + m] * ans[i];//带入求值
	for(int i = 1; i <= n; i ++)for(int j = 1; j <= m; j ++)if(c[i][j] == 'T')printf("%.9lf\n", ans[get(i, j)]);
	return 0;
}
```
_完结撒花。_

---

