# Dungeons and Candies

## 题目描述

给定 $k$ 次文件，每次 $n*m$ 个字符。

传输文件，有两种方式：

1.直接传输，耗费 $n*m$ 个字符。

2.通过比较这个文件与前面某个文件的差别，耗费 $这个文件与那个文件不同的字符数*w$ 个字符，其中 $w$ 是常数。

文件顺序可任意交换。

求最小耗费字符数，并输出方案，有多种方案时任意输出一个。

## 说明/提示

$1<=n,m<=10$

$1<=k,w<=1000$

字符只会是 '.' 或大小写字母。

## 样例 #1

### 输入

```
2 3 3 2
A.A
...
A.a
..C
X.Y
...
```

### 输出

```
14
1 0
2 1
3 1
```

## 样例 #2

### 输入

```
1 1 4 1
A
.
B
.
```

### 输出

```
3
1 0
2 0
4 2
3 0
```

## 样例 #3

### 输入

```
1 3 5 2
ABA
BBB
BBA
BAB
ABB
```

### 输出

```
11
1 0
3 1
2 3
4 2
5 1
```

# 题解

## 作者：YanYou (赞：5)

# Solution

题意大概是说，两个矩阵的转移费用为不同的字符数 $* w$ 或 $ n * m $，只能由已经转移出的矩阵转移，求最小费用。 

~~显然~~可以将转移费用转化为图上的边，然后是每个点能被转移到且总费用最小，那么一个~~很显然的~~思路就是最小生成树。
跑一遍 $Kruscal$ 即可。

# Code 

```cpp

#include<bits/stdc++.h>
using namespace std;
#define rep(i,l,r) for(int i=l;i<=r;++i)

int n,m,k,w,f[1005],ans,cnt,t;
char a[1005][15][15];
vector<int> v[1005];
struct rec
{
	int x,y,z;
	
}e[1050005];

bool operator <(rec a,rec b)
{
	return(a.z<b.z);
}

int find(int x)
{
	if(f[x]==x)return x;else return(f[x]=find(f[x]));
}

void dfs(int x,int fa)
{
	if(x>0)cout<<x<<" "<<fa<<"\n";
	for(auto y:v[x])if(y!=fa)dfs(y,x);
}

int main()
{
	cin>>n>>m>>k>>w;
	rep(i,1,k)
	{
		rep(j,1,n)rep(k,1,m)cin>>a[i][j][k];
		e[++cnt].x=0,e[cnt].y=i,e[cnt].z=n*m;
		rep(j,1,i-1)
		{
			int sum=0;
			rep(k,1,n)rep(l,1,m)if(a[j][k][l]!=a[i][k][l])sum+=w;
			e[++cnt].x=i,e[cnt].y=j,e[cnt].z=sum;
		}
	}
	sort(e+1,e+cnt+1);
	rep(i,0,k)f[i]=i;
	rep(i,1,cnt)
	{
		int p=find(e[i].x),q=find(e[i].y); 
		if(p!=q)
		{
			f[p]=q;
			ans+=e[i].z;
			v[e[i].x].push_back(e[i].y),v[e[i].y].push_back(e[i].x);
			++t;
			if(t==k)break;
		}
	}
	cout<<ans<<"\n";
	dfs(0,-1);
	return 0;
}

```

---

## 作者：小明小红 (赞：2)

# CF436C 题解
**思路构想**：这道题是每两个点之间计算最小权值和，所以我们很容易想到**最小生成树**。

**如何实现**：我们知道传输一共有两种形式。

第一种是耗费这个文件与那个文件不同的字符数 $\times w$ 个，我们可以通过**循环**朴素地建边。

而第二种是**直接传输**，耗费 $n \times m$ 个，解决这个问题有很多种解法，这里我采用的是建立**原点**，将每个点都连接原点权值为 $n \times m$。为什么是正确的呢？我们来简单证明一下：若现在有两个点，这两点按照方案一要的字符数远大于方案二，而我们跑最小生成树的时候早就用 $n \times m$ 或更小的权值将这两个点直接或间接连一起了，所以这个方法是正确的。


建完了图，我们就可以在上面跑最小生成树了，我们在并查集的合并的时候可以**累加权值**，这样答案就出来了。

什么？你问方案怎么输出？我们可以合并并查集的时候建一个图，这个肯定是个树了，然后按照**前序遍历**输出即为步骤。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,k,w,fa1,fa2;
string s[1009][19];
ll cnt=0,fa[1009];
vector<ll>v[1009];
struct node {
	ll start,to,w;
} p[1000009];
bool cmp(node s1,node s2) {
	return s1.w<s2.w;
}
ll find(ll x) { //简单并查集
	if(fa[x]==x) {
		return x;
	} else {
		fa[x]=find(fa[x]);
		return(fa[x]);
	}
}
void print(ll x,ll fa) { //简单前序遍历
	if(x>0) {
		cout<<x<<' '<<fa<<endl;
	}
	for(ll i=0; i<v[x].size(); i++) {
		if(v[x][i]!=fa) {
			print(v[x][i],x);
		}
	}
}
void kruskal() { //简单最小生成树板子
	for(ll i=1; i<=k; i++) { //为原点建立边
		++cnt;
		p[cnt].start=0,p[cnt].to=i,p[cnt].w=n*m;
	}
	sort(p+1,p+cnt+1,cmp);
	for(ll i=1; i<=k; i++) {
		fa[i]=i;
	}
	ll ccnt=0,ans=0;
	for(ll i=1; i<=cnt; i++) {
		ll a1=p[i].start,a2=p[i].to;
		fa1=find(a1),fa2=find(a2);
		if(fa1==fa2) {
			continue;
		}
		fa[fa1]=fa2;
		ccnt++;
		ans+=p[i].w;
		v[a1].push_back(a2),v[a2].push_back(a1);//建树
		if(ccnt==k) {
			break;
		}
	}
	cout<<ans<<endl;
	print(0,-1);//原点遍历 
}
int main() {
	cin>>n>>m>>k>>w;
	for(ll q=1; q<=k; q++) {
		for(ll i=1; i<=n; i++) {
			for(ll j=1; j<=m; j++) {
				cin>>s[q][i][j];
			}
		}
		for(ll p1=1; p1<q; p1++) { //点两两之间建边
			ll num=0;
			for(ll i=1; i<=n; i++) {
				for(ll j=1; j<=m; j++) {
					if(s[q][i][j]!=s[p1][i][j]) {
						num++;
					}
				}
			}
			++cnt;
			p[cnt].start=p1,p[cnt].to=q,p[cnt].w=num*w;
		}

	}
	kruskal();
	return 0;
}
```
这篇题解到这里就结束了，谢谢你的观看，如果你有任何疑问或者找出任何错误可以在评论区联系我，我看到会及时回复。

---

## 作者：Benzenesir (赞：0)

对于这种贡献和整体数量相关的问题，确实可以考虑和最小生成树挂上勾……

总体来说还是有点怪的，考虑转化为图论模型，物品两两之间建边，权值为相互转移的代价，再新建一个节点，每个点向其连边，权值为其直接代价，因为第一个必须要直接转移，所以跑一遍 MST 就行了。

总结一下 MST 的一些性质，贡献没有方向，对于顺序没有强的限制。

```c++
#define tup tuple<int,int,int>
#include <numeric>
vector<tup> g;
char c[1010][11][11];
int n,m,k,w;
int f[1010],op[1010];
vector<int>ng[1010];

int cmp(int x,int y){
	int cnt=0;
	fp(i,1,n)fp(j,1,m) if(c[x][i][j]!=c[y][i][j]) ++cnt;
	return cnt;
}

int acc(int x){
	if(f[x]^x) return f[x]=acc(f[x]);
	return x;
}

void dfs(int now,int f){
	if(now!=k+1){
		cout << now <<' ';
		if(f==k+1) cout << 0 << endl;
		else cout << f << endl;
	}
	for(int x:ng[now])
		if(x^f) dfs(x,now);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	n=rd(),m=rd(),k=rd(),w=rd();
	fp(d,1,k)
		fp(i,1,n)
			fp(j,1,m){
				c[d][i][j]=getchar();
				while(isspace(c[d][i][j])) c[d][i][j]=getchar();
			}
	fp(d1,1,k)
		fp(d2,d1,k)
			g.emplace_back(d1,d2,w*cmp(d1,d2));
	fp(i,1,k) g.emplace_back(i,k+1,n*m);
	sort(g.begin(),g.end(),[](tup x,tup y){
		return get<2>(x)<get<2>(y);
	});
	iota(f+1,f+k+2,1);
	int ans=0;
	for(auto [u,v,w]:g){
		if(acc(u)==acc(v)) continue ;
		ng[u].emplace_back(v),
		ng[v].emplace_back(u);
		ans+=w;
		f[acc(u)]=acc(v);
	}cout << ans << endl;
	dfs(k+1,0);
	return 0;
}
```


---

