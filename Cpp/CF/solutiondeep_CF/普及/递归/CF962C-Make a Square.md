# 题目信息

# Make a Square

## 题目描述

You are given a positive integer $ n $ , written without leading zeroes (for example, the number 04 is incorrect).

In one operation you can delete any digit of the given integer so that the result remains a positive integer without leading zeros.

Determine the minimum number of operations that you need to consistently apply to the given integer $ n $ to make from it the square of some positive integer or report that it is impossible.

An integer $ x $ is the square of some positive integer if and only if $ x=y^2 $ for some positive integer $ y $ .

## 说明/提示

In the first example we should delete from $ 8314 $ the digits $ 3 $ and $ 4 $ . After that $ 8314 $ become equals to $ 81 $ , which is the square of the integer $ 9 $ .

In the second example the given $ 625 $ is the square of the integer $ 25 $ , so you should not delete anything.

In the third example it is impossible to make the square from $ 333 $ , so the answer is -1.

## 样例 #1

### 输入

```
8314
```

### 输出

```
2
```

## 样例 #2

### 输入

```
625
```

### 输出

```
0
```

## 样例 #3

### 输入

```
333
```

### 输出

```
-1
```

# AI分析结果

### 题目翻译
#### 题目描述
给定一个正整数 $n$，该数不包含前导零（例如，数字 04 是不正确的）。

在一次操作中，你可以删除给定整数的任意一位数字，使得结果仍然是一个不包含前导零的正整数。

确定需要对给定整数 $n$ 连续执行的最少操作次数，以便将其变为某个正整数的平方；若无法实现，则报告不可能。

若存在正整数 $y$ 使得 $x = y^2$，则称整数 $x$ 是某个正整数的平方。

#### 说明/提示
在第一个示例中，我们应该从 $8314$ 中删除数字 $3$ 和 $4$。之后，$8314$ 变为 $81$，而 $81$ 是整数 $9$ 的平方。

在第二个示例中，给定的 $625$ 是整数 $25$ 的平方，因此无需删除任何数字。

在第三个示例中，无法将 $333$ 变为一个平方数，因此答案是 -1。

#### 样例 #1
##### 输入
```
8314
```
##### 输出
```
2
```

#### 样例 #2
##### 输入
```
625
```
##### 输出
```
0
```

#### 样例 #3
##### 输入
```
333
```
##### 输出
```
-1
```

### 综合分析与结论
这些题解主要围绕如何通过最少的操作次数将给定正整数转换为某个正整数的平方展开，若无法转换则输出 -1。各题解的思路主要分为暴力枚举和深度优先搜索（DFS）两类。

#### 思路对比
- **暴力枚举**：从最大可能的平方数（$\sqrt{n}$）开始递减枚举，将输入的 $n$ 每位数分解存入数组，再把枚举的平方数也拆分为数组，对比判断是否能由 $n$ 得到该平方数，找到所需操作最少的情况。
- **深度优先搜索（DFS）**：考虑每一位数字删或不删的情况，枚举所有可能的组合，判断组合得到的数是否为完全平方数，同时要注意处理前导零的情况。

#### 算法要点
- **暴力枚举**：关键在于枚举平方数并进行数字匹配，使用双指针匹配判断平方数是否为 $n$ 的子序列。
- **深度优先搜索（DFS）**：通过递归实现，记录当前选择的数字和操作次数，在搜索到尽头时判断是否满足条件并更新答案。

#### 解决难点
- **前导零处理**：在枚举和搜索过程中，需要确保得到的数不包含前导零，否则不符合要求。
- **时间复杂度**：由于 $n$ 最大为 $2\times10^9$，需要合理选择算法以避免超时，部分题解利用 $n$ 最多 9 位的特点进行暴力搜索。

#### 评分
- **GusyNight**：4 星。思路清晰，代码简洁，通过暴力枚举平方数并进行匹配，容易理解。
- **Andy_Li**：4 星。采用深度优先搜索，对前导零的处理有详细说明，并给出了测试数据，代码逻辑清晰。
- **QianianXY**：4 星。同样使用深度优先搜索，按位搜索选择删或不删，对前导零和转换为十进制数的处理细节有说明。

### 所选题解
- **GusyNight（4 星）**
    - **关键亮点**：思路直接，从最大可能的平方数开始递减枚举，通过双指针匹配判断是否能得到该平方数，代码简洁易懂。
- **Andy_Li（4 星）**
    - **关键亮点**：深度优先搜索思路明确，对前导零的处理有详细说明，并给出了测试数据，有助于理解。
    - **个人心得**：提供一组一开始没特判前导零数据把自己卡住的数据：输入 ```101```，输出 ```2```，提醒要注意前导零的处理。
- **QianianXY（4 星）**
    - **关键亮点**：按位搜索选择删或不删，类比快读将字符串转换为十进制数判断是否为完全平方数，思路清晰，细节处理得当。

### 重点代码
#### GusyNight
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    long long n,m,a[10],b[10];
    cin>>n;m=n;
    int cnt1=0,cnt2=0,l;
    while(m)a[cnt1++]=m%10,m/=10;
    for(int i=sqrt(n);i>=1;i--){
        long long x=i*i;cnt2=0;
        long long k=x;
        while(x)b[cnt2++]=x%10,x/=10;
        l=0;
        for(int j=0;j<cnt1;j++){
            if(a[j]==b[l]){
                l++;
                if(l==cnt2)break;
            }
        }
        if(l==cnt2)return cout<<cnt1-l,0;
    }
    puts("-1");
    return 0;
}
```
**核心思想**：将输入的 $n$ 每位数分解存入数组，从最大可能的平方数（$\sqrt{n}$）开始递减枚举，把枚举的平方数也拆分为数组，通过双指针匹配判断是否能由 $n$ 得到该平方数，找到所需操作最少的情况。

#### Andy_Li
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+7;
int cnt=0,ans=40;
int a[maxn];
int checks(int x,int num)
{
    num=cnt-num;
    while(x)
    {
        x/=10;
        num--;
    }
    if(num!=0)
        return 0;
    return 1;
}
void dfs(int pos,int x,int choose)
{
    if(pos>cnt)
    {
        if(int(sqrt(x))*int(sqrt(x))==x && x!=0 && checks(x,choose)!=0)
            ans=min(ans,choose);
        return ;
    }
    for(int i=0;i<=1;i++)
        if(i==0)
            dfs(pos+1,x*10+a[pos],choose);
        else
            dfs(pos+1,x,choose+1);
    return ;
}
int main()
{
    cin.tie(0);
    std::ios::sync_with_stdio(false);
    int x;
    cin>>x;
    int t=x;
    while(t)
    {
        a[++cnt]=t%10;
        t/=10;
    }
    for(int i=1;i<=cnt/2;i++)
        swap(a[i],a[cnt-i+1]);
    dfs(1,0,0);
    if(ans==40)
        ans=-1;
    cout<<ans;
    return 0;
}
```
**核心思想**：采用深度优先搜索，考虑每一位数字删或不删的情况，枚举所有可能的组合，在搜索到尽头时判断得到的数是否为完全平方数，同时使用 `checks` 函数处理前导零的情况，更新最少操作次数。

#### QianianXY
```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 200010
using namespace std;

int len, ans = 1e9;
char c[N], str[N];

inline bool check(int tot)
{
    double num = 0; 
    for (rei i = 1; i <= tot; i++) num = num * 10 + str[i] - 48;
    double ret = sqrt(num);
    return (ret == (int)ret);
}

inline void dfs(int k, int tot)
{
    if (k > len)
    {
        if (tot && check(tot)) ans = min(len - tot, ans);
        return;
    } 
    dfs(k + 1, tot);
    if (c[k] == '0' && !tot) return;
    str[++tot] = c[k];
    dfs(k + 1, tot);
}

int main()
{
    scanf("%s", c + 1); len = strlen(c + 1);
    dfs(1, 0);
    printf("%d", (ans == 1e9 ? -1 : ans));
    return 0;
}
```
**核心思想**：按位搜索，选择删或不删，并记录在一个字符串内。搜索到尽头后，将字符串转换为十进制数，判断开方后是否为整数，更新最少操作次数，同时注意处理前导零的情况。

### 最优关键思路或技巧
- **利用数据范围**：由于 $n$ 最多 9 位，时间限制为 2 秒，可采用暴力枚举或深度优先搜索等方法。
- **双指针匹配**：在暴力枚举平方数时，使用双指针匹配判断平方数是否为 $n$ 的子序列，提高效率。
- **深度优先搜索**：通过递归枚举每一位数字删或不删的情况，全面考虑所有可能的组合。

### 拓展思路
同类型题或类似算法套路：
- 涉及数字操作和组合的题目，如删除数字使结果满足特定条件、重新排列数字得到最大/最小值等。
- 可以使用深度优先搜索或暴力枚举的题目，需要注意处理边界条件和特殊情况，如前导零、重复元素等。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：从 $n$ 个数中选 $k$ 个数，使其和为素数，可使用深度优先搜索枚举所有组合。
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：输出从 $n$ 个数中选 $r$ 个数的所有组合，可使用深度优先搜索实现。
- [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)：输出 $n$ 个数的全排列，可使用深度优先搜索或 `next_permutation` 函数实现。

---
处理用时：68.64秒