# 题目信息

# Laura and Operations

## 题目描述

Laura is a girl who does not like combinatorics. Nemanja will try to convince her otherwise.

Nemanja wrote some digits on the board. All of them are either $ 1 $ , $ 2 $ , or $ 3 $ . The number of digits $ 1 $ is $ a $ . The number of digits $ 2 $ is $ b $ and the number of digits $ 3 $ is $ c $ . He told Laura that in one operation she can do the following:

- Select two different digits and erase them from the board. After that, write the digit ( $ 1 $ , $ 2 $ , or $ 3 $ ) different from both erased digits.

For example, let the digits be $ 1 $ , $ 1 $ , $ 1 $ , $ 2 $ , $ 3 $ , $ 3 $ . She can choose digits $ 1 $ and $ 3 $ and erase them. Then the board will look like this $ 1 $ , $ 1 $ , $ 2 $ , $ 3 $ . After that, she has to write another digit $ 2 $ , so at the end of the operation, the board will look like $ 1 $ , $ 1 $ , $ 2 $ , $ 3 $ , $ 2 $ .

Nemanja asked her whether it was possible for only digits of one type to remain written on the board after some operations. If so, which digits can they be?

Laura was unable to solve this problem and asked you for help. As an award for helping her, she will convince Nemanja to give you some points.

## 说明/提示

In the first test case, Laura can remove digits $ 2 $ and $ 3 $ and write digit $ 1 $ . After that, the board will have $ 2 $ digits $ 1 $ . She can make it have only digits $ 2 $ or $ 3 $ left by performing a similar operation.

In the second test case, she can remove digits $ 1 $ and $ 3 $ and write a digit $ 2 $ . After performing that operation $ 2 $ times, the board will have only digits $ 2 $ left. It can be proven that there is no way to have only digits $ 1 $ or only digits $ 3 $ left.

In the third test case, there is a sequence of operations that leaves only digits $ 1 $ on the board. It can be proven that there is no way to have only digits $ 2 $ or only digits $ 3 $ left.

## 样例 #1

### 输入

```
3
1 1 1
2 3 2
82 47 59```

### 输出

```
1 1 1
0 1 0
1 0 0```

# AI分析结果

### 题目内容（中文重写）
# Laura 和操作

## 题目描述

Laura 是一个不喜欢组合数学的女孩。Nemanja 会试图说服她改变想法。

Nemanja 在黑板上写下了一些数字。这些数字要么是 1，要么是 2，要么是 3。数字 1 的个数是 a，数字 2 的个数是 b，数字 3 的个数是 c。他告诉 Laura，她可以进行如下操作：
- 选择两个不同的数字并从黑板上擦除它们。然后，写下一个与这两个擦除数字都不同的数字（1、2 或 3）。

例如，假设黑板上的数字是 1、1、1、2、3、3。她可以选择数字 1 和 3 并擦除它们。此时黑板上的数字变为 1、1、2、3。之后，她需要写下另一个数字 2，所以操作结束时，黑板上的数字为 1、1、2、3、2。

Nemanja 问她，经过若干次操作后，是否有可能使得黑板上只留下一种类型的数字。如果可以，那么可能留下的是哪些数字？

Laura 无法解决这个问题，于是向你求助。作为帮助她的奖励，她会说服 Nemanja 给你一些分数。

## 说明/提示
在第一个测试用例中，Laura 可以擦除数字 2 和 3 并写下数字 1。之后，黑板上会有 2 个数字 1。通过执行类似的操作，她可以使黑板上只留下数字 2 或 3。

在第二个测试用例中，她可以擦除数字 1 和 3 并写下数字 2。执行两次该操作后，黑板上将只留下数字 2。可以证明，无法使黑板上只留下数字 1 或只留下数字 3。

在第三个测试用例中，存在一系列操作可以使黑板上只留下数字 1。可以证明，无法使黑板上只留下数字 2 或只留下数字 3。

## 样例 #1
### 输入
```
3
1 1 1
2 3 2
82 47 59
```
### 输出
```
1 1 1
0 1 0
1 0 0
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是围绕数字数量的奇偶性来判断是否能通过操作使得最后只剩下一种数字。不同题解的表述和推导方式略有不同，但本质相同。
- **思路对比**：大部分题解通过分析操作对数字数量的影响，得出两个数字数量的奇偶性在操作过程中不变这一关键结论。部分题解通过具体的操作步骤演示来辅助理解，如先消除数量相同的两种数字，再处理剩余数字等。
- **算法要点**：主要是判断另外两个数字数量的奇偶性是否相同，若相同则可以通过操作使得最后只剩下第三种数字。
- **解决难点**：难点在于发现操作过程中数字数量奇偶性不变这一规律，以及理解如何通过奇偶性判断是否能达到只剩一种数字的结果。

### 题解评分
- __Floze3__：4星。思路清晰，直接点明数字数量之差的奇偶性不变这一关键规律，代码简洁明了。
- feiji_code：4星。通过具体例子解释思路，易于理解，代码实现简单直接。
- yuyc：4星。详细分析了不同操作对数字数量的影响，对思路的解释较为全面，代码规范。

### 所选题解
- __Floze3__（4星）：关键亮点是直接指出三个数字的数量之差的奇偶性在操作过程中不会改变，通过判断另外两个数的奇偶性是否相同来得出结果，思路简洁清晰。
- feiji_code（4星）：通过具体例子展示操作过程，帮助理解思路，直接判断另外两个数字数量和的奇偶性来确定是否能只剩下一种数字，代码实现简单易懂。
- yuyc（4星）：详细分析了各种操作情况，解释了为什么不会出现数字不够用的情况，对思路的解释很全面，代码规范。

### 重点代码
#### __Floze3__
```cpp
#include <bits/stdc++.h>
using namespace std;

int T, a, b, c;

int main(){
    cin >> T;
    while (T--){
        cin >> a >> b >> c;
        cout << (b % 2 == c % 2) << ' ' << (a % 2 == c % 2) << ' ' << (a % 2 == b % 2) << '\n';
    }
    return 0;
}
```
核心实现思想：通过判断另外两个数字的奇偶性是否相同来确定是否能只剩下第三种数字。

#### feiji_code
```cpp
#include<bits/stdc++.h>
using namespace std;
//主函数↓
int main(){
    ios::sync_with_stdio(0),cin.tie(NULL),cout.tie(NULL);//关闭输入输出流的同步
    int t;
    cin>>t;
    for(int i=1,a,b,c;i<=t;++i){
        cin>>a>>b>>c;
        if((b+c)%2==0) cout<<1<<' ';//判断奇偶性
        else cout<<0<<' ';
        if((a+c)%2==0) cout<<1<<' ';
        else cout<<0<<' ';
        if((a+b)%2==0) cout<<1<<'\n';
        else cout<<0<<'\n';
    }
    return 0;
}
```
核心实现思想：判断另外两个数字数量和的奇偶性，若为偶数则可以只剩下第三种数字。

#### yuyc
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 200005;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        int a,b,c;
        cin>>a>>b>>c;
        if((c & 1) == (b & 1)) cout<<1;
        else cout<<0;
        cout<<' ';
        if((a & 1) == (c & 1)) cout<<1;
        else cout<<0;
        cout<<' ';
        if((a & 1) == (b & 1)) cout<<1;
        else cout<<0;
        cout<<'\n';
    }	
    return 0;
}
```
核心实现思想：通过位运算判断两个数字的奇偶性是否相同，若相同则可以只剩下第三种数字。

### 最优关键思路或技巧
发现操作过程中两个数字数量的奇偶性不变这一规律，通过判断另外两个数字的奇偶性是否相同来确定是否能只剩下第三种数字。

### 拓展思路
同类型题可能会改变数字的种类或操作规则，但核心思路可能还是围绕数字的某种属性（如奇偶性、余数等）在操作过程中的不变性来判断最终结果。类似算法套路可以用于解决一些涉及状态变化和最终结果判断的问题。

### 推荐题目
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：涉及数学计算和高精度处理。
- [P1069 细胞分裂](https://www.luogu.com.cn/problem/P1069)：需要运用数学知识进行分析和计算。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：可以通过数学推导来解决问题。

### 个人心得
题解中未包含个人心得。

---
处理用时：42.63秒