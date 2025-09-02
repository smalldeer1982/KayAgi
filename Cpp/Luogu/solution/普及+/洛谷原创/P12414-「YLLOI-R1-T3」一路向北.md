# 「YLLOI-R1-T3」一路向北

## 题目背景

![一路向北](bilibili:BV1qg411H7qR)

## 题目描述

给定 $n$ 个队列，每个队列中有 $m$ 个正整数，这些数均小于等于 $n$，第 $i$ 个队列的第 $j$ 个元素为 $a_{i,j}$，$a_{i,1}$ 为队首，$a_{i,m}$ 为队尾。

现在你的手中拿着一个数字 $0$，你要选择一个队列将 $0$ 放到其队尾，并把其队首拿到手中。

接下来你将重复进行一个操作直到再次把 $0$ 拿回手中：

- 设你手中的数字为 $p$，将其放到第 $p$ 个队列的队尾，并把第 $p$ 个队列的队首拿到手中。

现在小 Y 想知道，在无限的时间中，你是否可以不再拿回 $0$？如果可以，则输出 `Yes`，否则输出 `No`。

## 说明/提示

#### 【样例解释#1】

以下模拟一开始将 $0$ 放到第 $1$ 个队列的情况。

```
//手中数字：
0
//队列数字：（左边第一个为队首，右边第一个为队尾）
2 2
3 3
1 1
```

```
//手中数字：
2
//队列数字：
2 0
3 3
1 1
```

```
//手中数字：
3
//队列数字：
2 0
3 2
1 1
```

```
//手中数字：
1
//队列数字：
2 0
3 2
1 3
```

```
//手中数字：
2
//队列数字：
0 1
3 2
1 3
```

```
//手中数字：
3
//队列数字：
0 1
2 2
1 3
```

```
//手中数字：
1
//队列数字：
0 1
2 2
3 3
```

```
//手中数字：
0
//队列数字：
1 1
2 2
3 3
```
#### 【样例解释#2】

通过模拟可以发现当且仅当一开始把 $0$ 放到第 $1$ 个队列时，才可以不再拿回 $0$。因为在经过了若干轮后第 $2$ 个队列会被 $2$ 填满，并且手中的数字也是 $2$，所以将在第 $2$ 个队列一直循环。

#### 【数据范围】

**本题采用捆绑测试。**

- Subtask 1（20 pts）：$n\le2$。
- Subtask 2（10 pts）：$\forall a_{i,j}=i$。
- Subtask 3（20 pts）：$n\times m \le 1000$。
- Subtask 4（50 pts）：无特殊限制。

对于全部数据，保证 $1\le T\le 10$，$1\le n\times m\le 10^5$，$1\le a_{i,j}\le n$。

## 样例 #1

### 输入

```
1
3 2
2 2
3 3
1 1```

### 输出

```
No```

## 样例 #2

### 输入

```
1
3 2
2 1
3 3
2 2```

### 输出

```
Yes```

# 题解

## 作者：lovelish (赞：38)

因为数字 $x$ 只能到第 $x$ 个队列，所以若出现循环，则只会是 $1$ 个队列在循环。

下面我们给出一个结论：

- 把 $0$ 放到第 $x$ 个队列，只要 $x$ 的总数量小于 $m$ 个，$0$ 就一定不会出队。

证明：因为当一个 $x$ 出现在 $0$ 后时，在 $0$ 出队前，这个 $x$ 就不可能出队。然而想要 $0$ 出队，至少需要有 $m$ 个 $x$ 入该队。证毕。

因此只要有任意一个 $x$ 的总数量小于 $m$，就一定可以不再拿回 $0$。如果想要使所有 $x$ 的总数量都大于等于 $m$，任意一个 $x$ 的总数量都一定为 $m$。

下面我们再给出一个结论：

- 当一个 $x$ 的总数量小于等于 $m$ 个时，第 $x$ 个队列一定不会循环。

证明：要想使第 $x$ 个队列循环，首先需要把该队列用 $x$ 填满，不然一定会到其他队列；并且手中还需要拿着 $x$，不然无法再进入该队列。因此至少需要 $m+1$ 个 $x$ 才可能使第 $x$ 个队列循环。证毕。

当不会有任何队列可能循环时，$0$ 就一定会被拿回手中。

因此，我们把所有情况分为了两种，一种为每个数字的总数量都为 $m$，该情况 $0$ 一定会被拿回，除此之外 $0$ 一定可以不再被拿回。

---

## 作者：_Auror_ (赞：3)

神秘结论题？莫名其妙地想了出来。

## 思路

设 $p_i$ 为第 $i$ 个队列的编号。

如果将 $0$ 放到队列 $i$ 的末尾，要想取到它，必须先将前 $m$ 个元素取出，而想取出这 $m$ 个元素，就需要全局都有 $m$ 个以上的 $p_i$，如果没有，则放 $0$ 一定放在该队列，因为取不完前 $m$ 个元素。

可能会有疑惑，如果有一种情况是一个队列 $p_j$ 里的元素都是 $p_i$ 且没有一种方式可以到 $p_j$ 这个队列，$p_i$ 可以进入循环但不会参与循环那怎么办？

这种情况的话，我们选的答案就不是在 $p_i$ 中放 $0$，而是选择在 $p_j$ 中放 $0$。

---

## 作者：_O_v_O_ (赞：3)

一种从数学角度的证明，这是我验题时的想法。

我们注意到最终，设手上拿着 $x$，那么第 $x$ 个队列一定全是 $x$。

那么有解的**必要条件**就是存在一个数出现过 $>m$ 次。

我们继续观察发现，我们放 $0$ 的队列的必要条件是一定最终被放进去过 $<m$ 次。

那么，有个**充分条件**就是，这个队列所对应的数在所有队列中出现的次数 $<m$ 次。**等价于**某个数在队列中出现了超过 $m$ 次。

那么充要条件就是某个数在队列中出现了超过 $m$ 次，直接判断即可。

---

## 作者：lyms_Hz17 (赞：3)

**大家好，我数学不好，所以我用 dfs 通过了这道题。**

观察题目，很容易发现其实就是给出了 $n$ 个双端队列，用一个 $0$ 作为“外来元素”进行题目所说的操作。所谓操作也就是将手中的现有元素 $has$ 加入到第 $has$ 个队列队尾并将队头元素弹出作为新的 $has$。如果 $0$ 在操作中永远不会出现就输出 Yes，否则输出 No。

**那这不就是 dfs 么。**

考虑直接用 $n$ 个双端队列模拟，每一个队列作为一个可能的起点，对于每一个情况进行搜索，定义一个 $inf$ 作为 $0$ 永不出现的临界值，一旦搜索数超过了 $inf$ 就直接输出 Yes，反之若每一个情况都遍历过也没能输出 Yes 则输出 No。
****
### 一些细节：

显然不可以用暴力赋值来开启每一次的搜索（像这样）：
```cpp
for(int i=1;i<=n;i++){
    not0=0;
    for(int i=1;i<=n;i++)//这个循环是罪魁祸首，n^2的赋值比代码主体都慢。
        a[i]=b[i];
    a[i].push_back(0);
    int aaa = a[i].front();
    a[i].pop_front();
    if(dfs(aaa)){
        ender=1;
        cout<<"Yes"<<'\n';
        break;
    }
}
```
会 TLE。

可以直接将双端队列作为参数传入函数，省去大量的赋值，可以 AC。

****
### 完整代码：

```cpp
// code by 樓影沫瞬_Hz17
#include <bits/stdc++.h>
using namespace std;
int in();
typedef deque<int> deq;
int n, m, not0;
deq b[100100];

bool dfs(int has, deq a[]) {// 搜索的主体
    not0++;
    if (has == 0)// 0回到了手里
        return 0;
    if (not0 > 100000)// 100000也就是上文说的 inf (已经最优，少 1 都不行，同一个机房的dalao有证明出来为什么是 100000 的，但我不会)。
        return 1;
    a[has].push_back(has);
    int tem = a[has].front();
    a[has].pop_front();
    return dfs(tem, a);
}

bool work(int i, deq a[]) {// 每次搜索的起点
    not0 = 0;
    a[i].push_back(0);
    int tem = a[i].front();
    a[i].pop_front();
    return dfs(tem, a);
}

int main() {
    int T;
    T = in();
    while (T--) {
        n = in(), m = in();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                b[i].push_back(in());
        bool ender = 0;
        for (int i = 1; i <= n; i++)
            if (work(i, b)) {// 直接传参，不然会 TLE
                ender = 1;
                cout << "Yes\n";
                break;
            }
        if (!ender)// 没有输出过 Yes
            cout << "No\n";
        for (int i = 1; i <= n; i++)
            b[i].clear();// 多测不清空，__________。
    }
    return 0;
}
int in() {// 快读
    int n = 0, f = 0, c = getchar_unlocked();
    while (c <= '-')
        f = f ? 1 : c == '-', c = getchar_unlocked();
    while (!(c < '0' || c > '9'))
        n = (n << 1) + (n << 3) + (c ^ 48), c = getchar_unlocked();
    return f ? -n : n;
}
```

---

## 作者：OrinLoong (赞：2)

## LGP12414 [YLLOI R1] 一路向北 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/P12414)

### 前言
有段时间没做洛谷绿题了，来一道。

鉴定为趣题。出得挺好！

### 题意简述
给定 $n$ 个队列。每个队列一开始有 $m$ 个正整数，第 $i$ 个队列的第 $j$ 个元素记为 $a_{i,j}$。其中 $a_{i,1}$ 为队首，$a_{i,m}$ 为队尾。

现在你手中有一个数字 $0$。你要选择一个队列将 $0$ 放到队尾，并将其队首拿到手中。

接下来你将不断重复这个操作直到再次拿到 $0$：
+ 设你手中的数字为 $p$。将其放到第 $p$ 个队列的队尾，并将其队首拿在手中。

问能不能在无限长的时间内不再次拿到 $0$。多测，共 $T$ 组数据。

$T\le 10$，$n\times m\le 10^5$。

### 做法解析
你尝试手玩了些数据模拟，但一时半会没看出端倪，所以你考虑逆向思维。

考虑什么时候我们会再次拿到 $0$。更具体的，考虑到我们拿到 $0$ 的那一瞬间发生了什么。

设一开始把 $0$ 放在了序列 $k$，则在我们手中拿着一个 $k$ 并且 $0$ 在 $k$ 的队头的那一刻，我们就再次拿到了 $0$。

沿着这个场景进一步想，$0$ 一开始在队尾，现在又在队头，这说明在我们开局操作之后我们又来了这 $m$ 次，$m-1$ 次是来拿 $0$ 前面的元素的，第 $m$ 次是来拿 $0$ 自己的。你再想，我们每次来队列 $k$ 都需要手上拿着一次 $k$，而且这个 $k$ 会被放到 $0$ 后面不能再用，所以说如果开局把 $0$ 放到 $k$ 可以再次拿到 $0$，那么全场至少得有 $m$ 个 $k$。

所以反之，如果有某种元素 $c$ 出现次数小于 $m$，我们开局把 $m$ 放到 $c$ 就可以不拿到 $0$。我们得到了一个可以无限持续下去游戏的充分判定。

令人惊喜的，这也是必要判定。因为在无限长的时间内，所有元素都会趋向于回到自己编号的队列，而如果没有任何元素的出现次数小于 $m$，就意味着每种元素都出现了 $m$ 次，那么它们一定都会趋向于回到自己所属编号的队列而把场上所有队列挤满，你最后就一定会拿到 $0$。（作为对比，当我们可以无限进行游戏的时候，$0$ 会苟在一个没被 $k$ 号元素占满的队列 $k$，然后手上拿的东西独立于 $k$ 号队列无限循环进行游戏）

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
using namespace obasic;
const int MaxN=1e5+5;
int N,M,X,buc[MaxN];
void mian(){
    readis(N,M),fill(buc,buc+N+1,0);
    for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)readis(X),buc[X]++;
    for(int i=1;i<=N;i++)if(buc[i]<M){puts("Yes");return;}
    puts("No");
}
int Tcn;
int main(){
    readi(Tcn);
    while(Tcn--)mian();
    return 0;
}
```

---

## 作者：Meteor1212 (赞：1)

## 1.题意分析

给定 $n$ 个队列，每个队列长度均为 $m$，队列中的元素均为 $1$ 到 $n$ 的正整数。初始手中有数字 $0$，你可以先选一个队列，将手中的数字放到该队列队尾，并取出队首数字中，不断重复这个操作。位是否存在一种初始选择，使得在无限操作中手中永远不会再取到 $0$。

## 2.题目分析
我们发现除了初始放入的 $0$ 后来拿到手中的数字一定来自原始的那些正整数中。

通过观察样例二
```
1
3 2
2 1
3 3
2 2
```
```
Yes
```
此时可以不再拿回 $0$。因为选择第一个队列放入 $0$ 时经过若干次操作第二个队列会被 $2$ 填满并且手上拿的数字也是 $2$，导致不断循环最终无法将 $0$ 取出。

1. 由此我们可以发现如果能使操作一直处于循环状态那么 $0$ 将永远不会被取出。而想要使操作处于循环状态就需要某数字 $x$ 的全局出现次数 $>m$，若要将队列循环需要先将队列填满 $x$ 并且手中拿的数字也必须是 $x$，从此陷入循环，不会再出现 $0$。
2. 那为什么存在一个其他的队列把 $0$ 放进去并不会被取出。因为如果某数字的总个数 $>m$，那么一定有某数字的总个数 $<m$，此时将 $0$ 放入这个队列中，那么 $0$ 从队尾依次往前移动需要这个数 $x$ 不断在其后面添加将 $0$ 向前推动因为总个数 $<m$，所以不会将 $0$ 挤出。

综上：只要满足某数字 $x$ 的全局出现次数 $>m$ 则不再拿到 $0$。

## 3. 代码实现
统计每个数字出现的次数即可。
```
#include <bits/stdc++.h> 
using namespace std; 
const int N=1e6+10;
int sum[N];
int main() 
{ 
	ios::sync_with_stdio(false); 
	cin.tie(0); 
	int n,m,t;
	cin>>t;
	while(t--)
	{
		memset(sum,0,sizeof sum);
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				int a;
				cin>>a;
				sum[a]++;
			}
		}
		int maxn=-1;
		for(int i=1;i<=n;i++)
		{
			maxn=max(maxn,sum[i]);
		}	
		if(maxn>m)
		{
			cout<<"Yes"<<endl;
		}
		else cout<<"No"<<endl;
	}
	return 0; 
}
```
时间复杂度 $O(Tnm)$。

---

## 作者：FeelGood (赞：1)

提供一个与其他题解不一样的做法。

题目的操作比较复杂，直接分析比较麻烦。

发现可以将问题转化为图论，将 $n$ 个队列看作 $n$ 个点，而队列中的数 $a_{i, j}$ 看作 $i \to a_{i, j}$ 的有向边，那么每次操作就相当于走一条边，并将其断开。

接下来考虑是否会重新取回 $0$。

重边没有意义忽略，发现如果走完一个点所有的出边后，还会回到自己，那么就一定会取回 $0$，这种情况就是欧拉回路。

证明：如果从一个点出发，无法回到自己时，就一定会停留在某个点上，设这个点为 $p$。那么在最后一次进入之前，有 $in_p = out_p$，进入后无法离开，又说明 $in_p > out_p$，这与 $in_p = out_p$ 矛盾，所以不存在这样的点。

否则，一定可以找到一个点，最终无法回到自己，从这个点开始操作即可。

那么就只要判定欧拉回路即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lll __int128

using namespace std;

namespace Solve
{
	const int N = 1e5;
	
	int in[N + 5], out[N + 5];
	
	void Sol()
	{
		int t;
		scanf("%d", &t);
		while (t--)
		{
			int n, m;
			scanf("%d%d", &n, &m);
			for (int i = 1; i <= n; ++i) out[i] = in[i] = 0;
			for (int i = 1; i <= n; ++i)
			{
				for (int j = 1; j <= m; ++j)
				{
					int p;
					scanf("%d" ,&p);
					if (p == i) continue;
					++out[i];
					++in[p];
				}
			}
			bool flg = false;
			for (int i = 1; i <= n; ++i)
			{
				if (in[i] != out[i])
				{
					flg = true;
					break;
				}
			}
			if (flg == false) puts("No");
			else puts("Yes");
		}
	}
}

using Solve::Sol;

int main()
{
	Sol();
	return 0;
}
```

---

## 作者：All_Wrong_Answer (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12414)

## 思路：

考虑暴力。

枚举把 $0$ 放在哪一个队列中开始，用双端队列暴力模拟当前手上的数和每个队列中的数。

注意到每一个数只能进队出队一次，不然肯定是循环了,因为它第一次出队进队后就处在编号为它的数值的队列中了，第二次出队后再进队仍然是在同一个队列中，相当于把一个数弹出来又压了回去，所以直接给 ```DFS``` 设一个搜索上限，即 $2 \times n \times m=200000$，在 O2 下 [403ms](https://www.luogu.com.cn/record/227576780) 通过了此题。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read() {
	long long x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
void out(long long x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else out(x/10),putchar(x%10+'0');
}
int t,n,m;
deque<int>q[100005];

bool dfs(int mq,int u,deque <int>p[],int k){
	//cout<<"   "<<mq<<" "<<u<<"\n";
	if(u>200000) return false;
	if(mq==0&&u!=1) return true;
	if(u==1){
		p[k].push_back(mq);
		int g=p[k].front();
		p[k].pop_front();
		return dfs(g,u+1,p,k);
	} 
	p[mq].push_back(mq);
	int g=p[mq].front();
	p[mq].pop_front();
	return dfs(g,u+1,p,k);
}



int main() {
	t=read();
	while(t--) {
		n=read();
		m=read();
		for(int i=1;i<=n;i++){
			q[i].clear();
			for(int j=1;j<=m;j++){
				int a=read();
				q[i].push_back(a);
			}
		}
		int flag=0;
		for(int i=1;i<=n;i++){
			if(dfs(0,1,q,i)==false){
				cout<<"Yes\n";
				flag=1;
				break;
			}
		}
		if(flag==0) cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：CaiZi (赞：1)

首先发现，若某个数 $p$ 的个数 $<m$，且你把 $0$ 放在队列 $p$ 的末尾，那么永远无法再次拿到 $0$，因为至少要拿到 $m$ 次 $p$ 才能再次拿到 $0$（最开始队列 $p$ 的队首已经被拿到过一次）。

因此当有存在某个数的个数 $<m$ 时，输出 ```Yes```。

于是此时只剩下每个数的个数均 $=m$ 的情况。这种情况下，我们最终一定会在若干个队列中反复横跳，且这些队列中包含放着 $0$ 的队列，因为由前面的结论可以知道，不可能在没有放着 $0$ 的队列中不断循环。

因此对于其余情况，输出 ```No```。

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,x,a[100001];
bool b;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>t;
	while(t--){
		b=0;
		cin>>n>>m;
		fill(a+1,a+n+1,0);
		for(int i=1;i<=n*m;i++){
			cin>>x;
			a[x]++;
		}
		for(int i=1;i<=n;i++){
			if(a[i]<m){
				b=1;
			}
		}
		if(b){
			cout<<"Yes\n";
		}
		else{
			cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：redfull66 (赞：0)

将 $i$ 的个数记作 $d_i$，注意到若 $d_k<m$，且你把 $0$ 放在队列 $k$ 的末尾，$0$ 就一定不会出队，因为至少要拿到 $m$ 次 $k$ 才能再次拿到 $0$，然而一共只有 $d_k$ 个 $k$。

又注意到若 $d_k \le m$，第 $k$ 个队列一定不会循环，原因与上文类似（即队列 $k$ 中有 $m$ 个 $k$ 且手中还有 $1$ 个 $k$ 共 $m+1$ 个 $k$ 才会循环），则当且仅当对于任意 $1 \le k \le n$，$d_k=m$ 时输出 `No`，其余输出 `Yes`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a,n,m,ans,d[100005];
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m,ans=0,memset(d,0,sizeof(d));
		for(int i=1;i<=n*m;i++)cin>>a,d[a]++,ans+=(d[a]>m);
		cout<<(ans?"Yes":"No")<<endl;
	}
	return 0;
}

```

---

## 作者：Wy_x (赞：0)

一种疑似卡不掉的暴力解法。

我们很容易想到暴力怎么做，枚举将 $0$ 放在哪个队列后面，然后就是纯模拟。

考虑乱搞优化。

当 $0$ 放在队列 $i$ 后面时，设我们操作 $cnt$ 次，我们进行过操作的所有块的大小和为 $siz$。

有一个结论：当 $cnt > siz$ 时无解。

好像是因为我用函数，函数 check 时不用再复制一遍 queue，导致复杂度低。


### Code：

```cpp
#include<bits/stdc++.h>
// #define int long long

using namespace std;

const int Size=(1<<20)+1;
char buf[Size],*p1=buf,*p2=buf;
char buffer[Size];
int op1=-1;
const int op2=Size-1;
#define getchar()                                                              \
(tt == ss && (tt=(ss=In)+fread(In, 1, 1 << 20, stdin), ss == tt)     \
	? EOF                                                                 \
	: *ss++)
char In[1<<20],*ss=In,*tt=In;
inline int read()
{
	int x=0,c=getchar(),f=0;
	for(;c>'9'||c<'0';f=c=='-',c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c^48);
	return f?-x:x;
}
inline void write(int x)
{
	if(x<0) x=-x,putchar('-');
	if(x>9)  write(x/10);
	putchar(x%10+'0');
}

int n,m;

bool check(queue<int> q[],int i)
{
    // bool f[n+1]={};
    // const unsigned  siz=n+1;
    bitset<100001> f;
    int nw=q[i].size()+1;
    int cnt=0;
    q[i].push(0);

    while(cnt<nw)
    {
        int to=q[i].front();
        q[i].pop();
        if(to==0) return 0;
        if(!f[to]) nw+=q[to].size(),f[to]=1;// siz+=m
        cnt++;
        q[to].push(to);
        i=to;
    }
    return 1;
}

void solve()
{
    n=read();
    m=read();
    queue<int> q[n+1];
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    q[i].push(read());

    for(int i=1;i<=n;i++)
    {
        if(check(q,i))
        {
            puts("Yes");
            return;
        }
    }
    puts("No");
}

signed main()
{
    int T=read();
    while(T--) solve();
    // cout<<"No\n";
	//mt19937_64 myrand(time(0));
	return 0;
}

```

---

## 作者：jiangyunuo (赞：0)

### 题目分析
给定 $t$ 组数据，每组数据包括 $n$ 和 $m$，以及 $n$ 个队列（每个队列 $m$ 个元素）。每次操作：从手上为 $0$ 开始，选择一个队列，将当前数字放入队列尾部，并取出队列头部作为新数字。问是否存在操作序列，使得最终 $0$ 能回到手中。
### 解题思路

#### 关键观察：
通过分析数字的出现次数与队列长度的关系，可以得出以下结论：

1. 若存在某个数字 $i$（$1 \leq i \leq n$）在所有队列中的出现总次数小于 $m$，则答案为 `Yes`（存在操作序列回到 $0$）。

2. 若所有数字 $i$（$1 \leq i \leq n$）的出现次数均为 $m$，则答案为 `No`（不存在操作序列回到 $0$）。

#### 证明：

1. 假如数字 $x$ 的数量小于 $m$ 时，我们将数字 $0$ 放入一个队列 $x$，之后，要想取出来，就需要不断往这个队列里加入数字 $x$，在 $0$ 之后肯定只有 $x$，这个看题目可以看出来，如果 $x$ 的数量比 $m$ 小的话，$x$ 的数量就不足以将 $0$ 送出队列。注：如果数字 $y$ 的数量大于 $m$ 其实也是这种情况，毕竟除 $0$ 以外的其他 $n$ 种数字之和为 $n \times m$，显然，有一种数字多了，就必有一种数字少了。
2. 假如所有种类的数字数量都为 $m$ 时，$0$ 必定会回来。利用反证法，假若我们无法拿回 $0$，手上必有另一个数字，我们就叫它数字 $a$。数字 $a$ 的数量为 $m$，但是缺少这个数字 $a$，它所对应的队列并不是由数字 $a$ 所填满的，因此我们将其插入这个队列时就会得到一个新的数字，依旧是一样的思路。最终，所有队列一定会被其相应的数字填满，而此时 $0$ 就在我们手上。

### 代码实现

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	int n,m;
	bool z; // 标记是否已输出 Yes。
	while(t){
		t--;
		z=0;
		cin>>n>>m;
        int a[n+1][m+1]={}, b[n+1]={};  // a 存储队列，b 统计数字出现次数。
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				b[a[i][j]]++;  // 更新数字出现次数。
			}
		}
		// 检查数字 1 至 n 是否均出现 m 次。
		for(int i=1; i<=n; i++){
			if(b[i]<m){
				cout<<"Yes"<<endl;
				z=1; // 标记已输出。
				break;
			}
		}
		if(z==0)cout<<"No"<<endl;
	}
	return 0;
}
```

### 复杂度分析
时间复杂度：$O(t \cdot n \cdot m)$，每组数据遍历队列一次。

空间复杂度：$O(n \cdot m)$，存储队列。

---

