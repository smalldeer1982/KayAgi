# 题目信息

# GCD Compression

## 题目描述

Ashish has an array $ a $ of consisting of $ 2n $ positive integers. He wants to compress $ a $ into an array $ b $ of size $ n-1 $ . To do this, he first discards exactly $ 2 $ (any two) elements from $ a $ . He then performs the following operation until there are no elements left in $ a $ :

- Remove any two elements from $ a $ and append their sum to $ b $ .

The compressed array $ b $ has to have a special property. The greatest common divisor ( $ \mathrm{gcd} $ ) of all its elements should be greater than $ 1 $ .

Recall that the $ \mathrm{gcd} $ of an array of positive integers is the biggest integer that is a divisor of all integers in the array.

It can be proven that it is always possible to compress array $ a $ into an array $ b $ of size $ n-1 $ such that $ gcd(b_1, b_2..., b_{n-1}) > 1 $ .

Help Ashish find a way to do so.

## 说明/提示

In the first test case, $ b = \{3+6, 4+5\} = \{9, 9\} $ and $ \mathrm{gcd}(9, 9) = 9 $ .

In the second test case, $ b = \{9+10\} = \{19\} $ and $ \mathrm{gcd}(19) = 19 $ .

In the third test case, $ b = \{1+2, 3+3, 4+5, 90+3\} = \{3, 6,       9, 93\} $ and $ \mathrm{gcd}(3, 6, 9, 93) = 3 $ .

## 样例 #1

### 输入

```
3
3
1 2 3 4 5 6
2
5 7 9 10
5
1 3 3 4 5 90 100 101 2 3```

### 输出

```
3 6
4 5
3 4
1 9
2 3
4 5
6 10```

# AI分析结果

### 题目内容
# GCD压缩

## 题目描述
阿希什（Ashish）有一个由 \(2n\) 个正整数组成的数组 \(a\) 。他想将数组 \(a\) 压缩成一个大小为 \(n - 1\) 的数组 \(b\) 。为此，他首先从数组 \(a\) 中恰好丢弃任意两个元素。然后，他执行以下操作，直到数组 \(a\) 中没有元素为止：
- 从数组 \(a\) 中移除任意两个元素，并将它们的和追加到数组 \(b\) 中。

压缩后的数组 \(b\) 必须具有一个特殊属性。其所有元素的最大公约数（\(\mathrm{gcd}\)）必须大于 \(1\) 。

回想一下，正整数数组的最大公约数是能整除该数组中所有整数的最大整数。

可以证明，总是可以将数组 \(a\) 压缩成一个大小为 \(n - 1\) 的数组 \(b\) ，使得 \(\gcd(b_1, b_2, \ldots, b_{n - 1}) > 1\) 。

请帮助阿希什找到一种方法来实现这一点。

## 说明/提示
在第一个测试用例中，\(b = \{3 + 6, 4 + 5\} = \{9, 9\}\) ，且 \(\mathrm{gcd}(9, 9) = 9\) 。

在第二个测试用例中，\(b = \{9 + 10\} = \{19\}\) ，且 \(\mathrm{gcd}(19) = 19\) 。

在第三个测试用例中，\(b = \{1 + 2, 3 + 3, 4 + 5, 90 + 3\} = \{3, 6, 9, 93\}\) ，且 \(\mathrm{gcd}(3, 6, 9, 93) = 3\) 。

## 样例 #1
### 输入
```
3
3
1 2 3 4 5 6
2
5 7 9 10
5
1 3 3 4 5 90 100 101 2 3
```
### 输出
```
3 6
4 5
3 4
1 9
2 3
4 5
6 10
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是利用奇数和偶数的性质，通过将数组 \(a\) 中的数按奇偶分类，使得最终压缩得到的数组 \(b\) 的元素的最大公约数大于 \(1\)，具体来说是让最大公约数为 \(2\) （因为奇数加奇数为偶数，偶数加偶数也为偶数）。算法要点在于读入数据时记录每个数的奇偶性及其下标，然后根据奇数和偶数个数的奇偶性，合理地舍弃两个数，再将剩余的数两两配对输出下标。解决难点在于如何保证在舍弃两个数后，剩余的奇数和偶数个数都为偶数，以便能两两配对且满足最终数组 \(b\) 的最大公约数大于 \(1\) 的条件。

### 所选的题解
- **作者：liuyi0905 (3星)**
    - **关键亮点**：思路清晰，先阐述题意，再明确从使 \(b\) 数组最大公约数为 \(2\) 入手，将 \(a\) 数组按奇偶分类，且指出记录下标和读入 \(2n\) 个数的注意点。
    - **重点代码**：
```cpp
for(int i=1;i<=2*n;i++){
    cin>>a;
    if(a%2)ad[++n1]=i;
    else ev[++n2]=i;
}
for(int i=1;i<n1;i+=2)
    if(v<n-1)cout<<ad[i]<<" "<<ad[i+1]<<"\n",v++;
for(int i=1;i<n2;i+=2)
    if(v<n-1)cout<<ev[i]<<" "<<ev[i+1]<<"\n",v++;
```
    - **核心实现思想**：读入 \(2n\) 个数，根据数的奇偶性将其下标分别存入 `ad`（奇数下标数组）和 `ev`（偶数下标数组），然后分别从两个数组中按顺序两两取出下标输出，控制输出对数不超过 \(n - 1\) 。
- **作者：rouxQ (4星)**
    - **关键亮点**：不仅思路清晰，还对为什么要使 \(\gcd(b_i)=2\) 以及操作过程中奇数和偶数个数的要求进行了详细分析，代码简洁明了。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> v1, v2;
int main (){
    int T;
    scanf("%d", &T);
    while(T--){
        v1.clear(); v2.clear();
        int n, ch;
        scanf("%d", &n);
        for (int i = 1; i <= 2 * n; i++){
            scanf("%d", &ch);
            if (ch % 2 == 0)v1.push_back(i);
            else v2.push_back(i);
        }
        if (v1.size() % 2 == 1)v1.pop_back(), v2.pop_back();
        else if (v1.size() >= 2)v1.pop_back(), v1.pop_back();
        else v2.pop_back(), v2.pop_back();
        for (int i = 0; i < v1.size(); i += 2)
            printf("%d %d\n", v1[i], v1[i + 1]);
        for (int i = 0; i < v2.size(); i += 2)
            printf("%d %d\n", v2[i], v2[i + 1]);
    }
    return 0;
}
```
    - **核心实现思想**：定义两个向量 `v1` 和 `v2` 分别存储偶数和奇数的下标。读入数据并分类存储下标后，根据奇数和偶数下标的数量情况进行处理，保证剩余的奇数和偶数下标数量都为偶数，最后按顺序两两输出下标。
- **作者：LeavingZzz (4星)**
    - **关键亮点**：对解题思路的解释详细，包括对奇数和偶数个数不同情况的处理说明，代码注释丰富。
    - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn=2007;
int ev[maxn],od[maxn],t1,t2;
int T,N;
inline int R()
{
    char c;
    int re;
    while((c=getchar())>'9'||c<'0');
    re=c-48;
    while((c=getchar())>='0'&&c<='9')
    re=re*10+c-48;
    return re;
}
int main()
{
    T=R();
    while(T--)
    {
        memset(ev,0,sizeof(ev));
        memset(od,0,sizeof(od));
        t1=t2=0;
        N=R();int x;
        for(register int i=1;i<=2*N;i++)
        {
            x=R();
            if(x&1) od[++t1]=i;
            else ev[++t2]=i;
        }
        while(t1>1&&N>1)
        {
            printf("%d %d\n",od[t1],od[t1-1]);
            t1-=2;N--;
        }
        while(t2>1&&N>1)
        {
            printf("%d %d\n",ev[t2],ev[t2-1]);
            t2-=2;N--;
        }
    }
    return 0;
}
```
    - **核心实现思想**：通过自定义函数 `R` 读入数据，用数组 `ev` 和 `od` 分别记录偶数和奇数的下标。根据奇数和偶数下标的数量，在保证有足够对数的情况下，从后往前两两输出奇数下标对和偶数下标对。

### 最优关键思路或技巧
利用数的奇偶性这一简单性质，将问题简化，通过合理舍弃两个数，使得剩余的数能按奇偶两两配对，保证最终数组 \(b\) 的元素最大公约数为 \(2\) ，从而满足题目要求。这种利用数的基本性质进行构造的思维方式是解决此类问题的关键。

### 拓展思路
同类型题通常围绕数论相关性质，通过构造满足特定条件的数组或序列来考察。类似算法套路是先分析题目要求的最终结果的性质，如最大公约数、和、积等的特点，再根据给定数据的初始性质，如奇偶性、大小关系等，设计合理的构造方法。

### 洛谷题目推荐
- [P1072  Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：涉及数论中最大公约数和最小公倍数的知识，通过构造满足特定最大公约数和最小公倍数关系的数来求解。
- [P2152  聪聪可可](https://www.luogu.com.cn/problem/P2152)：利用树上路径权值和对 \(3\) 取模的性质进行构造和统计，与本题利用数的性质构造结果类似。
- [P3951 小凯的疑惑](https://www.luogu.com.cn/problem/P3951)：通过对两个互质正整数的线性组合的分析构造，求解最大不能表示为这两个数的非负整数倍的数。 

---
处理用时：71.53秒