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
## 构造平方数

### 题目描述
给定一个正整数 $n$，该数没有前导零（例如，数字 04 是不正确的）。

在一次操作中，你可以删除给定整数的任意一位数字，使得结果仍然是一个没有前导零的正整数。

确定你需要对给定整数 $n$ 连续执行的最少操作次数，以使它变成某个正整数的平方；如果不可能，则报告 -1。

若存在正整数 $y$ 使得 $x = y^2$，则称整数 $x$ 是某个正整数的平方。

### 说明/提示
在第一个示例中，我们应该从 8314 中删除数字 3 和 4。之后，8314 变为 81，81 是整数 9 的平方。

在第二个示例中，给定的 625 是整数 25 的平方，因此无需删除任何数字。

在第三个示例中，无法将 333 变成一个平方数，因此答案是 -1。

### 样例 #1
#### 输入
```
8314
```
#### 输出
```
2
```

### 样例 #2
#### 输入
```
625
```
#### 输出
```
0
```

### 样例 #3
#### 输入
```
333
```
#### 输出
```
-1
```

### 综合分析与结论
这些题解主要围绕如何通过删除给定正整数 $n$ 中的某些数字，使其成为一个完全平方数，并求出最少的删除操作次数。思路主要分为暴力枚举和深度优先搜索（DFS）两类。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|GusyNight|先将输入的 $n$ 每位数分解存入数组，从 $\sqrt{n}$ 开始递减枚举可能的完全平方数，通过双指针匹配判断其是否为 $n$ 的子序列|分解数字、双指针匹配|处理前导零|4星|
|Andy_Li|采用深度优先搜索，考虑每一位数字删或不删，计算答案时取最小值并特判前导零|DFS、取最小值、特判前导零|前导零的判断|4星|
|__Hacheylight__|把 $n$ 拆分成数组，枚举所有排列，判断每个排列拼接后的数是否为完全平方数，注意去除前导零和长度为 0 的情况|拆分数字、枚举排列、判断完全平方数|前导零和长度为 0 的情况处理|3星|
|Wf_yjqd|枚举最终的完全平方数，将其拆位后与 $n$ 对比，使用双指针匹配判断是否为子序列|枚举完全平方数、双指针匹配|子序列匹配|3星|
|QianianXY|按位搜索，选择删或不删，将记录的字符串转换为十进制数，判断开方后是否为整数并更新答案，处理前导零|按位搜索、字符串转十进制、判断完全平方数|前导零处理|4星|
|ChenJr|使用数位 dp 思想，先存储每一位数字，通过 DFS 记录最小操作数|数位 dp、DFS|最小操作数记录|3星|
|yuheng_wang080904|使用全排列进行暴力枚举，用 0 和 1 表示删去和保留，判断前导零和完全平方数|全排列、判断前导零和完全平方数|前导零和完全平方数判断|3星|
|RNTBW|使用 DFS，用两个参数表示上一个选的数和当前的数，对当前数取位数，标记可得到的位数，最后从大到小循环判断|DFS、标记位数、从大到小循环|前导零处理和循环顺序|3星|
|千年陈皮精|将正整数和枚举的平方数拆分存入数组，判断删掉后能否变成平方数|拆分数字、判断平方数|匹配判断|3星|

### 所选题解
- **GusyNight（4星）**
    - 关键亮点：思路清晰，通过双指针匹配有效判断完全平方数是否为 $n$ 的子序列，代码简洁易懂。
    - 核心代码：
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
- **Andy_Li（4星）**
    - 关键亮点：采用 DFS 搜索，详细说明了前导零的处理，代码逻辑清晰。
    - 核心代码：
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
- **QianianXY（4星）**
    - 关键亮点：按位搜索思路独特，通过字符串转换和判断开方结果更新答案，有效处理前导零。
    - 核心代码：
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
    if (c[k] == '0' &&!tot) return;
    str[++tot] = c[k];
    dfs(k + 1, tot);
}
int main()
{
    scanf("%s", c + 1); len = strlen(c + 1);
    dfs(1, 0);
    printf("%d", (ans == 1e9? -1 : ans));
    return 0;
}
```

### 最优关键思路或技巧
- **双指针匹配**：在判断一个完全平方数是否为给定数字 $n$ 的子序列时，使用双指针可以高效地完成匹配，时间复杂度较低。
- **深度优先搜索（DFS）**：通过递归的方式考虑每一位数字的删或不删，能够遍历所有可能的情况，同时可以方便地处理前导零等问题。
- **枚举完全平方数**：从 $\sqrt{n}$ 开始递减枚举可能的完全平方数，减少不必要的枚举，提高效率。

### 拓展思路
同类型题或类似算法套路：
- 其他数字操作类问题，如通过删除、插入或替换数字来满足特定条件，可采用类似的暴力枚举或 DFS 方法。
- 字符串操作问题，如通过删除、替换字符使字符串满足某种规则，也可以借鉴本题的思路。

### 洛谷推荐题目
- [P1103 书本整理](https://www.luogu.com.cn/problem/P1103)：涉及对序列的操作和优化，与本题的数字操作有一定相似性。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：需要通过枚举组合来满足特定条件，可使用 DFS 解决。
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：经典的回溯算法题目，与本题的 DFS 思想类似。

### 个人心得摘录与总结
- **RNTBW**：最初想限定位数导致 WA，后来改用 `bool` 数组判断可行性并加了算位数的操作才 AC。总结为在搜索时要合理设计状态和判断条件，避免因不合理的限制导致错误。
- **千年陈皮精**：调试了一个小时，说明在实现思路时可能会遇到各种细节问题，需要耐心调试和检查。 

---
处理用时：54.75秒