# Kirei and the Linear Function

## 题目描述

Given the string $ s $ of decimal digits (0-9) of length $ n $ .

A substring is a sequence of consecutive characters of a string. The substring of this string is defined by a pair of indexes — with its left and right ends. So, each pair of indexes ( $ l, r $ ), where $ 1 \le l \le r \le n $ , corresponds to a substring of the string $ s $ . We will define as $ v(l,r) $ the numeric value of the corresponding substring (leading zeros are allowed in it).

For example, if $ n=7 $ , $ s= $ "1003004", then $ v(1,3)=100 $ , $ v(2,3)=0 $ and $ v(2,7)=3004 $ .

You are given $ n $ , $ s $ and an integer $ w $ ( $ 1 \le w < n $ ).

You need to process $ m $ queries, each of which is characterized by $ 3 $ numbers $ l_i, r_i, k_i $ ( $ 1 \le l_i \le r_i \le n; 0 \le k_i \le 8 $ ).

The answer to the $ i $ th query is such a pair of substrings of length $ w $ that if we denote them as $ (L_1, L_1+w-1) $ and $ (L_2, L_2+w-1) $ , then:

- $ L_1 \ne L_2 $ , that is, the substrings are different;
- the remainder of dividing a number $ v(L_1, L_1+w-1) \cdot v(l_i, r_i) + v(L_2, L_2 + w - 1) $ by $ 9 $ is equal to $ k_i $ .

If there are many matching substring pairs, then find a pair where $ L_1 $ is as small as possible. If there are many matching pairs in this case, then minimize $ L_2 $ .

Note that the answer may not exist.

## 说明/提示

Consider the first test case of example inputs. In this test case $ n=7 $ , $ s= $ "1003004", $ w=4 $ and one query $ l_1=1 $ , $ r_1=2 $ , $ k_1=1 $ . Note that $ v(1,2)=10 $ . We need to find a pair of substrings of length $ 4 $ such that $ v(L_1, L_1+3)\cdot10+v(L_2,L_2+3) $ has a remainder of $ k_1=1 $ when divided by $ 9 $ . The values $ L_1=2, L_2=4 $ actually satisfy all the requirements: $ v(L_1, L_1+w-1)=v(2,5)=30 $ , $ v(L_2, L_2+w-1)=v(4,7)=3004 $ . Indeed, $ 30\cdot10+3004=3304 $ , which has a remainder of $ 1 $ when divided by $ 9 $ . It can be shown that $ L_1=2 $ is the minimum possible value, and $ L_2=4 $ is the minimum possible with $ L_1=2 $ .

## 样例 #1

### 输入

```
5
1003004
4 1
1 2 1
179572007
4 2
2 7 3
2 7 4
111
2 1
2 2 6
0000
1 2
1 4 0
1 4 1
484
1 5
2 2 0
2 3 7
1 2 5
3 3 8
2 2 6```

### 输出

```
2 4
1 5
1 2
-1 -1
1 2
-1 -1
1 3
1 3
-1 -1
-1 -1
-1 -1```

# 题解

## 作者：yr409892525 (赞：2)

### 题解：CF1729F Kirei and the Linear Function
我们知道一个数模 $9$ 的余数和这个数的数字和模 $9$ 的余数一样。                 
先处理出每个长度为 $w$，且 $v(i,i+w-1) \bmod 9=x$ 的所有坐标。                
对于每次询问，我们都可以枚举 $v(L1,L1+w-1) \bmod 9$ 和 $v(L2,L2+w-1) \bmod 9$。                   
然后再用预处理出的坐标去更新答案。                    

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,q,t;
string s;
vector<int> p[9];
int a[N];
int main(){
    for(cin>>q;q--;){
        cin>>s>>m>>t;
        n=s.size();
        for(int i=0;i<9;i++){
            p[i].clear();
        }
        for(int i=1;i<=n;i++){
            a[i]=(a[i-1]+s[i-1]-'0')%9;
            if(i>=m) p[(a[i]-a[i-m]+9)%9].push_back(i-m+1);
        }
        for(int l,r,x,l1=2e9,l2=2e9;t--;l1=2e9,l2=2e9){
            cin>>l>>r>>x;
            for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                    if((i*(a[r]-a[l-1]+9)+j)%9==x){
                        if(i==j && p[i].size()>=2){
                            if(p[i][0]<l1 || p[i][0]==l1 && p[i][1]<l2){
                                l1=p[i][0],l2=p[i][1];
                            }
                        }
                        if(i!=j && p[i].size() && p[j].size()){
                            if(p[i][0]<l1 || p[i][0]==l1 && p[j][0]<l2){
                                l1=p[i][0],l2=p[j][0];
                            }
                        }
                    }
                }
            }
            cout<<(l1==2e9?-1:l1)<<" "<<(l2==2e9?-1:l2)<<"\n";
        }
    }
	return 0;
}
```

---

## 作者：yhylivedream (赞：2)

感觉没有蓝。

根据小学数学知，一个数模 $9$ 的余数等于其数位和模 $9$ 的余数。

对于每个查询，枚举 $v(L_1,L_1+w-1)$ 和 $v(L_2,L_2+w-1)$ 的数位和 $x,y$，判断是否满足查询条件，若满足则选最小的数位和为 $x,y$ 的 $L_1,L_2$，更新答案。

注意 $x=y$ 时，选最小值和次小值，这里比较懒直接用 vector。

考虑如何求出一段区间的数位和模 $9$，前缀和即可。

### Code

```
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 2e5 + 5;

int T, n, w, m, pre[kMaxN];
vector<int> v[9];
string s;

signed main() {
  cin.tie(0)->ios::sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> s >> w >> m, n = s.size(), s = ' ' + s;
    for (int i = 0; i < 9; i++) v[i].clear();
    for (int i = 1; i <= n; i++) pre[i] = (pre[i - 1] + s[i] - '0') % 9;
    for (int i = 1; i + w - 1 <= n; i++) {
      int val = ((pre[i + w - 1] - pre[i - 1]) % 9 + 9) % 9;
      v[val].push_back(i);
    }
    for (int l, r, k; m--;) {
      cin >> l >> r >> k;
      int l1 = 1e9, l2 = 1e9;
      int val = ((pre[r] - pre[l - 1]) % 9 + 9) % 9;
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          if ((i * val + j) % 9 == k && i == j && v[i].size() > 1) {
            if (v[i][0] < l1 || (v[i][0] == l1 && v[i][1] < l2)) l1 = v[i][0], l2 = v[i][1];
          } 
          if ((i * val + j) % 9 == k && i != j && v[i].size() && v[j].size()) {
            if (v[i][0] < l1 || (v[i][0] == l1 && v[j][0] < l2)) l1 = v[i][0], l2 = v[j][0];
          }
        }
      }
      cout << (l1 == 1e9 ? -1 : l1) << ' ' << (l2 == 1e9 ? -1 : l2) << '\n';
    }
  }
}
```

---

## 作者：StayAlone (赞：2)

### 题意

给定一个下标从 $1$ 开始的字符串 $s$。令 $v(l, r)$ 表示 $\overline{s_ls_{l + 1}s_{l + 2}\dots s_r}$（允许有前导零）。

对于每组数据，给定 $w, m$。接下来 $m$ 个询问。每个询问给定 $l, r, k$，求 $L_1,L_2$ 满足：

- $v(L_1,L_1+w-1)\times v(l,r)+v(L_2,L_2+w-1)\equiv k\pmod 9$  

- $L_1 \ne L_2$

若有多个满足的，求 $L_1$ 尽量小的；若还有多个，同时求 $L_2$ 尽量小的。   

### 思路

比较简单，基本上一眼秒了。

首先发现所有计算均在模 $9$ 意义下，由小学数学得 $\overline{a_1a_2\dots a_t}\equiv \sum\limits_{i = 1}^t a_i \pmod 9$。

由于余数的可乘性、可加性，原式中的 $v(l, r)$ 太大没有意义，直接取模 $9$ 即可。

考虑到 $v(l, r)$ 和 $k$ 均在 $0\sim 8$ 范围内（模 $9$ 后），因此可以先枚举预处理出所有情况，$\Theta(1)$ 查询。  

对于每种情况，枚举 $L_1$。接下来可以算出 $v(L_2,L_2+w-1)\bmod 9$ 的取值。  

因此先拿一个数组 $use_{i, 2}$。其中 $use_{i, 0} = \min\limits_{v(j,j+w-1)=i}j$，也就是最小的 $j$ 满足 $v(j, j + w - 1) = i$。同理，记 $use_{i, 1}$ 为它的**严格次小值**。

回到题目。枚举出 $L_1$ 后，可以简单的算出 $v(L_2,L_2+w-1)\bmod 9$ 的取值。令它为 $p$，则若 $use_{p, 0}$ 与 $L_1$ 相等，则 $L_2 = use_{p, 1}$，否则等于 $use_{p, 0}$。

因此，对于给定的 $v(l, r), k$，每一个 $L_1$ 可以找到对应的 $L_2$（无解不计）。再拿一个数组 $opt_{i, j}$ 表示 $v(l, r) = i, k = j$ 时的最小答案，每一次算出一对 $L_1,L_2$ 时去更新。  

这是第一种实现。时间复杂度 $\Theta(nq^2 + m)$，其中 $q = 9$。

[AC record](https://www.luogu.com.cn/record/87039143)

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define ptc putchar
#define il inline
#define eb emplace_back
#define mp make_pair
#define fst first
#define snd second
#define .....
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 2e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int LOGN = log2(MAXN) + 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc {
    template <typename T> il bool read(T &x)

    il int read()

    template <typename T> il bool read(pair <T, T> &x) 

    template <typename T, typename ...L>
    il bool read(T &x, L &...y)

    template <typename T> il void write(T x)

    template <typename T> il void write(T x, char ch) 

    template <typename T> il void write(pair <T, T> x) 

    template <typename T> il T my_max(const T &x, const T &y)

    template <typename T> il T my_min(const T &x, const T &y)

    template <typename T> il T lowbit(const T &x)
}
using namespace stupid_lrc;
// 奇妙缺省源......
int n, w, m, a[MAXN], s[MAXN]; string p;
pii opt[10][10]; int use[10][2];

int main() {
	for (int T = read(); T--; ) {
		cin >> p; n = p.size();
		rep1(i, 1, n) a[i] = p[i - 1] - '0', s[i] = s[i - 1] + a[i];
		read(w, m); memset(use, 0, sizeof use);
		rep1(i, 1, n - w + 1) {
			int val = (s[i + w - 1] - s[i - 1]) % 9;
			if (!use[val][0]) use[val][0] = i;
			else if (!use[val][1]) use[val][1] = i;
		}
		rep1(v, 0, 8) rep1(k, 0, 8) {
			opt[v][k] = mp(inf, inf);
			rep1(i, 1, n - w + 1) {
				int t = v * (s[i + w - 1] - s[i - 1]) % 9, fst;
				if (k >= t) fst = k - t;
				else fst = k + 9 - t;
				int ans = use[fst][0] ^ i ? use[fst][0] : use[fst][1];
				if (ans) opt[v][k] = min(opt[v][k], mp(i, ans));
			}
		}
		int l, r, k;
		while (m--) {
			read(l, r, k); int v = (s[r] - s[l - 1]) % 9;
			if (opt[v][k] == mp(inf, inf)) puts("-1 -1");
			else write(opt[v][k]), ptc('\n');
		}
	}
	rout;
}
```  

第二种方法大同小异。同样枚举 $v(l, r)$ 和 $k$。接下来直接枚举 $v(L_1, L_1 + w - 1)$ 和 $v(L_2, L_2 + w - 1)$，也是在 $0\sim 8$ 范围内。然后用上面的 $use$ 数组即可找到最小的 $L_1, L_2$，更新 $opt$ 即可。  

时间复杂度单次 $\Theta(q^4 + n + m)$，其中 $q = 9$。~~若不是 CF 的多组数据，这种方法很有希望跑到最优解啊啊啊，却比第一种方法还慢……~~

[AC record](https://www.luogu.com.cn/record/87045257)

```cpp
using namespace stupid_lrc;
int n, w, m, a[MAXN], s[MAXN]; string p;
pii opt[10][10]; int use[10][2];

int main() {
	for (int T = read(); T--; ) {
		cin >> p; n = p.size();
		rep1(i, 1, n) a[i] = p[i - 1] - '0', s[i] = s[i - 1] + a[i];
		read(w, m); memset(use, 0, sizeof use);
		rep1(i, 1, n - w + 1) {
			int val = (s[i + w - 1] - s[i - 1]) % 9;
			if (!use[val][0]) use[val][0] = i;
			else if (!use[val][1]) use[val][1] = i;
		}
		rep1(v, 0, 8) rep1(k, 0, 8) {
			opt[v][k] = mp(inf, inf);
			rep1(l, 0, 8) rep1(r, 0, 8) if ((l * v + r) % 9 == k) {
				int t1 = use[l][0], t2 = l ^ r ? use[r][0] : use[l][1];
				if (t1 && t2) opt[v][k] = my_min(opt[v][k], mp(t1, t2));
			}
		}
		int l, r, k;
		while (m--) {
			read(l, r, k); int v = (s[r] - s[l - 1]) % 9;
			if (opt[v][k] == mp(inf, inf)) puts("-1 -1");
			else write(opt[v][k]), ptc('\n');
		}
	}
	rout;
}
```

---

## 作者：chroneZ (赞：2)

## Part.1 数学基础

引理：**$x \bmod 9$的值与  $x$ 的各位数字之和 $\bmod$ $9$ 的值相等。**

证明：因为任一十进制数 $x$ 均可写作
$$a_0+a_1\cdot10+a_2\cdot10^2+\dots+a_n\cdot10^n$$

而 $10^n \equiv1\pmod9$，因此 
$$a_0+a_1\cdot10+a_2\cdot10^2+\dots+a_n\cdot10^n \equiv a_0+a_1+a_2+\dots+a_n\pmod9$$

推论：**任意两数的和/差/积的值模 $9$ 等于两数各位数字之和的和/差/积的值模 $9$**

## Part.2 分析

有了上述结论，我们可以想到计算字符串 $s$ 的前缀和，并 $O(n)$ 预处理出有哪些 $l$ 满足区间 $[l,l+w-1]$ 的和模 $9$ 为 $x$。

记前缀和数组为 $pre$ ，显然 $v(l,r)=pre[r]-pre[l-1]$ 

此时问题就变为了，给定 $a=v(l,r),k$，求字典序最小的 $L_1,L_2$ 使得 $L_1\neq L_2$ 且 $a\cdot v(L_1,L_1+w-1)+v(L_2,L_2+w-1) \equiv k \pmod9$

接下来暴力枚举 $0\sim 8$ 中所有可能的 $v(L_1,L_1+w-1)$ 即可，此时 $L_2$ 为满足 $v(L_2,L_2+w-1)\equiv k-a*v(L_1,L_1+w-1)\pmod9$ 的最小值。

## Part.3 Code
```cpp
const int MAXN=2e5+5;
int n,w,m,l,r,k;
int pre[MAXN];
std::vector<int> vec[10];
void solve(){
	string s;
	cin>>s>>w>>m;
	n=s.length();
	for(register int i=0;i<9;++i) vec[i].clear();
	for(register int i=0;i<n;++i){
		pre[i+1]=pre[i]+s[i]-'0';
		if(i+1-w>=0) vec[(pre[i+1]-pre[i+1-w])%9].push_back(i+2-w);
        //处理定长区间
	}
	while(m--){
		cin>>l>>r>>k;
		int x=(pre[r]-pre[l-1])%9;
		int ans1=INF,ans2=INF;
		for(register int i=0;i<9;++i){
			if(vec[i].empty()||vec[((k-i*x)%9+9)%9].empty()) continue;
			if(((k-i*x)%9+9)%9==i&&vec[i].size()==1) continue;
           	//注意要特判L1==L2的情况
			if(vec[i][0]<ans1){
				if(((k-i*x)%9+9)%9==i) ans1=vec[i][0],ans2=vec[i][1];
				else ans1=vec[i][0],ans2=vec[((k-i*x)%9+9)%9][0];
			}
		}
		if(ans1==INF) cout<<"-1 -1\n";
		else cout<<ans1<<" "<<ans2<<'\n';
	}
}
```

---

## 作者：lgx57 (赞：1)

这是蓝？？？？？？

首先把 $v(l,r)$ 转化成 $(\sum_{i=l}^r s_i) \bmod 9$。然后前缀和预处理，后面可以 $O(1)$ 查询。

考虑到 $w$ 固定，所以把所有长度为 $w$ 的子串的 $v$ 值插入到一个 map 中。然后暴力枚举 $v(L_1,L_1+w-1)$ 和 $v(L_2,L_2+w-1)$ 的值，判断是否满足条件，然后更新答案即可。

注意需要在 map 中插入 $2$ 个数：最小值和次小值，因为可能会出现 $v(L_1,L_1+w-1)=v(L_2,L_2+w-1)$ 的情况，这时不能取相同的 $L$ ，所以要用最小值和次小值。

```cpp
int query(int l,int r){
	return (sum[r]-sum[l-1]+9)%9;// 前缀和查询
}
void sol(){
	string s;
	cin>>s;
	int n=s.size();
	s=" "+s;
	for (int i=1;i<=n;i++){
		sum[i]=sum[i-1]+s[i]-'0';
		sum[i]%=9;
	}
	int len,q;
	cin>>len>>q;
	map<int,pii> mp;
	for (int i=1;i+len-1<=n;i++){
		int x=query(i,i+len-1);
		if (!mp.count(x)) mp[x]={i,0};
		else if (mp[x].se==0) mp[x].se=i;
	}
//	for (pair<int,pii> kk:mp) cout<<kk.fi<<' '<<kk.se.fi<<' '<<kk.se.se<<endl;
	while (q--){
		int l,r,x;
		cin>>l>>r>>x;
		int num=query(l,r);
		int ans1=1e9,ans2=1e9;
		for (int _=0;_<9;_++){
			for (int __=0;__<9;__++){
				if (!mp.count(_)) continue;
				if (!mp.count(__)) continue;
				if ((_*num%9+__)%9==x){
					if (_==__&&mp[_].se==0) continue;//相等却只有一个数不能取
					int xx=mp[_].fi;
					int yy=(_==__?mp[_].se:mp[__].fi);//相等时要取次小值
//					cout<<"!!! "<<_<<' '<<__<<' '<<xx<<' '<<yy<<endl;
					if (xx<ans1) ans1=xx,ans2=yy;
					else if (xx==ans1) ans2=min(ans2,yy);
				}
			}
		}
		if (ans1==1e9&&ans2==1e9) cout<<-1<<' '<<-1;
		else cout<<ans1<<" "<<ans2;
		cout<<endl;
    }
}
```

---

## 作者：yingkeqian9217 (赞：1)

## 前言

~~这是我见过最水的蓝题~~，好吧可能是我太菜了（（

## 题目大意

给一个对于 $v( l,r  ) $ 的定义:允许存在前导“$0$"的 $s_l \sim s_r $ 这一串数字。

有 $m$ 次询问，每次三个数: $l,r,k$。寻找两个子串 $\left ( L_{1}, L_{1}+w-1 \right ) $ 和 $\left ( L_{2}, L_{2}+w-1 \right )$ 且满足:

- $L_{1}\ne L_{2}$

- $( v( L_{1},  L_{1}+w-1) \cdot  v ( l,r )+v( L_{2},  L_{2}+w-1 )) \bmod 9=k$

可能出现多组答案，先保证 $L_{1}$ 最小，其次再保证 $L_{2}$ 最小。

## 分析

看到 $\bmod 9$，根据小学数学就能知道，我们只需要维护所谓 $v(l,r)$ 的数位之和对 9 的取余即可，具体可以使用前缀和实现。

然后因为 $w$ 已经告诉了你，所以我们可以进行一个预处理——把所有区间长度为 $w$ 的区间和对 9 的模存下来，可以用桶，保留开头 $i$。

于是，问题变成了：已知 $x=v(l,r)$，$k$，求两个值 $x_1,x_2\in [0,9]$，使得 $(x\times x1+x2)\bmod 9= k$，我们枚举即可。找到解之后判断桶中是否存在（注意相同要特判），存入答案序列。

要注意的是，题目需要我们输出的是区间开头坐标，而且还要取那个最小的。所以我们在对桶存储的过程中要保留最小坐标与次小坐标。最后将答案序列排序。

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define inf INT_MAX
#define maxn 2900001
using namespace std;
int T,n,m,w,a[maxn],s[maxn];
char c[maxn];
struct Num{//桶
	int sum=0,minn=inf,cmin=inf;//分别为个数，最小坐标，次小坐标
	void init(){sum=0,minn=inf,cmin=inf;}
	void insert(int x){
		sum++;
		if(x<minn){//最小次小处理
			cmin=minn;
			minn=x;
		}
		else if(x<cmin) cmin=x;
	}
}t[290];
void solve(){
	int l,r,k;
	vector<pair<int,int>>v;//答案序列
	scanf("%d%d%d",&l,&r,&k);
	int x=(s[r]+9-s[l-1])%9;
	for(int i=0;i<9;i++)
	 if(t[i].sum){
		for(int j=0;j<9;j++)
		 if((i*x+j)%9==k){//是一个解
	  		if(i==j&&t[i].sum>1)//特判，不能重复
			 v.push_back({t[i].minn,t[i].cmin});
	  		else if(i!=j&&t[j].sum)
			 v.push_back({t[i].minn,t[j].minn});
  		 }
	 }
	sort(v.begin(),v.end());//排序后输出，其实也可以直接遍历取最小解
	if(v.size()) printf("%d %d\n",v[0].first,v[0].second);
	else printf("-1 -1\n");
}
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%s\n",c);
		n=strlen(c);
		for(int i=0;i<9;i++) t[i].init();//初始化
		for(int i=0;i<n;i++)
      a[i+1]=c[i]-'0',s[i+1]=(s[i]+a[i+1])%9;//前缀和
		scanf("%d%d",&w,&m);
		for(int i=1;i+w-1<=n;i++)//边界判定
		 t[(s[i+w-1]+9-s[i-1])%9].insert(i);//预处理
		while(m--){solve();}
	}
	return 0;
}
```

---

## 作者：孤芒星河233 (赞：1)

# CF1729F Kirei and the Linear Function


[CF题面](https://codeforces.com/problemset/problem/1729/F)
[洛谷题面](https://www.luogu.com.cn/problem/CF1729F)

## 题意
  
  有 $T$ 组数据。给你一个长度为 $n$ 十进制的数字串 $s$和整数 $w$。定义s的一个**子串**的价值为 $ v(l,r)=$ $l$ ~ $r$ 的数字大小，$1\leq l \leq r\leq n $

  例如 $ n=7,s=1003004 $，则 $v(1,3)=100,v(2,3)=0,v(2,7)=3004$

  处理 $m$ 个询问，第 $i$ 个询问对应三个整数 $l_i,r_i,k_i(1\leq l_i \leq r_i\leq n,0\leq k_i \leq 8)$，找到一组 $L_1,L_2(L_1 \neq L_2 )$，使得
  $$ v(L_1,L_1+w-1)\cdot v(l_i,r_i)+v(L_2,L_2+w-1) \equiv k_i \pmod 9 $$
  无解输出两个 $-1$，有解则输出 $L_1$ 最小的解，若有多组数据满足 $L_1$ 最小，输出 $L_2$ 最小的解

  数据范围：$1\leq T\leq 10^4,1\leq n\leq 2\cdot 10^5,1\leq m\leq 2\cdot 10^5$，$T$ 组数据中所用的 $n,m$ 之和均不超过 $2\cdot 10^5$

## 思路

  因为有我们有模 $9$的条件，可以快速预处理出所有的 $v(i,i+w-1)\bmod 9,i\in [1,n-w+1]$，但处理询问的 $v(l_i,r_i)$ 仍会让复杂度超标。
  
  但 $9$ 是一个及其特殊的模数，设一个整数 $x$，那么 $x \equiv x$ 的**各位数字之和** $\pmod 9$，因此只需要算出每一位数的**前缀和**就能快速算出所有的 $v(l,r),1\leq l\leq r\leq n$

  解决的计算 $v(l,r)$ 的问题之后，还需要知道怎么快速找到满足条件的 $L_1,L_2$ ，暴力需要两层枚举，明显不行。我们又可以从模 $9$ 的角度出发，处理出的 $v(l,r)$ 满足 $v(l,r)\in [0,8]$，只用两层循环 $0$ ~ $8$ 中满足条件的数就行了，这样询问就控制在了 $O(1)$

  预处理时记录 $v(i,i+w-1)$ 模 $9$ 后的数第一次出现的位置 $f[v(i,i+w-1)]$ 和第二次出现的位置 $g[v(i,i+w-1)]$。为什么要记录这个 $g[i]$ 呢？因为当取的两个数相同时，需要不同的 $L_1,L_2$。询问时枚举 $0$ ~ $8$ 中出现过的数，满足条件则记录答案。

## 代码

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;

  const int N=2e5+9;
  int T,w,m,a[N],f[10],g[10];
  char s[N];

  int get(char c){
      return c-'0';
  }
  int v(int l,int r){
      return ((a[r]-a[l-1])%9+9)%9;//防止负数
  }

  int main(){
      scanf("%d",&T);
      while(T--){
          memset(f,0,sizeof(f));
          memset(g,0,sizeof(g));
          scanf("%s",s+1);
          int n=strlen(s+1);
          scanf("%d%d",&w,&m);
          for(int i=1;i<=n;i++) a[i]=(a[i-1]+get(s[i]))%9;//前缀和
          for(int i=1;i<=n-w+1;i++){//预处理
              int x=v(i,i+w-1);
              if(!f[x]) f[x]=i;
              else if(!g[x]) g[x]=i;
          }
          int l,r,k;
          while(m--){
              bool flag=1;
              scanf("%d%d%d",&l,&r,&k);
              int x=v(l,r),ans1=N,ans2=N;
              for(int i=0;i<9;i++){
                  for(int j=0;j<9;j++){
                      if(f[i]&&f[j]&&(x*i+j)%9==k){//出现过且满足条件
                          if(i!=j){//特判一下i=j的时候
                              //按照题意模拟就行
                              if(ans1>f[i]) ans1=f[i],ans2=f[j];
                              else if(ans1==f[i]&&ans2>f[j]) ans2=f[j];
                              flag=0;
                          }
                          else{
                              if(!g[i]) continue;
                              if(ans1>f[i]) ans1=f[i],ans2=g[j];
                              else if(ans1==f[i]&&ans2>g[j]) ans2=g[j];
                              flag=0;
                          }
                      }
                  }
              }
              if(flag) printf("-1 -1\n");
              else printf("%d %d\n",ans1,ans2);
          }
      }
      return 0;
  }
  ```

---

## 作者：QWQ_123 (赞：0)

考虑预处理哈希，然后用数组存每个哈希值模 $9$ 为 $i$ 的下标。

然后每次就枚举 $v(L_1, L_1 + w - 1) \bmod 9$ 是多少，然后判断即可。

多测清空。

```cpp
#include <bits/stdc++.h>

using namespace std;

int T;
int w, m;
char s[200010];
int sum[200010], power10[200010];
vector<int> ma[20];

int Get_Hash(int l, int r) {
	return (((sum[r] - sum[l - 1] * power10[r - l + 1]) % 9) + 9) % 9;
}

int main() {
	scanf("%d", &T);
	for (int Tc = 1; Tc <= T; ++Tc) {
		for (int i = 0; i < 9; ++i) ma[i].clear();
		scanf("%s", s + 1);
		scanf("%d%d", &w, &m);
		int n = strlen(s + 1);
		power10[0] = 1;
		for (int i = 1; i <= n; ++i) {
			sum[i] = (sum[i - 1] * 10 + s[i] - '0') % 9;
			power10[i] = power10[i - 1] * 10 % 9;
		}

		for (int i = 1; i <= n - w + 1; ++i) {
			ma[Get_Hash(i, i + w - 1)].push_back(i);
		}

		for (int i = 1; i <= m; ++i) {
			int l, r, k; scanf("%d%d%d", &l, &r, &k);
			int t = Get_Hash(l, r);
			pair<int, int> ans = {-1, -1};
			for (int j = 0; j < 9; ++j) {
				if (!ma[j].size()) continue;
				int t1 = (9 - (j * t) % 9 + k) % 9;
				if (t1 != j) {
					if (ma[t1].size()) {
						if (ma[j][0] < ans.first || ans.first == -1) ans = {ma[j][0], ma[t1][0]};
						else if (ma[j][0] == ans.first && ma[t1][0] < ans.first) ans = {ma[j][0], ma[t1][0]}; 
					}
				} else {
					if (ma[j].size() >= 2) {
						if (ma[j][0] < ans.first || ans.first == -1 || (ma[j][0] == ans.first && ma[j][1] < ans.second)) ans = {ma[j][0], ma[j][1]};
					}
				}
			}
			
			printf("%d %d\n", ans.first, ans.second);
		}
	}
	return 0;
}
```

---

## 作者：lyt_awa (赞：0)

## 题意
[<传送门>](https://www.luogu.com.cn/problem/CF1729F)
## 解析
### 前置数学知识
### $\overline{a_1a_2\cdots a_n} \equiv a_1+a_2+\cdots+a_n \pmod{9}$

证明（比较简略因为不是重点）：

$\because\overline{a_1a_2\cdots a_n} = a_1\times 10^{n-1} + a_2\times 10^{n-2}+\cdots+a_i\times 10^{n-i}+\cdots +a_n$

又 $\because 10^{i} \equiv 1 \pmod{9} ,i\in N.$

$\therefore \overline{a_1a_2\cdots a_n} \equiv a_1\times 10^{n-1}+\cdots+a_i\times 10^{n-i}+\cdots +a_n \equiv a_1+a_2+\cdots+a_n \pmod{9}$

证毕。

于是 $v(l,r)\equiv \overline{s_l\cdots s_r} \equiv s_l+\cdots +s_r\pmod{9}$ $v(l,r)$ 变为了区间和。
### 暴力
对于每一个询问我们先 _暴力 for 循环_ 求出 $v(l,r)$ 再枚举 $l_1$ 然后 _暴力 for 循环_ 求出 $v(l_1,l_1+w-1)$，然后枚举 $l_2,l_2 \ne l_1$  _暴力 for 循环_ 求出 $v(l_2,l_2+w-1)$ 最后再判断是否满足 $v(l_1,l_1+w-1)\cdot v(l,r)+v(l_2,l_2+w-1)\equiv k \pmod{9}$ 更新答案即可。
### 优化 1
其实你可能早就发现 _斜体的地方_ 都可以通过**预处理一个前缀和数组 $p$** 于是 $v(l,r) \equiv p_r-p_{l-1} \pmod 9$，但这样优化还不够，于是就有了优化 2。
### 优化 2
由于每一次要枚举的区间的区间长度是固定的 $w$。所以我们又可以对于每一个区间长度为 $w$ 的区间的左端点 $l$ 进行 **hash**（hash 值为 $v(l,l+w-1) \bmod 9$），然后枚举一个 $i$：

$i \equiv v(l_1,l_1+w-1)\pmod 9$

再计算出一个 $j$：

$j \equiv v(l_2,l_2+w-1)\equiv k - v(l_1,l_1+w-1)\cdot v(l,r) \equiv k - i\cdot v(l,r) \pmod{9}$

再在 hash 值为 $j$ 的表中找到最小的 $l_2$（$l_2 \ne l_1$）更新答案即可。
## $code$
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;

inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int t, n, w, m, l, r, k, p[N];
vector<int> v[9];
char s[N];

int main() {
	t = read();
	while (t--) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		w = read(); m = read();
		p[0] = 0;
		for (int i = 0; i < 9; ++i) v[i].clear();
		for (int i = 1; i <= n; ++i) {
			p[i] = (p[i - 1] + (s[i] ^ 48)) % 9;
			if (i >= w) v[(p[i] - p[i - w] + 9) % 9].push_back(i - w + 1);
		}
		while (m--) {
			l = read(); r = read(); k = read();
			int l1 = -1, l2 = -1, a = (p[r] - p[l - 1] + 9) % 9;
			for (int i = 0; i < 9; ++i) {
				int j = (k - i * a % 9 + 9) % 9;
				if (v[i].size() && v[j].size()) {
					if (i == j) {
						if ((v[j].size() > 1) && (l1 == -1 || l1 > v[i][0] || l1 == v[i][0] && l2 > v[j][1]))
							l1 = v[i][0], l2 = v[j][1];
					}
					else if (l1 == -1 || l1 > v[i][0] || l1 == v[i][0] && l2 > v[j][0]) l1 = v[i][0], l2 = v[j][0];
				}
			}
			printf("%d %d\n", l1, l2);
		}
	}
	return 0;
}
```

---

## 作者：lrqlrq250 (赞：0)

~~这难度绝对没有 1900 啊？？？~~

## 解题思路
我们小学应该都学过，一个数模 $9$ 的余数等于这个数各个数位之和模 $9$ 的余数。

因此对于一个 $v(l, r) \bmod 9$，我们可以直接维护 $(\sum_{i = l}^{r} a[i]) \bmod 9$ 的值。

这个可以用前缀和 $O(n)$ 求出。

然后我们再 $O(n)$ 求出每一个长度为 $w$ 的区间模 $9$ 的余数，将它们按照余数分别压入 $9$ 个 `vector` 中，因为我们是根据从左到右的顺序将各个区间插入的，所以对于每个 `vector`，其中的区间左端点一定是单调递增的，也就是 `v[k][0]` 就是所有模 $9$ 余 $k$ 的区间中左端点最小的，满足输出的条件。

对于每个询问，我们先直接枚举 $v(L_1, L1 + w - 1) \bmod 9$ 的余数，然后因为 $k$ 和 $v(l, r) \bmod 9$ 都是固定的，所以根据这几个数就可以算出 $v(L_2, L_2 + w - 1) \bmod 9$ 的值了。

然后若这两个数不相等，则分别取 `v` 中余数为这两个数的第一个，作为备选答案。

若这两个数相等，则从 `v` 中这个余数的 `vector` 中取出前两个组成备选答案。

然后将所有备选答案排序，输出最小即可。

对于每个询问最大是 $O(9 \log 9)$ 的，也就近似于 $O(1)$ 了。

所以整体是大常数的 $O(n + m)$，通过绰绰有余。

## AC Code
```cpp
#include <bits/stdc++.h>
#define max(x, y) (x) > (y) ? (x) : (y)
using namespace std;
char s[200001];
int sum[200001], n, w, m;
vector<pair<int, int> > v[9];
vector<pair<int, int> > ans;

inline int query(int l, int r){
	return (sum[r] - sum[l - 1] + 9) % 9;
}

int main(){
	int t, l, r, k;
	scanf("%d", &t);
	while (t--){
		scanf("%s", s + 1);
		n = strlen(s + 1);
		sum[1] = (s[1] - '0') % 9;
		for (int i=2; i<=n; i++) sum[i] = (sum[i - 1] + s[i] - '0') % 9;
		scanf("%d%d", &w, &m);
		for (int i=1; i+w-1<=n; i++) v[query(i, i + w - 1)].push_back(make_pair(i, i + w - 1));
		while (m--){
			scanf("%d%d%d", &l, &r, &k);
			int vlr = query(l, r), vl1, vl2;
			for (int vl1=0; vl1<9; vl1++){//枚举v(L1, L1 + w - 1) % 9
				vl2 = (vl1 * vlr <= k) ? (k - vl1 * vlr) % 9 : (k - vl1 * vlr + 9 * 9) % 9;
				if (vl1 != vl2 && v[vl1].size() && v[vl2].size()) ans.push_back(make_pair(v[vl1][0].first, v[vl2][0].first));
				if (vl1 == vl2 && v[vl1].size() >= 2) ans.push_back(make_pair(v[vl1][0].first, v[vl1][1].first));
			}
			if (!ans.size()){printf("-1 -1\n"); continue;}
			stable_sort(ans.begin(), ans.end());
			printf("%d %d\n", ans[0].first, ans[0].second);
			ans.clear();
		}
		for (int i=0; i<9; i++) v[i].clear();
		memset(sum, 0, sizeof(sum));
	}
	return 0;
}
```

PS：由于洛谷 RMJ 正在维护，Codeforces 上的 AC 记录在[这里](https://codeforces.com/contest/1729/submission/175340594)

---

