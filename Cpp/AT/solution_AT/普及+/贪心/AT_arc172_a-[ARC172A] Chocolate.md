# [ARC172A] Chocolate

## 题目描述

你有一个大小为 $H \times W$ 的格子状矩形，你需要判断是否能把它从格子处分成 $N$ 个正方形，满足第 $i$ 个正方形的边长为 $2^{A_i}$，可以有剩余。

## 样例 #1

### 输入

```
4 4 4
1 0 0 1```

### 输出

```
Yes```

## 样例 #2

### 输入

```
5 7 6
0 1 0 2 0 1```

### 输出

```
Yes```

## 样例 #3

### 输入

```
3 2 7
0 0 0 0 0 0 0```

### 输出

```
No```

## 样例 #4

### 输入

```
11 11 2
2 3```

### 输出

```
No```

## 样例 #5

### 输入

```
777 777 6
8 6 9 1 2 0```

### 输出

```
Yes```

# 题解

## 作者：小超手123 (赞：8)

##### 题意：

有一个长为 $H$，宽为 $W$ 的巧克力块，判断是否能沿竖线或横线划分成若干块，使得 $n$ 个朋友得到自己想要的大小，第 $i$ 个朋友想要 $2^{A_{i}} \times 2^{A_{i}}$ 大小的巧克力。

$H,W \le 10^9, n \le 1000, a_{i} \le 25$。

##### 分析：

显然这样分是最优的：

![](https://img.atcoder.jp/arc172/febd5ca3888ea98565ab5c404e62fc5c.png)

图片来自于 AtCoder。

即从大到小的开始分配，以从左到右，从上到下的顺序切。

感性理解一下，由于需求的矩阵都是为 $2^x$ 的正方形，这样搞能使得 $2^{x}$ 分完后，$2^{x-1}$ 能从边角料继续分。

如何模拟这个过程呢？

一种方法是，用个 vector 存所有零散的矩形，对于 $2^{A_{i}} \times 2^{A_{i}}$ 的正方形，随便从 vector 里找到一个能满足于其的矩形，挖掉左上角，又变成了两个矩形。时间复杂度 $O(n^2)$。

另一种方法是，合法情况当且仅当 $sum(x) \le \lfloor \frac{H}{2^{x}}  \rfloor 2^{x} \lfloor \frac{W}{2^{x}}  \rfloor2^{x}$，其中 $0 \le x \le 25$，$sum(x)$ 表示边长大于等于 $x$ 的需求的正方形的面积之和。时间复杂度 $O(n w)$，其中 $w=25$。 

---

## 作者：huhexuan (赞：6)

觉得题解的思路都有些繁琐。

我的思路是如果当前填入的面积中能填的当前枚举到的正方形个数超过能填的总个数，那就肯定不行，退出。

如果最后都没有退出，就可以。

从大到小排序以保证面积中能填的当前枚举到的正方形个数为整数，因为是 $2$ 的正整数次幂。

感性理解一下，如果当前填入的总面积中能填的当前枚举到的正方形个数超过能填的总个数，那无论如何，一定是放不下了。

而如果当前填入的总面积中能填的当前枚举到的正方形个数没超过能填的总个数，那一定能通过一些方式使它可以放得下。

而且对于当前正方形之前的每一个正方形，都可以放得下，因为还没有退出。

这时只考虑当前正方形即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int h,w,n,a[1005],ans;
signed main()
{
    cin>>h>>w>>n;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]=(1<<a[i]);
	sort(a+1,a+n+1,greater<int>());
	for(int i=1;i<=n;i++)
	{
		ans+=(a[i]*a[i]);
		if(ans/(a[i]*a[i])>(h/a[i])*(w/a[i]))
		{ 
			cout<<"No";
			return 0;
		}
	} 
	cout<<"Yes"; 
    return 0;
}

---

## 作者：Register_int (赞：6)

发现 $2^i\times 2^i$ 可以拆分成 $4$ 个 $2^{i-1}\times2^{i-1}$，所以先塞大的再将大的拆成小的一定不劣。

考虑直接贪心从最大的开始往里面塞。若当前塞到 $2^i\times2^i$，当前的空位大概是长这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/3t8nmf8w.png)

黑色是已经填的部分，红色是将要填的部分。首先，两边的空隙只能放一行一列的正方形，因为上一层的填不进去，说明宽度 $<2^{i+1}=2\times2^i$。容易发现，我们事实上是在分别对两边做二进制拆分，所以可以简单得出竖的空位与横的空位是否能放。若都能放要记得减去角上算重的块。

预处理完最多能放的个数后，我们将正方形数量按从大到小的顺序进行比较。如果放不下了，直接无解。否则将剩下的空位分成更小的正方形即可。时间复杂度 $O(n+\log HW)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e3 + 10;

int h, w, x, y, n, a[MAXN], cnt[26];

ll num[30];

int main() {
	scanf("%d%d%d", &h, &w, &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]]++;
	for (int i = 29; ~i; i--) {
		if (h >> i & 1) num[i] += w >> i;
		if (w >> i & 1) num[i] += h >> i;
		if ((h & w) >> i & 1) num[i]--;
	}
	for (int i = 29; ~i; i--) {
		if (num[i] < cnt[i]) return puts("No"), 0;
		if (i) num[i - 1] += num[i] - cnt[i] << 2;
	}
	puts("Yes");
}
```

---

## 作者：_cmh (赞：4)

纵览题解区，发现做法均较为繁琐，这里提供一种较为简洁的做法。

对于放入最多的正方形，我们不难想到，优先考虑放入最大的正方形显然不劣。

观察整个过程，发现每次放入当前最大的正方形后，总会把原先的矩形分成两个块。故我们考虑使用优先队列维护每个块的长宽。

显然我们需要最大化一个块的长宽，使其可以满足接下来最大正方形的需求。假设我们记录当前最大块的长宽分别为 $H,W\ (H>W)$，最大正方形边长为 $A$，则根据最大化最大块长和宽的思想，我们在放入该正方形后此块被分割为 $(H-A)\times W$ 和 $(W-A)\times A$ 两个块，将其放入优先队列中。

重复此过程，若出现有正方形边长大于最大块的宽，则方案不合法，否则合法。

具体实现可以参考以下代码：

```cpp
#include<bits/stdc++.h>
#define A(a,b) Q.push(make_pair(a<b?a:b,a>b?a:b));
using namespace std;

const int N=1e3+3;
int a[N];
priority_queue<pair<int,int> >Q;

int main(){
	int p,q,n; scanf("%d%d%d",&p,&q,&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),a[i]=1<<a[i];
	sort(a+1,a+n+1,greater<int>()); A(p,q);
	for(int i=1;i<=n;i++){
		if(a[i]>Q.top().first){
			puts("No");
			return 0;
		}
		pair<int,int> now=Q.top(); Q.pop();
		A(now.first-a[i],a[i]);
		A(now.second-a[i],now.first);
	}
	puts("Yes");
}
```

---

## 作者：XYQ_102 (赞：1)

## A - Chocolate

> Ms. AtCoder has decided to distribute chocolates to $N$ friends on Valentine's Day. For the $i$-th friend $(1 \leq i \leq N)$, she wants to give a square chocolate bar of size $2^{A_i} \times 2^{A_i}$.
> 
> She has procured a rectangular chocolate bar of size $H \times W$. It is partitioned by lines into a grid of $H$ rows and $W$ columns, each cell being a $1 \times 1$ square.
> 
> Determine whether it is possible to divide the chocolate bar along the lines into several pieces to obtain all the chocolate bars for her friends. It is fine to have leftover pieces.
> 
> $1 \le H,W \le 10^9,1 \le N \le 1000,1 \le A_i \le 25$

赛时愣了半天不敢写，感觉非常抽象，小细节错了还交了一发罚时。

感觉首先需要考虑这里的 $2^{A_i}$ 的用意，不然为什么不是任意一个整数呢？

容易发现，对于一个边长为 $2$ 的幂次的正方形，你用这样的方块去填，样都填的满。

具体来说，对于每一个这样的正方形，只要你填进去的面积 **小于等于** 正方形的面积，你就不需要关心怎么填的问题了，

因为一定有一种方案是可以放下的，这运用到了 $2$ 的幂的性质，可以手玩一下。

于是对于这个 $H \times W$ 的长方形，我们尝试把它分成这样的边长 $2^x$ 的正方形。

显然正方形越大越好，（因为可以放下更大的方块）。

于是我们以一边为基准，以它的二进制为例不断往下分就可以了，容易发现这样一定更优。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

const int N=1e6+5;
int n,H,W,c[30];
ll S=0;

void calc(int x,ll Sum){
  if(!n) return ;
  for(int i=x;i>=0;i--){
    ll nw=(1ll<<i)*(1ll<<i);
    ll tmp=min(1ll*c[i],Sum/nw);
    Sum-=1ll*nw*tmp,c[i]-=tmp,n-=tmp;
    if(!Sum) break;
  }
}

void sol(){
  cin>>H>>W>>n;
  for(int i=1,x;i<=n;i++) cin>>x,c[x]++,S+=1ll*(1ll<<x)*(1ll<<x);
  if(H>W) swap(H,W);
  for(int i=29;i>=0;i--){
    int len=(1ll<<i),w=W;
    if(len<=H){
      calc(i,1ll*len*len*(w/len));
      w-=1ll*(w/len)*len;
      for(int j=i;j>=0;j--)
        if(w>=(1ll<<j)) calc(j,1ll*len*(1ll<<j)),w-=(1ll<<j);
      H-=len;
    }
  }
  if(!n) cout<<"Yes\n";
  else cout<<"No\n";
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  sol();
  return 0;
}
```

---

## 作者：XYQ_102 (赞：1)

## 思路
感觉首先需要考虑这里的 $2^{A_i}$ 的用意，不然为什么不是任意一个整数呢？

容易发现，对于一个边长为 $2$ 的幂次的正方形，你用这样的方块去填都填的满。

具体来说，对于每一个这样的正方形，只要你填进去的面积小于等于正方形的面积，你就不需要关心怎么填的问题了，因为一定有一种方案是可以放下的，这运用到了 $2$ 的幂的性质。

对于这个 $H\times W$ 的长方形，我们尝试把它分成这样的边长 $2^x$ 的正方形。

因为可以放下更大的方块，所以正方形越大越好。

于是我们以一边为基准，以它的二进制为例不断往下分就可以了，容易发现这样一定更优。

时间复杂度 $\Theta(\log H\times\log W)$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

const int N=1e6+5;
int n,H,W,c[30];
ll S=0;

void calc(int x,ll Sum){
  if(!n) return ;
  for(int i=x;i>=0;i--){
    ll nw=(1ll<<i)*(1ll<<i);
    ll tmp=min(1ll*c[i],Sum/nw);
    Sum-=1ll*nw*tmp,c[i]-=tmp,n-=tmp;
    if(!Sum) break;
  }
}

void sol(){
  cin>>H>>W>>n;
  for(int i=1,x;i<=n;i++) cin>>x,c[x]++,S+=1ll*(1ll<<x)*(1ll<<x);
  if(H>W) swap(H,W);
  for(int i=29;i>=0;i--){
    int len=(1ll<<i),w=W;
    if(len<=H){
      calc(i,1ll*len*len*(w/len));
      w-=1ll*(w/len)*len;
      for(int j=i;j>=0;j--)
        if(w>=(1ll<<j)) calc(j,1ll*len*(1ll<<j)),w-=(1ll<<j);
      H-=len;
    }
  }
  if(!n) cout<<"Yes\n";
  else cout<<"No\n";
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  sol();
  return 0;
}
```

---

## 作者：Robin_kool (赞：0)

发现先放小正方形非常不牛，因为它会让之后的放置过程留下一条很小的缝，故我们优先放置大的正方形。

首先肯定放在某个边界（可能是某个之前正方形的边）。考虑放了一个正方形后，会再次形成一个L字型的边界（可能为 $0$），那么根据上面的结论，把这个边界劈成两块后，我们肯定是放在较大的那块里（代码里默认是以长优先），如果放不下就肯定无解了。

以此类推，开个大根堆维护一下每个剩余部分即可。


```cpp
//#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 10;
int h, w, n, a[N];
priority_queue<pair<int, int>> q;
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline void Freopen(){
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
}
inline void solve(){
	h = read(), w = read(), n = read();
	for(int i = 1; i <= n; ++ i) a[i] = (1 << read());
	sort(a + 1, a + 1 + n, greater<int>());
	q.push(make_pair(min(h, w), max(h, w)));
	for(int i = 1; i <= n; ++ i){
		if(a[i] > q.top().first) return puts("No"), void();
		pair<int, int> now = q.top(); q.pop();
		q.push(make_pair(now.first - a[i], a[i]));
		q.push(make_pair(now.second - a[i], now.first));
	}
	puts("Yes");
}
signed main(){
	Freopen();
	int T = 1;
//	T = read();
	while(T --) solve();
	return 0;
}

```

---

## 作者：Daniel_yao (赞：0)

# Solve

第一个想法是将所有的矩形面积求和并与给定区域面积作比较，然后会被最后一个样例卡掉。手推一下发现这个只是一个必要条件。

考虑到将较大的矩形放在左上角（角落）是最优的。然后考虑缩小判断范围，假设当前要放置长度为 $a$ 的矩形。则放置范围为 $h:[1,2^a\times\left\lfloor\dfrac{H}{2^a}\right\rfloor]$，$w:[1,2^a\times\left\lfloor\dfrac{W}{2^a}\right\rfloor]$。考虑到如果所有长度大于 $a$ 的矩形之和小于等于放置范围的面积之和，则当前状态合法。

于是枚举 $a\in[0,25]$，然后依次判断即可。

时间复杂度 $O(n^2)$。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,l,r) for(int i=l;i<=r;++i)
#define FOR(i,r,l) for(int i=r;i>=l;--i)

using namespace std;

const int N = 1e3 + 5; 

int n, m, p, a[N];

int sum(int r) {
  int sum0 = 0;
  For(i,1,p) if(a[i] >= r) sum0 += ((1ll << a[i]) * (1ll << a[i]));
  return sum0;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> p;
  For(i,1,p) cin >> a[i];
  For(r,0,25) {
    int H = (n / (1ll << r)), W = (m / (1ll << r));
    int k = H * W * (1ll << r) * (1ll << r);
    if(sum(r) > k) {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
  return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

提供一个比较简单的做法。

将 $a$ 从大到小排序填到矩形里。每次加入一个小矩形，就会把大矩形分成三个。

具体地，假设填在左下角，那么剩下的部分是一个角型。可以将角型分成至多三个矩形。

我们维护一下当前手里有那些矩形。每次填一个进去，就会使矩形增加两个（去掉原来的一个，又增加三个）。如果手里没有能填进去的，直接输出 `No`。

由于每次都需要判断一下能不能填，判断是否能填复杂度 $O(n)$，复杂度就是 $O(n ^ 2)$。

---

## 作者：wangif424 (赞：0)

# 题面大意

你有一个大小为 $H \times W$ 的格子状矩形，你需要判断是否能把它从格子处分成 $N$ 个正方形，满足第 $i$ 个正方形的边长为 $2^{A_i}$，可以有剩余。

# 做法

假设当前矩形已经被裁减成了很多块，那么不难发现用当前尽可能小的一块矩形去裁出最大的正方形是最优策略。因为当裁去一个较小的正方形之后，剩余的两边的边角料所能裁的正方形边长不超过当前正方形边长，而对角的剩余块所能裁减出的正方形，其边长也不及原矩形。

因此，我们用较小的边为第一关键字对当前的边升序排序，并将 $A$ 数组降序排序，模拟以上过程并判断即可。

关于这个思路的来源，还有一个[哲理故事](https://zhuanlan.zhihu.com/p/346486579)（~~虽然我当时听到的版本是关于自助餐的~~。

# AC代码

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define int long long
#define R(x) x=read()
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
char pbuf[1<<20], *pp=pbuf;
inline void push(const char &c){if(pp - pbuf == 1<<20)fwrite(pbuf, 1, 1<<20, stdout),pp = pbuf;*pp++ = c;}
class io{public:~io(){fwrite(pbuf, 1, pp - pbuf, stdout);}}_;
inline void write(int x) {
    if (x<0)x=-x,push('-');
    int sta[35],top=0;
    do{sta[top++]=x%10,x/=10;}while (x);
    while(top)push(sta[--top]^'0');
}
#ifndef LOCAL
    char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
    #define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
int h,w,n;
int a[1010];
struct ct{
    int h,w;//h<=w
    bool operator<(const ct b)const{
        return h*w<b.h*b.w;
    }
};
multiset<ct> s;
int pw[30];
signed main(){
    R(h);R(w);R(n);
    if(h>w)h^=w^=h^=w;
    s.emplace(ct{h,w});
    pw[0]=1;
    for(int i=1;i<=27;i++)pw[i]=pw[i-1]*2;
    for(int i=1;i<=n;i++){R(a[i]);a[i]=pw[a[i]];}
    sort(a+1,a+1+n,[](int x,int y){
        return x>y;
    });
    for(int i=1;i<=n;i++){
        // for(auto it=s.begin();it!=s.end();it++){
        //     cerr << '|' << it->h << ' ' << it->w << '|';
        // }
        // cerr << a[i] << endl;
        auto it=s.begin();
        for(;it!=s.end();it++){
            if(it->h >= a[i])break;
        }
        if(it==s.end()){
            puts("No");
            return 0;
        }
        ct c=*it;
        s.erase(it);
        h=c.h-a[i];w=c.w-a[i];
        if(h)s.emplace(ct{h,w});
        w=a[i];
        if(h>w)h^=w^=h^=w;
        if(h)s.emplace(ct{h,w});
        h=a[i];
        w=c.w-a[i];
        if(h>w)h^=w^=h^=w;
        if(h)s.emplace(ct{h,w});
    }
    puts("Yes");
    return 0;
}
```

---

## 作者：incra (赞：0)

### Solution
挺好的思维题。

显然，从大的正方形开始放置一定比从小的正方形开始放置容易考虑。

设当前放置的正方形大小为 $t=2^x$，已经放置的面积为 $sum$。

那么，我们经过一点思考后可以发现：$sum$ 可以拆解成当前已经放置了 $\dfrac{sum}{t^2}$ 个边长为 $t$ 的正方形，注意没有下取整。

简单证明一下，设边长为 $2^k$ 的正方形放了 $cnt_k$ 个，那么 $sum=\displaystyle\sum_{i=x+1}^{25}cnt_i\times2^{2i}$，显然 $t^2=2^{2x}|2^{2i+2}(i>x)$。

如何计算当前长方形最多能放几个边长为 $t$ 的正方形？根据上面的内容可以推出最多能放 $\left\lfloor\dfrac{h}{t}\right\rfloor\left\lfloor\dfrac{w}{t}\right\rfloor-\dfrac{sum}{t^2}$，每次检验最多能放的正方形个数是否大于等于需要的个数即可。
### Code
代码中求 $sum$ 的过程用了秦九韶公式（应该是吧）。
```cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int N = 30;
int n,m,k;
int cnt[N];
int main () {
	cin >> n >> m >> k;
	for (int i = 1;i <= k;i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	LL sum = 0;
	for (int i = 25;i >= 0;i--) {
		sum *= 4;
		LL t = 1ll << i;
		LL c = (LL)(n / t) * (m / t) - sum;
		if (cnt[i] > c) {
			puts ("No");
			return 0;
		}
		sum += cnt[i];
	}
	puts ("Yes");
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：0)

赛时先过了 B、C 再过的 A。感觉这个比 B 要难多了啊。

很显然，~~但我想了很久~~应该用递归实现。

递归中有两个参数 $r,c$，表示当前划分出的矩形的长宽。先把能放的最大的正方形放在一角，然后剩下的一个 `L` 形区域分成两个矩形继续递归。要记录每块是否用过了。

```cpp
#include<iostream>
using namespace std;
int R,C,n,ans;
int cnt[30];
void fill(int r,int c)
{
  int now=-1;
  for(int i=25;i>=0;i--)
    if(cnt[i]&&r>=(1<<i)&&c>=(1<<i))
    {
      now=i;
      break;
    }
  if(now==-1)return;
  cnt[now]--;
  if(c>(1<<now))fill((1<<now),c-(1<<now));
  if(r>(1<<now))fill(r-(1<<now),c);
}
int main()
{
  cin>>R>>C>>n;
  for(int i=1;i<=n;i++)
  {
    int x;
    cin>>x;
    cnt[x]++;
  }
  fill(R,C);
  for(int i=25;i>=0;i--)
    if(cnt[i])
    {
      cout<<"No"<<endl;
      return 0;
    }
  cout<<"Yes"<<endl;
  return 0;
}
```

---

## 作者：LHLeisus (赞：0)

[AtCoder](https://atcoder.jp/contests/arc172/tasks/arc172_a)

[洛谷](https://www.luogu.com.cn/problem/AT_arc172_a)

[更好的阅读体验](https://www.cnblogs.com/LHLeisus/p/18022371)

从大到小依次考虑这些正方形。如果一个正方形是合法的，那么原矩形就会被划分成两个新的矩形，如下：

![](https://img.zshfoj.com/39ece79aef0f2d5d9d748fd4f588b5c8cb61dfcf6edbf85d4d9f8a00bcb5cc78.png)

蓝色是当前的正方形，橙色和红色就是两个新的矩形。我们把这些新的矩形丢到 multiset 里维护，按照 $\min(\text{长,宽})$ 从小到大排序，也就是每拿到一个新的正方形就从小的矩形开始考虑，而正方形又是从大到小排序的，这样不会有浪费。

```cpp
struct node{
	int h,w,t;
	bool operator <(const node &x)const{
		return t<x.t;
	}
};
multiset<node>st;
int main()
{
	h=read(),w=read(),n=read();
	FOR(i,1,n) a[i]=read(),a[i]=pow(2,a[i]);
	sort(a+1,a+1+n);reverse(a+1,a+1+n);
	st.insert({h,w,min(h,w)});
	FOR(i,1,n){
		auto it=st.begin();
		for(;it!=st.end();++it){
			if((*it).t>=a[i]) break;
		}
		if(it==st.end()) return puts("No"),0;
		node x=*it;
		st.erase(it);
		if(min(x.h-a[i],a[i]))
			st.insert({x.h-a[i],a[i],min(x.h-a[i],a[i])});
		if(min(x.h,x.w-a[i]))
			st.insert({x.h,x.w-a[i],min(x.h,x.w-a[i])});
	}
	puts("Yes");
	return 0;
}

```


---

