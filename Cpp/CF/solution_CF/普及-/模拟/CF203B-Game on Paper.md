# Game on Paper

## 题目描述

One not particularly beautiful evening Valera got very bored. To amuse himself a little bit, he found the following game.

He took a checkered white square piece of paper, consisting of $ n×n $ cells. After that, he started to paint the white cells black one after the other. In total he painted $ m $ different cells on the piece of paper. Since Valera was keen on everything square, he wondered, how many moves (i.e. times the boy paints a square black) he should make till a black square with side $ 3 $ can be found on the piece of paper. But Valera does not know the answer to this question, so he asks you to help him.

Your task is to find the minimum number of moves, till the checkered piece of paper has at least one black square with side of $ 3 $ . Otherwise determine that such move does not exist.

## 样例 #1

### 输入

```
4 11
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
3 3
4 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
4 12
1 1
1 2
1 3
2 2
2 3
1 4
2 4
3 4
3 2
4 2
4 1
3 1
```

### 输出

```
-1
```

# 题解

## 作者：qpzc (赞：6)

题意简洁明了，在此不再赘述。
## 思路：
如果我们每涂一个格子都判断整个矩阵有没有 $3 \times 3$ 的黑色矩阵，那时间复杂度为 $O(n^2m)$，显然超时，所以要考虑优化。

思考后可以发现，每涂一个格子所影响的只是**它和它周围的 $8$ 个格子**。所以我们只要判断当前这个格子和它周围的 $8$ 个格子有没有形成**以它为中心**的 $3 \times 3$ 的黑色矩阵就可以了。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
bool mp[1002][1002];//记录矩阵的状态
const int dir[9][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,0},{0,1},{1,-1},{1,0},{1,1}};//方向数组
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++){
        cin>>x>>y,mp[x][y]=true;//标记为黑格
        for(int j=0;j<9;j++){//搜索它周围的格子
            int xx=x+dir[j][0],yy=y+dir[j][1];
            bool ok=true;
            for(int k=0;k<9;k++){
                int xxx=xx+dir[k][0],yyy=yy+dir[k][1];
                if(!mp[xxx][yyy]){ok=false;break;}
            }   
            if(ok){cout<<i;return 0;}//若该格周围3*3的格子均为黑色，直接输出并结束程序
        }
    }
    cout<<-1;//无解则输出-1
    return 0;
}
```

---

## 作者：_ouhsnaijgnat_ (赞：2)

# 题目大意

有一个 $n\times n$ 的矩阵，初始时全部为黑。

你可以进行一个操作，将 $(x,y)$ 这个方格的颜色变为黑色。

经过 $m$ 次操作，让你求出第几次操作时黑色可以组成一个 $3\times3$ 的矩阵。

# 思路

首先，在第 $i$ 次操作时，它将 $(x_{i},y_{i})$ 这个方格染成黑色，这个操作要想组成 $3\times3$ 的矩阵，肯定是以 $(x_{i},y_{i})$ 为中心的 $5\times5$ 的矩阵。

所以我们只要遍历 $x_{i-2}$ 到 $x_{i+2}$，$y_{i-2}$ 到 $y_{i+2}$ 这些方格，判断是否能组成 $3\times3$ 的矩阵,如果到结束都组成不了，输出 $-1$ 就可以了。

此时，我们就将复杂度为 $O(N^2M)$，每进行一次操作就整个矩阵遍历的方法，优化成了复杂度为 $O(M)$，大大降低了时间。

$M$ 最大为 $10^5$，时间复杂度完全能过。

注意还要判读一下数组越界的问题。

---

## 作者：xuorange (赞：2)

题意：给一个 $n$ 和 $m$ ，代表有 $n \times n$ 的方格， $m$ 行输入给的格子，问到第几行时会出现 $3 \times 3$ 的方格都被走过。

思路：先把每一步的路都存起来，再暴力找哪个是 $3 \times 3$ 的，并找出这个 $3 \times 3$ 中最大的是第几步。

模拟题，暴力正好能过。

```
#include<iostream>
#include<cstring>
using namespace std;
int maze[1005][1005],qaq[1005][1005];
bool pd(int i,int j){
    if(maze[i][j]==1)
        if(maze[i-1][j]==1)
            if(maze[i+1][j]==1)
                if(maze[i][j-1]==1)
                    if(maze[i][j+1]==1)
                        if(maze[i-1][j-1]==1)
                            if(maze[i-1][j+1]==1)
                                if(maze[i+1][j-1]==1)
                                    if(maze[i+1][j+1]==1)return true;
    return false;
}
int main(){
    int n,m;
    while(cin>>n>>m){
        memset(maze,0,sizeof(maze));
        memset(qaq,0,sizeof(qaq));
        int flag=0;
        for(int i=0;i<m;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            qaq[a][b]=i+1;
            maze[a][b]=1;
        }
        int ans=1000005,tmp;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(pd(i,j)){
                    flag++;
                    tmp=qaq[i][j];
                    if(qaq[i-1][j]>tmp)tmp=qaq[i-1][j];
                    if(qaq[i+1][j]>tmp)tmp=qaq[i+1][j];
                    if(qaq[i][j-1]>tmp)tmp=qaq[i][j-1];
                    if(qaq[i][j+1]>tmp)tmp=qaq[i][j+1];
                    if(qaq[i-1][j-1]>tmp)tmp=qaq[i-1][j-1];
                    if(qaq[i-1][j+1]>tmp)tmp=qaq[i-1][j+1];
                    if(qaq[i+1][j-1]>tmp)tmp=qaq[i+1][j-1];
                    if(qaq[i+1][j+1]>tmp)tmp=qaq[i+1][j+1];
                    if(tmp<ans)ans=tmp;
                }
            }
        }
        if(flag)printf("%d\n",ans);
        else printf("-1\n");
    }
    return 0;
}
```

---

## 作者：CCDYJXZ (赞：2)

[CF203B传送门](https://www.luogu.com.cn/problem/CF203B)。

题意：

给出一个 $n \times n$ 的初始格子都为白色的矩阵。给出 $m$ 次操作，每次选定一个格子 $(x_i,y_i)$，并将这个格子涂成黑色。问最少第几次操作时才有一个 $3 \times 3$ 黑色矩阵。如果无解，则输出 $-1$。

思路：

暴力每次都要搜索整个矩阵，时间复杂度为 $O (n^2m)$。很明显超时了，但数据较水，勉强能过。

每将一个格子涂黑，只有它和他周围的八个格子会被影响。我们只需判断这个格子和它周围的八个格子的周围是否会形成一个 $3 \times 3$ 黑色矩阵。                                   



------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool aa[1001][1001];//状态数组，记录每个格子是否涂黑。
int a,s,x,y,d[4]={0,-1,0,1};
bool pan(int x,int y){//判断这个格子和周围八个格子是否有3*3的矩阵。
	int ax,ay;bool f=1;
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++){
			f=1;
			ax=x+d[i];
			ay=y+d[j];
			for(int l=1;l<=3;l++)	
				for(int h=1;h<=3;h++)
					if(!aa[ax+d[l]][ay+d[h]]){
						f=0;
						break;
					}
			if(f)
				return 1;
		}
	return 0;
}
int main(){
    cin>>a>>s;
    for(int i=1;i<=s;i++){
    	cin>>x>>y;//每次操作把当前格子标位黑色，并判断是否有3*3的黑色矩阵。
    	aa[x][y]=1; 
    	if(pan(x,y)){
    		cout<<i;//成立输出当前第几步。
    		return 0;
    	}
	}
	cout<<-1;//不成立输出-1。 
    return 0;
}
```
本人蒟蒻一位，如有不周之处请见谅。

---

## 作者：Ninelife_Cat (赞：1)

### 题目大意：

有一个 $n \times n$ 的矩阵，初始时矩阵的所有格子都是白色的。

现在你进行了 $m$ 次操作，每次操作会选定一个格子 $(x_i,y_i)$，并将这个格子涂成黑色。

请求出你最少需要几次操作才能涂出一个 $3 \times 3$ 的黑色矩阵，如果无解，输出 $-1$。

### 思路：

如果每涂黑一个格子就去检验一遍，那么时间复杂度是 $O(n^2m)$ 的，显然过不了。

所以我们转换一下思路，把全部格子涂完之后再去检验。

设 $vis[x][y]=z$ 表示格子 $(x,y)$ 在第 $z$ 次操作时被涂黑，所以涂黑一个 $3 \times 3$ 的矩阵所需的最少操作次数就是这个矩阵中的 $vis$ 的最大值。

再遍历整个 $n \times n$ 的矩阵，找出最小值就行了。

如果找不出最小值，说明无解。

### 代码：
```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ri register
#define int long long
#define inf 2147483647
#define mp(x,y) make_pair((x),(y))
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	int x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return f?-x:x;
}
const int N=1e3+10;
int n,m,x,y,vis[N][N],ans=inf;
signed main()
{
	n=read();m=read();
	for(ri int i=1;i<=m;++i)
		x=read(),y=read(),vis[x][y]=i;
	for(ri int i=1;i<=n-2;++i)
		for(ri int j=1;j<=n-2;++j)
			if(vis[i][j]&&vis[i+1][j]&&vis[i+2][j]&&vis[i][j+1]&&vis[i+1][j+1]&&vis[i+2][j+1]&&vis[i][j+2]&&vis[i+1][j+2]&&vis[i+2][j+2])
				ans=min(ans,max(max(max(max(max(max(max(max(vis[i][j],vis[i+1][j]),vis[i+2][j]),vis[i][j+1]),vis[i+1][j+1]),vis[i+2][j+1]),vis[i][j+2]),vis[i+1][j+2]),vis[i+2][j+2]));
	cout<<(ans==inf?-1:ans);//记得判无解
	return 0;
}

---

## 作者：liupan2010 (赞：1)

思路：

尽管 $\Theta(n^2m)$ 也能通过该题，但是我们应该思考正解。

仔细思考，可以发现：涂了一个格子只会影响相邻的 $8$ 个格子，所以我们只要判断涂了的格子周围的 $8$ 个格子有没有形成 $3\times3$ 的矩阵即可。如果形成，输出操作次数即可。否则在 $m$ 次循环后输出 $-1$。

代码：

和其他题解的很像，就不贴了。

---

## 作者：yingkeqian9217 (赞：1)

### 前言：
鉴于某些题解太过于暴力美学——咳咳，是干脆利落，我这里提供一种较为~~正常~~美观一些的写法。

### 题意：
有一个 $n \times n$ 的矩阵，初始时矩阵的所有格子都是白色的。

现在你进行了 $m$ 次操作，每次操作会选定一个格子 $(x_i,y_i)$ ，并将这个格子涂成黑色。

请求出你最少需要几次操作才能涂出一个 $3 \times 3$ 的黑色矩阵，如果无解，输出 $-1$ 。

### 分析：
这题很容易想到先存储再判断，毕竟再好的CPU也经不起 $O(n^2m)$ 的风吹雨打。
		
所谓“先存储再判断”，就是在读入时利用数组模拟整个矩阵，再记录步数。也就是说，当第 $k$ 步读入为 $x,y$ 时，使矩阵数组 $a_{x,y}=k$ 。

但存储时要注意区分已经涂的和未涂的，还有就是求最小的话初始值要设好。

接下来再对 $a$ 进行遍历，枚举 $3 \times 3$ 矩阵的中心，先判断此矩阵是否是全黑的，如果是，就取最大值，因为只有到第最大值步时，整个矩阵才能全黑。

遍历 $a$ 时可以考虑用方向数组 $dx,dy$ 判断，不过这里有些特殊，自己 $(0,0)$ 也要算上哦。

### AC_CODE:
```
#include<bits/stdc++.h>
using namespace std;
int dx[9]={0,0,0,1,1,1,-1,-1,-1};
int dy[9]={0,1,-1,0,1,-1,0,1,-1};//方向数组
int n,m,ans=INT_MAX,a[2001][2001];//初始化，a数组记录步数
int main(){
	scanf("%d%d",&n,&m);//现场推销scanf，又快又方便
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		a[x][y]=i;//预处理
	}
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=n;j++){
	 	int x=0;//记录最小步数
	 	for(int k=0;k<9;k++)
	 	 if(a[i+dx[k]][j+dy[k]])
	 	  x=max(x,a[i+dx[k]][j+dy[k]]);
	 	 else{//如果是白格子，直接跳出
	 	 	x=-1;
	 	 	break;
		  }
		if(x!=-1) ans=min(ans,x); //注意if要加上
	 }
	if(ans!=INT_MAX) printf("%d\n",ans);
	else printf("-1\n");//不可行
	return 0;
}
```



---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF203B)

一道模拟题。

如果每涂一个格子就判断整个矩阵，那时间复杂度显然会炸。

我们每涂一个格子，影响的应该只是以这个格子为中心的 $3 \times 3$ 矩阵，判断以这些点为中心的话会不会涂出 $3 \times 3$ 的矩阵即可。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, m;
int dx[9] = {1, 1, 1, -1, -1, -1, 0, 0, 0}; // x 坐标变化
int dy[9] = {0, -1, 1, 0, -1, 1, 0, -1, 1}; // y 坐标变化
bool vis[1005][1005];
bool check(int x, int y) {
    for (int i = 0; i < 9; i++) {
        if (!vis[x + dx[i]][y + dy[i]]) return 0;
    }
    return 1;
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        vis[x][y] = 1;
        for (int j = 0; j < 9; j++) {
            if (check(x + dx[j], y + dy[j])) {
                cout << i;
                return 0; // 直接结束程序
            }
        }
    }
    cout << -1;
    return 0;
}

```


---

## 作者：Ice_lift (赞：0)

## 题意

有一个 $n\times n$ 大小的矩阵，初始均为 $0$，现在，给出 $m$ 个操作，使 $(x,y)$  变为 $1$，问执行到第几个操作时存在一个 $3\times3$ 的全 $1$ 子矩阵。

## 思路

最容易想到的就是暴力枚举，每执行一次操作就在矩阵中判断是否存在题目要求的子矩阵，但是这样时间复杂度为 $O(mn^2)$ 一定会超时。

所以，我们不妨从当前操作的格子出发，判断包含它的 $3 \times 3$ 子矩阵是否为全 $1$ 子矩阵即可。如果是，则直接输出当前操作编号，如果执行完 $m$  次操作后仍然不存在符合要求的子矩阵，则直接输出 $-1$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3000 + 5;
int n, m, a[MAXN][MAXN], x, y;//a数组储存矩阵
int dx[10] = {1, 1, 1, -1, -1, -1, 0, 0, 0};//3*3矩阵x坐标变化
int dy[10] = {0, -1, 1, 0, -1, 1, 0, -1, 1};//3*3矩阵y坐标变化
bool check(int x, int y) {//判断条件
	for (int i = 0; i < 9; i++) {
		if (!a[x + dx[i]][y + dy[i]]) {
			return false;
		}
	}
	return true;
}
signed main() {
	scanf("%lld%lld", &n, &m);

	for (int i = 1; i <= m; i++) {
		scanf("%lld%lld", &x, &y);
		a[x][y] = 1;//标记
		for (int j = 0; j < 9; j++) {//依次讨论包含（x,y）的矩阵中心点
			if (check(x + dx[j], y + dy[j])){//判断
				printf("%lld", i);//输出编号
				return 0;
			}
		}
	}
	printf("-1");
	return 0;
}
```


---

## 作者：zhuweiqi (赞：0)

**方法一：暴力枚举**

时间复杂度：$O(n^2 m)$

思路：对于每次操作，先把对应的格子涂黑，再在整个矩阵中搜索有没有一个 $3\times 3$ 的黑色矩阵，如果有，输出答案并退出程序，如果没有就继续执行下一次操作，如果 $m$ 次操作都执行完了还没有找到一个 $3\times 3$ 的黑色矩阵就输出 $-1$。

**方法二：优化枚举**

不难发现，对于每次操作的 $(x_i,y_i)$，我们只需要搜索有没有以它周围八格或者它本身为中心的 $3\times 3$ 的黑色矩阵就可以了，因为在本次操作结束之后必然不会增加一个以其它位置为中心的 $3\times 3$ 的黑色矩阵，这样我们就可以把时间复杂度优化到 $O(m)$ 了，通过本题肯定是绰绰有余了，当然，我们还可以用数组继续优化，用空间换时间，用 $f_{i,j}$ 记录在 $(i,j)$ 周围（包括它本身）一共有多少个黑色的格子，优化了判断的时间。上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int f=1,n=0;
	char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		n=(n<<3)+(n<<1)+(c^48);
		c=getchar();
	}
	return n*f;
}
int a[1005][1005];
int f[1005][1005];
int dir[9][2]={{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1},{0,0}};
int main(){
	int n,m,x,y;
	n=read(),m=read();
	for(int ans=1;ans<=m;ans++){
		x=read(),y=read();
		if(a[x][y]==1) continue;
		for(int i=0;i<9;i++){
			int nx=x+dir[i][0];
			int ny=y+dir[i][1];
			f[nx][ny]++;
			if(f[nx][ny]==9){
				printf("%d",ans);
				return 0;
			}
		}
	}
	printf("%d",-1);
	return 0;
}
```

---

