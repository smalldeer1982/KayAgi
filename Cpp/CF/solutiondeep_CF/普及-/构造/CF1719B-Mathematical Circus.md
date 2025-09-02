# 题目信息

# Mathematical Circus

## 题目描述

A new entertainment has appeared in Buryatia — a mathematical circus! The magician shows two numbers to the audience — $ n $ and $ k $ , where $ n $ is even. Next, he takes all the integers from $ 1 $ to $ n $ , and splits them all into pairs $ (a, b) $ (each integer must be in exactly one pair) so that for each pair the integer $ (a + k) \cdot b $ is divisible by $ 4 $ (note that the order of the numbers in the pair matters), or reports that, unfortunately for viewers, such a split is impossible.

Burenka really likes such performances, so she asked her friend Tonya to be a magician, and also gave him the numbers $ n $ and $ k $ .

Tonya is a wolf, and as you know, wolves do not perform in the circus, even in a mathematical one. Therefore, he asks you to help him. Let him know if a suitable splitting into pairs is possible, and if possible, then tell it.

## 说明/提示

In the first test case, splitting into pairs $ (1, 2) $ and $ (3, 4) $ is suitable, same as splitting into $ (1, 4) $ and $ (3, 2) $ .

In the second test case, $ (1 + 0) \cdot 2 = 1 \cdot (2 + 0) = 2 $ is not divisible by $ 4 $ , so there is no partition.

## 样例 #1

### 输入

```
4
4 1
2 0
12 10
14 11```

### 输出

```
YES
1 2
3 4
NO
YES
3 4
7 8
11 12
2 1
6 5
10 9
YES
1 2
3 4
5 6
7 8
9 10
11 12
13 14```

# AI分析结果

### 题目中文重写
# 数学马戏团

## 题目描述
在布里亚特出现了一种新的娱乐活动——数学马戏团！魔术师向观众展示两个数字 $n$ 和 $k$，其中 $n$ 是偶数。接着，他取从 $1$ 到 $n$ 的所有整数，并将它们全部拆分成对 $(a, b)$（每个整数必须恰好位于一对中），使得对于每一对，整数 $(a + k) \cdot b$ 都能被 $4$ 整除（注意，对中数字的顺序很重要），或者向观众报告，遗憾的是，这样的拆分是不可能的。

布伦卡非常喜欢这样的表演，所以她请她的朋友托尼亚成为一名魔术师，并给了他数字 $n$ 和 $k$。

托尼亚是一只狼，众所周知，狼不会在马戏团表演，即使是在数学马戏团。因此，他请求你帮助他。让他知道是否可以进行合适的拆分，如果可以，请告诉他拆分方式。

## 说明/提示
在第一个测试用例中，拆分成对 $(1, 2)$ 和 $(3, 4)$ 是合适的，拆分成 $(1, 4)$ 和 $(3, 2)$ 也合适。

在第二个测试用例中，$(1 + 0) \cdot 2 = 1 \cdot (2 + 0) = 2$ 不能被 $4$ 整除，所以不存在拆分方案。

## 样例 #1

### 输入
```
4
4 1
2 0
12 10
14 11
```

### 输出
```
YES
1 2
3 4
NO
YES
3 4
7 8
11 12
2 1
6 5
10 9
YES
1 2
3 4
5 6
7 8
9 10
11 12
13 14
```

### 综合分析与结论
- **思路对比**：大部分题解都采用了分类讨论的思想，根据 $k$ 对 $4$ 取模的结果进行分类。如 $k \bmod 4 = 0$ 时无解；$k \bmod 4 = 1$ 或 $3$ 时，按 $(1, 2), (3, 4), \cdots$ 配对；$k \bmod 4 = 2$ 时，按 $(2, 1), (3, 4), \cdots$ 配对。部分题解通过分析 $(a + k) \cdot b$ 的数学性质来确定配对方式，还有题解采用枚举相邻数对并验证的暴力方法。
- **算法要点**：核心要点是根据 $k$ 的不同情况构造满足 $(a + k) \cdot b$ 能被 $4$ 整除的数对。对于 $k$ 为奇数，利用奇数加奇数为偶数，使 $(a + k)$ 和 $b$ 都为偶数；对于 $k$ 为偶数且 $k \bmod 4 = 2$，通过特定的数对排列凑出 $4$ 的倍数。
- **解决难点**：难点在于分析不同 $k$ 值下数对的构造方式，尤其是 $k \bmod 4 = 2$ 的情况。需要考虑如何让 $(a + k)$ 或 $b$ 成为 $4$ 的倍数，或者让 $(a + k)$ 和 $b$ 都为偶数。

### 评分较高的题解
- **作者：WhiteSunFlower（5星）**
    - **关键亮点**：思路清晰，详细分析了使 $(a + k) \cdot b$ 是 $4$ 的倍数的三种情况，并针对不同情况给出了具体的代码实现，代码可读性高。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define WhiteSunflower int main()
using namespace std;
int t,n,k;
WhiteSunflower{
    cin >> t;
    while(t--){
        cin >> n >> k;
        if(k%2==1){
            puts("YES");
            for(int i=1;i<=n;i+=2){
                cout << i << " " << i+1 << "\n";
            }
        }else if(k%2==0&&k%4!=0){
            puts("YES");
            int j=1;
            for(int i=1;i*4<=n;i++){
                cout << j << " " << i*4 << "\n";
                j+=2;
            }
            for(int i=1;i*4-2<=n;i++){
                cout << i*4-2 << " " << j << "\n";
                j+=2;
            }
        }else {
            puts("NO");
        }
    }
    return 0;
}
```
核心实现思想：先判断 $k$ 的奇偶性，若 $k$ 为奇数，直接按 $(1, 2), (3, 4), \cdots$ 输出；若 $k$ 为偶数且 $k \bmod 4 \neq 0$，先将奇数与 $4$ 的倍数配对，再将剩余的偶数与奇数配对；若不满足上述条件，则无解。
- **作者：weizhiyonghu（4星）**
    - **关键亮点**：详细分析了各种 $k$ 取值情况下的有解性和构造方法，逻辑严谨，代码简洁。
    - **核心代码**：
```cpp
#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;
int T,n,m; 
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        if(m % 2 == 1)
        {
            puts("YES\n");
            for(int i = 1;i < n;i+=2)
                printf("%d %d\n",i,i+1);
            continue;
        }
        if(m % 4 == 0)
            puts("NO\n");
        else
        {
            printf("YES\n");
            for(int i = 1;i < n;i+=2)
                if((i + m + 1) % 4 == 0)
                    printf("%d %d\n",i+1,i);
                else 
                    printf("%d %d\n",i,i+1);
        }
    }
    return 0;
}
```
核心实现思想：先判断 $k$ 的奇偶性，若 $k$ 为奇数，按 $(1, 2), (3, 4), \cdots$ 输出；若 $k$ 为偶数且 $k \bmod 4 = 0$，无解；否则，根据 $(i + k + 1) \bmod 4$ 的结果决定数对的顺序。
- **作者：D2T1（4星）**
    - **关键亮点**：简洁明了地对 $k \bmod 4$ 的值进行分类讨论，代码实现简洁高效。
    - **核心代码**：
```cpp
#define multiple_test_cases
const int N = 2e5 + 10;
int n, k;
void solve(){
    n = rdi;
    k = rdi;
    k %= 4;
    if(k == 0){
        puts("NO");
    } else if(k == 2){
        puts("YES");
        for(int i = 1; i <= n; i += 2){
            if(((i-1)/2) & 1){
                printf("%d %d\n", i, i+1);
            } else {
                printf("%d %d\n", i+1, i);
            }
        }
    } else {
        puts("YES");
        for(int i = 1; i <= n; i += 2){
            printf("%d %d\n", i, i+1);
        }
    }
}
```
核心实现思想：对 $k$ 取模 $4$ 后分类讨论，$k \bmod 4 = 0$ 时无解；$k \bmod 4 = 2$ 时，根据 $i$ 的情况调整数对顺序；其他情况按 $(1, 2), (3, 4), \cdots$ 输出。

### 最优关键思路或技巧
- **分类讨论**：根据 $k$ 对 $4$ 取模的结果进行分类讨论，能清晰地分析出不同情况下数对的构造方式。
- **奇偶性分析**：利用奇数和偶数的性质，判断 $(a + k)$ 和 $b$ 的奇偶性，从而确定数对是否满足条件。

### 可拓展之处
同类型题可能会改变整除的条件，如要求 $(a + k) \cdot b$ 能被 $6$ 整除等，解题思路仍然可以采用分类讨论和奇偶性分析的方法。类似算法套路还可以应用于其他构造类问题，通过分析目标条件，将问题拆分成不同情况进行处理。

### 洛谷相似题目推荐
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：考察博弈论和构造思想。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：涉及贪心算法和构造最优解。
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：需要运用优先队列和构造合并方案。

### 个人心得摘录与总结
- **E1_de5truct0r**：认为这是一道简单的思维题，但自己思考了 10 分钟，考虑退役。总结：即使是简单的思维题，也可能需要一定时间思考，不能轻视。
- **RoyWu1207**：考场上没完全想出证明过程，但通过分析样例找到规律并 AC。总结：在考试中，若无法严格证明，可通过分析样例找规律解题。 

---
处理用时：53.17秒