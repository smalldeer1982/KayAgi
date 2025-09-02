# 题目信息

# Alena's Schedule

## 题目描述

Alena has successfully passed the entrance exams to the university and is now looking forward to start studying.

One two-hour lesson at the Russian university is traditionally called a pair, it lasts for two academic hours (an academic hour is equal to 45 minutes).

The University works in such a way that every day it holds exactly $ n $ lessons. Depending on the schedule of a particular group of students, on a given day, some pairs may actually contain classes, but some may be empty (such pairs are called breaks).

The official website of the university has already published the schedule for tomorrow for Alena's group. Thus, for each of the $ n $ pairs she knows if there will be a class at that time or not.

Alena's House is far from the university, so if there are breaks, she doesn't always go home. Alena has time to go home only if the break consists of at least two free pairs in a row, otherwise she waits for the next pair at the university.

Of course, Alena does not want to be sleepy during pairs, so she will sleep as long as possible, and will only come to the first pair that is presented in her schedule. Similarly, if there are no more pairs, then Alena immediately goes home.

Alena appreciates the time spent at home, so she always goes home when it is possible, and returns to the university only at the beginning of the next pair. Help Alena determine for how many pairs she will stay at the university. Note that during some pairs Alena may be at the university waiting for the upcoming pair.

## 说明/提示

In the first sample Alena stays at the university from the second to the fifth pair, inclusive, during the third pair she will be it the university waiting for the next pair.

In the last sample Alena doesn't have a single pair, so she spends all the time at home.

## 样例 #1

### 输入

```
5
0 1 0 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7
1 0 1 0 0 1 0
```

### 输出

```
4
```

## 样例 #3

### 输入

```
1
0
```

### 输出

```
0
```

# AI分析结果

### 题目翻译
# 阿莲娜的课程表

## 题目描述
阿莲娜已成功通过大学入学考试，现在正期待着开始学习。

在俄罗斯的大学，一节两小时的课程传统上被称为“一对课”，持续两个学时（一个学时等于45分钟）。

大学的运作模式是，每天正好安排 $n$ 节课。根据特定学生群体的课程表，在某一天，有些课可能实际上有课程安排，而有些则可能是空的（这样的课被称为课间休息）。

大学的官方网站已经公布了阿莲娜所在班级明天的课程表。因此，对于这 $n$ 节课中的每一节，她都知道届时是否有课。

阿莲娜的家离大学很远，所以如果有课间休息，她并不总是回家。只有当课间休息至少连续有两节课时，阿莲娜才有时间回家，否则她会在学校等待下一节课。

当然，阿莲娜不想在上课时打瞌睡，所以她会尽可能长时间地睡觉，只会在课程表中的第一节课开始时来学校。同样，如果没有更多的课了，阿莲娜会立即回家。

阿莲娜很珍惜在家的时间，所以只要有可能，她总会回家，并且只会在下一节课开始时回到学校。请帮助阿莲娜确定她将在学校上多少节课。请注意，在某些课间，阿莲娜可能会在学校等待即将到来的课。

## 说明/提示
在第一个样例中，阿莲娜从第二节课到第五节课都在学校，包括在内，在第三节课时，她会在学校等待下一节课。

在最后一个样例中，阿莲娜没有一节课，所以她一整天都在家。

## 样例 #1
### 输入
```
5
0 1 0 1 1
```
### 输出
```
4
```

## 样例 #2
### 输入
```
7
1 0 1 0 0 1 0
```
### 输出
```
4
```

## 样例 #3
### 输入
```
1
0
```
### 输出
```
0
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟阿莲娜在学校的上课情况，计算她在学校的课程节数。具体做法是先统计1（有课）的个数，再统计被两个1夹着的0（课间但不回家）的个数，将两者相加得到结果。
- **思路对比**：大部分题解都是先统计1的数量，再判断夹在两个1中间的0的数量；DPair的题解是先假设所有课都在学校，再减去可以回家的课间数。
- **算法要点**：主要是对输入的01序列进行遍历，根据条件判断并计数。
- **解决难点**：正确判断哪些0是被两个1夹着的，避免越界访问数组。

### 评分较高题解
- **作者：asasas（4星）**
    - **关键亮点**：思路清晰，将夹在两个1中间的0直接变为1，最后统一计算1的个数，简化了后续的统计过程。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool a[105];
int main(){
    int n;
    cin >> n;
    for (register int i=1;i<=n;i++){
        cin >> a[i];
    }
    int ans=0;
    for (register int i=1;i<=n-2;i++){
        if (a[i]==1&&a[i+1]==0&&a[i+2]==1) a[i+1]=1; 
    } 
    for (register int i=1;i<=n;i++) ans+=a[i];
    cout << ans;
} 
```
核心思想：先将夹在两个1中间的0变为1，再统计数组中1的个数。

- **作者：绝艺（4星）**
    - **关键亮点**：代码结构清晰，先记录1的个数，再遍历判断夹在两个1中间的0的个数。
    - **重点代码**：
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n,a[101],ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]==1) ans++;
    }
    for(int i=2;i<n;i++)
    {
        if(a[i]==0)
        {
            if(a[i-1]==1&&a[i+1]==1) ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
核心思想：先统计1的个数，再遍历数组，找到夹在两个1中间的0并计数。

- **作者：Programmtion（4星）**
    - **关键亮点**：思路简洁明了，通过两次遍历分别统计1和夹在两个1中间的0的个数。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,a[101],ans=0;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]==1) ans++;
    }
    for(int i=2;i<n;i++){ 
        if(a[i]==0&&a[i-1]==1&&a[i+1]==1)
            ans++;
    }
    cout<<ans;
    return 0;
}
```
核心思想：先统计1的个数，再遍历数组，判断并统计夹在两个1中间的0的个数。

### 最优关键思路或技巧
- 使用数组存储输入的01序列，方便遍历和判断相邻元素。
- 对于夹在两个1中间的0的判断，要注意边界条件，避免数组越界。

### 可拓展之处
同类型题可能会改变回家的条件，比如连续三个课间才回家等，或者增加更多的条件限制，如不同时间段的课间有不同的处理方式。解题思路仍然是模拟整个过程，根据新的条件进行判断和计数。

### 推荐洛谷题目
- P1003 铺地毯
- P1047 校门外的树
- P1098 字符串的展开

### 个人心得摘录与总结
- **_tommysun_**：提到题目的难度主要在题面上，理解题面后就是入门题，强调了理解题意的重要性。
- **Chtholly_L**：表示看到超长英文题干很慌，但看到翻译后发现题目很简单，也体现了理解题意的关键作用。

---
处理用时：36.87秒