# [ABC216D] Pair of Balls

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc216/tasks/abc216_d

$ 2N $ 個のボールがあります。各ボールには $ 1 $ 以上 $ N $ 以下の整数によって表される色が塗られており、各色で塗られたボールはちょうど $ 2 $ 個ずつ存在します。

これらのボールが、底が地面と平行になるように置かれた $ M $ 本の筒に入れられています。はじめ、$ i\ (1\ \leq\ i\ \leq\ M) $ 本目の筒には $ k_i $ 個のボールが入っており、上から $ j\ (1\ \leq\ j\ \leq\ k_i) $ 番目のボールの色は $ a_{i,\ j} $ です。

あなたの目標は、以下の操作を繰り返すことで $ M $ 本の筒全てを空にすることです。

- 異なる $ 2 $ 本の空でない筒を選び、それぞれの筒の一番上にあるボールを取り出して捨てる。ここで、取り出して捨てた $ 2 $ つのボールは同じ色で塗られている必要がある。

目標が達成可能かを判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ k_i\ (1\ \leq\ i\ \leq\ M) $
- $ 1\ \leq\ a_{i,j}\ \leq\ N\ (1\ \leq\ i\ \leq\ M,1\ \leq\ j\ \leq\ k_i) $
- $ \sum_{i=1}^{M}\ k_i\ =\ 2N $
- 全ての $ x\ (1\ \leq\ x\ \leq\ N) $ について、$ 1\ \leq\ i\ \leq\ M $ かつ $ 1\ \leq\ j\ \leq\ k_i $ かつ $ a_{i,j}=x $ なる整数の組 $ (i,j) $ はちょうど $ 2 $ つ存在する
- 入力は全て整数

### Sample Explanation 1

以下のように操作を行えばよいです。 1. $ 1 $ つ目の筒と $ 2 $ つ目の筒を選び、それぞれの筒の一番上にあるボールを取り出して捨てる。捨てられるボールの色は共に $ 1 $ であり等しいので、この操作は有効である。 2. $ 1 $ つ目の筒と $ 2 $ つ目の筒を選び、それぞれの筒の一番上にあるボールを取り出して捨てる。捨てられるボールの色は共に $ 2 $ であり等しいので、この操作は有効である。

### Sample Explanation 2

そもそも一度も操作を行うことができないため、目標を達成する、すなわち $ M $ 本の筒全てを空にすることは不可能です。

## 样例 #1

### 输入

```
2 2
2
1 2
2
1 2```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2 2
2
1 2
2
2 1```

### 输出

```
No```

# 题解

## 作者：_zzzzzzy_ (赞：2)

## 思路
我们可以先分析一下怎么把问题转化成图论问题，如果我们要选一个数，那么我们就要先把他上面的那一个拿走，那我们再看一下怎么构造一个错误的解，比如要拿出的数字是 $2$，他上面有一个 $1$，就是说要先拿走 $1$，才能拿走 $2$，你又发现另外一个桶，要先拿走 $2$，才能拿 $1$，看到这里的同学可能已经有思路了，很像一个拓扑排序，既然已经选好了算法就来建一下图，根据上面的分析，我们把桶上面的数连向下面的数，表示要先选了上面的数才能选下面的，最后跑一边拓扑排序，如果有环，那就输出 `No`，否则就输出 `Yes`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000000;
vector<int>e[maxn];
int d[maxn];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int k,l;
		cin>>k>>l;
		for(int j=1;j<k;j++){
			int x;
			cin>>x;
			e[l].push_back(x);
			d[x]++;
			l=x;
		}
	}
	queue<int>Q;
	for(int i=1;i<=n;i++){
		if(d[i]==0)Q.push(i);
	}
	int cnt=0;
	while(Q.size()){
		int u=Q.front();Q.pop();
		cnt++;
		for(int v:e[u]){
			d[v]--;
			if(d[v]==0){
				Q.push(v);
			}
		}
	}
	if(cnt!=n)cout<<"No\n";
	else cout<<"Yes\n";
	return 0;
}
```

---

## 作者：lfxxx (赞：2)

考虑一个简单的模拟做法。

每次记录栈顶有哪些相同的元素，消除后在接着判断新栈顶是否可消，可以递归实现全过程，由于每递归三次一定会消除一个元素，因此总的递归次数是 $O(n)$ 的，自然时间复杂度也是 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5+114;
int n,m;
stack<int> st[maxn];
int col[maxn];//颜色为 i 的球位于哪个栈顶
void del(int pos){
	if(st[pos].size()==0) return ;
	if(col[st[pos].top()]==0){
		col[st[pos].top()]=pos;
		return ;
	}
	else{
		int next=col[st[pos].top()];
		col[st[pos].top()]=0;
		st[pos].pop();
		st[next].pop();
		del(next);
		del(pos);
		return ;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int k;
		cin>>k;
		vector<int> vec;
		for(int j=1;j<=k;j++){
			int cl;
			cin>>cl;
			vec.push_back(cl);
		}
		for(int j=vec.size()-1;j>=0;j--) st[i].push(vec[j]);
		del(i);
	}
	for(int i=1;i<=m;i++){
		if(st[i].size()!=0){
			cout<<"No\n";
			return 0;
		}
	}
	cout<<"Yes\n";
	return 0;
} 
```


---

## 作者：xiezheyuan (赞：1)

## 简要题意

有 $m$ 个栈，栈里面的小球有 $n$ 种颜色，每种颜色各有 $2$ 个，共 $2n$ 个小球。

每次可以取出栈顶 $2$ 个颜色相同的小球，问能不能把小球取完。

能取完输出 `Yes`，否则输出 `No`。

$1 \leq n \leq 2 \times 10^5$，$2 \leq m \leq 2 \times 10^5$。

## 思路

考试考的题目。

首先同一个颜色的球只有两个，所以我们显然能消一定可以消。

我们考虑动态维护每一个栈的栈顶信息，这个可以做到线性。

但是做到线性比较麻烦，这里我们可以使用一个 `set`。

每次取出出现次数最多的颜色，然后考虑将这两个元素删掉，如果可以入 `set` 重新入 `set`。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5+5;
int n,m,all;
vector<int> a[N];
vector<int> c[N];
set<pair<size_t,int> > pool;

signed main(){
//	freopen("Abig.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int k;cin>>k;all += k;
		for(int j=1;j<=k;j++){
			int v;cin>>v;
			a[i].push_back(v);	
		}
		reverse(a[i].begin(), a[i].end());
		c[a[i].back()].push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(c[i].size() > 0) pool.insert(make_pair(c[i].size(), i));
	}
//	cout<<all<<'\n';
	if(all & 1){
		cout<<"No";
		return 0;
	}
	for(int i=1;i<=(all>>1);i++){
		pair<int,int> tp = *pool.rbegin();
		if(tp.first < 2){
			cout<<"No";
			return 0;
		}
		int l1 = c[tp.second][c[tp.second].size() - 1];
		c[tp.second].pop_back();
		int l2 = c[tp.second][c[tp.second].size() - 1];
		c[tp.second].pop_back();
		a[l1].pop_back();
		a[l2].pop_back();
		pool.erase(tp);
		set<pair<size_t,int> >::iterator ite;
		if(!a[l1].empty()){
			c[a[l1].back()].push_back(l1);
			ite = pool.find(make_pair(c[a[l1].back()].size() - 1, a[l1].back()));
			if(ite != pool.end()) pool.erase(ite);
			pool.insert(make_pair(c[a[l1].back()].size(), a[l1].back()));
		}
		if(!a[l2].empty()){
			c[a[l2].back()].push_back(l2);
			ite = pool.find(make_pair(c[a[l2].back()].size() - 1, a[l2].back()));
			if(ite != pool.end()) pool.erase(ite);
			pool.insert(make_pair(c[a[l2].back()].size(), a[l2].back()));
		}
		if(tp.first - 2 > 0) pool.insert(make_pair(tp.first - 2, tp.second));
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：highkj (赞：1)

# 思路
我们对于每一个桶中的数，必须要将 $a_{i,j}$ 出桶后才能动 $a_{i,j+1}$ 那么我们很明显就能想到拓扑序了，然后我们就直接将相邻的两个数连边然后再直接跑拓扑，因为我们的每一个点的入度为 $2$ 若入度归零了就说明两个 $i$ 都在某两行的顶部，所以如果它的入度为 $0$ 了，那么我们就可以将这一行的下一个数给它的入度减一并且判断它是否也可以被抵消掉，最后看遍历到的点的个数是否等于 $n$ 即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void read(int &x) {
	x=false;
	ri f=1;
	char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c-'0'<=9&&c>='0') {
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n,m;
int k[200100];
int lst,a;
vector<int>v[200100];
int in[200100];
fire main() {
	cin>>n>>m;
	rep(i,1,m) {
		cin>>k[i]>>lst;
		rep(j,2,k[i]) {
			cin>>a;
			v[lst].push_back(a); //连边
			lst=a;
			in[a]++;
		}
	}
	queue<int>q;
	rep(i,1,n) {
		if(!in[i]) {
			q.push(i);
		}
	}
	int cnt=0;
	while(q.size()) {//拓扑
		int x=q.front();
		q.pop();
		for(auto y:v[x]) {
			if(--in[y]==0) {
				q.push(y);
			}
		}
		cnt++;
	}
	if(cnt==n) cout<<"Yes";
	else cout<<"No";
	return false;
}

```

---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc216_d)        
拓补排序好题。      
不难发现，对于 $a_{i,j}$，都需要先取 $a_{i,j-1}$。        
所以我们可以将其转化为拓补排序模型。      
我们建好边之后直接套拓补排序就可以了。       
在拓补排序的过程中，每访问一次新点，就统计一次，最后如果每一个点都被统计了，就是可以都取走，否则反之。       
[CODE](https://www.luogu.com.cn/paste/t851xmvf)

---

## 作者：Jerrlee✅ (赞：1)

## 题意
有 $m$ 个栈，栈里面的小球有 $n$ 种颜色，每种颜色各有 $2$ 个，共 $2n$ 个小球。

每次可以取出栈顶 $2$ 个颜色相同的小球，问能不能把小球取完。

能取完输出 `Yes`，否则输出 `No`。

$n,m \leq 2 \times 10^5$。

## 思路

因为栈顶两个小球颜色相同才能取，所以我们关注的是栈顶小球的颜色。

所以只需要维护当前栈顶的颜色的集合，每次删去一对，如果互不相同就是无解。

当然这题建图判其是否有环也是可以的。

## 代码
我代码的思路就是用队列（`queue`）维护上文所说集合，栈顶两个小球颜色相同就推入队列中，后面模拟跑这个队列，每次取出上面的小球，然后更改栈顶小球颜色情况，如果栈顶两个小球颜色依然相同继续推入队列中，如此反复，最后如果能取出 $2n$ 个小球则说明取完。

如果具体代码实现不清楚的，可以看看如下我写的代码。

```cpp
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int N,M;
queue<int>P[2<<17];
vector<int>ids[2<<17];
main()
{
	cin>>N>>M;
	queue<int>Q;
	for(int i=0;i<M;i++)
	{
		int k;cin>>k;
		for(int j=0;j<k;j++)
		{
			int a;cin>>a;
			P[i].push(a);
		}
		int f=P[i].front();
		ids[f].push_back(i);
		if(ids[f].size()==2)Q.push(f);//栈顶两小球颜色相同则推入队列中
	}
	int cnt=0;
	while(!Q.empty())
	{
		int u=Q.front();Q.pop();
		cnt++;
		for(int i:ids[u])
		{
			P[i].pop();
			if(!P[i].empty())
			{
				int f=P[i].front();
				ids[f].push_back(i);
				if(ids[f].size()==2)Q.push(f);//栈顶两小球颜色相同则推入队列中
			}
		}
	}
	cout<<(cnt<N?"No":"Yes");//如果能取出 2n 个小球则说明取完
}
```
[AC 记录](https://www.luogu.com.cn/record/91185358)

---

## 作者：OtterZ (赞：0)

# 【题意】
+ 有 $n$ 种颜色的球，每种颜色的球有两个，放在 $m$ 个桶里。
+ 每次可以取两个同色且都在桶的顶部的球。
+ 问是否可以取完所有的球。
+ $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
+ $ 2\ \leq\ M\ \leq\ 2\ \times\ 10^5 $

# 【题目分析】

## 1.基础思想  

对于每个桶，如果颜色为 $i$ 的球在颜色为 $j$ 的球的上方，则我们会需要先取颜色为 $i$ 的两个球，再取颜色为 $j$ 的两个球。注意，因为如果要先取第$i$种颜色的两个球,再取第 $j$ 种颜色的两个球，随后取第 $k$ 种颜色的两个球,自然可以推出要先取第 $i$ 种颜色的两个球,再取第 $k$ 种颜色的两个球。

## 2.转化为图论思想

设置 $N$ 个点，对应 $N$ 种颜色，若我们要先取第 $i$ 种颜色的两个球，再取第 $j$ 种颜色的两个球，那么我们需要从 $i$ 号点向 $j$ 号点连边。我们要求的是这张图是否存在拓扑序。

建图时遍历 $M$ 个桶，由上文可知，我们只需由 $a_{i,j}$ 向 $a_{i,j+1}$ 连一条边。对应的代码中建了一个零号节点，是为了方便找初始时入度为 $0$ 的点（可以不加）。

## 3.算法

求拓扑序，最佳的方法就是拓扑排序。  

在图上跑一遍拓扑排序，然后遍历每个点，若有点的入读仍然不为 $0$，则说明没有所求的拓扑序，否则就有。

# 【复杂度】

遍历$M$个桶时，因为共有 $2\ \times\ N$ 球，所以对应 $O(N)$ 的复杂度。  

拓扑排序的复杂度 $O(|V| + |E|)$，其中，用以上的方法，$|V|=N,|E| \leq 2\ \times\ N$，故为 $O(N)$ 的复杂度。

最后得出答案，也是 $O(N)$ 的复杂度。

因为 $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $，所以不会超时。

# 【代码】

```cpp
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=2e5+5;
vector<int>e[MAXN];
int n,dist,in[MAXN],vsj,ans=0,m,u;
int main(){
	scanf("%d%d",&n,&m);
	 //初始化
	e[0].clear();
	for(int i=1;i<=n;i++){
		in[i]=1;
		e[i].clear();
		e[0].push_back(i);
	}
	//建图
	for(int i=1;i<=m;i++){
		scanf("%d",&u);
        scanf("%d",&dist);
        for(int i=2;i<=u;i++){
            scanf("%d",&vsj);
            e[dist].push_back(vsj);
            in[vsj]++;
            dist=vsj;
        }
	}
	//拓扑排序
	queue<int>q;
	q.push(0);
	while(!q.empty()){
		int d=q.front();
		q.pop();
		for(int i=0;i<e[d].size();i++){
			in[e[d][i]]--;
			if(in[e[d][i]]==0)q.push(e[d][i]);
		}
	}
	//答案
	for(int i=1;i<=n;i++){
		if(in[i]!=0){
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	return 0;
}
```
# 【更新情况】
+ 11/9 初稿；
+ 11/10 修改排版并改变内容分段。

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$

显然只能模拟，进一步分析，我们发现现在如果有一组可以删的数，那么无论在之后的何时将他们取出，都会导致一样的结果，因为它们在此时一定处在顶部。其次，每次可能出现新的可取出的组都只会是在取出另一组之后，所以每次只用维护新出现的两个值。那么我们就可以使用队列将可以解决的组存入，每次将队首取出，判断会不会出现新的组数，若有继续加入队列，没有则用数组标记，代表这种数字已经在某个桶顶部，下次再出现这个数时就可以直接加入队列了。如果中途队列空了，说明推不走了直接输出 `No`。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
const int N=1e6+10;
using namespace std;
int n,m,k[N],vis[N],len[N];
vector<int> v[N];
queue<pii> q;
signed main()
{
	cin>>n>>m;
	rep1(i,1,m)
	{
		cin>>k[i];
		rep1(j,1,k[i])
		{
			int x;
			cin>>x;
			v[i].push_back(x);//二维vector存储每个桶里的元素
		}
	}
	rep1(i,1,m)
	{
		if(vis[v[i][0]]!=0) q.push(make_pair(vis[v[i][0]],i));
		else vis[v[i][0]]=i;
	}
	int s=n;
	while(n)
	{
		if(q.empty())//推不走了
		{
			puts("No");
			return 0;
		}
		pii t=q.front();
		q.pop();
		--n;//个数-1
		++len[t.x];//下个元素
		++len[t.y];//下个元素
		if(len[t.x]<k[t.x])//边界
		{
			int w=v[t.x][len[t.x]];//当前值
			if(vis[w]!=0) q.push(make_pair(t.x,vis[w]));//加入队列
			else vis[w]=t.x;//标记
		}
		if(len[t.y]<k[t.y])//边界
		{
			int w=v[t.y][len[t.y]];//当前值
			if(vis[w]!=0) q.push(make_pair(t.y,vis[w]));//加入队列
			else vis[w]=t.y;//标记
		}
	}
	puts("Yes");
	return 0;
}
```

---

