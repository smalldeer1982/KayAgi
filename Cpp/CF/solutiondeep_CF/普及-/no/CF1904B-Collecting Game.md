# 题目信息

# Collecting Game

## 题目描述

You are given an array $ a $ of $ n $ positive integers and a score. If your score is greater than or equal to $ a_i $ , then you can increase your score by $ a_i $ and remove $ a_i $ from the array.

For each index $ i $ , output the maximum number of additional array elements that you can remove if you remove $ a_i $ and then set your score to $ a_i $ . Note that the removal of $ a_i $ should not be counted in the answer.

## 说明/提示

In the first test case, the answers are as follows:

If we start with $ i=4 $ , our initial score is $ a_4=4 $ and $ a=[20,5,1,2] $ . We can remove $ 3 $ additional elements in the following order:

1. Since $ 4 \ge 1 $ , we can remove $ 1 $ and our score becomes $ 5 $ . After this, $ a=[20,5,2] $ .
2. Since $ 5 \ge 5 $ , we can remove $ 5 $ and our score becomes $ 10 $ . After this, $ a=[20,2] $ .
3. Since $ 10 \ge 2 $ , we can remove $ 2 $ and our score becomes $ 12 $ . After this, $ a=[20] $ .

If we start with $ i=1 $ we can remove all remaining elements in the array, so the answer is $ 4 $ .

If we start with $ i=2 $ , we can remove $ 3 $ additional elements in the following order: $ 1 $ , $ 4 $ , $ 2 $ .

If we start with $ i=3 $ , we can remove no additional elements.

If we start with $ i=5 $ , we can remove $ 1 $ additional element: $ 1 $ .

## 样例 #1

### 输入

```
4
5
20 5 1 4 2
3
1434 7 1442
1
1
5
999999999 999999999 999999999 1000000000 1000000000```

### 输出

```
4 3 0 3 1 
1 0 2 
0 
4 4 4 4 4```

# AI分析结果

【题目内容（中文重写）】
# 收集游戏

## 题目描述
给定一个包含 $n$ 个正整数的数组 $a$ 和一个分数。如果你的分数大于或等于 $a_i$，那么你可以将分数增加 $a_i$ 并从数组中移除 $a_i$。

对于每个索引 $i$，输出在移除 $a_i$ 并将分数设为 $a_i$ 后，你最多还能移除的数组元素数量。注意，移除 $a_i$ 这一操作不计入答案。

## 说明/提示
在第一个测试用例中，答案如下：

如果从 $i = 4$ 开始，初始分数为 $a_4 = 4$，数组 $a = [20, 5, 1, 2]$。我们可以按以下顺序移除 3 个额外元素：
1. 由于 $4 \geq 1$，我们可以移除 1，分数变为 5。此后，$a = [20, 5, 2]$。
2. 由于 $5 \geq 5$，我们可以移除 5，分数变为 10。此后，$a = [20, 2]$。
3. 由于 $10 \geq 2$，我们可以移除 2，分数变为 12。此后，$a = [20]$。

如果从 $i = 1$ 开始，我们可以移除数组中所有剩余元素，因此答案是 4。

如果从 $i = 2$ 开始，我们可以按以下顺序移除 3 个额外元素：1、4、2。

如果从 $i = 3$ 开始，我们无法移除任何额外元素。

如果从 $i = 5$ 开始，我们可以移除 1 个额外元素：1。

## 样例 #1

### 输入
```
4
5
20 5 1 4 2
3
1434 7 1442
1
1
5
999999999 999999999 999999999 1000000000 1000000000
```

### 输出
```
4 3 0 3 1 
1 0 2 
0 
4 4 4 4 4
```

【算法分类】贪心

【综合分析与结论】
这些题解的核心思路都是先对数组进行排序，因为从小到大删除元素是最优策略，能保证后续能删除更多元素。大部分题解还利用了前缀和来快速计算分数，提高效率。为了避免重复计算，不少题解采用双指针或记录上一次计算结果的方法。

各题解的主要区别在于实现细节和优化方式。例如，有的使用二分查找优化查找过程，有的通过递推直接计算答案。

【所选题解】
- 作者：huangrenheluogu (赞：7)，4星。关键亮点：思路清晰，先介绍了暴力解法，再逐步优化到双指针解法，代码简洁易懂。
- 作者：MicroSun (赞：5)，4星。关键亮点：详细解释了思路，通过预处理前缀和和维护上次计算的最大下标，实现了 $O(n)$ 的时间复杂度。
- 作者：_anll_ (赞：4)，4星。关键亮点：思路明确，结合注释的代码便于理解，同样利用前缀和和记录最大位置的方法进行优化。

【重点代码】
### 作者：huangrenheluogu
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int T, n, now, ans[N], s[N], tot;
struct node{
    int x, id;
}a[N];
inline bool cmp(node x, node y){
    return x.x < y.x;
}
signed main(){
    scanf("%lld", &T);
    while(T--){
        scanf("%lld", &n);
        for(int i = 1; i <= n; i++){
            a[i].id = i;
            scanf("%lld", &a[i].x);
        }
        now = 1;
        sort(a + 1, a + n + 1, cmp);
        for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i].x;
        for(int i = 1; i <= n; i++){
            now = max(now, i);
            tot = s[now];
            while(now < n && a[now + 1].x <= tot){
                tot += a[now + 1].x;
                now++;
            }
            ans[a[i].id] = now - 1;
        }
        for(int i = 1; i <= n; i++) printf("%lld ", ans[i]);
        putchar('\n');
    }
    return 0;
}
```
核心实现思想：先对数组按元素值从小到大排序，计算前缀和。然后遍历数组，对于每个元素，利用双指针，从上次能到达的位置开始，只要当前分数能吃下下一个元素，就更新分数和指针位置，最后记录答案。

### 作者：MicroSun
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    // 快速读入函数
}
inline void write(int x,char l='\n'){
    // 快速输出函数
}
using ll=long long;
using pii=pair<int,int>;
#define pb push_back
void solve(){
    int n=read();
    vector<pii> a(n+1);
    vector<ll> p(n+1);
    vector<int> ans(n+1);
    int l=0;
    for(int i=1;i<=n;i++) a[i]={read(),i};
    sort(begin(a)+1,end(a));
    p[0]=0;
    for(int i=1;i<=n;i++) p[i]=p[i-1]+a[i].first;
    for(int i=1;i<=n;i++){
        if(l<i){
            l=i;
            while(p[l]>=a[l+1].first&&l<n) l++;
        }
        ans[a[i].second]=l;
    }
    for(int i=1;i<=n;i++) write(ans[i]-1,' ');
    putchar('\n');	
}
int main(){
    int t=1;
    t=read();
    while(t--) solve();
}
```
核心实现思想：离线所有询问，对数组排序并预处理前缀和。维护一个指针 $l$ 表示上次计算中删除的元素的最大下标，对于每个元素，如果 $l$ 小于当前元素下标，就从当前元素开始往后扩展 $l$，直到不能再扩展，最后记录答案。

### 作者：_anll_
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define int long long
using namespace std;
struct Num{
    int id,val;
}num[100005];
int t,n,qzh[100005],anu[100005];
bool cmp(Num a,Num b){
    return a.val<b.val;
}
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>num[i].val;
            num[i].id=i;
        }
        sort(num+1,num+1+n,cmp);
        for(int i=1;i<=n;i++) qzh[i]=qzh[i-1]+num[i].val;
        int las=0,j,now=num[1].val;
        for(int i=1;i<=n;i++){
            las=max(las,i);
            anu[num[i].id]=las;
            for(j=las+1;j<=n;j++){
                if(qzh[j-1]<num[j].val) break;
            }
            las=j-1;
            anu[num[i].id]=las-1;
        }
        for(int i=1;i<=n;i++) cout<<anu[i]<<" ";
        cout<<endl;
    }
    return 0;
}
```
核心实现思想：对数组排序并计算前缀和，维护一个变量 $las$ 记录上次删除的最大元素位置。对于每个元素，从 $las + 1$ 开始往后遍历，只要前缀和能吃下当前元素就继续，更新 $las$ 并记录答案。

【关键思路或技巧】
- 排序：将数组按元素值从小到大排序，保证从最小的元素开始删除，是贪心策略的基础。
- 前缀和：预处理前缀和可以快速计算当前分数，避免重复计算，提高效率。
- 双指针或记录最大位置：避免每次都从头开始遍历，利用之前的计算结果，减少不必要的计算。

【拓展思路】
同类型题目可能会在规则上进行变化，例如增加元素的属性，或者改变删除元素的条件。类似的算法套路可以应用在其他贪心问题中，先确定最优策略，再通过排序、前缀和等方法优化计算过程。

【推荐题目】
- P1223 排队接水：涉及贪心策略，通过排序来优化结果。
- P1090 合并果子：同样是贪心问题，利用优先队列优化合并过程。
- P2240 食草的奶牛：需要根据条件进行排序和贪心选择。

【个人心得】
- 作者：P_VICVIC_R：提到老师强制要求学僧写题解，自己找出老早以前的比赛题。还提醒注意清数组，自己在这上面错了三回。总结：在多组数据的题目中，要注意数组的清空，避免数据残留影响结果。
- 作者：_anll_：感慨老被橙题卡得痛不欲生。总结：橙题有一定难度，需要不断练习和积累经验，提高解题能力。

---
处理用时：57.90秒