# 题目信息

# Trading Business

## 题目描述

To get money for a new aeonic blaster, ranger Qwerty decided to engage in trade for a while. He wants to buy some number of items (or probably not to buy anything at all) on one of the planets, and then sell the bought items on another planet. Note that this operation is not repeated, that is, the buying and the selling are made only once. To carry out his plan, Qwerty is going to take a bank loan that covers all expenses and to return the loaned money at the end of the operation (the money is returned without the interest). At the same time, Querty wants to get as much profit as possible.

The system has $ n $ planets in total. On each of them Qwerty can buy or sell items of $ m $ types (such as food, medicine, weapons, alcohol, and so on). For each planet $ i $ and each type of items $ j $ Qwerty knows the following:

- $ a_{ij} $ — the cost of buying an item;
- $ b_{ij} $ — the cost of selling an item;
- $ c_{ij} $ — the number of remaining items.

It is not allowed to buy more than $ c_{ij} $ items of type $ j $ on planet $ i $ , but it is allowed to sell any number of items of any kind.

Knowing that the hold of Qwerty's ship has room for no more than $ k $ items, determine the maximum profit which Qwerty can get.

## 说明/提示

In the first test case you should fly to planet Venus, take a loan on 74 units of money and buy three items of the first type and 7 items of the third type ( $ 3·6+7·8=74 $ ). Then the ranger should fly to planet Earth and sell there all the items he has bought. He gets $ 3·9+7·9=90 $ units of money for the items, he should give 74 of them for the loan. The resulting profit equals 16 units of money. We cannot get more profit in this case.

## 样例 #1

### 输入

```
3 3 10
Venus
6 5 3
7 6 5
8 6 10
Earth
10 9 0
8 6 4
10 9 3
Mars
4 3 0
8 4 12
7 2 5
```

### 输出

```
16```

# AI分析结果

### 题目内容
# 贸易业务

## 题目描述
为了赚钱购买一把全新的永恒爆能枪，游侠Qwerty决定暂时从事贸易活动。他想在其中一个星球上购买一定数量的物品（或者也可能什么都不买），然后在另一个星球上出售这些购买的物品。请注意，此操作仅进行一次，也就是说，购买和销售都只进行一次。为了实施他的计划，Qwerty打算从银行贷款以支付所有费用，并在交易结束时归还贷款（归还贷款时无需支付利息）。同时，Qwerty希望获得尽可能多的利润。

该星系总共有 $n$ 个星球。在每个星球上，Qwerty 都可以买卖 $m$ 种类型的物品（如食品、药品、武器、酒精等等）。对于每个星球 $i$ 和每种物品类型 $j$，Qwerty 知道以下信息：
- $a_{ij}$ —— 购买一件该物品的成本；
- $b_{ij}$ —— 出售一件该物品的收入；
- $c_{ij}$ —— 该物品的剩余数量。

不允许在星球 $i$ 上购买超过 $c_{ij}$ 件类型为 $j$ 的物品，但可以出售任意数量的任何种类物品。

已知 Qwerty 的飞船货舱最多只能容纳 $k$ 件物品，确定 Qwerty 能够获得的最大利润。

## 说明/提示
在第一个测试用例中，你应该飞往金星，贷款74单位货币，购买3件第一种物品和7件第三种物品（$3·6 + 7·8 = 74$）。然后，游侠应该飞往地球，并在那里出售他购买的所有物品。他从这些物品中获得 $3·9 + 7·9 = 90$ 单位货币，他需要归还74单位货币用于偿还贷款。最终利润为16单位货币。在这种情况下，我们无法获得更多利润。

## 样例 #1
### 输入
```
3 3 10
金星
6 5 3
7 6 5
8 6 10
地球
10 9 0
8 6 4
10 9 3
火星
4 3 0
8 4 12
7 2 5
```
### 输出
```
16
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是通过贪心策略解决问题。由于数据规模较小，都采用了暴力枚举两个星球（一个作为购买星球，一个作为销售星球）的方式，然后针对每对星球计算最大收益，最后取所有收益中的最大值。

算法要点在于对每个物品计算其在不同星球间买卖的差价（即收益），并按收益从大到小排序，优先选择收益高的物品购买，直到飞船货舱装满（达到 $k$ 件物品）或者没有正收益的物品可选。

解决难点主要在于如何合理地选择购买的物品以最大化利润，通过贪心策略选择收益高的物品购买，有效解决了这一问题。

### 所选的题解
- **作者：yedalong (赞：4)，星级：4星**
    - **关键亮点**：思路清晰，代码注释详细，对贪心思想的实现过程描述明确，使用 `vector` 存储物品信息，便于理解和操作。
    - **核心代码片段**：
```cpp
struct node{
    int cnt,k;
};
int n,m,k,a[15][105],b[15][105],c[15][105],ans;
bool cmp(node a,node b){
    return a.cnt>b.cnt;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    for(int i = 1;i<=n;i++){
        string s;cin>>s;
        for(int j = 1;j<=m;j++) cin>>a[i][j]>>b[i][j]>>c[i][j];
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            if(j==i) continue;
            vector<node> v;
            int cnt=0,sum=0;
            for(int l = 1;l<=m;l++) v.push_back(node{b[j][l]-a[i][l],c[i][l]});
            sort(v.begin(),v.end(),cmp);
            for(int l = 0;l<v.size();l++){
                if(v[l].cnt<=0) break;
                if(cnt+v[l].k<k) sum+=v[l].k*v[l].cnt,cnt+=v[l].k;
                else{
                    sum+=(k-cnt)*v[l].cnt;
                    break;
                }
            }
            ans=max(ans,sum);
        }
    }
    cout<<ans;
    return 0;
} 
```
    - **核心实现思想**：定义结构体 `node` 存储物品收益 `cnt` 和数量 `k`，通过 `cmp` 函数按收益从大到小排序。枚举购买和销售星球，计算每个物品的收益并存入 `vector`，排序后依次购买收益为正的物品，根据剩余容量决定购买数量，更新最大收益。
- **作者：wangcht (赞：1)，星级：4星**
    - **关键亮点**：代码简洁明了，逻辑清晰，使用结构体存储物品信息，并通过 `sort` 函数按差价排序，整体实现简洁高效。
    - **核心代码片段**：
```cpp
int n,m,k,maxans;
int a[15][105],b[15][105],c[15][105];
string t;
struct node
{
    int w,s;
}x[105];
bool cmp(node a,node b)
{
    return a.w>b.w;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>t;
        for(int j=1;j<=m;j++)
            cin>>a[i][j]>>b[i][j]>>c[i][j];
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            int sum=k,ans=0;
            if(i==j) continue;
            for(int o=1;o<=m;o++)
            {
                x[o].w=b[j][o]-a[i][o];
                x[o].s=c[i][o];
            }
            sort(x+1,x+m+1,cmp);
            for(int o=1;o<=m;o++)
            {
                if(x[o].w<=0) break;
                if(x[o].s>=sum)
                {
                    ans+=sum*x[o].w;
                    break;
                }
                else
                {
                    sum-=x[o].s;
                    ans+=x[o].s*x[o].w;
                }
            }
            maxans=max(maxans,ans);
        }
    cout<<maxans;
    return 0;
}
```
    - **核心实现思想**：定义结构体 `node` 存储物品差价 `w` 和数量 `s`，通过 `cmp` 函数按差价从大到小排序。枚举购买和销售星球，计算每个物品的差价和数量存入结构体数组，排序后依次处理差价为正的物品，根据剩余容量决定购买数量，更新最大收益。
- **作者：Aventurine_stone (赞：1)，星级：4星**
    - **关键亮点**：代码结构清晰，通过自定义 `read` 函数加快输入速度，对每个步骤的实现逻辑描述明确。
    - **核心代码片段**：
```cpp
const int N=110;
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
        x=(x<<1)+(x<<3)+c-'0',c=getchar();
    return x;
}
int n,m,k;
string s;
int a[N][N],b[N][N],c[N][N];
struct object{
    int cha,num;
}d[N];
inline bool cmp(object a1,object a2)
{
    return a1.cha>a2.cha;
}
int sum,ans,x;
int main()
{
    n=read(),m=read(),k=read();
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        for(int j=1;j<=m;j++)
            a[i][j]=read(),b[i][j]=read(),c[i][j]=read();
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            sum=0,x=k;
            if(i==j)
                continue;
            for(int k=1;k<=m;k++)
                d[k].num=c[i][k],d[k].cha=b[j][k]-a[i][k];
            sort(d+1,d+m+1,cmp);
            for(int k=1;k<=m;k++)
            {
                if(d[k].cha>0)
                {
                    if(x>d[k].num)
                    {
                        sum+=d[k].cha*d[k].num;
                        x-=d[k].num;
                    }
                    else
                    {
                        sum+=d[k].cha*x;
                        break;
                    }
                }
                else
                    break; 
            }
            ans=max(ans,sum);
        }
    }
    printf("%d ",ans);
    return 0;
}
```
    - **核心实现思想**：定义结构体 `object` 存储物品差价 `cha` 和数量 `num`，通过 `cmp` 函数按差价从大到小排序。枚举购买和销售星球，计算每个物品的差价和数量存入结构体数组，排序后依次处理差价为正的物品，根据剩余容量决定购买数量，更新最大收益。同时自定义 `read` 函数优化输入。

### 最优关键思路或技巧
1. **贪心策略**：优先选择买卖差价大的物品进行交易，确保每次交易都能获得尽可能多的利润。
2. **暴力枚举**：由于数据规模较小，通过枚举所有可能的购买和销售星球组合，保证不会遗漏最优解。

### 拓展思路
此类题目属于贪心策略在简单经济模型中的应用。类似的题目可能会增加限制条件，如多个交易周期、不同星球间运输成本等。解题时依然可以从贪心的角度出发，分析在新条件下如何选择最优的交易策略。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略每次选择最小的两个果子堆合并，以最小化总代价。
2. [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：利用贪心思想选择最大的数对，使得双方得分最优。
3. [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：通过贪心选择重复次数最多的子串，属于贪心在字符串问题中的应用。

### 个人心得摘录与总结
无个人心得相关内容。 

---
处理用时：77.31秒