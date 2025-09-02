# [ICPC 2020 Shanghai R] Mine Sweeper II

## 题目描述

A mine-sweeper map $X$ can be expressed as an $n\times m$ grid. Each cell of the grid is either a mine cell or a non-mine cell. A mine cell has no number on it. Each non-mine cell has a number representing the number of mine cells around it. (A cell is around another cell if they share at least one common point. Thus, every cell that is not on the boundary has $8$ cells around it.) The following is a $16\times 30$ mine-sweeper map where a flagged cell denotes a mine cell and a blank cell denotes a non-mine cell with number 0.

![](https://cdn.luogu.com.cn/upload/image_hosting/5bykwzuy.png)

Given two mine-sweeper maps $A, B$ of size $n\times m$, you should modify at most $\left\lfloor\frac{nm}{2}\right\rfloor$ (i.e. the largest nonnegative integer that is less than or equal to $\frac{nm}{2}$) cells in $B$ (from a non-mine cell to a mine cell or vice versa) such that the sum of numbers in the non-mine cells in $A$ and the sum of numbers in the non-mine cells in $B$ are the same. (If a map has no non-mine cell, the sum is considered as $0$.)

If multiple solutions exist, print any of them. If no solution exists, print ``-1`` in one line.

## 说明/提示

We modify one cell in $B$. Then the sums of the numbers on non-mine cells in $A$ and $B$ both equal $10$.

## 样例 #1

### 输入

```
2 4
X..X
X.X.
X.X.
.X..```

### 输出

```
X.XX
.X..```

# 题解

## 作者：Vct14 (赞：5)

### 题目大意

给定两张 $n\times m$ 的扫雷地图 $A$ 和 $B$，请你改变 $B$ 图中的 $\lfloor \dfrac{nm}{2} \rfloor$ 个格子，使两张图上的非地雷格上的数字（周围 $8$ 个格子中的地雷数）之和相同。若有解，输出修改后的 $B$ 图；若无解，输出 $-1$。

### 结论

定义一个图 $X$ 的“反地图”为将 $X$ 中的地雷格替换为非地雷格，非地雷格替换为地雷格的扫雷地图 $X_2$。

将 $B$ 改为 $A$ 或 $A$ 的反地图 $A_2$ 即可。没有无解的情况。

### 证明

1. $A$ 或 $A$ 的反地图 $A_2$ 两张图上的非地雷格上的数字之和相同。

对于相邻的两个格子：

- 若其中一个为地雷格，另外一个为非地雷格，则它的贡献为 $1$，反转后的贡献也为 $1$，所以它们的贡献相同。
- 若两个格子相同，则它们的贡献均为 $0$，也相同。

综上，任意两个相邻的格子都可以取反，取反后贡献不变。

因此，$A$ 或 $A$ 的反地图 $A_2$ 两张图上的非地雷格上的数字之和相同。

2. 将 $B$ 改为 $A$ 或 $A$ 的反地图 $A_2$ 所需的修改次数不大于 $\lfloor \dfrac{nm}{2} \rfloor$。

设 $A$ 和 $B$ 有 $k$ 个格子不同，即将 $B$ 改为 $A$ 需要修改 $k$ 次：

因为 $A$ 与 $A_2$ 所有格子都不同，所以 $B$ 与 $A_2$ 有 $nm-k$ 个格子不同，需要修改 $nm-k$ 次。

那么题目可化为证明 $k$ 和 $nm-k$ 中必有一数不大于 $\lfloor \dfrac{nm}{2} \rfloor$。这是显然的。

所以将 $B$ 改为 $A$ 或 $A$ 的反地图 $A_2$ 所需的修改次数不大于 $\lfloor \dfrac{nm}{2} \rfloor$。

### 代码

```c++
#include<bits/stdc++.h>
using namespace std;

int getbomb(){
	char bomb;
	cin>>bomb;
	if(bomb=='X') return 1;
	else return 0;
} 

void outbomb(bool b){
	if(b) cout<<"X";
	else cout<<".";
}

bool a[1002][1002];

int main(){
	int n,m;
	cin>>n>>m;
	int k=0;
	for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) a[i][j]=getbomb();
	for(int i=1; i<=n; i++) for(int j=1; j<=m; j++) if(getbomb()!=a[i][j]) k++;
	if(k<=n*m/2){
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++) outbomb(a[i][j]);
			cout<<"\n";
		}
	} 
	else{
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++) outbomb(!a[i][j]);
			cout<<"\n";
		}
	} 
	return 0;
}
```

---

## 作者：chen_zhe (赞：4)

以下内容转载自官方题解：

考虑数字和就等于相邻（雷格子，非雷格子）二元组的个数，于是把整个地图全反过来这个二元组个数不变，然后 $B$ 与 $A$ 之间以及 $B$ 与 $inv(A)$，即把 $A$ 所有格子全部取反的扫雷地图之间总有一个偏差不超过一半的，所以就选其中偏差不超过一半的然后变过去就行。

---

## 作者：yhx0322 (赞：2)

## Description
给出两张尺寸均为 $n\times m$ 的扫雷地图 $A,B$。每次修改可以将一个地雷格改为非地雷格，或者将一个非地雷格改为地雷格。你可以修改最多 $\lfloor \dfrac{nm}{2} \rfloor$ 个地图 $B$ 中的格子，请给出一种方案，使得 $A,B$ 中非地雷格上数字之和相同。若无解，输出 $-1$。
## Solution
简单来说，就是构造出两张图，差异在 $\lfloor \dfrac{nm}{2} \rfloor$ 之内。

如果差异在 $\lfloor \dfrac{nm}{2} \rfloor$ 之内，直接输出就好了。

对于其他情况，我们分析得出，**如果把图返过来，一定满足两张图的差异在 $\lfloor \dfrac{nm}{2} \rfloor$ 之内。**

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
char a[N][N], b[N][N];
int n, m;
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	int c = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			c += (a[i][j] != b[i][j]); // 统计差异的次数
		}
	}
	if (c > (n * m >> 1)) { // 如果差异超过 n * m >> 1，将 A 改成反图
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (a[i][j] == '.') a[i][j] = 'X';
				else a[i][j] = '.';
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << a[i] << endl;
	}
	return 0;
}
```

---

## 作者：ZLRest (赞：1)

### 题目大意
给定两个扫雷图，通过 $\tfrac{nm}{2}$ 以内次操作使 B 图上的非雷格上的数字之和等于 A 图的数字之和。
### 分析
可以很轻松发现当两图差异小于等于 $\tfrac{nm}{2}$ 时，只要输出 A 图就可以了。当两图差异大于 $\tfrac{nm}{2}$ 时，不难发现一个性质，一个扫雷图的反图和原图数字和相等，而取反后差异就变为了 $nm-\tfrac{nm}{2}$ 一定小于 $\tfrac{nm}{2}$，所以直接输出 A 的反图就可以了。

~~-1 是诈骗呜呜。~~
### CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
char a[1100][1100],b[1100][1100];
signed main(){
	cin>>n>>m;
	int cnt=0;
	for(int i=0;i<n;i++) 
		cin>>a[i];
	for(int i=0;i<n;i++) 
		cin>>b[i];
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++) 
		if(a[i][j]!=b[i][j]) cnt++;
		if(cnt<=n*m/2){
			for(int i=0;i<n;i++) 
				cout<<a[i]<<endl;
		}
		else{
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){
					if(a[i][j]=='.') cout<<'X';
					else cout<<".";
									}
					cout<<'\n';
			}
			
		}
}
```


---

## 作者：Nuyoah_awa (赞：1)

比较水的一道构造题，本题解补充对于反图数字和相同的证明。

### 题目大意

给定两个扫雷地图，请你修改小于等于 $\lfloor \dfrac{nm}{2} \rfloor$ 次 $B$ 图，使得 $B$ 图的数字和与 $A$ 图的数字和相同。

### 题目分析

简化题目，说白了就是让我构造出一个数字和与 $A$ 图相同且与 $B$ 图差异在 $\lfloor \dfrac{nm}{2} \rfloor$ 以下的地图。

我们先来想简单的，如果 $A$ 图与 $B$ 图差异在 $\lfloor \dfrac{nm}{2} \rfloor$ 以下，那么我们直接输出 $A$ 图就好了。

但是如果反之，我们如何构造呢？

我们尝试找出一种通解，使得所有图都适用，于是我们观察数字和的由来。

我们可以将每个数字看为它周围地雷对他的贡献，而每个地雷也会对它周围产生贡献。

我们发现上述两句话似乎有些相似，容易想到，我们可以反向建立贡献，即我们也可以将所有非地雷格视为地雷，它们对周围产生贡献，发现贡献值是不变的，即数字和不变。

根据这个性质，我们发现一个图的反图与原图的贡献是一样的，并且若一个图与 $B$ 图的差异为 $x$，那么容易发现，这个图反图与 $B$ 图的差异为 $nm - x$。于是，当 $x \ge \lfloor \dfrac{nm}{2} \rfloor$ 的情况下，$nm - x \le \lfloor \dfrac{nm}{2} \rfloor$，所以我们就已经找到通解了，即 $A$ 图的反图。

所以，当 $A$ 图与 $B$ 图差异在 $\lfloor \dfrac{nm}{2} \rfloor$ 以下，那么我们直接输出 $A$ 图，否则输出 $A$ 图的反图。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define int long long

using namespace std;

const int N = 1e3 + 5;
int n, m, sum;
string s[N], t[N];

signed main()
{
	scanf("%d %d", &n, &m);
	for(int i = 1;i <= n;i++)
	{
		cin >> s[i];
		s[i] = "#" + s[i];
	}
	for(int i = 1;i <= n;i++)
	{
		cin >> t[i];
		t[i] = "#" + t[i];
	}
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
			if(s[i][j] != t[i][j])
				sum++;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= m;j++)
			if(sum > n * m / 2)
				cout << (s[i][j] == '.' ? 'X' : '.');
			else
				cout << s[i][j];
		puts("");
	}
	return 0;
}
```

---

## 作者：sfqxx1 (赞：1)

## 题意

给出两张尺寸均为 $n\times m$ 的扫雷地图 $A,B$。每次修改可以将一个地雷格改为非地雷格，或者将一个非地雷格改为地雷格。你可以修改最多 $\lfloor \dfrac{nm}{2} \rfloor$ 个地图 $B$ 中的格子，请给出一种方案，使得 $A,B$ 中非地雷格上数字之和相同。若无解，输出 $-1$。

## 思路

这题肯定有解，所以 `-1` 一定是错的。

观察题目，显然若 $A$ 图与 $B$ 图的差异小于 $\lfloor \dfrac{nm}{2} \rfloor$ 时，直接输出 $A$ 图即可，反之输出 $A$ 的反图，即把 $A$ 图的地雷改成非地雷格，非地雷格改成地雷格。

## 代码
```
#include<bits/stdc++.h> 

using namespace std;

int ma,n,m,cnt;

char a[1010][1010],b[1010][1010];

int main() {

    scanf("%d%d",&n,&m);

    ma=n*m/2;

    for (int i=0;i<n;i++) scanf("%s",a[i]);

    for (int i=0;i<n;i++) scanf("%s",b[i]);

    for (int i=0;i<n;i++) 

    {

        for (int j=0;j<m;j++) 

        if (a[i][j]!=b[i][j]) cnt++;

    }

    if(cnt<=ma)

    {for(int i = 0; i < n; i++) 

    printf("%s\n", a[i]);

    }

    else {

        for(int i=0;i<n;i++) 

        { for(int j=0;j<m;j++) 

        { if(a[i][j]=='.') printf("X"); 

        else printf(".");

        }

        printf("\n");

        }

    }

    return 0;

}
```



---

## 作者：FreedomKing (赞：1)

### 思路

首先需要明确的一个非常关键的性质是，若我们将某个矩阵全部取反得到一个反矩阵 C，C 所产生的贡献是不变的，这个读者自证不难。

有了这个至关重要的性质这道题就直接迎刃而解了。不难发现一个神奇的结论，若矩阵 A 与 矩阵 B 之间的“差异” $>\left\lfloor\dfrac{nm}{2}\right\rfloor$，那么矩阵 A 的反矩阵 C 必然与矩阵 B 的差异 $<\left\lfloor\dfrac{nm}{2}\right\rfloor$。

证明：由于 C 是 A 的反矩阵，所以若某个点 $b_{i,j}$ 与 $a_{i,j}$ 不同，那么一定与 $c_{i,j}$ 相同，也就是说 A 与 B 的差异加上 C 与 B 的差异就等于 $nm$，所以无论如何一定存在一个矩阵与 B 的差异 $\le\left\lfloor\dfrac{nm}{2}\right\rfloor$。

所以其实根本没有输出 $-1$ 的情况。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+5;
int n,m,t,k;
char a[N][N],b[N][N];
inline int qread(){
#define qr qread()
	int x=0,c=getchar(),t=1;
	while(c<'0'||c>'9'){
		if(c=='0') t=0;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return (t?x:-x);
}
signed main(){
	n=qr;m=qr;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>b[i][j];
			if(a[i][j]!=b[i][j]) k++;
		}
	if(k<=n*m/2){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) cout<<a[i][j];
			puts("");
		}
	}
	else{
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(a[i][j]=='X') cout<<".";
				else cout<<"X";
			}
			puts("");
		}
	}
	return 0;
}
```

---

## 作者：Lovely_Elaina (赞：1)

一道诈骗题。

手动模拟样例易得，如果 $A$ 和 $B$ 的差异小于 $\lfloor {nm\over 2}\rfloor$，则直接输出 $A$ 即可，否则将 $A$ 中所有元素取反（地雷格变成非地雷格，非地雷格变成地雷格）输出即可。

时间复杂度为 $O(nm)$ 可过。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;
const int N = 1005;

int n,m,cnt;
bool a[N][N];
bool b[N][N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
    
    cin >> n >> m;
    
    char input;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> input;
            a[i][j] = (input == 'X');
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> input;
            b[i][j] = (input == 'X');
            cnt += (a[i][j] != b[i][j]);
        }
    }
    
    if(cnt > n*m/2){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                a[i][j] = !a[i][j];
            }
        }
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++)
            cout << (a[i][j]?'X':'.');
        cout << endl;
    }
	return 0;
}
```

---

## 作者：BetterGodPig (赞：0)

首先，对于每个格子，只有两种状态，数字与地雷。

那么就有一个显而易见的性质：如果答案矩阵中某个元素与 $\text{A}$ 不同，那么一定与 $\text{B}$ 相同，定义 $f(A,B)$ 为将 $\text{B}$ 矩阵转成 $\text{A}$ 的操作数量，也就是两个矩阵不同元素的数量，在令矩阵 $\text{C}$ 为每一个元素都与 $\text{A}$ 不同的一个矩阵，显然有 $f(A,B)+f(C,B) = n\times m$，所以 $f(A,B)$ 与 $f(C,B)$ 必定有一个小于 $\lfloor \frac{n\times m}{2} \rfloor$，那么做法就出来了，统计 $\text{A}$ 与 $\text{B}$ 中不同的数量，如果少于 $\lfloor \frac{n\times m}{2} \rfloor$ 就输出 $\text{A}$，否则输出 $\text{B}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e3+5;
int n,m;
char mp1[maxn][maxn],mp2[maxn][maxn];
int cnt;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>m;
    for(int i(1);i <= n;++i){
        cin>>(mp1[i]+1);
    }
    for(int i(1);i <= n;++i){
        cin>>(mp2[i]+1);
        for(int j(1);j <= m;++j){
            if(mp1[i][j] != mp2[i][j]) ++cnt;
        }
    }
    if(cnt <= n*m/2){
        for(int i(1);i <= n;++i){
            for(int j(1);j <= m;++j){
                cout<<mp1[i][j];
            }
            cout<<'\n';
        }
    }else{
        for(int i(1);i <= n;++i){
            for(int j(1);j <= m;++j){
                if(mp1[i][j] == 'X'){
                    cout<<'.';
                }else{
                    cout<<'X';
                }
            }
            cout<<'\n';
        }
    }
    return 0;
}
```


---

## 作者：ethan0328 (赞：0)

## 思路

首先发现一个重要性质，一幅图中数字和等于其反图的数字和。反图指把雷变非雷，非雷变雷。

你考虑每个非雷的的贡献为其相邻雷数。而雷会使其相邻非雷格子的数加 $1$，所以雷的贡献是其周围非雷的个数。就能推出上面的结论。

因为只要求操作次数小于一半，所以如果直接使两个序列相同的步数小于一半，则直接让两个相等。

不然的话，把图变为反图的操作次数小于一半，所以变为反图。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,m,ans1,ans2;
char a[N][N],b[N][N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>b[i][j];
			if(b[i][j]!=a[i][j])
			{
				ans1++;
			}else
			{
				ans2++;
			}
		}
	}
	if(ans1>ans2)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]=='X')
				{
					a[i][j]='.';
				}else
				{
					a[i][j]='X';
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cout<<a[i][j];
		}
		cout<<endl;
	}
}
```


---

## 作者：zhaohanwen (赞：0)

### 题目分析

肯定有解，`-1` 是拿来诈骗的。

如果 $A$ 图和 $B$ 图的差异小于 $\frac{mn}{2}$，那么直接输出 $A$ 图就行了。

如果 $A$ 图和 $B$ 图的差异大于 $\frac{mn}{2}$，怎么办呢？

我们可以发现一个重要的性质，就是把这样一个图取反之后，数字和还是可以弄成一样的。

然而如果 $A$ 图和 $B$ 图的差异大于 $\frac{mn}{2}$，那么 $A$ 的反图和 $B$ 的差异一定小于 $\frac{mn}{2}$，所以输出 $A$ 的反图即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define R(i,n) for(int i=1;i<=n;i++)
const int N=1e3+5;
char s1[N][N], s2[N][N];
void solve()
{
	int n, m, cnt = 0;
	cin>>n>>m;
	R(i,n)
		scanf("%s",s1[i]+1);
	R(i,n)
		scanf("%s",s2[i]+1);
	R(i,n)
		R(j,m)
			s1[i][j] = (s1[i][j] == 'X' ? '.' : 'X');
	R(i,n)
		R(j,m)
			if (s1[i][j]!=s2[i][j]) cnt++;
	if (cnt > n * m / 2)
	{
		R(i,n)
		{
			R(j,m)
				if (s1[i][j] == '.') putchar('X');
				else putchar('.');
			putchar('\n');
		}
		return;
	}
	for (int i = 1; i <= n; i++) printf("%s\n",s1[i]+1);
}
int main()
{
	solve();
	return 0;
}
```


---

