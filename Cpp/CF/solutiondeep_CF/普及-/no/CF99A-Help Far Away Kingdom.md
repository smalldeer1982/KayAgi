# 题目信息

# Help Far Away Kingdom

## 题目描述

In a far away kingdom lived the King, the Prince, the Shoemaker, the Dressmaker and many other citizens. They lived happily until great trouble came into the Kingdom. The ACMers settled there.

Most damage those strange creatures inflicted upon the kingdom was that they loved high precision numbers. As a result, the Kingdom healers had already had three appointments with the merchants who were asked to sell, say, exactly $ 0.273549107 $ beer barrels. To deal with the problem somehow, the King issued an order obliging rounding up all numbers to the closest integer to simplify calculations. Specifically, the order went like this:

- If a number's integer part does not end with digit $ 9 $ and its fractional part is strictly less than $ 0.5 $ , then the rounded up number coincides with the number’s integer part.
- If a number's integer part does not end with digit $ 9 $ and its fractional part is not less than $ 0.5 $ , the rounded up number is obtained if we add $ 1 $ to the last digit of the number’s integer part.
- If the number’s integer part ends with digit $ 9 $ , to round up the numbers one should go to Vasilisa the Wise. In the whole Kingdom she is the only one who can perform the tricky operation of carrying into the next position.

Merchants found the algorithm very sophisticated and they asked you (the ACMers) to help them. Can you write a program that would perform the rounding according to the King’s order?

## 样例 #1

### 输入

```
0.0
```

### 输出

```
0```

## 样例 #2

### 输入

```
1.49
```

### 输出

```
1```

## 样例 #3

### 输入

```
1.50
```

### 输出

```
2```

## 样例 #4

### 输入

```
2.71828182845904523536
```

### 输出

```
3```

## 样例 #5

### 输入

```
3.14159265358979323846
```

### 输出

```
3```

## 样例 #6

### 输入

```
12345678901234567890.1
```

### 输出

```
12345678901234567890```

## 样例 #7

### 输入

```
123456789123456789.999
```

### 输出

```
GOTO Vasilisa.```

# AI分析结果

### 题目内容（中文重写）
# 帮助遥远的王国

## 题目描述
在一个遥远的王国里，住着国王、王子、鞋匠、裁缝和许多其他公民。他们幸福地生活着，直到巨大的麻烦降临到这个王国。ACMers（可能指算法竞赛参与者）来到了这里。

这些奇怪的生物给王国带来的最大麻烦是，他们喜欢高精度的数字。结果，王国的药剂师已经和那些被要求出售，比如说，正好 $0.273549107$ 桶啤酒的商人进行了三次会面。为了以某种方式解决这个问题，国王颁布了一项命令，要求将所有数字四舍五入到最接近的整数，以简化计算。具体来说，命令如下：
- 如果一个数字的整数部分不以数字 $9$ 结尾，并且它的小数部分严格小于 $0.5$，那么四舍五入后的数字与该数字的整数部分相同。
- 如果一个数字的整数部分不以数字 $9$ 结尾，并且它的小数部分不小于 $0.5$，那么四舍五入后的数字是在该数字整数部分的最后一位上加 $1$ 得到的。
- 如果一个数字的整数部分以数字 $9$ 结尾，要对这些数字进行四舍五入，就应该去找瓦西丽莎智者（Vasilisa the Wise）。在整个王国中，只有她能够进行向更高位进位的棘手操作。

商人们发现这个算法非常复杂，于是他们请求你（ACMers）帮忙。你能编写一个程序，按照国王的命令进行四舍五入吗？

## 样例 #1
### 输入
```
0.0
```
### 输出
```
0
```

## 样例 #2
### 输入
```
1.49
```
### 输出
```
1
```

## 样例 #3
### 输入
```
1.50
```
### 输出
```
2
```

## 样例 #4
### 输入
```
2.71828182845904523536
```
### 输出
```
3
```

## 样例 #5
### 输入
```
3.14159265358979323846
```
### 输出
```
3
```

## 样例 #6
### 输入
```
12345678901234567890.1
```
### 输出
```
12345678901234567890
```

## 样例 #7
### 输入
```
123456789123456789.999
```
### 输出
```
GOTO Vasilisa.
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是先读入一个字符串表示的浮点数，然后找到小数点的位置，根据小数点前一位（整数部分的最后一位）是否为 9 进行不同处理：如果是 9，则输出 "GOTO Vasilisa."；如果不是 9，则根据小数点后一位的值进行四舍五入处理后输出整数部分。

各题解的算法要点和解决难点如下：
- **江山_远方**：使用 `find` 函数找到小数点位置，然后根据规则输出结果。难点在于处理四舍五入和判断整数部分最后一位是否为 9。
- **锦瑟，华年**：采用类快读的方式读入数据，判断整数部分最后一位是否为 9 并进行四舍五入。难点在于实现类快读和正确处理进位。
- **仗剑_天涯**：将四舍五入和输出操作封装成函数，逻辑清晰。难点在于函数的设计和调用。
- **RioBlu**：使用高精度加法处理进位，较为复杂。难点在于高精度加法的实现和逻辑判断。
- **谦谦君子**：使用 `substr` 函数截取整数部分，代码简洁。难点在于字符串的操作和判断。

### 题解评分
- 江山_远方：4星。思路清晰，代码简洁，使用 `find` 函数方便地找到小数点位置。
- 锦瑟，华年：3星。采用类快读方式，但代码可读性一般。
- 仗剑_天涯：3星。函数封装使逻辑清晰，但代码稍长。
- RioBlu：3星。使用高精度加法，实现复杂，增加了不必要的复杂度。
- 谦谦君子：4星。代码简洁，使用 `substr` 函数截取整数部分，易于理解。

### 所选题解
- 江山_远方（4星）：关键亮点是使用 `find` 函数快速找到小数点位置，代码简洁明了。
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int k;
int main()
{
    cin>>st; 
    k=st.find(".");
    if(st[k-1]=='9')cout<<"GOTO Vasilisa.";
    else 
    {
        if(st[k+1]>='5')
        {
            for(int i=0;i<k-1;i++)putchar(st[i]);
            putchar(st[k-1]+1);
        }
        else
            for(int i=0;i<=k-1;i++)putchar(st[i]);
    }
    return 0; 
} 
```
- 谦谦君子（4星）：关键亮点是使用 `substr` 函数截取整数部分，代码简洁易读。
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string num;
    while(cin>>num)
    {
        for(int i=0;i<num.length();++i)
        {
            if(num[i]=='.')
            {
                if(num[i-1]=='9')
                {
                    cout<<"GOTO Vasilisa."<<'\n';
                    break;
                }
                else
                {
                    if(num[i+1]>='5')
                        num[i-1]+=1;
                    string n=num.substr(0,i);
                    cout<<n<<'\n';
                    break;
                }
            }
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- 使用字符串来处理高精度的浮点数，避免了浮点数精度问题。
- 利用 `find` 函数或遍历字符串找到小数点位置，方便进行后续判断。
- 对于四舍五入，直接根据小数点后一位的值进行判断和处理。

### 可拓展之处
同类型题可能会有更复杂的四舍五入规则，或者需要处理更多位的小数。类似算法套路包括处理大整数的运算、字符串的处理和判断等。

### 推荐洛谷题目
- P1055 [NOIP2008 普及组] ISBN 号码：涉及字符串的处理和判断。
- P1598 垂直柱状图：需要对字符串进行统计和输出处理。
- P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here：涉及字符串的字符处理和简单运算。

### 个人心得摘录与总结
- 仗剑_天涯：一开始以为开 `double` 直接做就好了，但 `double` 过不了，说明在处理高精度问题时不能依赖浮点数，要使用字符串等方法。 

---
处理用时：46.15秒