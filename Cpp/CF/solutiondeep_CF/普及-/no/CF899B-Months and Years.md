# 题目信息

# Months and Years

## 题目描述

Everybody in Russia uses Gregorian calendar. In this calendar there are $ 31 $ days in January, $ 28 $ or $ 29 $ days in February (depending on whether the year is leap or not), $ 31 $ days in March, $ 30 $ days in April, $ 31 $ days in May, $ 30 $ in June, $ 31 $ in July, $ 31 $ in August, $ 30 $ in September, $ 31 $ in October, $ 30 $ in November, $ 31 $ in December.

A year is leap in one of two cases: either its number is divisible by $ 4 $ , but not divisible by $ 100 $ , or is divisible by $ 400 $ . For example, the following years are leap: $ 2000 $ , $ 2004 $ , but years $ 1900 $ and $ 2018 $ are not leap.

In this problem you are given $ n $ ( $ 1<=n<=24 $ ) integers $ a_{1},a_{2},...,a_{n} $ , and you have to check if these integers could be durations in days of $ n $ consecutive months, according to Gregorian calendar. Note that these months could belong to several consecutive years. In other words, check if there is a month in some year, such that its duration is $ a_{1} $ days, duration of the next month is $ a_{2} $ days, and so on.

## 说明/提示

In the first example the integers can denote months July, August, September and October.

In the second example the answer is no, because there are no two consecutive months each having $ 30 $ days.

In the third example the months are: February (leap year) — March — April – May — June.

In the fourth example the number of days in the second month is $ 28 $ , so this is February. March follows February and has $ 31 $ days, but not $ 30 $ , so the answer is NO.

In the fifth example the months are: December — January — February (non-leap year).

## 样例 #1

### 输入

```
4
31 31 30 31
```

### 输出

```
Yes

```

## 样例 #2

### 输入

```
2
30 30
```

### 输出

```
No

```

## 样例 #3

### 输入

```
5
29 31 30 31 30
```

### 输出

```
Yes

```

## 样例 #4

### 输入

```
3
31 28 30
```

### 输出

```
No

```

## 样例 #5

### 输入

```
3
31 31 28
```

### 输出

```
Yes

```

# AI分析结果

### 题目中文重写
# 月份和年份

## 题目描述
在俄罗斯，所有人都使用公历。在公历中，1月有31天，2月有28天或29天（取决于该年是否为闰年），3月有31天，4月有30天，5月有31天，6月有30天，7月有31天，8月有31天，9月有30天，10月有31天，11月有30天，12月有31天。

闰年的判断依据有两个：一是年份能被4整除，但不能被100整除；二是年份能被400整除。例如，2000年和2004年是闰年，而1900年和2018年不是闰年。

在本题中，给定 $n$（$1\leq n\leq24$）个整数 $a_{1},a_{2},\cdots,a_{n}$，你需要判断这些整数是否可以表示公历中连续 $n$ 个月的天数。注意，这些月份可能属于连续的几年。换句话说，检查是否存在某一年的某个月，其天数为 $a_{1}$ 天，下一个月的天数为 $a_{2}$ 天，依此类推。

## 说明/提示
在第一个样例中，这些整数可以表示7月、8月、9月和10月。

在第二个样例中，答案为否，因为不存在两个连续的月份都有30天。

在第三个样例中，这些月份是：2月（闰年）—3月—4月—5月—6月。

在第四个样例中，第二个月的天数是28天，所以这是2月。2月之后是3月，3月有31天，而不是30天，所以答案为否。

在第五个样例中，这些月份是：12月—1月—2月（平年）。

## 样例 #1
### 输入
```
4
31 31 30 31
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
2
30 30
```
### 输出
```
No
```

## 样例 #3
### 输入
```
5
29 31 30 31 30
```
### 输出
```
Yes
```

## 样例 #4
### 输入
```
3
31 28 30
```
### 输出
```
No
```

## 样例 #5
### 输入
```
3
31 31 28
```
### 输出
```
Yes
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是打表，将连续几年（包含平年和闰年）每个月的天数信息存储下来，再将输入的月份天数信息与之比对，判断输入是否是表中的一个子串。
- **思路**：先打表记录连续多个月的天数，再将输入的月份天数拼成字符串，使用 `find()` 函数判断是否在表中。
- **算法要点**：打表时要包含平年和闰年的情况，输入处理成字符串后用 `find()` 查找。
- **解决难点**：处理闰年的情况，以及输入输出的格式问题（如空格、回车）。

### 所选题解
- **清小秋ovo（4星）**
  - **关键亮点**：思路清晰，代码简洁，直接使用 `getline()` 读取输入，避免了复杂的处理。
  - **个人心得**：认为与其写复杂的判断和模拟，打表所需的代码量少之又少。

### 重点代码
```cpp
#include<bits/stdc++.h>

using namespace std;
string b;
int main()
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   int num;
   cin>>num;
   cin.ignore();
   getline(cin,b);
   string month="31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 29 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 31 28 31 30 31 30 31 31 30 31 30 31 ";
    if(month.find(b)!=string::npos){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
}
```
**核心实现思想**：先读取输入的月份数，忽略多余的回车，再用 `getline()` 读取一整行输入作为字符串。将预先打好的月份天数表存储在 `month` 字符串中，使用 `find()` 函数判断输入的字符串是否是 `month` 的子串，根据结果输出 `Yes` 或 `No`。

### 可拓展之处
同类型题目可能会改变数据范围、增加更多的条件判断等。类似算法套路可用于处理其他需要判断子串是否存在的问题，如判断一段字符序列是否是某个长字符序列的一部分等。

### 推荐题目
1. [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)
2. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
3. [P5734 【深基6.例6】文字处理软件](https://www.luogu.com.cn/problem/P5734)

---
处理用时：35.74秒