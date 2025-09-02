# 题目信息

# Create The Teams

## 题目描述

There are $ n $ programmers that you want to split into several non-empty teams. The skill of the $ i $ -th programmer is $ a_i $ . You want to assemble the maximum number of teams from them. There is a restriction for each team: the number of programmers in the team multiplied by the minimum skill among all programmers in the team must be at least $ x $ .

Each programmer should belong to at most one team. Some programmers may be left without a team.

Calculate the maximum number of teams that you can assemble.

## 样例 #1

### 输入

```
3
5 10
7 11 2 9 5
4 8
2 4 2 3
4 11
1 3 3 7```

### 输出

```
2
1
0```

# AI分析结果

### 题目内容
# 创建团队

## 题目描述
有$n$个程序员，你想将他们分成若干个非空团队。第$i$个程序员的技能值为$a_i$。你希望从中组建出最多数量的团队。每个团队有一个限制：团队中的程序员数量乘以团队中所有程序员技能值的最小值必须至少为$x$。

每个程序员最多只能属于一个团队。有些程序员可能会没有团队。

计算你能组建的最大团队数量。

## 样例 #1
### 输入
```
3
5 10
7 11 2 9 5
4 8
2 4 2 3
4 11
1 3 3 7
```
### 输出
```
2
1
0
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路均为贪心算法，要点在于将程序员按技能值从大到小排序，这样能使每组中技能值最小的程序员技能相对较高，更易满足“团队人数×团队最小技能值≥$x$”的条件，从而组建更多团队。在遍历排序后的数组时，通过动态维护当前团队的人数及最小技能值来判断能否组成新团队。各题解在代码实现细节上略有差异，如变量命名、初始化方式等，但整体思路一致。

### 所选的题解
- **作者：Accepted_Error (赞：2)  星级：4星**
    - **关键亮点**：思路阐述清晰，先说明贪心策略，再解释排序原因，代码简洁明了，变量命名有一定可读性。
    - **重点代码核心实现思想**：先对技能值数组从大到小排序，遍历数组过程中，动态更新当前团队的最小技能值和人数，当满足条件时，重置相关变量并增加团队计数。
    ```cpp
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        minn=min(minn,a[i]);
        cnt2++;
        if(minn*cnt2>=x)
        {
            minn=1e9;
            cnt2=0;
            cnt1++;
        }
    }
    ```
- **作者：Yizhixiaoyun (赞：2)  星级：4星**
    - **关键亮点**：简洁地阐述了贪心思路，代码使用`bits/stdc++.h`头文件，较为精简，变量命名直观。
    - **重点代码核心实现思想**：从大到小排序后，逆序遍历数组，以当前技能值和已统计人数判断是否满足条件，满足则增加团队计数并重置人数。
    ```cpp
    sort(a+1,a+n+1);
    int ans=0,cnt=1;
    for(register int i=n;i>=1;--i){
        if(cnt*a[i]>=x){
            ans++;cnt=1;
        }
        else cnt++;
    }
    ```
- **作者：linyihdfj (赞：1)  星级：4星**
    - **关键亮点**：在博客中详细分析了题目，思路清晰，代码注释详细，便于理解。
    - **重点代码核心实现思想**：类似地，先排序，遍历数组时更新当前团队的最小技能值和大小，满足条件时更新团队数量并重置相关变量。
    ```cpp
    sort(a+1,a+n+1,cmp);
    long long now_mn = INF,now_size = 0; 
    for(long long i=1; i<=n; i++){
        now_mn = min(now_mn,a[i]);
        now_size++;
        if(now_mn * now_size >= x){
            now_mn = INF;
            now_size = 0;
            ans++; 
        }
    }
    ```

### 最优关键思路或技巧
将程序员按技能值从大到小排序这一贪心策略是解题关键，能有效利用高技能程序员，使组建团队数量最大化。同时，在代码实现上，简洁高效地维护团队人数和最小技能值的动态变化，以快速判断是否能组成新团队。

### 可拓展之处
此类题目属于贪心策略在分组问题上的应用，相似套路是根据题目条件确定一个排序依据，使后续操作能达到最优解。例如，在资源分配、任务调度等场景中，也可通过类似的贪心思路，依据某个关键指标进行排序，进而完成分配或调度。

### 洛谷相似题目推荐
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：同样是分组问题，通过合理的排序和贪心策略来解决。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间进行排序，运用贪心思想安排顺序以达到最优结果。
- [P1980 计数问题](https://www.luogu.com.cn/problem/P1980)：在一定条件下，通过合理的贪心策略统计满足条件的数量。 

---
处理用时：39.85秒