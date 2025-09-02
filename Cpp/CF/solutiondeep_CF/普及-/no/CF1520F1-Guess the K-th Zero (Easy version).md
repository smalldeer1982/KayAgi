# 题目信息

# Guess the K-th Zero (Easy version)

## 题目描述

This is an interactive problem.

This is an easy version of the problem. The difference from the hard version is that in the easy version $ t=1 $ and the number of queries is limited to $ 20 $ .

Polycarp is playing a computer game. In this game, an array consisting of zeros and ones is hidden. Polycarp wins if he guesses the position of the $ k $ -th zero from the left $ t $ times.

Polycarp can make no more than $ 20 $ requests of the following type:

- ? $ l $ $ r $ — find out the sum of all elements in positions from $ l $ to $ r $ ( $ 1 \le l \le r \le n $ ) inclusive.

In this (easy version) of the problem, this paragraph doesn't really make sense since $ t=1 $ always. To make the game more interesting, each guessed zero turns into one and the game continues on the changed array. More formally, if the position of the $ k $ -th zero was $ x $ , then after Polycarp guesses this position, the $ x $ -th element of the array will be replaced from $ 0 $ to $ 1 $ . Of course, this feature affects something only for $ t>1 $ .

Help Polycarp win the game.

## 说明/提示

In the first test, the $ [1, 0, 1, 1, 0, 1] $ array is hidden. In this test $ k=2 $ .

## 样例 #1

### 输入

```
6 1
2

2

1

1

0

0```

### 输出

```
? 4 6

? 1 1

? 1 2

? 2 2

? 5 5

! 5```

# AI分析结果

### 题目内容
# 猜第K个零（简单版）

## 题目描述
这是一道交互题。
这是该问题的简单版本。与困难版本的区别在于，在简单版本中 t = 1，并且查询次数限制为20次。
波利亚科夫正在玩一款电脑游戏。在这个游戏中，隐藏着一个由0和1组成的数组。如果波利亚科夫能 t 次猜出从左数第 k 个0的位置，他就能获胜。
波利亚科夫最多可以进行20次以下类型的查询：
 - ？l r —— 找出从位置 l 到 r（1 ≤ l ≤ r ≤ n）的所有元素之和（包含 l 和 r）。
在这个（简单版本）的问题中，由于 t 始终为1，所以这一段实际上意义不大。为了使游戏更有趣，每次猜出的0会变成1，游戏会在改变后的数组上继续进行。更正式地说，如果第 k 个0的位置是 x ，那么在波利亚科夫猜出这个位置后，数组的第 x 个元素将从0替换为1。当然，这个特性仅在 t > 1 时才会产生影响。
帮助波利亚科夫赢得游戏。

## 说明/提示
在第一个测试中，隐藏的数组是 [1, 0, 1, 1, 0, 1] 。在这个测试中 k = 2 。

## 样例 #1
### 输入
```
6 1
2

2

1

1

0

0
```
### 输出
```
? 4 6

? 1 1

? 1 2

? 2 2

? 5 5

! 5
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路均是利用二分查找来确定第k个0的位置。由于最多询问20次，而2^20≥n ，二分查找的对数复杂度恰好满足要求。各题解在具体实现上略有差异，但本质都是通过询问区间和来计算区间内0的个数，进而调整二分区间。思路上，均先确定二分的左右端点，每次询问特定区间（多为1到mid ）的和，将其转换为0的个数后与k比较，根据比较结果调整二分区间。解决难点在于理解如何通过区间和获取0的个数以及正确调整二分区间。

### 所选的题解
- **作者：liruixiong0101 (5星)**
    - **关键亮点**：思路清晰，详细阐述了二分查找的目标是找到从下标1开始到下标为x的0的个数为k的最小x ，并对二分过程中的细节如t的输入、缓存区清理等做了说明。
    - **个人心得**：强调一定要输入t以及清缓存区，否则会遇到问题。
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int n, t, k, ans;
    int main(){
        ios::sync_with_stdio(0);
        cin.tie(0), cout.tie(0);
        cin >> n >> t >> k;
        int l = 1, r = n;
        for(int l = 1, r = n, mid, res; l <= r;){//二分查找
            mid = (l + r) / 2;
            cout << "? 1 " << mid << endl;//询问1~mid
            cin >> res;
            res = mid - res;//算出0的个数
            if(res >= k){
                ans = mid;
                r = mid - 1;
            }
            else{
                l = mid + 1;
            }
        }
        cout << "! " << ans << endl;//输出
        return 0;
    }
    ```
- **作者：qinshi0308 (4星)**
    - **关键亮点**：简洁明了地阐述二分思路，通过判断x + k与mid的大小关系来确定第k个0的位置在mid的左边还是右边，代码实现简洁。
    ```cpp
    # include <bits/stdc++.h>
    using namespace std;
    inline int work(int n,int k){//二分查找函数 
        int l=1,r=n;
        while(l<=r){
            int mid=(l+r)/2;
            cout<<"? 1 "<<mid<<endl;
            int x;
            cin>>x;
            if(x+k<=mid){
                r=mid-1; 
            }else{
                l=mid+1;
            }
        }
        return l;
    }
    int main(){
        int n,t,k;
        cin>>n>>t>>k;
        cout<<"! "<<work(n,k);
        return 0;
    }
    ```
- **作者：LinkZelda (4星)**
    - **关键亮点**：类比静态全局第k大整数的做法，将问题转化为通过比较区间内0的个数与k的大小来递归查询第k个0所在区间，清晰易懂。
    ```cpp
    int l=1,r=n,ans;
    while(l<=r)
    {
        int mid=(l+r)>>1,ret;
        cout<<"? "<<l<<' '<<mid<<endl;
        cin>>ret;
        ret=(mid-l+1)-ret;
        if(ret>=k)
            ans=mid,r=mid-1;
        else
            k-=ret,l=mid+1;
    }
    cout<<"! "<<ans<<endl;
    ```

### 最优关键思路或技巧
利用二分查找减少查询次数，通过询问区间和并转换为区间内0的个数，以此作为二分的判断依据，快速定位第k个0的位置。同时，注意交互题中输入输出的规范，如清缓存区等操作。

### 可拓展之处
同类型题可考虑改变数组元素类型、查询方式或增加更多限制条件。类似算法套路是对于在一定查询次数内确定某个位置或数值的问题，若数据范围允许，可优先考虑二分查找。通过合理设计二分的判断条件，利用查询结果来调整二分区间。

### 洛谷题目推荐
- P2249 [HNOI2005]狡猾的商人：通过前缀和与二分查找判断账本是否存在矛盾。
- P1873 砍树：二分查找合适的砍树高度，满足一定的木材需求。
- P3853 [TJOI2007]路标设置：二分查找合适的路标间距，使路标数量满足要求。 

---
处理用时：41.66秒