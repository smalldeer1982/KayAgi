# 题目信息

# The Same Calendar

## 题目描述

The girl Taylor has a beautiful calendar for the year $ y $ . In the calendar all days are given with their days of week: Monday, Tuesday, Wednesday, Thursday, Friday, Saturday and Sunday.

The calendar is so beautiful that she wants to know what is the next year after $ y $ when the calendar will be exactly the same. Help Taylor to find that year.

Note that leap years has $ 366 $ days. The year is leap if it is divisible by $ 400 $ or it is divisible by $ 4 $ , but not by $ 100 $ ([https://en.wikipedia.org/wiki/Leap\_year](https://en.wikipedia.org/wiki/Leap_year)).

## 说明/提示

Today is Monday, the $ 13 $ th of June, $ 2016 $ .

## 样例 #1

### 输入

```
2016
```

### 输出

```
2044
```

## 样例 #2

### 输入

```
2000
```

### 输出

```
2028
```

## 样例 #3

### 输入

```
50501
```

### 输出

```
50507
```

# AI分析结果



# The Same Calendar

## 题目描述

女孩泰勒有一个年份为 $ y $ 的美丽日历。日历中所有日期都标有星期几：周一、周二、周三、周四、周五、周六和周日。

这个日历如此精美，以至于她想知道下一个与 $ y $ 年日历完全相同的年份。帮助泰勒找到这个年份。

注意闰年有 $ 366 $ 天。闰年的判断条件是：能被 $ 400 $ 整除，或能被 $ 4 $ 整除但不能被 $ 100 $ 整除。

## 说明/提示

今天是 2016 年 6 月 13 日，星期一。

## 样例 #1

### 输入

```
2016
```

### 输出

```
2044
```

## 样例 #2

### 输入

```
2000
```

### 输出

```
2028
```

## 样例 #3

### 输入

```
50501
```

### 输出

```
50507
```

**算法分类**：模拟、数学

---

### 题解综合分析

核心思路是找到满足两个条件的年份：闰年状态相同，且累计天数差为 7 的倍数。各题解均采用枚举法，核心差异在于对天数累计的处理方式。

#### 关键思路总结
1. **正确累计天数**：必须累计从原年份到目标年份前一年的总天数模 7 的值，而非当前年份的天数。
2. **闰年状态匹配**：目标年份与原年份同为闰年或同为平年。
3. **模运算优化**：通过模 7 运算避免大数计算，提升效率。

---

### 精选题解

#### 1. 智子·起源（4星）
**关键亮点**：
- 维护累计天数差 `h`，每次累加前一年的天数。
- 代码逻辑清晰，通过 `getday` 函数显式计算天数。
- **核心代码**：
```cpp
int getday(int q) {
    if((q%4==0&&q%100!=0)||q%400==0) return 366;
    return 355; // 错误：此处应为返回365
}
// 修正后的正确实现：
int getday(int q) {
    return (q%4==0&&q%100!=0)||q%400==0 ? 366 : 365;
}
```
**个人心得**：作者最初错误地将平年天数写成 355，后修正为 365，强调了边界测试的重要性。

#### 2. yf最qhhh（5星）
**关键亮点**：
- 极简代码风格，通过三目运算符内联闰年判断。
- 使用 `sum` 累计前一年的天数，直接模 7 判断。
- **核心代码**：
```cpp
#include<cstdio>
#define rll register long long
ll rrr(ll x) {
    return (x%400==0)||(x%4==0&&x%100!=0);
}
int main() {
    ll n,sum=0; scanf("%lld",&n);
    for(ll i=n+1;;i++) {
        sum += rrr(i-1) ? 366 : 365;
        if(rrr(i)==rrr(n) && sum%7==0) {
            printf("%lld",i); return 0;
        }
    }
}
```
**优势**：代码简洁高效，无冗余操作，直接体现核心逻辑。

---

### 相似题目推荐
1. [P2141 回文日期](https://www.luogu.com.cn/problem/P2141) - 日期处理与闰年判断
2. [P1202 黑色星期五](https://www.luogu.com.cn/problem/P1202) - 计算特定日期的星期分布
3. [P1303 日期计算](https://www.luogu.com.cn/problem/P1303) - 天数到日期的转换

---
处理用时：212.42秒