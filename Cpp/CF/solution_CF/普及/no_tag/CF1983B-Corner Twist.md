# Corner Twist

## 题目描述

You are given two grids of numbers $ a $ and $ b $ , with $ n $ rows and $ m $ columns. All the values in the grid are $ 0 $ , $ 1 $ or $ 2 $ .

You can perform the following operation on $ a $ any number of times:

- Pick any subrectangle in the grid with length and width $ \ge 2 $ . You are allowed to choose the entire grid as a subrectangle.
- The subrectangle has four corners. Take any pair of diagonally opposite corners of the chosen subrectangle and add $ 1 $ to their values modulo $ 3 $ .
- For the pair of corners not picked, add $ 2 $ to their values modulo $ 3 $ .

Note that the operation only changes the values of the corners of the picked subrectangle.

Is it possible to convert the grid $ a $ into grid $ b $ by applying the above operation any number of times (possibly zero)?

## 说明/提示

In the first testcase, grid $ a $ can be converted into $ b $ in the following manner:

 $ \begin{matrix}\fbox{0} & 0 & \fbox{0}\\ 0 & 0 & 0\\ \fbox{0} & 0 & \fbox{0}\end{matrix} \Rightarrow \begin{matrix}1 & 0 & 2\\ 0 & \fbox{0} & \fbox{0}\\ 2 & \fbox{0} & \fbox{1}\end{matrix} \Rightarrow \begin{matrix}1 & 0 & 2\\ \fbox{0} & \fbox{1} & 2\\ \fbox{2} & \fbox{2} & 2\end{matrix} \Rightarrow \begin{matrix}1 & \fbox{0} & \fbox{2}\\ 1 & 0 & 2\\ 1 & \fbox{0} & \fbox{2}\end{matrix} \Rightarrow \begin{matrix}1 & 1 & 1\\ 1 & \fbox{0} & \fbox{2}\\ 1 & \fbox{2} & \fbox{0}\end{matrix} \Rightarrow \begin{matrix}1 & 1 & 1\\ 1 & 1 & 1\\ 1 & 1 & 1\end{matrix} $

Here, in each operation, the top-right and bottom-left corners highlighted by a box are incremented by $ 2 $ modulo $ 3 $ , while the top-left and bottom-right corners are incremented by $ 1 $ modulo $ 3 $ .

In the fourth testcase, it can be proven that it is not possible to convert grid $ a $ into grid $ b $ using the above-mentioned operations any number of times.

## 样例 #1

### 输入

```
7
3 3
000
000
000
111
111
111
4 4
0000
0000
0000
0000
2100
1200
0012
0021
4 4
1020
1200
1210
0000
0000
1200
2200
0000
3 3
012
012
012
010
111
011
8 8
00000000
00000000
00000000
00000000
00000000
00000000
00000000
10000000
00000000
01200000
02010000
00102000
00020100
00001020
00000210
10000000
2 7
0000000
0000000
2220111
0111222
2 7
0000000
0100010
2220111
1210202```

### 输出

```
YES
YES
YES
NO
YES
NO
YES```

# 题解

## 作者：roumeideclown (赞：4)

# 题解：CF1983B Corner Twist

## 题意简述

给出两个 $n \times m$ 的方阵 $a$ 与 $b$，所有方格中的数均为 $0$，$1$ 或 $2$。

你可以对 $a$ 执行以下操作任意多次：

- 选择一个长度与宽度 $\ge 2$ 的子方阵（可以为整个方阵）；
- 选择该子方阵四个角中处于其中一条对角线上的两个角，将它们的值加 $1$ 模 $3$；
- 将剩余两个未选择的角的值加 $2$ 模 $3$。

判断通过上述操作能否将 $a$ 变为 $b$。

## 解法分析

不难发现，任意操作之后，每一行、每一列的值之和不变。这显然是能将 $a$ 变为 $b$ 的必要条件，下面证明充分性。

我们可以通过选择 $2 \times 2$ 的子方阵进行操作的方式将任意一个子方阵变为直接对该子方阵进行操作的结果。例如，对于 $2 \times 3$ 的子方阵，我们可以将两个 $2 \times 2$ 的子方阵组合：

$$ \begin{matrix}1 & \fbox{2+1} & 2\\ 2 & \fbox{1+2} & 1\end{matrix} \equiv \begin{matrix}1 & 0 & 2\\ 2 & 0 & 1\end{matrix} \pmod{3} $$

对于 $n \times m$ 的方阵 $a$ 与 $b$，对于任意 $i \in [1,n-1] $，$j \in [1.m-1]$，可以这样操作：

- 若 $a[i][j] + 1 \equiv b[i][j] \pmod{3}$，将从 $a[i][j]$ 开始的子方阵加上 $\begin{matrix}1 & 2 \\ 2 & 1\end{matrix}$；

- 若 $a[i][j] + 2 \equiv b[i][j] \pmod{3}$，将从 $a[i][j]$ 开始的子方阵加上 $\begin{matrix}2 & 1 \\ 1 & 2\end{matrix}$；

- 否则不进行操作。

可以发现这样进行操作能够满足每行每列之和不变。

综上，$a$ 可以通过题述操作变为 $b$ 的充要条件是 $a$ 与 $b$ 对应的每行每列的值之和在模 $3$ 意义下相等。

## 代码实现

```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
const int N=505;
int n,m,a[N][N],b[N][N];
string s;
void work() {
  //输入
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) {
		cin>>s;
		for(int j=1;j<=m;j++) {
			a[i][j]=s[j-1]-'0';
		}
	}
	for(int i=1;i<=n;i++) {
		cin>>s;
		for(int j=1;j<=m;j++) {
			b[i][j]=s[j-1]-'0';
		}
	}
  //判断是否存在某行或某列值之和不相等的情况
	int suma,sumb;
	for(int i=1;i<=n;i++) {
		suma=sumb=0;
		for(int j=1;j<=m;j++) {
			suma=(suma+a[i][j])%3;
			sumb=(sumb+b[i][j])%3;
		}
     //若不相等
		if(suma!=sumb) {
			printf("NO\n");
			return;
		}
	}
	for(int i=1;i<=m;i++) {
		suma=sumb=0;
		for(int j=1;j<=n;j++) {
			suma=(suma+a[j][i])%3;
			sumb=(sumb+b[j][i])%3;
		}
     //若不相等
		if(suma!=sumb) {
			printf("NO\n");
			return;
		}
	}
  //不存在不相等的情况
	printf("YES\n");
}
int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0),cout.tie(0);
  //多组数据
	int t;scanf("%d",&t);
	while(t--) work();
	return 0;
}

```

---

## 作者：GreenMelon (赞：3)

思路参考了 @Special_Tony 大佬。

---

根据题意，我们可以模拟一下：

假设有一个 $5\times 5$ 的二维数组 $a$，每个数字都为 $0$：

```
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
```

现在，任意一行或任意一列的总和都是 $0$。

然后选择一个 $2\times2$ 的子矩形，完成操作后的矩阵：

```
1 2 0 0 0
2 1 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
```

可以发现，现在任意一行或任意一列的总和模 $3$ 还是 $0$。

得出一个规律：修改后的数组和原数组的任意一行或任意一列的总和模 $3$ 是永远相同的。

根据这个规律一个一个模拟：如果两个数组的同一行或同一列的总和模 $3$ 不相同，就可以直接输出 `NO`。

注意两个数字之间没有空格，所以先用 $\texttt{char}$ 读取数组，在操作时再 `-'0'` 转换成 $\texttt{int}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[505][505];
char b[505][505];
int main(){
	int t;
	cin>>t;
	while(t--){
		
		int n, m;
		cin>>n>>m;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>a[i][j];
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>b[i][j];
			}
		}
		bool is=1;
		for(int i=0;i<n;i++){
			int x=0, y=0;
			for(int j=0;j<m;j++){
				x+=a[i][j]-'0', y+=b[i][j]-'0';
			}
			if(x%3!=y%3) is=0;
		}
		for(int i=0;i<m;i++){
			int x=0, y=0;
			for(int j=0;j<n;j++){
				x+=a[j][i]-'0', y+=b[j][i]-'0';
			}
			if(x%3!=y%3) is=0;
		}
		if(!is) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
} 
```

---

## 作者：_H17_ (赞：2)

## 题目分析

对于一次 $2\times 3$ 的矩阵修改 $\begin{bmatrix}0 & 0 & 0 \\ 0 & 0 & 0 \end{bmatrix}$ 到 $\begin{bmatrix}1 & 0 & 2 \\ 2 & 0 & 1 \end{bmatrix}$，我们可以通过直接修改完成。

考虑到我们可以用 $\begin{bmatrix}1 & 2 \\ 2 & 1 \end{bmatrix}$ 和 $\begin{bmatrix}2 & 1 \\ 1 & 2 \end{bmatrix}$ 来进行修改刚才的矩阵。

我们规定 $\begin{bmatrix}1 & 2 \\ 2 & 1 \end{bmatrix}$ 和 $\begin{bmatrix}2 & 1 \\ 1 & 2 \end{bmatrix}$ 分别为 $1,2$ 号操作。

首先对上面矩阵左侧的 $2\times 2$ 进行 $1$ 操作，然后对右半部分实施 $2$ 操作。

这样就得到了刚才右边的矩阵。

既然 $2\times 2$ 的操作可以推广到 $2\times 3$，同样依次类推也可以推广到 $2\times m$ 进而推广到 $n\times m$。

于是我们得出结论：这需要用 $1,2$ 两种 $2\times 2$ 的矩阵操作即可完成其他的矩阵操作。

于是对于 $a$ 我们寻找 $a_{i,j}(1\le i<n,1\le j<m)$，然后如果 $a_{i,j}=b_{i,j}$，那么跳过；如果 $a_{i,j}+1\equiv b_{i,j}\pmod 3$，那么对  $\begin{bmatrix}a_{i,j} & a_{i+1,j} \\ a_{i,j+1} & a_{i+1,j+1} \end{bmatrix}$ 做 $1$ 操作；同样地如果 $a_{i,j}+2\equiv b_{i,j}\pmod 3$，那么做 $2$ 操作。

这样我们可以把 $a,b$ 的前 $n-1$ 行和 $m-1$ 列变得相同。

然后我们判断剩下的一行一列是否相同即可，不同就不行，相同可以。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[501][501],b[501][501];
void Main(){
	scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%1d",&a[i][j]);//注意无空格
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%1d",&b[i][j]);
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++){
            if(a[i][j]==b[i][j])
                continue;//跳
            if((a[i][j]+1)%3==b[i][j])
                a[i][j]++,a[i+1][j]+=2,a[i][j+1]+=2,a[i+1][j+1]++;// 1 操作
            if((a[i][j]+2)%3==b[i][j])
                a[i][j]+=2,a[i+1][j]++,a[i][j+1]++,a[i+1][j+1]+=2;// 2 操作
            a[i][j]%=3,a[i+1][j]%=3,a[i][j+1]%=3,a[i+1][j+1]%=3;
        }
    for(int i=1;i<=n;i++)
        if(a[i][m]!=b[i][m]){
        	puts("nO");
            return;
        }
    for(int j=1;j<=m;j++)
        if(a[n][j]!=b[n][j]){
        	puts("nO");//不行
            return;
        }
    puts("yEs");//可以
    return;
    puts("H17 is so OP!");
}
int main(){
    for(scanf("%d",&T);T;--T)
        Main();
    return 0;
}
```

---

## 作者：arrow_king (赞：2)

# 题意

给定两个由 $0,1,2$ 组成的 $n\times m$ 的矩阵 $A,B$。你可以对 $A$ 进行任意（可能为 $0$）次如下操作：

- 选择一个子矩阵，然后将左上、右下两个角元素 $+1$、右上左下两个角元素 $+2$。所有操作在 $\bmod 3$ 意义下进行。

问能不能把 $A$ 变成 $B$。$n,m\le500$。

# 分析

首先发现这个操作不好分析，因此我们在前缀和意义下看这个操作。

明显可以发现操作其实就是选择 $R\times C$ 的矩形进行操作后会对 $(R-1)\times(C-1)$ 的矩形前缀和数组加 $1$。

```plain
00000    11110
00000    11110
00000 -> 11110
00000    00000
```

因为选择的矩形是任意的，因此我们大可以将选择的矩形大小置为 $2\times2$，这样在前缀和意义下就是单点加 $1$。

这就说明：我们可以对左上角的 $(n-1)\times(m-1)$ 大小的前缀和部分**任意修改**，因此我们只需要判断最后一行、最后一列两个矩阵前缀和是否相等即可。

# 代码

思路想通之后代码非常好写。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 505
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,m;
int a[N][N],b[N][N];
char s[N];
il void check() {
	for(int i=1;i<=n;i++) if(a[i][m]!=b[i][m]) {printf("NO\n");return;}
	for(int i=1;i<=m;i++) if(a[n][i]!=b[n][i]) {printf("NO\n");return;}
	printf("YES\n");
	return;
}
int main() {
	int t=read();
	while(t--) {
		n=read(),m=read();
		for(int i=1;i<=n;i++) {
			scanf("%s",s+1);
			for(int j=1;j<=m;j++) a[i][j]=s[j]^48;
		}
		for(int i=1;i<=n;i++) {
			scanf("%s",s+1);
			for(int j=1;j<=m;j++) b[i][j]=s[j]^48;
		}
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) {
				a[i][j]=(a[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1]+99)%3;
				b[i][j]=(b[i][j]+b[i-1][j]+b[i][j-1]-b[i-1][j-1]+99)%3;
			}
		}
		check();
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=b[i][j]=0;
	}
	return 0;
}
```

---

## 作者：huhexuan (赞：2)

题意很好理解，建议直接百度翻译，或下载插件。

直接猜结论：按位修改，之后以此为 $2 \times 2$ 矩阵的右上角，修改此矩阵，最后判相等即可。

感性理解一下，每一个矩阵都是由很多小矩阵构成的，保证每一个小矩阵相等，自然就能保证全部相等。

换言之，确定左上角之后是不会影响之前正确答案的，且能保证当前点相等。

最后判一下是否相等，就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m;
char a[505][505],b[505][505];
signed main()
{
	cin>>t;
	while(t--)
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
			}
		}
		bool flag=0;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m;j++)
			{
				if(a[i][j]!=b[i][j])
				{
					int sum=(b[i][j]+3-a[i][j])%3;
					a[i][j]=b[i][j];
					a[i+1][j+1]=char((a[i+1][j+1]-'0'+sum)%3+'0');
					a[i+1][j]=char((a[i+1][j]-'0'+3-sum)%3+'0');
					a[i][j+1]=char((a[i][j+1]-'0'+3-sum)%3+'0');
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(a[i][j]!=b[i][j])
				{
					flag=1;
				}
			}
		}
		if(flag) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;	
}

---

## 作者：白鲟 (赞：1)

注意到可将任意大小的操作分解到 $2\times 2$ 大小的操作，又注意到对于每个 $2\times 2$ 的正方形，不会有第二次操作。因此，从左上角开始顺序扫描每个 $2\times 2$ 的正方形，依据其左上角的信息来进行操作，最后再检查最后一行与最后一列是否满足条件即可。

```cpp
#include <cstdio>
const int maxn = 500;
int T, n, m, x, a[maxn + 1][maxn + 1];
int main() {
    scanf("%d", &T);
    while(T--) {
        bool flag = true;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                scanf("%1d", &a[i][j]);
            }  
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) {
                scanf("%1d", &x);
                a[i][j] = (x + 3 - a[i][j]) % 3;
            }
        for(int i = 1; i < n; ++i)
            for(int j = 1; j < m; ++j) {
                int t = (3 - a[i][j]) % 3;
                a[i][j] = (a[i][j] + t) % 3;
                a[i + 1][j + 1] = (a[i + 1][j + 1] + t) % 3;
                a[i + 1][j] = (a[i + 1][j] + 3 - t) % 3;
                a[i][j + 1] = (a[i][j + 1] + 3 - t) % 3;
            }
        for(int i = 1; i <= n; ++i) {
            if(a[i][m]) {
                flag = false;
                break;
            }
        }
        for(int j = 1; j < m; ++j) {
            if(a[n][j]) {
                flag = false;
                break;
            }
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：Special_Tony (赞：1)

# 思路
显然，不管如何操作，每行、每列之和除以 $3$ 的余数始终不变。所以，我们只要枚举每行、每列，看看和除以 $3$ 的余数是否相同就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, m;
string a[505], b[505];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		for (int i = 0; i < n; ++ i)
			cin >> b[i];
		for (int i = 0, s1, s2; i < n; ++ i) {
			s1 = s2 = 0;
			for (int j = 0; j < m; ++ j)
				s1 += a[i][j] - '0', s2 += b[i][j] - '0';
			if (s1 % 3 != s2 % 3)
				goto no;
		}
		for (int j = 0, s1, s2; j < m; ++ j) {
			s1 = s2 = 0;
			for (int i = 0; i < n; ++ i)
				s1 += a[i][j] - '0', s2 += b[i][j] - '0';
			if (s1 % 3 != s2 % 3)
				goto no;
		}
		cout << "Yes\n";
		continue ;
no:
		cout << "No\n";
	}
	return 0;
}
```

---

## 作者：MrJC_Pandingding (赞：0)

# [题](https://codeforces.com/contest/1983/problem/B)[目](https://www.luogu.com.cn/problem/CF1983B)
# 解题思路
每次操作后，一行中的数 $\bmod 3$ 的值不变，一列中的数 $\bmod 3$ 的值不变。因此，我们只需比较两个矩阵每行的数的和 $\bmod 3$ 的值与每列的数的和 $\bmod 3$ 的值，如果都相同则有解；否则无解。
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=500;
int a[maxn+10][maxn+10];
int b[maxn+10][maxn+10],m,n;
int sumn[14][maxn+10],t;
char s[maxn+10];
int main()
{
	int i,j;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		memset(sumn,0,sizeof(sumn));
		for(i=1;i<=n;++i)
		{
			scanf("%s",s);
			for(j=1;j<=m;++j)
			{
				a[i][j]=s[j-1]-'0';
				sumn[1][i]=(sumn[1][i]+a[i][j])%3;
				sumn[2][j]=(sumn[2][j]+a[i][j])%3;
			}
		}
		for(i=1;i<=n;++i)
		{
			scanf("%s",s);
			for(j=1;j<=m;++j)
			{
				b[i][j]=s[j-1]-'0';
				sumn[3][i]=(sumn[3][i]+b[i][j])%3;
				sumn[4][j]=(sumn[4][j]+b[i][j])%3;
			}
		}
		for(i=1;i<=n;++i)
			if(sumn[1][i]!=sumn[3][i])
				break;
		for(j=1;j<=m;++j)
			if(sumn[2][j]!=sumn[4][j])
				break;
		if(i==n+1&&j==m+1)
			puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：SunsetVoice (赞：0)

抽象的把题目理解成一个对角 $+1$，一个对角 $-1$。

不难发现同一位置连续操作两次实际上相当于原来的基础上加另一个对角。因此证明时无需考虑反向操作。

又：连续的 $2\times 2$ 矩阵中操作相当于操作大矩阵，所以挨个操作即可。

代码思路：挨个消，每行操作不了无解；最后一行时还有剩余无解。其余有解。

---

## 作者：Kendieer (赞：0)

题目传送门：[**\[ 洛谷 \]**](https://www.luogu.com.cn/problem/CF1983B) [**\[CodeForces\]**](http://codeforces.com/problemset/problem/1983/B)

## 题意理解

根据题意，在给定的两个网格中，询问能否若干次操作后从 **A** 网格转化成 **B** 网格。

对于每次操作，我们选取任意一个矩形的 $4$ 个角，使其中一对对角 $+1$，剩余一对对角 $+2$，如果得到的数字大于 $3$，则对 $3$ 取模，此对角可以自由选择。

例如：选择图中任意一个矩形，并且选择左上角和右下角的数字 $+1$，右上角和左下角的数字 $+2$。

$\boxed{0}\boxed{0}\boxed{0}\rarr \boxed{1}\boxed{2}\boxed{0} \\ 
\boxed{0} \boxed{0}\boxed{0}\rarr \boxed{0}\boxed{0}\boxed{0}\\ 
\boxed{0}\boxed{0}\boxed{0}\rarr \boxed{2}\boxed{1}\boxed{0}$

## 分析

### 方阵转化

对于从 **A** 网格转为 **B** 网格，我们只要将对应的格子**添加/减少**对应的差值即可转换成功。

因此，我们可以把题目转化成以下题目：

> 给定一个差值网格，能否经过若干次操作后使网格上所有的值变为 $0$。

### 操作

对于每次操作，我们都需要选取任意一个矩形的四个角进行操作，设一对对角的坐标为 $(x_1,y_1)$ 和 $(x_2,y_2)$，则另一对对角的坐标为 $(x_1,y_2)$ 和 $(x_2,y_1)$。

对于其中一个点 $(x_1,y_1)$ 而言，倘若该点数值 $+1$，则在同一行以及在同一列的其他位置必然存在一个 $+2$ 的点，也就是是说，对于任意一次操作，都使得该列和该行的总和 $+3$。

反之，倘若该点数值 $+2$，同理可得该列和该行的总和 $+3$。

因此，我们可以反证得出：**对于每一次操作，无法使得该行/该列的总和值增加非 $3$ 的整数倍。**

通过上述结论可以进一步得出，无论经过多少次操作，我们只可以将该行或该列的总和增加或减少 $3$ 的整数倍。

### 总结

因此，在给定的 **A** 网格和 **B** 网格中，我们只需将它们每一个网格的差值变为 $0$ 即可。

对于每一行或每一列，当且仅有该行或该列的网格之和为 $3$ 的整数倍时，该行或该列的所有网格才可以都变为 $0$。

## Code

``` cpp 
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(ll i = (a);i < (b);i++)
typedef long long ll;
// 快读
ll qread(){
    int ch = getchar();
    ll r = 0,s = 1;
    while (ch == ' ' || ch == '\r' || ch == '\n')
        ch = getchar();
    if (ch == '-'){
        ch = getchar();
        s = -1;
    }
    while (ch >= '0' && ch <= '9'){
        r = r * 10 + ch - '0';
        ch = getchar();
    }
    return r * s;
}

// 用于读取单个非空字符
char readChar(){ 
    int ch = getchar();
    while (ch == ' ' || ch == '\r' || ch == '\n')
        ch = getchar();
    return ch;
}

template <typename ... Args>
void qread(Args&&... e){
    ((e = qread()), ...);
}

const int maxn = 1e9 + 7;
const int mod = 998244353;

void solve(){
    int n,m;
    qread(n,m);
    int arr1[n][m],arr2[n][m];
    rep(i,0,n){
        rep(j,0,m){
            arr1[i][j] = readChar() - '0';
        }
    }
    bool flag = 1; // 记录是否成功
    rep(i,0,n){
        ll tot = 0; // 顺便判断每一行的总和
        rep(j,0,m){
            tot += (arr2[i][j] = (readChar() - '0' - arr1[i][j] + 3) % 3);
        }
        if (tot % 3 != 0){
            flag = 0; // 结束之后不要return，要把数据读完。
        }
    }
    if (flag){
        rep(j,0,m){
            ll tot = 0;
            rep(i,0,n){
                tot += arr2[i][j];
            }
            if (tot % 3 != 0){
                flag = 0;
                break;
            }
        }
    }
    cout << (flag ? "YES" : "NO") << endl;
}

int main(){
   int n = qread();
   while(n--)
    solve();
    return 0;
}
```

## 后言

这是本蒟蒻第一个题解，有什么错误请指出，阿里嘎多~

---

## 作者：GoldenCreeper (赞：0)

注意到如果 $a$ 可以转换成 $b$，那么 $b$ 数组的每一行和每一列的和与 $a$ 数组的每一行和每一列模 $3$ 的值相等，因为执行运算中不会影响模 $3$ 意义下的值。即此命题是原命题的充分条件。

下面通过构造出一种方法，来证明此条件为必要条件。

依次取 $i = 1,2,\cdots,n-1,j = 1,2,\cdots,n-1$，

- 如果 $a_{i,j}+1\equiv b_{i,j}\pmod3$ 那么在把 $\begin{matrix} a_{i,j} & a_{i+1,j} \\ a_{i,j+1} &a_{i+1,j+1}\end{matrix}$ 设为 $\begin{matrix} a_{i,j}+1 & a_{i+1,j}+2 \\ a_{i,j+1}+2 &a_{i+1,j+1}+1\end{matrix}$，这样可以保证 $a_{i,j}=b_{i,j}$；
- 如果 $a_{i,j}+2\equiv b_{i,j}\pmod3$ 那么在把 $\begin{matrix} a_{i,j} & a_{i+1,j} \\ a_{i,j+1} &a_{i+1,j+1}\end{matrix}$ 设为 $\begin{matrix} a_{i,j}+2 & a_{i+1,j}+1 \\ a_{i,j+1}+1 &a_{i+1,j+1}+2\end{matrix}$，这样可以保证 $a_{i,j}=b_{i,j}$。

这样就可以保证对于所有的 $i = 1,2,\cdots,n-1,j = 1,2,\cdots,n-1$，均有 $a_{i,j}=b_{i,j}$。

因为操作不改变模 $3$ 意义下的值，上面已经保证了 $b$ 的每一行和每一列的和与 $a$ 的每一行和每一列模 $3$ 的值相等，所以有 $a=b$。

所以只需判断每一行或列的和模 $3$ 的值是否相等即可。

代码难度不大，就不放了。

---

## 作者：DrAlfred (赞：0)

摘要：数学

[传送门：https://www.luogu.com.cn/problem/CF1983B](https://www.luogu.com.cn/problem/CF1983B)

## 题意

给定两个长为 $n$，宽为 $m$ 的初始矩阵 $a$ 和目标矩阵 $b$（$0 \le a_{i, j}, b_{i, j} \le 2$）。你可以进行若干次操作。每次操作，你可以选择一个长宽都大于等于 $2$ 的一个 $a$ 的子矩阵，选择四个角中任意两个不相邻的角并将它们的值加 $1$ 模 $3$。同时对于剩下的两个角，将它们的值加 $2$ 模 $3$。问是否可能进行若干次操作，使得初始矩阵 $a$ 变为目标矩阵 $b$？若可以输出 `YES`，否则输出 `NO`。

## 分析思路

我们注意到无论怎么操作，每一行和每一列的和模 $3$ 的余数不变。所以 $a$ 和 $b$ 每一行和每一列的和相同是一个必要条件。下证这也是一个充分条件。

注意到任何大小的操作都可以由 $2 \times 2$ 的基础操作得到，如：

$$
\left[ \begin{array}{cc} 1 & 2 \\ 2 & 1  \end{array}\right] + \left[ \begin{array}{cc} 1 & 2 \\ 2 & 1  \end{array}\right] = \left[ \begin{array}{cc} 1 & 2 + 1 & 2 \\ 2 & 1 + 2 & 1 \end{array}\right] \equiv \left[ \begin{array}{cc} 1 & 0 & 2 \\ 2 & 0 & 1 \end{array}\right] \pmod 3
$$

那我们可以贪心地进行如下操作：

- 若 $a_{i, j} + 1 \equiv b_{i, j} \pmod 3$，则以 $a_{i, j}$ 为左上角叠加 $\left[ \begin{array}{cc} 1 & 2 \\ 2 & 1  \end{array}\right]$；
- 若 $a_{i, j} + 2 \equiv b_{i, j} \pmod 3$，则以 $a_{i, j}$ 为左上角叠加 $\left[ \begin{array}{cc} 2 & 1 \\ 1 & 2  \end{array}\right]$；
- 若 $a_{i, j} \equiv b_{i, j} \pmod 3$，不进行任何操作。

容易发现这样总能使得前 $n - 1$ 行中的前 $m - 1$ 列保持相等。由于上述操作之后，每一行和每一列的和模 $3$ 都不变，剩下 $n + m - 1$ 个元素的值可以通过之前每一行和每一列的和唯一确定，而它们要想等，所以这是一个充分条件。

时间复杂度 $O\left(nm\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 510;
char a[N][N], b[N][N];
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
inline void solve(void) {
    int n, m;
    cin >> n >> m;
    vector<int> sal(n), sbl(n);
    vector<int> sac(m), sbc(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            sal[i] += a[i][j] ^ 48;
            sac[j] += a[i][j] ^ 48;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[i][j];
            sbl[i] += b[i][j] ^ 48;
            sbc[j] += b[i][j] ^ 48;
        }
    }
    for (int i = 0; i < n; i++) {
        if (sal[i] % 3 != sbl[i] % 3) {
            cout << "NO\n";
            return;
        }
    }
    for (int i = 0; i < m; i++) {
        if (sac[i] % 3 != sbc[i] % 3) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}
int main(int argc, char const *argv[]) {
    int t = 1;
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

