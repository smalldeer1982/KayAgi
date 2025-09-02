# 题目信息

# Innokenty and a Football League

## 题目描述

Innokenty is a president of a new football league in Byteland. The first task he should do is to assign short names to all clubs to be shown on TV next to the score. Of course, the short names should be distinct, and Innokenty wants that all short names consist of three letters.

Each club's full name consist of two words: the team's name and the hometown's name, for example, "DINAMO BYTECITY". Innokenty doesn't want to assign strange short names, so he wants to choose such short names for each club that:

1. the short name is the same as three first letters of the team's name, for example, for the mentioned club it is "DIN",
2. or, the first two letters of the short name should be the same as the first two letters of the team's name, while the third letter is the same as the first letter in the hometown's name. For the mentioned club it is "DIB".

Apart from this, there is a rule that if for some club $ x $ the second option of short name is chosen, then there should be no club, for which the first option is chosen which is the same as the first option for the club $ x $ . For example, if the above mentioned club has short name "DIB", then no club for which the first option is chosen can have short name equal to "DIN". However, it is possible that some club have short name "DIN", where "DI" are the first two letters of the team's name, and "N" is the first letter of hometown's name. Of course, no two teams can have the same short name.

Help Innokenty to choose a short name for each of the teams. If this is impossible, report that. If there are multiple answer, any of them will suit Innokenty. If for some team the two options of short name are equal, then Innokenty will formally think that only one of these options is chosen.

## 说明/提示

In the first sample Innokenty can choose first option for both clubs.

In the second example it is not possible to choose short names, because it is not possible that one club has first option, and the other has second option if the first options are equal for both clubs.

In the third example Innokenty can choose the second options for the first two clubs, and the first option for the third club.

In the fourth example note that it is possible that the chosen short name for some club $ x $ is the same as the first option of another club $ y $ if the first options of $ x $ and $ y $ are different.

## 样例 #1

### 输入

```
2
DINAMO BYTECITY
FOOTBALL MOSCOW
```

### 输出

```
YES
DIN
FOO
```

## 样例 #2

### 输入

```
2
DINAMO BYTECITY
DINAMO BITECITY
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3
PLAYFOOTBALL MOSCOW
PLAYVOLLEYBALL SPB
GOGO TECHNOCUP
```

### 输出

```
YES
PLM
PLS
GOG
```

## 样例 #4

### 输入

```
3
ABC DEF
ABC EFG
ABD OOO
```

### 输出

```
YES
ABD
ABE
ABO
```

# AI分析结果



### 综合分析与结论

**题目核心**：为每个足球队分配唯一的三字母简称，确保若某队选用了第二构造方式（前两字母+家乡首字母），则其他队不能选用与其第一构造方式（前三字母）相同的选项。所有简称必须唯一。

**难点**：
1. **冲突处理**：当多个队的第一构造相同时，必须全部选第二构造，而第二构造间可能冲突。
2. **依赖关系**：某队选择第二构造会禁止其他队的第一构造，需动态维护禁止列表。
3. **贪心策略验证**：需确保每次选择不影响后续步骤，且全局唯一性。

**贪心策略解析**：
- **优先选择第二构造**：若可行，则选第二构造并禁止其第一构造，避免后续冲突。
- **验证唯一性**：维护 `used` 集合记录所有已选简称，确保唯一性。
- **禁止列表维护**：用 `cant` 集合记录被禁用的第一构造，确保后续队无法选择。

**正确性保障**：通过动态维护 `used` 和 `cant` 集合，贪心策略在每一步确保局部最优且不影响全局，最终所有简称唯一且满足条件。

### 题解清单（评分≥4星）

1. **Enzyme125 的贪心算法（5星）**
   - **关键亮点**：
     - 优先选择第二构造，简化冲突处理。
     - 动态维护 `used` 和 `cant` 集合，确保全局唯一性和条件约束。
     - 代码简洁高效，时间复杂度 O(n)。
   - **代码片段**：
     ```cpp
     if (!used[b]) {
         used[b] = 1;
         ans = b;
     } else {
         if (used[a] || cant[a]) {
             puts("NO");
             return 0;
         }
         used[a] = 1;
         ans = a;
     }
     cant[a] = 1;
     ```

2. **wgyhm 的 2-SAT 模型（4星）**
   - **关键亮点**：
     - 将问题转化为布尔变量约束，确保正确性。
     - 使用强连通分量（Tarjan）判断解的可行性。
   - **适用场景**：复杂约束或需严格验证正确性的问题。

3. **XiaoQuQu 的迭代处理法（4星）**
   - **关键亮点**：
     - 多次迭代处理冲突，确保所有可能被覆盖。
     - 适用于需多轮调整的复杂场景。
   - **代码片段**：
     ```cpp
     int times = 30;
     while (times--) {
         // 多轮处理未确定的队
     }
     ```

### 最优思路提炼
- **贪心选择依据**：优先选第二构造，减少后续冲突概率。
- **动态维护**：`used` 确保唯一性，`cant` 禁止冲突的第一构造。
- **验证顺序**：按输入顺序处理，保证每一步的局部最优性。

### 同类型题目与套路
- **区间调度**：选择不重叠区间，最大化收益（如 [P1803 活动安排](https://www.luogu.com.cn/problem/P1803)）。
- **最小覆盖**：如最少教室安排（类似 [P4053 建筑抢修](https://www.luogu.com.cn/problem/P4053)）。
- **资源分配**：如 [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080) 中的贪心排序。

### 推荐洛谷题目
1. P1803 活动安排（贪心区间调度）
2. P4053 建筑抢修（贪心+堆优化）
3. P1080 国王游戏（贪心排序策略）

### 可视化与算法演示
- **动画设计**：
  1. **像素风格**：每个队显示为像素方块，颜色区分选项一/二。
  2. **高亮冲突**：红色标记冲突，绿色标记有效选择。
  3. **自动演示**：AI 逐步选择，音效提示成功/冲突。
- **交互功能**：
  - **步进控制**：单步执行观察选择逻辑。
  - **参数调整**：修改处理顺序或输入数据，观察结果变化。
  - **音效反馈**：成功音效（上扬音调），冲突提示（短促音效）。

### 代码实现（贪心算法核心）
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> anss;
    map<string, int> used, cant;
    
    for (int i = 0; i < n; i++) {
        string a, b, ans;
        cin >> a >> b;
        string opt1 = a.substr(0, 3);
        string opt2 = a.substr(0, 2) + b.substr(0, 1);
        
        if (!used[opt2]) {
            used[opt2] = 1;
            ans = opt2;
        } else {
            if (used[opt1] || cant[opt1]) {
                cout << "NO" << endl;
                return 0;
            }
            used[opt1] = 1;
            ans = opt1;
        }
        cant[opt1] = 1;
        anss.push_back(ans);
    }
    
    cout << "YES" << endl;
    for (auto& s : anss) cout << s << endl;
    return 0;
}
```

---
处理用时：169.46秒