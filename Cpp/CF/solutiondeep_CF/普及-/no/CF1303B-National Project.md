# 题目信息

# National Project

## 题目描述

Your company was appointed to lay new asphalt on the highway of length $ n $ . You know that every day you can either repair one unit of the highway (lay new asphalt over one unit of the highway) or skip repairing.

Skipping the repair is necessary because of the climate. The climate in your region is periodical: there are $ g $ days when the weather is good and if you lay new asphalt these days it becomes high-quality pavement; after that, the weather during the next $ b $ days is bad, and if you lay new asphalt these days it becomes low-quality pavement; again $ g $ good days, $ b $ bad days and so on.

You can be sure that you start repairing at the start of a good season, in other words, days $ 1, 2, \dots, g $ are good.

You don't really care about the quality of the highway, you just want to make sure that at least half of the highway will have high-quality pavement. For example, if the $ n = 5 $ then at least $ 3 $ units of the highway should have high quality; if $ n = 4 $ then at least $ 2 $ units should have high quality.

What is the minimum number of days is needed to finish the repair of the whole highway?

## 说明/提示

In the first test case, you can just lay new asphalt each day, since days $ 1, 3, 5 $ are good.

In the second test case, you can also lay new asphalt each day, since days $ 1 $ - $ 8 $ are good.

## 样例 #1

### 输入

```
3
5 1 1
8 10 10
1000000 1 1000000```

### 输出

```
5
8
499999500000```

# AI分析结果

### 题目内容
# 国家项目

## 题目描述
你的公司被指定为长度为$n$的高速公路铺设新的沥青。你知道，每天你要么修复一单位长度的高速公路（在一单位长度的高速公路上铺设新沥青），要么跳过修复。

由于气候原因，跳过修复是必要的。你所在地区的气候是周期性的：有$g$天天气良好，如果你在这些天铺设新沥青，路面会成为高质量的；之后，接下来的$b$天天气不好，如果你在这些天铺设新沥青，路面会成为低质量的；然后又是$g$天好天气，$b$天坏天气，以此类推。

你可以确定你是在好天气季节开始时开始修复的，换句话说，第$1$、$2$、$\cdots$、$g$天是好天气。

你并不真正关心高速公路的质量，你只想确保至少有一半的高速公路有高质量的路面。例如，如果$n = 5$，那么至少$3$单位长度的高速公路应该有高质量；如果$n = 4$，那么至少$2$单位长度的高速公路应该有高质量。

完成整个高速公路的修复最少需要多少天？

## 说明/提示
在第一个测试用例中，你可以每天都铺设新沥青，因为第$1$、$3$、$5$天是好天气。

在第二个测试用例中，你也可以每天都铺设新沥青，因为第$1 - 8$天是好天气。

## 样例 #1
### 输入
```
3
5 1 1
8 10 10
1000000 1 1000000
```
### 输出
```
5
8
499999500000
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕计算完成高速公路修复且保证至少一半为高质量路面所需最少天数展开。核心思路都是基于对好天气、坏天气周期以及所需高质量路面长度的计算。不同之处在于计算方式和特殊情况处理。部分题解通过计算周期数和剩余天数来直接得出结果，有的则采用二分法。在特殊情况处理上，有的题解考虑了好天气与坏天气天数关系等特殊情况的特判。整体来看，多数题解思路清晰，部分题解代码实现较为简洁。

### 所选的题解
- **作者：xiaomuyun (4星)**
  - **关键亮点**：思路清晰，详细阐述了计算答案的过程，明确指出需至少$\left\lceil\ \dfrac{n}{2}\ \right\rceil$天在好天气下施工，将其设为$need$，通过计算周期数$(need÷g)$和剩余天数$(need\bmod g)$得出总天数，同时强调了结果小于$n$时的特判以及周期结束条件判断。
  - **个人心得**：无
  - **重点代码核心思想**：通过计算$need$，结合周期天数$g + b$算出总天数，最后特判结果与$n$的大小关系。
```cpp
// 伪代码示意
// need 为至少需要的好天气天数
// 计算需要的周期数和剩余天数
int cycle_num = need / g;
int remain_days = need % g;
int ans = cycle_num * (g + b);
if (remain_days!= 0) {
    ans += remain_days;
} else {
    ans -= b;
}
if (ans < n) {
    ans = n;
}
```
- **作者：do_while_true (4星)**
  - **关键亮点**：不仅思路清晰，还给出了完整代码。同样先计算出至少需要的好天气天数$maxx$，根据$maxx$与$g$的关系分情况计算总天数，考虑了$maxx\%g$是否为$0$的情况，并且在代码中简洁明了地实现了整个逻辑。
  - **个人心得**：无
  - **重点代码核心思想**：先计算$maxx$，根据$maxx$与$g$的取模结果分情况计算$ans$，最后判断$ans$与$n$的大小关系。
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#define ll unsigned long long
using namespace std;
ll T,n,a,b,maxx,ans,t;
int main()
{
    scanf("%llu",&T);
    for(int i=1;i<=T;i++)
    {
        ans = 0;
        scanf("%llu%llu%llu",&n,&a,&b);
        maxx = (n + 1) / 2;
        if(a >= maxx){
            printf("%llu\n",n);
            continue;
        }
        t = maxx / a;
        ans += (a + b) * t;
        ans += maxx % a;
        if(maxx % a == 0) ans -= b;
        if(ans >= n) printf("%llu\n",ans);
        else printf("%llu\n",n);
    }
    return 0;
}
```
- **作者：NaOH_Frog (4星)**
  - **关键亮点**：采用贪心策略，明确计算好路所需时间、考虑好路修完后坏路是否修完的情况。通过自定义函数实现计算逻辑，代码结构清晰。
  - **个人心得**：无
  - **重点代码核心思想**：先计算天气循环周期、需要修的好路长度、完整循环数以及剩余天数，最后得出总共需要修的天数。
```cpp
long long len(long long n, long long g, long long b){
    long long loop = b + g; //天气循环
    long long good_road = ceil(n, 2); //修多少好路 
    long long num_loop = ceil(good_road, g) - 1; //多少个完整循环, 注意最后一个循环可能不完整 
    long long leftover = good_road - num_loop * g + max(0 * 1LL, (n - good_road) - num_loop * b); //还要再修多少天, 记得特判好路修完坏路没修完的情况 
    return num_loop * loop + leftover; //总共修多少天 
}
```

### 最优关键思路或技巧
通过计算至少需要的好天气天数，结合好天气与坏天气的周期关系，分情况计算总天数，并对结果与高速公路总长度$n$进行比较判断。这种基于数学关系的直接计算方式简洁高效，避免了复杂的搜索或枚举过程。

### 可拓展思路
同类型题可拓展到其他具有周期性条件限制且需满足一定比例要求的任务安排问题。类似算法套路是先确定关键条件（如本题的好天气天数比例），再结合周期规律进行计算，注意特殊情况的处理。

### 洛谷相似题目推荐
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)
- [P1208 [USACO1.3]混合牛奶 Mixing Milk](https://www.luogu.com.cn/problem/P1208)

---
处理用时：66.56秒