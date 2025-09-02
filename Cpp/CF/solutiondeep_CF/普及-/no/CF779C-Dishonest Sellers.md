# 题目信息

# Dishonest Sellers

## 题目描述

Igor found out discounts in a shop and decided to buy $ n $ items. Discounts at the store will last for a week and Igor knows about each item that its price now is $ a_{i} $ , and after a week of discounts its price will be $ b_{i} $ .

Not all of sellers are honest, so now some products could be more expensive than after a week of discounts.

Igor decided that buy at least $ k $ of items now, but wait with the rest of the week in order to save money as much as possible. Your task is to determine the minimum money that Igor can spend to buy all $ n $ items.

## 说明/提示

In the first example Igor should buy item 3 paying 6. But items 1 and 2 he should buy after a week. He will pay 3 and 1 for them. So in total he will pay $ 6+3+1=10 $ .

In the second example Igor should buy right now items 1, 2, 4 and 5, paying for them 3, 4, 10 and 3, respectively. Item 3 he should buy after a week of discounts, he will pay 5 for it. In total he will spend $ 3+4+10+3+5=25 $ .

## 样例 #1

### 输入

```
3 1
5 4 6
3 1 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 3
3 4 7 10 3
4 5 5 12 5
```

### 输出

```
25
```

# AI分析结果

### 题目翻译
# 不诚实的卖家

## 题目描述
伊戈尔发现一家商店有折扣，于是决定购买 $n$ 件商品。商店的折扣将持续一周，伊戈尔知道每件商品现在的价格是 $a_{i}$，折扣一周后的价格是 $b_{i}$。

并非所有卖家都是诚实的，所以现在有些商品的价格可能比一周后的折扣价还要高。

伊戈尔决定现在至少购买 $k$ 件商品，其余的则等到一周后购买，以便尽可能节省资金。你的任务是确定伊戈尔购买所有 $n$ 件商品所需的最少资金。

## 说明/提示
在第一个示例中，伊戈尔应该现在购买第 3 件商品，花费 6。但他应该在一周后购买第 1 件和第 2 件商品，分别花费 3 和 1。因此，他总共将花费 $6 + 3 + 1 = 10$。

在第二个示例中，伊戈尔应该现在购买第 1、2、4 和 5 件商品，分别花费 3、4、10 和 3。他应该在一周后的折扣期购买第 3 件商品，花费 5。因此，他总共将花费 $3 + 4 + 10 + 3 + 5 = 25$。

## 样例 #1
### 输入
```
3 1
5 4 6
3 1 5
```
### 输出
```
10
```

## 样例 #2
### 输入
```
5 3
3 4 7 10 3
4 5 5 12 5
```
### 输出
```
25
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即尽可能在价格低的时候购买商品，同时满足第一周至少购买 $k$ 件商品的条件。具体做法是计算商品两周价格的差值，然后根据差值进行排序，优先选择差值小（即降价多或涨价少）的商品在第一周购买。

各题解的主要区别在于实现细节，如数据结构的选择（结构体或数组）、排序方式（使用 `sort` 或自定义 `cmp` 函数）以及计算最小花费的具体逻辑。

### 所选题解
- 作者：锦瑟，华年（4星）
  - 关键亮点：思路清晰，代码简洁，使用 `sort` 函数进行排序，通过计算差值并排序来选择最优购买方案。
  - 重点代码：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
int a[200005],b[200005],f[200005];
int main(){
    int n,k,i,ans=0;
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);
        ans+=a[i];//把所有的原价加起来
    }
    for(i=1;i<=n;i++){
        scanf("%d",&b[i]);
        f[i]=b[i]-a[i];//算差值
    }
    sort(f+1,f+1+n);//sort排序
    i=1;
    while(i<=n-k&&f[i]<0){//注意，要特判f[i]<0，白捡的便宜白不捡（多减一点）
        ans+=f[i++];//减一下差值
    }
    printf("%d",ans);
    return 0;
}
```
核心实现思想：先将所有商品的原价相加，然后计算每件商品的价格差值（第二周价格减去第一周价格），对差值进行排序。如果差值为负，说明第二周价格更低，在满足第一周至少购买 $k$ 件商品的条件下，选择这些商品在第二周购买，将差值累加到总花费中。

- 作者：Leap_Frog（4星）
  - 关键亮点：使用结构体存储商品信息，自定义比较函数进行排序，逻辑清晰。
  - 重点代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct good
{
    int fir,sec;
    inline bool operator<(good a) const {return sec-fir>a.sec-a.fir;}
}a[200005];
int n,k,i,ans=0;
int main()
{
    scanf("%d%d",&n,&k);
    for(i=1;i<=n;i++) scanf("%d",&a[i].fir);
    for(i=1;i<=n;i++) scanf("%d",&a[i].sec);
    sort(a+1,a+n+1);
    for(i=1;i<=k||a[i].sec-a[i].fir>0;i++) ans+=a[i].fir;
    for(;i<=n;i++) ans+=a[i].sec;
    printf("%d\n",ans);
    return 0;
}
```
核心实现思想：定义结构体 `good` 存储商品的第一周和第二周价格，自定义比较函数 `operator<` 对商品按价格差值进行排序。先选择前 $k$ 个商品或价格差值为正的商品在第一周购买，其余商品在第二周购买，累加总花费。

- 作者：diqiuyi（4星）
  - 关键亮点：使用结构体和自定义 `cmp` 函数进行排序，思路明确，代码规范。
  - 重点代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0;bool f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return f?x:-x;
}
struct node{
    int a,b;
}s[200005];
//这周与下周
int n,k,ans;
bool cmp(const node &x,const node &y){
    return x.a-x.b<y.a-y.b;
}
//按这周买赚的钱排序
int main(){
    n=read(),k=read();
    for(int i=1;i<=n;i++)
        s[i].a=read();
    for(int i=1;i<=n;i++)
        s[i].b=read();
    sort(s+1,s+n+1,cmp);
    int i;
    for(i=1;i<=k||s[i].a<s[i].b;i++)
        ans+=s[i].a;
    for(;i<=n;i++)
        ans+=s[i].b;
    printf("%d\n",ans);
    return 0;
}
```
核心实现思想：定义结构体 `node` 存储商品的第一周和第二周价格，自定义 `cmp` 函数按第一周购买能节省的钱进行排序。先选择前 $k$ 个商品或第一周价格低于第二周价格的商品在第一周购买，其余商品在第二周购买，累加总花费。

### 最优关键思路或技巧
- 计算商品两周价格的差值，通过排序来确定购买顺序，优先选择差值小的商品在第一周购买。
- 可以使用结构体来存储商品信息，方便进行排序和处理。
- 先将所有商品的原价相加，再根据差值进行调整，简化计算过程。

### 可拓展之处
同类型题目通常涉及在满足一定条件下的最优选择问题，例如在多个时间段内选择最优的任务安排、资源分配等。解题思路一般都是通过贪心算法，根据某个关键指标（如价格差、效率等）进行排序，然后按照一定规则进行选择。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P2240 食草的奶牛](https://www.luogu.com.cn/problem/P2240)

### 个人心得摘录与总结
- 作者：tryrtj 尝试手写 `cmp` 和冒泡排序，结果 TLE，后来意识到数据范围较大，应使用 `sort` 函数进行排序，提醒我们在处理大规模数据时要选择合适的排序算法。

---
处理用时：52.59秒