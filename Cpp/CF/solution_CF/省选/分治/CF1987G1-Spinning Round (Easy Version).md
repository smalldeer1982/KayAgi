# Spinning Round (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions are the allowed characters in $ s $ . In the easy version, $ s $ only contains the character ?. You can make hacks only if both versions of the problem are solved.

You are given a permutation $ p $ of length $ n $ . You are also given a string $ s $ of length $ n $ , consisting only of the character ?.

For each $ i $ from $ 1 $ to $ n $ :

- Define $ l_i $ as the largest index $ j < i $ such that $ p_j > p_i $ . If there is no such index, $ l_i := i $ .
- Define $ r_i $ as the smallest index $ j > i $ such that $ p_j > p_i $ . If there is no such index, $ r_i := i $ .

Initially, you have an undirected graph with $ n $ vertices (numbered from $ 1 $ to $ n $ ) and no edges. Then, for each $ i $ from $ 1 $ to $ n $ , add one edge to the graph:

- If $ s_i = $ L, add the edge $ (i, l_i) $ to the graph.
- If $ s_i = $ R, add the edge $ (i, r_i) $ to the graph.
- If $ s_i = $ ?, either add the edge $ (i, l_i) $ or the edge $ (i, r_i) $ to the graph at your choice.

Find the maximum possible diameter $ ^{\text{∗}} $ over all connected graphs that you can form. Output $ -1 $ if it is not possible to form any connected graphs.

 $ ^{\text{∗}} $ Let $ d(s, t) $ denote the smallest number of edges on any path between $ s $ and $ t $ .

The diameter of the graph is defined as the maximum value of $ d(s, t) $ over all pairs of vertices $ s $ and $ t $ .

## 说明/提示

In the first test case, here are some possible connected graphs that you can form (the labels are indices):

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G1/b9e604b93005a6fc948b7a3b538eda48ad94326a.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G1/1015454202f1913e51db8d5cb7f5b2c4acb62524.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1987G1/910cf619de9f1bf38bbce8c5e1df95915cc19272.png)In the second test case, the only connected graph has a diameter of $ 1 $ .

## 样例 #1

### 输入

```
8
5
2 1 4 3 5
?????
2
1 2
??
3
3 1 2
???
7
5 3 1 6 4 2 7
???????
5
5 2 1 3 4
?????
6
6 2 3 4 5 1
??????
8
1 7 5 6 2 8 4 3
????????
12
6 10 7 1 8 5 12 2 11 3 4 9
????????????```

### 输出

```
4
1
2
6
4
5
5
8```

# 题解

## 作者：BPG_ning (赞：3)

分类讨论好题。

~~事件起因：本人运气爆棚在 VP 时分配到了最难的 G1。~~

首先发现最大值的 $ l_i = r_i = i $。

而且这个图存在 $ n $ 点 $ n $ 边，是基环树。

把最大值的自环去掉之后就成了一棵**树**。

~~观察样例~~严格证明发现，**一定有解**。

### 证明：

令最大值下标为 $ pos $。

对于最大值左边 $ i < pos $ 部分，一定存在 $ r_i > i $ ，因为他右边一定有严格大于他的值，将 $ (i,r_i) $ 相连，一定是树形结构。

对于右边同理，证必。

---

我们定义最大值为根，所以这是一棵有根树。

### 性质一：

$ j $ 能在 $ i $ 的子树内当且仅当 $ j \in (l_i,r_i) $。

证明：

若想要连出去，一定要在 $ (l_i,r_i) $ 中出现一个 $ k $ 满足 $ p_k > p_{l_i} $ 或者 $ p_k > p_{r_i} $ ， 那么 $ k $ 就应该成为 $ i $ 的 $ l_i $ 或者 $ r_i $ ，矛盾。

### 性质二:

对于每个 $ i $ ，所有满足 $ r_j = i (i \ne j) $ 的 $ j $ 构成的子序列单调递减， $ r $ 同理。

证明：

若存在 $ j,k $ 满足 $ j<k , p_j < p_k , r_j = r_k = i $ ，那么应该是 $ r_j = k $ ，矛盾。

---

然后我们可以开始考虑怎么做，可以考虑枚举最长链左右端点的 $ lca $ ，称其为 $ pos $ ，根据性质一可得，链上所有的点都在 $ (l_{pos},r_{pos}) $ 范围内。

先考虑端点其中一个就是 $ pos $ 的情况，那么其实我们可以预处理出 $ g_{i} $ 表示以 $ i $ 为端点**向下延伸**的最长链长度。

如何处理 $ g $ ?

令 $ j $ 为 $ (l_i,i) $ 的最大位置， $ k $ 为 $ (i,r_i) $ 的最大位置。

显然 $ g_i = \max( g_j , g_k ) + 1 $ ，可以递归处理。

然后我们考虑两个端点都不是 $ pos $ 的情况。

另满足 $ r_i = pos (i \ne pos ) $ 的所有 $ i $ 构成的序列称为 $ dr $ , 显然 $ pos $ 在左边的儿子只能是 $ dr $ 中的元素。

又根据性质二知道 $ dr_{i-1} > dr_{i} $ 所以 $ l_{dr_i} = dr_{i-1} $ ，那么一条链一定形似 $ ... \to dr_i \to dr_{i-1} \to ... \to dr_j \to pos $。

前面省略号的最长长度就是 $ (dr_i,dr_{i+1}) $ 中的最长链长度，就是已经预处理过了的 $ g $。

中间部分考虑要么 $ j $ 是最小的 $ dr $ ， 要么 $ j-1 $ 又是一条链，否则能继续走到 $ dr_{j-1} $ ，所以这段部分的长度就是 $ dr_i $ 前面的 $ dr $ 个数，也就是 $ i $。

所以我们枚举左边有一个端点，两个端点；右边有一个端点，两个端点的最长链的方案，统计即可。

但是我们发现可能存在 $ (dr_i,dr_{i+1}) $ 中可能存在一种方案使得一部分连向 $ dr_i $ ，一部分连向 $ dr_{i+1} $。

我们考虑分治预处理这个东西，令他为 $ f $ ，还是考虑当我们分治到 $ (l_i,r_i) $ 时，他要么条链都是左边 $ (l_i,i) $ 的，要么都是右边 $ (i,r_i) $ 的，要么一条是左边一条是右边的。

令 $ j $ 为 $ (l_i,i) $ 中的最大位置， $ k $ 为 $ (i,r_i) $ 中的最大位置。

那么有 $ f_i = \max(f_j,f_k,g_j+g_k)+1 $。

分治处理即可，复杂度为 $ n \log n $ ，瓶颈为 ST 表 预处理求区间 RMQ。

（这个做法可能的缺点：很难拓展到 G2。）

代码：

```cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=4e5+10;
int n,p[N],l[N],r[N];
int st[N][22],lg[N];
int g[N],f[N];
int ans;
vector<int> dl[N],dr[N];
string useless_things;
int Maxid(int i,int j){
    if(i==0||j==0) return i+j;
    return (p[i]>p[j]?i:j);
}
void read(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
        st[i][0]=i;
    }
    cin>>useless_things;
}
int get_Max(int l,int r){
    if(l>r) return -1;
    int k=lg[r-l+1];
    return Maxid(st[l][k],st[r-(1<<k)+1][k]);
}
int init_dfs(int L,int R){
    if(L>R) return 0;
    int pos=get_Max(L,R);
    int lp=init_dfs(L,pos-1);
    int rp=init_dfs(pos+1,R);
    g[pos]=max(g[lp],g[rp])+1;
    l[pos]=L-1;
    r[pos]=R+1;
    return pos;
}
int init_2(int L,int R){
    if(L>R) return 0;
    int pos=get_Max(L,R);
    int Max=max(init_2(L,pos-1),init_2(pos+1,R));
    int midl=get_Max(L,pos-1),midr=get_Max(pos+1,R);
    if(midl!=-1 && midr!=-1)Max=max(Max,g[midl]+g[midr]);
    return (f[pos]=Max+1);
}
void init(){
    for(int i=1;i<=20;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            st[j][i]=Maxid(st[j][i-1],st[j+(1<<(i-1))][i-1]);
        }
    }
    lg[0]=-1;
    for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
    init_dfs(1,n);
    init_2(1,n);
    for(int i=1;i<=n;i++) dr[r[i]].push_back(i);
    for(int i=n;i>=1;i--) dl[l[i]].push_back(i);
}
void clear(){
    for(int i=0;i<=n+1;i++){
        l[i]=r[i]=0;
        f[i]=g[i]=0;
        dl[i].clear();
        dr[i].clear();
    }
    ans=0;
}
int getG(int L,int R){
    if(L>R) return -1;
    return g[get_Max(L,R)];
}
void work(int L,int R,int pos){
    int vl1=0,vl2=0,vr1=0,vr2=0;
    int res=0,cnt=0,Max=0;
    for(int p:dr[pos]) vr1=max(vr1,g[p]+(cnt++));
    cnt=0;
    for(int p:dl[pos]) vl1=max(vl1,g[p]+(cnt++));
    res=vl1+vr1;
    if(dr[pos].size()>=2){
        cnt=2;
        int id=get_Max(L,dr[pos][0]-1);
        int len=dr[pos].size();
        if(id!=-1) Max=g[id];
        else Max=0;
        for(int i=0;i<len;i++){
            if(i!=len-1) id=get_Max(dr[pos][i]+1,dr[pos][i+1]-1);
            else id=get_Max(dr[pos][i]+1,pos-1);
            if(id!=-1){
                vr2=max(vr2,Max+g[id]+cnt);
                Max=max(Max,g[id]);
            }
            if(i<len-2)cnt++;
        }
        vr2=max(vr2,Max+cnt);
        cnt=2;
        for(int i=1;i<dr[pos].size();i++){
            int p1=dr[pos][i-1],p2=dr[pos][i];
            id=get_Max(p1+1,p2-1);
            if(id!=-1) vr2=max(vr2,f[id]+cnt);
            cnt++;
        }
    }
    if(dl[pos].size()>=2){
        cnt=2;
        int id=get_Max(dl[pos][0]+1,R);
        int len=dl[pos].size();
        if(id!=-1) Max=g[id];
        else Max=0;
        for(int i=0;i<len;i++){
            if(i!=len-1) id=get_Max(dl[pos][i+1]+1,dl[pos][i]-1);
            else id=get_Max(pos+1,dl[pos][i]-1);
            if(id!=-1){
                vl2=max(vl2,Max+g[id]+cnt);
                Max=max(Max,g[id]);
            }
            if(i<len-2)cnt++;
        }
        vl2=max(vl2,Max+cnt);
        cnt=2;
        for(int i=1;i<len;i++){
            int p1=dl[pos][i-1],p2=dl[pos][i];
            id=get_Max(p2+1,p1-1);
            if(id!=-1) vl2=max(vl2,f[id]+cnt);
            cnt++;
        }
    }
    res=max(res,vl2);
    res=max(res,vr2);
    ans=max(ans,res);
}
void sol(){
    for(int i=1;i<=n;i++){
        work(l[i]+1,r[i]-1,i);
    }
    cout<<ans<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    freopen("nzq.in","r",stdin);
    freopen("nzq.out","w",stdout);
    int T=1;
    cin>>T;
    for(int c=1;c<=T;c++){
        read();
        init();
        sol();
        clear();
    }
    cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
    return 0;
}

```

---

## 作者：柳易辰 (赞：1)

完全不知道另一篇在写什么。简短优美的笛卡尔树做成了基环树大分讨，而且做法无法拓展到 Hard Ver。

考虑答案一定可以表示成 $v_1\to v_2\to\dots\to v_{k-1}\to v_k\gets v_{k+1}\gets\dots\gets v_{m-1}\gets v_m$。

### 情况一

设 $v_i$ 在区间中的位置为 $p_i$。一种情况是直径被最大点分成了左部和右部。即 $p_i(1\leqslant i<k)\in[1,p_k),\ p_i(k<i\leqslant m)\in(p_k,n]$。

设 $b_{i,0/1}$ 分别表示 $[1,i]/[i,n]$ 内的最长**链**，则这种情况的答案为 $b_{i,0}+b_{i,1}-1$。

如何求 $b$ 呢？我们很容易想到求出笛卡尔树求解。这里我们用单调栈维护右链的方式建笛卡尔树。维护一个二元组单调栈，每个元素 $(a_i,l_i)$ 表示值和以该值为根的最长链长度，单调栈按 $a_i$ 单调递减。我们插入一个元素时：

+ 弹出栈中 $a_j<a_i$ 的元素。笛卡尔树会接在 $i$ 的左孩子处，所以我们可以进行更新：$l_i=\max(l_i,l_j+1)$。
+ 不再弹出后，$i$ 会接在栈中其它节点的右孩子处，设 $s_j$ 表示栈中第 $j$ 个元素，我们可以从后向前进行更新：$l_{s_j}=\max(l_{s_j},l_{s_{j+1}}+1)$。

注意到第二个更新暴力做复杂度过高，我们可以在每次更新一弹出元素后再更新前一个元素。

每次用栈中最大元素的历史最大值去更新 $b_i$。正反都做一遍即可得到 $b_{i,0/1}$。

### 情况二

还有一种情况（见样例第一组数据）就是我们无法根据最大值将直径分成两侧，或者其实就没有包含最大值。

但注意到我们仍然可以根据 $v_k$ 将直径分成两段。使得 $p_1<p_2<\dots<p_{k-1}<p_m<p_{m-1}<\dots<p_{k+1}<p_k$。于是我们可以考虑枚举 $p_{k-1}$，剩下一段的答案显然就是 $b_{p_{k-1},1/0}$。但我们其实无法保证 $p_{k-1}$ 这条链可以连到 $p_k$ 这条链。

我们根据前缀最大值（即最终情况一中处理得到最终单调栈中的元素）将分成若干段。那么 $p_1,p_2,\dots,p_{k-1}$ 均在同一段中，否则不优。于是我们对于每段都做一遍情况一的单调栈，用得到的位置 $i$ 的答案 + $b_{i,1/0}$ 更新。

[代码](https://codeforces.com/contest/1987/submission/286675976)。

---

