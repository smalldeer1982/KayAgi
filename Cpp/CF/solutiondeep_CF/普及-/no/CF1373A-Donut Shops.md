# 题目信息

# Donut Shops

## 题目描述

There are two rival donut shops.

The first shop sells donuts at retail: each donut costs $ a $ dollars.

The second shop sells donuts only in bulk: box of $ b $ donuts costs $ c $ dollars. So if you want to buy $ x $ donuts from this shop, then you have to buy the smallest number of boxes such that the total number of donuts in them is greater or equal to $ x $ .

You want to determine two positive integer values:

1. how many donuts can you buy so that they are strictly cheaper in the first shop than in the second shop?
2. how many donuts can you buy so that they are strictly cheaper in the second shop than in the first shop?

If any of these values doesn't exist then that value should be equal to $ -1 $ . If there are multiple possible answers, then print any of them.

 The printed values should be less or equal to $ 10^9 $ . It can be shown that under the given constraints such values always exist if any values exist at all.

## 说明/提示

In the first testcase buying any number of donuts will be cheaper in the second shop. For example, for $ 3 $ or $ 5 $ donuts you'll have to buy a box of $ 10 $ donuts for $ 4 $ dollars. $ 3 $ or $ 5 $ donuts in the first shop would cost you $ 15 $ or $ 25 $ dollars, respectively, however. For $ 20 $ donuts you'll have to buy two boxes for $ 8 $ dollars total. Note that $ 3 $ and $ 5 $ are also valid answers for the second shop, along with many other answers.

In the second testcase buying any number of donuts will be either cheaper in the first shop or the same price. $ 8 $ donuts cost $ 32 $ dollars in the first shop and $ 40 $ dollars in the second shop (because you have to buy two boxes). $ 10 $ donuts will cost $ 40 $ dollars in both shops, so $ 10 $ is not a valid answer for any of the shops.

In the third testcase $ 1 $ donut costs $ 2 $ and $ 3 $ dollars, respectively. $ 2 $ donuts cost $ 4 $ and $ 3 $ dollars. Thus, $ 1 $ is a valid answer for the first shop and $ 2 $ is a valid answer for the second shop.

In the fourth testcase $ 10^9 $ donuts cost $ 10^{18} $ dollars in the first shop and $ 10^9 $ dollars in the second shop.

## 样例 #1

### 输入

```
4
5 10 4
4 5 20
2 2 3
1000000000 1000000000 1000000000```

### 输出

```
-1 20
8 -1
1 2
-1 1000000000```

# AI分析结果

### 题目内容
# 甜甜圈店

## 题目描述
有两家相互竞争的甜甜圈店。
第一家店以零售方式售卖甜甜圈：每个甜甜圈售价\(a\)美元。
第二家店仅以批量方式售卖甜甜圈：一盒有\(b\)个甜甜圈，售价为\(c\)美元。所以，如果你想从这家店购买\(x\)个甜甜圈，那么你必须购买最小数量的盒子，使得盒子中甜甜圈的总数大于或等于\(x\)。
你需要确定两个正整数值：
1. 购买多少个甜甜圈时，在第一家店购买比在第二家店购买更便宜？
2. 购买多少个甜甜圈时，在第二家店购买比在第一家店购买更便宜？
如果这两个值中的任何一个不存在，那么该值应设为\(-1\)。如果有多个可能的答案，那么打印其中任何一个。
打印的值应小于或等于\(10^9\)。可以证明，在给定的约束条件下，如果存在任何值，那么这样的值总是存在的。

## 说明/提示
在第一个测试用例中，购买任何数量的甜甜圈在第二家店都会更便宜。例如，购买\(3\)个或\(5\)个甜甜圈时，你必须购买一盒\(10\)个甜甜圈，花费\(4\)美元。然而，在第一家店购买\(3\)个或\(5\)个甜甜圈分别需要花费\(15\)美元或\(25\)美元。购买\(20\)个甜甜圈时，你必须购买两盒，总共花费\(8\)美元。注意，对于第二家店，\(3\)和\(5\)也是有效的答案，还有许多其他答案。
在第二个测试用例中，购买任何数量的甜甜圈要么在第一家店更便宜，要么价格相同。\(8\)个甜甜圈在第一家店花费\(32\)美元，在第二家店花费\(40\)美元（因为你必须购买两盒）。\(10\)个甜甜圈在两家店都花费\(40\)美元，所以\(10\)不是任何一家店的有效答案。
在第三个测试用例中，\(1\)个甜甜圈分别花费\(2\)美元和\(3\)美元。\(2\)个甜甜圈分别花费\(4\)美元和\(3\)美元。因此，\(1\)是第一家店的有效答案，\(2\)是第二家店的有效答案。
在第四个测试用例中，\(10^9\)个甜甜圈在第一家店花费\(10^{18}\)美元，在第二家店花费\(10^9\)美元。

## 样例 #1
### 输入
```
4
5 10 4
4 5 20
2 2 3
1000000000 1000000000 1000000000
```

### 输出
```
-1 20
8 -1
1 2
-1 1000000000
```

### 算法分类
数学

### 题解综合分析与结论
所有题解核心思路均围绕比较两家店购买甜甜圈的价格来确定答案。主要通过比较单个甜甜圈价格\(a\)与整盒甜甜圈平均价格\(\frac{c}{b}\)，以及单个甜甜圈价格\(a\)与整盒甜甜圈价格\(c\)的关系来求解。
- **思路方面**：多数题解先考虑第一家店买\(1\)个甜甜圈与第二家店整盒价格比较，判断第一问；再通过比较第一家店买\(b\)个甜甜圈价格与第二家店整盒价格判断第二问。部分题解如“cyh_toby”还从理论上进一步分析了价格关系成立的条件。
- **算法要点**：关键在于准确判断不同价格比较条件下的结果输出，即何时输出具体购买数量，何时输出\(-1\)。
- **解决难点**：难点在于理解题目中第二家店按盒购买不能拆分且需满足数量要求的条件，并据此合理构建价格比较逻辑。

### 所选的题解
- **作者：zct_sky (5星)**
  - **关键亮点**：思路清晰简洁，直接通过两次简单的价格比较得出结果，代码实现高效明了。
  - **重点代码**：
```c++
#include <bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
ll t,a,b,c;
int main(){
    cin>>t;
    for(ll i=0;i<t;i++){
        cin>>a>>b>>c;
        if(a>=c) cout<<"-1 ";
        else cout<<"1 ";
        if(a*b<=c) cout<<"-1\n";
        else cout<<b<<"\n";
    }
    return 0; 
}
```
  - **核心实现思想**：先判断\(a\)与\(c\)的大小，若\(a\geq c\)，第一家店买单个不可能比第二家店便宜，输出\(-1\)，否则输出\(1\)；再判断\(a\times b\)与\(c\)的大小，若\(a\times b\leq c\)，第二家店买一盒不可能比第一家店便宜，输出\(-1\)，否则输出\(b\)。
- **作者：cyh_toby (5星)**
  - **关键亮点**：对两种购买方案价格比较的情况分析全面细致，从理论层面深入推导何时第一家店更便宜、何时第二家店更便宜，逻辑严谨。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        ll a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        if (a < (double)c / b) {
            printf("1 -1\n");
            continue;
        }
        if (a < c) {
            printf("1 ");
        }
        else {
            printf("-1 ");
        }
        if (a*b > c) {
            printf("%lld\n", b);
        }
        else
            printf("-1\n");
    }
    return 0;
}
```
  - **核心实现思想**：先判断\(a\)与\(\frac{c}{b}\)的大小，若\(a < \frac{c}{b}\)，则第一家店买任何数量都更便宜，输出\(1 -1\)；否则再判断\(a\)与\(c\)的大小决定第一问输出；最后通过判断\(a\times b\)与\(c\)的大小决定第二问输出。
- **作者：b6e0_ (4星)**
  - **关键亮点**：思路简洁直接，针对两个问题分别选取购买\(1\)个和购买\(b\)个甜甜圈的情况进行价格比较，快速得出结论，代码简洁高效。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if(a>=c)
            cout<<"-1 ";
        else
            cout<<"1 ";
        if(c>=a*b)
            cout<<"-1\n";
        else
            cout<<b<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：与“zct_sky”类似，先比较\(a\)与\(c\)确定第一问输出，再比较\(c\)与\(a\times b\)确定第二问输出。

### 最优关键思路或技巧
通过分析极端购买情况（第一家店买\(1\)个，第二家店买\(b\)个）来构建价格比较逻辑，快速确定满足条件的购买数量。这种思维方式简化了问题，避免了复杂的枚举或计算。

### 拓展
此类题目属于简单的数学比较类问题，类似套路是通过分析题目条件找到关键比较量，构建合理的比较逻辑。同类型题目如比较不同套餐购买商品的性价比等。

### 洛谷推荐题目
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：同样是比较不同购买套餐的价格，选择最优购买方案。
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过比较不同活动安排下的时间等因素，得出最优结果。
- [P1425 小鱼的游泳时间](https://www.luogu.com.cn/problem/P1425)：涉及时间计算与比较，与本题比较价格的逻辑类似。 

---
处理用时：62.11秒