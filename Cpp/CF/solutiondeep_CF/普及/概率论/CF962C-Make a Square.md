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
给定一个正整数 $n$，该数没有前导零（例如，数字 04 是不正确的）。

在一次操作中，你可以删除给定整数的任意一位数字，使得结果仍然是一个没有前导零的正整数。

确定你需要对给定整数 $n$ 连续执行的最少操作次数，以使它变成某个正整数的平方；如果不可能，则报告 -1。

若存在正整数 $y$，使得 $x = y^2$，则整数 $x$ 是某个正整数的平方。

#### 说明/提示
在第一个样例中，我们应该从 8314 中删除数字 3 和 4。之后，8314 变为 81，81 是整数 9 的平方。

在第二个样例中，给定的 625 是整数 25 的平方，所以不需要删除任何数字。

在第三个样例中，不可能将 333 变成一个平方数，所以答案是 -1。

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
这些题解主要围绕如何通过最少操作次数将给定正整数 $n$ 变成某个正整数的平方展开，主要思路可分为暴力枚举和深度优先搜索（DFS）两类：
- **暴力枚举**：从 $\sqrt{n}$ 开始递减枚举可能的平方数，将其与 $n$ 的各位数字进行匹配，找到匹配位数最多的平方数，计算需删除的位数。
- **深度优先搜索**：考虑每一位数字删或不删的情况，生成所有可能的数字组合，判断其是否为完全平方数，并记录最少操作步数。

### 题解评分与选择
|作者|思路清晰度|代码可读性|优化程度|评分|
| ---- | ---- | ---- | ---- | ---- |
|GusyNight|思路清晰，详细阐述了暴力枚举的过程|代码简洁，变量命名合理|复杂度较高，未做明显优化|4星|
|Andy_Li|思路清晰，明确指出爆搜思路及注意事项|代码结构清晰，但部分变量命名不够直观|时间复杂度低，但未做进一步优化|4星|
|QianianXY|思路清晰，说明了暴力搜索的过程和处理前导零的方法|代码简洁，使用模板函数提高代码复用性|复杂度较高，未做明显优化|4星|

### 所选题解
- **GusyNight（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接通过暴力枚举找到答案。
    - **核心代码**：
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
    - **核心实现思想**：先将输入的 $n$ 每位数分解存入数组 $a$，再从 $\sqrt{n}$ 开始递减枚举可能的平方数 $x$，将 $x$ 的每位数存入数组 $b$，然后遍历数组 $a$ 与 $b$ 进行匹配，若匹配成功则输出需删除的位数，否则输出 -1。

- **Andy_Li（4星）**
    - **关键亮点**：采用深度优先搜索，考虑每一位数字删或不删的情况，思路清晰。
    - **核心代码**：
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
    - **核心实现思想**：使用深度优先搜索，通过递归函数 `dfs` 考虑每一位数字删或不删的情况，生成所有可能的数字组合，判断其是否为完全平方数，并记录最少操作步数。

- **QianianXY（4星）**
    - **关键亮点**：代码简洁，采用暴力搜索，通过按位搜索选择删或不删，并处理前导零的情况。
    - **核心代码**：
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
    - **核心实现思想**：按位搜索，选择删或不删，并记录在字符串 `str` 内，搜索到尽头后，将字符串转换为十进制数，判断开方后是否为整数，并更新答案，同时处理前导零的情况。

### 最优关键思路或技巧
- **枚举范围优化**：从 $\sqrt{n}$ 开始递减枚举可能的平方数，减少不必要的枚举。
- **深度优先搜索**：通过递归函数考虑每一位数字删或不删的情况，生成所有可能的数字组合。
- **前导零处理**：在生成数字组合时，判断是否存在前导零，避免无效计算。

### 拓展思路
同类型题或类似算法套路：
- 其他数字操作类问题，如删除数字使结果满足特定条件。
- 组合枚举类问题，通过深度优先搜索或暴力枚举生成所有可能的组合。

### 推荐题目
- [P1103 书本整理](https://www.luogu.com.cn/problem/P1103)：涉及对序列的操作和优化，需要考虑删除或保留某些元素。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合来满足特定条件，与本题的枚举思路类似。
- [P1706 全排列问题](https://www.luogu.com.cn/problem/P1706)：考察全排列的生成，与本题的枚举所有可能组合的思想相关。

### 个人心得摘录与总结
- **Andy_Li**：一开始没特判前导零，被数据 ```101``` 卡住，提示在处理数字问题时要注意前导零的情况。
- **RNTBW**：最开始想限定位数，WA 得很惨，后来改用 `bool` 数组判断一个数的可行性，加了算位数的操作才 A 掉，说明在设计算法时要考虑周全，及时调整思路。
- **千年陈皮精**：调试了一个小时，强调在实现算法时要注重细节，多进行测试和调试。

---
处理用时：52.74秒