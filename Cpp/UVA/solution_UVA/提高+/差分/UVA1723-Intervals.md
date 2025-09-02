# Intervals

## 题目描述

有 $n$ 个区间，在区间 $[a_i,b_i]$ 中至少取任意互不相同的 $c_i$ 个整数。求在满足 $n$ 个区间的情况下，至少要取多少个正整数。

# 题解

## 作者：蒟蒻zunny (赞：47)

之前那篇题解的输出好像有点问题，但思想是没有任何问题的。

此题是差分约束的裸题，但我之前也不知道差分约束系统是什么。

定义：差分约束系统是一种特殊的N元一次不等式，包含N个变量及M个约束条件，每个约束条件由两个变量作差构成，形如Xi-Xj>=Ck，Ck是常数，1<=i,j<=N,1<=k<=M。如
```cpp
X1-X0>=2
X2-X1>=3
X3-X2>=2
X3-X0>=6
```
通过消元可得到X3-X0的最小值为7。假若我们从0->1建一条权值为2的边，从1->2建一条权值为3的边，以此类推。从0到3跑一遍SPFA求最长路，发现也为7。

这不是个巧合，因为求最长路时，SPFA的松弛操作后，dis[v]>=dis[u]+g[i].w，与不等式Xi>=Xj+Ck性质一样，所以SPFA可以求出最小值，又因为不等式同大取大，所以要求出最长路。~~所以SPFA死了吗？~~

最后，一定要注意输出，每个答案**空**一行，最后一个答案最后要输出换行。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 0x3f3f3f3f
using namespace std;
int t,n,head[500005],tot,ma,dis[500005];
bool vis[500005];
struct node{
    int u,v,next,w;
}g[5000005];
inline int rea(){//快读
    int s=0,g=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            g=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=(s<<3)+(s<<1)+(ch^48);
        ch=getchar();
    }
    return s*g;
}
inline void add(int u,int v,int w){//建图
    g[++tot].u=u;
    g[tot].v=v;
    g[tot].w=w;
    g[tot].next=head[u];
    head[u]=tot;
}
inline void spfa(){//SPFA求最长路，即可得出最小值
    queue<int>q;
    q.push(0);
    vis[0]=true;
    dis[0]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i;i=g[i].next){
            int v=g[i].v;
            if(dis[v]<dis[u]+g[i].w){
                dis[v]=dis[u]+g[i].w;
                if(!vis[v]){
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
}
int main(){
    t=rea();
    while(t--){
        memset(head,0,sizeof(head));
        memset(dis,-0x3f,sizeof(dis));
        tot=0;
        n=rea();
        for(int i=1;i<=n;i=-~i){
            int a=rea(),b=rea(),c=rea();
            add(a,b+1,c);//因为前缀和中，Sb-S(a-1)>=c，然而a-1要大于等于0，a有可能是0，所以我们加一
            ma=max(ma,b+1);
        }
        for(int i=1;i<=ma;i=-~i){
            add(i-1,i,0);
            add(i,i-1,-1);//Si-S(i-1)>=0,S(i-1)-Si>=-1
        }
        spfa();
        printf("%d\n",dis[ma]);
        if(t)
        	printf("\n");//注意输出！！！
    }
    return 0;
}
```

---

## 作者：追梦_Chen (赞：43)

这题是差分约束系统一个很经典的例题，需要好好写一波~~
# 差分约束系统
### 定义
如果一个系统是由n个变量和m个约束条件组成，并且每个约束条件能够形成形如$$x_i-x_j<=c_k$$
### 我们就称该系统是差分约束系统
若你在AC此题前，对差分约束系统概念及应用**不熟悉**，可以看看这位神犇的blog

[膜拜巨佬](https://blog.csdn.net/my_sunshine26/article/details/72849441#commentBox)

讲一讲我的理解（请路过的神犇斧正）：我觉得差分约束系统是利用题面中给出的约束条件，和题干中隐藏的约束条件建图，之后求解最短（长）路的过程，在建图的过程中要先关注具体问题，若求的是**两个变量差的最大值**，那么将所有不等式转变成"**<=**"的形式并且在**建图后求最短路**，反之在转换成"**>=**"的形式，并且求**最长路**
# **咳咳咳，我们回到本题**
本题就是从0-50000选出最少的数，使每个区间至少有c个数被选，这是求最小值，**所以我们待会要将所有的不等式转换成">="的形式**
我们用数组d[i]表示0-i之间至少要选多少个数，所以对于每一个约束条件，可以看成$$d[b_i]-d[a_i-1]>=c_i$$

![](https://cdn.luogu.com.cn/upload/pic/30521.png)
上述公式变形$$d[b_i]>=c_i+d[a_i-1]$$

#### **因此我们在a[i-1]和b[i]之间建一条长度为c[i]的边**

上述建边过程只是题干中给出的条件，我们还要找出题目中的隐藏条件（隐藏条件视题目而为，有则加）。

#### 因为d[i]表示的是0-i之间要选的最小个数，所以d[i]一定要大于d[i-1]；

#### 又因为每个数只能选一次，所以d[i]-d[i-1]要么为0，要么为1；
由上述两个条件，我们对应出两个不等式
$$d_i-d_{i-1}>=0$$
$$d_{i-1}-d_{i}>=-1$$

**所以我们在i-1和i之间连长度为0的有向边，在i和i-1之间连长度为-1的有向边**

因为i的范围是0-50000所以i-1会变成负数，我们都知道，若数组的下标为负，程序会运行错误，**所以我们不妨给所有的变量加1，这样就不会出现负下标了**，所以上述加边过程可简述为
```cpp
1---->在a[i]和b[i]+1之间连一条长度为c[i]的有向边

2---->在i和i+1之间连一条长度为0的有向边

3---->在i+1和i之间连一条长度为-1的有向边
```
***接着，设d[0]为1,以0为起点求单元最长路***
# 注意

```cpp
求单元最长路要用SPFA算法，因为Dijkstra算法的贪心思路不适用于最长路，但是SPFA算法会把点x的所有出边都遍历一遍。既能求最短，也能求最长。
能屈能伸~~~~~~~~~~
```
**代码自然是标配**

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <queue>
using namespace std;
const int maxn=500010;
int ver[maxn],head[maxn],edge[maxn],Next[maxn],tot,d[maxn];//d[i]表示从1到i至少需要多少个整数 
int n;
queue<int>q;
bool v[maxn+5]; 
void add(int x,int y,int z){
    ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void SPFA(){
    memset(d,-1,sizeof(d));
    memset(v,0,sizeof(v));
    d[0]=0;v[0]=1;
    q.push(0);
    while(q.size()){
        int x=q.front();
        q.pop();
        v[x]=0;
        for(int i=head[x];i;i=Next[i]){
            int y,z;
            y=ver[i];
            z=edge[i];
            if(d[y]<d[x]+z){
                d[y]=d[x]+z;
                if(!v[y])	q.push(y),v[y]=1;
            }
        }
    }
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        tot=0;
        int mn=-1000; 
        memset(ver,0,sizeof(ver));
        memset(head,0,sizeof(head));
        memset(Next,0,sizeof(Next));
        memset(edge,0,sizeof(edge));
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            int a=0,b=0,c=0;
            scanf("%d%d%d",&a,&b,&c);
            add(a,b+1,c);
            mn=max(mn,b);
        }
        for(int i=1;i<=mn+1;i++){
            add(i-1,i,0);
            add(i,i-1,-1);
        }
        SPFA();
        printf("%d\n",d[mn+1]); 
        if(t)	printf("\n");
    }

    return 0;
}
```
# 注意
```cpp

除最后一组测试数据外只需输出一个空行外，其余都要输出两个空行

```

能否求一波赞~~~~~

---

## 作者：精益 (赞：16)

看到题解里没有贪心的做法，不会差分约束的蒟蒻来补一波
## 一道典型的贪心求区间选点问题 ##
### 类似于[P1250 种树](https://www.luogu.org/problemnew/show/P1250) ###
选整数尽量少，就要让一个整数给多个区间使用，就尽量让整数选在区间重叠的位置上，而重叠的部分一定在区间尾部。因此先按所有区间的尾部排序，再依次处理每一个区间，对于第$i$个区间，处理已经选择的整数的个数，并在其尾部选择剩余的整数。

### 对于第$i$个区间，如果从前到后扫描已选整数的个数，会TLE

### 所以使用树状数组计算已选整数的个数（树状数组不解释）

```cpp
k=sum(t[i].b)-sum(t[i].a-1);
```
然后从尾部到头部选择未被选择的整数

注意输出格式

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n,k,ans,c[50017];

struct Node{
	int a,b,c;
}t[50005];

bool cmp(Node a,Node b){
	return a.b<b.b;
}
bool v[50005];

void update(int x){
	for(;x<=50005;x+=x&(-x)){
		c[x]+=1;
	}
}

int sum(int x){
	int res=0;
	for(;x;x-=x&(-x)){
		res+=c[x];
	}
	return res;
}

void deal(){
	scanf("%d",&n);
	memset(v,0,sizeof(v));
	memset(c,0,sizeof(c));
	ans=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&t[i].a,&t[i].b,&t[i].c);
		++t[i].a;
		++t[i].b;
	}
	sort(t+1,t+n+1,cmp);//按尾部排序
	for(int i=1;i<=n;i++){
		k=sum(t[i].b)-sum(t[i].a-1);//树状数组求和计算
		if(k>=t[i].c) continue;
		for(int j=t[i].b;j>=t[i].a;j--){
			if(!v[j]){
				v[j]=1;
				update(j);//树状数组修改
				k++;
				ans++;
				if(k==t[i].c) break;
			}
		}
	}
	printf("%d\n",ans);
}

int main(){
	scanf("%d",&T);
	while(T--){
		deal();
		if(T) printf("\n");
	}
	return 0;
}
```

第一篇题解求过

---

## 作者：Soulist (赞：9)

呐，我们可以转化一下题面：

把某个正整数看作位置，选择这个正整数 即 此位置取 $1$ ，不选表示此位置取 $0$ 

然后就得到了一个 $01$ 串。

所以我们可以考虑维护一个前缀和，限制条件$l-r$至少有 $k$ 个数即：

$$sum_r - sum_[l-1] >= k$$

但是实际上还有一个隐藏的限制条件：

$$sum_{i+1} - sum_i>=0$$

且：

$$sum_{i} - sum_{i+1}>=-1 $$

所以都要连边，然后跑最长路 $QwQ$

```cpp

#include<bits/stdc++.h>
using namespace std;
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int N = 5e5 + 5; 
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
int n, maxn, dis[N], S, book[N], head[N], cnt, minn, vis[N];
struct E {
	int to, next, w;
} e[N * 2];
void init() {
	memset( head, 0, sizeof(head) ), cnt = 0;
}
void add( int x, int y, int z ) {
	e[++ cnt] = (E){ y, head[x], z }, head[x] = cnt;
}
void input() {
	n = read(); int x, y, z; minn = N;
	rep( i, 1, n ) {
		x = read(), y = read(), z = read(); 
		if( x > y ) swap( x, y );
		add( x - 1, y, z );
		maxn = max( maxn, y );
	}
	rep( i, 0, maxn ) add( i, i + 1, 0 ), add( i + 1, i, -1 );
}
queue< int> q;
void spfa( int x ) {
	while( !q.empty() ) q.pop();
	memset( dis, -63, sizeof(dis) ), memset( vis, 0, sizeof(vis) );
	memset( book, 0, sizeof(book) );
	dis[x] = 0, q.push(x);
	while( !q.empty() ) {
		int u = q.front(); q.pop(); 
		book[u] = 0, vis[u] = 1;
		Next( i, u ) {
			int v = e[i].to;
			if( dis[v] < dis[u] + e[i].w ) {
				if( !book[v] ) q.push(v), book[v] = 1;
				dis[v] = dis[u] + e[i].w;
			}
		}
	}
}
signed main()
{
	int T = read();
	while( T-- ) {
		init(), input();
		spfa(S), printf("%d\n", dis[maxn]);
		if(T) puts("");
	}
	return 0;
}
```

---

## 作者：逃离地球 (赞：5)

本蒟蒻最近在复习图论，听机房里的大佬说这道题是一道差分约束裸题，就跑过来做了这道题。

简单介绍一下差分约束系统：**差分约束系统**就是给出n个变量$x_{i}$，在m个形如$x_{i}-x_{j}\le c_{k}$的不等式的约束下，求解所有满足这些不等式的解。

而查分约束系统可以通过图论解决。我们可以把每一个变量看做一个节点，而每个约束条件$x_{i}-x_{j}\le c_{k}$可以视为$j$节点到$i$节点连了一条权值为$c_{k}$的有向边。

在这个图中，节点$i$到节点$j$的最短路为$x_{i}-x_{j}$的最大值，因为对于单源最短路径满足的三角不等式$dis_{u}\le w(u,v)+dis_{v}$，在本图中为$dis_{i}\le c_{k}+dis_{j}$，变形可得$dis_{i}-dis_{j}\le c_{k}$，即节点$i$到节点$j$的最短路为$x_{i}-x_{j}$的最大值。

再看这道题，要在区间[$a_{i}$，$b_{i}$]中至少取任意互不相同的$c_{i}$个整数。我们不妨设p[k]为0到k之间选几个整数。由题意易得，$p[b_{i}]-p[a_{i}]\ge c_{i}$，而题意中又有一些隐藏条件：
1. $p[i]-p[i-1]\ge0$，即$0$到$k$中选出的数肯定大于等于	$0$到$k-1$中选出的数
2. $p[k-1]-p[k]\ge-1$，即每个数至多选一次。

我们还需要建立一个根节点，与所有节点相连且边权为0，这样就可以以根节点为出发点跑一个最短/长路了。

得到这些条件后，就可以建一个图，然后跑一遍从根节点出发的**最长路**（因为要求最小值），再输出$dis[max]$就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int tot=0,dis[500003];
struct node{
    int v,k;
};
vector<node>head[500003];//邻接表 

inline int read(){
    int s=0,g=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            g=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=(s<<3)+(s<<1)+(ch^48);
        ch=getchar();
    }
    return s*g;
}
int max(int a,int b){
    if(a>b)
        return a;
    return b;
}

void spfa(int start){//spfa求最长路
    bool vis[500003];
    queue<int> que;
    que.push(start);
    for(int i=0;i<=tot;i++){
    	dis[i]=-0x7fffffff;
    	vis[i]=false;
    }
    vis[start]=true;
    dis[start]=0;
    
    while(!que.empty()){
        int num=que.front();
        que.pop();
        vis[num]=false;
        for(int i=0;i<head[num].size();i++){
            if(dis[head[num][i].v]<dis[num]+head[num][i].k){
                dis[head[num][i].v]=dis[num]+head[num][i].k;
                if(!vis[head[num][i].v]){
                	que.push(head[num][i].v);
                	vis[head[num][i].v]=true;
                }
            }
        }
    }
}

int main(){
    int n,a,b,c,t;
    node p;
    t=read();
    while(t){
        n=read();
    	for(int i=0;i<=50002;i++){
    		vector<node>().swap(head[i]);
        }//清空向量 
        tot=0;
        
    	for(int i=0;i<n;i++){
            a=read(),b=read(),c=read();
            p.v=b;
            p.k=c;
            head[a-1].push_back(p);
            tot=max(b,tot);
        }//建图 
        
        for(int i=1;i<=tot;i++){
            p.k=-1;
            p.v=i-1;
            head[i].push_back(p);//隐藏条件2 
    
            p.k=0;
            p.v=i;
            head[i-1].push_back(p);//隐藏条件1 
			     
			head[50002].push_back(p);//我设50002号节点为根节点，连上所有节点 
        }
        p.k=0;
        p.v=0;
        head[50002].push_back(p);
        spfa(50002);//spfa不是死了吗 
        printf("%d\n",dis[tot]);
        if(--t)
        	cout<<endl;//注意这里的输出格式，特别坑，我wa了好多次才发现 
    }
    return 0;
}
```


---

## 作者：pikabi (赞：5)

**全网唯一线段树题解！**

（差分约束？溜了溜了）

有一种显然的贪心， 就是**将每一个区间按照右端点升序排序**。那么对于每一段区间的回答，从左往右依次遍历：如果在当前区间内已选的数大于等于需求，我们进行下一个操作；如果小于，那么一定选是靠右边的数，因为这样才会对接下来的策略有最优影响。

统计区间内已选的数很好办，用线段树维护就行了。同时因为它选的是一段连续的靠右序列，刚好可以用线段树进行修改，直接将该目标区间的 $val_p$ 赋为 $r_p - l_p + 1$ 就行了，其中 $val_p$ 、$l_p$ 、 $r_p$ 表示左端为 $l_p$ , 右端为 $r_p$ 的线段树节点 $p$ 含有数的总数为 $val_p$ 。

但是区间缺少的靠右的数未必集中在最右边，不免有右端放了许多数而不得不用选用左端数的情况。这时候我们就二分查找，看从 $mid $ 到最右端缺少的数的数量是否大于等于实际区间缺少数量，不断找到最优策略。

总复杂度为 $O(n \times log^2n)$ ，满足 $n \le 50000$ 的数据范围。

奉上代码 $-->$

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
#define ll long long
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
	int x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

struct node{
	int x, y, z;
	bool operator <(const node &xx)const{
		return xx.y == y ? xx.x > x : xx.y > y;
	}
}b[50005];

int t, n, ans, tot;
int N;

struct Segment_Tree{
	int val, tag, sum;	
}a[1000005];

// 线段树基本操作
inline int ls(int p){
	return p << 1;
}

inline int rs(int p){
	return p << 1 | 1;
}

inline void update(int p){
	a[p].val = a[ls(p)].val + a[rs(p)].val ;
}

inline void push_up(int p, int l, int r){
	a[p].tag ++;
	a[p].val = r - l + 1;
}

inline void push_down(int p, int l, int r){
	if(!a[p].tag ) return ;
	int mid = l + r >> 1;
	push_up(ls(p), l, mid);
	push_up(rs(p), mid + 1, r);
	a[p].tag = 0;
}

inline void build(int p, int l, int r){
	if(l == r){
		a[p].tag = a[p].val = 0;
		return ;
	}
	int mid = l + r >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	a[p].tag = a[p].val = 0;
}

inline void modify(int p, int l, int r, int L, int R){
	if(L <= l && r <= R){
		a[p].val = r - l + 1;
		a[p].tag = 1;
		return ;
	}
	push_down(p, l, r);
	int mid = l + r >> 1;
	if(L <= mid) modify(ls(p), l, mid, L, R);
	if(mid < R) modify(rs(p), mid + 1, r, L, R);
	update(p);
}

inline int query(int p, int l, int r, int L, int R){
	if(L <= l && r <= R){
		return a[p].val ;
	}
	push_down(p, l, r);
	int mid = l + r >> 1, res = 0;
	if(L <= mid) res += query(ls(p), l, mid, L, R);
	if(mid < R) res += query(rs(p), mid + 1, r, L, R);
	update(p);
	return res;
}

int main(){
	t = read();
	while(t--){
		n = read();
		N = 0;
		ans = 0;
		for(int i = 1; i <= n; i++){
			b[i].x = read() + 1, b[i].y = read() + 1, b[i].z = read(); 
			N = max(N, b[i].y );
		}
		sort(b + 1, b + n + 1);
		build(1, 1, N);//重建树以清零
		for(int i = 1; i <= n; i++){
			int w = query(1, 1, N, b[i].x, b[i].y );
			if(w >= b[i].z ) continue;
			ans += b[i].z - w;
			int l = b[i].x , r = b[i].y , ok = b[i].x , delta = b[i].z - w;
			while(l <= r){//二分查找
				int mid = l + r >> 1;
				w = b[i].y - mid + 1 - query(1, 1, N, mid, b[i].y);
				if(w >= delta ){
					ok = mid;
					l = mid + 1;
				}
				else {
					r = mid - 1;
				}
			}
			modify(1, 1, N, ok, b[i].y);
		}
		if(t)//注意UVA题目的输出格式
		printf("%d\n\n",ans);
		else printf("%d\n",ans);
	}
}

```

完结撒花✿✿ヽ(°▽°)ノ✿


---

## 作者：SpeMars (赞：3)

**luogu主题库和SPOJ都有有一道题，代码思路基本一样**

## 双时空传送门

[P1250种树](https://www.luogu.com.cn/problem/P1250)

[SPOJ](https://www.luogu.com.cn/problem/SP116)

这道题有两种做法：

贪心和差分约束系统

本题解就不展开贪心的做法了~~其实就是懒~~

那么我们一起来康康差分约束系统怎么AC呢

# 差分约束系统

~~顾名思义，差分约束系统就是约束差分的系统~~

总的来讲，差分约束系统就是用于去解对于一些不等式组的解的方法(解不唯一)

形如:

## $\begin{cases}x_{a_1}-x_{b_1}\le c_{i_1} \\x_{a_2}-x_{b_2}\le c_{i_2} \\x_{a_3}-x_{b_3}\le c_{i_3} \\...\\ x_{a_q}-x_{b_q}\le c_{i_q} \\\end{cases}$

的一组不等式组($a_1$到$a_q$,$b_1$到$b_q$,$c_1$到$c_q$都有可能相同)

所以才能互相约束

题目一般求解 $x_i$ の最小非负整数整数解

那么这种不等式组怎么求解呢，又如何判断无解呢？

其实我们可以将数论与图论相结合

刚刚的式子经过变形可以变为

## $\begin{cases}x_{a_1}\le c_{i_1}+x_{b_1} \\x_{a_2}\le c_{i_2}+x_{b_2} \\x_{a_3}\le c_{i_3}+x_{b_3} \\...\\ x_{a_q}\le c_{i_q}+x_{b_q} \\\end{cases}$

那么结合这张图我们康康有什么特点:

![](https://cdn.luogu.com.cn/upload/image_hosting/6ioozei8.png?x-oss-process=image/resize,m_lfit,h_550,w_550)

$0$ 到第 $i$ 个点的最短路记为 $d_n$

设 $other$ 为除了 $0 , 1 , 2$ 这三个点的点

那么很明显 $d_2 \le d_1+c$

因为 $d_2$ 的松弛要么由点 $1$ 来松弛要么由其他点松弛过来所以 $d_2 \le d_1+c$

那么我们就可以从 $b_i$ 建一条单向边至 $a_i$

为了使得图是联通的我们创建一个虚拟点 $0$ 连接所有点

也就是说把所有这样的边建完后就会得到一个连通图。

我们就在这个图里跑最短路，那么所有的 $d_i$ 的值都符合这些约束条件
 
也就是说 $x_{a_i}$ 的一个解就是 $d_{a_i}$

最后由于这个图会存在负权边，所以我们要用 SPFA 来跑

~~SPFA尚存~~

所以说 $d_{a_i}$ 也可能会是负的，所以我们找到最小的 $d_i$ 记为 $s$ ,让每个 $d_i$ 都加上 $s$

这样不等式组仍然成立，因为他们同时加了某个数，这也挺好理解

这样最小非负整数解就求出来了。

那么无解的情况该怎么判呢?

其实 SPFA 里的判负权环就已经得到答案了，也就是说条件自相矛盾

SPFA 没学过的可以先去别的神犇的博客里学学，也是比较简单。

## 回到这道题

既然基本理论我们学完了，这道题如何用差分约束系统来解决呢？

在 $a_i$ 至 $b_i$ 之间选择 $c_i$ 个数相当于在这个区间内包含至少 $c_i$ 个数

我们假设从 $1$ 至 $i$ 选择了 $s_i$ 个不同的数,

那么从 $a_i$ 至 $b_i$ 之间选择了 $s_{b_i}-s_{a_{i-1}}$ 个不同的数

假设 $maxn$ 为条件里最大的 $b_i$ 也就是说有多少个 $x_i$ 

那么 $s_{maxn}$ 的最小正整数解就为答案

由题意得

$s_{b_i}-s_{a_{i-1}} \ge c$

$s_{a_{i-1}}-s_{b_i} \le -c$

$s_{a_{i-1}} \le s_{b_i}-c$

还有隐含条件一个数只能选一次所以

$s_{i-1} \le s_{i}$

$s_{i-1} \le s_{i}+0$

也就是说除了原来的条件，我们还要保证隐含条件的合法性

也就是说对于每个 $i$ ($1 \le i \le maxn$)都要建一条 $i$ 到 $i-1$ 的权值为   $0$ 的单向边

对于每个条件我们可以建由 $b_i$ 到 $a_{i-1}$ 的权值为 $-c$ 的单向边

假如图不连通(其实是联通的)我们可以创建 $1$ 个点 $maxn+1$ ,联通 $0$ 到  $maxn$ 的所有点

但是 $s_0$ 是要用到的，所以我们要用一些其他点来代替 $0$ 

这样解法也就不言而喻了。

 AC 代码:(~~有些比较臭的东西是防伪代码，请自动屏蔽~~)

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
#if 1
const int N=5e4+2;
struct node{
	int v,w;
};
int t,n,m,u,v,w,d[N],ti[N],minn=0x7fffffff;
bool vis[N];
queue<int> q;
vector<node> g[N];
void read(int &s){
	s=0;
	bool o=false;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar())if(ch=='-')o=true;
	for(;isdigit(ch);ch=getchar())s=(s<<1)+(s<<3)+(ch^48);
	if(o)s=-s;
	return;
}
int main(){
	for(;114514==1919810;)puts("包卷裹卷法");
	read(t);
	for(int j=1;j<=t;++j){
		minn=0x7fffffff,n=-1;
		memset(vis,false,sizeof(vis));
		memset(ti,0,sizeof(ti));
		memset(d,0x7f,sizeof(d));
		read(m);
		for(int i=1;i<=m;++i){
			read(u),read(v),read(w);
			g[v].push_back((node){u-1,-w});
			n=max(n,v);
		}
		for(int i=1;i<=n;++i){
			g[i-1].push_back((node){i,1}); 
			g[i].push_back((node){i-1,0});
			g[n+1].push_back((node){i,0}); 
		}
		g[n+1].push_back((node){0,0});
		for(;q.size();q.pop());
		vis[n+1]=true,q.push(n+1),d[n+1]=0;
		for(;q.size();){
			u=q.front();
			q.pop();
			vis[u]=false;
			for(int i=0;i<g[u].size();++i){
				v=g[u][i].v,w=g[u][i].w;
				if(d[u]+w<d[v]){
					d[v]=d[u]+w;
					if(!vis[v]){
						++ti[v];
						if(ti[v]==n+1){
							puts("出大问题!!!");
							return 0;
						}
						q.push(v),vis[v]=true;
					}
				}
			}
		}
		for(int i=0;i<=n+1;++i)g[i].clear(); 
		for(int i=0;i<=n+1;++i)minn=min(minn,d[i]);
		if(minn<0)d[n]-=minn;
		printf("%d\n",d[n]);//毒瘤换行
		if(j!=t)puts("");
	} 
	return 0;
	for(;114514==1919810;)puts("bp裹卷法");
}
#endif
//介是嘛呀 
```
这换行要求真的是严格除了最后一个数据前面都是两个换行

最后一个数据只有一个换行

但是别忘记了 3 倍 AC 的欢乐！

---

## 作者：fanfansann (赞：3)

本题的题意就是从$0$ ~ $50000$中选出尽量少的整数，使得每一个区间$[a_i,b_i]$内都至少有$c_i$个整数

那么我们设$s[k]$表示的是$0$ ~ $k$之间最少选取多少个整数，则根据题意，有$s[b_i]-s[a_i - 1]\geq c_i$

另外由于我们要求的是求最值，因此仅有这一个相对关系式是无法求得最值的。根据经验我们可以考虑$s_i$和$s_{i-1}$之间的关系。
很明显$s_i\geq s_{i-1}$既是$s_i-s_{i-1} \geq 0$
以及$s_i-s_{i-1} ≤ 1$（每一个数只能选一次），由于我们求的是最小值->下界最大->最长路，因此我们应该把符号全部换成$\geq$，所以上式可以变形为$s_{i-1}-s_i \geq -1$

$$ \left\{
\begin{aligned}
\ \ \ \ \ \ \ \ \ \ s[b_i]-s[a_i - 1]\geq c_i \\s[i]-s[i - 1] \geq 0 \\
\ \ \ \ \ s[ i - 1 ] - s[i] \geq -1\\
\end{aligned}
\right.
$$


我们需要找到一个源点，满足该源点可以到达所有的边，易证可以以 $0$ 为源点，建图：
$s[ i - 1 ] - s[i] \geq -1$从所有的 $i-1$ 到 $i$ 连权值为 $0$ 的有向边、
$s[ i - 1 ] - s[i] \geq -1$ 从所有的i到i-1连权值为-1的有向边、
$s[b_i]-s[a_i - 1]\geq c_i$从每一个$a_i- 1$到$b_i$连权值为$c_i$的有向边。
由于a和b的数据范围为$0$ ~ $50000$，而我们的源点为0，因此我们输入的时候将a和b都++，将数据范围改成$1$ ~ $50001$。再以0为源点跑一个最长路即可。

由于本题保证$c_i≤b_i -a_i+1$，所以图中是没有正环的，差分约束系统一定有解。我们输入a和b的时候求一下b的最大值`maxx`，最后求完最长路以后答案就是$dist[maxx]$（$dist[maxx]$是所有下界的最大值）

这latex公式快给我写吐了，看懂了就麻烦点个赞吧 ψ(｀∇´)ψ


**代码如下：**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstring>

using namespace std;
typedef long long ll;

const int N = 5e5 + 7, M = 5e6 + 7,INF = 0x3f3f3f3f;

void read(int &x)
{
     int f=1;x=0;char s=getchar();
     while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
     while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
     x*=f;
}

int n,m;
int ver[M],nex[M],edge[M],head[N],tot = 1;
int dist[N];
bool vis[N];
int q[N];

void add(int x,int y,int z){
    ver[ ++ tot] = y;
    edge[tot] = z;
    nex[tot] = head[x];
    head[x] = tot;
}

void spfa(){
    memset(dist,0xcf,sizeof dist);
    dist[0] = 0;
    vis[0] = true;

    int hh = 0,tt = 0;
    q[tt ++ ] = 0;

    while(hh != tt){
        int x = q[hh ++ ];
        if(hh == N)hh = 0;
        vis[x] = false;

        for(int i = head[x];i;i = nex[i]){
            int y = ver[i],z = edge[i];
            if(dist[y] < dist[x] + z){
                dist[y] = dist[x] + z;
                if(!vis[y]){
                    q[tt ++ ] = y;
                    if(tt == N)tt = 0;
                    vis[y] = true;
                }
            }
        }
    }
}
int t;
int maxx;
int main(){
    read(t);
    while(t -- ){
        memset(head,0,sizeof head);
        tot = 1;
        read(n);

        for(int i = 1;i <= n;++i){
            int a,b,c;
            read(a),read(b),read(c);
            a ++ ,b ++ ;
            add(a - 1,b,c);
            maxx = max(maxx,b);
        }
        for(int i = 1;i <= maxx;++i){
            add(i - 1,i,0);
            add(i,i - 1,-1);
        }
        spfa();

        printf("%d\n",dist[maxx]);

        if(t)puts("");//艹
    }

    return 0;
}

```


---

## 作者：MeowScore (赞：2)

## 题目

好像没啥好说的。挂链接：[UVA1723 Intervals](https://www.luogu.com.cn/problem/UVA1723)

------------

## 解决问题

是一道差分约束系统的好题。如果你对差分约束系统还不够熟悉，建议自行学习。推荐一下这位神犇的博客：[差分约束系统](https://blog.csdn.net/consciousman/article/details/53812818?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162726107316780274124871%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162726107316780274124871&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-53812818.first_rank_v2_pc_rank_v29&utm_term=%E5%B7%AE%E5%88%86%E7%BA%A6%E6%9D%9F&spm=1018.2226.3001.4187)。

我们要从题中找到不等关系。方便表示，我们设 $dis_{i}$ 为从区间 $[0,i]$ 里最少选数字的数量。很显然，从区间 $[a,b]$ 里选 $c$ 个数，就意味着 $dis_{b}- dis_{a-1}\ge c$. 根据差分约束系统的芝士，我们从点 $a-1$ 向点 $b$ 连权值为c的边。跑最长路即可。这里 $dis_{i}$ 的含义既指从区间 $[0,i]$ 里最少选数字的数量，又指我们建立的图中源点到点 $i$ 的最长路。

当然不止这样。因为我们这样建边，没有注意隐性的限制：

$$dis_{a-1}+1\ge dis_{a}\ge dis_{a-1}$$

把式子化成我们想要的形式：

$$dis_{a-1}-dis_{a}\ge -1$$

$$dis_{a}-dis_{a-1}\ge 0$$

再从点 $a$ 向点 $a-1$ 连权值为 $-1$ 的边,从点 $a-1$ 向点 $a$ 连权值为 $0$ 的边。

接下来考虑源点。如果直接从点 $0$ 开始跑，$dis_{0}$ 的取值难以确定。我的做法是把所有区间整体右移一个单位长度，这样题目中区间端点的数据范围就不包括 $0$ 了。这样一来 $dis_{i}$ 就代表从区间 $[1,i]$ 里最少选数字的数量。令点 $0$ 为虚拟源点，显然 $dis_{0}$ 就代表从区间 $[1,0]$ 里最少选数字的数量，该区间不合法， $dis_{0}=0$.

至于从虚拟源点向其他点连边，上面提到的那个“从点 $a$ 向点 $a-1$ 连权值为 $-1$ 的边,从点 $a-1$ 向点 $a$ 连权值为 $0$ 的边”，跑个循环顺便都解决了（珂以推一下式子验证正确性）。

然后跑最长路，珂以边权取反再跑SPFA最短路，也珂以把SPFA改装成最长路。

------------

## ~~说句闲话~~
~~关于SPFA，它复活了~~


------------


## 上代码
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ss=0,ww=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			ww=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ss=ss*10+ch-'0';
		ch=getchar();
	}
	return ss*ww;
}
int head[200010];
int to[200010];
int nex[200010];
long long len[200010];//边权 
int cnt;
long long dis[200010];//最长路 
inline void add(int x,int y,int d){
	cnt++;
	to[cnt]=y;
	nex[cnt]=head[x];
	len[cnt]=d;
	head[x]=cnt;
}
bool vis[200010];
int main(){
	int T;
	T=read();
	int n;
	int a,b,c;
	for(register int i=1;i<=T;i++){
		n=read();
		cnt=0;
		memset(head,0,sizeof(head));
		int maxn=-1;//记录区间上界 
		for(register int j=1;j<=n;j++){
			a=read();
			b=read();
			c=read();
			a++;//这样相当于把区间整体向右移动 
			b++;
			add(a-1,b,c);
			maxn=max(maxn,b);
		}
		for(register int j=1;j<=maxn;j++)
			dis[j]=-99999999999;
		for(register int j=1;j<=maxn;j++)
			vis[j]=0;
		for(register int j=1;j<=maxn;j++){
			add(j-1,j,0);
			add(j,j-1,-1);
		}
		queue<int> q;
		q.push(0);
		vis[0]=1;
		dis[0]=0;
		while(!q.empty()){
			int nw=q.front();
			q.pop();
			vis[nw]=0;
			for(register int j=head[nw];j;j=nex[j]){
				if(dis[nw]+len[j]>dis[to[j]]){//跟最短路相比，改了个符号 
					dis[to[j]]=dis[nw]+len[j];
					if(!vis[to[j]]){
						vis[to[j]]=1;
						q.push(to[j]);
					}
				}
			}
		}
		cout<<dis[maxn]<<endl;
		if(i!=T)
			cout<<endl;
	}
	return 0;
}
```

---

## 作者：_Diu_ (赞：2)

题目传送门：[UVA1723 Intervals](https://www.luogu.com.cn/problem/UVA1723)

双倍经验：[SP116 INTERVAL - Intervals](https://www.luogu.com.cn/problem/SP116)

三倍经验：[P1250 种树](https://www.luogu.com.cn/problem/P1250)

## 差分约束系统

## 建图

这一题的关键是建图

我们可以把对应前缀和的值映射到一张图上的每一个点

$d_i$表示在$[1,i]$中选了多少个数

那么对于每一对$(a,b,c)$，则有不等式$d_b-d_{a-1}>=c$

不等号两边同乘$-1$：$d_{a-1}-d_b<=-c$

利用这个不等式建图

还有隐含条件每一个数只有两个状态

即选或不选

则有不等式$0<=d_i-d_{i-1}<=1$

分解出两个不等式

$\begin{cases}d_{i-1}-d_i\le0\\d_i-d_{i-1}\le1\end{cases}$

建完图后以节点最大的$b$为起点跑$spfa$

$-d_0$就是答案了

## $code$

上代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
using namespace std;
const int N=50010;
int n,m,u,v,w,d[N],cnt[N],mx,ans;
bool vis[N];
queue<int> q;
struct cxk{
    int v,w;
};
vector<cxk> g[N];
int read(){//超级慢读 
    int x;
    scanf("%lld",&x);
    return x;
}
bool spfa(int s){
    memset(vis,0,sizeof(vis));
    memset(d,127,sizeof(d));
    memset(cnt,0,sizeof(cnt));
    d[s]=0;
    q.push(s);
    vis[s]=1;
    cnt[s]++;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=0;i<g[u].size();i++){
            int v=g[u][i].v;
            int w=g[u][i].w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                if(!vis[v]){
                    q.push(v);
                    vis[v]=1,cnt[v]++;
                    if(cnt[v]==n)return 0;
                }
            }
              
        }
    }
    return 1;
}
void work(int t){
    m=read();
    for(int i=1;i<N;i++)g[i].clear();
    int mx=0;
    while(m--){
        u=read(),v=read(),w=read();
        mx=max(mx,v);
        g[v].push_back({u-1,-w});
    }
    for(int i=1;i<=mx;i++)g[i].push_back({i-1,0}),g[i-1].push_back({i,1});
    spfa(mx);
    printf("%lld\n",-d[0]);
    if(t)puts("");
}
signed main(){
	while(1+1!=2)printf("昔时稀世西世西市惜时西施吸食稀世西世西市惜时西施稀释稀屎\n");//防伪标志 
	int t;
	scanf("%lld",&t);
	while(t--)work(t);
	while(1+1!=2)printf("昔时稀世西世西市惜时西施吸食稀世西世西市惜时西施稀释稀屎\n");
}
```

### ~~个人有一些奇怪的癖好不要介意哈~~

---

## 作者：南苑沁青 (赞：2)

###### 听大佬说这题也可以用贪心求解，可惜我太菜了，写不出贪心，只会用差分约束。
##### 本题对我来说还是比较棘手的，初读试题总觉得无从下手，本题的n很大，搜索显然是不行的。考虑用高效的算法：动态规划，对于状态又无法分析，很难找到一个拓扑序列，写一个合适的方程。
##### 因为题目要求是有n个区间，在区间[ai，bi]中至少取任意互不相同的ci个整数。求在满足n个区间的情况下，至少要取多少个正整数。这个时候就可以与差分约束联系起来，思路如下：
- 可以设一个数组s[k]表示0~k之间最少选出多少个整数。根据题意，有s[ bi ] - s[ ai - 1 ] ≥ ci 。这很显然是一个差分约束的模型。
- 不过还要增加一些隐含的条件才能保证求出解是有意义的：
	① s[ k ] - s[ k - 1] ≥ 0 。（因为0~k之间选出的数肯定不比 0~k-1少）。
    
    ② s[ k ] - s[ k - 1] ≤ 1 。 （每个数只能被选一次，可变形为 s[ k - 1] - s[ k ] ≥ -1 。）
- 看到这里，就很自然的想到了最短路。（三角形迭代更新）
- 因此，可以把 - 1 ~ 50000 这 50002 个整数分别作为图中的结点，从每个k-1到k连成长度为 0 的有向边，从每个 ai - 1 到 bi 连成长度为 ci 的有向边。
- 构图完成后，最后令 s[ - 1] = 0，以 - 1 为起点求单源最短路。因为题目保证 ci ≤ bi -ai -1，所以图中一定没有正环，差分约束一定有解。求完最长路后，s[ 50000 ] = dist[ 50000 ]就是本题的结果。

### AC代码如下
```cpp
#include<cstdio>
#include<cstring>
#include<stack>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define iNF 0x3f3f3f3f
#define N 50017
#define M 50017
int n,m,k;
int Edgehead[N],dis[N];
struct Edge
{
	int v,w,nex;
}Edge[3*M];
bool vis[N];
int minn,maxx;
int MIN(int a,int b)
{
	if(a<b) return a;
	return b;
}
int MAX(int a,int b)
{
	if(a>b) return a;
	return b;
}//手打的比较函数会比c++库的快
void Addedge(int u,int v,int w)
{
	Edge[k].nex=Edgehead[u];
	Edge[k].w=w;
	Edge[k].v=v;
	Edgehead[u]=k++;
}
int SPFA(int start)//spfa求最短路
{
	queue<int>q;
	int top;
	for(int i=minn;i<=maxx;i++)
		dis[i]=-iNF;
	dis[start]=0;
	memset(vis,false,sizeof(vis));
	q.push(start);
	vis[start]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=false;
		for(int i=Edgehead[u];i!=-1;i=Edge[i].nex)
		{
			int v=Edge[i].v;
			int w=Edge[i].w;
			if(dis[v]<dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(!vis[v])
				{
					q.push(v);
					vis[v]=true;
				}
			}
		}
	}
	return dis[maxx];
}
int main()
{
	//freopen("Intervals.in","r",stdin);
	//freopen("Intervals.out","w",stdout);
	int u,v,w,t;
	scanf("%d",&t);
	//for(int i=1;i<=t;i++)
	while(t--)
	{
		scanf("%d",&n);//n为目的地
		k=1;
		memset(Edgehead,-1,sizeof(Edgehead));
		memset(Edge,0,sizeof(Edge));
		minn=iNF;
		maxx=-1;
		for(int i=1;i<=n;i++)
		{	
			scanf("%d%d%d",&u,&v,&w);
			Addedge(u-1,v,w);
			maxx=MAX(v,maxx);
			minn=MIN(u-1,minn);
		}	
		for(int i=minn;i<=maxx;i++)
		{//新边，保证图的连通性还必须添加相邻两个整数点 i, i+1的边
			Addedge(i,i+1,0);
			Addedge(i+1,i,-1);
		}
		int ans=SPFA(minn);//从点minn开始寻找最短路
		printf("%d\n",ans);
		if(t)
		printf("\n");
	}
return 0;
}
```
##### 题解求过 Orz

---

## 作者：无咕_ (赞：0)

## 题解索引
1. **题目大意**
2. **Solution**
3. **AC code**
4. **类似题型**

代码类型： C++（cpp）

是否吸氧：否

不压行代码长度：59

------------

## 题目大意
题面： [<传送门>](https://www.luogu.com.cn/problem/UVA1723)

题意：选数。给出 $n$ 个条件，每次给出 $a_i$ 、 $b_i$ 、 $c_i$ ，表示整数区间 $[a_i,b_i]$ 中至少选 $c_i$ 个数。求满足 $n$ 个条件时，最少需选的区间数。

~~术语理解： [差分约束](https://www.luogu.com.cn/blog/wugu-2333/ci-fen-yue-shu-ji-tong) 加强题。~~

## Solution

本题并不难，主要在于思路的转化。

我们要使 $[a_i,b_i]$ 的区间里选 $c_i$ 个数，要使满足 $n$ 个条件时选的数最少，那就需要有一些数被多个条件选上。而题目让我们求的并不是哪些数被选，而是被选数的总数。

我们可以这样想：

1. 设区间最左端点为 $x$ 。

2. 将问题转化：设 $[x,a_i-1]$ 区间内选了 $w_i$ 个数，设 $[x,b_i]$ 区间内选了 $w_i+c_i$ （因为区间 $[a_i,b_i]$ 之间要求选 $c_i$ 个数）。

3. 转化为差分约束：区间 $[x,b_i]$ 比区间 $[x,a_i-1]$ 多选了 $c_i$ 个数，即：

------------

设 $e_i$ 表示区间 $[x,i]$ （ $x$ 为总选数区间左端点）选的数的总数。

$$e_{b_i}-e_{a_i-1}=c_i$$

即为：

$$e_{b_i}-e_{a_i-1}\le c_i$$

------------

那么我们就可以按照差分约束的形式来做了，不过有几个注意事项：

1. 题目中说过： $0\le a_i\le b_i\le 50000$ 所以，我们如果建边时选择用 $a_i-1$ 当左端点会出界，所以我们选择将整个区间都右移一格，即 $a_i$ 和 $b_i$ 都 $+1$ 。

2. 由于区间之间可能不连通，所以我们要建立虚拟源点（超级源点），连**所有可能放数字**的区间，权值为 $0$ 。

3. 题目多组数据，记得清数组。

4. 题目要求非最后一组数据时输出要额外带个空行，所以要在循环时判断一下。

## AC code

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<queue> 
#include<cstring>
using namespace std;
const int MAXN=1e6+9;
struct Edge{
    int nxt,to,w;
}edge[MAXN];
int t,n;
int maxn=-1,dis[MAXN];
bool vis[MAXN];
int num_edge=0,head[MAXN];
void add_edge(int from,int to,int w){
    edge[++num_edge]=(Edge){head[from],to,w};
    head[from]=num_edge;
}void spfa(int s){
    queue<int>q;
    q.push(s);
    dis[s]=0;
    vis[s]=1;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        vis[x]=0;
        for(int i=head[x];i;i=edge[i].nxt){
            int to=edge[i].to;
            if(dis[to]<dis[x]+edge[i].w){
                dis[to]=dis[x]+edge[i].w;
                if(!vis[to])q.push(to),vis[to]=1;
            }
        }
    }
}
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        num_edge=0;
        maxn=-1;
        memset(head,0,sizeof(head));
        for(int i=1;i<=n;i++){
            int a,b,c;
            scanf("%d %d %d",&a,&b,&c);
            add_edge(a,b+1,c);
            maxn=max(maxn,b+1);
        }memset(dis,-1,sizeof(dis));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=maxn;i++)dis[i]=-2147483647,vis[i]=0;
        for(int i=1;i<=maxn;i++){
            add_edge(i,i-1,-1);
            add_edge(i-1,i,0);
        }spfa(0);
        printf("%d\n",dis[maxn]);
        if(t)printf("\n");
    }
    return 0;
}
```

AC记录[<传送门>](https://www.luogu.com.cn/record/54730476)

## 类似题型

[P3275 [SCOI2011]糖果](https://www.luogu.com.cn/problem/P3275)

（差分约束）



---

## 作者：Zxsoul (赞：0)

## 差分约束 板子

### 题面

>从给定范围内选出尽量少的整数，使每个区间$[a_i,b_i]$内都有至少 $c_i$ 个数被选出

### 思路

既然这是一道差分约束题，那么就需要找出**不等关系**

题目中的 $x_i$ 作为未知量，将其表示出来就好了，

我们将每个 $x_i$ 用 $s[i]$ 表示 0~i 中最少选的数

那么为了满足条件，我们有 $s[b_i]-s[a_i - 1] >= c_i$

系统已找出，因为是最少，所以跑 **最长路**，值得高兴地是他**没卡**

### 实现方式

上述式子只是大体，不好表示，因此我们发现一些隐含的条件，即
$$
s[i] - s[i - 1] >= 0
$$

$$
s[i] - s[k - 1] <= 1
$$
有了这样的式子，建图就可以充分了，题解完毕

### 注意
数据卡换行！！！！
### Code
```c
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}
struct node{
  int v, nxt, w;
} e[B];
int vis[B], dis[B];
int head[B], cnt, n, m, minx = inf, manx = -inf;
void add(int u, int v, int w){
  e[++cnt].nxt = head[u];
  e[cnt].v = v;
  e[cnt].w = w;
  head[u] = cnt;
}
void spfa(int s){
  memset(vis, 0, sizeof(vis));
  memset(dis, -inf, sizeof(dis));
  queue<int> q;
  dis[s] = 0, vis[s] = 1, q.push(s);
  while(!q.empty()){
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt){
      int v = e[i].v, w = e[i].w;
      if(dis[v] < dis[u] + w)
      {
        dis[v] =dis[u] + w;
        if(!vis[v]){
          vis[v] = 1;
          q.push(v);
        }
      }
    }
  }
}
int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
  m = read();
  while(m--){
    memset(head, 0, sizeof(head));
    minx = inf;
    manx = -inf;
    cnt = 0;
  n = read();
  for(int i = 1; i <= n; i++){
    int a, b, c;
    cin >> a >> b >> c;
    add(a - 1, b, c);
    minx = min(minx, a - 1);
    manx = max(manx, b);
  }
  for(int i = minx; i <= manx; i++){
    add(i, i + 1, 0);
    add(i + 1, i, -1);
  }
  spfa(minx);
  cout << dis[manx] << endl;
  if(m) printf("\n");
}
  fclose(stdin);
  fclose(stdout);
  return 0;
}



```

---

## 作者：Suzt_ilymtics (赞：0)

## 写在前面

比较裸的差分约束，题面与[P1250种树](https://www.luogu.com.cn/problem/P1250)类似

## Solution


设 $sum[i]$ 表示 $0 \sim i$ 中共选了 $sum[i]$ 个数，$c_i$ 表示第 $i$ 个区间需要 $c_i$ 个数。
根据题目给我们的闭区间 $[a_i,b_i]$ 的要求，不难得到么一个约束条件

$$sum[b_i]-sum[a_{i-1}]>=c_i$$

发现选数时，一个数只能被选一次，我们又可以得到一个约束条件

$$0 \le sum[i + 1] - sum[i] \le 1$$

把它们转化成我们求最短路时的松弛操作的样式

$$sum[a_{i - 1}] \ge sum[b_i] - c_i$$

$$sum[i + 1] \ge sum[i] - 0$$

$$sum[i] \ge sum[i + 1] + 1$$

然后建图跑最短路即可

可以记录所有区间的左端点最小值 $minn$ 和所有区间的右端点最大值 $maxm$ ，那么答案就是从 $minn$ 开始跑，到 $maxm$ 的最短路


## Code

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define LL long long
#define orz cout<<"lkp Ak IOI"<<endl;

using namespace std;
const int MAXN = 5e4+100;
const int INF = 0x3f3f3f3f;
const int mod = 1;

struct edge{
	int to, w, nxt;
}e[MAXN << 2];
int head[MAXN], num_edge = 0;

int n, minn = INF, maxm = -1;
int dis[MAXN];
bool vis[MAXN];
queue<int> q;

int read(){
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') w = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
	return s * w;
}

void add_edge(int from, int to, int w){	e[++num_edge] = (edge){to, w, head[from]}, head[from] = num_edge; }

int SPFA(int st){
	for(int i = minn; i <= maxm; ++i) dis[i] = INF;
	q.push(st);
	vis[st] = true;
	dis[st] = 0;
	while(!q.empty()){
		int t = q.front(); q.pop();
		vis[t] = false;
		for(int i = head[t]; i; i = e[i].nxt){
			int v = e[i].to;
//			cout<<v<<" "<<dis[v]<<endl;
			if(dis[v] > dis[t] + e[i].w){
				dis[v] = dis[t] + e[i].w;
				if(!vis[v]) q.push(v), vis[v] = true;
			}
		}
	}
	return -dis[maxm];
}

int main()
{
	n = read();
	for(int i = 1, u, v, w; i <= n; ++i){
		u = read(), v = read(), w = read();
		add_edge(u - 1, v, -w);//根据我们推出来的约束条件加边即可
		maxm = max(v, maxm);
		minn = min(u - 1, minn);
	}
	for(int i = minn; i <= maxm; ++i) add_edge(i, i + 1, -0), add_edge(i + 1, i, 1);
	printf("%d", SPFA(minn));
	return 0;
}
```

---

## 作者：珈乐唯毒 (赞：0)

## 本题是差分约束板子题

### 双倍经验 
[SP116 INTERVAL - Intervals](https://www.luogu.com.cn/problem/SP116)

一直过不了的朋友们可以先A这道题，本题格式有点恶心。
## 题目分析
~~见题目描述~~

对于这种问题，我们可以把它抽象一下。

令dis[i]表示第0个节点到第i个节点总共放了多少个数。

那么题目的要求就可以转化为 dis[b]-dis[a-1]>=c

移项后为 dis[b]>=dis[a-1]+c 和最长路的更新方法一致。

因此我们可以根据这些不等式建图。然后在图上跑最长路即可。

同时也要注意题目的特殊性。为保证在区间内放数，我们还必须满足以下不等式

dis[i]>=dis[i-1]

dis[i]<=dis[i-1]+1

建边的时候一定要加上这两个不等式。
### 注
差分约束问题同样也可以使用最短路，基本思路一致，将题目信息抽象为三角不等式后建边。

**但本题不行**
在差分约束问题中，最短路一般用于求最大值，最长路一般用于求最小值。这是一个很重要的小结论。

同时注意本题格式，除最后一组数据输出一个空行以为，每一组数据后输出两个空行

~~uva特色，奇怪的格式，感人的测试速度~~
## 代码
~~应该不会有多少人看前面的内容吧~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
struct Edge{
	int next,to,val;
}edge[N<<2];
int head[N],en;
void add(int u,int v,int w){
	edge[++en].next=head[u];
	head[u]=en;
	edge[en].to=v;
	edge[en].val=w;
}
int n,t,dis[N],m;
queue<int> q;
bool vis[N]; 
int main(){
	cin>>t;
	while(t--){
		scanf("%d",&n);
		en=0;
		m=0;
		memset(head,0,sizeof(head));
		memset(dis,-1,sizeof(dis));
		for(int i=1;i<=n;i++){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			a++;
			b++;
			add(a-1,b,c);
			m=max(b,m);
		}
		for(int i=1;i<=m;i++){
			add(i-1,i,0);
			add(i,i-1,-1);
		}
		dis[0]=0;
		q.push(0);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			vis[u]=0;
			for(int i=head[u];i;i=edge[i].next){
				int v=edge[i].to,w=edge[i].val;
				if(dis[u]+w>dis[v]){
					dis[v]=dis[u]+w;
					if(!vis[v]){
						vis[v]=1;
						q.push(v);
					}
				}
			}
		}
		printf("%d\n",dis[m]);
		if(t!=0)printf("\n");
	}
	return 0;
} 
```


---

## 作者：Space_Gold_Trash (赞：0)

前置知识:

1.差分约束

2.最短路

解法:

我们假设前缀和$sum_i$为前$i$位的选的数的总数

那么在$l->r$的区间选择$k$的数的意义就是$k\leq sum_r-sum_{l-1}$

然后对于$i->i+1$之间,意义肯定为$sum_{i+1}-sum_{i}\leq 1$和$0\leq sum_{i+1}-sum_{i}$

然后跑一次查分约束即可

```
#include<bits/stdc++.h> 
#define N 50011
#define M 200011
using namespace std;
int head[N],nex[M],tot,to[M],val[M];
bool vis[N];
inline void build(int xxxx,int yyyy,int zzzz){
	to[++tot]=yyyy;
	val[tot]=zzzz;
	nex[tot]=head[xxxx];
	head[xxxx]=tot;
}
int dis[N];
inline void pre( ){
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(head,0,sizeof(head));
	memset(nex,0,sizeof(nex));
	tot=0;
}
int m;
inline void init( ){
	scanf("%d",&m);
	int x,y,z;
	while(m--){
		scanf("%d%d%d",&x,&y,&z);
		build(x,y+1,z);
	}
	int i;
	for(i=0;i<=50000;++i){
		build(i,i+1,0);
		build(i+1,i,-1);
	}
}
inline void spfa(int k){
	deque<int>q;
	q.push_back(k);
	vis[k]=1;
	memset(dis,-1,sizeof(dis));
	dis[k]=0;
	int x,y,z,i;
	while(!q.empty( )){
		x=q.front( );
		q.pop_front( );
		for(i=head[x];!!i;i=nex[i]){
			y=to[i];z=val[i];
			if(dis[y]<dis[x]+z){
				dis[y]=dis[x]+z;
				if(!vis[y]){
					if(!q.empty( )&&dis[y]>dis[q.front( )])q.push_front(y);
					else q.push_back(y);
					vis[y]=1;
				}
			}
		}
		vis[x]=0;
	}
}
inline void work( ){
	spfa(0);
	printf("%d\n",dis[50001]);
}
int main( ){
	int t;
	scanf("%d",&t);
	while(t--){
		pre( );
		init( );
		work( );
		if(!!t)putchar('\n');
	}
}
```

---

## 作者：年华天地 (赞：0)

还没有线段树优化贪心的题解，让我来交一发吧

## 思路
首先很容易想到贪心，把每一个区间按右端点排序，然后依次遍历，对于每一个区间选树一定是选靠后的更优，因为要让数选的少，区间重复的地方就要多选数，又因为我们将区间按右端点排了序，所以一定是选后面的数最优。

## 实现
按照贪心的思路，我们就需要一个数据结构来维护两个操作：
1. 查询区间中选了多少个数
1. 从区间右端点开始插数

那么我们就可以用线段树来维护，具体怎么从右端点开始选数呢？我们可以每次选数的时候先遍历右儿子，右儿子选完了还要插选在再遍历左儿子，并且只有在它能选的数的个数小于要选的数的个数时才选，保证每一次选都选完了当前区间。
```
if (t[id].lazy)pushdown(id);
	if (t[id].l>r||t[id].r<l||w<=0||t[id].sum==t[id].len)return ;
	else if (t[id].l>=l&&t[id].r<=r&&w>=t[id].len-t[id].sum)//w为选数的个数，全局变量
	{
		w-=t[id].len-t[id].sum;
		t[id].sum=t[id].len;
		t[id].lazy=1;
		return ;
	}
	else add(id*2+1,l,r),add(id*2,l,r);
	t[id].sum=t[id*2].sum+t[id*2+1].sum;
```
## 代码
 ```
#include<cstdio>
#include<algorithm>
#define mid (l+r)/2
using namespace std;
const int maxn=1e5;
int n,w;
struct node{
	int l,r,w;
}s[maxn];
struct tree{
	int l,r,sum,lazy,len;
}t[maxn*4];
bool cmp(node a,node b)
{
	return a.r<b.r;
}
void build(int id,int l,int r)
{
	t[id].l=l;
	t[id].r=r;
	t[id].sum=0;
	t[id].lazy=0;
	t[id].len=r-l+1;
	if (l==r)return ;
	build(id*2,l,mid);
	build(id*2+1,mid+1,r);
}
void pushdown(int id)
{
	t[id*2].lazy=t[id*2+1].lazy=1;
	t[id*2].sum=t[id*2].r-t[id*2].l+1;
	t[id*2+1].sum=t[id*2+1].r-t[id*2+1].l+1;
	t[id].lazy=0;
}
int query(int id,int l,int r)
{
	if(t[id].l>r||t[id].r<l)return 0;
	if (t[id].lazy)pushdown(id);
	if (t[id].l>=l&&t[id].r<=r)return t[id].sum;
	return query(id*2,l,r)+query(id*2+1,l,r);
}
void add(int id,int l,int r)
{
	if (t[id].lazy)pushdown(id);
	if (t[id].l>r||t[id].r<l||w<=0||t[id].sum==t[id].len)return ;
	else if (t[id].l>=l&&t[id].r<=r&&w>=t[id].len-t[id].sum)
	{
		w-=t[id].len-t[id].sum;
		t[id].sum=t[id].len;
		t[id].lazy=1;
		return ;
	}
	else add(id*2+1,l,r),add(id*2,l,r);
	t[id].sum=t[id*2].sum+t[id*2+1].sum;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int maxx=0;
		for (int i=1;i<=n;i++)scanf("%d%d%d",&s[i].l,&s[i].r,&s[i].w),maxx=maxx>s[i].r?maxx:s[i].r;
		build(1,1,maxx);
		sort(s+1,s+n+1,cmp);
		for (int i=1;i<=n;i++)w=s[i].w-query(1,s[i].l,s[i].r),add(1,s[i].l,s[i].r);
		printf("%d\n",t[1].sum);
		if (T)printf("\n");
	}
	return 0;
}
```


---

## 作者：极寒神冰 (赞：0)

### 差分约束

我们一般将$d_u+w>=d_v$称作三角形不等式，就是在点u上连一条权值为w的边到点v。

题意就是告诉你一些不等式 $S[a_i]-S[b_i]>=c_i$,且满足$S[i]-S[i-1]>=0$且$s[i]-s[i+1]>=-1$。然后求这些不等式组的最小解。

首先可以移项得$S[a_i]-c_i>=S[b_i]$即将$a_i$到$b_i$连一条边权为$-c_i$的边。

为了满足$S[i]-S[i-1]>=0$且$s[i]-s[i+1]<=1$,我们可以从$i$到$i+1$建一条边权为$0$,从$i+1$到$i$连一条边权为$-1$的边。

之后用spfa跑最长路即可

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int N=600010;
const int inf=0x3f3f3f3f;
struct edge
{
	int nxt,to,val;
}e[N];
int dis[N],head[N],n,minn=inf,maxx=-inf,cnt,vis[N];
inline void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
inline void add_edge(int u,int v,int d)
{
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	e[cnt].val=d;
	head[u]=cnt;
}
inline void spfa()
{
	queue<int>q;
	q.push(minn);
	dis[minn]=0;
	while(q.size()>0)
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i!=-1;i=e[i].nxt)
		{
			int v=e[i].to;
			if(dis[v]<dis[u]+e[i].val)
			{
				dis[v]=dis[u]+e[i].val;
				if(!vis[v])
				{
					vis[v]=1;
					q.push(v);
				}
			}
		}
	}
}
int _;
int main()
{
	{
		init();
		n=read();
		for(int i=1;i<=n;i++)
		{
			int x=read(),y=read(),z=read();
			add_edge(x,y+1,z);
			minn=min(minn,x);
			maxx=max(maxx,y+1);
		}
		for(int i=minn;i<=maxx;i++)
		{
			dis[i]=-inf;
			add_edge(i,i+1,0);
			add_edge(i+1,i,-1);
		}
		spfa();
		cout<<dis[maxx]<<endl;
	}
	
}
```




---

## 作者：windrizzle (赞：0)

### 题意

有n个如下形式的条件:

$ai$ $bi$ $ci$,表示在区间$[ai, bi]$内至少要选择$ci$个整数点。

问你满足$n$个条件的情况下,最少需要选多少个点?

### 题解

就差分约束呗......

何为差分约束:如果一个系统由$n$个变量和$m$个约束条件组成，形成$m$个形如$ai-aj≤k$的不等式($i,j∈[1,n]$,$k$为常数),则称其为差分约束系统。

由此，可以把它转化为图，跑一波SPFA就完事了。

### 代码

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<stack>
#include<iostream>
using namespace std;
struct node
{
    int u,v,w;
    int next;
}wee[500001];
int minnnn=0x7f,maxxxx=-1;//最小和最大
int n,h[500001],cnt;
int u,v,w;
int vis[500001],stackto[500001],qwq[500001];
void add(int u,int v,int w)
{
    wee[++cnt].u=u;
    wee[cnt].v=v;
    wee[cnt].w=w;
    wee[cnt].next=h[u];
    h[u]=cnt;
}
bool spfa()
{
    stack<int>st;
    while(!st.empty()) st.pop();
    memset(stackto,0,sizeof(stackto));
    memset(qwq,0,sizeof(qwq));
    for(int i=minnnn;i<=maxxxx;i++)
        vis[i]=-0x7f;
    st.push(minnnn);
    vis[minnnn]=0;
    stackto[minnnn]=1;
    qwq[minnnn]++;
    while(!st.empty())
    {
        int u=st.top();
        st.pop();
        stackto[u]=0;
        for(int i=h[u];i!=0;i=wee[i].next)
        {
            if(vis[wee[i].v]<vis[u]+wee[i].w)
            {
                vis[wee[i].v]=vis[u]+wee[i].w;
                if(!stackto[wee[i].v])
                {
                    stackto[wee[i].v]=1;
                    st.push(wee[i].v);
                    qwq[wee[i].v]++;
                    if(qwq[wee[i].v]>n)
                        return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>u>>v>>w;
        add(u,v+1,w);
        minnnn=min(minnnn,u);
        maxxxx=max(maxxxx,v+1);
    }
    for(int i=minnnn;i<maxxxx;i++)
    {
        add(i,i+1,0);
        add(i+1,i,-1);
    }
    spfa();//万能的spfa
    cout<<vis[maxxxx]-vis[minnnn]<<endl;
    return 0;
}
```


---

## 作者：RPChe_ (赞：0)

首先看完题目，就可以发现这是一道~~贪心~~差分约束的裸题。

#### 那么，差分约束乃何许物也？

差分约束系统是一种特殊的N元一次不等式组，它包含N个变量X1~XN以及M个约束条件，每个约束条件都是由两个变量作差构成的，形如Xi-Xj<=Ck，Ck是常数，1〈=i，j<=N,1<=k<=M。我们要解决的问题是：求一组解X1=a1，X2=a2...Xn=aN，使所有约束条件都得到满足。

差分约束系统的每个约束条件Xi-Xj<=ck可以变形为Xi<=Xj+ck。这与单源最短路算法中的三角形不等式dis[y]<=dis[x]+z非常相似。因此，可以把每个变量Xi看作有向图中的一个节点i，对于每个约束条件Xi-Xj<=ck,看作从节点j向节点i连一条长度为ck的有向边。（以上摘自信息学奥赛一本通.提高篇）这样就可以愉快的跑单源最短路算法了。

而对于形如Xi-Xj>=Ck的约束条件（本题），看作从节点j向节点i连一条长度为ck的有向边，然后跑单源最短长路算法就可以了。这里有一个判断是跑最长路还是最短路的窍门，把Xi-Xj<=ck变形为Xi<=Xj+ck，可以理解为最后的结果中源点到Xi的距离要么短于源点到Xj的距离加Xi与Xj之间的距离，要么与其相等。这样的话，肯定跑的是最短路算法。反之就是最长路算法。

## 但以上不是重点。

整个差分约束系统中最烦人的，莫过于判别隐藏条件和保证图联通（容易忘）。由于每道题的隐藏条件不同，所以要有针对性的分析。对于本题，设s[i]表示0~i中选择了n个数，则隐藏条件有2个：

1.s[i]-s[i-1]>=0。0~i中选出的数肯定不比0~i-1少。

2.s[i]-s[i-1]<=1。每个数只能被选一次，可变形为s[i-1]-s[i]>=-1。

本题由于添加隐藏条件后，图就必定联通，因此就不用考虑图是否联通的问题了。但是在做某些题时，题中的隐藏条件不足以保证图联通，或根本无隐藏条件，这时就要用另一个东西——超级源点。具体我写在另一篇题解上——[UVA515 King](https://www.luogu.org/blog/Darth-Che/solution-uva515)

还有一个问题，差分约束系统不能使用dijkstra算法，因为dijkstra算法不能处理负权回路，只能用Bellman-Ford算法或spfa算法。

最后抬上代码——

```cpp
#include<iostream>
#include<string.h>
#include<queue>
#include<stdlib.h>
using namespace std;
struct sss{
	int a,b,v,next;
}e[1000000];
const int inf=0x3f3f3f3f;
int head[1000000],n,dis[1000000],cnt=1,vis[1000000],vis1[1000000],minn=inf,maxx=0;
void add(int a,int b,int v)
{
	e[cnt].a=a;
	e[cnt].b=b;
	e[cnt].v=v;
	e[cnt].next=head[a];
	head[a]=cnt;
	cnt++;
}
int spfa(int sta)
{
	queue<int> q;
	q.push(sta);
	vis[sta]=1;
	dis[sta]=0;
	vis1[sta]++;
	while(!q.empty())
	{
		int temp=q.front();
		q.pop();
		vis[temp]=0;
		for(int i=head[temp];i!=-1;i=e[i].next)
		{
			if(dis[e[i].b]<dis[temp]+e[i].v)
			{
				dis[e[i].b]=dis[temp]+e[i].v;
				if(vis[e[i].b]==0)
				{
					vis[e[i].b]=1;
					q.push(e[i].b);
					vis1[e[i].b]++;
					if(vis1[e[i].b]>n)
					return -1;
				}
			}
		}
	}
	return dis[maxx];
}
void clear()
{
	memset(head,-1,sizeof(head));
	memset(dis,-inf,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(vis1,0,sizeof(vis1));
	cnt=1;
	minn=inf;
	maxx=0;
}
int main()
{
	int n1;
	cin>>n1;
	for(int ii=1;ii<=n1;ii++)
	{
		clear();
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			int a,b,c;
			cin>>a>>b>>c;
			add(max(0,a-1),b,c);
			minn=min(minn,max(0,a-1));
			maxx=max(maxx,b);
		}
		for(int i=minn;i<maxx;i++)
		{
			add(i,i+1,0);
			add(i+1,i,-1);
		}
		if(ii==n1) cout<<spfa(minn)<<endl;
		else cout<<spfa(minn)<<endl<<endl;
	}
	return 0;
}
```


---

## 作者：违规用户名71524 (赞：0)

我真的太弱了，大佬们说这是裸的差分约束，然而我并不知道是什么东西（滑稽）
所以现场学了一下
总的来说就是把问题转化成图论问题，由于要求最小值，所以spfa跑最长路（或者把边的权值变负，然后最短路）
由于本题数据的原因因此不用考虑无解的情况
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<math.h>
using namespace std;
int n,mn=100000000,mx;
int h[50005],fr[200005],to[200005],v[200005],cnt;
int dis[50005];
bool vis[50005];
queue<int>q;
void add(int x,int y,int z)
{
	fr[++cnt]=h[x];
	to[cnt]=y;
	v[cnt]=z;
	h[x]=cnt;
}
int spfa()
{
	q.push(mn);
	vis[mn]=1;
	memset(dis,0x80,sizeof(dis));
	dis[mn]=0;
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		vis[now]=0;
		for(int i=h[now];i;i=fr[i])
		{
			if(dis[to[i]]<dis[now]+v[i])
			{
				dis[to[i]]=dis[now]+v[i];
				if(!vis[to[i]])
				{
					vis[to[i]]=1;
					q.push(to[i]);
				}
			}
		}
	}
	return dis[mx];
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y,z;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y+1,z);
		mx=max(mx,y+1);
		mn=min(x,mn);
	}
	for(int i=mn;i<mx;i++)
	{
		add(i,i+1,0);
		add(i+1,i,-1);
	}
	int ans=spfa();
	printf("%d\n",ans);
}
```

---

