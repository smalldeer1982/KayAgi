# Putting Bricks in the Wall

## 题目描述

Pink Floyd are pulling a prank on Roger Waters. They know he doesn't like [walls](https://www.youtube.com/watch?v=YR5ApYxkU-U), he wants to be able to walk freely, so they are blocking him from exiting his room which can be seen as a grid.

Roger Waters has a square grid of size $ n\times n $ and he wants to traverse his grid from the upper left ( $ 1,1 $ ) corner to the lower right corner ( $ n,n $ ). Waters can move from a square to any other square adjacent by a side, as long as he is still in the grid. Also except for the cells ( $ 1,1 $ ) and ( $ n,n $ ) every cell has a value $ 0 $ or $ 1 $ in it.

Before starting his traversal he will pick either a $ 0 $ or a $ 1 $ and will be able to only go to cells values in which are equal to the digit he chose. The starting and finishing cells ( $ 1,1 $ ) and ( $ n,n $ ) are exempt from this rule, he may go through them regardless of picked digit. Because of this the cell ( $ 1,1 $ ) takes value the letter 'S' and the cell ( $ n,n $ ) takes value the letter 'F'.

For example, in the first example test case, he can go from ( $ 1, 1 $ ) to ( $ n, n $ ) by using the zeroes on this path: ( $ 1, 1 $ ), ( $ 2, 1 $ ), ( $ 2, 2 $ ), ( $ 2, 3 $ ), ( $ 3, 3 $ ), ( $ 3, 4 $ ), ( $ 4, 4 $ )

The rest of the band (Pink Floyd) wants Waters to not be able to do his traversal, so while he is not looking they will invert at most two cells in the grid (from $ 0 $ to $ 1 $ or vice versa). They are afraid they will not be quick enough and asked for your help in choosing the cells.  Note that you cannot invert cells $ (1, 1) $ and $ (n, n) $ .

We can show that there always exists a solution for the given constraints.

Also note that Waters will pick his digit of the traversal after the band has changed his grid, so he must not be able to reach ( $ n,n $ ) no matter what digit he picks.

## 说明/提示

For the first test case, after inverting the cell, we get the following grid:

```
<pre class="verbatim"><br></br>S010<br></br>0001<br></br>1001<br></br>111F<br></br>
```

## 样例 #1

### 输入

```
3
4
S010
0001
1000
111F
3
S10
101
01F
5
S0101
00000
01111
11111
0001F```

### 输出

```
1
3 4
2
1 2
2 1
0```

# 题解

## 作者：_ztyqwq (赞：2)

题意：给定一个 $ 0/1 $ 的 $ n \times n $ 地图，要求至多反转两个格子使得在路径上只能全部经过 $ 1 $ 或全部经过 $ 0 $ 的情况下，不能从 $ (1, 1) $ 出发走到 $ (n, n) $。

考虑反转 $ (1, 2) (2, 1) (n - 1, n) (n, n - 1) $ 中的某些格子，使得 $ (1, 2) (2, 1) $ 相同，$ (n - 1, n) (n, n - 1) $ 相同，而这两者不同。

也就是最后成为类似

```
S0**
0***
***1
**1F
```

或者

```
S1**
1***
***0
**0F
```

的形式。

有了思路以后就是大力分类讨论的事情了。。。

我的方式比较复杂，是先比较若起点和终点有一边两个已经相同（前两个 `if`），就使另一边的两个与他们不同；否则就两边各反转一个。

具体见代码。（实现不是很优美 QAQ）

```cpp
#include <bits/stdc++.h>
using namespace std;
string s[201];
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n;
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			cin >> s[i];
		if(s[0][1] == s[1][0])
		{
			printf("%d\n", (s[0][1] == s[n - 1][n - 2]) + (s[0][1] == s[n - 2][n - 1]));
			if(s[n - 1][n - 2] == s[0][1])
				printf("%d %d\n", n, n - 1);
			if(s[n - 2][n - 1] == s[0][1])
				printf("%d %d\n", n - 1, n);
		}
		else if(s[n - 1][n - 2] == s[n - 2][n - 1])
		{
			printf("%d\n", (s[n - 1][n - 2] == s[0][1]) + (s[n - 1][n - 2] == s[1][0]));
			if (s[n - 1][n - 2] == s[0][1])
				printf("%d %d\n", 1, 2);
			if (s[n - 2][n - 1] == s[1][0])
				printf("%d %d\n", 2, 1);
		}
		else
		{
			printf("2\n");
			printf("1 2\n");
			if(s[n - 1][n - 2] == s[1][0])
				printf("%d %d\n", n, n - 1);
			if(s[n - 2][n - 1] == s[1][0])
				printf("%d %d\n", n - 1, n);
		}
	}
	return 0;
}

```

---

## 作者：littlebug (赞：1)

## Solution

最多只能操作两次，而与 $(1,1)$ 和 $(n,n)$ 相邻的格子正好各有两个，所以可以在 $(1,2) , (2,1)$ 与 $(n-1,n) , (n,n-1)$ 中选择格子来操作。设 $a_1 = (1,2) , a_2 = (2,1)$，$b_1 = (n-1,n) , b_2 = (n,n-1)$，我们可以使 $a_1 , a_2$ 相同，$b_1 , b_2$ 相同，但是 $a_1 , a_2$ 与 $b_1 , b_2$ 不同，这样就一定无法从 $(1,1)$ 经过同一种格子走到 $(n,n)$ 了。

然后就可以分讨了，如果 $a_1 = a_2$ 相同，则将 $b_1 , b_2$ 设为与 $a_1 , a_2$ 不同的；$b_1 = b_2$ 同理；否则就将 $a_1 , a_2$ 设为 $0$，$b_1 , b_2$ 设为 $1$ 即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
//#define int long long
#define pii pair<int,int>
#define st first
#define nd second
#define mp make_pair
#define il inline
#define pb emplace_back
using namespace std;

const int MAXN=200+5;
int n;
char p[MAXN][MAXN];
vector < pii > ans;

il void solve()
{
    ans.clear();

    cin>>n;
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) cin>>p[i][j];

    pair <char,char> s=mp(p[1][2],p[2][1]),t=mp(p[n-1][n],p[n][n-1]);
    if(s.st==s.nd)
    {
        if(t.st==s.st) ans.pb(n-1,n);
        if(t.nd==s.st) ans.pb(n,n-1);
    }
    else if(t.st==t.nd)
    {
        if(s.st==t.st) ans.pb(1,2);
        if(s.nd==t.st) ans.pb(2,1);
    }
    else
    {
        if (s.st == '1') ans.pb(1, 2);
        else ans.pb(2, 1);
        if (t.st == '0') ans.pb(n - 1, n);
        else ans.pb(n, n - 1);
    }
    cout<<ans.size()<<'\n';
    for(auto i:ans) cout<<i.st<<' '<<i.nd<<'\n';

    return;
}

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：vectorwyx (赞：1)

不难想到我们应该使人在走出起点时只能选 $0/1$，而走到终点只能选相反的值。

又由于只能翻转两个位置，因此考虑紧挨起点的两个位置 $(1,2),(2,1)$ 和紧挨终点的两个位置 $(n.n-1),(n-1,n)$，我们的问题就转化成了给定一个长度为 $4$ 的 $01$ 串，最多将串内的两个元素取反使得它变成 $0011$ 或 $1100$ 的形式，这显然是有解的，分类讨论一下即可。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=205;
string a[maxn],s;

void work(){
	int n=read(),ans=0;
	fo(i,0,n-1) cin>>a[i];
	s.resize(4); 
	s[0]=a[0][1];
	s[1]=a[1][0];
	s[2]=a[n-1][n-2];
	s[3]=a[n-2][n-1];
	//s=a[0][1]+a[1][0]+a[n-1][n-2]+a[n-2][n-1];//(1,2) (2,1) (n-1,n-2) (n-2,n-1)
	//cout<<s<<endl;
	if(s=="0011"||s=="1100"){
		puts("0");
		return; 
	}
	if(s=="0000"||s=="1111"){
		puts("2");
		puts("1 2");
		puts("2 1");
		return;
	}
	if(s[0]!=s[1]){
		if(s[2]==s[3]){
			puts("1");
			if(s[0]==s[2]) puts("1 2");
			else puts("2 1");
		}else{
			puts("2");
			if(s[0]=='1') puts("1 2");
			else puts("2 1");
			if(s[2]=='0') printf("%d %d\n",n,n-1);
			else printf("%d %d\n",n-1,n); 
		}
	}else{
		puts("1");
		if(s[2]==s[0]) printf("%d %d\n",n,n-1);
		else printf("%d %d\n",n-1,n);
	}
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：YangXiaopei (赞：0)

## Solution:

我们可以发现，在出发时，起点右边的点和下面的点至少会经过其一。

在进入终点时，也必定经过终点上面和左边的两点之一，所以，我们只需围绕 $(1,2),(2,1),(n-1,n),(n,n-1)$ 这四个点讨论即可。

* $(1,2) = (2,1)$

那只需把 $(n-1,n),(n,n-1)$ 这两点中和 $(1,2)$ 相等的反转即可。

* $(n-1,n) = (n,n-1)$

也只需把 $(1,2),(2,1)$ 这两点中和 $(n-1,n)$ 相等的反转即可。

* 其余

不满足以上两种情况，那必定是起点边上两点和终点边上两点都是一个 $0$ 一个 $1$。

我们不妨将起点边上两点都改为 $0$，终点边上两点都改为 $1$。改 $2$ 个点。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
char a[205][205];
int main(){
	cin >> t;
	while(t--){
		cin >> n;
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				cin >> a[i][j];
			}
		}
		if(a[1][2] == a[2][1]){
			if(a[1][2] == '0'){
				cout << ((a[n][n - 1] == '0') + (a[n - 1][n] == '0')) << "\n";
				if(a[n - 1][n] == '0'){
					cout << n - 1 << " " << n << "\n";
				}
				if(a[n][n - 1] == '0'){
					cout << n << " " << n - 1 << "\n";
				}
			}
			else{
				cout << ((a[n][n - 1] == '1') + (a[n - 1][n] == '1')) << "\n";
				if(a[n - 1][n] == '1'){
					cout << n - 1 << " " << n << "\n";
				}
				if(a[n][n - 1] == '1'){
					cout << n << " " << n - 1 << "\n";
				}
			}
		}
		else if(a[n][n - 1] == a[n - 1][n]){
			if(a[n][n - 1] == '0'){
				cout << ((a[1][2] == '0') + (a[2][1] == '0')) << "\n";
				if(a[1][2] == '0'){
					cout << 1 << " " << 2 << "\n";
				}
				if(a[2][1] == '0'){
					cout << 2 << " " << 1 << "\n";
				}
			}
			else{
				cout << ((a[1][2] == '1') + (a[2][1] == '1')) << "\n";
				if(a[1][2] == '1'){
					cout << 1 << " " << 2 << "\n";
				}
				if(a[2][1] == '1'){
					cout << 2 << " " << 1 << "\n";
				}
			}
		}
		else{
			cout << 2 << "\n";
			if(a[1][2] == '0'){
				cout << 1 << " " << 2 << "\n";
			}
			if(a[2][1] == '0'){
				cout << 2 << " " << 1 << "\n";
			}
			if(a[n - 1][n] == '1'){
				cout << n - 1 << " " << n << "\n";
			}
			if(a[n][n - 1] == '1'){
				cout << n << " " << n - 1 << "\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1421B)

------------
# 思路：
这是一道思维题，不用想得很深，我们只需要知道一开始走出起点的限制有两个格子 $(1,2)$ 和 $(2,1)$，走到终点也有两个格子限制 $(n-1,n)$ 和 $(n,n-1)$。那么只要使得这起点格子和终点格子起冲突,让这两组的格子元素值相反即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e3+10;
const int INF=0x3f3f3f3f;
int T,n;
char c[N][N];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=0;i<=n-1;i++){
			cin>>c[i];
		}
		char a1=c[1][0],a2=c[0][1],b1=c[n-2][n-1],b2=c[n-1][n-2];
		if(a1!=a2){
			if(b1!=b2){
				cout<<2<<endl;
				if(a1==b1){
					cout<<"2 1"<<endl<<n<<" "<<n-1<<endl;
				}else{
					cout<<"2 1"<<endl<<n-1<<" "<<n<<endl;
				}
			}else{
				if(a1==b1){
					cout<<1<<endl<<"2 1"<<endl;
				}else{
					cout<<1<<endl<<"1 2"<<endl;
				}
			}
		}else{
			if(b1==b2){
				if(b1==a1){
					cout<<2<<endl<<"1 2"<<endl<<"2 1"<<endl;
				}else{
					cout<<0<<endl;
				}
				continue;
			}
			if(b1==a1){
				cout<<1<<endl<<n-1<<" "<<n<<endl;
			}
			else{
				cout<<1<<endl<<n<<" "<<n-1<<endl;
			}
		}
	}
	return 0;
}
```
完结撒花~

---

## 作者：Infinite_Loop (赞：0)

# CF1421B
## 题意
给定一个 $n \times n$ 的 $0 / 1$ 地图，要求至多反转两个格子中的值，且不能反转 $(1,1)$ 和 $(n,n)$ 中的值，使得在路径上只能全部通过 $1$ 或 $0$，不能从 $(1,1)$ 到达 $(n,n)$。
## 思路
因为 $n \ge 3$，所以只要考虑反转 $(1,2) (2,1) (n-1,n) (n,n-1)$ 中的某些格子，使得 $(1,2) (2,1)$ 格子内的值相同，$(n-1,n) (n,n-1)$ 格子内的值相同，且两者值不同。

综上，我们只要分类讨论哪些格子需要反转，最后输出即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
string s[205];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>s[i];
		if(s[1][1]==s[2][0]){
			int ans=(s[1][1]==s[n-1][n-1])+(s[1][1]==s[n][n-2]);
			cout<<ans<<'\n';
			if(s[1][1]==s[n-1][n-1]){
				cout<<n-1<<" "<<n<<'\n';
			}
			if(s[1][1]==s[n][n-2]){
				cout<<n<<" "<<n-1<<'\n';
			}
		}else if(s[n-1][n-1]==s[n][n-2]){
			int ans=(s[1][1]==s[n-1][n-1])+(s[2][0]==s[n-1][n-1]);
			cout<<ans<<'\n';
			if(s[1][1]==s[n-1][n-1]){
				cout<<1<<" "<<2<<'\n';
			}
			if(s[2][0]==s[n-1][n-1]){
				cout<<2<<" "<<1<<'\n';
			}
		}else{
			cout<<2<<'\n';
			cout<<1<<" "<<2<<'\n';
			if(s[2][0]==s[n-1][n-1]){
				cout<<n-1<<" "<<n<<'\n';
			}
			if(s[2][0]==s[n][n-2]){
				cout<<n<<" "<<n-1<<'\n'; 
			}
		}
	}
	return 0;
}
```


---

## 作者：xiaofeng_and_xiaoyu (赞：0)

本题解的优点：空间最优解（仅有 $4$ KB）

从题意可知答案数量最多为 $2$，大多数题解都说出了理由：只用从出发点左侧，下侧和终点上侧，右侧判断。

但是深挖一下他们的题解会发现空间复杂度不算优，主要原因是他们的二维数组。

然而这题不需要二维数组，只需要记录上文所说的四个值。

剩下的数，统统随着一次次的输入被迭代。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t1,t2,t3,t4;
int main(){
    int x,y;
	string z;
    char t=0;
    cin>>x;
    while(x--){
    	cin>>y;
    	for(int i=0;i<y;i++){
    		if(i==0){
    			cin>>z;
    			t1=z[1]-'0';
			}else if(i==1){
				cin>>z;
				t2=z[0]-'0';
				if(i==y-2)t3=z[y-1]-'0';//注意当y=3时的特判
			}else if(i==y-2){
    			cin>>z;
    			t3=z[y-1]-'0';
			}else if(i==y-1){
				cin>>z;
    			t4=z[y-2]-'0';
			}else{
    			cin>>z;
			}
		}
		if(t1==t2){
			if(t3==t4){
				if(t1==t3){
					cout<<2<<endl<<1<<' '<<2<<endl<<2<<' '<<1<<endl;
				}else{
					cout<<0<<endl;
				}
			}else{
				if(t1==t3){
					cout<<1<<endl<<y-1<<' '<<y<<endl;
				}else{
					cout<<1<<endl<<y<<' '<<y-1<<endl;
				}
			}
		}else{
			if(t3==t4){
				if(t1==t3){
					cout<<1<<endl<<1<<' '<<2<<endl;
				}else{
					cout<<1<<endl<<2<<' '<< 1<<endl;
				}
			}else{
				if(t1==t3){
					cout<<2<<endl<<1<<' '<<2<<endl<<y<<' '<<y-1<<endl;
				}else{
					cout<<2<<endl<<1<<' '<<2<<endl<<y-1<<' '<<y<<endl;
				}
			}
		}
	}
    return 0;
}
```


---

## 作者：Chinese_zjc_ (赞：0)

先看数据范围:
$$
3\leq n\leq200
$$
也就是说, $(1,2)$ , $(2,1)$ , $(n-1,n)$ , $(n,n-1)$ 均存在且为不同坐标.

显然有一种构造答案的方法,就是把上面四个坐标染成前两个相同颜色,后两个相同颜色.

总共 $16$ 种情况,可以一一证明有解,此处我们直接 $DFS$ 枚举变换的坐标,判断是否成功即可.

$Code$:

```cpp
//This Code was made by Chinese_zjc_.
//头文件已省略
#define int long long
#define double long double
using namespace std;
const double PI = acos(-1);
const double eps = 0.0000000001;
const int INF = 0x3fffffffffffffff;
int T, n;
char a[205][205];
struct L
{
    int x, y;
    char g()
    {
        return a[x][y];
    }
} c[4], did[4];
bool dfs(int now, int tim)//多组数据不能直接exit(0)
{
    if (tim > 2)
    {
        return false;
    }
    if (now == 4)
    {
        if (c[0].g() == c[1].g() && c[2].g() != c[0].g() && c[2].g() == c[3].g())
        {
            cout << tim << endl;
            for (int i = 0; i < tim; ++i)
            {
                cout << did[i].x << ' ' << did[i].y << endl;
            }
            return true;
        }
        return false;
    }
    if (dfs(now + 1, tim))
    {
        return true;
    }
    a[c[now].x][c[now].y] ^= 1;
    did[tim] = c[now];
    if (dfs(now + 1, tim + 1))
    {
        return true;
    }
    a[c[now].x][c[now].y] ^= 1;
    return false;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin >> T;
    while (T--)
    {
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                cin >> a[i][j];
            }
        }
        c[0] = {1, 2};
        c[1] = {2, 1};
        c[2] = {n - 1, n};
        c[3] = {n, n - 1};
        dfs(0, 0);
    }
    return 0;
}
```



---

## 作者：oneton429 (赞：0)

### CF1421B. Putting Bricks in the Wall

[Link](https://codeforces.com/contest/1421/problem/B)

> 一道降智题

#### 题目大意

一个人，可以从$(1,1)$开始，四联通地向与自己脚下格子数字($0$或$1$)相同的格子移动，最终要到达$(n,n)(3\leq n\leq100)$，起始时的数字可以是$0$或$1$。你需要输出一种修改方案，修改$c(0\leq c\leq2)$个点的数字，使得这个人无法从$(1,1)$走到$(n,n)$，并输出方案。

#### 思路1

按照正常套路，这题应该让你输出**最优**解，但是这题并没有。

但考的时候没注意到，想了好久才发现。

~~容易得到~~，在$S$点附近修改，一定能在$2$次修改次数内，使得他无法走到$T$点。

只要$
\begin{matrix}
&S\quad0\quad1\\
&0\quad1\quad\ \ \\
&1\quad\ \quad\ \ \ \\
\end{matrix}
$或者$
\begin{matrix}
&S\quad1\quad0\\
&1\quad0\quad\ \ \\
&0\quad\ \quad\ \ \ \\
\end{matrix}
$这样构造，这两种**取一个最优解**即可(要不有可能会最多修改$5$次)。

画画图就能自行理解。

#### Code1

有思路就很简单了。

```cpp
a1 = (mp[1][2] != '0') + (mp[2][1] != '0') + (mp[1][3] != '1') + (mp[2][2] != '1') + (mp[3][1] != '1'),
a2 = (mp[1][2] != '1') + (mp[2][1] != '1') + (mp[1][3] != '0') + (mp[2][2] != '0') + (mp[3][1] != '0');
if (a1 < a2) {
    printf("%d\n", a1);
    if (mp[1][2] != '0')
        puts("1 2");
    if (mp[2][1] != '0')
        puts("2 1");
    if (mp[1][3] != '1')
        puts("1 3");
    if (mp[2][2] != '1')
        puts("2 2");
    if (mp[3][1] != '1')
        puts("3 1");
} else {
    printf("%d\n", a2);
    if (mp[1][2] != '1')
        puts("1 2");
    if (mp[2][1] != '1')
        puts("2 1");
    if (mp[1][3] != '0')
        puts("1 3");
    if (mp[2][2] != '0')
        puts("2 2");
    if (mp[3][1] != '0')
        puts("3 1");
}
```

#### 思路2

在网上找到的另一种构造方案

只要$
\begin{matrix}
&\ S\quad\ \ 0\quad\cdots\\
&\ 0\quad\cdots\quad1\ \\
&\cdots\quad1\ \quad F\ \\
\end{matrix}
$或者$
\begin{matrix}
&\ S\quad\ \ 1\quad\cdots\\
&\ 1\quad\cdots\quad0\ \\
&\cdots\quad0\ \quad F\ \\
\end{matrix}
$这样构造，这两种**取一个最优解**既可(要不有可能会最多修改$4$次)

#### 无端联想

如果$n=2$？无解，无论如何都能走到$T$点。

---

## 作者：10circle (赞：0)

#### 题意

给一个 $01$ 矩阵 $a$，你最多可以更改两个格子，使从起点到终点没有纯由 $0$ 构成或纯由 $1$ 构成的路径。

#### 分析

根据 $a_{1,2},a_{2,1},a_{n-1,n},a_{n,n-1}$ 分类讨论。

大概意思就是把它们变成 $0011$ 或是 $1100$（按顺序）。

一共 $16$ 种情况，把它们全列出来就行了（具体实现见代码，语言叙述太麻烦了）。

#### 代码

```
#include<bits/stdc++.h>
#define itn int
#define ll long long
using namespace std;

ll read(){
	ll a=0,b=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')b=-1;c=getchar();}
	while(c>='0'&&c<='9')a=a*10+c-48,c=getchar();
	return a*b;
}
char a[205][205];

int main(){
	int t=read();
	while(t--){
		ll n=read();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>a[i][j];a[i][j]-='0';
			}
		}
		
		if(a[1][2]==0&&a[2][1]==0&&a[n-1][n]==0&&a[n][n-1]==0)cout<<"2\n1 2\n2 1\n";
		else if(a[1][2]==0&&a[2][1]==0&&a[n-1][n]==1&&a[n][n-1]==0)cout<<"1\n"<<n<<' '<<n-1<<endl;
		else if(a[1][2]==0&&a[2][1]==0&&a[n-1][n]==0&&a[n][n-1]==1)cout<<"1\n"<<n-1<<' '<<n<<endl;
		else if(a[1][2]==0&&a[2][1]==0&&a[n-1][n]==1&&a[n][n-1]==1)cout<<"0\n";
		
		else if(a[1][2]==0&&a[2][1]==1&&a[n-1][n]==0&&a[n][n-1]==0)cout<<"1\n1 2\n";
		else if(a[1][2]==0&&a[2][1]==1&&a[n-1][n]==1&&a[n][n-1]==0)cout<<"2\n1 2\n"<<n-1<<' '<<n<<endl;
		else if(a[1][2]==0&&a[2][1]==1&&a[n-1][n]==0&&a[n][n-1]==1)cout<<"2\n1 2\n"<<n<<' '<<n-1<<endl;
		else if(a[1][2]==0&&a[2][1]==1&&a[n-1][n]==1&&a[n][n-1]==1)cout<<"1\n2 1\n";
		
		else if(a[1][2]==1&&a[2][1]==0&&a[n-1][n]==0&&a[n][n-1]==0)cout<<"1\n2 1\n";
		else if(a[1][2]==1&&a[2][1]==0&&a[n-1][n]==1&&a[n][n-1]==0)cout<<"2\n2 1\n"<<n-1<<' '<<n<<endl;
		else if(a[1][2]==1&&a[2][1]==0&&a[n-1][n]==0&&a[n][n-1]==1)cout<<"2\n2 1\n"<<n<<' '<<n-1<<endl;
		else if(a[1][2]==1&&a[2][1]==0&&a[n-1][n]==1&&a[n][n-1]==1)cout<<"1\n1 2\n";
		
		else if(a[1][2]==1&&a[2][1]==1&&a[n-1][n]==0&&a[n][n-1]==0)cout<<"0\n";
		else if(a[1][2]==1&&a[2][1]==1&&a[n-1][n]==1&&a[n][n-1]==0)cout<<"1\n"<<n-1<<' '<<n<<endl;
		else if(a[1][2]==1&&a[2][1]==1&&a[n-1][n]==0&&a[n][n-1]==1)cout<<"1\n"<<n<<' '<<n-1<<endl;
		else if(a[1][2]==1&&a[2][1]==1&&a[n-1][n]==1&&a[n][n-1]==1)cout<<"2\n"<<n-1<<' '<<n<<endl<<n<<' '<<n-1<<endl;
	}
	return 0;
}

```

---

## 作者：—维尼— (赞：0)

## 题目描述
给定$n\times n$的方格,左上角是$S$,右下角是$F$，其他都由$0$或$1$构成，开始时，小A在左上角，会选择$1$或$0$，之后只走相邻的并且数字相同的格子，你的任务是阻止小A到右下角，只有两次操作机会，每次可以翻转一个格子（0变1,1变0），求翻转次数和翻转的格子（输出一种情况）

## 题目思路
乍一看挺唬人，其实思路挺好想，我们只要用不同的把终点堵上就好，这就要求终点旁边的和开始选择的数字不一样

那么怎么强迫小A选不一样的数字呢，我们用贪心，让左上角（1,2）（2,1）和（n,n-1）（n-1,n）不一样就好了，这个时候小A想出左上角只能选择一个和右下角不一样的数字，那么他就过不来了

这种方法虽然输出的不一定是最优解（因为小A可能本来就被堵住），但是只用输出其中一种，所以是可以完美A掉的，可以证明所以情况都可以在两次操作以内完成，然后分类讨论输出就行了

我这里记录了左上角和右下角的和，便于讨论
## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int a[205][205];
int main(){
	int t;
	cin>>t;
	while(t--){
		int suma=0,sumb=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				char x;
				cin>>x;
				if(x!='S'&&x!='F'){
					a[i][j]=x-'0';
				}
			}
		}
		if(a[2][1])
		suma++;
		if(a[1][2])
		suma++;
		if(a[n][n-1])
		sumb++;
		if(a[n-1][n])
		sumb++;
		if(suma==2&&sumb==0){
			cout<<0<<endl;
		}
		else if(suma==0&&sumb==2){
			cout<<0<<endl;
		}
		else if(suma==2&&sumb==2){
			cout<<2<<endl;
			cout<<1<<" "<<2<<endl;
			cout<<2<<" "<<1<<endl;
		}
		else if(suma==0&&sumb==0){
			cout<<2<<endl;
			cout<<1<<" "<<2<<endl;
			cout<<2<<" "<<1<<endl;
		}
		else if(suma==1&&sumb==1){
			cout<<2<<endl;
			if(a[1][2])
				cout<<1<<" "<<2<<endl;
			if(a[2][1])
				cout<<2<<" "<<1<<endl;
			if(a[n][n-1]==0)
				cout<<n<<" "<<n-1<<endl;
			if(a[n-1][n]==0)
				cout<<n-1<<" "<<n<<endl;
		}
		else{
			cout<<1<<endl;
			if(suma==0&&sumb==1){
				if(a[n][n-1]==0)
					cout<<n<<" "<<n-1<<endl;
				else
					cout<<n-1<<" "<<n<<endl;
			}
			if(suma==1&&sumb==0){
				if(a[1][2]==0)
					cout<<1<<" "<<2<<endl;
				else
					cout<<2<<" "<<1<<endl;
			}
			if(suma==2&&sumb==1){
				if(a[n][n-1])
					cout<<n<<" "<<n-1<<endl;
				else
					cout<<n-1<<" "<<n<<endl;
			}
			if(suma==1&&sumb==2){
				if(a[1][2])
					cout<<1<<" "<<2<<endl;
				else
					cout<<2<<" "<<1<<endl;
			}
		}
	}
} 
```

---

