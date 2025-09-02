# Prime Permutation

## 题目描述

You are given a string $ s $ , consisting of small Latin letters. Let's denote the length of the string as $ |s| $ . The characters in the string are numbered starting from $ 1 $ .

Your task is to find out if it is possible to rearrange characters in string $ s $ so that for any prime number $ p<=|s| $ and for any integer $ i $ ranging from $ 1 $ to $ |s|/p $ (inclusive) the following condition was fulfilled $ s_{p}=s_{p×i} $ . If the answer is positive, find one way to rearrange the characters.

## 说明/提示

In the first sample any of the six possible strings will do: "abc", "acb", "bac", "bca", "cab" or "cba".

In the second sample no letter permutation will satisfy the condition at $ p=2 $ ( $ s_{2}=s_{4} $ ).

In the third test any string where character "y" doesn't occupy positions 2, 3, 4, 6 will be valid.

## 样例 #1

### 输入

```
abc
```

### 输出

```
YES
abc
```

## 样例 #2

### 输入

```
abcd
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
xxxyxxx
```

### 输出

```
YES
xxxxxxy
```

# 题解

## 作者：Oscar12345 (赞：5)

题目大意:

给出一个字符串，问能否通过打乱它的顺序得到一个新的字符串，这个字符串满足所有的质数位和位数是这个质数的倍数的位数上的字母相同，输出能否，如果能，构造一组解.

题目分析：

首先我们知道输入的字符串的字母的顺序无所谓，我们只需要记录每个字母出现的次数。
然后我们发现不管n是多少，集合的形式一定是一个大集合，和一些规模为1的小集合，且这些集合的元素是质数，且大集合不存在这个质数的倍数。这个很显然。
利用上面的结论，我们只需要找到大集合的规模，然后看是否存在一个字母的数量不小于这个大集合的规模，如果存在，那么显然有解。否则无解。
构造最终的解，只需要用找出的字母构造大集合中每个位置的字母，其他的随意即可。 

AC代码如下：
```
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#define MAX 1007

using namespace std;
char s[MAX];
int maxPrime[MAX];
int mark[MAX];
int num[30];

void init ()
{
    memset ( maxPrime , -1 , sizeof ( maxPrime ) );
    for ( int i = 2 ; i < MAX ; i++ )
    {
        if (~maxPrime[i]) continue;
        for ( int j = i*2 ; j < MAX ; j += i )
            maxPrime[j] = i;
    }
}

int main ( )
{
    init ();
    while (~scanf ( "%s" , s ) )
    {
        int n = strlen ( s );
        memset ( mark , 0 , sizeof ( mark ) );
        if ( n < 4 )
        {
            puts ( "YES" );
            puts ( s );
            continue;
        }
        int cnt = 2;
        for ( int i = n ; i >= 2; i-- )
        {
            if ( mark[i] && maxPrime[i] == -1 ) continue;
            if ( ~maxPrime[i] )
            {
                mark[i] = true;
                for ( int j = 2 ; j*j <= i ; j++ )
                {
                    if ( i%j ) continue;
                    mark[j] = mark[i/j] = true;
                }
            }
            else cnt++;
        }
        memset ( num , 0 , sizeof ( num ));
        for ( int i = 0 ; i < n ; i++ )
            num[s[i]-97]++;
        int id = -1;
        for ( int i = 0 ; i < 26 ; i++ )
            if ( n-cnt+1 <= num[i] )
            {
                id = i;
                num[i] -= (n-cnt+1);
                break;
            }
        if ( id == -1 )
        {
            puts ( "NO" );
            continue;
        }
        for ( int i = 0 ; i < n ; i++ )
        {
            if ( mark[i+1] ) s[i] =(char)(id+97);
            else
            for ( int j = 0 ; j < 26 ; j++ )
                if ( num[j] )
                {
                    num[j]--;
                    s[i] = (char)(j+97);
                    break;
                }
        }
        puts ( "YES");
        puts ( s );
    }
}
```

坐等拍砖...

---

## 作者：qwertim (赞：4)

因为对于任意质数 $p$ 和任意 $i=2,3,...,\frac{|s|}{p}$，有 $s_p=s_{p \times i}$，又因为 $i \ge 2$，则 $s_p$ 一定与 $s_{2p}$ 相等，而 $2$ 是个质数，所以 $s_p$ 一定与 $s_2$ 相等。这说明 $s_2$ 一定与任意 $s_{p \times i}$ 相等（$i=1,2,3,...,\frac{|s|}{p}$）。

这上面一大段告诉我们，以在 $|s|$ 以内的任意合数以及在 $\frac{|s|}{2}$ 以内的任意质数为下标的字符均相等，而以其他数做下标的字符没有要求。

做到这里这个题就简单了。

我们计算出所有合数和所有小于 $\frac{|s|}{2}$ 的质数后统计共有多少个，然后判断出现次数最多的字符有没有超过这个数。

- 如果没有，那么肯定不行。
- 如果有，那么就把上面提到的所有符合要求的下标的字符全部填上出现次数最多的字符，然后剩下的随便填即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
int a,maxn,pos=1;
char c,ans[1005];
string s;
bool b[1005];
map<char,int>mp;
bool isprime(int x){//判断是不是质数
	int tmp=sqrt(x);
	fo(i,2,tmp)
		if(x%i==0)return 0;
	return 1;
}
int main(){
	cin>>s;
	fo(i,0,s.size()-1)mp[s[i]]++;
	for(auto it:mp)
		if(maxn<it.second)maxn=it.second,c=it.first;//求出出现次数最多的字符以及出现次数
	fo(i,2,s.size()){
		if(!isprime(i))b[i]=1,a++;//是合数
		else if(i<=s.size()/2)b[i]=1,a++;//是|s|/2及以下的质数
	}
	if(maxn<a)return cout<<"NO",0;//填不满则直接输出NO
	puts("YES"),mp[c]-=a;
	fo(i,1,s.size())
		if(b[i])ans[i]=c;//符合要求的都填上
	for(auto it:mp)
		fo(i,1,it.second){
			while(ans[pos]==c)pos++;//依次找出没有填过的
			ans[pos++]=it.first;
		}
	fo(i,1,s.size())cout<<ans[i];
	return 0;
}
```

---

## 作者：Lily_White (赞：3)

需要点思路，但并不算难的题目。

注意到，如果我们在$2$号位置填入字符$c$，那么$4,6,8,\dots,2n$号位置也必须填入字符$c$。如果在$6$号位置填入$c$，那么$3$号位置也要填入$c$，进而$6,9,12,15,\dots, 3n$也要填入$c$，进而在$5,10,15,\dots, 5n$也要填入$c$。换句话说，对于任意$1\le i \le |S|$，如果存在质数$p$和$k \ge 2$使得$kp=i$，那么它们就必须填入相同的字符。这样整个字符串就被分成了一个大集合和若干小集合，大集合中必须填入相同字符，这样就解决了本题。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
long long qread() {
	char c;
	int neg = 1;
	long long val = 0;
	while (c != '-' && !isdigit(c)) c = getchar();
	if (c == '-') c = getchar(), neg = -1;
	while (isdigit(c)) val = (val << 3) + (val << 1) + c - '0', c = getchar();
	return neg * val;
}
char s[1200], ans[1200];
int mark[1200];
int cnt, sz[1200], chr[1200];
vector <int> pos;
int main() {
	scanf("%s", s + 1); int n = strlen(s + 1);
	for (int i = 2; i <= n; i++){
		if (i == 1) continue;
		if (!mark[i]) {
			mark[i] = true;
			if (n / i <= 1) continue;			
 			pos.pb(i);
			for (int j = i; j <= n; j += i) {
				if (!mark[j]) {
					mark[j] = true;
					pos.pb(j);
				}
			}
		}
	}
	sort(s + 1, s + n + 1);
	repn(i, n) {
		if (s[i] != s[i - 1]) cnt++;
		chr[cnt] = s[i];
		sz[cnt]++;
	}
	int maxv, maxi = 0;
	maxv = -INF;
	repn(i, cnt) {
		if (sz[i] > maxv) {
			maxv = sz[i];
			maxi = i;
		}
	}
	if (maxv < (int)pos.size()) {
		cout << "NO" << endl;
		return 0;
	}
	else {
		puts("YES");
		for (auto i:pos) ans[i] = chr[maxi], sz[maxi]--;
		for (int i = 1; i <= n; i++) {
			if (ans[i]) continue;
			for (int j = 1; j <= cnt; j++) {
				if (sz[j]) {
					ans[i] = chr[j];
					sz[j]--;
					break;
				} 
			}
		}
		printf("%s\n", ans + 1);
	}
	return 0;
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF123A Prime Permutation
## 大意
给出一个字符串，问能否通过打乱它的顺序得到一个新的字符串，这个字符串满足所有的质数位和位数是这个质数的倍数的位数上的字母相同，输出能否，如果能，输出 $\texttt {YES}$，构造一组解；否则，输出 $\texttt {NO}$。
## 思路

首先我们可以观察一下，~~爬线~~发现对于任意质数 $m$ 和任意 $j=2,3,5,7,...,\frac{\lfloor s \lfloor}{m}$，又有 $s_m=j\times s_m$，又因为 $i≥2$，则 $s_{m}$ 一定与 $s_{2m}$ 相等。而 $2$ 是个质数，所以 $s_m$ 一定与 $s_{2}$ 相等。

所以我们计算出所有合数和所有小于 $\frac {\lfloor s \lfloor} {2}$ 的质数后统计共有多少个，然后判断出现次数最多的字符有没有超过这个数。

1. 如果没有，那么肯定不行。返回，~~炸！！！~~
2. 如果有，那么就把上面提到的所有符合要求的下标的字符全部填上出现次数最多的字符，然后剩下的随便填即可。

## 代码参考

```cpp
#include <bits/stdc++.h>
#define rep(i,x,y) for (int i=x;i<=y;i++)
#define rrep(i,x,y) for (int i=y;i>=x;i--)
using namespace std;
string s;
map<char,int> st;
int maxn,sp;
char p,a[1001];
bool b[1001];
inline bool prime (int k)
{
	if (k<2) return false;
	for (int i=2;i*i<=k;i++)
		if (k%i==0) return false;
	return true;
}
int main ()
{ 
	cin>>s;
	rep (i,0,s.size ()-1) st[s[i]]++;
	for (auto i:st)
		if (maxn<i.second)
			maxn=i.second,p=i.first;
	rep (i,2,s.size ())
		if (!prime (i)) b[i]=1,sp++;
			else if (i<=s.size ()/2) b[i]=1,sp++;  
	if (maxn<sp) cout<<"NO\n",exit (0);
	cout<<"YES\n",st[p]-=sp;
	rep (i,1,s.size ())
		if (b[i]) a[i]=p;
	int w=1;
	for (auto i:st)
		rep (j,1,i.second)
		{
			while (a[w]==p) w++;
			a[w++]=i.first;
		}
	rep (i,1,s.size ()) cout<<a[i];
	return 0;
}
```

---

## 作者：Rei_Sen (赞：0)

やあやあ，这里是铃仙酱 $\sim$。

由于铃仙今天试师酱的药试多了，所以代码可能写的比较晕乎，还请见谅。

题目给了我们若干颜色和每个颜色能染的元素个数，我们需要把每个质数和的每个质数的倍数放到分别放到各个集合里，形成的若干个集合，然后分别对他们进行染色，要求同一个集合内的元素颜色一致，问存不存在合法染色方案。

首先，我们不难发现一个性质，就是如果两个集合有交，则这两个集合的颜色一定一样的，证明过易，此处省略。

于是我们不妨从图的角度来看这个题，设 $p$ 为质数，$i$ 整数且 $\ge 2$，且保证 $pi\le n$，此时我们让 $pi$ 向 $p(i-1)$ 连边，就能得到若干个连通块，更准确的说是一个森林。然后这个时候我们的问题就变成了：

>有 $|\Sigma|$ 种颜料，每种颜料能染 $c_i$ 长度，现有 $n$ 条线段，每条线段长 $k_i$，问能否存在一种染色方案，使得每条线段的颜色单一。

然后我们发现这个问题似乎有点困难，故不妨继续深挖一下性质，然后不难得出，我们这样连边只会得到一棵树和若干个点，但是为什么呢，理由如下：

> 考虑如果想要一条边存在，我们必定得让 $i$ 和 $i-1$ 同为正整数，然后由于我们数保证了 $1 \sim n$ 都是出现的，所以如果 $pi\,(i\gt2)$ 出现了，则 $2p$ 一定出现了，由于 $2$ 也是一个质数，所以不难得出此时 $2p$ 已经在 $2$ 所属的集合中，则说明 $p$ 及其他 $pi$ 都应当与 $2$ 所在的集合的颜色一致，故要么只出现了 $p$（也就是单个点），要么他已经与 $2$ 所在的那棵树有了连边。

那么此时，我们不难想到用并查集维护那个大集合，最后判断一下某种颜色能不能染集合的 $siz$ 次就好了，然后构造就特判一下当前数是否属于并查集维护的那个大集合即可，时间复杂度这里我是暴力合并，所以为 $o({|s|}^2)$，至于为啥用小写 $o$，原因是铃仙这里懒得详细的计算具体的复杂度了，不过肯定不会比 $n^2$ 更劣罢了。

但是！这真的是这个题的极限吗？显然不是，我们再仔细的审一下这个题，题目让我们把**每个质数和的每个质数的倍数**染成同一个颜色，再根据上面的结论，我们不难得出，题目想让我们干的是把 **$1 \sim |s|$ 中存在倍数的质数及其倍数**染成同一个颜色，那么根据唯一分解定理，我们不难发现， $1 \sim |s|$ 中除了 $1$ 以外的合数全都会被染成同一个颜色，换句话讲，就是 $1 \sim  n$ 中的所有 $\ge \lfloor \dfrac{|s|}{2} \rfloor$ 的质数都是单一的点，那么，我们就可以 $O(1)$ 计算我们所需要的染色次数，由于预处理是 $O(n)$，所以我们就在 $O(n)$ 的复杂度内解决了该题。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_SIZE = 1e5;
const int MAX_COLS = 30;
bitset<MAX_SIZE> nf;
int presum[MAX_SIZE];
vector<int> primes;
void shai(int n) {
	nf[0] = nf[1] = 1; 
	presum[0] = presum[1] = 0;
	for (int i = 2; i <= n; i++) {
		if (!nf[i]) {
			primes.push_back(i);
		}
		presum[i] = presum[i-1] + !nf[i];
		for (int j = 0; j < (int)primes.size() && i * primes[j] <= n; j++) {
			nf[primes[j] * i] = true;
			if (i % primes[j] == 0) {
				break;
			}
		}
	}
}
int cnt[MAX_SIZE];
int main() {
	string s;
	cin >> s;
	int n = s.length();
	for (auto c : s) {
		++cnt[c - 'a'];
	}
	shai(n * 2);
	int siz_need = n - (presum[n] + 1) + presum[n / 2];
	char fillc = -1;
	for(int i = 0; i < 26; i++){
		if(cnt[i] >= siz_need){
			cnt[i] -= siz_need;
			fillc = i + 'a';
			break;
		}
	}
	if(fillc == -1) {
		puts("NO");
		return 0;
	}
	puts("YES");
	int p = 0;
	for(int i = 1; i <= n; i++){
		if(nf[i] && i != 1) {
			putchar(fillc);
		} else if(i <= n / 2 && i != 1) {
			putchar(fillc);
		} else {
			while(!cnt[p]) ++p;
			--cnt[p];
			putchar(p + 'a');
		}
	}
	return 0;
}
```



---

