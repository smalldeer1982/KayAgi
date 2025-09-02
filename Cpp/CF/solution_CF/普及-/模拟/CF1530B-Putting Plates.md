# Putting Plates

## 题目描述

有一张桌子，分为 $h$ 行 $w$ 列。

桌子**边缘**上的某一行某一列可以放一个盘子（也可以不放）。但是，一个盘子的上面、下面、左面、右面、左上、右上、左下、右下都不能有盘子。

问题来了：这个桌子，放盘子最多的方案是什么？请输出这个方案。当然，答案不止一种，你也不用全部输出，输出任意一个，即可。

## 样例 #1

### 输入

```
3
3 5
4 4
5 6```

### 输出

```
10101
00000
10101

0100
0001
1000
0010

010101
000000
100001
000000
101010```

# 题解

## 作者：zct_sky (赞：3)

### Solution:
-----
第 $1$ 行和第 $h$ 行奇数列全放盘子，这样这两行的盘子数就是最多的了。

再看第 $1$ 列和第 $w$ 列，如果要使这两列盘子数最多，那么只能从第 $2$ 行到第 $h-2$ 行的偶数行全放盘子，这样就能使桌子边缘放的盘子总数最多。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){//快读 
	int x=0,y=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x*y;
}
inline void write(ll x){//快输 
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int h,w,t;
int main(){
    t=read();
    for(int t1=0;t1<t;t1++){
    	h=read(),w=read();
		bool f[21][21]={};//清零数组 
		
		for(int i=0;i<w;i++)//第1行和第h行奇数列全放盘子
		    if(!(i%2))f[0][i]=f[h-1][i]=1;
		    
		for(int i=2;i<h-2;i++)//第1列和第w列的第2行到第h-2行的偶数行全放盘子
		    if(!(i%2))f[i][0]=f[i][w-1]=1;
		for(int i=0;i<h;i++,puts(""))
		    for(int j=0;j<w;j++)
		        write(f[i][j]);
		puts("");
	}
    return 0;
}
```

---

## 作者：Orin (赞：2)

[CF1530B](https://www.luogu.com.cn/problem/CF1530B)

本方法简单易懂不易出错。

------------

方法：上下两行奇数位全填，左右两列从 $3$ 到 $h-2$ 奇数位全填。

如果你觉得这不一定最优，那你的疑惑就是在 $4$ 个角上会不会少填。但这不会，以右上角为例。第一行要么在倒数第一个位置填，要么在倒数第二个位置填。但无论在哪里填，右面一列的第一个和第二个都填不了，所以只能从第三个位置开始填。而且这不会使得答案更劣，因为如果这样填使得右下角少了 $1$ 个，那把右下角的那 $1$ 个填上就会使右上角少 $1$ 个。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
long long t,n,m,a[30][30];
int main(){
	long long i,j,u,v;
	cin>>t;
	while(t--){
		cin>>n>>m;
		memset(a,0,sizeof(a));
		for(i=1;i<=m;i++){
			if(i&1) a[1][i]=a[n][i]=1;
		}
		for(i=3;i<=n-2;i++){
			if(i&1) a[i][1]=a[i][m]=1;
		}
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++){
				cout<<a[i][j];
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：SUPERXWX (赞：1)

个人认为该题是一道暴力枚举题。因为题目数据小的原因，暴力枚举是可行的，先将左上角放一个盘子，再逐个处理该位置能不能放盘子。

顺序的话，我是按照

- 左上，上，右，右下。

- 左上，左，下，右下。

这样判断下去，就可以得到答案。

## 最后附上代码：

~~忽略又臭又长的判断~~
```cpp
#include<string.h>
#include <iostream>　　　　
using namespace std;
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int a,b,n,s[30][30];
	cin>>n;
	for(int i=1;i<=n;i++){	
		memset(s,0,sizeof(s)); 
		cin>>b>>a;
		s[1][1]=a;//初始化给左上角放上盘子。
		for(int j=1;j<=a;j++){
			if(s[1][j-1]==0)
			s[1][j]=1;
		}
		for(int j=1;j<=b;j++){
			if(s[j-1][1]==0)
			s[j][1]=1;
		}
		for(int j=1;j<=a;j++){
			if(s[b-1][j-1]==0&&s[b-1][j]==0&&s[b-1][j+1]==0&&s[b][j-1]==0&&s[b][j+1]==0&&s[b+1][j-1]==0&&s[b+1][j]==0&&s[b+1][j+1]==0)//左上，上，右，右下。
			s[b][j]=1;
		}
		for(int j=1;j<=b;j++){
			if(s[j-1][a-1]==0&&s[j-1][a]==0&&s[j-1][a+1]==0&&s[j][a-1]==0&&s[j][a+1]==0&&s[j+1][a-1]==0&&s[j+1][a]==0&&s[j+1][a+1]==0)//- 左上，左，下，右下。
			s[j][a]=1;
		}
        //这样分两步操作的同时也防止了右下角重复的问题。
		for(int j=1;j<=b;j++){
			for(int k=1;k<=a;k++){
				cout<<s[j][k];
			}
			cout<<endl;
		}
}
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}

```
制作不易，望管理大大通过！

---

## 作者：__int127 (赞：0)

## CF1530B Putting Plates 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF1530B)

### 题目大意

本题有多组数据。

给定一个 $h$ 行 $w$ 列的方格 $a$，请你在上面放盘子，只允许在边缘放，对于已经放过盘子的 $a_{i,j}$，$a_{i-1,j},a_{i-1,j+1},a_{i,j+1},a_{i+1,j+1},a_{i+1,j},a_{i+1,j-1},a_{i,j-1},a_{i-1,j-1}$（即上、下、左、右、左上、右上、左下、右下）不允许再放盘子，输出任意一种盘子最多的情况（`1` 表示盘子，`0` 表示空位）。

### 思路

这题可以用暴力来解，打两层 for 循环就可以了，核心伪代码如下：

```cpp
for (遍历 a 数组的行：i 从 1 到 n){
	for (遍历 a 数组的列：j 从 1 到 m){
		if (是边缘且可以放){
			放入盘子并标记周围点
		}
	}
}
// 注：这里由于习惯将 h 和 w 变成了 n 和 m，本题解后面的代码也一样。
```

不管如何放盘子，其实我们都可以在 $a_{1,1}$ 处先放一个盘子，后面放盘子时再考虑是否可以放，这样总是最优解，把上面的伪代码转为核心代码如下：

```cpp
for (int i = 1; i <= n; i++){
	for (int j = 1; j <= m; j++){
		if (a[i][j] != 2 && (i == 1 || i == n || j == 1 || j == m)){
			a[i][j] = 1, a[i - 1][j] = a[i - 1][j + 1] = a[i][j + 1] = a[i + 1][j + 1] = a[i + 1][j] = a[i + 1][j - 1] = a[i][j - 1] = a[i - 1][j - 1] = 2;
		}
	}
}
```

那么这个代码就出来了。

### 代码+注释

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, a[25][25];
int main(){
	cin >> t;// 题组数据
	while (t--){
		cin >> n >> m;// 读入 n 行 m 列
		a[1][1] = 1, a[1][2] = 2, a[2][1] = 2, a[2][2] = 2;
		for (int i = 1; i <= n; i++){// 遍历 a 数组的行
			for (int j = 1; j <= m; j++){// 遍历 a 数组的列
				if (a[i][j] != 2 && (i == 1 || i == n || j == 1 || j == m)){// 如果为边缘且 a[i][j] 没有被标记过，就放盘子
					a[i][j] = 1, a[i - 1][j] = a[i - 1][j + 1] = a[i][j + 1] = a[i + 1][j + 1] = a[i + 1][j] = a[i + 1][j - 1] = a[i][j - 1] = a[i - 1][j - 1] = 2;
                    // 上为标记盘子的位置和其周围
				}
			} 
		}
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				cout << a[i][j] % 2;
			}
			cout << "\n";
		}
		cout << "\n";// 每个数据需要换行
		memset(a, 0, sizeof(a));// 易错点！！！记得清空数组
	}
	return 0;
}
```
### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：dthythxth_Huge_Brain (赞：0)

## 题目分析

~~这题有点像扫雷~~，我们可以将这张桌子看作是一个二维数组，然后遍历左上角到右下角每个格子，当这个格子在二维数组的边缘时，判断 $8$ 个邻格上是否放过盘子，一旦有一个邻格上已经有盘子了，就输出 $0$；若邻格都没有盘子，即输出 $1$。

## 部分代码

```cpp
memset(a,0,sizeof(a));//多测不清空，亲人 t-1 行泪
for(int i=1;i<=h;i++){
	for(int j=1;j<=w;j++){
		if((j==1||i==1||j==w||i==h/*判断是否在边缘*/)&&a[i-1][j]==0/*上*/&&a[i+1][j]==0/*下*/&&a[i][j-1]==0/*左*/&&a[i][j+1]==0/*右*/&&a[i-1][j-1]==0/*左上*/&&a[i+1][j-1]==0/*左下*/&&a[i-1][j+1]==0/*右上*/&&a[i+1][j+1]==0/*右下*/){
			cout<<1;
			a[i][j]=1;//此格放上了盘子
		}
		else cout<<0;
	}
	cout<<"\n";
}
cout<<"\n";//注意最后还要换行
```



---

## 作者：ssSSSss_sunhaojia (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF1530B)
# 思路：
根据题意，我们要使得能放的盘子的数量最多，考虑在奇数行或奇数列的位置放置盘子，因为对于任意一段从 $1$ 开始的连续的自然数，奇数永远不会比偶数少。

对于桌子边缘的上下两条边，我们只需要从 $1$ 到 $w$ 枚举奇数，对于其中的每个奇数 $i$，在 $1$ 行 $i$ 列以及 $h$ 行 $i$ 列的位置放置盘子。

对于桌子边缘的左右两条边，因为已经在角落放置了盘子，所以我们要从 $3$ 到 $h-2$ 枚举奇数，对于其中的每个奇数 $i$，在 $i$ 行 $1$ 列以及 $i$ 行 $w$ 列的位置放置盘子。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL T, h, w, f[30][30]; 
int main(){
	IOS;
	cin >> T;  
	while(T --) {
		cin >> h >> w; //输入
		for(re int i = 1; i <= h; i ++)
			for(re int j = 1; j <= w; j ++)
				f[i][j] = 0; //清空
		for(re int i = 1; i <= w; i += 2)
			f[1][i] = f[h][i] = 1; //桌子边缘的上下两条边
		for(re int i = 3; i <= h - 2; i += 2)
			f[i][1] = f[i][w] = 1; //桌子边缘的左右两条边
		for(re int i = 1; i <= h; i ++, cout << "\n")
			for(re int j = 1; j <= w; j ++)
				cout << f[i][j]; //输出
		cout << "\n"; 
	}
	return 0;
}

```

---

## 作者：lrmlrm_ (赞：0)

## 题意

一张桌子有 $h$ 行 $w$ 列，在边缘放棋子，在已经放的棋子周围（上、下、左、右、左上、左下、右上、右下）不能再放棋子。要求给出一种摆法使得桌子上的棋子数量最多。

边缘：指第 $1$ 行，第 $h$ 行，第 $1$ 列，第 $w$ 列。

## 题意

在边缘放棋子，我们就先横着放（在第 $1$ 行和第 $h$ 列放）。那根据题目要求，在第 $1$ 行第 $1$ 列放了一个，接下来第 $1$ 行只能放到第 $3$ 列的地方。概括起来就是：在第 $1$ 行和第 $h$ 行的奇数列放棋子。

横着放完，就应该竖着放。竖着并没有那么简单，我们先看几个例子。下图是横着放完后的图。
![](https://cdn.luogu.com.cn/upload/image_hosting/kbti798d.png?x-oss-process=image/resize,m_lfit,h_600,w_1000)

竖着放，不难放出下图的样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/kpsqjxx1.png?x-oss-process=image/resize,m_lfit,h_600,w_1000)

不难看出要在第 $1$ 列和第 $w$ 列的奇数行的位置放棋子，但是一个例子并不能说明一切，我们再举一个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/xr267mhp.png?x-oss-process=image/resize,m_lfit,h_600,w_1000)

为了方便，我们从上面开始竖着放：

![](https://cdn.luogu.com.cn/upload/image_hosting/5z5ljel4.png?x-oss-process=image/resize,m_lfit,h_500,w_1000)

那么不难发现，竖着放要在第 $1$ 和第 $w$ 列，第 $3$ 行到第 $h-2$ 行中的奇数行上放棋子。（如果理解不了可以配合图理解）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,h,w;
int p[30][30];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&h,&w);
		for(int i=1;i<=h;i++)
			for(int j=1;j<=w;j++)p[i][j]=0;
		for(int i=1;i<=w;i+=2)p[1][i]=1,p[h][i]=1;
		for(int i=3;i<=h-2;i+=2)p[i][1]=1,p[i][w]=1;
		for(int i=1;i<=h;i++){
			for(int j=1;j<=w;j++)
				printf("%d",p[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	return 0;
} 
```

---

## 作者：___cjy__ (赞：0)

# CF1530B Putting Plates 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1530B)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf1530b)

橙题，但是不如红题难度。

### 题目大意：

在一个大小为 $h \times w$ 的矩阵的边缘上放盘子，但是每一个盘子的周围 $8$ 个格子都不能有盘子。求可以放最多盘子的方案。

### 正文：

显然，我们可以直接对整个矩阵进行一次遍历，~~因为数据实在是太蒻了~~，紧接着对遍历到的每个位置进行一次判断，来确定是否可以放盘子。

判断盘子当前位置是否可以放盘子需要以下条件：

- 该位置在桌子边界。

- 该位置周围 $8$ 个格子没有放过盘子。

若当位置满足以上条件时，说明盘子可以放在此处。

### AC Code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define int long long
#define N 25
#define INF 0xffffffff
#define bug printf("..........bug!..........\n");
using namespace std;
int T, n, m;
int table[N][N];
bool ok(int x, int y){
	if(!((x == 1 || x == n) || (y == 1 || y == m))) return 0;//盘子只能放在桌子边界 
	if(table[x-1][y-1] == 1 || table[x-1][y] == 1 || table[x-1][y+1] == 1 ||
	   table[x][y-1]   == 1 || table[x][y]   == 1 || table[x][y+1]   == 1 ||
	   table[x+1][y-1] == 1 || table[x+1][y] == 1 || table[x+1][y+1] == 1) //判断周围是否已有盘子 
	   	return 0;
	else return 1;
}
void add(int x, int y){
	table[x][y] = 1;
}
signed main(){
	scanf("%lld", &T);
	while(T--){
		memset(table, 0, sizeof(table));//多组数据，需要初始化 
		scanf("%lld %lld", &n, &m);
		for(int i=1; i<=n; i++){//顺序遍历矩阵，放盘子 
			for(int j=1; j<=m; j++){
				if(ok(i, j))
					add(i, j);
		for(int i=1; i<=n; i++){//输出 
			for(int j=1; j<=m; j++){
				printf("%lld", table[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：_cpp (赞：0)

今天刷题时，无意间见到了这题，就顺便把它刷了。在题解区逛了一圈，发现各位神犇们都在推柿子，找规律。本蒟蒻是一点都看不懂。所以，我看了看数据，发现用模拟也可以解决这题。
### 思路：
我们可以通过读题目发现：如果有多组答案，那只要输出任意一种即可。因此，我们直接从左上角开始放盘子。每放一个盘子，就把它周围的八个格子占领。只要在边缘发现没被占领的格子（即为 $0$ ），就在这里放一个盘子，再把他周围八个格子占领。重复上述步骤，直到没有格子可放为止。然后输出整个数组。注意：我这里占领的地方的话是用负数的方式表现的，而题目要求没盘子的地方输出 $0$，所以输出时特判一下就行了。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int i,t,j,n,m,a[102][102];
void zhanling(int x,int y) //占领周围八个格子
{
	if(x-1>=1&&y-1>=1) a[x-1][y-1]--;
	if(x-1>=1) a[x-1][y]--;
	if(x+1<=n&&y-1>=1) a[x+1][y-1]--;
	if(x+1<=n) a[x+1][y]--;
	if(y+1<=m&&x+1<=n) a[x+1][y+1]--;
	if(y+1<=m) a[x][y+1]--;
	if(x-1>=1&&y+1<=m) a[x-1][y+1]--;
	if(y-1>=1) a[x][y-1]--;
}
bool pd(int x,int y) //判断周围八个格子有没有其它盘子
{
	if(a[x+1][y]!=1&&a[x][y+1]!=1&&a[x-1][y]!=1&&a[x][y-1]!=1&&a[x+1][y+1]!=1&&a[x+1][y-1]!=1&&a[x-1][y+1]!=1&&a[x-1][y-1]!=1) return 1;
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);  //去同步，加速cin，cout
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a)); //因为是多组数据，记得初始化
		cin>>n>>m;
		a[1][1]=1; //左上角开始
		zhanling(1,1);
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++){
				if(!(i==1||j==1||i==n||j==m)) continue; ///如果不是边缘就跳过
				if(a[i][j]==0&&pd(i,j)){ //判断当前位置有没有被占领，以及周围八个位置有有没盘子
					a[i][j]=1;//放置盘子
					zhanling(i,j);
                               }
			}
		for(i=1;i<=n;i++){
			for(j=1;j<=m;j++) 
				if(a[i][j]<0)cout<<"0";  //题目要求空着的输出0
				else cout<<a[i][j];
			cout<<'\n';
		}
		cout<<'\n';
	}
    return 0;
}
```


---

## 作者：hyc1026 (赞：0)

### 题意：

在一个 $n$ 行 $m$ 列的网格的边缘上放盘子，问最多能放几个，输出此时的方法。但盘子的周围八个格都不能放盘子。

边缘上，也就是第 $1$ 行，第 $n$ 行，第 $1$ 列，第 $m$ 列的统称。

### 思考：

最好的方法是将第 $1$ 行的奇数列和第 $n$ 行的奇数列填满，然后将第 $1$ 列和第 $m$ 列的奇数行填满。但此时要注意，如果 $n$ 为偶数，则第 $1$ 列和第 $m$ 列的倒数第二行是不能填的，原因是最后一行已经填上了。

样例解释：

当 $n=6,m=6$ 时：

首先将第 $1$ 行和第 $n$ 行的奇数列填满（填的是 $1$）。

| $1$ | $\ \ $ | $1$ | $\ \ $ | $1$ | $\ \ $ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $\ $ |  |  |  |  |  |
| $\ $ |  |  |  |  |  |
| $\ $ |  |  |  |  |  |
| $\ $ |  |  |  |  |  |
| $1$ |  | $1$ |  | $1$ |  |

然后将第 $1$ 列和第 $m$ 列的奇数行填满（填的是 $2$）。

| $1$ | $\ \ $ | $1$ | $\ \ $ | $1$ | $\ \ $ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $\ $ |  |  |  |  |  |
| $2$ |  |  |  |  | $2$ |
| $\ $ |  |  |  |  |  |
| $2$ |  |  |  |  | $2$ |
| $1$ |  | $1$ |  | $1$ |  |

但是由于 $n$ 为偶数，所以要删掉倒数第二行的盘子。

| $1$ | $\ \ $ | $1$ | $\ \ $ | $1$ | $\ \ $ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $\ $ |  |  |  |  |  |
| $2$ |  |  |  |  | $2$ |
| $\ $ |  |  |  |  |  |
| $\ $ |  |  |  |  | $\ $ |
| $1$ |  | $1$ |  | $1$ |  |

至此，我们完成了放盘子的所有操作。

### AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int flag[110][110];

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        memset(flag,0,sizeof(flag));
        int n,m;
        cin >> n >> m;
        for(int i=1; i<=m; i+=2) flag[1][i] = 1;
        for(int i=1; i<=m; i+=2) flag[n][i] = 1;
        for(int i=3; i<=n-2; i+=2) flag[i][1] = flag[i][m] = 1;
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=m; j++) cout << flag[i][j];
            cout << endl;
        }
        cout << endl;
    }
}
```

---

## 作者：CodingOIer (赞：0)

## CF1530B Putting Plates 题解

### 思路分析

这道题的题意是在这张 $n \times m$ 的桌子的边缘上放盘子，但是盘子的周围一圈都不能放其他盘子。

首先可以在第一行和最后一行的奇数列放盘子，这样无论 $m$ 为奇数还是偶数，都是最优的。

Code:

```cpp
for (int i = 1; i <= m; i++)
{
    if (i % 2 == 1)
    {
        printf("1");
    }
    else
    {
        printf("0");
    }
}
```

中间的位置便是奇数行在左右的边缘放盘子，偶数行则全不放。

但是如果 $n$ 为偶数的话，最后两行都会放上，所以只循环到第 $n - 2$ 行，然后给第 $n - 1$ 行不放，最后的第 $n$ 行便可以正常放置了。

Code:

```cpp
for (int i = 2; i <= n - 2; i++)
{
    if (i % 2 == 1)
    {
        printf("1");
    }
    else
    {
        printf("0");
    }
    for (int j = 1; j <= m - 2; j++)
    {
        printf("0");
    }
    if (i % 2 == 1)
    {
        printf("1");
    }
    else
    {
        printf("0");
    }
    printf("\n");
}
for (int j = 1; j <= m; j++)
{
    printf("0");
}
```

### 代码实现

讲上述代码整合，并加入换行即可。

```cpp
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define debug printf("Debug\n")
typedef long long ll;
const int inf = 0x3f3f3f3f;
int t;
int n, m;
void solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        if (i % 2 == 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
    for (int i = 2; i <= n - 2; i++)
    {
        if (i % 2 == 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
        for (int j = 1; j <= m - 2; j++)
        {
            printf("0");
        }
        if (i % 2 == 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
        printf("\n");
    }
    for (int j = 1; j <= m; j++)
    {
        printf("0");
    }
    printf("\n");
    for (int i = 1; i <= m; i++)
    {
        if (i % 2 == 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
    printf("\n");
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、题目翻译

[在这里！](https://www.luogu.com.cn/paste/44w9w56k)

### 二、思路

以 $6$ 行 $6$ 列，即 $h=6,w=6$ 为例。

首先，先把上边缘从左到右填满盘子，再把左边缘从上到下填满盘子，就像这样：

[![W3w6nx.png](https://z3.ax1x.com/2021/07/18/W3w6nx.png)](https://imgtu.com/i/W3w6nx)

接着，我们再填充右边缘。

但是，从第几行开始填充呢？

我们可以发现，无论 $w=5$ 或是 $w=6$，一定是从第三行开始填充。

填成了这样：

[![W3wojI.png](https://z3.ax1x.com/2021/07/18/W3wojI.png)](https://imgtu.com/i/W3wojI)

接着填充下边缘。

我们可以发现，此时，一定是从第三列开始填充，且填充的列数不能大于 $w-2$。

因此，我们就可以得出代码。

### 三、完整代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t,h,w;
int main()
{
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%d%d",&h,&w);
		bool graph[21][21];
		memset(graph,0,sizeof(graph));
		graph[1][1]=true;
		for(int y=3;y<=w;y+=2)//填充上边缘。
		{
			graph[1][y]=true;
		}
		for(int x=3;x<=h;x+=2)//填充左边缘。
		{
			graph[x][1]=true;
		}
		for(int x=3;x<=h;x+=2)//填充右边缘。
		{
			graph[x][w]=true;
		}
		for(int y=3;y<=w-2;y+=2)//填充下边缘。
		{
			graph[h][y]=true;
		}
		for(int x=1;x<=h;x++)//输出。
		{
			for(int y=1;y<=w;y++)
			{
				printf("%d",graph[x][y]?1:0);
			}
			printf("\n");
		}
		if(i!=t)//空行。
		{
			printf("\n");
		}
	}
	return 0;//完结撒花！
}

```

### 四、总结

可以看见，源代码中没有用来判断这个地方能不能放盘子的代码。

对于这种有多个答案的题目，有些时候是有多个答案的。但是，毒瘤出题人一般不会给你看出规律，典型代表就是[【LGR-085】洛谷 5 月月赛 & MCOI Round 5 Div.2 B 题：魔仙](https://www.luogu.com.cn/problem/P7567?contestId=30514)。因此，遇到这些题，好好想想有没有规律。

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

