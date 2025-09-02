# 题目信息

# Road To Zero

## 题目描述

You are given two integers $ x $ and $ y $ . You can perform two types of operations:

1. Pay $ a $ dollars and increase or decrease any of these integers by $ 1 $ . For example, if $ x = 0 $ and $ y = 7 $ there are four possible outcomes after this operation: 
  - $ x = 0 $ , $ y = 6 $ ;
  - $ x = 0 $ , $ y = 8 $ ;
  - $ x = -1 $ , $ y = 7 $ ;
  - $ x = 1 $ , $ y = 7 $ .
2. Pay $ b $ dollars and increase or decrease both integers by $ 1 $ . For example, if $ x = 0 $ and $ y = 7 $ there are two possible outcomes after this operation: 
  - $ x =             -1 $ , $ y = 6 $ ;
  - $ x = 1 $ , $ y = 8 $ .

Your goal is to make both given integers equal zero simultaneously, i.e. $ x = y = 0 $ . There are no other requirements. In particular, it is possible to move from $ x=1 $ , $ y=0 $ to $ x=y=0 $ .

Calculate the minimum amount of dollars you have to spend on it.

## 说明/提示

In the first test case you can perform the following sequence of operations: first, second, first. This way you spend $ 391 + 555       + 391 = 1337 $ dollars.

In the second test case both integers are equal to zero initially, so you dont' have to spend money.

## 样例 #1

### 输入

```
2
1 3
391 555
0 0
9 4```

### 输出

```
1337
0```

# AI分析结果

### 题目内容
#### Road To Zero
1. **题目描述**：给定两个整数 \(x\) 和 \(y\) ，可以执行两种类型的操作：
    - 花费 \(a\) 美元，对这两个整数中的任意一个进行加 \(1\) 或减 \(1\) 操作。例如，若 \(x = 0\) 且 \(y = 7\) ，此操作后有四种可能结果：
        - \(x = 0\) ， \(y = 6\) ；
        - \(x = 0\) ， \(y = 8\) ；
        - \(x = -1\) ， \(y = 7\) ；
        - \(x = 1\) ， \(y = 7\) 。
    - 花费 \(b\) 美元，同时对两个整数进行加 \(1\) 或减 \(1\) 操作。例如，若 \(x = 0\) 且 \(y = 7\) ，此操作后有两种可能结果：
        - \(x = -1\) ， \(y = 6\) ；
        - \(x = 1\) ， \(y = 8\) 。
    目标是使这两个给定整数同时变为零，即 \(x = y = 0\) 。计算为此必须花费的最少美元数。
2. **说明/提示**：在第一个测试用例中，可以执行以下操作序列：先执行第一种操作，再执行第二种操作，最后再执行第一种操作。这样花费 \(391 + 555+ 391 = 1337\) 美元。在第二个测试用例中，两个整数初始时就都为零，所以无需花钱。
3. **样例 #1**
    - **输入**：
```
2
1 3
391 555
0 0
9 4
```
    - **输出**：
```
1337
0
```

### 算法分类
贪心

### 综合分析与结论
所有题解核心思路均为贪心策略，通过比较两种操作的代价，来决定如何使 \(x\) 和 \(y\) 变为 \(0\) 以达到最小花费。难点在于分析何时单独操作更优，何时同时操作更优。各题解思路基本一致，主要差异在代码实现细节与表述清晰度上。

### 所选的题解
- **作者：SpeedStar (5星)**
    - **关键亮点**：思路清晰简洁，直接通过比较 \(2a\) 与 \(b\) 的大小，得出两种不同情况下的最优操作方式及对应花费公式，代码简洁明了。
    - **重点代码**：
```cpp
#include <iostream>
#define int long long

using namespace std;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	while (t--) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		if (a + a <= b) cout << (x + y) * a << '\n';
		else cout << min(x, y) * b + abs(x - y) * a << '\n';
	}
	
	return 0;
}
```
    - **核心实现思想**：先读入测试用例数量 \(t\) ，对于每个测试用例，读入 \(x\) 、 \(y\) 、 \(a\) 、 \(b\) ，根据 \(2a\) 与 \(b\) 的大小关系，选择对应公式计算并输出最小花费。

- **作者：do_while_false (4星)**
    - **关键亮点**：思路表述清晰，先确保 \(x < y\) 方便分析，提出两种最优操作方式并计算代价，取最小值为答案，复杂度为 \(O(1)\) 。
    - **重点代码**：无（未提供代码，但思路清晰可依描述实现）
    - **核心实现思想**：若 \(x > y\) 则交换 \(x\) 、 \(y\) ，之后计算两种操作代价，一是用 \(b\) 代价将两数同时削直到 \(x\) 变为 \(0\) ，再用 \(a\) 代价削 \(y - x\) 次；二是全都单独削，取两者最小值。

- **作者：添哥 (4星)**
    - **关键亮点**：不仅给出解题思路，还强调了数据范围导致不开 \(long long\) 会溢出的易错点，代码实现完整且注释详细。
    - **重点代码**：
```cpp
#include<iostream>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--){
        long long x,y,a,b;
        cin>>x>>y>>a>>b;
        if(b>a*2){
            cout<<(x + y) * a <<endl;
        }
        else{
            if(x>y){
            	cout<<y*b+(x - y)*a<<endl;
			}
			else{
            	cout<<x*b+(y - x)*a<<endl;
			}
        }
    }
    return 0;
}
```
    - **核心实现思想**：读入测试用例数 \(t\) ，对每个用例读入 \(x\) 、 \(y\) 、 \(a\) 、 \(b\) ，根据 \(b\) 与 \(2a\) 的大小关系，分情况计算并输出最小花费，若 \(b > 2a\) ，直接输出 \((x + y) * a\) ，否则比较 \(x\) 与 \(y\) 大小后按公式输出。

### 最优关键思路或技巧
通过比较 \(2a\) 和 \(b\) 的大小关系进行贪心选择操作方式。当 \(2a \leq b\) 时，选择每次花费 \(a\) 对单个变量操作；当 \(2a > b\) 时，优先使用花费 \(b\) 的操作将较小值变为 \(0\) ，再用花费 \(a\) 的操作处理剩余差值。

### 可拓展之处
此类题目属于贪心策略应用，类似套路为分析不同操作的代价，根据代价关系选择最优操作序列。同类型题常围绕资源分配、代价最小化等场景展开。

### 洛谷推荐题目
1. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得摘录与总结
- **作者：添哥**：强调了由于 \(x\) ， \(y\) ， \(a\) ， \(b\) 上限为 \(10^9\) ，相乘可能导致 \(int\) 溢出，必须使用 \(long long\) 类型，这是容易忽略的易错点。 

---
处理用时：47.39秒