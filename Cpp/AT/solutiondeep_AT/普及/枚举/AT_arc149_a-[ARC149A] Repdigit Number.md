# 题目信息

# [ARC149A] Repdigit Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc149/tasks/arc149_a

正整数 $ N,\ M $ が与えられます．次の条件をすべて満たす正整数 $ X $ のうち，最大であるものを答えてください．

- $ X $ は $ 10^N $ 未満の正整数で，$ X $ を $ 10 $ 進法表記したときのどの桁の数字も同じである．
- $ X $ は $ M $ の倍数である．

ただし，条件を満たす正整数 $ X $ が存在しない場合には `-1` と出力してください．

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 10^5 $
- $ 1\leq\ M\leq\ 10^9 $

### Sample Explanation 1

条件を満たす正整数 $ X $ は，$ 444,\ 888,\ 444444,\ 888888 $ の $ 4 $ つです．このうち最大のものである $ 888888 $ が答となります．

### Sample Explanation 2

条件を満たす正整数 $ X $ は，$ 444,\ 888,\ 444444,\ 888888,\ 444444444,\ 888888888 $ の $ 6 $ つです．

### Sample Explanation 3

条件を満たす正整数 $ X $ は，$ 3,\ 6,\ 9 $ の $ 3 $ つです．

### Sample Explanation 4

条件を満たす正整数 $ X $ は存在しません．

## 样例 #1

### 输入

```
7 12```

### 输出

```
888888```

## 样例 #2

### 输入

```
9 12```

### 输出

```
888888888```

## 样例 #3

### 输入

```
1 3```

### 输出

```
9```

## 样例 #4

### 输入

```
1000 25```

### 输出

```
-1```

## 样例 #5

### 输入

```
30 1```

### 输出

```
999999999999999999999999999999```

# AI分析结果

### 题目翻译
给定正整数 $N$ 和 $M$。请回答满足以下所有条件的最大正整数 $X$。
- $X$ 是小于 $10^N$ 的正整数，并且 $X$ 用十进制表示时的每一位数字都相同。
- $X$ 是 $M$ 的倍数。

但是，如果不存在满足条件的正整数 $X$，则输出 `-1`。

### 综合分析与结论
这些题解的核心思路都是枚举小于 $10^n$ 且各位数字相同的数，然后判断其是否为 $m$ 的倍数，取其中最大的数作为答案。由于 $n$ 最大可达 $10^5$，直接计算这些数会导致溢出，所以题解们都采用了取模运算的技巧，边计算边取模，避免了高精度运算。

各题解的算法要点和解决难点如下：
1. **思路**：枚举位数从 $1$ 到 $n$，每一位上的数字从 $1$ 到 $9$，生成各位数字相同的数。
2. **算法要点**：使用状态转移方程 $f_{i,j}=(f_{i - 1,j} \times 10 + j) \bmod m$ 计算余数，其中 $f_{i,j}$ 表示由 $i$ 个数字 $j$ 组成的数模 $m$ 的余数。
3. **解决难点**：避免高精度运算，通过取模运算在计算过程中控制数值大小。

### 所选题解
- **Garbage_fish（5星）**
    - **关键亮点**：思路清晰，对取模运算的数学原理进行了详细证明，代码简洁，使用一维数组优化了空间复杂度。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void fread(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
const int N=1e5+10;
int n,m,f[15],cnt=1,num=-1;
signed main(){
    fread();
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=9;j++){
            f[j]=(f[j]*10+j)%m;
            if(!f[j]){
                cnt=i,num=j;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        cout<<num;
    }
    return 0;
}
```
- **So_noSlack（4星）**
    - **关键亮点**：思路简单明了，代码实现清晰，对状态转移方程的推导有详细说明。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;

long long n, m, mp[100005][15];
long long ans1, ans2;

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= 9; j ++) {
            mp[i][j] = (mp[i - 1][j] * 10 + j) % m;
            if(!mp[i][j]) ans1 = i, ans2 = j;
        }
    if(!ans1 || !ans2) {
        cout << "-1\n";
        return 0;
    }
    for(int i = 1; i <= ans1; i ++) cout << ans2;
    return 0;
}
```
- **Naro_Ahgnay（4星）**
    - **关键亮点**：思路简洁，代码实现直接，对构造数字和判断倍数的方法有清晰说明。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,y,t;
long long a[11];
int main() 
{
    scanf("%d%d",&n,&m);
    x=y=0;
    for(int i=1;i<=n;++i) 
    {
        for(int j=1;j<=9;++j) 
        {
            a[j]=(a[j]*10+j)%m;
            if(a[j]==0) x=i,y=j;
        }
    }
    if(!x) puts("-1");
    else 
    {
        for(int i=1;i<=x;++i) printf("%d",y);
        putchar('\n');
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **取模运算优化**：利用 $(a + b) \bmod m = (a \bmod m + b \bmod m) \bmod m$ 和 $(a \times b) \bmod m = ((a \bmod m) \times (b \bmod m)) \bmod m$ 的性质，边计算边取模，避免高精度运算。
2. **状态转移方程**：使用 $f_{i,j}=(f_{i - 1,j} \times 10 + j) \bmod m$ 计算余数，减少计算量。

### 可拓展之处
同类型题目可能会有不同的约束条件，如数字的进制变化、倍数关系的变化等。类似的算法套路是在处理大数问题时，通过取模运算控制数值大小，利用状态转移方程减少计算量。

### 洛谷题目推荐
1. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：涉及大数运算和取模运算。
2. [P1965 转圈游戏](https://www.luogu.com.cn/problem/P1965)：需要运用快速幂和取模运算。
3. [P3811 乘法逆元](https://www.luogu.com.cn/problem/P3811)：考察取模运算和逆元的概念。

### 个人心得摘录与总结
题解中无个人心得相关内容。

---
处理用时：34.26秒