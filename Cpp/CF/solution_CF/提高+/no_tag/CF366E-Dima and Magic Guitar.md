# Dima and Magic Guitar

## 题目描述

Dima loves Inna very much. He decided to write a song for her. Dima has a magic guitar with $ n $ strings and $ m $ frets. Dima makes the guitar produce sounds like that: to play a note, he needs to hold one of the strings on one of the frets and then pull the string. When Dima pulls the $ i $ -th string holding it on the $ j $ -th fret the guitar produces a note, let's denote it as $ a_{ij} $ . We know that Dima's guitar can produce $ k $ distinct notes. It is possible that some notes can be produced in multiple ways. In other words, it is possible that $ a_{ij}=a_{pq} $ at $ (i,j)≠(p,q) $ .

Dima has already written a song — a sequence of $ s $ notes. In order to play the song, you need to consecutively produce the notes from the song on the guitar. You can produce each note in any available way. Dima understood that there are many ways to play a song and he wants to play it so as to make the song look as complicated as possible (try to act like Cobein).

We'll represent a way to play a song as a sequence of pairs $ (x_{i},y_{i}) $ $ (1<=i<=s) $ , such that the $ x_{i} $ -th string on the $ y_{i} $ -th fret produces the $ i $ -th note from the song. The complexity of moving between pairs $ (x_{1},y_{1}) $ and $ (x_{2},y_{2}) $ equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF366E/129d9e481d290acfa8db6ee14b7e888ae0d5095a.png) + ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF366E/0b7383bdbf6df32e7843f9a60054de19cedafc98.png). The complexity of a way to play a song is the maximum of complexities of moving between adjacent pairs.

Help Dima determine the maximum complexity of the way to play his song! The guy's gotta look cool!

## 样例 #1

### 输入

```
4 6 5 7
3 1 2 2 3 1
3 2 2 2 5 5
4 2 2 2 5 3
3 2 2 1 4 3
2 3 1 4 1 5 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4 4 9 5
4 7 9 5
1 2 1 7
8 3 4 9
5 7 7 2
7 1 9 2 5
```

### 输出

```
4
```

# 题解

## 作者：小胖同学 (赞：2)

题意实际为查询矩阵内两种颜色的点的最远距离。


![](https://cdn.luogu.com.cn/upload/image_hosting/kej3w78l.png)


两个点的相对位置有两种大概成上图 $l_1$ 和 $l_2$ 样子，计算距离可以种距离粉色点的距离来求。

具体的两个点的距离可以写作：
$\max(\lvert dis((1,1),(x_1,y_1))-dis((1,1),(x_2,y_2))\rvert,\lvert dis((n,1),(x_1,y_1))-dis((n,1),(x_2,y_2))\rvert)$

因此对于同一种颜色的点，只有其中距离 $(1,1)$ 或 $(n,1)$ 距离最大或最小值的点有可能对答案贡献。所以每种颜色的点可以用不多于 $4$ 个点来表示。


![](https://cdn.luogu.com.cn/upload/image_hosting/nnxeqfjm.png)


如上图圈出的点是蓝色点中可能贡献答案的点。
求答案直接枚举任意的（有可能对答案贡献的）两点的距离即可。

Code:[[Link]](https://www.luogu.com.cn/paste/7z3jiv5t)。

---

## 作者：zrzring (赞：2)

[更好的阅读体验](http://zrzring.cn/index.php/archives/205)

>题意：给你一个矩阵和一个序列，你要将序列中的每一个元素转化为矩阵上的对应数字的坐标，并使得相邻元素表示的坐标的曼哈顿距离中的最大值最大，求出这个最大值

武森的《浅谈信息学中的“0”和“1”》提到过这一套路

因为值域是9，预处理不到100组关系，复杂度瓶颈不在这里，考虑如何求出每组关系之间的最长曼哈顿距离

考虑曼哈顿距离的式子$|x_1 - x_2| + |y_1 - y_2|$，可以表示为

$$
\max
\left\{
\begin{matrix}
x_1 - x_2 + y_1 - y_2\\
-x_1 + x_2 + y_1 - y_2\\
x_1 - x_2 - y_1 + y_2\\
-x_1 + x_2 - y_1 + y_2\\
\end{matrix}
\right.
$$

发现每组x和y一定符号相反，这样我们用一个set维护每一个值的坐标集合的这4个值，对于每组关系，我们枚举该组关系中的一个元素，然后只需要用另一个元素的极值去更新答案即可

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
void file() {
    freopen("read.in", "r", stdin);
    freopen("write.out", "w", stdout);
}
const int N = 1e6 + 10, inf = 1e9;
inline int read() {
    int sym = 0, res = 0; char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
set<int>S[N][4];
int n, m, rg, s[N], vis[1005][1005], len;
int main() {
    n = read(); m = read(); rg = read(); len = read();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x = read();
            S[x][0].insert(i + j);
            S[x][1].insert(i - j);
            S[x][2].insert(-i + j);
            S[x][3].insert(-i - j);
        }
    }
    int ta = read(), tb;
    for (int i = 2; i <= len; i++) {
        tb = read(); vis[ta][tb] = vis[tb][ta] = 1; ta = tb;
    }
    set<int>::iterator it; int ans = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (!vis[i][j]) continue;
            for (int k = 0; k <= 3; k++) {
                for (it = S[i][k].begin(); it != S[i][k].end(); it++) {
                    ans = max(ans, abs(*S[j][k].begin() - *it));
                    ans = max(ans, abs(*S[j][k].rbegin() - *it));
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

