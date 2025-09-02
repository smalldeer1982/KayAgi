# 题目信息

# Delete Them

## 题目描述

Polycarp is a beginner programmer. He is studying how to use a command line.

Polycarp faced the following problem. There are $ n $ files in a directory and he needs to delete some of them. Polycarp wants to run a single delete command with filename pattern as an argument. All the files to be deleted should match the pattern and all other files shouldn't match the pattern.

Polycarp doesn't know about an asterisk '\*', the only special character he knows is a question mark '?' which matches any single character. All other characters in the pattern match themselves only.

Formally, a pattern matches a filename if and only if they have equal lengths and all characters in the corresponding positions are equal except when the character in the pattern is '?', in which case the corresponding filename character does not matter.

For example, the filename pattern "a?ba?":

- matches filenames "aabaa", "abba.", "a.ba9" and "a.ba.";
- does not match filenames "aaba", "abaab", "aabaaa" and "aabaa.".

Help Polycarp find a pattern which matches files to be deleted and only them or report if there is no such pattern.

## 样例 #1

### 输入

```
3 2
ab
ac
cd
1 2
```

### 输出

```
Yes
a?
```

## 样例 #2

### 输入

```
5 3
test
tezt
test.
.est
tes.
1 4 5
```

### 输出

```
Yes
?es?
```

## 样例 #3

### 输入

```
4 4
a
b
c
dd
1 2 3 4
```

### 输出

```
No
```

## 样例 #4

### 输入

```
6 3
.svn
.git
....
...
..
.
1 2 3
```

### 输出

```
Yes
.???
```

# AI分析结果



### 题目内容中文翻译

# 删除文件

## 题目描述

Polycarp 是一个刚学编程的新手。他正在学习如何使用命令行。

Polycarp 遇到了这样一个问题：目录中有 $n$ 个文件，他需要删除其中的一部分。Polycarp 想用单个删除命令，并附带一个文件名模式作为参数。所有需要删除的文件必须匹配该模式，而其他文件必须不匹配该模式。

Polycarp 不知道星号'\*'的用法，他唯一知道的通配符是问号'?'，可以匹配任意单个字符。模式中的其他字符仅与自身匹配。

形式化地说，当且仅当模式与文件名长度相等，且对应位置字符相同（模式中为'?'的位置可以匹配任意字符）时，文件名才匹配该模式。

例如，文件名模式 "a?ba?"：
- 匹配 "aabaa", "abba.", "a.ba9" 等文件名
- 不匹配 "aaba", "abaab" 等文件名

请帮助 Polycarp 找到满足条件的模式，或报告不存在这样的模式。

### 样例 #1

输入：
```
3 2
ab
ac
cd
1 2
```

输出：
```
Yes
a?
```

### 样例 #2

输入：
```
5 3
test
tezt
test.
.est
tes.
1 4 5
```

输出：
```
Yes
?es?
```

### 样例 #3

输入：
```
4 4
a
b
c
dd
1 2 3 4
```

输出：
```
No
```

### 样例 #4

输入：
```
6 3
.svn
.git
....
...
..
.
1 2 3
```

输出：
```
Yes
.???
```

---

### 算法分类
字符串

---

### 题解综合分析

各题解核心思路一致，分为两步：
1. **构造模式**：将所有待删文件对应的字符串逐位比对，不同字符的位置设为'?'，长度不一致时直接判否
2. **验证模式**：检查所有未被删除的文件是否被该模式意外匹配

#### 关键难点
- **长度一致性检查**：所有待删文件必须长度相同，否则无法构造有效模式
- **通配符替换逻辑**：对每个字符位置，若存在不同字符则必须替换为'?'
- **严格匹配验证**：确保未被删除的文件中不存在完全匹配模式的项

---

### 优质题解推荐

#### 1. [作者：Jerry_heng](https://www.luogu.com.cn) ★★★★☆
**核心亮点**：
- 代码结构清晰，分步处理长度检查和模式构造
- 使用标志变量快速终止非法情况
- 验证阶段直接逐字符比对，逻辑简洁

**核心代码**：
```cpp
int main(){
    // 长度检查
    if(st[x].length() != l) {
        cout<<"No";
        return 0;
    }
    // 模式构造
    for(int j=0;j<l;j++)
        if(ans[j]!=st[x][j]) ans[j]='?';
    // 验证
    for(int j=0;j<l;j++)
        if(st[i][j]!=ans[j]&&ans[j]!='?') break;
}
```

#### 2. [作者：Awa486](https://www.luogu.com.cn) ★★★★☆
**核心亮点**：
- 独立处理长度验证模块，逻辑更独立
- 使用双重循环提前终止无效匹配检查
- 包含调试经验（判重语句的添加）

**关键代码段**：
```cpp
// 长度检查模块
for(int j=1; j<m; j++)
    if(strlen(s[a[j]]) != len) flag = 1;
// 验证模块
for(int j=0; j<k; j++)
    if(s[i][j]!=ans[j]&&ans[j]!='?') break;
```

---

### 最优思路总结
1. **统一长度检查**：优先验证所有待删文件长度一致
2. **逐位通配符生成**：通过比对每个位置字符差异动态生成'?'
3. **逆向验证机制**：通过反证法验证非目标文件是否被意外匹配

---

### 类似题目推荐
1. [CF7D - Palindrome Degree](https://www.luogu.com.cn/problem/CF7D)  
   **标签**：字符串哈希、回文处理
2. [P1308 - 统计单词数](https://www.luogu.com.cn/problem/P1308)  
   **标签**：模式匹配、字符串遍历
3. [P1739 - 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)  
   **标签**：模式验证、栈结构应用

---
处理用时：127.49秒