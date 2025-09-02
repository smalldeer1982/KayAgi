# 题目信息

# Replace To Make Regular Bracket Sequence

## 题目描述

给定一个只含 `>`，`(`，`)`，`{`，`}`，`[`，`]`的字符串。记`<`，`(`，`{`，`[`为左括号，`>`，`)`，`}`，`]`为右括号。每次可以将任意一个左括号换为任意一个不同的左括号，或将任意一个右括号换为任意一个不同的右括号，记为一次操作。求使括号序合法的最小操作次数，若无解，输出 `impossible`。

## 样例 #1

### 输入

```
[&lt;}){}
```

### 输出

```
2```

## 样例 #2

### 输入

```
{()}[]
```

### 输出

```
0```

## 样例 #3

### 输入

```
]]
```

### 输出

```
Impossible```

# AI分析结果



# Replace To Make Regular Bracket Sequence

## 题目描述

给定一个只含 `>`，`(`，`)`，`{`，`}`，`[`，`]`的字符串。记`<`，`(`，`{`，`[`为左括号，`>`，`)`，`}`，`]`为右括号。每次可以将任意一个左括号换为任意一个不同的左括号，或将任意一个右括号换为任意一个不同的右括号，记为一次操作。求使括号序合法的最小操作次数，若无解，输出 `Impossible`。

## 样例 #1

### 输入

```
[<}){}
```

### 输出

```
2```

## 样例 #2

### 输入

```
{()}[]
```

### 输出

```
0```

## 样例 #3

### 输入

```
]]
```

### 输出

```
Impossible```

**分类标签**：栈、字符串

---

### 题解分析与结论

所有题解均采用**栈**结构处理括号匹配问题，核心思路为：遍历字符串时用栈维护未匹配的左括号，遇到右括号时与栈顶左括号进行匹配判断。若不匹配则操作次数+1，若无法匹配或最终栈非空则返回Impossible。

---

### 高分题解推荐

#### 题解作者：Zachary_Cloud（⭐⭐⭐⭐⭐）
**核心思路**：  
- 使用栈保存左括号，遇到右括号时检查栈顶是否为左括号  
- 类型不匹配时操作次数+1，栈非空则输出Impossible  
**代码亮点**：  
- 封装`is_left`和`match`函数提升可读性  
- 逻辑清晰，处理栈空情况及时终止  

```cpp
stack<char> a;
int ans;
// 判断是否为左括号的函数
inline bool is_left(char c) { /*...*/ }
// 判断括号是否匹配的函数
inline bool match(char a,char b) { /*...*/ }

signed main() {
    for (char c : s) {
        if (is_left(c)) a.push(c);
        else {
            if (a.empty() || !is_left(a.top())) return Impossible;
            ans += !match(a.top(), c);
            a.pop();
        }
    }
    if (!a.empty()) return Impossible;
    cout << ans;
}
```

---

#### 题解作者：IOI_AK_LHY（⭐⭐⭐⭐）
**核心思路**：  
- 栈处理左括号，右括号尝试匹配栈顶左括号  
**优化点**：  
- 使用函数名`flag1`、`flag2`增强语义  
- 直接处理字符不进行类型转换  

```cpp
stack<char> stk;
int ans;
// 判断左括号
bool flag1(char a) { /*...*/ }
// 判断匹配
bool flag2(char a,char b) { /*...*/ }

main() {
    for (char c : s) {
        if (stk.empty() || flag1(c)) stk.push(c);
        else {
            char top = stk.top();
            if (flag1(top)) {
                ans += !flag2(top, c);
                stk.pop();
            } else stk.push(c);
        }
    }
    if (!stk.empty()) return Impossible;
    cout << ans;
}
```

---

### 关键技巧总结
1. **栈结构维护未匹配括号**：确保括号序列的嵌套结构合法  
2. **类型不匹配即计数**：利用左/右括号类型可替换特性，统计必要操作次数  
3. **最终栈空校验**：保证所有左括号均被匹配  

---

### 类似题目推荐
1. [P1944 最长括号匹配](https://www.luogu.com.cn/problem/P1944)  
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)  
3. [CF3D Least Cost Bracket Sequence](https://codeforces.com/problemset/problem/3/D)  

---

### 个人心得摘录
- **栈顶类型检查**：当栈顶为右括号时无法匹配后续左括号，需及时终止  
- **结构完整性优先**：类型替换无法修复结构错误（如多余右括号）  
- **测试样例构造**：考虑纯右括号、交替不匹配等极端情况验证逻辑

---
处理用时：160.90秒