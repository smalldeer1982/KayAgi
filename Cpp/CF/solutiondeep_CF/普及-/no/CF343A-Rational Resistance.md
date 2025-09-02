# 题目信息

# Rational Resistance

## 题目描述

Mad scientist Mike is building a time machine in his spare time. To finish the work, he needs a resistor with a certain resistance value.

However, all Mike has is lots of identical resistors with unit resistance $ R_{0}=1 $ . Elements with other resistance can be constructed from these resistors. In this problem, we will consider the following as elements:

1. one resistor;
2. an element and one resistor plugged in sequence;
3. an element and one resistor plugged in parallel.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/f117fcf32ddafc80e319e28fce885c21483edc5b.png)With the consecutive connection the resistance of the new element equals $ R=R_{e}+R_{0} $ . With the parallel connection the resistance of the new element equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/a708eb8090c66cbbd34afced0c36506bcb612681.png). In this case $ R_{e} $ equals the resistance of the element being connected.

Mike needs to assemble an element with a resistance equal to the fraction ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/eecd60ed91fbeebe74e2406ea1a11d26df905945.png). Determine the smallest possible number of resistors he needs to make such an element.

## 说明/提示

In the first sample, one resistor is enough.

In the second sample one can connect the resistors in parallel, take the resulting element and connect it to a third resistor consecutively. Then, we get an element with resistance ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/234023ef6c61445a95e9903d46cd7846f3823141.png). We cannot make this element using two resistors.

## 样例 #1

### 输入

```
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
199 200
```

### 输出

```
200
```

# AI分析结果

### 题目内容
# 有理电阻

## 题目描述
疯狂科学家迈克正在业余时间建造一台时间机器。为了完成这项工作，他需要一个具有特定阻值的电阻。

然而，迈克所拥有的只是大量阻值为单位电阻 $R_{0}=1$ 的相同电阻。可以用这些电阻构建出具有其他阻值的元件。在本题中，我们将以下情况视为元件：
1. 一个电阻；
2. 一个元件和一个电阻串联；
3. 一个元件和一个电阻并联。

![电阻连接示意图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/f117fcf32ddafc80e319e28fce885c21483edc5b.png)
串联时，新元件的电阻值等于 $R = R_{e} + R_{0}$。并联时，新元件的电阻值等于![并联电阻计算公式](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/a708eb8090c66cbbd34afced0c36506bcb612681.png)。在这种情况下，$R_{e}$ 等于所连接元件的电阻值。

迈克需要组装一个电阻值等于分数![目标电阻分数](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/eecd60ed91fbeebe74e2406ea1a11d26df905945.png) 的元件。确定他制造这样一个元件所需的最少电阻数量。

## 说明/提示
在第一个样例中，一个电阻就足够了。

在第二个样例中，可以先将电阻并联，然后将得到的元件与第三个电阻串联。这样，我们就得到了一个电阻值为![第二个样例电阻值](https://cdn.luogu.com.cn/upload/vjudge_pic/CF343A/234023ef6c61445a95e9903d46cd7846f3823141.png) 的元件。我们无法用两个电阻制造出这个元件。

## 样例 #1
### 输入
```
1 1
```
### 输出
```
1
```

## 样例 #2
### 输入
```
3 2
```
### 输出
```
3
```

## 样例 #3
### 输入
```
199 200
```
### 输出
```
200
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路基本一致，均通过分析串联和并联电阻的计算方式，得出从目标电阻 $\frac{a}{b}$ 反推的方法，即若 $a > b$，则类似串联操作变为 $a - b$；若 $b > a$，则类似并联操作变为 $b - a$，此过程类似辗转相减法。由于数据范围大，直接相减会超时，所以都采用辗转相除法优化。各题解主要差异在于表述清晰度和代码风格。

### 所选的题解
- **作者：Alex_Wei (5星)**
    - **关键亮点**：思路阐述详细，从题目翻译到具体思路推导，逐步讲解，对辗转相减法到辗转相除法的转变解释清晰，代码简洁明了。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
long long a,b,c,ans; 
int main()
{
    std::cin>>a>>b;
    while(b!=0)ans+=a/b,c=a%b,a=b,b=c;
    std::cout<<ans;
}
```
核心实现思想：利用 `while` 循环进行辗转相除，每次循环将 $a$ 除以 $b$ 的商累加到 `ans` 中，然后更新 $a$ 和 $b$ 的值，直到 $b$ 为 $0$，此时 `ans` 即为所需最少电阻数量。

- **作者：封禁用户 (4星)**
    - **关键亮点**：题意简述清晰，对题目分析有条理，先给出正向合成电阻的公式，再反推得到解题思路，代码中有关闭同步流加速输入输出的优化，且对代码有较详细注释。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include <iostream>
using namespace std;
typedef long long ll; 
int main()
{
    ios::sync_with_stdio(0); 
    ll a, b, ans = 0; 
    cin >> a >> b;
    while (b!= 0) 
    {
        ans += a / b;
        int t = a % b;
        a = b;
        b = t;
    }
    cout << ans;
    return 0; 
}
```
核心实现思想：与上一题解类似，通过 `while` 循环辗转相除，计算过程中累加商到 `ans`，最终输出 `ans` 作为最少电阻数量。

### 最优关键思路或技巧
通过分析串联和并联电阻的运算规律，发现可从目标电阻值逆向推导，且推导过程类似辗转相减法，进而利用辗转相除法优化计算，避免大数据范围下的超时问题。

### 同类型题或类似算法套路拓展
此类题目通常围绕数学规律的发现与运用，通过对给定操作的数学分析，找到逆向或正向的计算方法，常涉及数论相关知识，如最大公约数、辗转相除法等的灵活应用。

### 洛谷相似题目推荐
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：考察对最大公约数和最小公倍数概念的理解及相关计算。
- [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：同样涉及数论知识，需要通过分析条件，利用最大公约数等概念解决问题。
- [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：与有理数运算相关，可锻炼对有理数在编程中的处理能力。 

---
处理用时：58.48秒