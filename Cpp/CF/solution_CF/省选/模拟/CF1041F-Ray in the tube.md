# Ray in the tube

## 题目描述

### 题目大意：
下边界有$n$个给定点，上边界有$m$个给定点，可以从任意一个点发出一条激光，激光碰到边界会反射

激光到达边界必须打到整数点，问最多可以打到几个给定点

## 样例 #1

### 输入

```
3 1
1 5 6
1 3
3
```

### 输出

```
3
```

# 题解

## 作者：zhoutb2333 (赞：11)

首先观察到 $y_1$ 和 $y_2$ 是没用的。激光最终会射到哪些接收器只会被 $A$ 点和
$B$ 点的位置所影响。

而 $A$ 点的位置和 $B$ 点的位置被 $x_A$ 和 $|x_A-x_B|$ 所决定。我们令 $L=|x_A-x_B|$ 。

现在假设我们已经确定了 $x_A$ ，并且还要选择 $L$ 。假如说我们选择了一个 $L$ ，并且存在一个**大于一的**奇数 $k|L$ ，那么我们可以选择一个新的 $L'=\frac{L}{k}$ ，新的激光不仅会经过原来的关键点，还会多经过一些点。

比如说 $k=3$ 的情况如下所示，新激光多经过了紫色圆圈的点：

[![iZGIpt.md.png](https://s1.ax1x.com/2018/09/17/iZGIpt.md.png)](https://imgchr.com/i/iZGIpt)

那么所以说**我们选择的 $L$ 不能被任意比一大的奇数整除。**

也就是说 $L=2^n$ 。这样的 $L$ 只有 $\log_2 10^9$ 个，我们挨个算最优解即可。

对于一个固定的 $L$ ，我们还需要计算最优的 $x_A$ 。观察到在下边的关键点 $a_i$ 如果满足 $|a_i-x_a| \equiv 0 \ (mod \ 2L)$ 则会被射中，而在上边的关键点 $b_i$ 则需满足 $|b_i-x_a| \equiv L \ (mod \ 2L)$ 。所以我们可以开一个 $map$ ，对于每个关键点让这个位置所需的 $x_A ++$ （在 $mod \ 2L$ 意义下 ）。

复杂度 $O(N \log N \log_2 10^9)$。

还有一个坑点，就是 $x_A$ 可以等于 $x_B$ ，相当于激光在一个位置来回跳。我就因为这个fst了...

``` cpp
#include<bits/stdc++.h>
#define maxn 200010
using namespace std;

int a[maxn],b[maxn],n,m,nothing,ans=0;
map<int,int> M;
void check(int x){
    M.clear();
    for(int i=1;i<=n;i++)
        M[a[i]%(2*x)]++;
    for(int i=1;i<=m;i++)
        M[(b[i]+x)%(2*x)]++;
    for(auto v:M)
        ans=max(ans,v.second);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>nothing;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    cin>>m>>nothing;
    for(int i=1;i<=m;i++)
        cin>>b[i];
    for(int i=1;i<=n;i++)
        M[a[i]]++;
    for(int i=1;i<=m;i++)
        M[b[i]]++;
    for(auto v:M)
        ans=max(ans,v.second);
    for(int i=0;i<=29;i++)
        check(1<<i);
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Altwilio (赞：8)

### $1.$ 题意

给定两条数轴，上轴有 $n$ 个关键点，下轴有 $m$ 个关键点。要求在下轴寻找 $A$ 点和在上轴寻找 $B$ 点，使从 $A$ 向 $B$ 发射光线在两个轴之间反射（碰到轴即反射，每个反射点必须是整点，满足反射定律）可以经过的关键点最多，输出最大值。

### $2.$ 思路

首先明确给的纵坐标没有任何用。光线经过的点只由 $A,B$ 两点决定。

设 $A,B$ 的横坐标差的绝对值为 $L$。然后我们通过画图发现对于一个 $L$，若 $L$ 包含一个大于 $1$ 的奇数因子 $k$，那么这个 $L$ 一定不如 $L \over k$ 优。 如图，同一点 $L$ 形成的光线在包含 $3L$ 光线所经过点的基础上还多包含了紫色的点。所以 $L$ 严格优于 $3L$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ckbn62t7.png)

于是我们发现对于一个固定点的 $L$ 只能取 $2$ 的整数次幂。$L = 2^n$，所以 $L$ 一共有 $\log_210^9$ 个取值不到 $30$ 个，所以对于固定位置直接枚举。

观察发现，对于下方的关键点满足横坐标为 $L$ 的偶数倍时可以被选到，上方的关键点满足横坐标为 $L$ 的奇数倍时可以被选到。开一个 $map$ 扫描每一个关键点，对于每一个 $L$ 的可能取值，使其在模 $2L$ 的意义下的起点加一，最后取最大值。复杂度 $O(N\log N \log_2 10^9)$

### $3.$ 代码

```cpp
const int N = 2e5 + 10;
int a[N], b[N], n, m, nouse, ans;
map<int, int> M;

inline void check(int x){
    M.clear();
    for(int i = 1; i <= n; i ++) M[a[i] % (x << 1)] ++;
    for(int i = 1; i <= m; i ++) M[(b[i] + x) % (x << 1)] ++;
    for(auto v : M) ans = max(ans, v.second);
}

signed main(){
    read(n), read(nouse); for(int i = 1; i <= n; i ++) read(a[i]);
    read(m), read(nouse); for(int i = 1; i <= m; i ++) read(b[i]);
    for(int i = 1; i <= n; i ++) M[a[i]] ++;
    for(int i = 1; i <= m; i ++) M[b[i]] ++;
    for(auto v : M) ans = max(ans, v.second);
    for(int i = 0; i <= 29; i ++) check(1 << i);
    print(ans); return 0;
}
```


---

## 作者：BLUESKY007 (赞：2)

昨天晚上全机房集体开$Div2$,因为人傻挂两次$B$题的我开场就$rank2000+\dots qwq$于是慌乱之中的我就开始胡乱看题~~(口胡)~~,于是看了$F\dots$~~(全机房似乎也就我一个人慌到心态爆炸)~~  
起初想到的只有$n^2$的暴力,然而复杂度显然炸了,于是试图寻找规律,但是只想到一个假结论:忽略$y$,然后取上面坐标为奇数的点数与下面坐标为偶数的点数的和与上面坐标为偶数的点数与下面坐标为奇数的点数的和,也即步长为$1$  
但是显然这样过不了样例啊(上面的方法输出$2\dots$然而答案是$3$),因为没有考虑在上面和下面选的点的坐标奇偶性相同的情况,也即步长为$2k(k\in N_+)$的情况,但是如果要枚举$\forall k\in [1,5\cdot10^8]$的话显然复杂度还是不对,于是切$F$题的幻想就此破灭$qwq$~~(所以我把CD都切了(逃))~~  
于是经过一番仔$(can)$细$(kao)$思$(ti)$考$(jie)$发现只需要枚举步长为$2^i(i\in[0,29])$即可且$y$坐标可以忽略,证明如下:  
对$y$坐标可以忽略的解释:考虑$y$坐标在步长一定时只会影响$ray$的斜率,而反射时斜率取相反数,所以显然在$y$坐标差一定的情况下,步长总是定值,反射点也总是固定的~~(口胡)~~,所以不妨忽略$y$坐标的影响(可以画图模拟一下)  
假设步长不为$2^k(k\in N)$则一定可以表示为$2^l\cdot (2p+1)(l,p\in N)$,此时我们作出从某一点出发步长分别为$2^l,2^l\cdot(2p+1)(l,p\in N)$的$ray$的路径图像(假设此时$l=1,p=3$,点$(2,0)$是两条$ray$的一个公共点,则步长分别为$2,6$)  
![](http://bluesky007.ml/files/pics/CF1041_01.png)  
不难发现在步长不等于$2^l(l\in N)$时,步长为$2^l\cdot (2p+1)(l,p\in N)$的$ray$的反射点与步长为$2^l$的$ray$的反射点完全重合且反射点密度小于步长为$2^l$的$ray$的反射点密度,所以对于所有步长非$2^k(k\in N)$的$ray$一定会存在一个更优解使得$ans$更大,由此可得只需判断步长为$2^k(k\in N)$的情况即可  
所以正解就是枚举对于所有的出发点,步长为$2^i(i\in[0,29])$的情况,对所有的$ans$取$max$即可,每次枚举$i$对所有坐标分上下对$2^{i+1}$取模分类,用$map$存余数为$r(r\in[0,2^{i+1}-1])$的坐标个数,时间复杂度为$O((log10^9)\cdot(n+m))$  
$AC$代码$\downarrow\downarrow\downarrow$  
```cpp
#include<cstdio>//CF1041F
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<map>

using namespace std;

const int N=1e5+5;

int n,m,y,a[N],b[N],base2[31],ans,LUOGU;

void solve(int u){
    map<int,int>cntd,cntu;
    int mod=base2[u+1];
    for(int i=1;i<=n;i++){
        cntd[a[i]%mod]++;
    }
    for(int i=1;i<=m;i++){
        cntu[b[i]%mod]++;
    }
    for(int i=1;i<=n;i++){
        ans=max(ans,cntd[a[i]%mod]+cntu[(a[i]+base2[u])%mod]);
    }
    for(int i=1;i<=m;i++){
        ans=max(ans,cntu[b[i]%mod]+cntd[(b[i]+base2[u])%mod]);
    }
}

int main(){
    for(int i=0;i<=30;i++){
        base2[i]=(1<<i);
    }
    scanf("%d%d",&n,&y);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d%d",&m,&y);
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
    }
    for(int i=0;i<=29;i++){
        solve(i);
    }
    printf("%d\n",max(ans,2));
    return 0;
}
```

---

## 作者：nynkqh_yzp (赞：1)

首先，$y_1$ 和 $y_2$ 是没用的，因为只关心两条线上的情况。

我们可以固定激光是从左往右射的。

如果一次 $x$ 坐标的增加量为 $l$。那么 $l$ 一定是 $2$ 的整数次幂。

因为若 $l$ 有奇质因子，那么就可以把它从 $l$ 中去掉，不影响结果。

所以我们可以直接枚举 $l$ 然后把每个 $b_i$ 加上 $l$。相当于把 $y_2$ 上的点变成 $y_1$ 上的点。接下来只有两个数的差是 $2\times l$ 的倍数时才会同时被射到。即两个数同余。可以用 `unordered_map` 开一个桶来记录每个余数当前的答案。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,a[100001],b[100001],ans,c[200001],k;
unordered_map<int,int>q;
int main(){
	scanf("%d%*d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%d%*d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	k=n+m;
	for(int i=29;i>=0;i--){
		for(int j=1;j<=n;j++)
			c[j]=a[j];
		for(int j=1;j<=m;j++)
			c[j+n]=b[j]+(1<<i);
		q.clear();
		for(int j=k;j>0;j--){
			q[c[j]%(1<<i+1)]++;
			ans=max(ans,q[c[j]%(1<<i+1)]);
		}
	}
	q.clear();
	for(int j=1;j<=n;j++){
		q[a[j]]++;
		ans=max(ans,q[a[j]]);
	}
	for(int j=1;j<=m;j++){
		q[b[j]]++;
		ans=max(ans,q[b[j]]);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Mr_HY43205 (赞：1)

[CF1041F Ray in the tube](https://www.luogu.com.cn/problem/CF1041F)
### 题意
有一根平行于 $x$ 轴的管道，其下边缘纵坐标为 $y_1$，上边缘纵坐标为 $y_2$。在两个边缘上分别有 $n$ 和 $m$ 个传感器，横坐标用 $a_i,b_i$ 表示。向管内发射一束激光，激光碰到边缘会反射，问激光最多能打到几个传感器。

$1\leq n,m\leq 10^5,0\leq y_1 < y_2 \leq 10^9,0\leq a_i,b_i \leq10^9$。

------------
### 解题思路
本题求解的是打到的传感器数量。首先可以发现，上下边缘的纵坐标，即 $y_1$ 和 $y_2$ 对答案是没有影响的。我们只需要关注传感器的横坐标即可。同样的，激光的发出点在上边缘还是下边缘对答案也没有影响，因此我们不妨设激光发出点总是在上边缘。

而能够被激光打到的传感器横坐标的形式与等差数列有相似之处，即最终结果只与发出点的横坐标（首项 $x$），和每次从一个边缘到另一个边缘，经过横坐标的差值（公差 $d$）有关。对于给定的 $x$ 和 $d$，这束激光能覆盖到的点必定是同边缘上的 $x+2k\times d,k\in\mathbb{N}$，和另一边缘上的 $x+(2k+1)\times d,k\in\mathbb{N}$。

从数据范围来看，直接枚举 $x$ 和 $d$ 的时间复杂度太高，显然不是正解。但我们可以从这个思路出发，看看有什么可优化的地方或者一些特别的性质。

既然本题需要我们打到尽可能多的传感器，那直觉上来说，公差越小，打到传感器的概率就越大。那直接把 $d$ 设为 $1$ 可行吗？从题目样例 $1$ 来看就不行。样例 $1$ 中， $d=2$ 时经过的传感器比 $d=1$ 时多。

但是，当我们再构造几组数据时，发现有时这个结论是成立的。比如， $d=5$ 时，构造以下例子：
```cpp
5 0
1 11 21 31 41
5 1
6 16 26 36 46
```
在这组数据中，虽然原本是按照 $d=5$ 构造的，$d=1$ 时也能打到所有传感器，而且还能覆盖到更多的点。

再举一些例子，会发现公差为奇数时，其结果一定不会比 $d=1$ 时更优。

于是，我们也可以推出： $d=2\times(2k+1),k\in \mathbb{Z^+}$ 时，其结果一定不会比 $d=2$ 时更优。

更广泛地说，我们可以用 $d=2^l,l\in\mathbb{N}$ 来覆盖所有 $d=2^l\times(2k+1),l\in\mathbb{N},k\in\mathbb{Z^+}$ 覆盖到的点。

这个结论不难证明。对于任意一个 $d=2^l\times(2k+1)$ 所能达到的同边缘点 $x+2\times d$，都有 

$x+2\times d = x+4\times(2k+1)\times2^l$，

因此 $2^l$ 也能覆盖到。不同边缘的点同理。

于是，$d$ 的范围就从 $10^9$ 缩小到了 $\log(10^9)$。由此我们就可以进行枚举了。

枚举的方法是对每一个 $d$，计算每一个传感器所对应横坐标最小的首项 $x$，然后找到能够打到最多传感器的 $x$ 即可。由于 $x$ 的范围为 $[0,10^9]$，我们需要使用一个 map 来记录每一个 $x$ 所能打到的传感器数量。由于 $n$ 与 $m$ 同阶，本题的时间复杂度为 $O(n\log n\cdot\log(10^9))$。

本题还有一种特殊情况，即为上下边缘都只有一个传感器，且 $a_1=b_1$。此时 $d=0$，无法计算到。这种情况只需要把答案的初始值设为 $2$，这样在取 $\max$ 操作时就可以绕过这个问题。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxN = 100005;
int n, m, y, a[maxN], b[maxN];
int ans = 2;		//答案初始化
map <int, int> M;

int main() {
    cin >> n >> y;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m >> y;
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    for (int k = 0; k < 30; k++) {
        int d = (1 << k);
        for (int i = 1; i <= n; i++) {
            M[a[i] % (2 * d)]++;	//计算能打到a[i]的，横坐标最小的激光发出点
            ans = max(ans, M[a[i] % (2 * d)]);
        }
        for (int i = 1; i <= m; i++) {
            M[(b[i] + d) % (2 * d)]++;//计算能打到b[i]的，横坐标最小的激光发出点
            ans = max(ans, M[(b[i] + d) % (2 * d)]);
        }
        M.erase(M.begin(), M.end());	//每次刷新map，防止枚举不同d时重复计算
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：forest114514 (赞：0)

### CF1041F Ray in the tube

思维题，显然 $y1,y2$ 对本题没用，我们只关心光束再对面的投影的横坐标变化量 $d$。

再仔细想想，发现最好的 $d$ 只有 $1$，$2$，$4$，$...$，$2^i$ 这些取值，其他所有取值取得的点一定是上述某一取值取到的点的子集。

对于每个 $2^i$ 加上对面的对 $2^i$ 取模同于的数即对  $2^{i+1}$ 取模余 $(mod+2^i)$ 和自己这边对 $2^{i+1}$ 取模同于的数，开个 unordered_map 即可。

> 小细节，还要开个离散化的桶记录每个横坐标的点的个数，再对答案取 max。

时间复杂度为 $O(N\log V)$。

CODE：

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
#define re register
#define il inline
#define gc() getchar()
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define repp(i,a,b) for(re int i=a;i<b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
#define tep(i,x) for(re int i=head[x];~i;i=ne[i])
#define ls(x) x<<1
#define rs(x) x<<1|1
#define eps (1e-9)
#define inf 0x3f3f3f3f
#define INF 1e18+100
#define pii pair<int,int>
#define mp(i,j) make_pair(i,j)
#define pb push_back
#define fi first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
template<typename T> inline void read(T &x){
	bool f=1;x=0;char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=0;ch=gc();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch&15),ch=gc();
	x=f?x:-x;
}
template<typename T> inline void write(T x){
	if(x<0) putchar('-'),x=-x;
   	if(x>9) write(x/10);
   	putchar(('0'+x%10));
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
template<typename T> inline void write(T x,char c){write(x),putchar(c);}
const int N=2e5+100;
struct NODE{
	int x,op;
	bool operator<(const NODE &T)const{
		return x<T.x;
	}
}a[N];
unordered_map<int,int> t,cnt[2][35];
int n,m,p,ans,tot;
signed main(){
	//ios::sync_with_stdio(false);
	//cin.tie(0);cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n,p);
	rep(i,1,n) read(a[i].x),a[i].op=0,t[a[i].x]++,ans=max(t[a[i].x],ans);
	read(m,p);
	rep(i,1,m) read(a[i+n].x),a[i+n].op=1,t[a[i+n].x]++,ans=max(t[a[i+n].x],ans);
	tot=n+m;
	sort(a+1,a+1+tot);
	rep(t,0,30){
		rep(i,1,tot){
			int op=a[i].op,x=a[i].x%(1<<(t+1));
			cnt[op][t][x]=cnt[op][t][x]+1;
			int val=cnt[op][t][x]+cnt[op^1][t][(x+(1<<t))%(1<<(t+1))];
			ans=max(val,ans);
		}
	}
	write(ans,'\n');
	return 0;
}
```



---

## 作者：Leasier (赞：0)

首先注意到 $y_1, y_2$ 没用，因为这玩意对斜率没有限制。

来考虑暴力怎么做：枚举一个半周期长度 $l$，则把所有 $a_i \bmod 2l, (b_i + l) \bmod 2l$ 中出现次数最多者的出现次数即为当前 $l$ 对应的答案。

但是本题中值域达到了 $10^9$，直接枚举 $l$ 显然不能通过。

考虑哪些 $l$ 可能作为最优解对应的 $l$。一个直观的想法是：如果一个 $l$ 所取到的点集都是另一个 $l'$ 的子集，则这个 $l$ 一定不优。

手画一下会发现 $\forall k \bmod 2 = 1$，$lk$ 一定不优于 $l$，于是我们把所有 $2$ 的幂抓出来讨论即可。时间复杂度为 $O(n \log n \log \max(a_i, b_i))$。

注意要特判 $l = 0$ 的情况。~~要不然会 WA on test 79。~~

代码：
```cpp
#include <iostream>
#include <map>

using namespace std;

int a[100007], b[100007];
map<int, int> mp;

int main(){
	int n, y1, m, y2, ans = 0;
	cin >> n >> y1;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
		ans = max(ans, ++mp[a[i]]);
	}
	cin >> m >> y2;
	for (int i = 1; i <= m; i++){
		cin >> b[i];
		ans = max(ans, ++mp[b[i]]);
	}
	for (int i = 0; i <= 29; i++){
		int cur_ans = 0, x = 1 << i, y = x << 1;
		mp.clear();
		for (int j = 1; j <= n; j++){
			cur_ans = max(cur_ans, ++mp[a[j] % y]);
		}
		for (int j = 1; j <= m; j++){
			cur_ans = max(cur_ans, ++mp[(b[j] + x) % y]);
		}
		if (ans < cur_ans) ans = cur_ans;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：nomonick (赞：0)

[CF1041F Ray in the tube](https://www.luogu.com.cn/problem/CF1041F)

原题链接：[Codeforces Round #509 (Div. 2)F. Ray in the tube](https://codeforces.com/problemset/problem/1041/F)

这道题目对于镜面反射的激光，可以看作是一个函数，他是有一个变化周期的，是一个三角形，他的底边是一定的，所以不需要考虑来回折射，抽象成在一个点上向前迈步即可。

其次，提到了变化是周期性的，所以步幅一定是 $2 \times x$ 的形式，就可以表示成一个偶数和一个数的积，所以只要枚举偶数即可，而偶数一定可以列成 $2^i$ 的形式。

最后注意一种特殊情况，其上下两个镜面的给定点横坐标相同，也就意味着可以上下弹射。所以如果有这样的情况答案一定大于等于二

没注意题目，窝把上镜面设成了下镜面。

# code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1e5 + 50;

inline int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}

int n,y_1,y_2,m,ans;
int id1[SIZE],id2[SIZE];
bool flat;
std::map<int, bool> vis;

inline void solve(int u)
{
	std::map<int, int> m_up,m_down;
	int mod = 1 << u + 1;
	for (int i = 1; i <= n; ++i)
	{
		m_up[id1[i] % mod]++;
	}
	for (int i = 1; i <= m; ++i)
	{
		m_down[id2[i] % mod]++;
	}
	for (int i = 1; i <= n; ++i)
	{
		ans = max(ans,m_up[id1[i] % mod] + m_down[(id1[i] + (1 << u)) % mod]);
	}
	for (int i = 1; i <= m; ++i)
	{
		ans = max(ans,m_down[id2[i] % mod] + m_up[(id2[i] + (1 << u)) % mod]);
	}
}

int main()
{
	n = read(),y_1 = read();
	for (int i = 1; i <= n; ++i)
	{
		vis[id1[i] = read()]  = true;
	}
	m = read();y_2 = read();
	for (int i = 1; i <= m; ++i)
	{
		id2[i] = read();
		if (vis[id2[i]])
		{
			flat = true;
		}
	}
	for (int i = 0; i <= 30; ++i)
	{
		solve(i);
	}
	ans = (flat ? max(ans,2) : ans);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

可以发现如果步长为d=a*b，a为奇数，b为偶数，那么存在步长为b的更优方案（可以包含之前所有的）

于是枚举步长（无奇数因子，即步长为2^k），在同余情况下会被选到（y轴略微特殊）

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=2e5+5;
int n,m,t,tot,ans,pre,a[N],tmp[N];
inline void init(){
	n=read(); t=read();
	for (int i=1;i<=n;i++) a[i]=read();
	m=read(); tot=n+m; t=read();
	for (int i=n+1;i<=tot;i++) a[i]=read();
}
inline void solve(){
	ans=2; tmp[tot+1]=2e9;
	for (int i=1;i<=1e9;i<<=1){
		int mod=i<<1;
		for (int j=1;j<=n;j++) tmp[j]=a[j]%mod;
		for (int j=n+1;j<=tot;j++) tmp[j]=(a[j]+i)%mod;
		sort(tmp+1,tmp+1+tot);
		for (int j=1,pre=1;j<=tot;j++)
			if (tmp[j]!=tmp[j+1]) ans=max(ans,j-pre+1),pre=j+1; 
	}
	writeln(ans);	
}
int main(){
	init(); solve();
	return 0;
}
```

---

## 作者：yellow_bored (赞：0)

# [Ray](https://www.luogu.com.cn/problem/CF1041F)
## $interesting$
### 前言
这是一道很有意思的题。
### 简化
这题主要就是两步简化。   
$1.$题目中给出了$y1,y2$。但性感思考一下，这个$y1,y2$是没有用的。   
$2.$激光一定是以某个角度射出的，如果去算这个角度是比较麻烦的，但是可以发现，因为反射角等于入射角。所以把激光看做函数的话，它是有周期的，可以形象地把周期看作步幅（即从下平面到上平面再到下平面的过程）。  
但就算变成了步幅也是不可以暴力枚举的。不过有个比较显然的剪枝：  
首先，因为是一个周期，所以步幅一定是$x*2$的形式，就可以表示成一个偶数和一个奇数的积（把$x$拆开，注意$12$是拆为$4$和$3$而不是$12$和$1$）,所以只要枚举前一个偶数就好，不难发现这个偶数就是$2$的$k$次方。
### 复杂度，统计答案与实现
于是这题就结束了，只要枚举再枚举就好，复杂度$O(log1e9(n+m))$。
枚举一种步幅，再对于所有点统计答案，统计答案时用两个$map$分别记录上下平面的点在模步幅长度意义下相等的点（注意上下平面要错开半个步幅）。看了代码会很好理解。还要注意可能会有两点在一条与$y$轴平行的线上，所以要特判。    
```cpp
for(int i=1;i<=n;++i)
  {
    cntd[d[i]%md]++;
  }
for(int i=1;i<=m;++i)
  {
    cntu[u[i]%md]++;
  }
```


------------
```cpp
#include<cstdio>
#include<map> 
using namespace std;
int n,m,u[101010],d[110101],ans;
map<int,int> vis;
void work(int x)
{
	map<int,int> cntd,cntu;
	int md=1<<(x+1);
	for(int i=1;i<=n;++i)
	  {
	  	cntd[d[i]%md]++;
	  }
	for(int i=1;i<=m;++i)
	  {
	  	cntu[u[i]%md]++;
	  }
	for(int i=1;i<=m;++i)
	  {
	  	ans=max(ans,cntu[u[i]%md]+cntd[(u[i]+(1<<x))%md]);
	  }
	for(int i=1;i<=n;++i)
	  {
	  	ans=max(ans,cntd[d[i]%md]+cntu[(d[i]+(1<<x))%md]);
	  }
	
}
int main()
{
	int flag=0;
	int hh;
	scanf("%d%d",&n,&hh);
	for(int i=1;i<=n;++i)
	  scanf("%d",&d[i]),vis[d[i]]=1;
	scanf("%d%d",&m,&hh);
	for(int i=1;i<=m;++i)
	{
	  scanf("%d",&u[i]);
	  if(vis[u[i]]==1) flag=1;
        }
	for(int i=0;i<=30;++i)
	{
		work(i);
	}
	printf("%d",flag==1?max(ans,2):ans);
}
```


---

