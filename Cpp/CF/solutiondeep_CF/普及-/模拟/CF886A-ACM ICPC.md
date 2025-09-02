# 题目信息

# ACM ICPC

## 题目描述

In a small but very proud high school it was decided to win ACM ICPC. This goal requires to compose as many teams of three as possible, but since there were only $ 6 $ students who wished to participate, the decision was to build exactly two teams.

After practice competition, participant number $ i $ got a score of $ a_{i} $ . Team score is defined as sum of scores of its participants. High school management is interested if it's possible to build two teams with equal scores. Your task is to answer that question.

## 说明/提示

In the first sample, first team can be composed of $ 1 $ st, $ 2 $ nd and $ 6 $ th participant, second — of $ 3 $ rd, $ 4 $ th and $ 5 $ th: team scores are $ 1+3+1=2+1+2=5 $ .

In the second sample, score of participant number $ 6 $ is too high: his team score will be definitely greater.

## 样例 #1

### 输入

```
1 3 2 1 2 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1 1 1 1 1 99
```

### 输出

```
NO
```

# AI分析结果

### 题目中文重写
# ACM国际大学生程序设计竞赛

## 题目描述
在一所规模不大但充满自豪的高中里，校方决定要在ACM国际大学生程序设计竞赛（ACM ICPC）中取得佳绩。为了实现这一目标，学校打算尽可能多地组建三人团队。由于只有6名学生愿意参赛，最终决定组建两支队伍。

在一次练习赛之后，第i名参赛学生获得了$a_{i}$分。团队得分定义为其成员得分之和。学校管理层想知道是否有可能组建两支得分相等的队伍。你的任务就是回答这个问题。

## 说明/提示
在第一个样例中，第一支队伍可以由第1、2和6名参赛学生组成，第二支队伍由第3、4和5名参赛学生组成：两支队伍的得分均为$1 + 3 + 1 = 2 + 1 + 2 = 5$。

在第二个样例中，第6名参赛学生的得分过高：他所在队伍的得分肯定会更高。

## 样例 #1
### 输入
```
1 3 2 1 2 1
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
1 1 1 1 1 99
```
### 输出
```
NO
```

### 综合分析与结论
这些题解的核心目标都是判断给定的6个数能否分成两组，每组3个数且两组和相等。思路上，主要围绕暴力枚举和剪枝展开。
- **infinities**：直接暴力生成所有分组情况，将其列成“表”，通过判断表中是否有满足两组和相等的情况来输出结果。这种方法代码重复度高，效率低。
- **chufuzhe**：先计算总和，若总和为奇数则直接输出NO，若为偶数则枚举第一组的三个数，判断其和是否等于总和的一半。
- **Dog_Two**：对6个数字进行全排列，若前三个数字之和等于总和的一半则输出YES，同时考虑总和为奇数的情况。
- **hello2020**：同样先判断总和奇偶性，若为偶数则暴力枚举6个数中选3个数的组合，判断其和是否等于总和一半。
- **AmaZingFantasy**：使用深度优先搜索（DFS）算法，枚举每个学生是否进入第一组，若第一组选了3个人且和等于总和一半则输出YES。
- **jijidawang**：提出枚举所有可能的三元组，再两两枚举判断，但未给出具体代码实现。

### 所选题解
- **chufuzhe（4星）**
    - **关键亮点**：思路清晰，先对总和进行奇偶判断剪枝，再通过三重循环枚举第一组的三个数，代码可读性高。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[6];
int main()
{
    ios::sync_with_stdio(false);
    bool ans=0;
    int s=0;
    for(register int i=0;i<6;i++)
    {
        cin>>a[i];
        s+=a[i];
    }
    if(s%2==0)
    {
        s/=2;
        for(register int i=0;i<6;i++)
            for(register int j=0;j<6;j++)
                if(i!=j)
                    for(register int k=0;k<6;k++)
                        if(i!=k && j!=k)
                            if(a[i]+a[j]+a[k]==s)
                            {
                                ans=1;
                                break;
                            }
    }
    if(!ans) puts("NO");
    else puts("YES");
    return 0;
}
```
- **Dog_Two（4星）**
    - **关键亮点**：利用全排列函数`next_permutation`，代码简洁，同时考虑了总和为奇数的情况进行剪枝。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[7],sum=0;
    for(int i=1;i<=6;++i) cin>>a[i],sum+=a[i];
    if(sum&1){
        puts("NO");
        return 0;
    }
    sort(a+1,a+6);
    bool if_ans=false;
    do{
        int val=a[1]+a[2]+a[3];
        if_ans=val==sum/2;	
    }while(next_permutation(a+1,a+6) and!if_ans);
    puts(if_ans?"YES":"NO");
    return 0;
}
```
- **hello2020（4星）**
    - **关键亮点**：先判断总和奇偶性，然后通过三重循环枚举6个数中选3个数的组合，避免了重复枚举，代码简洁高效。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int main(){
    int a[7],sum=0;
    for (int i=1;i<=6;i++)
        cin>>a[i],sum+=a[i];
    if (sum%2==1){
        cout<<"NO"<<endl;
        return 0;
    }
    sum/=2;
    for (int i=1;i<=4;i++)
        for (int j=i+1;j<=5;j++)
            for (int k=j+1;k<=6;k++)
                if (a[i]+a[j]+a[k]==sum){
                    cout<<"YES"<<endl;
                    return 0;
                }
    cout<<"NO"<<endl;
    return 0;
}
```

### 最优关键思路或技巧
- 先判断总和的奇偶性，若为奇数则直接输出NO，可避免不必要的枚举。
- 利用循环枚举组合或全排列，判断是否存在满足条件的分组。

### 可拓展之处
同类型题如将n个数分成m组，每组和相等，可使用回溯法、动态规划等算法。类似算法套路有子集和问题、背包问题等。

### 推荐洛谷题目
- P1734 最大约数和
- P1036 选数
- P2392 kkksc03考前临时抱佛脚

### 个人心得摘录与总结
- infinities：提到程序有重复可优化，同时吐槽了题目难度的恶意评分。
- Dog_Two：感慨本题难度被高估。
- hello2020：认为本题太水，使用暴力模拟即可。 

---
处理用时：34.70秒