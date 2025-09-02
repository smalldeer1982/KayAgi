# Trip to the Olympiad

## 题目描述

在新的一年中，将会有很多团队奥林匹克竞赛，因此「T-generation」的老师们需要选择三名学生组成一个团队来参加这些比赛。无论是哪三名学生，他们都能在任何团体竞赛中表现出色。然而，赢得比赛仅仅是成功的一部分；首先，他们需要获得参赛资格……

每位学生都有一个用整数表示的独立性等级。「T-generation」中，每个独立性等级从 $l$ 到 $r$（包含 $l$ 和 $r$）的数值都有且只有一名学生。对于一个由独立性等级为 $a$、$b$ 和 $c$ 的学生组成的三人团队，他们的团队独立性值定义为 $(a \oplus b) + (b \oplus c) + (a \oplus c)$，其中 $\oplus$ 表示按位异或运算。

你的任务是选择一个三人团队，使得他们的团队独立性值最大化。

## 说明/提示

在第一个测试用例中，可以选择的唯一个合适的三元组（忽略顺序）是 $(0, 1, 2)$。

在第二个测试用例中，其中一个合适的三元组是 $(8, 7, 1)$，因为 $(8 \oplus 7) + (7 \oplus 1) + (8 \oplus 1) = 15 + 6 + 9 = 30$。经过证明，$30$ 是在 $0 \le a, b, c \le 8$ 时，$(a \oplus b) + (b \oplus c) + (a \oplus c)$ 的最大可能值。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
0 2
0 8
1 3
6 22
128 137
69 98
115 127
0 1073741823```

### 输出

```
1 2 0
8 7 1
2 1 3
7 16 11
134 132 137
98 85 76
123 121 118
965321865 375544086 12551794```

# 题解

## 作者：arrow_king (赞：4)

发现二进制意义下一位能产生贡献当且仅当 $a,b,c$ 的这一位不都相同。

考虑 $l,r$ 从高到低相同的一个前缀。左右界的限制使得这些位一定无法产生贡献。那能不能让更低的位都能产生贡献呢？答案是肯定的。

构造：
$$
\begin{aligned}
a&=(0111\dots11)_2\\
b&=(1000\dots00)_2
\end{aligned}
$$

$c$ 取 $l,r$ 中与 $a,b$ 不同的那个即可。显然可以证明 $l\le a<b\le r$ 且两个等号不同时取得。

```cpp
#define getbit(x,y) ((x>>y)&1)
il void mian() {
	ll l=read(),r=read(),now=0;
	for(ll i=30;i>=0;i--) {
		if(getbit(l,i)!=getbit(r,i)) {
			ll x=(1ll<<i)-1,y=0;
			x+=now,y+=now+(1ll<<i);
			printf("%lld %lld ",x,y);
			if(x!=l&&y!=l) printf("%lld\n",l);
			else printf("%lld\n",r);
			return; 
		}
		now+=getbit(l,i)?(1ll<<i):0;
	}
	return;
}
```

---

## 作者：Drifty (赞：4)

### Solution

先考虑答案如何取到最大的。我们先把 $a, b, c$ 拆成 $2$ 进制，并记 $a, b, c$ 在 $2$ 进制下从小到大第 $i$ 位分别为 $a_i, b_i, c_i$。我们发现，当 $a_i, b_i, c_i$ 当中全是 $0$ 或全是 $1$ 时，就没有贡献，否则会产生 $(0\oplus 0) + (1\oplus 0) + (1\oplus 0) = 2$ 的贡献。那么我们肯定希望让每一位都能产生贡献。

我们不妨直接令 $a = l, a<b<c, c = r$。然后就可以直接暴力地构造 $b$（为了保证范围，我们让 $i$ 初始为从大到小第一个使得 $a_k \neq c_k$ 的 $k$）：

- 如果 $a_i = b_i$ 那么当前位只能填 $a_i \oplus 1$。
- 如果 $a_i \neq b_i$ 那么填 $1$，填完后如果 $b \ge r$，那么改成 $0$（为了保证范围）。
- $i$ 自减。

然后就构造出来了。由于是 $2$ 进制的，因此上述贪心的构造是正确的。

### Code

赛时的史山实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int T, l, r;
void solve() {
    cin >> l >> r;
    bitset <32> x(l), y(r), ans(0);
    int tp = 31;
    for (; ~tp; tp --) if (x[tp] ^ y[tp]) break;
    for (int i = 31; i > tp; i --) ans[i] = x[i];
    for (int i = tp; ~i; i --) {
        if (!(x[i] ^ y[i])) ans[i] = x[i] ^ 1;
    }
    for (int i = tp; ~i; i --) {
        if (x[i] ^ y[i]) {
            ans[i] = 1;
            if (ans.to_ulong() >= y.to_ulong()) ans[i] = 0;
        }
    }
    int a = x.to_ulong(), b = ans.to_ulong(), c = y.to_ulong();
    cout << a << ' ' << b << ' ' << c << '\n';
}
int32_t main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    for (cin >> T; T --; ) solve();
    return 0;
}
```

---

## 作者：yvbf (赞：2)

![](bilibili:BV1dkruY8ETZ?t=607)

---

## 作者：The_foolishest_OIer (赞：1)

首先当 $r - l = 2$ 时，只能取 $a = l,b = l + 1,c = l + 2$。

设 $r$ 在二进制下的表示是 $\sum_{i = 0}^x 2^i \times a_i$，$l$ 在二进制下的表示是 $\sum_{i = 0}^y 2^i \times b_i$，如果 $x \ne y$，否则不断减少 $x$，知道 $a_x = 1$ 而 $b_x = 0$ 为止，最大值就是 $2^{x + 1} - 2$。

当然，如果 $x = y$ 且 $l = 2^y$，那么 $x$ 也要减 $1$，否则下面构造出来的 $b$ 是不合法的。

显然，我们只要让 $a = 2^x,b = 2^x - 1$ 即可，此时 $c$ 对答案是没有影响的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 35;
int T,l,r;
int a[N],b[N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void solve(){
	cin >> l >> r;
	int ret = 0;
	while(1){
		if (r - l == 2){ // 万不得已
			cout << l + ret << ' ' << l + ret + 1 << ' ' << l + ret + 2 << endl;
			break;
		} 
		int x = 1;
		while (x * 2 <= r) x *= 2; // 找最大的 x
		if (x <= l){ // 如果 2 的 x 次方小于 l，即此时 x = y
			ret += x; // 不要忘记把减掉的加回来
			r -= x;
			l -= x;
			continue;
		}
		cout << x + ret << ' ' << x + ret - 1 << ' ' << (x == r ? l : r) + ret << endl;
		break;
	}
}
signed main(){
	close();
	T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：浮光掠影 (赞：0)

### 解题思路

考虑将 $l$ 和 $r$ 转为二进制，一定形如 $\texttt{xxxx0****}$ 和 $\texttt{xxxx1****}$。即以第一个不同的位分隔。显然可以构造  $a = \texttt{xxxx10000}$，$b = \texttt{xxxx01111}$，$c$ 任意取即可。显然这种方案可以使 $l$ 和 $r$ 第一个不同位及其之后的每一位都为 $\texttt{1}$，因此最优。

### 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int l, r, T = 1, x = 1;
void work()
{
    cin >> l >> r;
    int op;
    for (int k = 32; k >= 0; k--)
    {
        if ((l & (1 << k)) != (r & (1 << k)))
        {
            op = k;
			break;
        }
    }
    int p = (l >> op) << op;
    int a = p + (1 << op), b = p + (1 << op) - 1;
    if (b == l) cout << a << " " << b << " " << r << "\n";
    else cout << l << " " << a << " " << b << "\n";
}

signed main()
{
    if (x) cin >> T;
    while (T--) work();
    return 0;
}
```

---

## 作者：imljw (赞：0)

容易发现，对于第 $x$ 位，当且仅当有一个或三个数该位为 $1$ 时，它会有贡献。

那么我们可以先把 $l$，$r$，$a$，$b$，$c$ 的二进制转换出来。我们假定 $b < c$，那么可以这么构造：对于最大的 $i$ 使得 $l,r$ 的前面 $i$ 位都相等，举个例子：
$\newline (11000)_2 \newline (11100)_2 \newline$
对于这两个数，它们的 $i$ 就应该是 $2$。我们可以考虑把大的 $b , c$ 先求出来，对于上述例子，如果有前缀相同的，就把前缀取相同，如果没有，或取完了，对于没取值的那些位，只要一个 $1$ 就够了，$c$ 全部取 $1$，然后按照已经构造好的 $b , c$ 在值域里随便找一个 $a$ 使得 $a$ 不等于 $b$ 也不等于 $c$ 就行了。

这么说可能有点抽象，可以对照着赛时代码（有点丑，勿喷）模拟一遍好好理解一下。
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IN {
	const long long MANPUT = 1000000;
#define getc() (p1==p2&&(p2=(p1=buf)+inbuf->sgetn(buf,MANPUT),p1==p2)?EOF:*p1++)
	char buf[MANPUT],*p1,*p2;
};
using namespace IN;
template<typename T>inline bool read(T &x);
template<typename T,typename ...Args>inline bool read(T& a,Args& ...args);
long long T,l,r,id[40],i2[40],a[40],b[40],x,y,z;//id,i2记录l,r转二进制，a,b,记录a和b的二进制，第31位用不上，所以记录长度。
int main() {
	read(T);
	while(T--) {
		read(l,r);
		memset(id,0,sizeof(id));
		memset(i2,0,sizeof(i2));
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		for(long long i=0; i<=30; i++) {
			if((1<<i)&l)id[i]=1,id[31]=i;
			if((1<<i)&r)i2[i]=1,i2[31]=i;
		}
		if(id[31]==i2[31]) {
			long long i=i2[31];
			while(i>-1&&id[i]==i2[i]) {
				a[i]=b[i=id[i];
				i--;
			}
			if(i>-1){
				i2[31]=i;
				id[31]=i-1;
			}
		}
		a[i2[31]]=1;
		for(long long i=i2[31]-1; i>=0; i--) {
			b[i]=1;
		}
		x=y=z=0;
		for(long long i=0; i<=30; i++) {
			x|=(1<<i)*a[i];
			y|=(1<<i)*b[i];
		}
		for(int i=l;i<=r;i++)if(i!=x&&i!=y){
			z=i;
			break;
		}
		cout<<x<<' '<<y<<' '<<z<<'\n';
	}
	return 0;
}
template<typename T>inline bool read(T &x) {
	static std::streambuf *inbuf=cin.rdbuf();
	x=0;
	register long long f=0,flag=false;
	register char ch=getc();
	while(!isdigit(ch)) {
		if (ch=='-') f=1;
		ch=getc();
	}
	if(isdigit(ch)) x=x*10+ch-'0',ch=getc(),flag=true;
	while(isdigit(ch)) {
		x=x*10+ch-48;
		ch=getc();
	}
	x=f?-x:x;
	return flag;
}
#undef getc
template<typename T,typename ...Args>inline bool read(T& a,Args& ...args) {
	return read(a)&&read(args...);
}
```

---

## 作者：What__can__I__say (赞：0)

简易贪心。

考虑最大总贡献的值是怎样的。手玩样例可以发现，选出的 $a$，$b$，$c$ 的总贡献都形如 $2\times (2^x-1)$。仔细观察，这个 $x$ 就是给出的 $l$ 与 $r$ 二进制下从左往右最后一个相同的位置的权值。

考虑证明。记 $l$ 与 $r$ 二进制下从左往右最后一个相同的位置为 $k$，权值为 $v$。容易发现我们最多可以让 $k$ 之后的每个位都产生两次贡献。因为鸽巢原理，把 $0$ 或 $1$ 放入三个位置中，至少有两个位是一样的，这时它们不能产生贡献。另外两对则各有 $1$ 的贡献。因此最大贡献即为 $2\times (2^v-1)$。

接下来考虑如何构造。我们可以在其中一个数的从左往右第 $k+1$ 位放一个 $1$，之后全放 $0$。再在另外一个数的第 $k+1$ 位放一个 $0$，之后全放 $1$。就是形如下面两个数的样子：

$$···100000$$
$$···011111$$

那么它们产生了 $2^v-1$ 的贡献。发现第三个只要随便取一个 $l$ 到 $r$ 的值即可。因为这个数 $k$ 之后的每一位总与上述两个数的其中之一不同，一定有 $1$ 的贡献。

另外，本题需注意那两个特殊数的前 $k$ 位应与输入的前 $k$ 位相同，以确保符合范围。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define fir first
#define sec second
#define pb emplace_back
#define mod 1000000007
#define put putchar
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
const int JYAAKIOI=1e18,N=5e5+86,M=1e2+86;
int T,minn,maxn,k,maxk,ans1,ans2,ans3;
signed main(){
	T=rd();
	while(T--){
		minn=rd(),maxn=rd();
		if(maxn-minn==2){
			wr(minn),put(' '),wr(minn+1),put(' '),wr(maxn),put('\n');
			continue;
		}
		k=0;
		int val=0;
		for(int i=31;i>=0;--i){
			bool v1=maxn&(1ll<<i),v2=minn&(1ll<<i);
			if(!v2&&v1){
				k=i;
				break;
			}
			val=val+(1ll<<i)*v1;
		}
		//cout<<k<<" "<<val<<endl;
		int ans1=val+(1ll<<k),ans2=ans1-1;
		if(ans2==minn)ans3=ans1+1;
		else if(ans1==maxn)ans3=ans2-1;
		else ans3=minn;
		wr(ans1),put(' '),wr(ans2),put(' '),wr(ans3),put('\n');
	}
    return 0;
}
```

---

