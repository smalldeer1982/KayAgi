# 题目信息

# [USACO11FEB] Best Parenthesis S

## 题目描述

Recently, the cows have been competing with strings of balanced parentheses and comparing them with each other to see who has the best one.

Such strings are scored as follows (all strings are balanced): the string '()' has score 1; if 'A' has score s(A) then '(A)' has score 2\*s(A); and if 'A' and 'B' have scores s(A) and s(B), respectively, then 'AB' has score s(A)+s(B). For example, s('(())()') = s('(())')+s('()') = 2\*s('()')+1 = 2\*1+1 = 3.

Bessie wants to beat all of her fellow cows, so she needs to calculate the score of some strings. Given a string of balanced parentheses of length N (2 <= N <= 100,000), help Bessie compute its score.

给定一个只包含左右括号的字符串，得分规则如下：

如果一对括号内没有括号，那么这对括号的得分为1；如果两对括号互不包含（即并列存在），那这两对括号的得分相加；如果括号内包含一对括号，那么这个括号的得分纪为内部括号序列的得分\*2。

例如：对于这样一个字符串："() ()"，两对括号并列存在，则得分为1+1=2;

而对于这样一个字符串："(())"，最外层的括号内层包含一对括号，则得分为2\*1=2.


Bessie想击败所有同事的牛，所以她需要计算某个字符串的评分。给定一个长度为n、只包含括号的字符串（2≤N≤100000），计算其得分帮助Bessie。


## 说明/提示

This corresponds to the string "(())()". 

As discussed above.

输出答案要mod12345678910


## 样例 #1

### 输入

```
6 
0 
0 
1 
1 
0 
1 
```

### 输出

```
3 
```

# AI分析结果

### 综合分析与结论
这些题解围绕计算括号字符串得分展开，思路各有不同，但大多借助栈或递归实现。栈的使用可有效处理括号匹配，递归则能清晰模拟括号嵌套的计算逻辑。各题解在代码复杂度、可读性和优化程度上存在差异。

### 所选题解
- **作者：kkxhh（5星）**
    - **关键亮点**：思路清晰易懂，通过数组模拟栈，根据当前层的状态更新上一层的得分，代码简洁高效。
    - **核心代码**：
```cpp
#include <cstdio>
using namespace std;

typedef long long ll;

const ll mod=12345678910;
ll n,t=0,s[50010]={0},a;

int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a);
        if(!a) t++;
        else{
            if(!s[t]) s[t-1]=(s[t-1]+1)%mod,s[t--]=0;
            else s[t-1]=(s[t-1]+s[t]*2)%mod,s[t--]=0;
        }
    }
    printf("%lld",s[0]);
    return 0;
}
```
    - **核心思想**：`s[i]` 表示第 `i` 层目前的数值，读到左括号增加一层，读到右括号时，若当前层无得分则给上一层加1，否则将当前层得分乘2加到上一层。

- **作者：Loser_King（4星）**
    - **关键亮点**：采用递归实现，先预处理出所有左括号对应的右括号，再通过递归计算得分，思路清晰，代码简洁。
    - **核心代码**：
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int const MOD=12345678910ll;
int n,a[233333],brk[233333];
stack<int>s;
int solve(int l,int r){
    int ans=0;
    for(int i=l;i<=r;i=brk[i]+1)
        if(brk[i]==i+1)ans++;
        else ans+=solve(i+1,brk[i]-1)*2,ans%=MOD;
    return ans%MOD;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(!a[i])s.push(i);
        else brk[s.top()]=i,s.pop();
    }
    cout<<solve(1,n);
}
```
    - **核心思想**：预处理出所有左括号对应的右括号，递归计算 `solve(l, r)` 区间的得分，若为 `()` 形式则得分加1，否则加上内部区间得分的2倍。

- **作者：jzcrq（4星）**
    - **关键亮点**：详细解释了栈的使用思路，分别给出手写栈和STL栈的实现，代码规范。
    - **核心代码（STL栈）**：
```cpp
#include <stack>
#include <cstdio>
#define int long long
using namespace std;

const int mod=12345678910;
int n,in,tmp,tmp2;
stack<int> s;

signed main()
{
    scanf("%lld",&n);
    s.push(0);
    for (int i=1;i<=n;i++)
    {
        scanf("%lld",&in);
        if (in)
        {
            if (s.top())
            {
                tmp=(s.top()<<1)%mod;
                s.pop();
                tmp2=tmp+s.top();
                s.pop();
                s.push(tmp2);
            }
            else
            {
                s.pop();
                tmp=s.top()+1;
                s.pop();
                s.push(tmp);
            }
        }
        else s.push(0);
    }
    printf("%lld",s.top()%mod);
    return 0;
}
```
    - **核心思想**：用栈存储待匹配的 `0` 所对应的 `01` 序列的贡献，遇到 `0` 压入栈，遇到 `1` 时根据栈顶情况更新栈顶元素。

### 最优关键思路或技巧
- **栈的使用**：多数题解借助栈处理括号匹配，能有效模拟括号嵌套关系，方便计算得分。
- **递归求解**：递归可清晰模拟括号嵌套的计算逻辑，将大问题分解为小问题。

### 可拓展之处
同类型题如括号匹配的合法性判断、计算括号嵌套深度等，可使用栈或递归解决。类似算法套路可用于处理表达式求值、树形结构遍历等问题。

### 推荐题目
- P1739 表达式括号匹配
- P1449 后缀表达式
- P1981 表达式求值

### 个人心得摘录与总结
- **作者：Minclxc**：认为这题是裸模拟，但递归较多，调试了很久。总结为递归模拟虽思路清晰，但实现时需注意细节，可能会花费较多调试时间。 

---
处理用时：31.82秒