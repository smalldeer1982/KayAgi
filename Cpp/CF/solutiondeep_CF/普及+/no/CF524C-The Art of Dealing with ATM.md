# 题目信息

# The Art of Dealing with ATM

## 题目描述

ATMs of a well-known bank of a small country are arranged so that they can not give any amount of money requested by the user. Due to the limited size of the bill dispenser (the device that is directly giving money from an ATM) and some peculiarities of the ATM structure, you can get at most $ k $ bills from it, and the bills may be of at most two distinct denominations.

For example, if a country uses bills with denominations $ 10 $ , $ 50 $ , $ 100 $ , $ 500 $ , $ 1000 $ and $ 5000 $ burles, then at $ k=20 $ such ATM can give sums $ 100000 $ burles and $ 96000 $ burles, but it cannot give sums $ 99000 $ and $ 101000 $ burles.

Let's suppose that the country uses bills of $ n $ distinct denominations, and the ATM that you are using has an unlimited number of bills of each type. You know that during the day you will need to withdraw a certain amount of cash $ q $ times. You know that when the ATM has multiple ways to give money, it chooses the one which requires the minimum number of bills, or displays an error message if it cannot be done. Determine the result of each of the $ q $ of requests for cash withdrawal.

## 样例 #1

### 输入

```
6 20
10 50 100 500 1000 5000
8
4200
100000
95000
96000
99000
10100
2015
9950
```

### 输出

```
6
20
19
20
-1
3
-1
-1
```

## 样例 #2

### 输入

```
5 2
1 2 3 5 8
8
1
3
5
7
9
11
13
15
```

### 输出

```
1
1
1
2
2
2
2
-1
```

# AI分析结果

### 题目内容
# 处理ATM的技巧

## 题目描述
某小国家一家知名银行的ATM机设置为无法提供用户要求的任意金额。由于取款机（直接从ATM机出钱的设备）的容量有限以及ATM机结构的一些特殊性，你最多能从它那里取出 $k$ 张钞票，并且这些钞票最多只能有两种不同的面额。

例如，如果一个国家使用面额为 $10$、$50$、$100$、$500$、$1000$ 和 $5000$ 卢布的钞票，那么在 $k = 20$ 的情况下，这样的ATM机能给出 $100000$ 卢布和 $96000$ 卢布，但不能给出 $99000$ 卢布和 $101000$ 卢布。

假设这个国家使用 $n$ 种不同面额的钞票，并且你正在使用的ATM机每种面额的钞票数量都不受限制。你知道在一天中你需要取款 $q$ 次。你知道当ATM机有多种给钱方式时，它会选择所需钞票数量最少的那种方式，如果无法做到则显示错误信息。确定这 $q$ 次取款请求中每次的结果。

## 样例 #1
### 输入
```
6 20
10 50 100 500 1000 5000
8
4200
100000
95000
96000
99000
10100
2015
9950
```
### 输出
```
6
20
19
20
-1
3
-1
-1
```

## 样例 #2
### 输入
```
5 2
1 2 3 5 8
8
1
3
5
7
9
11
13
15
```
### 输出
```
1
1
1
2
2
2
2
-1
```

### 算法分类
搜索（枚举 + 二分查找优化）

### 题解综合分析与结论
该题解的思路是先计算出每种面额在不同张数下能构成的钱数，存放在二维vector中，第一维表示张数，第二维表示对应张数的面值和可能值，并对每个张数对应的面值和进行排序。对于每次取款请求，从小到大枚举使用的张数 $i$，对于每个 $i$ 再枚举单种面值构成的钱数，计算与目标金额的差值 $y$。若 $y$ 为0则更新答案；若 $y$ 小于等于0则退出当前张数的枚举。若 $y$ 大于0，则再枚举剩下的张数 $k$，通过二分查找找到能补上差值 $y$ 的最小张数组合，更新答案。若最终未找到合适组合则输出 -1。

算法要点在于通过枚举和二分查找结合来降低时间复杂度，难点在于合理组织数据结构（使用二维vector）以及多层循环和二分查找的嵌套逻辑实现。

### 所选的题解
 - **星级**：3星
 - **关键亮点**：利用vector存储不同张数下每种面额能构成的钱数，并通过排序和二分查找优化搜索过程。
 - **个人心得**：作者提到一开始用数组实现遇到困难，改用vector后变得简单，意识到要好好学习STL。

### 重点代码核心实现思想
先通过两层循环计算单种面值不同张数能构成的钱数并存入vector，再对每个张数对应的vector进行排序。对于每次取款请求，通过多层循环枚举和二分查找尝试找到满足条件的最小张数组合。

### 核心代码片段
```cpp
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
using namespace std;
vector<int> v[25];	//第一维表示第 i 张钱 
int main()			//第二维表示 i 张钱的面值和的可能值 
{
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin >> x;
        for(int j=1;j<=m;j++)
            v[j].push_back(x*j);//单种面值能构成的钱 
    }   
    for(int i=1;i<=m;i++)
        sort(v[i].begin(),v[i].end());//从小到大排 
    int q;
    cin >> q;
    while(q--)
    {
        int x;
        cin >> x;
        int ans = inf;
        for(int i=1;i<=m;i++)//从小到大枚举用的张数 
            for(int j=0;j<v[i].size();j++)
            {                //从小到大枚举可能构成的钱数 
                int y=x-v[i][j];//看现在的钱数和目标钱数的差 
                if(y<=0)
                {
                    if(!y)
                        ans = min(ans,i);//刚好构成,更新答案 
                    break;//太多了,退出 
                }
                for(int k=1;k<=m-i;k++)    //不够的情况枚举取 m-i 张牌 
                {                        //二分找到第一个大于等于这个差值的数     
                    int p=lower_bound(v[k].begin(),v[k].end(),y)-v[k].begin(); 
                //    cout << p << " " << y << endl; 
                    if(p<v[k].size()&&v[k][p] == y)//刚好补差值,更新答案 
                        ans = min(ans,i+k);
                }
            }
        if(ans == inf)
            cout << -1;
        else
            cout << ans;
        cout << endl;
    }
} 
```

### 通用建议与扩展思路
对于此类问题，还可以考虑使用动态规划的方法来优化时间复杂度，例如通过状态转移方程记录已经计算过的状态，避免重复计算。也可以进一步思考如何在数据规模更大时优化空间复杂度。

### 相似知识点洛谷题目
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及枚举和组合相关知识点。
 - [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：可以用动态规划或枚举解决，与本题在处理有限资源组合问题上有相似性。
 - [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：深度优先搜索类型题目，与本题在搜索思路上有一定关联。 

---
处理用时：60.33秒