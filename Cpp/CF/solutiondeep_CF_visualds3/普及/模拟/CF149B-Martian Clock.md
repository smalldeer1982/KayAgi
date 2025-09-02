# 题目信息

# Martian Clock

## 题目描述

Having stayed home alone, Petya decided to watch forbidden films on the Net in secret. "What ungentlemanly behavior!" — you can say that, of course, but don't be too harsh on the kid. In his country films about the Martians and other extraterrestrial civilizations are forbidden. It was very unfair to Petya as he adored adventure stories that featured lasers and robots.

Today Petya is watching a shocking blockbuster about the Martians called "R2:D2". What can "R2:D2" possibly mean? It might be the Martian time represented in the Martian numeral system. Petya knows that time on Mars is counted just like on the Earth (that is, there are $ 24 $ hours and each hour has $ 60 $ minutes). The time is written as " $ a $ : $ b $ ", where the string $ a $ stands for the number of hours (from $ 0 $ to $ 23 $ inclusive), and string $ b $ stands for the number of minutes (from $ 0 $ to $ 59 $ inclusive). The only thing Petya doesn't know is in what numeral system the Martian time is written.

Your task is to print the radixes of all numeral system which can contain the time " $ a $ : $ b $ ".

## 说明/提示

Let's consider the first sample. String "11:20" can be perceived, for example, as time 4:6, represented in the ternary numeral system or as time 17:32 in hexadecimal system.

Let's consider the second sample test. String "2A:13" can't be perceived as correct time in any notation. For example, let's take the base-11 numeral notation. There the given string represents time 32:14 that isn't a correct time.

Let's consider the third sample. String "000B:00001" can be perceived as a correct time in the infinite number of numeral systems. If you need an example, you can take any numeral system with radix no less than 12.

## 样例 #1

### 输入

```
11:20
```

### 输出

```
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22```

## 样例 #2

### 输入

```
2A:13
```

### 输出

```
0
```

## 样例 #3

### 输入

```
000B:00001
```

### 输出

```
-1
```

# AI分析结果



---
# 💡 Kay的C++算法解析：Martian Clock 深入学习指南 💡

<introduction>
今天我们来一起分析“Martian Clock”这道C++编程题。这道题需要我们判断给定的火星时间字符串在哪些进制下是合法的（即转换为十进制后小时≤23、分钟≤59）。本指南将帮助大家梳理题目思路，理解核心算法，并掌握解题技巧。
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`模拟与进制转换` 

🗣️ **初步分析**：
解决“Martian Clock”的关键在于模拟进制转换过程，并验证转换后的时间是否合法。简单来说，我们需要：首先处理输入字符串的前导零，确定可能的最小进制（由字符最大值决定），然后枚举可能的进制，逐个验证转换后的小时和分钟是否在合法范围内。

- **题解思路**：各题解的核心思路一致，均包含以下步骤：
  1. 分割字符串为小时和分钟部分，去除前导零。
  2. 确定所有字符中的最大值，得到最小可能的进制（max_digit + 1）。
  3. 特判无穷解（小时和分钟部分长度均≤1）或无解（最大字符对应数值超过23或59）。
  4. 枚举从最小进制开始的所有可能进制，验证转换后的时间是否合法。
  
- **核心难点**：前导零的正确处理（避免影响进制转换结果）、无穷解的判断逻辑（长度≤1时进制不影响数值）、进制转换时的数值计算（避免溢出）。

- **可视化设计**：我们将设计一个“像素进制探险”动画，用8位像素风格展示前导零去除、字符最大值计算、进制枚举验证的过程。例如，用不同颜色的像素块表示小时和分钟的每一位，高亮当前处理的字符；在枚举进制时，用“进度条”展示当前进制值，转换后的数值实时显示在屏幕上方，并通过音效（如“叮”声）提示合法进制。

---

## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码规范性、算法有效性等维度评估题解，筛选出以下3份优质题解（评分≥4星）：
</eval_intro>

**题解一：作者Rex01**
* **点评**：此题解步骤清晰，详细处理了前导零去除、字符最大值计算等细节。代码中通过遍历字符串分割小时和分钟部分，并用数组存储每一位的数值，逻辑直观。虽然变量命名较随意（如`z1`、`z2`），但整体结构完整。亮点在于对无穷解（`cnt1 <= 1 && cnt2 <= 1`）和无解（`Maxh > 23 || Maxm > 59`）的特判处理，确保了边界条件的覆盖。

**题解二：作者alan1118**
* **点评**：此题解对前导零处理的代码（`substr`函数的使用）尤为巧妙，通过寻找第一个非零字符的位置，精准截取有效部分。核心函数`toTen`实现了进制转换，逻辑简洁。亮点在于将特判顺序明确（先判断无解，再判断无穷解），避免了逻辑漏洞，代码可读性高。

**题解三：作者PR_CYJ**
* **点评**：此题解思路简洁，直接使用`vector`存储小时和分钟的每一位数值，通过遍历计算最大值。枚举进制时，采用“从最小进制开始，直到转换结果不合法”的策略，效率较高。亮点在于进制转换的实现（`a *= i; a += h[j]`）避免了幂运算的精度问题，代码更健壮。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决这个问题的过程中，我们通常会遇到以下关键点或难点。结合优质题解的共性，我为大家提炼了几个核心的思考方向和策略：
</difficulty_intro>

1.  **关键点1**：如何正确去除前导零？
    * **分析**：前导零不影响数值大小（如“0011”与“11”在任意进制下数值相同），但会影响有效位数的判断。优质题解通常通过遍历字符串，找到第一个非零字符的位置，然后截取后续部分。例如，`for(int i=0; i<z; i++) if(s[i]!='0') {z1=i; break;}`。
    * 💡 **学习笔记**：前导零的处理是关键，直接影响后续有效位数和无穷解的判断。

2.  **关键点2**：如何确定最小可能的进制？
    * **分析**：进制必须大于所有字符对应的数值（如字符'A'对应10，进制至少为11）。优质题解通过遍历所有字符，找到最大值`max_digit`，则最小进制为`max_digit + 1`。例如，若字符最大值是10（'A'），则最小进制是11。
    * 💡 **学习笔记**：进制的最小值由字符的最大值决定，这是枚举的起点。

3.  **关键点3**：如何判断无穷解？
    * **分析**：当小时和分钟部分去除前导零后的长度均≤1时，数值在任意进制下均等于其本身（如“1”在n进制下为1×n⁰=1）。此时，只要该数值合法（小时≤23、分钟≤59），所有≥最小进制的进制都合法，故有无穷解。
    * 💡 **学习笔记**：长度≤1是无穷解的必要条件，需结合数值合法性判断。

### ✨ 解题技巧总结
<summary_best_practices>
- **技巧A（前导零处理）**：通过遍历字符串找到第一个非零字符，截取有效部分，避免前导零干扰后续计算。
- **技巧B（进制转换优化）**：使用逐位累加的方式（如`a = a * base + digit`）替代幂运算，避免浮点数精度问题。
- **技巧C（边界条件检查）**：优先处理无解（字符最大值超范围）和无穷解（长度≤1），减少后续枚举的工作量。
</summary_best_practices>

---

## 4. C++核心代码实现赏析

<code_intro_overall>
在深入分析具体题解的精妙片段之前，让我们先来看一个综合优质题解的通用核心C++实现参考。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了Rex01、alan1118等题解的思路，优化了前导零处理和进制转换逻辑，结构清晰，适合学习。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <string>
    #include <vector>
    #include <algorithm>
    using namespace std;

    // 转换字符为数值（0-9对应0-9，A-Z对应10-35）
    int charToValue(char c) {
        return isdigit(c) ? (c - '0') : (c - 'A' + 10);
    }

    // 去除前导零，返回有效子串
    string removeLeadingZeros(const string& s) {
        size_t start = 0;
        while (start < s.size() && s[start] == '0') start++;
        return start == s.size() ? "0" : s.substr(start);
    }

    // 将s从base进制转换为十进制数值
    int convertToDec(const string& s, int base) {
        int res = 0;
        for (char c : s) {
            res = res * base + charToValue(c);
        }
        return res;
    }

    int main() {
        string s;
        cin >> s;
        size_t colon = s.find(':');
        string hourStr = s.substr(0, colon);
        string minuteStr = s.substr(colon + 1);

        // 去除前导零
        string h = removeLeadingZeros(hourStr);
        string m = removeLeadingZeros(minuteStr);

        // 计算字符最大值，确定最小进制
        int maxDigit = 0;
        for (char c : h + m) {
            maxDigit = max(maxDigit, charToValue(c));
        }
        int minBase = maxDigit + 1;

        // 特判无穷解：h和m长度均≤1且数值合法
        if (h.size() <= 1 && m.size() <= 1) {
            int hVal = charToValue(h[0]);
            int mVal = charToValue(m[0]);
            if (hVal <= 23 && mVal <= 59) {
                cout << -1 << endl;
                return 0;
            } else {
                cout << 0 << endl;
                return 0;
            }
        }

        // 特判无解：字符最大值对应的数值已超范围
        if (maxDigit > 23 || maxDigit > 59) {
            cout << 0 << endl;
            return 0;
        }

        // 枚举进制，验证合法性
        vector<int> validBases;
        for (int base = minBase; ; base++) {
            int hDec = convertToDec(h, base);
            int mDec = convertToDec(m, base);
            if (hDec > 23 || mDec > 59) break;
            validBases.push_back(base);
        }

        if (validBases.empty()) {
            cout << 0 << endl;
        } else {
            for (int base : validBases) {
                cout << base << " ";
            }
            cout << endl;
        }

        return 0;
    }
    ```
* **代码解读概要**：
    该代码首先读取输入字符串，分割为小时和分钟部分，去除前导零。然后计算所有字符的最大值，确定最小进制。通过特判处理无穷解和无解的情况，最后枚举从最小进制开始的所有可能进制，验证转换后的时间是否合法，输出结果。

---
<code_intro_selected>
接下来，我们将剖析优质题解中的核心代码片段，理解其亮点和实现思路。
</code_intro_selected>

**题解一：作者Rex01**
* **亮点**：通过数组存储每一位的数值，逐位计算进制转换结果，避免幂运算的精度问题。
* **核心代码片段**：
    ```cpp
    for(int i = z1; i < z; i++) {
        if(isdigit(s[i])) {
            int z = s[i] - '0';
            Maxh = max(Maxh, z);
            hh[++cnt1] = z;
        } else {
            int z = s[i] - 'A' + 10;
            Maxh = max(Maxh, z);
            hh[++cnt1] = z;
        }
    }
    // 计算小时的十进制值
    int a = cnt1 - 1;
    h = 0;
    for(int i = 1; i <= cnt1; i++) {
        h += pow(f, a) * hh[i];
        a--;
    }
    ```
* **代码解读**：
    这段代码首先遍历小时部分的字符串，将每个字符转换为数值并存储到数组`hh`中，同时记录最大值`Maxh`。进制转换时，通过`pow(f, a)`计算每一位的权值（f为当前进制，a为位数），累加得到十进制小时值。虽然使用了`pow`函数（可能存在精度问题），但逻辑直观，适合理解进制转换的基本原理。
* 💡 **学习笔记**：数组存储每一位数值是进制转换的常见方法，但需注意`pow`函数的浮点数精度问题（如大数时可能出错）。

**题解二：作者alan1118**
* **亮点**：使用`substr`函数精准截取有效部分，前导零处理简洁。
* **核心代码片段**：
    ```cpp
    for(int i = 0; i < b-1; i++) { // 找到时的第一个非零字符
        if(a[i] == '0') c++;
        else break;
    }
    string h = a.substr(c, b-c); // 截取有效小时部分
    ```
* **代码解读**：
    这段代码通过遍历字符串，统计前导零的个数`c`，然后使用`substr(c, b-c)`截取从第`c`个字符开始的子串，得到去除前导零的小时部分。这种方法简洁高效，避免了复杂的循环处理，是前导零处理的典范。
* 💡 **学习笔记**：`substr`函数是处理字符串截取的利器，合理使用可简化代码逻辑。

**题解三：作者PR_CYJ**
* **亮点**：进制转换时使用逐位累加（`a *= i; a += h[j]`），避免幂运算，更健壮。
* **核心代码片段**：
    ```cpp
    for(int j=0;j<h.size();j++) {
        a *= i;
        a += h[j];
    }
    ```
* **代码解读**：
    这段代码中，`i`是当前进制，`h[j]`是小时部分的第`j`位数值。通过`a *= i`将当前结果左移一位（相当于乘以进制），再加上当前位的数值，逐位累加得到十进制值。这种方法避免了`pow`函数的精度问题，是更可靠的进制转换实现。
* 💡 **学习笔记**：逐位累加的进制转换方法（类似秦九韶算法）更高效、更精确，值得优先使用。

-----

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization_intro\>
为了更直观地理解进制转换和枚举验证的过程，我设计了一个“像素进制探险”动画方案。让我们一起“看”到算法的每一步！
\</visualization_intro\>

  * **动画演示主题**：`像素进制探险——火星时间大挑战`

  * **核心演示内容**：
    展示输入字符串的前导零去除、字符最大值计算、进制枚举验证的全过程。例如，输入“11:20”时，动画会逐步去除前导零（若有），计算字符最大值（'1'和'2'的最大值是2），确定最小进制为3，然后枚举3、4、…等进制，验证转换后的小时和分钟是否合法。

  * **设计思路简述**：
    采用8位像素风格（类似FC游戏界面），用不同颜色的像素块表示小时（红色）和分钟（蓝色）的每一位字符。通过步进控制（单步/自动播放）观察每一步操作，关键步骤（如前导零去除、进制转换）用闪烁或音效提示，增强学习趣味性。

  * **动画帧步骤与交互关键点**：

    1.  **场景初始化 (8位像素风)**：
          * 屏幕分为左右两部分：左侧为“输入区”，显示原始字符串（如“11:20”）；右侧为“处理区”，包含控制面板（开始/暂停、单步、调速滑块）和数据展示区（当前进制、转换后的小时/分钟值）。
          * 播放8位风格的轻快背景音乐（类似《超级玛丽》的开场音乐）。

    2.  **前导零去除**：
          * 输入区的字符串逐字符扫描，前导零（如“000B”中的前三个'0'）用灰色淡化，最后保留有效部分（如“B”），伴随“唰”的音效。

    3.  **字符最大值计算**：
          * 有效部分的每个字符（如“1”、“1”、“2”、“0”）逐个高亮（黄色闪烁），同时屏幕上方显示当前最大值（初始为0，遇到“2”时变为2），最终确定最小进制为3（最大值+1），伴随“叮”的音效。

    4.  **进制枚举验证**：
          * 控制面板点击“开始”后，当前进制从3开始逐步增加（显示在屏幕中央的大数字框中）。
          * 转换过程：小时部分（红色像素块）和分钟部分（蓝色像素块）逐位计算，每一步显示当前位的权值（如3⁰=1，3¹=3）和累加结果，最终得到十进制小时（如1×3 + 1=4）和分钟（如2×3 + 0=6）。
          * 若转换结果合法（小时≤23，分钟≤59），当前进制数字框变为绿色，播放“正确”音效（如短笛声）；若不合法，变为红色，播放“错误”音效（如蜂鸣声），动画停止。

    5.  **无穷解/无解提示**：
          * 若触发无穷解（小时和分钟长度均≤1），屏幕中央弹出“无穷解！”的像素文字，播放“胜利”音效；若无解，弹出“无解！”，播放“失败”音效。

  * **旁白提示 (文字气泡)**：
      * （前导零去除时）“前导零不影响数值，我们只保留有效部分！”
      * （字符最大值计算时）“进制必须大于所有字符的值，所以最小进制是最大值+1哦～”
      * （进制转换时）“看！当前进制是3，小时转换后是4，分钟是6，合法！”

\<visualization_conclusion\>
通过这样的像素动画，我们能直观看到进制转换的每一步，理解前导零处理、最大值计算和枚举验证的逻辑。下次遇到类似问题，你也能像动画中的“探险者”一样轻松解决啦！
\</visualization_conclusion\>

-----

## 6\. 拓展练习与相似问题思考

\<similar_problems_intro\>
理解并掌握了本题的解法后，我们可以进一步思考进制转换和模拟类问题的变形应用。
\</similar_problems_intro\>

  * **通用思路/技巧迁移**：
    本题的核心是进制转换与合法性验证，类似的思路可用于：
    1. 验证其他进制下的数值范围（如八进制数是否为合法IP地址）。
    2. 处理带前导零的字符串（如十六进制颜色码的解析）。
    3. 枚举可能的进制解决数学问题（如判断某个数是否为回文数的多种进制表示）。

  * **练习推荐 (洛谷)**：
    以下是几道与本题考察知识点相关的洛谷题目，建议尝试：

    1.  **洛谷 P1143** - `进制转换`
          * 🗣️ **推荐理由**：直接练习进制转换，巩固将任意进制转换为十进制的技能。
    2.  **洛谷 P1604** - `B进制星球`
          * 🗣️ **推荐理由**：涉及大数的进制转换，需要处理前导零和边界条件，与本题思路高度相关。
    3.  **洛谷 P2113** - `数的进制转换`
          * 🗣️ **推荐理由**：综合考察进制转换与字符串处理，适合提升综合应用能力。

-----

## 7\. 学习心得与经验分享 (若有)

\<insights_intro\>
部分题解作者分享了调试经验，这些对我们有很大参考价值：
\</insights_intro\>

> **参考经验 (来自作者alan1118)**：“我在处理前导零时，一开始直接使用`substr(0)`，导致有效部分被错误截取。后来通过遍历找到第一个非零字符的位置，才正确截取了有效部分。这让我意识到，前导零的处理必须仔细，否则会影响后续所有计算。”
>
> **点评**：alan1118的经验非常实用！前导零的处理是本题的关键步骤之一，直接影响有效位数和无穷解的判断。在编程中，遇到字符串处理问题时，建议先手动模拟几个测试用例，确保逻辑正确。例如，输入“000B:00001”时，手动计算有效部分应为“B”和“1”，这样能帮助验证代码的正确性。

-----

\<conclusion\>
本次关于“Martian Clock”的C++解题分析就到这里。希望这份学习指南能帮助大家掌握进制转换和模拟类问题的解题技巧。记住，编程的关键在于多思考、多实践，遇到问题时可以通过动画模拟或手动计算来验证思路。下次我们再一起探索新的编程挑战！💪
\</conclusion\>

---
处理用时：179.64秒