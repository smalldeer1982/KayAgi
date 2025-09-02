# 题目信息

# Death's Blessing

## 题目描述

You are playing a computer game. To pass the current level, you have to kill a big horde of monsters. In this horde, there are $ n $ monsters standing in the row, numbered from $ 1 $ to $ n $ . The $ i $ -th monster has $ a_i $ health and a special "Death's Blessing" spell of strength $ b_i $ attached to it.

You are going to kill all of them one by one. It takes exactly $ h $ seconds to kill a monster with health $ h $ .

When the $ i $ -th monster dies, it casts its spell that increases the health of its neighbors by $ b_i $ (the neighbors of the $ j $ -th monster in the row are the monsters on places $ j - 1 $ and $ j + 1 $ . The first and the last monsters have only one neighbor each).

After each monster is killed, the row shrinks, so its former neighbors become adjacent to each other (so if one of them dies, the other one is affected by its spell). For example, imagine a situation with $ 4 $ monsters with health $ a = [2, 6, 7, 3] $ and spells $ b = [3, 6, 0, 5] $ . One of the ways to get rid of the monsters is shown below:

  $ 2 $  $ 6 $  $ 7 $  $ 3 $  $ \xrightarrow{6\ s} $  $ 8 $  $ 13 $  $ 3 $  $ \xrightarrow{13\ s} $  $ 8 $  $ 3 $  $ \xrightarrow{8\ s} $  $ 6 $  $ \xrightarrow{6\ s} $  $ \{\} $  $ 3 $  $ 6 $  $ 0 $  $ 5 $  $ 3 $  $ 0 $  $ 5 $  $ 3 $  $ 5 $  $ 5 $ The first row represents the health of each monster, the second one — the power of the spells.As a result, we can kill all monsters in $ 6 + 13 + 8 + 6 $ $ = $ $ 33 $ seconds. Note that it's only an example and may not be the fastest way to get rid of the monsters.

What is the minimum time required to kill all monsters in the row?

## 说明/提示

In the first test case, there is only one monster that will be killed in $ 10 $ seconds.

In the second test case, it's optimal to kill the first monster, the last monster and then the middle one. It will take $ 100 + 100 + (1 + 1 + 1) $ $ = $ $ 203 $ seconds.

In the third test case, it's optimal to kill the first monster, then the third one, then the fourth one and finally the second one. It will take $ 2 + 7 + (3 + 0) + (3 + 6 + 5) $ $ = $ $ 26 $ seconds.

## 样例 #1

### 输入

```
4
1
10
0
3
100 1 100
1 100 1
4
2 6 7 3
3 6 0 5
2
1000000000 1000000000
1000000000 1000000000```

### 输出

```
10
203
26
3000000000```

# AI分析结果

### 题目内容
# 死亡祝福

## 题目描述
你正在玩一款电脑游戏。为了通过当前关卡，你必须消灭一大群怪物。在这群怪物中，有 $n$ 只怪物排成一排，编号从 $1$ 到 $n$ 。第 $i$ 只怪物有 $a_i$ 的生命值，并且附着一个强度为 $b_i$ 的特殊 “死亡祝福” 法术。

你将逐个消灭它们。消灭一只生命值为 $h$ 的怪物恰好需要 $h$ 秒。

当第 $i$ 只怪物死亡时，它会施展法术，使它的相邻怪物的生命值增加 $b_i$ （这一排中第 $j$ 只怪物的相邻怪物是位置为 $j - 1$ 和 $j + 1$ 的怪物。第一只和最后一只怪物各自只有一个相邻怪物）。

在每只怪物被消灭后，这一排会收缩，所以它之前的相邻怪物会彼此相邻（所以如果其中一只死亡，另一只会受到它的法术影响）。例如，假设有 $4$ 只怪物，生命值 $a = [2, 6, 7, 3]$ ，法术强度 $b = [3, 6, 0, 5]$ 。消灭怪物的一种方式如下所示：

$2$  $6$  $7$  $3$  $\xrightarrow{6\ s}$  $8$  $13$  $3$  $\xrightarrow{13\ s}$  $8$  $3$  $\xrightarrow{8\ s}$  $6$  $\xrightarrow{6\ s}$  $\{\}$ 
$3$  $6$  $0$  $5$  $3$  $0$  $5$  $3$  $5$  $5$ 
第一行表示每只怪物的生命值，第二行表示法术的强度。结果是，我们可以在 $6 + 13 + 8 + 6 = 33$ 秒内消灭所有怪物。请注意，这只是一个示例，可能不是消灭怪物的最快方式。

消灭这一排所有怪物所需的最短时间是多少？

## 说明/提示
在第一个测试用例中，只有一只怪物，将在 $10$ 秒内被消灭。

在第二个测试用例中，最优的方法是先消灭第一只怪物，再消灭最后一只怪物，然后消灭中间那只。这将花费 $100 + 100 + (1 + 1 + 1) = 203$ 秒。

在第三个测试用例中，最优的方法是先消灭第一只怪物，然后是第三只，接着是第四只，最后是第二只。这将花费 $2 + 7 + (3 + 0) + (3 + 6 + 5) = 26$ 秒。

## 样例 #1
### 输入
```
4
1
10
0
3
100 1 100
1 100 1
4
2 6 7 3
3 6 0 5
2
1000000000 1000000000
1000000000 1000000000
```
### 输出
```
10
203
26
3000000000
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略。大家都意识到所有怪物的 $a_i$ 必然会计入总时间，而对于 $b_i$，关键在于如何使其对总时间的增加最小。大多数题解发现从两边删除怪物能保证每个 $b_i$ 最多只被加到相邻怪物一次（除了最后一个被删除怪物的 $b_i$），并且将最大的 $b_i$ 留到最后删除可使总时间最小，进而得出公式 $\sum_{i=1}^n{a_i}+\sum_{i=1}^n{b_i}-\max_{i=1}^n{b_i}$ 。部分题解通过双指针模拟从两边删除怪物的过程，另一些则直接利用公式计算。

### 所选的题解
- **作者：Yang818 (5星)**
    - **关键亮点**：思路清晰，不仅提出核心公式，还给出逆向思维的小技巧，即无需链表模拟删除过程，直接通过公式计算。代码简洁明了，使用快速读入优化输入。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define F(_b,_e) for(int i=_b;i<=_e;i++)
using namespace std;

inline int read(){
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return f*x;
}
int a,n,t;
long long sum;
int main(){
    //ios::sync_with_stdio(0);
    t=read();
    while(t--){
        n=read();
        sum=0;
        F(1,n){
            a=read();
            sum+=a;
        }
        int maxx=-1;
        F(1,n){
            a=read();
            maxx=max(maxx,a);
            sum+=a;
        }
        cout<<sum-maxx<<endl;
    }
    return 0;
}
```
核心实现思想：先通过循环读入并累加所有怪物的生命值 $a_i$，再读入所有法术强度 $b_i$ 并找出最大值，同时累加 $b_i$，最后用总和减去 $b_i$ 的最大值得到结果。
- **作者：Strelitzia_ (4星)**
    - **关键亮点**：对思路阐述详细，先明确题目大意，再深入分析并证明贪心策略的正确性。代码简洁高效。
    - **重点代码**：
```cpp
int t,n,ans,mx;struct E{int hth,d,l,r;}s[N];
signed main(){
    t=read();for(int nowt=1;nowt<=t;nowt++){
        n=read(),ans=0,mx=0;for(int i=1;i<=n;i++) s[i].hth=read(),ans+=s[i].hth;
        for(int i=1;i<=n;i++){
            s[i].d=read();mx=max(mx,s[i].d);ans+=s[i].d;
        }printf("%lld\n",ans-mx);
    }return Strelitzia_H;
}
```
核心实现思想：定义结构体数组存储怪物信息，先读入生命值并累加，再读入法术强度，找出最大值并累加，最后输出总和减去最大值的结果。
- **作者：东灯 (4星)**
    - **关键亮点**：直接从贪心角度出发，通过双指针模拟从两边删除怪物的过程，代码直观易懂。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define MAXN 200005
int t,n,a[MAXN],b[MAXN];
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        int left=1,right=n,ans(0);
        for(register int i=1;i<=n;++i)cin>>a[i];
        for(register int i=1;i<=n;++i)cin>>b[i];
        while(left!=right){
            if(b[left]<b[right]){
                ans+=a[left];
                a[left+1]+=b[left];
                ++left;
            }else{
                ans+=a[right];
                a[right-1]+=b[right];
                --right;
            }
        }
        ans+=a[left];
        cout<<ans<<endl;
    }
}
```
核心实现思想：用双指针 `left` 和 `right` 分别指向数组两端，每次比较两端的 $b_i$，将较小的一端对应的 $a_i$ 累加到答案中，并更新相邻怪物的生命值，移动指针，直到只剩下一个怪物，再将其生命值累加到答案。

### 最优关键思路或技巧
1. **贪心策略**：意识到从两边删除怪物能使每个 $b_i$ 对总时间增加最小化，且将最大的 $b_i$ 留到最后删除。
2. **逆向思维**：不模拟删除过程，直接通过公式 $\sum_{i=1}^n{a_i}+\sum_{i=1}^n{b_i}-\max_{i=1}^n{b_i}$ 计算结果，简化问题。

### 可拓展思路
此类贪心问题通常需要分析每个元素对结果的影响，找到一种顺序或方式使整体代价最小。类似题目可能会改变元素间的影响规则，或者在不同的数据结构（如树、图）上进行操作，但核心仍是通过合理的贪心策略优化结果。

### 相似知识点洛谷题目
1. [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
2. [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
3. [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
暂无个人心得。 

---
处理用时：68.30秒