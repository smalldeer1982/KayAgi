# Magazine Ad

## 题目描述

The main city magazine offers its readers an opportunity to publish their ads. The format of the ad should be like this:

There are space-separated non-empty words of lowercase and uppercase Latin letters.

There are hyphen characters '-' in some words, their positions set word wrapping points. Word can include more than one hyphen.

It is guaranteed that there are no adjacent spaces and no adjacent hyphens. No hyphen is adjacent to space. There are no spaces and no hyphens before the first word and after the last word.

When the word is wrapped, the part of the word before hyphen and the hyphen itself stay on current line and the next part of the word is put on the next line. You can also put line break between two words, in that case the space stays on current line. Check notes for better understanding.

The ad can occupy no more that $ k $ lines and should have minimal width. The width of the ad is the maximal length of string (letters, spaces and hyphens are counted) in it.

You should write a program that will find minimal width of the ad.

## 说明/提示

Here all spaces are replaced with dots.

In the first example one of possible results after all word wraps looks like this:

`<br></br>garage.<br></br>for.<br></br>sa-<br></br>le<br></br>`The second example:

`<br></br>Edu-ca-<br></br>tion-al.<br></br>Ro-unds.<br></br>are.so.fun<br></br>`

## 样例 #1

### 输入

```
4
garage for sa-le
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4
Edu-ca-tion-al Ro-unds are so fun
```

### 输出

```
10
```

# 题解

## 作者：Echoternity (赞：3)

随机跳了一道题，就放在题库里，原以为是一道 `dp`，结果是到二分。

首先，我们必须要做的就是将难以处理的字符串转化为我们比较熟悉的数字，因为在所有的 `-` 和 `' '`之间都可以断，所以我们将其中的字符串转化为一个数记为该段的长度。最后我们会得到一个长度为 $n$ 的数组 `val[i]` ，而我们要将这 $n$ 个数分成 $k$ 段。

到这里，这道题就显然了。

**将 $n$ 个数分成 $k$ 个区间，使最大区间和最小**

我们直接**二分**区间长度，然后暴力该区间和满足需要多少段。

`check(int len)` 函数：

``` c++
inline bool check(int x)
{
    int res=0,cnt=0;
    for(int i=1;i<=tot;++i)
    {
        if(val[i]>x) return 0;
        if(res+val[i]<=x) res+=val[i];
        else ++cnt,res=val[i];
    }
    // printf("%d %d\n",x,cnt);	//调试用
    if(cnt>=k) return 0;
    return 1;
}
```

记得特判 $val[i]>x$ 的情况（即单个区间的长度已经大于了需要判定的长度）

然后这道题就十分简单了。

有几个注意的点：

* 对于每一个区间，其末尾的 - 和空格也算该区间的一部分

* 对于整行字符串的输入，因为 `gets()` 函数的废除，建议用 `while(getchar())` 直接输入，不要使用 `stl` 库。

$AC\ Code$ ：

``` c++
省略预处理部分
int k,len,p;
char str[MAXS];
int val[MAXS],tot;
inline bool check(int x)
{
    int res=0,cnt=0;
    for(int i=1;i<=tot;++i)
    {
        if(val[i]>x) return 0;
        if(res+val[i]<=x) res+=val[i];
        else ++cnt,res=val[i];
    }
    // printf("%d %d\n",x,cnt);
    if(cnt>=k) return 0;
    return 1;
}
int main()
{
    // freopen("dp.in","r",stdin);
    // freopen("dp.out","w",stdout);
    read(k);
    while((str[++len]=gh())!='\n');
    p=1;
    for(int i=1;i<=len;++i)
        if(str[i]=='-'||str[i]==' ')
            val[++tot]=i-p+1,p=i+1;
    if(p!=len+1) val[++tot]=len-p;
    int l=0,r=len;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    printf("%d",l);
    return 0;
}
/*
4
garage for sa-le
7 4 3 2
4
Edu-ca-tion-al Ro-unds are so fun
4 3 5 3 3 5 4 3 3
*/
```

---

## 作者：wuyixiang (赞：2)

题目大意：给一段文字划分为 $k$ 段，规定只能在 `-` 或空格后面分段，问最长的那段长度最短是多少。

思路分析：一看到“分段”“最短”，想到二分。我们可以先二分枚举最短长度，接着判断。判断非常简单，就是尽可能的将一段变得更长，如果超过即跳转到最后一个可以分段的位置并进行分段。分段具体代码如下：

```cpp
bool check(int m)
{
    int w = 0,x = 0,z = 1;//z为分段个数，w为最后一次可断开位置，x表示目前该段的长度
    for(int i = 0;i < s.size();i ++)
    {
        if(s[i] == '-' || s[i] == ' ')w = i;//存储位置
        x ++;
        if(x >= m && i != s.size() - 1)//表示从这里或之前必须断开。这里注意，当到末尾时无需分段。
        {
            if(w == 0)return false;//若没有位置可以分开，直接返回flase
            x = i - w,w = 0,z ++;
        }
    }
    return z <= k;//判断段数是否满足条件
}
```

然后大体就完事了。这里有几个坑，需要注意：

一、当输入第一个数时，换行符是没有被输入的，需要再读取一个换行符；

二、长度最小是 $1$。

最后是完整代码。

```cpp
#include <iostream>
using namespace std;
string s;
int k,l = 1,r = 1e9;
bool check(int m)
{
    int w = 0,x = 0,z = 1;
    for(int i = 0;i < s.size();i ++)
    {
        if(s[i] == '-' || s[i] == ' ')w = i;
        x ++;
        if(x >= m && i != s.size() - 1)
        {
            if(w == 0)return false;
            x = i - w,w = 0,z ++;
        }
    }
    return z <= k;
}
int main()
{
    cin >> k;
    getchar();
    getline(cin,s);
    while(l < r)
    {
        int mid = (l + r) / 2;
        if(check(mid))r = mid;
        else l = mid + 1;
    }
    cout << l;
}

---

## 作者：神之右大臣 (赞：2)

 CF 803D Magazine Ad 题解

题面

正解：一道二分大水题！

A：你现在满分了吗？
B : 是啊！
A : 那你noip时就要爆零啦！
Q : 蛤？

 

正常情况下我们日常练习均使用的是windows系统(比如说这道题的评测机)，在windows下，string 本身是可以存储'\0'字符，'\0'字符只是char 数组的结束符。如果是一个字符一个字符赋值，string 是可以直接输出空字符的。

而在linux的情况下(比如OI或一些oj)，string 和char[]是一个德行，根本就存不了’\0',此字符也作为string 的结束符。

 

所以说：在Linux(noip)下，读取换行一定要用两遍getchar(),否则,就会爆零啦！

附上我的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int k;
char s[1000001];
int jd[1000001],cnt=0;
bool check(int x)
{
    int len=0,gs=1;
    for(int i=1;i<=cnt;i++)
    {
        if(jd[i]-jd[i-1]>x) return 0;
        if(len+(jd[i]-jd[i-1])<=x) len+=(jd[i]-jd[i-1]);
        else
        {
            gs++;
            len=jd[i]-jd[i-1];
        }
    }
    return gs<=k;
}
int main()
{
    cin>>k;
    getchar();
    //getchar(); 
    int i=0;
    while(1)
    {
        char ch=getchar();
        if(ch=='\n') break;
        s[i++]=ch;
    }
    int len=i;
    for(int i=0;i<len;i++) if(s[i]==' '||s[i]=='-') jd[++cnt]=i+1;
    jd[++cnt]=len;
    int l=0,r=len;
    while(l!=r)
    {
        int midd=(l+r)>>1;
        if(check(midd)) r=midd;
        else l=midd+1;
    }
    printf("%d",l);
}
```


---

## 作者：DennyQi (赞：2)

题目可以转化为：给出$n$个数，分为$k$块，使块的最大值最小

二分宽度。将问题转化为判定每一行的长度不超过$mid$时需要几行。利用一个类似队列的方法就可以了。

```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100010;
inline int read(){
	int x(0),w(1); char c = getchar();
	while(c^'-' && (c<'0' || c>'9')) c = getchar();
	if(c=='-') w = -1, c = getchar();
	while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
	return x*w;
}
int k,len,las,n,l,r,ans,mid;
char s[1000010];
vector <int> a,sum;
inline int get_sum(int l, int r){
	return !l ? sum[r] : sum[r]-sum[l-1];
}
inline bool judge(int x){
	int res = 0, pre = 0;
	for(int i = 0; i < n; ++i) if(a[i] > x) return 0;
	for(int i = 0; i < n; ++i) if(get_sum(pre,i) > x) pre = i, ++res;
	return res+1 <= k;
}
inline void cul_sum(){
	if(a.size() == 1) sum.push_back(a[0]);
	else sum.push_back(sum[a.size()-2]+a[a.size()-1]);
}
int main(){
	// freopen(".in","r",stdin);
	scanf("%d",&k); getchar();
	gets(s);
	len = strlen(s);
	for(int i = 0; i < len; ++i)
		if(s[i] == '-' || s[i] == ' '){
			a.push_back(i-las+1), cul_sum();
			las = i+1;
		}
	a.push_back(len-las), cul_sum();
	n = a.size();
	l = 1, r = len;
	while(l <= r){
		mid = (l+r)>>1;
		if(judge(mid)) r = mid-1, ans = mid; else l = mid+1;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Fkxxx (赞：1)

## 简述

给出一个 $k$ 与一个字符串，将字符串按连字符与空格分成各个小段，把段分成 $k$ 组，每组的最大总长度最小是多少？

## 解题

对于字符串的分段还是挺好做的，注意在输入时，先输入第一个整数后再读入第二行的字符串时，读入文件里还有一个换行符被落下了，此时直接 `getline`，函数依然会读入上一行，因为换行符还在。所以应该先读掉换行符，这里最简单的方法是 `getline` 两次或者加上一个 `getchar();`。

读入后，分段就很简单了，记得处理最后一个段。这里要注意，字符串前面和中间的段长包含了连字符或空格，但最后一个却不包含。

接下来就是数据处理，我们伟大的 @[zhangyaiwei](https://luogu.com/user/684245) ~~耐摔王~~巨佬曾告诉我，最小的最大的问题可以考虑二分。

所以就得二分。

用二分答案找最小的字符串最大长度，`check` 函数只需要模拟分组各个段，每当当前组装满了就下一组，最后看分了多少组，不符合要求就 out。

```cpp
bool check( int x ){
	int p = 0 , h = 1 ;
	for( int i = 1 ; i <= cnt ; i ++ ){
		if( p + t[i] <= x ) p += t[i] ;
		else h ++ , p = t[i] ;
	}
	if( h > n ) return false ;
	return true ;
}
```

显而易见的，这个check 函数有问题，如果有一个串长比 x 还大，应该直接返回 `false`。所以要记得特判。

到这里，这题就做完了，[这里](https://codeforces.com/contest/803/submission/259850965)给出我的 CF 提交记录，可自行查看。

---

## 作者：WS_ZZM (赞：1)

Err......题目表意已经很清楚了，就不再翻译了。~~我才不会说自己是因为懒而不翻译的......~~


------------

根据题意，可以较容易地得出结论：**每行的限制宽度越长，所用的行数越多，反之亦然**。显然，此题具有**单调性**，便可以考虑**二分**；由于是**答案**具有单调性，所以可以**二分答案**。

毋庸置疑，应二分**限宽**（即每行限制宽度）。注意，换行时的空格和连字符也应**占一个单位的宽度**，我们不妨对于每个字符串，在读入时将该字符串后紧接着的**空格**当作这个字符串的一个**字符**，也就是将字符串的长度在原来的基础上**加一**，连字符本质上和空格一样，也**同上**处理。

这样二分应该会好写一些，最后写 **check** 函数时注意细节就行。

# AC CODE

```cpp
#include <vector>
#include <cstdio>

using namespace std;

template<typename T> void get_min(T &x, const T &y) {if (y < x) x = y; return; }
template<typename T> void get_max(T &x, const T &y) {if (y > x) x = y; return; }
template<typename T> void quick_mod(T &x, const T &M) {if (x >= M) x -= M; return; }
template<typename T> T gcd(T a, T b) { for (T y; b; ) y = a, a = b, b = y % b; return a; }
template<typename T> T lcm(const T &x, const T &y) {return x / gcd(x, y) * y; }
template<typename T> T f_nd(const T &x) {for (T i = 2; i * i <= x; ++i) if (x % i == 0) return x / i; return 1; }
template<typename T> T quick_pow(T a, T b) {T res = 1; for (; b; b >>= 1, a *= a) if (b & 1) res *= a; return res; }
template<typename T> bool is_prime(const T &x) {for (T i = 2; i * i <= x; ++i) if (x % i == 0) return false; return true; }
template<typename T> T mod_pow(T a, T b, const T &M) {T res = 1; for (; b; b >>= 1, a = a * a % M) if (b & 1) res = res * a % M; return res; }
template<typename T> void DPF(T x, vector<T> &vt) {for (T i = 2; i * i <= x; ++i) for (; x % i == 0; x /= i) vt.emplace_back(i); if (x != 1) vt.emplace_back(x); return; }
template<typename T> T exgcd(const T &a, const T &b, T &x, T &y) {if (b == 0) return x = 1, y = 0, a; T d = exgcd(b, a % b, x, y), tmp; tmp = y, y = x - a / b * y, x = tmp; return d; }

template<typename type>
void read(type &x) {
    int f = 1; char c = getchar();
    for (; c != '-' && (c < 48 || c > 57); )
        c = getchar();
    c == '-' ? (f = -1, x = 0) : x = c - 48;
    for (c = getchar(); c > 47 && c < 58; )
        x = x * 10 + c - 48, c = getchar();
    x *= f; return;
}

int not_wa = 0;
char ac[200005];
template<typename type>
void write(type x, const char &y) {
    if (x == 0) {putchar('0'), putchar(y); return; }
    if (x < 0) {putchar('-'); x = -x; }
    for (; x; ac[++not_wa] = x % 10, x /= 10);
    for (; not_wa; putchar(ac[not_wa--] + 48));
    putchar(y);
    return;
}

#define N 1000005
#define mod 998244353
#define inf 2000000007
#define eps 0.000000001
#define PI 3.141592653589793

typedef const int CI;
typedef long long LL;
// typedef __int128 large;
typedef const long long CLL;
typedef unsigned long long ULL;

int k, n = 1, cnt[N];

bool check(CI &x) {
    for (int i = 1, now = 0, f = k; i <= n; ++i) {
        if (now + cnt[i] > x) {
            now = cnt[i];
            if (--f == 0)
                return false;
        }
        else now += cnt[i];
    }
    return true;
}

int main() {
    read(k);
    int l = 0, r = 0;
    for (char c; (c = getchar()) != '\n'; ++r)
        if (++cnt[n], c == ' ' || c == '-')
            l = max(l, cnt[n++]);
    l = max(l, cnt[n]), --l;
    for (int mid; l + 1 < r; ) {
        mid = l + r >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    write(r, '\n');
    return 0;
}
```

---

## 作者：Light_az (赞：1)

偶然遇到的题目，分析题目，看到收悉的文章分段，想起了一场 AT 的 $D$ 题。

本题特殊的是文章中有两种特殊的符号 `-` 和空格，只有在这两种符号后面才可以换行，举个例子：`funny-book` 可以换成 `funny-` 和 `book` 两行单词，值得注意的是，`-` 和空格是属于上一行的。

然后我们考虑二分一个最长长度 $k$，同时定义下标 $now$ 和 $last$，分别为我们匹配到文章第 $now$ 个位置，上一个 `-` 或者空格的位置是 $last$，当我们某一行匹配完 $k$ 个字符后，我们贪心的来想，为了满足要求，我们肯定会选择最后一个出现的 `-` 或者空格，然后换行即可，然后如果在 $n$ 行之前匹配好文章后，说明 $k$ 是合法的，套上二分判断即可：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define ps push_back
#define sz(x) ((ll)x.size())
#define mem(f,x) memset(f,x,sizeof(f))
#define all(x) x.begin(),x.end()
#define lc id*2
#define rc id*2+1
#define V vector<ll>
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
char ch;
string s;
bool check(ll k){
	ll now=0,last=-1;
	F(id,1,n){//n 行
		F(i,1,k){
			if(s[now]=='-'||s[now]==' ') last=now;//重置最晚的下标
			now++;//匹配下一个
			if(now==len) return 1;//匹配完了，k 是合法的
		}
		now=last+1;//由于在 last 换行，一次下一个字符是 last+1
	}
	return now==len;//如果相等说明匹配成功
}
int main(){
	cin>>n;
	getchar();//读入换行符
	getline(cin,s);//输入空格
	len=s.size();
	ll l=1,r=1e6+5;//二分
	while(l<=r){
		ll mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Special_Tony (赞：0)

# 注意事项
请注意要在输入 $n$ 后空转一次 getline 吃掉换行再输入字符串！
# 思路
“最大的最小”，一眼二分题。

先把原字符串按减号和空格拆了，然后只要二分答案，贪心取走每个子段，若当前总和超限了那就新开一段，最后只要看段数有没有到 $n$ 就行辣。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, m, a[1000005], tot = 0, l = 1, r, mid, best;
string s;
bool check () {
	int tot = 0, sum = 0;
	for (int i = 0; i <= m; ++ i)
		if ((sum += a[i]) > mid)
			if (++ tot > n)
				return 0;
			else
				-- i, sum = 0;
	return tot < n;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	getline (cin, s);
	getline (cin, s);
	for (char& i : s)
		if (i == '-' || i == ' ')
			a[m] = tot + 1, ++ m, tot = 0;
		else
			++ tot;
	a[m] = tot;
	r = s.size ();
	while (l <= r) {
		mid = l + r >> 1;
		if (check ())
			r = mid - 1, best = mid;
		else
			l = mid + 1;
	}
	cout << best;
	return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 题意

给定 $n$ 个长度为 $l_i$ 的串，串与串之间用空格或者 `-` 隔开（其中空格或者 `-` 字符属于前面的串），求将其分成 $k$ 段后最长的一段的长度最小值。

## 思路

应该可以发现这是一道二分的题目。我们可以二分每一段的最长长度，然后暴力判定即可。

或者我们换一种说法：

在输入时，我们要把每一段的长度都预处理出来，按顺序存入数组 $a$ 中。然后在判定时，我们用一个单指针来判定。注意每个串后面的空格或者 `-` 也要算在长度中，但是最后一个串没有额外的长度。

因此对于样例

```Plain Text
4
garage for sa-le
```



我们的 $a$ 数组应该是：$7 ,4, 3 ,2$。

然后我们把数组 $a$ 分成 $k$ 个区间，求区间和中最大值的最小值是多少。

## 代码

```C++
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define ll long long
#define db double
#define rtn return
using namespace std;

const int N=1e7;
const int M=1e5;
const int Mod=1e5;
const int INF=1e9;

int a[N],cnt,k,len,n,m,ans=INF;//注意数组开大些,1e5不够 

bool check(int x){
	int len=0,id=1,mx=0;
	for(int i=1;i<=cnt;i++){
		if(a[i]>x)return 0;
		if(len+a[i]>x)id++,mx=max(mx,len),len=a[i];
		else len+=a[i];
	}
	mx=max(mx,len);
//	cerr<<"mx="<<mx<<" len="<<x<<"id="<<id<<endl;
	
	if(id<=k)return 1;
	return 0;
}

signed main(){
	cin>>k;
	getchar();
	char c;
	while(c=getchar()){
		if(c=='\n')break;
		m++;
		if(c==' '||c=='-'){
			
			a[++cnt]=len+1,len=0;	
			n=max(n,len+1);
			continue;
		}
		len++;n=max(n,len);
	}
	if(len)a[++cnt]=len;
	
//	for(int i=1;i<=cnt;i++){
//		cout<<a[i]<<' ';
//	}

//	cerr<<"n,m="<<n<<","<<m<<endl;
	int l=n,r=m;
	while(l<r){
		int mid=l+r>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	cout<<l<<endl;
	return 0;
}

```




---

