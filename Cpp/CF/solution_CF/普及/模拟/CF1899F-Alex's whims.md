# Alex's whims

## 题目描述

树中两个顶点 $u$ 和 $v$ 之间的距离是指顶点 $u$ 到顶点 $v$ 必须经过的最小边数。

亚历克斯的生日快到了，蒂莫菲想送他一棵有 $n$ 个顶点的树。然而，亚历克斯是个喜怒无常的孩子。在 $q$ 天里，他每天都会选择一个整数，第 $i$ 天选择的整数用 $d_i$ 表示。如果在第 $i$ 天，树上没有两片距离**正好**为 $d_i$ 的叶子节点，亚历克斯就会很失望。

蒂莫菲决定送给亚历克斯一个设计器，这样他就可以随心所欲地改变他的树了。蒂莫菲知道亚历克斯也很懒惰，所以每天一开始，他可以进行**多**次以下类型的操作：

- 选择顶点 $u$ 、 $v_1$ 和 $v_2$，需要满足 $u$ 和 $v_1$ 之间有一条边， $u$ 和 $v_2$ 之间没有边。然后删除 $u$ 和 $v_1$ 之间的边，并在 $u$ 和 $v_2$ 之间添加一条边。如果操作后图形不再是树，则**不能**执行此操作。

不知怎的，蒂莫菲设法找出了所有的 $d_i$ 。之后，他又想出了一个绝妙的主意——以防万一，为这组集合 $d_i$ 制作一本说明书，这样亚历克斯就不会失望了。

## 样例 #1

### 输入

```
3
3 3
2
2
2
5 6
4
2
3
4
3
2
4 9
2
3
3
2
2
2
3
2
2```

### 输出

```
1 2
2 3
-1 -1 -1
-1 -1 -1
-1 -1 -1
1 2
2 3
3 4
4 5
-1 -1 -1
4 3 2
5 4 3
4 2 5
4 5 2
5 3 4
1 2
2 3
3 4
4 3 2
4 2 3
-1 -1 -1
4 3 2
-1 -1 -1
-1 -1 -1
4 2 3
4 3 2
-1 -1 -1```

# 题解

## 作者：Z1qqurat (赞：4)

一开始被这个 $500$ 的数据范围吓到了，深思后发现就一诈骗。愤怒，感觉这整场都是诈骗题。

发现一开始构造一条链即可，每次通过移动点 $n$ 的位置来保证条件：记当前 $n$ 点的上一个点为 $p$，初始时 $p = n - 1$。那么每次询问 $d$，如果 $d = p$，也就是 $n$ 到 $1$ 的距离恰好为 $d$，不用操作；否则就直接断掉 $(p, n)$，连上 $(d, n)$ 即可。

所以 $n$ 为什么不出 $10 ^ 6$？？？？？这是故意要吓我是吧？？？？？

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;
const int N = 505;
int t, n, q;

void solve() {
    cin >> n >> q; int p = n - 1;
    for (int i = 1; i < n; ++i) cout << i << ' ' << i + 1 << "\n";
    for (int i = 1, d; i <= q; ++i) {
        cin >> d;
        if(p == d) cout << "-1 -1 -1\n";
        else cout << n << ' ' << p << ' ' << d << "\n", p = d;
    }
    return ;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}

---

## 作者：zct_sky (赞：4)

### Solution
-----

首先跑一下样例二，可以得到这 $6$ 个操作的图如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/8tmvhypv.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/kr89bb97.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/6kv8er32.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/xht35ef7.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/6kv8er32.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/kr89bb97.png)

然后我们就可以仿照样例的思路，先将整棵树建立成一条链，然后以 $2$ 为链头，维护两条链。其中一条 $u$ 维护询问所需的深度，另一条 $v$ 负责放剩余节点，设 $u,v$ 链表的大小分别为 $siz_u,siz_v$。

设本次询问的 $d_i$ 为 $x$，则对询问的操作如下：
- $x=siz_u \text{ or } x=siz_v$，不进行操作，输出 $-1\ -1 \ -1$。
- $x>siz_u$，将 $u$ 中最后 $x-siz_u$ 个节点移至 $v$ 上。
- $x<siz_u$，将 $v$ 中最后 $siz_u-x$ 个节点移至 $u$ 上。

至于移动的输出，则再举个例子。若要将 $u$ 中最后 $y$ 个节点移至 $v$ 上，则三个输出分别为：$u$ 的第 $siz_u-y+1$ 个元素，$u$ 的第 $siz_u-y$ 个元素与 $v$ 的第 $siz_v$ 个元素。

最后时间复杂度为 $\mathcal{O}(nq)$，虽然不如其他题解的 $\mathcal{O}(q)$，但过这题也是绰绰有余。

### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
const int N=5e2+7;
ll T,n,q,u[N],ut,v[N],vt;
void moveu(ll y){
	ll U,V1,V2;
	U=u[ut-y+1];
	V1=u[ut-y];
	V2=v[vt];
	printf("%lld %lld %lld\n",U,V1,V2);
	for(int i=ut-y+1;i<=ut;i++)
		v[++vt]=u[i];
	ut-=y; 
}
void movev(ll y){
	ll U,V1,V2;
	U=v[vt-y+1];
	V1=v[vt-y];
	V2=u[ut];
	printf("%lld %lld %lld\n",U,V1,V2);
	for(int i=vt-y+1;i<=vt;i++)
		u[++ut]=v[i];
	vt-=y;
}
int main(){
	T=read();
	u[1]=v[1]=2;
	while(T--){
		n=read();q=read();
		for(int i=1;i<n;i++)
			printf("%d %d\n",i,i+1);
		ut=n-1;
		for(int i=2;i<=ut;i++)
			u[i]=i+1;
		vt=1;
		while(q--){
			ll x=read();
			if(x==vt||x==ut)printf("-1 -1 -1\n");
			else{
				if(x>ut) movev(x-ut);
				else moveu(ut-x);
			}
		}
	}
	return 0;
}
```

---

## 作者：Louis_lxy (赞：4)

这题总体来说还是挺简单的，就是数据范围很坑，让人以为正解是 $O(n^2)$ 但是实际上，正解是 $O(n)$。

话说这题是我见过的最简单的 CF 的 F 题了。

可以发现，只要在最开始的时候构建一条链，用 $p$ 点来维护条件：初始为 $p \gets n - 1$，观察规律，可以发现，如果用 $p$ 保存上个点的位置，如果 $d=p$，说明上一个点到 $1$ 的距离刚好就是 $d$，不用进行操作，反之就把链 $[p,n]$ 断掉，再连上 $[d,n]$ 即可。

另外简单讲一下为什么初始值为 $n-1$，其实不难想到，最初时的链是 $[1,n]$ 而如果 $d=n-1$ 那么肯定不满足题目所说的操作条件。

另外，这题还有一个坑点，因为他很懒，所以能不操作就不操作，不过对做题影响不大。

放上代码：

```cpp
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int main()
{
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n, q, p;
		cin >> n >> q;
		p = n - 1;
		for (int i = 1; i < n; ++i)//构成链
			cout << i << ' ' << i + 1 << endl;
		for (int i = 1; i <= q; ++i)
		{
			int d;
			cin >> d;
			if (p == d)//如果长度刚好是d就不用操作
				cout << "-1 -1 -1\n";
			else//反之断掉[q,n]，连上[d,n]
			{
				cout << n << ' ' << p << ' ' << d << endl;
				p = d;
			}
		}
	}
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 CF1899F Alex's whims](https://www.luogu.com.cn/problem/CF1899F)

## 解题思路

如图，用 $n-1$ 个节点构造一条链，根节点为 $n$，叶节点为 $1$。（此处 $n=8$）

![](https://cdn.luogu.com.cn/upload/image_hosting/i8e6ksjf.png)

让动点 $n$ 与编号为 $k\in[2,n-1]$ 的点相连。

不难发现，节点 $n$ 也是叶节点。

节点 $1$ 到节点 $k$ 的距离为 $k-1$，节点 $k$ 到节点 $n$ 的距离为 $1$，所以节点 $1$ 到节点 $n$ 的距离为 $k$。

通过调整 $k\in[2,n-1]$ 的编号，即可得到距离为 $d\in[2,n-1]$ 的两个叶节点。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
const int N=505;
int d[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n,q;
		cin>>n>>q;
		for(int i=1;i<=q;i++)
		{
			cin>>d[i];
		}
		for(int i=1;i<=n-2;i++)
		{
			cout<<i<<' '<<i+1<<'\n';
		}
		cout<<n<<' '<<2<<'\n';
		int now=2;
		for(int i=1;i<=q;i++)
		{
			if(d[i]==now)
			{
				cout<<"-1"<<' '<<"-1"<<' '<<"-1"<<'\n';
			}
			else
			{
				cout<<n<<' '<<now<<' '<<d[i]<<'\n';
				now=d[i];
			}
		}
	}
    return 0;
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

这题的数据范围是不是有什么病啊。

考虑观察样例。

不难发现，如果我们在一开始就将其构造成链，每次需要移动的时候固定移动某一个最初为链头的点，一定是可行的。假定最初构造出来的时候两个链头分别为 $1,n$，树的根为 $1$。

如果不需要移动，就是 $d_i=dep_n-dep_1$。因为题目里并没有跟你说只要可以不移动满足条件，就一定不能移动（赛时我都没有发现）。如果需要移动，因为 $1$ 到 $n-1$ 仍然构成一条链，所以只需要把 $n$ 连向一个深度为 $d_i$ 的点就行了（$d_i-dep_1+1=d_i$）。这时你会发现，复杂度是 $O(q)$ 的。

$1 \le q \le 500$ 啊。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

int n,q,dep,lst;

il void solve(){
	cin>>n>>q;
	for(re int i=1;i<n;++i) cout<<i<<" "<<i+1<<"\n";
	dep=n,lst=n-1;
	for(re int k=1;k<=q;++k){
		int d;cin>>d;bool fl=0;
		if(dep-1==d) cout<<"-1 -1 -1\n";
		else cout<<n<<" "<<lst<<" "<<d<<"\n",lst=d,dep=d+1;
	}
	return ;
}

signed main(){
	int t;cin>>t;while(t--)
	solve();
	return 0;
}

```


---

## 作者：huangboning (赞：0)

容易发现一件事：首先构造一条链，每次操作都将 $n$ 号节点接到 $d_{i}$ 号的节点上，这样就可以保证 $1$ 号节点与 $n$ 号节点距离为 $d_{i}$。

需要注意如果在操作前 $n$ 号节点已经接在了 $d_{i}$ 号节点上,就不用移动。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,lst,x;
int main()
{
	cin>>T;
	while(T--){
		cin>>n>>q;
		for(int i=1;i<n;i++){
			cout<<i<<" "<<i+1<<"\n";
		}
		lst=n-1;
		for(int i=1;i<=q;i++){
			cin>>x;
			if(lst==x)cout<<"-1 -1 -1\n";
			else cout<<n<<" "<<lst<<" "<<x<<endl,lst=x;
		}
	}
 } 
```

---

## 作者：WaterSun (赞：0)

# 思路

比较诈骗的一个题。

首先如果我们先让这棵树形成一条链，那么，这棵树中有效的路径只有从 $1$ 到 $n$ 的路径，且长度为 $n - 1$。

发现如果每次将 $n$ 号点移动，非常方便，如果要构造长度为 $x$，只需将 $n$ 连向与 $1$ 距离为 $x - 1$ 的点即可。

为了便于构造，直接将链构造为 $i \to (i + 1)$ 的形式，与 $1$ 距离为 $x - 1$ 的点便是 $x - 1$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

int T,n,q;

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    n = read();
    q = read();
    int lst = n - 1;
    for (re int i = 1;i < n;i++) printf("%d %d\n",i,i + 1);
    while (q--){
        int x;
        x = read();
        if (x == lst) puts("-1 -1 -1");
        else{
            printf("%d %d %d\n",n,lst,x);
            lst = x;
        }
    }
}

int main(){
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：operator_ (赞：0)

# Alex's whims

[题目传送门](https://www.luogu.com.cn/problem/CF1899F)

## 题解

构造题，感觉比 G 更难？可能是我不擅长构造。

考虑点的度数，发现一次操作 $u,v_1,v_2$ 会使 $deg_{v_1}$ 减 $1$，使 $deg_{v_2}$ 加 $1$，即一次操作最多减少一个叶子，那如果存在一个时刻使我们的叶子数量大于 $3$ 个，下一次若问 $n-1$ 则直接爆炸，所以要么就是离线下来考虑，要么就是使每时每刻的叶子数量 $\le 3$。显然后者更简单。

考虑一个更一般的思路，使 $1$ 始终为叶子，从点 $2$ 开始引出两个分叉，大概是这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/lcyhzeb2.png)

我们强制选择一个分叉，比如左边那个，然后多了就移到右边，少了就从右边补，就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
	int s=0,m=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
	while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return m?-s:s;
}
int t,n,q;
vector<int> a,b;
signed main() {
	cin>>t;
	while(t--) {
		n=rd(),q=rd();
		a.clear(),b.clear();
		a.push_back(2);
		for(int i=2;i<=n;i++)
			b.push_back(i),printf("%lld %lld\n",i-1,i);
		while(q--) {
			int d=rd();
			if(a.size()==d||b.size()==d) 
				printf("-1 -1 -1\n");
			else if(a.size()<d) {
				int id=b.size()-(d-a.size());
				printf("%lld %lld %lld\n",b[id],b[id-1],a[a.size()-1]);
				for(int i=id;i<b.size();i++)
					a.push_back(b[i]);
				for(int i=b.size()-1;i>=id;i--)
					b.pop_back();
			}
			else {
				printf("%lld %lld %lld\n",a[d],a[d-1],b[b.size()-1]);
				for(int i=d;i<a.size();i++)
					b.push_back(a[i]);
				for(int i=a.size()-1;i>=d;i--)
					a.pop_back();
			}
		}
	}
	return 0;
}

```

---

## 作者：DerrickLo (赞：0)

不难想的构造题。

我们可以先构造一条链，第 $i$ 条边由 $i$ 连向 $i+1$。

考虑第 $1$ 个点和第 $n$ 个点的距离，对于第 $i$ 天，我们将连向第 $n$ 个点的边的另一个点换成 $d_i$，那么这样第 $1$ 个点到第 $n$ 个点的距离就是 $d_i$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q,d[505];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=q;i++)cin>>d[i];
		for(int i=1;i<n;i++)cout<<i<<' '<<i+1<<'\n';
		int lst=n-1;
		for(int i=1;i<=q;i++){
			if(d[i]==lst){
				cout<<"-1 -1 -1\n";
				continue;
			}
			cout<<n<<' '<<lst<<' '<<d[i]<<'\n';
			lst=d[i];
		}
	}
	return 0;
}
```

---

