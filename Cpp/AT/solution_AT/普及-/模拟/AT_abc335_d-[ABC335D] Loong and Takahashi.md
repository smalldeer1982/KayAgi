# [ABC335D] Loong and Takahashi

## 题目描述

给定一个 $N \times N$ 的网格，其中 $N$ 是小于等于 $45$ 的奇数。
龙和高桥君要在这个网格上放置 $N^2-1$ 个编号从 $1$ 到 $N^2-1$ 的龙的部件，满足以下条件：

- 高桥君必须放置在网格的中心位置，即 $(\frac{N+1}{2},\frac{N+1}{2})$。
- 除了高桥君所在的位置外，每个格子必须恰好放置一个龙的部件。
- 对于满足 $2 \leq x \leq N^2-1$ 的所有整数 $x$，龙的部件 $x$ 必须放置在与部件 $x-1$ 相邻的格子上，即两个格子之间有边相连。
	- 格子 $(i,j)$ 与格子 $(k,l)$ 相邻，当且仅当 $|i-k|+|j-l|=1$。

请输出满足条件的一种放置方式。

## 样例 #1

### 输入

```
5```

### 输出

```
1 2 3 4 5
16 17 18 19 6
15 24 T 20 7
14 23 22 21 8
13 12 11 10 9```

# 题解

## 作者：Little_x_starTYJ (赞：4)

### 题目大意：

高桥在一个地图的中心，有一条龙从地图的左上角开始，每次只能到达与他相邻的四个点，现给出地图的边长，请你给出一种方案，使得地图上的每个点除高桥所在的地方外，都被龙走过且不重复。

### 解题思路：

首先，我们拿到这个题目，想十秒，便会发现，我们按照螺旋矩阵的方式行走，一定是符合题意的，于是我们就开始模拟：

1. 如果我们没有走到最后一列，则向右走一列，并跳过此次循环。
2. 如果我们没有走到最后一行，则向下走一行，并跳过此次循环。
3. 如果我们没有走到第一列，则向左走一列，并跳过此次循环。
4. 如果我们没有走到第一行，则向上走一行。

然后，我们就会发现，我们会走到重复的点。

于是，我们看了看 $n$ 的数据范围，很小，所以直接定义一个数组标记，在模拟时判断当前点是否走过，然后直接执行下一步即可。

AC CODE:

```cpp
#include <bits/stdc++.h>
using namespace std;
int c[50][50];
int main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	c[n / 2 + 1][n / 2 + 1] = 114514;
	int x = 1, y = 1;
	int ans = 1;
	int flag = 1;
	while (ans < n * n) {
		c[x][y] = ans++;
		if (flag == 1)
			y++, flag = (y < n && !c[x][y + 1] ? 1 : 2);
		else if (flag == 2)
			x++, flag = (x < n  && !c[x + 1][y] ? 2 : 3);
		else if (flag == 3)
			y--, flag = (y > 1  && !c[x][y - 1] ? 3 : 4);
		else
			x--, flag = (x > 1  && !c[x - 1][y] ? 4 : 1);
	}
	for (int i = 1; i <= n; i++, cout << endl)
		for (int j = 1; j <= n; j++)
		{
			if (c[i][j] == 114514)
				cout << "T ";
			else
				cout << c[i][j] << ' ';
		}
	return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：1)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

实际上就是要你从中间走，然后每一个点都遍历到，输出它的编号，由于样例是一环一环的，所以我误解了题意，其实直接遍历，到了不可以的地方就回退就行了。

本代码的实现是先处理好每一圈的环数然后遍历每一个环，如果遍历不了，往左边走。

[link](https://atcoder.jp/contests/abc335/submissions/49075489)。

---

## 作者：_shine_ (赞：0)

因为 $n$ 是奇数，所以说高桥的位置是能确定的，并且正是因为 $n$ 是奇数，所以高桥到任意一个边界的距离是相等的。

所以说既然高桥到周围一圈的距离是相等的，所以不妨尝试从 $\left(1,1\right)$ 开始放龙，并且当前方是放了龙的或是边界则就转弯，这可以使得分配刚刚好。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+10;
int a[maxn][maxn],n;
int a1[]={1,-1,0,0},b1[]={0,0,1,-1};
bool check(int x,int y){if(x<1 || y<1 || x>n || y>n || a[x][y]!=0)return true;return false;}
void dfs(int x,int y,int cnt,int num){
	a[x][y]=num;
	if(check(x+a1[cnt],y+b1[cnt])==true){for(int i=0;i<4;++i)if(check(x+a1[i],y+b1[i])==false){dfs(x+a1[i],y+b1[i],i,num+1);break;}}
	else dfs(x+a1[cnt],y+b1[cnt],cnt,num+1);
}
signed main(){
	scanf("%d",&n);
	a[(n+1)/2][(n+1)/2]=-1;
	dfs(1,1,0,1);
	for(int i=1;i<=n;++i){for(int j=1;j<=n;++j){if(a[i][j]!=-1)printf("%d ",a[i][j]);else printf("T ");}puts("");}
	return 0; 
} 
```


---

## 作者：lhc0707 (赞：0)

本篇题解不建议一开始做题就看。

观察到 $n$ 是个奇数，考虑从 $(1,1)$ 开始，向右走到头，然后右转，然后再右转，然后再走到头，然后再右转，直到填满为止。可以证明这种做法是正确的。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
typedef pair<int,int> pii;
inline void read(int &x)
{
    x=0;bool f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f^=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=(f?x:-x);
}
void write(int x){if(x<10){putchar(x+'0');return;}write(x/10);putchar(x%10+'0');}
inline void print(int x,char c){if(x<0){putchar('-');x=-x;}write(x);putchar(c);}
int n,vis[50][50],cnt;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0}; 
void go(int x,int y,int pdid)
{
	vis[x][y]=++cnt;
	int xx=x+dx[pdid],yy=y+dy[pdid];
	if(!vis[xx][yy])go(xx,yy,pdid);
	else
	{
		for(int i=0;i<4;i++)
		{
			xx=x+dx[i],yy=y+dy[i];
			if(!vis[xx][yy])
			{
				go(xx,yy,i);
				break;
			}
		}
	}
}
int main()
{
	memset(vis,0x3f3f3f3f,sizeof(vis));
	read(n);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)vis[i][j]=0;
	vis[(n+1)/2][(n+1)/2]=0x3f3f3f3f;
	go(1,1,3);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
		{
			if(vis[i][j]!=0x3f3f3f3f)print(vis[i][j],' ');
			else printf("T ");
		}
		putchar('\n');
	}
    return 0;
}
```

---

## 作者：xxboyxx (赞：0)

### 思路

两个格子相邻？结束在最中间？$N$ 为奇数？这么说就是从左上角开始走，到底或碰到原来的路线就转向，这样刚好可以在最中间结束。

这不就是蛇形方阵吗！再看看样例，果然对上了，感觉这道题比上一道题还简单一些。

### 注意

中间的位置应输出 `T`。

### 代码

就是蛇形方阵的代码，比较简单，这里就不写注释了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int g(int n,int x,int y)
{
	int tot=0;
	while (1)
	{
		if (x==1)
		{
			tot+=y;
			break;
		}
		if (y==n)
		{
			tot+=1*(n-1)+x;
			break;
		}
		if (x==n)
		{
			tot+=3*(n-1)+(2-y);
			break;
		}
		if (y==1)
		{
			tot+=4*(n-1)+(2-x);
			break;
		}
		tot+=4*(n-1);
		x--;
		y--;
		n-=2;
	}
	return tot;
}

int main()
{
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
		{
			if (i==n/2+1 && j==n/2+1)
				cout<<'T'<<' ';
			else
				cout<<g(n,i,j)<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：indream (赞：0)

## \[ABC335D] Loong and Takahashi 题解
[洛谷](https://www.luogu.com.cn/problem/AT_abc335_d) | [AtCoder](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc335_d)
### 思路
样例是个好东西。然后我一下想到了 [P5731](https://www.luogu.com.cn/problem/P5731)。只要把最后一个改成 `T` 即可。因为是 $n$ 是奇数，所以它一定在中间。

暴力模拟就行。

时间复杂度 $O(n^2)$。
### 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 50
using namespace std;
int ans[MAXN][MAXN],n,x,y;
char w='R';
int main(){
    cin>>n;
    
    for(int i=0;i<=n+1;++i)//边框
        ans[0][i]=-1;
    for(int i=0;i<=n+1;++i)
        ans[i][0]=-1;
    for(int i=0;i<=n+1;++i)
        ans[n+1][i]=-1;
    for(int i=0;i<=n+1;++i)
        ans[i][n+1]=-1;
    x=1;y=1;//初始化
    
    
    for(int i=1;i<n*n;++i){//模拟
        ans[x][y]=i;
        if(w=='R'){//右
            if(ans[x][y+1]!=0)//转向，移动会被下一个 if 语句识别
                w='D';
            else
                ++y;
        }
        if(w=='D'){//下
            if(ans[x+1][y]!=0)
                w='L';
            else
                ++x;
        }
        if(w=='L'){//左
            if(ans[x][y-1]!=0)
                w='U';
            else
                --y;
        }
        if(w=='U'){//上
            if(ans[x-1][y]!=0)//直接移动+转向
                ++y,w='R';
            else
                --x;
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(ans[i][j]!=0)
                cout<<ans[i][j]<<' ';
            else
                cout<<"T ";
        }
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：xz001 (赞：0)

- 首先题意就是让我们把人放在中心，然后让龙在矩阵中不交叉不留空地盘绕起来，我们可以让龙绕人转圈，可以发现这样问题就转化为了输出一个螺旋方阵，把中心点换成 ```T```。
- 代码如下：

```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define swap(a, b) 	a ^= b, b ^= a, a ^= b
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, a[105][105], cnt = 1, b[105][105];


signed main() {
    cin >> n;
    int x = 1, y = 1;
    a[x][y] = 1;
    while (cnt < n * n) {
    	while (y + 1 <= n && !a[x][y + 1]) a[x][ ++ y] = ++ cnt;
    	while (x + 1 <= n && !a[x + 1][y]) a[ ++ x][y] = ++ cnt;
    	while (y - 1 >= 1 && !a[x][y - 1]) a[x][ -- y] = ++ cnt;
    	while (x - 1 >= 1 && !a[x - 1][y]) a[ -- x][y] = ++ cnt;
	}
	
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				if (a[i][j] == n * n) cout << "T ";
				else cout << a[i][j] << ' ';
			}
			cout << endl;
		}
    return 0;
}

```

---

## 作者：huangzhixia (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/AT_abc335_d)**

## 题意

我们有一个数 $n$，从而需要得到一个如蛇一般卷起来的 $n \times n$ 的方阵，最中间的数字会被替换成 ```T```。如样例，一个 $5 \times 5$ 方阵，中间是 ```T```，也就是说我们有 $1$ 到 $n^2 -1$ 个数字。

## 思路

这道题 abc 上可以有多种蛇形的方式，这里我们就讲一下样例里的一种。

这里我们讲一个简单易懂的思路，用二维数组 $a$ 来记方阵，中间的数要替换成 ```T``` 我们暂时不考虑，先把最普通的蛇形方阵给记下来。

怎么记呢？

- 用一个变量 $t$，表示我们当前填了几个数字，每次 $t$ 小于 $n^2$ 时我们才能继续填下去。

- 还需要两个变量 $i$ 和 $j$，用来记我们当前要算的是 $a_{i,j}$。

把我们计算过程中需要的变量的定义搞定之后，接下来就要考虑建立蛇形方阵这个过程中往上，下，左，右生成数字的操作啦！结合样例，我们从点 $1$ 开始是往右边走，再往下走，然后往左走，接着往上走。最后就开始循环右，下，左，上，右，下，左，上……直到我们的变量 $t$ 等于 $n^2$ 了，我们就把所有的方阵填完啦！

下面是考虑右边的代码：

```cpp
while (a[i][j + 1] == 0 && j + 1 <= n) {
	j++;
	a[i][j] = ++t;
}
```

每次都往右考虑一个位置，但是你要保证往右考虑的位置必须没有超过 $n$。然后我们考虑的位置的值就是 $t+1$，这里的 $t$ 就有两个作用了，一是可以用来判断填数什么时候终止，二是可以用来填。

往下的代码也是同理：

```cpp
while (a[i + 1][j] == 0 && i + 1 <= n) {
	i++;
	a[i][j] = ++t;
}
```

往左：

```cpp
while (a[i][j - 1] == 0 && j - 1 >= 1) {
	j--;
	a[i][j] = ++t;
}
```

往上：

```cpp
while (a[i - 1][j] == 0 && i - 1 >= 1) {
	i--;
	a[i][j] = ++t;
}
```

最后，我们还有考虑一个问题，就是方阵搞定了，```T``` 放哪？很简单，在输出的时候判断以下，如果是中间就输出 ```T``` 就可以啦！

## AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int a[46][46];

int main(){
	scanf("%d", &n);
	int t = 1;
	a[1][1] = 1;
	int i = 1;
	int j = 1;
	while (t < n * n) {
		while (a[i][j + 1] == 0 && j + 1 <= n) {
			j++;
			a[i][j] = ++t;
		}
		while (a[i + 1][j] == 0 && i + 1 <= n) {
			i++;
			a[i][j] = ++t;
		}
		while (a[i][j - 1] == 0 && j - 1 >= 1) {
			j--;
			a[i][j] = ++t;
		}
		while (a[i - 1][j] == 0 && i - 1 >= 1) {
			i--;
			a[i][j] = ++t;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == n * n)
				printf("T ");
			else
				printf ("%d ", a[i][j]);
		}
		printf ("\n");
	}
}
```


---

## 作者：jess1ca1o0g3 (赞：0)

[Portal(AT)](https://atcoder.jp/contests/abc335/tasks/abc335_d)

[Portal(Luogu)](https://www.luogu.com.cn/problem/AT_abc335_d)

龙年元素好评！

## Part 1

赛时看了半天翻译，没看懂（

但是样例简单明了，就是[蛇形方阵](https://www.luogu.com.cn/problem/P5731)加强版（$3 \leq N \leq 45$），矩阵中央变成 `T`。

样例如下：

> ```
1 2 3 4 5
16 17 18 19 6
15 24 T 20 7
14 23 22 21 8
13 12 11 10 9
> ```

分类，上下左右四种，在草稿纸上画这个矩阵，分别标出每个数的下标，找规律。

于是就有了如下 $4$ 个函数：

```cpp
void cons1(int l,int r){ // 上横
    int u=l,v=l;
    for(int i=l;i<=r;i++){
        c[u][v]=d++;
        v++;
    }
}
void cons2(int l,int r){ // 右竖
    int u=l,v=r;
    for(int i=l;i<=r;i++){
        c[u][v]=d++;
        u++;
    }
}
void cons3(int l,int r){ // 下横
    int u=l+1,v=l;
    for(int i=l;i>=r;i--){
        c[u][v]=d++;
        v--;
    }
}
void cons4(int l,int r){ // 左竖
    int u=l,v=r-1;
    for(int i=l;i>=r;i--){
        c[u][v]=d++;
        u--;
    }
}
```

## Part 2

但这 $4$ 函数只能构造出一圈，想要打印出完整的矩阵还要找规律。

再次在草稿纸上画，标出每个函数工作的范围，于是就有了这样的代码：

```cpp
int o=1,p=2,q=0;
for(int i=0;i<n;i++){
    cons1(o,n-q);
    cons2(p,n-q);
    q++;
    cons3(n-q,o);
    cons4(n-q,p);
    o++,p++;
    }
```

## Part 3

接下来就是打印了。

矩阵中央的 `T` 可以特判。

于是打印代码如下：

```cpp
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        if(i==n/2+1&&j==n/2+1) printf("T ");
        else printf("%d ",c[i][j]);
    }
    printf("\n");
}
```

## Part 4

合并上述代码，得到最终代码：

```cpp
#include<cstdio>
int n,d=1;
int c[50][50];
namespace cons{
    void cons1(int l,int r){
        int u=l,v=l;
        for(int i=l;i<=r;i++){ // 上横
            c[u][v]=d++;
            v++;
        }
    }
    void cons2(int l,int r){ // 右竖
        int u=l,v=r;
        for(int i=l;i<=r;i++){
            c[u][v]=d++;
            u++;
        }
    }
    void cons3(int l,int r){ // 下横
        int u=l+1,v=l;
        for(int i=l;i>=r;i--){
            c[u][v]=d++;
            v--;
        }
    }
    void cons4(int l,int r){ // 左竖
        int u=l,v=r-1;
        for(int i=l;i>=r;i--){
            c[u][v]=d++;
            u--;
        }
    }
}
void work(){
    int o=1,p=2,q=0;
    for(int i=0;i<n;i++){
        cons::cons1(o,n-q);
        cons::cons2(p,n-q);
        q++;
        cons::cons3(n-q,o);
        cons::cons4(n-q,p);
        o++,p++;
    }
}
void print(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==n/2+1&&j==n/2+1) printf("T ");
            else printf("%d ",c[i][j]);
        }
        printf("\n");
    }
}
signed main(){
    scanf("%d",&n);
    work();
    print();
    return 0;
}
```

## Part 5

时间复杂度 $\mathcal{O}(n^2)$，空间复杂度 $\mathcal{O}(n^2)$。

[赛时AC](https://atcoder.jp/contests/abc335/submissions/49103079)

---

