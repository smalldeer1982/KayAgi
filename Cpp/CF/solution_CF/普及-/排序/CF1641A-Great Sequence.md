# Great Sequence

## 题目描述

A sequence of positive integers is called great for a positive integer $ x $ , if we can split it into pairs in such a way that in each pair the first number multiplied by $ x $ is equal to the second number. More formally, a sequence $ a $ of size $ n $ is great for a positive integer $ x $ , if $ n $ is even and there exists a permutation $ p $ of size $ n $ , such that for each $ i $ ( $ 1 \le i \le \frac{n}{2} $ ) $ a_{p_{2i-1}} \cdot x = a_{p_{2i}} $ .

Sam has a sequence $ a $ and a positive integer $ x $ . Help him to make the sequence great: find the minimum possible number of positive integers that should be added to the sequence $ a $ to make it great for the number $ x $ .

## 说明/提示

In the first test case, Sam got lucky and the sequence is already great for the number $ 4 $ because you can divide it into such pairs: $ (1, 4) $ , $ (4, 16) $ . Thus we can add $ 0 $ numbers.

In the second test case, you can add numbers $ 1 $ and $ 14 $ to the sequence, then you can divide all $ 8 $ integers into such pairs: $ (1, 2) $ , $ (1, 2) $ , $ (2, 4) $ , $ (7, 14) $ . It is impossible to add less than $ 2 $ integers to fix the sequence.

## 样例 #1

### 输入

```
4
4 4
1 16 4 4
6 2
1 2 2 2 4 7
5 3
5 2 3 5 15
9 10
10 10 10 20 1 100 200 2000 3```

### 输出

```
0
2
3
3```

# 题解

## 作者：Yizhixiaoyun (赞：6)

[更好的阅读体验](https://flowus.cn/f6fd140e-c4c6-41e6-85b1-460c76f88b87)

[题目传送门](https://www.luogu.com.cn/problem/CF1641A)

## 题目分析

使用一个 $map$ 当作桶，将所有数存入该 $map$ 当中，然后将数组从小到大排序一遍。

接着开始判断，对于每个数 $a_i$ ，如果 $0 \le map_{a_i}$ 且 $0 \le map_{a_i \times x}$ ，那么就可以匹配。

否则就说明不可以匹配，答案加 $1$。

特别的，如果 $map_{a_i} = 0$ ，那么说明 $a_i$ 已被用过，不可以再用了。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
int T;
int n,a[maxn];
int x;
int ans;
unordered_map<int,int> mp;
inline void init(){
	mp.clear();ans=0;
	cin>>n>>x;
	for(register int i=1;i<=n;++i){
		cin>>a[i];
		mp[a[i]]++;
	}
	sort(a+1,a+n+1);
}
signed main(){
	cin>>T;
	while(T--){
		init();
		for(register int i=1;i<=n;++i){
			if(mp[a[i]]==0) continue;
			if(mp[a[i]*x]!=0){
				mp[a[i]]--;
				mp[a[i]*x]--;
			}
			else{
				mp[a[i]]--;
				ans++;
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：heaksicn (赞：3)

## 1 题意
给定 $n,x$ 和一个数组 $a$。问有多少组数满足 $(a_i,a_i* x)$ 的形式。

设这个答案为 $ans$，输出 $n-2* ans$。

多组数据。
## 2 思路
由于 $a_i\leq 10^9$，直接存一个桶会爆炸，所以使用动态桶 $map$。

首先，在输入时将每个数按入桶中。

对数组从小到大排序。

对于每个数 $a_i$，如果 $map_{a_i}=0$，说明 $a_i$ 已经被用过了。

如果 $map_{a_i}>0$ 并且 $map_{a_i* x}>0$，说明可以匹配。

否则就不能匹配，将答案加 $1$。

时间复杂度 $O(Tn\log n)$。
## 3 code
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
    ll X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(ll x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
ll T; 
ll n,x;
ll a[200001];
map <ll,ll> mp; 
int main(){
	T=read();
	while(T--){
		n=read(),x=read();
		for(int i=1;i<=n;i++) a[i]=read(),mp[a[i]]++;//按入桶中
		sort(a+1,a+n+1);//排序
		int ans=0; 
		for(int i=1;i<=n;i++){
			if(mp[a[i]]==0){//被用过
				continue;
			}
			if(mp[a[i]*x]) mp[a[i]*x]--,mp[a[i]]--;//可以匹配
			else mp[a[i]]--,ans++;//不能匹配
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：ryf_loser (赞：0)

此题的简单题意是：已知 $n$ 和 $x$，以及一个数组 $a$，求出有多少组数满足 $(a_{i},a_{i}\times x)$。

此题思路是：桶，可是开一个数组空间肯定爆。

所以我们可以考虑到用 STL 中的 map 动态维护这个桶。

我们设 $s$ 为 map 的名称，所以我们可以定义状态：$s_{i}=0$ 为此变量已经用过。而反之则说明可以匹配。

如果不满足答案加一。

这样时间和空间都不会超。

AC CODE

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#define ll long long
using namespace std;
ll in(){//快读
	ll x=0;
	char c;c=getchar();
	while (c<'0'||c>'9')c=getchar();
	while (c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x;
}
ll t,n,x,a[200001];
map<ll,ll>s;//定义
bool cmp(ll x,ll y){return x>y;}
int main(){
	t=in();
	while (t--){
		s.clear();
		n=in();x=in();
		for (int i=1;i<=n;i++)a[i]=in(),s[a[i]]++;
		sort(a+1,a+1+n);//排序
		ll ans=0;
		for (int i=1;i<=n;i++){
			if (!s[a[i]])continue;//如果为 0，直接跳过。
			if (s[a[i]*x])s[a[i]*x]--;
            else ans++;如果不满足答案加 1。
			s[a[i]]--;//最后要取消一个已经被匹配过得。
		}
		printf ("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：_Flame_ (赞：0)

## 思路

第一反应是用桶，但是看了一下数据，好像会爆空间。

所以想到用一个动态 $map$ 来代替桶。

输入数据到一个 $a$ 数组中，从小到大排个序，然后从前到后扫一遍，对于数组中的每个数 $k$，若 $map_{k}$ 为零，则代表 $k$ 已经被用过了，所以我们可以只处理 $map_{k}$ 不为零时的情况即可，此时，当 $map_{k}$ 大于零且 $map_{k\times x}$ 大于零时，说明可以匹配，$map_{k}$ 与 $map_{k\times x}$ 减一，否则不能匹配，答案加一。

注意这道题是多组数据，记得每次清空 $map$。

## Code


```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 200100
using namespace std;

int t;
int n;
int x;

int a[maxn];

map<int,int> p;

signed main(){
	cin>>t;
	while(t--){
		
		cin>>n>>x;
		p.clear();
		int ans=0;
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
			p[a[i]]++;
		}
		sort(a+1,a+n+1);
		
		for(int i=1;i<=n;i++){
			if(p[a[i]]){
				if(p[a[i]*x]){
					p[a[i]]--;
					p[a[i]*x]--;
				}
				else{
					p[a[i]]--;
					ans++;
				}
			}
		}
		cout<<ans<<endl;
	}
}

```

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1641A)

[codeforces1](https://codeforces.ml/contest/1642/problem/C)

[codeforces2](https://codeforces.ml/contest/1641/problem/A)

### 题目大意
一个正整数数列对于正整数 $x$ 被称为棒的，当且仅当此数列可以被拆分为若干对，每对中一个数是另一个数的 $x$ 倍。

换一种说法，一个数列 $a$ 的长度 $n$ 是一个偶数，并且这个数列存在一种排列方式，使得满足 $1 \le i \le \frac{n}{2}$ 的每个正整数 $i$，符合 $a_{2i-1}x = a_{2i}$，那么我们称数列 $a$ 对于正整数 $x$ 是棒的。

Sam有一个数列 $a$ 和一个正整数 $x$。请你帮助他让这个数列 $a$ 对于 $x$ 变成棒的：将若干个正整数加入数列中。请问最少要加入几个正整数？

**数据范围**：$1 \le t \le 2 \times 10^4,1 \le n \le 2 \times 10^5,\sum{n} \le 2 \times 10^5,2 \leq x \leq 10^6,1 \leq a_i \leq 10^9$。

### 思路
用 map 记录每个数字出现的次数。为了不重不漏，我们可以先让需要加入的数字数量 $ans = n$，然后对 $a$ 数列排序，再遍历 $a$ 数列，如果 map 中存有 $a_i$ 和 $a_i x$，则判断这两个数字匹配成功，然后需要加入的数字数量 $ans$ 减 $2$，再把 map 中 $a_i$ 和 $a_i x$ 的出现次数分别减 $1$，就可以保证不重不漏了。

时间复杂度：$O(T n \log(n))$。

---
上代码——
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,a[200010],ans,x;
map<ll,int> m;//a[i]*x<=10^9*10^6=10^15，所以要开long long
inline ll read(){
	ll x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x;
}
int main(){
	t=read();
	while(t--){
		n=read(),x=read();
		ans=n;//需要加入的数字数量
		for(int i=1;i<=n;i++){
			a[i]=read();
			m[a[i]]++;
		}
		sort(a+1,a+n+1);//排序
		for(int i=1;i<=n;i++){
			if(m[a[i]]){
				if(m[a[i]*x])m[a[i]]--,m[a[i]*x]--,ans-=2;//匹配数字
			}
		}
		printf("%lld\n",ans);
		m.clear();
	}
	return 0;
}
```

---

## 作者：ExplodingKonjac (赞：0)

[**【原题链接】**](https://www.luogu.com.cn/problem/CF1641A)
 
## 题目分析
 
题意：向原序列添加尽量少的数，使得可以给所有数两两配对，使得每一对中，一个是另一个的 $x$ 倍。
 
做法挺直接的：将所有数塞进一个 `multiset` 里面，然后不断选出最小的数，设这个数是 $a$。如果 $ax$ 在 `multiset` 中存在，就 $ax$ 删掉，否则令 $ans\gets ans+1$，然后删掉 $a$。

这种做法的正确性证明：我们让一个小的数去配对一个大的数。那么对于一个 $a$，它配对的数是确定的。因此所有数的配对关系形成一棵森林。

一个非叶子节点选择与儿子配对还是和父亲配对，答案都是不变的，因为上面和下面对答案的贡献抵消，所以我们不妨直接令儿子贪心选择父亲配对。再考虑一下：对于一个非叶子节点，如果它被一个儿子节点配对了，那么剩下的没有配对的儿子不得不新拉一个节点来配对。由此可以得到我们的构造是最优的。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define OPENIOBUF

/*
省略100多行的快读快写模板。
即下文中的qin、qout。
*/

using namespace FastIO;
typedef long long LL;
LL T,n,k,x,ans,a[200005];
multiset<LL> s;
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>k,ans=0;
		for(int i=1;i<=n;i++)	qin>>a[i],s.insert(a[i]);
		while(!s.empty())
		{
			auto it=s.begin();
			x=*it,s.erase(it);
			if(!s.empty() && (it=s.find(x*k))!=s.end())
				s.erase(it);
			else
				ans++;
		}
		qout.writeln(ans);
	}
//	return qout.flush(),0;
}

```


---

## 作者：Milmon (赞：0)

[in Blog](https://milk-lemon.blog.luogu.org/solution-CF1641A) & [Problem](https://www.luogu.com.cn/problem/CF1641A)

## 题意简述

- 一个数列 $a$ 的长度 $n$ 是一个偶数，并且这个数列存在一种排列方式，使得满足 $1\leq i\leq\frac n2$ 的每个正整数 $i$，符合 $a_{2i-1}x=a_{2i}$，那么我们称数列 $a$ 对于正整数 $x$ 是棒的。

- Sam 有一个数列 $a$ 和一个正整数 $x$。请你帮助他让这个数列 $a$ 对于 $x$ 变成棒的：将若干个正整数加入数列中。请问最少要加入几个正整数？

- $1\leq n\leq 2\times 10^5$，$2\leq x\leq 10^6$，$1\leq a_i\leq 10^9$

## 题目分析

使用可重集合（multiset）存储原数列，每存一个数时间复杂度为 $\Theta(n\log n)$。

每次从集合中取出最小的数，判断它的 $x$ 倍是否存在于集合中：

- 如果存在，就不用添加新数，把这两个数都删掉即可；
- 如果不存在，就要添加一个数，使得它能成功配对。

因为这个数不可能与更小的数形成 $x$ 倍关系（即使添加的数比这个数更小，也不会因此影响答案的最优性），因为这是当前集合中最小的数；而且为了让这个数能够成功配对，所以必须添加一个数。故以上解法必然是最优解。

因为 $a_i$ 的上限为 $10^9$，$x$ 的上限为 $10^6$，相乘会超过 int 的范围，故使用 long long。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
 
int n,a[200001],x;
multiset<long long>S;
 
int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i);
		sort(a+1,a+1+n);
		S.clear();
		for(int i=1;i<=n;i++)
			S.insert(a[i]);
		int tot=0;
		while(S.size()){
			auto it=S.find((*(S.begin()))*(long long)x);
			if(it!=S.end())S.erase(it),S.erase(S.begin());
			else S.erase(S.begin()),tot++;
		}
		printf("%d\n",tot);
	}
	return 0;
}
```

---

## 作者：yzy1 (赞：0)

## 题目大意

- 多测，共 $t(1\le t \le 2\times 10^4)$ 组数据。
- 定义一个长度为 $2k(k \in \mathbb N_+)$ 的数组 $a$ 为「好的」，当且仅当 $a$ 能被划分为 $n$ 个二元组，对于每个二元组 $(i,j)$，均满足 $j=ix$，其中 $x$ 给定且 $2 \le x \le 10^6$。且每个整数都恰好划分到了一个二元组中。
- 给出一个长度为 $n(1\le n \le 2\times 10^5)$ 的数组 $a$，求至少在 $a$ 中再加入多少个整数，使得 $a$ 为「好的」。

## 简要做法

- 考虑贪心，开一个 `map` 来记录 $a$ 中每个数字的出现次数 $cnt$，然后从小到大遍历：
  - 若 $cnt(i\cdot k) \ge cnt(i)$，则直接让 $cnt(i)$ 个 $i$ 和 $cnt(i)$ 个 $i\cdot k$ 组成 $cnt(i)$ 个二元组，并另 $cnt(i\cdot k)\gets cnt(i\cdot k) - cnt(i);\ cnt(i)\gets 0$。
  - 否则，说明 $i \cdot k$ 的数量不够，我们需要加入 $cnt(i) - cnt(i\cdot k)$ 个 $i\cdot k$ 来让这些 $i$ 组成二元组。即 $ans \gets ans + cnt(i) - cnt(i\cdot k);\ cnt(i) \gets 0;\ cnt(i\cdot k) \gets 0$。

## 代码参考

```cpp
void Work(){
  map<int,int> mp;
  cin>>n>>K;re(i,n)cin>>a[i],++mp[a[i]];
  int ans=0;
  for(auto it=mp.begin();it!=mp.end();++it){
    if(!it->second)continue;
    if(mp[it->first*K]>=it->second)mp[it->first*K]-=it->second;
    else ans+= it->second-mp[it->first*K],mp[it->first*K]=0;
  }
  cout<<ans<<'\n';
}
```



---

## 作者：windflower (赞：0)

# 贪心

简要题意：
>给定一个正整数 x ，great sequence 表示它含有 2n 个元素，且可分成 n 对 $(a_i,b_i)$ 均满足 $a_i\cdot x=b_i$ ，问最少需要添加几个数才能将给定的数组变为 great sequence 。  

显然对于序列中的最小值，能够与之匹配的数是唯一的，因此我们可以贪心的枚举最小值，判断是否有与之匹配的，然后删除即可。  
 stl 大法好，优先队列 + map 就能轻松解决。  
 注意：$a_i\cdot x$ 不要忘记开long long  
 附 AC 代码
 ```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		int ans=0,a;
		priority_queue<int,vector<int>,greater<int>>q;
		map<long long,int>m;
		for(int i=0;i<n;i++){
			scanf("%d",&a);
			q.push(a);
			m[a]++;
		}
		while(!q.empty()){
			int now=q.top();
			q.pop();
			if(!m[now])continue;
			m[now]--;
			if(m[1ll*now*x])m[now*x]--;
			else ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：jiangtaizhe001 (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/jiangtaizhe001/p/15932375.html)  
[题目传送门](https://codeforces.com/problemset/problem/1641/A)
## 题目大意
给定一个长度为 $n$ 的序列 $a$ 和一个数字 $x$。
你需要在序列 $a$ 后面加上一些元素，然后对整个序列重新排序，使得对于 $[1,n]$ 内的任意奇数 $i$ 都有 $a_i\cdot x=a_{i+1}$。  
数据范围：$n\le 2\times10^5,\sum n\le 2\times 10^5,2\le x\le10^6,1\le a_i\le 10^9$。
## 题目解析
考虑贪心。  
首先把整个序列按升序排序。  
然后从头到尾扫一次，如果 $a_i\cdot x$ 存在，那么就把它删掉，否则就在序列里加入这个数字（也就是答案加一）。  
我们发现需要使用哈希或者是平衡树来维护，这样就可以做到 $O\left(n\right)$ 或者是 $O\left(n\log n\right)$。

这里用 `set` 来维护。

![](https://cdn.luogu.com.cn/upload/image_hosting/ycjuqnrc.png)  
我们发现 $x\le 10^6,a_i\le 10^9$，也就是说 $a_i\cdot x\le 10^{15}$，会爆 `int`，所以一定要开 `long long`。~~听说 Div 2 一堆人因为没开 FST 了。~~

核心代码：
```cpp
struct JTZ{
	ll x; int num;
	bool operator < (const JTZ x) const {
		if(this->x==x.x) return this->num < x.num;
		return this->x < x.x;
	}
};
set<JTZ> s,E;
int n,flag[maxn];
ll x,a[maxn];
void work(){
	s=E; n=read(); x=read(); int i,ans=0;
	for(i=1;i<=n;i++) a[i]=read(); sort(a+1,a+n+1);
	for(i=1;i<=n;i++) s.insert((JTZ){a[i],i}),flag[i]=1;
	for(i=1;i<=n;i++) if(flag[i]){
		flag[i]=0;
		s.erase((JTZ){a[i],i});
		set<JTZ>::iterator tmp=s.lower_bound((JTZ){a[i]*x,i});
		if((*tmp).x==a[i]*x) flag[(*tmp).num]=0,s.erase(tmp);
		else ans++;
	} print(ans),pc('\n'); return;
}
```

---

## 作者：Suzt_ilymtics (赞：0)

### Description

> $T$ 组数据。每组数据给定两个数 $n,x$，表示有 $n$ 个数和一个倍率 $x$。任意一对满足 $a_i = xa_j$ 的 $(i,j)$ 都可以匹配。你可以加入任意数量任意大小的数来帮助你完成这个操作。问最少加几个数。

### Solution

从小到大贪心，能匹配就匹配掉，否则新加一个数和其匹配。

正确性可以感性理解一下，我们把能匹配的值域连边，形如 $a - ax - ax^2 - \cdots$，发现从小到大贪心相当于从一条链的链头开始选，是最优的。

如果是用乘法（小数匹配大数）的话要开 `long long`，~~不然你就 FST 了~~，除法（大数匹配小数）的话就不需要了。

### Code

实现方式有很多，我用的 `set`。

```cpp
int T, n, x, ans = 0;
int stc[MAXN], sc = 0, now = 1;
multiset<int> S;

void Main() {
    sc = 0, now = 1, ans = 0;
    n = read(), x = read();
    for(int i = 1; i <= n; ++i) S.insert(read());
    int cnt = 0;
    for(multiset<int>::iterator it; S.size();) {
        it = S.begin();
        int p = *it;
        S.erase(it);
        if(S.find(p * x) != S.end()) {
            S.erase(S.find(p * x));
        } else {
            ans ++;
        }
    }
    printf("%lld\n", ans);
}

signed main()
{
    T = read();
    while(T--) Main(); 
    return 0;
}

```

---

