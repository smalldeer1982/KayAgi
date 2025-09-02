# 京都観光 (Sightseeing in Kyoto)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2022/tasks/joisc2022_b



# 题解

## 作者：___OccDreamer___ (赞：3)

### 题意

$(i,j)\to(i,j+1)$ 的代价为 $a_i$，$(i,j)\to(i+1,j)$ 的代价为 $b_j$。求 $(1,1)\to(n,m)$ 的最小代价。

$2\leq n,m\leq 10^5,1\leq a_i,b_i\leq 10^9$。

### Solution

假设现在有一个 $3\times2$ 的矩形，设行号为 $x,y,z(x<y<z)$，列号为 $i,j(i<j)$。$(x,i)\to(z,j)$，有三种方案：

1. $(x,i)\to(x,j)\to(z,j):(j-i)a_x+(z-x)b_j$
1. $(x,i)\to(z,i)\to(z,j):(j-i)a_z+(z-x)b_i$
1. $(x,i)\to(y,i)\to(y,j)\to(z,j):(j-i)a_y+(y-x)b_i+(z-y)b_j$

如果选方案三，即第 $y$ 有用，则满足：

$$
\frac{a_x-a_y}{x-y}<\frac{b_j-b_i}{j-i}<\frac{a_y-a_z}{y-z}
$$

如果 $\frac{a_x-a_y}{x-y}>\frac{a_y-a_z}{y-z}$ 则一定不满足，所以有用的行 $(i,a_i)$ 一定在下凸壳上，列同理。

先处理出关于行和列的下凸壳，删除所有没用的行和列，接下来只用贪心的考虑前两种方案，如果选方案一，则满足：

$$
\frac{a_i-a_x}{x-i}<\frac{b_j-b_y}{y-j}
$$

最后合并两个凸壳，每次选最优的走。

时间复杂度：$O(n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define cout cerr
using namespace std;
const int N=1e5+5;
int n,m;
int A[N],B[N],la,lb;
ll a[N],b[N],ans;
int read() {
	int x=0,f=0;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return f?-x:x;
}
bool cmpa(int x,int y,int z) {
	return 1LL*(a[x]-a[y])*(x-z)<1LL*(a[x]-a[z])*(x-y);
}
bool cmpb(int x,int y,int z) {
	return 1LL*(b[x]-b[y])*(x-z)<1LL*(b[x]-b[z])*(x-y);
}
bool cmp1(int x,int y,int z,int w) {
	return 1LL*(a[x]-a[y])*(w-z)<1LL*(b[z]-b[w])*(y-x);
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) b[i]=read();
	A[++la]=1,B[++lb]=1;
	for(int i=2;i<=n;i++) {
		while(la>1&&cmpa(i,A[la],A[la-1])) la--;
		A[++la]=i;
	}
	for(int i=2;i<=m;i++) {
		while(lb>1&&cmpb(i,B[lb],B[lb-1])) lb--;
		B[++lb]=i;
	}
	int x=1,y=1;
	while(x<la||y<lb) {
		if(x==la||(y<lb&&cmp1(A[x],A[x+1],B[y],B[y+1]))) ans+=(B[y+1]-B[y])*a[A[x]],y++; 
		else ans+=(A[x+1]-A[x])*b[B[y]],x++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：iCostalymh (赞：2)

[打个广告先](https://www.cnblogs.com/Chronologika/p/17655171.html)

[AtCoder 题目链接](https://atcoder.jp/contests/joisc2022/tasks/joisc2022_b)

[Luogu 题目链接](https://www.luogu.com.cn/problem/AT_joisc2022_b)

观察题目，不自觉地想到了 dp，但是再一看 $\text{1e5}$ 数据范围，意识到大概是 $2^{\text{1e5}}$ 的复杂度，绝望了……

然后就很自然地想到了最优策略。（思路很巧妙但是我当时没想到。）

考虑有三行（或三列），分别记为 $i, j, k$，如果 $j > i \land j > k$（也就是一个峰），那么走 $j$ 显然不优，就可以把 $j$ 删去。

维护的话可以考虑用优先队列把行和列维护在一起（当然也要同时维护是行还是列），乱搞就行了，复杂度 $O((h+w)\log(h+w))$，可以通过原题，但是可以被更大的数据卡掉。

那么就存在一种更优解。最开始的思路就是删峰，显然可以用单调队列维护凸包，分别维护行和列，看哪个最优先取哪个，直到两个单调队列都剩一个元素。复杂度是 $O(h+w)$。

代码挺好写的，就放个[链接](https://atcoder.jp/contests/joisc2022/submissions/44896696)吧。我写的是不带 $\log$ 的。

---

## 作者：Mirasycle (赞：1)

考虑 $(l,x)\to(r,y)$ 的路径可以 $(l,x)\to (r,x)\to (r,y)$，也可以 $(l,x)\to (l,y)\to (r,y)$。

前者的代价是 $b_x(r-l)+a_r(y-x)$，后者的代价是 $a_l(y-x)+b_y(r-l)$。前者比后者更优需要满足

$$\dfrac{b_x-b_y}{x-y}<\dfrac{a_r-a_l}{r-l}$$

可以发现这可以放到两个凸包上求解。单调栈建立对于 $a,b$ 的凸包之后，每次选择斜率写的一边走。由于上述式子可以放到到任意局部，所以这是对的。

其实本质就是对于两个凸包进行闵可夫斯基和。


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int n,m,a[maxn],b[maxn]; ll ans=0;
int sta[maxn],stb[maxn],ta,tb;
bool chk(int x1,int y1,int x2,int y2){ return 1ll*y1*x2<=1ll*y2*x1; }
bool cmpa(int x,int y,int z){ return chk(x-y,a[x]-a[y],y-z,a[y]-a[z]); }
bool cmpb(int x,int y,int z){ return chk(x-y,b[x]-b[y],y-z,b[y]-b[z]); }
bool cmpab(int w,int x,int y,int z){ return chk(w-x,a[w]-a[x],y-z,b[y]-b[z]); }
int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	sta[ta=1]=1; stb[tb=1]=1;
	for(int i=2;i<=n;i++){
		while(ta>1&&cmpa(i,sta[ta],sta[ta-1])) ta--;
		sta[++ta]=i;
	}
	for(int i=2;i<=m;i++){
		while(tb>1&&cmpb(i,stb[tb],stb[tb-1])) tb--;
		stb[++tb]=i;
	}
	int x=1,y=1;
	while(x<ta||y<tb){
		if(x==ta){
			ans+=1ll*(m-stb[y])*a[sta[x]];
			break;
		}
		if(y==tb){
			ans+=1ll*(n-sta[x])*b[stb[y]];
			break;
		}
		if(cmpab(sta[x+1],sta[x],stb[y+1],stb[y])){
			ans+=1ll*(sta[x+1]-sta[x])*b[stb[y]];
			x++;
		}else{
			ans+=1ll*(stb[y+1]-stb[y])*a[sta[x]];
			y++; 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hhhqx (赞：0)

从 [luogu - P9521 [JOISC2022] 京都观光](https://www.luogu.com.cn/problem/P9521) 过来的……

**超級抽象的贪心题。**

考虑三种走法：设 $x<y<z$ 和 $l<r$。

- $(x,l)$ 到 $(z,l)$ 再到 $(z,r)$。
- $(x,l)$ 到 $(x,r)$ 再到 $(z,r)$。
- $(x,l)$ 到 $(y,l)$ 再到 $(y,r)$ 再到 $(z,r)$。

列出每一种走法的代价，一三比较 + 二三比较，可以得到不等式：$\frac{a_y - a_x}{y - x} < \frac{b_r - b_l}{r - l} < \frac{a_z - a_y}{z - y}$。

所以只有 $\frac{a_y - a_x}{y - x} < \frac{a_z - a_y}{z - y}$ 才可能用到第三种走法。对于 $b$ 也是一样的推导。

由于任意最优路径中间的三个 $x,y,z$ 都是第三种走法，上面的结论即：最优路径中斜率递增。

贪心地，我们只维护下凸壳，因为每个凸壳内部的点都可以被替代且更优。

只用维护 $a,b$ 的下凸壳，具体每次是走第一种还是第二种，就需要再推一下式子（直接列出来，然后不等式不断移项），得到：如果 $\frac{b_r - b_l}{r - l} < \frac{a_z - a_x}{z - x}$ 就第二种。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using ULL = unsigned long long;
using PII = pair<int, int>;

const int MAXN = 1e5 + 3;

int n, m;
int a[MAXN], b[MAXN];
int ha = 1, ta = 0, dqa[MAXN];
int hb = 1, tb = 0, dqb[MAXN];

bool check_a(int x, int y, int z){
	return LL(a[y] - a[x]) * (z - y) < LL(a[z] - a[y]) * (y - x);
}
bool check_b(int x, int y, int z){
	return LL(b[y] - b[x]) * (z - y) < LL(b[z] - b[y]) * (y - x);
}
bool check_ab(int i, int j, int x, int y){
	return LL(a[j] - a[i]) * (y - x) >= LL(b[y] - b[x]) * (j - i);
}

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int i = 1; i <= m; i++){
		cin >> b[i];
	}
	for(int i = 1; i <= n; i++){
		while(ha < ta && !check_a(dqa[ta - 1], dqa[ta], i)) ta--;
		dqa[++ta] = i;
	}
	for(int i = 1; i <= m; i++){
		while(hb < tb && !check_b(dqb[tb - 1], dqb[tb], i)) tb--;
		dqb[++tb] = i;
	}
	LL ans = 0;
	while(ha < ta || hb < tb){
		if(ha == ta || (hb < tb && check_ab(dqa[ha], dqa[ha + 1], dqb[hb], dqb[hb + 1]))){
			ans += LL(dqb[hb + 1] - dqb[hb]) * a[dqa[ha]];
			hb++;
		}else{
			ans += LL(dqa[ha + 1] - dqa[ha]) * b[dqb[hb]];
			ha++;
		}
	}
	cout << ans;
	return 0;
}
```
参考题解：https://blog.csdn.net/cqbzlydd/article/details/130562472 & https://www.luogu.com.cn/article/ycf2xhx6

---

