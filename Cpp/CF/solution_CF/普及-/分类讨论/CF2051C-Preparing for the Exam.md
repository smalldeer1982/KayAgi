# Preparing for the Exam

## 题目描述

Monocarp 正在为他的第一场大学考试做准备。这场考试可能会涉及到 $n$ 个不同的问题，编号从 $1$ 到 $n$。一共有 $m$ 个不同的问题列表，每个列表包含正好 $n-1$ 个不同的问题。对于每个列表 $i$，用一个整数 $a_i$ 指定唯一没有出现在第 $i$ 个列表中的问题。例如，当 $n = 4$ 且 $a_i = 3$ 时，第 $i$ 个列表里有问题 $[1, 2, 4]$。

在考试的时候，Monocarp 将会拿到其中的一个问题列表，然后老师会要求他回答列表中所有的问题。要通过考试，Monocarp 必须回答列表中所有问题。

Monocarp 已经掌握了 $k$ 个问题的答案，这些问题编号是 $q_1, q_2, \dots, q_k$。请判断对于每一个问题列表，Monocarp 是否能够通过考试。

## 说明/提示

在第一个测试用例中，Monocarp 已掌握的问题是 $[1, 3, 4]$。我们来看所有的问题列表：

- 第一个列表的问题是 $[2, 3, 4]$。Monocarp 不懂第 $2$ 个问题，所以不能通过；
- 第二个列表的问题是 $[1, 3, 4]$。Monocarp 知道这些问题，因此能通过；
- 第三个列表的问题是 $[1, 2, 4]$。Monocarp 不懂第 $2$ 个问题，所以不能通过；
- 第四个列表的问题是 $[1, 2, 3]$。Monocarp 不懂第 $2$ 个问题，所以不能通过。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
4 4 3
1 2 3 4
1 3 4
5 4 3
1 2 3 4
1 3 4
4 4 4
1 2 3 4
1 2 3 4
2 2 1
1 2
2```

### 输出

```
0100
0000
1111
10```

# 题解

## 作者：封禁用户 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/CF2051C) / [Codeforces 传送门](https://codeforces.com/contest/2051/problem/C)

恼，赛时调了半天才 AC。

感谢 @[ZMQ_Ink6556](/user/1125291) 大佬的指导，在这里膜拜 %%%。

---

分类讨论。

先用一个 map 映射来标记 Monocarp 知道的问题。然后就开始分讨：

+ 如果 $k<n-1$，也就是 Monocarp 知道的问题数量少于 $n-1$ 个，那么他就无法通过任意一个问题，所以输出 $m$ 个 $0$；
+ 如果 $k=n$，也就是 Monocarp 知道所有的问题，那么他就必然可以回答所有的问题，所以输出 $m$ 个 $1$；
+ 如果 $k=n-1$，也就是 Monocarp 知道的问题数量恰好是 $n-1$ 个，那么他只缺少一个问题，所以我们需要遍历检查一下，如果他缺失的问题没有被映射标记，也就是他知道这个问题，则输出 $1$，否则输出 $0$。

记得多测清空映射。

```cpp
#include <iostream>
#include <map>
using namespace std;

const int N = 3e5 + 5;

int a[N], q[N];
map<int, bool> vis;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		vis.clear();
		int n, m, k;
		cin >> n >> m >> k;
		for (int i = 1; i <= m; i++)
			cin >> a[i];
		for (int i = 1; i <= k; i++)
		{
			cin >> q[i];
			vis[q[i]] = true;
		}
		if (k < n - 1)
		{
			for (int i = 1; i <= m; i++)
				cout << "0";
		}
		else if (k == n)
		{
			for (int i = 1; i <= m; i++)
				cout << "1";
		}
		else if (k == n - 1)
		{
			for (int i = 1; i <= m; i++)
			{
				if (!vis[a[i]]) cout << "1";
				else cout << "0";
			}
		}
        cout << "\n";
	}
	return 0;
}
```

---

## 作者：JimmyQ (赞：2)

# CF2051C Preparing for the Exam
## 思路
其实莫非就三种情况：
- 所有题目都会：所有试卷也都会。
- 有 $\ge 2$ 道题目不会：所有试卷都不会。
- 有 $1$ 道题目不会：假设这道题目是 $x$，那么遍历数组 $q$ 寻找是否有 $q_i=x$，如果有则输出 $1$，否者输出 $0$。
## AC 代码
时间复杂度为$\Theta(tn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 300005
long long n,m,k,t,b[N],q[N],vis[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=m;i++) cin>>b[i];
		for(int i=1;i<=k;i++) cin>>q[i];
		if(k==n){
			for(int i=1;i<=m;i++) cout<<1;
		}
		else if(k==n-1){
			long long now;
			for(int i=1;i<=k;i++) vis[q[i]]=1;
			for(int i=1;i<=n;i++){
				if(vis[i]==0){
					now=i;
					break;
				}
			}
			for(int i=1;i<=m;i++){
				if(b[i]==now) cout<<1;
				else cout<<0; 
			}
		}
		else for(int i=1;i<=m;i++) cout<<0;
		cout<<endl;
	}
	return 0;
} 
```
[AC 记录](https://codeforces.com/contest/2051/submission/297857628)

---

## 作者：jubaoyi2011 (赞：1)

## 思路

分类讨论三种情况。

首先考虑两种极端情况：

1. 所有题目都会，即 $k = n$，那么一定能通过所有考试，所以代码如下：

```cpp
if(n==k){
    for(int i=1;i<=m;i++){
        cout<<1;
    }
    continue;
}
```

2. 所有题目都不会，即 $k < n - 1$ ，那么一定不能通过所有的考试，所以代码如下：

```cpp
if(k<n-1){
    for(int i=1;i<=m;i++){
        cout<<0;
    }
    continue;
}
```

3. 只有一道题目不会，这是可以记下他会的题目，如果缺少的题目正好是他不会的那道，则可以通过，否则不能。

## 最终代码


```cpp
#include <bits/stdc++.h>

using namespace std;
int t,n,k,m,a[300005],q[300005];
main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--){
		bool f[300005]={0};
		cin>>n>>m>>k;
		for(int i=1;i<=m;i++)cin>>a[i];
		for(int i=1;i<=k;i++){
			cin>>q[i];
			f[q[i]]=1;
		}
		if(n==k){
			for(int i=1;i<=m;i++)cout<<1;
			cout<<endl;
			continue;
		}
		if(k<n-1){
			for(int i=1;i<=m;i++)cout<<0;
			cout<<endl;
			continue;
		}
		for(int i=1;i<=m;i++){
			if(f[a[i]]==1)cout<<0;
			else cout<<1;
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：All_Wrong_Answer (赞：1)

[原题传送门](https://codeforces.com/problemset/problem/2051/C)

## 思路：

**分类讨论**，显而易见的：

1. 如果 $k+1<n$ 那么对于题目的任何一种组合，Monocarp 都做不出来，直接输出 $k$ 个 $0$。
2. 如果 $k+1=n$ 那么就需要找到 Monocarp 不会做的那道题目，当某一个题目的组合方式中恰好不包含 Monocarp 不会做的题时，输出 $1$，否则输出 $0$。
3. 如果 $k=n$ 那么很明显 Monocarp 会做全部的题目，输出 $k$ 个 $1$。

判断当前题目的组合方式是否恰好不包含 Monocarp 不会做的题可以用 map 处理。

**细节**：多测要清空 map，但一定不要用 memset！

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int a,b,c;
int m[1000006];
map<int,bool>f; 
void work(){
	for(int k=1;k<=b;k++){
		if(f[m[k]]==false) cout<<1;//恰好不包含Monocarp不会做的题，输出1 
		else cout<<0;//否则输出0 
	}
	cout<<endl;
	return ;
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>a>>b>>c;
		//memset(m,0,sizeof(m)); 这个千万不能用，不然会T飞 
		f.clear();//清空map 
		for(int j=1;j<=b;j++) cin>>m[j];
		int u;
		for(int j=1;j<=c;j++){
			cin>>u;
			f[u]=true;
		}
		if(c+1<a){//上文的情况1 
			for(int j=1;j<=b;j++) cout<<0;
			cout<<endl;
		}
		else if(c==a){//上文的情况3 
			for(int j=1;j<=b;j++) cout<<1;
			cout<<endl;
		}
		else {//上文的情况2 
			work();
		}
	}
	return 0;
}

```


[AC 记录](https://codeforces.com/contest/2051/submission/298762858)

---

## 作者：N1tr0us_Acid (赞：1)

upd：修改了错误的字。

~赛时瞬秒题。~

# $\texttt{Solution}$
因为每一次考试只会缺一道考题，所以如果这个人知道的题目数与总题数差**一题以上**，即 $k < n - 1$，那么这个人不会通过任何一场考试。同样的，如果 $n = k$，那么这个人将会通过所有考试。

只需要考虑 $k = n - 1$ 的情况。

我们可以记下这个人不知道哪一题，然后对每场考试进行遍历，如果这场考试缺少的正好是这个人不知道的题，那么就可以通过，否则都不能通过。

# $\texttt{Code}$
显而易见了。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 3e5 + 10;

int tt;
int n, m, k;

int a[N], q[N];

signed main() {
	cin >> tt;

	while (tt --) {
		cin >> n >> m >> k;

		int g; // 用于记录这个人不知道的题目。

		for (int i = 1; i <= m; i ++) {
			cin >> a[i];
		}

		for (int i = 1; i <= k; i ++) {
			cin >> q[i];
		}

		g = 1;

		for (int i = 1; i <= k; i ++) {
			if(q[i] == g) g ++; // 取 mex 
			else if(q[i] > g) break;
		}

		if(n - k > 1) { // n - k > 1，不会通过任何一场考试
			for (int i = 1; i <= m; i ++) {
				cout << '0';
			}

			puts("");
		}

		else if(n == k) { // n = k，会通过所有考试。
			for (int i = 1; i <= m; i ++) {
				cout << '1';
			}

			puts("");
		}

		else {
			for (int i = 1; i <= m; i ++) {
				if(a[i] != g) cout << '0';
				else cout << '1';
			}

			puts("");
		}
	}
    return 0;
}
```

---

## 作者：alan1118 (赞：1)

## 题意

[【题目】](luogu.com.cn/problem/CF2051C)

题目里说的很清楚了，可以直接看原题。

## 思路

因为每场考试缺少且仅缺少一道题，所以每场比赛的题目数量就是 $n-1$。那么我们就可以看，这场比赛没有的这道题，如果知道答案，那有用的答案就只剩下 $k-1$ 个，否则还是 $k$ 个。最后我们只需要判断有用答案的个数是否 $\geq n-1$ 就可以了。

## Code
```cpp
#include <iostream>
using namespace std;
 
const int N = 3e5 + 5;
 
int a[N], b[N];
bool vis[N];
 
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n, m, k;
		cin >> n >> m >> k;
		for(int i = 1; i <= n; i++) vis[i] = false;
		for(int i = 1; i <= m; i++) cin >> a[i];
		for(int i = 1; i <= k; i++)
		{
			cin >> b[i];
			vis[b[i]] = true;
		}
		for(int i = 1; i <= m; i++)
		{
			if(k-vis[a[i]] >= n-1) cout << '1';
			else cout << '0';
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Zhang_Shao_ (赞：0)

### 题意
一共有 $n$ 个不同的问题，编号从 $1$ 到 $n$。有 $m$ 种不同的问题列表；每个列表正好由 $n-1$ 个不同的问题组成。每个列表 $i$ 包含除第 $a_i$ 个问题以外的所有问题。例如，如果 $n=4$ 且 $a_i=3$，则第 $i$ 列表包含问题 $[1,2,4]$。现在你已经知道了 $k$ 个问题的答案，问能否答对每个问题列表。
### 解法
因为每个问题列表都有 $n-1$ 个问题，所以只要问题数量 $n$ 与已知答案数量 $k$ 的差大于 $1$，那么就无法答对任何问题列表。如果 $n-k=1$，且不知道第 $x$ 个答案，那么只有第 $i$ 个问题 $(a_i=x)$ 能答对。如果已经知道所有问题的答案，那么每一个问题都能答对。这样的复杂度最大为 $O(tn)$。
### 代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int a[300005];
bool vis[300005];//存储已知答案
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		memset(vis,0,sizeof(vis));
		int n,m,k,b=-1;
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=m;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=k;i++){
			int x;
			scanf("%d",&x);
			vis[x]=1;
		}
		if(k+1<n){//特殊情况
			for(int i=1;i<=m;i++){
				printf("0");
			}
			printf("\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(vis[i]==0){
				b=i;
				break;
			}
		}
		if(b<0){
			for(int i=1;i<=m;i++){
				printf("1");
			}
			printf("\n");
			continue;
		}
		for(int i=1;i<=m;i++){
			if(b==a[i]) printf("1");
			else printf("0");
		}
		printf("\n");
	}
	return 0;//结束
}
```

---

## 作者：Lfz312g (赞：0)

# Solition
## 思路分析
对于 Monocarp 不知道的问题，也就是 $n-k$，有以下的分类讨论。  
如果 $n-k = 0$ 也就是 Monocarp 没有不知道的问题，此时全部输出 ```1``` 即可，一定能通过所有的考试。  
如果 $n-k \ge 2$ 那么哪怕有不存在的问题，Monocarp 也无法全部回答出，全部输出 ```0``` 即可。  
如果 $n-k = 1$ 遍历找到 Monocarp 唯一不知道的问题，如果问题列表中恰好没有这份问题，输出 ```1``` 即可，否则输出 ```0```。  
时间复杂度：$O(n)$。  
## 代码实现

```cpp
#include <bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
const int Maxn=3e5+27,mod=1e9+7;
int vis[Maxn],text[Maxn];
void solve() {
	int n,m,k;
	cin>>n>>m>>k;
	ffor(i,1,n) vis[i]=0;
	ffor(i,1,m) cin>>text[i];
	int sum=0;
	ffor(i,1,k) {
		int x;
		cin>>x;
		if (!vis[x]) sum++;
		vis[x]=1;
	}
	sum=n-k;
	if (!sum) {
		ffor(i,1,m) cout<<1;
		putchar('\n');
		return;
	}
	if (sum>=2) {
		ffor(i,1,m) cout<<0;
		putchar('\n');
		return;
	}
	if (sum==1) {
		int ys;
		ffor(i,1,n) {
			if (!vis[i]) {
				ys=i;
				break;
			}
		}
		ffor(i,1,m) cout<<(text[i]==ys?1:0);
		putchar('\n');
	}
	return;
}
int main()
{
	int T;
	cin>>T;
	while (T--) solve();
}
```

---

## 作者：Angelina188 (赞：0)

### 思路
首先特判两种情况：
- 全部输出 $0$：$k$ 等于 $n$ 时，所有题目和试卷都会；
- 全部输出 $1$：$k$ 小于 $n-1$ 时，所有试卷都不会。

接下来就剩下只有一道题不会的情况。题目说“每个列表恰好包含 $n−1$ 道不同的问题”，所以用统计他会的题目是哪些。然后遍历数组 $a$，若该题不会，则其他题目都会，可以通过。
### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int T,n,m,k,a[N],x;
bool p[N];//统计数组
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		memset(p,0,sizeof p);
		for(int i=1;i<=m;i++) cin>>a[i];
		for(int i=1;i<=k;i++){
			cin>>x;
			p[x]=1;
		}
		if(k<n-1){
			for(int i=1;i<=m;i++)
				cout<<"0";
			cout<<"\n";
			continue;
		}
		if(k==n){
			for(int i=1;i<=m;i++)
				cout<<"1";
			cout<<"\n";
			continue;
		}
		for(int i=1;i<=m;i++){
			if(p[a[i]]==0) cout<<"1";
			else cout<<"0";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Luo_Yicheng (赞：0)

### 分析
此题的 $n\le10^4,\sum_{i=1}^{t}n\le3\times10^5,\sum_{i=1}^{t}m\le3\times10^5,\sum_{i=1}^{t}k\le3\times10^5$ 此时可以 $O(m+k)$ 借助 map 求解答案。

### 解题方法
分类讨论。

先用一个 map 映射来标记 Monocarp 知道的问题。然后就开始分讨：

+ 如果 $k<n−1$，也就是 Monocarp 知道的问题数量少于 $n−1$ 个，那么他就无法通过任意一个问题，所以输出 $m$ 个 $0$；
+ 如果 $k=n$，也就是 Monocarp 知道所有的问题，那么他就必然可以回答所有的问题，所以输出 $m$ 个 $1$；
+ 如果 $k=n−1$，也就是 Monocarp 知道的问题数量恰好是 $n−1$ 个，那么他只缺少一个问题，所以我们需要遍历检查一下，如果他缺失的问题没有被映射标记，也就是他知道这个问题，则输出 $1$，否则输出 $0$。

### 总结
最终代码时间复杂度 $O(m+k)$。

---

## 作者：DoubleQLzn (赞：0)

由于每一场考试都只缺 $1$ 道题，所以就有以下情况：

- 都会，全部问题都可答出来。
- 不会的大于 $1$，全部问题都答不出来。
- 不会的等于 $1$，当不会的是刚刚好是缺少的问题时答出来。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int f[300005],a[300005],f2[300005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t,n,m,k;
	cin>>t;
	while(t--){
	
		cin>>n>>m>>k;
		fill(f+1,f+n+1,0);
		for(int i=1;i<=m;i++)cin>>a[i];
		for(int i=1;i<=k;i++){
			int x;//c
			cin>>x;
			f[x]++;
		}
		int s=0,b;
		for(int i=1;i<=n;i++){
			if(!f[i]){
				s++;
				b=i;
			}
		}
		if(s>1){
			for(int i=1;i<=m;i++)cout<<0;
			cout<<'\n';
			continue;
		}
		if(s==0){
			for(int i=1;i<=m;i++)cout<<1;
			cout<<'\n';
			continue;
		}
		for(int i=1;i<=m;i++){
			if(b==a[i])cout<<1;
			else cout<<0;
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Tiger_Rory (赞：0)

我们观察样例后可发现答案分为以下三种情况，分别分析即可：
- 当不知道答案的问题数量大于一个时，可以发现任意一个问题清单都不能通过，因为每个清单中至少有一个问题的答案不知道，故全部输出 $0$ 即可。
- 当不知道答案的问题数量为一个时，令这个不知道答案的问题编号为 $x$，则除了 $a_i = x$ 时清单上所有问题的答案都知道，输出 $1$，其他情况全部输出 $0$ 即可。
- 所有问题的答案都知道时，全部输出 $1$ 即可。

接下来是代码实现。


```cpp
#include<bits/stdc++.h>

using namespace std;

int t, n, m, k, a[300005], q[300005], ans[300005];
bool vis[300005];   

void solve() {
	cin >> n >> m >> k; 
	for(int i = 1; i <= n; i++) vis[i] = false; 
	for(int i = 1; i <= m; i++) cin >> a[i]; 
	for(int i = 1; i <= k; i++) cin >> q[i], vis[q[i]] = true; //用数组标记知道答案的问题
	bool fl = 0; int cnt = 0; 
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			++cnt; 
			if(cnt > 1) {
				for(int j = 1; j <= m; j++) cout << 0; 
				cout << '\n'; 
				return; 
			}//对应第一种情况
		}
	}
	if(cnt) {
		for(int i = 1; i <= m; i++) {
			if(!vis[a[i]]) {
				cout << 1; 
			}
			else cout << 0; 
		}
	}//对应第二种情况
	else {
		for(int i = 1; i <= m; i++) cout << 1; 
	}//对应第三种情况
	cout << '\n'; 
	return; 
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> t; 
	while(t--) {
		solve(); 
	}
	return 0;
}
```
如有不足，还请指出。

---

## 作者：沉石鱼惊旋 (赞：0)

# C. Preparing for the Exam


**分类讨论** $k$ 和 $n$ 的关系。

答案全 $0$ 和全 $1$ 可以先特判掉。全 $0$ 即 $k\leq n-2$，全 $1$ 即 $k=n$。

除了这两种只有 $k=n-1$ 的情况了，我们求出他不会的那一门，可以直接开桶记录，或者算 $x=(\bigoplus\limits_{i=1}^n i )\oplus (\bigoplus\limits_{i=1}^k q_i )$。由于异或的性质我们可以知道最后答案就是遗失的那个数。

对于 $m$ 个询问，答案为 $[x=a_i]$。

<https://codeforces.com/contest/2051/submission/297822232>

---

