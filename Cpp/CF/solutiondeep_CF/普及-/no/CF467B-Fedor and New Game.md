# 题目信息

# Fedor and New Game

## 题目描述

After you had helped George and Alex to move in the dorm, they went to help their friend Fedor play a new computer game «Call of Soldiers 3».

The game has $ (m+1) $ players and $ n $ types of soldiers in total. Players «Call of Soldiers 3» are numbered form $ 1 $ to $ (m+1) $ . Types of soldiers are numbered from $ 0 $ to $ n-1 $ . Each player has an army. Army of the $ i $ -th player can be described by non-negative integer $ x_{i} $ . Consider binary representation of $ x_{i} $ : if the $ j $ -th bit of number $ x_{i} $ equal to one, then the army of the $ i $ -th player has soldiers of the $ j $ -th type.

Fedor is the $ (m+1) $ -th player of the game. He assume that two players can become friends if their armies differ in at most $ k $ types of soldiers (in other words, binary representations of the corresponding numbers differ in at most $ k $ bits). Help Fedor and count how many players can become his friends.

## 样例 #1

### 输入

```
7 3 1
8
5
111
17
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 3 3
1
2
3
4
```

### 输出

```
3
```

# AI分析结果

### 题目翻译
# 费奥多尔与新游戏

## 题目描述
在你帮助乔治和亚历克斯搬进宿舍后，他们又去帮助他们的朋友费奥多尔玩一款新电脑游戏《士兵召唤 3》。

这款游戏共有 $ (m + 1) $ 名玩家和 $ n $ 种士兵。《士兵召唤 3》的玩家编号从 $ 1 $ 到 $ (m + 1) $，士兵类型编号从 $ 0 $ 到 $ n - 1 $。每位玩家都有一支军队。第 $ i $ 位玩家的军队可以用非负整数 $ x_{i} $ 来描述。考虑 $ x_{i} $ 的二进制表示：如果 $ x_{i} $ 的第 $ j $ 位为 $ 1 $，那么第 $ i $ 位玩家的军队就拥有第 $ j $ 种类型的士兵。

费奥多尔是游戏中的第 $ (m + 1) $ 位玩家。他认为，如果两名玩家的军队最多只有 $ k $ 种类型的士兵不同（换句话说，对应数字的二进制表示最多只有 $ k $ 位不同），那么这两名玩家就可以成为朋友。请帮助费奥多尔计算有多少名玩家可以成为他的朋友。

## 样例 #1
### 输入
```
7 3 1
8
5
111
17
```
### 输出
```
0
```

## 样例 #2
### 输入
```
3 3 3
1
2
3
4
```
### 输出
```
3
```

### 算法分类
位运算

### 综合分析与结论
这些题解的核心思路都是将问题转化为比较两个数二进制表示中不同位的数量，若不同位数量不超过 $k$，则对应的玩家可以成为朋友。各题解的主要区别在于计算二进制中 $1$ 的个数的方法。

- **思路对比**：大部分题解都是通过异或运算得到两个数二进制表示中不同位组成的数，再统计该数中 $1$ 的个数；部分题解直接逐位比较两个数的二进制位。
- **算法要点**：主要算法要点是异或运算和统计二进制中 $1$ 的个数。部分题解使用了内置函数 `__builtin_popcount()` 或 `std::bitset` 来简化统计过程，其他题解则通过短除法或位运算手动实现。
- **解决难点**：主要难点在于如何高效地统计二进制中 $1$ 的个数，不同的实现方法在代码复杂度和效率上有所差异。

### 题解评分与推荐
- **Lucky_Cloud（5星）**：
    - **关键亮点**：思路清晰，直接将问题转化为异或运算后统计 $1$ 的个数，并使用内置函数 `__builtin_popcount()` 简化代码，代码简洁高效。
- **Patricky（4星）**：
    - **关键亮点**：提供了两种统计二进制中 $1$ 的个数的方法，即 `std::bitset<xx>(x).count()` 和 `__builtin_popcount(x)`，并对不同方法的适用场景进行了说明，具有一定的参考价值。
- **bigclever（4星）**：
    - **关键亮点**：思路清晰，手动实现了统计二进制中 $1$ 的个数的函数，代码逻辑简单易懂。

### 重点代码
#### Lucky_Cloud
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
int n, m, k, a[N], ans;

int main() {
    cin >> n >> m >> k;
    m++;
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 1; i < m; i++) 
        if (__builtin_popcount(a[i] ^ a[m]) <= k)
            ans++;
    cout << ans;
    return 0;
}
```
**核心实现思想**：先读取输入的 $n$、$m$、$k$ 和每个玩家的军队编号，然后通过异或运算得到两个玩家军队编号二进制表示中不同位组成的数，使用 `__builtin_popcount()` 函数统计该数中 $1$ 的个数，若不超过 $k$，则答案加 $1$。

#### Patricky
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0), ios::sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> diff(m);
  for (int i = 0; i < m; ++i) {
    cin >> diff[i];
  }

  int x;
  cin >> x;
  bitset<20> X(x);

  int ans = 0;
  for (int i = 0; i < m; ++i) {
    ans += (int)(X ^ bitset<20>(diff[i])).count() <= k;
  }

  cout << ans << "\n";

  return 0 ^ 0;
}
```
**核心实现思想**：先读取输入的 $n$、$m$、$k$ 和每个玩家的军队编号，将费奥多尔的军队编号用 `std::bitset` 表示，然后对每个其他玩家的军队编号也用 `std::bitset` 表示，通过异或运算得到不同位组成的 `std::bitset`，使用 `count()` 方法统计其中 $1$ 的个数，若不超过 $k$，则答案加 $1$。

#### bigclever
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005];
int cal(int x,int y){//计算x和y在二进制下有几位不同
    int cnt = 0;
    //注意当x和y均变为0时才退出循环
    for(;x||y;x >>= 1,y >>= 1) cnt += (x & 1 != y & 1);
    return cnt;
}
int main(){
    int n, m, k, ans = 0;
    cin >> n >> m >> k;
    for(int i = 1; i <= m + 1; i++) cin >> a[i];
    for(int i = 1; i <= m; i++) ans += (cal(a[i], a[m + 1]) <= k);
    cout << ans;
    return 0;
}
```
**核心实现思想**：先定义一个函数 `cal()` 用于计算两个数二进制表示中不同位的数量，通过逐位比较并统计不同位的个数。然后读取输入的 $n$、$m$、$k$ 和每个玩家的军队编号，对每个其他玩家的军队编号调用 `cal()` 函数，若不同位数量不超过 $k$，则答案加 $1$。

### 最优关键思路或技巧
- 使用异或运算得到两个数二进制表示中不同位组成的数，再统计该数中 $1$ 的个数，将问题简化。
- 利用内置函数 `__builtin_popcount()` 或 `std::bitset` 来高效统计二进制中 $1$ 的个数，减少代码复杂度。

### 拓展思路
同类型题目通常涉及二进制位的操作和比较，例如判断两个二进制数的相似度、统计二进制数中特定模式的数量等。类似算法套路包括使用位运算进行状态压缩、利用异或运算的性质解决问题等。

### 推荐题目
- [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
- [P1888 三角函数](https://www.luogu.com.cn/problem/P1888)
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)

### 个人心得
题解中未包含个人心得。

---
处理用时：42.33秒