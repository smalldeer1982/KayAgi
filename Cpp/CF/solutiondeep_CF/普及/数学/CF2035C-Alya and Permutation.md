# 题目信息

# Alya and Permutation

## 题目描述

Alya has been given a hard problem. Unfortunately, she is too busy running for student council. Please solve this problem for her.

Given an integer $ n $ , construct a permutation $ p $ of integers $ 1, 2, \ldots, n $ that maximizes the value of $ k $ (which is initially $ 0 $ ) after the following process.

Perform $ n $ operations, on the $ i $ -th operation ( $ i=1, 2, \dots, n $ ),

- If $ i $ is odd, $ k=k\,\&\,p_i $ , where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).
- If $ i $ is even, $ k=k\,|\,p_i $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 说明/提示

For the first test case, the value of $ k $ is determined as follows:

 $ k = 0 $ initially.

- On the $ 1 $ st operation, $ 1 $ is odd, so Alya sets $ k $ to be $ k\&p_1 = 0\&2 = 0 $ .
- On the $ 2 $ nd operation, $ 2 $ is even, so Alya sets $ k $ to be $ k|p_2 = 0|1 = 1 $ .
- On the $ 3 $ rd operation, $ 3 $ is odd, so Alya sets $ k $ to be $ k\&p_3 = 1\&3 = 1 $ .
- On the $ 4 $ th operation, $ 4 $ is even, so Alya sets $ k $ to be $ k|p_4 = 1|4 = 5 $ .
- On the $ 5 $ th operation, $ 5 $ is odd, so Alya sets $ k $ to be $ k\&p_5 = 5\&5 = 5 $ .

The final value of $ k $ is $ 5 $ . It can be shown that the final value of $ k $ is at most $ 5 $ for all permutations of length $ 5 $ . Another valid output is $ [2, 3, 1, 4, 5] $ .

For the second test case, the final value of $ k $ is $ 7 $ . It can be shown that the final value of $ k $ is at most $ 7 $ for all permutations of length $ 6 $ . Other valid outputs include $ [2, 4, 1, 6, 3, 5] $ and $ [5, 2, 6, 1, 3, 4] $ .

## 样例 #1

### 输入

```
6
5
6
7
8
9
10```

### 输出

```
5
2 1 3 4 5 
7
1 2 4 6 5 3 
7
2 4 5 1 3 6 7 
15
2 4 5 1 3 6 7 8 
9
2 4 5 6 7 1 3 8 9 
15
1 2 3 4 5 6 8 10 9 7```

# AI分析结果

### 题目内容重写

**Alya和排列**

**题目描述**

Alya被赋予了一个难题。不幸的是，她正忙于竞选学生会，因此请你帮她解决这个问题。

给定一个整数 $n$，构造一个整数 $1, 2, \ldots, n$ 的排列 $p$，使得在执行以下操作后，变量 $k$（初始值为 $0$）的值最大化。

执行 $n$ 次操作，第 $i$ 次操作（$i=1, 2, \dots, n$）如下：

- 如果 $i$ 是奇数，$k = k\,\&\,p_i$，其中 $\&$ 表示按位与操作。
- 如果 $i$ 是偶数，$k = k\,|\,p_i$，其中 $|$ 表示按位或操作。

**说明/提示**

对于第一个测试用例，$k$ 的值按如下方式确定：

$k = 0$ 初始值。

- 第 $1$ 次操作，$1$ 是奇数，所以 Alya 将 $k$ 设为 $k\&p_1 = 0\&2 = 0$。
- 第 $2$ 次操作，$2$ 是偶数，所以 Alya 将 $k$ 设为 $k|p_2 = 0|1 = 1$。
- 第 $3$ 次操作，$3$ 是奇数，所以 Alya 将 $k$ 设为 $k\&p_3 = 1\&3 = 1$。
- 第 $4$ 次操作，$4$ 是偶数，所以 Alya 将 $k$ 设为 $k|p_4 = 1|4 = 5$。
- 第 $5$ 次操作，$5$ 是奇数，所以 Alya 将 $k$ 设为 $k\&p_5 = 5\&5 = 5$。

$k$ 的最终值为 $5$。可以证明，对于所有长度为 $5$ 的排列，$k$ 的最终值最多为 $5$。另一个有效的输出是 $[2, 3, 1, 4, 5]$。

对于第二个测试用例，$k$ 的最终值为 $7$。可以证明，对于所有长度为 $6$ 的排列，$k$ 的最终值最多为 $7$。其他有效的输出包括 $[2, 4, 1, 6, 3, 5]$ 和 $[5, 2, 6, 1, 3, 4]$。

### 题解分析与结论

通过对多条题解的分析，可以发现这些题解的核心思路都是基于对 $n$ 的奇偶性进行分类讨论，并通过构造特定的排列来最大化 $k$ 的值。以下是各题解的要点总结：

1. **Sakura_Emilia** 的题解通过打表观察得出结论，并提出了“隔断器”的概念，通过特定的排列构造来保证 $k$ 的最大值。代码实现较为简洁，但需要对 $n$ 的特殊情况进行特判。
2. **K_J_M** 的题解通过分析 $n$ 的奇偶性，提出了不同的排列构造策略，并对 $n$ 为偶数且为 $2$ 的幂的情况进行了特殊处理。代码实现较为清晰，但逻辑较为复杂。
3. **liugh_** 的题解同样基于 $n$ 的奇偶性进行分类讨论，并提出了不同的排列构造策略。代码实现较为简洁，但需要对 $n$ 的特殊情况进行特判。

### 精选题解

#### 题解1：Sakura_Emilia (4星)

**关键亮点：**
- 提出了“隔断器”的概念，通过特定的排列构造来保证 $k$ 的最大值。
- 代码实现简洁，逻辑清晰。

**核心代码：**
```cpp
inline void solve() {
    cin >> n;
    if(n == 6) {
        cout << "7\n1 2 4 6 5 3\n";
    } else if(n % 2 == 1) {
        cout << n << endl << 2 << ' ';
        for(int i = 4; i <= n - 2; i++)
            cout << i << ' ';
        cout << "3 1 " << n - 1 << ' ' << n << endl;
    } else {
        int num = __lg(n);
        cout << (int) pow(2, num + 1) - 1 << endl << 2 << ' ';
        int a = (int) pow(2, num) - 1;
        for(int i = 4; i <= n - 1; i++)
            if(i != a and i != a - 1)
                cout << i << ' ';
        cout << "3 1 " << a - 1 << ' ' << a << ' ' << n << endl;
    }
}
```

#### 题解2：K_J_M (4星)

**关键亮点：**
- 通过分析 $n$ 的奇偶性，提出了不同的排列构造策略。
- 对 $n$ 为偶数且为 $2$ 的幂的情况进行了特殊处理。

**核心代码：**
```cpp
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        if(n&1){
            cout<<n<<endl;
            for(int i=1;i<=n-4;++i) cout<<i+1<<" ";
            cout<<1<<" "<<n-2<<" "<<n-1<<" "<<n<<endl;
        }else{
            int k=log2(n);
            cout<<int(pow(2,k+1))-1<<endl;
            if(int(pow(2,k))==n){
                for(int i=1;i<=n-5;++i) cout<<i+1<<" ";
                cout<<1<<" "<<n-3<<" "<<n-2<<" "<<n-1<<" "<<n<<endl;;
            }else{
                for(int i=1;i<=int(pow(2,k))-2;++i) cout<<i<<" ";
                for(int i=int(pow(2,k));i<=n-2;++i) cout<<i<<" ";
                cout<<n<<" "<<n-1<<" "<<int(pow(2,k))-1<<endl;
            }
        }
    }
    return 0;
}
```

### 最优关键思路与技巧

1. **分类讨论**：根据 $n$ 的奇偶性进行分类讨论，分别构造不同的排列策略。
2. **隔断器**：通过特定的排列构造，确保在某个位置后 $k$ 的值不再受前面操作的影响。
3. **特殊处理**：对 $n$ 为偶数且为 $2$ 的幂的情况进行特殊处理，确保 $k$ 的最大值。

### 可拓展之处

类似的问题可以通过分类讨论和构造特定的排列来解决，尤其是在涉及位运算和排列组合的题目中。例如，可以通过分析二进制位来优化排列构造，或者通过打表观察来发现规律。

### 推荐题目

1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1013 进制位](https://www.luogu.com.cn/problem/P1013)

---
处理用时：55.05秒