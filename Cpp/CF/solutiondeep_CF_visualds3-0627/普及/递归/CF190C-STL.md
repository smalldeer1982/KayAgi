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



### 唯一算法分类
**递归**

---

### 综合分析与结论
题目要求将无序的 `pair` 和 `int` 字符串添加符号转化为合法的嵌套结构。核心难点在于正确匹配嵌套层级并处理错误情况（输入不足或冗余）。各题解均围绕递归展开，核心逻辑如下：

1. **递归构建**：遇到 `pair` 需递归处理两个子类型，并添加 `<`, `,`, `>`。
2. **错误检测**：通过全局变量记录输入是否提前结束，并在递归结束后检查是否有冗余输入。
3. **字符串拼接**：用字符串缓存结果，避免中途输出错误答案。

**可视化设计要点**：
- **递归树动画**：以树形结构展示嵌套关系，当前处理的节点高亮为黄色，完成部分渐变为绿色。
- **错误提示**：输入不足时，当前递归节点闪烁红色并播放短促音效。
- **像素风格**：用 8-bit 字体渲染字符串构建过程，每一步添加符号时伴随“滴答”音效。

---

### 题解清单（≥4星）
1. **Anguei（4.5星）**  
   - **亮点**：代码简洁，全局 `ok` 变量清晰标记错误，通过 `std::cin` 状态判断输入完整性。
   - **个人心得**：通过 `getline` 处理多余输入，避免残留字符干扰。

2. **Jiyuu_no_Tsubasa（4星）**  
   - **亮点**：递归函数返回布尔值直接控制错误流，逻辑紧凑。
   - **关键代码**：`if (cin >> ans) // 检查多余输入` 直接复用输入流。

3. **yimuhua（4星）**  
   - **亮点**：使用 `getline` 吞掉无用首行输入，避免 `n` 值干扰。
   - **代码精简**：仅用 20 行完成核心逻辑，可读性极佳。

---

### 核心代码实现
以 **Anguei** 的递归实现为例：
```cpp
bool ok = true;
std::string s, ans;

void input() {
    if (std::cin >> s) {
        if (s == "pair") {
            ans += "pair<";
            input();     // 处理左子树
            ans += ",";
            input();     // 处理右子树
            ans += ">";
        } else {
            ans += "int"; // 叶子节点
        }
    } else {
        ok = false;      // 输入不足
    }
}

int main() {
    input();
    if (!ok || std::cin >> s) { // 检查错误或冗余
        std::cout << "Error occurred";
    } else {
        std::cout << ans;
    }
}
```

---

### 相似题目推荐
1. **P1175 表达式的转换**（递归解析中缀表达式）
2. **P1044 栈**（栈与递归的等效性）
3. **P1300 括号匹配**（嵌套结构合法性检验）

---

### 复古游戏化动画设计
- **像素渲染**：用 Canvas 绘制 16x16 像素块表示每个 `pair` 和 `int`，嵌套层级以横向缩进展示。
- **音效设计**：
  - `pair`：低音鼓点。
  - `int`：高音电子音。
  - 错误：8-bit 故障音效。
- **自动演示**：按空格键逐步执行递归，按 `A` 键自动播放，速度可调。
- **状态面板**：右侧显示当前构建的字符串和剩余输入队列。

![递归树动画示例](https://i.imgur.com/8W7rGIs.gif)  
（图示：黄色为当前处理节点，绿色为已完成部分，红色表示错误位置）

--- 

**总结**：递归是解决嵌套结构问题的自然选择，通过全局状态和输入流控制错误，代码简洁高效。可视化设计可增强对递归过程的理解，复古风格增添趣味性。

---
处理用时：81.69秒