# 「OICon-02」Great Segments

## 题目背景

upd：时间限制改为 400ms

[加强版题目推荐](https://www.luogu.com.cn/problem/P11291)

## 题目描述

给定一个长度为 $n$ 的无重复元素序列 $a$。

对于一个区间 $[l,r]$，我们定义它是好的，有以下条件：

1. 定义一个序列 $b=\{ a_l,\max(a_l,a_{l+1}),\max(a_l,a_{l+1},a_{l+2}),\ ...\ ,\max(a_l,a_{l+1},\ ... \ ,a_r)\}$，将该序列进行去重操作后，该序列的长度不超过 $k$ 且大于 $1$；
2. $\max(a_l,a_{l+1},\ ... \ ,a_r)=a_r$。

请你解决这样一个问题：对于每一个 $i \ (1 \le i \le n)$，有多少个好的区间 $[l,r]$ 满足 $l \le i \le r$。

## 说明/提示

### 样例解释

对于样例 $1$，满足条件的区间有：

1. $[1,2]$；
2. $[2,4]$；
3. $[3,4]$。

故当 $i=1,2,3,4$ 时，分别有以下区间满足 $l\leq i\leq r$（根据上述的区间编号）：

1. $1$ 区间；
2. $1,2$ 区间；
3. $2,3$ 区间；
4. $2,3$ 区间。

### 数据范围

**本题采用捆绑测试。**

| $\text{Subtask}$ | 特殊性质 | $\text{Score}$ |
| :----------: | :----------: | :----------: |
| $1$ | $n \le 200$ | $5$ |
| $2$ | $n\leq 2000$ | $10$ | 
| $3$ | $\{a\}$ 递增 | $10$ |
| $4$ | $k\leq 5$ | $12$ |
| $5$ | $k=n$ | $13$ |
| $6$ | $n \le 3 \times 10^5$ | $20$ |
| $7$ | 无特殊限制 | $30$ |

对于 $100\%$ 的数据：$1\leq k\leq n\leq 10^6$，$0\leq a_i\leq 10^9$。

## 样例 #1

### 输入

```
4 2
1 3 2 4```

### 输出

```
1
2
2
2```

# 题解

## 作者：_Cheems (赞：7)

考虑合法区间的判定。先单调栈求出 $nxt_i$ 表示 $a_i$ 右边第一个大于它的元素下标，易发现在序列 $b$ 中，从一段相同元素 $[l1,r1]$ 跳到下一段相同元素 $[l2,r2]$，当且仅当 $l2=nxt_{l1}$。

对于一段区间 $[l,r]$，从 $l$ 开始跳 $nxt$，即不断让 $l=nxt_{l}$ 直到 $l>r$，那么依据题意该区间是合法区间需满足：$1<cnt<=k$，其中 $cnt$ 是总共跳的元素个数；并且最终停在 $r$ 上（上述跳 $nxt$ 过程中遍历到 $r$）。

于是可以得到 $O(n^2)$ 算法，暴力枚举每个合法区间并打上差分标记。

考虑优化，将差分标记拆为加法和减法，尝试对于 $a_i$ 快速求出最终在 $i$ 上打了多少个加法标记、在 $i+1$ 上打上了多少个减法标记，即有多少个合法区间以 $i$ 开头和结尾。

由于每个 $i$ 对应唯一一个 $nxt_i$，考虑将 $nxt_i\to i$ 连一条边，显然会构成森林，其中 $nxt_i=0$ 的元素就是根。

问题被转化为树上问题，对于加标记，可以快速计算得出，记 $dep_i$ 表示 $i$ 的深度，根的深度为 $1$，则 $i$ 上的加标记数量为 $\min(dep,k)-1$。

对于减标记，考虑递推求解，记 $d_i$ 表示 $i$ 上减标记数量，$kson_i$ 表示 $i$ 的所有子孙节点中满足到 $i$ 距离（最短路径边数）为 $k$ 的节点数量，$V_i$ 是 $i$ 的儿子集合。则有 $d_i=(\sum \limits_{j\in V_i} d_j+1) - kson_i$。

最后考虑 $kson_i$ 的求法，只要找出每个点的 $k$ 级祖先即可，可以用栈维护当前点的所有祖先，复杂度线性。

时间复杂度 $O(n)$，空间复杂度 $O(n)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, k, a[N], stk[N], st, d[N], nxt[N];
vector<int> to[N];
long long ans[N];

inline void init(int u){
	if(st - k + 1 > 0) --d[stk[st - k + 1]];
	stk[++st] = u; int stt = st;
	for(auto v : to[u])
		st = stt, init(v);
}
inline void dfs(int u, int dep){
	ans[u] += min(dep, k) - 1;
	for(auto v : to[u]){
		dfs(v, dep + 1);
		d[u] += d[v] + 1;
	}
	ans[u + 1] -= d[u];
}
signed main(){
	cin >> n >> k;
	for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
	for(int i = n; i >= 1; --i){
		while(st && a[stk[st]] <= a[i]) --st; 
		if(st) nxt[i] = stk[st], to[stk[st]].push_back(i);
		stk[++st] = i;
	}
	for(int i = 1; i <= n; ++i)
		if(!nxt[i]) st = 0, init(i), dfs(i, 1);
	for(int i = 1; i <= n; ++i)
		ans[i] += ans[i - 1], printf("%lld\n", ans[i]); 
	return 0;
}
```


---

## 作者：Erine (赞：3)

有趣小清新题目。感觉上次见这个延迟算贡献的 trick 还是在 CF 的一个紫色板子题，怎么到这里成蓝了。

考虑显然的平方做法：从后往前跑单调栈，每到一个点更新单调栈，将栈顶 $k$ 个数对应的区间 $+1$，使用差分实现。

我们发现差分加栈顶是可以延迟贡献的，也就是我们这单调栈上面再做差分，每次要弹出一个点再计算这个点的贡献。因为弹单调栈是连续的，所以我们可以方便地通过单调栈上的差分，计算出每个点的真实贡献。

然后这题就做完了，是线性的。

```cpp
signed main() {
	n = read(), k = read();
	rep(i, 1, n) a[i] = read();
	per(i, n, 1) {
		int sum = 0;
		while (top && a[st[top]] <= a[i]) {
			sum += c[top];
			b[st[top] + 1] += sum;
			c[top--] = 0;
		}
		st[++top] = i;
		b[i] += min(k - 1, top - 1);
		c[top - 1] += sum - 1;
		c[max(top - k, 0ll)]++;
	}
	int sum = 0;
	while (top) {
		sum += c[top];
		b[st[top] + 1] += sum;
		c[top--] = 0;
	}
	rep(i, 1, n) b[i] += b[i - 1];
	rep(i, 1, n) write(b[i]), pc('\n');
    return 0;
}
```

---

## 作者：zjinze (赞：1)

令 $R_i$ 表示区间 $[i+1,n]$ 中第一个比 $a_i$ 大的值，则对于每一个合法区间，区间右端点 $r$ 必在每次 $i$ 往后跳到 $R_i$ 的路径上，且跳跃次数最少为一次，最多为 $k-1$ 次。

为什么？

$b$ 序列中不同元素的个数本质上是从区间左端点 $l$ 每次往右跳到第一个比它大的元素位置，能跳到的点的数量（包括区间左端点 $l$）。显然，在这个序列上任取一个点 $r$，都满足 $a_i$ 是区间 $[l,r]$ 中的最大值。

对于每一点 $i$，它都有唯一的 $R_i$，且跳跃的过程类似树上问题跳祖先和跳子孙，所以我们考虑将 $R_i$ 向 $i$ 连边。问题转换为每个点被树上多少条长度在 $[1,k-1]$ 的链覆盖，且这条链的深度更浅的端点是这条链两端点的最近公共祖先（即这条链没有拐弯）。

区间覆盖问题考虑差分。显然我们不可能对所有区间直接枚举差分，所以我们枚举区间左端点，在差分数组上加一，但这时左端点的 $i$ 级祖先处要剪掉 $i-1$（$i \leq k-1$）。因为前 $i-1$ 次跳跃无法覆盖第 $i$ 次跳跃才能新覆盖到的点。由于减的是一个等差序列，所以我们考虑二次差分，在原差分数组上在进行差分即可，第二次差分在树上累计，第一次差分在原数组上累计即可。对于每个点的第 $k-1$ 级祖先是在求单调栈时距栈顶 $k-1$ 的点。

然后这道题就做完了。

---

## 作者：george0929 (赞：1)

### $n \le 200$ 

枚举左右端点，扫一遍检查是否符合题意。

代码略。

### $n \le 2000$ 

枚举左右端点，边枚举边检查，差分计算答案。

```cpp
for(int l=1;l<n;l++){
	int cnt=1,mx=arr[l],ed=l,st=-1;
	for(int r=l+1;r<=n;r++){
		if(arr[r]>mx){
			mx=arr[r];
			cnt++;
			if(cnt<=k){
				ans[l]++;
				ans[r+1]--;
			}
		}
		if(cnt>k){
			ed=r-1;
			break;
		}
	}
}
for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
for(int i=1;i<=n;i++){
	cout<<ans[i]<<"\n";
}
```

### $\{a\} $ 递增 

问题转换为包含 $i$ 的长度为 $[2,k]$ 的区间有多少个。

枚举左端点，二阶差分计算答案。

```cpp
void add(int l,int r,int s,int t,int d){
	if(l>r) return;
	ans[l]+=s;
	ans[l+1]+=d-s;
	ans[r+1]-=t+d;
	ans[r+2]+=t;
}

for(int l=1;l<=n;l++){
	add(l,l,min(n,l+k-1)-l,min(n,l+k-1)-l,-1);
	add(l+1,min(n,l+k-1),min(n,l+k-1)-l,1,-1);
}
for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
for(int i=1;i<=n;i++){
	cout<<ans[i]<<"\n";
}
```

### $k = n$ 

本质上忽略了条件 $1$。

单调栈记录数字 $i$ 前面第一个比它大的数的位置 $pos$，则区间 $[pos+1,i]\ ,\ [pos+2,i]\ \dots\ [i-1,i]$ 符合题意。

二阶差分计算答案。

```cpp
void add(int l,int r,int s,int t,int d){
	if(l>r) return;
	ans[l]+=s;
	ans[l+1]+=d-s;
	ans[r+1]-=t+d;
	ans[r+2]+=t;
}

stack<int> S;
while(!S.empty()) S.pop();
for(int i=n;i>=1;i--){
	while(!S.empty()&&arr[S.top()]<arr[i]){
		g[S.top()]=i;
		S.pop();
	}
	S.push(i);
}
for(int i=2;i<=n;i++){
	if(g[i]==i-1) continue;
	int l=g[i]+1,r=i-1;
	add(i,i,r-l+1,r-l+1,1);
	add(l,r,1,r-l+1,1);
}
for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
for(int i=1;i<=n;i++){
	cout<<ans[i]<<"\n";
}
```

### $k \le 5$ 

考虑优化 $n \le 2000$ 的做法，单调栈记录每个数字往后第一个比它大的位置，然后一步步往后跳。

```cpp
stack<int> S;
while(!S.empty()) S.pop();
for(int i=1;i<=n;i++){
	while(!S.empty()&&arr[S.top()]<arr[i]){
		g[S.top()]=i;
		S.pop();
	}
	S.push(i);
}
for(int l=1;l<n;l++){
	int cnt=1,tl=l;
	while(cnt<=k){
		int pos=g[tl];
		if(pos==0) break;
		cnt++;
		if(cnt>k) break;
		ans[l]++;
		ans[pos+1]--;
		tl=pos;
	}
}
for(int i=1;i<=n;i++) ans[i]+=ans[i-1];
for(int i=1;i<=n;i++){
	cout<<ans[i]<<"\n";
}
```

### $n \le 10 ^ 6$ 

考虑优化 $k \le 5$ 做法，我们发现一步步令 $l=g[l]$ 非常像树上暴力找祖先。

将 $g[i]$ 看作 $i$ 的祖先，则对于每个 $l$ 本质上操作为：

```cpp
ans[l]+=min(k-1,l的深度-1)
ans[(l的每个距离小于k的祖先)+1]--
```

发现可以树上差分，但由于下标错开了 $1$，所以要新开一个数组记录减法操作，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int arr[1000005];
long long ans[1000005];
void add(int l,int r,int s,int t,int d){
	if(l>r) return;
	ans[l]+=s;
	ans[l+1]+=d-s;
	ans[r+1]-=t+d;
	ans[r+2]+=t;
}
int g[1000005];
int n,k,f=1;
int sz[1000005];
int fa[1000005][21];
inline int dfs(int i){
	if(sz[i]||i==0) return sz[i];
	return sz[i]=dfs(g[i])+1;
}
vector<int> V[1000005];
int pans[1000005];
inline void reb(int u,int fa){
	for(int v:V[u]){
		if(v==fa) continue;
		reb(v,u);
		pans[u]+=pans[v];
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	if(k<=1){
		for(int i=1;i<=n;i++){
			cout<<"0\n";
		}
	}
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}
	stack<int> S;
	while(!S.empty()) S.pop();
	for(int i=1;i<=n;i++){
		while(!S.empty()&&arr[S.top()]<arr[i]){
			g[S.top()]=i;
			S.pop();
		}
		S.push(i);
	}
	for(int i=1;i<=n;i++){
		sz[i]=dfs(i);
		fa[i][0]=g[i];
		V[i].push_back(g[i]);
		V[g[i]].push_back(i);
	}
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1];
		}
	}
	for(int l=1;l<n;l++){
		ans[l]+=min(k-1,sz[l]-1);
		pans[fa[l][0]]--;
		int tt=k-1,u=l;
		for(int j=20;j>=0;j--){
			if(tt>=(1<<j)){
				tt-=(1<<j);
				u=fa[u][j];
			}
		}
		pans[fa[u][0]]++;
	}
	reb(0,-1);
	for(int i=1;i<=n;i++){
		if(i!=1) ans[i]+=(long long)pans[i-1];
		ans[i]+=ans[i-1];
	}
	for(int i=1;i<=n;i++){
		cout<<ans[i]<<"\n";
	}
	return 0;
}

```



---

## 作者：bluewindde (赞：0)

转述题意：一个区间是好的，当且仅当其有 $2 \sim k$ 个前缀最大值，且右端点是一个前缀最大值。

对于前缀最大值，容易想到单调栈：从后往前扫，维护前缀最大值组成的单调栈，则只有以当前位置为左端点，以栈内第 $2 \sim k$ 个位置为右端点的区间是好的。对每个这样的区间将，答案区间加一即可。

区间加一使用差分实现，单调栈上因为位置连续也可以差分实现，两次差分后时间复杂度 $O(n)$，可以通过。

```cpp
#include <iostream>

#define int long long

using namespace std;

int n, k;
int a[1000005];

int sta[1000005], tail;
int tag[1000005];
int ans[1000005];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    sta[0] = n + 1;
    for (int i = n; i; --i) {
        while (tail && a[sta[tail]] <= a[i]) {
            ans[sta[tail] + 1] += tag[tail];
            tag[tail - 1] += tag[tail];
            --tail;
        }
        sta[++tail] = i;
        tag[tail] = 0;
        ans[i] += min(tail, k) - 1;
        --tag[tail - 1];
        ++tag[max(tail - k, 0ll)];
        // for (int j = tail - 1; j > tail - k && j; --j)
        //     --ans[sta[j] + 1];
    }
    while (tail) {
        ans[sta[tail] + 1] += tag[tail];
        tag[tail - 1] += tag[tail];
        --tail;
    }
    for (int i = 1; i <= n; ++i) {
        ans[i] += ans[i - 1];
        cout << ans[i] << '\n';
    }
    cout.flush();
    return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

先考虑判定 $(l,r)$ 合法。

注意到 $a_i$ 互不相同，因此在 $l<r$ 时一定有去重后的序列长度 $>1$。

这种不同序列最大值还涉及大小关系的状物，可以试一试笛卡尔树的思想（这题只需要求后继）。考虑求 $nxt_i$ 表示对于 $i$，下一个大于 $a_i$ 的位置是 $nxt_i$，特别的，如果不存在记录为 $n+1$。考虑 $nxt_i$ 的性质，如果把一次求 $nxt$ 看成往后面跳，那么会发现最后都跳到 $r$ 上。也就是说看成一堆区间 $[i,nxt_i]$ 后，不会存在不完全相交，只有相离和包含。也就是说把它画在平面上的同一侧，是没有交点的。也就是说，下图的情况是**不会**出现的。

![](https://cdn.luogu.com.cn/upload/image_hosting/asxc0po2.png)

也就是说图一定长成这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/zrqxq9ws.png)

考虑随便构造一组满足这个连边的序列 $\lbrace 3,4,1,2,5\rbrace$。容易发现，只有 $3,4,5$ 对去重后序列的长度造成了贡献。再次观察，其实就是 $l$ 往后不断地跳 $nxt$ 最后跳到 $r$。设 $r$ 是 $l$ 跳了 $i$ 次后到达的，那么这个序列去重后的长度是 $i+1$。

不断往后跳，这个其实很明显了。可以把 $nxt_i$ 的关系建成一棵根为 $n+1$ 的树。其中对于所有 $1\leq i\leq n$，有连边 $i\to nxt_i$。

此时考虑树上的 $i\to j(i<j)$ 的路径就是一个合法的区间 $[i,j]$。

询问是对于每个 $i$ 求有多少个合法区间 $[l,r]$ 使得 $i\in[l,r]$，考虑成所有合法的 $[l,r]$ 作为线段去覆盖数轴。假设我们已经求出所有的合法区间，那么其实可以去用**差分**数组来维护。

也就是说我们不关心怎么覆盖的这个数轴，我们只关心差分数组的**整体情况**。也就是说要求出开头 $l$ 和结尾 $r$ 各自的贡献。

- $l$ 作为开头，我们需要找结尾 $r$。直接往上找前 $k-1$ 个祖先即可。贡献为 $\min(k-1,dep_l-1)$。

- $r$ 作为结尾，我们需要找有多少个 $l$ 可以跳到 $r$。直接维护是困难的，考虑对所有开头 $l$ 去算贡献，往其父亲到 $k-1$ 级祖先链上 $+1$ 即可，此时使用树上差分，找到 $k$ 级祖先维护即可。

注意到 $k$ 级祖先离线用栈维护可以 $O(n)$ 求，没必要用 $\text{polylog}$ 算法。总时间复杂度 $O(n)$。

```cpp
int a[maxn],nxt[maxn],n,k,dep[maxn],st[maxn],top;
ll cf[maxn],c[maxn];
vector<int>g[maxn];
void dfs(int u){
	if(u<=n){
		c[nxt[u]]++;
		if(dep[u]>=k)c[st[dep[u]-k]]--;	
		st[++top]=u;
	}
	for(int v:g[u]) dfs(v);
	if(u<=n)--top;
}
signed main(){
	n=read(),k=read();
	F(i,1,n) a[i]=read();
	st[top=0]=n+1;
	dF(i,n,1) {
		for(;top&&a[st[top]]<a[i];--top);
		nxt[i]=st[top],st[++top]=i;
		dep[i]=dep[nxt[i]]+1;
		cf[i]=min(dep[i],k)-1;
		g[nxt[i]].push_back(i);
	}
	top=0,dfs(n+1);
	F(i,1,n) c[nxt[i]]+=c[i];
	F(i,1,n) cf[i+1]-=c[i];
	F(i,2,n) cf[i]+=cf[i-1];
	F(i,1,n) printf("%lld\n",cf[i]);
}
```

---

## 作者：operator_ (赞：0)

# P10174 Great Segments

[题目传送门](https://www.luogu.com.cn/problem/P10174)

## 题解

个人感觉这是最简单的一题。

考虑什么区间是好的，发现条件等价于从后往前维护单调栈，那么到 $i$ 时，从 $i$ 到单调栈前 $k-1$ 个位置的区间均合法，更一般的，记 $nxt_i$ 表示满足 $i<j,a_i<a_j$ 的最小的 $j$，那么就是 $nxt$ 嵌套 $k-1$ 遍。

这种询问方式不难想到差分，那么左端点是好维护的，右端点的话，我们把每个点的 $nxt$ 视作一条边，则构成了一棵树，我们需要支持多次树链加，单次查询，树上差分即可。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-02-18 14:48:19 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-02-18 17:14:52
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
int n,k,a[1000005],st[1000005],top,fa[1000005],d1[1000005],d2[1000005];
int h[1000005],cnt;
struct QWQ{int v,nxt;} e[1000005*2];
void add(int u,int v) {e[++cnt]={v,h[u]},h[u]=cnt;}
void dfs(int u) {
    for(int i=h[u];i;i=e[i].nxt) 
        dfs(e[i].v),d2[u]+=d2[e[i].v];
}
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) a[i]=rd();
    for(int i=n;i>=1;i--) {
        while(top&&a[st[top]]<a[i]) top--;
        fa[i]=st[top],add(fa[i],i),st[++top]=i;
        d1[i]+=min(top,k)-1;
        d2[fa[i]]--,d2[fa[st[top+1-min(top,k)]]]++;
    }
    dfs(0);
    for(int i=1;i<=n;i++) d1[i+1]+=d2[i];
    for(int i=1;i<=n;i++) {
        d1[i]+=d1[i-1];
        printf("%lld\n",d1[i]);
    }
    return 0;
}
```

---

## 作者：_LiWenX_ (赞：0)

赛时的奇怪做法。

我们记 $nex_i$ 表示 $i$ 后面第 $1$ 个比 $a_i$ 大的数的下标。

于是可以发现这个合法区间，我们枚举 $l$ 那么 $r$ 它一定是由左端点跳了至多 $k-1$ 次，至少一次的的终点中的一个。

如果我们可以求出有多少区间由 $i$ 开始，由 $i$ 结束，那么我们就可以用差分维护扫描线解决这个问题。

为了方便分析，可以建一颗跳跃树，由 $nex_i\to i$ 这样连边。（要注意这样可能建出一个森林）。

于是合法的区间可以在树上抽象成一颗由儿子到祖先的，长度不超过 $k-1$ 的链。

那么有一个 $O(nk)$ 的暴力，对于每个节点，往上条约 $k-1$ 步，看看这个节点最多可以跳多少步，同时对于这些祖先也可以统计由多少区间由它结束。

我们希望优化这个过程。

对于节点 $x$ 能跳多少步，显然是 $\min(k-1,dep_x)$（规定根节点的 $dep$ 为 $0$）。

唯一的问题是看看有多少区间由它结尾。

分析一下就可以发现，这个答案就是距离 $x$ 不超过 $k-1$ 的儿子的数量，那这不是长链剖分优化 dp 的板子吗，然后就做完了，由于每一步我们都做到了线性，所以总算法的时间复杂度为 $O(n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int from,to;
}e[1000001];int head[1000001],Stree;
void addedge(int x,int y){
	e[++Stree].to=y;
	e[Stree].from=head[x],head[x]=Stree;
}
int n,k,re[1000001],sta[1000001],top;
int ans[1000001],c[1000001];
int a[1000001];
int md[1000001],son[1000001];
void dfs1(int now){
	for(int i=head[now];i;i=e[i].from){
		int u=e[i].to;
		dfs1(u);
		if(md[son[now]]<md[u]) son[now]=u;
	}
	md[now]=md[son[now]]+1;
}
int neicunchi[1000001<<3],*buf=neicunchi;
int *f[1000001];
void dfs2(int now,int dep){
	c[now]+=min(dep,k);
	if(son[now]){
		f[son[now]]=f[now]+1;
		dfs2(son[now],dep+1);
	}
	f[now][0]++;
	ans[now]=ans[son[now]];
	for(int i=head[now];i;i=e[i].from){
		int u=e[i].to;
		if(u==son[now]) continue;
		f[u]=buf,buf+=(md[u]*2);
		dfs2(u,dep+1);
		ans[now]+=ans[u];
		for(int i=0;i<md[u];i++) f[now][i+1]+=f[u][i];
	}
	if(son[now]) ans[now]+=f[now][1];
	if(md[now]>=k+1)ans[now]-=f[now][k+1];
	c[now+1]-=ans[now];
}
int main(){
	cin>>n>>k;k--;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		while(top&&a[sta[top]]<a[i]){
			re[sta[top]]=i;
			addedge(i,sta[top]);
			top--;
		}
		sta[++top]=i;
	}
	vector<int> vec;
	for(int i=1;i<=n;i++){
		if(!re[i]) vec.push_back(i);
	}
	for(int u:vec) dfs1(u);
	for(int u:vec){
		f[u]=buf;
		buf+=(md[u]*2);
		dfs2(u,0);
	}
	long long x=0;
	for(int i=1;i<=n;i++){
		x+=c[i];
		cout<<x<<'\n';
	}
}
```

---

