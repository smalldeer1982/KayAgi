# 题目信息

# 2D Traveling

## 题目描述

Piggy lives on an infinite plane with the Cartesian coordinate system on it.

There are $ n $ cities on the plane, numbered from $ 1 $ to $ n $ , and the first $ k $ cities are defined as major cities. The coordinates of the $ i $ -th city are $ (x_i,y_i) $ .

Piggy, as a well-experienced traveller, wants to have a relaxing trip after Zhongkao examination. Currently, he is in city $ a $ , and he wants to travel to city $ b $ by air. You can fly between any two cities, and you can visit several cities in any order while travelling, but the final destination must be city $ b $ .

Because of active trade between major cities, it's possible to travel by plane between them for free. Formally, the price of an air ticket $ f(i,j) $ between two cities $ i $ and $ j $ is defined as follows:

 $ $$$ f(i,j)= \begin{cases} 0, & \text{if cities }i \text{ and }j \text{ are both major cities} \\ |x_i-x_j|+|y_i-y_j|, & \text{otherwise} \end{cases}  $ $$$

Piggy doesn't want to save time, but he wants to save money. So you need to tell him the minimum value of the total cost of all air tickets if he can take any number of flights.

## 说明/提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1869B/5d562a7fae0997b047c9a0448bd832cdb0a43e6a.png) The major cities are marked red.The optimal way to choose the flights is: $ 3\rightarrow 1 \rightarrow 2 \rightarrow 5 $ , which will cost $ 3+0+1=4 $ . Note that the flight $ 1\rightarrow 2 $ costs $ 0 $ , because both city $ 1 $ and $ 2 $ are major cities.

In the second test case, since there are only $ 2 $ cities, the only way is to take a flight from city $ 1 $ to $ 2 $ .

In the third test case, since city $ 2 $ and $ 4 $ are both major cities, Piggy can directly take a flight from city $ 2 $ to $ 4 $ , which costs $ 0 $ .

In the fourth test case, Piggy can choose to take the following flights: $ 3\rightarrow 2\rightarrow 1 $ , and the cost is $ 11+11=22 $ .

## 样例 #1

### 输入

```
5
6 2 3 5
0 0
1 -2
-2 1
-1 3
2 -2
-3 -3
2 0 1 2
-1000000000 -1000000000
1000000000 1000000000
7 5 4 2
154 147
-154 -147
123 456
20 23
43 20
998 244
353 100
3 1 3 1
0 10
1 20
2 30
4 3 2 4
0 0
-100 100
-1 -1
-1 0```

### 输出

```
4
4000000000
0
22
1```

# AI分析结果

### 题目翻译
# 二维旅行

## 题目描述
小猪生活在一个带有笛卡尔坐标系的无限平面上。

平面上有 $n$ 个城市，编号从 $1$ 到 $n$，前 $k$ 个城市被定义为主要城市。第 $i$ 个城市的坐标是 $(x_i, y_i)$。

小猪作为一位经验丰富的旅行者，想在中考后进行一次轻松的旅行。目前，他在城市 $a$，并且他想乘飞机前往城市 $b$。你可以在任意两个城市之间飞行，并且在旅行过程中可以按任意顺序访问多个城市，但最终目的地必须是城市 $b$。

由于主要城市之间的贸易活跃，在它们之间乘飞机旅行是免费的。形式上，两个城市 $i$ 和 $j$ 之间的机票价格 $f(i, j)$ 定义如下：
$$
f(i,j)= 
\begin{cases}
0, & \text{如果城市 }i \text{ 和 }j \text{ 都是主要城市} \\
|x_i - x_j| + |y_i - y_j|, & \text{否则}
\end{cases}
$$
小猪不想节省时间，但他想节省费用。因此，你需要告诉他，如果他可以乘坐任意数量的航班，所有机票总费用的最小值是多少。

## 说明/提示
在第一个测试用例中：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1869B/5d562a7fae0997b047c9a0448bd832cdb0a43e6a.png) 主要城市用红色标记。选择航班的最优方式是：$3 \rightarrow 1 \rightarrow 2 \rightarrow 5$，费用为 $3 + 0 + 1 = 4$。注意，航班 $1 \rightarrow 2$ 的费用为 $0$，因为城市 $1$ 和 $2$ 都是主要城市。

在第二个测试用例中，由于只有 $2$ 个城市，唯一的方式是从城市 $1$ 乘坐航班到城市 $2$。

在第三个测试用例中，由于城市 $2$ 和 $4$ 都是主要城市，小猪可以直接从城市 $2$ 乘坐航班到城市 $4$，费用为 $0$。

在第四个测试用例中，小猪可以选择乘坐以下航班：$3 \rightarrow 2 \rightarrow 1$，费用为 $11 + 11 = 22$。

## 样例 #1

### 输入
```
5
6 2 3 5
0 0
1 -2
-2 1
-1 3
2 -2
-3 -3
2 0 1 2
-1000000000 -1000000000
1000000000 1000000000
7 5 4 2
154 147
-154 -147
123 456
20 23
43 20
998 244
353 100
3 1 3 1
0 10
1 20
2 30
4 3 2 4
0 0
-100 100
-1 -1
-1 0
```

### 输出
```
4
4000000000
0
22
1
```

### 算法分类
贪心

### 分析与结论
题目要求在一个二维平面的城市图中，找到从城市 $a$ 到城市 $b$ 的最小花费路径。城市间的花费规则为：若两个城市都是主要城市（前 $k$ 个城市），则花费为 $0$；否则，花费为两个城市的曼哈顿距离。

### 题解评分与选择
- **include13_fAKe**：4星。思路清晰，对各种情况的分析全面，代码实现简洁，有注释和提醒，如打开 `long long` 防止溢出。
- **One_JuRuo**：4星。思路简洁明了，对选择路径的理由分析合理，代码实现规范，有特判情况的处理。
- **BugGod**：4星。明确指出两种情况，对坑点的提醒很实用，代码结构清晰。

### 关键思路与技巧
- **贪心策略**：只考虑直接从 $a$ 到 $b$ 和通过主要城市中转这两种情况，取花费较小的路径。
- **预处理**：提前计算出离 $a$ 和 $b$ 最近的主要城市的距离，减少重复计算。
- **特判**：对于 $a$ 和 $b$ 都是主要城市的情况，直接输出 $0$。

### 拓展思路
同类型题目可能会改变城市间的花费规则，或者增加更多的限制条件，如每个城市有不同的停留费用等。解题思路仍然可以从贪心的角度出发，分析不同路径的花费情况，选择最优解。

### 推荐题目
1. [P9065](https://www.luogu.com.cn/problem/P9065)
2. 待补充（可根据具体知识点在洛谷上查找）
3. 待补充（可根据具体知识点在洛谷上查找）

### 个人心得
- **BugGod**：提醒计算 $a,b$ 与中转点距离的变量要初始化，且不能太大，否则会溢出；不要用 `memset`，会 TLE；要开 `long long` 防止溢出。

### 重点代码
#### include13_fAKe
```cpp
void solve(){
    cin>>n>>k>>a>>b;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    if(a<=k&&b<=k){
        puts("0");
        return;
    }
    if(a<=k||b<=k){
        int c=max(a,b);
        int ans=1e18;
        for(int i=1;i<=k;i++){
            ans=min(ans,abs(x[c]-x[i])+abs(y[c]-y[i]));
        }
        cout<<ans<<endl;
        return;
    }
    int ans1=1e18,ans2=1e18;
    int ans3=abs(x[b]-x[a])+abs(y[b]-y[a]);
    for(int i=1;i<=k;i++){
        ans1=min(ans1,abs(x[a]-x[i])+abs(y[a]-y[i]));
        ans2=min(ans2,abs(x[b]-x[i])+abs(y[b]-y[i]));
    }
    cout<<min(ans1+ans2,ans3)<<endl;
    return ;
}
```
**核心思想**：根据 $a$ 和 $b$ 是否为主要城市分情况讨论，对于不是主要城市的情况，枚举主要城市找到最小花费，最后比较直接从 $a$ 到 $b$ 和通过主要城市中转的花费，取最小值。

#### One_JuRuo
```cpp
while(T--)
{
    scanf("%lld%lld%lld%lld",&n,&k,&a,&b),ans1=ans2=0x3f3f3f3f3f3f3f3f;
    for(long long i=1;i<=n;++i) scanf("%lld%lld",&x[i],&y[i]);
    if(a<=k) ans1=0;
    else for(long long i=1;i<=k;++i) ans1=min(ans1,abs(x[i]-x[a])+abs(y[i]-y[a]));
    if(b<=k) ans2=0;
    else for(long long i=1;i<=k;++i) ans2=min(ans2,abs(x[i]-x[b])+abs(y[i]-y[b]));
    printf("%lld\n",min(ans1+ans2,abs(x[a]-x[b])+abs(y[a]-y[b])));
}
```
**核心思想**：分别计算离 $a$ 和 $b$ 最近的主要城市的距离，若 $a$ 或 $b$ 是主要城市，则距离为 $0$，最后比较直接从 $a$ 到 $b$ 和通过主要城市中转的花费，取最小值。

#### BugGod
```cpp
while(t--)
{
    ak=1e18;
    bk=1e18;
    cin>>n>>k>>a>>b;
    for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
    if(a>k)
    {
        for(int i=1;i<=k;i++)
        {
            ak=min(ak,dis(a,i));
        }
    }
    else ak=0;
    if(b>k)
    {
        for(int i=1;i<=k;i++)
        {
            bk=min(bk,dis(b,i));
        }
    }
    else bk=0;
    cout<<min(ak+bk,dis(a,b))<<endl;
}
```
**核心思想**：计算 $a$ 和 $b$ 到主要城市的最小距离，若 $a$ 或 $b$ 是主要城市，则距离为 $0$，最后比较直接从 $a$ 到 $b$ 和通过主要城市中转的花费，取最小值。

---
处理用时：50.64秒