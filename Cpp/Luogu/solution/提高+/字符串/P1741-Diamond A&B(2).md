# Diamond A&B(2)

## 题目背景

由于本题较难，将本题拆做两题，分别为 diamond A 以及 diamond B。本题为 Diamond B。



## 题目描述

教主上电视了！这个消息绝对是一个爆炸性的新闻。一经传开，大街上瞬间就没人了（都回家看电视去了），商店打烊，工厂停业。大家都把电视机的音量开到最大，教主的声音回响在大街小巷。

小 L 给小 X 慌乱地打开自己家的电视机，发现所有频道都播放的是教主的采访节目（-\_-bbb）。只见电视屏幕上的教主笑意吟吟，给大家出了一道难题：

一个边长为 $n$ 的大菱形被均匀地划分成了 $n\times n$ 个边长为 $1$ 的小菱形组成的网格，但是网格中部分边被抹去了，小 $L$ 想知道，大菱形内有多少个平行四边形，这些平行四边形内不存在边（平行四边形内是空的）。

教主说，如果谁写出了程序，移动用户请将程序发送到 xxxx，联通用户请将程序发送到 xxxx……如果答对这个题，将有机会参加抽奖，大奖将是教主签名的 Orz 教主 T-Shirt 一件！这个奖品太具有诱惑力了。于是你需要编一个程序完成这么一道题。


## 说明/提示

### 数据范围及约定

- 对于 $20\%$ 的数据，$n \le 10$；
- 对于 $40\%$ 的数据，$n \le 60$；
- 对于 $60\%$ 的数据，$n \le 200$；
- 对于 $100\%$ 的数据，$n \le 888$。

## 样例 #1

### 输入

```
4
1111
11101
1000
10111
1100
10101
0111
11101
1111
```

### 输出

```
3```

# 题解

## 作者：brealid (赞：4)

终于AC了这道题……如果不算@引领天下 巨佬的打表程序，应该算是首AC吧。

先放一下题目的样例解释

![](https://cdn.luogu.com.cn/upload/pic/62695.png)

难度估计：普及+/提高

两种做法：

## 一、DP

我写过，但是写炸了，有兴趣看@Smallbasic [转发的题解](https://www.luogu.org/discuss/show/121275)

## 二、枚举

考虑一个矩形，其左上角必定是 
```plain
 ——
|
```
的样子。所以遍历找到这样的矩形起始点（定义：节点就是正方形中的格点），然后左边向下拓展，遇到向右的边停止，并记录矩形的高（若向下拓展时某个节点既没有向下的边也没有向右的边则失败），上边向右拓展也类似。

然后检查矩形的下边，右边是否都为``1``，并检查矩形的内部是否都为``0``。若满足则``ans++;``

#### 附一组数据

>input

```plain
3
111
1101
110
1101
011
1101
111
```

>output

```plain
3
```

>解释

![](https://cdn.luogu.com.cn/upload/pic/62693.png)

#### 小技巧

可增加代码可读性

对于节点 ``(i, j)``，其右边与下边可 $\#define$ 为

```cpp
#define R(x, y) a[(x) * 2 - 1][y]
#define D(x, y) a[(x) * 2][y]
```

(读入的数组下标开始为1）

## Code

```cpp
/*************************************
 * problem:      P1741.
 * user ID:      63720.
 * user name:    Jomoo.
 * time:         2019-07-08.
 * language:     C++.
 * upload place: Luogu.
*************************************/ 

#include <bits/stdc++.h>
using namespace std;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}  

int n, a[2003][1003] = {0};
string getIn;

#define R(x, y) a[(x) * 2 - 1][y]
#define D(x, y) a[(x) * 2][y]

int main()
{
    n = read<int>();
    for (int i = 1; i <= n * 2 + 1; i++) {
        cin >> getIn;
        for (unsigned int j = 0; j < getIn.length(); j++) {
            a[i][j + 1] = getIn[j] & 1;
        }
    }
    int ans(0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (R(i, j) && D(i, j)) {
                bool fail = 0;
                int l = 1, h = 1;
                while (1) {
                    if (D(i, j + l)) break;
                    else if (R(i, j + l)) l++;
                    else {
                        fail = 1;
                        break;
                    }
                }
                if (fail) continue;
                while (1) {
                    if (R(i + h, j)) break;
                    else if (D(i + h, j)) h++;
                    else {
                        fail = 1;
                        break;
                    }
                }
                if (fail) continue;
                for (int y = 0; y < l && !fail; y++) {
                    if (!R(i + h, j + y)) fail = 1;
                }
                if (fail) continue;
                for (int x = 0; x < h && !fail; x++) {
                    if (!D(i + x, j + l)) fail = 1;
                }
                if (fail) continue;
                for (int x = 1; x < h && !fail; x++) {
                    for (int y = 0; y < l && !fail; y++) {
                        if (R(i + x, j + y)) fail = 1;
                    }
                }
                if (fail) continue;
                for (int y = 1; y < l && !fail; y++) {
                    for (int x = 0; x < h && !fail; x++) {
                        if (D(i + x, j + y)) fail = 1;
                    }
                }
                if (fail) continue;
                ans++;
            }
        }
    }
    write(ans, 10);
    return 0;
}
```

---

