# Maze Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/utpc2021/tasks/utpc2021_l

縦 $ H $ 行、横 $ W $ 列のグリッド状の迷路があります。 各マスには `S` , `G` , `#` , `.` のいずれかの文字が書かれています。$ i $ 行目 $ j $ 列目のマスに書かれている文字は$ c_{i,j} $ です。`#` と書かれたマスは壁になっており、そうでないマスは壁ではありません。 また、`S` と `G` は $ 1 $ つずつで、上下左右に隣接していないことが保証されます。

迷路が次の条件を満たす時、**到達可能な状態** と呼ぶことにします。

- `S` と書かれたマスから、`G` と書かれたマスに、上下左右に隣接する壁でないマス (つまり `#` と書かれてないマス) のみを通って到達できる。  ただし、迷路の外に出るような移動はできない。

最初、迷路は **到達可能な状態** であることが保証されます。

Alice と Bob がこの迷路を使ってゲームをします。 Alice が先手で、交互に以下の操作を行います。

- `.` と書かれたマスを $ 1 $ つ選び、 `#` と書かれたマスに変更する。

先に自分の操作終了時に、迷路が **到達可能な状態** でなくなったプレイヤーの勝利となります。 本問題の制約下で与えられる迷路では、必ず勝者が決定することが証明できます。 二人が最適に行動した場合、どちらが勝つか求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ T\ \le\ 50 $
- $ 2\ \le\ H,W\ \le\ 100 $
- 迷路に含まれる文字は、`S`, `G`, `.`, `#` のいずれか
- `S` と `G` は 1 つずつ含まれ、上下左右に隣接していない
- 与えられる迷路は **到達可能な状態** である

### Sample Explanation 1

1つめのケースでは、Aliceが選べるマスは右上か左下の2通りですが、どちらを選んでも次にBobがもう一方の `.` であるマスを選択してBobが勝ちます。 2つめのケースでは、Aliceが2行目の `.` を `#` に変えてAliceの勝利となります。

## 样例 #1

### 输入

```
2
2 2
S.
.G
2 3
#G#
S.#```

### 输出

```
Bob
Alice```

# 题解

## 作者：lzqy_ (赞：2)

题目乍一看无从下手，考虑拿出一组最小割来玩。

设 $s_1$ 表示最小割，$s_2$ 表示最小以外的可删除的点数。

注意到我们取出的割是极小的，所以不论 Bob 怎么选，Alice 总存在一种方案使得最小割 $-1$ 或不变。

所以只有当 $s_1,s_2$ 不同奇偶时先手才能获胜，反之后手胜。

记得特判 $s_1=1$ 的情况。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=20010;
const int maxm=50010;
const int inf=1<<30;
il int read(){
	int x=0;
	char c=getchar();
	for(;!(c>='0'&&c<='9');c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+c-'0';
	return x;
}
struct edge{
	int v,flo,to;
}e[maxm<<1];
int cur[maxn],head[maxn],ecnt=1;
void addedge(int u,int v,int flo){
	e[++ecnt].v=v,e[ecnt].flo=flo;
	e[ecnt].to=head[u],head[u]=ecnt;
}
void Add(int u,int v,int flo){
//	if(flo==inf)printf("%d->%d(inf)\n",u,v);
//	else printf("%d->%d(%d)\n",u,v,flo);
	addedge(u,v,flo),addedge(v,u,0);
}
int n,m,N,S,T;
int d[maxn];
queue<int>q;
bool bfs(){
	for(int i=1;i<=N;i++) d[i]=0;
	d[S]=1,q.push(S);
	while(!q.empty()){
		int t=q.front(); q.pop();
		for(int i=head[t];i;i=e[i].to)
			if(e[i].flo&&!d[e[i].v])
				d[e[i].v]=d[t]+1,q.push(e[i].v);
	}return d[T];
}
int dfs(int x,int flo){
//	printf("!!!%d(%lld)\n",x,flo);
	if(x==T||!flo) return flo;
	int delta=flo,xx;
	for(int i=cur[x];i;cur[x]=i,i=e[i].to)
		if(d[e[i].v]==d[x]+1){
			xx=dfs(e[i].v,min(delta,e[i].flo));
			e[i].flo-=xx,e[i^1].flo+=xx,delta-=xx;
		}
	return flo-delta;
}
int dinic(int sum=0){
	while(bfs()){
		for(int i=1;i<=N;i++) cur[i]=head[i];
		sum+=dfs(S,inf);
	}return sum;
}
int Test;
char a[110][110];
void clear(){
	for(int i=1;i<=N;i++) head[i]=0;
	ecnt=1,N=0;
}
int p[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int id(int x,int y){return (x-1)*m+y;}
int main(){
	Test=read();
	while(Test--){
		clear(); int tot=0;
		n=read(),m=read(),N=2*n*m;
		for(int i=1;i<=n;i++)
			scanf("%s",a[i]+1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(a[i][j]=='S') S=id(i,j),Add(id(i,j),n*m+id(i,j),inf);
				if(a[i][j]=='G') T=id(i,j)+n*m,Add(id(i,j),n*m+id(i,j),inf);
				if(a[i][j]=='.') tot++,Add(id(i,j),n*m+id(i,j),1);
				if(a[i][j]=='#') Add(id(i,j),n*m+id(i,j),0);
			} 
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(a[i][j]=='#') continue;
				for(int k=0;k<4;k++){
					int x=i+p[k][0],y=j+p[k][1];
					if(x<1||y<1||x>n||y>m) continue;
					if(a[x][y]=='#') continue;
					Add(n*m+id(i,j),id(x,y),inf);
				}
			}
		int s1=dinic(),s2=tot-s1;
		if(s1==1) printf("Alice\n"); 
		else if(s1%2==s2%2) printf("Bob\n");
		else printf("Alice\n");
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

若图中存在点使得删去它后 $S, T$ 不连通，那么 A 可以一步获胜。

否则，双方都不会删去一个点使得删去它后会产生一个点使得删去它后 $S, T$ 不连通。那么到最后图上会剩下两条 $S \to T$ 的不交路径。此时一方无论如何操作都会使得另一方获胜。

因为这是二分图，所以这两条路径的并的点数一定为偶数。那么只用判断初始时非障碍格数量的奇偶性，就能知道到达终态步数的奇偶性。

时间复杂度 $O(\sum nm)$。

注意不能直接套割点的板子。

[code](https://atcoder.jp/contests/utpc2021/submissions/46056438)

---

