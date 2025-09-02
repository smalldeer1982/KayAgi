# 题目信息

# Rocket

## 题目描述

This is an interactive problem.

Natasha is going to fly to Mars. Finally, Natasha sat in the rocket. She flies, flies... but gets bored. She wishes to arrive to Mars already! So she decides to find something to occupy herself. She couldn't think of anything better to do than to calculate the distance to the red planet.

Let's define $ x $ as the distance to Mars. Unfortunately, Natasha does not know $ x $ . But it is known that $ 1 \le x \le m $ , where Natasha knows the number $ m $ . Besides, $ x $ and $ m $ are positive integers.

Natasha can ask the rocket questions. Every question is an integer $ y $ ( $ 1 \le y \le m $ ). The correct answer to the question is $ -1 $ , if $ x<y $ , $ 0 $ , if $ x=y $ , and $ 1 $ , if $ x>y $ . But the rocket is broken — it does not always answer correctly. Precisely: let the correct answer to the current question be equal to $ t $ , then, if the rocket answers this question correctly, then it will answer $ t $ , otherwise it will answer $ -t $ .

In addition, the rocket has a sequence $ p $ of length $ n $ . Each element of the sequence is either $ 0 $ or $ 1 $ . The rocket processes this sequence in the cyclic order, that is $ 1 $ -st element, $ 2 $ -nd, $ 3 $ -rd, $ \ldots $ , $ (n-1) $ -th, $ n $ -th, $ 1 $ -st, $ 2 $ -nd, $ 3 $ -rd, $ \ldots $ , $ (n-1) $ -th, $ n $ -th, $ \ldots $ . If the current element is $ 1 $ , the rocket answers correctly, if $ 0 $ — lies. Natasha doesn't know the sequence $ p $ , but she knows its length — $ n $ .

You can ask the rocket no more than $ 60 $ questions.

Help Natasha find the distance to Mars. Assume, that the distance to Mars does not change while Natasha is asking questions.

Your solution will not be accepted, if it does not receive an answer $ 0 $ from the rocket (even if the distance to Mars is uniquely determined by the already received rocket's answers).

## 说明/提示

In the example, hacking would look like this:

5 2 3

1 0

This means that the current distance to Mars is equal to $ 3 $ , Natasha knows that it does not exceed $ 5 $ , and the rocket answers in order: correctly, incorrectly, correctly, incorrectly ...

Really:

on the first query ( $ 1 $ ) the correct answer is $ 1 $ , the rocket answered correctly: $ 1 $ ;

on the second query ( $ 2 $ ) the correct answer is $ 1 $ , the rocket answered incorrectly: $ -1 $ ;

on the third query ( $ 4 $ ) the correct answer is $ -1 $ , the rocket answered correctly: $ -1 $ ;

on the fourth query ( $ 5 $ ) the correct answer is $ -1 $ , the rocket answered incorrectly: $ 1 $ ;

on the fifth query ( $ 3 $ ) the correct and incorrect answer is $ 0 $ .

## 样例 #1

### 输入

```
5 2
1
-1
-1
1
0
```

### 输出

```
1
2
4
5
3
```

# AI分析结果

### 题目内容
# Rocket

## 题目描述
这是一道交互题。

娜塔莎准备飞往火星。终于，娜塔莎坐上了火箭。她飞啊飞……但感到无聊了。她希望快点抵达火星！所以她决定找点事做。她想来想去，觉得计算与红色星球（火星）的距离是个不错的选择。

设 $x$ 为与火星的距离。不幸的是，娜塔莎不知道 $x$ 的值。但已知 $1 \leq x \leq m$，其中 $m$ 这个数娜塔莎是知道的。此外，$x$ 和 $m$ 都是正整数。

娜塔莎可以向火箭提问。每个问题是一个整数 $y$（$1 \leq y \leq m$）。对该问题的正确答案是：如果 $x < y$，则为 $-1$；如果 $x = y$，则为 $0$；如果 $x > y$，则为 $1$。但火箭出故障了——它并不总是给出正确答案。确切地说：设当前问题的正确答案为 $t$，那么，如果火箭正确回答这个问题，它将回答 $t$，否则它将回答 $-t$。

此外，火箭有一个长度为 $n$ 的序列 $p$。该序列的每个元素要么是 $0$ 要么是 $1$。火箭按循环顺序处理这个序列，即第 $1$ 个元素，第 $2$ 个，第 $3$ 个，$\ldots$，第 $(n - 1)$ 个，第 $n$ 个，第 $1$ 个，第 $2$ 个，第 $3$ 个，$\ldots$，第 $(n - 1)$ 个，第 $n$ 个，$\ldots$。如果当前元素是 $1$，火箭给出正确答案，如果是 $0$ 则说谎。娜塔莎不知道序列 $p$，但她知道它的长度 $n$。

你向火箭提问的次数不能超过 $60$ 次。

帮助娜塔莎找到与火星的距离。假设在娜塔莎提问期间，与火星的距离不会改变。

如果你的解决方案没有从火箭得到答案 $0$（即使根据已收到的火箭答案可以唯一确定与火星的距离），则该解决方案将不被接受。

## 说明/提示
在示例中，黑客攻击（hacking）的情况如下：

5 2 3

1 0

这意味着当前与火星的距离等于 $3$，娜塔莎知道它不超过 $5$，并且火箭按顺序回答：正确，错误，正确，错误 $\ldots$

实际情况：
- 对于第一个查询（$1$），正确答案是 $1$，火箭正确回答：$1$；
- 对于第二个查询（$2$），正确答案是 $1$，火箭错误回答：$-1$；
- 对于第三个查询（$4$），正确答案是 $-1$，火箭正确回答：$-1$；
- 对于第四个查询（$5$），正确答案是 $-1$，火箭错误回答：$1$；
- 对于第五个查询（$3$），正确答案和错误答案都是 $0$。

## 样例 #1
### 输入
```
5 2
1
-1
-1
1
0
```
### 输出
```
1
2
4
5
3
```

### 算法分类
二分

### 综合分析与结论
这几道题解思路基本一致，均利用二分查找来解决问题。由于 $1\leq x\leq 10^9$，二分查找最坏情况约需30次查询，而火箭回答的周期长度 $n\leq 30$，两者相加刚好满足不超过60次提问的限制。各题解的核心思路都是先通过询问 $n$ 次 $1$ 来确定火箭回答的正误序列，再基于此进行二分查找。不同之处主要体现在代码实现细节和风格上。

### 所选的题解
- **作者：沉石鱼惊旋（5星）**
    - **关键亮点**：思路清晰，代码简洁明了。先通过循环询问 $n$ 次 $1$ 确定火箭回答正误数组 $f$，之后在二分过程中根据 $f$ 判断回答是否正确，从而调整二分区间。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool f[50];
int main()
{
    int n, m, cnt = 0;
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        cout << 1 << endl;
        fflush(stdout);
        int x;
        cin >> x;
        if (x == -1)
            f[i] = 0;
        else if (x == 1)
            f[i] = 1;
        else
            return 0;
    }
    int mid, x, l = 2, r = m;
    while (l <= r)
    {
        cnt %= n;

        mid = (l + r) / 2;
        cout << mid << endl;
        fflush(stdout);
        cin >> x;
        if (f[cnt] == 0 && x == -1 || f[cnt] == 1 && x == 1)
            l = mid + 1;
        else if (f[cnt] == 0 && x == 1 || f[cnt] == 1 && x == -1)
            r = mid - 1;
        else if (x == -2 || x == 0)
            return 0;
        cnt++;
    }
    return 0;
}
```
    - **核心实现思想**：首先通过循环询问 $n$ 次 $1$，根据返回值确定 $f$ 数组，$f[i]$ 为 $1$ 表示第 $i$ 次回答正确，为 $0$ 表示错误。二分过程中，根据 $f[cnt]$ 和当前回答 $x$ 判断是否调整二分区间。
- **作者：小闸蟹（4星）**
    - **关键亮点**：代码结构清晰，将询问操作封装成函数 `Ask`，提高代码可读性和可维护性。同样先确定火箭回答正误序列，再二分查找。
    - **重点代码**：
```cpp
// 先求出整个p序列，再二分
#include <iostream>
#include <array>

int Ask(int p)
{
    std::cout << p << std::endl;
    std::fflush(stdout);

    int t;
    std::cin >> t;
    return t;
}     

int main()
{
    constexpr int MaxN = 30 + 5;
    std::array<bool, MaxN> p{ false };

    int m, n;
    std::cin >> m >> n;
    for (int i = 1; i <= n; ++i)    // 先询问n遍1，把p序列求出来，
    {                               // 因为1是最短的距离，所以不可能有-1出现，如果出现了-1，则证明这次是假的答案
        std::cout << 1 << std::endl;
        std::fflush(stdout);
        
        int t;
        std::cin >> t;
        if (t == -1)    // 出现了-1，则证明是假的答案
        {
            p[i] = false;
        }
        else if (t == 1)    // 返回1才对
        {
            p[i] = true;
        }
        else // 恰好1就是答案
        {
            return 0;
        }
    }

    int l = 2, r = m, Now = 1;
    while (l <= r)
    {
        auto m = (l + r) / 2;
        auto Ans = Ask(m);
        if (p[(Now - 1) % n + 1] == false)  // 如果这次火箭会返回假的答案，我们就给它取个反
        {
            Ans = -Ans;
        }
        if (Ans == 0)
        {
            return 0;
        }
        else if (Ans < 0)
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }

        ++Now;
    }

    return 0;
}
```
    - **核心实现思想**：`Ask` 函数封装询问操作。先通过循环询问 $n$ 次 $1$ 填充 `p` 数组，`p[i]` 表示第 $i$ 次回答是否正确。二分查找时，根据 `p` 数组判断回答是否正确，若错误则取反回答值，再据此调整二分区间。
- **作者：野生林登万（4星）**
    - **关键亮点**：不仅给出解题思路和代码，还分享了交互题的实用技巧，如将询问操作封装成函数，提高代码的可读性、可维护性和调试便利性。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define Akano 1
#define pure__Elysia 0
#define loves ^
using namespace std;
const int MAXN = 66;
int n,m,cnt;
inline int Get(int x){
	cout<<x<<endl;
	int ret = 0;
	cin>>ret;
	if(ret == 0)exit(0);
	if(ret == -2)exit(0);
	return ret;
}
bool f[MAXN];
int main(){
	cin>>m>>n;
	for(int i = 1;i <= n;i++){
		int res = Get(1);
		if(res == -1){
			f[i] = true;
		}else{
			f[i] = false;
		}
	}
	int l = 1,r = m+1;
	while(l < r){
		const int mid = (l + r) >> 1;
		int res = Get(mid);
		cnt++;
		if(cnt > n)cnt = 1;
		if(f[cnt])res = -res;
		if(res == -1){
			r = mid;
		}else{
			l = mid + 1;
		}
	}
	return not(Akano loves pure__Elysia);
}
```
    - **核心实现思想**：`Get` 函数封装询问操作。先通过循环询问 $n$ 次 $1$ 确定 `f` 数组，`f[i]` 表示第 $i$ 次回答是否正确。二分过程中，根据 `f[cnt]` 判断回答是否正确，若错误则取反回答值，再调整二分区间。

### 最优关键思路或技巧
利用二分查找的特性，结合题目中给出的询问次数限制和火箭回答周期限制，先通过询问固定值（如 $1$）确定火箭回答的正误序列，再基于此进行二分查找。同时，将询问操作封装成函数，可提高代码的可读性和可维护性，方便调试。

### 同类型题或类似算法套路拓展
此类题目属于带有干扰因素的二分查找交互题。类似套路是先分析干扰因素的规律或特性，利用一定次数的操作去确定干扰信息，然后在已知干扰信息的情况下，运用常规算法（如本题的二分查找）解决问题。

### 洛谷相似题目推荐
- [P2249 查找](https://www.luogu.com.cn/problem/P2249)：基础的二分查找题目，可巩固二分查找的基本实现。
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：通过二分查找合适的砍树高度，与本题思路类似，都是利用二分解决特定条件下的数值查找问题。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：同样是二分查找的应用，需要根据题目条件确定二分的范围和判断条件。 

---
处理用时：136.36秒