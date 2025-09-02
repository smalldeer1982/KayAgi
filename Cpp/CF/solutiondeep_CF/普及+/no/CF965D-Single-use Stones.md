# 题目信息

# Single-use Stones

## 题目描述

A lot of frogs want to cross a river. A river is $ w $ units width, but frogs can only jump $ l $ units long, where $ l < w $ . Frogs can also jump on lengths shorter than $ l $ . but can't jump longer. Hopefully, there are some stones in the river to help them.

The stones are located at integer distances from the banks. There are $ a_i $ stones at the distance of $ i $ units from the bank the frogs are currently at. Each stone can only be used once by one frog, after that it drowns in the water.

What is the maximum number of frogs that can cross the river, given that then can only jump on the stones?

## 说明/提示

In the first sample two frogs can use the different stones at the distance $ 5 $ , and one frog can use the stones at the distances $ 3 $ and then $ 8 $ .

In the second sample although there are two stones at the distance $ 5 $ , that does not help. The three paths are: $ 0 \to 3 \to 6 \to 9 \to 10 $ , $ 0 \to 2 \to 5 \to 8 \to 10 $ , $ 0 \to 1 \to 4 \to 7 \to 10 $ .

## 样例 #1

### 输入

```
10 5
0 0 1 0 2 0 0 1 0
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 3
1 1 1 1 2 1 1 1 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 一次性石头

## 题目描述
许多青蛙想要过河。河宽为 $w$ 单位，但青蛙一次只能跳 $l$ 单位长，其中 $l < w$ 。青蛙也能跳小于 $l$ 的距离，但不能跳得更远。幸运的是，河里有一些石头可以帮助它们。

这些石头位于离河岸整数距离处。距离青蛙当前所在河岸 $i$ 单位的地方有 $a_i$ 块石头。每块石头只能被一只青蛙使用一次，之后就会沉入水中。

假设青蛙只能踩在石头上，那么最多有多少只青蛙可以过河？

## 说明/提示
在第一个样例中，两只青蛙可以使用距离为 $5$ 的不同石头，还有一只青蛙可以先使用距离为 $3$ 的石头，然后使用距离为 $8$ 的石头。

在第二个样例中，尽管距离为 $5$ 的地方有两块石头，但这并没有帮助。三条路径分别是：$0 \to 3 \to 6 \to 9 \to 10$ ，$0 \to 2 \to 5 \to 8 \to 10$ ，$0 \to 1 \to 4 \to 7 \to 10$ 。

## 样例 #1
### 输入
```
10 5
0 0 1 0 2 0 0 1 0
```
### 输出
```
3
```

## 样例 #2
### 输入
```
10 3
1 1 1 1 2 1 1 1 1
```
### 输出
```
3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，认为最多通过的青蛙数量就是每个长度为 $l$ 的区间中石头数量的最小值。因为青蛙每次跳跃距离不超过 $l$，必然会在每个长度为 $l$ 的区间至少落脚一次，所以能通过的青蛙数受限于石头数量最少的区间。各题解主要围绕如何高效统计每个长度为 $l$ 的区间内石头数量并找出最小值展开，有的使用前缀和数组，有的通过动态更新区间和来实现。

### 所选的题解
- **作者：lichenfan (5星)**
  - **关键亮点**：思路清晰，先阐述整体思路，再详细说明代码实现细节。利用前缀和数组计算每个区间的石头数量，代码简洁明了，易读性高。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long                 
int w,l,a[100010],sum[100010],ans=999999999;                 //sum数组代表前缀和 
signed main()
{
    cin>>w>>l;
    for(int i=1;i<w;i++) cin>>a[i],sum[i]=sum[i-1]+a[i]; //计算前缀和 
    for(int i=0;i<w-l;i++) ans=min(sum[i+l]-sum[i],ans); //计算这一段青蛙能跳的距离，有几个石头够它调到下一组 
    cout<<ans;                                           //ans取最小值，因为只要有一段跳不过去，青蛙就过不去 
} 
```
  - **核心实现思想**：首先通过循环读入石头数量并计算前缀和。然后遍历每个长度为 $l$ 的区间，通过前缀和相减得到区间内石头数量，不断更新最小值作为最终答案。
- **作者：XL4453 (4星)**
  - **关键亮点**：不仅给出解题思路，还对结论从两个方面进行了证明，逻辑严谨。代码简洁，直接利用前缀和数组计算并找出最小值。
  - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int w,l,a[100005],ans;
int main(){
    scanf("%d%d",&w,&l);
    for(int i=1;i<w;i++)
        scanf("%d",&a[i]),a[i]+=a[i-1];
    ans=2147483647;
    for(int i=l;i<w;i++)
        ans=min(ans,a[i]-a[i-l]);
    printf("%d",ans);
    return 0;
}
```
  - **核心实现思想**：读入数据时同时构建前缀和数组。之后遍历从长度为 $l$ 的区间开始往后的所有区间，通过前缀和差值得到区间内石头数并更新最小值。
- **作者：Hisaishi_Kanade (4星)**
  - **关键亮点**：对题意和思路阐述详细，逐步分析得出结论。代码注释丰富，结构清晰，使用前缀和数组求解。
  - **重点代码**：
```cpp
#include <stdio.h>
const int maxn=100005;
int w,l,len,i,ans=1<<30;
//w,l同题面。
//len即区间个数
//i为循环变量
//ans为结果，要求min
int a[maxn],s[maxn];
//a[]同题面
//s[]是前缀和数组
int main(){
    scanf("%d %d",&w,&l);
    for(i=1;i<w;++i){
        scanf("%d",&a[i]);//读入a[i]
        s[i]=s[i-1]+a[i]; //求前缀和数组
    }
    len=w-l;//求区间个数
    for(i=0;i<len;++i)
        if(s[i+l]-s[i]<ans)
            ans=s[i+l]-s[i];//求结果，s[i+l]-s[i]就是该区间a[i]之和
    printf("%d",ans);//输出
    return 0;
}
```
  - **核心实现思想**：先读入数据并构建前缀和数组，然后计算区间个数。通过遍历每个区间，利用前缀和差值判断并更新最小值作为答案。

### 最优关键思路或技巧
利用前缀和数组来高效计算每个长度为 $l$ 的区间内石头的数量，从而快速找出最小值。这种方法避免了每次都重新计算区间和，降低了时间复杂度。

### 拓展思路
同类型题通常围绕路径选择、资源分配等场景，通过寻找局部最优解来得到全局最优解。类似算法套路是在一些具有区间限制条件的问题中，通过合理利用数据结构（如前缀和数组）来优化计算区间内元素和等操作，进而解决问题。

### 洛谷题目推荐
- **P1090 [NOIP2004 提高组] 合并果子**：通过贪心策略，每次选择最小的两个果子堆合并，与本题选择区间内石头数量最小值思路类似，都基于贪心思想解决资源合并与分配问题。
- **P1199 [NOIP2010 普及组] 三国游戏**：同样需要通过分析游戏规则，利用贪心策略来确定最优的选择方式，锻炼对贪心策略的运用能力。
- **P2123 皇后游戏**：通过对数据的分析和排序，采用贪心策略解决问题，考验对贪心算法的理解和应用，以及对数据处理的技巧。 

---
处理用时：58.90秒