# [AGC014B] Unplanned Queries

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc014/tasks/agc014_b

高橋君は木の問題が苦手です。そこで、青木君は高橋君の練習相手になってあげることにしました。

まず、高橋君は $ N $ 頂点からなる木を用意し、頂点に $ 1 $ から $ N $ の番号を付けました。 そして、各辺に $ 0 $ と書きました。

次に、青木君は高橋君に $ M $ 個のクエリを与えました。$ i $ 個目のクエリは以下のような内容です。

- 頂点 $ a_i $ と頂点 $ b_i $ を結ぶパス上の辺すべてに対して、書かれている数を $ 1 $ 増やす。

全てのクエリを終えた後、高橋君は青木君にどの辺を見ても書かれている数が偶数になったと伝えました。 しかし、青木君は最初に高橋君が用意していた木を確認していなかったので、 高橋君が正しくクエリを処理できたか分かりませんでした。

青木君を助けるために、高橋くんの言う性質を満たす木が存在するかどうかを判定してください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ M\ ≦\ 10^5 $
- $ 1\ ≦\ a_i,b_i\ ≦\ N $
- $ a_i\ ≠\ b_i $

### Sample Explanation 1

例えば、頂点 $ 1 $ と頂点 $ 2,3,4 $ が辺で結ばれているような木を高橋君が持っている場合は、高橋くんの言っていることは正しいです。 この場合、クエリをすべて終えた後各辺に書かれている数はどれも $ 2 $ になります。

## 样例 #1

### 输入

```
4 4
1 2
2 4
1 3
3 4```

### 输出

```
YES```

## 样例 #2

### 输入

```
5 5
1 2
3 5
5 1
3 4
2 3```

### 输出

```
NO```

# 题解

## 作者：Lynkcat (赞：4)

AGC 老喜欢结论题了。

Step 1：我们可以把问题转化到点上，我们假设每次操作为 $(u,v)$ 那么 $B[u]++,B[v]++$。显然最后的 $B$ 对于每一个只可能是偶数。也就是说我们把问题转化成了 $a$ 到 $b$ 这条路径上所有点取反。

Step 2：我们假设 $1$ 是树的根那么显然有 $(a,b)$ 操作等价于 $(1,a)$ + $(1,b)$ 两个操作。接着我们开始分类讨论：如果所有 $B[i]$ 是偶数，也就是 $(1,i)$ 操作执行偶数次，那么显然不管树是咋样的都是可行的。如果有 $B[i]$ 是奇数，那么显然不管树是咋样的都不可行，因为深度最大的那个 $B$ 为奇数的点一定为奇数。

所以我们就得出了一个结论：我们只要随便造一颗树然后按题意取反一下，然后看看点权是不是都是偶数就行。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
#define int ll
#define N 100005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,a[N],u,v,ans=0,m;
signed main()
{
	n=read();m=read();
	for (int i=1;i<=m;i++)
	{
		u=read(),v=read();
		if (v<u) swap(u,v);
		a[u]++,a[v]--;
	}
	for (int i=1;i<=n;i++)
		a[i]=a[i-1]+a[i];
	for (int i=1;i<n;i++)
		if (a[i]&1) ans=1;
	if (!ans) puts("YES"); else puts("NO");
}
/*

*/

---

## 作者：TachibanaKanade (赞：2)

结论题。

首先考虑每个点都出现了偶数次时，显然满足题意。

而如果存在有一点出现次数为奇数，则图中必然存在该点的一条出边，它加的次数为奇数，不符合题意。

综上，只需要构造出一种所有点都出现偶数次的情况即可。

而显然一条链的情况满足题意。从而代码实现就非常简单了。

```
signed main() {
    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &a, &b);
        cnt[a] ^= 1;
        cnt[b] ^= 1;
    }
    for (int i = 1; i <= n; i++) {
        if (cnt[i]) return !printf("NO\n");
    }
    puts("YES");
}
```


---

## 作者：Spasmodic (赞：1)

这题紫真的虚高，感觉绿差不多，不过我和各位的想法不太一样？

考虑一个经典的树上差分，定义

$$
g_u=w_{u\to fa}-\sum_{c\in son_u}w_{c\to u}
$$

那么容易发现 $w_{u\to fa}$ 就是 $u$ 子树内 $g$ 的和。

考虑每次操作后 $g$ 的变换，发现就是 $g_u\gets g_u+1,g_v\gets g_v+1,g_{lca}\gets g_{lca}-2$，mod 2 意义下就是 $g_u\gets g_u+1,g_v\gets g_v+1$。

我们考虑反向推回去，就会发现 $g$ 最后应当全是偶数，容易发现这一结论是双向的。

那么我们随便算个 $g$ 就可以了。代码不放了。

---

## 作者：Yukinoshita_Yukino (赞：1)

[Link](https://www.luogu.com.cn/problem/AT2374)

结论题。

题意：每次操作将树上 $a_i$ 到 $b_i$ 的路径边权加一，问是否能构造出所有边边权都为偶数的树。

如果对于任意 $i$ 号节点作为边权加和操作的起点操作次数都是偶数，那就可以构造出来。否则就不行。

如果有一个点加了奇数次，那这个点的出边一定有一条边加了奇数次，不符合题意。

那么如何构造所有点出现偶数次时可行情况呢？

一种理解是，直接将 $a_i$ 和 $b_i$ 连边。因为每个点都出现了偶数次，所以图中一定有环。把环展开成链，就会有两个点，这样这条链上两个点个点就会断开。在这两个点之间沿着链加一遍，这样链上的点都出现偶数次了。

```cpp

#include<bits/stdc++.h>
using namespace std;
const int maxn=300010;
int n,m;
int cnt[maxn]; 
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int a,b;
		cin>>a>>b;
		cnt[a]++,cnt[b]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]%2)
		{
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;
	return 0;
 } 

```

---

## 作者：1saunoya (赞：1)

没啥意思的题。

发现这个树怎么样，奇数还是奇数，偶数还是偶数/youl

于是搞个链，差分一下就做完了。

```cpp
/*
 _      _  _ _ _ _ _   _      _
\_\   /_/ \_\_\_\_\_\ \_\   /_/
 \_\ /_/      \_\      \_\ /_/
  \_\_/       \_\       \_\_/
   \_\         \_\       \_\
   \_\     \_\ \_\       \_\
   \_\      \_\\_\       \_\
*/
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rp(i,y) for(int i=1;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define pr(i,y) for(int i=y;i>=1;i--)
#define sz(v) (int)v.size()
using namespace std;
const int SIZE=1<<26;
char gc[SIZE],*pgc=gc;
char pc[SIZE],*ppc=pc;
clock_t clk=clock();
struct flusher{
	flusher(){
#ifdef WHX_TXDY
		freopen("fuck.in","r",stdin);
#endif
		fread(gc,true,SIZE,stdin);
	}
	~flusher(){
		fwrite(pc,true,ppc-pc,stdout);
#ifdef WHX_TXDY
		std::cerr<<"TIME:"<<(clock()-clk)/1000.<<"s\n";
#endif
	}
}Flusher;
int _Neg=0;
template<class T>
void rd(T&x){
	x=_Neg=0;
	while(!isdigit(*pgc)){
		if((*pgc++)=='-'){
			_Neg=1;
		}
	}
	while(isdigit(*pgc)){
		x=x*10+*pgc++-48;
	}
	if(_Neg){
		x=-x;
	}
}
int _Stk[233],_Top=0;
template<class T>
void pt(T x,char c='\n'){
	if(x<0){
		*ppc++='-';
		x=-x;
	}
	do{
		_Stk[++_Top]=x%10;
		x/=10;
	}while(x);
	while(_Top){
		*ppc++=_Stk[_Top--]+48;
	}
	*ppc++=c;
}
void pts(const string&str){
	int len=sz(str);
	rep(i,0,len-1){
		*ppc++=str[i];
	}
	*ppc++='\n';
}
template<class T>
void cmax(T&x,const T&y){
	x=(x>y)?x:y;
}
template<class T>
void cmin(T&x,const T&y){
	x=(x<y)?x:y;
}

int n;
const int N = 1e5 + 5;
int a[N];

int main() {
	rd(n);
	int m;
	rd(m);
	while (m--) {
		int l, r;
		rd(l);
		rd(r);
		if(l>r)swap(l,r);
		a[l]++;
		a[r]--;
	}
	rp(i,n){
		a[i]+=a[i-1];
	}
	int cnt=0;
	rp(i,n-1){
		if(a[i]&1){
			++cnt;
		}
	}
	if(cnt)pts("NO");
	else pts("YES");
	return 0;
}

---

## 作者：lkjzyd20 (赞：0)

# 思路

一道结论题。

当有任意一个点有奇数个度时，那么必然存在一条边从这个点出发只被加过奇数次，不符合题意，故只要有一个点出现了奇数次，直接输出 `NO` 即可。

当所有点都是偶数次的时候，一条链肯定是满足题目的要求的，直接输出 `YES` 即可。

# 代码如下

```cpp
#include <bits/stdc++.h>

#define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++i)

using namespace std;

const int MAXN = 100010;
int f[MAXN];

main() 
{
	int n, m;
	cin >> n >> m;
	rep(i, 1, m)
	{
		int x, y;
		cin >> x >> y;
		++ f[x]; ++ f[y];
	}
	
	rep(i, 1, 100000)
		if(f[i] % 2 != 0)
		{
			puts("NO");
			return 0;
		}
	puts("YES");
}

```

---

## 作者：Krimson (赞：0)

结论题，光猜都能大概猜到。  

结论：当所有点出现的次数都是偶数次的时候必然有解，否则无解。  

倘若一个点出现了奇数次，那么必然存在一条边从这个点出发只被加过奇数次，满足必要性。  

其次，所有点都出现偶数次的时候，一条链肯定是满足题目的要求的，满足充分性。


 _Code_ 
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il int read(char *s){
    int len=0;
    register char ch=getchar();
    while(ch==' '||ch=='\n') ch=getchar();
    while(ch!=' '&&ch!='\n'&&ch!=EOF) s[++len]=ch,ch=getchar();
    return len;
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
int n,m;
const int MAXN=1e5+7;
int cnt[MAXN];
int main(){
    n=read(),m=read();
    for(ri i=1;i<=m;++i){
        int u=read(),v=read();
        cnt[u]^=1,cnt[v]^=1;
    }
    for(ri i=1;i<=n;++i){
        if(cnt[i]){
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}
```



---

