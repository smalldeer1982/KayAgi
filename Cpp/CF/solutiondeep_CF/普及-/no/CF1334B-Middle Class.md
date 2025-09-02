# 题目信息

# Middle Class

## 题目描述

Many years ago Berland was a small country where only $ n $ people lived. Each person had some savings: the $ i $ -th one had $ a_i $ burles.

The government considered a person as wealthy if he had at least $ x $ burles. To increase the number of wealthy people Berland decided to carry out several reforms. Each reform looked like that:

- the government chooses some subset of people (maybe all of them);
- the government takes all savings from the chosen people and redistributes the savings among the chosen people equally.

For example, consider the savings as list $ [5, 1, 2, 1] $ : if the government chose the $ 1 $ -st and the $ 3 $ -rd persons then it, at first, will take all $ 5 + 2 = 7 $ burles and after that will return $ 3.5 $ burles to the chosen people. As a result, the savings will become $ [3.5, 1, 3.5, 1] $ .

A lot of data was lost from that time, so we don't know how many reforms were implemented and to whom. All we can do is ask you to calculate the maximum possible number of wealthy people after several (maybe zero) reforms.

## 说明/提示

The first test case is described in the statement.

In the second test case, the government, for example, could carry out two reforms: $ [\underline{11}, \underline{9}, 11, 9] \rightarrow [10, 10, \underline{11}, \underline{9}] \rightarrow [10, 10, 10, 10] $ .

In the third test case, the government couldn't make even one person wealthy.

In the fourth test case, the government could choose all people to carry out a reform: $ [\underline{9}, \underline{4}, \underline{9}] \rightarrow [7\frac{1}{3}, 7\frac{1}{3}, 7\frac{1}{3}] $ .

## 样例 #1

### 输入

```
4
4 3
5 1 2 1
4 10
11 9 11 9
2 5
4 3
3 7
9 4 9```

### 输出

```
2
4
0
3```

# AI分析结果

### 题目内容
# 中产阶级

## 题目描述
许多年前，Berland 是一个小国，仅生活着 $n$ 个人。每个人都有一定的积蓄：第 $i$ 个人拥有 $a_i$ 卢布。

政府将拥有至少 $x$ 卢布的人视为富人。为了增加富人的数量，Berland 决定实施多项改革。每次改革如下：
- 政府选择一部分人（也可能是所有人）；
- 政府拿走被选中之人的所有积蓄，并在这些人中平均重新分配。

例如，考虑积蓄列表 $[5, 1, 2, 1]$：如果政府选择第 $1$ 个和第 $3$ 个人，首先，它将拿走所有的 $5 + 2 = 7$ 卢布，然后将 $3.5$ 卢布返还给被选中的人。结果，积蓄将变为 $[3.5, 1, 3.5, 1]$。

由于当时许多数据丢失，我们不知道实施了多少次改革以及针对哪些人。我们现在能做的就是请你计算经过若干次（可能为零次）改革后，富人的最大可能数量。

## 说明/提示
第一个测试用例在题目描述中已说明。

在第二个测试用例中，例如，政府可以实施两次改革：$[\underline{11}, \underline{9}, 11, 9] \rightarrow [10, 10, \underline{11}, \underline{9}] \rightarrow [10, 10, 10, 10]$。

在第三个测试用例中，政府甚至无法使一个人成为富人。

在第四个测试用例中，政府可以选择所有人进行改革：$[\underline{9}, \underline{4}, \underline{9}] \rightarrow [7\frac{1}{3}, 7\frac{1}{3}, 7\frac{1}{3}]$。

## 样例 #1
### 输入
```
4
4 3
5 1 2 1
4 10
11 9 11 9
2 5
4 3
3 7
9 4 9
```
### 输出
```
2
4
0
3
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解的核心思路都是基于贪心策略。主要有两种方向：一种是先对数据排序，然后从大到小（或先减去目标值 $x$ 后从小到大）遍历，通过判断当前选择的数的总和与个数的关系（如总和是否大于等于个数乘以 $x$）来确定满足条件的最大数量；另一种是利用优先队列维护数据，每次去掉最小的数，重新计算平均值，直到平均值大于等于 $x$。解决的难点在于理解如何通过贪心选择来使得最终大于等于 $x$ 的数尽可能多，即明白较大数与较小数如何组合能达到最优。

### 所选的题解
- **作者：Warriors_Cat（5星）**
  - **关键亮点**：思路清晰简洁，先将所有数减去 $x$ 后排序，通过判断总和与 $0$ 的关系来确定最终答案，代码实现简洁明了。
  - **重点代码及核心思想**：
```cpp
// 先减去目标值 x 并求和
for(int i = 1; i <= n; ++i){
    scanf("%lld", a + i);
    a[i] -= m;
    sum += a[i]; 
}
sort(a + 1, a + n + 1);
bool flag = 0;
// 遍历排序后的数据，判断总和是否大于等于 0
for(int i = 1; i <= n; ++i){
    if(sum >= 0){
        printf("%lld\n", n - i + 1);
        flag = 1;
        break;
    }
    sum -= a[i];
}
if(!flag) printf("0\n");
```
核心思想是通过减去目标值简化判断过程，排序后根据总和情况确定满足条件的最大数量。
- **作者：lingfunny（4星）**
  - **关键亮点**：详细解释了贪心思路，使用优先队列维护数据，实时更新平均值和所选数的个数，符合在线处理的思维方式，对数据范围的考虑也很周到。
  - **重点代码及核心思想**：
```cpp
while(pj < x &&!q.empty()){
    long long out=q.top();
    sum-=out;--n;
    pj=1.0*sum/n;
    q.pop();
}
cout<<n<<endl;
```
核心思想是利用优先队列每次取出最小数，重新计算总和与平均值，直到平均值大于等于 $x$，此时的 $n$ 即为答案。
- **作者：zjhzs666（4星）**
  - **关键亮点**：从大到小排序后，通过累加较大的数并与个数和 $x$ 的乘积比较，直观地确定满足条件的最大数量，代码简洁易懂。
  - **重点代码及核心思想**：
```cpp
sort(a+1,a+n+1,cmp);
for(i=1;i<=n;i++){
    if(s+a[i]>=x*i)s+=a[i];
    else break;
}
cout<<i-1<<endl;
```
核心思想是排序后从大到小累加，一旦当前累加和小于个数乘以 $x$ 就停止，此时的 $i - 1$ 就是满足条件的最大数量。

### 最优关键思路或技巧
- **贪心策略**：选择较大的数与较小的数组合，使得平均数尽可能满足大于等于 $x$ 的条件。
- **排序**：无论是从大到小还是从小到大排序，都有助于通过遍历数据快速确定满足条件的最大数量。
- **数据结构选择**：优先队列适用于在线处理，能实时更新数据；而直接排序后遍历适用于离线处理，代码相对简洁。

### 可拓展思路
此类题目属于贪心策略在平均数相关问题上的应用。类似的算法套路还可见于其他资源分配、组合优化等场景，在这些场景中，通过合理的贪心选择可以优化结果。同类型题通常围绕如何通过特定操作（如合并、拆分等）来最大化或最小化某个目标值。

### 洛谷推荐题目
- **P1080 [NOIP2012 提高组] 国王游戏**：通过贪心策略解决分配问题，与本题类似，需要考虑如何通过合理排序和选择来优化结果。
- **P1223 排队接水**：同样是贪心思想的应用，通过对数据的合理排序来优化总等待时间，与本题思路类似。
- **P1094 [NOIP2007 普及组] 纪念品分组**：利用贪心策略对数据进行分组，以满足特定条件，与本题在贪心选择上有相似之处。

### 个人心得摘录与总结
无。 

---
处理用时：52.06秒