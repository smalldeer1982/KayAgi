# 题目信息

# Important Exam

## 题目描述

A class of students wrote a multiple-choice test.

There are $ n $ students in the class. The test had $ m $ questions, each of them had $ 5 $ possible answers (A, B, C, D or E). There is exactly one correct answer for each question. The correct answer for question $ i $ worth $ a_i $ points. Incorrect answers are graded with zero points.

The students remember what answers they gave on the exam, but they don't know what are the correct answers. They are very optimistic, so they want to know what is the maximum possible total score of all students in the class.

## 说明/提示

In the first example, one of the most optimal test answers is "ABCD", this way the total number of points will be $ 16 $ .

In the second example, one of the most optimal test answers is "CCC", this way each question will be answered by exactly one student and the total number of points is $ 5 + 4 + 12 = 21 $ .

## 样例 #1

### 输入

```
2 4
ABCD
ABCE
1 2 3 4
```

### 输出

```
16```

## 样例 #2

### 输入

```
3 3
ABC
BCD
CDE
5 4 12
```

### 输出

```
21```

# AI分析结果

### 题目重写
# 重要考试

## 题目描述
一个班级的学生参加了一场多项选择题测试。
班级里有$n$名学生。测试有$m$道题目，每道题有$5$个可能的答案（A、B、C、D或E）。每道题都只有一个正确答案。第$i$道题的正确答案值$a_i$分，错误答案得$0$分。
学生们记得他们在考试中给出的答案，但他们不知道正确答案是什么。他们非常乐观，所以他们想知道全班学生可能获得的最大总分数是多少。

## 说明/提示
在第一个示例中，其中一个最优的测试答案是“ABCD”，这样总分数将是$16$分。
在第二个示例中，其中一个最优的测试答案是“CCC”，这样每道题都恰好有一名学生答对，总分数是$5 + 4 + 12 = 21$分。

## 样例 #1
### 输入
```
2 4
ABCD
ABCE
1 2 3 4
```
### 输出
```
16```

## 样例 #2
### 输入
```
3 3
ABC
BCD
CDE
5 4 12
```
### 输出
```
21```

### 算法分类
贪心

### 综合分析与结论
所有题解的核心思路均为贪心策略，即对于每一道题，选择学生中选择人数最多的答案作为正确答案，以使得该题得分最大，由于各题得分相互独立，这样能保证全班总分数最大。各题解在实现细节上略有不同，主要体现在数据存储和统计方式上。

### 所选的题解
 - **作者：SFWR (3星)**
    - **关键亮点**：代码简洁明了，利用数组和循环实现输入与统计，直接计算每道题使正确人数最多的答案得分并累加。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[1005][1005];
int num[1005],cnt[1005],n,m,ans;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>ch[i];
    for(int i=1;i<=m;i++)cin>>num[i];
    for(int i=0;i<m;i++)
    {
        cnt['A']=cnt['B']=cnt['C']=cnt['D']=cnt['E']=0;
        for(int j=1;j<=n;j++)cnt[ch[j][i]]++;
        ans+=(num[i+1]*(max(max(max(max(cnt['A'],cnt['B']),cnt['C']),cnt['D']),cnt['E'])));
    }
    cout<<ans;
}
```
核心实现思想：先读入学生答题情况和每题分值，然后对每道题，统计每个选项被选择的次数，找出次数最多的，乘以该题分值累加到总分中。
 - **作者：Mubuky (2星)**
    - **关键亮点**：详细解释了贪心和桶排序思想的应用，提供了自己的代码和标程。
    - **重点代码（自己的程序）**：
```cpp
#include<cstdio>
#define max(a,b) a>b?a:b
int tong[1001][5];
int main()
{
    int n,m;
    scanf("%d %d\n",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char ch;
            scanf("%c",&ch);
            tong[j][ch-'A'+1]++;
        }
        getchar();
    }
    int sum=0;
    for(int i=1;i<=m;i++){
        int a;
        scanf("%d",&a);
        int ans=0;
        for(int j=1;j<=5;j++){
            ans=max(ans,tong[i][j]);
        }
        sum+=ans*a;
    }
    printf("%d",sum);
    return 0;
}
```
核心实现思想：通过二维数组`tong`统计每道题每个选项的选择人数，然后对每道题找出选择人数最多的选项，乘以该题分值累加得到总分。
 - **作者：Waaifu_D (1星)**
    - **关键亮点**：认为本题是模拟题，代码使用字符数组存储答题情况，通过`sort`函数求每道题选择最多的选项。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>//sort必备 
#include<cstdio>
#include<iostream>
#include<string.h>
using namespace std;
int n,m,ans[6],s[1005],i,j,maxx;
char p[1002][1002];//用字符数组来储存（因为不会字符串（划掉）） 
void work()
{
    for(int i=1; i<=m;i++)
    {
        memset(ans,0,sizeof(ans));//朴素的数组清0 
        for(int j=1;j<=n;j++)//一个一个判断 
        {
        if(p[j][i]=='A') ans[1]++;if(p[j][i]=='B') ans[2]++;
        if(p[j][i]=='C') ans[3]++;if(p[j][i]=='D') ans[4]++;
        if(p[j][i]=='E') ans[5]++;
        }
        sort(ans+1,ans+1+5);//求出选的最多的选项 
        maxx+=s[i]*ans[5];//加上这题的分值 （总分数） 
    }
    cout<<maxx;//直接在函数里解决
    return; 
}
int main()
{
    cin>>n>>m;
    for(i=1; i<=n;i++)
    {
        for(j=1; j<=m;j++)
        {
            cin>>p[i][j];//每个学生的答题情况 
        }
    }
    for(i=1; i<=m;i++) cin>>s[i];//输入每题分数 
    work();//开始计算 
    return 0;
}
```
核心实现思想：先读入学生答题情况和每题分值，对每道题统计每个选项选择人数，通过`sort`排序找到选择人数最多的选项，乘以该题分值累加到总分。

### 最优关键思路或技巧
利用贪心思想，由于各题得分相互独立，所以对每道题分别处理，通过统计每个选项的选择人数，选取人数最多的选项作为该题的“正确答案”来计算得分，从而使总分最大。在实现上，可以使用数组方便地进行数据存储和统计。

### 可拓展之处
同类型题通常具有子问题相互独立且局部最优可导致全局最优的特点，类似算法套路为分析问题是否满足贪心条件，若满足则寻找局部最优策略解决问题。

### 洛谷相似题目推荐
 - P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)
 - P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199)
 - P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)

### 个人心得摘录与总结
Mubuky提到作为CF Div.2的A题比较简单，很快想到正解思路，认为这是很好的入门题目，是学习贪心的入门样例。整体来看，大家通过本题对贪心算法的应用有了一定实践和理解。 

---
处理用时：83.29秒