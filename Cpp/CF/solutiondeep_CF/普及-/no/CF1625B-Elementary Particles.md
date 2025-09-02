# 题目信息

# Elementary Particles

## 题目描述

Martians are actively engaged in interplanetary trade. Olymp City, the Martian city known for its spaceport, has become a place where goods from all the corners of our Galaxy come. To deliver even more freight from faraway planets, Martians need fast spaceships.

A group of scientists conducts experiments to build a fast engine for the new spaceship. In the current experiment, there are $ n $ elementary particles, the $ i $ -th of them has type $ a_i $ .

Denote a subsegment of the particle sequence ( $ a_1, a_2, \dots, a_n $ ) as a sequence ( $ a_l, a_{l+1}, \dots, a_r $ ) for some left bound $ l $ and right bound $ r $ ( $ 1 \le l \le r \le n $ ). For instance, the sequence $ (1\ 4\ 2\ 8\ 5\ 7) $ for $ l=2 $ and $ r=4 $ has the sequence $ (4\ 2\ 8) $ as a subsegment. Two subsegments are considered different if at least one bound of those subsegments differs.

Note that the subsegments can be equal as sequences but still considered different. For example, consider the sequence $ (1\ 1\ 1\ 1\ 1) $ and two of its subsegments: one with $ l=1 $ and $ r=3 $ and another with $ l=2 $ and $ r=4 $ . Both subsegments are equal to $ (1\ 1\ 1) $ , but still considered different, as their left and right bounds differ.

The scientists want to conduct a reaction to get two different subsegments of the same length. Denote this length $ k $ . The resulting pair of subsegments must be harmonious, i. e. for some $ i $ ( $ 1 \le i \le k $ ) it must be true that the types of particles on the $ i $ -th position are the same for these two subsegments. For example, the pair $ (1\ 7\ 3) $ and $ (4\ 7\ 8) $ is harmonious, as both subsegments have $ 7 $ on the second position. The pair $ (1\ 2\ 3) $ and $ (3\ 1\ 2) $ is not harmonious.

The longer are harmonious subsegments, the more chances for the scientists to design a fast engine. So, they asked you to calculate the maximal possible length of harmonious pair made of different subsegments.

## 说明/提示

The first test case is shown on the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625B/8f8e2ae794791a59d3657c5398bdb22d42498124.png)As you can see from it, you may choose the subsegments $ (2\ 1\ 3\ 4) $ and $ (3\ 1\ 5\ 2) $ , which are a harmonious pair. Their length is equal to $ 4 $ , so the answer is $ 4 $ .

In the second test case, you need to take two subsegments: one with $ l=1 $ and $ r=5 $ , and one with $ l=2 $ and $ r=6 $ . It's not hard to observe that these segments are a harmonious pair and considered different even though they are both equal to $ (1\ 1\ 1\ 1\ 1) $ .

In the third test case, you cannot make a harmonious pair, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
4
7
3 1 5 2 1 3 4
6
1 1 1 1 1 1
6
1 4 2 8 5 7
2
15 15```

### 输出

```
4
5
-1
1```

# AI分析结果

### 题目内容
# 基本粒子

## 题目描述
火星人积极从事星际贸易。奥林匹斯城，这座以其太空港而闻名的火星城市，已成为来自银河系各个角落货物的汇聚之地。为了从遥远星球运送更多货物，火星人需要快速的宇宙飞船。

一组科学家正在进行实验，为新型宇宙飞船打造一个快速引擎。在当前实验中，有$n$个基本粒子，第$i$个粒子的类型为$a_i$。

将粒子序列（$a_1, a_2, \dots, a_n$）的一个子段定义为序列（$a_l, a_{l + 1}, \dots, a_r$），其中$l$为左边界，$r$为右边界（$1 \leq l \leq r \leq n$）。例如，对于序列$(1\ 4\ 2\ 8\ 5\ 7)$，当$l = 2$，$r = 4$时，其子段为$(4\ 2\ 8)$。如果两个子段的至少一个边界不同，则认为它们是不同的子段。

请注意，即使两个子段作为序列是相等的，但如果边界不同，仍被视为不同子段。例如，对于序列$(1\ 1\ 1\ 1\ 1)$，其中一个子段左边界$l = 1$，右边界$r = 3$，另一个子段左边界$l = 2$，右边界$r = 4$。这两个子段都等于$(1\ 1\ 1)$，但由于它们的左右边界不同，仍被视为不同子段。

科学家们想要进行一个反应，以得到两个长度相同的不同子段。设这个长度为$k$。得到的这对子段必须是和谐的，即对于某个$i$（$1 \leq i \leq k$），这两个子段在第$i$个位置上的粒子类型必须相同。例如，对子段$(1\ 7\ 3)$和$(4\ 7\ 8)$是和谐的，因为这两个子段在第二个位置上都为$7$。而对子段$(1\ 2\ 3)$和$(3\ 1\ 2)$则不是和谐的。

和谐子段越长，科学家们设计出快速引擎的机会就越大。因此，他们请你计算由不同子段组成的和谐对子的最大可能长度。

## 说明/提示
第一个测试用例如下图所示：
![第一个测试用例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625B/8f8e2ae794791a59d3657c5398bdb22d42498124.png)
如你所见，可以选择子段$(2\ 1\ 3\ 4)$和$(3\ 1\ 5\ 2)$，它们是一对和谐子段。它们的长度等于$4$，所以答案是$4$。

在第二个测试用例中，需要取两个子段：一个左边界$l = 1$，右边界$r = 5$，另一个左边界$l = 2$，右边界$r = 6$。不难观察到，这两个子段是一对和谐子段，并且尽管它们都等于$(1\ 1\ 1\ 1\ 1)$，但仍被视为不同子段。

在第三个测试用例中，无法构成和谐对子，所以答案是$-1$。

## 样例 #1
### 输入
```
4
7
3 1 5 2 1 3 4
6
1 1 1 1 1 1
6
1 4 2 8 5 7
2
15 15
```
### 输出
```
4
5
-1
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路较为一致，均基于以下逻辑：要找到两个长度相同且和谐（存在至少一个相同位置元素相等）的不同子段，关键在于找到数组中距离最近的两个相等元素。因为若设两个相等元素位置为$i$和$j$（$i < j$），那么以它们为相同元素构建的子段长度为$i + n - j$，$n$固定，$j - i$越小，子段长度越大。各题解通过记录每个元素出现的位置，在遍历数组过程中计算并更新最大子段长度。

### 所选的题解
 - **作者：EC75 (赞：5)  星级：4星  关键亮点：先对结论进行了详细证明，思路清晰**
    ```python
    def solve():
        n = int(input())
        a = [int(x) for x in input().split()]
        pos = {}
        ans = -1
        for i in range(n):
            if a[i] in pos:
                ans = max(ans, pos[a[i]] + 1 + (n - 1 - i))
            pos[a[i]] = i
        print(ans)
    for _ in range(int(input())):
        solve()
    ```
    **核心实现思想**：利用字典`pos`记录每个元素的位置，遍历数组时，若当前元素已出现过，则计算并更新最大子段长度`ans`。
 - **作者：alm_crax (赞：2)  星级：4星  关键亮点：代码简洁明了，对思路解释清晰**
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n,a,l[150005],ans;
    int main()
    {
        cin>>t;
        while(t--)
        {
            cin>>n;
            memset(l,0,sizeof(l));
            ans=-1;
            for(int i=1;i<=n;i++)
            {
                cin>>a;
                if(l[a])
                {
                    ans=max(ans,i-l[a]+n);
                }
                l[a]=i;
            }
            cout<<ans<<endl;
        }
        return 0;
    }
    ```
    **核心实现思想**：使用数组`l`记录每个元素上次出现的位置，遍历输入数组，若当前元素已出现过，根据公式`i - l[a] + n`更新最大子段长度`ans`。
 - **作者：Disjoint_cat (赞：0)  星级：4星  关键亮点：先给出结论并结合样例直观解释，易于理解**
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    const int N=150005;
    int T,n,a[N],last[N],ans;
    int main()
    {
        scanf("%d",&T);
        while(T--)
        {
            scanf("%d",&n);
            for(int i=1;i<=n;i++)scanf("%d",&a[i]);
            for(int i=1;i<=N;i++)last[i]=0;
            ans=0;
            for(int i=1;i<=n;i++)
            {
                if(last[a[i]]>0)ans=max(ans,n-i+last[a[i]]);
                last[a[i]]=i;
            }
            if(ans==0)printf("-1\n");
            else printf("%d\n",ans);
        }
        return 0;
    }
    ```
    **核心实现思想**：利用数组`last`记录每个元素上次出现的位置，遍历数组，若当前元素已出现过，通过`n - i + last[a[i]]`计算并更新最大子段长度`ans`，最后根据`ans`是否为0输出结果。

### 最优关键思路或技巧
通过记录每个元素出现的位置，在遍历数组过程中快速找到距离最近的相同元素，进而计算出满足条件的最大子段长度。这种利用辅助数组或数据结构记录元素位置信息的方法，简化了对数组中元素关系的查找和处理。

### 同类型题或类似算法套路拓展
此类题目通常围绕数组元素间的关系展开，通过寻找特定关系的元素对（如相等元素对），并基于这些元素对计算某种最优值（如最大子段长度）。类似套路可应用于其他涉及数组子结构查找、最值计算的问题，关键在于分析元素间关系与所求最值的联系，并选择合适的数据结构辅助计算。

### 推荐洛谷题目
 - [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过不同包装铅笔价格和数量关系，计算购买一定数量铅笔的最小花费，涉及对数据关系分析和最值计算。
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：根据每天学习时间和规定时间的关系，找出一周内学习时间超过规定时间最多的天数，同样是基于数据关系的分析和最值查找。
 - [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：给定数列和分段条件，求满足条件下的最小分段最大值，需要分析数列元素关系并通过二分查找最值，与本题思路有一定相似性。 

---
处理用时：62.77秒