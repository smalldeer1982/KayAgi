# 题目信息

# Berland Music

## 题目描述

Berland Music is a music streaming service built specifically to support Berland local artist. Its developers are currently working on a song recommendation module.

So imagine Monocarp got recommended $ n $ songs, numbered from $ 1 $ to $ n $ . The $ i $ -th song had its predicted rating equal to $ p_i $ , where $ 1 \le p_i \le n $ and every integer from $ 1 $ to $ n $ appears exactly once. In other words, $ p $ is a permutation.

After listening to each of them, Monocarp pressed either a like or a dislike button. Let his vote sequence be represented with a string $ s $ , such that $ s_i=0 $ means that he disliked the $ i $ -th song, and $ s_i=1 $ means that he liked it.

Now the service has to re-evaluate the song ratings in such a way that:

- the new ratings $ q_1, q_2, \dots, q_n $ still form a permutation ( $ 1 \le q_i \le n $ ; each integer from $ 1 $ to $ n $ appears exactly once);
- every song that Monocarp liked should have a greater rating than every song that Monocarp disliked (formally, for all $ i, j $ such that $ s_i=1 $ and $ s_j=0 $ , $ q_i>q_j $ should hold).

Among all valid permutations $ q $ find the one that has the smallest value of $ \sum\limits_{i=1}^n |p_i-q_i| $ , where $ |x| $ is an absolute value of $ x $ .

Print the permutation $ q_1, q_2, \dots, q_n $ . If there are multiple answers, you can print any of them.

## 说明/提示

In the first testcase, there exists only one permutation $ q $ such that each liked song is rating higher than each disliked song: song $ 1 $ gets rating $ 2 $ and song $ 2 $ gets rating $ 1 $ . $ \sum\limits_{i=1}^n |p_i-q_i|=|1-2|+|2-1|=2 $ .

In the second testcase, Monocarp liked all songs, so all permutations could work. The permutation with the minimum sum of absolute differences is the permutation equal to $ p $ . Its cost is $ 0 $ .

## 样例 #1

### 输入

```
3
2
1 2
10
3
3 1 2
111
8
2 3 1 8 5 4 7 6
01110001```

### 输出

```
2 1
3 1 2
1 6 5 8 3 2 4 7```

# AI分析结果

### 题目内容
# Berland音乐

## 题目描述
Berland音乐是一款专门为支持Berland本土艺术家而打造的音乐流媒体服务。其开发者目前正在致力于开发歌曲推荐模块。

假设Monocarp收到了$n$首推荐歌曲，编号从$1$到$n$。第$i$首歌曲的预测评分是$p_i$，其中$1 \leq p_i \leq n$，并且从$1$到$n$的每个整数都恰好出现一次。换句话说，$p$是一个排列。

在听完每首歌后，Monocarp会按下喜欢或不喜欢按钮。用字符串$s$表示他的投票序列，其中$s_i = 0$表示他不喜欢第$i$首歌，$s_i = 1$表示他喜欢这首歌。

现在，该服务必须重新评估歌曲评分，使得：
- 新的评分$q_1, q_2, \dots, q_n$仍然构成一个排列（$1 \leq q_i \leq n$；从$1$到$n$的每个整数都恰好出现一次）；
- Monocarp喜欢的每首歌的评分都必须高于他不喜欢的每首歌的评分（形式上，对于所有满足$s_i = 1$且$s_j = 0$的$i, j$，都应有$q_i > q_j$）。

在所有有效的排列$q$中，找到使得$\sum\limits_{i=1}^n |p_i - q_i|$值最小的那个排列，其中$|x|$是$x$的绝对值。

输出排列$q_1, q_2, \dots, q_n$。如果有多个答案，可以输出其中任意一个。

## 说明/提示
在第一个测试用例中，只有一个排列$q$满足每首喜欢的歌曲的评分都高于每首不喜欢的歌曲的评分：歌曲$1$的评分是$2$，歌曲$2$的评分是$1$。$\sum\limits_{i=1}^n |p_i - q_i| = |1 - 2| + |2 - 1| = 2$。

在第二个测试用例中，Monocarp喜欢所有歌曲，所以所有排列都可行。绝对差之和最小的排列就是与$p$相等的排列。其代价为$0$。

## 样例 #1
### 输入
```
3
2
1 2
10
3
3 1 2
111
8
2 3 1 8 5 4 7 6
01110001
```

### 输出
```
2 1
3 1 2
1 6 5 8 3 2 4 7
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，目标是在满足喜欢的歌曲评分高于不喜欢歌曲评分的条件下，让新评分$q_i$尽量接近原评分$p_i$，以使得$\sum\limits_{i=1}^n |p_i - q_i|$最小。
1. **思路方面**：大多题解都提到先将喜欢（$s_i = 1$）和不喜欢（$s_i = 0$）的歌曲分开处理，再分别对这两类歌曲按原评分排序，最后根据排序结果构造新的评分序列$q$。
2. **算法要点**：利用结构体存储歌曲的原评分、位置、喜爱程度等信息，通过排序（如按原评分或喜爱程度排序）来实现贪心策略。
3. **解决难点**：难点在于证明贪心策略的正确性，即为何这样构造能使$\sum\limits_{i=1}^n |p_i - q_i|$最小。部分题解通过数学证明，对比不同交换情况的差距来论证。

### 所选的题解
#### 作者：让风忽悠你 (5星)
- **关键亮点**：思路清晰，先从简单情况入手分析，逐步引出复杂情况的处理方法。代码简洁明了，通过记录位置、排序、分类型构造新评分序列，很好地实现了贪心策略。
```cpp
#include<cstdio>
#include<algorithm>
#define N 200005 

using namespace std;

int T,n,cnt;
struct node{
    int p,idx;
}a[N];
int q[N];
bool pd[N];
char ch;

inline bool cmp(const node &a,const node &b){
    return a.p<b.p;
} //按照数值从小到大 

int main(){
    scanf("%d",&T);
    while(T--){
        cnt=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].p);
            a[i].idx=i;// 记录位置 
        }
        sort(a+1,a+1+n,cmp);
        for(int i=1;i<=n;i++){
            scanf(" %c",&ch);
            pd[i]=(ch=='0'); //记录类型 
        }
        for(int i=1;i<=n;i++)
            if(pd[a[i].idx])
                q[a[i].idx]=++cnt; 
        for(int i=1;i<=n;i++)
            if(!pd[a[i].idx])
                q[a[i].idx]=++cnt;
        //分类型构造 
        for(int i=1;i<=n;i++)
            printf("%d ",q[i]);
        printf("\n");
    }
    return 0;
}
```
核心实现思想：先读入原评分并记录位置，按原评分从小到大排序。再读入喜爱程度，先对不喜欢的歌曲按顺序赋予较小的新评分，再对喜欢的歌曲按顺序赋予较大的新评分。

#### 作者：Xdl_rp (4星)
- **关键亮点**：直接阐述贪心策略的两个要点，逻辑清晰。代码实现简洁，通过分离喜欢和不喜欢的歌曲，分别排序并构造新评分，符合贪心思路。
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int v, id;
}a[200005];
node sm[200005], bi[200005];
int ans[200005];
bool cmp(const node& x, const node& y) {
    return x.v < y.v;
}
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].v;
            a[i].id = i;
        }
        string s;
        cin >> s;
        int rs = 0, rb = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                sm[++rs] = a[i + 1];
            }
            else {
                bi[++rb] = a[i + 1];
            }
        }
        sort(sm + 1, sm + rs + 1, cmp);
        sort(bi + 1, bi + rb + 1, cmp);
        for (int i = 1; i <= rs; i++) {
            ans[sm[i].id] = i;
        }
        for (int i = 1; i <= rb; i++) {
            ans[bi[i].id] = rs + i;
        }
        for (int i = 1; i <= n; i++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
```
核心实现思想：读入原评分和喜爱程度，将不喜欢和喜欢的歌曲分别存入不同数组，对这两个数组按原评分排序，然后分别给不喜欢和喜欢的歌曲赋予从小到大的新评分。

#### 作者：ArrogHie (4星)
- **关键亮点**：不仅给出解题思路，还对贪心策略进行了详细的数学证明，通过数轴上的直观表示说明为何较小的数应填入较小原评分对应的位置。
```cpp
// 证明部分代码略，主要是思路阐述
// 核心代码部分
#include <iostream>
#include <algorithm>
using namespace std;
struct node{
    int v, id;
}a[200005];
node sm[200005], bi[200005];
int ans[200005];
bool cmp(const node& x, const node& y) {
    return x.v < y.v;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].v;
            a[i].id = i;
        }
        string s;
        cin >> s;
        int rs = 0, rb = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                sm[++rs] = a[i + 1];
            }
            else {
                bi[++rb] = a[i + 1];
            }
        }
        sort(sm + 1, sm + rs + 1, cmp);
        sort(bi + 1, bi + rb + 1, cmp);
        for (int i = 1; i <= rs; i++) {
            ans[sm[i].id] = i;
        }
        for (int i = 1; i <= rb; i++) {
            ans[bi[i].id] = rs + i;
        }
        for (int i = 1; i <= n; i++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
```
核心实现思想：与Xdl_rp的代码类似，先分离喜欢和不喜欢的歌曲，分别排序后按顺序赋予新评分，不同在于对贪心策略进行了详细证明。

### 最优关键思路或技巧
1. **贪心策略**：优先满足喜欢的歌曲评分高于不喜欢的歌曲评分，在此基础上让新评分尽量接近原评分。
2. **数据结构运用**：使用结构体存储歌曲的多种信息，方便进行排序和处理。

### 同类型题或类似算法套路拓展
同类型题通常围绕贪心策略展开，在满足某种大小关系或条件限制下，求某个目标函数的最值。类似套路包括先根据条件对数据进行分类，再对每类数据按某个关键值排序，最后根据排序结果构造满足条件且使目标函数最优的解。

### 推荐题目
1. **P1090 [NOIP2004 提高组] 合并果子**：通过贪心策略，每次选择最小的两个果子堆合并，以最小化总代价。
2. **P1199 [NOIP2010 普及组] 三国游戏**：运用贪心思想，根据武将武力值的关系进行策略选择。
3. **P2859 [USACO06DEC]Milk Patterns G**：利用贪心和后缀数组相关知识，寻找重复出现的子串模式。 

---
处理用时：60.06秒