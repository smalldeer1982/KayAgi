# Maximal Binary Matrix

## 题目描述

You are given matrix with $ n $ rows and $ n $ columns filled with zeroes. You should put $ k $ ones in it in such a way that the resulting matrix is symmetrical with respect to the main diagonal (the diagonal that goes from the top left to the bottom right corner) and is lexicographically maximal.

One matrix is lexicographically greater than the other if the first different number in the first different row from the top in the first matrix is greater than the corresponding number in the second one.

If there exists no such matrix then output -1.

## 样例 #1

### 输入

```
2 1
```

### 输出

```
1 0 
0 0 
```

## 样例 #2

### 输入

```
3 2
```

### 输出

```
1 0 0 
0 1 0 
0 0 0 
```

## 样例 #3

### 输入

```
2 5
```

### 输出

```
-1
```

# 题解

## 作者：封禁用户 (赞：5)

### 前言

[cnblog](https://www.cnblogs.com/CM-0728/p/14225305.html)

模拟赛原题。。

好好一道送分被我硬打成爆蛋。。

### $\sf{Solution}$

看了一波数据范围，感觉能 dfs 骗分。

骗成正解了。

大概就是将这个 $n\times n$ 的矩阵全扫一遍，可以选择填 $1$ 或不填。回溯一下就行啦。


- 位置问题

假设现在的坐标为 $(x,y)$ 

若 $x>n$ ，则结束 dfs ，比较一下矩阵字典序，较为简单不题。

若 $y>n$ ，则 $x→x+1,y=1$ ，即跳到下一行第一位。

- 对称处理       （定义 $a_{x,y}$ 为当前搜到的地方）


  - 在对角线上
  
  只填这个地方。
  
  - 其他
  
  填 $a_{x,y}$ 和 $a_{y,x}$ 。

填 $1$ 的话就要相应处理 $k$ 。

- 特判

**$k=0$ ，输出全 $0$ 矩阵。**



### $\sf{Code}$

写得有点麻烦。。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,k;
bool flag,m[105][105],q[105][105];
inline bool p()
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(m[i][j]<q[i][j])
				return flag=true;
	return false;
}
inline void dfs(int x,int y,int d)
{
	if(y>n)
		++x,y=1;
	if(d==0)
	{
		if(p())
			for(int i=1;i<=n;++i)
				for(int j=1;j<=n;++j)
					m[i][j]=q[i][j];
		return ;
	}
	if(x>n)
		return ;
	if(x==y&&d>=1&&!q[x][y])
			q[x][y]=1,dfs(x,y+1,d-1),q[x][y]=0;
	else if(x!=y&&d>=2&&(!q[x][y]||!q[y][x])) 
	{
		if(q[x][y]==0&&q[y][x]==0)
			q[x][y]=1,q[y][x]=1,dfs(x,y+1,d-2),q[x][y]=0,q[y][x]=0;
		else if(q[x][y]==1&&q[y][x]==0)
			q[y][x]=1,dfs(x,y+1,d-1),q[y][x]=0;
		else if(q[x][y]==0&&q[y][x]==1)
			q[x][y]=1,dfs(x,y+1,d-1),q[x][y]=0;
	}
	else dfs(x,y+1,d);
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>k;
	if(k==0)
	{
		for(int i=1;i<=n;++i,cout<<"\n")
			for(int j=1;j<=n;++j)
				cout<<"0 ";
		return 0;
	}
	if(k>n*n)
	{
		cout<<-1;
		return 0;
	}
	q[1][1]=1;
	dfs(1,2,k-1);
	if(flag)
		for(int i=1;i<=n;++i,cout<<"\n")
			for(int j=1;j<=n;++j)
				cout<<m[i][j]<<" ";
	else cout<<"-1";
	return 0;
}
```

---

## 作者：frankchenfu (赞：3)

这道题目贪心即可。首先我们考虑如何贪心。

------------


由于矩阵是字典序越小越优，所以我们要尽量填满前几行。对应的，由于填上了前几行，我们就要填上前几列。接下来，我们考虑当剩下的$1$不足以填满整行时（$rest$表示剩余的可填充的$1$的数量）应该怎么办。假设对于以下矩阵，我们还可以填充$4$个$1$（$rest=4$）。

$$\begin{bmatrix} 1&1&1&1\\1&0&0&0\\1&0&0&0\\1&0&0&0\end{bmatrix}\quad(rest=4)$$

这样，我们一定需要先填充$0$的部分的左上角，以确保字典序最小。就像这样：

$$\begin{bmatrix} 1&1&1&1\\1&1&0&0\\1&0&0&0\\1&0&0&0\end{bmatrix}\quad(rest=3)$$

然后我们再考虑，接下来的$3$个$1$，我们为了确保对称性，事实上只能在同一行放一个（对称到列再放一个）。就是这样：
$$\begin{bmatrix} 1&1&1&1\\1&1&1&0\\1&1&0&0\\1&0&0&0\end{bmatrix}\quad(rest=1)$$

这个时候，我们发现$rest=1$。为了对称，我们只好把它放在对角线上。于是，最终的矩阵就被我们排好了。也就是说，如果填充不满，是奇数就直接填充本行（本列），否则还有在下一行填充。

$$\begin{bmatrix} 1&1&1&1\\1&1&1&0\\1&1&1&0\\1&0&0&0\end{bmatrix}\quad(rest=0)$$

再如当$rest=5$的时候，因为是奇数，没有不对称的问题，不需要把$1$强制放到对角线上，所以最终矩阵如下：

$$\begin{bmatrix} 1&1&1&1\\1&1&1&1\\1&1&0&0\\1&1&0&0\end{bmatrix}$$

------------


根据上面这两个例子，我们可以看出一个最佳的排列方法：

设递归函数$f(p,rest)$用于填充矩阵，其中$p$为右下方没有填充的全$0$矩阵的宽度，$rest$含义同上。
1. 当$rest> 2p-1$时，直接填满当前行，递归调用$f(p-1,rest-2p+1)$.
2. 当$rest\le 2p-1$时，尝试尽可能在对称的情况下填充，由于有奇偶性，调用$f(p-1,k+1\!\mod 2)$。

注意边界条件有$2$个：
* 当$rest=1$的时候，需要标记一个位置之后再直接返回。
* 当$rest=0$的时候，直接返回。

注意`-1`的情况只有当需要填充的$k> n^{2}$的时候才会出现，不会由于对称而产生其他的`-1`情况。

------------

代码如下。为了方便填充，代码中的递归函数还有一个$pos$表示全$0$矩阵左上角所在的行。
```cpp
#include<cstdio>
#include<cstring>
const int MAXN=110;
int a[MAXN][MAXN];

void solve(int n,int pos,int k)
{
	if(k==1)
	{
		a[pos][pos]=1;
		return;
	}
	if(k==0)
		return;
	if(k<=(n<<1)-1)
	{
		for(int i=pos;i<=pos+(k-1>>1);i++)
			a[pos][i]=a[i][pos]=1;
		solve(n-1,pos+1,(k&1)^1);
	}
	else
	{
		for(int i=pos;i<=pos+n-1;i++)
			a[pos][i]=a[i][pos]=1;
		solve(n-1,pos+1,k-(n<<1)+1);
	}
	return; 
}

int main()
{
	int n,k;scanf("%d%d",&n,&k);
	if(k>n*n)
	{
		puts("-1");
		return 0;
	}
	solve(n,1,k);
	for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)
			printf("%d ",a[i][j]);
	return 0;
}
```

---

## 作者：Base_ring_tree (赞：2)

# 奇怪思路+详细讲解

2024 1.13 写了这篇博客

2024.1.25 修改了个别错别字。

2024.1.30 修改了格式问题。

2024 2.2  请求通过审核...
## Solution
我们放 $1$ 的思路是这样的：

| 0 |  0|  0|  0|
| -----------: | -----------: | -----------: | -----------: |
| 0 |  0|  0| 0 |
| 0 | 0 | 0 | 0 |
| 0| 0 | 0 |  0|

这是最初的状态，因为我们要求字典序最大的序列。

所以我们可以得到第一个重要思路（~~的线索~~）,那就是：在一排中从前到后能放多少算多少，否则最大字典序就不是这样。

但是，我们也不能这样放：

| 1 |1  |1  |1  |
| -----------: | -----------: | -----------: | -----------: |
| 1 | 1 |1  |1  |
| 0 |0  |0  |0  |
| 0 | 0 | 0 | 0 |

因为我们还有一个信息就是要从左上到右下对称，所以这样是不对滴~

那我们该如何同时满足两个条件呢？

这样！

| 1 |1  |1  |1  |
| -----------: | -----------: | -----------: | -----------: |
|1  |  0| 0 | 0 |
| 1 | 0 | 0 | 0 |
|  1| 0 | 0 | 0 |


这看起来似乎和样例有些矛盾（样例登场）。

```
1 0 0 
0 1 0 
0 0 0 
```

他明明是斜着放的啊，不也满足了吗？其实这并不矛盾，因为他压根不能摆成上述阵型。难不成他能这样？


| 1 |1  |  0|
| -----------: | -----------: | -----------: |
| 0 |0  |  0|
| 0 | 0| 0 |


不对称！

还是说能这样？


| 1 |0 |  0|
| -----------: | -----------: | -----------: |
| 1 |0  |  0|
| 0 | 0| 0 |

也不对称！

所以我们又推出当你还剩下一个 $1$ 时，就得把它放在对角线上，否则就按一个旋转了 $90\degree$ 的 $L$ 来放。每次放都将剩余可摆放 $1$ 的个数减一。

最后一步，**特判**！
 # **特判**
 
我们需要判断他是否输出 $-1$。

这个是比较好搞的，只要判断一下这些 $1$ 能不能放进来就行了。

完结散花！

散花啥呀散花，恭喜听取 WA 声一片。

因为还需要判断你放 $1$ 的个数为 $0$ 的情况，要不然他就会什么都不输出，所以要提前判断提前输出，本蒟蒻就是被这样卡疯的。

好了好了，贴上代码！

# 代码
```
#include<bits/stdc++.h>
#include<ctrl+c?>
using namespace std;
#define int ctrl+c?
int n,k;
bool c[105][105];
int l,r;
int sum;
signed noctrl+c()
{
	 cin>>n>>k;
	 if(k==0)
	 {
	 	for(int i=1;i<=n;i++)
	 	{
	 		for(int j=1;j<=n;j++)
	 		{
	 			cout<<"0 ";//特判
			 }
			 cout<<endl;
		 }
		 return 0;
	 }
	 if(k>n*n)
	 {
	 	cout<<-1;//不合法
	 	return 0;
	 }
	 sum=k;
 	 for(int i=1;i<=n;i++)
	 {
	 	for(int j=i;j<=n;j++)
	 	{
	 		if(i==j)
	 		{
	 			c[i][j]=1;
	 			sum--;//在角上没法两边对称
			 }
			 else{
			 	c[i][j]=1;
			 	c[j][i]=1;
			 	sum-=2;//两边对称
			 }
			 if(sum==1)
			 {
			 	i++;
			 	j=i;
			 	c[i][j]=1;
			 	for(int k=1;k<=n;k++)
			 	{
			 		for(int l=1;l<=n;l++)
			 		{
			 			cout<<c[l][k]<<" ";
					 }
					 cout<<endl;
				 }
				 return 0;
			 }//还剩一个放在对角线上
			 if(sum==0)
			 {
			 	for(int k=1;k<=n;k++)
			 	{
			 		for(int l=1;l<=n;l++)
			 		{
			 			cout<<c[l][k]<<" ";
					 }
					 cout<<endl;
				 }
				 return 0;
			 }//没有剩直接输出
		 }
	 }
	
	 
	return 0;
}
```
由于本人脑回路过于清奇，如果您不解，可以说，我会在讨论区里“狡辩”。


~~苍天啊，大地啊，让管理大大审核通过吧~~


---

## 作者：wflhx2011 (赞：2)

# Solution

这道题因为要求字典序最大，所以我们从 $(1,1)$ 开始依次遍历涂色。

又因为要求按照左上向右下的对称轴对称，所以：

如果 $i=j$，那么就只涂 $1$ 个格子。

反之，就需要涂两个格子，即 $a[i][j]$ 和 $a[j][i]$。

当然，最后可能会剩下一个，我们此时就只能涂 $a[i][i]$。

无解的情况也不难想到：

当 $k$ 比 $n \times n$ 还大时，无解。

注意：一开始要把数组赋值为 $0$，否则第 $4$ 个点 $n=1,k=0$ 就没有输出。

最后，代码非常简洁：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105],f;
int main()
{
	long long n,k;
	cin>>n>>k;
	if(n*n<k)
	{
		cout<<-1;
		return 0;
	}
	if(k==0)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				cout<<0<<" ";
			cout<<endl;
		}
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==0)
				if(i==j)
					a[i][j]=1,k--;
				else
					if(k==1)
						if(a[i][i]==1)
							a[i+1][i+1]=1,k--;
						else
							a[i][i]=1,k--;
					else
						a[i][j]=a[j][i]=1,k-=2;
				if(k==0)
				{
					f=1;
					break;
				}
		}
		if(f==1)
			break;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cout<<a[i][j]<<" ";
		cout<<endl;
	}	
	return 0;
}
```

---

## 作者：syf2008 (赞：2)

~~简单一眼题~~


给你一个n行n列全是0的矩阵。你需要把k个1放到矩阵中，

保证这个矩阵按照左上向右下的对称轴对称，

## 并且保证这个矩阵的字典序最大。


我画个图

![](https://cdn.luogu.com.cn/upload/image_hosting/v5c5pr0j.png)

按照行枚举

不是对角线   这个点和对称点上标为1，k-2

当枚举到对角线时  在对角线上标为1，k-1

特殊情况
1的个数>矩阵

输出-1

上代码
```
#include <bits/stdc++.h>
using namespace std;
int ff,n,k,s,a[105][105];
int main()
{
	cin>>n>>k;
	if(k>n*n)
	{
	cout<<-1<<endl;
	return 0;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
	if(k==0)//没有1了，弹出
	goto ss;
	if(a[i][j])//已被标记
	continue;
	if(i==j)//对角线
	{
	k--;
	a[i][j]=1;
	}
else{//非对角线
	if(k<2)
	continue;
	a[i][j]=a[j][i]=1;//双标
	k-=2;
	}
	}
	ss:;
	for(int i=1;i<=n;i++)//输出
	{
	for(int j=1;j<=n;j++)
	cout<<a[i][j]<<' ';
	cout<<endl;
	}
}
```

---

## 作者：_Lazy_zhr_ (赞：1)

如果 $k>n^2$，直接输出 `-1`。

否则直接遍历。设这个点位于第 $i$ 行第 $j$ 列，那么只遍历 $i \le j$ 的点。若 $i=j$，只放一个 $1$，否则放两个，记得把第 $j$ 行第 $i$ 列的点也放了。

最后，如果刚好放完，直接输出。否则放在第 $i+1$ 行第 $i+1$ 列的点再输出。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k;
char ans[105][105];
void init(){ for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ans[i][j]='0'; }
void write(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) cout<<ans[i][j]<<" ";
		cout<<"\n";
	}
}
void solve(){
	cin>>n>>k;
	init();
	if(k>n*n){
		cout<<"-1\n";
		return ;
	}
	if(!k){
		write();
		return ;
	}
	for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
		if(i==j) ans[i][j]='1',k--;
		else ans[i][j]=ans[j][i]='1',k-=2;
		if(k==0){
			write();
			return ;
		}
		else if(k<0){
			ans[i][j]=ans[j][i]='0';
			ans[i+1][i+1]='1';
			write();
			return ;
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Jim_Franklin (赞：1)

这是考试时候的题，当时只拿了 35 分。

写篇题解纪念一下。

#### 本题解只讲解贪心算法

以下正文：

因为要让字典序最大，所以很显然可以得到赋值顺序：

$(1,1)$ $(1,2)$ ··· $(1,n)$

$(2,2)$ $(2,3)$ ··· $(2,n)$

·
·
·

当 $i=j$ 时 
```cpp
a[i][j]=1,k--
```

否则 
```cpp
a[i][j]=a[j][i]=1,k-=2
```

但是这边我们还要考虑一个问题：

如果此时 $k=1$ 我们只能去做 $i=j$ 时的赋值。

如果做完一遍后 $k$ 仍有沉余，说明无法构造这个矩阵

Code ~~代码太丑，勿喷~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ri register
const int inf=0x3f3f3f;
inline int rd()
{
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int n,k;
int a[110][110];
void do_()
{
	for(int i=1;i<=n;i++)
		 for(int j=1;j<=n;j++){
		 	if(k==0)return ;
		 	if(a[i][j])continue;
		 	if(i==j)a[i][j]=1,k--;
		 	else if(k!=1)a[i][j]=a[j][i]=1,k-=2;
		 }
		 	
}
int main()
{
	n=rd();k=rd();
	if(k>n*n){
		cout<<-1;
		return 0;
	}
	do_();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)cout<<a[i][j]<<' ';
		puts("");
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

首先 $k > n^2$ 时肯定无解。

其次，肯定是从最上面一列一列填下来是最优的，但要保持对称，所以填充 $a_{i,j}$ 时也要填充 $a_{j,i}$。

但是如果只能再填一个了，又要保持对称性，所以应填在当前所有没有填的对角线方格上找一个字典序最大的。

然后就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 105;
int T,n,k;
int a[N][N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> n >> k;
	if (n * n < k){ // 特判
		cout << -1 << endl;
		return;
	}
	for (int i = 1 ; i <= n ; i++){
		for (int j = i ; j <= n ; j++){
			if (!k) break; // 如果不能填了，直接退出
			if (i == j){
				k--;
				a[i][j] = 1; // 当前方格是对角线
			}else{
				if (k == 1){ // 如果只能填一个
					if (j > i) a[i + 1][i + 1] = 1;
					else a[i][i] = 1; // 找字典序最大的
					k--;
					break;
				}
				k -= 2;
				a[i][j] = 1;
				a[j][i] = 1; // 填充
			}
		}
		if (!k) break;
	}
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= n ; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
}
signed main(){
	close();
	T = 1;
	//cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑字典序最大，那么就是说从第一行开始。

由于要对称，所以填了 $a_{i,j}$ 就要填 $a_{j,i}$，所以只有 $i=j$ 时会影奇偶性。

而当 $k$ 是奇数的时候，可以考虑先将 $(1,1)$ 填完，然后填第一行，然后就转换成了 $(n-1) \times (n-1)$ 的矩阵并且 $k$ 为偶数。

然后对于偶数就是每次填两个对角线，两行即可。

例如：

$n=4,k=11$。

$k$ 是奇数，先填第一行。
```
1111
1000
1000
1000
```
然后每两行填：
```
1111
1110
1110
1000
```

代码如下：
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k;
int a[110][110];

int main() {
	cin >> n >> k;
	if (k > n * n) {
		puts("-1");
	} else if (k == 0) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cout << 0 << ' ';
			}
			cout << endl;
		}
	} else {
		if (k & 1) {
			a[1][1] = 1;
			--k;
			for (int i = 2; i <= n; ++i) {
				if (k >= 2) {
					k -= 2;
					a[1][i] = a[i][1] = 1;
				}
			}

			int i = 2;
			while (i <= n) {
				if (!k) break;
				if (i + 1 <= n) {
					a[i][i] = a[i + 1][i + 1] = 1;
					k -= 2;
					for (int j = i + 1; j <= n; ++j) {
						if (k >= 2) {
							k -= 2;
							a[i][j] = a[j][i] = 1;
						}
					}
					for (int j = i + 2; j <= n; ++j) {
						if (k >= 2) {
							k -= 2;
							a[i + 1][j] = a[j][i + 1] = 1;
						}
					}
				} else {
					for (int j = 2; j <= n; ++j) {
						if (k >= 2) {
							k -= 2;
							a[i][j] = a[j][i] = 1;
						}
					}
					break;
				}
				i += 2;
			}
		} else {
			int i = 1;
			while (i <= n) {
				if (!k) break;
				if (i + 1 <= n) {
					a[i][i] = a[i + 1][i + 1] = 1;
					k -= 2;
					for (int j = i + 1; j <= n; ++j) {
						if (k >= 2) {
							k -= 2;
							a[i][j] = a[j][i] = 1;
						}
					}
					for (int j = i + 2; j <= n; ++j) {
						if (k >= 2) {
							k -= 2;
							a[i + 1][j] = a[j][i + 1] = 1;
						}
					}
				} else {
					for (int j = 2; j <= n; ++j) {
						if (k >= 2) {
							k -= 2;
							a[i][j] = a[j][i] = 1;
						}
					}
					break;
				}
				i += 2;
				// cout << k << ' ' << n << ' ' << n * 4 << ' ' << i << endl;
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) cout << a[i][j] << ' ';
			cout << endl;
		}
	}
	return 0;
}
```

---

## 作者：FJ_OIer (赞：0)

首先可以证明只要 $k \leq n^2$ 就一定有解。

如何构造最优解呢？我们先将矩阵划分成 $n$ 层：

![](https://cdn.luogu.com.cn/upload/image_hosting/mhsxe9bk.png)

每种颜色一层。

然后循环遍历这些层，若 $k$ 大于等于这一层的元素个数（第一层有 $2n-1$ 个，以此类推），那就将这一层的所有元素赋值为 $1$，并将 $k$ 减去这一层的元素个数。

但如果不大于，分两种情况讨论（以下用红点表示 $1$）：

1. $(k-1)\bmod2=0$，就按如下方式赋值：

![](https://cdn.luogu.com.cn/upload/image_hosting/omh6coj5.png)

2. $(k-1)\bmod2=1$，令 $k=k-1$，再按情况 $1$ 的方式赋值，最后将**下一层**的中间赋值为 $1$。

详见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k;
bool a[101][101];
int main(){
    cin>>n>>k;
    if (k>n*n){
        cout<<-1;
        return 0;
    }
    for (int i=n;i&&k;i--){//遍历层（i不代表层的编号）
        if (k>=i*2-1){
            k-=i*2-1;
            for (int j=n-i+1;j<=n;j++){
                a[j][n-i+1]=1;
            }
            for (int j=n-i+1;j<=n;j++){
                a[n-i+1][j]=1;
            }
            //将这一层全部赋值为1
        }else{
            for (int j=n-i+2;j<=n-i+1+(k-1)/2;j++){
                a[j][n-i+1]=1;
            }
            for (int j=n-i+2;j<=n-i+1+(k-1)/2;j++){
                a[n-i+1][j]=1;
            }
            //两边放1
            a[n-i+1][n-i+1]=1;
            //中间放1
            if ((k-1)%2){
                a[n-i+2][n-i+2]=1;//下一层的中间放1
            }
            break;
        }
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：灵光一闪 (赞：0)

我们教练告诉我们：循环是人做的事情，递归是神做的事情，那我把这题A了我是不是就是神了23333

好了，谈正事，首先这题嘛，既然要求对称的话，每一次添加1时想要对称的话只有两种方法：

one：
```
1000
0100
0000
0000
```
two：
```
0100
1000
0000
0000
```
然后就开始贪心：从左到右，从上到下，只要能放就放，比如这个：
```
样例2：3 2//^为循环到哪里了
0000
^//可以加就加
0000

0000

0000
然后：//下划线占位的
1000
_^//不可以，因为k为1
0000

0000

0000
一直到i==1,j==1时……
0000

0000
-^//可以！
0000

0000
所以答案就是：
1000
0100
0000
0000
```

注释在代码里 ~~（我不会告诉你们我没词了~~
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
bool k[105][105]={false};
int n,m;
void dg(int m)
{
    if(m==0)//终止条件
        return;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(!k[i][j])
            {
                if(i==j)//因为我是从头循环的，所以能加在对角线上就加在对角线上
                {
                    k[i][j]=true;
                    m--;
                    dg(m);//递归下一层
                    return;//返回上一层
                }
                if(m>1&&i!=j)//如果不属于对角线m又大于1就把它和它相对的那个赋为true
                {
                    k[i][j]=k[j][i]=true;
                    m-=2;
                    dg(m);
                    return;
                }
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    if(n*n<m)//如果格子数不够就puts("-1")
    {
        puts("-1");
        return 0;
    }
    else if(n*n==m)//等于就全输出1
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                cout<<"1"<<" ";
            puts("");
        }
        return 0;
    }
    dg(m);//开始递归
    for(int i=0;i<n;i++)//输出
    {
        for(int j=0;j<n;j++)
        {
            if(k[i][j])
                cout<<"1"<<" ";
            else
                cout<<"0"<<" ";
        }
        puts("");
    }
    return 0;//AC
}
```

---

