# 题目信息

# Polycarp and Div 3

## 题目描述

Polycarp likes numbers that are divisible by 3.

He has a huge number $ s $ . Polycarp wants to cut from it the maximum number of numbers that are divisible by $ 3 $ . To do this, he makes an arbitrary number of vertical cuts between pairs of adjacent digits. As a result, after $ m $ such cuts, there will be $ m+1 $ parts in total. Polycarp analyzes each of the obtained numbers and finds the number of those that are divisible by $ 3 $ .

For example, if the original number is $ s=3121 $ , then Polycarp can cut it into three parts with two cuts: $ 3|1|21 $ . As a result, he will get two numbers that are divisible by $ 3 $ .

Polycarp can make an arbitrary number of vertical cuts, where each cut is made between a pair of adjacent digits. The resulting numbers cannot contain extra leading zeroes (that is, the number can begin with 0 if and only if this number is exactly one character '0'). For example, 007, 01 and 00099 are not valid numbers, but 90, 0 and 10001 are valid.

What is the maximum number of numbers divisible by $ 3 $ that Polycarp can obtain?

## 说明/提示

In the first example, an example set of optimal cuts on the number is 3|1|21.

In the second example, you do not need to make any cuts. The specified number 6 forms one number that is divisible by $ 3 $ .

In the third example, cuts must be made between each pair of digits. As a result, Polycarp gets one digit 1 and $ 33 $ digits 0. Each of the $ 33 $ digits 0 forms a number that is divisible by $ 3 $ .

In the fourth example, an example set of optimal cuts is 2|0|1|9|201|81. The numbers $ 0 $ , $ 9 $ , $ 201 $ and $ 81 $ are divisible by $ 3 $ .

## 样例 #1

### 输入

```
3121
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1000000000000000000000000000000000
```

### 输出

```
33
```

## 样例 #4

### 输入

```
201920181
```

### 输出

```
4
```

# AI分析结果

### 题目翻译
# Polycarp与3的整除性

## 题目描述
Polycarp喜欢能被3整除的数。

他有一个非常大的数 $ s $ 。Polycarp想从这个数中切出尽可能多的能被3整除的数。为此，他在相邻数字对之间进行任意数量的垂直切割。结果，经过 $ m $ 次这样的切割后，总共会有 $ m + 1 $ 个部分。Polycarp分析每个得到的数，并找出其中能被3整除的数的数量。

例如，如果原始数字是 $ s = 3121 $ ，那么Polycarp可以用两次切割将其切成三个部分： $ 3|1|21 $ 。结果，他将得到两个能被3整除的数。

Polycarp可以进行任意数量的垂直切割，每个切割都在相邻数字对之间进行。得到的数不能包含多余的前导零（也就是说，一个数只有当它恰好是一个字符 '0' 时才能以0开头）。例如，007、01和00099不是有效的数字，但90、0和10001是有效的。

Polycarp最多能得到多少个能被3整除的数？

## 说明/提示
在第一个示例中，对该数字进行最优切割的一种方式是 $ 3|1|21 $ 。

在第二个示例中，不需要进行任何切割。指定的数字6本身就构成一个能被3整除的数。

在第三个示例中，必须在每对相邻数字之间进行切割。结果，Polycarp得到一个数字1和33个数字0。33个数字0中的每一个都构成一个能被3整除的数。

在第四个示例中，一种最优切割方式是 $ 2|0|1|9|201|81 $ 。数字 $ 0 $ 、 $ 9 $ 、 $ 201 $ 和 $ 81 $ 都能被3整除。

## 样例 #1
### 输入
```
3121
```
### 输出
```
2
```

## 样例 #2
### 输入
```
6
```
### 输出
```
1
```

## 样例 #3
### 输入
```
1000000000000000000000000000000000
```
### 输出
```
33
```

## 样例 #4
### 输入
```
201920181
```
### 输出
```
4
```

### 综合分析与结论
这些题解主要围绕如何从一个大数字中切割出最多能被3整除的数展开，思路主要分为贪心和动态规划两类。
- **贪心思路**：通过遍历字符串，依据当前累加数的个数、当前数是否为3的倍数、已累加数的和是否为3的倍数等条件进行切割。
- **动态规划思路**：定义状态表示以某个位置结尾或前若干个字符最多能划分出的能被3整除的段数，通过枚举转移点并利用前缀和判断区间和是否能被3整除来更新状态。

### 所选题解
- **SUPERLWR（5星）**
    - **关键亮点**：思路清晰，贪心策略简单直接，代码实现简洁易懂。
    - **个人心得**：无
- **Diaоsi（4星）**
    - **关键亮点**：先给出 $O(n^2)$ 的动态规划做法，再通过数学证明将时间复杂度优化到 $O(n)$ ，逻辑严谨。
    - **个人心得**：无
- **XL4453（4星）**
    - **关键亮点**：同样是动态规划思路，通过数学原理缩小转移点的枚举范围，优化了时间复杂度。
    - **个人心得**：无

### 重点代码
#### SUPERLWR
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string str;
    cin>>str;
    int len=str.size(),cnt=0,pre=0,ans=0;
    for(int i=0;i<len;i++)
    {
        pre+=str[i]-'0';
        cnt++;
        if(cnt==3||pre%3==0||(str[i]-'0')%3==0)
        {
            ans++;
            pre=0;
            cnt=0;
        }
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：遍历字符串，累加数字并计数，当满足当前累加数的个数为3、已累加数的和为3的倍数、当前数为3的倍数这三个条件之一时，划分出一段，答案加1，并将累加数和计数清零。

#### Diaоsi
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
int n,a[N],f[N],sum[N];
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int &x,int &y){x^=y^=x^=y;}
string s;
int main(){
    cin>>s;
    n=s.size();
    for(int i=1;i<=n;i++)
        a[i]=(int)(s[i-1]-'0'),sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++)
        for(int j=i;j>=Max(1,i-2);j--)
            f[i]=Max(f[i],f[j-1]+((sum[i]-sum[j-1])%3==0?1:0));
    printf("%d\n",f[n]);
    return 0;
}
```
**核心实现思想**：定义 $f_i$ 表示以 $i$ 为结尾时，每段之和被三整除的段数最多的个数。通过前缀和计算区间和，枚举 $j$ 从 $i - 2$ 到 $i$ ，若区间 $[j, i]$ 的和能被3整除，则更新 $f_i$ 。

#### XL4453
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[200005],a[200005],len,ans;
int check(int n){if(n%3==0)return 1;return 0;}
int main(){
    while(~scanf("%1d",&a[++len]));len--;
    for(int i=1;i<=len;i++){
        f[i]=max(f[max(0,i-1)]+check(a[i]),max(f[max(0,i-2)]+check(a[i]+a[max(0,i-1)]),f[max(0,i-3)]+check(a[i-1]+a[i]+a[max(0,i-2)])));
        ans=max(ans,f[i]);
    }
    printf("%d",ans);
}
```
**核心实现思想**：定义 $f_i$ 表示以 $i$ 为终点的一段区间最多能分成的能被三整除的段数，通过枚举 $i$ 向前最多三个位置，计算区间和是否能被3整除来更新 $f_i$ ，最后取最大值作为答案。

### 最优关键思路或技巧
- **贪心策略**：利用数的性质，当累加数个数为3、当前数为3的倍数、已累加数的和为3的倍数时进行切割，可快速得到结果。
- **动态规划优化**：通过数学证明，将转移点的枚举范围缩小到 $[i - 2, i]$ ，将时间复杂度从 $O(n^2)$ 优化到 $O(n)$ 。

### 可拓展之处
同类型题目可能会改变整除的条件，如能被其他数整除，或者改变切割规则。类似算法套路可应用于区间划分、子序列问题等，通过定义状态和转移方程，结合数学性质进行优化。

### 推荐洛谷题目
- [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)

### 个人心得摘录与总结
- **VenusM1nT**：本来只是尝试“暴力”解法，没想到最终通过了，确定贪心策略后，使用字符串存数和前缀和计算优化时间复杂度。总结：可以先尝试简单的暴力解法，再根据题目特点进行优化。

---
处理用时：61.10秒