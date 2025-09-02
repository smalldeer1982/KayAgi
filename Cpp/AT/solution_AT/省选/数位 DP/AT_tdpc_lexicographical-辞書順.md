# 辞書順

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_lexicographical

入力は以下の形式で標準入力から与えられる。

> $ s $ $ K $

 答えを一行に出力せよ。 ```

eel
6
```

```

Eel
```

```

lexicographical
100
```

```

capal
```

## 说明/提示

### Constraints

 文字列 $ s $ の空でない部分列のうち、辞書順で $ K $ 番目のものを求めよ。そのようなものが存在しない場合は "Eel" (quotes for clarity) と出力せよ。   
 ただし、$ s $ から何文字か取り除き (0 文字でもよい)、残りの文字を順番を変えずにつなげたものを部分列という。たとえば、"aba" の部分列は "a", "b", "aa", "ab", "ba", "aba" の 6 個である。"a" は異なる場所に二回現れるが、文字列として同じであれば区別しないものとする。

- - - - - -

- $ 1\ <\ =\ |s|\ <\ =\ 1000000 $
- Each character in s will be a lowercase letter ('a'-'z').
- $ 1\ <\ =\ K\ <\ =\ 10^{18} $

# 题解

## 作者：fa_555 (赞：2)

under 题解 [AT686](https://www.luogu.com.cn/problem/AT686)

同步发布于[个人博客](https://fa555.github.io/2020/某At的dp场/#G-辞書順)

### problem

求字符串 $s \ (1 \le |s| \le 10^6)$ 的字典序第 $K \ (1 \le K \le 10^{18})$ 小的非空**子序列**或判断不存在。相同的子序列只计算一次。字符集小写拉丁字母。

### solution

> と，色々書いたけどわかりにくい解説だな…．
>
> 自分もかなり苦手な問題なので…．
>
> —— Suikaba 的原话

看了 Suikaba 神仙的题解，尝试来自己胡一胡（

设 $\mathrm{nxt}_{i, c}$ 为 $s$ 中第 $i$ 个位置之后第一个出现 $c$ 的位置；$f_i$ 为使用第 $i$ 个位置的字符，其后子序列的个数。那么有

$$
f_i = 1 + \sum_{c \in |T|} f_{\mathrm{nxt}_{i, c}}
$$

其中 $T$ 表示字符集。加上的 $1$ 表示当前字符单独成串。

考虑如何找到字典序第 $K$ 小的集合。设一个向后跳的指针，初始指向字符串起始位置。从小到大枚举 $T$ 中的字符，向后边跳指针边统计答案即可。实现细节见代码。

### code

``` cpp
char s[1000003];
int nxt[1000003][27];
long long K, f[1000003];

int main() {
  scanf("%s%lld", s + 1, &K);
  const int N = strlen(s + 1);
  std::fill(nxt[N + 1] + 1, nxt[N + 1] + 27, N + 1);
  for (int i = N; i >= 0; --i) {
    memcpy(nxt[i] + 1, nxt[i + 1] + 1, sizeof(int) * 26);
    f[i] = 1;
    for (int j = 1; j <= 26; ++j) {
      f[i] += f[nxt[i][j]];
      f[i] = std::min(f[i], K + 1);
    }
    nxt[i][s[i] & 31] = i;
  }

  bool g = 0;
  for (int i, p = 1; K > 0; ) {
    for (i = 1; i <= 26; ++i)
      if (f[nxt[p][i]] < K)
        K -= f[nxt[p][i]];
      else {
        --K;
        p = nxt[p][i] + 1;
        g = 1;
        putchar(i - 1 + 'a');
        break;
      }
    if (i > 26) break;
  }
  puts(g ? "" : "Eel");
  return 0;
}


```

---

## 作者：Shizaki_Crazy_Three (赞：0)

# [题目链接](https://www.luogu.com.cn/problem/AT_tdpc_lexicographical)

一道妙妙题。我们发现直接求第 $k$ 大字符串不好求，正难则反。于是我们看看可不可以求出来从第 $i$ 位开始有多少个子序列来倒推出排名第 $k$ 的子序列。

于是我们设 $f_{i}$ 表示以第 $i$ 位开头共有多少子序列，于是我们考虑如何不算重。我们发现算重的情况只有两位字符相同我们却只选一个，就是假如第 $i$，$j$ 位字符是 $c$，我们先统计了以第 $j$ 位开头的子序列，后在统计以第 $i$ 位开头的子序列时没有选 $j$，导致算重。

知道算重的情况后，我们可以设 $nxt_{i,c}$ 表示第 $i$ 位之后第一个 $c$ 的下标。据此我们可以推出状态转移方程

$$
f_{i}=1+\sum_{c\in{T}}f_{nxt_{i,c}}
$$

求排名序列可以类比权值线段树那样不断通过子序列的个数来缩小区间，详情看代码。

### code

```cpp
#define LOCAL
#include<bits/stdc++.h>
#include<unistd.h>
#include<bits/extc++.h>
// #define getchar my_gechar
#define ll long long
#define lll __int128
#define db double
#define ldb long double
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
#define pii pair<int,int> 
#define vec Point
// #define max(a,b) ((a)<(b)?(b):(a))
// #define min(a,b) ((a)<(b)?(a):(b))
#define vi vector<int> 
#define vl vector<ll>
#define lowbit(x) (x)&(-x)
//#define sort stable_sort
using namespace std;
using namespace __gnu_pbds;
char buffer[32769];
unsigned li = 0;
inline char my_gechar(){
    if(buffer[li] == '\0') buffer[read(0, buffer, 32768)] = '\0',li = 0;
    return buffer[li++];
}
namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;

            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
                  inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline int read(double &x){return scanf("%lf",&x);}
            inline int read(long double &x){return scanf("%Lf",&x);}
            inline void dwrite(const double &x,int y=6,bool flag=1){printf("%.*lf",y,x),flag?putchar(' '):putchar(' ');}
            inline void dwrite(const long double &x,int y=6,bool flag=1){printf("%.*Lf",y,x),flag?putchar(' '):putchar(' ');}
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const char *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch[1000005]={};read(ch),x=ch;}
            inline void write(const string &x){int len=x.length();for(int i=0;i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>
            inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar(' ');}
            inline __int128 read(){static __int128 x;return read(x);}
            template<typename type>
            inline type put(type x,bool flag=1){write(x),flag?putchar(' '):putchar(' ');return x;}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;
struct Point{
	int x,y;
	Point operator +(const Point& b)const{return {x+b.x,y+b.y};}
	Point operator -(const Point& b)const{return {x-b.x,y-b.y};}
	bool operator <(const Point& b)const{
		if(x!=b.x)return x<b.x;
		return y<b.y;
	}
};
const int N=1e5+5;
const int M=1e6+5;
const int inf=1e9+5;
const int mod=1e9+7;
const int bit=50;
//mt19937 sj(chrono::steady_clock::now().time_since_epoch().count());
int B=705;
int nxt[M][26];
ll f[M];
string s;
int n;
ll k;
inline void solve(){
	cin>>s;
	read(k);
	n=s.size();
	for(int i=0;i<26;++i){
		nxt[n+1][i]=n+1;
	}
	for(int i=n;i>=1;--i){
		for(int j=0;j<26;++j) nxt[i][j]=nxt[i+1][j];
		f[i]=1;
		for(int j=0;j<26;++j){
			f[i]+=f[nxt[i][j]];
			f[i]=min(f[i],k+1);
		}
		nxt[i][s[i-1]-'a']=i;
	}
	int p=1;
	bool flag=0;
	int i;
	while(k>0){
		for(i=0;i<26;++i){
			//cout<<p<<endl;
			if(f[nxt[p][i]]<k){
				//cout<<i<<' '<<k<<' '<<f[nxt[p][i]]<<endl;
				k-=f[nxt[p][i]];
			}else{
				//cout<<f[nxt[p][i]]<<k-1<<endl;
				--k;
				p=nxt[p][i]+1;
				putchar(i+'a');
				flag=1;
				break;
			}
		}if(i==26) break;
	}
	if(!flag){
		puts("Eel");
	}else puts("");
}

signed main()
{   
    int _=1;
    while(_--) solve();
    return (0-0);
}
```

---

## 作者：Priestess_SLG (赞：0)

简单的问题。子序列相关题目考虑在子序列自动机上 dp。套路的，设 $to_{i,j}$ 表示 $i$ 后面第一个字符 $j$ 出现的位置，$f_i$ 表示当前到 $i$ 位置，可以得到的不同的子序列的数目。则 $to_{i,j}$ 显然可以 $O(n)$ 处理，$f_i$ 有转移式：$f_i=\sum\limits_{j=0}^{25}f_{to_{i,j}}+1$。

计算答案的时候直接贪心一下即可。总时间复杂度为 $O(n)$。

我的做法可能稍微有点难写（

```cpp
char s[N];
int to[N][26], f[N];
void run() {
    scanf("%s", s + 1);
    int k = read();
    int n = strlen(s + 1);
    fill(to[n + 1], to[n + 1] + 26, n + 1);
    for (int i = n; ~i; --i) {
        for (int j = 0; j < 26; ++j) to[i][j] = to[i + 1][j];
        if (i != n) to[i][s[i + 1] - 'a'] = i + 1;
    }
    f[n] = 1;
    for (int i = n - 1; i; --i) {
        f[i] = 1;
        for (int j = 0; j < 26; ++j)
            if (to[i][j] != n + 1) f[i] = min(f[i] + f[to[i][j]], k + 1);
    }
    int su = 0;
    for (int i = 0; i < 26; ++i)
        if (to[0][i] != n + 1) {
            su += f[to[0][i]];
            if (su > k) break;
        }
    if (su < k) cout << "Eel\n";
    else {
        for (int st = 0; st < 26; ++st) {
            int now = to[0][st], ok = 0;
            if (k > f[now]) {
                k -= f[now];
                continue;
            }
            if (now == n + 1) continue;
            while (now <= n) {
                if (k == 0) return;
                if (k == 1) {
                    if (!ok) cout << s[now];
                    cout << '\n';
                    return;
                }
                --k;
                for (int j = 0; j < 26; ++j)
                    if (f[to[now][j]] < k) k -= f[to[now][j]];
                    else {
                        if (!ok) ok = 1, cout << (char)(st + 'a');
                        cout << (char)(j + 'a');
                        now = to[now][j];
                        break;
                    }
            }
        }
        cout << '\n';
    }
}
```

---

