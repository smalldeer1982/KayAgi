# Switches and Lamps

## 题目描述

You are given $ n $ switches and $ m $ lamps. The $ i $ -th switch turns on some subset of the lamps. This information is given as the matrix $ a $ consisting of $ n $ rows and $ m $ columns where $ a_{i,j}=1 $ if the $ i $ -th switch turns on the $ j $ -th lamp and $ a_{i,j}=0 $ if the $ i $ -th switch is not connected to the $ j $ -th lamp.

Initially all $ m $ lamps are turned off.

Switches change state only from "off" to "on". It means that if you press two or more switches connected to the same lamp then the lamp will be turned on after any of this switches is pressed and will remain its state even if any switch connected to this lamp is pressed afterwards.

It is guaranteed that if you push all $ n $ switches then all $ m $ lamps will be turned on.

Your think that you have too many switches and you would like to ignore one of them.

Your task is to say if there exists such a switch that if you will ignore (not use) it but press all the other $ n-1 $ switches then all the $ m $ lamps will be turned on.

## 样例 #1

### 输入

```
4 5
10101
01000
00111
10000
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 5
10100
01000
00110
00101
```

### 输出

```
NO
```

# 题解

## 作者：ztyo_zysclown (赞：3)

我的思路：因为一个灯
可能被多个开关控制，所以只要存在一个这样的灯，任意去掉一个开关，仍然成立。
### 代码
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define zyto_zysclown return 0
int n,m;
int qwe[111000];//判断每个灯有多少个开关相连。 
char op[5500][5500];
signed main(){
	cin>>n>>m;
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
            cin>>op[i][j];
            if(op[i][j]=='1'){
            	qwe[j]++;
			}
        }
	} 
    for(int i=1;i<=n;i++){
        bool b=false;;
        for(int j=1;j<=m;j++){
        	if(op[i][j]=='1'&&qwe[j]==1){
        		b=true;
			}
		}
        if(!b){
			cout<<"YES";
			return 0;
		}
    }
    cout<<"NO";
    zyto_zysclown;
}
```


---

## 作者：AutumnKite (赞：2)

[我的博客](https://www.cnblogs.com/rill7747/p/9094088.html)

## 题意

有$n$个开关和$m$盏灯,给定一个矩阵$a(a_{i,j}\in [0,1])$,若$a_{i,j}=1$则说明开关$i$与第$j$盏灯连接.初始时所有灯都是关闭的.按下某开关后,所有与这个开关连接的灯将会打开,已经打开的不会关闭.

现在你需要去掉一个开关,使得按下剩余$n-1$个开关后,所有灯都可以打开.若存在方案,则输出`YES`,否则输出`NO`.

## 题解

直观的想法为,枚举去掉的开关$i$,然后枚举每个与开关$i$相连的灯$j$,若存在一个$j$只能靠开关$i$打开(即矩阵第$j$列只有第$i$行为$1$),那么说明$i$不能去掉.

但是这是$\mathcal O(n^3)$的.

优化很简单,我们可以发现我们枚举了很多次某一列.直接记录$cnt_j$表示第$j$列中$1$的个数,也即第$j$盏灯连接这的开关数.

在判断时,直接判断$cnt_j$是否等于$1$即可.

时间复杂度$\mathcal O(n^2)$

## 代码

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cctype>
using namespace std;
const int N = 2005;
int n, m, cnt[N];
char a[N][N];
int main(){
    scanf("%d%d", &n, &m);
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            while (!isdigit(a[i][j] = getchar()));
    for (register int i = 1; i <= n; ++i)
        for (register int j = 1; j <= m; ++j)
            cnt[j] += a[i][j] ^ '0'; // 统计cnt
    for (register int i = 1; i <= n; ++i){
        register bool bo = true;
        for (register int j = 1; j <= m; ++j)
            if (a[i][j] == '1' && cnt[j] == 1) bo = false; // 直接判断即可
        if (bo) return printf("YES"), 0;
    }
    return printf("NO"), 0;
}
```

---

## 作者：xiaozeyu (赞：1)

[CF985B Switches and Lamps](https://www.luogu.com.cn/problem/CF985B)

题目会给出一个矩阵来表示每盏灯泡与其他灯泡的控制关系。

要我们求出是否能在去掉一盏灯之后使剩下的灯中有一盏灯通过控制其他的灯逐步控制剩下的所有灯。

我们可能可以通过 bfs 之类的方法来求，但不一定好写，时间不一定够用。

我们可以直接枚举。

与其说判断是否能从一个点出发满足条件，不如去判断一个点是否对联通是不可少的。

那我们只要统计一下每个点的入度，若一个点的入度为一，那有连向这个点的边的点一定是不可以去掉的，因为去掉后原本这个点连向的点就会入度为零而无法被控制。

那么我们就直接在读入时更新入度，再直接枚举每一条边判断一下入度以及连通性就行。

代码如下。

---

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define f(a) ((a)*(a))
#define p(x) printf("%lld ",(x))
#define P() puts("")
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=2010;
const int maxm=100010;
int n,m,d[maxm];
char a[maxn][maxn];
signed main()
{
	n=read();m=read();
	For(i,1,n)
		For(j,1,m)
		{
			a[i][j]=getchar();
			while(!isdigit(a[i][j])) a[i][j]=getchar();
			if(a[i][j]=='1') d[j]++;
		}
	bool flag;
	For(i,1,n)
	{
		flag=true;
		For(j,1,m) if(d[j]==1&&a[i][j]=='1') flag=false;
		if(flag)
		{
			puts("YES");
			return 0;	
		}
	}
	puts("NO");
}
```


---

感谢管理员的审核。

---

## 作者：chenyanbing2023 (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF985B)

### 基本思路

首先统计每个灯被按了几次，然后枚举每个开关，把这个开关的贡献去掉，判断是否所有灯的次数大于等于 1，然后再恢复这个开关的贡献。

### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[2005];
string s[2005];
int n,m;
int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>s[i];
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='1')
			{
				vis[j]++;
			}
		}
	}
	bool flag1=false;//判断是否可以去掉
	for(int i=0;i<n;i++)
	{
		bool flag2=false;
		for (int j=0;j<m;j++)
		{
			if (s[i][j]=='1')
			{
				vis[j]--;
			}
			if(vis[j]==0)
			{
				flag2=true;
			}
		}
		if(!flag2)
		{
			flag1=true;
		}
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='1')
			{
				vis[j]++;
			}
		}
	}
	if(flag1)
	{
		cout<<"Yes\n";
	}
	else
	{
		cout<<"No\n";
	}
	return 0;
}
```


---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF985B)

### [题意解析]
给你一个 $n \times m$ 的二维矩阵，$a[i][j]$ 表示第 $i$ 个灯能够控制第 $j$ 个灯。题目想求得就是能否去掉其中一盏灯后，其余灯都能正常打开。

### [思路分析]
既然能把其中一盏灯去掉，那就说明这盏灯能被其他灯打开，那我们的思路就很清晰了，求出每盏灯能被其他的几盏灯打开，**如果这一盏灯只能被某 $1$ 盏特定的灯打开那这一盏灯就无法被去掉**。否则就可以被去掉。

### [贴上代码]
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,sum[2010];
char a[2010][2010];
int main() {
	cin>>n>>m;
	for(int i=1; i<=n; i++) 
		for(int j=1; j<=m; j++)
			cin>>a[i][j],sum[j] += a[i][j] - '0';
			/*读入这个二维矩阵，并求出每一盏灯能被其他的几盏灯打开。*/
	for(int i=1; i<=n; i++){
		bool flag = 0;
		/*初始化*/
		for(int j=1; j<=m; j++)
			if(a[i][j] == '1' && sum[j] == 1) flag = 1;
			/*如果这盏灯只能被一个灯打开，那就不能去掉*/
		if(!flag) {cout<<"YES"; return 0;}
		/*找到了可以去掉的灯*/
	}
	cout<<"NO";
	/*找不到*/ 
	return 0;
}
```


---

## 作者：Rainbow_Sky (赞：0)

## 思路

这一题算是比较简单的模拟题了，对于每一盏灯，如果一盏灯控制了另一盏灯，且那盏灯只受这盏灯的控制，那么自然就不行，不然就直接输出 `YES`，结束程序。知道循环结束，直接输出 `NO`。

## AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxm=1e5+10;
const int maxn=1e3+10;
const int mod=1e9+7;
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
string s[maxm];
int a[maxm];
signed main()
{
	int n=read();
	int m=read();
	for(int i=0;i<n;i++) cin>>s[i];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='1') a[j]++;
		}
	}
	for(int i=0;i<n;i++)
	{
		bool flag=1;
		for(int j=0;j<m;j++)
		{
			if(s[i][j]=='1'&&a[j]==1) flag=0;
		}
		if(flag)
		{
			cout<<"YES";
			exit(0);
		 } 
	}
	cout<<"NO";
	return 0;
}

```

---

## 作者：Zq_water (赞：0)

思路很简单，用 $cnt$ 数组记录每个灯可以被打开的开关数，如果一个灯只能被一个开关控制，则那个开关不能去掉。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,cnt[2005];
char mp[2005][2005];
int main(){
	cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='1') cnt[j]++;
        }
    
    for(int i=1;i<=n;i++){
        bool f=0;
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='1'&&cnt[j]==1) f=1;
        if(!f){cout<<"YES";return 0;}
    }
    cout<<"NO";
    return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF985B)

一道枚举题。

首先我们需要知道什么开关才能被去掉，题目要求去掉这个开关后所有的灯依然能够开启。也就是说，**这个开关能打开的所有灯都可以由其它开关代替**。

思路清晰了，就比较好做。我们可以用一个数组存储下每一盏灯可以被几个开关开启，如果有一盏灯只能被 $1$ 个开关所开启，则那个开关不能被去掉。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, m;
char a[2005][2005];
int cnt[2005]; // cnt[i] 表示有多少个开关可以打开第 i 盏灯
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if (a[i][j] == '1') cnt[j]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        bool flag = 0;
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '1') {
                if (cnt[j] == 1) flag = 1; // 这个开关是不可去掉的
            }
        }
        if (!flag) {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
```


---

## 作者：Creative_sad_yosgic (赞：0)

## CF985Bの题解
### 题意
给定 $n$ 个开关，$m$ 盏灯，每个开关有 $m$ 个数值，第 $i$ 个数值为 $1$ 表示该开关**能开第 $i$ 盏灯**，求是否能**去掉一个开关**，使所有灯能被剩下的 $n-1$ 盏灯打开。

### 做法
首先，能使所有灯被打开，则必定有 $1$ 个以上的开关是**无用的**，即有没有这个开关对开灯没有影响。

易发现，**这种无用灯的每一个为 $1$ 的数值，都在其他灯中出现过**。否则无法去掉这盏灯。而一个数值全部为 $0$ 的灯必定是无用灯。

了解了这一点之后便可以模拟，开一个 $vis$ 数组来存每个 $1$ 的出现位置，能找到这样的无用灯就输出 YES，否则输出 NO。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[114514];
char a[2005][2005];
int n,m,flag;
int main(){
	ios_base::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
	{
		cin>>a[i][j];
		if(a[i][j]=='1') vis[j]++;//累加每一个 1 的位置
	}
	for(int i=1;i<=n;i++){
		if(flag){
			cout<<"YES";
			return 0;
		}//省时
		int o=0;
		for(int j=1;j<=m;j++){
			if(a[i][j]=='1') {if(vis[j]==1) {o=1;break;}}//如果发现只有出现一次的位置则不是无用灯
		}
		if(o==0) flag=1;
	}
	if(flag){
		cout<<"YES";
		return 0;
	}
	cout<<"NO";
	return 0;
}
```


---

## 作者：望月Asta (赞：0)

### 题意

给出 $n$ 个长度为 $m$ 的二进制串，保证原本 $n$ 个串按位或得到的是 $m$ 位均为 $1$ 的二进制串。

求是否能够删除一个串并且使得剩余的 $n - 1$ 个串按位或依然得到 $m$ 位每位均为 $1$ 的二进制串。

### 解法

直接按照题意模拟，枚举删除的串，但是这种做法是 $\mathrm{O} (n^2 m)$ 的，难以通过本题。

考虑使用 `std::bitset` 优化位运算的过程。

`bitset` 类似一个 `bool` 数组但是每个元素仅占一位空间，且支持 `bitset` 之间位运算。

`bitset` 可以直接使用 `|=` 运算符运算，类似整型变量。

那么每次求出之后只需要使用 `bitset::count()` 来统计目前是否按位或结果有 $m$ 个 $1$ 即可。

时间复杂度为 $\mathrm{O} (\frac{n^2 m}{w})$，其中 $w$ 为计算机位数，取决于评测机系统不同而不同，常见 32 位和 64 位，均可通过本题。

### Code

```cpp
#include <iostream>
#include <bitset>
using std::cin;
using std::cout;
using std::endl;
constexpr int N = 2005;

std::bitset<N> p[N];
std::bitset<N> tmp;

int main() {
    std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,m;bool flag = 0;
    cin >> n >> m;
    for(int i = 1;i <= n;++i)
        cin >> p[i];
    for(int i = 1;i <= n;++i) {
        tmp = 0;
        for(int j = 1;j <= n;++j) if(i != j)
            tmp |= p[j];
        if(tmp.count() == m) {
            flag = 1;
            break;
        }
    }
    if(flag) cout << "YES" << endl;
    else cout << "NO" <<endl;
    return 0;
}
```

---

