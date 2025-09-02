# 题目信息

# Lost in Transliteration

## 题目描述

There are some ambiguities when one writes Berland names with the letters of the Latin alphabet.

For example, the Berland sound u can be written in the Latin alphabet as "u", and can be written as "oo". For this reason, two words "ulyana" and "oolyana" denote the same name.

The second ambiguity is about the Berland sound h: one can use both "h" and "kh" to write it. For example, the words "mihail" and "mikhail" denote the same name.

There are $ n $ users registered on the Polycarp's website. Each of them indicated a name represented by the Latin letters. How many distinct names are there among them, if two ambiguities described above are taken into account?

Formally, we assume that two words denote the same name, if using the replacements "u" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/77b2db707b29a82aec640f23cbd1fafe4293bbb0.png) "oo" and "h" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/77b2db707b29a82aec640f23cbd1fafe4293bbb0.png) "kh", you can make the words equal. One can make replacements in both directions, in any of the two words an arbitrary number of times. A letter that resulted from the previous replacement can participate in the next replacements.

For example, the following pairs of words denote the same name:

- "koouper" and "kuooper". Making the replacements described above, you can make both words to be equal: "koouper" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kuuper" and "kuooper" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kuuper".
- "khun" and "kkkhoon". With the replacements described above you can make both words to be equal: "khun" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "khoon" and "kkkhoon" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "kkhoon" ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF883F/355fee5161a1808ee95ea5dc6d815d4071657131.png) "khoon".

For a given list of words, find the minimal number of groups where the words in each group denote the same name.

## 说明/提示

There are four groups of words in the first example. Words in each group denote same name:

1. "mihail", "mikhail"
2. "oolyana", "ulyana"
3. "kooooper", "koouper"
4. "hoon", "khun", "kkkhoon"

There are five groups of words in the second example. Words in each group denote same name:

1. "hariton", "kkkhariton", "khariton"
2. "hkariton"
3. "buoi", "boooi", "boui"
4. "bui"
5. "boi"

In the third example the words are equal, so they denote the same name.

## 样例 #1

### 输入

```
10
mihail
oolyana
kooooper
hoon
ulyana
koouper
mikhail
khun
kuooper
kkkhoon
```

### 输出

```
4
```

## 样例 #2

### 输入

```
9
hariton
hkariton
buoi
kkkhariton
boooi
bui
khariton
boui
boi
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2
alex
alex
```

### 输出

```
1
```

# AI分析结果

# 💡 Kay的C++算法解析：Lost in Transliteration 深入学习指南 💡


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：编程技巧应用（字符串标准化与去重）

🗣️ **初步分析**：  
解决“Lost in Transliteration”的关键，是将具有歧义的字符串转换为**唯一的标准形式**（就像给每个名字办一张“身份证”）。比如“khun”和“kkkhoon”都能转换成“hoon”，这样就能通过比较标准形式来判断是否为同一个名字。  
- **核心思路**：处理两种歧义：  
  1. 将“u”替换为“oo”（因为“oo”是两个字符，替换后不会产生新的歧义，比如“u”→“oo”，而“oo”不能反向替换成“u”，否则会混淆“oou”和“uoo”）；  
  2. 将“h”前面的所有“k”去掉（比如“kkkh”→“h”，“kh”→“h”）。  
- **核心难点**：正确处理“h”前面的多个“k”（不能漏掉，也不能多删）；高效处理字符串（避免频繁修改导致的性能问题）。  
- **可视化设计思路**：用像素动画展示字符串转换的每一步——比如“khun”→“hun”（去掉“k”）→“hoon”（替换“u”为“oo”）。用不同颜色标记要处理的字符（如“k”是红色，“h”是蓝色，“u”是绿色），替换时伴随“叮”的音效，完成时显示“胜利”动画（比如像素星星闪烁）。  


## 2. 精选优质题解参考

为大家筛选了3份思路清晰、代码简洁的优质题解，一起来看看它们的亮点吧！


### **题解一：来源：LKY928261**  
* **点评**：这份题解的“空格代替法”非常巧妙！处理“h”前面的“k”时，没有直接删除（`erase`函数时间复杂度高），而是用空格标记要删除的“k”，最后统一处理。这样既避免了频繁修改字符串，又保证了正确性。代码结构清晰，变量命名简洁（比如用`a[i]`存储处理后的字符串），非常适合初学者借鉴。


### **题解二：来源：King_duck**  
* **点评**：此题解用`erase`函数直接删除“h”前面的“k”，逻辑直白易懂。比如找到“h”后，向前遍历所有“k”，然后用`erase`删除这些“k”。代码中的`foo`函数封装了字符串处理逻辑，复用性强。另外，用`set`存储标准串，自动去重，非常方便。


### **题解三：来源：codeLJH114514**  
* **点评**：这份题解的“基本串”概念非常清晰！将每个字符串转换为“基本串”（即标准形式），然后用`set`统计数量。代码中的`Mission`函数处理“u”和“h”的歧义，逻辑简洁，容易理解。比如处理“h”时，从前往后找，删除前面的“k”，步骤明确。


## 3. 核心难点辨析与解题策略

在解决这个问题时，我们会遇到3个核心难点，一起来看看如何解决，以及优质题解中的做法：


### **1. 如何正确处理“h”前面的多个“k”？**  
* **分析**：“h”前面可能有1个或多个“k”（比如“kkkh”→“h”），需要全部删除。优质题解中，LKY928261用空格标记“k”，最后统一删除；King_duck用`erase`直接删除；codeLJH114514从前往后找“h”，然后删除前面的“k”。这些方法都能正确处理多个“k”的情况。  
* 💡 **学习笔记**：处理连续字符时，标记法（用空格或其他字符标记）可以避免频繁修改字符串，提高效率。


### **2. 如何避免“u”和“oo”替换时的错误？**  
* **分析**：如果将“oo”替换为“u”，会导致“oou”和“uoo”转换成不同的字符串（比如“oou”→“uu”，“uoo”→“uoo”），而实际上它们是同一个名字。因此，必须将“u”替换为“oo”（比如“u”→“oo”，“oou”→“oooo”，“uoo”→“oooo”）。  
* 💡 **学习笔记**：对于“单字符↔多字符”的替换，应将单字符替换为多字符，避免歧义。


### **3. 如何高效处理字符串？**  
* **分析**：字符串的`erase`和`replace`函数会修改字符串的长度，频繁使用会导致性能问题。LKY928261用空格标记要删除的“k”，最后统一处理，减少了`erase`的次数；King_duck用`erase`直接删除，但逻辑清晰，对于题目中的数据规模（字符串长度不会太大）完全适用。  
* 💡 **学习笔记**：对于小规模数据，逻辑清晰比性能优化更重要；对于大规模数据，可以用标记法或其他高效方法。


### ✨ 解题技巧总结  
- **字符串标准化**：将歧义字符转换为唯一的标准形式，是解决此类问题的核心。  
- **替换顺序**：先处理“u”还是“h”？其实顺序不影响结果，但建议先处理“u”（因为“u”替换为“oo”不会影响“h”的处理）。  
- **数据结构选择**：用`set`或`map`存储标准串，自动去重，非常方便。


## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考  
* **说明**：综合了优质题解的思路，用`set`存储标准串，处理“u”和“h”的歧义。  
* **完整核心代码**：  
  ```cpp
  #include <iostream>
  #include <string>
  #include <set>
  using namespace std;

  string standardize(string s) {
      // 处理“u”→“oo”
      for (int i = 0; i < s.size(); ) {
          if (s[i] == 'u') {
              s.replace(i, 1, "oo");
              i += 2; // 跳过替换后的“oo”
          } else {
              i++;
          }
      }
      // 处理“h”前面的“k”
      for (int i = 0; i < s.size(); ) {
          if (s[i] == 'h') {
              int j = i - 1;
              while (j >= 0 && s[j] == 'k') {
                  j--;
              }
              // 删除j+1到i-1的“k”
              s.erase(j + 1, i - j - 1);
              i = j + 1; // 调整i的位置
          } else {
              i++;
          }
      }
      return s;
  }

  int main() {
      int n;
      cin >> n;
      set<string> unique_names;
      for (int i = 0; i < n; i++) {
          string s;
          cin >> s;
          unique_names.insert(standardize(s));
      }
      cout << unique_names.size() << endl;
      return 0;
  }
  ```  
* **代码解读概要**：  
  1. `standardize`函数：将字符串转换为标准形式。首先处理“u”→“oo”，然后处理“h”前面的“k”。  
  2. `main`函数：读入n个字符串，将每个字符串转换为标准形式，存入`set`（自动去重），最后输出`set`的大小（即不同名字的数量）。


### 针对各优质题解的片段赏析

#### **题解一：LKY928261（空格代替法）**  
* **亮点**：用空格标记要删除的“k”，避免频繁`erase`。  
* **核心代码片段**：  
  ```cpp
  for (j = s.size() - 1; j > 0; j--) {
      if (s[j] == 'h') {
          for (j--; j >= 0 && s[j] == 'k'; j--) {
              s[j] = ' '; // 用空格标记要删除的k
          }
          j++;
      }
  }
  // 处理空格和u
  for (j = 0; j < s.size(); j++) {
      if (s[j] != ' ') {
          if (s[j] == 'u') {
              a[i] += "oo";
          } else {
              a[i] += s[j];
          }
      }
  }
  ```  
* **代码解读**：  
  - 第一步：从后往前找“h”，将前面的“k”标记为空格。  
  - 第二步：遍历字符串，跳过空格，将“u”替换为“oo”，其他字符保留。  
* 💡 **学习笔记**：标记法是处理连续字符删除的好方法，能提高效率。


#### **题解二：King_duck（直接erase法）**  
* **亮点**：用`erase`直接删除“k”，逻辑清晰。  
* **核心代码片段**：  
  ```cpp
  if (st[i] == 'h') {
      int j = i - 1;
      while (j >= 0 && st[j] == 'k') {
          j--;
      }
      st.erase(j + 1, i - j - 1);
      i = j + 1;
  }
  ```  
* **代码解读**：  
  - 找到“h”后，向前遍历所有“k”，然后用`erase`删除这些“k”。  
  - `i = j + 1`：调整i的位置，避免重复处理。  
* 💡 **学习笔记**：`erase`函数的参数是（起始位置，长度），使用时要注意调整索引。


#### **题解三：codeLJH114514（基本串概念）**  
* **亮点**：用“基本串”概念，逻辑简洁。  
* **核心代码片段**：  
  ```cpp
  std::string Mission(std::string S) {
      for (int i = 0; i < S.size(); i++) {
          if (S[i] == 'h') {
              int j = i - 1;
              while (j >= 0 && S[j] == 'k')
                  j -= 1;
              S.erase(j + 1, i - j - 1);
              i = j + 1;
          } else if (S[i] == 'u')
              S.replace(i, 1, "oo");
      }
      return S;
  }
  ```  
* **代码解读**：  
  - `Mission`函数返回字符串的“基本串”（标准形式）。  
  - 处理“h”和“u”的歧义，逻辑清晰。  
* 💡 **学习笔记**：封装函数能提高代码的复用性和可读性。


## 5. 算法可视化：像素动画演示 (核心部分)

### 🎮 动画演示主题：“名字标准化大冒险”  
**风格**：8位像素风（类似FC红白机游戏），用鲜艳的颜色（如红色=“k”，蓝色=“h”，绿色=“u”，黄色=替换后的字符）展示字符串转换过程。  
**核心演示内容**：展示“khun”→“hun”→“hoon”的转换过程。  


### 🕹️ 动画帧步骤与交互关键点  
1. **场景初始化**：  
   - 屏幕左侧显示原始字符串“khun”（每个字符是一个像素块，“k”红，“h”蓝，“u”绿，“n”白）。  
   - 右侧显示“控制面板”：“开始”“单步”“重置”按钮，速度滑块（1x~5x）。  
   - 背景播放8位风格的轻松BGM（如《超级马里奥》的背景音乐）。  

2. **处理“h”前面的“k”**：  
   - 镜头聚焦在“h”（蓝色像素块），然后向左移动，标记前面的“k”（红色像素块）。  
   - 点击“单步”按钮，红色“k”变成灰色（表示要删除），伴随“叮”的音效。  
   - 再次点击“单步”，灰色“k”消失，“h”向左移动到原来的位置（“khun”→“hun”）。  

3. **处理“u”→“oo”**：  
   - 镜头聚焦在“u”（绿色像素块），点击“单步”按钮，绿色“u”变成两个黄色“o”（“hun”→“hoon”），伴随“叮”的音效。  

4. **完成标准化**：  
   - 屏幕显示“标准化完成！”的文字，伴随“胜利”音效（如《魂斗罗》的通关音乐），黄色“o”闪烁。  
   - 可以点击“重置”按钮，重新演示其他字符串（如“kkkhoon”→“hoon”）。  


### 📝 旁白提示（动画中的文字气泡）  
- “看！这个红色的‘k’在蓝色‘h’前面，需要删除哦～”  
- “绿色的‘u’要变成两个黄色的‘o’啦！”  
- “标准化完成！‘khun’和‘kkkhoon’都变成‘hoon’了～”  


## 6. 拓展练习与相似问题思考

### 🧠 通用思路迁移  
本题的“字符串标准化”思路可以应用到很多场景，比如：  
- 处理英文单词的复数形式（如“cat”→“cats”，“mouse”→“mice”）；  
- 处理日期格式（如“2024-05-20”→“2024/05/20”）；  
- 处理URL编码（如“%20”→“ ”）。  


### 📚 洛谷练习推荐  
1. **洛谷 P1055  ISBN号码**  
   - 🗣️ **推荐理由**：需要处理字符串中的数字和符号，将ISBN号码转换为标准形式，巩固字符串处理技巧。  
2. **洛谷 P1200 [USACO1.1] 你的飞碟在这儿**  
   - 🗣️ **推荐理由**：需要将字符串转换为数字，然后进行计算，练习字符串与数字的转换。  
3. **洛谷 P1598 垂直柱状图**  
   - 🗣️ **推荐理由**：需要统计字符串中的字符出现次数，然后输出柱状图，练习字符串统计技巧。  


## 7. 学习心得与经验分享 (若有)

### 📝 来自LKY928261的经验  
> “我在解决这个问题时，最初用了`erase`函数处理‘k’，但发现频繁`erase`会导致代码变慢。后来想到用空格标记要删除的‘k’，最后统一处理，这样效率提高了很多。”  

**点评**：这位作者的经验很实用！对于字符串的频繁修改，标记法是一个很好的优化方法，能避免`erase`函数的高开销。


## 🎉 总结  
本次分析的“Lost in Transliteration”问题，核心是**字符串标准化**。通过将歧义字符转换为唯一的标准形式，我们可以轻松统计不同的名字数量。希望这份指南能帮助大家掌握字符串处理的技巧，下次遇到类似问题时，能快速找到解决思路！  

记住：编程的乐趣在于解决问题的过程，慢慢来，你一定能学会！💪

---
处理用时：134.59秒