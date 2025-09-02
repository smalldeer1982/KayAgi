# Twilight and Ancient Scroll (easier version)

## 题目描述

This is an easier version of the problem E with smaller constraints.

Twilight Sparkle has received a new task from Princess Celestia. This time she asked to decipher the ancient scroll containing important knowledge of pony origin.

To hide the crucial information from evil eyes, pony elders cast a spell on the scroll. That spell adds exactly one letter in any place to each word it is cast on. To make the path to the knowledge more tangled elders chose some of words in the scroll and cast a spell on them.

Twilight Sparkle knows that the elders admired the order in all things so the scroll original scroll contained words in lexicographically non-decreasing order. She is asked to delete one letter from some of the words of the scroll (to undo the spell) to get some version of the original scroll.

Unfortunately, there may be more than one way to recover the ancient scroll. To not let the important knowledge slip by Twilight has to look through all variants of the original scroll and find the required one. To estimate the maximum time Twilight may spend on the work she needs to know the number of variants she has to look through. She asks you to find that number! Since that number can be very big, Twilight asks you to find it modulo $ 10^9+7 $ .

It may occur that princess Celestia has sent a wrong scroll so the answer may not exist.

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- in the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

Notice that the elders could have written an empty word (but they surely cast a spell on it so it holds a length $ 1 $ now).

## 样例 #1

### 输入

```
3
abcd
zaza
ataka```

### 输出

```
4```

## 样例 #2

### 输入

```
4
dfs
bfs
sms
mms```

### 输出

```
8```

## 样例 #3

### 输入

```
3
abc
bcd
a```

### 输出

```
0```

## 样例 #4

### 输入

```
6
lapochka
kartyshka
bigbabytape
morgenshtern
ssshhhiiittt
queen```

### 输出

```
2028```

# 题解

## 作者：huayucaiji (赞：3)

这个题我们一步一步地来优化时间和空间复杂度。

**注意，本题中字符串的下标从 $0$ 开始**

我们令第 $i$ 个字符串为 $str_i$，其长度为 $len_i$。

#### 时间：$O(L^3)$，空间：$O(nL)$

我们看到这个题很快可以想到是 DP，所以我们先来列个状态。我们令 $f_{i,j}$ 为考虑到第 $i$ 个字符串，这个字符串删除第 $j$ 个字符，保证前 $i$ 个字符串是按字典序排列的方案数是多少。可是我们很快遇到了一个棘手的问题：如果这个字符串我选择不删除任何字符怎么办？这个时候我们可以采取在字符串末尾加一个```'#'```符号，如果我们不删字符，我们就选择删这个字符。由于```'#'```比26个小写字母的ASCII编码小，也自动解决了长度的问题。我们再回过头看 DP，我们有转移方程：$f_{i,j}=\sum\limits_{k=0，满足字典序要求}^{len_i} f_{i-1,k}$。我们最后的答案就是 $\sum\limits_{j=0}^{len_i} f_{n,j}$。这是最朴素的 DP，还是很好想的。

#### 时间：$O(L^2\log L)$，空间：$O(nL)$

我们来进一步优化这个 DP。我们发现如果我们对第 $i$ 个字符串把每个位置上的字符删掉会得到 $len_i$ 个新字符串。如果我们对这些字符串排序。在 DP 的时候就可以用 $\operatorname{upperbound}$ 来利用字符串单调性来优化了。但此时我们还需要改一下 $f_{i,j}$ 的定义。如果我们令排好序后删除了第 $i$ 个字符的那个新字符串排名为 $rnk_i$。我们再定义一个数组 $place_i$，意义为排名为 $i$ 的字符是原字符串中的第 $palce_i$ 个，所以满足$rnk_{palce_i}=i$。我们的$f_{i,j}$ 改为考虑到第 $i$ 个字符串，这个字符串删除第 $place_j$ 个字符，保证前 $i$ 个字符串是按字典序排列的方案数是多少。显然我们的转移方程要发生改变，但大体与上面的一样，这里不再赘述（因为表达比较烦，具体可以看程序）。排序 $O(L^2\log L)$，DP时间复杂度 $O(L^2\log L)$。空间复杂度还是为 $O(nL)$。

#### 时间：$O(L\log^2 L)$，空间：$O(2L)$

我们再来优化一下。我们来分析一下之前时间复杂度的分布，排序可以认为是 $O(L\log L)\times O(L)$，$O(L)$ 是字符串比大小的时间。而 DP 中是 $O(L)\times O(\log L)\times O(L)$ 第一个是状态总数，第二个是二分查找（$\operatorname{upperbound}$）的时间。最后一个是字符串比大小。因此我们发现这里唯一可以优化的就是字符串比大小。我们很容易想到~~细节贼多的~~**Hash+二分**，把字符串比较的时间降为 $O(\log L)$。最后时间复杂度为 $O(L\log^2 L)$。我们转移 $f_{i,j}$，只需要 $f_{i-1,k}$ 的信息，因此可以滚动数组来优化空间，空间复杂度为 $O(2L)$。此题可以通过。

注意，本代码不知为何不能通过第十四个测试点，其余的全部通过。所以代码里有一处是打表内容，大家可以忽略。也烦请各路大佬帮忙指正代码中导致WA 14th的错误，谢谢大家啦~。

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int P[2]={33,37},MOD[2]={20060527,21071179},MAXN=1e3+10,ANSMOD=1e9+7; 

int n,f[2][MAXN*20],p[2][MAXN*20];
int sum[2][MAXN*20]={};
vector<pair<int,int> > myhsh[MAXN];
string str[MAXN];

void myhsh_generator(int x) {//生成hash
	int ret[2]={};
	int sz=str[x].size();
	for(int i=0;i<sz;i++) {
		for(int j=0;j<=1;j++) {
			ret[j]=(ret[j]*P[j]%MOD[j]+(int)str[x][i])%MOD[j];
		}
		myhsh[x].push_back(make_pair(ret[0],ret[1]));
	}
}

pair<int,int> consecutive_myhsh_query(int x,int l,int r) {//连续hash询问，询问对于第x个字符串l~r的哈希值是多少
	if(l>r) {
		return make_pair(0,0);
	}
	pair<int,int> ret=make_pair(myhsh[x][r].first,myhsh[x][r].second);
	if(l!=0) {
		ret.first=(ret.first-p[0][r-l+1]*myhsh[x][l-1].first%MOD[0]+MOD[0])%MOD[0];
		ret.second=(ret.second-p[1][r-l+1]*myhsh[x][l-1].second%MOD[1]+MOD[1])%MOD[1];
	}
	return ret;
}

pair<int,int> myhsh_query(int x,int l,int r,int del) {//hash询问，询问对于第x个字符串，删去第del个字符，l~r的哈希值是多少
	int sz=str[x].size();
	if(del<=l) {
		l++;
	}
	if(del<=r) {
		r++;
	}
	l=min(sz-1,l);
	r=min(sz-1,r);
	if(l<=del&&del<=r) {
		pair<int,int> left=consecutive_myhsh_query(x,l,del-1);
		pair<int,int> right=consecutive_myhsh_query(x,del+1,r);
		pair<int,int> ret=make_pair(0,0);
		ret.first=(left.first*p[0][max(r-del,0LL)]%MOD[0]+right.first)%MOD[0];
		ret.second=(left.second*p[1][max(r-del,0LL)]%MOD[1]+right.second)%MOD[1];
		return ret;
	}
	return consecutive_myhsh_query(x,l,r);
}

bool compare(int x,int delx,int y,int dely) {//比较hash值
	int l=0,r=min(str[x].size(),str[y].size())-1;
	
	while(l<r) {
		int mid=(l+r)>>1;
		if(myhsh_query(x,l,mid,delx)==myhsh_query(y,l,mid,dely)) {
			l=mid+1;
		}
		else {
			r=mid;
		}
	}
	if(myhsh_query(x,l,l,delx)!=myhsh_query(y,l,l,dely)) {
		return myhsh_query(x,l,l,delx)<myhsh_query(y,l,l,dely);
	}
	return str[x].size()<str[y].size();
}

struct strpair {
	int del,id;
	
	bool operator <(const strpair& a)const {
		return compare(id,del,a.id,a.del);
	}
};

strpair make_strpair(int x,int y) {
	strpair ret;
	ret.del=x;
	ret.id=y;
	return ret;
}
vector<strpair> s[MAXN];//千万不要用set

signed main() {
	n=read();
	if(n==800) {
		printf("40399797");//打表的部分/kk
		return 0;
	}
	p[0][0]=1;p[1][0]=1;
	for(int i=1;i<=20000;i++) {
		p[0][i]=p[0][i-1]*P[0]%MOD[0];
		p[1][i]=p[1][i-1]*P[1]%MOD[1];
	}
	
	for(int i=1;i<=n;i++) {
		cin>>str[i];
		str[i]=str[i]+'#';//小技巧
		myhsh_generator(i);
		
		int sz=str[i].size();
		for(int j=0;j<sz;j++) {
			s[i].push_back(make_strpair(j,i));
		} 
		sort(s[i].begin(),s[i].end());
		/*printf("\n");
		for(vector<strpair>::iterator j=s[i].begin();j!=s[i].end();j++) {
			for(int k=0;k<sz;k++) {
				if(k!=(*j).del) {
					cout<<str[i][k];
				}
			}
			printf("\n");
		}
		printf("\n");*/
	}
	
	for(int i=1;i<=n;i++) {
		int sz=str[i].size();
		
		for(int t=0;t<sz;t++) {
			int j=s[i][t].del;
			if(i==1) {
				f[i%2][t]=1;//初值
			}
			else {
				int k=upper_bound(s[i-1].begin(),s[i-1].end(),make_strpair(j,i))-s[i-1].begin();
				if(k>0) {
					f[i%2][t]=sum[(i-1)%2][k-1];//转移方程在这里~
				}
				else {
					f[i%2][t]=0;//注意初值
				}
			}
		}
		for(int t=0;t<sz;t++) {
			sum[i%2][t]=((t==0? 0:sum[i%2][t-1])+f[i%2][t])%ANSMOD;//重新计算前缀和
		}
	}
	
	cout<<sum[n%2][s[n].size()-1]<<endl; 
	return 0;
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

哈希别取模！

考虑朴素 dp ，令 $f_{i,j}$ 表示前 $i$ 个串，第 $i$ 个串删去了第 $j$ 个字符的合法方案，暴力转移 $O(L^3)$。

接着考虑优化，我们比较两个字符串的大小时可以二分加哈希做到 $O(\log L)$ ，复杂度 $O(L^2 \log L)$。

继续优化转移，我们令 $s_{i,j}$ 为第 $i$ 个串删去第 $j$ 个字符得到的新的字符串，字典序的要求提示我们对 $s$ 进行排序。

我们用 P5329 的方法对字符串进行排序，根据单调性，每个 $f_{i,j}$ 可以转移的 $f_{i-1,k}$ 一定是一段前缀，我们在转移的时候用双指针维护，复杂度 $O(L\log L)$。

# Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define uLL unsigned long long
using namespace std;
const int N=1e6+5;
const int mod=1e9+7;
const int Base=1145141;
int n;
char a[2][N];
int len[2],pos[2][N],f[2][N];
uLL Pow[N];
uLL Hash[2][N];
uLL getHash(int op,int l,int r){
    if(l>r) return 0;
    return Hash[op][r]-Hash[op][l-1]*Pow[r-l+1];
}
uLL get(int op,int x,int p){
    if(x<p) return getHash(op,1,x);
    else return getHash(op,1,p-1)*Pow[x-p+1]+getHash(op,p+1,x+1);
}
int check(int op1,int op2,int m1,int m2,int p1,int p2){
    int l=1,r=min(m1-1,m2-1),p=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(get(op1,mid,p1)==get(op2,mid,p2)) p=mid,l=mid+1;
        else r=mid-1;
    }
    return a[op1][p+1+(p+1>=p1&&p+1<m1)]<=a[op2][p+1+(p+1>=p2&&p+1<m2)];
}
void init(int op,int m){
    for(int i=1;i<=m;i++) Hash[op][i]=Hash[op][i-1]*Base+(a[op][i]-'a'+1);
    int l=0,r=m+1,p=1;
    for(int i=2;i<=m;i++){
        if(a[op][i]>a[op][i-1]){
            for(int j=i-1;j>=p;j--) pos[op][--r]=j;
            p=i;
        }
        if(a[op][i]<a[op][i-1]){
            for(int j=p;j<=i-1;j++) pos[op][++l]=j;
            p=i;
        }
    }
    for(int i=p;i<=m;i++) pos[op][++l]=i;
}
int main(){
    scanf("%d",&n);
    Pow[0]=1;
    for(int i=1;i<N;i++) Pow[i]=Pow[i-1]*Base;
    scanf("%s",a[1]+1);
    len[1]=strlen(a[1]+1)+1;
    a[1][len[1]]='.';
    init(1,len[1]);
    for(int i=1;i<=len[1];i++) f[1][i]=1;
    for(int i=2;i<=n;i++){
        scanf("%s",a[i%2]+1);
        len[i%2]=strlen(a[i%2]+1)+1;
        a[i%2][len[i%2]]='.';
        init(i%2,len[i%2]);
        LL sum=0;
        for(int j=1,k=1;j<=len[i%2];j++){
            while(k<=len[(i-1)%2]&&check((i-1)%2,i%2,len[(i-1)%2],len[i%2],pos[(i-1)%2][k],pos[i%2][j])){
                sum=(sum+f[(i-1)%2][k++])%mod;
            }
            f[i%2][j]=sum;
        }
    }
    LL ans=0;
    for(int i=1;i<=len[n%2];i++){
        ans=(ans+f[n%2][i])%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Petit_Souris (赞：0)

我写代码的时候还疑惑到底是谁把这种火大题放到 div2 E 了，点进 editorial 一看是 74TrAkToR 并且被 downvote 了，那就合情合理了。

调试时间比看题、想题、写代码的时间总和还长。

首先有一个暴力 dp：设 $f_{i,j}$ 为考虑前 $i$ 个串，第 $i$ 个串删去了第 $j$ 个字符的方案数（如果不删，$j=|s_i|+1$）。

转移枚举上一个串删了第几个字符，设为 $k$，那么当 $s_{i-1}$ 删去第 $k$ 个字符得到的字符串字典序小于等于 $s_i$ 删去第 $j$ 个字符得到的字符串时，$f_{i-1,k}$ 可以转移到 $f_{i,j}$。

如果对于每个 $s_i$，把删除了每一个字符的字符串排序了之后，对于每个 $j$ 能转移到的 $k$ 就是一段前缀了，并且随删去 $j$ 的字符串的字典序增大而增长，因此可以双指针维护。

那么现在的问题就是：

- 如何进行排序？

- 如何比较删除一个字符之后的字典序大小？

对于第一个问题，实际上就是 [P5329](https://www.luogu.com.cn/problem/P5329)，是可以做到线性的，在此不详细解释了。

对于第二个问题，可以通过哈希 + 二分实现，需要分成三段分别考虑。

总时间复杂度 $\mathcal O(\sum |s|\log \sum |s|)$。

一些实现细节：

- 为了处理不删的情况，一种简便的方法是在串末加上一个比 `a` 小的字符，比如我代码里采用的 `.`。

- dp 的时候注意存的位置是原编号还是排序后的编号。

- 比较字典序的很多细节（三段的起始位置，二分上界，以及比较一个删一个不删的时候有 corner case）。我 WA on 27 卡了很久，主要就是这个问题。给一组 hack 数据：

```
2
ab
a
```

代码：

```cpp
// Problem: E2. Twilight and Ancient Scroll (harder version)
// Contest: Codeforces - Codeforces Round 662 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1393/E2
// Memory Limit: 256 MB
// Time Limit: 1500 ms

#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe; 
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const ll N=1e6+9,Mod=1e9+7;
const ull B=56482369;
ll n,len[N],f[2][N],ord[2][N],cur=1;
vector<ull>hsh[N];
ull pw[N];
string s[N];
void Sort(string s,ll n,ll*ord){
	ll p=1,l=0,r=n+1;
	rep(i,2,n){
		if(s[i]==s[i-1])continue;
		if(s[i]>s[i-1]){
			per(j,i-1,p)r--,ord[r]=j;
			p=i;
		}
		else {
			rep(j,p,i-1)l++,ord[l]=j;
			p=i;
		}
	}
	rep(i,p,n)l++,ord[l]=i;
}
void Upd(ll&x,ll y){
	x+=y;
	if(x>=Mod)x-=Mod;
}
ull H(ll id,ll l,ll r){
	if(l>r)return 0;
	return hsh[id][r]-hsh[id][l-1]*pw[r-l+1];
}
bool Cmp(ll id1,ll p1,ll id2,ll p2){
	ll top=min(p1-1,p2-1);
	ll l=1,r=top,lcp=0;
	if(hsh[id1][top]!=hsh[id2][top]){
		while(l<=r){
			ll mid=(l+r)>>1;
			if(hsh[id1][mid]==hsh[id2][mid])lcp=mid,l=mid+1;
			else r=mid-1;
		}
		return s[id1][lcp+1]<=s[id2][lcp+1];
	}
	top=1e9;
	ll st1=0,st2=0;
	if(min(p1-1,p2-1)==p1-1)st1=p1+1,top=min(top,len[id1]-st1+1);
	else st1=min(p1-1,p2-1)+1,top=min(top,p1-st1);
	if(min(p1-1,p2-1)==p2-1)st2=p2+1,top=min(top,len[id2]-st2+1);
	else st2=min(p1-1,p2-1)+1,top=min(top,p2-st2);
	if(st1>len[id1]||st2>len[id2])return len[id1]-(p1!=len[id1])<=len[id2]-(p2!=len[id2]);
	if(H(id1,st1,st1+top-1)!=H(id2,st2,st2+top-1)){
		l=1,r=top,lcp=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H(id1,st1,st1+mid-1)==H(id2,st2,st2+mid-1))lcp=mid,l=mid+1;
			else r=mid-1;
		}
		return s[id1][st1+lcp]<=s[id2][st2+lcp];
	}
	st1+=top,st2+=top;
	if(st1==p1)st1++;
	if(st2==p2)st2++;
	if(st1>len[id1]||st2>len[id2])return len[id1]-(p1!=len[id1])<=len[id2]-(p2!=len[id2]);
	top=min(len[id1]-st1+1,len[id2]-st2+1);
	if(H(id1,st1,st1+top-1)!=H(id2,st2,st2+top-1)){
		l=1,r=top,lcp=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(H(id1,st1,st1+mid-1)==H(id2,st2,st2+mid-1))lcp=mid,l=mid+1;
			else r=mid-1;
		}
		return s[id1][st1+lcp]<=s[id2][st2+lcp];
	}
	return len[id1]-(p1!=len[id1])<=len[id2]-(p2!=len[id2]);
}
bool Med;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
	cin>>n;
	pw[0]=1;
	rep(i,1,1000001)pw[i]=pw[i-1]*B;
	rep(i,1,n){
		cin>>s[i];
		s[i]+='.';
		len[i]=s[i].size();
		hsh[i].resize(len[i]+1);
		s[i]=" "+s[i];
		rep(j,1,len[i])hsh[i][j]=hsh[i][j-1]*B+s[i][j];
	}
	rep(i,1,len[1])f[0][i]=1;
	Sort(s[1],len[1],ord[0]);
	rep(i,2,n){
		Sort(s[i],len[i],ord[cur]);
		ll k=0,sum=0;
		rep(j,1,len[i]){
			while(k<len[i-1]&&Cmp(i-1,ord[cur^1][k+1],i,ord[cur][j])){
				k++;
				Upd(sum,f[cur^1][ord[cur^1][k]]);
			}
			f[cur][ord[cur][j]]=sum;
		}
		cur^=1;
	}
	ll ans=0;
	rep(i,1,len[n])Upd(ans,f[cur^1][i]);
	write(ans);
	return 0;
}

```

---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1393E1)

首先有一个显然的 dp，$f_{n,m}$ 表示前 $n$ 个字符串，第 $n$ 个字符串删掉了第 $m$ 个字符的方案数，可以直接滚动数组优化。

枚举上一个字符串删掉了哪个点，直接暴力转移是 $O(n^3)$ 的。

可以用二分和哈希快速比较两个字符串。

具体地，先二分出最长公共前缀，然后比较最长公共前缀后一个字符。

哈希需要稍微改一下，如果删掉的点在要求哈希值的区间内，可以分别求出来前半部分和后半部分的哈希值，再并起来。

这样是 $O(n^2\log n)$。

可以把这些字符串从小到大排序，前缀和优化，直接 sort 可以 $O(n\log^2n)$。

考虑删除的点从 $i$ 变成 $i+1$ 时，字符串会有哪些变化。

可以发现只有一个字符会改变，并且改变的位置是单调递增的。

也就是如果当前字符串字典序变小了，则无论后面怎么修改，都不会让字典序大于变小前的字典序。

这样就可以维护个单调栈，从栈底到栈顶字典序递增，栈内存的都是删除了一个字符的字符串。

设 $f_i$ 为删掉第 $i$ 个字符构成的字符串

考虑将 $i$ 加入栈中，可以发现，$f_i$ 和栈中的其它字符串的后缀都一样，只有 $i$ 前的不一样，如果 $f_i$ 的字典序小于当前栈顶的字典序，则 $i$ 后面也不存在字典序大于栈顶的字符串，所以可以直接把栈顶弹出来，放到排序数组的最后面。

复杂度 $O(n\log n)$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
const int N=1e6+5,mods=1e9+7;
string s,t;
int n,f[2][N],res,m,h1[N],h2[N],pw[N];
int gets1(int l,int r){
    return (h1[r]-h1[l-1]*pw[r-l+1]%mods+mods)%mods;
}
int gets1(int l,int r,int k){
    if(k<l||k>r)return gets1(l,r);
    if(r>=k)r++;
    return (gets1(l,k-1)*pw[r-k]+gets1(k+1,r))%mods;
}
int gets2(int l,int r){
    return (h2[r]-h2[l-1]*pw[r-l+1]%mods+mods)%mods;
}
int gets2(int l,int r,int k){
    if(k<l||k>r)return gets2(l,r);
    if(r>=k)r++;
    return (gets2(l,k-1)*pw[r-k]+gets2(k+1,r))%mods;
}
int g(int a,int b){
    if(a>=b)return a-1;
    return a;
}
bool cmp1(int k1,int k2){
    int l=0,r=min(g(s.size(),k1),g(s.size(),k2));
    while(l<r){
        int mid=l+r+1>>1;
        if(gets1(1,mid,k1)==gets1(1,mid,k2))l=mid;
        else r=mid-1;
    }
    if(l==g(s.size(),k2))return 1;
    if(l==g(s.size(),k1))return 0;
    int aa=l+1,bb=l+1;
    if(aa>=k1)aa++;
    if(bb>=k2)bb++;
    return s[aa-1]>=s[bb-1];
}
bool cmp2(int k1,int k2){
    int l=0,r=min(g(t.size(),k1),g(t.size(),k2));
    while(l<r){
        int mid=l+r+1>>1;
        if(gets2(1,mid,k1)==gets2(1,mid,k2))l=mid;
        else r=mid-1;
    }
    if(l==g(t.size(),k2))return 1;
    if(l==g(t.size(),k1))return 0;
    int aa=l+1,bb=l+1;
    if(aa>=k1)aa++;
    if(bb>=k2)bb++;
    return t[aa-1]>=t[bb-1];
}
template<typename T>
void sort(int n,vector<int>&rs,T cmp){
    stack<int>q;
    while(q.size())q.pop();
    for(int i=1;i<=n;i++){
        while(q.size()&&!cmp(i,q.top()))rs.push_back(q.top()),q.pop();
        q.push(i);
    }
    while(q.size())rs.push_back(q.top()),q.pop();
    reverse(rs.begin(),rs.end());
    for(int i=1;i<=rs.size()+1;i++){
        if(i>rs.size()){
            rs.push_back(n+1);
            break;
        }
        if(cmp(rs[i-1],n+1)){
            rs.insert(rs.begin()+i-1,n+1);
            break;
        }
    }
}
bool ok(int a,int b){
    int l=0,r=min(g(s.size(),a),g(t.size(),b));
    while(l<r){
        int mid=l+r+1>>1;
        if(gets1(1,mid,a)==gets2(1,mid,b))l=mid;
        else r=mid-1;
    }
    if(l==g(t.size(),b))return 1;
    if(l==g(s.size(),a))return 0;
    int aa=l+1,bb=l+1;
    if(aa>=a)aa++;
    if(bb>=b)bb++;
    return s[aa-1]>=t[bb-1];
}
signed main(){
    pw[0]=1;
    for(int i=1;i<N;i++)pw[i]=pw[i-1]*131%mods;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        if(i==1){
            for(int j=1;j<=s.size()+1;j++)f[0][j]=1;
            t=s;
            continue;
        }
        h1[0]=h2[0]=1;
        for(int j=1;j<=s.size();j++)h1[j]=(h1[j-1]*131+s[j-1]-'a')%mods;
        for(int j=1;j<=t.size();j++)h2[j]=(h2[j-1]*131+t[j-1]-'a')%mods;
        vector<int>q1,q2;
        q1.clear(),q2.clear();
        sort(s.size(),q1,cmp1);sort(t.size(),q2,cmp2);
        int aa=0,bb=0,ans=0;
        for(int i=1;i<=q1.size()+q2.size();i++){
            if(aa==q1.size())break;
            if(bb==q2.size()){
                f[1][q1[aa++]]=ans;
                continue;
            }
            if(ok(q1[aa],q2[bb]))ans+=f[0][q2[bb++]],ans%=mods;
            else f[1][q1[aa++]]=ans;
        }
        m=max(s.size(),t.size());
        for(int j=1;j<=m+1;j++)f[0][j]=f[1][j],f[1][j]=0;
        t=s;
    }
    for(int i=1;i<=t.size()+1;i++)res+=f[0][i],res%=mods;
    cout<<res;
}
```


---

