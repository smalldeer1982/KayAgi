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

他们乘火车前往那里。晚上，火车上的所有学生都决定要喝点茶。当然，没有两个人可以同时使用同一个茶壶，所以学生们不得不排队去取茶。

第 $i$ 个学生在第 $l_{i}$ 秒开始时来到队列末尾。如果有多个学生在同一时刻来到队列，那么索引较大的学生排在索引较小的学生后面。队列中的学生行为如下：如果学生前面没有人，那么他会使用茶壶正好一秒钟，然后带着茶离开队列；否则，学生将等待前面的人取到茶。如果在第 $r_{i}$ 秒开始时，学生 $i$ 仍然无法取到茶（队列中有其他人在他前面），那么他将不拿茶就离开队列。

对于每个学生，确定他使用茶壶并取到茶的秒数（如果他确实取到了茶）。

## 说明/提示
示例包含 $2$ 个测试用例：
1. 在第 $1$ 秒，学生 $1$ 和 $2$ 来到队列，学生 $1$ 取到了茶。学生 $2$ 在第 $2$ 秒取到了茶。
2. 在第 $1$ 秒，学生 $1$ 和 $2$ 来到队列，学生 $1$ 取到了茶，学生 $2$ 没取到茶就离开了。在第 $2$ 秒，学生 $3$ 来到并取到了茶。

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

### 综合分析与结论
- **思路对比**：大部分题解采用模拟时间的方式，通过一个变量记录当前时间，根据学生到达时间 $l_i$ 和离开时间 $r_i$ 判断学生是否能取到茶。Great_Influence 的题解使用优先队列模拟，御坂御坂的题解使用双向链表模拟。
- **算法要点**：
    - 普通模拟：用一个变量记录当前时间，根据学生的 $l_i$ 和 $r_i$ 以及当前时间判断学生是否能取到茶。
    - 优先队列模拟：将学生按到达时间排序，使用优先队列存储当前队列中的学生，按时间顺序处理。
    - 双向链表模拟：使用双向链表存储队列，用一个数组记录每个时间点要离开的学生。
- **解决难点**：
    - 处理学生离开队列的情况，避免将离开的学生算入总时间。
    - 处理多个学生同时到达的情况。

### 所选题解
- **__LiChangChao__（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接模拟时间计数器，利用题目中 $l_{i - 1} \leq l_i$ 的条件，无需排序。
    - **核心代码**：
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
核心思想：用 `ans` 记录当前时间，遍历每个学生，根据当前时间和学生的 $l_i$、$r_i$ 判断学生是否能取到茶。

- **drop（4星）**
    - **关键亮点**：思路简洁，代码简单易懂，明确指出了模拟过程中的重点。
    - **核心代码**：
```c++
#include<bits/stdc++.h>
using namespace std;
int t,n;

int main(){
    cin>>t;
    while(t--){
        int time=1;
        cin>>n;
        for(int i=1;i<=n;i++){
            int l,r;
            cin>>l>>r;
            if(time<l) time=l;
            if(r<time&&i!=1) cout<<0<<" ";
            else cout<<time++<<" ";
        }
        cout<<endl;
    } 
    return 0;
}
```
核心思想：用 `time` 记录当前时间，遍历每个学生，根据当前时间和学生的 $l_i$、$r_i$ 判断学生是否能取到茶。

- **_VEGETABLE_OIer_xlc（4星）**
    - **关键亮点**：思路清晰，代码规范，建议在循环里建造计数器，避免忘记清空。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,l,r;
int main(){
    cin>>t;
    while(t--)
    {
        cin>>n;
        int c=1;
        for(int i=1;i<=n;i++)
        {
            cin>>l>>r;
            if(l>=c)
                c=l;
            if(r<c&&i!=1)
            {
                cout<<0<<" ";
                continue;
            }
            else
            {
                cout<<c<<" ";
                c++;
            }
        }
        cout<<endl;
    }
    return 0;
}
```
核心思想：用 `c` 记录当前时间，遍历每个学生，根据当前时间和学生的 $l_i$、$r_i$ 判断学生是否能取到茶。

### 最优关键思路或技巧
使用一个变量记录当前时间，根据学生的到达时间和离开时间，结合当前时间判断学生是否能取到茶，避免复杂的数据结构，简化代码实现。

### 可拓展之处
同类型题可能会增加队列的规则，如多个茶壶、不同的接水时间等。类似算法套路为模拟题，通常需要根据题目规则，用变量记录状态，按时间顺序或操作顺序进行模拟。

### 推荐题目
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)

### 个人心得
- **ryf_loser**：看到楼上几位大佬的程序，看的我瑟瑟发抖。最容易错的地方在于不能把没喝到茶的学生算到总时间中。
总结：在模拟过程中要注意细节，避免将不符合条件的情况算入结果。 

---
处理用时：37.57秒