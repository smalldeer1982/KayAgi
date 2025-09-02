# [USACO22FEB] Email Filing S

## 题目描述

Farmer John 在整理他的收件箱时落后了。他的屏幕布局如下：屏幕左侧是文件夹的垂直列表，右侧是邮件的垂直列表。总共有 $M$ 个文件夹，编号为 $1 \ldots M$（$1 \leq M \leq 10^4$）。他的收件箱目前包含 $N$ 封邮件，编号为 $1 \ldots N$（$1 \leq N \leq 10^5$）；第 $i$ 封邮件需要归档到文件夹 $f_i$（$1 \leq f_i \leq M$）。

FJ 的屏幕很小，因此他一次只能查看 $K$ 个文件夹和 $K$ 封邮件（$1 \leq K \leq \min(N, M)$）。初始时，他的屏幕显示左侧的文件夹 $1 \ldots K$ 和右侧的邮件 $1 \ldots K$。为了访问其他文件夹和邮件，他需要滚动这些列表。例如，如果他在文件夹列表中向下滚动一个位置，屏幕将显示文件夹 $2 \ldots K+1$，再向下滚动一个位置则显示文件夹 $3 \ldots K+2$。当 FJ 将一封邮件拖入文件夹时，该邮件会从邮件列表中消失，其后的邮件会向前移动一个位置。例如，如果当前显示的邮件是 $1, 2, 3, 4, 5$，而 FJ 将邮件 $3$ 拖入其对应的文件夹，邮件列表将显示 $1, 2, 4, 5, 6$。FJ 只能将邮件拖入其需要归档的文件夹。

不幸的是，FJ 的鼠标滚轮坏了，他只能向下滚动，不能向上滚动。唯一能实现类似向上滚动的效果是，当他查看邮件列表的最后 $K$ 封邮件时，如果他归档了其中一封邮件，邮件列表将再次显示尚未归档的最后 $K$ 封邮件，从而将最上面的邮件向上滚动一个位置。如果剩余的邮件少于 $K$ 封，则显示所有剩余的邮件。

请帮助 FJ 判断是否能够归档所有邮件。

## 说明/提示

- 在输入 2-10 中，所有子用例的 $M$ 之和不超过 $10^3$。
- 在输入 11-12 中，没有额外限制。

## 样例 #1

### 输入

```
6
5 5 1
1 2 3 4 5
5 5 1
1 2 3 5 4
5 5 1
1 2 4 5 3
5 5 2
1 2 4 5 3
3 10 2
1 3 2 1 3 2 1 3 2 1
3 10 1
1 3 2 1 3 2 1 3 2 1```

### 输出

```
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：sprads (赞：15)

### 前言

平凡的模拟题 + 一些贪心。

不建议看题解，建议自己先写一写，~~说不定就过了~~。

### 名称约定

$m$ 个文件夹，$n$ 封邮件，电脑屏幕只能显示 $K$ 封邮件和文件夹。

$i$ 表示第 $i$ 个文件夹，$j$ 表示第 $j$ 封邮件。

$\forall j\in [1,n]$，$f_j$ 表示 $j$ 应投入的文件夹。

目标将所有邮件投入对应的文件夹中。

### 分析

**两个性质：**
1. 某一个文件夹一旦翻出屏幕，就回不来了（~~你不能让其他文件夹消失，让它掉回来~~）。

2. 根据 1，我们发现，当屏幕显示 $i\sim i+K-1$ 时，**只有**当**所有** $f_j = i$ 的邮件都放进文件夹 $i$ 时，才能上翻，把文件夹 $i$ 踢出屏幕（只有这样才能完成目标）。

### 流程

1. 根据性质 2，我们直接枚举 $1\sim m$。为了方便判断，引入 $c_i$，表示还未放入且 $f_j=i$ 的邮件的数量。枚举 $i$ 就代表应将 $c_i$ 减为 $0$。

2. 注意到相比于 $i-1(i>1)$，屏幕多显示出了 $i+K-1$（也只多了这一个文件夹）。将**此时**在**屏幕中的** $f_j=i+K-1$ 的邮件放入 $i+K-1$。于是就需要用 `set` 维护屏幕，方便删除；用 $m$ 个 `queue` 维护每个文件夹**在屏幕中的**邮件。

3. 分两种情况考虑邮件：

	- 屏幕下方还有邮件，把它翻上来：如果屏幕中有 $K$ 封邮件，就把其中的第一封翻上去（这里可以用一个栈维护被翻上去的邮件）。其次，若新加入的邮件 $j$ 满足 $f_j\in[i,i+K-1]$，直接让 $c_{f_j}$ 减 $1$ 即可，否则邮件就得进入屏幕。 

	- 屏幕下方没有邮件，已经滚上去的邮件掉回屏幕：从维护滚上去邮件的栈中取出栈顶，同上面类似处理。不同的是，当屏幕中已有 $K$ 封邮件时，就代表无法完成目标，输出 `NO`。 

4. 如果成功枚举完 $1\sim m$，就代表可以完成任务，输出 `YES`。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100005,M = 10005;
set<int> sce;//维护屏幕的set
queue<int> q[M];//维护每个文件夹在屏幕中的邮件的queue
int T,n,m,K,f[N],c[N],top,st[N];//维护滚出屏幕邮件的栈
int rd(){
	int x = 0,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
void init(){//多测注意初始化 
	top = 0;
	sce.clear();
	for(int i = 1;i <= m;i++)
		while(!q[i].empty())q[i].pop();
	memset(c,0,sizeof(c));
}
bool check(){
	int j = 1,t;
	set<int>::iterator it;
	for(int i = 1;i <= m;i++){
		t = i + K - 1;
		if(t <= m){//处理新进入屏幕的文件夹 
			c[t] -= q[t].size();
			while(!q[t].empty()){//处理f[j]=i+K-1的邮件
				int x = q[t].front(); 
				q[t].pop();
				sce.erase(x);
			}
		}
		while(c[i]){//目标把文件夹 i 废掉。处理掉文件夹 i，就可以暂停处理邮件，优先翻出新的文件夹 
			int x = j <= n ? j : st[top--];//两种情况 
			if(sce.size() == K){
				if(j <= n){
					it = sce.begin();//踢出屏幕最顶上的邮件，维护set和queue和栈
					st[++top] = *it;
					q[f[*it]].pop();
					sce.erase(*it);
				}
				else return 0;//邮件的第二种情况，无解 
			}
			if(f[x] <= t)
				c[f[x]]--;
			else{
				sce.insert(x);//屏幕中加入新邮件 
				q[f[x]].push(x);
			}
			if(j <= n)j++;//往后一封邮件 
		}
	}
	return 1;
}
int main(){
	T = rd();
	while(T--){
		m = rd(),n = rd(),K = rd();
		init();
		for(int i = 1;i <= n;i++)
			f[i] = rd(),c[f[i]]++;
		check() ? puts("YES") : puts("NO");
	}
	return 0;
}
```


---

## 作者：dino (赞：13)

### **update**


有一处 $m$ 写成 $n$ 了，一开始以为是初始化的问题。拖了半年没改，现在修改了。

### 题意

题意就不过多说明了，总体就是可以理解为有两块屏幕，一块邮件夹的，一块邮件的，要把邮件放到对应文件夹中。

### 分析
首先我们可以发现这个邮件的屏幕头出尾进，但中间又有一些删除，所以可以用的 list（不用 queue，有删除操作）。还有屏幕上方有可能还有些未归类的邮件，越在后的越早落下，所以可以使用 stack。
### 实现
主要是要会用 list 和 stack 思想是模拟+一点点贪心。贪心体现在如果一个文件夹并没有归这类的文件了，就下移文件夹屏幕。因为文件夹一旦弹出屏幕，就回不来了。还有下移时先判断是否能归，不能归再压入 list。

   总体分三步走：
   
   1. 能归就归。
   
   2. 不能归下移。
   
   3. 移到底，栈中文件下落。
   
   
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int const N = 1e5 + 5;
stack <int> st;
list <int> lst; 
int d[N], vis[N];
int main()
{
	int t;
	cin >> t;
	while(t--){
		int m, n, k;
		cin >> m >> n >> k;
		while(!st.empty()) st.pop();
		lst.clear();
		memset(vis, 0, sizeof(vis));//多组数据要清空 
		for(int i = 1; i <= n; ++i){
			cin >> d[i];
			vis[d[i]]++;//用桶记录每个文件夹下有多少个邮件 
		} 
      for(int i = 1; i <= k; i++){
			lst.push_back(d[i]);//先将邮件屏幕铺满
		}
		int j = k + 1;//j表示没归邮件的第一个 
		for(int i = 1; i <= m - k + 1; ++i){//枚举邮件夹屏幕开头的位置（原来这里写错了） 
			list<int>::iterator it, tmp;
			for(it = lst.begin(); it != lst.end();){//能归就归，清一遍list 
				tmp = it;
				++it; //不然清掉之后会导致循环不知道在哪 
				if(*tmp >= i && *tmp <= i + k - 1){//在邮件夹范围內 
					lst.erase(tmp);
					vis[*tmp]--;//邮件个数减1 
				}
			}
			while(j <= n && vis[i]){//下移 ，假如邮件夹已经没有邮件归这个了就等下一次for循环 
				if(lst.size() == k){//满了 
					st.push(lst.front());//压入栈中 
					lst.pop_front();
				}
				if(!(d[j] >= i && d[j] <= i + k - 1)) //不能再归，压入list 
					lst.push_back(d[j]);
				else
					vis[d[j]]--;//邮件个数减1 
				j++;
			}
			if(j > n){//栈下落 
				while(lst.size() < k && st.size() > 0){//有空下落 
					if(!(st.top() >= i && st.top() <= i + k - 1))//不能再归，压入list 
						lst.push_back(st.top());
					else
						vis[st.top()]--;//邮件个数减1
					st.pop();//栈中邮件弹出 
				}
			}
		}
		if(lst.size()) cout << "NO" << endl;//还有邮件没归 
		else cout << "YES" << endl;
	}
	return 0;
} 
```

   
   

---

## 作者：内拉组里 (赞：4)

异常简单。大概只有 **普及-** 的难度。

只带了一点贪心，剩下都是大模拟。

# Thoughts：

因为数量会变的只有右侧的邮件列表，左边的文件夹列表往下翻了就不可能再翻回来了，

所以要保证整个文件夹全部塞完了再滑下去。

1. 对右侧列表维护一个双指针维护能看到的邮件，能归档就归档，直到一个也归档不了为止。
2. 然后去考虑左侧文件夹，塞完一个就往下滑，滑不动为止。

重复这两个步骤，若两者均无法执行，那么把双指针往下挪。

随后判断是否所有邮件都已归档即可。

# Details：

- 双指针应保证区间内**未被删除的**邮件有 $ k $ 条，

  注意移动双指针时跳过已被删除的邮件。

- 多测记得清空。

# Optimizations：

- 减少一些常数，每次把双指针指在未被删除的邮件上，减少无效遍历次数。

- 整体挪动双指针时，由于在双指针区间内已经不存在能够归档的邮件了，

  所以直接把新的左端点移到原来的右端点右侧即可。

# Analyses：

> 总时间复杂度 $ \Theta (NK) $，带个小常数。
>
> 总空间复杂度 $ \Theta (N + M) $。

# Code：

```cpp
#include	<iostream>
#include	<cstring>
#define		int		long long
using namespace std;
constexpr int maxn = 1e5+4;
constexpr int maxm = 1e4+4;

int f[maxn];
int buc[maxm];
int lst[maxm];
int vis[maxn];
int t, n, m, k;

signed main (void)
{
	cin >> t;
	while (t--)
	{
		memset (buc, 0, sizeof buc);
		memset (lst, 0, sizeof lst);
		memset (vis, 0, sizeof vis);
		cin >> m >> n >> k;
		for (int i = 1; i <= n; i++)
		{
			cin >> f[i];
			buc[f[i]]++;
		}
		for (int i = n; i; i--)
		{
			if (!lst[f[i]])
				lst[f[i]] = i;
		}
		int l = 1;
		int r = k;
		int now = 1;
		int cnt = 0;
		while (cnt < n)
		{
			int flag = 0;
			for (int i = l; i <= r; i++) if (!vis[i])
			{
				if (now <= f[i] && f[i] <= now + k - 1)
				{
					cnt++;
					buc[f[i]]--;
					flag = 1;
					vis[i] = 1;
					if (r < n)
						while (vis[++r]);
					else
						while (vis[--l]);
				}
			}
			while (!buc[now])
			{
				flag = 1;
				now++;
			}
			while (vis[l])
				l++;
			if (!flag)
			{
				if (r < n)
				{
					int tmp = r;
					while (l <= tmp)
					{
						while (vis[++l]);
						while (vis[++r]);
					}
				}
				else
					break;
			}
		}
		if (cnt == n)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
```

---

## 作者：滑蒻稽 (赞：2)

## Des

$M$ 个文件夹，$N$ 封邮件展示在两个窗口，每个窗口都最多展示 $K$ 个邮件或文件夹。每个邮件有一个属性 $f_i$ 表示它应该放到哪个文件夹里。已经被放好的邮件会消失，同时窗口下面（或上面）如果还有邮件，就会补上。FJ 需要把所有的邮件都放好，但他的鼠标滚轮坏了，只能往下滑。

问 FJ 是否能放好所有邮件。

$M\le 10^5, N\le 10^6$。

## Sol

主要的思路是用优先队列（小根堆）把右边窗口的邮件存起来，然后每次看所在文件夹编号最小的文件是否能放进左边最小的文件夹。如果不能放，就把右边窗口往下滑，如果能放，就模拟邮件补位的过程（从上面或从下面补）。由于文件夹被划过了就没了，所以当且仅当一个文件夹的所有邮件都被放好才能把文件夹往下滑。

标记一下右边窗口里邮件的左端点 $fl$ 和右端点 $fr$，模拟补位的过程是把 $fr$ 加一或者把 $fl$ 减一（取决于邮件窗口是否滑到底了），把邮件窗口往下滑的过程是把 $fl$ 和 $fr$ 同时加一，并把左边跳过的邮件存进一个 vector 里，等到邮件窗口滑到底后补位。你发现区间 $fl$ 位置对应的邮件可能已经被放好了，只需要给放好的邮件打好标记，然后保证 $fl$ 的位置是没有放好的邮件就行了。

## My Code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second
const int N = 1e5 + 5;
int T, m, n, k, cnt[N], a[N], vis[N];

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	for(cin >> T; T; T--) {
		cin >> m >> n >> k;
		for(int i = 1; i <= n; i++) cnt[i] = 0, vis[i] = 0;
		deque<int> l; // 存储被跳过的邮件 
		priority_queue<pii, vector<pii>, greater<pii>> q;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			if(i <= k) q.push(mp(a[i], i));
			++cnt[a[i]];
		}
		int fl = 1, fr = k, fold = 1;
		while(q.size() || l.size()) {
			while(!cnt[fold] && fold < m - k + 1) ++fold;
			if(q.size() && q.top().fi >= fold && q.top().fi <= fold + k - 1) {
				--cnt[q.top().fi];
				vis[q.top().se] = true; // 记录已经放好的邮件
				q.pop();
				if(fr < n) {
					++fr;
					q.push(mp(a[fr], fr));
				}
			} else if(fr < n) { // 邮件窗口没有滑到底时模拟补位 
				++fl, ++fr;
				q.push(mp(a[fr], fr));
				l.push_back(a[fl - 1]); // 记录跳过的邮件 
			} else if((int)q.size() < k && l.size()) { // 邮件窗口滑到底之后模拟补位 
				--fl;
				q.push(mp(l.back(), fl));
				l.pop_back();
			} else break;
			while(q.size() && q.top().se < fl) q.pop(); // 保证堆顶的邮件是没有被跳过的 
			while(vis[fl]) ++fl; // 保证 fl 位置的邮件是没有放好的 
		}
		if(q.size()) cout << "NO\n";
		else cout << "YES\n";
	}

	return 0;
}
```

---

