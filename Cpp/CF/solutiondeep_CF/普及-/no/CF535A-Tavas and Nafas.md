# 题目信息

# Tavas and Nafas

## 题目描述

Today Tavas got his test result as an integer score and he wants to share it with his girlfriend, Nafas.

His phone operating system is Tavdroid, and its keyboard doesn't have any digits! He wants to share his score with Nafas via text, so he has no choice but to send this number using words.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535A/b4f47a55f97fcd02924cac5270349f0616c61519.png)He ate coffee mix without water again, so right now he's really messed up and can't think.

Your task is to help him by telling him what to type.

## 说明/提示

You can find all you need to know about English numerals in [http://en.wikipedia.org/wiki/English\_numerals](http://en.wikipedia.org/wiki/English_numerals) .

## 样例 #1

### 输入

```
6
```

### 输出

```
six
```

## 样例 #2

### 输入

```
99
```

### 输出

```
ninety-nine
```

## 样例 #3

### 输入

```
20
```

### 输出

```
twenty
```

# AI分析结果

【中文重写题目】
# Tavas 和 Nafas

## 题目描述
今天 Tavas 得到了他的测试成绩，是一个整数，他想和他的女朋友 Nafas 分享这个成绩。

他的手机操作系统是 Tavdroid，其键盘上没有任何数字！他想通过短信和 Nafas 分享他的成绩，所以他别无选择，只能用单词来发送这个数字。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF535A/b4f47a55f97fcd02924cac5270349f0616c61519.png)
他又没加水就吃了咖啡混合物，所以现在他真的一团糟，无法思考。

你的任务是帮助他，告诉他应该输入什么。

## 说明/提示
你可以在 [http://en.wikipedia.org/wiki/English_numerals](http://en.wikipedia.org/wiki/English_numerals) 找到所有关于英语数字的信息。

## 样例 #1
### 输入
```
6
```
### 输出
```
six
```

## 样例 #2
### 输入
```
99
```
### 输出
```
ninety-nine
```

## 样例 #3
### 输入
```
20
```
### 输出
```
twenty
```

【算法分类】
模拟

【综合分析与结论】
这些题解的核心思路都是将数字转换为对应的英文表述。主要的方法有两种，一是直接打表，存储 0 - 99 所有数字对应的英文；二是分别存储 0 - 9、10 - 19、整十数的英文，再根据输入数字的范围进行判断和组合输出。
- **思路对比**：打表法简单直接，但代码量较大；分类存储法需要进行条件判断，但代码结构更清晰，扩展性更好。
- **算法要点**：都需要准确处理 0、11 - 19 以及整十数这些特殊情况。
- **解决难点**：主要难点在于对不同范围数字的分类处理，以及在输出时正确处理连字符。

【题解评分】
- 李至擎：4星。思路清晰，代码简洁，直接打表解决问题，容易理解。
- Eason_AC：3星。思路正确，通过分类判断输出结果，但代码中数组的使用和逻辑判断稍显复杂。
- cq_loves_Capoo：3星。提供了两种方法，思路明确，但打表法代码未给出，且代码中存在拼写错误。
- 开始新的记忆：3星。思路正确，代码简单，但数组中存在拼写错误。
- a1ioua：3星。思路清晰，代码简洁，但注释中存在拼写错误。
- Arghariza：3星。思路正确，考虑了特殊情况，但代码中使用 `qwq` 占位不太规范。
- 九月_014：3星。通过字符串长度判断，逻辑稍显繁琐，代码可读性一般。
- ZolaWatle：3星。思路正确，考虑了特殊情况，但数组定义较大，存在多余空间。

【所选题解】
- 李至擎（4星）
  - 关键亮点：直接打表，代码简洁，容易理解。
  - 个人心得：注意数据中出现了 0，需要特殊处理。

【重点代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
int num;
char a[105][25]={"zero","one","two","three","four","five","six","seven","eight","nine",
"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen",
"nineteen","twenty","twenty-one","twenty-two","twenty-three","twenty-four","twenty-five",
"twenty-six","twenty-seven","twenty-eight","twenty-nine","thirty","thirty-one","thirty-two",
"thirty-three","thirty-four","thirty-five","thirty-six","thirty-seven","thirty-eight",
"thirty-nine","forty","forty-one","forty-two","forty-three","forty-four","forty-five",
"forty-six","forty-seven","forty-eight","forty-nine","fifty","fifty-one","fifty-two",
"fifty-three","fifty-four","fifty-five","fifty-six","fifty-seven","fifty-eight",
"fifty-nine","sixty","sixty-one","sixty-two","sixty-three","sixty-four","sixty-five",
"sixty-six","sixty-seven","sixty-eight","sixty-nine","seventy","seventy-one","seventy-two",
"seventy-three","seventy-four","seventy-five","seventy-six","seventy-seven","seventy-eight",
"seventy-nine","eighty","eighty-one","eighty-two","eighty-three","eighty-four",
"eighty-five","eighty-six","eighty-seven","eighty-eight","eighty-nine","ninety",
"ninety-one","ninety-two","ninety-three","ninety-four","ninety-five","ninety-six",
"ninety-seven","ninety-eight","ninety-nine"};//一个0~99的表
int main()
{
    cin>>num;
    cout<<a[num];//输出结果 
    return 0;
}
```
【核心实现思想】
预先定义一个二维字符数组 `a`，存储 0 - 99 所有数字对应的英文表述。在输入一个数字 `num` 后，直接输出 `a[num]` 即可得到对应的英文表述。

【关键思路或技巧】
- 打表法：对于数据范围较小的问题，可以直接打表存储所有可能的结果，避免复杂的逻辑判断。
- 分类处理：对于不同范围的数字，采用不同的处理方式，如 0、11 - 19、整十数等特殊情况需要单独处理。

【拓展思路】
同类型题目可以是将更大范围的数字转换为英文表述，或者将英文数字转换为阿拉伯数字。类似算法套路是对数据进行分类处理，根据不同的条件进行判断和输出。

【推荐题目】
1. [P1617 爱与愁的一千个伤心的理由](https://www.luogu.com.cn/problem/P1617)
2. [P2084 进制转换](https://www.luogu.com.cn/problem/P2084)
3. [P1143 进制转换](https://www.luogu.com.cn/problem/P1143)

【个人心得摘录总结】
- Arghariza：题面说的是 1 - 99，但数据中出现了 0，导致第一次提交 WA，提醒我们要注意数据范围的边界情况。
- ZolaWatle：第一次提交没考虑 n == 0 的情况挂了，强调了特殊情况处理的重要性。

---
处理用时：37.99秒