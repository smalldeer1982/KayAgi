# 题目信息

# Email from Polycarp

## 题目描述

Methodius received an email from his friend Polycarp. However, Polycarp's keyboard is broken, so pressing a key on it once may cause the corresponding symbol to appear more than once (if you press a key on a regular keyboard, it prints exactly one symbol).

For example, as a result of typing the word "hello", the following words could be printed: "hello", "hhhhello", "hheeeellllooo", but the following could not be printed: "hell", "helo", "hhllllooo".

Note, that when you press a key, the corresponding symbol must appear (possibly, more than once). The keyboard is broken in a random manner, it means that pressing the same key you can get the different number of letters in the result.

For each word in the letter, Methodius has guessed what word Polycarp actually wanted to write, but he is not sure about it, so he asks you to help him.

You are given a list of pairs of words. For each pair, determine if the second word could be printed by typing the first one on Polycarp's keyboard.

## 样例 #1

### 输入

```
4
hello
hello
hello
helloo
hello
hlllloo
hello
helo
```

### 输出

```
YES
YES
NO
NO
```

## 样例 #2

### 输入

```
5
aa
bb
codeforces
codeforce
polycarp
poolycarpp
aaaa
aaaab
abcdefghijklmnopqrstuvwxyz
zabcdefghijklmnopqrstuvwxyz
```

### 输出

```
NO
NO
YES
NO
NO
```

# AI分析结果

### 题目内容
# Polycarp的邮件

## 题目描述
Methodius收到了来自他朋友Polycarp的一封邮件。然而，Polycarp的键盘坏了，所以按下一个键一次可能会导致相应的符号出现不止一次（如果在正常键盘上按下一个键，它只会打印出一个符号）。

例如，输入单词“hello”，可能打印出以下单词：“hello”、“hhhhello”、“hheeeellllooo”，但以下单词不可能打印出来：“hell”、“helo”、“hhllllooo”。

请注意，当你按下一个键时，相应的符号必须出现（可能出现多次）。键盘的损坏是随机的，这意味着按下相同的键，你可能会在结果中得到不同数量的字母。

对于邮件中的每个单词，Methodius都猜测了Polycarp实际想要输入的单词，但他不确定，所以他请你帮忙。

你会得到一组单词对。对于每一对单词，判断第二个单词是否可以通过在Polycarp的键盘上输入第一个单词而打印出来。

## 样例 #1
### 输入
```
4
hello
hello
hello
helloo
hello
hlllloo
hello
helo
```
### 输出
```
YES
YES
NO
NO
```

## 样例 #2
### 输入
```
5
aa
bb
codeforces
codeforce
polycarp
poolycarpp
aaaa
aaaab
abcdefghijklmnopqrstuvwxyz
zabcdefghijklmnopqrstuvwxyz
```
### 输出
```
NO
NO
YES
NO
NO
```

### 算法分类
字符串

### 综合分析与结论
这些题解主要围绕判断第二个字符串能否由第一个字符串在损坏键盘规则下生成展开。思路上可分为两类，一类是双指针法，直接通过双指针遍历两个字符串进行判断；另一类是先将字符串按连续相同字符进行结构转化，再对转化后的结构进行比较。各题解在细节处理和代码实现上有所不同，例如边界条件判断、指针移动逻辑等。

### 所选的题解
- **作者：Lovely_Elaina (赞：7)  星级：5星**
  - **关键亮点**：采用双指针法，思路清晰，代码简洁高效。通过简洁的双指针移动逻辑判断两个字符串是否符合要求。
  - **核心代码片段**：
```cpp
while(i <= l1 && j <= l2){
    if(s1[i]!= s2[j]){
        b = 0;
        break;
    }

    while(s1[i+1] == s1[i] && s2[j+1]!= s1[i])
        i++;

    i++,j++;
}
```
  - **核心实现思想**：用`i`遍历第一个字符串`s1`，`j`遍历第二个字符串`s2`。若当前字符不相等则直接判定不匹配；若相等，再判断`s1`下一个字符是否与当前字符相同且`s2`下一个字符与当前字符不同，若是则`i`自增，最后`i`和`j`同时自增。
- **作者：追梦之鲸 (赞：5)  星级：4星**
  - **关键亮点**：将字符串转化为结构体数组，便于比较，有效处理了连续相同字符的情况，逻辑清晰。
  - **核心代码片段**：
```c
while(c<'a'||c>'z')c=getchar();
a[1].x=c;
a[1].y=1;
for(;c<='z'&&c>='a';c=getchar()){
    if(a[top].x==c){
        a[top].y++;
    }else{
        a[++top].x=c;
        a[top].y=1;
    }
}
```
  - **核心实现思想**：将输入的字符串按连续相同字符转化为结构体数组，结构体包含字符和其连续出现次数。转化后对比两个结构体数组的长度、对应字符及出现次数是否符合要求。
- **作者：C20210404杜铖昊 (赞：2)  星级：4星**
  - **关键亮点**：先通过一些简单条件快速判定“NO”，减少不必要计算，再用双指针遍历判断。
  - **核心代码片段**：
```cpp
if(s.length() > s1.length() or s[0]!= s1[0] or s[s.length()-1]!= s1[s1.length()-1]) flag = 0;
for(i = 0;i < s.length();++i){
    if(s[i] == s[i+1]  and s[i] == s1[j]){
        j++;
        continue;
    }
    if(s[i]!= s1[j]){
        flag = 0;
        break;
    }
    else {
        while(s[i] == s1[j]) j++;
    }
}
```
  - **核心实现思想**：先判断猜测字符串长度、首尾字符是否符合条件，不符合则直接判定“NO”。然后用双指针遍历，若当前字符相同且下一个字符也相同则`j`自增；若当前字符不同则判定“NO”；若相同则移动`j`直到字符不同。

### 最优关键思路或技巧
双指针法在解决此类字符串匹配问题时较为简洁高效，通过合理移动指针，能快速判断两个字符串是否符合特定规则。同时，提前判断一些明显不满足条件的情况（如字符串长度、首尾字符等）可以减少不必要的计算。

### 可拓展之处
同类型题目通常围绕字符串的特定生成规则或匹配规则展开，类似算法套路为利用双指针、字符串预处理等方式解决字符串匹配问题。例如判断一个字符串是否是另一个字符串在某种特殊编辑规则下的结果。

### 洛谷推荐题目
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P1914 小书童——密码](https://www.luogu.com.cn/problem/P1914)
- [P2219 无聊的数列](https://www.luogu.com.cn/problem/P2219)

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：51.53秒