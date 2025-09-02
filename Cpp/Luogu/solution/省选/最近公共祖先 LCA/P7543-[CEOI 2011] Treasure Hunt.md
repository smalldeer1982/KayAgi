# [CEOI 2011] Treasure Hunt

## 题目描述

现在有一棵树，初始时只有一个根节点 $1$，你需要完成下列两种操作：

* `path u s` 表示在 $u$ 下面依次加入了 $s$ 个节点：其中的第 $i$ 个节点作为第 $i-1$ 个节点的孩子（$2\le i\le s$），特别地，第 $1$ 个节点会作为 $u$ 的孩子。设加入前时，树中节点的最大编号为 $n$，则新加入的 $s$ 个点会被依次编号为 $n+1,n+2,\cdots,n+s$；
* `dig u v` 表示询问 $u,v$ 的中点。形式化地，设 $u,v$ 间的距离为 $d$，则你需要求出 $u,v$的路径上，距离 $u$ 为 $\lfloor \frac d2\rfloor$ 的节点编号。

## 说明/提示

对于 $20\%$ 的数据，保证最终点的编号最大不超过 $5000$，且 $n\le 5000$；  
对于 $50\%$ 的数据，保证最终点的编号最大不超过 $400\ 000$；  
对于 $100\%$ 的数据，保证最终点的编号最大不超过 $10^9$，且 $n\le 400\ 000$。

#### 说明
题目译自 [CEOI 2011 day 1 T3 _Treasure Hunt_](http://ceoi.inf.elte.hu/probarch/11/trezad.pdf)。

## 样例 #1

### 输入

```
11
P 1 2
D 1 3
P 2 5
D 7 3
D 3 7
P 1 2
P 3 3
D 10 11
P 5 1
D 14 8
D 2 4```

### 输出

```
2
5
4
1
6
2```

# 题解

## 作者：cwfxlh (赞：0)

# [P7543](https://www.luogu.com.cn/problem/P7543)              

唐题，抢个首发题解。           

如果每次只加入一个点，那么处理新点的倍增数组，使用倍增即可解决问题。
  
考虑将每条链缩成一个点，然后处理每条链的倍增数组。查询两个点的 LCA 可以先从链上做 LCA，找到两点 LCA 的所在链，然后从两个点所在链往上倍增跳，即可求出 LCA 的具体位置。同样的，跳链的倍增也可以求出 k 级祖先。于是这个题就做完了。复杂度 $O(n\log n)$。       

代码：        


```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,k1,k2,k3,k4,k5,k6,k7,k8,k9,idx;
string s;
struct chn{
    int st;
    int ed;
    int dep;
    int chdep;
    int fa[23];
}P[400003];
set<pair<int,int> >R;
int getchn(int X){
    auto p=R.lower_bound(make_pair(X+1,-1000000));
    if(p==R.begin())return -1;
    p--;
    return (*p).second;
}
int getdep(int X){
    int uu=getchn(X);
    return P[uu].dep+(X-P[uu].st);
}
int chnLCA(int X,int Y){
    int c=20;
    if(P[X].chdep<P[Y].chdep)swap(X,Y);
    while(c--)if(P[P[X].fa[c]].chdep>=P[Y].chdep)X=P[X].fa[c];
    c=20;
    while(c--)if(P[X].fa[c]!=P[Y].fa[c])X=P[X].fa[c],Y=P[Y].fa[c];
    if(X==Y)return X;
    return P[X].fa[0];
}
int jumpDEP(int X,int chn,int tgt){
    if(chn==tgt)return P[chn].dep+(X-P[chn].st);
    for(int i=20;i>=0;i--)if(P[P[chn].fa[i]].dep>P[tgt].dep)chn=P[chn].fa[i];
    return P[chn].dep-1;
}
int KthPar(int X,int chn,int k){
    if(X-P[chn].st<k){k-=(X-P[chn].st);X=P[chn].st;}
    else return X-k;
    for(int i=20;i>=0;i--){
        if(!P[chn].fa[i])continue;
        if(P[chn].dep-P[P[chn].fa[i]].dep<=k){
            k-=P[chn].dep-P[P[chn].fa[i]].dep;
            chn=P[chn].fa[i];
        }
    }
    if(k==0)return P[chn].st;
    return P[P[chn].fa[0]].st+((P[chn].dep-k)-P[P[chn].fa[0]].dep);
}
int main(){
    freopen("P7543.in","r",stdin);
    ios::sync_with_stdio(false);
    cin>>q;
    idx=n=1;
    P[n=1].st=P[n=1].ed=P[1].dep=P[1].chdep=1;
    R.insert(make_pair(1,1));
    while(q--){
        cin>>s;
        if(s[0]=='P'){
            cin>>k1>>k2;
            P[++n].st=idx+1;
            P[n].ed=idx+k2;
            idx+=k2;
            P[n].fa[0]=getchn(k1);
            P[n].dep=P[P[n].fa[0]].dep+(k1-P[P[n].fa[0]].st)+1;
            P[n].chdep=P[P[n].fa[0]].chdep+1;
            R.insert(make_pair(P[n].st,n));
            for(int i=1;i<=20;i++)P[n].fa[i]=P[P[n].fa[i-1]].fa[i-1];
        }
        else{
            cin>>k1>>k2;
            k3=getchn(k1);
            k4=getchn(k2);
            k5=chnLCA(k3,k4);
            k6=getdep(k1)+getdep(k2)-2*min(jumpDEP(k1,k3,k5),jumpDEP(k2,k4,k5));
            if(getdep(k1)>getdep(k2))cout<<KthPar(k1,k3,(k6/2))<<'\n';
            else cout<<KthPar(k2,k4,k6-(k6/2))<<'\n';
        }
    }
    return 0;
}
```

---

