# Palindromic Paths

## 题目描述

这是一个交互题。

你有一个 $n \times n$ 的网格，其中 $n$ 是奇数。行从上到下编号为 $1$ 到 $n$，列从左到右编号为 $1$ 到 $n$。位于第 $x$ 行第 $y$ 列的格子记作 $(x, y)$。

每个格子中包含 $0$ 或 $1$。已知左上角格子为 $1$，右下角格子为 $0$。

你的目标是确定网格中所有格子的数值。为此，你可以进行如下询问：

“$?$ $x_1$ $y_1$ $x_2$ $y_2$”，其中 $1 \le x_1 \le x_2 \le n$，$1 \le y_1 \le y_2 \le n$，并且 $x_1 + y_1 + 2 \le x_2 + y_2$。换句话说，你需要输出网格中两个不同的格子 $(x_1, y_1)$ 和 $(x_2, y_2)$，并且可以仅通过向右或向下移动从第一个格子走到第二个格子，且它们不是相邻的。

对于每次这样的询问，你会被告知是否存在一条从 $(x_1, y_1)$ 到 $(x_2, y_2)$ 仅向右或向下移动的路径，使得路径上经过的格子中的数字序列构成一个回文串。

例如，图中绿色的路径是回文路径，因此对于“$?$ $1$ $1$ $2$ $3$”和“$?$ $1$ $2$ $3$ $3$”的答案都是存在这样的路径。然而，对于“$?$ $1$ $1$ $3$ $1$”则不存在回文路径。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1205C/b6805c57783550cbf5043011ffee37b4f451b7b2.png)

请通过不超过 $n^2$ 次询问，确定网格中所有格子的数值。可以证明总有解。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
0
1
0
1
1
1
1```

### 输出

```
? 1 1 1 3
? 1 1 2 3
? 2 1 2 3
? 3 1 3 3
? 2 2 3 3
? 1 2 3 2
? 1 2 3 3
!
100
001
000```

# 题解

## 作者：Rhodoks (赞：5)

考虑对距离为3的两个元素进行询问，此时得到的回答即是始末元素是否相同。

首先将矩阵奇偶染色，发现左上角和右下角这两个已知元素同色，称这种颜色的元素为偶数元素。偶数元素共有$(n*n+1)/2$个，可以通过$(n*n+1)/2-2$次询问求得所有偶数元素的确切值。

对于奇数元素，共有$(n*n-1)/2$个，并且可以通过$(n*n-1)/2-1$次询问求得所有奇数元素的相对值。不妨设$a[1][2]=1$，那么我们得到了一个完整的矩阵。

此时我们共计使用了$n*n-3$次询问。而还需要验证，$a[1][2]=1$是否符合原矩阵。

考虑距离为4的询问，假设其中一条路径为$c_1,c_2,c_3,c_4$。如果$c_1\oplus c_2\oplus c_3\oplus c_4=0$，那么当且仅当$c_2=c_3$时构成回文路径，否则$c_1\oplus c_4 = c_2\oplus c_3 =1$即$c_1$,$c_4$不等，自然不可能回文。

值得注意的是，由于$c_1$,$c_3$同色，那么他们之间的关系我们是确定的，自然异或和也确定。$c_2$,$c_4$同理。所以四个数的异或和也是确定的。

我们需要在矩阵中寻找一条长度为4的路径满足上述，用以验证。

因为$a[1][1]=1,a[n][n]=0$，必然存在$i$，使得$a[i][i]\oplus a[i+2][i+2]=1$。

于是
$$(a[i][i]\oplus a[i+1][i]\oplus a[i+1][i+1]\oplus a[i+2][i+1])$$
$$(a[i+1][i]\oplus a[i+1][i+1]\oplus a[i+2][i+1]\oplus a[i+2][i+2])$$

必然不同。

在两条路径之中必然能找出一条，满足$c_1\oplus c_2\oplus c_3\oplus c_4=0$。进行一次询问用以验证，符合则直接输出，否则奇数元素取反输出。

代码丑，不放了。

---

## 作者：MisaYuzuki (赞：2)

首先可以把所有格子 $(x,y)$ 根据 $x+y$ 的奇偶性分成两个集合，我们可以求出每个集合内的相对颜色关系，通过若干组长度为 $3$ 的链。

此时大约花费了将近 $n^2$ 次询问，我们仅剩常数次询问次数。

求出两个集合内的相对颜色关系，而且已知偶数集合中 $(1,1)$ 和 $(n,n)$ 的颜色，那么只要求出两个集合中任意一对的关系就可以求出整体颜色关系了。

情况 $1$：显然，我们需要用到长度 $\gt 3$ 的链，那么为了方便，我们就用长度 $=4$ 的链即可。对应 $1\times 4$ 的矩形和 $2\times 3$ 的矩形。前者没有什么拓展空间，那么就对 $2\times 3$ 的情况下手。观察下图的左 $2\times 3$ 矩阵（即忽视第三列）：

![](https://cdn.luogu.com.cn/upload/image_hosting/v3csf1h1.png)

（注：这里将所有 $x+y$ 为偶数的格子标红，计数表白，下文图照例）

这里可以发现 $(1,1)$ 到 $(3,2)$ 路径之二：

- $(1,1)\to(2,1)\to(2,2)\to(3,2)$
- $(1,1)\to(2,1)\to(3,1)\to(3,2)$

注意到 $(2,2)$ 和 $(3,1)$ 颜色相反，所以两条路径中必有一条中间两个点是相同。那么可以通过两条结果一对一错和两错分别得出 $(1,1)$ 和 $(3,2)$ 颜色相同和相反的结论。

那么只要在偶数的红左下——右上存在两个相邻的数相对关系是不同的就可以做上述操作。

情况 $2$：那么剩下的情况就是偶数的每一红左下——右上列内部相对关系相同。那么可以发现存在如下情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/df9ao5nh.png)

即至少存在相邻的两红左下——右上列值全部相同，有相邻红左下——右上列值完全相反。

那么观察图中加粗的矩形，即求 $(3,2),(4,3)$ 和 $(2,3),(4,3)$ 的关系。只要这两组有一组是相对关系相同那么便可以知道所有的值。

情况 $3$：那么问题变成两红左下——右上列值和值相反相邻红左下——右上列所夹的两白左下——右上列列内部颜色相同，列之间颜色相反。从左下往右上看，这五列本质上可以看做：

- $1,1,1,0,0$
- $1,0,1,1,0$

由于其他情况可以通过 $01$ 对称和序列翻转得到，故不列出。

后者存在长度为 $4$ 的链为回文。前者不存在。可以判断中间两列的颜色情况。

给可爱的小妹妹点个赞再走吧 qwq

---

## 作者：zyh_helen (赞：2)

提供一个简明的不同思路。

---
---

考虑回文串的性质，一个串是回文串的必要条件是该串的两端点的相等；进一步的，一个长为 3 的的回文串的充要条件是该串的两端点相同，所以欲要知道一个点的值，仅需知道任何一个与它曼哈顿距离为 2 的点的值即可。

---
---

首先考虑 $n=3$ 的情况，我们可以用三次形如 $\{1,1,x,y\} $ 的询问轻松处理出三个蓝点的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/urg5u7mr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

并且我们可以通过一次询问 $\{2,1,3,2\}$ 求出两个黄色点的值是否相等。

![](https://cdn.luogu.com.cn/upload/image_hosting/ptwpge6y.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

接下来我们称下图两串分别为红串和灰串，进行分类讨论：

![](https://cdn.luogu.com.cn/upload/image_hosting/kzqlfo2x.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- 若左下角点值为 1：

	- 若两黄点值相等，那么红串共有两种可能：$[1,0,1,0]$ 和 $[1,1,1,1]$，可以直接判断出黄点的值；
    
   - 若两黄点值不相等，那么灰串共有两种可能：$[1,1,0,0]$ 和 $[0,1,1,0]$，可以直接判断出黄点的值；

- 若左下角点值为 0：

	- 若两黄点值相等，那么灰串共有两种可能：$[0,0,0,0]$ 和 $[1,0,1,0]$，可以直接判断出黄点的值；
    
   - 若两黄点值不相等，那么红串共有两种可能：$[1,1,0,0]$ 和 $[1,0,0,1]$，可以直接判断出黄点的值。

---

还有一个小问题：题目中说只要存在任意一条回文路径即可，为何强制钦定经过左下角点呢？

- 若询问返回的值为不存在任何回文路径，即经过左下角的路径一定也不是回文路径；

- 若询问返回的值为存在至少一条回文路径，即已经得出了该路径两端点值相等的结论。

---

以上算是比较严谨的求出了 $n=3$ 的解。

---
---

当 $n>3$ 时，我们可以轻松求出横纵坐标和为偶数的点的值，并且只需要知道任何一个横纵坐标和为奇数的点的值，就能知道所有点的值。

---

考虑在整个矩形中，找到一个长宽皆为 3 的正方形并满足该正方形左上角的值已确定为 1，右下角的值已确定为 0。

这样我们就能运用 $n=3$ 时的构造方法，求出一个横纵坐标和为奇数的点的值。

---

一个简单的方法是从左上角开始找，若不满足就将当前正方形的右下角作为左上角，继续判断，由于整个大矩形中左上角值为 1，右下角值为 0，那么可以保证找到一个合法的正方形。

---
---

询问次数可以做到 $n^2-2$ 次，但是蒟蒻很菜用了 $n^2-1$ 次。

---
---

代码看起来有点长。

```cpp
#include<bits/stdc++.h>
#define int long long
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 2e5 + 10, M = 7001, inf = 1e9, mod = 998244353;
const double eps = 1e-8, pi = 3.1415926;
/*
		    	       	       _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/

//int head[N], tot = 1;
//struct edge{
//	int t, f;
//	char c;
//	int next;
//}e[N << 1];
//void edge_add(int u, int v, char c){
//	e[++tot].next = head[u];
//	e[tot].t = v;
//	e[tot].f = u;
//	e[tot].c = c;
//	head[u] = tot;
//}
//int qmr(int x, int a){
//	x %= mod;
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}


int n, a[55][55], vis[55][55];
int ask(int x1, int y1, int x2, int y2){
	printf("? %lld %lld %lld %lld\n", x1, y1, x2, y2);
	fflush(stdout);
	int x;
	scanf("%lld", &x);
	return x;
}
signed main(){
	cin >> n;
	a[1][1] = 1;
	if(n == 3){  //其实不写这个也是可以的
		a[1][3] = ask(1, 1, 1, 3);
		a[2][2] = ask(1, 1, 2, 2);
		a[3][1] = ask(1, 1, 3, 1);
		int x = ask(2, 1, 3, 2);
		if(a[3][1] ^ !x){
			a[3][2] = ask(1, 1, 3, 2);
			a[2][1] = !x ^ a[3][2];
		}
		else {
			a[2][1] = !ask(2, 1, 3, 3);
			a[3][2] = !x ^ a[2][1];
		}
		a[1][2] = !ask(1, 2, 3, 2) ^ a[3][2];
		a[2][3] = !ask(2, 1, 2, 3) ^ a[2][1];
		cout << "!\n";
		cout << a[1][1] << a[1][2] << a[1][3] << endl << a[2][1] << a[2][2] << a[2][3] << endl << a[3][1] << a[3][2] << a[3][3];
		fflush(stdout);
		return 0;
	}
	
	//处理横纵坐标和为偶数的情况 
	for(int i = 1;i <= n;i++){
		if(i & 1){
			if(i != 1)a[i][1] = a[i - 2][1] ^ !ask(i - 2, 1, i, 1);
			for(int j = 3;j <= n;j += 2){
				a[i][j] = a[i][j - 2] ^ !ask(i, j - 2, i, j);
			}
		}
		else {
			a[i][2] = a[i - 1][1] ^ !ask(i - 1, 1, i, 2);
			for(int j = 4;j <= n;j += 2){
				a[i][j] = a[i][j - 2] ^ !ask(i, j - 2, i, j);
			}
		}
	}
	
	//找到第一个满足条件的正方形
	int x = 1, y = 1;
	while(a[x + 2][y + 2] == 1)x += 2, y += 2;
	
	//找到第一个横纵坐标和为奇数的点的值
	int xx = ask(x + 1, y, x + 2, y + 1);
	if(a[x + 2][y] ^ !xx){
		a[x + 2][y + 1] = ask(x, x, x + 2, y + 1);
		a[x + 1][y] = !xx ^ a[x + 2][y + 1];
	}
	else {
		a[x + 1][y] = !ask(x + 1, y, x + 2, y + 2);
		a[x + 2][y + 1] = !xx ^ a[x + 1][y];
	}
	vis[x + 2][y + 1] = vis[x + 1][y] = 1;
	
	//处理横纵坐标和为奇数的情况
	x--;
	y--;
	while(x > 0){
		a[x + 1][y] = a[x + 2][y + 1] ^ !ask(x + 1, y, x + 2, y + 1);
		vis[x + 1][y] = 1;
		x--;
		y--;
	}
	a[1][2] = a[3][2] ^ !ask(1, 2, 3, 2);
	vis[1][2] = 1;
	for(int i = 1;i <= n;i++){
		if(i & 1){
			if(!vis[i][2])a[i][2] = a[i - 1][1] ^ !ask(i - 1, 1, i, 2);
			for(int j = 4;j <= n;j += 2){
				if(!vis[i][j])a[i][j] = a[i][j - 2] ^ !ask(i, j - 2, i, j);
			}
		}
		else {
			if(!vis[i][1])a[i][1] = a[i - 2][1] ^ !ask(i - 2, 1, i, 1);
			for(int j = 3;j <= n;j += 2){
				if(!vis[i][j])a[i][j] = a[i][j - 2] ^ !ask(i, j - 2, i, j);
			}
		}
	}
	
	//输出答案
	cout << "!\n";
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++)printf("%lld", a[i][j]);
		putchar('\n');
	}
	fflush(stdout);
	return 0;
}

---

## 作者：_edge_ (赞：0)

来点更加简洁，更加暴力的做法。

注意到交互库一次询问返回答案，感觉是只能 $O(n^3)$ 或者 $O(n^4)$ dp 的。

那么我们不妨先询问长为 $3$ 的路径，这样我们就能知道矩阵只剩下 $2$ 种情况，并且这两种情况只在 $2$ 不整除 $i+j$ 时翻转一下。

具体来说就是，矩阵只有 $a_{1,2}=1$ 或者 $a_{1,2}=0$ 的情况。

欸，这时候怎么办，我们注意到还剩下个 $2$ 次询问，我们直接对两种矩阵进行 dp，如果能找出一个四元组能区分开来那就询问一下。

注意到如果不能区分代表无法问出整个矩阵，所以必定存在）


```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int INF=55;
int n,Map[INF][INF],Map2[INF][INF],f[INF][INF][INF][INF],f2[INF][INF][INF][INF];
int query(int x,int y,int xx,int yy) {
    cout<<"? "<<x<<" "<<y<<" "<<xx<<" "<<yy<<endl;
    int op=0;cin>>op;return op;
}
queue < pii >q;
struct P4{
    int x,y,xx,yy;
};
queue < P4 > q2;
signed main()
{
    memset(Map,255,sizeof Map);
    cin>>n;Map[1][1]=1;Map[n][n]=0;
    q.push({1,1});Map[1][2]=1;q.push({1,2});
    while (q.size()) {
        int x=q.front().fi,y=q.front().se;q.pop();
        if (x+2<=n && Map[x+2][y]==-1) {
            int it=query(x,y,x+2,y);
            if (it) Map[x+2][y]=Map[x][y];
            else Map[x+2][y]=Map[x][y]^1;
            q.push({x+2,y});
        }
        if (y+2<=n && Map[x][y+2]==-1) {
            int it=query(x,y,x,y+2);
            if (it) Map[x][y+2]=Map[x][y];
            else Map[x][y+2]=Map[x][y]^1;
            q.push({x,y+2});
        }
        if (x+1<=n && y+1<=n && Map[x+1][y+1]==-1) {
            int it=query(x,y,x+1,y+1);
            if (it) Map[x+1][y+1]=Map[x][y];
            else Map[x+1][y+1]=Map[x][y]^1;
            q.push({x+1,y+1});
        }
        if (y-2>=1 && Map[x][y-2]==-1) {
            int it=query(x,y-2,x,y);
            if (it) Map[x][y-2]=Map[x][y];
            else Map[x][y-2]=Map[x][y]^1;
            q.push({x,y-2});
        }
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if ((i+j)%2==1) Map2[i][j]=Map[i][j]^1;
            else Map2[i][j]=Map[i][j];
    
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            f[i][j][i][j]=1,q2.push({i,j,i,j});
    for (int i=1;i<=n;i++)
        for (int j=1;j<n;j++)
            if (Map[i][j]==Map[i][j+1]) f[i][j][i][j+1]=1,q2.push({i,j,i,j+1});
    for (int i=1;i<n;i++)
        for (int j=1;j<=n;j++)
            if (Map[i][j]==Map[i+1][j]) f[i][j][i+1][j]=1,q2.push({i,j,i+1,j});
    while (q2.size()) {
        int x=q2.front().x,y=q2.front().y,xx=q2.front().xx,yy=q2.front().yy;q2.pop();
        if (x-1>=1 && xx+1<=n && !f[x-1][y][xx+1][yy]) {
            if (Map[x-1][y]!=Map[xx+1][yy]) continue;
            f[x-1][y][xx+1][yy]=1;
            q2.push({x-1,y,xx+1,yy});
        }
        if  (x-1>=1 && yy+1<=n && !f[x-1][y][xx][yy+1]) {
            if (Map[x-1][y]!=Map[xx][yy+1]) continue;
            f[x-1][y][xx][yy+1]=1;
            q2.push({x-1,y,xx,yy+1});
        }
        if (y-1>=1 && xx+1<=n && !f[x][y-1][xx+1][yy]) {
            if (Map[x][y-1]!=Map[xx+1][yy]) continue;
            f[x][y-1][xx+1][yy]=1;
            q2.push({x,y-1,xx+1,yy});
        }
        if (y-1>=1 && yy+1<=n && !f[x][y-1][xx][yy+1]) {
            if (Map[x][y-1]!=Map[xx][yy+1]) continue;
            f[x][y-1][xx][yy+1]=1;
            q2.push({x,y-1,xx,yy+1});
        }
    }



    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            f2[i][j][i][j]=1,q2.push({i,j,i,j});
    for (int i=1;i<=n;i++)
        for (int j=1;j<n;j++)
            if (Map2[i][j]==Map2[i][j+1]) f2[i][j][i][j+1]=1,q2.push({i,j,i,j+1});
    for (int i=1;i<n;i++)
        for (int j=1;j<=n;j++)
            if (Map2[i][j]==Map2[i+1][j]) f2[i][j][i+1][j]=1,q2.push({i,j,i+1,j});
    while (q2.size()) {
        int x=q2.front().x,y=q2.front().y,xx=q2.front().xx,yy=q2.front().yy;q2.pop();
        if (x-1>=1 && xx+1<=n && !f2[x-1][y][xx+1][yy]) {
            if (Map2[x-1][y]!=Map2[xx+1][yy]) continue;
            f2[x-1][y][xx+1][yy]=1;
            q2.push({x-1,y,xx+1,yy});
        }
        if  (x-1>=1 && yy+1<=n && !f2[x-1][y][xx][yy+1]) {
            if (Map2[x-1][y]!=Map2[xx][yy+1]) continue;
            f2[x-1][y][xx][yy+1]=1;
            q2.push({x-1,y,xx,yy+1});
        }
        if (y-1>=1 && xx+1<=n && !f2[x][y-1][xx+1][yy]) {
            if (Map2[x][y-1]!=Map2[xx+1][yy]) continue;
            f2[x][y-1][xx+1][yy]=1;
            q2.push({x,y-1,xx+1,yy});
        }
        if (y-1>=1 && yy+1<=n && !f2[x][y-1][xx][yy+1]) {
            if (Map2[x][y-1]!=Map2[xx][yy+1]) continue;
            f2[x][y-1][xx][yy+1]=1;
            q2.push({x,y-1,xx,yy+1});
        }
    }

    for (int x=1;x<=n;x++)
        for (int y=1;y<=n;y++) {
            for (int xx=x;xx<=n;xx++) {
                for (int yy=y;yy<=n;yy++) {
                    if (x+y+2<=xx+yy) {
                        if (f[x][y][xx][yy]!=f2[x][y][xx][yy]) {
                            int it=query(x,y,xx,yy);
                            if (it==f[x][y][xx][yy]) {
                                cout<<"!\n";
                                for (int i=1;i<=n;i++) {
                                    for (int j=1;j<=n;j++)
                                        cout<<Map[i][j];
                                    cout<<"\n";
                                }
                                return 0;
                            } else {
                                cout<<"!\n";
                                for (int i=1;i<=n;i++) {
                                    for (int j=1;j<=n;j++)
                                        cout<<Map2[i][j];
                                    cout<<"\n";
                                }
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
一道很有意思的交互题。

第一次切这样难度的交互，有点开心。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
发现只给了 $n^2$ 次询问次数，而我们就算一次弄出来一个位置也至少要 $n^2-2$，看起来有点难办。

因为不能询问相邻的，所以我们考虑先询问距离为二的。

对这个矩阵进行黑白染色（其中 $1,1$ 为黑点）。

显然的是我们可以对距离为 $2$ 的同色点进行询问，返回 $1$ 则代表颜色相同，否则不同。

那么我们就可以先通过 $1,1$ 把黑点的值全部搞出来。

接着考虑处理白点。

分为两种情况：
1. $n,n$ 为白点时，直接用 $n,n$ 弄出所有白点即可。
2. $n,n$ 也为黑点的时候，考虑找距离为 $3$ 的询问求出一个白点的值。

具体而言，先找到一个满足 $a_{x,y}=1,a_{x+2,y+2}=0$。

那么对于 $a_{x+1,y+1}=1$ 时，便可以询问 $x,y,x+2,y+1$ 来计算出白点的值。

具体的，即为：
```cpp
int xx=get(x+1,y,x+2,y+1);
if(a[x+2][y]^!xx)
{
    a[x+2][y+1]=get(x,y,x+2,y+1);
    a[x+1][y]=!xx^a[x+2][y+1];
}
```
类似的，当 $a_{x+1,y+1}=0$ 时，也可以类似的求出白点的值。
```cpp
else
{
    a[x+1][y]=!get(x+1,y,x+2,y+2);
    a[x+2][y+1]=!xx^a[x+1][y];
}
```
接着再用黑点拓展的方式弄出白点即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=55,INF=0x3f3f3f3f3f3f3f3f,mod=1e9+7;
int dxy[6][2]={{2,0},{0,2},{-2,0},{0,-2},{1,1},{-1,-1}};
int n,a[N][N],mp[N][N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool get(int x,int y,int xx,int yy)
{
	if(x>xx||y>yy) swap(x,xx),swap(y,yy); 
    cout<<"? "<<x<<" "<<y<<" "<<xx<<" "<<yy<<endl;
    cin>>x;return x;
}
inline void bfs(int sx,int sy,int w)
{
    queue<pair<int,int>>q;q.push({sx,sy});a[sx][sy]=w;mp[sx][sy]=1;
    while(!q.empty())
    {
    	int x=q.front().first,y=q.front().second;q.pop();
        for(int i=0;i<6;i++)
        {
            int dx=x+dxy[i][0],dy=y+dxy[i][1];
            if(dx<1||dy<1||dx>n||dy>n) continue;
            if(mp[dx][dy]) continue;q.push({dx,dy});
            a[dx][dy]=a[x][y]^!get(x,y,dx,dy);mp[dx][dy]=1;
        }
    }
}
signed main()
{
    cin>>n;mp[n][n]=1;bfs(1,1,1);bfs(n,n,0);
    if(n%2==0)
    {
        cout<<"!"<<endl;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++) cout<<a[i][j];
            cout<<endl;
        }
        return 0;
    }
    int x=1,y=1;while(a[x+2][y+2]) x+=2,y+=2;
    int xx=get(x+1,y,x+2,y+1);
    if(a[x+2][y]^!xx)
    {
        a[x+2][y+1]=get(x,y,x+2,y+1);
        a[x+1][y]=!xx^a[x+2][y+1];
    }
    else
    {
        a[x+1][y]=!get(x+1,y,x+2,y+2);
        a[x+2][y+1]=!xx^a[x+1][y];
    }
    mp[x+2][y+1]=1;bfs(x+1,y,a[x+1][y]);
    cout<<"!"<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) cout<<a[i][j];
        cout<<endl;
    }
    genshin:;flush();return 0;
}
```

---

## 作者：_maze (赞：0)

很好的一道题，思路自然，步骤清晰，结论好猜。唯一的缺点可能只是我赛时没有看到。



------------
## 构造可行解


看到题目，也许我们很快就能想出一个做法：每次询问 $(i,j,i+1,j)$，每行第一个额外询问 $(i,j,i+1,j)$，这样询问总共 $n ^ 2 - 1$ 次即可。

当我们怀疑看错题目重新检查时发现了被微软翻译漏掉的条件：$x_1+y_1+2 \le x_2 + y_2$。

长度为 $2$ 不行，我们可以长度为 $3$。每次询问 $(i,j,i,j + 2)$，每行第一个额外询问 $(i,j,i + 2,j)$，第一行第一个额外询问 $(1,1,2,2)$，偶数行的 $i$ 从 $2$ 开始。

由于我们已知点 $(1,1)$ 为 $1$，这样相当于往棋盘上染成国际象棋的黑白两色。不妨设点 $(1,1)$ 为黑色，那么我们知道黑色的棋子的确切值。

```cpp
a[1][1] = 1;
a[n][n] = 0;
for (int x = 1; x <= n; ++x) {
  int p = (x & 1 == 1 ? 1 : 2);
  if (x <= n - 2) {
    cout << "? " << x << ' ' << p << ' ' << x + 2 << ' ' << p << endl;
    a[x + 2][p] = a[x][p] ^ (!read());
  }
    
  for (int y = p; y <= n - 2; y += 2) {
    if (y == n - 2 && x == n) break;// 最后一个格子已知，没必要求
    cout << "? " << x << ' ' << y << ' ' << x << ' ' << y + 2 << endl;
    a[x][y + 2] = a[x][y] ^ (!read());
  }
    
  if (x == 1 && x < n) {
    cout << "? " << x << ' ' << p << ' ' << x + 1 << ' ' << p + 1 << endl;
    a[x + 1][p + 1] = a[x][p] ^ (!read());
  }
}
```

我们不知道白色格子的确切值，但是我们可以知道白色格子的相对值。也就是我们假设点 $(1,2)$ 为 $1$，那么我们可以求出所有白色格子的值。方法与上类似，这里不再赘述。

```cpp
b[1][2] = 1;
for (int x = 1; x <= n; x += 2) {
  for (int y = 2; y <= n - 1; y += 2) {
    if (y < n - 1) {
	  cout << "? " << x << ' ' << y << ' ' << x << ' ' << y + 2 << endl;
	  ++cnt;
	  b[x][y + 2] = b[x][y] ^ (!read());	
    }
    if (x < n) {
	  cout << "? " << x << ' ' << y << ' ' << x + 1 << ' ' << y + 1 << endl;
	  b[x + 1][y + 1] = b[x][y] ^ (!read());	
    }
  }
  if (x < n) {
    cout << "? " << x << ' ' << 2 << ' ' << x + 2 << ' ' << 2 << endl;
    b[x + 2][2] = b[x][2] ^ (!read());
    cout << "? " << x + 1 << ' ' << 1 << ' ' << x + 2 << ' ' << 2 << endl;
    b[x + 1][1] = b[x + 2][2] ^ (!read());	  
  }
}
```

现在唯一的问题是，点 $(1,2)$ 既有可能为 $1$，也有可能为 $0$。我们需要判断两种方案哪一种是正确的。在之前的过程中我们对除了 $(1,1),(1,2),(n，n)$ 三个点之外的所有点进行了一次判断，也就是说我们还剩下 $3$ 次询问。

## 判断正确性

既然所有长度为 $3$ 的路径都被我们考虑过了，我们顺理成章地考虑长度为 $4$ 的路线。需要注意的是，我们的解法不能与 $(i,j,i,j + 3)$ 这样的询问有关，因为当 $n = 3$ 时这是一个非法询问（为什么更长长度的路线不考虑？也是思考 $n=3$ 的情况可以把它们全部排除）。

也就是说，我们应该的询问类似于 $(i,j,i + 2,j + 1)$。由于这样的询问在给出否定答案时只能揭露点值的关系，无法给出具体信息，所以我们的判定方法只能是一种方案这个询问为真，另一种方案这个询问为假。在 $(n - 2) \times (n - 1)$ 个矩阵中找出一个满足条件的矩阵进行验证即可。

有没有可能这样的矩阵不存在？我们来分类讨论一下。

### 两种方案均为真

这种情况不存在。因为 $(i,j)$ 必定不和 $(i + 2,j + 1)$ 同色（对颜色的定义参照构造可行解一节），所以两种方案中有且仅有一个点发生改变，所以必定在一种情况里 $(i,j) = (i + 2,j + 1)$，在另一种情况中 $(i,j) \neq (i + 2, j + 1)$。

### 两种情况均为假

一种情况为假有两种可能：

1. 两端点不同。
2. 路径中间上的两个点不同。

所有路径中央的两个点必然属于异色，所以在一种情况不同时，另一种情况必然相同。因此两种方案必定分别属于上面的两种可能。所以这种情况只可能是下面的形式：

第一种：
```
11 10
10 00
01 00
```

第二种：

```
10 11
01 11
11 10
```

由于我们希望所有 $(i,j,i + 2,j + 1)$ 的询问答案均为假，所以我们必须把矩阵补全。但是我们发现了两点：

1. 这两种情况互斥，出现了第一种情况就不可能出现第二种情况。

如果 $n=3$，有一个看似成功的补全：

```
110
101
011
```

但这样 $(n,n) = 1$，不符合题目条件。

否则如果两个连续的 $1$ 不出现在最后，就必定会有一个矩形不存在于两种情况之间，不符合我们的条件。

2. 单一的情况不能补全矩形。

原因是我们不可能出现多个连续的 $1$ 的同时还保证每个 $1$ 下面的数都为一样的数。

因此，这种情况不可能存在。

于是我们找到一个两种方案矛盾的矩形进行询问，选择符合条件的那边即可。总共用了 $n^2 - 2$ 次询问，超额完成任务。

## 代码实现

```cpp
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 55;s

int read() {
  int x;cin >> x;return x;
}

struct mar {
  int a[4][3];
  bool check() {
    if (a[1][1] != a[3][2]) return false;
    if (a[1][2] == a[2][2]) return true;
    if (a[2][1] == a[2][2]) return true;
    if (a[2][1] == a[3][1]) return true;
    return false;
  }
};

int n;
int a[N][N], b[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int x = 1; x <= n; ++x) {
    for (int y = 1; y <= n; ++y) {
      a[x][y] = -1;
    }
  }
  a[1][1] = 1;
  a[n][n] = 0;
  for (int x = 1; x <= n; ++x) {
    int p = (x & 1 == 1 ? 1 : 2);
    if (x <= n - 2) {
      cout << "? " << x << ' ' << p << ' ' << x + 2 << ' ' << p << endl;
      a[x + 2][p] = a[x][p] ^ (!read());
    }
    
    for (int y = p; y <= n - 2; y += 2) {
      if (y == n - 2 && x == n) break;
      cout << "? " << x << ' ' << y << ' ' << x << ' ' << y + 2 << endl;
      a[x][y + 2] = a[x][y] ^ (!read());
    }
    
    if (x == 1 && x < n) {
      cout << "? " << x << ' ' << p << ' ' << x + 1 << ' ' << p + 1 << endl;
      a[x + 1][p + 1] = a[x][p] ^ (!read());
    }
  }

  
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      b[i][j] = -1;
    }
  }
  b[1][2] = 1;
  for (int x = 1; x <= n; x += 2) {
    for (int y = 2; y <= n - 1; y += 2) {
      if (y < n - 1) {
        cout << "? " << x << ' ' << y << ' ' << x << ' ' << y + 2 << endl;
        b[x][y + 2] = b[x][y] ^ (!read());	
      }
      if (x < n) {
        cout << "? " << x << ' ' << y << ' ' << x + 1 << ' ' << y + 1 << endl;
        b[x + 1][y + 1] = b[x][y] ^ (!read());	
      }
    }
    if (x < n) {
      cout << "? " << x << ' ' << 2 << ' ' << x + 2 << ' ' << 2 << endl;
      b[x + 2][2] = b[x][2] ^ (!read());

      cout << "? " << x + 1 << ' ' << 1 << ' ' << x + 2 << ' ' << 2 << endl;
      b[x + 1][1] = b[x + 2][2] ^ (!read());	
      
    }
  }
  // we find a and b

  mar z, f;
  int chk = 0, pd = 0;
  for (int i = 1; i <= n - 2; ++i) {
    for (int j = 1; j <= n - 1; ++j) {
      for (int x = i, wx = 1; x <= i + 2; ++x, ++wx) {
        for (int y = j, wy = 1; y <= j + 1; ++y, ++wy) {
        if (a[x][y] == -1) z.a[wx][wy] = b[x][y];
        else z.a[wx][wy] = a[x][y];
        }
      }
      for (int x = i, wx = 1; x <= i + 2; ++x, ++wx) {
        for (int y = j, wy = 1; y <= j + 1; ++y, ++wy) {
        if (a[x][y] == -1) f.a[wx][wy] = !b[x][y];
        else f.a[wx][wy] = a[x][y];
        }
      }
      if (z.check() != f.check()) {
        cout << "? " << i << ' ' << j << ' ' << i + 2 << ' ' << j + 1 << endl;
        int tmp = read();
        if (tmp == f.check()) chk = 1;
        pd = 1;
        break;
      }
    }
    if (pd == 1) break;
  }

  cout << "!" << endl;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (a[i][j] != -1) cout << a[i][j];
      else cout << (b[i][j] ^ chk);
    }
    cout << endl;
  }

  return 0;	
}

```



---

