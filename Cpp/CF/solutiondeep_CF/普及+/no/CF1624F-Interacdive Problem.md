# 题目信息

# Interacdive Problem

## 题目描述

This problem is interactive.

We decided to play a game with you and guess the number $ x $ ( $ 1 \le x < n $ ), where you know the number $ n $ .

You can make queries like this:

- + c: this command assigns $ x = x + c $ ( $ 1 \le c < n $ ) and then returns you the value $ \lfloor\frac{x}{n}\rfloor $ ( $ x $ divide by $ n $ and round down).

You win if you guess the current number with no more than $ 10 $ queries.

## 说明/提示

In the first sample initially $ x = 2 $ . After the first query $ x = 3 $ , $ \lfloor\frac{x}{n}\rfloor = 1 $ .

In the second sample also initially $ x = 2 $ . After the first query $ x = 3 $ , $ \lfloor\frac{x}{n}\rfloor = 0 $ . After the second query $ x = 4 $ , $ \lfloor\frac{x}{n}\rfloor = 0 $ . After the third query $ x=5 $ , $ \lfloor\frac{x}{n}\rfloor = 1 $ .

## 样例 #1

### 输入

```
3

1```

### 输出

```
+ 1

! 3```

## 样例 #2

### 输入

```
5

0

0

1```

### 输出

```
+ 1

+ 1

+ 1

! 5```

## 样例 #3

### 输入

```
10

0

0

1

2```

### 输出

```
+ 2

+ 2

+ 3

+ 8

! 20```

# AI分析结果

### 题目内容中文重写
# 交互问题

## 题目描述
这是一道交互题。

我们决定和你玩一个游戏，猜测数字 $x$（$1 \le x < n$），你知道数字 $n$。

你可以进行如下查询：
- + c：此命令将 $x$ 更新为 $x + c$（$1 \le c < n$），然后返回 $\lfloor\frac{x}{n}\rfloor$（$x$ 除以 $n$ 并向下取整）的值。

如果你在不超过 10 次查询内猜出当前数字，你就获胜。

## 说明/提示
在第一个样例中，初始时 $x = 2$。第一次查询后，$x = 3$，$\lfloor\frac{x}{n}\rfloor = 1$。

在第二个样例中，同样初始时 $x = 2$。第一次查询后，$x = 3$，$\lfloor\frac{x}{n}\rfloor = 0$。第二次查询后，$x = 4$，$\lfloor\frac{x}{n}\rfloor = 0$。第三次查询后，$x = 5$，$\lfloor\frac{x}{n}\rfloor = 1$。

## 样例 #1
### 输入
```
3
1
```
### 输出
```
+ 1
! 3
```

## 样例 #2
### 输入
```
5
0
0
1
```
### 输出
```
+ 1
+ 1
+ 1
! 5
```

## 样例 #3
### 输入
```
10
0
0
1
2
```
### 输出
```
+ 2
+ 2
+ 3
+ 8
! 20
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路均为二分查找。由于 $n$ 的范围较小（$2 < n \leq 1000$），$2^{10}=1024$，所以可以通过不超过 10 次询问来猜出数字。

- **思路对比**：大部分题解先考虑简化情况，即 `+ c` 不改变 $x$ 值，返回 $\lfloor\frac{x+c}{n}\rfloor$ 时如何二分。然后再处理 $x$ 实际变化的情况，通过记录增加的值 $sum$ 或 $tot$ 等，调整二分的判断条件。
- **算法要点**：二分查找的左右边界通常初始化为 $1$ 和 $n$，每次取中点 $mid$，计算要加的数 $c$，通过判断返回值与 $\lfloor\frac{mid + sum + c}{n}\rfloor$ 或 $\lfloor\frac{l + c}{n}\rfloor$ 等的关系来缩小范围。
- **解决难点**：主要难点在于处理 $x$ 不断变化的情况。不同题解采用不同方法，如记录增加的值，根据返回值的变化来判断 $x$ 与 $mid$ 的关系。

### 所选题解
- **AFewSuns（5星）**
    - **关键亮点**：思路清晰，详细分析了简化情况和原题的处理方法，代码注释详细。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define fl fflush(stdout)//记得清空缓存 
using namespace std;
ll n,sum=0;
int main(){
    scanf("%lld",&n);
    ll l=1,r=n;
    while(l<r){
        ll mid=(l+r+1)>>1,c=(10000*n-mid-sum)%n,tmp;//确定 c=(-mid-sum) mod n 
        printf("+ %lld\n",c);
        fl;
        scanf("%lld",&tmp);
        if(tmp==(mid+sum+c)/n) l=mid;//如果相等，那么x0>=mid 
        else r=mid-1;
        sum+=c;
    }
    printf("! %lld",l+sum);//记得要加上sum 
    fl;
    return 0;
}
```
核心实现思想：通过二分查找，每次计算 $c=(-mid - sum) \bmod n$，根据返回值判断 $x$ 与 $mid$ 的关系，更新左右边界，同时记录增加的值 $sum$，最后输出 $l + sum$ 作为结果。

- **清烛（4星）**
    - **关键亮点**：思路简洁，直接说明通过对二分左右端点同时加上 $c$ 来处理 $x$ 的变化。
    - **重点代码**：
```cpp
int add(int x) {
    cout << "+ " << x << endl;
    int res; cin >> res;
    return res;
}

int main() {
    int n; cin >> n;
    int l = 1, r = n;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        int a = n - mid % n;
        int res = add(a);
        l += a, r += a, mid += a;
        if (res == l / n) r = mid;
        else l = mid; 
    }
    cout << "! " << l << endl;
    return 0;
}
```
核心实现思想：定义 `add` 函数进行询问，每次二分取中点 $mid$，计算 $a = n - mid \bmod n$，根据返回值更新左右边界，最后输出 $l$ 作为结果。

- **rui_er（4星）**
    - **关键亮点**：思路清晰，详细说明了如何利用余数和商的变化来二分。
    - **重点代码**：
```cpp
int ask(int x) {
    printf("+ %d\n", x);
    fflush(stdout);
    scanf("%d", &x);
    return x;
}
void give(int x) {
    printf("! %d\n", x);
    fflush(stdout);
}

int main() {
    scanf("%d", &n);
    int L = 1, R = n;
    while(L + 1 < R) {
        int M = (L + R) >> 1;
        int diff = n - M % n;
        if(ask(diff) == (L + diff) / n) R = M;
        else L = M;
        L += diff; R += diff;
    }
    give(L);
    return 0;
}
```
核心实现思想：定义 `ask` 函数进行询问，`give` 函数输出结果。每次二分取中点 $M$，计算 $diff = n - M \bmod n$，根据返回值更新左右边界，最后输出 $L$ 作为结果。

### 最优关键思路或技巧
- **二分思想**：利用二分查找的特性，每次将搜索范围缩小一半，结合题目中返回值的信息来判断数字的范围。
- **记录变化**：由于 $x$ 会不断变化，通过记录增加的值，调整二分的判断条件，从而正确判断 $x$ 与 $mid$ 的关系。

### 可拓展之处
同类型题或类似算法套路：其他交互题可能会有不同的询问方式和返回信息，但可以尝试用二分的思想来解决。例如，在一些猜数字游戏中，可能会有不同的规则，如返回数字与目标数字的大小关系等，都可以考虑使用二分查找来减少询问次数。

### 推荐洛谷题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)

### 个人心得摘录与总结
部分题解提到要注意交互题的特性，如清空缓存（`fflush(stdout)`），否则可能会导致程序出错。在处理 $x$ 变化的情况时，需要仔细分析返回值与二分判断条件的关系，避免出现逻辑错误。

---
处理用时：51.92秒