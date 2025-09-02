# Polycarp and Snakes

## 题目描述

After a hard-working week Polycarp prefers to have fun. Polycarp's favorite entertainment is drawing snakes. He takes a rectangular checkered sheet of paper of size $ n \times m $ (where $ n $ is the number of rows, $ m $ is the number of columns) and starts to draw snakes in cells.

Polycarp draws snakes with lowercase Latin letters. He always draws the first snake with the symbol 'a', the second snake with the symbol 'b', the third snake with the symbol 'c' and so on. All snakes have their own unique symbol. There are only $ 26 $ letters in the Latin alphabet, Polycarp is very tired and he doesn't want to invent new symbols, so the total number of drawn snakes doesn't exceed $ 26 $ .

Since by the end of the week Polycarp is very tired, he draws snakes as straight lines without bends. So each snake is positioned either vertically or horizontally. Width of any snake equals $ 1 $ , i.e. each snake has size either $ 1 \times l $ or $ l \times 1 $ , where $ l $ is snake's length. Note that snakes can't bend.

When Polycarp draws a new snake, he can use already occupied cells for drawing the snake. In this situation, he draws the snake "over the top" and overwrites the previous value in the cell.

Recently when Polycarp was at work he found a checkered sheet of paper with Latin letters. He wants to know if it is possible to get this sheet of paper from an empty sheet by drawing some snakes according to the rules described above. If it is possible, he is interested in a way to draw snakes.

## 样例 #1

### 输入

```
1
5 6
...a..
..bbb.
...a..
.cccc.
...a..
```

### 输出

```
YES
3
1 4 5 4
2 3 2 5
4 2 4 5
```

## 样例 #2

### 输入

```
3
3 3
...
...
...
4 4
..c.
adda
bbcb
....
3 5
..b..
aaaaa
..b..
```

### 输出

```
YES
0
YES
4
2 1 2 4
3 1 3 4
1 3 3 3
2 2 2 3
NO
```

## 样例 #3

### 输入

```
2
3 3
...
.a.
...
2 2
bb
cc
```

### 输出

```
YES
1
2 2 2 2
YES
3
1 1 1 2
1 1 1 2
2 1 2 2
```

# 题解

## 作者：Eibon (赞：6)

不难发现，每个字母只有两种情况。

第一种是直接被覆盖。

第二种是没有被覆盖。[doge]

于是模拟即可。

对于每个字母，开一个结构体记录它最靠近左上方的点与最靠近右下方的点的坐标。

判断一下两点是否在同一条直线上，如果不是则不合法。

接下来按字母顺序暴力将每条链覆盖在二维数组 $mp$ 中。

给被覆盖的点随便找一个覆盖的点坐标即可。

最后统计答案输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2000+5;
int T,n,m,sum,VIP,cnt,nx,ny;
struct node
{
	int ax,ay,bx,by;
};
node num[28],ans[28];
char a[maxn][maxn],mp[maxn][maxn];
signed main()
{
    scanf("%lld",&T);
    while(T--){
    	VIP=1;cnt=0;nx=ny=0;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				mp[i][j]='.';
				for(int k=1;k<=26;k++){
					num[k].ax=1e18;num[k].bx=0;
					num[k].ay=1e18;num[k].by=0;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
				if(a[i][j]>='a'&&a[i][j]<='z'){
					int c=a[i][j]-'a'+1;
					num[c].ax=min(num[c].ax,i);num[c].bx=max(num[c].bx,i);
					num[c].ay=min(num[c].ay,j);num[c].by=max(num[c].ay,j);
				}
			}
		}
		for(int i=1;i<=26;i++){
			if(num[i].bx){
				if(num[i].ax!=num[i].bx&&num[i].ay!=num[i].by){
					VIP=0;
					break;
				}
				else{
					cnt=i;nx=num[i].ax;ny=num[i].ay;
					ans[i].ax=num[i].ax;ans[i].bx=num[i].bx;
					ans[i].ay=num[i].ay;ans[i].by=num[i].by;
					for(int x=num[i].ax;x<=num[i].bx;x++){
						for(int y=num[i].ay;y<=num[i].by;y++){
							mp[x][y]=(char)(i+'a'-1);
						}
					}
				}
			}
		}
		if(!VIP){
			puts("NO");
			continue;
		}
		for(int i=1;i<=cnt;i++){
			if(!num[i].bx){
				ans[i].ax=ans[i].bx=nx;
				ans[i].ay=ans[i].by=ny;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(mp[i][j]!=a[i][j]){
					VIP=0;
					break;
				}
			}
		}
		if(!VIP){
			puts("NO");
			continue;
		}
		puts("YES");
		printf("%lld\n",cnt);
		for(int i=1;i<=cnt;i++){
			printf("%lld %lld %lld %lld\n",ans[i].ax,ans[i].ay,ans[i].bx,ans[i].by);
		}
	}
    return 0;
}
//dyyyyds
/*
1
3 3
...
...
.c.
*/
```

---

## 作者：__phiu (赞：3)

第五道自主切的紫，写题解纪念一下。

## Pro

按照 $ a \sim z$ 的顺序加一条横链或者竖链，链上的所有点赋成当前链的值（可以覆盖），能否与给出的矩阵一样。

## Sol

首先分类讨论一下，共有三种情况：

1. 当前字符一次没有出现。

2. 出现了一次。

3. 出现了两次及以上。

### 第一种情况

找到最后一个字符的一个位置赋上，这样最后一定会被覆盖。

### 第二种情况

直接赋给这个点。

### 第三种情况

判断这些点是否构成一条直线，如果不是那么久不可以。

最后把矩阵覆盖判断一下是否相等（因为可能操作完覆盖导致不相等）

## Code

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define For(i,a,b,c) for(int i=a;i<=b;i+=c)
#define Rof(i,a,b,c) for(int i=a;i>=b;i-=c)
#define pb push_back
#define pii pair<int,int>
using namespace std;
const int N = 2e6 + 50;
inline int read() {
	char c = getchar();
	int x = 0, f = 1;
	while (c<'0' or c>'9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while (c >= '0' and c <= '9')
		x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return x * f;
}
int t;
char c[2005][2005];
pii a[26];
char tmp[2005][2005];
pair<int,bool>q[26];
int minn[26],maxx[26];
#define x(a) a.first
#define y(a) a.second
int ans1[26],ans2[26],ans3[26],ans4[26];
signed main() {
	t=read();
	while(t--){
		for(int i=0;i<=25;i++){
			a[i].first = a[i].second =0;
			q[i].first = q[i].second =0;
			minn[i]=maxx[i]=0;
		}
		int n=read(),m=read();
		for(int i=1;i<=n;i++)
			cin>>(c[i]+1);
		bool flag=true;
		for(int i=1;i<=n && flag;i++){
			for(int j=1;j<=m && flag;j++){
				char s=c[i][j];
				tmp[i][j]='.';
				if(c[i][j]=='.')
					continue;
#define id s-'a'
				if(a[id].first==0){
					a[id]=mp(i,j);
				}
				else{
					if(q[id].first == 0){
						if(i==a[id].first)
							q[id] = mp(i,0),minn[id] = a[id].second,maxx[id] = j;
						else if(j==a[id].second)
							q[id] = mp(j,1),minn[id] = a[id].first,maxx[id] = i;
						else{
							puts("NO");
							flag=false;
							break;
						}
					}
					else{
						if(q[id].second == 0){
							if(i != q[id].first){
								//cout<<1;
								puts("NO");
								flag=false;
								break;
							}
							maxx[id]=j;
						}
						else{
							if(j != q[id].first){
								puts("NO");
								flag=false;
								break;
							}
							maxx[id]=i;
						}
					}
				}
				
			}
		}
		if(!flag)
			continue;
		for(int i=0;i<=25;i++){
			if(a[i].first == 0)	continue;
			if(q[i].first ==0 ) tmp[a[i].first][a[i].second] = i+'a'; 
			else{
				if(q[i].second == 0){
					for(int j=minn[i];j<=maxx[i];j++)
						tmp[q[i].first][j] = i+'a';
				}
				else{
					for(int j=minn[i];j<=maxx[i];j++)
						tmp[j][q[i].first] = i+'a';
				}
			}
		}
		for(int i=1;i<=n && flag;i++){
			for(int j=1;j<=m && flag;j++){
//				if(c[i][j]=='.') continue;
				//cout<<tmp[i][j];
				if(c[i][j] != tmp[i][j]) {
					puts("NO");
					flag=false;
					break;
				}
			}
//			cout<<endl;
		}
		if(!flag) continue;
		int las=-1;
		for(int i=0;i<=25;i++){
			if(a[i].first == 0) 
				continue;
			las=i;
			if(q[i].first == 0){
				ans1[i]=a[i].first;
				ans2[i]=a[i].second;
				ans3[i]=a[i].first;
				ans4[i]=a[i].second;
			}
			else{
				if(q[i].second == 0){
					ans1[i]=q[i].first;
					ans2[i]=minn[i];
					ans3[i]=q[i].first;
					ans4[i]=maxx[i];
				}
				else{
//					cout<<minn[i]<<" "<<q[i].first<<" "<<maxx[i]<<" "<<q[i].first<<endl;
					ans2[i]=q[i].first;
					ans1[i]=minn[i];
					ans4[i]=q[i].first;
					ans3[i]=maxx[i];
				}
			}
		}
		for(int i=0;i<las;i++){
			if(a[i].first)
				continue;
			ans1[i]=a[las].first;
			ans2[i]=a[las].second;
			ans3[i]=a[las].first;
			ans4[i]=a[las].second;
		}
		puts("YES");
		if(las==-1)
			puts("0");
		else{
			cout<<las+1<<endl;
			for(int i=0;i<=las;i++){
				printf("%d %d %d %d \n",ans1[i],ans2[i],ans3[i],ans4[i]);
			}
		}
	}
	return 0;
}
```


---

## 作者：YLWang (赞：1)

这个题是属于比较简单的一类E。

首先我们遍历每种字符，对于每种字符的数量进行讨论。

1. 当前字符一个也没有

太简单了。直接涂在最后一个字符的任意一个格子上即可。因为最后一个字符一定存在，所以这次涂的一定会被覆盖掉。

2. 当前字符只有一个

太简单了。直接把它图上就行了。

~~于是这个题完成了一半~~

3. 当前字符有两个及以上

那么找出所有这种字符是否属于同一行/列。如果是，直接把最开始的到最后面的全部涂上。否则无解。

那么这个题做完了吗？

显然没有。还差最后一步。

因为我们每次涂只考虑到了当前能否涂上，而没有处理覆盖关系。

所以暴力的遍历一遍ans数组看看能不能实现原图就好了。

代码：
```
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define For(i, j, k) for(int i=(j);i<=(k);i++)
#define INF (2147483647>>1)
#define Pair pair<int,int>
#define ll long long
using namespace std;
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag=0;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return flag?num:-num;
}
#define MAXN 2005
int n, m;
int a[MAXN][MAXN], b[MAXN][MAXN]; 
struct Node {
	int x, y;
};
//bool cmp1(Node x, Node y) {
//	return x.x < y.x;
//}
//bool cmp2(Node x, Node y) {
//	return x.y < y.y;
//}
struct Square {
	int sx, sy, ex, ey;
};
vector < Node > pos[30];
vector < Square > ans;
int main()
{
    int T; cin >> T;
    while(T--) {
    	For(i, 1, 29) pos[i].clear();
    	ans.clear();
    	cin >> n >> m;
    	int maxi = 0;
    	For(i, 1, n)
    		For(j, 1, m)
    			a[i][j] = b[i][j] = 0;
    	For(i, 1, n) {
    		string s; cin >> s;
    		For(j, 1, m)
    			if(s[j-1] != '.')  {
    				a[i][j] = s[j-1] - 'a' + 1;
    				pos[a[i][j]].push_back((Node) {i, j});
    				maxi = max(maxi, a[i][j]);
				}
		}
		int num = 0;
		For(k, 1, maxi) {
			if(pos[k].size() == 0) {
				int X = pos[maxi][0].x, Y = pos[maxi][0].y;
				ans.push_back((Square) {X, Y, X, Y});
			} else if(pos[k].size() == 1) {
				int X = pos[k][0].x, Y = pos[k][0].y;
				ans.push_back((Square) {X, Y, X, Y});
			} else {
				int X1 = pos[k][0].x, Y1 = pos[k][0].y;
				int X2 = pos[k][1].x, Y2 = pos[k][1].y;
				if(X1 != X2 && Y1 != Y2) {
					puts("NO");
					goto end;
				}
				if(X1 == X2) {
					for(int i = 2; i < pos[k].size(); i++) {
						if(pos[k][i].x != X1) {
							puts("NO");
							goto end;
						}
					}
				}
				if(Y1 == Y2) {
					for(int i = 2; i < pos[k].size(); i++) {
						if(pos[k][i].y != Y1) {
							puts("NO");
							goto end;
						}
					}
				}
				ans.push_back((Square) {X1, Y1, pos[k][pos[k].size()-1].x, pos[k][pos[k].size()-1].y});
			}
		}
		for(int i = 0; i < maxi; i++) {
			For(j, ans[i].sx, ans[i].ex) {
				For(k, ans[i].sy, ans[i].ey) {
					b[j][k] = i+1;
				}
			}
		}
		For(i, 1, n) {
			For(j, 1, m) {
				if(a[i][j] != b[i][j]) {
					puts("NO");
					goto end;
				}
			}
		}
		printf("YES\n");
		printf("%d\n", maxi);
		for(int i = 0; i < maxi; i++) {
			printf("%d %d %d %d\n", ans[i].sx, ans[i].sy, ans[i].ex, ans[i].ey);
		}
		end:;
	}
    return 0;
}


```

---

## 作者：LittleChara (赞：0)

模拟题，感觉紫评高了，可以降绿或蓝。

显然操作次数是矩阵中字典序最大的字符的字典序，覆盖颜色不难做，重点是判可行性。

先按字典序顺序枚举当前应该填什么颜色，找出矩阵中第一次出现该颜色的位置和最后一次出现的位置，记为 $(sx,sy)$ 和 $(ex,ey)$。

对于矩阵中没有出现该颜色的情况，可以假定被下一种颜色完全覆盖。

判不可行需要判三种情况：

1. 判断是否在同一行或同一列，若否则不可行。因为只能填充横向或纵向的一条链。
2. 判断除了该行或该列之外是否有该颜色，若有则不可行。因为一种颜色只能填一次。
3. 判断这条链上是否有比当前颜色字典序小的颜色，若有则不可行。因为只允许字典序更大的颜色覆盖字典序小的颜色。

记得多测清空并按上述模拟即可。

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned ll
#define i128 __int128
#define db double
#define ld long db

#define M 2005
#define N 27
#define mod 290182597
#define mod2 1222827239
#define base 163729
#define base2 38833
#define inf 1e9+7
#define dinf 1e15
#define linf 7e18

int T;
int n,m;
char c[M][M];
int to[N];
struct node{
	int sx,sy,ex,ey;
}ans[N];
bool vis[M][M];

int main(){
	scanf("%d",&T);
	while(T--){
		bool ok=1;
		memset(to,0,sizeof to);
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;++i) scanf("%s",c[i]+1);
		int maxn=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(c[i][j]!='.') maxn=max(maxn,c[i][j]-'a'+1);
				vis[i][j]=0;
			}
		}
		for(int i=1;i<=26;++i){
			int sx=0,sy=0;
			for(int x=1;x<=n;++x){
				bool op=0;
				for(int y=1;y<=m;++y){
					if(c[x][y]-'a'+1==i){
						sx=x; sy=y;
						op=1;
						break;
					}
				}
				if(op) break;
			}
			int ex=0,ey=0;
			for(int x=n;x>=1;--x){
				bool op=0;
				for(int y=m;y>=1;--y){
					if(c[x][y]-'a'+1==i){
						ex=x; ey=y;
						op=1;
						break;
					}
				}
				if(op) break;
			} 
			if(!sx){
				to[i]=i+1;
				continue;
			}
			if(sx!=ex&&sy!=ey) {ok=0; goto end;}
			for(int x=sx;x<=ex;++x) for(int y=sy;y<=ey;++y) vis[x][y]=1;
			for(int x=1;x<=n;++x) for(int y=1;y<=m;++y) if(!vis[x][y]&&c[x][y]-'a'+1==i) {ok=0; goto end;}
			for(int x=sx;x<=ex;++x) for(int y=sy;y<=ey;++y) vis[x][y]=0;
			for(int x=sx;x<=ex;++x)
				for(int y=sy;y<=ey;++y)
					if(c[x][y]=='.'||c[x][y]-'a'+1<i) {ok=0; goto end;}
			ans[i]=(node){sx,sy,ex,ey};
		}
		for(int i=maxn;i>=1;--i){
			if(!to[i]) continue;
			ans[i]=ans[to[i]];
		}
		printf("YES\n%d\n",maxn);
		for(int i=1;i<=maxn;++i) printf("%d %d %d %d\n",ans[i].sx,ans[i].sy,ans[i].ex,ans[i].ey);
		end:{
			if(!ok) printf("NO\n");
			continue;	
		}
	}
	return 0;
}
```


---

## 作者：Zinc_acetate (赞：0)


[~~来孩子的小窝看看吧，求求你啦求求你啦~~](https://www.luogu.com.cn/blog/ZincAcetate/solution-cf1185e)

## 题意
在 $n \times m$ 的矩阵上画蛇，标号从 $a$ 到 $z$，后一条会覆盖前一条，给你矩阵最后的样子，推测是如何画蛇的。

## 思路

简单模拟，从标号最大的蛇开始，如果不能用一条直线连接或者首尾连上之后中间路径上有空白或比该蛇标号小的蛇， ~~这条蛇肯定“有问题”，直接寄，画不了一点，~~ 输出 ```NO``` 就好了，否则记录下这条蛇，最后输出答案就好。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
char c[2010][2010];
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a[26];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> c[i][j];
            if (c[i][j] != '.')
                a[c[i][j] - 'a'].push_back(make_pair(i, j));
        }
    }
    int k = 25;
    while (k >= 0 && (!a[k].size()))
        k--;
    if (k == -1)
    {
        cout << "YES\n0\n";
        return;
    }
    pair<pair<int, int>, pair<int, int>> ans[26];
    for (int i = k; i >= 0; i--)
    {
        if (a[i].size() == 0)
        {
            ans[i] = ans[i + 1];
            continue;
        }
        int mx1, mx2, my1, my2;
        mx1 = my1 = INT_MAX;
        mx2 = my2 = INT_MIN;
        for (auto j : a[i])
        {
            mx1 = min(mx1, j.first);
            mx2 = max(mx2, j.first);
            my1 = min(my1, j.second);
            my2 = max(my2, j.second);
        }
        if (mx1 != mx2 && my1 != my2)
        {
            cout << "NO\n";
            return;
        }
        if (mx1 == mx2)
        {
            ans[i] = make_pair(make_pair(mx1, my1), make_pair(mx2, my2));
            for (int j = my1; j <= my2; j++)
            {
                if (c[mx1][j] != 'a' + i && c[mx1][j] != 0)
                {
                    cout << "NO\n";
                    return;
                }
                c[mx1][j] = 0;
            }
        }
        else
        {
            ans[i] = make_pair(make_pair(mx1, my1), make_pair(mx2, my2));
            for (int j = mx1; j <= mx2; j++)
            {
                if (c[j][my1] != 'a' + i && c[j][my1] != 0)
                {
                    cout << "NO\n";
                    return;
                }
                c[j][my1] = 0;
            }
        }
    }
    cout << "YES\n";
    cout << k + 1 << endl;
    for (int i = 0; i <= k; i++)
    {
        cout << ans[i].first.first + 1 << ' ' << ans[i].first.second + 1 << ' ' << ans[i].second.first + 1 << ' ' << ans[i].second.second + 1 << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
```
---
---



---

