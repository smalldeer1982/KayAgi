# 题目信息

# Sifid and Strange Subsequences

## 题目描述

A sequence $ (b_1, b_2, \ldots, b_k) $ is called strange, if the absolute difference between any pair of its elements is greater than or equal to the maximum element in the sequence. Formally speaking, it's strange if for every pair $ (i, j) $ with $ 1 \le i<j \le k $ , we have $ |a_i-a_j|\geq MAX $ , where $ MAX $ is the largest element of the sequence. In particular, any sequence of length at most $ 1 $ is strange.

For example, the sequences $ (-2021, -1, -1, -1) $ and $ (-1, 0, 1) $ are strange, but $ (3, 0, 1) $ is not, because $ |0 - 1| < 3 $ .

Sifid has an array $ a $ of $ n $ integers. Sifid likes everything big, so among all the strange subsequences of $ a $ , he wants to find the length of the longest one. Can you help him?

A sequence $ c $ is a subsequence of an array $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first test case, one of the longest strange subsequences is $ (a_1, a_2, a_3, a_4) $

In the second test case, one of the longest strange subsequences is $ (a_1, a_3, a_4, a_5, a_7) $ .

In the third test case, one of the longest strange subsequences is $ (a_1, a_3, a_4, a_5) $ .

In the fourth test case, one of the longest strange subsequences is $ (a_2) $ .

In the fifth test case, one of the longest strange subsequences is $ (a_1, a_2, a_4) $ .

## 样例 #1

### 输入

```
6
4
-1 -2 0 0
7
-3 4 -2 0 -4 6 1
5
0 5 -3 2 -5
3
2 3 1
4
-3 0 2 0
6
-3 -2 -1 1 1 1```

### 输出

```
4
5
4
1
3
4```

# AI分析结果

### 题目内容
# Sifid和奇怪的子序列

## 题目描述
一个序列$(b_1, b_2, \ldots, b_k)$被称为奇怪的，如果它任意两个元素之间的绝对差大于或等于序列中的最大元素。 形式上，如果对于每一对$(i, j)$，其中$1 \leq i < j \leq k$，我们有$|a_i - a_j| \geq MAX$，其中$MAX$是序列中的最大元素，那么这个序列就是奇怪的。 特别地，任何长度至多为1的序列都是奇怪的。

例如，序列$(-2021, -1, -1, -1)$和$(-1, 0, 1)$是奇怪的，但$(3, 0, 1)$不是，因为$|0 - 1| < 3$。

Sifid有一个包含$n$个整数的数组$a$。Sifid喜欢所有大的东西，所以在$a$的所有奇怪子序列中，他想找到最长的那个的长度。你能帮助他吗？

一个序列$c$是数组$d$的子序列，如果$c$可以通过删除$d$中的几个（可能是零个或全部）元素得到。

## 说明/提示
在第一个测试用例中，最长的奇怪子序列之一是$(a_1, a_2, a_3, a_4)$。

在第二个测试用例中，最长的奇怪子序列之一是$(a_1, a_3, a_4, a_5, a_7)$。

在第三个测试用例中，最长的奇怪子序列之一是$(a_1, a_3, a_4, a_5)$。

在第四个测试用例中，最长的奇怪子序列之一是$(a_2)$。

在第五个测试用例中，最长的奇怪子序列之一是$(a_1, a_2, a_4)$。

## 样例 #1
### 输入
```
6
4
-1 -2 0 0
7
-3 4 -2 0 -4 6 1
5
0 5 -3 2 -5
3
2 3 1
4
-3 0 2 0
6
-3 -2 -1 1 1 1
```
### 输出
```
4
5
4
1
3
4
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解的核心思路都是基于贪心策略。要点在于发现所有非正数必然满足奇怪子序列的条件，所以先将所有非正数选入子序列。对于正数，最多只能选一个，且若要选，应选最小的正数，然后通过排序数组，检查相邻非正数元素差值是否小于该最小正数，来判断能否将其选入。各题解的主要区别在于代码实现细节及对思路的阐述清晰度。

### 题解1
- **星级**：4星
- **关键亮点**：思路清晰，先明确选出所有非正数，再通过计算非正数间最小差值，与最小正数比较，判断是否能选入最小正数，逻辑连贯。
```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,a[Len];
inline int Iabs(int x){return x < 0? -x : x;}
int main()
{
    int t;scanf("%d",&t);
    while(t --)
    {
        scanf("%d",&n);
        for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
        bool flag = false ;int flaw = 0;int ans = 0;
        for(int i = 1 ; i <= n ; i ++) if(a[i] < 0) ans ++;
        for(int i = 1 ; i <= n ; i ++) 
        {
            if(a[i] > 0) flag |= 1;
            if(a[i] == 0) flaw ++;
        }
        sort(a + 1, a + 1 + n);
        int idx = 1;
        for(; idx <= n ; idx ++) if(a[idx] > 0) break;
        if(!flag){printf("%d\n",ans + flaw);continue;}
        int Ans = ans + flaw;bool flalwd = true;
        for(int i = 2 ; i < idx ; i ++) if(Iabs(a[i] - a[i - 1]) < a[idx]) {flalwd = false ; break;}
        if(flalwd) printf("%d\n",Ans + 1);
        else printf("%d\n",Ans);
    }
    return 0;
}
```
核心实现思想：先统计负数个数`ans`，标记是否有正数`flag`及零的个数`flaw`。排序后找到第一个正数位置`idx`，若没有正数则直接输出`ans + flaw`。否则检查非正数间相邻差值是否小于第一个正数，决定是否加1输出。

### 题解2
- **星级**：4星
- **关键亮点**：证明了最多只能添加一个正数且若添加则为最小正数这两个重要结论，使得解题思路更具严谨性。
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int N=1e5+10,inf=0x7fffffff;

int n,a[N],ans;

int main(){
    int t;scanf("%d",&t);
    while(t--){
        scanf("%d",&n);ans=0;
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);
            if(a[i]<=0)++ans;
        }
        sort(a+1,a+n+1);
        int minn=inf;
        for(int i=1;i<ans;++i)minn=min(minn,a[i+1]-a[i]);
        for(int i=ans+1;i<=n;++i){
            minn=min(minn,a[i]-a[i-1]);
            if(minn>=a[i])++ans;
            else break;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
核心实现思想：先统计非正数个数`ans`，排序后求出非正数间最小差值`minn`，再遍历正数，每次更新`minn`并判断是否能加入该正数，能则`ans`加1。

### 题解3
- **星级**：4星
- **关键亮点**：代码简洁，逻辑清晰，直接在排序后的数组上进行遍历判断，通过不断更新最小差值和最大值，决定是否选择当前数加入子序列。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t, k, a[100005];
main() {
    ios::sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i(1); i <= n; ++i) cin >> a[i];
        sort(a + 1, a + n + 1);
        int ma = a[1], jg = 2000000001, cnt = 1;
        for (int i(2); i <= n; ++i) {
            int nj = a[i] - a[i - 1];
            if (min(nj, jg) >= max(ma, a[i])) {
                ++cnt;
                jg = min(jg, nj);
                ma = max(ma, a[i]);
            }
        }
        cout << cnt << endl;
    }
}
```
核心实现思想：排序后，从第二个数开始遍历，比较相邻数差值`nj`与当前最小差值`jg`、当前最大值`ma`与当前数`a[i]`，若满足条件则更新`cnt`、`jg`和`ma`。

### 最优关键思路或技巧
利用贪心策略，先确定非正数必选，再分析正数最多选一个且为最小正数的特性。通过排序数组，利用相邻元素差值判断是否满足奇怪子序列条件，简化判断过程。

### 拓展
同类型题可考虑对奇怪子序列条件进行变化，如改变差值与最大元素的关系，或在不同数据结构上进行类似操作。类似算法套路是先分析满足条件的简单情况（如本题非正数情况），再对复杂情况（正数情况）进行细致讨论，利用排序等手段辅助判断。

### 洛谷相似题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123) 

---
处理用时：73.92秒