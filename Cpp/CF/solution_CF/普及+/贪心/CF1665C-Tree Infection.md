# Tree Infection

## 题目描述

### 题意描述
一个树是一个无环连通图。一个有根树有一个被称作“根结点”的结点。对于任意一个非根结点 $v$ ，其父结点是从根结点到结点 $v$ 最短路径上的前一个结点。结点 $v$ 的子结点包括所有以 $v$ 父结点为 $v$ 的结点。

给定一个有 $n$ 个结点的有根树。结点 $1$ 即为根结点。一开始，该树上所有结点均是“健康”的。

每一秒你会进行两次操作——先是传播操作，然后是注射操作，定义如下。

- 传播操作：对于每个结点 $v$ ，若该结点至少有一个子结点被“感染”，则你可以“感染”顶点 $v$ 任意一个其他的子结点。
- 注射：你可以选择任意一个“健康”的结点并使它变为“感染”状态。

这程每秒会重复一次知道整个树的结点都处于“感染”状态。你需要找到使整个树被“感染”的最短时间（秒数）。

## 说明/提示

- $ 1 \le t \le 10^4 $
- $ 2 \le n \le 2 \times 10^5 $
- $ 1 \le p_i \le n $
- $ \sum \limits_{i=1} ^t n_i \le 2 \times 10^5 $

## 样例 #1

### 输入

```
5
7
1 1 1 2 2 4
5
5 5 1 4
2
1
3
3 1
6
1 1 1 1 1```

### 输出

```
4
4
2
3
4```

# 题解

## 作者：tzyt (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF1665C)

[博客](https://ttzytt.com/CF1665C)中观看体验更佳
# 1.题意：
给你一个有 $n$ 个节点的树，一开始，每个节点都是健康的。每秒钟你可以进行下面两种操作：
1. 传播：对于一个节点，如果它的至少一个**子节点**被感染了，那么可以感染它的另一个子节点。（如果有多个节点符合条件，那一秒钟就可以传播多个节点）
2. 注射：你可以任选树中的一个节点进行感染。（一秒钟只能多感染一个节点）

现在问你最少需要多少秒才能感染整个树。

# 2.思路：
看完题我们要注意到，这个题说的是节点可以把病毒传播给他们的兄弟节点，而不是传播给他们的子节点，所以这个树的每一层之间是完全独立的，不可能把病毒从一层传播给另一层。

所以我们肯定需要在一开始的时候就给每个节点的至少一个子节点注射病毒（具体哪个不重要），这样每秒钟能感染的节点更多（根据操作 1）。

那先给谁的子节点注射呢？考虑先被注射的子节点会有更多的时间把病毒传播给更多的子节点。所以我们应该先给子节点更多的节点注射病毒。

（如果先给子节点少的节点注射，那在给所有节点注射完之前，这个节点的所有子节点可能都被感染了，也就是有很多时间被浪费了）。

在确保每个节点都有至少一个子节点被注射后，我们还可以给子节点特别多的那些节点注射病毒，防止有些特别大的节点靠传播来传染特别慢。

当然我们不能直接跟前面一样直接根据子节点数量来排序，并且一直给子节点多的节点注射病毒，因为这样可能会让某个节点以及它的子节点迅速的被完全感染，而其他的节点还需要很长时间。

比如有两个节点，他们在经过注射后的，健康的子节点的数量分别是 $100$ 和 $98$，如果我们直接排序，先给大的节点注射，那感染完整个树就还需要 $(100\div2) + \frac{(98 - (100\div2))}{2} = 74$ 秒（ $\div 2$ 是因为有传播和注射两种感染方式同时进行，而 $98 - 50$ 之后再 $\div 2$ 是因为我们先处理完 $100$ 那个节点才去给 $98$ 那个节点注射）。但是如果我们同时给两个节点注射，只需要 $(100 + 98) \div 3 = 66$ 秒的时间（因为可以把两个节点看成一个节点，那每秒就有两个子节点因为传播而感染，一个因为注射而感染）。

所以我们可以把健康的子节点数压入堆中，每次注射子节点最多的那个。

# 3.代码：
不过多解释，代码中有详细注释
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
int n;
int siz[MAXN], t;
//siz 表示这个节点的子节点的数量

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(siz, 0, sizeof(siz));
        for (int i = 1; i < n; i++) {
            int fa;
            scanf("%d", &fa);
            siz[fa]++;
        }
        siz[0] = 1;  //让 0 号节点连到根节点，所以 0 号节点的子节点数量是 1
        sort(siz, siz + 1 + n);
        int fir_n_zero = -1;  //第一个子节点数量不是 0 的节点的下标

        fir_n_zero =
            find_if(siz, siz + 1 + n, [](int a) { return a != 0; }) - siz;

        priority_queue<int> pq;
        for (int i = fir_n_zero; i <= n; i++) {
            //循环中 i 小的节点是后被注射的，可以把 i 理解为倒数第 i 个被注射
            pq.push(siz[i] - (i - fir_n_zero) - 1);
            //给所有节点的某个子节点注射一遍，但是在注射的过程中还会传播，因为传播而被感染的子节点数就是
            // i - fir_n_zero，因为注射而被感染的是 1，所以被 push
            // 进去的数就是经过这一轮注射后，每个树还剩下几个子节点未被感染。
        }

        int tm_used = n - fir_n_zero + 1; //这一轮注射用掉的时间，也就是有子节点的节点的数量
        int spreaded = 0;

        while(pq.top() > spreaded){
            //这里的 pq 没有减去因为传播而感染的数量，因为每一个节点都会有传播
            spreaded++;
            //每次都会因为传播而多感染一个
            int tp = pq.top();
            pq.pop();
            pq.push(tp - 1);
            //每次挑选最大的节点注射
            tm_used++;
        }
        printf("%d\n", tm_used);
    }
}
```

最后，希望这篇题解对你有帮助，如果有问题可以通过评论区或者私信联系我。

---

## 作者：听取MLE声一片 (赞：4)

很奇怪的一道题，我又用的堆。

简要题意：给定一棵有根树，根节点为 1，初始时每个节点为健康的。每步感染一个健康的节点，而且如果一个点的被感染的儿子节点的数量不为零，则感染这个点的一个健康的儿子节点，两种操作同时进行。问感染整棵树需要多少步。

很容易想到统计每个节点的儿子个数，并规定 0 号节点的儿子节点为 1，然后把 $n+1$ 个节点的儿子数量排序，并找到所有儿子个数不为零的。

一个比较显然的想法是从最大的向最小的感染，感染一轮之后全往最大的感染，但是这个做法会 `wa on 6`。

这是因为如果一个点有 999 个儿子，另外一个点有 1000 个儿子，按照上面的方法，染完一轮就直接全把最多的感染，直接忽略了次多的节点。

为了解决这个问题，我是用一个堆，从最大的向最小的感染，感染一轮之后全往扔到堆里面，顺便整个计数器。每次暴力给目前儿子节点数最多的感染（儿子数量减一），然后计数器加一。如果当前计数器不小于儿子节点数，感染完成。正确性显然。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<bitset>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=4e5+10;
int n,m,a[N];
int main()
{
	int T=read();
	while(T--){
		int n=read();
		for(int i=1;i<n;i++){
			int x=read();
			a[x]++;
		}
		a[0]=1;
		sort(a,a+n+1);
		for(int i=0;i<=n;i++){
			if(a[i]!=0){
				priority_queue<int> q;
				for(int j=i;j<=n;j++)
					q.push(a[j]-(j-i+1));
				int ans=n-i+1,top=0;
				while(q.top()>top){
					//cout<<q.top()<<endl;
					top++;
					int x=q.top();
					q.pop();
					q.push(x-1);
					ans++;
				}
				cout<<ans<<endl;
				break;
			}
		}
		for(int i=1;i<=n;i++)
			a[i]=0;
	}
	return 0;
}

```

---

## 作者：jiangtaizhe001 (赞：2)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/16126094.html)

### 题目大意
给定一棵有根树，每秒钟可以完成以下操作：

- 注入一个节点，从而感染这棵树的这个节点。
- 如果一个节点至少有一个儿子节点被感染（在上个操作之前），那么这个节点的另一个儿子节点会被传染。  

现在求感染所有节点的最少需要几秒。树的节点数 $n\le 10^5$。

### 题目解析
显然答案只和每个节点的儿子数量有关。  
我们可以开一个桶记录下每个节点的儿子数量，但是注意不要忘记**加上根**。

不难发现，我们需要先保证每个节点的儿子都有一个被感染，这样每秒钟除了被注入就能感染更多的节点。显然在注入的时候我们优先注入节点数更多的节点，这样在注入的过程中也能传染到更多的节点。  
当所有节点都有一个儿子被感染之后，显然我们需要注入没有被感染的儿子节点数最多的节点的一个儿子。并且保持传染其他节点。  

我们可以用一个堆来维护最大值，同时传染的节点我们可以用懒惰标记。

算法复杂度 $O(n \log n)$

代码：
```cpp
int n,x,ans,tmp,cnt,son[maxn];
priority_queue<int> a,b,E;
void work(){
	n=read(); int i; for(i=1;i<=n;i++) son[i]=0; for(i=2;i<=n;i++) x=read(),son[x]++;
	a=b=E; ans=0; cnt=1; for(i=1;i<=n;i++) if(son[i]) a.push(son[i]),cnt++; a.push(1);//加进去的1是根
	tmp=cnt; while(!a.empty()){ cnt--; x=a.top(); a.pop(); b.push(x-cnt-1); }
	while(b.top()>ans){ x=b.top(); b.pop(); b.push(x-1); ans++; }
	print(ans+tmp),pc('\n'); return;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1600}$
---
日常读错题。

---
### 解题思路：

注意题目要求的是子节点而不是子树。也就是说每一个点的子节点和其它的所有点都是割裂开的。可以先将所有的点的子节点的数量预处理出来。

----
然后问题也就转化成一些互相独立的集合，每一个集合中如果存在被标记的点就能在每一个单位时间内拓展一个点。每一个单位时间内可以对一个点进行标记。

对于转化后的问题，可以发现至少要对所有的集合进行一次标记，可以先将这一部分拿出来。然后考虑对于一些集合进行额外的标记以在最短的时间内让所有的点被标记。

---
然后进行二分，二分出需要额外进行的标记次数，在这个时间内优先进行贪心。优先标记集合内元素较多的集合，证明可以直接用交换的方法。

总复杂度为 $O(n\log n)$。

---
### 代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,n,s[200005],x,ans,l,r,mid;
vector <int> v;
bool check(int num){
	int cnt=0;
	for(int i=0;i<v.size();i++){
		cnt+=max(0,v[i]-num-1-i);
	}
	if(cnt>num)return 0;
	return 1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)s[i]=0;
		for(int i=2;i<=n;i++){
			scanf("%d",&x);
			s[x]++;
		}
		v.clear();
		v.push_back(1);
		for(int i=1;i<=n;i++)
		if(s[i]!=0)v.push_back(s[i]);
		
		sort(v.begin(),v.end());
		l=0;r=n+1;ans=0;
		while(l<=r){
			mid=l+r>>1;
			if(check(mid))r=mid-1,ans=mid;
			else l=mid+1;
		}
		printf("%d\n",ans+v.size());
	}
	return 0;
}
```


---

## 作者：BerlandsFD (赞：0)

容易想到统计每个节点的子节点数量，定义 $0$ 号点的子节点为 $1$，并将这 $n+1$ 个数排序，保留非 $0$ 项。

显然，我们会想到直接从子节点最多的向最小的感染，感染一轮后全去感染最大的，但是，这是不对的：因为这样会忽略次多的节点。

所以，选择使用优先队列，我们先从最大到最小感染，一轮之后加入优先队列，每次从优先队列里取出最大的元素并减一(最大的感染一次)，并且定义一个 $cnt$，$cnt$ 每感染一次就加 $1$，当 $cnt$ 比优先队列里最大的元素还要大时，说明已经全部感染，输出 $ans$。
```cpp
#include <bits/stdc++.h>
using namespace std;
int lst[200010];
int t = 0;
int n = 0;
int main(){
	cin >> t;
	while(t --){
		memset(lst, 0, sizeof(lst));
		cin >> n;
		for(int i = 2; i <= n; i++){
			int cur = 0;
			cin >> cur;
			lst[cur] ++; //记录子节点个数（出度） 
		}
		lst[0] = 1; 
		sort(lst, lst + 1 + n);//排序 
		for(int i = 0; i <= n; i++){
			if(lst[i] != 0){
				priority_queue<int> pque;
				for(int j = i; j <= n; j++){
					pque.push(lst[j] - j + i - 1);//直接把感染了一轮的节点加进去 
				}
				int ans = n - i + 1;//提前加上感染的一轮的值 
				int cnt = 0;//计数器 
				while(pque.top() > cnt){
					cnt ++;
					int top = pque.top();//每次取最大，感染加上 
					pque.pop();
					pque.push(top - 1);
					ans ++; 
				}
				cout << ans << endl;//输出 
				break;
			}
		}
	}
	return 0;
}
```


---

