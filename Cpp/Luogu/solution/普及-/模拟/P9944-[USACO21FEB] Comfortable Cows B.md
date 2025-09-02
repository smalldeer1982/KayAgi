# [USACO21FEB] Comfortable Cows B

## 题目描述

Farmer John 的草地可以被看作是一个由正方形方格组成的巨大的二维方阵（想象一个巨大的棋盘）。初始时，草地上是空的。

Farmer John 将会逐一地将 $N$（$1\le N\le 10^5$）头奶牛加入到草地上。第 $i$ 头奶牛将会占据方格 $(x_i,y_i)$，不同于所有已经被其他奶牛占据的方格（$0\le x_i,y_i\le 1000$）。

一头奶牛被称为是「舒适的」，如果它水平或竖直方向上与恰好三头其他奶牛相邻。Farmer John 对他的农场上舒适的奶牛数量感兴趣。对 $1\ldots N$ 中的每一个 $i$，输出第 $i$ 头奶牛加入到草地上之后舒适的奶牛的数量。 

## 说明/提示

### 样例解释 1

在前四头奶牛加入之后，位于 $(1,1)$ 的奶牛是舒适的。

在前七头奶牛加入之后，位于 $(2,1)$ 的奶牛是舒适的。

在前八头奶牛加入之后，位于 $(2,1)$ 和 $(2,2)$ 的奶牛是舒适的。 

### 测试点性质

- 测试点 $1-4$ 满足 $N\le 400$。
- 测试点 $5-12$ 没有额外限制。

## 样例 #1

### 输入

```
8
0 1
1 0
1 1
1 2
2 1
2 2
3 1
3 2```

### 输出

```
0
0
0
1
0
0
1
2```

# 题解

## 作者：Harrylzh (赞：4)

题意：每次加入一头牛，统计此时**恰好**有三头牛相邻的牛的数量。

思路：
- 每次按题意枚举符合要求的牛的数量，每次都需要枚举所有牛，明显超时。
- 考虑到每次加入后只可能会改变**加入的牛**以及**相邻的牛**的情况，所以只需每次操作后更新答案即可，时间复杂度 $O(n)$ 。变量具体更新方法详见代码。

代码：

```cpp
#include<iostream>
using namespace std;
int n;
bool l[1000+5][1000+5];//记录此位置是否有牛
int l2[1000+5][1000+5];//记录每头牛相邻的牛的数量
int ans=0;//答案
int d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};//相邻的牛的方向
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		l[x][y]=1;//记录此位置有牛
		for(int j=0;j<4;j++)//遍历相邻位置的牛
		{
			if(x+d[j][0]>=0&&y+d[j][1]>=0&&l[x+d[j][0]][y+d[j][1]])//判断此位置是否存在且有牛
			{
				l2[x][y]++;//相邻的牛数加一
				if(l2[x+d[j][0]][y+d[j][1]]==3) ans--;//如果原本这头牛是舒适的，加入后不是了，答案减一
				if(l2[x+d[j][0]][y+d[j][1]]==2) ans++;//如果原本这头牛不是舒适的，加入后是了，答案加一
				l2[x+d[j][0]][y+d[j][1]]++;//相邻牛的相邻数量加一
			}
		}
		if(l2[x][y]==3) ans++;//如果加入这头牛是舒适的，答案加一
		cout<<ans<<endl;
	}
}
```

---

## 作者：lutaoquan2012 (赞：3)

## 思路
一道简单的思维题目。

这道题只需要在每一次加入一头牛的时候，看一看他是不是能影响旁边的牛，如果能影响，就改变，这是有 $3$ 种情况。

- 发现牛的舒适变成了 $3$，那么我们把答案加一。
- 发现牛的舒适变成了 $4$，以为这原来是舒适的，但现在被影响了，所以变成不舒适的，把答案减一。
- 以上 $2$ 种都不是，不用特殊处理。

## 代码
```cpp
//
// Created by 55062 on 2024/1/22.
//
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, x, y, ans[1010][1010], vis[1010][1010], cnt;//一定要有vis数组来记录每个位置是不是有
int dx[10] = {1, -1, 0, 0}, dy[10] = {0, 0, 1, -1};//方向数组

int main() {
    cin >> n;
    for (int j = 1; j <= n; j++) {
        cin >> x >> y;
        for (int i = 0; i < 4; i++) {
            ll nx = x + dx[i], ny = y + dy[i];//向四周查看
            if (nx < 0) continue;//如果越界，那么跳过
            ans[nx][ny]++;//舒适度加一
            if (ans[nx][ny] == 3 && vis[nx][ny] == 1) cnt++;//如果这头牛舒适了并且有位置，那么答案+1
            if (ans[nx][ny] == 4 && vis[nx][ny] == 1) cnt--;//如果这头牛原本是舒适的，但是因为这个新加的牛变成了不舒适的
        }
        vis[x][y] = 1;//标记
        if (ans[x][y] == 3) cnt++;//如果原本的这头牛就是舒适的，那么答案也加一
        cout << cnt << "\n";
    }
    return 0;
}
```

---

## 作者：Tachibana27 (赞：1)

还是比较简单的题。



------------
每一次输入一头牛时，需要判断会不会影响其他的牛。如果当前这头牛的出现影响了其他牛那么做出对应的处理即可。事实上，每次加入只有 $3$ 种可能：

- 原来是 $2$ 个，加入这头牛正好 $3$ 个，答案加一。 
- 原来是 $3$ 个，加入这头牛多于 $3$ 个，答案减一。
- 不属于上述 $2$ 种情况，加入这头牛后不做处理。

详见代码

code：
```cpp
%:include<bits/stdc++.h>
inline int read()<%
	int s=0;
	int w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0' and ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
%>

void write(int x)<%
	if(x<0)<%
   		putchar('-');
   		x=-x;
	%>
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
%>
typedef long long ll;
int n;
int ans[1086][1086];
bool vis[1086][1086];
int cnt;
int dx[]{0,1,0,-1,0};
int dy[]{0,0,1,0,-1};
int main(){
    n=read();
    while(n--){
        int x;
        int y;
		x=read();
        y=read();
        for(int j=1;j<=4;j++){
            if(x+dx[j]<0||y+dy[j]<0||x+dx[j]>1000||y+dy[j]>1000)
				continue;//越界 
            ans[x+dx[j]][y+dy[j]]++;
            if(ans[x+dx[j]][y+dy[j]]==3 and vis[x+dx[j]][y+dy[j]])
				cnt++;//正好是3，答案加一 
            if(ans[x+dx[j]][y+dy[j]]==4 and vis[x+dx[j]][y+dy[j]])
				cnt--;//多于3，答案减一 
        }
        vis[x][y]=true;
        if(ans[x][y]==3)
			cnt++;
        write(cnt);//输出：) 
        puts("");
    }
    return 0;//撒花 
}
```

---

## 作者：Grapeskin2191 (赞：1)

# [P9944](https://www.luogu.com.cn/problem/P9944)
## 题意分析
应该很好理解。但是要注意：只有一个点上下左右**恰好**有 $3$ 个相邻的点时，这个点才是舒适的，大于小于 $3$ 个都不行。
## 思路
每次暴力搜索所有的点进行判断的话，时间复杂度会达到 $O(n^2)$，过不了。

注意到，只要将每个点一个一个加入，每加入一个点，检查它的上下左右相邻的四个点，更新它们的相邻点个数，并检查舒适的点个数是否有变化即可。如此，时间复杂度是 $O(n)$，可以过。
## 代码
还是很好写的。AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, g[1004][1004], ans;
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x++, y++; //坐标可能有0，我懒就直接加1了
        g[x][y] = 1; //注意这里1代表存在点，且没有相邻点
        for (int j = 0; j < 4; j++) {
            int xx = x + dx[j], yy = y + dy[j];
            if (g[xx][yy]) {
                if (g[xx][yy] == 4) ans--; //如果这个点相邻要超过3个，ans减1
                g[x][y]++, g[xx][yy]++;
                if (g[xx][yy] == 4) ans++; //如果这个点达到3个，ans加1
            }
        }
        if (g[x][y] == 4) ans++; //如果自己达到3个，ans加1（为什么我不加这行也能过）
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# P9944 [USACO21FEB] Comfortable Cows B 题解

### 解析

开一个二维数组代表每一个位置上奶牛的“舒适度”。

每一次“添加奶牛”操作后都遍历一遍数组是不行的，时间复杂度高达 $\mathcal O(n^2)$。

但是我们注意到，“添加奶牛”操作只会改变自己及周边 $4$ 个奶牛的舒适度，所以我们将单次时间复杂度降为了 $\mathcal O(1)$，总复杂度 $\mathcal O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int n,ans,x,y;
int com[N][N];
bool vis[N][N];
int dx[]={0,0,1,-1},dy[]={1,-1,0,0}; //偏移量数组
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    while(n--){
        cin>>x>>y;
        for(int i=0;i<4;i++){
            int px=x+dx[i],py=y+dy[i];
            com[px][py]++;
            if(com[px][py]==3&&vis[px][py]){ //如果是“舒适的”，则 ans++
            	ans++;
			} 
            if(com[px][py]==4&&vis[px][py]){ //如果原先是“舒适的”现在不是了，ans--
            	ans--;
			} 
        }
        vis[x][y]=1;
        if(com[x][y]==3){
        	ans++;
		} 
        cout<<ans<<"\n";
    }
return 0;
}
```


---

## 作者：Laoda_Bryant (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9944) | 
[更好的体验](https://www.luogu.com.cn/article/431fv6n3)  
## 思路
由于每次输入 $x$ 和 $y$ 只改变其上下左右的值，所以每次只要更新其相邻的值即可。
* 当某个位置相邻的奶牛数达到 $3$ 时，舒适度加一。
* 当某个位置相邻的奶牛数达到 $4$ 时，舒适度减一。
* 注意：每增加一头奶牛以后，如果该位置相邻正好有三头奶牛，则舒适度也要加一。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int p[1000][1005],x,y;
int xk[4]={0,1,0,-1},yk[4]={1,0,-1,0};
bool k[1005][1005];
int n,a=0;
signed main(){
	cin>>n;
	while(n--){
		cin>>x>>y;
		k[x][y]=1;
		for(int i=0;i<4;i++){
			if(x+xk[i]<0||y+yk[i]<0||x+xk[i]>1000||y+yk[i]>1000) continue;
			p[x+xk[i]][y+yk[i]]++;
			if(p[x+xk[i]][y+yk[i]]==3&&k[x+xk[i]][y+yk[i]]) a++;
			if(p[x+xk[i]][y+yk[i]]==4&&k[x+xk[i]][y+yk[i]]) a--;
		}
		if(p[x][y]==3) a++;
		cout<<a<<endl;
	}
	return 0;
}
```

---

## 作者：卷王 (赞：0)

## 大体思路

一道可以直接模拟的题目。

显然可以对于每次加入的操作，看 **这个点以及这个点四周** 的地方有什么改变，当然前提是这个点有牛。具体来讲，我们用 $cnt_{i,j}$ 表示 $(i, j)$ 周围有多少头牛，$vis_{i,j}$ 表示 $(i, j)$ 这个地方是否有牛。由于在 $(x,y)$ 这个地方增加了一头牛，它四周的牛的 $cnt$ 都会增加一，即：

```cpp
cnt[x - 1][y]++; cnt[x][y - 1]++;
cnt[x + 1][y]++; cnt[x][y + 1]++;
```

然后看看 $(x,y)$ 这个点本身符不符合要求，如果符合，答案就要 `++`，即：

```cpp
if(cnt[x][y] == 3) ans++;
```

最后依次判断四周的牛是否满足要求，即：

```cpp
if(cnt[x - 1][y] == 3 && vis[x - 1][y]) ans++;
if(cnt[x - 1][y] == 4 && vis[x - 1][y]) ans--; //是 4 说明原来是 3，因为前面累加了才变成了 4，原来的 3 肯定被计算在了答案里面，现在变成了 4，就不符合要求了，得减掉
if(cnt[x + 1][y] == 3 && vis[x + 1][y]) ans++;
if(cnt[x + 1][y] == 4 && vis[x + 1][y]) ans--;
if(cnt[x][y - 1] == 3 && vis[x][y - 1]) ans++;
if(cnt[x][y - 1] == 4 && vis[x][y - 1]) ans--;
if(cnt[x][y + 1] == 3 && vis[x][y + 1]) ans++;
if(cnt[x][y + 1] == 4 && vis[x][y + 1]) ans--;
```

## 代码
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int x, y, n, ans = 0;
int cnt[1007][1007];
bool vis[1007][1007];

signed main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		x = read(), y = read();
		x++, y++; //技巧：为了防止越界，x,y 同时加 1
		vis[x][y] = 1;
		cnt[x - 1][y]++; cnt[x][y - 1]++;
		cnt[x + 1][y]++; cnt[x][y + 1]++;
		
		if(cnt[x][y] == 3) ans++; //别忘了自己也有可能有贡献
		
		if(cnt[x - 1][y] == 3 && vis[x - 1][y]) ans++;
		if(cnt[x - 1][y] == 4 && vis[x - 1][y]) ans--; //是 4 说明原来是 3，因为前面累加了才变成了 4，原来的 3 肯定被计算在了答案里面，现在变成了 4，就不符合要求了，得减掉
		if(cnt[x + 1][y] == 3 && vis[x + 1][y]) ans++;
		if(cnt[x + 1][y] == 4 && vis[x + 1][y]) ans--;
		if(cnt[x][y - 1] == 3 && vis[x][y - 1]) ans++;
		if(cnt[x][y - 1] == 4 && vis[x][y - 1]) ans--;
		if(cnt[x][y + 1] == 3 && vis[x][y + 1]) ans++;
		if(cnt[x][y + 1] == 4 && vis[x][y + 1]) ans--;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：JOKER_chu (赞：0)

### 闲话

模拟赛考到了，懒得跳出循环然后用了 `goto` 所以 `AK` 没了，呜呜呜。

### 思路

1力做法：每次放完牛检查一遍整个地图，统计舒服的牛总数。预计得分 $32$，时间复杂度 $O(N^2)$。

正解：我们发现其实每次放完牛后对答案的影响就只有**上下左右**四个格子**和**自己这个格子，所以每次不用扫一遍整个地图了，放完后更新影响答案的五个格子就行了，其他格子不用动。时间复杂度 $O(N)$

### 做法和技巧

定义一个方向数组，存储与它相邻的牛数量。然后使用两个标记数组，一个用来标记这个格子上有没有牛，另一个用来记录是否计算过这个格子，以免重复计算。

### 代码

```cpp
#include <iostream>

#include <cmath>

#include <algorithm>

#include <climits>

#define endl '\n'

using namespace std;

const int hutao = 1e3 + 5, fx[6][4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}}; // 方向数组

int n, ans, a[hutao][hutao], v[hutao][hutao];

void function1(int x, int y){
  if(a[x][y] == 0){ // 这个地方没有牛，不算
    return ;
  }
  int cnt = 0;
  for(int first = 0; first < 4; ++first){ // 四个方向的奶牛数量
    cnt += a[x + fx[first][0]][y + fx[first][1]];
  }
  if(cnt != 3){ // 不是舒适的，注意，不是三个就不是舒适的
    if(v[x][y] == 1){ // 由舒适转为不舒适，答案减去
      ans--;
      v[x][y] = 0; // 标记为没计算过
    }
  }else{
    ans += !v[x][y]; // 看有没有计算过
    v[x][y] = 1;
  }
}

int main(){
  ios :: sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for(int first = 1, x, y; first <= n; ++first){
    cin >> x >> y;
    x++, y++; // 方向数组里面有 -1 所以加一，避免下标越界
    a[x][y] = 1;
    for(int second = 0; second < 5; ++second){ // 影响到的五个格子
      function1(x + fx[second][0], y + fx[second][1]);
    }
    cout << ans << endl; // 输出
  }
  return 0;
}
```

---

## 作者：continueOI (赞：0)

简单题。

考虑暴力，如果每次加入一只奶牛都遍历已有的所有奶牛判断是 $\mathcal{O}{(n^2)}$ 的，无法通过所有数据。

考虑优化，每加入一只奶牛只会对自己周围的 $4$ 只奶牛造成影响，于是建立一个数组 $mp$ 来维护奶牛周围已经有几只奶牛了，如果发现有 $3$ 只就 $ans$ 加上一，如果有 $4$ 只就将 $ans$ 减去一，从而在 $\mathcal{O}{(n)}$ 的时间复杂度类得到答案。

当然不要忘记判断加入的奶牛自身周围是否已经有 $3$ 只奶牛了。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int ans;
int mp[1010][1010];
bool vis[1010][1010];
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int tx,ty;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		for(int j=0;j<4;j++){
			tx=x+dx[j],ty=y+dy[j];
			mp[tx][ty]++;
			if(mp[tx][ty]==3&&vis[tx][ty]) ans++;
			if(mp[tx][ty]==4&&vis[tx][ty]) ans--;
		}
		vis[x][y]=1;
		if(mp[x][y]==3) ans++;
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：Cute__yhb (赞：0)

## 思路
可以用一个二维数组来存位于 $(x,y)$ 的点相邻的奶牛数。

对于新加进去的奶牛，可以枚举相邻的点，把它们的相邻数加 $1$，然后更新答案。

更新答案时，可以用一个数组来存这个点是否舒适，再用一个数组存此点有无奶牛。如果这个点没有奶牛，直接跳过。剩下的：

- 如果此点不舒适但满足条件，答案加 $1$，标记。
- 如果此点舒适但不满足条件，答案减 $1$，取消标记。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,cnt=0;
int a[1005][1005],c[1005][1005],vis[1005][1005];
void fun(int x,int y){//更新
	if(!vis[x][y]) return ;//无奶牛
	if(!c[x][y]&&a[x][y]==3){//不舒适但满足条件
		cnt++;//答案+1
		c[x][y]=1;//标记
	}else if(c[x][y]){//舒适
		if(a[x][y]!=3){//不满足条件
			cnt--;//答案-1
			c[x][y]=0;//取消标记
		}
	}
}
int dx[]={0,1,-1,0,0};//方向数组
int dy[]={0,0,0,1,-1};
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		vis[x][y]=1;//有奶牛
		for(int j=1;j<=4;j++){//遍历相邻点
			int xx=x+dx[j],yy=y+dy[j];
			if(xx<0||xx>1000||yy<0||yy>1000) continue;//越界
			a[xx][yy]++;//相邻数+1
			fun(xx,yy);//更新
		}
		cout<<cnt<<endl;//输出
	}
    return 0;
}
```


---

## 作者：wwxxbb (赞：0)

# [题目](https://www.luogu.com.cn/problem/P9944)

# 思路


这题有一种比较简单的做法，设变量 $ans$ 表示舒适的奶牛的数量，$a$ 数组表示奶牛四周其他奶牛的数量，如果发现有 $3$ 只就 $ans$ 加 $1$，如果有 $4$ 只就将 $ans$ 减 $1$，还有不要忘记本来奶牛四周是否有 $3$ 只奶牛。

# Std：

```cpp
#include<bits/stdc++.h>
#define N 1010
using namespace std;
int n,ans,a[N][N],sx,sy,x,y;
bool vis[N][N];
int d[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//从1开始防止越界
		cin>>x>>y;
		for(int j=0;j<4;j++){
			sx=x+d[j][0],sy=y+d[j][1];
			a[sx][sy]++;
			if(a[sx][sy]==3&&vis[sx][sy])ans++;
			if(a[sx][sy]==4&&vis[sx][sy])ans--;
		}
		vis[x][y]=1;
		if(a[x][y]==3)ans++;
		cout<<ans<<endl;
	}
	return 0;
}
```

---

