# Manhattan Circle

## 题目描述

给定一个由“.”和“#”字符组成的n*m的网格，网格上存在一个完整的曼哈顿圆。网格的左上角坐标为(1,1)
，右下角坐标为(n,m) 。
如果|h-a| +|k-b|<r，则点（a,b）属于以（h,k）为中心的曼哈顿圆，其中r是正常数。
在网格上，作为曼哈顿圆一部分的点集被标记为“#”。找到圆心的坐标。

## 样例 #1

### 输入

```
6
5 5
.....
.....
..#..
.....
.....
5 5
..#..
.###.
#####
.###.
..#..
5 6
......
......
.#....
###...
.#....
1 1
#
5 6
...#..
..###.
.#####
..###.
...#..
2 10
..........
...#......```

### 输出

```
3 3
3 3
4 2
1 1
3 4
2 4```

# 题解

## 作者：Kindershiuo (赞：4)

# 解题思路
这道题的话我是这样想的，我们的曼哈顿圆的中心一定是在我所有出现井号的行的中间一行，以及所有出现井号的中间一列，那么我们记录一下所有出现井号的行和列，然后取它们的中间行和中间列就是答案了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int T;

void solve() {
	map<int, int>mahan;
	map<int, int>mashu;
	int n, m;
	cin >> n >> m;
	char c[n + 5][m + 5];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> c[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (c[i][j] == '#') {
				mahan[i] = 1;
				mashu[j] = 1;
			}
		}
	}
	int s1 = mahan.size();
	s1 = (s1 + 1) / 2;
	int cnt = 0;
	for (auto it = mahan.begin(); it != mahan.end(); it++) {
		cnt++;
		if (cnt == s1)
			cout << it->first << " ";
	}
	int s2 = mashu.size();
	s2 = (s2 + 1) / 2;
	cnt = 0;
	for (auto it = mashu.begin(); it != mashu.end(); it++) {
		cnt++;
		if (cnt == s2 )
			cout << it->first << endl;
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：BrotherCall (赞：2)

## 题意

给定一个由 `#` 和 `.` 组成的 $n \times m$ 的网格，网格上存在一个由 `#` 构成的完整的曼哈顿圆，求这个曼哈顿圆的中心。

以 $(a,b)$ 为中心，半径为 $r$ 的曼哈顿圆的定义：将与 $(a,b)$ 曼哈顿距离小于 $r$ 的点全设置成 `#`，$r$ 为正整数。

## 思路

画图发现曼哈顿圆一定是一个菱形（$r = 1$ 的时候是一个点）。

那么中心点就是 `#` 最长的一行的连续 `#` 的中点。

扫一遍得到横坐标 $x_0$，记录下该行第一个 `#` 纵坐标 $y_1$ 和最后一个 `#` 纵坐标 $y_2$，中心即为 $\displaystyle (x_0 , \frac{y_1+y_2}{2})$。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

const int N = 1e6 + 100;
char ch[N];
int t , n , m , a[N];

signed main() {
	cin >> t;
	while(t --) {
		cin >> n >> m;
		int maxx = 0;
		int x , y;
		for(int i = 1;i <= n;i ++) {
			scanf("%s" , ch + 1);
			int now = 0 , zh = 0 , zq = 0;
			for(int j = 1;j <= m;j ++) {
				if(ch[j] == '#') {
					if(now == 0) zq = j;
					now ++ , zh = j;
				}
			}
			if(now > maxx) {
				maxx = now;
				x = i;
				y = (zq + zh) / 2;
			}
		}
		cout << x << ' ' << y << "\n";
	}
	return 0;
}
```

---

## 作者：OPEC (赞：2)

# [CF1985D Manhattan Circle](https://www.luogu.com.cn/problem/CF1985D)

这道题会发现曼哈顿圆的中心点在最多井号的一列和一行的交界处。预处理每行和每列井号的个数，再找出井号最多的一列和一行就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e3+10,M=2e5+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t,n,m;
void solve()
{
	int h[M];
	int s[M];
	memset(h,0,sizeof(h));
	memset(s,0,sizeof(s));
	cin>>n>>m;
	char a[n+10][m+10];//注意要放在里面，因为n*m小于2e5时，n可能是2e5，m是1
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]=='#')
			{
				h[i]++;
				s[j]++;
			}
		}
	}
	int tt=0;
	int bi,bj;
	for(int i=1;i<=n;i++)
	{
		if(h[i]>tt)
		{
			bi=i;
			tt=h[i];
		}
	}
	tt=0;
	for(int i=1;i<=m;i++)
	{
		if(s[i]>tt)
		{
			bj=i;
			tt=s[i];
		}
	}
	cout<<bi<<' '<<bj<<'\n';
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：tanzexiaodezhonghao (赞：0)

## 思路
很水的一道题，数组都不用，我觉得是个红的难度。题目的意思是让你求一个曼哈顿圆的圆心，但通过观察样例，我们发现所谓的曼哈顿圆是一个菱形。再经过观察，发现菱形的中心在井号最多的那一行的中心。但肯定不能像求最大值一样跑 $O(T(nm)^3)$，所以我们可以一边输入一边求，中心点所在的列，就是菱形左端点和右端点的平均值。代码很好写，时间复杂度为 $O(Tnm)$。另外不建议开数组，我开数组结果爆了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define genshin_start ios::sync_with_stdio(false);cin.tie(0);
int T;int n,m;char ch;
int main(){genshin_start;
    cin>>T;
    while(T--){
cin>>n>>m;int x=0,y=0,maxans=0,starts=0,ends=0;//starts表示菱形左端点，ends表示右端点。
for(int i=1;i<=n;i++){int cnt=0;//长度。
ends=0,starts=0;
    for(int j=1;j<=m;j++){
        cin>>ch;
        if(ch=='#'){
            if(cnt==0){starts=j;}
            cnt++;ends=j;
        }
    }
    if(cnt>maxans){maxans=cnt;
        x=i;y=(ends+starts)/2;//求中心点。
    }
}cout<<x<<" "<<y<<endl;
    
    }
    return 0;
}
```
~~码风有点烂~~

---

## 作者：nightwatch.ryan (赞：0)

### 思路
题目让我们求一个曼哈顿圆的圆心，观察样例发现，曼哈顿圆实际上就是一个菱形。所以我们：

- 第一步，找出所有边界点的坐标。
- 第二步，将所有横轴和纵轴的坐标分开。
- 第三步，分别将横轴和纵轴的坐标排序。
- 最后一步，输出横坐标和纵坐标的中位数。

这个方法是基于中位数最小化绝对偏差的原理：在曼哈顿距离下，中位数点能使所有点到圆心的曼哈顿距离总和最小。
### 代码
```cpp
#include<iostream>
#include<climits>
#include<queue>
#include<map>
#include<algorithm>
#define int long long
std::map<std::pair<int,int>,char>mp;
void solve(int T){
	if(T==0)return;
	int n,m;
	std::cin>>n>>m;
	mp.clear();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			std::cin>>mp[{i,j}];
	int U_i,U_j,D_i,D_j,L_i,L_j,R_i,R_j;
	//求上坐标 
	for(int i=1;i<=n;i++){
		int cnt=0;
		int jj=0;
		for(int j=1;j<=m;j++)
			if(mp[{i,j}]=='#')jj=j,cnt++;
		if(cnt==1){
			U_i=i;
			U_j=jj;
			break;
		}
	}
	//求下坐标 
	for(int i=n;i>=1;i--){
		int cnt=0;
		int jj=0;
		for(int j=1;j<=m;j++)
		if(mp[{i,j}]=='#')jj=j,cnt++;
		if(cnt==1){
			D_i=i;
			D_j=jj;
			break;
		}
	}
	//求左坐标 
	for(int j=1;j<=m;j++){
		int cnt=0;
		int jj=0;
		for(int i=1;i<=n;i++){
			if(mp[{i,j}]=='#')jj=i,cnt++;
		} 
		if(cnt==1){
			L_i=jj;
			L_j=j;
			break;
		}
	}
	//求右坐标
	 for(int j=m;j>=1;j--){
		int cnt=0;
		int jj=0;
		for(int i=1;i<=n;i++)
		if(mp[{i,j}]=='#')jj=i,cnt++;
		if(cnt==1){
			R_i=jj;
			R_j=j;
			break;
		}
	}
	int dx[]={U_i,D_i,L_i,R_i};
	int dy[]={U_j,D_j,L_j,R_j};
	std::sort(dx,dx+4);
	std::sort(dy,dy+4);
	std::cout<<dx[1]<<" "<<dy[1]<<"\n";
	solve(T-1);
} 
signed main(){
	std::ios::sync_with_stdio(0);
	int T;
	std::cin>>T;
	solve(T); 
} 
```

---

## 作者：abc1856896 (赞：0)

# solution

简单题。

曼哈顿圆的中心一定是在所有出现井号的行的中间一行，所有出现井号的中间一列。

那么记录一下所有出现井号的行和列，然后取它们的中间行和中间列输出即可。

---

## 作者：int_stl (赞：0)

我们发现，曼哈顿圆就是一个菱形，那么我们找到这个圆的最上、最下、最左和最右部分的位置，分别设为 $a,b,c,d$，那么答案就是 $(a-1+\frac{1+b-a+1}{2},c-1+\frac{1+d-c+1}{2})=(\frac{a+b}{2},\frac{c+d}{2})$。

代码如下：

```cpp
int n, m;
int main() {
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        vector < vector <char> > mych;
        cin >> n >> m;
        mych.assign(n + 1, vector <char> (m + 1, 0));
        FORL(i, 1, n, 1) {
            FORL(j, 1, m, 1) {
                cin >> mych[i][j];
            }
        }
        int shang = 0, xia = 0, zuo = 0, you = 0;
        FORL(i, 1, n, 1) {
            bool ok = 0;
            FORL(j, 1, m, 1) {
                if (mych[i][j] == '#') {
                    ok = 1;
                    break;
                }
            }
            if (ok) {
                shang = i;
                break;
            }
        }
        FORR(i, n, 1, 1) {
            bool ok = 0;
            FORL(j, 1, m, 1) {
                if (mych[i][j] == '#') {
                    ok = 1;
                    break;
                }
            }
            if (ok) {
                xia = i;
                break;
            }
        }
        FORL(i, 1, m, 1) {
            bool ok = 0;
            FORL(j, 1, n, 1) {
                if (mych[j][i] == '#') {
                    ok = 1;
                    break;
                }
            }
            if (ok) {
                zuo = i;
                break;
            }
        }
        FORR(i, m, 1, 1) {
            bool ok = 0;
            FORL(j, 1, n, 1) {
                if (mych[j][i] == '#') {
                    ok = 1;
                    break;
                }
            }
            if (ok) {
                you = i;
                break;
            }
        }
        cout << (shang + xia) / 2 << " " << (zuo + you) / 2 << '\n';
    }
}
```

---

## 作者：ZnHF (赞：0)

# 题意简述

称一个点 $(a,b)$ 属于圆心为 $(c,d)$ 的曼哈顿圆，当且仅当 $|c-a|+|d-b|<r$。

给定一个 $n \times m$ 的网格和 $r$，网格上有一个完整的曼哈顿圆，属于该曼哈顿圆的点在网格上用 `#` 表示，不属于的用 `.` 表示。

求该曼哈顿圆的圆心的坐标。

# 题目分析

观察样例可以发现，一个曼哈顿圆在网格上可以被表示成一个菱形，这个菱形的两条对角线的交点即为答案。因为菱形的两条对角线互相垂直平分，所以只需要找到一条对角线的起始坐标和终止坐标就可以求出答案，答案即为这条对角线的中点的坐标。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<pair<int,int>,char> maze;
//由于数据范围只说明了n*m的范围而没有说明n和m的范围，所以使用map来存题目给定的网格
int T,n,m,maxx,temp,s,e,ansx,ansy;
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		maze.clear();
		maxx=-1;
		s=0;
		e=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				char t;
				cin>>t;
				maze[{i,j}]=t;
			}
		}
		for(int i=1;i<=n;i++){
			int now=0;
			for(int j=1;j<=m;j++){
				if(maze[{i,j}]=='#') now++;
			}
			if(now>maxx){
				maxx=now;//记录对角线的长度
				ansx=i;//记录对角线所在的横坐标
			}
		}
		for(int i=1;i<=m;i++){
			if(maze[{ansx,i}]=='#'){
				s=i;//计算对角线的起始坐标
				e=i+maxx-1;//计算对角线的终止坐标
				break;
			}
		}
		ansy=s+e>>1;
		cout<<ansx<<" "<<ansy<<endl;
	}
	return 0;
}

```

---

## 作者：Wind_love (赞：0)

## 解题思路
通过读题我们可以发现：  
曼哈顿圆的圆心一定在 $#$ 最多的那一行上，于是就可以先找出这一行作为圆心的横坐标。  
然后遍历这一行，找出 $#$ 的起始点与终止点，这两个点的中点作为圆心的纵坐标。  
接下来输出即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;  
int t;
int n,m;
string s[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>s[i];
		int maxn=0,h=0,i=0,j=0;
		for(int i=1;i<=n;i++){
			int temp=0;
			for(int j=0;j<s[i].size();j++){
				if(s[i][j]=='#')temp++;
			}
			if(temp>maxn)maxn=temp,h=i;
		}
		int be=-1,ed=-1;
		for(int i=0;i<s[h].size();i++){
			if(be==-1&&s[h][i]=='#'){
				be=i+1;
			}
			if(s[h][i]=='#')ed=i+1;
		}
		printf("%d %d\n",h,be+(ed-be)/2);
	}
    return 0;  
}

---

