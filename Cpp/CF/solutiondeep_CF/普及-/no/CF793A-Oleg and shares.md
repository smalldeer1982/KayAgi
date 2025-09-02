# 题目信息

# Oleg and shares

## 题目描述

Oleg the bank client checks share prices every day. There are $ n $ share prices he is interested in. Today he observed that each second exactly one of these prices decreases by $ k $ rubles (note that each second exactly one price changes, but at different seconds different prices can change). Prices can become negative. Oleg found this process interesting, and he asked Igor the financial analyst, what is the minimum time needed for all $ n $ prices to become equal, or it is impossible at all? Igor is busy right now, so he asked you to help Oleg. Can you answer this question?

## 说明/提示

Consider the first example.

Suppose the third price decreases in the first second and become equal $ 12 $ rubles, then the first price decreases and becomes equal $ 9 $ rubles, and in the third second the third price decreases again and becomes equal $ 9 $ rubles. In this case all prices become equal $ 9 $ rubles in $ 3 $ seconds.

There could be other possibilities, but this minimizes the time needed for all prices to become equal. Thus the answer is $ 3 $ .

In the second example we can notice that parity of first and second price is different and never changes within described process. Thus prices never can become equal.

In the third example following scenario can take place: firstly, the second price drops, then the third price, and then fourth price. It happens $ 999999999 $ times, and, since in one second only one price can drop, the whole process takes $ 999999999*3=2999999997 $ seconds. We can note that this is the minimum possible time.

## 样例 #1

### 输入

```
3 3
12 9 15
```

### 输出

```
3```

## 样例 #2

### 输入

```
2 2
10 9
```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 1
1 1000000000 1000000000 1000000000
```

### 输出

```
2999999997```

# AI分析结果

### 题目翻译
# Oleg和股票

## 题目描述
Oleg这位银行客户每天都会查看股票价格。他关注 $ n $ 只股票的价格。今天他观察到，每秒钟恰好有一只股票的价格下降 $ k $ 卢布（注意，每秒钟恰好有一只股票的价格发生变化，但在不同的秒数，变化的股票可能不同）。股票价格可能变为负数。Oleg觉得这个过程很有趣，于是他向金融分析师Igor询问，让所有 $ n $ 只股票的价格变得相等所需的最短时间是多少，或者这根本就不可能？Igor现在很忙，所以他让你帮助Oleg。你能回答这个问题吗？

## 说明/提示
考虑第一个样例。

假设在第一秒，第三只股票的价格下降，变为12卢布；然后第一只股票的价格下降，变为9卢布；在第三秒，第三只股票的价格再次下降，变为9卢布。在这种情况下，所有股票的价格在3秒后都变为9卢布。

可能还有其他情况，但这种情况使所有股票价格变得相等所需的时间最短。因此，答案是3。

在第二个样例中，我们可以注意到第一只和第二只股票价格的奇偶性不同，并且在上述过程中奇偶性不会改变。因此，股票价格永远不可能相等。

在第三个样例中，可能会发生以下情况：首先，第二只股票的价格下降，然后是第三只，接着是第四只。这个过程会发生999999999次，由于每秒只能有一只股票的价格下降，整个过程需要999999999 * 3 = 2999999997秒。我们可以注意到，这是最短的可能时间。

## 样例 #1
### 输入
```
3 3
12 9 15
```
### 输出
```
3
```

## 样例 #2
### 输入
```
2 2
10 9
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
4 1
1 1000000000 1000000000 1000000000
```
### 输出
```
2999999997
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是一致的，由于股票价格只能下降，所以要让所有股票价格相等，必然是都降到最小值。先找出最小值，然后判断每只股票价格与最小值的差是否能被 $ k $ 整除，如果存在不能整除的情况，则无法使所有股票价格相等，输出 -1；若都能整除，则将每只股票价格与最小值的差除以 $ k $ 并累加，得到的结果就是使所有股票价格相等所需的最短时间。

### 所选题解
- **LordLaffey（4星）**
  - **关键亮点**：思路清晰，对题目分析详细，代码注释明确，使用了自定义的求最小值函数。
  - **个人心得**：无
- **Utilokasteinn（4星）**
  - **关键亮点**：代码简洁，使用了 `min` 函数和 `exit(0)` 直接结束程序，逻辑清晰。
  - **个人心得**：无
- **lrmlrm_（4星）**
  - **关键亮点**：代码规范，注释中强调了 `long long` 的重要性，避免数据溢出。
  - **个人心得**：无

### 重点代码
#### LordLaffey的代码
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
int a[100010];

ll _min(ll a,ll b) {
    return a<b?a:b;
}

int main(){
    int n,k,Min=2147483647;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        Min=_min(a[i],Min);
    }
    ll ans=0;
    for(int i=1;i<=n;i++) {
        int x=a[i]-Min;
        if(x%k) {
            printf("-1");
            return 0;
        }
        ans+=x/k;
    }
    printf("%lld",ans);
    return 0;
}
```
**核心实现思想**：先读取输入，找出最小值，然后遍历数组，判断每个元素与最小值的差是否能被 $ k $ 整除，若不能则输出 -1 并结束程序，若能则累加差除以 $ k $ 的结果，最后输出答案。

#### Utilokasteinn的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100001],k,minn=1e9,ans;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;minn=min(minn,a[i++]))
        cin>>a[i];
    for(int i=1;i<=n;i++)
        if((a[i]-minn)%k)cout<<-1,exit(0);
        else ans+=(a[i]-minn)/k;
    cout<<ans;
    return 0;
}
```
**核心实现思想**：读取输入的同时更新最小值，然后遍历数组，若元素与最小值的差不能被 $ k $ 整除则输出 -1 并结束程序，否则累加差除以 $ k $ 的结果，最后输出答案。

#### lrmlrm_的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k,mi=2100000000,sum=0; 
long long a[1000010];
int main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        mi=min(a[i],mi);
    }
    for(int i=1;i<=n;i++){
        if((a[i]-mi)%k){sum=-1;break;}
        else sum+=(a[i]-mi)/k; 
    }
    printf("%lld",sum); 
    return 0;
}
```
**核心实现思想**：读取输入并找出最小值，遍历数组，若元素与最小值的差不能被 $ k $ 整除则将结果设为 -1 并跳出循环，否则累加差除以 $ k $ 的结果，最后输出答案。

### 最优关键思路或技巧
- 由于股票价格只能下降，所以让所有股票价格都降到最小值是最优策略。
- 用一个变量记录最小值，遍历数组判断每个元素与最小值的差是否能被 $ k $ 整除，避免不必要的计算。
- 注意使用 `long long` 类型，防止数据溢出。

### 可拓展之处
同类型题可能会有股票价格可以上升或下降的情况，或者有多轮操作等。类似算法套路可以是先分析题目条件，找出最优目标（如本题的最小值），然后根据规则判断是否能达到目标，最后计算达到目标所需的操作次数。

### 推荐洛谷题目
- P1003 [铺地毯](https://www.luogu.com.cn/problem/P1003)
- P1047 [校门外的树](https://www.luogu.com.cn/problem/P1047)
- P1420 [最长连号](https://www.luogu.com.cn/problem/P1420)

---
处理用时：42.44秒