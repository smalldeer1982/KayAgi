# 题目信息

# [USACO09DEC] Music Notes S

## 题目描述

FJ is going to teach his cows how to play a song. The song consists of N (1 <= N <= 50,000) notes, and the i-th note lasts for B\_i (1 <= B\_i <= 10,000) beats (thus no song is longer than 500,000,000 beats). The cows will begin playing the song at time 0; thus, they will play note 1 from time 0 through just before time B\_1, note 2 from time B\_1 through just before time B\_1 + B\_2, etc.

However, recently the cows have lost interest in the song, as they feel that it is too long and boring. Thus, to make sure his cows are paying attention, he asks them Q (1 <= Q <= 50,000) questions of the form, 'In the interval from time T through just before time T+1, which note should you be playing?' The cows need your help to answer these questions which are supplied as T\_i (0 <= T\_i <=

end\_of\_song). 

Consider this song with three notes of durations 2, 1, and 3 beats:

```cpp
Beat:   0    1    2    3    4    5    6    ...
        |----|----|----|----|----|----|--- ...
        1111111111     :              :
                  22222:              :
                       333333333333333:
``` 
Here is a set of five queries along with the resulting answer:

Query    Note

2        2

3        3

4        3

0        1

1        1


## 样例 #1

### 输入

```
3 5 
2 
1 
3 
2 
3 
4 
0 
1 
```

### 输出

```
2 
3 
3 
1 
1 
```

# AI分析结果

### 综合分析与结论
这些题解围绕奶牛演奏音符问题，给出了多种解题思路。主要分为暴力枚举、二分查找和使用 STL 函数三类方法。暴力枚举思路简单但复杂度高，二分查找和 STL 函数则能有效优化时间复杂度。

### 所选题解
- **x_faraway_x 的题解（5 星）**
    - **关键亮点**：使用 STL 的 `upper_bound` 函数，代码简洁，时间复杂度低，思路清晰。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=50005;
int b[N],sum[N],n,q;
inline int _read()
{
    int x=0; char c;
    for(;c<'0'||c>'9';c=getchar());
    for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+c-'0';
    return x;
}
int main()
{
    n=_read(),q=_read();
    for(int i=1;i<=n;i++)
    {
        b[i]=_read();
        sum[i]=sum[i-1]+b[i];
    }
    while(q--)
    {
        int x=_read();
        printf("%d\n",upper_bound(sum+1,sum+1+n,x)-sum);
    }
}
```
    - **核心实现思想**：先计算每个音符结束时间的前缀和数组 `sum`，对于每个查询时间 `x`，使用 `upper_bound` 函数找到第一个大于 `x` 的元素在 `sum` 数组中的位置，该位置即为要演奏的音符编号。

- **HNFMS__vistonuzi 的题解（4 星）**
    - **关键亮点**：同样使用 `upper_bound` 函数，代码简洁易懂，有注释说明。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,m,n,b[50005],c[50005],d,i;
int main()
{
    cin>>m>>n;
    for(i=1;i<=m;i++)
    {
        cin>>a;
        c[i]=c[i-1]+a;
    }
    for(i=1;i<=n;i++)
    {
        cin>>d;
        b[i]=upper_bound(c,c+m+1,d)-c;
    }
    for(i=1;i<=n;i++)
    {
        cout<<b[i]<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：与上一题解类似，先计算前缀和数组 `c`，对于每个查询时间 `d`，使用 `upper_bound` 函数找到对应音符编号并存储在 `b` 数组中，最后输出结果。

- **BBD186587 的做法三（4 星）**
    - **关键亮点**：手动实现二分查找，优化了暴力枚举的时间复杂度，详细展示了从暴力到优化的过程。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,q,d,x;
struct node
{
    int l,r;
}a[100010];
inline int read()
{
    char ch;int f=1;
    while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
    int x=ch-'0';
    while(isdigit(ch=getchar())) x=x*10+ch-'0';
    return x*f;
}
int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++)
    {
        x=read();
        a[i].l=d,d+=x,a[i].r=d-1;
    }
    while(q--)
    {
        x=read();
        int l=1,r=n,mid;
        while(1)
        {
            mid=(l+r)/2;
            if(a[mid].l<=x&&a[mid].r>=x) {printf("%d\n",mid); break;}
            else if(a[mid].l>x) r=mid;
            else l=mid+1;
        }
    }
    return 0;
}
```
    - **核心实现思想**：用结构体 `node` 存储每个音符的开始和结束时间，对于每个查询时间 `x`，使用二分查找在结构体数组中找到包含 `x` 的音符区间，输出该音符编号。

### 最优关键思路或技巧
- 使用前缀和数组记录每个音符的结束时间，将问题转化为在有序数组中查找元素位置。
- 利用 STL 的 `upper_bound` 函数或手动实现二分查找，将查询的时间复杂度从 $O(N)$ 优化到 $O(\log N)$。

### 拓展思路
同类型题或类似算法套路：区间查询问题，如在多个时间段内查找某个时间点所在的区间，可使用前缀和与二分查找结合的方法。

### 推荐题目
- P1102 A-B 数对
- P2249 【深基13.例1】查找
- P1678 烦恼的高考志愿

### 个人心得摘录与总结
- **BBD186587**：最初使用桶排，因空间复杂度高导致 RE 和 MLE；接着使用结构体暴力枚举，又因时间复杂度高导致 TLE；最后使用二分查找优化复杂度，成功 AC。总结为在解题时要根据数据范围合理选择算法，避免因复杂度问题导致错误。 

---
处理用时：32.43秒