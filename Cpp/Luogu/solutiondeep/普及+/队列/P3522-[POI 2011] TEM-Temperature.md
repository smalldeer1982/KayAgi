# 题目信息

# [POI 2011] TEM-Temperature

## 题目描述

The Byteotian Institute of Meteorology (BIM) measures the air temperature  daily.

The measurement is done automatically, and its result immediately printed.

Unfortunately, the ink in the printer has long dried out...

The employees of BIM however realised the fact only recently, when the    Byteotian Organisation for Meteorology (BOM) requested access to that data.

An eager intern by the name of Byteasar saved the day, as he systematically    noted down the temperatures reported by two domestic alcohol thermometers    placed on the north and south outside wall of the BIM building.

It was established decades ago by various BIM employees that the temperature    reported by the thermometer on the south wall of the building is never lower    than the actual temperature, while that reported by the thermometer on the    north wall of the building is never higher than the actual temperature.

Thus even though the exact temperatures for each day remain somewhat of    a mystery, the range they were in is known at least.

Fortunately for everyone involved (except Byteasar and you, perhaps),    BOM does not require exact temperatures. They only want to know the longest    period in which the temperature was not dropping (i.e. on each successive    day it was no smaller than on the day before).

In fact, the veteran head of BIM knows very well that BOM would like this    period as long as possible.

To whitewash the negligence he insists that Byteasar determines, based on    his valuable notes, the longest period in which the temperature    could have been not dropping.

Now this is a task that Byteasar did not quite expect on his BIM internship,    and he honestly has no idea how to tackle it.

He asks you for help in writing a program that determines the longest such    period.

某国进行了连续 $ n $ ( $ 1 \le n \le 1,000,000 $）天的温度测量，测量存在误差，测量结果是第 $i$ 天温度在 $[l_i,r_i]$ 范围内。

求最长的连续的一段，满足该段内可能温度不降。


## 样例 #1

### 输入

```
6
6 10
1 5
4 8
2 5
6 8
3 5```

### 输出

```
4```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何求解最长连续温度不降的时间段展开，多数采用单调队列的方法，部分使用动态规划结合线段树等方法。单调队列的核心在于维护队列中元素的单调性，以高效地找到满足条件的最长区间；动态规划结合线段树则是通过状态转移和数据结构优化来解决问题。

### 所选题解
- **作者：Lonely_NewYear（4星）**
    - **关键亮点**：思路清晰，对单调队列的原理和应用解释详细，通过生动的例子帮助理解，代码实现规范且有详细注释，对错误情况有分析和修正。
    - **个人心得**：在实现过程中发现初始做法样例过不了，原因是当有一天的最低温度特别大，把前面的所有天都弹出时，不能重新从这一天开始计数，前面的天还是可以用的，弹出只是为了维护单调性，所以在弹出时记录最后一个被弹出的天，并赋值给这一天的天数。

### 重点代码
```cpp
#include<cstdio>
#include<deque>
#include<algorithm>
using namespace std;
struct node
{
    int l,r,id;//id表示是第几天
};
int main()
{
    int n,ans=1;
    scanf("%d",&n);
    deque<node> q;
    for(int i=1;i<=n;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        while(!q.empty()&&q.front().l>r)//要判断队列非空哦
        {
            q.pop_front();
        }
        if(!q.empty())
        {
            ans=max(ans,i-q.front().id+1);
        }
        int tmp=i;
        while(!q.empty()&&q.back().l<l)
        {
            tmp=q.back().id;//维护这一段的起始天
            q.pop_back();
        }
        q.push_back((node){l,r,tmp});
    }
    printf("%d",ans);
    return 0;
}
```
**核心实现思想**：使用双端队列维护一个单调队列，队列中存储结构体 `node`，包含每天的最低温度 `l`、最高温度 `r` 和天数 `id`。每次读入新的一天的温度范围，先从队头弹出最低温度过大的天，更新答案，再从队尾弹出所有比这一天的最低温度小的天，维护单调性，最后将当前天加入队列，同时记录这一段的起始天。

### 最优关键思路或技巧
- **单调队列的应用**：通过维护队列中元素的单调性，高效地找到满足条件的最长区间，时间复杂度为 $O(n)$。
- **记录起始天**：在弹出元素时记录最后一个被弹出的天，避免重新从当前天开始计数，保证了结果的正确性。

### 可拓展之处
同类型题或类似算法套路：
- 求最长连续递增子序列：可以使用单调队列维护递增的元素，通过类似的方法找到最长连续递增子序列。
- 滑动窗口最大值：使用单调队列维护窗口内的最大值，每次窗口滑动时，从队头弹出不在窗口内的元素，从队尾弹出比当前元素小的元素，保证队头元素为窗口内的最大值。

### 推荐题目
- P1886 滑动窗口 /【模板】单调队列
- P2032 扫描
- P1714 切蛋糕

### 个人心得总结
在实现过程中，要注意对特殊情况的处理，不能仅仅根据表面的逻辑进行实现，需要深入思考，例如在本题中，不能因为弹出了前面的元素就重新从当前天开始计数，要考虑到前面的天仍然可能对结果有贡献。同时，在调试过程中，要仔细分析样例不通过的原因，逐步修正代码。

---
处理用时：24.44秒