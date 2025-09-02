# 题目信息

# Elections

## 题目描述

Elections are taking place in Berland. There are $ n $ candidates participating in the elections, numbered from $ 1 $ to $ n $ . The $ i $ -th candidate has $ a_i $ fans who will vote for him. Additionally, there are $ c $ people who are undecided about their favorite candidate, let's call them undecided. Undecided people will vote for the candidate with the lowest number.

The candidate who receives the maximum number of votes wins the elections, and if multiple candidates receive the same maximum number of votes, the candidate with the lowest number among them wins.

You found these elections too boring and predictable, so you decided to exclude some candidates from them. If you do not allow candidate number $ i $ to participate in the elections, all $ a_i $ of his fans will become undecided, and will vote for the candidate with the lowest number.

You are curious to find, for each $ i $ from $ 1 $ to $ n $ , the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win the elections.

## 说明/提示

In the first test case:

- If all candidates are allowed, candidate number $ 1 $ will receive $ 3 $ votes ( $ 1 $ undecided person will vote for him), candidate number $ 2 $ will receive $ 0 $ votes, and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 1 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 0 $ .
- If candidate number $ 1 $ is not allowed, his $ 2 $ fans will become undecided. Then candidate number $ 2 $ will receive $ 3 $ votes ( $ 3 $ undecided people will vote for him) and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 2 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 1 $ .
- If candidates with numbers $ 1 $ and $ 2 $ are not allowed, candidate number $ 3 $ wins, so the answer for him is $ 2 $ .

In the second test case, candidate number $ 1 $ will win if candidate number $ 2 $ is not allowed to participate.

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5```

# AI分析结果



### 综合分析与结论

**核心思路**  
题目要求每个候选人在最少排除次数下获胜。关键贪心策略如下：  
1. **前置处理**：将初始的 `c` 票加给 `a[1]`，简化后续计算。
2. **必须排除前驱**：对候选人 `i`，必须排除前 `i-1` 人，使其成为当前最小编号，获得所有未决定票。
3. **后缀最大值判断**：排除前驱后，若 `i` 的总票数（前缀和）≥ 后面候选人的最大值，则无需额外排除；否则需排除后面最大值，总次数+1。

**可视化设计**  
- **动画方案**：逐帧显示排除前 `i-1` 人的过程，高亮当前 `i` 的总票数（sum[i]），对比后缀最大值（max_r[i+1]）。若 sum[i] < max_r，再排除后缀最大值，动态更新票数。
- **像素风格**：用不同颜色块表示候选人，当前操作元素高亮，音效提示排除动作及比较结果。
- **交互控制**：支持步进、暂停，调节速度观察决策过程。

---

### 题解清单 (4星及以上)

1. **KSCD_ (5星)**  
   - **亮点**：代码简洁高效，逻辑清晰。直接处理后缀最大值，快速判断每个 `i` 的情况。
   - **关键代码**：预处理后缀最大值，一次遍历完成所有判断。

2. **Lu_xZ (4星)**  
   - **亮点**：明确处理前缀和与后缀最大值的比较，逻辑直白。
   - **个人心得**：强调必须排除前驱，避免因未处理导致无法获得未决定票。

3. **szh_AK_all (4星)**  
   - **亮点**：详细推导贪心策略，代码结构清晰，可读性强。
   - **关键思路**：分情况讨论排除前驱后的总票数是否足够。

---

### 最优思路与代码

**核心贪心逻辑**  
- **前缀和与后缀最大值**：预处理 `sum[i]` 为前 `i` 项和（含初始 `c`），`max_r[i]` 为 `i` 到 `n` 的最大值。
- **决策条件**：对每个 `i`，若 `sum[i] >= max_r[i+1]`，答案为 `i-1`；否则为 `i`。

```cpp
#include <iostream>
#define int long long
using namespace std;
const int N = 2e5 + 10;

int n, c, a[N], sum[N], max_r[N];

void solve() {
    cin >> n >> c;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    a[1] += c; // 初始c加到a[1]
    // 预处理后缀最大值
    max_r[n + 1] = 0;
    for (int i = n; i >= 1; --i)
        max_r[i] = max(max_r[i + 1], a[i]);
    // 计算前缀和
    for (int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + a[i];
    // 找到原始最大值位置
    int max_pos = 1;
    for (int i = 1; i <= n; ++i)
        if (a[i] > a[max_pos]) max_pos = i;
    // 处理每个i的答案
    for (int i = 1; i <= n; ++i) {
        if (i == max_pos) cout << 0 << ' ';
        else if (sum[i] >= max_r[i + 1]) cout << i - 1 << ' ';
        else cout << i << ' ';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}
```

---

### 相似题目与扩展

**同类型题套路**  
- **前缀和+后缀极值**：处理前后依赖关系时常用。
- **贪心排除策略**：通过局部最优选择构造全局解。

**推荐题目**  
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心选择最小堆）
2. **P1223 排队接水**（贪心排序最小等待时间）
3. **P1803 线段覆盖**（贪心选择右端点最小的区间）

---

### 可视化与游戏化设计

**核心交互设计**  
1. **Canvas 绘制**：候选人显示为色块，排除时变灰，当前 `i` 高亮为绿色。
2. **动画流程**：  
   - 步骤1：排除前 `i-1` 人，显示 `sum[i]`。
   - 步骤2：比较 `sum[i]` 与 `max_r[i+1]`，若不满足则排除最大后缀，总次数+1。
3. **音效与反馈**：  
   - 正确排除时播放清脆音效，错误时低沉音效。
   - 背景音乐为 8-bit 风格循环曲。

**复古像素风格**  
- **色块设计**：候选人用不同颜色区分，当前操作块闪烁。
- **控制面板**：速度滑块、暂停/继续按钮，支持单步执行观察决策。

---
处理用时：133.79秒