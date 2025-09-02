# [ABC045D] すぬけ君の塗り絵

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc045/tasks/arc061_b

縦 $ H $ 行、横 $ W $ 列のマス目からなる盤があります。最初、どのマス目も白く塗られています。

すぬけ君が、このうち $ N $ マスを黒く塗りつぶしました。$ i $ 回目 ( $ 1\ \leq\ i\ \leq\ N $ ) に塗りつぶしたのは、 上から $ a_i $ 行目で左から $ b_i $ 列目のマスでした。

すぬけ君がマス目を塗りつぶした後の盤の状態について、以下のものの個数を計算してください。

- 各整数 $ j $ ( $ 0\ \leq\ j\ \leq\ 9 $ ) について、盤の中に完全に含まれるすべての $ 3 $ 行 $ 3 $ 列の連続するマス目のうち、黒いマスがちょうど $ j $ 個あるもの。

## 说明/提示

### 制約

- $ 3\ \leq\ H\ \leq\ 10^9 $
- $ 3\ \leq\ W\ \leq\ 10^9 $
- $ 0\ \leq\ N\ \leq\ min(10^5,H×W) $
- $ 1\ \leq\ a_i\ \leq\ H $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ b_i\ \leq\ W $ $ (1\ \leq\ i\ \leq\ N) $
- $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $ $ (i\ \neq\ j) $

### Sample Explanation 1

!\[\](https://atcoder.jp/img/arc061/30326702be007759dce81231012a8353.png) この盤に含まれる $ 3×3 $ の正方形は全部で $ 6 $ 個ありますが、これらのうち $ 2 $ 個の内部には黒いマスが $ 3 $ 個、残りの $ 4 $ 個の内部には黒いマスが $ 4 $ 個含まれています。

## 样例 #1

### 输入

```
4 5 8
1 1
1 4
1 5
2 3
3 1
3 2
3 4
4 4```

### 输出

```
0
0
0
2
4
0
0
0
0
0```

## 样例 #2

### 输入

```
10 10 20
1 1
1 4
1 9
2 5
3 10
4 2
4 7
5 9
6 4
6 6
6 7
7 1
7 3
7 7
8 1
8 5
8 10
9 2
10 4
10 9```

### 输出

```
4
26
22
10
2
0
0
0
0
0```

## 样例 #3

### 输入

```
1000000000 1000000000 0```

### 输出

```
999999996000000004
0
0
0
0
0
0
0
0
0```

# 题解

## 作者：Withers (赞：7)

[题目传送门](https://atcoder.jp/contests/arc061/tasks/arc061_b)
# 题目大意
就是一个 $N$ 行 $W$ 列的矩形，每次输入一个格子，把它染色，变成黑色。然后要求的是所有九宫格里不同黑格子数量个数，简而言之就要求有 $0,1,2\dots9$ 个黑格子的个数
# 思路

我们正常的想法肯定是开数组模拟，但一看数据范围，$H,W$ 都到了 $10^9$ 肯定会 MLE 和 TLE，那怎么办呢

这时候就要想到贡献法，就是每输入一个格子，计算它对包含它的九宫格的贡献（记得判边界）

所以我们只需维护一个答案数组，每次计算新格子对它的影响就行了

但是，又有个新问题：如何记录新加进来的格子所在的九宫格原来黑格子的个数呢？

~~显然~~我们可以用 map 来解决，用它来维护以 $x,y$ 为中心的九宫格黑格子个数

完结撒花！
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long  ans[10];
typedef pair<int,int> pii;//用pair来维护二元组 
map<pii,int> mp;
int main()
{
	long long h,w;
	int n;
	cin>>h>>w>>n;
	ans[0]=(h-2)*(w-2);//初始化，一开始一个黑格子都没有 
	for(int i=1;i<=n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		for(int j=-1;j<=1;j++)
		{
			for(int k=-1;k<=1;k++)//遍历计算影响 
			{
				int x=a+j,y=b+k;//九宫格的中心 
				if(x>1&&x<h&&y>1&&y<w)//判断边界 
				{
					int now;//now表示现在这个九宫格的黑格子的数量 
					now=++mp[{x,y}];
					ans[now]++,ans[now-1]--;
				}
			}
		}
	}
	for(int i=0;i<10;i++) cout<<ans[i]<<endl;
}
```


---

## 作者：tangyigeng (赞：5)

## 简要题意
题面应该够简洁了吧。
## 分析
首先看到是在一个子矩阵中求有多少个黑格子，但看到数据范围开个二位数组肯定是不行的。

仔细一看，包含 $0$ 个黑格子的子矩阵是可以通过包含 $1\sim 9$ 个黑格子的数量算出来的，可以用所有子矩阵的数量减去那些子矩阵的个数，所以现在我们就只用考虑一定包含黑格子的子矩阵。

要满足一定包含黑格子就只用依次枚举黑格子，枚举时依次计算以当前黑格子为中心 $5\times 5$ 的子矩阵内的前缀和，然后按正常方法算再用一个数据结构去个重就行了。

值得注意的是由于黑格子的坐标也很大，所以不能用二维数组直接存，可以给它们排个序，然后在计算前缀和的时候用二分查找看一下当前位置有没有黑格子，具体看代码。
## 代码
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
const int N = 1e5;
pair<int, int> a[N + 10];
map<pair<int, int> , bool> m;
int q[6][6], ans[10], ans0;
int h, w, n;
inline bool check(int x, int y){//二分查找坐标为(x,y)的位置有没有黑格子
	int l = 1, r = n;
	while(l < r){//本蒟蒻不会用lower_bound和upper_bound
		int mid = (l + r) >> 1;
		if(a[mid].first < x)
			l = mid + 1;
		else if(a[mid].first > x)
			r = mid - 1;
		else{
			if(a[mid].second < y)
				l = mid + 1;
			else
				r = mid;
		}
	}
	return a[l] == make_pair(x, y);
}
int main(){
	scanf("%d%d%d", &h, &w, &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &a[i].first, &a[i].second);
	sort(a + 1, a + n + 1);//排序
	for(int i = 1; i <= n; i++){//枚举黑格子
		for(int x = 1; x <= 5; x++){//枚举5*5的子矩阵
			for(int y = 1; y <= 5; y++){
				int ux = a[i].first + x - 3, uy = a[i].second + y - 3;//当前枚举的点在原矩形中的位置
				q[x][y] = check(ux, uy) + q[x - 1][y] + q[x][y - 1] - q[x - 1][y - 1];//前缀和
				if(ux >= 3 && ux <= h && uy >= 3 && uy <= w && x >= 3 && y >= 3 && !m[{ux, uy}]){
					ans[q[x][y] - q[x - 3][y] - q[x][y - 3] + q[x - 3][y - 3]]++;
					ans0++;//0要特殊计算
					m[{ux, uy}] = 1;//去重
				}
			}
		}
	}
	printf("%lld\n", 1ll * (h - 2) * (w - 2) - ans0);
	for(int i = 1; i <= 9; i++)
		printf("%d\n", ans[i]);
	return 0;
}
```
本蒟蒻只会这种垃圾方法。

---

## 作者：Hog_Dawa_IOI (赞：3)

### 题意
给定一个 $H$ 行 $W$ 列的矩形，再给定矩形上 $N$ 个黑格子的坐标。对于每个 $0\le j\le9$ ，求出有多少个  $3\times3$ 的子矩阵包含有**恰好** $j$ 个黑格子。  

数据范围：
- $ 3\ \leq\ H\ \leq\ 10^9 $
- $ 3\ \leq\ W\ \leq\ 10^9 $
- $ 0\ \leq\ N\ \leq\ min(10^5,H×W) $
- $ 1\ \leq\ a_i\ \leq\ H $ $ (1\ \leq\ i\ \leq\ N) $
- $ 1\ \leq\ b_i\ \leq\ W $ $ (1\ \leq\ i\ \leq\ N) $
- $ (a_i,\ b_i)\ \neq\ (a_j,\ b_j) $ $ (i\ \neq\ j) $

### 分析
由于 $ 3\ \leq\ H\ \leq\ 10^9 , 3\ \leq\ W\ \leq\ 10^9 $，所以我们无法直接暴力枚举。但是看到 $ 0\ \leq\ N\ \leq\ min(10^5,H×W) $，可以想到枚举每个点，计算它对每个 $3\times3$ 的子矩阵产生的贡献。  
对于每个点 $(a,b)$，我们枚举它的八个方向记为 $(x,y)$，查询以 $(x,y)$ 为中心的子矩阵当前有多少个黑格子。现在又多了一个点 $(a,b)$，所以把答案加一，同时统计到答案数组中去。由于坐标太大，我们可以把点记录在一个 map 中。    
一开始，所有子矩阵都有 $0$ 个黑格子，所以要给 $ans_0$（有 $0$ 个黑格子的子矩阵数目）初始化。  
### 代码
```cpp
#include<map>
#include<cstdio>
using namespace std;
long long h,w,n,a,b,ans[15];
map<pair<int,int>,int>lwq;
int main()
{
    scanf("%lld%lld%lld",&h,&w,&n),ans[0]=(h-2)*(w-2);
    while(n--)
    {
        scanf("%lld%lld",&a,&b);
        for(int i=-1;i<=1;i++) for(int j=-1;j<=1;j++)
        if(a+i>1&&a+i<h&&b+j>1&&b+j<w)
        {
            int dq=++lwq[make_pair(a+i,b+j)];
            ans[dq]++,ans[dq-1]--;
        }
    }
    for(int i=0;i<=9;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：Acc_Robin (赞：3)

正常想法是开个二维数组模拟，但奈何值域太大，只能用 `map` 多只 $\log$。

考虑新增一个点的贡献，显然只对相邻 $9$ 个格子产生 $+1$ 的影响，那么我们可以维护增量，逐步模拟。

只需要维护一个答案数组 $r[]$，$r[i]$ 表示相邻的格子中恰好有 $i$ 个黑色即可。

注意一些小细节，即靠边的那些格子是不算贡献的！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Acc{
	int dx[9]={-1,-1,-1,0,0,0,1,1,1};
	int dy[9]={1,0,-1,1,0,-1,1,0,-1};
	int n,w,h,x,y,xx,yy,z,i,j;
	long long r[10];
	map<pair<int,int>,int>mp;
	void work(){
		cin>>h>>w>>n,r[0]=(h-2)*1ll*(w-2);
		for(i=1;i<=n;++i){
			cin>>x>>y;
			for(j=0;j<9;++j)if(1<(xx=x+dx[j])&&xx<h&&1<(yy=y+dy[j])&&yy<w){
				if(!mp.count({xx,yy}))mp[{xx,yy}]=z=1;
				else z=++mp[{xx,yy}];
				r[z]++,r[z-1]--;
			}
		}
		for(int i=0;i<10;++i)cout<<r[i]<<'\n';
	}
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：Fuko_Ibuki (赞：3)

**这个题是个模拟.**  
显然每一个涂颜色的格子能够影响$9$个格子.  
因为此题中只问3$\times$3的格子,我们可以考虑对于每一个输入的格子,暴力处理它影响的$9$个格子.  
数据范围是$10^{9}$?对不起,有map是可以为所欲为的.  
这样处理完之后map里$1-9$的个数就是答案,直接遍历一遍map即可.  
最后还剩下$0$的可能.  
我们知道所有的答案都在$0\to9$之间,因此用数学计算算出长$h$宽$w$的矩形网格中$3\times3$的小方格有$(h-2)\times(w-2)$个,减去算出来的1-9的个数就可以得出0的个数.  
愉快地输出答案就A了此题.
```
#include<bits/stdc++.h> //Ithea Myse Valgulious
namespace chtholly{//这里快读快写有30多行,我就省略了.
using namespace std;
const int yuzu=1e5;
typedef pair<int,int> pii;
map<pii,int> mp;
int h=read(),w=read(),n=read(),cnt[10];

int main(){
int i,j;
for (;n--;){
  int x=read(),y=read();
  for (i=max(1,x-2);i<=min(h-2,x);++i){
    for (j=max(1,y-2);j<=min(w-2,y);++j){
      mp[pii(i,j)]++; 
	  }
	}
  }
for (auto p:mp) cnt[p.second]++,n++;
ll ans=1ll*(h-2)*(w-2);
write(ans-n-1),pl;
for (i=1;i<=9;++i) write(cnt[i]),pl;
}
```

---

## 作者：NY_An18623091997 (赞：2)

## 简要题意
有一个 $H$ 行 $W$ 列的矩形，输入 $N$ 个黑格子的坐标，求**恰好**有 $0,1,2,3 \cdots 9$ 的九宫格的数量。

## 思路
看到题目的第一眼就应该想到开二维数组模拟，但是 $3 \le H,W \le 1 \times 10^9$，开二维数组肯定会炸，所以就要用 map 来解决这个问题， ~~不想手写离散化~~。  
学过小学奥数的都知道，最初恰好有 $0$ 个黑格子的九宫格有 $(H-2) \times (W-2)$ 个。如图，当 $H=6,W=5$ 时，一共可以枚举出 $(6-2) \times (5-2) = 12$ 个九宫格中心（蓝色的部分），即有 $12$ 个最初恰好有 $0$ 个黑格子的九宫格。   
![](https://cdn.luogu.com.cn/upload/image_hosting/ywodz0hy.png)  
我们单独定义一个 $ans$ 数组来存答案，初始化为 $ans_0 = (H-2) \times (W-2)$。  
然后我们通过枚举九宫格的中心，来更新 $ans$ 数组，同时别忘了判边界。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pair pair<ll,ll>
using namespace std;
const ll N=1e5+3;
ll h,w,n,x[N],y[N],ans[13];
ll dx[3]={-1,0,1},dy[3]={-1,0,1};
map<pair,ll> m;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>h>>w>>n;
	for(int i=1;i<=n;i++)	cin>>x[i]>>y[i];
	ans[0]=(h-2)*(w-2);//初始化
	for(int i=1;i<=n;i++){
		for(int j=0;j<3;j++){//枚举九宫格的中心 
			for(int k=0;k<3;k++){
				ll xx=x[i]+dx[j],yy=y[i]+dy[k];
				if(xx<=1||xx>=h||yy<=1||yy>=w)	continue;
				m[{xx,yy}]++;//处理ans数组
				ans[ m[{xx,yy}] ]++,ans[ m[{xx,yy}]-1 ]--;
			}
		}
	}
  //完结撒花
	for(int i=0;i<=9;i++)	cout<<ans[i]<<"\n";
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/191879678)

---

## 作者：KarmaticEnding (赞：2)

本题考查您对 STL 容器 `unordered_map` 的理解。

观察到虽然 $H,W$ 很大，但是 $n$ 是很小的，所以我们不能用 $O(H\times W)$ 完成这道题，但是我们可以用 $O(n)$ 完成这道题。

我们想想，每给一个格子 $(x,y)$ 染色成黑色，那么是不是以 $(x-1,y-1),(x-1,y),(x-1,y+1),(x,y-1),(x,y),(x,y+1),(x+1,y-1),(x+1,y),(x+1,y+1)$ 这九个格子为中心的 $3\times 3$ 子矩阵内部的黑色格子数就会 $+1$？

我们用 $cnt_{x,y}$ 表示以 $(x,y)$ 为中心的 $3\times 3$ 子矩阵中黑色格子的个数。

每读入一个黑色格子 $(x,y)$，就令周围 $9$ 个格子的 $cnt+1$。

但是，$x,y$ 太大，存不下怎么办？没关系，我们用一个 `unordered_map` 存储 $cnt$。又有人说，`unordered_map` 的 $key$ 不能是 $pair$ 类型怎么办？`unordered_map` 的 $key$ 不能是 $pair$ 类型的原因是 STL 库里面没有 $pair$ 类型的哈希规则，所以我们要自己定义一个哈希规则。

这里我们定义，对于每一组 $x,y$，其哈希值是 $hsh=x\times(10^9+7)+y$，由于 $H,W\le 10^9$，这个哈希不会重复，把这个哈希之后的 `long long` 类型当作 `unordered_map` 的 $key$，就可以了。

最后分析一下空间复杂度：除去 $cnt=0$ 的情况，由于每读入一个黑色方块只会对周围的 $9$ 个点的 $cnt$ 进行更新，所以 `unordered_map` 里面最多只会存储 $9n$ 个元素，是存得下的。

$151$ ms，迄今为止还是全洛谷最优解。

```cpp
#include<cstdio>
#include<unordered_map>
using namespace std;
unordered_map<long long,int> cnt;
int dx[9]={-1,-1,-1,0,0,0,1,1,1};
int dy[9]={-1,0,1,-1,0,1,-1,0,1};
int n;
int H,W;
long long ans[10];
inline long long hsh(int x,int y){
	return (long long)(x)*1000000007ll+(long long)(y);
}
int main(){
	scanf("%d%d%d",&H,&W,&n);
	ans[0]=(long long)(H-2)*(W-2);
	for(int r=1,x,y;r<=n;++r){
		scanf("%d%d",&x,&y);
		for(int i=0;i<=8;++i){
			if(x+dx[i]>1&&y+dy[i]>1&&x+dx[i]<=H-1&&y+dy[i]<=W-1){//子矩阵必须合法
				++cnt[hsh(x+dx[i],y+dy[i])];
			}
		}
	}
	for(auto iter=cnt.begin();iter!=cnt.end();++iter){
		++ans[iter->second];
	}
	ans[0]=(long long)(H-2)*(long long)(W-2);
	for(int i=1;i<=9;++i){
		ans[0]-=ans[i];
	}
	for(int i=0;i<=9;++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：cjh_trailblazer (赞：1)

[原题面](https://www.luogu.com.cn/problem/AT_arc061_b)　　
## 题目分析：
注意到，题目的数据范围对于 $h$ 和 $w$ 都开到了 $10^9$ 大小，因此不能直接二维数组进行模拟。  
考虑优化，注意到 $n$ 的范围并不大，只有 $10^5$ 大小，因此可以考察每个黑格子对附近的矩形产生的贡献。  
那么如何记录呢？考虑使用 map 进行维护及查找 ~~map 无敌，我说的~~。  
最后遍历一遍 map 即可。  
其余看注释。
## 代码如下：

```cpp
#include<bits/stdc++.h>
#define mihoyo freopen
#define starrail main
#define int long long
#define lowbit(x)  (x&(-x))
using namespace std;
inline int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int dx[9]={-1,-1,-1,0,0,0,1,1,1};
const int dy[9]={-1,0,1,-1,0,1,-1,0,1};
int n,w,h,s[10];
struct node{
	int x,y;
}a[100010];
map<pair<int,int>,int>black;
signed starrail()
{
	h=read();w=read();n=read();
	for(int i=1;i<=n;i++){
		a[i].x=read();
		a[i].y=read();
	}
	s[0]=1*(h-2)*(w-2);//s[0]记得初始化 
	for(int i=1;i<=n;i++){
		for(int j=0;j<9;j++){
			int x=a[i].x+dx[j];
			int y=a[i].y+dy[j];//9个格子 
			if(x>1&&x<h&&y>1&&y<w)/*边界别忘了*/{
				int cnt=++black[make_pair(x,y)];
				s[cnt]++; 
				s[cnt-1]--;//记得减掉 
			}
			else continue;
		}
	}
	for(int i=0;i<=9;i++)	printf("%lld\n",s[i]);
	return 0;
}
```

---

## 作者：caibet (赞：1)

### 题意：

有 $n$ 个放在 $h\times w$ 棋盘上的棋子，求有 $0\sim 9$ 个棋子的 $3\times 3$ 矩阵分别有几个。

$1\le h,w\le 10^9,1\le n\le 10^5$。

### 解法：

$1\le h,w\le 10^9$，我们肯定不能开数组模拟了。

但是 $1\le n\le 10^5$，所以我们可以对于每个棋子，记录这个棋子对答案的影响。

显然，这个棋子所在的所有 $3\times3$ 矩阵的包含棋子数 $+1$。

这些矩阵，我们用其中心来表示，例如 $f(2,2)$ 表示以第 $2$ 行第 $2$ 列格子为中心的 $3\times3$ 矩阵。若一个棋子的坐标为 $(x,y)$，那么其相邻的所有格子（注意不包括纵坐标为 $1$ 或 $w$、横坐标为 $1$ 或 $h$ 的格子，因为以它们为中心无法构成一个完整的 $3\times3$ 矩阵）为中心的矩阵包含的棋子数都会 $+1$。

于是，我们用一个 `map<pair<int,int>,int>` 来记录所有矩阵包含的棋子数。每次读入一个棋子的坐标，我们把所有相邻的格子（注意同上）代表的矩阵包含棋子数 $+1$。最后遍历整个 `map`，统计答案即可。

注意包含 $0$ 个棋子的矩阵数量是总有效矩阵数减去被计入 `map` 的矩阵数。

```cpp
namespace{
	map<pair<int,int>,int> st;
	int n,m,k,cnt[10],sum;
	const int dx[9]={1,1,1,0,0,0,-1,-1,-1},dy[9]={1,0,-1,1,0,-1,1,0,-1};
	void work(){
		n=read();m=read();k=read();
		while(k--){
			Int x=read(),y=read();
			F(i,0,<9){
				Int nx=x+dx[i],ny=y+dy[i];//遍历相邻的格子
				if(nx>1&&nx<n&&ny>1&&ny<m){
					++st[{nx,ny}];//记录答案
				}
			}
		}
		for(map<pair<int,int>,int>::iterator it=st.begin();it!=st.end();++it){//遍历 map
			++sum;//统计加入 map 的矩阵数量
			++cnt[it->second];
		}
		put("%lld\n",(n-2ll)*(m-2)-sum);//剩下的矩阵
		F(i,1,<=9){
			put("%d\n",cnt[i]);
		}
	}
}
```

---

## 作者：YuYuanPQ (赞：1)

我没场切纯属唐氏。

看到题面都会想到模拟。

但是数据范围比较大，所以不行。

思路非常好想，考虑每个点的贡献。

用 map 维护：以当前点 $(x,y)$ 为中心的九宫格中，黑格子的个数。

形象地理解：

![pic1](https://cdn.luogu.com.cn/upload/image_hosting/lpgsmn67.png)

$\color{B5E51D}绿色格子$ 表示当前点。

$\color{FFF200}黄色格子$ 表示能够影响到的点，包括当前点共有 $9$ 个。

初始时：不计算四周 $2$ 层的格子，$s[0]=(n-2)\times(m-2)$。

画图不易，点个赞再走吧~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
#define MAXN 100010
using namespace std;
int n,m,k;
ll s[10];
int dx[9]={-1,-1,-1,0,0,0,1,1,1};
int dy[9]={-1,0,1,-1,0,1,-1,0,1};
struct node{
    int x,y;
}d[MAXN];
map<pair<int,int>,int>mp;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++) scanf("%d%d",&d[i].x,&d[i].y);
    s[0]=1ll*(n-2)*(m-2);//不计算四周2层的格子
    for(int i=1;i<=k;i++)//考虑每个点的贡献
    {
        for(int j=0;j<9;j++)//包括当前点
        {
            int p=d[i].x+dx[j],q=d[i].y+dy[j];
            if(!(p>1&&p<n&&q>1&&q<m)) continue;
            int cnt=++mp[mkp(p,q)];
            s[cnt]++;//贡献
            s[cnt-1]--;//注意这里要减1
        }
    }
    for(int i=0;i<10;i++) printf("%lld\n",s[i]);
    return 0;
}
```

---

## 作者：leixinranYY (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc061_b)
## 题目大意
给定一个 $H$ 行 $W$ 列的矩形，再给定矩形上 $N$ 个黑格子的坐标。对于每个 $0\le j\le9$ 求出有多少个 $3\times3$ 的子矩阵包含有恰好 $j$ 个黑格子。
## 思路
首先 $H$ 和 $W$ 数值过大，开二维数组肯定会爆，所以应该用 map 优化，~~写离散化太麻烦~~。

接下来我们定义一个 $ans$ 数组来记录答案。每次输入一个黑格子，都计算一下这个黑格子对整个九宫格的贡献，最后输出 $ans$ 就行了。

## 初始化

众所周知，矩阵中含有 $0$ 个黑格子的九宫格有 $(H-2)\times (W-2)$ 个，所以 $ans_0$ 初始化为 $(H-2)\times (W-2)$。
另外，因为 $H,M\le1\times10^9$，所以要开 long long。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans[11],x,y,a,b,h,w,n,now;
map<pair<int,int>,int>m;
signed main()
{
	scanf("%lld%lld%lld",&h,&w,&n);
	ans[0]=(h-2)*(w-2);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a,&b);
		for(int j=-1;j<=1;j++)
		{
			for(int k=-1;k<=1;k++)
			{
				x=a+j,y=b+k;
				if(x>1 && x<h && y>1 && y<w)
				{
					now=0;
					now=++m[make_pair(x,y)];
					ans[now]++;
					ans[now-1]--;
				}
			}
		}
	}
	for(int i=0;i<=9;i++)printf("%lld\n",ans[i]);
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/192509829)

---

## 作者：__Creeper__ (赞：0)

## 题目大意

给定一个 $H \times W$ 列的矩形，再给定矩形上 $N$ 个黑格子的坐标。对于每个 $0 \le j \le 9$，求出有多少个 $3 \times 3$ 的子矩阵包含有恰好 $j$ 个黑格子。

## 思路

因为 $H$ 和 $W$ 过大，我们可以用贡献做法。对于每次输入的格子坐标，计算这个格子对包含它的九宫格的贡献。这时维护一个答案数组，每次计算新格子对它的影响，再用 map 维护 $(a,b)$ 为中心的九宫格黑格子个数就行了。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, h, w, ans[10];
map<pair<int, int>, int> mp;

void solve()
{
	cin >> h >> w >> n;
	ans[0] = ( h - 2 ) * ( w - 2 );
	for ( int i = 1; i <= n; i++ )
	{
		int a, b;
		cin >> a >> b;
		for ( int j = -1; j <= 1; j++ )
		{
			for ( int k = -1; k <= 1; k++ ) 
			{
				int x = a + j, y = b + k; 
				if ( x > 1 && x < h && y > 1 && y < w ) // 边界
				{
					mp[{x, y}]++;
					ans[mp[{x, y}]]++;
					ans[mp[{x, y}] - 1]--;
				}
			}
		}
	}
	for ( int i = 0; i <= 9; i++ ) cout << ans[i] << endl;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
//	cin >> T;
	while ( T-- ) solve();
	return 0;
}
```

---

