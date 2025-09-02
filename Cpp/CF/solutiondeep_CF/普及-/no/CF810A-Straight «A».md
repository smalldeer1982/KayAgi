# 题目信息

# Straight «A»

## 题目描述

Noora is a student of one famous high school. It's her final year in school — she is going to study in university next year. However, she has to get an «A» graduation certificate in order to apply to a prestigious one.

In school, where Noora is studying, teachers are putting down marks to the online class register, which are integers from $ 1 $ to $ k $ . The worst mark is $ 1 $ , the best is $ k $ . Mark that is going to the certificate, is calculated as an average of all the marks, rounded to the closest integer. If several answers are possible, rounding up is produced. For example, $ 7.3 $ is rounded to $ 7 $ , but $ 7.5 $ and $ 7.8784 $ — to $ 8 $ .

For instance, if Noora has marks $ [8,9] $ , then the mark to the certificate is $ 9 $ , because the average is equal to $ 8.5 $ and rounded to $ 9 $ , but if the marks are $ [8,8,9] $ , Noora will have graduation certificate with $ 8 $ .

To graduate with «A» certificate, Noora has to have mark $ k $ .

Noora got $ n $ marks in register this year. However, she is afraid that her marks are not enough to get final mark $ k $ . Noora decided to ask for help in the internet, where hacker Leha immediately responded to her request. He is ready to hack class register for Noora and to add Noora any number of additional marks from $ 1 $ to $ k $ . At the same time, Leha want his hack be unseen to everyone, so he decided to add as less as possible additional marks. Please help Leha to calculate the minimal number of marks he has to add, so that final Noora's mark will become equal to $ k $ .

## 说明/提示

Consider the first example testcase.

Maximal mark is $ 10 $ , Noora received two marks — $ 8 $ and $ 9 $ , so current final mark is $ 9 $ . To fix it, Leha can add marks $ [10,10,10,10] $ ( $ 4 $ marks in total) to the registry, achieving Noora having average mark equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF810A/b75d87f7c46ec7c9f8f2851b79244a71ffa349ba.png). Consequently, new final mark is $ 10 $ . Less number of marks won't fix the situation.

In the second example Leha can add $ [5,5,5] $ to the registry, so that making average mark equal to $ 4.5 $ , which is enough to have $ 5 $ in the certificate.

## 样例 #1

### 输入

```
2 10
8 9
```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5
4 4 4
```

### 输出

```
3```

# AI分析结果

### 题目翻译
# 全优成绩

## 题目描述
诺拉是一所著名高中的学生。这是她在学校的最后一年——明年她将进入大学学习。然而，为了申请一所著名的大学，她必须获得一个“A”级的毕业证书。

在诺拉就读的学校里，老师们会将分数录入在线班级登记册，分数是从 1 到 k 的整数。最差的分数是 1，最好的分数是 k。记入毕业证书的分数是所有分数的平均值，四舍五入到最接近的整数。如果有多个可能的答案，则向上取整。例如，7.3 四舍五入为 7，但 7.5 和 7.8784 四舍五入为 8。

例如，如果诺拉的分数是 [8, 9]，那么毕业证书上的分数是 9，因为平均分是 8.5，四舍五入后为 9；但如果分数是 [8, 8, 9]，诺拉的毕业证书上的分数将是 8。

为了以“A”级毕业证书毕业，诺拉的最终分数必须达到 k。

诺拉今年在登记册上已经有了 n 个分数。然而，她担心自己的分数不足以获得最终分数 k。诺拉决定在网上寻求帮助，黑客莱哈立即回应了她的请求。他准备为诺拉黑进班级登记册，并为诺拉添加任意数量的 1 到 k 之间的额外分数。同时，莱哈希望他的黑客行为不被任何人发现，所以他决定添加尽可能少的额外分数。请帮助莱哈计算他必须添加的最少分数，以使诺拉的最终分数达到 k。

## 说明/提示
考虑第一个示例测试用例。
最高分是 10，诺拉得到了两个分数——8 和 9，所以当前的最终分数是 9。为了修正这个问题，莱哈可以在登记册中添加分数 [10, 10, 10, 10]（总共 4 个分数），使诺拉的平均分等于 [具体公式]。因此，新的最终分数是 10。更少的分数无法解决这个问题。
在第二个示例中，莱哈可以在登记册中添加 [5, 5, 5]，使平均分等于 4.5，这足以使毕业证书上的分数为 5。

## 样例 #1
### 输入
```
2 10
8 9
```
### 输出
```
4
```

## 样例 #2
### 输入
```
3 5
4 4 4
```
### 输出
```
3
```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕如何计算出最少添加多少个 k 能使最终平均分四舍五入后为 k 展开。思路主要分为两类：一类是通过数学推导得出直接计算结果的公式；另一类是通过枚举或模拟添加 k 的过程，不断计算平均分，直到满足条件。

数学推导类题解的要点在于列出关于平均分四舍五入的不等式，然后求解出添加 k 的数量的表达式。模拟枚举类题解的要点在于处理好四舍五入的判断，通常采用扩大倍数或使用四舍五入函数的方法。

解决的难点主要在于四舍五入的处理，不同题解采用了不同的方式，如扩大倍数利用整除、使用库函数（round）、自定义四舍五入函数等。

### 高星题解
- **L2_sheep（4星）**
    - **关键亮点**：思路清晰，通过数学推导得出直接计算结果的公式，代码简洁高效。
    - **重点代码**：
```cpp
#include <stdio.h>

int main() 
{
    int n, k, s = 0, x, i, a;
        
    scanf("%d%d", &n, &k);
    for(i = 0; i < n; i++){
    	scanf("%d", &x);
    	s += x;
	}
	a = (2 * k - 1) * n - 2 * s;
    if(a < 0) a = 0;
    printf("%d", a);
    return 0;
}
```
核心实现思想：先计算出已有分数的总和 s，然后根据数学推导得出的公式 `a = (2 * k - 1) * n - 2 * s` 计算出需要添加的分数个数，最后判断结果是否小于 0，若小于 0 则取 0。

- **TRZ_2007（4星）**
    - **关键亮点**：详细给出了数学推导过程，逻辑严谨，代码规范。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

int n,k,m,s;
int a[N];

int main() {
	scanf("%d %d",&n,&k);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
		s += a[i];
	}
	m = 2 * n * k - n - s * 2;
	if(m <= 0) m = 0;
	printf("%d\n",m);
	return 0;
}
```
核心实现思想：同样先计算已有分数总和 s，再根据推导公式 `m = 2 * n * k - n - s * 2` 计算结果，最后处理结果小于等于 0 的情况。

- **学而思李老师（4星）**
    - **关键亮点**：详细解释了四舍五入的条件，并通过数学推导得出最终结果的表达式，思路清晰。
    - **重点代码**：无具体代码，但核心思路是输出 `max((2k - 1)n - 2 * sum, 0)`。
核心实现思想：根据四舍五入的条件列出不等式，推导得出需要添加的分数个数的表达式，然后取表达式结果和 0 中的最大值。

### 最优关键思路或技巧
- 数学推导：通过列出关于平均分四舍五入的不等式，求解出添加 k 的数量的表达式，避免了枚举或模拟的过程，时间复杂度为 O(1)。
- 四舍五入处理：可以采用扩大倍数利用整除、使用库函数（round）、自定义四舍五入函数等方法。

### 拓展思路
同类型题可能会改变分数的范围、四舍五入的规则或添加其他限制条件，但核心思路仍然是围绕平均分的计算和四舍五入的处理。类似算法套路可以应用于其他需要根据条件计算最优解的数学问题。

### 推荐题目
- P1001 A+B Problem
- P1002 过河卒
- P1003 铺地毯

### 个人心得摘录与总结
- **动态WA**：提到程序存在缺陷，如果有像 k = 5，而 z/n = 4.45 这种需要多次四舍五入的数据会被卡，需要把数据都扩大 10^x 倍，保证不出现多次四舍五入。总结：在处理四舍五入问题时，要注意数据精度和多次四舍五入可能带来的影响。
- **SIXIANG32**：指出 C++ 如果要用 `round` 函数来四舍五入，除以的数必须要乘 1.0，因为和是整数，n + i 也是整数，整数除以整数是整数，所以要变成实数。总结：在使用四舍五入函数时，要注意数据类型的转换，避免整数除法导致结果不准确。

---
处理用时：46.08秒