# 题目信息

# And Matching

## 题目描述

You are given a set of $ n $ ( $ n $ is always a power of $ 2 $ ) elements containing all integers $ 0, 1, 2, \ldots, n-1 $ exactly once.

Find $ \frac{n}{2} $ pairs of elements such that:

- Each element in the set is in exactly one pair.
- The sum over all pairs of the [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) of its elements must be exactly equal to $ k $ . Formally, if $ a_i $ and $ b_i $ are the elements of the $ i $ -th pair, then the following must hold: $ $$$\sum_{i=1}^{n/2}{a_i \& b_i} = k, $ $  where  $ \\&amp; $  denotes the bitwise AND operation. </li></ul><p>If there are many solutions, print any of them, if there is no solution, print  $ -1$$$ instead.

## 说明/提示

In the first test, $ (0\&3)+(1\&2) = 0 $ .

In the second test, $ (0\&2)+(1\&3) = 1 $ .

In the third test, $ (0\&1)+(2\&3) = 2 $ .

In the fourth test, there is no solution.

## 样例 #1

### 输入

```
4
4 0
4 1
4 2
4 3```

### 输出

```
0 3
1 2
0 2
1 3
0 1
2 3
-1```

# AI分析结果

### 题目翻译
#### And匹配

#### 题目描述
给定一个包含 $n$ 个元素的集合（$n$ 始终是 $2$ 的幂），该集合恰好包含所有整数 $0, 1, 2, \ldots, n - 1$ 各一次。

找出 $\frac{n}{2}$ 对元素，使得：
- 集合中的每个元素恰好位于一对中。
- 所有元素对按位与（`&`）的和必须恰好等于 $k$。形式上，如果 $a_i$ 和 $b_i$ 是第 $i$ 对的元素，那么必须满足：$\sum_{i = 1}^{n/2} {a_i \& b_i} = k$，其中 `&` 表示按位与运算。

如果有多种解决方案，输出其中任意一种；如果没有解决方案，则输出 $-1$。

#### 说明/提示
在第一个测试中，$(0 \& 3) + (1 \& 2) = 0$。
在第二个测试中，$(0 \& 2) + (1 \& 3) = 1$。
在第三个测试中，$(0 \& 1) + (2 \& 3) = 2$。
在第四个测试中，没有解决方案。

#### 样例 #1
##### 输入
```
4
4 0
4 1
4 2
4 3
```
##### 输出
```
0 3
1 2
0 2
1 3
0 1
2 3
-1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是利用位运算的性质来构造满足条件的数对。大部分题解都先分析了位运算的几个关键性质，如 `i & (n - i - 1) = 0`、`(n - 1) & k = k`、`0 & p = 0` 等，然后根据 $k$ 的不同取值进行分类讨论来构造数对。
- **思路对比**：多数题解的分类讨论思路一致，即分为 $k < n - 1$ 和 $k = n - 1$ 两种情况，部分题解还单独讨论了 $k = 0$ 的情况。对于 $k < n - 1$ 的情况，一般是将 $k$ 与 $n - 1$ 配对得到 $k$，再处理其他数对使其按位与结果为 $0$；对于 $k = n - 1$ 的情况，通常是将 $n - 1$ 与 $n - 2$ 配对、$1$ 与 $n - 3$ 配对等，同时注意 $n = 4$ 且 $k = 3$ 时无解。
- **算法要点**：利用位运算性质构造数对，通过分类讨论不同的 $k$ 值来确定具体的构造方法。
- **解决难点**：主要难点在于找到合适的数对构造方式，使得按位与的和等于 $k$，同时要注意特殊情况（如 $n = 4$ 且 $k = 3$）的处理。

### 所选题解
- **8atemak1r（5星）**
    - **关键亮点**：思路清晰，详细证明了位运算的性质，并结合表格直观地展示了 $k = n - 1$ 时的构造过程，代码简洁易懂。
    - **个人心得**：无
- **IvanZhang2009（4星）**
    - **关键亮点**：对每种情况的构造过程解释详细，逻辑清晰，代码简洁明了。
    - **个人心得**：提到很多大佬比赛时看到样例 $n = 4, k = 3$ 无解，就认为 $k = n - 1$ 时都无解，提醒要避免这种错误思维。
- **Morgen_Kornblume（4星）**
    - **关键亮点**：提出可以通过打暴力找可行解的思路，然后利用位运算性质进行构造，代码实现较为简洁。
    - **个人心得**：强调只要理论扎实，代码就能通过，遇到构造题可以打暴力找思路。

### 重点代码
#### 8atemak1r 的代码
```cpp
#include<iostream>
using namespace std;
int t, n, k;
int main() {
    cin >> t;
    while(t --) {
        cin >> n >> k;
        if(k == n - 1) {
            if(k <= 4) {
                cout << "-1\n";
                continue;
            }
            cout << 1 << ' ' << n - 3 << '\n';
            cout << n - 1 << ' ' << n - 2 << '\n';
            cout << "0 2\n";
            for(int i = 3; i < (n >> 1); ++ i) cout << i << ' ' << n - i - 1 << '\n';
            continue;
        }
        cout << k << ' ' << n - 1 << '\n';
        if(k != 0) cout << "0 " << n - k - 1 << '\n';
        for(int i = 1; i < (n >> 1); ++ i) {
            if(i == k || i == n - k - 1) continue;
            cout << i << ' ' << n - i - 1 << '\n';
        }
    }
    return 0;
}
```
**核心实现思想**：先读取输入的 $t$ 组数据，对于每组数据，根据 $k$ 的值进行分类讨论。当 $k = n - 1$ 且 $k \leq 4$ 时输出 $-1$，否则按特定方式构造数对；当 $k < n - 1$ 时，将 $k$ 与 $n - 1$ 配对，$0$ 与 $n - k - 1$ 配对，其他数按 `i` 与 `n - i - 1` 配对。

#### IvanZhang2009 的代码
```cpp
int n,k;
cin>>n>>k;
if(!k){
    REP(i,0,n/2)
    cout<<i<<' '<<n-1-i<<endl;
    return;
}
if(k&&k<n-1){
    cout<<0<<' '<<n-1-k<<endl;
    cout<<n-1<<' '<<k<<endl;
    REP(i,1,n/2)
    if(i!=k&&i!=n-1-k)cout<<i<<' '<<n-1-i<<endl;
}
if(k==n-1){
    if(n==4)cout<<-1<<endl;
    else{
        cout<<0<<' '<<2<<endl;
        cout<<n-1<<' '<<n-2<<endl;
        cout<<n-3<<' '<<1<<endl;
        REP(i,3,n/2)cout<<i<<' '<<n-1-i<<endl;
    }
}
```
**核心实现思想**：根据 $k$ 的值进行分类讨论。当 $k = 0$ 时，直接按 `i` 与 `n - 1 - i` 配对；当 $0 < k < n - 1$ 时，将 $k$ 与 $n - 1$ 配对，$0$ 与 $n - 1 - k$ 配对，其他数按 `i` 与 `n - 1 - i` 配对；当 $k = n - 1$ 且 $n = 4$ 时输出 $-1$，否则按特定方式构造数对。

#### Morgen_Kornblume 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,k; 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(n==4&&k==3){
            cout<<-1<<endl;	
            continue;
        }
        if(k==n-1){
            cout<<n-1<<" "<<n-2<<endl;
            cout<<1<<" "<<n-3<<endl;
            cout<<0<<" "<<((n-3)^(n-1))<<endl;
            for(int i=3;i<n/2;i++){
                cout<<i<<" "<<((n-1)^i)<<endl;
            }
        }
        else{
            cout<<n-1<<" "<<k<<endl;
            if(k!=0)cout<<0<<" "<<((n-1)^k)<<endl;
            for(int i=1;i<n/2;i++){
                if(i==k||i==((n-1)^k))continue;
                cout<<i<<" "<<((n-1)^i)<<endl;
            }
        }
    }
    return 0;
}
```
**核心实现思想**：先读取 $T$ 组数据，对于每组数据，当 $n = 4$ 且 $k = 3$ 时输出 $-1$。当 $k = n - 1$ 时，按特定方式构造数对；当 $k < n - 1$ 时，将 $k$ 与 $n - 1$ 配对，$0$ 与 `(n - 1) ^ k` 配对，其他数按 `i` 与 `(n - 1) ^ i` 配对。

### 最优关键思路或技巧
- **利用位运算性质**：如 `i & (n - i - 1) = 0`、`(n - 1) & k = k` 等，这些性质是构造数对的关键。
- **分类讨论**：根据 $k$ 的不同取值进行分类讨论，分别构造满足条件的数对。

### 可拓展之处
同类型题可能会改变数对的运算规则或增加其他限制条件，但核心思路仍然是利用相关运算的性质进行构造。类似算法套路可以应用于其他需要构造特定结果的题目，通过分析问题的性质，找到合适的构造方法。

### 推荐洛谷题目
- P1100 高低位交换：考察位运算的基本操作。
- P1886 滑动窗口 /【模板】单调队列：涉及队列和模拟的思想。
- P2114 [NOI2014] 起床困难综合症：综合考察位运算和贪心思想。

---
处理用时：59.86秒