# [ABC384E] Takahashi is Slime 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_e

縦 $ H $ 行横 $ W $ 列のマス目があります。 上から $ i $ 行目 $ (1\leq\ i\leq\ H) $、左から $ j $ 列目 $ (1\leq\ j\leq\ W) $ のマスをマス $ (i,j) $ と呼ぶことにします。

はじめ、マス $ (i,j) $ には強さ $ S\ _\ {i,j} $ のスライムがおり、マス $ (P,Q) $ にいるスライムが高橋くんです。

高橋くんが以下の行動を好きな回数（$ 0 $ 回でもよい）行ったあとの、高橋くんの強さとしてありえる最大値を求めてください。

- 高橋くんに隣接するスライムのうち、強さが高橋くんの強さの $ \dfrac1X $ 倍**未満**のものを選んで吸収する。 その結果、吸収されたスライムは消滅し、高橋君の強さは吸収したスライムの強さだけ増加する。
 
上記の行動の際、スライムが吸収され消滅したことで生じた隙間は直ちに高橋くんによって埋められ、消滅したスライムに隣接していたスライム（それらが存在すれば）は新たに高橋くんと隣接します（入出力例１の説明も参照してください）。

## 说明/提示

### 制約

- $ 1\leq\ H,W\leq500 $
- $ 1\leq\ P\leq\ H $
- $ 1\leq\ Q\leq\ W $
- $ 1\leq\ X\leq10^9 $
- $ 1\leq\ S_{i,j}\leq10^{12} $
- 入力はすべて整数
 
### Sample Explanation 1

はじめ、それぞれのマスにいるスライムの強さは以下の図のようになっています。 
![](https://img.atcoder.jp/abc384/6b3d3bbde4767c7f5070ad0b1f202043.png) 例えば、高橋くんは次のように行動を行うことができます。 
![](https://img.atcoder.jp/abc384/81c0ccdba241277bf0cdd16ae6a7c54d.png) - マス $ (2,1) $ にいるスライムを吸収する。高橋くんの強さは $ 9+4=13 $ となり、新たにマス $ (1,1) $ のスライムとマス $ (3,1) $ のスライムが高橋くんと隣接する。 - マス $ (1,2) $ にいるスライムを吸収する。高橋くんの強さは $ 13+6=19 $ となり、新たにマス $ (1,3) $ のスライムが高橋くんと隣接する。 - マス $ (1,3) $ にいるスライムを吸収する。高橋くんの強さは $ 19+9=28 $ となる。 以上の行動を行ったあと、高橋くんの強さは $ 28 $ となります。 高橋くんがどのように行動を行っても、高橋くんの強さを $ 28 $ より大きくすることはできないため、`28` を出力してください。 高橋くんの強さの $ \dfrac12 $ 倍未満のスライムしか吸収できないことに注意してください。 例えば、上図の右側の状態からマス $ (1,1) $ にいるスライムを吸収することはできません。

### Sample Explanation 2

高橋くんはどのスライムも吸収できません。

## 样例 #1

### 输入

```
3 3 2
2 2
14 6 9
4 9 20
17 15 7```

### 输出

```
28```

## 样例 #2

### 输入

```
3 4 1
1 1
5 10 1 1
10 1 1 1
1 1 1 1```

### 输出

```
5```

## 样例 #3

### 输入

```
8 10 2
1 5
388 130 971 202 487 924 247 286 237 316
117 166 918 106 336 928 493 391 235 398
124 280 425 955 212 988 227 222 307 226
336 302 478 246 950 368 291 236 170 101
370 200 204 141 287 410 388 314 205 460
291 104 348 337 404 399 416 263 415 339
105 420 302 334 231 481 466 366 401 452
119 432 292 403 371 417 351 231 482 184```

### 输出

```
1343```

# 题解

## 作者：ikunTLE (赞：11)

[题面传送门](https://www.luogu.com.cn/problem/AT_abc384_e)

### 思路

不难想到以 $(P,Q)$ 为起点 bfs，然后将每个点都枚举一遍能不能到达。然后这种做法在最差情况下可能每次会把每个点都枚举一遍，时间复杂度为 $\mathcal{O}(H^2W^2)$。

考虑**贪心**策略，每一次寻找该图形相邻点中强度最小的点进行吸收。因为如果该图形无法吸收这个点，那么它也不能吸收强度更大的点。

这种策略可以用**优先队列**实现，每次取最小的点判断是否可以被吸收。如果可以吸收，那么这个点周围的点放入队列中，并增加图形的强度；否则其他点也无法吸收，直接输出答案并结束程序。

这种做法的时间复杂度是 $\mathcal{O}(HW\log HW)$。

**注意事项**

- 设图形强度为 $C$，在计算 $S_{i,j}<\frac{C}{X}$ 时为了控制精度，需要把不等式变为 $S_{i,j}\times X<C$，然而 $S_{i,j}\times X$ 炸了 `long long`，需要在这一步开 `__int128`。 

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int __int128
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void unsigned_write(int x){if(x>9)unsigned_write(x/10);putchar(x%10+'0');return;}
const int N=505;
int s[N][N],dx[]={0,-1,1,0,0},dy[]={0,0,0,-1,1};
bool vis[N][N];
struct node{
	int x,y,num;
	friend bool operator>(const node cmp_x,const node cmp_y){
		return cmp_x.num>cmp_y.num;
	}
};priority_queue<node,vector<node>,greater<node>>pq;
signed main(){
	int n=read(),m=read(),x=read(),p=read(),q=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			s[i][j]=read();
	vis[p][q]=true;
	int power=s[p][q];
	for(int i=1;i<=4;++i){
		int xx=p+dx[i],yy=q+dy[i];
		if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&!vis[xx][yy]){
			vis[xx][yy]=true;
			pq.push({xx,yy,s[xx][yy]});
		}
	}
	while(!pq.empty()){
		node u=pq.top();pq.pop();
		if(u.num*x>=power)
			return unsigned_write(power),0;
		power+=u.num;
		for(int i=1;i<=4;++i){
			int xx=u.x+dx[i],yy=u.y+dy[i];
			if(xx>=1&&xx<=n&&yy>=1&&yy<=m&&!vis[xx][yy]){
				vis[xx][yy]=true;
				pq.push({xx,yy,s[xx][yy]});
			}
		}
	}
	unsigned_write(power);
	return 0;
}
```

---

## 作者：Moya_Rao (赞：8)

# 题目大意
给定一张 $H \times W$ 的网格图，其中第 $i$ 行第 $j$ 列上的格子里有一个力量值为 $S_{i,j}$ 的人。高桥也在这个网格图中，他的位置是第 $p$ 行第 $q$ 列。

高桥需要寻找帮手，如果高桥当前的力量值严格大于他相邻格子上人的力量值的 $X$ 倍，那么他可以将这个人收为帮手，并占据他所在的地方，力量值也会增加这个人的力量值。

现在高桥想知道，他通过寻找帮手从而获得的最大力量值。

# 思路和代码
赛时好不容易干掉 D，打开题瞅了一眼。  
啊，这不是一眼 BFS 吗？简简单单。

是啊，多简单的 BFS，弄个变量 $now$ 记录当前力量值，然后用 BFS 来不断寻找帮手即可。

那么就有了这么一份错误百出的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int x,y;};
int n,m,aa,bb;
long long p,s[505][505],now;
bool flag[505][505];
queue<node> q;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int main(){
    cin>>n>>m>>p>>aa>>bb;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)cin>>s[i][j];
    now=s[aa][bb],flag[aa][bb]=1;
    q.push({aa,bb});
    while(!q.empty()){
        node t=q.front();q.pop();
        for(int i=0;i<4;i++){
            int x2=t.x+dx[i],y2=t.y+dy[i];
            if(x2<1||x2>n||y2<1||y2>m)continue;
            if(flag[x2][y2])continue;
            if(s[x2][y2]*p>=now)continue;
            flag[x2][y2]=1;
            now+=s[x2][y2];
            q.push({x2,y2});
        }
    }
    cout<<now;
    return 0;
}
```

提交！咦？错了啊！怎么回事儿呀？

仔细一想，好像确实不行，万一这个人现在无法成为高桥的帮手，但是只要再收一个可以的帮手增加完力量值后，又可以收之前这个人了呢？但按照现在这种做法，有可能之前这个人就收不到了呀。

那怎么办？  
优先队列 BFS 驾到！

是的，用一个优先队列就可以了，再改变一下思路，把即将考虑被收的人扔进队列，在取出队头的时候看看能不能把这个人收为帮手就行了。

编起来很简单，代码长这样：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int x,y;};
int n,m,aa,bb;
long long p,s[505][505],now;
bool flag[505][505];
priority_queue<node> q;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
bool operator < (const node &A, const node &B){
    return s[A.x][A.y]>s[B.x][B.y];
}
int main(){
    cin>>n>>m>>p>>aa>>bb;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)cin>>s[i][j];
    now=s[aa][bb],flag[aa][bb]=1;
    for(int i=0;i<4;i++){
        int x2=aa+dx[i],y2=bb+dy[i];
        if(x2<1||x2>n||y2<1||y2>m)continue;
        q.push({aa+dx[i],bb+dy[i]});
    }
    while(!q.empty()){
        node t=q.top();q.pop();
        if(s[t.x][t.y]*p<now&&!flag[t.x][t.y]){
            flag[t.x][t.y]=1;
            now+=s[t.x][t.y];
        }
        else continue;
        for(int i=0;i<4;i++){
            int x2=t.x+dx[i],y2=t.y+dy[i];
            if(x2<1||x2>n||y2<1||y2>m)continue;
            if(flag[x2][y2])continue;
            q.push({x2,y2});
        }
    }
    cout<<now;
    return 0;
}
```

交上去，怎么还是错的？不理解了呀。

无意间看到数据范围。  
等等，好像有句话是会爆 `long long` 的！

你发现了么？  
对，就是这句 `s[t.x][t.y]*p<now`。

注意到代码里 $s$ 的最大值是 $10^{12}$，而代码里 $p$ 的最大值是 $10^9$，把它们相乘的话，就会变成 $10^{21}$！完蛋，这不是爆 `long long` 了吗？

哎，这该怎么解决？没事，乘法改除法，加个向上取整，完美搞定！那么现在，代码被简单修改后长这样儿了：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int x,y;};
int n,m,aa,bb;
long long p,s[505][505],now;
bool flag[505][505];
priority_queue<node> q;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
bool operator < (const node &A, const node &B){
    return s[A.x][A.y]>s[B.x][B.y];
}
int main(){
    cin>>n>>m>>p>>aa>>bb;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)cin>>s[i][j];
    now=s[aa][bb],flag[aa][bb]=1;
    for(int i=0;i<4;i++){
        int x2=aa+dx[i],y2=bb+dy[i];
        if(x2<1||x2>n||y2<1||y2>m)continue;
        q.push({aa+dx[i],bb+dy[i]});
    }
    while(!q.empty()){
        node t=q.top();q.pop();
        if(s[t.x][t.y]<(now+p-1)/p&&!flag[t.x][t.y]){
            flag[t.x][t.y]=1;
            now+=s[t.x][t.y];
        }
        else continue;
        for(int i=0;i<4;i++){
            int x2=t.x+dx[i],y2=t.y+dy[i];
            if(x2<1||x2>n||y2<1||y2>m)continue;
            if(flag[x2][y2])continue;
            q.push({x2,y2});
        }
    }
    cout<<now;
    return 0;
}
```

交上去。心里很焦急。

终于过啦！太棒咯！

# 后记
各位读者若有不理解的地方可以私信我，我会尽量及时解答！

希望本篇题解对你有帮助！

也希望你留下一个小小的赞，多谢啦！

最后告诉大家，我吃了三发罚时才过掉此题哦。菜吧？

---

## 作者：Walrus (赞：4)

## 做法

第一眼这不是 bfs 板子吗？第二眼发现有个贪心，发现如果从一个点能够到达多的点，那么一定**先走格子上的数字最小的格子最优**。

不难证明先走小的就可以尽可能的多积累能量以到达更多的格子。

考虑 bfs 的过程是用 `queue` 实现的，那么考虑改成 `priority_queue` 就可以了。

为什么这么多人会去骂呢？

注意有个细节题目说是严格小于当前能量的 $\dfrac{1}{X}$ 倍，如果 $\dfrac{res}{X}$ 是整数的话那么能走的条件是 $S<\lfloor\dfrac{res}{X}\rfloor$，否则就是 $S\leq\lfloor\dfrac{res}{X}\rfloor$。

code

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define pre(i, j, k) for(int i = j; i >= k; --i)
#define lowbit(i) (i & -i)
#define inf 0x3fffffff
#define int long long
#define pb push_back
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;
const int N = 2e3 + 5;
const int M = 5e4 + 5;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

int n, m, s, t, k, res, a[N][N], vis[N][N];
struct node {
	int p, x, y;
	bool operator < (const node &a) const {return p > a.p;
	}
};
priority_queue<node> q;
bool check_edge(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m || vis[x][y]) return false;
	return true;
}

bool check_value(int x) {
	if(x > res / k || res % k == 0 && x == res / k) return false;
	return true;
	if(res % k == 0 && x < res / k || res % k != 0 && x <= res / k) return true;
	return false;
}

signed main() {
	FASTIO
	cin >> n >> m >> k >> s >> t; 
	rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
	vis[s][t] = 1, res = a[s][t];
	rep(i, 0, 3) {
		int x = s + dx[i], y = t + dy[i];
		if(!check_edge(x, y)) continue;
		q.push({a[x][y], x, y}); vis[x][y] = 1;
	}
	while(q.size()) {
		int p = q.top().p, x = q.top().x, y = q.top().y; q.pop();
		if(!check_value(p)) continue;
//		cout << x << ' ' << y << '\n';
		res += a[x][y];
		rep(i, 0, 3) {
			int xx = x + dx[i], yy = y + dy[i];
			if(!check_edge(xx, yy)) continue;
			q.push({a[xx][yy], xx, yy});
			vis[xx][yy] = 1;
		}
	}
	cout << res;
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：2)

纪念第一次做出五题。

有一个明显的贪心：优先吞并力量小的粘液肯定是不劣的。

简单的证明：假使现在与高桥相邻的力量最小的粘液为 $k$。

- 若 $k$ 不可以被合并，则力量更大的粘液也不能被合并，先尝试合并哪个没有区别。

- 若 $k$ 可以被合并，则力量更大且一开始不能被合并的粘液在高桥的力量增大以后有可能可以被合并，一定不劣。

因此可以维护一个优先队列做 BFS，同时维护一个 $ans$ 来记录高桥的实时力量。先把高桥周围的四个格子扔进优先队列里，然后对于每一个点，判断他是否能被高桥吞并，如果可以，标记其为已访问、更新 $ans$ 并向与该点相邻的点扩展。

[code](https://atcoder.jp/contests/abc384/submissions/60747694)

---

## 作者：xyx404 (赞：2)

## 思路：
从一个点出发前往其它点，要求必须到达点的强度严格小于我们的强度的 $\dfrac{1}{X}$ 倍，每次都可以从我们走过的地方形成的多边形的边上向没有到过的地方。

考虑 bfs。

与 bfs 模版不同的地方就在于每次都可以从我们走过的地方形成的多边形的边上向没有到过的地方，由此可以使用堆进行处理，每次把在边的旁边的点放进堆，每次取力量最小的点走。  
如果这时要走到点的强度已经不严格小于现在的强度的 $\dfrac{1}{X}$ 倍了，那么可以直接输出现在的值，然后结束程序。  
可以这样的原因是我们采用了堆并且每次取的的最小强度，那么现在最小强度已经不严格小于现在的强度的 $\dfrac{1}{X}$ 倍了，后面的强度只会大于或等于最小强度，所以也会是相同的结果，所以可以直接结束。


## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int H,W,p,q,x;
LL s[510][510];
bool bj[510][510];
struct node{
	LL x,y,v;
	friend bool operator <(node x,node y){
		return x.v>y.v;
	}
};
LL now;
priority_queue<node>dl;
int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int main(){
	cin>>H>>W>>x>>p>>q;
	for(int i=1;i<=H;i++){
		for(int j=1;j<=W;j++){
			cin>>s[i][j];
		}
	}
	now=0;
	bj[p][q]=1;
	bool bjj=0;
	dl.push({p,q,s[p][q]});
	while(dl.empty()==0){
		node tamp=dl.top();dl.pop();
//		cout<<tamp.x<<" "<<tamp.y<<"\n";
		if(bjj&&1.00000*now/x<=tamp.v)break;
		now+=tamp.v;
		bjj=1;
		for(int i=0;i<4;i++){
			int tx=dx[i]+tamp.x,ty=dy[i]+tamp.y;
			if(tx>=1&&ty>=1&&tx<=H&&ty<=W&&!bj[tx][ty]){
				bj[tx][ty]=1;
				dl.push({tx,ty,s[tx][ty]});
			}
		}
	}
	
	cout<<now;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc384/submissions/60771485)。

---

## 作者：zhouzihang1 (赞：1)

# AT_abc384_e [ABC384E] Takahashi is Slime 2 题解

## 思路

比较显然的一个结论：在所有可以走的点中，一定先走点权最小的点，如果点权最小的点不能走，说明不能继续走了。

所以可以使用 bfs，队列使用小根堆找权值最小的点。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=505;
int n,m,X,sx,sy;
ll a[N][N];
bool vis[N][N];
struct node{
	int first,second;
	ll num;
};
bool operator>(const node &x,const node &y){return x.num>y.num;}
bool check(int x,int y){return x>=1&&x<=n&&y>=1&&y<=m;}
int main()
{
	scanf("%d%d%d%d%d",&n,&m,&X,&sx,&sy);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lld",&a[i][j]);
	ll ans=0;
	priority_queue<node,vector<node>,greater<node> > q;
	q.push({sx,sy,a[sx][sy]});
	int dx[]={0,0,1,-1};
	int dy[]={1,-1,0,0};
	while(q.size())
	{
		int x,y;
		ll num;
		x=q.top().first;
		y=q.top().second;
		num=q.top().num;
		q.pop();
		__int128 k1=num,k2=X,k3=ans;
        //10^9 * 10^12 > LONG_LONG_MAX
		if(!(x==sx&&y==sy)&&k1*k2>=k3) break;
		if(vis[x][y]) continue;
		ans+=num;
		vis[x][y]=1;
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i],yy=y+dy[i];
			if(vis[xx][yy]) continue;
			if(check(xx,yy))
				q.push({xx,yy,a[xx][yy]});
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：sjh0626 (赞：1)

## 题意概括
高桥变成了一只史莱姆，他在网格中的 $(P,Q)$ 位置，他可以吸收他周围强度严格小于他的强度的 $\displaystyle\frac{1}{X}$ 的史莱姆，请你求出他的最大强度。
## 思路分析
一道优先队列与 BFS 好题。

我们要知道一个事实：高桥一定要优先吸收他周围强度最小的史莱姆，如果不能吸收，那他就其他的都无法吸收。

对于是否可以吸收，有两种方法，把当前要吸收的史莱姆的强度当作 $k$，高桥的强度为 $S$：

- 当 $k \times X < S$ 时，可以吸收。
- 当 $k < \displaystyle\frac{S}{X}$ 时，可以吸收。

第一种因为数据范围，会爆 `long long`，所以我们用第二种，接下来就是代码了。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ull unsigned long long
using namespace std;
int h,w,x,y,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0},nx,ny;
bool vis[1010][1010];
ull X,s[1010][1010],ans;
int main(){
	cin>>h>>w>>X>>x>>y;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>s[i][j];
		}
	}
	priority_queue<tuple<ull,int,int>,
			vector<tuple<ull,int,int>>,
			greater<>>q;
	vis[x][y]=1;
	ans=s[x][y];
	q.push({0,x,y});
	while(!q.empty()){
		auto [ss,sx,sy] =q.top();
		q.pop();
		if(ss>=(ans+X-1)/X)break; 
		ans+=ss;
		for(int i=0;i<4;i++){
			nx=sx+dx[i],ny=sy+dy[i];
			if(vis[nx][ny]||nx<1||nx>h||ny<1||ny>w)continue;
			vis[nx][ny]=1;
			q.push({s[nx][ny],nx,ny});
		}
	} 
	cout<<ans;
	sjh0626s code;
}
```

---

## 作者：__O_v_O__ (赞：1)

考虑使用优先队列维护和高桥相邻（可能被吃）的所有点。

每次，我们贪心地取出当前队列中大小最小的点，如果当前高桥不足以吃掉它，则以后不可能再增长，退出循环。

否则，高桥吃掉它，大小增加，然后把与这个新加点相邻的所有点加入队列（必须不在队列且没被吃）。

重复以上过程，直到队列为空或跳出循环，此时高桥的大小就是最终答案。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const __int128 G=1;
int h,w,X,p,q,s[501][501],no,f[501][501];
struct A{
	int x,y,nu;
	bool operator<(const A p)const{
		return nu>p.nu;
	}
};
priority_queue<A>qu;
int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
signed main(){
	ios::sync_with_stdio(0);
	cin>>h>>w>>X>>p>>q;
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			cin>>s[i][j];
		}
	}
	for(int i=0;i<4;i++){
		int tx=p+dx[i],ty=q+dy[i];
		if(tx<1||ty<1||tx>h||ty>w)continue;
		qu.push((A){tx,ty,s[tx][ty]});
	}
	f[p][q]=1,no=s[p][q];
	while(!qu.empty()){
		A tp=qu.top();
		qu.pop();
		int x=tp.x,y=tp.y,nu=tp.nu;
		if(f[x][y])continue;
		f[x][y]=1;
		if(G*nu*X>=G*no)break;//__int128,否则会爆long long
		no+=nu;
		for(int i=0;i<4;i++){
			int tx=x+dx[i],ty=y+dy[i];
			if(tx<1||ty<1||tx>h||ty>w||f[tx][ty])continue;
			qu.push((A){tx,ty,s[tx][ty]});
		}
	}
	cout<<no;
	return 0;
}
```

---

## 作者：__PJL__ (赞：0)

### 题意

给你一个 $n \times m$ 的矩阵，矩阵中第 $i$ 行第 $j$ 列的值为 $a_{i, j}$，你现在拥有一个格子为 $(sx, sy)$，每次行动可以将一个方格 $(x, y)$ 变成你自己的，但是得满足三个条件，在此之前你没有拥有过 $(x, y)$，$(x, y)$ 得与你的至少一个格子相邻，你所有拥有的格子数值的总和的 $\frac{1}{x}$ 倍严格大于 $a_{x, y}$，你可以进行任意次操作，问你可以获得的最大数值。

### 思路

首先，我们可以每次选择一个与你相邻的格子中数值的最小值，因为你先吸收小的，不会影响你现在可以吸收的较大的格子。所以我们直接使用一个优先队列来维护当前能够吸收的所有格子坐标，每次取出队头并且判断这个元素是否可以被吸收，如果能被吸收就将你的数值增加，并往四个方向查找在此之前不能被吸收的格子，将其标记并加入队列。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1000 + 1;

long long n, m, demage, second_chance, nowx, nowy, petal[MAXN][MAXN];
bool mobs[MAXN][MAXN];
struct cmp {
	bool operator()(pair<int, int> a, pair<int, int> b) {
		return petal[a.first][a.second] > petal[b.first][b.second];
	}
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> mob;
int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
void find_mob(int x, int y) {
	for(int i = 0; i < 4; i++) {            //枚举四个方向
		int newx = dx[i] + x, newy = dy[i] + y;
		if(newx >= 1 && newx <= n && newy >= 1 && newy <= m && mobs[newx][newy] == false) {  //如果在此之前没有标记并且没有出界
			mob.push({newx, newy});          //加入队列
			mobs[newx][newy] = true;         //标记已经加入过了
		}
	}
}

signed main() {
	cin >> n >> m >> second_chance;
	cin >> nowx >> nowy;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> petal[i][j];
		}
	} 
	mobs[nowx][nowy] = true;
	demage = petal[nowx][nowy];
	find_mob(nowx, nowy);
	while(!mob.empty()) {
		pair<int, int> now = mob.top();  //取出队头
		mob.pop();
		if(petal[now.first][now.second] < ceil(demage * 1.0 / second_chance)) {     //如果可以吸收当前格子
			demage += petal[now.first][now.second];  //将你的格子的数值总和增加
			find_mob(now.first, now.second);     //查找被吸收格子的相邻四个格子
		}
		else { 
			break;          //如果你当前连最小的值都无法吸收，那么就直接退出
		}
	}
	cout << demage;
	return 0;
}
```

---

## 作者：Happy_mouse (赞：0)

用一种类似 `BFS` 的做法并加以贪心。

易发现只要接触，不管过了多久都可以“吃掉”它。因此先吃小的来“蓄力”，值变大了再开始吃其它的。如果连已接触最小的都吃不了，那么还谈什么大的？

因此做一个小根堆，存已接触的方块的值与位置，每次取堆顶来判断或吃掉。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls u*2
#define rs u*2+1
#define fi first
#define se second
const int N=5e2+5;
int a[N][N];
bool v[N][N];
int n,m,k,p,q;
int cg[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
priority_queue<pair<int,pair<int,int>>>pq;
bool check(int x,int y){
    return x>0&&x<=n&&y>0&&y<=m;
}//判断合法性函数
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k>>p>>q;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) cin>>a[i][j]; 
	}//输入
	int sum=a[p][q];//当前的值
	v[p][q]=1;
	for(int i=0;i<4;i++){
		int nx=p+cg[i][0],ny=q+cg[i][1];
		if(check(nx,ny)) v[nx][ny]=1,pq.push({-a[nx][ny],{nx,ny}});
	}//先把第一波放进去
	while(pq.size()){//开始 BFS
		int x=pq.top().se.fi,y=pq.top().se.se;//坐标
		pq.pop();
		if(a[x][y]>=1.0*sum/k){
			cout<<sum;
			return 0;
		}//判断并输出
		v[x][y]=1;//标记
		sum+=a[x][y];//累加
		for(int i=0;i<4;i++){
			int nx=x+cg[i][0],ny=y+cg[i][1];
			if(check(nx,ny)&&!v[nx][ny]) v[nx][ny]=1,pq.push({-a[nx][ny],{nx,ny}});
		}//新接触到的放入堆
	}
	cout<<sum;//这里也要输一下，防止有能全部吃完的情况
	return 0;
}
```

---

