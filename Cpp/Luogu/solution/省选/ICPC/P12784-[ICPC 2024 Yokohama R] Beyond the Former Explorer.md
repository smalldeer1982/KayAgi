# [ICPC 2024 Yokohama R] Beyond the Former Explorer

## 题目背景

译自 [ICPC 2024 Yokohama Regional Contest](https://icpc.jp/2024/)。

## 题目描述

**这是一道交互题。**

你正站在一片区域的正中心，该区域被划分为南北走向和东西走向的网格单元。一份巨大的宝藏隐藏在其中一个单元内。  

John Belzoni——著名的宝藏猎人 Giovanni Battista Belzoni 的后裔——实际上已发现了这份宝藏。不幸的是，他在成功挖出宝藏前因中暑去世；他似乎花了过长的时间在这片区域徘徊。  

John 的探索从你当前站立的区域中心单元出发。他通向宝藏的所有足迹都留在了这片区域，但只有抵达某个单元才能识别该单元上的足迹。某一单元上的足迹指示了他下一步前往四个相邻网格单元中的哪一个。 已知 John 不会重复访问同一网格单元。你在中心单元看到一个足迹，表明 **John 的第一步是向北**。

区域中存在恰好一个宝藏单元，只有站在该单元时你才能识别它。  

下图展示了区域的一种可能情形。John 的足迹在单元中以箭头标识。宝藏单元标记为 $\texttt{G}$。阴影单元是你的初始位置。  

![](https://cdn.luogu.com.cn/upload/image_hosting/bakj14ug.png)

你的任务是在有限**步**内找到宝藏。每一步中，你需决定朝北、西、南、东四个方向之一移动，并进入该方向的相邻单元。当你移动到该单元时，可能发现宝藏、John 的足迹，或者空无一物。你无需追随 John 的足迹。与 John 的路线不同，你可以重复访问同一单元。无论你如何探索，John 的足迹始终保持不变。  


### 实现细节

交互开始时，你需从标准输入读取一个整数 $n$（$1 \leq n \leq 2000$），后接换行符。整数 $n$ 表示区域被划分为 $(2n + 1) \times (2n + 1)$ 的网格单元。你的初始位置从西向东第 $n+1$ 列、从北向南第 $n+1$ 行的单元。读入整数 $n$ 后，你即可开始探索。  

每步，你向标准输出发送表示移动方向的单个字符：  
- `^`（插入符）表示向北；
- `<`（小于号）表示向西；
- `v`（小写字母 $\texttt{v}$）表示向南；
- `>`（大于号）表示向东。

字符后需附加换行符。  

作为回答，你将收到一个表示抵达单元内容的字符，后接换行符：  

- `G`：该单元有宝藏；
- `^`, `<`, `v`, `>`：John 的足迹分别指示北、西、南、东；
- `.`（点号）：既无宝藏也无足迹。

当你发现宝藏（即收到 `G`）时，交互立即终止，你的程序必须退出。 **你需在 $\bf{30000}$ 步内抵达宝藏单元**。尽管追随 John 的足迹必能找到宝藏，但步数可能超过 $30000$。 

以下情况将被判为 $\text{Wrong Answer}$：  

- 程序输出格式无效；
- 指定了移出网格的方向；
- 找到宝藏后仍有额外输出；
- 未在 $30000$ 步内抵达宝藏单元。

区域的布局（宝藏位置与 John 的足迹）在交互前已固定，在交互过程中不会改变。  

**在每次移动后，你都需要换行并刷新缓冲区**。例如：

- $\texttt{C++}$ 中的 `cout.flush()`。


## 说明/提示

样例如「题目描述」中的图所示。

## 样例 #1

### 输入

```
2

^

.

<

^

G```

### 输出

```

^

<

v

<

^```

# 题解

## 作者：KingPowers (赞：3)

直接的想法是考虑二分，每次把当前矩形横着切成两半，尝试问出来终点实在上半部分还是下半部分，然后递归过去，这样每次能把问题规模减半。考虑如何判断终点是否在一个矩形区域内，发现只需要把矩形的边界和边界外的一圈问出来（如果某个方向的边界就是整个网格图的边界则不用处理），根据方向统计一下进出这个矩形的次数即可。

于是就有了这么一个策略，设 $solve(l,r)$ 表示当前已经确定了终点在第 $[l,r]$ 行内，每次把当前位置移动到 $mid$ 行然后把第 $mid,mid+1$ 行全部经过一遍，然后就可以按照上面的策略判断上半或下半矩形是否合法了。这样看上去总共需要走 $O(n\log n)$ 步，但是发现每层二分的步数都在 $4n$ 步左右，常数太大了所以无法通过。

发现上面的策略步数太大的原因是我们每次都横着切而且要扫两行，所以有个优化方向是考虑同时加入竖切操作，这样每层要扫的格子数量就会不断缩减。具体来说设 $solve(l_1,r_1,l_2,r_2)$ 表示当前已经确定终点在第 $[l_1,r_1]$ 行，$[l_2,r_2]$ 列这个范围内，然后考虑类似网格图分治那样，每次选行列里长度较大的那个方向劈成两半，然后同样是在劈开的折线附近两行/两列内走一下，继续用上面的方法判断终点在哪一侧子矩形递归过去即可。为了减小常数，可以每次先令当前点移动到整个矩形范围内的中心。

提交上去发现可以通过，稍微分析一下发现上面的策略步数其实应该是 $O(n)$ 的，画一下就发现每次折线的长度至多递归两层后就会减半，所以一个比较松的上界大概是 $T(n)=8n+T(n/2)=16n$ 左右，实际上并不太满。

给一个比较简短的代码实现，小细节是判定一个矩形的时候如果矩形包含了起点进入次数要加 $1$。


```cpp
#include<bits/stdc++.h>
//#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
template<typename T> void cmax(T &x, T y){x = x < y ? y : x;}
template<typename T> void cmin(T &x, T y){x = x > y ? y : x;}
const int N = 5005;
int n, len, nx, ny;
char cur, a[N][N];
bool valid(){return nx >= 1 && nx <= len && ny >= 1 && ny <= len;}
char moveU(){nx--; cout << "^" << endl; char c; cin >> c; return a[nx][ny] = cur = c;}
char moveD(){nx++; cout << "v" << endl; char c; cin >> c; return a[nx][ny] = cur = c;}
char moveL(){ny--; cout << "<" << endl; char c; cin >> c; return a[nx][ny] = cur = c;}
char moveR(){ny++; cout << ">" << endl; char c; cin >> c; return a[nx][ny] = cur = c;}
void move(int tx, int ty){
	while(nx > tx) if(moveU() == 'G') return;
	while(nx < tx) if(moveD() == 'G') return;
	while(ny > ty) if(moveL() == 'G') return;
	while(ny < ty) if(moveR() == 'G') return;
}
bool check(int l1, int r1, int l2, int r2){
	int cnt = 0;
	if(l1 <= n + 1 && n + 1 <= r1 && l2 <= n + 1 && n + 1 <= r2) cnt++;
	For(i, l1, r1){
		cnt += a[i][l2 - 1] == '>'; cnt += a[i][r2 + 1] == '<';
		cnt -= a[i][r2] == '>'; cnt -= a[i][l2] == '<';
	}
	For(i, l2, r2){
		cnt += a[r1 + 1][i] == '^'; cnt += a[l1 - 1][i] == 'v';
		cnt -= a[r1][i] == 'v'; cnt -= a[l1][i] == '^';
	}
	return cnt;
}
void solve(int l1, int r1, int l2, int r2){
	int mid1 = (l1 + r1) >> 1, mid2 = (l2 + r2) >> 1;
	move(mid1, mid2); if(cur == 'G') return;
	if(r1 - l1 >= r2 - l2){
		For(i, mid2 + 1, r2) if(moveR() == 'G') return;
		if(moveD() == 'G') return;
		Rof(i, r2 - 1, l2) if(moveL() == 'G') return;
		if(moveU() == 'G') return;
		For(i, l2 + 1, mid2) if(moveR() == 'G') return;
		if(check(l1, mid1, l2, r2)) solve(l1, mid1, l2, r2);
		else solve(mid1 + 1, r1, l2, r2);
	}
	else{
		For(i, mid1 + 1, r1) if(moveD() == 'G') return;
		if(moveR() == 'G') return;
		Rof(i, r1 - 1, l1) if(moveU() == 'G') return;
		if(moveL() == 'G') return;
		For(i, l1 + 1, mid1) if(moveD() == 'G') return;
		if(check(l1, r1, l2, mid2)) solve(l1, r1, l2, mid2);
		else solve(l1, r1, mid2 + 1, r2);
	}
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n; nx = n + 1, ny = n + 1; len = 2 * n + 1;
	a[nx][ny] = '^'; solve(1, len, 1, len);
	return 0;
}
```

---

## 作者：Mirasycle (赞：3)

首先有一个显然的二分做法，就是直接二分答案在哪一列。然后遍历列得到答案。可以通过两列之间左右箭头数量的大小关系得出终点在左还是在右。注意你不能对于一列的左右箭头进行二分，不然在数量相等的时候无法判断。必须对于两列之间的空隙二分，统计左边列的右箭头，右边列的左箭头，如果个数相等的话可以通过初始进入方向来判断。

可惜，这个做法常数过大，无法通过。

考虑对于行列同时二分，写成分治形式，行和列交替进行二分缩小。可以得到答案是处于一个矩形范围内，我们现在需要将这个矩形顺着红线一分为二。

![](https://cdn.luogu.com.cn/upload/image_hosting/u1rroalc.png)

一个很直接的思路就是扫描这条红线，计算跨过其两边的次数。但是我们发现这条红线并没有抵住黑色方框的上下边界，所以我们统计到的跨越左右的次数是不完整的。

有一个巧妙的处理方法，将绿色方框内红线左边看成一个点，红线右边看成一个点，绿色框框之外黑框之内看成一个点。这样子我们有三个点，可以通过统计跨过红线的次数，跨过绿线的次数来得到三个点之间的有向边关系。于是整个问题就变成了欧拉路径问题！通过比较点 $(n+1,n+1)$ 和三个矩形的关系，我们可以得到起点是在哪个点内部。根据所有都要经过恰好一次边的信息，可以唯一确定终点。肯定不能直接模拟，我们考虑使用度数来解决这个问题，一个点能成为终点，要么其入读大于出度，要么其入度等于出度且其为起点。找到终点之后，直接往其中一个矩形递归即可。

每次对着红线两端行走一下即可，绿色的线两端不需要行走，因为绿线必定是之前某次的分割线，也就是意味着格子上面的值之前肯定走过了，我们用一个数组保存，调用之前的信息就行了。

最终的次数是 $12n$ 左右。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e3+10;
char a[maxn][maxn],C;
int in[5],out[5],x,y,n;
char move(char c){
	cout<<c<<endl;
	if(c=='^') x--; if(c=='v') x++;
	if(c=='<') y--; if(c=='>') y++;
	cin>>a[x][y]; return a[x][y];
}
bool to(int sx,int sy){
	while(x<sx){
		C=move('v');
		if(C=='G') return 1;
	}
	while(x>sx){
		C=move('^');
		if(C=='G') return 1;
	}
	while(y<sy){
		C=move('>');
		if(C=='G') return 1;
	}
	while(y>sy){
		C=move('<');
		if(C=='G') return 1;
	}
	return 0;
}
void init(){ for(auto i:{0,1,2}) in[i]=out[i]=0; }
bool IN(int x,int y,int x1,int x2,int y1,int y2){ return x1<=x&&x<=x2&&y1<=y&&y<=y2; }
void getrow(int u,int v,int l,int r,int y){
	for(int i=l;i<=r;i++){
		if(a[i][y]=='>') in[v]++,out[u]++;
		if(a[i][y+1]=='<') in[u]++,out[v]++;
	}
}
void getline(int u,int v,int l,int r,int x){
	for(int i=l;i<=r;i++){
		if(a[x][i]=='v') out[u]++,in[v]++;
		if(a[x+1][i]=='^') in[u]++,out[v]++;
	}
}
void solve(int lx,int rx,int ly,int ry,int t){
	if(!t){//div line
		int m1=(lx+rx)>>1,m2=(ly+ry)>>1; init();
		if(to(m1,m2)) return ; if(to(m1,ry)) return ;
		if(to(m1+1,ry)) return ; if(to(m1+1,ly)) return ;
		if(to(m1,ly)) return ; if(to(m1,m2)) return ;
		for(int i=ly;i<=ry;i++){
			if(a[m1][i]=='v') in[1]++,out[0]++;
			if(a[m1+1][i]=='^') in[0]++,out[1]++;
		}
		getrow(2,0,lx,m1,ly-1); getrow(0,2,lx,m1,ry); getrow(2,1,m1+1,rx,ly-1); 
		getrow(1,2,m1+1,rx,ry); getline(2,0,ly,ry,lx-1); getline(1,2,ly,ry,rx);
		int S=2,T=2;
		if(IN(n+1,n+1,lx,m1,ly,ry)) S=0;
		else if(IN(n+1,n+1,m1+1,rx,ly,ry)) S=1;
		for(auto i:{2,1,0}){
			if(in[i]==out[i]&&i==S) T=i;
			if(in[i]>out[i]) T=i;
		} assert(T<2);
		if(!T) solve(lx,m1,ly,ry,t^1);
		else solve(m1+1,rx,ly,ry,t^1);
	}else{//div row
		int m1=(lx+rx)>>1,m2=(ly+ry)>>1; init();
		if(to(m1,m2)) return ; if(to(lx,m2)) return ;
		if(to(lx,m2+1)) return ; if(to(rx,m2+1)) return ;
		if(to(rx,m2)) return ; if(to(m1,m2)) return ;
		for(int i=lx;i<=rx;i++){
			if(a[i][m2]=='>') in[1]++,out[0]++;
			if(a[i][m2+1]=='<') in[0]++,out[1]++;
		}
		getline(2,0,ly,m2,lx-1); getline(0,2,ly,m2,rx); getline(2,1,m2+1,ry,lx-1); 
		getline(1,2,m2+1,ry,rx); getrow(2,0,lx,rx,ly-1); getrow(1,2,lx,rx,ry);
		int S=2,T=2;
		if(IN(n+1,n+1,lx,rx,ly,m2)) S=0;
		else if(IN(n+1,n+1,lx,rx,m2+1,ry)) S=1;
		for(auto i:{2,1,0}){
			if(in[i]==out[i]&&i==S) T=i;
			if(in[i]>out[i]) T=i;
		} assert(T<2);
		if(!T) solve(lx,rx,ly,m2,t^1);
		else solve(lx,rx,m2+1,ry,t^1);
	}
}
int main(){
	cin>>n; x=n+1; y=n+1;
	for(int i=0;i<=2*n+2;i++)
		for(int j=0;j<=2*n+2;j++) a[i][j]='?';
	a[x][y]='^'; solve(1,2*n+1,1,2*n+1,1);
	return 0;
}
```

---

