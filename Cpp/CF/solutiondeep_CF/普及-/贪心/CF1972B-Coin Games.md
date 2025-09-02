# 题目信息

# Coin Games

## 题目描述

There are $ n $ coins on the table forming a circle, and each coin is either facing up or facing down. Alice and Bob take turns to play the following game, and Alice goes first.

In each operation, the player chooses a facing-up coin, removes the coin, and flips the two coins that are adjacent to it. If (before the operation) there are only two coins left, then one will be removed and the other won't be flipped (as it would be flipped twice). If (before the operation) there is only one coin left, no coins will be flipped. If (before the operation) there are no facing-up coins, the player loses.

Decide who will win the game if they both play optimally. It can be proved that the game will end in a finite number of operations, and one of them will win.

## 说明/提示

In the first test case, the game may go as follows.

- Alice chooses the first coin and $ s $ becomes "DDUU".
- Bob chooses the last coin and $ s $ becomes "UDD".
- Alice chooses the first coin and $ s $ becomes "UU".
- Bob chooses the first coin and $ s $ becomes "U".
- Alice chooses the only coin and $ s $ becomes empty.
- Bob can't choose any coin now, and he loses the game.

It can be proved that Bob will always lose if they both play optimally.

## 样例 #1

### 输入

```
3
5
UUDUD
5
UDDUD
2
UU```

### 输出

```
YES
NO
NO```

# AI分析结果



# Coin Games 题解

## 题目重述

桌子上有 $n$ 枚硬币围成一个圆圈，每枚硬币要么正面朝上（记为 `U`），要么反面朝上（记为 `D`）。Alice 和 Bob 轮流进行操作，Alice 先手。每次操作规则如下：

1. 玩家选择一个正面朝上的硬币，移除它，并翻转其相邻的两枚硬币。
2. 若操作前只剩两枚硬币，移除一枚后另一枚不翻转（因为会被翻转两次）。
3. 若操作前只剩一枚硬币，移除后无硬币需翻转。
4. 若操作前无正面朝上的硬币，当前玩家输。

双方均采取最优策略，判断 Alice 是否必胜。

---

## 题解综合分析

### 核心结论
**胜负仅由初始正面朝上硬币的奇偶性决定**：若初始 `U` 的数量为奇数，Alice 必胜；否则必败。

### 关键思路
1. **奇偶性变化规律**：每次操作会移除一个 `U`（奇偶性变化），且翻转相邻硬币可能增加或减少 `U`，但无论何种情况，整体 `U` 的奇偶性必然改变。
2. **博弈过程推导**：若初始 `U` 为奇数，先手总能通过操作将偶数 `U` 留给对手，最终迫使对手面对 `U=0` 的必败态。

### 最优题解摘录

#### 题解作者：yitian_ (⭐⭐⭐⭐⭐)
**亮点**：通过奇偶性变化的严格数学推导，清晰解释胜负条件。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        int n, num=0;
        scanf("%d",&n);
        while(n--) {
            char c; cin >> c;
            if(c=='U') num++;
        }
        cout << (num%2 ? "YES\n" : "NO\n");
    }
    return 0;
}
```

#### 题解作者：cjh20090318 (⭐⭐⭐⭐)
**亮点**：简洁总结多种操作场景，验证奇偶性规律。
```python
T = int(input())
for _ in range(T):
    int(input())
    print('YES' if input().count('U')%2 else 'NO')
```

#### 题解作者：keep_shining (⭐⭐⭐⭐)
**亮点**：列举具体操作场景，明确奇偶性变化的一致性。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int t; cin>>t;
    while(t--) {
        int n, cnt=0; string s;
        cin>>n>>s;
        for(auto c:s) if(c=='U') cnt++;
        cout<<(cnt%2 ? "YES\n" : "NO\n");
    }
    return 0;
}
```

---

## 举一反三

### 类似题目推荐
1. **洛谷 P1246**：博弈中的奇偶性分析。
2. **洛谷 P3150**：基于操作次数奇偶性的胜负判断。
3. **洛谷 P2568**：利用奇偶性优化策略的游戏问题。

### 思维拓展
- **关键观察点**：在博弈问题中，若每次操作必然改变某一关键属性（如奇偶性），则初始状态的该属性可直接决定胜负。
- **调试技巧**：对于复杂规则，可通过暴力模拟小规模样例验证猜想，再推广到一般情况。

---
处理用时：53.17秒