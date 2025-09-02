# Wilbur and Strings

## 题目描述

Wilbur the pig now wants to play with strings. He has found an $ n $ by $ m $ table consisting only of the digits from $ 0 $ to $ 9 $ where the rows are numbered $ 1 $ to $ n $ and the columns are numbered $ 1 $ to $ m $ . Wilbur starts at some square and makes certain moves. If he is at square ( $ x $ , $ y $ ) and the digit $ d $ ( $ 0<=d<=9 $ ) is written at position ( $ x $ , $ y $ ), then he must move to the square ( $ x+a_{d} $ , $ y+b_{d} $ ), if that square lies within the table, and he stays in the square ( $ x $ , $ y $ ) otherwise. Before Wilbur makes a move, he can choose whether or not to write the digit written in this square on the white board. All digits written on the whiteboard form some string. Every time a new digit is written, it goes to the end of the current string.

Wilbur has $ q $ strings that he is worried about. For each string $ s_{i} $ , Wilbur wants to know whether there exists a starting position ( $ x $ , $ y $ ) so that by making finitely many moves, Wilbur can end up with the string $ s_{i} $ written on the white board.

## 说明/提示

In the first sample, there is a $ 1 $ by $ 1 $ table consisting of the only digit $ 0 $ . The only move that can be made is staying on the square. The first string can be written on the white board by writing $ 0 $ repeatedly. The second string cannot be written as there is no $ 2 $ on the table.

## 样例 #1

### 输入

```
1 1 2
0
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
1 1
0000000000000
2413423432432
```

### 输出

```
YES
NO
```

## 样例 #2

### 输入

```
4 2 5
01
23
45
67
0 1
0 -1
0 1
0 -1
0 1
0 -1
0 1
0 -1
0 1
0 -1
0000000000
010101011101
32232232322
44343222342444324
6767
```

### 输出

```
YES
YES
YES
NO
YES
```

# 题解

## 作者：abruce (赞：3)

这道题的数据好弱啊，好多 $O(nm\sum |T|)$ 的算法能过，当然我在这里肯定是要讲正解，即 $O(nmq+\sum |T|)$ 的算法。  
首先我们发现每个网格图上的点有且仅有一条出边，所以这个图是一个基环森林。题目中的问题即在上面进行匹配。很明显我们的匹配是现在树边上走一段距离，然后一直走环将剩下的匹配完。如果我们枚举树边起点，就容易被[shangcheng的Hack数据](https://www.luogu.com.cn/discuss/show/323587)叉掉。所以我们考虑枚举环。  
我们考虑将这个字符串翻转过来，这样就是先走环，后走树边（当然边也要反过来）。记录一个环里面出现了哪些数字，这样我们就可以把后面的很长一段匹配完。然后我们从这个环里出去，走树边，容易得知每个点至多被访问一次，所以时间复杂度 $O(nmq+\sum |T|)$。  
```cpp
#include<bits/stdc++.h>
#define fi first
#define sc second
using namespace std;
const int maxn=205,maxm=1e6+5;
typedef pair<int,int> pi;
struct edge {
	int next,tx,ty;
} e[maxn*maxn];
int dx[10],dy[10],a[maxn][maxn],n,m,q,book[maxn*maxn][10],bc,bel[maxn][maxn],h[maxn][maxn],cnt,len,f[10];
vector<pi> b[maxn*maxn];
bool vis[maxn][maxn],maps[maxn][maxn];
stack<pi> t;
char s[maxm];
void addedge(int x,int y,int tx,int ty) {
	e[++cnt].next=h[x][y];
	e[cnt].tx=tx,e[cnt].ty=ty;
	h[x][y]=cnt;
}
void dfs(int x,int y) {
	int tx=x+dx[a[x][y]],ty=y+dy[a[x][y]];
	if(tx<1||tx>n||ty<1||ty>m)tx=x,ty=y;
	vis[x][y]=1,maps[x][y]=1,t.push(pi(x,y));
	if(!vis[tx][ty])dfs(tx,ty);
	else if(maps[tx][ty]) {
		bc++;
		while(!t.empty()) {
			book[bc][a[t.top().fi][t.top().sc]]=1;
			bel[t.top().fi][t.top().sc]=bc;
			if(t.top().fi==tx&&t.top().sc==ty) {
				t.pop();
				break;
			}
			t.pop();
		}
	}
	if(!bel[x][y]&&bel[tx][ty])b[bel[tx][ty]].push_back(pi(x,y));
	maps[x][y]=0;
	if(!t.empty()&&t.top().fi==x&&t.top().sc==y)t.pop();
}
bool find(int x,int y,int l) {
	if(a[x][y]==s[l]-'0')l++;
	if(l==len+1)return 1;
	bool w=0;
	for(register int i=h[x][y]; i; i=e[i].next)w|=find(e[i].tx,e[i].ty,l);
	return w;
}
int main() {
	scanf("%d%d%d",&n,&m,&q);
	for(register int i=1; i<=n; i++) {
		scanf("%s",s);
		for(register int j=1; j<=m; j++)a[i][j]=s[j-1]-'0';
	}
	for(register int i=0; i<10; i++)scanf("%d%d",&dx[i],&dy[i]);
	for(register int i=1; i<=n; i++)
		for(register int j=1; j<=m; j++) {
			if(!vis[i][j])dfs(i,j);
			int tx=i+dx[a[i][j]],ty=j+dy[a[i][j]];
			if(tx<1||tx>n||ty<1||ty>m)tx=i,ty=j;
			addedge(tx,ty,i,j);
		}
	while(q--) {
		scanf("%s",s+1),len=strlen(s+1);
		reverse(s+1,s+len+1);
		memset(f,0,sizeof(f));
		for(register int i=1; i<=len; i++)if(!f[s[i]-'0'])f[s[i]-'0']=i;
		bool ans=0;
		for(register int i=1; i<=bc; i++) {
			int mn=len+1;
			for(register int j=0; j<10; j++)if(!book[i][j]&&f[j])mn=min(mn,f[j]);
			if(mn==len+1) {
				ans=1;
				break;
			}
			for(register int j=0; j<b[i].size(); j++) {
				if(find(b[i][j].fi,b[i][j].sc,mn)) {
					ans=1;
					break;
				}
				if(ans==1)break;
			}
		}
		puts(ans?"YES":"NO");
	}
}
```

---

