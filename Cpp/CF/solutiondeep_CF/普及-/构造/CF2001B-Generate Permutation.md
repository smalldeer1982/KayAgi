# 题目信息

# Generate Permutation

## 题目描述

There is an integer sequence $ a $ of length $ n $ , where each element is initially $ -1 $ .

Misuki has two typewriters where the first one writes letters from left to right, with a pointer initially pointing to $ 1 $ , and another writes letters from right to left with a pointer initially pointing to $ n $ .

Misuki would choose one of the typewriters and use it to perform the following operations until $ a $ becomes a permutation of $ [1, 2, \ldots, n] $

- write number: write the minimum positive integer that isn't present in the array $ a $ to the element $ a_i $ , $ i $ is the position where the pointer points at. Such operation can be performed only when $ a_i = -1 $ .
- carriage return: return the pointer to its initial position (i.e. $ 1 $ for the first typewriter, $ n $ for the second)
- move pointer: move the pointer to the next position, let $ i $ be the position the pointer points at before this operation, if Misuki is using the first typewriter, $ i := i + 1 $ would happen, and $ i := i - 1 $ otherwise. Such operation can be performed only if after the operation, $ 1 \le i \le n $ holds.

Your task is to construct any permutation $ p $ of length $ n $ , such that the minimum number of carriage return operations needed to make $ a = p $ is the same no matter which typewriter Misuki is using.

## 说明/提示

In the first testcase, it's possible to make $ a = p = [1] $ using $ 0 $ carriage return operations.

In the second testcase, it is possible to make $ a = p = [1, 2] $ with the minimal number of carriage returns as follows:

If Misuki is using the first typewriter:

- Write number: write $ 1 $ to $ a_1 $ , $ a $ becomes $ [1, -1] $
- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 2 $ to $ a_2 $ , $ a $ becomes $ [1, 2] $

If Misuki is using the second typewriter:

- Move pointer: move the pointer to the next position. (i.e. $ 1 $ )
- Write number: write $ 1 $ to $ a_1 $ , $ a $ becomes $ [1, -1] $
- Carriage return: return the pointer to $ 2 $ .
- Write number: write $ 2 $ to $ a_2 $ , $ a $ becomes $ [1, 2] $

It can be proven that the minimum number of carriage returns needed to transform $ a $ into $ p $ when using the first typewriter is $ 0 $ and it is $ 1 $ when using the second one, so this permutation is not valid.

Similarly, $ p = [2, 1] $ is also not valid, so there is no solution for $ n = 2 $ .

In the third testcase, it is possibile to make $ a = p = [3, 1, 2] $ with $ 1 $ carriage return with both the first and the second typewriter. It can be proven that, for both typewriters, it is impossible to write $ p $ with $ 0 $ carriage returns.

With the first typewriter it is possible to:

- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 1 $ to $ a_2 $ , $ a $ becomes $ [-1, 1, -1] $
- Move pointer: move the pointer to the next position. (i.e. $ 3 $ )
- Write number: write $ 2 $ to $ a_3 $ , $ a $ becomes $ [-1, 1, 2] $
- Carriage return: return the pointer to $ 1 $ .
- Write number: write $ 3 $ to $ a_1 $ , $ a $ becomes $ [3,1,2] $

With the second typewriter it is possible to:

- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 1 $ to $ a_2 $ , $ a $ becomes $ [-1, 1, -1] $
- Carriage return: return the pointer to $ 3 $ .
- Write number: write $ 2 $ to $ a_3 $ , $ a $ becomes $ [-1, 1, 2] $
- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Move pointer: move the pointer to the next position. (i.e. $ 1 $ )
- Write number: write $ 3 $ to $ a_1 $ , $ a $ becomes $ [3, 1, 2] $

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
1
-1
3 1 2```

# AI分析结果

### 题目翻译
# 生成排列

## 题目描述
有一个长度为 $n$ 的整数序列 $a$，其中每个元素最初都为 $-1$。

美月有两台打字机，第一台从左到右书写，指针最初指向位置 $1$；另一台从右到左书写，指针最初指向位置 $n$。

美月会选择其中一台打字机，并执行以下操作，直到 $a$ 成为 $[1, 2, \ldots, n]$ 的一个排列：
- 写入数字：将数组 $a$ 中未出现过的最小正整数写入元素 $a_i$，其中 $i$ 是指针当前指向的位置。此操作仅当 $a_i = -1$ 时可以执行。
- 回车：将指针返回到其初始位置（即第一台打字机的指针回到 $1$，第二台打字机的指针回到 $n$）。
- 移动指针：将指针移动到下一个位置。设 $i$ 为操作前指针指向的位置，如果美月使用的是第一台打字机，则执行 $i := i + 1$；否则执行 $i := i - 1$。此操作仅当操作后 $1 \le i \le n$ 成立时可以执行。

你的任务是构造一个长度为 $n$ 的排列 $p$，使得无论美月使用哪台打字机，将 $a$ 变为 $p$ 所需的最小回车操作次数相同。

## 说明/提示
在第一个测试用例中，可以使用 $0$ 次回车操作使 $a = p = [1]$。

在第二个测试用例中，以下是使用最少回车次数使 $a = p = [1, 2]$ 的方法：
如果美月使用第一台打字机：
- 写入数字：将 $1$ 写入 $a_1$，$a$ 变为 $[1, -1]$。
- 移动指针：将指针移动到下一个位置（即 $2$）。
- 写入数字：将 $2$ 写入 $a_2$，$a$ 变为 $[1, 2]$。

如果美月使用第二台打字机：
- 移动指针：将指针移动到下一个位置（即 $1$）。
- 写入数字：将 $1$ 写入 $a_1$，$a$ 变为 $[1, -1]$。
- 回车：将指针返回到 $2$。
- 写入数字：将 $2$ 写入 $a_2$，$a$ 变为 $[1, 2]$。

可以证明，使用第一台打字机将 $a$ 转换为 $p$ 所需的最小回车次数为 $0$，而使用第二台打字机时为 $1$，因此这个排列是无效的。

同样，$p = [2, 1]$ 也是无效的，所以 $n = 2$ 时没有解。

在第三个测试用例中，可以使用 $1$ 次回车操作，用两台打字机都使 $a = p = [3, 1, 2]$。可以证明，对于两台打字机，都不可能用 $0$ 次回车操作写出 $p$。

使用第一台打字机的操作如下：
- 移动指针：将指针移动到下一个位置（即 $2$）。
- 写入数字：将 $1$ 写入 $a_2$，$a$ 变为 $[-1, 1, -1]$。
- 移动指针：将指针移动到下一个位置（即 $3$）。
- 写入数字：将 $2$ 写入 $a_3$，$a$ 变为 $[-1, 1, 2]$。
- 回车：将指针返回到 $1$。
- 写入数字：将 $3$ 写入 $a_1$，$a$ 变为 $[3, 1, 2]$。

使用第二台打字机的操作如下：
- 移动指针：将指针移动到下一个位置（即 $2$）。
- 写入数字：将 $1$ 写入 $a_2$，$a$ 变为 $[-1, 1, -1]$。
- 回车：将指针返回到 $3$。
- 写入数字：将 $2$ 写入 $a_3$，$a$ 变为 $[-1, 1, 2]$。
- 移动指针：将指针移动到下一个位置（即 $2$）。
- 移动指针：将指针移动到下一个位置（即 $1$）。
- 写入数字：将 $3$ 写入 $a_1$，$a$ 变为 $[3, 1, 2]$。

## 样例 #1
### 输入
```
3
1
2
3
```
### 输出
```
1
-1
3 1 2
```

### 综合分析与结论
- **思路总结**：大部分题解都先判断 $n$ 的奇偶性，当 $n$ 为偶数时，认为无法构造出满足条件的排列，输出 $-1$；当 $n$ 为奇数时，通过不同方式构造出一个排列，使得左右打字机达到最小回车次数相同。
- **算法要点**：对于奇数 $n$，常见的构造方式有从中间向两侧发散排列，如 $n,n - 2,\ldots,3,1,2,4,\ldots,n - 3,n - 1$；或者先放最大数，再正序和倒序放置部分数字。
- **解决难点**：关键在于理解回车操作的使用场景，以及如何构造排列使左右打字机的回车次数平衡。部分题解通过分析相邻数的顺序对和逆序对来解决这个问题。

### 所选题解
- **作者：Magallan_forever（5星）**
    - **关键亮点**：思路清晰，对回车操作的使用场景进行了详细分析，将问题转化为左右箭头数量相等的问题，易于理解。代码简洁明了。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        if(n&1){
            for(int i=n;i>=1;i-=2) printf("%d ",i);
            for(int i=2;i<n;i+=2) printf("%d ",i);
            putchar('\n');
        }
        else printf("-1\n");
    }
    return 0;
}
```
核心实现思想：当 $n$ 为奇数时，先从 $n$ 开始递减输出奇数，再从 $2$ 开始递增输出偶数；当 $n$ 为偶数时，输出 $-1$。

- **作者：Ryan_Adam（4星）**
    - **关键亮点**：分析过程详细，从简单情况逐步推导，代码结构清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N];
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        if (n % 2 == 0)
            cout << -1 << endl;
        else
        {
            int cnt = n, l = 1, r = n;
            while (l < r)
            {
                a[l] = cnt--;
                a[r] = cnt--;
                l++, r--; 
            }
            a[l] = cnt++;
            for (int i = 1; i <= n; i++)
                cout << a[i] << " ";
            cout << endl;
        }
    }
    return 0;
}
```
核心实现思想：使用双指针 $l$ 和 $r$ 从两端向中间填充数组，先放较大的数，最后处理中间位置。

- **作者：clx201022（4星）**
    - **关键亮点**：从逆序对和顺序对的角度分析问题，给出了严谨的推理过程。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,bucket_a[101],ans;
void solve()
{
    cin>>n;
    if(n%2==0)
    {cout<<-1<<endl;return;}
    for(int i=n;i>=1;i-=2)cout<<i<<' ';
    for(int i=2;i<n;i+=2)cout<<i<<' ';
    cout<<endl;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}
```
核心实现思想：与 Magallan_forever 的思路类似，根据 $n$ 的奇偶性输出结果，奇数时按特定顺序输出排列。

### 最优关键思路或技巧
- 先判断 $n$ 的奇偶性，简化问题。
- 对于奇数 $n$，从中间向两侧构造排列，保证左右打字机的回车次数平衡。
- 部分题解通过分析相邻数的顺序对和逆序对来理解和解决问题，提供了一种新的思维方式。

### 可拓展之处
同类型题可能会改变操作规则或增加约束条件，例如改变打字机的移动方式、增加更多的操作类型等。类似算法套路可以是先分析特殊情况，再通过构造法解决一般情况，同时可以从数学角度分析问题，如逆序对、顺序对等。

### 推荐题目
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：考察排列组合的构造和枚举。
- [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：需要构造满足特定条件的数，并进行筛选。
- [P1618 三连击（升级版）](https://www.luogu.com.cn/problem/P1618)：在 P1008 的基础上增加了一些约束条件，进一步考察排列组合的构造。

### 个人心得摘录与总结
- **作者：jubaoyi2011**：一开始对题目感到困惑，通过观察样例得出 $2$ 的倍数无解的结论，并通过分析样例逐步推导出奇数情况下的排列构造方法。总结：对于难题可以从简单的样例入手，逐步分析和推导结论。

---
处理用时：50.01秒