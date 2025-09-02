# [NordicOI 2022] 嬉皮爵士 Hipster Jazz

## 题目背景

译自 Nordic Olympiad in Informatics 2022  [Hipster Jazz](https://noi22.kattis.com/contests/noi22/problems/hipsterjazz)。如果发现 SPJ 锅了请联系搬题人 qvq。

$\texttt{1s,1G}$。


## 题目描述

爵士学校里，新班级诞生了。这个班级里有 $N$ 名学生，其中有 $M$ 对朋友关系。每个学生要选择一种主修乐器：钢琴，或者萨克斯。当然，所有的学生都希望成为有创意的爵士音乐家，所以他们想要保证，至少有一半朋友主修的乐器和自己主修的乐器不一样。

学生们发现，选择乐器是一件很困难的事情。于是他们找来了你，希望你能够为每个同学选择一个主修乐器，满足上述条件。

数据保证至少存在一种方案。

## 说明/提示

#### 数据范围

- $1\le N\le 200$；
- $0\le M\le \dfrac{N(N-1)}{2}$；
- 同一对朋友不会被列出两次；
- 至少存在一种方案。

#### 子任务

| 子任务编号 | 得分 | 限制 |
| :--: | :--: | :--: |
| $1$ | $10$ |  每对学生都是朋友 |
| $2$ | $15$ | $N\le 15$ |
| $3$ | $25$ | 存在一种方案，其中任意一对朋友主修的乐器都不同 |
| $4$ | $50$ | 无额外限制 |

## 样例 #1

### 输入

```
3 3
1 2
1 3
2 3
```

### 输出

```
PSP
```

## 样例 #2

### 输入

```
5 6
1 2
1 3
1 5
2 4
3 5
4 5
```

### 输出

```
SPPSP
```

## 样例 #3

### 输入

```
6 9
1 4
1 5
1 6
2 4
2 5
2 6
3 4
3 5
3 6
```

### 输出

```
PPPSSS
```

# 题解

## 作者：Aventurine_stone (赞：7)

## 1. 题目分析
先看数据范围，$n \le 200$。如此小的数据范围，首先考虑是否可以使用模拟退火。  
模拟退火可以跑十万次，但我们很快可以发现，此题对于一个随机的序列，我们很难找到一个参数用来判断此序列的优劣，故不能用模拟退火解题。  
既然不是模拟退火，那么此题很明显便是一道构造题。
## 2. 题目做法
我们可以将他们的朋友关系做成一张图。然后创建一个数组记录每个人使用的乐器，这里我用 $0$ 表示萨克斯，用 $1$ 表示钢琴。然后用一个数组记录每个人的朋友个数，再用一个数组记录每个人与他使用不同乐器的朋友个数。  
对于乐器记录数组，我们可以先随机生成一个序列，然后算出初始的不同乐器数组，之后我们对于一个人，如果他的拥有不同乐器的朋友数不符合题意，那么我们让他主修另外一种乐器，让他符合题意。就这样一直操作，直到得到一个符合题意的方案，然后输出。  
每次操作的时间复杂度为 $O(n)$，那么最坏情况下我们要进行多少次操作呢？  
#### 猜测：
最多进行 $m$ 次操作。
#### 证明：
初始时，对于一对朋友关系，如果他们使用的是不同的乐器，我们可以将此关系看作不同色关系，反之则为同色关系。  
可以看出，我们每进行一次操作，那么同色关系将至少减少一，最多只有 $m$ 个同色关系，故最多进行 $m$ 次操作。  
证毕。  
故时间复杂度为 $O(nm)$，可以轻松通过此题。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=210,M=40010;//记得开够空间 
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int head[N],ne[M],e[M],idx;
inline void add(int x,int y)//建边 
{
	ne[++idx]=head[x];
	head[x]=idx;
	e[idx]=y;
}
int n,m;
bool p[N];
int num[N],cnt[N];
inline void change(int x)//修改乐器 
{
	cnt[x]=num[x]-cnt[x];
	for(int i=head[x];i;i=ne[i])
	{
		int c=e[i];
		if(p[x]^p[c])
			cnt[c]++;
		else
			cnt[c]--;
	}
}
int x,y;
bool pd;
int main()
{
	n=read(),m=read();
	while(m--)
	{
		x=read(),y=read();
		add(x,y),add(y,x);
		num[x]++,num[y]++;
	}
	for(int i=1;i<=n;i++)
		p[i]=rand()&1;
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j;j=ne[j])
		{
			int c=e[j];
			if(p[i]^p[c])
				cnt[i]++;
		}
	}
	pd=1;
	for(int i=1;i<=n;i++)
	{
		if((cnt[i]<<1)<num[i])
		{
			x=i,pd=0;
			break;
		}
	}
	while(!pd)//进行操作 
	{
		p[x]=!p[x];
		change(x);
		pd=1;
		for(int i=1;i<=n;i++)
		{
			if((cnt[i]<<1)<num[i])
			{
				x=i,pd=0;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(p[i])
			printf("P");
		else
			printf("S");
	}
	return 0;
}
```

---

## 作者：Lucyna_Kushinada (赞：3)

特别神奇的题。

我们可以给每个点先随机染色，染色之后计算同色边的条数 $k$，易知 $k_{max}=m$，且我们希望 $k$ 是不断减小的。

然后进行若干轮操作，每轮检查每个点是否满足题目条件，如果不满足就把这个点反色，这样一定会让 $k$ 减小，因为这个点所连的同色边的数量大于异色边的数量，反色之后，同色边和异色边的数量也就相应地反过来了，因为 $k_{max}=m$，所以最多操作 $m$ 次使得每个点合法，最后输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,l,r) for(int i=(r);i>=(l);--i)
#define pr pair<int,int>
#define fi first
#define se second
#define pb emplace_back

#define N 214
//#define int long long

int n,m,siz[N],diff[N];
vector<int>e[N],tmp;
bitset<N>f;

mt19937 rd(114514);

inline void rand_init(){
	rep(i,1,n){
		tmp.pb(i);
	}
	shuffle(tmp.begin(),tmp.end(),rd);
	
	rep(i,1,n/2){
		f[tmp[i-1]]=1;
	}
	
//	rep(i,1,n){
//		cout<<f[i]<<" ";
//	}
	
	rep(i,1,n){
		for(int x:e[i]){
			diff[i]+=(f[i]!=f[x]);
		}
//		cout<<diff[i]<<"\n";
	}
}

inline void upd(int k){
	diff[k]=siz[k]-diff[k];
	
	for(int x:e[k]){
		if(f[k]==f[x]){
			diff[x]++;
		}
		else{
			diff[x]--;
		}
	}
	
	f[k]=!f[k];
}

signed main(){
//	freopen("jazz.in","r",stdin);
//	freopen("jazz.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin>>n>>m;
	
	int u,v;
	rep(i,1,m){
		cin>>u>>v;
		
		e[u].pb(v);
		e[v].pb(u);
		
		siz[u]++,siz[v]++;
	}
	
	rand_init();
	
	bool suc=0;
	
	while(!suc){
		suc=1;
		
		rep(i,1,n){
			if(diff[i]*2<siz[i]){
				suc=0;
				upd(i);
				break;
			}
		}
	}
	
	rep(i,1,n){
		if(f[i]){
			cout<<'P';
		}
		else{
			cout<<'S';
		}
	}
	
	return 0;
}
```

---

## 作者：Lee_OIer (赞：2)

红名后的 AC 首题，也是红名后的首篇题解，目前 AC $20$ 蓝题（我是**废物**）。

---

### 题意
给定一张 $N$ 个点 $M$ 条边的无向图，每个点可以染成黑色或白色，求一种染色方案保证每个点至少有一半相邻点的颜色与自己的颜色不同。

### 思路
普通构造题，需要我们自己思考解决方法，在此采用随机调整配合图上 dfs。

1. 链式前向星建图存双边。
2. 默认所有学生都选萨克斯（`P`），即 $val[i] = 0$。
3. 检查每个点，通过 dfs 遍历该点的所有相邻点，判断是否符合标准。
4. 若不符合标准，则 $val[i] = val[i] \oplus 1$。
5. 重复检查直至所有点均符合标准，输出。

每次修改同色边至少减少 $1$ 条，每个点最多经历 $1$ 次修改，故时间复杂度为 $O(NM)$。

补充：

- $0 \oplus 1 = 1$
- $1 \oplus 1 = 0$

### Code
```cpp
#include<iostream>
using namespace std;
const int N = 210;
const int M = 4e4 + 10;
int n, m, u, v, head[N], edgetot, val[N], cnt1, cnt2;
struct node{int to, nxt;}e[M];
void add(int u, int v) {
	e[++edgetot].to = v;
	e[edgetot].nxt = head[u];
	head[u] = edgetot;
}
bool dfs(int num) {
	cnt1 = cnt2 = 0;
	for (int i = head[num]; i; i = e[i].nxt) {
		if (val[e[i].to]) cnt1++;
		else cnt2++;
	}
	if (val[num]) {
		if (cnt1 <= cnt2) return 1;
		else return 0;
	} else {
		if (cnt1 >= cnt2) return 1;
		else return 0;
	}
}
bool check() {
	for (int i = 1; i <= n; ++i) if (! dfs(i)) {
		val[i] ^= 1;
		return 0;
	}
	return 1;
}
signed main(void) {
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	while (1) if (check()) break;
	for (int i = 1; i <= n; ++i) {
		if (val[i]) cout << "P";
		else cout << "S";
	}
}
```

---

## 作者：_Mount_ (赞：2)

这只蒟蒻来交理解了。  
### 1.思路
明显构造题，思路也很清晰。
1. 首先根据朋友关系用链式前向星建图。
2. 构造每一种情况，每次构造好后遍历一遍图，判断是否满足条件。
3. 输出符合条件的情况。

时间复杂度是多少呢？我们来浅算一下。每次修改都会使朋友间相同选择的关系至少减少一个，最多有 $m$ 个相同选择的关系，又因为总共有 $n$ 个点，每个点最多经历 $1$ 次修改（初始情况不算），所以总体时间复杂度最高为 $O(nm)$。
### 2.实现
#### 1.C++
[这是通过记录。](https://www.luogu.com.cn/record/175551851)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 210,M = 200*N;
int n,m;
int head[N],nxt[M],adj[M],ind;
bool choose[N];

void addedge(int from,int to){
	adj[ind] = to;
	nxt[ind] = head[from];
	head[from] = ind++;
	return;
}	

bool make(int from){
	int sum0 = 0,sum1 = 0;
	for(int i = head[from];i >= 0;i = nxt[i]){
		if(choose[adj[i]]){
			sum1 ++;	
		}else{
			sum0 ++;
		}
	}
	if(choose[from]){
		if(sum0 >= sum1){
			return 1;
		}else{
			return 0;
		}
	}else{
		if(sum1 >= sum0){
			return 1;
		}else{
			return 0;
		}
	}
}

bool check(){
	bool flag = 0;
	for(int i = 1;i <= n;i ++){
		if(!make(i)){
			choose[i] = !choose[i];
			flag = true;
		}
	}
	if(flag) return 0;
	else return 1;
}


int main(){
	ios::sync_with_stdio(NULL),cin.tie(NULL),cout.tie(NULL);
	memset(head,-1,sizeof(head));
	cin >> n >> m;
	for(int i = 1;i <= m;i ++){
		int a,b;
		cin >> a >> b;
		addedge(a,b),addedge(b,a);
	}
	while(true){
		if(check()){
			break;
		}
	}
	for(int i = 1;i <= n;i ++){
		if(choose[i]) putchar('P');
		else putchar('S');
	}
	return 0;
}
```
#### 2.GO
[这是通过记录。](https://www.luogu.com.cn/record/175551812)

```
package main;

import (
	"fmt"
)

var n,m int;
var adj[40010] int;
var nxt[40010] int;
var head[210] int;
var ind int;
var choose[210] bool;

func addedge(to,from int) {
	adj[ind] = to;
	nxt[ind] = head[from];
	head[from] = ind;
	ind ++;
	return;
}

func make(from int) bool { 
	var sum0,sum1 int;
	for i := head[from];i != -1;i = nxt[i] {
		if(choose[adj[i]]){
			sum1 ++;
		}else{
			sum0 ++;
		}
	}
	if(choose[from]){
		if(sum0 >= sum1){
			return true;
		}else{
			return false;
		}
	}else{
		if(sum1 >= sum0){
			return true;
		}else{
			return false;
		}
	}
}

func check() bool {
	var flag bool;
	for i := 1;i <= n;i ++{
		if(!make(i)){
			choose[i] = !choose[i];
			flag = true;
		}
	}
	if(flag){
		return false;
	}
	return true;
}

func main() {
	fmt.Scanf("%d %d",&n,&m);
	for i:=1;i <= n;i ++{
		head[i] = -1;
	}
	for i:=1;i <= m;i ++{
		var a,b int;
		fmt.Scanf("%d %d",&a,&b);
		addedge(a,b);
		addedge(b,a);
	}
	for true{
		if(check()){
			break;
		}
	}
	for i:=1;i <= n;i ++{
		if(choose[i]){
			fmt.Printf("P");
		}else{
			fmt.Printf("S");
		}
	}
	return;
}
```

---

## 作者：zzx0102 (赞：2)

非常玄学的题。

我们只分析一个点，如果 $i$ 周围的点颜色已经确定，那么点 $i$ 的颜色就可以确定。

我们可以先随机搞个方案，然后给不符合条件的点改个颜色，这样至少这个点就对了。

改完不对就继续改，直到改对为止。

我们定义方案的权值为两端点颜色相同的边数，每换掉一个点权值必然减小。

调整一个点后权值必然减小，权值最大为 $m$，所以最多改 $m$ 次，复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 210;
vector<int> e[N];
int n, m, ans[N], in[N];
int main() {
	ios::sync_with_stdio(0);
	srand(time(0));
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		in[a]++, in[b]++;
		e[a].push_back(b); e[b].push_back(a);
	}
	for(int i = 1; i <= n; i++) ans[i] = rand() % 2;
	bool flag = 0;
	while(!flag) {
		flag = 1;
		for(int i = 1; i <= n; i++) {
			int cnt = 0;
			for(int j: e[i]) if(ans[j] != ans[i]) cnt++;
			if(cnt * 2 < in[i]) ans[i] ^= 1, flag = 0;
		}
	}
	for(int i = 1; i <= n; i++) cout << (ans[i] ? "P" : "S");
	return 0;
}
```

---

## 作者：D2T1 (赞：0)

## P10643

考虑调整：先随机一个染色方案，然后遍历整张图，发现一个点不满足条件（同色邻居数量多于异色邻居）则更换它的颜色，重复若干次直到所有点都满足条件。

证明：定义一种染色方案的权值为两端同色边数。可以发现在上述调整过程中每次调整权值一定减小，故调整一定会终止；调整终止时若方案不合法，则任选一不合法点更换颜色权值一定更小，调整未终止，矛盾，故调整终止时方案一定合法。染色方案权值最大为 $m$，故时间复杂度为 $O(nm)$。

---

## 作者：wyc0607 (赞：0)

### 思路：随机调整

适合随机调整的初学者，思路简单易懂。

### 具体步骤：
1. 读入，对于每对朋友 $a,b$，使用 vector 存他们两个连的一条边，再给各自的入度分别加一。
2. 接下来，给每个人随机附一个乐器。
3. 循环直到满足题意，在循环中做 Step 4，Step 5。
4. 循环每个点 $a$，定义一个计数器 $count$，初值为 $0$，循环这个点连接的所有点（这个人的所有朋友）。如果连接的点选择的乐器与本人选择的不同，$count$ 增加一。
  
   如果 $2 \times count < rd[a]$，不满足题意，更换这个人的乐器。

5. 如果每个点都有 $2 \times count \ge rd[a]$，满足题意，退出循环，输出。

### 代码：

[AC记录](https://www.luogu.com.cn/record/198873399)

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> to[205];
int ans[205];
int n,m;
int rd[205];
main() {
	srand(rand());
	cin>>n>>m;
	for(int i=1; i<=n; i++) ans[i]=rand()%2;//ans[i]=0 : 学生 i 选择萨克斯; ans[i]=1 : 学生 i 选择钢琴。 
	for(int i=1; i<=m; i++) {
		int a,b;
		cin>>a>>b;
		to[a].push_back(b);//存边。 
		to[b].push_back(a);//存边。 
		rd[a]++;//入度 ++。 
		rd[b]++;//入度 ++。 
	}
	while(1) {
		bool fl=1;
		for(int i=1; i<=n; i++) {
			int count=0;
			for(int j=0; j<to[i].size(); j++) if(ans[to[i][j]]!=ans[i]) count++;
			if(count*2<rd[i]) ans[i]=(ans[i]==1?0:1),fl=0;//不满足题意，更换乐器。 
		}
		if(fl==1) {
			for(int i=1; i<=n; i++) cout<<(ans[i]==0?"S":"P");
			break;
		}
	}
}
```

---

## 作者：Xuejiama1227 (赞：0)

逆天构造题。

考虑一种暴力的做法。

我们可以先给每个点随机染色，然后只要有点不满足要求就让那个点改变颜色（称为一次操作），直到所有点都满足要求为止。

事实上，上述方法可以在最多 $M$ 次操作内完成。证明如下：

考虑势能分析。设图中同色边条数为 $k$。

每一次操作，都会让一个点的连边中同色边条数由超过半数变成不超过半数（不然就不用操作了），因此 $k$ 会在每次操作后减小。

所有操作开始前 $k$ 最大为总边数 $M$，所有操作结束后 $k=0$，且 $k$ 在每次操作中减小 $1$ 及以上，所以操作数最大为 $M$。

实现方面，因为每一次操作后只可能会让与操作的点有连边的点是否满足要求的状态发生变化，所以可以通过只枚举这些点来优化时间。

可以建立一个操作队列，初始时将不符合要求的点入队，每次操作后将不再符合要求的点入队。每次操作选择队列头的点，并使其出队。队列空时所有操作完成。

为了避免一个点入队多次，用一个 $vis$ 数组来记录一个点是否在队列里。点将要入队时，若该点已在队列里，就不入队。

平均时间复杂度 $O(\frac{M^2}{N})$。

代码如下：

```cpp
int n,m,d[N],s[N],q[N*N],hd,tl;
vector<int>e[N];
int c[N],vs[N];
signed main(){
	int i,x,y;
	read(n,m);
	for(i=1;i<=m;i++){
		read(x,y);
		e[x].push_back(y);
		e[y].push_back(x);
		d[x]++;d[y]++;
	}
	for(i=1;i<=n;i++)c[i]=i&1;
	for(i=1;i<=n;i++)for(int j:e[i])s[i]+=(c[j]==c[i]);
	for(i=1;i<=n;i++)if((s[i]<<1)>d[i])q[tl++]=i,vs[i]=1;
	while(hd<tl){
		x=q[hd++];vs[x]=0;
		if((s[x]<<1)<=d[x])continue;
		c[x]^=1;s[x]=d[x]-s[x];
		for(int y:e[x]){
			s[y]+=(c[y]==c[x])?1:-1;
			if((s[y]<<1)>d[y]&&!vs[y])q[tl++]=y,vs[y]=1;
		}
	}
	for(i=1;i<=n;i++)write(c[i]?'S':'P');
	return 0;
}
```

---

## 作者：junee (赞：0)

# P10643 题解

## 前置知识

构造。

## 题目分析

对于每一个人开始任意设置一种，然后检查每一个点是否满足，如果不满足，则将该点换成相反的。

对于某个不符合的点，每次操作后都会使之前同色的边变少，同色边最多有 $m$ 条。故时间复杂度为 $O(nm)$。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=210,M=4e4+10;
int h[N],e[M],ne[M],idx,w[N];
int n,m;
void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
bool dfs(int u){
	int cnt0=0,cnt1=0;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(w[j])cnt1++;
		else cnt0++;
	}
	if(w[u]){
		if(cnt0>=cnt1)return 1;
		else return 0;
	}
	else{
		if(cnt1>=cnt0)return 1;
		else return 0;
	}
}
bool check(){
	int f=0;
	for(int i=1;i<=n;i++){
		if(!dfs(i)){
			w[i]^=1;f=1;
		}
	}
	if(f)return 0;
	return 1;
}
int main(){
	memset(h,-1,sizeof h);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1,a,b;i<=m;i++){
		cin>>a>>b;
		add(a,b),add(b,a);	
	}
	while(1){
		if(check())break;
	}
	for(int i=1;i<=n;i++){
		if(w[i])cout<<"P";
		else cout<<"S";
	}
	return 0;
}
```

---

