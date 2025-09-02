# [BalticOI 2001] Box of Mirrors

## 题目描述

数学家 Andris 有一个小盒子，其底部是 $n\times m$ 的格子，每个格子可以放一面 $45$ 度朝向的镜子。

在盒子的边界，每行每列的两端，有一些孔，光线可以从中射入盒子，也可以射出。

![](https://cdn.luogu.com.cn/upload/image_hosting/i5gnsp7v.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/1xl9wkfz.png)

如上图所示，从孔 $2$ 射进盒子的光线经过两次反射后又从孔 $7$ 射出。

Andris 想请你设计一个盒子，使得从每个孔射入的光线都会从指定的孔射出。

例如，如果他希望从 $10$ 个孔里射入的光线分别由孔 $9,7,10,8,6,5,2,4,1,3$ 射出，则上图也是一个满足要求的盒子。

注意，孔的编号如图从 $1$ 到 $2\times (n+m)$ 编号。

## 说明/提示

对于 $100\%$ 的数据，$1\leq n,m\leq 100$，$1\leq a_i\leq 2\times (n+m)$。

## 样例 #1

### 输入

```
2 3
9
7
10
8
6
5
2
4
1
3```

### 输出

```
0 1 0
0 1 1```

# 题解

## 作者：qinyubo (赞：6)

[Box of Mirrors：一道有意思的构造题](https://www.luogu.com.cn/problem/P10612)

首先考虑什么样的 $\{a_i\}$ 才能有解。

首先 $\{a_i\}$ 得是一个排列，并且得是一个对换排列，即 $\forall i,a_i\ne i,a_{a_i}=i$，这是因为光路可逆。

其次，$\forall i\le n+m,a_i>n+m$，这是因为镜子是左下-右上型的，所以从左方或下方入射的光只能从右方或上方出来。

基于此，我们还可以得到一个更强一些的结论：$\forall 1\le i\le n，2n+m-i+1\le a_i\le 2(n+m)$，和 $\forall 1\le i\le m，n+m+1\le a_{n+i}\le 2(n+m)-i+1$，在图像上理解就是一束左下方入射的光只能往它的右上方走，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/dwaj67pa.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/uu35vvip.png)

然后……我们发现，这就是充要条件了？

其必要性是显然的。接下来，我们将通过归纳地构造，证明其充分性。

我们将通过数学归纳法，证明当每束左下方入射的光都从它的右上方射出时，可以构造出一组合法的镜子。

上述命题当 $n=0$ 时显然成立，因为此时不存在左方或右方，那么题设条件等价于每一个下方入射的光都将从上方对应的出口射出。此时不需要放镜子。

现在，我们假设上述命题对于 $n-1$ 成立，试图推导出对于 $n$ 是成立的。

首先考虑第一行。

如果第一行左侧的光线（红色光）直接从右侧出去了，那么我们只需删除第一行并且什么也不用做。

![](https://cdn.luogu.com.cn/upload/image_hosting/b8v4mv42.png)

否则根据我们的假设，红色光只能从上方出去，不妨假设其要从第 $l$ 列上方出去，那么我们就可以确定第一行第 $l$ 列必然会放一面镜子。而此时第一行右侧的光线（绿色光）将会（在剩余的 $(n-1)$ 行看来）变成从第 $l$ 列上方射入：

![](https://cdn.luogu.com.cn/upload/image_hosting/73uoj98v.png)

而假设此时绿色光的出口在第 $l$ 列左侧，那么剩余 $(n-1)$ 行仍然是符合条件的。由归纳假设，存在一组合法的镜子。

![](https://cdn.luogu.com.cn/upload/image_hosting/p94t4ual.png)

若不然，即绿色光的出口在第 $l$ 列右侧，那么此时剩余 $(n-1)$ 行就不符合我们的假设（每束左下方入射的光都从它的右上方射出）了。

![](https://cdn.luogu.com.cn/upload/image_hosting/2pu70kiv.png)

不妨设其出口是第 $l_2$ 列下方，那么我们就在第一行、第 $l_2$ 列放一面镜子，那么绿色光就符合假设了。但是，考虑第 $l_2$ 行上方射入的光线（蓝色光），其将会（在剩余的 $(n-1)$ 行看来）变成从第 $l$ 列上方射入，我们又要考虑蓝色光的出口……

![](https://cdn.luogu.com.cn/upload/image_hosting/7m9i0pel.png)

容易发现，由于第 $l$ 列右边的列是有限的，所以上述步骤一定会在有限步之后终止，此时我们去掉第一行，剩下的 $(n-1)$ 行将会仍然符合假设。

于是，我们证明了上述条件（每束左下方入射的光都从它的右上方射出）的充分性，同时给出了一组构造性的解。

![](https://cdn.luogu.com.cn/upload/image_hosting/mdzocrug.png)

代码很好写，维护最上方是哪些光线就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace QYB {
  int n, m, a[205], b[205], c[105], d[205], t[105][105];
  int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + m; i++) {
      scanf("%d", a + i);
      a[i] = 2 * (n + m) + 1 - a[i];
      d[a[i]] = i - n;
    } for (int i = 1; i <= m; i++) b[i] = c[i] = i;
    for (int i = 1; i <= n; i++) {
      if (a[i] == i + m) continue;
      t[i][b[a[i]]] = 1;
      c[b[i + m] = b[a[i]]] = i + m;
      while (d[c[b[a[i]]]] > b[a[i]]) {
        t[i][d[c[b[a[i]]]]] = 1;
        swap(b[c[b[a[i]]]], b[c[d[c[b[a[i]]]]]]);
        swap(c[b[a[i]]], c[d[c[b[a[i]]]]]);
      }
    } for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        printf("%d%c", t[i][j], " \n"[j == m]);
      }
    } return 0;
  }
} int main() { return QYB::main(); }
```

---

## 作者：红黑树 (赞：4)

[可能更好的阅读体验](https://rbtr.ee/P10612)

## [题目](https://www.luogu.com.cn/problem/P10612)

## 题解
由于光路可逆，我们只需观察左下两侧，分别编号为 $1$ 到 $n + m$。

对于一面镜子 $\left(i, j\right)$，观察它对光路的改变。

我们假设不加这面镜子前，从 $i$ 开始的光线会到达 $b_i$。那么加上这面镜子之后，相当于交换了 $b_i$ 和 $b_{n + j}$。当然有个前提是当前 $\left(i, j\right)$ 右上方不能有任何镜子。

我们现在求出 $b$，看看能不能倒推出上一步的 $b'$，这样我们就推出一面镜子的位置。当 $b_i = i$ 对于所有 $i$ 均满足时，说明没有镜子了，可以结束程序。

现在我们试图找到上一步的 $b'$，我们需要更加具象的东西。让 $i$ 到 $b_i$ 连边。如果产生了自环，说明 $b_i = i$，任务完成了。假设有一条链 $u \to v \to w$，如果删去 $v$，映射关系变成 $u \to w$ 和 $v \to v$，此时 $b_u = w$，我们确实地让自环数量变多了，也就找到了一面镜子。

因此我们选择一个直接相邻的两个点 $\left(i, j\right)$，加镜子 $\left(i, j - n \right)$，消去这条边即可。如果 $b_i = j$ 或者 $b_j = i$，那么这两个点直接相邻。

但我们现在需要找到尽可能靠后加入的镜子，根据上述描述，越靠后的镜子 $i$ 越小，$j$ 越大（右上方）。于是我们可以直接从小到大枚举 $i$，然后从大到小枚举 $j$，判断这两点是否直接连接即可。

## 代码
```cpp
/* C++17 is required!
 * By Koicy (https://koicy.ly)
 * Email n@rbtr.ee
 * 我还期待着名为奇迹的魔法，哪怕会凋零会消散只会是一场浮华，我笑纳！

         __    __                             __         _
   _____/ /_  / /_________  ___              / /______  (_)______  __
  / ___/ __ \/ __/ ___/ _ \/ _ \   ______   / //_/ __ \/ / ___/ / / /
 / /  / /_/ / /_/ /  /  __/  __/  /_____/  / ,< / /_/ / / /__/ /_/ /
/_/  /_.___/\__/_/   \___/\___/           /_/|_|\____/_/\___/\__, /
                               SIGN                         /___*/
#define __NO_MAIN__ false
#define __ENABLE_RBLIB__ true
constexpr bool _MTS = false, SPC_MTS = false;
constexpr char EFILE[] = "";
#include <bits/stdc++.h>
#define FULL(arg) arg.begin(), arg.end()

// :/

using namespace std;
using tp = long long int;
using vetp = basic_string<tp>;
[[maybe_unused]] constexpr tp ZERO = 0, ONE = 1, INF = -1ull >> 2;
signed STRUGGLING(unsigned long long int);
void MIST();
#if !__NO_MAIN__
int main(int argc, char* argv[]) {
  unsigned long long int t = 0, _t = 1;
  MIST();
  if (_MTS && !SPC_MTS) cin >> _t;
  while (t < _t || SPC_MTS) {
    if (STRUGGLING(++t) != 0) return 0;
  }
  return 0;
}
#endif
#ifdef XCODE
#define bg(...){bin<<"[#"<<__LINE__<<'@'<<++_LT[__LINE__]<<':';BG(__VA_ARGS__);}
size_t _LT[21777]; template<typename _Type>void BG(const _Type&_cur){cout<<' '<<
_cur << ']' << " <<:" << endl; } template<typename _Type,typename... _Other>void
BG(const _Type& _cur, const _Other& ..._other) {cout<< ' '<<_cur;BG(_other...);}
#else
#define bg(...)
#define dputs(...)
#endif

// :/

// :/

signed STRUGGLING([[maybe_unused]] unsigned long long int TEST_NUMBER) {
  tp n, m; cin >> n >> m;
  vetp c(2 * n + 2 * m + 1, 0);
  for (tp i = 1; i <= 2 * n + 2 * m; ++i) cin >> c[i];
  vetp b(n + m + 1, 0);
  for (tp i = 1; i <= n + m; ++i) {
    tp x = i <= n ? 1 + n + m + n : n + 1 + n * 2 + m * 2;
    x -= i;
    b[i] = c[x];
  }
  vector a(n + 1, vetp(m + 1, 0));
  for (tp i = 1; i <= n; ++i) {
    for (tp j = n + m; j > n; --j) {
      if (b[i] == j || b[j] == i) {
        swap(b[i], b[j]);
        a[i][j - n] = 1;
      }
    }
  }
  for (tp i = 1; i <= n; ++i) {
    for (tp j = 1; j <= m; ++j) cout << a[i][j] << ' ';
    cout << '\n';
  }
  return 0;
}

void MIST() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
}

// :\ */
```

---

