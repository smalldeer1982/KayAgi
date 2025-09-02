# Refactoring

## 题目描述

Alice 编写了一个程序，现在她想提升代码的可读性。提升可读性的方法之一是为变量赋予有意义的名字，因此 Alice 想要重命名她程序中的一些变量。在她的 IDE 中有一个名为“批量重构”的命令，可以在一次操作中替换许多变量的名字。要使用该命令，Alice 需要选择两个字符串 $s$ 和 $t$，之后对于每个变量，执行如下算法：如果变量名中包含 $s$ 作为子串，则将第一个（且仅第一个）出现的 $s$ 替换为 $t$。如果变量名中不包含 $s$，则该变量名保持不变。

变量列表已知，对于每个变量，既给出了初始名字，也给出了 Alice 希望更改后的名字。此外，对于每个变量，初始名字和目标名字的长度是相等的（否则代码的对齐可能会被破坏）。你需要判断是否可以通过一次“批量重构”命令完成所有变量的重命名，或者判断这是不可能的。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1
topforces
codecoder
```

### 输出

```
YES
topforces
codecoder
```

## 样例 #2

### 输入

```
3
bab
cac
cdc
bdb
cdc
cdc
```

### 输出

```
YES
a
d
```

## 样例 #3

### 输入

```
2
you
shal
not
pass
```

### 输出

```
NO
```

# 题解

## 作者：Luzhuoyuan (赞：1)

Links: [[Codeforces]](http://codeforces.com/problemset/problem/1055/D) [[Luogu]](https://www.luogu.com.cn/problem/CF1055D)

搬运[官解](https://codeforces.com/blog/entry/63099)。

### 题意

给定 $n$ 个字符串 $w_i$ 和另外 $n$ 个字符串 $w'_i$，问是否存在两个字符串 $s,t$ 满足 $1\le|s|=|t|\le 5000$，且对于 $1\le i\le n$，将 $w_i$ 中的最靠左的与 $s$ 相等的子串替换为 $t$ 后与 $w'_i$ 完全相同（若没有与 $s$ 相等的子串则不改变）。若不存在输出 `NO`，否则输出 `YES` 与一组合法的 $s,t$。

- $1\le n\le 3000$；
- $1\le |w_i|=|w'_i|\le 3000$。

### 思路

首先我们忽略那些满足 $w_i=w'_i$ 的串。定义 $dif(a,b)$ 表示字符串 $a$ 去掉 $a,b$ 两个字符串的公共前后缀的部分，那么对于每个 $w_i\ne w'_i$ 的串，$dif(w_i,w'_i)$ 必然是 $s$ 的子串，$dif(w'_i,w_i)$ 必然是 $t$ 的子串，因为这一段必须被整段修改；并且对于每对 $1\le i<j\le n$ 满足 $w_i\ne w'_i,w_j\ne w'_j$，$dif(w_i,w'_i),dif(w'_i,w_i)$ 与 $dif(w_j,w'_j),dif(w'_j,w_j)$ 必须分别相等，否则必然不能通过一个 $s,t$ 把两段都修改好，这样的情况下直接输出 `NO`。

找出了每段的 $dif$ 还不够，我们发现有可能在修改的时候，某个串在本该修改的地方的前面就有一处与 $s$ 匹配了，改了不该改的东西，该改的却没改，我们要尽量避免这种情况，因此我们的 $s,t$ 越长越好。我们可以对于每个串尽量将 $s,t$ 向左右两边扩展，使 $s,t$ 还是能匹配所有 $dif$ 的同时长度尽量长。

最后得出了一组最长的 $s,t$ 后还要 check 一遍，如果 $s$ 匹配了一个 $w_i=w'_i$ 的 $w_i$，或者匹配 $w_i=w'_i$ 的串时匹配到了比应当匹配的位置更靠前的位置，那么就不合法，否则就是合法的。可以用哈希维护整段的匹配，时间复杂度 $O(\sum|w_i|)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N=3005,B=13331,mod=1e9+9;
mt19937 rnd(time(0));
int n,a[N<<1][N],sz[N],d[30],bs[N],l[N],r[N],v,v1,p,pl,pr,len;
bool fl[B];
char s[N<<1][N];
inline int hs(int x,int l,int r){return (a[x][r]-a[x][l-1]*bs[r-l+1]%mod+mod)%mod;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;v=-1;
	for(int i=1;i<=26;i++){do d[i]=rnd()%B;while(fl[d[i]]);fl[d[i]]=true;}
	bs[0]=1;for(int i=1;i<=3000;i++)bs[i]=bs[i-1]*B%mod;
	for(int i=1;i<=(n<<1);i++){
		cin>>(s[i]+1);sz[i]=strlen(s[i]+1);
		for(int j=1;j<=sz[i];j++)a[i][j]=(a[i][j-1]*B+d[s[i][j]^96])%mod;
	}
	for(int i=1;i<=n;i++)if(a[i][sz[i]]!=a[i+n][sz[i]]){
		l[i]=1;while(s[i][l[i]]==s[i+n][l[i]])l[i]++;
		r[i]=sz[i];while(s[i][r[i]]==s[i+n][r[i]])r[i]--;
		if(!~v)v=hs(i,l[i],r[i]),v1=hs(i+n,l[i],r[i]);
		else if(v!=hs(i,l[i],r[i])||v1!=hs(i+n,l[i],r[i])){cout<<"NO\n";return 0;}
	}
	if(!~v){cout<<"YES\nzyzakioi\nzyzakioi\n";return 0;}
	for(int i=1;i<=n;i++)if(l[i]){
		if(!p){p=i,pl=l[i]-1,pr=sz[i]-r[i];continue;}
		int ll=0,rr=0;
		while(ll<l[i]&&ll<pl&&s[i][l[i]-ll-1]==s[p][l[p]-ll-1])ll++;
		while(rr<sz[i]-r[i]&&rr<pr&&s[i][r[i]+rr+1]==s[p][r[p]+rr+1])rr++;
		pl=ll,pr=rr;
	}
	v=hs(p,l[p]-pl,r[p]+pr);len=r[p]+pr-l[p]+pl+1;
	for(int i=1;i<=n;i++)for(int j=1;j<=sz[i]-len+1;j++)
		if(hs(i,j,j+len-1)==v&&(!l[i]||j<l[i]-pl)){cout<<"NO\n";return 0;}
	cout<<"YES\n";
	for(int i=l[p]-pl;i<=r[p]+pr;i++)cout<<s[p][i];
	cout<<'\n';
	for(int i=l[p]-pl;i<=r[p]+pr;i++)cout<<s[p+n][i];
	cout<<'\n';
	return 0;
}
```

（逃

---

