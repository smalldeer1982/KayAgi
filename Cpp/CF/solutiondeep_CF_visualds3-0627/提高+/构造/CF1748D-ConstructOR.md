# 题目信息

# ConstructOR

## 题目描述

You are given three integers $ a $ , $ b $ , and $ d $ . Your task is to find any integer $ x $ which satisfies all of the following conditions, or determine that no such integers exist:

- $ 0 \le x \lt 2^{60} $ ;
- $ a|x $ is divisible by $ d $ ;
- $ b|x $ is divisible by $ d $ .

Here, $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 说明/提示

In the first test case, $ x=18 $ is one of the possible solutions, since $ 39|18=55 $ and $ 12|18=30 $ , both of which are multiples of $ d=5 $ .

In the second test case, $ x=14 $ is one of the possible solutions, since $ 8|14=6|14=14 $ , which is a multiple of $ d=14 $ .

In the third and fourth test cases, we can show that there are no solutions.

## 样例 #1

### 输入

```
8
12 39 5
6 8 14
100 200 200
3 4 6
2 2 2
18 27 3
420 666 69
987654321 123456789 999999999```

### 输出

```
18
14
-1
-1
0
11
25599
184470016815529983```

# AI分析结果



---

## 唯一算法分类
**位运算与贪心构造**

---

## 题解思路与解决难点

### 核心思路
1. **判无解条件**  
   - 若 `lowbit(d) > min(lowbit(a), lowbit(b))` 则无解。因为此时 `d` 的最低有效位比 `a|b` 更高，无法通过位运算补足。
   - `lowbit(x)` 表示 `x` 的二进制表示中最右侧的 `1` 的位置。

2. **构造 x 的方法**  
   - 计算 `c = a | b`，构造一个覆盖 `c` 所有 `1` 位的 `x`，且 `x` 是 `d` 的倍数。
   - 从低位到高位遍历 `c` 的每一位，若当前位需要置 `1` 但 `x` 未覆盖，则通过将 `d` 左移对齐该位后累加到 `x`。

### 算法难点
1. **位对齐操作**  
   - 每次添加 `d << (i - k)`（`k` 是 `lowbit(d)`）确保 `x` 的最低有效位正确覆盖。
   - 保证每次操作不破坏已构造的高位。

2. **时间复杂度**  
   - 遍历最多 60 位，时间复杂度为 `O(log(max(a, b, d)))`。

---

## 题解评分（≥4星）

### As_Snow（⭐⭐⭐⭐⭐）
- **亮点**  
  - 代码简洁，直接通过位遍历构造 `x`，逻辑清晰。  
  - 利用 `lowbit` 快速判断无解条件。  
- **关键代码**  
  ```cpp
  for(int i=0;i<30;i++)
      if( ((a|b)>>i&1) && (x>>i&1)==0 )
          if(i<k)return void(puts("-1"));
          else x+=(d<<i-k);
  ```

### jiangtaizhe001（⭐⭐⭐⭐）
- **亮点**  
  - 通过位掩码逐位构造，验证答案正确性。  
  - 使用断言确保构造的 `x` 满足条件。  
- **关键代码**  
  ```cpp
  for(i=0;i<30;i++) if((c&(1<<i))&&!(ans&(1<<i))){
      if(i<cnt){ puts("-1"); return; }
      ans+=(d<<(i-cnt));
  }
  ```

### chroneZ（⭐⭐⭐⭐）
- **亮点**  
  - 直接处理 `res` 作为 `d` 的倍数，无需额外数学工具。  
  - 代码极简，仅需 10 行核心逻辑。  
- **关键代码**  
  ```cpp
  for(int i = c; i < 30; ++i){
      if((res >> i) & 1) continue;
      if(!(((a | b) >> i) & 1)) continue;
      res += (d << (i - c));
  }
  ```

---

## 最优思路提炼
1. **lowbit 快速判解**  
   - 使用 `lowbit` 快速判断 `d` 是否可能覆盖 `a|b` 的二进制位。

2. **贪心位填充**  
   - 从最低位到最高位遍历，用 `d` 的左移对齐操作填充 `c` 中未覆盖的 `1` 位。

3. **构造验证**  
   - 最终构造的 `x` 必须满足 `x | a == x` 且 `x | b == x`，确保 `x` 是 `d` 的倍数。

---

## 类似题目推荐
1. **CF 1516C - Baby Ehab Plays with Permutations**  
   - 位操作与构造验证。

2. **洛谷 P2114 [NOI2014] 起床困难综合症**  
   - 位运算贪心构造最优解。

3. **洛谷 P1582 倒水**  
   - 利用 `lowbit` 分析容器合并条件。

---

## 可视化算法演示
**核心步骤动画设计**  
1. **初始状态**  
   - 展示 `a`、`b`、`d` 的二进制位，高亮 `lowbit` 位置。
2. **逐位填充**  
   - 遍历 `a|b` 的每一位，若该位需置 `1` 但 `x` 未覆盖，添加 `d` 左移后的值。  
   - 动态显示 `x` 的二进制变化，用颜色区分已覆盖和新添加的位。
3. **失败条件**  
   - 当 `d` 的 `lowbit` 过高时，播放失败音效并提示无解。

**复古像素风格**  
- **颜色方案**：8-bit 色调，绿色表示有效位，红色表示冲突位。  
- **音效**：添加位时播放 "beep"，成功时播放 8-bit 胜利音效。  
- **Canvas 绘制**：网格化二进制位，每步更新后刷新渲染。

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll a, b, d;
    cin >> a >> b >> d;
    int k = __builtin_ctzll(d); // lowbit(d)
    if (__builtin_ctzll(a) < k || __builtin_ctzll(b) < k) {
        cout << "-1\n";
        return;
    }
    ll x = 0;
    for (int i = 0; i < 60; ++i) {
        if ((((a | b) >> i) & 1) && !((x >> i) & 1)) {
            if (i < k) {
                cout << "-1\n";
                return;
            }
            x += d << (i - k);
        }
    }
    cout << x << '\n';
}

int main() {
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```

**代码说明**  
- `__builtin_ctzll` 快速计算 `lowbit` 位置。  
- 遍历每一位，动态构造 `x` 并验证覆盖条件。

---
处理用时：79.95秒