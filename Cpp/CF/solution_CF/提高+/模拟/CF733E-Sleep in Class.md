# Sleep in Class

## 题目描述

The academic year has just begun, but lessons and olympiads have already occupied all the free time. It is not a surprise that today Olga fell asleep on the Literature. She had a dream in which she was on a stairs.

The stairs consists of $ n $ steps. The steps are numbered from bottom to top, it means that the lowest step has number $ 1 $ , and the highest step has number $ n $ . Above each of them there is a pointer with the direction (up or down) Olga should move from this step. As soon as Olga goes to the next step, the direction of the pointer (above the step she leaves) changes. It means that the direction "up" changes to "down", the direction "down" — to the direction "up".

Olga always moves to the next step in the direction which is shown on the pointer above the step.

If Olga moves beyond the stairs, she will fall and wake up. Moving beyond the stairs is a moving down from the first step or moving up from the last one (it means the $ n $ -th) step.

In one second Olga moves one step up or down according to the direction of the pointer which is located above the step on which Olga had been at the beginning of the second.

For each step find the duration of the dream if Olga was at this step at the beginning of the dream.

Olga's fall also takes one second, so if she was on the first step and went down, she would wake up in the next second.

## 样例 #1

### 输入

```
3
UUD
```

### 输出

```
5 6 3 ```

## 样例 #2

### 输入

```
10
UUDUDUUDDU
```

### 输出

```
5 12 23 34 36 27 18 11 6 1 ```

# 题解

## 作者：duanyll (赞：7)

## 题意

一个人站在楼梯上，楼梯编号1到n，每一层楼梯上面都有着标识，'U'代表这个人上楼，'D'代表这个人下楼，每当这个人离开这一层楼梯，这层楼梯的标识改变，U变成D，D变成U。

现在的问题是，询问出这个人站在1到N的每一层楼梯，那么在每一层楼梯，他要花费多少时间才能走出这些楼（从1或者N走出去），如果他永远走不出去，输出-1

## 分析

```
UUD UUD UUD
^    ^    ^
DUD UDD UUU
 ^    ^  ^
DDD UDU UDU
  ^  ^    ^
DDU UUU
 ^  ^
DUU ...
^
```

手工模拟几次样例之后容易发现人会一直沿着一段连续相同的标记往前走，遇到第一个不同的标记就返回后一直往回走，再碰到一个不一样的标记后继续向开始的方向走，回到刚才的折返点时不同的标记已经被清除掉了，就可以继续向前走了……

相当于这个人从出发点开始，以 $ 2*dis $ 的代价依次消除两侧颜色不一样的点，最后获得一条连续的颜色相同的路走出去，不存在走不出去的情况。

```
DUDUDDDUU
   |-^
   |--|
 |----|
 |------>
```

再模拟几次又发现如果~~出发点方向的折返点（D方向的U，U方向的D）数量**大于**出发点的反方向的折返点数量，就会从出发点的反方向走出来，否则就从出发点方向走出来~~好绕啊，再概括一下就是**左U（包括自己）大于右D就从右边出去，否则从左边出去**。

答案就是D方向的U，U方向的D的距离之和乘二加上最后走出去的花费。

用前缀和统计D和U的数量来判定每个点走出去的方向，然后正方向反方向各开一个队列（里面存当前点需要的的折返点位置）来差分统计当前方向的折返点的距离之和，统计时利用另一个方向的折返点计数保证队列中元素个数正确。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

typedef long long int64;

const int MAXN = 1e6+10;
const int INF = 0x3f3f3f3f;

char a[MAXN];
int64 ans[MAXN];

int sumu[MAXN],sumd[MAXN];
int q[MAXN];

int main(){
	int n;
	cin >> n >> (a+1);
	for(int i = 1;i<=n;i++){
		sumu[i] = sumu[i-1];
		if(a[i] == 'U'){
			sumu[i]++;
		}
	}
	for(int i = n;i>=1;i--){
		sumd[i] = sumd[i+1];
		if(a[i] == 'D'){
			sumd[i]++;
		}
	}
	for(int i = 1;i<=n;i++){
		if(sumd[i+1] >= sumu[i]){
			ans[i] = i;
		}else{
			ans[i] = n-i+1;
		}
	}
	
	int head = 0,tail = 0;
	int64 tot = 0;
	for(int i = 1;i<=n;i++){
		tot += head-tail;			//向前推进一格，距离当前队列中折返点距离之和增加为折返点个数 
		while(head-tail > sumd[i]){
			tot -= i - q[tail++];	//出队多余折返点 
		}
		ans[i] += tot*2;
		if(a[i] == 'U'){
			q[head++] = i;
		} 
	}
	
	head = 0,tail = 0;
	tot = 0;
	for(int i = n;i>=1;i--){
		tot += head-tail;
		while(head-tail > sumu[i]){
			tot += i - q[tail++];	//出队多余折返点 
		}
		ans[i] += tot*2;
		if(a[i] == 'D'){
			q[head++] = i;
		} 
	}
	
	for(int i = 1;i<=n;i++){
		cout << ans[i] << ' '; 
	}
	cout << endl;
}
```

本代码在差分统计答案上参考了[Toooooocold](https://blog.csdn.net/qq_32506797/article/details/53039638)的代码实现（自己没想到直接加元素个数这一点，写的太复杂了）。

---

## 作者：Pengzt (赞：4)

[CF733E](https://www.luogu.com.cn/problem/CF733E)

简单的。

手摸一下容易发现来回走了若干次之后，$i$ 的左右都会变为同一个字符，因为它向上时遇到 $\texttt{D}$，会沿着上来的路再下去，然后遇到 $\texttt{U}$ 再上去……它一直执行这样的操作的话，就只有上面的 $\texttt{D}$ 和下面的 $\texttt{U}$ 可能会产生贡献，贡献是 $2|i-j|$。最后是走到 $1$ 还是 $n$ 以及两边分别的贡献，按照它们的个数和当前点的值分类讨论一下即可，具体细节见代码。

时空复杂度线性。

[评测记录](https://codeforces.com/contest/733/submission/228109088)

---

## 作者：ifffer_2137 (赞：1)

### 题意
一排箭头，走过一个后该箭头方向反转，对于每一个起点求走出序列的步数。
### 分析
考虑一个起点的过程，是先朝一个方向一直走，然后遇到反方向的就反转这个箭头，然后跑回来去另一个方向，这样循环往复，直到任意一侧被全部反转至能走出去的方向。

容易发现每次走回起点时都只有一个箭头被反转，因为其它都走了两遍。所以只要找出起点左边所有的 `U` 和右边所有的 `D`，然后手工模拟一下左边翻一个右边翻一个的过程，发现是求一个前 $k$ 小/大之和，BIT 上二分即可，时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
#define mkpr make_pair
#define x first
#define y second
#define popcnt __builtin_popcountll
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
template<class T1,class T2>inline bool Cmn(T1 &x,T2 y){return y<x?(x=y,1):0;}
template<class T1,class T2>inline bool Cmx(T1 &x,T2 y){return y>x?(x=y,1):0;}
template<class T>inline void Dbg(T *a,int l,int r){for(int i=l;i<=r;i++)cout<<a[i]<<' ';cout<<'\n';}
mt19937 rnd(time(NULL));
constexpr int inf=0x3f3f3f3f;
constexpr int maxn=1e6+5;
constexpr int maxm=5e3+5;
constexpr int mod=998244353;
constexpr int base=2137;
constexpr int V=1e9;
constexpr int H=20;
constexpr int W=64;
constexpr int Z=26;
constexpr double eps=1e-9;
inline int Redu(int x){return x-(x>=mod)*mod;}
inline void Add(int &x,int y){x=x+y-(x+y>=mod)*mod;}
inline void _Add(int &x,ll y){x=(x+y)%mod;}
inline void Del(int &x,int y){x=x-y+(x<y)*mod;}
inline void _Del(int &x,ll y){x=(x-y)%mod;x+=(x<0)*mod;}
inline int Mul(int x,int y){return 1ll*x*y%mod;}
inline int Pow(int a,int x){int s=1;for(;x;x>>=1,a=1ll*a*a%mod)if(x&1)s=1ll*s*a%mod;return s;}
bool Mem1;
int n;
string s;
class Fenwick_Tree{
private:
	int c[maxn];
	ll s[maxn];
public:
	void add(int x,int k){for(int i=x;i<=n;i+=i&-i)c[i]+=k,s[i]+=k*x;}
	int get(){int s=0;for(int i=n;i;i-=i&-i)s+=c[i];return s;}
	ll query(int k){
		int pos=0,cnt=0; ll sm=0;
		for(int i=H-1;i>=0;i--) if((pos|(1<<i))<=n&&cnt+c[pos|(1<<i)]<=k) pos|=(1<<i),cnt+=c[pos],sm+=s[pos];
		return sm;
	}
}ft[2];
void Init(){}
void Clear(){}
void Mymain(){
	Clear();
	n=read();
	cin>>s;s=' '+s;
	for(int i=1;i<=n;i++) if(s[i]=='D') ft[1].add(i,1);
	for(int i=1;i<=n;i++){
		if(s[i]=='D') ft[1].add(i,-1);
		int t0=ft[0].get(),t1=ft[1].get(),t=min(t0,t1); ll ans=0;
		if(t0<t1) ans=i;
		else if(t0>t1) ans=n-i+1;
		else ans=(s[i]=='U'?n-i+1:i);
		if(s[i]=='D'&&t0>t1) ans+=(1ll*i*(t+1)-(ft[0].query(t0)-ft[0].query(t0-t-1)))<<1;
		else ans+=(1ll*i*t-(ft[0].query(t0)-ft[0].query(t0-t)))<<1;
		if(s[i]=='U'&&t1>t0) ans+=(ft[1].query(t+1)-1ll*i*(t+1))<<1;
		else ans+=(ft[1].query(t)-1ll*i*t)<<1;
		cout<<ans<<' ';
		if(s[i]=='U') ft[0].add(i,1);
	}
	cout<<'\n';
}
bool Mem2;
signed main(){
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	Init();int _=1;
	while(_--) Mymain();
	cerr<<"Time: "<<1000.0*clock()/CLOCKS_PER_SEC<<" ms\n";
	cerr<<"Memory: "<<(&Mem1-&Mem2)/1024.0/1024.0<<" MB\n";
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：1)

- $s_i=D$

这个时候其实就是走到离 $i$ 右边最近的 $U$，然后转向走到左边最近的 $D$。

然后你把左边 $D$ 的个数和右边 $U$ 的个数取 $\min$。注意到对于 $s_k=D$ 的时候它会从右边找一个 $U$ 被它到达，然后再找一个 $U$ 到达它。就是 $-2s_k$。

同理，$L$ 就是 $2s_k$。

注意，先往下面走，上面可以少到一次，所以取 $\min$ 的时候，所以左边 $D$ 的数量取 $\min$ 时可以 $+1$。

- $s_i=U$

  同理。好像两边的式子还是一样的。但是取 $\min$ 的两边 $+1$ 可能不一样。

虽然但是，如果你要求的话，时间复杂度是 $O(n\times k)$，似乎不行？

错误的，其实你可以预处理出每个位置的 $k$，然后的话递推，用队列限制 $U,D$ 的数量。

等等，$k_i$ 不具有单调性，但是 $+1$ 的话两个之间最多差一，就多存一个栈把删掉的放进去就行了。

这样的话，时间复杂度 $O(n)$ 了。

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF733E)

------------
# 题意：
有一个长度为 $n$ 的楼梯，每节台阶上有一个字符串。$U$ 则代表向上走，$D$ 则代表向下走，当走过这个台阶后，台阶上的字符串会从 $U$ 变为 $D$ 或从 $D$ 变成 $U$。求从第 $i$ 个台阶开始要走出这 $N$ 个台阶需要的步数（即从 $1$号台阶向下，或 $N$ 号台阶向上），若出不去则输出 ```-1```。

------------
# 思路：
首先考虑第 $i$ 个位置是 $U$，显然它会走到第一个 $D$ 反向，之后到 $i$ 下面的第一个 $U$ 再次反向，显然这部分后面就不会再影响答案了。于是可以很容易的得出第 $i$ 个位置是从上还是从下走出去的，然后就只需要计算折返的距离即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int n,c,ans[N],l[N],r[N];
char s[N];
queue<int>q;
signed main(){
    cin>>n>>s+1;
    for(int i=1;i<=n;i++){
		l[i]=l[i-1]+(s[i]=='U');
	}
    for(int i=n;i>=1;i--){
		r[i]=r[i+1]+(s[i]=='D');
	}
    for(int i=1;i<=n;i++){
		if(l[i]<=r[i+1]){
			ans[i]=i;
		}else{
			ans[i]=n-i+1;
		}
	}
    for(int i=1;i<=n;i++){
        c+=q.size();
        while(q.size()>r[i]){
			c-=i-q.front();
			q.pop();
		}
        ans[i]+=c * 2;
        if(s[i]=='U'){
			q.push(i);
		}
    }
    while(q.size()){
		q.pop();
	}
    c=0;
    for(int i=n;i>=1;i--) {
        c+=q.size();
        while(q.size()>l[i]){
			c-=q.front()-i;
			q.pop();
		}
        ans[i]+=c * 2;
        if(s[i]=='D'){
			q.push(i);
		}
    }
    for(int i=1;i<=n;i++){
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}
```
完结撒花~

---

