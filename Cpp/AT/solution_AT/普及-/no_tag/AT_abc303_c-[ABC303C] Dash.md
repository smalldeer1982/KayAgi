# [ABC303C] Dash

## 题目描述

现在高桥在一个二维平面上。初始时他在 $(0,0)$ 处，生命值为 $H$。平面上有 $M$ 个可以恢复生命值的物品，其中第 $i$ 个物品的位置为 $(x_i,y_i)$。

高桥将要进行 $N$ 次移动，第 $i$ 次移动的方式如下：

- 设高桥现在的位置是 $(x,y)$，那么他将会消耗 $1$ 点生命值，同时：
  - 如果 $S_i=\texttt R$，移动到 $(x+1,y)$；
  - 如果 $S_i=\texttt L$，移动到 $(x-1,y)$；
  - 如果 $S_i=\texttt U$，移动到 $(x,y+1)$；
  - 如果 $S_i=\texttt D$，移动到 $(x,y-1)$。
- 如果高桥的生命值降为负数，他就会倒下无法行动；否则，如果当前位置有一个可以恢复生命值的物品，且当前生命值小于 $K$，那么生命值将会恢复到 $K$。

请判断高桥能否进行完所有的移动而不倒下。

#### 数据范围与约定

$1\le N,M,H,K\le2\times10^5$，$|x_i|,|y_i|\le2\times10^5$。

保证 $S$ 是一个只由字符 `R`、`L`、`U`、`D` 构成的长度为 $N$ 的字符串。保证 $(x_i,y_i)$ 两两不同。保证所有输入的数均为整数。

## 样例 #1

### 输入

```
4 2 3 1
RUDL
-1 -1
1 0```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 2 1 5
LDRLD
0 0
-1 -1```

### 输出

```
No```

# 题解

## 作者：未来姚班zyl (赞：2)

## 题目大意
在一个二维平面中，有 $M$ 个位置不同的医疗包，一个拥有 $H$ 健康值的人初始时在点 $(0,0)$，他按照给定路径行走 $N$ 步（每步从上下左右四个方向中选一个），每一步会使健康值减少 $1$，走到一个新的点后，如果这个点有医疗包且这个人的健康值严格小于 $K$，则他会使用这个医疗包并将健康值恢复到 $K$。在这个过程中，如果他的健康值降到了负数，则他会倒下。问他能不能坚持走完全程。

$1\le N,M\le 2\times10^5$，医疗包坐标 $(x_i,y_i)$ 满足 $ |x_i|,|y_i|\le2\times 10^5$。
## 题目分析
乍一看是一道模拟题，但根据数据范围，医疗包的坐标即不能暴力枚举，也不能直接开一个 $vis$ 数组来记录。这就需要想一个方法来判断一个位置是否有医疗包。那么各路大神们可能会直接用 set，map 或是哈希来做。不过没学过这些也没关系。由于医疗包的位置不会重复，可以直接二分查找。具体做法就是将医疗包先按照横坐标从小到大排序，然后相同横坐标的按纵坐标从小到大排序。然后对于每一个存在的横坐标，记录它在排好序的医疗包中的右端点，然后要查询时，先按横坐标二分，再在横坐标的内部按纵坐标二分，判断二分查找出来的坐标和当前坐标是否相等就行了。最后对医疗包开一个 vis 数组，这个问题就解决了。

最后按照题目模拟就行，要注意，应该是先走一步再在终点吃医疗包。

这样复杂度 $O(N \log M)$，常数极小，轻松拿到[最优解](https://www.luogu.com.cn/record/111517115)。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pf printf
#define cf scanf
#define rt return
using namespace std;
const int N=2e5+5;
const int del=2e5;
int n,m,h,k;
bool vis[N];
struct node{
	int x,y;
}a[N];
int R[N*2];
bool cmp(node a,node b){
	if(a.x^b.x)return a.x<b.x;
	return a.y<b.y;
}
string s;
int main(){
	cin >>n>>m>>h>>k;
	cin >>s;
	for(int i=1;i<=m;i++)cf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+m+1,cmp);
	a[m+1].x=20000000;
	for(int i=2;i<=m+1;i++)if(a[i].x^a[i-1].x)R[a[i-1].x+del]=i;
	int x=0,y=0;
	for(int i=0;i<n;i++){
		char c=s[i];
		if(c=='R')x++;
		else if(c=='L')x--;
		else if(c=='U')y++;
		else y--;
		if(h==0){cout <<"No";return 0;
		}
		h--;
		
		if(h<k){
		int l=1,r=m,pos=-1;
		while(l<=r){
			int mid=(l+r>>1);
			if(a[mid].x>=x)pos=mid,r=mid-1;
			else l=mid+1;
		}
		if(pos!=-1&&a[pos].x==x){
			l=pos,r=R[a[pos].x+del]-1,pos=-1;
			while(l<=r){
			int mid=(l+r>>1);
			if(a[mid].y>=y)pos=mid,r=mid-1;
			else l=mid+1;
			}
			if(pos!=-1&&a[pos].y==y&&!vis[pos])vis[pos]=1,h=k;
		}
		}
	}
	cout <<"Yes";
	return 0;
}
```


---

## 作者：__Emerald__ (赞：2)

模拟即可。若用普通二维数组，则复杂度为 $O(X^2)$，其中 $X=\max({|a_i|},{|b_i|})$，不能承受。我们可以用 `set` 记录下每个补给品的位置，复杂度为 $O(N+M\log M)$，可以承受。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,m,h,k;
    cin >> n >> m >> h >> k;
    string s;
    cin >> s;
    set<pair<int, int> > st;
    for(int i = 0;i < m;i++){
        int x,y;
        cin >> x >> y;
        st.insert({x, y});
    }
    int nx = 0,ny = 0;
    for(int i = 0;i < n;i++) {
        int dx = 0,dy = 0;
        if(s[i] == 'R') dx = 1;
        if(s[i] == 'L') dx = -1;
        if(s[i] == 'U') dy = 1;
        if(s[i] == 'D') dy = -1;
        nx += dx,ny += dy;
        if(--h < 0) {
            cout << "No\n";
            return 0;
        }
        if(h < k and st.count({nx, ny})) {
            h = k;
            st.erase({nx, ny});
        }
    }
    cout << "Yes\n";
    return 0;
}
```

---

## 作者：xiaoming007 (赞：1)

## 思路

由于 $x,y$ 可能为负数，且二维数组开不下，我们如果用一个长度为 $m$ 的数组存的话，再执行 $n$ 次操作，这样复杂度 $O(nm)$，通过不了，考虑更优的存储 $x,y$ 方式。

易想到 STL 中的 `map`，对于每组 $x,y$，仅需将 `map` 中 `insert` 一个为 $\{x,y\}$ 的结构体即可。

接下来仅需根据题意模拟。

但是注意细节问题：

- 先扣后回血，也就是说，尽管走到了药包，但是如果血量 $< 0$，还是无法正常到达。

- 本题的方向和一般的方向不一样。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int x, y;
	bool operator < (const node &a) const {
		if(x == a.x) return y < a.y;
		return x < a.x;
	}
};
map<node, bool> mp;
int main(){
	int n, m, h, k;
	scanf("%d%d%d%d", &n, &m, &h, &k);
	
	char s[201010];
	scanf("%s", s);int x = 0, y = 0;
	for(int i = 1; i <= m; ++i){
			int x, y;
			scanf("%d%d", &x, &y);
			mp[{x, y}] = 1;
		}
	for(int i = 0; i < n; ++i){
		
		--h;
		if(s[i] == 'R') ++x;
		else if(s[i] == 'L') --x;
		else if(s[i] == 'U') ++y;
		else --y;
		if(h < 0){
					return puts("No"), 0;
				}
		if(mp[{x, y}] == 1){
			if(h < k){
				h = k;
				mp[{x, y}] = 0;
			}
		} 
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：0xyz (赞：1)

按照题意模拟即可。由于 $M\le 2\times 10^5$，所以可以用 map 记录所有有东西可以回血的地点。维护 $2$ 个变量 $x,y$，一开始设为 $0$。对于每一步先后进行以下 $4$ 个操作。

$(1)$ 移动。按照对应的字符将对应的变量加减即可。

```cpp
if(s[i]=='U')y++;
else if(s[i]=='D')y--;
else if(s[i]=='L')x--;
else if(s[i]=='R')x++;
```

$(2)$ 扣血。

```cpp
h--;
```

$(3)$ 判断死亡。题目说了，无论是第几次操作，这个格子能不能回血，只要血量为负就会死。

```cpp
if(h<0){
	cout<<"No"<<'\n';
	return 0;
}
```

$(4)$ 回血。如果当前此人没有死并且血量严格小于 $k$，那么血量会回到 $k$。并且由于回血会将格子上的东西消耗掉，要记得让这个格子不再能回血。

```cpp
if(a[{x,y}]&&h<k)h=k,a[{x,y}]=0;
```

最后，如果一直没死，输出 `Yes`。

总的代码，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,h,k,x=0,y=0;
string s;
map<pair<ll,ll>,bool>a;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>h>>k>>s;
	for(ll i=1,X,Y;i<=m;i++){
		cin>>X>>Y;
		a[{X,Y}]=1;
	}
	for(ll i=0;i<n;i++){
		if(s[i]=='U')y++;
		else if(s[i]=='D')y--;
		else if(s[i]=='L')x--;
		else if(s[i]=='R')x++;
		h--;
		if(h<0){
			cout<<"No"<<'\n';
			return 0;
		}
		if(a[{x,y}]&&h<k)h=k,a[{x,y}]=0;
	}
	cout<<"Yes"<<'\n';
	return 0;
}
```

---

## 作者：guanyf (赞：0)

### 题意
- 给定 $N,M,H,K$，高桥初始时在 $(0,0)$ 上，生命值是 $H$。给定高桥的 $N$ 次移动，分别为：

1. `R`：$(x+1,y)$
1. `L`：$(x-1,y)$
1. `U`：$(x,y+1)$
1. `D`：$(x,y-1)$

高桥每一次移动，都会消耗一点生命值。在平面上还有 $M$ 个急救箱，当高桥移动到急救箱的位置上且生命值严格小于 $K$ 时，才能使用急救箱。使用之后，急救箱会消失，高桥的生命会变成 $K$。求高桥是否能在生命值不为负的情况下，完成所有的移动。

- $1 \le N,M,H,K \le 2 \times 10^5$

### 思路
直接按照题意模拟即可。我们可以用 `unordered_map` 记录下每个急救箱的位置和高桥所在的位置，在按照题意操作就行了。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
unordered_map<char, pair<int, int>> KD;
unordered_map<int, unordered_map<int, bool>> vis;
int n, m, h, k, nx, ny;
string s;
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m >> h >> k >> s, s = ' ' + s;
  KD['R'] = {1, 0}, KD['L'] = {-1, 0}, KD['U'] = {0, 1}, KD['D'] = {0, -1};
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y, vis[x][y] = 1;
  }
  for (int i = 1; i <= n; i++) {
    nx += KD[s[i]].first, ny += KD[s[i]].second, h--;
    if (h < 0) {
      cout << "No", exit(0);
    }
    if (h < k && vis[nx][ny]) {
      h = k, vis[nx][ny] = 0;
    }
  }
  cout << "Yes";
  return 0;
}
```


---

## 作者：Cure_Wing (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc303_c)

### 解析

容易发现这是一道按要求走路然后路上还能吃东西回血的模拟题，所以直接按要求模拟就可以了。

考虑 $|x_i|,|y_i|\le2\times10^5$，于是用 `map` 存储，由于 $1\le N,M\le2\times10^5$，所以经过的点最多 $4\times10^5$ 个，直接用就好，不会爆内存。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
using std::cin;using std::cout;
int n,m,h,k,x,y,a,b;
std::map<int,std::map<int,bool> >p;
std::string s;
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m>>h>>k>>s;
	for(int i=1;i<=m;++i){
		cin>>x>>y;
		p[x][y]=1;//使用map进行标记宝盒
	}
	for(int i=0;i<n;++i){
		if(s[i]=='U') ++b;
		if(s[i]=='D') --b;
		if(s[i]=='L') --a;
		if(s[i]=='R') ++a;//按要求走路
		--h;
		if(h<0){
			cout<<"No";//失血而死
			return 0;
		}
		if(p[a][b]&&h<k){
			h=k;p[a][b]=0;//如果需要使用就用掉
		}
	}
	cout<<"Yes";//挺过来了
    return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

给你四个正整数 $n,m,h,k$。有一个人站在点 $(0,0)$，初始时他的生命值为 $h$，他每走一步生命值减少 $1$。在坐标系中有 $m$ 件物品，如果他所在的格子有物品且他的生命值严格小于 $k$，那么他的生命值会变成 $k$ 并**消耗**该物品。他一共有 $n$ 次移动，一旦他在移动过程中生命值为 $-1$，那么称他失败，问他是否成功。

备注：哪怕在他生命值为 $-1$ 时他的格子为终点或有物品，也称为失败；没有两个物品在同一位置。

**分析**

没有节点在同一位置，记录物品位置，较长的题面，理想的复杂度 $O(n \log m)$，都提示着做法：map 模拟。

`map<pair<int,int>,int>` 来定义 map，其键为一个坐标 $(x,y)$，若该处有物品，其值为 $1$。接下来对 $n$ 次移动，先处理当前位置，然后是生命值（顺便判断是否失败），最后查找是否有物品就行了。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int x,y;//当前位置
int main()
{
	int n,m,h,k;
	string s;
	map<pair<int,int>,int> mp;//map的定义
	cin>>n>>m>>h>>k;
	cin>>s;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;//输入的时候借用一下这两个变量
		mp[{x,y}]=1;//这个位置有物品
	}
	x=0;//借用完毕
	y=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='L')//向左
		{
			x--;
			h--;
			if(h<0)//判断血量
			{
				cout<<"No";
				return 0;
			}
			if(mp[{x,y}]&&h<k)//是否使用物品
			{
				h=k;
				mp[{x,y}]=0;
			}
		}
		if(s[i]=='R')//向右
		{
			x++;
			h--;
			if(h<0)
			{
				cout<<"No";
				return 0;
			}
			if(mp[{x,y}]&&h<k)
			{
				h=k;
				mp[{x,y}]=0;
			}
		}
		if(s[i]=='U')//向上
		{
			y++;
			h--;
			if(h<0)
			{
				cout<<"No";
				return 0;
			}
			if(mp[{x,y}]&&h<k)
			{
				h=k;
				mp[{x,y}]=0;
			}
		}
		if(s[i]=='D')//向下
		{
			y--;
			h--;
			if(h<0)
			{
				cout<<"No";
				return 0;
			}
			if(mp[{x,y}]&&h<k)
			{
				h=k;
				mp[{x,y}]=0;
			}
		}
	}
	cout<<"Yes";
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

这题首先想到暴力做法，$ O(N) $ 去模拟，每次模拟的时候，如果 $ H < K $ 了，就 $ O(M) $ 去找这个位置是不是补给点，如果是，就把 $ H $ 变为 $ K $。 但是，复杂度过不去。

## 优化

这题我们可以想到开一个很大的数组来存这个地图哪里是有补给的，但是，数组肯定开不下。

### 空间优化

我们可以想一下怎么优化，这时候 ``set`` 就该出场了。``set`` 有一个函数叫 ``find()``,它可以在 $ \log M $ 的复杂度里找到它是不是补给点,所以，复杂度变成了 $ O(M \log M) $ 的复杂度，能通过本题。

下面看代码：

~~~cpp


#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
set<pair<ll, ll> > se;
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll n, m, h, k;
	cin >> n >> m >> h >> k;
	string s;
	cin >> s;
	ll x = 0, y = 0;
	ll xx, yy;
	for (int i = 1; i <= m; i++) {
		cin >> xx >> yy;
		pair<ll, ll> u = make_pair(xx, yy);
		se.insert(u);
	}
	if (h >= n) {
		cout << "Yes";
		return 0;
	}
	bool flag = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'R') {
			x++;
		} else if (s[i] == 'L') {
			x--;
		} else if (s[i] == 'U') {
			y++;
		} else {
			y--;
		}
		h--;
		if (h < 0) {
			flag = 1;
			break;
		}
		if (h < k) {
			auto t = se.find(make_pair(x, y));
			if (t != se.end()) {
				h = k;
				se.erase(t);
			}
		}
	}
	if (flag) {
		cout << "No";
	} else {
		cout << "Yes";
	}
	return 0;
}



~~~

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc303_c)     
细节量巨大的一道题。         
我们按题意模拟即可，但是这里说几个点：     
- 最后一步死了不算 `Yes`。      
- 回血是必须严格小于 $k$ 的。
- 回血只能用一次。（一个 HL 群友告诉我的，这里特别感谢，~~不然掉大分~~）    

我们可以把每步坐标的变化存进 unordered_map 里，方便而且速度快。      
[CODE](https://www.luogu.com.cn/paste/0vp5u30u)

---

