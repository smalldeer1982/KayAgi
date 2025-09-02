# 「FSLOI Round I」迷雾

## 题目背景

小 F 来到了迷雾之森。

## 题目描述

整个迷雾之森可以由一个 $n \times m$ 的矩阵表示，`X` 代表有迷雾的地块，`.` 代表空地。从上到下给每行标号为 $1,2,\cdots,n$，从左到右给每列标号为 $1,2,\cdots,m$。除此之外，还会给定一个迷雾系数 $k$。

小 F 进行了 $q$ 次移动。第 $i$ 次移动由一个字符 $c_i$，两个数字 $a_i,b_i$ 描述，更具体地说：

- $c_i$ 为 `U` 时，向上走 $a_i$ 步。
- $c_i$ 为 `D` 时，向下走 $a_i$ 步。
- $c_i$ 为 `L` 时，向左走 $a_i$ 步。
- $c_i$ 为 `R` 时，向右走 $a_i$ 步。

当然，小 F 不可以走出这个 $ n \times m $ 的范围。换句话说，若走到边界处，立即结束此次移动。

若第 $i$ 次移动**结束**后小 F 停留在有迷雾的地块上，则小 F 会对从 $i+k$ 开始，之后每 $k$ 次移动的 $c$ 进行一次修改，一共修改 $b_i$ 个移动。也就是说，小 F 会对 $c_{i+k},c_{i+2\times k},\cdots,c_{i+b_i \times k}$ 进行一次**修改**（保证 $i+b_i\times k \leq q$）。若 $b_i=0$ 则相当于不做修改。**注意所有操作的 $k$ 是一样的**。

修改 $c_x$ 即为按照以下规则替换 $c_x$：

- 若 $c_x$ 为 `U`，则替换为 `D`。
- 若 $c_x$ 为 `D`，则替换为 `U`。
- 若 $c_x$ 为 `R`，则替换为 `L`。
- 若 $c_x$ 为 `L`，则替换为 `R`。

初始时小 F 在点 $(1,1)$ 处，请输出 $q$ 次移动后小 F 所在的位置 $(x,y)$。

## 说明/提示

**【样例 1 解释】**

小 F 的位置变化如下：

$(1,1) \rightarrow (2,1) \rightarrow (2,2)\rightarrow (1,2) \rightarrow (1,3)$

序列 $c$ 的变化如下：

$ \lbrace \texttt{D,R,D,L} \rbrace \rightarrow \lbrace \texttt{D,R,D,L} \rbrace \rightarrow \lbrace \texttt{D,R,U,R} \rbrace \rightarrow \lbrace \texttt{D,R,U,R} \rbrace \rightarrow \lbrace \texttt{D,R,U,R} \rbrace$

**【数据规模与约定】**

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，保证：
- $1 \leq n,m \leq 500$
- $1 \leq k \leq 20$
- $1\leq q \leq 2 \times 10^5$
- $1 \leq a_i,b_i \leq 10^6$
- $c_i$ 为 `L`，`R`，`U`，`D` 四个字符中的一个。

|子任务|分值|特殊性质|
|:-----:|:-----:|:-----:|
|$1$|$5$|$q=1$|
|$2$|$15$|$n,m,q\leq 100$|
|$3$|$20$|$k=1$|
|$4$|$30$|$n=1$|
|$5$|$30$|无|

## 样例 #1

### 输入

```
3 3 4 1
..X
.XX
XXX
D 1 2
R 1 2
D 2 0
L 1 0
```

### 输出

```
1 3
```

## 样例 #2

### 输入

```
10 10 8 2
XX.XX.X...
XXX..XXX.X
XXX.X.XXXX
XXXXXXX.X.
.XX...XX.X
.XXX.X.X.X
...XXX.XXX
XX...XX...
X..XX....X
XXXXX...XX
U 2 1
L 1 3
R 3 1
L 1 2
D 2 1
R 5 1
L 4 0
D 3 0
```

### 输出

```
1 10
```

# 题解

## 作者：FL_sleake (赞：14)

### 解题思路

维护坐标是简单的，注意走到边界处时及时停下即可。难点在于修改操作。

#### Subtask 1

由于 $q=1$，所以输出移动一次后的位置即可。

#### Subtask 2

$n,m$ 其实没有用。由于 $q \leq 100$，考虑按照题目描述的暴力修改 $c_i$ 即可。

#### Subtask 3

首先需要发现对 $c_i$ 进行偶数次修改等于没有修改，进行奇数次修改等于修改一次。

由于 $k=1$，所以每次修改的都是连续段，提高组选手可以考虑一个线段树砸上去。但是这是基础赛，所以我们考虑差分。维护一个 $flag$ 代表是否修改。如果第 $i$ 次移动结束后需要修改，先把 $flag$ 异或上 $1$，再维护一个差分数组 $cnt$，将 $cnt_{i+b_i+1}$ 也异或上 $1$。在第 $i$ 次移动前，让 $flag$ 异或上当前的 $cnt_i$ 即可。

#### Subtask 4 & 5

发现 $k$ 的加入并没有本质影响。实际上就是把 $c$ 序列按照下标除以 $k$ 的余数分成了 $k$ 组。提高组选手可以考虑 $k$ 个线段树砸上去，并没有刻意卡线段树。但是这是基础赛，所以我们考虑 $k$ 个差分砸上去即可。和 Subtask 3 没有本质区别。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,q;
string s[510];
char c[200010];
int a[200010],b[200010];
int cnt[200100][25],flg[25];
//修改的函数
char Change(char x){
	if(x=='U') return 'D';
	if(x=='D') return 'U';
	if(x=='L') return 'R';
	if(x=='R') return 'L'; 
}
signed main(){
	cin>>n>>m>>q>>k;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	for(int i=1;i<=q;i++) cin>>c[i]>>a[i]>>b[i];
	int x=1,y=1;
	for(int i=1;i<=q;i++){
		int id;
      //判断除以k的余数
		if(i%k==0) id=k;
		else id=i%k;
		flg[id]^=cnt[i][id];
      //修改
		if(flg[id]) c[i]=Change(c[i]);
      //移动
		if(c[i]=='U') x=max(1ll,x-a[i]);
		if(c[i]=='D') x=min(n,x+a[i]);
		if(c[i]=='L') y=max(1ll,y-a[i]);
		if(c[i]=='R') y=min(m,y+a[i]);
      //修改，利用差分思想
		if(s[x][y]=='X') flg[id]^=1,cnt[i+b[i]*k+k][id]^=1;
	}
	cout<<x<<" "<<y<<endl;
	return 0;
}
```

事实上空间复杂度可以优化到 $\Theta(n)$，因为上述代码中 $cnt$ 数组实际用到的空间只有 $\Theta(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,q;
string s[510];
char c[200010];
int a[200010],b[200010];
int cnt[200100],flg[25];
//修改的函数
char Change(char x){
	if(x=='U') return 'D';
	if(x=='D') return 'U';
	if(x=='L') return 'R';
	if(x=='R') return 'L'; 
}
signed main(){
	cin>>n>>m>>q>>k;
	for(int i=1;i<=n;i++) cin>>s[i],s[i]=" "+s[i];
	for(int i=1;i<=q;i++) cin>>c[i]>>a[i]>>b[i];
	int x=1,y=1;
	for(int i=1;i<=q;i++){
		int id;
      //判断除以k的余数
		if(i%k==0) id=k;
		else id=i%k;
		flg[id]^=cnt[i];
      //修改
		if(flg[id]) c[i]=Change(c[i]);
      //移动
		if(c[i]=='U') x=max(1ll,x-a[i]);
		if(c[i]=='D') x=min(n,x+a[i]);
		if(c[i]=='L') y=max(1ll,y-a[i]);
		if(c[i]=='R') y=min(m,y+a[i]);
      //修改，利用差分思想
		if(s[x][y]=='X') flg[id]^=1,cnt[i+b[i]*k+k]^=1;
	}
	cout<<x<<" "<<y<<endl;
	return 0;
}
```

---

## 作者：fishing_cat (赞：12)

### 闲话
作为第三题，个人感觉要比第二题简单。

### 题意

给你一个地图，初始位置 $(1,1)$，按照操作移动。

若一次操作进入迷雾，会使后面的一些操作发生改变。

注意，走到边界处，要立即结束此次移动。

### 分析

首先，大家都会写 $O(q^2)$ 的暴力。贴一下我的[暴力代码](https://www.luogu.com.cn/record/177895263)。

可以发现时间复杂度的瓶颈在每次移动后的暴力修改后面的移动方向。      
还可以发现，对一个方向的修改，偶数次修改是没有意义的。所以可以用异或操作去维护。

在题面中，**注意所有操作的 $k$ 是一样的**已经被用黑体标出了。然后不难发现，可以将所有操作操作分成 $k$ 组，每一组只存储操作下标对 $k$ 取模后结果相同的。

为什么要这样分？因为在进入迷雾时只会对后面操作下标对 $k$ 取模后结果相同的操作进行修改。          
如果还不懂，可以自己手推一下喵。

这样我们就有了 $k$ 个串，然后就是要区间异或，单点查询值了。区间修改，单点查询？线段树？

想了想还是用了差分数组，~~害怕线段树被卡~~。因为每次的修改都不会影响已经用过的值，所以可以一边修改差分数组一边维护这一位的实际值。而且又快又好写。     
关于差分数组，可以看看这篇[博客](https://blog.nowcoder.net/n/71b183a54c354b248154f4089487b1f7?from=nowcoder_improve)。

然后就把 $O(q^2)$ 的时间复杂度优化到了 $O(q)$ 了。更多细节看代码吧。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;
// 快读省了
ll n, m, q, k;
ll a[200100];
char mp[600][600];
ll fx[200100], s[200100], cnum[200100];
bool f[200100][200];// 第一位是在当前串中值的编号， 第二位是串的编号
ll vel[200];

int main() { // 代码不难写的
	read(n); read(m); read(q); read(k);
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m;j++) 
			cin >> mp[i][j];
	char r;
	for (int i = 1; i <= q; i++) {
		cin >> r; // 关于后面为申么要这样赋值，额，数字好翻转
		if (r == 'L') fx[i] = 1;
		if (r == 'R') fx[i] = 2;
		if (r == 'D') fx[i] = 12;
		if (r == 'U') fx[i] = 11;
		read(s[i]); read(cnum[i]);
	}
	ll nowx = 1, nowy  = 1;
	ll flog = 0;
	for (int i = 1; i <= q; i++) {
		vel[i%k] ^= f[i/k+flog][i%k]; 
		if (vel[i%k] == 1) { // 是 1 ， 翻转
			if (fx[i] % 2 == 0) fx[i]--;
			else fx[i] ++;
		}
		if(fx[i] == 1) {
			nowy -= s[i];
			if (nowy < 1) nowy = 1; // 注意边界
		} else if (fx[i] == 2) {
			nowy += s[i];
			if (nowy > m) nowy = m; // 注意边界
		} else if (fx[i] == 11) {
			nowx -= s[i];
			if (nowx < 1) nowx = 1; // 注意边界
		}else {
			nowx += s[i];
			if (nowx > n) nowx = n; // 注意边界
		}
		if (mp[nowx][nowy] == 'X' && cnum[i] != 0) { // 更新差分数组
			f[i/k + 1 +flog][i%k] ^= 1;
			f[i/k + cnum[i]+1 + flog][i%k] ^= 1;
		}
	}
	cout << nowx << " " << nowy << "\n";
	return 0;// 完结撒花
}
```

---

## 作者：ycy1124 (赞：8)

### 题意
有一个 $n \times m$ 由 ```X``` 和 ```.``` 组成的地图，你从左上角出发，每次给出一个向一个方向走多少步的命令，假如**停下**时在 ```X``` 上面，就把第 $i+k$，$i+2 \times k$ $\cdots$ $i+b_i \times k$ 次命令的方向修改为**相反的方向**。
### 注意
1.修改是可以叠加的。

2.当执行命令后会超出地图，还是会执行，只是在碰到边缘时停止。
### 20 分做法
模拟这个走的过程，然后每次停在 ```X``` 上时暴力打上标记。
### 20 分代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[501][501];
bool md[200001];
int main(){
	int n,m,q,k;
	scanf("%d%d%d%d",&n,&m,&q,&k);
	int x=1,y=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];//读入地图
		}
	}
	for(int i=1;i<=q;i++){
		char ch;
		int w,b;
		cin>>ch;
		scanf("%d%d",&w,&b);
		if(ch=='U'){//模拟
			if(md[i]){
				x=min(x+w,n);
			}
			else{
				x=max(x-w,1);
			}
		}
		else if(ch=='D'){
			if(md[i]){
				x=max(x-w,1);
			}
			else{
				x=min(x+w,n);
			}
		}
		else if(ch=='L'){
			if(md[i]){
				y=min(y+w,m);
			}
			else{
				y=max(y-w,1);
			}
		}
		else{
			if(md[i]){
				y=max(y-w,1);
			}
			else{
				y=min(y+w,m);
			}
		}
		if(a[x][y]=='X'){//停留在X上了
			for(int j=1;j<=b;j++){
				md[i+j*k]=!md[i+j*k];//取反就等于变成相反的方向
			}
		}
	}
	printf("%d %d",x,y);
	return 0;
}
```
### 100 分做法
我们不难发现，$i+k$，$i+2 \times k$ $\cdots$ $i+b_i \times k$ 他们除 $k$ 的余数都是相同的，因此我们可以按除 $k$ 的余数分成 $k$ 组来打标记。

分组之后，标记显然变成连续的了，因此我们可以把标记看成一段区间，当第 $i$ 次命令时，只有区间的 $r \ge i$ 的标记是对于 $i$ 有效的，因此我们可以用 $k$ 个小根堆来维护每组标记区间的 $r$，当 $r < i$ 时将其弹出。通过判断堆内剩下的区间个数的奇偶性来判断是否为相反方向。
### 100 分代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[501][501];
struct Node{
	int t[200001],tot=0;
}md[20];//分组标记 
void work(int p,int x){//基本的堆函数 
	if(x*2+1<=md[p].tot&&md[p].t[x]>md[p].t[x*2]&&md[p].t[x*2]<md[p].t[x*2+1]){
		swap(md[p].t[x],md[p].t[x*2]);
		work(p,x*2);
	}
	else if(x*2+1<=md[p].tot&&md[p].t[x]>md[p].t[x*2+1]){
		swap(md[p].t[x],md[p].t[x*2+1]);
		work(p,x*2+1);
	}
	else if(x*2==md[p].tot&&md[p].t[x]>md[p].t[x*2]){
		swap(md[p].t[x],md[p].t[x*2]);
		work(p,x*2);
	}
}
void work1(int p,int x){//基本的堆函数 
	if(md[p].t[x]<md[p].t[x/2]){
		swap(md[p].t[x],md[p].t[x/2]);
		work1(p,x/2);
	}
}
int main(){
	int n,m,q,k;
	scanf("%d%d%d%d",&n,&m,&q,&k);
	int x=1,y=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];//读入地图 
		}
	}
	for(int i=1;i<=q;i++){//模拟 
		char ch;
		int w,b;
		cin>>ch;
		scanf("%d%d",&w,&b);
		if(ch=='U'){
			if(md[i%k].tot%2==1){//通过判断堆内区间个数的奇偶性来判断是否取反方向 
				x=min(x+w,n);
			}
			else{
				x=max(x-w,1);
			}
		}
		else if(ch=='D'){
			if(md[i%k].tot%2==1){
				x=max(x-w,1);
			}
			else{
				x=min(x+w,n);
			}
		}
		else if(ch=='L'){
			if(md[i%k].tot%2==1){
				y=min(y+w,m);
			}
			else{
				y=max(y-w,1);
			}
		}
		else{
			if(md[i%k].tot%2==1){
				y=max(y-w,1);
			}
			else{
				y=min(y+w,m);
			}
		}
		if(a[x][y]=='X'){//重点打标记部分 
			md[i%k].t[++md[i%k].tot]=i+b*k;//将i~i+b*k的标记区间放入堆中。 
			work1(i%k,md[i%k].tot);
		}
		while(md[i%k].tot>0&&md[i%k].t[1]<=i){//如果堆顶的区间r小于i就弹出 
			swap(md[i%k].t[1],md[i%k].t[md[i%k].tot]);
			md[i%k].tot--;
			work(i%k,1);
		}
	}
	printf("%d %d",x,y);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/177907490)。

---

## 作者：hez_EX (赞：8)

经典套路，难度不高。目前最优解。

---

**你猜题目为什么声明所有操作 $k$ 是一样的？**

---

移动不用说，每次维护变量，记得取 $\min$ 和 $\max$ 防止跑出边界。问题在于当被 `X` 代表的迷雾迷之后它会影响后续的走法。

注意到方向的映射无非两种：
 - $\{U,D,R,L\}\rightarrow\{U,D,R,L\}$；
 - $\{U,D,R,L\}\rightarrow\{D,U,L,R\}$。

并且连续用变换两次之后会变回原状。

先忽略 $k$ 的影响，令 $k=1$，那么考虑用类似差分的方式处理，在开头 $i$ 反转一次，结尾 $i+b$ 的地方再记录一个反转 $rev_{i+b}:=rev_{i+b}\oplus 1$。每走到一个新地方 $j$，就先把 $rev_j$ 读了对应真实状态异或一下。

因为差分使用的异或，所以**本质上**开头的反转和结束的反转回来是同一操作。

再考虑 $k\ge1$ 的情况。注意到这构成了一个等差数列，而等差数列最显著的（也最容易被忽略的）特征即所有数字在模公差意义下同余，鉴于 $k$ 极小，直接记录 $k$ 的剩余系的反转状态即可。

### AC 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#define ll long long
using namespace std;
inline void read(int &x)
{
	char c=getchar();x=0;
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10-48+c,c=getchar();
}
int n,m,q,k,mp[128],x,y,a,b;
bool st[25],rev[200005];
char c,f[505][505];
//0U 1D 2R 3L
const int dir[2][4]={{0,1,2,3},{1,0,3,2}};
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,1,-1};
int main()
{
	read(n);read(m);read(q);read(k);
	mp['U']=0;mp['D']=1;mp['R']=2;mp['L']=3;
	for(int i=1;i<=n;i++) scanf("%s",f[i]+1);
	x=y=1;
	for(int i=1;i<=q;i++)
	{
		c=getchar();
		while(!isalpha(c)) c=getchar();
		read(a);read(b);
		x+=a*dx[dir[st[i%k]][mp[c]]];
		y+=a*dy[dir[st[i%k]][mp[c]]];
		x=max(1,x);x=min(n,x);
		y=max(1,y);y=min(m,y);
		if(f[x][y]=='X') st[i%k]^=1,rev[i+k*b]^=1;
		if(rev[i]) st[i%k]^=1;
	}
	printf("%d %d\n",x,y);
	return 0;
}
```

---

## 作者：dayz_break404 (赞：5)

### 题目分析
阅读题面，发现坐标转移很容易，重点在于考虑当前移动的方向是否有被翻转。

考虑当前若在迷雾地块上后，对后面翻转的贡献。根据题意，可以发现被更改的操作标号是每次跳跃 $k$ 个位置的，这样的操作很难让人不想到线段树，但是这样的更改是跳跃的。

考虑将更改变成连续的，我们可以将长度为 $q$ 的操作序列分成若干个长度为 $k$ 的块，将每个块作为一个节点，用线段树维护每个块，观察到 $k$ 的范围很小，可以对于每个线段树上的节点开一个大小为 $k$ 的数组，表示是否要翻转方向，对应修改时只需要打上对应的懒标记，查询时递归到叶子节点即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x*f;
}
const int maxn=520;
const int maxm=2e5+20;
char mp[maxn][maxn];
int n,m,q,k;
struct node{
	int tag[23],val[23];
}tree[maxm<<2];
struct segment_tree{
	inline int ls(int x){
		return x<<1;
	}
	inline int rs(int x){
		return x<<1|1;
	}
	inline void push_down(int p){
		for(int i=1;i<=k;i++) 
			tree[ls(p)].val[i]^=tree[p].tag[i],tree[ls(p)].tag[i]^=tree[p].tag[i];
		for(int i=1;i<=k;i++) 
			tree[rs(p)].val[i]^=tree[p].tag[i],tree[rs(p)].tag[i]^=tree[p].tag[i],tree[p].tag[i]=0;
	}
	void update(int p,int l,int r,int k,int x,int y){
		if(x<=l&&y>=r){
			tree[p].val[k]^=1,tree[p].tag[k]^=1;
			return;
		}
		push_down(p);
		int mid=l+r>>1;
		if(x<=mid) update(ls(p),l,mid,k,x,y);
		if(y>mid) update(rs(p),mid+1,r,k,x,y);
	}
	int query(int p,int l,int r,int x,int k){
		if(l==r) return tree[p].val[k];
		push_down(p);
		int mid=l+r>>1;
		if(x<=mid) return query(ls(p),l,mid,x,k);
		else return query(rs(p),mid+1,r,x,k);
	}
}S;
int nowx=1,nowy=1,block;
int main(){
	n=read(),m=read(),q=read(),k=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
		}
	}
	block=(int)ceil(1.0*q/k);
	char op;
	int x,y;
	for(int i=1;i<=q;i++){
		cin>>op;
		x=read(),y=read();
		if(S.query(1,1,block,(int)ceil(1.0*i/k),i%k+1)){
			if(op=='U') op='D';
			else if(op=='D') op='U';
			else if(op=='L') op='R';
			else op='L';
		}
		if(op=='U') nowx=max(1,nowx-x);
		else if(op=='D') nowx=min(n,nowx+x);
		else if(op=='L') nowy=max(1,nowy-x);
		else nowy=min(m,nowy+x);
		if(mp[nowx][nowy]=='X'&&i+k<=q) S.update(1,1,block,i%k+1,(int)ceil(1.0*i/k)+1,min(block,(int)ceil(1.0*i/k)+y));
	}
	printf("%d %d\n",nowx,nowy);
	return 0;
}

```
~~好像可以用差分，傻了qwq。~~

---

## 作者：WZWZWZWY (赞：4)

很简单的一道题，赛时一眼秒了，难度大概是黄（摊手）。


---


观察题目，容易得到：

+ 每次“修改”会上下颠倒，左右颠倒。
+ “修改”两次等于没操作。
+ $n,m\le 500,k\le 20$。

题目的“修改”操作：

> $c_{i+k},c_{i+2\times k},\cdots,c_{i+b_i \times k}$ 进行一次**修改**

修改的是类似 $c_{i+x\times k}$，而 $k$ 很小，可以把所有模 $k$ 的同余项放在一起。因为要把连续的一段都修改，所以要用差分，最后根据差分数组前缀和的奇偶性判断要不要“修改”这个位置。

本题的坐标轴如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/i3axul3c.png)

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

bool ks[25][200005]; // 差分数组 

int dx[] = {-1, 1, 0, 0}; // 上 下 左 右 
int dy[] = {0, 0, -1, 1};
int n, m, q, k;

char c[505][505];

int ne(char op, bool k) { // 判断当前应该是往那个方向走 
	if (op == 'U') return 0 ^ k;
	else if (op == 'D') return 1 ^ k;
	else if (op == 'L') return 2 ^ k;
	else return 3 ^ k;
}

void move(int &x, int &y, char op, int a, bool k) { // 移动 
	int xd = ne(op, k);
	x += dx[xd] * a; y += dy[xd] * a;
	x = max(1, min(x, n));
	y = max(1, min(y, m));
}

int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> n >> m >> q >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) cin >> c[i][j];
	
	int nx = 1, ny = 1;
	
	for (int i = 1; i <= q; i++) {
		ks[i % k][i] ^= ks[i % k][i - k];
		
		char op; cin >> op;
		int a, b; cin >> a >> b;
		
		move(nx, ny, op, a, ks[i % k][i]); 

		if (c[nx][ny] == 'X' && b) { // 维护差分数组 
			ks[i % k][i + k] ^= 1;
			ks[i % k][min(i + (b+1)*k, q + 1)] ^= 1;
		}
	}
	cout << nx << " " << ny;
}
```

---

## 作者：mysterys (赞：4)

挺好的一道题。

# 思路

首先进行模拟，可以拿到 $20$ 分。

然后考虑怎么优化，发现瓶颈在于修改操作。

1. 注意到修改 $c_i$ 的方法其实类似异或，所以只需要统计次数即可。
2. 将下标按对 $k$ 的同余分组，发现每个下标要操作的次数是之前的同余的下标的需要操作次数之和。
3. 综上，可以考虑用差分维护。

# 优化

如果直接按上面的写，空间复杂度是 $O(k \times N)$，但是我们发现：差分数组实际上使用的是 $O(N)$，所以可以有如下优化：

- 另外开一个数组，记录当前下标的**同余前驱**，每次转移时从前驱处转移。
- 进行差分操作时，利用同余进行操作。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
#define endl '\n'
#define ll long long
const int N=2e5+5;
char mp[505][505];
struct node{
    char opt;int x,b;
}a[N];
int x=1,y=1;
int n,m,q,k;
int cnt[25],lst[N];
int s[N];
inline void upd(int id){
    if(a[id].opt=='U') a[id].opt='D';
    else if(a[id].opt=='D') a[id].opt='U';
    else if(a[id].opt=='R') a[id].opt='L';
    else if(a[id].opt=='L') a[id].opt='R';
}
inline void solve(int id){
    if(a[id].opt=='U') x-=a[id].x;
    if(a[id].opt=='D') x+=a[id].x;
    if(a[id].opt=='L') y-=a[id].x;
    if(a[id].opt=='R') y+=a[id].x;
    if(x<1) x=1;if(y<1) y=1;
    if(x>n) x=n;if(y>m) y=m;
}
signed main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr);
    cin>>n>>m>>q>>k;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>mp[i][j];
    for(int i=1;i<=q;i++){
        cin>>a[i].opt>>a[i].x>>a[i].b;
        lst[i]=cnt[i%k];
        cnt[i%k]=i;
    }
    for(int i=1;i<=q;i++){
        s[i]^=s[lst[i]];
        if(s[i]==1) upd(i);
        solve(i);
        if(mp[x][y]=='X'){
            s[i]^=1;
            if(i+(a[i].b+1)*k<=q) s[i+(a[i].b+1)*k]^=1;
        }
    }
    cout<<x<<' '<<y;
    return 0;
}
```

---

## 作者：naroto2022 (赞：4)

# P11078 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/P11078)

### 思路

本蒟蒻太菜了，只会用线段树。。。（准确来说这题是线段森林？）

首先很自然的想到可以按模 $k$ 的余数来分类开线段树，这样每一次在迷雾上的操作就是区间异或，最后于是判断当前节点是否需要改就可以了，思路非常简单，打代码的时候细心点就可以过了。

当然，这样的话要特判下 $q=1$ 的情况，不然会 RE。（别问我怎么知道的）

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int MN=2e5+5,MM=505;
ll num,n,m,q,k,x=1,y=1,a,b,dx[5]={0,-1,0,1,0},dy[5]={0,0,1,0,-1};
char mp[MM][MM],op;
struct node{ll num,l,r;bool tag;}t[25][MN<<2];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll gs(ll ch){if(ch=='U') return 1;if(ch=='D') return 3;if(ch=='R') return 2;return 4;}
void build(ll p, ll l, ll r, ll i){
    t[i][p].l=l,t[i][p].r=r;t[i][p].tag=false;
    if(l==r){
        t[i][p].num=0;
        return;
    }
    ll mid=(l+r)>>1;
    build(ls,l,mid,i);build(rs,mid+1,r,i);
    t[i][p].num=t[i][ls].num+t[i][rs].num;
}
void pushdown(ll p, ll i){
    if(t[i][p].tag){
        t[i][p].tag=false;
        t[i][ls].tag=t[i][ls].tag?false:true;
        t[i][rs].tag=t[i][rs].tag?false:true;
        t[i][ls].num=t[i][ls].r-t[i][ls].l+1-t[i][ls].num;
        t[i][rs].num=t[i][rs].r-t[i][rs].l+1-t[i][rs].num;
    }
}
void change(ll p, ll l, ll r, ll i){
    if(l<=t[i][p].l&&t[i][p].r<=r){
        t[i][p].num=t[i][p].r-t[i][p].l+1-t[i][p].num;
        t[i][p].tag=t[i][p].tag?false:true;
        return;
    }
    pushdown(p,i);
    ll mid=(t[i][p].l+t[i][p].r)>>1;
    if(l<=mid) change(ls,l,r,i);
    if(r>mid) change(rs,l,r,i);
    t[i][p].num=t[i][ls].num+t[i][rs].num;
}
ll query(ll p, ll x, ll i){
    if(t[i][p].l==t[i][p].r) return t[i][p].num;
    pushdown(p,i);
    ll mid=(t[i][p].l+t[i][p].r)>>1,res=0;
    if(x<=mid) res=res^query(ls,x,i);
    if(x>mid) res=res^query(rs,x,i);
    return res;
}
int main(){
    // freopen("1.in","r",stdin);
    n=read();m=read();q=read();k=read();
    for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) cin>>mp[i][j];
    if(q==1){
        cin>>op;a=read();b=read();
        num=gs(op);
        x=max(1ll,min(n,x+dx[num]*a));
        y=max(1ll,min(m,y+dy[num]*a));
        write(x);putchar(' ');write(y);
        return 0;
    }
    for(int i=0; i<k; i++) build(1,1,q/k,i);
    for(int i=1; i<=q; i++){
        cin>>op;a=read();b=read();
        num=gs(op);
        if(query(1,i/k,i%k)){
            if(num==1) num=3;
            else if(num==2) num=4;
            else if(num==3) num=1;
            else num=2;
        }
        x=max(1ll,min(n,x+dx[num]*a));
        y=max(1ll,min(m,y+dy[num]*a));
        if(mp[x][y]=='X') change(1,i/k+1,min(i/k+b,q/k),i%k);
    }
    write(x),putchar(' '),write(y);
	return 0;
}
```

---

## 作者：VitrelosTia (赞：2)

问题的关键显然是 $c$ 的变化，考虑对于一个 $c_x$ 被第 $i$ 次操作改变到当且仅当 $x = i + kp$，其中 $1 \le p \le b_i$，这有点类似同余式的形式，然后你又发现 $k$ 非常小，于是开 20 个线段树分别维护每个余数在每个位置上的变化次数就做完了。

赛时思路不是很清晰，代码比较幽默所以仅展示部分。

```cpp
int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m >> Q >> k;
	retab['U'] = -1, retab['D'] = 1, retab['L'] = 2, retab['R'] = -2;
	for (int i = 0; i < k; i++) t[i].build(1, 1, Q);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		cin >> mp[i][j];
	int x = 1, y = 1;
	for (int i = 1; i <= Q; i++) {
		char c; int a, b, o; cin >> c >> a >> b; o = retab[c];
		int d = t[i % k].query(1, i / k);
		if (d & 1) o = -o;
		if (o == -1) x = max(x - a, 1);
		if (o == 1) x = min(x + a, n);
		if (o == 2) y = max(y - a, 1);
		if (o == -2) y = min(y + a, m);
		if (mp[x][y] == 'X' && b > 0) t[i % k].update(1, i / k + 1, i / k + b);
	}
	cout << x << ' ' << y << '\n';
	return 0;
}
```

---

## 作者：Hisy (赞：2)

## Subtask 1&2
很明显的暴力模拟，每到一个迷雾点，那就再后面更新符号，时间复杂度 $\operatorname{O}(q^2)$。
```cpp
#include<iostream>
#include<algorithm>
#define MAXN 505
#define MAXM 200002
using namespace std;
int n,m,q,k,a[MAXM],b[MAXM];
char mp[MAXN][MAXN],c[MAXM];
int dy[4]={0,0,-1,1};
int dx[4]={1,-1,0,0};
inline int turn(char c){
	if(c=='D'){
		return 0;
	}
	if(c=='U'){
		return 1;
	}
	if(c=='L'){
		return 2;
	}
	return 3;
}
inline char change(char c){
	if(c=='U'){
		return 'D';
	}
	if(c=='D'){
		return 'U';
	}
	if(c=='L'){
		return 'R';
	}
	return 'L';
}
int main(){
	scanf("%d %d %d %d",&n,&m,&q,&k);
	for(int i=1;i<=n;++i){
		scanf("%s",mp[i]+1);
	}
	for(int i=1;i<=q;++i){
		scanf("\n%c %d %d",&c[i],&a[i],&b[i]);
	}
	int x=1,y=1;
	for(int i=1;i<=q;++i){
		x+=dx[turn(c[i])]*a[i];
		y+=dy[turn(c[i])]*a[i];
		x=min(max(x,1),n);
		y=min(max(y,1),m);
//		cout<<x<<" "<<y<<endl;
		if(mp[x][y]=='X'){
			for(int j=1;j<=b[i];++j){
				c[i+j*k]=change(c[i+j*k]);
			}
		}
//		for(int j=1;j<=q;++j){
//			cout<<c[j]<<" ";
//		}
//		cout<<endl;
	}
	printf("%d %d",x,y);
	return 0;
}
```
## Subtask 3
考虑 $k=1$ 的情况，即每到一个迷雾点，就更新 $[i+1,i+b_i]$，加上 $1$，当一个点它的值为偶数的时候，就会变回去，否则就要变。这个可以用维护差分数组的树状数组维护。时间复杂度 $\operatorname{O}(q\log q)$，仅限于 $k=1$。
```cpp
#include<iostream>
#include<algorithm>
#define MAXN 505
#define MAXM 200002
using namespace std;
int n,m,q,k,a[MAXM],b[MAXM];
char mp[MAXN][MAXN],c[MAXM];
int tree[MAXM<<1];
int dy[4]={0,0,-1,1};
int dx[4]={1,-1,0,0};
inline int turn(char c){
	if(c=='D'){
		return 0;
	}
	if(c=='U'){
		return 1;
	}
	if(c=='L'){
		return 2;
	}
	return 3;
}
inline char change(char c){
	if(c=='U'){
		return 'D';
	}
	if(c=='D'){
		return 'U';
	}
	if(c=='L'){
		return 'R';
	}
	return 'L';
}
inline int lowbit(int x){
	return x&-x;
}
inline void modify(int p,int add){
	for(int i=p;i<MAXM;i+=lowbit(i)){
		tree[i]+=add;
	}
}
inline int query(int p){
	int ans=0;
	for(int i=p;i;i-=lowbit(i)){
		ans+=tree[i];
	}
	return ans;
}
inline void work(){
	int x=1,y=1;
	for(int i=1;i<=q;++i){
		if(query(i)%2==1){
			c[i]=change(c[i]);
		}
		x+=dx[turn(c[i])]*a[i];
		y+=dy[turn(c[i])]*a[i];
		x=min(max(x,1),n);
		y=min(max(y,1),m);
		if(mp[x][y]=='X'){
			modify(i+1,1);
			modify(i+b[i]+1,-1);
		}
	}
	printf("%d %d",x,y);
}
int main(){
	scanf("%d %d %d %d",&n,&m,&q,&k);
	for(int i=1;i<=n;++i){
		scanf("%s",mp[i]+1);
	}
	for(int i=1;i<=q;++i){
		scanf("\n%c %d %d",&c[i],&a[i],&b[i]);
	}
	if(k==1){
		work();
		return 0;
	}
	int x=1,y=1;
	for(int i=1;i<=q;++i){
		x+=dx[turn(c[i])]*a[i];
		y+=dy[turn(c[i])]*a[i];
		x=min(max(x,1),n);
		y=min(max(y,1),m);
		if(mp[x][y]=='X'){
			for(int j=1;j<=b[i];++j){
				c[i+j*k]=change(c[i+j*k]);
			}
		}
	}
	printf("%d %d",x,y);
	return 0;
}
```
## Subtask 4&5
考虑到第 $i$ 个节点只可能被 $i-k,i-2\times k,i-3\times k\dots$ 更新到，也就是以 $k$ 为模数，$i$ 只可能更新到与其在模 $k$ 意义下同余的点，考虑开 $k$ 个树状数组，每一个维护 $x\times k+y=i$ 中的 $y$，$x$ 就是维护值的下标，时间复杂度 $\operatorname{O}(q\log q)$。
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#define MAXN 505
#define MAXM 200002
#define MAXK 22
using namespace std;
int n,m,q,k,a[MAXM],b[MAXM];
char mp[MAXN][MAXN],c[MAXM];
int tree[MAXK][MAXM<<1];
int dy[4]={0,0,-1,1};
int dx[4]={1,-1,0,0};
inline int turn(char c){
	if(c=='D'){
		return 0;
	}
	if(c=='U'){
		return 1;
	}
	if(c=='L'){
		return 2;
	}
	return 3;
}
inline char change(char c){
	if(c=='U'){
		return 'D';
	}
	if(c=='D'){
		return 'U';
	}
	if(c=='L'){
		return 'R';
	}
	return 'L';
}
inline int lowbit(int x){
	return x&-x;
}
inline void modify(int ex,int p,int add){
	for(int i=p;i<MAXM;i+=lowbit(i)){
		tree[ex][i]+=add;
	}
}
inline int query(int ex,int p){
	int ans=0;
	for(int i=p;i;i-=lowbit(i)){
		ans+=tree[ex][i];
	}
	return ans;
}
int main(){
	scanf("%d %d %d %d",&n,&m,&q,&k);
	for(int i=1;i<=n;++i){
		scanf("%s",mp[i]+1);
	}
	for(int i=1;i<=q;++i){
		scanf("\n%c %d %d",&c[i],&a[i],&b[i]);
	}
	int x=1,y=1;
	for(int i=1;i<=q;++i){
	    int now=i/k;
		if(query(i%k,now)%2==1){
			c[i]=change(c[i]);
		}
		x+=dx[turn(c[i])]*a[i];
		y+=dy[turn(c[i])]*a[i];
		x=min(max(x,1),n);
		y=min(max(y,1),m);
		if(mp[x][y]=='X'){
			modify(i%k,now+1,1);
			modify(i%k,now+b[i]+1,-1);
		}
	}
	printf("%d %d",x,y);
	return 0;
}
```

---

## 作者：lkjzyd20 (赞：1)

### 思路
根据题目模拟，我们可以发现，每一次的修改其实是一次异或操作。

比如我们可以看下这四个操作：
* 若 $c$ 为 `U`，则替换为 `D`。
* 若 $c$ 为 `D`，则替换为 `U`。
* 若 $c$ 为 `R`，则替换为 `L`。
* 若 $c$ 为 `L`，则替换为 `R`。

显然易见，如果我们把 $c$ 从 `U`，替换为 `D`，又从 `D`，替换为 `U`，这就是一次异或操作。

然后我们可以写出这样的一份代码：
```cpp
rep(i, 1, q) {
    char dir = cmds[i];
    if(flip[i]) dir = flipDir(dir); // 单点修改
    move(dir, a[i]);
    if(grid[x][y] == 'X')
        rep(j, 1, b[i]) 
        {
            if(i + j * k <= q) flip[i + j * k] ^= 1; // 区间修改
            else break;
        }
}
printf("%d %d\n", x, y);

```
但我们看时间复杂度为 $O(\cfrac{q^2}{k})$，大概是 $1\times10^{9}$，显然这样我们不能满意。

继续观察，我们可以发现下面这个区间修改是可以优化的。
```cpp
rep(j, 1, b[i]) 
{
    if(i + j * k <= q) flip[i + j * k] ^= 1; // 区间修改
    else break;
}
```
我们发现每一次的修改对与 $i$ 这个点的前面无影响，我们可以通过取模操作来维护，但是我们发现这个点的修改最多只能到达 $i+b_i\times k$，如果超出，就无法修改。

我们可以使用类似差分的写法来进行维护 ，我们新开一个数组，在第 $i+(b_i+1)\times k$ 进行异或操作，后续遍历时，如果这个点之前被处理过，那么就进行异或。

**注意：一定要先异或再处理。~~（老子就因为这个赛时没过）~~**

### 代码如下

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
using namespace std;

const int N = 510, Q = 200010;
int n, m, q, k;
char grid[N][N];
char cmds[Q];
int a[Q], b[Q];
int flip[Q];
int x = 1, y = 1;
void move(char &dir, int &dist) 
{
    if(dir == 'U') 
    {
        dist = min(dist, x - 1);
        x -= dist;
    } 
    if(dir == 'D') 
    {
        dist = min(dist, n - x);
        x += dist;
    } 
    if(dir == 'L') 
    {
        dist = min(dist, y - 1);
        y -= dist;
    } 
    if(dir == 'R') 
    {
        dist = min(dist, m - y);
        y += dist;
    }
}

char flipDir(char c) 
{
    if(c == 'U') return 'D';
    if(c == 'D') return 'U';
    if(c == 'L') return 'R';
    return 'L';
}
int xx[Q];
int main() 
{
    scanf("%d%d%d%d", &n, &m, &q, &k);
    rep(i, 1, n) scanf("%s", grid[i] + 1);
    rep(i, 1, q) scanf(" %c%d%d", &cmds[i], &a[i], &b[i]);
    rep(i, 1, q) 
    {
        char dir = cmds[i];
        if(xx[i]) flip[i % k + 1] ^= 1;
        if(flip[i % k + 1]) 
            dir = flipDir(dir);
        move(dir, a[i]);
        if(grid[x][y] == 'X')
        {
            flip[i % k + 1] ^= 1;
            if(i + b[i] * k + k <= q) xx[i + b[i] * k + k] ^= 1;
        }
    }
    printf("%d %d\n", x, y);
}
```

---

## 作者：Justin_ding (赞：0)

[传送门](https://www.luogu.com.cn/problem/P11078)

一道简单的题，从暴力轻轻推敲就能搞定。

**Subtask#1&2**

数据范围不大，暴力解决，按照题目大模拟即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,q,k,a[200010],b[200010],c[200010],dx[4]={1,0,-1,0},dy[4]={0,1,0,-1},x,y,sum[200010],r[200010];
char ma[505][505],d;
int main(){
	x=y=1;//初始化位置
	cin>>n>>m>>q>>k;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>ma[i][j];
	for(int i=1;i<=q;i++){
		cin>>d>>a[i]>>b[i];
		if(d=='D')c[i]=0;//用int存储，移动更方便
		else if(d=='R')c[i]=1;
		else if(d=='U')c[i]=2;
		else c[i]=3;
	}
	for(int i=1;i<=q;i++){
		x+=dx[c[i]]*a[i],y+=dy[c[i]]*a[i];
		if(x<1)x=1;
		if(x>n)x=n;
		if(y<1)y=1;
		if(y>m)y=m;
		if(ma[x][y]=='X')for(int j=1;j<=b[i]&&i+j*k<=q;j++)c[i+j*k]=(c[i+j*k]+2)%4;//用int记录C数组使修改更方便
	}
	cout<<x<<" "<<y;
 	return 0;
}
``````
**Subtask#3&4&5**

从 $i+k$ 到 $i+b_i \times k$ 进行更改，可不可以用 $O(1)$ 的差分呢？答案当然是能的。不过我们在记录时就要把差分数组前缀和一并求出来。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,q,k,a[200010],b[200010],c[200010],dx[4]={1,0,-1,0},dy[4]={0,1,0,-1},x,y,sum[200010],r[200010];
char ma[505][505],d;
int main(){
	x=y=1;
	cin>>n>>m>>q>>k;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>ma[i][j];
	for(int i=1;i<=q;i++){
		cin>>d>>a[i]>>b[i];
		if(d=='D')c[i]=0;
		else if(d=='R')c[i]=1;
		else if(d=='U')c[i]=2;
		else c[i]=3;
	}
	for(int i=1;i<=k&&i<=q;i++){//若在此用前缀和会RE
		x+=dx[c[i]]*a[i],y+=dy[c[i]]*a[i];
		if(x<1)x=1;
		if(x>n)x=n;
		if(y<1)y=1;
		if(y>m)y=m;
		if(ma[x][y]=='X'){//差分
			sum[i]+=2;
			sum[min(i+k*b[i],((q-i)/k)*k+i)/*防止越界*/]-=2;
		}
	}
	for(int i=k+1;i<=q;i++){
		r[i]=((r[i-k]+sum[i-k])%4+4)%4;//差分的前缀和
		c[i]=(c[i]+r[i])%4;//求出这一次该走哪个方向
		x+=dx[c[i]]*a[i],y+=dy[c[i]]*a[i];
		if(x<1)x=1;
		if(x>n)x=n;
		if(y<1)y=1;
		if(y>m)y=m;
		if(ma[x][y]=='X'){//差分
			sum[i]+=2;
			sum[min(i+k*b[i],((q-i)/k)*k+i)/*防止越界*/]-=2;
		}
	}
	cout<<x<<" "<<y;
 	return 0;
}
``````

---

## 作者：KANO07 (赞：0)

## 前言

记录一个赛时略微有点麻烦的写法，但配上平板电视码量还是挺小的。

## 思路

本题的难点主要是反转操作。朴素的想法是按照题目要求模拟，把要反转的位置依次反转。

但经过观察，发现 $k$ 是一个定值。所以我们可以按模 $k$ 来划分操作。到这之后，其他题解基本选择使用线段树来进行区间操作。但赛时我没注意到  $k$ 的范围，以为 $10^5$ 左右，想着写静态线段树内存会爆。

于是我选择了查询位置的写法，假设目前操作的是从 $a$ 开始的接下来 $b$ 个点。因为操作的一定是接下来的范围，所以可以统一把起点 $ a $ 移动到 $a\ mod\ k$ 处，再对 $b$ 修改一下。查询的时候只需知道有多少个操作区间覆盖了当前位置，可以用平衡树维护。

贴出代码。

```cpp
using ll = long long;
using pll = pair<ll, ll>;
ll dir[4][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
char g[505][505];
const ll N = 2e5 + 5;
map<char, ll> mp = {{'U', 0}, {'D', 1}, {'L', 2}, {'R', 3}};
vector<tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update>> start;
void solve() {
    ll n, m, q, k;
    cin >> n >> m >> q >> k;
    start.resize(k);
    for (ll i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> g[i][j];
    ll x = 1, y = 1;
    for (ll i = 1; i <= q; i++) {
        char tmp;
        ll a, b;
        cin >> tmp >> a >> b;
        ll opt = mp[tmp];
        ll dif = (i - i % k + k - 1) / k;   //需要几次k才能覆盖到这个点
        ll st = i % k;                      //起点
        ll index = start[st].size() - start[st].order_of_key({dif, 0});   //有几个覆盖过当前节点
        if (index % 2) opt ^= 1;
        x += dir[opt][0] * a, y += dir[opt][1] * a;
        x = min(x, n), y = min(y, m), x = max(1ll, x), y = max(1ll, y);
        if (g[x - 1][y - 1] == '.' || b == 0) continue;
        start[i % k].insert({b + (i - i % k) / k, i});
    }
    cout << x << " " << y << endl;
}
```

---

## 作者：Priestess_SLG (赞：0)

考虑简单线段树，维护当前区间的坐标以及之后每一次询问方向被翻转的次数。每一次更新点的坐标之后，若当前点在迷雾中则将其所对应的影响点在线段树上覆盖次数自增 $1$。具体因为区间不连续但是区间之间的差值相同考虑将点重新映射。总的时间复杂度为 $O(n+q\log q)$，可以通过。

```cpp
// #pragma GCC optimize(3)
#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define int long long
#define F(i,x,y) for(int i=x;i<=y;++i)
#define G(i,x,y) for(int i=x;i>=y;--i)
#define FD(i,x,y) for(int i=x;i*i<=y;++i)
#define GD(i,x,y) for(int i=x;i*i>=y;--i)
#define adde(x,y) z[x].eb(y);
#define Adde(x,y) z[x].eb(y),z[y].eb(x);
#define addew(x,y,w) z[x].eb(y,w)
#define Addew(x,y,w) z[x].eb(y,w),z[y].eb(x,w)
#define FIMX(X) memset(X,0x3f,sizeof X)
#define FIMI(X) memset(X,-0x3f,sizeof X)
#define FI0(X) memset(X,0,sizeof X)
#define FIN(X) memset(X,-1,sizeof X)
#define rng(X) X.begin(),X.end()
#define PII pair<int,int>
#define PDD pair<double,double>
#define PIII tuple<int,int,int>
#define VI vector<int>
#define VII vector<PII>
#define VID vector<pair<int,double>>
#define VDD vector<PDD>
using namespace std;
const int N=1100100,mod=998244353;
const int dx[]={0,0,1,-1},dy[]={-1,1,0,0};
const char op[]={'U','D','R','L'};
char s[555][555];
const int block=140;
int fuck[N];
int a[N],b[N];
struct qwq{
    int l,r,sum,tag;
    void init(int p){
        l=r=p;
        sum=tag=0;
    }
    void yhb(int v){
        sum+=(r-l+1)*v;
        tag+=v;
    }
}z[N<<2];
qwq operator+(const qwq&l,const qwq&r){
    return {l.l,r.r,l.sum+r.sum,0ll};
}
void build(int l,int r,int rt){
    if(l==r)
        return z[rt].init(l);
    int mid=l+r>>1;
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    z[rt]=z[rt<<1]+z[rt<<1|1];
}
void pushyhb(int rt){
    if(z[rt].tag){
        z[rt<<1].yhb(z[rt].tag);
        z[rt<<1|1].yhb(z[rt].tag);
        z[rt].tag=0;
    }
}
void modify(int l,int r,int rt,int ll,int rr,int v){
    if(ll<=l&&r<=rr)
        return z[rt].yhb(v);
    int mid=l+r>>1;
    pushyhb(rt);
    if(ll<=mid)
        modify(l,mid,rt<<1,ll,rr,v);
    if(mid<rr)
        modify(mid+1,r,rt<<1|1,ll,rr,v);
    z[rt]=z[rt<<1]+z[rt<<1|1];
}
int query(int l,int r,int rt,int p){
    if(l==r)return z[rt].sum;
    int mid=l+r>>1;pushyhb(rt);
    if(p<=mid)return query(l,mid,rt<<1,p);
    return query(mid+1,r,rt<<1|1,p);
}
void solve(unsigned __testid=1){
    int n,m,q,k;cin>>n>>m>>q>>k;
    F(i,1,n)F(j,1,m)cin>>s[i][j];
    int x=1,y=1;
    if(k>=block){
        F(i,1,q){
            char c;int a,b;cin>>c>>a>>b;
            if(fuck[i]){
                if(c=='U')c='D';
                else if(c=='D')c='U';
                else if(c=='L')c='R';
                else c='L';
            }
            if(c=='U')x-=a;
            else if(c=='D')x+=a;
            else if(c=='L')y-=a;
            else y+=a;
            if(x<1)x=1;
            if(y<1)y=1;
            if(x>n)x=n;
            if(y>m)y=m;
            if(s[x][y]=='X'){
                F(j,1,b)
                    fuck[i+j*k]^=1;
            }
        }
        cout<<x<<' '<<y<<'\n';
    }else{
        int idx=0;
        F(p,1,k)
            F(i,0,1145141919810){
                int now=i*k+p;
                if(now>q)break;
                ++idx;
                a[now]=idx;
                b[idx]=now;
            }
        build(1,q,1);
        //a[i]:第i个元素所映射的位置
        //b[i]:第i个位置所映射的元素
        F(i,1,q){
            char c;int a,b;cin>>c>>a>>b;
            int pos=query(1,q,1,::a[i]);
            if(pos&1){
                if(c=='U')c='D';
                else if(c=='D')c='U';
                else if(c=='L')c='R';
                else c='L';
            }
            if(c=='U')x-=a;
            else if(c=='D')x+=a;
            else if(c=='L')y-=a;
            else y+=a;
            if(x<1)x=1;
            if(y<1)y=1;
            if(x>n)x=n;
            if(y>m)y=m;
            if(s[x][y]=='X'){
                int bg=::a[i]+1;
                if(b)modify(1,q,1,bg,bg+b-1,1);
            }
        }
        cout<<x<<' '<<y<<'\n';
    }
}
int32_t main(){
    // ios_base::sync_with_stdio(0) ;
    // cin.tie(nullptr);
    int T;
    T=1;
    // cin>>T;
    F(_,1,T)
        solve(_);
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# P11078 解题报告

## 前言

感觉出的很不错，要说不足就是有点典了

## 思路分析

首先题意有点复杂，我们明确一下问题本质。

考虑维护当前人所在的位置是平凡的，瓶颈在于维护每一次操作是否被反转。所以，问题本质是一个区间取反，单点查询的数据结构题。

观察题目数据，$k$ 很小，同时注意到区间推平修改的是下标模 $k$ 同余的一段区间。所以容易想到将下标模 $k$ 同余的点合并处理。

具体地，考虑维护 $k$ 棵动态开点线段树，在第 $i$ 棵线段树的下标为 $j$ 的叶子节点维护的是原序列下标为 $j \cdot k + i \bmod k$ 的值。

然后就做完了，注意动态开点时下传标记时可能要新建儿子。

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,q,k,a,b,nowx,nowy;
char op,mp[505][505];
int val[64000005],tag[64000005],ls[64000005],rs[64000005],rt[25],dcnt;
void pushdown(int x){
	if(!ls[x]) ls[x]=++dcnt;
	if(!rs[x]) rs[x]=++dcnt;
	if(!tag[x]) return;
	val[ls[x]]^=1;
	val[rs[x]]^=1;
	tag[ls[x]]^=1;
	tag[rs[x]]^=1; 
	tag[x]=0;
}
void modify(int l,int r,int ql,int qr,int &x){
	if(!x) x=++dcnt;
	if(ql<=l && r<=qr){
		val[x]^=1;
		tag[x]^=1;
		return;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if(ql<=mid) modify(l,mid,ql,qr,ls[x]);
	if(qr>=mid+1) modify(mid+1,r,ql,qr,rs[x]);
}
int query(int l,int r,int pos,int x){
	if(!x) return 0;
	if(l==r) return val[x];
	pushdown(x);
	int mid=(l+r)>>1;
	if(pos<=mid) return query(l,mid,pos,ls[x]);
	else return query(mid+1,r,pos,rs[x]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>q>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mp[i][j];
		} 
	}
	nowx=1,nowy=1;
	for(int i=1;i<=q;i++){
		cin>>op>>a>>b;
		if(!query(0,q/k+1,i/k,rt[i%k])){
			if(op=='U') nowx=max(1,nowx-a);
			if(op=='D') nowx=min(n,nowx+a);
			if(op=='L') nowy=max(1,nowy-a);
			if(op=='R') nowy=min(m,nowy+a);
		}else{
			if(op=='D') nowx=max(1,nowx-a);
			if(op=='U') nowx=min(n,nowx+a);
			if(op=='R') nowy=max(1,nowy-a);
			if(op=='L') nowy=min(m,nowy+a);
		}
		if(mp[nowx][nowy]=='X' && b) modify(0,q/k+1,i/k+1,i/k+b,rt[i%k]);
	}
	cout<<nowx<<' '<<nowy;
	return 0;
}
```

## 后记

题解是比赛打一半不会 T4 的时候写的，当时以为 T3 会有区分度了。

现在看怎么一车人切了。

---

## 作者：Your_Name (赞：0)

## 题意
给一个地图，一开始在 $(1,1)$，有 $q$ 步行走，$c_1...c_q$，每次都向特定方向都 $a_i$ 步，并且如果当前走完所在位置是迷雾中的话，他就会把 $c_{i+k},c_{i+2\times k},\cdots,c_{i+b_i \times k}$ 进行一次**修改**（左变右，右变左，上变下，下变上）。

求最后在哪。
## 题解
读完题发现有几个关键信息：
* 每次修改都只会被他前面的点反转，也就是说改了 $2$ 的倍数次就相当于没改。
* 不是区间修改，而是跳跃修改，也就是说用不了常用的树状数组或者线段树。
* k 很小。

一开始我先打了个暴力看看多少分，代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, q, k;
const int N = 2e5 + 10;
char ma[510][510];
struct node{
    int a, b, f;
}zou[N];//每一步
int fx[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void fan(int x){//反转
    if(zou[x].f == 0)zou[x].f = 1;
    else if(zou[x].f == 1)zou[x].f = 0;
    else if(zou[x].f == 2)zou[x].f = 3;
    else if(zou[x].f == 3)zou[x].f = 2;
}
int main(){
    cin >> n >> m >> q >> k;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> ma[i][j];
        }
    }
    for(int i = 1; i <= q; i ++){
        char c;
        cin >> c >> zou[i].a >> zou[i].b;
        if(c == 'U')zou[i].f = 0;
        if(c == 'D')zou[i].f = 1;
        if(c == 'L')zou[i].f = 2;
        if(c == 'R')zou[i].f = 3;
    }
    int nx = 1, ny = 1;
    for(int i = 1; i <= q; i ++){
        int kx = fx[zou[i].f][0] * zou[i].a + nx;
        int ky = fx[zou[i].f][1] * zou[i].a + ny;
        if(kx < 1)kx = 1;
        if(ky < 1)ky = 1;
        if(kx > n)kx = n;
        if(ky > m)ky = m;
        if(ma[kx][ky] == 'X'){
            for(int j = i + k; j <= i + zou[i].b * k; j += k){
                fan(j);
            }
        }
        nx = kx, ny = ky;
    }
    cout << nx <<' ' << ny;
    return 0;
}
```
不出所料，20。

看看哪里可以优化。

首先，枚举每一步是肯定不能优化的，因为要知道当前有没有走出去，走到了哪里。每次反转操作又是 $O(1)$，那么能优化的只剩下修改操作了。

注意到，对于当前在第 $i$ 步，每次修改都跳 $k$ 步，那么是不是说只要没有这个右边界限制，每个 $j$ 满足 $j \equiv i(\bmod k)$的所有步都要修改。

知道了这个再考虑右边界。

是不是只要在遍历到 $i$ 时看之前同余于 $i$ 的所有操作中的右边界大于等于 $i$ 的有多少个就可以知道当前这一步被反转了多少次。

至于用什么存每个模 $k$ 值的右边界，可以想到右边界小的先没用，剩下的都是有用的，所以开个优先队列就行。

每次 pop 到队头大于等于 $i$ 那么整个 size 就是当前点被修改的次数。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, q, k;
const int N = 2e5 + 10;
char ma[510][510];
int cnt[21];
priority_queue<int, vector<int>, greater<int> > qu[21];//每个模数的操作
struct node{
    int a, b, f;
}zou[N];
int fx[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
void fan(int x){
    if(zou[x].f == 0)zou[x].f = 1;
    else if(zou[x].f == 1)zou[x].f = 0;
    else if(zou[x].f == 2)zou[x].f = 3;
    else if(zou[x].f == 3)zou[x].f = 2;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> q >> k;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> ma[i][j];
        }
    }
    for(int i = 1; i <= q; i ++){
        char c;
        cin >> c >> zou[i].a >> zou[i].b;
        if(c == 'U')zou[i].f = 0;
        if(c == 'D')zou[i].f = 1;
        if(c == 'L')zou[i].f = 2;
        if(c == 'R')zou[i].f = 3;
    }
    int nx = 1, ny = 1;
    for(int i = 1; i <= q; i ++){
        int now = i % k;
        while(!qu[now].empty() && qu[now].top() < i){
            qu[now].pop();
        }//pop 到队头大于等于i，size 就是修改次数
        if(qu[now].size() % 2 == 1)fan(i);//反转奇数次才有效
        int kx = fx[zou[i].f][0] * zou[i].a + nx;
        int ky = fx[zou[i].f][1] * zou[i].a + ny;
        if(kx < 1)kx = 1;
        if(ky < 1)ky = 1;
        if(kx > n)kx = n;
        if(ky > m)ky = m;
        if(ma[kx][ky] == 'X'){
            int ed = i + zou[i].b * k;
            qu[i % k].push(ed);//加一个操作
        }
        nx = kx, ny = ky;
    }
    cout << nx <<' ' << ny;
    return 0;
}
```
 _完结撒花_

---

## 作者：JYX0924 (赞：0)

如果 $i$ 可以对 $j$ 产生影响，显然说明 $i$ 和 $j$ 模 $k$ 同余。那么对于每一次修改，可以用线段树维护。由于 $k$ 的范围极小，给线段树加上一维表示模 $k$ 的余数就可以了。

下面是我的 AC 代码。


```c
#include<bits/stdc++.h>
#define ll long long 
#define int long long 
#define maxn 1005 
#define mid ((l+r)>>1)
#define ls (now<<1)
#define rs (now<<1|1)
using namespace std;
ll n,m,q,k,a[1000005],b[1000005],sum[25][1000005<<2],lazy[25][1000005<<2];
char s[maxn][maxn],str[1000005];
queue<ll> tt;
void push_up(ll now,ll x) {sum[x][now]=sum[x][ls]+sum[x][rs];}
void push_down(ll now,ll l,ll r,ll pos)
{
	sum[pos][ls]+=(mid-l+1)*lazy[pos][now]; sum[pos][rs]+=(r-mid)*lazy[pos][now];
	lazy[pos][ls]+=lazy[pos][now]; lazy[pos][rs]+=lazy[pos][now];
	lazy[pos][now]=0;
}
void modify(ll now,ll l,ll r,ll L,ll R,ll pos)
{
	if(l>=L&&r<=R) {sum[pos][now]+=(r-l+1); lazy[pos][now]++; return;}
	if(lazy[pos][now]) push_down(now,l,r,pos);
	if(mid>=L) modify(ls,l,mid,L,R,pos);
	if(R>=mid+1) modify(rs,mid+1,r,L,R,pos);
	push_up(now,pos);
}
ll query(ll now,ll l,ll r,ll pos,ll tt)
{
	if(l==r) return sum[tt][now];
	if(lazy[tt][now]) push_down(now,l,r,tt);
	if(mid>=pos) return query(ls,l,mid,pos,tt);
	return query(rs,mid+1,r,pos,tt);
}
void cal(int now)
{
	ll sum=query(1,1,1000000,(now/k+(now%k!=0)+1),now%k);
	if(sum%2==1)
	{
		if(str[now]=='D') {str[now]='U'; return;}
		if(str[now]=='U') {str[now]='D'; return;}
		if(str[now]=='L') {str[now]='R'; return;}
		if(str[now]=='R') {str[now]='L'; return;}
	}
}
signed main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>m>>q>>k; for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>s[i][j];
	for(int i=1;i<=q;i++) cin>>str[i]>>a[i]>>b[i];
	ll x=1,y=1,now=1;
	while(now<=q)
	{
		cal(now);
		if(str[now]=='U') x-=a[now];
		if(str[now]=='D') x+=a[now];
		if(str[now]=='R') y+=a[now];
		if(str[now]=='L') y-=a[now];
		if(x<=0) x=1;
		if(y<=0) y=1;
		if(x>n) x=n;
		if(y>m) y=m;
		if(s[x][y]=='X'&&b[now]>0) modify(1,1,1000000,now/k+(now%k!=0)+2,now/k+(now%k!=0)+b[now]+1,now%k);
		now++; 
	}
	cout<<x<<" "<<y;
	return 0;
}
```
谢谢大家！！！

---

