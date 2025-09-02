# 题目信息

# Leaving Auction

## 题目描述

There are $ n $ people taking part in auction today. The rules of auction are classical. There were $ n $ bids made, though it's not guaranteed they were from different people. It might happen that some people made no bids at all.

Each bid is define by two integers $ (a_{i},b_{i}) $ , where $ a_{i} $ is the index of the person, who made this bid and $ b_{i} $ is its size. Bids are given in chronological order, meaning $ b_{i}&lt;b_{i+1} $ for all $ i&lt;n $ . Moreover, participant never makes two bids in a row (no one updates his own bid), i.e. $ a_{i}≠a_{i+1} $ for all $ i&lt;n $ .

Now you are curious with the following question: who (and which bid) will win the auction if some participants were absent? Consider that if someone was absent, all his bids are just removed and no new bids are added.

Note, that if during this imaginary exclusion of some participants it happens that some of the remaining participants makes a bid twice (or more times) in a row, only first of these bids is counted. For better understanding take a look at the samples.

You have several questions in your mind, compute the answer for each of them.

## 说明/提示

Consider the first sample:

- In the first question participant number $ 3 $ is absent so the sequence of bids looks as follows: 
  1. $ 1 $ $ 10 $
  2. $ 2 $ $ 100 $
  3. $ 1 $ $ 10000 $
  4. $ 2 $ $ 100000 $
  
   Participant number $ 2 $ wins with the bid $ 100000 $ .
- In the second question participants $ 2 $ and $ 3 $ are absent, so the sequence of bids looks: 
  1. $ 1 $ $ 10 $
  2. $ 1 $ $ 10000 $
  
   The winner is, of course, participant number $ 1 $ but the winning bid is $ 10 $ instead of $ 10000 $ as no one will ever increase his own bid (in this problem).
- In the third question participants $ 1 $ and $ 2 $ are absent and the sequence is: 
  1. $ 3 $ $ 1000 $
  2. $ 3 $ $ 1000000 $
  
   The winner is participant $ 3 $ with the bid $ 1000 $ .

## 样例 #1

### 输入

```
6
1 10
2 100
3 1000
1 10000
2 100000
3 1000000
3
1 3
2 2 3
2 1 2
```

### 输出

```
2 100000
1 10
3 1000
```

## 样例 #2

### 输入

```
3
1 10
2 100
1 1000
2
2 1 2
2 2 3
```

### 输出

```
0 0
1 10
```

# AI分析结果

### 题目内容
# 离开拍卖会

## 题目描述
今天有 $n$ 人参加拍卖会。拍卖规则是经典的。共进行了 $n$ 次出价，但不能保证这些出价来自不同的人。可能会出现有些人根本没有出价的情况。

每次出价由两个整数 $(a_{i},b_{i})$ 定义，其中 $a_{i}$ 是出价人的索引，$b_{i}$ 是出价的金额。出价按时间顺序给出，这意味着对于所有 $i < n$，都有 $b_{i} < b_{i + 1}$。此外，参与者不会连续两次出价（没有人会更新自己的出价），即对于所有 $i < n$，都有 $a_{i} \neq a_{i + 1}$。

现在你对以下问题感到好奇：如果一些参与者缺席，谁（以及哪次出价）将赢得拍卖？ 假设如果某人缺席，他的所有出价将被移除，并且不会添加新的出价。

请注意，如果在排除某些参与者的过程中，发现剩余的某些参与者连续出价两次（或更多次），则只计算这些出价中的第一次。为了更好地理解，请查看示例。

你心中有几个问题，请为每个问题计算答案。

## 说明/提示
考虑第一个示例：
- 在第一个问题中，3 号参与者缺席，所以出价序列如下：
  1. $1$ $10$
  2. $2$ $100$
  3. $1$ $10000$
  4. $2$ $100000$
  
  2 号参与者以 $100000$ 的出价赢得拍卖。
- 在第二个问题中，2 号和 3 号参与者缺席，所以出价序列如下：
  1. $1$ $10$
  2. $1$ $10000$
  
  获胜者当然是 1 号参与者，但获胜出价是 $10$ 而不是 $10000$，因为在这个问题中没有人会提高自己的出价。
- 在第三个问题中，1 号和 2 号参与者缺席，序列如下：
  1. $3$ $1000$
  2. $3$ $1000000$
  
  获胜者是 3 号参与者，出价为 $1000$。

## 样例 #1
### 输入
```
6
1 10
2 100
3 1000
1 10000
2 100000
3 1000000
3
1 3
2 2 3
2 1 2
```
### 输出
```
2 100000
1 10
3 1000
```

## 样例 #2
### 输入
```
3
1 10
2 100
1 1000
2
2 1 2
2 2 3
```
### 输出
```
0 0
1 10
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕如何高效处理每次询问中移除部分参与者后确定获胜者及其出价。主要难点在于处理出价的顺序限制以及在不同参与者缺席情况下准确找到获胜出价。

各题解思路和要点如下：
 - **封禁用户**：将每人的竞标结果按人分类放入桶中，对每个桶按最高价排序。每次询问时遍历找到权值最高（即最高价）的桶确定获胜者，再找次高桶，通过二分在最高桶里找比次高桶权值更高的竞标作为获胜出价。
 - **泠小毒**：先对出价者按其最高出价排序，每次询问从排序后的出价者中扫出未被排除且出价最高的作为获胜者，再通过二分在获胜者出价序列中找比第二名最高出价高的第一个出价作为获胜价格。
 - **mulberror**：利用set维护出价者及其最高出价，按最高出价从大到小排序。每次询问从set中删除缺席者，根据set剩余大小分类讨论，若大小为0输出“0 0”，为1则输出唯一买家及其最低出价，大于1则找最高和次高出价者，通过二分在最高出价者出价序列中找比次高出价者最高出价高的出价作为获胜价格。
 - **柠檬草苏打水**：预处理每个买家出价序列、最高和最低出价，用set维护出价者及其最高出价并按最高出价从大到小排序。每次询问从set删除缺席者，按set大小分类讨论确定获胜者和价格，与mulberror思路类似，最后要把移除的人重新插入set。
 - **ran_qwq**：用set维护每个人最后位置确定获胜者，通过预处理后缀种数并二分查找确定获胜出价。

### 所选的题解
 - **封禁用户（4星）**
   - **关键亮点**：通过桶分类出价结果，利用排序和二分查找高效确定获胜者和价格，思路清晰，代码实现较为完整。
   - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lld;
const int N = 201000; 
struct Node {
    int value, pos;
    bool operator<(const Node &tmp) const{
        if (value!= tmp.value) return value > tmp.value;
        else return pos > tmp.pos;
    };
    Node(int x, int y):value(x), pos(y){};
    Node(){};
}node[N];
vector<int> bucket[N];
vector<Node> people(N);
int main() {
    int n, q;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int pid, bid;
        scanf("%d%d", &pid, &bid);
        people[pid] = Node(bid, pid); // bigger bid
        bucket[pid].push_back(bid);
    }  
    sort(people.begin(), people.begin() + n + 1);
    cin >> q;
    while (q--) {
        int k;
        scanf("%d", &k);
        map<int, int> h;
        for (int i = 0; i < k; ++i) {
            int tmp;
            scanf("%d", &tmp);
            h[tmp] = 1;
        }
        int ok = 0;
        for (int i = 0; i < n; ++i) {
            if (people[i].pos == 0) break;
            if (h.find(people[i].pos) == h.end()) { // find top
                int topId = people[i].pos;
                int secondId = 0;
                for (int j = i + 1; j < n; ++j) {
                    if (h.find(people[j].pos) == h.end()) { // find second top
                        secondId = people[j].pos;
                        break;
                    }
                }
                if (secondId == 0) cout << topId << " " << bucket[topId].front() << endl;// not find second top
                else cout << topId << " " << *upper_bound(bucket[topId].begin(), bucket[topId].end(), bucket[secondId].back()) << endl;
                ok = 1;
                break;
            }
        }
        if (!ok) cout << "0 0" << endl;
    }   
	return 0;
}
```
 - **泠小毒（4星）**
   - **关键亮点**：通过排序出价者简化获胜者查找过程，利用二分查找获胜价格，代码简洁明了。
   - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int num;}b[200010];
vector<int>a[200010];
int n,m,q,x,y,lim[200010],ll[200010];
int cmp(node xx,node yy){return a[xx.num][a[xx.num].size()-1]<a[yy.num][a[yy.num].size()-1];}
int find(int k)
{
    for(int i=k;i>=1;i--)if(!lim[b[i].num])return i;
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n;i++)a[i].push_back(0);
    for(int i=1;i<=n;i++)scanf("%d%d",&x,&y),a[x].push_back(y),b[i].num=i;
    sort(b+1,b+1+n,cmp),scanf("%d",&m);
    while(m--)
    {
        scanf("%d",&q);
        for(int i=1;i<=q;i++)scanf("%d",&ll[i]),lim[ll[i]]=1;
        x=find(n),lim[b[x].num]=1,y=find(x-1),lim[b[x].num]=0;
        if(!a[b[x].num][a[b[x].num].size()-1])puts("0 0");
        else printf("%d %d\n",b[x].num,*upper_bound(a[b[x].num].begin(),a[b[x].num].end(),a[b[y].num][a[b[y].num].size()-1]));
        for(int i=1;i<=q;i++)lim[ll[i]]=0;
    }
    return 0;
}
```
 - **柠檬草苏打水（4星）**
   - **关键亮点**：利用set维护出价者及其最高出价，按最高出价排序，通过二分查找获胜价格，思路清晰，代码实现逻辑明确。
   - **核心代码片段**：
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;
vector<int> G[200005];
int n, a, b;
int maxn[200005];
int minn[200005];
int d[200005];
int max(int a, int b)
{
    return a > b? a : b;
}
int min(int a, int b)
{
    return a < b? a : b;
}
struct node
{
    int index;
    int maxn;
};
struct cmp
{
    bool operator ()(const node & a, const node & b)const
    {
        return a.maxn > b.maxn;
    }
};
int main()
{
    cin >> n;
    memset(minn, 0x3f, sizeof(minn));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        maxn[a] = max(maxn[a], b);
        minn[a] = min(minn[a], b);
    }
    set<node, cmp> s;
    for (int i = 1; i <= n; i++)
    {
        if (G[i].size())
        {
            node tmp;
            tmp.index = i;
            tmp.maxn = maxn[i];
            s.insert(tmp);
        }
    }
    int T, x;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &x);
        for (int j = 0; j < x; j++)
        {
            scanf("%d", &d[j]);
            node t;
            t.index = d[j];
            t.maxn = maxn[d[j]];
            s.erase(t);
        }
        if (s.size() == 0)
        {
            puts("0 0");
        }
        else if (s.size() == 1)
        {
            printf("%d %d\n", s.begin()->index, minn[s.begin()->index]);
        }
        else
        {
            set<node, cmp>::iterator t = s.begin();
            node y;
            y.index = t->index;
            y.maxn = t->maxn;
            s.erase(s.begin());
            set<node, cmp>::iterator t2 = s.begin();
            vector<int>::iterator it;
            it = upper_bound(G[t->index].begin(), G[t->index].end(), t2->maxn);
            if (it!= G[t->index].end())
            {
                printf("%d %d\n", y.index, *it);
            }
            else
            {
                puts("0 0");
            }
            s.insert(y);
        }
        for (int j = 0; j < x; j++)
        {
            node t;
            t.index = d[j];
            t.maxn = maxn[d[j]];
            if (G[t.index].size())
                s.insert(t);
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **数据结构选择**：使用vector保存每个参与者的出价序列，方便对出价进行管理和查找。利用set或排序后的数组来维护参与者及其最高出价，以便快速确定获胜者。
2. **二分查找**：在确定获胜价格时，由于出价序列是有序的，通过二分查找可以高效地在获胜者的出价序列中找到比第二名最高出价高的第一个出价，将时间复杂度从线性降低到对数级别。

### 拓展思路
同类型题目可能会改变出价规则、参与人数限制或查询方式等。类似算法套路主要围绕如何高效处理数据的动态变化（如参与者的加入或退出）以及在有序数据中快速查找特定值。例如，在其他拍卖场景问题中，可能会涉及更复杂的价格调整规则，或者在处理大规模数据时需要进一步优化数据结构和算法以满足时间和空间限制。

### 洛谷相似题目推荐
1. **P1083 [NOIP2012 提高组] 借教室**：涉及到对资源分配的动态查询和处理，与本题处理不同条件下的结果类似，需要考虑时间和资源的限制。
2. **P2672 [NOIP2015 提高组] 推销员**：通过对数据的排序和动态处理，找到满足一定条件下的最优解，和本题确定获胜者及价格的思路有相似之处。
3. **P3398 仓鼠找sugar**：在树上进行动态查询和路径处理，与本题处理不同询问下的结果类似，需要对数据结构和算法进行合理运用。

### 个人心得摘录
 - **封禁用户**：未提及具体调试或顿悟内容，但整体题解思路清晰，对题目理解透彻，从问题分析到复杂度分析都较为详细。
 - **泠小毒**：提醒不要在循环里使用memset，因为其复杂度是n，可能导致程序运行时间过长，这是在优化代码时需要注意的细节。
 - **柠檬草苏打水**：提到开始在set的每个节点中保存相应买家的出价序列导致TLE，意识到数据结构设计不合理，这表明在解决问题时需要仔细考虑数据结构的选择对时间复杂度的影响。 

---
处理用时：118.91秒