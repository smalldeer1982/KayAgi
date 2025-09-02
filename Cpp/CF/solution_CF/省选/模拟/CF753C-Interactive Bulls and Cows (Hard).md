# Interactive Bulls and Cows (Hard)

## 题目描述

**本题是一道交互题。**

你需要与交互库玩一个猜数游戏。

首先，交互库随机生成一个**四个数位互不相同**的四位数。你需要尝试猜出这个数。

每次你可以询问一个数，交互库可以告诉你这个数与答案的差异：

- 具体地，记答案为 $s$，你询问的数字为 $x$；

- 令 $A$ 类数码为对于某个位置 $i(1\le i\le 4)$ 使得 $s_i=x_i$（这里的 $s_i$ 表示 $s$ 的第 $i$ 位，$x$ 同理）的 $i$，其数量记为 $a$；

- 令 $B$ 类数码为对于某两个位置 $i,j(1\le i\le j\le 4)$ 使得 $s_i=x_j,i \neq j$ 的 $(i,j)$，其数量记为 $b$；

- 交互库会告诉你 $a$ 和 $b$ 的值。

例如：答案为 $2139$，所猜的数字 $1239$，则交互库会返回 $a=2$ 和 $b=2$。其中，$A$ 类数码为 $3,9$，$B$ 类数码为 $1,2$。

**您最多有 $7$ 次询问机会。**

## 样例 #1

### 输入

```
0 1
2 0
1 1
0 4
2 1
4 0
```

### 输出

```
8000
0179
3159
3210
0112
0123```

# 题解

## 作者：丛雨 (赞：2)

## 题目大意
> 本题为交互题，初始时有一个长度为4无重复数字出现的数字串，你每次询问一个长度为4的数字串（可出现重复数字），将返回相同位置上2串数字相同的数量，以及2串共同出现但出现位置不同的数的个数

## 分析
> 本题和那些构造的交互题有点区别，会发现难以找到合理的构造方法，但发现情况数只有$9*8*7*6=5040$种,故考虑搜索/枚举/贪心

## 做法
> 感性分析，贪心地每次选择在最坏情况下询问后可行情况最少的进行询问，可将期望询问次数降到最低，具体内容见代码

献上我~~丑陋~~码风极佳的代码

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
# define read read1<int>()
# define Type template<typename T>
Type inline const T read1()
{
    T m=0;
    char k=getchar();
    while(('0'>k||k>'9')&&(k!='-'))k=getchar();
    const bool f=(k=='-'?1:0);
    if(f)k=getchar();
    while('0'<=k&&k<='9')m=(m<<3)+(m<<1)+(k^48),k=getchar();
    return f?-m:m;
}
struct X{
    int x,v;
    int Get(int n){return (int)(x/pow(10,n-1))%10;} 
    bool operator <(X b){return v!=b.v?v<b.v:x<b.x;}
    int Same(X v){//同位同值的
        int t=0;
        for(int i=1;i<=4;++i)
            t+=Get(i)==v.Get(i);
        return t;
    }
    int Have(X v){//异位同值的
        int have[10]={},t=0;
        for(int i=1;i<=4;++i)
            ++have[Get(i)];
        for(int i=1;i<=4;++i)
            t+=have[v.Get(i)];
        return t-Same(v);
    }
}a[5045];
int cnt=-1;bool vis[10];
void dfs(int n,int v){//初始情况
    if(!n)a[++cnt].x=v;
    else for(int i=0;i<10;++i)
        if(!vis[i]){
            vis[i]=1;
            dfs(n-1,v*10+i);
            vis[i]=0;
        }
}
int fu;
bool change(){
    if(fu){//按询问后最坏情况下剩余可行解从小到大排序
        for(int i=0;i<=cnt;++i)
            a[i].v=0;
        for(int i=0;i<=cnt;++i){//获取询问后最坏情况下剩余可行解
            int tm[5][5]={};
            for(int j=0;j<=cnt;++j)
                ++tm[a[i].Same(a[j])][a[i].Have(a[j])];
            for(int j=0;j<5;++j)
                for(int k=0;j+k<5;++k)
                    a[i].v=max(a[i].v,tm[j][k]);
        }
        sort(a,a+cnt+1);
    }
    ++fu;
    printf("%04d\n",a[0].x);
    fflush(stdout);
    int n=read,f=read;
    X tem=a[0];
    if(n==4)return 0;
    for(int i=0;i<=cnt;++i)//删去不可行的解
        if(tem.Same(a[i])!=n||tem.Have(a[i])!=f){
            if(i!=cnt)swap(a[i],a[cnt]);
            --cnt;--i;
        }
    return 1;
}
int main(){
    dfs(4,0);
    while(change());
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

信息熵入门。也算是 [P8079 [WC2022] 猜词](https://www.luogu.com.cn/problem/P8079) 的前置版本了。

---------------

考虑用信息熵公式衡量每次猜测数 $x$ 的信息量：

$$
H(x)=-\sum\limits_{S} p_S\log_2 p_S
$$

其中 $S$ 表示某种返回值情况下剩余的答案集，$p_S$ 表示它占据原答案集的大小，即条件概率。我们对所有可能的返回值产生的 $S$ 用上述公式进行求和即可算出信息熵。

初状态无需计算信息熵，我们直接输出 `0123`，之后我们直接在每个状态下都选择信息熵最大的进行猜测就行了。

然而我们不能够每次都对所有的 $10^4$ 种猜测都重算信息熵，时间限制不够。所以我们可以考虑前几次尝试只从当前剩下的可选数中进行决策，几次之后可以成为答案的数的数量会迅速缩小，我们就可以遍历 $10^4$ 种猜测暴力重算信息熵了。

从第四次猜测开始对所有决策暴力重算信息熵就可以通过。

```cpp
vector <string> s;
string p[10000];
bool satisfy(string x,string g,int a,int b){
	a-=(x[0]==g[0]);
	a-=(x[1]==g[1]);
	a-=(x[2]==g[2]);
	a-=(x[3]==g[3]);
	if(a) return 0;
	fr1(i,0,3){
		if(x[i]==g[i]) continue;
		fr1(j,0,3){
			if(x[i]==g[j]){
				b--;
				break;
			}
		}
	}
	if(b) return 0;
	return 1;
}
double getH(string j){
	double H=0;
	fr1(a,0,4){
		fr1(b,0,4){
			int sz=0;
			for(auto k:s){
				if(satisfy(k,j,a,b)) sz++;
			}
			if(!sz) continue;
			double p=sz/(double)(s.size());
			H+=-p*log2(p);
		}
	}
	return H;
}
int main(){
#ifdef Shun
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	fr1(i,0,9999){
		string t=to_string(i);
		while(t.length()!=4) t='0'+t;
		fr1(j,0,3){
			fr1(k,j+1,3) if(t[k]==t[j]) goto label;
		}
		s.pb(t);
		label:
		p[i]=t;
	}
	fr1(i,1,8){
		if(s.size()==1) return cout<<s[0]<<endl,0;
		double maxn=-1;
		string id="0123";
		if(i>1&&i<=3){
			for(auto j:s){
				double H=getH(j);
				if(H>maxn) maxn=H,id=j;
			}
		}
		else if(i>1){
			fr1(j,0,9999){
				double H=getH(p[j]);
				if(H>maxn) maxn=H,id=p[j];
			}
		}
		cout<<id<<endl;
		int a,b;
		cin>>a>>b;
		vector <string> t;
		for(auto k:s){
			if(satisfy(k,id,a,b)) t.pb(k);
		}
		s=t;
	}
	ET;
}
//ALL FOR Zhang Junhao.
```

---

## 作者：This_Rrhar (赞：1)

信息论入门题。

考虑猜测一个数字 $n$，交互库可能的所有返回为集合 $\text{result}$，其信息熵为

$$
H(n)=-\sum\limits_{x\in\text{result}}p(x)\log_2p(x)
$$

每次在 $S$ 中选出信息熵最大的数字进行猜测就行了。

但是当你兴冲冲地写了代码运行时，会发现第一次询问还没跑出来就超时了。

注意到第一次询问的数是固定的，即 $0123$，所以直接输出即可。

此时再交会发现 #179 需要 $8$ 次询问，超出了限制。

由于 #179 的答案是 $0932$，所以我们可以把程序修改为第一次询问 $0932$，这样就可以通过了。

此处补充两个问题：

- 为什么这样可以通过？直觉上看，各位均不相同的数字在分布上是近似均匀的，因此每个数字所得到的信息熵是差不多的，进一步地，询问次数也是差不多的。

- 为什么每次询问的数字不是任意四位数而是 $S$ 中的数字？你可能做过 [P8079 [WC2022] 猜词](https://www.luogu.com.cn/problem/P8079)，那题每次询问的单词是在**全集**而非 $S$ 中选择的，在此题使用这个做法不能通过。经过测试，P8079 中第一次询问能够获得 $5\sim6\operatorname{bit}$ 的信息，而此题仅有 $3\operatorname{bit}$，所以本题中 $S$ 缩小得较慢，故需猜测 $S$ 中的数字。

具体实现时，可以将交互库可能返回的所有 $(a,b)$ 压成一个数 $c=10a+b$，同时给每个 $c$ 标号，即可较为简单地遍历所有状态。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define N 10000
#define St 15
vector<int>ans;
string str[N];
int conv[401];
void dfs(int i,int v,string s,int used)
{
	if(i==4)
	{
		str[v]=s;
		if(__builtin_popcount(used)==4)ans.push_back(v);
		return;
	}
	for(int j=0;j<10;j++)dfs(i+1,v*10+j,s+char(j+48),used|(1<<j));
}
void init(){dfs(0,0,"",0),sort(ans.begin(),ans.end()),conv[0]=0,conv[1]=1,conv[2]=2,conv[3]=3,conv[4]=4,conv[10]=5,conv[11]=6,conv[12]=7,conv[13]=8,conv[20]=9,conv[21]=10,conv[22]=11,conv[30]=12,conv[31]=13,conv[40]=14;}

int state(string Q,string A)
{
	int a=0,b=0;
	for(int i=0;i<4;i++)for(int j=0;j<4;j++)if(Q[i]==A[j])
	{
		if(i!=j)b++;
		else a++;
	}
	return conv[a*10+b];
}

double mxE;
int cnt[St],mxv;
double entropy(string q)
{
	double E=0;
	for(int i:ans)cnt[state(q,str[i])]++;
	for(int j=0;j<St;j++)if(cnt[j])
		E-=cnt[j]*1./ans.size()*log2(cnt[j]*1./ans.size()),cnt[j]=0;
	return E;
}

void table()
{
	for(int i=0;i<1e4;i++)
	{
		double E=entropy(str[i]);
		if(E>mxE)mxE=E,mxv=i;
	}
}

string lst;
int A,B;
void sieve(int res)
{
	vector<int>v=ans;
	ans.clear();
	for(int i:v)if(state(lst,str[i])==res)ans.push_back(i);
}

void query(string s)
{
	cout<<(lst=s)<<endl,cout.flush();
	cin>>A>>B;
	if(A==4)exit(0);
	sieve(conv[A*10+B]),mxE=-1e9;
	if(ans.size()==1)mxv=ans.front();
	else for(int i:ans)
	{
		double E=entropy(str[i]);
		if(E>mxE)mxE=E,mxv=i;
	}
}

int main()
{
	init(),query(str[932]);
	while(1)query(str[mxv]);
}
```

---

## 作者：TernaryTree (赞：1)

这不是我们 THUSC2024 Day2 吗？

---

设一个随机变量 $X$ 有 $n$ 种不同取值 $x_1,x_2,\dots,x_n$，$x_i$ 出现的概率为 $p_i$，则定义 $X$ 的熵为 

$$H(X)=-\sum_{i=1}^n p_i\log_2 p_i$$

---

然后我们考虑，如果当前答案的集合为 $S$，进行一次猜测 $g$ 之后，会得到若干种结果。假设答案从 $S$ 中均匀随机，则我们可以认为结果是上文中的随机变量，$p_i$ 即为 $i$ 这种结果在所有 $r\in S$ 中出现的次数除以 $|S|$，于是我们可以对猜测 $g$ 计算出其信息熵。我们贪心地选择信息熵最大的 $g$ 进行猜测即可。同时我们加上 $|S|=1$ 直接输出答案的优化即可。注意到第一次询问总是相同的，故没有必要每次都跑一遍，第一次询问直接询问初始词 `0123` 即可。

---

然而这样交了一发你发现 WA 在了 #179，即当答案为 `0932` 时会使用 $8$ 次询问。不过，我们~~充分发扬人类智慧~~发现把初始词也换成 `0932` 时就能跑过 #179，想必也能跑过其他点吧！事实上它确实过了。

---

```cpp
#include <bits/stdc++.h>
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 1e6 + 10;
const bool multidata = 0;

int read() {
	int x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

void write(int x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write(x / 10), pc(x % 10 + '0');
}

pii get(string secret, string guess) {
	int bull = 0, cow = 0;
	int vis[10] = {};
	rep(i, 0, 3) bull += (secret[i] == guess[i]), vis[guess[i] - '0'] = 1;
	rep(i, 0, 3) if (vis[secret[i] - '0'] && guess[i] != secret[i]) ++cow;
	return {bull, cow};
}

string reals;

pii query(string guess) {
	cout << guess << endl;
	int bull, cow; 
	cin >> bull >> cow;
	return {bull, cow};
}

string tostring(int i) {
	string s;
	s += (i / 1000 % 10) + '0';
	s += (i / 100 % 10) + '0';
	s += (i / 10 % 10) + '0';
	s += (i / 1 % 10) + '0';
	return s;
}

double getH(vector<double> p) {
	double ans = 0;
	for (double x : p) ans -= x * log2(x);
	return ans; 
}

vector<string> now;

void fake_main() {
	rep(i, 0, 9999) {
		string s = tostring(i);
		bool fl = 1;
		rep(j, 0, 3) rep(k, j + 1, 3) if (s[j] == s[k]) fl = 0;
		if (fl) now.push_back(s);
	}
	int tot = 0;
	while (true) {
		string rg = "0932"; double mx = -1e9;
		if (now.size() == 1) {
			query(now[0]);
			break;
		}
		if (tot) {
			for (string g : now) {
				int cnt[5][5] = {};
				for (string s : now) {
					pii cur = get(s, g);
					++cnt[cur.fs][cur.sc];
				}
				vector<double> p;
				rep(i, 0, 4) rep(j, 0, 4) if (cnt[i][j]) p.push_back((double) cnt[i][j] / now.size());
				double H = getH(p);
				if (H > mx) mx = H, rg = g;
			}
		}
		pii w = query(rg);
		++tot;
		if (w.fs == 4) break;
		vector<string> tmp;
		for (string s : now) if (get(s, rg) == w) tmp.push_back(s);
		tmp.swap(now);
	}
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}
/*

*/
```

---

## 作者：船酱魔王 (赞：0)

## 题意回顾

有一个神秘的各位数字不同的四位数字串 $ S $，对于每次猜测数字串（猜测串允许数位相同） $ T $，对于每个 $ 1 \le i \le 4 $：

* 如果 $ S_i=T_i $，计数器 $ A $ 加一。

* 如果 $ S_i \ne T_i $ 且 $ S_i = T_j $，计数器 $ B $ 加一。

请猜测出数字串 $ S $（即让交互库返回 `4 0`），**你最多猜测 $ 7 $ 次**。

## 分析

考虑维护剩余可能合法的答案集合 $ Q $，对于猜测词 $ T $ 产生的所有可能的猜测结果对于集合 $ Q $ 的一组**划分** $ U_1,U_2,\cdot \cdot \cdot,U_k $，计算出带来的**信息熵**为 $ E(T)=-\sum_{i=1}^{k}{r_i\log_2 r_i} $，其中 $ U_i $ 中元素出现的概率 $ r_i=\frac{U_i}{\sum_{i=1}^{k}U_i} $。感性理解，就是 $ r_i $ 概率的事件如果发生，那么带来了信息量就是 $ -\log_2 r_i $，信息熵就是信息量的期望；对于每次状态空间砍掉一半，有 1 个二进制位的信息，$ -\log_2 r_i=\log_2 \frac{1}{r_i} $ 就是状态空间被砍半的次数。所以信息熵可以理解为带来信息 bit 数的期望。

暴力划分集合的复杂度是很高的，大概是 $ O(V(\sum_{i=1}^{k} |Q_i|))\approx O(V^2) $（$ Q_i $ 为第 $ i $ 次猜测前的答案可能集合），我们发现只有 $ Q_1 $ 很大，是复杂度的瓶颈，考虑每个测试点首猜前 $ Q $ 都是所有各位数字互不相同的四位数字串，故每次首猜理论上都应该是同一个词，考虑预处理出首猜是 `0123`，然后复杂度优化到 $ O(V{\sum_{i=2}^{k}|Q_i|})\approx O(\frac{V^2}{w}) $，其中 $ w $ 与划分种类同阶，大概在 $ 16 $ 左右。

我们发现剩余的可行答案数量很少时，猜测可能的答案是更有价值的，故考虑估价函数 $ f(T)=E(T)+k \cdot G(T) $，$ G(T) $ 表示 $ T $ 成为答案的概率，这里 $ k=4.5 $ 可以通过本题。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>
#include <map>
#include <cmath>
#include <vector>
#define iter set<string>::iterator
using namespace std;
string str[10001];
set<string> se;
pair<int, int> check(string str, string ans) {
    pair<int, int> res = (pair<int, int>){0, 0};
    for(int i = 0; i < 4; i++) {
        if(ans[i] == str[i]) ans[i] = '*', res.first++;
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(ans[i] == str[j]) ans[i] = '*', res.second++;
        }
    }
    return res;
}
int main() {
    for(int i = 0; i <= 9999; i++) {
        int ii = i;
        string whr = "0000";
        for(int j = 3; j >= 0; j--) {
            whr[j] = ii % 10 + '0';
            ii /= 10;
        }
        str[i] = whr;
        for(int j = 0; j < 4; j++) {
            for(int k = j + 1; k < 4; k++) {
                if(whr[j] == whr[k]) whr = "gzh";
            }
        }
        if(whr != "gzh") se.insert(whr);
    }
    pair<int, int> pr;
    for(int ti = 1; ti <= 7; ti++) {
        string tr;
        if(ti == 1) {
            tr = "0123";
        } else if(se.size() == 1) {
            tr = *(se.begin());
        } else {
            string guess = "0000";
            double mix = -3;
            string vec[10001];
            int xjn = 0;
            for(iter it = se.begin(); it != se.end(); it++) {
                vec[++xjn] = *it;
            }
            map<pair<int, int>, int> mp;
            for(int i = 0; i <= 9999; i++) {
                string t = str[i];
                double thi = 0;
                mp.clear();
                for(int j = 1; j <= xjn; j++) {
                    string s = vec[j];
                    mp[check(t, s)]++;
                }
                for(map<pair<int, int>, int>::iterator it = mp.begin(); it != mp.end(); it++) {
                    double rate = (double)(it -> second) / se.size();
                    thi += rate * -log2(rate);
                }
                if(se.find(t) != se.end()) thi += 4.5 / se.size();
                if(thi > mix) mix = thi, guess = t;
            }
            tr = guess;
        }
        cout << tr << endl;
        cin >> pr.first >> pr.second;
        if(pr.first == 4) break;
        set<string> del;
        del.clear();
        for(iter it = se.begin(); it != se.end(); it++) {
            if(check(tr, *it) != pr) del.insert(*it);
        }
        for(iter it = del.begin(); it != del.end(); it++) {
            se.erase(*it);
        }
    }
    return 0;
}

```

---

