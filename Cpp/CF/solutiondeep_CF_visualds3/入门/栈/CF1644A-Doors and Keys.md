# 题目信息

# Doors and Keys

## 题目描述

The knight is standing in front of a long and narrow hallway. A princess is waiting at the end of it.

In a hallway there are three doors: a red door, a green door and a blue door. The doors are placed one after another, however, possibly in a different order. To proceed to the next door, the knight must first open the door before.

Each door can be only opened with a key of the corresponding color. So three keys: a red key, a green key and a blue key — are also placed somewhere in the hallway. To open the door, the knight should first pick up the key of its color.

The knight has a map of the hallway. It can be transcribed as a string, consisting of six characters:

- R, G, B — denoting red, green and blue doors, respectively;
- r, g, b — denoting red, green and blue keys, respectively.

Each of these six characters appears in the string exactly once.

The knight is standing at the beginning of the hallway — on the left on the map.

Given a map of the hallway, determine if the knight can open all doors and meet the princess at the end of the hallway.

## 说明/提示

In the first testcase, the knight first collects all keys, then opens all doors with them.

In the second testcase, there is a red door right in front of the knight, but he doesn't have a key for it.

In the third testcase, the key to each door is in front of each respective door, so the knight collects the key and uses it immediately three times.

In the fourth testcase, the knight can't open the blue door.

## 样例 #1

### 输入

```
4
rgbBRG
RgbrBG
bBrRgG
rgRGBb```

### 输出

```
YES
NO
YES
NO```

# AI分析结果

# 💡 Kay的C++算法解析：Doors and Keys 深入学习指南 💡

<introduction>
今天我们来一起分析"Doors and Keys"这道C++编程题。这道题像是一场"骑士闯关小游戏"——骑士要穿过走廊见到公主，必须先拿到对应颜色的钥匙才能打开门。本指南会帮你理清思路，掌握核心模拟技巧，还能通过像素动画直观看到算法运行过程！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟应用  

🗣️ **初步分析**：  
解决这道题的关键是**模拟骑士的闯关过程**——就像你玩"超级玛丽"收集金币再通关一样，骑士只能从左到右走，遇到钥匙就"捡起来"，遇到门就"检查有没有对应的钥匙"。如果所有门都能顺利打开，就能见到公主啦！  

### 核心思路与难点
- **核心逻辑**：遍历字符串（走廊），用变量记录"是否拿到了红/绿/蓝钥匙"；遇到门时，检查对应钥匙是否已收集——没收集就无法通过（输出NO），全部通过则输出YES。  
- **常见难点**：① 多组数据要重置钥匙状态（不然上一局的钥匙会带到下一局！）；② 钥匙和门要对应（比如R门必须用r钥匙开）；③ 遇到无法通过的门要立刻停止遍历（节省时间）。  

### 可视化设计思路
我会设计一个**8位像素风的"骑士闯关动画"**：  
- 走廊是一排8x8的像素块，钥匙是亮彩色（r红、g绿、b蓝），门是深彩色（R深红、G深绿、B深蓝），骑士是一个小像素人。  
- 骑士从左到右移动：收集钥匙时，钥匙块闪烁并消失，骑士的"钥匙栏"对应颜色亮起；遇到门时，如果有钥匙，门会"吱呀"打开（变成透明）；如果没钥匙，门变红，骑士停止并播放"嘟"的错误音效。  
- 交互设计：有"单步执行"（看每一步细节）、"自动播放"（调速滑块控制速度）、"重置"按钮，还有8位风格的背景音乐！


## 2. 精选优质题解参考

<eval_intro>
我从"思路清晰度""代码可读性""实践价值"三个维度筛选了3份优质题解，帮你快速掌握不同的实现方式～
</eval_intro>

**题解一：作者Eason_AC（赞：7）**  
* **点评**：这份题解的思路像"找位置游戏"——直接用`find()`函数找钥匙和门的位置，如果钥匙的位置在门之后，就无法通过。代码超级简洁（只有几行核心逻辑），适合理解题目本质：**钥匙必须在门左边**。但需要注意`find()`函数的返回值是字符第一次出现的位置（正好符合本题"每个字符出现一次"的条件）。

**题解二：作者SunSkydp（赞：3）**  
* **点评**：这份题解用`switch`语句模拟骑士的每一步，逻辑像"做选择题"——遇到小写字母就标记钥匙，遇到大写字母就检查钥匙。代码结构清晰，变量命名直观（`r/g/b`表示是否有钥匙），还特别注意了"每组数据要重置变量"（比如`r = 0, g = 0, b = 0`），非常严谨。

**题解三：作者xieyikai2333（赞：3）**  
* **点评**：这份题解用数组`key[26]`记录钥匙状态，利用ASCII码的规律（小写字母比大写字母大32，比如'r'-'a'=17，'R'-'A'=17），直接对应钥匙和门。代码高效且通用（如果有更多颜色也能轻松扩展），还提到了"清空数组"的重要性——多组数据一定要重置状态！


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题时，大家常犯的"小错误"其实是三个"关键细节"。结合优质题解，我帮你总结了应对策略：
</difficulty_intro>

1. **关键点1：多组数据的状态重置**  
   * **问题**：如果上一组数据的钥匙状态没清空，下一组数据会"继承"之前的钥匙，导致错误（比如上组拿到了r钥匙，下组没拿到r但门R会被误判为可通过）。  
   * **解法**：每组数据开始时，一定要把钥匙状态重置为"未拿到"（比如`r = 0, g = 0, b = 0`或`memset(key, false, sizeof(key))`）。  
   * 💡 **学习笔记**：多组数据的"初始化"是模拟题的必查点！

2. **关键点2：钥匙与门的正确对应**  
   * **问题**：容易把R对应成g钥匙，或者G对应成b钥匙，导致逻辑错误。  
   * **解法**：用"一一对应"的规律：① 小写字母是钥匙，大写是门；② 相同字母的大小写对应（比如'r'对应'R'，'g'对应'G'）。可以用ASCII码计算（比如`门字符 - 'A' = 钥匙字符 - 'a'`），或者直接写死对应关系。  
   * 💡 **学习笔记**："对应关系"要写清楚，避免"张冠李戴"！

3. **关键点3：及时终止遍历**  
   * **问题**：遇到无法通过的门时，继续遍历后面的字符是没用的，但会浪费时间（虽然本题字符串只有6位，但养成好习惯很重要）。  
   * **解法**：用一个`flag`变量标记是否"无法通过"，一旦`flag`变`false`，就用`break`停止遍历。比如SunSkydp的题解中，`if(!flag) break;`就是这个思路。  
   * 💡 **学习笔记**："提前终止"能让代码更高效！

### ✨ 解题技巧总结
- **技巧1：用变量/数组记录状态**：模拟题的核心是"状态管理"——用布尔变量或数组记录"是否拿到钥匙"，清晰又方便。  
- **技巧2：利用字符规律简化代码**：比如ASCII码中，小写字母比大写字母大32，用`门字符 - 'A' = 钥匙字符 - 'a'`可以快速对应钥匙和门。  
- **技巧3：多组数据要初始化**：每组数据开始时，一定要重置所有状态变量，避免"历史残留"！


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一个**通用的模拟实现**——它综合了SunSkydp和xieyikai2333的思路，逻辑清晰，适合初学者理解：
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码用布尔变量记录钥匙状态，遍历字符串模拟骑士的闯关过程，逻辑直观，适合入门学习。  
* **完整核心代码**：
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        bool has_r = false, has_g = false, has_b = false; // 记录是否拿到钥匙
        bool can_pass = true; // 是否能通过所有门
        for (char c : s) { // 遍历走廊的每一个位置
            switch (c) {
                case 'r': has_r = true; break;
                case 'g': has_g = true; break;
                case 'b': has_b = true; break;
                case 'R': if (!has_r) can_pass = false; break;
                case 'G': if (!has_g) can_pass = false; break;
                case 'B': if (!has_b) can_pass = false; break;
            }
            if (!can_pass) break; // 无法通过，停止遍历
        }
        cout << (can_pass ? "YES" : "NO") << endl;
    }
    return 0;
}
```
* **代码解读概要**：  
  1. 读入测试用例数`t`，循环处理每组数据；  
  2. 初始化"是否有钥匙"的布尔变量（`has_r/has_g/has_b`）和"是否能通过"的标记`can_pass`；  
  3. 遍历字符串`s`的每个字符：  
     - 遇到钥匙（小写字母），标记对应`has_*`为`true`；  
     - 遇到门（大写字母），检查对应`has_*`是否为`true`——不是就把`can_pass`设为`false`；  
  4. 一旦`can_pass`为`false`，立刻停止遍历（`break`）；  
  5. 输出结果（`can_pass`为`true`则输出YES，否则NO）。


<code_intro_selected>
接下来看三个优质题解的核心片段，学习它们的"巧妙之处"：
</code_intro_selected>

**题解一：作者Eason_AC**  
* **亮点**：用`find()`函数直接比较位置，代码极简，直击问题本质（钥匙必须在门左边）。  
* **核心代码片段**：
```cpp
if(s.find("r") > s.find("R") || s.find("b") > s.find("B") || s.find("g") > s.find("G"))
    puts("NO");
else
    puts("YES");
```
* **代码解读**：  
  `s.find(c)`返回字符`c`在字符串中的位置（从0开始）。比如`s.find("r") > s.find("R")`表示r钥匙的位置在R门之后——无法通过！三个条件只要有一个满足，就输出NO。  
* 💡 **学习笔记**：如果问题的核心是"位置关系"，用`find()`函数能快速解决！

**题解二：作者SunSkydp**  
* **亮点**：用`switch`语句处理所有情况，逻辑清晰，容易调试。  
* **核心代码片段**：
```cpp
for(int i = 0; i < s.size(); i++) {
    switch (s[i]) {
        case 'r': r = 1; break;
        case 'g': g = 1; break;
        case 'b': b = 1; break;
        case 'R': if(r == 0) flag = false; break;
        case 'G': if(g == 0) flag = false; break;
        case 'B': if(b == 0) flag = false; break;
    }
    if(!flag) break;
}
```
* **代码解读**：  
  遍历每个字符，用`switch`分情况处理：遇到钥匙就把对应变量设为1，遇到门就检查对应变量是否为1。一旦`flag`变`false`（无法通过），立刻`break`停止遍历。  
* 💡 **学习笔记**：`switch`语句适合"多分支判断"，比多个`if-else`更整洁！

**题解三：作者xieyikai2333**  
* **亮点**：用数组`key[26]`记录钥匙状态，利用ASCII码规律，扩展性强。  
* **核心代码片段**：
```cpp
bool key[26];
memset(key, false, sizeof(key)); // 重置钥匙状态
for(int i=0;i<6;i++) {
    if('a'<=s[i]&&s[i]<='z') key[s[i]-'a']=true; // 拿到钥匙
    else if(!key[s[i]-'A']) return false; // 没钥匙，无法通过
}
```
* **代码解读**：  
  数组`key[26]`对应26个小写字母，`s[i]-'a'`计算出字母的索引（比如'r'-'a'=17）。遇到小写字母，就把对应`key`设为`true`；遇到大写字母，计算`key[s[i]-'A']`（比如'R'-'A'=17，对应'r'的索引）——如果为`false`，就返回`false`。  
* 💡 **学习笔记**：数组适合"批量管理状态"，如果有更多颜色（比如'y'钥匙对应'Y'门），只需扩展数组即可！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地"看"到骑士闯关的过程，我设计了一个**8位像素风的动画**——像玩FC游戏一样学算法！
</visualization_intro>

### 动画设计详情
#### 1. 整体风格与场景
- **像素风格**：采用FC红白机的8位色板（比如背景#E0E0E0，钥匙#FF0000（r）、#00FF00（g）、#0000FF（b），门#CC0000（R）、#00CC00（G）、#0000CC（B），骑士#000000（黑）+ #FFFF00（黄））。  
- **场景布局**：屏幕左侧是"走廊"（6个8x8的像素块排成一排），右侧是"控制面板"（开始/暂停、单步、重置按钮，速度滑块），底部是"钥匙栏"（3个小像素块，对应红、绿、蓝钥匙的状态）。

#### 2. 核心动画步骤
1. **初始化**：  
   - 走廊显示输入的字符串（比如"rgbBRG"），每个字符对应一个像素块；  
   - 钥匙栏全灰（表示没拿到钥匙）；  
   - 骑士站在第一个像素块左侧；  
   - 播放8位风格的背景音乐（比如《超级玛丽》的开头旋律）。

2. **单步执行/自动播放**：  
   - 骑士移动到下一个像素块：如果是钥匙（小写字母），钥匙块闪烁3次后消失，钥匙栏对应颜色变亮（比如拿到'r'，钥匙栏红色块变亮），同时播放"叮"的音效；  
   - 如果是门（大写字母）：  
     - 有钥匙：门块变成透明（表示打开），播放"吱呀"的音效，骑士继续前进；  
     - 没钥匙：门块变红，骑士停止移动，播放"嘟"的错误音效，弹出提示框"没钥匙！无法通过"。

3. **目标达成**：  
   - 骑士走到走廊尽头（第6个像素块右侧），播放"胜利"音效（比如《魂斗罗》的通关音乐），屏幕显示"恭喜！见到公主啦～"，并弹出"再来一局？"的按钮。

#### 3. 交互设计
- **控制面板**：  
  - "开始/暂停"：控制动画播放/暂停；  
  - "单步"：点击一次，骑士走一步；  
  - "重置"：恢复初始状态，重新开始；  
  - "速度滑块"：调节自动播放的速度（从"很慢"到"很快"）。  
- **AI自动演示**：点击"AI演示"按钮，动画会自动执行，像"游戏AI"一样完成闯关，你可以观察每一步的细节。

#### 4. 为什么这样设计？
- **像素风格**：复古游戏的感觉能降低学习的"距离感"，让你更愿意探索；  
- **音效与动画**：用"叮""吱呀""嘟"的声音强化"收集钥匙""开门""错误"的记忆，比纯文字更直观；  
- **交互控制**：单步执行能让你仔细看每一步的逻辑，自动播放能快速看整体流程，适合不同的学习节奏。


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
模拟是编程中最基础也最常用的技巧——比如游戏中的角色移动、数据的流程处理，都能用模拟解决。掌握了这道题的模拟思路，你可以尝试以下问题：
</similar_problems_intro>

### 通用思路迁移
- **场景1**：游戏中的"捡道具开门"（比如《塞尔达传说》中捡钥匙开宝箱）；  
- **场景2**：数据的"流程验证"（比如检查密码是否符合"先有数字再有字母"的规则）；  
- **场景3**：物流中的"路径规划"（比如快递必须经过某个站点才能送达）。

### 洛谷练习推荐
1. **洛谷 P1002 过河卒**  
   * 🗣️ **推荐理由**：这道题需要模拟卒的移动路径，判断是否能到达终点——和本题的"骑士闯关"逻辑类似，能巩固模拟技巧。  
2. **洛谷 P1047 校门外的树**  
   * 🗣️ **推荐理由**：这道题需要模拟"砍树"的过程，记录树的状态——和本题的"记录钥匙状态"思路一致，能锻炼状态管理能力。  
3. **洛谷 P1161 开灯**  
   * 🗣️ **推荐理由**：这道题需要模拟"开关灯"的过程，判断最终的灯状态——和本题的"遍历+状态修改"逻辑相同，能提升代码的严谨性。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
很多作者在题解中分享了"踩坑"的经历，这些经验能帮你避免犯同样的错误：
</insights_intro>

> **参考经验（来自SunSkydp）**："我一开始忘记重置变量，导致下一组数据的钥匙状态继承了上一组，结果错了好几个测试用例。后来加上`r = 0, g = 0, b = 0`才通过。"  
> **点评**：这个经验太重要了！多组数据的"初始化"是模拟题的"必踩坑点"——一定要记得重置所有状态变量，不然会像"上一局的金币带到下一局"一样，导致逻辑错误。  
> **参考经验（来自xieyikai2333）**："我一开始用`if-else`处理字符，代码很长，后来用ASCII码计算索引，代码简洁了很多。"  
> **点评**：利用字符的ASCII码规律能简化代码——比如小写字母比大写字母大32，这样就能用一个数组处理所有钥匙和门的对应关系，不用写多个`if`判断！


<conclusion>
本次关于"Doors and Keys"的分析就到这里啦～这道题的核心是"模拟骑士的闯关过程"，关键是"状态管理"和"细节处理"。记住：模拟题的本质是"按步骤复现逻辑"，只要理清每一步该做什么，就能轻松解决！  

下次我们再一起探索更有趣的算法问题～💪
</conclusion>

---
处理用时：994.71秒