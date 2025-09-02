# [CEOI 2013] 灌水 / Watering

## 题目背景

upd on 2023/11/01: 本题部分分已修复。

翻译自 [CEOI 2013 Day 2](https://ceoi2013.hsin.hr/tasks/tasks_day2.pdf)。

Sara 是一位专注的农民，拥有一块大的长方形土地。她的土地被分成网格状的若干个单元格，共有 $5\times R$ 行和 $5\times C$ 列。此外，每隔五行有一道横向的围栏，每隔五列有一道纵向的围栏。这些围栏将土地划分成了 $R\times C$ 个大小为 $5\times5$ 的区域，称为田地。

![](https://cdn.luogu.com.cn/upload/image_hosting/1d5z6e4a.png)

这块农田两个最常见的问题是鸟害和旱灾。为了对抗鸟害，有些田地安置了稻草人。稻草人（如果有的话）占据一个单元格，每个 $5\times5$ 的田地最多只能有一个稻草人。

在干旱期，可能会持续数月时间，Sara 使用洒水器来浇灌她的庄稼。每个洒水器都有三个喷嘴：一个主喷嘴和两个侧喷嘴。它正好占据三个单元格，并浇灌所有这些单元格。侧喷嘴总是占据紧邻主喷嘴（上、下、左或右）的两个单元格。因此，单个洒水器可以浇灌到的三个单元格如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/mkdmixtp.png)

Sara 要在未被稻草人占据的每个单元格上恰好放置一个洒水器。含有稻草人的单元格不能包含洒水器喷嘴。此外，喷嘴不能放置在 Sara 的土地之外。被单个洒水器浇灌的三个单元格不一定属于同一 $5\times5$ 领域：它们也可以属于相邻的领域。在这种情况下，Sara 必须在两个由同一洒水器浇灌的相邻领域之间的栅栏上钻一个洞。

## 题目描述

**这是一个提交答案题。您将获得 $10$ 个输入文件，只需提交相应的输出文件即可。您可以从附件里的 `watering.in.zip` 中下载输入文件。**

提交一个可行的浇灌方案，使得它满足所有的要求。

如果存在多个解决方案，可以提交任何一个。

## 说明/提示

每个测试点的分值为 $10$ 分。如果输出方案无效，该测试点将获得零分。如果方案有效，则将按以下方式进行评分：
- 如果栅栏上的孔的数量不超过 $R\times C$，则得分为 $10$ 分。
- 否则，得分为 $5$ 分。


在 $10$ 个测试输入中的 $4$ 个中，每个田地都有一个稻草人。

SPJ 提供者：@[cff_0102](https://www.luogu.com.cn/user/542457) 。注：附件中的文件请用记事本/写字板打开。

## 样例 #1

### 输入

```
2 2
.....|.....
.....|.....
...#.|.....
.....|.....
.....|.....
-----+-----
.....|.....
.....|.....
.....|.....
.....|.....
.....|.....```

### 输出

```
aaacc|dxxxa
bbbce|dyyya
ddd#e|dzzza
ccbae|fccbb
cbbaa|ffcdb
-----+---_-
ssrrr|tttdd
saaax_xxeee
yxbbb|zdaaa
yxccc|zdbbb
yxddd|zdccc```

# 题解

## 作者：cff_0102 (赞：5)

一个 $5\times5$ 的没有稻草人的田地无法使用喷灌器完全铺满，因为单元格数量不可被 $3$ 整除。然而，如果这个田地有一个稻草人，有 $24$ 个单元格，这样的田地不管稻草人的位置如何都可以完全用喷灌器铺满。这是很直观的，可以通过执行简单的递归铺砖算法来证明每个可能的稻草人位置都可以铺满田地。

这意味着解决每个有稻草人的测试用例并不困难。对于其他的空田地怎么办呢？显然，我们应该在每个空田地的边缘钻一个洞。这样可以使此田地中的空单元格数量可被 $3$ 整除：如果我们通过洞口放入一个适当的瓷砖，它可以减少田地中空单元格的数量。然后我们可以使用简单的递归铺砖来铺砖。依此，我们可以得出解决每个测试用例的算法。

很容易将所有的田地排列成一串，使得在这个序列中任意相邻的两个田地也是 Sara 的土地上的相邻田地（例如，我们按螺旋的方式遍历田地）。

我们沿着这个顺序一个田地接一个田地地遍历。如果当前田地有可被 $3$ 整除的空单元格数量，我们就用瓷砖铺满它。否则，我们在这个田地和下一个田地之间钻一个洞，并通过这个洞放入一片适当的瓷砖，使得当前田地中空的单元格数可以被 $3$ 整除。然后我们铺满当前田地并移动到下一个田地（其中现在包含一块瓷砖）。这个算法是正确的，因为初始的总空单元格数量可以被 $3$ 整除（输入文件是可解的）。

通常会存在一些情况，其中洞和相应的瓷砖的选择使得该特定田地的铺砖变得不可能（例如，稻草人和通过洞的瓷砖可能会让一个空单元格孤立）。幸运的是，这是个提交答案题，我们可以手动更改输出，并用提交答案的方式提交到题目上。

下面是官方题解中的代码（只能通过题目中这 $10$ 个测试点，谁知道哪个数据又能把它 hack 了呢）：

```cpp
// CEOI 2013 - Task: Watering - Solution
// Author: Adrian Satja Kurdija

// Warning! The solution may not solve all possible inputs (this is an output-only task).
// Read the algorithm description at http://ceoi2013.hsin.hr

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char a[605][605];
char b[10][10];
int R, S;

inline char c(int i, int j) {
    return 'b' + i * 5 + j;
}

char ccc = 'z';
inline char cc(int i, int j) {
    ccc = (ccc == 'z'? 'y' : 'z');
    return ccc;
}

bool solve() {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (b[i][j] == '.') {
                b[i][j] = c(i,j);
                if (j+2 < 5 && b[i][j+1] == '.' && b[i][j+2] == '.') {
                    b[i][j+1] = b[i][j+2] = c(i,j);
                    if (solve()) return true;
                    b[i][j+1] = b[i][j+2] = '.';
                }
                if (i+2 < 5 && b[i+1][j] == '.' && b[i+2][j] == '.') {
                    b[i+1][j] = b[i+2][j] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i+2][j] = '.';
                }
                if (i+1 < 5 && j+1 < 5 && b[i+1][j] == '.' && b[i][j+1] == '.') {
                    b[i+1][j] = b[i][j+1] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i][j+1] = '.';
                }
                if (i+1 < 5 && j+1 < 5 && b[i][j+1] == '.' && b[i+1][j+1] == '.') {
                    b[i][j+1] = b[i+1][j+1] = c(i,j);
                    if (solve()) return true;
                    b[i][j+1] = b[i+1][j+1] = '.';
                }
                if (i+1 < 5 && j+1 < 5 && b[i+1][j] == '.' && b[i+1][j+1] == '.') {
                    b[i+1][j] = b[i+1][j+1] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i+1][j+1] = '.';
                }
                if (i+1 < 5 && j-1 >= 0 && b[i+1][j] == '.' && b[i+1][j-1] == '.') {
                    b[i+1][j] = b[i+1][j-1] = c(i,j);
                    if (solve()) return true;
                    b[i+1][j] = b[i+1][j-1] = '.';
                }
                b[i][j] = '.';
                return false;
            }
    return true;
}

char ograda = '#';
inline char& p(int r, int s, int x, int y) {
  if (x < 0 || x >= 5 || y < 0 || y >= 5)
    return ograda;
  return a[r * 5 + x][s * 5 + y];
}

inline char h(int x, int y) {
  if (a[x][y] != a[x+1][y] || a[x][y] == '.')
    return '-';
  return '_';
}
inline char v(int x, int y) {
  if (a[x][y] != a[x][y+1] || a[x][y] == '.')
    return '|';
  return '_';
}

inline void ispis() {
  for (int x = 0; x < R * 5; ++x) {
    for (int y = 0; y < S * 5; ++y) {
      printf("%c", a[x][y]);
      if (y % 5 == 4 && y + 1 != S * 5)
        printf("%c", v(x, y));
    }
    printf("\n");
    if (x % 5 != 4 || x == R * 5 - 1)
      continue;
    for (int y = 0; y < S * 5; ++y) {
      printf("%c", h(x, y));
      if (y % 5 == 4 && y + 1 != S * 5)
        printf("+");
    }
    printf("\n");
  }
}

int main () {
  scanf("%d%d", &R, &S);
  for (int x = 0; x < R * 5; ++x)
    for (int y = 0; y < S * 5; ++y)
      a[x][y] = '.';

  char buff[S * 6];
  int x = 0, cff = 0102;
  while (x < 5 * R) {
    scanf("%s", buff);
    if (buff[0] == '-') continue;
    int s = strlen(buff);
    int y = 0;
    for (int j = 0; j < s; ++j) {
      if (buff[j] == '|') continue;
      if (buff[j] == '#')
        a[x][y] = '#';
      y++;
    }
    x++;
  }

  vector<pair<int,int> > polja;
  for (int r = 0; r < R; ++r)
    if (r % 2 == 0)
      for (int s = 0; s < S; ++s)
        polja.push_back(make_pair(r, s));
    else
      for (int s = S - 1; s >= 0; --s)
        polja.push_back(make_pair(r, s));

  for (int i = 0; i < (int)polja.size() - 1; ++i) {
    // Treba li staviti triominu izmedju polja?
    int praznih = 0;
    for (int x = 0; x < 5; ++x)
      for (int y = 0; y < 5; ++y)
        praznih += (p(polja[i].first, polja[i].second, x, y) == '.');
//    printf("(%d %d) %d\n", polja[i].first, polja[i].second, praznih);
    if (praznih % 3 == 0) continue;

    // Stavi triominu tako da (praznih - viri) % 3 == 0.
    // Nadji dva susjedna polja:
    for (int x = 0; x < 5; ++x)
      for (int y = 0; y < 5; ++y)
        for (int xx = 0; xx < 5; ++xx)
          for (int yy = 0; yy < 5; ++yy)
            if (abs(polja[i].first * 5 + x - polja[i + 1].first * 5 - xx)
                + abs(polja[i].second * 5 + y - polja[i + 1].second * 5 - yy)
                == 1 &&
                p(polja[i].first, polja[i].second, x, y) == '.' &&
                p(polja[i + 1].first, polja[i + 1].second, xx, yy) == '.') {
              int praznih_save = praznih;
              int j = i;
              int X = x, Y = y;
              praznih -= 2;
              if (praznih % 3 != 0) {
                j = i + 1;
                X = xx; Y = yy;
                ++praznih;
              }
              for (int nx = 0; nx < 5; ++nx)
                for (int ny = 0; ny < 5; ++ny)
                  if (abs(polja[j].first * 5 + X - polja[j].first * 5 - nx)
                      + abs(polja[j].second * 5 + Y - polja[j].second * 5 - ny)
                      == 1 &&
                      p(polja[j].first, polja[j].second, nx, ny) == '.') {
                    p(polja[i].first, polja[i].second, x, y) =
                    p(polja[i + 1].first, polja[i + 1].second, xx, yy) =
                    p(polja[j].first, polja[j].second, nx, ny) = cc(x, y);
              
              bool ok = true;
              for (int r = 0; r < 5 && ok; ++r)
                for (int s = 0; s < 5; ++s)
                  if (p(polja[i].first, polja[i].second, r, s) == '.' &&
                      p(polja[i].first, polja[i].second, r-1, s) != '.' &&
                      p(polja[i].first, polja[i].second, r+1, s) != '.' &&
                      p(polja[i].first, polja[i].second, r, s-1) != '.' &&
                      p(polja[i].first, polja[i].second, r, s+1) != '.' ||
                      p(polja[i + 1].first, polja[i + 1].second, r, s) == '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r-1, s) != '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r+1, s) != '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r, s-1) != '.' &&
                      p(polja[i + 1].first, polja[i + 1].second, r, s+1) != '.') {
                    ok = false;
                    break;
                  }
              if (ok) goto line;
              p(polja[i].first, polja[i].second, x, y) =
              p(polja[i + 1].first, polja[i + 1].second, xx, yy) =
              p(polja[j].first, polja[j].second, nx, ny) = '.';
              praznih = praznih_save;
              cc(x, y);
                  }
            }
    line: ;
  }

  for (int r = 0; r < R; ++r)
    for (int s = 0; s < S; ++s) {
      for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
          b[x][y] = p(r, s, x, y);
      if (!solve())
        printf("Shouldn't happen! %d %d\n\n", r, s);
      for (int x = 0; x < 5; ++x)
        for (int y = 0; y < 5; ++y)
          p(r, s, x, y) = b[x][y];
    }
  ispis();

  return 0;
}
```

~~编写这份代码的看起来有点暴躁，他在“无解”的时候输出了一个 `Shouldn't happen!` 来表示自己心中的愤慨。~~

[这里](https://www.luogu.com.cn/problem/U288988)的附件还可以下载提交答案的文件。

---

