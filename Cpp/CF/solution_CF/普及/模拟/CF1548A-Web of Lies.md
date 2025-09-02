# Web of Lies

## 题目描述

When you play the game of thrones, you win, or you die. There is no middle ground.

Cersei Lannister, A Game of Thrones by George R. R. Martin



There are $ n $ nobles, numbered from $ 1 $ to $ n $ . Noble $ i $ has a power of $ i $ . There are also $ m $ "friendships". A friendship between nobles $ a $ and $ b $ is always mutual.

A noble is defined to be vulnerable if both of the following conditions are satisfied:

- the noble has at least one friend, and
- all of that noble's friends have a higher power.

You will have to process the following three types of queries.

1. Add a friendship between nobles $ u $ and $ v $ .
2. Remove a friendship between nobles $ u $ and $ v $ .
3. Calculate the answer to the following process.

The process: all vulnerable nobles are simultaneously killed, and all their friendships end. Then, it is possible that new nobles become vulnerable. The process repeats itself until no nobles are vulnerable. It can be proven that the process will end in finite time. After the process is complete, you need to calculate the number of remaining nobles.

Note that the results of the process are not carried over between queries, that is, every process starts with all nobles being alive!

## 说明/提示

Consider the first example. In the first type 3 query, we have the diagram below.

In the first round of the process, noble $ 1 $ is weaker than all of his friends ( $ 2 $ and $ 3 $ ), and is thus killed. No other noble is vulnerable in round 1. In round 2, noble $ 3 $ is weaker than his only friend, noble $ 4 $ , and is therefore killed. At this point, the process ends, and the answer is $ 2 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1548A/eccd6f0add10562eaeff6f7302fe13d3e1f9be51.png)In the second type 3 query, the only surviving noble is $ 4 $ .

The second example consists of only one type $ 3 $ query. In the first round, two nobles are killed, and in the second round, one noble is killed. The final answer is $ 1 $ , since only one noble survives.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1548A/af37f9a008f1a978239a03ac88fceea275d5859b.png)

## 样例 #1

### 输入

```
4 3
2 1
1 3
3 4
4
3
1 2 3
2 3 1
3```

### 输出

```
2
1```

## 样例 #2

### 输入

```
4 3
2 3
3 4
4 1
1
3```

### 输出

```
1```

# 题解

## 作者：Gokix (赞：32)

[CF1548A](https://www.luogu.com.cn/problem/CF1548A)

个人感觉自己的做法比较简单。

------------

我们先不管 1 操作和 2 操作，来看 3 操作。

考虑什么人最后能活。

1. **没有朋友的人一定能活。**

2. **如果一个人的直接朋友都比自己弱，那这个人就能活下来。** 原因是这个人的直接朋友都会比自己先挂，然后这个人就成为 1 情况。

考虑什么人最后会挂：

**存在至少 1 个直接朋友比自己强。**

于是我们想看最后会有多少人能活只需要维护每个人比自己强的直接朋友的个数就好了，记为 $out_i$。同时注意到我们并不需要每次 3 操作的时候都看一遍 $out_i$，只需要记录一下有多少个 $i$ 使得 $out_i=0$ 即可，记作 $ans$。1 操作的时候就把弱的那个人的 $out$ 加 1，同时更新 $ans$；同理，2 操作的时候只需要把弱的那个人的 $out$ 减 1，同时更新 $ans$。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

long long n,m,t,out[200050],ans;

int main(){
    long long i,j,u,v;
    cin>>n>>m;
    ans=n;//一开始都能活
    while(m--){
        cin>>u>>v;
        if(u>v) swap(u,v);
        if(out[u]==0) ans--;
        out[u]++;
    }
    cin>>t;
    while(t--){
        cin>>j;
        if(j==1){
            cin>>u>>v;
            if(u>v) swap(u,v);
            if(out[u]==0) ans--;
            out[u]++;
        }
        if(j==2){
            cin>>u>>v;
            if(u>v) swap(u,v);
            out[u]--;
            if(out[u]==0) ans++;
        }
        if(j==3){
            cout<<ans<<endl;
        }
    }
    return 0;
}
```


---

## 作者：xiaoxiaoxia (赞：4)

# Part 1 思路分析
题目大意不难理解，在这里只需要注意一些细节。在加边时，只有当 $cnt_{min}$ 的值为 $1$ 时答案才应该减 $1$，而不是当 $cnt_{min}$ 的值大于等于 $1$ 时答案都应该减 $1$，这是因为在加边后，如果 $cnt_{min}$ 的值为 $1$ 说明在加边前 $cnt_{min}$ 的值为 $0$，意思是在加边前 $min$ 这个人没有被杀的风险，但是在加边后 $min$ 这个人有了被杀的风险，答案应该减1。这也就是为什么只有当 $cnt_{min}$ 的值为 $1$ 时答案才应该减 $1$，如果当 $cnt_{min}$ 的值大于等于 $1$ 时答案都减 $1$ 的话，就重复计算了好多次，意思是 $\min$ 这个人被杀死了好多次，但实际上一个人只能被杀死一次。同理，在去边时，当 $cnt_{min}$ 的值为 $0$ 时答案才应该加 $1$，这是因为在去边后，如果 $cnt_{n}$ 的值前 $cnt_{min}$ 的值为 $1$，意思是在去边前 $\min$ 这个人有被杀的风险，但是在去边后 $\min$ 这个人没有了被杀的风险，答案应该加 $1$。
# Part 2 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
int cnt[N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    while(m--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        cnt[min(u,v)]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
    	if(cnt[i]==0)
    	{
    		ans++;
		}
	}
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int x;
        scanf("%d",&x);
        if(x==1)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            cnt[min(u,v)]++;
            if(cnt[min(u,v)]==1)
                ans--;
        }
        if(x==2)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            cnt[min(u,v)]--;
            if(cnt[min(u,v)]==0)
                ans++;
        }
        if(x==3)
        {
        	printf("%d\n",ans);
		}
    }
    return 0;
}

```


---

## 作者：Sora1336 (赞：4)

### 题目描述

给你一个 $n$ 个点 $m$ 条边的无向图，要求支持以下几种操作共 $q$ 次：

- 加入一条边 $(u,v)$。
- 删除一条边 $(u,v)$。
- 查询按照以下步骤对图进行操作后剩下的点的数量：删除所有与其相连的点编号都比其大的点和与该点相连的边，然后再次进行操作，直到删除点的数量为 $0$ 为止。（该查询对图的结构不影响）

数据范围：$1 \le n,q \le 2\cdot 10^5, 0 \le m \le 2\cdot 10^5$ 。

### 结论

对于每一个点，只要有任意相邻的点编号大于它，那么该点一定会在最后一轮前被删除。

### 证明

采用反证法。假如一个有一个相邻点编号大于它，且其存活到了最后一轮。那么其必有一个相邻点小于它。其相邻点若没有编号比其更小的，那么其会在本轮被删除，那本轮不为最后一轮。其相邻点若有编号比其更小的，同样的逻辑也适用于该点。这样我们得到一个无限下降的论证，但编号小于起始点的点数量是有限的，所以产生了矛盾。得证。

### 代码实现

由于正常邻接表的边删除操作不是 $O(1)$ 的，所以不能使用邻接表。

我们可以考虑使用一个叫 `alive` 的数组来存储 “比编号为 $i$ 的点编号大的其邻居的数目”，再使用一个变量 `ans` 存储每次询问的答案，由于初始所有点都是不连通的，那么 `ans` 初始化为 $n$。

- 假如一个点加边后有且仅有一个相邻的点编号大于它，答案就减少 $1$。
- 假如一个点删掉与它相邻且唯一的编号大于它的点，答案就增加 $1$。

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 2e5 + 5;
int alive[maxn], n, m;

int main() {
	cin >> n >> m;
	int ans = n;
	for(int i = 1, x, y; i <= m; i ++) {
		cin >> x >> y;
		if(x > y) { 
			alive[y] ++; 
			if(alive[y] == 1)  ans --; 
		} else { 
			alive[x] ++; 
			if(alive[x] == 1)  ans --; 
		}
	}
	int q;
	cin >> q;
	while(q --) {
		int cmd, x, y;
		cin >> cmd;
		if(cmd == 1) {
			cin >> x >> y;
			if(x > y) {          // when x is stronger than y
				alive[y] ++;       // y's dangerous friend ++
				if(alive[y] == 1) ans --;   // if this is the first dangerous friend, answer --;
			} else { 
				alive[x] ++; 
				if(alive[x] == 1) ans --; 
			}
		} else if(cmd == 2) {
			cin >> x >> y;
			if(x > y) { 
				alive[y] --; 
				if(alive[y] == 0) ans ++; 
			} else { 
				alive[x] --; 
				if(alive[x] == 0) ans ++; 
			}
		} else {
			cout << ans << endl;
		}
	}
}
```

---

## 作者：XL4453 (赞：3)


### 题目分析：

考虑这样的一个结论：每一个有编号比自己大的点的邻居的点一定会被删掉，每一个 3 询问就是询问有多少个点是比其所有的相邻点的编号大的。

这样的一个结论是成立的，可以由反证法证明：假设当前还有至少一个点与编号比自己大的点有连边，那么这样一个点没有被删掉一定是因为有至少一个比自己编号小的点与之连边。而这样的一个编号比自己小的点其实又是另一个“与编号比自己大的点连边的点”，他没有被删掉肯定又是因为有编号更小的点与之连边。以此类推，发现由于点的数目有限，这样的一个情况肯定不可能是无限进行下去的，所以肯定会在某一个时刻将所有的与编号比自己大的点连边的点全部删去。

然后是如何实现的问题，直接建立图的复杂度是 $O(n^2)$ 的，无法接受。重新观察题目，发现题目中给出了这样的一个条件：不存在重边，且删除的边一定存在。发现其实并不需要真的记录下某一个点到底和谁连了边，只需要记录这个点和几个比他大的点连了边就行了。

------------
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,T,x,y,cnt[200005],ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		if(x>y)swap(x,y);
		cnt[x]++;
		if(cnt[x]==1)ans++;
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d",&x);
		if(x==1){
			scanf("%d%d",&x,&y);
			if(x>y)swap(x,y);
			cnt[x]++;
			if(cnt[x]==1)ans++;
		}else
		if(x==2){
			scanf("%d%d",&x,&y);
			if(x>y)swap(x,y);
			cnt[x]--;
			if(cnt[x]==0)ans--;
		}else printf("%d\n",n-ans);
	}
	return 0;
}
```



---

## 作者：Atserckcn (赞：3)

## Web of Lies 题解

[洛谷](https://www.luogu.com.cn/problem/CF1548A)。

[Codeforces](https://codeforces.com/problemset/problem/1548/A)。

题意比较直接，就不复述了。

### 思路

#### 分析题意

首先根据操作 $3$，删人只是暂时的，可以分析出每次删的人对于后面都没有影响。

关注到这个词：

> 执行以下操作直至不可再执行为止。

显然，在整个图中所有该被删除的人都逃不掉，迟早被删除。

那么看看什么样的神犇才能从操作 $3$ 中存活下来？

+ 没朋友的人可以。（这很显然）
+ 在所有朋友中，他是最强的一个。这样的话，他的所有朋友都会比他早归西，他也就没了朋友，可以当作第一种情况看待。

这么说来，这道题还挺富含哲理的……

当你最孤独，没朋友就能活下来。

当你在你朋友中是最强的，他们归西了，你还苟着。

当你的某个朋友比你强，你就得卒。

可以考虑用一个数组 $e$ 来记录。$e_i$ 表示第 $i$ 个人有几个**比他强的朋友**。

#### 现在看看操作

##### 加边

当你交了一个朋友，会怎么样呢？

分下情况：

若他比你弱，啥事也没发生。

若他比你强，交了这个朋友会把你害死。必死无疑。$e_i+1$。答案 $+1$。

##### 删边

若他比你弱，也是什么事都没发生。

比你强：

如果你只有这一个比你强的朋友，即 $e_i=1$，那么恭喜你，你跟他绝交，你活了下来。

如果你不止他一个，那你目前还得死。不过 $e_i$ 可以减一。这样以后再绝交几个就可以活了。

##### 询问

直接输出答案即可。

### Code

```cpp
//wrote by Atserckcn
#include<bits/stdc++.h>
using namespace std;
#define ljl long long
const ljl N=2e5+5,M=2e5+5;
ljl n,m,q,u,v,ans/*ans 即为答案*/,op,e[N];
struct EDGE{
	void solve1(ljl from,ljl to)//加边
	{
		ljl minn=(ljl)min(from,to);//选取主角：弱的那个
		if(!e[minn])//交了个比你强的朋友，很遗憾，你目前得死
			--ans;
		e[minn]++;
		return;
	}
	void solve2(ljl from,ljl to)//删边
	{
		ljl minn=(ljl)min(from,to);//找主角
		if(e[minn]==1)//你只有一个比你强的朋友，恭喜你，你能活着
			++ans;
		--e[minn];
		return;
	}
}edge;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	ans=n;
	for(ljl i=1;i<=m;++i)
	{
		cin>>u>>v;
		edge.solve1(u,v);
//		cout<<"----------"<<ans<<'\n';
	}
	cin>>q;
	while(q--)
	{
		cin>>op;
		if(op==1)
		{
			cin>>u>>v;
			edge.solve1(u,v);
			continue;
		}
		if(op==2)
		{
			cin>>u>>v;
			edge.solve2(u,v);
			continue;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/1548/297675803)。

---

## 作者：Gongyujie123 (赞：2)

## [CF1548A](https://www.luogu.com.cn/problem/CF1548A)
### 题目描述
有 $n$ 个人，编号从 $1$ 到 $n$ ，有 $m$ 条友谊，分别表示编号 $a$ 和 $b$ 的友谊。

对于每一个人，满足下面两个条件，他就被定义为脆弱的：
- 这个人至少有一个朋友。
- 他的所有朋友编号都比他**大**。

现在有 $q$ 次操作：
1. **添加**编号 $u$ 和 $v$ 之间的友谊。
2. **删除**编号 $u$ 和 $v$ 之间的友谊。
3. 将所有脆弱的人同时被杀死，他们的友谊关系将全部**结束**。然后，可能会有新的人变得脆弱。这个过程不断重复，直到没有人变得脆弱。过程结束后，输出**剩余的人数**。

注意：每次操作开始时，**所有**的人都还**活着**。

---
### 题目分析
我们观察操作 3，发现当一个人**至少有一个比他编号大**的朋友时，他**不可能活下来**。也就是说，当一个人**是他的朋友中编号最大**的人，他**一定能活下来**。

所以，我们用一个数组来存储**每个编号的人有多少个朋友的编号比他大**。

---
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main(){
	int n,m;
	cin>>n>>m;
	int ans=n;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(x<y){
			a[x]++;
			if(a[x]==1) ans--;
		}else{
			a[y]++;
			if(a[y]==1) ans--;
		}
	}
	int q;
	cin>>q;
	for(int i=1;i<=q;i++){
		int t;
		cin>>t;
		if(t==1){
			int x,y;
			cin>>x>>y;
			if(x<y){
				a[x]++;
				if(a[x]==1) ans--;
			}else{
				a[y]++;
				if(a[y]==1) ans--;
			}
		}else if(t==2){
			int x,y;
			cin>>x>>y;
			if(x>y){
				a[y]--;
				if(a[y]==0) ans++;
			}else{
				a[x]--;
				if(a[x]==0) ans++;
			}
		}else{
			cout<<ans<<endl;
		}
	}
	return 0;
}
```
---
**感谢您的观看！谢谢！**

---

## 作者：NXYorz (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1548A)

--------
### 题目大意
有 $n$ 个贵族，第 $i$ 个贵族拥有的权力是 $i$，他们之间相互有朋友联系。定义一个贵族成功的标志为：

- 至少有一个朋友
- 在所有朋友中他自己的权力最小。

对于每次询问，都会将把所有的成功贵族杀掉，他与朋友间的联系也将取消。重复上述过程，直到没有成功贵族为止，输出剩余贵族人数。

每次询问不相干，即询问过后死掉的贵族将复活，其与朋友间的联系恢复。

--------

### 分析
可撤销并查集？~~省省叭您。~~

发现对于每一个贵族来说，如果他的直系朋友中存在比他权力大的贵族，那么这个贵族一定不会存活。换句话说，如果一个贵族在他的直系朋友圈中权力最大，那么他一定存活

注：这里的直系朋友指直接向连的。

因此只需要记录每一个贵族有几个权力比其大的直系朋友，一开始 $n$ 个贵族肯定都会存活，如果某权力比其大的直系朋友数大于零了，那么他就会死。如果减为零了，那么他就不会死了。

--------
### $\texttt{Code}$
```cpp
#include<cstdio>

using namespace std;

const int N = 2e5 + 10;

int n,m,q,ans;
int sum[N];

void swap(int &x , int &y)
{int c = y ; y = x ; x = c;}

int main()
{
 //   freopen("aa.in","r",stdin);
    scanf("%d%d",&n,&m); ans = n;
    for(int i = 1; i <= m; i++)
    {
        int ui , vi; scanf("%d%d",&ui,&vi);
        if(ui > vi) swap(ui , vi);
        if(!sum[ui]) ans--; sum[ui]++;
    }
    scanf("%d",&q);
    for(int i = 1; i <= q; i++)
    {
        int op , ui , vi;
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                scanf("%d%d",&ui,&vi);
                if(ui > vi) swap(ui , vi);
                if(!sum[ui]) ans--; sum[ui]++;
                break;
            case 2:
                scanf("%d%d",&ui,&vi);
                if(ui > vi) swap(ui , vi);
                sum[ui]--; if(!sum[ui]) ans++;
                break;
            case 3:
                printf("%d\n",ans);
                break;
            break;
        }
    }
}
```

---

## 作者：Florrer_A (赞：1)

## 解题思路

显然的，每个连通块里，最后只会存活一个人。

我们定义一个数组 $a_i$ 表示第 $i$ 个人的朋友里强度比他高的有几个。那么对于一次 $3$ 操作而言，每个 $a_i$ 大于 $0$ 的人必死。

## 代码实现

只需要用一个并查集来维护所有连通块即可。

---

## 作者：Billhqh9 (赞：0)

### 我的 AC 记录
[![](https://cdn.luogu.com.cn/upload/image_hosting/pwrxtjfy.png)](https://codeforces.com/problemset/submission/1548/304244381)

### 定义
在这篇题解中，我们定义：当在自己到一个人有**一条边直接相连**时，这个人是自己朋友；同时我们将 A 比 B 强度高，简称为 A 比 B 强，同时 B 比 A 弱。

### 题解

看道题首先考虑暴力。发现不可行，尝试优化。注意到，我们只要求出在弱肉强食的世界中求出幸存者个数，我们不妨在做添边和删边的操作时就做记录，来节省时间复杂度。逆向思维：先看看怎样成为幸存者：
- 自己无和他人连边时。
- 自己比自己所有朋友强。

所以我们不妨用 $total_i$ 记第 $i$ 个人的朋友中比第 $i$ 个人强的人的个数，所以可以得到如下结论：如果 $total_i = 0$，则第 $i$ 个人可以幸存；如果 $total_i > 0$，则第 $i$ 个人会死。

那么，接下来我们要做的事情就转换成了维护 $total_i$。但此时还要通过维护 $total_i$ 来直接维护答案 $ans$，要不然还是会 TLE，因为在没连边之前，大家互不干扰，所以开始时 $ans = n$。

我们再继续逆向思考：来看看如何维护 $total_i$。有两种情况：
- 第 $i$ 个人和比其厉害的人连边。那么将 $total_i$ 加 $1$，如果 $total_i$ 在累加前等于 $0$，则说明原来第 $i$ 个人不死，但现在会死，所以 $ans$ 减 $1$。
- 第 $i$ 个人和比其厉害的人删边。那么将 $total_i$ 减 $1$，如果 $total_i$ 在减少后等于 $0$，则说明原来第 $i$ 个人会死，但现在不死，所以 $ans$ 加 $1$。

当第 $i$ 个人和比其更弱的人连边或删边对 $i$ 无影响，所以不考虑。

我们可以看到，我们实现所有操作的时间复杂度都是 $O(1)$ 的，所以综合来看时间复杂度是 $O(m+q)$，可以通过此题。

### 代码实现
思路有了，代码自然是小事：[AC Code](https://www.luogu.com.cn/paste/3fwnrin0)。

---

## 作者：Tiger_Rory (赞：0)

这题的关键在于如何 $O(1)$ 输出答案。

我们考虑分两类分析。

由于开始的建图和操作一作用效果相同，故而归于第一类讨论：开一个桶记录连到强者的点（编号小的那个）连到强者的次数，如果第一次连到就扣一个答案，这样可以防止一个点死多次。

第二类就是操作二：编号小的点扣除一次连到强者的次数，如果桶中它的这个次数归零，那么它复活，答案加回去。

操作三时直接输出答案即可，这题就做完了。

---

## 作者：__HHX__ (赞：0)

# 思路
在关于点 $v$ 的所有连边中，如果 $u<v$，则 $u$ 一定会在 $v$ 之前删掉。

所以边 $(u,v)$ 并不影响 $v$ 是否删除。

所以对于点 $v$ 我们仅需考虑 $u>v$ 的连边。

易证：对于点 $v$ 如果存在连边，$v$ 点会被删。

因为保证加边 $(u,v)$ 一定不存在，加删边 $(u,v)$ 一定存在。

所以仅需开个桶记录 $u$ 有多少个边 $(u,v)$ 满足 $u<v$，加边加 $1$ 删边减 $1$。

然后在加边时判断 $u$ 是否为 $0$，减边时判断 $u$ 是否为 $1$。

---

## 作者：Retired_lvmao (赞：0)

### 题意

有 $n$ 个点，第 $i$ 个点的编号是 $i$。一开始在这些点中有 $m$ 条边。接下来会进行 $Q$ 次操作，每次操作可能是一下三种之一：

- 操作 $1$：在未连边的 $x,y$ 之间连一条边。

- 操作 $2$：删去 $x,y$ 之间的边。

- 操作 $3$： 删去所有存在连边且与其相连的点的编号全都比它大的点，重复执行直到无点可删。（注意，操作并不实际发生。）

### 题解

先上结论：一个点不会被删去，当且仅当这个点没有与编号更大的点连边。

考虑证明。假如一个点有与它相连的更小的点，这个更小的点会在前一步被删掉，因为第一步一定会有至少一个最小的点被删去，然后类似于蝴蝶效应的，会一步一步的把所有存在于更大编号点连边的点删去。

实现的话，只需要记录每个点与编号更大的点的连边数量即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,ans=0;
int cnt[200010]={};
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(x>y)
			swap(x,y);
		cnt[x]++;
		if(cnt[x]==1)
			ans++;
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int opt,x=114514,y=1919810;
		scanf("%d",&opt);
		if(opt!=3)
			scanf("%d%d",&x,&y);
		if(x>y)
			swap(x,y);
		if(opt==1)
		{
			cnt[x]++;
			if(cnt[x]==1)
				ans++;
		}
		else if(opt==2)
		{
			cnt[x]--;
			if(cnt[x]==0)
				ans--;
		}
		else
			printf("%d\n",n-ans);
	}
}
```

---

## 作者：言琢დ (赞：0)

#### upd：【非公式不应使用 LaTeX】已经改正。

边水群边切简单题。

题意很简单，$n$ 个点、$m$ 条无向边的图，$q$ 个操作：

前两个操作是正常的加边、删边，考虑最后一个操作能给我们带来些什么。

对于每个联通快：不停地删掉编号最小的点，直到只剩一个点。

我们考虑某一条边 $(u,v)$，不失正确性，设 $u<v$。

考虑先证明一个结论：**$v$ 永远不可能比 $u$ 先被删除。**

理由是：由于边 $(u,v)$ 的存在，$u,v$ 必在同一个联通快。所以如果 $v$ 是编号最小的点，那么 $u$ 肯定已经被先删除掉（否则至少有结点 $u$ 编号比它小）。

再来一个更进一步结论：**点 $u$ 周围存在比自己大的点 $v$，自己一定会在某个时刻被删除。**

理由是：每次删掉一个点，每个联通快都一定会被删得只剩一个点。此时 $u,v$ 两点 **至多** 保留一个点未被删除，而根据上面一条结论，保留的只会是 $v$，不可能是 $u$。

由上面这个结论，不难得到另一个结论：**点 $u$ 周围不存在比自己大的点 $v$，自己一定不会被删除。**

理由是：根据第一条结论，点 $u$ 周围所有比自己小的点 $v$，都一定比自己先被删除。据此，当 $u$ **可能** 被删除时，周围一定一个点都不剩。此时由于 $u$ 周围已经没有点，**它是一个独立的联通快，当然不会被删除。**

据上述分析得到 `3` 的判定：**当且仅当周围存在比自己大的点 $v$ 时，自己一定会在某个时刻被删除。**

据此，直接动态记录某个点周围是否存在比自己大的点即可，这里可以建立一个桶记录点 $u$ 周围比自己大的点的个数 $cnt$。

答案就是满足 $cnt=0$ 的点的个数（不会被删除的点的个数），其他的点都会被删除。

每次加边，就是把编号为 $\min(u,v)$ 的点的 `cnt++`；删边就是 `cnt--`。

每次加边之前如果 $cnt=0$，那么 `ans--`；每次删边之后如果 $cnt=0$，那么 `ans++`。

这些都是常用的统计技巧。

一道不错的思维题，AC code：

```cpp
#include<cstdio>
inline int in();
inline void wr(int);
const int N=(int)2e5+5;
int beat[N];//beat[i] 表示结点 i 被多少个相邻结点打败
inline int mn(int,int);
int main(int argc,char**argv){
#ifndef ONLINE_JUDGE
	freopen("CF1548A.in","r",stdin);
	freopen("CF1548A.out","w",stdout);
#endif
	register int n=in(),m=in();
	for(register int i=1;i<=m;++i){
		register int u=in(),v=in();
		++beat[mn(u,v)];
	}
	register int ans=0;
	for(register int i=1;i<=n;++i)
		ans+=!beat[i];
	register int q=in();
	while(q--){
		register int tp=in();
		if(tp==1)
			ans-=(!beat[mn(in(),in())]++);
		else if(tp==2)
			ans+=(!--beat[mn(in(),in())]);
		else
			wr(ans),putchar('\n');
	}
}
inline int mn(int x,int y){
	return x<y?x:y;
}
inline int in(){
	register char c=getchar();
	register int x=0,f=1;
	for(;c<'0'||c>'9';c=getchar())
		if(c=='-')f=-1;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c&15);
	return x*f;
}
inline void wr(int x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)wr(x/10);
	putchar(x%10+'0');
}
```

---

