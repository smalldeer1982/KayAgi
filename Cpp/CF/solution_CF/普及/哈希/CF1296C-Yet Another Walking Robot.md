# Yet Another Walking Robot

## 题目描述

There is a robot on a coordinate plane. Initially, the robot is located at the point $ (0, 0) $ . Its path is described as a string $ s $ of length $ n $ consisting of characters 'L', 'R', 'U', 'D'.

Each of these characters corresponds to some move:

- 'L' (left): means that the robot moves from the point $ (x, y) $ to the point $ (x - 1, y) $ ;
- 'R' (right): means that the robot moves from the point $ (x, y) $ to the point $ (x + 1, y) $ ;
- 'U' (up): means that the robot moves from the point $ (x, y) $ to the point $ (x, y + 1) $ ;
- 'D' (down): means that the robot moves from the point $ (x, y) $ to the point $ (x, y - 1) $ .

The company that created this robot asked you to optimize the path of the robot somehow. To do this, you can remove any non-empty substring of the path. But this company doesn't want their customers to notice the change in the robot behavior. It means that if before the optimization the robot ended its path at the point $ (x_e, y_e) $ , then after optimization (i.e. removing some single substring from $ s $ ) the robot also ends its path at the point $ (x_e, y_e) $ .

This optimization is a low-budget project so you need to remove the shortest possible non-empty substring to optimize the robot's path such that the endpoint of his path doesn't change. It is possible that you can't optimize the path. Also, it is possible that after the optimization the target path is an empty string (i.e. deleted substring is the whole string $ s $ ).

Recall that the substring of $ s $ is such string that can be obtained from $ s $ by removing some amount of characters (possibly, zero) from the prefix and some amount of characters (possibly, zero) from the suffix. For example, the substrings of "LURLLR" are "LU", "LR", "LURLLR", "URL", but not "RR" and "UL".

You have to answer $ t $ independent test cases.

## 样例 #1

### 输入

```
4
4
LRUD
4
LURD
5
RRUDU
5
LLDDR```

### 输出

```
1 2
1 4
3 4
-1```

# 题解

## 作者：123456zmy (赞：6)

~~STL大法好~~

用 $map$ 标记走到过的点的步数，如果走到之前的点就更新答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,y,ansl,ansr;
string s;
map<long long,int> vis;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		cin>>s;
		x=0,y=0,ansl=0,ansr=0x3f3f3f3f;
		vis.clear();
		for(int i=0;i<n;i++)
		{
			if(vis[(x*100000000)+y])
			{
				if(i-vis[(x*100000000)+y]<ansr-ansl)
				{
					ansr=i;
					ansl=vis[(x*100000000)+y];
				}
			}
			vis[(x*100000000)+y]=i+1;
			if(s[i]=='U')++y;
			if(s[i]=='D')--y;
			if(s[i]=='R')++x;
			if(s[i]=='L')--x;
		}
		if(vis[(x*100000000)+y])
		{
			if(n-vis[(x*100000000)+y]<ansr-ansl)
			{
				ansr=n;
				ansl=vis[(x*100000000)+y];
			}
		}
		if(ansl&&ansr!=0x3f3f3f3f)printf("%d %d\n",ansl,ansr);
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：3)

题目：[Link](https://www.luogu.com.cn/problem/CF1296C)

一道较简单的思维题，实现过程很简单，主要是怎样想到做法

对于此题，只能用减少走动操作的方式来优化路线，并不能用短路经替换长路径。这样，就只剩下了一个优化方法，消环

对于每一步访问的坐标，我们就在 $vis$ 数组中标记上访问的时间。当走到一个已被访问过的坐标 $(x,y)$ 时，我们就找到了一个环。而要想消掉这个环所要删除的操作就是区间 $[vis_{(x,y)}+1,i]$ 内的所有操作，最后更新答案即可  
由于要求的是最小环，$vis$ 数组储存的应该是每个坐标上一次（最近一次）被访问的时间

```cpp
#include<cstdio>
#include<iostream>
#include<map>
using namespace std;
const int Maxn=200000+10,inf=0x3f3f3f3f;
int n,l,r;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
inline void move(char opt,int &x,int &y)
{
	if(opt=='L')--x;
	if(opt=='R')++x;
	if(opt=='U')++y;
	if(opt=='D')--y;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int T=read();
	while(T--)
	{
		n=read();
		int ans=inf;
		char s[Maxn];
		map <pair<int,int>,int> vis;
		
		vis[make_pair(0,0)]=0; // 刚开始在原点
		int x=0,y=0;
		scanf("%s",s+1);
		for(int i=1;i<=n;++i)
		{
			move(s[i],x,y);
			pair <int,int> cur=make_pair(x,y);			
			if(vis[cur] || !x && !y) // 该点已被访问过得情况
			{
				if(i-vis[cur]<ans) // 更新答案
				{
					ans=i-vis[cur];
					l=vis[cur]+1,r=i;
				}
			}
			vis[cur]=i;
		}
		if(ans==inf)puts("-1");
		else printf("%d %d\n",l,r);
	}
	return 0;
}
```

---

## 作者：Aehnuwx (赞：1)

如果从第 $l$ 步到第 $r$ 步绕了一个圈，那么就可以被删去。

考虑使用 `std::map` 维护每一个点最早什么时候被到达即可。

具体细节可以看代码注释。

代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

int mv[200][2];

void solve(){
	map<pair<int,int>,int>mp;//每一个坐标映射一个时间点
	mp[make_pair(0,0)]=1;
	int n;cin>>n;
	n++;
	string s;cin>>s;
	s="  "+s;
	//将n++，因为这样的话就能用mp[...]=0表示“某点仍未被访问”的情况了
	int x=0,y=0,len=INT_MAX;
	pair<int,int> ans;
	for(int i=2;i<=n;i++){
		x+=mv[s[i]][0];y+=mv[s[i]][1];
		int &z=mp[make_pair(x,y)];//前面加上 &，方便下面处理
		if(z){
			if(i-z<len){
				len=i-z;ans=make_pair(z+1,i);
				//更新答案
			}
		}
		z=i;//无论该点是否被访问，都需要执行，因为答案需要最小化
	}
	if(len==INT_MAX)cout<<-1<<'\n';
	else cout<<ans.first-1<<' '<<ans.second-1<<'\n';//因为上面n++了，所以答案区间也需要减一
}

int main(){
	int t;cin>>t;
	mv['L'][0]=-1;mv['L'][1]=0;
	mv['R'][0]=1;mv['R'][1]=0;
	mv['U'][0]=0;mv['U'][1]=1;
	mv['D'][0]=0;mv['D'][1]=-1;
	//mv: move, 记录移动方法
	while(t--)solve();
  return 0;
}
```

---

## 作者：rrrrr (赞：1)

~~排序多好啊~~   
在x,y方向做一遍前缀和（$L,U=1\quad R,D=-1$），发现当两数前缀和均相等时，两数之间恰有相同数目$(L,R)(U,D)$,所以排序，当相等时比较id，取id差最小值。
时间($n\log n$)
```
#include<bits/stdc++.h>
using namespace std;
int t,n;char a[200005];
struct abc 
{
	int x,y,id;
}u[200005];
bool cmt(abc a,abc b)
{
	if(a.x==b.x)
	{
		if(a.y==b.y)
		{
			return a.id<b.id; 
		}
		return a.y<b.y; 
	}
	return a.x<b.x;
}
int main()
{
	cin>>t;
	for(int ii=1;ii<=t;ii++)
	{
		int ans=0x3f3f3f3f;
		int rx,ry;
		cin>>n;
		cin>>a+1;
		u[0].id=0;
		u[0].x=u[0].y=0;
		for(int i=1;i<=n;i++)
		{
			u[i].x=u[i-1].x;u[i].y=u[i-1].y;
			if(a[i]=='L')u[i].x=u[i-1].x+1;
			if(a[i]=='R')u[i].x=u[i-1].x-1;
			if(a[i]=='U')u[i].y=u[i-1].y+1;
			if(a[i]=='D')u[i].y=u[i-1].y-1;
			u[i].id=i;
		}
		sort(u,u+n+1,cmt);
		for(int i=0;i<n;i++)
		{
			if(u[i].x==u[i+1].x&&u[i].y==u[i+1].y)
			if(u[i+1].id-u[i].id+1<ans)
			{
				ans=u[i+1].id-u[i].id+1;
				rx=u[i].id+1;
				ry=u[i+1].id;
			}
		}
		if(ans<0x3f3f3f3f)
		cout<<rx<<" "<<ry<<"\n";
		else
		cout<<"-1"<<"\n";
	}
}
```

---

## 作者：lyzhsxx (赞：0)

### 思路
这题我们可以用 map 做，```map<int,map<int,int> mp;``` 用法类似二维数组，还可以节省不少内存。只要我们模拟一下机器人的路线，然后看一下有没有走过这个点，如果有就去看一下要不要更新答案，最后输出，这样的时间复杂度就只有 $O(tn)$ ，其中 $t$ 是有多少个样例， $n$ 是字符串 $S$ 的长度。
这个东西开在全局不清空会 WA 的，这时你要清空 map 里的所有东西，当然你写在局部就不用考虑这个问题。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
void f(){
	map<int,map<int,int>> mp;//局部不用清空
	int n;
	cin>>n;
	string s;
	cin>>s;
	mp[0][0]=1;
	int x=0,y=0,l,r,ans=INT_MAX;
	for(int i=0;s[i];i++){
		if(s[i]=='L') x--;
		else if(s[i]=='R') x++;
		else if(s[i]=='U') y--;
		else y++; //x y 现在下标
	    if(mp[x][y]!=0){//去过了
	    	if(ans>i-mp[x][y]+1){
	    		ans=i-mp[x][y]+1;
	    		l=mp[x][y];
	    		r=i+1;
			}//谁大谁小
		}	
		mp[x][y]=i+2;//如果重复则l为i+1+1=i+2
	}
	if(ans==INT_MAX) cout<<-1<<endl;//无解
	else cout<<l<<" "<<r<<endl;
}//核心部分
int main(){
	int n;
	cin>>n;
	while(n--){
		f();
	}
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 要删去一部分，就要保证这部分走之前的位置和走之后的位置相同。
- 定义方位，用**类似前缀的形式**加起来得到每个坐标的准确值。
- 两个坐标用 map 做起来很方便，所以可以每轮循环结束时进行 $mp_{i,j}=i$ 代表走到 $(i,j)$ 是在**第几轮**，若发现**走过这个位置**时，用 $i-mp_{i,j}$ 求出**可以删去的长度**，用 $ans$ 进行比较即可。

### 代码：
```
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
#define ll long long
#define endl '\n'
int T,n;
char a[N];
map<char, int> dx;
map<char, int> dy;
int sx[N], sy[N];
map<pair<int, int> , int> lst;

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	dx['L'] = -1, dy['L'] = 0;
	dx['R'] = 1, dy['R'] = 0;
	dx['D'] = 0, dy['D'] = -1;
	dx['U'] = 0, dy['U'] = 1;
	cin >> T;
	while(T --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			cin >> a[i];
			sx[i] = sx[i - 1] + dx[a[i]];
			sy[i] = sy[i - 1] + dy[a[i]];
		}
		lst.clear();
		lst[{0, 0}] = 1;
		int ans = n + 1, lp, rp;
		for (int i = 1; i <= n; i ++) {
			int l = lst[{sx[i], sy[i]}];
//			cout << l << endl;
			lst[{sx[i], sy[i]}] = i + 1;
			if(l == 0) continue;
			if(i - l + 1 < ans) {
				ans = i - l + 1;
				lp = l, rp = i;
			}
		}
		if(ans == n + 1) cout << "-1" << endl;
		else cout << lp << ' ' << rp << endl;
	}
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
这道题就是删除走过的重复点步数的最小步数，用 map 维护坐标被记录过的位置，第二次跑到这个点就是走了一个圈，就更新答案。

### code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
string s;
map<pair<int,int>,int> mp;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>s;
		mp.clear();//多测不清空，亲人两行泪
		int z=0,f=0,ans=INT_MAX,ll=0,rr=0;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='L') z++;
			if(s[i]=='R') z--;
			if(s[i]=='U') f++;
			if(s[i]=='D') f--;
			if((mp[make_pair(z,f)]!=0||(z==0&&f==0))&&ans>i-mp[make_pair(z,f)])
			{
//				cout<<z<<" "<<f<<" "<<mp[make_pair(z,f)]<<" "<<ans<<"\n";
				ll=mp[make_pair(z,f)]+1;
				rr=i+1;
				ans=i-mp[make_pair(z,f)];
				
			}
			mp[make_pair(z,f)]=i+1;
		}
		if(ans!=INT_MAX) cout<<ll<<" "<<rr<<"\n";
		else cout<<"-1\n";
	}
	return 0;
}


```

---

## 作者：LZYAC (赞：0)

## 思路
其实就是找在一区间里走了一圈（起点和终点相同）的最小长度。考虑用标记数组维护某坐标在多久被跑过。但数据不能使用数组，于是只好用 $map$ 维护，再次走过时更新即可。

注意多测要清空。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,ans=INT_MAX,x,y,l,r;
char s[200010];
map<pair<int,int>,int> mp;
signed main(){
	scanf("%d",&t);
	for(int tt=1;tt<=t;tt++){
		scanf("%d%s",&n,s+1);
		ans=INT_MAX;
		mp.clear();
		mp[{0,0}]=0,x=0,y=0;
		for(int i=1;i<=n;i++){
			if(s[i]=='U') y++;
			if(s[i]=='D') y--;
			if(s[i]=='L') x--;
			if(s[i]=='R') x++;
			if(mp[{x,y}]||(x==0&&y==0)){
				if(i-mp[{x,y}]<ans){
					ans=i-mp[{x,y}];
					l=mp[{x,y}]+1;
					r=i;
				}
			}
			mp[{x,y}]=i;
		}
		if(ans==INT_MAX) printf("-1\n");
		else printf("%d %d\n",l,r);
	}
    return 0;
}

```

---

## 作者：haokee (赞：0)

我们可以发现，如果一段路径可以省略，那么这段路径走之前和走之后的位置会是一样的。因此我们可以使用 STL 当中的 map 来记录上一次走到这个位置的时间。因为是要求最短的区间，因此选择最小值就可以了。时间复杂度 $\mathcal O(n\log_2 n)$。

```cpp
#include <iostream>
#include <map>

using namespace std;

const int kMaxN = 2e5 + 5;

int t, n, x, y, l, r, mn;
map<pair<int, int>, int> f;  // 记录最后一次达到的时间
char c;

int main() {
  for (cin >> t; t; t--) {
    cin >> n;
    x = y = 0, mn = 1e9;  // 清零
    f.clear();            // 清空容器
    f[{x, y}] = 0;        // 初始时在 (0, 0)
    for (int i = 1; i <= n; i++) {
      cin >> c;
      x = x - (c == 'L') + (c == 'R');              // 移动 x
      y = y + (c == 'U') - (c == 'D');              // 移动 y
      if (f.count({x, y}) && i - f[{x, y}] < mn) {  // 如果已经记录过并且比答案更优
        mn = i - f[{x, y}];                         // 修改答案
        l = f[{x, y}] + 1, r = i;                   // 记录位置
      }
      f[{x, y}] = i;                                // 更新
    }
    if (mn == 1e9) {
      cout << "-1\n";
    } else {
      cout << l << ' ' << r << '\n';
    }
  }
  return 0;
}
```

---

## 作者：Six_chestnuts (赞：0)

# 分析

根据题意，既然我们要删除一段最小的操作，并让机器人最后的位置不变。不就是变相的说这段的前一个操作操作完了的位置和折断的最后一个操作操作完了的位置一模一样，而且我们修改的段要最短，那么我们就可以开一个数组来统计这个位置最早出现在那一次操作后面。

### 注意

一定要给初始位置初始值，不然最短的操作没准是从初始位置到初始位置。

# 考场代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
string s;
map<int,int> id;
int get_id(int x,int y)
{
    return x*200000+y;
}
void work()
{
    int n,mini=1000000000,a=0,b=0,l=0,r=0;
    cin>>n>>s;
    s=' '+s;
    id.clear();
    id[0]=get_id(0,0);
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='L')
            a++;
        if(s[i]=='R')
            a--;
        if(s[i]=='U')
            b++;
        if(s[i]=='D')
            b--;
//        int now=0;
        int now=get_id(a,b);
//        cout<<a<<" "<<b<<"!\n\n";
        if(id.count(now)&&mini>i-id[now])
            mini=i-id[now],l=id[now]+1,r=i;
        id[now]=i;
    }
    if(!l&&!r)
        cout<<"-1\n";
    else
        cout<<l<<" "<<r<<"\n";
}
signed main()
{
    int t;
    cin>>t;
    while(t--)
        work();
    return 0;
}
```

---

## 作者：Jinzixun (赞：0)

简单概括一下题意：求一个有 $L,R,U,D$ 的字符串中，求最小区间，使得其中 $L$ 和 $R$，$U$ 和 $D$ 的数量分别相等。

直接使用 $\texttt{map}$ 维护最近走过这个点的时间，并求最小值。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n;
map<int, map<int, int> > mp;
//这里使用的方法和别的题解略有不同。
//使用map嵌套的方式，好处是和二维数组一样，很方便。
string s;
signed main(){
	scanf("%lld", &t);
	while(t--){
        mp.clear();//多测清空！！！
		int ans = 2e18, ansx, ansy, nowx = 0, nowy = 0;
		scanf("%lld", &n);
		cin >> s;
		s = ' ' + s;
		for(int i = 1; i <= n; i++){
			if(s[i] == 'L')	nowx++;
			if(s[i] == 'R')	nowx--;
			if(s[i] == 'U')	nowy++;
			if(s[i] == 'D')	nowy--;//计算新的坐标
			if((mp[nowx][nowy] || (nowx == 0 && nowy == 0)) && i - mp[nowx][nowy] < ans){//如果这个点之前出现过，那么更新答案。
				ans = i - mp[nowx][nowy];
				ansx = mp[nowx][nowy] + 1;//要加一，这样中间的部分才能刚好抵消。
				ansy = i;
			}
            mp[nowx][nowy] = i;//更新这个点。
		}
		if(ans == 2e18)	printf("-1\n");
		else	printf("%lld %lld\n", ansx, ansy);
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

### 题意分析

想要删去一部分指令还要使机器人的终点不能改变，那么这一段指令一定满足:"L"的个数和"R"的个数相等，"U"的个数和"D"的个数相等

或者说，机器人运行要删去的这一段指令前的坐标，和运行要删去这一段指令后的坐标相等

换句话说，若这一段指令是从$i$开始，$j$结束的，则一定满足走完i-1步，和走完j步在同一个点

### 思路分析

首先考虑O(n^2)算法，$x_i$代表第i步走到的横坐标，$y_i$代表第i步走到的纵坐标，那么去枚举i和j，如果$x_i$==$x_j$&&$y_i$==$y_j$&&$ans$>$j-i+1$，那么就更新答案

时间复杂度共O(Tn^2)，在第四个点就TLE了

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n;
char ch;
int x[200010],y[200010];
int ans,minni,minnj;
int main()
{
	ios::sync_with_stdio(0);
	scanf("%d",&T);
	while(T--)
	{
		ans=0x7fffffff;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			cin>>ch;
			if(ch=='L'){x[i]=x[i-1]-1;y[i]=y[i-1];}
			if(ch=='R'){x[i]=x[i-1]+1;y[i]=y[i-1];}
			if(ch=='U'){x[i]=x[i-1];y[i]=y[i-1]+1;}
			if(ch=='D'){x[i]=x[i-1];y[i]=y[i-1]-1;}
		}
		for(int i=0;i<=n;i++)
		   for(int j=i+1;j<=n;j++)
		      {
		      	if(x[i]==x[j]&&y[i]==y[j]&&ans>j-i+1)
		      	    ans=j-i,minni=i+1,minnj=j;
			  }
		if(ans!=0x7fffffff) printf("%d %d\n",minni,minnj);
		else printf("-1\n");
	}
	return 0;
}
```

听说有**神仙**用前缀和+结构体排序+链表过了，应该类似于这个思路

考虑正解，$vis_{x,y}$表示最近一次走到( x , y )点是第几步，那么如果当前走到的$vis_{x,y}$有值，更新答案。

再把当前走到的$vis_{x,y}$更新。（注意是 管更不更新ans，$vis_{x,y}$都要更新一遍，保持$vis_{x,y}$值尽量接近现在走到的步数）

但是x，y有可能为负数，所以我们考虑使用map

###  _Code:_ 

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
int T,n;
char ch[200010];
int ans,mini,minj;
int nx,ny;
map<pair<int,int>,int> vis;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
	   	nx=ny=mini=minj=0;
		ans=0x7fffffff;
		scanf("%d",&n);
		vis.clear();
		vis[make_pair(0,0)]=1;
		for(int i=0;i<n;i++)
			cin>>ch[i];
		for(int i=2;i<=n+1;i++)
		{
			if(ch[i-2]=='R') nx++;
			if(ch[i-2]=='L') nx--;
			if(ch[i-2]=='U') ny++;
			if(ch[i-2]=='D') ny--;
			pair<int,int> now=make_pair(nx,ny);
			if(vis[now]&&i-vis[now]<ans)
			  ans=i-vis[now],mini=vis[now],minj=i;
			vis[now]=i;
			if(ans==2) break;
		}
		if(ans!=0x7fffffff) printf("%d %d\n",mini,minj-1);
		else puts("-1");
	}
	return 0;
}
```


---

