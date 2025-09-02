# 题目信息

# RPD and Rap Sheet (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is that here $ k=2 $ . You can make hacks only if both the versions of the problem are solved.

This is an interactive problem.

Every decimal number has a base $ k $ equivalent. The individual digits of a base $ k $ number are called $ k $ -its. Let's define the $ k $ -itwise XOR of two $ k $ -its $ a $ and $ b $ as $ (a + b)\bmod k $ .

The $ k $ -itwise XOR of two base $ k $ numbers is equal to the new number formed by taking the $ k $ -itwise XOR of their corresponding $ k $ -its. The $ k $ -itwise XOR of two decimal numbers $ a $ and $ b $ is denoted by $ a\oplus_{k} b $ and is equal to the decimal representation of the $ k $ -itwise XOR of the base $ k $ representations of $ a $ and $ b $ . All further numbers used in the statement below are in decimal unless specified. When $ k = 2 $ (it is always true in this version), the $ k $ -itwise XOR is the same as the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

You have hacked the criminal database of Rockport Police Department (RPD), also known as the Rap Sheet. But in order to access it, you require a password. You don't know it, but you are quite sure that it lies between $ 0 $ and $ n-1 $ inclusive. So, you have decided to guess it. Luckily, you can try at most $ n $ times without being blocked by the system. But the system is adaptive. Each time you make an incorrect guess, it changes the password. Specifically, if the password before the guess was $ x $ , and you guess a different number $ y $ , then the system changes the password to a number $ z $ such that $ x\oplus_{k} z=y $ . Guess the password and break into the system.

## 说明/提示

In the example test case, the hidden password is $ 2 $ .

The first query is $ 3 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 1 $ since $ 2\oplus_2 1=3 $ .

The second query is $ 4 $ . It is not equal to the current password. So, $ 0 $ is returned, and the password is changed to $ 5 $ since $ 1\oplus_2 5=4 $ .

The third query is $ 5 $ . It is equal to the current password. So, $ 1 $ is returned, and the job is done.

Note that this initial password is taken just for the sake of explanation. When you submit, the interactor might behave differently because it is adaptive.

## 样例 #1

### 输入

```
1
5 2

0

0

1```

### 输出

```
3

4

5```

# AI分析结果

### 题目内容中文重写
# RPD和犯罪记录（简单版本）

## 题目描述
这是该问题的简单版本。唯一的区别在于这里 $k = 2$。只有当两个版本的问题都解决后，你才能进行 Hack 操作。

这是一个交互式问题。

每个十进制数都有对应的 $k$ 进制表示。$k$ 进制数的各个数位被称为 $k$ - 位（$k$ - its）。我们定义两个 $k$ - 位 $a$ 和 $b$ 的 $k$ - 位异或为 $(a + b) \bmod k$。

两个 $k$ 进制数的 $k$ - 位异或等于将它们对应 $k$ - 位进行 $k$ - 位异或后形成的新数。两个十进制数 $a$ 和 $b$ 的 $k$ - 位异或用 $a \oplus_{k} b$ 表示，且等于 $a$ 和 $b$ 的 $k$ 进制表示进行 $k$ - 位异或后的十进制表示。除非另有说明，下面陈述中使用的所有数字均为十进制。当 $k = 2$（在这个版本中始终如此）时，$k$ - 位异或与 [按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) 相同。

你已经黑入了罗克波特警察局（RPD）的犯罪数据库，也就是所谓的犯罪记录。但是为了访问它，你需要一个密码。你不知道密码是什么，但你很确定它在 $0$ 到 $n - 1$（包含）之间。所以，你决定尝试猜测。幸运的是，你最多可以尝试 $n$ 次而不会被系统封锁。但是系统是自适应的。每次你做出错误的猜测时，它都会更改密码。具体来说，如果猜测前的密码是 $x$，而你猜测了一个不同的数字 $y$，那么系统会将密码更改为一个数字 $z$，使得 $x \oplus_{k} z = y$。猜出密码并侵入系统。

## 说明/提示
在示例测试用例中，隐藏的密码是 $2$。

第一次查询是 $3$。它不等于当前密码。所以，返回 $0$，并且密码更改为 $1$，因为 $2 \oplus_2 1 = 3$。

第二次查询是 $4$。它不等于当前密码。所以，返回 $0$，并且密码更改为 $5$，因为 $1 \oplus_2 5 = 4$。

第三次查询是 $5$。它等于当前密码。所以，返回 $1$，任务完成。

请注意，这个初始密码只是为了解释而设定的。当你提交时，交互器的行为可能会不同，因为它是自适应的。

## 样例 #1
### 输入
```
1
5 2

0

0

1
```
### 输出
```
3

4

5
```

### 算法分类
位运算

### 综合分析与结论
- **思路对比**：三位作者思路本质相同，都是利用异或的性质来消除前面询问对当前询问的影响。通过顺序枚举，根据异或运算的结合律和自反性，将每次询问后的密码变化进行化简，从而找到一种在 $n$ 次询问内猜出密码的方法。
- **算法要点**：利用异或运算 $x \oplus z = y \Rightarrow x \oplus y = z$ 的性质，按顺序枚举 $0$ 到 $n - 1$，每次询问 $i \oplus (i - 1)$（$i$ 从 $1$ 开始），初始询问 $0$。
- **解决难点**：解决了系统自适应更改密码带来的问题，通过异或运算的特性，保证在 $n$ 次询问内必然能猜出密码。

### 题解评分与展示
- **Evier（5星）**：
    - **关键亮点**：思路清晰，对异或运算的推导过程详细，代码注释完整，可读性高。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,n,k;
int main(){
    cin>>T;
    while(T--){
        cin>>n>>k;
        int re,x=0;
        cout<<"0"<<endl;
        cin>>re;
        if(re==0){
            for(int i=1;i<=n;i++){
                cout<<(x^i)<<endl;
                x=i;
                cin>>re;
                if(re==1)break;
            }
        }
    }
}
```
核心实现思想：先询问 $0$，若猜错则从 $1$ 开始顺序枚举，每次询问 $x$ 与当前枚举值 $i$ 的异或结果，同时更新 $x$ 为 $i$，直到猜对密码。

- **_lgh_（4星）**：
    - **关键亮点**：思路简洁明了，对证明过程有详细说明，代码中注意到了输出刷新的问题，避免了 UKE 错误。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T,n,k,x;
    scanf("%d",&T);//输入
    while(T--)
    {
        scanf("%d%d",&n,&k);//输入
        for(int i=0; i<n; ++i)//枚举
        {
            if(!i) printf("0\n");
            else printf("%d\n",i^(i-1));//直接猜
            cout.flush();//不加这一行会UKE
            scanf("%d",&x);
            if(x==1) break;
        }
    }
}
```
核心实现思想：通过循环枚举 $0$ 到 $n - 1$，第一次询问 $0$，后续每次询问 $i$ 与 $i - 1$ 的异或结果，每次输出后刷新输出缓冲区，直到猜对密码。

### 最优关键思路或技巧
利用异或运算的性质，通过顺序枚举并构造特定的询问值，消除前面询问对当前询问的影响，从而在 $n$ 次询问内猜出密码。

### 可拓展之处
同类型题可能会改变 $k$ 的值，或者改变密码更新的规则，但核心思路可能仍然是利用相应运算的性质来构造询问策略。类似算法套路可以应用在其他交互式问题中，通过分析规则和运算性质来设计询问方案。

### 推荐洛谷题目
1. [P1886 滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886)：涉及位运算和队列的应用。
2. [P1047 [NOIP2005 普及组] 校门外的树](https://www.luogu.com.cn/problem/P1047)：可以通过位运算简化一些判断过程。
3. [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：简单的模拟题，可结合位运算进行优化。

### 个人心得摘录与总结
_lgh_ 的题解中提到 “cout.flush();//不加这一行会UKE”，总结为在交互式问题中，要注意输出缓冲区的刷新，否则可能会导致答案错误（UKE）。 

---
处理用时：50.23秒