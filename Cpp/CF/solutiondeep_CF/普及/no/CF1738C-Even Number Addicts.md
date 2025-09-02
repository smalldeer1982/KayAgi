# 题目信息

# Even Number Addicts

## 题目描述

Alice and Bob are playing a game on a sequence $ a_1, a_2, \dots, a_n $ of length $ n $ . They move in turns and Alice moves first.

In the turn of each player, he or she should select an integer and remove it from the sequence. The game ends when there is no integer left in the sequence.

Alice wins if the sum of her selected integers is even; otherwise, Bob wins.

Your task is to determine who will win the game, if both players play optimally.

## 说明/提示

In the first and second test cases, Alice always selects two odd numbers, so the sum of her selected numbers is always even. Therefore, Alice always wins.

In the third test case, Bob has a winning strategy that he always selects a number with the same parity as Alice selects in her last turn. Therefore, Bob always wins.

In the fourth test case, Alice always selects two even numbers, so the sum of her selected numbers is always even. Therefore, Alice always wins.

## 样例 #1

### 输入

```
4
3
1 3 5
4
1 3 5 7
4
1 2 3 4
4
10 20 30 40```

### 输出

```
Alice
Alice
Bob
Alice```

# AI分析结果

### 题目内容重写
# 偶数爱好者

## 题目描述

Alice 和 Bob 在一个长度为 $n$ 的序列 $a_1, a_2, \dots, a_n$ 上玩游戏。他们轮流行动，Alice 先手。

在每个玩家的回合中，他或她应该选择一个整数并将其从序列中移除。当序列中没有整数时，游戏结束。

如果 Alice 选择的整数的和为偶数，则 Alice 获胜；否则，Bob 获胜。

你的任务是确定谁会赢得游戏，如果双方都采取最优策略。

## 说明/提示

在第一个和第二个测试用例中，Alice 总是选择两个奇数，因此她选择的数的和总是偶数。因此，Alice 总是获胜。

在第三个测试用例中，Bob 有一个必胜策略，即他总是选择与 Alice 在她最后一次选择中相同奇偶性的数。因此，Bob 总是获胜。

在第四个测试用例中，Alice 总是选择两个偶数，因此她选择的数的和总是偶数。因此，Alice 总是获胜。

## 样例 #1

### 输入

```
4
3
1 3 5
4
1 3 5 7
4
1 2 3 4
4
10 20 30 40```

### 输出

```
Alice
Alice
Bob
Alice```

### 算法分类
数学

### 题解分析与结论
本题的核心在于通过数学推理确定 Alice 和 Bob 的胜负关系。主要思路是通过统计序列中奇数和偶数的个数，并根据其模 4 的结果来判断胜负。这种方法避免了复杂的动态规划，直接通过数学规律得出结论。

### 评分较高的题解
1. **作者：Sycamore_Ma (赞：12)**
   - **星级：5**
   - **关键亮点：** 提供了详细的数学推理和分类讨论，逻辑清晰，代码简洁。
   - **个人心得：** 通过数学推理简化了问题，避免了复杂的动态规划。

2. **作者：XenonWZH (赞：2)**
   - **星级：4**
   - **关键亮点：** 通过分类讨论和数学推理，简化了问题，代码实现简洁。
   - **个人心得：** 通过数学推理和分类讨论，简化了问题的复杂度。

3. **作者：zuytong (赞：1)**
   - **星级：4**
   - **关键亮点：** 通过数学推理和分类讨论，简化了问题，代码实现简洁。
   - **个人心得：** 通过数学推理和分类讨论，简化了问题的复杂度。

### 最优关键思路
通过统计序列中奇数和偶数的个数，并根据其模 4 的结果来判断胜负。这种方法避免了复杂的动态规划，直接通过数学规律得出结论。

### 可拓展之处
类似的问题可以通过数学推理和分类讨论来简化复杂度，特别是在涉及到奇偶性和模运算的问题中。

### 推荐题目
1. [洛谷 P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [洛谷 P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
3. [洛谷 P1044 栈](https://www.luogu.com.cn/problem/P1044)

### 重点代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define YN(x) cout << (x ? "Alice" : "Bob") << endl

int main()
{
    int tt;     
    cin >> tt;
    while (tt --){
        int n; 		
        cin >> n;
        int cntOdd = 0, cntEven = 0;
        int x;      
        for (int i = 0; i < n; i ++){
            cin >> x;
            if (x & 1)  cntOdd ++;
            else        cntEven ++;
        }
        
        bool ok = false;
        if (cntOdd % 4 == 2)		ok = false;
        else if (cntOdd % 4 == 3)	ok = true;
    	else if (cntOdd % 4 == 0)	ok = true;
    	else if (cntEven % 2 == 1)	ok = true;
    	
        YN(ok);
    }
    return 0;
}
```

### 核心代码实现思想
通过统计序列中奇数和偶数的个数，并根据其模 4 的结果来判断胜负。代码简洁，逻辑清晰。

---
处理用时：30.77秒