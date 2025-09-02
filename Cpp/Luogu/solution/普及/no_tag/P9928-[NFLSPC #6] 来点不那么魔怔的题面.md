# [NFLSPC #6] 来点不那么魔怔的题面

## 题目描述

给定一个 $1\sim n$ 的排列 $p$ 和一个整数 $k$，要求找到 $p$ 的一个子序列 $\{p_{i_1}, p_{i_2}, \cdots, p_{i_m}\}$（$1\le i_1 < i_2 < \cdots < i_m\le n$）满足：

- 恰好有 $k$ 个 $j$ 满足 $1\le j\le m$ 且 $p_{i_j}$ 是 $p_{i_1}, p_{i_2}, \cdots, p_{i_m}$ 中从小往大数第 $j$ 个。

如果有多解，输出任意一组解即可。如果不存在合法的子序列，输出 $-1$。

## 说明/提示

对于所有数据，$1\le n\le 10 ^ 5$，$1\le k\le n$，$p_1, p_2, \cdots, p_n$ 为 $1\sim n$ 的排列。

- 子任务 1（$10$ 分）：$n\leq 20$。
- 子任务 2（$10$ 分）：$k = 2$。
- 子任务 3（$30$ 分）：$k = 3$。
- 子任务 4（$30$ 分）：$n\leq 10 ^ 3$。
- 子任务 5（$20$ 分）：无特殊限制。

Source：NFLSPC #6 D by tzc_wk

## 样例 #1

### 输入

```
4 1
4 2 1 3
```

### 输出

```
3
2 3 4
```

# 题解

## 作者：cjh666_ (赞：9)

# 题意一下

- 在长度为 $n$ 的数组 $q$ 中找到一个恰好有 $k$ 个数的序号与自身大小相同（例如下标为 $j$ 若合法，则 $q_{j}$ 为此集合第 $j$ 小的。简单点来说，要达成这个条件，我们就要在 $q$ 提取一个单调递增的序列，（因为单调递增，所以每个数下标越小，则值越小）。

# 思路一下
- 一个上升序列，判断序列长度，是从前一个不大于此点的点的长度转移过来的，第一个想到什么？没错，DP。先规定状态，这个简单：$dp[i]$ 为在 $q$ 中序号为 $i$ 的点为最高点，向前的最长序列长度。那状态转移方程呢？$dp[i] \gets \max (dp[j])+1$  $(j<i，q[j]<q[i])$ 在向前的比自己小的点中找到一个最大的长度在加上自己的一个长度。边界，很幸运，这题没有什么特殊边界，直接初始为 $1$ 就好。
### 注意
- 题目不是输出整个序列，而是有 $k$ 个合法点的序列，因为我们这个方法的特殊，每个点都是合法的，有解则输出 $k$ 个。
### DP代码如下

```c
#include<bits/stdc++.h>
using namespace std;
int a[100005],dp[100005],b[100005];
int main(){
	int n,k,ans=-1;
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		dp[i]=1;//边界
		for(int j=1;j<i;j++)
			if(a[j]<a[i])dp[i]=max(dp[i],dp[j]+1);
		ans=max(dp[i],ans);	
		if(ans==k)break;	
	}
	if(ans<k){
		cout<<-1<<endl;
		return 0;
	}
	else cout<<k<<endl;
	int siz=0;
	for(int i=n;i>=1;i--){
		if(dp[i]==ans){
			b[++siz]=i;
			ans--;
		}
	}
	for(int i=k;i>=1;i--){
		cout<<b[i]<<' ';
	}
}
```

### 分析一下
- 这份代码的时间复杂度为 $n_{}^{2}$，空间复杂度为 $n$，但数据范围不如人意，$n = 1 \times 10_{}^{5}$，$n_{}^{2}$ 不能接受。这里本蒟蒻没有想到什么优化方法，所以走了另一条路（手动捂脸）。代码这个东西，你想到的方法都要试一下，平时没事多写几种方法，没 AC 也没事。

# AC 思路
- 首先我们维护一个数组，让这个数组单调递增，怎么加入新节点呢？我们用二分，找到一个大小大于的最小新节点的节点，把它更新掉，然后我们记录这个新节点的前一个点，这里有人就不理解了，为什么可以更新，更新了新节点的上一个位置的不就有可能会乱了吗？
- 这就是这个代码的核心了，我们从小到大向上枚举的，所以我们对于每个节点都会单独记录他前面的一个最大值，而对于更新的新值，不会影响前面的点，同时也不会影响序列的长度。
- 那序列怎么变长呢？我们开始的时候，将 $r \gets siz +1$ 如果新节点的大小是最大的，那么就会使 $siz$ 增加，使序列增长。没理解的同学也没关系，代码奉上，同学们可以在边看代码边理解。
- 这种方法的时间复杂度是 $n log(n)$，空间复杂度是 $n$，可以通过本题。
### AC 代码
```c
#include<bits/stdc++.h>
using namespace std;
int n,k,siz=0;
int a[100005],b[100005],q[100005];
void dfs(int x,int num){//x为点的下标，num为已经拿了的点数
	if(num>k)return ;
	dfs(q[x],num+1);//递归前一个点，点数加1。
	cout<<x<<' ';//先递归再输出，是小的序号在前。
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		int l=0,r=siz+1;
		while(l+1<r){
			int mid=r+l>>1;
			if(a[i]>=a[b[mid]])l=mid;
			else r=mid;
		}		//二分
		b[r]=i;//注意这里不是记录a的值，而是记录下标，方便后面取出。
		q[b[r]]=b[r-1];//记录这个点的前一个点第一个在它前面，且比它小的点。
		if(r==siz+1)siz++;
	}
	if(siz<k){
		cout<<-1<<endl;
		return 0;
	}
	else cout<<k<<endl;
	dfs(b[siz],1);//从最大的往下找。
}
```

# 结语
- 这道题做完了（舒坦），如果有同学这种单调序列的题的话可以去做一下 P1020 导弹拦截，跟这道题目有相似之处。
- 不太会写题解，有问题的地方欢迎指出

---

## 作者：RH233 (赞：5)

### P9928 [NFLSPC #6] 来点不那么魔怔的题面 题解
#### [题目传送门](https://www.luogu.com.cn/problem/P9928)

### 题意
在一个长度为 $n$ 的无序排列 $p$ 中找到一个长度为 $k$ 的**上升子序列**。
### 做法
首先用数组 $a$ 把原序列输入进来，然后维护一个数组 $dp$ ,先把第一个元素直接放进去,接下来其他的元素用 `lower_bound` 来查找第一个大于等于 $a[i]$ 的元素，查找时将返回值 $-1$ ，然后将 $dp[x+1]$ 给赋值为 $a[i]$ ，这个操作使得 $dp$ 要么尽量小，要么变长。在执行这个操作之前，我们还需要维护一个二维动态数组 $G$ 用来存储上升子序列。具体地， $G[i][j]$ 表示在原序列 $p$ 中长度为 $i$ 的上升子序列。对于输出，观察发现其实题目并没有要求我们输出一个上升子序列，而是输出**每一个合法的节点**，所以我们只需要输出 $G[k]$ 当中任意 $k$ 个元素就可以了。由于~~懒~~实现难度问题这里直接输出前 $k$ 个元素。
### AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const ll N=1e5+10; 
ll n,k,a[N],dp[N];
ll ans[N],len; // len 表示 dp 的长度 
vector<ll> G[N]; // G 存上升子序列 
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++){
		ll x=lower_bound(dp+1,dp+len+1,a[i])-dp-1;//找位置 
		dp[x+1]=a[i]; //如果不是最大，因为前面有-1，这里赋值会使得数组中元素尽量小 
		G[x+1]=G[x]; //先把前面的直接赋值进去 
		G[x+1].push_back(i); //序号存进去 
		if(x+1>len) //如果发现长度增加了，len++，方便输出时取答案 
			len++;
	}
	if(k>len) //无法达到要求直接坠机 输出-1 
		cout<<-1;
	else{ //否则输出答案 
		cout<<k<<endl;
		for(int i=0;i<k;i++)
			cout<<G[len][i]<<" ";
	}
	return 1-1;
}
```

---

## 作者：exLucas (赞：2)

对于第一个子任务的 $n \leq 20$，可以枚举所有子序列进行判断。复杂度 $O(2^n)$，期望得分 $10$ 分。

对于第二个子任务的 $k = 2$，只需要找 $a_i < a_j$ 并统计个数即可。复杂度 $O(n)$，目前期望得分 $20$ 分。

对于第三个子任务的 $k = 3$，和第四个子任务的 $n \leq 10 ^ 3$，$O(n ^ 2)$ 朴素 DP 求 LIS 即可。复杂度 $O(n^2)$，目前期望得分 $80$ 分。


---


现在考虑正解。将满足 $p _ {i _ j}$ 为第 $j$ 大的所有 $p_{i_j}$ 提出得到 $a_{1 \sim k}$，能看出 $a$ 是 $p$ 的子序列，且 a 满足单调递增。

于是得到结论：如果 $a$ 有长度为 $k$ 的上升子序列，则有解且解为该上升子序列，否则无解。

时间复杂度 $O(n \log n)$ 可以通过此题。

---

## 作者：small_john (赞：2)

## 前言

Upd：修改了一些表述问题。

## 思路

首先发现，对于两个合法的 $j_1,j_2$，如果 $j_1>j_2$，那么一定满足 $p_{i_{j_1}}>p_{i_{j_2}}$。

所以，我们可以猜测，选一个**最长**上升序列一定是最优的，这样，整个序列都是合法的。

考虑反证，尝试向答案序列加入一个数使得其不满足单调递增，那么加入的位置的后面都不合法。这种操作有贡献当且仅当本序列可以继续加数。有两种情况：

1. 在中间插入，多加一个数，但至少损失两个数；
2. 任意插入，换成另一个上升序列。

而无论如何这样都是不优的。

然后这道题就变成了求最长上升子序列的模板。

本蒟蒻太弱了，不会用那种改状态的 DP，用的值域线段树维护。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
const int N = 1e5+5;
int n,k,a[N],f[N],pre[N],stk[N],top;
struct node{
	int p,mx;
}t[N<<2];
#define ls (k*2)
#define rs (k*2+1)
inline node Max(node x,node y)
{
	node res;
	if(x.mx>y.mx) res = x;
	else res = y;
	return res;
}
void change(int k,int l,int r,int x,node v)
{
	if(l==r) return t[k] = Max(t[k],v),void();
	int mid = (l+r)/2;
	if(mid>=x) change(ls,l,mid,x,v);
	else change(rs,mid+1,r,x,v);
	t[k] = Max(t[ls],t[rs]);
}
node ask(int k,int l,int r,int x,int y)
{
	if(l>y||r<x) return (node){0,0};
	if(l>=x&&r<=y) return t[k];
	int mid = (l+r)/2;
	return Max(ask(ls,l,mid,x,y),ask(rs,mid+1,r,x,y));
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(k);
	for(int i = 1;i<=n;i++)
		read(a[i]);
	for(int i = 1;i<=n;i++)
	{
		node res = ask(1,1,n,1,a[i]);
		f[i] = res.mx+1,pre[i] = res.p;
		change(1,1,n,a[i],(node){i,f[i]});
	}
	int mx = 0;
	for(int i = 1;i<=n;i++)
		if(f[mx]<f[i]) mx = i;
	if(f[mx]<k) return puts("-1"),0;
	writen(k);
	while(k--) stk[++top] = mx,mx = pre[mx];
	while(top) write(stk[top--]),putchar(32);
	return 0;
}
```

---

## 作者：sbno333 (赞：1)

这道题可以看出来，是让你在原序列中找到一个长度为 $k$ 的上升子序列。

证明：

我们设我们的序列为 $s_1,s_2,s_3\dots s_n$。

其中 $s_{a_1},s_{a_2},s_{a_3}\dots s_{a_k}$ 为满足题目要求的 $j$，其中 $a_1<a_2<a_3\dots<a_k$。

即 $s_{a_i}$ 是在 $s$ 里是第 $a_i$ 小的。

因此对于 $x<y$，$s_{a_x}<s_{a_y}$。

此时我们发现存在 $s$ 的子序列 $b$ 满足 $b_i=s_{a_i}$。

此时 $b$ 为上升序列。

由于存在 $s$ 就存在 $b$。

因此我们只需要找长度为 $k$ 的上升序列即可。

我们要用时间复杂度 $\Theta(n\log n)$ 的算法求子序列，可以用如下方法：

首先我们都学过求长度，即对于每一个数，如果比队列里的最后一个数大，就加入队列，否则二分查找替换队列中一个数，使得那个位置上的数变小且整个队列仍然为上升序列。

如果算完后长度无法达到 $k$，就报告无解。

问题就在于求最长上升子序列。

可以标记队列每个元素在原序列的编号以及这个元素加入或替换队列元素时其在队列中上一个元素的编号。

算完后如果某一时刻队列长度达到 $k$，就通过记录的编号进行递归。

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[1000009];
int bt[1000009];
int t[1000009];
int inn;
void dfs(int x){
	if(x==0){
		return;
	}
	dfs(t[x]);
	cout<<x<<" ";
}
int main(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		if(a>q[inn]){
			q[++inn]=a;
			bt[inn]=i;
			t[i]=bt[inn-1];
		}else{
			int l,r;
			l=1;
			r=inn;
			while(l<r){
				int mid;
				mid=l+r;
				mid/=2;
				if(a<q[mid]){
					r=mid;
				}else{
					l=mid+1;
				}
			}
			q[r]=a;
			bt[r]=i;
			t[i]=bt[r-1];
		}
		if(inn==k){
			cout<<inn<<endl;
			dfs(i);
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：tangzirui1016 (赞：0)

### 题意分析
题目说要找到一个子序列，满足恰好有 $k$ 个 $j$ 满足 $j$ 合法且这个序列的第 $j$ 个数是这个子序列中第 $j$ 大的数。   
通过贪心的思想，其实这就是找一个长度为 $k$ 的上升子序列。  
### 思路分析
- **朴素做法**

时间复杂度：$O(n^2)$

设 $dp_i$ 表示以 $i$ 结尾的最长上升子序列长度，那么有 $dp_i=\max_{1\le j\le i,p_j<p_i} dp[j]+1$，暴力枚举 $j$,同时记录 $i$ 是从那个 $j$ 转移过来的，方便输出路径。

- **优化方法**

时间复杂度：$O(n\log n)$  

法一：树状数组优化 $dp$  
发现 $dp_i=\max_{1\le j\le i,a_j<a_i} dp[j]+1$，需要满足 $1\le j\le i$ 和 $p_j<p_i$ 这两个条件，是一种变形的 RMQ 问题，所以可以用树状数组记录 $[1,a_i-1]$ 中 $dp$ 的最大值，当然你也可以用线段树等算法。

至于通过树状数组找出这个子序列我还没有研究清楚。当然线段树是可以的，你可以参考这篇题解：[here](https://www.luogu.com.cn/article/pc7d5o3w)。这里就不给出这种方法的代码了。

法二：二分、贪心  
维护一个递增序列，找到序列中第一个大于等于 $a_i$ 的值，并替换它。若没有，则在最后插入这个数。

![](https://cdn.luogu.com.cn/upload/image_hosting/dav3fksc.png)

故有了AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,p[100005];
int lis[100005],len,now[100005];
int v[100005];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=n;i++){
		int pos=lower_bound(lis+1,lis+len+1,p[i])-lis;
		lis[pos]=p[i];
		now[pos]=i;
		if(pos>len) len++; 
		v[i]=now[pos-1];  
		if(len>=k){ //长度到了 k
			cout<<k<<'\n';
			stack<int>st;//最后要正序输出，所以用了栈
			int j=i;
			while(k--){
				st.push(j); 
				j=v[j]; 
			}
			while(!st.empty()){
				cout<<st.top()<<' ';
				st.pop();
			} 
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
```

我觉得我讲的还算详细吧。

**望管理大大通过！！！**

---

