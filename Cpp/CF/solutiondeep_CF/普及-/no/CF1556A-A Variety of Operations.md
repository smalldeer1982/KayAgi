# 题目信息

# A Variety of Operations

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1556A/5428dff7add309271d42dab51ff349469f968da9.png)William has two numbers $ a $ and $ b $ initially both equal to zero. William mastered performing three different operations with them quickly. Before performing each operation some positive integer $ k $ is picked, which is then used to perform one of the following operations: (note, that for each operation you can choose a new positive integer $ k $ )

1. add number $ k $ to both $ a $ and $ b $ , or
2. add number $ k $ to $ a $ and subtract $ k $ from $ b $ , or
3. add number $ k $ to $ b $ and subtract $ k $ from $ a $ .

Note that after performing operations, numbers $ a $ and $ b $ may become negative as well.

William wants to find out the minimal number of operations he would have to perform to make $ a $ equal to his favorite number $ c $ and $ b $ equal to his second favorite number $ d $ .

## 说明/提示

Let us demonstrate one of the suboptimal ways of getting a pair $ (3, 5) $ :

- Using an operation of the first type with $ k=1 $ , the current pair would be equal to $ (1, 1) $ .
- Using an operation of the third type with $ k=8 $ , the current pair would be equal to $ (-7, 9) $ .
- Using an operation of the second type with $ k=7 $ , the current pair would be equal to $ (0, 2) $ .
- Using an operation of the first type with $ k=3 $ , the current pair would be equal to $ (3, 5) $ .

## 样例 #1

### 输入

```
6
1 2
3 5
5 3
6 6
8 0
0 0```

### 输出

```
-1
2
2
1
2
0```

# AI分析结果

### 题目内容
# 多种操作

## 题目描述
William 有两个数 $a$ 和 $b$，初始时都等于 $0$。William 熟练掌握了快速执行三种不同的操作。在执行每个操作之前，会选择一个正整数 $k$，然后用于执行以下操作之一：（注意，对于每个操作，你可以选择一个新的正整数 $k$）
1. 将数 $k$ 加到 $a$ 和 $b$ 上；
2. 将数 $k$ 加到 $a$ 上，并从 $b$ 中减去 $k$；
3. 将数 $k$ 加到 $b$ 上，并从 $a$ 中减去 $k$。

注意，执行操作后，数 $a$ 和 $b$ 也可能变为负数。

William 想知道他必须执行的最少操作次数，以使 $a$ 等于他最喜欢的数 $c$，$b$ 等于他第二喜欢的数 $d$。

## 说明/提示
让我们展示一种得到数对 $(3, 5)$ 的非最优方法：
- 使用第一种类型的操作，$k = 1$，当前数对将等于 $(1, 1)$。
- 使用第三种类型的操作，$k = 8$，当前数对将等于 $(-7, 9)$。
- 使用第二种类型的操作，$k = 7$，当前数对将等于 $(0, 2)$。
- 使用第一种类型的操作，$k = 3$，当前数对将等于 $(3, 5)$。

## 样例 #1
### 输入
```
6
1 2
3 5
5 3
6 6
8 0
0 0
```
### 输出
```
-1
2
2
1
2
0
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是基于对三种操作特性的分析来确定最少操作次数。要点在于发现操作对两数和与差的影响规律，难点是准确判断各种情况并分类讨论。所有题解都指出若 $c + d$ 为奇数则无解，对于 $c = d = 0$ 答案为 $0$ ；$c = d$ 或 $c = -d$ 答案为 $1$ ；其他情况答案为 $2$ 。只是在分析过程和表述上有所差异。

### 所选的题解
- **作者：wanggk (赞：3)  星级：4星**
    - **关键亮点**：清晰阐述操作对两数和与差的影响，根据和与差的变化判断操作次数，逻辑清晰。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int T,c,d;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&c,&d);
        if((c + d) % 2 == 1)
        {
            printf("-1\n");
            continue;
        }
        int ans = 0;
        if(c + d!= 0) ans++;
        if(c!= d) ans++;
        printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：先判断 $c + d$ 的奇偶性，若为奇数输出 $-1$ ；再根据 $c + d$ 是否为 $0$ 以及 $c$ 是否等于 $d$ 来确定操作次数。

- **作者：yangzd (赞：1)  星级：4星**
    - **关键亮点**：全面证明只有 $-1,0,1,2$ 这 $4$ 种结果情况，分析每种情况的原因清晰明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std; 

signed main()
{
    ios::sync_with_stdio(0);

    long long t;
    
    cin >> t;
    
    while(t--)
    {
        long long a,b;
        
        cin >> a >> b;
        
        if(abs(a - b)&1)
            cout << "-1" << endl;
            
        else if(a == b && a == 0)
            cout << "0" << endl;
            
        else if(a == b)
            cout << "1" << endl;
             
        else 
            cout << "2" << endl;
    }
    
    return 0;
}
```
    - **核心实现思想**：通过判断 $a - b$ 的奇偶性确定是否有解，再根据 $a$ 和 $b$ 是否为 $0$ 以及是否相等来确定操作次数。

- **作者：fz20181223 (赞：0)  星级：4星**
    - **关键亮点**：利用数轴模拟 $a$ 和 $b$ 的移动过程，直观地得出答案至多为 $2$ ，并讨论省去步骤的条件，思路独特。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int c,d;
        scanf("%d %d",&c,&d);
        if((d + c)&1) printf("-1\n");
        else printf("%d\n",2 - (d == c) - (d == -c));
    }
    return 0;}
```
    - **核心实现思想**：根据 $d + c$ 的奇偶性判断是否有解，通过式子 $2 - (d == c) - (d == -c)$ 直接计算操作次数。

### 最优关键思路或技巧
通过分析操作对两数和与差的影响，利用数学性质（如和的奇偶性不变）来简化问题，快速判断结果。对于多种情况的分类讨论要全面且准确，避免遗漏。

### 同类型题或类似算法套路拓展
此类题目通常需要深入分析操作对数据的影响规律，利用数学性质简化问题求解。常见套路是找出操作前后数据的不变量或变化规律，基于此进行分类讨论得出结果。

### 推荐洛谷题目
- **P1028 [NOIP2001 普及组] 数的计算**：通过分析数字生成规则，利用数学规律递推求解。
- **P1147 连续自然数和**：利用等差数列求和公式及数学推导，找出满足条件的连续自然数序列。
- **P2669 [NOIP2015 普及组] 金币**：根据题目描述的规律，通过数学计算得出结果。 

---
处理用时：37.06秒