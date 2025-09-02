# Coffee Varieties (hard version)

## 题目描述

This is the hard version of the problem. You can find the easy version in the Div. 2 contest. Both versions only differ in the number of times you can ask your friend to taste coffee.

This is an interactive problem.

You're considering moving to another city, where one of your friends already lives. There are $ n $ cafés in this city, where $ n $ is a power of two. The $ i $ -th café produces a single variety of coffee $ a_i $ .

As you're a coffee-lover, before deciding to move or not, you want to know the number $ d $ of distinct varieties of coffees produced in this city.

You don't know the values $ a_1, \ldots, a_n $ . Fortunately, your friend has a memory of size $ k $ , where $ k $ is a power of two.

Once per day, you can ask him to taste a cup of coffee produced by the café $ c $ , and he will tell you if he tasted a similar coffee during the last $ k $ days.

You can also ask him to take a medication that will reset his memory. He will forget all previous cups of coffee tasted. You can reset his memory at most $ 30\ 000 $ times.

More formally, the memory of your friend is a queue $ S $ . Doing a query on café $ c $ will:

- Tell you if $ a_c $ is in $ S $ ;
- Add $ a_c $ at the back of $ S $ ;
- If $ |S| > k $ , pop the front element of $ S $ .

Doing a reset request will pop all elements out of $ S $ .

Your friend can taste at most $ \dfrac{3n^2}{2k} $ cups of coffee in total. Find the diversity $ d $ (number of distinct values in the array $ a $ ).

Note that asking your friend to reset his memory does not count towards the number of times you ask your friend to taste a cup of coffee.

In some test cases the behavior of the interactor is adaptive. It means that the array $ a $ may be not fixed before the start of the interaction and may depend on your queries. It is guaranteed that at any moment of the interaction, there is at least one array $ a $ consistent with all the answers given so far.

## 说明/提示

In the first example, the array is $ a = [1, 4, 1, 3] $ . The city produces $ 3 $ different varieties of coffee ( $ 1 $ , $ 3 $ and $ 4 $ ).

The successive varieties of coffee tasted by your friend are $ 1, 4, \textbf{1}, 3, 3, 1, 4 $ (bold answers correspond to Y answers). Note that between the two ? 4 asks, there is a reset memory request R, so the answer to the second ? 4 ask is N. Had there been no reset memory request, the answer to the second ? 4 ask is Y.

In the second example, the array is $ a = [1, 2, 3, 4, 5, 6, 6, 6] $ . The city produces $ 6 $ different varieties of coffee.

The successive varieties of coffee tasted by your friend are $ 2, 6, 4, 5, \textbf{2}, \textbf{5} $ .

## 样例 #1

### 输入

```
4 2
N
N
Y
N
N
N
N```

### 输出

```
? 1
? 2
? 3
? 4
R
? 4
? 1
? 2
! 3```

## 样例 #2

### 输入

```
8 8
N
N
N
N
Y
Y```

### 输出

```
? 2
? 6
? 4
? 5
? 2
? 5
! 6```

# 题解

## 作者：duyi (赞：7)


[超超超超超超超超超超超超超超超超超超超超超超超超超超超爽的阅读体验](https://www.cnblogs.com/dysyn1314/p/14369865.html)


# CF1290D Coffee Varieties (hard version)

[题目链接](https://codeforces.com/contest/1290/problem/D)

以下仅讨论较为一般的情况（$1 < k < n$）。其他情况留给读者自行特判。

---

**朴素暴力**：

要对元素去重，可以考虑判断**每一对元素**是否相同。具体来说，对于所有二元组 $(i, j)$（$1\leq i < j\leq n$），先清空队列，然后把 $i$ 加入队列，再把 $j$ 加入队列。如果 $j$ 和 $i$ 两元素相同，就把 $j$ 打上“死亡标记”。最后答案就是没有被打上死亡标记的元素数量。

上述做法太暴力了。考虑**不清空队列**。对所有二元组 $(i_1, j_1), (i_2, j_2), \dots, (i_{\frac{n(n - 1)}{2}}, j_{\frac{n(n - 1)}{2}})$，依次将元素：$i_1, j_1, i_2, j_2, \dots, i_{\frac{n(n - 1)}{2}}, j_{\frac{n(n - 1)}{2}}$ 加入队列。加入一个数时，若队列里存在和它相同的数，就把该数打上死亡标记。但这样（不清空队列）会带来一个问题：可能队列里和它相同的那个数**就是它自己**！那么我们可能就把某个数值的唯一一次出现给删了。

为了避免自己把自己删掉的情况，我们不得不使用一些清空操作。考虑这样一个问题：一张 $n$ 个点的有向图，对所有 $i$，从点 $i$ 向点 $i + 1, i + 2, \dots, n$ 连边。求将图划分为尽量少的路径，使得每条边恰好出现在一条路径中。我的构造方法是：考虑枚举间隔 $d = 1, 2, \dots, n - 1$。

- 所有【端点间隔为 $1$ 的边】只需要 $1$ 条路径就能串起来。
- 所有【端点间隔为 $2$ 的边】需要划分为 $2$ 条路径：起点为 $1$ 的路径和起点为 $2$ 的路径。
- ......
- 所有【端点间隔为 $\frac{n}{2}$ 的边】需要划分为 $\frac{n}{2}$ 条路径。
- 所有【端点间隔为 $\frac{n}{2} + 1$ 的边】需要划分为 $\frac{n}{2} - 1$ 条路径，因为起点为 $\frac{n}{2}$ 时就没有【端点间隔为 $\frac{n}{2} + 1$ 的边】了。
- ......
- 所有【端点间隔为 $n - 1$ 的边】需要划分为 $1$ 条路径。

总路径数是：$\frac{(\frac{n}{2} + 1)\frac{n}{2}}{2} + \frac{\frac{n}{2}(\frac{n}{2} - 1)}{2} = \frac{n^2}{4}$。

那么需要的清空次数也是 $\frac{n^2}{4}$。询问次数 = 总边数 + 划分出的路径数 = $\frac{n(n - 1)}{2} + \frac{n^2}{4}$。无法通过本题。

---

**分块暴力**：

上述做法难以通过，是因为没有充分利用队列长度为 $k$ 的特点。

我们考虑分块：每 $\frac{k}{2}$ 个数分为一块，分出 $\frac{2n}{k}$ 块。

把任意一个块里的所有元素加入队列（队列里有相同元素就打死亡标记），相当于实现了**块内去重**。下面考虑**不同块之间**的去重。暴力枚举一对块 $(i, j)$（$1\leq i < j\leq \frac{2n}{k}$），把队列清空，然后将两个块依次加入队列。

所需的清空次数，即块的无序对数，为 $\frac{\frac{2n}{k}(\frac{2n}{k} - 1)}{2} = \frac{2n^2}{k^2} - \frac{n}{k} \leq \frac{2n^2}{k}\leq 20000$。

所需的询问次数，是无序对数乘以 $k$，即 $\frac{\frac{2n}{k}(\frac{2n}{k} - 1)}{2}\cdot k = \frac{2n^2}{k} - n$。可以通过本题的 [easy version](https://codeforces.com/contest/1291/problem/F)。

[参考代码-在CF查看](https://codeforces.com/contest/1291/submission/106367464)

---

**结合一下**：

我们发现，分块做法在处理二元组 $(i,i + 1), (i, i + 2),  \dots,(i, n)$ 时，都要先清空队列，再重新加入第 $i$ 块。这样是非常亏的。

考虑把分块和“朴素暴力”里的做法相结合。即，不用每次都只加入一个二元组，然后清空。我们把二元组看做边，那么可以每次加入**一条路径**，然后再清空。

在朴素暴力部分，我们知道，一张 $n$ 个节点的图，有 $\frac{n(n - 1)}{2}$ 条边，可以划分成 $\frac{n^2}{4}$ 条路径。现在通过分块，我们把节点数压缩到了 $\frac{2n}{k}$。所以边数是 $\frac{\frac{2n}{k}(\frac{2n}{k} - 1)}{2} = \frac{2n^2}{k^2}-\frac{n}{k}$，划分出的路径数是 $\frac{n^2}{k^2}$。

每条边，以及每条路径的起点，都需要 $\frac{k}{2}$ 次询问操作（即把一个块加入队列）。所以需要的询问操作数是：$\frac{k}{2}(\frac{2n^2}{k^2}-\frac{n}{k} + \frac{n^2}{k^2}) = \frac{3n^2}{2k} - \frac{n}{2}$。可以通过本题。

[参考代码-在CF查看](https://codeforces.com/contest/1290/submission/106370041)

---

**更牛一点**：

发现在上述的，从 $i$ 向 $i + 1, i + 2, \dots ,n$ 连边的有向图中，我们已经难以构造出更优的划分方案。

不妨退一步，把图扩充一下，变成完全图，即 $i$ 向所有 $j\neq i$ 连边。

完全图的性质更好，有更漂亮的划分方法：**之字形划分**（官方题解中称为 zig-zag pattern）。枚举所有起点 $s$（$s = 1, 2, \dots n$）。走出一条不经过重复点的路径：$s \to (s - 1)\to (s + 1)\to (s - 2)\to (s + 2),\dots$。可以理解为把点排成一圈。手动模拟一下，发现这样每条边恰好被覆盖一次。

并且由于扩充为了有向图，我们可以让块的大小从 $\frac{k}{2}$ 变成 $k$。因为任意两个块正着反着都会被拼一次，所以效果和原来是一样的。这样边数和路径数，分别被优化为了 $\frac{n^2}{k^2} - \frac{n}{k}$ 和 $\frac{n}{k}$。总询问次数是：$k(\frac{n^2}{k^2} - \frac{n}{k} + \frac{n}{k}) = \frac{n^2}{k}$。非常优秀。

[参考代码-在CF查看](https://codeforces.com/contest/1290/submission/106372152)


---

## 作者：Fuyuki (赞：2)

## Description

有 $n$ 个元素和一个大小为 $k$ 的队列，你每次可以指定一个元素并执行一次查询操作：

$1$、返回队列中是否存在一个元素的值与该元素的值相同。

$2$、将该元素放到队列末尾，如果队列中元素个数超过 $k$，将队首元素弹出。

额外的，你还可以进行不超过 $30000$ 次的清空队列的操作。

查询操作至多不超过 $\frac{3n^2}{2k}$ 次，并保证 $\frac{3n^2}{2k}\leq 15000$。

你需要求出这 $n$ 个元素去重之后有多少个。

$1\leq k\leq n\leq 1024$，且 $n,k$ 为 $2$ 的整数次幂。

## Solution

$k=1$ 和 $n=k$ 的情况平凡，不做考虑。

对元素去重，对每个值只保留一个元素。如果询问的时候判断该值已经出现，就将该元素去掉（需要保证该元素本身不在队列中，否则可能使得这个值的所有元素都被删去），被去掉的元素不会再次被询问（理由同上）。

将序列对 $\frac{k}{2}$ 分块，每个块内的元素依次询问之后就可以使得每个块内的相同值元素保留最多一个。之后就只需要考虑块之间的相等关系。将一个块对另一个块去重就是依次询问这两个块之间的元素。

直接枚举块需要的询问次数过多，但是可以利用重复的询问，即询问块 $(i,j)$ 和 $(j,k)$ 的话，块 $j$ 就不需要询问两次，下一次可以重复利用上一块已经在队列中的部分。

任意两个块之间都可能存在这样的相等关系，换言之就需要对任意两个无序块之间进行询问操作。

可以将一个块看做一个点，就得到了一张 $\frac{2n}{k}$ 阶完全图，需要处理的块间关系就是所有的边。每次可以在上面选取一条链，花费链上节点个数乘上 $\frac{k}{2}$ 的询问次数并删去链上所有的边。因为查询的时候需要保证查询的元素一定不在队列中，所以一条链是不能出现两个相同节点的。

选取链覆盖完全图可以采用之字形的构造（zig-zag pattern？），枚举起点 $s\in[1,\frac{n}{k}]$，并选取 $s\rightarrow s-1\rightarrow s+1\rightarrow s-2\rightarrow \dots$ 的路径。

这样的话，如果将编号从小到大按顺时针排成一圈，那么对于相差奇数的边会顺时针覆盖到，偶数的话会逆时针覆盖到。每条边会被覆盖到恰好一次。

（P.S. 这个构造方法成立当且仅当节点个数为偶数，但是 $\frac{2n}{k}$ 肯定是偶数）

这样做的询问次数是 $\frac{2n}{k}\times \frac{k}{2}\times \frac{n}{k}=\frac{n^2}{k}$ 满足要求。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;i++)
const int N=2048;
int n,m,k,B,ans,d,tag[N];
int ask(int p){
	static string tmp;
	cout<<"? "<<p<<'\n',cout.flush();
	return cin>>tmp,tmp=="Y";
}
int nxt(int x){return (x<=0)-x;}
void query(int p){
	FOR(i,p*B+1,(p+1)*B)if(!tag[i]&&ask(i))
		tag[i]=1,ans--;
}
int main(){
	cin>>n>>k,B=max(1,k/2),m=n/B,ans=n;
	FOR(i,0,n/k-1){
		if(i)cout<<"R\n",cout.flush(),d=0;
		FOR(j,1,m)query((i+d+m)%m),d=(d<=0)-d;
	}
	cout<<"! "<<ans<<'\n',cout.flush();
	return 0;
}
```


---

## 作者：居然有个高手 (赞：1)

分享一个块长为 $k$，比较直接容易想到的做法。

$k=1$ 与 $k=n$ 都是容易的，考虑 $k=\frac{n}{2}$ 时，我们可以考虑分成两块，按 $[1,n]$ 顺序询问一遍，则第 $i$ 个数已经被 $[\max(1,i-k),i-1]$ 筛选过，然后我们可以先从大到小加入 $[1,\frac n 2]$ 的元素，再从大到小加入 $[\frac n 2 +1,n]$ 的元素，可以发现这样可以完全筛选所有元素。

考虑 $k\not=\frac n 2$ 时，对于序列按 $k$ 分块，对每两块进行如上操作，操作次数为 $\frac{n}{k} \times (\frac{n}{k}-1)\times \frac 1 2\times 4k =2\times \frac{n^2}k - 2n^2$  级别，可以通过 easy version。

发现以上部分十分浪费，原因是处理 $i,j（i<j）$ 时 $j$ 这块的询问没有被利用，于是我们可以一次加入一条路径进行处理，随后即可通过。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1500;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
vector<int>v[N];
int n,k,B;
// bool vis[N];
inline bool push(int x){
    printf("? %d\n",x);fflush(stdout);
    char ch;cin>>ch;
    return ch=='Y';
}
inline void clear(){
    printf("R\n");fflush(stdout);
}
vector<int>q;
int main(){
    n=read(),k=read();
    B=k;
    int id=1;
    for(int i = 1;i+B-1<=n;i+=B,id++){
        for(int j = i;j<=i+B-1;j++)v[id].push_back(j);
    }
    id--;
    if(id==1){
        int ans=n;
        for(int i = 1;i<=n;i++)if(push(i))ans--;
        cout<<"! "<<ans;return 0;
    }
    // cerr<<id<<endl;
    for(int dis = 1;dis<=id;dis++){
        for(int j = 1;j<=dis;j++){
            if(j+dis <= id){
                for(int k = j;k<=id;k+=dis){
                    for(auto i : v[k])if(push(i))q.push_back(i);
                    while(q.size())v[k].erase(lower_bound(v[k].begin(),v[k].end(),q.back())),q.pop_back();
                }
                clear();
                for(int k = j;k<=id;k+=dis){
                    for(int i = v[k].size()-1;i>=0;i--)if(push(v[k][i]))q.push_back(v[k][i]);
                    while(q.size())v[k].erase(lower_bound(v[k].begin(),v[k].end(),q.back())),q.pop_back();
                }
                clear();
            }
        }
    }
    int ans = 0;
    for(int i = 1;i<=id;i++)ans+=v[i].size();
    cout<<"! "<<ans;
    return 0;
}
```

---

## 作者：tzc_wk (赞：1)

Easy version：[Codeforces 题面传送门](https://codeforces.ml/contest/1291/problem/F) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1291F)

Hard version：[Codeforces 题面传送门](https://codeforces.ml/contest/1290/problem/D) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1290D)

发现自己交互题烂得跟 sh*t 一样……于是不管三七二十一先来两道再说（

首先考虑最 trivial 的情况，也就是 $k=1$ 和 $k=n$ 两种情况，对于 $k=1$ 你就 $\mathcal O(n^2)$ 地检查一遍所有的 pair，具体来说我们枚举所有 $i,j(i<j)$，然后依次询问 $i,j$，如果询问到 $j$ 时发现队列中存在 $i$，就说明在 $j$ 前面有存在与 $a_j$ 相同的值，此时 $j$ 不会对答案产生贡献，因此我们考虑开一个数组 $is_i$ 表示 $i$ 是否对答案产生贡献，每访问到这样的 $j$ 就将 $is_j$ 设为 $0$ 即可。最后统计 $\sum\limits_{i=1}^nis_i$ 即可，总询问次数 $\dbinom{n}{2}·2=n(n-1)$

$k=n$ 的情况更容易，直接扫一遍，如果插入一个 $i$ 时发现 $i$ 已经存在，就将 $is_i$ 设为 $0$ 即可，总查询次数 $n$。

现在继续思考更一般的情形，也就是 $k\ne 1$ 且 $k\ne n$ 的情形，我们考虑将两个暴力结合一下，也就是人们常说的**分块暴力**，我们考虑将每 $\dfrac{k}{2}$ 个元素形成一块，询问时对每两个块 $i,j(i<j)$ 跑一遍上面 $k=n$ 的暴力然后清空队列，这样对于每一对满足 $x<y$ 且 $a_x=a_y$ 的 $(x,y)$，如果 $x,y$ 在同一块中那只要扫到 $x$ 所在的块就会统计到这个二元组，否则在遍历 $x$ 所在的块与 $y$ 所在的块时会遍历到该二元组，这也就证明了上述算法的正确性。

算下询问次数，总共 $\dfrac{2n}{k}$ 个块，遍历次数 $\dbinom{2n/k}{2}=\mathcal O(\dfrac{2n^2}{k^2})$，而每次遍历要检验 $k$ 个元素，因此总操作次数 $\dfrac{2n^2}{k}$，可以通过 easy version。

```cpp
const int MAXN=1<<10;
int n,k,is[MAXN+5];
bool query(int x){
	printf("? %d\n",x);fflush(stdout);
	char c;cin>>c;return (c=='Y');
}
int main(){
	scanf("%d%d",&n,&k);int siz=max(k>>1,1);
	for(int i=1;i<=n;i++) is[i]=1;int cnt=n/siz;
	for(int i=1;i<=cnt;i++) for(int j=i+1;j<=cnt;j++){
		for(int l=(i-1)*siz+1;l<=i*siz;l++) is[l]&=!query(l);
		for(int l=(j-1)*siz+1;l<=j*siz;l++) is[l]&=!query(l);
		printf("R\n");fflush(stdout);
	} int sum=0;for(int i=1;i<=n;i++) sum+=is[i];
	printf("! %d\n",sum);fflush(stdout);
	return 0;
}
```

接下来考虑 hard version，不难发现上述算法的瓶颈在于，每次遍历两块时都要重新清空队列，效率太低。考虑优化。我们考虑将所有待检验的二元组 $(i,j)$ 看作一个边，那么显然会连成一个 $\dfrac{2n}{k}$ 个点的完全图（注：这里可能有人会有疑问，在之前的算法中我们不是强制钦定 $i$ 必须小于 $j$ 吗？那这里不应该也有 $i<j$ 吗？为什么会得到一张完全图呢？事实上我们并不一定非得要 $i<j$，如果我们采取这样一个思想：维护一个集合表示目前没有值与其重复的元素，对于某个 $a_i$，如果我们发现在该集合中存在某个元素，满足值与其相同，就将 $a_i$ 从集合中删除，如此进行下去直到集合中无法再删除元素。此时 $is_i$ 的定义要变为 $a_i$ 是否还在集合中。不难发现这两个思路是等价的，而后者并不需要用到 $i<j$ 这个性质），我们的目标即是覆盖这些边。不难发现对于完全图中的一条长度为 $l$ 的链 $a_1\to a_2\to a_3\to\cdots\to a_l$，覆盖它们所需的最小代价为 $l·\dfrac{k}{2}$，具体步骤就是对于这条链上所有点一一询问即可。而显然我们不会重复覆盖相同的边，因此对于某个链覆盖的方案，覆盖整张图所需的最少代价就是 $\dfrac{k}{2}·(\dbinom{2n/k}{2}+\text{使用链的个数})$。而对于一个 $n$ 个点（$n$ 是偶数）的完全图而言有一个性质，就是覆盖它的边集所用的最少的链的个数是 $\dfrac{n}{2}$，具体构造是我们枚举所有 $s\in[1,\dfrac{n}{2}]$，然后 $s\to s+1\to s-1\to s+2\to s-2$ 这样之字形反复横跳，如果超过 $n$ 就回到 $1$，如果小于 $1$ 就回到 $n$。可以证明这样操作之后必然可以覆盖所有边，大概证明方式就是，对于每一条边 $(i,j)$，显然恰好存在两个点 $s$ 满足从 $s$ 开始能够遍历到这个边，而这两个 $s$ 刚好差 $\dfrac{n}{2}$，因此必定恰好有一个 $s$ 在 $[1,\dfrac{n}{2}]$ 中。具体细节留给读者自己思考。操作次数 $\dfrac{k}{2}·(\dbinom{2n/k}{2}+\dfrac{2n}{2k})=\dfrac{k}{2}·(\dfrac{n}{k}·(\dfrac{2n}{k}-1)+\dfrac{n}{k})=\dfrac{n^2}{k}$，可以通过 hard version。

```cpp
const int MAXN=1<<10;
int n,k,siz,cnt,is[MAXN+5];
bool query(int x){
	printf("? %d\n",x);fflush(stdout);
	char c;cin>>c;return (c=='Y');
}
void deal(int x){
	for(int i=(x-1)*siz+1;i<=x*siz;i++) if(is[i]&&query(i)) is[i]=0;
}
int main(){
	scanf("%d%d",&n,&k);siz=max(k>>1,1);cnt=n/siz;
	for(int i=1;i<=n;i++) is[i]=1;
	for(int i=1;i<=n/k;i++){
		int cur=0;
		for(int j=1;j<=cnt;j++) deal((i+cur+cnt)%cnt+1),cur=(cur<=0)-cur;
		printf("R\n");fflush(stdout);
	} int sum=0;for(int i=1;i<=n;i++) sum+=is[i];
	printf("! %d\n",sum);fflush(stdout);
	return 0;
}
```


---

## 作者：Hoks (赞：0)

## 前言
语文课给玩出来了，感觉给不到 $\color{red}*2800,\color{black}*3\color{red}000$。

摘自[交互、构造、博弈](https://www.luogu.com.cn/training/676672)。
## 思路分析
先来看 [easy version](https://www.luogu.com.cn/problem/CF1291F)。

注意到这个题比较特殊的一点在于次数限制是 $\frac{2n^2}{k}$，长得很奇怪，我们考虑怎么把这样的东西凑出来。

注意到 $n,k$ 都是 $2$ 的幂次，也就是告诉我们 $k|n$。

我们不妨把这 $n$ 个数划分为 $k$ 块，那么每块就是 $\frac{n}{k}$ 个数，我们可以给每块用 $2n$ 判断是否有重复出现。

接着就是怎么找种类数的问题了。

因为这题交互库自适应，所以本质而言对于数 $i$，我们要判断所有的 $j(1\le j<i)$，是否存在 $a_i=a_j$，如果存在，那么 $j$ 这个数就是没有贡献的，否则贡献为 $1$。

也就是说对于块 $i$ 的数，我们肯定要先去判断一下块 $j(1\le j<i)$ 对他是否有相同的，同时我们还要判断一下同一块中的情况。

这看上去好像很难做，我们不妨先来考虑点简单的，比如只有 $1$ 块的时候。

此时我们只要把这块内的数依次放进队列，就可以不重不漏的判断每个的相同了。

尝试推广一下，当有 $2$ 块的时候。

此时我们先把块 $1$ 的数都放到队列里去。

然后选择块 $2$ 的一个数，放进来即可以判断是否和块 $1$ 中的数相同。

但是这样做了之后块 $1$ 就有一个数被挤掉了，我们必须要 `reset` 或者在之后补上这没判的一部分，貌似很困难。

如果我们直接选择 `reset`，那么查询次数就是 $k^2+2k$，而此时的 $\frac{2n^2}{k}=8k$，完全不是同一个量级的。

怎么去优化这个部分呢？

队列长度为 $k$，所以当我们贪心的想要一次去判掉 $k$ 个数，下一次就必须要重新清空。

那如果我们一次只判断 $k-1$ 个数呢？

也就是 $k-1$ 个数划分一块。

那么我们一次就可以判断掉两个数的信息了。

比如我们将 $1,2,\dots,k-1$ 划为一块，那么我们可以在队列里再加入 $k,k+1$，能判断掉其和这第一块的所有可能情况。

推广一下，如果我们一次只判断 $k-w$ 个数呢？

那么就可以一次判断掉 $w+1$ 个数的信息了。

考虑均衡一下，我们肯定希望一次可以把两块之间的贡献处理掉最优秀，所以不妨取 $w=\frac{k}{2}$，这样一次就能判断掉 $\frac{k}{2}+1$ 个数。

我们希望刚好是整块的，所以虽然我们是可以一次判 $\frac{k}{2}+1$ 个数，为了方便处理还是只判 $\frac{k}{2}$ 个数，也就是一整块。

此时做法已经呼之欲出了，我们不放设 $m=\frac{2n}{k}$，表示块数，此时块长为 $\frac{k}{2}$。

每一次我们枚举两个块 $i,j(i<j)$，先把块 $i$ 的所有数扔进队列，再把块 $j$ 的数全部扔进队列，就可以得到块 $i$ 对于块 $j$ 的贡献。

至于块间贡献，因为我们已经把任何的同一块都同时的扔在队列里过了，所以已经在块间询问时判断完了。

然后来算一下询问次数。

枚举所有块对 $\frac{m(m-1)}{2}$，每个块要用 $k$ 步。

代入 $m=\frac{2n}{k}$，我们可以得到最后的步数为 $\frac{2n^2-nk}{k}$，显然是小于 $\frac{2n^2}{k}$ 的，可以通过 [easy version](https://www.luogu.com.cn/problem/CF1291F)。

然后来看 [hard version](https://www.luogu.com.cn/problem/CF1290D)。

这个询问次数还是过不了，那我们还应该如何优化呢？

你注意到，我们枚举判断了块 $i,j(i<j)$ 后，$j$ 已经在队列里了，而块 $i$ 是我们不在意的，可以扔掉的。

也就是我们可以再找到一个块 $k(k>j)$，直接在询问块 $i,j$ 后立刻询问块 $k$，这样就不用再浪费清空并且搞出了块 $k$ 的答案。

这样每一次我们就节约了 $\frac{k}{2}$ 步，为了方便实现我们不妨优先枚举块间距 $len$，然后直接枚举起点 $i$，每次跳间距 $len$ 块处理贡献。

这样显然是不重不漏的。

而我们每次合并判断都可以节约 $\frac{k}{2}$ 步，最后没能省掉的询问就是在开头那个块扔进来的时候。

我们算一下这个询问次数，大概就是 $\frac{km(m-1)}{4}+\frac{km^2}{8}$，这个式子的意义就是每个节约后的块被问到的次数加上开头块需要的次数。

然后把 $m=\frac{2n}{k}$ 代入可以得到次数为 $\frac{3n^2}{2k}-\frac{n}{2}$，显然是能过的。

然后我们就拿下了这题。
## 代码
实现的时候注意一下 $k=1$ 的情况。

因为我们最开始不是把多余的一步扔了吗，实际上当 $k=1$ 的时候，这步是要拿回来的。

所以当 $k=1$ 时，我们直接令 $k=2$ 就对了。

剩下的非常好写。
```cpp
#include<bits/stdc++.h>
#define int long long 
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=1e6+10,M=1e5+10,V=2e2+10,mod=1e9+9,INF=0x3f3f3f3f3f3f3f3f;
int n,k,a[N];char s[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
//	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline long long read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(long long x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='+'||c=='-'||c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int getl(int x){return (x-1)*k+1;}
inline int getr(int x){return x*k;}
inline void add(int x)
{
	cout<<"? "<<x<<endl;
	int l=0;rd(s,l);if(s[1]=='Y') a[x]=1;
	if(s[1]=='E') exit(0);
}
inline void solve()
{
	n=read(),k=read();if(k==1) k++;k/=2;int m=n/k;
	for(int i=1;i<m;i++) for(int j=1;j<=i&&j+i<=m;j++)
	{
		cout<<"R"<<endl;
		for(int l=j;l<=m;l+=i) for(int p=getl(l);p<=getr(l);p++) add(p);
	}int ans=0;for(int i=1;i<=n;i++) if(!a[i]) ans++;cout<<"! "<<ans<<endl;
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：larsr (赞：0)

来点不一样的？发现题解区全是 $\frac{n^2}{k}$ 的，而我的确是一个乱搞做法。

对 $n$ 个数进行分组，$t$ 个数一组，$t$ 也是二的次幂，并且小于 $k$。至于计数可以计算每个 $a_i$ 之前有没有和 $a_i$ 相同的数。可以按照每个组之间的差值进行分类查询，也就是说每次插入的组是一个等差数列。又会发现有些公差没必要存在，因为一个栈可能同时出现很多组，在一次公差更小的时候可能也处理了，那么不对这些公差进行查询即可。

复杂度？不会证，但通过打表发现对于每组 $n,k$ 都满足情况。这个 $t$ 直接暴力枚举哪个可行就选哪个。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define N 2000
using namespace std;
int n, k, t, a[N], lim;
int p[N], w[N];
int check(int x)
{
	int mm;
	if(t == 1)mm = k;
	else mm = k / t - 1;
	for(int i = 2; i <= mm; i++)
		if(x % i == 0 && w[x / i])
			return 0;
	w[x] = 1;
	return 1;
}
int main()
{
	scanf("%d%d", &n, &k);
	lim = 3 * n * n / 2 / k;
	for(t = 1; t <= k; t *= 2)
	{
		memset(w, 0, sizeof w);
		for(int i = 1; i <= n / t; i++)p[i] = check(i) + p[i - 1];
		int sum = 0;
		for(int i = 1; i <= n / t; i++)sum += p[max(i - 1, n / t - i)] * t;
		if(sum <= lim)
		{
//			printf("%d %d %d\n", t, sum, lim);
			break;
		}
	}
	memset(w, 0, sizeof w);
	int h = n / t;
	for(int x = 1; x < h; x++)
		if(check(x))
		{
			for(int i = 1; i <= x && i <= h - x; i++)
			{
				for(int j = i; j <= h; j += x)
					for(int k = (j - 1) * t + 1; k <= j * t; k++)
					{
						printf("? %d\n", k);
						fflush(stdout);
						char m;
						cin >> m;
						if(m == 'Y')a[k] = 1;
					}
				printf("R\n");
				fflush(stdout);
			}
		}
	int sum = 0;
	for(int i = 1; i <= n; i++)
		sum += a[i]^1;
	printf("! %d\n", sum);
	return 0;
}

```

---

## 作者：int08 (赞：0)

## 前言
偶遇神秘交互题，不明不白反正战胜了。

头一次见一道题两个难度分到两个 Div. 考的。

# Solution

### Easy version

首先考虑 $k=n$，这个太简单了：直接从前往后加一遍，输出 `N` 的个数即可，原因是这样我们只计算了每种数第一次出现，就是对的。

换句话说，我们只需要求出序列里有多少个数满足前面没有和它相等的数。

对于任意 $i$，我们需要检查所有 $j<i$，$a_i$ 和 $a_j$ 是否相等。

如果把需要检查的数对画到平面上，就会发现它形如一个等腰直角三角形。

考虑 $k=\frac{n}{2}$，此时我们仍然先把整个序列顺序加一遍（然后清空队列），发现已经检查的部分形如：

![](https://cdn.luogu.com.cn/upload/image_hosting/rp75450v.png)

我们只需要检查一个小三角即可。

手玩发现检查小三角的方案如下：假如说要检查 $[x_1,y_1],[x_2,y_2](x_1<x_2,y_1<y_2)$ 对应的小三角，考虑先从 $y_1$ 到 $x_1$ 加入，在从 $y_2$ 到 $x_2$ 加入的时候一个个检查。

如果要检查反过来的小三角，就把倒序改为正序加入。

这样我们就用 $2k$ 次操作检查了一个 $k$ 长的三角，三角总数又只有 $(\frac{n}{k})^2$ 个，总共只需要花 $\frac{2n^2}{k}$ 次操作即可检查完毕，可以通过简单版本。

啥？交上去 WA on #9，比正确答案小？

原来倒序加入的一步出锅了，会导致检查的被同组内后面相同的数干扰。

于是我们把同组内的 $k$ 个三角的检查放到最开始，倒序加入时候只加入同组内已经确定不重复的，这样就不会干扰了。

[Easy version Code](https://codeforces.com/contest/1291/submission/289086566)

### Hard version

发现我们每次检查一个小三角就要清空队列，这亏大发了。

发现我们可以把检查连起来，比如说，我们检查完 $[x_1,y_1],[x_2,y_2](x_1<x_2,y_1<y_2)$ 对应的小三角，队列里剩下了 $[x_2,y_2]$，可以直接用来检查 $[x_2,y_2],[x_3,y_3](x_2<x_3,y_2<y_3)$ 对应的小三角。

直接连起来就过了。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,i,j,len;
bool zt[1145];
char op;
int main()
{
	memset(zt,1,sizeof zt);
	cin>>n>>len;k=n/len;
	for(i=1;i<=n;i++)
		cout<<"? "<<i<<endl,cin>>op,op=='Y'?zt[i]=0:0;
	if(k==1) goto here;
	cout<<"R"<<endl;
	for(i=1;i<=k;i++)
		for(int x=i*len;x>=i*len-len+1;x--) if(zt[x]) cout<<"? "<<x<<endl,cin>>op,op=='Y'?zt[x]=0:0;
	cout<<"R"<<endl;
	for(i=2;i<k;i++)
		for(j=1;j<=i;j++)
			if(j+i<=k)
			{
				for(int x=j*len-len+1;x<=j*len;x++) cout<<"? "<<x<<endl,cin>>op;
				int l=j+i;
				while(l<=k)
				{
					for(int x=l*len-len+1;x<=l*len;x++) cout<<"? "<<x<<endl,cin>>op,op=='Y'?zt[x]=0:0;
					l+=i;
				}
				cout<<"R"<<endl;
				for(int x=j*len;x>=j*len-len+1;x--) cout<<"? "<<x<<endl,cin>>op;
				l=j+i;
				while(l<=k)
				{
					for(int x=l*len;x>=l*len-len+1;x--) if(zt[x]) cout<<"? "<<x<<endl,cin>>op,op=='Y'?zt[x]=0:0;
					l+=i;
				}
			}
	here:
	int ans=0;
	for(i=1;i<=n;i++) if(zt[i]) ans++;
	cout<<"! "<<ans<<endl;
	return 0;
 } 
```
# The End.

---

