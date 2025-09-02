# [ARC167D] Good Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc167/tasks/arc167_d

この問題では順列と言った際には $ (1,2,\dots\ ,N) $ の順列を指すものとします。

順列 $ P=(P_{1},P_{2},\dots\ ,P_{N}) $ が与えられます。

ここで、以下の条件を満たす順列 $ Q=(Q_{1},Q_{2},\dots\ ,Q_{N}) $ を良い順列とします。

- 任意の整数 $ 1\leq\ x\leq\ N $ について、 $ x\leftarrow\ Q_{x} $ という置換を好きな回数繰り返すことで、 $ x $ を $ 1 $ にすることができる。
 
$ P $ に対して、以下の操作を $ 0 $ 回以上行うことで、 $ P $ を良い順列にしたいです。

- $ 1\leq\ i\lt\ j\ \leq\ N $ を満たす整数 $ i,j $ を選んで、 $ P_{i} $ と $ P_{j} $ を入れ替える
 
$ P $ を良い順列にするのに必要な最小の操作回数を $ M $ としたとき、 $ P $ に対し操作を $ M $ 回行うことで得られる良い順列のうち、辞書式順序で最小のものを求めてください。

$ 1 $ つの入力ファイルにつき $ T $ 個のテストケースが与えられるので、それぞれについて解いてください。

  数列の辞書順とは？数列 $ S\ =\ (S_1,S_2,\ldots,S_{|S|}) $ が数列 $ T\ =\ (T_1,T_2,\ldots,T_{|T|}) $ より**辞書順で小さい**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します。

1. $ |S|\ \lt\ |T| $ かつ $ (S_1,S_2,\ldots,S_{|S|})\ =\ (T_1,T_2,\ldots,T_{|S|}) $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ (S_1,S_2,\ldots,S_{i-1})\ =\ (T_1,T_2,\ldots,T_{i-1}) $
  - $ S_i $ が $ T_i $ より（数として）小さい。

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ 10^{5} $
- $ 2\leq\ N\leq\ 2\times\ 10^{5} $
- $ (P_{1},P_{2},\dots\ ,P_{N}) $ は $ (1,2,\dots\ ,N) $ の順列
- $ 1 $ つの入力ファイルにつき、 $ N $ の総和は $ 2\times\ 10^{5} $ を超えない
- 入力は全て整数
 
### Sample Explanation 1

$ 1 $ つ目のテストケースについて $ P $ は良い順列ではありません。$ P_{1} $ と $ P_{3} $ を入れ替えると $ P=(4,1,2,3) $ となりますがこのとき $ P $ は良い順列となるので、 $ M=1 $ です。 他にも $ P_{2} $ と $ P_{4} $ を入れ替えると $ P=(2,3,4,1) $ となりますが、これは $ M=1 $ 回の操作で得られる良い順列のうち辞書順で最も小さいものになるため、これが答えです。

## 样例 #1

### 输入

```
5
4
2 1 4 3
5
2 1 3 4 5
2
1 2
2
2 1
9
4 3 6 2 7 1 9 8 5```

### 输出

```
2 3 4 1
2 3 4 5 1
2 1
2 1
4 3 5 2 7 1 8 9 6```

# 题解

## 作者：樱雪喵 (赞：5)

## Description

对于一个 $(1,2,\dots,N)$ 的排列 $Q$，称其是好的，当且仅当

- 对于每个整数 $i \in [1,N]$，在若干次 $i \gets Q_i$ 后能够得到 $i=1$。

给定一个排列 $P$，每次操作可以交换两个数。使用最小的操作次数，使得 $P$ 成为一个好的排列，若有多种解，输出字典序最小的。

## Solution

怎么连着两场 D<C 呢？

对于每个 $i$，我们连边 $i\to P_i$，那么这张图形成了若干个不相交的环。$P$ 是一个好的排列当且仅当图上只有一个环。

从小到大依次贪心确定每一位的值，设当前位为 $i$：

- 如果存在至少一个 $P_j=u,j>i$，满足 $i,j$ 不在一个环且 $u<P_i$，我们找到最小的 $u$，并 $\text{swap}(P_i,P_j)$。

- 否则我们不希望字典序变大，尽量不换。但如果 $i$ 是它所在连通块的最后一个位置，必须要换，找到后面最小的 $u$，设 $P_j=u$，并 $\text{swap}(P_i,P_j)$。

判断是否在一个环使用并查集，用一个 `set` 维护每个连通块之间的大小关系。

```cpp
const int N=2e5+5;
#define pii pair<int,int>
#define fi first
#define se second
int n,a[N];
int fa[N],mn[N],siz[N],pos[N];
set<pii> s;
int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
void merge(int x,int y)
{
    x=find(x),y=find(y); if(x==y) return;
    s.erase(pii(mn[x],x)),s.erase(pii(mn[y],y));
    fa[x]=y,siz[y]+=siz[x],mn[y]=min(mn[y],mn[x]);
    s.insert(pii(mn[y],y));
}
int main()
{
    int T=read();
    while(T--)
    {
        s.clear();
        n=read();
        for(int i=1;i<=n;i++) a[i]=read(),pos[a[i]]=i;
        for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1,mn[i]=i,s.insert(pii(i,i));
        for(int i=1;i<=n;i++) merge(i,a[i]);
        for(int i=1;i<=n;i++)
        {
            if(s.size()==1) break;
            auto it=s.begin();
            while(find(it->se)==find(i)) it++;
            int u=it->fi;
            if(u<a[i]||siz[find(i)]==1) 
            {
                int j=pos[u]; swap(a[i],a[j]),swap(pos[a[i]],pos[a[j]]);
                merge(i,j);
            }
            siz[find(i)]--;
        }
        for(int i=1;i<=n;i++) printf("%d ",a[i]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Pengzt (赞：5)

[cnblogs](https://www.cnblogs.com/Pengzt/p/17929982.html)

[ARC167D](https://www.luogu.com.cn/problem/AT_arc167_d)

看到排列并且有 $i\gets a_i$，就可以直接建出图来，显然是若干个不相干的环。

如果不求字典序最小，就可以直接不在同一个环中的 $i,j$ 直接交换就可以了，因为它要求了最小化操作数。如果求字典序最小，直接从前往后扫一遍，可以用 set 维护不在这个环中且 $j>i$ 的最小值，如果小于当前的 $a_i$ 就可以直接交换。但注意如果这是这个环的最后一个数，就必须要交换。

时间复杂度：$\mathcal{O}(n\log n)$。空间线性。

更优的做法是因为最小值有单调性，就可以不用 set，直接扫一遍即可。

代码：
```cpp
const int N=2e5+10;
int n;
int a[N],fa[N],sz[N],mn[N],pos[N];
set<pii> s;
typedef set<pii>::iterator iter;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void merg(int u,int v){
	u=find(u),v=find(v);
	if(u!=v){
		fa[u]=v,sz[v]+=sz[u];
		s.erase(pii(mn[u],u));
		s.erase(pii(mn[v],v));
		s.insert(pii((mn[v]=min(mn[u],mn[v])),v));
	}
}
void solve(){
	cin>>n;
	s.clear();
	for(int i=1;i<=n;i++)cin>>a[i],fa[i]=mn[i]=i,pos[a[i]]=i,sz[i]=1,s.insert(pii(mn[i],i));
	for(int i=1;i<=n;i++)merg(a[i],i);
	for(int i=1;i<=n&&s.size()>1;i++){
		iter it=s.begin();
		while(find(it->second)==find(i))it++;
		int v=it->first,p=pos[it->first];
		if(v<a[i]||sz[find(i)]==1){
			swap(a[i],a[p]);swap(pos[a[i]],pos[a[p]]);
			merg(i,p);
		}
		sz[find(i)]--;
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：3)

## 题意

对于一个长度为 $N$ 的排列 $Q$，定义其为好的，当且仅当

- 对于任意整数 $i \in \left[1, N\right]$，在进行若干次操作 $i \leftarrow Q_i$ 后可以得到 $i = 1$。

给定一个排列 $P$，定义一次操作为交换两个数。定义 $M$ 为可以将 $P$ 变为一个好的的排列的最小操作次数，求在操作 $M$ 次的情况下可以得到的字典序最小的好的排列。

（$2 \le N \le 2 \times 10^5$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ARC167D.html)

转化为图论模型，考虑对于对于所有 $i \in \left[1, N\right]$，建边 $i \rightarrow P_i$，因为每个点的出度和入度均为 $1$，所以建出的图一定是若干个环。而一个好的排列最后建出的图就是一个长度为 $N$ 的环。而每次操作实质上就是合并两个环。

由于所有节点最后均与 $1$ 在统一个环中，并且我们要求字典序最小，那么我们可以从小到大去枚举一个元素 $i$，若其与 $1$ 不在同一个环中就交换其所在环的一个元素与 $1$ 所在环的一个元素，考虑到需要字典序最小，那么我们可以交换与 $1$ 在同一个环的所有元素中第一个大于当前元素，若与 $1$ 在同一个环的所有元素均小于当前元素，那么我们将其与最后一个位置交换。

若出现后者的情况，可以发现与 $1$ 联通的集合为 $\left\{1, 2, 3, \cdots, i - 1\right\}$，由于值的集合和下标集合相同，所以这种情况下 $i$ 会与 $P_{i - 1}$ 交换。若出现前者的情况，由于其是一个环，那么一定存在边 $u \rightarrow v$ 满足， $u < i - 1, v > i$，即存在 $j \le i - 1, P_j > i$。此时的 $j$ 一定满足对于任意 $k < j$，有 $P_k < i \Rightarrow P_k < i + 1$，也就是说被 $i$ 排除的位置集合也不可能进入 $i + 1$ 的决策集合，换句话说，每次交换位置的位置是单调递增的。那么我们使用一个指针 $j$ 去维护即可，若找到了 $P_j > i$ 或扫描到了 $i - 1$ 那么就执行交换操作。

总复杂度 $\mathcal{O}(N)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<bool> bitset;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType T;

    std::cin >> T;

    for (int testcase = 0; testcase < T; ++testcase) {
        valueType N;

        std::cin >> N;

        ValueVector P(N + 1), pos(N + 1);

        for (valueType i = 1; i <= N; ++i) {
            std::cin >> P[i];

            pos[P[i]] = i;
        }

        valueType pointer = 1;

        bitset visited(N + 1, false);

        {
            valueType y = pos[1];

            while (!visited[P[y]]) {
                visited[P[y]] = true;

                y = P[y];
            }
        }

        for (valueType i = 1; i <= N; ++i) {
            if (visited[i])
                continue;

            valueType const x = pos[i];

            while (pointer < i - 1)
                if (P[pointer] < i)
                    ++pointer;
                else
                    break;

            {
                valueType y = x;

                while (!visited[P[y]]) {
                    visited[P[y]] = true;

                    y = P[y];
                }
            }
            std::swap(P[x], P[pointer]);
        }

        std::copy(P.begin() + 1, P.end(), std::ostream_iterator<valueType>(std::cout, " "));

        std::cout << std::endl;
    }

    std::cout << std::flush;

    return 0;
}
```

---

## 作者：233L (赞：3)

### 题意

对于一个 $(1,2,\ldots,N)$ 的排列 $Q$，称其是好的，当且仅当

- 对于每个整数 $i \in [1,N]$，在若干次 $i \gets Q_i$ 后能够得到 $i=1$。

给定一个排列 $P$，每次操作可以交换两个数。使用最小的操作次数，使得 $P$ 成为一个好的排列，若有多种解，输出字典序最小的。

### 分析

稍微转换下题意，$i \to P_i$ 连边，那么好的排列就是所有点都在同一个环中。考虑交换两个数的影响，对于不在同一个环上的两个下标 $i,j$，交换 $P_i,P_j$ 会使得它们处于同一个环（见下图）。所以假设目前有 $k$ 个环，最小操作次数就是 $(k-1)$。

![0](https://p.sda1.dev/13/724f51378d9ac551e229a370c17c98d9/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202023-10-16%20092632.png)

现在看怎么处理字典序最小。我们考虑从前往后扫，假设当前下标为 $i$，对于所有不与 $i$ 在同一个环的点，记 $j$ 是其中 $P_j$ 最小的，且 $i<j$。若 $P_j<P_i$，那么我们直接换，并把它们合并成一个环；若 $P_j>P_i$，一换字典序就变劣了，所以我们尽量不换，除非再不换就合并不了了，即当且仅当 $i$ 是它所在的环中最靠右的点时，才交换。

举个例子：`2143`，`21` 和 `43` 是 $2$ 个环。先考虑 $P_1$，此时 $j=4,P_j=3>P_1$，$1$ 不是环上最靠右的点，不换。然后是 $P_2$，$j$ 不变，但是 $2$ 是环上最靠右的点，这下不得不换了，交换 $(P_2,P_4)$，得到 `2341`。再到 $P_3$，此时不存在 $j$，说明只有一个环了，退出。

### 实现

维护环可以用并查集。记 `pos[i]` 表示 $i$ 在排列中出现的下标，用一个指针从左往右扫，就能求得上文的 $j$。找一个环在排列中最靠右的点，可以维护环的大小，每次处理一个点就把它所在环的大小减 $1$，大小为 $0$ 说明这是最靠右的点。

[My Submission](https://atcoder.jp/contests/arc167/submissions/46637142)

---

## 作者：elbissoPtImaerD (赞：1)

考虑置换环，那么当且仅当只有一个置换环时合法。

考虑交换操作相当于什么：交换两个不在同一个环的数相当于合并这两个环。

我们考虑从小到大确定每个 $i$ 的最终位置。

考虑已经确定 $1 \sim i-1$ 的位置，现在要确定 $i$ 的最终位置。

如果 $i$ 已与 $1$ 在同一个置换环中，由于步数最小，$i$ 就不需要交换，保持原位。

否则，我们要在与 $1$ 在同一置换环中，满足元素值 $>i$ 的情况下，下标最小的那个元素交换。

特别地，如果元素值均 $<i$，我们选取最后那个，即 $p_{i-1}$ 进行交换。

拿一个指针 $j$ 从 $1$ 开始扫，如果当前 $p_j>i$ 或者 $j = i - 1$，那么就进行交换。

复杂度 $\mathcal{O(n)}$。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/arc167/submissions/47134660)。

---

## 作者：_sunkuangzheng_ (赞：1)

真的是大水题，赛时死磕 BC 没看这题太遗憾啦！

$\textbf{1.1 Describtion}$

给定排列 $p$，定义一个排列 $q$ 是好的，当且仅当对于任意 $i \in [1,n]$，都可以进行若干次操作 $i \gets q_i$ 使得 $i=1$。记 $m$ 为只通过交换 $p_i,p_j$ 让 $p$ 变成好的排列的操作次数，求出 $m$ 次操作后能够得到的字典序最小的好的排列 $p'$。

$\textbf{1.2 Hints}$

- $\textbf{1.2.1 Hint 1}$

考虑一个排列是好的的充要条件。

- $\textbf{1.2.2 Hint 2}$

贪心。

$\textbf{1.3 Solution}$

考察“好的排列”的定义，容易发现如果建一张有向图，$i \to p_i$ 连一条有向边，那么整张图只能有一个环。否则，和 $1$ 不在同一个环上的点一定不能通过若干次操作变成 $1$。

原排列若存在 $k$ 个环，显然 $m=k-1$，因为一次操作只能合并两个环。那我们考虑如何让字典序最小，考虑贪心。先求出所有的环，对于每一个环，我们尝试把当前环向 $1$ 所在的环合并。字典序最小，我们希望前面的元素尽可能小，即我们找到当前环里**最小**元素 $x$，并找到在 $1$ 所在的环里，**大于 $x$ 的元素里最靠前的**交换。如果不存在大于 $x$ 的元素，那么这一次交换一定变劣，我们减小其影响，与 $1$ 所在的环里最后一个元素交换。

找到 $x$ 的位置可以使用线段树，找最后一个位置可以简单开一个变量维护。时间复杂度 $\mathcal O(n \log n)$。

$\textbf{1.3 Code}$

实现上，记得交换完元素以后在线段树上要更新。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 16.10.2023 08:23:32
**/
#include<bits/stdc++.h>
using namespace std;
const int N = 2e6+5;
int T,t[N],n,a[N],c[N],re;
void upd(int s,int l,int r,int x,int k){
    if(l == r) return t[s] = k,void();
    int mid = (l + r) / 2;
    if(x <= mid) upd(s*2,l,mid,x,k); else upd(s*2+1,mid+1,r,x,k);
    t[s] = min(t[s*2],t[s*2+1]);
}int qry(int s,int l,int r,int ql,int qr){
    if(ql <= l && r <= qr) return t[s];
    int mid = (l + r) / 2,ans = 1e9;
    if(ql <= mid) ans = min(ans,qry(s*2,l,mid,ql,qr));
    if(qr > mid) ans = min(ans,qry(s*2+1,mid+1,r,ql,qr));
    return ans;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> T;
    while(T --){
        cin >> n;int lstp = 0;
        for(int i = 1;i <= n;i ++) cin >> a[i],c[i] = 0;
        for(int i = 1;i <= n * 4;i ++) t[i] = 1e9;
        for(int i = 1;i <= n;i ++){
            if(c[i]) continue;
            int x = i,mn = i;vector<int> acc;
            while(a[x] != i) if(c[x] = i,acc.push_back(x),x = a[x],a[x] < a[mn]) mn = x;
            c[x] = i,acc.push_back(x);
            // cout << "mn : " << mn << "\n" << "a[mn] : " << " " << a[mn] << "\n";
            int tmp = qry(1,1,n,a[mn],n);x = mn;
            for(int j : acc) upd(1,1,n,a[j],j);
            if(i != 1){
                if(tmp != 1e9) upd(1,1,n,a[tmp],x),upd(1,1,n,a[x],tmp),swap(a[x],a[tmp]);
                else upd(1,1,n,a[x],lstp),upd(1,1,n,a[lstp],x),swap(a[lstp],a[x]);
            }for(int j : acc) lstp = max(lstp,j);
        }for(int i = 1;i <= n;i ++) cout << a[i] << " ";
    cout << "\n";
    }
}
```

---

## 作者：AC_love (赞：0)

一个图包含了 $n$ 个点，若排列的第 $i$ 项为 $P_i$，我们可以连一条 $i \rightarrow P_i$ 的边。通过这种方式，任何一个排列都可以转化成只有若干个环的有向图。

注意到，本题要求的就是让所有点在同一个环上，考虑这个东西怎么做。

我们交换 $P_i, P_j$ 时，本质是断开了 $i \rightarrow P_i$ 与 $j \rightarrow P_j$ 的两条边，转而添加了 $i \rightarrow P_j$ 和 $j \rightarrow P_i$ 的边。

显然，只有 $i, j$ 不在同一个环里时，交换 $P_i, P_j$ 才有意义。而这样一步操作可以把两个环合并成一个环。

如果不要求字典序最小的话，直接换就可以了。但本题要求字典序最小，考虑这个东西怎么做。

首先从小到大枚举每个数 $k$，若 $k$ 和 $1$ 在一个环里，不需要操作。若 $k$ 和 $1$ 不在一个环里，考虑交换 $k$ 和 $1$ 环里的某个元素，使两个环合并。

我们交换的这个对象一定是 $1$ 环里比 $k$ 大的最靠前的数。考虑为什么：如果这个数在 $k$ 前面，那么一定越往前交换使得到的新序列字典序就越最小。

可如果这个数在 $k$ 后面呢？我们发现，此时交换不一定会更优，比如有个形如 $3,6,4$ 之类的东西，我们拿 $3$ 去换 $4$ 其实比换 $6$ 更优。难道我们刚才的结论错了吗？

这种情况对很多人造成了困扰。但仔细思考之后我们发现：不会存在这种情况，这是个虚空 case。

这种情况不存在的原因是：如果 $k$ 后面存在比 $k$ 大的数，那么 $k$ 前面也一定存在。

因为这个环是连向 $1$ 的，如果 $k$ 后面存在比 $k$ 大的数，而 $k$ 前面不存在，那么这个环就无法从 $1$ 连向 $k$ 后面，这个环断开了。这与前提矛盾，因此这种情况不可能存在。

因此刚才的结论是没有问题的，$k$ 应该和 $1$ 环里最靠左的比 $k$ 大的元素交换位置。如果不存在这样一个元素，那么为了让影响最小，$k$ 应该和 $1$ 环里最靠右的元素交换位置。

维护一个优先队列表示当前在 $1$ 环里的元素，优先队列内按照元素位置排序。询问到 $k$ 时，如果队头元素的值小于 $k$，就把这个东西弹出优先队列，直到找到大于 $k$ 的为止。这时我们交换这两个元素的位置。

如果没找到大于 $k$ 的元素，就把 $k$ 和最后一个元素交换。

[code](https://atcoder.jp/contests/arc167/submissions/59537270)

---

## 作者：Erine (赞：0)

这不比 C 简单一百倍？来点无脑做法。

首先套路式地将 $i\to P_i$ 连边，那么图会连成若干个环，结束条件是最后图连成一个大环。

然后交换两个位置，手摸一下实际上就是改变这两个点所在环的连通性。那么最少操作次数显然应该是环数减 $1$。也就是说我们的每次交换都必须要合并两个环，否则不优。

考虑按位贪心。从前往后扫。有两种情形需要交换：

- 必须换。即，这个位置是当前环的最后一个点，如果不换那么这里就 gg 了。
- 贪心换。即，在当前位置所在环外的其他环内，存在比当前位置小的数。这时候我们把它贪心地换过来是优的。

至于维护这个过程，对于当前点是否是当前环的最后一个点，使用并查集即可，注意合并时向位置更靠后的合并；对于找不在当前环内的最小的数（其实等价于当前环的正整数意义下的 $\operatorname{mex}$），可以二分。对于每一个环维护一个平衡树，合并环时启发式合并其对应平衡树，代码中使用 rope 实现。时间复杂度 $\Theta(n\log ^2 n)$。

想做到 $\Theta(n\log n)$ 可以手写平衡树，并实现平衡树上二分与 finger search 平衡树合并即可。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define int long long

using namespace std;
using namespace __gnu_pbds;
using tre = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const int maxn = 2e5 + 10;

int T, n;
int a[maxn], b[maxn], fa[maxn]; 
tre t[maxn];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void fake_main() {
	cin >> n;
	for (int i = 1; i <= n; i++) fa[i] = i, t[i].clear();
	for (int i = 1; i <= n; i++) {
		cin >> a[i], b[a[i]] = i;
		int u = find(i), v = find(a[i]);
		if (u > v) swap(u, v);
		fa[u] = v;
	}
	for (int i = 1; i <= n; i++) t[find(i)].insert(a[i]);
	for (int i = 1; i < n; i++) {
		bool fl = 0;
		if (find(i) == i) fl = 1;
		else if (t[find(i)].order_of_key(a[i]) != a[i] - 1) fl = 1;
		if (!fl) continue;
		int l = 1, r = n;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (mid <= t[find(i)].size() && *t[find(i)].find_by_order(mid - 1) == mid) l = mid;
			else r = mid - 1;
		}
		++l;
		int j = b[l];
		swap(a[i], a[j]);
		b[a[i]] = i, b[a[j]] = j;
		int u = find(i), v = find(j);
		if (u > v) swap(u, v);
		fa[u] = v;
		if (t[u].size() > t[v].size()) t[u].swap(t[v]);
		while (!t[u].empty()) {
			auto it = t[u].begin();
			auto nxt = next(it);
			t[v].insert(*it);
			t[u].erase(it);
			it = nxt;
		}
		tre().swap(t[u]);
	}
	for (int i = 1; i <= n; i++) cout << a[i] << " ";
	cout << endl;
}

signed main() {
	cin >> T;
	while (T--) fake_main();
	return 0;
}
```

---

## 作者：zhongpeilin (赞：0)

## 题目大意:
给你一个 $n$ 的排列 $P$，$i$ 可以到 $P_{i}$，现在有一种操作是选一个 $1\leq i, j \leq n$，并交换 $P_{i}, P_{j}$，请问最少要操作几次才能满足每个数都能经过某些移动到 1？请输出最后的字典序最小的 $P$。

## 解题思路：
首先，我们在纸上画一画，如果将 $i \to P_{i}$，会发现他是几个环组成的，因为通过 $i \to P_{i}$，每个 $i$ 只出现一次，每个 $P_{i}$ 只出现一次。所以每个店入度为 `1`，出度为 `1`。那么最少的操作次数一定是环的个数减一，而目标是将其他的环都与 `1` 的环合并。接下来考虑枚举到 $j$ 的合并最优策略：  
1. 设 $minn$ 是 $j$ 所在连通块的最小点，若 $minn$ 比 `1` 所在的连通块里每个点都大，那么把他们连起来字典序一定不比之前的优了，但为了合并，尽量让字典序小一点，我们选择将 `1` 所在的连通块里最大的点设为 $maxn$，它的 $P$ 值变成 $minn$，而原来指向 $minn$ 的点指向原来指向 $maxn$。如图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/5y6i8gna.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
而我们通过上面的策略会得到：  
![](https://cdn.luogu.com.cn/upload/image_hosting/b4jy6vsa.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
这里直接对于 `1` 的连通块维护 $maxn$，搜索 $j$ 的连通块时，维护 $minn$。  
但是我们如何快速查找谁指向 $i$ 呢？我们可以设 $b_{i}$ 表示谁指向了 $i$，初始化成 $b_{a_{i}} = i$。那么维护 $a,b$ 就可以。  
2. 现在我们到了 $minn < maxn$ 的情况，那么我们就可以在 `1` 里找到最小的点，满足它指向一个比 $minn$ 大的数，那么我们将 每一个 `1` 连通块中 $x$ 点的值设为 $b_{x}$，那么最优的指向 $minn$ 的点一定是 $\min_{minn+1 \leq i \leq maxn} val_{x}$。  
这是区间查询，我们可以用线段树维护 `1` 联通块的点。  
而交换的时候记得改变线段树。  
$O(n \log n)$。

## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0;
	char op = getchar();
	while(op < '0' || op > '9') op = getchar();
	while(op >= '0' && op <= '9'){
		x = x * 10 + (op - '0');
		op = getchar();
	}
	return x;
}
int n, a[200005], b[200005], tree[800005], maxn, minn;
bool vis[200005];
vector<int> vec;

int ask(int u, int l, int r, int L, int R){ //区间查询
	if(r < L || R < l) return n + 1;
	if(L <= l && r <= r) return tree[u];
	int mid = (l + r) / 2;
	return min(ask(u << 1, l, mid, L, R), ask(u << 1 | 1, mid + 1, r, L, R));
}
void add(int u, int l, int r, int pos, int val){ //单点修改
	if(pos < l || r < pos) return ;
	if(l == r){
		tree[u] = val;
		return ;
	}
	int mid = (l + r) / 2;
	add(u << 1, l, mid, pos, val);
	add(u << 1 | 1, mid + 1, r, pos, val);
	tree[u] = min(tree[u << 1], tree[u << 1 | 1]);
}

void ADD(int x){
	add(1, 1, n, x, b[x]);
	//指，值是被指 
}
void DFS(int x){
	if(vis[x]) return ;
	ADD(x); //加入x
	maxn = max(maxn, x);
	vis[x] = 1;
	DFS(a[x]);
}
void dfs(int x){ //向下搜
	if(vis[x]) return ;
	minn = min(minn, x);
	vec.push_back(x); //存
	vis[x] = 1;
	dfs(a[x]);
}

void solve(){
	n = read();
	maxn = 0; minn = n + 1;
	for(int i = 1; i <= n; i++){
		a[i] = read();
		b[a[i]] = i; //
	}
	for(int i = 1; i <= n; i++) vis[i] = 0;
	for(int i = 1; i <= 4 * n; i++) tree[i] = n + 1;
	//上面全是初始化
    
	DFS(1); //1我是特殊处理的
	for(int i = 2; i <= n; i++){
		if(!vis[i]){
			vec.clear(); //存 j 的点
			minn = n + 1;
			dfs(i); //搜索
			
			if(maxn < minn){ //第1种情况
				int bca = a[maxn], bcb = b[minn];
				a[maxn] = minn; b[minn] = maxn;
				ADD(minn); //更新
				
				a[bcb] = bca; b[bca] = bcb;
				ADD(bca);
			} else { //剩下情况
				int bcmaxn = maxn;
				maxn = ask(1, 1, n, minn + 1, n); //查询最小值
				int bca = a[maxn], bcb = b[minn];
				a[maxn] = minn; b[minn] = maxn;
				ADD(minn); //加上
				
				a[bcb] = bca; b[bca] = bcb;
				ADD(bca);
				maxn = bcmaxn; //这里不想脑筋急转弯了，直接将上边的copy下来，不过要改回最大值
			}
			
			for(int j = 0; j < vec.size(); j++){
				int num = vec[j];
				maxn = max(maxn, num);
				ADD(num);
			} //需要后来更新
		}
	}
	for(int i = 1; i <= n; i++) cout << a[i] << " ";
	cout << endl;//答案
}
int main(){
	ios::sync_with_stdio(false);
	int t = read();
	while(t--) solve();
    return 0;
}
```
创作不易，给个赞吧 QWQ!

---

## 作者：Iratis (赞：0)

显然，让 $ i $ 向 $ p_i $ 连有向边，题目的要求即为每次交换两个点所指向的终点，使得整张图形成一个环。

我们发现每次操作可以合并两个环，所以最少的操作次数即为环的个数。

要使得字典序最小，显然 $ 1 $ 指向的会是不在该环中的最小点，同理推得，我们可以从小到大枚举每一个点 $ i $，若其不在 $ 1 $ 所在的环中，就将其加入。

考虑当前 $ 1 $ 所在的环中，满足 $ p_j>i $ 的最小的 $ j $，倘若存在，则使得 $ i $ 与 $ j $ 互换即为最优，否则，直接令该环中最大的 $ j $ 与 $ i $ 互换最优。

赛时代码：[AC code](https://atcoder.jp/contests/arc167/submissions/46636809)

---

## 作者：henrytb (赞：0)

这场感觉 D $\ll$ C 啊，不会数数。

这个 D 题就是首先先把排列看作一个置换，拆出来所有的循环。

然后套路是“交换两个数”的操作可以看成将两个循环捏在一起变成一个大循环。

所以最小的操作次数显然是循环个数再减去 $1$。怎么最小化字典序呢？

考虑从前往后贪心，尝试对每一个位置找到最小可能的值。

假如当前在位置 $i$，我们只考虑位置 $i$ 后的东西交换到 $i$ ，即向前交换的情况。若除了 $i$ 当前所在的循环的所有其他循环中的最小值 $< p_i$，那么可以将其交换过来，然后合并这两个循环。否则，就不动。假如现在枚举到一个循环尾部了，这时候就不得不将其和其他循环捏起来了，就算其他循环中的最小值比它大也得换过来，要不然这个循环就再也没机会和别人合并了。

实现用 `set` 启发式合并。$O(n\log^2 n)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 2e5 + 5;
int _, n;
int p[N], hr[N], cnt;
set<pair<int, int>> hrs[N];
struct Segment {
    int l, r;
    pair<int, int> mn;
} t[N << 2];
inline void pushup(int p) {
    t[p].mn = min(t[p << 1].mn, t[p << 1 | 1].mn);
}
void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r;
    if (l == r) { t[p].mn = *hrs[l].begin(); return; }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}
void modify(int p, int pos) {
    if (t[p].l == t[p].r) { t[p].mn = (hrs[t[p].l].empty() ? make_pair(0x3f3f3f3f, 0x3f3f3f3f) : *hrs[t[p].l].begin()); return; }
    int mid = (t[p].l + t[p].r) >> 1;
    if (pos <= mid) modify(p << 1, pos);
    else modify(p << 1 | 1, pos);
    pushup(p);
}
pair<int, int> query(int p, int l, int r) {
    if (l <= t[p].l && t[p].r <= r) return t[p].mn;
    int mid = (t[p].l + t[p].r) >> 1; pair<int, int> res = make_pair(0x3f3f3f3f, 0x3f3f3f3f);
    if (l <= mid) res = min(res, query(p << 1, l, r));
    if (mid < r) res = min(res, query(p << 1 | 1, l, r));
    return res;
}
int main() {
    for (scanf("%d", &_); _; --_) {
        scanf("%d", &n);
        cnt = 0;
        rep(i, 1, n) hr[i] = 0, hrs[i].clear();
        rep(i, 1, n) scanf("%d", &p[i]);
        rep(i, 1, n) if (!hr[i]) {
            ++cnt; int x = i;
            do {
                hr[x] = cnt;
                x = p[x];
                hrs[cnt].emplace(p[x], x);  // val, pos
            } while (x != i);
        }
        build(1, 1, cnt);
        int now = cnt;
        rep(i, 1, n) {
            if (now == 1) break;
            int id = hr[i];
            // p[i], i
            pair<int, int> mnn = make_pair(0x3f3f3f3f, 0x3f3f3f3f);
            if (id > 1) mnn = min(mnn, query(1, 1, id - 1));
            if (id < cnt) mnn = min(mnn, query(1, id + 1, cnt));
            if (mnn.first > p[i]) {
                if (hrs[id].size() == 1) {
                    goto els;
                }
            } else {
                els:
                --now;
                // swap!
                int nowmnid = hr[mnn.second];
                hrs[id].erase(make_pair(p[i], i));
                hrs[nowmnid].erase(make_pair(p[mnn.second], mnn.second));
                swap(p[i], p[mnn.second]);
                hrs[id].emplace(p[i], i);
                hrs[nowmnid].emplace(p[mnn.second], mnn.second);
                if (hrs[nowmnid].size() < hrs[id].size()) {
                    for (auto &[x, pos]: hrs[nowmnid]) {
                        hr[pos] = id; hrs[id].emplace(x, pos);
                    }
                    hrs[nowmnid].clear();
                } else {
                    for (auto &[x, pos]: hrs[id]) {
                        hr[pos] = nowmnid; hrs[nowmnid].emplace(x, pos);
                    }
                    hrs[id].clear();
                }
                modify(1, id);
                modify(1, nowmnid);
            }
            
            hrs[hr[i]].erase(make_pair(p[i], i));
            modify(1, hr[i]);
        }
        rep(i, 1, n) printf("%d ", p[i]);
        puts("");
    }
    return 0;
}
```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

定义长度为 $n$ 一个排列 $p$ 是好的，当且仅当对于所有 $1\le x\le n$，都可以通过执行若干次以下变换得到 $1$：

> $x=p_x$

给你 $T$ 次询问，每次给出一个排列 $p$，你可以交换当中的两个值。使得其变成一个好的排列。要求在交换次数最少的情况下，最终的排列的字典序最小，输出最后的排列。

## 题目分析

显然，我们建立一个图，对于图中的每个点 $x$，建边 $x\rightarrow p_x$，则题目条件变为了从这张图中的每个点出发都可以抵达 $1$ 号节点。

考虑排列的特殊性，在这张图中，每个点的出度和入度都是 $1$，这说明每个点都存在于一个环中。所以一个联通块内的点都是可以互达的。现在我们要让所有点可达 $1$，就是要将整张图变成一个大环，**联通块个数降为 $1$**。

这时考虑交换排列上两个位置的值对图的影响。如果这两个位置在同一联通块内，则联通块个数不变。否则，它们所在的两个联通块会合并，联通块个数减一。

到这里，最少交换次数就求出来了，为联通块个数减一。

重点在如何维护字典序，这里我考虑的是贪心。

首先，将所有联通块按照联通块内的最小编号排序，依次处理。

> 为什么这样可能处理好字典序？

首先，我们总是希望编号靠小的节点能取到小的值。对于每个节点，我们都希望从大于它且不和它在同一联通块的点，当然还有自己中找到最小的值，与之交换。这肯定是最优的（因为它不能和联通块内的点交换，而小于它的点优先级比它高）。而只有在处理完编号小于它的节点的时候，才能轮到它选择（这才能保证字典序）。

现在我们来考虑该如何交换。

假设当前处理的联通块集合为 $E$，已经处理完的联通块集合为 $S$，未处理的联通块集合为 $T$。$h$ 为 $E$ 中编号最小的点。显然，$E$ 中最小的 $p_x=h$，设这个编号为 $k$。

首先，如果 $\exists x\in S,x<h,p_x>h$，则我们肯定得找到满足条件的最小的 $x$，并交换 $p_x$ 与 $p_k$。

否则，我们在 $T$ 中找到 $x>h$ 中最小的 $p_x$，将其与 $p_h$ 交换。

如果上面两个都不存在，我们就只能和编号小于 $h$ 的数交换，由与小于 $h$ 的数都在 $S$ 内，当中编号最大的就是 $h-1$ 了，交换 $p_{h-1}$ 和 $p_k$ 即可。

刚开始把第一个联通块内的节点加入 $S$，然后每次从 $T$ 中取出下一个联通块的点加入 $E$，进行上述变换后将 $E$ 的点加入 $S$ 并清空 $E$，直至 $T$ 为空即可得到答案。

维护上述的操作，使用二分加线段树可以做到 $O(n\log^2 n)$，使用线段树二分或平衡树可以做到 $O(n\log n)$。

赛时直接二分加线段树，代码很丑，参考价值为零。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=1e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=998244353,bas=131;
const ui base=13331;
using namespace std;
int T,n,a[N],cnt,tot,h[N],to[N<<1],nxt[N<<1],ans[N];
inline void add(int a,int b){
	to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt;
}
bool vis[N];
int bel[N];
vector<int>p[N];
inline void dfs(int x,int rt){
	bel[x]=rt,p[rt].pb(x),vis[x]=1;
	e(x){
		if(!vis[y])dfs(y,rt);
	}
}
int hd[N];
int xd[N<<2],id[N<<2],mx[N<<2];
inline void build(int x,int l,int r){
	xd[x]=inf,id[x]=0,mx[x]=-inf;
	if(l==r)return id[x]=l,void();
	build(lc),build(rc);
}
inline void modify(int x,int l,int r,int p,int k){
	if(l==r)return xd[x]=mx[x]=k,void();
	if(p<=mid)modify(lc,p,k);
	else modify(rc,p,k);
	if(xd[L]<xd[R])xd[x]=xd[L],id[x]=id[L];
	else xd[x]=xd[R],id[x]=id[R];
	mx[x]=max(mx[L],mx[R]);
}
inline int query(int x,int l,int r,int Ll,int Rr){
	if(Ll>Rr)return 0;
	if(OK){
		if(xd[x]==inf)return 0;
		return id[x];
	}
	if(Rr<=mid)return query(lc,Ll,Rr);
	if(Ll>mid)return query(rc,Ll,Rr);
	int lk=query(lc,Ll,Rr),rk=query(rc,Ll,Rr);
	if(!lk)return rk;
	if(!rk)return lk;
	if(ans[lk]<ans[rk])return lk;
	return rk;
}
inline int get(int x,int l,int r,int Ll,int Rr){
	if(OK)return mx[x];
	if(Rr<=mid)return get(lc,Ll,Rr);
	if(Ll>mid)return get(rc,Ll,Rr);
	return max(get(lc,Ll,Rr),get(rc,Ll,Rr));
}
signed main(){  
	T=read();
	while(T--){
		n=read();
		rep(i,1,n)vis[i]=h[i]=0;
		rep(i,1,n)ans[i]=a[i]=read(),add(i,a[i]);
		build(Root);
		cnt=tot=0;
		rep(i,1,n)if(!vis[i])dfs(i,++tot),hd[tot]=i;
		rep(i,1,tot)sort(p[i].begin(),p[i].end());
		for(auto y:p[1])modify(Root,y,a[y]);
		rep(i,2,tot){
			int nw=hd[i];
			int siz=p[i].size();
			rep(j,1,siz-1)if(ans[p[i][j]]<ans[nw])nw=p[i][j];
			int l=1,r=hd[i]-1,as=hd[i];
			while(l<=r){
				if(get(Root,l,mid)>hd[i])as=mid,r=mid-1;
				else l=mid+1;
			}
			if(as==hd[i]){
				int Id=query(Root,hd[i]+1,n);
				if(Id){
					swap(ans[Id],ans[hd[i]]);
					modify(Root,nw,ans[hd[i]]),modify(Root,Id,ans[Id]);
				}else {
					as--;swap(ans[nw],ans[as]);modify(Root,nw,ans[nw]),modify(Root,as,ans[as]);
				}
			}
			else {
				swap(ans[nw],ans[as]);
				modify(Root,nw,ans[nw]),modify(Root,as,ans[as]);
			}
			for(auto y:p[i])modify(Root,y,ans[y]);
		}
		rep(i,1,n)pf(ans[i]),putchar(' ');
		putchar('\n');
		rep(i,1,tot)p[i].clear();
	}
	return 0;
}
```


---

