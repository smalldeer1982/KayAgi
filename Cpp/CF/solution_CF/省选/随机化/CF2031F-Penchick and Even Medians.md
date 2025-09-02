# Penchick and Even Medians

## 题目描述

这是一个交互式的问题。

Penchick 刚从澳大利亚的黄金海岸度假回家，却遗忘给他的宠物鸭 Duong Canh 带礼物！或许经过海滩上的深思熟虑设计出的一道有趣题目，是最好的纪念品。

你面临的任务是找出一个长度为 $n$ 的隐藏排列 $p$，其中 $n$ 是偶数。你可以通过以下方式进行查询：

- 选择排列 $p$ 的一个长度为 $4 \le k \le n$ 的子序列（子序列中的元素不必连续）。交互系统会返回该子序列中的两个中位数。

你的任务是在不超过 80 次查询的条件下，找出排列 $p$ 中这两个中位数的索引。

注意：交互系统是固定的，即排列 $p$ 在开始时就已经确定，并不会根据你的查询而改变。

## 样例 #1

### 输入

```
2
6

3 4

3 4

2 3

10

3 4

6 7```

### 输出

```
? 6 1 2 3 4 5 6

? 4 3 6 1 5

? 4 3 6 2 5

! 3 6

? 6 1 3 7 8 9 10

? 8 1 2 3 4 5 6 7 8

! 6 5```

# 题解

## 作者：rizynvu (赞：6)

首先因为 $n$ 就为偶数，中位数就是 $(\frac{n}{2}, \frac{n}{2} + 1)$。

考虑到 $n\le 100$，$q\le 80$，所以第一想法是尝试去排除一些无用的状态。  
那么因为长度为偶数，所以只能通过两个两个删来判断。

但是手玩一下发现这样做好像没啥前途。  
但是手玩的过程中能知道，如果删去的两个下标 $x, y$ 满足 $p_x, p_y$ 一个 $< \frac{n}{2}$，一个 $> \frac{n}{2} + 1$，那么查询出来的一定还是 $(\frac{n}{2}, \frac{n}{2} + 1)$。

令这个对为 $(x_0, y_0)$，那么就会发现这个 $x_0, y_0$ 是容易判断的，看起来也有点用，于是考虑利用一下这个对（关于如何求出 $(x_0, y_0)$，放到下面再探讨）。

那么一个想法就是让询问中包含 $x_0, y_0$ 两个下标。  
又因为询问必须为偶数，所以将剩下 $n - 2$ 个下标随意两两配对，记为 $(x_i, y_i)$。  
那么去询问 $(x_0, y_0, x_i, y_i)$，考虑这会有什么性质。  
（为什么是两两配对一次只问 $4$ 个？因为询问的越多得到的信息就相对越模糊。）

注意到，如果 $p_{x_i}, p_{y_i}$ 中含有 $\frac{n}{2}, \frac{n}{2} + 1$，那么返回的值就必然带有这些数。  
这是因为 $p_{x_0}, p_{y_0}$ 在 $\frac{n}{2}, \frac{n}{2} + 1$ 的两边，所以当 $\frac{n}{2}$ 或者 $\frac{n}{2} + 1$ 放进去的时候必然会被两个数夹在中间，那么不管另一个数是什么肯定都不会影响返回的中位数带有 $\frac{n}{2}$ 或者 $\frac{n}{2} + 1$。

否则，如果 $p_{x_i}, p_{y_i}$ 中不含有 $\frac{n}{2}, \frac{n}{2} + 1$，那么返回的值必没有这些数。  
这是比较显然的，因为都没有这些数就不可能带这些数了。

于是考虑把每一对都询问下来后留下询问的返回值中带有 $\frac{n}{2}$ 或者 $\frac{n}{2} + 1$ 的下标对 $(x_1, y_1), (x_2, y_2)$，那么可以知道的是 $\frac{n}{2}$ 和 $\frac{n}{2} + 1$ 必出现在这两对的下标之中，且每对都恰好只有 $1$ 个对应的下标。  
那么实际上就只有 $2\times 2 = 4$ 种情况，可以直接枚举每一对选出的下标 $a, b$，如果询问 $(x_0, y_0, a, b)$ 为 $(\frac{n}{2}, \frac{n}{2} + 1)$，那么答案就为 $(a, b)$。  
如果想的话也可以优化掉 $1$ 次操作：枚举 $3$ 种，都不合法就为剩下的一种。这个优化实际上并不必要，想加就加。

其实还有一种情况是问出来的对只有一个 $(x_1, y_1)$，但是这个时候答案肯定就为 $(x_1, y_1)$，更为简单。

那么可以知道的是，只要知道了 $(x_0, y_0)$，只需要 $\frac{n - 2}{2} + 3 = \frac{n}{2} + 2$ 次询问就可以得到答案了。

于是现在的问题来到了在 $78 - \frac{n}{2}$ 次询问内得到一组合法的 $(x_0, y_0)$。

注意到 $p_{x_0}, p_{y_0}$ 只需要满足一个 $< \frac{n}{2}$ 一个 $> \frac{n}{2} + 1$ 就合法了，那么合法的 $p_{x_0}, p_{y_0}$ 的数量应该挺多的，且题目并没有交互库自适应。  
所以可以考虑随机化得出 $(x_0, y_0)$，至于判断，方法在一开始就已经提到了。

随出合法下标对的概率分析：  
单次随出合法的概率就为 $\frac{2(\frac{n}{2} - 1)^2}{n(n - 1)}$，那么总失败率就为 $(1 - \frac{2(\frac{n}{2} - 1)^2}{n(n - 1)})^{78 - \frac{n}{2}}$。  
放到 desmos 里面观察，当 $n = 100$ 时取到失败率最大值，约为 $8.5\times 10^{-9}$，非常可过阿。

代码优化了最后 $1$ 次询问，写的好像有点丑了 qaq。

```cpp
#include<bits/stdc++.h>
std::mt19937_64 eng(std::chrono::steady_clock::now().time_since_epoch().count());
constexpr int maxn = 1e2 + 10;
std::pair<int, int> query(std::vector<int> a) {
   std::cout << "? " << a.size();
   for (int x : a) std::cout << ' ' << x;
   std::cout << std::endl;
   int x, y;
   std::cin >> x >> y;
   return std::make_pair(x, y);
}
inline void solve() {
   int n;
   std::cin >> n;
   int x0 = 0, y0 = 0;
   do {
      int x = eng() % n + 1, y;
      do {
         y = eng() % n + 1;
      } while (y == x);
      std::vector<int> vec;
      for (int i = 1; i <= n; i++) {
         if (i == x || i == y) continue;
         vec.push_back(i);
      }
      if (query(vec) == std::make_pair(n / 2, n / 2 + 1)) {
         x0 = x, y0 = y;
      }
   } while (! x0);
   std::pair<int, int> c[2] = {{0, 0}, {0, 0}};
   for (int i = 1, j = 0, k = 0; i <= n; i++) {
      if (i == x0 || i == y0) continue;
      if (j) {
         auto [x, y] = query({i, j, x0, y0});
         if (x == n / 2 || x == n / 2 + 1 || y == n / 2 || y == n / 2 + 1) {
            c[k++] = {i, j};
         }
         j = 0;
      } else {
         j = i;
      }
   }
   if (! c[1].first) {
      std::cout << "! " << c[0].first << ' ' << c[0].second << std::endl;
   } else if (query({c[0].first, c[1].first, x0, y0}) == std::make_pair(n / 2, n / 2 + 1)) {
      std::cout << "! " << c[0].first << ' ' << c[1].first << std::endl;
   } else if (query({c[0].first, c[1].second, x0, y0}) == std::make_pair(n / 2, n / 2 + 1)) {
      std::cout << "! " << c[0].first << ' ' << c[1].second << std::endl;
   } else if (query({c[0].second, c[1].first, x0, y0}) == std::make_pair(n / 2, n / 2 + 1)) {
      std::cout << "! " << c[0].second << ' ' << c[1].first << std::endl;
   } else {
      std::cout << "! " << c[0].second << ' ' << c[1].second << std::endl;
   }
}
int main() {
   int T;
   for (std::cin >> T; T--; ) {
      solve();
   }
   return 0;
}
```

---

## 作者：lalaouye (赞：4)

赛时坠机了，赛后把 F 做出来了。。

刚开始做不出来，后来注意到样例输出了长度为 $n-2$ 的询问，启发我对于每个相邻数对 $(i,i+1)$，将其删去再进行询问，其中 $i$ 为奇数，共消耗 $50$ 次。然后我们对输出的两个数 $x,y$ 进行讨论：

1. 如果 $x,y$ 满足 $x=\frac n 2,y=\frac n 2 +1$，则说明删去的两个数其中一个数小于 $\frac n 2$，一个数大于 $\frac n 2 +1$。这种情况貌似对答案并不影响。

2. 如果 $x,y$ 满足 $x<\frac n 2,y > \frac n 2 + 1$，则说明删除的数正是 $\frac n 2$ 和 $\frac n 2 +1$，这种情况是好处理的。

3. 如果 $x,y$ 满足 $x=\frac n 2,y> \frac n 2+1$，则说明 $\frac n 2+1$ 正好在这个数对里面，将其记录下来。

4. 如果 $x,y$ 满足 $x<\frac n 2,y=\frac n 2+1$，跟上面的情况类似。

5. 如果 $x,y$ 满足 $x<\frac n 2,y=\frac n 2$，这种情况有些复杂，也是本题的重点，数对中的数都大于等于 $\frac n 2+1$。

6. 如果 $x,y$ 满足 $x=\frac n 2+1,y>\frac n 2+1$，跟上面情况类似。

发现最麻烦的是第 $5,6$ 类点对，我们把第 $5$ 类点对存入一个数组，第 $6$ 类存入另一个数组，现在考虑找到包含 $\frac n 2$ 的点对和 $\frac n 2 +1$ 的点对，怎么找呢？其实也是简单的，直接询问第一个数组的第一个点对与第二个数组的第一个点对，第一个数组的第二个点对与第二个数组的第二个点对......这样子只要结果输出了 $\frac n 2$ 或 $\frac n 2+1$，我们就能够确定包含这两个数的两个点对了。

找到点对后怎么处理都行，算一下操作次数，首先要花 $50$ 次枚举点对，然后再最多花 $25$ 次找两个点对，最后花 $4$ 次确定位置，总共 $79$ 次，可以通过。

代码很丑，仅供参考：

   ````
   #include <bits/stdc++.h>
   #define rep(i, l, r) for (int i (l); i <= r; ++ i)
   #define rrp(i, l, r) for (int i (r); i >= l; -- i)
   #define pii pair <int, int>
   #define eb emplace_back
   #define inf 1000000000000
   using namespace std;
   constexpr int N = 100 + 5, K = 10;
   typedef unsigned long long ull;
   typedef long long ll;
   inline int rd () {
     int x = 0, f = 1;
     char ch = getchar ();
     while (! isdigit (ch)) {
       if (ch == '-') f = -1;
       ch = getchar ();
     }
     while (isdigit (ch)) {
       x = (x << 1) + (x << 3) + ch - 48;
       ch = getchar ();
     }
     return x * f;
   }
   int n;
   pii ask1 (int x, int y) {
     cout << "? " << n - 2 << " ";
     rep (i, 1, n) {
       if (i != x && i != y) cout << i << " ";
     }
     cout << endl;
     cin >> x >> y;
     return pii (x, y);
   }
   pii ask2 (int a, int b, int c, int d) {
     cout << "? 4 " << a << " " << b << " " << c << " " << d << endl; 
     int x, y;
     cin >> x >> y;
     return pii (x, y);
   }
   int a1[N], n1, a2[N], n2, tt;
   void motherfucker () {
     ++ tt;
     cin >> n; n1 = n2 = 0;
     int f1 = 0, f2 = 0;
     int x = 0, y = 0, z = 0;
     rep (i, 1, n) {
       pii t = ask1 (i, i + 1);
       if (t.first == n / 2 && t.second == n / 2 + 1) {
         if (! f1) f1 = i; else f2 = i;
       } else {
         if (t.first == n / 2 && t.second > n / 2 + 1) {
           y = i;
         } else 
         if (t.first < n / 2 && t.second == n / 2 + 1) {
           x = i;
         } else {
           if (t.first < n / 2 && t.second > n / 2 + 1) {
             z = i; ++ i; continue;
           }
           if (t.first < n / 2 && t.second == n / 2) a2[++ n2] = i;
           else a1[++ n1] = i;
         }
       }
       ++ i;
     }
     if (z) {
       if (! f1) {
         rep (i, 1, n1) f1 = a1[i];
         rep (i, 1, n2) f2 = a2[i];
       } else {
         if (! f2) {
           rep (i, 1, n1) f2 = a1[i];
           rep (i, 1, n2) f2 = a2[i];
         }
       }
       pii t = ask2 (f1, f1 + 1, f2, z);
       if (t.first == n / 2 || t.second == n / 2) {
         cout << "! " << z << " " << z + 1 << endl; 
       } else cout << "! " << z + 1 << " " << z << endl;
       return ;
     } else {
       int mn = min (n1, n2);
       int l = 0, r = 0;
       rep (i, 1, mn) {
         pii t = ask2 (a1[i], a1[i] + 1, a2[i], a2[i] + 1);
         if (t.first == n / 2 || t.second == n / 2) x = a1[i];
         else l = a1[i];
         if (t.first == n / 2 + 1 || t.second == n / 2 + 1) y = a2[i];
         else r = a2[i];
       }
       if (n2)
       rep (i, n2 + 1, n1) {
         pii t = ask2 (a1[i], a1[i] + 1, a2[1], a2[1] + 1);
         if (t.first == n / 2 || t.second == n / 2) x = a1[i];
         else l = a1[i];
         if (t.first == n / 2 + 1 || t.second == n / 2 + 1) y = a2[1];
         else r = a2[1];
       }
       if (n1)
       rep (i, n1 + 1, n2) {
         pii t = ask2 (a1[1], a1[1] + 1, a2[i], a2[i] + 1);
         if (t.first == n / 2 || t.second == n / 2) x = a1[1];
         else l = a1[1];
         if (t.first == n / 2 + 1 || t.second == n / 2 + 1) y = a2[i];
         else r = a2[i];
       }
       if (f1) l = f1, r = f1 + 1;
       if (! l) l = r + 1; if (! r) r = l + 1;
       pii t = ask2 (l, r, x, y);
       int ans1 = 0, ans2 = 0;
       if (t.first == n / 2 || t.second == n / 2) {
         ans1 = x;
       }
       if (t.first == n / 2 + 1 || t.second == n / 2 + 1) {
         ans2 = y;
       }
       t = ask2 (l, r, x + 1, y);
       if (t.first == n / 2 || t.second == n / 2) {
         ans1 = x + 1;
       }
       if (t.first == n / 2 + 1 || t.second == n / 2 + 1) {
         ans2 = y;
       }
       t = ask2 (l, r, x, y + 1);
       if (t.first == n / 2 || t.second == n / 2) {
         ans1 = x;
       }
       if (t.first == n / 2 + 1 || t.second == n / 2 + 1) {
         ans2 = y + 1;
       }
       t = ask2 (l, r, x + 1, y + 1);
       if (t.first == n / 2 || t.second == n / 2) {
         ans1 = x + 1;
       }
       if (t.first == n / 2 + 1 || t.second == n / 2 + 1) {
         ans2 = y + 1;
       }
       cout << "! " << ans1 << " " << ans2 << endl;
     }
   }
   int main () {
     // freopen ("1.in", "r", stdin);
     int T; cin >> T;
     for (; T; -- T) motherfucker ();
   }
   ````

---

## 作者：2022dyx (赞：1)

这种题目的询问一定要有比较好的意义。如果能够询问 $k=2$ 是非常好的，可以直接确定两个数，但是这不被允许。我们退而求其次，接下来比较边缘的询问是 $k=4$ 或 $k=n-2$。前者由于牵扯到 $4$ 个数共 $24$ 种排列方式而比较棘手，所以我们尝试后者。先用 $1$ 次操作问出原序列中的两个中位数分别是 $l$ 和 $r$，设 $L=l-1$，$R=r+1$，则有以下可能。

- $LR$：最好的可能，意味着剩下的两个就是原先的中位数。
- $Lr/lR$：也很好处理，剩下的一个是中位数之一，一个是另一侧的普通数字。
- $lL/Rr$：很难处理，剩下的可能是中位数和同侧普通数字，也可能是两个同色普通数字。
- $lr$：普通情况，一定是两个不同侧普通数字。

我们先把 $50$ 对相邻的分别剩下后问出结果，此时最大的问题就是对上述第三种情况的处理。不难发现其他所有情况都是剩下的都是左右侧各一个，只有这种情况是两个单侧，所以 $lL$ 和 $Rr$ 的个数一定相等。所以我们可以通过把一组 $lL$ 和一组 $Rr$ 都剩下来询问判断其中有没有中位数，由于最后一组不用问，这只需 $24$ 次操作。

最后就是已知两组中各有一个中位数，确定下来这两个中位数，显然可以每组剩一个来询问，$3$ 次就够，还没问出来就是剩下那两个。

综上所述，此做法仅需 $1+50+24+3=78$ 次操作，可以通过，只是需要判很多细节，比方说 $n=6$ 时无法剩 $4$ 个询问等等，

---

