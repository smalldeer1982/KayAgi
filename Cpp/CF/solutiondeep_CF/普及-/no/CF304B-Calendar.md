# 题目信息

# Calendar

## 题目描述

Calendars in widespread use today include the Gregorian calendar, which is the de facto international standard, and is used almost everywhere in the world for civil purposes. The Gregorian reform modified the Julian calendar's scheme of leap years as follows:

 Every year that is exactly divisible by four is a leap year, except for years that are exactly divisible by 100; the centurial years that are exactly divisible by 400 are still leap years. For example, the year 1900 is not a leap year; the year 2000 is a leap year.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF304B/f8498332105130efe5e68ba02dfcaba5e2afd72f.png)In this problem, you have been given two dates and your task is to calculate how many days are between them. Note, that leap years have unusual number of days in February.

Look at the sample to understand what borders are included in the aswer.

## 样例 #1

### 输入

```
1900:01:01
2038:12:31
```

### 输出

```
50768
```

## 样例 #2

### 输入

```
1996:03:09
1991:11:12
```

### 输出

```
1579
```

# AI分析结果

### 题目内容
# 日历

## 题目描述
当今广泛使用的日历包括格里高利历，它事实上是国际标准，并且几乎在世界上所有地方用于民用目的。格里高利改革对儒略历的闰年规则修改如下：

能被4整除的年份为闰年，但能被100整除的年份除外；能被400整除的世纪年仍然是闰年。例如，1900年不是闰年；2000年是闰年。

在本题中，给定两个日期，你的任务是计算它们之间相隔多少天。注意，闰年的2月天数不同寻常。

通过样例来理解答案中包含哪些边界情况。

## 样例 #1
### 输入
```
1900:01:01
2038:12:31
```
### 输出
```
50768
```

## 样例 #2
### 输入
```
1996:03:09
1991:11:12
```
### 输出
```
1579
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要分为数学计算和模拟两种思路。数学计算思路通过特定公式直接计算日期距离某一固定日期（如0年或1900年）的天数，再相减取绝对值得到结果，计算速度快且代码简洁。模拟思路则是按日期变化规则，逐天模拟从一个日期到另一个日期的过程，统计天数，逻辑直观但代码较繁琐，时间复杂度相对较高。解决难点在于准确处理闰年规则及日期边界条件。

### 所选的题解
 - **作者：无意识躺枪人 (5星)**
    - **关键亮点**：使用数学方法，通过一个函数快速计算某日期距0的天数，代码简洁高效。
    - **重点代码**：
```c
long long Calculation(int y,int m,int d)
{
    if (m<3) {y-=1;m+=12;}
    return 365*y+y/4-y/100+y/400+(153*m-457)/5+d-306;
}

int main()
{
    int y,m,d;
    scanf("%d:%d:%d",&y,&m,&d); long long a=Calculation(y,m,d);
    scanf("%d:%d:%d",&y,&m,&d); long long b=Calculation(y,m,d);
    printf("%lld\n",abs(b-a));
    return 0;
}
```
核心实现思想：`Calculation`函数根据给定日期计算距0的天数，先调整月份，再依据闰年规则和每月天数计算总天数，主函数读入两个日期计算差值。
 - **作者：xtr169 (4星)**
    - **关键亮点**：同样采用数学计算方法，思路清晰，代码结构明确。
    - **重点代码**：
```cpp
int dimd(int yyy,int mmm,int ddd)
{
    int ans;
    if (mmm<3)
    {
        mmm+=12;
        yyy--; 
    }
    ans=365*yyy+yyy/4-yyy/100+yyy/400+(153*mmm-457)/5+ddd-306;
    return ans;
}

int main()
{
    scanf("%d:%d:%d",&y,&m,&d); 
    t1=dimd(y,m,d);
    scanf("%d:%d:%d",&yy,&mm,&dd); 
    t2=dimd(yy,mm,dd);
    cout<<(t1>t2?t1-t2:t2-t1);
    return 0;
}
```
核心实现思想：`dimd`函数与上一题解类似，计算给定日期距某固定点天数，主函数读入两个日期并输出天数差。
 - **作者：ygsldr (4星)**
    - **关键亮点**：提供了Python利用`datetime`包的简洁解法及数学计算思路，对公式来源有说明。
    - **重点代码（数学计算部分）**：
```python
def get(y, m, d):
    if(m < 3):
        y -= 1
        m += 12
    return 365 * y + y // 4 - y //100 + y//400 + (153*m-457)//5+d-306
```
核心实现思想：`get`函数通过调整月份，结合闰年规则和每月天数计算距某固定点天数。

### 最优关键思路或技巧
数学计算思路中通过特定公式计算日期距固定日期天数的方法最优，能显著减少计算量，提高效率，且代码简洁易读。

### 拓展
同类型题常考察日期计算、闰年判断等知识点，类似算法套路是找到一个固定参考点，通过公式计算各日期距参考点天数，再做差值。

### 推荐题目
 - [P1424 小鱼的航程(改进版)](https://www.luogu.com.cn/problem/P1424)：涉及日期计算和条件判断。
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：结合数学计算与逻辑判断。
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：需处理时间相关条件和计算。 

---
处理用时：47.49秒