# Robots

## 题目描述

There is a field divided into $ n $ rows and $ m $ columns. Some cells are empty (denoted as E), other cells contain robots (denoted as R).

You can send a command to all robots at the same time. The command can be of one of the four types:

- move up;
- move right;
- move down;
- move left.

When you send a command, all robots at the same time attempt to take one step in the direction you picked. If a robot tries to move outside the field, it explodes; otherwise, every robot moves to an adjacent cell in the chosen direction.

You can send as many commands as you want (possibly, zero), in any order. Your goal is to make at least one robot reach the upper left corner of the field. Can you do this without forcing any of the robots to explode?

## 说明/提示

Explanations for test cases of the example:

1. in the first test case, it is enough to send a command to move left.
2. in the second test case, if you try to send any command, at least one robot explodes.
3. in the third test case, it is enough to send a command to move left.
4. in the fourth test case, there is already a robot in the upper left corner.
5. in the fifth test case, the sequence "move up, move left, move up" leads one robot to the upper left corner;
6. in the sixth test case, if you try to move any robot to the upper left corner, at least one other robot explodes.

## 样例 #1

### 输入

```
6
1 3
ERR
2 2
ER
RE
2 2
ER
ER
1 1
R
4 3
EEE
EEE
ERR
EER
3 3
EEE
EER
REE```

### 输出

```
YES
NO
YES
YES
YES
NO```

# 题解

## 作者：Dream_weavers (赞：3)

## 题意

有一些机器人站在 $n\times m$ 网格上，可以操控它们上下左右移动一格，每操控一次所有机器人都会一起动，但是如果某个机器人离开了网格它就会爆炸。请你判断在机器人不爆炸的情况下，能否把一个机器人移到左上角。

## 思路

既然要把机器人移到左上角，就要先找到距离左上角最近的机器人，也是第一个出现的机器人。然后循环遍历每一行，找到每行最前的机器人，如果它的 $y$ 坐标（列数）比第一个出现的机器人的要小，就说明当机器人移到左上角时，它就会越界爆炸，输出 `NO`，否则输出 `YES`。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char s;
int t,n,m;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		int tmp=0,ans=1,maxn;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>s;
				if(tmp==0&&s=='R')maxn=j,tmp=1;
				if(s=='R'&&j<maxn)ans=0;
			}
		}
		if(ans)puts("YES");
		else puts("NO");
	}
	return 0;
}

```

---

## 作者：Jerrlee✅ (赞：3)

## 题意
$t$ 组数据，每组数据给定 $n$ 和 $m$ 和 $n \times m$ 的矩形。

矩形中的 `R` 代表机器人，`E` 代表空地。每次操作可以使**所有**机器人向上或下或左或右移动一格。问能否在**所有**机器人不出格的情况下使**其中一个**机器人达到左上角。
## 思路
既然要到左上角，那就可以只向上或左移动。

反过来思考，怎样会使机器人出格？

- 向左时出格，那就不向左，向上；

- 向上时出格，那就不向上，向左。

那么，如果以上两种情况，无论如何移动都会导致机器人出格，肯定是类似如下图的情况：
```
ERE
REE
```
这类情况，必定是最左边的机器人上方还有机器人，或者说最上面的机器人左边还有机器人。

反过来，只要所有机器人横纵坐标最小值的位置有机器人，那说明可以满足题意，反之则不能。
## 代码
```cpp
#include<iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        int mx=n,mn=m;
        char x[n][m];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>x[i][j];
                if(x[i][j]=='R'){
                    mx=min(mx,i);
                    mn=min(mn,j);
                }
            }
        }
        if(x[mx][mn]=='R') cout<<"YES\n";
        else cout<<"NO\n";
    }
}
```
[AC 记录（洛谷）](https://www.luogu.com.cn/record/75791402)

[AC 记录（CF）](https://codeforces.com/contest/1680/submission/157255831)

---

## 作者：Engulf (赞：2)

显然，为了避免机器人越界，我们要尽量减少行走的步数，所以我们找到离点 $(1,1)$ 最近的一个机器人，算出需行走的步数，判断一下是否越界即可。

```cpp
void solve(){
    cin>>n>>m;
    int x=0x3f3f3f3f,y=0x3f3f3f3f;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];
    if(a[1][1]=='R')return (void)(cout<<"YES\n");
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='R' && i+j-2 < x+y-2)x=i,y=j;
        }
    }
    int nx=x-1,ny=y-1;
    //cout<<"nx: "<<nx<<" ny: "<<ny<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]=='R'){
                if(i-nx<=0||j-ny<=0)return (void)(cout<<"NO\n");
            }
        }
    }
    cout<<"YES\n";
}
```

---

## 作者：accomplishment (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1680B)

这道题思维难度不大，建议评橙。首先因为是所有机器人要同时移动，唯一可能移到左上角的就是严格左上角的机器人（指左边和上面都没有更多机器人），因此我们只要判断最左端的机器人和最上端的机器人是不是同样的机器人即可，如果相同输出 ```YES```，否则输出 ```NO```。

判断是否相同方法：

先用```vector```存储所有机器人的坐标，然后分别找到 $x$ 坐标与 $y$ 坐标的最小值，查看索引值是否相同即可。

$Code: $
```cpp
// Problem: B. Robots
// Contest: Educational Codeforces Round 128 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1680/problem/B
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
/*
 * Author: guzheran @YYXX
 */
 
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
 
#define fi first
#define se second
#define register rg
#define mp make_pair
#define pb push_back
#define pf push_front
 
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)
 
namespace IO {
	
	template <typename type>
	inline void Read (type &theNum) {
	
		char theChar = 0;
		int negative = 0; 
		
		theNum = 0;
		theChar = getchar();
		negative = 1;
		
		while (theChar < '0' || theChar > '9') {
			if (theChar == '-') {
				negative = -1;
			}
			
			theChar = getchar();
		}
		
		theNum = theChar ^ 48;
		
		while ((theChar = getchar()) > '0' - 1 && theChar < '9' + 1) {
			theNum = (theNum << 3) + (theNum << 1) + (theChar ^ 48);
		}
		
		theNum *= negative;
		
	}
	
	template <typename type>
	inline void RecursionWrite (type theNum) {
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
	}
	
	template <typename type1, typename type2>
	inline void Write (type1 theNum, type2 endChar) {
		
		if (!theNum) {
			putchar('0');
		}
		
		if (theNum < 0) {
			putchar('-');
			theNum *= -1;
		}
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
		putchar(endChar);
		
	}
	
}
 
using namespace IO;

const int inf = 0x3f3f3f3f;
 
/* template ends here */
 
int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int T;
	
	cin >> T;
	
	while (T--) {
		int n, m;
		char arr[5][5];
		vector<int> x;
		vector<int> y;
		
		cin >> n >> m;
		
		rep (i, 1, n) {
			rep (j, 1, m) {
				cin >> arr[i][j];
				
				if (arr[i][j] == 'R') {
					x.push_back(i);
					y.push_back(j);
				}
			}
		}
		
		int xminn = inf, xmini = 0;
		int yminn = inf, ymini = 0;
		
		rep (i, 0, x.size() - 1) {
			if (x[i] < xminn) {
				xminn = x[i];
				xmini = i;
			}
			
			if (y[i] < yminn) {
				yminn = y[i];
				ymini = i;
			}
		}
		
		if (xmini == ymini) {
			cout << "YES" << '\n';
			continue;
		}
		
		cout << "NO" << '\n';
	}
	
	return 0;
	
}

```


---

## 作者：ttq012 (赞：1)

好题。

由于要到达左上角，所以机器人只会往左走和往上走。

容易发现，当一个机器人的位置的横坐标和纵坐标都非严格小于另一个机器人的位置的横坐标和纵坐标的时候，第一个机器人可以到达左上角，如果一个机器人的横坐标严格小于另一个机器人的横坐标并且第一个机器人的纵坐标严格大于第二个机器人的纵坐标的时候，或者第一个机器人的横坐标严格大于第二个机器人的横坐标，并且第一个机器人的纵坐标严格小于第二个机器人的纵坐标的时候，这两个机器人都无法到达左上角。

如果一个机器人的横坐标和纵坐标都严格小于其他的机器人，那么这一个机器人就可以到达左上角。

```cpp
#include <bits/stdc++.h>

using namespace std;

char s[2323][2323];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        scanf ("%s", s[i] + 1);
    int mx = 0x3f3f3f3f, my = 0x3f3f3f3f;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
            if (s[i][j] == 'R') {
                mx = min(mx, i);
                my = min(my, j);
            }
    if (mx == 0x3f3f3f3f || s[mx][my] != 'R')
        puts("NO");
    else
        puts("YES");
}

signed main() {
    int T;
    cin >> T;
    while (T --)
        solve();
}

```


---

## 作者：Shunpower (赞：0)

## 题目大意

现在有一个 $n\times m$ 大小的棋盘，上面有一些空格或者机器人。其中空格用 `E` 表示，机器人用 `R` 表示。

你可以让所有机器人同时向上、向下、向左或向右一次。若在某次发号施令后某个机器人走出了棋盘，那么这步操作是不合法的。

你需要回答你能不能通过若干次合法操作使得某个机器人走到了棋盘左上角？

数据范围：**本题有多组数据**，$1\leqslant n,m\leqslant 5,1\leqslant t\leqslant 5000$。

## 思路

首先，我们显然不会发向下或向右的命令，因为这样做对于解决问题毫无帮助。

考虑一个机器人到达左上需要怎么走。很显然，无论这个机器人到左上的路径是怎么样的，如果剩下有机器人会走出去，那么它逃不掉走出去的命运。

那不妨考虑一个机器人它先向上再向左，我们用两个变量记录它需要向上走的步数、向左走的步数。剩下的机器人若是用自己的坐标减掉这两个步数后，有机器人出界，那么这个机器人就不能当选为最终走到左上角的机器人。

形象化地，假设一个机器人的坐标为 $(x,y)$（对应的是棋盘上的 $x$ 列 $y$ 行），那么它需要向左走 $x-1$ 步，向上走 $y-1$ 步。

再假设 $l=x-1$，$r=y-1$，剩下的机器人的坐标分别为 $(x_1,y_1),(x_2,y_2),\cdots,(x_k,y_k)$，如果对于任意 $1\leqslant i\leqslant k$ 有 $x_i-l< 1\lor y_i-r<1$，那么这个 $(x,y)$ 的机器人就不能成为最后走到左上角的机器人。

枚举所有机器人，看看它是否能成为左上角的那个机器人。如果它可以，直接输出 `YES`，否则就全部验证，再输出 `NO`。

时间复杂度最坏 $O(tn^2m^2)$，可以通过。

## 代码

```
//Author:Zealous_YH
//Hai Bian & Xiao Bao
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define inf INT_MAX
#define uinf INT_MIN
#define vr vector
#define pii pair<int,int>
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)<<setprecision(2)
using namespace std;
const int N=1e5+10;
int maxn=uinf,minn=inf;
int tnt,tot;
int T;
int a,b;
vector <pii> robots;//记录所有机器人
void solve(){
	cin>>a>>b;
	robots.clear();//多测记得清空
	fr1(i,1,a){
		fr1(j,1,b){
			char c;
			cin>>c;
			if(c=='R'){
				robots.pb(mp(i,j));
			}
		}
	}
	fv(i,robots){
		int x=robots[i].fi,y=robots[i].se;
		int lef=x-1,up=y-1;//计算步数
		bool f=0;
		fv(j,robots){
			if(i==j){
				continue;
			}
			if(robots[j].fi-lef<1||robots[j].se-up<1){//验证是否可以移过去
				f=1;
				break;//可以快一点
			}
		}
		if(!f){
			puts("YES");
			return;
		}
	}
	puts("NO");
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//Everything For Ji.
//Everything For Lin.
//Everything For You.
```

[AC 记录](https://www.luogu.com.cn/record/75870900)

---

