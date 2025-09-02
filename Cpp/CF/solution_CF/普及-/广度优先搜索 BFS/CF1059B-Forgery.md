# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 3
###
###
###
```

### 输出

```
NO```

## 样例 #3

### 输入

```
4 3
###
###
###
###
```

### 输出

```
YES```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......
```

### 输出

```
YES```

# 题解

## 作者：Abyss_Bright (赞：15)

```cpp
/*
一、题意
给一张n，m的地图，初始的时候都一个样。
然后然后你可以染色，选定一个格子，将其周围的八个格子染成#。
但除它自己以外，而且你可以染色无数次。 
输入目标状态，问你是否能达到这个状态。
二、思路
题意已经很明确了。
我们只需要开两个数组，一个用来存目标状态，一个用来染色，最后比对就行了。
三、具体操作
输入地图后，枚举地图的格子，若能染色就染色，不能就枚举下一个。
如果目标状态不是'#'，不染色。 
如果染色范围出了边界，不染色。
如果都没有，就将周围8个格子染成#。
染色完毕后，与目标状态比对。
若一样，输出YES，不一样，输出NO。
四、代码
代码里有一些小细节。
以下是AC代码：
*/
#include<bits/stdc++.h>
using namespace std;
int dx[8]={1,1,-1,-1,0,0,1,-1};//移动数组就不说啦。
int dy[8]={1,-1,1,-1,1,-1,0,0}; 
int n,m;
char mubiao[1005][1005];//存目标地图。 
char bian[1005][1005];//存我们用来搜索的地图，也是方便搜完后比对。
bool bidui()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(mubiao[i][j]!=bian[i][j])//一个一个挨着比对。 
			return false;//如果有不一样的，说明不行，返回false。 
		} 
	}
	return true;//如果没有不一样的，说明可以，返回true。 
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>mubiao[i][j];//输入目标地图。 
			bian[i][j]='.';//要改变的地图，初始都是'.'。 
		}
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
			{
				int biao=1;//作为标记。 
				for(int z=0;z<8;z++)
				{
					int mx=x+dx[z];
					int my=y+dy[z];
					if(mx>n||mx<=0||my>m||my<=0)//如果出了边界，打标记，不能染色。
					{
						biao=0;
						break;
					}
					else if(mubiao[mx][my]!='#')//如果目标状态不是'#'，打标记，不能染色。
					{
						biao=0;
						break;
					}
				}
				if(biao==0)//如果上面被标记，选下一个点。 
				continue;
				for(int z=0;z<8;z++)//没有就染色。 
				{
					int mx=x+dx[z];
					int my=y+dy[z];
					bian[mx][my]='#';//全部都染上。
				}
			}
	if(bidui())//比对。
	cout<<"YES";//可以输出YES。
	else
	cout<<"NO";//不能输出NO。
	return 0;
}

```


---

## 作者：「已注销」 (赞：11)

枚举所有$(n-2)(m-2)$个圈，如果目标局面中这个圈都是`#`就覆盖，涂完之后判断两张图是否相等

$s$是初始地图，$a$是目标
```cpp
#include<iostream>
using namespace std;
int n,m,dx[]={0,0,0,1,1,2,2,2},dy[]={0,1,2,0,2,0,1,2};
string s[1001],a[1001];
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        s[i]=a[i];
        for(int j=0;j<m;++j)s[i][j]='.';
    }
    for(int i=1;i<=n-2;++i)
        for(int j=0;j<m-2;++j){
            bool flag=true;
            for(int k=0;k<8;++k)
                if(a[i+dx[k]][j+dy[k]]!='#'){
                    flag=false;
                    break;
                }
            if(flag)
                for(int k=0;k<8;++k)
                    s[i+dx[k]][j+dy[k]]='#';    
        }
    for(int i=1;i<=n;++i)
        for(int j=0;j<m;++j)
            if(a[i][j]!=s[i][j]){
                cout<<"NO";
                return 0;
            }    
    cout<<"YES";        
}
```

---

## 作者：Forever1507 (赞：9)

~~关于好端端的一道枚举题被教练强制用来复习深搜这件事~~

好了步入正题，既然题目中说你可以染色**无数次**，那么应该很容易想到，只要出现了一个点在目标图中是被 `#` 围成了一个圈的并且周围一圈都没有越界，那么就在当前图中染掉，然后去到下一个点。

全部染完之后与目标图比对一下就行了，一样就输出 `YES` ,反之则 `NO` 。

策略很简单，但是找到满足条件的点有两种方法：枚举或深搜。

当然个人比较推荐枚举法，深搜的话要多开一个 `bool vis[1005][1005];` 空间多了不少，虽然这道题里不会 `MLE` 但是养成省空间的习惯是很有必要的。深搜纯粹是老师的要求才会去打的。

枚举：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char want[1005][1005],now[1005][1005];
int dx[8]={0,0,1,1,-1,-1,1,-1};
int dy[8]={1,-1,1,-1,1,-1,0,0};//位移数组
bool cmp(){//比对
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(want[i][j]!=now[i][j])return 0;
		}
	}
	return 1;
}
void solve(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			bool flag=0;
			for(int k=0;k<=7;k++){
				int mx=i+dx[k];
				int my=j+dy[k];
				if(mx<=0||mx>n||my<=0||my>m||want[mx][my]=='.'){
					flag=1;//边界和当前点的状态要判断
					break;
				}
			}
			if(flag)continue;
			for(int k=0;k<=7;k++){//染色
				int mx=i+dx[k];
				int my=j+dy[k];
				now[mx][my]='#';
			}
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>want[i][j];
			now[i][j]='.';
		}
	}
	solve();
	string s=(cmp())?"YES":"NO";//三目运算符
   /*
   这里的三目运算符可以理解为：
   if(cmp()==1)s="YES";
   else s="NO";
   但是三目更短，跑得也更快。
   */
	cout<<s;
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/51989912)

深搜：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char want[1005][1005],now[1005][1005];
int dx[8]={0,0,1,1,-1,-1,1,-1};
int dy[8]={1,-1,1,-1,1,-1,0,0};
bool vis[1005][1005];
bool cmp(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(want[i][j]!=now[i][j])return 0;
		}
	}
	return 1;
}
void solve(int x,int y){
	bool flag=0;
	for(int k=0;k<=7;k++){
		int mx=x+dx[k];
		int my=y+dy[k];
		if(mx<=0||mx>n||my<=0||my>m||want[mx][my]=='.'){
			flag=1;
			break;
		}
	}
	for(int k=0;k<=7;k++){
		int mx=x+dx[k];
		int my=y+dy[k];
		if(!flag){	
			now[mx][my]='#';
		} 	
		if(mx<=0||mx>n||my<=0||my>m||vis[mx][my]){
			continue;
		}
		vis[mx][my]=1;
		solve(mx,my);
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>want[i][j];
			now[i][j]='.';
		}
	}
	solve(1,1);//随便从那个点开始都一样
	string s=(cmp())?"YES":"NO";
	cout<<s;
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/51990139)

~~显然深搜无论在时间还是空间上都劣不少，仅供参考。~~

---

## 作者：zlpiscoming (赞：5)

### AC题解
 这道问题的解法主要在于当把一个'.'变成'#'之后无法将其变回来，也就是一旦一个'.'变成'#'之后就没法回来了，所以要解决这道问题关键在于，针对目标图形枚举所有可以打上图案的地方，并在这些地方都打上图案，这样即使重复打图案也没关系，因为图案不会因为多次打上而消失，而假如所有这些可以打上图案的地方都打上图案之后，还得不到目标图形，及说明永远都无法得到原图形。
 
 
##  以下是我的AC代码（没有任何算法）
 ```
#include<bits/stdc++.h>
using namespace std;
char graph[1000][1000];
char now[1000][1000];
int ok(int x,int y,int n,int m){
	if(x<1||y<1||x>n-2||y>m-2) return 0;
	else{
		if(graph[x-1][y-1]=='#'&&graph[x-1][y+1]=='#'&&graph[x-1][y]=='#'&&graph[x][y-1]=='#'
		&&graph[x+1][y-1]=='#'&&graph[x+1][y+1]=='#'&&graph[x][y+1]=='#'&&graph[x+1][y]=='#')
		return 1;
		else return 0;
	}
}
void write(int i,int j){
	now[i-1][j-1]='#';now[i-1][j+1]='#';now[i-1][j]='#';now[i][j-1]='#';
	now[i+1][j-1]='#';now[i+1][j+1]='#';now[i][j+1]='#';now[i+1][j]='#';
}
int same(int n,int m){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(graph[i][j]!=now[i][j]) return 0;
		}
	}
	return 1;
}
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%s",graph[i]);
		for(int j=0;j<m;j++)
		now[i][j] = '.';
	}
	for(int i=0;i<n;i++){
		for(int j =0;j<m;j++){
			if(ok(i,j,n,m)) write(i,j);
		}
	}
	if(same(n,m)) printf("YES");
	else printf("NO");
	
}
```



---

## 作者：䒛夢 (赞：1)

**努力努力再努力的䒛夢他又来啦**

**写完这篇就先不再写下一篇了，有点虚了，今天写的有点多了**

# 先是题意

你想要一个 $n\times m$ 的矩阵，但是需要染色变为你想要的矩阵

# 思路
将可以染色的地方全部染上，判断与目标数组是否相同，估计是因为数据较水，所以并未没有没涂玩的数据，这种方法可以过

# 最后奉上代码

```
#include<iostream>
#include<cstdio>
using namespace std;
int n,m;
char a[1010][1010],b[1010][1010];
const int ml[9]={0,1, 1,-1,-1,0, 0,1,-1};//方向数组方便判断
const int mk[9]={0,1,-1, 1,-1,1,-1,0, 0};
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1 ; i<=n ; ++i)
		for(int j=1 ; j<=m ; ++j)
		{
			cin>>a[i][j];
			b[i][j]='.';·//先将存的数组初始化
		}
	for(int i=2 ; i<n ; ++i)
	{
		for(int j=2 ; j<m ; ++j)
		{
			bool v=0;//判断能否涂色
			for(int z=1 ; z<=8 ; ++z)
				if(a[i+ml[z]][j+mk[z]]!='#')
				{
					v=1;
					break;//不能就剪枝
				}
			if(v==0)
			{
				for(int z=1 ; z<=8 ; ++z)
					b[i+ml[z]][j+mk[z]]='#';
                 		//可以就涂色
			}
		}
	}
	for(int i=1 ; i<=n ; ++i)
	{
		for(int j=1 ; j<=m ; ++j)
		{
			if(a[i][j]!=b[i][j])
			{
				printf("NO");//判断是不是相等
				return 0;
			}
		}
	}
	printf("YES");
	return 0;
}
```

---

## 作者：氢氧化铯CsOH (赞：1)

我尽量把代码写得简洁些。

如题，只要枚举所有的圈的位置，能画就画上，最后再检查一遍是不是所有的墨水都被画过。

```cpp
#include<cstdio> 
#include<cstring>
const int maxn = 3000 + 5;
const int dx[] = {0, 0, 0, 1, 1, 2, 2, 2}, dy[] = {0, 1, 2, 0, 2, 0, 1, 2};
char s[maxn][maxn];
bool vis[maxn][maxn];
int n, m;

// 判断以(x, y)为左上角的8个格子是否都是# 
bool all(int x, int y) {
	for(int i = 0; i < 8; i++) {
		int r = x + dx[i], c = y + dy[i];
		if(r < 0 || r >= n || c < 0 || c >= m) return false; 
		if(s[r][c] == '.') return false;
	}
	return true;
}

void set(int x, int y) {
	for(int i = 0; i < 8; i++) {
		int r = x + dx[i], c = y + dy[i];
		vis[r][c] = true;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i++) scanf("%s", s[i]);
	for(int i = 0; i + 2 < n; i++) for(int j = 0; j + 2 < m; j++) 
		if(all(i, j)) set(i, j);
	
	bool ans = true;
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
		if(s[i][j] == '#' && !vis[i][j]) ans = false;
	}
	puts(ans ? "YES" : "NO");
}
```

---

## 作者：Apojacsleam (赞：1)

# B. Forgery
    time limit per test： 2 seconds
	memory limit per test： 256 megabytes
	input： standard input
	output： standard output


### 【Problem】
Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an n×m grid, where every cell is either filled with ink or empty. Andrey's pen can fill a 3×3
square without its central cell if it is completely contained inside the grid, as shown below.

http://codeforces.com/contest/1059/problem/B

### 【题解】
	从上到下，从左到右地遍历。
    若当前点为‘#’字符，则将它作为这个3*3矩阵的左上角覆盖，即可完成本问题。
### 【AC代码】
```cpp
#include<cstdio>
#include<iostream>
int n,m,p[1005][1005];
char a[1005][1005];
void BFS(int x,int y)
{
	if(x+1>n||y+1>m||x+2>n||y+2>m)  return;
	if(a[x][y]=='.'||a[x+1][y]=='.'||a[x+2][y]=='.'||a[x][y+1]=='.'||a[x][y+2]=='.'||a[x+1][y+2]=='.'||a[x+2][y+1]=='.'||a[x+2][y+2]=='.') return;
	p[x][y]=p[x+1][y]=p[x+2][y]=p[x][y+1]=p[x][y+2]=p[x+1][y+2]=p[x+2][y+1]=p[x+2][y+2]=true;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
			std::cin>>a[i][j];
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
		  if(a[i][j]=='#') BFS(i,j);
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
		  if(a[i][j]=='#'&&!p[i][j])
			{
				puts("NO");
				return 0;
			}
	puts("YES");
	return 0;
}
```

---

## 作者：luqyou (赞：0)

# 前言
~~不得不说一句CF评测是真慢~~

# 思路
这一题其实简单模拟一下就行了。

如果盖下一个章，那么这个章的中心 $8$ 个方向一定是 '#'（这不是废话吗）。

那么我们可以再建一个字符数组，扫一遍原图，只要原图某个点的一圈都是 ```#```，那我们就以这个点为中心盖一个章。

最后对比一下我们构造的图和原图，如果不一样，那肯定是无法盖出图中的形状的。

# AC code

```
#include<bits/stdc++.h>
const int maxn=1000+50;
using namespace std;
queue<int>q;
char a[1001][1001];
char b[1001][1001];
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",a[i]);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            b[i][j]='.';
    for(int i=1;i<n-1;i++)
        for(int j=1;j<m-1;j++)
            if(a[i-1][j+1]=='#'&&a[i-1][j-1]=='#'&&a[i+1][j-1]=='#'&&a[i+1][j+1]=='#'&&a[i-1][j]=='#'&&a[i][j+1]=='#'&&a[i][j-1]=='#'){
                b[i][j-1]='#';
                b[i][j+1]='#';
                b[i-1][j]='#';
                b[i+1][j]='#';
                b[i+1][j-1]='#';
                b[i+1][j+1]='#';
                b[i-1][j+1]='#';
                b[i-1][j-1]='#';
            }
    bool flag=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++)
            if(a[i][j]!=b[i][j]) {
                flag=1;
                break;
            }
        if(flag)
            break;
    }
    if(flag)
        printf("NO");
    else
        printf("YES");
    return 0;
}

```


---

## 作者：Na2_CuCl4 (赞：0)

# CF1059B 题解


题意：

有一个 $n \times m$ 的方阵，现在通过题目中说的染色方式，看看能不能染成目标方阵。

数据范围是 $3\le n,m \le1000$，所以直接用暴力搜索即可。复杂度是 $ O(n^2)$。

对于每一个格进行搜索，如果在想要的染色里面这个格子周围八个格子都是 `#`，则对其进行染色操作。

也就是说，如果我们要的目标方阵的一个局部是：

```
###
#.#
###
```

当我们搜索到正中心这个点的时候，我们就进行染色操作。（无论其中的点是否已经染过色了）

这一步代码如下：
```cpp
for(int i=1;i<n-1;i++){
   for(int j=1;j<m-1;j++){
      down=false;
        for(int l=-1;l<=1;l++){
            if(down)break;
            for(int t=-1;t<=1;t++){
                if(t==0&&l==0)continue;
                if(!k[i+l][j+t]）{down=true;break;}
            }
        }
        if(down)continue;
        else {
            for(int l=-1;l<=1;l++){
                for(int t=-1;t<=1;t++){
                    if(t==0&&l==0)continue;
                    g[i+l][j+t]=true;
                }
            }
        }
    }
}
```


然后，对进行染色之后的成果进行检索，看看两个数组是否完全一样。

```cpp
for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
        if(k[i][j]!=g[i][j]){
            cout<<"NO"<<endl;
            return 0;
        }
    }
}
cout<<"YES"<<endl;
return 0;
```

这道题就结束了。

完整代码：

```cpp
#include<iostream>
using namespace std;
const int NR=1024;
bool k[NR][NR],g[NR][NR];
bool down;
int main(){
    int n,m;
    cin>>n>>m;
    char c;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c;
            if(c=='#')k[i][j]=true;
        }

    }
    for(int i=1;i<n-1;i++){
        for(int j=1;j<m-1;j++){
            down=false;
            for(int l=-1;l<=1;l++){
                if(down)break;
                for(int t=-1;t<=1;t++){
                    if(t==0&&l==0)continue;
                    if(!k[i+l][j+t]){down=true;break;}
                }
            }
            if(down)continue;
            else {
                for(int l=-1;l<=1;l++){
                    for(int t=-1;t<=1;t++){
                        if(t==0&&l==0)continue;
                        g[i+l][j+t]=true;
                    }
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(k[i][j]!=g[i][j]){
                cout<<"NO"<<endl;
                return 0;
            }
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```


---

## 作者：carreye (赞：0)

## 题意简述

现在有一张空白的纸，需要进行若干次染色变成目标图形。

染色：选择一个点，将它周围八个点染成 `#` ，初始全是 `.` 。
## 解题方法

对每一个点进行分析，如在目标矩阵内其周围 $8$ 个点都是 `#` ，则染色，否则跳过。因为一个点可以染色多次，所以无需判断重复染色。

最后对染色后的矩阵与原矩阵对比，输出结果。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char c[1010][1010];//目标方程
char empty[1010][1010];//空白
int fx[8]={1, 1,1,-1,-1,-1,0, 0};
int fy[8]={1,-1,0, 1,-1, 0,1,-1};//四周8个格的位置关系
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
			empty[i][j]='.';//初始化
		}
	}
	for(int i=2;i<n;i++)
	{
		for(int j=2;j<m;j++)
		{
			bool flag=true;
			for(int k=0;k<8;k++)//处理
			{
				int mx=i+fx[k];
				int my=j+fy[k];
				if(mx<=0||mx>n||my<=0||my>m||c[mx][my]=='.')
				{
					flag=false;
					break;
				}
			}
			if(flag)
			{
				for(int k=0;k<8;k++)//染色
				{
					int mx=i+fx[k];
					int my=j+fy[k];
					empty[mx][my]='#';
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]!=empty[i][j])//对比
			{
				cout<<"NO"<<endl;
				return 0;
			}
		}
	}
	cout<<"YES"<<endl;
	return 0;
}
```

---

## 作者：lucky2008 (赞：0)

# CF1059B题解

## [题目传送门](https://www.luogu.com.cn/problem/CF1059B)

### 题目大意

给定一个n,mn,m的目标矩阵，初始矩阵全为$\,$ ' $.$ '  。
你可以染色无数次，每次选一个格子将它周围的八个格子覆盖成$\,$ ' $#$ '。

这个 $3*3$ 的矩阵只能出现在 $n*m$ 的矩阵内部，不能越界。

问是否能构成目标矩阵。

### 思路

这题数据量不大直接 $O(n^2)$ 枚举即可。

## AC代码

最后附上ac代码。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,m;
int dx[]={-1,-1,-1,0,0,1,1,1},dy[]={-1,0,1,-1,1,-1,0,1};//周围8个方向 
int a[1005][1005],b[1005][1005];//个人习惯用int,0表示'.',1表示'#'。 
void f(int x,int y)//染色 
{
	for(int i=0;i<8;++i)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(b[nx][ny]!=1)//把不能染色的情况排除 
			return; 
	}
	for(int i=0;i<8;++i)//剩下的都可以染色 
	{
		int nx=x+dx[i],ny=y+dy[i];
		a[nx][ny]=1;
	}
	return;
}
bool check()//比对染完色的数组和目标数组 
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(a[i][j]!=b[i][j]) 
				return false;//如果不一样就直接返回,无需继续比对 
	return true;//如果没有返回则都相等 
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			char s;
			cin>>s;
			if(s=='#')//输入&预处理 
				b[i][j]=1;
		}
	for(int i=2;i<n;++i)//枚举2~n-1 
		for(int j=2;j<m;++j) //枚举2~m-1 
			f(i,j);
	if(check())//输出 
		cout<<"YES";
	else
		cout<<"NO";
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，题中也说了**你可以染色无数次**，这就是告诉我们：能染则染。

什么是能染呢？

首先，越界的，不能染色（废话）。

然后，如果目标矩阵的染色的范围内出现不能染色的 `.`  的，不能染色。

如果以上都不符合，那就可以进行染色。

最后，检查一下，如果当前矩阵与目标矩阵一致的，输出 `YES`，否则输出 `NO`。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
int direction[8][2]=//方向数组，指示染色范围。
{
	{-1,-1},
	{-1,0},
	{-1,1},
	{0,-1},
	{0,1},
	{1,-1},
	{1,0},
	{1,1}
};
int n,m;
bool goal_graph[1005][1005],now_graph[1005][1005];
char input_graph[1005][1005];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)//输入。
	{
		scanf("%s",input_graph[i]+1);
	}
	for(int i=1;i<=n;i++)//转换。
	{
		for(int j=1;j<=m;j++)
		{
			goal_graph[i][j]=(input_graph[i][j]=='#');
		}
	}
	for(int i=2;i<n;i++)//枚举每一个不会越界的染色中心。
	{
		for(int j=2;j<m;j++)
		{
			bool flag=true;
			for(int k=0;k<8;k++)//检查目标矩阵的染色范围是否出现不可染色的格子。
			{
				if(!goal_graph[i+direction[k][0]][j+direction[k][1]])
				{
					flag=false;
					break;
				}
			}
			if(flag)//染色。
			{
				for(int k=0;k<8;k++)
				{
					now_graph[i+direction[k][0]][j+direction[k][1]]=true;
				}
			}
		}
	}
	for(int i=1;i<=n;i++)//判断是否一致。
	{
		for(int j=1;j<=m;j++)
		{
			if(now_graph[i][j]!=goal_graph[i][j])
			{
				printf("NO\n");
				return 0;
			}
		}
	}
	printf("YES\n");
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：Creator_157 (赞：0)

### 思路：


------------

用 **一个数组存目标矩阵** 。

**另一个数组模拟染色的过程** ：如果矩形内部的八个方向上的点都为 # 则可以认为这个点是被选定过的，将其四周八个方向的点染色。

最后将模拟的数组与目标数组比对，即可得出答案。


------------
### code


------------


```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
int n,m;
char a[1005][1005],s[1005][1005];//a为目标数组，s为模拟的数组
int mx[8]={0,0,1,1,1,-1,-1,-1};//方向数组，易于操作
int my[8]={1,-1,1,0,-1,1,0,-1};
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
	for(int j=1;j<=m;j++)
	{
	    cin>>a[i][j];
	    s[i][j]='.';//初始化
	}
    }
    for(int i=2;i<=n-1;i++)
    {
	for(int j=2;j<=m-1;j++)
	{
	    bool fl=true;
	    for(int l=0;l<8;l++)
	    {
		if(a[i+mx[l]][j+my[l]]!='#')//判断8个方向是否涂上了色
		{
		    fl=false;
		    break;
		}
	    }
	    if(fl)
	    {
		for(int l=0;l<8;l++)//染色
		{
		    s[i+mx[l]][j+my[l]]='#';
		}
	    }
	}
    }
    for(int i=1;i<=n;i++)
    {
	for(int j=1;j<=m;j++)
	{
	    if(a[i][j]!=s[i][j])//比对
	    {
		cout<<"NO";
		return 0;
	    }
	}
    }
    cout<<"YES";
    return 0;
}
```


---

