# 3-Coloring

## 题目描述

This is an interactive problem.

Alice and Bob are playing a game. There is $ n\times n $ grid, initially empty. We refer to the cell in row $ i $ and column $ j $ by $ (i, j) $ for $ 1\le i, j\le n $ . There is an infinite supply of tokens that come in $ 3 $ colors labelled $ 1 $ , $ 2 $ , and $ 3 $ .

The game proceeds with turns as follows. Each turn begins with Alice naming one of the three colors, let's call it $ a $ . Then, Bob chooses a color $ b\ne a $ , chooses an empty cell, and places a token of color $ b $ on that cell.

We say that there is a conflict if there exist two adjacent cells containing tokens of the same color. Two cells are considered adjacent if they share a common edge.

If at any moment there is a conflict, Alice wins. Otherwise, if $ n^2 $ turns are completed (so that the grid becomes full) without any conflicts, Bob wins.

We have a proof that Bob has a winning strategy. Play the game as Bob and win.

The interactor is adaptive. That is, Alice's color choices can depend on Bob's previous moves.

## 说明/提示

The final grid from the sample is pictured below. Bob wins because there are no two adjacent cells with tokens of the same color. $ $$$\begin{matrix}2&3\\3&1\end{matrix} $ $$$

The sample is only given to demonstrate the input and output format. It is not guaranteed to represent an optimal strategy for Bob or the real behavior of the interactor.

## 样例 #1

### 输入

```
2
1

2

1

3```

### 输出

```
2 1 1

3 1 2

3 2 1

1 2 2```

# 题解

## 作者：Acfboy (赞：6)

其实这题的实现也挺有意思的，不过不知道为什么题解区的代码都很长，直接一坨 `if` 到底，所以来写一份清新一点的题解。

做法：

1. 将网格图染成棋盘的样子
2. 能填 $1$ 或 $2$ 时只用其中一种颜色，一种颜色没法继续填了再启用 $3$。
3. 因为一种颜色没法填了，所以任意一个空网格周围四个肯定已经被 $1$ 或 $2$ 盖满，不会和 $3$ 产生冲突，$1$ 和 $2$ 由于棋盘染色，肯定也不会出现这种冲突，所以这种做法是对的。

来考虑实现，可以用一个 `check` 来检验当前能否继续填 $1$ 或 $2$, 能填就填了，不然再找空格填 $3$ 就可以了。

思路非常清晰，没有一堆 `if`, 代码也很简短。

```cpp
#include <cstdio>
#include <algorithm>
const int N = 105;
int n, c[N][N], vis[N][N], x;
struct twt { int x, y; };
bool check(int x) {
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= n; j++)
			if(!vis[i][j] && c[i][j] == x) {
				vis[i][j] = 1;
				printf("%d %d %d\n", x+1, i, j);
		    	fflush(stdout);
				return 1;
			}
	return 0;
}
twt find() {
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(vis[i][j] == 0) {
				vis[i][j] = 1;
				return (twt){i, j};
			}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		c[i][1] = 1 ^ c[i-1][1];
		for(int j = 2; j <= n; j++) c[i][j] = 1 ^ c[i][j-1];
	}
	for(int k = 1; k <= n*n; k++) {
		scanf("%d", &x);
		if(x == 3) { if(!check(1)) check(0); }
		else if(!check((x-1)^1)) {	
			twt sp; 
			sp = find();
		    printf("%d %d %d\n", 3, sp.x, sp.y);
		    fflush(stdout);
		}
	} 
	return 0;
}
```

---

## 作者：water_tomato (赞：4)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1503b-3-coloring-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1503B)。

有一张 $n\times\ n$ 的网格，有 $1,2,3$ 三种颜色，每轮交互库会给出一种颜色，你需要在剩余两种颜色中选一种颜色涂在一个格子上，不可以使任何两个相邻格子颜色相同。你需要扮演涂色者将所有格子涂上颜色。

## 解析

首先我们考虑到，如果有一个空格子，其上下左右四个格子中有两种颜色，你就输了（因为交互库可以一直给出剩余的这种颜色）。因此我们不能让这种情况发生，最好的解决办法就是尽可能只用两种颜色，且不相邻，将第三种颜色当作后手。

以这个思路，我们可以构造出一张理想网格。

![](https://cdn.luogu.com.cn/upload/image_hosting/udn8usau.png)

我们发现，在 $1$ 或 $2$ 全部被填完之前，不论交互库询问什么，我们都一定能在这个理想网格上填一格（例如，给出 $1$，就在应该填 $2$ 但尚未填的地方填一个 $2$）。

那当我们填完了其中一个数字时呢？我们发现我们已经无敌了，因为剩下的任意一个空格子，其上下左右四个格子都一定只有一种颜色，那么不论交互库给出哪一种颜色，我们都只需要填上另一种颜色，直至整张棋盘都被填满为止。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int c[N][N];
int n,a,T,n1x,n1y,n2x,n2y;
int x,y;
bool fl;
int main(){
	scanf("%d",&n);T=n*n;
	n1x=n1y=1;
	n2x=1,n2y=2;
	x=y=1;
	while(T--){
		scanf("%d",&a);
		if(!fl){//填理想网格
			if(a==1){
				c[n2x][n2y]=2;
				printf("%d %d %d\n",2,n2x,n2y);
				fflush(stdout);
				n2y+=2;
				if(n2y>n){
					n2x+=1;
					if(n2x%2==1) n2y=2;
					else n2y=1;
				}
				if(n2x>n) fl=true;
			}
			else{
				c[n1x][n1y]=1;
				printf("%d %d %d\n",1,n1x,n1y);
				fflush(stdout);
				n1y+=2;
				if(n1y>n){
					n1x+=1;
					if(n1x%2==1) n1y=1;
					else n1y=2;
				}
				if(n1x>n) fl=true;
			}
		}
		else{//有一个数字被填完了
			while(x<=n&&y<=n){
				if(!c[x][y]){
					if(a==1){
						if(c[x][y-1]==1||c[x][y+1]==1) c[x][y]=2;
						else c[x][y]=3;
					}
					else if(a==2){
						if(c[x][y-1]==1||c[x][y+1]==1) c[x][y]=3;
						else c[x][y]=1;
					}
					else{
						if(c[x][y-1]==1||c[x][y+1]==1) c[x][y]=2;
						else c[x][y]=1;
					}
					printf("%d %d %d\n",c[x][y],x,y);
					fflush(stdout);
					y++;if(y>n){y=1;x++;}
					break;
				}
				y++;if(y>n){y=1;x++;}
			}	
		}
	}
	return 0;
}
```

---

## 作者：Lynkcat (赞：3)

比较容易的一道交互题。

考虑把所有的点奇偶染色分成两个集合 $A,B$ 一个集合颜色染 $1$ ，另一个染 $3$ 。

如果 Alice 选 $2$ ，那么两个集合显然可以随便挑一个集合染色。

如果 Alice 选 $1$ ，考虑染另外一个点集，如果另一个点集点用光了那么就从自己的点集里挑一个染 $2$ 。

Alice 选 $3$ 的情况同理。

我们发现这样子做保证了其中最多两个颜色的点在一个集合，另一种颜色的点在另一集合，所以必定可行。

---

## 作者：Binary_Lee (赞：2)

## [题面传送门](https://www.luogu.com.cn/problem/CF1503B)

### 解决思路

讲一下 $\text{VP}$ 时的思路。

首先想到，只要能将棋盘中红色或蓝色部分全部填成同一个数，那么剩下的就不会受限了（可行有两个，限制只有一个）：

![](https://cdn.luogu.com.cn/upload/image_hosting/wgik2hah.png)

但考虑到交互库可能有点坑，比如第一个给了 $1$，你钦定了红色块全填 $2$，但后面他可能一直给 $2$ 。这样的话，你只能再钦定蓝色块全填 $1$ 。所以需要 “双线并行” ，直到填满其中一种为止。

可以证明，是一定存在这样的一组可行解的。

注意：随意填时填的数不能和给出的数相同。为了找出这个错误笔者甚至写了一个简陋的交互库。。。

具体解释可以看代码。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
using namespace std;
int n,ans[105][105],t1,t2,op,cnt1,cnt2;
int tot1,tot2;
struct node{
	int x,y;
}a1[10005],a2[10005];
bool fl;
int main(){	
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((i+j)%2==0) a1[++tot1].x=i,a1[tot1].y=j;
			else a2[++tot2].x=i,a2[tot2].y=j;
		}
	}    
	//预处理红色块、蓝色块的位置
    
	cin>>op;  
	if(op==1) cout<<2<<' ',t1=2;
	if(op==2) cout<<3<<' ',t1=3;
	if(op==3) cout<<1<<' ',t1=1;
	cnt1++;
	cout<<a1[cnt1].x<<' '<<a1[cnt1].y<<endl;
	//钦定红色块全填什么
        
	for(int i=1;i<=n*n-1;i++){
		cin>>op;
		if(op==t1&&!fl){
			if(op==1) cout<<2<<' ',t2=2;
			if(op==2) cout<<3<<' ',t2=3;
			if(op==3) cout<<1<<' ',t2=1;
			cnt2++;
			cout<<a2[cnt2].x<<' '<<a2[cnt2].y<<endl;
			fl=1;
		}
        //钦定蓝色块全填什么
        
		else if(op==t1&&cnt2<tot2){
			cout<<t2<<' ';
			cnt2++;
			cout<<a2[cnt2].x<<' '<<a2[cnt2].y<<endl;
		}
        //往蓝色块填数
        
		else if(op==t1){
			for(int z=1;z<=3;z++){
				if(z!=t1&&z!=t2){
					cout<<z<<' ';
					break;
				}
			}
			cnt1++;
			cout<<a1[cnt1].x<<' '<<a1[cnt1].y<<endl;
		}
        //蓝色块填满了就往红色块填可行数
        
		else if(cnt1<tot1){
			cout<<t1<<' ';
			cnt1++;
			cout<<a1[cnt1].x<<' '<<a1[cnt1].y<<endl;
		}
        //往红色块填数
        
		else{
			for(int z=1;z<=3;z++){
				if(z!=t1&&z!=op){   //注意这里不能与输入的数相同
					cout<<z<<' ';
					break;
				}
			}
			cnt2++;
			cout<<a2[cnt2].x<<' '<<a2[cnt2].y<<endl;
		}
        //红色块填满了就往蓝色块填可行数
        
	}
	return 0;
}
```

---

## 作者：vectorwyx (赞：2)

先把方格图黑白染色，然后钦定黑色格子填 $1$，白色格子填 $2$。每一回合，如果禁止填 $1$ 就去填白色格子，否则去填黑色格子，二者必得其一。这样做下去，如果某种颜色的格子已全被填充（很显然这个事件总会发生），就转变策略。

假如黑色格子先被填满，那就用 $2$ 和 $3$ 去填白色格子，二者必得其一；而如果白色格子先被填满，就用 $1$ 和 $3$ 去填黑色格子，同样是二者必得其一。可以捏几组小样例手模一下来辅助理解。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
pair<int,int> st1[N],st2[N];
int top1,top2,a;

int main(){
	int n=read();
	fo(i,1,n)
		fo(j,1,n){
			if((i+j)&1) st1[++top1]=make_pair(i,j);
			else st2[++top2]=make_pair(i,j);
		}
	fo(i,1,n*n){
		int x=read();
		if(!top1){
			printf("%d %d %d\n",(x==2?3:2),st2[top2].first,st2[top2].second);
			top2--;
			cout.flush();
			continue;
		}
		if(!top2){
			printf("%d %d %d\n",(x==1?3:1),st1[top1].first,st1[top1].second);
			top1--;
			cout.flush();
			continue;
		}
		if(x==1){
			printf("%d %d %d\n",2,st2[top2].first,st2[top2].second);
			top2--;
			cout.flush();
			continue;			
		}else{
			printf("%d %d %d\n",1,st1[top1].first,st1[top1].second);
			top1--;
			cout.flush();
			continue;			
		}
	}
	return 0;
}
```


---

## 作者：7KByte (赞：2)

首先对格子黑白染色。

整个交互过程分为两部。

第一步：

如果给定的数是 $1$ ，在白色格子中填一个 $2$ 。

如果给定的数不是 $1$ ，在黑色格子中填一个 $1$ 。

那么黑色格子或者白色格子先被填满，当一种颜色的格子被填满时进入第二步。

第二步：

给定的数为 $x$ ，枚举还没有填的格子，一定会剩余至少一种颜色可以填，填入即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define N 105
using namespace std;
int a[N][N];
typedef pair<int,int> Pr;
Pr u[N*N],v[N*N];int p,q;
int mat[4]={0,2,3,1};
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n)rep(j,1,n)if((i+j)&1)v[++q]=make_pair(i,j);else u[++p]=make_pair(i,j);
	int T=n*n;
	while(T){
		int x;cin>>x;
		if(x==1){
			cout<<2<<" "<<u[p].first<<" "<<u[p].second<<endl;
			a[u[p].first][u[p].second]=2;p--;
		}
		else {
			cout<<1<<" "<<v[q].first<<" "<<v[q].second<<endl;
			a[v[q].first][v[q].second]=1;q--;
		}
		if(!p||!q)break;
	}
	while(T){
		int x;cin>>x;
		if(p){
			int l=u[p].first,r=u[p].second;p--;
			rep(k,1,3)if(a[l-1][r]!=k&&a[l+1][r]!=k&&a[l][r-1]!=k&&a[l][r+1]!=k&&x!=k){
				a[l][r]=k;
				cout<<k<<" "<<l<<" "<<r<<endl;
				break;
			}
		}
		else{
			int l=v[q].first,r=v[q].second;q--;
			rep(k,1,3)if(a[l-1][r]!=k&&a[l+1][r]!=k&&a[l][r-1]!=k&&a[l][r+1]!=k&&x!=k){
				a[l][r]=k;
				cout<<k<<" "<<l<<" "<<r<<endl;
				break;
			}
		}
		if(!p&&!q)break;
	}
	return 0;
}
```

---

## 作者：hujiasheng1234 (赞：1)

提供一种比较妙的处理方式。

先将棋盘分成二部分。

```
1 2 1 2 1 ...
2 1 2 1 2 ...
1 2 1 2 1 ...
...
```

要保证没有两个相邻的位置上放有相同颜色的代币，即每个 $1$ 或 $2$ 周围的格子有同一编号。

否则评测机剩下的全给出另一种编号就不合法。

然后将用两个 `vector` 将所有 $1$ 或 $2$ 的位置记录下来。

当有一个编号的位置都被填了后，剩下的位置周围均为同一编号，此时任意空格子去掉相邻和评测机给的编号后均有解合法。

代码如下。

```
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define fi first
#define se second
using namespace std;
const int mx=2e5+5;
int T,n,x;
vector<pair<int,int>> _1,_2;
void ret(int _,int i,int j){
	cout<<_<<" "<<i<<" "<<j<<endl;
}
void solve(){
	cin>>n;	
	for(int i=1;i<=n;i++){//所有 1 或 2 的位置 
		for(int j=2-(i-1)%2;j<=n;j+=2) _1.push_back({i,j}); 
		for(int j=2-i%2;j<=n;j+=2) _2.push_back({i,j});
	}
	int len1=_1.size(),len2=_2.size(),t1=0,t2=0,f=0;
	for(int i=1;i<=n*n;i++){
		cin>>x;
		if(!f){//还有 1 或 2 的位置未被全部填满 
			if(x!=1) ret(1,_1[t1].fi,_1[t1].se),t1++;
			else ret(2,_2[t2].fi,_2[t2].se),t2++;
		}
	    else{//填满后去掉相邻和评测机给的编号，剩余编号即合法 
	    	if(t2<len2){
	    		if(x!=3) ret(3,_2[t2].fi,_2[t2].se),t2++;
	    		else ret(2,_2[t2].fi,_2[t2].se),t2++;
			}
	    	else{
	    		if(x!=3) ret(3,_1[t1].fi,_1[t1].se),t1++;
	    		else ret(1,_1[t1].fi,_1[t1].se),t1++;
			}
		}
		if(t2==len2||t1==len1) f=1;
	}
}
signed main(){
//	ios::sync_with_stdio(0);cout.tie(0);cin.tie(0);
	T=1;
	while(T--) solve();
	return 0;
}

---

## 作者：Little09 (赞：1)

简单的构造。考虑把原图黑白染色，然后把 $1$ 放入黑格，$2$ 放入白格。禁用一个就放另一个。

当一个颜色的格子放满后，再启用 $3$ 一起填满剩下的格子。例如黑格先填满，那么就用 $2$ 和 $3$ 继续把白格填满。

很显然这样是符合题意的。代码也很好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mem(x) memset(x,0,sizeof(x))
//const ll inf=1000000000000000000; 
int n; 
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
void work(int &x,int &y,int k)
{
	printf("%d %d %d\n",k,x,y);
	fflush(stdout);
	y+=2;
	if (y>n)
	{
		if (y%2==1) y=2;
		else y=1;
		x++;
	}
}
int main()
{
	n=read();
	int ans1=(n*n+1)/2,ans2=n*n-ans1,res1=0,res2=0;
	int x1=1,y1=1,x2=1,y2=2;
	for (int i=1;i<=n*n;i++)
	{
		int x=read();
		if (x!=2&&res2!=ans2)
		{
			work(x2,y2,2);
			res2++;
		}
		else if (x!=1&&res1!=ans1)
		{
			work(x1,y1,1);
			res1++;
		} 
		else
		{
			if (res2==ans2) work(x1,y1,3);
			else work(x2,y2,3);
		}
	}
	return 0;
}
```


---

## 作者：Warriors_Cat (赞：1)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1503B) & [CF 题面传送门](http://codeforces.com/problemset/problem/1503/B)。

题目大意：

* 这是一个交互题。
* 给定 $n\times n$ 的网格，每个格可以填 $1, 2, 3$ 三个数。每次禁止填某个数，一共要填 $n^2$ 次。
* 如果填完后有两个相邻的格数字相同，则输了。你要赢得这场游戏。保证你有必胜策略。

一道挺有意思的思维题，~~不过一年前我在 XES 做过一道 MO 上类似的来着（~~

---

### Solution：

考虑将这个 $n\times n$ 的网格黑白染色。我们先规定黑格填 $1$，白格只能填 $2$。

如果禁止填 $1$，我们就在白格填 $2$；如果禁止填 $2$，我们就在黑格填 $1$；如果禁止填 $3$，我们白格填 $2$ 与黑格填 $1$ 均可。

于是这道题就做完了……吗？

显然并没有，我们还要考虑如果有一种颜色的格子已经填满了怎么办。

这很简单。比如现在黑格的 $1$ 已经填满了，如果禁止填 $2$，我们就在白格填上一个 $3$ 就行。其它两种情况仍然像刚才那样办。

这样操作后，我们会发现，每种数字会当且仅当填在一种颜色的格子中。这样我们就保证了没有同数字相邻格。

over，时间复杂度为 $O(n^2)$。

---

### Code：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = x; i >= y; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define mpr make_pair
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 110;
int n, x, len1, len2;
pair <int, int> a[N * N], b[N * N];
// a 1
// b 2
inline void mian(){
	n = read();
	rep(i, 1, n) rep(j, 1, n){
		if(i + j & 1) a[++len1] = mpr(i, j);
		else b[++len2] = mpr(i, j);
	}
	rep(i, 1, n * n){
		x = read();
		if(x == 1){
			if(!len2) printf("%d %d %d\n", 3, a[len1].fi, a[len1].se), --len1, fflush(stdout);
			else printf("%d %d %d\n", 2, b[len2].fi, b[len2].se), --len2, fflush(stdout);
		}
		if(x == 2){
			if(!len1) printf("%d %d %d\n", 3, b[len2].fi, b[len2].se), --len2, fflush(stdout);
			else printf("%d %d %d\n", 1, a[len1].fi, a[len1].se), --len1, fflush(stdout);
		}
		if(x == 3){
			if(!len2) printf("%d %d %d\n", 1, a[len1].fi, a[len1].se), --len1, fflush(stdout);
			else printf("%d %d %d\n", 2, b[len2].fi, b[len2].se), --len2, fflush(stdout);
		}
	}
}
int main(){ int qwq = 1; while(qwq--) mian(); return 0; }
```


---

## 作者：t162 (赞：1)

## 题目大意

这是一道交互题。

你需要和交互库玩一个游戏。交互库每次给出一个属于 $[1,3]$ 的整数，你需要在一个 $n\times n$ 的网格图中任意一个格子上填写一个属于 $[1,3]$ 且和交互库给出的整数不同的整数。

如果任意时刻网格图中相邻两个格子（有公共边）上的数相同，你就输了，否则你就赢了。

你需要赢得这个游戏。

## 换位思考

如果你是交互库，你打算怎么玩？

其实容易想到，如果网格图中出现任意一个空的格子，其四周中的格子里中有不同的数，那么你一直给出没有出现过的那个数，到最后你就赢了。

举个例子，如果一个空的格子，其上方格子中填了 $1$，右方格子填了 $2$，那么你只要一直给出 $3$，对手就一直没法填这个空格子。

想到这里就差不多了。

## 解题

我们为了避免上面那种情况，可以考虑交错着填，填到最后达到这种状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/00zba8xm.png)


或这种状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/1g64jb8t.png)

其中同一张图中黄色格子中填的数字是一样的，白色格子可填可不填，但填的数字不能和黄色格子中数字一样。

这样，剩余的空格子就可以很轻松填完了（因为不论交互库给出什么整数，剩余的任意一个空格子总有至少一种数字可填）。

具体实现的时候，如下图。为了达到上面那两种状态之一，我们可以规定红色格子填一个固定值，黄色格子填另一种固定值，如果交互库给出的数等于红色格子中的值，那么就填黄色格子，否则就填红色格子。最终，总有一种颜色的格子被先填满，也就是到达上面两种状态之一。

![](https://cdn.luogu.com.cn/upload/image_hosting/vk53pdvt.png)

## 代码实现

代码中，我是斜着填的，当然这样写太麻烦了，容易出错，可以横着填，竖着填。

```cpp
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<limits>
 
namespace StandardLibrary {
    using std::cin;
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::fixed;
    using std::flush;
    using std::setprecision;
    using std::setw;
    using std::numeric_limits;
}
using namespace StandardLibrary;
 
#include<algorithm>
#include<bitset>
#include<complex>
#include<deque>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<utility>
#include<vector>
 
namespace STL {
    using std::bitset;
    using std::complex;
    using std::deque;
    using std::greater;
    using std::less;
    using std::map;
    using std::pair;
    using std::priority_queue;
    using std::queue;
    using std::set;
    using std::stack;
    using std::string;
    using std::vector;
 
    using std::make_pair;
    using std::sort;
}
using namespace STL;
 
#define rep(var, start, end) for(int var = (start), var##_end = (end); var <= var##_end; var++)
#define rrep(var, start, end) for(int var = (start), var##_end = (end); var >= var##_end; var--)
 
namespace IO {
    template <typename T>
    inline T read(T& dest) {
        int c = getchar(); T f = 1; dest = 0;
        while (c < 48 || c > 57) f *= (c == 45 ? -1 : 1), c = getchar();
        while (c >= 48 && c <= 57) dest = (dest << 3) + (dest << 1) + (c ^ 48), c = getchar();
        return dest *= f;
    }
    template <typename T, typename... args>
    inline void read(T& dest, args&... dests) { read(dest), read(dests...); }
    template <typename T>
    inline T read() {
        int c = getchar(); T f = 1, dest = 0;
        while (c < 48 || c > 57) f *= (c == 45 ? -1 : 1), c = getchar();
        while (c >= 48 && c <= 57) dest = (dest << 3) + (dest << 1) + (c ^ 48), c = getchar();
        return dest * f;
    }
 
    template <typename T>
    inline void put(T val) {
        T tmp = 0, l = 0; if (val < 0) putchar('-'), val = -val;
        while (val) tmp = tmp * 10 + (val % 10), l++, val /= 10;
        if (l == 0) putchar('0');
        else {
            while (l) putchar((tmp % 10) + 48), l--, tmp /= 10;
            while (l) putchar('0'), l--;
        }
    }
    template <>
    inline void put<char*>(char* val) { rep(i, 0, ((int)strlen(val)) - 1) putchar(val[i]); }
    template <>
    inline void put<const char*>(const char* val) {
        rep(i, 0, ((int)strlen(val)) - 1) putchar(val[i]);
    }
    template <>
    inline void put<string>(string val) { put(val.c_str()); }
    template <typename T, typename... args>
    inline void put(T val, args&... values) { put(val), putchar(' '), put(values...); }
 
    template <typename T>
    inline void write(T val) {
        put(val), putchar(' ');
    }
    template <typename T, typename... args>
    inline void write(T val, args&... values) { write(val), write(values...); }
 
    inline void writeln() { puts(""); }
    template <typename T>
    inline void writeln(T val) { put(val), writeln(); }
    template <typename T, typename... args>
    inline void writeln(T val, args&... values) { put(val), putchar(' '), writeln(values...); }
}
using namespace IO;
 
namespace Tools {
    template <typename T, typename... args>
    inline void log(T val) { cerr<<val<<endl; }
    template <typename T, typename... args>
    inline void log(T val, args... lists) { cerr<<val<<' '; log(lists...); }
}
using namespace Tools;

//=======正文开始=======
 
int a[201][201];
 
int n, k, oi = 1, oj = 1, ei = 2, ej = 1, flag = 1, li = 1, lj = 1;
 
void _put(int b, int i, int j) { a[i][j] = b, writeln(b,i,j), fflush(stdout); }  //填充函数
 
int main() {
    read(n);
    for (int i = 1; i <= n * n; i++) {
        int d; read(d);
        if (k == 0) {          //确定两种格子颜色
            if (d == 1) {
                _put(2, 1, 1), k = 2, oi++, oj++;
            } else _put(1, 1, 1), k = 1, oi++, oj++;
        } else if (flag) {         //未达到两种状态
            if (d == k) {
                _put(3 - k, ei, ej);
                ei++, ej++;
                if (ei > n) ei -= n, ej -= (n & 1);
                if (ej > n) ej -= n, ei -= (n & 1);
                if (a[ei][ej]) {
                    if (ei == n || ei == n - 1) flag = 0;
                    else ei += 2;
                }
            } else {
                _put(k, oi, oj);
                oi++, oj++;
                if (oi == oj && oi > n) oi -= n, oj -= n;
                if (oi > n) oi -= n, oj += (n & 1);
                if (oj > n) oj -= n, oi += (n & 1);
                if (a[oi][oj]) {
                    if (oi == n || oi == n - 1) flag = 0;
                    else oi += 2;
                }
            }
        } else {        //达到两种状态之一
            int f = 0;
            for (; li <= n; li++) {
                if (lj == n + 1) lj = 1;
                for (; lj <= n; lj++) {
                    if (a[li][lj]) continue;
                    if ((li >= lj && (li - lj) % 2 == 1) || ((li < lj) && (lj - li) % 2 == 1)) {
                        if (3 - k == d) _put(3, li, lj);
                        else _put(3 - k, li, lj);
                    } else {
                        if (d == k) _put(3, li, lj);
                        else _put(k, li, lj);
                    }
                    f = 1; break;
                }
                if (f) break;
            }
        }
    }
}
```

---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1503B)

同步发表于个人 [blog](https://www.cnblogs.com/alex-liu09/articles/CF1503B.html)，有更好的阅读体验。

## 分析：

首先考虑如果只给两种颜色让你填，你会怎么办？


那必然是交叉地填，这样才能满足题目要求。
```
1 2 1
2 1 2
1 2 1
```



于是考虑把填颜色 $1$ 的格子与填颜色 $2$ 的格子都预处理出来，时间复杂度 $O(n^2)$。

那么继续考虑题目给出的限制条件，禁止你使用一个颜色，那么你只需要填另一个颜色的格子即可。

但是如果一个颜色的格子全部都已经填完了怎么办？那么我们就可以使用颜色 $3$ 来弥补，把颜色 $3$ 填到本来被禁止的颜色的格子中即可。

考虑证明这种猜想：

由于不会出现颜色 $1$ 与颜色 $2$ 同时用完的情况，并且我们预处理出的格子中的任意颜色 $1$ 的格子或任意颜色 $2$ 的格子不会相邻，那么我们使用颜色 $3$ 来替代了一种颜色之后，也不会出现相邻的情况。

总时间复杂度 $O(n^2)$。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cl;
struct node{int x,y;};
stack<node>q1,q2;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//预处理颜色1与颜色2的格子。
		for(int j=1;j<=n;j++){
			if(i&1){
				if(j&1)q1.push((node){i,j});
				else q2.push((node){i,j});
			}else{
				if(j&1)q2.push((node){i,j});
				else q1.push((node){i,j});
			}
		}
	}
	for(int i=1;i<=n*n;i++){
		cin>>cl;
		if(cl==1){//禁止颜色1。
			if(!q2.empty()){//颜色2的格子还有剩余。
				cout<<"2 "<<q2.top().x<<" "<<q2.top().y<<endl;
				q2.pop();
			}else{//否则拿颜色3代替。
				cout<<"3 "<<q1.top().x<<" "<<q1.top().y<<endl;
				q1.pop();
			}
		}else if(cl==2){//禁止颜色2。
			if(!q1.empty()){//颜色1的格子还有剩余。
				cout<<"1 "<<q1.top().x<<" "<<q1.top().y<<endl;
				q1.pop();
			}else{//否则拿颜色3代替。
				cout<<"3 "<<q2.top().x<<" "<<q2.top().y<<endl;
				q2.pop(); 
			}
		}else{//禁止颜色3，填颜色1或者颜色2都可以。
			if(!q1.empty()){
				cout<<"1 "<<q1.top().x<<" "<<q1.top().y<<endl;
				q1.pop();
			}else{
				cout<<"2 "<<q2.top().x<<" "<<q2.top().y<<endl;
				q2.pop();
			}
		}
	}
	return 0;
} 
```


---

