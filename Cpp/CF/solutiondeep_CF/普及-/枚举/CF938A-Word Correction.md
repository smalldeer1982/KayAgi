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

### 题目中文重写
# 单词修正

## 题目背景
给定一个长度为 n 的字符串，当有两个元音字母相邻时，删除后一个元音字母，输出修改后的字符串。（注：a、e、i、o、u、y 为元音字母）

## 题目描述
维克多试图编写自己的文本编辑器，其中包含单词修正功能。然而，单词修正的规则非常奇怪。

维克多认为，如果一个单词包含两个连续的元音字母，那么这个单词有点奇怪，需要进行替换。因此，单词修正器的工作方式如下：只要单词中有两个连续的元音字母，就删除单词中第一个后面紧跟着另一个元音字母的元音字母。如果单词中没有两个连续的元音字母，则认为该单词是正确的。

给定一个单词 s，你能预测它在修正后会变成什么样子吗？

在这个问题中，字母 a、e、i、o、u 和 y 被视为元音字母。

## 说明/提示
示例解释：
1. 只有一次替换：weird → werd；
2. 由于没有两个连续的元音字母，不需要进行替换；
3. aaeaa → aeaa → aaa → aa → a。

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

### 综合分析与结论
这些题解的核心目标都是解决字符串中相邻元音字母的删除问题，思路大致可分为标记删除、直接遍历输出、使用栈结构和转换为 01 序列处理等几类。
- **思路对比**：
    - 标记删除类（如 yizimi 远欣的题解）通过标记需要删除的元音字母，最后输出未标记的字符。
    - 直接遍历输出类（如 Eason_AC、monstersqwq 做法 1、Zirnc 等题解）在遍历过程中根据当前字符和前一个或后一个字符的情况决定是否输出。
    - 使用栈结构（如 monstersqwq 做法 2）利用栈的特性，根据栈顶元素和当前字符的情况决定是否入栈和输出。
    - 转换为 01 序列处理（如 judgejudge 的题解）将字符串转换为 01 序列，方便判断相邻元音。
- **算法要点**：
    - 标记删除类需要额外的数组来记录标记信息。
    - 直接遍历输出类需要在遍历过程中进行条件判断，决定是否输出当前字符。
    - 使用栈结构需要注意栈的操作，如入栈、出栈和判断栈是否为空。
    - 转换为 01 序列处理需要先将字符串转换为 01 序列，再进行判断。
- **解决难点**：
    - 处理连续多个元音字母的情况，确保只保留第一个元音字母。
    - 避免越界访问，如在判断下一个字符时需要注意字符串的边界。

### 所选题解
- **yizimi 远欣（5 星）**
    - **关键亮点**：思路清晰，通过标记数组记录需要删除的字符，代码结构清晰，易于理解。
    - **核心代码**：
```c
#include<bits/stdc++.h>
using namespace std;
#define go(i,j,n,k) for(int i=j;i<=n;i+=k)
#define fo(i,j,n,k) for(int i=j;i>=n;i-=k)
#define mn 105
char a[mn];
int n;
bool b[mn];//记录是否被删除
int main(){
    cin>>n;
    go(i,1,n,1){
        cin>>a[i];
        b[i]=true;
    }
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
    go(i,1,n,1){
        if(b[i]){
            cout<<a[i];
        }
    }
    return 0;
}
```
核心实现思想：先将所有字符标记为保留，然后遍历字符串，当遇到元音字母时，检查其后连续的元音字母并标记为删除，最后输出未标记删除的字符。
- **Eason_AC（4 星）**
    - **关键亮点**：代码简洁，通过一个变量记录前一个字符是否为元音，在遍历过程中直接输出符合条件的字符。
    - **核心代码**：
```cpp
string s;
int vowel = 0, n;

int main() {
    getint(n);
    cin >> s;
    _for(i, 0, n - 1) {
        if((s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y') && vowel) continue;
        printf("%c", s[i]);
        vowel = (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y');
    }
    return 0;
}
```
核心实现思想：遍历字符串，若当前字符是元音且前一个字符也是元音，则跳过当前字符；否则输出当前字符，并更新记录前一个字符是否为元音的变量。
- **monstersqwq 做法 1（4 星）**
    - **关键亮点**：思路简单直接，通过定义判断元音的函数，在遍历字符串时根据当前字符和前一个字符的情况决定是否输出。
    - **核心代码**：
```cpp
bool check(char a)
{
    if(a=='a'||a=='e'||a=='i'||a=='o'||a=='u'||a=='y') return true;
    else return false;
}
int main()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            cout<<s[i];
            continue;
        }
        if(check(s[i])&&check(s[i-1])) ;
        else cout<<s[i];
    }
    return 0;
}
```
核心实现思想：定义一个判断字符是否为元音的函数，遍历字符串，对于第一个字符直接输出，对于后续字符，若当前字符和前一个字符都是元音，则不输出；否则输出当前字符。

### 最优关键思路或技巧
- **标记法**：使用标记数组记录需要删除的字符，避免直接在原字符串上进行删除操作，简化逻辑。
- **单变量记录**：使用一个变量记录前一个字符是否为元音，在遍历过程中直接判断是否输出当前字符，减少额外空间开销。
- **函数封装**：将判断元音的逻辑封装成函数，提高代码的可读性和可维护性。

### 可拓展之处
同类型题目可能会有不同的删除规则，如删除前一个元音、删除连续元音中的特定位置元音等，解题思路仍然是遍历字符串并根据规则进行判断和处理。类似算法套路还可应用于字符串的其他处理问题，如删除重复字符、替换特定字符等。

### 推荐洛谷题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串的处理和校验。
2. [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)：需要对字符串进行字符转换和计算。
3. [P1597 语句解析](https://www.luogu.com.cn/problem/P1597)：考查字符串的解析和变量赋值。

### 个人心得摘录与总结
- **珅肐**：提到“y 是半元音也算！我第一遍就错了”，总结为在处理字符串问题时，要仔细阅读题目条件，注意特殊情况，避免因遗漏条件而导致错误。
- **judgejudge**：指出原代码“无法判断两个及以上相邻元音”，并进行了改进，总结为在编写代码时，要充分考虑各种可能的情况，对代码进行全面测试，发现问题及时改进。 

---
处理用时：44.64秒