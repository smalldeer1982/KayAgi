# [ABC337D] Cheating Gomoku Narabe

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc337/tasks/abc337_d

$ H $ 行 $ W $ 列のグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,\ j) $ と呼びます。

各マスには `o` 、`x` 、`.` のうちいずれかの文字が書かれています。 各マスに書かれた文字は $ H $ 個の長さ $ W $ の文字列 $ S_1,\ S_2,\ \ldots,\ S_H $ で表され、 マス $ (i,\ j) $ に書かれた文字は、文字列 $ S_i $ の $ j $ 文字目と一致します。

このグリッドに対して、下記の操作を $ 0 $ 回以上好きな回数だけ繰り返します。

- `.` が書かれているマスを $ 1 $ 個選び、そのマスに書かれた文字を `o` に変更する。
 
その結果、縦方向または横方向に連続した $ K $ 個のマスであってそれらに書かれた文字がすべて `o` であるようなものが存在する（ すなわち、下記の $ 2 $ つの条件のうち**少なくとも一方**を満たす）ようにすることが可能かを判定し、可能な場合はそのために行う操作回数の最小値を出力してください。

- $ 1\ \leq\ i\ \leq\ H $ かつ $ 1\ \leq\ j\ \leq\ W-K+1 $ を満たす整数の組 $ (i,\ j) $ であって、マス $ (i,\ j),\ (i,\ j+1),\ \ldots,\ (i,\ j+K-1) $ に書かれた文字が `o` であるものが存在する。
- $ 1\ \leq\ i\ \leq\ H-K+1 $ かつ $ 1\ \leq\ j\ \leq\ W $ を満たす整数の組 $ (i,\ j) $ であって、マス $ (i,\ j),\ (i+1,\ j),\ \ldots,\ (i+K-1,\ j) $ に書かれた文字が `o` であるものが存在する。

## 说明/提示

### 制約

- $ H,\ W,\ K $ は整数
- $ 1\ \leq\ H $
- $ 1\ \leq\ W $
- $ H\ \times\ W\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ \max\lbrace\ H,\ W\ \rbrace $
- $ S_i $ は `o` 、`x` 、`.` のみからなる長さ $ W $ の文字列
 
### Sample Explanation 1

操作を $ 2 $ 回行って、例えばマス $ (2,\ 1) $ とマス $ (2,\ 2) $ に書かれた文字をそれぞれ `o` に変更することで問題文中の条件を満たすことができ、これが最小の操作回数です。

### Sample Explanation 2

操作を一度も行わなくても問題文中の条件を満たします。

### Sample Explanation 3

問題文中の条件を満たすことは不可能なので、`-1` を出力します。

## 样例 #1

### 输入

```
3 4 3
xo.x
..o.
xx.o```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2 3
.o
.o
.o
.o```

### 输出

```
0```

## 样例 #3

### 输入

```
3 3 3
x..
..x
.x.```

### 输出

```
-1```

## 样例 #4

### 输入

```
10 12 6
......xo.o..
x...x.....o.
x...........
..o...x.....
.....oo.....
o.........x.
ox.oox.xx..x
....o...oox.
..o.....x.x.
...o........```

### 输出

```
3```

# 题解

## 作者：_xxxxx_ (赞：5)

### 题意

给出一个 $n \times m$ 的字符矩阵，你可以添加 `o` 的个数，使得矩阵中的 `o` 横连或竖连有 $k$ 个或以上。其中，

- `.` 表示这个位置可以放 `o`，操作后这个位置就变为 `o`。
- `x` 表示这个位置不能放 `o`，不能对这个位置进行操作。

问最少要进行几次操作，才能有 $k$ 个连起来的 `o`。

### 分析

首先要解决的是数组的存储，没有给出 $n$ 和 $m$ 的实际大小，但是给出了 $nm \le 2 \times 10^5$。因此我们可以用一个字符串数组来存，或者也可以用 `vector` 来存。

没思路就先打个暴力吧。

对于每一个可以向后连 $k$ 个点，都进行一次循环，没有 `x` 就对 `.` 的个数取最小值。时间复杂度 $O(nmk)$，会有六个点时间超限。

可以发现，在 $O(nmk)$ 中，$nm$ 是输入要用的，所以优化只能是在 $k$ 上面。并且暴力算法中也大量的重复计算，例如当前点与上一个点就重复计算了 $k-2$ 个点。是否可以用什么东西来对这种重复计算来进行优化呢？

答案肯定是有的。我们记录下从开头到当前点中出现了多少个 `.` 和多少个 `x`，没有 `x` 就可以取最小值，如果统计范围超过 $k$，对应的计数器减一即可。避免了大量的重复计算。

对于了解过这种思想的人可能可以秒切这题，如果没有也可以把这题当作例题学习这种思想。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, m, k;
string a[N];//用字符串来存 
int minn;
signed main()
{
	cin >> n >> m >> k;
	minn = k + 1;//避免重复，与极大值意义相同 
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i] = "!" + a[i];
	}
	//横向 
	for(int i = 1; i <= n; i++)
	{
		int cnt1, cnt2;
		cnt1 = cnt2 = 0;
		//cnt1:从a[i][1]到a[i][j]出现了多少个 .
		//cnt1:从a[i][1]到a[i][j]出现了多少个 x
		for(int j = 1; j <= m; j++)
		{
			if(a[i][j] == '.') cnt1++;
			if(a[i][j] == 'x') cnt2++;
			if(j > k)//超出范围，前面的点对当前没有影响了 
			{
				//超出去的点对应着减一 
				if(a[i][j - k] == '.') cnt1--;
				if(a[i][j - k] == 'x') cnt2--;
			}
			if(j >= k && cnt2 == 0)//没有x就可以取最小值 
			{
				minn = min(minn, cnt1);
			}
		}
	}
	//竖向，与横向同理 
	for(int i = 1; i <= m; i++)
	{
		int cnt1, cnt2;
		cnt1 = cnt2 = 0;
		for(int j = 1; j <= n; j++)
		{
			if(a[j][i] == '.') cnt1++;
			if(a[j][i] == 'x') cnt2++;
			if(j > k)
			{
				if(a[j - k][i] == '.') cnt1--;
				if(a[j - k][i] == 'x') cnt2--;
			}
			if(j >= k && cnt2 == 0)
			{
				minn = min(minn, cnt1);
			}
		}
	}
	if(minn == k + 1)
	{
		cout << "-1" << endl;
	}
	else
	{
		cout << minn << endl;
	}
	return 0;
}

 
```


---

## 作者：Lame_Joke (赞：3)

**这就是第四题吗？$64$ 个测试点……**

- ### 题目大意

  题目给出 $N,W,K$ 与一个 $N$ 行 $W$ 列的矩阵，矩阵中仅含 `o`、`x`、`.`。每次操作可以将一个 `.` 修改成 `o`。求经过若干次操作后是否能使矩阵中竖着或横着的连续 $K$ 个字符为 `o`。若能则输出最小操作次数，否则输出 `-1`。

- ### 大体思路

  我们可以在输入时求两个前缀和，分别表示当前字符上面和左边共连续了几个 `o` 或 `.`。记录 `.` 的数量。当连续数量等于 $K$ 时，记录下来的 `.` 的数量就是操作次数，$ans$ 取这些数的最小值。当往上的连续数量超过 $K$ 时，判断当前字符往上的第 $K$ 个字符是不是 `.`，如果是的话连续 `.` 的数量减 $1$，左边同理。

- ### 参考代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int h,w,k;
  int lx[200005],l1[200005],lx1,l2,ans=0x7f7f7f7f;
  int main()
  {
  	scanf("%d%d%d",&h,&w,&k);
  	char a[h+5][w+5];
  	for(int i=1;i<=h;i++)
  	{
  		scanf("%s",a[i]);
  		lx1=0,l2=0;
  		for(int j=0;j<w;j++)
  		{
  			if(a[i][j]!='x')
  			{
  				//lx1是左边连续"x"或"."的个数，lx数组是上面的；
  				//lx要用数组是因为我只遍历了一遍这个矩阵，节省时间复杂度; 
  				lx[j]++;
  
  				if(a[i][j]=='.') l1[j]++;
  				if(lx[j]>k)
  				{
  					lx[j]--;
  					if(a[i-k][j]=='.') l1[j]--;
  				}
  				if(lx[j]==k) ans=min(ans,l1[j]);
  				lx1++;
  				if(a[i][j]=='.') l2++;
  				if(lx1>k)
  				{
  					lx1--;
  					if(a[i][j-k]=='.') l2--;
  				}
  				if(lx1==k) ans=min(ans,l2);								
  			}
  			else
  			{
  				lx[j]=0;
  				l1[j]=0;
  				lx1=0,l2=0;
  			}
  		}
  	}
  	if(ans==0x7f7f7f7f) printf("-1");
  	else printf("%d",ans);
  }
  ```

  [AC 记录](https://atcoder.jp/contests/abc337/submissions/49486403)

---

## 作者：2huk (赞：1)

最终的 `o` 串一定是横着或竖着的。那么我们枚举这个**横串**的最左边的位置和**竖串**的最上面的位置。令其为 $(i, j)$。

- 如果可以从 $(i, j)$ 开始，往右一个**横串**，就代表第 $i$ 行中，第 $j \sim j + k -  1$ 列都没有 `x`。如果确实一个 `x` 都没有，那么如果要填满这个**横串**，就需要把第 $i$ 行第 $j \sim j + k - 1$ 列中的所有 `.` 改为 `o`。那么代价即第 $i$ 行第 $j \sim j + k - 1$ 列中 `.` 的数量。
- 同理，如果可以从 $(i, j)$ 开始，往下一个**竖串**，就代表第 $i$ 列中，第 $j \sim j + k -  1$ 行都没有 `x`。如果确实一个 `x` 都没有，那么如果要填满这个**竖串**，就需要把第 $i$ 列第 $j \sim j + k - 1$ 行中的所有 `.` 改为 `o`。那么代价即第 $i$ 列第 $j \sim j + k - 1$ 行中 `.` 的数量。

因此需要预处理 `x` 和 `.` 的数量。直接二维前缀和解决。

[代码](https://atcoder.jp/contests/abc337/submissions/49464781)中记录的是 `x` 和 `o` 的数量，那么 `.` 的数量就是 $k$ 减 `o` 的数量。

最恶心的是不能开二维数组，得用二维 `vector`。

---

## 作者：tallnut (赞：1)

为什么众位巨佬都是用前缀和维护的，就我一个用队列吗 \jk
# 题意简述
给你 $1$ 个 $n \times m$ 的字符矩阵，每个元素为 `o`,`x` 或 `.`，有一些满足如下条件的长度为 $k$ 的子串（横着或竖着）：
- 这个子串中所有元素均为 `o` 或 `.`。

这些子串中，有一个子串含有最少的 `.`。请你输出这个最小的数目。
# 思路
**这篇题解只讨论同一行的子串的情况，同列的话同理。**

先考虑暴力。把每一行扫一遍，枚举其中所有的子串并判断。时间复杂度 $\Theta(n(m-k)k)$，TLE ~~(Time Limit Exploded)~~。

接着优化。我们发现，其实枚举的过程就好像一个[滑动窗口](https://www.luogu.com.cn/problem/P1886)，每次向右滑一个，只不过这次不是维护最值，而是维护 `.` 的数量。同时还要保证没有 `x` 在子串中。

那就好办了。不使用单调队列，转而采用**队列+计数变量**。

具体来说，使用如下算法：
- 枚举每一行（以下均基于对当前这一行进行扫描，并且每行扫描完成后清空所有变量/对象）；
  - 对当前指针所指的元素进行判断：
    - 判断结果为 `x`：撞上障碍物了。不断向后移动指针，直到撞边缘或指向的元素不为 `x`，随后清空所有变量/对象；
    - 否则对队列大小进行判断：
      - 队列大小 $<k$：将当前元素入队，并 _更新计数变量_ （指：如果是入队就视情况将记录 `.` 的数量的变量 $+1$，否则视情况 $-1$，下同）；
      - 队列大小 $=k$：踢出队首元素，并更新计数变量；加入新元素，并更新计数变量；更新最终答案（取 $\min$）；
      - 将指针向后移一位。

# AC 代码
[AC 记录](https://www.luogu.com.cn/record/144254808)。
```
#include <iostream>
#include <queue>
using namespace std;
int h,w,k,ans,tmpcnt;
const int N = 2e5 + 10;
string a[N];
queue<char> q;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ans = 1e9;
	cin >> h >> w >> k;
	for (int i = 0;i < h;i++)
		cin >> a[i];
	//判断行信息中是否存在符合要求的串
	for (int i = 0;i < h;i++)
	{
		int j = 0;
		tmpcnt = 0;
		//开始扫描
		for (;j < w;)
		{
			//如果遇到阻碍，跳过去
			if (a[i][j] == 'x')
			{
				for (;j < w && a[i][j] == 'x';j++);
				//清零
				tmpcnt = 0;
				//清空队列
				while (q.size()) q.pop();
				//直接进入下一次
				continue;
			}
			//此时没有阻碍了，尝试计数
			//用队列维护
			if (q.size() < k)
			{
				q.push(a[i][j]);
				if (a[i][j] == '.') tmpcnt++;
				if (q.size() == k) ans = min(ans,tmpcnt);
			}
			else
			{
				//更新答案
				ans = min(ans,tmpcnt);
				//把队首元素踢出去
				if (q.front() == '.') tmpcnt--;
				q.pop();
				//把新元素加进来
				if (a[i][j] == '.') tmpcnt++;
				q.push(a[i][j]);
				//更新答案
				ans = min(ans,tmpcnt);
			}
			j++;
		}
		while (q.size()) q.pop();
	}
	//判断列信息中是否存在符合要求的串
	for (int i = 0;i < w;i++)
	{
		int j = 0;
		tmpcnt = 0;
		//开始扫描
		for (;j < h;)
		{
			//如果遇到阻碍，跳过去
			if (a[j][i] == 'x')
			{
				for (;j < h && a[j][i] == 'x';j++);
				//清零
				tmpcnt = 0;
				//清空队列
				while (q.size()) q.pop();
				//直接进入下一次
				continue;
			}
			//此时没有阻碍了，尝试计数
			//用队列维护
			if (q.size() < k)
			{
				q.push(a[j][i]);
				if (a[j][i] == '.') tmpcnt++;
				if (q.size() == k) ans = min(ans,tmpcnt);
			}
			else
			{
				//更新答案
				ans = min(ans,tmpcnt);
				//把队首元素踢出去
				if (q.front() == '.') tmpcnt--;
				q.pop();
				//把新元素加进来
				if (a[j][i] == '.') tmpcnt++;
				q.push(a[j][i]);
				//更新答案
				ans = min(ans,tmpcnt);
			}
			j++;
		}
		while (q.size()) q.pop();
	}
	if (ans != 1e9) cout << ans << '\n';
	else cout << -1 << '\n';
}
```

---

## 作者：Guizy (赞：1)

赛时吃了 $7$ 发罚时……

## 题目大意

给你 $H,W,K$ 和一个 $H$ 行 $W$ 列的用 `o`、`x`、`.` 组成的矩阵，每次可以将一个 `.` 改成 `o`。问最少多少次可以让某一行或某一列有 $K$ 个连续的 `o`。

## 思路

数据范围不大，可以使用暴力。

横着遍历一遍，竖着遍历一遍。

以横着遍历为例子（以下 $i$ 为行数，$j$ 为列数）：

用 $temp1$ 表示 $(i,j-k)$ 到 $(i,j)$ 的 `o` 的个数，用 $temp2$ 表示连续的 `.` 或 `o` 的个数，当 $temp2$ 大于 $k$，就用 $k-temp1$ 和答案比较后更新答案，竖着同理。

存输入的数组要先输入长度和宽度之后再定义，否则会 MLE。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,k,ans=INT_MAX;
int temp1,temp2;

int main(){

	cin>>n>>m>>k;
	char ch[n+5][m+5];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>ch[i][j];
			
	for(int i=1;i<=n;i++){
		temp1=temp2=0;
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='x'){
				temp1=temp2=0;
			}
			else if(ch[i][j]=='o'){
				temp1++,temp2++;
			}
			else temp2++;
			if(temp2>k&&ch[i][j-k]=='o') temp1--;
			if(temp2>=k) ans=min(ans,k-temp1);
		}
	}
	
	for(int i=1;i<=m;i++){
		temp1=temp2=0;
		for(int j=1;j<=n;j++){
			if(ch[j][i]=='x'){
				temp1=temp2=0;
			}
			else if(ch[j][i]=='o'){
				temp1++,temp2++;
			}
			else temp2++;
			if(temp2>k&&ch[j-k][i]=='o') temp1--;
			if(temp2>=k) ans=min(ans,k-temp1); 
		}
	}
	
	if(ans==2147483647) return puts("-1"),0;
	
	printf("%d",ans);
	
}
```



---

## 作者：zbzbzzb (赞：0)

在此膜拜一下暴力过的大佬。

我用了有点像滑动窗口的做法。

每次窗口往后移一格，就要判断新加进来的是不是 `o`，如果是，计数器加一，如果是 `x` ，**障碍的**计数器加一。

如果最前面被踢掉的是 `o`，计数器再减一，如果是 `x` ，**障碍的**计数器减一。

后面就是判断是否没有障碍，如果没有，就尝试更新最大值。

以上操作行和列各做一遍就可以了。

AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int h=0,w=0,k=0,cnt=0,cnt1=0,mx=0,flag=1;
string s[200010];
int main(){
	scanf("%d%d%d",&h,&w,&k);
	for(int i=1;i<=h;i++){
		cin>>s[i];
		s[i]=' '+s[i];
	}for(int i=1;i<=h;i++){//行
		cnt=0,cnt1=0;//o和x的数量
		for(int j=1;j<=w;j++){//没到k个先统计
			if(j<=k){
				if(s[i][j]=='o'){
					cnt++;
				}else if(s[i][j]=='x'){
					cnt1++;
				}
			}if(j==k){
				if(cnt1==0){//没障碍
					flag=0;
					mx=max(mx,cnt);
				}
			}if(j>k){
				if(s[i][j]=='o'){//判断新加进来的是否是o
					cnt++;
				}else if(s[i][j]=='x'){//判断新加进来的是否是障碍
					cnt1++;
				}if(s[i][j-k]=='o'){//判断踢掉的是否是o
					cnt--;
				}else if(s[i][j-k]=='x'){//判断踢掉的是否是障碍
					cnt1--;
				}if(cnt1==0){
					flag=0;//用于后面判断输出-1的情况
					mx=max(mx,cnt);//尝试更新
				}
			}
		}
	}for(int i=1;i<=w;i++){//列，同上
		cnt=0,cnt1=0;
		for(int j=1;j<=h;j++){
			if(j<=k){
				if(s[j][i]=='o'){
					cnt++;
				}else if(s[j][i]=='x'){
					cnt1++;
				}
			}if(j==k){
				if(cnt1==0){
					flag=0;
					mx=max(mx,cnt);
				}
			}if(j>k){
				if(s[j][i]=='o'){
					cnt++; 
				}else if(s[j][i]=='x'){
					cnt1++;
				}if(s[j-k][i]=='o'){
					cnt--;
				}else if(s[j-k][i]=='x'){
					cnt1--;
				}if(cnt1==0){
					flag=0;
					mx=max(mx,cnt);
				}
			}
		}
	}if(flag==1){//没有可能的情况
		printf("-1");
	}else{
		printf("%d",k-mx);//答案就是长度减最大值
	}return 0;
}
```

---

## 作者：xz001 (赞：0)

直接用二维 ```vector```，存储矩阵，统计行和列的前缀和（分别统计可修改的点数和阻挡点数），然后枚举每个可能符合条件的点对其下方和右方判断是否合理即可。

代码如下：

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

int h, w, k;

string s[N];

vector <int> sum1[N], sum2[N], sum3[N], sum4[N];

signed main() {
    cin >> h >> w >> k;
    for (int i = 1; i <= h; ++ i)
        cin >> s[i], s[i] = " " + s[i];
    for (int i = 0; i <= h; ++ i) {
    	for (int j = 0; j <= w; ++ j) sum1[i].push_back(0), sum2[i].push_back(0), sum3[i].push_back(0), sum4[i].push_back(0);
	}
	for (int i = 1; i <= h; ++ i) {
		for (int j = 1; j <= w; ++ j) {
			sum1[i][j] = sum1[i][j - 1] + (s[i][j] == 'x');
			sum3[i][j] = sum3[i][j - 1] + (s[i][j] == '.');
		}
	}
	for (int j = 1; j <= w; ++ j) {
		for (int i = 1; i <= h; ++ i) {
			sum2[i][j] = sum2[i - 1][j] + (s[i][j] == 'x');
			sum4[i][j] = sum4[i - 1][j] + (s[i][j] == '.');
		}
	}
	int ans = 1e18;
	for (int i = 1; i <= h; ++ i) {
		for (int j = 1; j <= w - k + 1; ++ j) {
			if (sum1[i][j + k - 1] - sum1[i][j - 1] == 0) ans = min(ans, sum3[i][j + k - 1] - sum3[i][j - 1]);
		}
	}
	for (int i = 1; i <= h - k + 1; ++ i) {
		for (int j = 1; j <= w; ++ j) {
			if (sum2[i + k - 1][j] - sum2[i - 1][j] == 0) ans = min(ans, sum4[i + k - 1][j] - sum4[i - 1][j]);
		}
	}
	if (ans == 1e18) {
		puts("-1");
	} else {
		printf("%lld\n", ans);
	}
    return 0;
}

```

---

## 作者：wuzijinmlily (赞：0)

# 题意

给你一个 $N$ 行 $M$ 列的字符矩阵，由 `o`、`x`、`.` 三种字符组成，你每次可以将一个 `.` 改成 `o`，问最少要多少次才能让某行或者某列为连续 $K$ 个连续的 `o`。

# Solution

数据范围非常友好，$H\times W$ $\le 200000$，不用快读快输照样 AC，简直水题一道，直接用最朴素的算法——暴力枚举，通过枚举矩阵来确定改变次数的最小值，最后判断，输出答案。

详情请参考代码。

# 代码

```cpp
#include<bits/stdc++.h>//先声明一下，本人不喜欢压行，不喜勿喷 
using namespace std;
int h,w,k,a[200001],b[200001],ans=1e9;
string s[200001];
int main()
{
	scanf("%d%d%d",&h,&w,&k);
	for(int i=1;i<=h;i++) 
	{
		cin>>s[i];
	}
	for(int i=1;i<=h;i++)
	{
		s[i]="#"+s[i];//这只是为了方便起见，以便将下标与解释性文本对齐
	}
	for(int y=1;y<=h;y++)
	{
		for(int i=1;i<=w;i++)
		{
			a[i]=a[i-1];
			b[i]=b[i-1];
			if(s[y][i]=='x')
			{
				a[i]++;
			}
			if(s[y][i]=='.')
			{
				b[i]++;
			}
		}
		for(int i=1;i<=w-k+1;i++)
		{
			if(a[i+k-1]-a[i-1]==0)
			{
				ans=min(ans,b[i+k-1]-b[i-1]);
			}
		}
	}
	for(int x=1;x<=w;x++)
	{
		for(int i=1;i<=h;i++)
		{
			a[i]=a[i-1];
			b[i]=b[i-1];
			if(s[i][x]=='x')
			{
				a[i]++;
			}
			if(s[i][x]=='.')
			{
				b[i]++;
			}
		}
		for(int i=1;i<=h-k+1;i++)
		{
			if(a[i+k-1]-a[i-1]==0)
			{
				ans=min(ans,b[i+k-1]-b[i-1]);
			}
		}
	}
	if(ans>k)
	{
		ans=-1;
	}
	printf("%d",ans);
	return 0;
}
```

# 另一种做法

c++ 的操作非常麻烦，所以有一种语言叫做 python……

```python
import numpy as np
import scipy.signal as sig

A,*S=open(0)
*H,k=map(int,A.split())
s=(np.c_[S].view("i4")-46)%64
s[s>1]=-k
a=-1
for i in H:s=s.T;a=max(a,-1 if i<k else int(sig.convolve(s,[[1]*k],"valid").max().round()))
print([-1,k-a][0<=a<=k])
```

短小精悍就是这么来的。python 非常复杂，在这里不做描述，有时间自行了解。

---

## 作者：Wi_Fi (赞：0)

分明是很简单的问题，不需要多么高级的算法。

矩阵大小 $2 \times 10^5$，遍历两遍绰绰有余。横向与纵向遍历算法是相同的，都是直接模拟统计：当前子串是否长度超过 $k$ 且不包含 ```x``` 和 ```o``` 的数量。数组开在输入后即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

int i,j,n,m,k,s1,s2,ans=INT_MAX;
int main()
{
	cin>>n>>m>>k;
	char a[n+5][m+5];
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)cin>>a[i][j];
	}
	for(i=1;i<=n;i++)
	{
		s1=s2=0;
		for(j=1;j<=m;j++)
		{
			if(j>k&&a[i][j-k]=='.')s2--;
			if(a[i][j]=='.')s2++;
			if(a[i][j]=='.'||a[i][j]=='o')s1++;
			else s1=0;
			if(s1>=k)ans=min(ans,s2);
		}
	}
	for(j=1;j<=m;j++)
	{
		s1=s2=0;
		for(i=1;i<=n;i++)
		{
			if(i>k&&a[i-k][j]=='.')s2--;
			if(a[i][j]=='.')s2++;
			if(a[i][j]=='.'||a[i][j]=='o')s1++;
			else s1=0;
			if(s1>=k)ans=min(ans,s2);
		}
	}
	if(ans==INT_MAX)cout<<-1;
	else cout<<ans;
	return 0;
}

```


---

## 作者：xiaofu15191 (赞：0)

首先一行一行地考虑。每一行使用前缀和统计障碍 ``x`` 的个数，同时统计每一个行上的连续空格中 ``o`` 的个数。

前缀和处理完之后，枚举连续 $k$ 个空格的左边界，算出右边界，检查 $k$ 个空格中是否有 ``x``，如果没有，使用 $k$ 减去空格中 ``o`` 的数量更新答案。

一列一列同理。

代码不长，注意空间，Code：

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
long long h,w,k,sum[300010],sum_x[300010];
vector<char>input[300010];
int main()
{
	cin>>h>>w>>k;
	for(long long i=1;i<=h;i++)
	{
		input[i].push_back('x');
		for(long long j=1;j<=w;j++)
		{
			char t='0';
			cin>>t;
			input[i].push_back(t);
		}
	}
	long long ans=2147483647;
	for(long long i=1;i<=h;i++)
	{
		sum_x[0]=sum[0]=0;
		for(long long j=1;j<=w;j++)
		{
			if(input[i][j]=='x')
			{
				sum_x[j]=sum_x[j-1]+1;
				sum[j]=0;
			}
			else
			{
				sum[j]=sum[j-1]+(input[i][j]=='o');
				sum_x[j]=sum_x[j-1];
			}
		}
		for(long long j=k;j<=w;j++)
		{
			long long r=j,l=j-k+1;
			if(sum_x[r]-sum_x[l-1]==0) ans=min(ans,max(1LL*0,k-(sum[r]-sum[l-1])));
		}
	}
	for(long long j=1;j<=w;j++)
	{
		sum_x[0]=sum[0]=0;
		for(long long i=1;i<=h;i++)
		{
			if(input[i][j]=='x')
			{
				sum_x[i]=sum_x[i-1]+1;
				sum[i]=0;
			}
			else
			{
				sum[i]=sum[i-1]+(input[i][j]=='o');
				sum_x[i]=sum_x[i-1];
			}
		}
		for(long long i=k;i<=h;i++)
		{
			long long r=i,l=i-k+1;
			if(sum_x[r]-sum_x[l-1]==0) ans=min(ans,max(1LL*0,k-(sum[r]-sum[l-1])));
		}
	}
	if(ans==2147483647) printf("-1\n");
	else printf("%lld\n",ans);
}
```

彩蛋：

![](https://cdn.luogu.com.cn/upload/image_hosting/wn42ilie.png)

---

## 作者：kczw (赞：0)

# 题意
给定一个 $H\times W$ 的字符矩阵，现在你可以将 `.` 修改为 `o`，问是否可以通过这样的操作获得一个横或者竖着的长为 $K$、宽为 $1$ 的由且仅有 `o` 组成的矩形。若可以输出最小操作数，否则输出 $-1$。
# 思路
因为仅知道 $H\times W\le2\times10^5$，所以这里我选择动态开数组。

其次，我们可以假设所有的 `.` 为 `o`，然后枚举每一个符合条件的矩形求出最小的修改次数即可。

这里的枚举有几个重点：
- 枚举时要保证这里的矩形长度为 $K$，不是至少，而是相等。所以为了方便，这里我用了一个队列来维护，当枚举的矩形长度达到 $K$ 时，每次多枚举一个点，就要从队列里弹出尾上的点，同时维护 `o` 的个数。
- 因为 `x` 不可被修改，所以一旦在枚举过程中遇到了 `x` 就要清空枚举的队列。
```cpp
#include<iostream>
#include<queue>
using namespace std;
int n,m,k,ned=1e9;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	char map[n+5][m+5];
	for(int i=1,kk,o;i<=n;i++){
		kk=o=0;	
		queue<int> q;
		for(int j=1;j<=m;j++){
			cin>>map[i][j];
			if(map[i][j]=='x'){
				kk=o=0;
				while(q.size())q.pop();
			}
			else{
				if(map[i][j]=='o'){
					o++;
					q.push(1);
				}else q.push(0);
				++kk;
				if(kk>k){
					o-=q.front();
					q.pop();
					kk--;
				}
				if(k==kk)ned=min(ned,kk-o);
			}
		}
	}
	for(int j=1,kk,o;j<=m;j++){
		kk=o=0;
		queue<int> q;
		for(int i=1;i<=n;i++){
			if(map[i][j]=='x'){
				kk=o=0;
				while(q.size())q.pop();
			}
			else{
				if(map[i][j]=='o'){
					o++;
					q.push(1);
				}else q.push(0);
				++kk;
				if(kk>k){
					o-=q.front();
					q.pop();
					kk--;
				}
				if(k==kk)ned=min(ned,kk-o);
			}
		}
	}if(ned==1e9)printf("-1");
	else  printf("%d",ned);
}
```

---

## 作者：Cure_Wing (赞：0)

[AT_abc337_d [ABC337D] Cheating Gomoku Narabe](https://www.luogu.com.cn/problem/AT_abc337_d)

### 思路

题目说要填出一行连续 $K$ 个 `o` 或一列连续 $K$ 个 `o`，那么我们就枚举可以成为答案的行和列区间，用双指针维护区间内是否含有 `x` 和区间内 `o` 的个数。如果滑动到一个区间不含 `x`，此时计算出还需要填 `o` 的个数，然后打擂台取最小值即可。

时间复杂度 $O(HW)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=200005;
int h,w,k,tot1,tot2,ans=N;
std::string s[N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>h>>w>>k;
	for(int i=1;i<=h;++i){cin>>s[i];s[i]=" "+s[i];}
	for(int i=1;i<=h;++i){//行
		tot1=tot2=0;
		for(int j=1;j<=w;++j){
			tot1+=s[i][j]=='o';
			tot2+=s[i][j]=='x';//双指针滑动
			if(j>=k){
				if(!tot2) ans=std::min(ans,k-tot1);//打擂台取最小值
				tot1-=s[i][j-k+1]=='o';
				tot2-=s[i][j-k+1]=='x';
			}
		}
	}
	for(int i=1;i<=w;++i){//列
		tot1=tot2=0;
		for(int j=1;j<=h;++j){
			tot1+=s[j][i]=='o';
			tot2+=s[j][i]=='x';
			if(j>=k){
				if(!tot2) ans=std::min(ans,k-tot1);
				tot1-=s[j-k+1][i]=='o';
				tot2-=s[j-k+1][i]=='x';
			}
		}
	}
	cout<<(ans==N?-1:ans);
	return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

赛时想到的一种做法。

我们考虑枚举每个点。对于每个点，得出从当前点为一端的上、下、左、右四个方向连续 $k$ 个变为 `o` 的最少次数。每次更新最小值。

枚举每个点的复杂度为 $O(H \times W)$。$H \times W \le 2 \times 10^{5}$，而 $k$ 最坏情况下等于 $\max \{H, W\}$，所以判断只能用 $O(1)$ 的复杂度进行。

我们考虑用两个前缀和。

要使连续 $k$ 个变为 `o`，根据题意，其区间内不能有任何 `x`。考虑用二维前缀和 $sumx_{i, j}$ 记录左上角到 $i, j$ 这个位置，所有的 `x` 的个数。这是第一个前缀和。

每次将区间内的所有 `.` 变为 `o`，求最少的操作次数，可以用 $sumpoint_{i, j}$ 表示从左上角到 $i, j$ 的位置，共有 `.` 的个数。这是第二个。

有了前缀和，就可以求出区间内的信息了。

然后就好做了。对于枚举每个点，所得出的四个区间。首先判断区间内是否有 `x`，有则区间不可行。在可行的前提下，求该区间全部变为 `o` 的最少操作次数，即区间内 `.` 的个数。注意判断区间是否越界。

对于每个区间，求最少操作次数即为最终答案。

和官方题解比起来，确实有点麻烦。

```cpp
#include <bits/stdc++.h>

int n, m, k;

int main()
{
 	std::ios::sync_with_stdio(false);
 	std::cin.tie(nullptr);
 	std::cout.tie(nullptr);

	std::cin >> n >> m >> k;
	std::vector <std::vector <char> > a(n + 100, std::vector <char> (m + 100)); 
	std::vector <std::vector <int> > sumx(n + 100, std::vector <int> (m + 100));
	std::vector <std::vector <int> > sumpoint(n + 100, std::vector <int> (m + 100));
	
	for (int i = 1; i <= n; ++ i) 
		for (int j = 1; j <= m; ++ j) std::cin >> a[i][j];
	for (int i = 1; i <= n; ++ i) 
		for (int j = 1; j <= m; ++ j) {
			sumx[i][j] = sumx[i][j - 1] + (a[i][j] == 'x');
			sumpoint[i][j] = sumpoint[i][j - 1] + (a[i][j] == '.');
		}
	for (int j = 1; j <= m; ++ j)
		for (int i = 1; i <= n; ++ i) {
			sumx[i][j] += sumx[i - 1][j]; sumpoint[i][j] += sumpoint[i - 1][j];
		} //预处理两个前缀和
		
	
	int ans = 2e9;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			//向上延伸
			if (i - k + 1 >= 1) { //判断越界
				int sx = i - k + 1, sy = j, ex = i, ey = j; //向上延伸区间的四个端点
				int jud = sumx[ex][ey] - sumx[ex][sy - 1] - sumx[sx - 1][ey] + sumx[sx - 1][sy - 1]; //区间内 x 的个数
				if (jud == 0) { //区间内不包含 x，即为可行区间
					int cost = sumpoint[ex][ey] - sumpoint[ex][sy - 1] - sumpoint[sx - 1][ey] + sumpoint[sx - 1][sy - 1];
					// 区间内 . 的个数，相当于操作次数
					ans = std::min(ans, cost); //求最少操作次数
				} 
			}
			
			//向下延伸
			if (i + k - 1 <= n) {
				int sx = i, sy = j, ex = i + k - 1, ey = j;
				int jud = sumx[ex][ey] - sumx[ex][sy - 1] - sumx[sx - 1][ey] + sumx[sx - 1][sy - 1];
				if (jud == 0) {
					int cost = sumpoint[ex][ey] - sumpoint[ex][sy - 1] - sumpoint[sx - 1][ey] + sumpoint[sx - 1][sy - 1];
					ans = std::min(ans, cost);
				}
			}
			
			//向左延伸
			if (j - k + 1 >= 1) {
				int sx = i, sy = j - k + 1, ex = i, ey = j;
				int jud = sumx[ex][ey] - sumx[ex][sy - 1] - sumx[sx - 1][ey] + sumx[sx - 1][sy - 1];
				if (jud == 0) {
					int cost = sumpoint[ex][ey] - sumpoint[ex][sy - 1] - sumpoint[sx - 1][ey] + sumpoint[sx - 1][sy - 1];
					ans = std::min(ans, cost);
				}
			}
			
			//向右延伸
			if (j + k - 1 <= m) {
				int sx = i, sy = j, ex = i, ey = j + k - 1;
				int jud = sumx[ex][ey] - sumx[ex][sy - 1] - sumx[sx - 1][ey] + sumx[sx - 1][sy - 1];
				if (jud == 0) {
					int cost = sumpoint[ex][ey] - sumpoint[ex][sy - 1] - sumpoint[sx - 1][ey] + sumpoint[sx - 1][sy - 1];
					ans = std::min(ans, cost);
				}
			}
		}
	}
	if (ans == 2e9) std::cout << -1;
	else std::cout << ans;

	return 0;
}

```

跑了几乎最拉解。

---

## 作者：Genius_Star (赞：0)

### 题意：

给定一个 $N \times M$ 的矩阵，由 ``x o .`` 组成。

求横着的或者竖着的长度为 $k$ 的一条线段，使得线段中没有 ``x``，并且线段内 ``.`` 的数量最少，输出这个最少的值。

### 思路：

设 $N,M$ 同阶，直接暴力的话，时间复杂度为 $O(N^3)$，你会光荣的得到 ``TLE × 6``。

考虑优化，我们在这个矩阵中枚举这个线段的一个端点，记作 $(i,j)$，要快速判断 $(i,j) \sim (i,j+k-1)$ 内是否有 ``x`` 和 $(i,j) \sim (i,j+k-1)$ 点 ``o`` 的个数。

明显可以进行优化，定义：

- $s_{1,i,j}$ 表示 $(i,1) \sim (i,j)$ 内 ``o`` 的个数。

- $s_{2,i,j}$ 表示 $(1,j) \sim (i,j)$ 内 ``o`` 的个数。

- $s_{3,i,j}$ 表示 $(i,1) \sim (i,j)$ 内 ``x`` 的个数。

- $s_{4,i,j}$ 表示 $(1,j) \sim (i,j)$ 内 ``x`` 的个数。

每次判断第 $i$ 行的 $[l,r]$ 范围内是否有 ``x``，只需要看 $s_{3,i,r}-s_{3,i,l-1}$ 是否为 $0$ 即可，求 $[l,r]$ 范围内 ``o`` 的个数，即 $s_{1,i,r}-s_{1,i,l-1}$；对于列也差不多，就不细讲了。

这样利用前缀和优化时间复杂度为 $O(N^2)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
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
ll n,m,k,ans=1e9;
char c;
int main(){
	n=read(),m=read(),k=read();
	vector<vector<ll>> a(n+10),s1(n+10),s2(n+10),s3(n+10),s4(n+10);
	for(int i=0;i<=n;i++){
		a[i].resize(m+10);
		s1[i].resize(m+10);
		s2[i].resize(m+10);
		s3[i].resize(m+10);
		s4[i].resize(m+10);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%c",&c);
			if(c=='x')
			  a[i][j]=-1;
			else if(c=='o')
			  a[i][j]=1;
		}
		getchar();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			s1[i][j]=s1[i][j-1];
			s3[i][j]=s3[i][j-1];
			if(a[i][j]==1)
			  s1[i][j]++;
			if(a[i][j]==-1)
			  s3[i][j]++;
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			s2[i][j]=s2[i-1][j];
			s4[i][j]=s4[i-1][j];
			if(a[i][j]==1)
			  s2[i][j]++;
			if(a[i][j]==-1)
			  s4[i][j]++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m-k+1;j++){
			ll x=s3[i][j+k-1]-s3[i][j-1];
			if(!x)
			  ans=min(ans,k-(s1[i][j+k-1]-s1[i][j-1]));
		}
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n-k+1;i++){
			ll x=s4[i+k-1][j]-s4[i-1][j];
			if(!x)
			  ans=min(ans,k-(s2[i+k-1][j]-s2[i-1][j]));
		}
	}
	write(ans==1e9?-1:ans);
	return 0;
}
```


---

## 作者：yshpdyt (赞：0)

## 题意
一个 $n\times m$ 矩阵，选取一个 $k\times1$ 或 $1\times k$ 的区域，这个区域不能含有 `x`，找到一个含有最少 `.` 的区域并输出这个最小值，或报告无解。
 
## Sol
把 `.` 值设为 $1$，把 `o` 值设为 $0$，把 `x` 值设为 `inf` ，把列和行单独分开来做，动态查前缀和，即求 $sum_i-sum_{i-k}$，如果这东西绝对值比 $k$ 小，说明是一种合法答案。

但题目没有规定 $n$，$m$ 的单独范围，直接开二维存图会炸。一种解决方式是用 `vector`。这里介绍一种另类的方式。


行的情况很好维护，读入时顺带处理即可，当然也可以用下面这种。

重点在列，先考虑正常前缀和，$w_{i,j}$ 维护前 $i$ 行，第 $j$ 列的前缀和，然后求的是 $w_{i,j}-w_{i-k,j}$，注意到每次查询区间长度固定，~~很像滑动窗口~~，只需要维护前 $k$ 行位置的答案即可，那么就可以去掉一维，$w_j$ 表示第 $j$ 列 $i-k+1 \sim i$ 位置的和，用一个队列存每行的字符串，动态删除超过位置的前缀即可。

具体实现见代码，复杂度 $O(nm)$。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 400005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e9;
const double eps=1e-6;
ll n,m,k;
ll sum[N],w[N];
queue<string>q;//好似string内部是vector所以不会炸
string s;
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    cin>>n>>m>>k;
    ll res=inf;
    for(int i=1;i<=n;i++){
        cin>>s;
        s=" "+s;
        q.push(s);
        for(int j=1;j<=m;j++){
            sum[j]=sum[j-1];//这个是行的
            if(s[j]=='x')sum[j]+=inf,w[j]+=inf;
            if(s[j]=='.')sum[j]++,w[j]++;//行加，列也要加
            if(abs(sum[j]-sum[j-k])<=k&&j>=k)res=min(res,sum[j]-sum[j-k]);//维护行的答案
        }
        if(i>=k){
            s=q.front();
            q.pop();
            for(int j=1;j<=m;j++){
                if(abs(w[j])<=inf)res=min(res,w[j]);//维护列的答案
                if(s[j]=='x')w[j]-=inf;//新增一列就得删除一列
                if(s[j]=='.')w[j]--;
            }
        }
    }
    if(res==inf)res=-1;
    cout<<res;
    return 0;
}
```

---

## 作者：Saint_ying_xtf (赞：0)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。

这道题只有两种方式：竖着和横着。

所以我们对两种方式分讨。

先说竖着。

我们从上往下遍历，开两个指针，一个是遍历的 $i$，另一个是往回走最远的指针 $j$。$i$ 到 $j$ 的这段区间中不会包含 ```x```。如果碰到了 ```x```，那么我们就要将 $j = i+ 1$，要保证区间内不包含 ```x```。若当 $i$ 到 $j$ 的长度等于 $k$，此时就可以通过将 ```.``` 换成 ```o```。

我们只需要在双指针移动的时候统计以下区间内 ```.``` 的数量，然后在符合条件的时更新答案。

横着也是同理，只需要横着遍历，具体细节也是一样的。

注意细节。

[link](https://atcoder.jp/contests/abc337/submissions/49494330)。

---

## 作者：mgcjade (赞：0)

# AT_abc337_d 的题解

## 题目大意

给你一个 $H \times W(H \times W \leq 2 \times 10^5)$ 的矩阵，矩阵由 `o`、`x` 和 `.` 构成。存在一种操作：将一个 `.` 变成 `o`。问在一段连续的区间内，需要进行多少次操作才可以将同一行或同一列中的连续 $k$ 个数都变为 `o`，若无法完成，输出 `-1`。

## 思考过程

看到了~~可爱的~~ $H \times W \leq 2 \times 10^5$，就知道这里必须使用复杂度为 $O(HW)$ 的算法了。

考虑枚举每一列和每一行中的 $k$ 个点是否能满足要求，并更新 `ans`，由于是连续 $k$ 个点，我们需要使用一个类似队列的东西来维护，维护当前的列或者行中的连续 $k$ 个点中有多少个 `.` 和多少个 `x`，有多少个 `.` 就是当前的最优答案，如果当前 $k$ 个字符中有 `x`，就证明当前 $k$ 个字符不符合题意。

## Code

代码中也有详细解释，但不要直接复制。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int ans = 0x3f3f3f3f;
int sum, flag;
string str;
vector<string>s; //直接用char的话会爆空间

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        s.push_back(str);
    }
    for (int i = 0; i < n; i++)  //枚举每一行
    {
        sum = 0, flag = 0;    //sum记录该串中有多少个"."，flag记录该串中有多少个"x"
        for (int j = 0; j < m; j++)
        {
            sum += (s[i][j] == '.'), flag += (s[i][j] == 'x');
            if (j >= k)    //确保此时比连续的k个多
                sum -= (s[i][j - k] == '.'), flag -= (s[i][j - k] == 'x');
            if (j + 1 >= k && flag == 0) //是连续的k个并且没有"x"
                ans = min(ans, sum);
        }
    }
    for (int i = 0; i < m; i++)  //枚举每一列
    {
        sum = 0, flag = 0;
        for (int j = 0; j < n; j++)
        {
            sum += (s[j][i] == '.'), flag += (s[j][i] == 'x');
            if (j >= k)
                sum -= (s[j - k][i] == '.'), flag -= (s[j - k][i] == 'x');
            if (j + 1 >= k && flag == 0)
                ans = min(ans, sum);
        }
    }
    if (ans == 0x3f3f3f3f)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}
```

---

## 作者：yyrwlj (赞：0)

## 题意简述

给定一个 $n \times m$ 的矩阵，矩阵中的每个字母可以是 `.` 或 `x` 或 `o`。

可以花费一个代价让一个 `.` 变成 `o`。

问在矩阵中构造出一个 $1 \times k$ 或 $k \times 1$ 全都是 o 的矩阵的最小代价。若无法构造输出 $-1$。

$n \times m \le 2 \times 10^5$。

## 思路

二维前缀和，维护子矩阵 `.` 和 `x` 的数量。

若矩阵内有 `x`，那么就无法在此矩阵构造。

否则将这个矩阵全变成 `o` 的代价就是矩阵中 `.` 的个数。

因为我们并不知道 $n$ 和 $m$ 单独的范围，所以可以使用 `vector` 来动态申请内存。

读入用 `vector` 套 `string` 即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int get(vector<vector<int> > &a,int x1,int _y1,int x2,int y2,int op = 2)
{
    return a[x2][y2] - a[x2][_y1 - 1] - a[x1 - 1][y2] + a[x1 - 1][_y1 - 1];
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> a(n + 1);
    for (int i=1;i<=n;i++)
    {
        cin >> a[i];
        a[i] = " " + a[i];
    }
    vector<vector<int> > s1(n + 1), s2(n + 1);
    s1[0].resize(m + 1);
    s2[0].resize(m + 1);
    for (int i=1;i<=n;i++)
    {
        s1[i].resize(m + 1);
        s2[i].resize(m + 1);
        for (int j=1;j<=m;j++)
        {
            s1[i][j] = s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1];
            s2[i][j] = s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1];
            if (a[i][j] == 'x')
                s2[i][j] ++;
            else if (a[i][j] == '.')
                s1[i][j] ++;
        }
    }
    int ans = 2e9;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            if (a[i][j] == 'x')
                continue;
            if (j >= k && get(s2, i, j - k + 1, i, j, 1) == 0)
                ans = min(ans, get(s1, i, j - k + 1, i, j));
            if (i >= k && get(s2, i - k + 1, j, i, j, 1) == 0)
                ans = min(ans, get(s1, i - k + 1, j, i, j));
            
        }
    if (ans > 1e9)
        cout << -1 << endl;
    else
        cout << ans;
    return 0;
}
```

---

## 作者：ilibilib (赞：0)

## 分析：

双指针维护一个长度为 $k$ 的序列。

如果右指针移动至 `.` 则费用 $t$ 加一。

如果右指针移动至 `x` 则不合法，将左指针移动到 `x` 后一位，并将费用重置为 $0$。

记录最小的合法费用，记得横竖都要扫。不存在合法情况则输出 `-1`。

## CODE：

```cpp
#include<bits/stdc++.h>
#define N 200010
#define sc scanf
using namespace std;
vector<vector<char>>g;
int main()
{
	int n,m,k,ans=N;
	sc("%d%d%d",&n,&m,&k);
	g.resize(n+10);
	for(int i=1;i<=n;++i)
	{
		g[i].resize(m+10);
		scanf("%s",&g[i][1]);
	}

	for(int i=1;i<=n;++i)
	{
		int l=1,r=0,t=0;
		while(r<m)
		{
			while(r-l+1<k&&r<m)
			{
				++r;
				if(g[i][r]=='x') l=r+1,t=0;
				else if(g[i][r]=='.') ++t;
			}
			if(r-l+1==k) ans=min(ans,t);
			if(l>m) break;
			if(g[i][l]=='.') --t;
			++l;
		}
	}
	for(int i=1;i<=m;++i)
	{
		int l=1,r=0,t=0;
		while(r<n)
		{
			while(r-l+1<k&&r<n)
			{
				++r;
				if(g[r][i]=='x') l=r+1,t=0;
				else if(g[r][i]=='.') ++t;
			}
			if(r-l+1==k) ans=min(ans,t);
			if(l>n) break;
			if(g[l][i]=='.') --t;
			++l;
		}
	}
	if(ans==N) puts("-1");
	else printf("%d",ans);
	return 0;
}
```

---

