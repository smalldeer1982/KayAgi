# 题目信息

# Martian Luck

## 题目描述

You know that the Martians use a number system with base $ k $ . Digit $ b $ ( $ 0<=b&lt;k $ ) is considered lucky, as the first contact between the Martians and the Earthlings occurred in year $ b $ (by Martian chronology).

A digital root $ d(x) $ of number $ x $ is a number that consists of a single digit, resulting after cascading summing of all digits of number $ x $ . Word "cascading" means that if the first summing gives us a number that consists of several digits, then we sum up all digits again, and again, until we get a one digit number.

For example, $ d(3504_{7})=d((3+5+0+4)_{7})=d(15_{7})=d((1+5)_{7})=d(6_{7})=6_{7} $ . In this sample the calculations are performed in the 7-base notation.

If a number's digital root equals $ b $ , the Martians also call this number lucky.

You have string $ s $ , which consists of $ n $ digits in the $ k $ -base notation system. Your task is to find, how many distinct substrings of the given string are lucky numbers. Leading zeroes are permitted in the numbers.

Note that substring $ s[i...\ j] $ of the string $ s=a_{1}a_{2}...\ a_{n} $ ( $ 1<=i<=j<=n $ ) is the string $ a_{i}a_{i+1}...\ a_{j} $ . Two substrings $ s[i_{1}...\ j_{1}] $ and $ s[i_{2}...\ j_{2}] $ of the string $ s $ are different if either $ i_{1}≠i_{2} $ or $ j_{1}≠j_{2} $ .

## 说明/提示

In the first sample the following substrings have the sought digital root: $ s[1...\ 2] $ = "3 2", $ s[1...\ 3] $ = "3 2 0", $ s[3...\ 4] $ = "0 5", $ s[4...\ 4] $ = "5" and $ s[2...\ 6] $ = "2 0 5 6 1".

## 样例 #1

### 输入

```
10 5 6
3 2 0 5 6 1
```

### 输出

```
5```

## 样例 #2

### 输入

```
7 6 4
3 5 0 4
```

### 输出

```
1```

## 样例 #3

### 输入

```
257 0 3
0 0 256
```

### 输出

```
3```

# AI分析结果

### 题目内容
# Martian Luck

## 题目描述
已知火星人使用基数为 $k$ 的数字系统。数字 $b$（$0 \leq b < k$）被认为是幸运的，因为火星人与地球人的首次接触发生在年份 $b$（按火星人的纪年法）。

数字 $x$ 的数字根 $d(x)$ 是这样一个数字，它由单个数字组成，是对数字 $x$ 的所有数字进行级联求和后得到的结果。“级联” 意味着如果第一次求和得到的数字由多个数字组成，那么我们再次对所有数字求和，如此反复，直到得到一个一位数。

例如，$d(3504_{7}) = d((3 + 5 + 0 + 4)_{7}) = d(15_{7}) = d((1 + 5)_{7}) = d(6_{7}) = 6_{7}$ 。在这个例子中，计算是在七进制下进行的。

如果一个数字的数字根等于 $b$，火星人也将这个数字称为幸运数。

你有一个字符串 $s$，它由 $n$ 个 $k$ 进制的数字组成。你的任务是找出给定字符串中有多少个不同的子串是幸运数。数字中允许有前导零。

注意，字符串 $s = a_{1}a_{2}...a_{n}$ 的子串 $s[i... j]$（$1 \leq i \leq j \leq n$）是字符串 $a_{i}a_{i + 1}...a_{j}$ 。字符串 $s$ 的两个子串 $s[i_{1}... j_{1}]$ 和 $s[i_{2}... j_{2}]$ 不同，当且仅当 $i_{1} \neq i_{2}$ 或 $j_{1} \neq j_{2}$ 。

## 说明/提示
在第一个样例中，以下子串具有所需的数字根：$s[1... 2] =$ “3 2”，$s[1... 3] =$ “3 2 0”，$s[3... 4] =$ “0 5”，$s[4... 4] =$ “5” 以及 $s[2... 6] =$ “2 0 5 6 1” 。

## 样例 #1
### 输入
```
10 5 6
3 2 0 5 6 1
```
### 输出
```
5```

## 样例 #2
### 输入
```
7 6 4
3 5 0 4
```
### 输出
```
1```

## 样例 #3
### 输入
```
257 0 3
0 0 256
```
### 输出
```
3```

### 算法分类
数学、前缀和

### 综合分析与结论
这几道题解的核心思路都是利用数字根在 $k$ 进制下与模 $k - 1$ 的关系来解题。难点在于处理 $b = 0$ 和 $b = k - 1$ 的特殊情况，避免对 $0$ 子串的重复计算或错误计算。各题解都通过前缀和结合 `map` 统计来优化时间复杂度到 $O(n\log n)$ 。不同之处在于对特殊情况的处理细节以及代码实现风格略有差异。

### 所选的题解
 - **豆浆的题解**：
   - **星级**：4星
   - **关键亮点**：先阐述数字根的相关性质，如一个数加9、乘9以及两数相加时数字根的变化规律，便于理解原理。利用这些性质说明可用前缀和维护子串数字根。代码简洁明了，对特殊情况 $b = 0$ 和 $b = k - 1$ 的处理逻辑清晰。
   - **重点代码及核心思想**：
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> m;
long long ans,sum;
int k,b,n,x,cnt;
int main(){
    cin>>k>>b>>n;
    if(!b){//b为0时的特殊处理
        for(int i=0;i<n;i++){
            cin>>x;
            cnt=x?0:(cnt+1);
            ans+=cnt;
        }
    }
    else{
        k--;
        m[0]=1;
        for(int i=0;i<n;i++){
            cin>>x;
            sum+=x;
            cnt=x?0:(cnt+1);
            ans+=m[(sum-b+k)%k];//利用前缀和及map统计符合条件子串
            m[sum%=k]++;
            if(b==k){//b等于k - 1时防止0被重复计算
                ans-=cnt;
            } 
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
核心思想是先对 $b = 0$ 的情况单独处理，统计连续0的个数作为答案。对于其他情况，利用前缀和 `sum` 记录当前位置数字和，通过 `map` 统计 `sum % (k - 1)` 的出现次数，根据公式 `(sum - b + k) % k` 计算符合数字根为 $b$ 的子串数量，并处理 $b = k - 1$ 时的特殊情况。
 - **_edge_ 的题解**：
   - **星级**：4星
   - **关键亮点**：详细证明了 $x$ 经过数位和变换最终为 $b$ 时，$x \equiv b \pmod {(k - 1)}$ 的结论，逻辑严谨。代码实现上对特殊情况的处理清晰，通过 `Map` 记录前缀和模 $k - 1$ 的值出现次数来统计答案。
   - **重点代码及核心思想**：
```cpp
#include <iostream>
#include <cstdio>
#include <map>
#define int long long 
using namespace std;
int n,k,b,sum,ans;
map <int,int> Map;
signed main()
{
    scanf("%lld %lld %lld",&k,&b,&n);
    if (b==0) {
        for (int i=1;i<=n;i++) {
            int xx=0;scanf("%lld",&xx);
            if (xx==0) sum++;
            else sum=0;
            ans+=sum;
        }
        cout<<ans<<"\n";
    }
    else {
        Map[0]++;int cnt=0;
        for (int i=1;i<=n;i++) {
            int xx=0;scanf("%lld",&xx);
            if (xx) cnt=0;
            else cnt++;
            sum+=xx;
            ans+=Map[(sum-b+k-1)%(k-1)];
            Map[sum%(k-1)]++;
            if (b==k-1) ans-=cnt;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```
核心思想与豆浆题解类似，先处理 $b = 0$ 的特殊情况，统计连续0的个数。对于其他情况，通过前缀和 `sum` 记录当前数字和，利用 `Map` 统计 `sum % (k - 1)` 的出现次数，根据公式 `(sum - b + k - 1) % (k - 1)` 计算符合条件子串数量，并处理 $b = k - 1$ 时的特殊情况。
 - **ifffer_2137的题解**：
   - **星级**：4星
   - **关键亮点**：通过打表得出 $k$ 进制下数根循环节为 $k - 1$ 的结论，利用位值原理证明合法子段的充要条件是子段和模 $k - 1$ 余 $b$ 。代码实现上对特殊情况处理细致，先统计所有连续为0的段的子段数，再根据 $b$ 的不同情况进行计算。
   - **重点代码及核心思想**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
int k,b,n,ans;
int a[maxn];
map<int,int> t;
signed main(){
    k=read(),b=read(),n=read();
    int cnt=0;
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]) ans+=cnt*(cnt+1)/2,cnt=0;
        else cnt++;
    }
    if(cnt) ans+=cnt*(cnt+1)/2;
    if(b==0){
        cout<<ans<<endl;
        return 0;
    }else if(b==k-1){
        ans=-ans;
    }else{
        ans=0;
    }
    t[0]++;
    for(int i=1,s=0;i<=n;i++){
        s=(s+a[i])%(k-1);
        ans+=t[(s-b%(k-1)+(k-1))%(k-1)];
        t[s]++;
    }
    cout<<ans<<endl;
    return 0;
}
```
核心思想是先统计连续0子串的数量，对于 $b = 0$ 直接输出结果。对于 $b = k - 1$ 先将之前统计的连续0子串数量取反（因为后续计算会重复），其他情况重新计算。利用前缀和 `s` 记录当前数字和，通过 `t` 统计 `s % (k - 1)` 的出现次数，根据公式 `(s - b % (k - 1) + (k - 1)) % (k - 1)` 计算符合条件子串数量。

### 最优关键思路或技巧
利用数字根在 $k$ 进制下与模 $k - 1$ 的关系，通过前缀和结合 `map` 统计来高效求解。同时要注意对 $b = 0$ 和 $b = k - 1$ 这两种特殊情况的细致处理，避免重复或错误计算。

### 可拓展之处
同类型题可能会改变数字根的定义或者改变判断幸运数的条件，但核心思路依然是利用数字在特定进制下的数学性质结合前缀和等方法优化求解。类似算法套路还可应用于其他涉及数字性质分析及子串统计的题目。

### 洛谷相似题目推荐
 - **P1082 [NOIP2012 提高组] 同余方程**：考察数论中的同余知识。
 - **P2613 【模板】有理数取余**：涉及有理数在取模意义下的运算，与本题数字在特定进制下的运算分析有相似之处。
 - **P3951 [NOIP2017 提高组] 小凯的疑惑**：同样是数论相关题目，锻炼对数论性质的分析和应用能力。 

---
处理用时：94.46秒