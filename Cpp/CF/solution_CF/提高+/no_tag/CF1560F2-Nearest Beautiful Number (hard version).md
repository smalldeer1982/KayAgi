# Nearest Beautiful Number (hard version)

## 题目描述

It is a complicated version of problem F1. The difference between them is the constraints (F1: $ k \le 2 $ , F2: $ k \le 10 $ ).

You are given an integer $ n $ . Find the minimum integer $ x $ such that $ x \ge n $ and the number $ x $ is $ k $ -beautiful.

A number is called $ k $ -beautiful if its decimal representation having no leading zeroes contains no more than $ k $ different digits. E.g. if $ k = 2 $ , the numbers $ 3434443 $ , $ 55550 $ , $ 777 $ and $ 21 $ are $ k $ -beautiful whereas the numbers $ 120 $ , $ 445435 $ and $ 998244353 $ are not.

## 样例 #1

### 输入

```
6
2021 3
177890 2
34512 3
724533 4
998244353 1
12345678 10```

### 输出

```
2021
181111
34533
724542
999999999
12345678```

# 题解

## 作者：Illusory_dimes (赞：8)

[还须要往下翻却仍然不一定有更好的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15169251.html)

## description

求大于一个数 $n$ 并且包含的不同数字不超过 $k$ 的最小数。

## solution

### easy version

看到题目 $k\leq 2$ ，着实小的可怜，可以用一堆判断乱搞？？（没试过）

### hard version

（注：下文“试填”表示用从当前这一位的数字 $+1$ 到 $9$ 去更换这一位，看是否合法）

可以想到应该尽可能不动高位，所以可以由高到低从第一个不合法的位置开始试填，然后分两种情况：

1. 发现这一位试填完了都不能使其合法，往高一位继续试填；

2. 发现这一位能够试填到使其合法，往低一位继续试填。

直到最低一位都合法的时候，这个数字就合法了。

要枚举最久的例子应该是在 $k=1$ 的时候，但总共试填次数大概就小一百的样子，非常可过。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n,k;
inline int read(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+ch-'0';ch=getchar();}
	return s*w;
}
inline int digcnt(int x){
	int tmp=0,it;
	while(x){
		it=x%10;
		tmp|=(1<<it);
		x/=10;
	}
	return __builtin_popcount(tmp);
}
inline void mian(){
	n=read();k=read();
	while(digcnt(n)>k){
		int l=1,r=n;
		while(digcnt(r)>k){
			l*=10;r/=10;
		}
		l/=10;
		n=((n/l)+1)*l;
	}
	printf("%d\n",n);
}
int main(){
	t=read();
	for(int i=1;i<=t;++i)mian();
	return 0;
}
```

---

## 作者：Register_int (赞：6)

~~好水一*2100~~  
思路很简单，直接在原数上贪心。找到原数中满足条件的最长前缀。设前缀为 $1\sim l$，保留这一部分，然后将后面修改为最小的小于原数且 $l+1$ 位比原来增加 $1$ 的数。也就是 $(a_{l+1}+1)000\cdots0$ 的形式。一直操作只到原数满足要求即可。复杂度 $O(\log n)$。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

inline 
int calc(int n) {
	int t = 0, cnt = 0;
	while (n) t |= 1 << n % 10, n /= 10;
	while (t) t &= t - 1, cnt++;
	return cnt;
}

int t, n, k;

int p, q;

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		while (calc(n) > k) {
			p = 1, q = n;
			while (calc(q) > k) p *= 10, q /= 10; p /= 10;
			n = (n / p + 1) * p;
		}
		printf("%d\n", n);
	}
}
```

---

## 作者：MagicalSheep (赞：2)

# 分析

假设我们已经取得 $k$ 个不同的、可以用于构造答案的数字，现在考虑如何使用这些数字来构造一个最小的、大于等于所给数字 $n$ 的答案。

从最高位开始构造数字，我们可以得到以下两个贪心策略：

1. 如果该位可以使用一个更小的数字来满足大于等于 $n$ 上相同位数字的条件，则使用更大的数字不会更优。
2. 如果所构造答案的某一位严格大于 $n$ 上相同位的数字，则该位之后的每一位可以任意使用 $k$ 个数字的其中一个。显然，选择 $k$ 个数中最小的那个最优。

于是我们可以得出以下构造方式：

1. 从最高位开始向低位构造数字。
2. 对于每一位，从小到大依次尝试使用这 $k$ 个数，直到某个数大于等于 $n$ 上相同位的数字，将该数字填入该位。如果 $k$ 个数都小于 $n$ 上相同位的数字，则构造失败（这 $k$ 个数无法构造出答案）。
3. 如果选取的数字严格大于 $n$ 上相同位的数字，则使用 $k$ 个数中最小的数字填入该位之后的所有位。否则，对下一位重复执行第 $2$ 个步骤。

这个构造方法可以通过对每一位进行递归实现。

接下来，我们考虑如何选取这 $k$ 个数。当 $k=2$ 时（Easy version），我们可以枚举所有的取值情况，记录每一种取值情况的合法解，最后选取其中最小的解作为答案即可。

然而事实上，我们并不需要在递归求解之前就得到这 $k$ 个数的取值，而是在对每一位递归的过程中逐渐取得这 $k$ 个数。

让我们从最高位开始考虑，此时我们选中的数字个数为 $0$ ，这意味着我们可以选择一个当前最优的数字加入 $k$ 数字集合，然后直接使用该数字填入该位。当前最优的数字是什么？显然是 $n$ 相同位上的数字，这是能满足大于等于 $n$ 上相同位数字条件的最小值；如果通过递归求解发现填入该数字后无法构造出答案，那其加一后的值就是当前位最优的数字（满足大于相同位数字的条件，一定能够确保构造出答案）。

让我们将该取数方法扩展到其他位，当处理到第 $i$ 位，此时选中的数字个数 $m$ 小于 $k$ 时，选择 $n$ 相同位上的数字填入该位，并将该数加入 $k$（注意去重），继续递归求解下一位；若递归求解下一位无法构造出答案，则将该数加一后填入该位，并将该数加入 $k$（注意去重），然后递归求解下一位，此时能够保证构造出最优解。

# AC代码

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int t, k, dignum;
bool vis[10]; // 用于标记某个数是否已被加入k数集合
char n[15], ans[15];

// ind: 当前构造的位数
// num: 已选择的k数数组
// len: 已选择的k数数量
// isok: 该位之前是否已经存在某一位严格大于n相同位的数字
bool dfs(int ind, int *num, int len, bool isok)
{
    if (ind == dignum)
        return true;

    // 已选择的k数个数小于k
    if (len < k)
    {
        int new_num[k] = {0}, new_num_len = len;
        for (int i = 0; i < len; i++)
            new_num[i] = num[i];

        // 如果k集合中没有该数，便加入该数并标记
        if (!vis[n[ind] - '0'])
            new_num[new_num_len++] = n[ind] - '0', vis[n[ind] - '0'] = true;
        ans[ind] = n[ind];
        // 递归求解，如果可以构造，则必为最优解
        if (dfs(ind + 1, new_num, new_num_len, isok))
            return true;
        // 从k集合中移除该数
        if (new_num_len != len)
            vis[n[ind] - '0'] = false;

        for (int i = 0; i < len; i++)
            new_num[i] = num[i];
        // 注意，如果加一后的值已经在集合中了，这意味着在集合未填满的情况下，我们获得了任意填写之后所有位的权利
        // 此时，当后续所有位填0时最优，因此，我们需要将0加入k集合。
        if (vis[n[ind] - '0' + 1])
            new_num[len] = 0;
        else
            new_num[len] = n[ind] - '0' + 1;
        ans[ind] = n[ind] + 1;
        // 若上述情况无法构造，则加一后填入必能构造出最优解
        return dfs(ind + 1, new_num, len + 1, true);
    }

    sort(num, num + len);
    // 先前已有某一位严格大于n相同位上的数字
    if (isok)
    {
        ans[ind] = num[0] + '0';
        return dfs(ind + 1, num, len, isok);
    }
    for (int i = 0; i < len; i++)
    {
        // 满足条件
        if (num[i] >= n[ind] - '0')
        {
            ans[ind] = num[i] + '0';
            // 递归求解下一位
            if (dfs(ind + 1, num, len, num[i] > n[ind] - '0'))
                return true;
        }
    }
    // 若该位无法继续构造答案，返回false表示构造失败
    return false;
}

int main()
{
    cin >> t;
    while (t--)
    {
        memset(vis, 0, sizeof(vis));
        cin >> n >> k;
        dignum = strlen(n);
        // 答案必为dignum位
        ans[dignum] = '\0';
        int num[k] = {0};
        dfs(0, num, 0, false);
        cout << atoll(ans) << endl;
    }
    return 0;
}
```

---

## 作者：z_yq (赞：0)

# 前言
打 CP 的时候没有拿到首切，反而是第二，炸了。
# 题面
给定 $n,k$ 找到最小的 $x$ 满足 $x\ge n$ 且 $x$ 的不同数位数量小于等于 $k$。
# 做法
很明显，$999\dots 99$ 是满足条件的，因为 $k\ge 1$，所以 $x$ 的数位一定等于 $n$ 的数位。其次就是看到这种题目，和数位的数值有关，并且数位是一定的，所以自然想到数位 DP，所以数位 DP 最好写的就是递归版，板子写多了这种题目直接套用即可。
# 代码
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<climits>
#include<cmath>
#define ll long long
#define se second
#define fi first 

using namespace std;
const int N=2e5+9;
int T,n,k,mp[20],num[20],cnt,ans;

inline void dfs(int x,int y,int cnum,int f){
	if(ans!=-1) return void();
//	cout<<x<<' '<<y<<endl;
	if(x>cnt){
		ans=y;
		return;
	}
	for(int i=0;i<=9;i++){
		if(f && i>=num[x] && (mp[i]==0)+cnum<=k) 
			dfs(x+1,y*10+i,cnum+(mp[i]++==0),(i==num[x]));
		if(!f && (mp[i]==0)+cnum<=k)
			dfs(x+1,y*10+i,cnum+(mp[i]++==0),0);
	}
}

inline void solve(){
	memset(mp,0,sizeof(mp));
    cin>>n>>k;ans=-1;cnt=0;
    while(n){
    	num[++cnt]=n%10;
    	n/=10;
	}
	reverse(num+1,num+cnt+1);
	dfs(1,0,0,1);
    cout<<ans<<endl;
    return void();
}
int main(){
	cin>>T;
	while(T--)solve();
    return 0;
}

```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1560F2)

***2100**，独立切了。

先看了 F1，然后才过来了，那就两个都一起讲了吧。

记 $n$ 数位排到一个数组上记为 $a$。

先看 F1，不同点在 $1\le k\le 2$。

$k=1$ 是容易的，只能用一种数填，那直接枚举用 $[0,9]$ 哪个填就好了，注意可能位数要增加一位的情况。

$k=2$ 同理，枚举使用哪两个数是 $81$ 种可能，可以承受，所以枚举用哪两个数填就行。

这个填的过程就是枚举 $n$ 的每一位，如果当前填的 $x>a_i$，后面填尽可能小的即可。

于是 F1 就是一个暴力枚举题，不懂为什么有 ***1900**。

看 F2。

首先我们不能枚举用了哪些数，时间复杂度无法承受。

不妨换一种构造方式。

回忆我们怎么比较两个数的大小，位数相同时，我们从高到低位比较，当前数位大的那个对应数值更大。

所以，我们只要枚举数位 $i$，钦定它是第一个大于 $a_i$ 的那个位置，这是本题的突破点。

- 对于 $j \in [1,i)$ 的位置，我们构造的每个位就是 $a_j$。

- 对于 $i$ 位置，如果我们不同的数字有剩余，那就安排上 $a_i+1$，否则只能在用过的数值上安排。

- 对于剩下的位置，我们随意安排，贪心即可。如果有剩余，直接安排 $0$ 即可，如果没有剩余，安排用过的最小的即可。

实现略微有点细节。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
#define DEBUG cout<<"when can get npy"<<endl;
stack<int> sta;
int a[N],tot;
bool vis[N],vis1[N];
void Slove(int n,int k){
	for(int i=0;i<=9;i++)	vis[i]=vis1[i]=false;
	int dis=n,len=0;
	while(dis>0)	sta.push(dis%10),dis/=10;
	tot=0;
	while(!sta.empty())	a[++tot]=sta.top(),sta.pop();
	int ans=0,now=0;
	for(int i=1;i<=tot;i++)	ans=ans*10+9;
	for(int i=1;i<=tot+1;i++){
		int dus=0;
		for(int j=0;j<=9;j++)	dus+=vis[j];
		if(i==tot+1){
			if(dus<=k)	ans=n;
			break;
		}
		if(a[i]==9){
			vis[a[i]]=true,now=now*10+a[i];	
			continue;	
		}
		if(dus>k)	continue;
		for(int j=0;j<=9;j++)	vis1[j]=vis[j];
		int lst=k-dus,predus,nowans=now;
		bool f0=false;
		if(vis1[a[i]+1]==true)	predus=a[i]+1;
		else{
			if(lst>0){
				predus=a[i]+1,vis1[a[i]+1]=true,lst--;	
			}
			else{
				predus=-1;
				for(int j=0;j<=9;j++){
					if(vis1[j]==true&&j>a[i]){
						predus=j;break;
					}
				}
				if(predus==-1){
					f0=true;
				}
			}
		}
		if(f0){
			vis[a[i]]=true,now=now*10+a[i];
			continue;
		}
		nowans=nowans*10+predus;
		int lstU;
		if(lst>0)	lstU=0;
		else{
			for(int j=0;j<=9;j++){
				if(vis1[j]==true)	{lstU=j; break;}
			}
		}
		for(int j=i+1;j<=tot;j++)	nowans=nowans*10+lstU;
		ans=min(ans,nowans);
		vis[a[i]]=true,now=now*10+a[i];
	}
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		Slove(n,k);
	}
	return 0;
}

```

---

## 作者：rainbow_cat (赞：0)

答案长度为 $l$ 的前缀显然为 $n$ 的长度为 $l$ 的前缀，当然 $l$ 可以等于 $0$，由于 $l \le 9$，我们可以直接枚举 $l$。     
其次，要求答案大于等于 $n$，我们枚举答案的第 $l+1$ 位，这个数字显然要大于 $n$ 的第 $l+1$ 位。     
若当前出现的数字恰好为 $m$ 种，则剩余位数用出现过的最小数字填充，若小于 $m$ 种，用 $0$ 填充。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,num,ans,cnt[10];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		memset(cnt,0,sizeof cnt),num=0;
		int tmp=n;
		ans=n;
		while(tmp)cnt[tmp%10]++,tmp/=10;
		tmp=0;
		for(int i=0;i<=9;i++)tmp+=(cnt[i]>0);
		if(tmp<=m)
		{
			cout<<n<<'\n';
			continue;
		}
		while(n)
		{
			cnt[n%10]--,num++;
			if(!cnt[n%10])tmp--;
			if(tmp>m||num<m-tmp)
			{
				n/=10;
				continue;
			}
			for(int i=n%10+1;i<=9;i++)
			{
				cnt[i]++;
				if(cnt[i]==1)tmp++;
				if(tmp<m)
				{
					for(int j=1;j<=num;j++)ans/=10;
					ans=ans*10+i;
					for(int j=1;j<num;j++)ans=ans*10;
					goto ex;
				}
				else if(tmp==m)
				{
					for(int j=0;j<=9;j++)
					{	
						if(cnt[j])
						{
							for(int k=1;k<=num;k++)ans/=10;
							ans=ans*10+i;
							for(int k=1;k<num;k++)ans=ans*10+j;
							goto ex;							
						}
					}
				}
				cnt[i]--;
				if(!cnt[i])tmp--;
			}
			n/=10;
		}
		ex:
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 前言
~~蓝题有点过分了，我这种蒟蒻都可以做出来。~~

思路概括：一位一位枚举。

### 思路

最为简单的方法，并不需要很高深的算法和思路。

因为 $n$ 最多只有 $10$ 位，如果一位一位枚举最慢也不超过 $100$ 次，所以直接从最高位开始枚举，一位一位判断是否成立，这里我用桶记录了当前使用过的数字和当前不同的数字的个数，所以在出现不合法的情况时，直接跳过。


注意当第 $n$ 位的数字大于原数组第 $n$ 位时，对于下一位也就数第 $n-1$ 位，我们就不用再从 $a_{n-1}$ 开始枚举，直接从 $1$ 开始枚举。

因为我的每一位是从最小的开始搜，所以第一个符合条件的就是答案。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,len[100],book[100],ans[100],siz=0;

inline int read(){//快读
	register int x = 0, t = 1;
	register char ch=getchar(); 
	while(ch<'0'||ch>'9'){
		if(ch=='-')
			t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);  
		ch=getchar();
	}
	return x*t;
}

bool dfs(int now,int dif,bool l)
{
//now 是当前在第几位
//dif 表示当前不同数字的数量
//l 用于下面的特判
//return 1 表示合法
//return 0 表示不合法
	if(now==0) return 1;
//走到底，成功。
	if(dif>k) return 0;
//超过限制，失败，但没啥用，因为上一层DFS计算过了。
	int flag,chan=0;
	for(int i=0;i<=9;i++)
	{
		if(l!=1 && i<len[now]) continue;
//判断i是否可以取到，l表示上一位也就是now-1，是否超过len[now-1]，用于取尽可能小的值。
		if(book[i]==0)
			book[i]++,
			chan=1;
//判断是否有新的数字出现。
		if(dif+chan<=k)
		{
//超过限制，失败。
			ans[now]=i;
			flag=dfs(now-1,dif+chan,(i>len[now]?1:l));
//flag记录后面的DFS是否成功 now-1下一位 dif+chen上一层和当前层的不同的数字的数量 (i>len[now]?1:l)看第36行
			if(flag==1) return 1;	
//成功退出
		}
		if(chan==1)
			book[i]=0,
			chan=0;	
//不成功还原
	}
	return 0;
//没啥用
}
signed main()
{
	cin>>t;
	while(t--)
	{
		for(int i=0;i<=15;i++)//初始化
			len[i]=0,book[i]=0,ans[i]=0,siz=0;
		n=read();
		k=read();
		for(int j=n;j>0;)
		{
			siz++;
			len[siz]=j%10;
			j/=10;
		}//拆分n的每一位
		dfs(siz,0,0);
		for(int i=siz;i>=1;i--)
			cout<<ans[i];
		//输出
		cout<<endl;
	}
	return 0;
}

```
[AC记录](https://codeforces.com/contest/1560/submission/284419090)

---

## 作者：zky114514 (赞：0)

[洛谷题目传送门](luogu.com.cn/problem/CF1560F2) || [cf 题目传送门](codeforces.com/problemset/problem/1560/F2)

## [三十](https://codeforces.com/contest/1560/submission/276368820)分做法

暴力出奇迹。

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll t,x,k;
bool ck(ll x){
	ll q=x;
	bool flag[10];
	for(int i=0;i<=9;i++)flag[i]=0;
	while(q){
		ll p=q%10;
		flag[p]=1;
		q/=10;
	}
	int cnt=0;
	for(int i=0;i<=9;i++)cnt+=flag[i];
	return cnt<=k;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>x>>k;
		if(ck(x)){
			cout<<x<<'\n';
			continue;
		}
		while(!ck(x))x++;
		cout<<x<<'\n';
	}
}
```

## [正解](https://codeforces.com/contest/1560/submission/276366694)

贪心。说实话，贪心其实很不错的，但不一定正确。

### 思路
注意到一个结论：答案和 $n$ 同位数，因为当所有位都为 $9$ 时必定满足。

这时找到满足 $a$ 不同位数使得 $a_i\le k$ 的最大前缀加 $1$ 的位置，显然此位需要加 $1$，后面的的位全部修改为 $0$，然后修改 $n$，直到 $n$ 满足条件为止。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int flag[10],t,n,k;
inline bool check(int x,int k){
	int cnt=0;
	for(int i=0;i<=9;i++)flag[i]=0;
	while(x){
		if(!flag[x%10])cnt++;
		flag[x%10]=1;
		x/=10;
	}
	return cnt<=k;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		while(!check(n,k)){
			int l=1,r=n;
			while(!check(r,k)){
				l*=10;
				r/=10;
			}
			l/=10;
			n=((n/l)+1)*l;
		}
		cout<<n<<'\n';
	}
	return 0;
}
```

---

## 作者：GeXiaoWei (赞：0)

# CF1560F2 Nearest Beautiful Number (hard version)
## 解析
我们可以定义一个变量 $flag$ 表示是否找到最小解，变量 $big$ 表示构造的数 $x$ 是否比题目给定的 $n$ 大，随后桶数组，表示 $x$ 每位数的出现次数。

找数字时，从小到大遍历，一旦找到合适的数，即可直接输出，节省超多时间。如果搜索时新添一位后出现的位数大于 $k$ 并且这一位以前从未出现，那么一定不行，不要搜索了。否则可以继续搜，注意回溯取消操作。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,k,flag,big,f[1005];
string p,path;
void dfs(string n,int k,int wei,int sum){
	if(flag==1) return ;//已经有解
	if(wei==n.size()){//位数足够
		cout<<path<<"\n",flag=1;
		return ;
	}
	for(char i=big?'0':n[wei];i<='9';i++){
		if(flag==1) return ;
		if(!f[i]&&sum+1>k) continue;
		f[i]++,path+=i;
		if(i>n[wei]) big=1;
		if(f[i]==1) dfs(n,k,wei+1,sum+1);//多一位数位加一
		else dfs(n,k,wei+1,sum);
		big=0,path.erase(path.size()-1),f[i]--;//回溯取消
	}
}
int main(){
	scanf("%lld",&t);
	while(t--){
		cin>>p>>k;big=flag=0,path="",memset(f,0,sizeof(f));//赋初值
		dfs(p,k,0,0);
	}
	return 0;
}
```

---

## 作者：MMXIandCCXXII (赞：0)

$\Large{\text{Solution}}$

第一次模拟赛切蓝，纪念一下。

其实我是在想 F1 的时候想到的做法，~~（当时没想到打表）~~。模拟这个样例：`177890 2`。

要保留两种不同数字，我们肯定从高位开始保留，这样才最小。所以我们先保留到 `177xxx`，但是 `8` 和前面的不一样，这是我们就会想到把它变成比 `8` 大的，前面出现过的最小的数（例：`998244353` 先变成 `999244353`）。但是没有这样的数，所以我们只能变成 `178000`。这样我们就能向答案一步步靠近并且保证不超过。递归次数不多，所以不会超时。

$\Large{\text{Code}}$
```cpp
#include <bits/stdc++.h>
#include <windows.h>
#define int long long
using namespace std;

int n, k;

int dfs(int x)
{
//	cout << x << endl;
//	Sleep (500);
	bool vis[10];
	int a[20];
	memset (a, 0, sizeof a);
	memset (vis, false, sizeof vis);
	int tep = x;
	while (tep)
	{
		a[++a[0]] = tep % 10;
		tep /= 10;
	}
	int cnt = 0;
	for (int i = a[0]; i >= 1; i--)
	{
		if (!vis[a[i]]) cnt++;
		vis[a[i]] = true;
		if (cnt > k)
		{
			int j;
			for (j = 0; j <= 9; j++)
				if (vis[j] && j > a[i]) break;
			if (j > a[i])
				return dfs (x / (int) (pow (10, i)) * pow (10, i) + j * pow (10, i - 1));
			else return dfs (x / (int) (pow (10, i)) * pow (10, i) + pow (10, i));
		}
	}
	return x;
}

signed main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n >> k;
		cout << dfs (n) << endl;
	}
	return 0;
}

```

---

## 作者：happybob (赞：0)

题意：给定 $n,k$。定义一个数是美好的当且仅当这个数的十进制无前导零表示下数位上不同数个数 $\leq k$，求 $\geq n$ 的最小的美好的数。多测。$1 \leq n \leq 10^9, 1 \leq k \leq 10$。

首先我们可以证明答案的位数一定和 $n$ 的位数相等，因为每一位都填 $9$ 一定合法且 $\geq n$。

考虑数位 DP，每一位从小到大枚举当前能填的，用一个二进制数记录一下目前哪些数是存在的，这和状压的做法类似。记忆化一下，填成功了直接输出即可。

```cpp
#pragma GCC optimize("-Ofast,fast-math,-inline")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

const int N = 11, M = (1 << 11);

#ifndef ONLINE_JUDGE
#define __builtin_popcount __popcnt
#endif

bitset<M> f[N][2];

int t, n, k;
string s;

bool dfs(int u, bool zgw, int bt, long long now)
{
	if (__builtin_popcount(bt) > k) return 0;
	if (u > s.size() + 1) return 0;
	if (u == s.size() + 1)
	{
		cout << now << "\n";
		return 1;
	}
	if (!f[u][zgw][bt]) return f[u][zgw][bt];
	f[u][zgw][bt] = 0;
	int minn = (zgw ? s[u - 1] - '0' : (u == 1 ? 1 : 0));
	for (int i = minn; i <= 9; i++)
	{
		if (dfs(u + 1, (zgw && (i == minn)), bt | (1 << i), now * 10 + i)) return 1;
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		cin >> n >> k;
		for (int i = 0; i < N; i++)
		{
			f[i][0].set();
			f[i][1].set();
		}
		s = to_string(n);
		dfs(1, 1, 0, 0);
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1560F2 题解



## 思路分析

提供一个能解决两个版本的做法。

考虑直接进行 dp，记 $dp_{i,\mathbf S}$ 表示当前填第 $i$ 位，用过的数码构成集合 $\mathbf S$ 时，第 $i\sim 0$ 位所取得的的最小数值，然后状压 $\mathbf S$ 再套一个 dfs 解数位 dp 的板子即可，搜索的时候要记住从理论最高位（第 $9$ 位）开始搜索并且记录一下当前是否在前导零状态下即可。

由于其取得最小数值一定要先让高位尽可能小，因此查到一组解可以直接 `break`。

时间复杂度 $\Theta(2^{10}\cdot\log_{10}n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=11,MAXS=1<<10;
const int b[]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
inline int bit(int x) { return 1<<x; }
int n,k,dp[MAXN][MAXS],a[MAXN];
bool vis[MAXN][MAXS];
inline int dfs(int dig,int S,bool lim,bool qd) {
	if(dig<0) return __builtin_popcount(S)<=k?0:-1; 
	if(!lim&&vis[dig][S]) return dp[dig][S];
	int ret=-1;
	for(int i=(lim?a[dig]:0);i<10;++i) {
		int k=dfs(dig-1,(qd&&i==0)?0:S|bit(i),lim&&(i==a[dig]),qd&&(i==0));
		if(k!=-1) {
			ret=b[dig]*i+k;
			break;
		}
	}
	if(!lim) vis[dig][S]=true,dp[dig][S]=ret;
	return ret;
}
inline void solve() {
	memset(dp,-1,sizeof(dp));
	memset(vis,false,sizeof(vis));
	scanf("%d%d",&n,&k);
	int len=0;
	while(n) {
		a[len]=n%10;
		n/=10,++len;
	}
	for(int i=len;i<=9;++i) a[i]=0;
	printf("%d\n",dfs(9,0,true,true));
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
} 
```



---

## 作者：_edge_ (赞：0)

来补充一下不用贪心，好写模板化的数位 DP。

事实上，在本题解之前 F1 已经有 dalao 二分+预处理了。

但是我们到 F2 的时候，会发现数量比较大，可能无法预处理了。

这个时候，数位 DP 就有了代替这个的优势。

首先，看到这个题目，显然是要用二分。

关键是二分之后如何 check，假定我们二分的值为 $Mid$，那么需要统计的即为 $[l,Mid]$ 这个区间内的符合要求的个数。

转化成这样之后，可以利用数位 DP 来做。

不同的数，那么就把他状压下来，然后对于前导零进行一些特判即可。

数位 DP 模板挺好写的。

注意这里有多测的原因，数位 DP 记得把上限的给去掉。

具体的，我们设 $f_{i,j,k,l}$ 表示现在是第 $i$ 位，$0/1$ 表示是否有前导零，$k$ 类似于状压，对于第 $n$ 位如果为 $1$，那么则 $n$ 出现过，对于 $l$ 是目前不能超过的数。

然后在做的时候，枚举每一位是啥即可。

最后判一下出现数数量是否小于等于 $l$ 即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long 
using namespace std;
const int INF=15;
const int INFM=11;
int t,f[INF][2][1<<INFM][INFM],n,k;
//     位数,前导零,位数状态压缩,不超过多少?
int g[INF];
int calc(int x) {
	int kk=0;
	while (x) kk++,x-=x&-x;
	return kk;
}
int DFS(int a1,int a2,int a3,int a4,int a5) {
	if (!a1) return calc(a4)<=a5;
	if (!a2 && ~f[a1][a3][a4][a5]) return f[a1][a3][a4][a5];
	int Max=a2?g[a1]:9,res=0;
	for (int i=0;i<=Max;i++) {
		int xx=a4;
		if (i==0 && a3) ;
		else xx|=(1<<i);
		res+=DFS(a1-1,a2 && i==Max,a3 && i==0,xx,a5);
	}
	if (!a2) f[a1][a3][a4][a5]=res;
	return res;
}
int calc(int x,int k) {
	memset(g,0,sizeof g);
	while (x) {
		g[++g[0]]=x%10;
		x/=10;
	}
	return DFS(g[0],1,1,0,k);
}
bool check(int xx,int yy,int zz) {
	return calc(xx,zz)-calc(yy-1,zz)>0;
}
signed main()
{
	memset(f,255,sizeof f);
	ios::sync_with_stdio(false);
	cin>>t;
	while (t--) {
		cin>>n>>k;
		int l=n,r=2e9,ans=-1;
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (check(Mid,n,k)) r=(ans=Mid)-1;
			else l=Mid+1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

