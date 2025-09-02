# String

## 题目描述

One day in the IT lesson Anna and Maria learned about the lexicographic order.

String $ x $ is lexicographically less than string $ y $ , if either $ x $ is a prefix of $ y $ (and $ x≠y $ ), or there exists such $ i $ ( $ 1<=i<=min(|x|,|y|) $ ), that $ x_{i}&lt;y_{i} $ , and for any $ j $ ( $ 1<=j&lt;i $ ) $ x_{j}=y_{j} $ . Here $ |a| $ denotes the length of the string $ a $ . The lexicographic comparison of strings is implemented by operator < in modern programming languages​​.

The teacher gave Anna and Maria homework. She gave them a string of length $ n $ . They should write out all substrings of the given string, including the whole initial string, and the equal substrings (for example, one should write out the following substrings from the string "aab": "a", "a", "aa", "ab", "aab", "b"). The resulting strings should be sorted in the lexicographical order. The cunning teacher doesn't want to check all these strings. That's why she said to find only the $ k $ -th string from the list. Help Anna and Maria do the homework.

## 说明/提示

In the second sample before string "bc" follow strings "a", "ab", "abc", "b".

## 样例 #1

### 输入

```
aa
2
```

### 输出

```
a
```

## 样例 #2

### 输入

```
abc
5
```

### 输出

```
bc
```

## 样例 #3

### 输入

```
abab
7
```

### 输出

```
b
```

# 题解

## 作者：Fearliciz (赞：7)

为什么要人云亦云？

谁说这题只能后缀自动机？

贪心其实也可以。

首先想到的思路就是将字符串的所有子串一一加到优先队列中，不过很显然，这种方法不论是时间还是空间都会炸。所以就直接排除这种写法。

### 解题思路：

其实贪心策略很好想，如下所示。

步骤一：将字符串中的字符依次加入优先队列中。

步骤二（之后一直重复此步骤直至达到第 $k$ 小字串）：从优先队列中取出字典序最小的字符串，然后将其加上其后面的字符，放入优先队列中，这样可以省去很多的无用的加入，不用将所有的字串放入优先队列，不会 $\texttt{MLE}$。

不过我却错了，原因是字符有可能重复，所以便需要一个记录位置的参数。

然后我就这样去写了，不过代码在第 $16$ 个点超时了。

```cpp
#include<bits/stdc++.h> //TLE 代码
using namespace std;
typedef pair<string,int> psi;
priority_queue<psi,vector<psi>,greater<psi>> q;
string ss;
int k;
int main()
{
    cin>>ss>>k;
    for(int i=0;i<ss.length();i++)
    {
        string tmp="";
        tmp+=ss[i];
        q.push(make_pair(tmp,i));
    }
    for(int i=1;i<k;i++)
    {
        psi u=q.top();
        q.pop();
        if(u.second<ss.length()-1)
        {
            string tmp=u.first;
            tmp+=ss[u.second+1];
            q.push(make_pair(tmp,u.second+1));
        }
        if(q.empty())
		{
            printf("No such line.");
            return 0;
        }
    }
    cout<<q.top().first;
    return 0;
}
```

经过分析，发现 $\texttt{TLE}$ 原因是每次放入优先队列的都是一个字符串加下标，其实完全没必要这样。

于是，我将参数改成了只记录开始位置和结束位置的两个 $\texttt{int}$ 值，然后就对了。

当然这样就需要重载运算符了。

以下是完整代码（比后缀自动机是不是好些很多）：

```cpp
#include<bits/stdc++.h> //AK 代码
using namespace std;
string ss;
struct Substring
{
    int l,r;
    Substring(int l,int r):l(l),r(r){}
    Substring(){}
    bool operator<(const Substring &y)//>
    const
    {
        for(int k=0;k<=r-l;k++)
        {
            int i=l+k,j=y.l+k;
            if(j>y.r) return 1;
            if(ss[i]!=ss[j]) return ss[i]>ss[j];
        }
        return 0;
    }
};
priority_queue<Substring> q;
int k;
int main()
{
    cin>>ss>>k;
    for(int i=0;i<ss.length();i++)
    {
        q.push(Substring(i,i));
    }
    for(int i=1;i<k;i++)
    {
        Substring u=q.top();
        q.pop();
        if(u.r<ss.length()-1)
        {
            ++u.r;
            q.push(u);
        }
        if(q.empty())
     	{
            printf("No such line.");
            return 0;
        }
    }
    for(int i=q.top().l;i<=q.top().r;i++) printf("%c",ss[i]);
    return 0;
}
```

#### 鸣谢：

[$\color{black} \texttt{吴雨航323}$](https://www.luogu.com.cn/user/378693)

---

## 作者：SFlyer (赞：4)

## CF128B 题解

### 前言

~~本人认为这题没那么难，其实只有 普及+/提高 左右~~

~~看到其他人写的题解，代码长度吓死我了，我只写了540B就过了~~

### 思路

很显然，如果我们所有的字串都求出来，排序后再输出第$k$个，时间复杂度会是 $O(n^2)$，会超时。但是，$k$ 只有 $10^5$，所以可以枚举排在前 $k$ 个的字串。要枚举排在前$k$个的字串，可以自然想到，要用 $\text {priority queue} $。

### 程序

程序很好写，可以首先定义一个 $\text {priority queue} $，先把给定字符串的每一个字符 $\text {push} $进去。然后，对于每一个 $\text {push} $进去了的字符串，每一次延申一位就行了。因为我们知道如果 $a$ 是 $b$ 的前缀， $b$ 字典序一定比$a$大，所以可以确保最后得到的是第 $k$ 大的，不会有字典序大的比字典序小的先出现。

${\color{LimeGreen}\colorbox{white}{AC}}$ 了的代码：

```
#include <bits/stdc++.h>
using namespace std;

#define forn(i,a,n) for (int i=a; i<n; i++)
#define p pair<string,int>

priority_queue<string, vector<p>, greater<p> > q;
string s,a;
int k,b;

int main(){
    cin>>s>>k;
	long long n=s.size();
	if (k>n*(n+1)/2)
		return cout<<"No such line."<<endl,0;
	int c=1;
	forn(i,0,n) q.push(make_pair((a=s[i]),(i+1)));
	while (c!=k){
		a=q.top().first;
		b=q.top().second;
		q.pop();
		c++;
		if (b==n) continue;
		q.push(p(a+s[b],b+1));
	}
	cout<<q.top().first<<endl;
	return 0;
}

```

祝大家 ${\color{LimeGreen}\colorbox{white}{AC}}$ 愉快！

---

## 作者：igAC (赞：3)

# $\text{Describe}$

模拟赛 $\text C$ 题，不简单题。。。

[洛谷link](https://www.luogu.com.cn/problem/CF128B)

[Codeforces link](https://codeforces.com/contest/128/problem/B)

简要题意（洛谷翻译）：求给定字符串的字典序第 $k$ 小子串（允许重复）。

# $\text{Solution}$

机房几个大佬用 SAM ``prioryty_queue`` 把这道题过了，都薄纱我。

首先我们想到子串一定可以表示为某个后缀的前缀，这启发我们用后缀数组做这道题。

按字典序将所有后缀从小到大排好，第 $i$ 个的所有前缀的字典序一定是小于第 $i+1$ 个后缀的。

这是显然的，大家稍作思考遍能得出这个结论（不会的可以在评论里说一下）。

所以我们从 $\mathrm{lcp}(i-1,i)+1$ 开始向后枚举前缀，统计他们出现的个数。

从 $\mathrm{lcp}(i-1,i)+1$ 枚举前缀是为什么呢，因为前 $\mathrm{lcp}(i-1,i)$ 个元素组成的子串一定被统计过了。

那我们如何统计出现次数呢，因为所有后缀的前缀本质上一定是不同的（因为开头就不同了）。

而且我们已经将它们按照字典序排好序了所以当前后缀 $i$ 与后面的 $i+1 \sim n$ 的 $\mathrm{lcp}$ 一定是单调不升的。

满足单调性就可以二分统计次数了。

然后我们再维护一个当前 $rank$ 表示目前的排名是多少，每次 $rank$ 加上子串出现的个数，如果满足要求（达到 $k$），那当前字串就是答案。

# $\text{Code}$

```cpp
//SA and Binary_Search
#include<bits.stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,m=256,k,w,p,Rank;
int sa[N],rk[N],height[N];
int id[N],ork[N<<1],lcp[N][25],cnt[N],key[N];
char a[N];
namespace SA{
	int Lcp(int x,int y){
		int p=log(y-x+1)/log(2);
		return min(lcp[x][p],lcp[y-(1<<p)+1][p]);
	}
	int LCP(int l,int r){
		if(l>r) swap(l,r);
		return Lcp(min(rk[l],rk[r])+1,max(rk[l],rk[r]));
	}
	bool cmp(int x,int y,int w){return ork[x]==ork[y] && ork[x+w]==ork[y+w];}
	void Get_SA(){
		for(int i=1;i<=n;++i) ++cnt[rk[i]=a[i]];
		for(int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;--i) sa[cnt[rk[i]]--]=i;
		for(w=1;;w<<=1,m=p){
			p=0;
			for(int i=n;i>n-w;--i) id[++p]=i;
			for(int i=1;i<=n;++i){
				if(sa[i]>w){
					id[++p]=sa[i]-w;
				}
			}
			memset(cnt,0,sizeof(cnt));
			for(int i=1;i<=n;++i) ++cnt[key[i]=rk[id[i]]];
			for(int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
			for(int i=n;i>=1;--i) sa[cnt[key[i]]--]=id[i];
			for(int i=1;i<=n;++i) ork[i]=rk[i];
			p=0;
			for(int i=1;i<=n;++i) rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
			if(p==n){
				for(int i=1;i<=n;++i) sa[rk[i]]=i;
				break;
			}
		}
	}
	void Get_LCP(){
		for(int i=1;i<=n;++i) lcp[i][0]=height[i];
		for(int j=1;j<=20;++j){
			for(int i=1;i<=(n-(1<<j)+1);++i){
				lcp[i][j]=min(lcp[i][j-1],lcp[i+(1<<j-1)][j-1]);
			}
		}
	}
	void Get_Height(){
		for(int i=1,k=0;i<=n;++i){
			if(k) --k;
			while(a[i+k]==a[sa[rk[i]-1]+k]) ++k;
			height[rk[i]]=k;
		}
	}
	void init(){
		Get_SA();
		Get_Height();
		Get_LCP();
	}
}
int main(){
	scanf("%s",a+1);n=strlen(a+1);k=read();
	SA::init();
	if((ll)n*(n+1)/2<(ll)k){
		puts("No such line.");
		return 0;
	}
	for(int i=1;i<=n;++i){
		for(int j=height[i]+sa[i]+1;j<=n+1;++j){
			int l=i+1,r=n,res=i;
			while(l<=r){
				int mid=(l+r)>>1;
				if(SA::Lcp(i+1,mid)>=j-sa[i]) l=mid+1,res=mid;
				else r=mid-1;
			}
			Rank+=res-i+1;
			if(Rank>=k){
				for(int t=sa[i];t<j;++t) printf("%c",a[t]);
				return 0;
			}
		}
	}
	return 0;
}
```

---

## 作者：zhengrunzhe (赞：3)

和[[TJOI2015]弦论](https://www.luogu.org/problem/P3975)这个一样

显然**后缀自动机**

$size[p]$表示节点p能表示的每个子串在原串中的出现次数

这个玩意只是对单个节点的，类似平衡树找kth，我们需要知道每个子树的大小

所以我们还要把26条转移边的$size$都累加起来记作$tot$

```cpp
#include<cstdio>
#include<cstring>
typedef long long ll;
const int N=1e5+10;
template<int maxn,int maxc>class Suffix_Automaton
{
	private:
		static const int maxs=maxn<<1;
		ll tot[maxs];
		int last,cnt,n,son[maxs][26],fa[maxs],len[maxs],size[maxs],sum[maxn],rnk[maxs];
		inline const void extend(int c)
		{
			int p=last,np=++cnt;
			len[last=np]=len[p]+(size[np]=1);
			for (;p&&!son[p][c];p=fa[p])son[p][c]=np;
			if (!p)return fa[np]=1,void();
			int q=son[p][c];
			if (len[q]==len[p]+1)return fa[np]=q,void();
			int nq=++cnt;len[nq]=len[p]+1;
			memcpy(son[nq],son[q],sizeof(son[q]));
			fa[nq]=fa[q];fa[q]=fa[np]=nq;
			for (;son[p][c]==q;p=fa[p])son[p][c]=nq;
		}
		inline const void radixsort()
		{
			for (int i=1;i<=cnt;i++)sum[len[i]]++;
			for (int i=1;i<=n;i++)sum[i]+=sum[i-1];
			for (int i=1;i<=cnt;i++)rnk[sum[len[i]]--]=i;
		}
	public:
		inline const void build(char *s)
		{
			last=cnt=1;
			n=strlen(s+1);
			for (int i=1;i<=n;i++)extend(s[i]-'a');
			radixsort();
			for (int i=cnt;i;i--)size[fa[rnk[i]]]+=size[rnk[i]];
			size[1]=0;
			for (int i=cnt;i;i--)
			{
				int p=rnk[i];
				tot[p]=size[p];
				for (int j=0;j<26;j++)tot[p]+=tot[son[p][j]];
			}
		}
		inline const void query(int k)
		{
			if (k>tot[1])return puts("No such line."),void();
			int p=1;
			while ((k-=size[p])>0)
			{
				int i=0;
				for (;k>tot[son[p][i]]&&i<26;i++)k-=tot[son[p][i]];
				p=son[p][i];
				putchar(i+'a');
			}
		}
};
Suffix_Automaton<N,26>sam;
char s[N];
int k;
int main()
{
	scanf("%s",s+1);
	scanf("%d",&k);
	sam.build(s);
	sam.query(k);
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：1)

### 题意
求给定字符串的字典序第 $k$ 小子串（允许重复）。
### 分析
有个东西叫 SPT（Super Piano's Trick)，来源于超级钢琴那道题。

其实这道题也很像，并且更简单。

考虑每一个后缀的前缀就是所有子串，而一个后缀的所有前缀都是随长度增加字典序增大的，所以我们维护一个集合，最开始加入每一个单点表示一个后缀的开头，再每次删去一个字典序最小的子串，因为显然它不可能成为答案了；然后加入这个子串拼接上后一位的新子串，这样重复执行 $k$ 次后集合内最小串即为答案。容易发现整个过程可以用堆模拟，比较两个后缀可以用 SA。

时间复杂度 $O((n+k)\log n)$，注意特判无解。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int> 
#define fir first
#define sec second
#define mkpr make_pair
#define arr(x) array<int,x>
inline int read(){
	int x=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();
	return w?x:-x;
}
bool getmn(int &x,int y){if(x>y)return x=y,1;return 0;}
bool getmx(int &x,int y){if(x<y)return x=y,1;return 0;}
mt19937 rnd(time(NULL));
const int maxn=2e5+5;
const int mod=998244353;
const int H=18;
int n,k;
string s;
class Sparse_Table{
private:
	int lg[maxn],mn[maxn][H];
public:
	void init(int *a){
		for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++) mn[i][0]=a[i];
		for(int j=1;j<H;j++) for(int i=1;i+(1<<j)-1<=n;i++) mn[i][j]=min(mn[i][j-1],mn[i+(1<<j-1)][j-1]);
	}
	int query(int l,int r){int s=lg[r-l+1];return min(mn[l][s],mn[r-(1<<s)+1][s]);}
};
class Suffix_Array{
public:
	int m,p;
	int sa[maxn],rk[maxn],ori[maxn],cnt[maxn],id[maxn],hgt[maxn];
	Sparse_Table st;
	void init(){
		m=128;
		for(int i=1;i<=n;i++) cnt[rk[i]=s[i]]++;
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
		for(int w=1;;w<<=1,m=p){
			int tt=0;
			for(int i=n-w+1;i<=n;i++) id[++tt]=i;
			for(int i=1;i<=n;i++) if(sa[i]>w) id[++tt]=sa[i]-w;
			memset(cnt,0,sizeof(cnt));
			for(int i=1;i<=n;i++) cnt[rk[i]]++;
			for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
			for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
			p=0;memcpy(ori,rk,sizeof(ori));
			for(int i=1;i<=n;i++){
				if(ori[sa[i]]==ori[sa[i-1]]&&ori[sa[i]+w]==ori[sa[i-1]+w]) rk[sa[i]]=p;
				else rk[sa[i]]=++p;
			}
			if(p==n) break;
		}
		for(int i=1,j=0;i<=n;i++){
			if(rk[i]==1){j=hgt[1]=0;continue;}
			if(j) j--;
			while(s[i+j]==s[sa[rk[i]-1]+j]) j++;
			hgt[rk[i]]=j;
		}
		st.init(hgt);
	}
	int lcp(int i,int j){if(i==j)return n-i+1;i=rk[i],j=rk[j];if(i>j)swap(i,j);return st.query(i+1,j);}
}SA;
struct sub{
	int l,r;
	sub(int L=0,int R=0){l=L,r=R;}
	bool operator < (const sub &b) const{
		int k=SA.lcp(l,b.l);
		if(l+k>r||b.l+k>b.r) return r-l+1>b.r-b.l+1; 
		return s[l+k]>s[b.l+k];
	}
}ans;
priority_queue<sub> pr;
signed main(){
	#ifdef LOCAL
	assert(freopen("data.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(0),cout.tie(0);
	cin>>s;n=s.size();s=' '+s;k=read();
	if(n*(n+1)/2<k) return puts("No such line."),0;
	SA.init();
	for(int i=1;i<=n;i++) pr.push(sub(i,i));
	while(k--){
		ans=pr.top();pr.pop();
		if(ans.r<n) pr.push(sub(ans.l,ans.r+1));
	}
	for(int i=ans.l;i<=ans.r;i++) cout<<s[i];cout<<'\n';
	//cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
	return 0;
}
```

---

## 作者：Ag2WO4 (赞：1)

#### 不错的贪心。
由于是取字典序第 $n$ 大的，先确定第一个字母（如果以某个字母开头的子串少于 $n$ 个肯定不是，第一个大于等于的肯定是），再确定第二个字母，以此类推，直到确定 $n$ 落在某个子串的字典序区间。
#### [Python 代码](https://codeforces.com/contest/128/submission/276700107)
```
s=list(map(lambda i:ord(i)-97,input()));l=len(s);m=int(input());t='';u=range(l)#t 记录子串的已确定部分
while m:
    a=[0]*26;b=[[]for i in range(26)];c=[0]*26;d=0;e=1
    for k in u:
        a[s[k]]+=l-k;c[s[k]]+=1#a 为以剩余子串中为已确定部分 + 该字母 + 任意后缀的所有子串数，c 为剩余子串中为已确定部分 + 该字母的子串数
        if~k+l:b[s[k]].append(k+1)#记录下一层的搜索位置
    for k in range(26):
        if c[k]+d>=m:t+=chr(97+k);m=e=0;break#如果 n 落在子串字典序区间，结束
        if a[k]+d>=m:t+=chr(97+k);m-=d+c[k];u=b[k];e=0;break#以后的子串都不是，开始下一层筛选
        d+=a[k]
    if e:print('No such line.');exit()#如果都没落到就是 n 太大不存在
print(t)
```
#### [C/C++ 代码](https://codeforces.com/contest/128/submission/276702393)
```c
#include<stdio.h>
char a[100001],t[100001],x;
int b[26][100001],c[27],e[100001],f[27],l,i,m,o,q,n;
long long d[27];
int main()
{
    while(x-10)
    {
        x=getchar();
        a[l++]=x-97;
    }
    --l;
    scanf("%d",&m);
    for(i=0;i<l;i++)e[i]=i;
    q=l;
    while(m)
    {
        for(o=0;o<26;o++)
        {
            i=0;
            while(b[o][i])b[o][i++]=0;
        }
        o=0;
        x=1;
        for(i=0;i<26;i++)
        {
            c[i]=0;
            d[i]=0;
            f[i]=0;
        }
        while(q--)
        {
            d[a[e[q]]]+=l-e[q];
            ++c[a[e[q]]];
            if(~e[q]+l)b[a[e[q]]][f[a[e[q]]]++]=e[q]+1;
        }
        for(i=0;i<26;++i)
        {
            if(c[i]+o>=m)
            {
                t[n++]=i+97;
                m=x=0;
                break;
            }
            if(d[i]+o>=m)
            {
                t[n++]=i+97;
                m-=o+c[i];
                q=x=0;
                while(e[q])e[q++]=0;
                q=0;
                while(b[i][q])
                {
                    e[q]=b[i][q];
                    ++q;
                }
                break;
            }
            o+=d[i];
        }
        if(x)
        {
            puts("No such line.");
            return 0;
        }
    }
    q=0;
    while(t[q])putchar(t[q++]);
}
```

---

## 作者：Kevin911 (赞：1)

因为 $k$ 和 $n$ 同阶，所以可以直接贪心的模拟代码流程。

有些类似[序列合并](https://www.luogu.com.cn/problem/P1631)这道题，即用堆维护点对表示的子串，并且堆中的元素个数 $\leq n$ ,从而保证将时间复杂度控制在 $O(n\log n)$ 的范围内，而排序规则修改为比较两个字串的字典序。

具体细节详见代码。

------------

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
char s[maxn];
int k;
struct type
{
	int l,r;
	bool operator<(const type &x)const
	{
		for(int len=0;len<=r-l;len++)
		{
			int i=l+len,j=x.l+len;
			if(j>x.r) return 1;
			if(s[i]!=s[j]) return s[i]>s[j];
		}
		return 0;
	}
};
priority_queue<type> q;
signed main()
{
	cin>>s+1>>k;
	int n=strlen(s+1);
	for(int i=1;i<=n;i++) q.push({i,i});
	for(int i=1;i<k;i++)
	{
		int l=q.top().l,r=q.top().r;
		q.pop();
		if(r<n) q.push({l,r+1});
		if(q.empty())
		{
			cout<<"No such line.";
			return 0;
		}
	}
	int l=q.top().l,r=q.top().r;
	for(int i=l;i<=r;i++) cout<<s[i];
	return 0;
}
```


---

## 作者：_edge_ (赞：1)

据说这题正解是 SAM？但是我不会这东西，咋办，欸有一种神奇的乱搞做法。

**本题解不能保证该算法时间复杂度是否正确，如果有 dalao 能证明请私信我。**

首先一个非常明显的贪心想法就是把首字母为 $a$ 的拿出来，然后看看它能构成多少个子串，然后如果 $k$ 大于等于它则意味着首字母不是 $a$，然后换下一个跑，注意这里 $k$ 要减去 $a$ 能构成的子串数量，如果找到了合法的，就把它加进答案里面，然后对于它后面的位置都加到一个地方。

对于循环往复这样操作，然后就对了。

更加具体的实现，就是把需要加的位置扔到一个 vector 里面，每次从里面取出数，然后算一下以他为首字母组成的子串有多少个。

如果你学过类似于线段树上二分的操作，这个应该不难理解。

但是令人无法理解的是，它的复杂度居然非常的奇怪，而且在数据下还跑的飞快。

另外，对于题解区有几种 priority_queue 和 set 乱搞搞过掉的，我认为他们的复杂度都有问题，因为内部他们需要 $O(len)$ 的复杂度去比较。

能过纯属是远古题的原因。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
vector <int> v,x[35];
string s1,ans;
int k;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1>>k;long long len=s1.size();
	if (k>len*(len+1)/2) {cout<<"No such line.\n";return 0;}
	for (int i=0;i<len;i++) v.pb(i);
	while (1) {
		for (int i=0;i<26;i++) x[i].clear();
		int len=v.size();
		for (int i=0;i<len;i++) x[s1[v[i]]-'a'].pb(v[i]);
		for (int i=0;i<26;i++) {
			if (x[i].size()==0) continue;
			if (k<=x[i].size()) {cout<<(ans+(char)(i+'a'))<<"\n";return 0;}
			k-=x[i].size();
			int sum=0,len=x[i].size();
			for (int j=0;j<len;j++) 
				sum+=s1.size()-x[i][j]-1;
			if (sum>=k) {
				ans+=(char)(i+'a');
				v.clear();
				for (int j=0;j<len;j++)
					if (x[i][j]!=s1.size()-1) 
						v.pb(x[i][j]+1);
				break;
			}
			else k-=sum;
		}
//		cout<<k<<" yiw\n";
	}
	
	return 0;
}
```


---

## 作者：kouylan (赞：1)

首先有一个很显然的想法，堆。与超级钢琴和异或粽子类似，每次找到最小值后往后延申一位。但是这会 TLE on Test 16。

所以只能换种方法。考虑后缀数组，每一个后缀的所有前缀就是原串的所有子串，所以我们只要在后缀中找前缀即可。

求出 $sa[]$ 和 $ht[]$ 后，后缀都是按字典序排好的，我们先来考虑相邻两个后缀的前缀，该如何排序。

![](https://cdn.luogu.com.cn/upload/image_hosting/uujjt4mh.png)

红色是相同的部分，显然长度为 $ht$。那么，排序的顺序一定是 “红$\times2+$紫$+$粉”。也就是说，相同部分优先，剩下的按顺序排。

所以这就给我们启发。我们可以从前往后的看后缀，枚举前缀的长度。对于每一个长度，我们可以二分在求出在之后有多少相同的前缀，排进序列中。只是要记住用线段树更新一下后面的后缀的枚举起点，因为有些前缀已经跟前面相同的前缀一并计算过了。

下面是 AC 代码。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define lson o<<1
#define rson o<<1|1
#define mid (l+r>>1)

int n,m,k;
int sa[100005],ht[100005],rk[100005],rk2[100005];
int mn[100005][20];
char str[100005];
struct segtree{
	int mx,laz;
}t[100005<<2];

bool cmp(int i,int j)
{
	if(rk[i]!=rk[j])
		return rk[i]<rk[j];
	int ri=(i+k<=n ? rk[i+k] : -1);
	int rj=(j+k<=n ? rk[j+k] : -1);
	return ri<rj;
}

void getsa(int n,char *str)
{
	for(int i=1;i<=n;i++)
		sa[i] = i, rk[i] = str[i];
	for(k=1;k<=n;k*=2)
	{
		sort(sa+1,sa+1+n,cmp);
		rk2[sa[1]] = 1;
		for(int i=2;i<=n;i++)
			rk2[sa[i]] = rk2[sa[i-1]]+cmp(sa[i-1],sa[i]);
		for(int i=1;i<=n;i++)
			rk[i] = rk2[i];
	}
}

void getht(int n,char *str)
{
	for(int i=1;i<=n;i++)
		rk[sa[i]] = i;
	int h=0;
	ht[1] = 0;
	for(int i=1;i<=n;i++)
	{
		int j=sa[rk[i]-1];
		if(h>0)
			h--;
		for(;j+h<=n&&i+h<=n;h++)
			if(str[j+h]!=str[i+h])
				break;
		ht[rk[i]] = h;
	}
}

void pushdown(int o)
{
	if(t[o].laz)
	{
		t[lson].mx = t[lson].laz = t[o].laz;
		t[rson].mx = t[rson].laz = t[o].laz;
	}
	t[o].laz = 0;
}

void modify(int o,int l,int r,int ql,int qr,int v)
{
	if(l>=ql && r<=qr)
	{
		t[o].mx = t[o].laz = v;
		return;
	}
	pushdown(o);
	if(ql<=mid)
		modify(lson,l,mid,ql,qr,v);
	if(qr>mid)
		modify(rson,mid+1,r,ql,qr,v);
}

int query(int o,int l,int r,int x)
{
	if(l==x && r==x)
		return t[o].mx;
	pushdown(o);
	if(x<=mid)
		return query(lson,l,mid,x);
	else
		return query(rson,mid+1,r,x);
}

int ask(int l,int r)
{
	int k=log2(r-l+1);
	return min(mn[l][k],mn[r-(1<<k)+1][k]);
}

int getp(int lef,int rht,int lim)
{
	int l=lef,r=rht,pos=lef-1;
	while(l<=r)
	{
		if(ask(lef,mid)>=lim)
			pos = mid, l = mid+1;
		else
			r = mid-1;
	}
	return pos;
}

void print(int st,int len)
{
	for(int i=st;i<=st+len-1;i++)
		cout<<str[i];
	puts("");
}

signed main()
{
	scanf("%s%lld",str+1,&m);
	n = strlen(str+1);
	if(m>n*(n+1)/2)
		return puts("No such line."), 0;
	getsa(n,str), getht(n,str);
	for(int i=1;i<=n;i++)
		mn[i][0] = ht[i];
	for(int j=1;j<20;j++)
		for(int i=1;i+(1<<j-1)<=n;i++)
			mn[i][j] = min(mn[i][j-1],mn[i+(1<<j-1)][j-1]);
	for(int i=1;i<=n;i++)
	{
		int st=sa[i],len=n-sa[i]+1,bot=query(1,1,n,i);
		for(int j=bot+1;j<=len;j++)
		{
			if(j<=ht[i+1])
			{
				int p=getp(i+1,n,j);
				int cnt=p-i+1;
				modify(1,1,n,i,p,j);
				if(m<=cnt)
					return print(sa[i],j), 0;
				m -= cnt;
			}
			else
			{
				m--;
				if(m==0)
					return print(sa[i],j), 0;
			}
		}
	}
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：lkjzyd20 (赞：0)

## 简要题意
求给定字符串 $S$ 的字典序第 $k$ 小子串（允许重复）。

如果没有输出“No such line.”。（$|S|,k\le 10^5$）

## 思路
令 $|S|$ 为 $n$。

首先思考暴力，发现这样的字串个数有 $\cfrac{n\times n+n}{2}$ 个，则无解情况可以得出。

继续思考，暴力枚举的需要 $n^2$ 的时间复杂度，但 $n \le 10^5$ 不可取。我们需要找到第 $k$ 字串，暴力枚举找出了 $\cfrac{n\times n+n}{2}$ 个字串，有没有一种方法减少找字串的数量呢？？

我们贪心找到前 $k$ 小的字串，这样只需要找出 $k$ 个字串即可，用优先队列来进行维护，因为我们知道如果字串 $S_1$ 是 $S_2$ 的前缀，那么 $S_2$ 字串长度一定比 $S_1+S_2$ 小，则字典序比 $S_1+S_2$ 小，所以可以确保先从优先队列中弹出的是字典序小的，如果弹到第 $k$ 次，则输出答案。

**注意** 判断无解情况时要化成 $\texttt{long long}$ 类型，因为 $|S=10^5|^2> \texttt{INT\_MAX}$。

## 代码
```cpp
#include <bits/stdc++.h>
// #define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
using namespace std;
priority_queue<string, vector<pair<string,int> >, greater<pair<string, int> > > q;
char s[100001];
int k;
main()
{
    cin>>(s+1)>>k;
    int len=strlen(s+1);
    if(1ll*k>(1ll*len*len+1ll*len)/2ll)puts("No such line."),exit(0);
    rep(i,1,len){
        string x="";
        x+=s[i];
        q.push({x,i});
    }
    for(int x=1;x!=k;)
    {
        auto a=q.top();q.pop();
        ++x;
        if(a.second==len)continue;
        string xx=a.first;
        xx+=s[a.second+1];
        q.push({xx,a.second+1});
    }
    cout<<q.top().first;
    return 0;
}
```

---

## 作者：ダ月 (赞：0)

### 题目分析：

首先，[原题](https://www.luogu.com.cn/problem/P3975)。

做法类似，我们建一棵 SAM，我们可以记录每个结点可以达到多少的子串，也记录每个结点出现多少次。显然，在每次递归时，我们从 `a` 一直枚举到 `z`，每次减掉子串数，直到对于 $x$ 号节点能够到达的子串数要大于等于剩下的 $k$。

代码是从那个原题那里复制过来的，没用的部分我注释或删除了。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef long long ll;
ll f[N],tr[N][26],len[N];
ll cnt[N];
int tot=1,P1=1;
ll sum[N],to[N],lar[N];
int opt;
char c[N];
void SAM(int c){
	int P2=P1;P1=++tot;
	len[P1]=len[P2]+1;cnt[P1]=1;
	int wh;
	for(;P2&&!tr[P2][c];P2=f[P2])tr[P2][c]=P1;
	if(!P2){f[P1]=1;return;}
	int P3=tr[P2][c];
	if(len[P3]==len[P2]+1){f[P1]=P3;return;}
	int P4=++tot;len[P4]=len[P2]+1;
	f[P4]=f[P3];f[P3]=P4;f[P1]=P4;
	for(;P2&&tr[P2][c]==P3;P2=f[P2])tr[P2][c]=P4;
	memcpy(tr[P4],tr[P3],sizeof(tr[P3]));
}void topu(){
	for(int i=1;i<=tot;i++) sum[len[i]]++;
	for(int i=1;i<=tot;i++) sum[i]+=sum[i-1];
	for(int i=1;i<=tot;i++) to[sum[len[i]]--]=i;
	for(int i=tot;i;i--) cnt[f[to[i]]]+=cnt[to[i]];
	for(int i=1;i<=tot;i++){
		if(opt) lar[i]=cnt[i];
	//	lar[i]=cnt[i]=1;
	}cnt[1]=lar[1]=0;
	for(int i=tot;i;i--)
		for(int j=0;j<26;j++)
			lar[to[i]]+=lar[tr[to[i]][j]];
}void dfs(int x,int y){
	if(y<=cnt[x]) return;;
	y-=cnt[x];
	for(int i=0;i<26;i++)
		if(tr[x][i]){
			if(y>lar[tr[x][i]]) y-=lar[tr[x][i]];
			else{putchar('a'+i);return dfs(tr[x][i],y);}}
}int main(){
	int wh;
	scanf("%s%d",c+1,&wh);int n=strlen(c+1);opt=1;
	for(int i=1;i<=n;i++) SAM(c[i]-'a');topu();
	if(lar[1]>=wh) dfs(1,wh);
	else puts("No such line.");
	return 0;
}

```


---

