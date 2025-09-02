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
在一所规模不大但充满自豪感的高中里，校方决定在ACM国际大学生程序设计竞赛中取得佳绩。为此，学校需要尽可能多地组建三人团队。由于只有6名学生愿意参赛，学校决定组建两支队伍。

在一次练习赛之后，第 $i$ 名参赛学生获得了 $a_{i}$ 分。团队得分定义为其成员得分之和。学校管理层想知道是否有可能组建两支得分相同的队伍。你的任务就是回答这个问题。

## 说明/提示
在第一个样例中，第一支队伍可以由第1、2、6名参赛学生组成，第二支队伍由第3、4、5名参赛学生组成：两支队伍的得分均为 $1 + 3 + 1 = 2 + 1 + 2 = 5$。

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
这些题解的核心目标都是判断给定的6个数能否分成两组，每组3个数且两组和相等。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|infinities|暴力生成所有分组情况，用if语句判断是否有相等的分组|用多层循环生成所有可能的分组组合，将结果存储在文件中并复制到代码的if语句中|避免重复且不遗漏地生成所有分组情况|1星|
|chufuzhe|先计算总和，若总和为偶数则枚举第一组的三个数，判断其和是否等于总和的一半|先判断总和奇偶性，再用三层循环枚举第一组的三个数|避免重复枚举|4星|
|Dog_Two|对6个数字作全排列，若前三个数字之和等于总和的一半则输出YES|使用`next_permutation`函数进行全排列，先判断总和奇偶性|处理全排列和总和奇偶性|4星|
|hello2020|枚举6个数中选3个数的所有组合，判断其和是否等于总和的一半|用三层循环枚举组合，先判断总和奇偶性|避免重复枚举|4星|
|AmaZingFantasy|使用深度优先搜索算法枚举是否将学生分到第一组|定义变量记录总和和已选学生数，根据条件剪枝和判断|深度优先搜索的实现和剪枝|3星|
|jijidawang|枚举所有可能的三元组，两两比较|列出所有可能的三元组并两两枚举|确定所有可能的三元组|2星|

### 所选题解
- **chufuzhe（4星）**
    - 关键亮点：思路清晰，先判断总和奇偶性减少不必要的枚举，代码可读性高。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[6];
int main()
{
    ios::sync_with_stdio(false);
    bool ans = 0;
    int s = 0;
    for(register int i = 0; i < 6; i++)
    {
        cin >> a[i];
        s += a[i];
    }
    if(s % 2 == 0)
    {
        s /= 2;
        for(register int i = 0; i < 6; i++)
            for(register int j = 0; j < 6; j++)
                if(i!= j)
                    for(register int k = 0; k < 6; k++)
                        if(i!= k && j!= k)
                            if(a[i] + a[j] + a[k] == s)
                            {
                                ans = 1;
                                break;
                            }
    }
    if(!ans) puts("NO");
    else puts("YES");
    return 0;
}
```
核心实现思想：先计算6个数的总和，若总和为偶数则计算每组的目标和，然后用三层循环枚举第一组的三个数，判断其和是否等于目标和。

- **Dog_Two（4星）**
    - 关键亮点：使用全排列函数，代码简洁。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a[7], sum = 0;
    for(int i = 1; i <= 6; ++i) cin >> a[i], sum += a[i];
    if(sum & 1){
        puts("NO");
        return 0;
    }
    sort(a + 1, a + 6);
    bool if_ans = false;
    do{
        int val = a[1] + a[2] + a[3];
        if_ans = val == sum / 2;	
    }while(next_permutation(a + 1, a + 6) and!if_ans);
    puts(if_ans? "YES" : "NO");
    return 0;
}
```
核心实现思想：先计算总和，若总和为奇数则直接输出NO，否则对6个数进行全排列，每次判断前三个数的和是否等于总和的一半。

- **hello2020（4星）**
    - 关键亮点：枚举组合时避免了重复，代码简单易懂。
    - 核心代码：
```cpp
#include<iostream>
using namespace std;
int main(){
    int a[7], sum = 0;
    for (int i = 1; i <= 6; i++)
        cin >> a[i], sum += a[i];
    if (sum % 2 == 1){
        cout << "NO" << endl;
        return 0;
    }
    sum /= 2;
    for (int i = 1; i <= 4; i++)
        for (int j = i + 1; j <= 5; j++)
            for (int k = j + 1; k <= 6; k++)
                if (a[i] + a[j] + a[k] == sum){
                    cout << "YES" << endl;
                    return 0;
                }
    cout << "NO" << endl;
    return 0;
}
```
核心实现思想：先计算总和，若总和为奇数则直接输出NO，否则用三层循环枚举6个数中选3个数的组合，判断其和是否等于总和的一半。

### 最优关键思路或技巧
- 先判断总和的奇偶性，若为奇数则直接输出NO，减少不必要的计算。
- 使用循环枚举组合时，通过合理设置循环条件避免重复枚举。
- 利用全排列函数简化组合的枚举过程。

### 可拓展之处
同类型题可以是判断给定的 $n$ 个数能否分成 $m$ 组，每组 $k$ 个数且每组和相等。可以使用类似的枚举或搜索算法，根据具体情况进行优化。

### 推荐洛谷题目
- P1036 [NOIP2002 普及组] 选数：从 $n$ 个数中选 $k$ 个数，判断它们的和是否为素数。
- P1100 高低位交换：将一个无符号整数的高16位和低16位交换。
- P1217 [USACO1.5] 回文质数 Prime Palindromes：找出指定范围内的回文质数。

### 个人心得摘录与总结
- infinities：提到程序有重复，可自行优化，还吐槽了题目难度的恶意评分。总结：在写代码时要注意代码的简洁性和可优化性，同时对题目难度的评价要有理性认识。
- Dog_Two：吐槽本题难度被评价过高。总结：题目难度评价可能存在偏差，要根据实际情况分析题目难度。
- hello2020：认为题目太水，是暴力模拟。总结：对于简单题目可以采用暴力方法解决，但也要思考是否有更优的解法。 

---
处理用时：36.91秒