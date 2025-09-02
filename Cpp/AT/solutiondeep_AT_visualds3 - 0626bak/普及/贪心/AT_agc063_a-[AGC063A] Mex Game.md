# 题目信息

# [AGC063A] Mex Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc063/tasks/agc063_a

`A`, `B` からなる長さ $ N+1 $ の文字列 $ S\ =\ S_0\cdots\ S_N $ が与えられます． 各 $ k=1,\ \ldots,\ N $ に対して次の問題を解いてください：

> Alice と Bob が集合 $ X $ を使ってゲームをします．$ X $ ははじめ空集合で，$ t=1,\ldots,\ k $ の順に次の行動を行います．
> 
> - $ t $ が奇数ならば，Alice が非負整数 $ x $ を選び，$ X $ を $ X\cup\ \{x\} $ に置き換える．
> - $ t $ が偶数ならば，Bob が非負整数 $ x $ を選び，$ X $ を $ X\cup\ \{x\} $ に置き換える．
>  
> $ k $ 回すべての行動が終わった時点での $ \mathrm{mex}(X) $ を $ x $ とするとき，文字 $ S_x $ が `A` ならば Alice が，$ S_x $ が `B` ならば Bob が勝者となります．集合 $ X $ の要素数は $ k $ 以下であるため，$ x\ =\ \mathrm{mex}(X)\ \leq\ k $ が成り立つ（したがって文字 $ S_x $ が存在する）ことに注意してください．
> 
> 両者が最適に行動した場合の勝者の名前を出力してください．

   $ \mathrm{mex}(X) $ とは？ 非負整数からなる有限集合 $ X $ に対し，$ x\notin\ X $ を満たす最小の非負整数 $ x $ を $ \mathrm{mex}(X) $ と定義します．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ S $ は `A`, `B` からなる長さ $ N+1 $ の文字列である．
 
### Sample Explanation 1

$ k=1 $ とした場合のゲームの進行例の一例を次に示します． - Alice が $ x=10 $ を選ぶ． - $ \mathrm{mex}(X)=\mathrm{mex}(\lbrace\ 10\rbrace)\ =\ 0 $ であり，$ S_0 $ は `A` なので，Alice が勝利する． $ k=2 $ とした場合のゲームの進行例の一例を次に示します． - Alice が $ x=2 $ を選ぶ． - Bob が $ x=0 $ を選ぶ． - $ \mathrm{mex}(X)=\mathrm{mex}(\lbrace\ 0,2\rbrace)\ =\ 1 $ であり，$ S_1 $ は `B` なので，Bob が勝利する．

## 样例 #1

### 输入

```
2

ABB```

### 输出

```
Alice

Bob```

## 样例 #2

### 输入

```
4

AAAAA```

### 输出

```
Alice

Alice

Alice

Alice```

## 样例 #3

### 输入

```
7

BBAABABA```

### 输出

```
Bob

Bob

Alice

Bob

Alice

Bob

Alice```

# AI分析结果



## 算法分类
**博弈论、贪心策略**

---

## 题解思路与解决难点

### 核心思路
- **问题转化**：通过分析最优策略，发现 Alice 和 Bob 会分别优先消除对方的有利字符（即最小的对方字符下标），最终胜负取决于前 `k+1` 个字符中 `A` 和 `B` 的数量对比。
- **关键观察**：若 `A` 的数量 ≥ `B` 的数量，则 `mex(X)` 对应的字符更可能是 `A`，Alice 胜；反之 Bob 胜。Alice 作为先手，在数量相等时仍能获胜。

### 解决难点
- **最优策略推导**：双方的最优操作是消除对方字符的最小下标，最终剩下的第一个未被消除的字符即为 `mex(X)`。
- **复杂度优化**：直接统计 `A` 和 `B` 的数量，时间复杂度优化至 `O(N)`，无需复杂模拟。

---

## 题解评分（≥4星）

### [5星] chinazhanghaoxun
- **亮点**：代码简洁，直接统计字符数量，思路清晰，可读性高。
- **代码片段**：
  ```cpp
  (s[i]=='A') ? cnta++ : cntb++;
  if (cnta >= cntb) puts("Alice");
  ```

### [4星] yuheng_wang080904
- **亮点**：详细推导奇偶轮次对操作次数的影响，逻辑严谨。
- **代码片段**：
  ```cpp
  cnta += (s[i] == 'A');
  cntb += (s[i] == 'B');
  ```

### [4星] pengbubu
- **亮点**：结合 `mex` 定义解释问题，代码轻量，注释清晰。
- **代码片段**：
  ```cpp
  if (Alice >= Bob) printf("Alice\n");
  ```

---

## 最优思路提炼
- **贪心策略**：双方每次选择对方字符的最小下标，最终胜负由字符数量决定。
- **统计法**：遍历字符串，动态维护 `A` 和 `B` 的计数，直接比较即可。

---

## 类似题目推荐
1. **P4137 Rmq Problem**：涉及 `mex` 查询，需结合数据结构优化。
2. **CF1537E2 Erase and Extend**：贪心策略优化字符串构造。
3. **AT_abc194E Mex Min**：滑动窗口求最小 `mex`，需统计频率。

---

## 个人心得摘录
- **边界处理**：需注意初始字符的统计，如 `i=0` 的字符必须计入。
- **顿悟点**：最优策略下，胜负仅由数量对比决定，无需模拟具体操作。

---

## 可视化设计

### 算法演示
- **动态柱状图**：展示 `A` 和 `B` 的数量随 `k` 增加的变化，当 `A` 柱 ≥ `B` 时高亮 Alice。
- **关键步骤**：每一步显示当前字符的 `A/B` 归属，更新计数器后比较结果。

### 复古游戏化设计
- **像素风格**：字符显示为 8-bit 方块，Alice 和 Bob 为像素小人，消除对方颜色块。
- **音效设计**：
  - **操作音效**：每次消除时播放短促“哔”声。
  - **胜利音效**：Alice 胜利时播放上扬音调，Bob 则低沉音调。
- **自动演示**：按 `k` 逐步推进，自动显示统计结果，速度可调。

### 代码片段（Canvas 绘制）
```javascript
// 伪代码：绘制柱状图
function drawBars(cntA, cntB) {
  ctx.fillStyle = '#FF0000'; // A 红色
  ctx.fillRect(x, height - cntA * 10, 30, cntA * 10);
  ctx.fillStyle = '#0000FF'; // B 蓝色
  ctx.fillRect(x + 40, height - cntB * 10, 30, cntB * 10);
}
```

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, cntA = 0, cntB = 0;
    string s;
    cin >> n >> s;
    for (int i = 0; i <= n; ++i) {
        (s[i] == 'A') ? cntA++ : cntB++;
        if (i > 0) {
            cout << (cntA >= cntB ? "Alice\n" : "Bob\n");
        }
    }
    return 0;
}
```

---
处理用时：112.28秒