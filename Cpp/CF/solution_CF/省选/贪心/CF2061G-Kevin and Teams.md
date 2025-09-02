# Kevin and Teams

## 题目描述

这是一道交互题。

Kevin 有 $n$ 个同学，编号为 $1, 2, \ldots, n$。他们之间可能是朋友，也可能不是朋友。

Kevin 想要选出 $2k$ 个同学组成 $k$ 支队伍，每支队伍恰好包含 $2$ 人。每个同学最多只能属于一支队伍。

设第 $i$ 支队伍中的两人为 $u_i$ 和 $v_i$。为了避免组队过程中潜在的冲突，队伍成员必须满足以下两个条件之一：

- 对于所有 $i$（$1 \leq i \leq k$），同学 $u_i$ 和 $v_i$ 是朋友。
- 对于所有 $i$（$1 \leq i \leq k$），同学 $u_i$ 和 $v_i$ 不是朋友。

Kevin 想要确定最大的 $k$，使得无论这 $n$ 个人之间的朋友关系如何，他总能找到 $2k$ 人组成队伍。之后，他需要组成这 $k$ 支队伍。但询问两个同学是否是朋友很尴尬，因此 Kevin 希望在使用不超过 $n$ 次询问的情况下达成目标。

交互器是自适应的。这意味着同学之间的隐藏关系在交互前并不固定，并且会在交互过程中改变。

## 说明/提示

第一个测试用例：

Kevin 声称无论 3 人之间的朋友关系如何，他总能组成 1 支队伍。

Kevin 询问同学 1 和 2 是否是朋友。裁判回答他们是朋友。

Kevin 回答他可以组成由同学 1 和 2 组成的队伍。

第二个测试用例：

Kevin 声称无论 5 人之间的朋友关系如何，他总能组成 2 支队伍。

Kevin 询问了同学 $(1, 2)$、$(3, 4)$、$(3, 5)$、$(1, 3)$、$(2, 4)$ 之间的关系。裁判依次回答 $1, 0, 1, 0, 0$。

Kevin 回答他可以组成两支队伍 $(1, 2)$ 和 $(3, 5)$。

也可以组成两支队伍 $(1, 3)$ 和 $(2, 4)$，因为他们都彼此不是朋友。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3


1

5


1

0

1

0

0```

### 输出

```
1
? 1 2

! 1 2

2
? 1 2

? 3 4

? 3 5

? 1 3

? 2 4

! 1 2 3 5```

# 题解

## 作者：_abcd_ (赞：2)

## [[CF2061G] Kevin and Teams](https://codeforces.com/contest/2061/problem/G)

考虑一种构造：将 $ 2/3 $ 的点两两连边，剩下的点都不连，那么最多有 $ \left\lfloor \frac{n+1}{3} \right\rfloor $ 组匹配。

考虑询问方案：维护一条同色链，令链的末尾的点为 $ a $，倒数第二个点为 $ b $，每次询问新点 $ c $ 和 $ a $ 的关系。如果和这条链同色，则将新点加入到链的末尾，否则将 $ a,c $ 作为一种颜色的匹配，$ b,c $ 作为另一种颜色的匹配，然后将 $ b,c $ 从链末删去。最后会剩下一条链，两两匹配即可。不难证明最后链的颜色的匹配数量至少为 $ \left\lfloor \frac{n+1}{3} \right\rfloor $。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
int n,m;
stack<int>st;
vector<pair<int,int>>ans[2];
void solve()
{
    n=re();m=(n+1)/3;
    printf("%d\n",m);
    fls();
    bool cl=0;
    while(st.size())
        st.pop();
    ans[0].clear();
    ans[1].clear();
    for(int i=1;i<=n;i++)
    {
        if(!st.size())
            st.push(i);
        else
        {
            int t=st.top();
            printf("? %d %d\n",t,i);
            fls();
            bool ret=re();
            if(st.size()==1)
                cl=ret;
            if(cl!=ret)
            {
                ans[ret].push_back({t,i});
                st.pop();
                int t2=st.top();
                ans[cl].push_back({t2,t});
                st.pop();
            }
            else
                st.push(i);
        }
    }
    while(st.size()>=2)
    {
        int t=st.top();
        st.pop();
        int t2=st.top();
        st.pop();
        ans[cl].push_back({t,t2});
    }
    if(ans[0].size()<m)
        swap(ans[0],ans[1]);
    ans[0].resize(m);
    printf("! ");
    for(auto [u,v]:ans[0])
        printf("%d %d ",u,v);
    pn;
    fls();
}
signed main()
{
    int T=re();
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Error_Yuan (赞：1)

考虑先把答案猜出来：交互库怎样构造一个达到答案的图？

经过一些手玩，最好的构造是这样的：

- 把点平均分成 3 份，取出其中 2 份，形成一个红色团；剩下的 1 份全连蓝色边。

这样得到的答案是 $n/3$ 级别的，因为：

- 红色团只有 $2n/3$ 个点；
- 蓝色团只有 $n/3$ 个出发点。

仔细处理边界，可以得到准确的结果为 $\lfloor(n+1)/3\rfloor$。

我们坚信这就是对的答案，于是考虑询问。

注意到下面一种惊人的询问策略：

- 维护一条同色链，如果下一条询问的边是异色的，那么弹出链首的两个点。注意，维护的链的颜色可能会发生更改。

为啥这是对的？因为每次弹出都是三个点一条红边一条蓝边，而最后剩下来的链可以贡献长度除以二的答案，一定更优，所以这可以达到 $n/3$ 级别的上界，仔细分析可知确实是 $\lfloor(n+1)/3\rfloor$。

---

