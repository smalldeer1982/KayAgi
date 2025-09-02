# RGB Substring (easy version)

## 题目描述

The only difference between easy and hard versions is the size of the input.

You are given a string $ s $ consisting of $ n $ characters, each character is 'R', 'G' or 'B'.

You are also given an integer $ k $ . Your task is to change the minimum number of characters in the initial string $ s $ so that after the changes there will be a string of length $ k $ that is a substring of $ s $ , and is also a substring of the infinite string "RGBRGBRGB ...".

A string $ a $ is a substring of string $ b $ if there exists a positive integer $ i $ such that $ a_1 = b_i $ , $ a_2 = b_{i + 1} $ , $ a_3 = b_{i + 2} $ , ..., $ a_{|a|} = b_{i + |a| - 1} $ . For example, strings "GBRG", "B", "BR" are substrings of the infinite string "RGBRGBRGB ..." while "GR", "RGR" and "GGG" are not.

You have to answer $ q $ independent queries.

## 说明/提示

In the first example, you can change the first character to 'R' and obtain the substring "RG", or change the second character to 'R' and obtain "BR", or change the third, fourth or fifth character to 'B' and obtain "GB".

In the second example, the substring is "BRG".

## 样例 #1

### 输入

```
3
5 2
BGGGG
5 3
RBRGR
5 5
BBBRR
```

### 输出

```
1
0
3
```

# 题解

## 作者：EatBread (赞：3)

由于时间才 $2000$，这题爆枚不会超时，所以就想到分为：

RGB 的循环，GBR 的循环，BRG 的循环三种情况，逐个爆枚。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,gs;
string s;
char h[3];
int jjss(int t,int w)
{
	int ans=0;
	for(int i=t; i<w; i++){if(s[i]!=h[(i-t)%3])ans++;}
	return ans;
}
int js()
{
	int t=0,ans=100000,w=b;
	while(w<=a)
	{
		ans=min(jjss(t,w),ans);
		t++,w++;
	}
	return ans;
}
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		scanf("%d%d",&a,&b);cin>>s;gs=10000000;
		h[0]='R',h[1]='G',h[2]='B';gs=min(gs,js());
		h[0]='G',h[1]='B',h[2]='R';gs=min(gs,js());
		h[0]='B',h[1]='R',h[2]='G';gs=min(gs,js());
		cout<<gs<<endl;
	}
	return 0;
} 
```





---

## 作者：crashed (赞：2)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/CF1196D1)看题目。
# 分析  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$xjb$算法。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们先假设这个串的起点匹配的是$R$。起点匹配$B$和$G$的情况类似。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后，我们先将原串中$s[1...K]$这个部分先修改得和匹配的部分一样。然后，我们右移起点，并且这是$s[2...K+1]$匹配的就是原匹配的后一个串了。一直右移直到起点到终点之间的长度$<K$。（语文爆炸了）  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后这样搞是$O(q+\sum_i len_i)$，可以在线完成。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;这个~~优秀的~~时间复杂度也可以~~水~~过[[CF1196D2] RGB Substring (hard version)](https://www.luogu.org/problem/CF1196D2)
# 代码
```cpp
#include <cstdio>

const int MAXN = 2005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int base[3][MAXN];
int a[MAXN];
char str[MAXN];
int N, K;

int trans( const char c )
{
	if( c == 'R' ) return 1;
	if( c == 'G' ) return 2;
	if( c == 'B' ) return 3;
}

void init()
{
	for( int j = 1 ; j <= 3 ; j ++ )
	{
		for( int i = 1 ; i <= 2000 ; i ++ )
		{
			base[j - 1][i] = ( j + i - 2 ) % 3 + 1;
		}
	}
}

int solve( const int sta )
{
	int cnt = 0, i;
	for( i = 1 ; i <= K ; i ++ )
	{
		cnt += ( a[i] != base[sta][i] );
	}
	int res = cnt;
	for( ; i <= N ; i ++ )
	{
		cnt -= ( a[i - K] != base[sta][i - K] );
		cnt += ( a[i] != base[sta][i] );
		res = MIN( res, cnt );
	}
	return res;
}

int main()
{
	int Q, res;
	read( Q );
	init();
	while( Q -- )
	{
		read( N ), read( K );
		scanf( "%s", str + 1 );
		for( int i = 1 ; i <= N ; i ++ )
		{
			a[i] = trans( str[i] );
		}
		res = 0x3f3f3f3f;
		for( int i = 0 ; i < 3 ; i ++ )
		{
			res = MIN( res, solve( i ) );
		}
		write( res ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这题思路很直接，就两个字，
### 暴枚！
每次枚举头和尾，再循环三次枚举三种排列，最后取最小值，就可以了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long q,n,k,t,w,x,mi;
string s;
int main()
{
	cin>>q;
	for(int i=1; i<=q; i++)
	{
		cin>>n>>k>>s;
		t=0,w=k,x=0,mi=2147483647;
		while(w<=n)
		{
			for(int j=t; j<w; j++)
			{
				if(j%3==0&&s[j]!='R')x++;
				if(j%3==1&&s[j]!='G')x++;
				if(j%3==2&&s[j]!='B')x++;
			}
			mi=min(mi,x),x=0;
			for(int j=t; j<w; j++)
			{
				if(j%3==0&&s[j]!='G')x++;
				if(j%3==1&&s[j]!='B')x++;
				if(j%3==2&&s[j]!='R')x++;
			}
			mi=min(mi,x),x=0;
			for(int j=t; j<w; j++)
			{
				if(j%3==0&&s[j]!='B')x++;
				if(j%3==1&&s[j]!='R')x++;
				if(j%3==2&&s[j]!='G')x++;
			}
			mi=min(mi,x),x=0;
			t++,w++;
		}
		cout<<mi<<endl;
	}
	return 0;
}
```

---

## 作者：Amm_awa (赞：0)

$$\huge{\texttt{CF1196D1 题解}} \tag*{\texttt{作者：wjl\_100930}}$$

## 链接

[$\color{red}\fbox{\text{洛谷链接}}$](https://www.luogu.com.cn/problem/CF1196D1)

[$\color{red}\fbox{\text{ CF 链接}}$](https://codeforces.com/contest/1196/problem/D1)

## 分析
数据范围小于 $2000$，所以采用爆枚。

1. 母串为 $\texttt{RGBRGBRGB}\dots$，可以得到 $3$ 个长度为 $3$ 的不同子串，分别为 $\texttt{RGB}$，$\texttt{GBR}$，$\texttt{BRG}$。
2. 在这三个子串的基础上分别进行枚举，再取出这三种情况中修改次数最少的。
3. 枚举时会有不同方案出现，要取最优值。

剩下放代码注释里了。

## code
```cpp
#include<bits/stdc++.h>
#define Inf 0x3fffffff
//无穷大
using namespace std;
int n,t,k;
string s;
void readNum();
void solve();
inline int read()
//快读，输入优化
{
    register int x=0,f=1;
    register char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    //位运算优化
    return x*f;
}
void readNum()
//输入数据
{
	t=read();
	while(t--)
    //多组数据
	{
	    n=read(),k=read();
        cin>>s;
	    solve();
	}
}
int Enum(string te)
//枚举，核心部分
{
    register int l=0,r=k,ans=Inf,temp=0,i;
    while(r<=n)
    //判断是否越界
    {
        temp=0;
        //当前区间的答案
        for(i=l;i<r;i++)
        //左（l）右（r）端点
            temp+=((s[i]!=te[(i-l)%3])?1:0);
            //增加修改次数
            //三目运算，当 s[i] 与当前应该出现的值不同时要增加
        ans=min(ans,temp);
        //不同方案（起始和结束端点不同）的最优值
        l++,r++;
        //下一个区间
    }
    return ans;
}
void solve()
//计算与输出部分
{
    register int ans=Inf;
    ans=min({Enum("RGB"),Enum("GBR"),Enum("BRG")});
    //三种情况，取最小值
    cout<<ans<<'\n';
    //多组数据，输出换行
}
int main()
{
	readNum();
	return 0;
    //完美结束
}

```

---

## 作者：heyx0201 (赞：0)

# RGB Substring (easy version) 题解
## Meaning
> 给定 $q$ 组询问，每组询问输入一个 $n, k$ 和一个字符串 $s$，问最少修改多少次 $s$ 中的字母（一次只能修改一个字母），才能使得 $s$ 的某一个子串是字符串 `RGBRGBRGB...` 的子串，同时该子串的长度 $\ge k$。
## Solution
首先观察得出：字符串 $s$ 的长度为 $k$ 子串为 `RGBRGBRGB......` 的子串，这个子串只有三种可能：`RGBRGBRGB......`，`GBRGBRGBR......`，`BGBRGBRG......`。

所以自然可以想出一种 $O(n^2)$ 的解法：先枚举 $3$ 种情况，然后再枚举左端点和右端点，然后再循环判断有多少个字符不符合条件。

## Accept Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const string kPos = "RGB";

int q, n, k;
string s;

void Solve() {
  cin >> n >> k >> s;
  int ans = INT_MAX;
  for (int i = 0; i < 3; i++) {
    for (int l = 0; l + k - 1 < n; l++) {
      int sum = 0;
      for (int r = l; r < l + k; r++) {
        sum += s[r] != kPos[(i + r) % 3];
      }
      ans = min(ans, sum);
    }
  }
  cout << ans << '\n';
}

int main() {
  cin >> q;
  while (q--) {
    Solve();
  }
  return 0;
}
```

---

## 作者：JOKER_chu (赞：0)

# CF1196D1 题解

想过这题思路很重要，打个比喻：没明白思路你这题就只能写空气，有思路了你就是~~玩原神~~都能轻松写出来。

由于数据范围很小，足以跑过一个很暴力的玩意：

代码思路就是每次都去枚举位置，对位置 `substr` 之后再写一个函数去枚举字符串里字串里的字符的顺序，按 RGB 顺序枚举 3 遍就行了，函数里每遍都要统计答案，结束每一遍都要统计最小返回值，每次答案与返回值取最小的，位置枚举结束后就是答案，还有，记得换行，不是空格（~~蒟蒻作者被卡了~~）。

贴代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, x, y;
string a;

int f(string a){ // 函数统计 substr 中的字符顺序，遇到不合法的计数
  int r = INT_MAX, cnt = 0;
  char no = 'R';
  for(int i = 0; i < a.size(); i++){
    if(a[i] != no){ // 遇到不合法的
      cnt++; // 计数

    }
    if(no == 'R'){ // 按 RGB 更新当前合法的字符
      no = 'G';
    }else if(no == 'G'){
      no = 'B';
    }else{
      no = 'R';
    }
  }
  r = min(r, cnt); // 每次取最小返回值
  cnt = 0; // 计数归 0
  no = 'G';
  for(int i = 0; i < a.size(); i++){
    if(a[i] != no){
      cnt++;

    }
    if(no == 'R'){
      no = 'G';
    }else if(no == 'G'){
      no = 'B';
    }else{
      no = 'R';
    }
  }
  r = min(r, cnt);
  no = 'B';
  cnt = 0;
  for(int i = 0; i < a.size(); i++){
    if(a[i] != no){
      cnt++;

    }
    if(no == 'R'){
      no = 'G';
    }else if(no == 'G'){
      no = 'B';
    }else{
      no = 'R';
    }
  }
  r = min(r, cnt);
  return r;
}

int main(){
  cin >> n;
  for(int _ = 1; _ <= n; _++){
    cin >> x >> y >> a;
    int ans = INT_MAX; // 答案初始化一个极大值
    for(int i = 0; i < x - y + 1; i++){
      ans = min(ans, f(a.substr(i, y))); // 对字符串 substr ，每次返回值都传一个极大值 
    }
    cout << ans << endl; // 输出答案
  }
  return 0; // 好习惯
}
```
完

---

## 作者：FwbAway (赞：0)

我们把 RGB 的几种情况都列出来就可以了，其实这道题算红题的。

设一个指针指向原串的开头，再设一个指向结尾，然后判断是否这个和原来的字串相同，相同不动，不想同往前进一位。

可以使用 solve 函数去判断他是不是正确的一组串，也可以用动态数组，用一个空间开辟一个空间就可以做对这道题了。

过于简单，代码略。

---

## 作者：fjy666 (赞：0)

## 0x01 思路
首先从 RBG 串的性质入手。  
发现当长度为 $n$ 时，有且只有三种 RGB 串：
- `RGBRGBRGB......`
- `GBRGBRGBR......`
- `BRGBRGBRG......`

我们只要枚举这三种串，再和原串对比，求操作次数就 OK 了！  

## 0x02 代码
```cpp
#include <algorithm>
#include <cstdio>
#define _for(i_,a_,b_) for(int i_ = a_;i_ < b_;++i_)
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int n,k,ans = 0x7fffffff;
char s[200050];
const char str[] = "RGB";
inline void getNxt(int& qwq){qwq = (qwq+1) % 3;}
void solve(int fjy){
	int cnt = 0;
	_rep(i,1,k){
		if(s[i] != str[fjy])++cnt;
		getNxt(fjy);
	}
	char *st = s+1,*ed = s+k;
	while(*ed != '\0'){
		ans = std::min(ans,cnt);
		if((*st) != str[((fjy-k)%3+3)%3])--cnt;
		++st;++ed;
		if(*ed != str[fjy])++cnt;
		getNxt(fjy);
	}
}

void solve(void){
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	ans = 0x7fffffff;
	solve(0);
	solve(1);
	solve(2);
	printf("%d\n",ans);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
    return 0;
}
```

---

