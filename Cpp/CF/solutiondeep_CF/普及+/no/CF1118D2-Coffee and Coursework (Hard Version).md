# 题目信息

# Coffee and Coursework (Hard Version)

## 题目描述

The only difference between easy and hard versions is the constraints.

Polycarp has to write a coursework. The coursework consists of $ m $ pages.

Polycarp also has $ n $ cups of coffee. The coffee in the $ i $ -th cup Polycarp has $ a_i $ caffeine in it. Polycarp can drink some cups of coffee (each one no more than once). He can drink cups in any order. Polycarp drinks each cup instantly and completely (i.e. he cannot split any cup into several days).

Surely, courseworks are not being written in a single day (in a perfect world of Berland, at least).

Let's consider some day of Polycarp's work. Consider Polycarp drinks $ k $ cups of coffee during this day and caffeine dosages of cups Polycarp drink during this day are $ a_{i_1}, a_{i_2}, \dots, a_{i_k} $ . Then the first cup he drinks gives him energy to write $ a_{i_1} $ pages of coursework, the second cup gives him energy to write $ max(0, a_{i_2} - 1) $ pages, the third cup gives him energy to write $ max(0, a_{i_3} - 2) $ pages, ..., the $ k $ -th cup gives him energy to write $ max(0, a_{i_k} - k + 1) $ pages.

If Polycarp doesn't drink coffee during some day, he cannot write coursework at all that day.

Polycarp has to finish his coursework as soon as possible (spend the minimum number of days to do it). Your task is to find out this number of days or say that it is impossible.

## 说明/提示

In the first example Polycarp can drink fourth cup during first day (and write $ 1 $ page), first and second cups during second day (and write $ 2 + (3 - 1) = 4 $ pages), fifth cup during the third day (and write $ 2 $ pages) and third cup during the fourth day (and write $ 1 $ page) so the answer is $ 4 $ . It is obvious that there is no way to write the coursework in three or less days.

In the second example Polycarp can drink third, fourth and second cups during first day (and write $ 4 + (2 - 1) + (3 - 2) = 6 $ pages) and sixth cup during second day (and write $ 4 $ pages) so the answer is $ 2 $ . It is obvious that Polycarp cannot write the whole coursework in one day in this test.

In the third example Polycarp can drink all cups of coffee during first day and write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) + (5 - 4) = 15 $ pages of coursework.

In the fourth example Polycarp cannot drink all cups during first day and should drink one of them during the second day. So during first day he will write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) = 14 $ pages of coursework and during second day he will write $ 5 $ pages of coursework. This is enough to complete it.

In the fifth example Polycarp cannot write the whole coursework at all, even if he will drink one cup of coffee during each day, so the answer is -1.

## 样例 #1

### 输入

```
5 8
2 3 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 10
1 3 4 2 1 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 15
5 5 5 5 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5 16
5 5 5 5 5
```

### 输出

```
2
```

## 样例 #5

### 输入

```
5 26
5 5 5 5 5
```

### 输出

```
-1
```

# AI分析结果

### 题目内容翻译
# 咖啡与课程作业（困难版本）

## 题目描述
简单版本和困难版本的唯一区别在于数据范围。

波利卡普需要写一篇课程作业。该课程作业共有 $m$ 页。

波利卡普还有 $n$ 杯咖啡。他拥有的第 $i$ 杯咖啡中含有 $a_i$ 单位的咖啡因。波利卡普可以喝若干杯咖啡（每杯咖啡最多喝一次），且喝咖啡的顺序可以任意选择。波利卡普会立即且完全地喝完每一杯咖啡（即他不能将任何一杯咖啡分成几天来喝）。

当然，在完美的伯兰世界里，课程作业显然不是在一天内完成的。

让我们来考虑波利卡普工作的某一天。假设波利卡普在这一天喝了 $k$ 杯咖啡，且他在这一天喝的咖啡的咖啡因含量分别为 $a_{i_1}, a_{i_2}, \dots, a_{i_k}$。那么，他喝的第一杯咖啡能让他完成 $a_{i_1}$ 页的课程作业，第二杯咖啡能让他完成 $\max(0, a_{i_2} - 1)$ 页，第三杯咖啡能让他完成 $\max(0, a_{i_3} - 2)$ 页，以此类推，第 $k$ 杯咖啡能让他完成 $\max(0, a_{i_k} - k + 1)$ 页。

如果波利卡普在某一天没有喝咖啡，那么他在这一天就完全无法写课程作业。

波利卡普需要尽快完成他的课程作业（即花费最少的天数来完成）。你的任务是找出完成作业所需的最少天数，或者判断这是不可能完成的。

## 说明/提示
在第一个样例中，波利卡普可以在第一天喝第四杯咖啡（完成 $1$ 页作业），在第二天喝第一杯和第二杯咖啡（完成 $2 + (3 - 1) = 4$ 页作业），在第三天喝第五杯咖啡（完成 $2$ 页作业），在第四天喝第三杯咖啡（完成 $1$ 页作业），因此答案是 $4$。显然，没有办法在三天或更少的天数内完成课程作业。

在第二个样例中，波利卡普可以在第一天喝第三杯、第四杯和第二杯咖啡（完成 $4 + (2 - 1) + (3 - 2) = 6$ 页作业），在第二天喝第六杯咖啡（完成 $4$ 页作业），因此答案是 $2$。显然，在这个样例中，波利卡普不可能在一天内完成整个课程作业。

在第三个样例中，波利卡普可以在第一天喝完所有的咖啡，完成 $5 + (5 - 1) + (5 - 2) + (5 - 3) + (5 - 4) = 15$ 页的课程作业。

在第四个样例中，波利卡普无法在第一天喝完所有的咖啡，因此他需要在第二天喝其中一杯。所以，他在第一天将完成 $5 + (5 - 1) + (5 - 2) + (5 - 3) = 14$ 页的课程作业，在第二天将完成 $5$ 页的课程作业，这样就足够完成作业了。

在第五个样例中，即使波利卡普每天喝一杯咖啡，他也无法完成整个课程作业，因此答案是 $-1$。

## 样例 #1
### 输入
```
5 8
2 3 1 1 2
```
### 输出
```
4
```

## 样例 #2
### 输入
```
7 10
1 3 4 2 1 4 2
```
### 输出
```
2
```

## 样例 #3
### 输入
```
5 15
5 5 5 5 5
```
### 输出
```
1
```

## 样例 #4
### 输入
```
5 16
5 5 5 5 5
```
### 输出
```
2
```

## 样例 #5
### 输入
```
5 26
5 5 5 5 5
```
### 输出
```
-1
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路基本一致，都是先对咖啡的咖啡因含量数组进行降序排序，利用贪心思想，优先喝咖啡因含量大的咖啡，再通过二分答案来确定最少的天数。在二分过程中，对于每个中间值（天数），通过检查在该天数下能否完成作业来调整二分的左右边界。

各题解的算法要点主要包括：排序保证贪心策略的正确性，二分查找提高查找效率，检查函数计算在给定天数下能完成的作业量。

解决的难点在于如何合理地安排每天喝咖啡的顺序以达到最大的作业完成量，以及如何高效地判断在给定天数下能否完成作业。

### 题解评分与选择
- **LinuF（赞：3）**：4星。思路清晰，代码简洁，对二分和贪心的结合解释明确。
- **櫻尘ིོི༹（赞：1）**：4星。详细地阐述了思路和过程，代码逻辑清晰。
- **zhouzihang1（赞：0）**：4星。先给出简单的 $O(n^2)$ 做法，再优化到二分，有助于理解。

### 重点代码与核心实现思想
#### LinuF 的代码
```cpp
int check(int x){
    int cnt=0,ans=0,times=0;
    while(true){
        for(int i=1;i<=x;i++){
            ans+=max((int)0,a[++cnt]-times);
        }
        times++;
        if(cnt>=n) break;
    }
    return ans>=m;
}
void solve(){
    int l=1,r=n;
    while(l<r){
        int mid=l+r>>1;
        if(check(mid)){
            r=mid;
        }
        else l=mid+1;
    }
    if(!check(l)) cout<<-1<<endl;
    else cout<<l<<endl;
}
```
核心实现思想：`check` 函数模拟在 $x$ 天内喝咖啡完成作业的过程，计算能完成的作业量。`solve` 函数通过二分查找最小的满足条件的天数。

#### 櫻尘ིོི༹ 的代码
```cpp
inline bool check(int x){
    int num=1,num1=0;
    int nsum=sum;
    while(num<=n){
        if(num+x-1<=n){
            if(s[num+x-1]>=num1){
                nsum-=num1*x;
                num+=x;
                num1++;
            }else{
                int i;
                for(i=num;i<=num+x-1;i++){
                    if(s[i]>num1)nsum-=num1;
                    else break;
                }
                for(;i<=n;i++)nsum-=s[i];
                break;
            }
        }else{
            if(s[n]>=num1){
                nsum-=(n-num+1)*num1;
                num=n;
            }else{
                int i;
                for(i=num;i<=n;i++){
                    if(s[i]>num1)nsum-=num1;
                    else break;
                }
                for(;i<=n;i++)nsum-=s[i];
            }
            break;
        }
    }
    if(nsum>=m)return true;
    return false;
}
```
核心实现思想：`check` 函数通过模拟每天喝咖啡的过程，根据咖啡的咖啡因含量和天数计算剩余的作业量，判断是否能完成作业。

#### zhouzihang1 的代码
```cpp
bool check(int k)
{
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=max(0,a[i]-(i-1)/k);
        if(sum>=m) return 1;
    }
    return 0;
}
```
核心实现思想：`check` 函数计算在 $k$ 天内喝咖啡能完成的作业量，判断是否能达到作业要求。

### 最优关键思路或技巧
- 贪心策略：将咖啡的咖啡因含量从大到小排序，优先喝咖啡因含量大的咖啡，以最大化每天完成的作业量。
- 二分查找：利用答案的单调性，通过二分查找最小的满足条件的天数，将时间复杂度从 $O(n^2)$ 优化到 $O(n\log n)$。

### 拓展思路
同类型题或类似算法套路：在一些需要求最小值且答案具有单调性的问题中，可以考虑使用二分查找来优化时间复杂度。例如，在一些资源分配问题中，通过二分查找最小的资源分配量，再通过检查函数判断该分配量是否满足条件。

### 推荐题目
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分查找最短跳跃距离，再检查该距离是否能满足条件。
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)：二分查找最大分段和，检查该和是否能将数列分成指定的段数。
- [P3853 [TJOI2007] 路标设置](https://www.luogu.com.cn/problem/P3853)：二分查找最大的相邻路标距离，检查该距离是否能在给定的新增路标数量下满足条件。

### 个人心得摘录与总结
题解中未包含个人心得内容。

---
处理用时：62.66秒