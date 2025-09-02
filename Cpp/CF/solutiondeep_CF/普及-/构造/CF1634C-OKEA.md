# 题目信息

# OKEA

## 题目描述

People worry that computers will get too smart and take over the world, but the real problem is that they're too stupid and they've already taken over the world.

— Pedro Domingos



You work for a well-known department store that uses leading technologies and employs mechanistic work — that is, robots!

The department you work in sells $ n \cdot k $ items. The first item costs $ 1 $ dollar, the second item costs $ 2 $ dollars, and so on: $ i $ -th item costs $ i $ dollars. The items are situated on shelves. The items form a rectangular grid: there are $ n $ shelves in total, and each shelf contains exactly $ k $ items. We will denote by $ a_{i,j} $ the price of $ j $ -th item (counting from the left) on the $ i $ -th shelf, $ 1 \le i \le n, 1 \le j \le k $ .

Occasionally robots get curious and ponder on the following question: what is the mean price (arithmetic average) of items $ a_{i,l}, a_{i,l+1}, \ldots, a_{i,r} $ for some shelf $ i $ and indices $ l \le r $ ? Unfortunately, the old robots can only work with whole numbers. If the mean price turns out not to be an integer, they break down.

You care about robots' welfare. You want to arrange the items in such a way that the robots cannot theoretically break. Formally, you want to choose such a two-dimensional array $ a $ that:

- Every number from $ 1 $ to $ n \cdot k $ (inclusively) occurs exactly once.
- For each $ i, l, r $ , the mean price of items from $ l $ to $ r $ on $ i $ -th shelf is an integer.

Find out if such an arrangement is possible, and if it is, give any example of such arrangement.

## 样例 #1

### 输入

```
4
1 1
2 2
3 3
3 1```

### 输出

```
YES
1 
YES
1 3 
2 4 
NO
YES
1 
2 
3```

# AI分析结果

### 题目中文重写
## 题目描述

人们担心计算机变得过于智能并统治世界，但真正的问题是它们太愚蠢了，而且已经统治了世界。

——佩德罗·多明戈斯

你在一家著名的百货公司工作，该公司采用领先技术并雇佣机械化工——也就是机器人！

你所在的部门出售 $n \cdot k$ 件商品。第一件商品售价 1 美元，第二件售价 2 美元，依此类推：第 $i$ 件商品售价 $i$ 美元。这些商品放在货架上，形成一个矩形网格：总共有 $n$ 个货架，每个货架正好有 $k$ 件商品。我们用 $a_{i,j}$ 表示第 $i$ 个货架上（从左往右数）第 $j$ 件商品的价格，其中 $1 \le i \le n$，$1 \le j \le k$。

偶尔，机器人会好奇地思考这样一个问题：对于某个货架 $i$ 以及索引 $l \le r$，商品 $a_{i,l}, a_{i,l+1}, \ldots, a_{i,r}$ 的平均价格（算术平均值）是多少？不幸的是，旧机器人只能处理整数。如果平均价格不是整数，它们就会崩溃。

你关心机器人的福祉。你想以一种理论上机器人不会崩溃的方式来摆放商品。正式地说，你想选择一个二维数组 $a$，使得：
- 从 1 到 $n \cdot k$（包含两端）的每个数字恰好出现一次。
- 对于每个 $i, l, r$，第 $i$ 个货架上从 $l$ 到 $r$ 的商品的平均价格是整数。

找出是否存在这样的排列方式，如果存在，请给出任意一种这样的排列。

## 样例 #1
### 输入
```
4
1 1
2 2
3 3
3 1
```

### 输出
```
YES
1 
YES
1 3 
2 4 
NO
YES
1 
2 
3
```

### 综合分析与结论
这些题解的核心思路都是先分析出每行数字奇偶性需相同这一关键条件，再根据 $k$ 和 $n$ 的取值情况进行分类讨论。当 $k = 1$ 时，直接按顺序输出数字；当 $k > 1$ 且 $n$ 为奇数时，无解；当 $k > 1$ 且 $n$ 为偶数时，通过构造满足条件的矩阵来求解。

### 所选题解
- **Yusani_huh（5星）**
    - **关键亮点**：思路清晰，详细推导了满足条件的情况，并给出了构造方法的数学证明，代码简洁易读。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define INF 0x3f3f3f3f
int t,n,k;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        if(n%2&&k>1){
            puts("NO");
            continue;
        }
        else{
            puts("YES");
            if(k==1){
                for(int i=1;i<=n;++i)
                    printf("%d\n",i);
            }
            else{
                int cnt=0;
                for(int i=1;i<=n*k;i+=2){
                    printf("%d",i),cnt++;
                    if(cnt==k) puts(""),cnt=0;
                    else printf(" ");
                }
                for(int i=2;i<=n*k;i+=2){
                    printf("%d",i),cnt++;
                    if(cnt==k) puts(""),cnt=0;
                    else printf(" ");
                }
            }
        }
    }
    return 0;
}
```
    - **核心实现思想**：先判断 $n$ 和 $k$ 的取值情况，若 $n$ 为奇数且 $k > 1$ 则无解；否则有解。当 $k = 1$ 时按顺序输出数字，当 $k > 1$ 时先输出奇数再输出偶数。

- **XiaoQuQu（4星）**
    - **关键亮点**：对分类讨论的情况进行了详细证明，给出了两种构造方式并证明其正确性，代码逻辑清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, k;
int main(void){
    cin >> t;
    while (t--){
        cin >> n >> k;
        if (k == 1){
            cout << "YES" << endl;
            for (int i = 1; i <= n; ++i)  cout << i << endl;
        }
        else if (n & 1)  cout << "NO" << endl;
        else{
            cout << "YES" << endl;
            int x = 1, y = 2;
            for (int i = 1; i <= n; ++i){
                if (i & 1)
                    for (int j = 1; j <= k; ++j)
                    {
                        cout << x << ' ';
                        x += 2;
                    }
                else
                    for (int j = 1; j <= k; ++j)
                    {
                        cout << y << ' ';
                        y += 2;
                    }
                cout << endl;
            }
        }
    }
}
```
    - **核心实现思想**：同样先判断 $k$ 和 $n$ 的取值情况，$k = 1$ 时按顺序输出，$n$ 为奇数且 $k > 1$ 时无解，其他情况通过交替输出奇数和偶数来构造矩阵。

### 最优关键思路或技巧
- **奇偶性分析**：通过分析相邻两数平均数为整数得出每行数字奇偶性需相同，这是解决本题的关键思维方式。
- **等差数列性质**：利用等差数列的和能被项数整除这一性质来构造满足条件的矩阵。

### 可拓展之处
同类型题目可能会改变矩阵的约束条件，如要求每列的某些统计量也满足特定条件，或者改变数字的取值范围等。解题时仍可从分析数字的性质（如奇偶性、整除性）和构造满足条件的结构入手。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：考察二维矩阵的操作和逻辑判断。
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：需要对数字进行排序和组合，涉及数字性质的分析。
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：可通过区间处理的方式解决，锻炼逻辑思维和数组操作能力。

### 个人心得
- **happy_dengziyue**：在比赛时，@[dengzijun](/user/387836) 提供了按列优先顺序依次填入 $n\times k$ 的新方式，且指出填完后改变行的顺序（不改变行内元素顺序）也是可行的。这体现了在解题过程中可以从不同角度思考，借鉴他人思路可能会得到更简单的解法。 

---
处理用时：35.72秒