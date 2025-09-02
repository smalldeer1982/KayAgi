# Forbidden Indices

## 题目描述

You are given a string $ s $ consisting of $ n $ lowercase Latin letters. Some indices in this string are marked as forbidden.

You want to find a string $ a $ such that the value of $ |a|·f(a) $ is maximum possible, where $ f(a) $ is the number of occurences of $ a $ in $ s $ such that these occurences end in non-forbidden indices. So, for example, if $ s $ is aaaa, $ a $ is aa and index $ 3 $ is forbidden, then $ f(a)=2 $ because there are three occurences of $ a $ in $ s $ (starting in indices $ 1 $ , $ 2 $ and $ 3 $ ), but one of them (starting in index $ 2 $ ) ends in a forbidden index.

Calculate the maximum possible value of $ |a|·f(a) $ you can get.

## 样例 #1

### 输入

```
5
ababa
00100
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
ababa
00000
```

### 输出

```
6
```

## 样例 #3

### 输入

```
5
ababa
11111
```

### 输出

```
0
```

# 题解

## 作者：hsfzLZH1 (赞：8)

## 解题思路

对 $s$ 进行后缀排序。在后缀排序中，相邻的两个后缀的字典序都最接近，也有最长公共前缀 （ LCP ） 。

任意后缀的前缀都是原串的子串，先不考虑被禁止的位置，我们考虑每个后缀的前缀对答案的贡献。

一个长度为 $t$ 的子串在原串中的位置是一段连续的区间，区间中的相邻两后缀的 LCP 长度 （ $h$ 数组 ）都是大于或等于 $t$ 的。这样我们只要求出 $h$ 数组，把 $h$ 数组的每个值转换成等量的格子，我们要求的就是其最大子矩阵。

我们使用贪心的方法，每次选择一个位置当做这个矩形的高，然后找到其能往左右扩展的最大长度，相乘即可。向左右扩展的最大长度即为向右最近的 $h$ 值小于该位 $h$ 值的下标 $lft_i$ 减去向左最近的 $h$ 值小于该位 $h$ 值的下标 $rgt_i$ 。这两个值都是可以用单调栈在总共 $O(n)$ 的时间复杂度内求出的。

最后的答案即为 $Ans=\max\{h_i\times(rgt_i-lft_i)\}$ 。

处理被禁止的位置，我们可以将字符串和表示被禁止状态的字符串翻转，将禁止最后一个字符转化成禁止第一个字符，删除后缀排序中这个字符开始的后缀，并将该位的 $h$ 值与后一位合并 （取 $\min$ ） 即可正常计算。

## 代码展示

```cpp
// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
const int maxn=200010;
const int maxsiz=130;
typedef long long ll;
const ll inf=2e9;
ll n,m,sa[maxn],x[maxn],y[maxn],c[maxn],rnk[maxn],h[maxn];
ll tf[maxn],lft[maxn],rgt[maxn],ans,cur,hh[maxn],minn;
char s[maxn],ss[maxn],ch;
stack<int>st;
int main()
{
    scanf("%d%s",&n,ss+1);
    for(int i=1;i<=n;i++)s[i]=ss[n-i+1];
    for(int i=n;i>=1;i--)scanf(" %c",&ch),tf[i]=ch-'0';
    m=maxsiz-1;
    for(int i=1;i<=n;i++)x[i]=s[i];
    for(int i=0;i<=m;i++)c[i]=0;
    for(int i=1;i<=n;i++)c[x[i]]++;
    for(int i=1;i<=m;i++)c[i]+=c[i-1];
    for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
    for(int k=1,cur;k<=n;k<<=1)
    {
        cur=0;
        for(int i=n;i>n-k;i--)y[++cur]=i;
        for(int i=1;i<=n;i++)if(sa[i]>k)y[++cur]=sa[i]-k;
        for(int i=0;i<=m;i++)c[i]=0;
        for(int i=1;i<=n;i++)c[x[i]]++;
        for(int i=1;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
        cur=y[sa[1]]=1;
        for(int i=2;i<=n;i++)
        {
        	int a,b;
        	a=sa[i]+k>n?-1:x[sa[i]+k];
      		b=sa[i-1]+k>n?-1:x[sa[i-1]+k];
      		y[sa[i]]=(x[sa[i]]==x[sa[i-1]])&&(a==b)?cur:(++cur);
        }
        swap(x,y);
        if(cur>=n)break;
        m=cur;
    }
    for(int i=1;i<=n;i++)rnk[sa[i]]=i;
    int nww=0;
    for(int i=1;i<=n;i++)
    {
        if(rnk[i]==1)continue;
        if(nww)nww--;
        while(i+nww<=n&&sa[rnk[i]-1]+nww<=n&&s[i+nww]==s[sa[rnk[i]-1]+nww])nww++;
        h[rnk[i]]=nww;
    }
    tf[0]=1;
    for(int i=1;i<=n;i++)
    {
    	if(!tf[sa[i]])ans=max(ans,n-sa[i]+1); 
    	if(tf[sa[i]])minn=min(minn,h[i]);
    	else if(!tf[sa[i]]&&tf[sa[i-1]])hh[++cur]=min(minn,h[i]),minn=inf;
    	else hh[++cur]=h[i];
	}
	//printf("%lld\n",ans);
	n=cur;
	for(int i=1;i<=n;i++)h[i]=hh[i];
    for(int i=1;i<=n;i++)
    {
    	while(!st.empty()&&h[st.top()]>=h[i])st.pop();//数据太水了，这一行原来打的 > 都过了
    	if(st.empty())lft[i]=1;
    	else lft[i]=st.top();
    	st.push(i);
	}
	while(!st.empty())st.pop();
	for(int i=n;i>=1;i--)
    {
    	while(!st.empty()&&h[st.top()]>=h[i])st.pop();
    	if(st.empty())rgt[i]=n+1;
    	else rgt[i]=st.top();
    	st.push(i);
	}
	//for(int i=1;i<=n;i++)printf("%lld ",h[i]);printf("\n");
	//for(int i=1;i<=n;i++)printf("%lld ",lft[i]);printf("\n");
	//for(int i=1;i<=n;i++)printf("%lld ",rgt[i]);printf("\n");
	for(int i=1;i<=n;i++)ans=max(ans,h[i]*(rgt[i]-lft[i]));
	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：asuldb (赞：3)

 还有这么板子的题？
 
 和你谷上后缀自动机的板子基本一样，区别就是之后这个位置是$0$才计入贡献
 
 代码
 
 ```cpp
#include<iostream>
#include<cstdio>
#define maxn 400005
#define re register
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
char S[maxn>>1],T[maxn>>1];
int n,lst=1,cnt=1;LL ans;
int fa[maxn],len[maxn],sz[maxn],tax[maxn],a[maxn],son[maxn][26];
inline void ins(int c,int o) {
	int p=++cnt,f=lst; lst=p;
	len[p]=len[f]+1,sz[p]=o;
	while(f&&!son[f][c]) son[f][c]=p,f=fa[f];
	if(!f) {fa[p]=1;return;}
	int x=son[f][c];
	if(len[f]+1==len[x]) {fa[p]=x;return;}
	int y=++cnt;
	len[y]=len[f]+1,fa[y]=fa[x],fa[x]=fa[p]=y;
	for(re int i=0;i<26;i++) son[y][i]=son[x][i];
	while(f&&son[f][c]==x) son[f][c]=y,f=fa[f];
}
int main()
{
	scanf("%d",&n);scanf("%s",S+1),scanf("%s",T+1);
	for(re int i=1;i<=n;i++) ins(S[i]-'a',int(T[i]-'0')^1);
	for(re int i=1;i<=cnt;i++) tax[len[i]]++;
	for(re int i=1;i<=n;i++) tax[i]+=tax[i-1];
	for(re int i=1;i<=cnt;i++) a[tax[len[i]]--]=i;
	for(re int i=cnt;i;i--) sz[fa[a[i]]]+=sz[a[i]];
	for(re int i=1;i<=cnt;i++) ans=max(ans,(LL)sz[i]*(LL)len[i]);
	std::cout<<ans;
	return 0;
}

```

---

## 作者：lfxxx (赞：1)

我们可以用 SAM 来刻画一个模式串在文本串的出现位置，也就是 $endpos$ 集合。

那么及既然有些位置不能作为结束位置就将其的贡献置为 $0$，否则是 $0$，然后在 parent 树上 dp 一遍算出一个节点的带权子树大小也就是合法的出现位置数量最后乘上这个等价类的最长字符串长度即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 4e5+114;;
struct SAM{
	int len,fa;
	int son[26];
}nd[maxn]; 
int tot,lst,q;
int dp[maxn];
void ins(char c){
    if(nd[lst].son[c-'a']!=0){
    	int q=nd[lst].son[c-'a'],v=lst;
        if(nd[q].len==nd[v].len+1){
        	lst=q;
        	return ;	
		}
        int nq=++tot;
        lst=nq;
        nd[nq]=nd[q];
        nd[nq].len=nd[v].len+1;
        nd[q].fa=nq;
        while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
        return ;
    }
    int u=++tot,v=lst;
	nd[u].len=nd[lst].len+1;
  	lst=u;
	while(v!=0&&nd[v].son[c-'a']==0) nd[v].son[c-'a']=u,v=nd[v].fa;
	if(v==0){
        nd[u].fa=1;
        return ;
    }else{
        int q=nd[v].son[c-'a'];
        if(nd[v].len+1==nd[q].len){
            nd[u].fa=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[u].fa=nq;
            nd[q].fa=nq;
            while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
            return ;
        }
    }
    return ;
}
vector<int> E[maxn];
void init(){
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
    return ;
}
string t;
int n,ans;
void dfs(int u){
    for(int v:E[u]){
        dfs(v);
        dp[u]+=dp[v];
    }
    ans=max(ans,dp[u]*nd[u].len);
}
signed main(){
    ans=-1e18-114;
    lst=++tot;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    cin>>t;
    for(int i=1;i<=n;i++){
        char c;
        cin>>c;
        ins(t[i-1]);
        if(c=='0') dp[lst]=1;
    }
    init();
    dfs(1);
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：Rikka__ (赞：1)

## 题目大意：

先给定一个制虎窜，如果不看题目限制，那么本题求的就是所有子串的长度乘上其出现次数即：
 $$ans=\max( len[i]*num[i])$$


①len[i] 为 i 节点代表的 endpos 的最长串串长度。

②num[i] 为 i 节点代表的 endpos 的集合大小即串串的出现次数。

但是题目中给定了限制，在某些位置结束的串串不可被记入贡献。

所以我们可以在 extend 的时候进行分论：

①若该位置对应的节点被禁止，我们则将 num[i] 记为 0。

②若该位置对应的节点不被禁止，我们就按照 SAM 的标准流程，将 num[i] 记为 1。

在整个串串都 extend 完之后进行 DFS 或拓扑（基数排序），对 num 数组进行转移。在转移完了之后按照上面的式子统计贡献就行了。

Codes:
```cpp
//By Rikka__
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define _ =read()
inline int read(){
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
inline void Put(int x){printf("%lld\n",x);}
const int Maxn=500000*2+1;
int N;

char str[Maxn];
char fob[Maxn];
struct ss{
	int len[Maxn];
	int link[Maxn];
	int ar[Maxn];
	int c[Maxn];
	int num[Maxn];
	int head[Maxn];
	int last;
	int siz;
	int ans;
	map<int,int> next[Maxn];

	void init(){
		len[0]=0;
		link[0]=-1;
		siz=0;
		last=0;
		ans=-INT_MAX;
	}
	//0 ok
	// 1 nop
	
	void extend(int c,int opt){
		
		int now=++siz;
		len[now]=len[last]+1;
		int pre=last;
		num[now]=opt;
		
		while(pre!=-1&&!next[pre][c]){
			next[pre][c]=now;
			pre=link[pre];
		}
		if(pre==-1) link[now]=0;
		else{
			int s=next[pre][c];
			if(len[pre]+1==len[s]) link[now]=s;
			else{
				int clone=++siz;
				len[clone]=len[pre]+1;
				link[clone]=link[s];
				next[clone]=next[s];
				
				link[s]=clone;
				link[now]=clone;
				
				while(pre!=-1&&next[pre][c]==s){
					next[pre][c]=clone;
					pre=link[pre];
				}		
			}
		}
		last=now; 
	}
	
	void Sort(){
		
		for(int i=1;i<=siz;i++) c[len[i]]++;
		for(int i=1;i<=siz;i++) c[i]+=c[i-1];
		for(int i=1;i<=siz;i++) ar[c[len[i]]--]=i;
		for(int i=siz;i>=1;i--) {
			num[link[ar[i]]]+=num[ar[i]];
		}
		for(int i=1;i<=siz;i++){
			ans=max(ans,num[i]*len[i]);
		}
	}
}SAM;



signed main(){
	N _;
	char ch;
	scanf("%s",str);
	scanf("%s",fob);
	SAM.init();
	for(int i=0;i<N;i++) {
		SAM.extend(str[i]-'a',(fob[i]-'0')==0);
	}
	SAM.Sort();
	
	Put(SAM.ans);
	
	return 0;
}
```

END

---

## 作者：冷却心 (赞：0)

简单串串 SA。

先不考虑这个神秘 01 序列，那么就是求出每个子串出现次数乘以其长度的最大值。先把单独出现一次特判掉，然后考虑建后缀数组，得到 LCP 的 $h$ 数组。我们枚举子串长度 $l$，然后统计出现次数最大的。容易发现同一个子串的出现在 $\mathrm{sa}$ 数组中一定是连续的。对于所有的 $h_i \ge l$，在 $i$ 和 $i-1$ 之间连边。那么每个连通块就是一个长度为 $l$ 的子串的最大出现次数，取 $\max$ 即可。这样直接做是 $O(n^2)$ 的，我们考虑从大到小枚举子串长度，用并查集维护连边即可，时间复杂度 $O(n \alpha(n))$。

然后考虑加上这个 01 序列限制怎么做。我们发现结尾的限制对 SA 不是很友好，所以我们把整个序列翻转，那么就变成不能以某个位置开头。和上面的做法类似的，只不过我们把连通块的大小变成连通块内 $0$ 的个数即可。然后就做完了。时间复杂度视 SA 的实现，这里给一个 $O(n \log^2 n)$ SA 做法。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 4e5 + 10;
int n; char S[N], T[N];
int rk[N], sa[N], rk_[N], h[N];
void Simulated_Annealing() {
	for (int i = 1; i <= n; i ++) sa[i] = i, rk[i] = S[i];
	for (int w = 1; w <= n; w <<= 1) {
		sort(sa + 1, sa + 1 + n, [w](int a, int b) { 
			return (rk[a] == rk[b] ? rk[a + w] < rk[b + w] : rk[a] < rk[b]); 
		});
		for (int i = 1, r = 0; i <= n; i ++) {
			if (rk[sa[i]] == rk[sa[i - 1]] && rk[sa[i] + w] == rk[sa[i - 1] + w]) rk_[sa[i]] = r;
			else rk_[sa[i]] = ++ r;
		} for (int i = 1; i <= n; i ++) rk[i] = rk_[i];
	} 
	for (int i = 1, cur = 0; i <= n; i ++) {
		if (rk[i] == 1) continue;
		if (cur) cur --;
		while (S[i + cur] == S[sa[rk[i] - 1] + cur]) ++ cur;
		h[rk[i]] = cur;
	} return ;
}

int fa[N], sz[N]; 
int Find(int x) { return (fa[x] == x ? x : fa[x] = Find(fa[x])); };
void merge(int x, int y) {
	x = Find(x), y = Find(y); if (x == y) return ;
	fa[x] = y; sz[y] += sz[x]; sz[x] = 0;
}
vector<int> vec[N];
int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> (S + 1) >> (T + 1);
	reverse(S + 1, S + 1 + n); reverse(T + 1, T + 1 + n);
	Simulated_Annealing(); LL Ans = 0;
	for (int i = 1; i <= n; i ++) if (T[i] == '0') { Ans = n - i + 1; break; }
	for (int i = 1; i <= n; i ++) fa[i] = i, sz[i] = (T[sa[i]] != '1');
	for (int i = 1; i <= n; i ++) vec[h[i]].emplace_back(i);
	for (int i = n; i >= 0; i --) {
		for (int x : vec[i]) {
			if (x > 1) merge(x, x - 1);
			Ans = max(Ans, 1ll * i * sz[Find(x)]);
		}
	} cout << Ans << "\n";
	return 0;
}
```

---

## 作者：__stick (赞：0)

## 题意
给出一个字符串 $s$，一个 01 串，长度均为 $n$（$n\le 2\cdot10^5$）。设 $a$ 为 $s$ 的一个子串，求 $|a|\cdot f(a)$ 的最大值，其中 $f(a)$ 表示子串 a 在 $s$ 中的出现次数（结尾位置在 01 串中的值是 0）。
## 思路

不管这个奇妙的 01 串，发现这个问题可以用后缀数组解决，先特判掉 $f(a)=1$ 的情况，这时候就是字符串本身。

然后考虑不等于 $1$ 的情况，其实等价于选择一些后缀的 lcp，这里后缀排序后求出来 $height$ 数组。由于排序后我们选择的后缀肯定是连续的，于是本质就是求 $(\min\limits_{1\le l \le i\le r \le n} height_i)(r-l)$ 的最大值，这个都会做，考虑每个 $height$ 的贡献，用单调栈求出来这玩意作为最小值的区间，选择当前 $ height$ 肯定选择这个区间是最优的，于是枚举所有 $height$ 即可。

加上 01 的限制并不难，首先在结尾是 $0$ 非常难处理，此时我们将字符串翻转，这样答案明显不变，而限制转化成开头不为 $1$ 的子串，于是对应的就是开头不为 $0$ 的后缀的前缀才对答案有贡献，这里可以处理一个前缀和数组 $sum$ 表示当前 01 串前缀中 $0$ 的个数，此时式子就变成了：

$ (\min\limits_{1\le l \le i\le r \le n} height_i)(sum_r-sum_{l-2})$ 还是可以单调栈处理后，枚举所有 $height$，于是就做完了。
## 代码

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
const int mod=1e9+7;
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
const int MAXN=1e6+10;
int cnt[MAXN],x[MAXN],y[MAXN];
char a[MAXN],s[MAXN];
int sa[MAXN];
void get_sa(int n,int m)
{
	for(int i=1;i<=n;i++)cnt[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int p=0;
		for(int i=n-k+1;i<=n;i++)y[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)y[++p]=sa[i]-k;
		for(int i=1;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[x[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i;i--)sa[cnt[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y);
		p=1,x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p==n)break;
		m=p;
	}
}
int rk[MAXN],hi[MAXN];
void get_hi(int n)
{
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	for(int i=1,k=0;i<=n;i++)
	{
		if(rk[i]==1)continue;
		if(k)k--;int j=sa[rk[i]-1];
		while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++;
		hi[rk[i]]=k;
	}
}
ll sum[MAXN];
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int n;cin>>n;
	cin>>(a+1);
	cin>>(s+1);
	reverse(a+1,a+n+1),reverse(s+1,s+n+1);
	ll ans=0;
	for(int i=1;i<=n;i++)if(s[i]=='0')cmax<ll>(ans,n-i+1);
	get_sa(n,258),get_hi(n);
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(s[sa[i]]=='0');
	vi l(n+1),r(n+1);
	{
		vi s(n+1);int top=0;
		for(int i=1;i<=n;i++)
		{
			while(top&&hi[s[top]]>=hi[i])top--;			
			l[i]=s[top]+1;
			s[++top]=i;
		}
		top=0;
		s[0]=n+1;
		for(int i=n;i>=1;i--)
		{
			while(top&&hi[s[top]]>=hi[i])top--;		
			r[i]=s[top]-1;
			s[++top]=i;
		}
	}
	for(int i=2;i<=n;i++)cmax(ans,hi[i]*(sum[r[i]]-sum[max(0,l[i]-2)]));
	cout<<ans;
	return 0;
}
```


---

