# 题目信息

# Sage's Birthday (hard version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in the easy version all prices $ a_i $ are different. You can make hacks if and only if you solved both versions of the problem.

Today is Sage's birthday, and she will go shopping to buy ice spheres. All $ n $ ice spheres are placed in a row and they are numbered from $ 1 $ to $ n $ from left to right. Each ice sphere has a positive integer price. In this version, some prices can be equal.

An ice sphere is cheap if it costs strictly less than two neighboring ice spheres: the nearest to the left and the nearest to the right. The leftmost and the rightmost ice spheres are not cheap. Sage will choose all cheap ice spheres and then buy only them.

You can visit the shop before Sage and reorder the ice spheres as you wish. Find out the maximum number of ice spheres that Sage can buy, and show how the ice spheres should be reordered.

## 说明/提示

In the sample it's not possible to place the ice spheres in any order so that Sage would buy $ 4 $ of them. If the spheres are placed in the order $ (3, 1, 4, 2, 4, 2, 5) $ , then Sage will buy one sphere for $ 1 $ and two spheres for $ 2 $ each.

## 样例 #1

### 输入

```
7
1 3 2 2 4 5 4```

### 输出

```
3
3 1 4 2 4 2 5```

# AI分析结果

### 题目内容（中文重写）
# Sage 的生日（困难版本）

## 题目描述
这是该问题的困难版本。与简单版本的区别在于，在简单版本中所有价格 $a_i$ 都不同。只有当你同时解决了两个版本的问题时，才可以进行 Hack 操作。

今天是 Sage 的生日，她要去购物买冰球。所有 $n$ 个冰球排成一排，从左到右编号为 $1$ 到 $n$。每个冰球都有一个正整数价格。在这个版本中，有些价格可能相等。

如果一个冰球的价格严格低于它相邻的两个冰球（左边最近的和右边最近的），则称这个冰球是便宜的。最左边和最右边的冰球不被视为便宜的。Sage 会选择所有便宜的冰球，然后只购买它们。

你可以在 Sage 之前去商店，并按照你希望的方式重新排列冰球。找出 Sage 最多可以购买的冰球数量，并展示应该如何重新排列冰球。

## 说明/提示
在样例中，不可能以任何顺序放置冰球，使得 Sage 能购买 4 个冰球。如果冰球按顺序 $(3, 1, 4, 2, 4, 2, 5)$ 放置，那么 Sage 将购买一个价格为 1 的冰球和两个价格为 2 的冰球。

## 样例 #1
### 输入
```
7
1 3 2 2 4 5 4
```
### 输出
```
3
3 1 4 2 4 2 5
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路大多是通过合理的构造来最大化满足条件（价格严格小于左右相邻冰球）的冰球数量。大部分题解先对冰球价格进行排序，然后采用奇数位放大数、偶数位放小数的策略进行排列，最后遍历排列后的序列统计满足条件的冰球个数。

不同题解的差异主要在于具体的实现细节，如使用的数据结构和处理边界情况的方式。例如，“7KByte” 的题解使用了 `multiset` 来进行更复杂的贪心构造，而其他大部分题解则直接通过数组下标操作完成构造。

### 所选题解
- **素质玩家孙1超（5星）**
    - **关键亮点**：代码简洁，将所有操作集中在主函数中，思路清晰，直接按照奇数位放大数、偶数位放小数的策略实现，易于理解。
- **0xFF（4星）**
    - **关键亮点**：对题目分析详细，先明确答案上限，再阐述构造方法，最后进行答案统计，逻辑严谨。
- **MVP_Harry（4星）**
    - **关键亮点**：代码中使用了模板函数 `read` 和 `write` 进行输入输出优化，且思路清晰，按照贪心策略进行构造和答案统计。

### 重点代码及核心实现思想
#### 素质玩家孙1超
```cpp
n=R();
for(int i=1;i<=n;i++) a[i]=R();
sort(a+1,a+1+n);
int p1=1,p2=n/2+1,num=0;
for(int i=1;i<=n;i++)ans[i]=i%2?a[p2++]:a[p1++];
for(int i=1;i<=n;i++)num+=(ans[i]<ans[i-1]&&ans[i]<ans[i+1]);
printf("%d\n",num);
for(int i=1;i<=n;i++)printf("%d ",ans[i]);
```
**核心实现思想**：先读取输入并排序，然后将排序后的数组前半部分依次放入偶数位，后半部分依次放入奇数位，最后遍历排列后的数组统计满足条件的冰球个数。

#### 0xFF
```cpp
n = read();
for(int i=1;i<=n;i++){
    a[i] = read();
}
sort(a+1,a+n+1);
int pos1 = 1,pos2 = n/2+1;
int num = 0;
for(int i=1;i<=n;i++){
    if(i % 2 == 0){
        ans[i] = a[pos1++];
    }
    else ans[i] = a[pos2++];
}
for(int i=1;i<=n;i++){
    if(ans[i] < ans[i-1] && ans[i] < ans[i+1])
        num++;
}
printf("%lld\n",num);
for(int i=1;i<=n;i++){
    printf("%lld ",ans[i]);
}
```
**核心实现思想**：同样先读取输入并排序，然后将小的数依次放入偶数位，大的数依次放入奇数位，最后统计满足条件的冰球个数。

#### MVP_Harry
```cpp
read(N);
rep(i, 1, N) read(b[i]);
sort(b + 1, b + N + 1);
int cnt = 0; 
for (int i = 2; i <= N; i += 2) {
    c[i] = b[i / 2];
    ++cnt;  
}
for (int i = 1; i <= N; i += 2) {
    c[i] = b[++cnt]; 
}
int ans = 0; 
for (int i = 2; i <= N - 1; i++) {
    if (c[i] < c[i - 1] && c[i] < c[i + 1]) ++ans; 
}
cout << ans << endl; 
for (int i = 1; i <= N; i++) cout << c[i] << " ";
```
**核心实现思想**：读取输入并排序后，将小的数依次放入偶数位，大的数依次放入奇数位，最后统计满足条件的冰球个数，同时使用模板函数进行输入输出优化。

### 最优关键思路或技巧
- **排序**：先对冰球价格进行排序，为后续的构造提供基础。
- **奇偶位放置**：将排序后的数组前半部分放在偶数位，后半部分放在奇数位，能有效构造出满足条件的排列。
- **遍历统计**：最后遍历排列后的数组，统计满足价格严格小于左右相邻冰球的冰球个数。

### 可拓展之处
同类型题可能会有不同的条件限制，如相邻元素的关系可能变为大于、小于等于等，或者元素的属性更多。类似的算法套路可以应用于其他构造类问题，通过合理的排序和位置分配来达到最优解。

### 推荐洛谷题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 个人心得摘录与总结
- **7KByte**：比赛时和前几篇题解思路一样，然后交了一发 `WA` 了，然后直接上平衡树。总结：即使思路看似正确，也可能因为细节问题导致错误，需要进一步优化和调试。

---
处理用时：45.17秒