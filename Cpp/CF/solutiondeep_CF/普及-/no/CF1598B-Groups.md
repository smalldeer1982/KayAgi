# 题目信息

# Groups

## 题目描述

$ n $ students attended the first meeting of the Berland SU programming course ( $ n $ is even). All students will be divided into two groups. Each group will be attending exactly one lesson each week during one of the five working days (Monday, Tuesday, Wednesday, Thursday and Friday), and the days chosen for the groups must be different. Furthermore, both groups should contain the same number of students.

Each student has filled a survey in which they told which days of the week are convenient for them to attend a lesson, and which are not.

Your task is to determine if it is possible to choose two different week days to schedule the lessons for the group (the first group will attend the lesson on the first chosen day, the second group will attend the lesson on the second chosen day), and divide the students into two groups, so the groups have equal sizes, and for each student, the chosen lesson day for their group is convenient.

## 说明/提示

In the first testcase, there is a way to meet all the constraints. For example, the first group can consist of the first and the third students, they will attend the lessons on Thursday (the fourth day); the second group can consist of the second and the fourth students, and they will attend the lessons on Tuesday (the second day).

In the second testcase, it is impossible to divide the students into groups so they attend the lessons on different days.

## 样例 #1

### 输入

```
2
4
1 0 0 1 0
0 1 0 0 1
0 0 0 1 0
0 1 0 1 0
2
0 0 0 1 0
0 0 0 1 0```

### 输出

```
YES
NO```

# AI分析结果

### 题目内容
# 分组

## 题目描述
$n$ 名学生参加了伯兰德州立大学编程课程的第一次会议（$n$ 为偶数）。所有学生将被分成两组。每组每周将在五个工作日（周一、周二、周三、周四和周五）中的某一天参加一节课，并且为两组选择的日子必须不同。此外，两组应包含相同数量的学生。

每个学生都填写了一份调查问卷，其中说明了一周中的哪些日子方便他们上课，哪些日子不方便。

你的任务是确定是否有可能选择两个不同的工作日来安排两组的课程（第一组将在第一个选择的日子上课，第二组将在第二个选择的日子上课），并将学生分成两组，使两组人数相等，并且对于每个学生，为其所在组选择的上课日是方便的。

## 说明/提示
在第一个测试用例中，有一种方法可以满足所有约束条件。例如，第一组可以由第一名和第三名学生组成，他们将在周四（第四天）上课；第二组可以由第二名和第四名学生组成，他们将在周二（第二天）上课。

在第二个测试用例中，不可能将学生分成两组，使他们在不同的日子上课。

## 样例 #1
### 输入
```
2
4
1 0 0 1 0
0 1 0 0 1
0 0 0 1 0
0 1 0 1 0
2
0 0 0 1 0
0 0 0 1 0
```
### 输出
```
YES
NO
```

### 算法分类
枚举

### 题解综合分析与结论
这几道题解的核心思路都是通过枚举不同的两天作为两组课程的安排时间，然后判断是否能将学生合理分配到这两天且两组人数相等。
- **思路方面**：happy_dengziyue、SegTre和洛桃的思路较为相似，都是先枚举两天，然后统计只在某一天有空、两天都有空的学生人数，再根据这些人数判断能否完成分组。Farkas_W则是通过容斥原理，利用统计第 $i$ 天可以上课的学生数量 $cnt_i$ 以及第 $i$ 天和第 $j$ 天都可以上课的学生数量 $num_{i,j}$ ，通过特定的等式关系判断分组是否可行。
- **算法要点**：主要要点在于准确统计不同情况的学生数量，并依据这些数量判断分组的可行性。
- **解决难点**：难点在于如何全面且准确地考虑各种学生时间安排情况，以确保判断的正确性。例如在不同的学生时间分布下，如何合理利用两天都有空的学生来平衡两组人数。

### 所选的题解
- **作者：happy_dengziyue（4星）**
  - **关键亮点**：思路清晰直接，代码实现简洁明了。通过定义数组 `cnt` 分别统计仅第一天有空、仅第二天有空和两天都有空的学生数量，根据这些数量关系判断方案是否合法。
  - **重点代码**：
```cpp
bool check(int x,int y){
    cnt[0]=cnt[1]=cnt[2]=0;
    for(int i=1;i<=n;++i){
        if(a[i][x]&&!a[i][y])++cnt[0];
        if(!a[i][x]&&a[i][y])++cnt[1];
        if(a[i][x]&&a[i][y])++cnt[2];
        if(!a[i][x]&&!a[i][y])return false;
    }
    if(cnt[0]<n/2)cnt[2]+=cnt[0]-n/2;
    if(cnt[1]<n/2)cnt[2]+=cnt[1]-n/2;
    return cnt[2]>=0;
}
```
  - **核心实现思想**：在 `check` 函数中，遍历每个学生，统计不同情况的学生数量。若两天都没空则直接返回 `false`。之后根据仅第一天有空和仅第二天有空的学生数量与 $n/2$ 的关系，从两天都有空的学生中抽调人员平衡两组，最后判断两天都有空的学生数量是否足够，以确定方案是否合法。
- **作者：SegTre（4星）**
  - **关键亮点**：同样是枚举两天判断方案可行性，对各种学生时间情况的讨论细致全面，分四种情况判断能否分组成功。
  - **重点代码**：
```cpp
bool check(int x,int y) {
    int cnt1=0,cnt2=0,cnt=0;
    for(int i=1;i<=n;++i) cnt1+=(!a[i][y]&a[i][x]);
    for(int i=1;i<=n;++i) cnt2+=(!a[i][x]&a[i][y]);
    for(int i=1;i<=n;++i) cnt+=(a[i][y]&a[i][x]);
    if(cnt1>=n/2&&cnt2>=n/2) return 1;
    if(cnt1<n/2&&cnt2<n/2) {
        if(cnt-(n-cnt1-cnt2)>=0) return 1;
        else return 0;
    }
    if(cnt1<n/2&&cnt2>=n/2) return cnt1+cnt>=n/2? 1:0;
    if(cnt2<n/2&&cnt1>=n/2) return cnt2+cnt>=n/2? 1:0;
    return 0;
}
```
  - **核心实现思想**：在 `check` 函数中，先统计只在 `x` 课有空、只在 `y` 课有空以及两节课都有空的学生数量。然后分四种情况判断：若 `cnt1` 和 `cnt2` 都能凑齐一组则可行；若都没凑齐，判断两节课都有空的学生能否补足；若其中一个能凑齐一组，判断加上两节课都有空的学生能否凑齐另一组，以此确定方案是否可行。
- **作者：Farkas_W（4星）**
  - **关键亮点**：运用容斥原理，通过特定的数量关系判断分组可行性，角度较为新颖。
  - **重点代码**：
```cpp
for(re i=1;i<5;i++)
{
    if(cnt[i]*2<n)continue;
    for(re j=i+1;j<=5;j++)
    {
        if(cnt[j]*2<n)continue;
        int x=cnt[i],y=cnt[j],z=num[(1<<i)|(1<<j)],p;
        if(x+y-z==n){ans=1;break;}
    }
    if(ans)break;
}
```
  - **核心实现思想**：通过两层循环枚举两天，先判断这两天分别能上课的学生数量是否满足至少为 $n/2$ ，然后根据容斥原理得出的等式 `cnt_i+cnt_j-num_{i,j}= n` 判断能否完成分组，若满足则方案可行。

### 最优关键思路或技巧
这些题解中，利用枚举两天的方式是基础。在判断分组可行性上，统计不同时间情况学生数量并合理利用这些数量关系是关键。例如Farkas_W利用容斥原理得出的判断等式，以及其他作者根据仅一天有空和两天都有空的学生数量来平衡两组人数的方法，都是解决问题的有效技巧。

### 可拓展之处
此类题目属于分组可行性判断问题，类似套路是先确定需要枚举的关键因素（如本题中的两天），然后统计相关数据，依据特定条件判断可行性。同类型题可能会改变限制条件，如改变分组数量、时间安排的限制等，但核心思路类似。

### 洛谷推荐题目
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：通过枚举组合来输出结果，与本题枚举两天的思路类似。
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：涉及到利用数学原理进行计算和判断，与本题利用数量关系判断可行性有相似之处。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：需要通过枚举路径等方式来解决问题，和本题枚举关键因素判断可行性思路相符。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：66.87秒