# Great Vova Wall (Version 2)

## 题目描述

Vova 的家族正在建造伟大的 Vova 墙（这个名字是 Vova 自己起的）。Vova 的父母、祖父母、曾祖父母都为此做出了贡献。现在，最后的收尾工作完全交给了 Vova。

当前墙的状态可以用一个长度为 $n$ 的整数序列 $a$ 表示，其中 $a_i$ 表示第 $i$ 段墙的高度。

Vova 只能使用 $2 \times 1$ 的砖块（他有无限多这样的砖块）。

Vova 只能将砖块水平放置在相邻且高度相等的墙段上。也就是说，如果对于某个 $i$，第 $i$ 段和第 $i+1$ 段的当前高度相同，那么 Vova 可以在这两个位置放置一块砖，从而使这两段的高度都增加 $1$。显然，Vova 不能把砖块放在墙的边界之外（不能放在第 $1$ 段的左边或第 $n$ 段的右边）。

注意，Vova 不能竖直放置砖块。

Vova 是个完美主义者，他认为墙完成的标准是：

- 墙的所有部分高度都相同；
- 墙内部没有空隙。

Vova 能否使用任意数量的砖块（可以为零）完成这堵墙？

## 说明/提示

在第一个样例中，Vova 可以在第 $2$ 段和第 $3$ 段放一块砖，使墙变为 $[2, 2, 2, 2, 5]$，然后在第 $1$ 段和第 $2$ 段放 $3$ 块砖，在第 $3$ 段和第 $4$ 段放 $3$ 块砖，使其变为 $[5, 5, 5, 5, 5]$。

在第二个样例中，Vova 不需要在墙上放任何砖块。

在第三个样例中，墙已经是完成状态。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 1 1 2 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3
4 5 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2
10 10
```

### 输出

```
YES
```

# 题解

## 作者：Nightingale_OI (赞：3)

给你一个残缺的墙，有 $ n $ 个位置，问你是否可以把它砌平整。

你可以横着方宽为 $ 2 $ 的砖块，即如果有两个位置相邻且高度相等，你可以让它们的高度增加 $ 1 $ 。

每个位置的高度最高可以是 $ 10 ^ 9 $ 。

 $ n \leq 2 \times 10 ^ 5 $ 

------------

考虑用栈按顺序维护每一个未两两匹配的高度是多少。

因为在栈中的想要出栈的数依赖于刚出栈的数叠到该层，

所以如果上一个操作是出栈，那么这次的出栈操作的数字不可比上一次的出栈操作的数字小。

能出栈就出栈即可。

------------

程序复杂度 $ O(n) $ ，显然能过。

------------

代码如下 （~~非常简单~~)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
int a[202020],b[202020];
int main(){
    cin>>n;
    int al=0;
    for(register int i=1;i<=n;++i)scanf("%d",&a[i]);
    for(register int i=1;i<=n;++i){
        if(s && b[s]==a[i] && (a[i]>=l || m)){//可以出栈
            m=0;
            s--;
            l=a[i];
            if(al<a[i])al=a[i];
        }else{//进栈
            m=1;
            b[++s]=a[i];
        }
    }
    if(!s)printf("YES\n");//直接可以
    else if(s==1 && b[1]>=al)printf("YES\n");//最后剩下的可以达到
    else printf("NO\n");
    return 0;
}
```

---

## 作者：meyi (赞：1)

~~做 ds 题做魔怔了所以写了一个带 $\log$ 的解法。。。~~

显然按权值从小到大考虑，考虑相同权值的极长连续段，如果段长为奇数则输出 `NO`，否则将当前段的权值改为段两端的较小值并将权值相同的位置合并为新的连续段，这样做显然每次能减少至少一段，故复杂度是 $O(\text{段数}\times\text{DS})$ 的，使用 set 维护可以做到 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri int
typedef long long ll;
const int maxn=2e5+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
static char pbuf[1000000],*p1=pbuf,*p2=pbuf;
#define getchar() p1==p2&&(p2=(p1=pbuf)+fread(pbuf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int qr(){
	ri in=0;char ch;
	while(!isdigit(ch=getchar()));
	do in=(in<<1)+(in<<3)+(ch^48);while(isdigit(ch=getchar()));
	return in;
}
int a[maxn],lst=1,n;
struct cmp{inline bool operator()(int x,int y)const{return a[x]!=a[y]?a[x]<a[y]:x<y;}};
set<int,cmp>s1;
set<int>s2;
int main(){
	n=qr();
	for(ri i=1;i<=n;++i){
		a[i]=qr();
		if(a[i]!=a[lst])s1.insert(lst),s2.insert(lst),lst=i;
	}
	s1.insert(lst),s2.insert(lst);
	while(s1.size()>1){
		ri l=*s1.begin();s1.erase(s1.begin());
		auto nxt=s2.erase(s2.find(l));
		ri r=(nxt==s2.end()?n:*nxt-1);
		if((r-l+1)&1)return puts("NO"),0;
		ri val=INT_MAX;
		if(nxt!=s2.end())ckmin(val,a[*nxt]);
		if(nxt!=s2.begin())ckmin(val,a[*prev(nxt)]);
		a[l]=val;
		if(nxt!=s2.end()&&a[l]==a[*nxt])s1.erase(*nxt),nxt=s2.erase(nxt);
		if(nxt!=s2.begin()&&a[l]==a[*prev(nxt)]);
		else s1.insert(l),s2.insert(l);
	}
	puts("YES");
	return 0;
}
```


---

## 作者：7KByte (赞：1)

这里提供一个不同的方法。

首先模拟一下，不难发现一定是从低处往高处填。

所以我们从低到高枚举当前高度 $h$，不难发现有解的充要条件是对于每个 $h$，$\le h$ 的 $a_i$ 构成的联通块长度都是偶数。

这样思路就非常清晰了，我们从小到大依次加点，然后用并查集维护每个联通块和联通块大小。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,a[N],u[N],c[2],sz[N],fa[N];bool flag=true;
bool cmp(int x,int y){return a[x]<a[y];}
int get(int x){return fa[x]==x?x:fa[x]=get(fa[x]);}
void merge(int x,int y){
	x=get(x);y=get(y);
	c[sz[x]&1]--;c[sz[y]&1]--;
	sz[x]+=sz[y];fa[y]=x;
	c[sz[x]&1]++;
}
void solve(int l,int r){
	rep(i,l,r){
		c[1]++;fa[u[i]]=u[i];sz[u[i]]=1;
		if(fa[u[i]-1])merge(u[i],u[i]-1);
		if(fa[u[i]+1])merge(u[i],u[i]+1);
	}
	if(c[1])flag=false;
}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]),u[i]=i;
	sort(u+1,u+n+1,cmp);int pre=1;
	//rep(i,1,n)printf("%d ",u[i]);putchar('\n');
	rep(i,2,n)if(a[u[i]]!=a[u[i-1]])solve(pre,i-1),pre=i;
	if(flag)puts("YES");else puts("NO");
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

我们先来考虑 V1。

## V1

给定一个序列 $a=\{a_1,a_2,\dots,a_n\}$，有以下两种操作：

- 若 $a_i=a_{i\ +\ 1}$，则可将 $a_i$ 与 $a_{i\ +\ 1}$（$1\le i < n$）同时加 $1$；

- 将 $a_i$（$1\le i\le n$）加 $2$。

求问是否可经过多此操作后使得所有 $a_i$ 相等。

---

首先我们考虑第 $2$ 种操作——我们只使用这一种操作很显然并不能达到目的，但是我们可以使用操作 $2$ 来让每个 $\max(a_i)-\min(a_i)≤1$，这样我们用操作 $1$ 会更容易讨论一些。

下面我们来讨论一些情况。

- $a,a+1,a+1,a$ 型

这种情况我们先把中间两个 $+1$，变成 $a,a+2,a+2,a$。然后对两边执行操作 $2$，即可变成 $a+2,a+2,a+2,a+2$。

- $a+1,a,a,a+1$ 型

一目了然了。

上面是一些具体的例子，下面我们来考虑比较普遍的情况。我们考虑把所有 $a_i$ 看成是在对 $2$ 取模的意义下，那么操作 $1$ 就是对相邻的两个数字同时取反，操作 $2$ 就相当于没有影响。

现在问题看上去貌似简单了一些：给定 $01$ 串，每次你可以选择相邻两个数字把他们取反。求最后是否可以让所有数字相等。由上面第一个距离可以发现，如果两个奇偶性相同的数字中间有若干**对奇偶性相同**的数字，那么这两个数字也是可以最终变成和其他数字奇偶性相同。

于是我们可以想到括号匹配，用**栈**来维护。我们定义一种括号匹配为 `(` 与 `(` 匹配，`)` 与 `)` 匹配，那么本题就是询问能否在这种匹配规则下完成匹配，或者只有一个字符无法匹配（思考为什么这种情况也合法）。详情看代码。


## V2

我们发现我们不能使用操作 $2$ 了！

我们再来考虑 $a,b,b,a$ 这种情况。如果 $b>a$，那么很显然我们无法完成。因此只有 $b<a$ 时我们才能按照 V1 的思路把 $b,b$ 匹配并且弹出栈。

我们把 V1 的代码添加这个限制即可。

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
// #define long long long long
#define mp make_pair

#define rd read()
inline long long read()
{
	long long xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(long long out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const long long N=5e5+5;
 const long long M=5e5+5;
const long long INF=2e9+5;
const long long MOD=2e9+7;
bool f1;
long long n,t,m;
long long stk[N],top;
long long ans;
bool f2;

int mxlst,lst;


signed main(){

    // freopen("woof.in","r",stdin);
    // freopen("woof.out","w",stdout);

	n=rd;
	while(n--){
		int a=rd;
		if(top&&stk[top]==a&&(a>=lst||m)){
			m=0,top--,lst=a;
			if(mxlst<a)mxlst=a;
		}
		else stk[++top]=a,m=1;
	}
	
	if(!top||(top==1&&stk[1]>=mxlst))cout<<"YES";
	else cout<<"NO";
    
}

/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/
```




---

## 作者：MuelsyseU (赞：0)

考虑按照题意模拟。我们的目标等价于问是否所有数都可以做到能被无限提升。

首先对于每两个连续相同的数，将它作为一个组，这个组的高度可以任意提升。

然后考虑一个性质，那就是在移动过程中一定存在一种方案，不会拆开任何组分别增加，除非这个组两边的数相等并且这两边的数都不在任何组内。考虑拆开来增加只会导致另外一个对应元素只能依赖另外一边的数来增加。那么这两个元素的操作实际上还是对称的，所以除非两边的数相等，否则肯定不这样做。当两边相等，我们称之为“合并”操作。这可以推广到任何长度为偶数的段。

现在考虑长度为奇数的段，它可以拆成一个点和一个偶数段。那个偶数段一定不满足两边数相等的性质，所以它没有用。于是这一段就相当于一个点，只要它左右两边有一个数可以达到它，这整一段就是可以提升的。

综上所述，我们对每个长度为偶数的段，尝试向外扩张，也就是在两边找尽量长的上升子串，并且两边的部分必须完全一致。

这里注意特判，假如扩张时两边已经不相等，但是其中一边还可以继续扩张（仍然相等），这一段可以继续扩张，但是扩张的结果长度必须是偶数。这对应着“在边界上遇到一个奇数段”这种情况。另外，如果这一边扩张到了整个输入序列的边界，那么就不用管是否是偶数。

我们规定一个段不能合并其它长度为偶数的段，因为这些段自己合并两边的部分肯定不会更劣。如果有一个点不在任何段中，又不被两边的偶数段扩张到，显然无解。

这种模拟非常好理解，所以不放代码。时空复杂度 $O(n)$，常数略大于栈做法。

---

## 作者：Nylch (赞：0)

相邻两个是相等高度的才能达到任意高度，像 ```1221``` 这种也不行。如果最后剩下一个未匹配成功的，那么一定要是最高的。（因为只能横着放）

那么用栈维护一下就好了。

```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define ull unsigned long long
#define db double
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pi>
#define vpl vector<pl>
#define pb push_back
#define er erase
#define SZ(x) (int) x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mkp make_pair
#define ms(data_name) memset(data_name, 0, sizeof(data_name))
#define msn(data_name, num) memset(data_name, num, sizeof(data_name))
#define For(i, j) for(reg int (i) = 1; (i) <= (j); ++(i))
#define For0(i, j) for(reg int (i) = 0; (i) < (j); ++(i))
#define Forx(i, j, k) for(reg int (i) = (j); (i) <= (k); ++(i))
#define Forstep(i , j, k, st) for(reg int (i) = (j); (i) <= (k); (i) += (st))
#define fOR(i, j) for(reg int (i) = (j); (i) >= 1; (i)--)
#define fOR0(i, j) for(reg int (i) = (j) - 1; (i) >= 0; (i)--)
#define fORx(i, j, k) for(reg int (i) = (k); (i) >= (j); (i)--)
#define tour(i, u) for(reg int (i) = head[(u)]; (i) != -1; (i) = nxt[(i)])
using namespace std;
char ch, B[1 << 20], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 20, stdin), S == T) ? 0 : *S++)
#define isd(c) (c >= '0' && c <= '9')
int rdint() {
  int aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
ll rdll() {
  ll aa, bb;
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
const int mod = 998244353;
// const int mod = 1e9 + 7;
struct mod_t {
  static int norm(int x) {
    return x + (x >> 31 & mod);
  }
  int x;
  mod_t() {  }
  mod_t(int v) : x(v) {  }
  mod_t(ll v) : x(v) {  }
  mod_t(char v) : x(v) {  }
  mod_t operator +(const mod_t &rhs) const {
    return norm(x + rhs.x - mod);
  }
  mod_t operator -(const mod_t &rhs) const {
    return norm(x - rhs.x);
  }
  mod_t operator *(const mod_t &rhs) const {
    return (ll) x * rhs.x % mod;
  }
};
const int MAXN = 2e5 + 10;
int n, a[MAXN], stk[MAXN], top = 0;
inline void work() {
  n = rdint();
  int mx = 0;
  For(i, n) {
    a[i] = rdint();
    mx = max(mx, a[i]);
  }
  bool flag = 0;
  For(i, n) {
    if(top != 0 && stk[top] == a[i])
      top--;
    else if(top != 0 && stk[top] < a[i])
      flag = 1;
    else
      stk[++top] = a[i];
  }
  if(!flag && (top == 0 || top == 1 && stk[top] == mx))
    printf("YES\n");
  else
    printf("NO\n");
}
int main() {
  // freopen("input.txt", "r", stdin);
  work();
  return 0;
}
```

---

