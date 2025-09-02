# Anti-Tetris

## 题目描述

Let us consider the game "Sticky Tetris". In this game, there is a field of $ n \times m $ squares. Tiles appear on the field and the player can move the tiles.

Each tile is a $ 4 $ -connected set of at most $ 7 $ squares.

Each new tile appears in any position that fits inside the field, does not intersect any other tile, and the top cell of the tile is at the top row of the field. The player can move the tile left, right, and down, and at any moment the tile must still entirely fit inside the field and must not intersect other tiles. The player can stop the tile at any position at any time. After that, it cannot be moved. Since this is "Sticky Tetris," the tile will not fall once stopped.

You are given a final configuration of a "Sticky Tetris" game. You need to restore a sequence of steps that leads to that configuration if it exists.

## 样例 #1

### 输入

```
3 2
aa
ab
aa```

### 输出

```
2
2 DS
1 S```

## 样例 #2

### 输入

```
5 6
....dd
.ccccd
.cbbdd
.aab.a
aabbaa```

### 输出

```
5
2 DDDS
4 DDLS
6 DDDS
2 DS
5 S```

## 样例 #3

### 输入

```
5 3
...
aab
abb
aab
.bb```

### 输出

```
-1```

# 题解

## 作者：gyh20 (赞：2)

正着做是不好做的，因为我们不知道哪一块是最先放的，很难求出顺序的关系。

考虑倒着做，每次拿掉一个可以拿掉的，因为拿掉一个可以拿掉的连通块时不会影响其它连通块是否会被拿掉，即如果存在可行方案，每次将一个可以作为最后一个位置的连通块拿掉一定可行。

接下来可以直接模拟，每一次枚举所有连通块，bfs 检查是否可行，时间复杂度理论上是 $O(n^6)$ 的，来源于模拟 $O(n^2)$ 次，枚举 $O(n^2)$ 个连通块，bfs 是 $O(n^2)$ 的复杂度，但由于枚举到可行的连通块可以直接退出，枚举到不可行的连通块时 bfs 不会访问 $O(n^2)$ 个位置，连通块大小不可能全 $\leq 2$ 所以连通块个数也带着一个小常数，bfs 其实也是带一个小常数的，总的来说跑得很快。（可能有更正确的复杂度证明，很多自己口胡的不严谨的证明都存在一些恰好违背这个性质的极其特殊的反例，所以没有写出来）。

在模拟部分的一些细节可以参考代码：

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
const int M=998244353;
inline int ksm(re int x,re int y){
	re int s=1;
	while(y){
		if(y&1)s=1ll*s*x%M;
		x=1ll*x*x%M,y>>=1;
	}
	return s;
}
inline void add(re int &x,re int y){(x+=y)>=M?x-=M:x;}
inline int Mod(re int x){return x>=M?x-M:x;}
int n,m,X,Y,tot,px[2502],py[2502],ans1[2502],num;
string ans[2502];
char vis[52][52],s[52][52],cc[52][52];
struct node{int x,y;string S;};
inline bool ck(){
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			if(s[i][j]!='.')return 1;
	return 0;
}
inline void bfs(re int x,re int y){
	if(vis[x][y])return;
	if(s[x][y]!=s[X][Y])return;
	vis[x][y]=1,px[++tot]=x-X,py[tot]=y-Y;
	bfs(x-1,y),bfs(x+1,y),bfs(x,y-1),bfs(x,y+1);
}
inline bool ck(re int x,re int y){
	if(cc[x][y])return 0;
	for(re int i=1;i<=tot;++i)if(s[x+px[i]][y+py[i]]!='.')return 0;
	cc[x][y]=1;
	return 1;
}
inline int Try(re int x,re int y){
	X=x,Y=y,tot=0,bfs(x,y);
	re char c=s[x][y];
	for(re int i=1;i<=tot;++i)s[x+px[i]][y+py[i]]='.';
	queue<node>Q;
	memset(cc,0,sizeof(cc));
	Q.push((node){x,y,""});
	while(!Q.empty()){
		re node z=Q.front();Q.pop();
		if(z.x==1){
			ans1[++num]=z.y;
			ans[num]=z.S+'S';
			return 1;
		}
		if(ck(z.x-1,z.y))Q.push((node){z.x-1,z.y,"D"+z.S});
		if(ck(z.x,z.y-1))Q.push((node){z.x,z.y-1,"R"+z.S});
		if(ck(z.x,z.y+1))Q.push((node){z.x,z.y+1,"L"+z.S});
	}
	for(re int i=1;i<=tot;++i)s[x+px[i]][y+py[i]]=c;
	return 0;
}
int main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i)scanf("%s",s[i]+1);
	re int ttttt=0;
	while(ck()){
		memset(vis,0,sizeof(vis));
		re int ia=0;
		for(re int i=1;i<=n&&!ia;++i)
			for(re int j=1;j<=m&&!ia;++j)
				if(!vis[i][j]&&s[i][j]!='.'){
					if(Try(i,j))ia=1;
				}
		if(!ia)return puts("-1"),0;
	}
	printf("%d\n",num);
	for(re int i=num;i;--i){
		printf("%d ",ans1[i]);
		cout<<ans[i]<<'\n';
	}
}
```


---

## 作者：freoepn (赞：0)

正着移动不好做，尝试反着将每个方块移到最上面，枚举哪个方块可以直接移动到最上面，能移则移，否则等移走另一个方块后继续尝试。

```cpp
#include <bits/stdc++.h>
using namespace std;
char c[55][55];
int n, m;
int b[55][55];
bool e[55][55];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
vector<pair<int, int> > v[2505];
int siz = 0, szz = 0;
pair<int, int> er[2505];
void dfs(int x, int y) {
  b[x][y] = siz;
  v[siz].push_back(make_pair(x, y));
  for (int i = 0; i < 4; i++) {
    int ex = x + dx[i], ey = y + dy[i];
    if (c[ex][ey] == c[x][y] && b[ex][ey] == 0) {
      dfs(ex, ey);
    }
  }
}
bool vis[2505];
struct node {
  int x, y;
  string a;
};
vector<pair<int, string> > ew;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    b[i][0] = b[i][m + 1] = -1;
    for (int j = 1; j <= m; j++) {
      b[0][j] = b[n + 1][j] = -1;
      cin >> c[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (b[i][j] == 0&&c[i][j]!='.') {
        b[i][j] = ++siz;
        dfs(i, j);
      }
    }
  }
  int sum = 1;
  while (sum != 0) {
    sum = 0;
    for (int j = 1; j <= siz; j++) {
      if (!vis[j]) {
        szz = 0;
        queue<node> q;
        q.push((node){v[j][0].first, v[j][0].second, ""});
        e[v[j][0].first][v[j][0].second] = 1;
        er[++szz] = make_pair(v[j][0].first, v[j][0].second);
        while (!q.empty()) {
          int x = q.front().x, y = q.front().y;
          if (x == 1) {
            vis[j] = 1;
            sum++;
            ew.push_back(make_pair(y, q.front().a));
            for (int w = 0; w < v[j].size(); w++) {
              b[v[j][w].first][v[j][w].second] = 0;
            }
            break;
          }
          for (int k = 0; k <= 2; k++) {
            int ex = x + dx[k], ey = y + dy[k], p = (e[ex][ey] == 1);
            for (int w = 0; w < v[j].size(); w++) {
              int ux = ex + v[j][w].first - v[j][0].first, uy = ey + v[j][w].second - v[j][0].second;
              if (b[ux][uy] != j && b[ux][uy] != 0) {
                p = 1;
              }
            }
            if (p == 0) {
              e[ex][ey] = 1;
              er[++szz] = make_pair(ex, ey);
              if (k == 0) {
                q.push((node){ex, ey, q.front().a + "L"});
              } else if (k == 1) {
                q.push((node){ex, ey, q.front().a + "R"});
              } else {
                q.push((node){ex, ey, q.front().a + "D"});
              }
            }
          }
          q.pop();
        }
        for(int i = 1;i <= szz;i++){
          e[er[i].first][er[i].second] = 0;
        }
      }
    }

  }
  if(ew.size() == siz){
    cout << siz << endl;
    reverse(ew.begin(),ew.end());
    for(int i = 0;i < ew.size();i++){
      reverse(ew[i].second.begin(),ew[i].second.end());
      cout << ew[i].first << " "<< ew[i].second << "S\n";
    }
  }else{
    cout << "-1";
  }
  return 0;
}
```

---

