# 题目信息

# Before an Exam

## 题目描述

Tomorrow Peter has a Biology exam. He does not like this subject much, but $ d $ days ago he learnt that he would have to take this exam. Peter's strict parents made him prepare for the exam immediately, for this purpose he has to study not less than $ minTime_{i} $ and not more than $ maxTime_{i} $ hours per each $ i $ -th day. Moreover, they warned Peter that a day before the exam they would check how he has followed their instructions.

So, today is the day when Peter's parents ask him to show the timetable of his preparatory studies. But the boy has counted only the sum of hours $ sumTime $ spent him on preparation, and now he wants to know if he can show his parents a timetable $ sсhedule $ with $ d $ numbers, where each number $ sсhedule_{i} $ stands for the time in hours spent by Peter each $ i $ -th day on biology studies, and satisfying the limitations imposed by his parents, and at the same time the sum total of all $ schedule_{i} $ should equal to $ sumTime $ .

## 样例 #1

### 输入

```
1 48
5 7
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2 5
0 1
3 5
```

### 输出

```
YES
1 4 ```

# AI分析结果

### 题目中文重写
# 考试前

## 题目描述
明天彼得有一场生物考试。他不太喜欢这门学科，但在 $d$ 天前他得知自己必须参加这场考试。彼得严厉的父母立即要求他为考试做准备，为此，他每天学习的时间 $i$ 需满足不少于 $minTime_{i}$ 小时且不超过 $maxTime_{i}$ 小时。此外，他们警告彼得，考试前一天会检查他是否遵循了指示。

所以，今天是彼得的父母要求他出示备考时间表的日子。但男孩只算出了他备考花费的总时长 $sumTime$，现在他想知道是否能向父母展示一个包含 $d$ 个数字的时间表 $schedule$，其中每个数字 $schedule_{i}$ 代表彼得每天学习生物的时长，且满足父母设定的限制条件，同时所有 $schedule_{i}$ 的总和等于 $sumTime$。

## 样例 #1
### 输入
```
1 48
5 7
```
### 输出
```
NO
```

## 样例 #2
### 输入
```
2 5
0 1
3 5
```
### 输出
```
YES
1 4
```

### 题解综合分析与结论
这些题解主要围绕判断是否存在满足条件的学习时间表展开，核心思路是先判断总学习时间是否在每天最小学习时间总和与最大学习时间总和之间，若存在解，则使用贪心或动态规划的方法构造具体的时间表。

#### 思路对比
- **贪心算法**：大部分题解采用贪心策略，先让每天学习最少时间，再将剩余时间依次分配到每天，直到达到总学习时间或某一天达到最大学习时间。
- **动态规划**：早右昕的题解使用动态规划，设 $dp_{i,k}$ 为前 $i$ 天总用时为 $k$ 的可能性，通过状态转移方程求解。

#### 算法要点
- **贪心算法**：计算每天的最小和最大学习时间总和，判断总学习时间是否在该范围内，若有解则依次分配剩余时间。
- **动态规划**：定义状态 $dp_{i,k}$ 和 $f_{i,k}$，通过三重循环进行状态转移，最后递归输出解。

#### 解决难点
- **判断无解情况**：通过比较总学习时间与最小、最大学习时间总和来判断是否无解。
- **构造解**：贪心算法通过依次分配剩余时间构造解，动态规划通过状态转移和递归输出解。

### 评分较高的题解
1. **作者：Priori_Incantatem（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，使用贪心算法解决问题，注释详细。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int n,i,s,mins,maxs;
int a[31],b[31];//每一天的maxtime和mintime
int main(){
    cin>>n>>s;
    for(i=1;i<=n;i++)
    {
        cin>>a[i]>>b[i];
        mins+=a[i];//mintime之和
        maxs+=b[i];//maxtime之和
    }
    if(s<=maxs&&s>=mins)//如果有解的话
    {
        cout<<"YES"<<endl;
        s-=mins;
        i=1;
        while(s)   //当s!=0
        {   
            if(s>b[i]-a[i])
            {
                s-=b[i]-a[i];
                a[i]=b[i];
            }
            else 
            {
                a[i]+=s;
                s=0;
            }
            i++;
        }
        for(i=1;i<=n;i++)
        cout<<a[i]<<' ';
    }
    else cout<<"NO! YOU ARE DEAD!!!"<<endl;
    return 0;
}
```
核心实现思想：先计算每天最小和最大学习时间总和，判断是否有解。若有解，先让每天学习最小时间，再将剩余时间依次分配到每天，直到剩余时间为 0。

2. **作者：离散小波变换°（4星）**
    - **关键亮点**：思路清晰，代码使用宏定义简化循环，逻辑明确。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;
typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}
const int MAXN =30+3;
int n,s,t,L[MAXN],R[MAXN],T[MAXN];
int main(){
    n=qread(),s=qread();
    up(1,n,i){
        L[i]=qread(),R[i]=qread();
        s-=L[i],T[i]=R[i]-L[i],t+=R[i]-L[i];
    }
    if(s<0||s>t) puts("NO"),exit(0);
    puts("YES"); up(1,n,i){
        if(s>=T[i]) s-=T[i],printf("%d ",L[i]+T[i]);
        else printf("%d ",L[i]+s),s=0;
    }
    return 0;
}
```
核心实现思想：先计算每天的最小学习时间和剩余可学习时间，判断是否有解。若有解，依次考虑每一天，贪心地分配剩余时间。

3. **作者：Michael_Kong（4星）**
    - **关键亮点**：思路简单直接，代码结构清晰，对新手友好。
    - **个人心得**：特别要注意yes和no都要大写（作者在此处被坑过一次）。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1926;
int mint[maxn],maxt[maxn],n,tot;
int mins,maxs,ans[maxn];
int main(void) {
    scanf("%d %d",&n,&tot);
    for(int i=1; i<=n; i++) {
        scanf("%d %d",&mint[i],&maxt[i]);
        mins+=mint[i];
        maxs+=maxt[i];
    }
    if(tot>=mins&&tot<=maxs) {
        printf("YES\n");
    } else {
        printf("NO\n");
        return 0;
    }
    tot-=mins;
    for(int i=1; i<=n; i++) {
        if(tot-(maxt[i]-mint[i])>0) {
            tot-=maxt[i]-mint[i];
            ans[i]=maxt[i];
        }else{
            ans[i]=mint[i]+tot;
            tot=0;
        }
    }
    for(int i=1;i<=n;i++){
        printf("%d ",ans[i]);
    }
}
```
核心实现思想：先计算每天最小和最大学习时间总和，判断是否有解。若有解，先让每天学习最小时间，再将剩余时间依次分配到每天，直到剩余时间为 0。

### 最优关键思路或技巧
- **贪心策略**：先让每天学习最少时间，再将剩余时间依次分配到每天，直到达到总学习时间或某一天达到最大学习时间。
- **边界判断**：通过比较总学习时间与最小、最大学习时间总和来判断是否无解。

### 可拓展之处
同类型题可能会增加更多限制条件，如每天的学习时间必须是某个特定值的倍数，或者增加不同的科目，每个科目有不同的学习时间要求。类似算法套路可应用于资源分配问题，如将一定数量的资源分配到不同的任务中，每个任务有资源使用的上下限。

### 推荐洛谷题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法的应用。
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心算法解决分组问题。
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心算法解决区间覆盖问题。

### 个人心得摘录与总结
- **Michael_Kong**：特别要注意yes和no都要大写，作者在此处被坑过一次。总结：在做题时要仔细阅读题目要求，注意输出格式等细节。

---
处理用时：51.40秒