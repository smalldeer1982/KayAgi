# 题目信息

# Prime XOR Coloring

## 题目描述

You are given an undirected graph with $ n $ vertices, numbered from $ 1 $ to $ n $ . There is an edge between vertices $ u $ and $ v $ if and only if $ u \oplus v $ is a [prime number](https://en.wikipedia.org/wiki/Prime_number), where $ \oplus $ denotes the [bitwise XOR operator](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Color all vertices of the graph using the minimum number of colors, such that no two vertices directly connected by an edge have the same color.

## 说明/提示

In the first test case, the minimum number of colors is $ 1 $ , because there is only one vertex.

In the second test case, the minimum number of colors is $ 2 $ , because there is an edge connecting $ 1 $ and $ 2 $ ( $ 1 \oplus 2 = 3 $ , which is a prime number).

In the third test case, the minimum number of colors is still $ 2 $ , because $ 2 $ and $ 3 $ can be colored the same since there is no edge between $ 2 $ and $ 3 $ ( $ 2 \oplus 3 = 1 $ , which is not a prime number).

In the fourth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the fifth test case, it can be shown that the minimum number of colors is $ 3 $ .

In the sixth test case, it can be shown that the minimum number of colors is $ 4 $ .

## 样例 #1

### 输入

```
6
1
2
3
4
5
6```

### 输出

```
1
1
2
1 2
2
1 2 2
3
1 2 2 3
3
1 2 2 3 3
4
1 2 2 3 3 4```

# AI分析结果

### 题目内容
# 质数异或染色

## 题目描述
给定一个无向图，有 $n$ 个顶点，编号从 $1$ 到 $n$ 。当且仅当 $u \oplus v$ 是一个[质数](https://en.wikipedia.org/wiki/Prime_number)时，顶点 $u$ 和 $v$ 之间存在一条边，其中 $\oplus$ 表示[按位异或运算符](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

使用最少数量的颜色对图的所有顶点进行染色，使得直接通过边相连的两个顶点颜色不同。

## 说明/提示
在第一个测试用例中，最少颜色数量为 $1$，因为只有一个顶点。

在第二个测试用例中，最少颜色数量为 $2$，因为顶点 $1$ 和 $2$ 之间有一条边（$1 \oplus 2 = 3$，$3$ 是质数）。

在第三个测试用例中，最少颜色数量仍为 $2$，因为 $2$ 和 $3$ 之间没有边（$2 \oplus 3 = 1$，$1$ 不是质数），所以 $2$ 和 $3$ 可以染成相同颜色。

在第四个测试用例中，可以证明最少颜色数量为 $3$。

在第五个测试用例中，可以证明最少颜色数量为 $3$。

在第六个测试用例中，可以证明最少颜色数量为 $4$。

## 样例 #1
### 输入
```
6
1
2
3
4
5
6
```
### 输出
```
1
1
2
1 2
2
1 2 2
3
1 2 2 3
3
1 2 2 3 3
4
1 2 2 3 3 4
```

### 综合分析与结论
所有题解思路核心均为先通过样例发现 $n \geq 6$ 时最少颜色数为 $4$ ，$n \leq 5$ 时直接使用样例给出的染色方案。难点在于证明 $n \geq 6$ 时使用 $4$ 种颜色染色的可行性。各题解通过分析同余类异或结果性质来证明，即若两数对 $4$ 同余，其异或结果必为 $4$ 的倍数，不可能是质数，从而得出按 $i \bmod 4 + 1$ 对顶点 $i$ 染色的方案。

### 所选的题解
- **作者：AKPC (赞：5)**
  - **星级**：5星
  - **关键亮点**：思路清晰，先明确颜色数量范围，通过对 $i$ 节点染上 $(i - 1) \bmod 4 + 1$ 颜色，从理论上严谨证明了 $n \geq 6$ 时颜色数量不会小于 $4$ 也不会大于 $4$ ，逻辑完整。
- **作者：_lmh_ (赞：4)**
  - **星级**：4星
  - **关键亮点**：简洁高效，快速抓住“两整数差为4的倍数则异或也为4的倍数，必为合数”这一关键性质，直接给出四种颜色的万能方案，代码实现简洁明了。
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  #define ll long long
  ll T,n;
  int main(){
      ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
      cin>>T;
      while(T--){
          cin>>n;
          if (n<=5){
              cout<<n/2+1<<endl;
              for (int i=1;i<=n;++i) cout<<i/2+1<<' ';cout<<endl;
          }
          else{
              cout<<4<<endl;
              for (int i=1;i<=n;++i) cout<<(i%4)+1<<' ';cout<<endl;
          }
      }
      return 0;
  }
  ```
  **核心实现思想**：先判断 $n$ 的大小，$n \leq 5$ 时按样例规律输出染色数及方案，$n \gt 5$ 时直接按 $i \bmod 4 + 1$ 输出染色方案。
- **作者：2huk (赞：1)**
  - **星级**：4星
  - **关键亮点**：先翻译题意，使读者更易理解。证明部分清晰，先说明答案必定 $\geq 4$ ，再通过对 $i$ 染色为 $i \bmod 4 + 1$ 证明等号可以取到，逻辑连贯。
  ```cpp
  #include <bits/stdc++.h>

  using namespace std;

  const int N = 1e6 + 10;

  typedef long long ll;

  signed main() {
      int T;
      cin >> T;
      while (T -- ) {
          int n;
          cin >> n;
          if (n == 1) {
              cout << 1 << '\n';
              cout << 1 << '\n';
          }
          else if (n == 2) {
              cout << 2 << '\n';
              cout << 1 << ' ' << 2 << '\n';
          }
          else if (n == 3) {
              cout << 2 << '\n';
              cout << 1 << ' ' << 2 << ' ' << 2 << '\n';
          }
          else if (n == 4) {
              cout << 3 << '\n';
              cout << 1 << ' ' << 2 << ' ' << 2 << ' ' << 3 << '\n';
          }
          else if (n == 5) {
              cout << 3 << '\n';
              cout << 1 << ' ' << 2 << ' ' << 2 << ' ' << 3 << ' ' << 3 << '\n';
          }
          else {
              cout << 4 << '\n';
              for (int i = 1; i <= n; ++ i ) {
                  cout << i % 4 + 1 << ' ';
              }
              cout << '\n';
          }
      }
      return 0;
  }
  ```
  **核心实现思想**：同样根据 $n$ 的大小分类讨论，$n \leq 5$ 按样例输出，$n \gt 5$ 按 $i \bmod 4 + 1$ 输出染色方案。

### 最优关键思路或技巧
通过分析数字间按位异或结果与质数的关系，利用数论中同余类的性质，发现按对 $4$ 取模的同余类进行染色可满足题目要求，这种从样例找规律并结合数学性质证明的思维方式是解题关键。

### 可拓展之处
此类题目属于图染色与数论结合的问题，类似套路为从简单样例入手找规律，利用数论性质如奇偶性、同余关系等证明染色方案的正确性与最优性。同类型题可考虑其他基于数字运算构建图结构并染色的问题，例如基于加法、乘法等运算构建图。

### 相似知识点洛谷题目
- [P1525 关押罪犯](https://www.luogu.com.cn/problem/P1525)：图的染色问题，通过二分图染色解决冲突分配问题，考察对图结构和染色原理的理解。
- [P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)：涉及图的遍历和染色，判断能否用两种颜色对图染色，与本题判断最少颜色数思路类似。
- [P2032 扫描游戏](https://www.luogu.com.cn/problem/P2032)：结合图论与逻辑推理，通过对图的节点状态分析，类似本题根据特定规则对图元素进行处理。

### 个人心得摘录与总结
部分作者提到这是“诈骗题”，意思是乍看可能觉得复杂，但通过分析样例和数字性质能发现较为简单的解法，强调了从简单情况入手找规律在解决构造类问题中的重要性。 

---
处理用时：31.44秒