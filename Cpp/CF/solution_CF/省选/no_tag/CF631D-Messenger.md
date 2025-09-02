# Messenger

## 题目描述

这两个字符串可能会很长，所以字符串被分成很多块，其中s被分成n块，t被分成m块。每一块(l,c)代表l个c字符连接在一起组成的字符串。即(2,′a′)="aa"。一个字符串ss会被表示成一个序列((l1,c1),(l2,c2),…,(ln,cn))。在输入中字符串"l−c"代表(l,c)。

注意到字符串的表示方式不是唯一的，例如((1,′a′),(3,′a′))=((2,′a′),(2,′a′))="aaaa"。

## 样例 #1

### 输入

```
5 3
3-a 2-b 4-c 3-a 2-c
2-a 2-b 1-c
```

### 输出

```
1```

## 样例 #2

### 输入

```
6 1
3-a 6-b 7-a 4-c 8-e 2-a
3-a
```

### 输出

```
6```

## 样例 #3

### 输入

```
5 5
1-h 1-e 1-l 1-l 1-o
1-w 1-o 1-r 1-l 1-d
```

### 输出

```
0```

# 题解

## 作者：ezoixx130 (赞：4)

我们定义$S[i]$代表S的第i块，$T[i]$代表T的第i块。

同时$S[l..r]$代表S的l到r位，并且，$T[l..r]$代表T的l到r位。

若T是S的字串，则S[l + 1..r - 1]=T[2..m - 1]且S[l].l = T[1].l且S[l].c ≥ T[1].c且S[r].l = T[m].l且S[r].c ≥ T[m].c.

所以我们只需要找到$T[2..m-1]$在$S$中出现的地方，然后再检查一下边界，这可以用KMP算法解决。

另外：

1. $M=1$和$M=2$的情况可以特殊处理

2. 若相邻的两块所含的字符相同，则可以合并

3. 答案需要储存在long long中

Time: $O(n+m)$

Memory: $O(n+m)$

代码：

```
#include <bits/stdc++.h>
using namespace std;

#define ll long long

struct dat{
	ll l;
	char c;
	friend bool operator<=(const dat &d1,const dat &d2)
	{
		return (d1.c==d2.c) && (d1.l<=d2.l);
	}
	friend bool operator==(const dat &d1,const dat &d2)
	{
		return (d1.c==d2.c) && (d1.l==d2.l);
	}
}a[200001],b[200001];

int f[200001],n,m;

void cp(dat *a,int &n)
{
	int m=0;
	for(int i=0;i<n;++i)
	{
		if(m==0 || a[m-1].c!=a[i].c)
			a[m++]=a[i];
		else
			a[m-1].l+=a[i].l;
	}
	n=m;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)scanf("%lld-%c",&a[i].l,&a[i].c);
	for(int i=0;i<m;++i)scanf("%lld-%c",&b[i].l,&b[i].c);
	cp(a,n);
	cp(b,m);
	ll ans=0;
	switch(m) {
		case 1:{
			for(int i=0;i<n;++i)
            if (b[0]<=a[i])
                ans+=a[i].l-b[0].l+1;
			break;
		}
		case 2:{
			for(int i=0;i<n-1;++i)
            if (b[0]<=a[i]&&b[1]<=a[i + 1])
                ++ans;
			break;
		}
		default:{
			f[1]=0;
        	for(int i=2;i<m-1;i++) {
	            int j=f[i-1];
	            while(j>0&&!(b[j+1]==b[i]))
	                j=f[j];
	            if (b[j+1]==b[i])
	                j++;
	            f[i]=j;
	        }
	        for(int i=1,j=0;i<n-1;i++){
	            while (j>0 && !(b[j+1]==a[i]))
	                j=f[j];
	            if(b[j+1]==a[i])
	                j++;
	            if(j==m-2)
				{
	                if(b[0]<=a[i-j] && b[j+1]<=a[i+1])
	                    ans++;
	                j=f[j];
	            }
	        }
		}
	}
	printf("%lld\n",ans);
}
```

---

## 作者：SnowTrace (赞：2)

模板拼凑练习题。

食用此题以练习读入，字符串匹配和哈希。

首先显然相邻的字母若相等可以合并。

我们以字符块整体的字符为关键字进行字符串匹配（即不考虑单个字符块的长度）。

举个例子，$s = daaabbbc$，我们只关心字符块整体，从而把 $s$ 看作 $dabc$ 进行匹配。

如果匹配成功，我们再来 check 块长。

这个结论很显然，文本串中成功匹配模式串的子串需要满足以下条件：

子串第一块块长大于等于模式串（t）第一块块长

子串最后一块快长大于等于模式串最后一块块长

字串其他块块长都与在模式串中对应的块的块长相等

这个显然我们可以转化为字符串匹配的问题。

令 $s$ 的块长数组为 $a$,$t$ 的块长数组为 $b$ 

则要判断 $\{a_l,a_{l+1},...,a_r\}$ 与 $\{b_1,b_2,b_{r-l+1}\}$ 是否相等

直接用哈希维护即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=  1000000007;
const int base = 233;
int qp(int p,int q){
	int ans = 1,pro = p;
	while(q){
		if(q&1)ans = ans*pro%mod;
		pro = pro*pro%mod,q>>=1;
	}return ans%mod;
}
int n,m;
int f[400005];
vector<pair<char,int> >s;
vector<pair<char,int> >t;
int pre1[400005],pre2[400005];
bool check(int l,int r){
	if(s[l].second<t[0].second or s[r].second<t.back().second)return 0;
	int s1 = pre1[r-1]-pre1[l],s2 = pre2[t.size()-2]-pre2[0];
	s1*=qp(qp(233,l+1)%mod,mod-2)%mod;s2*=qp(233,mod-2);
	s1%=mod,s1+=mod,s1%=mod;s2%=mod,s2+=mod,s2%=mod;
	return s1 == s2;
}
signed main(){
	cin>>n>>m;
	for(int i = 1;i<=n;i++){
		int x = 0;
		char c = getchar();
		while(c>'9' or c<'0')c = getchar();
		while('0'<=c and c<='9'){
			x = x*10+(c^48);c =getchar();
		}while(c>'z' and c<'a')c = getchar();
		c = getchar();
		if(s.size() and s.back().first == c)s[s.size()-1].second+=x;
		else s.push_back({c,x});
	}for(int i = 1;i<=m;i++){
		int x = 0;
		char c = getchar();
		while(c>'9' or c<'0')c = getchar();
		while('0'<=c and c<='9'){
			x = x*10+(c^48);c =getchar();
		}while(c>'z' and c<'a')c = getchar();
		c = getchar();
		if(t.size() and t.back().first == c)t[t.size()-1].second+=x;
		else t.push_back({c,x});
	}
	f[0] = 0;int j =0;
	if(t.size() == 1){
		int ans = 0;
		for(int i =0;i<s.size();i++)if(t[0].first == s[i].first)ans+=max((int)0,s[i].second-t[0].second+1);
		cout<<ans <<endl;return 0;
	}for(int i = 1;i<t.size();i++){
		while(j>0 and t[j].first!=t[i].first)j = f[j-1];
		if(t[j].first == t[i].first)j++;
		f[i] = j;
	}
	pre1[0] = s[0].second,pre2[0] = t[0].second;
	for(int i =1;i<s.size();i++){
		pre1[i] = (pre1[i-1]+qp(base,i)*s[i].second%mod)%mod;
	}for(int i =1;i<t.size();i++){
		pre2[i] = (pre2[i-1]+qp(base,i)*t[i].second%mod)%mod;
	}j = 0;int ans = 0;
	for(int i =0;i<s.size();i++){
		while(j>0 and t[j].first!=s[i].first)j = f[j-1];
		if(t[j].first == s[i].first)j++;
		if(j == t.size()){
			if(check(i-j+1,i))ans++;
			j = f[j-1];
		}
	}cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：chichow (赞：1)

乍一看，定睛一想，这难道不就是 KMP 多加了个权值，多判断一下不就行了？

首先将相同字符压缩，后续操作和 KMP 基本一致，只需要多判断个数是否相等。
```cpp
/* 这里使用了清华教材的数据结构的KMP实现，可能与各位的略有不同
 * 此处k-1代表已经匹配好的，接下来b[k]与a[i]比较
 */
nxt[1] = 0;
for (int i=1,k=0;i<=nb+1;){ //需要算出 nxt[nb+1]
	if (k==0 || (ib[i].ch==ib[k].ch&&ib[i].cnt==ib[k].cnt)){
		i++,k++;
        nxt[i] = k;
	}else k = nxt[k];
} 
```
改错心路历程：（好阴间啊，好在去 cf 提交可以看数据！！）

样例二错：需要特判开头和结尾，主串的计数大于等于模式串都行

WA#11: 模式串长度为1需要特判

WA#13: 要开 long long : (

WA#53: 这里很有意思：

（如果你写的 KMP 的 nxt 数组代表 **前缀后缀的公共元素的最大长度** 应该不用考虑这个问题）
```
8 5
1-a 1-b 1-c 1-a 2-b 1-c 1-a 1-b
1-a 1-b 1-c 1-a 1-b
```
注意第5个 `2-b` 和 `1-b` 属于最后一个，特判成功，根据 next 数组模式串会跳到nxt[nb+1]，也就模式串第3个是 `1-c` ，，发现此时的主串第5个 `2-b` 和模式串第2个 `1-b` 并不相同，是被特判给“合法化”。于是再加一个特判，
```cpp
if (k==nb){//k是模式串指针
	ans++;
	if (ib[k].cnt!=ia[i].cnt){
		k = nxt[k+1]-1;
	}else{
		k++;i++;
    }
}

```
WA#7: （疑惑：怎么还开倒车了？？）好吧，纯粹是上面写的特判写错了。


下面贴上丑陋的题解
```cpp

int getline(char *s){
	int re = 0;
	do{
		s[re] = getchar();
		if (s[re] == EOF) return EOF;
	}while(s[re] == '\r' || s[re] == '\n');
	while(s[re] != '\r' && s[re] != '\n' && s[re] != EOF){
		re++;
		s[re] = getchar();
	}
	s[re] = '\0';
	return re;
}

struct ITEM{
	ll cnt;
	char ch;
}ia[200100],ib[200100];
int na,nb,nxt[200100];
int main(){
	int n,m;
	ll cnt;
	char ch;
	scanf("%d%d",&n,&m);
	ia[0].ch = 0;
	for (int i=0; i<n; i++){
		scanf("%lld%*c%c",&cnt,&ch);
		if (ch==ia[na].ch){
			ia[na].cnt+=cnt;
		}else{
			ia[++na].cnt = cnt;
			ia[na].ch = ch;
		}
	}
	ib[0].ch = 0;
	for (int i=0; i<m; i++){
		scanf("%d-%c",&cnt,&ch);
		if (ch==ib[nb].ch){
			ib[nb].cnt+=cnt;
		}else{
			ib[++nb].cnt = cnt;
			ib[nb].ch = ch;
		}
	}
	ib[nb+1].ch = 0;
	ll ans = 0;
	if (nb == 1){
		for (int i=1; i<=na; i++){
			if (ia[i].ch==ib[1].ch) ans += max(0ll, ia[i].cnt-ib[1].cnt+1);
		}
		printf("%lld",ans);
		return 0;
	}

	nxt[1] = 0;
	for (int i=1,k=0;i<=nb+1;){
		if (k==0 || (ib[i].ch==ib[k].ch&&ib[i].cnt==ib[k].cnt)){
			i++,k++;
			nxt[i] = k;
		}else k = nxt[k];
	}

	for (int i=1,k=1;i<=na;){
		if (k==0){
			k++,i++;
		}else if (ib[k].ch==ia[i].ch){
			if (!((k==1&&ib[k].cnt<=ia[i].cnt) || ib[k].cnt==ia[i].cnt || (k==nb&&ib[k].cnt<=ia[i].cnt))){
				k = nxt[k];
				continue;
			}
			if (k==nb){
				ans++;
				if (ib[k].cnt!=ia[i].cnt){
					k = nxt[k+1]-1;
				}else{
					k++;i++;
				}
			}else{
				k++,i++;
			}

		}else k = nxt[k];
	}
	printf("%lld",ans);

}

```


---

## 作者：SudoXue (赞：0)

[更好的阅读体验](https://www.cnblogs.com/xueruhao/p/18949567)

题意是统计字符串 $t$ 在字符串 $s$ 中的出现次数，它们以块 $(\ell,c)$ 形式给出。先把相邻且字符相同的块合并成极大块序列，设合并后 $s$ 有 $n$ 块、$t$ 有 $m$ 块。

若 $m=1$，模式仅一块 $(b_1,c_1)$。它能放进 $s$ 的某块 $(a_i,c_i)$ 的位置数为 $a_i-b_1+1$，前提是 $c_i=c_1$ 且 $a_i\ge b_1$，累加即得答案。

若 $m=2$，只需扫一遍相邻块对 $(a_i,c_i),(a_{i+1},c_{i+1})$，当 $c_i=c_1,\;c_{i+1}=c_2,\;a_i\ge b_1,\;a_{i+1}\ge b_2$ 时出现一次。

当 $m\ge3$ 时，把首尾两块单独比较，核心是中间 $m-2$ 块序列。该序列要求在 $s$ 的块序列中逐块完全对应，于是用 KMP 在 $O(n+m)$ 时间匹配。每匹配成功一次，再检查核心左侧块与右侧块是否满足 $c_{\text{左}}=c_1,\;c_{\text{右}}=c_m,\;a_{\text{左}}\ge b_1,\;a_{\text{右}}\ge b_m$，满足即计数。

时间复杂度 $O(n+m)$。


[link](https://codeforces.com/contest/631/submission/326072824)

---

## 作者：wwwwwza (赞：0)

字符串哈希好题，思维难度和码量都不高。

一眼看上去是 KMP 算法，但用哈希更方便。

当 $t_2$ 至 $t_{m-1}$ **完全等于** $s_i$ 至 $s_{i+m-3}$ 时，可统计答案。注意，$m=1$ 或 $m=2$ 要特判。

接下来要给每一个形如 $l  -  c$ 的结构赋值，我将其赋值成 $c^l$。

接下来运用哈希实时计算 $s_i$ 至 $s_{i+m-3}$ 的哈希值，若和 $t_2$ 至 $t_{m-1}$ 相等，判断 $s_{i-1}$ 和 $s_{i+m-2}$ 是否能满足条件。

如果怕哈希值重复，可用双哈希。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+3;  
const int mod=1e9+7;  
const int p1=31,p2=73;
int n,m,lens=0,lent=0,H1=0,H2=0,ans=0;
string str;
struct node{
	int len;
	char ch;
}s[N],t[N];
int ksm(int a,int b){
	int sum=1;
	while(b){
		if(b&1)sum=sum*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return sum;
}
signed main(){
	cin >>n>>m;
	for(int i=1;i<=n;i++){
		cin >>str;
		int x=0,p=str.size();
		for(int j=0;j<p;j++){
			if('0'<=str[j]&&str[j]<='9')x=x*10+(str[j]-'0');
			else break;
		}
		if(s[lens].ch==str[p-1])s[lens].len+=x;
		else s[++lens]={x,str[p-1]};
	}
	n=lens;
	for(int i=1;i<=m;i++){
		cin >>str;
		int x=0,p=str.size();
		for(int j=0;j<p;j++){
			if('0'<=str[j]&&str[j]<='9')x=x*10+(str[j]-'0');
			else break;
		}
		if(t[lent].ch==str[p-1])t[lent].len+=x;
		else t[++lent]={x,str[p-1]};
	}
	m=lent;
	if(m==1){
		for(int i=1;i<=n;i++){
			if(s[i].ch==t[1].ch&&s[i].len>=t[1].len)ans+=(s[i].len-t[1].len+1);
		}
		cout <<ans;
		return 0;
	}
	if(m==2){
		for(int i=1;i<n;i++){
			if(s[i].ch==t[1].ch&&s[i].len>=t[1].len&&s[i+1].ch==t[2].ch&&s[i+1].len>=t[2].len)ans++;
		}
		cout <<ans;
		return 0;
	}
	for(int i=2;i<m;i++){
		H1=(H1*p1%mod+ksm(t[i].ch,t[i].len))%mod;
		H2=(H2*p2%mod+ksm(t[i].ch,t[i].len))%mod;
	}
//	cout <<H1<<" "<<H2<<endl;
	int T1=0,T2=0,k=m-2;
	for(int i=1;i<=n;i++){
		T1=(T1*p1%mod+ksm(s[i].ch,s[i].len))%mod;
		T2=(T2*p2%mod+ksm(s[i].ch,s[i].len))%mod;
		if(i>k){
			T1=(T1-ksm(p1,k)*ksm(s[i-k].ch,s[i-k].len)%mod+mod)%mod;
			T2=(T2-ksm(p2,k)*ksm(s[i-k].ch,s[i-k].len)%mod+mod)%mod;
		}
		if(i>=k){
			if(H1==T1&&H2==T2){
//				cout <<i+1<<"kk"<<i-k<<endl;
				if(1<=i-k&&i+1<=n){
					if(s[i+1].ch==t[m].ch&&s[i+1].len>=t[m].len&&s[i-k].ch==t[1].ch&&s[i-k].len>=t[1].len)ans++;
				}
			}
			
		}
	}
	cout <<ans;
	return 0;
}
```

---

## 作者：aulive (赞：0)

~~好水的字符串题~~

## 题目分析

显然，本题是一个进行压缩后进行匹配的的问题，首先，一个很显然的做法是将压缩后的字符串展开用 KMP 或哈希解决，考虑到字符串可能长达 $2^{11}$ 的长度只能在此之上进行改进。

观察题目，我们很容易发现若要使匹配串在模式串中出现，当且仅当匹配串除去两端后在模式串中出现一模一样的，并且匹配串两端的字母出现次数小于等于模式串中的次数

但这还没完，考虑到样例二中 $m=1$ 的特殊情况，我们还要特判一下 （因为我们在对匹配串进行掐头去尾的操作时可能会处理到一些奇怪的地方去）。

这里我采用的是哈希，因为为了防止在不同表示法表示相同字符串的时候哈希成不同的字符串，我们还要将相邻且有着相同字符的块合并，然后再按照前面的方式进行进行匹配就可以了。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200000;
const int mod=1e9+7;
int n,m,a[maxn+5],b[maxn+5],jin,c[maxn+5],d[maxn+5],cnt_a,cnt_b,pre_hash[maxn+5];
char ch_a[maxn+5],ch_b[maxn+5],ch_c[maxn+5],ch_d[maxn+5];
inline int read(){
	int res=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		c=getchar();
	}
	while('0'<=c&&c<='9'){
		res=(res<<3)+(res<<1)+(c^48),c=getchar();
	}
	return res;
}
int ksm(int x,int y){
	if(!y)return 1;
	int fw=ksm(x,y>>1);
	if(y&1)return fw*fw%mod*x%mod;
	return fw*fw%mod;
}
signed main(){
	srand(time(0));
	jin=rand();
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i]=read();
		cin>>ch_a[i];
	}
	for(int i=1;i<=n;i++){
		if(ch_c[cnt_a]==ch_a[i]){
			c[cnt_a]+=a[i];
		}else{
			cnt_a++;
			c[cnt_a]=a[i];
			ch_c[cnt_a]=ch_a[i];
		}
	}//合并相同字符的块
	for(int i=1;i<=m;i++){
		b[i]=read();
		cin>>ch_b[i];
	}
	for(int i=1;i<=m;i++){
		if(ch_d[cnt_b]==ch_b[i]){
			d[cnt_b]+=b[i];
		}else{
			cnt_b++;
			d[cnt_b]=b[i];
			ch_d[cnt_b]=ch_b[i];
		}
	}//同上
	n=cnt_a;
	m=cnt_b;
	memcpy(a,c,sizeof(c));
	memcpy(ch_a,ch_c,sizeof(ch_c));
	memcpy(b,d,sizeof(d));
	memcpy(ch_b,ch_d,sizeof(ch_d));
	if(m==1){//特判m=1的的特殊情况
		int ans=0;
		for(int i=1;i<=n;i++){
			if(ch_a[i]==ch_b[1]&&a[i]>=b[1]){
				ans+=a[i]-b[1]+1;
			}
		}
		cout<<ans;
		return 0;
	}
	int to_hash=0;
	for(int i=2;i<m;i++){
		to_hash=(to_hash*jin%mod+b[i]*ch_b[i]%mod)%mod;
	}
	for(int i=1;i<=n;i++){
		pre_hash[i]=pre_hash[i-1]*jin%mod+a[i]*ch_a[i]%mod;
		pre_hash[i]%=mod;
	}
	int ans=0;
	for(int i=2;i+m-3<n;i++){
		int now_hash=pre_hash[i+m-3]-pre_hash[i-1]*ksm(jin,m-2)%mod;
		now_hash=(now_hash+mod)%mod;
		if(now_hash==to_hash){
			if(ch_a[i-1]==ch_b[1]&&ch_a[i+m-2]==ch_b[m]&&a[i-1]>=b[1]&&a[i+m-2]>=b[m]){
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：_edge_ (赞：0)

我们来好好分析一下这个题目，显然对他进行暴力做事不够优秀的。

来考虑一下 $m=1$ 的情况，对于这一类情况，我们可以直接找到和他字符相等的就可以了，对于具体答案的处理，设相同的那个长度为 $a$，我需要匹配的是 $b$，那么对于答案的贡献即为 $a-b+1$。

对于 $m=2$ 的情况，这种情况下，我们寻找头相等的和尾相等的就可以了。

注意到我们匹配了一个位置就不能再左右移动的，因此每一个位置只能被计算为一种贡献。

对于 $m>2$ 的推广情况，事实上这个不弱于 $m=2$，也就是说如果匹配了则只能算一次这个结论是对的。

然后就考虑中间这部分如何匹配，匹配可以利用哈希或者 KMP 来实现。

当然，这里细节要处理的优秀一点，对于相同的字符我们合并掉即可。

时间复杂度 $O(n)$。

```cpp
#include <iostream>
#include <cstdio>
#define int long long 
using namespace std;
const int INF=2e5+5;
int n,m,nn,mm,na[INF],base,Mod,nb[INF],ba[INF],hash1[INF];
string a[INF],b[INF];
char aa[INF],bb[INF];

namespace S{
	int na[INF],nb[INF],n,m,ans;
	char aa[INF],bb[INF];
	int Sub(int l,int r) {
		return (hash1[r]-hash1[l-1]*ba[r-l+1]%Mod+Mod)%Mod;
	}
	void main() {
		base=233;Mod=1e9+7;
//		for (int i=1;i<=n;i++) cout<<na[i]<<" "<<aa[i]<<" ";cout<<"\n";
//		for (int i=1;i<=m;i++) cout<<nb[i]<<" "<<bb[i]<<" ";cout<<"\n";
		
		if (m==1) {
			for (int i=1;i<=n;i++)
				if (aa[i]==bb[1]) 
					if (na[i]>=nb[1]) 
						ans+=na[i]-nb[1]+1;
					
		}
		else if (m==2) {
			for (int i=1;i<n;i++) 
				if (aa[i]==bb[1] && aa[i+1]==bb[2]) {
					if (na[i]>=nb[1] && na[i+1]>=nb[2]) 
						ans++;
				}
		}
		else {
			ba[0]=1;int sum=0;
			for (int i=1;i<=n;i++) ba[i]=ba[i-1]*base%Mod;
			for (int i=1;i<=n;i++) hash1[i]=(hash1[i-1]*base+na[i]*base+aa[i])%Mod;
			
			for (int i=2;i<m;i++) sum=(sum*base+nb[i]*base+bb[i])%Mod;
			
			for (int i=2;i<n;i++) {
				int r=i+m-3;
				if (r>=n) continue;
				if (Sub(i,r)==sum) {
					if (aa[i-1]==bb[1] && aa[r+1]==bb[m]) {
						if (na[i-1]>=nb[1] && na[r+1]>=nb[m]) ans++;
					}
				}
			}
		}
		cout<<ans<<"\n";
		return ;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) {
		cin>>a[i];
		int x=0,len=a[i].size();
		for (int j=0;j<len;j++) {
			if (a[i][j]>='0' && a[i][j]<='9') 
				x=(x*10)+(a[i][j]-'0');
			else break;
		}
		na[i]=x;
		aa[i]=a[i][len-1];
	}
	
	for (int i=1;i<=m;i++) {
		cin>>b[i];
		int x=0,len=b[i].size();
		for (int j=0;j<len;j++) {
			if (b[i][j]>='0' && b[i][j]<='9') 
				x=(x*10)+(b[i][j]-'0');
			else break;
		}
		nb[i]=x;
		bb[i]=b[i][len-1];
	}
	
	S::n++;
	S::aa[S::n]=aa[1];
	S::na[S::n]=na[1];
	for (int i=2;i<=n;i++) {
		if (S::aa[S::n]==aa[i]) 
			S::na[S::n]+=na[i];
		else {
			S::n++;
			S::aa[S::n]=aa[i];
			S::na[S::n]=na[i];
		}
	}
	
	S::m++;
	S::bb[S::m]=bb[1];
	S::nb[S::m]=nb[1];
	for (int i=2;i<=m;i++) {
		if (S::bb[S::m]==bb[i]) 
			S::nb[S::m]+=nb[i];
		else {
			S::m++;
			S::bb[S::m]=bb[i];
			S::nb[S::m]=nb[i];
		}
	}
	
	S::main();
	return 0;
}
```


---

## 作者：王熙文 (赞：0)

## 题解

其实并不用 KMP，简单粗暴上 hash 即可。

首先，我们先将相同块合并起来（可以新开一个合并后的字符串，然后 $\mathcal O(n)$ 合并），这样以后好处理。

设合并后 $t$ 串的块数为 $m$，$|str|$ 表示字符串 $str$ 的长度。

首先需要特判 $m=1$ 或 $m=2$ 的情况：

* 当 $m=1$ 时，我们只需要遍历一遍 $s$ 串的块，如果碰到与 $t$ 串唯一的块的字母相同并且长度大于等于 $t$ 串那一块的长度的，$t$ 串的这一个块的起点可以放到 $s$ 串的 $1 \sim |s|-|t|+1$ 中（最后的一个起点可以算出来终点为 $|s|$），所以这一个块的贡献就是 $|s|-|t|+1$。

* 当 $m=2$ 时，$t$ 串的这两块需要“卡”到 $s$ 串的某相邻两块中。枚举 $s$ 串相邻的两块，如果左边这一块与 $t$ 的第一块颜色一样且包含（$s$ 这一块的长度大于等于 $t$ 这一块的长度），右面这一块也与 $t$ 的第二块颜色一样且包含，那么 $t$ 串就可以放到这里，答案加一。

接下来，对于 $m \ge 3$ 的情况，对于 $t$ 串除了首块和尾块，其他块都必须完美匹配（颜色一样且长度相等）$s$ 串的一些相邻的块。

枚举 $t$ 串放在 $s$ 串的位置，然后快速判断首块和尾块是否被包含，中间这些块是否完全匹配 $s$ 串的几块，如果可以答案就加一，否则不不改变答案。

因为枚举 $t$ 串放在 $s$ 串的位置已经花了 $\mathcal O(n)$ 的时间了，快速判断必须 $\mathcal O(1)$。

回想 hash 的应用，hash 是快速判断一个字符串（可能是子串）是否与一个串的子串相等。我们将每一块当成一个字符（数），接下来就可以进行哈希判断了。

我对于长度为 $len$，字符为 $c$ 的串，设 $c$ 在小写字母中排第 $k$，那我将它们这一块转化成了 $len+(10^6+1)k$ 这个数。这种转化可以保证不相同的块一定会转化成不一样的数。

处理出哈希值，求出中间那些块的哈希值，判断是否与 $s$ 串的一段的哈希值相等即可。

## 参考代码

哈希用的是自然溢出。

```cpp
#include<bits/stdc++.h>
#define int long long
#define unsigned unsigned long long
#define fir first
#define sec second
using namespace std;

pair<int,char> s[200010],t[200010],tmp[200010];

void uni_str(int &n,pair<int,char> s[]) // 转化，合并相同字符的块
{
	int cnt=0;
	for(int i=1; i<=n; ++i)
	{
		int now=i+1,sum=s[i].fir;
		while(now<=n && s[i].sec==s[now].sec)
		{
			sum+=s[now].fir;
			++now;
		}
		tmp[++cnt]=make_pair(sum,s[i].sec);
		i=now-1;
	}
	for(int i=1; i<=cnt; ++i) s[i]=tmp[i];
	n=cnt;
}

unsigned bas=1145141919;

unsigned base[200010],has[200010];

signed main()
{
	int n,m,ans=0;
	scanf("%lld%lld",&n,&m);
	for(int i=1; i<=n; ++i)
	{
		scanf("%lld-%c",&s[i].fir,&s[i].sec);
	}
	for(int i=1; i<=m; ++i)
	{
		scanf("%lld-%c",&t[i].fir,&t[i].sec);
	}
	uni_str(n,s);
	uni_str(m,t);
	if(m==1)
	{
		for(int i=1; i<=n; ++i)
		{
			if(s[i].fir>=t[1].fir && s[i].sec==t[1].sec) // 包含关系
			{
				ans+=s[i].fir-t[1].fir+1;
			}
		}
		printf("%lld",ans);
		return 0;
	}
	if(m==2)
	{
		for(int i=1; i<n; ++i)
		{
			if(s[i].fir>=t[1].fir && s[i].sec==t[1].sec
			&& s[i+1].fir>=t[2].fir && s[i+1].sec==t[2].sec) // 两边都包含
			{
				++ans;
			}
		}
		printf("%lld",ans);
		return 0;
	}
	if(m>n) return printf("0"),0; // 特判如果 t 的块数比 s 的块数多，显然不行
	base[0]=1;
	for(int i=1; i<=n; ++i) base[i]=base[i-1]*bas;
	unsigned thash=0;
	for(int i=2; i<m; ++i) // 求出 t 串除首位块的哈希值
	{
		thash=thash*bas+(t[i].fir+1000001*(t[i].sec-'a'));
	}
	for(int i=1; i<=n; ++i) // 预处理 s 串的哈希值
	{
		has[i]=has[i-1]*bas+(s[i].fir+1000001*(s[i].sec-'a'));
	}
	int cnt=0;
	for(int i=2; i<=n-m+2; ++i) // 枚举 t 放在哪里
	{
		int l=i,r=i+(m-2)-1;
		if(s[l-1].sec!=t[1].sec || s[l-1].fir<t[1].fir || s[r+1].sec!=t[m].sec || s[r+1].fir<t[m].fir) // 首位串是否包含
		{
			continue;
		}
		if(thash==has[r]-has[l-1]*base[r-l+1]) ++cnt; // 中间的哈希值是否相等
	}
	printf("%lld",cnt);
	return 0;
}
```

---

## 作者：infinities (赞：0)

这是一个可能有些奇怪的哈希做法。

首先，若给定的字符串中相邻两部分块的字符相同，则不妨将两段合并，这样我们可以得到两个相邻块内字符不同的串，显然比较好处理一些。


接下来，对于字符串 $t$，我们暴力枚举串 $s$ 中和 $t$ 相同子串的起始块的编号 $i$，然后只需判断子串的一头一尾和 $t$ 的头尾的字符是否相同，长度是否分别不小于 $t$ 头尾的块的长度（因为如果长度不小于 $t$ 头尾块的长度，则这两块所在的位置可以尝试匹配，若小于则无法匹配，直接跳过这个 $i$ 即可）。

最后需要做的就是判断 $t$ 除掉头尾的中间部分和子串除掉头尾的中间部分是否完全一致了，可以哈希求解。

我用了一个不是很正常的哈希方法，将 $base$ 设成一个大质数，然后第 $i$ 位的值取：字母序数加上相同的常数乘上块长度加上另一个相同的常数。

最后注意特判 $t$ 串缩完之后只剩两块和一块的情况。这两种情况直接哈希显然是不对的。

可能有一点抽象，具体可以看代码。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint register int
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int base = 998244353;
using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
int read(){int x = 0,f = 1; char ch = getchar(); while(ch < '0' || ch > '9'){if(ch == '-')f = -1; ch = getchar();}while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();} return x * f;}
int n, m;
int len1[maxn], len2[maxn], cnt1, cnt2, bas[maxn], hash1[maxn], hash2[maxn];
char s1[maxn], s2[maxn];
string s;
signed main(){
	n = read(), m = read();
	for(int i = 1; i <= n; i++){
		cin >> s;
		for(int j = 0; j < s.size(); j++){
			if(s[j] >= '0' && s[j] <= '9'){
				len1[i] = len1[i] * 10 + s[j] - '0';
			}
			if(s[j] >= 'a' && s[j] <= 'z')s1[i] = s[j];
		}
	}
	for(int i = 1; i <= m; i++){
		cin >> s;
		for(int j = 0; j < s.size(); j++){
			if(s[j] >= '0' && s[j] <= '9'){
				len2[i] = len2[i] * 10 + s[j] - '0';
			}
			if(s[j] >= 'a' && s[j] <= 'z')s2[i] = s[j];
		}
	}//这部分是处理出所有块的长度和字符
	for(int i = 1; i <= n; i++){
		if(s1[i] == s1[i - 1])len1[cnt1] += len1[i];else
		len1[++cnt1] = len1[i], s1[cnt1] = s1[i];
	}
	for(int i = 1; i <= m; i++){
		if(s2[i] == s2[i - 1])len2[cnt2] += len2[i];else
		len2[++cnt2] = len2[i], s2[cnt2] = s2[i];
	}//缩一下相邻字符相同的块
	bas[0] = 1;
	m = cnt2, n = cnt1;//缩完之后的大小更新一下
	for(int i = 1; i <= max(n, m); i++){
		bas[i] = (bas[i - 1] * base) % mod;
		hash1[i] = (hash1[i - 1] * base % mod + (int)(s1[i] - 'a' + 3) * (len1[i] + 17) % mod) % mod;
		hash2[i] = (hash2[i - 1] * base % mod + (int)(s2[i] - 'a' + 3) * (len2[i] + 17) % mod) % mod;
	}//奇怪的哈希方法，(字母序数+2)*(块长+17)作为这位的值
	if(cnt2 == 1){
		int ans = 0;
		for(int i = 1; i <= cnt1; i++){
			if(s1[i] == s2[1] && len1[i] >= len2[1]){
				ans += len1[i] - len2[1] + 1;
			}
		}cout << ans;
		return 0;
	}//特判1，只剩1块
	int sum = 0;
	for(int i = 1; i + m - 1 <= n; i++){
		if(s2[1] != s1[i] || len1[i] < len2[1] || s2[m] != s1[i + m - 1] || len1[i + m - 1] < len2[m])continue;
		//头尾是否满足要求
		if(m == 2){
			++sum; continue;
		}//特判2，只剩两块
		if(((hash2[m - 1] - hash2[1] * bas[m - 2]) % mod + mod) % mod == ((hash1[i + m - 2] - hash1[i] * bas[m - 2]) % mod + mod) % mod)++sum;
		//中间的是否一致
	}
	cout << sum << "\n";
}
```

---

