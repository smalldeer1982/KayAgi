# 题目信息

# Interesting drink

## 题目描述

Vasiliy likes to rest after a hard work, so you may often meet him in some bar nearby. As all programmers do, he loves the famous drink "Beecola", which can be bought in $ n $ different shops in the city. It's known that the price of one bottle in the shop $ i $ is equal to $ x_{i} $ coins.

Vasiliy plans to buy his favorite drink for $ q $ consecutive days. He knows, that on the $ i $ -th day he will be able to spent $ m_{i} $ coins. Now, for each of the days he want to know in how many different shops he can buy a bottle of "Beecola".

## 说明/提示

On the first day, Vasiliy won't be able to buy a drink in any of the shops.

On the second day, Vasiliy can buy a drink in the shops $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ .

On the third day, Vasiliy can buy a drink only in the shop number $ 1 $ .

Finally, on the last day Vasiliy can buy a drink in any shop.

## 样例 #1

### 输入

```
5
3 10 8 6 11
4
1
10
3
11
```

### 输出

```
0
4
1
5
```

# AI分析结果

### 题目翻译
瓦西里喜欢在辛苦工作后休息，所以你经常能在附近的酒吧见到他。和所有程序员一样，他喜欢著名的饮料“Beecola”，这种饮料在城市里的 $n$ 家不同商店都能买到。已知第 $i$ 家商店里一瓶饮料的价格是 $x_{i}$ 枚硬币。

瓦西里计划连续 $q$ 天购买他最喜欢的饮料。他知道，在第 $i$ 天他最多能花 $m_{i}$ 枚硬币。现在，对于每一天，他都想知道在多少家不同的商店里他可以买到一瓶“Beecola”。

### 算法分类
排序

### 综合分析与结论
- **思路对比**：
    - **CYOI 官方账号**：使用桶排思想，用数组统计每个价格出现的次数，再求前缀和，通过前缀和数组快速查询结果。
    - **一只大龙猫**：先对商铺价格数组和询问数组排序，利用询问数组排序后的单调性，从上一次查询遍历到的地方开始，减少遍历次数。
    - **Toclhu**：先对商铺价格数组排序，然后使用二分查找找到第一个大于询问值的数，进而得到小于等于询问值的数的个数。
    - **Suuon_Kanderu**：先暴力枚举，后优化为排序加 `upper_bound` 函数查找不小于询问值的第一个元素的地址，从而得到结果。
    - **rzh123**：先对商铺价格数组排序，预处理出每个数对应的答案，查询时直接输出结果。
- **算法要点**：大部分题解都先对商铺价格数组进行排序，在此基础上采用不同的方法进行查询。如前缀和、单调性优化、二分查找、`upper_bound` 函数、预处理等。
- **解决难点**：主要解决的难点是如何高效地处理多次询问，避免每次询问都遍历整个数组，从而降低时间复杂度。

### 所选题解
- **CYOI 官方账号（4星）**：
    - **关键亮点**：思路清晰，利用桶排和前缀和的思想，代码实现简单，能快速处理询问。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++) cin>>a[i],t[a[i]]++,Max=mmax(a[i],Max);
for(int i=1;i<=Max;i++) tt[i]=tt[i-1]+t[i];
for(int i=1;i<=m;i++) {
    cin>>lem;
    if (lem<=Max) cout<<tt[lem]<<endl;
    else cout<<tt[Max]<<endl;
}
```
核心实现思想：先统计每个价格出现的次数，再求前缀和，查询时根据询问值在前缀和数组中查找结果。
- **一只大龙猫（4星）**：
    - **关键亮点**：巧妙利用询问数组排序后的单调性，减少遍历次数，优化了暴力算法。
    - **核心代码**：
```cpp
sort(a+1,a+n+1);
sort(q+1,q+m+1,cmp);
for(int i=1;i<=m;i++){
    if(q[i].num>=a[n]){
        ans[q[i].id]=n;
        continue;
    }
    while(q[i].num>=a[now]){
        now++;
    }
    ans[q[i].id]=now-1;
}
```
核心实现思想：对商铺价格数组和询问数组排序，利用询问数组的单调性，从上一次查询的位置开始遍历，找到满足条件的结果。
- **Toclhu（4星）**：
    - **关键亮点**：使用二分查找，时间复杂度低，是一种高效的查询方法。
    - **核心代码**：
```cpp
sort(a+1,a+1+n);
for(int i=1;i<=t;i++){
    cin>>x;
    int l=0,r=n,mid;
    while(l<=r){
        mid=(l+r)/2;
        if(x<a[mid]) r=mid-1;
        else if(x>=a[mid]) l=mid+1;
    }
    cout<<l-1<<endl;
}
```
核心实现思想：对商铺价格数组排序，使用二分查找找到第一个大于询问值的数，输出其下标减一即为结果。

### 最优关键思路或技巧
- 排序是解决此类问题的基础，能为后续的优化提供条件。
- 利用前缀和、单调性、二分查找等方法可以高效地处理多次询问，避免重复计算。

### 可拓展之处
同类型题或类似算法套路：对于多次查询数组中满足某个条件的元素个数的问题，都可以考虑先排序，再结合前缀和、二分查找等方法进行优化。

### 推荐题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得
- **Suuon_Kanderu**：尝试暴力枚举会 TLE，所以需要更先进的办法，如排序加 `upper_bound` 函数优化。总结：对于数据量较大的问题，暴力枚举往往会超时，需要考虑优化算法。 

---
处理用时：32.84秒