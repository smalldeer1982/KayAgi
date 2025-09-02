# Lena and Matrix

## 题目描述

Lena is a beautiful girl who likes logical puzzles.

As a gift for her birthday, Lena got a matrix puzzle!

The matrix consists of $ n $ rows and $ m $ columns, and each cell is either black or white. The coordinates $ (i,j) $ denote the cell which belongs to the $ i $ -th row and $ j $ -th column for every $ 1\leq i \leq n $ and $ 1\leq j \leq m $ . To solve the puzzle, Lena has to choose a cell that minimizes the Manhattan distance to the farthest black cell from the chosen cell.

More formally, let there be $ k \ge 1 $ black cells in the matrix with coordinates $ (x_i,y_i) $ for every $ 1\leq i \leq k $ . Lena should choose a cell $ (a,b) $ that minimizes

$$\max_{i=1}^{k}(|a-x_i|+|b-y_i|). $$

As Lena has no skill, she asked you for help. Will you tell her the optimal cell to choose?

## 说明/提示

In the first test case the two black cells have coordinates $ (1,1) $ and $ (3,2) $ . The four optimal cells are $ (1,2) $ , $ (2,1) $ , $ (2,2) $ and $ (3,1) $ . It can be shown that no other cell minimizes the maximum Manhattan distance to every black cell.

In the second test case it is optimal to choose the black cell $ (2,2) $ with maximum Manhattan distance being $ 2 $ .

## 样例 #1

### 输入

```
5
3 2
BW
WW
WB
3 3
WWB
WBW
BWW
2 3
BBB
BBB
5 5
BWBWB
WBWBW
BWBWB
WBWBW
BWBWB
9 9
WWWWWWWWW
WWWWWWWWW
BWWWWWWWW
WWWWWWWWW
WWWWBWWWW
WWWWWWWWW
WWWWWWWWW
WWWWWWWWW
WWWWWWWWB```

### 输出

```
2 1
2 2
1 2
3 3
6 5```

# 题解

## 作者：王熙文 (赞：7)

## 思路

其实拆开曼哈顿距离之后分讨也可以做，但是这里有一个更加无脑的做法：随机化。

考虑随机 $500$ 个点，对于这些点找到其最远的 `B` 格子，然后枚举所有点计算与这些 `B` 格子的最远曼哈顿距离，取最小即可。

## 参考代码

```cpp
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;

int n,m;

string s[1010];

pair<int,int> p[510];

int main()
{
	int t; cin>>t;
	while(t--)
	{
		int cnt=0;
		cin>>n>>m;
		for(int i=1; i<=n; ++i)
		{
			cin>>s[i]; s[i]=" "+s[i];
		}
		for(int i=1; i<=500; ++i)
		{
			int x=rand()%n+1,y=rand()%m+1;
			int ax=-1,ansx,ansy; // 注意，这里的 ax 不能设为 0，因为如果随机到的点恰好是唯一的一个 B，曼哈顿距离是 0，不能更新了
			for(int j=1; j<=n; ++j)
			{
				for(int k=1; k<=m; ++k)
				{
					if(s[j][k]=='B')
					{
						if(abs(x-j)+abs(y-k)>ax)
						{
							ax=abs(x-j)+abs(y-k);
							ansx=j,ansy=k;
						}
					}
				}
			}
			p[++cnt]={ansx,ansy};
		}
		sort(p+1,p+cnt+1);
		cnt=unique(p+1,p+cnt+1)-p-1;
		int in=1e9,ansx,ansy;
		for(int i=1; i<=n; ++i)
		{
			for(int j=1; j<=m; ++j)
			{
				int nowax=0;
				for(int k=1; k<=cnt; ++k)
				{
					nowax=max(nowax,abs(i-p[k].first)+abs(j-p[k].second));
				}
				if(nowax<in)
				{
					in=nowax;
					ansx=i,ansy=j;
				}
			}
		}
		cout<<ansx<<' '<<ansy<<'\n';
	}
	return 0;
}
```

---

## 作者：linyihdfj (赞：7)

## D. Lena and Matrix ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16366229.html)

#### 题目描述 ####
[原题面](https://codeforces.com/problemset/problem/1689/D)

给定一个 $n\times m$ 的矩阵，每个位置都有一个颜色，分别为黑色或白色，要求你选择一个位置（不计这个位置上是什么颜色），使得这个位置到所有黑色格子的曼哈顿距离的最大值最小。

曼哈顿距离即：$|x_1 - x_2|  + |y_1 - y_2|$
#### 题目分析 ####
要求的是最大值最小，其实发现这个最大值不是和任意一个黑色格子的距离都有可能成为最大值的，能成为最大距离的黑色格子一定是最左上、右下、左下、右上的黑格子，可以发现如果不是这四个格子，那么把距离转化到这四个黑色格子上都一定可以增加。

下面就是如何寻找着四个黑色格子的问题了，我感觉这个思路还是很神奇的。

考虑如果一个格子离左上角越近，$x$ 越小，$y$ 越小，而且 $x$ 与 $y$ 的减小，对其离左上角的距离产生的贡献是一样的，那么就直接令这个贡献为 $x+y$，那么最左上角的点也就一定是贡献最小的点，最右下角的点也一定是贡献最大的点，这就解决了两个。

考虑如果一个格子里右上角越近，$x$ 越大，$y$ 越小，而且它们产生的贡献也都是一样的，所以就考虑直接令贡献为 $x-y$，这样最右上的点也就是 $x-y$ 最大点，最左下的点也就是 $x-y$ 最小的点，至此四个点全部解决了。

那么就是要找一个位置使得这个位置到这四个位置的距离最大值最小，那么就直接枚举每一个位置寻找一下就好了。
#### 代码详解 ####

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9+5;
struct node{
	int x,y;
	node(){}
	node(int _x,int _y){
		x = _x,y = _y;
	}
};
int main(){
	int t;
	cin>>t;
	while(t--){
		node a[6];
		bool flag[6];
		memset(flag,0,sizeof(flag));
		int n,m;
		cin>>n>>m;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				char h;
				cin>>h;
				if(h == 'B'){
					if(i + j > a[1].x + a[1].y || !flag[1])	a[1] = node(i,j),flag[1] = true;
					//越在右下角 i + j 越大 
					if(i + j < a[2].x + a[2].y || !flag[2])	a[2] = node(i,j),flag[2] = true;
					//越在左上角 i + j 越小 
					if(i - j > a[3].x - a[3].y || !flag[3])	a[3] = node(i,j),flag[3] = true;
					//越在右上角 i - j 越大 
					if(i - j < a[4].x - a[4].y || !flag[4]) a[4] = node(i,j),flag[4] = true;
					//越在左下角 i - j 越小 
				}
			}
		}
		int res = INF;
		node ans;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				int h = 0;
				for(int k=1; k<=4; k++){
					h = max(h,abs(i - a[k].x) + abs(j - a[k].y));
				}
				if(h < res){
					ans = node(i,j);
					res = h;	
				}
			}
		}
		printf("%d %d\n",ans.x,ans.y);
	}
	return 0;
}
```

先去找四个点找到了就每个位置枚举一下，最后输出就好了。

---

## 作者：npqenqpve (赞：3)

板题。
可以考虑枚举答案在哪个点。

考虑到曼哈顿距离转切比雪夫距离，记 $d(a,b)$ 为两点的曼哈顿距离，$f(a,b)$ 为两点的切比雪夫距离，那么把每个点 $(x,y)$ 变换成 $(x+y,x-y)$ 之后，两点的曼哈顿距离就等于变换后的切比雪夫距离。

枚举答案点，然后显然只有最大/小的 $x$ 或 $y$ 可能制造最大的 $f(a,b)$，那么 $b$ 的取值就只有至多 $4$ 个，取 $\max$ 后打擂台即可。

---

## 作者：Zhao_daodao (赞：2)

# [题目传送门](https://www.luogu.com.cn/problem/CF1689D)

# 题目描述
多组数据。对于每一组数据，输入两个数 $n$，$m$，分别代表矩阵的行和列。

对于每个矩阵，第 $i$ 行、第 $j$ 列的字符 $a_{i,j}$，$W$ 或 $B$，表示颜色。

对于矩阵上的每个黑点，计算到达每一个黑点的曼哈顿距离最大值 $D_{i,j}$。

求 $D_{i,j}=\min(D_{i,j})$ 时的点 $(i,j)$。

# 题目分析
对于每一个点，设点为 $k$，坐标为 $(k_x,k_y)$。

又有一黑点，设点为 $B$，坐标为 $(B_x,B_y)$。

此时点 $k$ 到点 $B$ 的曼哈顿距离为 $D_{B,k}=\left|k_x-B_x\right|+\left|k_y-B_y\right|$。

将绝对值拆开，得：

$D_{B,k}=\left\{\begin{matrix} 
   (k_x-B_x)+(k_y-B_y)&B_x<k_x,B_y<k_y\\  
   (k_x-B_x)+(B_y-k_y)&B_x<k_x,B_y\ge k_y\\
   (B_x-k_x)+(k_y-B_y)&B_x\ge k_x,B_y<k_y\\
   (B_x-k_x)+(B_y-k_y)&B_x\ge k_x,B_y\ge k_y\\
\end{matrix}\right. $

因为将 $K$ 点的坐标更改，不影响四个式子的相对取值。

所以对于每一个式子，均存在一个 $B$，使得该条式子最大。

---
将每一个最大值记为 $ans_i$，其中 $i\in \left[1,4\right]$。

$ans_i$ 计算公式：

$\left\{\begin{matrix} 
    ans_1=(A_x,A_y)&A_x+A_y=\min(K_1)\\  
    ans_2=(B_x,B_y)&B_x-B_y=\min(K_2)\\
    ans_3=(C_x,C_y)&C_x+C_y=\max(K_2)\\  
    ans_4=(D_x,D_y)&D_x-D_y=\max(K_1)\\
\end{matrix}\right. $

其中 $K_1$ 为所有黑点 $t$ 的 $t_x+t_y$ 构成的集合，$K_2$ 为所有黑点 $t$ 的 $t_x-t_y$ 构成的集合。

这样就很好的解释了为什么四个黑点要在四个角落。

---
此时 $ans$ 数组对应的四个点即为各个式子的最大值，换言之，枚举其他的点不会更优。

所以我们只用枚举这四个点，计算最大曼哈顿距离即可。

做法：将矩阵的四个 $ans$ 数组对应的点算出来，再枚举每一个点，计算与四个 $ans$ 对应的点的最大值。

# 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e3+5;
int n,m;
char a[MAXN][MAXN];
void solve(){
    cin>>n>>m;
    bool flag=1;
    pair<int,int>ans[5];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]!='B')continue;
            if(flag){
                for(int t=1;t<=4;t++)
                    ans[t].first=i,ans[t].second=j;
                flag=0;
                continue;
            }
            if(ans[1].first+ans[1].second>i+j)
                ans[1].first=i,ans[1].second=j;
            if(ans[2].first-ans[2].second>i-j)
                ans[2].first=i,ans[2].second=j;
            if(ans[3].first-ans[3].second<i-j)
                ans[3].first=i,ans[3].second=j;
            if(ans[4].first+ans[4].second<i+j)
                ans[4].first=i,ans[4].second=j;
        }
    pair<int,int>anss;
    int cntt=1e9;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            int cnt=0;
            for(int t=1;t<=4;t++)
                cnt=max(cnt,abs(i-ans[t].first)+abs(j-ans[t].second));
            if(cntt>cnt){
                cntt=cnt;
                anss.first=i;
                anss.second=j;
            }
        }
    cout<<anss.first<<" "<<anss.second<<"\n";
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--)solve();
}
```

---

## 作者：DengDuck (赞：2)

考虑对于已知点快速求最远距离，不是很好求，但是如果你转成切比雪夫距离，就很容易了。

怎么转换这个问题比较经典，我在这里直接上结论，可以将点 $(x,y)$ 转换成 $(y-x,x+y)$，然后前者与其他点的曼哈顿距离为后者的切比雪夫距离等价。

那么我们这里也考虑这么转换，转换之后 $(X,Y)$ 到各个特殊点 $(x_i,y_i)$ 的最大距离如下（坐标默认为转换后的）：

$$
\max({\max{(|X-x_i|,|Y-y_i|)}})
$$

显然可以变化变化，然后就变成：

$$
\max({\max{(|X-x_i|),\max(|Y-y_i|)}})
$$

然后这个式子就可以快速求了，然后你直接枚举原来的矩阵上的点就行了。

时间复杂度为 $\mathcal O(nm\log nm)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=2005;
LL T,n,m,a[N][N],ansx,ansy;
vector<LL>v1,v2;
char c;
LL cal(LL xx,LL yy)
{
	return max({xx-v1[0],yy-v2[0],v1[v1.size()-1]-xx,v2[v2.size()-1]-yy});
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;		
		ansx=1e9;
		v1.clear(),v2.clear();
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				cin>>c;
				if(c=='B')
				{
					v1.push_back(j-i);
					v2.push_back(i+j);
				}
			}
		}
		sort(v1.begin(),v1.end());
		sort(v2.begin(),v2.end());
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				LL xx=j-i,yy=i+j;
				if(cal(xx,yy)<cal(ansy-ansx,ansy+ansx))
				{
					ansx=i,ansy=j;
				}
			}
		}
		cout<<ansx<<' '<<ansy<<endl;
	}

}
```

---

## 作者：Ryder00 (赞：2)

题意清晰，不再阐述。

## 思路
分析容易得到，对于一列中的所有黑格子，只有最上边和最下边的两个格子可能造成贡献。对于一行中的黑格子同理。所以，对于每一列，我们可以只保留上下两个格子。这样，总的黑格子数就降到了 $O(m)$ 级别。

现在我们来考虑，当前枚举的格子从 $(i,j)$ 移到了 $(i,j+1)$ 时，贡献发生的变化。分析可得，对于 $\left[ 1,j \right]$ 列上的所有黑格子，距离都增加了 $1$。而对于 $\left[ j+1,m \right]$ 列上的黑格子，距离都减少了 $1$。我们可以使用线段树的区间修改、区间查询来完成维护。

枚举格子，使用线段树维护数据的复杂度为 $O(nm\log m)$，枚举时换行后重新统计贡献的复杂度为 $O(nm)$，总复杂度为 $O(nm \log m)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=1e3+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,m,w[N][3],cnt,val[N*4],t[N*4],tag[N*4],lst[N*2];
char a[N][N];
void pushup(int id){
    t[id]=max(t[id*2],t[id*2+1]);
}
void pushdown(int id){
    if(tag[id]==0) return ;
    t[id*2]+=tag[id],t[id*2+1]+=tag[id];
    tag[id*2]+=tag[id],tag[id*2+1]+=tag[id];
    tag[id]=0;
}
void build(int id,int l,int r){
    t[id]=0,tag[id]=0;
    if(l==r){
        t[id]=val[l];
        tag[id]=0;
        return ;
    }
    int mid=(l+r)>>1;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
    pushup(id);
}
void add(int id,int l,int r,int L,int R,int val){
    if(L>R) return ;
    if(L<=l&&R>=r){
        t[id]+=val;
        tag[id]+=val;
        return ;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    if(L<=mid) add(id*2,l,mid,L,R,val);
    if(R>mid) add(id*2+1,mid+1,r,L,R,val);
    pushup(id);
}
void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    }
    for(int j=1;j<=m;j++){
        bool pd=0;
        w[j][1]=w[j][2]=0;
        for(int i=1;i<=n;i++){
            if(a[i][j]=='W') continue;
            w[j][2]=i;
            if(!pd){
                pd=1;
                w[j][1]=i;
            }
        }
    }
    int mx=inf,ansi=0,ansj=0;
    for(int i=1;i<=n;i++){
        cnt=0;
        for(int j=1;j<=m;j++){
            if(!w[j][1]) {
                lst[j]=lst[j-1];
                continue;
            }
            val[++cnt]=abs(w[j][1]-i)+abs(j-0);
            val[++cnt]=abs(w[j][2]-i)+abs(j-0);
            lst[j]=lst[j-1]+2;
        }
        build(1,1,cnt);
        for(int j=1;j<=m;j++){
            if(j>1) add(1,1,cnt,1,lst[j-1],1);
            add(1,1,cnt,lst[j-1]+1,cnt,-1);
            if(t[1]<mx){
                mx=t[1];
                ansi=i,ansj=j;
            }
        }
    }
    cout<<ansi<<" "<<ansj<<endl;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>T;
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：revolutionary_oier (赞：1)

# CF1689D Lena and Matrix
## 题目描述
- $n \cdot m$ 的矩阵，求矩阵上任意一点坐标使得到矩阵上的关键点曼哈顿距离最大值最小。
- 数据范围：$\sum n \cdot m \leq 10^6$ 。
## 思路点拨
考虑每个点，只需要关注它到其他点曼哈顿距离的最大值，而实际上全局只会有 $4$ 个点真正会影响最大值。

$dis = |x_1-x_2|+|y_1-y_2|$ 将绝对值拆开分为 $4$ 种情况，如下：
 
- $dis = x_1-x_2+y_1-y_2$

- $dis = x_1-x_2+y_2-y_1$

- $dis = x_2-x_1+y_1-y_2$

- $dis = x_2-x_1+y_2-y_1$
 
设定 $(x_1,y_1)$ 为关键点，若使距离dis最大，推广一下 $(x_2,y_2)$ 作为四至点（地理）需要满足以下 $4$ 点之一：

- $\min(x_2+y_2)$

- $\min(x_2-y_2)$

- $\max(x_2-y_2)$

- $\max(x_2+y_2)$

先预处理出四至点，再暴力每个点到四至点的曼哈顿距离最大值的最小值（打擂台）。

预处理时间复杂度：$\Omicron(4 \cdot n)$ 。 


打擂台时间复杂度：$\Omicron(4 \cdot n)$ 。

## 题目收获
将关键式分解压缩解空间。

## 代码实现


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=1e3+10;
const int inf=1e18;
int t,n,m;
bool flag;
int pos[10][2];
char a[maxn][maxn];
inline void input(){
    flag=true;
    scanf("%lld%lld",&n,&m);
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=m;j++){
            scanf(" %c",&a[i][j]); 
            if(a[i][j]=='B')flag=false;
        }
    }
}
inline void init(){
    pos[1][0]=pos[1][1]=inf;
    pos[2][0]=inf;
    pos[2][1]=-inf;
    pos[3][0]=pos[3][1]=-inf;
    pos[4][0]=-inf;
    pos[4][1]=inf;
}
inline void calculate(){
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=m;j++){
            if(a[i][j]=='W')continue;
            if(i+j<pos[1][0]+pos[1][1]){
                pos[1][0]=i;
                pos[1][1]=j;
            }
            if(i-j<pos[2][0]-pos[2][1]){
                pos[2][0]=i;
                pos[2][1]=j;
            }
            if(i+j>pos[3][0]+pos[3][1]){
                pos[3][0]=i;
                pos[3][1]=j;
            }
            if(i-j>pos[4][0]-pos[4][1]){
                pos[4][0]=i;
                pos[4][1]=j;
            }
        }
    }
}
inline void greedy(){
    int ans=inf,ansl=1,ansr=1;
    if(flag){
        printf("%lld %lld\n",ansl,ansr);
        return ;
    }
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=m;j++){
            int mx=-inf;
            for(register int k=1;k<=4;k++){
                int dis=abs(pos[k][0]-i)+abs(pos[k][1]-j);
                mx=max(dis,mx);
            
            }
            if(mx<ans){
                ans=mx;
                ansl=i;
                ansr=j;
            }
        }
    }
    printf("%lld %lld\n",ansl,ansr);
    return ;
}
inline void solve(){
    scanf("%lld",&t);
    while(t--){
        input();
        init();
        calculate();
        greedy();
    }
}
signed main(){
    solve();
    return 0;
}
```

---

## 作者：yyym (赞：0)

我们可以使用二分的方法来解决这道题，综合复杂度为 $O(\log(n + m)n^2)$；

我们可以直接二分答案，并在 `check_(len)` 函数中检验是否合法。

在 `check_(len)` 函数中，我们先枚举 $k\:(k \in [1, n])$ 作为我们寻找的合法答案的第一个坐标值，此时我们只需要确定第二个坐标值是否存在且合法即可。

我们发现，如果一个坐标与所有黑色坐标的曼哈顿距离小于 `len` 的话，那么所有的黑色坐标都必须在图中有颜色的区块内。

![ORIdRp.png](https://ooo.0x0.ooo/2024/07/31/ORIdRp.png)

所以下一步我们就需要判断是否所有的黑色坐标都在颜色快中：

*  我们首先来判断第一个坐标值。
	
	> 一个显然的结论是：所有的黑色坐标的第一个坐标值都应该在 $[k - len, k + len]$ 之中。
	>
	> 我们可以提前维护所有黑色坐标第一个坐标值的上界和下界来加速这个判断过程。

* 我们接着判断第二个坐标值。

	> 我们枚举 $\alpha \:(\alpha \in [k - len, k + len])$，我们可以计算出：如果要让第一个坐标值为 $\alpha$ 的黑色坐标在有色区块中，那么我们要寻找的答案的第二个坐标值的范围。
	>
	> 我们将所有 $\alpha$ 算出的范围并在一起，如果并的过程中，他们的交集为空集，那么第一个坐标值 $k$ 无效。
	>
	> 注意，如果当前 $\alpha$ 中不存在黑色坐标，那么范围为 $[1, m]$；

我们可以在 `check_(len)` 中保存合法的答案，之后直接输出即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;
int n, m;
map<int, pair<int,int> > infos;
lli LL, RR;
pair<int,int> ans;
lli disL;


bool check_(lli mid) {
    bool flag = false;
    for(int i = 1 ; i <= n ; i ++) {
        int Lpos = i - mid, Rpos = i + mid;
        Lpos = max(1, Lpos); Rpos = min(n, Rpos);
        if(LL < Lpos || RR > Rpos) continue;

        pair<int,int> area = make_pair(INT_MIN, INT_MAX);
        bool finded = true;
        for(int j = Lpos ; j <= Rpos ; j ++) {
            int hh = mid - abs(j - i);
            if(infos[j].second - infos[j].first + 1 > hh * 2 + 1) {
                finded = false; break;
            }
            int LLpos = max(1, infos[j].second - hh), RRpos = min(infos[j].first + hh, m);
            if(infos[j].first == 0) {
                LLpos = 1, RRpos = m;
            }
            if(area.first > RRpos || area.second < LLpos) {
                finded = false; break;
            }
            area.first = max(area.first, LLpos);
            area.second = min(area.second, RRpos);
        }
        if(finded) {
            flag = true;
            if(disL > mid) {
                ans.first = i; ans.second = area.first;
                disL = mid;
            }
            break;
        }
    }
    return flag;
}

void solve() {
    infos.clear(); disL = INT_MAX;
    cin >> n >> m;
    for(int i = 1 ; i <= n ; i ++) {
        string ss; cin >> ss;
        for(int j = 0 ; j < m ; j ++) {
            if(ss[j] == 'W') continue;
            if(infos[i].first == 0) {
                infos[i].first = infos[i].second = j + 1;
            } else {
                infos[i].first = min(infos[i].first, j + 1);
                infos[i].second = max(infos[i].second, j + 1);
            }
        }
    }
    LL = (*infos.begin()).first; RR = (*(--infos.end())).first;

    lli L = 0, R = n + m + 1;
    while(L < R) {
        lli mid = (L + R) >> 1;
        if(check_(mid)) R = mid;
        else L = mid + 1;
    }
    cout << ans.first << " " << ans.second << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    lli ask; cin >> ask;
    while (ask --)
        solve();
    return 0;
}
```

---

## 作者：sgl654321 (赞：0)

我的做法是 $O(nm\log nm)$ 的，不是最优秀的，但我认为也有一定启发意义。

### 题目大意
给定一个只含有字符 `R` 和 `B` 的 $n\times m$ 的矩阵，请在其中选出一个点 $(x,y)$，最小化 $\max\{|x-i|+|y-j|\}$，其中 $(i,j)$ 是一个字符为 `B` 的点。

### 解题思路
首先我们容易发现，每一行有用的字符 `B` 肯定要么是最左边的，要么是最右边的。中间的肯定不优秀。

那么我们就只保留每一行最左边和最右边的 `B`。

接着，我们考虑先从左往右枚举每一列，再从上往下枚举该列的每一行。在同一列中，$|y-j|$ 这一项永远不会变化，变化的只是行之间的差值。

同时，从第 $i-1$ 行移动到第 $i$ 行，$i\sim n$ 行中的 `B` 与其横向距离减少了 $1$，$1\sim i - 1$ 行中的 `B` 与其横向距离增加了 $1$。

套路地，对行建立一颗线段树，我们发现我们只需要进行区间加 $1$，区间减 $1$，区间最大值三种操作即可。这样我们就可以计算出每一个位置 $(i,j)$ 到所有 `B` 点的距离的最大值 $b_{i,j}$ 了。

最后统计答案时，我们枚举每一个位置，看看哪个的 $b_{i,j}$ 最小，输出这个 $(i,j)$ 即可。

实现比较容易。

### 参考代码
注意多测的清空，还有列变化时的清空。

```cpp
// LUOGU_RID: 168527190
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node{
	ll l, r, ma, tag; 
} t[1010 << 2];
ll tt, n, m, b[1010][1010], mi[1010], ma[1010], pos[1010];
ll l[1010], r[1010], tot, now, ansx, ansy;
char a[1010][1010];
void build(ll i, ll l, ll r){
	t[i].l = l; t[i].r = r;
	if(l == r){
		t[i].ma = 0; return;
	}
	ll mid = (l + r) >> 1;
	build(i * 2, l, mid); build(i * 2 + 1, mid + 1, r);
}
void pushdown(ll i){
	if(t[i].tag == 0) return;
	t[i * 2].tag += t[i].tag; t[i * 2 + 1].tag += t[i].tag;
	t[i * 2].ma += t[i].tag; t[i * 2 + 1].ma += t[i].tag;
	t[i].tag = 0;
}
void xiugai(ll i, ll l, ll r, ll k){
	if(l <= t[i].r && r >= t[i].l){
		if(l <= t[i].l && r >= t[i].r){
			t[i].ma += k; t[i].tag += k;
			return;
		}
		pushdown(i);
		xiugai(i * 2, l, r, k); xiugai(i * 2 + 1, l, r, k);
		t[i].ma = max(t[i * 2].ma, t[i * 2 + 1].ma);
	}
}
void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		l[i] = 1e16, r[i] = -1e16;
	for(int i = 1; i <= 4 * n; i++) t[i].l = t[i].r = t[i].ma = t[i].tag = 0;	
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
			if(a[i][j] == 'B')
				l[i] = min(l[i], (ll) j),
				r[i] = max(r[i], (ll) j);
		}

	tot = 0;
	for(int i = 1; i <= n; i++)
		if(l[i] != 1e16) tot++, mi[tot] = l[i], ma[tot] = r[i], pos[tot] = i;
//	for(int i = 1; i <= tot; i++) cout << mi[i] << ',' << ma[i] << endl;
//	cout << endl;
	
	for(int j = 1; j <= m; j++)
	{
		now = 1;
		for(int i = 1; i <= 4 * tot; i++)
			t[i].l = t[i].r = t[i].ma = t[i].tag = 0; 
		build(1, 1, tot);		
	
		for(int i = 1; i <= tot; i++)
			xiugai(1, i, i, max(abs(j - mi[i]), abs(j - ma[i])) + pos[i] - 1);
		b[1][j] = t[1].ma;
		if(pos[now] == 1) now++;
		
		for(int i = 2; i <= n; i++){
			xiugai(1, 1, now - 1, 1);
			xiugai(1, now, tot, -1);
			b[i][j] = t[1].ma;
			if(i == pos[now]) now++;
		}
	}
	
	
	ansx = ansy = 1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(b[i][j] < b[ansx][ansy]) ansx = i, ansy = j;
	cout << ansx << ' ' << ansy << '\n';
		
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> tt;
	while(tt--) solve();
	return 0;
}
```

---

