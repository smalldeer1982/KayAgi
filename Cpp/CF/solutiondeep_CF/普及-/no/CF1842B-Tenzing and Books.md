# 题目信息

# Tenzing and Books

## 题目描述

Tenzing received $ 3n $ books from his fans. The books are arranged in $ 3 $ stacks with $ n $ books in each stack. Each book has a non-negative integer difficulty rating.

Tenzing wants to read some (possibly zero) books. At first, his knowledge is $ 0 $ .

To read the books, Tenzing will choose a non-empty stack, read the book on the top of the stack, and then discard the book. If Tenzing's knowledge is currently $ u $ , then his knowledge will become $ u|v $ after reading a book with difficulty rating $ v $ . Here $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). Note that Tenzing can stop reading books whenever he wants.

Tenzing's favourite number is $ x $ . Can you help Tenzing check if it is possible for his knowledge to become $ x $ ?

## 说明/提示

For the first test case, Tenzing can read the following $ 4 $ books:

- read the book with difficulty rating $ 1 $ on the top of the first stack. Tenzing's knowledge changes to $ 0|1=1 $ .
- read the book with difficulty rating $ 1 $ on the top of the third stack. Tenzing's knowledge changes to $ 1|1=1 $ .
- read the book with difficulty rating $ 2 $ on the top of the first stack. Tenzing's knowledge changes to $ 1|2=3 $ .
- read the book with difficulty rating $ 5 $ on the top of the second stack. Tenzing's knowledge changes to $ 3|5=7 $ .

After reading all books, Tenzing's knowledge is $ 7 $ .

For the third test case, Tenzing can read $ 0 $ books to make his final knowledge equals to $ 0 $ .

## 样例 #1

### 输入

```
3
5 7
1 2 3 4 5
5 4 3 2 1
1 3 5 7 9
5 2
3 2 3 4 5
5 4 3 2 1
3 3 5 7 9
3 0
1 2 3
3 2 1
2 2 2```

### 输出

```
Yes
No
Yes```

# AI分析结果

### 题目翻译
# Tenzing 和书籍

## 题目描述
Tenzing 从粉丝那里收到了 $3n$ 本书。这些书被分成 3 堆，每堆有 $n$ 本书。每本书都有一个非负整数的难度评级。

Tenzing 想读一些（可能为零本）书。一开始，他的知识水平为 0。

为了阅读这些书，Tenzing 会选择一个非空的书堆，阅读堆顶的书，然后把这本书扔掉。如果 Tenzing 当前的知识水平是 $u$，那么在阅读一本难度评级为 $v$ 的书后，他的知识水平将变为 $u|v$。这里的 $|$ 表示[按位或运算](https://en.wikipedia.org/wiki/Bitwise_operation#OR)。注意，Tenzing 可以随时停止阅读。

Tenzing 最喜欢的数字是 $x$。你能帮 Tenzing 检查一下他的知识水平是否有可能变成 $x$ 吗？

## 说明/提示
对于第一个测试用例，Tenzing 可以阅读以下 4 本书：
- 阅读第一堆顶部难度评级为 1 的书。Tenzing 的知识水平变为 $0|1 = 1$。
- 阅读第三堆顶部难度评级为 1 的书。Tenzing 的知识水平变为 $1|1 = 1$。
- 阅读第一堆顶部难度评级为 2 的书。Tenzing 的知识水平变为 $1|2 = 3$。
- 阅读第二堆顶部难度评级为 5 的书。Tenzing 的知识水平变为 $3|5 = 7$。

读完所有书后，Tenzing 的知识水平是 7。

对于第三个测试用例，Tenzing 可以不读任何书，使他的最终知识水平等于 0。

## 样例 #1
### 输入
```
3
5 7
1 2 3 4 5
5 4 3 2 1
1 3 5 7 9
5 2
3 2 3 4 5
5 4 3 2 1
3 3 5 7 9
3 0
1 2 3
3 2 1
2 2 2
```

### 输出
```
Yes
No
Yes
```

### 算法分类
贪心、位运算

### 综合分析与结论
这些题解的核心思路都是基于按位或运算的性质进行贪心选择。按位或运算的特点是二进制中某一位一旦变为 1 就不会再变回 0，所以只要栈顶元素的二进制中为 1 的位在目标值 $x$ 对应的位上也为 1，就可以选择该元素。具体实现上，都是遍历三个栈，依次判断栈顶元素是否满足条件，若满足则进行按位或操作，直到不满足条件或栈为空，最后判断最终结果是否等于 $x$。

### 所选题解
- **作者：paramecium_ (4星)**
    - **关键亮点**：思路清晰，使用了快读优化输入，代码简洁。
    - **个人心得**：无
- **作者：sz_jinzikai (4星)**
    - **关键亮点**：对按位或运算的性质解释详细，代码注释丰富，使用三目表达式简化输出判断。
    - **个人心得**：无
- **作者：D0000 (4星)**
    - **关键亮点**：给出了易错点提示，代码结构清晰，使用 `vector` 存储数据。
    - **个人心得**：提到同学使用递归做只有 10 分，建议不要使用递归。

### 重点代码
#### paramecium_ 的代码
```cpp
while(xa<=n&&(a[xa]|x)==x) now|=a[xa++];
while(xb<=n&&(b[xb]|x)==x) now|=b[xb++];
while(xc<=n&&(c[xc]|x)==x) now|=c[xc++];
if(now==x) P("Yes\n");
else P("No\n");
```
**核心实现思想**：依次遍历三个栈，只要栈顶元素与 $x$ 按位或的结果等于 $x$，就将该元素与当前知识水平按位或，最后判断知识水平是否等于 $x$。

#### sz_jinzikai 的代码
```cpp
while (ha < n && (a[ha] | x) == x) now |= a[ha ++];
while (hb < n && (b[hb] | x) == x) now |= b[hb ++];
while (hc < n && (c[hc] | x) == x) now |= c[hc ++];
cout << (now == x ? "Yes\n" : "No\n");
```
**核心实现思想**：与 paramecium_ 的思路相同，只是变量名不同，使用三目表达式判断输出结果。

#### D0000 的代码
```cpp
for (int i = 1; i <= n; i++) {
    if ((x | a[i]) == x) ans |= a[i];
    else break;
}
for (int i = 1; i <= n; i++) {
    if ((x | b[i]) == x) ans |= b[i];
    else break;
}
for (int i = 1; i <= n; i++) {
    if ((x | c[i]) == x) ans |= c[i];
    else break;
}
std::cout << (ans == x ? "Yes\n" : "No\n");
```
**核心实现思想**：同样是遍历三个栈，满足条件就按位或，不满足则跳出循环，最后判断结果。

### 关键思路或技巧
- 利用按位或运算的性质，即二进制中某一位一旦变为 1 就不会再变回 0，进行贪心选择。
- 通过判断元素与目标值 $x$ 按位或的结果是否等于 $x$，来确定该元素是否可以选择。

### 拓展思路
同类型题可以是涉及按位运算（如按位与、按位异或等）的贪心问题，或者是在栈、队列等数据结构上进行操作的贪心问题。类似算法套路就是根据运算的性质进行贪心选择，优先选择对结果有利的元素。

### 推荐题目
- [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P2240 【深基12.例1】部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得摘录与总结
- **rainygame**：赛时因为样例太水导致错了 4 次，两个晚上白熬了。总结：不能仅仅依赖样例，要深入理解题目和算法，多考虑边界情况和特殊情况。
- **D0000**：同学使用递归做只有 10 分，建议不要使用递归。总结：在选择算法时要根据题目特点进行合理选择，递归可能不适合本题的贪心性质。 

---
处理用时：43.70秒