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
这些题解的核心思路均为枚举区间长度 `K`，并对每个 `K` 计算使所有牛朝前的最小操作次数，最终找出最小操作次数对应的 `K` 和操作次数 `M`。多数题解采用贪心策略，即从左到右遇到朝后的牛就翻转以当前牛为起点的长度为 `K` 的区间。为优化时间复杂度，大部分题解使用了差分技巧，将区间修改的时间复杂度从 $O(n)$ 降至 $O(1)$，从而使整体复杂度从 $O(n^3)$ 优化到 $O(n^2)$。

### 所选题解
- **作者：Delva (赞：58)，4星**
  - **关键亮点**：思路清晰，详细模拟了样例，对差分的解释和实现较为易懂。
  - **个人心得**：无
- **作者：FallR (赞：41)，4星**
  - **关键亮点**：对贪心策略的分析详细，通过对比不同翻转起点的情况，解释了为什么要从第一个 `0` 开始翻转。同时，对差分的引入和使用有较为清晰的阐述。
  - **个人心得**：因未正确处理序列后面元素数目不足 `k - 1` 个的情况，导致90分，找错一个多小时。
- **作者：llzzxx712 (赞：31)，4星**
  - **关键亮点**：对题意和算法思路分析全面，详细解释了差分的实现方法，代码中注释丰富，易于理解。
  - **个人心得**：无

### 重点代码及核心实现思想
#### Delva 的题解
```cpp
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
}
```
**核心思想**：枚举区间长度 `len`，使用差分数组 `B` 记录区间翻转情况，`b` 表示当前位置的翻转状态。遇到朝后的牛时，若剩余长度足够则进行翻转，并更新差分数组和操作次数。

#### FallR 的题解
```cpp
for(register int k=1;k<=n;k++){
    sum=0;tag=0;op=0;
    memset(f,0,sizeof(f));
    for(register int i=1;i<=n;i++){
        if((a[i]+tag)%2==0){
            if(i+k-1>n){
                op=1;
                break;
            }
            ++sum;
            ++tag;
            f[i+k-1]=-1;
        }
        if(f[i]==-1){
            --tag;
            f[i]=0;
        }
    }
    if(op) continue;
    if(sum<ans){
        ans=sum;
        ansk=k;
    }
}
```
**核心思想**：枚举 `k`，使用 `tag` 记录当前位置的翻转次数，`f` 数组作为差分数组。遇到朝后的牛时，若剩余长度足够则进行翻转，更新 `tag` 和差分数组。

#### llzzxx712 的题解
```cpp
for(int k=1;k<=n;k++){
    memset(cha,0,sizeof(cha));
    int flag=1,tot=0,now=0;
    for(int i=1;i<=n;i++){
        now^=cha[i];
        if(a[i]^now==0){
            if(i+k-1>n){
                flag=0;
                break;
            }
            tot++;
            now^=1,cha[i+k]^=1;
        }
    }
    if(flag){
        if(tot<ansm){
            ansm=tot;
            ansk=k;
        }
    }
}
```
**核心思想**：枚举 `k`，使用 `now` 表示当前位置的翻转状态，`cha` 数组作为差分数组。遇到朝后的牛时，若剩余长度足够则进行翻转，更新 `now` 和差分数组。

### 最优关键思路或技巧
- **贪心策略**：从左到右遇到朝后的牛就翻转以当前牛为起点的长度为 `K` 的区间，可保证操作次数最少。
- **差分优化**：使用差分数组记录区间翻转情况，将区间修改的时间复杂度从 $O(n)$ 降至 $O(1)$，从而将整体复杂度从 $O(n^3)$ 优化到 $O(n^2)$。

### 可拓展之处
同类型题如二维版本的翻转问题，一次反转某个格子及其周围的格子，可采用类似的思路，如枚举第一行的状态，然后根据第一行的状态递推后续行的状态。类似算法套路包括按顺序操作、利用差分或前缀和优化区间操作等。

### 推荐题目
- P1896 [SCOI2005] 互不侵犯：状态压缩动态规划，与本题按顺序操作的思路有相似之处。
- P2704 [NOI2001] 炮兵阵地：状态压缩动态规划，同样需要考虑状态的转移和优化。
- P1040 加分二叉树：区间动态规划，涉及区间的划分和状态的更新。

### 个人心得总结
FallR 因未正确处理序列后面元素数目不足 `k - 1` 个的情况，导致90分，找错一个多小时。这提醒我们在处理边界条件时要格外仔细，避免因小错误导致大量时间的浪费。

---
处理用时：43.13秒