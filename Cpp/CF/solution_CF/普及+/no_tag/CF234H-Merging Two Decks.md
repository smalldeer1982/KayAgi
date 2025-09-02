# Merging Two Decks

## 题目描述

你面前的桌子上放着两副牌，其中有些牌面朝上，有些牌面朝下。你想把它们合并成一副牌，并且每张牌都面朝下。你将分两个阶段进行。



第一阶段是合并两副牌，使同一副牌的相对的顺序不变。也就是说，对于一副牌中的任意两张不同的牌 $i$ 和 $j$，如果牌 $i$ 位于牌 $j$ 之上，则在合并之后，牌 $i$ 也必须位于牌 $j$ 之上。



第二阶段是在第一阶段的基础上进行的。在阶段中，你可以拿几张最上面的牌，把它们全部转回来。因此，每一张被拿走的牌都被翻转，并且这些牌的顺序被颠倒。也就是说，在颠倒前位于底部的牌，在颠倒后将位于顶部。



你的任务是确保所有的牌都面朝下。在第一阶段找到合并牌的顺序，在第二阶段找到翻转操作的顺序，使所有牌面朝下，并且翻转次数最小。

## 样例 #1

### 输入

```
3
1 0 1
4
1 1 1 1
```

### 输出

```
1 4 5 6 7 2 3
3
5 6 7
```

## 样例 #2

### 输入

```
5
1 1 1 1 1
5
0 1 0 1 0
```

### 输出

```
6 1 2 3 4 5 7 8 9 10
4
1 7 8 9
```

# 题解

## 作者：_edge_ (赞：1)

这道题目倒是做了我不少的时间。

首先我们先来考虑第二个操作，对于操作 $2$ 来说，若序列已经确定了，那么它产生的贡献即为相邻且数值不同的对数。

这个应该很好证，就你考虑当前你碰到一个相邻且数值不同的你必须要先把前面的一大堆都给翻过来才行。

当然，最后一个必须是 $0$，如果不是还要再翻过来，操作次数要 $+1$。

然后呢，我们发现这个合并的过程类似于归并排序，于是我就比较贪心的想了一想，发现这个东西显然是放在相同的左右最优，所以以 $a$ 数列为基准，将 $b$ 数列放进去，如果还有没填完的直接扔到最后。

然而我们发现，样例二竟然神奇的错掉了。

```
5
1 1 1 1 1
5
0 1 0 1 0
```

按照我们贪心的想法，构造出来的序列如下：

```
1 1 1 1 1 0 1 0 1 0
```

我们发现这个东西竟然变劣了，显然将第一个 $0$ 放在最前面是最优的。

然后我们大胆的猜测一下，贪心应该是对的，只不过要加点优化，~~实际上我是看了一眼 CF 标签有一个 `greedy` 才觉得是对的。~~

我们分析一下之前错误的原因是什么，我们发现对于 $a$ 数列来讲，后面跟着 `0` 显然是很不划算的，我们想办法将它插到 `1` 旁边，这样就可以省去一个操作数。

那么我们又有了新的想法，以 $a$ 数列为基准，$b$ 数列插进去，然后 $a$ 和 $b$ 交换一下再搞一遍。

我们发现这个东西好像挺对的？

严谨的证明本蒟蒻不会，只会瞎口胡，过了样例再手玩一下发现挺对的，就写了，在考场上可以写一个 $O(2^n \times n)$ 的暴力对拍一下，看看有没有反例。

然后注意一下 `freopen` 的问题即可。

如有问题还请指出。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=1e6+5;
int n,m,a[INF],b[INF],la[INF][2],c[INF],tot,ans,ans1[INF][2];
int d[INF][5],tot1,ans11;
signed main()
{
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
        scanf("%d",&b[i]);
    la[n][0]=la[n][1]=n+1;
    for (int i=n-1;i>=1;i--) {
        la[i][0]=la[i+1][0];
        la[i][1]=la[i+1][1];
        la[i][a[i]]=i;
    }
    int j=1,i=1;int fl=0;
    for (i=1;i<=n;) {
        while (b[j]==a[i] && j<=m) {
            c[++tot]=b[j];
            d[++tot1][0]=j+n;
            j++;
        }
        if (j>m) break;
        int len=la[i][b[j]];
        if (len>n) len=n;
        int l=0;if (i==1) l=1;else l=i+1;
        for (int k=l;k<=len;k++) {
            c[++tot]=a[k];
            d[++tot1][0]=k;
        }
        i=la[i][b[j]];
        fl=1;
    }
    if (fl) i++;
    while (j<=m) c[++tot]=b[j],d[++tot1][0]=j+n,j++;
    while (i<=n) c[++tot]=a[i],d[++tot1][0]=i,i++;
    for (int i=1;i<=tot;i++)
        if (c[i]!=c[i+1]) ans1[++ans][0]=i;
    // cout<<ans<<"\n";
    la[m][0]=la[m][1]=m+1;
    for (int i=m-1;i>=1;i--) {
        la[i][0]=la[i+1][0];
        la[i][1]=la[i+1][1];
        la[i][b[i]]=i;
    }
    tot1=tot=0;
    j=1,i=1;fl=0;
    for (i=1;i<=m;) {
        while (b[i]==a[j] && j<=n) {
            c[++tot]=a[j];
            d[++tot1][1]=j;
            j++;
        }
        if (j>n) break;
        int len=la[i][a[j]];
        if (len>m) len=m;
        int l=0;if (i==1) l=1;else l=i+1;
        for (int k=l;k<=len;k++) {
            c[++tot]=b[k];
            d[++tot1][1]=k+n;
        }
        i=la[i][a[j]];
        fl=1;
        // cout<<i<<" "<<j<<"\n";
    }
    // for (int i=1;i<=tot;i++)
    //     cout<<c[i]<<" ";
    // cout<<"\n";
    if (fl) i++;
    while (j<=n) c[++tot]=a[j],d[++tot1][1]=j,j++;
    while (i<=m) c[++tot]=b[i],d[++tot1][1]=i+n,i++;
    // for (int i=1;i<=tot;i++)
    //     cout<<c[i]<<" ";
    for (int i=1;i<=tot;i++)
        if (c[i]!=c[i+1]) ans1[++ans11][1]=i;
    if (ans>ans11) {
        for (int i=1;i<=tot1;i++)
            cout<<d[i][1]<<" ";
        cout<<"\n"<<ans11<<"\n";
        for (int i=1;i<=ans11;i++)
            cout<<ans1[i][1]<<" ";
        cout<<"\n";
    } 
    else {
        for (int i=1;i<=tot1;i++)
            cout<<d[i][0]<<" ";
        cout<<"\n"<<ans<<"\n";
        for (int i=1;i<=ans;i++)
            cout<<ans1[i][0]<<" ";
        cout<<"\n";
    }
    return 0;
}

```


---

## 作者：开始新的记忆 (赞：0)

题目大意：有两叠扑克牌，我们首先要将他们合并在一起，每张扑克牌都有0 1两面。通过反转可以将0 与 1交换，问最少多少操作可以将扑克牌的0全部朝上，合并规则：保持每一叠的相对顺序不变，反转的规则是：从当前位置开始前面的全部都反转？

思路：贪心。合并的时候，以第一叠牌的第一张为基准形成情况1 frm，以第二叠牌第一张为基准形成情况2 lat.之后对于每个情况，如果其中一叠的当前牌是相同状态就直接放进，不然放另外一叠牌的当前牌，力求最相同连续。这样就得出两个情况对叠后的一副牌啦。之后就从头开始反转，不同就翻转，最后使得所有的牌都一样状态，此时如果是1状态，就再做一次反转。这样得出的结果是最优的，这个可以自己想象。

code：（勿喷，码风较丑）
```cpp
include<bits/stdc++.h> 
using namespace std;  
class Pair  
{  
public:  
    int ind,stat;  
    Pair() {};  
    Pair & operator =(Pair rhs)  
    {  
        this->ind=rhs.ind;  
        this->stat=rhs.stat;  
        return *this;  
    }  
};  
int main()  
{   freopen("input.txt","r",stdin);  
    freopen("output.txt","w",stdout);  
    int n,m,i,j,cntf,cntl,a_i,b_i,f_i,l_i;  
    vector<Pair> a,b,frm,lat;
    while(cin>>n)  
    {  
        a.clear();b.clear();frm.clear();lat.clear();a.resize(n);  
        for(i=0; i<n; i++)  
        {  
            cin>>j;  
            a[i].ind=i+1;  
            a[i].stat=j;  
        }  
        cin>>m;  
        b.resize(m);  
        frm.resize(n+m);  
        lat.resize(n+m);  
        for(i=0; i<m; i++)  
        {  
            cin>>j;  
            b[i].ind=n+i+1;  
            b[i].stat=j;  
        }  
        frm[0]=a[0];f_i=0;a_i=1;b_i=0;  
        while(f_i<n+m-1)  
        {  
            if((a_i<n&&frm[f_i].stat==a[a_i].stat)||b_i==m)  
            {  
                f_i++;  
                frm[f_i]=a[a_i];  
                a_i++;  
            }  
            else  
            {  
                f_i++;  
                frm[f_i]=b[b_i];  
                b_i++;  
            }  
        }  
        lat[0]=b[0];l_i=0;a_i=0;b_i=1;  
        while(l_i!=n+m-1)  
        {  
            if((b_i<m&&lat[l_i].stat==b[b_i].stat)|| (a_i==n))  
            {  
                l_i++;  
                lat[l_i]=b[b_i];  
                b_i++;  
            }  
            else  
            {  
                l_i++;  
                lat[l_i]=a[a_i];  
                a_i++;  
            }  
        }  
        cntf=cntl=0;  
        int stat=frm[0].stat;  
        for(f_i=1; f_i<n+m; f_i++)  
        {  
            if(frm[f_i].stat!=stat)  
            {  
                stat=frm[f_i].stat;  
                cntf++;  
            }  
        }  
        if(stat==1)  
            cntf++;  
        stat=lat[0].stat;  
        for(l_i=1; l_i<n+m; l_i++)  
        {  
            if(lat[l_i].stat!=stat)  
            {  
                stat=lat[l_i].stat;  
                cntl++;  
            }  
        }  
        if(stat==1)  
            cntl++;  
        if(cntl<cntf)  
        {  
            for(i=0;i<n+m;i++)
                cout<<lat[i].ind<<" ";  
            cout<<endl<<cntl<<endl;  
            stat=lat[0].stat;  
            for(l_i=1; l_i<n+m; l_i++)  
            {  
                if(lat[l_i].stat!=stat)  
                {  
                    stat=lat[l_i].stat;  
                    cout<<l_i<<" ";  
                }  
            }  
            if(stat==1)  
                cout<<l_i;  
            cout<<endl;  
        }  
        else  
        {  
            for(i=0;i<n+m;i++) 
                cout<<frm[i].ind<<" "; 
            cout<<endl<<cntf<<endl;  
            stat=frm[0].stat;  
            for(f_i=1; f_i<n+m; f_i++)  
            {  
                if(frm[f_i].stat!=stat)  
                {  
                    stat=frm[f_i].stat;  
                    cout<<f_i<<" ";  
                }  
            }  
            if(stat==1)  
                cout<<f_i<<" ";  
             cout<<endl;  
        }
    }  
    return 0;  
}  
```


---

