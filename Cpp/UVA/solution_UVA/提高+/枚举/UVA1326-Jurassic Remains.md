# Jurassic Remains

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=446&page=show_problem&problem=4072

[PDF](https://uva.onlinejudge.org/external/13/p1326.pdf)

# 题解

## 作者：VenusM1nT (赞：2)

$\texttt{Meet in the middle}$。

今天上午法老在讲这个，趁机找了道题qwq

那么 $\texttt{Meet in the middle}$ 到底是个啥呢？它类似于一种分治算法，本质上是将一个暴力解决会超时的问题分成两块，用可以接受的暴力复杂度解决第一块，再解决第二块再合并，只要合并的时间复杂度足够优秀，那么就可以过这样的题。

然而这种算法的面向群体一般是爆搜题emm

比如这题，我们可以考虑枚举选取的子集，显然一组数据的复杂度是 $\Theta(n\times 2^n)$，在极限数据和多组数据的情况下很显然要超时，我们考虑将其分而治之。

首先我们可以用异或的方法来表示一个字符取到奇数次还是偶数次，然后我们枚举前 $\frac{n}{2}$ 个子串，用 $\texttt{map}$ 维护异或和，这样的好处是什么呢？我们知道，我们最后要求的若干个串中，每个字母的出现次数是偶数，而只有两个数完全相同，它们的异或和才是 $0$（也就是出现偶数次），这样我们可以在枚举后 $\frac{n}{2}$ 个子串时，直接在 $\texttt{map}$ 里找有没有相同的异或和就行了，而不用算出来再合并，比较方便。

```cpp
#include<bits/stdc++.h>
#define MAXN 35
#define MAXM 10005
#define reg register
#define inl inline
using namespace std;
map <int,int> m;
int n,has[MAXN];
char ch[MAXM];
inl int lowbit(reg int x)
{
	return x&-x;
}
inl int Calc(reg int x)
{
	reg int res=0;
	for(;x;x-=lowbit(x)) res++;
	return res;
}
int main()
{
	while(cin>>n)
	{
		m.clear();
		memset(has,0,sizeof(has));
		for(reg int i=0;i<n;i++)
		{
			scanf("%s",ch+1);
			reg int len=strlen(ch+1);
			for(reg int j=1;j<=len;j++) has[i]^=1<<ch[j]-65;
		}
		reg int ans=0,n1=n/2,n2=n-n1;
		for(reg int i=0;i<(1<<n1);i++)
		{
			reg int x=0;
			for(reg int j=0;j<n1;j++) if(i&(1<<j)) x^=has[j];
			if(!m.count(x) || Calc(m[x])<Calc(i)) m[x]=i;
		}
		for(reg int i=0;i<(1<<n2);i++)
		{
			reg int x=0;
			for(reg int j=0;j<n2;j++) if(i&(1<<j)) x^=has[n1+j];
			if(m.count(x) && Calc(ans)<Calc((i<<n1)^m[x])) ans=(i<<n1)^m[x];
		}
		printf("%d\n",Calc(ans));
		for(reg int i=0;i<n;i++) if(ans&(1<<i)) printf("%d ",i+1);
		puts("");
	}
	return 0;
}
```

---

## 作者：gyfer (赞：2)

# Meet int the middle
看一眼这道题，要求你将字符串分成较多集合，每个集合内字母出现偶数次。
## 首先，如何处理字母出现偶数次？
我们将每个不同的字母进行hash处理

我们进行异或和，根据异或的性质，出现奇数次为1，偶数次为0，最后只要求答案为0。那么答案就**可求**了。

## 我会枚举子集！
复杂度 $$ O(n * 2^n ) $$ 显然对于n = 24的数据范围只能呵呵。
## 一般对于这种 n 明显比可做数据范围大2倍左右的数据范围我们自然的想到meet int the middle(折半搜索）
我们考虑前半段和后半段的异或值，显然他们异或起来等于0时是答案。
那么我们就可以分开处理，先预处理前半部分，再计算后半部分的答案。
如果后半部分算出来的值在前半部分有的话就可以当做答案

这种meet in the middle 正如泰戈尔中的诗一样
```
就像海鸥与海浪那样，我们相遇，彼此走近。 
海鸥飞走，海浪退去，我们远离。
Like the seagulls and the waves, 
we meet and approach each other.
The seagulls fly away, 
the waves retreat,
we are far away.
```
两部分互不干扰只有算答案的时候有贡献

**这正是折半搜索的基本操作及本质**

My code:
``` c++
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#include<cmath>
#include<map>
using namespace std;
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define PER(i, a, b) for(int i = a; i >= b; i--)
#define LL long long
inline int read(){
    int x = 0, flag = 1;char ch = getchar();
    if(ch == '-') flag = -1;
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * flag;
}
int n;
char ch[1000];
int a[30];
map <int, int> mp;
int calc(int x) {//计算集合个数
    int res = 0;
    for(; x; x-=(x &(-x))) ++ res;
    return res;
}
int main() {
    while(scanf("%d", &n) == 1) {
        REP(i, 1, n) {
            scanf("%s", ch);
            a[i] = 0;
            for(int j = 0; j < strlen(ch); ++j) 
                a[i] ^= 1 << (ch[j] - 'A');//字符串hash
        }
        mp.clear();
        int mid = n / 2;
        int lim = (1 << mid) - 1;
        REP(i, 0, lim) {
            int x = 0;
            REP(j, 1, mid) 
                if(i & (1 << (j - 1))) x ^= a[j];
            if(!mp.count(x) || calc(mp[x]) < calc(i)) mp[x] = i;
        }
        int ans = 0;
        lim  =  (1 << (n - mid)) - 1;//分而治之
        REP(i, 0, lim) {
            int x = 0;
            REP(j, mid + 1, n)
                if(i & (1 << (j - mid - 1))) x ^= a[j];
            if(mp.count(x) && calc(ans) < calc(i) + calc(mp[x])) ans = (i << mid) ^ mp[x];
        }
        cout << calc(ans) << endl;
        REP(i, 0, n - 1) {
            if(ans & (1 << i)) printf("%d ",i+1);
        }
        cout << endl;
    }
	return 0;
}
```


---

## 作者：Milthm (赞：2)

拿到题目考虑搜索，但是复杂度 $O(Tn\times 2^n)$，虽然 $n$ 最大只有 $24$，但是多组数据，还是会炸。

但是看到 $24$ 和偶数这两个东西，我们想到把每个字符串压成 $2$ 进制。那如何判断是偶数呢？

我们先把每个字符串字母出现的次数偶数设为 $0$，奇数为 $1$。我们又知道，一个数异或自己偶数次是 $0$。这样就好办了，我们暴力搜索每个数字判断选不选，把它们异或起来，最后结果如果是 $0$ 就统计答案即可。

时间复杂度 $O(T\times2^n)$，足以通过本题。

### AC code

```cpp
#include<iostream>
using namespace std;
string s[30]; 
int n,a[30],b[30],ans,qwq[30],cnt,ttq[30];
void dfs(int x,int sum){
	if(x>n){
		if(sum==0&&cnt>ans){
			ans=cnt;
			for(int i=1;i<=cnt;++i)ttq[i]=qwq[i];
		}
		return;
	}
	qwq[++cnt]=x;
	dfs(x+1,sum^a[x]);
	--cnt;
	dfs(x+1,sum);
}
int main(){
	while(cin>>n){
		ans=0;
		for(int i=1;i<=n;++i)ttq[i]=a[i]=cnt=0;
		for(int i=1;i<=n;++i){
			cin>>s[i];
			for(int j=0;j<26;++j)b[j]=0;
			int l=s[i].size();
			for(int j=0;j<l;++j)b[s[i][j]-'A']++;
			for(int j=0;j<26;++j)a[i]=(a[i]<<1)+(b[j]&1);
		}
		dfs(1,0);
		cout<<ans<<'\n';
		for(int i=1;i<=ans;++i)cout<<ttq[i]<<" ";
		cout<<'\n';
	}
	return 0;
}

```


---

## 作者：翼德天尊 (赞：2)

提供一个不一样的思路~

——暴力！（）

首先根据异或的性质，可以将每一个字符串转成一个长度为 $26$ 的 $01$ 串，每一位表示存在奇数个该字母还是偶数个该字母。

观察题目数据范围：

> $1\le n\le 24$

~~正解~~ 暴力代码油然而生：$2^n$ 枚举！不妨考虑枚举每一个串是否选择，最终统计答案即可。

代码简洁易懂~

记得递归的同时顺便记录方案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 30
int n,ans,k[N],anss;
bool g[N][N];
int read(){
	int w=0,fh=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') fh=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*fh;
}
void dfs(int now,int sum,int h,int jl,int two){
	if (now==n+1){
		if (h==0)
			if (sum>ans) ans=sum,anss=jl;
		return;
	}
	dfs(now+1,sum+1,h^k[now],jl+two,two<<1);
	dfs(now+1,sum,h,jl,two<<1);
	
}

int main(){
	while (scanf("%d",&n)==1){
		memset(g,0,sizeof(g));
		memset(k,0,sizeof(k));
		ans=anss=0;
		for (int i=1;i<=n;i++){
			string s;
			cin>>s;
			int x=1;
			for (int j=0;j<s.size();j++)
				g[i][s[j]-'A']^=1;
			for (int j=0;j<26;j++)
				k[i]+=x*g[i][j],x<<=1;
		}
		dfs(1,0,0,0,1);
		printf("%d\n",ans);
		for (int i=1;i<=n;i++){
			if (anss%2) printf("%d ",i);
			anss>>=1;
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：wangbinfeng (赞：1)

[![](https://img.shields.io/badge/题目-UVA1326__Jurassic__Remains-green)
![](https://img.shields.io/badge/难度-提高+/省选---blue)
![](https://img.shields.io/badge/考点-二进制、暴力（DFS）-yellow)
![](https://img.shields.io/badge/题型-传统题-red)](https://www.luogu.com.cn/problem/UVA1326)
[![](https://img.shields.io/badge/作者-wangbinfeng(387009)-purple)](https://www.luogu.com.cn/user/387009)

------------

首先，由于是 UVA 的题目，可能无法查看题目，翻译也不太好。在这里放出[我认为更好一点的翻译](https://www.luogu.com.cn/discuss/52102)和我手敲的样例：
```
.in:
1
ABC
6
ABD
EG
GE
ABE
AC
BCD
.ans:
0

5
1 2 3 5 6
```

下面开始分析：

首先读入字符串，由于字母最多只有 $26$ 个，所以显然可以用二进制存储。在这里，二进制中 `0` 代表偶数个，`1` 代表奇数个（因为这样方便记录，可以直接使用异或运算）。   
应当知道，一个数异或自身奇数次为自身，一个属异或自身偶数次为 `0`。因此，我们可以使用异或结果来存储当前状态。   
当且仅当状态值为 `0` 时代表所有字母均为偶数次，因为若存在奇数次则根据异或可知该位一定时 `1`。   
代码很好写，读入时将字符串转换为二进制串即可。然后暴力（DFS）求答案。  
剪枝很容易，比如折半 DFS，但这道题并没有必要，有兴趣的读者可以自己尝试。具体实现可以看注释。时间复杂度为 $\Theta \left(T\times2^n\right)$。

代码如下：
```cpp
//T组数据 
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x=0,f=1;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar())if(c=='-')f=-f;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
int now[30],ans[30],anss,dat[30],n;//now存储当前选择的字符串编号，anss存储数量
char s[1000000];//我并不知道字符串最大长度
void dfs(int st,int ed,int state,int sum){//sum存储档当前数量，state存储当前状态
	if(st>ed&&!state&&sum>anss){
		anss=sum;
		for(int i=1;i<=sum;i++)ans[i]=now[i];
		return;
	}
	if(st>ed)return;
	dfs(st+1,ed,state,sum);
	now[++sum]=st;
	dfs(st+1,ed,state^dat[st],sum);
}
signed main(){
	for(;scanf("%lld",&n)==1;anss=0,memset(dat,0,sizeof(dat))){//多测记得清空！ 
		for(int i=1;i<=n;i++){
			scanf("%s",s);//如果上面用scanf，下面一定用scanf，否则可能出一些奇奇怪怪的小bug 
			for(int j=0;s[j];j++)dat[i]^=1<<(s[j]-'A');
		}
		dfs(1,n,0,0);
		printf("%lld\n",anss);
		for(int i=1;i<=anss;i++)printf("%lld ",ans[i]);
		printf("\n");
	}
}
```

---

## 作者：Lyccrius (赞：1)

在一个字符串中，每个字符出现的次数本身是无关紧要的，重要的只是这些次数的奇偶性，因此想到用一个二进制的位表示一个字母（$1$ 表示出现奇数次，$0$ 表示出现偶数次）。

问题转化为求尽量多的数，使得它们的 $\text{xor}$ （异或）值为 $0$。

注意到 $\text{xor}$ 值为 $0$ 的两个整数必需完全相等，我们可以把字符串分成两部分：首先计算前 $n / 2$ 个字符串所能得到的所有 $\text{xor}$ 值，并将其保存到一个映射 $S$（$\text{xor}$ 值 $\to$ 前 $n / 2$ 个字符串的一个子集）中；然后枚举后 $n / 2$ 个字符串所能得到的所有 $\text{xor}$ 值，并每次都在 $S$ 中查找。

这样的策略称为中途相遇法。

```
#include <cstdio>
#include <map>

const int maxN = 24 + 10;

int N;
int A[maxN];
char s[10000 + 10];
std::map<int, int> table;

int bitCount(int x) {
    if (x == 0) return 0;
    return bitCount(x / 2) + (x & 1);
}

int main() {
    while (scanf("%d", &N) == 1 && N) {
        char s[1000 + 10];
        for (int i = 0; i < N; i++) {
            scanf("%s", s);
            A[i] = 0;
            for (int j = 0; s[j] != '\0'; j++) A[i] ^= (1 << (s[j] - 'A'));
        }
        table.clear();
        int N1 = N / 2;
        int N2 = N - N1;
        for (int i = 0; i < (1 << N1); i++) {
            int x = 0;
            for (int j = 0; j < N1; j++) if (i & (1 << j)) x ^= A[j];
            if (table.count(x) || bitCount(table[x]) < bitCount(i)) table[x] = i;
        }
        int ans = 0;
        for (int i = 0; i < (1 << N2); i++) {
            int x = 0;
            for (int j = 0; j < N2; j++) if (i & (1 << j)) x ^= A[N1 + j];
            if (table.count(x) && bitCount(ans) < bitCount(table[x]) + bitCount(i)) ans = (i << N1) ^ table[x];
        }
        printf("%d\n", bitCount(ans));
        for (int i = 0; i < N; i++) if (ans & (1 << i)) printf("%d ", i + 1);
        printf("\n");
    }
    return 0;
}
```

---

