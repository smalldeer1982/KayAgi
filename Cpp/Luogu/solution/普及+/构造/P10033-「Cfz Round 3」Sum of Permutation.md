# 「Cfz Round 3」Sum of Permutation

## 题目描述

**请注意本题特殊的时间限制。**

给定一个 $1\sim n$ 的排列 $p$。

你需要构造一个长度为 $n$ 的序列 $a$，满足：

- 序列 $a$ 中的每个元素均为不大于 $n$ 的正整数；
- 不存在有序整数二元组 $(l,r)$，满足 $1 \le l \le r \le n$ 且 $\sum\limits_{i=l}^r a_i=\sum\limits_{i=l}^r p_i$；

或报告无解。

其中，$1\sim n$ 的排列指满足所有不大于 $n$ 的正整数恰好出现一次的序列。

## 说明/提示

#### 「样例解释 #1」

对于第 $1$ 组数据，$\{1,3,3\}$ 和 $\{1,1,3\}$ 均为满足条件的序列 $a$。

对于第 $2$ 组数据，可以证明不存在满足条件的序列 $a$。

对于第 $3$ 组数据，除 $\{5,3,2,1,1 \}$ 外，$\{3,4,5,3,2 \}$、$\{1,4,5,3,4 \}$、$\{5,3,3,4,5\}$ 等均为满足条件的序列 $a$。

#### 「数据范围」

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \le T \le 5000$，$2 \le n \le 10^6$，$\sum n \le 10^6$，保证 $p$ 是 $1\sim n$ 的排列。

**只有你通过本题的所有测试点，你才能获得本题的分数。**

**本题输入输出量较大，请使用较快的输入输出方式。**

## 样例 #1

### 输入

```
4
3
3 2 1
2
1 2
5
4 2 1 5 3
7
5 7 3 1 2 4 6```

### 输出

```
1 3 3
-1
5 3 2 1 1
2 3 5 4 6 3 1```

# 题解

## 作者：_•́へ•́╬_ (赞：17)

## 思路

我想全填 $1$。

cfz 说，不行，原排列有个 $1$，撞车了。

暴力枚举原排列那个 $1$ 的位置填啥，其他地方全填 $1$。

cfz 说，不行，`2 1 3`。

那就暴力枚举原排列那个 $n$ 的位置填啥，其他地方全填 $n$。

cfz 哭了，他卡不掉。

确实不存在以上两种方法都失败的情况。

## code

检验合法性的复杂度是 $\mathcal O(n\log n)$ 的。比标算稍劣。无所谓，cfz 本来想卡这个的来着，但是加个快读快写随便冲。

```cpp
#include<stdio.h>
#include<algorithm>
#define N 1000009
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
inline void pc(char x)
{
	static char buf[99999],*r=buf;
	(!x||(*r++=x,r==buf+99999))&&(fwrite(buf,1,r-buf,stdout),r=buf);
}
inline void pr(int x){if(x>9)pr(x/10);pc(x%10+'0');}
int t,n,m,a[N],b[N];long long c[N];
struct __readt__
{
	inline __readt__(){read(t);}
	inline~__readt__(){pc(0);}
}_readt___;
inline bool jg()
{
	c[0]=0;for(int i=1;i<=n;++i)c[i]=c[i-1]+a[i]-b[i];
	sort(c,c+n+1);
	for(int i=0;i<n;++i)if(c[i]==c[i+1])return 0;
	return 1;
}
main()
{
	read(n);for(int i=1;i<=n;read(a[i++]));
	for(int i=1;i<=n;b[i++]=1)if(a[i]==1)m=i;
	for(++b[m];b[m]<=n;++b[m])if(jg())
	{
		for(int i=1;i<=n;pr(b[i++]),pc(' '));
		goto nxt;
	}
	for(int i=1;i<=n;b[i++]=n)if(a[i]==n)m=i;
	for(--b[m];b[m];--b[m])if(jg())
	{
		for(int i=1;i<=n;pr(b[i++]),pc(' '));
		goto nxt;
	}
	pc('-');pc('1');pc('\n');
	nxt:if(--t)main();
}
```

---

## 作者：FFTotoro (赞：7)

题目链接：[$\color{Green}\texttt{P10033 「Cfz Round 3」Sum of Permutation}$](https://www.luogu.com.cn/problem/P10033)。

赛时过了 E 没过 D。挺不错的构造题。

下文令 $a$ 为给定排列，$b$ 为答案序列。

$n=2$ 显然无解，先判掉。可以证明用以下方法对于 $n\ge 3$ 的全部排列都可以构造出解。

对于题目有个比较显然的想法：将 $b$ 除了 $a_i=1$ 的 $i$ 全都执行 $b_i\leftarrow1$。

对于 $a_i=1$ 的那个 $i$，显然放的数越小越好。有一种**有纰漏**的做法：将一个正整数 $x$ 从 $2,3,\ldots$ 开始枚举，如果 $a_{i-1}$ 或 $a_{i+1}$ 存在且等于 $x$，那么这个 $x$ 显然不合法，继续往上枚举。找到最小的满足条件的 $x$ 即可。

但是这种做法在 $a_{i-1}\in\{2,3\}\land a_{i+1}\in\{2,3\}$ 的时候 $x=4$，在序列为 $\{2,1,3,4\}$ 时会出错（此时 $a_2+a_3+a_4=2+3+1=6=4+1+1=b_2+b_3+b_4$）。于是考虑在这种情况下进行一些微调。具体地，构造 $b_{i-1}\leftarrow a_{i+1}$，$b_i=3$，$b_{i+1}\leftarrow a_{i-1}$。

但还可能出现 $a_{i-2}+a_{i-1}+a_i=b_{i-2}+b_{i-1}+b_i$ 的情况（这是与 $i-2$ 出现冲突的情况，$i+2$ 类似），此时构造 $b_{i-1}\leftarrow 1,b_i\leftarrow 4,b_{i+1}\leftarrow 2$ 即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
  int x=0; char c=getchar();
  while(!isdigit(c))c=getchar();
  while(isdigit(c))x=x*10+c-48,c=getchar();
  return x;
} // 快读
void write(int x){
  if(x>9)write(x/10);
  putchar(x%10+48);
} // 快写
int main(){
  int t=read();
  while(t--){
    int n=read();
    vector<int> a(n),b(n);
    for(auto &i:a)i=read();
    if(n<=2){cout<<"-1\n"; continue;} // 无解
    bool f=true;
    for(int i=0;i<n&&f;i++)
      if(b[i]=(a[i]==1)+1;a[i]==1){
        while(i&&a[i-1]==b[i]||i<n-1&&a[i+1]==b[i])b[i]++;
        if(b[i]>n||a[i-1]+a[i]+a[i+1]==b[i-1]+b[i]+1)f=false;
      }
    if(!f){ // 第一种构造方式有问题，使用第二种
      fill(b.begin(),b.end(),1);
      for(int i=0;i<n;i++)
        if(a[i]==1){
          b[i-1]=a[i+1],b[i]=3,b[i+1]=a[i-1];
          if(i+2<n&&a[i]+a[i+1]+a[i+2]==b[i]+b[i+1]+b[i+2])b[i+1]=1,b[i]=4,b[i-1]=2;
          if(i>=2&&a[i]+a[i-1]+a[i-2]==b[i]+b[i-1]+b[i-2])b[i-1]=1,b[i]=4,b[i+1]=2;
        } // 进行微调
    }
    for(int i:b)write(i),putchar(32);
    putchar(10); // 汇报答案
  }
  return 0;
}
```

---

## 作者：SkyWave (赞：6)

不喜欢特判？不喜欢分讨？不喜欢被卡 corner？不喜欢证明？不喜欢动脑子？

那就看这篇题解！

# 感性思路

首先感性地感受一下题目宽泛的限制条件题解区各种花式的构造方法就不难想出，符合条件的序列实在很多，那不是随便构造？但是随便上随机化还是很容易被卡而且常数太大，又不想写屎山分讨被 corner 卡到心态爆炸，怎么办！

爆搜！直接每一位枚举 $[1, n]$，先不说枚举到一个合法解的复杂度，朴素地检查需要把序列每一位都搜完，并且光检查就要 $O(n^2)$。我们需要将序列合法条件进行转换，最好做到若一位填的不合法立刻剪枝，就有希望很对！

首先 $\sum\limits_{i=l}^{r} a_i = \sum\limits_{i=l}^{r} p_i$ 容易转换成 $\sum\limits_{i=l}^{r} (a_i - p_i) = 0$，令 $b_i = a_i - p_i$，那么这个条件就再次转换为序列 $b$ 的前缀和序列没有两项是相同的（注意也不能为 0）。那么搜索的时候再记一个参数表示当前 $a_i-p_i$ 的前缀和即可。注意出题人卡了一个 $n \log n$，于是要用 ```unordered_set``` 检查。

# 理性证明

刚才只是感性理解了一下时间和做法，实际上这个时间是可以被证明的！

首先不难发现每次检查的都是一个前缀，那么也就是说如果前 $i$ 个数合法，第 $i + 1$ 个数没有冲突，那么前 $i + 1$ 个数合法。搜索产生回溯当且仅当第 $i + 1$ 个数与任意一个前缀都冲突。而随着 $n$ 增大，前缀和的产生的值域范围也是非常大的，也就是不满的。可以证明 $n$ 大于一个定值是一定不会产生回溯的。只有经过特殊构造的 $n$ 很小的时候才会产生回溯。但是还有一个问题，无解会将搜索跑满，那时间复杂度就不对了？但注意无解是强于存在回溯的，也就是值域要求更加窄。可以证明，当且仅当 $n=2$ 时才会产生无解。

还有一个好玩的性质，只要有解，那么必定能构造出一组使得 $\forall p_i \leq 4$。综上所述，可以认为时间复杂度最坏为 $O(Vn)$，其中 $V$ 为构造一组合法的 $p$ 要用到的最大的 $p_i$，最大为常数 4。复杂度正确。

# 实现代码

```cpp

#include <iostream>
#include <unordered_set>
using namespace std;
typedef long long ll;

int uread() {
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    int num = 0;
    while (c >= '0' && c <= '9') {
        num = (num << 1) + (num << 3) + (c ^ 48);
        c = getchar();
    }
    return num;
}

const int N = 1e6 + 1;

int n;
int a[N], b[N];

unordered_set<ll> st;

bool dfs(int pos, ll sum) {
    if (pos == n + 1) {
        return true;
    }
    for (int i = 1; i <= n; ++i) {
        if (a[pos] == i) {
            continue;
        }
        ll now = sum + a[pos] - i;
        if (st.count(now)) {
            continue;
        }
        st.insert(now);
        b[pos] = i;
        if (dfs(pos + 1, now)) {
            return true;
        }
        st.erase(now);
    }
    return false;
}

void solve() {
    n = uread();
    for (int i = 1; i <= n; ++i) {
        a[i] = uread();
    }
    st.clear(); st.insert(0ll);
    if (!dfs(1, 0ll)) {//或直接特判 n == 2
        puts("-1");
        return ;
    }
    for (int i = 1; i <= n; ++i) {
        printf("%d ", b[i]);
    }
    putchar('\n');
}

int main(int argc, const char * argv[]) {
    int T = uread();
    while (T--) {
        solve();
    }
    return 0;
}


```


---

## 作者：pp_orange (赞：5)

[原题链接](https://www.luogu.com.cn/problem/P10033)

一个新思路。看了其他题（乱）解（搞），感觉其实挺神秘的，我没想到这样就过了。所以提供一个从**模**和**函数**的角度的思路。

先把 $n=2$ 和 $n=3$ 特判掉，暴力即可。

由于后续思路涉及取模，所以不妨设 permutation 的值域为 $[0,n)$。


我们记 $A=n-1,B=n-2$，即最大和次大。

考虑所有的数字都等于 $A$，只有 $A$ 改为 $B$，此时要求 $A$ 和 $B$ 不相邻即可。

我们于是转手考虑 $A$ 和 $B$ 相邻的情况。

考虑模 $n$ 意义下函数 $f(x) = x+1$ 直接使用此函数不行，**全局的 $sum$ 有问题**，但是局部的 $sum$ 一定没有问题，可以在模 $n$ 意义下证明这里局部的 $sum$ 不相等。

现在我们考虑把其中的**少量的数字再加一**来克服这个问题。

考虑 $A$ 和 $B$ 的位置，分 $3$ 类：

- `...AB...`：此时让 $A$ 和 $B$ 的位置再加一即可，可以证明，如果在模 $n$ 意义下 $\sum\limits_{i=l}^r a_i=\sum\limits_{i=l}^r p_i$，那么这个区间必然包括 $A$ 和 $B$，但是这两个数字先 $+2$ 后模 $n$，等价于 $A=A+2-n,B=B+2-n$，减去了 $2$ 个 $n$，但是其他数字加的 $1$，总共也没有 $n$，所以显然不行。


- `BA.....`：$B$ 处再加 $1$ 即可，证明类似。

- `AB....C`：$B,C$ 再加 $1$ 即可，证明类似。（$C$ 在 $A$ 的对面，可以是任何数）

任何情况都可以归约到上面（如果不行就把 $p$ 翻转一下）

做法核心在于，使用模 $n$ 进行必要性探路，在不合法处再调整并说明。事实上，在其他题你可以看见类似的 trick。

参考程序：

```cpp
/* Code by pp_orange */
//#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define m_p(a,b) make_pair(a,b)
#define pb push_back
#define ll long long
#define ull unsigned long long
#define ld long double
#define inf 0x7FFFFFFF
#define inff 9223372036854775807
#define rep(i,l,r) for(int i=l;i<r;++i)
#define repp(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r-1;i>=l;--i)
#define pper(i,r,l) for(int i=r;i>=l;--i)
#define pii pair<int,int>
#define fi first
#define se second
#define p_q priority_queue
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
#define lb(x) ((x)&-(x))
const int mod = 998244353;
//#define int ll
using namespace std;
namespace FastIO {
	const int SZ=(1<<21)+1;
	struct I {
		char ibuf[SZ],*iS,*iT,c;int f,_eof;FILE*fi;
		I(FILE*f):fi(f){}
		inline char Gc(){return iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SZ,fi),(iS==iT?EOF:*iS++)):*iS++;}
		inline ll operator()(){ll x;operator()(x);return x;}
		inline I&operator()(char&x){x=Gc();return*this;}
		inline I&operator()(char*s){for(c=Gc();c<32||c>126||c==' ';)c=Gc();for(;c>31&&c<127&&c!=' '&&c!='\n'&&c!='\r';++s,c=Gc())*s=c;*s=0;return*this;}
		template<class T>inline I&operator()(T&x){_eof=0;for(f=1,c=Gc();(c<'0'||c>'9')&&!_eof;c=Gc()){if(c=='-')f=-1;_eof|=c==EOF;}for(x=0;c<='9'&&c>='0'&&!_eof;c=Gc())x=x*10+(c&15),_eof|=c==EOF;x*=f;return*this;}
		template<class T>I&operator()(T*x,const int&n,const int&st=1){rep(i,st,n){operator()(x[i]);}return*this;}
	} rd(stdin);
	struct O {
		char obuf[SZ],*oS=obuf,*oT=oS+SZ-1,qu[55];int f,qr;FILE*fi;
		O(FILE*f):fi(f){}
		~O(){Flush();}
		inline void Flush(){fwrite(obuf,1,oS-obuf,fi),oS=obuf;}
		inline O&operator()(char x){*oS++=x;if(oS==oT)Flush();return*this;}
		inline O&operator()(char*s){int len=strlen(s);for(f=0;f<len;++f)operator()(s[f]);return*this;}
		inline O&operator()(const char*s){return operator()((char*)s);}
		template<class T>inline O&operator()(T x){if(!x)operator()('0');if(x<0)operator()('-'),x=-x;while(x)qu[++qr]=x%10+'0',x/=10;while(qr)operator()(qu[qr--]);return*this;}
		template<class T>O&operator()(T*x,const int&n,const char&ed=' ',const int&st=1){rep(i,st,n)operator()(x[i])(ed);return*this;}
	} out(stdout);
}
using namespace FastIO;
#define MAX 1000005
int a[MAX];
signed main(){
	//freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
	int T = rd();
	while(T--){
		int n = rd();
		repp(i,1,n)a[i] = rd();
		if(n==2){
			out(-1)('\n');
		}else if(n==3){//暴力
			bool flag = 0;
			repp(i,1,3){
				if(i==a[1])continue;
				repp(j,1,3){
					if(j==a[2])continue;
					repp(k,1,3){
						if(k==a[3])continue;
						if(i+j!=a[1]+a[2]&&j+k!=a[2]+a[3]&&i+j+k!=6){
							out(i)(' ')(j)(' ')(k)('\n');
							flag = 1;
							break;
						}
					}
					if(flag)break;
				}
				if(flag)break;
			}
			if(!flag)out(-1)('\n');
		}else{
			int n1,n2;
			repp(i,1,n){
				if(a[i]==n)n1 = i;
				if(a[i]==n-1)n2 = i;
			}
			if(abs(n1-n2)!=1){//相邻
				repp(i,1,n){
					if(a[i]==n)out(n-1)(' ');
					else out(n)(' ');
				}out('\n');
			}else{
				if(n1==1||n1==n){//第三类
					repp(i,1,n){
						if(i==n2||i==n+1-n1){
							out((a[i]+1)%n+1)(' ');
						}else{
							out((a[i]%n)+1)(' ');
						}
					}out('\n');
				}else if(n2==1||n2==n){//第二类
					repp(i,1,n){
						if(i==n2){
							out((a[i]+1)%n+1)(' ');
						}else{
							out((a[i]%n)+1)(' ');
						}
					}out('\n');
				}else{//第一类
					repp(i,1,n){
						if(i==n1||i==n2){
							out((a[i]+1)%n+1)(' ');
						}else{
							out((a[i]%n)+1)(' ');
						}
					}out('\n');
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：wosile (赞：4)

全场最鬼畜题，虽然我很不想写一个绿题的题解但是这题卡了我一个小时。

关于评分 6：

作为一个生活中发现的小 trick，这题是极好的。我也希望我平时能注意到这玩意然后扔给数竞同学等他们骂人。

作为一个数学题，这题是可行的。

作为一个 OI 题，只能说未来可期吧。

刚读到题感觉这题十分不可做，随后发现如果全填 $1$ 那么只有 $a_i=p_i=1$ 不满足。

（以下讨论基于 $n \ge 6$，$n \le 5$ 的情况直接枚举就好了）

方便起见，我们称 $q_i$ 为 $i$ 在 $p$ 中的出现位置，即 $p_{q_i}=i$，$q$ 是 $p$ 的逆排列。

考虑取 $a_{q_1}=2$，这样 $[q_1,q_1]$ 区间确实符合条件了，但是如果 $q_2=q_1+1$ 的话就会有一个区间 $[q_1,q_2]$ 不符合题意，在 $a$ 和 $p$ 上这个区间的和都是 $1+2=3$。

那么如果在 $q_2=q_1+1$ 的时候取 $a_{q_1}=3$ 呢？$q_3=q_1-1$ 的情况会让 $[q_3,q_1]$ 这个区间也不合法。在 $a$ 和 $p$ 上这个区间的和都是 $1+3=4$。

那么如果 $2,3$ 都和 $1$ 相邻，取 $a_{q_1}=4$ 总没问题了吧？然后我以为这是对的，就这么交了。看了半天才发现自己样例都没过。

沿用上面 $q_3+1=q_1=q_2-1$ 的设定，考虑 $[q_3,q_2]$ 这个区间，在 $a$ 上的和是 $1+4+1=6$，在 $p$ 上的和是 $3+1+2=6$。

做到这里你可能有点怀疑除了 $a_{q_1}$ 全填 $1$ 这个做法的正确性，但是先别急，只要有信仰，这么做就是对的。

我们填 $a_{q_1}=5$。

你会发现仍然不对，如果 $q_4=q_2+1=q_1+2=q_3+3$（$p$ 中有一段 $3\;1\;2\;4$），$[q_1,q_5]$ 有 $1+2+4=5+1+1$。

不要放弃，做题耐心是很重要的。

注意我们每讨论掉一种取值，数列的性质就多了一条。要使得 $a_{q_1} \le 5$ 的填法均不成立，我们需要 $q_2=q_1 \pm 1,q_3=q_1 \pm 1, q_4=q_2 \pm 1$。

考虑 $a_{q_1}=6$，乍看之下如果出现 $q_5=q_2+1$ 就会有 $[q_1,q_5]$ 上 $1+2+5=6+1+1$，并且在 $q_4=q_3-1$ 的时候也会有 $[q_4,q_1]$ 上 $4+3+1=1+1+6$，但实际上这两种情况都不会出现，**只有 $2$ 和 $4$ 相邻的情况下 $a_{q_1}=5$ 才会不成立，而此时 $2$ 不可能再和 $5$ 相邻，$3$ 也不可能再和 $4$ 相邻。** 所以，如果 $a_{q_1} \le 5$ 的填法都不成立，填 $a_{q_1}=6$ 一定成立。

---

## 作者：Coffee_zzz (赞：4)

首先手玩可以发现，$n=2$ 的两种情况都无解，所以 $n=2$ 时无解。

接下来考虑其他情况。

我们令 $k_i=p_i-a_i$。

想使不存在有序整数二元组 $(l,r)$ 满足 $1 \le l \le r \le n$ 且 $\sum\limits_{i=l}^r a_i=\sum\limits_{i=l}^r p_i$，其实就是要使不存在有序整数二元组 $(l,r)$ 满足 $1 \le l \le r \le n$ 且 $\sum\limits_{i=l}^r k_i=0$。于是就有一个非常基本的构造思路：使 $k_i$ 的值都尽可能大于 $0$，这样满足 $\sum\limits_{i=l}^r k_i\le0$ 的区间就会尽可能少。

于是，当 $p$ 中 $1$ 与 $2$ 不相邻时，设 $p_x=1$，$p_y=2$，可以令 $a_x=2$，其余的元素均为 $1$。此时 $k_x=-1$，$k_y=1$，其余的 $k_i$ 均满足 $k_i\gt1$。由于 $1$ 与 $2$ 不相邻，正确性显然。

那我们考虑 $p$ 中 $1$ 与 $2$ 相邻的情况。

若 $1$ 与 $2$ 相邻但不与 $3$ 相邻，设 $p_x=1$，$p_y=2$，$p_z=3$，可以令 $a_x=3$，其余的元素均为 $1$。此时 $k_x=-2$，$k_y=1$，$k_z=2$，其余的 $k_i$ 均满足 $k_i\gt2$。由于 $1$ 与 $3$ 不相邻，正确性也显然。

若 $1$ 与 $2$ 和 $3$ 均相邻，要分两种情况讨论：

- 若 $n=3$，设 $p_x=3$，则可以令 $a_x=2$，其余两个元素为 $3$。枚举所有情况可以发现这样构造是满足条件的。

- 若 $n\gt 3$，设 $p_x=1$，$p_y=2$，$p_z=3$，则可以令 $a_x=4$，$a_z=2$，其余的元素均为 $1$。此时 $k_x=-3$，$k_y=1$，$k_z=1$，其余的 $k_i$ 均满足 $k_i\ge3$。由于 $1$ 与 $2$ 和 $3$ 均相邻，正确性同样显然。

总复杂度 $\mathcal{O}(n)$。

```c++
#include <bits/stdc++.h>

using namespace std;
const int N=1e6+5;
int a[N],v[N],n;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],v[a[i]]=i;
	if(n==2) cout<<"-1\n";
	else if(abs(v[1]-v[2])==1){
		if(abs(v[1]-v[3])==1){
			if(n==3) for(int i=1;i<=n;i++) cout<<(a[i]==3?2:3)<<(i==n?'\n':' ');
			else for(int i=1;i<=n;i++) cout<<(a[i]==1?4:(a[i]==3?2:1))<<(i==n?'\n':' ');
		}
		else for(int i=1;i<=n;i++) cout<<(a[i]==1?3:1)<<(i==n?'\n':' ');
	}
	else for(int i=1;i<=n;i++) cout<<(a[i]==1?2:1)<<(i==n?'\n':' ');
}
signed main(){
	ios::sync_with_stdio(0);
	int T=1;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：int_R (赞：3)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/17937893/P10033)

[原题链接](https://www.luogu.com.cn/problem/P10033)

基础赛唯一写了的题，因为我喜欢构造！

事实上的确有点麻烦了，应该会有更好的做法。但是自我感觉这个思维很连贯，因为这就是我做题时思路的写照。

记 $p_{pos1}=1,p_{posn}=n$。

首先可以构造 $a_i\gets p_i+1$ 这样一定满足第二个限制，但是当 $p_i = n$ 时不满足第一个限制。

钦定 $pos1<posn$，否则将整个序列翻转即可使 $pos1<posn$。

先假设 $posn\not = n$（由于钦定了 $pos1<posn$ 所以 $posn\not = 1$）。

于是考虑对于 $j < posn,a_j\gets p_j+1$，对于 $j > posn,a_j\gets p_j-1$，$a_{posn}=n-{posn}$。

证明一下为什么正确。当区间 $[l,r]$ 不包含 $posn$ 即完全位于左边或者右边时，其相当于一开始那个东西，是肯定正确的。当区间 $[l,r]$ 包含 $posn$，发现 $\forall i<posn,\sum\limits_{j=i}^{posn-1} (a_j-p_j)\in [1,posn-1]$，在加上 $a_{posn}-p_{posn}$ 之后范围变成 $[1-posn,-1]$，再往后加也一定是负数，不会为 $0$ 所以不会相等。

再说 $posn = n$，你会发现这种时候直接用上面那种 $p_n=0$ 就寄了。但是这种特例很好处理，只需要 $j<n,a_j\gets n,a_n=\begin{cases} n-1 & p_{n-1}\not = n-1 \\ n-2 & p_{n-1} = n-1 \end{cases}$ 即可。

然后你发现 $n\leq 2$ 这个东西又寄了，然后你发现 $n\leq 2$ 无解。


---

## 作者：M1saka16I72 (赞：1)

# Cfz Round 3 E / [洛谷 P10033](https://www.luogu.com.cn/problem/P10033) 题解

## 前言
[更孬的阅读体验](https://misaka16172.github.io/solution-p10033.html)

我场切了，看来这场题目顺序很诈骗，明明 C 和 D 都没写出来。

等等，这道题竟然评绿了？

好激动，第一次场切绿，所以来写篇题解。


## 题意

给定一个 $1\sim n$ 的排列 $p$。你需要构造一个长度为 $n$ 的序列 $a$，满足：
- 序列 $a$ 中的每个元素均为不大于 $n$ 的正整数；
- 不存在有序整数二元组 $(l,r)$，满足 $1 \le l \le r \le n$ 且 $\sum\limits_{i=l}^r a_i=\sum\limits_{i=l}^r p_i$；或报告无解。

其中，$1\sim n$ 的排列指满足所有不大于 $n$ 的正整数恰好出现一次的序列。

### 数据范围

设 $\sum n$ 表示单个测试点中 $n$ 的和。

对于所有数据，$1 \le T \le 5000$，$2 \le n \le 10^6$，$\sum n \le 10^6$，保证 $p$ 是 $1\sim n$ 的排列。

## 思路

我们可以尝试考虑最终答案序列 $a$ 的形式。

$a$ 和原序列 $p$ 一样都由从 $1$ 到 $n$ 的整数构成，但不同点在于 $a$ 并不是 $1\sim n$ 的排列，$a$ 中的数字出现多少次都可以。

而题目里要求 ${\forall}l,r \in [1,n]$，$\sum\limits_{i=l}^r a_i≠\sum\limits_{i=l}^r p_i$，直觉告诉我让 $p$ 中的全部数字都大于 $a$ 就能很轻松地满足这个条件了；

但 $p_i$ 的取值最大只能为 $n$，且序列 $a$ 里必定有一个 $n$，所以一个全部为 $n$ 的 $p$ 序列已经可以满足除了 $l=r=i(a_i=n)$ 的所有情况了，因为不管怎么取 $l$ 和 $r$，$\sum\limits_{i=l}^r p_i$ 都一定是大于 $\sum\limits_{i=l}^r a_i$ 的。

那么 $a_i=n$ 的这一位 $p_i$ 该怎么改呢？我们顺着刚刚的思路，也给 $i$ 这一位放一个除了 $n$ 以外尽量大的数，设这个数 $p_i=n-k (1\leq k<n )$。

那么在取 $l,r$ 时，如果 $l>i$ 或 $r<i$，则 $\sum p$ 的值仍为 $(r-l+1)\times n$ 不受影响，一定满足要求；

但如果 $l\leq i\leq r$，$\sum p$ 就不一定能够大于 $\sum a$ 了。

于是我们换个思路，尝试让 $p_i$ 的值能够取到一个临界值 $[l_S,r_S]$，正好使这时在 $[l_S,r_S]$ 内的 $\sum p<\sum a$，但凡 $l$ 再比 $l_S$ 小 $1$ 或 $r$ 比 $r_S$ 大 $1$，$\sum p$ 就会超过 $\sum a$。

上述的这个过程我们可以通过从大到小枚举 $p_i$ （也就是 $n-k$），同时枚举 $l$ 和 $r$ 完成，看起来枚举了三个数很吓人，实际上复杂度并不高，因为临界值很快就会被取到，不信的话可以尝试构造一个能够尽量增加枚举次数的序列 $a$，它大概长成这个样子：

> $\cdots n-2,n,n-1,n-3,\cdots $

可以看到，上面的这个序列已经很努力地在卡掉了 $p_i(a_i=n)$ 在 $[n-3,n-1]$ 中的值，但这已经是它能做到的极限了，不太优雅的证明如下：

当序列 $a$ 能卡掉 $p_i=n-1$、$n-2$ 时，$n-1$ 与 $n-2$ 一定正好在 $n$ 的两侧，此时 $n-3$ 自然也被卡掉了；

想卡掉 $n-4$ 就只能在 $n-1$ 的同一侧放一个 $n-3$，但这样做你就永远卡不掉 $n-5$ 了，因为 $n-3$ 与 $n-1$ 在同侧，与 $n-2$ 在异侧；

反之亦然，如果想卡掉 $n-5$ 那 $n-4$ 就一定没法被卡掉。

所以我们不太优雅地证明了在 $[n-5,n-1]$ 里一定能取到 $p_i$。
 
到这里我们几乎已经解决了本题，接下来考虑序列 $a$ 的长度 $n$ 太小，导致 $n-5<1$ 的情况，下面是一个例子：

```
4
2 4 3 1
```
显然我们取遍了 $p_i$ 也没能取到一个值不会被特定的 $[l,r]$ 给卡掉，但有了前面的经验，我们只要反过来构造就好了：

把除了 $a_i=1$ 对应的 $p_i$ 以外的 $p$ 值都设成 $1$，让 $\sum p$ 尽量小于 $\sum a$，然后再枚举 $p_i$ 即可。

用上面的方法就能构造出序列 `1 1 1 2`，满足条件。

如果上面两种方法都构造不出来序列 $p$，那就是因为序列长度 $n$ 过短（也就是 $n=2$），可以证明这个时候一定无解，输出 `-1` 即可。


## 代码
```cpp
int a[1000005],ans[1000005],pf[1000005];
inline int ques(int l,int r){return pf[r]-pf[l-1];}
void solve() {
    int t;read(t);
    pf[0] = 0;
    while(t--){
        int n;read(n);
        for(int i=1;i<=n;i++)   read(a[i]);
        for(int i=1;i<=n;i++)   pf[i] = pf[i-1]+a[i];   //前缀和处理一下方便查询
        a[0] = 0;a[n+1] = 0;
        bool get = 0;
        for(int i=1;i<=n;i++){
            if(a[i]!=n) ans[i] = n;
            else{
                for(int j=n-1;j>=1;j--){    //枚举这个位置该填的值
                    get = 1;
                    int sum = n,fsum = j;   //原数列a在该区间的和与构造出的数列的和
                    for(int l=0;i-l>=1;l++){
                        for(int r=0;i+r<=n;r++){
                            sum = n+(l?ques(i-l,i-1):0)+(r?ques(i+1,i+r):0);    //枚举区间[n-l,n+r]
                            fsum = j+(l+r)*n;
                            if(fsum>=sum){  //到了临界值
                                if(fsum==sum)   get = 0;    //这个值j不可用
                                break;
                            }
                        }
                    }
                    if(get){
                        ans[i] = j; //取到了符合条件的j
                        break;
                    }
                }
            }
        }
        if(get){
            for(int i=1;i<=n;i++)   cout<<ans[i]<<" ";
        }
        else{
            for(int i=1;i<=n;i++){  //再次尝试用n-1个1构造序列p
                if(a[i]!=1) ans[i] = 1;
                else{
                    for(int j=2;j<=n;j++){
                        get = 1;
                        int sum = 1,fsum = j;
                        for(int l=0;i-l>=1;l++){
                            for(int r=0;i+r<=n;r++){
                                sum = n+(l?ques(i-l,i-1):0)+(r?ques(i+1,i+r):0);
                                fsum = j+(l+r)*n;
                                if(fsum<=sum){
                                    if(fsum==sum)   get = 0;
                                    break;
                                }
                            }
                        }
                        if(get){
                            ans[i] = j;
                            break;
                        }
                    }
                }
            }
            if(get){
                for(int i=1;i<=n;i++)   cout<<ans[i]<<" ";
            }
            else    cout<<-1;   //这都构造不出来就是真无解了
        }
        cout<<"\n";
    }
}
```
## 其他

感觉自己能做出来这道题还是因为最近 cf 的毒瘤题刷的比较多，可能对思维有点用；但是这一场的 C 和 D 竟然都没写出来，数论、位运算之类的还是要多练练，以及这场虽然没考到但我的算法也非常菜。

写这篇题解是在比赛当天($2023/12/31$)，希望大家在新的一年里都能在 OI 上取得好成绩。

以上，如果题解里有疏漏的地方欢迎各位神犇指正。

---

## 作者：indream (赞：1)

## P10033 「Cfz Round 3」Sum of Permutation 题解
[P10033](https://www.luogu.com.cn/problem/P10033) | [AC](https://www.luogu.com.cn/record/141611371)
### 构造方法
首先根据样例，$n=2$ 时显然无解。

其他情况均有解：我的构造方法比较抽象，欢迎来 Hack！

首先把所有的 $ans_i$ 赋值为 $1$。这样只要 $[l,r]$ 范围内不存在 $1$ 时，满足条件。

那考虑 $1$ 怎么处理？设 $a_x=1$，观察 $a_{x-1}$ 和 $a_{x+1}$：显然不能让以下成立：$ans_x=a_{x-1}$ 及 $ans_x=a_{x+1}$。显然应让 $ans_x$ 最小，那么让其取最小自然数即可，共 $2$、$3$、$4$ 三种可能。但如果 $a$ 序列、$ans$ 序列如下时，构造失败：
```
a:  4 3 1 2 5
ans:1 1 4 1 1
```
怎么办呢？考虑将 $a_2=3$ 对应的位置换成 $ans_2=2$ 即可。此时易证无法构造出来干掉这个方法的数据。

这种构造方法需要特判 $n=3$ 且 $a_2=1$ 的情况，这次令 $a_x=3$ 对应的 $ans_x=2$，其余的 $a_i=3$ 即可。

综上所述模拟，可以通过此题。

时间复杂度 $O(n)$。
### 最终代码
代码中让答案直接覆盖了 $a$ 序列。

~~赛事丑陋代码勿喷。~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1000005];
int _1,rem,x,y;
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        if(n==2){
            scanf("%d %d",&a[1],&a[2]);
            puts("-1");
            continue;
        }
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);
            if(a[i]==1)_1=i;
        }
        if(n==3&&_1==2){
            for(int i=1;i<=3;++i)
                cout<<((a[i]==3)?"2 ":"3 ");
            putchar('\n');
            continue;
        }
        rem=0;
        x=a[_1-1];y=a[_1+1];
        for(int i=1;i<=n;++i){
            if(i==_1){
                for(int j=2;j<=4;++j){
                    if(x!=j&&y!=j){
                        a[i]=j;
                        if(j==4)rem=1;
                        break;
                    }
                }
                continue;
            }
            if(rem&&a[i]==3)a[i]=2;
            else if(rem&&a[i]==2)a[i]=1,a[i-2]=2;
            else a[i]=1;
        }
        for(int i=1;i<=n;++i)
            printf("%d ",a[i]);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：min_inf (赞：1)

不知道对不对，欢迎 Hack。

方便起见我们将 $p$ 转化为 $0 \sim n-1$ 的排列。

瞎玩会样例，猜一个结论：只有 $p_i=0$ 的位置 $a_i \ne 0$，设这个位置为 $x$。考虑怎么求 $a_x$，显然如果有不符合要求的区间一定有 $l \le x \le r$，那么 $\sum\limits_{i=l}^r p_i=a_x$。分两侧的贡献卷积一下找个凑不出来的位置即可。

注意到由于 $p$ 是排列，所以 $p_i$ 互不相同，只需要拿 $O(\sqrt n)$ 个 $p_i$ 就会超过 $n$ 了，所以这个卷积暴力卷即可，复杂度 $O((\sqrt n)^2)=O(n)$。

把这个东西交上去会 WA 一个点，所以如果跑不出解就把序列取反再跑一遍，然后就过了。

```cpp
int work(vector<int> &a,int n){
    int pos;
    rep(i,0,n-1)if(!a[i])pos=i;
    vector<int> f(n),v1{0},v2{0};
    int s=0;
    per(i,pos-1,0){
        s+=a[i];
        if(s>=n)break;
        v1.push_back(s);
    }
    s=0;
    rep(i,pos+1,n-1){
        s+=a[i];
        if(s>=n)break;
        v2.push_back(s);
    }
    for(auto i:v1)for(auto j:v2)if(i+j<n)f[i+j]=1;
    int res=0;
    while(res<n&&f[res])++res;
    return res;
}
void solve(){
    int n;
    cin>>n;
    vector<int> a(n);
    rep(i,0,n-1)cin>>a[i],--a[i];
    int r=work(a,n);
    if(r==n){
        rep(i,0,n-1)a[i]=n-a[i]-1;
        r=work(a,n);
        if(r==n){
            cout<<"-1";
        }
        else{
            rep(i,0,n-1)cout<<(a[i]?n:n-r)<<' ';
        }
    }
    else{
        rep(i,0,n-1)cout<<(a[i]?1:r+1)<<' ';
    }
    cout<<'\n';
}
```


---

## 作者：Vct14 (赞：0)

第一个思路是全都取 $1$ 或全都取 $n$，即最大的数和最小的数，因为这样可以使与原排列的区间之和相等的区间和尽量少。但是这样有一个问题：$p$ 为一个排列，一定含有 $1$。那么枚举一下 $p$ 中 $1$ 的位置填什么即可。$n$ 也同理。两种方法必有一种可以满足题意。

后来发现 $n=2$ 无解，输出 $-1$。

---

## 作者：Erica_N_Contina (赞：0)

## 思路

构造题！

首先因为 $p_i$ 是混沌状态，所以我们的 $a$ 中填什么都是不稳妥的——除了 $1$ 和 $n$。我们貌似找到了一个很巧妙的构造方法，同时也是最简单的构造方法：全填 $1$。

这个构造方法是天衣无缝的，除非——我们知道，$p_i=1$，并且有一个区间是 $[i,i]$。这是唯一一个问题了。所以如果 $p_i=1$，那么我们 $a_i$ 就不可以填 $1$ 了。那怎么办呢？暴力枚举 $2\sim n$ 中的每一个数并且判断是否合法！

但是经过缜密思考，我们发现这种方法不可信！就比如在 $p=[2,1,3]$ 时，可以验证 $a=[1,2,1],[1,3,1]$ 都是不合法的！我们发现问题的关键所在就是 $\sum a_{l\sim i}$ 可能会等于 $\sum p_{l\sim i}$，或者是 $\sum a_{i\sim r}$ 可能会等于 $\sum p_{i\sim r}$。为什么？因为从 $p_i$ 向外扩散是从 $1$ 开始且增大的，从 $a_i$ 向外扩散是从 $s(s>1)$ 开始且减小的。

形象证明就是：我们考虑第一象限的两条线段 $l_1,l_2$，一条斜率 $>0$，另一条斜率 $<0$，记录 $l_1$ 到其在 $x$ 上的投影扫过的面积为 $S_2$，$S_2$ 亦然。那么一定可以构造出 $S_1=S_2$。

所以我们在发现这种构造不合法后，应该怎么做？——别忘了，我们还有一种方法没有用：全填 $n$。和全填 $1$ 类似，这种方法也有什么的问题。但是可以证明，这两个问题是**不会同时出现**的。于是我们都解法就出来了。

---

判断合法我们可以使用 $O(n\log n)$ 的算法。不合法即 $a,p$ 两个序列有一个区间的和相同。即这两个区间的和的差为 $0$。我们维护一个序列 $c$，$c_i=p_i-a_i$，并且将其前缀和化。现在我们就是要判断是否有 $c_i=c_j$。如果有，就说明 $[i,j]$ 区间不合法。

---

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define ps second
#define pf first
 
 
#define rd read()
inline int read(){
	int xx=0,ff=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') ff=-1;c=getchar();}
	while(c>='0'&&c<='9') xx=xx*10+(c-'0'),c=getchar();
	return xx*ff;
}
inline void write(int out){
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int INF=1e9+5;
int MOD=1e9+7;
const int N=3e6+5;

int n,m,p[N],k;
int a[N],c[N];

inline bool check(){
	c[0]=0;
	for(int i=1;i<=n;++i)c[i]=c[i-1]+p[i]-a[i];
	sort(c,c+n+1);
	for(int i=0;i<n;++i)if(c[i]==c[i+1])return 0;
	return 1;
}

void solve(){
	for(int i=1;i<=n;i++)p[i]=rd,a[i]=1;
	for(int i=1;i<=n;i++)if(p[i]==1)m=i;

	for(int i=2;i<=n;i++){
		a[m]=i;
		if(check()){
			for(int i=1;i<=n;i++)cout<<a[i]<<' ';
			cout<<endl;
			return ;
		}
	}
	for(int i=1;i<=n;i++)a[i]=n;

	for(int i=1;i<=n;i++)if(p[i]==n)m=i;
	for(int i=1;i<n;i++){
		a[m]=i;
		if(check()){
			for(int i=1;i<=n;i++)cout<<a[i]<<' ';
			cout<<endl;
			return ;
		}
	}
	cout<<-1<<endl;
}
signed main(){
	int t=rd;
	while(t--){

		n=rd;
		solve();
		
	}
	
}
```




---

