# [CEOI 2013] 停车场 / Splot

## 题目背景

翻译自 [CEOI 2013 Day 1](https://ceoi2013.hsin.hr/tasks/tasks_day1.pdf)。

亚得里亚海沿岸和岛屿都有各种形状和大小的美丽沙滩。然而，许多沙滩无法通过汽车到达。为了满足不断增长的需求，沿海附近的一片巨大空地被改建成停车场。

由于参与设计的所有建筑师都具有电气工程背景，想着怎么着自己学过的专业也得用上，于是停车场的布局就类似于在设计电路时常用的串并联图。

停车场由停车位和连接它们的双向道路组成。每条道路连接两个不同的停车位，每一对停车位之间最多只能通过一条道路连接。每个停车位在任何时刻最多只能停放一辆汽车。其他车辆不能通过被占用的停车位行驶。

![](https://cdn.luogu.com.cn/upload/image_hosting/j207s329.png)
$$\text{图 1：构建停车图的规则，对应下面的三点}$$

串并联停车场（也称为 splot，下文称为停车图）是一种由称为源点和终点的两个特定停车位构成的停车场，它是通过使用串并联组合规则从单个停车位构建而成的。每个停车图可以通过编码来指定其结构和停放车辆的位置，编码是一个描述其结构的字符序列。有效的停车图及其编码按照以下递归方式定义：

1. 只包含一个停车位且没有道路的停车场是一个有效的停车图。这个单个停车位既是停车图的源点也是终点。如果停车位为空，则该停车图的编码为小写字母 `o`，如果停车位被汽车占用，则编码为小写字母`x`。
   - ![](https://cdn.luogu.com.cn/upload/image_hosting/x6vficzn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

2. 如果 $G_1$ 和 $G_2$ 是两个有效的停车图，它们的串联组合 $G$ 也是一个停车图。串联组合是通过在 $G_1$ 的终点和 $G_2$ 的源点之间添加一条道路来获得的。新获得的停车图 $G$ 的源点是 $G_1$ 的源点，而终点是 $G_2$ 的终点。如果 $E_1$ 和 $E_2$ 分别是停车图 $G_1$ 和 $G_2$ 的编码，则 $G$ 的编码为 `SE1E2#`。换句话说，编码是通过连接大写字母 `S`、组成它的停车图的编码和井号 `#` 获得的。
   - ![](https://cdn.luogu.com.cn/upload/image_hosting/bzrozfho.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

3. 如果 $G_1$ 和 $G_2$ 是两个有效的停车图，它们的并联组合 $G$ 也是一个有效的停车图。并联组合是通过添加两个新的停车位 $s$ 和 $t$，添加从 $s$ 到 $G_1$ 和 $G_2$ 的源之间的道路，以及从 $t$ 到 $G_1$ 和 $G_2$ 的终端之间的道路得到的。新获得的停车图G的源是新添加的停车位 $s$，而 $G$ 的终端是新添加的停车位 $t$。如果 $E_1$ 和 $E_2$ 分别是停车图 $G_1$ 和 $G_2$ 的编码，而 $E_s$ 和 $E_t$ 是源 $s$ 和终端 $t$ 的编码（如果相应的空间为空，则为小写字母 `o`，否则为小写字母 `x`），则 $G$ 的编码为 `PEs|E1E2|Et#`。换句话说，编码是通过连接大写字母 `P`，源停车位的编码，竖线符号 `|`，被组合的停车图的编码，另一个竖线符号 `|`，终端停车位的编码，最后是井号 `#` 得到的。
   - ![](https://cdn.luogu.com.cn/upload/image_hosting/czj2m8t8.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

![](https://cdn.luogu.com.cn/upload/image_hosting/6gyst5bp.png)
$$\text{图2：与下面第一个测试示例对应的停车图}$$

例如，上图中给出的停车图的编码是 `Po|Px|Sxo#Soo#|o#Soo#|o#`（译者注：`{Po|[Px|(Sxo#)(Soo#)|o#](Soo#)|o#}`）。请注意，停车图 $G$ 的编码中小写字母（`o` 或 `x`）的数量始终与 $G$ 中的停车位数量相同，并且停车图中的停车位与其编码中的小写字母之间存在一一对应关系。停车场只有一个出口，它就在整个停车图的**源停车位**。如果车辆可以通过一些道路和空的停车位到达源停车位，即它可以离开这个停车图，则我们称该车辆未被阻挡。例如，在上面的停车图中，两辆车都没有被阻挡，但是如果我们将一辆车停在停车图的终端（最右边的节点）上，则其中一辆车将被阻挡。允许将车停在停车图的源停车位上（但是如果这样做，停车图中的所有其他车辆都将被阻挡）。

## 题目描述

停车场的运营商希望以一种方式安排进站的车辆，让图中没有车辆被阻挡。

编写一个程序，计算可以停放在给定停车场的最大汽车总数，（**包括已经在那里的汽车**），使它没有任何汽车被阻挡，也不会移动任何已经在那里的车。此外，程序应该**找到一种方法**来安排停车图中最大数量的汽车。

## 说明/提示

样例解释见题目描述最后一趴。

如果输出不正确或不完整，但第一行输出（最大汽车数量）是正确的，你将获得相应测试点 $80\%$ 的分数。

在 $30\%$ 的测试点中，splot 中的停车位总数最多为 $20$ 个。

在另外 $40\%$ 的测试点中，splot 为空，即输入不包含字母 `x`。

对于 $100\%$ 的数据，给定的 splot 的编码最多包含 $10$ 万个字符。

SPJ 提供者：@[cff_0102](https://www.luogu.com.cn/user/542457) 。

## 样例 #1

### 输入

```
Po|Px|Sxo#Soo#|o#Soo#|o#```

### 输出

```
3
Po|Px|Sxo#Sox#|o#Soo#|o#```

## 样例 #2

### 输入

```
Po|SPo|oo|o#Px|oo|o##Po|Sxo#Po|ox|o#|o#|o#```

### 输出

```
7
Po|SPo|xx|o#Px|ox|o##Po|Sxx#Po|ox|o#|o#|o#```

# 题解

## 作者：cff_0102 (赞：0)

由于停车图是**递归定义**的，因此有必要为问题找到**递归公式**。考虑串联和并联组合后，需要调用其他需要计算的函数。对于给定停车图的所有子图 $G$，计算对应的下面四个函数值，每个函数都**代表的是可以停放在图 $G$ 中的汽车总数**（包括已经停在那里的汽车），使每辆停放的汽车都能以某种方式从 $G$ 中出去。这些函数之间的区别主要在于汽车如何精确地从 $G$ 中出去：
- $\texttt{FORWARD[G]}$: 每辆停放的汽车都能通过 $G$ 的源节点离开。
- $\texttt{BACKWARD[G]}$: 每辆停放的汽车都能通过 $G$ 的终端节点离开。
- $\texttt{BOTH[G]}$: 每辆停放的汽车可以通过 $G$ 的源节点或终端节点离开。
- $\texttt{THROUGH[G]}$: 与前一种情况相同，但是另外还可以从 $G$ 的源到终端，即存在由空停车位组成的路径连接 $s$ 和 $t$。

在上述所有函数中，可以使用特殊符号或数字（例如 $-\infty$）来表示对于已经停放在 $G$ 中的车辆，怎么样都无法到达这种情况。

此外，为了使公式更简单，我们定义一个对于子图 $G$ 的函数：
- $\texttt{NONE[G]}$: 如果 $G$ 为空，则为 $0$，否则为 $-\infty$。

现在，需要为上述每个函数找到递归公式。这里详细解释了函数 $\texttt{FORWARD}$ 的递归公式，并列出了其他函数的公式。大家可以自行验证其他公式。此外，会用到 $\texttt{THROUGH}\le\texttt{FORWARD},\texttt{BACKWARD}\le\texttt{BOTH}$ 这个很容易推出的式子，来减少需要考虑的情况数量。这里重申一遍，每个函数都**代表的是在这种情况下，可以停放在图 $G$ 中的汽车总数**。在下文中，五个函数分别简称为 $\texttt{F,B,A,T,N}$。

1. 如果该图只包含一个节点，则 $\texttt{F,B,A}$ 的值始终为 $1$，而 $\texttt{T,N}$ 的值要么为 $0$（如果这个节点没有车），要么为 $-\infty$（这个节点停了车）。
2. 假设我们串联 $G_1,G_2$ 得到 $G$，并想要计算它的 $\texttt{F}$ 函数值。有两种可能性：至少有一辆汽车停在 $G_2$ 中，或者 $G_2$ 为空。在第一种情况下，必须要有一条路径让 $G_1$ 中的汽车全部在源点退出，因此，在此情况下最多可以停放的汽车数量为 $\texttt{T(}G_1\texttt{)+F(}G_2\texttt{)}$。在第二种情况下，最多可以停放的汽车数量是 $\texttt{F(}G_1\texttt{)+N(}G_2\texttt{)}$，因为 $G_2$ 必须为空，并且 $\texttt{F(}G_1\texttt{)}$ 给出了该情况下最佳的安排。
3. 现在，假设 $G$ 是并联组合的结果，并且我们要计算函数 $\texttt{F}$ 的值。并联组合更为复杂，因为我们还需要考虑新添加的源和终端是怎么样的。根据源和终端是否停了车，分为三种情况：
   1. 源被占用，终点空闲，此时，$G_1$ 和 $G_2$ 都必须为空。$\texttt{F(G)}$ 的值为 $1+\texttt{N(}G_1\texttt{)}+\texttt{N(}G_2\texttt{)}$。
   2. 源和终点都是空闲的：现在，来自 $G_1$ 和 $G_2$ 的汽车可以直接向前退出，或者它们可以从其中一个的两侧退出，而另一个则具有从终端到汇点的路径。因此，$\texttt{F(G)}$ 的值是 $\texttt{F(}G_1\texttt{)}+\texttt{F(}G_2\texttt{)},\texttt{B(}G_1\texttt{)}+\texttt{T(}G_2\texttt{)},\texttt{T(}G_1\texttt{)}+\texttt{B(}G_2\texttt{)}$ 中最大的一个。
   3. 源空闲，终点被占用：其中一个子图必须要保证停在终点的车辆可以退出到源，而另一个子图的所有汽车都需要向前退出。因此，$\texttt{F(G)}$ 的值为 $1+\texttt{T(}G_1\texttt{)}+\texttt{F(}G_2\texttt{)},1+\texttt{F(}G_1\texttt{)}+\texttt{T(}G_2\texttt{)}$ 中更大的一个。

即使找到了递归计算函数的所有可能规则，由于需要考虑的情况数量巨大，实现（特别是重构最优排列时）仍然容易出错。一个寄巧可以极大地简化它的实现，那就是使用常量来定义上述递归规则，见下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/d0tcpyxn.png)

上述表格将递归计算函数的规则编码为在 C++ 中的简单整数数组。例如，第二列中的 `{FORWARD，0，1，THROUGH，FORWARD}` 表示当 $G$ 是 $G_1$ 和 $G_2$ 的并行组合，并且正在计算 $\texttt{F}$ 函数时，我们需要考虑终点是否为空，终端是否被占用，$G_1$ 的 $\texttt{T}$ 值是多少，以及 $G_2$ 的 $\texttt{F}$ 值是几。

通过上述定义的常量，解决方案变得简单但仍然很长（不过还是好多了），需要实现一个解析器来将编码转换为类似树形结构的形式，然后需要递归遍历该树来计算每个函数。为了重构最优排列，我们需要记住用于获得相应函数最大值的规则索引。

下面是官方题解代码：

```cpp
// CEOI 2013 - Task: Splot - Solution
// Author: Ante Derek

#include <cstdio>
#include <cassert>

using namespace std;

const int MAX = 1000000;
const int NEGINF = -(1<<28);
const int CFF_0102 = 542457;

enum FunctionType {FORWARD=0, BACKWARD=1, BOTH=2, THROUGH=3, NONE=4};

static const int S_RULE[][3] = {
  {FORWARD, FORWARD, NONE},
  {FORWARD, THROUGH, FORWARD},
  {BACKWARD, NONE, BACKWARD},
  {BACKWARD, BACKWARD, THROUGH},
  {BOTH, FORWARD, BACKWARD}, 
  {BOTH, BOTH, THROUGH},
  {BOTH, THROUGH, BOTH},
  {THROUGH, THROUGH, THROUGH},
  {NONE, NONE, NONE},
  {-1, -1, -1}
};

static const int P_RULE[][5] = {
  {FORWARD, 1, 0, NONE, NONE},
  {FORWARD, 0, 0, FORWARD, FORWARD},
  {FORWARD, 0, 0, THROUGH, BOTH},
  {FORWARD, 0, 0, BOTH, THROUGH},
  {FORWARD, 0, 1, THROUGH, FORWARD},
  {FORWARD, 0, 1, FORWARD, THROUGH},
  {BACKWARD, 0, 1, NONE, NONE},
  {BACKWARD, 0, 0, BACKWARD, BACKWARD},
  {BACKWARD, 0, 0, THROUGH, BOTH},
  {BACKWARD, 0, 0, BOTH, THROUGH},
  {BACKWARD, 1, 0, THROUGH, BACKWARD},
  {BACKWARD, 1, 0, BACKWARD, THROUGH},
  {BOTH, 1, 1, NONE, NONE},
  {BOTH, 1, 0, BACKWARD, BACKWARD},
  {BOTH, 0, 1, FORWARD, FORWARD},
  {BOTH, 0, 0, BOTH, BOTH},
  {THROUGH, 0, 0, THROUGH, BOTH},
  {THROUGH, 0, 0, BOTH, THROUGH},
  {NONE, 0, 0, NONE, NONE},
  {-1, -1, -1, -1}
};

class Splot {
  enum SplotType {NODE, SERIES, PARALLEL} type;
  int source;
  int sink;
  Splot *first;
  Splot *second;
  int result[5];
  int how[5];
  Splot(SplotType _type, 
        int _source=0, 
        int _sink=0,
        Splot* a = NULL,
        Splot* b = NULL):
    type(_type),
    source(_source),
    sink(_sink),
    first(a),
    second(b) {
    for (int i=0; i<5; i++)
      how[i] = result[i] = -1;    
  }
public:
  ~Splot() {
    if (first)
      delete first;
    if (second)
      delete second;
  }
  static Splot* new_node(char c) {
    return new Splot(NODE, c=='x', c=='x');
  }
  static Splot* new_series(Splot* a, Splot *b) {
    return new Splot(SERIES, 0, 0, a, b);
  }
  static Splot* new_parallel(char s, char t, Splot* a, Splot* b) {
    return new Splot(PARALLEL, s=='x', t=='x', a, b);
  }
  int node_result(int f) {
    if (f == FORWARD || f == BACKWARD || f == BOTH)
      return result[f] = 1;
    return result[f] = source?NEGINF:0;
  }
  Splot* rec_node(int f) const {
    if (f == FORWARD || f == BACKWARD || f == BOTH)
      return new_node('x');
    else
      return new_node('o');
  }
  int series_result(int f) {
    int &what = result[f];
    what = NEGINF;
    for (int l=0; S_RULE[l][0]!=-1; l++) {
      if (S_RULE[l][0] != f)
        continue ;
      int left = first->get_result(S_RULE[l][1]);
      int right = second->get_result(S_RULE[l][2]);
      if (left != NEGINF && right != NEGINF && left+right > what) {
        how[f] = l;
        what = left+right;
      }
    }
    return what;
  }
  Splot *rec_series(int f) const {
    int l = how[f];
    return new_series(first->reconstruct(S_RULE[l][1]), 
                      second->reconstruct(S_RULE[l][2]));
  }
  int parallel_result(int f) {
    int &what = result[f];
    what = NEGINF;
    for (int l=0; P_RULE[l][0]!=-1; l++) {
      if (P_RULE[l][0] != f)
        continue ;
      int news = P_RULE[l][1];
      int newt = P_RULE[l][2];
      if ((source && !news) || (sink && !newt))
        continue ;      
      int left = first->get_result(P_RULE[l][3]);
      int right = second->get_result(P_RULE[l][4]);
      if (left != NEGINF && right != NEGINF && left+right+news+newt > what) {
        how[f] = l;
        what = left+right+news+newt;
      }
    }
    return what;
  }
  Splot *rec_parallel(int f) const {
    int l = how[f];
    return new_parallel(P_RULE[l][1]?'x':'o',
                        P_RULE[l][2]?'x':'o',
                        first->reconstruct(P_RULE[l][3]), 
                        second->reconstruct(P_RULE[l][4]));
  }
  int get_result(int f) {
    if (result[f] != -1)
      return result[f];
    if (type == NODE) 
      return node_result(f);
    else if (type == SERIES)
      return series_result(f);
    else
      return parallel_result(f);
  }
  Splot* reconstruct(int f) const {
    if (type == NODE) 
      return rec_node(f);
    else if (type == SERIES)
      return rec_series(f);
    else
      return rec_parallel(f);
  }
  void print() const {
    if (type == NODE)
      printf("%c", source?'x':'o');
    else if (type == SERIES) {
      printf("S");
      first->print();
      second->print();
      printf("#");
    } else {
      printf("P%c|", source?'x':'o');
      first->print();
      second->print();
      printf("|%c#", sink?'x':'o');
    }
  }
};

class Parser {
  const char *s;
  int p;
  Splot* do_parse() {
    if (s[p] == 'o' || s[p] == 'x')
      return Splot::new_node(s[p++]);
    if (s[p] == 'S') {
      p++;
      Splot *first = do_parse();
      Splot *second = do_parse();
      p++;
      return Splot::new_series(first, second);
    }
    assert(s[p] == 'P');
    char sc = s[p+1];
    p += 3;
    Splot *first = do_parse();
    Splot *second = do_parse();
    char tc = s[p+1]; 
    p += 3;
    return Splot::new_parallel(sc, tc, first, second);
  }
 public:
  Parser(const char *_s):
    s(_s), p(0) {
  }
  Splot* parse() {
    assert(p == 0);
    Splot *r = do_parse();
    assert(s[p] == 0 || s[p] == '\n');
    return r;
  }
};

int main() {
  static char s[MAX+1];
  scanf("%s", s);
  Splot* splot = Parser(s).parse();
  int best = splot->get_result(FORWARD);
  printf("%d\n", best);
  Splot *filled = splot->reconstruct(FORWARD);
  filled->print();
  printf("\n");
  delete splot;
  delete filled;
  return 0;
}
```


最后附一份官方出题组的出题背景：

![](https://cdn.luogu.com.cn/upload/image_hosting/sw9lc3r9.png)

---

