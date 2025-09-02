# 题目信息

# Tanya and Toys

## 题目描述

In Berland recently a new collection of toys went on sale. This collection consists of $ 10^{9} $ types of toys, numbered with integers from $ 1 $ to $ 10^{9} $ . A toy from the new collection of the $ i $ -th type costs $ i $ bourles.

Tania has managed to collect $ n $ different types of toys $ a_{1},a_{2},...,a_{n} $ from the new collection. Today is Tanya's birthday, and her mother decided to spend no more than $ m $ bourles on the gift to the daughter. Tanya will choose several different types of toys from the new collection as a gift. Of course, she does not want to get a type of toy which she already has.

Tanya wants to have as many distinct types of toys in her collection as possible as the result. The new collection is too diverse, and Tanya is too little, so she asks you to help her in this.

## 说明/提示

In the first sample mom should buy two toys: one toy of the $ 2 $ -nd type and one toy of the $ 5 $ -th type. At any other purchase for $ 7 $ bourles (assuming that the toys of types $ 1 $ , $ 3 $ and $ 4 $ have already been bought), it is impossible to buy two and more toys.

## 样例 #1

### 输入

```
3 7
1 3 4
```

### 输出

```
2
2 5 
```

## 样例 #2

### 输入

```
4 14
4 6 12 8
```

### 输出

```
4
7 2 3 1
```

# AI分析结果

### 题目中文重写
# 坦尼娅和玩具

## 题目描述
在伯兰，最近有一系列新玩具上市。这个系列共有 $10^{9}$ 种玩具，编号从 $1$ 到 $10^{9}$。新系列中第 $i$ 种玩具的价格为 $i$ 伯尔（货币单位）。

坦尼娅已经收集到了新系列中的 $n$ 种不同玩具，编号分别为 $a_{1},a_{2},\cdots,a_{n}$。今天是坦尼娅的生日，她的妈妈决定在给女儿的礼物上花费不超过 $m$ 伯尔。坦尼娅会从新系列中挑选几种不同的玩具作为礼物。当然，她不希望得到已经拥有的玩具类型。

坦尼娅希望最终能拥有尽可能多不同类型的玩具。新系列的玩具种类太多，而坦尼娅还太小，所以她请你帮忙解决这个问题。

## 说明/提示
在第一个样例中，妈妈应该买两种玩具：一个编号为 $2$ 的玩具和一个编号为 $5$ 的玩具。在花费 $7$ 伯尔的情况下（假设编号为 $1$、$3$ 和 $4$ 的玩具已经买过），不可能买到两个或更多的玩具。

## 样例 #1
### 输入
```
3 7
1 3 4
```
### 输出
```
2
2 5 
```

## 样例 #2
### 输入
```
4 14
4 6 12 8
```
### 输出
```
4
7 2 3 1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即优先选择价格低的玩具，以用有限的钱买到最多的玩具。各题解的主要区别在于数据结构的选择和实现细节：
- **数据结构选择**：部分题解使用 `map` 或 `set` 来标记已有的玩具，能处理较大范围的数据，但有一定时间复杂度；部分题解使用数组标记，在数据范围较小时更高效。
- **实现细节**：有的题解直接从 $1$ 枚举到一个较大值，有的题解根据数学推导缩小枚举范围。

### 所选的题解
- **柳下惠（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接体现了贪心算法的核心思想。
- **MuYC（4星）**
    - **关键亮点**：对答案范围进行数学推导，缩小枚举范围，优化了时间复杂度。
    - **个人心得**：一开始看成要把钱花完，实际不需要，还建议题目注明 $SPJ$，并认为题目数据水，可增大数据或下调难度评分。
- **liuyongle（4星）**
    - **关键亮点**：使用 `vector` 存储结果，代码规范，还给出了 C++11 及以上标准的遍历方式。

### 重点代码
#### 柳下惠
```cpp
n=read(),m=read();
for(int i=1,t;i<=n;i++)
{
    t=read();
    a[t]=1;
}
for(int i=1;i<=200000;i++)
{
    if(a[i]) continue;
    m-=i;
    if(m<0) break;
    q.push(i);
}
printf("%lld\n",q.size());
int w=q.size(); 
for(int i=1;i<=w;i++)
{
    printf("%lld ",q.front());
    q.pop();
}
```
**核心实现思想**：先标记已有的玩具，然后从小到大枚举玩具编号，若该玩具未拥有且钱足够则购买，直到钱不够为止。

#### MuYC
```cpp
n = read() , M = read();
for(int i = 1 ; i <= n ; i ++)
{
    int x = read();
    if(x <= Max)
        book[x] = 1;
}
for(int i = 1 ; i <= Max ; i ++)
{
    if(book[i]) continue;
    M -= i;
    if(M < 0) break;
    tail ++ , arr[tail] = i;
}
printf("%d\n",tail);
for(int i = 1 ; i <= tail ; i ++)
    printf("%d ",arr[i]);
```
**核心实现思想**：先标记不超过 $2\times10^5$ 的已有玩具，然后在这个范围内从小到大枚举，若玩具未拥有且钱足够则购买，直到钱不够。

#### liuyongle
```cpp
scanf("%d%d",&n,&m);
for (int i=1;i<=n;++i)
    scanf("%d",&a[i]);
sort(a+1,a+1+n);
for(int i=1,j=1;;++i) {
    if(j<=n && i==a[j])
        ++j;
    else if(m<i)
        break;
    else
        m-=i,ans.push_back(i);
}
printf("%d\n",ans.size());
for(int i=0;i<ans.size();++i)
    printf("%d ",ans[i]);
```
**核心实现思想**：先输入已有玩具编号并排序，然后从小到大枚举玩具编号，若该玩具已拥有则跳过，若钱不够则停止，否则购买并存储到 `vector` 中。

### 最优关键思路或技巧
- **贪心策略**：优先选择价格低的玩具，以用有限的钱买到最多的玩具。
- **范围优化**：通过数学推导，将枚举范围从 $10^9$ 缩小到 $2\times10^5$，减少不必要的计算。

### 可拓展之处
同类型题或类似算法套路：在资源有限的情况下，通过贪心策略选择最优解的问题，如活动选择问题、背包问题（部分背包）等。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略每次合并最小的两堆果子，以达到最小的总代价。
- [P2240 【深基12.例1】部分背包问题](https://www.luogu.com.cn/problem/P2240)：根据物品的单位价值进行贪心选择，以获取最大价值。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：按照接水时间从小到大排序，以达到最小的平均等待时间。

---
处理用时：38.61秒