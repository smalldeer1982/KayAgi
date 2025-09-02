# Prime Graph

## 题目描述

Every person likes prime numbers. Alice is a person, thus she also shares the love for them. Bob wanted to give her an affectionate gift but couldn't think of anything inventive. Hence, he will be giving her a graph. How original, Bob! Alice will surely be thrilled!

When building the graph, he needs four conditions to be satisfied:

- It must be a simple undirected graph, i.e. without multiple (parallel) edges and self-loops.
- The number of vertices must be exactly $ n $ — a number he selected. This number is not necessarily prime.
- The total number of edges must be prime.
- The degree (i.e. the number of edges connected to the vertex) of each vertex must be prime.

Below is an example for $ n = 4 $ . The first graph (left one) is invalid as the degree of vertex $ 2 $ (and $ 4 $ ) equals to $ 1 $ , which is not prime. The second graph (middle one) is invalid as the total number of edges is $ 4 $ , which is not a prime number. The third graph (right one) is a valid answer for $ n = 4 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178D/3f451a0a015e85e0d9b919833cd5a0b4f7edb60b.png)Note that the graph can be disconnected.

Please help Bob to find any such graph!

## 说明/提示

The first example was described in the statement.

In the second example, the degrees of vertices are $ [7, 5, 2, 2, 3, 2, 2, 3] $ . Each of these numbers is prime. Additionally, the number of edges, $ 13 $ , is also a prime number, hence both conditions are satisfied.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1178D/44a2f5b9baacda9bf16e12d85f0a2a6d19c2b3cb.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
5
1 2
1 3
2 3
2 4
3 4```

## 样例 #2

### 输入

```
8
```

### 输出

```
13
1 2
1 3
2 3
1 4
2 4
1 5
2 5
1 6
2 6
1 7
1 8
5 8
7 8
```

# 题解

## 作者：max0810 (赞：6)

首先考虑一个问题：如果没有边数是素数的限制，应该怎么构造？

这其实很简单，把原图连成一个环即可，每个点度数为 $2$。

---
接着考虑在原图上加边，注意到 $3$ 也是个素数，所以每次可以任意选两个度数为 $2$ 的点连边，此时仍然符合条件。这样加边最多可以加 $\left\lfloor\frac{n}{2}\right\rfloor$ 次。

这时就要用到一个定理：在 $n$ 到 $\left\lfloor\frac{3n}{2}\right\rfloor$ 中一定存在着一个素数 ~~（证明太难了，我不会）~~。

其实可以手推一下，在 $1000$ 以内两个相邻的素数的差最大也就 $20$（$887$ 和 $907$）。

所以只需依次加边，直到 $m$ 是一个素数，此时新增的边的数量不超过 $\left\lfloor\frac{n}{2}\right\rfloor$ 条。

---
代码中，我选的是每次连编号为 $i$ 和 $i+\left\lfloor\frac{n}{2}\right\rfloor$ 的边。

```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
using namespace std;
int n,m;
bool f(int x)
{
    for(int i = 2;i*i <= x;i++)
        if(x%i==0)return 0;
    return 1;
}
int main()
{
    cin >> n;m = n;
    while(!f(m))m++;
    cout << m << endl;
    for(int i = 1;i <= n;i++)printf("%d %d\n",i,i%n+1);
    for(int i = 1;i <= m-n;i++)printf("%d %d\n",i,i+n/2);
    return 0;
}

```


---

## 作者：Waddles (赞：5)

这个题贪心233

我自己都没想到我比赛时是一遍过的（因为我考虑多了一种情况，结果发现不怎么会写，结果交上去发现没必要~~其实是懒得写~~）

在代码里可以看到我写了一个大if没有else，那就是我考虑多了的s>n/2的情况（因为素数是密集的）

不同于楼下，我写的是贪心

先筛素数

先把每个点和相邻点连上边（这样度都是2），连了n条边

找到比n大的最小素数，设它为p

上面讲到，质数是密集的，所以p-n<=n/2，所以只需要把剩下p-n条边让差的很远的两点连上一条边，不会重合，所以一个点最多度为3

这里我怕不保险又在最容易出问题的中间部分特判了一下，无伤大雅，因为当时写的时候没有想到质数是密集的，所以怕接近n/2，交完才觉得有点多虑了

这种贪心就是用了质数是密集的和2,3是唯一相邻素数这两个结论得到的

```
#include<map>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
int n,a[10005],v[10005],p[10005],top;
void prime(){//埃筛素数
	v[1]=1;
	for(int i=2;i<=10000;i++){
		if(!v[i]){
			p[++top]=i;
			for(int j=i*2;j<=10000;j+=i)v[j]=1;
		}
	}
}
int main(){
	prime();
	in(n);
	if(v[n]==0){//特判n是质数，直接输个环
		printf("%d\n",n);
		for(int i=1;i<n;i++)printf("%d %d\n",i,i+1);
		printf("%d %d\n",n,1);
		return 0;
	}
	int sum=1;
	while(p[sum]<=n)sum++;//找我上面所说的p
	int s=p[sum]-n;//要加的边个数，保证边数为质数
	for(int i=1;i<=n;i++)a[i]=2;//每个点度为2
	if(s<=n/2){//这个if没必要写
		printf("%d\n",n+s);
		for(int i=1;i<n;i++)printf("%d %d\n",i,i+1);//和上面特判质数的一样，每个点搞成度为2
		printf("%d %d\n",n,1);
		int sum=0;
		if(n%2==0){
			if(s==1){
				printf("%d %d\n",1,n-1);
				return 0;
			}
			else{//假象p-n可以等于n/2，那么不能让n/2和n/2+1连上了，所以这里把他和1,n配对
				printf("%d %d\n%d %d\n",1,n/2,n,n/2+1);
				s-=2;
			}
		}
		else{
			printf("%d %d\n",1,n/2+1);
			s--;
		}
		int l=2,r=n-1;//一个小，一个大，配对输出，保证最大度为3
		while(sum<s){
			printf("%d %d\n",l,r);
			l++;
			r--;
			sum++;
		}
	}
	return 0;
}
```

---

## 作者：zhangzirui66 (赞：1)

随机跳到的题，做完发现解法和第一篇的思路一模一样，有点激动，写篇题解。

## 题意
构造一个有 $n$ 个节点的简单图，满足：

- 边数 $m$ 为质数。
- 所有点的度数均为质数。

## 思路
我们容易发现，若构造成一个环，每个点的的度数为 $2$，满足了第二点：
![](https://cdn.luogu.com.cn/upload/image_hosting/927mgprz.png)

容易发现若再连一条边，两个点的度数将会变为 $3$，仍为质数，我们能找到 $\lfloor \frac{n}{2} \rfloor$ 组点，由于素数较密的原因，我们可以找到合适的 $m$ 满足其为质数。图为如下：
![](https://cdn.luogu.com.cn/upload/image_hosting/bxqzpzke.png)

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, now = 1;
struct graph{
	int u, v;
};
vector<graph> g;
bool prime(int x){
	if(x <= 1) return 0;
	for(int i = 2; i * i <= x; i ++) if(x % i == 0){
		return 0;
	}
	return 1;
}
int main(){
	cin >> n;
	if(n <= 2){
		cout << -1;
		return 0;
	}
	for(int i = 1; i <= n; i ++) g.push_back({i, i % n + 1});
	while(!prime(g.size())){//不为质数
		g.push_back({now, now + n / 2});//前一半与后一半相匹配，避免重复。
		now ++;
	}
	cout << g.size() << "\n";
	for(int i = 0; i < g.size(); i ++) cout << g[i].u << " " << g[i].v << "\n";
	return 0;
}

```
时间复杂度 $O(n+k)$，其中 $k$ 为小于 $n$ 的最大相邻素数之差，在本题的数据范围（$n\le 1000$）中，差最大为 $20$，两个质数分别是 $887$ 和 $907$，可以通过。

---

## 作者：世末OIer (赞：1)

目测全CF就我一个人这样做。

---

1.预处理处所有的素数

2.枚举所有可能的边数。

3.对于每一个可能的边数，计算出所有节点的度数的总数，进行爆搜。

4.构造答案。


```cpp
bool nisp[1000006];
vector<int>p;
int n,m,sum;
int lmt;
int cnt[1003];
vector<pair<int,int> >ans;
bool used[1003][1003];
inline void output(){    //构造
	sort(cnt,cnt+n);
	reverse(cnt,cnt+n);
	cout<<sum<<endl;
	for(int i=0;i<n;++i) cnt[i]+=2;
	for(int i=0;i<n;++i){
		for(int j=0;j<n and cnt[i];++j) if(abs(i-j)>=n/2 and cnt[j] and i!=j and !used[i][j]){
			used[i][j]=1,used[j][i]=1;
			ans.push_back(mp(i+1,j+1));
			--cnt[i],--cnt[j];
		}			
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n and cnt[i];++j) if(cnt[j] and i!=j and !used[i][j]){
			used[i][j]=1,used[j][i]=1;
			ans.push_back(mp(i+1,j+1));
			--cnt[i],--cnt[j];
		}			
	}
	for(int i=0;i<ans.size();++i) cout<<ans[i].first<<' '<<ans[i].second<<endl;
}
inline void dfs(int x,int lst,int ts){  //爆搜
	if(!ts){
		output();
		exit(0);
	}
	if(x>=n) return;
	for(;lst<p.size() and p[lst]<=ts and p[lst]<=sum;++lst)cnt[x]=p[lst],dfs(x+1,lst,ts-p[lst]);
}
inline void go(){        //计算总度数
	int ts=sum*2-2*n;
	dfs(0,0,ts);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;m=n*(n-1)/2;
	nisp[0]=1,nisp[1]=1;
	for(int i=2;i<=m;++i){
		if(!nisp[i]){
			if(i>2)p.push_back(i-2);
			for(int j=i+i;j<=m;j+=i) nisp[j]=1;
		}
	}
	for(sum=n;sum<=m;++sum)  //枚举可能的边数
		if(!nisp[sum]) go();
	cout<<-1<<endl;
}
```

---

## 作者：封禁用户 (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1178d-prime-graph-de-ti-jie/)
## 题目大意
构造一个简单无向图，是所有的有度的点的度都是质数而且总共的边的数量的个数是质数。

## 思路
因为需要让所有的入度都为质数，所以我们可以找到两个相邻的质数 $2,3$，因为这样即使增加了一条边那么这个节点的度也是质数。

先将这个图构成一个巨大的环，接着如果所有的边数并不是质数，那么就随便找两个不相邻的点连边。

因为在 $2000$ 以内，质数都是十分密集的，所以即使是最坏的情况，那么大于 $2\cdot n$ 最近的质数也不会超过 $n/2$，直接将相距很远的点连边就可以了。

## AC Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,a[N],s;
bool ck(int x){
	for(int i=2;i*i<=x;i++) if(x%i==0) return 0;
	return 1;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	while(!ck(s+n)) s++;
	cout<<n+s<<'\n';
	for(int i=1;i<=n;i++) cout<<i<<' '<<((i+1>n)?(i+1-n):(i+1))<<'\n';
	for(int i=1;i<=s;i++) cout<<i<<' '<<((i+n/2>n)?(i+n/2-n):(i+n/2))<<'\n';
	return 0;
}
```

---

## 作者：Ryder00 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1178D)

## 思路

考虑贪心。步骤如下：

- 筛出 $n+20$ 范围内的素数。 

- 将每个点按照顺序连成一个环，使得当前边数为 $n$ ，每个点的度数为 $2$ 。

- 打表可得： $1000$ 以内的素数是密集的（即对于每个数 $n$，与相邻素数 $k$ （ $k \ge n$ ）的距离均在 $\dfrac{n}{2}$ 的范围以内）。

- 二分查找 $n$ 的相邻素数 $k$ （ $k \ge n$ ），目前还剩下（ $k-n$ ）条边没有连。

- 对于从 $1$ 开始的每个 $i$，向 $i+\dfrac{n}{2}$ 连一条边，直到（ $k-n$ ）条边连完（这样可以保证连了多余边的点的度数可以变为 $3$，依然是素数）。

- 输出即可。


```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1020;
int n,cnt,vis[N+10],l=1,r=N,k;
bool pri[N+10];
void prime()
{
	memset(vis,0x3f,sizeof(vis));
	for(int i=2;i<=N;i++) pri[i]=1;
	for(int i=2;i<=N;i++) 
	{
		if(pri[i]) 
		{
			for(int j=2*i;j<=N;j+=i) pri[j]=0;
			vis[++cnt]=i;
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	prime();
	cin>>n;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(vis[mid]>=n) r=mid;  
		else l=mid+1;
	}
	int ans=vis[l];
	cout<<ans<<endl;
	for(int i=1;i<n;i++) cout<<i<<' '<<i+1<<endl;
	cout<<n<<' '<<1<<endl;
	ans-=n; 
	while(ans--)
	{
		k++;
		cout<<k<<' '<<n/2+k<<endl;
	}
	return 0;
}
```

---

