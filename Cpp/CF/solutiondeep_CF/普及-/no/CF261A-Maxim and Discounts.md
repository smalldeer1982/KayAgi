# 题目信息

# Maxim and Discounts

## 题目描述

Maxim always goes to the supermarket on Sundays. Today the supermarket has a special offer of discount systems.

There are $ m $ types of discounts. We assume that the discounts are indexed from 1 to $ m $ . To use the discount number $ i $ , the customer takes a special basket, where he puts exactly $ q_{i} $ items he buys. Under the terms of the discount system, in addition to the items in the cart the customer can receive at most two items from the supermarket for free. The number of the "free items" (0, 1 or 2) to give is selected by the customer. The only condition imposed on the selected "free items" is as follows: each of them mustn't be more expensive than the cheapest item out of the $ q_{i} $ items in the cart.

Maxim now needs to buy $ n $ items in the shop. Count the minimum sum of money that Maxim needs to buy them, if he use the discount system optimally well.

Please assume that the supermarket has enough carts for any actions. Maxim can use the same discount multiple times. Of course, Maxim can buy items without any discounts.

## 说明/提示

In the first sample Maxim needs to buy two items that cost $ 100 $ and get a discount for two free items that cost $ 50 $ . In that case, Maxim is going to pay $ 200 $ .

In the second sample the best strategy for Maxim is to buy $ 3 $ items and get $ 2 $ items for free using the discount. In that case, Maxim is going to pay $ 150 $ .

## 样例 #1

### 输入

```
1
2
4
50 50 100 100
```

### 输出

```
200
```

## 样例 #2

### 输入

```
2
2 3
5
50 50 50 50 50
```

### 输出

```
150
```

## 样例 #3

### 输入

```
1
1
7
1 1 1 1 1 1 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 马克西姆与折扣

## 题目描述
马克西姆总是在周日去超市。今天，超市推出了特别的折扣活动。

超市有 $m$ 种折扣类型。我们假设折扣从 1 到 $m$ 编号。要使用第 $i$ 种折扣，顾客需拿一个特殊的购物篮，在里面放入恰好 $q_{i}$ 件所购商品。根据折扣规则，除了购物篮里的商品，顾客最多还能从超市免费获得两件商品。“免费商品”的数量（0、1 或 2）由顾客自行选择。对所选“免费商品”的唯一限制如下：每件免费商品的价格不得高于购物篮中 $q_{i}$ 件商品里最便宜的那件商品的价格。

马克西姆现在需要在超市购买 $n$ 件商品。如果他能最优地利用折扣系统，计算他购买这些商品所需的最小金额。

假设超市有足够的购物篮供任何操作使用。马克西姆可以多次使用同一种折扣。当然，马克西姆也可以不使用任何折扣购买商品。

## 说明/提示
在第一个样例中，马克西姆需要购买两件价格为 100 的商品，并利用折扣免费获得两件价格为 50 的商品。在这种情况下，马克西姆将支付 200。

在第二个样例中，马克西姆的最佳策略是购买 3 件商品，并利用折扣免费获得 2 件商品。在这种情况下，马克西姆将支付 150。

## 样例 #1
### 输入
```
1
2
4
50 50 100 100
```
### 输出
```
200
```

## 样例 #2
### 输入
```
2
2 3
5
50 50 50 50 50
```
### 输出
```
150
```

## 样例 #3
### 输入
```
1
1
7
1 1 1 1 1 1 1
```
### 输出
```
3
```

### 算法分类
贪心

### 题解综合分析与结论
这三道题解均采用贪心算法。核心思路是由于每种折扣送的商品个数上限一样，所以选择 $q_i$ 最小的折扣方式能使打折次数更多，从而获得更多免费商品。在选择商品时，为使花费最小，应从价格高的商品开始选，每买满 $q_i$ 件商品，就从剩余商品中选价格最大的两件作为免费商品。

### 所选的题解
- **作者：happy_zero (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，详细说明了排序方向及原因，避免数组越界问题。
    - **重点代码**：
```cpp
bool cmp(int x, int y)
{
    return x > y;
}
int mian()
{
    int n, m, k = INF;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        int x;
        cin >> x;
        k = min(k, x);
    }
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + 1 + n, cmp);
    int ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += a[i];
        cnt++;
        if (cnt % k == 0) i += 2;
    }
    cout << ans << endl;
    return 0;
}
```
    - **核心实现思想**：先找到最小的 $q_i$，对商品价格从大到小排序，遍历商品，每次累加价格，当购买商品数量达到 $q_i$ 时，跳过后续两件商品作为免费商品。
- **作者：Transparent (4星)**
    - **关键亮点**：开头详细解释题目大意，对贪心思路阐述清晰，代码注释丰富。
    - **个人心得**：提到翻译题目范围出错导致运行错误，提醒不要过度依赖翻译。
    - **重点代码**：
```cpp
int main()
{
    scanf("%d",&m);
    for(register int i=1;i<=m;++i)
    {
        scanf("%d",&tmp);
        minq=min(minq,tmp); 
    }
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
    {
        scanf("%d",a+i);
    }
    sort(a+1,a+n+1);
    int nowa=n,nownum=0,ans=0;
    while(nowa>0)
    {
        ans+=a[nowa];
        ++nownum;
        --nowa; 
        if(nownum==minq)
        {
            nownum=0;
            nowa-=2; 
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
    - **核心实现思想**：找到最小的 $q_i$，对商品价格从小到大排序，从后往前遍历商品，累加价格，当未参与促销商品数量达到 $q_i$ 时，将后续两件商品视为赠品。
- **作者：XL4453 (4星)**
    - **关键亮点**：简洁地阐述贪心思路，代码简洁高效。
    - **重点代码**：
```cpp
int main(){
    scanf("%d",&m);
    for(int i=1;i<=m;i++)scanf("%d",&x),minx=min(minx,x);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    int cnt=0;
    for(int i=n;i>=1;i--){
        cnt++;
        ans+=a[i];
        if(cnt==minx)i-=2,cnt=0;
    }
    printf("%d",ans);
    return 0;
}
```
    - **核心实现思想**：与Transparent类似，先找最小 $q_i$，对商品价格从小到大排序，从后往前遍历，统计购买商品数量，满 $q_i$ 时跳过两件商品作为赠品。

### 最优关键思路或技巧
- **贪心策略**：选择 $q_i$ 最小的折扣方式，从价格高的商品开始选择购买，保证每次获得的免费商品价值最大化。
- **排序技巧**：无论是从大到小还是从小到大排序，关键是要配合正确的遍历方向，避免数组越界等问题。

### 拓展思路
此类题目属于贪心策略在实际场景中的应用，类似题目常通过改变折扣规则、商品条件等进行变形。比如改变免费商品数量限制、增加商品种类限制等。解题关键在于分析各种条件对最终结果的影响，找到最优的贪心策略。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)

---
处理用时：60.60秒