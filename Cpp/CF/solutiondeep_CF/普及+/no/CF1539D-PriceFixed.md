# 题目信息

# PriceFixed

## 题目描述

Lena is the most economical girl in Moscow. So, when her dad asks her to buy some food for a trip to the country, she goes to the best store — "PriceFixed". Here are some rules of that store:

- The store has an infinite number of items of every product.
- All products have the same price: $ 2 $ rubles per item.
- For every product $ i $ there is a discount for experienced buyers: if you buy $ b_i $ items of products (of any type, not necessarily type $ i $ ), then for all future purchases of the $ i $ -th product there is a $ 50\% $ discount (so you can buy an item of the $ i $ -th product for $ 1 $ ruble!).

Lena needs to buy $ n $ products: she must purchase at least $ a_i $ items of the $ i $ -th product. Help Lena to calculate the minimum amount of money she needs to spend if she optimally chooses the order of purchasing. Note that if she wants, she can buy more items of some product than needed.

## 说明/提示

In the first example, Lena can purchase the products in the following way:

1. one item of product $ 3 $ for $ 2 $ rubles,
2. one item of product $ 1 $ for $ 2 $ rubles,
3. one item of product $ 1 $ for $ 2 $ rubles,
4. one item of product $ 2 $ for $ 1 $ ruble (she can use the discount because $ 3 $ items are already purchased),
5. one item of product $ 1 $ for $ 1 $ ruble (she can use the discount because $ 4 $ items are already purchased).

In total, she spends $ 8 $ rubles. It can be proved that it is impossible to spend less.

In the second example Lena can purchase the products in the following way:

1. one item of product $ 1 $ for $ 2 $ rubles,
2. two items of product $ 2 $ for $ 2 $ rubles for each,
3. one item of product $ 5 $ for $ 2 $ rubles,
4. one item of product $ 3 $ for $ 1 $ ruble,
5. two items of product $ 4 $ for $ 1 $ ruble for each,
6. one item of product $ 1 $ for $ 1 $ ruble.

In total, she spends $ 12 $ rubles.

## 样例 #1

### 输入

```
3
3 4
1 3
1 5```

### 输出

```
8```

## 样例 #2

### 输入

```
5
2 7
2 8
1 2
2 4
1 8```

### 输出

```
12```

# AI分析结果

### 题目内容中文重写
# 固定价格

## 题目描述
莉娜是莫斯科最节俭的女孩。所以，当她爸爸让她为乡村之旅购买一些食物时，她去了最好的商店——“固定价格”。该商店有以下规则：
- 商店里每种商品都有无限数量。
- 所有商品的价格相同：每件 2 卢布。
- 对于每种商品 $i$，有一个针对老顾客的折扣：如果你购买了 $b_i$ 件商品（任何类型，不一定是第 $i$ 种商品），那么对于后续购买的第 $i$ 种商品将有 50% 的折扣（因此你可以以 1 卢布的价格购买第 $i$ 种商品！）

莉娜需要购买 $n$ 种商品：她必须至少购买第 $i$ 种商品 $a_i$ 件。帮助莉娜计算，如果她以最优顺序购买，她需要花费的最少金额。注意，如果她愿意，她可以购买比所需数量更多的某种商品。

## 说明/提示
在第一个样例中，莉娜可以按以下方式购买商品：
1. 以 2 卢布的价格购买 1 件商品 3。
2. 以 2 卢布的价格购买 1 件商品 1。
3. 以 2 卢布的价格购买 1 件商品 1。
4. 以 1 卢布的价格购买 1 件商品 2（她可以使用折扣，因为已经购买了 3 件商品）。
5. 以 1 卢布的价格购买 1 件商品 1（她可以使用折扣，因为已经购买了 4 件商品）。

总共，她花费了 8 卢布。可以证明不可能花费更少。

在第二个样例中，莉娜可以按以下方式购买商品：
1. 以 2 卢布的价格购买 1 件商品 1。
2. 以每件 2 卢布的价格购买 2 件商品 2。
3. 以 2 卢布的价格购买 1 件商品 5。
4. 以 1 卢布的价格购买 1 件商品 3。
5. 以每件 1 卢布的价格购买 2 件商品 4。
6. 以 1 卢布的价格购买 1 件商品 1。

总共，她花费了 12 卢布。

## 样例 #1
### 输入
```
3
3 4
1 3
1 5
```
### 输出
```
8
```

## 样例 #2
### 输入
```
5
2 7
2 8
1 2
2 4
1 8
```
### 输出
```
12
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，通过合理安排商品的购买顺序来使总花费最小。大部分题解先将商品按 $b_i$ 排序，然后根据当前已购买商品数量和商品的 $b_i$ 值，分情况讨论购买策略：若有商品可以打折，就优先买完；若没有，则购买 $b_i$ 大的商品，促使更多商品打折。不同题解在实现细节和代码风格上有所差异，但整体思路一致。

### 所选题解
- **Acc_Robin（5星）**
    - **关键亮点**：思路清晰，对贪心策略的解释详细，代码实现简洁，使用碰撞指针从两侧向中间逼近，复杂度为 $O(n\log n)$。
    - **个人心得**：做完这题，感觉自己不会买东西了。
- **StayAlone（4星）**
    - **关键亮点**：对代码逐行解释，适合初学者理解，同样使用双指针实现贪心策略。
    - **个人心得**：这道题目还是有一定思考难度的，虽然代码很短，但不一定很好理解，当时做的时候想到脑子爆炸。
- **nalemy（4星）**
    - **关键亮点**：对贪心策略的正确性分析透彻，通过维护两个碰撞指针实现算法，复杂度为 $O(n\log n)$。

### 重点代码
#### Acc_Robin 的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
    const int N = 1e5+10;
#define int long long
    struct node{int a,b;}a[N];
    int z,n;
    void work(){
        cin>>n;
        for(int x,y,i=1;i<=n;i++)cin>>x>>y,a[i]={x,y};
        sort(a+1,a+n+1,[](node x,node y){return x.b<y.b;});
        for(int l=1,r=n,s=0,x;l<=r;)
            if(a[l].b<=s)s+=a[l].a,z+=a[l].a,l++;
            else{
                s+=(x=min(a[r].a,a[l].b-s)),z+=x*2,a[r].a-=x;
                if(!a[r].a)r--;
            }
        cout<<z<<'\n';
    }
#undef int
}
int main(){
    return Acc::work(),0;
}
```
**核心实现思想**：先将商品按 $b_i$ 升序排序，然后使用双指针 $l$ 和 $r$ 分别指向 $b_i$ 最小和最大的商品。若 $a[l].b\leq s$（$s$ 为已购买商品数量），则以 1 元价格买完 $a[l]$；否则，购买 $a[r]$ 直到有新商品打折或 $a[r]$ 买够。

#### StayAlone 的核心代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define fr(i, l, r) for (int i = l; i <= r; ++i)
using namespace std;
int n; ll prsum;
struct node
{
    ll a, b;
}vn[100010];

bool cmp(const node &x, const node &y)
{
    return x.b > y.b;
}

int main()
{
    scanf("%d", &n);
    ll nd = 0, t = 0;
    fr(i, 1, n) scanf("%lld%lld", &vn[i].a, &vn[i].b), nd += vn[i].a;
    sort(vn + 1, vn + 1 + n, cmp);
    int l = 1, r = n;
    while (t^nd)
    {
        if (t >= vn[r].b) t += vn[r].a, prsum += vn[r].a, r--;
        else if (t + vn[l].a >= vn[r].b) vn[l].a -= vn[r].b - t, prsum += (vn[r].b - t) * 2, t = vn[r].b;
        else t += vn[l].a, prsum += vn[l].a * 2, l++;
    }
    printf("%lld", prsum);
    return 0;
}
```
**核心实现思想**：将商品按 $b_i$ 降序排序，$l$ 表示用原价购买的商品，$r$ 表示打折购买的商品。根据当前已购买商品数量 $t$ 与 $vn[r].b$ 的关系分三种情况处理，直到买够所有商品。

#### nalemy 的核心代码
```C++
#include<iostream>
#include<algorithm>
#define N 100000
#define a second
#define b first
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

pii o[N];
int main() {
    ll n, ans = 0; cin >> n;
    for (int i=0; i<n; i++) cin >> o[i].a >> o[i].b; sort(o, o+n);
    for (ll l=0, r=n-1, cnt=0, t; l<=r; o[r].a ? 0 : r--)
        if (o[l].b > cnt)
            cnt += t=min(o[l].b-cnt, o[r].a), ans += 2*t, o[r].a -= t;
        else cnt += t=o[l++].a, ans += t;
    return cout << ans, 0;
}
```
**核心实现思想**：将商品按 $b_i$ 升序排序，使用双指针 $l$ 和 $r$。若 $o[l].b > cnt$（$cnt$ 为已购买商品数量），则购买 $o[r]$ 直到有新商品打折；否则，以 1 元价格买完 $o[l]$。

### 最优关键思路或技巧
- **贪心策略**：优先购买能打折的商品，若没有则购买 $b_i$ 大的商品，促使更多商品打折。
- **双指针技巧**：通过维护两个指针，分别指向 $b_i$ 最小和最大的商品，从两端向中间逼近，高效模拟购买过程。

### 可拓展之处
同类型题可能会改变商品的价格规则、折扣条件或增加其他限制，解题思路仍然可以基于贪心算法，根据具体条件调整购买策略。类似算法套路可以应用于资源分配、任务调度等问题，通过合理安排顺序来优化目标函数。

### 推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得总结
- Acc_Robin 做完题后感觉自己不会买东西了，说明该题的贪心策略与日常思维有差异。
- StayAlone 认为题目有思考难度，代码虽短但不好理解，做的时候想到脑子爆炸，体现了该题的思维挑战。 

---
处理用时：70.04秒