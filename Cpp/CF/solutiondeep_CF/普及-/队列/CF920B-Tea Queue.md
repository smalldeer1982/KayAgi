# 题目信息

# Tea Queue

## 题目描述

Recently $ n $ students from city S moved to city P to attend a programming camp.

They moved there by train. In the evening, all students in the train decided that they want to drink some tea. Of course, no two people can use the same teapot simultaneously, so the students had to form a queue to get their tea.

 $ i $ -th student comes to the end of the queue at the beginning of $ l_{i} $ -th second. If there are multiple students coming to the queue in the same moment, then the student with greater index comes after the student with lesser index. Students in the queue behave as follows: if there is nobody in the queue before the student, then he uses the teapot for exactly one second and leaves the queue with his tea; otherwise the student waits for the people before him to get their tea. If at the beginning of $ r_{i} $ -th second student $ i $ still cannot get his tea (there is someone before him in the queue), then he leaves the queue without getting any tea.

For each student determine the second he will use the teapot and get his tea (if he actually gets it).

## 说明/提示

The example contains $ 2 $ tests:

1. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, and student $ 1 $ gets his tea. Student $ 2 $ gets his tea during $ 2 $ -nd second.
2. During $ 1 $ -st second, students $ 1 $ and $ 2 $ come to the queue, student $ 1 $ gets his tea, and student $ 2 $ leaves without tea. During $ 2 $ -nd second, student $ 3 $ comes and gets his tea.

## 样例 #1

### 输入

```
2
2
1 3
1 4
3
1 5
1 1
2 3
```

### 输出

```
1 2 
1 0 2 
```

# AI分析结果

### 题目翻译
# 茶水队列

## 题目描述
最近，来自S市的 $n$ 名学生搬到了P市参加一个编程训练营。

他们是坐火车去的。晚上，火车上的所有学生都决定要喝点茶。当然，没有两个人可以同时使用同一个茶壶，所以学生们不得不排起队来泡茶。

第 $i$ 个学生在第 $l_{i}$ 秒开始时来到队列末尾。如果有多个学生在同一时刻来到队列，那么索引较大的学生排在索引较小的学生后面。队列中的学生行为如下：如果学生前面没有人，那么他会使用茶壶整整一秒钟，然后带着茶离开队列；否则，学生将等待前面的人泡完茶。如果在第 $r_{i}$ 秒开始时，学生 $i$ 仍然无法泡到茶（队列中他前面还有人），那么他将不泡茶就离开队列。

对于每个学生，确定他使用茶壶并泡到茶的秒数（如果他确实泡到了茶）。

## 说明/提示
示例包含 $2$ 个测试用例：
1. 在第 $1$ 秒，学生 $1$ 和 $2$ 来到队列，学生 $1$ 泡到了茶。学生 $2$ 在第 $2$ 秒泡到了茶。
2. 在第 $1$ 秒，学生 $1$ 和 $2$ 来到队列，学生 $1$ 泡到了茶，学生 $2$ 没泡茶就离开了。在第 $2$ 秒，学生 $3$ 来到并泡到了茶。

## 样例 #1
### 输入
```
2
2
1 3
1 4
3
1 5
1 1
2 3
```
### 输出
```
1 2 
1 0 2 
```

### 题解综合分析与结论
这些题解大多采用模拟的思路解决问题，根据学生到达时间和等待时间的限制，模拟每个学生泡茶的过程。以下是各题解的对比：
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|__LiChangChao__|模拟时间计数器，计算每个人接水时间|用变量 `ans` 记录当前时间，根据学生到达和离开时间判断泡茶情况|处理学生到达、等待和离开的逻辑|4星|
|ryf_loser|枚举时间，判断学生是否能喝到茶|用变量 `c` 记录经过的时间，根据学生到达和等待时间判断|避免将没喝到茶的学生算入总时间|3星|
|Great_Influence|按题意开堆模拟|使用优先队列存储学生，按时间枚举处理学生入队、出队|处理学生离开队列的情况|2星|
|drop|通过 `time` 变化判断是否出队|根据 `time` 和学生到达、离开时间判断泡茶情况|判断 `time` 初始值和出队情况|3星|
|_VEGETABLE_OIer_xlc|用计数器记录时间，模拟泡茶过程|用变量 `c` 记录时间，从最早时间开始模拟|根据题意处理学生泡茶情况|3星|
|御坂御坂|使用STL的list双向链表模拟队列|用 `list` 存储队列，`vector` 记录出队信息|处理学生离开队列的情况|1星|

### 所选题解
- __LiChangChao__（4星）
    - 关键亮点：思路清晰，代码简洁，直接模拟时间计数器，无需排序。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
long long n,t,l[maxn],r[maxn];
int main() {
    scanf("%lld",&t);
    while(t--) {
        scanf("%lld",&n);
        for(int i=1;i<=n;i++)scanf("%lld%lld",&l[i],&r[i]);
        int ans=0;
        for(int i=1; i<=n; i++) {
            if(ans<=l[i]) ans=l[i]+1,printf("%lld ",l[i]);
            else if(r[i]>=ans) printf("%lld ",ans),ans++;
            else printf("0 ");
        }
        printf("\n");
    }
}
```
核心实现思想：使用变量 `ans` 记录当前时间，遍历每个学生，根据学生到达时间和等待时间判断学生是否能泡茶，更新 `ans` 并输出结果。

### 最优关键思路或技巧
使用一个变量记录当前时间，遍历学生时根据学生到达和离开时间判断学生是否能泡茶，避免复杂的数据结构和排序操作，简化代码实现。

### 可拓展之处
同类型题可能会增加更多限制条件，如茶壶数量、泡茶时间不同等，可采用类似的模拟思路，根据具体条件调整判断逻辑。

### 洛谷相似题目推荐
1. P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)：模拟合并过程，使用优先队列优化。
2. P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199)：模拟游戏过程，分析必胜策略。
3. P1223 [排队接水](https://www.luogu.com.cn/problem/P1223)：模拟排队过程，计算等待时间。

### 个人心得摘录与总结
ryf_loser提到“最容易错的地方在于不能把没喝到茶的学生算到总时间中”，总结为在模拟过程中要注意特殊情况的处理，避免逻辑错误。 

---
处理用时：28.61秒