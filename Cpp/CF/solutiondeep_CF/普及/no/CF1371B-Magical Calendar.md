# 题目信息

# Magical Calendar

## 题目描述

A competitive eater, Alice is scheduling some practices for an eating contest on a magical calendar. The calendar is unusual because a week contains not necessarily $ 7 $ days!

In detail, she can choose any integer $ k $ which satisfies $ 1 \leq k \leq r $ , and set $ k $ days as the number of days in a week.

Alice is going to paint some $ n $ consecutive days on this calendar. On this calendar, dates are written from the left cell to the right cell in a week. If a date reaches the last day of a week, the next day's cell is the leftmost cell in the next (under) row.

She wants to make all of the painted cells to be connected by side. It means, that for any two painted cells there should exist at least one sequence of painted cells, started in one of these cells, and ended in another, such that any two consecutive cells in this sequence are connected by side.

Alice is considering the shape of the painted cells. Two shapes are the same if there exists a way to make them exactly overlapped using only parallel moves, parallel to the calendar's sides.

For example, in the picture, a week has $ 4 $ days and Alice paints $ 5 $ consecutive days. \[1\] and \[2\] are different shapes, but \[1\] and \[3\] are equal shapes.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1371B/39eae368c2a57a50366d3b4d64699d9970b52d63.png)Alice wants to know how many possible shapes exists if she set how many days a week has and choose consecutive $ n $ days and paints them in calendar started in one of the days of the week. As was said before, she considers only shapes, there all cells are connected by side.

## 说明/提示

In the first test case, Alice can set $ 1,2,3 $ or $ 4 $ days as the number of days in a week.

There are $ 6 $ possible paintings shown in the picture, but there are only $ 4 $ different shapes. So, the answer is $ 4 $ . Notice that the last example in the picture is an invalid painting because all cells are not connected by sides.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1371B/1ff3916b23daa3947041e2801c12887257623fb7.png)In the last test case, be careful with the overflow issue, described in the output format.

## 样例 #1

### 输入

```
5
3 4
3 2
3 1
13 7
1010000 9999999```

### 输出

```
4
3
1
28
510049495001```

# AI分析结果

### 题目内容重写

#### 魔法日历

**题目描述**

一位竞技食客Alice正在为一个魔法日历上的吃比赛安排一些练习。这个日历不同寻常，因为一周不一定包含7天！

具体来说，她可以选择任何满足$1 \leq k \leq r$的整数$k$，并将$k$天设置为一周的天数。

Alice将在这个日历上涂色连续的$n$天。在这个日历上，日期从一周的左单元格到右单元格依次写入。如果日期到达一周的最后一天，则下一天的单元格位于下一行的最左单元格。

她希望所有涂色的单元格通过边相连。这意味着，对于任何两个涂色的单元格，应该存在至少一个由涂色单元格组成的序列，从其中一个单元格开始，到另一个单元格结束，使得序列中任何两个连续的单元格通过边相连。

Alice正在考虑涂色单元格的形状。如果仅通过平行于日历边的平移可以使两个形状完全重叠，则认为这两个形状相同。

例如，在图片中，一周有4天，Alice涂色了5个连续的天。\[1\]和\[2\]是不同的形状，但\[1\]和\[3\]是相同的形状。

Alice想知道，如果她设置一周的天数并选择连续的$n$天并在日历上涂色，有多少种可能的形状存在。如前所述，她只考虑所有单元格通过边相连的形状。

**说明/提示**

在第一个测试用例中，Alice可以将1、2、3或4天设置为一周的天数。

图片中显示了6种可能的涂色，但只有4种不同的形状。因此，答案是4。注意，图片中的最后一个示例是无效的涂色，因为所有单元格没有通过边相连。

在最后一个测试用例中，请注意输出格式中描述的溢出问题。

**样例 #1**

**输入**

```
5
3 4
3 2
3 1
13 7
1010000 9999999
```

**输出**

```
4
3
1
28
510049495001
```

### 算法分类

数学、组合数学

### 题解分析与结论

#### 题解1：pyz51

**关键亮点**
- 分类讨论$n$与$r$的关系，分别计算形状数量。
- 使用等差数列求和公式简化计算。
- 代码简洁，逻辑清晰。

**评分**：4星

**核心代码**
```cpp
#include<iostream>
using namespace std;
int t,n,r;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>r;
        if(n>r) cout<<1ll*r*(r+1)/2;
        else cout<<1ll*n*(n-1)/2+1;
        cout<<'\n';
    }
    return 0;
}
```

#### 题解2：huayucaiji

**关键亮点**
- 同样分类讨论$n$与$r$的关系，使用等差数列求和公式。
- 代码中使用了`unsigned long long`防止溢出。
- 逻辑清晰，代码可读性高。

**评分**：4星

**核心代码**
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;

int read() {
    char ch=getchar();
    int f=1,x=0;
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}

int n,r;

signed main() {
    int t;
    t=read();
    while(t--) {
        n=read();r=read();
        
        int ans=0;
        if(n<=r) {
            ans+=(n-1)*n/2;
            ans+=1;
        }
        else {
            ans+=(r+1)*r/2;
        }
        cout<<ans<<endl;
    } 
    return 0;
}
```

### 最优关键思路与技巧

- **分类讨论**：根据$n$与$r$的大小关系，分别计算形状数量。
- **等差数列求和**：利用等差数列求和公式简化计算，避免复杂循环。
- **防止溢出**：使用`unsigned long long`或`1ll`来防止整数溢出。

### 可拓展之处

- 类似问题可以扩展到更高维度的形状计数，或者考虑更多限制条件（如形状的对称性）。
- 可以进一步研究不同形状的排列组合问题，结合图论或几何知识。

### 推荐题目

1. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036)
3. [P1044 栈](https://www.luogu.com.cn/problem/P1044)

---
处理用时：32.08秒