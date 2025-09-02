# 题目信息

# Sereja and Coat Rack

## 题目描述

Sereja owns a restaurant for $ n $ people. The restaurant hall has a coat rack with $ n $ hooks. Each restaurant visitor can use a hook to hang his clothes on it. Using the $ i $ -th hook costs $ a_{i} $ rubles. Only one person can hang clothes on one hook.

Tonight Sereja expects $ m $ guests in the restaurant. Naturally, each guest wants to hang his clothes on an available hook with minimum price (if there are multiple such hooks, he chooses any of them). However if the moment a guest arrives the rack has no available hooks, Sereja must pay a $ d $ ruble fine to the guest.

Help Sereja find out the profit in rubles (possibly negative) that he will get tonight. You can assume that before the guests arrive, all hooks on the rack are available, all guests come at different time, nobody besides the $ m $ guests is visiting Sereja's restaurant tonight.

## 说明/提示

In the first test both hooks will be used, so Sereja gets $ 1+2=3 $ rubles.

In the second test both hooks will be used but Sereja pays a fine $ 8 $ times, so the answer is $ 3-8=-5 $ .

## 样例 #1

### 输入

```
2 1
2 1
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 1
2 1
10
```

### 输出

```
-5
```

# AI分析结果

### 题目内容
# Sereja和衣帽架

## 题目描述
Sereja拥有一家可容纳$n$人的餐厅。餐厅大厅有一个带有$n$个挂钩的衣帽架。每位餐厅访客可以使用一个挂钩来挂衣服。使用第$i$个挂钩需要花费$a_{i}$卢布。一个挂钩只能供一人挂衣服。

今晚Sereja预计有$m$位客人来餐厅。自然地，每位客人都想将衣服挂在价格最低的可用挂钩上（如果有多个这样的挂钩，他会任选其一）。然而，如果客人到达时衣帽架上没有可用挂钩，Sereja必须向该客人支付$d$卢布的罚款。

帮助Sereja计算今晚他将获得的利润（可能为负）。你可以假设在客人到达之前，衣帽架上的所有挂钩都是可用的，所有客人在不同时间到达，并且今晚除了这$m$位客人之外，没有其他人来Sereja的餐厅。

## 说明/提示
在第一个测试用例中，两个挂钩都会被使用，所以Sereja得到$1 + 2 = 3$卢布。

在第二个测试用例中，两个挂钩都会被使用，但Sereja要支付$8$次罚款，所以答案是$3 - 8 = -5$。

## 样例 #1
### 输入
```
2 1
2 1
2
```
### 输出
```
3
```
## 样例 #2
### 输入
```
2 1
2 1
10
```
### 输出
```
-5
```

### 算法分类
贪心

### 综合分析与结论
所有题解的核心思路都是基于贪心策略。由于客人总是选择最便宜的可用挂钩，所以先对挂钩价格进行排序。然后根据客人数量$m$和挂钩数量$n$的关系进行分类讨论：
 - **$m \leq n$时**：客人能使用部分挂钩，收益为排序后前$m$个挂钩价格之和。
 - **$m > n$时**：客人会用完所有挂钩，收益为所有挂钩价格之和减去$(m - n) \times d$（即罚款金额）。
各题解的主要区别在于代码实现细节，如变量命名、计算方式、边界处理等，但整体思路和算法要点基本一致。

### 所选的题解
 - **作者：Halberd_Cease（5星）**
    - **关键亮点**：思路清晰，代码简洁明了，直接根据$n$和$m$的大小关系进行计算，先计算所有挂钩价格总和，再根据不同情况处理，减少重复计算。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[110];
int n,d,m;
int total;
main()
{
    cin>>n>>d;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        total+=a[i];
    }
    cin>>m; 
    if(m>=n)
    {
        cout<<total-(m-n)*d;
        return 0;
    }
    total=0;
    sort(a+1,a+n+1);
    for(int i=1;i<=m;i++)
    {
        total+=a[i];
    }
    cout<<total;
}
```
    - **核心实现思想**：先读入挂钩价格并计算总和`total`，读入客人数量$m$后，若$m \geq n$，直接输出`total - (m - n) * d`；若$m < n$，重新计算前$m$个挂钩价格之和并输出。
 - **作者：WilliamFranklin（5星）**
    - **关键亮点**：先求出整个数列之和，然后根据$m$与$n$的不同关系，通过不同方式处理，逻辑清晰，代码可读性高。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int main() {
	int n, d, m, ans = 0;
	cin >> n >> d;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		ans += a[i];
	}
	cin >> m;
	sort(a + 1, a + n + 1);
	if (m == n) {
		cout << ans;
	} else if (m < n) {
		int sum = 0;
		for (int j = n; j > m; j--) {
			sum += a[j];
		}
		cout << ans - sum;
	} else {
		cout << ans - (m - n) * d;
	}
	return 0;
} 
```
    - **核心实现思想**：读入挂钩价格并累加至`ans`，读入$m$后排序，根据$m$与$n$的关系，$m == n$时直接输出`ans`；$m < n$时计算并减去后$n - m$个挂钩价格；$m > n$时减去罚款金额。
 - **作者：chenjingfei（4星）**
    - **关键亮点**：通过分类讨论，代码结构清晰，易于理解，使用`while(~scanf())`可处理多组输入数据。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,m,sum,s;
int a[10000];
int main()
{    
    while(~scanf("%d%d",&n,&d))
    {
        memset(a,0,sizeof(a));
        s = 0;
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            s+=a[i];
        }
        sort(a,a+n);
        scanf("%d",&m);
        if(m==n)printf("%d\n",s);
        else if(m>n)
        {
            s-=(m-n)*d;
            printf("%d\n",s);
        }
        else if(m<n)
        {
            sum=0;
            for(int i=0;i<m;i++)sum+=a[i];
            printf("%d\n",sum);
        }
    }
    return 0;
}
```
    - **核心实现思想**：通过`while`循环处理多组输入，读入挂钩价格并累加至`s`，排序后根据$m$与$n$的关系分别计算并输出结果。

### 最优关键思路或技巧
 - **排序**：利用客人总是选择最便宜挂钩这一特性，对挂钩价格进行排序，方便后续计算收益。
 - **分类讨论**：根据客人数量和挂钩数量的关系进行分类讨论，清晰地计算出不同情况下的利润。

### 拓展思路
此类题目属于贪心策略应用，类似题目通常会给出一些资源和需求，每个需求对资源有一定选择倾向，可通过排序和分类讨论，依据贪心思想解决问题。例如，任务分配问题，每个任务有不同收益，每个机器有不同处理能力，按照一定规则（如任务收益从高到低，机器处理能力从大到小）进行分配，以获取最大收益。

### 洛谷相似题目
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略，每次选择最小的两个果子堆合并，以最小化总代价。
 - [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：根据武将武力值排序，利用贪心思想，在双方最优策略下计算得分。
 - [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：通过对奶牛产奶模式排序，利用贪心找到出现次数不少于$k$次的最长子串。 

---
处理用时：64.44秒