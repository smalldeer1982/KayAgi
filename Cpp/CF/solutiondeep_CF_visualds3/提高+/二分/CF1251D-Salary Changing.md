# 题目信息

# Salary Changing

## 题目描述

You are the head of a large enterprise. $ n $ people work at you, and $ n $ is odd (i. e. $ n $ is not divisible by $ 2 $ ).

You have to distribute salaries to your employees. Initially, you have $ s $ dollars for it, and the $ i $ -th employee should get a salary from $ l_i $ to $ r_i $ dollars. You have to distribute salaries in such a way that the median salary is maximum possible.

To find the median of a sequence of odd length, you have to sort it and take the element in the middle position after sorting. For example:

- the median of the sequence $ [5, 1, 10, 17, 6] $ is $ 6 $ ,
- the median of the sequence $ [1, 2, 1] $ is $ 1 $ .

It is guaranteed that you have enough money to pay the minimum salary, i.e $ l_1 + l_2 + \dots + l_n \le s $ .

Note that you don't have to spend all your $ s $ dollars on salaries.

You have to answer $ t $ test cases.

## 说明/提示

In the first test case, you can distribute salaries as follows: $ sal_1 = 12, sal_2 = 2, sal_3 = 11 $ ( $ sal_i $ is the salary of the $ i $ -th employee). Then the median salary is $ 11 $ .

In the second test case, you have to pay $ 1337 $ dollars to the only employee.

In the third test case, you can distribute salaries as follows: $ sal_1 = 4, sal_2 = 3, sal_3 = 6, sal_4 = 6, sal_5 = 7 $ . Then the median salary is $ 6 $ .

## 样例 #1

### 输入

```
3
3 26
10 12
1 4
10 11
1 1337
1 1000000000
5 26
4 4
2 4
6 8
5 6
2 7
```

### 输出

```
11
1337
6
```

# AI分析结果


### 💡 Kay的C++算法解析：Salary Changing 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：二分答案、贪心策略

🗣️ **初步分析**：
> 解决本题的关键在于将问题转化为**二分答案验证模型**。想象你在玩一款像素冒险游戏，目标是搭建一座尽可能高的"中位数塔"（塔高即中位数）。二分法就像用不同高度的塔基进行测试，而贪心策略则是用最省金币的方式搭建当前高度的塔。  
> - 核心思路：二分枚举中位数 `x`，用贪心策略验证能否用 `s` 金币保证至少 `(n+1)/2` 人工资 ≥ `x`。难点在于如何高效分配金币：  
>   • 将员工分为三类：`r_i < x`（必须 < x）、`l_i > x`（必然 ≥ x）、`l_i ≤ x ≤ r_i`（可灵活分配）  
>   • 对灵活分配的员工，**优先提升 `l_i` 较大者**（减少提升代价），这是最小化总成本的关键  
> - 可视化设计：  
>   • 像素风格网格展示员工（红/绿/黄块表示三类员工）  
>   • 动态排序黄色块（按 `l_i` 降序），闪烁显示被提升的员工  
>   • 显示金币消耗进度条，当消耗超过 `s` 时播放失败音效

---

#### 2. 精选优质题解参考
**题解一（Weakest_Konjac）**  
* **点评**：思路清晰直白，分类严谨（三类员工处理逻辑分明），代码规范（变量名 `cnt1/cnt2/sum` 含义明确）。亮点在于对第三类员工按 `l_i` 排序后，巧妙选取前 `k` 个保留原工资，其余提升至 `x`，使提升代价最小化。边界处理完整（`cnt1 > n/2` 提前终止），可直接用于竞赛。

**题解二（灵茶山艾府）**  
* **点评**：创新性从大到小排序 `l_i`，扫描时动态选择可提升员工。亮点在于：1) 实现简洁（仅需单次扫描） 2) 空间优化（无需额外存储第三类）3) Go 语言实现拓宽视野。虽思路稍抽象，但贪心正确性有严格证明（优先处理高 `l_i` 降低提升成本）。

**题解三（HYXLE）**  
* **点评**：结构清晰，核心逻辑与题解一一致。亮点在于位运算优化（`n>>1`）和二分边界精细处理（`l=a[(n+1)>>1].l`）。代码规范性稍弱（未显式排序第三类），但算法本质正确且效率相同。

---

#### 3. 核心难点辨析与解题策略
1. **难点1：贪心策略设计**  
   * **分析**：验证 `x` 时需最小化总成本。关键发现：提升第三类员工时，**优先选择 `l_i` 大的员工**（提升代价 `x-l_i` 更小）。优质题解均通过排序实现此策略（正序/倒序本质相同）。
   * 💡 **学习笔记**：贪心优化常通过排序实现局部最优性

2. **难点2：二分边界确定**  
   * **分析**：左端点取 `l_i` 中位数（保证至少有 `(n+1)/2` 人可 ≥ `x`），右端点取 `min(max_r_i, s/((n+1)/2)`。题解中 `Weakest_Konjac` 的 `r=1ll*s/((n>>1)+1)` 是典型优化。
   * 💡 **学习笔记**：二分边界需结合数学约束与问题特性

3. **难点3：状态完整性检查**  
   * **分析**：需处理三类边界：1) 第一类过多时 `x` 不可能 2) 第三类不足时立即终止 3) 总成本溢出 `s`。题解均通过 `cnt1 > n/2` 等判断覆盖。
   * 💡 **学习笔记**：验证函数需全面覆盖失败场景

✨ **解题技巧总结**  
- **问题转化技巧**：将最值问题转化为判定问题（二分答案）  
- **贪心排序技巧**：通过排序（`l_i` 降序）保证局部最优性  
- **边界防御技巧**：显式处理 `cnt` 超标、成本溢出等边界  

---

#### 4. C++核心代码实现赏析
**本题通用核心实现**  
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

struct Employee { ll l, r; };
const int N = 2e5 + 5;

bool check(ll x, vector<Employee>& emp, ll s, int n) {
    ll sum = 0;
    int cnt1 = 0, cnt2 = 0;
    vector<ll> flexible;

    for (int i = 0; i < n; ++i) {
        if (emp[i].r < x) { cnt1++; sum += emp[i].l; }
        else if (emp[i].l > x) { cnt2++; sum += emp[i].l; }
        else flexible.push_back(emp[i].l);
    }

    if (cnt1 > n/2 || flexible.size() < max(0, (n+1)/2 - cnt2)) 
        return false;

    sort(flexible.begin(), flexible.end()); // 关键排序
    int k = max(0, (n+1)/2 - cnt2);
    for (int i = 0; i < flexible.size(); ++i) 
        sum += (i < flexible.size() - k) ? flexible[i] : x;
    
    return sum <= s;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; ll s; cin >> n >> s;
        vector<Employee> emp(n);
        for (int i = 0; i < n; ++i) 
            cin >> emp[i].l >> emp[i].r;

        sort(emp.begin(), emp.end(), [](auto a, auto b) {
            return a.l < b.l;
        });

        ll L = emp[n/2].l, R = 0;
        for (auto& e : emp) R = max(R, e.r);
        
        while (L <= R) {
            ll mid = (L + R) >> 1;
            check(mid, emp, s, n) ? L = mid + 1 : R = mid - 1;
        }
        cout << L - 1 << "\n";
    }
}
```
**代码解读概要**：  
1. **输入处理**：读入多组测试数据，按 `l_i` 排序员工数组  
2. **二分框架**：在 `[最小中位数, 最大r_i]` 区间二分  
3. **验证函数**：  
   - 分类统计三类员工并计算基础成本  
   - 对灵活员工按 `l_i` 排序，最优分配提升名额  
   - 综合判断成本是否 ≤ `s`  

**题解片段赏析**  
**题解一（Weakest_Konjac）**  
```cpp
for (int i=1; i<=(n>>1)-cnt1; ++i) sum += num[tot[i]].l;
sum += 1ll*mid*((n>>1)+1-cnt2);  // 剩余提升至mid
```
> **亮点**：显式区分保留原薪与提升人数  
> **解读**：`tot` 存储第三类员工索引（已按 `l_i` 排序）。循环保留前 `k` 个低 `l_i` 员工原薪，剩余提升至 `mid`。**为何先处理低 `l_i`？** 因为提升高 `l_i` 员工代价更小（`mid-l_i` 更小），此写法等价于优先提升高 `l_i` 者。  
> 💡 **学习笔记**：排序方向不影响最优性，关键在区分处理对象  

**题解二（灵茶山艾府）**  
```go
sort.Slice(ps, func(i, j int) bool { return ps[i].l > ps[j].l })
for _, p := range ps {
    if p.r >= x {
        cost += max(0, x - p.l) // 动态计算提升代价
        if 2*cnt-1 == n { break } // 提前终止
    }
}
```
> **亮点**：降序扫描避免显式存储第三类  
> **解读**：按 `l_i` 降序排序后，扫描时优先处理高 `l_i` 员工（提升代价小）。当满足人数要求时提前终止，优化常数时间。  
> 💡 **学习笔记**：动态计算提升代价可减少状态存储  

---

#### 5. 算法可视化：像素动画演示
**主题**：8-bit风格《中位数大冒险》  
**核心演示**：  
1. **场景设计**：  
   - 员工显示为三色像素块：🔥红色（`r_i<x`）、💚绿色（`l_i>x`）、💛黄色（灵活分配）
   - 动态条形图显示金币消耗（红/黄/绿区表示当前开销）

2. **关键动画流程**：  
   ```mermaid
   graph TD
   A[二分开始] --> B[显示当前x值]
   B --> C[员工按l_i降序排列]
   C --> D[扫描员工：红/绿/黄块闪烁]
   D --> E[黄块处理：按l_i高低动态提升]
   E --> F{金币≤s 且 ≥x人数达标？}
   F -->|是| G[播放胜利音效 提升x]
   F -->|否| H[播放失败音效 降低x]
   ```

3. **交互控制**：  
   - **单步执行**：逐步显示员工分类过程
   - **速度滑块**：控制二分查找速度
   - **AI演示**：自动完成二分全流程（类似贪吃蛇AI）

4. **像素特效**：  
   - 员工块排序时显示像素拖尾动画  
   - 提升操作时显示💰金币飞入效果  
   - 成功时放烟花（8-bit音效+闪烁星星）

---

#### 6. 拓展练习与相似问题思考
1. **通用技巧迁移**：  
   - 二分答案模型适用于：最大值最小化/中位数最大化  
   - 贪心排序技巧可用于：区间调度、任务分配  

2. **洛谷推荐练习**：  
   - 🟦 **P2884 [USACO07MAR] Monthly Expense**  
     > 二分最小值验证，巩固问题转化能力  
   - 🟪 **P4343 [SHOI2015] 自动刷题机**  
     > 二分答案+验证的变体，训练边界处理  
   - 🟨 **P1642 规划**  
     > 分数规划问题，拓展二分应用场景  

---

#### 7. 学习心得与经验分享
> 本次分析的题解中未发现明确的作者个人心得分享部分，但综合解题过程可得：  
> **调试经验**：  
> - 边界处理是核心难点（如 `cnt1 > n/2` 判断）  
> - 提升策略需数学证明（为什么优先提升高 `l_i`）  
> **学习建议**：  
> - 用小规模数据手工模拟算法流程  
> - 添加调试输出验证分类结果  

---  
**Kay的结语**：  
掌握二分答案与贪心的结合，就能在算法世界中建造属于你的"高塔"！下次遇到最值问题，记得先问：**我能二分答案吗？** 💪

---
处理用时：307.87秒