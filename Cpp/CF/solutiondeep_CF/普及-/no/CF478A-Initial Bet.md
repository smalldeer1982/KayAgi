# 题目信息

# Initial Bet

## 题目描述

There are five people playing a game called "Generosity". Each person gives some non-zero number of coins $ b $ as an initial bet. After all players make their bets of $ b $ coins, the following operation is repeated for several times: a coin is passed from one player to some other player.

Your task is to write a program that can, given the number of coins each player has at the end of the game, determine the size $ b $ of the initial bet or find out that such outcome of the game cannot be obtained for any positive number of coins $ b $ in the initial bet.

## 说明/提示

In the first sample the following sequence of operations is possible:

1. One coin is passed from the fourth player to the second player;
2. One coin is passed from the fourth player to the fifth player;
3. One coin is passed from the first player to the third player;
4. One coin is passed from the fourth player to the second player.

## 样例 #1

### 输入

```
2 5 4 0 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 5 9 2 1
```

### 输出

```
-1
```

# AI分析结果

### 中文重写题目内容
# 初始赌注

## 题目描述
有五个人在玩一个叫做“慷慨”的游戏。每个人都拿出一些非零数量的硬币 $b$ 作为初始赌注。在所有玩家都下注 $b$ 枚硬币后，会重复进行以下操作若干次：将一枚硬币从一个玩家传递给另一个玩家。

你的任务是编写一个程序，根据游戏结束时每个玩家拥有的硬币数量，确定初始赌注 $b$ 的大小；如果对于任何正整数的初始赌注 $b$ 都无法得到这样的游戏结果，则输出 -1。

## 说明/提示
在第一个样例中，可能的操作序列如下：
1. 一枚硬币从第四个玩家传递给第二个玩家；
2. 一枚硬币从第四个玩家传递给第五个玩家；
3. 一枚硬币从第一个玩家传递给第三个玩家；
4. 一枚硬币从第四个玩家传递给第二个玩家。

## 样例 #1
### 输入
```
2 5 4 0 4
```
### 输出
```
3
```

## 样例 #2
### 输入
```
4 5 9 2 1
```
### 输出
```
-1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是利用游戏过程中硬币总数不变这一特性。由于五个人初始下注相同，所以若游戏结束时硬币总数是 5 的倍数且总数不为 0，那么初始赌注 $b$ 就等于硬币总数除以 5；若总数不是 5 的倍数或者总数为 0，则无解，输出 -1。各题解的区别主要在于代码实现方式，有的使用数组，有的直接使用多个变量存储输入，但整体逻辑一致。

### 所选的题解
- Mr_Avalan（4 星）
  - 关键亮点：思路清晰，代码简洁明了，有详细的注释说明，对特殊情况（总数为 0）的处理也有明确提示。
- JimmyF（4 星）
  - 关键亮点：思路阐述清晰，用数学公式表达了核心逻辑，代码简洁，对细节（总数为 0）的处理有强调。
- 仗剑_天涯（4 星）
  - 关键亮点：对题目进行了转化说明，代码使用函数封装输入和判断逻辑，结构清晰。

### 重点代码
#### Mr_Avalan 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[6],s=0;
int main()
{
    for(int i=1;i<=5;i++)
    {
        cin>>a[i];//输入
        s+=a[i];//求总数
    }
    if(s%5==0&&s)//如果是5的倍数并且不为0
    {
        cout<<s/5;//输出
        return 0;
    }
    cout<<-1;//因为如果有解在if中程序就结束了,所以这里没有写else
    return 0;
}
```
核心实现思想：先输入每个玩家的硬币数并累加得到总数，然后判断总数是否为 5 的倍数且不为 0，若是则输出总数除以 5 的结果，否则输出 -1。

#### JimmyF 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,sum;
int main()
{
    cin>>a>>b>>c>>d>>e;
    sum=a+b+c+d+e;
    if(sum%5==0&&sum!=0)cout<<sum/5; //注意细节
    else cout<<-1;
    return 0;
}
```
核心实现思想：直接输入五个玩家的硬币数并求和，判断和是否为 5 的倍数且不为 0，根据判断结果输出相应答案。

#### 仗剑_天涯的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,s; 
void doit()//void表示只做一件事情，不返回值
{
    for(int i=1;i<=5;i++)
    {
        cin>>x;
        s+=x;
    }
    if(s==0)//特判0
    {
        cout<<-1;//无解
        return;//结束函数
    }
    if(s%5!=0) cout<<-1;//无解
    else cout<<s/5;//有解
}
int main()
{
    doit();//调用过程函数
    return 0;
}
```
核心实现思想：将输入和判断逻辑封装在 `doit` 函数中，在函数中输入每个玩家的硬币数并求和，先特判和为 0 的情况，再判断和是否为 5 的倍数，根据结果输出相应答案。

### 最优关键思路或技巧
利用游戏中硬币总数不变的特性，通过判断总数是否为 5 的倍数且不为 0 来确定初始赌注，简化了问题的解决过程。

### 可拓展之处
同类型题目可能会改变玩家数量或者操作规则，但核心思路依然是抓住某个不变量（如总数、差值等），通过数学运算来求解。类似算法套路可用于解决一些涉及数量分配、交换且存在不变量的问题。

### 推荐题目
1. [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)

### 个人心得摘录与总结
部分题解提到要注意特判硬币总数为 0 的情况，这是本题的一个容易忽略的细节，在解题时需要仔细分析题目条件，考虑到所有可能的特殊情况。 

---
处理用时：33.19秒