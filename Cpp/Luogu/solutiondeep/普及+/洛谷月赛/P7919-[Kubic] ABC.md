# 题目信息

# [Kubic] ABC

## 题目背景

建议先看 D 题题目背景。

## 题目描述

给定一个长度为 $n$ 的只包含 $\texttt{A,B,C}$ 的字符串 $S$，你可以进行若干次操作，每次操作为：

- 先选择一个区间 $[l,r]$，你需要保证 $1\le l\le r\le n$。

- 再选择三个字符 $pA,pB,pC\in\{\texttt{A,B,C}\}$，并将 $S_{l\dots r}$ 中所有 $\texttt{A}$ 变为 $pA$，所有 $\texttt{B}$ 变为 $pB$，所有 $\texttt{C}$ 变为 $pC$，**$pA,pB,pC$ 可以相等**。

求出**最少**需要进行多少次操作才能使得 $S$ 中**任意相邻两个字符不同**，并**输出构造方案**。

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 5\times 10^3,S_i\in\{\texttt{A,B,C}\}$。

||分值|$n$|特殊性质|
|:-:|:-:|:-:|:-:|
|$\operatorname{Subtask}1$|$1$|无特殊限制|$\forall i\in[1,n),S_i\neq S_{i+1}$|
|$\operatorname{Subtask}2$|$19$|$\le 10$|无|
|$\operatorname{Subtask}3$|$10$|无特殊限制|$S_i=\texttt{A}$|
|$\operatorname{Subtask}4$|$20$|无特殊限制|$S_i\in\{\texttt{A,B}\}$|
|$\operatorname{Subtask}5$|$20$|$\le 100$|无|
|$\operatorname{Subtask}6$|$30$|无特殊限制|无|

### 评分方法

以下情况将会使你在该测试点获得 $0$ 分：

- 输出格式不满足要求。

- 输出多余信息（包括空格和换行符）

- 构造的方案操作次数与标准答案不同。

- 构造的方案不符合题目要求。

- 时间超限。

如果没有上述情况，你在该测试点获得满分。

**保证 SPJ 占用不超过 $100\operatorname{ms},10\operatorname{MB}$**。

### 样例解释 1

一种操作过程如下：

`ABBAA`

`ABABA`

可以证明没有更优的方案。

### 样例解释 2

初始序列已经符合题目要求，直接输出一行 $0$ 即可。

## 样例 #1

### 输入

```
5
ABBAA```

### 输出

```
1
3 4 BAC```

## 样例 #2

### 输入

```
5
ABCBA```

### 输出

```
0```

# AI分析结果

• 综合分析与结论：这些题解思路大致相同，均基于对操作性质的分析，得出一次操作最多使相邻相同对数减少2的结论，进而确定最少操作次数为 $\left\lceil\dfrac{x}{2}\right\rceil$（$x$ 为初始相邻相同对数）。构造方案上，基本通过双指针寻找相邻相同对并配对处理，对于奇数个相同对的剩余一对单独处理。不同之处主要在细节处理和代码实现风格上。
• 所选的题解：
  - **作者：VinstaG173 (5星)**
    - **关键亮点**：思路清晰，先给出最少操作次数的理论依据，再详细说明构造方案，代码简洁明了，时间复杂度为 $O(n)$ 符合要求。
    - **重点代码**：
```cpp
#include<cstdio>
int n,x,y,t;
char s[5003];
int l[5003],r[5003];
int main()
{
    scanf(" %d %s",&n,s+1);x=1,y=n;
    while(x<y)
    {
        while(x<y&&s[x]!=s[x+1])++x;
        while(y>x&&s[y]!=s[y-1])--y;
        if(x==y)break;
        l[++t]=++x,r[t]=--y;
    }
    printf("%d\n",t);
    if(l[t]>r[t])r[t]=n;
    for(int i=1;i<=t;++i)printf("%d %d BCA\n",l[i],r[i]);
    return 0;
}
```
    - **核心实现思想**：通过双指针 $x$ 和 $y$ 分别从字符串两端向中间移动，寻找相邻相同对，将其配对记录为操作区间，最后处理可能剩余的单独一对，每次操作采用固定变换 `BCA`。
  - **作者：kkio (4星)**
    - **关键亮点**：思路阐述简洁，代码使用 `vector` 存储操作区间，整体结构清晰，同样采用双指针寻找相邻相同对并配对处理。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
char s[5005]; 
vector<pair<int,int> > ans;
int main()
{
    cin>>n;
    int l=1,r=n;
    cin>>s+1;
    while(1)
    {for(;l<r&&s[l]!=s[l+1];l++);for(;l<r&&s[r]!=s[r-1];r--);
        if(l>=r)break;
        int cl=++l,cr=((--r)<l?n:r); 
        ans.push_back(make_pair(cl,cr));
    }
    printf("%d\n",ans.size());
    for(int i=0;i<ans.size();i++)
        printf("%d %d CAB\n",ans[i].first,ans[i].second); 
}
```
    - **核心实现思想**：利用双指针 `l` 和 `r` 从两端向中间遍历字符串，找到相邻相同对并确定操作区间，将区间记录到 `vector` 中，最后输出操作次数和每个操作区间及变换方式 `CAB`。
  - **作者：int08 (4星)**
    - **关键亮点**：先分析 $pA$、$pB$、$pC$ 的取值，明确应使其互不相同，再给出操作次数和构造方案，逻辑连贯，代码简洁。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,j=-1,ans,a[2][5006];char s[5003];
int main()
{
    cin>>n;
    scanf("%s",s);
    for(;;)
    {
        i=j+1;
        while(s[i]!=s[i+1]&&i<n-1) {i++;}
        if(i>=n-1) break;
        j=i+1;
        while(s[j]!=s[j+1]&&j<n-1) {j++;}                         
        ans++;a[0][ans]=i+2;a[1][ans]=j+1;
    }
    cout<<ans<<endl;
    for(i=1;i<=ans;i++) cout<<a[0][i]<<" "<<a[1][i]<<" BCA\n";
    return 0;
} 
```
    - **核心实现思想**：通过两个嵌套循环，外层循环持续寻找相邻相同对，内层循环分别用 `while` 找到前后相邻相同对的位置，记录操作区间，每次操作采用 `BCA` 变换。
• 最优关键思路或技巧：利用操作不改变区间内部（除两端）相邻字符相同性这一性质，确定最少操作次数；通过双指针法寻找并配对相邻相同对，简化构造方案。每次操作采用固定的字符变换方式（如 `BCA`）可避免复杂讨论。
• 可拓展之处：同类型题通常围绕字符串操作、区间操作以及最小化操作次数展开。类似算法套路是先分析操作对目标状态的影响，确定最少操作次数的下限，再通过贪心或构造法找到具体方案。
• 相似知识点洛谷题目：
  - [P1249 最大乘积](https://www.luogu.com.cn/problem/P1249)：涉及数字拆分和乘积最大化，需分析操作性质并通过贪心策略求解。
  - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：双指针法结合贪心思想解决分组问题，与本题双指针寻找配对元素思路类似。
  - [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：通过对区间操作的分析，贪心选择区间以满足特定条件，与本题对操作区间的分析和选择思路有相似之处。
• 个人心得摘录与总结：
  - **作者：int08**：输入时避免连用 `getchar()`，最好也不要用字符串 `cin`，可能是因为这些输入方式在处理本题数据时可能出现问题，如输入格式不符或效率较低。 

---
处理用时：58.82秒