# BerOS File Suggestion

## 题目描述

Polycarp is working on a new operating system called BerOS. He asks you to help with implementation of a file suggestion feature.

There are $ n $ files on hard drive and their names are $ f_1, f_2, \dots, f_n $ . Any file name contains between $ 1 $ and $ 8 $ characters, inclusive. All file names are unique.

The file suggestion feature handles queries, each represented by a string $ s $ . For each query $ s $ it should count number of files containing $ s $ as a substring (i.e. some continuous segment of characters in a file name equals $ s $ ) and suggest any such file name.

For example, if file names are "read.me", "hosts", "ops", and "beros.18", and the query is "os", the number of matched files is $ 2 $ (two file names contain "os" as a substring) and suggested file name can be either "hosts" or "beros.18".

## 样例 #1

### 输入

```
4
test
contests
test.
.test
6
ts
.
st.
.test
contes.
st
```

### 输出

```
1 contests
2 .test
1 test.
1 .test
0 -
4 test.
```

# 题解

## 作者：mrsrz (赞：2)

对所有给定串首尾相连（中间用分隔符隔开）建后缀数组。然后询问给的串在后缀数组上二分匹配。

二分+ST表得出这个串在后缀数组上的区间，则转化为区间数颜色问题。

离线莫队即可。

时间复杂度$O((L+q)\log L+L\sqrt q)$。

## Code：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 188888
#define log2(x)(31-__builtin_clz(x))
int siz;
struct que{
	int l,r,id;
	inline bool operator<(const que&rhs)const{
		return(l/siz!=rhs.l/siz)?(l<rhs.l):(r<rhs.r);
	}
}q[N];
char S[10005][10],t[10];
int s[N],n,m,fx=127,ys[N],x[N],y[N],c[N],sa[N],height[N],p[N],st[18][N],Q,len;
int ans1[N],ans2[N];
void sort(){
	int m=fx;
	for(int i=0;i<=m;++i)c[i]=0;
	for(int i=1;i<=n;++i)++c[x[i]=s[i]];
	for(int i=1;i<=m;++i)c[i]+=c[i-1];
	for(int i=n;i;--i)sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1){
		int p=0;
		for(int i=n-k+1;i<=n;++i)y[++p]=i;
		for(int i=1;i<=n;++i)if(sa[i]-k>0)y[++p]=sa[i]-k;
		for(int i=0;i<=m;++i)c[i]=0;
		for(int i=1;i<=n;++i)++c[x[i]];
		for(int i=1;i<=m;++i)c[i]+=c[i-1];
		for(int i=n;i;--i)sa[c[x[y[i]]]--]=y[i];
		std::swap(x,y);
		x[sa[1]]=p=1;
		for(int i=2;i<=n;++i)
		x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?p:++p;
		if(p==n)break;
		m=p;
	}
	for(int i=1,k=0;i<=n;++i)
	if(x[i]!=1){
		k-=!!k;
		int j=sa[x[i]-1];
		while(s[i+k]==s[j+k])++k;
		height[x[i]]=k;
	}
}
void init(){
	for(int i=1;i<=n;++i)
	p[i]=ys[sa[i]];
	for(int i=1;i<=n;++i)st[0][i]=height[i];
	for(int i=0;i<17;++i)
	for(int j=1;(1<<i)+j<=n;++j)
	st[i+1][j]=std::min(st[i][j],st[i][j+(1<<i)]);
}
inline int ask(int l,int r){
	int lg=log2(r-l+1);
	return std::min(st[lg][l],st[lg][r-(1<<lg)+1]);
}
bool chk(int w){
	for(int i=0;i<len;++i)
	if(s[w+i]!=t[i])return s[w+i]<t[i];
	return 1;
}
int findl(int wz,int len){
	int l=1,r=wz-1,ans=wz;
	while(l<=r){
		const int mid=l+r>>1;
		if(ask(mid+1,wz)>=len)r=(ans=mid)-1;else l=mid+1;
	}
	return ans;
}
int findr(int wz,int len){
	int l=wz+1,r=n,ans=wz;
	while(l<=r){
		const int mid=l+r>>1;
		if(ask(wz+1,mid)>=len)l=(ans=mid)+1;else r=mid-1;
	}
	return ans;
}
void MD(){
	if(m==0)return;
	siz=n/sqrt(m);
	std::sort(q+1,q+Q+1);
	static int vis[N];
	for(int i=1,l=1,r=0,nw=0;i<=Q;++i){
		while(r<q[i].r)
		if(!vis[p[++r]]++)++nw;
		while(l>q[i].l)
		if(!vis[p[--l]]++)++nw;
		while(l<q[i].l)
		if(!--vis[p[l++]])--nw;
		while(r>q[i].r)
		if(!--vis[p[r--]])--nw;
		ans1[q[i].id]=nw;
	}
}
int main(){
	scanf("%d",&m);
	for(int i=1;i<=m;++i){
		scanf("%s",S[i]);
		for(int j=0;S[i][j];++j)s[++n]=S[i][j],ys[n]=i;
		s[++n]=fx++;
	}
	sort();
	init();
	scanf("%d",&Q);
	for(int i=1;i<=Q;++i){
		scanf("%s",t);
		len=strlen(t);
		int l=1,r=n,as=n+1;
		while(l<=r){
			const int mid=l+r>>1;
			if(chk(sa[mid]))l=(as=mid)+1;else r=mid-1;
		}
		bool ok=1;
		for(int i=0;i<len;++i)
		if(s[sa[as]+i]!=t[i])ok=0;
		if(!ok)q[i]=(que){1,0,i};else{
			int L=findl(as,len),R=findr(as,len);
			q[i]=(que){L,R,i};
			ans2[i]=p[as];
		}
	}
	MD();
	for(int i=1;i<=Q;++i){
		if(ans1[i])
		printf("%d %s\n",ans1[i],S[ans2[i]]);else
		puts("0 -");
	}
	return 0;
}
```

---

## 作者：huyangmu (赞：2)

首先 $n$ 和 $q$ 的范围都很大，如果每次询问都要遍历前面的 $n$ 个字串，并判断询问到的字符串是否是前面字符串的子串，时间复杂度肯定接受不了。

所以我们可以考虑预处理，因为 $len\le8$，所以可以先遍历 $n$ 个字符串，然后枚举起点，并向后遍历，并统计每个子串出现在哪个字符串中，出现了几次。

然后就可以写出如下代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q;
string s;
map<string, string> mp;
map<string, int> pos;
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i){
		cin >> s;
		for (int j = 0; j < s.size(); ++j){
			string sa = "";
			for (int k = j ; k < s.size(); ++k){
				sa += s[k];
				mp[sa] = s;
				++pos[sa];
			}
		}
	}
	cin >> q;
	while (q --){
		cin >> s;
		if (!mp.count(s)) cout << "0 -" << '\n';
		else cout << pos[s] << ' ' << mp[s] << '\n';
	} 
	return 0;
}
```
但交上去，到第二个点就错了，因为一个字符串中可能有很多相同的子串，但这个字符串只能算一次，所以还需要标记当前字符串是否出现过相同子串。
```cpp

#include <bits/stdc++.h>
#define int long long 
using namespace std;
int n, q;
string s;
map<string, string> mp;
map<string, int> pos;
map<string, bool> vis;
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i){
		cin >> s;
		vis.clear();
		for (int j = 0; j < s.size(); ++j){
			string sa = "";
			for (int k = j ; k < s.size(); ++k){
				sa += s[k];
				if (vis[sa]) continue;
				mp[sa] = s;
				++pos[sa];
				vis[sa] = 1;
			}
		}
	}
	cin >> q;
	while (q --){
		cin >> s;
		if (!mp.count(s)) cout << "0 -" << '\n';
		else cout << pos[s] << ' ' << mp[s] << '\n';
	} 
	return 0;
}


---

## 作者：Super_Builder (赞：1)

## 思路

我们第一眼看题就发现每个字符串的长度在只有 $8$。

我们需要判断的是某个字符串是不是前面字符串的子串，因为长度太小，所以可以把字符串的每一个子串放到 `map` 里，再用一个 `map` 判断一个子串是否在当前字符串出现过，出现过就不能重复记。最后在用一个 `map` 记录一下每个子串对应哪个字符串，然后这题就切了。

## AC CODE

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
map<string,int>mp;
map<string,string>mp2;
map<string,bool>mp3;
int n,m;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		mp3.clear();
		for(int i=0;i<s.size();i++){
			string tmp="";
			for(int j=i;j<s.size();j++){
				tmp+=s[j];
				if(!mp3[tmp]){
					mp3[tmp]=1;
					mp[tmp]++;
					mp2[tmp]=s;
				}
			}
		}
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		string s;
		cin>>s;
		if(!mp[s]){
			cout<<"0 -\n";
		}
		else{
			cout<<mp[s]<<" "<<mp2[s]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：1)

这题可以用 $\verb!map!$ 水过。
## 思路
我们注意到 $\verb!len!$ 居然只有 $\verb!8!$，这就意味着一个字符串所有的字串数量只有几十个，再减去重复的字串，每一个字符串的字串数可能平均只有 $\verb!20!$ 左右。一共有一万个字符串，我们显然可以开一个 $\verb!map!$ 把所有字串记录下来，然后直接查询即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
map< string,vector<string> >mp;//表示每种子串分别包含于哪几个串
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;cin>>n;
	for (rint i=1;i<=n;++i){
		string s;cin>>s;
	    int len=s.length();
	    map<string,int>mpp;//记录当前是否记录了重复的子串
	    for (rint j=0;j<len;++j)
	        for (rint k=j;k<len;++k){
	        	string s1=s.substr(j,k-j+1);
				if (mpp[s1]==0) mpp[s1]=1,mp[s1].push_back(s);
			}
	}
	int q;cin>>q;
	while (q--){
		string t;cin>>t;
		if (mp[t].size()==0) cout<<"0 -\n";
		else cout<<(int)(mp[t].size())<<' '<<mp[t][0]<<'\n';
	}
    return 0;
}
```


---

## 作者：nekko (赞：1)

对于一开始给定的 $n$ 个字符串，可以把它们的所有后缀去重后都插入到 $trie$ 中

这样在匹配的时候最后访问的点就是所有匹配的字符串了

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10010 * 215 + 10;
char str[30];
int n, m;
int cnt[N], tot = 1;
map<int, int> ch[N];
vector<int> nds;
string val[N];

void ins(int fro) {
    int x = 1;
    for(int j = fro ; str[j] ; ++ j) {
        int c = str[j] - 'a';
        if(!ch[x][c]) ch[x][c] = ++ tot;
        x = ch[x][c];
        nds.push_back(x);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", str + 1);
        nds.clear();
        for(int j = 1 ; str[j] ; ++ j) {
            ins(j);
        }
        sort(nds.begin(), nds.end());
        nds.erase(unique(nds.begin(), nds.end()), nds.end());
        for(int j = 0 ; j < nds.size() ; ++ j) {
            ++ cnt[nds[j]];
            val[nds[j]] = string(str + 1);
        }
    }
    scanf("%d", &m);
    for(int i = 1 ; i <= m ; ++ i) {
        scanf("%s", str + 1);
        int x = 1;
        for(int j = 1 ; str[j] ; ++ j) {
            int c = str[j] - 'a';
            x = ch[x][c];
        }
        if(cnt[x])
            printf("%d %s\n", cnt[x], val[x].c_str());
        else puts("0 -");
    }
}
```

---

## 作者：Dilute (赞：0)

对于这题，看到字符串匹配，第一反应想到字符串hash，同时看到$len \leq 8 $ ，考虑对于先给出的$n$个字符串，$O(len^2)$枚举它的子串，将其加入$map$中，但是要注意如果一个然后对于每个字符串，我们都统计一下它最后一次出现在哪里（于是就可以顺便判一下重）


然后我们在询问的时候，就可以直接输出这个字符串对应的出现次数以及最后一处出现的位置啦QwQ

```cpp
// Sooke bless me.
// LJC00118 bless me.
#include<bits/stdc++.h>

#define INF 2147483647
#define ll long long

int Inp(){
	char c = getchar();
	int Neg = 1;
	while(c < '0' || c > '9'){
		if(c == '-')
			Neg = -1;
		c = getchar();
	}
	int Sum = 0;
	while(c >= '0' && c <= '9'){
		Sum = ((Sum << 3) + (Sum << 1)) + c - '0';
		c = getchar();
	}
	return Neg * Sum;
}

std::map <std::string, int> Cnt; // 出现次数
std::map <std::string, int> Ans; // 最后一次出现位置
std::string s[10010];

int main(){
	int n = Inp();
	for(int i = 1; i <= n; i++){
		std::cin >> s[i];
		int Len = s[i].size();
		for(int j = 1; j <= Len; j++)
			for(int u = 0; u <= Len - j; u++){
				if(Ans[s[i].substr(u, j)] != i){
					Cnt[s[i].substr(u, j)]++;
					Ans[s[i].substr(u, j)] = i;
				}
			}
	}
	int m = Inp();
	for(int i = 1; i <= m; i++){
		std::string str;
		std::cin >> str;
		printf("%d ", Cnt[str]);
		if(Cnt[str] == 0)
			printf("-\n"); 
		else
			std::cout << s[Ans[str]] << std::endl;
	}
}
```

---

