# 题目信息

# Keyboard Layouts

## 题目描述

There are two popular keyboard layouts in Berland, they differ only in letters positions. All the other keys are the same. In Berland they use alphabet with $ 26 $ letters which coincides with English alphabet.

You are given two strings consisting of $ 26 $ distinct letters each: all keys of the first and the second layouts in the same order.

You are also given some text consisting of small and capital English letters and digits. It is known that it was typed in the first layout, but the writer intended to type it in the second layout. Print the text if the same keys were pressed in the second layout.

Since all keys but letters are the same in both layouts, the capitalization of the letters should remain the same, as well as all other characters.

## 样例 #1

### 输入

```
qwertyuiopasdfghjklzxcvbnm
veamhjsgqocnrbfxdtwkylupzi
TwccpQZAvb2017
```

### 输出

```
HelloVKCup2017
```

## 样例 #2

### 输入

```
mnbvcxzlkjhgfdsapoiuytrewq
asdfghjklqwertyuiopzxcvbnm
7abaCABAABAcaba7
```

### 输出

```
7uduGUDUUDUgudu7
```

# AI分析结果

### 题目内容（中文重写）
# 键盘布局

## 题目描述
在 Berland 有两种流行的键盘布局，它们仅在字母位置上有所不同，其他所有按键都相同。在 Berland 使用的字母表有 26 个字母，与英文字母表相同。

给你两个字符串，每个字符串由 26 个不同的字母组成，分别表示第一种和第二种键盘布局的所有按键，顺序相同。

还给你一些由小写和大写英文字母以及数字组成的文本。已知该文本是在第一种键盘布局下输入的，但输入者原本打算在第二种键盘布局下输入。请输出在第二种键盘布局下按相同按键所得到的文本。

由于两种键盘布局中除字母外的所有按键都相同，所以字母的大小写以及其他所有字符都应保持不变。

## 样例 #1
### 输入
```
qwertyuiopasdfghjklzxcvbnm
veamhjsgqocnrbfxdtwkylupzi
TwccpQZAvb2017
```
### 输出
```
HelloVKCup2017
```

## 样例 #2
### 输入
```
mnbvcxzlkjhgfdsapoiuytrewq
asdfghjklqwertyuiopzxcvbnm
7abaCABAABAcaba7
```
### 输出
```
7uduGUDUUDUgudu7
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先记录两种键盘布局中字母的映射关系，再遍历输入的文本，根据映射关系将文本中的字母转换为第二种键盘布局对应的字母，非字母字符保持不变。

各题解的算法要点和解决难点对比如下：
- **使用 `map` 存储映射关系**：如 Eason_AC 和 Erusel 的题解，利用 `map` 强大的映射功能，方便地存储和查找字母的映射关系，代码简洁。但 `map` 可能存在一定的性能开销。
- **使用数组存储映射关系**：如 Arghariza、MC 小萌新、peppaking8、codemap 和 Rainbow_qwq 的题解，通过字符的 ASCII 码作为数组下标来存储映射关系，性能较高。需要处理好大小写字母的映射和数组下标的计算。
- **直接遍历查找映射**：如 TLMPEX 和 Nortrom 的题解，在遇到字母时直接遍历查找其映射，实现简单，但时间复杂度较高。

### 所选题解
- **Eason_AC（5 星）**
    - **关键亮点**：思路清晰，使用 `map` 存储映射关系，代码简洁易读，能很好地处理大小写字母的映射。
    - **重点代码**：
```cpp
string a, b, c;
map<char, char> mm;

int main() {
    cin >> a >> b;
    int len = a.size();
    for(int i = 0; i < len; ++i) mm[a[i]] = b[i], mm[a[i] - 32] = b[i] - 32;
    cin >> c;
    len = c.size();
    for(int i = 0; i < len; ++i)
        if((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z'))
            c[i] = mm[c[i]];
    cout << c;
    return 0;
}
```
核心实现思想：先读取两种键盘布局的字符串，将小写字母和对应的大写字母的映射关系存储在 `map` 中，再读取输入的文本，遍历文本，将字母按映射关系转换，最后输出转换后的文本。

### 最优关键思路或技巧
- 使用 `map` 或数组存储字母的映射关系，能高效地进行查找和转换。
- 处理大小写字母时，可以利用 ASCII 码的差值进行转换。

### 拓展思路
同类型题可能会有更复杂的映射规则，如映射关系不仅限于字母，还包括特殊字符；或者输入的文本包含多行等。类似的算法套路可以应用在密码转换、字符替换等问题中。

### 推荐洛谷题目
- P1079 Vigenère 密码
- P1308 统计单词数
- P5733 【深基6.例1】自动修正

### 个人心得摘录与总结
- Arghariza：在转换大写字母时，一开始把 `-32` 打成了 `+32`，导致错误。总结：在处理大小写转换时，要注意 ASCII 码的差值。

---
处理用时：33.14秒