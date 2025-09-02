# 题目信息

# [USACO10JAN] Buying Feed, II S

## 题目描述

Farmer John needs to travel to town to pick up K (1 <= K <= 100) pounds of feed. Driving D miles with K pounds of feed in his truck costs D\*K cents.

The county feed lot has N (1 <= N <= 100) stores (conveniently numbered 1..N) that sell feed. Each store is located on a segment of the X axis whose length is E (1 <= E <= 350). Store i is at location X\_i (0 < X\_i < E) on the number line and can sell FJ as much as F\_i (1 <= F\_i <= 100) pounds of feed at a cost of C\_i (1 <= C\_i <= 1,000,000) cents per pound. Amazingly, a given point on the X axis might have more than one store.

FJ starts at location 0 on this number line and can drive only in the positive direction, ultimately arriving at location E, with at least K pounds of feed. He can stop at any of the feed stores along the way and buy any amount of feed up to the the store's limit.

What is the minimum amount FJ has to pay to buy and transport the K pounds of feed? FJ knows there is a solution.

Consider a sample where FJ needs two pounds of feed from three stores (locations: 1, 3, and 4) on a number line whose range is 0..5:

```
0   1   2   3   4   5 
+---|---+---|---|---+ 
    1       1   1      Available pounds of feed 
    1       2   2      Cents per pound 
```
It is best for FJ to buy one pound of feed from both the second and third stores. He must pay two cents to buy each pound of feed for a total cost of 4. When FJ travels from 3 to 4 he is moving 1 unit of length and he has 1 pound of feed so he must pay 1\*1 = 1 cents.

When FJ travels from 4 to 5 he is moving one unit and he has 2 pounds of feed so he must pay 1\*2 = 2 cents.

The total cost is 4+1+2 = 7 cents. 

FJ 开车去买 $K$ 份食物，如果他的车上有 $X$ 份食物。每走一里就花费 $X$ 元。FJ 的城市是一条线，总共 $E$ 里路，有 $E+1$ 个地方，标号 $0\sim E$。 FJ 从 $0$ 开始走，到 $E$ 结束（不能往回走），要买 $K$ 份食物。 城里有 $N$ 个商店，每个商店的位置是 $X_i$（一个点上可能有多个商店），有 $F_i$ 份食物，每份 $C_i$ 元。 问到达 $E$ 并买 $K$ 份食物的最小花费。

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/1720.png)


## 样例 #1

### 输入

```
2 5 3
3 1 2
4 1 2
1 1 1```

### 输出

```
7```

# AI分析结果

### 综合分析与结论
这些题解主要采用贪心和动态规划两种思路来解决问题。贪心思路是将每个商店购买一份食物的总花费（包含路费）计算出来并排序，优先选择花费小的商店购买，直到满足需求；动态规划思路则将问题转化为多重背包问题，通过状态转移方程求解最小花费。

### 所选题解
- **作者：幽界の冥神（5星）**
    - **关键亮点**：代码简洁，注释详细，清晰展示了贪心算法的核心思路，先计算每个商店购买一份食物的总花费，排序后依次购买。
    - **核心代码**：
```cpp
struct food{int val,num;}f[102];
bool cmp(food a,food b){return a.val<b.val;}
int Min(int a,int b){return a<b?a:b;}
int main(){
    int number,s,n,ans=0;
    scanf("%d%d%d",&number,&s,&n);
    for(int i=1,a,b;i<=n;i++){
        scanf("%d%d%d",&a,&f[i].num,&b);
        f[i].val=s-a+b;
    }
    sort(f+1,f+1+n,cmp);
    for(int i=1;i<=n&&number>0;i++){
        ans+=Min(number,f[i].num)*f[i].val;
        number-=f[i].num;
    }
    printf("%d",ans);
    return 0;
}
```
- **作者：tktp_AK（4星）**
    - **关键亮点**：思路清晰，通过结构体存储商店信息，排序后根据当前购买量和所需量的关系决定购买策略。
    - **核心代码**：
```cpp
struct node
{
    int x,f,c;
}a[550];
bool cmp(node x,node y){return x.c<y.c;}
int main()
{
    int k,e,n;scanf("%d%d%d",&k,&e,&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&a[i].x,&a[i].f,&a[i].c);
        a[i].c+=e-a[i].x;
    }
    sort(a+1,a+n+1,cmp);
    long long ans=0,t=0;
    for(int i=1;i<=n;i++)
    {
        if(t+a[i].f>k)
        {
            ans+=(k-t)*a[i].c;
            break;
        }
        else
        {
            ans+=a[i].f*a[i].c;
            t+=a[i].f;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
- **作者：SunsetLake（4星）**
    - **关键亮点**：详细阐述贪心思路，通过结构体存储信息并排序，根据购买情况更新花费和剩余需求量。
    - **核心代码**：
```cpp
struct node{
    int x,f,c,tal;
}st[110];
bool cmp(node s,node g){
    return s.tal<g.tal;
}
int main(){
    int k,e,n,ans;
    cin>>k>>e>>n;
    for(int i=1;i<=n;i++){
        cin>>st[i].x>>st[i].f>>st[i].c;
        st[i].tal=st[i].c+e-st[i].x;
    }
    sort(st+1,st+1+n,cmp);
    for(int i=1;;i++){
        k-=st[i].f;
        if(k>=0){
            ans+=st[i].tal*st[i].f;
        }
        else{
            k+=st[i].f;
            ans+=k*st[i].tal;
            break;
        }
    }
    cout<<ans;
    return 0;
}
```

### 最优关键思路或技巧
- **贪心算法**：将每个商店购买一份食物的总花费（包含从该商店到终点的路费）计算出来，按总花费从小到大排序，优先选择花费小的商店购买，直到满足需求。
- **结构体应用**：使用结构体存储商店的位置、食物数量和单价等信息，方便排序和处理。

### 可拓展之处
同类型题可考虑增加更多限制条件，如每个商店有不同的营业时间，或FJ有时间限制等。类似算法套路可用于资源分配问题，如在多个供应商处采购物品，考虑运输成本和物品单价，求最小总花费。

### 推荐题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：贪心算法，通过排序解决排队接水的时间优化问题。
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心算法，合理分组使分组数最少。
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：贪心算法，选择不重叠的线段使覆盖范围最大。

### 个人心得
- **RatingStar**：提到排序要是升序排列，因为题目说不能往回走，前面买的自然不能比后面的大，否则得不到最优解；还建议函数最好调用库里面有的，尽量不使用STL库，锻炼手打能力。
- **YuanZihan1225**：强调排序要升序，因为题目限制不能往回走，前面买到的必须比后面小才能得到最优解。 

---
处理用时：29.59秒