# 题目信息

# Counting-out Rhyme

## 题目描述

 $ n $ children are standing in a circle and playing the counting-out game. Children are numbered clockwise from $ 1 $ to $ n $ . In the beginning, the first child is considered the leader. The game is played in $ k $ steps. In the $ i $ -th step the leader counts out $ a_{i} $ people in clockwise order, starting from the next person. The last one to be pointed at by the leader is eliminated, and the next player after him becomes the new leader.

For example, if there are children with numbers $ [8,10,13,14,16] $ currently in the circle, the leader is child $ 13 $ and $ a_{i}=12 $ , then counting-out rhyme ends on child $ 16 $ , who is eliminated. Child $ 8 $ becomes the leader.

You have to write a program which prints the number of the child to be eliminated on every step.

## 说明/提示

Let's consider first example:

- In the first step child $ 4 $ is eliminated, child $ 5 $ becomes the leader.
- In the second step child $ 2 $ is eliminated, child $ 3 $ becomes the leader.
- In the third step child $ 5 $ is eliminated, child $ 6 $ becomes the leader.
- In the fourth step child $ 6 $ is eliminated, child $ 7 $ becomes the leader.
- In the final step child $ 1 $ is eliminated, child $ 3 $ becomes the leader.

## 样例 #1

### 输入

```
7 5
10 4 11 4 1
```

### 输出

```
4 2 5 6 1 
```

## 样例 #2

### 输入

```
3 2
2 5
```

### 输出

```
3 2 
```

# AI分析结果

### 题目翻译
# 报数游戏

## 题目描述
有 $n$ 个孩子站成一个圆圈玩报数游戏。孩子们按顺时针方向从 $1$ 到 $n$ 编号。游戏开始时，第一个孩子被视为领导者。游戏分 $k$ 步进行。在第 $i$ 步中，领导者从下一个人开始按顺时针方向数出 $a_{i}$ 个人。最后被领导者指到的人被淘汰，他的下一个玩家成为新的领导者。

例如，如果当前圆圈中的孩子编号为 $[8,10,13,14,16]$，领导者是编号为 $13$ 的孩子，且 $a_{i}=12$，那么报数结束时编号为 $16$ 的孩子被淘汰，编号为 $8$ 的孩子成为领导者。

你需要编写一个程序，输出每一步被淘汰的孩子的编号。

## 说明/提示
让我们考虑第一个样例：
- 在第一步中，编号为 $4$ 的孩子被淘汰，编号为 $5$ 的孩子成为领导者。
- 在第二步中，编号为 $2$ 的孩子被淘汰，编号为 $3$ 的孩子成为领导者。
- 在第三步中，编号为 $5$ 的孩子被淘汰，编号为 $6$ 的孩子成为领导者。
- 在第四步中，编号为 $6$ 的孩子被淘汰，编号为 $7$ 的孩子成为领导者。
- 在最后一步中，编号为 $1$ 的孩子被淘汰，编号为 $3$ 的孩子成为领导者。

## 样例 #1
### 输入
```
7 5
10 4 11 4 1
```
### 输出
```
4 2 5 6 1 
```

## 样例 #2
### 输入
```
3 2
2 5
```
### 输出
```
3 2 
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟报数游戏的过程，找出每一步被淘汰的孩子。不同题解主要在数据结构的选择上有所不同，常见的数据结构有 `vector`、`queue`、`deque`、`set` 等。解决的难点在于处理较大的 $a_i$ 值（范围为 $1 \leq a_i \leq 10^9$），需要通过取模运算避免不必要的循环，提高效率。

### 高评分题解
- **Alex_Wei（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `vector` 模拟游戏过程，对取模运算的处理解释详细。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector <int> s;
int n,k,a,p;
int main()
{
    cin>>n>>k;
    for(int x=1;x<=n;x++)s.push_back(x);
    while(k--){
        cin>>a,p=(p+a)%s.size();
        cout<<s[p]<<" ",s.erase(s.begin()+p);
    }
    return 0;
}
```
    - **核心实现思想**：先将孩子编号依次存入 `vector` 中，每次读入报数步数 $a$，计算出要删除的位置 $p$（通过取模保证位置合法），输出该位置的孩子编号并删除，更新 `vector`。

- **Sternenlicht（4星）**
    - **关键亮点**：使用自定义的输入输出函数，提高输入输出效率，对模拟过程的步骤描述清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define LL long long
namespace IO{
    // 自定义输入输出函数
}
using namespace IO;
using namespace std;

vector<int> ve;
int main(){
    int n=read(),k=read(),pos=0;
    for (int i=1;i<=n;i++)ve.push_back(i);
    for (int i=1;i<=k;i++){
        int x=read();
        pos=(pos+x)%ve.size();
        write(ve[pos],' ');
        ve.erase(ve.begin()+pos);
    }
    return 0;
}
```
    - **核心实现思想**：与 Alex_Wei 的思路类似，利用 `vector` 模拟，通过取模确定要删除的位置，输出并删除该位置的元素。

- **kirky_wang（4星）**
    - **关键亮点**：提供了普通数组和 `deque` 两种实现方式，对 `deque` 的使用进行了详细解释。
    - **核心代码（deque 版本）**：
```cpp
#include<iostream>
#include<deque>
using namespace std;
deque<int> a;
int n,k;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    { 
        a.push_back(i);
    }
    for(int i=0;i<k;i++)
    {        
        int s;
        cin>>s;
        s%=a.size();
        while(s--)
        {
            a.push_back(a.front());
            a.pop_front(); 
        }
        int val=a.front();
        a.pop_front();
        cout<<val<<" ";
    }
    return 0;
}
```
    - **核心实现思想**：使用 `deque` 模拟圆圈，每次读入报数步数 $s$，通过取模避免不必要的循环，将队首元素移到队尾 $s$ 次，最后弹出队首元素（即被淘汰的孩子）并输出。

### 关键思路或技巧
- **取模运算**：由于 $a_i$ 可能达到 $10^9$，直接模拟会超时，通过对当前剩余孩子数量取模，可以避免不必要的循环，提高效率。
- **数据结构的选择**：`vector` 方便随机访问和删除元素；`queue` 和 `deque` 可以方便地实现元素的移动和删除；`set` 可以用于标记已淘汰的孩子。

### 拓展思路
同类型题或类似算法套路通常涉及对环形结构的模拟，如约瑟夫环问题。解题的关键在于合理使用数据结构和取模运算来处理循环和删除操作。

### 推荐题目
- [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)
- [P2872 [USACO07DEC]Building Roads S](https://www.luogu.com.cn/problem/P2872)
- [P1548 [NOIP1997 普及组] 棋盘问题](https://www.luogu.com.cn/problem/P1548)

### 个人心得
- **oimaster**：自己 WA 了不少次，结果居然是低级错误。做这类题需要有熟练的代码能力、复杂度分析能力、调试代码能力和 STL 基本运用能力。 总结：在解题过程中要注意细节，避免低级错误，同时要注重自身编程能力的提升。

---
处理用时：44.84秒