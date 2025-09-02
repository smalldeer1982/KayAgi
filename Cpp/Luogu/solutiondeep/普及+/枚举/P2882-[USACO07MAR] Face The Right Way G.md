# 题目信息

# [USACO07MAR] Face The Right Way G

## 题目描述

Farmer John has arranged his N (1 ≤ N ≤ 5,000) cows in a row and many of them are facing forward, like good cows. Some of them are facing backward, though, and he needs them all to face forward to make his life perfect.

Fortunately, FJ recently bought an automatic cow turning machine. Since he purchased the discount model, it must be irrevocably preset to turn K (1 ≤ K ≤ N) cows at once, and it can only turn cows that are all standing next to each other in line. Each time the machine is used, it reverses the facing direction of a contiguous group of K cows in the line (one cannot use it on fewer than K cows, e.g., at the either end of the line of cows). Each cow remains in the same \*location\* as before, but ends up facing the \*opposite direction\*. A cow that starts out facing forward will be turned backward by the machine and vice-versa.

Because FJ must pick a single, never-changing value of K, please help him determine the minimum value of K that minimizes the number of operations required by the machine to make all the cows face forward. Also determine M, the minimum number of machine operations required to get all the cows facing forward using that value of K.

$N$ 头牛排成一列 $1 \le N \le 5000$。每头牛或者向前或者向后。为了让所有牛都面向前方，农夫每次可以将 $K$ 头连续的牛转向 $1 \le K \le N$，求使操作次数最小的相应 $K$ 和最小的操作次数 $M$。$F$ 为朝前，$B$ 为朝后。

请在一行输出两个数字 $K$ 和 $M$，用空格分开。

## 说明/提示

For K = 3, the machine must be operated three times: turn cows (1,2,3), (3,4,5), and finally (5,6,7)


## 样例 #1

### 输入

```
7
B
B
F
B
F
B
B```

### 输出

```
3 3```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何解决让所有牛都面向前方的问题，核心在于找到最小的操作区间长度 `K` 和对应的最小操作次数 `M`。大部分题解采用枚举 `K` 值并结合贪心和差分的方法，时间复杂度为 $O(n^2)$。

### 所选题解
- **作者：Delva（5星）**
  - **关键亮点**：思路清晰，对贪心策略和差分优化的解释详细，代码简洁易懂。
  - **个人心得**：无

### 重点代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 10009;
int n;
bool A[maxn],B[maxn];
int main(){
    scanf("%d",&n);
    char ch;
    for(int i=1;i<=n;++i){
        cin>>ch;A[i]=ch=='B'?0:1;
    }
    int mincnt=0x7fffffff,anslen;
    for(int len=1;len<=n;++len){
        memset(B,0,sizeof B);
        bool b=0,flag=1;int cnt=0;
        for(int i=1;i<=n;++i){
            b^=B[i];
            if(!(A[i]^b)){
                if(i+len-1>n){flag=0;break;}
                b^=1,B[i+len]^=1;
                ++cnt;
            }
        }
        if(flag){if(cnt<mincnt)mincnt=cnt,anslen=len;}
    }printf("%d %d\n",anslen, mincnt);
} 
```
**核心实现思想**：
1. 枚举不同的 `K` 值。
2. 对于每个 `K` 值，使用差分思想记录区间翻转情况，通过异或操作判断当前牛是否需要翻转。
3. 若当前位置的牛需要翻转且剩余长度足够，则进行翻转并更新差分数组。
4. 若所有牛都能翻转成功，记录最小操作次数和对应的 `K` 值。

### 最优关键思路或技巧
- **贪心策略**：从左到右对于出现的每一个 `B` 翻转一次从当前点开始的区间，能保证是最优解。
- **差分优化**：使用差分数组记录区间翻转情况，将区间修改的时间复杂度从 $O(n)$ 降低到 $O(1)$，从而将总时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。

### 拓展思路
同类型题或类似算法套路：
- 二维矩阵的翻转问题，如一次反转某个元素及其周围元素的值，可采用枚举第一行，然后按顺序向下操作的方法。
- 区间修改和查询问题，可使用差分、线段树、树状数组等数据结构进行优化。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：考察线段树的区间修改和查询操作。
2. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)：考察树状数组的区间修改和单点查询操作。
3. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：考察差分和二分查找的结合应用。

### 个人心得摘录与总结
- **FallR**：在实现过程中因为序列后面元素数目不足 `k - 1` 个时的判断问题导致 90 分，找了一个多小时的错。总结：在处理边界条件时要格外小心，仔细检查判断条件是否正确。
- **LevenKoko**：无聊想刷水题然而却 T 了，怒怼一波常数，尝试了各种卡常优化。总结：当暴力算法超时，可尝试一些卡常优化技巧，但在正式比赛中要谨慎使用。

---
处理用时：32.14秒