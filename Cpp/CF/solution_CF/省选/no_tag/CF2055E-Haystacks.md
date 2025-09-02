# Haystacks

## 题目描述

On the next new moon, the universe will reset, beginning with Florida. It's up to Florida Man to stop it, but he first needs to find an important item.There are $ n $ haystacks labelled from $ 1 $ to $ n $ , where haystack $ i $ contains $ a_i $ haybales. One of the haystacks has a needle hidden beneath it, but you do not know which one. Your task is to move the haybales so that each haystack is emptied at least once, allowing you to check if the needle is hidden under that particular haystack.

However, the process is not that simple. Once a haystack $ i $ is emptied for the first time, it will be assigned a height limit and can no longer contain more than $ b_i $ haybales. More formally, a move is described as follows:

- Choose two haystacks $ i $ and $ j $ . If haystack $ i $ has not been emptied before, or haystack $ i $ contains strictly less than $ b_i $ haybales, you may move exactly $ 1 $ haybale from haystack $ j $ to haystack $ i $ .

Note: Before a haystack is emptied, it has no height limit, and you can move as many haybales as you want onto that haystack.

Compute the minimum number of moves required to ensure that each haystack is emptied at least once, or report that it is impossible.

## 说明/提示

In the first test case, we can do the following sequence of moves:

- Move $ 3 $ haybales from haystack $ 1 $ to haystack $ 2 $ . Haystack $ 1 $ is now emptied, and is assigned a height limit of $ 5 $ .
- Move $ 5 $ haybales from haystack $ 2 $ to haystack $ 1 $ . Haystack $ 2 $ is now emptied, and is assigned a height limit of $ 4 $ .

The above sequence requires $ 3 + 5 = 8 $ moves. It is not possible to use less than $ 8 $ moves as the following sequence of moves is invalid:

- Move $ 2 $ haybales from haystack $ 2 $ to haystack $ 1 $ . Haystack $ 2 $ is now emptied, and is assigned a height limit of $ 4 $ .
- Move $ 4 $ haybales from haystack $ 1 $ to haystack $ 2 $ . Haystack $ 1 $ now has $ 1 $ haybale, while haystack $ 2 $ has $ 4 $ haybales.
- Haystack $ 1 $ cannot be emptied as haystack $ 2 $ is already at its height limit of $ 4 $ , so no more haybales can be moved from haystack $ 1 $ to haystack $ 2 $ .

In the second test case, the task is impossible. This is because the height limits of both haystacks are too small that once one of the haystacks is emptied, the other haystack cannot be emptied due to the small height limits.

In the third test case, the following sequence of moves can be shown to be optimal:

- Move $ 1 $ haybale from haystack $ 1 $ to haystack $ 3 $ . Haystack $ 1 $ is now emptied, and is assigned a height limit of $ 3 $ .
- Move $ 3 $ haybales from haystack $ 2 $ to haystack $ 1 $ .
- Move $ 1 $ haybale from haystack $ 2 $ to haystack $ 3 $ . Haystack $ 2 $ is now emptied and is assigned a height limit of $ 3 $ .
- Move $ 3 $ haybales from haystack $ 3 $ to haystack $ 2 $ . Haystack $ 3 $ is now emptied, and is assigned a height limit of $ 1 $ .

The above sequence requires $ 1 + 3 + 1 + 3 = 8 $ moves.

## 样例 #1

### 输入

```
7
2
3 5
2 4
2
10 1
1 10
3
1 3
4 3
1 1
3
5 4
2 4
1 10
6
2 1
3 3
5 4
1 5
1 6
1 8
5
3 2
1 2
1 1
1 3
6 5
2
5 10
7 12```

### 输出

```
8
-1
8
9
14
15
19```

# 题解

## 作者：Albert_Wei (赞：17)

## $\textup{\textbf{Part 1}}$
考虑 $b_i = \infty$ 的情况。我们发现，除了第一个清空的草垛，其他草垛中的草捆都可以放在比它早清空的草垛里，从而只需移动一次，而第一个草垛中的草捆无论如何都得放在比它后清空的草垛里，必须移动两次，所以答案为 $\sum \limits_{i = 1} ^ n a_i + \min \limits_{i = 1} ^ n a_i$。
## $\textup{\textbf{Part 2}}$
考虑草垛清空顺序确定的情况（不妨设为从 $1$ 到 $n$ 依次清空），我们发现相比 $b_i = \infty$ 的情况，差别是每一个草垛都有可能必须把草捆放在比它晚清空的草垛中。具体来说，是第 $i$ 个草垛清空时，有 $c_i = \max(0, \sum \limits_{j = 1} ^ i a_j - \sum\limits_{j = 1} ^ {i - 1} b_j)$ 个草垛必须放在比它晚清空的草垛中，所以答案至少为 $\sum \limits_{i = 1} ^ n a_i + \max \limits_{i = 1} ^ n c_i$，且必须保证 $c_n = 0$ （否则多出来的草捆就没地方放了）。又因为我们可以贪心地尽量把这一次清空中的草捆往已经清空的草垛中的空位丢，剩下的放到最晚清空的草垛里，这样可以保证所有草捆只被移动不超过两次，而且被扔到第 $n$ 堆的草捆（即移动两次的草捆）不超过 $\max \limits_{i = 1} ^ n c_i$ 个，所以答案必能取到 $\sum \limits_{i = 1} ^ n a_i + \max \limits_{i = 1} ^ n c_i$。
## $\textup{\textbf{Part 3}}$
考虑去掉 $c_n = 0$ 限制的情况。由于 $n \le 5 \times 10 ^ 5$，考虑使用调整法寻找贪心策略。首先，由于 $\sum \limits_{j = 1} ^ i a_j - \sum\limits_{j = 1} ^ {i - 1} b_j = \sum\limits_{j = 1} ^ {i - 1} (a_j - b_j) + a_i$，我们将 $a_i - b_i \le 0$ 的草垛先清空显然不劣。其次，交换两个草垛 $y, x$ 需要保证 $\max(a_x, a_x - b_x + a_y) \le \max(a_y, a_y - b_y + a_x)$。
- 对于 $a_i - b_i \le 0$ 的部分，有 $a_x - b_x + a_y \le a_y$，所以只需保证 $a_x \le a_y$，按照 $a$ 从小到大排序即可。
- 对于 $a_i - b_i > 0$ 的部分，有 $a_x < a_y - b_y + a_x$，所以只需保证 $a_x - b_x + a_y \le a_y - b_y + a_x$，即 $b_x \ge b_y$，按照 $b$ 从大到小排序即可。
## $\textup{\textbf{Part 4}}$
考虑 $c_n = 0$ 的限制，我们发现它要求 $\sum \limits_{i = 1} ^ n (a_j - b_j) + b_n \le 0$，即 $b_n \le \sum \limits_{i = 1} ^ n (b_j - a_j)$，可以预处理出有哪些草垛满足。于是我们只需要考虑去掉一个草垛后对 $\sum\limits_{j = 1} ^ {i - 1} (a_j - b_j) + a_i$ 的影响。这只是对该草垛所在位置之后的值做一个后缀减，所以维护前、后缀最大值即可。总复杂度 $\mathcal{O}(n \log n)$，瓶颈在排序。

核心代码：

```cpp
n = read(), pos.clear();
sum = tot = 0, pmx[0] = smx[n + 1] = -1e18;
for (int i = 1; i <= n; i ++) {
  t[i].a = read(), t[i].b = read();
  t[i].dlt = t[i].a - t[i].b, sum -= t[i].dlt, tot += t[i].a;
}
sort(t + 1, t + n + 1, [&](Thing x, Thing y) {
  if (x.dlt <= 0 && y.dlt > 0) return true;
  if (x.dlt > 0 && y.dlt <= 0) return false;
  if (x.dlt <= 0 && y.dlt <= 0) return x.a < y.a;
  return x.b > y.b;
});
for (int i = 1; i <= n; i ++)
  if (t[i].b <= sum) pos.push_back(i);
if (!pos.size()) return puts("-1"), void();
for (int i = 1; i <= n; i ++) {
  val[i] = val[i - 1] + t[i].a - t[i - 1].b;
  pmx[i] = max(pmx[i - 1], val[i]);
}
for (int i = n; i >= 1; i --) smx[i] = max(smx[i + 1], val[i]);
LL ans = 1e18;
for (int i : pos) Fmin(ans, max(pmx[i - 1], smx[i + 1] - t[i].a + t[i].b));
cout << max(0ll, ans) + tot << '\n';
```

---

## 作者：phigy (赞：1)

## 前言

本文比较详细阐述了思路。

## 正文

很自然的，只有在清空一个堆的时候我们需要将这个堆上的东西转移出去，同时我们没有理由去关注同一个堆被清空的第二次的时间，因此我们考虑固定所有堆第一次被清空的顺序 $p_1,p_2\dots ,p_n$。

对于 $p_n$ 之外的堆，在清空时由于可以转移到 $p_n$ 上，因此一定能清空，所以此时无解当且仅当 $p_n$ 无法清空，也就是 $\sum_{i=1}^{n-1}b_{p_i}<\sum_{i=1}^n a_i$。

对于所有堆，明显应当优先往清空过的堆转移，而只能往没清空的堆转移时，容易发现应当优先往 $p_n$ 转移，因此答案就是往 $p_n$ 的额外转移个数加上必须被清空的 $\sum_{i=1}^na_i$。

对于一个排列 $p$ 直接计算答案是不好理解的，因为需要不断的对 $0$ 取 $\max$，考虑钦定有且仅有 $x$ 个额外转移，即可拆除限制，将问题转化为初始值 $x$，有当值 $\ge a_i$ 时可以将值 $-a_i+b_i$ 的操作，问能不能进行所有操作。

这是经典比较贪心问题，最优的顺序一定是先按 $a_i$ 升序做 $a_i\leq b_i$ 的操作，再按 $b_i$ 降序做 $a_i>b_i$ 操作，那么此时我们又可以解除上面添加的钦定了，排序后可以直接得到答案是变化曲线的初始值减去最低值。

考虑 $p_n$ 有额外限制，我们枚举 $p_n$ 是什么，那么此时对于其余的操作排序是不变的，因此我们预处理前后缀的末尾值与最小值，重新合并计算即可，复杂度 $O(n\log n)$。


```cpp
#include <bits/stdc++.h>

#define int long long
#define pii pair<int,int>
using namespace std;

const int REN=500000,MAXN=REN+5;
const int inf=0x3f3f3f3f3f3f3f3f;
int n;
vector<pii>vec;
bool cmp(pii A,pii B)
{
    if(A.first<=A.second&&B.first<=B.second)
    {
        return A.first<B.first;
    }
    else if(A.first<=A.second&&B.first>B.second)
    {
        return 1;
    }
    else if(A.first>A.second&&B.first<=B.second)
    {
        return 0;
    }
    else 
    {
        return A.second>B.second;
    }
}
int pre[MAXN],premn[MAXN],suf[MAXN],sufmn[MAXN];
int get(int x)
{
    return -min({premn[x-1],pre[x-1]+sufmn[x+1],pre[x-1]+suf[x+1]-vec[x].first});
}
int res[MAXN],cnt;
void solve()
{
    int i,j,k;
    int suma=0,sumb=0;
    cin>>n;
    vec.clear();
    vec.emplace_back(0,0);
    for(i=0;i<=n+1;i++) {pre[i]=suf[i]=premn[i]=sufmn[i]=0;}
    for(i=1;i<=n;i++)
    {
        int a,b;
        cin>>a>>b;
        suma+=a;sumb+=b;
        vec.emplace_back(a,b);
    }
    bool fl=0;
    for(i=1;i<=n;i++)
    {
        int b=vec[i].second;
        if(suma<=sumb-b) {fl=1;}
    }
    if(!fl) {cout<<"-1\n";return ;}
    sort(vec.begin(),vec.end(),cmp);
    premn[1]=-vec[1].first;
    pre[1]=-vec[1].first+vec[1].second;
    sufmn[n]=-vec[n].first;
    suf[n]=-vec[n].first+vec[n].second;
    for(i=2;i<=n;i++)
    {
        premn[i]=min(premn[i-1],pre[i-1]-vec[i].first);
        pre[i]=pre[i-1]-vec[i].first+vec[i].second;
    }
    for(i=n-1;i>=1;i--)
    {
        sufmn[i]=min(sufmn[i+1]-vec[i].first+vec[i].second,-vec[i].first);
        suf[i]=suf[i+1]-vec[i].first+vec[i].second;
    }
    int ans=inf;
    for(i=1;i<=n;i++)
    {
        int b=vec[i].second;
        if(suma<=sumb-b) 
        {
            ans=min(ans,get(i));
        }
    }
    cout<<ans+suma<<'\n';
}
signed main()
{
    int i,j,k;
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int _;cin>>_;
    while(_--) {solve();}
    return 0;
}
```


## 后话

由于曾以为不用对 `premn` 做任何额外的清空所以把错的数据套出来了。


```
6
40818611 910006299 
305061955 380290262
430057402 705179172
619226853 751473692
666694202 203954313
878140977 49096262
```

---

## 作者：yvbf (赞：1)

内嵌b站视频分p参数不生效，贴一下直接的链接

[题解](https://m.bilibili.com/video/BV12scGeME5a?p=2)

---

