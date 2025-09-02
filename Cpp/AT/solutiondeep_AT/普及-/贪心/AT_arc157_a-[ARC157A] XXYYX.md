# 题目信息

# [ARC157A] XXYYX

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc157/tasks/arc157_a

`X`, `Y` からなる長さ $ N $ の文字列 $ S $ であって，以下の条件を満たすものが存在するかどうかを判定してください．

**条件:** $ S $ 中で $ 2 $ つの文字が隣り合う $ (N\ -\ 1) $ 箇所のうち

- ちょうど $ A $ 個が `XX`，
- ちょうど $ B $ 個が `XY`，
- ちょうど $ C $ 個が `YX`，
- ちょうど $ D $ 個が `YY` である．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ A\ \geq\ 0 $
- $ B\ \geq\ 0 $
- $ C\ \geq\ 0 $
- $ D\ \geq\ 0 $
- $ A\ +\ B\ +\ C\ +\ D\ =\ N\ -\ 1 $
 
### Sample Explanation 1

たとえば $ S\ =\ {} $`XXYYX` とすると，$ 2 $ つの文字が隣り合う箇所は左から順に `XX`, `XY`, `YY`, `YX` であり，各 $ 1 $ 個ずつとなって条件を満たします．

### Sample Explanation 2

たとえば $ S\ =\ {} $`XXYXY` が条件を満たします．

### Sample Explanation 3

条件を満たす文字列は存在しません．

## 样例 #1

### 输入

```
5 1 1 1 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 1 2 1 0```

### 输出

```
Yes```

## 样例 #3

### 输入

```
5 0 4 0 0```

### 输出

```
No```

# AI分析结果

### 题目内容重写

【题目描述】

给定一个由字符 `X` 和 `Y` 组成的长度为 $N$ 的字符串 $S$，判断是否存在满足以下条件的字符串：

在 $S$ 中的 $N-1$ 对相邻字符中，恰好有 $A$ 对 `XX`，$B$ 对 `XY`，$C$ 对 `YX`，$D$ 对 `YY`。

### 综合分析与结论

本题的核心在于判断给定的 `XX`、`XY`、`YX`、`YY` 的数量是否能够构成一个合法的字符串。通过对题解的分析，可以发现以下几点关键思路：

1. **`XY` 和 `YX` 的关系**：`XY` 和 `YX` 的数量差必须满足 $|B - C| \leq 1$，否则无法构成合法字符串。
2. **特殊情况**：当 `B` 和 `C` 都为 0 时，如果 `A` 和 `D` 都大于 0，则无法构成合法字符串，因为 `XX` 和 `YY` 之间必须有 `XY` 或 `YX` 连接。
3. **构造方法**：当 $|B - C| \leq 1$ 时，可以通过交替插入 `X` 和 `Y` 来构造满足条件的字符串。

### 所选高分题解

#### 题解1：作者：SlyCharlotte (4星)

**关键亮点**：
- 详细分析了 `XY` 和 `YX` 的关系，并给出了构造方法。
- 代码简洁，逻辑清晰。

**代码实现**：
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

signed main()
{
    int n, a, b, c, d;
    scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
    if (abs(b - c) >= 2)
        cout << "No";
    else if (b == 0 && c == 0 && a > 0 && d > 0)
        cout << "No";
    else
        cout << "Yes";
}
```

#### 题解2：作者：__LiChangChao__ (4星)

**关键亮点**：
- 简洁明了地指出了 `XY` 和 `YX` 的关系，并给出了特殊情况下的判断。
- 代码简洁，易于理解。

**代码实现**：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,a,b,c,d;
int main() {
    cin>>n>>a>>b>>c>>d;
    if((abs(b-c)>=2)||(b==0&&c==0&&a>0&&d>0))cout<<"No";
    else cout<<"Yes";
}
```

#### 题解3：作者：_Chesed_ (4星)

**关键亮点**：
- 详细分析了 `XY` 和 `YX` 的关系，并给出了构造方法。
- 代码简洁，逻辑清晰。

**代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,a,b,c,d;
    cin>>n>>a>>b>>c>>d;
    if(abs(b-c)>=2){
        printf("No");
    }
    else if(b==0&&c==0&&a>0&&d>0){
        printf("No");
    }
    else{
        printf("Yes");
    }
}
```

### 最优关键思路与技巧

1. **`XY` 和 `YX` 的关系**：通过分析 `XY` 和 `YX` 的数量差，可以快速判断是否存在合法字符串。
2. **特殊情况处理**：当 `B` 和 `C` 都为 0 时，需要特别处理 `A` 和 `D` 的关系。
3. **构造方法**：通过交替插入 `X` 和 `Y`，可以构造满足条件的字符串。

### 拓展思路与类似题目

1. **类似题目**：
   - [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：考察字符串的构造与匹配。
   - [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)：考察字符串的构造与匹配。
   - [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)：考察字符串的构造与匹配。

2. **拓展思路**：
   - 可以进一步探讨更复杂的字符串构造问题，如包含更多字符或更复杂的匹配规则。
   - 可以研究字符串的自动机模型，用于更复杂的字符串匹配问题。

---
处理用时：42.83秒