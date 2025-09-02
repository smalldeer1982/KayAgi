# Intellectual Inquiry

## 题目描述

After getting kicked out of her reporting job for not knowing the alphabet, Bessie has decided to attend school at the Fillet and Eggs Eater Academy. She has been making good progress with her studies and now knows the first $ k $ English letters.

Each morning, Bessie travels to school along a sidewalk consisting of $ m+n $ tiles. In order to help Bessie review, Mr. Moozing has labeled each of the first $ m $ sidewalk tiles with one of the first $ k $ lowercase English letters, spelling out a string $ t $ . Mr. Moozing, impressed by Bessie's extensive knowledge of farm animals, plans to let her finish labeling the last $ n $ tiles of the sidewalk by herself.

Consider the resulting string $ s $ ( $ |s|=m+n $ ) consisting of letters labeled on tiles in order from home to school. For any sequence of indices $ p_{1}<p_{2}<...<p_{q} $ we can define subsequence of the string $ s $ as string $ s_{p1}s_{p2}...\ s_{pq} $ . Two subsequences are considered to be distinct if they differ as strings. Bessie wants to label the remaining part of the sidewalk such that the number of distinct subsequences of tiles is maximum possible. However, since Bessie hasn't even finished learning the alphabet, she needs your help!

Note that empty subsequence also counts.

## 说明/提示

In the first sample, the optimal labeling gives $ 8 $ different subsequences: "" (the empty string), "a", "c", "b", "ac", "ab", "cb", and "acb".

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF645E/9a7e922a3340c3ac5614145c3650ab330142ea1a.png)In the second sample, the entire sidewalk is already labeled. The are $ 10 $ possible different subsequences: "" (the empty string), "a", "b", "aa", "ab", "ba", "aaa", "aab", "aba", and "aaba". Note that some strings, including "aa", can be obtained with multiple sequences of tiles, but are only counted once.

## 样例 #1

### 输入

```
1 3
ac
```

### 输出

```
8
```

## 样例 #2

### 输入

```
0 2
aaba
```

### 输出

```
10
```

# 题解

## 作者：是个汉子 (赞：6)

[洛谷传送门](https://www.luogu.com.cn/problem/CF645E)	[CF传送门](http://codeforces.com/problemset/problem/645/E)

正好学校考试考到过一个加强版，写一写。

### Solution

很明显的DP

如果 $n=0$ ，设 $f_i$ 表示到 $i$ 位置之前不同的子序列数，可以得到两个转移方程：

1. 第 $i$ 位的字符之前没有出现过，方程就是 $f_i=2\times f_{i-1}+1$ 

   意思是有 $i-1$ 位时的方案，和 ${i-1}$ 位的每一种方案都加第 $i$ 位上的字符，还有自己 $1$ 种

2. 第 $i$ 位的字符出现过，方程是 $f_{i}=2\times f_{i-1}-f_{pre_{a_i}}$ 

   其中 $pre_{a_i}$ 是第 $i$ 位字符上次出现的位置，这个方程的意思是要减去上次这个字符的贡献

现在 $n>0$ ，因为要最大数量，所以第二个方程中 $f_{pre_{a_i}}$ 减的越少越好，那么填的时候按 $pre_{a_i}$ 从小到大依次填入最优

此时的复杂度是 $O(n+m)$ ，完全足够通过本题

---

但是，如果是 $n\leq 10^{18}$ 

这个时候，上面的方法就完全不行了

我们发现在填 $n$ 的时候，每 $k$ 位都算是一个循环节，而 $k\leq 26$ 

我们可以考虑用一些和 $k$ 有关且能快速求出答案的方法——矩阵快速幂

将矩阵初始化的时候考虑第 $i$ 个字符和第 $j$ 个字符之间的相互影响即可

时间复杂度： $O(m+k^3\log n)$ 

注意：运算的时候没加空集，输出答案的时候记得加上

### Code

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int mod=1e9+7,N=4e6+10;
int m,k,a[N],vis[N],q[N],cnt,f[N],pre[N],tot,pow2[N];
ll n,t,ans,d;
char s[N];

inline int add(int x,int y){return x+y>mod?x+y-mod:x+y;}
inline int dec(int x,int y){return x-y<0?x-y+mod:x-y;}

struct matrix{
    int c[210][210];
    void init(int d=0){
        for(int i=1;i<=k+1;i++)
            for(int j=1;j<=k+1;j++)
                c[i][j]=0;
        for(int i=1;i<=k+1;i++) c[i][i]=d;
    }
    matrix operator * (matrix x){
        matrix res;
        res.init();
        for(int i=1;i<=k+1;i++)
            for(int j=1;j<=k+1;j++)
                for(int l=1;l<=k+1;l++)
                    res.c[i][j]=add(res.c[i][j],1ll*c[i][l]*x.c[l][j]%mod);
        return res;
    }
}Ans;

matrix Fpow(matrix a,ll b){
    matrix res;
    res.init(1);
    while(b){
        if(b&1) res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}

int main(){
    scanf("%lld%d",&n,&k);cnt=k;
    scanf("%s",s+1);
    m=strlen(s+1);
    for(int i=1;i<=m;i++)
        a[i]=s[i]-'a'+1;
    for(int i=m;i>=1;i--)
        if(!vis[a[i]]) q[--cnt]=a[i],vis[a[i]]=1;
    for(int i=1;i<=k;i++)
        if(!vis[i]) q[--cnt]=i;
    memset(pre,-1,sizeof(pre));
    t=min(n,1ll*k);
    for(int i=1;i<=m+t;i++){
        if(i>m) a[i]=q[tot],tot=(tot+1)%k;
        if(pre[a[i]]!=-1) f[i]=dec(add(f[i-1],f[i-1]),f[pre[a[i]]-1]);
        else f[i]=add(add(f[i-1],f[i-1]),1);
        pre[a[i]]=i;
    }
    if(n==t){
        printf("%d\n",f[n+m]+1);
        return 0;
    }
    Ans.init();
    pow2[0]=1;
    for(int i=1;i<=k+1;i++) pow2[i]=pow2[i-1]*2%mod;
    Ans.c[1][k+1]=1;
    for(int i=2;i<=k+1;i++){
        for(int j=1;j<i-1;j++)
            Ans.c[i][j]=dec(mod,pow2[i-j-1]);
        Ans.c[i][i-1]=mod-1;
        Ans.c[i][k+1]=add(Ans.c[i][k+1],pow2[i-1]);
    }
    d=(n-1)/k,n-=d*k;
    Ans=Fpow(Ans,d);
    for(int i=0;i<=k;i++)
        ans=add(ans,1ll*f[m+i]*Ans.c[n+1][i+1]%mod);
    printf("%d\n",ans+1);
    return 0;
}
```



---

## 作者：_yolanda_ (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF645E) | [无耻地宣传我的博客](https://www.cnblogs.com/yolanda-yxr/p/16811810.html)

~~看一眼题，没什么思路，那大概就是个 dp 了。~~

先求已知序列的方案数。

考虑怎么设计状态。

因为 **本质不同** ，如果设 $f[i]$ 表示，前 $i$ 个元素构成的序列的本质不同子序列个数似乎不太好转移。

但是 $f[i]$ 表示以 $i$ 结尾的子序列方案数似乎要好一些。让每个子序列只在第一次出现时被统计。

转移：

1. 当 $a[i]$ 与前面的字符都不同时，那么前面的所有方案后面再加上这个字符一定是不同的，并且这个字符本身也算一个新的子序列。于是有了

$$f[i]=\sum_{j=1}^{i-1}{f[j]} +1$$

2. 当 $a[i]$ 在前面出现过时，记前一个位置为 $lst[i]$，那么 $lst[i]$ 以前的方案末尾加上当前字符已经在 $lst[i]$ 被统计过了，所以只能在以 $lst[i]$ 到 $i$ 中间这一段字符结尾的方案后面加当前字符。于是有

$$f[i]=\sum_{j=lst[i]}^{i-1}f[j]$$

显而易见，上面的求和可以用前缀和，再记录一个 $lst$ 数组就行 能求出已知序列的方案数了。

```cpp
for(int i=1;i<=n;++i){
	if(!lst[a[i]])	f[i]=sum[i-1]-sum[0]+1;
	else	f[i]=sum[i-1]-sum[lst[a[i]]-1];
	f[i]=(f[i]%p+p)%p;
	lst[a[i]]=i,sum[i]=sum[i-1]+f[i];
	sum[i]%=p;
}
```

从上面的转移得知，每次用前缀和更新时，右端点一定是 $i-1$，为了让值尽量大，那就一定要让左端点尽量靠前，也就是 $lst[i]$ 尽量小。

这样就有了一个贪心策略，每次填字符的时候填当前 $lst$ 最小的字符。稍稍模拟一下就会发现这其实是循环填进去的。

所以只需要把上面的 $lst$ 数组拿来排一下序，按照排序结果不断地填字母，并且按照上面同样的方法计算答案，直到填的个数到达 $n$。

因为有空序列的存在，最后答案加一就好。

排序复杂度很小忽略不计，所以总复杂度应该是 $O(n+m)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int sum=0,f=1;char a=getchar();
	while(a<'0' || a>'9'){if(a=='-')	f=-1;a=getchar();}
	while(a>='0' && a<='9')	sum=sum*10+a-'0',a=getchar();
	return sum*f;
}

const int N=2e6+5,p=1e9+7;
int lst[105],f[N],sum[N],a[N],q[N];
int n,m,k;
bool cmp(int _,int __){return lst[_]<lst[__];}
signed main(){
	
	m=read(),k=read();
	string s;cin>>s;n=s.size();
	for(int i=0;i<n;++i)	a[i+1]=s[i]-'a'+1;
	for(int i=1;i<=n;++i){
		if(!lst[a[i]])	f[i]=sum[i-1]-sum[0]+1;
		else	f[i]=sum[i-1]-sum[lst[a[i]]-1];
		f[i]=(f[i]%p+p)%p;
		lst[a[i]]=i,sum[i]=sum[i-1]+f[i];
		sum[i]%=p;
	}
	for(int i=1;i<=k;++i)	q[i]=i;
	sort(q+1,q+k+1,cmp);
	for(int i=n+1,j=1;i<=n+m;++i){
		a[i]=q[j];
		if(!lst[a[i]])	f[i]=sum[i-1]-sum[0]+1;
		else	f[i]=sum[i-1]-sum[lst[a[i]]-1];
		f[i]=(f[i]%p+p)%p;
		lst[a[i]]=i,sum[i]=sum[i-1]+f[i];
		sum[i]%=p;
		++j;if(j==k+1)	j=1;
	}
	cout<<sum[n+m]+1;
	
	return 0;
}
```

---

最后提一嘴，见过一个加强版，$n$ 直接到了 $10^{18}$，这个时候就不能直接枚举了，观察发现在填了几个字符后 $sum[i]$ 的计算方式就比较固定了，可以用矩阵乘法优化。（博客园有矩阵乘法的代码，链接在上面）

---

## 作者：BFqwq (赞：4)

其实楼下的题解已经讲得非常清楚了。

如果这一位加入的字符为 $a_i$，上一次 $a_i$ 出现的位置为 $lst_{a_i}$。

令 $f_i$ 表示前 $i$ 位构成的串中不同的字串数目。

对于前面的每种字串，依然存在。同时，在它们的尾部加上一个 $a_i$ 又是一个新的字串。

但是，以 $lst_{a_i}$ 位置结尾的字串与 $i$ 位置结尾的字串是相同的，应当减去。

所以方程为：

$$f_i=\min{f_{i-1}\times 2-f_{lst_{a_i}}}$$

其中，若 $a_i$ 是固定的则直接出答案，否则我们需要选择。

那么显然，我们让 $lst_{a_i}$ 最小，一定最优。

我们可以用一个小根堆来维护 $lst$，小根堆内的元素数量一定是 $k$。

复杂度 $\operatorname{O}(m+n\log k)$。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline long long read(){
	register long long x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register long long x,register char k='\n') {
    if(!x) putchar('0');
    if(x < 0) putchar('-'),x=-x;
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
const int maxn=2000050;
const int p=1e9+7;
char s[maxn];
int n,k,f[maxn],m,lst[maxn];
priority_queue<pair<int,int>> q;
signed main() {
    n=read(),k=read();
    gets(s+1);
    m=strlen(s+1);
    for(int i=1;i<=m;i++) {
        if(!lst[s[i]]){
            f[i]=(f[i-1]*2+1)%p;
        }
		else{
            f[i]=(f[i-1]*2-f[lst[s[i]]-1])%p+p;
            f[i]%=p;
        }
        lst[s[i]]=i;
    }
    for(char i='a';i<'a'+k;i++){
    	q.push(make_pair(-lst[i],i));
	}
    for(int i=1;i<=n;i++){
        int mn=-q.top().first;
        int pos=q.top().second;
        q.pop();
        int now=i+m;
        if(mn==0){
            f[now]=(f[now-1]*2+1)%p;
        }
		else{
            f[now]=(f[now-1]*2-f[mn-1])%p+p;
            f[now]%=p;
        }
        lst[pos]=now;
        q.push(make_pair(-now,pos));
    }
    int ans=f[n+m]+1;
    print((ans%p+p)%p);
}
```


---

## 作者：洁咪 (赞：1)

**[更好的阅读体验](https://www.luogu.com.cn/blog/shaymin5216/solution-cf645e)**

**题意**：

一个长为 $n+m$，字符集大小为 $k$ 的字符串，前 $n$ 位已经填好，后 $m$ 位自己填。求填完后不同的子序列个数最多为多少，答案对 $10^9+7$ 取模。  
（$n,m\le10^6$，$k\le26$）


------------
$\texttt{Solution}$：

有两种考虑 DP 的方向。

1. 记 $lst[a_i]$ 表示 $a_i$ 这个字符上一次的出现位置。  
	设 $f_i$ 表示**以字符串的第 $i$ 位为结尾，且在前面没有出现过的子序列有几个**。考虑转移： 
    
	若 $a_i$ 在前面没出现过，则 $f_i=1+\sum_{j=1}^{i-1}f_j$（前面的所有子序列后加个 $a_i$，以及 $a_i$ 本身都是新的）。  
    若 $a_i$ 在前面出现过，则 $f_i=\sum_{j=lst[a_i]}^{i-1} f_j$（$lst[a_i]$ 之前的子序列后面再加个 $a_i$ 已在 $f_{lst[a_i]}$ 处统计过了）。  
    
    观察上述两个式子，发现 $lst[a_i]$ 越小能加上的值就越多。  
    于是填后 $m$ 位的时候每次只要填入 $lst[a_i]$ 最小的 $a_i$ 就好。又因为每次填入 $a_i$ 就会让 $lst[a_i]$ 变成最大值，所以对 $lst$ 排完序后只要顺序循环使用就好。  
    最终答案为 $ans=1+\sum_{i=1}^{n+m}f_i$（$+1$ 是统计空序列）。  
    使用前缀和优化，时间复杂度 $O(n+m)$。
    
$\texttt{Code}$：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+5,mod=1e9+7;
int read() {
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();}
    return x*f; 
}
 
int n,m,k,a[N];
char ch[N];
int lst[N],f[N],sum[N],id[N];

bool cmp(int i,int j) {return lst[i]<lst[j];}
int main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    m=read(); k=read();
    scanf("%s",ch+1); n=strlen(ch+1);
    for(int i=1; i<=n; i++) a[i]=ch[i]-'a'+1;

    for(int i=1; i<=n; i++) {
        if(!lst[a[i]]) f[i]=(sum[i-1]+1)%mod;
        else f[i]=(sum[i-1]-sum[lst[a[i]]-1]+mod)%mod;

        lst[a[i]]=i; sum[i]=(sum[i-1]+f[i])%mod;
    }

    for(int i=1; i<=k; i++) id[i]=i;
    sort(id+1,id+1+k,cmp);
    for(int i=n+1,j=1; i<=n+m; i++,j++) {
        if(j>k) j=1;
        a[i]=id[j];// 贪心选取
        if(!lst[a[i]]) f[i]=(sum[i-1]+1)%mod;
        else f[i]=(sum[i-1]-sum[lst[a[i]]-1]+mod)%mod;

        lst[a[i]]=i; sum[i]=(sum[i-1]+f[i])%mod;
    }

    printf("%d\n",(sum[n+m]+1)%mod);// +1 是有空序列的存在

    return 0;
}

```


------------
2. 设 $f_i$ 表示**当前以字符 $i$ 结尾的子序列个数**。  
	若当前位的字符是 $x$，那么有：$f_x=1+\sum_{i=1}^k f_i$（即前面所有子序列加上字符 $x$，以及字符 $x$ 本身）。  
    发现无论当前位是什么，新的 $f_x$ 都是一样的。由于要最大化答案 $1+\sum_{i=1}^k f_i$，那么原本的 $f_x$ 要越小越好。  
    于是在填后 $m$ 位的时候，每次填入当前 $f_x$ 最小的 $x$，具体处理同方法 $1$。  
    时间复杂度 $O(n+m)$。

$\texttt{Code}$：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,mod=1e9+7;
int read() {
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();}
    return x*f; 
}
 
char ch[N];
int n,m,k,a[N];
int sum,sve,f[N],id[N];

bool cmp(int i,int j) {return f[i]<f[j];}
int main() {
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    m=read(); k=read();
    scanf("%s",ch+1); n=strlen(ch+1);
    for(int i=1; i<=n; i++) a[i]=ch[i]-'a'+1;

    for(int i=1; i<=n; i++) {
        sve=f[a[i]];
        f[a[i]]=(sum+1)%mod;
        sum=(sum-sve+f[a[i]]+mod)%mod;
    }

    for(int i=1; i<=k; i++) id[i]=i;
    sort(id+1,id+1+k,cmp);
    for(int i=n+1,j=1; i<=n+m; i++,j++) {
        if(j>k) j=1;
        a[i]=id[j];

        sve=f[a[i]];
        f[a[i]]=(sum+1)%mod;
        sum=(sum-sve+f[a[i]]+mod)%mod;
    }

    printf("%d\n",(sum+1)%mod);

    return 0;
}

```


------------
**后话**：若 $m$ 值增至 $10^{18}$，因为上述两种方法填后 $m$ 位的方式都是不断地填一个 $k$ 的排列，故均能用矩阵快速幂优化至 $O(n+k^3\log m)$。

---

## 作者：hhhqx (赞：0)

走路题，第一步显然是想：如何统计不同子序列数量。

- 考虑 dp。设 $f_{i}$ 表示前 $i$ 个字符有多少不同子序列。如果直接 $f_i = 2 \times f_{i-1}$，会算重复，考虑哪里会算重复？
	- 当前字符是 $c$，则前面所有以 $c$ 结尾的的子序列都会重算一遍。
- 设 $g_{c}$ 表示字符 $c$ 结尾的不同子序列数量。设当前字符是 $c$，则 $g_c = \sum\limits_{i=0}^{k-1}{g_c}$。
- 但是这个转移式子忽略了空串的情况，所以应该是添加 $g_k$ 表示空串结尾的数量。
- $g_k$ 初始值设为 $1$，然后 $g_c = \sum\limits_{i=0}^{k}{g_c}$（$c$ 不能等于 $k$） 推下去就可以了。

观察这个转移，如果可以选则 $c$，则每次选最小的 $g_c$ 去转移最优。

还发现每经过一次转移 $g_c$ 又会变为最大值。

然后就可以直接做了。

考虑离散化，每次转移 $g_c$，只需要把 $g_c$ 的离散值设为当前离散值中最大的就可以了。

具体实现可以看代码，应该还是很好懂的。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const int MAXN = 3e6 + 3;
const int mod = 1e9 + 7;

int n, m, k, dp[27];
string s;
int tot = 0, mp[MAXN], w[27];
set<int> st;

void ADD(int &x, int y){ x = (x + y) % mod; }

void Update(int i, int c){
	for(int j = 0; j <= k; j++){
		if(j != c) ADD(dp[c], dp[j]); 
	}
	st.erase(w[c]);
	tot++, mp[tot] = c, w[c] = tot;
	st.insert(tot);
}

int main(){
	cin >> n >> k >> s, m = s.size(), s = " " + s;
	tot = k;
	for(int i = 0; i < k; i++) st.insert(i), mp[i] = i, w[i] = i;
  dp[k] = 1;
	for(int i = 1; i <= m; i++){ int c = s[i] - 'a';
		Update(i, c);
	}
	for(int i = m + 1; i <= m + n; i++){
		int c = mp[*st.begin()];
		Update(i, c);
	}
	int ans = 0;
	for(int j = 0; j <= k; j++) ADD(ans, dp[j]);
	cout << ans;
	return 0;
}
```

---

## 作者：minxu (赞：0)

[题目](https://www.luogu.com.cn/problem/CF645E)

可以将$f[0]$初始化为$1$即代表空集也算一 这样直接就是答案了
转移的话就变为
$f[i]=\begin{cases}
 f[i-1]*2&las[s[i]]=0  \\
f[i-1]*2-f[las[s[i]]-1]&las[s[i]]!=0 \\ 
\end{cases}$

即如果没有出现过 就是当前接不接在之前的上 就是两倍的

如果之前的有过 也是接或不接 当时如果$f[las[s[i]]]=f[las[s[i]]-1]*2$时有的没接 现在接了就重复了 所以要减去一次$f[las[s[i]]-1]$

剩下就是贪心的选减的最小的

最后直接输出$f[n+len]$即可 

要注意减法取模可能出负数
以及堆且重载运算符的话小根堆要改$>$
```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 10000;
const int mod = 1e9 + 7;
int n, m, k;
char s[N];
int las[N];
int f[N];
struct node
{
    int las;
    int id;
    friend bool operator<(node x, node y) { return x.las > y.las; }
};
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
priority_queue<node> q;
signed main()
{
    n = read(), k = read();
    cin >> (s + 1);
    int len = strlen(s + 1);
    f[0] = 1;
    for (int i = 1; i <= len; ++i)
    {
        int c = s[i];
        if (las[c] == 0)
        {
            f[i] = (f[i - 1] * 2) % mod;
            las[c] = i;
        }
        else
            f[i] = (f[i - 1] * 2 - f[las[c] - 1]) % mod, las[c] = i;
    }
    //char ch = 'a';
    //int x = 0 + s[1] - '0';
    // cout << x << endl;
    for (char i = 'a'; i < 'a' + k; ++i)
        q.push((node){las[i], i});
    for (int i = 1; i <= n; ++i)
    {
        node p = q.top();
        q.pop();
        int c = p.las;
        char d = p.id;
        if (las[d] == 0)
            f[i + len] = f[i + len - 1] * 2 % mod;
        else
        {
            f[i + len] = (f[i + len - 1] * 2 - f[c - 1]) % mod;
        }
        las[d] = i + len;
        q.push((node){las[d], d});
    }
    printf("%lld\n", (f[len + n] + mod) % mod);
    return 0;
}
```


---

## 作者：SuperTNT (赞：0)

# CF645E 题解

## 思路

 参考了$Liao$_$rl$  大佬的题解

$dp$ 题

先不考虑空集

* 设 $dp[i]$ 表示到这个位置，不同子序列的个数
* 当该位置字母没有出现过时，相当于在之前答案的每个位置都加上了一个新的字符，因此答案翻了 $1$ 倍，但还有当前新字母没有统计到答案里，因此答案还要 $+1$ 。 每个  $dp$  转移方程有  $dp[i]=2\times dp[i - 1] + 1$ 
* 若之前出现过就减去以前出现过的最靠近现在位置的字母的贡献，因为有一部分答案是之前已经统计过的，因此要减去重复的，且该字符已经出现过，不用再 $+1$。转移为 $dp[i] = 2\times dp[i - 1] - dp[last[k] - 1]$ ， $k$ 表示当前位置所选的字符
* $dp$ 转移已经有了，我们思考如何才能让答案最大，因为 $dp$ 是单调上升的，而且对答案有影响的只有第二个转移减去的 $dp[last[k]-1]$ ，因此我们要让 $dp[last[k]-1]$ 最小，只要让该字符 $k$ 出现位置最早即可 
* 最后不要忘了加上空集的答案
* 时间复杂度为 $O(26N)$

## 代码

```c++
#include <bits/stdc++.h>

#define re register

typedef long long ll;

namespace TNT
{
    const int MAXN = 2e6 + 10;
    const int mod = 1e9 + 7;

    int read()
    {
        int x = 0, f = 1;
        char ch = getchar();

        while (ch < '0' || ch > '9')
        {
            if (ch == '-')
                f = -1;
            ch = getchar();
        }

        while (ch >= '0' && ch <= '9')
        {
            x = (x << 3) + (x << 1) + (ch ^ 48);
            ch = getchar();
        }

        return x * f;
    }

    void write(int x)
    {
        if (x < 0)
            putchar('-'), x = -x;
        if (x > 9)
            write(x / 10);

        putchar(x % 10 + '0');
    }

    int last[30], dp[MAXN];

    inline void main()
    {
        int n = read(), k = read(), m = 0;
        char ch;

        while ((ch = getchar()) != '\n')
        {
            ++m;
            if (!last[ch - 'a'])
                dp[m] = 1ll * (2ll * dp[m - 1] % mod + 1) % mod;
            else
                dp[m] = 1ll * (2ll * dp[m - 1] % mod - dp[last[ch - 'a'] - 1] + mod) % mod;

            last[ch - 'a'] = m;
        }

        for (re int i = 1; i <= n; i++)
        {
            int minpos = 2e6 + 5, minletter = -1;

            for (re int j = 0; j < k; j++)
                if (last[j] < minpos)
                    minletter = j, minpos = last[j];

            int now = i + m;

            if (!minpos)
                dp[now] = 1ll * (2ll * dp[now - 1] % mod + 1) % mod;
            else
                dp[now] = 1ll * (2ll * dp[now - 1] % mod - dp[minpos - 1] + mod) % mod;

            last[minletter] = now;
        }

        write((dp[n + m] + 1 % mod + mod) % mod);

        return;
    }
} // namespace TNT

int main()
{
    TNT::main();
    return 0;
}
```



---

## 作者：DarkMoon_Dragon (赞：0)

# CF645E Intellectual Inquiry
+ *2100 的 简单 $Greedy$

## $Description$
+ 给定一个长度为 $m$ 的字符串（$lowercase$ $letters$），你可以在字符串后再添加 $n$ 个字符，使得新字符串所包含的不同的子序列数量尽量多。求最多的不同子序列数量，答案模大质数。
+ $n + m\leq 10^6$

## $Solution$
+ 考虑子序列 $dp$ 的套路
+ 令 $f[i]$表示到当前这个位置为止，但不一定要选当前位置，不同的子序列个数。
+ 那么转移分两种情况
    1. 当前字符未出现过（第一个出现）。那么可行方案有原来的 $f[i-1]$，以及和前面所有可行子序列新形成的 $f[i-1]$ ，还有当前字符本身。     
    转移方程 $f[i]=2*f[i-1]+1$
    2. 相同字符会被重复计算，应减去上次以这个字符结尾的贡献，并且最后不加以一了。注意这里结尾的贡献是上一位，所以应该是 $last[s[i]-1]$ 。取模的时候加上模数，可能出现负数。     
    转移方程 $f[i]=2*f[i-1]-f[last[s[i]-1]$ 
+ 子序列 $dp$ 值显然是单调增加的
+ 发现重复出现时会减上次出现的 $dp$ 值
+ 所以每次结尾加上 $last_i$ 最小的字符，这样减得最小，使得 $f_i$ 最大
+ 贪心得证，时间复杂度 $\mathcal{O}(n\times26)$
+ 还有这道题特别容易乘爆 QAQ

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return f * res;
}
const int N = 2000050;
const ll mod = 1e9 + 7;
char s[N];
int n, k;
// first time dp[i] = 2 * dp[i - 1] + 1
// re  dp[i] = 2 * dp[i - 1] - dp[las[i] - 1] 
int len;
int las[N], f;
ll dp[N];
int main() {
    n = read(), k = read();
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (rr i = 1; i <= len; ++i) {
        if (!las[s[i] - 'a']) {
            dp[i] = dp[i - 1] * 2ll + 1;
            dp[i] %= mod;
        } else {
            dp[i] = dp[i - 1] * 2ll + mod;
            dp[i] -= dp[las[s[i] - 'a'] - 1];
            dp[i] %= mod;
        }
        las[s[i] -'a'] = i;
    }
    // cout << dp[len] << endl;
    for (rr i = 1; i <= n; ++i) {
        int minn = 1e9, minpos = -1;
        for (rr j = 0; j < k; ++j) {
            if (las[j] < minn) {
                minpos = j;
                minn = las[j];
            }
        }
        int now = i + len;
        if (minn == 0) {
            dp[now] = dp[now - 1] + dp[now - 1] + 1;
            dp[now] %= mod;
        } else {
            dp[now] = dp[now - 1] + dp[now - 1];
            dp[now] %= mod;
            dp[now] += mod;
            dp[now] -= dp[las[minpos] - 1];
            dp[now] %= mod;
        }
        las[minpos] = now;
    }
    //注意这里加一也要取模！！！ 最好新定义ans
    ll ans = dp[n + len] + 1;
    ans += mod;
    ans %= mod;
    cout << ans % mod << endl;
}
```

---

