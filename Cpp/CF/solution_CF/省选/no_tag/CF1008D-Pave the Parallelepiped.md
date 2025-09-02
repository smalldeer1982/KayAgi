# Pave the Parallelepiped

## 题目描述

给定一个长方体，其三条边的长度分别为正整数 $A$、$B$ 和 $C$。

请你求出有多少组不同的整数三元组 $(a, b, c)$，满足 $1 \leq a \leq b \leq c$，并且可以用若干个 $a \times b \times c$ 的长方体无缝铺满 $A \times B \times C$ 的长方体。注意，所有小长方体的朝向必须一致。

例如，$1 \times 5 \times 6$ 的长方体可以被划分为若干个 $1 \times 3 \times 5$ 的长方体，但不能被划分为 $1 \times 2 \times 3$ 的长方体。

## 说明/提示

在第一个测试用例中，长方体 $(1, 1, 1)$ 只能被划分为 $(1, 1, 1)$ 的长方体。

在第二个测试用例中，长方体 $(1, 6, 1)$ 可以被划分为 $(1, 1, 1)$、$(1, 1, 2)$、$(1, 1, 3)$ 和 $(1, 1, 6)$ 的长方体。

在第三个测试用例中，长方体 $(2, 2, 2)$ 可以被划分为 $(1, 1, 1)$、$(1, 1, 2)$、$(1, 2, 2)$ 和 $(2, 2, 2)$ 的长方体。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 1 1
1 6 1
2 2 2
100 100 100
```

### 输出

```
1
4
4
165
```

# 题解

## 作者：物灵 (赞：8)

思维。

首先筛一遍因数个数函数 $d(n)$，

```cpp
for(int i = 2; i <= MAXN; ++i) {
  if(!hs[i]) zs[++zc] = i, d[i] = 2, eb[i] = 1;
  for(int j = 1, cr; j <= zc && (cr = i * zs[j]) < MAXN; ++j) {
    hs[cr] = 1; if(!(i % zs[j])) {
      d[cr] = d[i] / (eb[i] + 1) * (eb[i] + 2), eb[cr] = eb[i] + 1; break; }
    else d[cr] = d[i] << 1, eb[cr] = 1; }}
```

然后答案就是 $d(a)d(b)d(c)$ 减去一个什么东西。但是减什么呢？画图可以帮助思维。

大圈代表范围，小圈代表 $a, b, c$ 的取值（~~其实我忘记区分大小写了~~）。对称的情况仅列一次。$ga = \gcd(b, c), gb = \gcd(a, c), gc = \gcd(a, b), gg = \gcd(a, b, c)$。

| #    | 图形                                                     | 描述                                                         |
| ---- | -------------------------------------------------------- | ------------------------------------------------------------ |
| 0    | ![iImO78.jpg](https://s1.ax1x.com/2018/11/04/iImO78.jpg) | 一般情况。贡献$$+d(a)d(b)d(c)$$                              |
| 1    | ![iImL0f.jpg](https://s1.ax1x.com/2018/11/04/iImL0f.jpg) | 会重复计算 $(a, b, c)$ 和 $(b, a, c)$ 两次，故减去一次。贡献$$-\dfrac {d(ga)(d(ga) - 1) + d(gb)(d(gb) - 1) + d(gc)(d(gc) - 1)} 2$$此值包含两个对称。 |
| 2    | ![iIm76I.jpg](https://s1.ax1x.com/2018/11/04/iIm76I.jpg) | 计算 6 次，减去 9 次（因为考虑每个「中间地带」时都减 3 次），故增加 4 次。贡献 $$+4 \cdot \dfrac {d(gg)(d(gg) - 1)(d(gg) - 2)} 6$$ |
|3|![iIKDfg.jpg](https://s1.ax1x.com/2018/11/05/iIKDfg.jpg)|同一组数允许出现 $(a, a, b), (a, b, b)$ 2 次，现计算 6 次，减去 6 次，故增加 2 次。贡献$$+2 \cdot \dfrac {d(gg)(d(gg) - 1)} 2$$情况 $a = b = c$ 只计算一次，不需处理。|
| 4    | ![iImHXt.jpg](https://s1.ax1x.com/2018/11/04/iImHXt.jpg) | 计算 4 次，减去 5 次，故增加 2 次。贡献$$+d(gg)(d(gg) - 1)(d(ga) + d(gb) + d(gc) - 3d(gg))$$含对称，同样不需考虑相等。 |
| 5    | ![iImqnP.jpg](https://s1.ax1x.com/2018/11/04/iImqnP.jpg) | 计算 2 次，未被减去，故减去一次。贡献$$-(d(ga) - d(gg))(d(gb) - d(gg))(d(gc) - d(gg))$$ |

一个大 `printf` 来袭。

```cpp
inline long long Qjy(long long u) { return u * (u - 1); }

printf("%lld\n", d[a] * d[b] * d[c]
  - (d[a] * Qjy(d[ga]) + d[b] * Qjy(d[gb]) + d[c] * Qjy(d[gc]) >> 1)
  + (Qjy(d[gg]) * (d[gg] - 2) / 3 << 1)
  + (Qjy(d[gg]) * (d[ga] + d[gb] + d[gc] - 3 * d[gg] + 2) >> 1)
  - (d[ga] - d[gg]) * (d[gb] - d[gg]) * (d[gc] - d[gg]));
```

---

