# 题目信息

# Polycarp and Letters

## 题目描述

Polycarp loves lowercase letters and dislikes uppercase ones. Once he got a string $ s $ consisting only of lowercase and uppercase Latin letters.

Let $ A $ be a set of positions in the string. Let's call it pretty if following conditions are met:

- letters on positions from $ A $ in the string are all distinct and lowercase;
- there are no uppercase letters in the string which are situated between positions from $ A $ (i.e. there is no such $ j $ that $ s[j] $ is an uppercase letter, and $ a_{1}<j<a_{2} $ for some $ a_{1} $ and $ a_{2} $ from $ A $ ).

Write a program that will determine the maximum number of elements in a pretty set of positions.

## 说明/提示

In the first example the desired positions might be $ 6 $ and $ 8 $ or $ 7 $ and $ 8 $ . Positions $ 6 $ and $ 7 $ contain letters 'a', position $ 8 $ contains letter 'b'. The pair of positions $ 1 $ and $ 8 $ is not suitable because there is an uppercase letter 'B' between these position.

In the second example desired positions can be $ 7 $ , $ 8 $ and $ 11 $ . There are other ways to choose pretty set consisting of three elements.

In the third example the given string $ s $ does not contain any lowercase letters, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
11
aaaaBaabAbA
```

### 输出

```
2
```

## 样例 #2

### 输入

```
12
zACaAbbaazzC
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
ABC
```

### 输出

```
0
```

# AI分析结果

# 💡 Kay的C++算法解析：Polycarp and Letters 深入学习指南 💡

<introduction>
  今天我们来一起分析「Polycarp and Letters」这道C++字符串题。这道题看似复杂，其实本质是「找被大写字母分割的小写字母岛，统计每个岛的不同字母数最大值」。跟着Kay的思路，我们会一步步理清逻辑，掌握核心技巧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：模拟（字符串遍历与区域统计）

🗣️ **初步分析**：
解决这道题，关键在于「模拟」——就像在字符串里找**被大写字母隔开的“小写字母小岛”**！每个小岛上的字母必须不同，我们的目标是找到最大的那个小岛的“不同字母数”。  
比如样例1中的字符串`aaaaBaabAbA`，被`B`、`A`等大写字母分割成多个小岛：`aaaa`（1种）、`aab`（2种）、`b`（1种）……最大的就是2，也就是答案。  

**核心思路**：遍历字符串→遇到大写字母分割区域→统计每个区域的不同小写字母数→取最大值。  
**核心难点**：①正确分割区域；②高效统计不同字母；③处理首尾的小写区域。  
**可视化设计思路**：用8位像素风格展示字符串（大写红、小写蓝），小人“探险”收集字母，遇到大写字母就“结算”当前岛的大小，最后闪烁最大数——像玩游戏一样看算法！


---

## 2. 精选优质题解参考

<eval_intro>
我从**思路清晰度、代码可读性、算法效率**三个维度筛选了3份优质题解，它们各有亮点，适合不同学习阶段的你参考～
</eval_intro>

**题解一：_Spectator_ 的极简模拟**
* **点评**：这份题解把问题讲得**最直白**！直接将题目转化为“找连续小写字母段的不同字母数最大值”，用`islower()`/`isupper()`简化字符判断，用数组`js`统计字母是否出现。遇到大写字母就结算最大值并重置，最后还不忘处理末尾的小写区域——逻辑闭环，代码几乎没有冗余，初学者看了秒懂！

**题解二：yxy666 的STL巧解**
* **点评**：用`set`的“自动去重”特性太妙了！遇到小写字母直接`insert`进set，遇到大写字母就统计`set.size()`（即不同字母数）并清空。代码只有短短几行，却把“去重+统计”的逻辑交给STL处理——适合想学习STL简化代码的同学！

**题解三：Fatelism 的底层逻辑实现**
* **点评**：这份题解用`ch[26]`数组直接对应`a-z`的索引，统计时遍历数组求和——**最适合理解底层逻辑**！比如`ch[s[i]-'a']=1`就是标记字母`s[i]`出现过，遇到大写字母就遍历数组算`k`（不同字母数）。代码没有用任何库函数，把“统计不同字母”的过程扒得明明白白！


---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决这道题的过程中，大家常踩的“坑”其实就3个。结合优质题解的经验，Kay帮你把“坑”填上～
</difficulty_intro>

1.  **关键点1：如何正确分割小写区域？**
    * **分析**：大写字母是“分割符”！遍历字符串时，遇到大写字母就说明当前小写区域结束，需要**结算当前区域的统计结果**（比如当前不同字母数），并重置统计工具（数组/set）。比如题解一中，遇到大写字母就执行`ma=max(ma, len)`，然后`len=0`、`memset(js,0,sizeof(js))`。
    * 💡 **学习笔记**：大写字母=“停止键”，遇到就结算！

2.  **关键点2：如何高效统计不同字母？**
    * **分析**：小写字母只有26个，用**布尔数组**（比如`ch[26]`）最快最省空间！也可以用`set`（自动去重，`size`就是不同数）或`unordered_map`（更通用）。题解一用数组，题解二用set，都很高效——选你顺手的！
    * 💡 **学习笔记**：26个字母=26个格子，数组是“性价比之王”！

3.  **关键点3：如何处理首尾的小写区域？**
    * **分析**：如果字符串以小写字母结尾，遍历结束后不会遇到大写字母，所以需要**在循环结束后再结算一次**。比如题解一的`cout<<max(ma, len)`，题解二的`sum=s.size(); ans=max(ans,sum)`——别忘“收尾巴”！
    * 💡 **学习笔记**：首尾情况要单独处理，不然会漏掉最后一个岛！

### ✨ 解题技巧总结
- **模拟问题要“按步走”**：遍历→判断→统计→更新结果，不要跳步骤。
- **利用数据范围简化**：小写字母只有26个，用数组统计比`map`快10倍！
- **边界处理要“补一刀”**：首尾的小写区域，循环结束后再算一次。


---

## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合所有优质题解的通用核心代码**——它用数组统计，逻辑清晰，效率高，适合作为“模板”参考～
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了题解一、三的思路，用数组统计不同字母，单遍历字符串，处理了所有边界情况，是最基础也是最易理解的实现。
* **完整核心代码**：
    ```cpp
    #include <iostream>
    #include <cstring>
    #include <string>
    #include <cctype> // 包含islower/isupper函数
    using namespace std;

    int main() {
        int n;
        string s;
        cin >> n >> s;
        
        int max_cnt = 0;       // 记录最大不同字母数
        int current_cnt = 0;   // 当前区域的不同字母数
        bool exist[26] = {false}; // 标记当前区域的字母是否出现过

        for (char c : s) {
            if (islower(c)) { // 是小写字母
                int idx = c - 'a'; // 转换为0-25的索引
                if (!exist[idx]) { // 之前没出现过
                    exist[idx] = true;
                    current_cnt++;
                }
            } else { // 是大写字母，分割区域
                if (current_cnt > max_cnt) {
                    max_cnt = current_cnt;
                }
                current_cnt = 0;
                memset(exist, 0, sizeof(exist)); // 重置标记数组
            }
        }
        // 处理字符串末尾的小写区域
        if (current_cnt > max_cnt) {
            max_cnt = current_cnt;
        }

        cout << max_cnt << endl;
        return 0;
    }
    ```
* **代码解读概要**：  
  1. 用`exist`数组标记当前区域的字母是否出现（`exist[idx]=true`表示字母`'a'+idx`出现过）；  
  2. 遍历每个字符：小写字母更新`exist`和`current_cnt`，大写字母结算`max_cnt`并重置；  
  3. 最后处理末尾的小写区域，输出`max_cnt`。

---

<code_intro_selected>
接下来看3份优质题解的**核心片段**，感受不同实现方式的亮点～
</code_intro_selected>

**题解一：_Spectator_ 的极简判断**
* **亮点**：用`islower()`/`isupper()`简化字符判断，代码逻辑像“说话一样自然”。
* **核心代码片段**：
    ```cpp
    for(int i=0;i<n;i++){　
        if(islower(st[i])&&js[st[i]]==0) // 小写且未出现过
            len++,js[st[i]]=1;　
        if(isupper(st[i])){ // 大写字母，结算
            ma=max(ma,len);
            len=0;
            memset(js,0,sizeof(js));
        }
    }　
    cout<<max(ma,len); // 处理末尾
    ```
* **代码解读**：  
  - `islower(st[i])`判断是否是小写字母，`js[st[i]]==0`判断是否未出现过；  
  - 遇到大写字母，用`max(ma, len)`更新最大值，然后重置`len`和`js`数组；  
  - 最后`max(ma, len)`处理末尾的小写区域——逻辑完美闭环！
* 💡 **学习笔记**：标准库函数（`islower`/`isupper`）能帮你少写很多判断条件！

**题解二：yxy666 的STL巧解**
* **亮点**：用`set`的“自动去重”特性，把“统计不同字母”的工作交给STL，代码超短！
* **核心代码片段**：
    ```cpp
    set<char> s; // 自动去重的集合
    for(int i=1;i<=n;i++){
        if(a[i]>='A'&&a[i]<='Z'){ // 大写字母，结算
            sum=s.size(); // set的大小就是不同字母数
            s.clear();    // 清空集合
            ans=max(sum,ans);
        }
        else s.insert(a[i]); // 小写字母插入集合
    }
    sum=s.size(); // 处理末尾
    ans=max(ans,sum);
    ```
* **代码解读**：  
  - `set`的`insert`方法会自动忽略重复元素，所以`set.size()`就是当前区域的不同字母数；  
  - 遇到大写字母，统计`set.size()`并清空——比数组统计少写了“遍历求和”的步骤！
* 💡 **学习笔记**：STL是“懒人神器”，但要先理解它的原理（比如`set`的去重逻辑）！

**题解三：Fatelism 的底层实现**
* **亮点**：用数组直接对应字母索引，把“统计不同字母”的底层逻辑扒得明明白白！
* **核心代码片段**：
    ```cpp
    int ch[26]={}; // 对应a-z的出现情况
    for(int i=0;i<s.length();i++){
        if(s[i]>='a'&&s[i]<='z'){ // 小写字母
            ch[s[i]-'a']=1; // 标记为已出现
        } else { // 大写字母，结算
            int k=0;
            for(int j=0;j<26;j++) if(ch[j]==1) k++; // 统计不同字母数
            if(k>max) max=k;
            memset(ch,0,sizeof(ch)); // 重置数组
        }
    }
    // 处理末尾
    int k=0;
    for(int j=0;j<26;j++) if(ch[j]==1) k++;
    if(k>max) max=k;
    ```
* **代码解读**：  
  - `s[i]-'a'`把小写字母转换为0-25的索引（比如`'a'`→0，`'b'`→1）；  
  - 遇到大写字母，遍历`ch`数组统计`k`（`ch[j]==1`的数量就是不同字母数）；  
  - 最后再遍历一次`ch`数组处理末尾——没有用任何库函数，纯底层逻辑！
* 💡 **学习笔记**：想理解“统计不同字母”的本质，就用数组实现一次！


---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地“看”到算法流程，Kay设计了一个**8位像素风的“字母岛探险”动画**——像玩FC游戏一样学算法！
</visualization_intro>

### 🎮 动画演示主题：像素小人的字母岛探险
**设计思路**：用FC红白机的8位风格，把字符串变成“岛屿”，大写字母是红色障碍，小写字母是蓝色方块，不同字母用不同颜色（比如`a`浅蓝、`b`深蓝）。小人收集字母，遇到障碍就结算当前岛的大小，最后显示最大数——**用游戏感强化记忆**！

### 🕹️ 动画帧步骤与交互设计
1. **场景初始化**（FC风格）：  
   - 屏幕上方是**16x16像素的字符串块**：大写字母（红）、小写字母（蓝），排列成一行；  
   - 下方是**控制面板**：开始/暂停、单步、重置按钮（像素风格），速度滑块（1x-5x）；  
   - 右侧是**统计面板**：当前岛字母数（黄色）、最大字母数（绿色）；  
   - 背景是浅灰色，播放8位风格的轻快BGM（比如《超级马里奥》的背景音乐）。

2. **算法启动**：  
   - 一个**黄色16x16像素的小人**站在字符串起点，统计面板显示：当前0，最大0。

3. **核心遍历流程**（单步/自动模式）：  
   - **单步模式**：点击“单步”，小人移动到下一个字符：  
     - 如果是小写字母且未收集过：字母块变成对应颜色（比如`a`变浅蓝），统计面板“当前数”+1，播放**“叮”**的像素音效；  
     - 如果是小写字母但已收集过：字母块闪烁2次，不加分；  
     - 如果是大写字母（红色块）：小人停下，统计面板“当前数”闪烁，“最大数”更新（如果当前数更大），播放**“咚”**的音效，然后小人跳到下一个字符，“当前数”重置为0，已收集的字母块变回蓝色。  
   - **自动模式**：点击“自动”，小人按滑块速度自动移动，流程同上，音效同步。

4. **结束状态**：  
   - 小人走到字符串末尾，统计面板“最大数”闪烁，播放**“啦啦啦”**的胜利音效，背景出现像素星星（黄色小方块）。

5. **交互设计**：  
   - 重置按钮：回到初始状态，重新开始；  
   - 速度滑块：调整自动模式的播放速度（1x最慢，5x最快）；  
   - 代码同步：屏幕下方显示当前步骤对应的C++核心代码（比如“处理小写字母：exist[idx] = true; current_cnt++;”），当前执行行高亮。

### 🎵 音效设计（增强记忆）
- 收集新字母：轻微“叮”声（提示“这个字母是新的！”）；  
- 遇到大写字母：短促“咚”声（提示“区域结束，结算！”）；  
- 更新最大数：轻快“滴”声（提示“找到更大的岛了！”）；  
- 胜利：8位风格的“啦啦啦”音乐（强化成就感）。

<visualization_conclusion>
通过这个动画，你能**直观看到每个步骤的变化**：小人怎么移动，字母怎么收集，大写字母怎么分割区域，最大数怎么更新。比看代码更有趣，比听讲解更深刻！
</visualization_conclusion>


---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了“模拟字符串遍历+区域统计”的思路后，你可以解决很多类似的问题！Kay给你推荐几个洛谷的练习，帮你巩固技巧～
</similar_problems_intro>

### 🧠 通用思路迁移
“模拟+区域统计”的思路，还能解决这些问题：
1. 统计字符串中**每个单词的长度最大值**（用空格分割）；  
2. 统计数组中**被0分隔的子数组的和最大值**；  
3. 统计日志中**每个时间段的访问次数最大值**（用时间戳分割）。

### 📚 洛谷练习推荐
1. **洛谷 P1055** - 谁拿了最多奖学金  
   🗣️ **推荐理由**：需要处理字符串（姓名、班级）和多个条件判断，锻炼“模拟+多条件统计”的能力！  
2. **洛谷 P1553** - 数字反转  
   🗣️ **推荐理由**：需要反转字符串（处理前导零），锻炼“字符串遍历+边界处理”的能力！  
3. **洛谷 P1200** - 你的飞碟在这儿  
   🗣️ **推荐理由**：需要将字符串转换为数字（哈希），锻炼“字符串处理+数学计算”的能力！  
4. **洛谷 P2010** - 回文日期  
   🗣️ **推荐理由**：需要处理日期字符串（判断回文、合法日期），锻炼“字符串遍历+复杂条件判断”的能力！


---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中最有价值的，往往是作者的“踩坑心得”。比如_Spectator_的提示，比代码更重要！
</insights_intro>

> **参考经验 (来自_Spectator_)**：“题解千万条，理解第一条。直接粘题解，棕名两行泪。”  
> **点评**：这句话戳中了很多人的“痛点”！直接复制代码不仅学不到东西，还可能因为不理解逻辑而写错（比如漏处理末尾区域）。正确的做法是：**先理解思路，再自己写代码，遇到问题再看题解**——这样才能真正掌握算法！


---

<conclusion>
本次关于「Polycarp and Letters」的分析就到这里啦！这道题的核心是“模拟字符串遍历+区域统计”，关键是处理好分割和边界。记住：**理解思路比复制代码重要，多练比多看重要**！下次我们再一起探索更有趣的算法问题～💪
</conclusion>

---
处理用时：484.40秒