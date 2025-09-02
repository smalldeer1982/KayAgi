# 题目信息

# Cubes for Masha

## 题目描述

Absent-minded Masha got set of $ n $ cubes for her birthday.

At each of 6 faces of each cube, there is exactly one digit from 0 to 9. Masha became interested what is the largest natural $ x $ such she can make using her new cubes all integers from 1 to $ x $ .

To make a number Masha can rotate her cubes and put them in a row. After that, she looks at upper faces of cubes from left to right and reads the number.

The number can't contain leading zeros. It's not required to use all cubes to build a number.

Pay attention: Masha can't make digit 6 from digit 9 and vice-versa using cube rotations.

## 说明/提示

In the first test case, Masha can build all numbers from 1 to 87, but she can't make 88 because there are no two cubes with digit 8.

## 样例 #1

### 输入

```
3
0 1 2 3 4 5
6 7 8 9 0 1
2 3 4 5 6 7
```

### 输出

```
87```

## 样例 #2

### 输入

```
3
0 1 3 5 6 8
1 2 4 5 7 8
2 3 4 6 7 9
```

### 输出

```
98```

# AI分析结果

### 题目中文重写
# 玛莎的方块

## 题目描述
心不在焉的玛莎生日时收到了 $n$ 个方块。

每个方块的 6 个面上都恰好有一个 0 到 9 的数字。玛莎想知道最大的自然数 $x$ 是多少，使得她可以用这些新方块拼出从 1 到 $x$ 的所有整数。

为了拼出一个数字，玛莎可以旋转方块并将它们排成一排。之后，她从左到右查看方块的上表面并读出数字。

这个数字不能包含前导零。不需要使用所有方块来组成一个数字。

注意：玛莎不能通过旋转方块将数字 6 变成 9，反之亦然。

## 说明/提示
在第一个测试用例中，玛莎可以拼出从 1 到 87 的所有数字，但她无法拼出 88，因为没有两个方块上有数字 8。

## 样例 #1
### 输入
```
3
0 1 2 3 4 5
6 7 8 9 0 1
2 3 4 5 6 7
```
### 输出
```
87
```

## 样例 #2
### 输入
```
3
0 1 3 5 6 8
1 2 4 5 7 8
2 3 4 6 7 9
```
### 输出
```
98
```

### 题解综合分析与结论
- **思路对比**：大部分题解思路类似，都是通过枚举所有可能的数字组合并标记，然后找出第一个无法拼出的数字，输出其前一个数字。如引领天下、cbyybccbyybc 等题解；LordLaffey 题解则是记录每个数字出现在哪些骰子上，通过判断一个数的各位是否能在不同骰子上找到来确定能否拼出。
- **算法要点**：核心要点是枚举和标记，通过多层循环遍历所有方块和面上的数字，组合成一位数和两位数并标记。
- **解决难点**：主要难点在于避免重复组合和正确处理一位数与两位数的情况。部分题解通过判断方块编号是否相同来避免同一方块重复组合，同时对一位数单独标记。

### 评分较高的题解
- **引领天下（4星）**
    - **关键亮点**：思路简洁，直接离散化，通过 $O(n^2)$ 暴力枚举，代码简短易读。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std ;
int a[20],n,i=1;
bool v[300];//标记出现了没有
int main(){
    cin>>n;
    for(int i=0;i<6*n;i++){cin>>a[i];v[a[i]]=1;}//读入，初始标记
    for(int i=0;i<6*n;i++)for(int j=0;j<6*n;j++)if((i!=j)&&((i/6)!=(j/6)))v[a[i]+10*a[j]]=1;//直接暴力枚举拼方块
    while(v[i++]);cout<<i-2;//因为退出循环的时候i已经++过了，所以要-2
}
```
- **yxy666（4星）**
    - **关键亮点**：思路详细，对每个步骤的枚举解释清晰，使用结构体存储方块数据。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool vis[105];//判断当前下标能否造出来，造的出来为1 
struct yan{
    int num[10];
}a[5];//用来存不同的方块的数字 
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}//快读 
int main(){
    n=read();
    for(int i=1;i<=n;i++)
    for(int j=1;j<=6;j++)a[i].num[j]=read();//我是用结构体读入数据 
    for(int i=1;i<=n;i++){//枚举第一个方块 
        for(int t=1;t<=6;t++){//枚举第一个方块的数字 
            for(int j=1;j<=n;j++){//枚举第二个方块 
                if(i==j)continue;//保证两个方块不同 
                for(int k=1;k<=6;k++){//枚举第二个方块的数字 
                    vis[a[i].num[t]]=1;vis[a[j].num[k]]=1;//三种情况，第一：本身 
                    vis[a[i].num[t]*10+a[j].num[k]]=1;//第二：x*10+y 
                    vis[a[j].num[k]*10+a[i].num[t]]=1;//第三：y*10+x 
                }
            }
        }
        
    }
    for(int i=0;i<99;i++){
        if(vis[i+1]==0){printf("%d",i);return 0;}
    }//找第一个造不出来的，输出 
    return 0;
}
```
- **LordLaffey（4星）**
    - **关键亮点**：采用不同思路，记录数字在骰子上的出现情况，通过函数判断数字能否拼出，代码逻辑清晰。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
bool num[10][10];
int n;

bool is(int x){
    int a1=x/10,a2=x%10;        //将这个数拆开
    if(a1==0)                   //如果这个数一位数，那么就只需要找它在色子里出没出现过
    {
        for(int i=1;i<=n;i++)
            if(num[a2][i])
                return true;    //这个一位数出现过
        return false;           //没出现过
    }
    for(int i=1;i<=n;i++)       //枚举每个色子
    {
        for(int j=1;j<=n;j++)
        {
            if(j==i)            //这个数的两位不能在同一个色子上
                continue;
            if(num[a1][i]&&num[a2][j])  //可以在两个不同的色子上分别找到x的十位和个位
                return true;
        }
    }
    return false;               //没有找到
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=6;j++)
        {
            int a;
            scanf("%d",&a);
            num[a][i]=true;         //记录a在第i个色子可以找到
        }
    }
    for(int i=1;i<=100;i++)         //枚举每个数可不可以拼出来
    {
        if(!is(i))
        {
            cout<<i-1;              //如果拼不出来，上一个数则为解
            return 0;
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
- 使用标记数组记录能拼出的数字，避免重复计算。
- 通过多层循环枚举所有可能的方块组合，生成一位数和两位数。
- 对于不同方块的组合，通过判断方块编号避免同一方块重复组合。

### 可拓展之处
同类型题可能会增加方块数量、面的数量或数字范围，解题思路依然是枚举和标记，但可能需要更高效的枚举方式或数据结构。类似算法套路可用于解决组合问题，如从多个集合中选取元素组成特定组合。

### 推荐洛谷题目
- P1008 三连击
- P1036 选数
- P1217 [USACO1.5]回文质数 Prime Palindromes

### 个人心得摘录与总结
- **cbyybccbyybc**：在处理单独骰子时容易出错，需要特判将单独骰子的数字标记。
- **yxy666**：一开始理解错题意，看成求能组合的最大值，浪费了时间，提醒做题时要仔细审题。
- **yutong_Seafloor**：因为对“最大”的理解错误，导致样例多次出错，强调理解题意的重要性。 

---
处理用时：45.82秒