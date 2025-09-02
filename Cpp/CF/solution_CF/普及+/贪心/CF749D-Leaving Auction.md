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

# 题解

## 作者：封禁用户 (赞：4)

# 0.前言
题目链接：[http://codeforces.com/contest/749/problem/D](http://codeforces.com/contest/749/problem/D)
 
题目大意：
$n$ 个人在竞标物品，轮流出价，最终价高者得。
现在已知整个竞标过程总共有 $n$ 次出价，用 $(a[i],b[i])$ 来表示第 $i$ 次竞标中，第 $a[i]$ 个人，出价为 $b[i]$。
 
$q$ 个询问，每个询问首先是 $k$，表示假如 $k$ 个人没来，接下来是 $k$ 个整数，表示 $k$ 个没来人的序号。对于每个询问，输出最终的竞标结果。

# 1.关于样例
```
 **input**
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
 **output**
 2 100000
 1 10
 3 1000
```
样例解释：

当 3 号没来参加时，竞标过程是：

```
1 10
2 100
1 10 000
2 100 000
```

2 号出价 $100000$ 竞标成功；

---
当 2,3 号没来参加时，竞标过程是
```
1 10
1 10 000
```

1 号竞标成功，但是因为 1 号不会出价超过自己，所以最终是出价 $10$ 竞标成功；

---
当 1,2 号没来参加时，最终 $1000$ 竞标成功。

---

# 2.解析

 - 整体思维
 
主要问题：如何快速求出竞标的结果。

$q$ 的数量较大，能够接受的时间复杂度在 $O(\log N)$。

从题目中显然看出，越往后，出价会越高，通过最后面就可以知道最高价。

 - 询问的影响&解决方法：

**影响：**

1. 某些人不来，其竞标的价格无效，本来可能是他的最高价，会顺延下一个人；
2. 假设某个人出了最高价，但是因为某些人没来，导致他的次高价也是最高的，这时候会选择次高价。

**办法：**

根据竞标结果，按大小放到一个桶中。其中每个桶依照最高价作为权值进行 sort（排序）；

每次找有效的和权值最高的桶，就中标；

再找次高的桶，在最高的桶里面选择一个比次高桶的权值更高的竞标作为低价。

 - 复杂度分析：

若 $N$ 为竞标数量，然后将每人的竞标结果分类，复杂度为 $O(N)$。

若 $M$ 为桶的数量，每个桶的排序，复杂度为 $O(M\log M)$。        
用遍历操作找到权值最高的桶。

继续用遍历操作，找权值最高的桶和找权值次高的桶。

在权值最高的桶里面找一个竞标，比次高桶的权值更高的，用二分的复杂度是 $O(\log N)$，次数有 $O(N)$ 次，总复杂度是 $O(N\log N)$。
 
# 3.code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lld;
const int N = 201000; 
struct Node {
    int value, pos;
    bool operator<(const Node &tmp) const{
        if (value != tmp.value) return value > tmp.value;
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
//by guyugeng2007
```
只写了 ~~非常简单~~ 的英文注释，应该能看懂吧。

# 4.发点牢骚
关注关注再关注！[我的主页qwq](https://www.luogu.com.cn/user/554872)

没记错的话这是我的第八篇题解，预祝各位学生们在新学期拿到好成绩，考 CSP 和 NOIP 的都拿一等奖！

---

## 作者：泠小毒 (赞：2)

# T4-Leaving Auction
一场拍卖会，共n个买家。这些买家共出价n次，有的买家可能一次都没有出价。

每次出价用（ai,bi）表示，ai为此次出价人的编号，bi为价格。

出价严格递增（bi<bi+1）并且没有玩家在一轮竞拍中在没有其他竞争对手的情况下自动增加自己的出价（ai!=ai+1）。

现在给定q次查询，每次去掉一些出价者及其所有出价，问最后谁是赢家并且他以什么价格赢得拍卖品。
## 广告插入
在我的博客里看题解使用效果更佳哦QwQ

[慕容琳的后花园](https://muronglin.top/hgoi-20190508/)
## 解法
首先第一小问，求谁是赢家，可以先排序，由于k的和限定在20w，所以每次从排名上扫来找到赢家

对于第二小问，求赢家出的价格，可以换一种思路，找到比第二名的最高出价高的第一个出价，就是答案

这个就很好维护了，找到第二名的复杂度也是k的和，然后二分找到比他大的第一个出价就可以了

总复杂度nlogn，tips：memset的复杂度是n（emmmm），所以不要在循环里加上memset，~~怎么死的都不知道~~
## ac代码
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

---

## 作者：mulberror (赞：2)

一定是没有去掉的第二大的。  
那么就set+二分就好了  
```cpp
#include <bits/stdc++.h>
#define rep(i, s, t) for (int i = (s); i <= (t); i ++) 
using namespace std;
template <typename T> inline void read(T &x) {
	x = 0; T fl = 1; char ch = 0; 
	for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') fl = -1; 
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	x *= fl; 
}
template <typename T, typename... Args> inline void read(T& x, Args&... args) {
    read(x); read(args...); 
}
const int N = 2e6 + 5; 
vector<int> a[N];
int b[N], d[N], vis[N]; 
set<pair<int, int> > s; 
int n, q, k; 
int main() {
	read(n); rep(i, 1, n) { int x, y; read(x, y); a[x].push_back(y); vis[x] = 1; b[x] = y; } 
	rep(i, 1, n) if (vis[i]) s.insert(make_pair(b[i], i));
	read(q); 
	rep (_t, 1, q) {
		read(k); rep(i, 1, k) { read(d[i]); if (vis[d[i]]) s.erase(make_pair(b[d[i]], d[i])); }
		if (s.size() == 0) printf("0 0\n"); 
		else if (s.size() == 1) printf("%d %d\n", s.begin()->second, *a[s.begin()->second].begin());
		else {
			auto i1 = s.end(), i2 = s.end(); i1 --; i1 --; i2 --; 
			int num1 = i1->first, num2 = i2->second; 
			auto it = upper_bound(a[num2].begin(), a[num2].end(), num1);
			printf("%d %d\n", num2, *it);
		}
		rep(i, 1, k) if (vis[d[i]]) s.insert(make_pair(b[d[i]], d[i]));
	}
	return 
```

---

## 作者：柠檬草苏打水 (赞：1)

题目链接：

http://codeforces.com/problemset/problem/749/D

题目大意：

一场拍卖会，共n个买家。这些买家共出价n次，有的买家可能一次都没有出价。每次出价用（ai,bi）表示，ai为此次出价人的编号，bi为价格。出价严格递增（bi<bi+1）并且没有玩家在一轮竞拍中在没有其他竞争对手的情况下自动增加自己的出价（ai!=ai+1）。现在给定q次查询，每次去掉一些出价者及其所有出价，问最后谁是赢家并且他以什么价格赢得拍卖品。

解题思路：

首先预处理所有的出价，保存每个买家的出价序列，最高出价和最低出价。然后维护一个set。其中保存出价者id和他的出价序列中的最高出价maxn，整个set按照maxn从大到小的顺序排序。对于每次查询，从set中删掉出局的人，如果此时set大小为0，输出“0 0”；大小为1，则只有一个买家，他赢得了拍卖品且价格为他的所有出价中的最小值；否则找maxn最高的人和第二高的人。最终的价格应该是在maxn最高的人的出价序列中比maxn第二高的人的最高出价高一点点的值。考虑到是有序的，二分即可。之后不要忘了把之前剔除掉的人再insert回来。
开始时我在set的每个节点中保存了相应买家的出价序列，结果T了很多次，真是被自己蠢哭了......

Code：
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
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
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
            if (it != G[t->index].end())
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

---

## 作者：ran_qwq (赞：0)

先考虑第一问，就是剩下的人中最后一次出价最后的那个人。具体地，用个 set 维护每个人最后位置，询问时把不考虑的人删掉，询问结束后加回来。

再考虑第二问，第一问中最后的人 $x$ 最后的出价会形成连续段，我们要找连续段的段首。可以先找一个位置 $p$，使得剩下的人出现两次，然后 $p$ 后面 $x$ 的第一次出价就是答案。

问题是如何找这个 $p$。考虑先预处理后缀的种数 $c_p$，询问时二分 $p$。如果 $c_p$ 减去后面不考虑的人的种数 $>1$ 则往右找，否则往左找。

注意特判没人的情况。

```cpp
int n,m,x,a[N],b[N],c[N],d[N],ps[N],rps[N],vs[N]; set<int> st,ss[N];
int chk(int y) {
	int ct=c[y];
	for(int i=1;i<=x;i++) ct-=ps[d[i]]>=y;
	return ct>1;
}
void QwQ() {
	n=rd();
	for(int i=1;i<=n;i++) a[i]=rd(),b[i]=rd(),ss[a[i]].insert(i);
	for(int i=n;i;i--)
		if(vs[a[i]]) c[i]=c[i+1];
		else c[i]=c[i+1]+1,vs[a[i]]=1,st.insert(ps[a[i]]=i),rps[i]=a[i];
	m=rd();
	for(;m--;) {
		x=rd(); int ct=0;
		for(int i=1;i<=x;i++) d[i]=rd(),ct+=vs[d[i]];
		if(ct==c[1]) puts("0 0");
		else {
			for(int i=1;i<=x;i++) st.erase(ps[d[i]]);
			int rs=0,p; wr(p=rps[*st.rbegin()]," ");
			for(int l=1,r=*st.rbegin(),md;l<=r;) chk(md=l+r>>1)?l=(rs=md)+1:r=md-1;
			wr(b[*ss[p].ub(rs)],"\n");
			for(int i=1;i<=x;i++) st.insert(ps[d[i]]);
		}
	}
}
```

---

