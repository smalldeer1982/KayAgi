# [ABC377C] Avoid Knight Attack

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc377/tasks/abc377_c

縦 $ N $ マス、横 $ N $ マスの $ N\ ^\ 2 $ マスからなるマス目があります。 上から $ i $ 行目 $ (1\leq\ i\leq\ N) $ 、左から $ j $ 列目 $ (1\leq\ j\leq\ N) $ のマスをマス $ (i,j) $ と呼ぶことにします。

それぞれのマスは、空マスであるかコマが置かれているかのどちらかです。 マス目には合計で $ M $ 個のコマが置かれており、$ k $ 番目 $ (1\leq\ k\leq\ M) $ のコマはマス $ (a\ _\ k,b\ _\ k) $ に置かれています。

あなたは、すでに置かれている**どのコマにも取られないように**、いずれかの**空マス**に自分のコマを置きたいです。

マス $ (i,j) $ に置かれているコマは、次のどれかの条件を満たすコマを取ることができます。

- マス $ (i+2,j+1) $ に置かれている
- マス $ (i+1,j+2) $ に置かれている
- マス $ (i-1,j+2) $ に置かれている
- マス $ (i-2,j+1) $ に置かれている
- マス $ (i-2,j-1) $ に置かれている
- マス $ (i-1,j-2) $ に置かれている
- マス $ (i+1,j-2) $ に置かれている
- マス $ (i+2,j-1) $ に置かれている

ただし、存在しないマスについての条件は常に満たされないものとします。

たとえば、マス $ (4,4) $ に置かれているコマは、以下の図で青く示されたマスに置かれているコマを取ることができます。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc377_c/399e5a909392dc44071791350bba40d75968dfd7.png)

あなたがコマを置くことができるマスがいくつあるか求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq10\ ^\ 9 $
- $ 1\leq\ M\leq2\times10\ ^\ 5 $
- $ 1\leq\ a\ _\ k\leq\ N,1\leq\ b\ _\ k\leq\ N\ (1\leq\ k\leq\ M) $
- $ (a\ _\ k,b\ _\ k)\neq(a\ _\ l,b\ _\ l)\ (1\leq\ k\lt\ l\leq\ M) $
- 入力はすべて整数

### Sample Explanation 1

すでに置かれているコマは、以下の図で青く示されたマスに置かれたコマを取ることができます。 ![](https://img.atcoder.jp/abc377/cb70c753c18ba20c291ba79e76f34599.png) よって、あなたがすでに置かれているコマに取られないように自分のコマを置くことができるマスは残りの $ 38 $ マスです。

### Sample Explanation 2

$ 10\ ^\ {18} $ マスのうち、置くことができないマスはマス $ (1,1),(2,3),(3,2) $ の $ 3 $ マスのみです。 答えが $ 2\ ^\ {32} $ 以上になる場合があることに注意してください。

## 样例 #1

### 输入

```
8 6
1 4
2 1
3 8
4 5
5 2
8 3```

### 输出

```
38```

## 样例 #2

### 输入

```
1000000000 1
1 1```

### 输出

```
999999999999999997```

## 样例 #3

### 输入

```
20 10
1 4
7 11
7 15
8 10
11 6
12 5
13 1
15 2
20 10
20 15```

### 输出

```
338```

# 题解

## 作者：cyx012113 (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc377_c)

[Atcoder 传送门](https://atcoder.jp/contests/abc377/tasks/abc377_c)
### 题目大意
有一个 $N$ 行 $N$ 列的网格，每个方格要么是空的，要么有一个“马”放在上面。网格上有 $M$ 个棋子，第 $k$ 个棋子被放置在 $(a_k,b_k)$。

例如，放在 $(4,4)$ 位置上的棋子可以吃掉**八个方向**上的棋子：

[![](https://cdn.luogu.com.cn/upload/image_hosting/0q70656z.png?x-oss-process=image/resize,m_lfit,h_200,w_200)](https://img.atcoder.jp/abc377/871985d4de26cef302c00cdd6f178880.png "点击可查看大图")

有多少个不会被马吃掉的棋子？
### 题目分析
我们发现，这道题目是[前一题](https://www.luogu.com.cn/problem/AT_abc377_b)的加强版，可以**用二维数组**记录被马吃掉的位置。  
但是，我们发现 $N\leq10^9$，很明显，直接记录数组，空间复杂度 $\mathcal{O}(N^2)$，时间复杂度 $\mathcal{O}(8\times M)$，无法通过。
> **空间复杂度**：  
> 对于开一个 $N\times N$ 的数组，不难得出时间复杂度为 $\mathcal{O}(N^2)$。
> 
> **时间复杂度**：  
> 输入并标记 $M$ 个位置，每个位置扩展出最多 $8$ 个点，可以同时计算，总用时 $\mathcal{O}(8\times M)$。

于是，我们想到，利用 map 记录下所有能被马攻击的坐标 **（包括马所在位置）**，最后进行计算就可以啦！  
最坏空间复杂度 $\mathcal{O}(3\times M)$，时间复杂度 $\mathcal{O}(8\times M \log_2M)$，可以通过。（$1\leq M\leq2\times10^5$）
> **空间复杂度**：
> 对于一个存储 $M$ 个元素的双下标 map，每个位置有 $3$ 个元素，空间复杂度为 $\mathcal{O}(3\times M)$。
>
> **时间复杂度**：
> - 输入 $M$ 个数，用时 $\mathcal{O}(M)$；
> - 每次扩展 $8$ 个方向，用时 $\mathcal{O}(8)$；
> - 每次插入 map，用时 $\mathcal{O}(\log_2M)$。
> 
> 综上所述，时间复杂度为 $\mathcal{O}(8\times M \log_2M)$。

我们可以打出八个方向的表，边输入边记录排除的格子。
> Q：如何使用 map 记录二维坐标？\
> A：使用 map 套用 pair。

代码有一些细节，需要注意：
> **注意：**
> - 题目样例二给出了提示，要**开 long long**。
> - 需要特判所记录格子**坐标是否越界**。
> - 需要记录马的所在位置。
> - 将 $x$、$y$ 坐标放入 map 时，需要用 make_pair 函数将 int 类型改为 pair。

具体介绍请看代码中的注释。
### 代码实现
```cpp
#include <bits/stdc++.h>
#define int long long // 提示：答案可能是2^32或更大
using namespace std;

map <pair <int, int>, bool> a; // 记录(x, y)位置放置棋子，是否能被马吃掉

int n, m, x, y;
int fx[] = {0, 2, 1, -1, -2, -2, -1,  1,  2}; // 打8个方向的表
int fy[] = {0, 1, 2,  2,  1, -1, -2, -2, -1};

signed main() {
	cin >> n >> m;
	for (int i = 1;i <= m;i++) {
		cin >> x >> y;
		a[make_pair(x, y)] = 1; // 注意：要记录马的所在位置
		for (int j = 1;j <= 8;j++) // 枚举8个方向
			if (x + fx[j] > 0 && y + fy[j] > 0 && x + fx[j] <= n && y + fy[j] <= n) // 特判：防止坐标越界
				a[make_pair(x + fx[j], y + fy[j])] = 1; // 将这个位置设为可被吃掉
	}
  // 进行数学运算：所有格子-可攻击格子=剩余格子，a.size()代表 map 中被使用过的格子数
	cout << n * n - a.size() << endl; 
    return 0;
}
```
> Update 2024.11.4
> - 对于时空复杂度的计算做详细介绍；
> - 因为 MarkDown 加粗需要，审核的管理请忽略第 18 行的多余空格。

---

## 作者：FlowerAccepted (赞：2)

## 前言

这就是一个国际象棋的马步，但 AT 非要藏头露尾的只给形式化题面，读题费时。

## 解题思路

这个题数据较大，显然不能通过暴力遍历检查每个正方形。

考虑枚举每个棋子的 $8$ 个移动，并将它们记录在一个去重的容器中，最后输出 $N^2 -$ 这个容器的大小 $- M$，即可。

## 细节实现

对于这个去重的容器，不难想到 `std::set`，为了方便，我们可以使用 `std::pair` 来存储一个骑士或被吃子位置。于是，我们使用两个 `set<pair<int, int>>` $knight$（存储每个骑士的位置），$capture$（吃子位置）来维护数据和答案。

骑士的走法可以用数组批量存储：

```cpp
int
jumpx[] = {-1,  1,  2,  2,  1, -1, -2, -2},
jumpy[] = {-2, -2, -1,  1,  2,  2,  1, -1};
```

`set` 的插入可以使用 `set.insert()`，遍历可以使用 `for (const auto& i : set) {}`，查询集合内是否有某元素可以使用 `set.count()`，查询大小可以使用 `set.size()`。

注意我们要在插入吃子位置前判断这个位置是否在棋盘内，具体的

```cpp
1 <= knight.first + jumpx[i] && knight.first + jumpx[i] <= n &&
1 <= knight.second + jumpy[i] && knight.second + jumpy[i] <= n
```

和这个位置是否已存在骑士

```cpp
!knights.count(make_pair(knight.first + jumpx[i], knight.second + jumpy[i]))
```

满足以上条件后，便可插入元素

```cpp
capture.insert(make_pair(knight.first + jumpx[i], knight.second + jumpy[i]));
```

核心代码整合一下，

```cpp
for (const auto& knight : knights) {
    for (int i = 0; i < 8; i ++) {
        if (1 <= knight.first + jumpx[i] && knight.first + jumpx[i] <= n &&
            1 <= knight.second + jumpy[i] && knight.second + jumpy[i] <= n &&
            !knights.count(make_pair(knight.first + jumpx[i], knight.second + jumpy[i]))) {
            capture.insert(make_pair(knight.first + jumpx[i], knight.second + jumpy[i]));
        }
    }
}
```

注意输出时要开 `long long`。十年 OI 一场空，不开 `long long` 见祖宗。

## 代码呈现

```cpp
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <set> // 不用万能头
using namespace std;

int
jumpx[] = {-1,  1,  2,  2,  1, -1, -2, -2},
jumpy[] = {-2, -2, -1,  1,  2,  2,  1, -1}; // 走法

set<pair<int, int> > knights, capture; // set，启动！

int main() {
    int n, m, x, y;
    long long ans; // 开long long 呦
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        cin >> x >> y;
        knights.insert(make_pair(x, y)); // 保险，使用make_pair
    }
    for (const auto& knight : knights) {
        for (int i = 0; i < 8; i ++) {
            if (1 <= knight.first + jumpx[i] && knight.first + jumpx[i] <= n &&
                1 <= knight.second + jumpy[i] && knight.second + jumpy[i] <= n && // 出界？
                !knights.count(make_pair(knight.first + jumpx[i], knight.second + jumpy[i]))) { // 把其它骑士吃了？
                capture.insert(make_pair(knight.first + jumpx[i], knight.second + jumpy[i])); // 插入
            }
        }
    }
    ans = n * 1ll * n - capture.size() - m; // 开long long
    cout << ans;
    return 0;
}

```

## 复杂度分析

`std::set` 底层使用红黑树，是一种非常平衡的平衡二叉树，插、查操作的平均时间复杂度是 $O(\log n)$，所以代码的时间复杂度就是 $O(M \log M)$，在这个数据范围下可以通过。

如果 STL 中没有这些现成的工具，这道题该评蓝罢。`vector`、数组查找都 $O(n)$，还得重载运算符并二分，可以 $O(\log n)$，但插入操作是避不掉的 $O(n)$，只能用一些神仙数据结构（平衡二叉树？~~珂朵莉树~~？）。STL 好闪，拜谢 STL。

---

## 作者：include13_fAKe (赞：2)

直接枚举马能够控制的格子，注意格子**必须在网格内**。

至于要考虑去重，可以用一个 `pair<int,int>` 来储存即可。然后排序计算哪些是重复的。（实际上我用的是 struct）。然后再拿 $n^2$ 减去被控制的格子数即可。**注意马所在的格子本身也是被控制的。**

用 map 可能会炸，建议不用。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2e6;
int n,m;
struct node{
	int x,y;
}include13[maxn];
int ptr=0;
int dx[9]={1,2,2,1,-1,-2,-2,-1,0};
int dy[9]={-2,-1,1,2,2,1,-1,-2,0};
bool cmp(node a,node b){
	if(a.x==b.x)	return a.y<b.y;
	return a.x<b.x;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		for(int j=0;j<=8;j++){
			int tx=x+dx[j];
			int ty=y+dy[j];
			if(1<=tx&&tx<=n&&1<=ty&&ty<=n){
				include13[++ptr]=(node){tx,ty};
//				cout<<tx<<' '<<ty<<endl;
			}
		}
	}
	sort(include13+1,include13+ptr+1,cmp);
	int ans=0;
	for(int i=1;i<=ptr;i++){
		if(include13[i].x!=include13[i-1].x||include13[i].y!=include13[i-1].y)	ans++;
	}
	cout<<n*n-ans<<endl;
	return 0;
} //ABC377C 
```

---

## 作者：sherry_lover (赞：0)

# AT_abc377_c [ABC377C] Avoid Knight Attack 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc377_c)

## 思路

这题就不能像 B 那样开二维数组标记了，由于马只能防住 $9$ 个位置（自己所在的位置也要算上），可以开一个 map 来记录下某个位置是否被防御，注意答案要开 long long。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[10][2] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1},{0,0}};
map<pair<int,int>,bool> mp;
long long ans,n,m;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	ans = n*n;
	for(int i = 1,x,y;i <= m;i++)
	{
		cin >> x >> y;
		for(int j = 0;j < 9;j++)
		{
			int xx = x+f[j][0],yy = y+f[j][1];
			if(xx >= 1 && xx <= n && yy >= 1 && yy <= n)
			{
				if(!mp[{xx,yy}]) ans--;
				mp[{xx,yy}] = 1;
			}
		}
	}
	cout << ans;
    return 0;
}
```

---

## 作者：kikilong_mamba (赞：0)

# [AT_abc377_c](https://atcoder.jp/contests/abc377/tasks/abc377_c)题解
## 解法分析
题目中的棋子其实就是中国象棋中的”马“。

我们一看数据量，$n$ 高达 $10^9$，连数组都开不了，只能用别的方法。

其实我们可以用一个 set（自动排序去重容器）存所有被棋子控制的位置，然后用总格子数减去被控制的位置的个数，即为答案。整体代码应该算不上难写。

[这里有关于 set 的教程。](https://blog.csdn.net/yas12345678/article/details/52601454)

## AC code
（777ms 险过本题）
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
using namespace std;
inline int read()
{
	int a=0,b=0,c=getchar();
	while(!isdigit(c) && c!=-1) b|=(c==45),c=getchar();
	while(isdigit(c)) a=a*10+(c^48),c=getchar();
	return b?~(a-1):a;
}
//上面这些乱七八糟的东西不用看
const int dx[]{1,2,1,2,-1,-2,-1,-2},dy[]{2,1,-2,-1,2,1,-2,-1};
int n;
set<pair<int,int> >s;
signed main()
{
	n=read();
	for(rint _=read();_;--_)
	{
		int x=read(),y=read();
		s.insert({x,y}); //注意，棋子原位置也被控制，是本题一个坑点
		for(rint i=0;i<8;++i)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(xx>0 && yy>0 && xx<=n && yy<=n) s.insert({xx,yy});
		}
	}
	cout<<n*n-s.size();
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个大小为 $N\times N$ 的矩阵，现在此矩阵上有 $M$ 个标记，若一个标记坐标为 $(i,j)$，则 $(i+2,j+1),(i+1,j+2),(i-1,j+2),(i-2,j+1),(i-2,j-1),(i-1,j-2),(i+1,j-2),(i+2,j-1)$ 这八个位置都会被标记，问最后矩阵上有多少个点没有被标记，数据范围 $N\le 10^9,M\le 2\times 10^5$。

## 解题思路

这一题暴力的思路不难想到，就是手动模拟矩阵的标记，接下来考虑在 $N$ 极大的情况下如何标记。可以发现 $M$ 很小，这意味着最后被标记的点数也会很小，最多只有 $1.8\times 10^6$ 个点被标记，所以我们可以对标记点的编号进行离散化。~~而我比较懒，~~ 很容易可以想到将一个坐标对先转换为一个数字，再将此数字转换为字符串，用 `unordered_map` 存储模拟标记的过程，同时计算答案即可。总时间复杂度 $O(M)$，常数平均为 $100$ 左右。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,m,x,y,ans;
string t;
unordered_map<string,ll> mp;
ll calc(ll x, ll y) {return x*n+y;}
string itos(ll x)
{string res=""; while(x) res+=x%10+48, x/=10; return res;}

void put(ll x, ll y)
{
    if(x>0 && x<=n && y>0 && y<=n)
    {
        t=itos(calc(x,y));
        if(!mp[t]) mp[t]=1, --ans;
    }
}

int main()
{
    n=read(); m=read(); ans=n*n;

    while(m--)
    {
        x=read(); y=read(); put(x,y);
        put(x+2,y+1); put(x+1,y+2);
        put(x-1,y+2); put(x-2,y+1);
        put(x-2,y-1); put(x-1,y-2);
        put(x+1,y-2); put(x+2,y-1);
    }

    write(ans);
    return 0;
}
```

---

## 作者：Hacker_Cracker (赞：0)

## [ABC377C] Avoid Knight Attack 题解
### Solution
注意到 $N \le 10^9$，显然开 $N\times N$ 的二维数组模拟是不可行的。注意到 $M$ 的大小比较正常，考虑存储每个马及其扩展点然后去重。

~~STL 大法好。~~

使用 set 维护横纵坐标，每次将马及扩展点的坐标存进去，最后它的大小就是不能放置棋子的点数。因为扩展点最多只有 $2 \times 10^5 \times 9=1.8 \times 10^6$ 个，空间不会超限。

时间复杂度 $O(N \log N)$，可以通过本题。

### [AC](https://www.luogu.com.cn/record/185773684) Code
```cpp
#include<iostream>
#include<cstring>
#include<set>
using namespace std;
set<pair<int,int> >s;
int dx[]={0,-2,-1,1,2,2,1,-1,-2};
int dy[]={0,-1,-2,-2,-1,1,2,2,1};
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		for(int j=0;j<=8;j++){
			int xx=x+dx[j];
			int yy=y+dy[j];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=n){
				s.insert(make_pair(xx,yy));
			}
		}
	}
	cout<<(long long)n*n-s.size()<<endl;
	return 0;
}
```
至此本篇题解就结束啦。

---

## 作者：liuziqin (赞：0)

## 思路

虽然 $n$ 看起来非常吓人，但可被攻击的点是可以被枚举的。

考虑开一个二维的 map 存储能被攻击到的点。每当加入一个点时，将该点可以攻击到的点加入 map 中，接着统计 map 中的点数，最后用总点数减去可被攻击的点的总数即可。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<int,map<int,int> >mp; 
int n,m;
bool check(int x,int y){
	return 1<=x&&x<=n&&1<=y&&y<=n; 
}
signed main(){
	cin>>n>>m;
	int ans=n*n;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(check(x,y)&&!mp[x][y])ans--,mp[x][y]=1;
		if(check(x+1,y+2)&&!mp[x+1][y+2])ans--,mp[x+1][y+2]=1;
		if(check(x+1,y-2)&&!mp[x+1][y-2])ans--,mp[x+1][y-2]=1;
		if(check(x-1,y+2)&&!mp[x-1][y+2])ans--,mp[x-1][y+2]=1;
		if(check(x-1,y-2)&&!mp[x-1][y-2])ans--,mp[x-1][y-2]=1;
		if(check(x+2,y+1)&&!mp[x+2][y+1])ans--,mp[x+2][y+1]=1;
		if(check(x+2,y-1)&&!mp[x+2][y-1])ans--,mp[x+2][y-1]=1;
		if(check(x-2,y+1)&&!mp[x-2][y+1])ans--,mp[x-2][y+1]=1;
		if(check(x-2,y-1)&&!mp[x-2][y-1])ans--,mp[x-2][y-1]=1;
//可被攻击的点
	}
	cout<<ans<<"\n";//输出
}
```

---

## 作者：cjh_trailblazer (赞：0)

[原题面](https://atcoder.jp/contests/abc377/tasks/abc377_c)
## 题目分析：
没啥好说的，直接模拟。对于每个放置的马，会修改 $9$ 个格子的状态，那我们直接开个 map 存储格子状态，最后用整体格子数减去枚举出的格子数即可。
## [Code](https://atcoder.jp/contests/abc377/submissions/59207831)

---

