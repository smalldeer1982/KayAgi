# [EC Final 2021] Check Pattern is Bad

## 题目描述

庞教授得到一个 $n \times m$ 的棋盘。有些格子被涂成黑色，有些被涂成白色，其他的则没有颜色。

庞教授不喜欢“棋盘格”图案，所以他想要给所有未上色的格子上色，使得棋盘上没有棋盘格图案。

如果 $4$ 个格子形成一个 $2 \times 2$ 的正方形，并且它们的颜色是以下两种方式之一，则称它们具有棋盘格图案：

```plain
BW
WB
```

```plain
WB
BW
```

这里 `W`（在切瓦语中为“wakuda”）表示格子被涂成黑色，`B`（在科西嘉语中为“biancu”）表示格子被涂成白色。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
2 2
??
??
3 3
BW?
W?B
?BW
3 3
BW?
W?W
?W?```

### 输出

```
YES
BW
WW
NO
YES
BWB
WWW
BWB```

# 题解

## 作者：FFTotoro (赞：17)

## 前言

Update：原来的代码漏判了一个细节被 hack 了，现在已经修正，感谢 @[Sio_](https://www.luogu.com.cn/user/678673) 的贡献。

$10\mathrm{s}$ 抽象构造题。罚了 $10$ 发爽歪歪。

## 解法

考虑先确定可以确定的 $\texttt{?}$，就是一个 $2\times 2$ 的子矩阵，其中 $3$ 个字符已经确定，剩下那个字符只有一种填法的。实现可以枚举一个格子，使用一个方向数组枚举子矩阵，然后如果两种子矩阵在该字符上有冲突直接无解。**这个过程要正着倒着做两遍**！可以证明剩下的情况都是有解的。

现在我们剩下了一些格子没法确定。考虑随机化，对当前一个 $\texttt{?}$ 先随机赋一个值，然后后面的格子再根据前面已经染好色的格子进行染色（显然最开始那种构造的方法可以改一改再用），如果还是有多种选择就再随机一下。一直重复这个过程（用死循环），直到找到解了就输出。

放代码：

```cpp
// 10s...mt19937 yyds!!!
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int dx[4]={-1,-1,0,0},dy[4]={-1,0,-1,0}; // 方向数组
char mp(bool b){return b?'W':'B';}
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m;
    mt19937 g(time(0));
    uniform_int_distribution<> u(0,1);
    vector<string> a(n);
    for(auto &i:a)cin>>i;
    auto cl=[&](int x,int y){
      for(int i=0;i<4;i++){
        int x0=x+dx[i],y0=y+dy[i];
        if(~min(x0,y0)&&x0+1<n&&y0+1<m){
          vector<pii> p={
            make_pair(x0,y0),
            make_pair(x0+1,y0),
            make_pair(x0,y0+1),
            make_pair(x0+1,y0+1)};
          // 子矩阵中四个元素
          int c=0;
          for(auto [x1,y1]:p)
            if(make_pair(x1,y1)!=make_pair(x,y)&&a[x1][y1]=='?')c++;
            // 判断其他字符是否是 ?
          if(c)continue; // 该子矩阵不能确定
          switch(i){
            case 0:
              if(a[x0+1][y0]==a[x0][y0+1]&&a[x0+1][y0]!=a[x0][y0])
                if(a[x][y]==a[x0][y0])return false;
                else a[x][y]=a[x0+1][y0];
              break;
              // 先判矛盾然后染色
            case 1:
              if(a[x0][y0]==a[x0+1][y0+1]&&a[x0][y0+1]!=a[x0][y0])
                if(a[x][y]==a[x0][y0+1])return false;
                else a[x][y]=a[x0][y0];
              break;
            case 2:
              if(a[x0][y0]==a[x0+1][y0+1]&&a[x0+1][y0]!=a[x0][y0])
                if(a[x][y]==a[x0+1][y0])return false;
                else a[x][y]=a[x0][y0];
              break;
            case 3:
              if(a[x0+1][y0]==a[x0][y0+1]&&a[x0+1][y0]!=a[x0+1][y0+1])
                if(a[x][y]==a[x0+1][y0+1])return false;
                else a[x][y]=a[x0+1][y0];
              break;
          }
        }
      }
      return true;
    }; // 染色构造，返回值为是否有矛盾
    bool f=true;
    for(int i=0;i<n&&f;i++)
      for(int j=0;j<m&&f;j++)f&=cl(i,j);
    for(int i=n-1;~i&&f;i--)
      for(int j=m-1;~j&&f;j--)f&=cl(i,j); // 记得把漏下的做一遍
    if(!f){cout<<"NO\n"; continue;} // 无解
    while(1){
      vector<string> r=a; f=true;
      for(int i=0;i<n&&f;i++)
        for(int j=0;j<m&&f;j++)
          if(a[i][j]=='?')
            if(f&=cl(i,j);a[i][j]=='?')a[i][j]=mp(u(g));
            // 随机一下
      for(int i=0;i<n&&f;i++)
        for(int j=0;j<m&&f;j++)f&=cl(i,j); // 判断解的合法性
      if(f)break; a=r;
    }
    cout<<"YES\n";
    for(auto i:a)cout<<i<<'\n';
  }
  return 0;
}
```

顺便放一下 hack 掉原来的代码的 hack 数据：

```
1
4 10
WB??WB??B?
??WB??W??B
??W?BWB??W
??BW??????
```

---

## 作者：Kreado (赞：13)

[题目传送门](https://www.luogu.com.cn/problem/P9878)。

很好的构造题。

## 思路

为了更好理解解法，我们不妨将行列奇偶性相同的格子反色处理，比如说该格子上的颜色为 `B`，它的反色处理就是 `W`，`W` 同理。

这样我们的限制就变成了不能出现一个 $2\times 2$ 的方格区域使得该区域内的颜色相同。

这样，如果我们已经确定了一个 $2\times 2$ 区域内三个格子的颜色，那么我们必定能确定剩下一个格子的颜色。

先 BFS 一次把能推出来的格子填色，如果矛盾输出无解，否则我们考虑使用这样的步骤构造出一组合法解：

1. 如果所有格子都被填上了颜色，结束程序，否则随机选择一个未填上颜色的格子，将其染成黑白色的一种（即随便染色）。

2. BFS 暴力拓展一遍，把能推出来的格子推出来。

3. 重复以上两个步骤，最终一定能找到一组合法解。

那么，为什么随机填颜色是正确的呢？让我们来浅浅证明一下：

不妨设 $(x,y)$ 表示我们将要填色的位置，假设我们将其染色成黑，我们考虑右下角的情况。

如果方格 $(x+1,y+1)$ 能被确定当且仅当方格 $(x+1,y),(x,y+1)$ 确定为黑色，那么我们将 $(x+1,y+1)$ 染成白色，接下来我们要往 $(x+2,y+2)$ 拓展，重复一遍操作，直到存在一个 $k$ 使得 $(x+k,y+k)$ 和 $(x+k-1,y+k),(x+k,y+k-1)$ 异色，那么考虑 $(x+k-1,y+k-1)$，这种情况我们已经在之前的运算中确定了，矛盾。

注意：我们只是为了更好理解思路才将行列反色的，代码可以直接做的。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=110;
int T,n,m,hd,tl;

char s[Maxn][Maxn];
struct node{
	int x,y;
	node(int x=0,int y=0):x(x),y(y){}
}q[Maxn*Maxn];

inline char f(char x){
	return x=='B'?'W':'B';
} 
inline bool check(int x,int y){
	if(!x||!y||x==n||y==m) return 1;
	int cnt=0;if(s[x][y]=='?') ++cnt;if(s[x+1][y]=='?') ++cnt;
	if(s[x][y+1]=='?') ++cnt;if(s[x+1][y+1]=='?') ++cnt;
	if(cnt>1) return 1;
	if(!cnt) return s[x][y]==s[x+1][y]||s[x][y]==s[x][y+1]||s[x][y]!=s[x+1][y+1];
	if(s[x][y]==s[x+1][y+1]){
		if(s[x+1][y]=='?'&&s[x][y]!=s[x][y+1]) s[x+1][y]=f(s[x][y+1]),q[++tl]=node(x+1,y);
		if(s[x][y+1]=='?'&&s[x][y]!=s[x+1][y]) s[x][y+1]=f(s[x+1][y]),q[++tl]=node(x,y+1);
	}
	if(s[x+1][y]==s[x][y+1]){
		if(s[x][y]=='?'&&s[x+1][y]!=s[x+1][y+1]) s[x][y]=f(s[x+1][y+1]),q[++tl]=node(x,y);
		if(s[x+1][y+1]=='?'&&s[x+1][y]!=s[x][y]) s[x+1][y+1]=f(s[x][y]),q[++tl]=node(x+1,y+1);
	} 
	return 1;
} 

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);hd=1,tl=0;
		for(int i=1;i<=n;i++){
			scanf("%s",s[i]+1);
			for(int j=1;j<=m;j++) if(s[i][j]!='?') q[++tl]=node(i,j);
		} 
		bool flg=0;
		node ps=node(1,1);
		while(1){
			if(hd>tl){
				while(ps.x<=n&&s[ps.x][ps.y]!='?') if(ps.y<m) ps.y++;else ps.x++,ps.y=1;
				if(ps.x>n)break;// 以全部染色 
				s[ps.x][ps.y]='B';q[++tl]=ps; // 随机染色 
			}
			node t=q[hd++];
			if(!check(t.x,t.y)) {printf("NO\n");flg=1;break;}if(!check(t.x-1,t.y)) {printf("NO\n");flg=1;break;}
			if(!check(t.x,t.y-1)) {printf("NO\n");flg=1;break;}if(!check(t.x-1,t.y-1)) {printf("NO\n");flg=1;break;}
			
			// 判断是否合法 & 拓展染色 
			
		}
		if(!flg){
			printf("YES\n");
			for(int i=1;i<=n;i++,puts(""))
				for(int j=1;j<=m;j++)
					printf("%c",s[i][j]);
		}
	}	
	
	return 0;
}



```


---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/P9878)

**题目大意**

> 给定 $n\times m$ 网格，有一些位置已经被填 $0/1$，构造一种给整个网格填入 $0/1$ 的方案，使得其不包含子矩阵 $\begin{bmatrix}0&1\\1&0\end{bmatrix}$ 或 $\begin{bmatrix}1&0\\0&1\end{bmatrix}$。
>
> 数据范围：$n,m\le 100$。

**思路分析**

先把网格图黑白间隔染色，把被染成黑色的点 $0/1$ 翻转，那么我们就要让新网格不包含全 $0$ 和全 $1$ 的 $2\times 2$ 子矩阵。

首先，如果有一个 $2\times 2$ 子矩形中填入三个同色元素，那么剩下一个位置一定要填异色元素，填完之后可能又产生连锁反应，将另一个 $2\times 2$ 子矩形中填入了三个同色元素，用一个 dfs 维护此过程。

对每个 $2\times 2$ 子矩形 dfs 一遍，得到的新图不包含任何一个 $2\times 2$ 子矩形有三个同色元素和一个空位。

接下来我们任选一个空位，随便填 $0/1$，然后 dfs 增广，可以证明不断这样构造就能得出解。

我们只要说明一次 dfs 中不可能得到 $2\times 2$ 同色子矩形。

反证法设我们将一个子矩形 $\begin{bmatrix}x&0\\0&0\end{bmatrix}$ 的 $x$ 钦定为 $0$，那么这一定是通过右上角的全 $1$ 矩形得到的。

也就是形如：$\begin{bmatrix}1&1&\\1&x&0\\&0&0\end{bmatrix}$ 的结构，由于 dfs 前没有 $2\times 2$ 子矩形有三个同色元素和一个空位，因此这个结构中的三个 $0$ 至少有一个是在这一轮确定的，简单分析发现不可能存在这种情况。

时间复杂度 $\mathcal O(nm)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
int n,m,a[105][105];
void dfs(int i,int j) {
	if(i<1||j<1||i>=n||j>=m) return ;
	int s=a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1];
	if(s!=3&&s!=-3) return ;
	s=-s/3;
	if(!a[i][j]) a[i][j]=s,dfs(i-1,j-1);
	else if(!a[i+1][j]) a[i+1][j]=s,dfs(i+1,j-1);
	else if(!a[i][j+1]) a[i][j+1]=s,dfs(i-1,j+1);
	else a[i+1][j+1]=s,dfs(i+1,j+1);
}
void solve() {
	cin>>n>>m;
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		char c; cin>>c,a[i][j]=(c=='?'?0:(c=='B'?1:-1))*((i+j)&1?-1:1);
	}
	for(int i=1;i<n;++i) for(int j=1;j<m;++j) dfs(i,j);
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) if(!a[i][j]) {
		a[i][j]=1,dfs(i-1,j-1),dfs(i-1,j),dfs(i,j-1),dfs(i,j);
	}
	bool flg=1;
	for(int i=1;i<n;++i) for(int j=1;j<m;++j) {
		int s=a[i][j]+a[i+1][j]+a[i][j+1]+a[i+1][j+1];
		flg&=(s!=4&&s!=-4);
	}
	if(!flg) return cout<<"NO\n",void();
	cout<<"YES\n";
	for(int i=1;i<=n;++i,cout<<"\n") for(int j=1;j<=m;++j) {
		if((i+j)&1) a[i][j]*=-1;
		cout<<(a[i][j]>0?'B':'W');
	}
}
signed main() {
	ios::sync_with_stdio(false);
	int T; cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：tder (赞：0)

水黑，人类智慧题。配合代码食用效果更佳。

首先，若原棋盘中有满足条件的子矩阵，则显然无解。称作「Type 1」。

接下来，我们考虑有否能确定的点。例如 $\begin{bmatrix}\tt{W}&\tt{B}\\\tt{B}&?\end{bmatrix}$ 的，我们应当将 $?$ 处改为 $\tt{B}$。我们不妨枚举每个 $?$ 处，再枚举至多四个包含该 $?$ 的子矩阵，如果该子矩阵满足：

- 只有一个 $?$；
- 不含 $?$ 的对角线相等；
- 除 $?$ 外，相邻两个不等。

那么显然应当将 $?$ 替换为与其相邻的字母。特别的，若多个子矩阵得出的答案不一样，则无解。

上述过程需要正反各重复一遍，以确保所有能确定的都被确定。称作「Type 2」。

最后还有一些不能确定的点，我们不妨暴力枚举，使用随机化，同时每次也可以使用上面的方法进行剪枝。称作「Type 3」。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e2 + 5;
int t, n, m; char a[N][N], r[N][N];
const int dx[4] = {-1, -1, 0, 0};
const int dy[4] = {-1, 0, -1, 0};
bool same(int x1, int y1, int x2, int y2) {
	return (a[x1][y1] == a[x2][y2]);
}
bool equal(int x1, int y1, int x2, int y2) {
	return (a[x1][y1] == a[x2][y2] || a[x1][y1] == '?' || a[x2][y2] == '?');
}
bool work(int x1, int y1, int x2, int y2) {
	return equal(x1, y1, x2, y2) && equal(x1, y2, x2, y1) && (!equal(x1, y1, x1, y2) || !equal(x1, y1, x2, y1) || !equal(x2, y1, x2, y2) || !equal(x1, y2, x2, y2));
}
char near(int x, int y, int x1, int y1, int x2, int y2) {
	int xx = x, yy = (y == y1 ? y2 : y1);
	return a[xx][yy];
}
bool certain(int x, int y) {
	return a[x][y] != '?';
}
bool run(int x1, int y1, int x2, int y2) {
	return certain(x1, y1) && certain(x1, y2) && certain(x2, y1) && certain(x2, y2) && same(x1, y1, x2, y2) && same(x1, y2, x2, y1) && !same(x1, y1, x1, y2);
}
int check(int x, int y) {
	if(x + 1 <= n && y + 1 <= m && run(x, y, x + 1, y + 1)) return 0; // Type 1
	if(a[x][y] != '?') return 1;
	for(int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 1 || nx + 1 > n || ny < 1 || ny + 1 > m) continue;
		int b = 1;
		for(int xx = 0; xx < 2 && b; xx++) for(int yy = 0; yy < 2 && b; yy++) {
			int tx = nx + xx, ty = ny + yy;
			if((x != tx || y != ty) && a[tx][ty] == '?') b = 0;
		}
		if(!b) continue;
		if(work(nx, ny, nx + 1, ny + 1))
			if(a[x][y] != '?' && a[x][y] != near(x, y, nx, ny, nx + 1, ny + 1)) return 0;
			else a[x][y] = near(x, y, nx, ny, nx + 1, ny + 1);
	}
	return 1;
}
void solve() {
	cin>>n>>m;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin>>a[i][j];
	int b = 1;
	for(int i = 1; i <= n && b; i++) for(int j = 1; j <= m && b; j++) b = min(b, check(i, j)); // Type 2
	for(int i = n; i >= 1 && b; i--) for(int j = m; j >= 1 && b; j--) b = min(b, check(i, j));
	if(!b) {
		cout<<"NO"<<endl;
		return;
	}
	cout<<"YES"<<endl;
	while(1) { // Type 3
		memcpy(r, a, sizeof(r));
		b = 1;
		for(int i = 1; i <= n && b; i++) for(int j = 1; j <= m && b; j++) {
			b = min(b, check(i, j));
			if(a[i][j] == '?') a[i][j] = ((rand() % 2) ? 'B' : 'W');
		}
		for(int i = 1; i <= n && b; i++) for(int j = 1; j <= m && b; j++) b = min(b, check(i, j));
		if(b) break;
		memcpy(a, r, sizeof(a));
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) cout<<a[i][j];
		cout<<endl;
	}
}
signed main() {
	srand(time(0));
	cin>>t;
	while(t--) solve();
}
```

---

