# 题目信息

# Building a Fence

## 题目描述

You want to build a fence that will consist of $ n $ equal sections. All sections have a width equal to $ 1 $ and height equal to $ k $ . You will place all sections in one line side by side.

Unfortunately, the ground beneath the fence is not flat. For simplicity, you can think that the ground level under the $ i $ -th section is equal to $ h_i $ .

You should follow several rules to build the fence:

1. the consecutive sections should have a common side of length at least $ 1 $ ;
2. the first and the last sections should stand on the corresponding ground levels;
3. the sections between may be either on the ground level or higher, but not higher than $ k - 1 $ from the ground level $ h_i $ (the height should be an integer);

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1469C/639e8b11cbea2061b5e63469ccc4551e6fb009c3.png)One of possible fences (blue color) for the first test caseIs it possible to build a fence that meets all rules?

## 说明/提示

In the first test case, one of the possible fences is shown in the picture.

In the second test case, according to the second rule, you should build both sections on the corresponding ground levels, and since $ k = 3 $ , $ h_1 = 0 $ , and $ h_2 = 2 $ the first rule is also fulfilled.

In the third test case, according to the second rule, you should build the first section on height $ 3 $ and the third section on height $ 2 $ . According to the first rule, the second section should be on the height of at least $ 2 $ (to have a common side with the first section), but according to the third rule, the second section can be built on the height of at most $ h_2 + k - 1 = 1 $ .

## 样例 #1

### 输入

```
3
6 3
0 0 2 5 1 1
2 3
0 2
3 2
3 0 2```

### 输出

```
YES
YES
NO```

# AI分析结果

### 题目内容重写
# 建造篱笆

## 题目描述

你需要建造一个由 $n$ 个相同部分组成的篱笆。所有部分的宽度均为 $1$，高度均为 $k$。你将所有部分排成一条直线，相邻部分紧挨着。

不幸的是，篱笆下的地面并不平坦。简单来说，第 $i$ 个部分下的地面高度为 $h_i$。

你需要遵循以下规则建造篱笆：

1. 相邻部分必须至少有长度为 $1$ 的公共边；
2. 第一个和最后一个部分必须分别位于对应的地面高度上；
3. 中间部分可以位于地面高度或更高，但不能比地面高度 $h_i$ 高出超过 $k - 1$（高度必须为整数）；

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1469C/639e8b11cbea2061b5e63469ccc4551e6fb009c3.png)  
第一个测试用例中可能的篱笆（蓝色部分）

问：是否有可能建造一个满足所有规则的篱笆？

## 说明/提示

在第一个测试用例中，图中展示了一个可能的篱笆。

在第二个测试用例中，根据规则2，你需要将两个部分分别放在对应的地面高度上，由于 $k = 3$，$h_1 = 0$，$h_2 = 2$，因此规则1也满足。

在第三个测试用例中，根据规则2，你需要将第一个部分放在高度 $3$ 上，第三个部分放在高度 $2$ 上。根据规则1，第二个部分必须至少放在高度 $2$ 上（以与第一个部分有公共边），但根据规则3，第二个部分最多只能放在高度 $h_2 + k - 1 = 1$ 上。

## 样例 #1

### 输入

```
3
6 3
0 0 2 5 1 1
2 3
0 2
3 2
3 0 2
```

### 输出

```
YES
YES
NO
```

### 算法分类
递推

### 题解分析与结论
该题的核心思路是通过递推计算每个篱笆部分的高度范围，并判断是否满足所有规则。具体来说，每个篱笆部分的高度范围受前一个篱笆部分的高度范围和当前地面的高度限制。通过不断更新每个篱笆部分的高度范围，最终判断是否能够满足所有条件。

### 所选高分题解
1. **作者：Mars_Dingdang (赞：5)**
   - **星级：5星**
   - **关键亮点：**
     - 通过区间覆盖的思路，将每个篱笆部分的高度范围抽象为区间，并通过递推计算每个区间的交集。
     - 代码简洁，逻辑清晰，通过逐步更新每个篱笆部分的高度范围来判断是否满足条件。
   - **核心代码：**
     ```cpp
     ll l,r;l=r=h[1];
     bool flag=1;
     rep(i,2,n){
         l=max(h[i],l-k+1);
         r=min(h[i]+k-1,r+k-1);
         if(l>r || l-h[i]>=k){
             puts("NO");
             flag=0;
             break;
         }
     }
     if(!flag) continue;
     if(l==h[n]) puts("YES");
     else puts("NO");
     ```

2. **作者：caoshuchen (赞：2)**
   - **星级：4星**
   - **关键亮点：**
     - 通过递推公式计算每个篱笆部分的高度范围，并判断是否满足条件。
     - 详细解释了递推公式的推导过程，逻辑清晰。
   - **核心代码：**
     ```cpp
     int l = h[1], r = h[1];
     bool f = true;
     for (int i = 2; i <= n; i++) {
         l = max(h[i], l - k + 1);
         r = min(h[i] + k - 1, r + k - 1);
         if (r < l) {
             f = false;
             break;
         }
     }
     if (f && l <= h[n] && h[n] <= r)
         puts("YES");
     else
         puts("NO");
     ```

3. **作者：zjjws (赞：2)**
   - **星级：4星**
   - **关键亮点：**
     - 通过维护每个篱笆部分的高度范围，逐步判断是否满足条件。
     - 代码简洁，逻辑清晰，通过逐步更新高度范围来判断是否满足条件。
   - **核心代码：**
     ```cpp
     LL l,r;
     l=r=h[1];
     bool if_true=true;
     for(int i=2;i<=n;i++){
         LL l_,r_;
         l_=max(h[i],l+1-k);
         r_=min(h[i]+k-1,r-1+k);
         l=l_;r=r_;
         if(l>r||l-h[i]>=k)if_true=false;
     }
     if(if_true&&l==h[n])puts("YES");else puts("NO");
     ```

### 最优关键思路
通过递推计算每个篱笆部分的高度范围，并判断是否满足所有规则。具体来说，每个篱笆部分的高度范围受前一个篱笆部分的高度范围和当前地面的高度限制。通过不断更新每个篱笆部分的高度范围，最终判断是否能够满足所有条件。

### 可拓展之处
该题的思路可以应用于类似的区间覆盖问题，特别是涉及到多个区间之间的相互限制条件的情况。通过递推计算每个区间的交集，可以有效地解决这类问题。

### 推荐题目
1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)
2. [P1044 [NOIP2003 普及组] 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1091 [NOIP2004 提高组] 合唱队形](https://www.luogu.com.cn/problem/P1091)

### 个人心得摘录
- **Mars_Dingdang**：通过区间覆盖的思路，将每个篱笆部分的高度范围抽象为区间，并通过递推计算每个区间的交集，最终判断是否满足条件。
- **caoshuchen**：通过递推公式计算每个篱笆部分的高度范围，并判断是否满足条件，详细解释了递推公式的推导过程。
- **zjjws**：通过维护每个篱笆部分的高度范围，逐步判断是否满足条件，代码简洁，逻辑清晰。

---
处理用时：43.38秒