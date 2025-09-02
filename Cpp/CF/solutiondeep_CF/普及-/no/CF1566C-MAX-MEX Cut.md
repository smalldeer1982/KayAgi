# 题目信息

# MAX-MEX Cut

## 题目描述

A binary string is a string that consists of characters $ 0 $ and $ 1 $ . A bi-table is a table that has exactly two rows of equal length, each being a binary string.

Let $ \operatorname{MEX} $ of a bi-table be the smallest digit among $ 0 $ , $ 1 $ , or $ 2 $ that does not occur in the bi-table. For example, $ \operatorname{MEX} $ for $ \begin{bmatrix} 0011\\ 1010 \end{bmatrix} $ is $ 2 $ , because $ 0 $ and $ 1 $ occur in the bi-table at least once. $ \operatorname{MEX} $ for $ \begin{bmatrix} 111\\ 111 \end{bmatrix} $ is $ 0 $ , because $ 0 $ and $ 2 $ do not occur in the bi-table, and $ 0 < 2 $ .

You are given a bi-table with $ n $ columns. You should cut it into any number of bi-tables (each consisting of consecutive columns) so that each column is in exactly one bi-table. It is possible to cut the bi-table into a single bi-table — the whole bi-table.

What is the maximal sum of $ \operatorname{MEX} $ of all resulting bi-tables can be?

## 说明/提示

In the first test case you can cut the bi-table as follows:

- $ \begin{bmatrix} 0\\ 1 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 2 $ .
- $ \begin{bmatrix} 10\\ 10 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 2 $ .
- $ \begin{bmatrix} 1\\ 1 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 0 $ .
- $ \begin{bmatrix} 0\\ 1 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 2 $ .
- $ \begin{bmatrix} 0\\ 0 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 1 $ .
- $ \begin{bmatrix} 0\\ 0 \end{bmatrix} $ , its $ \operatorname{MEX} $ is $ 1 $ .

The sum of $ \operatorname{MEX} $ is $ 8 $ .

## 样例 #1

### 输入

```
4
7
0101000
1101100
5
01100
10101
2
01
01
6
000000
111111```

### 输出

```
8
8
2
12```

# AI分析结果

### 题目内容
# MAX - MEX Cut

## 题目描述
一个二进制字符串是由字符0和1组成的字符串。一个双表是一个恰好有两行且长度相等的表格，每行都是一个二进制字符串。

设一个双表的MEX是0、1或2中未在该双表中出现的最小数字。例如，对于$\begin{bmatrix} 0011\\ 1010 \end{bmatrix}$，MEX是2，因为0和1至少在该双表中出现一次。对于$\begin{bmatrix} 111\\ 111 \end{bmatrix}$，MEX是0，因为0和2未在该双表中出现，且0 < 2。

给定一个有n列的双表。你应该将其切割成任意数量的双表（每个双表由连续的列组成），使得每一列都恰好在一个双表中。也可以将双表切割成单个双表，即整个双表。

所有结果双表的MEX之和的最大值是多少？

## 说明/提示
在第一个测试用例中，你可以按如下方式切割双表：
 - $\begin{bmatrix} 0\\ 1 \end{bmatrix}$，其MEX是2。
 - $\begin{bmatrix} 10\\ 10 \end{bmatrix}$，其MEX是2。
 - $\begin{bmatrix} 1\\ 1 \end{bmatrix}$，其MEX是0。
 - $\begin{bmatrix} 0\\ 1 \end{bmatrix}$，其MEX是2。
 - $\begin{bmatrix} 0\\ 0 \end{bmatrix}$，其MEX是1。
 - $\begin{bmatrix} 0\\ 0 \end{bmatrix}$，其MEX是1。

MEX之和是8。

## 样例 #1
### 输入
```
4
7
0101000
1101100
5
01100
10101
2
01
01
6
000000
111111
```
### 输出
```
8
8
2
12
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解都围绕贪心策略展开，核心思路是通过合理划分双表的列，使MEX之和最大。主要的贪心策略有：对于一列中上下两个数为0和1的情况，直接将这一列单独划分，其MEX为2；对于全0或全1的列，根据相邻列的情况决定是否与相邻列合并划分，以获取更大的MEX值。不同题解在实现细节和代码风格上有所差异。

### 所选的题解
- **作者：wangqinyan (赞：3)  星级：4星**
    - **关键亮点**：思路清晰，通过对每一列的三种情况进行分析，直接在遍历过程中计算答案，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1,s2;
long long ans,x,n,t;
bool p1,p2;
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        cin>>s1>>s2;
        ans=0,x=-1;
        for(int i=0;i<n;i++)
        {
            p1=((s1[i]=='0')|(s2[i]=='0'));
            p2=((s1[i]=='1')|(s2[i]=='1'));
            if(p1&&p2)x=2,ans+=x;
            else if(p1==false)
            {
                if(x==1)ans++,x=-1;
                else x=0;
            }
            else
            {
                ans++;
                if(x==0)ans++,x=-1;
                else x=1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：遍历每一列，根据当前列上下数字情况更新答案。如果当前列同时有0和1，直接加2；如果全为0或全为1，结合前一列情况判断是否能增加答案。
- **作者：Big_Dinosaur (赞：2)  星级：4星**
    - **关键亮点**：先记录每列单独切开的价值，再通过分类讨论进行贪心，逻辑清晰，代码结构良好。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Dino{
inline int r(){
int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}return x*f;
}
int n,t,a[114514];
inline void bigdino(){
n=r();string x,y;cin>>x>>y;for(int i=1;i<=n;++i)
if(x[i-1]!=y[i-1])a[i]=2;else if(x[i-1]=='1')a[i]=0;else a[i]=1;a[n+1]=3;
int ans=0;for(int i=1;i<=n;++i){
if(a[i]==2)ans+=2;
else if((a[i]==1&&a[i+1]==0)||(a[i]==0&&a[i+1]==1)){ans+=2;a[i+1]=-1;}
else if(a[i]!=-1)ans+=a[i];
}cout<<ans<<endl;
}
inline void _(){
t=r();while(t--)bigdino();
}
}
signed main(){Dino::_();}
```
    - **核心实现思想**：先预处理每列单独切开的价值，遍历过程中，若当前列价值为2直接加2；若当前列价值为0或1，且下一列价值为2减去当前列价值，则两列合并加2，否则单独切开加当前列价值。
- **作者：Jur_Cai (赞：2)  星级：4星**
    - **关键亮点**：通过标记前面是否出现过0和1来进行贪心计算，代码简洁高效。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char s1[100005],s2[100005];
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int n,ans=0,flag0=0,flag1=0;
        scanf("%d",&n);
        scanf("%s%s",s1+1,s2+1);
        for(int i=1;i<=n;i++) {
            if(s1[i]=='0'||s2[i]=='0'){
                if(flag0) ans++;//前面有多余的0
                flag0=1;
            }
            if(s1[i]=='1'||s2[i]=='1') flag1=1;
            if(flag1&&flag0) {
                flag1=flag0=0;
                ans+=2; 
            }
        }
        if(flag0) ans++;
        cout<<ans<<'\n'; 
    }
}
```
    - **核心实现思想**：遍历每一列，若当前列有0则根据前面是否有0决定是否加1，同时标记有0；若有1则标记有1。当同时有0和1标记时，加2并重置标记，最后若还有0标记则再加1。

### 最优关键思路或技巧
这些题解的最优关键思路在于对不同列的数字组合情况进行细致分析，利用贪心策略，优先选取能使MEX值最大的划分方式。具体技巧包括对每列情况的分类讨论、结合相邻列情况进行决策以及通过标记或预处理简化计算过程。

### 可拓展之处
同类型题可关注涉及最优划分、最大/最小化某种值的贪心题目。类似算法套路是对不同情况进行分类，根据目标值的优化方向，在每一步决策中选择最优的操作，如本题根据MEX值的计算规则，选择合适的列划分方式。

### 洛谷相似题目推荐
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略选择合并顺序以最小化总代价，与本题类似，都需要在不同操作选择中找出最优决策。
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及双方博弈下的贪心策略，需要分析不同局面下的最优选择，锻炼贪心思维。
 - [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：可以用归并排序结合贪心思想来统计逆序对数量，与本题一样，需要运用一定的算法技巧来解决问题。 

---
处理用时：91.62秒