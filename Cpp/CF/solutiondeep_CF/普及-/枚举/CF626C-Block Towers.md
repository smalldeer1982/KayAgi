# 题目信息

# Block Towers

## 题目描述

Students in a class are making towers of blocks. Each student makes a (non-zero) tower by stacking pieces lengthwise on top of each other. $ n $ of the students use pieces made of two blocks and $ m $ of the students use pieces made of three blocks.

The students don’t want to use too many blocks, but they also want to be unique, so no two students’ towers may contain the same number of blocks. Find the minimum height necessary for the tallest of the students' towers.

## 说明/提示

In the first case, the student using two-block pieces can make a tower of height $ 4 $ , and the students using three-block pieces can make towers of height $ 3 $ , $ 6 $ , and $ 9 $ blocks. The tallest tower has a height of $ 9 $ blocks.

In the second case, the students can make towers of heights $ 2 $ , $ 4 $ , and $ 8 $ with two-block pieces and towers of heights $ 3 $ and $ 6 $ with three-block pieces, for a maximum height of $ 8 $ blocks.

## 样例 #1

### 输入

```
1 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5 0
```

### 输出

```
10
```

# AI分析结果

### 题目翻译
# 积木塔

## 题目描述
一个班级的学生正在用积木搭建塔。每个学生通过将积木纵向堆叠来搭建一个（非零高度）的塔。有 $n$ 个学生使用由两块积木组成的部件，有 $m$ 个学生使用由三块积木组成的部件。

学生们不想使用太多的积木，但他们也希望每个塔都是独一无二的，所以任意两个学生的塔不能包含相同数量的积木。请找出学生们所搭塔中最高塔的最小高度。

## 说明/提示
在第一个样例中，使用两块积木部件的学生可以搭出高度为 $4$ 的塔，使用三块积木部件的学生可以搭出高度为 $3$、$6$ 和 $9$ 的塔。最高的塔高度为 $9$ 块积木。

在第二个样例中，使用两块积木部件的学生可以搭出高度为 $2$、$4$ 和 $8$ 的塔，使用三块积木部件的学生可以搭出高度为 $3$ 和 $6$ 的塔，最高塔的高度为 $8$ 块积木。

## 样例 #1
### 输入
```
1 3
```
### 输出
```
9
```

## 样例 #2
### 输入
```
3 2
```
### 输出
```
8
```

## 样例 #3
### 输入
```
5 0
```
### 输出
```
10
```

### 题解综合分析与结论
这些题解主要围绕如何求出最高塔的最小高度展开，核心在于处理两种不同搭法（2 块一搭和 3 块一搭）产生的高度重合问题。
- **思路对比**：
    - **暴力枚举**：Bpds1110、fmdd_szx、SilverLi、Umbrella_Leaf、hank0402 这几位作者的思路类似，都是枚举答案 $s$，通过判断 $s$ 是否满足 $\left \lfloor \frac{s}{2}  \right \rfloor \ge n$、$\left \lfloor \frac{s}{3}  \right \rfloor \ge m$ 和 $\left \lfloor \frac{s}{2}  \right \rfloor + \left \lfloor \frac{s}{3}  \right \rfloor - \left \lfloor \frac{s}{6}  \right \rfloor \ge n + m$ 这三个条件来确定最小的 $s$。hank0402 在此基础上，先将枚举起点设为 $\max(2\times n,3\times m)$。
    - **动态调整**：Melon_Musk 先计算初始高度 $sum1 = 2 * n$ 和 $sum2 = 3 * m$，当出现高度重合（6 的倍数）时，增加当前值较小的那个，不断调整直到满足条件。
    - **二分查找**：SummerFlyFly 和 Fat_Fish 采用二分答案的方法，通过判断中间值是否满足上述三个条件来缩小查找范围。
    - **枚举数字**：what_can_I_do 枚举每个数字，根据数字是 2、3 或 6 的倍数情况，动态分配给 2 块搭或 3 块搭的人，最后找出最大高度。
- **算法要点对比**：
    - 暴力枚举思路简单直接，但效率相对较低，时间复杂度为 $O(k)$，其中 $k$ 是满足条件的最大答案。
    - 动态调整通过不断更新高度值，避免了不必要的枚举，时间复杂度取决于重合次数。
    - 二分查找将时间复杂度优化到 $O(log k)$，效率较高。
    - 枚举数字的方法需要遍历较大范围的数字，时间复杂度较高。
- **难点解决对比**：
    - 对于高度重合问题，暴力枚举和二分查找通过容斥原理（减去 $\left \lfloor \frac{s}{6}  \right \rfloor$）来处理。
    - 动态调整通过增加较小值来避免重合。
    - 枚举数字的方法通过比较剩余人数来分配重合高度。

### 所选题解
- **Melon_Musk（5 星）**：
    - **关键亮点**：思路清晰，通过动态调整高度值，避免了复杂的枚举和判断，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,sum1,sum2;
int main()
{
    scanf("%d%d",&n,&m);
    sum1=n*2;sum2=m*3;
    while(n>=3 && m>=2)
    {
        if(sum1+2<=sum2+3) sum1+=2,n++;
        else sum2+=3,m++;
        n-=3,m-=2;
    }
    printf("%d\n",max(sum1,sum2));
    return 0;
}
```
核心实现思想：先计算初始高度，当出现高度重合时，选择增加当前值较小的高度，同时更新人数，最后输出最大高度。
- **Fat_Fish（4 星）**：
    - **关键亮点**：利用二分查找优化了查找过程，时间复杂度较低，代码结构清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+100;
int n,m,t,a[maxn];
bool check(int x){
    if(x/2>=n&&x/3>=m&&x/2+x/3-x/6>=m+n){
        return true;
    }
    return false;
}
signed main(){
    cin>>n>>m;
    int l=0,r=6000000;
    while(l+1<r){
        int mid=l+r>>1;
        if(check(mid)){
            r=mid;
        }else {
            l=mid;
        }
    }
    if(check(l)){
        cout<<l<<'\n';
    }else if(check(r)){
        cout<<r<<'\n';
    }
    return 0;
}
```
核心实现思想：二分查找最高塔的高度，通过 `check` 函数判断中间值是否满足条件，不断缩小查找范围。
- **Bpds1110（4 星）**：
    - **关键亮点**：思路直接，利用容斥原理判断答案是否满足条件，代码简洁。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>

int main()
{
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; ; ++ i)
        if (i / 2 >= n && i / 3 >= m && i / 2 + i / 3 - i / 6 >= n + m)
            return std::cout << i, 0;
    return 0;
}
```
核心实现思想：枚举答案，判断其是否满足三个条件，满足则输出。

### 最优关键思路或技巧
- 对于高度重合问题，利用容斥原理（减去最小公倍数的倍数）来处理。
- 当问题具有单调性时，可以使用二分查找来优化查找过程。
- 动态调整高度值，优先增加较小值，可避免不必要的枚举。

### 可拓展之处
同类型题可能会有更多种搭法，或者对塔的高度有其他限制条件。类似算法套路可用于解决具有单调性和重叠情况的最值问题，如不同长度线段覆盖问题、不同速度行程问题等。

### 推荐题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：二分查找在实际问题中的应用。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分答案解决最值问题。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：二分查找优化问题求解。

### 个人心得摘录与总结
- SummerFlyFly：提到二分写得很丑，反映出二分查找代码实现可能存在一定难度，需要注意细节。
- Umbrella_Leaf：回顾自己曾经试图骗分的经历，提醒我们要认真思考问题，不能投机取巧。 

---
处理用时：43.59秒