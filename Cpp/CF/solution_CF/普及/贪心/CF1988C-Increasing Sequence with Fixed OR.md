# Increasing Sequence with Fixed OR

## 题目描述

You are given a positive integer $ n $ . Find the longest sequence of positive integers $ a=[a_1,a_2,\ldots,a_k] $ that satisfies the following conditions, and print the sequence:

- $ a_i\le n $ for all $ 1\le i\le k $ .
- $ a $ is strictly increasing. That is, $ a_i>a_{i-1} $ for all $ 2\le i\le k $ .
- $ a_i\,|\,a_{i-1}=n $ for all $ 2\le i\le k $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

## 样例 #1

### 输入

```
4
1
3
14
23```

### 输出

```
1
1
3
1 2 3
4
4 10 12 14
5
7 18 21 22 23```

# 题解

## 作者：Dioretsa (赞：13)

因为要最大化元素个数，又因为元素的最大值为 $n$。所以，不妨令序列中最后一个元素为 $n$，下面以 $n=(23)_{10}$ 为例。将 $(23)_{10}$ 转化为二进制数 $(10111)_2$。

我们令 $(23)_{10}$ 为序列中最后一个元素，由此可以构造前面一个元素。为了让元素数量最大，我们应该尽量让这个元素大一些。我们可以将二进制数  $(10111)_2=(23)_{10}$ 的第零位（最右边的一位）变为 $0$，以此得到一个合法且最大的元素 $(10110)_2=(22)_{10}$。

遵循最大化元素数量的思想，我们可以继续往下构造出 $(10101)_2=(21)_{10}$，$(10011)_2=(19)_{10}$，$(00111)_2=(7)_{10}$。我们将这些数放在一张表上。

|  | $4$ | $3$ | $2$ | $1$ | $0$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $7$ | $\underline{0}$ | $0$ | $1$ | $1$ | $1$ |
| $19$ | $1$ | $0$ | $\underline{0}$ | $1$ | $1$ |
| $21$ | $1$ | $0$ | $1$ | $\underline{0}$ | $1$ |
| $22$ | $1$ | $0$ | $1$ | $1$ | $\underline{0}$ |
| $23$ | $1$ | $0$ | $1$ | $1$ | $1$ |

注意表中带下滑线的 $0$，这是构造出来的每一个元素与 $n=23$ 的不同之处。我们可以发现，上文所说的构造方法其实就是每次将二进制数 $(10111)_2=(23)_{10}$ 中的一位 $1$ 变成 $0$。且**第一个**元素 $7$ 将 $n=23$ 二进制数上的**第一个** $1$ 变成了 $0$，**第二个**元素 $19$ 将 $n=23$ 二进制数上的**第二个** $1$ 变成了 $0$（此处说的第一个、第二个是从左往右数的）。以此类推，我们可以得出构造方法。

不难发现，以上过程可以使用 lowbit 实现。赛时代码如下：
```cpp
#include<bits/stdc++.h>
#define MAXN 500005
using namespace std;
long long T,n,m,ans[MAXN],cnt,tmp;
long long lowbit(long long x){
	return x&-x;
}
int main() {
	cin>>T;
	while(T--){
		cin>>n;
		m=n,tmp=0,cnt=1,ans[1]=n;
		while(m!=0){
			tmp=lowbit(m);
			if(n-tmp>0) ans[++cnt]=n-tmp;
			m-=tmp;
		}
		cout<<cnt<<endl;
		for(int i=cnt;i>=1;i--) cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：4)

### [CF1988C Increasing Sequence with Fixed OR](https://www.luogu.com.cn/problem/CF1988C)

当 $k > 1$ 时，所有 $a_i$ 在二进制下是 $n$ 的子集，否则不满足 $a_i \operatorname | a_{i - 1} = n$ 的限制。

对于序列中的某个 $a_i$ 和某一位 $b$，如果 $n$ 的第 $b$ 位是 $1$ 但 $a_i$ 的第 $b$ 位是 $0$，那么 $a_{i - 1}$ 的第 $b$ 位必须是 $1$。但 $a_{i - 1} < a_i$，所以存在更高位 $d > b$ 满足 $a_{i - 1}$ 的第 $d$ 位是 $0$，而 $a_i$ 的第 $d$ 位是 $1$。这说明 $a_i$ 相较于 $n$ 缺失的最高位低于 $a_{i - 1}$ 相较于 $n$ 缺失的最高位。

由 $a_{k - 1}$ 相较于 $n$ 一定缺了至少一位可知答案不超过 $\mathrm{popcount}(n) + 1$。设 $n$ 的第 $p_1 < \cdots < p_c$ 位是 $1$，对 $c > 1$，构造 $[n - 2 ^ {p_c}, \cdots, n - 2 ^ {p_1}, n]$ 达到该上界。对 $c = 1$，易知答案只能为 $[n]$。

时间复杂度 $\mathcal{O}(\log n)$。[代码](https://codeforces.com/contest/1988/submission/270838109)。

---

## 作者：sangshang (赞：2)

# Solution

首先可以想到一个贪心。构造到第 $i$ 个数我们希望 $a_i$ 尽可能小，这样之后更有操作余地。而考虑构造 $a_{i+1}$ 时，就只需考虑 $a_{i+1}>a_i$ 时让 $a_{i+1}$ 尽可能小，并可适当加大 $a_i$。

为方便描述，将 $n$ 在二进制下拆解，从高位数，第 $i$ 位所代表的值记作 $\text{bit}(i)$。

1. 考虑第 $1,2$ 两数，因为 $a_2|a_1=n,a_2>a_1$，所以 $a_2\ge \text{bit}(1)$，此时考虑 $a_1=n-\text{bit}(1)$，即可使 $a_2$ 最小。

2. 考虑 $a_3$，因为 $a_3>a_2$，所以 $a_3>a_2\ge \text{bit}(1)$。因为之后就不考虑 $a_2$ 的值了，所以此时让 $a_3$ 尽可能小才是最重要的。那 $n$ 的其他几位肯定不应该全部加在 $a_3$，而是应该在 $a_3>a_2$ 的前提下尽量让 $a_2$ 承担。最高位 $a_3,a_2$ 都必须包含，思考时去掉。此时问题又回到类似 $(1)$ 中的形式。容易想到 $a_3$ 最小是 $\text{bit}(1)+\text{bit}(2)$，$a_2$ 改为 $n-\text{bit}(2)$。

此时已容易发现规律，之后决策都可以用类似思路得出 $a_i=n-\text{bit}(i)$，最后再加上 $n$。注意特判 $n$ 是 $2$ 的整数次幂的情况。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int vec[105], tot;

int main() {
	int T;
	cin >> T;
	while (T--) {
		long long n;
		scanf("%lld", &n);
		tot = 0;
		for (int i = 0; (1LL << i) <= n; ++i) {
			if ((1LL << i)&n) {
				vec[++tot] = i;
			}
		}
		if (tot == 1) {
			printf("1\n");
			printf("%lld\n", n);
		} else {
			printf("%d\n", tot + 1);
			for (int i = tot; i >= 1; --i) {
				printf("%lld ", n - (1LL << vec[i]));
			}
			printf("%lld\n", n);
		}
	}
	return 0;
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

### 题意

给定 $n$，要你构造一个长度为 $k$，严格单调上升的正整数序列 $a$，满足对于 $2\le i\le k$ 有 $a_i|a_{i-1}=n$，即每两个相邻的数的或等于 $n$。

现在问最大的 $k$ 是多少以及构造出的序列。

### 思路

因为是二进制所以先考虑把 $n$ 二进制表示出来。预先声明下面的所有关于位数的讨论都是基于二进制形式进行的，第 $i$ 位表示从左往右数第 $i$ 个 $1$。

首先最后一个放 $n$ 肯定不劣。

因为或的性质我们知道填的所有数只能是 $n$ 抹掉一些 $1$ 得到的。考虑 $n$ 的最高位，在两个相邻的数里面一定有一个数最高位为 $n$ 的最高位才能或出来 $n$。所以在 $k$ 个数中 $a_2$ 到 $a_k$ 的最高位与 $n$ 一致。

随便给个数吧，假设 $n=10101111$。

假设现在你要填 $a_2$，因为要求上升，所以如果你删去的最高位是 $i=4$，那么从 $i$ 往前的所有位就锁定了，也就是往后面无论什么数都要以 $101011$ 开头。这个显然是不优的，因为我们明显可以删去第 $2$ 个或者第 $3$ 个 $1$ 让可以填的数范围更大。

所以根据贪心思想我们一定要选择前面有 $1$ 的位数最少的位置来删，也就是 $n$ 的第二位 $1$。

同理我们往后面依次删掉第三位第四位直到最后一位的一，然后在最后补上一个把 $n$ 最高位删掉的 $a_1$ 就好了。

注意特判一下 $n=1$ 的情况。

```cpp
#include <bits/stdc++.h>
#define int long long
#define Rg register
#define Ri Rg int
#define Il inline
#define vec vector
#define pb push_back
#define fi first
#define se second
#define IT ::iterator

using namespace std;

typedef double db;
typedef pair<int,int> pii;
const int N=2e5,Inf=1e9;
const db eps=1e-8;

int T,K;
bool a[65];
stack<int>s;

Il void yuanshenqidong(){
	cin>>K;
	if(K==1){
		cout<<"1\n1\n";
		return;
	}//特判
	int n=0,x=K;
	for(;K;K>>=1)a[++n]=K&1;//拆分二进制
	s.push(x);//最后一个就是本身
	for(Ri i=1;i<n;i++)if(a[i])s.push(x-(1ll<<(i-1)));//从前往后是依次删除最靠前的，从后往前添数就是依次最靠后的，注意二进制拆分后顺序是反着的
	if(x-s.top())s.push(x-s.top());//如果去掉最高位还有数就可以加进来
	cout<<s.size()<<'\n';
	for(;!s.empty();s.pop())cout<<s.top()<<' ';
	cout<<'\n';
	return;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)yuanshenqidong();
	return 0;
}

```

---

## 作者：Special_Tony (赞：1)

# 思路
其实这题 $a_i=n\operatorname{xor}\text{(n 的从高到低第 i 个 1 的权值)}$，最后补一个 $n$ 就行。另外若 $n=2^m$ 是例外，只能直接输出 $n$。
# 代码
## 方法 $1$
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, m;
ll n, a[500005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		if (n == (n & -n)) {
			cout << "1\n" << n << '\n';
			continue ;
		}
		m = 0;
		for (int i = 62; ~i; -- i)
			if (n >> i & 1)
				a[++ m] = n ^ (1ll << i);
		a[++ m] = n;
		cout << m << '\n';
		for (int i = 1; i <= m; ++ i)
			cout << a[i] << ' ';
		cout << '\n';
	}
	I AK IOI
}
```
## 方法 $2$
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, m;
ll n, a[500005], tmp;
ll f (ll x) { //highbit
	while (x != (x & -x))
		x ^= x & -x;
	return x;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		if (n == (n & -n)) {
			cout << "1\n" << n << '\n';
			continue ;
		}
		m = 0, tmp = n;
		while (n)
			a[++ m] = tmp ^ f (n), n ^= f (n);
		a[++ m] = tmp;
		cout << m << '\n';
		for (int i = 1; i <= m; ++ i)
			cout << a[i] << ' ';
		cout << '\n';
	}
	I AK IOI
}
```

---

## 作者：Naoxiaoyu (赞：1)

## 思路
首先数列的最后一个数一定是 $n$，从低位到高位枚举 $n$ 的二进制位，答案序列中的每个数就是 $n$ 减去自己的每个二进制位得出，最后倒序输出即可。

注意，在 $n$ 为 $2$ 的整数次幂时要特判为 $0$ 的情况，不能作为答案输出。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int a[500010];//要开long long
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		long long int n;
		scanf("%lld",&n);
		long long int m=n,p=1;
		a[1]=n;
		int cnt=1;
		while(m!=0)//枚举二进制位
		{
			if(m%2==1) a[++cnt]=a[1]-p;
			if(a[cnt]==0) --cnt;//特判0
			p=p*2;
			m=m/2;
		}
		printf("%d\n",cnt);
		for(int i=cnt;i>=1;i--)//倒序输出
		{
			printf("%lld ",a[i]);
		}
		printf("\n");
	}
	return 0;
}

---

## 作者：Mugino_Shizuri (赞：0)

[link](https://www.luogu.com.cn/problem/CF1988C)

好玩但难度不高的构造题。

为了简化问题，我们把 $n$ 看做是二的整次幂减一，因为 $0$ 没有影响，最后再加进去便是。

然后你发现正着做很烦，因为你不知道第一个数是啥。

但最后一个数肯定是 $n$，否则这个序列肯定可以再长（比如再加一个 $n$ 进去）。

我们来仔细看看这个看起来很就很像正解的想法。

实例是理解的试金石 --by 米尔嘉。

以 $1111$ 为例，倒着推一下试试看：

```
1 1 1 1
1 1 1 0
1 1 0 1
1 0 1 1
0 1 1 1
```

发现下面的正方形的对角线为 $0$，是巧合吗？

仔细想一下，发现每个数扣掉一个二进制位一定不劣且满足所有条件。

于是做法就出来了：把 $n$ 进行二进制分解，构造一个长度为 $\operatorname{popcount}(n)+1$，且除最后一个数外都是 $n$ 扣掉一个二进制位的数的序列。

但是要特判一下 $\operatorname{popcount}(n)$ 为 $1$ 的情况，因为不能填 $0$，感谢样例。

[AC代码](https://codeforces.com/contest/1988/submission/270864758)

---

## 作者：Guchenxi0971 (赞：0)

### 题意

构造最长的序列 $a$，使其严格递增，并且每个数小于 $n$，还有满足所有 $1<i\leq len ,a_i|a_{i-1}=n$。

### Sol

我们发现答案只与 $n$ 二进制分解后 $1$ 的个数有个，因为每个 $1$ 最多消失（即不出现）$1$ 次，并且每次只消失一个 $1$ 肯定不劣。（为了方便，本文只讨论二进制分解后全是 $1$ 的情况，因为出现的 $0$ 不会产生影响。）

为什么呢？我们设 $f(x)$ 表示二进制从高位开始第 $x$ 个 $1$ 的出现位置，那么如果让序列 $a_i=n-2^{f(i)-1}$ ，然后最后一个是 $n$ 那么该系列长度就是 $\operatorname{popcount}(n)+1$。

假设第 $i$ 位即以前按照该方法构造，那么考虑第 $i$ 个和第 $i+1$ 个数中，那么第 $i+1$ 个数的 $f(i)$ 即以前的 $f$ 必须为 $1$ 否则会小于 $a_i$ ，那么如果让第 $i+1$ 项从第 $f(i+1)$ 开始有多个联系位置是 $0$ ，这会导致在下一个值时这些位置必须为 $1$，那么会那个第一个为 $0$ 的位置必定会在 $f(i+2)$ 之后，会更劣。~~其实感性理解一下是很简单的。~~

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define mk make_pair
#define reaD read
#define raed read
#define haed head
#define cotu cout
#define se second
#define fi first
#define itn int
using namespace std;
const int Max=2e5+10;
const int mod=998244353;
const int inf=1e9+10;

namespace Fread {
	const int SIZE=1<<21;
	char buf[SIZE],*S,*T;
	inline char getchar() {
	    if(S==T){
	        T=(S=buf)+fread(buf,1,SIZE,stdin);
	        if(S==T)return '\n';
	    }
	    return *S++;
	}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){
	    fwrite(buf,1,S-buf,stdout);
	    S=buf;
	}
	inline void putchar(char c){
	    *S++=c;
	    if(S==T)flush();
	}
	struct POPOSSIBLE{
	    ~POPOSSIBLE(){flush();}
	}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();
        	T f=1;
        	while(c<'0'||c>'9'){
            	if(c=='-')f=-1;
            	c=getchar();
        	}
        	x=0;
        	while(c>='0'&&c<='9'){
	            x=x*10+(c-'0');
	            c=getchar();
	        }
	        x*=f;
	        return *this;
    	}
	    Reader& operator >> (char& c) {
	        c=getchar();
	        while(c==' '||c=='\n')c=getchar();
	        return *this;
	    }
	    Reader& operator >> (char* str) {
	        int len=0;
	        char c=getchar();
	        while(c==' '||c=='\n')c=getchar();
	        while(c!=' '&&c!='\n'&&c!='\r'){
	            str[len++]=c;
            	c=getchar();
        	}
			str[len]='\0';
			return *this;
	    }
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];
	        int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {
        	putchar(c);
        	return *this;
	    }
    	Writer& operator << (char* str) {
        	int cur=0;
        	while(str[cur])putchar(str[cur++]);
        	return *this;
    	}
    	Writer& operator << (const char* str) {
    	    int cur=0;
    	    while(str[cur])putchar(str[cur++]);
			return *this;
    	}
    	Writer(){}
	}cout;
}
#define cin Fastio :: cin
#define cout Fastio :: cout
#define endl Fastio :: endl


inline int read(){
	int x;
	cin>> x;
	return x;
}


int lowbit(int x){
	return x&(-x);
}

vector<int>ans; 

signed main(){
	int T=read();
	while(T--){
		int n=read();
		ans.clear();
		int x=n;
		int Pos=0;
		while(n){
			++Pos;
			if((n&1ll)==1)ans.push_back(Pos-1);
			n>>=1;
		}
		n=x;
		int pos=0;
		for(int i:ans){
			if((n-(1ll<<(i)))>0)++pos;
		}
        //一定要加1ll，不然会像某人一样吃4发罚时
		++pos;
		cout << pos << "\n";
		for(int i=ans.size()-1;i>=0;--i){
			if((n-(1ll<<(ans[i])))>0) cout << (n-(1ll<<(ans[i]))) << ' ';
		}
		cotu << n << "\n";
		
	}

	return 0;
}

```

---

## 作者：白鲟 (赞：0)

考虑所构造序列的二进制表示，要满足递增且相邻或为 $n$，越靠后的数将与 $n$ 拥有严格越长的公共前缀，由此答案上界为 $\operatorname{popcount}(n)+1$。为使得序列最长，则固定除最后一个数为 $n$ 本身外，每个数二进制表示仅有一位与 $n$ 不同，且序号每增加 $1$，不同的位就向低移一位。注意特判 $n$ 二进制中仅有一个 $1$ 的情况，此时答案为 $1$ 而非 $2$。

```cpp
#include<cstdio>
const int maxn = 64;
long long base[maxn + 1];
int main() {
    int T, cnt;
    long long n, t, multi;
    scanf("%d", &T);
    while(T--) {
        cnt = 0;
        multi = 1;
        scanf("%lld", &n);
        t = n;
        while(n) {
            if(n & 1) {
                base[++cnt] = multi;
            }
            multi <<= 1;
            n >>= 1;
        }
        if(cnt == 1) {
            printf("1\n%lld\n", t);
            continue;
        }
        printf("%d\n", cnt + 1);
        while(cnt) {
            printf("%lld ", t - base[cnt--]);
        }
        printf("%lld\n", t);
    }
    return 0;
}
```

---

## 作者：Eason_cyx (赞：0)

## 题意简述

给定 $n$，求一个长度最长的**正整数**序列 $a$，记其长度为 $k$，那么这个序列应满足以下条件：

- 对于所有的 $1\le i\le k$，$a_i\le n$。

- 对于所有的 $2\le i\le k$，$a_i>a_{i-1}$。

- 对于所有的 $2\le i\le k$，$a_i\,|\,a_{i-1}=n$，其中 $|$ 为或运算。

## 分析

考虑将原来的 $n$ 拆分成二进制。

以第五组样例 $n=23$ 为例：

$(23)_{10}=(10111)_2$，那么为了让 $a$ 最长，且相邻两个元素进行或运算等于 $n$，那么 $a$ 里面的元素转换为二进制后一定满足：

- 对于一个 $a_i$，假设 $n$ 的二进制表示下的第 $j$ 位为 $0$，则 $a_i$ 二进制表示下一定为 $0$。

- 对于某两个 $a_i$ 和 $a_{i-1}$，假设 $n$ 的二进制表示下的第 $j$ 位为 $1$，则 $a_i$ 或 $a_{i-1}$ 中的某一个的二进制表示下一定为 $1$。

又，题目要求我们使得 $a$ 序列最长，所以我们可以构造一个长度为 $\operatorname{popcount}(n)+1$ 的序列，其中 $\operatorname{popcount}(n)$ 表示 $n$ 在二进制表示中 $1$ 的个数。

读者可能已经想到了构造方法：$a_i$ 的二进制表示即为将 $n$ 的二进制表示中的第 $i$ 个 $1$ 变成 $0$ 即可。注意：$a_{\operatorname{popcount}(n)+1}$ 为 $n$ 本身，这样也是满足条件的。

单组时间复杂度 $\Theta(\log n)$。

注意特判：如果 $n=2^q$，其中 $q$ 为非负整数，此时 $n$ 的二进制表示下只有一个 $1$，将这个 $1$ 去掉后这个数就变成了 $0$，不满足题目条件。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[200005];
void Main() {
	long long n; cin >> n;
	int cnt = __builtin_popcountll(n);
	if(cnt == 1) {
		cout << cnt << endl;
		cout << n << endl;
		return ;
	}
	cout << cnt+1 << endl;
	long long k = n,num = 1,cur = 0;
	while(k) {
		if(k % 2) a[++cur] = n - num;
		num *= 2; k /= 2;
	}
	reverse(a+1,a+cur+1);
	for(int i = 1;i <= cur;i++) cout << a[i] << " ";
	cout << n << endl;
}
int main() {
	int t; 
	cin >> t;
	// t = 1;
	while(t--) Main();
	return 0;
}
```

---

## 作者：yanlikun (赞：0)

# 题意
给定一个数 $n$ ，要求我们构造一个符合要求下的最长序列 $a$ ，$k$ 为答案序列长度，要求如下：
1. $a_i \le n (1 \le i \le k)$ 。
2. $a$ 序列严格递增，即 $a_i>a_{i-1} (2 \le i \le k)$ 。
3. $a_i|a_{i-1} = n (2 \le i \le k)$ 。

如果不知道这个 $|$ ，[左转OI Wiki](https://oi-wiki.org/math/bit/)。
# 思路
了解了或运算的性质后，我们可以来分析一下 $n=23$ 时的一组合法序列：

| 23 | 1 | 0 | 1 | 1 | 1 |
| :----------- | :----------- | :----------- | :----------- | :----------- | :----------- |
| 22 | 1 | 0 | 1 | 1 | 0 |
| 21 | 1 | 0 | 1 | 0 | 1 |
| 18 | 1 | 0 | 0 | 1 | 0 |
| 5 | 0 | 0 | 1 | 0 | 1 |

因为要构造最长的子序列，我们每次贪心地构造，使二进制下每一位都尽量与上一个数的相同位置上的数相反。当然，我们很容易就能发现，其实我们真正用得上的只有二进制下为 $1$ 的位，故上图可以简化为如下：

| 23： | 1 | 1 | 1 | 1 |
| :----------- | :----------- | :----------- | :----------- | :----------- |
| 22： | 1 | 1 | 1 | 0 |
| 21： | 1 | 1 | 0 | 1 |
| 18： | 1 | 0 | 1 | 0 |
| 5： | 0 | 1 | 0 | 1 |

现在，大家应该很清晰地看到，简化后 $0$ 的分布是平行与对角线的。

根据这条规律，我们就可以开始写代码啦！
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int t,x[100],newx[100][100],whe[100];
int main()
{
	cin>>t;
	while(t--)
	{
		int sum=0,sumy=0,tot=0;
		for(int i=1;i<=60;i++)
			for(int j=1;j<=60;j++)
				newx[i][j]=1;
		cin>>n;
		long long nn=n;
		while(nn)
		{
			x[++sum]=nn%2;
			nn/=2;
		}
		for(int i=1;i<=sum;i++)
		{
			if(!x[i])
				tot++;
			else
			{
				sumy++;
				whe[sumy]=tot;//小优化：因为我们把为0的位数全部删去了，所以我们要用一个后缀数组记录每一个为1的位后面被删去的0的位数，方便将答案转回十进制。
			}
		}
		if(sumy==1)
			cout<<"1\n"<<n<<"\n";
		else
		{
			cout<<sumy+1<<"\n";
			for(int i=1;i<=sumy;i+=2)
			{
				int y=0;
				for(int j=sumy-i+1;j>=1;j--)
				{
					newx[i+y][sumy-y]=0;
					y++;
				}
			}
			for(int i=sumy;i>=1;i--)
			{
				long long sumx=0;
				for(int j=1;j<=sumy;j++)
					if(newx[i][j])
						sumx+=pow(2,sumy-j+whe[sumy-j+1]);//加上删去的0的位数
				cout<<sumx<<" ";
			}
			cout<<n<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：ZhaoV1 (赞：0)

解析
------------
做一个逆向模拟，即从 $n$ 向更小数的模拟：  
假若 $n=23$，那么用二进制表示就是 $10111$，我们需要得到最多的前项个数，经过模拟，我们只需要将当前值 $num$ 的二进制中位数最小为 $1$ 的位数改为 $0$，再填补上一轮消除掉的 $1$ 即可，因为第一轮情况特殊，我们还是简单模拟一下：

```
n = 23

10111 -> 十进制为 23，我们删除二进制中最小为 1 的位数，变为10110
10110 -> 十进制为 22，我们将目前最小的 1 改为 0，再补上之前消除的 1，得到10101
10101 -> 十进制为 21，以此类推
10011 -> 十进制为 19
00111 -> 十进制为 7

虽然与样例答案不同，但可证明这种解法符合题意，是正解。

```

AC Code
------------

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5+5;
int t,n;
int bit[165];

long long fast_power(int base, int power){
	int res = 1;
	while(power){
		if(power&1){
			res = res*base;
		}
		power /= 2;
		base = base*base;
	}
	return res;
}

void solve(){
	vector<int> v;
	for(int i=0;i<=102;i++) bit[i] = 0;
	int count = 0;
	cin >> n;
	int nn = n;
	while(nn){
		if(nn & 1){
			bit[count] = 1;
		}
		count++;
		nn /= 2;
	}
	int num = n;
	int last = -1;
	v.push_back(num);
	for(int i=0;i<count;i++){
		if(!bit[i]) continue;
		num = num - fast_power(2,i);
		if(last != -1){
			num += fast_power(2,last);
		}
		last = i;
		if(num == 0) break;
		v.push_back(num);
	}
	cout << v.size() << '\n';
	for(int i=v.size()-1;i>=0;i--){
		cout << v[i] << " ";
	}
	cout << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：EricWan (赞：0)

我们考虑反向思考，从最后一位入手。

最后一个数一定是 $n$（如果不是，那么在后面在放一个 $n$ 绝对是没问题的，与“如果最后一个不是 $n$”假设矛盾）。

整个题目中，我们可以把 $n$ 的二进制下是的 $0$ 的位全部忽略。

假设我们后一个数在二进制下长这样：$A$ 个 $1$，之后是一个 $0$，后面是什么我们不管。

那前一个数的第 $A+1$ 位一定是 $1$。因此他的第 $A$ 位就一定得是 $0$ 了（否则就不能比后面的数小），这样，每一个数都会使得 $A$ 变小。

因此我们就可以证明 $k=\text{count\_bit}(n)+1$ 了（$\text{count\_bit}(n)$ 指 $n$ 二进制中 $1$ 的个数），但注意，$n$ 是 $2$ 的整数次幂时 $k=1$。

具体实现方法可以看代码（[不开 long long 见祖宗](https://codeforces.com/contest/1988/submission/270689492)）：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, n, bits[1000];
signed main()
{
	cin >> T;
	while (T--)
	{
		cin >> n;
		if (lowbit(n) == n)
		{
			cout << "1\n" << n << endl;
			continue;
		}
		bits[0] = 0;
		for (int i = 0; i <= 61; i++)
		{
			if (n & (1ll << i))
			{
				bits[++bits[0]] = (1ll << i);
			}
		}
		cout << bits[0] + 1 << endl;;
		for (int i = bits[0]; i >= 1; i--)
		{
			cout << n - bits[i] << " ";
		}
		cout << n << endl;
	}
	return 0;
}
```

---

## 作者：Chillturtle (赞：0)

# 题意

有 $t$ 个询问，每一次给出一个数 $n$，构造一个数组，使得 $a_i$ 与上 $a_{i+1}$ 的值为 $n$ 且使这个数组尽量长。

# 思路

首先，我们可以从这个**与运算**入手。我们知道与运算表示当两个数的二进制的两个对应位中有一个 $1$ 对应的答案位也就为 $1$。这里我们可以发现两个数的与运算结果是和这两个数的二进制码有关的且只和对应位是否有 $1$ 有关。所以我们需要用一种奇妙的函数来处理，一个数二进制编码中 $1$ 的个数。

隆重介绍 `lowbit` 函数（大佬绕道）。

`lowbit` 用于计算二进制最低位 $1$ 以及后面的 $0$ 组成的数。大概就长这样：

```cpp
int lowbit(int x){
	return x&(-x);
}
```

这里关于 `lowbit` 的原理就不再赘述，详情请查询 [oi-wiki](https://oi-wiki.org/ds/fenwick/#%E7%AE%A1%E8%BE%96%E5%8C%BA%E9%97%B4)。

相当于我们手上现在有了这个数中 $1$ 的个数。然后我们就可以在这一串 $1$ 里面插入 $0$。我们记 $1$ 的个数为 `one`，显然我们 $0$ 插进去后就有 `one+1` 种可能。这就是答案数组的长度最大值。这时，答案数组的各位数字也就很好求了。就是将 $0$ 插进去后，与 $1$ 组成的二进制数的十进制形式。这里我用了一个 `stack` 来存。注意，这个 $0$ 也是可以插在 $1$ 串的最前面的。

这里放张图来解释样例的第五个测试点：

![](https://cdn.luogu.com.cn/upload/image_hosting/jkn7exqm.png)

特别注意：当 $n$ 为 $1$ 的时候要进行特判。~~其实也可以在循环内判断~~。不开 `long long` 见祖宗。

# AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
stack<int> q;
int lowbit(int x){
	return x&(-x);
}
signed main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		q.push(n);
		int bf=n,lst=0;
		while(bf){
			int opt=bf;
			bf-=lowbit(bf);
			if(bf+lst==0){
				break;
			}else{
                n=bf+lst;
            }
			lst+=(opt-bf);
			q.push(n);
		}
		cout<<q.size()<<endl;
		while(q.size()!=0){
			cout<<q.top()<<" ";
			q.pop();
		}
		cout<<endl;
	}
return 0;
}
```

---

## 作者：LaDeX (赞：0)

题意简述如下：

> 给定一个正整数 $n$，请构造一个正整数序列使其满足以下条件并尽可能长：这个序列中每个数都大于等于 $1$ 且小于等于$n$；这个序列是单调递增的；这个序列中任意两个相邻的数按位或的结果都为 $n$。

通过手玩或者写个最长上升子序列可以发现，我们记这个数在二进制位上 $1$ 的个数为 $c$，当 $c=1$ 时，序列最长的长度为 $1$，否则为 $c+1$。

然后很显然的构造，当 $c=1$ 时直接输出自身，否则这 $c+1$ 个数中第 $i$ 个数为将 $n$ 从高位到低位第 $i$ 个 $1$ 改为 $0$ 后的值，当然第 $c+1$ 个数一定最大，就是 $n$。

最后为什么长度为 $c+1$ 时是最大的，可以感性理解一下，显然上文中的构造方法是每一个数都是 $n$ 的二进制下去掉一位，如果去掉的位数大于一位，又要保证其单调递增，那么长度就会小于 $c+1$。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
 
LL t[100], tot = 0;
 
int main() {
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	LL T, n; cin >> T;
	while (T --) {
		cin >> n; tot = 0;
		for (LL i = 0; i <= 62; i ++) {
			if ((n >> i) & 1) t[++ tot] = i;
		}
		if (tot == 1) {
			cout << "1\n" << n << "\n";
			continue;
		} else cout << tot + 1 << "\n";
		for (LL i = tot; i >= 1; i --) {
			cout << (n ^ (1LL << t[i])) << " ";
		}
		cout << n << "\n";
	}
	return 0;
}
```

---

