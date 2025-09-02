# [ICPC 2021 WF] Prehistoric Programs

## 题目描述

考古学家在 Alutila 洞穴的深层发现了令人兴奋的粘土板。除了两个似乎描述嵌套结构的符号（类似于 LISP 中的开括号和闭括号）外，没有人能够破译粘土板上的文字。难道几千年前人类就已经在编写程序了吗？

综合来看，这些粘土板似乎描述了一项伟大的作品——可能是一个程序，或者是一部史诗，甚至是税务记录！不出所料，经过这么长时间，粘土板已经处于无序状态。你的任务是将它们排列成一个序列，使得结果作品具有正确嵌套的括号结构。仅考虑开括号和闭括号，一个正确嵌套的结构要么是

- $()$，或者
- $(A)$，其中 $A$ 是一个正确嵌套的结构，或者
- $AB$，其中 $A$ 和 $B$ 是正确嵌套的结构。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
())())()
((()
```

### 输出

```
2
1```

## 样例 #2

### 输入

```
5
(
))
((
))
(
```

### 输出

```
1
5
3
4
2
```

## 样例 #3

### 输入

```
2
((
)
```

### 输出

```
impossible
```

# 题解

## 作者：iyaang (赞：2)

[神秘的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17574755.html)

[题目链接](https://www.luogu.com.cn/problem/P9446)

套路的，将 `(` 视为 $1$,`)` 视为 $-1$，显然如果所有序列的和不为 $0$ 则无解。

对于一个括号序列，记序列和为 $sum$，任意前缀和的最小值为 $mix$。称一个序列为正平衡当且仅当 $sum \geq 0$，否则为负平衡。能够发现如果存在一种合法构造方案，出现了一个负平衡序列放在了正平衡序列前，那么调换这两个序列依旧可以得到一组合法的构造，所以我们先放置所有的正平衡序列，再放置所有的负平衡序列。同种平衡的序列考虑贪心放置，对于正平衡序列，按照 $mix$ 从大到小放；对于负平衡序列，按照 $sum - mix$ 从小到大放，这样可以尽量避免未配对右括号的出现。

按照这种贪心策略构造的解如果依然不合法，则无解。check 是简单的，记录一个总和 $all$ 依次累加，每加一个新序列 $i$ 看看 $all + mix_i$ 会不会小于 $0$ 即可。记 $N = \sum_{i = 1}^n |S_i|$，于是做到 $\mathcal O(N)$。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
using namespace std;

namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        putchar(ch);
        return;
    }
}
using namespace FastIO;

namespace MTool
{   
    #define TA template<typename T,typename... Args>
    #define TT template<typename T>
    static const int Mod=998244353;
    TT inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    TT inline void cmax(T &a,T b) {a=a>b?a:b;}
    TT inline void cmin(T &a,T b) {a=a<b?a:b;}
    TT inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
    TT inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    TT inline void Mmul(T &a,T b) {a=a*b%Mod;}
    TT inline void Mmod(T &a) {a=(a%Mod+Mod)%Mod;}
    TT inline T Cadd(T a,T b) {return a+b>=Mod?a+b-Mod:a+b;}
    TT inline T Cdel(T a,T b) {return a-b<0?a-b+Mod:a-b;}
    TT inline T Cmul(T a,T b) {return a*b%Mod;}
    TT inline T Cmod(T a) {return (a%Mod+Mod)%Mod;}
    TA inline void Madd(T &a,T b,Args... args) {Madd(a,Cadd(b,args...));}
    TA inline void Mdel(T &a,T b,Args... args) {Mdel(a,Cadd(b,args...));}
    TA inline void Mmul(T &a,T b,Args... args) {Mmul(a,Cmul(b,args...));}
    TA inline T Cadd(T a,T b,Args... args) {return Cadd(Cadd(a,b),args...);}
    TA inline T Cdel(T a,T b,Args... args) {return Cdel(Cdel(a,b),args...);}
    TA inline T Cmul(T a,T b,Args... args) {return Cmul(Cmul(a,b),args...);}
    TT inline T qpow(T a,T b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    TT inline T qmul(T a,T b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    TT inline T spow(T a,T b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;}
    TT inline void exgcd(T A,T B,T &X,T &Y) {if(!B) return X=1,Y=0,void(); exgcd(B,A%B,Y,X),Y-=X*(A/B);}
    TT inline T Ginv(T x) {T A=0,B=0; exgcd(x,Mod,A,B); return Cmod(A);}
    #undef TT
    #undef TA
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=10000010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    int n,all,sum,len,flag;
    struct lmy{int mix,sum;}a[MAX];
	char s[MAX];
	vector<int> pos,neg;

    inline void lmy_forever()
    {
    	read(n);
    	for(int i=1;i<=n;++i)
    	{
    		scanf("%s",s+1),len=strlen(s+1);
    		for(int j=1;j<=len;++j) a[i].sum+=(s[j]=='('?1:-1),cmin(a[i].mix,a[i].sum);
    		all+=a[i].sum;
    		if(a[i].sum>=0) pos.eb(i); else neg.eb(i);
		}
		if(all) return puts("impossible"),void();
		sort(pos.begin(),pos.end(),[&](int x,int y){return a[x].mix>a[y].mix;});
		sort(neg.begin(),neg.end(),[&](int x,int y){return a[x].mix-a[x].sum<a[y].mix-a[y].sum;});
		for(auto tab:pos) flag|=(sum+a[tab].mix<0),sum+=a[tab].sum;
		for(auto tab:neg) flag|=(sum+a[tab].mix<0),sum+=a[tab].sum;
		if(flag) return puts("impossible"),void();
		for(auto it:pos) write(it,'\n');
		for(auto it:neg) write(it,'\n');
        return;
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：CznTree (赞：0)

通过经典的括号序列套路，我们将左括号置为 $1$，右括号置为 $-1$。考虑一段的和 $sum$ 以及前缀最小值 $min$。

因为我们希望让他合法的话，可以考虑对于 $sum_i \ge 0$ 的部分以 $min_i$ 进行降序排序。实际上如果不合法那么就与你的顺序没有任何关系了。

代码也很简单吧。删去了一些是个人都会的部分。

```cpp

bool cmp1(int x, int y) {
	return min[x] > min[y]; 
}

bool cmp2(int x, int y) {
	return min[x] - sum[x] < min[y] - sum[y]; 
}

void solve() {
	if(flag){
		std::cout << "impossible" << endl; 
		return ; 
	}

	std::sort(a + 1, a + 1 + cnta, cmp1); std::sort(b + 1, b + 1 + cntb, cmp2); 

	
	rep(i, 1, cnta) {
		if(flag + min[a[i]] < 0) {
			std::cout << "impossible" << endl;
			return ; 
		}
		flag += sum[a[i]];
	}

	rep(i, 1, cntb) {
		if(flag + min[b[i]] < 0) {
			std::cout << "impossible" << endl;
			return ; 
		}
		flag += sum[b[i]];
	}

```

---

## 作者：steambird (赞：0)

## 思路

### Step 1. 简化题意

考虑到只有两种括号，思考我们如何进行括号匹配：令 $v$ 表示当前有多少个左括号未匹配，设初始时 $v=0$，遇到一个 `(` 就把 $v$ 加一，遇到 `)` 就减一，若始终有 $v \ge 0$，且最终 $v=0$，则原序列合法。

因此，对每个字符串的每个位置求 $v$（不要求 $v \ge 0$，此时若 $v < 0$，表示有 $-v$ 个右括号要求左括号），问题可以转化为：设 $a_i$ 为 $v$ 的最终值，$b_i$ 为 $v$ 过程中的最小值，满足 $b_i \le 0$，要求所有 $a_i$ 的和为 $0$（否则一定无解），现在需要构造一个 $1$ 到 $n$ 的排列 $p_1,p_2,\dots,p_n$，满足：

$$\forall i \in [2,n],\sum_{j=1}^{i-1} a_j \ge -b_i$$

显然，如果 $a_i \ge 0$，我们希望让 $b_i$ 较大（即对前缀和要求较小）的优先，如果 $b_i$ 相同，则 $a_i$ 较大的优先。但是这个贪心策略在 $a_i < 0$ 时是错的（[Hack](https://www.luogu.com.cn/paste/7ysyxmlp)）：例如如果 $a_i,b_i$ 都较小，我们希望它靠前放置而不是靠后。

### Step 2. “还原”题意

考虑上面所说的 $a_i$ 和 $b_i$ 的实质是什么。可以发现，对于每个字符串，如果 $a_i < 0$，我们可以将其转化为 $-b_i$ 个右括号与 $a_i - b_i$ 个左括号（为负则为 $b_i - a_i$ 个右括号）相连接的结果。这样构造出的字符串与原字符串等效（对之前有几个左括号的要求相同）。

我们希望有尽可能多的左括号在字符串的左边（越靠右能“帮助”的右括号越少）。因此，考虑下面的贪心策略：

- 如果 $a_i \ge 0$，则将 $b_i$ 从大到小排序后按顺序选择。如果有两个 $b_i$ 相同，比较 $a_i$，较大的优先。
- 否则，将 $a_i - b_i$ 从大到小排序后按顺序选择。如果有两个 $a_i - b_i$ 相同，比较 $b_i$，较大的优先。

这样即在实质上将左括号尽可能放到了左边。

## 代码

```c++
#include <bits/stdc++.h>
using namespace std;

inline void train() {
	   ios::sync_with_stdio(false);
	   cin.tie(0);
	   cout.tie(0);
}

inline int maxi(int a, int b) {
	return a > b ? a : b;
}

inline int mini(int a, int b) {
	return a < b ? a : b;
}

constexpr int N = 1e6+3;
int a[N], b[N], id[N], n;

bool cmp(int x, int y) {
	if (a[x] >= 0 && a[y] < 0) return true;
	else if (a[x] < 0 && a[y] >= 0) return false;
	else if (a[x] >= 0 && a[y] >= 0) {
		if (b[x] == b[y]) return a[x] > a[y];
		else return b[x] > b[y];
	} else {
		if ((a[x] - b[x]) == (a[y] - b[y])) {
			return b[x] > b[y]; 
		} else {
			return (a[x] - b[x]) > (a[y] - b[y]);
		}
	}
}

string s;

int main() {

	train();
	cin>>n;
	for (int i = 1; i <= n; i++) {
		cin>>s;
		int cur = 0;
		for (auto &j : s) {
			if (j == '(') cur++;
			else cur--;
			if (cur < b[i]) b[i] = cur;
		}
		a[i] = cur;
		id[i] = i;
	}
	sort(id+1,id+n+1,cmp);
	int ans = 0;
	for (int it = 1; it <= n; it++) {
		int i = id[it];
		if (ans < (-b[i])) {
			cout<<"impossible"<<endl;
			return 0;
		}
		ans += a[i];
	}
	if (ans != 0) {
		cout<<"impossible"<<endl;
		return 0;
	}
	for (int it = 1; it <= n; it++) cout<<id[it]<<'\n';

	cout<<flush;

	return 0;
}
```

---

## 作者：big_quantum (赞：0)

## 思路

[题目链接](https://www.luogu.com.cn/problem/P9446)

将 `(` 视为 $1$，`)` 视为 $-1$，若所有括号序列的和不为 $0$，显然无法构造合适的序列（左右括号没有办法一一对应）。

对第 $i$ 个括号序列，定义 $tot_i$ 为该括号序列所有左括号与右括号的和，$mix_i$ 为该括号序列从左向右遍历时所有位置前缀和的最小值。

### 举例：
`(()))()`

对这个括号序列进行遍历，可以得到如下数组：
```text
tot：1 2 1 0 -1 0 -1
mix：1 1 1 0 -1 -1 -1
```

所以该括号序列的 $tot = -1$，$mix = -1$。

---

考虑贪心地放置括号序列，显然将所有 $tot \ge 0$ 的序列放在左边，其余的放在右边。

那么对于左半部分，考虑在最左边尽可能的放置 `(`，即按 $mix$ 从大到小放置，以防止出现 `())` 这种括号被放在最左边的情况。

对于右半部分，同样考虑在最右边尽可能放置 `)`，用 $tot-mix$ 代替 $mix$ 并将排序顺序更改为从小到大（如果是从小到大就是在左边尽可能放置 `)`，还不明白请写几个括号序列然后手推一下）。

全部放置完后，对整个序列做一次检查，即求 $\sum_{i = 1}^n mix_i + tot_{i - 1}(tot_0 = 0)$，每一步运算中如果和小于 $0$，那么当前排序不合法，由于贪心思想，如果这样构造的序列都不合法，那就不可能存在合法序列。

### 为什么检查是必要的：

假定输入为：
```text
)(
()
```

我们可以构造出一个满足操作要求的序列 `())(`，显然它不合法，因此检查是必要的。

---

时间复杂度为 $O(N)$，其中 $N = \sum^n_{i = 1} S_i$，$S_i$ 为第 $i$ 个字符串的长度。

### code

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10000005;

int n, ans[MAXN], mix[MAXN], tot[MAXN], cnt;
vector<pair<int, int>> up, down;
string s;

bool cmp1(pair<int, int> a, pair<int, int> b){
    return a.first > b.first;
}

bool cmp2(pair<int, int> a, pair<int, int> b){
    return a.first < b.first;
}

int main(){
    cin >> n;
    memset(mix, 1, sizeof(mix));
    for(int i = 1; i <= n; i++){
        cin >> s;
        for(int j = 0; j < s.size(); j++){
            if(s[j] == '(') tot[i]++;
            if(s[j] == ')') tot[i]--;
            mix[i] = min(mix[i], tot[i]);
        }
        if(tot[i] >= 0){
            up.push_back(make_pair(mix[i], i));
        } else {
            down.push_back(make_pair(mix[i] - tot[i], i));
        }
        cnt += tot[i];
    }
    
    sort(up.begin(), up.end(), cmp1);
    sort(down.begin(), down.end(), cmp2);
    
    if(cnt != 0){
        cout << "impossible" << endl;
    } else {
        int all = 0;
        for(auto i : up){
            if(all + mix[i.second] < 0){
                cout << "impossible" << endl;
                return 0;
            }
			all += tot[i.second];
        }
        for(auto i : down){
            if(all + mix[i.second] < 0){
                cout << "impossible" << endl;
                return 0;
            }
			all += tot[i.second];
        }
        for(auto i : up){
            cout << i.second << endl;
        }
        for(auto i : down){
            cout << i.second << endl;
        }
    }
    return 0;
}
```

---

