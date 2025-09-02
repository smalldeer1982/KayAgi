# 题目信息

# Bicolored RBS

## 题目描述

A string is called bracket sequence if it does not contain any characters other than "(" and ")". A bracket sequence is called regular (shortly, RBS) if it is possible to obtain correct arithmetic expression by inserting characters "+" and "1" into this sequence. For example, "", "(())" and "()()" are RBS and ")(" and "(()" are not.

We can see that each opening bracket in RBS is paired with some closing bracket, and, using this fact, we can define nesting depth of the RBS as maximum number of bracket pairs, such that the $ 2 $ -nd pair lies inside the $ 1 $ -st one, the $ 3 $ -rd one — inside the $ 2 $ -nd one and so on. For example, nesting depth of "" is $ 0 $ , "()()()" is $ 1 $ and "()((())())" is $ 3 $ .

Now, you are given RBS $ s $ of even length $ n $ . You should color each bracket of $ s $ into one of two colors: red or blue. Bracket sequence $ r $ , consisting only of red brackets, should be RBS, and bracket sequence, consisting only of blue brackets $ b $ , should be RBS. Any of them can be empty. You are not allowed to reorder characters in $ s $ , $ r $ or $ b $ . No brackets can be left uncolored.

Among all possible variants you should choose one that minimizes maximum of $ r $ 's and $ b $ 's nesting depth. If there are multiple solutions you can print any of them.

## 说明/提示

In the first example one of optimal solutions is $ s =  $ " $ \color{blue}{()} $ ". $ r $ is empty and $ b =  $ " $ () $ ". The answer is $ \max(0, 1) = 1 $ .

In the second example it's optimal to make $ s =  $ " $ \color{red}{(}\color{blue}{(}\color{red}{)}\color{blue}{)} $ ". $ r = b =  $ " $ () $ " and the answer is $ 1 $ .

In the third example we can make $ s =  $ " $ \color{red}{(}\color{blue}{((}\color{red}{)()}\color{blue}{)())} $ ". $ r =  $ " $ ()() $ " and $ b =  $ " $ (()()) $ " and the answer is $ 2 $ .

## 样例 #1

### 输入

```
2
()
```

### 输出

```
11
```

## 样例 #2

### 输入

```
4
(())
```

### 输出

```
0101
```

## 样例 #3

### 输入

```
10
((()())())
```

### 输出

```
0110001111```

# AI分析结果

### 题目内容重写

#### 题目描述

一个字符串被称为括号序列，如果它只包含字符 `(` 和 `)`。一个括号序列被称为正则括号序列（简称 RBS），如果可以通过在该序列中插入字符 `+` 和 `1` 来获得正确的算术表达式。例如，`""`、`"(())"` 和 `"()()"` 是 RBS，而 `")("` 和 `"(()"` 不是。

我们可以看到，RBS 中的每个左括号都与某个右括号配对，利用这一事实，我们可以定义 RBS 的嵌套深度为最大括号对数，使得第 2 对括号在第 1 对括号内，第 3 对括号在第 2 对括号内，依此类推。例如，`""` 的嵌套深度为 `0`，`"()()()"` 的嵌套深度为 `1`，`"()((())())"` 的嵌套深度为 `3`。

现在，给定一个长度为 `n` 的 RBS `s`，你需要将 `s` 中的每个括号涂成红色或蓝色。由红色括号组成的序列 `r` 必须是 RBS，由蓝色括号组成的序列 `b` 也必须是 RBS。它们中的任何一个都可以为空。你不允许重新排列 `s`、`r` 或 `b` 中的字符。所有括号都必须被涂色。

在所有可能的方案中，你应该选择一个使 `r` 和 `b` 的嵌套深度的最大值最小的方案。如果有多个解，你可以输出任意一个。

#### 说明/提示

在第一个示例中，一个最优解是 `s = "()"`，`r` 为空，`b = "()"`。答案是 `max(0, 1) = 1`。

在第二个示例中，最优解是 `s = "(())"`，`r = b = "()"`，答案是 `1`。

在第三个示例中，我们可以使 `s = "((()())())"`，`r = "()()"`，`b = "(()())"`，答案是 `2`。

#### 样例 #1

##### 输入

```
2
()
```

##### 输出

```
11
```

#### 样例 #2

##### 输入

```
4
(())
```

##### 输出

```
0101
```

#### 样例 #3

##### 输入

```
10
((()())())
```

##### 输出

```
0110001111
```

### 算法分类

贪心

### 题解分析与结论

这道题的核心思想是通过贪心策略来平衡两个颜色的括号序列的嵌套深度。所有题解都采用了类似的思路：对于左括号，优先将其分配给当前嵌套深度较小的颜色；对于右括号，优先将其分配给当前嵌套深度较大的颜色。这样可以有效平衡两个颜色的嵌套深度，使得它们的最大值最小化。

### 精选题解

#### 题解作者：lukelin (赞：4)

**星级：★★★★★**

**关键亮点：**
- 思路清晰，代码简洁。
- 直接通过两个变量 `rd` 和 `bl` 来维护两个颜色的嵌套深度，实现简单高效。

**代码核心思想：**
- 遍历括号序列，对于左括号，选择当前嵌套深度较小的颜色；对于右括号，选择当前嵌套深度较大的颜色。

```cpp
int rd = 0;
int bl = 0;
int ans[200005];

int main(){
    int n = read();
    string s; cin >> s;
    for (int i = 0; i < n; ++i){
        if (s[i] == ')')
            (rd > bl) ? (--rd, ans[i] = 0) : (--bl, ans[i] = 1);
        else if (s[i] == '(')
            (rd < bl) ? (++rd, ans[i] = 0) : (++bl, ans[i] = 1);
    }
    for (int i = 0; i < n; ++i)
        printf("%d", ans[i]);
    return 0;
}
```

#### 题解作者：saixingzhe (赞：3)

**星级：★★★★**

**关键亮点：**
- 分析深入，解释了贪心策略的正确性。
- 虽然没有提供代码，但思路清晰，有助于理解问题。

**核心思想：**
- 对于左括号，优先分配给当前嵌套深度较小的颜色；对于右括号，优先分配给当前嵌套深度较大的颜色。

#### 题解作者：TPJX (赞：0)

**星级：★★★★**

**关键亮点：**
- 代码简洁，直接输出结果，无需额外存储。
- 通过实时输出结果，减少了内存使用。

**代码核心思想：**
- 遍历括号序列，对于左括号，选择当前嵌套深度较小的颜色；对于右括号，选择当前嵌套深度较大的颜色。

```cpp
int n, r, b;
int main() {
    string s;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            if (r <= b) {
                cout << "0";
                ++r;
            } else {
                cout << "1";
                ++b;
            }
        } else {
            if (r >= b) {
                cout << "0";
                --r;
            } else {
                cout << "1";
                --b;
            }
        }
    }
    cout << endl;
    return 0;
}
```

### 最优关键思路或技巧

- **贪心策略**：通过优先将左括号分配给当前嵌套深度较小的颜色，右括号分配给当前嵌套深度较大的颜色，可以有效平衡两个颜色的嵌套深度。
- **实时维护**：通过两个变量实时维护两个颜色的嵌套深度，避免使用复杂的数据结构，提高代码效率。

### 可拓展之处

- 类似的问题可以扩展到多颜色的括号序列，或者扩展到其他需要平衡多个序列深度的场景。

### 推荐题目

1. [P1044 括号匹配](https://www.luogu.com.cn/problem/P1044)
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
3. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)

---
处理用时：37.38秒