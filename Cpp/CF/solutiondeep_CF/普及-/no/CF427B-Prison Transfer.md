# 题目信息

# Prison Transfer

## 题目描述

The prison of your city has $ n $ prisoners. As the prison can't accommodate all of them, the city mayor has decided to transfer $ c $ of the prisoners to a prison located in another city.

For this reason, he made the $ n $ prisoners to stand in a line, with a number written on their chests. The number is the severity of the crime he/she has committed. The greater the number, the more severe his/her crime was.

Then, the mayor told you to choose the $ c $ prisoners, who will be transferred to the other prison. He also imposed two conditions. They are,

- The chosen $ c $ prisoners has to form a contiguous segment of prisoners.
- Any of the chosen prisoner's crime level should not be greater then $ t $ . Because, that will make the prisoner a severe criminal and the mayor doesn't want to take the risk of his running away during the transfer.

Find the number of ways you can choose the $ c $ prisoners.

## 样例 #1

### 输入

```
4 3 3
2 3 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 1 1
2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
11 4 2
2 2 0 7 3 2 2 4 9 1 4
```

### 输出

```
6
```

# AI分析结果

### 题目中文重写
# 囚犯转移

## 题目描述
你们城市的监狱里有 $n$ 名囚犯。由于监狱无法容纳所有囚犯，市长决定将其中 $c$ 名囚犯转移到另一个城市的监狱。

为此，他让 $n$ 名囚犯站成一排，胸前写着一个数字。这个数字代表他/她所犯罪行的严重程度。数字越大，罪行越严重。

然后，市长让你选择将被转移到另一所监狱的 $c$ 名囚犯。他还提出了两个条件：
- 所选的 $c$ 名囚犯必须形成一个连续的囚犯段。
- 任何被选中的囚犯的犯罪等级都不应大于 $t$。因为这将使囚犯成为重罪犯，市长不想冒他在转移过程中逃跑的风险。

请找出你可以选择 $c$ 名囚犯的方法数。

## 样例 #1
### 输入
```
4 3 3
2 3 1 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
1 1 1
2
```
### 输出
```
0
```

## 样例 #3
### 输入
```
11 4 2
2 2 0 7 3 2 2 4 9 1 4
```
### 输出
```
6
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕找出满足条件（连续 $c$ 个囚犯且犯罪等级不大于 $t$）的选择方法数展开。思路大致可分为暴力枚举、模拟、使用数据结构（线段树、分块、st 表、笛卡尔树等）来维护区间最大值等。暴力枚举复杂度高，会超时；模拟方法简单直接，复杂度低；使用数据结构的方法能有效处理区间查询问题，但实现相对复杂。

### 所选题解
- **作者：_Emiria_ (4星)**
    - **关键亮点**：提供了多种解题思路，包括模拟、线段树、分块等，对每种方法的复杂度分析清晰，代码注释详细，方便理解。
- **作者：王熙文 (4星)**
    - **关键亮点**：使用 st 表求区间最大值，思路新颖，代码注释详细，对 st 表的构建和查询过程解释清晰。
- **作者：yzh_Error404 (4星)**
    - **关键亮点**：提供了朴素模拟和线段树两种方法，对模拟过程的解释通过样例图示，直观易懂。

### 重点代码
#### 模拟思路（作者：_Emiria_）
```cpp
#include <cstdio>

int n, t, c, k, cnt, ans;

int main(){
    scanf("%d %d %d", &n, &t, &c);
    for(int i = 1; i <= n; i++){
        scanf("%d", &k);
        if(k <= t){
            if(++cnt >= c) ans++; //囚犯数量足够，则开始累加答案
        }
        else cnt = 0; //若出现不满足的囚犯，则清空计数
    }
    printf("%d\n", ans);
    return 0;
}
```
**核心实现思想**：线性扫描输入的囚犯犯罪等级，若当前等级不大于 $t$，计数器加 1，当计数器大于等于 $c$ 时，答案加 1；若当前等级大于 $t$，计数器清零。

#### st 表思路（作者：王熙文）
```cpp
#include<bits/stdc++.h>
using namespace std;

int st[20][200010]; // 定义 st[i][j] 表示从 j 位置，向右 2^i 个数，这一段的区间最大值。区间就是 [j,j+(1<<i)-1]

int main()
{
    int n,t,c,cnt=0;
    cin>>n>>t>>c;
    int log_2=log2(c);
    for(int i=1; i<=n; ++i)
    {
        cin>>st[0][i]; // 区间 [i,i+1-1] 的最大值就是 i 本身，直接输入
    }
    for(int i=1; i<=17; ++i) // 枚举区间长度 (1<<i)
    {
        for(int j=1; j+(1<<i)-1<=n; ++j) // 枚举左端点
        {
            st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=1; i+c-1<=n; ++i) // 暴力枚举长度为 c 的区间
    {
        cnt+=(max(st[log_2][i],st[log_2][i+c-1-(1<<log_2)+1])<=t);
    }
    cout<<cnt;
    return 0;
}
```
**核心实现思想**：先构建 st 表，将区间最大值存储在 `st` 数组中，然后枚举长度为 $c$ 的区间，通过 st 表查询该区间的最大值，判断是否不大于 $t$，若是则答案加 1。

#### 朴素模拟思路（作者：yzh_Error404）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,c;
int len,ans;//len为当前子串长度，ans为子串总个数
int main()
{
    scanf("%d%d%d",&n,&t,&c);
    for(register int i=1;i<=n;i++)
    {
        int op;
        scanf("%d",&op);
        if(op>t)//遇到的元素大于t
        {
            if(len>=c)ans+=(len-c+1);//如果子串长度大于c就累加答案
            len=0;
        }
        else len++;
    }
    if(len>=c)ans+=(len-c+1);//最后把没有累加的子串加上
    printf("%d",ans);
    return 0;
}
```
**核心实现思想**：在读入数据时，记录当前连续不大于 $t$ 的元素个数，若遇到大于 $t$ 的元素，判断当前连续元素个数是否大于等于 $c$，若是则累加答案，然后将连续元素个数清零；最后处理最后一段连续元素。

### 可拓展之处
同类型题可能会有不同的条件限制，如要求选择不连续的囚犯、对犯罪等级有其他约束等。类似算法套路可用于处理其他区间查询问题，如区间和、区间最小值等，可使用线段树、st 表等数据结构进行优化。

### 推荐洛谷题目
1. [P1816 忠诚](https://www.luogu.com.cn/problem/P1816)：区间最小值查询问题，可使用 st 表或线段树解决。
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：线段树的基础应用，涉及区间修改和区间查询。
3. [P2880 [USACO07JAN]Balanced Lineup G](https://www.luogu.com.cn/problem/P2880)：区间最大值查询问题，可使用 st 表或线段树解决。

### 个人心得摘录与总结
- **作者：_Emiria_**：没想到分块和线段树差不多快，可能自己常数大。总结：不同数据结构的实际运行效率可能与理论复杂度有差异，要注意代码实现中的常数优化。

---
处理用时：45.62秒