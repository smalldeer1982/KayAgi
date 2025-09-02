# 题目信息

# [USACO20OPEN] Cowntact Tracing B

## 题目描述

由于高传染性的牛传染病 COWVID-19 的爆发，Farmer John 非常担忧他的奶牛们（编号为 $1\ldots N$）的健康。

最近，Farmer John 对他的所有奶牛进行了检测，发现有一部分奶牛对该疾病的检测结果呈阳性。利用牛棚内的视频监控，他得以查看最近的奶牛之间的互动行为，结果发现奶牛们互相打招呼时，她们会握蹄，不幸的是这是一种会将疾病从一头奶牛传播给另一头奶牛的行为。Farmer John 汇总了一个添加了时间戳的清单，每条数据的形式为 $(t,x,y)$，表示在时间 $t$，奶牛 $x$ 与奶牛 $y$ 握了蹄。Farmer John 同时还知道以下信息：

（一）他的农场上恰有一头奶牛最初带有携带疾病（我们将这头奶牛称为“零号病人”）。

（二）一旦一头奶牛被感染，她会在接下来的 $K$ 次握蹄中传染疾病（可能会与同一头奶牛握蹄多次）。握蹄 $K$ 次后，她不再在此后的握蹄中传染疾病（因为此时她意识到了她会传染疾病，于是会仔细地洗蹄）。

（三）一旦一头奶牛被感染，她会持续处于被感染状态。

不幸的是，Farmer John 不知道他的 $N$ 头奶牛中的哪一头是零号病人，也不知道 $K$ 的值！基于他的数据，请帮助他缩小这些未知量的范围。保证至少有一种可能的情况。 

## 说明/提示

### 样例解释 1

唯一可能是零号病人的是奶牛 $1$。对于所有的 $K>0$，奶牛 $1$ 在时刻 $7$ 感染奶牛 $2$，而奶牛 $3$ 和奶牛 $4$ 均不会被感染。 

## 样例 #1

### 输入

```
4 3
1100
7 1 2
5 2 3
6 2 4```

### 输出

```
1 1 Infinity```

# AI分析结果



### 唯一算法分类
暴力枚举、模拟

### 综合分析与结论
**核心思路**：  
暴力枚举每个可能的零号病人和 K 值，模拟握手过程，检查最终感染状态是否符合题意。  
**难点与解决方案**：  
1. **时间顺序处理**：必须按时间戳排序握手事件，确保模拟顺序正确。  
2. **传染次数计算**：每个被感染的牛在 K 次握蹄中会传播疾病，需精确维护剩余传播次数。  
3. **边界条件处理**：当 K 超过最大可能握手次数时输出 `Infinity`，需特殊判断。  

**可视化设计**：  
- **动画方案**：网格展示每头牛的状态，红色表示感染，绿色表示未感染。剩余次数用数字或进度条显示。  
- **高亮逻辑**：当前处理的握手事件高亮，被感染的牛闪烁，剩余次数减少时颜色变淡。  
- **交互功能**：支持暂停/继续/单步执行，可调节模拟速度观察传播细节。  
- **复古像素风**：使用 8-bit 像素牛图标，传染时播放经典 FC 音效，背景音乐循环播放。  

---

### 题解清单（≥4星）
1. **mengleo（5星）**  
   - **亮点**：  
     - 时间排序清晰，感染逻辑处理准确。  
     - 代码结构简洁，变量命名合理。  
     - 正确处理 K 的边界条件（如 `Infinity`）。  
   - **核心代码段**：  
     ```cpp
     for (int i = 1; i <= t; i++) {
         if (cs[lst[i].x] == -1 && cs[lst[i].y] > 0) {
             cs[lst[i].y]--;
             cs[lst[i].x] = k;
         } else if (...) { // 类似处理其他情况 }
     }
     ```

2. **XiaoWhy（4星）**  
   - **亮点**：  
     - 代码可读性高，注释明确。  
     - 通过 `cnt` 数组维护剩余传染次数，逻辑直观。  
   - **核心代码段**：  
     ```cpp
     if (cnt[x] > 0) {
         cnt[x]--;
         if (!st[y]) st[y] = true, cnt[y] = k;
     }
     ```

---

### 最优思路提炼
1. **暴力枚举框架**：  
   - 外层循环枚举零号病人，内层循环枚举 K 值。  
   - 对每个组合模拟感染过程，验证最终状态。  
2. **时间排序预处理**：  
   - 必须按握手时间排序，确保模拟顺序正确。  
3. **状态维护技巧**：  
   - 使用数组记录每头牛的剩余传播次数，初始化为 K。  
   - 每次握手后递减剩余次数，避免重复传染。  

---

### 同类型题与套路
- **常见套路**：  
  - 暴力枚举 + 状态模拟：适用于数据量小且决策有限的场景。  
  - 时间轴排序处理：如「航班预订统计」「会议室安排」。  
- **类似题目**：  
  1. P2921 [USACO08DEC] Trick or Treat on the Farm（状态传播模拟）  
  2. P1034 [NOIP2002 提高组] 传染病控制（树形传播模拟）  
  3. P1141 01 迷宫（多源扩散+预处理）  

---

### 个人心得摘录
- **调试教训**：  
  > "必须严格按时间排序，否则模拟顺序错误导致结果全错。" —— mengleo  
- **优化技巧**：  
  > "K 的上界设为 T+1，直接覆盖 Infinity 情况。" —— XiaoWhy  

---

### 核心代码实现（mengleo 版）
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Event { int t, x, y; };
int n, t, possible_cows = 0, min_k = INT_MAX, max_k = 0;
string infected_status;

int main() {
    cin >> n >> t >> infected_status;
    vector<Event> events(t);
    for (auto &e : events) cin >> e.t >> e.x >> e.y;
    sort(events.begin(), events.end(), [](auto &a, auto &b) { return a.t < b.t; });

    for (int cow = 1; cow <= n; cow++) { // 枚举零号病人
        bool valid_cow = false;
        for (int k = 0; k <= t + 1; k++) { // 枚举 K 值
            vector<int> spread_cnt(n + 1, -1); // -1 表示未感染
            spread_cnt[cow] = k; // 初始感染

            for (auto &e : events) { // 模拟握手
                int &x = e.x, &y = e.y;
                if (spread_cnt[x] != -1 && spread_cnt[x] > 0) {
                    if (spread_cnt[y] == -1) spread_cnt[y] = k;
                    spread_cnt[x]--;
                }
                if (spread_cnt[y] != -1 && spread_cnt[y] > 0) {
                    if (spread_cnt[x] == -1) spread_cnt[x] = k;
                    spread_cnt[y]--;
                }
            }

            bool match = true;
            for (int i = 1; i <= n; i++) {
                bool infected = (infected_status[i-1] == '1');
                if ((spread_cnt[i] >= 0) != infected) match = false;
            }
            if (match) {
                valid_cow = true;
                min_k = min(min_k, k);
                max_k = max(max_k, k);
            }
        }
        if (valid_cow) possible_cows++;
    }

    cout << possible_cows << " " << min_k << " ";
    if (max_k == t + 1) cout << "Infinity";
    else cout << max_k;
    return 0;
}
```

---
处理用时：269.43秒