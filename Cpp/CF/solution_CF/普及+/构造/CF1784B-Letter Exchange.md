# Letter Exchange

## 题目描述

A cooperative game is played by $ m $ people. In the game, there are $ 3m $ sheets of paper: $ m $ sheets with letter 'w', $ m $ sheets with letter 'i', and $ m $ sheets with letter 'n'.

Initially, each person is given three sheets (possibly with equal letters).

The goal of the game is to allow each of the $ m $ people to spell the word "win" using their sheets of paper. In other words, everyone should have one sheet with letter 'w', one sheet with letter 'i', and one sheet with letter 'n'.

To achieve the goal, people can make exchanges. Two people participate in each exchange. Both of them choose exactly one sheet of paper from the three sheets they own and exchange it with each other.

Find the shortest sequence of exchanges after which everyone has one 'w', one 'i', and one 'n'.

## 样例 #1

### 输入

```
3
2
nwi
inw
3
inn
nww
wii
4
win
www
iii
nnn```

### 输出

```
0
2
2 w 3 i
3 w 1 n
3
2 w 3 i
2 w 4 n
3 i 4 n```

# 题解

## 作者：AThousandSuns (赞：11)

只是想~~水~~发一篇代码逻辑清晰一点的题解。目前其它题解的代码有点混乱邪恶了。

为了方便先将 $\texttt{win}$ 分别变为 $\texttt{012}$。

建立有 $0,1,2$ 三个点的有向图，如果一个人有多余数字 $x$ 而缺少数字 $y$ 那就从 $x$ 到 $y$ 连一条有向边。

然后就是贪心交换。若同时存在边 $(x,y)$ 和 $(y,x)$ 那么直接将代表的这两个人交换。

最后只能剩下数量相等的 $(0,1)(1,2)(2,0)$ 或 $(0,2)(2,1)(1,0)$，每三条这样的边可以两次交换完成。

$\texttt{win}$ 和 $\texttt{012}$ 的转换提前开两个数组就行了。连边就是出现次数 $>1$ 的数字向出现次数 $=0$ 的连边。贪心的第一步直接枚举 $x$ 和 $y$，贪心的第二步记录 $p,q,r$ 表示存在 $(p,q)(q,r)(r,p)$ 这些边，判断下存不存在 $(0,2)$ 就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=333333,mod=998244353;
#define fi first
#define se second
#define MP make_pair
#define PB push_back
#define sz(v) (int)(v.size())
#define all(v) v.begin(),v.end()
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
inline int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
	return ans;
}
int n,ans[maxn][4],al,c[3],id[128];
char s[10],rid[3];
vector<int> vec[3][3];
void clear(){
	FOR(i,0,2) FOR(j,0,2) vec[i][j].clear();
	al=0;
}
inline void add(int a,int b,int c,int d){
	ans[++al][0]=a;
	ans[al][1]=b;
	ans[al][2]=c;
	ans[al][3]=d;
}
void solve(){
	n=read();
	FOR(i,1,n){
		scanf("%s",s);
		c[0]=c[1]=c[2]=0;
		FOR(j,0,2) c[id[s[j]]]++;
		FOR(j,0,2) FOR(k,0,2) if(c[j]>1 && c[k]<1) vec[j][k].PB(i);
	}
	FOR(i,0,2) FOR(j,0,2) while(sz(vec[i][j]) && sz(vec[j][i])){
		int x=vec[i][j].back();vec[i][j].pop_back();
		int y=vec[j][i].back();vec[j][i].pop_back();
		add(x,i,y,j);
	}
	int p=0,q=1,r=2;
	if(sz(vec[0][2])) swap(q,r);
	FOR(i,0,sz(vec[p][q])-1){
		int x=vec[p][q][i];
		int y=vec[q][r][i];
		int z=vec[r][p][i];
		add(x,p,y,q);
		add(y,p,z,r);
	}
	printf("%d\n",al);
	FOR(i,1,al) printf("%d %c %d %c\n",ans[i][0],rid[ans[i][1]],ans[i][2],rid[ans[i][3]]);
	clear();
}
int main(){
	id['w']=0;id['i']=1;id['n']=2;
	rid[0]='w';rid[1]='i';rid[2]='n';
	int T=read();
	while(T--) solve();
}
```

---

## 作者：FFTotoro (赞：6)

## 前言

赛时写了 $45\operatorname{min}$，差点把人写吐。

## 解法

本题需要使用**贪心算法**与**双指针处理技巧**。

先将所有的字符串按照 $\texttt{w}$ 个数为第一关键字，$\texttt{i}$ 个数为第二关键字排序，然后令 $l=1$，$r=n$，两个指针从两边往中间靠拢，不断将 $l$ 处有多余 $\texttt{w}$ 的字符串的 $\texttt{w}$ 从 $r$ 指向的字符串中“换”一个它有多的字母，如果不能换了就跳出。

然后再按照同样的方式排序一次，将还有多余 $\texttt{w}$ 的全部换完。

最后按照 $\texttt{i}$ 个数为关键字排序，把多余的 $\texttt{i}$ 换成 $\texttt{n}$ 即可。

实现可以借助 STL 中的多元组 `std::tuple`。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int,int> tpi;
tpi a[100001];
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  while(t--){
    int n; cin>>n;
    vector<tuple<int,char,int,char> > v;
    for(int i=1;i<=n;i++){
      string s; cin>>s;
      a[i]=make_tuple(i,count(s.begin(),s.end(),'w'),count(s.begin(),s.end(),'i'),count(s.begin(),s.end(),'n'));
      // 统计字符个数
    }
    sort(a+1,a+n+1,[](tpi x,tpi y){return get<1>(x)==get<1>(y)?get<2>(x)>get<2>(y):get<1>(x)>get<1>(y);});
    int l=1,r=n;
    while(l<r){
      if(get<1>(a[l])<2)break;
      if(get<1>(a[l])==3){
        char c; get<1>(a[l])--,get<1>(a[r])++;
        if(get<2>(a[r])>1)get<2>(a[r])--,get<2>(a[l])++,c='i';
        else get<3>(a[r])--,get<3>(a[l])++,c='n';
        v.emplace_back(get<0>(a[l]),'w',get<0>(a[r]),c);
      } // 有 3 个 w
      else if(get<1>(a[l])==2){
        char c; get<1>(a[l])--,get<1>(a[r])++;
        if(get<2>(a[r])>1)get<2>(a[r])--,get<2>(a[l])++,c='i';
        else get<3>(a[r])--,get<3>(a[l])++,c='n';
        v.emplace_back(get<0>(a[l]),'w',get<0>(a[r]),c);
      } // 有 2 个 w
      else break; // 没必要继续处理
      l++,r--;
    } // 第一轮
    sort(a+1,a+n+1,[](tpi x,tpi y){return get<1>(x)==get<1>(y)?get<2>(x)>get<2>(y):get<1>(x)>get<1>(y);});
    l=1,r=n;
    while(l<r){
      if(get<1>(a[l])<2)break;
      if(get<1>(a[l])==2){
        char c; get<1>(a[l])--,get<1>(a[r])++;
        if(get<2>(a[r])>1)get<2>(a[r])--,get<2>(a[l])++,c='i';
        else get<3>(a[r])--,get<3>(a[l])++,c='n';
        v.emplace_back(get<0>(a[l]),'w',get<0>(a[r]),c);
      }
      l++,r--;
    } // 第二轮
    sort(a+1,a+n+1,[](tpi x,tpi y){return get<2>(x)==get<2>(y)?get<3>(x)>get<3>(y):get<2>(x)>get<2>(y);});
    l=1,r=n;
    while(l<r){
      if(get<2>(a[l])<2)break;
      v.emplace_back(get<0>(a[l]),'i',get<0>(a[r]),'n');
      l++,r--;
    } // 第三轮
    cout<<v.size()<<endl;
    for(auto [a,b,c,d]:v)cout<<a<<' '<<b<<' '<<c<<' '<<d<<endl;
  }
  return 0;
}
```

---

## 作者：听取MLE声一片 (赞：3)

代码极度混乱邪恶，请谨慎观看。

首先假定 $w=1$，$i=2$，$n=3$，那么一共有这些可能，我们为他们标号。

```
1:3 0 0
2:0 3 0
3:0 0 3
4:2 1 0
5:2 0 1
6:1 2 0
7:0 2 1
8:1 0 2
9:0 1 2
```

以下把最长长度为 $3$ 的简记为“三”，最长长度为 $2$ 的简记为“二”，最长长度为 $1$ 的简记为“一”。

显然一是满足 win 条件的，不需要考虑。1~3 为三，4~9 为二。

我们定下规则，只有编号小的才能和编号大的交换，因为三一定是要先降为二的，而且定下顺序不会出现反复横跳的现象。

另一个前提是交换之后的长度和必须减少，比如三和二交换后变为二和二或三或一。如果不是，那么此次交换没有意义。

更为具体的，我们只能拿当前的一个零位去和编号靠后的一个非零位交换。当然，和二位交换必须要放在一位交换讨论的前面。

其实可以用代码写出来简化的，但是因为我比较蠢，就直接展开写的。

赛时代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=1e5+10;
int n;
string str;
vector<int>a[10],e1,e2,e3,e4;
void add(int u,int v,int w,int z){
	e1.push_back(u);
	e2.push_back(v);
	e3.push_back(w);
	e4.push_back(z);
}
int main()
{
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){
			cin>>str;
			int s1=0,s2=0,s3=0;
			for(int j=0;j<str.length();j++){
				if(str[j]=='w')s1++;
				if(str[j]=='i')s2++;
				if(str[j]=='n')s3++;
				if(s1==3)a[1].push_back(i);
				if(s2==3)a[2].push_back(i);
				if(s3==3)a[3].push_back(i);
				if(s1==2&&s2==1)a[4].push_back(i);
				if(s1==2&&s3==1)a[5].push_back(i);
				if(s2==2&&s1==1)a[6].push_back(i);
				if(s2==2&&s3==1)a[7].push_back(i);
				if(s3==2&&s1==1)a[8].push_back(i);
				if(s3==2&&s2==1)a[9].push_back(i);
			}
		}
		for(int i=0;i<a[1].size();i++){
			int x=a[1][i];
			if(!a[2].empty()){
				int y=a[2].back();
				a[2].pop_back();
				a[4].push_back(x);
				a[6].push_back(y);
				add(x,y,1,2);
				continue;
			}
			if(!a[3].empty()){
				int y=a[3].back();
				a[3].pop_back();
				a[5].push_back(x);
				a[8].push_back(y);
				add(x,y,1,3);
				continue;
			}
			if(!a[7].empty()){
				int y=a[7].back();
				a[7].pop_back();
				a[4].push_back(x);
				add(x,y,1,2);
				continue;
			}
			if(!a[9].empty()){
				int y=a[9].back();
				a[9].pop_back();
				a[5].push_back(x);
				add(x,y,1,3);
				continue;
			}
		}
		for(int i=0;i<a[2].size();i++){
			int x=a[2][i];
			if(!a[3].empty()){
				int y=a[3].back();
				a[3].pop_back();
				a[7].push_back(x);
				a[9].push_back(y);
				add(x,y,2,3);
				continue;
			}
			if(!a[5].empty()){
				int y=a[5].back();
				a[5].pop_back();
				a[6].push_back(x);
				add(x,y,2,1);
				continue;
			}
			if(!a[8].empty()){
				int y=a[8].back();
				a[8].pop_back();
				a[7].push_back(x);
				add(x,y,2,3);
				continue;
			}
		}
		for(int i=0;i<a[3].size();i++){
			int x=a[3][i];
			if(!a[4].empty()){
				int y=a[4].back();
				a[4].pop_back();
				a[8].push_back(x);
				add(x,y,3,1);
				continue;
			}
			if(!a[6].empty()){
				int y=a[6].back();
				a[6].pop_back();
				a[9].push_back(x);
				add(x,y,3,2);
				continue;
			}
		}
		for(int i=0;i<a[4].size();i++){
			int x=a[4][i];
			if(!a[9].empty()){
				int y=a[9].back();
				a[9].pop_back();
				add(x,y,1,3);
				continue;
			}
			if(!a[7].empty()){
				int y=a[7].back();
				a[7].pop_back();
				a[6].push_back(y);
				add(x,y,1,3);
				continue;
			}
			if(!a[8].empty()){
				int y=a[8].back();
				a[8].pop_back();
				a[5].push_back(x);
				add(x,y,1,3);
				continue;
			}
		}
		for(int i=0;i<a[5].size();i++){
			int x=a[5][i];
			if(!a[7].empty()){
				int y=a[7].back();
				a[7].pop_back();
				add(x,y,1,2);
				continue;
			}
			if(!a[9].empty()){
				int y=a[9].back();
				a[9].pop_back();
				a[8].push_back(y);
				add(x,y,1,2);
				continue;
			}
		}
		for(int i=0;i<a[6].size();i++){
			int x=a[6][i];
			if(!a[8].empty()){
				int y=a[8].back();
				a[8].pop_back();
				add(x,y,2,3);
				continue;
			}
		}
		cout<<e1.size()<<'\n';
		for(int i=0;i<e1.size();i++){
			int x=e1[i],y=e2[i],z=e3[i],w=e4[i];
			cout<<x<<' ';
			if(z==1)cout<<"w ";
			if(z==2)cout<<"i ";
			if(z==3)cout<<"n ";
			cout<<y<<' ';
			if(w==1)cout<<"w ";
			if(w==2)cout<<"i ";
			if(w==3)cout<<"n ";
			cout<<'\n';
		}
		for(int i=1;i<=9;i++)
			a[i].clear();
		e1.clear(),e2.clear(),e3.clear(),e4.clear();
	}
	return 0;
}

```

---

## 作者：Leasier (赞：1)

考虑每个字符串都可以表示为 $0 \sim 2$ 个“多 $a$ 少 $b$”的形式。下面简记为 $(a, b)$。

如果出现两个 $(a, b), (b, a)$，则它们可以互补，只需要一次操作就可以消去两个。

在上述操作结束后，可能还剩一些没消掉的项。不难发现剩下的项一定可以表示为若干 $(a, b), (b, c), (c, a)$，这里我们两次操作才能消去三个。

所以说先操作消两个再操作消三个一定更优。

直接分别讨论两种情况即可。不难发现最终的 $k \leq n$。

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int ansa1[100007], ansc1[100007], ansa2[100007], ansc2[100007];
char ref[7], s[7];
vector<int> v[7][7];

int main(){
	int t;
	cin >> t;
	ref[1] = 'i';
	ref[2] = 'n';
	ref[3] = 'w';
	for (int i = 1; i <= t; i++){
		int m, ansk = 0;
		cin >> m;
		for (int j = 1; j <= 3; j++){
			for (int k = 1; k <= 3; k++){
				v[j][k].clear();
			}
		}
		for (int j = 1; j <= m; j++){
			cin >> &s[1];
			sort(s + 1, s + 4);
			if (s[1] == 'i'){
				if (s[2] == 'i'){
					if (s[3] == 'i'){
						v[1][2].push_back(j);
						v[1][3].push_back(j);
					} else if (s[3] == 'n'){
						v[1][3].push_back(j);
					} else {
						v[1][2].push_back(j);
					}
				} else if (s[2] == 'n'){
					if (s[3] == 'n') v[2][3].push_back(j);
				} else {
					v[3][2].push_back(j);
				}
			} else if (s[1] == 'n'){
				if (s[2] == 'n'){
					if (s[3] == 'n'){
						v[2][1].push_back(j);
						v[2][3].push_back(j);
					} else {
						v[2][1].push_back(j);
					}
				} else {
					v[3][1].push_back(j);
				}
			} else {
				v[3][1].push_back(j);
				v[3][2].push_back(j);
			}
		}
		for (int j = 1; j <= 3; j++){
			for (int k = 1; k <= 3; k++){
				while (!v[j][k].empty() && !v[k][j].empty()){
					int a = v[j][k].back(), b = v[k][j].back();
					v[j][k].pop_back();
					v[k][j].pop_back();
					ansk++;
					ansa1[ansk] = a;
					ansc1[ansk] = j;
					ansa2[ansk] = b;
					ansc2[ansk] = k;
				}
			}
		}
		for (int j = 1; j <= 3; j++){
			for (int k = 1; k <= 3; k++){
				for (int l = 1; l <= 3; l++){
					while (!v[j][k].empty() && !v[k][l].empty() && !v[l][j].empty()){
						int a = v[j][k].back(), b = v[k][l].back(), c = v[l][j].back();
						v[j][k].pop_back();
						v[k][l].pop_back();
						v[l][j].pop_back();
						ansk++;
						ansa1[ansk] = a;
						ansc1[ansk] = j;
						ansa2[ansk] = b;
						ansc2[ansk] = k;
						ansk++;
						ansa1[ansk] = b;
						ansc1[ansk] = j;
						ansa2[ansk] = c;
						ansc2[ansk] = l;
					}
				}
			}
		}
		cout << ansk << endl;
		for (int j = 1; j <= ansk; j++){
			cout << ansa1[j] << " " << ref[ansc1[j]] << " " << ansa2[j] << " " << ref[ansc2[j]] << endl;
		}
	}
	return 0;
}
```

---

## 作者：MortisM (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Jerry-Jiang/p/17099756.html)

[题目链接](https://codeforces.com/contest/1785/problem/B)

难度：绿+。

## 题意

给定 $t$ 组 testcase，每组 testcase 如下。

有 $m$ 个长度为 3 的字符串，每个字符都是 $\text{w}$、$\text{i}$、$\text{n}$ 中的一个，一共有 $m$ 个 $\text{w}$，$m$ 个 $\text{i}$ 和 $m$ 个 $\text{n}$。

现在要求用最少次数的交换使得每个字符串都变成 $\text{w}$、$\text{i}$、$\text{n}$ 各有一个，并输出方案。

## 题解

题目本身不难，但是很有趣，感觉分数有点打低了，不过听说 CF 普遍把思维打得比较低。

最让人头疼的问题是要交换次数最小，怎么样才能保证最小？或者说什么样的取法是最优方案？

观察到有 `wwn` 和 `iin` 这种只要交换一次就能让两个都结束，肯定优先交换这种的。

将 $\text{w}$ 设为 0，$\text{i}$ 设为 1，$\text{n}$ 设为 2，则所有字符串都可以用 `012` 来表示。例如 `wwn` 是 `002`，`iin` 是 `112` 等。

分析什么样的可以一下就两个都消掉，发现是一个 $x$ 多 $y$ 少，另一个 $y$ 多 $x$ 少的情况。例如 `002` 就是 0 多 1 少，`112` 就是 1 多 0 少，所以这两个可以直接消掉。

特殊地，`000` 这种三个都是一样的就既算 0 多 1 少，也算 0 多 2 少，容易证明这样也是对的。

除了能直接消掉的就是三个一组的消了。为了书写方便，记 $x$ 多 $y$ 少的字符串用二元组 $(x,y)$ 表示。则三个一组只有两种情况：$(0,1),(1,2),(2,0)$ 和 $(1,0),(0,2),(2,1)$。

## 实现

这道题的实现每个人写出来都不一样，我觉得我写得比较简单。

把 $(x,y)$ 的字符串存到一个 `vector<int> vec[3][3]` 中的 `vec[x][y]` 里。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,n) for(int i=0;i<n;i++)
#define rept(i,n) for(int i=1;i<=n;i++)
#define repe(i,l,r) for(int i=l;i<=r;i++)
#define FOR(i,r,l) for(int i=r;i>=l;i--)
#define fi first
#define se second
#define pii pair<int,int>
#define mpr make_pair
#define pb push_back
#define sz(v) (int)(v.size())
using namespace std;
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
template<typename T>void chmax(T& a,T b){if(a<b)a=b;return;}
template<typename T>void chmin(T& a,T b){if(a>b)a=b;return;}
const int N=1e5+10;
const char ch[3]={'w','i','n'};
int n;
string s[N];
vector<int> vec[3][3];
struct answer{
	int a[2],c[2];
};
vector<answer> ans;
answer mans(int a,int b,int c,int d){
	answer res;
	res.a[0]=a;
	res.c[0]=b;
	res.a[1]=c;
	res.c[1]=d;
	return res;
}
int get(char c){
	if(c=='w')return 0;
	if(c=='i')return 1;
	return 2;
}
void solve(){
	cin>>n;
	rep(i,3)rep(j,3)vec[i][j].clear();
	rept(i,n){
		cin>>s[i];
		int x=get(s[i][0]),y=get(s[i][1]),z=get(s[i][2]);
		if(x!=y&&y!=z&&x!=z)continue;
		if(x==y&&x==z){
			if(x!=0)vec[x][0].pb(i);
			if(x!=1)vec[x][1].pb(i);
			if(x!=2)vec[x][2].pb(i);
		}
		else{
			int u;
			if(x==y||x==z)u=x;
			else u=y;
			int v=3-x-y-z+u;
			vec[u][v].pb(i);
		}
	}
	ans.clear();
	rep(i,3){
		rep(j,3){
			if(i<j){
				while(!vec[i][j].empty()&&!vec[j][i].empty()){
					int x=vec[i][j].back(),y=vec[j][i].back();
					vec[i][j].pop_back();
					vec[j][i].pop_back();
					ans.pb(mans(x,i,y,j));
				}
			}
		}
	}
	while(!vec[0][1].empty()&&!vec[1][2].empty()&&!vec[2][0].empty()){
		int x=vec[0][1].back(),y=vec[1][2].back(),z=vec[2][0].back();
		vec[0][1].pop_back();
		vec[1][2].pop_back();
		vec[2][0].pop_back();
		ans.pb(mans(x,0,y,1));
		ans.pb(mans(y,0,z,2));
	}
	while(!vec[1][0].empty()&&!vec[0][2].empty()&&!vec[2][1].empty()){
		int x=vec[1][0].back(),y=vec[0][2].back(),z=vec[2][1].back();
		vec[1][0].pop_back();
		vec[0][2].pop_back();
		vec[2][1].pop_back();
		ans.pb(mans(x,1,y,0));
		ans.pb(mans(y,1,z,2));
	}
	cout<<sz(ans)<<"\n";
	rep(i,sz(ans)){
		cout<<ans[i].a[0]<<" "<<ch[ans[i].c[0]]<<" "<<ans[i].a[1]<<" "<<ch[ans[i].c[1]]<<"\n";
	}
}
signed main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
//Jerry_Jiang
```

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1784B)

[codeforces div1](https://codeforc.es/contest/1784/problem/B)

[codeforces div2](https://codeforc.es/contest/1786/problem/D)

### 题目大意

洛谷链接。

### 思路

先将三种字母都不缺的人筛去。剩下的人可以分为六种情况：（表格中编号一栏对应我的代码中数组的编号，某人多字符 $a$ 且少字符 $b$ 用 $a \rightarrow b$ 表示）

|编号|交换字符情况|
|:-:|:-:|
|$0$|$\texttt{w} \rightarrow \texttt{i}$|
|$1$|$\texttt{i} \rightarrow \texttt{w}$|
|$2$|$\texttt{w} \rightarrow \texttt{n}$|
|$3$|$\texttt{n} \rightarrow \texttt{w}$|
|$4$|$\texttt{i} \rightarrow \texttt{n}$|
|$5$|$\texttt{n} \rightarrow \texttt{i}$|

当然，可能有人符合两种情况，分别处理即可。

从表中看出，$0$ 和 $1$ 两种情况互补，$2$ 和 $3$、$4$ 和 $5$ 也是如此。那么在处理时，对于一种情况，先找是否有人属于其互补情况，如果有，可以直接抵消，否则存起来。

在将互补情况处理好后，可能还会有如第二组样例那样形成环的情况，即剩余情况 $0$、$3$、$4$ 或 $1$、$2$、$5$。这时最多两次交换就可以消除一个环。

上述交换以情况 $0$、$3$、$4$ 为例：

情况 $3$ 需要把 $\texttt{n}$ 换成 $\texttt{w}$，恰好情况 $0$ 中多出一个 $\texttt{w}$，可以把情况 $0$ 的 $\texttt{w}$ 和情况 $3$ 的 $\texttt{n}$ 交换。于是情况 $3$ 消失，情况 $0$ 转化成了情况 $5$，就可以与情况 $4$ 抵消了。

至于查找互补情况等等内容，可以用 $6$ 个 stack 存人的编号，需要操作时直接拿一个出来就行。（这里 stack 可以换成 queue、vector 之类的，只要能存取数据就能用。）

没错的话，stack 的所有操作都是 $O(1)$ 的，整体复杂度 $O(n)$。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;char s[5];
stack<int>e[6];
struct G{
	int a,b;char c,d;
	G(){}
	G(int _1,char _2,int _3,char _4){a=_1;b=_3;c=_2;d=_4;}
}p[100010];
void solve(){
	cin>>n;k=0;
	for(int i=0;i<6;++i)while(e[i].size())e[i].pop();
	for(int i=1;i<=n;++i){
		cin>>s;
		int xa=0,xb=0,xc=0;
		for(int j=0;j<3;++j)
			xa+=s[j]=='w',xb+=s[j]=='i',xc+=s[j]=='n';
		if(xa>1&&xb<1){
			if(e[1].size()){//w->i
				p[++k]=G(i,'w',e[1].top(),'i');
				e[1].pop();
			}else e[0].push(i);
		}
		if(xa<1&&xb>1){
			if(e[0].size()){//i->w
				p[++k]=G(i,'i',e[0].top(),'w');
				e[0].pop();
			}else e[1].push(i);
		}
		if(xa>1&&xc<1){
			if(e[3].size()){//w->n
				p[++k]=G(i,'w',e[3].top(),'n');
				e[3].pop();
			}else e[2].push(i);
		}
		if(xa<1&&xc>1){
			if(e[2].size()){//n->w
				p[++k]=G(i,'n',e[2].top(),'w');
				e[2].pop();
			}else e[3].push(i);
		}
		if(xb>1&&xc<1){
			if(e[5].size()){//i->n
				p[++k]=G(i,'i',e[5].top(),'n');
				e[5].pop();
			}else e[4].push(i);
		}
		if(xb<1&&xc>1){
			if(e[4].size()){//n->i
				p[++k]=G(i,'n',e[4].top(),'i');
				e[4].pop();
			}else e[5].push(i);
		}//边输入边处理互补情况
	}
	while(e[0].size()&&e[3].size()&&e[4].size()){//w->i->n->w 的环
		int x=e[0].top(),y=e[3].top(),z=e[4].top();
		e[0].pop();e[3].pop();e[4].pop();
		p[++k]=G(x,'w',y,'n');
		p[++k]=G(x,'n',z,'i');
	}
	while(e[1].size()&&e[2].size()&&e[5].size()){//w->n->i->w 的环
//这两种环最多会出现一种，因为另一种已经被抵消了
		int x=e[1].top(),y=e[2].top(),z=e[5].top();
		e[1].pop();e[2].pop();e[5].pop();
		p[++k]=G(x,'n',y,'w');
		p[++k]=G(x,'i',z,'n');
	}
	cout<<k<<'\n';
	for(int i=1;i<=k;++i)cout<<p[i].a<<' '<<p[i].c<<' '<<p[i].b<<' '<<p[i].d<<'\n';
	return;
}
int main(){
	int t=1;cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：ztlh (赞：0)

# Solution

我们可以把所有人的**缺少**和**多余**情况存下来。可以发现：轮换的人数 $\leq 3$ 时一定是最优的。

由此，可以先两两配对，最后再进行三人的轮换。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
int T,n;
ll ans,p;
char s[5];
int mp[5][5];
vector<int> mpp[5][5];
int main(){
	scanf("%d",&T);
	while(T--){
		memset(mp,0,sizeof(mp));
		scanf("%d",&n);
		for(int i=1,s1,s2,s3;i<=n;i++){
			scanf("%s",s+1); s1=s2=s3=0;
			for(int j=1;j<=3;j++)
				if(s[j]=='w') s1++;
				else if(s[j]=='i') s2++;
				else if(s[j]=='n') s3++;
			if(s1==3){
				mp[1][2]++;
				mp[1][3]++;
				mpp[1][2].push_back(i);
				mpp[1][3].push_back(i);
			}
			else if(s1==2){
				if(s2) mp[1][3]++,mpp[1][3].push_back(i);
				else mp[1][2]++,mpp[1][2].push_back(i);
			}
			else if(s1==1){
				if(s2==2) mp[2][3]++,mpp[2][3].push_back(i);
				else if(s3==2) mp[3][2]++,mpp[3][2].push_back(i);
			}
			else{
				if(s2==0){
					mp[3][1]++;
					mp[3][2]++;
					mpp[3][1].push_back(i);
					mpp[3][2].push_back(i);
				}
				else if(s2==1)
					mp[3][1]++,mpp[3][1].push_back(i);
				else if(s2==2)
					mp[2][1]++,mpp[2][1].push_back(i);
				else{
					mp[2][1]++;
					mp[2][3]++;
					mpp[2][1].push_back(i);
					mpp[2][3].push_back(i);
				}
			}
		} // 以上是输入和存储
		ans=0;
		p=min(mp[1][2],mp[2][1]);
		ans+=p; mp[1][2]-=p; mp[2][1]-=p;
		p=min(mp[1][3],mp[3][1]);
		ans+=p; mp[1][3]-=p; mp[3][1]-=p;
		p=min(mp[2][3],mp[3][2]);
		ans+=p; mp[2][3]-=p; mp[3][2]-=p;
		ans+=2*max(mp[1][3],mp[3][1]);
		printf("%d\n",ans); // 计算答案
		while(mpp[1][3].size()&&mpp[3][1].size()){
			printf("%d w %d n\n",mpp[1][3][mpp[1][3].size()-1],mpp[3][1][mpp[3][1].size()-1]);
			mpp[1][3].pop_back();
			mpp[3][1].pop_back();
		}
		while(mpp[2][3].size()&&mpp[3][2].size()){
			printf("%d i %d n\n",mpp[2][3][mpp[2][3].size()-1],mpp[3][2][mpp[3][2].size()-1]);
			mpp[2][3].pop_back();
			mpp[3][2].pop_back();
		}
		while(mpp[1][2].size()&&mpp[2][1].size()){
			printf("%d w %d i\n",mpp[1][2][mpp[1][2].size()-1],mpp[2][1][mpp[2][1].size()-1]);
			mpp[1][2].pop_back();
			mpp[2][1].pop_back();
		} // 两人轮换
		while(mpp[1][2].size()){
			printf("%d w %d i\n",mpp[1][2][mpp[1][2].size()-1],mpp[2][3][mpp[2][3].size()-1]);
			printf("%d w %d n\n",mpp[2][3][mpp[2][3].size()-1],mpp[3][1][mpp[3][1].size()-1]);
			mpp[1][2].pop_back();
			mpp[2][3].pop_back();
			mpp[3][1].pop_back();
		}
		while(mpp[2][1].size()){
			printf("%d i %d n\n",mpp[2][1][mpp[2][1].size()-1],mpp[3][2][mpp[3][2].size()-1]);
			printf("%d n %d w\n",mpp[2][1][mpp[2][1].size()-1],mpp[1][3][mpp[1][3].size()-1]);
			mpp[2][1].pop_back();
			mpp[3][2].pop_back();
			mpp[1][3].pop_back();
		} // 三人轮换
	}
	return 0;
}
```

---

## 作者：yinhy09 (赞：0)

## 题目分析：

极其恶心人的题。

我们搞 $6$ 个 set 分别存：

1. 需要以 `w` 换 `i`。

1. 需要以 `w` 换 `n`。

1. 需要以 `i` 换 `w`。

1. 需要以 `i` 换 `n`。

1. 需要以 `n` 换 `w`。

1. 需要以 `n` 换 `i`。

然后只要 $6$ 个 set 中还有元素我们就继续模拟，对于每一次模拟，遍历 $m$ 个字符串，然后从其他的 set 里挑选一个与他交换，如果优先有能同时符合两个人需求的交换方式就选他，否则就满足一个人的需求，并且把另一人交换后的需求丢到其对应的新 set 里，一直往复。

## AC Code : 

```cpp
/*******************************
| Author:  yinhy09
| Problem: D. Letter Exchange
| Contest: Codeforces Round #850 (Div. 2, based on VK Cup 2022 - Final Round)
| URL:     https://codeforces.com/contest/1786/problem/D
| When:    2023-02-05 20:06:07
| 
| Memory:  512 MB
| Time:    4000 ms
*******************************/
 
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define multicase() ll T;scanf("%lld",&T);while(T--)
ll read()
{
	char c;
	ll x=0;
	ll f=1;
	c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f*=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
ll m;
const int maxm=1e5+10;
char a[maxm][3];
set<ll> s1,s2,s3,s4,s5,s6;
ll x,y,z;
struct Node
{
	ll x;
	char p;
	ll y;
	char q;
}op[maxm<<2];
int main()
{
	multicase()
	{
		s1.clear(),s2.clear(),s3.clear(),s4.clear(),s5.clear(),s6.clear();
		m=read();
		ll tot=0;
		for(int i=1;i<=m;i++)
		{
			cin>>a[i];
			x=(a[i][0]=='w')+(a[i][1]=='w')+(a[i][2]=='w');
			y=(a[i][0]=='i')+(a[i][1]=='i')+(a[i][2]=='i');
			z=(a[i][0]=='n')+(a[i][1]=='n')+(a[i][2]=='n');
		//	printf("%lld %lld %lld\n",x,y,z);
			if(x==2&&y==0)s1.insert(i);
			if(x==2&&z==0)s2.insert(i);
			if(y==2&&x==0)s3.insert(i);
			if(y==2&&z==0)s4.insert(i);
			if(z==2&&x==0)s5.insert(i);
			if(z==2&&y==0)s6.insert(i);
			if(x==3)s1.insert(i),s2.insert(i);
			if(y==3)s3.insert(i),s4.insert(i);
			if(z==3)s5.insert(i),s6.insert(i);
		//	printf("qwq\n");
		}
		while(s1.size()+s2.size()+s3.size()+s4.size()+s5.size()+s6.size()!=0)
		{
			for(int i=1;i<=m;i++)
			{
				if(s1.count(i)==1)
				{
					if(s3.size()!=0)
					{
						op[++tot]=(Node){i,'w',*s3.begin(),'i'};
						s1.erase(s1.begin());
						s3.erase(s3.begin());
					}
					else
					{
						op[++tot]=(Node){i,'w',*s4.begin(),'i'};
						s1.erase(s1.begin());
						s2.insert(*s4.begin());
						s4.erase(s4.begin());
					}
				}
				if(s2.count(i)==1)
				{
					if(s5.size()!=0)
					{
						op[++tot]=(Node){i,'w',*s5.begin(),'n'};
						s2.erase(s2.begin());
						s5.erase(s5.begin());
					}
					else
					{
						op[++tot]=(Node){i,'w',*s6.begin(),'n'};
						s2.erase(s2.begin());
						s1.insert(*s6.begin());
						s6.erase(s6.begin());
					}
				}
				if(s3.count(i)==1)
				{
					if(s1.size()!=0)
					{
						op[++tot]=(Node){i,'i',*s1.begin(),'w'};
						s1.erase(s1.begin());
						s3.erase(s3.begin());
					}
					else
					{
						op[++tot]=(Node){i,'i',*s2.begin(),'w'};
						s3.erase(s3.begin());
						s4.insert(*s2.begin());
						s2.erase(s2.begin());
					}
				}
				if(s4.count(i)==1)
				{
					if(s6.size()!=0)
					{
						op[++tot]=(Node){i,'i',*s6.begin(),'n'};
						s4.erase(s4.begin());
						s6.erase(s6.begin());
					}
					else
					{
						op[++tot]=(Node){i,'i',*s5.begin(),'n'};
						s4.erase(s4.begin());
						s3.insert(*s5.begin());
						s5.erase(s5.begin());
					}
				}
				if(s5.count(i)==1)
				{
					if(s2.size()!=0)
					{
						op[++tot]=(Node){i,'n',*s2.begin(),'w'};
						s2.erase(s2.begin());
						s5.erase(s5.begin());
					}
					else
					{
						op[++tot]=(Node){i,'n',*s1.begin(),'w'};
						s5.erase(s5.begin());
						s6.insert(*s1.begin());
						s1.erase(s1.begin());
					}
				}
				if(s6.count(i)==1)
				{
					if(s4.size()!=0)
					{
						op[++tot]=(Node){i,'n',*s4.begin(),'i'};
						s4.erase(s4.begin());
						s6.erase(s6.begin());
					}
					else
					{
						op[++tot]=(Node){i,'n',*s3.begin(),'i'};
						s6.erase(s6.begin());
						s5.insert(*s3.begin());
						s3.erase(s3.begin());
					}
				}
			}
		}
		printf("%lld\n",tot);
		for(int i=1;i<=tot;i++)
		{
			printf("%lld ",op[i].x);
			cout<<op[i].p<<" ";
			printf("%lld ",op[i].y);
			cout<<op[i].q<<endl;
		}
	}
	return 0;
}
```

---

## 作者：yemuzhe (赞：0)

### 简化题意

- 有 $n$ 个人和 $3n$ 张纸条，其中有 $n$ 张纸条写着 `w`，有 $n$ 张纸条写着 `i`，有 $n$ 张纸条写着 `n`。
- 把这 $3n$ 张纸条分给 $n$ 个人，每个人 $3$ 张，可能有重复的。
- 现在你可以交换任意两个人的一张纸条，问你最少需要交换多少次才能使每个人手里的纸条都能拼成 `win`？
- 有 $t$ 组测试数据，$1 \le t \le 10 ^ 4$，$1 \le n \le 10 ^ 5$，$\sum n \le 10 ^ 5$。

### 解题思路

我们可以按照每个人多余的和缺少的分为 $6$ 类：

1. 多余 `w`，缺少 `i`；
2. 多余 `w`，缺少 `n`；
3. 多余 `i`，缺少 `w`；
4. 多余 `i`，缺少 `n`；
5. 多余 `n`，缺少 `w`；
6. 多余 `n`，缺少 `i`。

这些人可能同时满足其中的 $0$ 类、$1$ 类或 $2$  类。我们可以统计每个人手中 `w`、`i`、`n` 的数量，枚举多余的和缺少的快速把编号 $i$ 加入这一类。

这样，我们得到 $6$ 个数组（代码里稍有不同），每个数组里存的是满足此类的人的编号。

显然对于满足第 $1$ 类的人和满足第 $3$ 类的人可以互相交换，满足第 $2$ 类的人和满足第 $5$ 类的人可以互相交换，满足第 $4$ 类的人和满足第 $6$ 类的人可以互相交换。

交换完这些后还可能有一些人手中的纸条不能拼成 `win`。这是因为分别满足第 $1$ 类、第 $4$ 类、第 $5$ 类的人构成了一个“环”，或者满足第 $2$ 类、第 $3$ 类、第 $6$ 类的人构成了一个“环”。每一组数据至多出现以上的一种情况。

于是对于第一种情况，我们可以先让满足第 $1$ 类的人的 `w` 与满足第 $4$ 类的人的 `i` 交换，再让满足第 $4$ 类的人的 `w` 与满足第 $5$ 类的人的 `n` 交换；对于第二种情况，我们可以先让满足第 $2$ 类的人的 `w` 与满足第 $3$ 类的人的 `i` 交换，再让满足第 $2$ 类的人的 `i` 与满足第 $6$ 类的人的 `n` 交换。

最后输出答案即可。

### AC Code

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#define N 100005
using namespace std;

const char op[] = {'\0', 'w', 'i', 'n'};

int T, n, ans, ansa[N], ansc[N], cnt[N][5];
char ansb[N], ansd[N], s[N][5];
vector <int> v[11]; // 思路的种类与代码中的种类的对应关系如下：1-2, 2-3, 3-4, 4-6, 5-7, 6-8

void add (int tx, int ty, int x, int y) // 把编号为 x 的人的 op[tx] 和编号为 y 的人的 op[ty] 交换
{
    ansa[++ ans] = x, ansb[ans] = op[tx];
    ansc[ans] = y, ansd[ans] = op[ty];
    return ;
}

int main ()
{
    scanf ("%d", &T);
    while (T --)
    {
        scanf ("%d", &n), ans = 0;
        for (int i = 1; i <= n; i ++)
        {
            scanf ("%s", s[i] + 1);
            for (int j = 1; j <= 3; j ++)
            {
                cnt[i][j] = 0; // 数组要清零，最好别用 memset
            }
            for (int j = 1; j <= 3; j ++)
            {
                cnt[i][s[i][j] == 'w' ? 1 : s[i][j] == 'i' ? 2 : 3] ++; // 统计每种纸条出现的次数
            }
            for (int j = 1; j <= 3; j ++)
            {
                for (int k = 1; k <= 3; k ++)
                {
                    if (cnt[i][j] > 1 && !cnt[i][k]) // 如果多余 op[j] 而缺少 op[k]
                    {
                        v[(j - 1) * 3 + k].push_back (i); // 这个人满足第 3(j - 1) + k 类
                    }
                }
            }
        }
        // 交换：
        while (v[2].size () && v[4].size ())
        {
            add (1, 2, v[2].back (), v[4].back ());
            v[2].pop_back (), v[4].pop_back ();
        }
        while (v[3].size () && v[7].size ())
        {
            add (1, 3, v[3].back (), v[7].back ());
            v[3].pop_back (), v[7].pop_back ();
        }
        while (v[6].size () && v[8].size ())
        {
            add (2, 3, v[6].back (), v[8].back ());
            v[6].pop_back (), v[8].pop_back ();
        }
        while (v[2].size ())
        {
            add (1, 2, v[2].back (), v[6].back ());
            add (1, 3, v[6].back (), v[7].back ());
            v[2].pop_back (), v[6].pop_back (), v[7].pop_back ();
        }
        while (v[3].size ())
        {
            add (1, 2, v[3].back (), v[4].back ());
            add (2, 3, v[3].back (), v[8].back ());
            v[3].pop_back (), v[4].pop_back (), v[8].pop_back ();
        }
        printf ("%d\n", ans);
        for (int i = 1; i <= ans; i ++)
        {
            printf ("%d %c %d %c\n", ansa[i], ansb[i], ansc[i], ansd[i]);
        }
    }
    return 0;
}
```

---

