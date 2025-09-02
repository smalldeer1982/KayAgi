# 题目信息

# Tea Tasting

## 题目描述

A tea manufacturer decided to conduct a massive tea tasting. $ n $ sorts of tea will be tasted by $ n $ tasters. Both the sorts of tea and the tasters are numbered from $ 1 $ to $ n $ . The manufacturer prepared $ a_i $ milliliters of the $ i $ -th sort of tea. The $ j $ -th taster can drink $ b_j $ milliliters of tea at once.

The tasting will be conducted in steps. During the first step, the $ i $ -th taster tastes the $ i $ -th sort of tea. The $ i $ -th taster drinks $ \min(a_i, b_i) $ tea (how much is available of the $ i $ -th sort and how much the $ i $ -th taster can drink). $ a_i $ also decreases by this amount.

Then all tasters move to the previous sort of tea. Thus, during the second step, the $ i $ -th taster tastes the $ (i-1) $ -st sort of tea. The $ i $ -th taster drinks $ \min(a_{i-1}, b_i) $ tea. The $ 1 $ -st person ends the tasting.

During the third step, the $ i $ -th taster tastes the $ (i-2) $ -nd sort of tea. The $ 2 $ -nd taster ends the tasting. This goes on until everyone ends the tasting.

Take a look at the tasting process for $ n = 3 $ , $ a = [10, 20, 15] $ , $ b = [9, 8, 6] $ . In the left row, there are the current amounts of each sort of tea. In the right column, there are current amounts of tea each taster has drunk in total. The arrow tells which taster each tea goes to on the current step. The number on the arrow is the amount — minimum of how much is available of the sort of tea and how much the taster can drink.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795C/470487c0e21724392d7014bece095c7efdff8422.png)For each taster, print how many milliliters of tea he/she will drink in total.

## 说明/提示

The first testcase is described in the statement. Here are the remaining amounts of each sort of tea after each step and the total amount of tea each taster has drunk:

- $ a = [1, 12, 9] $ , $ \mathit{ans} = [9, 8, 6] $
- $ a = [0, 6, 9] $ , $ \mathit{ans} = [9, 9, 12] $
- $ a = [0, 6, 9] $ , $ \mathit{ans} = [9, 9, 12] $

In the second testcase, the only taster drinks $ \min(5, 7) $ milliliters of tea of the only sort.

Here are the remaining amounts of each sort of tea after each step and the total amount of tea each taster has drunk for the third testcase:

- $ a = [10, 4, 3, 3] $ , $ \mathit{ans} = [3, 4, 2, 1] $ ;
- $ a = [6, 2, 2, 3] $ , $ \mathit{ans} = [3, 8, 4, 2] $ ;
- $ a = [4, 1, 2, 3] $ , $ \mathit{ans} = [3, 8, 6, 3] $ ;
- $ a = [3, 1, 2, 3] $ , $ \mathit{ans} = [3, 8, 6, 4] $ .

Here are the remaining amounts of each sort of tea after each step and the total amount of tea each taster has drunk for the fourth testcase:

- $ a = [999999999, 999999999, 0] $ , $ \mathit{ans} = [1, 1, 1000000000] $ ;
- $ a = [999999998, 0, 0] $ , $ \mathit{ans} = [1, 2, 1999999999] $ ;
- $ a = [0, 0, 0] $ , $ \mathit{ans} = [1, 2, 2999999997] $ .

## 样例 #1

### 输入

```
4
3
10 20 15
9 8 6
1
5
7
4
13 8 5 4
3 4 2 1
3
1000000000 1000000000 1000000000
1 1 1000000000```

### 输出

```
9 9 12 
5 
3 8 6 4 
1 2 2999999997```

# AI分析结果

### 题目内容重写

#### 题目描述

一个茶叶制造商决定进行一次大规模的茶叶品尝活动。共有 $n$ 种茶叶和 $n$ 名品茶师，茶叶和品茶师都从 $1$ 到 $n$ 编号。制造商准备了 $a_i$ 毫升的第 $i$ 种茶叶。第 $j$ 名品茶师一次可以喝 $b_j$ 毫升的茶。

品尝活动将分步骤进行。在第一步中，第 $i$ 名品茶师品尝第 $i$ 种茶叶。第 $i$ 名品茶师喝掉 $\min(a_i, b_i)$ 毫升的茶（即第 $i$ 种茶叶的剩余量和第 $i$ 名品茶师能喝的量中的较小值）。$a_i$ 也会相应减少这个量。

然后，所有品茶师向前移动一位，品尝前一种茶叶。因此，在第二步中，第 $i$ 名品茶师品尝第 $(i-1)$ 种茶叶。第 $i$ 名品茶师喝掉 $\min(a_{i-1}, b_i)$ 毫升的茶。第 $1$ 名品茶师结束品尝。

在第三步中，第 $i$ 名品茶师品尝第 $(i-2)$ 种茶叶。第 $2$ 名品茶师结束品尝。这个过程一直持续，直到所有品茶师都结束品尝。

例如，当 $n = 3$，$a = [10, 20, 15]$，$b = [9, 8, 6]$ 时，品尝过程如下：

- 第一步：$a = [1, 20, 15]$，$\mathit{ans} = [9, 8, 6]$
- 第二步：$a = [0, 12, 15]$，$\mathit{ans} = [9, 9, 12]$
- 第三步：$a = [0, 6, 15]$，$\mathit{ans} = [9, 9, 12]$

对于每名品茶师，输出他/她总共喝了多少毫升的茶。

### 算法分类
差分、二分、前缀和

### 题解分析与结论

#### 题解1：ztlh (赞：7)
- **星级**：5星
- **关键亮点**：使用前缀和和二分查找来优化时间复杂度，通过差分数组记录完整贡献的次数，最后计算每个品茶师的总饮茶量。
- **代码核心思想**：
  - 计算 $b_i$ 的前缀和 $s_i$。
  - 对于每杯茶，二分查找其贡献终止的位置 $j$，并更新差分数组 $cnt$ 和 $ex$。
  - 最后通过差分数组计算每个品茶师的总饮茶量。

```cpp
for(int i=1,l,r,mid;i<=n;i++){
    if(s[n]-s[i-1]<=a[i]){
        cnt[i]++;
        continue;
    }
    l=i; r=n;
    while(l<r){
        mid=l+r>>1;
        if(s[mid]-s[i-1]<=a[i]) l=mid+1;
        else r=mid;
    }
    l--;
    cnt[i]++; cnt[l+1]--;
    ex[l+1]+=a[i]-(s[l]-s[i-1]);
}
for(int i=1;i<=n;i++){
    cnt[i]+=cnt[i-1];
    printf("%lld ",cnt[i]*b[i]+ex[i]);
}
```

#### 题解2：daiarineko (赞：5)
- **星级**：4星
- **关键亮点**：利用前缀和和二分查找优化查询，使用树状数组维护差分数组，最后计算每个品茶师的总饮茶量。
- **代码核心思想**：
  - 计算 $b_i$ 的前缀和 $s_i$。
  - 对于每杯茶，二分查找其贡献终止的位置 $j$，并更新树状数组和 $ex$。
  - 最后通过树状数组计算每个品茶师的总饮茶量。

```cpp
for(int i=1;i<=n;i++){
    int k = lower_bound(s + 1, s + 1 + n, s[i - 1] + a[i]) - s;
    int x = a[i] + s[i - 1] - s[k - 1];
    update(i, 1);
    if (k <= n) {
        update(k, -1);
        ex[k] += x;
    }
}
for(int i=1;i<=n;i++){
    cout << b[i] * query(i) + ex[i] << ' ';
}
```

#### 题解3：ダ月 (赞：3)
- **星级**：4星
- **关键亮点**：使用前缀和和二分查找优化查询，通过差分数组记录完整贡献的次数，最后计算每个品茶师的总饮茶量。
- **代码核心思想**：
  - 计算 $b_i$ 的前缀和 $s_i$。
  - 对于每杯茶，二分查找其贡献终止的位置 $j$，并更新差分数组 $b$ 和 $ans$。
  - 最后通过差分数组计算每个品茶师的总饮茶量。

```cpp
for(int i=1;i<=n;i++){
    int pos=lower_bound(s+i,s+n+1,a[i]+s[i-1])-s;
    b[pos]--;b[i]++;ans[pos]+=a[i]-(s[pos-1]-s[i-1]);
}
for(int i=1;i<=n;i++) b[i]+=b[i-1];
for(int i=1;i<=n;i++)
    printf("%lld ",ans[i]+b[i]*k[i]);
```

### 最优关键思路与技巧
1. **前缀和与二分查找**：通过计算 $b_i$ 的前缀和，可以快速查询每杯茶的贡献终止位置，从而优化时间复杂度。
2. **差分数组**：使用差分数组记录完整贡献的次数，避免了对每个品茶师进行单独更新，进一步优化了时间复杂度。
3. **树状数组**：在某些题解中，使用树状数组维护差分数组，提供了更高效的数据结构支持。

### 可拓展之处
- 类似的问题可以通过前缀和和二分查找来优化查询，例如区间求和、区间更新等问题。
- 差分数组和树状数组在处理区间更新和单点查询时非常有用，可以应用于其他需要高效处理区间操作的问题。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)
3. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得总结
- **调试经历**：在处理差分数组时，需要注意边界条件的处理，例如当茶的总量不足以支持所有品茶师时，需要特别处理。
- **踩坑教训**：在二分查找时，确保查找的范围和条件正确，避免出现死循环或错误的结果。
- **顿悟感想**：通过前缀和和差分数组的结合，可以高效地处理区间更新和查询问题，大大优化了时间复杂度。

---
处理用时：47.18秒