# 题目信息

# Serval and Toxel's Arrays

## 题目描述

Toxel likes arrays. Before traveling to the Paldea region, Serval gave him an array $ a $ as a gift. This array has $ n $ pairwise distinct elements.

In order to get more arrays, Toxel performed $ m $ operations with the initial array. In the $ i $ -th operation, he modified the $ p_{i} $ -th element of the $ (i-1) $ -th array to $ v_{i} $ , resulting in the $ i $ -th array (the initial array $ a $ is numbered as $ 0 $ ). During modifications, Toxel guaranteed that the elements of each array are still pairwise distinct after each operation.

Finally, Toxel got $ m+1 $ arrays and denoted them as $ A_{0}=a, A_{1},\ldots,A_{m} $ . For each pair $ (i,j) $ ( $ 0\le i<j\le m $ ), Toxel defines its value as the number of distinct elements of the concatenation of $ A_{i} $ and $ A_{j} $ . Now Toxel wonders, what is the sum of the values of all pairs? Please help him to calculate the answer.

## 说明/提示

In the first test case, the arrays change as follows: $ [1,2,3]\to[\underline{4},2,3]\to[4,\underline{5},3] $ .

The concatenation of the $ 0 $ -th array and the $ 1 $ -st array is $[1,2,3,4,\sout{2},\sout{3}]$ . There are $ 4 $ distinct elements.

The concatenation of the $ 0 $ -th array and the $ 2 $ -nd array is $[1,2,3,4,5,\sout{3}] $ . There are $ 5 $ distinct elements.

The concatenation of the $ 1 $ -st array and the $ 2 $ -nd array is $[4,2,3,\sout{4},5,\sout{3}] $ . There are $ 4 $ distinct elements.

Strikethrough elements are duplicates in the array.

Therefore, the answer is $ 4+5+4=13 $ .

In the second test case, note that the array may remain unchanged after operations.

## 样例 #1

### 输入

```
3
3 2
1 2 3
1 4
2 5
1 1
1
1 1
10 10
4 6 9 12 16 20 2 10 19 7
1 3
5 4
2 17
2 18
6 11
7 1
8 17
5 5
5 5
2 2```

### 输出

```
13
1
705```

# AI分析结果

【题目内容中文重写】

# Serval 和 Toxel 的数组

## 题目描述

Toxel 喜欢数组。在前往 Paldea 地区之前，Serval 给了他一个数组 $a$ 作为礼物。这个数组有 $n$ 个互不相同的元素。

为了获得更多的数组，Toxel 对初始数组进行了 $m$ 次操作。在第 $i$ 次操作中，他将第 $(i-1)$ 个数组的第 $p_i$ 个元素修改为 $v_i$，得到第 $i$ 个数组（初始数组 $a$ 编号为 $0$）。在每次修改中，Toxel 保证每个数组的元素在操作后仍然是互不相同的。

最终，Toxel 得到了 $m+1$ 个数组，并将它们记为 $A_0 = a, A_1, \ldots, A_m$。对于每一对 $(i, j)$（$0 \le i < j \le m$），Toxel 定义其值为 $A_i$ 和 $A_j$ 拼接后的不同元素的数量。现在 Toxel 想知道，所有对的值的总和是多少？请帮助他计算答案。

## 说明/提示

在第一个测试用例中，数组的变化如下：$[1,2,3] \to [\underline{4},2,3] \to [4,\underline{5},3]$。

- 第 $0$ 个数组和第 $1$ 个数组的拼接为 $[1,2,3,4,\sout{2},\sout{3}]$，有 $4$ 个不同元素。
- 第 $0$ 个数组和第 $2$ 个数组的拼接为 $[1,2,3,4,5,\sout{3}]$，有 $5$ 个不同元素。
- 第 $1$ 个数组和第 $2$ 个数组的拼接为 $[4,2,3,\sout{4},5,\sout{3}]$，有 $4$ 个不同元素。

因此，答案为 $4 + 5 + 4 = 13$。

在第二个测试用例中，注意操作后数组可能保持不变。

## 样例 #1

### 输入

```
3
3 2
1 2 3
1 4
2 5
1 1
1
1 1
10 10
4 6 9 12 16 20 2 10 19 7
1 3
5 4
2 17
2 18
6 11
7 1
8 17
5 5
5 5
2 2```

### 输出

```
13
1
705```

【算法分类】  
组合数学

【题解分析与结论】  
本题的核心在于计算所有数组对拼接后的不同元素数量的总和。由于每个数组的元素互不相同，我们可以通过统计每个元素在多少个数组中出现过，来计算它对答案的贡献。具体来说，每个元素的贡献可以分为两种情况：
1. 如果两个数组中一个包含该元素，另一个不包含，则贡献为 $1$。
2. 如果两个数组都包含该元素，则贡献也为 $1$。

通过统计每个元素的出现次数，我们可以高效地计算出所有数组对的贡献总和。

【评分较高的题解】

1. **作者：Binary_Lee (赞：21)**  
   - **星级：5**  
   - **关键亮点**：  
     - 通过统计每个元素的出现次数，巧妙地计算了每个元素对答案的贡献。
     - 使用了 $lst_x$ 记录元素最后一次出现的位置，动态更新每个元素的出现次数。
     - 代码简洁且高效，逻辑清晰。
   - **个人心得**：  
     - 作者通过分类讨论，清晰地解释了每个元素的贡献计算方式，避免了复杂的枚举操作。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=m;i++){
         cin>>x>>y;
         if(a[x]!=y){
             cnt[a[x]]+=i-lst[a[x]],lst[a[x]]=-1;
             lst[y]=i,a[x]=y;
         }
     }
     for(int i=1;i<=n+m;i++) if(lst[i]!=-1) cnt[i]+=m-lst[i]+1;
     int ans=0;
     for(int i=1;i<=n+m;i++){
         ans+=cnt[i]*(m+1-cnt[i]);
         ans+=cnt[i]*(cnt[i]-1)/2;
     }
     ```

2. **作者：MspAInt (赞：0)**  
   - **星级：4**  
   - **关键亮点**：  
     - 同样通过统计每个元素的出现次数来计算贡献，思路与 Binary_Lee 类似。
     - 代码实现简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=m;i++){
         int x,y;
         scanf("%d%d",&x,&y);
         if(a[x]==y)continue;
         s[a[x]]+=i-h[a[x]],h[a[x]]=-1;
         h[y]=i,a[x]=y;
     }
     for(int i=1;i<=n+m;i++)if(h[i]!=-1)s[i]+=m-h[i]+1;
     for(int i=1;i<=n+m;i++)ans+=1ll*s[i]*(s[i]-1)/2+1ll*s[i]*(m+1-s[i]);
     ```

【最优关键思路与技巧】  
- **统计元素出现次数**：通过记录每个元素最后一次出现的位置，动态更新其出现次数，避免了复杂的枚举操作。
- **贡献分类计算**：将每个元素的贡献分为两种情况（一个数组包含，另一个不包含；两个数组都包含），简化了计算过程。

【可拓展之处】  
- 类似的问题可以通过统计元素的出现次数来优化计算，尤其是在需要计算多个数组或集合的交集、并集等操作时。
- 可以进一步扩展到多个数组的拼接或合并问题，统计不同元素的数量。

【推荐题目】  
1. [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)  
2. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)  
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

---
处理用时：41.86秒