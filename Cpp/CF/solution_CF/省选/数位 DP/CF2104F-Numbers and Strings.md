# Numbers and Strings

## 题目描述

对于每个从 $1$ 到 $n$ 的整数 $x$，我们将按照以下规则生成字符串 $S(x)$：

- 计算 $x+1$；
- 将 $x$ 和 $x+1$ 在十进制表示下无分隔符、无前导零地拼接在一起；
- 将得到的字符串中的所有数字按非递减顺序排序。

例如，字符串 $S(139)$ 是 `011349`（排序前的拼接结果是 `139140`）。字符串 $S(99)$ 是 `00199`。

你的任务是统计 $S(1), S(2), \dots, S(n)$ 中不同字符串的数量。

## 样例 #1

### 输入

```
2
42
1337```

### 输出

```
42
948```

# 题解

## 作者：ln001 (赞：3)

![色图](https://cdn.luogu.com.cn/upload/image_hosting/rb8ja111.png)

## 题意
$q$ 次询问不超过 $n$ 的好的数的个数，定义数 $x$ 是好的当且仅当不存在 $y \in [1, x - 1]$ 满足 $f(x) \cup f(x + 1) = f(y) \cup f(y + 1)$，其中 $f(x)$ 表示由 $x$ 各数位组成的**可重集**，例如 $f(1033) = \{0, 1, 3, 3\}$。

## 思路
该篇题解思路和官解一致均为乱搞，不是数位 DP 的做法，想学数位 DP 的可以去 cf 的讨论区。

先考虑数 $x$ 是好的的必要条件，即数 $x$ 不是好的的充分条件。

将 $x$ 的数位分解为三部分，一段前缀和一段后缀，前缀后缀不直接相连，中间夹有**一位**不属于前缀也不属于后缀的数位，称为中缀，后缀满足是**极长的**由 $9$ 构成的连续段，若 $x \bmod 10 \not= 9$，则后缀大小为 $0$，若后缀过长，可能会使前缀甚至中缀的长度为 $0$，我们认为其均是合法的划分方案。

考虑通过上述 $x$ 的三个部分构造出 $x + 1$，不难想到其实就是保持前缀不变，将中缀 $ + 1$，后缀全部推平为 $0$。所以 $f(x) \cup f(x + 1)$ 中必定会包含两次 $x$ 的前缀，一次 $x$ 的中缀和中缀 $+ 1$，以及若干 $0$ 和 $9$。由此看出，中缀和后缀变化不易量化，而前缀未发生变化，所以不难想到对前缀做文章，我们发现，若存在数 $y < x$ 满足 $y$ 的后缀和中缀与 $x$ 一致，且 $f(\text{x 的前缀}) = f(\text{y 的前缀})$，则 $x$ 一定不好，即我们找到了数不好的充分条件，即数是好的的必要条件。

根据上文推理，数是好的必要条件即为数的前缀递增，但这样有一个问题，若数的第一位为 $0$，则数不符合规范，若数第一位不为 $0$，则数的前缀就不可能有 $0$，但注意到数 $70839$ 是好的，其前缀仍包含 $0$，所以合法数的前缀应为一段递增序列，若该序列第一个值为 $0$，则交换第一个值和序列从左到右第一个非 $0$ 的值，不难证明好的数一定符合该结论。

正常的题目到这里就需要找充分条件了，但这是 CF，所以我们要另寻出路。

组合数不难证明符合上述条件的数较少，可以先 dfs 找出前缀合法（即满足该必要条件）的所有数，然后再在这些数上暴力扫出 $f(x) \cup f(x + 1)$ 并判断是否合法，最后查询时直接在答案序列上二分即可。

---

## 作者：3a51_ (赞：1)

考虑到一个数增加 $1$ 后的变化方式是将最后若干个 $9$ 变为 $0$，最后一个不是 $9$ 的位置增加 $1$，前面不变。所以可以将每个数都按照这种方式分成三部分。

不难发现，如果两个数 $x,y$ 的后两部分相同，第一部分的组成也相同（如 $311299$ 和 $131299$），那么 $S(x)$ 和 $S(y)$ 一定相同。由于只能计算一个，不妨计算第一部分单调不降的那个。

稍微观察一下发现好像第一部分单调不降的数并不多，所以有一个朴素的想法：递归找到所有第一部分单调不降的数，存到一个 `vector` 里，然后按照 $S$ 值去重，对于每个询问二分回答。注意前导 $0$ 的处理，如果有前导 $0$ 只需要跟第一个非 $0$ 位交换即可。

实际上这样复杂度是正确的，假设第一部分有 $p1$ 个数，那么枚举的总量为：

$$ \sum_{p1=0}^8 \binom{p1+9}{p1}\times 9\times (9-p1)$$

（还是比较好理解的，第一部分 $\binom{p1+9}{p1}$，第二部分和第三部分分界线 $9-p1$，第二部分 $9$）

而这个式子经过计算为 $680238$，复杂度完全可以接受。

![](https://cdn.luogu.com.cn/upload/image_hosting/yxxsf78c.png)

[提交记录](https://codeforces.com/contest/2104/submission/319398160)。

---

## 作者：xzy090626 (赞：0)

\*2600，太牛。我们考虑这个排序操作意思就是找数位组成不同的串的个数。考虑分析一下 $[1,n]$ 中的数，可以考虑只找各种角度上本质不同的数、减少计算量。

首先，考虑一个十进制数 $+1$ 后的变化。显然是将低位连续的若干的 $9$ 全部变为 $0$，再将第一个不是 $9$ 的数 $+1$。

这样，我们将整个数拆分成了三个部分：前面一部分的数，第二部分的一个非 $9$ 的数，以及最后连续的一些 $9$。 

注意到如果两个数 $x,y$ 满足三个部分都相同，那么 $S(x)=S(y)$。当然这是一个充分不必要条件，也就是说还需要进一步去重。

考虑本质不同个数最多的显然是第一部分（后两个部分都至多只有 $9$ 种）；一般地，钦定这部分数单调不降便能自然地去重。于是，可以考虑先 dfs 求出所有满足条件的第一部分的数（实际上很少），大概是 $5\times 10^4$ 个左右。这部分有一些前导 $0$ 的细节问题，

我们先将第一部分的数排序，然后考虑后面两部分。先考虑枚举后两个部分，然后对于每种 $S(x)$ 找到与之对应最小的 $x$（这一步可以排序找到，运算量不大）；最后可以排序后对于每次询问二分回答。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
#include<string>
#include<set>
#include<map>
#include<unordered_map>
#include<queue>
#include<time.h>
#include<bitset>
#include<random>
#include<iomanip>
#include<assert.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define pb push_back
using namespace std;
const int N = 1e6 + 7;
const int M = 1e9;
int n,m;
vector<int>vec,ans;
vector<pair<string,int>>res;
int b[20],tt[20];
void dfs(int x,int lst){
	int cur = 0;
	for(int i=1;i<x;++i) tt[i] = b[i];
	for(int i=1;i<x;++i){
		if(tt[i]){
			swap(tt[i],tt[1]);
			break;
		}
	}
	for(int i=1;i<x;++i) cur = cur * 10 + tt[i];
	vec.push_back(cur);
	if(x>9) return;
	for(int i=lst;i<=9;++i){
		b[x] = i;
		dfs(x+1,i);
	}
}
void solve(){
	int n;cin>>n;
	cout<<upper_bound(ans.begin(),ans.end(),n)-ans.begin()<<'\n';
}
string work(int x){
	string str = to_string(x) + to_string(x+1);
	sort(str.begin(),str.end());
	return str;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	dfs(1,0);
	sort(vec.begin(),vec.end());
	vec.erase(unique(vec.begin(),vec.end()),vec.end());
	for(auto c:vec){
		for(int i=0;i<9;++i){
			int x = c * 10 + i,tt = 1;
			if(x>M) break;
			for(int j=0;j<=9;++j){
				int y = x * tt + tt - 1;
				if(y>M) break;
				if(y) res.push_back({work(y),y});
				tt *= 10;
			}
		}
	}
	sort(res.begin(),res.end());
	int m = res.size();
	for(int i=0;i<m;++i){
		if(!i || res[i].x!=res[i-1].x) ans.push_back(res[i].y);
	}
	sort(ans.begin(),ans.end());
	int T;cin>>T;
	for(int _=1;_<=T;++_){
		solve();
	}
	return 0;
}
```

---

## 作者：ax_by_c (赞：0)

考虑对每个 $S(x)$ 求出对应最小的 $x$。

注意到若最后不是 $9$ 那么加 $1$ 只会影响最后一位，于是考虑将数表示为前面若干位，最后一个不是 $9$ 的位和若干个 $9$。

如果两个数前面若干位相同且最后一个不是 $9$ 的位也相同，那么可以只保留较小的数。

于是可以以此为去重依据进行搜索，实际上搜出来的数是不多的，那么将这些数排序并一一判断是否是 $S(x)$ 第一次出现即可。

每次询问二分即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define repll(i,l,r) for(ll i=(l);i<=(r);i++)
#define perll(i,r,l) for(ll i=(r);i>=(l);i--)
#define pb push_back
#define ins insert
#define clr clear
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ull,int> H;
const ull P=1145141;
const int L=10;
int tmp[L];
vector<int>as,f,ff;
set<H>vis;
set<ull>S;
ull F(int n){
	as.clr();
	int t_=n;
	while(t_)as.pb(t_%10),t_/=10;
	t_=n+1;
	while(t_)as.pb(t_%10),t_/=10;
	sort(as.begin(),as.end());
	ull h=0;
	for(auto it:as)h=h*P+(it+1);
	return h;
}
H cal(int n){
	as.clr();
	rep(i,1,n-1)as.pb(tmp[i]);
	sort(as.begin(),as.end());
	ull h=0;
	for(auto it:as)h=h*P+(it+1);
	return {h,tmp[n]};
}
void dfs(int u){
	if(u>2){
		auto h=cal(u-1);
		if(vis.count(h))return ;
		vis.ins(h);
	}
	if(u>1&&tmp[u-1]!=9){
		int xx=0;
		rep(i,1,u-1)xx=xx*10+tmp[i];
		rep(i,u,10)f.pb(xx),xx=xx*10+9;
	}
	if(u==10)return ;
	int L=0,R=9;
	if(u==1)L=1;
	rep(x,L,R){
		tmp[u]=x;
		dfs(u+1);
	}
}
void Init(){
	dfs(1);
	f.pb(9);
	f.pb(99);
	f.pb(999);
	f.pb(9999);
	f.pb(99999);
	f.pb(999999);
	f.pb(9999999);
	f.pb(99999999);
	f.pb(999999999);
	sort(f.begin(),f.end());
	for(auto x:f){
		ull h=F(x);
		if(!S.count(h))S.ins(h),ff.pb(x);
	}
}
int n;
void slv(){
	scanf("%d",&n);
	int l=0,r=(int)ff.size()-1,mid,res=0;
	while(l<=r){
		mid=l+((r-l)>>1);
		if(ff[mid]<=n)res=mid+1,l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",res);
}
void main(){
	Init();
	int T=1;
//	int csid=0;scanf("%d",&csid);
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	string __name="";
	if(__name!=""){
		freopen((__name+".in").c_str(),"r",stdin);
		freopen((__name+".out").c_str(),"w",stdout);
	}
	ax_by_c::main();
	return 0;
}
```

---

