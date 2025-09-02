# 「LCOI2022」 Cow Dance

## 题目背景

Bessie 带着他的奶牛姐妹们来跳舞了。

她们已经规划好了跳舞的步骤，但是为了更加美观，她们需要知道其中一些头奶牛在某时的平均位置，已达到更完美的表演效果。

不幸的是，由于 Bessie 的姐妹太多了，最多会有 $8\times 10^4$ 只奶牛同时来跳舞。她没有什么方便且快速的方法算这些平均位置，所以向你求助。

## 题目描述

Bessie 和她的姐妹们已经排好了位置，第 $i$ 头奶牛的坐标为 $(x_i,y_i)$。其中，$x_i$ 是 $x$ 轴坐标，$y_i$ 是 $y$ 轴坐标。

她们的舞蹈队形会有这几种变换方式：
1. 移动：$x$ 到 $y$ 号奶牛的 $x_i\to x_i+a$，$y_i\to y_i+b$。
1. 旋转：$x$ 到 $y$ 号奶牛以 $(a,b)$ 为旋转中心顺时针旋转 $g°$。
1. 散开: $x$ 到 $y$ 号奶牛以 $(a,b)$ 为中心散开为 $\dfrac{p}{q}$ 倍。即设之前奶牛坐标为 $A$，散开后坐标为 $B$，$(a,b)$ 为 $G$，$\overrightarrow{GB}=\dfrac{p}{q}\overrightarrow{GA}$。

Bessie 想知道：对于 $x$ 到 $y$ 号奶牛，他们的平均位置 $(\frac{\sum\limits^y_{i=x}x_i}{y-x+1},\frac{\sum\limits^y_{i=x}y_i}{y-x+1})$。

舞会就要开始了，所以她只能给你 $\texttt{1s}$ 的时间。

## 说明/提示

【样例解释】
![](https://cdn.luogu.com.cn/upload/image_hosting/3jt6apa4.png)

$0$ 为初始情况。$1$ 为进行样例中 `1 1 2 1 -2` 操作后结果。$2$ 为进行样例中 `2 1 3 2 0 270` 操作后结果。$3$ 为进行样例中 `3 1 2 2 2 2 1` 操作后结果。

【数据范围与约定】

保证运算时所有数的绝对值小于或等于 $10^{15}$。

|subtask|特殊限制|分数|
|:-:|:-:|:-:|
|$1$|$1\le n,m\le10^3$|$8$|
|$2$|只有旋转操作且都按奶牛为旋转中心|$18$|
|$3$|只有散开操作且都按奶牛为位似中心|$18$|
|$4$|没有旋转和散开操作|$8$|
|$5$|对于所有操作和询问 $x=y$|$18$|
|$6$|旋转中心和散开中心都是奶牛|$8$|
|$7$|$1\le n,m\le 8\times10^4$|$10$|
|$8$|没有特殊限制|$12$|

对于 $100\%$ 的数据，$1\le n,m\le3\times10^5$，$1\le x\le y\le n$，$-32768\le a,b<32768$，$0< \dfrac{p}{q}\le 233333$，$0\le g\le359$，初始坐标限制同 $a,b$。

### **注：**
- **请注意常数因子优化。**
- **此题输入输出量较大，建议使用 `scanf` 和 `printf`。**

## 样例 #1

### 输入

```
3 7
1 1
1 3
3 1
1 1 2 1 -2
4 1 3
2 1 3 2 0 270
4 1 2
3 1 2 2 2 2 1
4 1 3
4 3 3```

### 输出

```
2.3333333333 0.3333333333
2.0000000000 0.0000000000
1.6666666667 -1.0000000000
1.0000000000 1.0000000000```

# 题解

## 作者：STA_Morlin (赞：14)

考虑用矩阵描述区间操作，线段树维护。

对于点 $(x,y)$，表为行向量 $\begin{bmatrix}x&y\end{bmatrix}$，则：
- 平移：$\begin{bmatrix}x'&y'\end{bmatrix}=\begin{bmatrix}x&y\end{bmatrix}+\begin{bmatrix}a&b\end{bmatrix}$。
- 旋转：不妨设关于 $(0,0)$ 旋转（不满足形式可以先平移过去），$\begin{bmatrix}x'&y'\end{bmatrix}=\begin{bmatrix}x&y\end{bmatrix}\begin{bmatrix}\cos g^{\circ}&\sin g^{\circ}\\-\sin g^{\circ}&\cos g^{\circ}\end{bmatrix}$。
- 位似：不妨设关于 $(0,0)$ 位似（不满足形式可以先平移过去），$\begin{bmatrix}x'&y'\end{bmatrix}=\begin{bmatrix}x&y\end{bmatrix}\begin{bmatrix}0&\frac pq\\\frac pq&0\end{bmatrix}$。

区间查询只需要求区间的向量和即可，相当于区间加区间乘区间求和，这就是线段树 2。于是问题被 $\Theta(q\log n)$ 解决。

然而如果直接写常数比较大可能需要展开矩阵乘法去掉一些没用的操作这样就能过了。

---

## 作者：peterwuyihong (赞：2)

CF618E 来的 idea。

给一个[原题面](https://www.luogu.com.cn/problem/U168596)，我觉得我写的很好啊

题意：给定点集支持区间平移区间绕某个点旋转或位似，和询问区间点横坐标和纵坐标分别的平均数。

题解：

1.暴力。

2.维护区间旋转角度，区间加，线段树即可。

3.维护区间放大倍数，区间加，线段树即可。

4.维护区间平移，两个线段树即可。

5.暴力。

6.留给会正解但不完全会的选手。

7.留给常数大选手。

8.注意到区间旋转位似都可以拿矩阵维护，就相当于矩阵加和矩阵乘，或者用虚数维护。

对于平移操作，就是加上一个虚数。

对于旋转和位似操作，可以先把这个中心移到原点，再乘上一个虚数即可，维护区间加，区间乘即可。

复杂度 $O(n\log n)$。

---

## 作者：Misophiliac (赞：1)

用矩阵卡过去了，来水一篇题解。

之前做过一道类似的题（[P7453](https://www.luogu.com.cn/problem/P7453)），导致看到这题第一眼就是线段树维护矩乘，于是开始——

## 推式子

因为有常数操作，用
$$
\begin{bmatrix}
x & 0 & 0\\
y & 0 & 0\\
1 & 0 & 0
\end{bmatrix}
$$
表示点 $(x,y)$。

### 移动

容易验证有

$$
\begin{bmatrix}
x+a & 0 & 0\\
y+b & 0 & 0\\
1 & 0 & 0
\end{bmatrix}
=
\begin{bmatrix}
1 & 0 & a\\
0 & 1 & b\\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x & 0 & 0\\
y & 0 & 0\\
1 & 0 & 0
\end{bmatrix}
$$

于是可记 $P(a,b)=\begin{bmatrix}
1 & 0 & a\\
0 & 1 & b\\
0 & 0 & 1
\end{bmatrix}$。

该操作所乘矩阵为 $P(a,b)$。

### 旋转

设 $(x,y)$ 绕 $(0,0)$ 逆时针旋转 $\theta$ 弧度到 $(x',y')$，容易验证有

$$
\begin{bmatrix}
x' & 0 & 0\\
y' & 0 & 0\\
1 & 0 & 0
\end{bmatrix}
=
\begin{bmatrix}
\cos\theta & -\sin\theta & 0\\
\sin\theta & \cos\theta & 0\\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x & 0 & 0\\
y & 0 & 0\\
1 & 0 & 0
\end{bmatrix}
$$

于是可记 $R(\theta)=\begin{bmatrix}
\cos\theta & -\sin\theta & 0\\
\sin\theta & \cos\theta & 0\\
0 & 0 & 1
\end{bmatrix}$。

注意题目中是绕 $(a,b)$，**顺时针**旋转 $g$ **度**，于是可以先将点 $(x,y)$ 平移 $(-a,-b)$，旋转 $-\pi g/180$ 弧度，再平移 $(a,b)$。

该操作所乘矩阵为 $P(a,b)R(-\pi g/180)P(-a,-b)$。

### 散开

容易验证有

$$
\begin{bmatrix}
kx & 0 & 0\\
ky & 0 & 0\\
1 & 0 & 0
\end{bmatrix}
=
\begin{bmatrix}
k & 0 & 0\\
0 & k & 0\\
0 & 0 & 1
\end{bmatrix}
\begin{bmatrix}
x & 0 & 0\\
y & 0 & 0\\
1 & 0 & 0
\end{bmatrix}
$$

于是可记 $S(k)=\begin{bmatrix}
k & 0 & 0\\
0 & k & 0\\
0 & 0 & 1
\end{bmatrix}$。

与旋转同理，先平移，再位似，最后平移回来。

该操作所乘矩阵为 $P(a,b)S(p/q)P(-a,-b)$。

## 卡常

从上面的分析中，我们很容易能写出 $O(n\log n)$ 带 27 倍常数的代码，并与快读配合得到可观的 [36 分](https://www.luogu.com.cn/record/166465302)。不惜将 3*3 矩阵写成九个变量后能得到显著的提升：[92 分](https://www.luogu.com.cn/record/166473320)。

众所周知，C++20 快于 C++14，于是我们愉快地 [AC](https://www.luogu.com.cn/record/166485356) 了这道题。

## 代码

```c
#include <stdio.h>
#include <math.h>
#define B 1 << 20
char buf[B], *p1 = buf, *p2 = buf;
#define g() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, B, stdin), p1 == p2) ? EOF : *p1++)
int rd() {
    int x = 0, f = 0; char c = g();
    for (; c < '0' || c > '9'; c = g())
        f ^= c == '-';
    for (; c >= '0' && c <= '9'; c = g())
        x = (x << 3) + (x << 1) + (c ^ '0');
    return f ? -x : x;
}
#define K 3
struct mat {
    double a, b, c, d, e, f, g, h, i;
    mat(double _a, double _b, double _c, double _d, double _e, double _f, double _g, double _h, double _i) {
        a = _a, b = _b, c = _c, d = _d, e = _e, f = _f, g = _g, h = _h, i = _i;
    }
    mat(double x = 1) {
        a = e = i = x, b = c = d = f = g = h = 0;
    }
    mat operator +(mat x) {
        return (mat){ a + x.a, b + x.b, c + x.c, d + x.d, e + x.e, f + x.f, g + x.g, h + x.h, i + x.i };
    }
    mat operator *(mat x) {
        return (mat){
            a * x.a + b * x.d + c * x.g, a * x.b + b * x.e + c * x.h, a * x.c + b * x.f + c * x.i,
            d * x.a + e * x.d + f * x.g, d * x.b + e * x.e + f * x.h, d * x.c + e * x.f + f * x.i,
            g * x.a + h * x.d + i * x.g, g * x.b + h * x.e + i * x.h, g * x.c + h * x.f + i * x.i
        };
    }
};
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
mat f[1<<20], g[1<<20];
void bd(int p, int l, int r) {
    if (l == r) f[p] = mat(0), f[p].a = rd(), f[p].d = rd(), f[p].g = 1, g[p] = mat();
    else bd(ls, l, mid), bd(rs, mid + 1, r), f[p] = f[ls] + f[rs];
}
mat t;
void mod(int p, int l, int r, int x, int y) {
    if (x <= l && y >= r) { g[p] = t * g[p], f[p] = t * f[p]; return; }
    f[ls] = g[p] * f[ls], g[ls] = g[p] * g[ls],
    f[rs] = g[p] * f[rs], g[rs] = g[p] * g[rs],
    g[p] = mat();
    if (x <= mid) mod(ls, l, mid, x, y);
    if (y >= mid + 1) mod(rs, mid + 1, r, x, y);
    f[p] = f[ls] + f[rs];
}
mat qry(int p, int l, int r, int x, int y) {
    if (x <= l && y >= r) return f[p];
    f[ls] = g[p] * f[ls], g[ls] = g[p] * g[ls],
    f[rs] = g[p] * f[rs], g[rs] = g[p] * g[rs],
    g[p] = mat();
    if (y <= mid) return qry(ls, l, mid, x, y);
    if (x >= mid + 1) return qry(rs, mid + 1, r, x, y);
    return qry(ls, l, mid, x, y) + qry(rs, mid + 1, r, x, y);
}
int main() {
    int n = rd(), m = rd(); bd(1, 1, n);
    for (int o, x, y; m--; ) {
        o = rd(), x = rd(), y = rd(), t = mat();
        if (o < 4) {
            t.c = rd(), t.f = rd();
            if (o > 1) {
                mat r, s;
                r.c = -t.c, r.f = -t.f;
                if (o == 2) {
                    double g = M_PI * rd() / 180;
                    s.a = s.e = cos(g), s.d = -(s.b = sin(g));
                }
                if (o == 3) {
                    double k = (double)rd() / rd();
                    s.a = s.e = k;
                }
                t = t * s * r;
            }
            mod(1, 1, n, x, y);
        }
        else t = qry(1, 1, n, x, y),
            printf("%.6lf %.6lf\n", t.a / (y - x + 1), t.d / (y - x + 1));
    }
    return 0;
}
```

---

## 作者：kbtyyds (赞：1)

# P8105 题解

[2022/12/30]：update，修复了几处笔误。

建议在[博客](https://www.luogu.com.cn/blog/453059/solution-p8105)里食用。

[题目链接](https://www.luogu.com.cn/problem/P8105)

## 1.题目简述

维护 $n$ 个坐标 $(x_i,y_i)$，支持4种操作：

1. 移动：$x$ 到 $y$ 号奶牛的 $x_i\to x_i+a$，$y_i\to y_i+b$。
1. 旋转：$x$ 到 $y$ 号奶牛以 $(a,b)$ 为旋转中心顺时针旋转 $g°$。
1. 散开：$x$ 到 $y$ 号奶牛以 $(a,b)$ 为中心散开为 $\dfrac{p}{q}$ 倍。即设之前奶牛坐标为 $A$，散开后坐标为 $B$，$(a,b)$ 为 $G$，$\overrightarrow{GB}=\dfrac{p}{q}\overrightarrow{GA}$。
1. 查询：求 $x$ 到 $y$ 号奶牛的平均位置 $(\frac{\sum\limits^y_{i=x}x_i}{y-x+1},\frac{\sum\limits^y_{i=x}y_i}{y-x+1})$ 。

## 2.分析

很明显可以用线段树维护，于是我们一个一个操作来分析（记 $l,r$ 分别为区间的两端）：

### 操作4

对于操作 4 ，就很直接地说明我们要维护区间和，即 $sx=\sum\limits_{i=l}^rx_i$，$sy=\sum\limits_{i=l}^ry_i$。

### 操作1

分析它的实质：区间加，即 $(x,y)\leftarrow(x+a,y+b)$。

### 操作2

这时我们需要用到[旋转公式](https://www.luogu.com.cn/paste/313pgbdj)：

若点 $(x,y)$ 绕点 $(a,b)$ 顺时针旋转 $\alpha$ 角度，则新的点的坐标为：

$$\begin{aligned}&((x-a)\cos\alpha+(y-b)\sin\alpha+a,-(x-a)\sin\alpha+(y-b)\cos\alpha+b)\\\text{即}&(\cos\alpha\cdot x+\sin\alpha\cdot y+a-a\cos\alpha-b\sin\alpha,-\sin\alpha\cdot x+\cos\alpha\cdot x+b+a\sin\alpha-b\cos\alpha)\end{aligned}$$

所以它的本质为 $(x,y)\leftarrow(\cos g\degree\cdot x+\sin g\degree\cdot y+a-a\cos g\degree-b\sin g\degree,-\sin g\degree\cdot x+\cos g\degree\cdot y+b+a\sin g\degree-b\cos g\degree)$。

### 操作3

题目用向量解释得很清楚，那我们再仔细推一推：

$$\begin{aligned}&\because G(a,b),A(x,y)\\&\therefore\overrightarrow{GA}=(x-a,y-b)\\&\therefore\overrightarrow{GB}=\frac p q\overrightarrow{GA}=(\frac p q(x-a),\frac p q(y-b))\\&\because G(a,b)\\&\therefore B(\frac p q(x-a)+a,\frac p q(y-b)+b)\end{aligned}$$

将其展开，可以知道它的本质为 $(x,y)\leftarrow(\dfrac p q\cdot x+a(1-\dfrac p q),\dfrac p q\cdot y+b(1-\dfrac p q))$。

### 总结

1. 求值只需维护区间和。

1. 修改我们可以将操作 1, 2, 3 看成一个操作，即：对于实数 $A,B,C,D$ ，将 $(x,y)$ 改为 $(Ax+By+C,-Bx+Ay+D)$

具体来说：

操作 1 ：

$$\begin{aligned}&A=1\\&B=0\\&C=a\\&D=b\end{aligned}$$

操作 2 ：

$$\begin{aligned}&A=\sin g\degree\\&B=\cos g\degree\\&C=a-a\cos g\degree-b\sin g\degree\\&D=b+a\sin g\degree-b\cos g\degree\end{aligned}$$

操作 3 ：

$$\begin{aligned}&A=\frac p q\\&B=0\\&C=a(1-\frac p q)\\&D=b(1-\frac p q)\end{aligned}$$

## 3.推导&实现

根据 2 中的总结，我们知道了要维护的懒标记，即：

```cpp
double sumx[S<<2],sumy[S<<2];
// 区间和
double taga[S<<2],tagb[S<<2],tagc[S<<2],tagd[S<<2];
// 懒标记
```

那么我们只要在打懒标记时再考虑以下两点（核心）：

1. 懒标记对区间和的影响：

记 $x_i^\prime$ 为修改后的 $x_i$，$y_i^\prime$ 为修改后的 $y_i$，那么：

$$\begin{aligned}\sum_{i=l}^rx_i^\prime&=\sum_{i=l}^r(Ax_i+By_i+C)\\&=\sum_{i=l}^r(Ax_i)+\sum_{i=l}^r(By_i)+\sum_{i=l}^rC\\&=A\sum_{i=l}^rx_i+B\sum_{i=l}^ry_i+C(r-l+1)\\&=A\cdot sx+B\cdot sy+C(r-l+1)\end{aligned}$$

$$\begin{aligned}\sum_{i=l}^ry_i^\prime&=\sum_{i=l}^r(-Bx_i+Ay_i+D)\\&=\sum_{i=l}^r(-Bx_i)+\sum_{i=l}^r(Ay_i)+\sum_{i=l}^rD\\&=-B\sum_{i=l}^rx_i+A\sum_{i=l}^ry_i+D(r-l+1)\\&=-B\cdot sx+A\cdot sy+D(r-l+1)\end{aligned}$$

代码实现如下：

```cpp
inline void pushone(int o,int l,int r,double a,double b,double c,double d)//打懒标记操作
{
    //其中a,b,c,d分别对应4个懒标记
    int len=r-l+1;
    double sx=sumx[o],sy=sumy[o];
    sumx[o]=a*sx+b*sy+len*c;
    sumy[o]=a*sy-b*sx+len*d;
}
```

2. 懒标记对懒标记的影响（懒标记叠加）：

考虑对一段区间打懒标记。记区间的原懒标记分别为 $A_1,B_1,C_1,D_1$，新打的懒标记分别为 $A_2,B_2,C_2,D_2$，叠加后的懒标记分别为 $A,B,C,D$，$x^\prime$ 为修改一次后的 $x$。$x^{\prime\prime}$ 为修改两次后的 $x$，对于 $y$ 同理，那么：

$$\begin{aligned}&x^\prime=A_1x+B_1y+C_1\\&y^\prime=-B_1x+A_1y+D_1\end{aligned}$$

$$\begin{aligned}&x^{\prime\prime}=A_2x^\prime+B_2y^\prime+C_2=Ax+By+C\\&y^{\prime\prime}=-B_2x^\prime+A_2y^\prime+D_2=-Bx+Ay+D\end{aligned}$$

代入，展开：

$$\begin{aligned}x^{\prime\prime}&=A_2(A_1x+B_1y+C_1)+B_2(-B_1x+A_1y+D_1)+C_2\\&=(A_1A_2-B_1B_2)x+(A_1B_2+A_2B_1)y+(A_2C_1+B_2D_1+C_2)\\y^{\prime\prime}&=-B_2(A_1x+B_1y+C_1)+A_2(-B_1x+A_1y+D_1)+D_2\\&=-(A_1B_2+A_2B_1)x+(A_1A_2-B_1B_2)y+(A_2D_1-B_2C_1+D_2)\end{aligned}$$

与懒标记的格式对比，我们可以得出：

$$\begin{aligned}&A=A_1A_2-B_1B_2\\&B=A_1B_2+A_2B_1\\&C=A_2C_1+B_2D_1+C_2\\&D=A_2D_1-B_2C_1+D_2\end{aligned}$$

代码如下（已包含懒标记对区间和的影响）：

```cpp
inline void pushone(int o,int l,int r,double a,double b,double c,double d)
{
    //其中a,b,c,d分别对应4个懒标记
    int len=r-l+1;
    double sx=sumx[o],sy=sumy[o];
    double A=taga[o],B=tagb[o],C=tagc[o],D=tagd[o];
    //下面直接运用结论
    sumx[o]=a*sx+b*sy+len*c;
    sumy[o]=a*sy-b*sx+len*d;
    taga[o]=a*A-b*B;
    tagb[o]=a*B+b*A;
    tagc[o]=a*C+b*D+c;
    tagd[o]=a*D-b*C+d;
}
```

以及最终的修改代码：

```cpp
inline void pushdown(int o,int l,int r)
{//下放懒标记
    int mid=(l+r)>>1;
    pushone(ls,l,mid,taga[o],tagb[o],tagc[o],tagd[o]);
    pushone(rs,mid+1,r,taga[o],tagb[o],tagc[o],tagd[o]);
    taga[o]=1,tagb[o]=tagc[o]=tagd[o]=0;
}
inline void move(int o,int l,int r,int ql,int qr,double x,double y)
{//移动
    if(ql<=l&&r<=qr) {pushone(o,l,r,1,0,x,y);return;}
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(ql<=mid) move(ls,l,mid,ql,qr,x,y);
    if(qr>mid) move(rs,mid+1,r,ql,qr,x,y);
    pushup(o);
}
inline void rotate(int o,int l,int r,int ql,int qr,double x,double y,double g)
{//////////旋转
    if(ql<=l&&r<=qr)
    {
        double sing=sin(g),cosg=cos(g);
        pushone(o,l,r,cosg,sing,x-x*cosg-y*sing,y+x*sing-y*cosg);
        return;
    }
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(ql<=mid) rotate(ls,l,mid,ql,qr,x,y,g);
    if(qr>mid) rotate(rs,mid+1,r,ql,qr,x,y,g);
    pushup(o);
}
inline void disperse(int o,int l,int r,int ql,int qr,double x,double y,double k)
{//散开
    if(ql<=l&&r<=qr) {pushone(o,l,r,k,0,x-k*x,y-k*y);return;}
    pushdown(o,l,r);
    int mid=(l+r)>>1;
    if(ql<=mid) disperse(ls,l,mid,ql,qr,x,y,k);
    if(qr>mid) disperse(rs,mid+1,r,ql,qr,x,y,k);
    pushup(o);
}
```

## 4.细节&代码

注意旋转操作给出的是角度，而 `cmath` 库里的三角函数是弧度制，因此要把角度转化为弧度（具体看代码）。

以及初始懒标记的设置。由于一开始 $x_i^\prime=x_i$，$y_i^\prime=y_i$，于是 $A=1,B=C=D=0$。

因为篇幅有限（况且已经把主要的函数给出了），所以完整代码放到[云剪切板](https://www.luogu.com.cn/paste/9255iz2f)。

---

## 作者：little_cindy (赞：1)

## 思路
这个题是对于subtask进行处理（有的不能同时得分，例如 subtask $2$ 和 subtask $3$）。
### subtask 1
暴力就好了。
### subtask 2
维护区间旋转角度，区间和，线段树即可。
### subtask 3
维护区间放大倍数，区间和，线段树即可。
### subtask 4
维护区间平移，两个线段树即可。
### subtask 5
暴力。
### subtask 6
和正解几乎一样但有缺陷的做法。
### subtask 7
留给常数较大的同正解相同的做法。
### subtask 8
注意到区间旋转位似都可以拿矩阵维护，就相当于矩阵加和矩阵乘，或者用虚数维护。

对于平移操作，就是加上一个虚数。

对于旋转和位似操作，可以先把这个中心移到原点，再乘上一个虚数即可，维护区间加，区间乘即可。

复杂度 $\Theta(n\log n)$。
## code
这一题比较良心，不用快读。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 300010
int n,m;
int x,y,a,b,p,q,opt;
const double eps=1e-6;
struct Cp{
	double a,b;
	Cp(double aa=0,double bb=0):a(aa),b(bb){}
	Cp operator+(Cp x)const{return Cp(a+x.a,b+x.b);}
	Cp operator-(Cp x)const{return Cp(a-x.a,b-x.b);}
	Cp operator*(Cp x)const{return Cp(a*x.a-b*x.b,a*x.b+x.a*b);}
	Cp operator*(int x)const{return Cp(a*x,b*x);}
	bool operator==(double x)const{return fabs(b)<eps&&fabs(a-x)<eps;}
	bool operator==(Cp x)const{return fabs(a-x.a)<eps&&fabs(b-x.b)<eps;}
	void print(){
		printf("%.6lf %.6lf\n",a,b);
	}
};
Cp e(int a){
	double r=a*3.14159265358979323846/180;
	return Cp(cos(r),-sin(r));
}
	struct sto_DX_orz{
		int l,r;
		Cp sum,mul,add;
	}tree[maxn<<2];
	void pushup(int x){
		tree[x].sum=tree[x<<1].sum+tree[x<<1|1].sum;
	}
	void pushdown(int x){
		if(!(tree[x].mul==1.0)){
			tree[x<<1].add=tree[x<<1].add*tree[x].mul;
			tree[x<<1|1].add=tree[x<<1|1].add*tree[x].mul;
			tree[x<<1].sum=tree[x<<1].sum*tree[x].mul;
			tree[x<<1|1].sum=tree[x<<1|1].sum*tree[x].mul;
			tree[x<<1].mul=tree[x<<1].mul*tree[x].mul;
			tree[x<<1|1].mul=tree[x<<1|1].mul*tree[x].mul;
			tree[x].mul=Cp(1,0);
		}
		if(!(tree[x].add==0)){
			tree[x<<1].add=tree[x<<1].add+tree[x].add;
			tree[x<<1|1].add=tree[x<<1|1].add+tree[x].add;
			tree[x<<1].sum=tree[x<<1].sum+tree[x].add*(tree[x<<1].r-tree[x<<1].l+1);
			tree[x<<1|1].sum=tree[x<<1|1].sum+tree[x].add*(tree[x<<1|1].r-tree[x<<1|1].l+1);
			tree[x].add=Cp(0,0);
		}
	}
	void build(int x,int l,int r){
		tree[x].l=l,tree[x].r=r;
		tree[x].mul=Cp(1,0);
		if(l==r){
			int a,b;
			cin>>a>>b;
			tree[x].sum=Cp((double)a,(double)b);
			return;
		}
		int mid=(l+r)>>1;
		build(x<<1,l,mid),build(x<<1|1,mid+1,r);
		pushup(x);
	}
	void change1(int x,int l,int r,Cp k){
		if(tree[x].l>=l&&tree[x].r<=r){
			tree[x].add=tree[x].add+k;
			tree[x].sum=tree[x].sum+k*(tree[x].r-tree[x].l+1);
			return;
		}
		pushdown(x);
		int mid=(tree[x].l+tree[x].r)>>1;
		if(l<=mid)change1(x<<1,l,r,k);
		if(r>mid)change1(x<<1|1,l,r,k);
		pushup(x);
	}
	void change2(int x,int l,int r,Cp k){
		if(tree[x].l>=l&&tree[x].r<=r){
			tree[x].add=tree[x].add*k;
			tree[x].mul=tree[x].mul*k;
			tree[x].sum=tree[x].sum*k;
			return;
		}
		pushdown(x);
		int mid=(tree[x].l+tree[x].r)>>1;
		if(l<=mid)change2(x<<1,l,r,k);
		if(r>mid)change2(x<<1|1,l,r,k);
		pushup(x);
	}
	Cp ask(int x,int l,int r){
		if(tree[x].l>=l&&tree[x].r<=r)return tree[x].sum;
		pushdown(x);
		int mid=(tree[x].l+tree[x].r)>>1;
		Cp val;
		if(l<=mid)val=(val+ask(x<<1,l,r));
		if(r>mid)val=(val+ask(x<<1|1,l,r));
		return val;
	}
signed main(){
  srand(time(NULL));
	scanf("%d%d",&n,&m);
	build(1,1,n);
	while(m--){
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==4){
			Cp DX=ask(1,x,y);
			DX.a/=(y-x+1),DX.b/=(y-x+1);
			DX.print();
		}else{
			scanf("%d%d",&a,&b);
			Cp A((double)a,(double)b);
			if(opt==1)change1(1,x,y,A);
			else{
				scanf("%d",&p);
				Cp E;
				if(opt==2)E=e(p);
				else scanf("%d",&q),E=Cp((double)p/q,0);
				change2(1,x,y,E);
				change1(1,x,y,A*(Cp(1,0)-E));
			}
		}
	}
}
```

---

## 作者：Link_Cut_Y (赞：0)

### 吐槽一下

这就是蓝题的难度吗？我真的爬了。

### 题目大意

给定平面上 $n$ 个点（$n \leq 3 \times 10 ^ 5$），第 $i$ 个点为 $p_i$。进行以下操作。

1. 移动：$\forall i \in [l, r]$， $x_i\to x_i+a$，$y_i\to y_i+b$。
2. 旋转：$\forall i \in [l, r]$， $p_i$ 以 $(a,b)$ 为旋转中心顺时针旋转 $g\degree$。
3. 散开: $\forall i \in [l, r]$，$p_i$ 以 $(a,b)$ 为中心散开为 $\dfrac{p}{q}$ 倍。
4. 查询：输出 $(\frac{\sum\limits^r_{i=l}x_i}{r-l+1},\frac{\sum\limits^r_{i=l}y_i}{r-l+1})$。

### 题目分析

逐个操作分析。

对于操作一，需要实现区间加的数据结构。可以考虑建两棵线段树。对 $x, y$ 分别操作。

对于操作二，我们可以先把每个点移动到原点，旋转后移动回去。移动操作可以套用操作 $1$，关键是旋转操作。

~~百度一下~~ 旋转公式：对于点 $(x, y)$ ，绕原点旋转 $\theta \degree$ 之后的坐标为：

$$(x \cos \theta + y \sin \theta , - x\sin\theta + y \cos \theta)$$

我看到这个式子是第一眼就想到矩阵的。考虑对于一个向量 $\begin{bmatrix}x & y\end{bmatrix}$，构造转移矩阵。手玩一下可以得到下面式子：

$$\begin{bmatrix}x & y\end{bmatrix} \times \begin{bmatrix}\cos \theta & \sin \theta \\ - \sin \theta & \cos \theta\end{bmatrix} = \begin{bmatrix}x_1 & y_1\end{bmatrix}$$

对于操作三，也可以将点移动到原点在进行操作。放缩即对向量 $\overrightarrow{OP}$ 数乘 $\dfrac{p}{q}$。对于矩阵运算即为（其中 $k = \dfrac{p}{q}$）：

$$\begin{bmatrix}x & y\end{bmatrix} \times \begin{bmatrix}k & 0 \\ 0 & k\end{bmatrix} = \begin{bmatrix}x_1 & y_1\end{bmatrix}$$

这样操作一也可以在矩阵中完成了。矩阵加法的式子就不放了。

好，$O(n \log n)$ 的大常数矩阵线段树出来了（[代码在这里](https://www.luogu.com.cn/paste/iiojdhn4)）

然而，但是，大常数的矩阵线段树只能够得到 $70$ 分，无法通过最后一个 $\text{substack}$。考虑对上述过程进行优化。

有一个东西叫做复平面，我们把点 $(x, y)$ 抽象成复数 $xi + y$，可以将他乘以旋转子 $R_\theta = i\sin \theta + \cos \theta$ 进行旋转。当然，移动和放缩分别搞复数加减和复数乘实数就好了。[参考文献](https://www.cnblogs.com/noluye/p/11964513.html)

~~我是不会告诉你我把 `double` 写成 `int` 调了两天的。~~

### 代码示例

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define rop(i, a, b) for (int i = (a); i < (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )
#define dop(i, a, b) for (int i = (a); i > (b); i -- )

using namespace std;

using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;

const int N = 300010;
const double pi = acos(-1);
double Sin[360], Cos[360];
int n, m;
PII p[N];

// 快读消失了

struct Complex { // 手写虚数库，x 为虚部，y 为实部
	double x, y;
	Complex(){}
	Complex(double _x, double _y) { x = _x, y = _y; }
	Complex operator + (const Complex& tmp)const {
		return Complex(x + tmp.x, y + tmp.y);
	}
	Complex operator * (const Complex& tmp)const {
		return Complex(x * tmp.y + y * tmp.x, y * tmp.y - x * tmp.x);
	}
	Complex operator - (const Complex& tmp)const {
		return Complex(x - tmp.x, y - tmp.y);
	}
	Complex operator * (const double &tmp)const {
		return Complex(x * tmp, y * tmp);
	}
	Complex &operator += (Complex& tmp) {
		this -> x += tmp.x; this -> y += tmp.y;
		return *this;
	}
	Complex &operator *= (Complex& tmp) {
		*this = (*this * tmp);
		return *this;
	}
	void clear() { x = y = 0; }
	void makeI() { x = 0, y = 1; }
	bool empty() { return (x == 0) and (y == 0); }
	bool isI() { return (x == 0) && (y == 1); }
};

struct Tree {
	int l, r;
	Complex add, mul;
	Complex sum;
	int len() { return r - l + 1; }
}tr[N << 2];
#define ls u << 1
#define rs u << 1 | 1

void pushup(int u) {
	tr[u].sum = tr[ls].sum + tr[rs].sum;
}
void push_add(int u, Complex add) {
	if (tr[u].l == tr[u].r) {
		tr[u].sum = tr[u].sum + (add * tr[u].len());
		return;
	}
	tr[u].add = tr[u].add + add;
	tr[u].sum = tr[u].sum + (add * tr[u].len());
}
void push_mul(int u, Complex mul) {
	if (tr[u].l == tr[u].r) {
		tr[u].sum = tr[u].sum * mul;
		return;
	}
	tr[u].mul *= mul; tr[u].sum *= mul; tr[u].add *= mul;
}
void pushdown(int u) {
	if (tr[u].l == tr[u].r) return;
	if (!tr[u].mul.isI()) {
		push_mul(ls, tr[u].mul);
		push_mul(rs, tr[u].mul);
		tr[u].mul.makeI();
	}
	if (!tr[u].add.empty()) {
		push_add(ls, tr[u].add);
		push_add(rs, tr[u].add);
		tr[u].add.clear();
	}
}
void build(int u, int l, int r) {
	tr[u] = {l, r}, tr[u].mul.makeI();
	if (l == r) {
		tr[u].sum = Complex(p[r].first, p[r].second);
		return;
	}
	int mid = l + r >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	pushup(u);
}
void Multiply(int u, int l, int r, Complex k) {
	if (tr[u].l >= l && tr[u].r <= r) {
		push_mul(u, k); return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) Multiply(ls, l, r, k);
	if (r > mid) Multiply(rs, l, r, k);
	pushup(u);
}
void Add(int u, int l, int r, Complex k) {
	if (tr[u].l >= l && tr[u].r <= r) {
		push_add(u, k); return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (l <= mid) Add(ls, l, r, k);
	if (r > mid) Add(rs, l, r, k);
	pushup(u);
}
Complex query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if(r <= mid) return query(ls, l, r);
    if(l > mid) return query(rs, l, r);
    return query(ls, l, r) + query(rs, l, r);
}
void modify1(int l, int r, int a, int b) {
	Complex A(a, b); Add(1, l, r, A);
}
void modify2(int l, int r, int a, int b, int alpha) {
	Complex t(Sin[alpha], Cos[alpha]); Complex M(-a, -b);
	Multiply(1, l, r, t); Add(1, l, r, M * t - M);
}
void modify3(int l, int r, int a, int b, double k) {
	Complex t(0, k); Complex M(-a, -b);
	Multiply(1, l, r, t), Add(1, l, r, M * t - M);
}

int main() {
	read(n, m);
	for (int i = 1; i <= n; i ++ )
		read(p[i].first, p[i].second);
	build(1, 1, n);
	for (int i = 0; i < 360; i ++ )
		Sin[i] = sin((double)i * pi / 180.00), Cos[i] = cos((double)i * pi / 180.00);
	
	while (m -- ) {
		int op, l, r, a, b;
		int g, p, q;
		read(op, l, r);
		if (op == 1) read(a, b), modify1(l, r, a, b);
		if (op == 2) read(a, b, g), modify2(l, r, a, b, g);
		if (op == 3) read(a, b, p, q), modify3(l, r, a, b, (double)p / q);
		if (op == 4) { Complex ans = query(1, l, r); printf("%.4lf %.4lf\n", (double)ans.x / (r - l + 1), (double)ans.y / (r - l + 1)); }
	}
	
	return 0;
}
```

---

## 作者：Kalium (赞：0)

# P8105 「LCOI2022」 Cow Dance题解

## 前言：

一道很好的线段树好题，让我一步步压缩了操作数量。

## 题意：

平面直角坐标系内给定了 n 个点，m 次操作，对于操作 1，2，3，分别为平移，旋转，位似，对于操作 4，求出 x，y 轴的区间和，并分别除以区间长度后输出。

## 前置芝士（大佬可跳过）：

首先你得把操作 2，3 换成数学公式表达。

求一个点 $(x, y)$ 绕点 $(a, b)$ 旋转 $\alpha$ 后的点 $(m, n)$。

公式：

$m = (x - a) * \cos \alpha + (y - b) * \sin \alpha + a$。

$n = (y - b) * \cos \alpha + (x - a) * -\sin \alpha + b$。

求一个点 $(x, y)$ 以 $(a, b)$ 为中心位似 k 倍后的坐标 $(m, n)$。

公式：

$m = (x - a) * k + a$。

$n = (y - b) * k + b$。

以上知识度娘都可以有，推导过程不在赘述。

## 思路：

看完三种操作就很明显的反应过来，只有区间加区间乘，用线段树石锤了。

很明显，第一思路就是做两个线段树，一个表示 x 轴，再来一个表示 y 轴，这样可以解决操作 1 和操作 3，因为他们只是单纯的对一个线段树进行操作。

但是你看看操作二……，是不是感到极其不友善了。

改变一个值，要两颗线段树一起影响？

但是没关系，我们可以考虑在建两颗线段树，在面对操作 2 的时候，修改前先将原来的区间 $(x, y)$ 赋值进去，在对其分别修改，最后将两个相加即可。

不管这样发现你会对操作 2 进行了 18 次的操作，很明显，这是不能承受的，考虑一下下优化。

发现不必建四颗，因为 x, y 两颗可以分别用结构体来储存，所以只需要 2 棵就够了，这样一来，我们就把操作次数减半了，操作 2 只需要进行 8 次了！

这部分代码过于冗长，省略，并且也很好实现的呢。

但是打完发现你交上去只有 34 分，只能过测试点 1，3，4。

很明显的，你的操作 2 还是炸了，还得接着优化下。

考虑将操作 2，3 的表达柿子展开。

操作 2：

$m = (x * \cos \alpha + y * \sin \alpha) + (-a * \cos \alpha - b * \sin \alpha + a)$。

$n = (y * \cos \alpha + x * -\sin \alpha) + (-b * \cos \alpha - a * -\sin \alpha + b)$。

我们发现，由于和 y 有关，所以我们可以把每个操作绑定起来，即修改时 x，y 一起在结构体中操作，这样就避免了改了 y 的值而重建棵树。

乘法操作如下：

```cpp
	node operator * (node p) {
		return (node) {1.0 * x * p.x - 1.0 * y * p.y, 1.0 * y * p.x + 1.0 * x * p.y};
	}
```

还是很好理解的，不理解的自己带入算一下。

现在解决后半部分，容易发现，其实就是这样：

```cpp
(node) {-a, -b} * (node) {COS(g), -SIN(g)} + (node) {a, b}
```

现在考虑下操作 3。

展开式子：

$m = x * k + (-a * k + a)$。

$n = y * k + (-b * k + b)$。

发现挺对称的俩柿子，但是不友善的发现是乘法被改变了。

容易发现，我们如果让 $p.x == k$，$p.y == 0$ 的话，就可以让 x，y 分别乘 k 了呢。

里面的 a，b 同理。

剩下的操作就是基本了，区间和，区间加，区间乘，不会的去学习模板二。

挺好的题目，主要考虑如何转换，建议打打。


## 代码：

码量看着很大，但实际上不打，里面加了对拍和 debug，以及我那松散的马蜂，所以看着 300 多行，实际上只有200行左右。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

const int N = 3e5 + 7;
const double pai = 3.14159265358979323846;

int n, m;

struct node {
	double x, y;
	
	node operator + (node p) {
		return (node) {1.0 * x + 1.0 * p.x, 1.0 * y + 1.0 * p.y};
	}
	
	node operator * (node p) {
		return (node) {1.0 * x * p.x - 1.0 * y * p.y, 1.0 * y * p.x + 1.0 * x * p.y};
	}
	
	node operator * (double p) {
		return (node) {1.0 * x * p, 1.0 * y * p};
	}
} pos[N];

struct SegmentTree {
	int l, r;
	node sum, add, mul;
} tree[N << 2 | 1];

struct SeTr {
	inline void push_up(int dep) {
		tree[dep].sum = tree[dep << 1].sum + tree[dep << 1 | 1].sum;
	}
	
	inline void push_down(int dep) {
		if (tree[dep].mul.x != 1.0 || tree[dep].mul.y != 1.0) {
			tree[dep << 1].mul = tree[dep << 1].mul * tree[dep].mul;
			tree[dep << 1].sum = tree[dep << 1].sum * tree[dep].mul;
			tree[dep << 1].add = tree[dep << 1].add * tree[dep].mul;
			
			tree[dep << 1 | 1].mul = tree[dep << 1 | 1].mul * tree[dep].mul;
			tree[dep << 1 | 1].sum = tree[dep << 1 | 1].sum * tree[dep].mul;
			tree[dep << 1 | 1].add = tree[dep << 1 | 1].add * tree[dep].mul;
			
			tree[dep].mul = (node) {1.0, 0}; 
		}
		
		if (tree[dep].add.x || tree[dep].add.y) {
			tree[dep << 1].add = tree[dep << 1].add + tree[dep].add;
			tree[dep << 1 | 1].add = tree[dep << 1 | 1].add + tree[dep].add;
			
			tree[dep << 1].sum = tree[dep << 1].sum + tree[dep].add * (tree[dep << 1].r - tree[dep << 1].l + 1);
			tree[dep << 1 | 1].sum = tree[dep << 1 | 1].sum + tree[dep].add * (tree[dep << 1 | 1].r - tree[dep << 1 | 1].l + 1);
			
			tree[dep].add = (node) {0, 0};
		}
	}
	
	void build(int dep, int l, int r) {
		tree[dep].l = l, tree[dep].r = r;
		tree[dep].mul = (node) {1.0, 0};
		
		if (l == r) {
			tree[dep].sum = (node) {pos[l].x, pos[l].y};
			
			return ;
		}
		
		int mid = l + r >> 1;
		
		build(dep << 1, l, mid);
		build(dep << 1 | 1, mid + 1, r);
		
		push_up(dep);
	} 
	
	void update_add(int dep, int x, int y, node val) {
		if (tree[dep].l >= x && tree[dep].r <= y) {
			tree[dep].add = tree[dep].add + val;
			tree[dep].sum = tree[dep].sum + val * (tree[dep].r - tree[dep].l + 1); 
			
			return ;
		}
		
		push_down(dep);
		
		int mid = tree[dep].l + tree[dep].r >> 1;
		
		if (x <= mid) update_add(dep << 1, x, y, val);
		if (y > mid) update_add(dep << 1 | 1, x, y, val);
		
		push_up(dep);
	}
	
	void update_mul(int dep, int x, int y, node val) {
		if (tree[dep].l >= x && tree[dep].r <= y) {
			tree[dep].mul = tree[dep].mul * val;
			tree[dep].add = tree[dep].add * val;
			tree[dep].sum = tree[dep].sum * val;
			
			return ;
		}
		
		push_down(dep);
		
		int mid = tree[dep].l + tree[dep].r >> 1;
		
		if (x <= mid) update_mul(dep << 1, x, y, val);
		if (y > mid) update_mul(dep << 1 | 1, x, y, val);
		
		push_up(dep);
	}
	
	node query(int dep, int x, int y) {
		node ans = (node) {0, 0};
		
		if (tree[dep].l >= x && tree[dep].r <= y)
			return tree[dep].sum;
		
		push_down(dep);
		
		int mid = tree[dep].l + tree[dep].r >> 1;
		
		if (x <= mid) ans = ans + query(dep << 1, x, y);
		if (y > mid) ans = ans + query(dep << 1 | 1, x, y);
		
		return ans;
	}
} segment;

inline int read() {
	int n = 0, f = 1;
	char c = getchar();
	
	while (c < '0' || c > '9') {
		if (c == '-') f = -f;
		
		c = getchar();
	}
	
	while (c >= '0' && c <= '9') {
		n = (n << 3) + (n << 1) + (c ^ '0');
		
		c = getchar();
	}
	
	return n * f;
}

inline double COS(int g) {
	return cos(g * pai / 180);
}

inline double SIN(int g) {
	return sin(g * pai / 180);
}

int main() {
	n = read(), m = read();
	
	for (int i = 1; i <= n; i ++)
		pos[i].x = read(), pos[i].y = read();
	
	segment.build(1, 1, n);
	
	for (int i = 1; i <= m; i ++) {
		int op, x, y, a, b, p, q, g;
		
		op = read();
		
		if (op == 1) {
			x = read(), y = read(), a = read(), b = read();
			
			segment.update_add(1, x, y, (node) {a, b}); 
		} else if (op == 2) {
			x = read(), y = read(), a = read(), b = read(), g = read();
			
			segment.update_mul(1, x, y, (node) {COS(g), -SIN(g)});
			segment.update_add(1, x, y, (node) {-a, -b} * (node) {COS(g), -SIN(g)} + (node) {a, b});
		} else if (op == 3) {
			x = read(), y = read(), a = read(), b = read(), p = read(), q = read();
			
			double k = (1.0 * p) / (1.0 * q);
			
			segment.update_mul(1, x, y, (node) {k, 0});
			segment.update_add(1, x, y, (node) {-a, -b} * (node) {k, 0} + (node) {a, b});
		} else {
			x = read(), y = read();
			
			node ans = segment.query(1, x, y);
			
			printf("%0.6lf %0.6lf\n", ans.x / (1.0 * (y - x + 1)), ans.y / (1.0 * (y - x + 1)));
		}
	}
	
	return 0;
}
```

$Atlantis.$

---

