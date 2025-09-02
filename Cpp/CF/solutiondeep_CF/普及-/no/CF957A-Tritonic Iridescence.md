# 题目信息

# Tritonic Iridescence

## 题目描述

Overlooking the captivating blend of myriads of vernal hues, Arkady the painter lays out a long, long canvas.

Arkady has a sufficiently large amount of paint of three colours: cyan, magenta, and yellow. On the one-dimensional canvas split into $ n $ consecutive segments, each segment needs to be painted in one of the colours.

Arkady has already painted some (possibly none or all) segments and passes the paintbrush to you. You are to determine whether there are at least two ways of colouring all the unpainted segments so that no two adjacent segments are of the same colour. Two ways are considered different if and only if a segment is painted in different colours in them.

## 说明/提示

For the first example, there are exactly two different ways of colouring: CYCMY and CYMCY.

For the second example, there are also exactly two different ways of colouring: CMCMY and CYCMY.

For the third example, there are four ways of colouring: MCYCM, MCYCY, YCYCM, and YCYCY.

For the fourth example, no matter how the unpainted segments are coloured, the existing magenta segments will prevent the painting from satisfying the requirements. The similar is true for the fifth example.

## 样例 #1

### 输入

```
5
CY??Y
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
C?C?Y
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
5
?CYC?
```

### 输出

```
Yes
```

## 样例 #4

### 输入

```
5
C??MM
```

### 输出

```
No
```

## 样例 #5

### 输入

```
3
MMY
```

### 输出

```
No
```

# AI分析结果

### 题目翻译
# 三色虹彩

## 题目描述
画家阿尔卡季俯瞰着无数春日色彩的迷人交融，铺开了一幅长长的画布。

阿尔卡季有足够多的三种颜色的颜料：青色、品红色和黄色。在被分成 $n$ 个连续线段的一维画布上，每个线段都需要涂上其中一种颜色。

阿尔卡季已经涂好了一些（可能没有或全部涂好）线段，然后把画笔递给了你。你需要确定是否至少有两种方法来给所有未涂色的线段上色，使得相邻的两个线段颜色不同。当且仅当某个线段在两种方法中涂的颜色不同时，这两种方法才被认为是不同的。

## 说明/提示
对于第一个样例，恰好有两种不同的上色方法：CYCMY 和 CYMCY。

对于第二个样例，也恰好有两种不同的上色方法：CMCMY 和 CYCMY。

对于第三个样例，有四种上色方法：MCYCM、MCYCY、YCYCM 和 YCYCY。

对于第四个样例，无论如何给未涂色的线段上色，现有的品红色线段都会使这幅画无法满足要求。第五个样例也是如此。

## 样例 #1
### 输入
```
5
CY??Y
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
5
C?C?Y
```
### 输出
```
Yes
```

## 样例 #3
### 输入
```
5
?CYC?
```
### 输出
```
Yes
```

## 样例 #4
### 输入
```
5
C??MM
```
### 输出
```
No
```

## 样例 #5
### 输入
```
3
MMY
```
### 输出
```
No
```

### 算法分类
字符串

### 综合分析与结论
- **思路**：该题解没有直接考虑“？”所代表的颜色，而是根据已知颜色与未知颜色的关系进行判断。先检查已知颜色中是否有相邻相同的情况，若有则不能完成上色；再分析未知颜色的分布情况，若存在单独一块“？”满足特定条件或者有相邻多个“？”的情况，则可以有至少两种上色方法。
- **算法要点**：遍历字符串，检查相邻已知颜色是否相同；判断“？”的分布情况，若“？”在开头、结尾、连续或者满足特定条件则标记可以完成上色。
- **解决难点**：难点在于准确判断“？”的不同分布情况对上色方法数量的影响，题解通过对不同情况的分类讨论解决了这个问题。

### 题解
- **星级**：3星
- **关键亮点**：思路清晰，通过分类讨论已知颜色和未知颜色的关系来判断是否能有至少两种上色方法，代码实现简洁。

### 重点代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
bool b=0;
char p[110];
int main()
{
    scanf("%d",&n);
    scanf("%s",p);
    for(int i=0;i<n;i++)
    {
        if(p[i]!='?')//如果这块有颜色
        {
            if(p[i+1]==p[i])//如果这块与相邻的已知颜色相同
            {
                printf("No");
                return 0;
            }
        }
        else
        if(i==0||i==n-1||p[i-1]=='?'||p[i+1]=='?'/*“？”是否连续*/||(p[i-1]!='?'&&p[i+1]!='?'&&p[i-1]==p[i+1])/*是否满足2-①*/)
        {
            b=1;
        }
    }
    if(b)
        printf("Yes");
    else
        printf("No");	
}
```
**核心实现思想**：先读取输入的字符串长度和字符串，然后遍历字符串。对于有颜色的位置，检查相邻位置颜色是否相同，若相同则输出`No`并结束程序；对于“？”位置，判断其是否满足特定条件，若满足则标记`b`为`true`。最后根据`b`的值输出`Yes`或`No`。

### 通用建议与扩展思路
在处理这类字符串相关的判断问题时，可以先分析题目中的关键条件，然后对不同情况进行分类讨论。对于类似的需要根据字符串中字符的分布和关系进行判断的题目，可以借鉴本题解的思路，通过遍历字符串并结合条件判断来解决问题。

### 推荐洛谷题目
1. P1055 [NOIP2008 普及组] ISBN 号码
2. P1957 口算练习题
3. P1125 [NOIP2008 提高组] 笨小猴

### 个人心得
题解中未包含个人心得。

---
处理用时：30.44秒