# [USACO24JAN] Walking in Manhattan G

## 题目描述

Farmer John 和他的 $Q$（$1\le Q\le 2\cdot 10^5$）头奶牛在曼哈顿度假，但奶牛们逃跑了，现在正在城市里自由走动！曼哈顿很大——大到它的 $N$（$1\le N\le 2\cdot 10^5$）条道路在 $x-y$ 平面上无限延伸，但简单的是，这些道路都完全水平或垂直。每条水平和垂直道路都可以用形式为 $y=c_i$ 或 $x=c_i$ 的方程表示，其中 $c_i$ 是 $0$ 到 $10^9$ 范围内的整数。

Farmer John 准确地知道每头奶牛从哪里开始行走，以及她们多久之前逃跑的。奶牛们很容易被预测，因此每头奶牛都是按照以下模式行走：

- 她们只会以每秒一个单位的速度向北（$+y$）或向东（$+x$    ）行走。
- 如果她们当前在一条道路上，她们会继续沿着道路的方向行走。
- 如果她们在两条道路的交叉口处，如果她们行走了偶数秒，则向北行走，否则向东行走。

给定曼哈顿的布局以及每头奶牛的信息，帮助 Farmer John 求出他的奶牛们现在在哪里！ 

## 说明/提示

### 样例解释 1

前两头奶牛经过的路径如下：

$(6, 3) \to (6, 4) \to (7, 4) \to (7, 5) \to (8, 5) \to \ldots \to (14, 5)$  
$(6, 4) \to (6, 5) \to (7, 5) \to (7, 6) \to \ldots \to (7, 13)$

### 测试点性质

- 测试点 $2-4$：$N,Q,c_i,x_i,y_i,d_i\le 100$。
- 测试点 $5-9$：$N,Q\le 3000$。
- 测试点 $10-20$：没有额外限制。

## 样例 #1

### 输入

```
4 5
V 7
H 4
H 5
V 6
6 3 10
6 4 10
6 5 10
6 6 10
100 4 10```

### 输出

```
14 5
7 13
6 15
6 16
110 4```

# 题解

## 作者：FFTotoro (赞：9)

[$\mathrm{\color{Black}B\color{Red}enq}$](https://codeforces.com/profile/Benq) 出的神奇倍增题。

对于这种细节很多的题，先把边界判掉。于是使用 `lower_bound` 把奶牛放到它第一个走到的交叉路口，再来考虑接下来的行走。

考虑奶牛的走法有什么规律或者性质。不妨设出发点 $(s_x,s_y)$ 满足 $(s_x+s_y)\bmod 2=0$；对于每条路，奶牛再它上面行走时会转向当且仅当遇到一条**方向不同**且**奇偶性不同**的路。由此可以确定的是，当奶牛再次走到与这条路方向相同的路时，**不需**考虑 $s_x+s_y$ 的奇偶性，下一条**同方向**的路的奇偶性一定与这条路**相反**。

于是这个东西可以**倍增**，类比 LCA 来理解，倍增的数组里面记的是“对于一条道路，令其‘父亲’为在它前面且与它奇偶性不同的第一条同方向道路，对于所有 $k$，这条路的 $2^k$ 级‘祖先’”；于是对于一个时间 $d$，就可以求出在 $d$ 秒内奶牛能走到的最远的交叉路口。

最后处理一下奶牛离开所有交叉路口后要走的路程即可。

时间复杂度 $O(n\log n)$。注意判断倍增的边界。

放代码：

```cpp
/*
ID: CrowMatrix
TASK: Walking in Manhattan
LANG: C++
*/
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,q; cin>>n>>q;
  vector<int> h,v;
  while(n--){
    char c; int x; cin>>c>>x;
    if(c=='H')h.emplace_back(x);
    else v.emplace_back(x);
  } // 存储所有道路
  sort(h.begin(),h.end());
  sort(v.begin(),v.end());
  h.emplace_back(2e9),v.emplace_back(2e9);
  vector r(h.size(),vector<int>(18)),
    c(v.size(),vector<int>(18)); // 倍增数组
  for(int i=0;i<18;i++){
    r[h.size()-1][i]=h.size()-1;
    c[v.size()-1][i]=v.size()-1;
  } // 倍增数组初始化
  for(int i=h.size()-2;~i;i--){
    r[i][0]=(h[i]+h[i+1]&1?i+1:r[i+1][0]);
    for(int j=1;j<18;j++)
      r[i][j]=r[r[i][j-1]][j-1];
  } // 对于横的道路处理 2^k 级祖先
  for(int i=v.size()-2;~i;i--){
    c[i][0]=(v[i]+v[i+1]&1?i+1:c[i+1][0]);
    for(int j=1;j<18;j++)
      c[i][j]=c[c[i][j-1]][j-1];
  } // 对于竖的道路处理 2^k 级祖先
  auto Q=[&](int x,int y,int d,int t=0){
    int h0=lower_bound(h.begin(),h.end(),y)-h.begin(),
      v0=lower_bound(v.begin(),v.end(),x)-v.begin();
    if(y<h[h0]){
      if(d+y<=h[h0])return make_pair(x,d+y);
      d-=h[h0]-y,t+=h[h0]-y;
    }
    if(x<v[v0]){
      if(d+x<=v[v0])return make_pair(x+d,y);
      d-=v[v0]-x,t+=v[v0]-x;
    } // 找到第一个交叉路口，记得判走不到的情况
    for(int k=17;~k;k--){
      int x=r[h0][k],y=c[v0][k];
      if(h[x]-h[h0]>d||v[y]-v[v0]>d)continue;
      if(v[y]-v[v0]+h[x]-h[h0]>d)continue;
      d-=v[y]-v[v0]+h[x]-h[h0],t+=v[y]-v[v0]+h[x]-h[h0];
      h0=x,v0=y;
    } // 倍增找走最远的点
    if(t&1){
      int a=c[v0][0];
      if(v[a]-v[v0]>=d)return make_pair(v[v0]+d,h[h0]);
      d-=v[a]-v[v0];
      return make_pair(v[a],h[h0]+d);
    }
    int a=r[h0][0];
    if(h[a]-h[h0]>=d)return make_pair(v[v0],h[h0]+d);
    d-=h[a]-h[h0];
    return make_pair(v[v0]+d,h[a]); // 最后一段
  };
  while(q--){
    int x,y,d; cin>>x>>y>>d;
    auto [a,b]=Q(x,y,d);
    cout<<a<<' '<<b<<'\n';
  } // 处理询问
  return 0;
}
```

---

## 作者：qwer6 (赞：2)

## Solution

我们可以先看看怎么模拟这个过程，将两种直线分别存入两个 set 中，然后每次找到下一个到达的路口，看看需不需要转弯即可。

这样的时间复杂度是 $O(qn\log n)$，可以拿到 $45$ 分的好成绩。

考虑优化，我们发现当一头奶牛到达了第一个需要转弯的路口之后，接下来它的路径就已经被确定了。

这个形式看上去就很倍增的样子，考虑如何倍增。

我们首先想一想从一个路口开始向北走是怎么走到，假设现在的 $y$ 等于 $y_0$，$x$ 等于 $x_0$，那么下一次转弯就要找到另一条 $y=y_1$，且 $y_1$ 和 $y_0$ 奇偶性不同，因为从上一个路口向北走就说明这个时候走过的时间是偶数，如果想要向东走，那么就要向北走奇数时间才能使总时间是奇数，在这个路口向东走，找到一条 $x=x_1$，且 $x_1$ 和 $x_0$ 的奇偶性不同，原因和上面相同，那么这个时候的 $x_1$ 就是比 $x_0$ 大且和 $x_0$ 奇偶性不同的最小的 $x$，换而言之，对于一个固定的 $x$，在转换两次方向之后，到达的 $x$ 是固定的。

同理可得，对于一个固定的 $y$，在转换两次方向，到达的 $y$ 也是固定的。

那么现在 $x$ 和 $y$ 就是无关的了，可以直接进行倍增，记录 $f_{i,j}$ 表示 $x=j$，一开始向北走，经过 $2^{i+1}$ 次转弯之后到达的 $x$，$g_{i,j}$ 表示 $y=j$，一开始向北走，经过 $2^{i+1}$ 次转弯之后到达的 $y$。

开始倍增之前，我们模拟这只奶牛的移动位置，走到第一个向北走的路口，然后开始倍增即可。

最后可能还能向北再转一次弯，然后向东走或者一直向北走才能走到最后到达的终点。

如果这只奶牛刚开始在一条竖直的路上，那么需要转两次弯，否则只需要转一次弯，并且注意，这里要找和 $x$ 奇偶性相同的 $x=c$ 的直线才可以向北走。

## Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int N=2e5+5,inf=0x3f3f3f3f;
int n,q,totx,toty;
int tmpx[N],tmpy[N],f[25][N],g[25][N];
set<int>st[2][2];
int cal(int sx,int sy,int tx,int ty){
	return tx+ty-sx-sy;
}
signed main(){
	read(n),read(q);
	for(int i=1,x,c;i<=n;i++){
		c=getchar();
		while(c!='H'&&c!='V')c=getchar();
		read(x);
		if(c=='H'){
			st[0][x&1].insert(x);
			tmpy[++toty]=x;
		}else{
			st[1][x&1].insert(x);
			tmpx[++totx]=x;
		}
	}
	sort(tmpy+1,tmpy+toty+1);
	sort(tmpx+1,tmpx+totx+1);
	for(int i=0,tmp;i<=totx;i++){
		tmp=(tmpx[i]+1)&1;
		auto it=st[1][tmp].lower_bound(tmpx[i]);
		if(it==st[1][tmp].end())f[0][i]=inf;
		else f[0][i]=lower_bound(tmpx+1,tmpx+totx+1,*it)-tmpx;
	}
	for(int i=1,tmp;i<toty;i++){
		tmp=(tmpy[i]+1)&1;
		auto it=st[0][tmp].lower_bound(tmpy[i]);
		if(it==st[0][tmp].end())g[0][i]=inf;
		else g[0][i]=lower_bound(tmpy+1,tmpy+toty+1,*it)-tmpy;
	}
	for(int j=1;j<=20;j++){
		for(int i=1;i<=totx;i++){
			if(f[j-1][i]>totx)f[j][i]=f[j-1][i];
			else f[j][i]=f[j-1][f[j-1][i]];
		}
	}
	for(int j=1;j<=20;j++){
		for(int i=1;i<=toty;i++){
			if(g[j-1][i]>toty)g[j][i]=g[j-1][i];
			else g[j][i]=g[j-1][g[j-1][i]];
		}
	}
	while(q--){
		int x=read(),y=read(),d=read();
		if(binary_search(tmpx+1,tmpx+totx+1,x)){
			int tmp=(y+1)&1;
			auto it=st[0][tmp].lower_bound(y);
			if(it==st[0][tmp].end()){
				write(x),Spa,write(y+d),Nxt;
				continue;
			}
			int yy=*it;
			if(yy-y>=d){
				write(x),Spa,write(y+d),Nxt;
				continue;
			}
			d-=yy-y;
			y=yy;
			tmp=(x+1)&1;
			it=st[1][tmp].lower_bound(x);
			if(it==st[1][tmp].end()){
				write(x+d),Spa,write(y),Nxt;
				continue;
			}
			int xx=*it;
			if(xx-x>=d){
				write(x+d),Spa,write(y),Nxt;
				continue;
			}
			d-=xx-x;
			x=xx;			
		}else{
			int tmp=(x+1)&1;
			auto it=st[1][tmp].lower_bound(x);
			if(it==st[1][tmp].end()){
				write(x+d),Spa,write(y),Nxt;
				continue;
			}
			int xx=*it;
			if(xx-x>=d){
				write(x+d),Spa,write(y),Nxt;
				continue;
			}
			d-=xx-x;
			x=xx;
		}
		int nowx=x,nowy=y;
		x=lower_bound(tmpx+1,tmpx+totx+1,x)-tmpx;
		y=lower_bound(tmpy+1,tmpy+toty+1,y)-tmpy;
		for(int j=20;j>=0;j--){
			if(f[j][x]==inf||g[j][y]==inf)continue;
			if(cal(nowx,nowy,tmpx[f[j][x]],tmpy[g[j][y]])>d)continue;
			d-=cal(nowx,nowy,tmpx[f[j][x]],tmpy[g[j][y]]);
			nowx=tmpx[f[j][x]],nowy=tmpy[g[j][y]];
			x=f[j][x],y=f[j][y];
		}
		if(!d){
			write(nowx),Spa,write(nowy),Nxt;
			continue;
		}
		int tmp=(nowy+1)&1;
		auto it=st[0][tmp].lower_bound(nowy);
		if(it==st[0][tmp].end()){
			write(nowx),Spa,write(nowy+d),Nxt;
			continue;
		}
		int yy=*it;
		if(yy-nowy>=d){
			write(nowx),Spa,write(nowy+d),Nxt;
			continue;
		}
		d-=yy-nowy;
		nowy=yy;
		write(nowx+d),Spa,write(nowy),Nxt;
	}
}
```

---

## 作者：happybob (赞：2)

好题。

不妨假设询问的起点都在交叉口，且初始方向向上。其他情况都可以转成这种处理。

观察一下容易发现，对于 $x$ 相同的点，进行两次转弯后，到达的点 $x$ 都相同。对于 $y$ 相同的点也有类似结论。

考虑询问的路径必然形如经过了若干次连续两次的转弯后无法转弯。考虑倍增处理 $f_{i,j}$ 表示 $x=i$ 的点经过 $2^j$ 次转弯到达的 $x$ 是什么，$g_{i,j}$ 同理，不过是对于 $y$。询问的时候直接倍增处理即可。实现精细复杂度为 $O(n \log n)$。

代码实现比较丑，仅供参考：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int N = 2e5 + 5;

int fx[N][20], fy[N][20];
int x[2][N], y[2][N], n, q;
int cx[2], cy[2];

map<int, int> rx, ry;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	vector<int> tx, ty;
	for (int i = 1; i <= n; i++)
	{
		char c;
		cin >> c;
		int p;
		cin >> p;
		int k = p & 1;
		if (c == 'V') x[k][++cx[k]] = p, tx.emplace_back(p);
		else y[k][++cy[k]] = p, ty.emplace_back(p);
	}
	sort(x[0] + 1, x[0] + cx[0] + 1);
	sort(x[1] + 1, x[1] + cx[1] + 1);
	sort(y[0] + 1, y[0] + cy[0] + 1);
	sort(y[1] + 1, y[1] + cy[1] + 1);
	sort(tx.begin(), tx.end());
	sort(ty.begin(), ty.end());
	for (int i = 0; i < tx.size(); i++) rx[tx[i]] = i;
	for (int i = 0; i < ty.size(); i++) ry[ty[i]] = i;
	// Init for x
	for (int i = 0; i < tx.size(); i++)
	{
		int k = tx[i] & 1;
		k ^= 1;
		int pos = upper_bound(x[k] + 1, x[k] + cx[k] + 1, tx[i]) - x[k];
		if (pos > cx[k]) fx[i][0] = -1;
		else
		{
			fx[i][0] = rx[x[k][pos]];
		}
	}
	for (int j = 1; j <= 19; j++)
	{
		for (int i = 0; i < tx.size(); i++)
		{
			if (fx[i][j - 1] == -1) fx[i][j] = -1;
			else fx[i][j] = fx[fx[i][j - 1]][j - 1];
		}
	}
	// Init for y
	for (int i = 0; i < ty.size(); i++)
	{
		int k = ty[i] & 1;
		k ^= 1;
		int pos = upper_bound(y[k] + 1, y[k] + cy[k] + 1, ty[i]) - y[k];
		if (pos > cy[k]) fy[i][0] = -1;
		else
		{
			fy[i][0] = ry[y[k][pos]];
		}
	}
	for (int j = 1; j <= 19; j++)
	{
		for (int i = 0; i < ty.size(); i++)
		{
			if (fy[i][j - 1] == -1) fy[i][j] = -1;
			else fy[i][j] = fy[fy[i][j - 1]][j - 1];
		}
	}
	while (q--)
	{
		int px, py, d;
		cin >> px >> py >> d;
		if (!rx.count(px) || !ry.count(py))
		{
			if (rx.count(px))
			{
				auto it = upper_bound(ty.begin(), ty.end(), py);
				if (it == ty.end() || (*it - py) >= d)
				{
					cout << px << " " << py + d << "\n";
					continue;
				}
				else
				{
					d -= (*it - py);
					int g = (*it - py);
					py = *it;
					if (g & 1)
					{
						int k = px & 1;
						k ^= 1;
						int pos = upper_bound(x[k] + 1, x[k] + cx[k] + 1, px) - x[k];
						if (pos > cx[k] || (x[k][pos] - px >= d))
						{
							cout << px + d << " " << py << "\n";
							continue;
						}
						d -= (x[k][pos] - px);
						px = x[k][pos];
					}
				}
			}
			else
			{
				int k = px & 1;
				int pos = upper_bound(x[k] + 1, x[k] + cx[k] + 1, px) - x[k];
				if (pos > cx[k] || (x[k][pos] - px >= d))
				{
					cout << px + d << " " << py << "\n";
					continue;
				}
				else
				{
					d -= (x[k][pos] - px);
					px = x[k][pos];
				}
			}
		}
		// now, (px, py) is in a crossing, arrow is up
		for (int i = 19; i >= 0; i--)
		{
			int xid = rx[px], yid = ry[py];
			if (fx[xid][i] == -1 || fy[yid][i] == -1)
			{
				continue;
			}
			int nx = tx[fx[xid][i]], ny = ty[fy[yid][i]];
			if (nx - px + ny - py <= d)
			{
				d -= (nx - px + ny - py);
				px = nx, py = ny;
			}
		}
		if (!d) cout << px << " " << py << "\n";
		else
		{
			int k = py & 1;
			k ^= 1;
			int pos = upper_bound(y[k] + 1, y[k] + cy[k] + 1, py) - y[k];
			if (pos > cy[k] || (y[k][pos] - py) >= d)
			{
				cout << px << " " << py + d << "\n";
			}
			else
			{
				d -= (y[k][pos] - py);
				py = y[k][pos];
				cout << px + d << " " << py << "\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：xyvsvg (赞：1)

注意到：奶牛改变方向当且仅当一条道路的长度为奇数。我们可以直接预处理出每条道路右 / 上方第一个与他距离为奇数的道路。

这样的话，奶牛的轨迹必然是连续的“上 - 右 - 上……”或“右 - 上 - 右……”。不妨把一段上 + 右考虑成一步，则奶牛一定会连续走若干步，直到剩余时间不足。

于是我们对于每个询问，找到距离 $(x_i,y_i)$ 最近的十字路，然后跳若干步，对于剩余部分，分讨考虑即可。

由于步数可能很多，但无论是上还是右，一条道路所要跳到的另一条道路总是固定的，于是我们可以倍增优化。

注意特判无法走到任何一个十字路口的情况。

复杂度为 $O(n\log n)$，代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct ST
{
    int n,m;
    vector<vector<int> >st;
    ST(int n_,const vector<int>&a)
    {
        n=n_;
        m=20;
        st.resize(m,vector<int>(n+10,n+1));
        array<int,2> mk={n+1,n+1};
        for(int i=n;i;--i)
        {
            st[0][i]=mk[a[i]&1^1];
            mk[a[i]&1]=i;
        }
        for(int j=1;j<m;++j)
            for(int i=1;i+(1<<j)-1<=n;++i)
                st[j][i]=st[j-1][st[j-1][i]];
    }
};
signed main()
{
    int n,Q;
    cin>>n>>Q;
    vector<int>a,b;
    for(int i=0;i<n;++i)
    {
        char c;
        int x;
        cin>>c>>x;
        if(c=='V')
            a.push_back(x);
        else
            b.push_back(x);
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    n=a.size();
    int m=b.size();
    a.insert(a.begin(),-1);
    b.insert(b.begin(),-1);
    a.push_back(INT_MAX);
    b.push_back(INT_MAX);
    ST sa(n,a),sb(m,b);
    while(Q--)
    {
        int x,y,k,K;
        cin>>x>>y>>K;
        k=K;
        int p=lower_bound(a.begin(),a.end(),x)-a.begin();
        int q=lower_bound(b.begin(),b.end(),y)-b.begin();
        int dx=a[p],dy=b[q];
        if(dx-x+dy-y>k)
        {
            if(dx==x)
                cout<<x<<' '<<y+k<<endl;
            else
                cout<<x+k<<' '<<y<<endl;
        }
        else
        {
            k-=dx+dy-x-y,x=dx,y=dy;
            for(int i=19;~i;--i)
                if(a[sa.st[i][p]]-a[p]+b[sb.st[i][q]]-b[q]<=k)
                    k-=a[sa.st[i][p]]-a[p]+b[sb.st[i][q]]-b[q],
                    p=sa.st[i][p],
                    q=sb.st[i][q];
            x=a[p],y=b[q];
            if(K-k&1^1)
            {
                if(b[sb.st[0][q]]-b[q]<=k)
                    k-=b[sb.st[0][q]]-b[q],y=b[sb.st[0][q]],x=a[p]+k;
                else
                    y=b[q]+k;
            }
            else
            {
                if(a[sa.st[0][p]]-a[p]<=k)
                    k-=a[sa.st[0][p]]-a[p],x=a[sa.st[0][p]],y=b[q]+k;
                else
                    x=a[p]+k;
            }
            cout<<x<<' '<<y<<endl;
        }
    }
    return 0;
}

```

---

## 作者：Wogua_boy (赞：0)

这里给出一种递归的思路.

对每条横线，记录纵坐标往上的下一条 [奇偶性不同] 的横线.

对每条竖线，记录横坐标往右的下一条 [奇偶性不同] 的竖线.

记奶牛转变方向的过程是 [拐弯] .

对每头奶牛，设计如下寻路策略：

- 如果当前不在交叉点上，就去找最近的交叉点 (第一步)

- 如果当前已经在交叉点上，就先确定方向，这里以往东走为例：

  去找下一条 [奇偶性不同] 的纵线

  因为中间的所有纵线都不可能产生 [拐弯]，可以一次性走完.

  找到下一条纵线后，如果时间可以走到，就递归到那个点继续寻路.

此时，已经可以做到 $45$ 分，但是时间复杂度是 $O(n^2q)$ .

有这样一个补丁：

- 记和当前维度的上一条线 [奇偶性不同] 的线为 **奇线** 
- 两条 **奇线** 的交点记为 **奇点**
- 从任何一条线上的任意点出发，[拐弯] 2 次之内必定可以到达 **奇点**
- 到达 **奇点** 之后，可以通过二分的方法处理出接下来将完整地拐多少个弯，然后快速拐完这些弯，到达目标点 $u$ .
- 到 $u$ 之后，剩下的时间只能拐不超过两次弯了，继续递归处理.

打上这个补丁之后，**奇点** 前后的操作都是常数，时间的瓶颈在到达 **奇点** 后的二分操作. 整体时间复杂度 $O(q \log n)$ 

我的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
vector<int> hs, vs;
map<int, int> hm, vm;
vector<int> qhs, qvs;
map<int, int> qhm, qvm;
int n, q;

void dfs(int x, int y, int d, int f)
{
    if (qhm.count(x) && qvm.count(y))
    {
        // <奇, 奇> 点, 额外处理一部分
        int idx = qhm[x];
        int idy = qvm[y];
        int len = min(qhs.size() - idx - 1, qvs.size() - idy - 1);
        int L = 0, R = len, p = 0;
        while (L <= R)
        {
            int mid = (L + R) >> 1;
            if (qhs[idx + mid] - qhs[idx] + qvs[idy + mid] - qvs[idy] <= d)
            {
                p = mid;
                L = mid + 1;
            }
            else
            {
                R = mid - 1;
            }
        }
        // 先把完整的拐完
        d -= qhs[idx + p] - qhs[idx] + qvs[idy + p] - qvs[idy];
        x = qhs[idx + p];
        y = qvs[idy + p];
    }
    if (hm.count(x) && vm.count(y))
    {
        // 交点
        if (f % 2 == 0)
        {
            // 当前走了偶数步
            // 往上二分找最近的 [奇偶性不同] 的点
            if (!qvs.size() || y >= qvs.back())
            {
                // 上面没有 [奇偶性不同] 的位置了
                cout << x << " " << y + d << "\n";
                return;
            }
            int idx = upper_bound(qvs.begin(), qvs.end(), y) - qvs.begin();
            if (y + d <= qvs[idx])
            {
                // 走不到
                cout << x << " " << y + d << "\n";
                return;
            }
            dfs(x, qvs[idx], d - (qvs[idx] - y), f ^ 1);
            return;
        }
        else
        {
            // 当前走了奇数步
            // 往右二分找最近的 [奇偶性] 不同的点
            if (!qhs.size() || x >= qhs.back())
            {
                // 右边没有 [奇偶性不同] 的位置了
                cout << x + d << " " << y << "\n";
                return;
            }
            int idx = upper_bound(qhs.begin(), qhs.end(), x) - qhs.begin();
            if (x + d <= qhs[idx])
            {
                // 走不到
                cout << x + d << " " << y << "\n";
                return;
            }
            assert(qhs[idx] - x > 0);
            dfs(qhs[idx], y, d - (qhs[idx] - x), f ^ 1);
            return;            
        }
    }
    if (vm.count(y))
    {
        // 横线上
        if (!hs.size())
        {
            // 如果没有竖线
            cout << x + d << " " << y << "\n";
            return;
        }
        if (x >= hs.back())
        {
            // 如果已经在最右侧了
            // 后面没有竖线
            cout << x + d << " " << y << "\n";
            return;
        }
        int idx = upper_bound(hs.begin(), hs.end(), x) - hs.begin();
        if (hs[idx] >= x + d)
        {
            // 有竖线，但是走不到
            cout << x + d << " " << y << "\n";
            return;
        }
        dfs(hs[idx], y, d - (hs[idx] - x), (hs[idx] - x) % 2);
        return;
    }
    if (hm.count(x))
    {
        // 竖线上
        if (!vs.size())
        {
            // 如果没有横线
            cout << x << " " << y + d << "\n";
            return;
        }
        if (y >= vs.back())
        {
            // 如果已经在最右侧了
            // 后面没有竖线
            cout << x << " " << y + d << "\n";
            return;
        }
        int idx = upper_bound(vs.begin(), vs.end(), y) - vs.begin();
        if (vs[idx] >= y + d)
        {
            // 有竖线，但是走不到
            cout << x << " " << y + d << "\n";
            return;
        }
        dfs(x, vs[idx], d - (vs[idx] - y), (vs[idx] - y) % 2);
        return;       
    }
}

int main ()
{
	cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        string op;
        int c;
        cin >> op >> c;
        if (op == "V")
            hs.push_back(c);
        else
            vs.push_back(c);
    }
    sort(hs.begin(), hs.end());
    sort(vs.begin(), vs.end());
    for (int i = 0; i < hs.size(); i++)
        hm[hs[i]] = i;
    for (int i = 0; i < vs.size(); i++)
        vm[vs[i]] = i;
    for (int i = 1; i < hs.size(); i++)
    {
        if (hs[i] % 2 != hs[i - 1] % 2)
            qhs.push_back(hs[i]);
    }
    for (int i = 1; i < vs.size(); i++)
    {
        if (vs[i] % 2 != vs[i - 1] % 2)
            qvs.push_back(vs[i]);
    }
    for (int i = 0; i < qhs.size(); i++)
        qhm[qhs[i]] = i;
    for (int i = 0; i < qvs.size(); i++)
        qvm[qvs[i]] = i;
    while (q--)
    {
        int x, y, d;
        cin >> x >> y >> d;
        dfs(x, y, d, 0);
    }
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

思路真的非常的清奇，好题。部分参考[这篇](/article/3qdyj2s2)题解。先提示一下，一种正解是倍增。

这道题的突破口是奶牛转向的条件。从奶牛第一次转向起，如果他转向，那意味着它遇到了一条与他方向不同，正好出入的奇偶性不同不同的道路。

到这里，我们仍然看不到倍增的影子。硬要说有的话，你可以选择找出所有的交叉点的下一个点。但是交叉点的个数是 $O(n^2)$ 的，显然接受不了。

但是我们容易发现，当奶牛下一次走向同方向的道路时，其奇偶性必然会发生改变。

有了上面的结论，横纵就先对独立了，也就是说我们可以考虑倍增了。

对于每一条边，记录出他的下 $2^j$ 条与他间隔为奇数的道路出现的位置。由于上述性质，当在 $x$ 方向走到后 $2^i$ 条边时，$y$ 方向也必然走到了后 $2^i$ 条边的位置。

因此我们可以考虑先走到下一个路口上，然后倍增快速寻找最后一次能够走到二者均改变的路口。最后考虑一下剩余的距离对应的位移即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, r[200005][19], c[200005][19];
vector<int> h, v; char o;
inline int ps(const vector<int>& v, int p) {
	return lower_bound(v.begin(), v.end(), p) - v.begin();
}
inline void query(int x, int y, int d) {
	int hp = ps(h, y), vp = ps(v, x), a = 0, lp;
	if (y != h[hp])
		if (d + y > h[hp]) d -= h[hp] - y, a += h[hp] - y;
		else return void(cout << x << " " << d + y << endl);
	if (x != v[vp])
		if (d + x > v[vp])d -= v[vp] - x, a += v[vp] - x;
		else return void(cout << x + d << " " << y << endl);
	//正确性：题目保证了初始点在道路上，这也就意味着以上两个if至多会进入其中的一个。
	for (int k = 18, ad; ~k; k--) {
		int nh = r[hp][k], nv = c[vp][k];
		if ((ad = v[nv] - v[vp] + h[nh] - h[hp]) > d)continue;
		d -= ad, a += ad, hp = nh, vp = nv;
		//不管你先走v还是先走h，都一定会走到下一个奇偶性不同的十字路口
		//因此，在这一步，可以优先保时复，直接向后跳就完事了
	}
	//此时已经跳到了最后一次能暴力走的路口，需要直接处理了。
	//注意到我们一直在跳路口，现在的位置也是一个路口。
	if (a & 1)
		//奇数步，向北走
		//如果走不到下一个奇偶性变化的点就在当前路
		//否则在拐角后的某个位置
		if ((v[lp = c[vp][0]] - v[vp] < d) && (d -= v[lp] - v[vp]))
			return void(cout << v[lp] << " " << h[hp] + d << endl);
		else return void(cout << v[vp] + d << " " << h[hp] << endl);
	//类似于向北走的思路
	if ((h[lp = r[hp][0]] - h[hp] < d) && (d -= h[lp] - h[hp]))
		return void(cout << v[vp] + d << " " << h[lp] << endl);
	else return void(cout << v[vp] << " " << h[hp] + d << endl);
}
signed main() {//写在前面：有参考3qdyj2s2的代码
	ios::sync_with_stdio(0); cin >> n >> m;
	for (int i = 1, p; i <= n; ++i)
		(cin >> o >> p, o != 'V' ? h : v).emplace_back(p);
	sort(h.begin(), h.end()); sort(v.begin(), v.end());
	h.emplace_back(2.1e9), v.emplace_back(2.1e9);
	for (int i = 0; i != 19; i++)
		r[h.size() - 1][i] = h.size() - 1,//谨防越界
		c[v.size() - 1][i] = v.size() - 1;//直接暴力跳回是好方法
	for (int i = h.size() - 2; i >= 0; i--) {
		r[i][0] = (h[i] + h[i + 1] & 1 ? i + 1 : r[i + 1][0]);
		//检验是否 h[i] 与 h[i + 1] 奇偶性不同
		//不同就是下一个点作为转折点
		//否则就是下一个点的下一个奇偶性不同的点
		for (int j = 1; j != 19; j++) r[i][j] = r[r[i][j - 1]][j - 1];
	}
	for (int i = v.size() - 2; i >= 0; i--) {
		c[i][0] = (v[i] + v[i + 1] & 1 ? i + 1 : c[i + 1][0]);
		//道理同上
		for (int j = 1; j != 19; j++) c[i][j] = c[c[i][j - 1]][j - 1];
	}
	for (int i = 1, x, y, d; i <= m; ++i)
		cin >> x >> y >> d, query(x, y, d);
}//能快速想到这是倍增的题的人也是真的厉害
```

---

