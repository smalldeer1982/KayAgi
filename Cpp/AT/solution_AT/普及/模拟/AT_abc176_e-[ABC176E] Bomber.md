# [ABC176E] Bomber

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc176/tasks/abc176_e

$ H\ \times\ W $ マスの二次元グリッドがあります。この中には $ M $ 個の爆破対象があります。 $ i $ 個目の爆破対象の位置は $ \left(h_i,\ w_i\ \right) $です。

高橋君は $ 1 $ つのマスを選び、そのマスに爆弾を設置し、起爆します。爆弾と同じ行または同じ列に存在する爆破対象が爆破されます。爆破対象が存在するマスに爆弾を設置することも出来ます。

高橋君は、爆破する爆破対象の数を最大化しようとしています。最大でいくつの爆破対象を爆破出来るか答えてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \leq\ H,\ W\ \leq\ 3\ \times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min\left(H\times\ W,\ 3\ \times\ 10^5\right) $
- $ 1\ \leq\ h_i\ \leq\ H $
- $ 1\ \leq\ w_i\ \leq\ W $
- $ \left(h_i,\ w_i\right)\ \neq\ \left(h_j,\ w_j\right)\ \left(i\ \neq\ j\right) $

### Sample Explanation 1

爆弾を $ \left(1,\ 2\right) $ に設置することで、全ての爆破対象を爆破することが出来ます。

## 样例 #1

### 输入

```
2 3 3
2 2
1 1
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3 4
3 3
3 1
1 1
1 2```

### 输出

```
3```

## 样例 #3

### 输入

```
5 5 10
2 5
4 3
2 3
5 5
2 2
5 4
5 3
5 1
3 5
1 4```

### 输出

```
6```

# 题解

## 作者：chl090410 (赞：8)

## The Solution to [ABC176E] Bomber

### 题目大意

有一个 $H\times W$ 的二维矩阵，其中有 $M$ 个目标。第 $i$ 个目标的位置是 $(h_i,w_i)$。有一个炸弹，可以选定一个位置投放炸弹，与炸弹位于同一行或同一列中的爆炸目标将被炸毁。求最多能摧毁多少个目标。

### 分析

我们可以用两个数组分别统计每行的目标数及每列的目标数。若想摧毁最多的目标，则选定的位置必须满足该位置所在的行是所有行中目标最多的，所在的列是所有列中目标最多的。

若仅仅像刚才那样思考，能摧毁的目标数就为两个数组中最大值之和。但选定的位置也可能有一个目标。在统计摧毁的目标数时，该目标被算了两次。所以要将该目标被多算的那一次减掉。由于目标最多的行和列可能不止一个，可供备选的位置也不止一个。在这些位置中，若有任何一个位置没有目标，答案就为两个数组中最大值之和，否则答案为两个数组中最大值之和减 $1$。

### Accode 如下：

```
#include<bits/stdc++.h>
using namespace std;
int h[300005],l[300005],a,b,c,kkk,sc03,mx,u=1,my,hm[300005],lm[300005],mh,ml;
map<pair<int,int>,int> m;
int main(){
	cin>>a>>b>>c;
	for(int i=1;i<=c;i++){
		cin>>kkk>>sc03;
		m[make_pair(kkk,sc03)]=1;
		h[kkk]++;l[sc03]++;
	}
	for(int i=1;i<=a;i++){
		mx=max(mx,h[i]);
	}
	for(int i=1;i<=b;i++){
		my=max(my,l[i]);
	}
	for(int i=1;i<=a;i++){
		if(h[i]==mx){
			hm[++mh]=i;
		}
	}
	for(int i=1;i<=b;i++){
		if(l[i]==my){
			lm[++ml]=i;
		}
	}
	for(int i=1;i<=mh;i++){
		for(int j=1;j<=ml;j++){
			if(m[make_pair(hm[i],lm[j])]!=1){
				u=0;break;
			}
		}
	}
	cout<<mx+my-u;
	return 0;
}


---

## 作者：whrwlx (赞：4)

# 分析

我们可以用 hf 和 wf 分别储存每行的目标数及每列的目标数。

然后我们可以**贪心**：

若想摧毁最多的目标，则选定的位置所在的行是所有行中目标最多的，所在的列是所有列中目标最多的。

但是，选定的位置也可能有一个目标。在统计摧毁的目标数时，该目标被算了两次。所以要将该目标被多算的那次减掉。

所以我们可以枚举每个满足条件的位置，然后看是否有一个位置上没有炸弹。

那么代码如下：

```c++
#include<bits/stdc++.h>
#define int long long
#define fd(i,a,b) for(int i=a;i<=b;i=-~i)
using namespace std;
int h,w,m,hf[300100],wf[300100];
int ans=1,hi,wi,maxh,maxw,cnth,cntw;
int sumh[300100],sumw[300100];
unordered_map < int,unordered_map<int,int> > mp;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>h>>w>>m;
	fd(i,1,m)
	{
		cin>>hi>>wi;
		hf[hi]++;wf[wi]++;
		maxh=max(hf[hi],maxh);
		maxw=max(wf[wi],maxw);
		mp[hi][wi]++;
	}
	fd(i,1,h)
	{
		if(hf[i]==maxh) sumh[++cnth]=i;
	}
	fd(i,1,w)
	{
		if(wf[i]==maxw) sumw[++cntw]=i;
	}
	fd(i,1,cnth)
	{
		fd(j,1,cntw)
		{
			if(!mp[sumh[i]][sumw[j]])
			{
				ans=0;
				break;
			}
		}
	}
	cout<<maxh+maxw-ans;
	return 0;
}
```

---

## 作者：PineappleSummer (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc176_e)

简单统计题。

用 $cnt1_i$ 统计第 $i$ 行的目标数，$cnt2_i$ 统计第 $i$ 列的目标数，$max_x$ 表示 $cnt1_i$ 中的最大值，$max_y$ 表示 $cnt2_i$ 中的最大值，$mp_{i,j}$ 为 $1$ 表示坐标 $(i,j)$ 有目标。

在输入时统计出上述变量的值：
```cpp
for(int i=1;i<=m;i++)
{
	cin>>a[i]>>b[i];
	mp[a[i]][b[i]]=1;
	cnt1[a[i]]++,cnt2[b[i]]++;
	max_x=max(max_x,cnt1[a[i]]);
	max_y=max(max_y,cnt2[b[i]]);
}
```

然后我们想，如果要使摧毁的目标更多，肯定要使炸弹所在的行和列中的目标数最大，行和列中目标数的最大值就是 $max_x$ 和 $max_y$。把所有行和列中目标数为最大值的行和列存入 $v1$ 和 $v2$ 中。$v1$ 中存行中目标数为 $max_x$ 的行的编号，$v2$ 中存列中目标数为 $max_y$ 的列的编号。

```cpp
for(int i=1;i<=m;i++)
{
	if(cnt1[a[i]]==max_x&&!vis1[a[i]]) v1.push_back(a[i]),vis1[a[i]]=1;
	if(cnt2[b[i]]==max_y&&!vis2[b[i]]) v2.push_back(b[i]),vis2[b[i]]=1;
}
```

然后双重循环枚举 $v1$ 与 $v2$，如果 $v1_i$ 与 $v2_j$ 相交的位置没有目标，答案即为 $max_x+max_y$，否则答案为 $max_x+max_y-1$（减去 $(v1_i,v2_j)$ 位置多算的一个目标）。

```cpp
for(auto i:v1)//为了简便，使用了 auto
	for(auto j:v2)
		if(!mp[i][j])
			cout<<max_x+max_y,exit(0);//exit(0)就是结束程序
cout<<max_x+max_y-1;
```

[完整代码](https://atcoder.jp/contests/abc176/submissions/44341582)，时间复杂度 $\mathcal{O}(n)$。

---
有同学可能会问：最后有一个双重循环，为什么时间复杂度为 $\mathcal{O}(n)$ 呢，原因是**最多循环 $m$ 次就会结束程序**。

我们可以构造一组数据，$h$ 为 $1\times 10^2$，$w$ 为 $3\times 10^3$，**每个坐标都有目标**，目标数为 $3\times 10^5$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lrncxjt6.png)

这时候 $v1$ 的长度为 $1\times 10^2$，$v2$ 的长度为 $3\times 10^3$，实际循环次数为 $1\times 10^2\times 3\times 10^3=3\times 10^5$ 次，为 $m$ 的值。

我们可以再构造一组数据，$h$ 为 $3\times 10^5$，$w$ 为 $3\times 10^5$，**目标在对角线上**，目标数为 $3\times 10^5$。如下图（红色为目标点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/iorqew5t.png)
看似各种数据都已拉满，但仍不会超时，你会发现当 $i=1,j=2$ 时就会结束程序，因为坐标 $(1,2)$ 并没有目标。

我们可以通过构造数据来说明时间复杂度为 $\mathcal{O}(n)$。哪位大佬能给出更加严谨的证明，欢迎在评论区提供。

----
update on 2023-09-30：感谢@[FL_sleake](https://www.luogu.com.cn/user/368791)大佬的证明。

证明：当一个位置没有爆破对象时，整个程序就会结束。循环继续的条件为当前位置是爆破对象。由于总共有 $n$ 个爆破对象，在最坏情况下只能使循环进行 $n$ 次，$n+1$ 次必定扫描到非爆破对象点或退出循环。

---

## 作者：Andy_WA (赞：2)

## 题目大意
在一个 $w$ 和 $h$ 的矩阵中，有 $n$ 个点有目标，我们需要放置炸弹，与炸弹同行同列的目标将会被炸毁，当我们仅放置 $1$ 个炸弹时，最多可以炸毁多少个目标。

## 题目分析
+ 看见数据范围就知道 $O(n^2)$ 包过不了的。
+ 所以，贪心：\
  先求出每行最多的目标与每列最多的目标，由于炸弹投放的位置可能也有目标\
  但当然会被**重复计算**，所以最后要遍历所有有最多目标的行与列。


```cpp
#include<bits/stdc++.h>
using namespace std;
/*Optimization series
#pragma GCC/G++ optimize(1)
#pragma GCC/G++ optimize(2)
#pragma GCC/G++ optimize(3,"OSumast","inline")
*/
const long long MaxN=3e5+5;
long long H,W,M,ans;
long long h[MaxN],m[MaxN];
long long ht[MaxN],wt[MaxN];
long long Max_h,Max_w;
long long Cnt_h,Cnt_w;
bool flag;
map<long long,long long> Vis[MaxN];
int main(){
	cin>>H>>M>>W;
	for(long long i=1;i<=W;i++){
		long long x,y;
		cin>>x>>y;
		h[x]++;
		m[y]++;
		Vis[x][y]=1;
	}
	for(long long i=1;i<=H;i++){
		Max_h=max(Max_h,h[i]);
	} 
	for(long long i=1;i<=H;i++){
		if(h[i]==Max_h){ 
			ht[++Cnt_h]=i;
		}
	} 
	for(long long i=1;i<=M;i++){
		Max_w=max(Max_w,m[i]);
	} 
	for(long long i=1;i<=M;i++){
		if(m[i]==Max_w){
			wt[++Cnt_w]=i;
		}
	}
	long long ans=Max_h+Max_w;
	for(long long i=1;i<=Cnt_h;i++)
		for(long long j=1;j<=Cnt_w;j++)
			if(Vis[ht[i]][wt[j]]==0){
				flag=1;
				break;
			}
	if(flag==0) ans--;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ICE__LX (赞：2)

### 题意
可以这么想，在一个 $H \times W$ 的纸张上有 $M$ 个点，让你画一条横线和一条竖线，且两者垂直，求连接的最大点的数量。  
### 具体思路
可以采用贪心的思路，用两个桶分别记录第 $x$ 行、$y$ 列上有多少个点，然后选取点数最多的那一条，然后相加得出答案。特别的，若两点相交处有一个点，点的总数就要减一，因为重复记录了。当然，若存在多种情况，自然选择相交处没有点的方案。
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define in(a) a=read()
const int maxn=INT_MAX;
const double INF=DBL_MAX;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int dx[300005],dy[300005],n,m,t,maxx,maxy;
vector<int>nx,ny;
set<pair<int,int> >s;
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	in(n),in(m),in(t);
	rep(i,1,t) {
		int x,y;
		in(x),in(y);
		s.insert({x,y});//将点加入集合 
		dx[x]++;//第x行的点数增加 
		dy[y]++;//第y列的点数增加
	}
	rep(i,1,n)maxx=max(maxx,dx[i]);//找含点数量最多的一行 
	rep(i,1,m)maxy=max(maxy,dy[i]);//找含点数量最多的一列  
	rep(i,1,n)
	if(dx[i]==maxx)nx.push_back(i);//记录下来
	rep(i,1,m)
	if(dy[i]==maxy)ny.push_back(i);//记录下来
	for(auto x:nx)
		for(auto y:ny)
			if(s.find({x,y})==s.end()) {//判断是否存在两点相交处没有点的方案 
				cout<<maxx+maxy;
				return 0;
			}
	cout<<maxx+maxy-1;//若不存在，输出两点相交处有一个点的方案的解 
	return 0;
}
```

---

## 作者：lihe_qwq (赞：1)

要计算炸弹的最大杀伤，不妨开两个数组，$xx_{i}$ 存储第 $i$ 行的目标物的数量，$yy_{i}$ 存储第 $i$ 列的目标物数量,则最大值为：

$$
\operatorname{max}(xx_i+yy_j-mp_{i,j})
$$

设 $xx_{ansx}$ 为目标物最多的行的目标物数量，$yy_{ansy}$ 为目标物最多的列的目标数数量。则有：

$$
ans=\operatorname{max}(\operatorname{max}(xx_{ansx}+yy_i-mp_{ansx,i}),\operatorname{max}(xx_{i}+yy_{ansy}-mp_{i,ansy}))
$$

由于 $h$，$w$ 的范围很大所以要开 `map`。

然后这个题就可以愉快的 AC 了。

[详细代码](https://atcoder.jp/contests/abc176/submissions/51721701)

---

## 作者：Fkxxx (赞：1)

## 算法

如果要最大化【数据删除】伤力，如果我们选在 $(x,y)$，那么第 $x$ 行是目标最多的一行，第 $y$ 列是目标最多的一列。

我们考虑记录行最大目标量的和列最大目标，那么我们就可以得到答案为 $\max(x)+ \max(y)$。

这样就能写出下面的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m , k , a[300005] , b[300005] , numx[300005] , numy[300005] , maxx , maxy ;
signed main(){
    cin >> n >> m >> k ;
    for( int i = 1 ; i <= k ; i ++ ){
        cin >> a[i] >> b[i] ;
        numx[a[i]] ++ ;
        numy[b[i]] ++ ;
        maxx = max( maxx , numx[a[i]] ) ;
        maxy = max( maxy , numy[b[i]] ) ;
    }
    cout << maxx + maxy ;
    return 0 ;
}
```

可恶的是，我们发现这个代码是错误的，稍作思考发现，如果我们选择在 $(x,y)$，且 $(x,y)$ 有一个目标，那我们就会发现 $(x,y)$ 这个目标被多算了一次！

为了判断 $(x,y)$ 是否有目标，可用标记数组判断。常规的标记数组是会寄的，还好我们有 `STL MAP`。为了防止有多种最大的 $x$ 或 $y$，可用两个数组记录**每一个**最大的 $x$ 或 $y$，最后再拿这两个数组中的数两两判断，若 $(\max(x_i),\max(y_j))$ 没有目标，输出 $maxx\_num+maxy\_num$，如果没有任何一对 $(\max(x_i),\max(y_j))$ 没有目标，则输出 $\max(x)+\max(y)\color{red}{-1}$。

## Accode

```
#include<bits/stdc++.h>
using namespace std;
int n , m , k , a[300005] , b[300005] , numx[300005] , numy[300005] , maxx , maxy , tmpx[300005] , tmpy[300005] , mpx , mpy ;
map<pair<int,int>,int> mp ;
signed main(){
    cin >> n >> m >> k ;
    for( int i = 1 ; i <= k ; i ++ ){
        cin >> a[i] >> b[i] ;
        mp[make_pair(a[i],b[i])] = 1 ;
        numx[a[i]] ++ ;
        numy[b[i]] ++ ;
        if( numx[a[i]] > maxx ){
            mpx = 1 ;
            tmpx[1] = a[i] ;
            maxx = numx[a[i]] ;
        }
        else if( numx[a[i]] == maxx ){
            tmpx[++ mpx] = a[i] ;
        }
        if( numy[b[i]] > maxy ){
            mpy = 1 ;
            tmpy[1] = b[i] ;
            maxy = numy[b[i]] ;
        }
        else if( numy[b[i]] == maxy ){
            tmpy[++ mpy] = b[i] ;
        }
    }
    for( int i = 1 ; i <= mpx ; i ++ ){
        for( int j = 1 ; j <= mpy ; j ++ ){
            if( mp[make_pair(tmpx[i],tmpy[j])] != 1 ){
                cout << maxx + maxy ;
                return 0 ;
            }
        }
    }
    cout << maxx + maxy - 1 ;
    return 0 ;
}
```



---

## 作者：Dream_Stars (赞：0)

## 题目大意：
在一个 $w$ 和 $h$ 的矩阵中，有 $n$ 个点有目标，我们需要放置炸弹，与炸弹同行同列的目标将会被炸毁，当我们仅放置 $1$ 个炸弹时，最多可以炸毁多少个目标。
## 算法分析：
考虑贪心求解。\
这道题目我们可以求出最多目标的行，最多目标的列，在将其求和就可以得出最多目标的行和列了。

但是，万一最多目标的行和列的那个点是炸弹的话，最后的结果就需要减一了。这种情况需要特殊处理，需要一个标记数组。\
但是，这道题的数据量非常大，所以，标记数组是二维的，需要开 map 不然会......
## 代码展示：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 * 3 + 10;

int w,h,n;
int xx,yy;
int ansx,ansy,ans,cntx,cnty;
int x[N],y[N];
int numx[N],numy[N];

unordered_map <int , unordered_map<int , int> > vis;

int main(){

  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> h >> w >> n;
  for(int i = 1 ; i <= n ; i++){
  	cin >> xx >> yy;
  	x[xx]++;
  	y[yy]++;
		ansx = max(x[xx] , ansx);
		ansy = max(y[yy] , ansy);//找最大行和最大列
  	vis[xx][yy] = true;
  }
  for(int i = 1 ; i <= h ; i++)
	if(x[i] == ansx) cntx++ , sumx[cntx] = i;
  for(int i = 1 ; i <= w ; i++)
	if(y[i] == ansy) cnty++ , sumy[cnty] = i;
  for(int i = 1 ; i <= cntx ; i++)
  	for(int j = 1 ; j <= cnty ; j++)
	    if(vis[numx[i]][numy[j]] == false){
		  cout << ansx + ansy << endl;
		  return 0;//是否有目标
    }
  ans = ansx + ansy - 1;
  cout << ans << endl;
  return 0;
}
```

---

## 作者：2012_Zhang_ (赞：0)

#### 第一眼，贪心！简单！
#### 第二眼，没那么简单！
#### 步入正题。

## 贪心
首先考虑贪心。\
我们可以直接用两个数组存 $X$ 轴与 $Y$ 轴上的目标数，再取最大值相加，然后输出。\
但事情与我们想的并不一样。\
 $X$  轴与  $Y$  轴目标最多处会有交点。\
若交点处有目标，该目标会被算两次，导致答案多了 $1$。\
所以我们可以用 map 存位置。\
在符合要求(目标最多)的位置判断交点是否有目标，没有就直接相加，否则减 $1$。

奉上代码 ：
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
map<pair<int,int>,int>p;
long long h,w,m,x[1000000],y[1000000],M,MM;
long long xx[1000000],yy[1000000],t1,t2;
int main(){
    cin>>h>>w>>m;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        x[a]++,y[b]++;
        p[make_pair(a,b)]=1;\\存点
    }
    for(int i=1;i<=h;i++)M=max(M,x[i]);
    for(int i=1;i<=w;i++)MM=max(MM,y[i]);
    for(int i=1;i<=h;i++)
        if(x[i]==M) xx[++t1]=i;\\存符合要求的位置
    for(int i=1;i<=w;i++)
        if(y[i]==MM) yy[++t2]=i;
    for(int i=1;i<=t1;i++){
        for(int j=1;j<=t2;j++){
            if(p[make_pair(xx[i],yy[j])]==0){\\交点无目标
                cout<<M+MM;
                return 0;
            }
        }
    }
    cout<<M+MM-1;\\交点有目标
    return 0;
}

---

## 作者：GJX_Algorithm (赞：0)

# AT_abc176_e题解
## 题目描述
1. 给定一个 $H \times W$ 的二维矩阵，以及 $M$ 个目标，第 $i$ 个目标的位置是 $(h_i,w_i)$。
2. 现有一个炸弹，可以摧毁其所在行和所在列的目标。
3. 求最多摧毁的目标。

## 解题思路
1. 看见数据范围就知道 $O(n^2)$ 过不了。
2. 可以先求出每行最多的目标与每列最多的目标，由于炸弹投放的位置可能也有目标，会被重复计算，所以最后要遍历所有有最多目标的行与列

## 代码
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  const int N = 3e5 + 5;
  int h, m, w, ans;
  int h_target[N], m_target[N], ht[N], mt[N], hmax, mmax, cnt1, cnt2;
  bool flag;
  map<int, int> vis[N];
  int main()
  {
      cin >> h >> m >> w;
      for (int i = 1; i <= w; i++)
      {
          int x, y;
          cin >> x >> y;
          h_target[x]++, m_target[y]++;
          vis[x][y] = 1;
      }
      for (int i = 1; i <= h; i++)
          hmax = max(hmax, h_target[i]);
      for (int i = 1; i <= h; i++)
          if (h_target[i] == hmax)
              ht[++cnt1] = i;
      for (int i = 1; i <= m; i++)
          mmax = max(mmax, m_target[i]);
      for (int i = 1; i <= m; i++)
          if (m_target[i] == mmax)
              mt[++cnt2] = i;
      int ans = hmax + mmax;
      for (int i = 1; i <= cnt1; i++)
          for (int j = 1; j <= cnt2; j++)
              if (vis[ht[i]][mt[j]] == 0)
              {
                  flag = 1;
                  //cout << ht[i] << " " << mt[j] << "\n";
                  break;
              }
      if (flag == 0) ans--;
      cout << ans;
      return 0;
  }
  ```

---

## 作者：linjinkun (赞：0)

~~先说明一下，我的这篇题解代码以及思路都和前三篇差不多，但这里重点讲思路，因为大佬们讲得不太清晰（其实是我太逊了），所以我要发一篇清晰的题解（给萌新看的）。~~

进入正题

暴力？？

先看一下数据范围：

$ 1\ \leq\ H,\ W\ \leq\ 3\ \times\ 10^5 $

哦，不行，那该怎么办呢？假如我们选的坐标系是 $x,y$，那我们必须满足目标中行数是 $x$ 出现次数的值加目标中列数出现次数是 $y$ 的值是最大的，那很容易写。

但是我们会发现问题，如果行数出现次数最大值对应的行数和列竖出现次数最大值对应的列数是在同一个下标（也就是这个位置有目标），那这个答案就错了，那你可能会想了，是不是可以减去 $1$？不行，因为有可能你减少 $1$ 后会有其他的行数列数代替，那就得把行数出现次数最大值和列数出现次数最大值列出来，再暴力枚举，如果这个行数列数不是其中一个目标，就记录不减 $1$。

其中有一些细节会在代码中讲解。

代码：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int f1[N],f2[N],num1[N],num2[N];
int ans1,ans2;
int q = 1;//一开始q为1，代表要减少1
map<pair<int,int>,int>s;//s是统计一个坐标是否出现
int main()
{
	int n,m,w;
	scanf("%d %d %d",&n,&m,&w);
	for(int i = 1;i<=w;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		f1[x]++;//行数++
		f2[y]++;//列数++
		s[make_pair(x,y)] = 1;//记录有这个坐标
	}
	int maxx1 = 0;
	int maxx2 = 0;
	for(int i = 1;i<=n;i++)//注意是n（我可没忘我提交5次才过的惨状）
	{
		maxx1 = max(maxx1,f1[i]);
	}
	for(int i = 1;i<=m;i++)//这里是m！！
	{
		maxx2 = max(maxx2,f2[i]);
	}	
	for(int i = 1;i<=n;i++)
	{
		if(f1[i] == maxx1)
		{
			num1[++ans1] = i;//记录下所有行数出现次数最多最大值的行数
		}
	}
	for(int i = 1;i<=m;i++)
	{
		if(f2[i] == maxx2)
		{
			num2[++ans2] = i;//记录下所有列数出现次数最多的列数
		}
	}
	for(int i = 1;i<=ans1;i++)
	{
		for(int j = 1;j<=ans2;j++)
		{
			if(s.find(make_pair(num1[i],num2[j])) == s.end())//不存在（不是目标）
			{
				q = 0;//不能减少1
				break;
			}
		}
	}
	printf("%d",maxx1+maxx2-q);//要减少q
    return 0;
}

~~~
抱歉，我无法解释时间复杂度，请见谅……

---

