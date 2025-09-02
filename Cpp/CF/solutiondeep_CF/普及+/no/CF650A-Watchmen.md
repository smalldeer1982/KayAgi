# 题目信息

# Watchmen

## 题目描述

Watchmen are in a danger and Doctor Manhattan together with his friend Daniel Dreiberg should warn them as soon as possible. There are $ n $ watchmen on a plane, the $ i $ -th watchman is located at point $ (x_{i},y_{i}) $ .

They need to arrange a plan, but there are some difficulties on their way. As you know, Doctor Manhattan considers the distance between watchmen $ i $ and $ j $ to be $ |x_{i}-x_{j}|+|y_{i}-y_{j}| $ . Daniel, as an ordinary person, calculates the distance using the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF650A/fcefde1ea60e1105aa698e148af7dc900a7454c9.png).

The success of the operation relies on the number of pairs $ (i,j) $ ( $ 1<=i&lt;j<=n $ ), such that the distance between watchman $ i $ and watchmen $ j $ calculated by Doctor Manhattan is equal to the distance between them calculated by Daniel. You were asked to compute the number of such pairs.

## 说明/提示

In the first sample, the distance between watchman $ 1 $ and watchman $ 2 $ is equal to $ |1-7|+|1-5|=10 $ for Doctor Manhattan and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF650A/91477f866a0e0d69e03fe1418359568f2f96b567.png) for Daniel. For pairs $ (1,1) $ , $ (1,5) $ and $ (7,5) $ , $ (1,5) $ Doctor Manhattan and Daniel will calculate the same distances.

## 样例 #1

### 输入

```
3
1 1
7 5
1 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 0
0 1
0 2
-1 1
0 1
1 1
```

### 输出

```
11
```

# AI分析结果

### 题目内容
# 守望者

## 题目描述
守望者们正处于危险之中，曼哈顿博士和他的朋友丹尼尔·德雷伯格需要尽快警告他们。平面上有\(n\)个守望者，第\(i\)个守望者位于点\((x_{i},y_{i})\) 。

他们需要制定一个计划，但他们面临一些困难。如你所知，曼哈顿博士认为守望者\(i\)和\(j\)之间的距离为\(|x_{i}-x_{j}|+|y_{i}-y_{j}|\)。而丹尼尔作为一个普通人，使用公式\(\sqrt{(x_{i}-x_{j})^2+(y_{i}-y_{j})^2}\)来计算距离。

行动的成功取决于满足\(1\leq i < j\leq n\)的点对\((i,j)\)的数量，即曼哈顿博士计算出的守望者\(i\)和\(j\)之间的距离等于丹尼尔计算出的距离的点对数量。你需要计算这样的点对数量。

## 说明/提示
在第一个样例中，对于曼哈顿博士来说，守望者\(1\)和守望者\(2\)之间的距离为\(|1 - 7|+|1 - 5| = 10\)，对于丹尼尔来说为\(\sqrt{(1 - 7)^2+(1 - 5)^2}=\sqrt{36 + 16}=\sqrt{52}\)。对于点对\((1,1)\)，\((1,5)\)和\((7,5)\) ，\((1,5)\)，曼哈顿博士和丹尼尔将计算出相同的距离。

## 样例 #1
### 输入
```
3
1 1
7 5
1 5
```
### 输出
```
2
```

## 样例 #2
### 输入
```
6
0 0
0 1
0 2
-1 1
0 1
1 1
```
### 输出
```
11
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先通过数学推导得出当两点间横坐标相等或者纵坐标相等时，其曼哈顿距离等于欧几里得距离。然后通过不同方式统计这样的点对数量。主要难点在于处理重复点对的情况，避免重复计数。各题解在实现细节上有所不同，有的使用`map`，有的使用`unordered_map`，有的在去重方式上有差异。

### 所选的题解
- **作者：yuzhechuan (5星)**
    - **关键亮点**：思路清晰，先详细推导公式得出关键结论，再介绍算法，还提及`map`与`unordered_map`复杂度差异并进行优化，对`make_pair`进行补充说明。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
unordered_map<int,int> X,Y;
map<pair<int,int>,int> p;
long long ans; 
int n;
signed main(){
    scanf("%d",&n);
    for(int i=1,x,y;i<=n;i++){
        scanf("%d%d",&x,&y);
        ans+=X[x]+Y[y]-p[make_pair(x,y)];
        X[x]++;
        Y[y]++;
        p[make_pair(x,y)]++;
    }
    printf("%I64d",ans);
}
```
    - **核心实现思想**：使用`unordered_map`记录横坐标和纵坐标出现次数，`map`记录点坐标出现次数，每次读入点时，通过容斥原理计算当前点与之前点满足条件的点对数量并累加到答案中，同时更新各映射表。

- **作者：_Han (4星)**
    - **关键亮点**：简洁明了地阐述题意和解题思路，通过推导公式得出关键结论，代码实现简洁，使用`map`维护横纵坐标相同点的数量，并利用容斥原理计算方案数。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define int long long
using namespace std;
int x,y,n,ans;
map<int,int> m1,m2;
map<pair<int,int>,int> m3; 
inline int read()
{
    // 读入优化函数
}
signed main()
{
    n=read();
    for (int i=1;i<=n;i++)
    {
        x=read(); y=read();
        ans+=(m1[x]+m2[y]-m3[mp(x,y)]); 
        m1[x]++; m2[y]++; m3[mp(x,y)]++; 
    }
    cout<<ans<<endl;
}
```
    - **核心实现思想**：与上一题解类似，通过三个`map`分别记录横坐标、纵坐标、点坐标出现次数，每次读入新点，利用容斥原理更新答案并维护`map`。

- **作者：SamHJD (4星)**
    - **关键亮点**：先直观解释曼哈顿距离和欧几里得距离概念，通过图形辅助理解得出关键结论，代码实现简洁易懂，利用`map`统计坐标出现次数，并通过容斥原理计算答案。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
map<ll,ll> mp,mp1;
map<pair<ll,ll>,ll> mp2;
ll n,ans;
int main(){
    cin>>n;
    for(ll i=1;i<=n;++i){
        ll x,y;
        scanf("%d%d",&x,&y);
        ans+=mp[x]+mp1[y];
        ans-=mp2[make_pair(x,y)];
        mp[x]++;
        mp1[y]++;
        mp2[make_pair(x,y)]++;
    }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：利用三个`map`分别记录横坐标、纵坐标、点坐标出现次数，读入每个点时，通过容斥原理累加满足条件的点对数量到答案，并更新`map`。

### 最优关键思路或技巧
利用数学推导得出关键结论，即横坐标或纵坐标相等时曼哈顿距离等于欧几里得距离。使用`map`或`unordered_map`数据结构统计坐标出现次数，通过容斥原理避免重复计算点对数量。

### 拓展
同类型题通常围绕几何距离概念，结合数学推导和数据统计。类似套路是先通过数学分析得出关键条件，再选择合适的数据结构统计相关信息，处理好重复计数问题。

### 推荐洛谷题目
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：涉及简单数据统计和条件判断，与本题统计满足条件数量类似。
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)：需要数学推导和枚举统计，与本题推导结论后统计数量思路类似。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：结合数学知识（斐波那契数列性质和最大公约数）与数据处理，锻炼数学分析和代码实现能力。 

---
处理用时：68.11秒