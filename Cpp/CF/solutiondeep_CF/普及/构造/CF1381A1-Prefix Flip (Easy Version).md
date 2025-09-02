# 题目信息

# Prefix Flip (Easy Version)

## 题目描述

This is the easy version of the problem. The difference between the versions is the constraint on $ n $ and the required number of operations. You can make hacks only if all versions of the problem are solved.

There are two binary strings $ a $ and $ b $ of length $ n $ (a binary string is a string consisting of symbols $ 0 $ and $ 1 $ ). In an operation, you select a prefix of $ a $ , and simultaneously invert the bits in the prefix ( $ 0 $ changes to $ 1 $ and $ 1 $ changes to $ 0 $ ) and reverse the order of the bits in the prefix.

For example, if $ a=001011 $ and you select the prefix of length $ 3 $ , it becomes $ 011011 $ . Then if you select the entire string, it becomes $ 001001 $ .

Your task is to transform the string $ a $ into $ b $ in at most $ 3n $ operations. It can be proved that it is always possible.

## 说明/提示

In the first test case, we have $ 01\to 11\to 00\to 10 $ .

In the second test case, we have $ 01011\to 00101\to 11101\to       01000\to 10100\to 00100\to 11100 $ .

In the third test case, the strings are already the same. Another solution is to flip the prefix of length $ 2 $ , which will leave $ a $ unchanged.

## 样例 #1

### 输入

```
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1```

### 输出

```
3 1 2 1
6 5 2 5 3 1 2
0
9 4 1 2 10 4 1 2 1 5
1 1```

# AI分析结果

### 题目中文重写
# 前缀翻转（简单版本）

## 题目描述
这是该问题的简单版本。不同版本之间的区别在于 $n$ 的限制和所需的操作次数。只有当所有版本的问题都被解决时，你才能进行 Hack 操作。

有两个长度为 $n$ 的二进制字符串 $a$ 和 $b$（二进制字符串是由字符 $0$ 和 $1$ 组成的字符串）。在一次操作中，你选择 $a$ 的一个前缀，同时对该前缀中的位进行取反操作（$0$ 变为 $1$，$1$ 变为 $0$），并反转该前缀中位的顺序。

例如，如果 $a = 001011$，你选择长度为 $3$ 的前缀，它将变为 $011011$。然后，如果你选择整个字符串，它将变为 $001001$。

你的任务是在最多 $3n$ 次操作内将字符串 $a$ 转换为 $b$。可以证明这总是可行的。

## 说明/提示
在第一个测试用例中，我们有 $01 \to 11 \to 00 \to 10$。

在第二个测试用例中，我们有 $01011 \to 00101 \to 11101 \to 01000 \to 10100 \to 00100 \to 11100$。

在第三个测试用例中，字符串已经相同。另一种解决方案是翻转长度为 $2$ 的前缀，这将使 $a$ 保持不变。

## 样例 #1

### 输入
```
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1
```

### 输出
```
3 1 2 1
6 5 2 5 3 1 2
0
9 4 1 2 10 4 1 2 1 5
1 1
```

### 综合分析与结论
这些题解的核心目标都是在最多 $3n$ 次操作内将字符串 $a$ 转换为 $b$，主要有两种思路方向：
1. **逐位处理**：从字符串的最后一位开始，让 $a$ 的每一位等于 $b$ 的对应位。若当前位不同，根据 $a$ 的第一位和 $b$ 的当前位的关系决定是否先对 $a$ 的第一位操作，再对当前位及之前的前缀操作。
2. **统一字符**：将字符串 $a$ 和 $b$ 分别转化为只含 $0$ 或只含 $1$ 的字符串，若转化后的字符不同，再进行一次整体操作。

### 所选题解
- **Little_x_starTYJ（4星）**
    - **关键亮点**：思路清晰，通过贪心策略，利用相邻字符是否相等来确定操作，代码简洁，操作次数最多为 $2n - 1$ 次，能同时通过本题和加强版。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int num[200010];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    int t;
    cin >> t;
    while (t--) {
        int n, id = 0;
        string a, b;
        cin >> n >> a >> b;
        for (register int i = 0; i < n - 1; i++) {
            if (a[i] != a[i + 1])
                num[++id] = i + 1;
        }
        if (a[n - 1] != b[n - 1])
            num[++id] = n;
        for (register int i = n - 1; i; i--)
            if (b[i] != b[i - 1])
                num[++id] = i;
        cout << id << ' ';
        for (register int i = 1; i <= id; i++)
            cout << num[i] << ' ';
        cout << '\n';
    }
    return 0;
}
```
    - **核心实现思想**：先遍历字符串 $a$，若相邻字符不同则记录操作位置，再判断 $a$ 和 $b$ 的最后一位是否相同，不同则记录对整个字符串的操作，最后遍历字符串 $b$，同样记录相邻字符不同时的操作位置，最后输出操作次数和操作位置。

- **gaozitao1（4星）**
    - **关键亮点**：先给出暴力思路并分析其复杂度，然后逐步优化，提供了两种优化后的代码，一种时间复杂度为 $O(n^2)$，另一种为 $O(n)$，逻辑清晰，易于理解。
    - **核心代码（$O(n)$ 版本）**：
```cpp
#include<cstdio>
#include<iostream>
const int N=1000;
char a[N+1],b[N+1];
int c[N],d[N];//c和d分别记录a和b的操作
int main()
{
    register int i,j,k,n,t;//j和k分别统计a和b的方案数
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%s%s",&n,a+1,b+1);
        j=k=0;//注意清零
        for(i=1; i<n; ++i)
        {
            if(a[i]!=a[i+1])
                c[++j]=i;//将a变成只有一种字符的字符串
            if(b[i]!=b[i+1])
                d[++k]=i;//将b变成只有一种字符的字符串
        }
        if(a[n]!=b[n])//如果两个字符串不一样，那么就要对整个字符串操作一次
            c[++j]=n;
        printf("%d ",j+k);//输出方案数
        for(i=1; i<=j; ++i)
            printf("%d ",c[i]);//输出a的操作
        for(i=k; i; --i)
            printf("%d ",d[i]);//倒着输出b的操作
        putchar('\n');
    }
    return 0;
}
```
    - **核心实现思想**：分别遍历字符串 $a$ 和 $b$，若相邻字符不同则记录操作位置，若 $a$ 和 $b$ 的最后一位不同，则对字符串 $a$ 进行一次整体操作，最后输出操作次数和操作位置，注意输出 $b$ 的操作位置时要倒序。

- **liaoxingrui（4星）**
    - **关键亮点**：思路简洁明了，直接阐述将两个字符串都转化为一个字符的方法，操作次数最多为 $2n - 1$ 次，时间复杂度为 $O(n)$，代码实现简单。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,len;
int a[1005],b[1005];
string s1,s2;
int main(){
    cin>>t;
    while(t--){
        cin>>len>>s1>>s2;
        s1=' '+s1;
        s2=' '+s2;
        int sum1=0,sum2=0;
        for(int i=1;i<len;i++){
            if(s1[i]!=s1[i+1]){
                sum1++;
                a[sum1]=i;
            }
            if(s2[i]!=s2[i+1]){
                sum2++;
                b[sum2]=i;
            }
        }
        if(s1[len]!=s2[len]){
            sum1++;
            a[sum1]=len;
        }
        cout<<sum1+sum2;
        for(int i=1;i<=sum1;i++)
            cout<<" "<<a[i];
        for(int i=sum2;i>=1;i--)
            cout<<" "<<b[i];
        putchar('\n');
    }
    return 0;
}
```
    - **核心实现思想**：遍历字符串 $s1$ 和 $s2$，若相邻字符不同则记录操作位置，若 $s1$ 和 $s2$ 的最后一位不同，则对 $s1$ 进行一次整体操作，最后输出操作次数和操作位置，输出 $s2$ 的操作位置时倒序。

### 最优关键思路或技巧
- **贪心策略**：通过判断相邻字符是否相等来确定操作，可将字符串转化为只含 $0$ 或只含 $1$ 的字符串，减少操作次数。
- **倒序处理**：从字符串的最后一位开始处理，可避免后续操作影响已经处理好的位。

### 可拓展之处
同类型题可能会改变操作规则或限制条件，例如改变操作的范围、操作的方式等，但核心思路可能类似，可采用逐位处理或统一字符的方法。类似算法套路可应用于字符串处理、数组操作等问题中，通过合理的操作和判断来达到目标状态。

### 推荐洛谷题目
1. [P1217 [USACO1.5] 回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：涉及字符串处理和质数判断，需要对字符串进行操作和判断。
2. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：需要对字符串进行解析和计算，根据规则判断 ISBN 号码是否正确。
3. [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)：涉及字符串的加密和解密，需要根据规则进行字符替换和判断。

### 个人心得
本题解中未包含个人心得相关内容。

---
处理用时：43.16秒