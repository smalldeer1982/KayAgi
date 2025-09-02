# [ABC355C] Bingo 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc355/tasks/abc355_c

縦 $ N $ 行、横 $ N $ 列のマス目があり、上から $ i $ 行目、左から $ j $ 列目のマスには整数 $ N\times\ (i-1)+j $ が書かれています。

今から $ T $ ターンにわたって相異なる整数が宣言されます。$ i $ ターン目には $ A_i $ が宣言され、$ A_i $ が書かれたマスに印をつけます。初めてビンゴを達成するのは何ターン目か求めてください。ただし、$ T $ ターンの中でビンゴを達成しない場合は `-1` を出力してください。

ここで、ビンゴを達成するとは以下のいずれかのうち少なくとも一つ満たされることを言います。

- マス目の横の列であって、列に含まれる $ N $ 個のマスすべてに印がついているものが存在する
- マス目の縦の列であって、列に含まれる $ N $ 個のマスすべてに印がついているものが存在する
- マス目の対角線の列であって、列に含まれる $ N $ 個のマスすべてに印がついているものが存在する

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^3 $
- $ 1\leq\ T\leq\ \min(N^2,2\times\ 10^5) $
- $ 1\leq\ A_i\leq\ N^2 $
- $ i\neq\ j $ ならば $ A_i\neq\ A_j $
- 入力は全て整数
 
### Sample Explanation 1

マス目の状態は以下のように変化します。初めてビンゴを達成するのは $ 4 $ ターン目です。 !\[\](https://img.atcoder.jp/abc355/85614db45da7c299bcc5551fc45092a7.png)

### Sample Explanation 2

$ 5 $ ターンの中でビンゴを達成できないので `-1` を出力してください。

## 样例 #1

### 输入

```
3 5
5 1 8 9 7```

### 输出

```
4```

## 样例 #2

### 输入

```
3 5
4 2 9 7 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 12
13 9 6 5 2 7 16 14 8 3 10 11```

### 输出

```
9```

# 题解

## 作者：SXqwq (赞：3)

### Description

给定一个 $n\times n$ 的网格。从上往下第 $i$ 行，从左往上第 $j$ 列的单元格包含整数 $n×(i−1)+j$。

共有 $t$ 次操作，每次操作给定一个整数 $a_i$ 并在网格中把它标记。请求出最少经过几次操作使得 **任意一行，任意一列，任意一条对角线被标记。**

$2 \le n \le 2\times 10^3$。
### Analysis

一眼二分。

二分最小操作次数，对于每一个 $mid$，若合法则改变右区间，否则改变左区间。

满足局部答案舍弃性，若一个 $mid$ 不合法则比它小的一定不合法，二分成立。

还需注意的一个细节是，题目给定的是需标记数字，我们需要将其转换为坐标。这也很简单，通过画图模拟可得，若设需标记数字为 $m$，则坐标为 $(m-(\lceil \frac{m}{n}\rceil-1)\times n,\lceil \frac{m}{n} \rceil)$。

对于判断是否合法，我直接暴力地扫了一遍，依据题意模拟即可。
具体实现见代码。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3000;
int n,t;
int vis[N][N];
int cnt = 0;
int k[N*100];
bool check()
{
    for(int i=1;i<=n;i++) //行
    {
        bool flg = 1;
        for(int j=1;j<=n;j++)
        {
            if(!vis[i][j])
            {
                flg = 0;
                break;
            }
        }
        if(flg) return 1;
    }
    for(int j=1;j<=n;j++) //列
    {
        bool flg = 1;
        for(int i=1;i<=n;i++)
        {
            if(!vis[i][j]) 
            {
                flg = 0;
                break;
            }
        }
        if(flg) return 1;
    }
    int px = 1,py = 1; //对角线
    bool flg = 1;
    for(int i=1;i<=n;i++)
    {
        if(!vis[px][py]) 
        {
            flg = 0;
            break;
        }
        px ++;
        py ++;
    }
    if(flg) return 1;
    px = n;py = 1;
    flg = 1;
    for(int i=1;i<=n;i++)
    {
        if(!vis[px][py]) 
        {
            flg = 0;
            break;
        }
        px -- ;
        py ++;
    }
    if(flg) return 1;
    return 0;

}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>t;
    for(int i=1;i<=t;i++)
    {
        cin>>k[i];
    }
    int l = 1,r = 200000+1;
    while(l <= r) //二分
    {
        int mid = (l+r) / 2;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=min(mid,t);i++)
        {
            double y = ceil(k[i]*1.0/n); //坐标转换
            int x = k[i]-((y-1)*n);
            vis[x][(int)y] = 1; //标记
        }
        if(check()) 
        {
            r = mid - 1;
        }
        else l = mid+1;
    }
    memset(vis,0,sizeof(vis));
        for(int i=1;i<=min(l,t);i++) //这里再判断一下二分结果是否合法
        {
            double y = ceil(k[i]*1.0/n); 
            int x = k[i]-((y-1)*n);
            vis[x][(int)y] = 1; 
        }
    if(!check()) cout<<"-1"<<endl;
    else cout<<l<<endl;
}
```

---

## 作者：XXh0919 (赞：3)

## 题意

我相信题目说的很明确。

## 解法

其实就是一道通过格子里的数逆序找数 $a_i$ 的横纵坐标的题。我们可以通过公式找到 $a_i$ 的横坐标，纵坐标经过观察可以知道是由 $a_i \bmod N$ 得到的。至于对角线，若 $a_i$ 的横纵坐标相等，就表示 $a_i$ 在从左上到右下的那条对角线上，若 $a_i$ 的横纵坐标相加等于 $N+1$，就表示 $a_i$ 在从右上到左下的那条对角线上。然后对行、列和对角线上的数进行计数，若其中一方归零了，就表示可以，输出。否则，若循环完了都没有其中一方归零，输出 $-1$。

## AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=3e5+15;

int n,t;
int a[N];
int h[N],l[N],x1,x2;
/*
h[N]:行
l[N]:列
x1:左上到右下的对角线
x2:右上到左下的对角线
*/

signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>t;
	rep(i,1,n)h[i]=l[i]=n;
	x1=x2=n;
	rep(i,1,t){
		cin>>a[i];
		int ll=a[i]%n;
		ll==0?ll=n:ll=ll;
		int hh=(a[i]-ll)/n+1;
      //开始计数
		--h[hh];
		--l[ll];
		if(ll==hh)--x1;//在左上到右下的对角线上
		if(ll+hh==n+1)--x2;//在右上到左下的对角线上
      
		if(!x1||!x2||!h[hh]||!l[ll]){//任意一方归零
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}
```

感谢用户 [fengzhaoyu](https://www.luogu.com.cn/user/983555) 的帮助！

---

## 作者：MinimumSpanningTree (赞：3)

[题目链接](https://www.luogu.com.cn/problem/AT_abc355_c)

给出数字，我们可以得出数字所在的行和列。接下来开两个一维数组表示某一行、某一列出现了多少个数字，开两个变量表示两条斜线出现了多少个数字。每次输入数字时把它所在的行和列都 $+1$。再判断如果在斜线上，所在斜线 $+1$。加完之后判断是否满足某行某列或某斜线出现数字 $=n$，如果满足就直接输出 $i$ 并 `return 0`。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=2e3+100;
int n,t,a,cx[N],cy[N],dg1,dg2,x,y;
int main()
{
	scanf("%d%d",&n,&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d",&a);
		x=(a-1)/n+1,y=a%n;
		if(!y) y=n;
		//printf("%d %d\n",x,y);
		cx[x]++,cy[y]++;
		if(x==y) dg1++;
		if(x+y==n+1) dg2++;
		if(cx[x]==n||cy[y]==n||dg1==n||dg2==n) 
		{
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}
```

---

## 作者：I_Love_DS (赞：2)

## 思路

本题的暴力算法是从 $1 \sim t$ 枚举每一个状态，如果某个方案可行，那么就输出这个状态的编号；如果 $1 \sim t$ 没有一个方案是可行的，就输出 `-1`。

但是，判断函数是 $O(n^2)$ 的，总时间复杂度为 $O(n^2 \times t)$，会 TLE，根本过不去。

### 如何优化

设 $l = 1,r = t$，我们可以发现，**如果 $mid$ 状态成立，那么 $mid \sim r$ 的状态都成立；如果 $mid$ 状态不成立，那么 $l \sim mid$ 的状态都不成立。**

那么如果 $mid$ 状态成立，就使 $r = mid$，否则 $l = mid$。

**这不就是二分吗？？？**

如果最后 $l = t$，说明无解，输出 `-1`。

总时间复杂度 $O(n^2 \times \log t)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t;
int wrt[2024][2024]; 
//存这个点是在哪个状态才落下的
//如果 = 3，表示这个格子是在第三个状态才落下的
//如果 = 0，表示这个格子从来都没有棋子
bool check(int x){ //判断函数
	for (int i = 1; i <= n; i++) {
		bool flag = true;
		for (int j = 1; j <= n; j++) {
			if (wrt[i][j] > x || wrt[i][j] == 0) {
//> x 或 == 0表示在此状态下这个位置没有棋子，下同
				flag = false;
				break;
			}
		}
		if (flag) return true;
	}
	for (int i = 1; i <= n; i++) {
		bool flag = true;
		for (int j = 1; j <= n; j++) {
			if (wrt[j][i] > x || wrt[j][i] == 0) {
				flag = false;
				break;
			}
		}
		if (flag) return true;
	}
	bool flag = true;
	for (int i = 1; i <= n; i++) {
		if (wrt[i][i] > x || wrt[i][i] == 0) {
			flag = false;
			break;
		}
	}
	if (flag) return true;
	flag = true;
	for (int i = 1,j = n; i <= n && j >= 1; i++,j--) {
		if (wrt[i][j] > x || wrt[i][j] == 0) {
			flag = false;
			break;
		}
	}
	if (flag) return true;
	else return false;
}
int main(){
	scanf("%d%d",&n,&t);
	for (int i = 1; i <= t; i++) {
		int x;
		scanf("%d",&x);
		wrt[(x - 1) / n + 1][(x - 1) % n + 1] = i;
		//结合上文，把这行留给读者自行尝试和思考
	}
	int l = 0,r = t + 1,mid;//愉快的二分
	while (l + 1 < r) {
		mid = (l + r) / 2;//取中间值
		if (check(mid)) r = mid;//可行，右边界左移
		else l = mid;//不可行，左边界右移
	}
	if (l == t) printf("-1");//无解输出-1
	else printf("%d",r);//有解输出答案
	return 0;
}
```

---

## 作者：sssscy_free_stdio (赞：2)

我这个 Atcoder Better 很奇怪，把 announced 翻译成了公布，不过不影响。

可以用 map 存一个数在矩阵中的 $i$ 和 $j$。

再开两个数组记录每行每列被公布了几个。

再开一个 tmp 记录矩阵中每个位置是否被公布。

每次公布了 $a_i$ 后更新。

然后判断是否有一列或一行被公布的个数等于 $n$。

再看对角线。

枚举 $i$，然后判断 $tmp_{i,i}$ 是否被公布。

另一条也一样，枚举 $i$，然后判断 $tmp_{i,n-i+1}$ 是否被公布。

只要满足一条，便输出答案。

### AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,t,col[2010],row[2010],tmp[2010][2010],cnt[2010][2010],a[200010];
map<int,pair<int,int> >mp;
signed main(){
    scanf("%lld%lld",&n,&t);
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
    		cnt[i][j]=n*(i-1)+j;
    		mp[cnt[i][j]]=make_pair(i,j);//存i,j
		}
	}for(int i=1;i<=t;i++){
    	scanf("%lld",&a[i]);
    	int ci=mp[a[i]].first,cj=mp[a[i]].second;
    	tmp[ci][cj]=1;//更新
    	col[ci]++;
    	row[cj]++;
    	int flag=0,flag1=0,flag2=0;
    	for(int j=1;j<=n;j++){
    		if(col[j]==n||row[j]==n){//满足条件
    			flag=1;
			}
		}for(int j=1;j<=n;j++){
    		if(tmp[j][j]==0){
    			flag1=1;
    			break;
			}
		}if(flag1==0){//满足条件
			flag=1;
		}for(int j=1;j<=n;j++){
    		if(tmp[j][n-j+1]==0){
    			flag2=1;
    			break;
			}
		}if(flag2==0){//满足条件
			flag=1;
		}if(flag==1){
			printf("%lld",i);
			return 0;
		}
	}printf("-1");
	return 0;
}
```

---

## 作者：Hughpig (赞：2)

方便起见，我在这里假设网格为 $W$，下标从 $0$ 开始。

对于数字 $i$，显然它位于网格的 $\dfrac{i-1}{N}$ 行，$(i-1)\mod N$ 列。

然后对于每个 $A_i$ 把它在网格上的位置标记一下，然后检查是否实现 Bingo 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

constexpr int N=2e3+7;

int n,x;
bool vis[N][N];

int main()
{
    cin>>n;
    int TestCases=1;
    cin>>TestCases;
    for(int qwq=0;qwq<TestCases;++qwq){
    	cin>>x;
    	vis[(x-1)/n][(x-1)%n]=1;
    	bool flag=1;
    	for(int i=0;i<n;++i){
    		if(!vis[(x-1)/n][i])flag=0;
		}
		if(flag)cout<<qwq,exit(0);
		flag=1;
		for(int i=0;i<n;++i){
    		if(!vis[i][(x-1)%n])flag=0;
		}
		if(flag)cout<<qwq,exit(0);
		flag=1;
		for(int i=0;i<n;++i){
    		if(!vis[i][i])flag=0;
		}
		if(flag)cout<<qwq,exit(0);
		flag=1;
		for(int i=0;i<n;++i){
			if(!vis[i][n-i-1])flag=0;
		}
		if(flag)cout<<qwq,exit(0);
    }
    cout<<-1;
	return 0;
}
```

---

## 作者：wfirstzhang (赞：1)

# ABC355C题解
## 思路
题目的意思是让我们判断新来数字的那一行，那一列有没有全被标记；如果在主对角线或副对角线上，还要判断这两条对角线有没有被标记。

可以考虑标记数组，标记这一条线上还有多少数**没被使用**。如果标记后发现全部被使用（标记为 $0$），就输出当前步数。到最后还没有被完全标记的，就输出 $-1$。

按这种思路，一共需要 $2$ 个标记数组，表示每行每列；和 $2$ 个变量，表示对角线。
### 行列处理方式
![](https://img.atcoder.jp/abc355/85614db45da7c299bcc5551fc45092a7.png)
如图所示，在 $x$ 行 $y$ 列的数字是 $N \times (i-1) + j$。这里我采用最笨的方式，开一个 $mp$ 数组，表示这个数在第 $x$ 行第 $y$ 列。

初始化时两重循环，把 $mp_{N\times (i-1) + j}$ 赋值为 $i,j$。过程复杂度 $\Theta (N^2)$。
### 四标记初始化方式
对于行和列的标记数组，把每一行、列初始化为 $N$。两条对角线也全部初始化为 $N$。过程复杂度 $\Theta(N)$。
### 标记方式
在输入一个数时，先查表 $mp$ 查出对应的行和列。然后将对应行列上没被使用的数字 $-1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/nx0g5ez7.png)
主对角线上，$x$ 和 $y$ 坐标的差都是 $0$，所以当检查到 $x-y=1$ 时，主对角线标记 $-1$。

副对角线上，$x$ 和 $y$ 坐标的和都是 $N+1$，其它过程与上方同理。

标记过程复杂度都是 $O(1)$。

## AC Code
```cpp
#include <iostream>
using namespace std;
int n, tmp, T;
int vis_r, vis_c, vis_x[4096], vis_y[4096];
pair<int, int> mp[4194304];
void init() {
    for (int i = 1; i <= n; i++)
		vis_x[i] = vis_y[i] = n; //每行每列都有 N 个数字
	vis_r = n, vis_c = n; //两个对角线上都有 N 个数字
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mp[n * (i - 1) + j] = { i,j }; //便于获取行和列
}
int main() {
	cin >> n >> T;
	init();
	for(int i = 1; i <= T; i++)
	{
		cin >> tmp;
		const int x = mp[tmp].first, y = mp[tmp].second;
		vis_x[x]--; vis_y[y]--; //行列还剩的数
		if (x - y == 0)	vis_r--; //主对角线
		if (x + y == n + 1)	vis_c--; //副对角线
		if(!vis_x[x] || !vis_y[y] || !vis_r || !vis_c)
		{
			cout << i << endl;
			return 0;
		}
	}
	cout << "-1" << endl;
	return 0;
}
```

---

## 作者：lucasincyber (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc355_c)
## 思路
如果我们对于每一次操作都进行一次判断，时间复杂度很劣，为 $O(n \times T)$。我们可以将每一排，每一列和每一条对角线都开一个变量 $x$，表示对于当前的要判断的位置，有多少个还没有被标记。这样对于每一次操作，只用判断那些变量需要改变，再判断这些改变了的变量中有没有全部标记了的。

这样每次判断时间复杂度为 $O(1)$，总时间复杂度 $O(T)$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, M = 2005;

int n, t;
int a[N], row[M], col[M], dia[4]; // 记录的数组

int main()
{
    scanf("%d%d", &n, &t);
    dia[1] = dia[2] = n;
    for (int i = 1; i <= n; i++)
        row[i] = col[i] = n;
    for (int i = 1; i <= t; i++)
    {
        scanf("%d", &a[i]);
        int x = ceil(a[i] * 1.0 / n), y = a[i] % n; // 算挡前数的坐标
        if (y == 0) y = n;
        row[x]--;
        col[y]--;
        if (x == y) dia[1]--;
        if (x + y - 1 == n) dia[2]--;
        if (!row[x] || !col[y] || !dia[1] || !dia[2])
        {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
首先 $a_i$ 是第 $\lfloor\frac{a_i-1}{n}\rfloor$ 行第 $(a_i-1)\bmod n$ 列的（此处均为 $0$ 开始），然后每次添加点肯定不用整个都判断，只需要判断更改的部分即可。
# 代码
```cpp
# include <bits/stdc++.h>
# define done {cout << i; return 0;}
using namespace std;
int n, t, x, y, sh[3005], sl[3005], s1, s2;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> t;
	for (int i = 1; i <= t; ++ i) {
		cin >> x;
		-- x, y = x % n, x /= n;
		if (++ sh[x] >= n)
			done;
		if (++ sl[y] >= n)
			done;
		if (x == y && ++ s1 >= n)
			done;
		if (x == n - y - 1 && ++ s2 >= n)
			done;
	}
	cout << "-1";
	return 0;
}
```

---

## 作者：ThisIsLu (赞：1)

直接模拟就可以了，记录每行每列和对角线上被公布的数数量，检查是不是等于 $n$，若等于就输出 Yes 并退出，否则输出 No。

关于位置：

题目中给出的是编号而非坐标，因此需要解方程：

$$n(x-1)+y=a$$

其中 $1 \le x,y \le n,x,y\in N$。

移项：

$$a-y=n(x-1)$$

$$x=\dfrac{a-y+n}{n}$$

又有：

$$y \equiv a \pmod n$$

由于 $1 \le y \le n$，所以：

$$y=(a-1) \bmod n+1$$

回代得：

$$x=\dfrac{a+n-1-(a-1) \bmod n}{n}=\left\lceil\dfrac{a}{n}\right\rceil=\left\lfloor\dfrac{a+n-1}{n}\right\rfloor$$

关于如何判断在对角线上：

对于从左下到右上的对角线，条件为 $x+y=n+1$。

对于从左上到右下的对角线，条件为 $x=y$。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int mpx[2005],mpy[2005];
int sum1,sum2;
bool visx,visy,visxx,visyy;
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int ai;
        cin>>ai;
        int x=(ai+n-1)/n;
        int y=(ai-1)%n+1;
        mpx[x]++;
        mpy[y]++;
        if(x==y){
            sum1++;
        }
        if(x+y==n+1){
            sum2++;
        }
        if(mpx[x]==n) visx=true;
        if(mpy[y]==n) visy=true;
        if(sum1==n) visxx=true;
        if(sum2==n) visyy=true;
        if(visx||visy||visxx||visyy){
            cout<<i<<"\n";
            return 0;
        }
    }
    cout<<"-1";
    return 0;
}
```

---

## 作者：crz_qwq (赞：0)

### 思路
由于 $T$ 很大，所以我们只能使用时间复杂度 $O(T)$ 的算法。\
考虑用 $l_i$ 维护每行的 $0$ 的数量，$c_i$ 维护每列的 $0$ 的数量，$djx$ 维护主对角线的 $0$ 的数量，$fdjx$ 为副对角线的 $0$ 的数量，初始值都是 $N$。\
在一次修改中，将这个数 $A_i$ 转化为坐标 $(x_i,y_i)$ ，对 $l_{x_i}$ 减去一个 $1$，同时对 $r_{x_i}$ 减去 $1$。\
当 $x_i=y_i$ 的时候，将 $djx$ 减去一个 $1$，当 $x_i=N-y_i+1$ 时，将 $fdjx$ 减去 $1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int n,q,a[N][N],p[N][N],x[N*N],y[N*N],l[N],c[N],cnt;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		l[i]=c[i]=n;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			p[i][j]=++cnt;
			x[cnt]=i;
			y[cnt]=j;
		}
	int djx=n,fdjx=n;
	for(int C=1;C<=q;++C)
	{
		int k;
		cin>>k;
		a[x[k]][y[k]]=1;
		--c[x[k]],--l[y[k]];
		if(x[k]==y[k])
			--djx;
		if(x[k]==n-y[k]+1)
			--fdjx;
		if(!c[x[k]]||!l[y[k]]||!djx||!fdjx)
		{
			cout<<C;
			exit(0);
		}
	}
	cout<<-1;
} 
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定一个 $n \times m$ 的矩阵，第 $i$ 行第 $j$ 列是数 $a_{i,j} = n \times (i-1) + j$。

有 $m$ 次操作：

- 每次给定 $x$，将值为 $x$ 的方格染色。

需要判断在第几次操作时满足以下条件之一：

- 有一行都被染色。

- 有一列都被染色。

- 存在一条对角线都被染色。

### 思路：

注意到每个位置的值都不一样，即每次操作只会将一个格子染色。

求 $x$ 所在的方格位置，易知为 $(\lfloor \frac{x-1}{n} \rfloor + 1,((x-1) \bmod n) + 1)$。

需要记录一下每行每列被染色的个数。

然后若 $a=b$，则在主对角线上；若 $a+b=n+2$，则在副对角线上；分别统计一下个数即可。

时间复杂度为 $O(M)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef long long ll;
typedef double db;
const ll N=2e3+10;
mt19937 R(time(0));
inline ll Rand(ll l,ll r){
	if(l==r)
	  return l;
	return R()%(r-l+1)+l;
}
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,x,a,b,t1,t2;
ll s1[N],s2[N];
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		x=read();
		a=(x-1)/n,b=(x-1)%n;
		if(++s1[a]==n){
			write(i);
			exit(0);
		}
		if(++s2[b]==n){
			write(i);
			exit(0);
		}
		if(a==b&&++t1==n){
			write(i);
			exit(0);
		}
		if(a+b==n-1&&++t2==n){
			write(i);
			exit(0);
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
这道题我们定义一个行数组和列数组和对角线数组，对于每一个数，只需算出它对应的行和列和在不在两条对角线上，再判一下数组有没有超过 $k$，就行了。
*   行：如果当前数 $x$ 是 $n$ 的倍数，则行是 $x \div n$。否则行是 $x \div n-1$。
*   列：如果当前数 $x$ 是 $n$ 的倍数，则列是 $n$。否则列是 $x \bmod n$。
*   对角线：观察找规律可得，第 $x$ 正对角线的数是 $1 + ( x - 1) \times (n + 1)$，第 $x$ 负对角线的数是 $n + ( x - 1) \times (n - 1)$。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,t;
int a[200005];
int h[2001],s[2001],x[3];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=t;i++)
	{
		h[a[i]%n]++;
		int tt=a[i]/n+1;
		if(a[i]%n==0) tt-=1;
		s[tt]++;
		if((a[i]-1)%(n+1)==0&&(a[i]-1)/(n+1)==tt-1) 
		{
			x[1]++;
		}
		if((a[i]-n)%(n-1)==0&&(a[i]-n)/(n-1)==tt-1) 
		{
			x[2]++;
		}
		if(h[a[i]%n]>=n||s[tt]>=n||x[1]>=n||x[2]>=n)
		{
			cout<<i<<"\n";
			return 0;
		}
	}
	cout<<-1<<"\n";
	return 0;
}

```

---

## 作者：LZYAC (赞：0)

## 思路
分两个方面解决此题：

+ 两条对角线

通过找规律的方式得出两条对角线的成立式如下：

$i \times (n-1) + 1$ 是反对角线。

$n \times (i-1) + i$ 是正对角线。

于是用 map 预处理之后判断是否在线上即可。

+ 行列

开两个一维数组进行存储，每次输入的数字判断在几行几列，计数即可。

每次计数后进行判断，次数等于 $n$ 次时输出次数。

如果循环结束还未输出就输出 ``-1`` 。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,x,h[5010],s[5010],xie1,xie2;
map<int,bool> b1,b2;
signed main(){
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++) b1[i*n-i+1]=true;
	for(int i=1;i<=n;i++) b2[(i-1)*n+i]=true;
	for(int i=1;i<=t;i++){
		scanf("%d",&x);
		if(b1[x]==true){
			xie1++;
			if(xie1==n){
				printf("%d",i);
				return 0;
			}
		}
		if(b2[x]==true){
			xie2++;
			if(xie2==n){
				printf("%d",i);
				return 0;
			}
		}
		h[(x%n==0?x/n:x/n+1)]++;
		if(h[(x%n==0?x/n:x/n+1)]==n){
			printf("%d",i);
			return 0;
		}
		s[x%n+1]++;
		if(s[x%n+1]==n){
			printf("%d",i);
			return 0;
		}
		
	}
	printf("-1");
    return 0;
}

```

---

## 作者：tder (赞：0)

[ABC355 场记](https://tder6.github.io/articles/ABC355A%20to%20ABC355E%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。 

---

**【题意】**

在 $n\times n$ 的棋盘上，位于 $(i,j)$ 的格子上写有 $(i-1)\times n+j$。依次翻开写有 $a_i$ 的格子，求第几次操作可以达成 Bingo。

**【思路】**

达成 Bingo 的充要条件是存在某行、某列、某对角线上所有 $n$ 个格子均被翻开。

考虑用 $a_i$ 表示第 $i$ 行现被翻开了的格子的个数，用 $b_j$ 表示第 $j$ 列现被翻开了的格子的个数，用 $c_k$ 表示对角线现被翻开了的格子的个数。由此，达成 Bingo 的充要条件即为存在 $q$ 使得 $a_q=n$ 或 $b_q=n$ 或 $c_q=n$。

那么，对于一个写有 $p$ 的格子，考虑其贡献。容易得到其坐标为 $(x,y)=\left(\left\lfloor\dfrac{p-1}n\right\rfloor+1,((p-1)\bmod n)+1\right)$，且当且仅当 $x=y$ 时在左上—右下对角线、当且仅当 $x+y=n+1$ 时在右上—左下对角线。

于是，其仅能对 $a_x$ 和 $b_y$ 产生贡献，若满足对应条件则可能对 $c_k$ 产生贡献。对于可以产生贡献的，判断其是否等于 $n$ 并输出操作数即可。

时间复杂度 $O(T)$，有一定的常数。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e3 + 5;
int n, t, a[N], b[N], c[N];
signed main() {
	cin>>n>>t;
	for(int i = 1; i <= t; i++) {
		int x; cin>>x;
		a[(x - 1) / n + 1]++, b[(x - 1) % n + 1]++;
		if(((x - 1) / n + 1) == ((x - 1) % n + 1)) c[1]++;
		if(((x - 1) / n + 1) + ((x - 1) % n + 1) == n + 1) c[2]++;
		if(a[(x - 1) / n + 1] == n) cout<<i<<endl, exit(0);
		if(b[(x - 1) % n + 1] == n) cout<<i<<endl, exit(0);
		if(c[1] == n) cout<<i<<endl, exit(0);
		if(c[2] == n) cout<<i<<endl, exit(0);
	}
	cout<<-1<<endl;
}
```

---

## 作者：yegengghost (赞：0)

如果我早知道打比赛也会被……

设输入值为 $num$，则我们可以将输入的每个值的坐标如下表示：

* 横坐标：```x=num/n+(num%n?1:0);```

* 纵坐标：```y=(num-1)%n+1;```

那么就可以把当前值的横坐标，纵坐标为下标，加到对应的数组里，来判断是否有宾果出现。

对角线的判断方法：

* 左上到右下：```x==y;```

* 右上到左下：```n-x+1==y;```

最后在每一次判断当前行列，以及对角线是否构成宾果即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114514;
int n,t;
int h[N],l[N],k1,k2;//行，列，左上到右下的对角线，右上到左下的对角线 
int read()
{
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
signed main()
{
	n=read();
	t=read();
	for(int i=1;i<=t;i++)
	{
		int num;
		num=read();
		int x=num/n+(num%n?1:0);
		int y=(num-1)%n+1;
		//记录横纵坐标 
		h[x]++;
		l[y]++;
		//当前行列++ 
		if(x==y)
			k1++;
		if(n-x+1==y)
			k2++;
		//判定对角线 
		if(h[x]==n||l[y]==n||k1==n||k2==n)
		{
			cout<<i<<'\n';
			return 0;
		}
		//每一次都要判断是否有宾果 
	}
	cout<<-1<<'\n';
	//没有宾果只能遗憾离场 
	return 0;
}
```

---

## 作者：int_stl (赞：0)

题意：给定一个 $N \times N$ 的网格，有 $T$ 次操作，每一次指定一个数 $A_i$，把 $A_i$ 所在的位置打上标记，问第一次形成 Bingo 的是第几次。

我们考虑预处理每个数在第几行第几列，然后对于每次操作，给这个位置打上标记，标记的数字表示这是第几次操作。

接着，我们检查是否形成 Bingo，如果形成 Bingo，那么取当前行、列或对角线的最大值，这就表示在第几次形成 Bingo，再取最小值即可。

时间复杂度 $O(N^2+T)$，空间复杂度 $O(N^2)$。

代码如下：
```cpp
int a[2005][2005];
int visline[2005 * 2005], viscol[2005 * 2005];
int n, t;
int main() {
	read(n, t);
	rep(i, 1, n, 1) {
		rep(j, 1, n, 1) {
			visline[(i - 1) * n + j] = i;
			viscol[(i - 1) * n + j] = j;
		}
	}
	rep(i, 1, t, 1) {
		int num;
		read(num);
		a[visline[num]][viscol[num]] = i;
	}
	int mn = 1e9;
	rep(i, 1, n, 1) { // check a line
		int cnt = 0, mx = -1;
		rep(j, 1, n, 1) {
			if (a[i][j]) {
				cnt++;
				mx = max(mx, a[i][j]);
			}
		}
		if (cnt == n) {
			mn = min(mn, mx);
		}
	}
	rep(j, 1, n, 1) { // check a column
		int cnt = 0, mx = -1;
		rep(i, 1, n, 1) {
			if (a[i][j]) {
				cnt++;
				mx = max(mx, a[i][j]);
			}
		}
		if (cnt == n) {
			mn = min(mn, mx);
		}
	}
	int cnt = 0, mx = -1;
	rep(i, 1, n, 1) {
		if (a[i][i]) {
			cnt++;
			mx = max(mx, a[i][i]);
		}
	}
	if (cnt == n) {
		mn = min(mn, mx);
	}
	cnt = 0, mx = -1;
	rep(i, 1, n, 1) {
		if (a[i][n - i + 1]) {
			cnt++;
			mx = max(mx, a[i][n - i + 1]);
		}
	}
	if (cnt == n) {
		mn = min(mn, mx);
	}
	if (mn != 1000000000) write(mn);
	else write(-1);
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc355_c)

## 思路

在线模拟操作时间复杂度为 $\mathcal{O}(N^2T)$，会超时，所以我们考虑离线操作。

读入数据的时候在对应位置标记好它被染色的次序。从 $(0,0)$ 开始数，数字 $x$ 在 $(\lfloor \frac{x-1}{N}\rfloor,(x-1)\bmod N)$ 的位置上。读入完成后再二重循环查找即可。经过这番操作，时间复杂度降为 $\mathcal{O}(N^2+T)$。

- 记得如果找不到，输出 ``-1``。

- 由于我们要找的是最小时间，所以要把每个点的染色时间**初始化为一个极大值**。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n,T,a[N][N],ans=1e9;
signed solution(){
	cin>>n>>T;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)a[i][j]=1e9;
	}
	for(int i=1;i<=T;++i){
		int x;
        cin>>x;
        --x;
		a[x/n][x%n]=i;
	}
	for(int i=0;i<n;++i){//横向找。
		int res=-1e9;
		for(int j=0;j<n;++j)res=max(res,a[i][j]);
		ans=min(ans,res);
	}
	for(int i=0;i<n;++i){//纵向找。
		int res=-1e9;
		for(int j=0;j<n;++j)res=max(res,a[j][i]);
		ans=min(ans,res);
	}
	int x=0,y=0,res=-1e9;
	while(x<n){//左上到右下。
		res=max(res,a[x][y]);
		++x;++y;
	}
	ans=min(ans,res);

	x=0,y=n-1,res=-1e9;
	while(x<n){//右上到左下。
		res=max(res,a[x][y]);
		++x;--y;
	}
	ans=min(ans,res);
	if(ans==(int)1e9)ans=-1;
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/160311532)

---

## 作者：unordered_yao (赞：0)

## 思路

1. 因为 $A_i$ 最大到 $4\times10^6$，完全可以用哈希表存储每个点的坐标。

2. 然后我们准备三个数组 $row,col,diag$，分别表示这个单元格的行、列、两条对角线上点的个数。注意的是，正方形的对角线有两条，$diag_0$ 表示直线 $y=x$ 所经过的对角线，$diag_1$ 表示直线 $y=-x$ 所经过的对角线。

3. 对于每个回合，我们取出输入数字的横纵坐标。首先，我们必须要知道，如果点 $s$ 的坐标是 $(x,y)$，那么这个坐标在第 $x$ 行，第 $y$ 列。

4. 根据上述，令我们将要标记的数字为 $a$，其坐标为 $(x,y)$，我们就要把 $row_x+1$，把 $col_y+1$，以及把两条对角线都要加上 $1$。

5. 如果第 $i$ 行或第 $i$ 列或两条对角线所经过的被标记数字的个数大于等于 $n$ 个，那么就直接输出当前回合数。如果到最后都没有找到，那么就输出 ```-1```。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename t>
inline void read(t &x){
    x = 0;char ch = getchar();bool f = 0;
    while(ch < '0' || ch > '9'){if(ch == '-')f = 1;ch = getchar();}
    while(ch >= '0' && ch <= '9')x = (x<<1) + (x<<3) + (ch^48),ch=getchar();
    if(f)x = -x;                                       
}
template <typename t,typename ...args>
inline void read(t &tmp,args &...tmps){read(tmp);read(tmps...);}
template<typename type>
inline void write(type x,short mode=0)//0为空格，1为换行，2啥也不干
{
    x<0?x=-x,putchar('-'):0;static short Stack[50],top(0);
    do Stack[++top]=x%10,x/=10; while(x);
    while(top) putchar(Stack[top--]|48);
    if(mode == 2) return;
    mode?putchar('\n'):putchar(' ');
}
const int N=3e3+20;
int row[N],col[N],diag[2];
unordered_map<int,pair<int, int>> pos;
int n,t;
int main() {
    read(n,t);
    vector<int> a(t);
    for (int i=0;i<t;i++) read(a[i]);
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            pos[n*i+j+1]={i,j};

    for (int s=0;s<t;s++) {
        int i=pos[a[s]].first,j=pos[a[s]].second;
        if (++row[i]==n || ++col[j] == n || (i==j && ++diag[0]==n) || (i+j==n-1 && ++diag[1]==n)) {
            write(s+1);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
```

---

## 作者：pengzy (赞：0)

### 题意
给定一个正方形矩阵，按照数字顺序排列（可以看 at 样例给的图）。

进行 $m$ 次点亮操作。规定当行、列、对角线中有一个满足每个数字全都被点亮，输出此时的操作次数。

### 思路
看这题的数据范围，很显然不可能每点亮一个数字，就去循环查找它所在的行、列、对角线。

我使用 $a$，$b$ 数组分别来统计每行，每列被点亮的个数。再用两个变量统计两个对角线。

每次读入的数，我们算出它所在的行、列，并统计。

```cpp
const int Max=2e3+10;
int n,t,a[Max],b[Max],d,f,ans;
int main()
{
	n=read(),t=read();
	for(int i=1;i<=t;i++) {
		int k;k=read();
		int p,q;//p为该数字所在行，q为所在列 
		if(k%n){p=k/n+1;q=k%n;}
		else{p=k/n;q=n;}
		if(p+q==n+1)d++;//判断是否在从右上角到左下角的对角线上 
		if(p==q)f++;//判断是否在左上到右下 
		a[p]++;b[q]++;
		if(d==n||f==n||a[p]==n||b[q]==n) {
			ans=i;
			break;
		}
	}
	if(ans==0)cout<<-1;//注意如果没有满足条件，输出-1 
	else cout<<ans;
	return 0;
}
```

---

## 作者：遥遥领先 (赞：0)

给你一个 $N\times N$ 的网格，第 $i$ 行，第 $j$ 列的格子里的数字是 $N\times(i-1)+j$。

每次输入一个不超过 $N\times N$ 的数，将网格中所对应数的格子标记一下，如果某次标记后出现行，列，或对角线上所有都标记过，输出现在标记的次数。

思路：因为一次标记只会影响它所在的行，列，或对角线，所以只需要枚举它所在的行，列，或对角线是否全部被标记，时间复杂度是 $O(N^2)$。

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

int n,m;
int vis[2010][2010];

void solve()
{
	cin >> n >> m;
	for (int i = 1;i <= m;i++)
	{
		int x;
		cin >> x;
		int xx = (x-1)/n+1,yy = (x-1+n)%n+1;
//		cout << xx << ' ' << yy << '\n';
		vis[xx][yy] = 1;
		int flag = 1;
		for (int j = 1;j <= n;j++)
			if (!vis[xx][j])
			{
				flag = 0;
				break;
			}
		if (flag)
		{
			cout << i;
			return ;
		}
		flag = 1;
		for (int j = 1;j <= n;j++)
			if (!vis[j][yy])
			{
				flag = 0;
				break;
			}
		if (flag)
		{
			cout << i;
			return ;
		}
		flag = 1;
		for (int j = 1;j <= n;j++)
			if (!vis[j][j])
			{
				flag = 0;
				break;
			}
		if (flag)
		{
			cout << i;
			return ;
		}
		flag = 1;
		for (int j = 1;j <= n;j++)
			if (!vis[j][n-j+1])
			{
				flag = 0;
				break;
			}
		if (flag)
		{
			cout << i;
			return ;
		}
	}
	cout << -1;
}

signed main()
{
	solve();
	return 0;
}

```

---

## 作者：Ivan422 (赞：0)

题目大意：给出一个 $n\times n$ 的棋盘，$1$ 到 $n^2$ 的数字从上往下，从左往右依次排列。给出 $T$ 次放置棋子，每次放在编号 $a_i$ 的格子上。要是发现有占满一行、一列、一对角线的情况，输出当前放置步数。要是发现没有一次占满，输出 $-1$。

思路：直接模拟放置操作。我们可以用一个简单的转化把数字转为坐标。再对棋盘进行放置。这里使用 $h$ 数组记录行占有情况，$w$ 数组记录列占有情况，$lx$ 和 $rx$ 表示对角线占有情况。每次模拟放置，发现占有即输出。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=2010,M=1010,P=998244353,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,t,x,px,py,id;
int h[N],w[N],lx,rx;
signed main(){
    cin>>n>>t;
    while(t--){
        cin>>x;++id;
        px=(x-1)/n+1;py=(x-1)%n+1;
        h[px]++;w[py]++;
        if(px==py)lx++;
        if(px+py-1==n)rx++;
        if(h[px]==n||w[py]==n||lx==n||rx==n){
            cout<<id;
            return 0;
        }
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：Guizy (赞：0)

这题关键在于给出一个数字如何判断行、列和对角线。

设当前数字为 $a_i$，行数为 $h$，列数为 $s$。

- 判断行、列 

简单找规律，发现 $h=\lfloor \frac{a_i+(n-1)}{n}\rfloor,s=a_i\bmod n$（如果 $a_i\bmod n$ 为 $0$ 的话就是第 $n$ 列）。

然后开一个数组统计每行每列的数字个数即可。

- 判断对角线

一个数在左上右下对角线当且仅当 $h=s$。

一个数在右上左下对角线当且仅当 $h+s=n+1$。

这个两个变量统计即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Max=2001;
int n,t,a[200001];
int heng[Max],shu[Max],zsyx,yszx;
/*每行被标记数字个数，每列被标记数字个数，左上右下对角线
被标记数字个数，右上左下对角线被标记数字个数*/

int main(){
	
	cin>>n>>t;
	for(int i=1;i<=t;i++){
		cin>>a[i];
		int h=(a[i]+(n-1))/n;
		int s=a[i]%n; if(s==0) s=n;//特判 a[i]%n=0
		heng[h]++,shu[s]++;
		if(h==s) zsyx++;
		if(h+s==n+1) yszx++;
		if(heng[h]==n||shu[s]==n||zsyx==n||yszx==n){
			cout<<i;
			return 0;
		}
	}
	cout<<-1;//无解
	
}
```

---

## 作者：kevinZ99 (赞：0)

# 思路

很明显暴力超时，如何优化呢？

先考虑行，每一行有什么特点，所有行数都一样，那么直接开一个桶记录，记录这一行出现了几个数字。

列同理。

接下来考虑两个对角线。

左上到右下，很明显行数等于列数，那么开桶记录。

~~另一条对角线与左上到右下相似，请读者自行完成。~~

另一条对角线就是把列数倒过来就行了。

# 代码

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define putendl putchar('\n')
#define putspace putchar(' ')
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using ll = long long ;
using hint = __int128 ;
using pii = pair<int,int> ;
using pll = pair<ll,ll> ;
using vi = vector<int> ;
using vl = vector<ll> ;
using vpi = vector<pair<int,int>> ;
using vpl = vector<pair<ll,ll>>;
using db = double ;
const double eps=1e-6;
namespace __STL{
	ll max(ll x,ll y){return x>=y?x:y;}
    ll min(ll x,ll y){return x<=y?x:y;}
    ll abs(ll x){return x<=0?-x:x;}
}
using namespace __STL;
namespace my{
	const int N=2005;
	string ot;
	int n,q;
	int col[N],row[N],s[2];
	void solve(){
		cin>>n>>q;
		up(d,1,q){
			int x;cin>>x;
			int i=x/n+1,j=x-(i-1)*n;
			if(x%n==0)i=x/n,j=n;
//			cout<<i<<' '<<j<<'\n';
			col[j]++;
			row[i]++;
			if(i==j)s[0]++;
			if(i==n-j+1)s[1]++;
			if(col[j]==n||row[i]==n||s[0]==n||s[1]==n){
				cout<<d<<'\n';
				return ;
			}
		}
		cout<<"-1\n";
	}
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;
	while(_--)my::solve();return 0;
}

```

---

## 作者：huangzhixia (赞：0)

[**场记**](https://www.luogu.com.cn/article/grncdeld)观赏效果更佳。

---

这题首先想到的就是暴力，我赛时算了算，不可过，什么预处理啊都没有，那么是不是这题要用什么科技算法或者毒瘤数据结构呢？

当然是不用的，我们需要换一个角度想问题，题目中只是问我们第一次出现“宾果”是在哪一个回合，并没有让我们具体告诉他哪一行哪一列之类的。于是乎，我们可以用 $h_i$ 表示第 $i$ 行还剩几个格子即可实现“宾果”，用 $l_i$ 表示第 $i$ 列还剩几个格子实现“宾果”，用 $x1$ 表示从左上到右下，用 $x2$ 表示从右上到左下。

用一个 ```map<int, pair<int, int>> mp``` 来记，表示下标上的数，在这个方阵里面对应哪一行哪一列。

然后每个回合将 ```h[mp[a[i]].first]``` 减 $1$ 为 $0$ 就输出当前的回合，结束程序，列也是同理。

那么斜线怎么判呢？观察一下样例解释给出的图，可以发现从左上到右下的斜线他们的 $i$ 是与 $j$ 相等的。发现这个就判断一下，成立说明这个数是在这条斜线上，再去减 $1$ 进行判断。

以上说的是从左上到右下，还有从右上到左下的。同样是观察方阵，可以发现凡是在这条斜线上的 $i + j$ 都等于 $n + 1$。通过这个即可判断是不是在从右上到左下的线上。然后也是将 $x2$ 减 $1$ 看看是不是等于 $0$。

你以为这就完了吗？当然还要在最后输出 ```-1```，如果整个循环等枚举完了还没有 ```return 0;```，说明无解，输出 ```-1```。

整洁的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, t, a[N], h[2001], l[2001], x1, x2;
map<int, pair<int, int>> mp;

int main(){
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= t; i++)
		scanf("%d", &a[i]);
	x1 = n, x2 = n;
	for (int i = 1; i <= n; i++)
		h[i] = n, l[i] = n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int y = n * (i - 1) + j;
			mp[y] = {i, j};
		}
	}
	for (int i = 1; i <= t; i++) {
		//printf("%d %d %d\n", a[i], mp[a[i]].first, mp[a[i]].second);
		if (--h[mp[a[i]].first] == 0) {
			cout << i << endl;
			return 0;
		}
		if (--l[mp[a[i]].second] == 0) {
			cout << i << endl;
			return 0;
		}
		if (mp[a[i]].first == mp[a[i]].second) {
			if (--x1 == 0) {
				cout << i << endl;
				return 0;
			}
		}
		if (mp[a[i]].first + mp[a[i]].second == n + 1) {
			if (--x2 == 0) {
				cout << i << endl;
				return 0;
			}
		}
	}
	puts("-1");
}
```

---

