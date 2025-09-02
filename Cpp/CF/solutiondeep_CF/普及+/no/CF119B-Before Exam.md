# 题目信息

# Before Exam

## 题目描述

Vasya is about to take his first university exam in about several minutes. And it's not just some ordinary exam, it's on mathematical analysis. Of course, right now Vasya can only think of one thing: what the result of his talk with the examiner will be...

To prepare for the exam, one has to study proofs of $ n $ theorems. It is known that there will be $ k $ examination cards on the exam and each card contains ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF119B/a79102df34bfb4ac36a7e7ca20435b44cb7b516b.png) distinct theorems. Besides, no theorem is mentioned in more than one card (that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF119B/eaf3adf2c359f646a89e2e39756bfd54a8c45754.png) theorems won't be mentioned in any card). During the exam several students may get the same card.

We do not know the exact way theorems are distributed by cards, however the students that took the exam before Vasya told him what theorems their cards contained. Vasya evaluates his level of proficiency in the $ i $ -th theorem by some number $ a_{i} $ . The level of proficiency in some card is the average of the levels of proficiency in the theorems that are included in the card. Now Vasya wants to know the minimally and maximally possible levels of his proficiency in the card he gets on the exam. Vasya wants to determine it by the data he has collected from other students. Unfortunately, Vasya has no time left to do the math and he asked you to help him.

## 说明/提示

Let's analyze the first sample. Vasya's proficiency in the cards whose content he already knows equals $ 6 $ and $ 15.5 $ correspondingly. The three theorems that are left are only enough to make one exam card. If we consider all possible variants of theorems included in the card we can see that in the best case scenario Vasya gets the card that contains theorems $ 4 $ and $ 7 $ (his proficiency would equal $ 15.5 $ ) and in the worst case scenario he gets theorems $ 3 $ and $ 5 $ (his proficiency would equal $ 5 $ ).

The $ ⌊\ x⌋ $ operation denotes taking integer part of real number $ x $ (rounding down).

## 样例 #1

### 输入

```
7 3
7 15 0 19 10 5 12
2
1 6
7 4
```

### 输出

```
5.0000000000 15.5000000000```

## 样例 #2

### 输入

```
4 2
10 8 1 17
2
2 3
3 2
```

### 输出

```
4.5000000000 13.5000000000```

# AI分析结果

### 题目内容
# 考试前

## 题目描述
瓦夏（Vasya）几分钟后就要参加他大学的第一场考试了。而且这可不是一场普通的考试，而是数学分析考试。当然，此刻瓦夏只能想到一件事：他与考官交谈的结果会是什么……

为了准备考试，需要学习 $n$ 个定理的证明。已知考试会有 $k$ 张考签，并且每张考签包含 $\lfloor\frac{n}{k}\rfloor$ 个不同的定理。此外，没有一个定理会在超过一张考签中被提及（也就是说，$n - k\lfloor\frac{n}{k}\rfloor$ 个定理不会在任何考签中被提及）。在考试期间，几个学生可能会拿到相同的考签。

我们不知道定理在考签中的具体分布方式，然而在瓦夏之前参加考试的学生告诉了他他们考签上包含哪些定理。瓦夏用数字 $a_{i}$ 来评估自己对第 $i$ 个定理的掌握程度。对某张考签的掌握程度是该考签中所包含定理的掌握程度的平均值。现在瓦夏想通过他从其他学生那里收集到的数据，知道他拿到的考签的掌握程度的最小和最大可能值。不幸的是，瓦夏没有时间做这些数学计算了，所以他请你帮忙。

## 说明/提示
让我们分析第一个样例。瓦夏对他已经知道内容的考签的掌握程度分别为 $6$ 和 $15.5$。剩下的三个定理只够组成一张考签。如果我们考虑考签中包含定理的所有可能变体，我们可以看到，在最好的情况下，瓦夏拿到的考签包含定理 $4$ 和 $7$（他的掌握程度将等于 $15.5$），在最坏的情况下，他拿到定理 $3$ 和 $5$（他的掌握程度将等于 $5$）。

$\lfloor x \rfloor$ 操作表示取实数 $x$ 的整数部分（向下取整）。

## 样例 #1
### 输入
```
7 3
7 15 0 19 10 5 12
2
1 6
7 4
```
### 输出
```
5.0000000000 15.5000000000
```
## 样例 #2
### 输入
```
4 2
10 8 1 17
2
2 3
3 2
```
### 输出
```
4.5000000000 13.5000000000
```

### 算法分类
贪心

### 综合分析与结论
这几道题解思路基本一致，均采用贪心策略。核心思路是分别计算已知考签熟练度的最值，以及用未出现在考签中的定理组成新考签的熟练度最值，再取两者中的最值作为最终答案。算法要点在于统计已出现的定理，将未出现的定理按熟练度排序，根据定理数量判断能否组成新考签，并选取合适数量的定理计算熟练度。解决难点在于理解题意，明确如何通过已有信息确定最小和最大熟练度，以及处理剩余定理能否组成新考签的情况。

### 所选的题解
- **作者：dxy2020（5星）**
  - **关键亮点**：思路清晰，代码简洁明了，详细注释有助于理解。采用自定义读入函数，整体结构完整。
  - **重点代码**：
```cpp
signed main(){
    in (n);in (k);
    m=n/k; 
    for (int i=1;i<=n;++i){//读入a数组 
        in (a[i]);
    }
    int x,sum;
    in (q);
    for (int i=1;i<=q;++i){//已参加考试的q个同学所用试卷的最大和最小熟练程度 
        sum=0;
        for (int j=1;j<=m;++j){
            in (x);
            vis[x]=1;
            sum+=a[x];
        }
        minans=min (minans,sum*1./m);
        maxans=max (maxans,sum*1./m);
    }
    int tot=0;
    for (int i=1;i<=n;++i)
        if (!vis[i]) b[++tot]=a[i]; //未在试卷中出现的定理  
    sort (b+1,b+1+tot);//从小到大排序 
    if (tot>=m&&n-tot<k*m){//剩下的定理还能组卷 
        sum=0;
        for (int i=1;i<=m;++i){
            sum+=b[i];//选最小的m个定理组卷 
        }
        minans=min (minans,	sum*1./m);
        sum=0;
        for (int i=tot;i>tot-m;++i){
            sum+=b[i];//选最大的 m 个定理组卷  
        } 
        maxans=max (maxans,sum*1./m); 
    }
    printf ("%.10lf %.10lf\n",minans,maxans);
    return 0;
}
```
  - **核心实现思想**：先读入数据，统计已知考签的熟练度最值。再找出未出现的定理，排序后根据定理数量判断能否组成新考签，分别计算新考签熟练度的最值，最后输出结果。

- **作者：zsyyyy（4星）**
  - **关键亮点**：对题意解读详细，代码逻辑清晰，使用了常见的数组和布尔数组标记已出现的定理。
  - **重点代码**：
```cpp
signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
    scanf("%lld",&q);
    for(int i=1;i<=q;i++)
    {
        sum=0;
        for(int j=1;j<=(n/k);j++)
        {
            scanf("%lld",&x);
            book[x]=1;
            sum+=a[x];
        }
        minn=min(minn,sum);
        maxx=max(maxx,sum);
    }
    for(int i=1;i<=n;i++)
    {
        if(!book[i])  aa[++cnt]=a[i]; //统计未出现在卡片中的定理
    }
    if(cnt<=(n-k*(n/k))) //无法再组成新的卡片的情况
    {
        ans1=minn/(n/k*1.0);
        ans2=maxx/(n/k*1.0);
        printf("%.10lf %.10lf\n",ans1,ans2);
        return 0;
    }
    sort(aa+1,aa+cnt+1);
    sum=0;
    for(int i=1;i<=(n/k);i++)  sum+=aa[i]; 
    //未出现在卡片中的定理的熟练度最小值
    minn=min(minn,sum);
    sum=0;
    for(int i=cnt;i>=cnt-(n/k)+1;i--)  sum+=aa[i]; 
    //未出现在卡片中的定理的熟练度最大值
    maxx=max(maxx,sum);
    ans1=minn/(n/k*1.0);
    ans2=maxx/(n/k*1.0);
    printf("%.10lf %.10lf\n",ans1,ans2);
    return 0;
}
```
  - **核心实现思想**：读入数据后，遍历已知考签计算熟练度最值，统计未出现的定理。根据未出现定理数量判断能否组成新考签，若能则排序计算新考签熟练度最值并输出。

- **作者：_lxy_（4星）**
  - **关键亮点**：使用 `vector` 和 `bitset` 等容器，代码风格简洁，通过 `map` 对重复考签进行去重处理。
  - **重点代码**：
```cpp
int main()
{
    qread(n,k);int i,j;a.resize(n+1);for(i=1;i<=n;i++) qread(a[i]);qread(q);
    int m=n/k,cnt=0; // cnt表示已配好的卡片数
    for(i=0;i<q;i++) 
    {
        int sum=0;tmp.clear();
        for(j=0;j<m;j++) qread(b[i][j]),vis[b[i][j]]=true,sum+=a[b[i][j]],tmp.push_back(b[i][j]);
        sort(tmp.begin(),tmp.end());if(!mp[tmp]) mp[tmp]=true,cnt++; // 由于前q张可能有重复，所以用map记一下去重
        mx=qmax(mx,sum);mn=qmin(mn,sum);
    }
    for(i=1;i<=n;i++) if(!vis[i]) c.push_back(a[i]); // 剩余的定理的平均数
    int t=0;
    if(c.size()>=m&&k-cnt>0)
    {
        sort(c.begin(),c.end(),greater<int>());for(i=0;i<m;i++) t+=c[i];mx=qmax(mx,t); // 最大值
        t=0;sort(c.begin(),c.end());for(i=0;i<m;i++) t+=c[i];mn=qmin(mn,t); //最小值
    }
    printf("%.10lf %.10lf\n",mn/1.0/m,mx/1.0/m);
    // system("pause");
    return 0;
}
```
  - **核心实现思想**：读入数据后，处理已知考签，用 `map` 去重并计算熟练度最值。统计未出现的定理，根据条件判断能否组成新考签，分别计算新考签熟练度最值后输出。

### 最优关键思路或技巧
采用贪心策略，通过排序未出现定理的熟练度，选取合适数量的定理组成新考签来计算最值。利用布尔数组或 `bitset` 标记已出现的定理，方便统计未出现的定理。部分题解使用 `map` 对重复考签进行去重，使计算更准确。

### 同类型题或类似算法套路拓展
此类题目通常围绕如何通过已有信息，利用贪心策略求最值。类似套路是先分析已知部分的最值情况，再考虑剩余元素通过合理组合对最值的影响，关键在于明确贪心的方向和条件。

### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过贪心策略确定最优排列顺序。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析各种情况，利用贪心思想找到最优策略。
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：通过贪心和其他算法结合解决问题。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：101.03秒