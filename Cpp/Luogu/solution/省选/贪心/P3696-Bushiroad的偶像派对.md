# Bushiroad的偶像派对

## 题目背景

Bushiroad又叫不许摸。


## 题目描述

Bushiroad的派对有N个校园偶像团体，可能来自编号1-N的学校。每个学校可能有多个团体参加，也有可能没有团体参加。在所有的团体都演出完后，进行人气投票。

我们已经掌握了中场时和结束时的两张人气排行表。给出排行表从人气高到低排序，并给出每个组的学校编号（你却不知道具体是哪个团体）

可是，结束时的表是不太准确的。因为基于这样的一个事实：某个团体的结束时的人气不会低于中场的人气，而且每个团体的学校不会改变。结束的表产生一些矛盾。

负责统计的人为了不想背锅，希望尽可能少修改结束时的排行表的某些团体的学校（人气值不能改），使其不矛盾，请问至少要修改多少个呢？


## 说明/提示

【数据范围】

对于20%的数据， $N\le16$，时限0.5s。

对于40%的数据， $N\le50$，时限0.5s。

对于70%的数据， $N\le5000$，时限1s。

对于全部测试数据， $N\le200000, A\le10^9$。最后3个点时限3s。


## 样例 #1

### 输入

```
3
3 500
2 200
1 100
1 1000
3 700
3 400```

### 输出

```
1```

# 题解

## 作者：demerzel_iv (赞：3)

首先我们来考虑如何建模。

把中场的每个团体看做左括号。结束时的每个团体看做右括号。然后按照人气值从小到大排序。

这样我们就得到了一个括号序列。每个括号都有一个编号（即其学校编号）。

这个括号序列一开始一定是合法的。因为题目保证有解（虽然题目中并没有写= =）。

再看题目的要求。相当于修改尽量少的右括号的编号。使得每个左括号都能找到一个编号相同的右括号与之对应。


那么我们第一步可以贪心地将已经匹配了的相同编号的括号都删去。

删完后剩下的括号序列就不一定合法了= =。我们称之为坏掉的括号序列。

所以要重新加入一些之前删掉的匹配括号使得序列重新合法。在这过程中可以方便地统计答案。

并且你加入的括号对要尽量少。因为每加入一次都要将相应的右括号编号修改。使得满足题目要求。


考虑加入一对括号时会发生什么:


    )      <--未匹配的右括号      ==>      (  )  )

 (     )   <--新加入的括号              左边产生一对匹配。右边多出一个未匹配的右括号

这相当于加入一对括号使得某个右括号向右边移动了。


那么我们将所有可加入的括号对 按照左端点从小到大排序。然后从左往右扫。用一个堆来维护当前最远的右端点。

如果遇到一个坏掉的括号序列中的右括号。就取出堆顶的位置。并将这个右括号向右移动。可以证明这一定是最优的。

再考虑如何处理坏掉的括号序列中的左括号。

我们将坏掉的括号序列中每一个左括号都看做 右括号在无穷远处的一个括号对。这样它在堆中的优先级也会是最高的。

而当它与一个右括号匹配时。那个右括号将被移到无穷远处。

我们只要将所有的右括号都移到无穷远处就可以了。


统计答案？

加入一对括号时。会产生一对新的匹配括号。和一个新的右括号。

我们只需要将这对括号的右括号编号修改使得它们编号相同。而不需要处理那个新的右括号（想一想）。

这样可以很方便的统计答案了。


好像讲起来不是很明白。不如看看代码= =。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
namespace metaphysics
{
    const int N=201000,M=N<<1,INF=2147483647;
    typedef std::pair<int,int> pii;
    struct key{int ty,id,w,pos;key(){}key(int a,int b,int c){ty=a,id=b,w=c;}};
    //ty表示左右括号 id表示编号 w为人气值 pos为排序后的位置
    bool operator < (key a,key b){return a.w==b.w?a.ty>b.ty:a.w<b.w;}
    key s[M];
    pii t[N];
    std::priority_queue<int>Q;
    std::priority_queue<int,std::vector<int>,std::greater<int>>S; //这是小根堆
    bool done[M];
    int begin[N],next[M],pre[M];//链表 用来将相同编号的括号连起来
    int n,m,tot,ans;
    void gotin()
    {
        scanf("%d",&n);
        for(int i=1,x,y;i<=n;i++)scanf("%d%d",&x,&y),s[i]=key(1,x,y);
        for(int i=1,x,y;i<=n;i++)scanf("%d%d",&x,&y),s[n+i]=key(-1,x,y);
        m=n;n<<=1;
        std::sort(s+1,s+n+1);
        //排序得到括号序列
        for(int i=1;i<=n;i++)s[i].pos=i;
        for(int i=n,x;i;i--)
        {
            x=s[i].id;
            pre[begin[x]]=i;
            next[i]=begin[x];
            begin[x]=i;
        }
        //连接同编号的括号
    }
    void first_greedy()
    {
        tot=0;
        for(int i=1,pos;i<=m;i++)
            for(pos=begin[i];pos;pos=next[pos])
                if(s[pre[pos]].ty>0 && s[pos].ty<0)
                {
                    pos[next][pre]=pos[pre][pre];     //相当于   pre[next[pos]]=pre[pre[pos]]
                    pos[pre][pre][next]=pos[next];    //相当于   next[pre[pre[pos]]]=next[pos]
                    pos[done]=pos[pre][done]=1;       //相当于   done[pos]=done[pre[pos]]=1
                    //done数组 用来记录是否被匹配
                    t[++tot]=pii(pre[pos],pos);
                }
        //贪心地消除 已匹配的 同编号括号对

        int cnt=0;
        while(!S.empty())S.pop();

        for(int i=1;i<=n;i++)
            if(done[i])continue;
            else if((s[++cnt]=s[i]).ty>0)t[++tot]=pii(s[i].pos,INF);//将左括号看做右端点无穷远的括号对
            else S.push(s[i].pos);         

        std::sort(t+1,t+tot+1);
        //将所有可加入括号对排序
    }
    void second_not_greedy()
    {
        while(!Q.empty())Q.pop();
        ans=0;

        int maxr,mit=S.top();
        //mit表示当前最左边的 待匹配右括号 的位置
        for(int i=1;i<=tot && !S.empty();i++)
        {
            Q.push(t[i].second);
            while((t[i+1].first>mit || i==tot) && !S.empty())
            {
                maxr=Q.top();Q.pop();
                //maxr表示当前可匹配括号中最远的右括号的位置
                //如果maxr等于INF 我们可以将其匹配掉
                if(maxr<INF)S.push(maxr);
                S.pop();
                mit=S.top();
                ans++;
                //统计答案
            }
        }
    }
    void solve()
    {
        gotin();
        first_gredy();
        second_not_gredy();
        printf("%d\n",ans);
    }
}
int main()
{
    metaphysics::solve();
    return 0;
}
```

---

