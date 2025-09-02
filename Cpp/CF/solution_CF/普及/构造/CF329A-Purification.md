# Purification

## 题目描述

You are an adventurer currently journeying inside an evil temple. After defeating a couple of weak zombies, you arrived at a square room consisting of tiles forming an $ n×n $ grid. The rows are numbered $ 1 $ through $ n $ from top to bottom, and the columns are numbered $ 1 $ through $ n $ from left to right. At the far side of the room lies a door locked with evil magical forces. The following inscriptions are written on the door:

 The cleaning of all evil will awaken the door!Being a very senior adventurer, you immediately realize what this means. You notice that every single cell in the grid are initially evil. You should purify all of these cells.

The only method of tile purification known to you is by casting the "Purification" spell. You cast this spell on a single tile — then, all cells that are located in the same row and all cells that are located in the same column as the selected tile become purified (including the selected tile)! It is allowed to purify a cell more than once.

You would like to purify all $ n×n $ cells while minimizing the number of times you cast the "Purification" spell. This sounds very easy, but you just noticed that some tiles are particularly more evil than the other tiles. You cannot cast the "Purification" spell on those particularly more evil tiles, not even after they have been purified. They can still be purified if a cell sharing the same row or the same column gets selected by the "Purification" spell.

Please find some way to purify all the cells with the minimum number of spells cast. Print -1 if there is no such way.

## 说明/提示

The first example is illustrated as follows. Purple tiles are evil tiles that have not yet been purified. Red tile is the tile on which "Purification" is cast. Yellow tiles are the tiles being purified as a result of the current "Purification" spell. Green tiles are tiles that have been purified previously.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329A/04b73f6bd6d4f5c1ba16b8072ebad28ccdfa62cc.png)In the second example, it is impossible to purify the cell located at row $ 1 $ and column $ 1 $ .

For the third example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329A/8ffcc7f3e4ed4b4242d89f880e88ffce0ed4e4ab.png)

## 样例 #1

### 输入

```
3
.E.
E.E
.E.
```

### 输出

```
1 1
2 2
3 3
```

## 样例 #2

### 输入

```
3
EEE
E..
E.E
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
EE.EE
E.EE.
E...E
.EE.E
EE.EE
```

### 输出

```
3 3
1 3
2 2
4 4
5 3```

# 题解

## 作者：Qerucy (赞：3)

翻译：你要净化一片大小为 $ n \times n $ 的土地。定义一次操作：你可以选一个不是 $ \texttt {E} $ 点的点，当你选择一个点时，与这个点的横坐标或纵坐标相等的点全被净化，每个点可以被净化多次，你要用最少的操作次数把这片土地净化完，输出所有你选择的点的坐标。

很简单，我们先判断有没有完全由 $ \texttt {E} $ 点组成的行和完全由 $ \texttt {E} $ 点组成的列，如果有，则不能满足要求，因为这一行与这一列相交的点无法被净化。

然后来想如何选择可净化的点。

以下有两种方案：

+ 如果没有完全由 $ \texttt {E} $ 点组成的行，那么我们可以每一行找一个可以净化的点来净化整片土地。

+ 如果没有完全由 $ \texttt {E} $ 点组成的列，那么我们可以每一列找一个可以净化的点来净化整片土地。

因此，操作的最少次数便是土地的边长，也就是 $n$。

最后再输出这些点的坐标即可。

代码：

```cpp
#include<cstdio>

using namespace std;

int n;
bool a[1010][1010];
char c;
bool fg;
int ans,sum;
bool vis[1010][1010];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf(" %c",&c);
			a[i][j]=(c=='E'?1:0);
		}
	}
	
	for(int i=1;i<=n;i++){
		fg=0;
		for(int j=1;j<=n;j++){
			if(!a[i][j]){
				fg=1;
			}
		}
		if(!fg) break;//貌似是并没用的操作
	}
	
	for(int i=1;i<=n;i++){
		fg=0;
		for(int j=1;j<=n;j++){
			if(!a[j][i]){
				fg=1;//貌似也是并没用的操作
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!a[i][j]){
				ans++;//累计列能满足要求的点
				break;
			}
		}
	}
	
	if(ans<n){//如果列不能满足要求，就求行能否满足要求
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(!a[j][i]){
					sum++;//累计行能满足要求的点
					break;
				}
			}
		}
	}
	
	if(ans>=n){//如果列能满足要求，就输出列的方案
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(!a[i][j]){
					printf("%d %d\n",i,j);
					break;
				}
			}
		}
	}
	
	else if(sum>=n){//如果列不能满足要求而行能满足要求，就输出行的方案
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(!a[j][i]){
					printf("%d %d\n",j,i);
					break;
				}
			}
		}
	}
	
	else printf("-1");//如果行和列都不能满足要求，就没有方案
	
	return 0;
}
```


---

## 作者：National_Studying (赞：1)

翻译翻译得很好，没有什么问题。

如果有全由 `.` 点组成的行和全由 `.` 组成的列，输出 `-1`。从样列 $2$ 就能很直观的看出。

接着分两种情况：

1. 选择一条非完全由 `.` 组成的行，每一行找一个可以净化的点来净化整片土地。
2. 选择一条非完全由 `.` 组成的列，每一列找一个可以净化的点来净化整片土地。

总操作数即土地的边长，为 $n$。

---

## 作者：Nuclear_Fish_cyq (赞：1)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF329A)

[CF 原题传送门](https://codeforces.com/problemset/problem/329/A)

[提交记录](https://www.luogu.com.cn/record/127748654)

## 题意简述

给定一个 $n\times n$ 的网格，你可以选取几个非 `E` 的点，把它们所在的行和列上的所有点都打上标记。要求使网格里的每一个点都被标记。求一个选取点的方案，如果没有输出 `-1`。

## 做法

首先，要使网格被完全覆盖,要么每一个行上都有选中的点，要么每一列上都有选中的点。那么我们就可以暴力枚举每一个行和每一列上有没有非 `E` 的点，如果存在全 `E` 的行就说明不可以使每一个行上都有选中的点，如果存在全 `E` 的列也同理。如果两种方案都不行就直接输出无解，退出。接下来就是对于每一行（列，取决于你选择的方案）进行枚举，找出这个行（列）里面一个非 `E` 的点，输出它的坐标，然后再继续枚举下一行（列）即可。

上代码。码风可能比较奇怪，不要在意：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n;
bool a[100][100], flagr[100], flagc[100], r = true, c = true; 
int main(){
//	std::ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++){
		scanf("\n");
		for(int j = 0; j < n; j++){
			char t = getchar();
			a[i][j] = (t == '.');
			flagr[i] = flagr[i] || a[i][j];
			flagc[j] = flagc[j] || a[i][j];
		}
	}
	for(int i = 0; i < n; i++){//选择方案
		r = r && flagr[i];
		c = c && flagc[i];
	}
	if(!r && !c){//无解
		cout << -1 << endl;
		return 0;
	}
	if(r){//在每一行里选点
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(a[i][j]){
					cout << i + 1 << " " << j + 1 << endl;//码风问题，习惯使用0~n-1，所以需要加1 
					break;
				}
			}
		}
	}
	else{//在每一列里选点
		for(int j = 0; j < n; j++){
			for(int i = 0; i < n; i++){
				if(a[i][j]){
					cout << i + 1 << " " << j + 1 << endl;//码风问题，习惯使用0~n-1，所以需要加1 
					break;
				}
			}
		}
	}
	return 0;
}

```


---

## 作者：All_Wrong_Answer (赞：0)

[luogu 题目传送门](https://www.luogu.com.cn/problem/CF329A)

[CF 题目传送门](https://codeforces.com/contest/329/problem/A)

## 题目大意：

有一张 $n \times n$ 的地图，你可以在一个非 ```E``` 点上放一个净化器，让与这个点同一行或和这个点同一列的点都被净化，问在那些点放净化器可以净化整张地图，如果无法净化整张地图，不可能完成则输出 ```-1```。

## 思路：

考虑在没有 ```E``` 点的情况下最少放多少个点可以让整张地图净化，明显在每一行或每一列上都放置一个净化器即可，共 $n$ 个。

那么加上对 ```E``` 的处理，当有一行全是 ```E``` 且还有一列全是 ```E``` 时，明显无论如何这一行和这一列的交叉点无法被净化，输出 ```-1```。

否则就在每一行或每一列中都找到一个非 ```E``` 点放置即可，只要每一行或每一列都有净化器，那么整个地图就一定被净化完毕了。

## 完整代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int x;
char m[105][105];
int main(){
	cin>>x;
	int f1=0,f2=0;
	for(int i=1;i<=x;i++){
		for(int j=1;j<=x;j++){
			cin>>m[i][j];
		}
	}
	
	for(int i=1;i<=x;i++){
		for(int j=1;j<=x;j++){
			
			if(m[i][j]=='.') f1=1;
		}
		if(f1==0){f1=2;break;} 
		f1=0;
	} 
	for(int i=1;i<=x;i++){
		for(int j=1;j<=x;j++){
			if(m[j][i]=='.') f2=1; 
		} 
		if(f2==0){f2=2;break;}
		f2=0;
	}
	if(f1==2&&f2==2){
		cout<<"-1\n";
		exit(0);
	} 
	//14到32行是判断无解。 
	
	int t=0;
	for(int i=1;i<=x;i++){
		for(int j=1;j<=x;j++){
			if(m[i][j]=='.'){
				t++;
				break;
			}
		}
	}
	if(t==x){
		for(int i=1;i<=x;i++){
		    for(int j=1;j<=x;j++){
	    		if(m[i][j]=='.'){
	    			cout<<i<<" "<<j<<"\n";
	    			break;
	    		}
	    	}
	    }
	    exit(0);
	}//在行上找答案 
	t=0;
	for(int i=1;i<=x;i++){
		for(int j=1;j<=x;j++){
			if(m[j][i]=='.'){
				t++;
				break;
			}
		}
	}
	if(t==x){
		for(int i=1;i<=x;i++){
	    	for(int j=1;j<=x;j++){
	    		if(m[j][i]=='.'){
		    		cout<<j<<" "<<i<<endl;
		    		break;
	    		}
	    	}
    	}
    	exit(0);
	}//在列上找答案 
	cout<<"-1\n";
	return 0;
}
```

时间复杂度为：$O(n^2)$。

[CF 上可过](https://codeforces.com/contest/329/submission/302190095)。

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路
	不难想到，向上下左右放射标记格子，想要标记完全部，必须要使每行每列都有一个可以进行操作的格子，也就是 `.`。反之，若任意一行且任意一列整一列都没有 `.`，那么肯定无解。所以开始时我们先判断是否有解（判断时若想让时间复杂度更优，可以记录每一行或每一列其中一个 `.` 的坐标，如果像我一样懒得开数组，那当我没说），若无解，输出 $-1$ 结束，否则，选择每一行操作一个或每一列操作一个（前提是可行），输出这一行或这一列的其中一个 `.` 的坐标即可。样例小，$N$ 的平方可过。

- ### 具体实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[105][105];
int main()
{
	scanf("%d",&n);
	bool l=1,h=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",a[i]+1);
	}
	for(int i=1;i<=n;i++)
	{
		l=1;
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]=='.')
			{
				l=0;
				break;
			}
		}
		if(l==1) break;
	}
	for(int i=1;i<=n;i++)
	{
		h=1;
		for(int j=1;j<=n;j++)
		{
			if(a[j][i]=='.')
			{
				h=0;
				break;
			}
		}
		if(h==1) break;
	}	
	if(h==1&&l==1) printf("-1");
	else{
		if(l==0)
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(a[i][j]=='.')
					{
						printf("%d %d\n",i,j);
						break;
					}
				}
			}			
		}
		else
		{
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
				{
					if(a[j][i]=='.')
					{
						printf("%d %d\n",j,i);
						break;
					}
				}
			}
		}

	}
}

---

## 作者：SpringFullGarden (赞：0)

## 题意

有一个 $n \times n$ 的网格。每次操作可以选一个不为 `E` 的点，这个点所处的行和列中的点会被覆盖，每个点可以被覆盖多次，求把网格覆盖完操作次数最少时选择的点的坐标，无法覆盖输出 `-1`。

## 思路

要使网格全部被覆盖，每行（列）都需要一个点不为 `E` 的点来覆盖，即每行（列）选择一个点输出。如果有一行（列）的点都为 `E`，则无法覆盖。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ui unsigned int
using namespace std;

inline int rd() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

int mp[105][105];
int a[105], b[105];

int main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
	int n = rd(), flag;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s;
		for(int j = 0; j < n; j++) 
			if(s[j] == '.') mp[i][j + 1] = 1, a[i] = j + 1, b[j + 1] = i;
	}
	flag = 1;
	for(int i = 1; i <= n; i++) if(!a[i]) flag = 0;
	if(flag) {
		for(int i = 1; i <= n; i++) cout << i << ' ' << a[i] << '\n';
		return 0;
	}
	flag = 1;
	for(int i = 1; i <= n; i++) if(!b[i]) flag = 0;
	if(flag) {
		for(int i = 1; i <= n; i++) cout << b[i] << ' ' << i << '\n';
		return 0;
	}
	cout << -1;
    return 0;
}
```



---

## 作者：jasonshen_ (赞：0)

## 思路

你要净化一片大小为 $ n \times n $ 的土地。定义一次操作：你可以选一个不是 $ \texttt {E} $ 点的点，当你选择一个点时，与这个点的横坐标或纵坐标相等的点全被净化，每个点可以被净化多次，你要用最少的操作次数把这片土地净化完，输出所有你选择的点的坐标。

这里只需要判断两个不同的点组成的列是否相交即可。如果有，则不能满足要求，因为两条线相交的交点无法被净化。最后再输出这些点的坐标即可。


## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	char arr[109][109] ;
	int n;
	vector<pair<int,int> >v;
	cin>>n;
	for(int i=1; i<=n; i++)for(int j=1; j<=n; j++)cin>>arr[i][j];

	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) if(arr[i][j]=='.') {
				v.push_back({i,j});
				break ;
			}
	if(v.size()==n) {
		for(auto i : v)cout<<i.first<<" "<<i.second<<endl;
		return 0 ;
	}
	v.clear();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) if(arr[j][i]=='.') {
				v.push_back({j,i});
				break ;
			}

	if(v.size()==n) {
		for(auto i : v)cout<<i.first<<" "<<i.second<<endl;
		return 0 ;
	}
	cout<<-1;
}


```



---

