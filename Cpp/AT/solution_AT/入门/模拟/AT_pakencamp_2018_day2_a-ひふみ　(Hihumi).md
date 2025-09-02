# ひふみ　(Hihumi)

## 样例 #1

### 输入

```
10```

### 输出

```
10```

## 样例 #2

### 输入

```
124```

### 输出

```
123```

## 样例 #3

### 输入

```
1000```

### 输出

```
999```

# 题解

## 作者：hjl2011 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_pakencamp_2018_day2_a)

## 题意简述

- 给定一个数 $N$。
- 有一个人要从 $1$ 数到 $N$，但他会把 $123$ 这个数跳过去，请问他数了几个数。
- $1 \le N \le 1000$ 且 $n \ne 123$。

## 题目分析

### 做法 1

其实就是求 $1$ 到 $N$ 除了 $123$ 有几个数。分情况讨论即可。

如果 $N < 123$，那么也就是 $1$ 到 $N$ 中没有 $123$，直接输出 $N$。  
如果 $N > 123$，那么也就是 $1$ 到 $N$ 中包含 $123$，需要输出 $N - 1$。

（题目保证了不存在 $N = 123$ 的情况，所以无需讨论。）

### 做法 2

模拟一下数数的过程即可：
- 如果当前的数是 $123$，那么就跳过。
- 否则累计一下这是第几个数。

## 代码

### 做法 1

```cpp
#include <cstdio>

using namespace std;

int main() {
    int n;
    scanf("%d",&n);
    if(n < 123) printf("%d",n); // 数不到 123，所以输出 n 就行。
    else printf("%d",n - 1); // 123 被跳过，所以输出 n - 1 即可。
    return 0;
}
```

### 做法 2

```cpp
#include <cstdio>

using namespace std;

int main() {
    int n;
    scanf("%d",&n);
    int cnt = 0; // 这个变量用来计数。
    for(int i = 1;i <= n;i++) { // 从 1 数到 n。
        if(i == 123) continue; // 数到 123 了，跳过。
        cnt++; // 累计一下。
    }
    printf("%d",cnt); // 别忘记输出。
    return 0;
}
```

---

## 作者：Nosta1enh (赞：0)

很入门的一道题。

题目中说高桥君会跳过 $123$ 这个数，那么如果 $n < 123$ ，所有的数都会被数一遍，因此答案就是 $n$ 。

如果 $n \ge 123$ ，那么就会少数 $123$ 这个数，答案为 $n-1$ 。

[AC](https://www.luogu.com.cn/record/96491155) code:

```
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    if(n<123)cout<<n;
    else cout<<n-1;
    return 0;
}
```


---

