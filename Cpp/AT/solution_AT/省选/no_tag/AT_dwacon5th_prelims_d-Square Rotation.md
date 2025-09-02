# Square Rotation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwacon5th-prelims/tasks/dwacon5th_prelims_d

ドワンゴ社員のニワンゴくんはテレビちゃんが大好きなので、テレビちゃんのぬいぐるみを大量に集めて床に一面に並べていました。

ニワンゴくんはレアな黒いテレビちゃんのぬいぐるみを $ N $ 個持っていて、普通のテレビちゃんのぬいぐるみと一緒に並べていました。しかし、あちこちに置いておくと管理が難しいので近くにまとめることにしました。

無限に広い二次元平面上のすべての格子点上にぬいぐるみが置いてあります。$ N $ 個の黒いぬいぐるみの座標 $ (x_i,y_i) $ が与えられます。ぬいぐるみは点として扱います。

ニワンゴくんは以下の操作を任意の回数行うことができます。

- 辺が軸に平行な一辺の長さが $ D $ の正方形を、各頂点が格子点と重なるように任意の座標に置き、正方形の角の $ 4 $ 点を、そこにある $ 4 $ 個のぬいぐるみと一緒に $ 90 $ 度回転させる。つまり、正方形の左下の頂点を $ (x,y) $ とした場合、$ (x,y)\ \rightarrow\ (x+D,y)\ \rightarrow\ (x+D,y+D)\ \rightarrow\ (x,y+D)\ \rightarrow\ (x,y) $ の順に、$ 4 $ 点を同時に回転させる

配置の**乱雑さ**を、すべての黒いぬいぐるみを囲うのに必要な辺が軸に平行な正方形の一辺の長さの最小値とします。 ここで、正方形の辺上にあるぬいぐるみも正方形に囲われているものとします。

ニワンゴくんが何度か操作を行ったあとの乱雑さとしてありうる値のうち、最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ D\ \leq\ 1000 $
- $ 0\ \leq\ x_i,\ y_i\ \leq\ 10^9 $
- 与えられる座標はすべて異なる
- 入力として与えられる数値はすべて整数である

### 部分点

- $ 1\ \leq\ D\ \leq\ 30 $ を満たすデータセットに正解すると、$ 500 $ 点が与えられる

## 样例 #1

### 输入

```
3 1
0 0
1 0
2 0```

### 输出

```
1```

## 样例 #2

### 输入

```
19 2
1 3
2 3
0 1
1 1
2 1
3 1
4 4
5 4
6 4
7 4
8 4
8 3
8 2
8 1
8 0
7 0
6 0
5 0
4 0```

### 输出

```
4```

## 样例 #3

### 输入

```
8 3
0 0
0 3
3 0
3 3
2 2
2 5
5 2
5 5```

### 输出

```
4```

# 题解

## 作者：moongazer (赞：1)

[$\mathfrak{View\space it\space on\space my\space Blog}$](https://blog.seniorious.cc/2020/AT-4497/)

## 分析

首先不难发现，按横纵坐标 $\bmod D$ 的值可分为 $D^2$ 个同余类，同余类中的数两两可达，设 $A_{i,j}$ 为 $x\bmod D=i,y\bmod D=j$ 的黑点个数

不难发现最终会把所有黑点放在一起然后用一个正方形包括所有的黑点，并尽量使正方形边长最小

不妨设正方形边长为 $aD+b$ 其中 $1\le b\le D$，不难发现 $a=\left(\max\limits_{0\le i,j\lt D}\lceil\sqrt{A_{i,j}}\rceil\right)-1$ （考虑一个边长为 $aD$ 的正方形能包括每个同余类恰好 $a^2$ 次）

不难发现若正方形左下角在 $(0,0)$ 处，则 $(0\sim b,0\sim b)$ 被覆盖 $(a+1)^2$ 次；$(0\sim b,b+1\sim D-1)$ 和 $(b+1\sim D-1,0\sim b)$ 被覆盖 $a(a+1)$ 次；$(b+1\sim D-1,b+1\sim D-1)$ 被覆盖 $a^2$ 次

可以一开始就将 $b$ 设为 $D$ 然后枚举每一个点作为左下角，若此时 $b$ 合法，则计入答案并令 $b\leftarrow b-1$，否则就枚举下一个左下角，于是问题转变为判断对于一个左下角 $b$ 是否合法

这个问题可以用二维前缀和解决：分别记录 $a^2\lt A_{i,j}\le a(a+1)$ 的个数和 $a(a+1)\lt A_{i,j}$ 的个数，每次询问即查询 $a^2$ 的区域是否有 $\gt a^2$ 的和 $a(a+1)$ 的区域是否有 $\gt a(a+1)$ 的，并注意处理 $+b$ 后超过 $D-1$ 的情况，具体见代码

## 代码

```cpp
constexpr int N = 1005;

int sum2(int x1, int y1, int x2, int y2);
int sum3(int x1, int y1, int x2, int y2);
bool check2(int x, int y, int b);
bool check3(int x, int y, int b);

int cnt2[N][N], cnt3[N][N];
int cnt[N][N];
int n, d;

int main() {
  read(n), read(d);
  for (int i = 1; i <= n; ++i) {
    int x, y;
    read(x), read(y);
    ++cnt[x % d][y % d];
  }
  int a = 0;
  for (int i = 0; i < d; ++i) {
    for (int j = 0; j < d; ++j) {
      if (cnt[i][j]) {
        int tmp = std::sqrt(cnt[i][j]);
        if (tmp * tmp < cnt[i][j]) {
          ++tmp;
        }
        a = max(a, tmp - 1);
      }
    }
  }
  for (int i = 0; i < d; ++i) {
    for (int j = 0; j < d; ++j) {
      if (cnt[i][j] > a * a) {
        if (cnt[i][j] > a * (a + 1)) {
          ++cnt3[i + 1][j + 1];
        } else {
          ++cnt2[i + 1][j + 1];
        }
      }
    }
  }
  for (int i = 1; i <= d; ++i) {
    for (int j = 1; j <= d; ++j) {
      cnt2[i][j] += cnt2[i - 1][j] + cnt2[i][j - 1] - cnt2[i - 1][j - 1];
      cnt3[i][j] += cnt3[i - 1][j] + cnt3[i][j - 1] - cnt3[i - 1][j - 1];
    }
  }
  int b = 0;
  for (; b < d; ++b) {
    if (check2(0, 0, b) && check3(0, 0, b)) {
      break;
    }
  }
  for (int i = 0; i < d; ++i) {
    for (int j = 0; j < d; ++j) {
      if (!(i + j)) {
        continue;
      }
      while (b) {
        if (check2(i, j, b - 1) && check3(i, j, b - 1)) {
          --b;
        } else {
          break;
        }
      }
    }
  }
  write(a * d + b), EL;
  return 0;
}

int sum2(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2) {
    return 0;
  }
  ++x1, ++y1, ++x2, ++y2;
  return cnt2[x2][y2] - cnt2[x2][y1 - 1] - cnt2[x1 - 1][y2] + cnt2[x1 - 1][y1 - 1];
}
int sum3(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2) {
    return 0;
  }
  ++x1, ++y1, ++x2, ++y2;
  return cnt3[x2][y2] - cnt3[x2][y1 - 1] - cnt3[x1 - 1][y2] + cnt3[x1 - 1][y1 - 1];
}
bool check2(int x, int y, int b) {
  int t1 = sum2(x + b + 1, y + b + 1, d - 1, d - 1);
  int t2 = sum2(max(0, x + b + 1 - d), max(0, y + b + 1 - d), x - 1, y - 1);
  int t3 = sum2(x + b + 1, max(0, y + b + 1 - d), d - 1, y - 1);
  int t4 = sum2(max(0, x + b + 1 - d), y + b + 1, x - 1, d - 1);
  return !t1 && !t2 && !t3 && !t4;
}
bool check3(int x, int y, int b) {
  int t1 = sum3(x + b + 1, 0, d - 1, d - 1);
  int t2 = sum3(0, y + b + 1, d - 1, d - 1);
  int t3 = sum3(max(0, x + b + 1 - d), 0, x - 1, d - 1);
  int t4 = sum3(0, max(0, y + b + 1 - d), d - 1, y - 1);
  return !t1 && !t2 && !t3 && !t4;
}
```


---

