# 题目信息

# STL

## 题目描述

Vasya used to be an accountant before the war began and he is one of the few who knows how to operate a computer, so he was assigned as the programmer.

We all know that programs often store sets of integers. For example, if we have a problem about a weighted directed graph, its edge can be represented by three integers: the number of the starting vertex, the number of the final vertex and the edge's weight. So, as Vasya was trying to represent characteristics of a recently invented robot in his program, he faced the following problem.

Vasya is not a programmer, so he asked his friend Gena, what the convenient way to store $ n $ integers is. Gena used to code in language X-- and so he can use only the types that occur in this language. Let's define, what a "type" is in language X--:

- First, a type is a string "int".
- Second, a type is a string that starts with "pair", then followed by angle brackets listing exactly two comma-separated other types of language X--. This record contains no spaces.
- No other strings can be regarded as types.

More formally: type := int | pair<type,type>. For example, Gena uses the following type for graph edges: pair<int,pair<int,int>>.

Gena was pleased to help Vasya, he dictated to Vasya a type of language X--, that stores $ n $ integers. Unfortunately, Gena was in a hurry, so he omitted the punctuation. Now Gena has already left and Vasya can't find the correct punctuation, resulting in a type of language X--, however hard he tries.

Help Vasya and add the punctuation marks so as to receive the valid type of language X--. Otherwise say that the task is impossible to perform.

## 样例 #1

### 输入

```
3
pair pair int int int
```

### 输出

```
pair<pair<int,int>,int>```

## 样例 #2

### 输入

```
1
pair int
```

### 输出

```
Error occurred```

# AI分析结果



---

**算法分类**：递归解析

---

### **题解思路与算法要点**

1. **核心思路**  
   题目要求将输入的单词序列转换为合法的嵌套类型字符串。每个`pair`必须包含两个子类型，递归处理结构，确保每个`pair`后有两个合法类型。错误情况包括输入不足或多余。

2. **解决难点**  
   - **递归结构**：每次遇到`pair`需递归生成两个子类型，否则无法正确嵌套。
   - **错误检测**：全局标记输入是否提前结束，递归后检查剩余输入。
   - **字符串拼接**：使用全局字符串逐步构建结果，避免中途失败无法回退。

3. **关键步骤与变量**  
   - **递归函数**：每次处理一个单词，`pair`则拼接`<`并递归两次，`int`直接拼接。
   - **错误标记**：如递归中无法读取单词，或处理后仍有剩余输入，标记错误。

---

### **题解评分与亮点**

1. **Anguei（★★★★★）**  
   - **亮点**：代码简洁，注释清晰，递归逻辑直接，正确处理输入结束和多于输入。
   - **核心代码**：
     ```cpp
     void input() {
         if (std::cin >> s) {
             if (s == "pair") {
                 ans += "pair<";
                 input(); // 递归处理第一个子类型
                 ans += ",";
                 input(); // 递归处理第二个子类型
                 ans += ">";
             } else ans += "int";
         } else ok = false; // 输入不足
     }
     ```

2. **Jiyuu_no_Tsubasa（★★★★☆）**  
   - **亮点**：函数命名清晰，主流程简洁，处理错误后直接输出。
   - **心得**：强调递归结束后必须检查多余输入。

3. **myee（★★★★☆）**  
   - **亮点**：栈模拟递归，两遍扫描验证合法性，适合非递归实现。
   - **代码片段**：
     ```cpp
     // 栈中保存 pair 的处理状态（false: 未处理第一个子类型）
     std::stack<bol> S;
     for (uint i = 0; i < n; i++) {
         if (Ok[i]) { // 当前是 int
             if (S.empty()) error();
             while (!S.empty() && S.top()) S.pop(); // 处理已完成的 pair
             S.top() = true; // 标记第一个子类型处理完毕
         } else { // 当前是 pair
             S.push(false); // 新增未处理的 pair
         }
     }
     ```

---

### **最优思路提炼**

- **递归解析**：每个`pair`对应两次递归调用，天然匹配嵌套结构。
- **错误处理**：全局标记输入状态，递归中途失败或输入残留均报错。
- **字符串构建**：边递归边拼接符号，避免复杂回溯。

---

### **相似题目推荐**

1. **括号生成（洛谷 P22）**：递归生成合法括号序列，类似结构嵌套。
2. **表达式解析（洛谷 P227）**：处理运算符优先级，需递归/栈解析。
3. **XML解析（洛谷 P399）**：验证标签嵌套合法性，类似树形结构。

---

### **可视化设计**

**算法演示方案**：  
1. **递归树动画**：  
   - 以树形结构展示递归过程，每次展开`pair`时生成两个子节点。
   - **颜色标记**：当前处理的节点高亮（如红色），已完成的节点变灰。
   - **步进控制**：用户可单步执行递归，观察当前拼接的字符串。

2. **栈模拟演示**：  
   - 显示栈中状态，用不同颜色区分未处理的`pair`（黄色）和已处理第一个子类型的`pair`（绿色）。
   - 输入序列逐步压入栈，遇到`int`时触发出栈操作。

**复古像素风格**：  
- **Canvas 绘制**：用16色像素块表示递归层级，每个`pair`显示为嵌套方框。
- **音效设计**：  
  - 递归进入时播放“点击”音效，完成时播放“确认”音效。
  - 错误时播放短促“错误”音效，背景8位循环音乐。

---

### **核心代码示例**

```cpp
// 递归解法核心代码（Anguei）
#include <iostream>
#include <string>
using namespace std;

bool ok = true;
string ans;

void parse() {
    string s;
    if (cin >> s) {
        if (s == "pair") {
            ans += "pair<";
            parse(); // 左子树
            ans += ",";
            parse(); // 右子树
            ans += ">";
        } else {
            ans += "int";
        }
    } else {
        ok = false; // 输入不足
    }
}

int main() {
    int n; cin >> n;
    parse();
    string tmp;
    if (!ok || cin >> tmp) cout << "Error occurred";
    else cout << ans;
    return 0;
}
```

---
处理用时：95.29秒