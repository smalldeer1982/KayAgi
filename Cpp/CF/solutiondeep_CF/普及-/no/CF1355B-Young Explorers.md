# 题目信息

# Young Explorers

## 题目描述

Young wilderness explorers set off to their first expedition led by senior explorer Russell. Explorers went into a forest, set up a camp and decided to split into groups to explore as much interesting locations as possible. Russell was trying to form groups, but ran into some difficulties...

Most of the young explorers are inexperienced, and sending them alone would be a mistake. Even Russell himself became senior explorer not long ago. Each of young explorers has a positive integer parameter $ e_i $ — his inexperience. Russell decided that an explorer with inexperience $ e $ can only join the group of $ e $ or more people.

Now Russell needs to figure out how many groups he can organize. It's not necessary to include every explorer in one of the groups: some can stay in the camp. Russell is worried about this expedition, so he asked you to help him.

## 说明/提示

In the first example we can organize three groups. There will be only one explorer in each group. It's correct because inexperience of each explorer equals to $ 1 $ , so it's not less than the size of his group.

In the second example we can organize two groups. Explorers with inexperience $ 1 $ , $ 2 $ and $ 3 $ will form the first group, and the other two explorers with inexperience equal to $ 2 $ will form the second group.

This solution is not unique. For example, we can form the first group using the three explorers with inexperience equal to $ 2 $ , and the second group using only one explorer with inexperience equal to $ 1 $ . In this case the young explorer with inexperience equal to $ 3 $ will not be included in any group.

## 样例 #1

### 输入

```
2
3
1 1 1
5
2 3 1 2 2```

### 输出

```
3
2```

# AI分析结果

### 题目内容
# 年轻的探险家

## 题目描述
年轻的野外探险家们在资深探险家罗素的带领下开始了他们的首次探险。探险家们进入森林，搭建营地，并决定分成小组，以探索尽可能多的有趣地点。罗素在组建小组时遇到了一些困难……

大多数年轻探险家缺乏经验，让他们单独行动将是个错误。就连罗素自己也是不久前才成为资深探险家的。每位年轻探险家都有一个正整数参数 $e_i$ —— 他的无经验值。罗素决定，无经验值为 $e$ 的探险家只能加入人数为 $e$ 或更多人的小组。

现在罗素需要弄清楚他能组建多少个小组。不一定要将每个探险家都编入小组：有些人可以留在营地。罗素对这次探险很担心，所以他请你帮忙。

## 说明/提示
在第一个示例中，我们可以组建三个小组。每个小组只有一名探险家。这是正确的，因为每个探险家的无经验值都等于 $1$，所以不小于他所在小组的人数。

在第二个示例中，我们可以组建两个小组。无经验值为 $1$、$2$ 和 $3$ 的探险家将组成第一组，另外两名无经验值为 $2$ 的探险家将组成第二组。

这个解决方案不是唯一的。例如，我们可以用三名无经验值为 $2$ 的探险家组成第一组，用一名无经验值为 $1$ 的探险家组成第二组。在这种情况下，无经验值为 $3$ 的年轻探险家将不被编入任何小组。

## 样例 #1
### 输入
```
2
3
1 1 1
5
2 3 1 2 2
```
### 输出
```
3
2
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要分为贪心和动态规划两种思路。贪心思路是按照探险家的无经验值从小到大处理，尽量让相同无经验值的探险家组成一组，剩余的与更大无经验值的探险家组合；动态规划思路则是设状态表示前 $i$ 个人最多能分的组数，通过考虑第 $i$ 个人是否单独分组得出状态转移方程。

贪心思路的难点在于证明按此方式分组能得到最优解；动态规划的难点在于准确得出状态转移方程以及处理多组数据时数组的清零方式，避免超时。

贪心思路相对更简洁直观，时间复杂度为 $O(n)$，动态规划思路代码相对复杂，时间复杂度同样为 $O(n)$，但贪心思路在理解和实现上更优。

### 所选的题解
- **作者：b6e0_ （5星）**
  - **关键亮点**：清晰阐述贪心思路，从单个数字分析入手，逐步推导整体贪心策略，代码简洁明了，还指出 memset 函数在本题中会超时的易错点，并给出正确做法。
  - **个人心得**：指出 memset 复杂度实际为 $O(n)$ 而非认为的 $O(1)$，在本题多组大数据情况下会导致 TLE。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int main()
{
    int t,n,i,le,ans;
    cin>>t;
    while(t--)
    {
        ans=le=0;
        cin>>n;
        int tot[n+10]={};
        for(i=0;i<n;i++)
        {
            cin>>a[i];
            tot[a[i]]++;
        }
        for(i=1;i<=n;i++)
        {
            ans+=(tot[i]+le)/i;
            le=(tot[i]+le)%i;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：用 tot 数组统计每个无经验值出现的次数，通过循环遍历无经验值，每次计算当前无经验值和上一轮剩余人数能组成的组数，并更新剩余人数，最后累加所有组数得到答案。

- **作者：oimaster （4星）**
  - **关键亮点**：以贪心思想为基础，详细分析样例，逐步展示解题思路，代码简洁易懂。
  - **核心代码**：
```c++
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int e[n+1];
        for(int i=1;i<=n;++i)
            cin>>e[i];
        int sum[n+1];
        for(int i=0;i<=n;++i)
            sum[i]=0;
        for(int i=1;i<=n;++i)
            ++sum[e[i]];
        int ans=0;
        int left=0;
        for(int i=1;i<=n;++i){
            ans+=(sum[i]+left)/i;
            left=(sum[i]+left)%i;
        }
        cout<<ans<<endl;
    }
}
```
  - **核心实现思想**：先统计每个无经验值的人数，然后按无经验值从小到大遍历，计算每组能形成的组数及剩余人数，累加组数得到最终答案。

- **作者：Into_qwq （4星）**
  - **关键亮点**：简洁地阐述贪心策略，利用 map 数据结构记录每个无经验值的人数，代码实现简洁高效。
  - **核心代码**：
```c++
#include<bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(register int i=l;i<=r;++i)
map <int,int> p;
inline void solve(int n){
    p.clear();
    int ans=0,people_left=0;
    rep(i,1,n){
        int x;
        cin>>x;
        ++p[x];
    }
    rep(i,1,n){
        ans+=(p[i]+people_left)/i;
        people_left=(p[i]+people_left)%i;
    }
    cout<<ans<<endl;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        solve(n);
    }
    return 0;
}
```
  - **核心实现思想**：通过 map 记录每个无经验值出现的次数，循环遍历无经验值，计算每组能形成的组数和剩余人数，累加组数得到结果。

### 最优关键思路或技巧
贪心思路中，按照无经验值从小到大处理，优先让相同无经验值的探险家组成一组，剩余的与更大无经验值的探险家组合，这种方式能保证组成的组数最多。同时，在处理多组数据时，注意数组清零方式，避免使用复杂度为 $O(n)$ 的 memset 函数导致超时。

### 可拓展之处
同类型题通常围绕如何根据给定条件合理分组或分配资源，以达到最优目标。类似算法套路是先分析局部最优情况，推导整体贪心策略，并证明其正确性。

### 洛谷推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过合理排序实现贪心策略，解决分配问题。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：利用贪心思想分析博弈过程，找到最优策略。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过推导排序条件，运用贪心算法解决双属性排序问题。 

---
处理用时：53.94秒