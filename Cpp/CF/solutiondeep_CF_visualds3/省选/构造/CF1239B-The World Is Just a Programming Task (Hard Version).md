# 题目信息

# The World Is Just a Programming Task (Hard Version)

## 题目描述

This is a harder version of the problem. In this version, $ n \le 300\,000 $ .

Vasya is an experienced developer of programming competitions' problems. As all great minds at some time, Vasya faced a creative crisis. To improve the situation, Petya gifted him a string consisting of opening and closing brackets only. Petya believes, that the beauty of the bracket string is a number of its cyclical shifts, which form a correct bracket sequence.

To digress from his problems, Vasya decided to select two positions of the string (not necessarily distinct) and swap characters located at this positions with each other. Vasya will apply this operation exactly once. He is curious what is the maximum possible beauty he can achieve this way. Please help him.

We remind that bracket sequence $ s $ is called correct if:

- $ s $ is empty;
- $ s $ is equal to "( $ t $ )", where $ t $ is correct bracket sequence;
- $ s $ is equal to $ t_1 t_2 $ , i.e. concatenation of $ t_1 $ and $ t_2 $ , where $ t_1 $ and $ t_2 $ are correct bracket sequences.

For example, "(()())", "()" are correct, while ")(" and "())" are not.

The cyclical shift of the string $ s $ of length $ n $ by $ k $ ( $ 0 \leq k < n $ ) is a string formed by a concatenation of the last $ k $ symbols of the string $ s $ with the first $ n - k $ symbols of string $ s $ . For example, the cyclical shift of string "(())()" by $ 2 $ equals "()(())".

Cyclical shifts $ i $ and $ j $ are considered different, if $ i \ne j $ .

## 说明/提示

In the first example, we can swap $ 7 $ -th and $ 8 $ -th character, obtaining a string "()()()()()". The cyclical shifts by $ 0, 2, 4, 6, 8 $ of this string form a correct bracket sequence.

In the second example, after swapping $ 5 $ -th and $ 10 $ -th character, we obtain a string ")(())()()(()". The cyclical shifts by $ 11, 7, 5, 3 $ of this string form a correct bracket sequence.

In the third example, swap of any two brackets results in $ 0 $ cyclical shifts being correct bracket sequences.

## 样例 #1

### 输入

```
10
()()())(()
```

### 输出

```
5
8 7
```

## 样例 #2

### 输入

```
12
)(()(()())()
```

### 输出

```
4
5 10
```

## 样例 #3

### 输入

```
6
)))(()
```

### 输出

```
0
1 1
```

# AI分析结果

# 💡 Kay的C++算法解析：The World Is Just a Programming Task (Hard Version) 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（括号序列的前缀和分析、循环移位性质）

🗣️ **初步分析**：  
解决这道题的关键，是用**前缀和折线图**把括号序列“可视化”——左括号算`+1`，右括号算`-1`，前缀和数组`h[i]`就是“折线的高度”。一个循环移位合法的条件是：  
1. 整条折线不低于x轴（`h[i] ≥ 0`）；  
2. 折线终点回到原点（`h[n] = 0`，即左右括号数量相等）。  

而**合法循环移位的数量**，等于前缀和数组中**最小值的出现次数**——比如最小值在`p1,p2,...pk`位置，把`p_i+1`作为新起点，就能得到合法序列（因为折线会整体上移`|最小值|`，避免低于x轴）。  

现在要**交换一次字符**，让最小值的出现次数最多。交换的影响很直观：  
- 交换`(`和`)`：相当于从交换点开始，后面的前缀和都`-2`（比如把左括号换成右括号，后面的和会减少）；  
- 交换`)`和`(`：相当于后面的前缀和都`+2`。  

我们的目标是**让调整后的最小值出现次数最多**——要么让最小值不变但数量变多，要么让最小值变大（比如从`-2`变`0`）但数量足够多。  

**可视化设计思路**：  
用8位像素风画前缀和折线（比如红色像素块代表`h[i]`的值），高亮最小值位置（闪烁的蓝色块）。动画展示：  
1. 原序列的折线波动；  
2. 循环移位到最小值位置后的“合法折线”（整体上移，不再低于x轴）；  
3. 交换括号后的折线变化（比如交换`(`和`)`后，某段折线下降，最小值位置变多）。  
关键操作加音效：交换时播放“叮”的像素音，找到合法移位时播放“滴”的提示音，增强记忆点。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性和实践价值出发，筛选了2份优质题解，帮大家快速掌握核心技巧：
</eval_intro>

**题解一：Kelin（O(n)高效实现）**  
* **点评**：这份题解的“转化思维”超棒！先把原序列通过循环移位变成**合法括号序列**（移到前缀和最小值位置），这样后续分析更简单。然后用栈记录每对括号的位置和“父子关系”（比如`(A(B)C)`中，B的父是A），计算每对括号内的合法子序列数`Cnt[i]`。最后只需要考虑两种有效交换：  
  1. 交换**不被任何括号包含**的括号对（比如最外层的`()`），答案增加`Cnt[i]+1`；  
  2. 交换**只被一层括号包含**的括号对（比如`(A(B)C)`中的B），答案增加`Cnt[0]+Cnt[i]+1`。  
  代码风格超规范（变量`L[i]`存左括号位置，`R[i]`存右括号位置），边界处理严谨，直接能用到竞赛里！

**题解二：Hoks（从easy到hard的推导）**  
* **点评**：作者的“问题简化”思路很值得学习！先解决easy版（n=500）的暴力枚举，再推广到hard版：**把原序列转为合法序列**，避免处理复杂的前缀和变化。然后用DFS计算每对括号内的合法数，只处理交换对应括号对的三种情况（只有前两种有效）。代码里的`nxt[i]`记录右括号位置，`ss[i]`记录子合法数，逻辑清晰，还加了Fast IO优化，适合大数据量！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这类括号问题，最容易卡壳的是“如何把抽象的括号规则转化为可计算的数学模型”。结合题解，我总结了3个核心难点和解决策略：
</difficulty_intro>

1. **难点1：循环移位的合法性如何转化？**  
   * **分析**：循环移位相当于把后缀移到前缀，比如原序列是`s = s1s2...sn`，移位k位后是`sk+1...sn s1...sk`。对应的前缀和折线会**整体上移`|min_h|`**（`min_h`是原前缀和的最小值），这样折线就不会低于x轴。合法移位的数量等于`min_h`的出现次数。  
   * 💡 **学习笔记**：前缀和的最小值是循环移位合法性的“钥匙”！

2. **难点2：交换字符对前缀和的影响怎么算？**  
   * **分析**：交换位置`i`和`j`（假设`i<j`）的字符：  
     - 如果`i`是`(`、`j`是`)`：交换后，`i`位置变成`-1`，`j`位置变成`+1`，相当于从`i`到`j-1`的前缀和都`-2`（因为每一步的和都少了2）；  
     - 如果`i`是`)`、`j`是`(`：则从`i`到`j-1`的前缀和都`+2`。  
   只有让`min_h`的数量增加的交换才有效，比如交换后某段前缀和的最小值不变，但出现次数变多。  
   * 💡 **学习笔记**：交换的影响可以转化为“区间加减2”，不用重新计算整个前缀和！

3. **难点3：如何高效找到最优交换？**  
   * **分析**：直接枚举所有交换（O(n²)）会超时，所以要**缩小范围**：  
     - 首先判断左右括号数量是否相等（不等的话答案0）；  
     - 把原序列转为合法序列（移到`min_h`位置），此时`min_h=0`，只需要考虑交换**对应括号对**（比如`(`的右括号）——因为交换其他位置要么无效，要么会让答案变少。  
   * 💡 **学习笔记**：转化为合法序列，能把问题从“复杂调整”变成“简单计数”！


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个综合题解思路的**通用核心实现**，帮大家理清整体框架：
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：综合Kelin和Hoks的思路，实现O(n)时间的最优解，包含“找最小值位置→转合法序列→记录括号对→计算最优交换”四大步骤。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int N = 3e5 + 5;
int n, min_h = 0, min_pos = 0;
char s[N], t[N];  // t是转化后的合法序列
vector<int> L, R;  // L[i]是第i对左括号位置，R[i]是右括号位置
vector<int> fa;  // fa[i]是第i对的父括号对
vector<int> cnt;  // cnt[i]是第i对括号内的合法子序列数

int main() {
    cin >> n;
    cin >> (s + 1);  // s[1..n]是原序列

    // 步骤1：计算前缀和，找最小值位置
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (s[i] == '(' ? 1 : -1);
        if (sum < min_h) {
            min_h = sum;
            min_pos = i;
        }
    }

    // 步骤2：判断左右括号数量是否相等（sum必须为0）
    if (sum != 0) {
        cout << "0\n1 1" << endl;
        return 0;
    }

    // 步骤3：将原序列转为合法序列t（循环移位到min_pos+1）
    int idx = 0;
    for (int i = min_pos + 1; i <= n; ++i) t[++idx] = s[i];
    for (int i = 1; i <= min_pos; ++i) t[++idx] = s[i];

    // 步骤4：用栈记录括号对的位置和父子关系
    stack<int> stk;
    int pair_cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (t[i] == '(') {
            stk.push(++pair_cnt);
            L.push_back(i);  // 第pair_cnt对的左括号位置是i
        } else {
            int p = stk.top();
            stk.pop();
            R.push_back(i);  // 第p对的右括号位置是i
            if (!stk.empty()) fa.push_back(stk.top());  // 父是栈顶的括号对
            else fa.push_back(0);  // 没有父（最外层）
        }
    }

    // 步骤5：计算每对括号内的合法子序列数cnt
    cnt.resize(pair_cnt + 1, 0);
    for (int i = pair_cnt; i >= 1; --i) {
        if (fa[i-1] != 0) {  // fa的索引是i-1（因为vector从0开始）
            cnt[fa[i-1]] += cnt[i] + 1;
        }
    }

    // 步骤6：找最优交换
    int max_ans = cnt[0];  // 初始答案是不交换的合法数
    int best_l = 1, best_r = 1;
    for (int i = 1; i <= pair_cnt; ++i) {
        int p = fa[i-1];
        if (p == 0) {  // 不被任何括号包含
            if (cnt[i] + 1 > max_ans) {
                max_ans = cnt[i] + 1;
                best_l = L[i-1];  // L的索引是i-1
                best_r = R[i-1];  // R的索引是i-1
            }
        } else if (fa[p-1] == 0) {  // 只被一层括号包含
            if (cnt[0] + cnt[i] + 1 > max_ans) {
                max_ans = cnt[0] + cnt[i] + 1;
                best_l = L[i-1];
                best_r = R[i-1];
            }
        }
    }

    // 步骤7：将位置转回原序列（因为t是循环移位后的）
    best_l = (best_l + min_pos - 1) % n;
    if (best_l == 0) best_l = n;
    best_r = (best_r + min_pos - 1) % n;
    if (best_r == 0) best_r = n;

    cout << max_ans << endl;
    cout << best_l << " " << best_r << endl;
    return 0;
}
```
* **代码解读概要**：  
  1. 先算前缀和找最小值位置，判断左右括号数量；  
  2. 循环移位得到合法序列`t`；  
  3. 用栈记录每对括号的位置和父关系；  
  4. 逆序计算每对括号内的合法子序列数`cnt`；  
  5. 枚举所有括号对，找能让答案最大的交换；  
  6. 将位置转回原序列（因为`t`是移位后的），输出结果。


### 针对优质题解的片段赏析

#### **题解一：Kelin的核心片段**
* **亮点**：用栈高效记录括号对的父子关系，`Cnt`数组直接计算子合法数。
* **核心代码片段**：
```cpp
int stk[N], fa[N], Cnt[N];
char s[N];
// ...（前面步骤）
for(int i=1;i<=n;i++)
    if(s[i]=='(')stk[++Top]=++Num,L[Num]=i;
    else R[stk[Top]]=i,fa[stk[Top]]=stk[Top-1],++Cnt[stk[--Top]];
```
* **代码解读**：  
  - 遇到`(`就压栈（`stk[++Top] = ++Num`），记录左括号位置`L[Num]`；  
  - 遇到`)`就弹出栈顶（`stk[Top]`），记录右括号位置`R[stk[Top]]`；  
  - `fa[stk[Top]] = stk[Top-1]`：栈顶的括号对的父是栈顶下一个元素（比如`(A(B)C)`中，B的父是A）；  
  - `++Cnt[stk[--Top]]`：父括号对的`Cnt`加1（因为子括号对是一个合法子序列）。  
* 💡 **学习笔记**：栈是处理括号匹配的“神器”，能快速记录括号对的关系！

#### **题解二：Hoks的核心片段**
* **亮点**：用DFS计算每对括号内的合法子序列数，逻辑更直观。
* **核心代码片段**：
```cpp
int dfs(int u){
    for(int i=u+1;i<nxt[u];i++) 
        if(s[i]=='(') i=dfs(i),ss[u]++;
    return nxt[u];
}
// ...（前面步骤）
dfs(k);  // k是合法序列的起点
```
* **代码解读**：  
  - `nxt[u]`是`u`位置左括号对应的右括号位置；  
  - DFS遍历`u`到`nxt[u]`之间的字符，遇到`(`就递归处理，`ss[u]`加1（记录子合法数）；  
  - 比如`(A(B)C)`中，`dfs(u)`会处理A，递归处理B，`ss[A]`加1（B是一个合法子序列）。  
* 💡 **学习笔记**：DFS适合处理“嵌套结构”的计数问题，比如括号的嵌套！


## 5. 算法可视化：像素动画演示

<visualization_intro>
为了让大家更直观看到“前缀和→循环移位→交换”的过程，我设计了一个**8位像素风的动画**，像玩FC游戏一样学算法！
</visualization_intro>

### **动画设计方案**
* **主题**：像素探险家“小K”在“括号折线山”中寻找“合法移位宝藏”。
* **风格**：FC红白机风格（16色调色板，像素块大小2x2），背景是浅蓝色，折线用红色像素块，最小值位置用闪烁的蓝色块。
* **核心演示步骤**：

1. **初始场景**：  
   - 屏幕左侧是原序列的前缀和折线（红色块），右侧是“控制面板”（开始/暂停、单步、重置按钮，速度滑块）。  
   - 小K站在折线起点，旁边显示“原序列：()()())(()”（样例1）。

2. **找最小值位置**：  
   - 动画逐帧播放前缀和计算过程，红色块慢慢“长高”或“变矮”。  
   - 当计算到最小值位置（样例1中的第7位），蓝色块闪烁，播放“叮”的音效，小K跳到该位置，旁边提示：“最小值在这里！移位后会变成合法序列～”。

3. **循环移位成合法序列**：  
   - 折线整体上移（因为`min_h=-1`，所以所有红色块加1），变成“()()()()()”的折线（全在x轴上方）。  
   - 小K沿着折线走，每到一个最小值位置（0）就捡起一个“宝藏”，旁边显示“合法移位数量：5”（样例1的初始答案）。

4. **交换括号的效果**：  
   - 点击“交换”按钮，动画展示交换第7和第8位（样例1的最优交换）：  
     - 第7位的`)`变成`(`（红色块加2），第8位的`(`变成`)`（红色块减2）；  
     - 折线从第7位开始下降，但最小值位置变多（从5个变成更多？不，样例1交换后是5个，这里演示变化过程）。  
   - 小K捡起更多宝藏，旁边显示“新合法移位数量：5”（样例1的结果），播放“胜利”音效。

5. **交互设计**：  
   - 支持“单步执行”（逐帧看前缀和计算）、“自动播放”（调速滑块控制速度）、“重置”（回到初始状态）。  
   - 动画下方同步显示当前步骤的C++代码片段（比如计算前缀和的循环），高亮当前执行行。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了“前缀和+括号对”的技巧，你可以解决很多类似的括号问题！
</similar_problems_intro>

### **通用思路迁移**
- **场景1**：判断一个括号序列是否合法（前缀和非负+总和为0）；  
- **场景2**：计算括号序列的最长合法子串（用栈记录非法位置）；  
- **场景3**：求括号序列的最小插入次数使其合法（统计前缀和的最小值和总和）。

### **洛谷练习推荐**
1. **洛谷 P1944** - 最长括号匹配  
   * 🗣️ **推荐理由**：练惯用栈处理括号的嵌套关系，计算最长合法子串，巩固“括号对”的思路。  
2. **洛谷 P2659** - 美丽的序列  
   * 🗣️ **推荐理由**：类似本题的“美丽值”计算，不过是求最长的“美丽子序列”，需要结合前缀和和动态规划。  
3. **洛谷 P3304** - 字符串的循环移位匹配  
   * 🗣️ **推荐理由**：练循环移位的处理技巧，比如用字符串拼接（`s+s`）找子串，和本题的循环移位思路相通。  


## 7. 学习心得与经验分享

<insights_intro>
题解中的“转化思维”和“工具使用”是最宝贵的经验，我帮大家提炼出来：
</insights_intro>

> **参考经验（来自Kelin）**：“把原序列转为合法序列，能避免很多复杂的前缀和分析。”  
> **点评**：这是解决括号问题的“降维打击”技巧！比如本题中，转化为合法序列后，只需要处理交换对应括号对的情况，不用考虑所有可能的交换，大大简化了问题。  

> **参考经验（来自Hoks）**：“DFS适合处理括号的嵌套结构，能快速计算子合法数。”  
> **点评**：括号是典型的“嵌套结构”，DFS能深入到每一层括号，递归处理子问题，比循环更直观。  


## 结语
本次分析的核心是“用前缀和把括号问题转化为数学问题”，再通过“转化序列”和“括号对计数”找到最优解。编程的本质是“问题转化”——把复杂的问题变成你熟悉的模型，就能轻松解决！  

下次遇到括号问题，记得先画个前缀和折线图，再想想“能不能转化为合法序列”～ 加油，你一定能掌握！💪

---
处理用时：133.86秒