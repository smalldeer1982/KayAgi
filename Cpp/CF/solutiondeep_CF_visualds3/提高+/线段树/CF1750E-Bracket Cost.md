# 题目信息

# Bracket Cost

## 题目描述

Daemon Targaryen decided to stop looking like a Metin2 character. He turned himself into the most beautiful thing, a bracket sequence.

For a bracket sequence, we can do two kind of operations:

- Select one of its substrings $ ^\dagger $ and cyclic shift it to the right. For example, after a cyclic shift to the right, "(())" will become ")(()";
- Insert any bracket, opening '(' or closing ')', wherever you want in the sequence.

We define the cost of a bracket sequence as the minimum number of such operations to make it balanced $ ^\ddagger $ .

Given a bracket sequence $ s $ of length $ n $ , find the sum of costs across all its $ \frac{n(n+1)}{2} $ non-empty substrings. Note that for each substring we calculate the cost independently.

 $ ^\dagger $ A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

 $ ^\ddagger $ A sequence of brackets is called balanced if one can turn it into a valid math expression by adding characters $ + $ and $ 1 $ . For example, sequences "(())()", "()", and "(()(()))" are balanced, while ")(", "(()", and "(()))(" are not.

## 说明/提示

In the first test case, there is the only substring ")". Its cost is $ 1 $ because we can insert '(' to the beginning of this substring and get a string "()", that is a balanced string.

In the second test case, the cost of each substring of length one is $ 1 $ . The cost of a substring ")(" is $ 1 $ because we can cyclically shift it to right and get a string "()". The cost of strings ")()" and "()(" is $ 1 $ because its enough to insert one bracket to each of them. The cost of substring ")()(" is $ 1 $ because we can cyclically shift it to right and get a string "()()". So there are $ 4 + 2 + 2 + 1 = 9 $ substring of cost $ 1 $ and $ 1 $ substring of cost $ 0 $ . So the sum of the costs is $ 9 $ .

In the third test case,

- "(", the cost is $ 1 $ ;
- "()", the cost is $ 0 $ ;
- "())", the cost is $ 1 $ ;
- ")", the cost is $ 1 $ ;
- "))", the cost is $ 2 $ ;
- ")", the cost is $ 1 $ .

So the sum of the costs is $ 6 $ .

## 样例 #1

### 输入

```
5
1
)
4
)()(
3
())
5
(((((
10
)(())))())```

### 输出

```
1
9
6
35
112```

# AI分析结果


### 💡 Kay的C++算法解析：Bracket Cost 深入学习指南 💡

<introduction>
今天我们一起分析Codeforces 1750E的括号序列问题。本指南将帮你理解如何高效计算所有子串的最小操作次数之和，掌握前缀和与栈的巧妙应用，并通过像素动画直观感受算法过程。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`前缀和技巧` + `栈应用` + `数学推导`

🗣️ **初步分析**：
> 本题核心在于**将操作次数转化为数学表达式**：每个子串的代价 = max(L,R) - X（L/R为左右括号数，X为已匹配括号对数）。通过三步拆分：
> - **前缀和数组**：将括号序列转为±1序列，用前缀和计算L-R
> - **绝对值处理**：通过排序快速计算所有子串的|L-R|之和
> - **栈匹配**：用栈高效计算所有匹配括号对的贡献
> 
> **可视化设计思路**：在像素动画中，我们将用颜色标记前缀和变化（绿色上升/红色下降），高亮栈匹配过程（黄色闪光表示括号匹配），并添加音效（匹配成功时"叮"声）。采用8-bit风格网格展示，控制面板支持单步执行观察状态变化。

---

## 2. 精选优质题解参考

<eval_intro>
从思路清晰性、代码规范性和算法效率角度，精选以下题解：

**题解一（dottle）**
* **点评**：思路最直观严谨，完整推导数学表达式。代码高度优化（O(n)时间复杂度），用单次排序和栈匹配实现计算。变量命名简洁（`a`存前缀和，`res`累积结果），边界处理完善（空栈判断）。亮点在于将max(L,R)拆解为(L+R+|L-R|)/2的数学变换。

**题解二（MSqwq）**
* **点评**：讲解更详细，分步推导清晰。代码添加详细注释，用`sum`数组存储前缀和排序结果，显式分离|L-R|和匹配对计算。实践价值高，包含调试心得（提到比赛时卡关1小时），提醒注意下标偏移问题（左括号压入i-1需谨慎）。

**题解三（lkytxdy）**
* **点评**：提供独特视角（将操作次数关联前缀和极值），用单调栈计算区间最小值。代码紧凑但稍难理解（双重循环处理左右边界），亮点是避免显式排序，用单调栈直接计算绝对值和。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题需突破三个关键点：

1.  **数学转换**：如何将操作次数转为可计算的表达式？
    * **分析**：发现代价 = max(L,R) - X是突破口。优质题解均通过数学拆解（max(L,R)=(L+R+|L-R|)/2）将问题转化为前缀和与绝对值的计算。
    * 💡 **学习笔记**：复杂操作问题常可转化为数学表达式求解。

2.  **绝对值求和**：如何高效计算所有子串的|L-R|之和？
    * **分析**：利用前缀和数组pre[]，|L-R|=|pre[r]-pre[l-1]|。通过对pre排序，用公式`sum(j*b[j] - prefix_sum)`在O(n)内完成计算，避免O(n²)遍历。
    * 💡 **学习笔记**：排序后利用前缀和是计算绝对值和的高效技巧。

3.  **匹配括号统计**：如何计算所有子串的已匹配括号对数？
    * **分析**：用栈模拟括号匹配过程。对每对匹配括号(l,r)，贡献为(l+1)*(n-r)（左端点0~l共l+1选择，右端点r~n-1共n-r选择）。需注意栈为空时的处理。
    * 💡 **学习笔记**：栈是处理括号匹配问题的核心数据结构。

### ✨ 解题技巧总结
<summary_best_practices>
- **问题分解**：将复杂操作拆解为数学表达式（max(L,R)和X）
- **前缀和转化**：将括号序列转为数值序列，利用排序优化计算
- **栈应用**：实时匹配括号并计算贡献
- **边界处理**：注意前缀和数组长度(n+1)和栈空判断

---

## 4. C++核心代码实现赏析

<code_intro_overall>
通用解法融合多题解优点，完整实现如下：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve() {
    int n; string s;
    cin >> n >> s;
    vector<ll> pre = {0}; // 前缀和数组
    for (char c : s) pre.push_back(pre.back() + (c=='('?1:-1));

    // 计算|L-R|和总长度
    sort(pre.begin(), pre.end());
    ll abs_sum = 0, len_sum = 0, prefix = 0;
    for (int i = 0; i <= n; i++) {
        abs_sum += i * pre[i] - prefix;
        len_sum += 1LL * i * (n - i + 1); // 子串长度和
        prefix += pre[i];
    }
    ll max_LR = (abs_sum + len_sum) / 2;

    // 计算匹配括号对贡献
    ll match = 0;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') st.push(i);
        else if (!st.empty()) {
            match += 1LL * (st.top() + 1) * (n - i);
            st.pop();
        }
    }
    cout << max_LR - match << '\n';
}
```
**代码解读概要**：
> 1. 构建前缀和数组pre（长度n+1）
> 2. 排序pre后计算绝对值和（abs_sum）与总长度和（len_sum）
> 3. 通过公式(max_LR = (abs_sum + len_sum)/2)获得第一部分结果
> 4. 用栈遍历字符串，累计匹配括号对贡献（match）
> 5. 最终结果 = max_LR - match

---
<code_intro_selected>
精选题解片段赏析：

**题解一（dottle）**
* **亮点**：最简洁高效的前缀和处理
* **核心代码片段**：
```cpp
sort(a.begin(), a.end());
ll res = 0, ns = 0;
for (int i = 0; i <= n; i++) {
    res += i * a[i] - ns;   // |L-R|求和
    res += i * (n - i + 1); // 长度求和
    ns += a[i];
}
res = res / 2 - match; // 最终结果
```
* **代码解读**：
> 排序后前缀和数组`a`，用`i*a[i]-ns`计算绝对值和（`ns`为前缀累计）。`i*(n-i+1)`计算位置i的贡献次数，二者相加除以2即max(L,R)。减法匹配对后得结果。
* 💡 **学习笔记**：合并计算多项指标可提升效率。

**题解二（MSqwq）**
* **亮点**：清晰分离计算步骤
* **核心代码片段**：
```cpp
for (int i = 1; i <= n; i++) {
    if (a[i] == '(') s.push(i - 1);
    else if (!s.empty()) {
        match += (s.top() + 1) * (n - (i - 1));
        s.pop();
    }
}
```
* **代码解读**：
> 栈存储左括号下标（注意压入i-1需确保下标正确）。匹配时用`(左括号下标+1)*(n-右括号下标+1)`计算贡献，直观体现代数逻辑。
* 💡 **学习笔记**：括号位置贡献 = 左端点选择数 × 右端点选择数。

**题解三（lkytxdy）**
* **亮点**：单调栈替代排序
* **核心代码片段**：
```cpp
// 单调栈求左右边界
while (top && a[i] < a[st[top]]) top--;
L[i] = top ? st[top] + 1 : 0;
st[++top] = i;
```
* **代码解读**：
> 用单调栈快速找到每个pre[i]的左右边界（L[i]/R[i]），通过边界计算绝对值和，避免显式排序。
* 💡 **学习笔记**：单调栈可高效处理数列边界问题。

---

## 5. 算法可视化：像素动画演示

<visualization_intro>
设计**"括号探险家"**像素动画演示前缀和与栈匹配过程，采用FC红白机复古风格：

![动画示意图](https://assets.luogu.com.cn/upload/image_hosting/5bhn1k0p.png)

* **设计思路**：用8-bit网格（16色）表示括号序列，上方显示前缀和折线。通过关卡式推进（每处理10字符为一关），增强学习成就感。

* **关键帧步骤**：
  1. **初始化**：显示括号序列网格（绿( / 红)），控制面板含步进/调速/重置按钮
  2. **前缀和计算**：
     - 左括号：角色右移，网格变绿，折线上升（↑音效）
     - 右括号：角色左移，网格变红，折线下降（↓音效）
  3. **栈匹配演示**：
     - 遇左括号：压入栈（像素块弹入动画 + 咔嗒声）
     - 遇右括号：检测栈顶 → 匹配成功：栈顶与当前括号闪光（💥特效 + 叮咚音效）
  4. **贡献计算**：匹配时显示(l+1)*(n-r)计算公式及结果
  5. **关卡推进**：每关结束显示阶段结果，背景音乐变调提示

* **交互设计**：
  - **步进控制**：空格键单步执行，方向键调整速度
  - **自动演示**：AI模式自动播放（类贪吃蛇AI移动）
  - **高亮提示**：当前操作位置闪烁红框，栈状态实时显示

* **音效设计**：
  - 括号移动：8-bit电子音（不同音高表升降）
  - 匹配成功：胜利旋律片段
  - 计算错误：短促警报声
  - 背景音乐：循环芯片音乐（可开关）

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
前缀和+栈的技巧适用于多种问题：

1. **最长有效括号**：计算最长的合法括号子串
2. **括号得分**：根据嵌套深度计算分数
3. **括号树**：树形结构上的括号匹配

**洛谷练习推荐**：
1. **P1944 最长括号匹配**  
   → 应用栈匹配求最长有效子串
2. **P5658 括号树**  
   → 扩展树形结构上的括号匹配
3. **P4200 千与千寻**  
   → 综合前缀和与贪心的括号问题

---

## 7. 学习心得与经验分享

<insights_intro>
题解中的调试经验值得借鉴：

> **MSqwq的调试经验**：  
> *"比赛时在**下标处理**卡了1小时，最后发现左括号压入i-1会导致贡献计算错误"*

> **Kay的总结**：  
> 括号问题需特别注意**下标起始**（0或1）和**边界情况**（空栈、单字符）。建议：
> 1. 先在纸上模拟小规模案例
> 2. 用`cout`输出中间变量（如pre[]和匹配对）
> 3. 单元测试边界用例（全左/全右括号）

---

<conclusion>
通过本指南，我们深入解析了括号代价问题的数学本质和高效解法。记住：
1. **问题转换**是优化复杂操作的关键
2. **前缀和+排序**可高效处理绝对值和
3. **栈应用**在括号匹配中不可替代
下次遇到括号问题，不妨尝试像素动画模拟辅助理解！🚀
</conclusion>

---
处理用时：264.76秒