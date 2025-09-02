# [PA 2021] Butelki

## 题目描述

Byteasar 有三瓶橙汁。他现在想通过把橙汁从一个瓶子倒入另一个瓶子的方式，让其中一个瓶子恰好装有 $k$ 升橙汁。因为他家里没有量筒，所以唯一允许的操作是在两个瓶子之间转移橙汁——要么把一个瓶子倒空，要么把一个瓶子倒满。橙汁不能撒到地上，也不能在这三个瓶子之外添加橙汁。

Byteasar 现在想知道，对于每一个 $k$，最少需要转移多少次橙汁才能让三个瓶子中的一个装有恰好 $k$ 升橙汁。他希望你帮帮他。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq A \leq B \leq C \leq 10^5$，$0 \leq a \leq A$，$0 \leq b \leq B$，$0 \leq c \leq C$。

## 样例 #1

### 输入

```
2 7 9
1 3 6```

### 输出

```
1 0 1 0 1 1 0 1 2 1```

# 题解

## 作者：Tjaweiof (赞：5)

# P9038 题解
[题目传送门](https://www.luogu.com.cn/problem/P9038)

容易发现一次操作之后必然有一个瓶子是满的或是空的，于是我们记 $s=a+b+c$，即橙汁的总量。假设满（空）的瓶子是第一个，则另外两个瓶子的橙汁的总量必为 $s$ 或 $s-a$，故不同的状态数不超过 $\max(A,B,C)$，直接记忆化搜索即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int A, B, C, a, b, c;
bool vis[100001][3][2];
int ans[100001];
struct Tjaweiof{
	int x, m;
	bool p;
	int t;
};
queue <Tjaweiof> q;
void pu(int a, int b, int c, int t){
	if (a + b <= A){
		q.push({c, 1, 0, t});
	}
	if (a + b >= A){
		q.push({a + b - A, 0, 1, t});
	}
	if (b + c <= B){
		q.push({a, 2, 0, t});
	}
	if (b + c >= B){
		q.push({b + c - B, 1, 1, t});
	}
	if (c + a <= C){
		q.push({b, 0, 0, t});
	}
	if (c + a >= C){
		q.push({c + a - C, 2, 1, t});
	}
	if (a + c <= A){
		q.push({a + c, 2, 0, t});
	}
	if (a + c >= A){
		q.push({b, 0, 1, t});
	}
	if (b + a <= B){
		q.push({b + a, 0, 0, t});
	}
	if (b + a >= B){
		q.push({c, 1, 1, t});
	}
	if (c + b <= C){
		q.push({c + b, 1, 0, t});
	}
	if (c + b >= C){
		q.push({a, 2, 1, t});
	}
	return;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> A >> B >> C >> a >> b >> c;
	memset(ans, -1, sizeof ans);
	ans[a] = 0;
	ans[b] = 0;
	ans[c] = 0;
	pu(a, b, c, 1);
	while (!q.empty()){
		auto u = q.front();
		q.pop();
		if (vis[u.x][u.m][u.p]){
			continue;
		}
		vis[u.x][u.m][u.p] = true;
		int na, nb, nc;
		if (!u.m){
			na = A * u.p;
			nb = u.x;
			nc = a + b + c - na - nb;
		} else if (u.m == 1){
			nb = B * u.p;
			nc = u.x;
			na = a + b + c - nb - nc;
		} else if (u.m == 2){
			nc = C * u.p;
			na = u.x;
			nb = a + b + c - nc - na;
		}
		if (ans[na] == -1){
			ans[na] = u.t;
		}
		if (ans[nb] == -1){
			ans[nb] = u.t;
		}
		if (ans[nc] == -1){
			ans[nc] = u.t;
		}
		pu(na, nb, nc, u.t + 1);
	}
	for (int i = 0; i <= C; i++){
		cout << ans[i] << " ";
	}
	return 0;
}

```

---

## 作者：lzdll (赞：3)

注意到 $a,b,c\le 10^5$，非常的神秘，我们可以使用广搜把所有情况搜出来。

## 证明

因为果汁不能直接倒走，所以总量是不变的。

如果其中一个瓶子倒空了或另外的瓶子满了，那么第三个瓶子的容量可以算出来。

所以总情况数是关于 $C$ 成线性的。

## 代码

代码虽然长，但是上下的内容都差不多

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
int X,Y,Z;
int ans[N];
inline int hax(int x,int y,int z) {
	return x*N*N+y*N+z;
}
inline int getx(int h) {
	return h/(N*N);
}
inline int gety(int h) {
	return h/N%N;
}
inline int getz(int h) {
	return h%N;
}
queue<int>q;
unordered_map<int,int>vis,dis;
void bfs(int s) {
	q.push(s);
	dis[s]=0;
	while(!q.empty()) {
		int u=q.front();q.pop();
		int x=getx(u),y=gety(u),z=getz(u);
		ans[x]=min(ans[x],dis[u]);
		ans[y]=min(ans[y],dis[u]);
		ans[z]=min(ans[z],dis[u]);
		if(x+z<=Z) {//x->z
			if(!vis[hax(0,y,x+z)]&&(dis.find(hax(0,y,x+z))==dis.end()||dis[hax(0,y,x+z)]>dis[u]+1)){
				vis[hax(0,y,x+z)]=1;
				q.push(hax(0,y,x+z));
				dis[hax(0,y,x+z)]=dis[u]+1;
			}
		} else {
			if(!vis[hax(x+z-Z,y,Z)]&&(dis.find(hax(x+z-Z,y,Z))==dis.end()||dis[hax(x+z-Z,y,Z)]>dis[u]+1)){
				vis[hax(x+z-Z,y,Z)]=1;
				q.push(hax(x+z-Z,y,Z));
				dis[hax(x+z-Z,y,Z)]=dis[u]+1;
			}
		}
		if(x+y<=Y) {//x->y
			if(!vis[hax(0,x+y,z)]&&(dis.find(hax(0,x+y,z))==dis.end()||dis[hax(0,x+y,z)]>dis[u]+1)){
				vis[hax(0,x+y,z)]=1;
				q.push(hax(0,x+y,z));
				dis[hax(0,x+y,z)]=dis[u]+1;
			}
		} else {
			if(!vis[hax(x+y-Y,Y,z)]&&(dis.find(hax(x+y-Y,Y,z))==dis.end()||dis[hax(x+y-Y,Y,z)]>dis[u]+1)){
				vis[hax(x+y-Y,Y,z)]=1;
				q.push(hax(x+y-Y,Y,z));
				dis[hax(x+y-Y,Y,z)]=dis[u]+1;
			}
		}
		if(y+z<=Z) {
			if(!vis[hax(x,0,y+z)]&&(dis.find(hax(x,0,y+z))==dis.end()||dis[hax(x,0,y+z)]>dis[u]+1)){
				vis[hax(x,0,y+z)]=1;
				q.push(hax(x,0,y+z));
				dis[hax(x,0,y+z)]=dis[u]+1;
			}
		} else {
			if(!vis[hax(x,y+z-Z,Z)]&&(dis.find(hax(x,y+z-Z,Z))==dis.end()||dis[hax(x,y+z-Z,Z)]>dis[u]+1)){
				vis[hax(x,y+z-Z,Z)]=1;
				q.push(hax(x,y+z-Z,Z));
				dis[hax(x,y+z-Z,Z)]=dis[u]+1;
			}
		}
		if(y+x<=X) {
			if(!vis[hax(x+y,0,z)]&&(dis.find(hax(x+y,0,z))==dis.end()||dis[hax(x+y,0,z)]>dis[u]+1)){
				vis[hax(x+y,0,z)]=1;
				q.push(hax(x+y,0,z));
				dis[hax(x+y,0,z)]=dis[u]+1;
			}
		} else {
			if(!vis[hax(X,x+y-X,z)]&&(dis.find(hax(X,x+y-X,z))==dis.end()||dis[hax(X,x+y-X,z)]>dis[u]+1)){
				vis[hax(X,x+y-X,z)]=1;
				q.push(hax(X,x+y-X,z));
				dis[hax(X,x+y-X,z)]=dis[u]+1;
			}
		}
		if(z+x<=X) {
			if(!vis[hax(z+x,y,0)]&&(dis.find(hax(z+x,y,0))==dis.end()||dis[hax(z+x,y,0)]>dis[u]+1)){
				vis[hax(z+x,y,0)]=1;
				q.push(hax(z+x,y,0));
				dis[hax(z+x,y,0)]=dis[u]+1;
			}
		} else {
			if(!vis[hax(X,y,x+z-X)]&&(dis.find(hax(X,y,x+z-X))==dis.end()||dis[hax(X,y,x+z-X)]>dis[u]+1)){
				vis[hax(X,y,x+z-X)]=1;
				q.push(hax(X,y,x+z-X));
				dis[hax(X,y,x+z-X)]=dis[u]+1;
			}
		}
		if(z+y<=Y) {
			if(!vis[hax(x,z+y,0)]&&(dis.find(hax(x,z+y,0))==dis.end()||dis[hax(x,z+y,0)]>dis[u]+1)){
				vis[hax(x,z+y,0)]=1;
				q.push(hax(x,z+y,0));
				dis[hax(x,z+y,0)]=dis[u]+1;
			}
		} else {
			if(!vis[hax(x,Y,z+y-Y)]&&(dis.find(hax(x,Y,z+y-Y))==dis.end()||dis[hax(x,Y,z+y-Y)]>dis[u]+1)){
				vis[hax(x,Y,z+y-Y)]=1;
				q.push(hax(x,Y,z+y-Y));
				dis[hax(x,Y,z+y-Y)]=dis[u]+1;
			}
		}
	}
}
signed main() {
	int x,y,z;
	memset(ans,0x3f,sizeof ans);
	cin>>X>>Y>>Z>>x>>y>>z;
	bfs(hax(x,y,z));
	for(int i=0;i<=Z;++i){
		if(ans[i]>1e17)cout<<"-1";
		else cout<<ans[i];
		if(i!=Z)cout<<" ";
	}
	cout<<"\n";
	return 0;
}

```

---

## 作者：iyaang (赞：3)

[神秘的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17099060.html)

[题目链接](https://www.luogu.com.cn/problem/P9038)

设三个瓶子分别为 $x$、$y$、$z$，考虑一次操作只会有一个瓶子倒向另一个瓶子，所以最多延伸出六个新状态：$x \to y$、$x \to z$、$y \to x$、$y \to z$、$z \to x$、$z \to y$。每种状态都有两种可能，一个是倒空了当前的瓶子，另一个是倒满了要倒的瓶子。

不妨记三个瓶子初始的水量为 $a,b,c$，一次操作过后，必定有一个瓶子是满的或者空的，钦定 $a$ 是满的，那么剩下两个瓶子的状态数便是这三种情况之一：

$$
\min\{b,c\} +
\begin{cases}
\min\{a,b\} + \min\{a,c\} \\
\min\{a,b\} + 1 \\
\min\{a,c\} + 1
\end{cases}
$$

于是得到了一个 $2a + 2b + 2c +2 \times 3 + 1$ 数量的状态上界，其中 $2 \times 3$ 为六种不同倒的情况，$1$ 为初始状态，足以证明是状态数是线性增长的。因此尽管数据范围有 $10^5$，依然可以直接记忆化搜索。

记录只需要记三个瓶子的容量和当前状态的步数，直接压到一个数里面就好，这样也方便判重。

其他细节直接看代码罢。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	return s*w;
}

namespace LgxTpre
{
	static const int MAX=100010;
	static const int INF=4557430888798830399;
	static const int mod=998244353;
	static const int puz=1000000;
	
	int x_start,y_start,z_start;
	int ans[MAX];
	int up[4],bot[4],tmp[4],goal;
	
	queue<pair<int,int> > q;
	map<int,bool> mp;
	inline int get(int x,int y,int z)
	{
		return x*1000000000000+y*1000000+z;
	}
	inline void pullin(int tim)
	{
		int now=get(tmp[1],tmp[2],tmp[3]);
		if(mp.find(now)!=mp.end()) return;
		q.push(make_pair(now,tim));
		mp[now]=1;
		return;
	}
	
	inline void lmy_forever()
	{
		memset(ans,0x3f,sizeof ans);
		up[1]=read(),up[2]=read(),up[3]=read(); goal=up[3];
		x_start=read(),y_start=read(),z_start=read();
		q.push(make_pair(get(x_start,y_start,z_start),0));
		while(!q.empty())
		{
			int now=q.front().first,tim=q.front().second; q.pop();
			bot[3]=now%puz,now/=puz,ans[bot[3]]=min(ans[bot[3]],tim);
			bot[2]=now%puz,now/=puz,ans[bot[2]]=min(ans[bot[2]],tim);
			bot[1]=now%puz,now/=puz,ans[bot[1]]=min(ans[bot[1]],tim);
			for(int i=1;i<=3;++i)
				for(int j=1;j<=3;++j)
				{
					if(i==j) continue;
					int sum=bot[i]+bot[j];
					memcpy(tmp,bot,sizeof bot);
					if(sum>=up[j]) tmp[i]=sum-up[j],tmp[j]=up[j],pullin(tim+1);
					else tmp[i]=0,tmp[j]=sum,pullin(tim+1);
				}
		}
		for(int i=0;i<=goal;++i)
			cout<<(ans[i]==INF?-1:ans[i])<<" ";
		return;
	}
}

signed main()
{
	LgxTpre::lmy_forever();
	return (0-0);
}
```


---

## 作者：ycy1124 (赞：2)

### 题意
题面很详细，这里不讲。
### 思路
开题很容易想到记搜，最开始想的是如果当前倒出来的三种体积原来都倒出过就退出。可这是错的，因为可能只有某些特殊的体积组合才能倒出某些不同体积，三个都有但在不同的杯子里也是可以倒出一些其他的体积的。于是考虑用一个 map，每次将倒出的三个体积仿照 hash 操作一下然后放进 map 打标机，出现一样的就退出。
### 代码
使用 bfs 实现，每次暴力枚举从哪个杯子倒向哪个杯子。
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long base=114514;
const long long md=1e18+7;
int ans[100005];
int a,b,c,aa,bb,cc;
map<long long,bool>m;
struct Node{
    int a,b,c,w;
};
queue<Node>q;
inline int Min(int x,int y){//特别的Min函数
    if(x==-1){
        return y;
    }
    if(y==-1){
        return x;
    }
    return x<y?x:y;
}
inline long long sum(int A,int B,int C){//类似hash
    return (long long)(A+base*B%md+base*C%md*base%md)%md;
}
inline void bfs(int A,int B,int C,int w){
    ans[A]=Min(w,ans[A]);
    ans[B]=Min(w,ans[B]);
    ans[C]=Min(w,ans[C]);
    int AA,BB,CC;
    AA=A;
    if(B+C>b){
        BB=b;
        CC=B+C-b;
    }
    else{
        BB=B+C;
        CC=0;
    }
    if(!m.count(sum(AA,BB,CC))){
        m[sum(AA,BB,CC)]=1;
        q.push({AA,BB,CC,w+1});
        ans[AA]=Min(ans[AA],w+1);
        ans[BB]=Min(ans[BB],w+1);
        ans[CC]=Min(ans[CC],w+1);
    }
    if(B+C>c){
        BB=B+C-c;   
        CC=c;
    }
    else{
        BB=0;
        CC=B+C;
    }
    if(!m.count(sum(AA,BB,CC))){
        m[sum(AA,BB,CC)]=1;
        q.push({AA,BB,CC,w+1});
        ans[AA]=Min(ans[AA],w+1);
        ans[BB]=Min(ans[BB],w+1);
        ans[CC]=Min(ans[CC],w+1);
    }
    BB=B;
    if(A+C>a){
        AA=a;
        CC=A+C-a;
    }
    else{
        AA=A+C;
        CC=0;
    }
    if(!m.count(sum(AA,BB,CC))){
        m[sum(AA,BB,CC)]=1;
        q.push({AA,BB,CC,w+1});
        ans[AA]=Min(ans[AA],w+1);
        ans[BB]=Min(ans[BB],w+1);
        ans[CC]=Min(ans[CC],w+1);
    }
    if(A+C>c){
        CC=c;
        AA=A+C-c;
    }
    else{
        CC=A+C;
        AA=0;
    }
    if(!m.count(sum(AA,BB,CC))){
        m[sum(AA,BB,CC)]=1;
        q.push({AA,BB,CC,w+1});
        ans[AA]=Min(ans[AA],w+1);
        ans[BB]=Min(ans[BB],w+1);
        ans[CC]=Min(ans[CC],w+1);
    }
    CC=C;
    if(A+B>a){
        AA=a;
        BB=A+B-a;
    }
    else{
        AA=A+B;
        BB=0;
    }
    if(!m.count(sum(AA,BB,CC))){
        m[sum(AA,BB,CC)]=1;
        q.push({AA,BB,CC,w+1});
        ans[AA]=Min(ans[AA],w+1);
        ans[BB]=Min(ans[BB],w+1);
        ans[CC]=Min(ans[CC],w+1);
    }
    if(A+B>b){
        BB=b;
        AA=A+B-b;
    }
    else{
        BB=A+B;
        AA=0;
    }
    if(!m.count(sum(AA,BB,CC))){
        m[sum(AA,BB,CC)]=1;
        q.push({AA,BB,CC,w+1});
        ans[AA]=Min(ans[AA],w+1);
        ans[BB]=Min(ans[BB],w+1);
        ans[CC]=Min(ans[CC],w+1);
    }
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>a>>b>>c>>aa>>bb>>cc;
    for(int i=0;i<=c;i++){
        ans[i]=-1;
    }
    q.push({aa,bb,cc,0});
    while(q.size()){
        bfs(q.front().a,q.front().b,q.front().c,q.front().w);
        q.pop();
    }
    for(int i=0;i<=c;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}
```
[AC 记录。](https://www.luogu.com.cn/record/198487468)

---

## 作者：Alter_Native (赞：1)

## 思路

&emsp;首先一次操作只能把一个瓶子里的倒进另一个瓶子里，我们只需要根据倒的情况分类进行 bfs 即可。（只有 $6$ 种情况：`A` 倒进 `B`，`A` 倒进 `C`，`B` 倒进 `A`，`B` 倒进 `C`，`C` 倒进 `A`，`C` 倒进 `B`）

&emsp;当 bfs 到一个点时，我们算出每个瓶子剩余的容积是多少，然后拓展上面提到的六种情况。

- 如果一个瓶子里的橙汁量大于目标瓶子的容积，说明目标瓶子满了，这个倒出去的瓶子还剩一点。

- 如果如果一个瓶子里的橙汁量小于等于目标瓶子的容积，说明目标瓶子没有满（或刚好满了），这个倒出去的瓶子空了。

&emsp;对于那六种情况，每种进行上面的判断即可。

&emsp;为了防止出现重复访问浪费时间，我们可以把 bfs 过的状态（三个瓶子里剩的分别 $a,b,c$）存进一个 `map` 里，每次 bfs 时检测map里是否有这个状态，如果有就直接 `continue` 就行了。

&emsp;由于杯子容量最大为 $10^5$，所以我们可以开一个大小为 $10^5$ 的数组，记录达到每一个容量的最小步数。这个数组初始值应设为极大值，在最后如果我们发现数组的这个位置是我们设定的极大值，说明这个容量不能得到，要输出 $-1$。

&emsp;时间复杂度：因为每个容量我们至多访问一次，所以答案的时间复杂度为 $O(\max(A,B,C))$，可以通过此题。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int A,B,C,stp[100002];

struct node{
	int k,a,b,c;//k:步数 
};
struct step{
	int a,b,c;
	bool operator<(const step& q)const{//map需要排序，随便排一下就好了 
		if(a==q.a){
			if(b==q.b){
				if(c==q.c){
					return 0;
				}
				return c<q.c;
			}
			return b<q.b;
		}
		return a<q.a;
	}
};
queue<node> q;
map<step,bool> vis;

int main(){
	int a,b,c;
	scanf("%d%d%d%d%d%d",&A,&B,&C,&a,&b,&c);
	for(int i=0;i<=C+1;i++){
		stp[i]=0x3f3f3f3f;//设成最大 
	}
	q.push({0,a,b,c});//初始状态 
	while(!q.empty()){
		node f=q.front();
		q.pop();
		a=f.a,b=f.b,c=f.c;
		int k=f.k;
		if(vis[{a,b,c}]){
			continue;//走过了 
		}
		vis[{a,b,c}]=1;// 标记走过 
		stp[a]=min(stp[a],k);
		stp[b]=min(stp[b],k);//更新步数 
		stp[c]=min(stp[c],k);
		int sa=A-a,sb=B-b,sc=C-c;//剩余容积 
		if(sc>=a){//开始分类 
			q.push({k+1,0,b,c+a});
		} 
		else{
			q.push({k+1,a-sc,b,c+sc});
		} 
		if(sb>=a){
			q.push({k+1,0,b+a,c});
		} 
		else{
			q.push({k+1,a-sb,b+sb,c});
		}
		if(sa>=b){
			q.push({k+1,a+b,0,c});
		}
		else{
			q.push({k+1,a+sa,b-sa,c});
		}
		if(sc>=b){
			q.push({k+1,a,0,c+b});
		}
		else{
			q.push({k+1,a,b-sc,c+sc});
		}
		if(sa>=c){
			q.push({k+1,a+c,b,0});
		}
		else{
			q.push({k+1,a+sa,b,c-sa});
		}
		if(sb>=c) {
			q.push({k+1,a,b+c,0});
		}
		else{
			q.push({k+1,a,b+sb,c-sb});
		}
	} 
	for(int i=1;i<=C+1;i++){
		if(stp[i-1]==0x3f3f3f3f){
			stp[i-1]=-1;//没走过 
		}
		cout<<stp[i-1]<<" ";
	}
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/224939099)

---

## 作者：_Weslie_ (赞：1)

MX 盖世计划青岛 C 班 Day 2 T1 原题。

## Solution P9038

### Idea

首先，水量守恒。所以你最多只需要记录两个杯子的水量就可以直接求出来第三个。

其次，除了初始状态，一定存在一个杯子满或一个杯子空。

所以只需要记录四个值：

- 第一个值，记录一个普通的杯子中的水量。
- 第二个值，记录上面所说的“普通的杯子”是哪一个。
- 第三个值，记录特殊的杯子是空的还是满的。
- 第四个值，记录特殊的杯子是哪一个。

第一个值有最多 $C$ 种，第二、四个值最多三种，第三个最多两种情况。加上记忆化后，复杂度是 $\operatorname{O}(C)$ 的，可以通过。

具体来说，我们需要 bfs，从一个状态枚举 $12$ 种情况转移到下一个状态。可以参照代码理解。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
bool vis[N][3][2][3];
int ans[N],tot;
int siz[3],fir[3];
int r[3];
struct node{
	int w,t1,em,t2,st;
};
queue<node>q;
void bfs(){
	//三个杯子分别为 0,1,2 
	int st=0;
	//由于初始状态不一定满足有一个杯子空或满，需要对 12 种倒水情况分别枚举 
	if(r[0]+r[1]<=siz[0])q.push({r[2],2,0,1,st+1});//1->0 1 空 
	else q.push({r[2],2,1,0,st+1});//1->0 0 满 
	if(r[0]+r[2]<=siz[0])q.push({r[1],1,0,2,st+1});//2->0 2 空 
	else q.push({r[1],1,1,0,st+1});//2->0 0 满 
	if(r[2]+r[1]<=siz[1])q.push({r[0],0,0,2,st+1});//2->1 2 空 
	else q.push({r[0],0,1,1,st+1});//2->1 2 满 
	if(r[0]+r[1]<=siz[1])q.push({r[2],2,0,0,st+1});//0->1 0 空 
	else q.push({r[2],2,1,1,st+1});//0->1 1 满 
	if(r[0]+r[2]<=siz[2])q.push({r[1],1,0,0,st+1});//0->2 0 空 
	else q.push({r[1],1,1,2,st+1});//0->2 2 满 
	if(r[2]+r[1]<=siz[2])q.push({r[0],0,0,1,st+1});//1->2 1 空 
	else q.push({r[0],0,1,2,st+1});//1->2 2 满 
	//小优化：其实上面记录被更改的和没有被更改的是等价的情况，为了减少码量并且降低出错率，我们直接用没有被更改的记录状态。 
	ans[r[0]]=0;ans[r[1]]=0;ans[r[2]]=0;
	while(!q.empty()){
		node p=q.front();
		q.pop();
		int w=p.w,t1=p.t1,em=p.em,t2=p.t2;st=p.st;
		r[t1]=w;r[t2]=(em ? siz[t2] : 0);
		int t3=3-t1-t2;//找到第三个杯子。 
		r[t3]=tot-r[t1]-r[t2];//计算第三个杯子（没有被记录的这个）的水量 
		if(vis[w][t1][em][t2]||r[0]<0||r[1]<0||r[2]<0)continue;//不合法：注意一定要判断水量 <0 的情况 
		vis[w][t1][em][t2]=1;///记忆化 
		ans[r[0]]=min(ans[r[0]],st);
		ans[r[1]]=min(ans[r[1]],st);
		ans[r[2]]=min(ans[r[2]],st);//记录答案 
		if(r[0]+r[1]<=siz[0])q.push({r[2],2,0,1,st+1});//1->0 1 空 
		else q.push({r[2],2,1,0,st+1});//1->0 0 满 
		if(r[0]+r[2]<=siz[0])q.push({r[1],1,0,2,st+1});//2->0 2 空 
		else q.push({r[1],1,1,0,st+1});//2->0 0 满 
		if(r[2]+r[1]<=siz[1])q.push({r[0],0,0,2,st+1});//2->1 2 空 
		else q.push({r[0],0,1,1,st+1});//2->1 2 满 
		if(r[0]+r[1]<=siz[1])q.push({r[2],2,0,0,st+1});//0->1 0 空 
		else q.push({r[2],2,1,1,st+1});//0->1 1 满 
		if(r[0]+r[2]<=siz[2])q.push({r[1],1,0,0,st+1});//0->2 0 空 
		else q.push({r[1],1,1,2,st+1});//0->2 2 满 
		if(r[2]+r[1]<=siz[2])q.push({r[0],0,0,1,st+1});//1->2 1 空 
		else q.push({r[0],0,1,2,st+1});//1->2 2 满 
	}
}
int main(){
	scanf("%d%d%d%d%d%d",&siz[0],&siz[1],&siz[2],&r[0],&r[1],&r[2]);
	tot=r[1]+r[2]+r[0];//总量守恒 
	for(int i=0;i<=siz[2];i++)ans[i]=0x3f3f3f3f;
	bfs();
	for(int i=0;i<=siz[2];i++){
		printf("%d ",(ans[i]==0x3f3f3f3f ? -1 : ans[i]));
	}
}
```
```

---

## 作者：chenhanzheapple (赞：1)

# [传送门](https://www.luogu.com.cn/problem/P9038)

# 思路

不难发现可以直接爆搜。

因为橙汁总量一定，每次操作完后必定有一个瓶子是满的或者空的，因此知道那个没有满的瓶子里装了多少橙汁和那个瓶子刚刚被灌满或倒空就可以推算出 $3$ 个瓶子各装了多少橙汁。因此一共有至多 $2 \times (a+b+c)+1$ 个状态。

因此 BFS 或记搜即可。

# 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
int A,B,C,a,b,c,s;
int ans[300005];
map<pair<int,int>,int> f;
int fill(int x,int y,int X,int Y){//将x倒入y
    if(x+y<=Y){
        return x+y;
    }
    return Y;
}
queue<pair<int,int> > que;
void push(int x,int y,int z){
    if(!f.count({y,z})){
       f[{y,z}] = x+1;
       que.push({y,z});
    }
}
signed main(){
//    freopen("juice.in","r",stdin);
//    freopen("juice.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> A >> B >> C >> a >> b >> c;
    s = a+b+c;
    que.push({a,b});
    f[{a,b}] = 0;
    while(!que.empty()){
        auto t = que.front();
        que.pop();
        int k = f[t];
        int x = t.first,y = t.second,z = s-x-y;
        int nx = fill(y,x,B,A),ny = x+y-nx,nz = z;//B->A
        push(k,nx,ny);
        ny = fill(x,y,A,B),nx = x+y-ny,nz = z;//A->B
        push(k,nx,ny);
        nz = fill(x,z,A,C),nx = x+z-nz,ny = y;//A->C
        push(k,nx,ny);
        nx = fill(z,x,C,A),nz = x+z-nx,ny = y;//C->A
        push(k,nx,ny);
        nz = fill(y,z,B,C),ny = y+z-nz,nx = x;//B->C
        push(k,nx,ny);
        ny = fill(z,y,C,B),nx = y+z-ny,nx = x;//C->B
        push(k,nx,ny);
    }
    memset(ans,0x3f,sizeof(ans));
    for(auto x:f){
        ans[x.first.first] = min(ans[x.first.first],x.second);
        ans[x.first.second] = min(ans[x.first.second],x.second);
        ans[s-x.first.first-x.first.second] = min(ans[s-x.first.first-x.first.second],x.second);
    }
    for(int i=0;i<=C;i++){
        if(ans[i]>1e18){
            cout << -1;
        }
        else{
            cout << ans[i];
        }
        cout << " ";
    }
	return 0;
}
```

---

## 作者：Thekhoi_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9038)

### P9038 [PA2021] Butelki=数据结构+思维
#### 1. 暴力做法

按题意模拟，用一个深搜分别搜 $6$ 种情况。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
const long long inf=1e18;
int A,B,C,a,b,c;
long long f[N];
unordered_map<int,int>s;
void dfs(int x,int y,int z,int step){
	int tmp=x*1e12+y*1e6+z;//哈希
	if(s.count(tmp)&&s[tmp]<=step) return;
	//边界  
	s[tmp]=step;
	f[x]=min(f[x],step);
	f[y]=min(f[y],step);
	f[z]=min(f[z],step);
	
	int t=min(x,B-y);
	dfs(x-t,y+t,z,step+1);
	t=min(x,C-z);
	dfs(x-t,y,z+t,step+1);
	
	t=min(y,A-x);
	dfs(x+t,y-t,z,step+1);
	t=min(y,C-z);
	dfs(x,y-t,z+t,step+1);
	
	t=min(z,A-x);
	dfs(x+t,y,z-t,step+1);
	t=min(z,B-y);
	dfs(x,y+t,z-t,step+1);
	//6种倒法,也可使用for循环  
}
signed main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	cin>>A>>B>>C>>a>>b>>c;
	fill(f,f+C+1,inf);
	dfs(a,b,c,0);
	for(int i=0;i<=C;i++){
		if(f[i]>=inf) cout<<-1<<' ';
		else cout<<f[i]<<' ';
	}
	return 0;
}
```
[Unaccepted。](https://www.luogu.com.cn/record/183234931)

#### 2. 正解

记 $s=a+b+c$，注意到每一操作之后至少有一个瓶子是空的或者满的，不放设其为 $A$，那么剩下两个瓶子的橙汁数 $y，z$ 满足 $y+z=A$ 或 $y+z=s-A$，故不同的状态数只有 $\max(A,B,C)$ 种，用一个 BFS 搜出所有状态即可，时间复杂度为 $O(C)$，可以通过。

AC code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int A,B,C,a,b,c;
bool vis[N][3][2];
int f[N];
struct node{
	int p,m;
	bool full;
	int step;
};
queue<node> q;
void qpush(int x,int y,int z,int step){
	if(x+y<=A) q.push({z,1,0,step});
	if(x+y>=A) q.push({x+y-A,0,1,step});
	
	if(y+z<=B) q.push({x,2,0,step});	
	if(y+z>=B) q.push({y+z-B,1,1,step});
	
	if(z+x<=C) q.push({y,0,0,step});	
	if(z+x>=C) q.push({z+x-C,2,1,step});
	
	if(x+z<=A) q.push({x+z,2,0,step});
	if(x+z>=A) q.push({y,0,1,step});
	
	if(y+x<=B) q.push({y+x,0,0,step});
	if(y+x>=B) q.push({z,1,1,step});
	
	if(z+y<=C) q.push({z+y,1,0,step});
	if(z+y>=C) q.push({x,2,1,step});
}//6种倒法,建议好好理解  
void bfs(){
	f[a]=f[b]=f[c]=0;
	qpush(a,b,c,1);
	while(!q.empty()){
		node k=q.front();
		q.pop();
		int p=k.p,m=k.m;
		bool full=k.full;
		if(vis[p][m][full]) continue;
		vis[p][m][full]=1;
		int x,y,z;
		switch(m){
			case 0:
				x=A*full;
				y=p;
				z=a+b+c-x-y;
				break;
			case 1:
				y=B*full;
				z=p;
				x=a+b+c-y-z;
				break;
			case 2:
				z=C*full;
				x=p;
				y=a+b+c-z-x;
				break;
		}
		if(f[x]==-1) f[x]=k.step;
		if(f[y]==-1) f[y]=k.step;
		if(f[z]==-1) f[z]=k.step;
		qpush(x,y,z,k.step+1);
	}
}
int main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	memset(f,-1,sizeof(f));
	cin>>A>>B>>C>>a>>b>>c;
	bfs();
	for(int i=0;i<=C;i++) 
		cout<<f[i]<<' ';
}
```
[Accepted。](https://www.luogu.com.cn/record/183273909)

---

