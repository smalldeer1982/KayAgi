# L-shapes

## 题目描述

An L-shape is a figure on gridded paper that looks like the first four pictures below. An L-shape contains exactly three shaded cells (denoted by \*), which can be rotated in any way.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1722F/c4bb8e8c5c94521e87ed2d5ba5ef373384bb7be7.png)You are given a rectangular grid. Determine if it contains L-shapes only, where L-shapes can't touch an edge or corner. More formally:

- Each shaded cell in the grid is part of exactly one L-shape, and
- no two L-shapes are adjacent by edge or corner.

For example, the last two grids in the picture above do not satisfy the condition because the two L-shapes touch by corner and edge, respectively.

## 样例 #1

### 输入

```
10
6 10
........**
.**......*
..*..*....
.....**...
...*.....*
..**....**
6 10
....*...**
.**......*
..*..*....
.....**...
...*.....*
..**....**
3 3
...
***
...
4 4
.*..
**..
..**
..*.
5 4
.*..
**..
....
..**
..*.
3 2
.*
**
*.
2 3
*..
.**
3 2
..
**
*.
3 3
.**
*.*
**.
3 3
..*
.**
..*```

### 输出

```
YES
NO
NO
NO
YES
NO
NO
YES
NO
NO```

# 题解

## 作者：Binary_Lee (赞：11)

## [题面传送门](https://www.luogu.com.cn/problem/CF1722F)


其实这题根本不用搜索，有耐心即可。

可以发现，在 $n\times m$ 范围内扫，可能合法的只有以下四种情况，其中蓝色代表示是 `*`，红色表示不能是 `*`，其中黄色五角星表示当前 $i,j$ 的位置。

![](https://cdn.luogu.com.cn/upload/image_hosting/vjucu7f9.png)

所以只要把 `*` 标记为 $1$，全图扫一遍，发现合法就给它变 $0$，看最后有没有 $1$ 剩余即可。


Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n,m,a[55][55];
char c;
void search(int i,int j){
	if(a[i+1][j]&&a[i+1][j+1]&&!a[i-1][j-1]&&!a[i-1][j]&&!a[i-1][j+1]&&
	   !a[i][j-1]&&!a[i][j+1]&&!a[i][j+2]&&!a[i+1][j-1]&&!a[i+1][j+2]&&
	   !a[i+2][j-1]&&!a[i+2][j]&&!a[i+2][j+1]&&!a[i+2][j+2]){
		a[i][j]=a[i+1][j]=a[i+1][j+1]=0;
		return ;
	}
	if(a[i+1][j-1]&&a[i+1][j]&&!a[i-1][j-1]&&!a[i-1][j]&&!a[i-1][j+1]&&
	   !a[i][j-2]&&!a[i][j-1]&&!a[i][j+1]&&!a[i+1][j-2]&&!a[i+1][j+1]&&
	   !a[i+2][j-2]&&!a[i+2][j-1]&&!a[i+2][j]&&!a[i+2][j+1]){
		a[i][j]=a[i+1][j-1]=a[i+1][j]=0;
		return ;
	}
	if(a[i][j+1]&&a[i+1][j+1]&&!a[i-1][j-1]&&!a[i-1][j]&&!a[i-1][j+1]&&
	   !a[i-1][j+2]&&!a[i][j-1]&&!a[i][j+2]&&!a[i+1][j-1]&&!a[i+1][j]&&
	   !a[i+1][j+2]&&!a[i+2][j]&&!a[i+2][j+1]&&!a[i+2][j+2]){
		a[i][j]=a[i][j+1]=a[i+1][j+1]=0;
		return ;
	}
	if(a[i][j+1]&&a[i+1][j]&&!a[i-1][j-1]&&!a[i-1][j]&&!a[i-1][j+1]&&
	   !a[i-1][j+2]&&!a[i][j-1]&&!a[i][j+2]&&!a[i+1][j-1]&&!a[i+1][j+1]&&
	   !a[i+1][j+2]&&!a[i+2][j-1]&&!a[i+2][j]&&!a[i+2][j+1]){
		a[i][j]=a[i][j+1]=a[i+1][j]=0;
		return ;
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c;
			if(c=='*') a[i][j]=1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==1) search(i,j);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==1){
				printf("NO\n");
				return ;
			}
		}
	}
	printf("YES\n");
}
int main(){
	scanf("%d",&T);
	while(T--) solve();
    return 0;
}
```


---

## 作者：lihanwen12 (赞：5)

题目大意：  
定义 L 型为 $2\times 2$ 的格子缺了任意一个角。现在给定一个 $n$ 行 $m$ 列的由 ```.``` 或者 ```*``` 构成的矩形，询问这个矩形是否由若干个 L 型构成且这些 L 型之间没有点或者边相接触。  

解题思路：  
扫描每一个格子，看它是否能作为 L 型的一角。如果可以，检查这个 L 型四周与其点或者边相接触的格子有没有字符 ```*```，然后将构成这个 L 型的三个格子标记为使用过。最终如果每一个字符 ```*``` 所在的格子都被标记为使用过并且没有发生 L 型与其他格子点或者边相接触则按照题目要求输出 ```YES``` 否则输出 ```NO```。  

代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}
long long t,n,m,leixing;
char ch[60][60];
bool f[60][60];
bool ans;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=50;i++)
			for(int j=1;j<=50;j++)
				ch[i][j]='.';
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>ch[i][j];
		memset(f,0,sizeof(f));
		ans=true;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				leixing=0;
				if(ch[i][j]=='*'){
					if(ch[i-1][j]==ch[i][j] && ch[i][j+1]==ch[i][j])leixing=1;
					if(ch[i-1][j]==ch[i][j] && ch[i][j-1]==ch[i][j])leixing=2;
					if(ch[i][j-1]==ch[i][j] && ch[i+1][j]==ch[i][j])leixing=3;
					if(ch[i][j+1]==ch[i][j] && ch[i+1][j]==ch[i][j])leixing=4;
					if(leixing==1){
						f[i][j]=1;
						f[i-1][j]=1;
						f[i][j+1]=1;
					}
					if(leixing==2){
						f[i][j]=1;
						f[i-1][j]=1;
						f[i][j-1]=1;
					}
					if(leixing==3){
						f[i][j]=1;
						f[i][j-1]=1;
						f[i+1][j]=1;
					}
					if(leixing==4){
						f[i][j]=1;
						f[i][j+1]=1;
						f[i+1][j]=1;
					}
				}
				if(leixing==1){
					for(int x=i-2;x<=i+1;x++)
						for(int y=j-1;y<=j+2;y++){
							if(x==i-2 && y==j+2)continue;
							if(x==i && y==j)continue;
							if(x==i-1 && y==j)continue;
							if(x==i && y==j+1)continue;
							if(x>=1 && x<=n && y>=1 && y<=m)
								if(ch[x][y]=='*')ans=false;
						}
				}
				if(leixing==2){
					for(int x=i-2;x<=i+1;x++)
						for(int y=j-2;y<=j+1;y++){
							if(x==i-2 && y==j-2)continue;
							if(x==i && y==j)continue;
							if(x==i-1 && y==j)continue;
							if(x==i && y==j-1)continue;
							if(x>=1 && x<=n && y>=1 && y<=m)
								if(ch[x][y]=='*')ans=false;
						}
				}
				if(leixing==3){
					for(int x=i-1;x<=i+2;x++)
						for(int y=j-2;y<=j+1;y++){
							if(x==i+2 && y==j-2)continue;
							if(x==i && y==j)continue;
							if(x==i && y==j-1)continue;
							if(x==i+1 && y==j)continue;
							if(x>=1 && x<=n && y>=1 && y<=m)
								if(ch[x][y]=='*')ans=false;
						}
				}
				if(leixing==4){
					for(int x=i-1;x<=i+2;x++)
						for(int y=j-1;y<=j+2;y++){
							if(x==i+2 && y==j+2)continue;
							if(x==i && y==j)continue;
							if(x==i && y==j+1)continue;
							if(x==i+1 && y==j)continue;
							if(x>=1 && x<=n && y>=1 && y<=m)
								if(ch[x][y]=='*')ans=false;
						}
				}
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(ch[i][j]=='*' && f[i][j]==0)ans=false;
		if(ans)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

```

---

## 作者：CodingShark (赞：4)

~~唉，我真是太废了，比赛的时候竟然没有做出来。~~

我来一发搜索的题解。

首先，对于棋盘上的任意一个八连通块，如果它的大小不为 3，则结果必然为 `No`，那么我们进一步考虑，在连通块大小都为 3 的情况下，有以下两种类型的情况也为 `No`：

```
...
***
...
```

```
*..
.*.
..*
```

第一种的判定比较好办，只需要将每个横的或竖的的图形枚举出来一一判定即可，但第二种情况似乎有很多，不过我们其实只需要枚举所有 2 x 2 的小正方形，判断其是否仅在对角线上有 `*` 符号就可以了。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, m, dir[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
char arr[55][55];
bool vis[55][55];
 
int bfs(int sx, int sy)
{
    int res = 0;
    queue<pair<int, int>> q;
    q.push({sx, sy}), vis[sx][sy] = true;
    while (q.size())
    {
        auto cur = q.front();
        q.pop(), res++;
        for (int i = 0; i < 8; i++)
        {
            int tx = cur.first + dir[i][0], ty = cur.second + dir[i][1];
            if (1 <= tx && tx <= n && 1 <= ty && ty <= m && !vis[tx][ty])
                vis[tx][ty] = true, q.push({tx, ty});
        }
    }
    return res;
}
 
bool check()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!vis[i][j] && bfs(i, j) != 3)
                return false;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (arr[i][j] == '*' && arr[i][j] == arr[i + 1][j] && arr[i][j] == arr[i + 2][j])
                return false;
            if (arr[i][j] == '*' && arr[i][j] == arr[i][j + 1] && arr[i][j] == arr[i][j + 2])
                return false;
            if (arr[i][j] == '*' && arr[i][j] == arr[i + 1][j + 1] && arr[i][j] != arr[i + 1][j] && arr[i][j] != arr[i][j + 1])
                return false;
            if (arr[i][j] == '*' && arr[i][j] == arr[i + 1][j - 1] && arr[i][j] != arr[i + 1][j] && arr[i][j] != arr[i][j - 1])
                return false;
        }
    return true;
}
 
int main()
{
    cin >> T;
    while (T--)
    {
        memset(vis, false, sizeof vis), memset(arr, 0, sizeof arr);
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                cin >> arr[i][j];
                if (arr[i][j] == '.')
                    vis[i][j] = true;
            }
        puts(check() ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：Lantrol (赞：1)

《关于我的繁琐思路和玄学代码》

昨天赛后 3min 过 F。还是因为思路乱，代码比较复杂，最后差点就调出来了。

题面有点长，在这就不写了。直接看思路。

### 思路

先判断有没有不归属于任何 L 形的“单点”。枚举所有 $2×2$ 的区域，每找到一个 L 形，就给 L 形中所有的点打上标记。同时判断是否有同属于两个 L 形的点。最后扫一遍整个数组，如果发现没被打标记的点，就判掉。

再暴力判断 L 形四周是否有其他点。还需要根据 L 形的朝向分类讨论。

再加一点玄学特判，可以跑的快点。

### 代码

96行，又臭又长。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool mp[105][105],vis[105][105];
int h,w;

int isl(int x,int y){
	int cnt=0,xz,yz;
	for(int i=x;i<=x+1;i++){
		for(int j=y;j<=y+1;j++){
			cnt+=mp[i][j];
			if(!mp[i][j]){
				xz=i;yz=j;
			}
		}
	}
	if(cnt!=3){
		if(mp[x+1][y]&&mp[x][y+1]){
			return -1;
		}
		if(mp[x][y]&&!vis[x][y]){
			return -1;
		}
		return 0;
	}
	for(int i=x;i<=x+1;i++){
		for(int j=y;j<=y+1;j++){
			if(vis[i][j]){
				return -1;
			}
			vis[i][j]=mp[i][j];
		}
	}
	for(int i=x-1;i<=x+2;i++){
		for(int j=y-1;j<=y+2;j++){
			if(x<=i&&i<=x+1&&y<=j&&j<=y+1){
				continue;
			}
			if(mp[i][j]){
				if(xz==x&&yz==y&&i==x-1&&j==y-1){
					continue;
				}
				if(xz==x+1&&yz==y&&i==x+2&&j==y-1){
					continue;
				}
				if(xz==x+1&&yz==y+1&&i==x+2&&j==y+2){
					continue;
				}
				if(xz==x&&yz==y+1&&i==x-1&&j==y+2){
					continue;
				}
				return -1;
			}
		}
	}
	return 1;
}

void solve(){
	memset(mp,0,sizeof(mp));
	memset(vis,0,sizeof(vis));
	cin>>h>>w;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			char c;
			cin>>c;
			if(c=='*'){
				mp[i][j]=1;
			}
		}
	}
	for(int i=1;i<=h-1;i++){
		for(int j=1;j<=w-1;j++){
			if(isl(i,j)==-1){
				cout<<"NO"<<endl;
				return;
			}
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			if(!vis[i][j]&&mp[i][j]){
				cout<<"NO"<<endl;
				return;
			}
		}
	}
	cout<<"YES"<<endl;
}

int main(){
	int t;
	cin>>t;
	while(t--){
	    solve();
	}
}
```


---

## 作者：zsseg (赞：1)

### Solution
并查集，维护若干个 $\text *$ 组成的连通块，若有下列情况之一，即不符合要求:

* 一个连通块大小不为 $3$

* 一个连通块内的元素在一条直线上

* 两个在同一对角线上的元素不在同一个连通块内

单组数据时间复杂度 $\varTheta(n^2\log^2n)$ 
### Code
```cpp
#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
#define g(i,a,b) for(int i=a;i>=b;i--)
#define ll long long
#define end() putchar('\n')
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return f?x:-x;
}
inline void write(int x,char end=' '){
    static int k[31];
    int f=0;
    if(x<0)x=-x,putchar('-');
    do{k[f++]=x%10,x/=10;}while(x);
    while(f)putchar(k[--f]^'0');
    putchar(end);
}
int T=read(),n,m,fa[2510],siz[2510];
inline int pos(int x,int y){return (x-1)*m+y;}
char s[51][51];
//并查集板子
inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
inline void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	if(siz[fx]>siz[fy])swap(fx,fy);
	fa[fx]=fy;
	siz[fy]+=siz[fx];
}
int main(){
	while(T--){
		n=read(),m=read();
		f(i,1,n*m)siz[i]=1,fa[i]=i;
		f(i,1,n)scanf("%s",s[i]+1);
		f(i,1,n)f(j,1,m){
			if(s[i][j]=='*'){
            //合并连通块
				if(s[i-1][j]=='*')merge(pos(i,j),pos(i-1,j));
				if(s[i][j-1]=='*')merge(pos(i,j),pos(i,j-1));
			}
		}
		int flag=0;
		f(i,1,n)f(j,1,m){
			if(flag)break;
			if(s[i][j]=='*'){
           		//条件1
				if(siz[find(pos(i,j))]!=3)flag=1;
                //条件2
				if(j!=m&&s[i][j-1]=='*'&&s[i][j+1]=='*')flag=1;
				if(i!=n&&s[i-1][j]=='*'&&s[i+1][j]=='*')flag=1;
                //条件3
				if(s[i-1][j-1]=='*'){
					if(find(pos(i,j))!=find(pos(i-1,j-1)))flag=1;
				}
				if(j!=m&&s[i-1][j+1]=='*'){
					if(find(pos(i,j))!=find(pos(i-1,j+1)))flag=1;
				}
			}
		}
		puts(flag?"No":"Yes");
	}
	return 0;
}
//O(Tnmlog(nm))
```


---

## 作者：include_BM (赞：1)

先判断是否有 $2$ 个 L 形相邻：

+ 若 $2$ 个 L 形的角相邻，就会在相邻处形成下面两种情况之一：

```
.*
*.
```

```
*.
.*
```

+ 若 $2$ 个 L 形的边相邻，就会在相邻处形成下面两种情况之一：

```
***
```

```
*
*
*
```

现在网格中没有相邻的 L 形，那么对于每个 $2\times 2$ 的方格，若这个方格内恰好有 $3$ 个 $\texttt{*}$，由于任意 $2$ 个 L 形不相邻，这 $3$ 个 $\texttt{*}$ 必然不会是 $2$ 个 L 形拼在一起得到的，所以这个方格内恰好是一个 L 形，然后我们将这个 L 形从网格中删去。

经过上述操作后网格中的每个 L 形都已被删去，那么剩下的 $\texttt{*}$ 就一定不是 L 形的组成部分，说明网格中存在非 L 形。

```cpp
n=read(),m=read(),ok=1;
for(int i=1;i<=n;++i) scanf("%s",s[i]+1);
for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j){
        if(i!=1&&j!=m&&s[i][j]=='*'&&s[i-1][j+1]=='*'&&s[i-1][j]=='.'&&s[i][j+1]=='.') ok=0;
        if(i!=n&&j!=m&&s[i][j]=='*'&&s[i+1][j+1]=='*'&&s[i+1][j]=='.'&&s[i][j+1]=='.') ok=0;
        if(i+2<=n&&s[i][j]=='*'&&s[i+1][j]=='*'&&s[i+2][j]=='*') ok=0;
        if(j+2<=m&&s[i][j]=='*'&&s[i][j+1]=='*'&&s[i][j+2]=='*') ok=0;
    }
for(int i=1;i<n;++i)
    for(int j=1;j<m;++j){
        int num=(s[i][j]=='*')+(s[i+1][j]=='*')+(s[i][j+1]=='*')+(s[i+1][j+1]=='*');
        if(num==3) s[i][j]=s[i+1][j]=s[i][j+1]=s[i+1][j+1]='.';
    }
for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j) if(s[i][j]=='*') ok=0;
ok?puts("YES"):puts("NO");
```

---

## 作者：Micnation_AFO (赞：0)

有点乱搞的做法，总之这个做法细节有点多。

首先可以发现，如果有连续三个的在一行或者在一列，那么肯定无解。

然后，对于下面这个情况：
```
1*
*2
```
若位置 $1$ 和 $2$ 都不为 $\texttt{*}$，则肯定无解。

上面情况的对称情况同理。所以先扫描一遍判断一下：
```cpp
	bool flag = false;
    	//判断是否在同一行
        for (int i = 1; i <= n; i++) 
            for (int j = 3; j <= m; j++) 
                if (ch[i][j] == '*' && ch[i][j - 1] == '*' && ch[i][j - 2] == '*') { flag = true; break; }
        ////判断是否在同一列
        for (int i = 3; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (ch[i][j] == '*' && ch[i - 1][j] == '*' && ch[i - 2][j] == '*') { flag = true; break; }
        //判断斜线
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (ch[i][j] == '*' && ch[i + 1][j + 1] == '*' && ch[i][j + 1] != '*' && ch[i + 1][j] != '*') {
                    flag = true;
                    break;
                }
        for (int i = 1; i < n; i++)
            for (int j = 2; j <= m; j++) 
                if (ch[i][j] == '*' && ch[i + 1][j - 1] == '*' && ch[i][j - 1] != '*' && ch[i + 1][j] != '*') {
                    flag = true;
                    break;
```

判断完之后，用 $t_{i, j}$ 表示以 $(i, j)$ 为中心的 $3\times 3$ 的方格中 $\texttt{*}$ 的数量。若大于 $3$，则肯定不合法。若小于 $3$，则不用管。若等于 $3$，那么用一个函数判断一下是不是组成了 $\texttt{L}$：
```cpp
bool find(int i, int j) {
    for (int I = i - 1; I <= i + 1; I++)
        for (int J = j - 1; J <= j + 1; J++)
            if (ch[I][J] != '*') continue;
            else {
                if (I != i - 1 && J != j - 1 && ch[I][J - 1] == '*' && ch[I - 1][J] == '*') return true;
                else if (I != i + 1 && J != j + 1 && ch[I][J + 1] == '*' && ch[I + 1][J] == '*') return true;
                else if (J != j - 1 && I != i + 1 && ch[I][J - 1] == '*' && ch[I + 1][J] == '*') return true;
                else if (I != i - 1 && J != j + 1 && ch[I - 1][J] == '*' && ch[I][J + 1] == '*') return true;
            }
    return false;
}
```

如果是，则清空这个 $3\times 3$ 的块。否则不用管。

最后再扫描一遍整个地图，如果有 $\texttt{*}$，就不合法。

完整代码：[Link](https://www.luogu.com.cn/paste/me78dfd3)。

---

