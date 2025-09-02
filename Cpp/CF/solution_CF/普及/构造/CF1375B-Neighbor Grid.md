# Neighbor Grid

## 题目描述

### 题意：

给你一个 $n$ 行 $m$ 列的矩阵，要求你让这个矩阵是“完美”的。

“完美”的定义如下：

1. 若当前的格子里是一个正整数 $k$，那么与这个网格相邻（有公共边）的 $k$ 个格子也必须有一个正整数。

2. 若当前的格子里是 `0` ，那么不受上述的限制。

你可以对任意的一个格子加上 `1` ，次数不受限制。

对于每一组数据：

如果可以做到“完美”，请输出 `YES` 之后，将修改过的矩阵输出。

否则只输出一行 `NO` 。

## 说明/提示

$1\le T\le 5000$。

$2\le n,m\le 300$。

$n \times m \le 10^5$

对于每一个位置上的数字 $a_{(i,j)}$：
$0 \le a_{(i,j)} \le 10^9$。

------

+ Translate by black_trees

## 样例 #1

### 输入

```
5
3 4
0 0 0 0
0 1 0 0
0 0 0 0
2 2
3 0
0 0
2 2
0 0
0 0
2 3
0 0 0
0 4 0
4 4
0 0 0 0
0 2 0 1
0 0 0 0
0 0 0 0```

### 输出

```
YES
0 0 0 0
0 1 1 0
0 0 0 0
NO
YES
0 0
0 0
NO
YES
0 1 0 0
1 4 2 1
0 2 0 0
1 3 1 0```

# 题解

## 作者：sto__Liyhzh__orz (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1375B)

1. 当这个格子在角落，那么他身上的数字必定小于等于 $2$，否则无解。

2. 当这个格子在边上，那么他身上的数字必定小于等于 $3$，否则无解。

3. 当这个格子在中间，那么他身上的数字必定小于等于 $4$，否则无解。

4. 若上述条件皆满足，有解。

无解的情况在这里就不过多叙述了，直接输出 `NO`。

考虑有解：

先输出 `YES`。

可以设想一种保证合法的情况：

在角落填满 $2$，边上填满 $3$，格子填满 $4$。

这种情况保证合法。自证不难。

代码：

```cpp
#include<bits/stdc++.h>
#define I_LOVE_OI ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define qwq ;
#define I cout
#define AK <<
#define LL long long
#define NOI endl
using namespace std qwq 

const int MAXN=300+5 qwq 
int T,n,m,a[MAXN][MAXN] qwq 

void solve()
{
	cin>>n>>m qwq 
	bool flag=0 qwq 
	for(int i=1 qwq i<=n qwq i++)
	{
		for(int j=1 qwq j<=m qwq j++)
		{
			cin>>a[i][j] qwq 
			if((i==1 || i==n) && (j==1 || j==m) && a[i][j]>2) flag=1 qwq 
			if((i==1 || i==n) && (j>1 && j<m) && a[i][j]>3) flag=1 qwq 
			if((j==1 || j==m) && (i>1 && i<n) && a[i][j]>3) flag=1 qwq 
			if(j>1 && j<m && i>1 && i<n && a[i][j]>4) flag=1 qwq  
		}
	}
	if(flag)
	{
		I AK "NO" AK NOI qwq 
		return qwq 
	}
	I AK "YES" AK NOI qwq 
	for(int i=1 qwq i<=n qwq i++)
	{
		for(int j=1 qwq j<=m qwq j++)
		{
		    if((i==1 || i==n) && (j==1 || j==m)) a[i][j]=2 qwq 
			if((i==1 || i==n) && (j>1 && j<m)) a[i][j]=3 qwq 
			if((j==1 || j==m) && (i>1 && i<n)) a[i][j]=3 qwq 
			if(j>1 && j<m && i>1 && i<n) a[i][j]=4 qwq  
		}
	}
	for(int i=1 qwq i<=n qwq i++)
	{
		for(int j=1 qwq j<=m qwq j++)
		{
			int IOI=a[i][j] qwq
			I AK IOI AK ' ' qwq 
		}
		I AK NOI qwq 
	}
}

int main()
{
	I_LOVE_OI qwq 
	cin>>T qwq 
	while(T--)
	{
		solve() qwq 
	}
	return 0 qwq 
}
```

---

## 作者：Zhuluoan (赞：0)

## 题意简述

给你一个 $n$ 行 $m$ 列的矩阵，要求你让这个矩阵是“完美”的。

“完美”的定义如下：

1. 若当前的格子里是一个正整数 $k$，那么与这个网格相邻（有公共边）的 $k$ 个格子也必须有一个正整数。

2. 若当前的格子里是 $0$，那么不受上述的限制。

你可以对任意的一个格子加上 $1$，次数不受限制。

## 题目分析

首先，我们可以发现一个在角上的格子只有 $2$ 个格子与其相邻，在边上的只有 $3$ 个格子相邻，而在中间部分的有 $4$ 个格子相邻。如果有格子超出上述限制，因为题目规定只能增加，不能减少，所以必定无解。

接下来，我们考虑如何构造合法的矩阵。

我们考虑将整个矩阵填满，即将角上填 $2$，边上填 $3$，中间部分填 $4$，可以看出这种情况一定是“完美”的。

最后，我们考虑操作的过程是否合法。因为上述判无解的过程已经保证了给出矩阵的数一定小于等于矩阵填满后的数，所以不会出现减少的情况，故合法。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=310;
int T,n,m,a[N][N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
	    if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
	    x=(x<<1)+(x<<3)+ch-48;
	    ch=getchar();
	}
	return x*f;
}
inline void write(int x)
{
    if(x<0)
	{
    	putchar('-');
		x=-x;
	}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
void solve()
{
	n=read();
	m=read();
	bool flag=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			a[i][j]=read();
			if((i==1||i==n)&&(j==1||j==m)&&a[i][j]>2) flag=1;
			if((i==1||i==n)&&(j>1&&j<m)&&a[i][j]>3) flag=1;
			if((j==1||j==m)&&(i>1&&i<n)&&a[i][j]>3) flag=1;
			if(j>1&&j<m&&i>1&&i<n&&a[i][j]>4) flag=1; 
		}
	}
	if(flag)
	{
		printf("NO\n");
		return;
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
		    if((i==1||i==n)&&(j==1||j==m)) a[i][j]=2;
			if((i==1||i==n)&&(j>1&&j<m)) a[i][j]=3;
			if((j==1||j==m)&&(i>1&&i<n)) a[i][j]=3;
			if(j>1&&j<m&&i>1&&i<n) a[i][j]=4; 
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			write(a[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}
int main()
{
	T=read();
	while(T--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：yxy666 (赞：0)

因为题目叫我们构造一个矩阵，我们可以将其构造出一个极端的情况，也就是所有数字都最大的情况。

对于角上的元素，最多与两个元素互相接触，所以最大为二。对于边上的元素，最多与三个元素互相接触，所以最大为三。对于矩阵中间的元素，最多与四个元素互相接触，所以最大为四。如果有数字不符合上面的规则，那就是无解。

code :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=305;
int T,n,m,a[maxn][maxn],f[4][2]={{0,1},{-1,0},{0,-1},{1,0}};
bool flg;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	T=read();
	while(T--){
		n=read();m=read();flg=0;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=read();
		if(n==1||m==1){
			if(n==1){
				for(int j=1;j<=m;j++){
					if(j==1||j==m)if(a[1][j]>1){flg=1;break;}
					else if(a[1][j]>2){flg=1;break;}
				}
			}
			else {
				for(int i=1;i<=n;i++){
					if(i==1||i==n)if(a[i][1]>1){flg=1;break;}
					else if(a[i][1]>2){flg=1;break;}
				}
			}
		}
		else {
			for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if((i==1&&j==1)||(i==1&&j==m)||(i==n&&j==1)||(i==n&&j==m)){if(a[i][j]>2){flg=1;break;}}
				else if((i==1)||(i==n)||(j==1)||(j==m)){if(a[i][j]>3){flg=1;break;}}
				else if(a[i][j]>4){flg=1;break;}
			}
		}
		if(flg)printf("NO\n");
		else {
			if(n==1||m==1){
				if(n==1){
					for(int j=1;j<=m;j++){
						if(j==1||j==m)putchar('1');
						else putchar('2');
						if(j==m)putchar(10);
						else putchar(' ');
					}
				}
				else {
					for(int i=1;i<=n;i++){
						if(i==1||i==n)putchar('1');
						else putchar('2');
						putchar(10);
					}
				}
			}
			else {
				printf("YES\n");
				for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++){	
					if((i==1&&j==1)||(i==1&&j==m)||(i==n&&j==1)||(i==n&&j==m))putchar('2');
					else if((i==1)||(i==n)||(j==1)||(j==m))putchar('3');
					else putchar('4');
					if(j==m)putchar(10);else putchar(' ');
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：Andrewzdm (赞：0)

又是一道构造题。

我们可以先考虑如何判断答案为 $\texttt{NO}$。

角上的格子周围最多有 $2$ 个格子中的数大于 $0$，边上的格子周围最多有 $3$ 个格子中的数大于 $0$，中部的格子周围最多有 $4$ 个格子中的数大于 $0$。所以如果题目给出的 $a_{i,j}$ 大于上面所述的上限，那么自然无法构造，因为我们只能增加格子中的数。

接着构造的方法就出来了——让每个格子的数都达到其上限。换言之，把每个格子都填满。

这里的代码我将角、边和中部分开处理了。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn = 310;
int a[maxn][maxn];

void solve()
{
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> a[i][j];
	bool flag = true;
	//角
	if(a[1][1] > 2 || a[1][m] > 2 || a[n][1] > 2 || a[n][m] > 2)
		flag = false;
	//边
	for(int j = 2; j < m; j++)
		if(a[1][j] > 3 || a[n][j] > 3)
			flag = false;
	for(int i = 2; i < n; i++)
		if(a[i][1] > 3 || a[i][m] > 3)
			flag = false;
	//中部
	for(int i = 2; i < n; i++)
		for(int j = 2; j < m; j++)
			if(a[i][j] > 4)
				flag = false;
	if(!flag)
	{
		puts("NO");
		return;	
	}
	puts("YES");
	//和上边判断的过程同理
	a[1][1] = a[1][m] = a[n][1] = a[n][m] = 2;
	for(int j = 2; j < m; j++)
		a[1][j] = a[n][j] = 3;
	for(int i = 2; i < n; i++)
		a[i][1] = a[i][m] = 3;
	for(int i = 2; i < n; i++)
		for(int j = 2; j < m; j++)
			a[i][j] = 4;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}		 
	return;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：youngk (赞：0)

这道题目要求是给出一个网格矩阵，要求每个位置上的数表示的是其相邻的位置中数$>0$的个数，其中相邻是定义为是有边相邻才为相邻。经过数次在位置上$+1$问是否能构造出一个满足条件的可行解出来。

这个题目如果从每个不满足条件的位置出发取判断，则会变的非常复杂，但我们不妨可以考虑一下如果有位置上的数$>4$了，则一定不可以成立，其实再次发现每个位置上都有着其数值的上限，四个角为$2$，四条边除去角为$3$，其余部分为$4$，如果有不满足的则直接无法构造，如果需要构造的话直接变成这种全部都是极限的情况，必然可以从可以构造的条件中经过数次在位置上$+1$的操作得到一个可行解。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define endl '\n'
#define lowbit(x) x & -x
#define inf 0x3f3f3f3f
#define maxn 310

int x, n, m, t;
int a[maxn][maxn];
bool flag;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> t;
    while (t--) {
        flag = true;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
                if (a[i][j] > (i - 1 >= 1) + (j - 1 >= 1) + (i + 1 <= n) + (j + 1 <= m)) {
                    flag = false;
                }
                a[i][j] = (i - 1 >= 1) + (j - 1 >= 1) + (i + 1 <= n) + (j + 1 <= m);
            }
        }
        if (!flag) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cout << a[i][j] << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}
```


---

## 作者：wmy_goes_to_thu (赞：0)

易发现，在角上的元素最多能是 $2$，在边上的元素最多能是 $3$，在内部的最多是 $4$，所以我们可以构造一个矩阵：

$2~3 \dots 3~2$

$3~4 \dots 4~3$

$\dots \dots \dots$

$3~4 \dots 4~3$

$2~3 \dots 3~2$

每个点都尽可能多，所以如果不能得到这种方案，剩下的方案更得不到了，所以直接判断一下是否输入的元素要 $\leq$ 构造的矩阵的元素就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[305][305],f[305][305],n,m;
int valid(int x,int y)
{
	if(x>=1&&x<=n&&y>=1&&y<=m)return 1;
	return 0;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
			a[i][j]=valid(i-1,j)+valid(i+1,j)+valid(i,j-1)+valid(i,j+1);
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
			scanf("%d",&f[i][j]);
		int pp=1;
		for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
			if(f[i][j]>a[i][j])pp=0;
		if(pp==0)cout<<"NO"<<endl;
		else
		{
			cout<<"YES"<<endl;
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<m;j++)printf("%d ",a[i][j]);
				printf("%d\n",a[i][m]);
			}
		}
	}
	return 0;
}
```

---

## 作者：SpeedStar (赞：0)

#### 算法分析

对于这题的一种万能解法是，先判断四个角上的点是否不超过$2$，四条边上的点是否不超过$3$，以及内部的点是否不超过$4$；如果答案是$YES$的话，就令四个角上的点都为$2$，四条边上的点都为$3$，内部的点都为$4$。

#### C++代码

```cpp
#include <iostream>

using namespace std;

void solve() {
    int n, m;
	cin >> n >> m;
	int a[n][m];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> a[i][j];
		}
	}
	if (a[0][0] > 2 || a[n - 1][0] > 2 || a[0][m - 1] > 2 || a[n - 1][m - 1] > 2) {
		cout << "NO\n";
		return;
	}
	for (int j = 1; j < m - 1; ++j) {
		if (a[0][j] > 3) {
			cout << "NO\n";
			return;
		}
	}
	for (int j = 1; j < m - 1; ++j) {
		if (a[n - 1][j] > 3) {
			cout << "NO\n";
			return;
		}
	}
	for (int i = 1; i < n - 1; ++i) {
		if (a[i][0] > 3) {
			cout << "NO\n";
			return;
		}
	}
	for (int i = 1; i < n - 1; ++i) {
		if (a[i][m - 1] > 3) {
			cout << "NO\n";
			return;
		}
	}
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 1; j < m - 1; ++j) {
			if (a[i][j] > 4) {
				cout << "NO\n";
				return;
			}
		}
	}
	cout << "YES\n";
	a[0][0] = a[0][m - 1] = a[n - 1][0] = a[n - 1][m - 1] = 2;
	for (int j = 1; j < m - 1; ++j) a[0][j] = 3;
	for (int j = 1; j < m - 1; ++j) a[n - 1][j] = 3;
	for (int i = 1; i < n - 1; ++i) a[i][0] = 3;
	for (int i = 1; i < n - 1; ++i) a[i][m - 1] = 3;
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 1; j < m - 1; ++j) {
			a[i][j] = 4;
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cout << a[i][j] << " ";
		}
		cout << '\n';
	}
}

int main() {
    int t;
    cin >> t;

    while (t--) {
    	solve();
    }
    
    return 0;
}
```


---

## 作者：钓鱼王子 (赞：0)

由于只能变大，所以只用考虑最大的情况。

角落上的数最多为 $2$，边界上的数最多为 $3$，中间的数最多为 $4$。

只用判断每个位置是否合法即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,ans,a[402][402],b[402][402];
int main(){
	t=read();
	while(t--){
		bool ia=0;
		n=read();m=read();
		for(re int i=1;i<=n;++i){
			for(re int j=1;j<=m;++j){
				a[i][j]=0;b[i][j]=read();
			}
		}
		for(re int i=1;i<=n;++i){
			for(re int j=1;j<=m;++j){
				if((i!=1))++a[i][j];
				if(i^n)++a[i][j];
				if(j^1)++a[i][j];
				if(j^m)++a[i][j];
				if(b[i][j]>a[i][j])ia=1;
			}
		}
		if(ia)puts("NO");
		else{
			puts("YES");
			for(re int i=1;i<=n;++i){
			for(re int j=1;j<=m;++j){
				printf("%d ",a[i][j]);
			}puts("");
		}
		}
	}
}

```


---

