# [ABC341C] Takahashi Gets Lost

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc341/tasks/abc341_c

$ H $ 行 $ W $ 列のグリッドがあります。

グリッドの各マスは**陸**か**海**のどちらかであり、 その情報は $ H $ 個の長さ $ W $ の文字列 $ S_1,\ S_2,\ \ldots,\ S_H $ で与えられます。 上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ で表すと、 $ S_i $ の $ j $ 文字目が `.` のときマス $ (i,\ j) $ は陸であり、`#` のときマス $ (i,\ j) $ は海です。

ここで、グリッドの外周のマス（すなわち、$ i\ =\ 1 $ 、$ i\ =\ H $ 、$ j\ =\ 1 $ 、$ j\ =\ W $ のうち少なくとも $ 1 $ 個以上を満たすマス $ (i,\ j) $ ）については、すべて海であることが制約として保証されます。

高橋君が乗った宇宙船が、グリッド上のあるマスに不時着してしまいました。 その後、高橋君は `L` 、`R` 、`U` 、`D` のみからなる長さ $ N $ の文字列 $ T $ で表される手順に沿って、グリッド上を $ N $ 回移動しました。 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ T $ の $ i $ 文字目は $ i $ 回目の移動の内容を下記の通り表します。

- `L` のとき、左に $ 1 $ マス移動したことを表す。すなわち、移動前のマスを $ (i,\ j) $ とするとき、移動後のマスは $ (i,\ j-1) $ である。
- `R` のとき、右に $ 1 $ マス移動したことを表す。すなわち、移動前のマスを $ (i,\ j) $ とするとき、移動後のマスは $ (i,\ j+1) $ である。
- `U` のとき、上に $ 1 $ マス移動したことを表す。すなわち、移動前のマスを $ (i,\ j) $ とするとき、移動後のマスは $ (i-1,\ j) $ である。
- `D` のとき、下に $ 1 $ マス移動したことを表す。すなわち、移動前のマスを $ (i,\ j) $ とするとき、移動後のマスは $ (i+1,\ j) $ である。

高橋君の移動経路上のマス（不時着したマスおよび現在いるマスを含む）はいずれも海でないことがわかっています。 高橋君が現在いるマスとしてあり得るものの個数を出力してください。

## 说明/提示

### 制約

- $ H,\ W,\ N $ は整数
- $ 3\ \leq\ H,\ W\ \leq\ 500 $
- $ 1\ \leq\ N\ \leq\ 500 $
- $ T $ は `L` 、`R` 、`U` 、`D` のみからなる長さ $ N $ の文字列
- $ S_i $ は `.` と `#` のみからなる長さ $ W $ の文字列
- 高橋君が現在いるマスとしてあり得るものが少なくとも $ 1 $ 個存在する。
- グリッドの外周のマスはすべて海である。

### Sample Explanation 1

下記の $ 2 $ つの場合がありえるため、高橋君が現在いるマスとしてあり得るものは $ (3,\ 4) $ と $ (4,\ 5) $ の $ 2 $ 個です。 - マス $ (3,\ 5) $ に不時着し、$ (3,\ 5)\ \rightarrow\ (3,\ 4)\ \rightarrow\ (2,\ 4)\ \rightarrow\ (2,\ 3)\ \rightarrow\ (3,\ 3)\ \rightarrow\ (3,\ 4) $ と移動した場合 - マス $ (4,\ 6) $ に不時着し、$ (4,\ 6)\ \rightarrow\ (4,\ 5)\ \rightarrow\ (3,\ 5)\ \rightarrow\ (3,\ 4)\ \rightarrow\ (4,\ 4)\ \rightarrow\ (4,\ 5) $ と移動した場合

## 样例 #1

### 输入

```
6 7 5
LULDR
#######
#...#.#
##...##
#.#...#
#...#.#
#######```

### 输出

```
2```

## 样例 #2

### 输入

```
13 16 9
ULURDLURD
################
##..##.#..####.#
###.#..#.....#.#
#..##..#####.###
#...#..#......##
###.##.#..#....#
##.#####....##.#
###.###.#.#.#..#
######.....##..#
#...#.#.######.#
##..###..#..#.##
#...#.#.#...#..#
################```

### 输出

```
6```

# 题解

## 作者：__Dist__ (赞：4)

暴力。

枚举每个可能成为起点的位置，走 $n$ 步看看有没有掉进海里或者走出地图。

```cpp
#include <bits/stdc++.h>
#define gt getchar
#define pt putchar
#define ll long long
​
using namespace std;
​
const int MAXN = 505;
​
ll read() {
    ll x = 0, f = 1;char ch = gt();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1;ch = gt();}
    while (ch >= '0' && ch <= '9') {x *= 10;x += ch - '0';ch = gt();}
    return x * f;
}
​
ll h, w, n;
char s[MAXN];
char ch[MAXN][MAXN];
​
int main() {
    cin >> h >> w >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> ch[i][j];
        }
    }
    ll res = 0;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if(ch[i][j] == '.') {
                int x = i, y = j;
                bool f = true;
                for (int k = 1; k <= n; k++) {
                    if(s[k] == 'L') y--;
                    else if(s[k] == 'R') y++;
                    else if(s[k] == 'U') x--;
                    else x++;
                    if(x < 1 || x > h || y < 1 || y > w || ch[x][y] == '#') {
                        f = false;
                        break;
                    }
                }
                res += f;
            }
        }
    }
    cout << res;
    return 0;
}
```

---

## 作者：endswitch (赞：2)

思路：

考虑到 $H,W,N$ 的数据范围很小，而你所走的路径是一定的，所以我们不难想到枚举地图上的每一个点，然后模拟一遍路径即可。时间复杂度 $O(N^3)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 505;
int H, W, n, x, y, ans;
char T[N], Map[N][N];
signed main() {
	ios_base :: sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> H >> W >> n;
	for(int i = 1 ; i <= n ; ++ i)
		cin >> T[i];
	for(int i = 1 ; i <= H ; ++ i)
		for(int j = 1 ; j <= W ; ++ j)
			cin >> Map[i][j];
	for(int i = 1 ; i <= H ; ++ i)
		for(int j = 1 ; j <= W ; ++ j)
			if(Map[i][j] == '.') {
				x = i, y = j;
				for(int k = 1 ; k <= n ; ++ k) {
					if(T[k] == 'L') -- y;
					else if(T[k] == 'R') ++ y;
					else if(T[k] == 'U') -- x;
					else ++ x;
					if(x > H || y > W || x < 1 || y < 1 || Map[x][y] == '#') goto Vegetableless;
				}
				ans++;
				Vegetableless:;
			}
	cout << ans;
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc341_c)

我们直接暴力枚举 Takahashi 降落的位置，然后根据他走的方向判断他经过的地方是否全是陆地即可。

时间复杂度 $\mathcal O(hwn)$。

[code](https://atcoder.jp/contests/abc341/submissions/50346249)

---

## 作者：cjh20090318 (赞：2)

本来不想写这个题题解的，但是偶然发现在洛谷上是最优解？

这个题和 [P6226 [BalticOI 2019 Day1] 潜艇](https://www.luogu.com.cn/problem/P6226)有一定的相似之处。

## 题意

海洋是一个 $H \times W$ 的网格，其中 `.` 代表岛屿，`#` 代表水域，高桥**只能在陆地上行走**。

高桥坠落到了一个陆地上，接着他会依次沿着给定的字符串 $T$ 进行移动，其中字符串中的 `LRUD`，分别表示向左、向右、向上、向下移动一个单元格。

你不知道高桥坠落的位置，所以请求出高桥移动后可能的位置数量。

## 分析

考虑动态规划。

### 状态设计

设 $f_{i,x,y}$ 表示执行完前 $i$ 个操作后位置 $(x,y)$ 能否作为终点。

设命令字符串为 $s$，原地图为 $a$。

### 状态转移

$$
f_{i,x,y}=f_{0,x,y} \operatorname{and} 
\begin{cases}
f_{i-1,x+1,y} & T_i=\texttt{U}\\
f_{i-1,x-1,y} & T_i=\texttt{D}\\
f_{i-1,x,y+1} & T_i=\texttt{L}\\
f_{i-1,x,y-1} & T_i=\texttt{R}\\
0 & \text{otherwise}
\end{cases}
$$

### 初始状态

$$

$$

$$
f_{0,x,y}=
\begin{cases}
1 & a_{x,y}=\texttt{.}\\
0 & a_{x,y}=\texttt{\#}\\
0 & \text{otherwise}
\end{cases}
$$

经过观察可以发现状态转移只需要两维，所以可以直接滚动省略掉第一维。

时间复杂度 $O(HWN)$，但是因为 `std::bitset` 砍掉了一个大常数。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<bitset>
using namespace std;
int n,m,k;//这里的 n,m,k 分别对应题面中的 H,W,N。
bitset<505>c[505],b[505];
char t[505];
int main(){
	scanf("%d%d%d %s",&n,&m,&k,t);
	for(int i=0;i<n;i++){
		scanf(" ");
		for(int j=0;j<m;j++) b[i][j]=c[i][j]=getchar()=='.';
	}
	for(int i=0;i<k;i++){
		if(t[i]=='L'){
			for(int i=0;i<n;i++) b[i]=(b[i]>>1)&c[i];
		}
		else if(t[i]=='R'){
			for(int i=0;i<n;i++) b[i]=(b[i]<<1)&c[i];
		}
		else if(t[i]=='U'){
			for(int i=0;i<n-1;i++) b[i]=b[i+1]&c[i];
			b[n-1].reset();
		}
		else if(t[i]=='D'){
			for(int i=n-1;i>0;--i) b[i]=b[i-1]&c[i];
			b[0].reset();
		}
	}
	int ans=0;
	for(int i=0;i<n;i++) ans+=b[i].count();//统计有多少个点可能存在。
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：tder (赞：2)

按题意模拟即可。

枚举初始点，判断经过路径是否无海，累加即可。

注意要判断初始点和终止点。

时间复杂度 $O(h\times w\times n)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500 + 5;
int h, w, n, ans;
string t;
char s[N][N];
bool check(int x, int y) {
    for(char c : t) {
        if(x < 1 || x > h || y < 1 || y > w || s[x][y] == '#') return 0; 
        if(c == 'L') y--;
        if(c == 'R') y++;
        if(c == 'U') x--;
        if(c == 'D') x++;
    }
    return 1;
}
signed main() {
    cin>>h>>w>>n>>t;
    t += ' ';
    for(int i = 1; i <= h; i++) for(int j = 1; j <= w; j++) cin>>s[i][j];
    for(int i = 1; i <= h; i++) for(int j = 1; j <= w; j++) if(check(i, j)) ans++;
    cout<<ans;
}
```

---

## 作者：fmdd_szx (赞：1)

[原题](https://www.luogu.com.cn/problem/AT_abc341_c)
## 思路
大模拟，枚举每个位置，看是否满足条件，照题意移动即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,i,j,x,y,l,fl,ans;
char a[501][501],s[501];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);                        
    cin>>n>>m>>k>>s+1;
    for(i=1;i<=n;i++)
        cin>>a[i]+1;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            x=i;y=j;fl=1;
            for(l=1;l<=k;l++){
                if(a[x][y]=='#'){
                    fl=0;
                    break;
                }
                if(s[l]=='U') x--;
                else if(s[l]=='D') x++;
                else if(s[l]=='L') y--;
                else y++;
            }
            if(fl&&a[x][y]!='#') ans++;//统计路径数量
        }
    cout<<ans;
    return 0;
}
```

---

## 作者：_Weslie_ (赞：1)

## 题意简述

$h\times w$ 的网格，给定操作序列，任意选择起点，途中不能经过 ```#``` 点，问有多少个终点。

## 思路分析

每一个终点都对应一个起点有操作序列，所以可以枚举起点然后进行对操作序列的转化。

时间复杂度 $\operatorname{O}(n^3)$，不会超时。

## 代码实现

在判断时必须要判断是否越界，这增大了很多码量。

所以我们可以初始将所有都设为 ```#``` 然后输入，这样边界的所有点都是 ```#```，就不会出现越界问题了。

## Code

```
#include<iostream>
using namespace std;
char c[505][505];
string s;
int n,h,w;
int main(){
	cin>>h>>w>>n>>s;
	for(int i=0;i<=501;i++){
		for(int j=0;j<=501;j++){
			c[i][j]='#'; 
		}
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>c[i][j];
		}
	}
	int ans=0;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			int nowi=i,nowj=j,f=1;
			if(c[nowi][nowj]=='#')continue;
			for(int k=0;k<s.length();k++){
				if(s[k]=='R')nowj++;
				if(s[k]=='L')nowj--;
				if(s[k]=='U')nowi--;
				if(s[k]=='D')nowi++;
				if(c[nowi][nowj]=='#'){
					f=0;
					break;
				}
			}
			if(f)ans++;
		}
	}
	cout<<ans<<endl;
}
```

---

## 作者：Guizy (赞：1)

$H,W,N$ 只有 $500$，考虑 $O(HWN)$ 的暴力。

对于每个点执行一次指令，如果不会到海洋就把答案加 $1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Max=501;
char ch[Max][Max];
string s;
int n,m,sze,cnt;

bool check(int x,int y){
	if(ch[x][y]=='#') return 0;
	for(int i=0;i<sze;i++){
		if(s[i]=='L') y--;
		if(s[i]=='R') y++;
		if(s[i]=='U') x--;
		if(s[i]=='D') x++;
		if(ch[x][y]=='#'||x<=0||y<=0||x>n||y>m){
			return 0;
		}
	} 
	return 1;
}

signed main(){
	
	scanf("%d%d%d",&n,&m,&sze);
	cin>>s;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>ch[i][j];
			
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(check(i,j)) cnt++;
	printf("%d",cnt);
	
	return 0;
}
```

---

## 作者：Albatross_LC (赞：1)

### 题意

给一个地图，求得上面的一些点，在移动过程中不会移动到海里，求合法节点数。

### 思路

可以看到 $3 \le H, W \le 500, 1 \le N \le 500$，直接暴力做的话时间复杂度为 $O(HWN)$，可以接受。

### Code:

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
int n, m, t;
char s[501][501], c[501];
bool check(int u, int v) {
	return u <= n && u && v <= m && v && s[u][v] == '.';
}
pair<int, int>d[123];
int main() {
	d['L'] = { 0,-1};
	d['R'] = { 0, 1};
	d['U'] = {-1, 0};
	d['D'] = { 1, 0};
	cin >> n >> m >> t;
	for (int i = 1; i <= t; i ++ ) cin >> c[i];
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ )
		cin >> s[i][j];
	int ans = 0;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= m; j ++ ) if (s[i][j] == '.'){
			bool ok = 0;
			bool p = 1;
			int x = i, y = j;
			for (int k = 1; k <= t; k ++ ) {
				if (check(x + d[c[k]].x, y + d[c[k]].y))
					x += d[c[k]].x, y += d[c[k]].y;
				else { p = 0; break; }
			}
			if (p) ok = 1;
			ans += ok;
		}
	cout << ans;
}
```

---

## 作者：Lele_Programmer (赞：1)

# AT_abc341_c 题解

## 题目大意

给定一张地图，只能在 `.` 的格子走动，不能在 `#` 的格子走动，给定一串由 `UDLR` 组成的命令，分别表示上下左右移动一格，可以从任意一个 `.` 的格子出发，按照命令走动，途中不得穿过 `#` 的格子，问路径的终点有可能在几个格子。

## 题目分析

暴力模拟，对于每一个能够走动的格子，将其作为起点，按照命令进行移动，统计路径数量即可。

时间复杂度 $O(N^3)$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=505;

int n,m,k;
string op; // 储存命令
char a[N][N]; // 储存地图

bool check(int x,int y) { // 判断是否出界或走向不能走的格子
    if (x>=1 && y>=1 && x<=n && y<=m && a[x][y]!='#') {
        return true;
    } else {
        return false;
    }
}

int main() {
    scanf("%d %d %d",&n,&m,&k);
    cin>>op;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            scanf(" %c",&a[i][j]); // %c 前面要加一个空格，过滤换行符和空格
        }
    }
    int ans=0;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            if (a[i][j]=='#') continue;
            int x=i,y=j;
            bool ok=true;
            for (int p=0;p<k;++p) { // 对于每一个可以走的格子，进行一次模拟即可
                if (op[p]=='L') y--;
                else if (op[p]=='R') y++;
                else if (op[p]=='U') x--;
                else x++;
                if (!check(x,y)) { // 一旦不能往下走，直接退出
                    ok=false;
                    break;
                }
            }
            if (ok) ans++; // 记录答案
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：mgcjade (赞：1)

# [\[ABC341C\] Takahashi Gets Lost](https://luogu.com.cn/problem/AT_abc341_c) 的题解

## 题目大意

给你一个图，`.` 表示可以通行，`#` 表示不可以通行，还给你一个操作指令串，`U` 代表向上走一格，`D` 代表向下走一格，`L` 代表向左走一格，`R` 代表向右走一格，问你有多少种起始点，按照指令走，可以不经过障碍走完，输出方案数。

## 思路

既然 $1 \le W,H \le 500$，考虑直接暴力。

枚举每一个起点 $(i,j)$，随后看看按照规定能否走完，如果可以，`ans++`，否则，去看下一个起点。

时间复杂度 $O(WHN)$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, k;
string goes;
string str[505];
int ans;
int _turn[128][2];

bool check(int x, int y)
{
	int a = x, b = y;
	int i = 0;
	while (i < k && x >= 0 && y >= 0 && x < n && y < m && str[x][y] == '.')
		x += _turn[goes[i]][0], y += _turn[goes[i]][1], i++;
	if (str[x][y] != '.')
		return 0;
	return 1;
}

int main()
{
	_turn['L'][0] = 0, _turn['L'][1] = -1;
	_turn['R'][0] = 0, _turn['R'][1] = 1;
	_turn['U'][0] = -1, _turn['U'][1] = 0;
	_turn['D'][0] = 1, _turn['D'][1] = 0;
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> k;
    cin >> goes;
    for (int i = 0; i < n; i++)
    	cin >> str[i];
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		ans += check(i, j);
    cout << ans;
    return 0;
}
```

---

## 作者：Clay_L (赞：0)

### 算法分析

模拟。枚举每一个点，是 `'@'` 就跳过。再以枚举到的点作为起始点开始按路线走。走到边界以外或走进带有 `'@'` 的点直接跳过。那些没有被跳过的点数就是答案。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=10*x+ch-'0',ch=getchar();
	return x*f;
}
inline void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n=read(),m=read(),l=read(),ans;
string s;
char c[510][510];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>s;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>c[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i][j]=='#')continue;
			int x=i,y=j;
			bool b=1;
			for(int k=0;k<l;k++){
				if(s[k]=='U')x--;
				else if(s[k]=='D')x++;
				else if(s[k]=='L')y--;
				else y++;
				/*
				同下:
				switch(s[k]){
					case'U':x--;break;
					case'D':x++;break;
					case'L':y--;break;
					case'R':y++;break;
				}
				*/
				if(x<1||x>n||y<1||y>m||c[x][y]=='#'){//出边界就跳过
					b=0;
					break;
				}
			}
			if(b)ans++;//未跳过就将数量加1
		}
	}
	write(ans);
	return 0;
}
```

完结撒花。

---

## 作者：unordered_yao (赞：0)

## 做题思路

1. 首先遍历 $S$ 数组的每一个字符，只要遍历到陆地，就遍历给的方向 $D$，拓展下一个点。

1. 然后呢，如果拓展的下一个点出界了，或者是海洋，那么这个点不合法，直接退出循环搜下一个点。

1. 如果这个点按照方向走完没有出界或经过海洋，那就将 $ans+1$。



## 代码

```cpp
#include <iostream>

using namespace std;

const int N = 505;
char s[N][N];//地形图
char d[N];//方向
int h,w,n;
int dx[] = {-1,0,1,0},dy[] = {0,1,0,-1};//通过偏移量访问下一个点

int ans;

int main() {
	scanf("%d%d%d",&h,&w,&n);

	scanf("%s",d);

	for(int i=0; i<h; i++) scanf("%s",s[i]);

	//遍历每个点
	for(int i=0; i<h; i++) {
		for(int j=0; j<w; j++) {
			if(s[i][j] == '.') { //如果为陆地，拓展这个点
				bool flag = 0;//标记不合法，true为不合法
				int x=i,y=j;       
				for(int k=0; k<n; k++) { //遍历要走方向
					int id;
					if(d[k] == 'U') id = 0;//确定方向
					else if(d[k] == 'R') id = 1;
					else if(d[k] == 'D') id = 2;
					else if(d[k] == 'L') id = 3;
                    
					x+=dx[id],y+=dy[id];
					//判断出界（注意，我的下标是从0开始
					if(x < 0 || x >= h || y < 0 || y >= w) {
						flag = 1;
						break;
					}
					//判断是不是海洋，如果是，该方案不合法
					if(s[x][y] == '#') {
						flag = 1;
						break;
					}
				}
            			
				if(!flag) ans++;//如果合法，那就ans+1
			}
		}
	}
	//输出答案
	printf("%d\n",ans);
	return 0;//完美结束
}
```

---

## 作者：AnnaQ (赞：0)

# 思路
这道题就是去模拟在岛屿上按照指定路线去走，海不能走，让你求出来你现在可能在的位置的数量。

这道题在按照指定路线去走的时候坐标的加减不能按照在坐标轴上那样加减，比如说：向左走的话，$ y - 1 $，因为在代码中，$ x $ 是代表哪一行，就相当于坐标轴上的 $ y $，而 $ y $ 是代表哪一列，就相当于坐标轴上的 $ x $，所以，当坐标轴上是变 $ x $ 时，需要变 $ y $，而当坐标轴上是要变 $ y $ 时，需变 $ x $。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int h,w,n,ans;
char control[510],s[510][510];
//递归
void dfs(int x,int y,int step)
{
	if(s[x][y] == '#')//如果是海，那么就退出
	{
		return;
	}
	if(step == n + 1)//如果走完了，也没有走到过海，那么答案就+1，注意：step不能是n，得是n+1，因为当step是n时，还要再走一步，没有走完给定的路线
	{
		ans += 1;//答案+1
		return;
	}
	if(control[step] == 'L')
	{
		dfs(x,y - 1,step + 1);//向左走
	}
	else if(control[step] == 'R')
	{
		dfs(x,y + 1,step + 1);//向右走
	}
	else if(control[step] == 'U')
	{
		dfs(x - 1,y,step + 1);//向上走
	}
	else if(control[step] == 'D')
	{
		dfs(x + 1,y,step + 1);//向下走
	}
}
int main()
{
	//输入
   cin >> h >> w >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> control[i];
	}
	for(int i = 1;i <= h;i++)
	{
		for(int j = 1;j <= w;j++)
		{
			cin >> s[i][j];
		}
	}
   //枚举
	for(int i = 1;i <= h;i++)
	{
		for(int j = 1;j <= w;j++)
		{
			if(s[i][j] == '.')//如果是陆地
			{
				dfs(i,j,1);//开始按照给定的路线去递归
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：2021zjhs005 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc341_c)。

Despriction
------------
给定一个 $h\times w$（$1\le h,w\le 500$） 的矩阵以及长度为 $n$ 的字符串 $T$。矩阵由 `.` 和 `#` 组成，并且保证最外边一圈都是 `#`。字符串由 `L`,`R`,`U`,`D` 组成。

设当前位置位 $(i,j)$。

- `L` 表示向左走，操作后为 $(i,j-1)$。

- `R` 表示向右走，操作后为 $(i,j+1)$。

- `U` 表示向上走，操作后为 $(i-1,j)$。

- `D` 表示向下走，操作后为 $(i+1,j)$。

高桥出生在某一个点 $(i,j)$，经过操作后可以到达另一个点 $(l,r)$。途中必须**不越界**（似乎不会越界，因为最外圈都是 `#`），并且**没有碰到 `#`**。求满足条件的 $(l,r)$ 数量。


Solution
------------

将问题转化为求满足条件的 $(i,j)$，如果说都能走，那么不同的 $(i,j)$ 所到达的点 $(l,r)$ 一定不同。

因此直接暴力即可。

枚举 $h\times w$ 的矩阵，如果这个点是 `.`，则进行字符串指令。

若指令中途越界了，**或者**说是碰到 `#`，那么这个点不能作为答案；反之，这个点对答案的贡献为 $1$。

时间复杂度为 $\mathcal (h\times w\times len)$，其中 $len$ 表示字符串 $T$ 的长度。

仔细看时间限制，发现不会 `T`，所以直接大胆打代码即可。

[Code](https://www.luogu.com.cn/paste/ihglbdkd)。

[`AC` 记录](https://atcoder.jp/contests/abc341/submissions/50402754)。

---

## 作者：banned_gutongxing (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc341_c)

## 思路分析

这道题中，$H$、$W$ 和 $N$ 的范围比较小，所以我们直接枚举每一个位置然后检查是否合法。时间复杂度：$O(HWN)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 510;
int n,m,k,ans;
bool flag[MAXN][MAXN];
char op[MAXN],tmp[MAXN];
bool check(int i,int j,int now){
	if(i<1||j<1) return false;
	if(i>n||j>m) return false;
	if(!flag[i][j]) return false;
	if(now>k) return true;
	switch(op[now]){
		case 'L':{
			return check(i,j-1,now+1);
			break;
		}
		case 'R':{
			return check(i,j+1,now+1);
			break;
		}
		case 'U':{
			return check(i-1,j,now+1);
			break;
		}
		case 'D':{
			return check(i+1,j,now+1);
			break;
		}
	} 
}
signed main(){
	scanf("%d%d%d%s",&n,&m,&k,op+1);
	for(int i = 1;i<=n;i++){
		scanf("%s",tmp+1);
		for(int j = 1;j<=m;j++){
			if(tmp[j]=='.'){
				flag[i][j] = 1;
			}
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			if(flag[i][j]){
				if(i==4&&j==5){
					bool flag = 0;
				}
				if(check(i,j,1)){
					ans++;
				}
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```



---

## 作者：Programming_Konjac (赞：0)

# 思路
枚举每一个点，进行遍历移动操作的字符串，如果经过的每一个点都是 `.`，那么计数器加 $1$。

可以使用 dfs 进行遍历。

最后输出计数器就可以了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define bpq<s> priority_queue<s>
#define spq<s> priority_queue<s,vector<s>,greater<s> >
#define rep(i,j,k) for(int i=j; i<=k; i++)
#define per(i,j,k) for(int i=j; i>=k; i--)
int flag=1,h,w,n;
char c[505][505];
string s;
void dfs(int i,int x,int y){
	if(c[x][y]=='#'&&i>0){
		flag=0;
		return;
	}
	if(i==n) return;
	if(x<0||x>=h||y<0||y>=w){
		flag=0;
		return;
	}
	if(c[x][y]=='#'&&i>0){
		flag=0;
		return;
	}
	if(!flag) return;
	if(s[i]=='L'){
		dfs(i+1,x,y-1);
	}
	if(s[i]=='R'){
		dfs(i+1,x,y+1);
	}
	if(s[i]=='U'){
		dfs(i+1,x-1,y);
	}
	if(s[i]=='D'){
		dfs(i+1,x+1,y);
	}
}
int main(){
	cin>>h>>w>>n;
	cin>>s;
	for(int i=0;i<h;i++){
		cin>>c[i];
	}
	int cnt=0;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(c[i][j]=='.'){
				flag=1;
				dfs(0,i,j);
				if(flag) cnt++;
			}
		}
	}
	cout<<cnt;
	return 0;
}



```

---

## 作者：MicroSun (赞：0)

考虑暴力。注意到 $H,W,N\le500$，所以复杂度为 $O(HWN)≈10^8$ 的算法可以被接受。

实现时对于每个点检查一遍能否按顺序走该路径即可。

Code：
```cpp
// Problem: C - Takahashi Gets Lost
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
#define fst first
#define scd second
#define rep(i,s,e) for(int i=s;i<=e;i++)
#define dep(i,s,e) for(int i=s;i>=e;i--)

using ll=long long;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

const int maxn=2e5+10;

char a[505];
char p[505][505];
int n,m,x1;
bool check(int x,int y){
	if(p[x][y]=='#') return 0;
	rep(i,1,x1){
		if(a[i]=='L') --y;
		else if(a[i]=='R') ++y;
		else if(a[i]=='U') --x;
		else ++x;
		if(p[x][y]=='#') return 0;
	}
	return 1;
}
void solve(){
	cin>>n>>m>>x1;
	rep(i,1,x1) cin>>a[i];
	rep(i,1,n)
		rep(j,1,m) cin>>p[i][j];
	int cnt=0;
	rep(i,1,n)
		rep(j,1,m)
			if(check(i,j)) ++cnt;
	cout<<cnt;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t=1;
	//cin>>t;
	while(t--) solve();
    return 0;
}
```

---

## 作者：Bpds1110 (赞：0)

因为 $H \le 500$，$W \le 500$，$N \le 500$。所以考虑暴力求解。

对于每个不是 `#` 的点，都暴力判断该点按照给出字符串移动，移动到的每个点都是否为 `.`。若是，则增加方案数。

最终输出总方案数即可。时间复杂度约为 $O(H \times W \times N)$。

---

## 作者：SnowFlavour (赞：0)

# Part 1 题目本身
## 思路
这道题的数据范围告诉我们它可以暴力解决。因此我们的思路就是：枚举每一个点，然后尝试按照路径移动，看看会不会掉进海里（因为四面都是海所以不用考虑撞墙的情况）。如果不会，那么这个点就是合法的起点。

也就是说，用 $O(n^2)$ 的时间遍历每一个点，然后再对于每一个点用 $O(n)$ 的时间移动，总共的时间复杂度为 $O(n^3)$。

代码其实很容易实现，毕竟是暴力做法。
## 代码
```cpp
#include<iostream>
using namespace std;
bool mp[505][505];
int mv_x[4]={-1,1,0,0};
int mv_y[4]={0,0,-1,1};
int t[505];
int main(){
	int h,w,n;
	cin>>h>>w>>n;
	string s;
	cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='U')t[i]=0;
		if(s[i]=='D')t[i]=1;
		if(s[i]=='L')t[i]=2;
		if(s[i]=='R')t[i]=3;
	}
	for(int i=0;i<h;i++){
		string sn;
		cin>>sn;
		for(int j=0;j<w;j++){
			char &a=sn[j];
			if(a=='.')mp[i][j]=1;
			else mp[i][j]=0;
		}
	}
	int cnt=0;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			if(!mp[i][j])continue;
			int pos_x=i,pos_y=j,yes=1;
			for(int k=0;k<n;k++){
				pos_x+=mv_x[t[k]];
				pos_y+=mv_y[t[k]];
				if(pos_x<0||pos_x>=h||pos_y<0||pos_y>=w||!mp[pos_x][pos_y]){
					yes=0;
					break;
					
				}
			}
			
			if(yes)cnt++;
			}
	}
	cout<<cnt<<endl;
}
```
# Part 2 题目的延伸
在这里，我们的 $N,H,W \le 500$。然而假如数据范围扩大到 $10^4$，我们又该如何解决这道题目呢？其实有两个显而易见的优化：
- 每一次我们都要一步步的走。然而其实每一次的路径是相同的。这也就是说，我们可以预先求出路径，然后每一次都直接根据找到的路径再进行计算。
- 不需要遍历全图。我们可以在输入的时候就定义一个队列，然后只需要用队列进行运算就行了，也就是说，省去了“搜索”的时间。  

至于代码，就留给你们自己实现了。

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc341_c)     
## 题意
给定一张地图，`#` 表示海洋，`.` 表示陆地。    
高桥现在有一个操作序列，这个操作序列由 `UDLR` 组成，其分别代表上下左右移动。     
高桥现在要按照这个操作序列进行移动，这个过程中的任意时刻都不能在海洋上。求最终可到达的位置的个数。       
## 解法
我们直接枚举起点，每次暴力按照操作序列进行 check 即可。    
时间复杂度 $O(hwn)$，可以通过。   
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=5e2;
int n,m,k,ans;
string s;
char c[N+10][N+10];
il bool check(int x,int y){
	if(c[x][y]=='#'){
		ret 0;
	}
	for(int i=1;i<=k;i++){
		int dx=x,dy=y;
		if(s[i]=='U'){
			dx--;
		}else if(s[i]=='D'){
			dx++;
		}else if(s[i]=='L'){
			dy--;
		}else{
			dy++;
		}
		if(dx<1||dy<1||dx>n||dy>m||c[dx][dy]=='#'){
			ret 0;
		}
		x=dx;
		y=dy;
	}
	ret 1;
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k>>s;
	s="="+s;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ans+=check(i,j);
		}
	}
	write(ans);
	ret 0;
}
```


---

## 作者：filletoto (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc341_c)

# 思路
首先，高桥一开始可能会在这个 $H \times W$ 网格的每一个点，所以我们要用双层 `for` 循环先枚举高桥的当前方格。

然后，如果高桥在该位置上着陆，我们要检查他是否可以按照字符串 $T$ 去行走并且途中不进入大海。

时间复杂度为 $O(HWN)$。

# 代码
[AC记录](https://www.luogu.com.cn/record/147254909)

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,len,ans;
string s[505],g;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>len;
	cin>>g;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='#') continue;
			int x=i;
			int y=j;
			bool flag=true;
			for(int m=0;m<g.size();m++)
			{
				if(g[m]=='L') y--;
		        if(g[m]=='R') y++;
		        if(g[m]=='U') x--;
		        if(g[m]=='D') x++;
				if(s[x][y]=='#')
				{
					flag=false;
					break;
				}
			}
			if(flag) ans++;
		}
	}
	cout << ans << endl;



	return 0;
}
```

---

## 作者：vectorxyz (赞：0)

来一发暴力的题解。

#### 题目分析
很容易发现他的操作没有那么复杂，就是遍利所有非海的点，然后根据他的行动轨迹模拟一遍，如果移动到的点都是陆地，这个点就是一个可能的着陆点。

所以这题不用搜索也行。

值得注意的是，他移动是承接式的，即当前点是 $(x,\ y)$，他进行一次上操作和一次下操作，应该是移动到 $(x - 1, \ y)$ 和 $(x, \ y)$，并不是 $(x - 1, \ y)$ 和 $(x + 1, \ y)$。

#### 代码
```cpp
#include <bits/stdc++.h>

using namespace std;
char a[505][505];int ans;
int main()
{
    int h, w, n;
    cin >> h >> w >> n;

    string s;
    cin >> s;

    for(int i = 1;i <= h;i ++ ){
        for(int j = 1;j <= w;j ++ ){ 
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= h;i ++ ){
        for(int j = 1;j <= w;j ++ ){
            if(a[i][j] == '.'){ // 如果是陆地。
                int f = 0;int x = i, y = j;
                for(int k = 0;k < s.size();k ++ ){ // 开始移动。
                    
                    if(s[k] == 'L'){
                        y -- ;
                    }
                    if(s[k] == 'R'){
                        y ++ ;
                    }
                    if(s[k] == 'U'){
                        x -- ;
                    }
                    if(s[k] == 'D'){
                        x ++ ;
                    }
                    if(a[x][y] == '#'){
                        f = 1;
                        break;
                    } // 如果是海洋，说明不合法，退出。
                }
                if(f == 0) ans ++ ;//如果没碰到海洋，就是可行的点。
            }
        }
    }cout << ans << endl;
    return 0;
}
```

#### 后记
[记录](https://atcoder.jp/contests/abc341/submissions/50350676)。

---

## 作者：Genius_Star (赞：0)

### 题意：

网格中的每个单元格都是**陆地**或**海洋**。

有一个移动序列，从**源点**进行移动，方向可能是 ``LRUD``。

你需要求出有多少个**源点**满足按照移动序列进行移动后，路径的每一个点都是**陆地**。

### 思路：

发现数据范围很小，考虑暴力枚举算法。

枚举**源点** $(i,j)$，然后进行一遍搜索判断是否满足要求。

时间复杂度为 $O(HWN)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=505;
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
ll n,m,t,ans;
ll a[N][N];
ll b[N];
char c;
ll dx[]={0,0,-1,1},dy[]={-1,1,0,0};
bool check(ll x,ll y){
	for(int i=1;i<=t;i++){
		x+=dx[b[i]],y+=dy[b[i]];
		if(x<1||x>n||y<1||y>m)
		  return 0;
		if(a[x][y])
		  return 0;
	}
	return 1;
}
int main(){
	n=read(),m=read(),t=read();
	for(int i=1;i<=t;i++){
		scanf("%c",&c);
		if(c=='L')
		  b[i]=0;
		else if(c=='R')
		  b[i]=1;
		else if(c=='U')
		  b[i]=2;
		else
		  b[i]=3;
	}
	getchar();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%c",&c);
			if(c=='#')
			  a[i][j]=1;
		}
		getchar();
	}
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    if(!a[i][j])
	      if(check(i,j))
	        ans++;
	write(ans);
	return 0;
}
```


---

## 作者：_colin1112_ (赞：0)

## 思路

暴力枚举每一个点，对于每一个点，按照输入指令进行操作，如果移动过程中始终没有到达墙（即 `#` 中），就将答案加 $1$，最后输出答案即可。

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll h, w, n;
char a[1001][1001], op[E];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> h >> w >> n;
    cin >> op;
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
            cin >> a[i][j];
    ll ans = 0;
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; j++)
        {
            if (a[i][j] == '#')
                continue;
            ll x = i, y = j;
            bool flag = 1;
            for (int i = 0; i < n; i++)
            {
                if (op[i] == 'L')
                    y--;
                if (op[i] == 'R')
                    y++;
                if (op[i] == 'U')
                    x--;
                if (op[i] == 'D')
                    x++;
                if (x < 1 || x > h || y < 1 || y > w || a[x][y] == '#')
                    flag = false;
            }
            if (flag)
                ans++;
        }
    cout << ans;
    return 0;
}
```

---

