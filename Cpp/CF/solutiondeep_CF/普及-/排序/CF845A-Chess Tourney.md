# 题目信息

# Chess Tourney

## 题目描述

Berland annual chess tournament is coming!

Organizers have gathered $ 2·n $ chess players who should be divided into two teams with $ n $ people each. The first team is sponsored by BerOil and the second team is sponsored by BerMobile. Obviously, organizers should guarantee the win for the team of BerOil.

Thus, organizers should divide all $ 2·n $ players into two teams with $ n $ people each in such a way that the first team always wins.

Every chess player has its rating $ r_{i} $ . It is known that chess player with the greater rating always wins the player with the lower rating. If their ratings are equal then any of the players can win.

After teams assignment there will come a drawing to form $ n $ pairs of opponents: in each pair there is a player from the first team and a player from the second team. Every chess player should be in exactly one pair. Every pair plays once. The drawing is totally random.

Is it possible to divide all $ 2·n $ players into two teams with $ n $ people each so that the player from the first team in every pair wins regardless of the results of the drawing?

## 样例 #1

### 输入

```
2
1 3 2 4
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1
3 3
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# 国际象棋锦标赛

## 题目描述
伯兰一年一度的国际象棋锦标赛即将来临！

组织者已经召集了 $ 2·n $ 名棋手，他们应该被分成两队，每队 $ n $ 人。第一队由伯油公司（BerOil）赞助，第二队由伯移动公司（BerMobile）赞助。显然，组织者应该确保伯油公司赞助的队伍获胜。

因此，组织者应该将所有 $ 2·n $ 名棋手分成两队，每队 $ n $ 人，使得第一队总是获胜。

每个棋手都有自己的等级分 $ r_{i} $ 。已知等级分较高的棋手总是能战胜等级分较低的棋手。如果他们的等级分相等，那么任何一名棋手都有可能获胜。

在队伍分配完成后，将进行抽签以组成 $ n $ 对对手：每一对中都有一名第一队的棋手和一名第二队的棋手。每名棋手都必须恰好参加一对比赛。每一对进行一场比赛。抽签是完全随机的。

是否有可能将所有 $ 2·n $ 名棋手分成两队，每队 $ n $ 人，使得无论抽签结果如何，每一对中的第一队棋手都能获胜？

## 样例 #1
### 输入
```
2
1 3 2 4
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
1
3 3
```
### 输出
```
NO
```

### 综合分析与结论
- **思路**：所有题解核心思路一致，先对 $ 2n $ 个棋手的等级分排序，再比较排序后第 $ n $ 个和第 $ n + 1 $ 个等级分的大小，若第 $ n $ 个小于第 $ n + 1 $ 个，则可以将棋手分成满足条件的两队，输出 `YES`，否则输出 `NO`。
- **算法要点**：排序算法是关键，题解中均使用了 `sort` 函数进行排序。
- **解决难点**：主要难点在于理解如何通过比较第 $ n $ 个和第 $ n + 1 $ 个等级分来判断是否能分组。因为排序后前 $ n $ 个为一组，后 $ n $ 个为一组，若第 $ n $ 个小于第 $ n + 1 $ 个，那么前一组所有数都小于后一组所有数，满足第一队总是获胜的条件。

### 评分情况
| 作者 | 评分 | 理由 |
| ---- | ---- | ---- |
| ShineEternal | 4星 | 思路清晰，代码简洁，有必要的注释。 |
| Nivi | 3星 | 思路讲解较详细，但使用万能头文件可能影响编译速度，且代码注释较简单。 |
| TLMPEX | 3星 | 思路清晰，但代码注释较少。 |
| Fat_Fish | 3星 | 对不成立情况有思考，但代码中使用了重复的头文件。 |
| 王炸拆开打 | 2星 | 提供了两种判断方法，但第一种判断方法错误，思路不够严谨。 |
| Soshine_溯闪 | 3星 | 思路完整，但使用了较多不必要的头文件。 |
| Contemptuous | 3星 | 思路清晰，有举例说明，但使用了重复的头文件。 |
| Elma_ | 3星 | 思路清晰，但判断条件表述与其他题解相反，易混淆。 |
| hensier | 3星 | 代码简洁，但比较的索引有误。 |
| PC_DOS | 3星 | 使用了动态数组，思路清晰，但代码相对复杂。 |

### 所选题解
- **作者：ShineEternal（4星）**
    - **关键亮点**：代码简洁，思路清晰，有必要的注释。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[210];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a+1,a+2*n+1);
    if(a[n]<a[n+1])
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}
```
核心实现思想：先读入 $ 2n $ 个等级分，再对其进行排序，最后比较第 $ n $ 个和第 $ n + 1 $ 个等级分的大小，根据比较结果输出相应信息。

### 最优关键思路或技巧
- **思维方式**：利用贪心思想，将等级分排序后，通过比较中间两个数的大小来判断是否能分组，避免了复杂的组合枚举。
- **代码实现技巧**：使用 `sort` 函数进行排序，代码简洁高效。

### 可拓展之处
同类型题或类似算法套路：
- 区间分组问题：给定多个区间，要求将其分成若干组，使得每组内的区间不相交。可以先对区间的左端点进行排序，再根据区间的右端点进行分组判断。
- 任务调度问题：有多个任务，每个任务有开始时间和结束时间，要求安排任务的执行顺序，使得在某个时间段内任务不冲突。可以先对任务的开始时间进行排序，再根据任务的结束时间进行调度。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心算法每次合并最小的两堆果子，与本题贪心思想类似。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：对每个人的接水时间进行排序，从而使总的等待时间最短，也是贪心算法的应用。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：根据物品的价值和重量计算单位价值，按单位价值从高到低排序，选择物品装入背包，体现了贪心思想。

### 个人心得摘录与总结
- **Nivi**：第一次提交忘记排序，提醒我们在编写代码时要仔细检查，确保实现了所有必要的步骤。
- **Fat_Fish**：一开始没想到两数相等的情况，经过思考才发现，说明在解题时要全面考虑各种可能的情况，避免遗漏。

---
处理用时：39.86秒