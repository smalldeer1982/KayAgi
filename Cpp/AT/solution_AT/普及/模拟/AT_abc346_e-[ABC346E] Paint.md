# [ABC346E] Paint

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc346/tasks/abc346_e

$ H $ 行 $ W $ 列のグリッドがあり、はじめすべてのマスは色 $ 0 $ で塗られています。

これから $ i\ =\ 1,\ 2,\ \ldots,\ M $ の順で以下の操作を行います。

- $ T_i\ =\ 1 $ のとき、$ A_i $ **行目**のマスをすべて色 $ X_i $ に塗り替える
- $ T_i\ =\ 2 $ のとき、$ A_i $ **列目**のマスをすべて色 $ X_i $ に塗り替える

すべての操作を終えたとき、最終的に色 $ i $ で塗られたマスが存在するような各色 $ i $ についてその色で塗られたマスの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,\ W,\ M\ \leq\ 2\ \times\ 10^5 $
- $ T_i\ \in\ \lbrace\ 1,\ 2\ \rbrace $
- $ T_i\ =\ 1 $ なる $ i $ に対して $ 1\ \leq\ A_i\ \leq\ H $
- $ T_i\ =\ 2 $ なる $ i $ に対して $ 1\ \leq\ A_i\ \leq\ W $
- $ 0\ \leq\ X_i\ \leq\ 2\ \times\ 10^5 $
- 入力される値はすべて整数

### Sample Explanation 1

操作によってグリッドの各マスの色は以下のように変化します。 ``` 0000 0000 0000 0000 0000 0000 → 5555 → 5550 → 5550 → 5550 0000 0000 0000 3333 2222 ``` 最終的に色 $ 0 $ で塗られたマスは $ 5 $ つ、色 $ 2 $ で塗られたマスは $ 4 $ つ、色 $ 5 $ で塗られたマスは $ 3 $ つです。

## 样例 #1

### 输入

```
3 4 4
1 2 5
2 4 0
1 3 3
1 3 2```

### 输出

```
3
0 5
2 4
5 3```

## 样例 #2

### 输入

```
1 1 5
1 1 1
1 1 10
2 1 100
1 1 1000
2 1 10000```

### 输出

```
1
10000 1```

## 样例 #3

### 输入

```
5 5 10
1 1 1
1 2 2
1 3 3
1 4 4
1 5 5
2 1 6
2 2 7
2 3 8
2 4 9
2 5 10```

### 输出

```
5
6 5
7 5
8 5
9 5
10 5```

# 题解

## 作者：2huk (赞：15)

> 有一个 $H \times W$ 的网格，最开始每个格子的颜色都是 $0$。
>
> 按顺序执行 $N$ 个操作，每个操作形如 $(T_i, A_i, X_i)$：
> 
> - 若 $T_i = 1$，将第 $A_i$ 行全部涂成 $X_i$ 颜色。
> - 若 $T_i = 2$，将第 $A_i$ 列全部涂成 $X_i$ 颜色。
> 
> 求最后每种颜色的出现次数。
>
> $1 \le H, W, M, X_i \le 2 \times 10^5$。

首先观察到，如果对某一行/列进行了多次染色，那么只有最后一次染色是有效的，所以我们只保留最后一次染色。如果这一行/列自始至终没有没染过色，相当于最开始为它全染成 $0$。

这样，我们就相当于对于每一行和每一列都进行了**恰好**一次染色操作。那么做法是将所有操作倒序处理。

假如在「在第 $1$ 列染颜色 $2$」之后，总共出现过 $k$ 次染整行的操作，那么最终第 $1$ 列上颜色 $2$ 会有 $n - k$ 个。行列翻转过来同理。

所以我们在倒序处理操作的过程中，记录已经操作过多少次行/列，并分解计算即可。

```cpp
int n, m, k;
int nn, mm;
int res[N];

struct Node {
	int op, a, x;
}a[N];

void solve() {
	fin >> n >> m >> k;
	for (int i = 1; i <= k; ++ i ) {
		fin >> a[i].op >> a[i].a >> a[i].x;
	}
	
	map<pair<int, int>, bool> mp;
	auto work = [&](int op, int a, int x) {
		pair<int, int> t = {op, a};
		if (mp.count(t)) {
			return;
		}
		mp[t] = true;
		
		if (op == 1) {
			res[x] += m - nn;
			++ mm;
		}
		else {
			res[x] += n - mm;
			++ nn;
		}
	};
	
	for (int i = k; i; -- i ) work(a[i].op, a[i].a, a[i].x);
	for (int i = 1; i <= n; ++ i ) work(1, i, 0);
	
	vector<pair<int, int> > ans;
	for (int i = 0; i <= 200000; ++ i )
		if (res[i]) ans.push_back({i, res[i]});
	fout << ans.size() << '\n';
	for (auto t : ans) {
		fout << t.first << ' ' << t.second << '\n';
	}
}
```

---

## 作者：XP3301_Pipi (赞：11)

# ABC346E E - Paint

一道很不错的思维题。

不难看出，在同一列（或行）的操作，只有最后一次操作可能对最后结果有影响。

所以，我们可以倒序处理所有操作：  
- 当前操作的行和列已经被后面的操作覆盖，则跳过；
- 维护两个变量 $c$ 与 $l$，分别表示行操作还能覆盖多少列，列操作还能覆盖多少行；
- 对于行操作，如果没有被跳过，则占用一行，在此之前的列操作将不能覆盖这一行，将变量 $c$ 减一；
- 对于列操作，也会占用一列，与行操作同理，将变量 $l$ 减一。

具体实现请看代码：
```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define int long long
using namespace std;
const int N=2e5+15;
const long long INF=0x3f3f3f3f3f3f3f3fll;

inline void FileIO() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}

template<typename Type>
inline void read(Type& res) {
	Type x=0,f=1;
	char c=' ';
	while(!isdigit(c)) {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	res=x*f;
}

int n,m,k,c,l;
ll cnt[N];
map<pii,bool> vis;

struct Op{
	int type,x,w;
}a[N];

signed main() {
//	不开longlong见祖宗！
//	检查数组大小！
//	禁止在int乘int时不开longlong！
//	STL数据类型拷贝赋值时间复杂度是 O(N)！
	read(n),read(m),read(k);
	for(int i=1;i<=k;i++){
		read(a[i].type);
		read(a[i].x);
		read(a[i].w);
	}
	l=m,c=n;
	for(int i=k;i;i--){
		if(vis[make_pair(a[i].type,a[i].x)]) continue;
		vis[make_pair(a[i].type,a[i].x)]=1;
		if(a[i].type==1){
			cnt[a[i].w]+=l;
			c=max(c-1,0ll);
		}
		else{
			cnt[a[i].w]+=c;
			l=max(l-1,0ll);
		}
	}
	int num=0;
	ll cnt0=n*m;
	for(int i=1;i<=2e5;i++) if(cnt[i]) num++,cnt0-=cnt[i];
	printf("%lld\n",num+((cnt0>0ll)?1:0));
	for(int i=0;i<=2e5;i++){
		if(i==0&&cnt0>0) printf("0 %lld\n",cnt0);
		else if(cnt[i]){
			printf("%lld %lld\n",i,cnt[i]);
		}
	}
	return 0;
}





```

---

## 作者：Mortidesperatslav (赞：7)

P9117 加强版。

我们每次维护每一行每一列的涂色，记录这一行或这一列是第几个被涂色的。

我们排个序，优先处理后面的涂色。

对于每个涂色：

1. 若这一行（列）在之后又被涂了，那么这一次涂色作废。

2. 否则若这是一行涂色，维护之后涂了多少不同的列；若这是一列涂色，维护之后涂了多少不同的行。

我们逆序处理就很好维护了。

另外，如果你 WA $12$ 个测试点，请注意 $n^2 = 4 \times 10^{10}$，要开 `long long`。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
    int c, id, h; 
}a[200005], b[200005];
int n, m, q, cnt;
int buk[200005], vis[200005][2];
queue<int> qq, q2;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++){//先涂成 0
    	a[i].c = 0;
    	a[i].id = i;
    	a[i].h = i;
	}
	q += n;
    for (int i = n + 1; i <= q; i++){
    	int u, v, w;//题目中给的涂色操作
    	cin >> u >> v >> w;
    	if (u == 1){
    		a[v].c = w;
    		a[v].id = i;
    		a[v].h = v;
		}else{
			b[v].c = w;
			b[v].id = i;
			b[v].h = v;
		}
	}
	sort(a + 1, a + n + 1, [](node o, node t){return o.id > t.id;});
	sort(b + 1, b + m + 1, [](node o, node t){return o.id > t.id;});
	int tpa = 1, tpb = 1, ma = 0, mb = 0;
	while (a[tpa].id || b[tpb].id){
	//维护更后的操作
		if (a[tpa].id > b[tpb].id){
			if (!vis[a[tpa].h][0])
				buk[a[tpa].c] += m - ma;
			vis[a[tpa].h][0] = 1;
			tpa++;
			mb++;
		}
		if (a[tpa].id < b[tpb].id){
			if (!vis[b[tpb].h][1])
				buk[b[tpb].c] += n - mb;
			vis[b[tpb].h][1] = 1;
			tpb++;
			ma++;
		}
	}
	for (int i = 0; i <= 200000; i++)
		if (buk[i]){//扫一遍颜色
			cnt++;
			qq.push(i);
			q2.push(buk[i]);
		}
	cout << cnt << "\n";
	while (!qq.empty()){
		cout << qq.front() << " " << q2.front() << '\n';
		qq.pop();
		q2.pop();
	}
}
```

---

## 作者：2c_s (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc346_e)

## 思路

由于是覆盖问题，很容易想到反向覆盖可以保证不会重复。我们考虑离线操作。

读入数据后反向遍历（注意“已覆盖”这三个字和行、列的区分）：

- 如果当前要进行 $1$ 号操作，那么看看这一**行**有没有被覆盖过。如果没覆盖过，就记录这一**行**的覆盖情况，将记录已覆盖的**行**数的变量 $+1$，并将这个颜色的数量加上 **$W-$** 已覆盖的**列**数。

- 如果当前要进行 $2$ 号操作，那么看看这一**列**有没有被覆盖过。如果没覆盖过，就记录这一**列**的覆盖情况，将记录已覆盖的**列**数的变量 $+1$，并将这个颜色的数量加上 **$H-$** 已覆盖的**行**数。

最后记录颜色 $0$ 的覆盖方格数就是 $H\times W$ 减去其他所有颜色的覆盖方格总数。最后输出图中颜色的数量和每个颜色覆盖的方格数。

- 值最大可能为 $4\times 10^{10}$，记得开 long long。

## 核心代码

```cpp
const int N=2e5+10;
ll n,m,q,a[N],x[N],t[N],cnt,col[N],cnth,cntl;
bool r[N],c[N];
/*
n,m,q,a[],x[],t[]：不做解释。
cnt：总颜色个数。
cnth：已覆盖的行数。
cntl：已覆盖的列数。
col[]：每个颜色覆盖的方格数。
r[]：当前行有没有被覆盖过。
c[]：当前列有没有被覆盖过。
*/
signed main(){
    cin>>n>>m>>q;
    for(int i=q;i>=1;--i)cin>>t[i]>>a[i]>>x[i];
    for(int i=1;i<=q;++i){
        if(t[i]==1&&!r[a[i]]){
            r[a[i]]=1;
            ++cnth;
            col[x[i]]+=m-cntl;
        }
        if(t[i]==2&&!c[a[i]]){
            c[a[i]]=1;
            ++cntl;
            col[x[i]]+=n-cnth;
        }
    }
    col[0]=n*m;
    for(int i=1;i<=(int)2e5;++i){
        col[0]-=col[i];
        if(col[i])++cnt;
    }
    if(col[0])++cnt;
    cout<<cnt<<"\n";
    for(int i=0;i<=(int)2e5;++i){
        if(col[i])printf("%d %lld\n",i,col[i]);
    }
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/152438807)

---

## 作者：Xuan_qwq (赞：3)

~~社贡已经掉没了，赶紧来写题解~~

### 题面大意
给定一个 $H\times W$ 的网格，初始每个格子都是颜色 $0$，有 $m$ 次操作，每次把一行或一列所有格子全部变成颜色 $X_i$。问最后每个颜色有多少个格子。

### 思路
看到 $2\times 10^5$ 的数据范围，我们知道直接在线更新网格情况肯定是不可能的了。

那么让我们来考虑一下题目中操作的特性。

我们注意到，只有后一次的操作所染的颜色可能覆盖之前的操作所染的颜色，不存在反向覆盖的情况。

最后一次操作一定产生了纯色的一行（列）。如果我们把这一行（列）去掉呢？

倒数第二次操作产生的纯色的一行（列）有三种可能：
- 被最后一次操作完全覆盖。
- 被最后一次操作覆盖了一格。
- 没有被最后一次操作覆盖。

如果是第一种情况，那么去掉了这一行（列），倒数第二次操作就无效了，也不会被计入答案，跳过。

如果是第二种情况，将最后一次操作的一行（列）去掉后，被覆盖的一格也去掉了，又形成了纯色的一行（列）。

如果是第三种情况，这一行（列）本身就是纯色的。

我们发现，这一行要么不计入答案，要么就是作为纯色的一行计入答案，也就是说，我们可以把这一次操作当作最后一次操作，并且让棋盘的行（列）数减一。

于是我们就可以从后往前计算，对于最后一次操作，如果它所在的行（列）没有被删除，那就以当前的棋盘大小计算该颜色所占的格子数并计入答案，然后把这一行（列）删掉。

最后要注意颜色 $0$ 的情况，我们可以用原棋盘减去后面所有颜色所占格子数的总和得到。

好了上代码！

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;//n是h，m是w，q是原题中的m
long long cnt[200005];//记录每种颜色已经计算了多少格
int vis[200005][2];//标记这一行(列)是否被删
int x,y;//已经删掉的列数，行数
struct Q{
	int a,t,x; 
}op[200005];//记录操作
int main(){
	cin>>n>>m>>q;
	for(int i=0;i<q;i++){
		cin>>op[i].t>>op[i].a>>op[i].x;
		op[i].t--;//输入的t是1和2，我们把它变成0和1
	}
	for(int i=q-1;i>=0;i--){
		int pos=op[i].a;
		int t=op[i].t;
		int X=op[i].x;
		if(vis[pos][t])continue;
		vis[pos][t]=1;//把这一行(列)删掉
		if(t==0){
			cnt[X]+=m-x;
			y++;//删掉了一行
		}
		else{
			cnt[X]+=n-y;
			x++;//删掉了一列
		}
	}
	cnt[0]=1ll*n*m;
	for(int i=1;i<=200000;i++)cnt[0]-=cnt[i];
	int tot=0;
	for(int i=0;i<=200000;i++){
		if(cnt[i]!=0)tot++;
	}
	cout<<tot<<endl;
	for(int i=0;i<=200000;i++){
		if(cnt[i]!=0)cout<<i<<" "<<cnt[i]<<endl;
	}
	return 0;
}
```

---

## 作者：QWQ_123 (赞：2)

先将每一行和每一列的最终颜色储存下来。

然后将行的最终颜色排序。

那么对于一个列的颜色，它可以覆盖时间比他小的所有行，所以可以二分最后一个 $\le$ 它时间的值，设为 $i$。

然后前 $i$ 个就是都覆盖成列的颜色，后面就是行对应的颜色，那么对于颜色计算贡献，将列的颜色个数加上 $i$，然后用一个数组记录行的颜色加了多少次，那么每一差分一下，最后前缀和即可。

不过由于每次加的都是 $[i+1,n]$ 这段区间，所以不用减（因为没有用到 $n+1$，所以就算减了前缀和也算不上）。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

int n, m, k;
pair<int, int> g[200010], h[200010];
int ma[200010];
int s[200010];

signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for(int i = 1; i <= 200000; ++i) g[i] = {0, 0};
	for(int i = 1; i <= 200000; ++i) h[i] = {0, 0};
	for (int i = 1; i <= k; ++i) {
		int opt, x, y; scanf("%lld%lld%lld", &opt, &x, &y);
		if (opt == 1) {
			g[x] = {y, i};
		} else if (opt == 2) {
			h[x] = {y, i};
		}
	}
	sort(g + 1, g + 1 + n, [&](pair<int, int> a, pair<int, int> b) {
		return a.second < b.second;
	});
	g[0] = {-1, -1};

	for (int i = 1; i <= m; ++i) {
		int l = 0, r = n;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (g[mid].second <= h[i].second) l = mid;
			else r = mid - 1;
		}
		ma[h[i].first] += l;
		++s[l + 1];
	}
	for (int i = 1; i <= n; ++i) s[i] += s[i - 1];
	for (int i = 1; i <= n; ++i) ma[g[i].first] += s[i];

	int cnt = 0;
	for (int i = 0; i <= 200000; ++i) if (ma[i]) ++cnt;
	printf("%lld\n", cnt);
	for (int i = 0; i <= 200000; ++i) if (ma[i]) printf("%lld %lld\n", i, ma[i]);

	return 0;
}
```

---

## 作者：kczw (赞：2)

# 题意
给定一张 $H\times W$ 的网格图（$H$ 行 $W$ 列），最初颜色为 $0$。

对其进行 $M$ 次操作，有 $T_i,A_i,X_i$：

- $T_i=1$，则对第 $A_i$ 行覆盖 $X_i$ 色。
- $T_i=2$，则对第 $A_i$ 列覆盖 $X_i$ 色。

问最后图上颜色总数以及不同颜色格子个数。

输出颜色个数时按颜色从大到小输出。
# 思路
如果正着做，死翘翘不用说。

正着做会死，有覆盖修改的功劳。那么就算不正着做，如何处理覆盖也是一大问题。

于是，很容易想到倒着做。因为倒着，所以原来的覆盖修改就变成了不可被覆盖，于是我们只需要维护行、列是否被修改的标记就可以轻松过此题了。
# 代码
```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

const int N=2e5+5;

int n[3],m;
int t[N],a[N],x[N];
int c[N],v[3][N],V[3],id[N],sum;

bool cmp(int aa,int bb){return c[aa]>0&&c[bb]>0?aa<bb:c[aa]>c[bb];}

main(){
    
    for(int i=1;i<=N-5;i++)id[i]=i;

    scanf("%lld%lld%lld",&n[1],&n[2],&m);
    for(int i=1;i<=m;i++)
        scanf("%lld%lld%lld",&t[i],&a[i],&x[i]);

    for(int i=m;i;i--){
	//倒着模拟
        if(v[t[i]][a[i]]||V[3-t[i]]==n[3-t[i]])continue;
 	//此行（或列）已被覆盖，或者所有列（或行）都已被覆盖，于是不可上色，跳过此次操作。
        V[t[i]]++;//行（或列）的覆盖数赠一
        v[t[i]][a[i]]=1;//此行（或列）被覆盖标记
        c[x[i]]+=n[3-t[i]]-V[3-t[i]];//上色格数计算：总列（或行）数减去已经被上色的列（或行）数
        sum+=n[3-t[i]]-V[3-t[i]];//被上色格子总数
    }
    c[0]+=n[1]*n[2]-sum;
    //未被上色格的颜色是 0
    sort(id,id+N-4,cmp);
    //颜色排序，脑子抽了写的，可以直接遍历颜色，总个数 2e5 左右。
    for(int i=0;i<=N-5&&c[id[i]]!=0;i++)
        if(c[id[i+1]]==0)
            printf("%lld\n",i+1);//颜色不为 0 的个数
    
    for(int i=0;i<=N-5&&c[id[i]]!=0;i++)
        printf("%lld %lld\n",id[i],c[id[i]]);
}
```

---

## 作者：Double_Light (赞：2)

可以考虑离线做法，从前往后比较难以实现，于是从后往前。

从最后染色的一次开始处理。记录每行是否被染色过的数组 $a$，以及每列是否被染色过的数组 $b$。

接下来有以下两种情况：

- 该行（列）后来被染色过了，后面颜色把这一行覆盖了。此时视为染色失败。

- 这是该行（列）的最后一次染色。若此时将一行进行染色，记录有多少列后来没有被染过色，设为 $k_1$，则将这 $k_1$ 列中对应该行的位置染上色。若此时将一列进行染色，记录有多少行后来没有被染过色，设为 $k_2$，则将这 $k_2$ 行中对应该列的位置染上色。

在第二种情况中，若 $k_1=m$（或 $k_2=n$），没有格子被染上颜色，但视为染色成功。

最终染完色后，记录有多少格被染了色，一共有 $n\times m$ 个格子，减去这些被染色的格子，剩余都是 $0$ 颜色。

代码如下：

```cpp
#include<iostream>
#include<map>
#include<algorithm>
#define int long long
using namespace std;
int n,m,k,opt[200005],x[200005],v[200005];
int lst1[200005],lst2[200005];//行或列中最后一次染色的操作编号
int hang,lie;//hang记录被染色的行数，lie记录被染色的列数
int color[200005],tot;//tot是成功染色的次数，color[i]代表第i次染色的颜色
map<int,int>ma,ans;//ma[i]记录第i种颜色以前有无成功染色过，ans[i]记录第i种颜色格子的个数
int zero,num;
signed main(){
	cin>>n>>m>>k;
	zero=n*m;//zero代表没有被染色的格子个数
	for(int i=1;i<=k;i++){
		cin>>opt[i]>>x[i]>>v[i];
		if(opt[i]==1){
			lst1[x[i]]=i;
		}
		if(opt[i]==2){
			lst2[x[i]]=i;
		}
	} 
	for(int i=k;i>=1;i--){
		if(opt[i]==1&&lst1[x[i]]>i)continue;//判断染色失败
		if(opt[i]==2&&lst2[x[i]]>i)continue;
		if(!ma[v[i]]){//如果当前颜色出现过，不需要记录一种新颜色
			ma[v[i]]=1;
			color[++tot]=v[i];
		}
		if(opt[i]==1){
			hang++;
			ans[v[i]]+=m-lie;
		}
		if(opt[i]==2){
			lie++;
			ans[v[i]]+=n-hang;
		}
	}
	for(int i=1;i<=tot;i++)zero-=ans[color[i]];
	if(!ma[0])color[++tot]=0,ans[0]+=zero;
	else ans[0]+=zero;//这里是特判有格子重新染上颜色0
	sort(color+1,color+tot+1);
	for(int i=1;i<=tot;i++){
		if(ans[color[i]])num++;//为防止成功染过色但该颜色格子数为0的情况重新扫一遍
	}
	cout<<num<<'\n';
	for(int i=1;i<=tot;i++){
		if(!ans[color[i]])continue;
		cout<<color[i]<<' '<<ans[color[i]]<<'\n';
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：2)

### 思路

定义矩阵为 $a$。

显然不能在线处理，否则 $10^{10}$ 的复杂度一定 $\tt TLE$。

考虑每一次操作所可以覆盖的格子，离线处理。

不同的列和列是互不干扰的，行同理。

行和列是干扰的，因为覆盖的是整行整列，所以它们一定互相干扰对方。如果第 $i$ 行（颜色为 $p$）在第 $j$ 列（颜色为 $q$）之后覆盖，那么 $a_{i,j}$ 的颜色会变为 $p$ 而不是 $q$。

如果有一行被覆盖了多次，我们只需要看最后一次。

我们造一组样例：
```
3 4 5
1 3 2
2 3 1
2 4 3
1 3 4
2 2 3
```

变化顺序将如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/r959r92h.png)

如果我们倒序考虑最终结果图，那么会发现：

- 第 $5$ 次操作因为是最后一次，所以每一个格子都能覆盖上。
- 第 $4$ 次操作虽然不是最后一次，但是后面并没有列来干扰它了，所以也是每一个格子都能覆盖上。
- 第 $3$ 次操作操作的是列，但是它后面已经有两行被提前覆盖了，所以它只能覆盖 $1$ 格。
- 第 $2$ 次同理。
- 第 $1$ 次操作覆盖的第 $3$ 行第 $5$ 次操作已经覆盖过了，一个都不能覆盖。

这就是最终的结果图。

那么，最后会留下一些为 $0$ 的颜色格子，这些该怎么考虑呢？

有两种方法。

1. 数学法：$0$ 的数量就是全部的数量 $-$ 被覆盖的数量。具体来说，如果 $m$ 行 $n$ 列被覆盖，则剩余 $0$ 数量应为 $h\times w-m\times w-n\times h+n\times m$。
2. 暴力法。我们可以看成开局的全是 $0$ 是进行了 $h+w$ 次操作，每一次都覆盖成 $0$ 造成的，这样增加了 $\operatorname{O}(h+w)$ 的时间复杂度，但是仍然可以通过。

### 代码实现

显然我们可以记录数组表示操作，不过我这里用了一个栈。

栈满足后进先出的原则，调试更加方便。

还有答案数组要开 $\texttt{long long}$！不要忘记输出总和！

### Code（暴力法）：

```
#include<bits/stdc++.h>
using namespace std;
int h,l,m,opt,x,y;
long long ans[200005];
bool f[200005][3];
stack<int>st1;
stack<int>st2;
stack<int>st3;
int main(){
	cin>>h>>l>>m;
	for(int i=1;i<=h;i++){
		st1.push(1);
		st2.push(i);
		st3.push(0);
	}
	for(int i=1;i<=l;i++){
		st1.push(2);
		st2.push(i);
		st3.push(0);
	}
	while(m--){
		cin>>opt>>x>>y;
		st1.push(opt);
		st2.push(x);
		st3.push(y); 
	}
	int hang=0,lie=0;
	while(!st1.empty()){
		opt=st1.top();
		x=st2.top();
		y=st3.top();
		st1.pop();st2.pop();st3.pop();
		if(f[x][opt]==1)continue;
		f[x][opt]=1;
		if(opt==1){
			ans[y]+=(l-lie);
			hang++;
		}
		else{
			ans[y]+=(h-hang);
			lie++;
		}
	}
	int sum=0;
	for(int i=0;i<=200000;i++){
		if(ans[i]>0)sum++;
	}
	cout<<sum<<endl;
	for(int i=0;i<=200000;i++){
		if(ans[i]>0)cout<<i<<' '<<ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：2)

# 题解 ABC346E - Paint

前排提示：本题解为 **时光倒流** 做法。

### 题意

已提交翻译。

给定 $H\times W$ 的网格，初始全部为颜色 $0$，进行 $m$ 次操作，每次操作可能是：
- `1 a x`：将第 $a$ **行**填充为颜色 $x$。
- `2 a x`：将第 $a$ **列**填充为颜色 $x$。

求操作完后表格中的颜色种数。

数据范围：$H,W,m,a,x \le 2\times10^5$。

### 做法

由于后面的操作会覆盖前面的操作，所以考虑时光倒流。

我们倒着做操作，此时先做的操作会覆盖后做的操作。因此开三个数组 $r,c,flg$，分别维护哪些行被操作过、哪些列被操作过、每个数字出现了几次。有时所有行（或者列）都被操作过了，此时不能再进行操作，因此还需要用变量 $sr,sc$ 记录有多少行和多少列被操作过。

操作时（为了方便，我们假设这是操作 $1$，操作 $2$ 完全同理），如果 $sc<W$（还有没操作过的列）且 $r_i=0$（该行还未操作过）则 $r_i\leftarrow1$，$flg_i\leftarrow flg_i+(W-sc)$（没被操作过的列都操作上）。这样就可以实现 $O(m)$ 完成全部操作了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll n,m,k,op[200010],a[200010],x[200010],r[200010],c[200010],flg[200010],cnt,sr,sc,tot;
int main(){
	cin>>n>>m>>k;
	for(int i=0;i<k;i++){
		cin>>op[i]>>a[i]>>x[i];
	}
	for(int i=k-1;i>=0;i--){
		if(op[i]==1){
			if(sc==m)continue;
			if(!r[a[i]]){
				sr++;
				if(x[i])tot-=flg[x[i]];
				if(!flg[x[i]])cnt++;
				flg[x[i]]+=m-sc;
				if(x[i])tot+=flg[x[i]];
			}
			r[a[i]]=1;
		}
		else{
			if(sr==n)continue;
			if(!c[a[i]]){
				sc++;
				if(x[i])tot-=flg[x[i]];
				if(!flg[x[i]])cnt++;
				flg[x[i]]+=n-sr;
				if(x[i])tot+=flg[x[i]];
			}
			c[a[i]]=1;
		}
	}
	if(flg[0]==0&&sr<n&&sc<m){
		cnt++;
	}
	flg[0]=n*m-tot;
	cout<<cnt<<endl;
	for(int i=0;i<200010;i++){
		if(flg[i]){
			cout<<i<<' '<<flg[i]<<endl;
		}
	}
	return 0;
}

```

---

## 作者：KSCD_ (赞：2)

# 题意
有一个 $H$ 行 $W$ 列网格，初始均为颜色 $0$。$M$ 次操作，每次把一整行或一整列涂成一种颜色，求最后的颜色种数和每种颜色的格子数。
# 思路
暴力修改查找复杂度过高，无法通过本题。

我们发现每次操作都会覆盖之前的操作，所以考虑倒序处理，这样每次就能直接确定下若干格的颜色，之后不再考虑这些格。

那么若涂某一行，则以后再涂这行就不再产生影响，再涂列时都不会再涂这行的那一格。涂某一列造成的影响也一样。

如此处理，由于初始为颜色 $0$，最后把没涂过的格子涂成颜色 $0$ 即可。

具体看代码实现吧。
# 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+10;
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
    return s*w;
}
struct nod
{
	int t,x,id;
}a[N];
bool hang[N],lie[N];//标记某一行/列是否整体被涂过 
int h,w,m,sum[N],aa[N],ab[N],cnt; 
signed main()
{
	h=read(),w=read(),m=read();
	int th=h,tw=w;//剩余可涂的行/列数 
	for(int i=1;i<=m;i++) a[i].t=read(),a[i].id=read(),a[i].x=read();
	for(int i=m;i>=1;i--)//记录操作并倒序处理 
	{
		if(a[i].t==1)//涂行 
		{
			if(hang[a[i].id]) continue;//涂过就跳过
			hang[a[i].id]=1,sum[a[i].x]+=tw;//标记并更新答案 
			th--;//之后涂列时少涂一格 
		}
		else//涂列同上 
		{
			if(lie[a[i].id]) continue;
			lie[a[i].id]=1,sum[a[i].x]+=th;
			tw--;
		}
	}
	sum[0]=h*w;
	for(int i=1;i<=2e5;i++) sum[0]-=sum[i];//从总数中减掉非零的格子数 
	for(int i=0;i<=2e5;i++) if(sum[i]) 
		aa[++cnt]=i,ab[cnt]=sum[i];//记录答案 
	cout<<cnt<<"\n";
	for(int i=1;i<=cnt;i++) cout<<aa[i]<<' '<<ab[i]<<"\n";
	return 0;
}
```

---

## 作者：SJH__qwq (赞：2)

考虑春测的套路。把所有的询问倒着处理，每一次记录一下每一行 / 列是否被染色，每一行 / 列被染了多少次色。

发现是一个整体修改的问题，所以用线段树解决。但是又发现每一次必然是把所有的行 / 列全部修改，所以直接用两个数来打标记修改即可。

时间复杂度为 $O(n)$。

---

