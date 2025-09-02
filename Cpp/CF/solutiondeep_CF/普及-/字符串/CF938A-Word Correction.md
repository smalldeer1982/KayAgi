# 题目信息

# Word Correction

## 题目背景

给一个长为n的字符串，当有两个元音字母相邻时，删除后一个元音，输出修改后的字符串。（注：a,e,i,o,u,y为元音字母）

## 题目描述

Victor tries to write his own text editor, with word correction included. However, the rules of word correction are really strange.

Victor thinks that if a word contains two consecutive vowels, then it's kinda weird and it needs to be replaced. So the word corrector works in such a way: as long as there are two consecutive vowels in the word, it deletes the first vowel in a word such that there is another vowel right before it. If there are no two consecutive vowels in the word, it is considered to be correct.

You are given a word $ s $ . Can you predict what will it become after correction?

In this problem letters a, e, i, o, u and y are considered to be vowels.

## 说明/提示

Explanations of the examples:

1. There is only one replace: weird ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) werd;
2. No replace needed since there are no two consecutive vowels;
3. aaeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aeaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aaa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png)aa ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF938A/5a518872d8942914aef6c33d251688a64a8d6d74.png) a.

## 样例 #1

### 输入

```
5
weird
```

### 输出

```
werd
```

## 样例 #2

### 输入

```
4
word
```

### 输出

```
word
```

## 样例 #3

### 输入

```
5
aaeaa
```

### 输出

```
a
```

# AI分析结果

### 题目内容重写

#### 题目背景

给定一个长度为n的字符串，当有两个元音字母相邻时，删除后一个元音字母，输出修改后的字符串。（注：a,e,i,o,u,y为元音字母）

#### 题目描述

Victor尝试编写自己的文本编辑器，其中包含单词校正功能。然而，单词校正的规则非常奇怪。

Victor认为，如果一个单词包含两个连续的元音字母，那么它有点奇怪，需要被替换。因此，单词校正器的工作方式如下：只要单词中有两个连续的元音字母，它就删除单词中第一个元音字母，使得它前面有一个元音字母。如果单词中没有两个连续的元音字母，则认为该单词是正确的。

给定一个单词$s$，你能预测它在校正后会变成什么吗？

在这个问题中，字母a, e, i, o, u和y被视为元音字母。

#### 说明/提示

样例解释：

1. 只有一个替换：weird → werd；
2. 不需要替换，因为没有两个连续的元音字母；
3. aaeaa → aeaa → aaa → aa → a。

#### 样例 #1

##### 输入

```
5
weird
```

##### 输出

```
werd
```

#### 样例 #2

##### 输入

```
4
word
```

##### 输出

```
word
```

#### 样例 #3

##### 输入

```
5
aaeaa
```

##### 输出

```
a
```

### 题解分析与结论

#### 综合分析

本题的核心任务是处理字符串中的连续元音字母，删除后一个元音字母。各题解的思路大致相同，主要通过遍历字符串，判断当前字符和前一个字符是否都是元音字母，如果是则删除后一个元音字母。不同题解在实现细节上有所差异，如使用标记数组、栈、迭代器等。

#### 最优关键思路

1. **遍历字符串**：通过遍历字符串，逐个检查字符是否为元音字母，并判断是否与前一个字符形成连续元音。
2. **标记删除**：使用标记数组或直接跳过需要删除的字符，避免修改原字符串。
3. **栈结构**：使用栈来存储字符，遇到连续元音时不压栈，从而实现删除操作。
4. **优化判断**：通过定义辅助函数或使用布尔变量简化元音字母的判断逻辑。

#### 推荐题解

1. **作者：yizimi远欣 (3星)**
   - **亮点**：使用标记数组记录删除的字符，逻辑清晰，代码可读性较好。
   - **核心代码**：
     ```cpp
     go(i,1,n,1){
         if(b[i]){
             if(a[i]=='a'||a[i]=='e'||a[i]=='o'||a[i]=='i'||a[i]=='u'||a[i]=='y'){
                 go(j,i+1,n,1){
                     if(a[j]=='a'||a[j]=='e'||a[j]=='o'||a[j]=='i'||a[j]=='u'||a[j]=='y'){
                         b[j]=false;
                     }else{
                         break;
                     }
                 }
             }
         }
     }
     ```

2. **作者：monstersqwq (4星)**
   - **亮点**：提供了两种解法，第一种直接遍历判断，第二种使用栈结构，思路多样，代码简洁。
   - **核心代码**：
     ```cpp
     for(int i=0;i<n;i++){
         if(i==0){
             cout<<s[i];
             continue;
         }
         if(check(s[i])&&check(s[i-1])) ;
         else cout<<s[i];
     }
     ```

3. **作者：Zirnc (4星)**
   - **亮点**：使用辅助函数简化元音判断，代码简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     for (int i = 0; i < n; i++){
         cout << s[i];
         if (isaeiouy(s[i]) && isaeiouy(s[i+1]))
             while (isaeiouy(s[i+1]) && i < n-1)
                 i++;
     }
     ```

#### 通用建议与扩展思路

- **数据结构选择**：根据具体需求选择合适的数据结构，如栈、队列等，可以简化问题。
- **优化判断逻辑**：通过定义辅助函数或使用布尔变量，可以减少重复代码，提高代码可读性。
- **边界条件处理**：注意处理字符串的边界条件，如第一个字符和最后一个字符的特殊情况。

#### 推荐题目

1. **P1308 统计单词数**：考察字符串处理和遍历。
2. **P1012 拼数**：涉及字符串排序和拼接。
3. **P1055 ISBN号码**：字符串处理和验证。

#### 个人心得摘录

- **调试经历**：在处理连续元音时，注意边界条件的处理，避免数组越界。
- **踩坑教训**：使用栈结构时，注意栈空的情况，避免访问空栈。
- **顿悟感想**：通过定义辅助函数，可以大大简化代码逻辑，提高代码可读性。

---
处理用时：31.84秒