# Shortest Path

## 题目描述

在Ancient Berland有$n$ 座城市和$m$ 条长度相同的双向道路。城市从$1$ 到$n$ 编号。根据一个古老的迷信说法，如果一个旅行者连续访问了$a_i$ 、$b_i$ 、$c_i$ 三座城市而不去拜访其他城市，来自东方的神秘力量将使他遭受巨大的灾害。传说中一共有$k$ 组这样的城市，每个三元组都是有序的，这意味着你可以按照$a_i$ 、$c_i$ 、$b_i$ 这样的方式来访问一组城市而不遭受灾害。Vasya想要从城市$1$ 走到城市$n$ 并且不受到诅咒。请告诉他最短路的长度，并输出一条路线。

## 样例 #1

### 输入

```
4 4 1
1 2
2 3
3 4
1 3
1 4 3
```

### 输出

```
2
1 3 4
```

## 样例 #2

### 输入

```
3 1 0
1 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4 4 2
1 2
2 3
3 4
1 3
1 2 3
1 3 4
```

### 输出

```
4
1 3 2 3 4
```

# 题解

## 作者：Llx2022 (赞：5)

**双倍经验**，[P1811 最短路](https://www.luogu.com.cn/problem/P1811)

## **题意**

给定一个包含 $N$ 个点，$M$ 条边的无向图，每条边的边权均为 $1$。

再给定 $K$ 个三元组 $(A,B,C)$，表示从 $A$ 点走到 $B$ 点后不能往 $C$ 点走。注意三元组是有序的，如可以从 $B$ 点走到 $A$ 点再走到 $C$。

现在你要在 $K$ 个三元组的限制下，找出 $1$ 号点到 $N$ 号点的最短路径，并输出任意一条合法路径，无解则输出 `-1`。

### **数据范围**
$N \le 3000$，$M \le 20000$，$K \le 100000$。

这个 $n$ 范围这么小，而且只有某些路径有限制，显然可以**直接保存路径**。

设 $p_{v,i}=u$ 表示路径 $v$ 到 $i$ 的父亲是 $u$，其实二元组 $p$ 相当于 $u,v,i$ 到 $v,i,new$，若出现每次重复走的路径和不能走的路径判断一下，最后倒退回去输出即可。

# **Code**

```cpp
#include<iostream>
#include<queue>
#include<utility>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
template<typename T>inline void read(T &x){
	x=0;T f=1;char ch=getchar();
	while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=getchar();}
	while(ch>=48&&ch<=57){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
const int N=3e3+9;
vector<int> a[N];
queue<pair<int,int> > q;
int p[N][N];
int n,m,k;
map<pair<pair<int,int>,int>,int> ch;
int main(){
    read(n),read(m),read(k);
    for(int i =1;i<=m;i++){
        int u,v;
        read(u),read(v);
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=1;i<=k;i++){
        int a,b,c;
        read(a),read(b),read(c);
        ch[{{a,b},c}]++;
    }
    pair<int,int> ans={-1,-1};
    q.push({1,1});
    while(!q.empty()){
        int u=q.front().first;
        int v=q.front().second;
        q.pop();
        if(v==n){
            ans={u,v};
            break;
        }
        for(int i:a[v]){
            if(p[v][i]||ch[{{u,v},i}])continue;
            p[v][i]=u;
            q.push({v,i});
        }
    }
    if(ans.first==-1){
        puts("-1");
        return 0;
    }
    vector<int> path;
    while(ans.second!=1){
        path.push_back(ans.second);
        ans={p[ans.first][ans.second],ans.first};
    }
    
    printf("%d\n",path.size());
    path.push_back(1);
    reverse(path.begin(),path.end());
    for(int i:path){
        printf("%d ",i);
    }
    return 0;
}
```

---

## 作者：_NoOne (赞：5)

本题可用hash + BFS。

- 将给定的三元组插入哈希表, 定义Hash(x) = (a * b * c + a + b + c) % M, 其中M = 99991。

	```cpp
	vector<triplet>Hash[M + 1];
	inline int getHash(triplet x) {
	    return ((x.a * x.b % M * x.c % M) + x.a + x.b + x.c) % M;
	}
	inline void insert(triplet x) {
	    Hash[getHash(x)].push_back(x);
	}
	```
- 对于当前点cur, 已知指向该点的边的id, 则有三元组(Edge[id^1].to，cur, to)。(利用了成对储存技巧) 

- 查询是否为被诅咒的三元组：
	```cpp
	inline bool check(triplet x) {
	    for (auto i : Hash[getHash(x)]) 
	        if (x.a == i.a && x.b == i.b && x.c == i.c) return true;
	    return false;
	}
- BFS中, pre[i], dis[i], vis[i]分别表示编号为i的边的前驱, 经过的距离，是否访问过。（如果储存节点的信息，会出现样例3中一个点多次被访问，输出路径出现死循环)

BFS:
```cpp
inline void BFS() { 
	queue<pair<int, int> >q; //first记录当前节点 second记录指向该节点的边的id
	q.push({1, 0});
	while (!q.empty()) {
		int cur = q.front().first, id = q.front().second;
		q.pop();
		for (int i = head[cur]; i; i = Edge[i].next) {
			int to = Edge[i].to;
			if (check(triplet(Edge[id ^ 1].to, cur, to)) || vis[i]) continue; //三元组判断以及该边是否访问过
			dis[i] = dis[id] + 1, pre[i] = id, vis[i] = true;
			//到达i号边的距离 并记录i号边的前驱
			if(to == n) {
				printf("%d\n", dis[i]), print(i);
				return;
			}
			q.push({to, i});
		}
	}
	puts("-1");
}
```

完整代码:
```cpp
#include<bits/stdc++.h>
constexpr int MAXN = 3e3 + 3;
constexpr int MAXM = 2e4 + 4;
constexpr int M = 99991;
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) f = (ch == '-') ? -1 : 1, ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}
int n, m, k, tot = 1;
int dis[MAXM << 1], pre[MAXM << 1], head[MAXN], vis[MAXM << 1];
struct triplet { //三元组
	int a, b, c;
	triplet(){}
	triplet(int _a, int _b, int _c) : a(_a), b(_b), c(_c){}
}tmp;
struct E{ //边
	int to, next;
	E(){}
	E(int _to, int _next) : to(_to), next (_next){}
}Edge[MAXM << 1];
inline void add(int from, int to){
	Edge[++tot] = E(to, head[from]), head[from] = tot;
	Edge[++tot] = E(from, head[to]), head[to] = tot;
}
/******************hash********************/
vector<triplet>Hash[M + 1];
inline int getHash(triplet x) {
	return ((x.a * x.b % M * x.c % M) + x.a + x.b + x.c) % M;
}
inline void insert(triplet x) {
	Hash[getHash(x)].push_back(x);
}
inline bool check(triplet x) {
	for (auto i : Hash[getHash(x)]) 
		if (x.a == i.a && x.b == i.b && x.c == i.c) return true;
	return false;
}
/*****************hash********************/
inline void print(int id) {
	if(id != 0) print(pre[id]), printf("%d ", Edge[id].to);
	else printf("1 ");
}
inline void BFS() { 
	queue<pair<int, int> >q; //first记录当前节点 second记录指向该节点的边的id
	q.push({1, 0});
	while (!q.empty()) {
		int cur = q.front().first, id = q.front().second;
		q.pop();
		for (int i = head[cur]; i; i = Edge[i].next) {
			int to = Edge[i].to;
			if (check(triplet(Edge[id ^ 1].to, cur, to)) || vis[i]) continue;
			dis[i] = dis[id] + 1, pre[i] = id, vis[i] = true;
			//到达i号边的距离 并记录i号边的前驱
			if(to == n) {
				printf("%d\n", dis[i]), print(i);
				return;
			}
			q.push({to, i});
		}
	}
	puts("-1");
}
int main() {
	n = read(), m = read(), k = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		add(u, v); //建图 需成对储存 tot
	}
	for (int i = 1; i <= k; i++) {
		tmp.a = read(), tmp.b = read(), tmp.c = read();
		insert(tmp); //插入hash表
	}
	BFS();
	return 0;
}
```


---

## 作者：BlankAo (赞：3)

看到题目是求带限制条件的最短路，想到 BFS。

当我走到一个点的时候，我们记录四个值 $o,las,dis,fro$，依次代表我现在所处的点，我的上一个点，我走过的距离，我是从队列的几号元素转移来的（便于最后输出方案）。

这样，我枚举下一个点 $v$​ 的时候，我只用判断如下两个条件：

1. $las,o,v$​ 是否是一个**被禁止的**三元组。

   用 C++11 的 `Tuple` 函数（即 `pair` 的升级版，可以有三元组、四元组等等），可以轻松判重。

2. 把双向边拆成两条单向边后，判断这条边有没有被走过。因为这是 BFS，早标记的时间肯定不大于晚标记的时间。

最终利用 $fro$ 去递归，输出答案即可。

```c++
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;++i)
#define mar(o) for(int E=fst[o];E;E=e[E].nxt)
#define v e[E].to
#define MP make_tuple
using namespace std;
const int n7=3012,m7=20123*2;
struct dino{int to,nxt;}e[m7];
struct cafe{int o,las,dis,fro;}que[m7];
int n,m,K,head,tail,ecnt,fst[n7];bool u[m7];
map < tuple<int,int,int>,bool > mop;

int rd(){
	int shu=0;bool fu=0;char ch=getchar();
	while( !isdigit(ch) ){if(ch=='-')fu=1;ch=getchar();}
	while( isdigit(ch) )shu=(shu<<1)+(shu<<3)+ch-'0',ch=getchar();
	return fu?-shu:shu;
}

void edge(int sta,int edn){
	ecnt++;
	e[ecnt]=(dino){edn,fst[sta]};
	fst[sta]=ecnt;
}

void output(int z){
	if(que[z].fro)output(que[z].fro);
	printf("%d ",que[z].o);
}

void bfs(){
	que[1].o=1,head=tail=1;
	while(head<=tail){
		cafe now=que[head];
		mar(now.o){
			if(u[E]||mop[ MP(now.las,now.o,v) ])continue;
			if(v==n){
				printf("%d\n",now.dis+1);
				output(head);
				printf("%d",n);
				exit(0);
			}
			u[E]=1,tail++;
			que[tail]=(cafe){v,now.o,now.dis+1,head};
		}
		head++;
	}
}

int main(){
	n=rd(),m=rd(),K=rd();
	rep(i,1,m){
		int sta=rd(),edn=rd();
		edge(sta,edn),edge(edn,sta);
	}
	rep(i,1,K){
		int p=rd(),q=rd(),z=rd();
		mop[ MP(p,q,z) ]=1;
	}
	bfs();
	puts("-1");
	return 0;
}
```



---

## 作者：SpeMars (赞：3)

```cpp
//蒟蒻的歪解，仅供各位奆佬们参考...
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
struct node{
    //pid为它是队列中的第pid个节点
    //pre为这个点从pre走过来
    //u为当前节点
    //ti为时间
    int pid,pre,u,ti;
}f,q[300010];
string s;
int u,v,n,m,k,a,b,c,r,l;
vector<int> g[3010];
map<string,bool> mp,mp2;
//mp存三元组
//mp2存这个点是否已经被某个点更新过
string str(int x){
    //手动把数字封装成字符串，奆佬们肯定都看得懂
    string s="";
    if(x==0)s+='0';
    while(x>0){
        s+=(char)((x%10)+'0');
        x/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}
void pri(node x){
	//递归输出
	if(x.pid==-1){
		printf("%d ",x.u);
		return; 
	}
	pri(q[x.pid]);
	printf("%d ",x.u);
	return;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }//建无向图
    for(int i=1;i<=k;i++){
        s="";
        scanf("%d%d%d",&a,&b,&c);
        s+=str(a);
        s+=" ";
        s+=str(b);
        s+=" ";
        s+=str(c);
        mp[s]=true;
        //用map储存三元组字符串封装
        //不能直接读入，会出错！不知道为什么
    }
    q[++r]=(node){-1,0,1,0};
    while(r>=l){//因为是要输出路径，所以手写队列方便递归输出
        f=q[++l];
        u=f.u;
        for(int i=0;i<g[u].size();i++){
            v=g[u][i];
            string pd="";
            pd+=str(f.pre);
            pd+=" ";
            pd+=str(u);
            pd+=" ";
            pd+=str(v);
            if(mp[pd]){
                continue;
                //如果有三元组限制，则无法走此路
            }
            pd="";
            pd+=str(u);
            pd+=" ";
            pd+=str(v);
            if(mp2[pd]){
            	continue;
            }//如果原来已经从这个点更新过来，则不需要走这条路，即走过了，再走一次结果一样
	    mp2[pd]=true;
            if(v==n){//达到目标输出路径
                printf("%d\n",f.ti+1);
                pri(f);
                printf("%d",n);
                return 0;
            }
            q[++r]=(node){l,u,v,f.ti+1};
            //新状态入队
            //l为这个点从该队列中第l个点更新过来
            //u为这个点为这个点从u更新过来
            //v为当前节点
        }
    }
    //无解
    printf("-1");
    return 0;
}
```


---

## 作者：SpeMars (赞：2)

上次的题解被卡了,原因:map效率太低，3秒时限也过不了于是我将map改为了哈希表
神奇的是时限开500ms也能过

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
struct node{
    int pid,pre,u,ti;
    //pid为当前节点由队列中的第pid个节点更新而来
    //pre为当前节点由节点pre更新过来
    //u为这个节点的编号
    //ti为走到这个点的最小时间(无权则用时间作为最短路程)
}f,q[300010];//q为手写队列
int u,v,n,m,k,a,b,c,r,l,base=3001;
//base将三元组封装成base进制数类似stringHash
//作用:将三元组映射为一个数值方便O(1)时间判断
//也可以将走过的路封装为base进制数
unsigned long long s;//Hash最好用unsigned long long 存
vector<int> g[3010];
vector<unsigned long long> syz[1000007],path[1000007];
inline int read(){
    register int s=0,w=0;
    static char ch=getchar();
    for(;!isdigit(ch);)ch=getchar();
    for(;isdigit(ch);){
        s=(s<<1)+(s<<3)+(ch^48);
        ch=getchar();
    }
    return w?-s:s;
}
void insert1(unsigned long long x){//在三元组限制中添加限制
	unsigned long long key=x%1000007;
	syz[key].push_back(x);
	return;
}
void insert2(unsigned long long x){
	//记录走过的路径(即从记录从u到v已经走过)
   	//(下次如果还是从u到v则不需处理)(because结果一样)
	unsigned long long key=x%1000007;
	path[key].push_back(x);
	return;
}
bool find(unsigned long long x){//在三元组中查询限制
	unsigned long long key=x%1000007;
	for(int i=0;i<syz[key].size();++i)if(x==syz[key][i])return true;
	return false;
}
bool find2(unsigned long long x){//在走过的路径中查询该路径是否走过
	unsigned long long key=x%1000007;
	for(int i=0;i<path[key].size();++i)if(x==path[key][i])return true;
	return false;
}
void pri(node x){//递归输出
	if(x.pid==-1){//(边界)
    		//如果这是第一个节点则回归，停止递归
		printf("%d ",x.u);
		return; 
	}
   	//输出它的前一个点的路径
	pri(q[x.pid]);
   	//再输出自己
	printf("%d ",x.u);
	return;
}
int main(){
    n=read(),m=read(),k=read();
    for(register int i=1;i<=m;++i){//建无向图
        u=read(),v=read();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(register int i=1;i<=k;++i){
        a=read(),b=read(),c=read();
        s=0,s+=a;s*=base,s+=b,s*=base,s+=c;
        //三元组封装并push进Hash
        insert1(s);
    }
    q[++r]=(node){-1,0,1,0};//初始节点入队
    for(;r>=l;){//手写队列方便递归输出
        f=q[++l];
        u=f.u;
        for(register int i=0;i<g[u].size();++i){
            v=g[u][i];
            //封装从u的前一个节点走向u再走向v是否有三元组限制
            s=0,s+=f.pre,s*=base,s+=u,s*=base,s+=v;
            if(find(s))continue;//如果有则不处理这种情况
            s=0,s+=u,s*=base,s+=v;
            //再处理这个点是不是由同一个点更新而来的
            if(find2(s))continue;//如果有也不处理(处理后结果一样)
	    insert2(s);
            if(v==n){//达到目标递归输出路径
                printf("%d\n",f.ti+1);
                pri(f);
                printf("%d",n);
                return 0;
            }
            //新状态入队
            q[++r]=(node){l,u,v,f.ti+1};
        }
    }
    //无解
    puts("-1");
    return 0;
}
```

---

## 作者：翟翟 (赞：1)

因为每条道路的长度都为 $1$，所以使用广搜。在拓展的时候记录当前节点、上一个节点、路径长度。判断是否可以走。还有就是判断从 $u$ 到 $v$ 能不能走，不是看 $vis_v$ 是否被标记，而是看 $vis_{u,v}$ 是否被标记，因为一个点可能重复到达。判断三元组时先判断 $a,b$ 和 $b,c$ 是否都联通（加上这个优化程序快了三倍）。

# Code
```
#include<cstdio>
namespace IO{
	static const int buf_size=1000000;
	static unsigned char buf[buf_size];
	static int buf_len,buf_pos;
	bool isEOF(){
		if(buf_pos==buf_len){
			buf_pos=0;
			buf_len=fread(buf,1,buf_size,stdin);
			if(buf_pos==buf_len)return 1;
		}
		return 0;
	}
	inline char gc(){
		return isEOF()?EOF:buf[buf_pos++];
	}
	inline int rint(){
		int x=0;
		char c=gc();
		for(;c<48||c>57;c=gc());
		for(;c>=48&&c<=57;c=gc())
			x=(x<<1)+(x<<3)+(c^48);
		return x;
	}
	template<typename T>
	void read(T&x){x=rint();}
	template<typename T,typename...Ts>
	inline void read(T&x,Ts&...rest){
		read(x);
		read(rest...);
	}
}
using IO::read;
typedef long long ll;
const int N=3001,M=4e4+1,K=1e5+1,mod=1000039; 
bool f[N][N],mp[1000039],g[N][N];
int n,m,k,u,v,a,b,c,q[M][3];
int tot,head[N],nxt[M],to[M];
void add(int u,int v){
	nxt[++tot]=head[u];
	head[u]=tot;
	to[tot]=v;
}
int hsh(ll a,int b,int c){
	return (a*n*n+b*n+c)%mod;
}
void print(int x){
	if(q[x][1])print(q[x][1]);
	printf("%d ",q[x][0]);
}
int main(){
	read(n,m,k);
	for(int i=0;i<m;++i){
		read(u,v);
		add(u,v);
		add(v,u);
		g[u][v]=g[v][u]=1;
	}
	for(int i=0;i<k;++i){
		read(a,b,c);
		if(g[a][b]&&g[b][c])
			mp[hsh(a,b,c)]=1;
	}
	int h=0,t=1;
	q[1][0]=1;
	q[1][1]=0;
	for(;h<t;){
		u=q[++h][0];
		v=q[q[h][1]][0];
		for(int i=head[u];i;i=nxt[i])
			if(!mp[hsh(v,u,to[i])]&&!f[u][to[i]]){
				f[u][to[i]]=1;
				q[++t][0]=to[i];
				q[t][1]=h;
				q[t][2]=q[h][2]+1;
				if(to[i]==n){
					printf("%d\n",q[t][2]);
					print(t);
					return 0; 
				}
			}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：wgyhm (赞：1)

# 【图论记录】CF59E Shortest Path

看了题解

## 题意

有 $n $ 个点 $m$ 条边的边权为 $1$ 的无向图。有 $k$ 个有序的三元组 $(x,y,z)$ ，不能出现连续走过 $x,y,z$。求 $1$ 到 $n$ 最短路并输出路径。

$1\le n\le 3000,1\le m \le 2\times 10^4,1\le k\le 10^5$

## 题解

边权为 $1$ 的最短路，考虑直接 $bfs$。对于三元组，可以用 $map$ 或者哈希存下来。

现在有个非常 $naive$ 的想法(全是我当时的想法)，直接跑最短路，队列里存上一次的点和上上次的点，对于每个点记录前驱。

当然这是有很多问题的。

* 队列里还要存走到上一个点的最短路

每个点的最短路大小是会不断被更新且变大的，所以要存下当前的最短路

* 不能每个点记录前驱，对于每条边记录前驱

把双向边拆为两条单向边，很显然每条边最多被走过一遍。这就有了一个优化：

* 如果这条边被搜过，则不继续搜

## Code

```cpp
#define maxn 3005
#define maxm 100005
int n,m,k,h[maxn],head=1,vis[maxm];
int pre[maxm],ans[maxn],tot;
struct node{
	int x,y,z;
	bool operator <(const node &a)const{
	    if (x^a.x) return x<a.x;
	    if (y^a.y) return y<a.y;
	    return z<a.z;
	}
	node (int a=0,int b=0,int c=0){
		x=a,y=b,z=c;
	}
};
map<node,bool>mp;
struct yyy{
	int to,z;
	inline void add(int x,int y){
		to=y;z=h[x];h[x]=head;
	}
}a[maxm];
queue<node>q;
inline void print(int now){
	rg int i;
	while (now){
		ans[++tot]=a[now^1].to;
		now=pre[now];
	}
	for (i=tot;i;i--) printf("%d ",ans[i]);printf("%d ",n);
}
inline int bfs(void){
	rg int i,x,y,z;
	q.push(node(1,0,0));
	while (!q.empty()){
		x=q.front().x;y=q.front().y;z=q.front().z;q.pop();
		for (i=h[x];i;i=a[i].z)
		    if (!vis[i]&&mp[node(a[y^1].to,x,a[i].to)]==0){
		    	pre[i]=y;q.push(node(a[i].to,i,z+1));vis[i]=1;
		    	if (a[i].to==n) return printf("%d\n",z+1),print(i),0;
			}
	}
	puts("-1");
}
signed main(){
    rg int i,x,y,z;
    read(n);read(m);read(k);
    for (i=1;i<=m;i++){
    	read(x);read(y);
    	a[++head].add(x,y);
    	a[++head].add(y,x);
	} 
	for (i=1;i<=k;i++){
		read(x);read(y);read(z);
		mp[node(x,y,z)]=1;
		
	}
	bfs();
	return 0;
}
```



---

## 作者：doyo (赞：1)

思路：BFS

一看这个题，本蒟蒻就想到了最短路（想不到的话GG）只是加一个判断，设pre[x]为x的上一个搜到的点，然后每次搜索判断f[pre[x]][x]是否等于v就行了呗

还顺便吐槽了一下你谷的评级

可是打完之后，样例没过，GG

发现没有那么简单，因为一个x可能由多个点转移而来

于是怎么办呢？ 一般搜索的东西，思路错了，多半是状态没设计好。

对于这道题，我们按边搜索，用队列记录下一条边的两个端点，然后在搜索的同时，我们就可以判断到所有点x可能的上一层，于是就A了。

见代码

```cpp
#include<cstdio>
#include<string>
#include<queue>
#include<cstdlib>
#include<vector>
#define il inline
using namespace std;
const int maxn=3005;
const int maxm=4e5+5;
struct Edge
{
    int next;
    int to;
}edge[maxm];
struct node
{
    int u;
    int v;
};
queue<node> q;
vector<int> f[maxn][maxn];//f[x][y]表示从x到y不能通过的点 
int n,cnt,tot,m,k;
int head[maxm],dis[maxn][maxn],ans[maxm],pre[maxn][maxn];
//dis[x][y]表示点1经过了x到达y的最短路径
//由于要输出路径，我们用pre记录路径 
il int read()//读入优化 
{
    int num=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=num*10+ch-'0';
        ch=getchar();
    }
    return num*f;
}
il bool check(int d,int u,int v)//判断是否有诅咒 
{
	for(int i=0;i<f[d][u].size();i++)
		if(f[d][u][i]==v) return false;
	return true;
}
il void addedge(int from,int to)
{
//链式前向星存边 
    edge[++tot].next=head[from];
    edge[tot].to=to;
    head[from]=tot;
}
il void print(int d)
{
    printf("%d\n1 ",dis[d][n]);
    int tmp,fat=n;
    while(fat!=1)
    {
        ans[++cnt]=fat;
        tmp=d;d=pre[d][fat];fat=tmp;
    }
    for(int i=cnt;i>=1;i--)
        printf("%d ",ans[i]);
    printf("\n");
}
il void bfs()
{
	//广搜模板 
    q.push((node){0,1});
    while(!q.empty())
    {
        node tmp=q.front();q.pop();
        int u=tmp.v,d=tmp.u;
        if(u==n)
        {
            print(d);
            exit(0);
        }
        for(int i=head[u];i;i=edge[i].next)
        {
            int v=edge[i].to;
            if(check(d,u,v)&&!dis[u][v])
            {
                pre[u][v]=d;
                dis[u][v]=dis[d][u]+1;
                q.push((node){u,v});
            }
        }
    }
}
int main()
{
    int x,y,z;
    n=read();m=read();k=read();
    for(int i=1;i<=m;i++)
    {
        x=read();y=read();
        addedge(x,y);
        addedge(y,x);
    }
    for(int i=1;i<=k;i++)
    {
        x=read();y=read();z=read();
        f[x][y].push_back(z);//注意由x到y以后，不能经过的点不只有1个 
    }
    bfs();
    printf("-1\n");
    return 0;
}
```


---

## 作者：SUNCHAOYI (赞：0)

对于 $k$ 对有序的三元组 $(x,y,z)$ 为不能走的路线。本题对选择恰当的工具存储三元组有着较高的要求。

首先想到的是 `map` 与 `set`，令 `set <int> ban[x][y]` 记录形如 $x \to y \to z_i$ 的所有 $z_i$。进行广度优先搜索，记录一个点 $u$ 的前驱 $p$ 点的同时遍历后继节点 $v$，若 $(u,v,z)$ 合法，即 `ban[x][y].find (z) == ban[x][y].end ()`，同时该路径可以更新，那么加入队列中去并记录下前驱节点（用于路径的输出）。于是得到了以下核心代码：

```cpp
set <int> ban[MAX][MAX];
void bfs ()
{
	q.push ({0,1});
	while (!q.empty ())
	{
		pair <int,int> x = q.front ();q.pop ();
		int p = x.first,u = x.second;
		if (u == n)
		{
			printf ("%d\n",dis[p][u]);
			print (p,u);
			ok = 1;puts ("");
			return ;
		}
		for (auto v : ve[u])
		{
			if (ban[p][u].find (v) == ban[p][u].end () && !dis[u][v])
			{
				pre[u][v] = p;dis[u][v] = dis[p][u] + 1;
				q.push ({u,v});
			}
		}
	}
}
```

虽然能过样例，可是……一交发现 $\texttt{MLE}$。仔细一看 $k$ 的范围，直接寄。于是尝试用哈希来优化空间。大体思路相同，而这次用 $xyz+x+y+z$ 对大质数 $p$ 的值来表示 $(x,y,z)$，考虑到重复，用 `vector <tri> hsh[M]` 来记录同一个值的不同三元组，这样空间便可大大降低，可以通过此题。代码如下:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 3005;
const int M = 999983;
const int MOD = 1e9 + 7;
inline int read ();
struct tri
{
	int x,y,z;
};
int n,m,k,ok,dis[MAX][MAX],pre[MAX][MAX];
vector <int> ve[MAX];
vector <tri> hsh[M];
queue <pair <int,int> > q;
int get (int x,int y,int z);
void add (int u,int v);
bool check (int x,int y,int z);
void bfs ();
void print (int u,int v);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();m = read ();k = read ();
	for (int i = 1;i <= m;++i)
	{
		int x = read (),y = read ();
		ve[x].push_back (y);ve[y].push_back (x);
	} 
	for (int i = 1;i <= k;++i)
	{
		int x = read (),y = read (),z = read ();
		hsh[get (x,y,z)].push_back ((tri){x,y,z});
	}
	bfs ();
	if (!ok) puts ("-1");
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
int get (int x,int y,int z)//进行哈希操作
{
	return (1ll * x * y * z % M + 1ll * x + 1ll * y + 1ll * z) % M;
}
bool check (int x,int y,int z)//检测是否合法
{
	for (auto tmp : hsh[get (x,y,z)])
		if (tmp.x == x && tmp.y == y && tmp.z == z) return 1;
	return 0;
}
void bfs ()
{
	q.push ({0,1});
	while (!q.empty ())
	{
		pair <int,int> x = q.front ();q.pop ();
		int p = x.first,u = x.second;
		if (u == n)
		{
			printf ("%d\n",dis[p][u]);//输出路径长度
			print (p,u);
			ok = 1;puts ("");
			return ;
		}
		for (auto v : ve[u])
		{
			if (!check (p,u,v) && !dis[u][v])//合法且能过更新
			{
				pre[u][v] = p;dis[u][v] = dis[p][u] + 1;
				q.push ({u,v});
			}
		}
	}
}
void print (int u,int v)// 递归输出路径
{
	if (!v) return ;//终止条件
	print (pre[u][v],u);
	printf ("%d ",v);
}
```

---

## 作者：TammyZhao (赞：0)

简单题。

我们使用 `map+tuple<int,int,int>` 来判断每个三元组是否被诅咒，然后跑 SPFA，SPFA 的 $\tt node$ 可以

+ 记录这个状态是通过哪个状态来的，来得到最终的路径。
+ 记录这个点的上一个点，这个点的上一个点的上一个点（为了检查是否是被诅咒三元组）

队列是手写的数组，一方面并不会有太多的状态需要加入队列，另一方面这样以前的状态不会消失，方便最后查找路径的时候获取。

```cpp
#define MT std::make_tuple
#define TP std::tuple<int,int,int>
#define PR std::pair<int,int>

const int maxn = 3e3 + 5;
const int maxm = 4e4 + 5;
const int inf = 1e9;

int n,m,k,u,v,w;
std::vector<PR> G[maxn];
std::map<TP,bool> M;

struct node{
	int u,s,d,f;
}; node q[maxm];
int st = 1,ed = 0;

#define node(a,b,c,d) (node){a,b,c,d}

bool vis[maxm];
int tmp[maxn],len;

void SPFA(){
	q[++ed] = node(1,0,0,0);
	while(st <= ed){
		int id; auto[u,s,d,f] = q[id = st++];
		if(u == n){
			int i = id;
			while(i){
				tmp[++len] = q[i].u;
				i = q[i].f;
			}
			print(len - 1,'\n');
			while(len) print(tmp[len--],' '); print('\n');
			exit(0);
		}
		for(auto[v,i] : G[u]){
			if(M[MT(s,u,v)] || vis[i]) continue;
			vis[i] = true;
			q[++ed] = node(v,u,d,id);
		}
	}
}

int main(){
	read(n,m,k);
	int ec = 0;
	rep(i,1,m){
		read(u,v);
		G[u].emplace_back(v,++ec);
		G[v].emplace_back(u,++ec);
	}
	rep(i,1,k){
		read(u,v,w);
		M[MT(u,v,w)] = 1;
	}
	SPFA();
	print("-1\n");
    return 0;
}
```

---

## 作者：超级玛丽王子 (赞：0)

RT，和 P1811 是双倍经验，但是被那道题卡了空间。

## 题意简述

> 给定 $n$ 个点 $m$ 条边的无权图，以及若干条限制条件，表示不能连续经过 $a,b,c$ 三个点，求从 $1$ 到 $n$ 的最短路。

## 解法

看到无权图最短路，直接上广搜。难点主要在于限制条件怎么判断和更新。

先解决限制条件的存储问题。一开始没过脑子开了一个 `vector<int>k[3005][3005]`，然后条件 $(a,b,c)$ 就存储为 `k[a][b].push_back(c)`，查询的时候遍历一遍 `k[a][b]` 即可。CF 上可过，P1811 会 MLE。于是改为索引一个点（例如 $b$），`vector` 里存储 `pair<int,int>` 记录 $(a,c)$。这样空间就可以卡的非常小了。本以为时间会牺牲一点，结果反倒时间更快了（（（

这里想了一个小优化，没有实现，就是如果限制条件更多，可以对 `vector` 做排序，然后二分去找是否存在这个限制条件。代价是要多一个排序，不知道时间能不能更快。

再考虑怎么更新。一开始没注意到是无权图，以为要跑 Dijkstra，然后打算给每个点手写个栈记录更新过这个节点的所有点以及对应的最短路。显然这个栈关于最短路从顶到底单调递减，用的时候如果发现不满足限制条件，就从顶到底开始找第一个能符合条件的去更新（注意不弹出）。但是在处理前驱节点记录上没想好怎么搞。后来发现无权图，就简单 bfs，如果不满足限制条件就不入队即可。为了方便判断是否满足限制条件，将按点 bfs 改为按边 bfs，前向星里记录一个 `from`，然后队列里面压前向星的边编号即可。

最后有一步输出路径，常规套路记录前驱节点，最后回溯到 1 号节点反向输出即可。

在 bfs 过程中，可以直接开二维数组记录当前最短路和当前边前驱，但是为了压空间，代码中改为了直接记录边编号。

## 代码

```cpp
//快读快写函数声明如下
int read()
void wr(int x, char ch='\n')

#define pii pair<int, int>
const int N=3005,M=40005;
int tot=0,head[N],to[M],nxt[M],from[M];
inline void addedge(int u, int v) {
	to[++tot]=v;
	from[tot]=u;
	nxt[tot]=head[u];
	head[u]=tot;
}
inline void add(int u, int v) {
	addedge(u,v);
	addedge(v,u);
}

vector< pii >k[N];
queue<int>Q;
int dis[M],pre[M],ans[N],tail=1;

int n,m,K,x,y,a,b,c;
int elast;

int bfs() {
	to[0]=1,from[0]=0,nxt[0]=head[0]=0;
	Q.push(0);
	while(!Q.empty()) {
		int epre=Q.front();
		Q.pop();
		int fa=from[epre],u=to[epre];
		if(u==n) {
			elast=epre;
			return fa;
		}
		for(int e=head[u];e;e=nxt[e]) {
			int v=to[e];
			if(v==u||dis[e]) continue;
			bool flag=true;
			for(int i=0;i<k[v].size();++i) {
				if(k[v][i].second==u&&k[v][i].first==fa) {
					flag=false;
					break;
				}
			}
			if(flag) {
				dis[e]=dis[epre]+1;
				pre[e]=epre;
				Q.push(e);
			}
		}
	}
	return -1;
}

int main(void) {
	n=read(),m=read(),K=read();
	while(m--) {
		x=read(),y=read();
		add(x,y);
	}
	while(K--) {
		a=read(),b=read(),c=read();
		k[c].push_back(pii(a,b)); 
	}
	int fa=bfs();
	if(fa==-1) wr(-1);
	else {
		wr(dis[elast]),wr(1,' ');
		int sw,cur=n,curedge=elast;
		while(cur^1) {
			ans[tail++]=cur;
			sw=fa;
			curedge=pre[curedge];
			fa=from[curedge];
			cur=sw;
		}
		while(--tail) wr(ans[tail],' ');
	}
	return 0;
}
```

时间：41ms

空间：1.90MB

上述代码与原代码略有区别。

---

## 作者：太阳起晚了呢 (赞：0)

## 题解

### 题目大意

有 $n$ 个点 $m$ 条边的边权为 $1$ 的无向图。有 $k$ 个有序的三元组 $(x,y,z)$ ，不能出现连续走过 $x,y,z$。求 $1$ 到 $n$ 最短路并输出路径。

### Sulotion

本题可以使用广搜+hash技术

首先我们可以把给定的三元组哈希一下，然后打进去

然后我们每次搜索的时候就check一下

我们在BFS的时候顺手记录一下上一条边，利用双向边的性质check一下就可以了

具体见代码注释

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e4+10;
const int maxk=1e6+10;
const int maxm=2e5+10;//随便开的数据范围
const int mod=99991;
struct myhash
{
    int x,y,z;
}tmp[maxk];
int tot=0;
int n,m,k;
vector<int >f[100000];
int gethash(myhash tmp)
{
    return (((tmp.x*tmp.y)%mod*tmp.z)%mod+tmp.x+tmp.y-tmp.z)%mod;
}//简单hash值
void inserthash(int x,int y,int z)
{
    tmp[++tot].x=x;tmp[tot].y=y;tmp[tot].z=z;
    int key=gethash(tmp[tot]);
    f[key].push_back(tot);
}//插入一个hash值，并且建立hash表
bool check(int x,int y,int z)
{
    myhash kkk;kkk.x=x;kkk.y=y;kkk.z=z;
    int tim=gethash(kkk);
    for(int i=0;i<(int)f[tim].size();i++)//
    {
        myhash now=tmp[f[tim][i]];
        if(now.x==x && now.y==y && now.z==z) return 1;
    }
    return 0;
}//查询一下当前三元组是否合法
int cnt=1,head[maxn],dis[maxm],pre[maxm];
bool vis[maxm];
struct node
{
    int v,next;
}e[maxm<<1];
void add(int u,int v)
{
    e[++cnt].next=head[u];
    e[cnt].v=v;
    head[u]=cnt;
}//链式前向星建图
struct now
{
    int u,last;
};//这其实是一个pair，但是我写这道题的时候抽风了
now make(int u,int last)
{
    now tmp;
    tmp.u=u;tmp.last=last;
    return tmp;
}//make_pair
void pp(int i)
{
    if(i) {pp(pre[i]);printf("%d ",e[i].v);}
    else printf("1 ");
}//反向输出，记录边的前驱就可以了
void bfs(int st)
{
    queue<now>q;
    q.push(make(st,0));//记录一下当前节点和上一条边
    while(!q.empty())
    {
        int u=q.front().u,last=q.front().last;q.pop();
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].v;
            if(check(e[last^1].v,u,v) || vis[i]) continue;
            //利用双向边的性质找到上一个点
            //显然在我们把双向边拆成两个单向边，显然就不可能经过一条边两次
            pre[i]=last;dis[i]=dis[last]+1;vis[i]=1;//
            if(v==n)
            {
                printf("%d\n",dis[i]);
                pp(i);//如果找到了就输出
                return;
            }
            q.push(make(v,i));
        }
    }
    puts("-1");//没找到就-1
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1,u,v;i<=m;i++)
        scanf("%d%d",&u,&v),add(u,v),add(v,u);//拆边
    //cout<<1<<endl;
    for(int i=1,x,y,z;i<=k;i++)
        scanf("%d%d%d",&x,&y,&z),inserthash(x,y,z);//插入
    //cout<<check(1,4,3);
    bfs(1);//直接爆搜
    return 0;
}
```





---

## 作者：chen_qian (赞：0)

本题解与 @_NoOne 大佬 的题解高度相似

（本来只是想写个做题记录，但是能交题解就交吧）

那么对于本题，可以想到的是必须记录路径，这不仅仅是题目的输出要求，也是我们要满足题目中的三元组关系必须要的做法。

因为边权都是$1$,不难想到广搜。

那么假如说我们当前三步走的是$(x,y,z)$这三个节点，如何检索限制条件中是否有这样的三元组呢?

不难想到**Hsah**,设$h((x,y,z))=x*y*z+x+y+z \ mod \ m$

平均下来是$O(1)$检索。

那么现在有一个问题了，如样例3，我们如果想要满足条件的话，可能会有一些点会反复经历。

那么用一贯用的标记点的方法，是无法解决本题的。只好换一种标记了。。。

通过观察，如果我们最后得到的路径是序列$a$，那么对于任意的二元组$(a_i,a_{i+1})$两两之间必然互异。

也就是说我们如果把每条双向边拆成两条单向边之后，我们能通过标记边的方式来保证路径最短。

所以就记录上一条边就行了。

```
#include<bits/stdc++.h>
#define N 3005
#define M 20005
#define mod 99991
using namespace std;
int n,m,k,idx;
int a[N],head[N];
int ans[N];
int dis[N];
struct edge{
	int u,v,next;
}e[2*M];
struct node{
	int x,y,z;
};
void add(int u,int v){
	e[++idx].v=v;
	e[idx].u=u;
	e[idx].next=head[u];
	head[u]=idx;
}
int Hash(node a){
	return (((a.x*a.y)%mod*a.z)%mod+a.x+a.y+a.z)%mod;
}
vector<node> v[mod+5];
bool find(node a){
	int t=Hash(a);
	for(int i=0;i<v[t].size();i++){
		if(v[t][i].x==a.x&&v[t][i].y==a.y&&v[t][i].z==a.z) return true;
	}
	return false;
}
int path[N],cnt[N],p[N];
bool vis[N];
void print(int id){
	if(id){
		print(p[id]);
		cout<<e[id].v<<' ';
	}
	else cout<<1<<' ';
}
void bfs(){
	for(int i=1;i<=n;i++) dis[i]=-1;
	dis[1]=0;
	queue<pair<int,int> > q;
	q.push(make_pair(1,0));
	while(!q.empty()){
		int u=q.front().first,pre=q.front().second;
		q.pop();
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].v;
			if(vis[i]) continue;
			if(pre){
				node a;
				a.x=e[pre].u;
				a.y=u;
				a.z=v;
				if(find(a)) continue;
			}
			vis[i]=1;
			p[i]=pre;
			dis[i]=dis[pre]+1;
			if(v==n){
				cout<<dis[i]<<endl;
				print(i);
				return ;
			}
			q.push(make_pair(v,i));
		}
	}
	cout<<-1;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	idx=1;
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=k;i++){
		node a;
		scanf("%d%d%d",&a.x,&a.y,&a.z);
		v[Hash(a)].push_back(a);
	}
	bfs();
	return 0;
}
```


---

## 作者：luxiaomao (赞：0)

## 一道综合性挺强但又不会太毒瘤的好题

补充一下题解区对一些错误解法解释的不足。

其实本题就是在最短路模板题的基础上加入一个约束条件：三元组。

对于一个三元组 $(a,b,c)$，如果从 $a$ 走到 $b$，此时不允许走到 $c$。

笔者的第一个想法是：跑模板最短路，然后给每个点记录一下前驱，这样子构成前驱、当前点和目标点的三元组，然后用一个 `map` 一类的数据结构判断一下能不能跑，最后搜到 $n$ 的时候根据前驱一路找回到 $1$，倒序输出即可。

思路听起来可能一时半会找不出错，但是有一个关键的点：如样例 3 一类的数据，为了绕开三元组的限制，一个点可能不止一次被走过，这样的话，记录前驱的思路被证伪。

一个点可能不止一次被走过，那么一条边呢？

我们把无向边拆成两条有向边，然后化边为点，原来三元组的限制就变成了二元组，即不允许从一条边走向另一条相邻的边。

在这个前提下，如果路径最优，一条有向边不可能被重复经过。（大家可以自己想想，只有可能是这条有向边的反向边被经过）

我们用 `tuple<int,int,int>` 来存三元组，然后化边为点跑最短路（朴素的 BFS 就可以），这样你就通过了 P1811 最短路。

然而把代码放到这里，发现 MLE 了。

我们针对判断三元组的 `map<tuple<int,int,int>,bool>` 进行优化，用常规的 Hash 把它优化成 `vector<tuple<int,int,int> >`，减少内存开支。具体实现请看代码。（别忘了选好一个大质数进行 Hash）

## Code Time

```cpp

#include<bits/stdc++.h>
#define int long long
#define inf 1000000000
#define mod 999983
using namespace std;

int n,m,k;
vector<int> mp[3005];
vector<tuple<int,int,int> > flag[999983];

int get(int x,int y,int z){return (x*y*z%mod+x+y+z)%mod;} 
bool check(int x,int y,int z)
{
	for(auto a : flag[get(x,y,z)])
		if((tuple<int,int,int>){x,y,z} == a)return 1;
	return 0;
}

int dis[3005][3005],las[3005][3005];
queue<pair<int,int> > q;
int ans[3005];

void bfs()
{
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			dis[i][j] = inf;
	dis[0][1] = 0;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int l = q.front().first,u = q.front().second;
		q.pop();
		if(u == n)
		{
			printf("%lld\n",dis[l][n]);
			int tot = 1;
			while(1)
			{
				ans[tot++] = u;
				if(u == 1)break;
				int temp = l;
				l = las[l][u];
				u = temp;
			}
			while(--tot)printf("%lld ",ans[tot]);
			return;
		}
		for(int i = 0;i < (int)mp[u].size();i++)
		{
			int v = mp[u][i];
			if(check(l,u,v))continue;
			if(dis[l][u] + 1 < dis[u][v])
			{
				las[u][v] = l;
				dis[u][v] = dis[l][u] + 1;
				q.push(make_pair(u,v));
			}
		}
	}
	printf("-1");
	return;
}

signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	while(m--)
	{
		int u,v;
		scanf("%lld%lld",&u,&v);
		mp[u].push_back(v);
		mp[v].push_back(u);
	}
	while(k--)
	{
		int l,u,v;
		scanf("%lld%lld%lld",&l,&u,&v);
		flag[get(l,u,v)].push_back((tuple<int,int,int>){l,u,v});
	}
	bfs();
	return 0;
}
```

大家有什么问题欢迎私信我，谢谢支持！

---

