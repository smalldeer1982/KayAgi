# [POI 2017 R2] 集装箱 Shipping containers

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5059)。

## 题目描述

**题目译自 [XXIV Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi24-2/dashboard/) [Kontenery](https://szkopul.edu.pl/problemset/problem/oNnWY6ZuzzhvG-jCmijiXkIk/statement/)**

工程师 Bajtazar 负责管理一个集装箱装卸坡道。坡道由 $n$ 个连续位置组成，编号从 $1$ 至 $n$。每位位置上，起重机可堆放任意数量的集装箱，层层叠放。

部分集装箱装有危险物质，需避免过于密集堆放。

Bajtazar 收到 $k$ 项起重机操作指令，第 $i$ 项操作形如 $(a_i, \ell_i, d_i)$，表示从位置 $a_i$ 开始，每隔 $d_i$ 个位置放置一个集装箱，共放置 $\ell_i$ 个（即在位置 $a_i, a_i+d_i, a_i+2d_i, \ldots, a_i+(\ell_i-1)d_i$ 各放一个）。他想知道所有操作完成后，每位位置上的集装箱数量。

## 说明/提示

**样例 1 解释**

每个集装箱上的编号对应将其放置在坡道上的操作序号。

![](https://cdn.luogu.com.cn/upload/image_hosting/49gtt0eh.png)

**附加样例**

1. $n=10, k=10$，随机样例。  
2. $n=11000, k=999, a_i=\ell_i=i+1, d_i=10$，对于 $i=1, 2, \ldots, k$。  
3. $n=100000, k=100000, \ell_1=\ell_2=\ldots=\ell_k=1$。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n \leq 1000, k \leq 2000$ | $21$ |
| $2$    | $n, k \leq 100000, d_1=d_2=\ldots=d_k$ | $33$ |
| $3$    | $n, k \leq 100000$       | $46$ |

## 样例 #1

### 输入

```
8 3
3 4 1
2 3 3
3 2 2```

### 输出

```
0 1 2 1 3 1 0 1```

# 题解

## 作者：R_8x (赞：4)

# P12751 [POI 2017 R2] 集装箱 Shipping containers - 题解 #

不知道各位大神都是用的是什么做法，但是我使用了根号分治。

## 思路： ##

首先，本题要求对序列进行修改操作，很像数据结构题，但是像线段树这种数据结构只能对**连续区间**进行加和，并不能处理这种操作，所以肯定不能通过此题。

先想想数据范围较小的情况，我们可以直接暴力模拟，对答案数组跳着加一，理论时间复杂度是 $O(nq)$ 的，但是如果询问的 $d_i$ 较大时，这种暴力模拟的时间复杂度可能会很优，甚至在 $d_i$ 接近 $n$ 的时候达到常数级别。当然，直接暴力模拟肯定会超时。

然后我们很容易想到一种简单的算法：我们可以认为每一次要修改的下标是一个等差数列，然后把操作离线，按 $d_i$ 排序，然后处理 $d_i$ 相同的操作。对于 $d_i$ 相同的操作，我们可以维护差分数组，对等差数列的首项加一，末项的下一项减一，然后对差分数组求前缀和……不是普通的前缀和，而是跳着加（常规的前缀和是 ```w[i]+=w[i-1]```，而我们需要 ```w[i]+=w[i-d]```）。

但很明显，在处理的 $d_i$ 种类很多时，这种做法的时间复杂度也会变劣，所以第二种方法也不能通过此题。

难道这题就这样变得无解了吗？

当然不是，我们还有利器——根号分治（不会的同学可以看一下 [这位大佬的文章](https://www.luogu.com.cn/article/5gtqzd4a)，并完成模版题 [CF1207F](https://www.luogu.com.cn/problem/CF1207F)）。注意到第一种思路在 $d_i$ 较大时会较优，而第二种思路在 $d_i$ 种类较少时更优，且第二种思路不会因为 $d_i$ 较小而变劣。所以我们仍然可以将操作离线，按 $d_i$ 排序，设 $lim$ 为 $\sqrt{n}$，当 $d_i$ 小于 $lim$ 时使用第二个思路，否则使用第一个思路，这样就会使算法时间复杂度达到 $O(q\sqrt{n})$，可以通过此题。

## 代码： ##

```cpp
#include<bits/stdc++.h>
using namespace std;
int d[200005],ans[200005];
int n,q;
struct node
{
	int a,l,d;
}que[100005];
int lim;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	lim=sqrt(n);
	for(int i=1;i<=q;i++)
		cin>>que[i].a>>que[i].l>>que[i].d;
	sort(que+1,que+q+1,[](node x,node y){return x.d<y.d;});
	int pre=que[1].d;
	for(int i=1;i<=q;i++)
	{
		if(que[i].d<lim)
		{
			if(que[i].d==pre)
				d[que[i].a]+=1,d[que[i].a+que[i].l*que[i].d]--;
			else
			{
				for(int j=pre;j<=n;j++)
					d[j]+=d[j-pre];
				for(int j=1;j<=n;j++)
					ans[j]+=d[j],d[j]=0;
				pre=que[i].d;
				d[que[i].a]+=1,d[que[i].a+que[i].l*que[i].d]--;
			}//第二种思路
		}
		else
		{
			for(int k=que[i].a,j=1;k<=n&&j<=que[i].l;k+=que[i].d,j++)
				ans[k]++;
		}//第一种思路
	}
	for(int i=pre;i<=n;i++)
		d[i]+=d[i-pre];
	for(int i=1;i<=n;i++)
		ans[i]+=d[i];//注意细节，这里差分数组会被少加一次，所以要另外加
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	return 0;
}

```

---

## 作者：BaiBaiShaFeng (赞：2)

## 题意概括

> 有一个长度为 $n$ 的序列，进行 $k$ 次操作，每一次选择起始点 $a$，每隔 $d$ 加一，一共加 $l$ 次，询问最后序列结果。

注意这里起始点是用放置的。

## 做法

感觉没有什么快速的做法，考虑暴力去模拟，时间复杂度固然是爆炸的，但当操作的 $d$ 较大时似乎还蛮优秀的。

有没有其它手段？观察每一次操作的过程就像在向右跳，每一个点会对向右边 $d$ 的点有一个贡献，我们可以考虑1、差分，最后统计的时候可以隔 $d$ 个进行统计，把所有 $d$ 相同的放到一起进行考虑，这样似乎也不错，但是我们发现如果我们全部像这样处理的话时间复杂度依然会爆炸。

不过因为我们在 $d$ 较大的时候有一个相对优秀的暴力解法，我们可以考虑根号分治。

设阈值为 $B$。

暴力模拟一次的时间复杂度是 $O(\frac{n}{B})$。

我们把阈值设为 $\sqrt{n}$，如果 $d$ 大于 $\sqrt{n}$，我们就暴力模拟，这样一次是 $O(\sqrt{n})$ 的。

而剩下的一共只有 $\sqrt{n}$ 个 $d$，我们只需要做 $\sqrt{n}$ 次前缀和就行了。

这么一来整体的时间复杂度就是 $O(n\sqrt{n})$，过这个数据完全没有问题。

## 代码


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int B=300;
const int MN=1e5+115;
int n, k, val[MN], d[MN];
struct Node {int a, l;};
vector<Node> tmp[B+5];
signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); cin>>n>>k;
    for(int i=1,a,l,d; i<=k; ++i){
        cin>>a>>l>>d;
        if(d>B){
            for(int j=1; j<=l; ++j) val[a+(j-1)*d]++;
        }else{
            tmp[d].push_back({a,l});
        }
    }
    for(int i=1; i<=B; ++i){
        if(tmp[i].empty()) continue;
        memset(d,0,sizeof(d));
        for(auto v:tmp[i]){
            d[v.a]++;
            if(v.a+v.l*i<=n) d[v.a+v.l*i]--;
        }
        for(int j=1; j<=n; ++j){
            if(j>i) d[j]+=d[j-i];
            val[j]+=d[j];
        }
    }
    for(int i=1; i<=n; ++i) cout<<val[i]<<" ";
    return 0;
}
```

---

## 作者：ouyangdou (赞：0)

一道好的根号分治（平衡思想）题。

## 思路
考虑暴力，每次复杂度 $O(l)$，最差时间复杂度为 $O(n^2)$，过不了。

再考虑差分，建立差分数组 `a[100005][100005]`( 这里把数列拆成 $n$ 个数列的和，  `a[i][j]`维护目标第 $i$ 个数列的第 $j$ 项减去第 $(j-i)$ 项，符合加的方式)。但最后还原的时间复杂度也是 $O(n^2)$ 的。

为了平衡，我们设一个阈值 $b$，如果 $d\leq b$，就按照差分的方式处理，如果 $d>b$，就暴力。这种算法单次操作最坏复杂度为 $O(\frac{n}{b})$，最后还原的复杂度为 $O(nb)$，总体复杂度为 $O(\frac{n^2}{b}+nb)$。

我们设 $b=\sqrt{n}$，则总体复杂度为 $O(n\sqrt{n})$，$n\leq 100000$，能过！

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[160][100005];//差分数组
int res[100005];//暴力统计
int main(){
    int n,k;
    cin>>n>>k;
    int b=sqrt(n)/2//防MLE
    int st,d,len;//对应操作里的a,d,l
    while(k--){
        cin>>st>>len>>d;
        if(d>b){
            for(int i=0;i<len;i++)res[st+d*i]++;//暴力加
        }
        else{
            a[d][st]++;
            if(st+len*d<=n)a[d][st+len*d]--;//差分
        }
    }
    for(int i=1;i<=b;i++){
        for(int j=1;j<=n;j++){
            if(j>=i)a[i][j]+=a[i][j-i];//还原
            res[j]+=a[i][j];//加和
        }
    }
    for(int i=1;i<=n;i++)cout<<res[i]<<' ';
    cout<<endl;
    return 0;
}
```

---

## 作者：Bobi2014 (赞：0)

这是一道使用根号分治~~优雅的暴力~~的题目。

### 前置知识

- [根号分治~~优雅的暴力~~](https://www.luogu.com.cn/article/5gtqzd4a)
- [前缀和和差分~~不会前缀和和差分来做绿题~~](https://oi.wiki/basic/prefix-sum/)

### 思路

考虑使用差分解决 $d < \sqrt{n}$ 的问题，暴力解决 $d \geq \sqrt{n}$ 的问题，这里主要讲一下如何使用差分解决问题，对于相同的 $d$，我们使用差分数组维护每个位置减去上一个位置之差，遇到不同的 $d$ 时，我们把差分数组做个前缀和，加到答案里去就可以了，要注意前缀和时 $a_{i} = a_{i} + a_{i - d}$。

时间复杂度 $O(q \sqrt{n})$。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct upd{
    int st,cnt,d;
} upds[N];
int n,k,pre = -1,d[N],ans[N],lim;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> k;
    for(int i = 1;i <= k;i ++){
        cin >> upds[i].st >> upds[i].cnt >> upds[i].d;
    }
    sort(upds + 1,upds + k + 1,[](upd a, upd b){
        return a.d < b.d;
    });
    lim = sqrt(n);
    for(int i = 1;i <= k;i ++){
        if(upds[i].d >= lim){
            for(int j = 1;j <= upds[i].cnt;j ++){
                ans[(j - 1) * upds[i].d + upds[i].st] ++;
            }
        }else{
            if(pre == -1 or pre != upds[i].d){
                for(int j = pre;j <= n;j ++){
                    d[j] += d[j - pre];
                }
                for(int j = 1;j <= n;j ++){
                    ans[j] += d[j];
                    d[j] = 0;
                }
                pre = upds[i].d;
                d[upds[i].st] ++;
                d[upds[i].st + upds[i].cnt * pre] --;
            }else{
                d[upds[i].st] ++;
                d[upds[i].st + upds[i].cnt * pre] --;
            }
        }
    }
    if(pre != -1){
        for(int j = pre;j <= n;j ++){
            d[j] += d[j - pre];
        }
        for(int j = 1;j <= n;j ++){
            ans[j] += d[j];
        }
    }
    for(int i = 1;i <= n;i ++){
        cout << ans[i] << " ";
    }
    return 0;
}
```

---

