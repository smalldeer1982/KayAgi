# Sonya and Matrix Beauty

## 题目描述

一句话题意：给定一个 $n \times m$ 的字符矩阵，请求出有多少个子矩阵在重排子矩阵每一行的字符后，使得子矩阵的每行每列都是回文串。

Sonya 最近过了生日，她收到一个 $n \times m$ 的字符矩阵。

我们称一个子矩阵是美丽的，当且仅当在重新排列这个子矩阵每一行的字符后，使得这个子矩阵的每一行每一列都是回文串。

Sonya 想要知道这个矩阵中有几个子矩阵是美丽的。

## 说明/提示

对于 $1 \leq m,n \leq 250$

## 样例 #1

### 输入

```
1 3
aba
```

### 输出

```
4```

## 样例 #2

### 输入

```
2 3
aca
aac
```

### 输出

```
11```

## 样例 #3

### 输入

```
3 5
accac
aaaba
cccaa
```

### 输出

```
43```

# 题解

## 作者：EricWan (赞：8)

本题数据范围较小，考虑三次方做法。

下令 $a_{i,j}$ 为矩阵第 $i$ 行 $j$ 列的字母。

众所周知，关于回文串的问题，多半是要用到马拉车，额，可是这是二维，我们怎样转化为一维的马拉车呢？这时，我们发现我们有很多时间可以 “使用”，于是想到了**暴力枚举左界 $l$ 和右界 $r$**，之后对于 $1\le i\le n$ 判断 $a_{i,(l...r)}$ 是不是回文串。如果是，将 $a_{i,(l...r)}$ 映射为一个哈希值（注意，这里映射的哈希值不考虑字母顺序，**能且仅能体现每一个字母的数量**即可），参与后续的马拉车；否则，将其设为一个负数，使其在参与后续马拉车时，不参与到回文中心不是它自己的任何回文串即可。最后，各位大佬按自己定义的马拉车答案状态计算题目最终答案即可。

贴一下本人 AC 代码的主要部分：

`box[i][j]` 代表 $\big((i,l),(i,r)\big)$ 中字母 `'a' + j - 1` 出现的次数；

`ji[i]` 代表 $\big((i,l),(i,r)\big)$ 中出现奇数次的字母数量；

`h[i]` 代表 $\big((i,l),(i,r)\big)$ 对应的哈希值；

`mnc[i]` 代表需要进行马拉车的序列；

`len[i]` 代表马拉车之星结束后的结果；

`ans` 为最终答案。

```cpp
	for (int l = 1; l <= m; l++) {
		memset(box,0,sizeof(box));
		memset(ji,0,sizeof(ji));
		memset(h,0,sizeof(h));
		for (int r = l; r <= m; r++) {
			for (int i = 1; i <= n; i++) {
				box[i][a[i][r]]++;
				if (box[i][a[i][r]] % 2 == 1) ji[i]++;
				else ji[i]--;
				h[i] += quik_power(1000,a[i][r] - 1);
			}
			memset(mnc,0,sizeof(mnc));
			memset(len,0,sizeof(len));
			for (int i = 1; i <= n; i++) {
				if (ji[i] < 2) mnc[i * 2] = h[i];
				else mnc[i * 2] = -i;
			}
			manacher(n * 2 + 1);
			for (int i = 1; i <= n * 2 + 1; i++)
				if (mnc[i] >= 0)
					ans += (len[i]) / 2;
		}
	}
```
码风太丑，于是进行了轻微压行。

个人认为这是个很好的题目，很考验大家的思维水平，使用的马拉车算法也十分巧妙，细节不多，但有很多需要优化的点。

↓ 既然都看完了，点个赞再走呗！

---

## 作者：辰星凌 (赞：3)

# **【题解】Sonya and Matrix Beauty Codeforces1080E**

**传送门：[$Sonya$ $and$ $Matrix$ $Beauty$ $pairs$](https://www.luogu.org/problem/CF1080E) [$[CF1080E]$](http://codeforces.com/problemset/problem/1080/E)**

## **【题目描述】**

$Sonya$ 最近过了生日，她收到一个 $n \times m$ 的字符矩阵。

我们称一个子矩阵是美丽的，当且仅当在重新排列这个子矩阵每一行的字符后，使得这个子矩阵的每一行每一列都是回文串。

$Sonya$ 想要知道这个矩阵中有几个子矩阵是美丽的。

（给定一个 $n \times m$ 的字符矩阵，求有多少个子矩阵在任意排列每一行内的字符后，使得子矩阵的每行每列都是回文串）

**【样例】**

```cpp
样例输入：
1 3
aba
样例输出：
4

样例输入：
2 3
aca
aac
样例输出：
11

样例输入：
3 5
accac
aaaba
cccaa
样例输出：
43
```

**【数据范围】**

$100\%$ $1 \leqslant n,m \leqslant 250$

-------

## **【分析】**

先膜一膜 [隔壁大佬](https://www.luogu.org/blog/da-ju-ruo-pb/solution-cf1080e) $Hash$ 判回文的方法，一脸懵逼的本蒟蒻只能另找出路了。。。

由于每一行的以内的字符可以任意排列，子矩阵中的某一行字符可以形成回文串，当且仅当该行中出现次数为奇数的字符只有一个。

如果让每一列都形成回文串的话，那么关于中心行对称的任意两行都应是完全相同的，否则就无法做到每一列都一样。

将子矩阵每一行视为一个字符，比较两个字符（行）是否相等时就看其 $26$ 个字母的个数是否全部相同，对于内部本身无法形成回文的字符（行）就不让它与其他的匹配。
枚举一下子矩阵的左右边界，然后处理出 $26$ 个字母在子矩阵每一行中分别出现的次数，然后对这 $n$ 个字符（行）跑一遍 $Manacher$ 得到上下边界，最后答案取个最大值就 $ok$ 啦！

时间复杂度：$O(nm^2)$ 。

## **【Code】**

```cpp
#include<cstdio>
#define Re register int
const int N=510;
int n,m,a,p,q,Ans,f[N],odd[N],cnt[N][30];char ch[N][N];
inline int min(Re a,Re b){return a<b?a:b;}
inline bool cmp(Re a,Re b){
    if(odd[a]>1||odd[b]>1)return 0;//本身不能形成回文的统统踢掉
    for(Re i=0;i<26;++i)if(cnt[a][i]!=cnt[b][i])return 0;
    return 1;
}
int main(){
    scanf("%d%d",&n,&m);
    for(Re i=1;i<=n;++i)scanf("%s",ch[i]+1);
    for(Re L=1;L<=m;++L){
    	for(Re i=0;i<=n;odd[2*i-1]=0,++i)
            for(Re j=0;j<26;++j)
            	cnt[2*i-1][j]=0;//初始化
    	for(Re R=L;R<=m;++R){
            for(Re i=1;i<=n;++i){//右边界从前往后扫，每次都只需要处理n个新加进来的字符
            	++cnt[2*i-1][a=ch[i][R]-'a'];
            	if(cnt[2*i-1][a]&1)++odd[2*i-1];
            	else --odd[2*i-1];
            }
            for(Re i=0;i<=2*n;++i)f[i]=0;//回文半径的初始化
            cnt[2*n+1][0]=-1;//防止多余的部分被匹配
            p=q=0;
            for(Re i=1;i<=2*n;++i){
                if(odd[i]>1)continue;//自身都不符合要求，还想找配偶？没门！
            	f[i]=q>i?min(f[(p<<1)-i],q-i):1;
            	while(cmp(i-f[i],i+f[i])==1)++f[i];
            	if(i+f[i]>q)q=(p=i)+f[i];
            	Ans+=f[i]/2;//因为之前在字符（行）序列中加入了空位置，所以统计答案时要除2
            }
    	}
    }
    printf("%d",Ans);
}
```



---

## 作者：Arghariza (赞：1)

考虑枚举答案矩形的 $j_1$ 和 $j_2$，只需要考虑所有行的 $S_i[j_1,j_2]$ 子串，于是只用统计满足 $[i_1,i_2]$ 之间所有子串每个重排后都是回文串，并且重排后子串排列回文的区间 $[i_1,i_2]$ 的个数。

首先判定一个子串重排后是回文串是容易的，相当于只有至多一个出现次数为奇数的字符，把字符集每个字符压成 $2^0,2^1,\cdots,2^{26}$ 之后前缀异或判定即可。

考虑如何判定一个重排后子串的序列回文。当且仅当第 $i$ 行和第 $i_2-i_1+i$ 行的两个子串每个字符个数完全相同，于是想到每行开一个字符集大小的桶，表示这行的子串每个字符有多少个，对每个桶序列进行哈希。于是变成数回文子串，manacher 即可。复杂度 $O(nm^2)$。

注意到有些行的子串是不合法（不能构成回文）的，这些不合法的行将 $1$ 到 $n$ 分成若干合法连续段，在每个连续段里跑 manacher。

吐槽：如果用自然溢出哈希的话，由于 manacher 需要在字符串首尾插入一个不在字符集（这里是 `unsigned long long` 的范围）中的元素，一开始这两个元素我取了 $114514$ 和 $1919810$，结果 WA on test 73 了，改成 $1145141919810$ 和 $1919810114514$ 就过了，这么连这东西都卡啊……

```cpp
// Problem: Sonya and Matrix Beauty
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1080E
// Memory Limit: 250 MB
// Time Limit: 1500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define pb pop_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int N = 300;
const ull B = 31;

int n, m, res, len, a[N][N], vl[N][N], ct[N][30], p[N << 1];
ull h[N], th[N], pw[N], c[N << 1];
char s[N];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> (s + 1);
		for (int j = 1; j <= m; j++) {
			a[i][j] = s[j] - 'a' + 1;
			vl[i][j] = (1 << (a[i][j] - 1)) ^ vl[i][j - 1];
		}
	}
	pw[0] = 1;
	for (int i = 1; i <= 26; i++) pw[i] = pw[i - 1] * B;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) th[j] = 0;
		for (int j = 1; j <= n; j++) 
			for (int k = 1; k <= 26; k++)
				ct[j][k] = 0;
		for (int j = i; j <= m; j++) {
			for (int k = 1; k <= n; k++) {
				th[k] -= ct[k][a[k][j]] * pw[a[k][j]];
				ct[k][a[k][j]]++;
				th[k] += ct[k][a[k][j]] * pw[a[k][j]];
				if (__builtin_popcount(vl[k][j] ^ vl[k][i - 1]) > 1) h[k] = 0;
				else h[k] = th[k];
			}
			for (int l = 1; l <= n; l++) {
				if (!h[l]) continue;
				int r = l;
				while (r < n && h[r + 1]) r++;
				c[len = 1] = 1145141919810, c[++len] = 0;
				for (int k = l; k <= r; k++)
					c[++len] = h[k], c[++len] = 0;
				c[++len] = 1919810114514;
				for (int k = 1; k <= len; k++) p[k] = 0;
				int mid = 0, mr = 0;
				for (int k = 2; k < len; k++) {
					if (k <= mr) p[k] = min(mr - k + 1, p[2 * mid - k]);
					else p[k] = 1;
					while (c[k - p[k]] == c[k + p[k]]) p[k]++;
					if (k + p[k] > mr) mr = k + p[k] - 1, mid = k;
				}
				for (int k = 2; k < len; k++) res += p[k] / 2;
				l = r;
			}
		}
	}
	cout << res << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：chenxia25 (赞：1)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF1080E) & [CodeForces题目页面传送门](https://codeforces.com/contest/1080/problem/E)

>若一个矩阵满足存在一种重新排列每行的方案，使得排列之后的每行每列都是回文串，那么称它是美丽的。给定一个$n\times m$的字符矩阵$a$，求有多少个美丽子矩阵。

>$n,m\in[1,250],|\Sigma|\in[1,26]$。

考虑探索一个矩阵美丽的充要条件。

某行能够重排之后变成回文串，显然当且仅当这行出现次数为奇数的字符的数量$\leq1$。充分性和必要性都很显然。

接下来考虑每列都回文的充要条件。显然，重排每行之后能够每列都回文，当且仅当重排之后能够从上到下每行的字符串组成的字符串序列回文，显然又等价于从上到下每行的字符多重集组成的多重集序列回文。这个字符多重集可以用一个$|\Sigma|$元组表示，第$i$个元素表示第$i$种字符出现的次数。

这样一来，我们显然可以枚举子矩阵的起始列、终止列，就转化成了$\mathrm O\!\left(m^2\right)$个回文子串计数问题。对于每一次枚举，我们算出每一行的表示字符多重集的$|\Sigma|$元组，然后跑[Manacher](https://www.cnblogs.com/ycx-akioi/p/Manacher-algorithm.html)即可。

然鹅这一次Manacher与正常的稍有不同。对于每一次枚举，因为有可能有的行不满足“这行出现次数为奇数的字符的数量$\leq1$”，它内部不能组成回文串，所以要跑Manacher的字符串中会有**不可匹配**的“字符”（$|\Sigma|$元组）出现。这怎么办呢？不妨定义一个新的可匹配函数$eq:eq(x,y)=[x=y\land odd_x\leq1\land odd_y\leq 1]$，其中$odd_x$表示字符多重集$x$中出现次数为奇数的字符数量。这样，$eq$显然不满足自反性，但是满足传递性。注意：Manacher算法不需要自反性，只需要传递性。所以Manacher可以照常跑。

至于$|\Sigma|$元组们和$odd$数组如何快速求出，枚举过程中递推即可。

时间复杂度$\mathrm O\!\left(nm^2|\Sigma|\right)$。可能会被卡常哟！怎么做到保证不被卡常呢？可以用集合哈希去哈希$|\Sigma|$元组，使得判断$2$个$|\Sigma|$元组相等只需$\mathrm O(1)$，并且哈希值也可以递推。这样时间复杂度是$\mathrm O\!\left(nm^2\right)$的。不过本蒟蒻没有被卡常，就不写哈希了吧！

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=250,M=250,LET=26;
int n/*行数*/,m/*列数*/;
char a[N+1][M+5];//字符矩阵 
vector<int> cnt[N+1];//|Σ|元组 
int odd[N+1];//odd[i]表示cnt[i]中奇数的数量 
int s;//|b|
vector<int> b[2*N+2];//塞上分隔符之后的|Σ|元组序列 
bool ok[2*N+2];//ok[i]表示b[i]能否行内回文 
void sep(){//塞分隔符（分隔符是vector<int>(LET,0)） 
	b[s=1]=vector<int>(LET,0);ok[s]=true;//分隔符自然可匹配 
	for(int i=1;i<=n;i++)b[++s]=cnt[i],ok[s]=odd[i]<=1,b[++s]=vector<int>(LET,0),ok[s]=true;
}
bool eq(int x,int y){return ok[x]&&ok[y]&&b[x]==b[y];}//可匹配函数 
int rds[2*N+2];//最长回文半径数组 
void manacher(){//对b跑Manacher算法 
	int mid=0,r=0;
	for(int i=1;i<=s;i++)
		if(r<i){
			rds[i]=0;
			while(i-rds[i]>=1&&i+rds[i]<=s&&eq(i-rds[i],i+rds[i])/*调用可匹配函数*/)rds[i]++;
			mid=i;r=i+rds[i]-1;
		}
		else if(i+rds[2*mid-i]<=r)rds[i]=rds[2*mid-i];
		else{
			rds[i]=r-i+1;
			while(i-rds[i]>=1&&i+rds[i]<=s&&eq(i-rds[i],i+rds[i])/*调用可匹配函数*/)rds[i]++;
			mid=i;r=i+rds[i]-1;
		}
}
signed main(){
//	freopen("C:\\Users\\chenx\\OneDrive\\桌面\\data.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	for(int i=1;i<=n;i++)cnt[i].resize(LET);
	int ans=0;
	for(int i=1;i<=m;i++){//枚举起始列 
		for(int j=1;j<=n;j++){//新一轮递推，清空数据 
			for(int k=0;k<LET;k++)cnt[j][k]=0;
			odd[j]=0;
		} 
		for(int j=i;j<=m;j++){//枚举终止列 
			for(int k=1;k<=n;k++)odd[k]+=++cnt[k][a[k][j]-'a']&1?1:-1;//递推求odd,cnt 
			sep();//塞分隔符 
			manacher();//对b跑Manacher 
			for(int k=1;k<=2*n+1;k++)ans+=rds[k]>>1;//贡献答案 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：p_b_p_b (赞：1)

## 前言

这场比赛由于~~午觉睡过头~~忘记了，于是怕掉rating，没有参加，只敢在场外BB。

结果被大佬喷了……

但最后看标程时发现我的思路其实基本正确，只是没有代码实现而已。

## 正文

### 思路

这题看到横排可以打乱，于是想到计数数组。但列上的顺序不能打乱，稍微麻烦一点。

思考后可以得到，对于一个美丽的矩形，每一排字符数量为奇数的字符数不大于1，而且每一排的计数数组哈希之后恰好可以组成回文串

（可能叙述不太清晰，具体看代码）

### 做法

首先暴力枚举横排的左右端点，将每一排的这一段的计数数组哈希一下，顺便判一下能否组成回文串，然后对这些哈希值跑$manacher$，最后$ans+= \sum (int)\frac{len[i]}{2}$即可

（还是好混乱啊。。。）

### 代码

```cpp
#include<bits/stdc++.h>
#define sz 666
using namespace std;
typedef long long ll;
int cnt[sz][sz][26];
char a[sz][sz];
int t[sz][sz];
int n,m;
#define pll pair<ll,ll>
#define MP make_pair
#define fir first
#define sec second
const ll M1=19260817,M2=998244353;
pll Minus (const pll &x,const pll &y){return MP((x.fir-y.fir+M1)%M1,(x.sec-y.sec+M2)%M2);}
pll H[sz][sz];
pll Hash(int *x)
{
    pll ret;
    ret.fir=ret.sec=0;
    for (int i=0;i<26;i++) (ret.fir=ret.fir*(m+1)+x[i])%=M1,(ret.sec=ret.sec*(m+1)+x[i])%=M2;
    return ret;
}
bool check(int i,int l,int r)
{int x=t[i][l-1]^t[i][r];return (!x)||(!(x-(x&(-x))));}//利用状态压缩快速判定能否组成回文串 
pll s[sz];
int len[sz];
ll ans;
void manacher()
{
    int mid=0,R=0;
    for (int i=1;i<=n*2;i++) if (s[i].fir>=0)//特判不能组成回文串 
    {
        len[i]=1;
        if (R>=i) len[i]=min(len[mid*2-i],R-i+1);
        while (len[i]<i&&s[i+len[i]]==s[i-len[i]]) ++len[i];
        ans+=len[i]/2;
        if (i+len[i]-1>R) R=i+len[i]-1,mid=i;
    }
}
int main()
{
    int i,j,k;
    cin>>n>>m;
    for (i=1;i<=n;i++) 
    {
        cin>>((a[i])+1); 
        for (j=1;j<=m;j++) 
        { 
            for (k=0;k<26;k++) cnt[i][j][k]=cnt[i][j-1][k];
            cnt[i][j][a[i][j]-'a']++;
            H[i][j]=Hash(cnt[i][j]);//对计数数组哈希 
            t[i][j]=t[i][j-1]^(1<<(a[i][j]-1));//状态压缩 
        } 
    }
    for (i=1;i<=m;i++) for (j=i;j<=m;j++) 
    { 
        for (k=1;k<=n;k++) 
        {
			s[k*2-1]=MP(0,0);
			if (check(k,i,j)) s[k*2]=Minus(H[k][j],H[k][i-1]);//求这一段的hash值 
			else s[k*2]=MP(-1ll*k,-1ll*k);//对于不能重组为回文串的部分赋一个奇怪的负值 
        } 
        manacher(); 
    }
    cout<<ans;
    return 0;//goodbye~
}

```


---

## 作者：int_R (赞：0)

[CF1080E Sonya and Matrix Beauty](https://www.luogu.com.cn/problem/CF1080E)

求出有多少个子矩阵在重排子矩阵每一行的字符后，使得子矩阵的每行每列都是回文串。

相当于将每一行的每个字串重排为回文串后，将每个子串看做一个整体，看能否组成回文。

先考虑每一行字符串的每个子串能否重排为回文串，一个显而易见的结论是：能重排为回文串等价于出现次数为奇数的字符小于等于一个。

那我们可以枚举左端点，扫描右端点，将 $m^2$ 个子串能否重排为回文串都处理出来。共 $n$ 个字符串，时间复杂度 $O(nm^2)$。

```cpp
    for(register int k=1;k<=n;++k)
        for(register int i=1;i<=m;++i)
        {
            int cur=0;//出现次数为单数的字符个数
            for(register int j=i;j<=m;++j)
            {
                ++cnt[c[k][j]];// 每个字符出现次数
                (cnt[c[k][j]]&1)?++cur:--cur;
                if(cur<=1) b[k][i][j]=true;
            }
            for(register int j=i;j<=m;++j) --cnt[c[k][j]];
        }
```

然后我们枚举所有子矩阵的左边界和右边界 $i,j$，也就是将每个字符串的 $S_k[i,j]$ 截取出来。对于一段连续的满足 $S_k[i,j]$ 合法的行，我们对每行的子串做一个哈希映射，抽象出来一个整数序列，再求这个整数序列有多少个回文串即可。

因为枚举左右边界是 $O(m^2)$，所以要求使用 $O(n)$ 判断回文串个数的算法，manacher 即可。细节代码可见。

再说如何进行映射，因为子串可以重排，所以不是普通的哈希，我们不在乎每个字符的出现顺序，只在乎出现了多少次，可以加法哈希实现。但我没写加法哈希，别人写了一个用了一个种子 CF 上还 WA 了。我选择对每个数分配一个质数，然后对于每个字符对应的质数求积，然后双模哈希，正确率应该很高很高。

```cpp
    for(register int i=1;i<=m;++i)
    {
        for(register int k=1;k<=n;++k)
            now[k][0]=now[k][1]=1;
        for(register int j=i;j<=m;++j)
        {
            int pre=1;//上一个还未统计过的行
            for(register int k=1;k<=n;++k)
            {
                now[k][0]=(now[k][0]*num[c[k][j]][0])%MOD1;
                now[k][1]=(now[k][1]*num[c[k][j]][1])%MOD2;
                a[k]=(now[k][0]<<30)+now[k][1];
                //这里指如果当前不是合法的子串，那相当于连续的行断开了
                //对所有上面的未统计过的连续行操作，从 pre 到 k-1
                //特殊判断一下 pre > k-1 直接返回 0 就行了
                if(!b[k][i][j]) manacher(pre,k-1),pre=k+1;
            }
            manacher(pre,n);//最后还要统计一下。
        }
    }
```

完整代码挂一下，总时间复杂度 $O(nm^2)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<math.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*f;
}
const int MAXN=260,MOD1=1e9+93,MOD2=1e9+97;
int n,m,cnt[310],num[310][2],h[MAXN<<1];bool b[MAXN][MAXN][MAXN];
long long now[MAXN][2],a[MAXN],s[MAXN<<1],ans;char c[MAXN][MAXN];
int p[610],tot;
inline void init()//用不几个，懒得写线性筛
{
    for(register int i=2;tot<=600;++i)
    {
        bool flag=false;int Y=sqrt(i);
        for(register int x=2;x<=Y;++x) flag|=(!(i%x));
        if(!flag) p[++tot]=i;
    }
    return ;
}
inline void manacher(int L,int R)
{
    if(L>R) return ;
    int tot=0,l=1,r=1;s[++tot]=-1;
    for(register int i=L;i<=R;++i)
        s[++tot]=a[i],s[++tot]=-1;
    for(register int i=1;i<=tot;++i) h[i]=0;h[1]=1;
    for(register int i=2;i<=tot;++i)
    {
        if(i<=r) h[i]=min(r-i+1,h[l+r-i]);
        while(i+h[i]<=tot&&i-h[i]>=1&&s[i+h[i]]==s[i-h[i]]) ++h[i];
        if(i+h[i]-1>r) l=i-h[i]+1,r=i+h[i]-1;
    }
    for(register int i=1;i<=tot;++i) ans+=h[i]/2;
    return ;
}
int main()
{
    // freopen("pal.in","r",stdin);
    // freopen("pal.out","w",stdout);
    n=read(),m=read();init();
    for(register int i=1;i<=300;++i) num[i][0]=p[i],num[i][1]=p[i<<1];
    for(register int i=1;i<=n;++i)
        for(register int j=1;j<=m;++j) 
        {
            c[i][j]=getchar();
            while(c[i][j]<=32) c[i][j]=getchar();
        }
    for(register int k=1;k<=n;++k)
        for(register int i=1;i<=m;++i)
        {
            int cur=0;
            for(register int j=i;j<=m;++j)
            {
                ++cnt[c[k][j]];
                (cnt[c[k][j]]&1)?++cur:--cur;
                if(cur<=1) b[k][i][j]=true;
            }
            for(register int j=i;j<=m;++j) --cnt[c[k][j]];
        }
    for(register int i=1;i<=m;++i)
    {
        for(register int k=1;k<=n;++k)
            now[k][0]=now[k][1]=1;
        for(register int j=i;j<=m;++j)
        {
            int pre=1;
            for(register int k=1;k<=n;++k)
            {
                now[k][0]=(now[k][0]*num[c[k][j]][0])%MOD1;
                now[k][1]=(now[k][1]*num[c[k][j]][1])%MOD2;
                a[k]=(now[k][0]<<30)+now[k][1];
                if(!b[k][i][j]) manacher(pre,k-1),pre=k+1;
            }
            manacher(pre,n);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：User_Authorized (赞：0)

## 题意
给定一个 $n \times m$ 的字符矩阵，求经过重新排列每行内元素可以使每行每列均为回文串的子矩阵个数。

（$1 \le n,m \le 250$）。

## 题解

假定 $n,m$ 同阶，考虑 $\mathcal{O}(n^3)$ 做法。

因为每行元素均可以重新排列，所以合法的子矩阵第一行和最后一行一定相等，注意这里的相等是字符集相等且可以形成回文串。考虑对这类字符集计算哈希，最终答案即为钦定列和行回文情况下哈希值形成的回文串数量。

复杂度 $\mathcal{O}(n^3)$，可以通过本题。

## Code
```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef unsigned long long hashType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<hashType> hashVector;
typedef std::vector<hashVector> hashMatrix;
typedef std::vector<hashMatrix> hashCube;
typedef char sourceType;
typedef std::vector<sourceType> SourceVector;
typedef std::vector<SourceVector> SourceMatrix;

const hashType mask = std::chrono::system_clock::now().time_since_epoch().count();

hashType xor_shift(hashType x) {
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;

    return x;
}

hashType hash(sourceType const &data) {
    return xor_shift(xor_shift(xor_shift(data)));
}

hashType hash(sourceType const &data, valueType count) {
    return xor_shift(xor_shift(hash(data) + xor_shift(xor_shift(xor_shift(count)))));
}

valueType manacher(hashVector const &data) {
    auto const size = (valueType) data.size();

    ValueVector odd(size, 0), even(size, 0);

    for (valueType i = 0, l = 0, r = -1; i < size; ++i) {
        valueType k = (i > r) ? 1 : std::min(odd[l + r - i], r - i + 1);

        while (i - k >= 0 && i + k < size && data[i - k] == data[i + k])
            ++k;

        odd[i] = k--;

        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    for (valueType i = 0, l = 0, r = -1; i < size; ++i) {
        valueType k = (i > r) ? 0 : std::min(even[l + r - i + 1], r - i + 1);

        while (i - k - 1 >= 0 && i + k < size && data[i - k - 1] == data[i + k])
            ++k;

        even[i] = k--;

        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }

    return std::accumulate(odd.begin(), odd.end(), (valueType) 0) +
           std::accumulate(even.begin(), even.end(), (valueType) 0);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    SourceMatrix source(N + 1, SourceVector(M + 1));

    for (valueType i = 1; i <= N; ++i)
        for (valueType j = 1; j <= M; ++j)
            std::cin >> source[i][j];

    hashCube data(N + 1, hashMatrix(M + 1, hashVector(M + 1, 0)));

    for (valueType i = 1; i <= N; ++i) {
        for (valueType start = 1; start <= M; ++start) {
            SourceVector bucket(130, 0);

            hashType nowHash = 0;
            valueType oddCount = 0;

            for (valueType end = start; end <= M; ++end) {
                ++bucket[source[i][end]];

                if (bucket[source[i][end]] & 1)
                    ++oddCount;
                else
                    --oddCount;

                nowHash += hash(source[i][end], bucket[source[i][end]]);

                if (oddCount < 2)
                    data[i][start][end - start + 1] = nowHash;
                else
                    data[i][start][end - start + 1] = 0;
            }
        }
    }

    valueType ans = 0;

    for (valueType j = 1; j <= M; ++j) {
        for (valueType len = 1; len <= M - j + 1; ++len) {
            hashVector bucket;

            bucket.reserve(N);

            for (valueType i = 1; i <= N; ++i) {
                if (data[i][j][len] != 0) {
                    bucket.push_back(data[i][j][len]);
                } else {
                    ans += manacher(bucket);

                    bucket.clear();
                }
            }

            ans += manacher(bucket);
        }
    }

    std::cout << ans << std::endl;

    return 0;
}

```

---

## 作者：Retired_lvmao (赞：0)

首先考虑什么样的矩形是好的。显然的，每一行出现奇数次的数都不能超过一个，否则无法将这一行变为回文串。而要让竖行也都是回文串，则需要让第 $i$ 行和第 $n-i+1$ 行构成完全相同。

考虑怎么统计这样的矩形。首先枚举这个矩形的左端和右端，然后将每一行中间的部分通过哈希处理一下，于是就可以判定两行是否同构。

判定一行出现奇数次的数是否超过一个有一个很简单的方法。考虑给每个字符都赋予一个在 ```int``` 以内随机的权重，假如一些字符的权重的异或和为 $0$，说明**有极大的概率**下所有字母都出现了偶数次；假如这些字符权重的异或和为某个字母的权重，说明**有极大的概率** 有且仅有这个字母出现了奇数次。否则，**一定**存在多个出现奇数次的字符。

在知道了这些事情之后，你可以把每一行的哈希值都存下来，然后做 Manacher 即可。其中有些数不能和任意数匹配（即存在多个出现奇数次的字符），对于这种字符，可以给它赋一个随机的负权，然后在以它为中心的时候直接跳过，这样就可以做到不与任何字符匹配。

时间复杂度 $O(nm^2)$  

```
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
int n,m;
char s[310][310];
int HASH[310][310];
int XOR[310][310];
int b[100010],cnt=0;
int a[510];
int wht[510];
bool vis[310];
int ok[510];
mt19937 rng(time(0));
void init()
{
	cnt=0;
	b[++cnt]=1145141919;
	for(int i=1;i<=n;i++)
	{
		if(ok[i])
			b[++cnt]=a[i];
		else
			b[++cnt]=-(int)rng();
		b[++cnt]=1145141919;
	}
}
int p[100010];
int calc()
{
	memset(p,0,sizeof(p)); 
	memset(vis,0,sizeof(vis));
	int r=0,mid=0;
	for(int i=1;i<=cnt;i++)
	{
		if(b[i]<0)
			continue;
		if(i<=r)	
			p[i]=min(p[mid*2-i],r-i+1);
		while(i-p[i]>=1&&i+p[i]<=cnt&&b[i-p[i]]==b[i+p[i]])
			p[i]++;
		if(p[i]+i>r)
			r=p[i]+i-1,mid=i;
	}	
	int sum=0;
	for(int i=1;i<=cnt;i++)
		sum+=p[i]/2;
	return sum;
}
set<ull> VIS;
signed main()
{
	VIS.insert(0);
	for(int i=0;i<=25;i++)
		wht[i]=rng(),VIS.insert(wht[i]);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			HASH[i][j]=HASH[i][j-1]+wht[s[i][j]-'a'],XOR[i][j]=XOR[i][j-1]^wht[s[i][j]-'a'];
	int ans=0;
	for(int i=1;i<=m;i++)
		for(int j=i;j<=m;j++)
		{
			for(int k=1;k<=n;k++)
				a[k]=HASH[k][j]-HASH[k][i-1],ok[k]=VIS.count(XOR[k][j]^XOR[k][i-1]);	
			init();
			ans+=calc();
		}
	printf("%lld\n",ans);
}
```

---

## 作者：LCuter (赞：0)

## CF1080E 题解

##### $\text{Description}$

给定一个由小写字母组成的矩形，我们称其的一个子矩形是美丽的，当且仅当其任意行任意排列字符后，任意行或任意列都为回文串。

求该矩形的子矩形中，有多少个是美丽的。

$1\le n,m\le 250,|\Sigma|=26$

##### $\text{Solution}$

考虑一个矩形是美丽的，当且仅当其任意行任意排列字符后，任意行或任意列都为回文串，这意味着其每一行都是回文串，等价于说该行至多只有一个字符的数量为奇数，并且在矩形中对称的两行相同（对于其每一个字符分析，由于它们在同一列上并且对称，故相等），等价于说该两行任意字母数量都相等。

如果我们把每一行写成一个 $26$ 维向量 $[a_1\ a_2\ \cdots\ a_{26}]$，$a_i$ 表示第 $i$ 个字母在该行中的出现次数，那么，我们在列上截取 $[l,r]$，则每一行 $[l,r]$ 这一子区间对应的 $26$ 维向量可以对应一个序列，我们所要做的就是求出这个序列的回文子串个数，套用 manacher 即可 $\mathcal O(n|\Sigma|)$ 求出（以某个元素为中心的回文子串个数是以该元素为中心的最长回文子串长度除以 $2$ 下取整）。

另外，需要预处理对于某一行的一个子区间，其上下最靠近它的一个不能通过重排变为回文串的子区间。

至于如何求出某一行某一子区间对应的 $26$ 维向量，考虑对 $\mathcal O(nm|\Sigma|)$ 地每一行求出其所有前缀对应的 $26$ 维向量，对于某一个子区间可以通过作差得到其对应的 $26$ 维向量。

时间复杂度 $\mathcal O(nm^2|\Sigma|)$，**注意卡空间，可以不开的数组尽量不开，尤其是立方级别的**。

##### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define REG register
using namespace std;
inline void read(int& x){
	REG char c;
	while(!isdigit(c=getchar()));x=c^48;
	while(isdigit(c=getchar()))x=(x*10)+(c^48);
}

const int S=26,N=505;

int n,m;

char str[N][N];

int Ans;

short PreV[N][N][S];

inline void Pre_Init(){
	for(REG int i=1;i<=n;++i)
    	for(REG int j=1;j<=m;++j){
        	for(REG int c=0;c<S;++c) PreV[i][j][c]=PreV[i][j-1][c];
            ++PreV[i][j][str[i][j]-'a'];
        }
}

inline void GetV(int i,int l,int r,short* V){for(REG int c=0;c<S;++c)V[c]=PreV[i][r][c]-PreV[i][l-1][c];}
inline bool cmp(short* V1,short* V2){
	for(REG int c=0;c<S;++c)
    	if(V1[c]^V2[c]) return false;
	return true;
}
inline bool cmp(short* V){
	int cnt=0;
	for(REG int c=0;c<S;++c) cnt+=(V[c]&1);
	return cnt<=1;
}

short Vtmp1[N][S],MxR,MxC,MRad[N];

inline void Manacher(int l,int r){
	for(REG int i=1;i<=n;++i) GetV(i,l,r,Vtmp1[i<<1]);
	MxR=MxC=0;
	for(REG int i=1;i<=2*n+1;++i){
    	int ML=i>MxR?1:min(MRad[2*MxC-i],(short)(MxR-i+1));
    	while((i-ML)&&(i+ML<=2*n+1))
        	if(cmp(Vtmp1[i-ML],Vtmp1[i+ML])) ++ML;
        	else break;
    	MRad[i]=ML;
    	if(i+ML-1>MxR) MxR=i+ML-1,MxC=i;
    }
}

short UMD[N],DMD[N];

inline void UD(int l,int r){
	for(REG int i=1;i<=n;++i) UMD[i]=0,DMD[i]=n+1;
	int lst=0;
	for(REG int i=1;i<=n;++i){
    	if(cmp(Vtmp1[i<<1])) UMD[i]=lst;
    	else
        	for(UMD[i]=DMD[i]=i,++lst;lst<i;++lst) DMD[lst]=i;
    }
}

inline void Work(){
	read(n),read(m);
	for(REG int i=1;i<=n;++i) scanf("%s",str[i]+1);
	Pre_Init();
	for(REG int l=1;l<=m;++l)
    	for(REG int r=l;r<=m;++r){
        	Manacher(l,r),UD(l,r);
        	for(REG int i=2;i<=2*n;++i){
            	if(i&1){
                	int U=min((i-1)/2-UMD[(i-1)>>1],MRad[i]>>1);
                	int D=min(DMD[(i+1)>>1]-(i+1)/2,MRad[i]>>1);
                	Ans+=min(U,D);
                }
            	else{
                	int U=min(i/2-UMD[i>>1],MRad[i]>>1);
                	int D=min(DMD[i>>1]-i/2,MRad[i]>>1);
                	Ans+=min(U,D);
                }
            }
        }
	printf("%d\n",Ans);
}

int main(){Work();}
```



---

## 作者：daniEl_lElE (赞：0)

拒绝马拉车，学习 PAM！

如何判断一个序列是否可以重排成回文串？容易证明该问题等价于这个序列中出现的字母数量为奇数的不超过一个。于是我们可以先对每一行的每个子串判断他是否满足要求。

其次就是矩阵，考虑一个矩阵可以重排，当且仅当每一行都能重排，且上下对称的两行所含的每种字母数量均相等。不难发现我们可以先对总共 $O(nm^2)$ 个子串所包含的字母去重离散化得到每个子串的序号 $p_{i,j,k}$。然后枚举这个矩阵在第 $l\sim r$ 列之间，此时我们可以得到 $n$ 个数 $p_{i,l,r}$。我们所要求的就是所得到的 $n$ 个数序列中的回文串数量，PAM 即可解决，复杂度 $O(nm^2)$。注意前面去重离散化可以使用哈希，模数选小一点就可以不用 map。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod=19260817;
signed mp[19260817];
signed vis[17000005],it;
vector<int> vc(26);
signed x[255][255][255],cnt;
char c[255][255];
int trie[255][255];
vector<int> hs[255];
int len[255],fail[255],now,top,ct[255],p[255],mul[255];
int getfail(int x,int pos){
	while(p[pos-len[x]-1]!=p[pos]) x=fail[x];
	return x;
}
void extend(int i){
	int fa=getfail(now,i);
	if(!trie[fa][p[i]]){
		hs[fa].push_back(p[i]);
		++top;
		len[top]=len[fa]+2;
		fail[top]=trie[getfail(fail[fa],i)][p[i]];
		trie[fa][p[i]]=top;
		ct[top]=ct[fail[top]]+1;
	}
	now=trie[fa][p[i]];
}
signed main(){
	mul[0]=1;
	for(int i=1;i<=27;i++) mul[i]=mul[i-1]*10007%mod;
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
		}
		for(int j=1;j<=m;j++){
			for(int k=0;k<26;k++) vc[k]=0;
			int cnto=0,thash=0;
			for(int k=j;k<=m;k++){
				if(!(vc[c[i][k]-'a']&1)) cnto++;
				else cnto--;
				vc[c[i][k]-'a']++;
				(thash+=mul[c[i][k]-'a'])%=mod;
				if(!mp[thash]) mp[thash]=++cnt;
				x[j][k][i]=mp[thash];
				if(cnto>1) x[j][k][i]=0;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++){
		for(int j=i;j<=m;j++){
			it=0;
			for(int k=1;k<=n;k++){
				if(x[i][j][k]==0){
					p[k]=0;
					continue;
				} 
				if(!vis[x[i][j][k]]){
					vis[x[i][j][k]]=++it;
				}
				p[k]=vis[x[i][j][k]];
			}
			top=1;
			fail[0]=fail[1]=1;
			len[1]=-1;
			now=0;
			for(int k=1;k<=n;k++){
				vis[x[i][j][k]]=0;
				if(p[k]!=0) extend(k);
				else now=0;
				ans+=ct[now];
			}
			for(int k=0;k<=top;k++){
				len[k]=fail[k]=ct[k]=0;
				for(auto v:hs[k]) trie[k][v]=0;
				hs[k].clear();
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

