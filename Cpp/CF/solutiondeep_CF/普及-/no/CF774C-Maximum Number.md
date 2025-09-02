# 题目信息

# Maximum Number

## 题目描述

Stepan has the newest electronic device with a display. Different digits can be shown on it. Each digit is shown on a seven-section indicator like it is shown on the picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF774C/7e680319981615bc8164e9951beec5e830c7cca7.png)So, for example, to show the digit $ 3 $ on the display, $ 5 $ sections must be highlighted; and for the digit $ 6 $ , $ 6 $ sections must be highlighted.

The battery of the newest device allows to highlight at most $ n $ sections on the display.

Stepan wants to know the maximum possible integer number which can be shown on the display of his newest device. Your task is to determine this number. Note that this number must not contain leading zeros. Assume that the size of the display is enough to show any integer.

## 样例 #1

### 输入

```
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
7
```

# AI分析结果

### 题目内容翻译
# 最大数字

## 题目描述
斯捷潘有一个带有显示屏的最新电子设备。显示屏上可以显示不同的数字。每个数字都显示在一个七段数码管上，如下图所示。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF774C/7e680319981615bc8164e9951beec5e830c7cca7.png)
例如，要在显示屏上显示数字 $3$，必须点亮 $5$ 个线段；而要显示数字 $6$，则必须点亮 $6$ 个线段。

这个最新设备的电池最多允许在显示屏上点亮 $n$ 个线段。

斯捷潘想知道在他的最新设备显示屏上能显示的最大可能整数是多少。你的任务是确定这个数字。注意，这个数字不能有前导零。假设显示屏的尺寸足够大，可以显示任何整数。

## 样例 #1
### 输入
```
2
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3
```
### 输出
```
7
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心算法，因为要得到最大的数，位数越多越好，而 1 所需的线段数最少（2 个），所以优先考虑用 1 来组成数字。当总线段数为奇数时，先拿出 3 个线段组成 7 放在首位，因为 7 比 1 大且能利用多余的一个线段，剩下的再用 1 填充。

### 题解列表
- **cbyybccbyybc（4星）**
    - **关键亮点**：思路清晰，代码简洁易懂，通过简单的条件判断和循环实现了贪心策略。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[12]={6,2,5,5,4,5,6,3,7,6};
int main()
{
    int n;
    cin>>n;
    if(n%2!=0)
    {
        cout<<"7";
        n-=3;
    }
    while(n>0)
    {
        cout<<"1";
        n-=2;
    } 
    return 0;
}
```
    - **核心实现思想**：先判断总线段数 $n$ 是否为奇数，若为奇数则先输出 7 并减去 3 个线段，然后不断输出 1 并减去 2 个线段，直到线段用完。

- **RainFestival（3星）**
    - **关键亮点**：用 Pascal 语言实现，对问题的分析比较详细，解释了奇数情况的处理方法。
    - **核心代码**：
```pascal
var n,i:longint;
begin
readln(n);
if n mod 2=1 then
begin 
write(7); 
n:=n-3;
end;
for i:=1 to n div 2 do
write(1);
writeln;
end.
```
    - **核心实现思想**：若总线段数 $n$ 为奇数，先输出 7 并减去 3 个线段，然后循环输出 $n/2$ 个 1。

- **CZQ_King（3星）**
    - **关键亮点**：提到了 `string(num, char)` 这种输出重复字符的方法，代码非常简洁。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;main(int n){cin>>n;if(n&1)n-=3,cout<<7;cout<<string(n/2,49);}
```
    - **核心实现思想**：用位运算判断 $n$ 是否为奇数，若为奇数先输出 7 并减去 3 个线段，然后用 `string` 函数输出 $n/2$ 个 1。

### 最优关键思路或技巧
- 贪心策略：优先使用所需线段数最少的数字 1 来组成更多的位数，当线段数为奇数时，将 7 放在首位。
- 代码实现技巧：可以使用 `string(num, char)` 函数快速输出重复字符。

### 可拓展之处
同类型题目可能会改变数字显示的规则，或者增加一些限制条件，如规定某些数字不能使用等，但核心思路仍然是基于贪心算法，优先选择性价比高的数字来组成最大的数。

### 推荐洛谷题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P1080 [NOIP2012 提高组] 国王游戏

### 个人心得摘录与总结
- **RainFestival**：提到 Pascal 语言读入输出太慢，在实际竞赛中可能会影响效率，提醒我们在选择编程语言时要考虑其性能。 

---
处理用时：32.53秒