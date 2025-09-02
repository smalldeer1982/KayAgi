# Lost Array

## 题目描述

This is an interactive problem.

Note: the XOR-sum of an array $ a_1, a_2, \ldots, a_n $ ( $ 1 \le a_i \le 10^9 $ ) is defined as $ a_1 \oplus a_2 \oplus \ldots \oplus a_n $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Little Dormi received an array of $ n $ integers $ a_1, a_2, \ldots, a_n $ for Christmas. However, while playing with it over the winter break, he accidentally dropped it into his XOR machine, and the array got lost.

The XOR machine is currently configured with a query size of $ k $ (which you cannot change), and allows you to perform the following type of query: by giving the machine $ k $ distinct indices $ x_1, x_2, \ldots, x_k $ , it will output $ a_{x_1} \oplus a_{x_2} \oplus \ldots \oplus a_{x_k} $ .

As Little Dormi's older brother, you would like to help him recover the XOR-sum of his array $ a_1, a_2, \ldots, a_n $ by querying the XOR machine.

Little Dormi isn't very patient, so to be as fast as possible, you must query the XOR machine the minimum number of times to find the XOR-sum of his array. Formally, let $ d $ be the minimum number of queries needed to find the XOR-sum of any array of length $ n $ with a query size of $ k $ . Your program will be accepted if you find the correct XOR-sum in at most $ d $ queries.

Lastly, you also noticed that with certain configurations of the machine $ k $ and values of $ n $ , it may not be possible to recover the XOR-sum of Little Dormi's lost array. If that is the case, you should report it as well.

The array $ a_1, a_2, \ldots, a_n $ is fixed before you start querying the XOR machine and does not change with the queries.

## 说明/提示

In the first example interaction, the array $ a_1, a_2, \ldots, a_n $ is $ 2, 1, 7, 5, 6 $ and its XOR-sum is $ 7 $ .

The first query made asks for indices $ 1,2,3 $ , so the response is $ a_1 \oplus a_2 \oplus a_3 = 2 \oplus 1 \oplus 7 = 4 $ .

The second query made asks for indices $ 2,3,5 $ , so the response is $ a_2 \oplus a_3 \oplus a_5 = 1 \oplus 7 \oplus 6 = 0 $ .

The third query made asks for indices $ 4,1,5 $ , so the response is $ a_4 \oplus a_1 \oplus a_5 = 5 \oplus 2 \oplus 6 = 1 $ . Note that the indices may be output in any order.

Additionally, even though three queries were made in the example interaction, it is just meant to demonstrate the interaction format and does not necessarily represent an optimal strategy.

In the second example interaction, there is no way to recover the XOR-sum of Little Dormi's array no matter what is queried, so the program immediately outputs $ -1 $ and exits.

## 样例 #1

### 输入

```
5 3

4

0

1```

### 输出

```
? 1 2 3

? 2 3 5

? 4 1 5

! 7```

## 样例 #2

### 输入

```
3 2```

### 输出

```
-1```

# 题解

## 作者：pigstd (赞：24)

[CF1534E](https://www.luogu.com.cn/problem/CF1534E)

本题有个非常简单的做法，不需要分类讨论不需要 dp 不需要 bfs。

不难想象，因为给出的是异或运算，那么你所能得到的所有信息就是把已知的若干条信息异或起来。那么显然，设第 $i$ 个数被询问的次数为 $c_i$，那么需要满足 $c_i$ 为奇数，这样把所有的信息异或起来就可以得到 $a_1 \oplus a_2 \oplus \dots \oplus a_n$ 的值。

思考一下 $c_i$ 需要满足什么条件：首先，令 $sum=\sum c_i$ ，则 $sum$ 需要是 $k$ 的倍数。其次，显然这个时候需要 $\frac {sum}k$ 次操作，那么显然需要满足 $\max(c_i)\le \frac {sum}k$，并且可以用数学归纳法证明满足这个条件就必然有解，这貌似是一个经典问题，具体过程就不展开了。

那么接下来只要构造出 $c_i$ 就可以了。因为要让 $\max(c_i)$ 尽可能的小，所以不难想到一个方法就是先让 $c_i=1$，然后轮流让 $c_i$ 加二直到满足条件为止。关于不合法，因为答案保证次数 $\le 500$ 所以当 $sum>k \times 500$ 的时候就可以停下来，但是我并没有特判这一点而是特判了一个更显然的情况：$k$ 为偶数且 $n$ 为奇数，就直接通过了，因此可以猜测其他情况都是有解的。

得到 $c_i$ 后，把 $(c_i,i)$ 放进优先队列按照 $c_i$ 从大到小排序，每次取出前 $k$ 大的进行一次询问再放回来就可以了，实现非常简单。设询问次数为 $t$，那么时间复杂度就是 $\mathcal{O}(t \times k \times  \log n)$。

代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define WT int TT=read();while(TT--) 
#define NO puts("NO");
#define YES puts("YES");
using namespace std;

inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}

const int M=510; 
int n,k,a[M],res,cnt,x[M],y[M];
priority_queue<pair<int,int> >q;

signed main()
{
	n=read(),k=read();
	if (n%2==1&&k%2==0)return puts("-1"),0;
	for (int i=1;i<=n;i++)a[i]=1,cnt++;
	while(cnt%k!=0)
	{
		for (int i=1;i<=n&&(cnt%k!=0||a[1]>cnt/k);i++)
			a[i]+=2,cnt+=2;
	}
	for (int i=1;i<=n;i++)q.push(mp(a[i],i));
	while(!q.empty())
	{
		for (int i=1;i<=k;i++)
			x[i]=q.top().x,y[i]=q.top().y,q.pop();
		cout<<"?";
		for (int i=1;i<=k;i++)
			cout<<' '<<y[i];cout<<endl;
		int l=read();res^=l;
		for (int i=1;i<=k;i++)
			if (x[i]!=1)q.push(mp(x[i]-1,y[i]));
	}cout<<"! "<<res<<endl;
	return 0;
}
```



---

## 作者：Acfboy (赞：7)

你肯定不会想写 @天机星 的大力分类讨论（

题目里面要求是询问最少的步数，那么肯定得想想最少的步数怎么求得，再构造方案。而要考虑步数就得考虑我们手头有什么样的操作。首先就是询问 $k$ 个没有问过的，这样的答案异或在一起可以得到若干个的异或和。

众所周知，异或的性质是异或两遍就等于没有异或，所以还有一种操作是选过的取 $j$ 个，剩下取 $k-j$ 个，把选过的 $j$ 个又异或了一遍异或没了，所以增加的 $k-j$ 个里面要减去 $j$ 个，相当于多获得了 $k-2j$ 个异或在一起的答案。

那么剩下的操作还有没有呢？因为异或在一起的东西你不把它异或掉一些是没法还原的（不然强制在线就可以破解了），所以其它的各种操作应该是无效的，我们手头上只有上面的一种变换方式。

考虑数据小的时候，直接 bfs 一遍就行了。等等，题目里不是说可以证明不超过 $500$ 个吗，而且我们好像不关心取的 $j$ 个是哪 $j$ 个啊！那直接 bfs 就行了！

这样我们知道了最少步数。

现在来构造方案。

由前面的分析知道我们每次只需要随便选取选过的中的一些（“一些”是多少可以由 bfs 中记录下来）和没选过中的一些，然后询问之后选过的变成了没选过的，没选过的变成了选过的。那么就开两个 vector 记录一下，每次取出一些丢进另一个 vector 里就行了。

代码：

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
const int N = 2005, INF = 0x3f3f3f3f;
int dis[N], pre[N], n, k, x, ans;
int main() {
    std::cin >> n >> k;
    memset(dis, 0x3f, sizeof dis);
    std::queue<int> que;
    dis[0] = 0, pre[0] = -1, que.push(0);
    while(!que.empty()) {
        int c = que.front(); que.pop();
        for(int i = 0; i <= k; i++)
            if(i <= n-c && k-i <= c) {
                int v = c+i-(k-i);
                if(dis[v] == INF) {
                    dis[v] = dis[c]+1;
                    pre[v] = c;
                    que.push(v);
                }
            }
    }
    // 上面 bfs
    if(dis[n] == INF) return puts("-1"), 0;
    std::vector<int> sel, nosel, path;
    for(int i = 1; i <= n; i++) nosel.push_back(i);
   	// nosel 是没选过的，开始时把每个都扔进去。
    for(int i = n; i != -1; i = pre[i]) path.push_back(i);
    std::reverse(path.begin(), path.end());
    // 获取路径。
    for(int i = 0; i < (signed)path.size()-1; i++) {
        int a = path[i], b = path[i+1], d= b-a, num = (d+k) / 2, rnum = k-num;
        // 根据路径算出这次的 j。
        std::vector<int> tmps, tmpns;
        for(int j = 0; j < num; j++) {
            tmps.push_back(nosel.back());
            nosel.pop_back();
        }
        // 从没选过的中取。
        for(int j = 0; j < rnum; j++) {
            tmpns.push_back(sel.back());
            sel.pop_back();
        }
       	// 从选过的取。
        std::cout << "? ";
        for(int j = 0; j < (signed)tmps.size(); j++) std::cout << tmps[j] << " ";
        for(int j = 0; j < (signed)tmpns.size(); j++) std::cout << tmpns[j] << " ";
        std::cout << std::endl;
        // 询问。
        nosel.insert(nosel.end(), tmpns.begin(), tmpns.end());
        sel.insert(sel.end(), tmps.begin(), tmps.end());
        // 把选过的取的丢进没选过的里，没选过的丢进选过的里。
        std::cin >> x;
        ans ^= x;
        // 加入答案。
    }
    std::cout << "! " << ans << std::endl;
    return 0;
}
```

---

## 作者：AzusaCat (赞：6)

这是一个比其他做法阳间的分类讨论做法。

首先一次可以询问 $k$ 个数的异或和。同时对于不大于 $mx=2\min(k,n-k)$ 的偶数 $m$，我们都可以通过两次询问得到任意 $m$ 个数的异或和，方法是把要询问的数分成两半，再任选 $k-\dfrac{m}{2}$ 个其它的数，每次分别询问一半和找到的其他的数，所以有 $m+k-\dfrac{m}{2}\leqslant n$ 得到 $m\leqslant 2(n-k)$。

注意到当 $n$ 是奇数且 $k$ 是偶数的时候我们只能得到偶数个数的异或和，所以一定无解。对于剩下的情况，我们对 $n\bmod k$ 的**奇偶性**分类讨论，下面我们称**预留**的数为通过我们上面所讲的第二种方法询问的数。

- 如果 $n\bmod k$ 是奇数，可以发现这时 $k$ 一定是奇数，那么我们先预留下 $k+n\bmod k$ 个数，每次贪心询问即可，剩下的数 $k$ 个一堆询问即可。
- 如果 $n\bmod k$ 是偶数，如果 $k+n\bmod k\leqslant mx$ 且 $k$ 是偶数，仍旧预留 $k+n\bmod k$ 个数，否则改成预留 $n\bmod k$ 个数即可。

注意到任何操作都可以用上面的两种操作表示出来（分类讨论询问集合是否和当前被询问奇数次的集合有交即证），同时发现我们利用第二种操作询问的数的总和不会超过 $2k$（否则可以用第一种替代），所以我们只会预留 $k+n\bmod k$ 或 $n\bmod k$ 个数，所以 $n\bmod k$ 是奇数的情况得证。

对于 $n\bmod k$ 是偶数的情况，若 $k$ 是奇数同上；若 $k$ 是偶数且 $k+n\bmod k> mx$，如果 $mx<k$ 那么显然不优，反之 $mx\geqslant k$，预留 $k+n\bmod k$ 个数至少要询问 $4$ 次，而预留 $n\bmod k$ 个数只需要询问 $3$ 次，得证。

显然本做法到达了本题的复杂度下界。

[这里](https://codeforces.com/contest/1534/submission/119698063)是一份不太优美的实现。 

---

## 作者：Kubic (赞：3)

这题有两种挺不一样的做法，都挺有意思的。

# $\operatorname{I}$

我们本质上是要对一个 $01$ 序列进行操作，每次操作可以选择 $m$ 个不同的位置将它上面的数反转（$0\rightarrow 1,1\rightarrow 0$）。目标是将 $01$ 序列全变为 $1$。

考虑什么时候无解。如果 $n$ 为奇数，$m$ 为偶数，那么无论如何操作 $01$ 序列的异或和总是等于 $0$，永远达不到目标。

如果 $n$ 比 $m$ 大很多，那么我们可以这样构造：

先进行 $\lfloor\dfrac{n}{m}\rfloor$ 次操作，使得只剩下 $n\mod m$ 个 $0$。

如果 $n\mod m$ 为奇数，那么撤回一次操作，显然此时 $(n\mod m)+m$ 一定为偶数。

令 $t$ 为当前剩余 $0$ 的个数，显然 $t$ 为偶数。拿出 $\dfrac{t}{2}$ 个 $0$ 和 $m-\dfrac{t}{2}$ 个 $1$ 进行操作，此时还会剩余总共 $m-\dfrac{t}{2}+\dfrac{t}{2}=m$ 个 $0$，直接一次操作全部变为 $1$ 即可。

显然在这种情况下这样构造是次数最少的。

如果 $n$ 并不比 $m$ 大很多，那么这个构造就会出问题，因为并没有足够的 $1$ 可选。

形式化地说，如果 $n$ 为偶数且 $m$ 为奇数且 $n<2m$，那么就需要特殊处理。操作过程中 $0$ 的个数一定时奇偶交替的，而我们希望的终止态是偶数。所以在奇数时我们要让操作出的 $0$ 尽量多，这样在偶数时 $1$ 就能尽量多。反复执行贪心操作即可。

再结合之前的构造，即可得出正解。

木有代码。

# $\operatorname{II}$

显然所有恰好有 $i$ 个 $1$ 的状态其实是等价的，可以缩为一个，下称 "状态 $i$"。考虑状态之间的转移关系，对于状态 $i$，枚举当前操作包含的 $1$ 的个数，并求出新状态中 $1$ 的个数 $i'$，连边 $i\rightarrow i'$。

到达状态 $i$ 最少的操作次数就是 $0\rightarrow i$ 的最短路，只需在 bfs 过程中记录前驱并对利用对应的操作状态之间进行转移即可，时间复杂度 $O(n^2)$。

这种做法相较于之前那种来说简洁、直观很多，并且容易想到，细节也更少。

参考代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 505
#define pb push_back
int n,m,w,ans,q[N],dst[N],pr[N],st[N];
bool vs[N];vector<int> e[N];
void slv(int x,int y)
{
	int t[2]={(y-x+m)/2,(x-y+m)/2};printf("? ",x,y);
	for(int i=1;i<=n;++i) if(t[vs[i]])
		--t[vs[i]],vs[i]^=1,printf("%d ",i);
	fflush(stdout);scanf("%d",&w),ans^=w;
}
int main()
{
	scanf("%d %d",&n,&m);q[0]=q[1]=2;
	for(int i=1;i<=n;++i) dst[i]=-1;
	for(int i=0;i<=n;++i)
		for(int j=max(m-n+i,0);j<=min(m,i);++j)
			e[i].pb(m+i-j*2);
	while(q[0]<=q[1])
	{
		int u=q[q[0]++];
		for(auto v:e[u]) if(dst[v]==-1)
			q[++q[1]]=v,dst[v]=dst[u]+1,pr[v]=u;
	}if(dst[n]==-1) {puts("-1");return 0;}
	for(int i=n;i;i=pr[i]) st[++st[0]]=i;
	slv(0,st[st[0]]);
	for(int i=st[0];i>1;--i) slv(st[i],st[i-1]);
	printf("! %d\n",ans);return 0;
}
```

---

## 作者：meyi (赞：3)

### 前置知识：

- 一点 [图论](https://oi-wiki.org/graph/) 基础（如 [BFS](https://oi-wiki.org/graph/bfs/) 

- 一点 [状压dp](https://oi-wiki.org/dp/state/) 基础（可能并不需要

### 题意简述：

交互题，有 $n$ 个数，每次可以查询其中 $k$ 个数的异或和，你需要使用最少的查询次数来得到这 $n$ 个数的异或和，若无解则在输入 $n$ 和 $k$ 后立即输出 `-1 ` 。

### 思路：

如果本题的数据范围是 $n\leq 20$，那么显然可以使用 $O(n\times2^n)$ 的 状压dp 找到查询次数最少的方案。

但我们有必要一一知道这 $n$ 个数当前的状态吗？

令状态 $x$ 表示当前选了 $x$ 个数，若我们在新的一次查询中选择了 $i$ 个已选的数，则会转移到状态 $x-i+(k-i)$，不难发现 $i$ 的限制条件为 $0\leq i\leq \min(k,x)$ 且 $(k-i)\leq(n-x)$。

使用 BFS，在转移时记录前驱，最后输出方案即可。

时间复杂度： $O(nk)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int inf=0x3f3f3f3f,maxn=510;
int a[maxn],ans,dis[maxn],k,n,pre[maxn],val[maxn],x;
queue<int>q;
void dfs(int p){
	if(~pre[p])dfs(pre[p]);
	else return;
	printf("? ");
	for(ri cnt1=val[p],cnt2=k-val[p],i=1;cnt1||cnt2;++i){
		if(a[i]){
			if(cnt1)a[i]^=1,--cnt1,printf("%d ",i);
		}
		else{
			if(cnt2)a[i]^=1,--cnt2,printf("%d ",i);
		}
	}
	printf("\n");
	fflush(stdout);
	scanf("%d",&x);
	ans^=x;
}
int main(){
	scanf("%d%d",&n,&k);
	memset(dis,0x3f,sizeof dis);
	dis[0]=0;
	memset(pre,-1,sizeof pre);
	q.push(0);
	while(q.size()){
		ri now=q.front();q.pop();
		for(ri i=0;i<=k;++i)
			if(i<=now&&(k-i)<=(n-now)){
				ri nxt=now-i+(k-i);
				if(nxt>0&&nxt<=n&&dis[now]+1<dis[nxt]){
					dis[nxt]=dis[now]+1;
					pre[nxt]=now;
					val[nxt]=i;
					q.push(nxt);
				}
			}
	}
	if(dis[n]==inf){
		puts("-1");
		fflush(stdout);
		return 0;
	}
	dfs(n);
	printf("! %d",ans);
	fflush(stdout);
	return 0;
}
```


---

## 作者：E1_de5truct0r (赞：2)

## 思路

如果我们能够通过若干次操作，使得每个元素都比选中了奇数次，那么就能够求出答案；否则你会发现，我们无法通过仅有的信息确定异或次数为偶数的元素的相关信息，因为它的异或永远会被消掉。

那么明显 $n$ 是奇数、$k$ 是偶数的时候无解，因为你每次操作都会产生偶数个异或，但是你需要凑出 $n$ 个奇数相加的次数，这还是一个奇数，所以明显不可能。而其他的情况都是有解的。

那么考虑怎么使得这个操作的次数最小。

其实直接贪心就是对的：从 $1$ 开始，每 $k$ 个向后查一下，最后剩下的那些再和队头的进行匹配，如此往复直到次数能够整除 $k$ 为止。注意一个细节就是如果某一个数的操作次数 $cnt \times k$ 大于总操作次数，那么这样无论怎么安排方案都是不合法的，因为会出现一轮里它被加好几次的情况，我们需要继续加下去。

然后我们就求出了每个点需要操作多少次。那么输出询问就很简单了，每次选择 $k$ 个剩余询问次数不为 $0$ 的询问一下，把答案异或上返回的值。这个可以使用优先队列进行维护。

最后直接输出异或起来的答案就好了。

复杂度 $O(nk\log n)$。

## 代码

[Code & Submission](https://codeforces.com/contest/1534/submission/219436403)

---

## 作者：fjy666 (赞：2)

容易发现你知道哪几个数的 $\operatorname{xor}$ 和并不重要，重要的是你知道几个。  
设 $d_i$ 为经过 $d_i$ 次操作后你知道 $i$ 个数的 $\operatorname{xor}$ 和。  
转移：$d_{i+k}\leftarrow d_i+1,d_{i+k-2j}\leftarrow d_i+1(1\le j\le i)$  
用 bfs 实现，之后求构造的话 bfs 里加个记录路径即可。

[submission](https://codeforces.com/contest/1534/submission/176962977)

---

## 作者：walk_alone (赞：2)

此题本质就是翻硬币问题。对题解区其他几个分类讨论做法做一个简化的说明与注释。

根据 AzusaCat 大佬的分析，我们可以得到一个重要结论：对于不超过 $x=2\min\{k,n-k\}$ 的偶数，我们可以使用两次询问出这一部分的异或和。显然这个值要小于 $k$，同时要预留出足够多的剩余量让我们好消除，因而有上界 $2(n-k)$。其使用方式如下：

考虑一个长度为 $7$ 的序列 $\{a_1,a_2,a_3,a_4,a_5,a_6,a_7\}$，一次可以询问 $5$ 个，那么对于任意不超过 $4$ 的偶数均可通过这种方式询问出来：（以询问 $\{a_1,a_2,a_3,a_4\}$ 为例）

1. 询问 $\{a_1,a_2,a_5,a_6,a_7\}$。

2. 询问 $\{a_3,a_4,a_5,a_6,a_7\}$。

3. 将二者异或起来，就可以得到 $\{a_1,a_2,a_3,a_4\}$。

可以从这个使用过程中看到，除了一次性能询问的数 $k$，剩下的数 $n-k$ 也是一个限制因素。

那么考虑最优策略（或者说能成功的策略）——最后只剩下偶数个数，数目记位 $y$，可以通过两次询问完成其中 $x$ 个数的询问，使用该策略 $\displaystyle \lceil {\frac{y}{x}} \rceil$ 次询问出这 $y$ 个数的异或和；剩下的依次询问过去，只覆盖一次（例如，$\{a_5,a_6,a_7\},\{a_8,a_9,a_{10}\}$）。那么就考虑如何减到这个数 $y$。这里就涉及到其他题解涉及到的奇偶性讨论：

1. 如果 $n$ 为奇数而 $k$ 为偶数，那么无论无何都减不到这个值。直接输出 ```-1```。

2. 其余情况均能减到我们所需的那个数 $y$。那么先减到 $n \mod k$，如果为奇数则加上一个 $k$ 使得变成偶数。若 $n,k$ 均为偶数那么余数必为偶数；如果 $k$ 为奇数那么一定可以通过加 $k$ 改变我们所得到的这个值的奇偶性。

这样我们就可以使用上面这个最优策略以最少的询问数达成要求。

（代码过丑就不放了）

---

## 作者：DPair (赞：0)

一道伪装成交互题的构造题，我们的输出和交互库的输出基本没有关系。。。

我们假设我们有一个数集，我们要做的是每一次选择 $k$ 个数，把不在数集内的移到数集内，在数集内的移出数集，要求用最小的次数使得原先在数集外的所有数全部进入数集内，这样子的话把交互库给出的所有输出异或起来就是我们最终要的答案

那么现在要做的就是构造一种方案，使得能够达成这个目标

不难发现对于一个状态，假设当前集合内有 $x$ 个数，那么这个状态离答案的距离只和这个 $x$ 有关

因此可行的状态数是 $O(n)$ 的，我们可以直接暴力连边，从一个可行状态开始，往所有后继的可行状态连边，然后跑 $0\rightarrow n$ 的最短路即可

然后考虑输出方案，不难发现我们可以在最短路的过程中记录前驱，然后从 $n$ 开始逆推，不难发现每一次入集的数的个数和出集的数的个数都是确定的，假设分别是 $c_1, c_2$

而具体哪些数出入集我们并不关心，因此随便取 $c_1$ 个当前在集合外的数和 $c_2$ 个当前在集合内的数改变状态即可，不难发现这样是对的

然后就做完了

```cpp
#include <cstring>
#include <cstdio>
#include <queue>
int ans = 0, n, k;
const int MAXN = 505;
struct DPair {int val, id; DPair(int val, int id) : val(val), id(id) {} inline bool operator< (const DPair &tmp) const{return val > tmp.val;}};
std::priority_queue < DPair > q;
const int INF = 0x3f3f3f3f;
int head[MAXN], e[MAXN * MAXN], nxt[MAXN * MAXN], cnt, dis[MAXN], pre[MAXN];
inline void add(int u, int v) { nxt[++ cnt] = head[u]; head[u] = cnt; e[cnt] = v; }
bool vis[MAXN];
inline void Dijkstra() {
    for(int i = 1;i <= n;++ i) dis[i] = INF;
    q.push(DPair(0, 0));
    while(!q.empty()) {
        const int x = q.top().id; q.pop();
        if(vis[x]) continue;
        vis[x] = 1; for (int i = head[x];i;i = nxt[i]) {
            if(dis[e[i]] > dis[x] + 1) {
                dis[e[i]] = dis[x] + 1; pre[e[i]] = x;
                q.push(DPair(dis[e[i]], e[i]));
            }
        }
    }
}
inline int mx(int x, int y) {return x > y? x : y;}
inline void init() {
    scanf("%d%d", &n, &k);
    for (int i = 0;i <= n;++ i) {
        for (int j = mx(0, k + i - n);j <= k && j <= i;++ j) {
            const int v = i - j + (k - j);
            if(v <= n && !vis[v]) { vis[v] = 1; add(i, v); }
        } memset(vis, 0, sizeof(vis));
    }
}
inline int abs(int x) {return x < 0? -x : x;}
void output(int x) {
    if(!x) return ;
    const int y = pre[x]; int r1 = (k + x - y) >> 1, r2 = k - r1;
    printf("?");
    for (int i = 1;i <= n;++ i) {
        if(vis[i] && r1) {
            printf(" %d", i);
            vis[i] = 0; -- r1;
        } else if(!vis[i] && r2) {
            printf(" %d", i);
            vis[i] = 1; -- r2;
        }
    } printf("\n"); fflush(stdout); int r;
    scanf("%d", &r); ans ^= r; output(y);
}

int main() { init();
    Dijkstra();
    if(dis[n] == INF) {
        printf("-1\n"); fflush(stdout);
        return 0;
    } memset(vis, 1, sizeof(vis));
    output(n); printf("! %d\n", ans); fflush(stdout);
}
```

---

## 作者：7KByte (赞：0)

比较有意思的交互构造题。

首先我们知道答案一定是查询的所有数的异或和。因为如果查询某个数而不在异或和内，那么去掉这次查询一定更优。如果在异或和内出现多次，等价于出现 $0$ 或 $1$ 次。

那么每次可以异或 $k$ 个数，这 $k$ 个数可以与当前异或和中的数重合。

不难设计状态 $f_{i,j}$ 表示是否有方案使用 $i$ 次询问，使得当前异或和中有 $j$ 个数。

那么我们枚举当前的询问与前面 $j$ 个数中有多少个重合即可得到 $\mathcal{O}(n^2k)$ 的转移。这已经足够通过这道题。

同时我们发现对于每个 $j$ 只用记录最早到达的 $i$ 即可，时间复杂度可以降至 $\mathcal{O}(nk)$ 。

构造答案的时候用两个栈维护在异或和内的数和不在异或和内的数，下面是 $\mathcal{O}(n^2k)$ 的代码。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 505
using namespace std;
int n,k,f[N][N],g[N][N],ans;
int s[N],T,sta[N],top,rub[N],tt;
void calc(){
	int cur=n;
	pre(i,ans,1){
		s[++T]=g[i][cur];
		cur-=k-s[T]*2;
	}
	int sum=0;
	rep(i,1,n)sta[++top]=i;
	pre(i,T,1){
		printf("? ");
		vector<int>w;
		rep(j,1,s[i])printf("%d ",rub[tt]),w.push_back(rub[tt--]);
		rep(j,1,k-s[i])printf("%d ",rub[++tt]=sta[top--]);
		rep(j,1,s[i])sta[++top]=w[j-1];
		cout<<endl;
		int x;cin>>x;
		sum^=x;
	}
	cout<<"! "<<sum<<endl;
}
int main(){
	scanf("%d%d",&n,&k);
	f[0][0]=1;
	rep(i,1,n){
		rep(j,0,n-1)if(f[i-1][j]){
			for(int w=0;w<=min(k,j);w++)if((n-j)>=(k-w)&&j+k-w*2<=n)
				f[i][j+k-w*2]=1,g[i][j+k-w*2]=w;
		}
		if(f[i][n]){
			ans=i;calc();return 0;
		}
	}
	puts("-1");
	return 0;
}
```

---

