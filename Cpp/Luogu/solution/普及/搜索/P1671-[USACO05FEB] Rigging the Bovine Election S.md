# [USACO05FEB] Rigging the Bovine Election S

## 题目描述

农场被划分为 $5\times 5$ 的格子，每个格子中都有一头奶牛，并且只有荷斯坦（标记为 `H`）和杰西（标记为 `J`）两个品种。如果一头奶牛在另一头上下左右四个格子中的任一格里，我们说它们相连。奶牛要大选了。现在杰西奶牛们想选择 $7$ 头相连的奶牛，划成一个竞选区，使得其中它们品种的奶牛比荷斯坦的多。

要求你编写一个程序求出方案总数。


## 样例 #1

### 输入

```
HHHHH
JHJHJ
HHHHH
HJHHJ
HHHHH```

### 输出

```
2```

# 题解

## 作者：MoonCake2011 (赞：9)

我们用 `dfs` 找连通块。

每次将选过的坐标进行扩散，所以我们要记录每次选过的坐标。

选了 $7$ 格后，将那 $7$ 个坐标的 `hash` 值存入数组里。

对那个数组去重。

最终那个数组里的非重复个数就是答案。

记得用 `vis` 数组标记。

竟然能在 150ms 内卡过，时间总和才不到 710ms。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int d[4][2]={{0,1},{-1,0},{0,-1},{1,0}};
bool vis[10][10];
char a[10][10];
bool check(int x,int y){
	return (x>0 && y>0 && x<=5 && y<=5);
}
vector<pair<int,int> >v;
struct node{
	pair<int,int>a[9];
	node(){
		for(int i=0;i<7;i++)
			a[i].first=a[i].second=0;
	}
	pair<int,int> &operator [] (int i){
		return a[i];
	}
	void Sort(){
		std::sort(a,a+7);
	}
	int get_hash(){
		int base=7,ans=0;
		for(int i=0;i<7;i++){
			ans=ans*base+a[i].first;
			ans=ans*base+a[i].second;
		}
		return ans;
	}
};
vector<int>ans;
void dfs(int x,int y,int cnt,int p){
	v.push_back({x,y});
	if(p==7){
		if(cnt>3){
			node x=node();
			for(int i=0;i<7;i++)
				x[i]=v[i];
			x.Sort();
			ans.push_back(x.get_hash());
		}
		v.pop_back();
		return;
	}
	vis[x][y]=1;
	for(int i=0;i<v.size();i++){
		int ux=v[i].first,uy=v[i].second;
		for(int j=0;j<4;j++){
			int tx=ux+d[j][0],ty=uy+d[j][1];
			if(!vis[tx][ty] && check(tx,ty))
				dfs(tx,ty,cnt+(a[tx][ty]=='J'),p+1);
		}
	}
	v.pop_back();
	vis[x][y]=0;
}
void read(){
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			cin>>a[i][j];
}
signed main() {
	read();
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			dfs(i,j,a[i][j]=='J',1);
	sort(ans.begin(),ans.end());
	int p=unique(ans.begin(),ans.end())-ans.begin();
	cout<<p;
	return 0;
}
```

---

## 作者：Adam0826 (赞：3)

一开始这道题我看了半天硬是没敢做，首先想到的是状压 DP，可是状压虽然二十五格应该能压得下，但是怎么判断连续？所以一时束手无策
直到看到了某位网上的神犇说——大力出奇迹！！！
然后我就按照那样子来了一发，结果居然能过！！！
实际上就是朴素暴力
## 题目大意
 $5 \times 5$ 的字符数组，选择 $7$ 个相连的字符，使其中 $J$ 的数目比 $H$ 多。
## 题目思路
枚举七个点。

如果 $J$ 的数目大于 $4$ 且有七个点


方案数就加一。

如果不是就继续枚举。

最后输出方案数。

### 下面是 AC 代码
```
#include<bits/stdc++.h>
using namespace std;
char str[7][7];
int ans,temp,c[8],d[8],flag[8];
int dir[4][2]={1,0,0,1,-1,0,0,-1};
void Jud(int p)
{
	int i,j,dx,dy;
	flag[p]=1,temp++;
	for(i=0;i<=3;i++)
	{
		dx=c[p]+dir[i][0];
		dy=d[p]+dir[i][1];
		for(j=1;j<=7;j++)
		{
			if(c[j]==dx&&d[j]==dy&&flag[j]==0)
				Jud(j);
		}
	}
}
void Sech(int x,int y)
{
	int i,sum;
	if(y==8)
	{
		temp=sum=0;
		memset(flag,0,sizeof(flag));
		for(i=1;i<=7;i++)
		{
			if(str[c[i]][d[i]]=='J')
				sum++;
		}
		Jud(1);
		if(sum>=4&&temp==7)
			ans++;
		return;
	}
	if(x>25)
		return;
	for(i=x;i<=25;i++)
	{
		c[y]=(i+4)/5;
		d[y]=i-((i+4)/5-1)*5;
		Sech(i+1,y+1);
	}
}
int main()
{
	int i;
	for(i=1;i<=5;i++)
		scanf("%s",str[i]+1);
	Sech(1,1);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：JOKER_chu (赞：3)

这题评绿一点不过分。

## 思路

枚举 $7$ 个点，然后检查是否相连，并且不在同一个格子上有多个点即可。

## 做法

$7$ 重循环，然后将选的格子记录在数组中，最后检查时要注意答案去重。并且请注意你的数组是否回溯。我使用了 `vector` 去重，并且 `pair` 储存坐标。

## 代码

```cpp
#include <iostream>

#include <cmath>

#include <algorithm>

#include <climits>

#include <vector> 

#include <map>

#define endl '\n'

using namespace std;

struct mep{
	int n;
};

const int hutao = 1e1, fx[6][4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

char a[hutao][hutao];
bool v[hutao][hutao];
int ans;
 
map< vector< pair<int, int> >, bool >vv;

int main(){
	for(int first = 1; first <= 5; ++first){
		for(int second = 1; second <= 5; ++second){
			cin >> a[first][second];
		}
	}
	for(int first = 1; first <= 5; ++first){
		for(int second = 1; second <= 5; ++second){
			v[first][second] = 1;
			for(int first1 = 1; first1 <= 5; ++first1){
				for(int second1 = 1; second1 <= 5; ++second1){
					if(v[first1][second1] == 1){
						continue;
					}
					v[first1][second1] = 1;
					bool flag = 0;
					for(int i = 0; i < 4; ++i){
						if(v[first1 + fx[i][0]][second1 + fx[i][1]] == 1){
							flag = 1;
							break;
						}
					}
					if(flag == 0){
						v[first1][second1] = 0;
						continue;
					}
					for(int first2 = 1; first2 <= 5; ++first2){
						for(int second2 = 1; second2 <= 5; ++second2){
							if(v[first2][second2] == 1){
								continue;
							}
							v[first2][second2] = 1;
							bool flag = 0;
							for(int i = 0; i < 4; ++i){
								if(v[first2 + fx[i][0]][second2 + fx[i][1]] == 1){
									flag = 1;
									break;
								}
							}
							if(flag == 0){
								v[first2][second2] = 0;
								continue;
							}
							for(int first3 = 1; first3 <= 5; ++first3){
								for(int second3 = 1; second3 <= 5; ++second3){
									if(v[first3][second3]){
										continue;
									}
									v[first3][second3] = 1;
									bool flag = 0;
									for(int i = 0; i < 4; ++i){
										if(v[first3 + fx[i][0]][second3 + fx[i][1]] == 1){
											flag = 1;
											break;
										}
									}
									if(flag == 0){
										v[first3][second3] = 0;
										continue;
									}
									for(int first4 = 1; first4 <= 5; ++first4){
										for(int second4 = 1; second4 <= 5; ++second4){
											if(v[first4][second4]){
												continue;
											}
											v[first4][second4] = 1;
											bool flag = 0;
											for(int i = 0; i < 4; ++i){
												if(v[first4 + fx[i][0]][second4 + fx[i][1]] == 1){
													flag = 1;
													break;
												}
											}
											if(flag == 0){
												v[first4][second4] = 0;
												continue;
											}
											for(int first5 = 1; first5 <= 5; ++first5){
												for(int second5 = 1; second5 <= 5; ++second5){
													if(v[first5][second5]){
														continue;
													}
													v[first5][second5] = 1;
													bool flag = 0;
													for(int i = 0; i < 4; ++i){
														if(v[first5 + fx[i][0]][second5 + fx[i][1]] == 1){
															flag = 1;
															break;
														}
													}
													if(flag == 0){
														v[first5][second5] = 0;
														continue;
													}
													for(int first6 = 1; first6 <= 5; ++first6){
														for(int second6 = 1; second6 <= 5; ++second6){
															if(v[first6][second6]){
																continue;
															}
															v[first6][second6] = 1;
															bool flag = 0;
															for(int i = 0; i < 4; ++i){
																if(v[first6 + fx[i][0]][second6 + fx[i][1]] == 1){
																	flag = 1;
																	break;
																}
															}
															if(flag == 0){
																v[first6][second6] = 0;
																continue;
															} 
															vector< pair<int, int> >sum;
															int res = a[first][second] == 'J';
															res += a[first1][second1] == 'J';
															res += a[first2][second2] == 'J';
															res += a[first3][second3] == 'J';
															res += a[first4][second4] == 'J';
															res += a[first5][second5] == 'J';
															res += a[first6][second6] == 'J';
															pair<int, int>u(first, second);
															sum.push_back(u);
															pair<int, int>d(first1, second1);
															sum.push_back(d);
															pair<int, int>c(first2, second2);
															sum.push_back(c);
															pair<int, int>x(first3, second3);
															sum.push_back(x);
															pair<int, int>z(first4, second4);
															sum.push_back(z);
															pair<int, int>s(first5, second5);
															sum.push_back(s);
															pair<int, int>w(first6, second6);
															sum.push_back(w);
															sort(sum.begin(), sum.end());
															if(res > 3 && vv[sum] == 0){
																ans++;
															}
															vv[sum] = 1;
															v[first6][second6] = 0;
														}
													}
													v[first5][second5] = 0;
												}
											}
											v[first4][second4] = 0;
										}
									}
									v[first3][second3] = 0;
								}
							}
							v[first2][second2] = 0;
						}
					}
					v[first1][second1] = 0;
				}
			}
			v[first][second] = 0;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：xiaoli12345678 (赞：2)

# 题意简述

给定一个 $5\times5$ 的字符数组，且只由 $\texttt{J}$ 和 $\texttt{H}$ 组成，要寻找 $7$ 个联通的字符，使 $\texttt{J}$ 比 $\texttt{H}$ 多，并输出方案总数。

# 题目分析

由于数据只有 $5\times 5$ 并且选 $7$ ，而且时间限制是 $5\text{s}$ ，所以选择暴力。

可以用 `dfs` 找连通块。

每次从选过的坐标进行扩散，记录每次选过的坐标。

选了 $7$ 个后，对坐标排序，对比方案是不是记录过了。

如果没记录过，则方案数加一，并记录下来。

# 代码流程

- 读入字符数组。

- 遍历数组，开始搜索。

- 从前 $k-1$ 点扩散。

- 选完 $7$ 个点，判断 $\texttt{J}$ 是否比 $\texttt{H}$ 多。

- 把选中的坐标排序，遍历判重数组，如果没与记录过，则方案数加一，并记录。

- 输出答案。

# 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
char map[5][5];
int v[5][5],ans;
int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};//方向数组

struct point {
	int x,y;
} b[8],v_ans[100001][8],c[8];
bool cmp(point x,point y) {
	if(x.x==y.x) {
		return x.y<y.y;
	} else {
		return x.x<y.x;
	}
}
void dfs(int k,int x,int y) {
	//k表示选到第k个点，x表示J的数量，y表示H的数量
	if(k>7) {
		if(x>y) {
			for(int i=1; i<=7; i++) {
				c[i]=b[i];
			}
			sort(c+1,c+1+7,cmp);
			int i=0;
			for(i=1; i<=ans; i++) {
				int j=0;
				for(j=1; j<=7; j++) {
					if(c[j].x!=v_ans[i][j].x || c[j].y!=v_ans[i][j].y) {//坐标不同则跳出
						break;
					}
				}
				if(j>7) {//当j=8时，证明每一个坐标都相同，所以跳出。
					break;
				}
			}
			if(i>ans) {//当i>ans时，证明所选点没记录过。
				ans++;
				for(i=1; i<=7; i++) {
					v_ans[ans][i]=c[i];
				}
			}
		}
		return;
	}
	for(int i=1; i<k; i++) {//从前k+1个点搜索
		for(int j=0; j<4; j++) {//扩散
			int xx=b[i].x+dir[j][0];
			int yy=b[i].y+dir[j][1];
			if(xx>=0 && xx<5 && yy>=0 && yy<5 && !v[xx][yy]) {
				b[k].x=xx;
				b[k].y=yy;
				v[xx][yy]=1;
				if(map[xx][yy]=='J') {
					dfs(k+1,x+1,y);
				} else {
					dfs(k+1,x,y+1);
				}
				v[xx][yy]=0;
			}
		}
	}
}
int main() {
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			cin>>map[i][j];
		}
	}
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			b[1].x=i;//标记第一个点
			b[1].y=j;
			v[i][j]=1;
			if(map[i][j]=='J') {//搜索
				dfs(2,1,0);
			} else {
				dfs(2,0,1);
			}
			v[i][j]=0;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：KXY_Moon (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P1671)


## 概括式题意：

一个矩阵中有个 $5^2$ 格子，每个格子都有一头牛（II 或 J），选出 $7$ 个连通（上，下，左，右）格子，让这 $7$ 个格子中杰西奶牛比荷斯坦奶牛多，求有多少种筛选方案。

## 解法：

看到题目时间限制有 $5$ 秒了吗？

**暴力 dfs 即可通过本题**

对于每一个格子 $A_{i,j}$，搜索其四个方向，同时将 $A_{i-1,j}$, $A_{i+1,j}$, $A_{i,j-1}$, $A_{i,j+1}$ 标记。

这样，筛出 $7$ 个格子后，判断：
    
```cpp

//以下为判断伪代码
for(int i=1;i<=7;i++)
    if(K[i]=='J') Jcnt++;

Hcnt=7-Jcnt;
if(Hcnt>Jcnt) return False;
else return Ture;

```


## 代码：

```cpp
//不可抄袭！
#include <bits/stdc++.h>
#define int long long
const int r=7;
const int f[4][2]={1,0,0,1,-1,0,0,-1};
using namespace std;
char A[r+1][r+1];
int ans,t,c[r+1],d[r+1],flag[r+1];
void dfs_one(int k){int dx,dy;
	flag[k]=1,t++;
	for(int i=0;i<=3;i++){
		dx=c[k]+f[i][0];
		dy=d[k]+f[i][1];
		for(int j=1;j<=r;j++)
			if(c[j]==dx&&d[j]==dy&&!flag[j]) dfs_one(j);
	}
}
void dfs_two(int x,int y){
	if(y==r+1){
		int sum=0; t=0;
		memset(flag,0,sizeof(flag));
		for(int i=1;i<=r;i++){
			if(A[c[i]][d[i]]=='J') sum++;
		}
		dfs_one(1);
		if(sum>=4&&t==r) ans++;
		return;
	}
	if(x>25)return;
	for(int i=x;i<=25;i++){
		c[y]=(i+4)/5;
		d[y]=i-((i+4)/5-1)*5;
		dfs_two(i+1,y+1);
	}
}
signed main(){
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			cin>>A[i][j];
	dfs_two(1,1);
	cout<<ans;
	return 0;
}
```
[提交记录](https://www.luogu.com.cn/record/182241702)    

End.

---

## 作者：hgzxHZR (赞：2)

第一篇题解，题目不难。~~不过还是调了很久~~

## 题目大意
给定一个 $5\times5$ 的由 **J** 和 **H** 组成的地图，要求寻找 7 个联通的字符，使其中 **J** 的数目比 **H** 多（即 **H** 的数目 $\le3$）。

## 做法
由于数据只有 5，所以直接暴力枚举 7 个点，判断是否符合题意（相连且不重复）。但是要注意，不能太过硬核，否则会超时（见代码第 28 行注释）。

做的时候答案要去重，可以考虑 map，我这里选择将坐标转换为字符串，当然 map 的关键字也可以用 pair 嵌套，~~但是代码很不具有美感（个人认为）~~。也可以用 unique 函数，第一篇题解就是这样的。

详见代码注释

~~~cpp
#include<iostream>
#include<algorithm>
#include<map>

//精简代码 
#define for1(i,r,n) for(i=r;i<=n;i++)
using namespace std;

struct tPoint
{
    int x,y;
    tPoint(int x=0,int y=0) : x(x),y() {}//似乎这里必须初始化一下，但不知道为什么
    bool operator <(const tPoint &B)//重载小于号，排序用，或者直接写一个cmp 
    {
        if(x!=B.x) return x<B.x;
        else return y<B.y;
    }
}a[8],b[8];//每个点的横纵坐标 
char s[6][6];
int ans=0,i,j;
map<string ,bool > M;//见panduan2()

bool panduan1(int x);//判断选择的点是否相邻
bool panduan2();//判断选择的点是否满足条件 (J>H，不重复选择)

void Search()
{
    /*枚举每个点，必须在每次循环前判定是否合法，不然5^14*c次绝对会TLE,c是每次循环后进行的运算次数，为常数
    为了美观，没加缩进*/
    for1(a[1].x,1,5) for1(a[1].y,1,5)
    for1(a[2].x,1,5) for1(a[2].y,1,5) if(panduan1(2)) continue;//相邻和重复，有一个就不行 
    else for1(a[3].x,1,5) for1(a[3].y,1,5) if(panduan1(3)) continue;
    else for1(a[4].x,1,5) for1(a[4].y,1,5) if(panduan1(4)) continue;
    else for1(a[5].x,1,5) for1(a[5].y,1,5) if(panduan1(5)) continue;
    else for1(a[6].x,1,5) for1(a[6].y,1,5) if(panduan1(6)) continue;
    else for1(a[7].x,1,5) for1(a[7].y,1,5) if(panduan1(7)) continue;
    else
    {
        for1(i,1,7) b[i].x=a[i].x,b[i].y=a[i].y;
        sort(b+1,b+1+7);//排序，按点的坐标降序，便于判重
        if(panduan2()) ans++;       
    }
    return ;
}

int main()
{
    for1(i,1,5) for1(j,1,5) cin>>s[i][j];//输入 

    Search();//主体 

    cout<<ans<<endl;//输出 

    return 0;
}

bool panduan1(int x)
{
    //判重，就是判断当前点是否与之前的的横纵坐标相同，只要有一个相同就不行
    for1(i,1,x-1) if(a[x].x==a[i].x&&a[i].y==a[x].y) return true;
    //判联通,如果 1,2,3,4,5,6 联通，7只需与任意一个相连
    bool key1=false;
    for1(i,1,x-1) if(abs(a[i].x-a[x].x)+abs(a[i].y-a[x].y)==1){key1=true;break;}
    if(key1==false) return true;
    else return false;
}
bool panduan2()
{
    //将7*2=14个数变换成字符串，再判重 
    char tmp[20]="";int _t=0;
    for1(i,1,7) tmp[_t++]=b[i].x+'0',tmp[_t++]=b[i].y+'0';//注意，字符数组第0个不要为‘\0’
    if(M[tmp]) return false;//标记过，不合法，进行下一轮循环 
    M[tmp]=true;
    //如果H小于J，ans加1
    int H=0;
    for1(i,1,7) if(s[b[i].x][b[i].y]=='H') H++;
    if(H<=3) return true;
    return false;
}
~~~

---

## 作者：Po7ed (赞：2)

**[题目传送门](https://www.luogu.com.cn/problem/P1671)**

 _前排提醒：做法硬核。_ 

### 题目大意
$5\times 5$ 的字符数组，选择 $7$ 个相连的字符，使 $\texttt{J}$ 比 $\texttt{H}$ 多，并输出方案总数。
### 解法
暴力搜！
#### 思路
首先关注数据范围：$5\times 5$ 选 $7$，再看时空限制：$5\text{s},256\text{MB}$。

一看就不正常，果断选择暴力。
#### 算法流程
- 枚举 $7$ 个坐标，使得它们**互不相同**且**相连**。
- 统计 $\texttt{J}$ 与 $\texttt{H}$ 的个数。
  - 如果 $\texttt{J}$ 比 $\texttt{H}$ 多，判重并标记，方案总数加 $1$。
  - 否则重新枚举。
- 反复枚举坐标。

#### 代码
[见云剪贴板（附提交记录）](https://www.luogu.com.cn/paste/en3pe8rg)

---

## 作者：dulinfan2023 (赞：1)

## 题意：

有 $5 \times 5$ 个格子，每格都有一头牛，请你选出 $7$ 个格子，让杰西奶牛(`J`)比荷斯坦奶牛(`H`)多。

## 思路：

一看见 5.00s 的时间限制就能想到 **暴力**！

暴力过程：

- 枚举要选的 $7$ 个格子并存储下坐标。

- 在选完 $7$ 个格子后，判断 `J` 是否比 `H` 多。 

AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char str[7][7];
int ans,temp,c[8],d[8],flag[8];
const int dir[4][2]={1,0,0,1,-1,0,0,-1};
void aj(int p){
	int i,j,dx,dy;
	flag[p]=1,temp++;
	for(i=0;i<=3;i++){
		dx=c[p]+dir[i][0];
		dy=d[p]+dir[i][1];
		for(j=1;j<=7;j++){
			if(c[j]==dx&&d[j]==dy&&flag[j]==0)aj(j);
		}
	}
}
void Search(int x,int y){
	int i,sum;
	if(y==8){
		temp=sum=0;
		memset(flag,0,sizeof(flag));
		for(i=1;i<=7;i++){
			if(str[c[i]][d[i]]=='J')
				sum++;
		}
		aj(1);
		if(sum>=4&&temp==7)
			ans++;
		return;
	}
	if(x>25)return;
	for(i=x;i<=25;i++){
		c[y]=(i+4)/5;
		d[y]=i-((i+4)/5-1)*5;
		Search(i+1,y+1);
	}
}
signed main(){
	for(int i=1;i<=5;i++)for(int j=1;j<=5;j++)cin>>str[i][j];
	Search(1,1);
	cout<<ans;
	return 0;
}
```

---

## 作者：ZY_king_YB (赞：0)

[P1671 [USACO05FEB] Rigging the Bovine Election S 题目](https://www.luogu.com.cn/problem/P1671)

# 1.题意抽象化

有一个 $5\times5$ 的矩阵，每个格子都有一头牛（`I`牛或`J`牛），选出 $7$ 个**连通**（即上下左右其中一个方向相连）的格子，让这 $7$ 个格子中 `J`牛比`H`牛多，求有多少种选择方案。

# 2.思路

瞪眼法！！！

瞪了半天愣是瞪不出，首先想到状压`DP`，可是状压虽然 $25$ 格应该不会超，但是我不会判断连续，所以我一时束手无策。

忽然看到时间限制，高达 $5$ 秒，这还`DP`个球啊，直接暴力。

~~想起了当年疯狂缩时间的日子，TLE你也有今天啊哈哈哈~~

对于每一个格子 $A_{i,j}$，搜索其四个方向，同时将 $A_{i-1,j}$（上）, $A_{i+1,j}$（下）, $A_{i,j-1}$（左）, $A_{i,j+1}$（右）标记。

这样，选出 $7$ 个格子后，判断：
```cpp
//判断伪代码
for(int i=1;i<=7;i++)
    if(m[i]=='J') J++;
H=7-J;
if(H>J) return false;
else return ture;
```
代码：
```cpp
//P1671
#include <bits/stdc++.h>
#define ll long long
#define r 7 //常量定义
#define ZY return 
#define king 0
#define YB ;
using namespace std;
const ll F[4][2]={1,0,0,1,-1,0,0,-1};//打表
char a[r+1][r+1];//数组储存矩阵
ll sum,t,c[r+1],d[r+1];
bool flag[r+1];
void dfs1(ll k){
	ll dx,dy;
	flag[k]=true;
	t++;
	for(int i=0;i<=3;i++){
		dx=c[k]+F[i][0],dy=d[k]+F[i][1];
		for(int j=1;j<=r;j++)
			if(c[j]==dx&&d[j]==dy&&flag[j]==false)
				dfs1(j);//递归
	}
}
void dfs2(ll x,ll y){
	if(y==r+1){
		ll sum=0; 
		t=0;
		memset(flag,false,sizeof(flag));
		//初始化
		for(int i=1;i<=r;i++)
			if(a[c[i]][d[i]]=='J') 
				sum++;//累加J牛个数
		dfs1(1);//dfs
		if(sum>=4&&t==r)//判断J牛是否比H牛多
			sum++;//累加
		return;
	}
	if(x>25)
		return;
	for(int i=x;i<=25;i++){
		c[y]=(i+4)/5;
		d[y]=i-((i+4)/5-1)*5;
		dfs2(i+1,y+1);//递归
	}
}
void io_off(){ios::sync_with_stdio(0);cin.tie(0);}/*
关闭流同步，使cin,cout的速度与scanf,printf相当
关流后，不能再使用scanf和printf，否则可能引起程序异常
*/int main(){
	io_off();
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++)
			cin>>a[i][j];//输入矩阵
	dfs2(1,1);//开始dfs
	cout<<sum;
	ZY king YB
}

---

## 作者：lovely_codecat (赞：0)

不难想到深搜连通块。

然而这道题的难点在于判重。

考虑用一个向量存储连通块坐标然后判重。

如果暴力判重，复杂度是 $O(T)$ ( $T=$ 方案数）的。

看起来不大，但是由于这道题的题面中全是常数，所以这道题还要乘上一个 $7^3\times 5^4$ 的常数。

这个常数的具体计算方法：枚举每个点进行扩展 $7^2$，暴力判重常数 $7^1$, 深搜扩展 $5^2$, 枚举起点 $5^2$。

计算后发现过不了。

我们可以将一个坐标压缩成一个数，具体方法：将 $(x,y)$ 压缩成 $(x-1)\times 5+y$。

然后对压缩后的数组进行哈希即可。

由于这题需要维护连通块的具体信息，所以不能使用传统的方法深搜连通块，需要枚举目前向量中的数进行扩展。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char s[6][6];
int cnt,fl,dx[]={0,1,0,-1},dy[]={1,0,-1,0},vis[6][6];
vector<pair<int,int> >ss;
unordered_map<int,int>mp;
inline void chk(vector<pair<int,int> > tt){
	sort(tt.begin(),tt.end());
	int sum=0;
	for(int i=0;i<7;i++)sum*=27,sum+=(tt[i].first-1)*5+tt[i].second;
	if(mp[sum])return;
	cnt++;
	mp[sum]=1;
	return;
}
void dfs(int k,int j){
	if(k>7){
		if(j>3)chk(ss);
		return;
	}
	if(j+(7-k)<3)return;
	for(int h=0;h<k-1;h++){
		for(int i=0;i<4;i++){
			int nx=ss[h].first+dx[i],ny=ss[h].second+dy[i];
			if(!vis[nx][ny]&&nx>0&&nx<6&&ny>0&&ny<6){
				vis[nx][ny]=1;
				ss.push_back({nx,ny});
				dfs(k+1,j+(s[nx][ny]=='J'));
				ss.pop_back();
				vis[nx][ny]=0;
			}
		}
	}
}
main(){
	for(int i=1;i<=5;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=5;i++){
		for(int j=1;j<=5;j++){
			vis[i][j]=1;
			ss.push_back({i,j});
			dfs(2,(s[i][j]=='J'));
			ss.pop_back();
			vis[i][j]=0;
		}
	}
	cout<<cnt;
}
```

---

## 作者：hgzxczw (赞：0)

## 大意

给定一个 $5\times5$ 的由 $\texttt{J}$ 和 $\texttt{H}$ 组成的地图，要求寻找 $7$ 个联通的字符，使其中 $\texttt{J}$ 的数目比 $\texttt{H}$ 多（也就是说 $\texttt{H}$ 的数目 $\le3$）。

## 做法
暴力枚举 $7$ 个点，判断其是否合法，这样总次数是 $25^7$，太大了，需要剪枝处理。

答案去重时，将坐标转换为字符串用 map 处理。

## code

~~~cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define rep(i,  l,  r) for(i = l; i <= r; i++)

struct Point {
    int x, y;
    bool operator < (Point B) const {return x == B.x ? y < B.y : x < B.x;}
}a[8], b[8];
char s[6][6];
int ans=0, i, j;

bool check1(int x) { //判断选择的点是否相邻
    rep(i, 1, x - 1) if(a[x].x == a[i].x && a[i].y == a[x].y) return 1;
    bool k = 0;
    rep(i, 1, x - 1)
        if(abs(a[i].x - a[x].x) + abs(a[i].y - a[x].y) == 1) {
            k = 1;
            break;
        }
    return !k;
}
map<string , bool > M;
bool check2() { //判断J>H，判重
    string str;
    int H = 0;
    rep(i, 1, 7) {
        str.push_back(b[i].x + '0'), str.push_back(b[i].y + '0');
        if(s[b[i].x][b[i].y]=='H') H++;
    }
    if(M[str]) return 0; M[str] = 1;
    return H <= 3;
}

signed main() {
    rep(i, 1, 5) rep(j, 1, 5) cin>>s[i][j];//输入

    rep(a[1].x, 1, 5) rep(a[1].y, 1, 5)
        rep(a[2].x, 1, 5) rep(a[2].y, 1, 5) if(!check1(2))
            rep(a[3].x, 1, 5) rep(a[3].y, 1, 5) if(!check1(3))
                rep(a[4].x, 1, 5) rep(a[4].y, 1, 5) if(!check1(4))
                    rep(a[5].x, 1, 5) rep(a[5].y, 1, 5) if(!check1(5))
                        rep(a[6].x, 1, 5) rep(a[6].y, 1, 5) if(!check1(6))
                            rep(a[7].x, 1, 5) rep(a[7].y, 1, 5) if(!check1(7)) {
                                rep(i, 1, 7) b[i].x=a[i].x, b[i].y=a[i].y;
                                sort(b + 1, b + 1 + 7);//排序，便于判重
                                if(check2()) ans++;
                            }

    cout << ans;

    return 0;
}
~~~

---

