# Dyn-scripted Robot (Easy Version)

## 题目描述

这是该问题的简单版本。唯一的区别在于本版本中 $k \le n$。只有当你同时解决了两个版本的问题时，才能进行 hack。

给定一个 $w \times h$ 的矩形，位于 $Oxy$ 平面上，左下角为点 $(0, 0)$，右上角为点 $(w, h)$。

你还有一个初始位于点 $(0, 0)$ 的机器人，以及一个长度为 $n$ 的脚本 $s$。脚本 $s$ 由 $n$ 个字符组成，每个字符为 L、R、U 或 D，分别表示机器人向左、右、上、下移动。

机器人只能在矩形内部移动；如果尝试越界，则会按如下方式修改脚本 $s$：

- 如果尝试越过垂直边界，则将所有的 L 字符变为 R，所有的 R 字符变为 L。
- 如果尝试越过水平边界，则将所有的 U 字符变为 D，所有的 D 字符变为 U。

然后，机器人会从无法执行的那个字符开始，执行修改后的脚本。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/ff49f6aa11a19418f77260f4c00c02fa1a42de65.png)  
这是机器人的移动过程示例，$s = \texttt{"ULULURD"}$。

脚本 $s$ 会被连续执行 $k$ 次。所有对字符串 $s$ 的修改在重复执行时都会保留。在这个过程中，机器人总共会有多少次到达点 $(0, 0)$？注意，初始位置不计入。

## 说明/提示

在第一个测试用例中，机器人只会向上和向右移动。最终停在 $(2, 2)$，但从未到达 $(0, 0)$，所以答案为 $0$。

在第二个测试用例中，每次执行脚本时，机器人会两次到达原点。由于 $k=2$，所以总共到达原点 $2 \cdot 2 = 4$ 次。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/4c04dc66914a3e1ee672ced7111b24a5891eec80.png)  
在第三个测试用例中，示意图如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1993F1/354b17fd45a6d2914b35f5325993193690563e94.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 2 2 2
UR
4 2 1 1
LLDD
6 3 3 1
RLRRRL
5 5 3 3
RUURD
7 5 3 4
RRDLUUU```

### 输出

```
0
4
3
0
1```

# 题解

## 作者：_LSA_ (赞：4)

# Solution(Easy Version)
注：参考了官方题解

我们发现每次碰到边界反转不好维护，于是我们不考虑反转，让它走出边界，再考虑它对应原矩形的哪个点。

显然行和列两个方向是独立的，我们接下来从讨论列的方向上来讨论。

我们先从简单的情况开始，令 $R$ 表示每次遇到边界**都**反转操作的机器人，$B$ 为遇到边界**不**反转操作的机器人，当他们即将越出上边界 $H$ ，而下一个操作又是往上走时，$R$ 会反转操作往下走，而 $B$ 会继续往上走，接下来在 $R$ 没有碰到下一个边界之前，我们发现，它们经过的路径是关于上边界 $H$ 成**镜像**的。

接下来如果 $B$ 继续向上走，走到 $2H$，再继续往上走，对应的，$R$ 将走到 $0$，反转为原来的操作，也继续往上走，那么它们接下来的操作将是一样的，而它们的坐标差为 $2H$。

同理当 $B$ 走到 $3H$ 时，它们的操作又会成镜像，走到 $4H$ 时，它们操作又会相同而坐标差变为 $4H$，走到 $0$ 以下，$-H$ 以下也是同理。于是我们可以归纳出以下性质：$R$ 的纵坐标 $y$ 与 $y$ 模 $2H$ 意义下同余的坐标是等价的。

横坐标也是同理，$x$ 与 $x \bmod 2H$ 是等价的。

那么我们把矩形扩大到 $2W\times 2H$，就可以在这个范围内维护出 $B$ 的运动轨迹。

回到题意，题目要求经过点 $(0,0)$ 的次数，我们发现，刚好当且仅当在 $B$ 也经过 $(0,0)$ 时，$R$ 才经过 $(0,0)$。

我们可以处理出 $B$ 沿着操作走一次的终止位置 $(x,y)$，并统计每个点经过多少次。令 $x_i=(i-1)x \bmod 2W,y_i=(i-1)y \bmod 2H$，那么第 $i$ 轮操作的起始位置就在 $(x_i,y_i)$，这轮操作走到 $(0,0)$ 的次数实际上就是第一轮操作走到 $(2W-x_i,2H-y_i)$ 的次数，由于本题 $k$ 较小，直接枚举当前是第几轮即可通过。

如果用 $\text{map}$ 维护每个点经过次数的话，时间复杂度为 $O((n+k)\log n)$。
# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
using namespace std;
ll read(){
    ll X = 0,r = 1;
    char ch = getchar();
    while(!isdigit(ch) && ch != '-') ch = getchar();
    if(ch == '-') r = -1,ch = getchar();
    while(isdigit(ch)) X = X*10+ch-'0',ch = getchar();
    return X*r;
}
const int N = 1e6+10;
int n,k,w,h;
char s[N];
map<pii,int> mp;
int main(){
    int T = read();
    while(T--){
        n = read(); k = read();
        w = read()*2; h = read()*2;
        cin >> (s+1);
        mp.clear();
        int x = 0,y = 0;
        for(int i=1;i<=n;i++){
            if(s[i] == 'U') y++;
            if(s[i] == 'D') y--;
            if(s[i] == 'L') x--;
            if(s[i] == 'R') x++;
            x = (x+w)%w;
            y = (y+h)%h;
            mp[mk(x,y)]++;
        }
        ll ans = 0;
        x = w-x; y = h-y;
        for(int i=0;i<k;i++){
            int nx = 1ll*i*x%w,
                ny = 1ll*i*y%h;
            ans += mp[mk(nx,ny)];
        }
        cout << ans << "\n";
    }
    return 0;
}


```

---

## 作者：Engulf (赞：1)

记题目中的机器人是 $A$，考虑一个不受约束的机器人 $B$。它严格按照脚本行走，不管那个矩形边界，**所以也就不会修改脚本**。

在机器人 $A$ 碰到矩形边界前，$A$ 和 $B$ 行进路线重合。

考虑 $A$ 走到矩形顶部，且收到了 $\tt U$ 的指令，此时 $B$ 继续向上，而 $A$ 向下，且之后的 $\tt U$ 指令都变为了 $\tt D$。发现此时 $A$ 和 $B$ 是关于直线 $y = h$ 对称的。

$A$ 不再向上，而是全部向下。若 $A$ 碰到了 $x$ 轴，且当前指令（修改后的脚本）是 $\tt D$，它又向上了，且之后的 $\tt D$ 指令变为 $\tt U$。设 $A(x, 0)$，因为 $A, B$ 关于直线 $y = h$ 对称，所以此时的 $B(x, 2h)$，且现在 $A, B$ 方向一致。同理，$A$ 向上，向下，又碰到 $x$ 轴，此时 $B(x, 4h)$，如此往复，发现 $A$ 在 $x$ 轴时，$B$ 就在 $(x, y), y \bmod 2h = 0$ 上。

发现了这个，向下，向左，向右都是同理可得了。所以，问题转化为，在 $B$ 经过的点 $(x, y)$ 中有多少个满足 $x \bmod 2w = 0, y \bmod 2h = 0$。

设第一次按照脚本移动 $j$ 步后，$B$ 停留在 $(x_j, y_j)$。所以第一次脚本执行结束 $B$ 停在 $(x_n, y_n)$。

重复执行 $i$ 次脚本，相当于平移了 $i - 1$ 次，所以重复执行第 $i$ 次脚本的第 $j$ 步后的坐标就是 $(x_j + ix_n, y_j + iy_n), i \in [0, k - 1]$。现在要求满足

$$\left\{\begin{matrix}
x_j + ix_n \equiv 0 (\bmod 2w) \\
y_j + iy_n \equiv 0 (\bmod 2h)
\end{matrix}\right. i \in [0, k - 1]$$

的 $(x_j, y_j)$ 对数。

移项

$$\left\{\begin{matrix}
x_j \equiv -ix_n (\bmod 2w) \\
y_j \equiv -iy_n (\bmod 2h)
\end{matrix}\right. i \in [0, k - 1]$$

执行一遍脚本，得到所有 $(x_j, y_j)$ 和 $(x_n, y_n)$，用 map 记录下来，从 $0$ 到 $k - 1$ 枚举 $i$，在 map 里查找 $(-ix_n, -iy_n)$ 即可，记得分别对 $2w,2h$ 取模。

时间复杂度 $O(n + k)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n, k, w, h;
        string script;
        cin >> n >> k >> w >> h >> script;

        int x = 0, y = 0;
        map<pii, int> mp;
        for (auto c: script) {
            if (c == 'L') x--;
            if (c == 'R') x++;
            if (c == 'U') y++;
            if (c == 'D') y--;

            mp[{(x % (2 * w) + (2 * w)) % (2 * w), (y % (2 * h) + (2 * h)) % (2 * h)}]++;
        }

        ll ans = 0;
        for (ll i = 0; i < k; i++)
            ans += mp[{((-i * x) % (2 * w) + (2 * w)) % (2 * w), ((-i * y) % (2 * h) + (2 * h)) % (2 * h)}];

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1993F1)

## 题意

在平面直角坐标系中，机器人初始位于 $(0,0)$，有一段长度为 $n$ 的仅包含 $\texttt{DULR}$ 的操作序列 $s$，机器人将把此操作序列执行 $k$ 轮，要求机器人任意时刻的位置都必须在 $(0,0)-(h,w)$ 的矩形中，若按第 $i$ 个操作移动会超出矩形，那么若 $s_i$ 为 $\texttt{L/R}$，将 $s$ 中所有 $\texttt{L}$ 变成 $\texttt{R}$，所有 $\texttt{R}$ 变成 $\texttt{L}$；若 $s_i$ 为 $\texttt{U/D}$ 也同理。变换后再执行第 $i$ 个操作，注意变换对操作序列的影响会保留到下一轮。

求机器人在移动过程中经过 $(0,0)$ 的次数（不包括初始状态）。

数据范围：$t$ 为数据组数，$1 \le t \le 10^4,1 \le \sum n,w,h \le 10^6,1 \le k \le n$。

由于神秘原因，本题解的 $h,w$ 对应原题中的 $w,h$。

## 分析

场上想不出 F1 的简单做法，但会了 F2，然而由于时间原因最终没有调出来。

先考虑一个简单的转化：带限制走到 $(0,0)$ 相当于不带限制走到 $(2ah,2bw)\ (a,b\in \mathbb{Z})$。

简单证明一下，假设一次 $\texttt{U}$ 时超出了矩阵，那么 $\texttt{L,R}$ 不受影响，若不改变操作序列，则相当于把走到 $(0,0)$ 改为了走到 $(0,2w)$；$\texttt{D,L,R}$ 也以此类推，所以转化成立。

于是问题要求经过 $(2ah,2bw)\ (a,b\in \mathbb{Z})$ 的次数，显然一轮后的位移是固定的，令其为 $(X,Y)\ (0\le X< 2h,0\le Y<2w)$，所以我们枚举一轮中第 $i$ 个操作作为结尾，设第一轮中第 $i$ 次操作后位于 $(x_i,y_i)$，那么在第 $j+1\ (0\le j\le k-1)$ 轮中机器人位于 $(x_i+jX,y_i+jY)$。

先将 $x,y$ 分开考虑，那么 $x_i+jX=2ah,y_i+jY=2bw$。

可以转化为同余方程 $jX\equiv -x_i\pmod {2h},jY\equiv -y_i\pmod {2w}$，用两次 $\texttt{exgcd}$ 分别算出两个方程的通解，再用一次 $\texttt{exgcd}$ 合并即可。

时间复杂度 $O(n\log k)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define PY puts("YES")
#define PN puts("NO")
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch))
	{if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e6+10;
int t,n,h,w;
ll k,ans; 
string s;
int fx[4]={0,0,-1,1};
int fy[4]={-1,1,0,0};
struct Node{
	int x,y;
}a[N];
Node forward(Node p,int t){
	return (Node){p.x+fx[t],p.y+fy[t]};
}
int turn(char c){
	if(c=='D')return 0;
	if(c=='U')return 1;
	if(c=='L')return 2;
	return 3;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
    if(!b){
        x=1;y=0;
        return a;
    }
    long long d=exgcd(b,a%b,x,y);
    long long z=x;x=y;y=z-y*(a/b);
    return d;
}
ll solve(Node p,ll k){
	int vv=(p.x==0&&p.y==0);
	p.x=h-p.x;p.y=w-p.y;
	ll hx0,hy0,hd,hB;
	hd=exgcd(a[n].x,h,hx0,hy0);
	if(p.x%hd)return vv;
	hB=h/hd;
	hx0*=p.x/hd;hx0=(hx0%hB+hB)%hB;
	ll wx0,wy0,wd,wB;
	wd=exgcd(a[n].y,w,wx0,wy0);
	if(p.y%wd)return vv;
	wB=w/wd;
	wx0*=p.y/wd;wx0=(wx0%wB+wB)%wB;
	ll x0,y0,d,B,xy;
	if(wx0<hx0)swap(wx0,hx0),swap(hB,wB);
	xy=(wx0-hx0)%wB;
	d=exgcd(hB,wB,x0,y0);
	if(xy%d)return vv;
	B=wB/d;
	x0*=xy/d;x0=(x0%B+B)%B;
	ll u=k-hx0;if(u<0)return vv;
	u=(u/hB-x0);if(u<0)return vv;
	u/=B;
	return u+vv+(x0*hB+hx0!=0&&x0*hB+hx0<=k);
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	t=read();
	while(t--){
		cin>>n>>k>>h>>w>>s;
		a[0]=(Node){0,0};
		h*=2;w*=2;
		for(int i=1;i<=n;i++){
			a[i]=forward(a[i-1],turn(s[i-1]));
			a[i].x=(a[i].x%h+h)%h;
			a[i].y=(a[i].y%w+w)%w;
		}
		ans=0;
		for(int i=1;i<=n;i++)
			ans+=solve(a[i],k-1);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

首先需要一个关键结论，所谓碰壁后翻转操作序列，实际上等价于碰壁后不做改变继续操作，但是走到的所有形如 $(2 \times l_1 \times w,2 \times l_2 \times h)$ 的位置都与位置 $(0,0)$ 等价。

考虑枚举是在某次执行中的第几次操作带来的贡献，也就是时间对 $n$ 取模后的余数，我们假定这个值为 $i$。

加入已经操作了 $k$ 次，那么当前走到的点就是 $(k \times \Delta_x,k \times \Delta_y)$，这里 $\Delta x,\Delta y$ 分别表示一次执行带来的位置偏移量，令 $\delta_x,\delta_y$ 表示考虑一次执行的前 $i$ 个操作带来的位置偏移量，那么其可以产生贡献当且仅当 $k \times \Delta_x + \delta_x \bmod 2 \times w = 0$ 且 $k \times \Delta_y + \delta_y \bmod 2 \times h = 0$，解两个同余方程得到关于 $k$ 的两个同余方程，再使用扩展中国剩余定理合并同余方程即可计数。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+114;
#define int long long
int n,k;
int deltax[maxn],deltay[maxn];
int w,h;
int exgcd(int a,int b,int &x,int &y){
    //ax+by=gcd(a,b)
	bool flag=false;
	if(a<b) swap(a,b),flag=true;
    if(b==0){
        x=1;
        y=0;
		if(flag==true) swap(x,y);
        return a;
    }else{
        int k=a/b;
        int d=exgcd(b,a%b,y,x);
        y-=k*x;
		if(flag==true) swap(x,y);
        return d;
    }
}
int mul(int a,int b,int c){
	int res=0,sum=a;
	for(int i=0;i<63;i++){
		if((1ll<<i)&b) res=(res+sum)%c;
		sum=(sum+sum)%c;
	}
	return res;
}
void work(){
    int answer=0;
    cin>>n>>k>>w>>h;
    w*=2;
    h*=2;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        if(c=='L') deltax[i]=deltax[i-1]-1,deltay[i]=deltay[i-1];
        if(c=='R') deltax[i]=deltax[i-1]+1,deltay[i]=deltay[i-1];
        if(c=='U') deltax[i]=deltax[i-1],deltay[i]=deltay[i-1]+1;
        if(c=='D') deltax[i]=deltax[i-1],deltay[i]=deltay[i-1]-1;
    }
    for(int i=1;i<=n;i++){
        if(deltax[i]<0) deltax[i]=(deltax[i]+n*w)%w;
        if(deltay[i]<0) deltay[i]=(deltay[i]+n*h)%h;
        if(deltax[i]>0) deltax[i]%=w;
        if(deltay[i]>0) deltay[i]%=h;
        if(deltax[i]==0) deltax[i]+=w;
        if(deltay[i]==0) deltay[i]+=h;
    }
    for(int i=1;i<=n;i++){
        //横坐标限制
        //k'*deltax[n] = (2*w)*y-detlax[i]
        int a=deltax[n],b=w,c=(w-deltax[i])%w;
        if(c%__gcd(a,b)!=0) continue;
        int x0=0,y0=0;
        exgcd(a,b,x0,y0);
        x0*=c/__gcd(a,b);
        y0*=c/__gcd(a,b);
        int stx=b/__gcd(a,b);
        int sty=a/__gcd(a,b);
        x0%=stx;
        //k'=x0+stx*L
        int M=stx,ans=x0;
        //纵坐标限制
        //k'*deltay[n] = (2*h)*y'-detlay[i]
        int A=deltay[n],B=h,C=(h-deltay[i])%h;
        if(C%__gcd(A,B)!=0) continue;
        int X0=0,Y0=0;
        exgcd(A,B,X0,Y0);
        X0*=C/__gcd(A,B);
        Y0*=C/__gcd(A,B);
        int stX=B/__gcd(A,B);
        int stY=A/__gcd(A,B);
        X0%=stX;
        //k'=X0+stX*L'
        //cout<<i<<' '<<x0<<' '<<stx<<' '<<X0<<' '<<stX<<'\n';
        int cc=((X0-ans)%stX+stX)%stX;
        int x=0,y=0;
        if(cc%__gcd(M,stX)!=0) continue;
		int g=exgcd(M,stX,x,y);
        int p=stX/g;
        x=mul(x,cc/g,p);
        ans+=x*M;
        M*=p;
        ans=(ans%M+M)%M;
        //cout<<ans<<' '<<M<<'\n';
        //k=L*M+ans;
        //L*M+ans<K
        if(k<ans) continue;
        answer+=(k-ans)/M+1-((k-ans)%M==0?1:0);
    }
    cout<<answer<<'\n';
}
signed main(){
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
1
5 6 3 3
RUURD
*/

```

---

