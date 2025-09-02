# 题目信息

# [USACO13NOV] Empty Stalls G

## 题目描述

Farmer John's new barn consists of a huge circle of N stalls (2 <= N <= 3,000,000), numbered 0..N-1, with stall N-1 being adjacent to stall 0.

At the end of each day, FJ's cows arrive back at the barn one by one, each with a preferred stall they would like to occupy.  However, if a cow's preferred stall is already occupied by another cow, she scans forward sequentially from this stall until she finds the first unoccupied stall, which she then claims.  If she scans past stall N-1, she continues scanning from stall 0.

Given the preferred stall of each cow, please determine the smallest index of a stall that remains unoccupied after all the cows have returned to the barn.  Notice that the answer to this question does not depend on the order in which the cows return to the barn.

In order to avoid issues with reading huge amounts of input, the input to this problem is specified in a concise format using K lines (1 <= K <= 10,000) each of the form:

X Y A B

One of these lines specifies the preferred stall for XY total cows: X cows prefer each of the stalls f(1) .. f(Y), where f(i) = (Ai + B) mod N.  The values of A and B lie in the range 0...1,000,000,000.

Do not forget the standard memory limit of 64MB for all problems.

约翰的谷仓中有N(2 <= N <=3,000,000)个房间，编号0到N-1，这些房间排布成环状,编号0的和编号N-1的相邻。

每天傍晚，奶牛们一只一只排队回到谷仓，每头奶牛都有一个喜欢的房间，但是，如果它喜欢的房间已被其他奶牛占了，它会向前挨个探索其他房间（如果它探索过了N-1号房间，它会继续探索0号房间，以此继续下去）直到探到第一个没有被占用的房间，这时它会宣布占用这个房间。

告诉你每头奶牛喜欢的房间，当所有奶牛都找到房间后，剩下的没被占用的房间中，编号最小的是哪个。很明显，问题的答案与奶牛进入谷仓的顺序无关。


为避免输入内容过多。本题的输入数据采用一种简洁的方式：一共K(1 <= K <=10,000)行，每行格式如下：

X Y A B

表示有Y批奶牛，每批X头，也就是总共X\*Y只奶牛喜欢的房间号。Y批奶牛编号1到Y，第i批X头奶牛喜欢的房间号为(A\*i+B) Mod N.

A和B的取值范围为0...1,000,000,000

注意，只有64M的空间。


## 说明/提示

There are 10 stalls in the barn, numbered 0..9.  The second line of input states that 3 cows prefer stall (2\*1+4) mod 10 = 6, and 3 cows prefer stall (2\*2+4) mod 10 = 8.  The third line states that 2 cows prefer stall (0\*1+1) mod 10 = 1.  Line four specifies that 1 cow prefers stall (1\*1+7) mod 10 = 8 (so a total of 4 cows prefer this stall).


All stalls will end up occupied except stall 5. 



## 样例 #1

### 输入

```
10 3 
3 2 2 4 
2 1 0 1 
1 1 1 7 
```

### 输出

```
5 
```

# AI分析结果

### 综合分析与结论
这些题解主要围绕奶牛选房间问题展开，解题思路大致可分为模拟分配和并查集两种。模拟分配思路是先统计各房间初始奶牛数，再通过多次循环将多余奶牛往后推，直至分配完毕；并查集思路则是用 `fa` 数组记录每头牛可去的房间，动态更新房间占用情况。各题解在代码实现、复杂度和细节处理上存在差异，但都能解决问题。

### 所选题解
- **小手冰凉（4星）**
    - **关键亮点**：思路清晰，利用题目中“答案与奶牛进入顺序无关”的信息，将所有数据一起处理，避免了复杂的模拟过程。代码简洁，使用 `read` 函数优化输入，同时考虑了数据可能爆 `int` 的情况。
    - **个人心得**：无

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3000000;
int n;
int ans[N];
int x,y,a,b,k;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
    return x*f;
}
signed main()
{
    n=read();k=read();
    while(k--){
        x=read();y=read();a=read();b=read();
        for(int i=1;i<=y;i++){
            ans[(a*i+b)%n]+=x;
        }
    }
    for(int i=0;i<n;i++){
        if(ans[i]>0)ans[(i+1)%n]+=ans[i]-1,ans[i]=1;
    }
    while(ans[0]>1)
        for(int i=0;i<n;i++){
            if(ans[i]>0)ans[(i+1)%n]+=ans[i]-1,ans[i]=1;
        }
    for(int i=0;i<n;i++)
        if(ans[i]==0){
            cout<<i<<endl;
            return 0;
        }
    return 0;
}
```
**核心实现思想**：先统计每个房间初始的奶牛数，然后通过循环将多余的奶牛往后推，每次循环保证每个房间最多有一头奶牛。由于房间是环形的，可能需要多次循环，直到第一个房间的奶牛数不超过 1。最后遍历房间，找到第一个没有奶牛的房间并输出其编号。

### 最优关键思路或技巧
- **利用题目特性**：根据“答案与奶牛进入顺序无关”，将所有数据一起处理，简化了问题。
- **模拟分配**：通过多次循环将多余的奶牛往后推，避免了复杂的模拟过程。
- **并查集优化**：部分题解使用并查集记录每头牛可去的房间，动态更新房间占用情况，提高了查找效率。

### 可拓展之处
同类型题或类似算法套路：
- 环形排列的资源分配问题，如环形座位分配、环形任务调度等。
- 涉及路径查找和连通性维护的问题，可使用并查集优化。

### 推荐题目
- [P1195 口袋的天空](https://www.luogu.com.cn/problem/P1195)：并查集的应用，用于判断图的连通性。
- [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)：经典的并查集问题，判断两个人是否为亲戚。
- [P2814 家谱](https://www.luogu.com.cn/problem/P2814)：并查集的应用，维护家族关系。

### 个人心得摘录与总结
- **不便透露**：一开始没注意“答案与奶牛进入顺序无关”，用并查集侥幸过了，提醒我们要仔细审题，充分利用题目信息。
- **yydfj**：提醒自己在写题解时要注意错误点，欢迎他人指出，体现了学习和进步的态度。

---
处理用时：32.80秒