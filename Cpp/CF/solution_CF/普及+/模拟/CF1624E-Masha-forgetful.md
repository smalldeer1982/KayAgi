# Masha-forgetful

## 题目描述

Masha 认识了一个新朋友并且获得了他的电话号码 $s$。她想要尽快地记住它。电话号码是一个长度为 $m$，由 $0\sim 9$ 构成的字符串。电话号码有可能以 $0$ 开始。

Masha 已经知道了 $n$ 个电话号码（所有的电话号码长度都为 $m$）。如果新的电话号码 $s$ 能拆分成几段并且存在于她已经知道的电话号码中，她能够更容易得记住新号码。每一个段的长度都必须大于等于 $2$，否则 Masha 会因为有太多的段而混淆。

举个例子，Masha 需要记住的号码 $s$ 是 $\texttt{12345678}$，并且她知道 $n=4$ 个号码：$\texttt{12340219}$，$\texttt{20215601}$，$\texttt{56782022}$，$\texttt{12300678}$。你可以用在 $s$ 中拆分成 $3$ 段：$\texttt{1234}$ 在第一个号码中，$\texttt{56}$ 在第二个号码中，$\texttt{78}$ 在第三个号码中。当然还有其它分解 $s$ 的方法。

Masha 想要你来帮她，她想让你把电话号码 $s$ 拆分成几个长度大于等于 $2$ 的字符串，并且在她知道的电话号码中存在。如果有多个答案，请输出其中的任意一个。

## 样例 #1

### 输入

```
5

4 8
12340219
20215601
56782022
12300678
12345678

2 3
134
126
123

1 4
1210
1221

4 3
251
064
859
957
054

4 7
7968636
9486033
4614224
5454197
9482268```

### 输出

```
3
1 4 1
5 6 2
3 4 3
-1
2
1 2 1
2 3 1
-1
3
1 3 2
5 6 3
3 4 1```

# 题解

## 作者：XL4453 (赞：6)

### $\text{Difficulty : 2000}$
---
### 解题思路：

本题没有要求结果分解出来的字串最小，因此难度降低了很多。

考虑将所有的可以记住的字符串分成若干个长度为 $2$ 或者 $3$ 的字串，并用一个哈希记录下来，相同的可以直接覆盖，反正都是一样的。

然后对于每一个需要记忆的位置，记录下 $f_i$ 表示是否可行（用 $0$ 或非 $0$ 表示），若可行需要几次，每一个 $f_i$ 都可以从 $f_{i-2}$ 或者 $f_{i-3}$ 通过补足一个之前哈希下来的字串转移。同时记录路径。

---
分解后的字串数量依旧是和 $m$ 同阶的，所以总复杂度是 $O(nm)$ 的可以接受。

而且由于二和三完全可以表示所有的长度大于 $2\times3-2-3=1$ 的字串，可以担任表示的任务。

注意多测清空。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
struct str{
	int l,r,id;
}t[3005];
int T,n,a[1005][1005],m,fr[1005],f[1005],ans[1005],b[1005],rec[1005],cnt;
int hash(int num1,int num2,int num3){
	if(num1==0)num1=10;if(num2==0)num2=10;if(num3==0)num3=10;
	if(num1==-1)num1=0;
	return num1*121+num2*11+num3;
}
void init(){
	cnt=0;
	for(int i=1;i<=3000;i++)t[i].id=t[i].l=t[i].r=0;
	for(int i=1;i<=1000;i++)fr[i]=f[i]=ans[i]=b[i]=rec[i]=0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		init();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){			
			for(int j=1;j<=m;j++)
			scanf("%1d",&a[i][j]);
			
			for(int j=2;j<=m;j++){
				int num=hash(-1,a[i][j-1],a[i][j]);
				t[num].l=j-1;t[num].r=j;t[num].id=i;
			}
			for(int j=3;j<=m;j++){
				int num=hash(a[i][j-2],a[i][j-1],a[i][j]);
				t[num].l=j-2;t[num].r=j;t[num].id=i;
			}
		}
		for(int i=1;i<=m;i++)scanf("%1d",&b[i]);
		f[0]=1;
		for(int i=2;i<=m;i++){
			if(f[i-2]){
				int num=hash(-1,b[i-1],b[i]);
				if(t[num].id!=0){
					f[i]=f[i-2]+1;fr[i]=i-2;ans[i]=num;
				}
			}
			if(i==2)continue;
			if(f[i-3]){
				int num=hash(b[i-2],b[i-1],b[i]);
				if(t[num].id!=0){
					f[i]=f[i-3]+1;fr[i]=i-3;ans[i]=num;
				}
			}
		}
		if(f[m]==0){
			printf("-1\n");
			continue;
		}
		printf("%d\n",f[m]-1);
		int now=m;
		while(now){
			rec[++cnt]=now;
			now=fr[now];
		}
		for(int i=cnt;i>=1;i--)
		printf("%d %d %d\n",t[ans[rec[i]]].l,t[ans[rec[i]]].r,t[ans[rec[i]]].id);
	}
	return 0;
}
```

---

## 作者：huyiyang (赞：2)

# [E.Masha-forgetful](https://codeforces.com/contest/1624/problem/E)
## 题目
给你一个长度为 $m$ 的字符串 $s$ 和 $n$ 个字符串 $a_i(1\le i\le n)$，问你需要如何用 $a_i$ 的长度 $\ge 2$ 的子串拼出 $s$。
## 思路
我们发现，长度 $\ge 2$ 的字符串均可分解为长度为$2$的字符串和长度为 $3$ 的字符串。
于是我们可以把长度为 $2$ 和 $3$ 的字符串用 $\texttt{map}$ 记录下来，然后进行 $\texttt{dp}$ ，判断可行性，之后只要找出 $\texttt{dp}$ 的一种路径就可以了。
## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
bool dp[1111];
string a[1111],s;
map<string,int>b,null,l,id;
int main(){
	cin>>t;
	while(t--){
		b=null;
		l=null;
		id=null;
		cin>>n>>m;
		for(int i=1;i<=m;i++)dp[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(m>1){
				for(int j=0;j+2<a[i].length();j++){
					//记录
					b[a[i].substr(j,2)]=1;
					l[a[i].substr(j,2)]=j;
					id[a[i].substr(j,2)]=i;
					b[a[i].substr(j,3)]=1;
					l[a[i].substr(j,3)]=j;
					id[a[i].substr(j,3)]=i;
				}
				b[a[i].substr(a[i].length()-2,2)]=1;
			l[a[i].substr(a[i].length()-2,2)]=a[i].length()-2;
				id[a[i].substr(a[i].length()-2,2)]=i;
			}
		}
		cin>>s;
		if(m==1){//特判
			cout<<-1<<endl;
			continue;
		}
		//dp
		dp[0]=1;
		for(int i=2;i<=m;i++){
			if(b.count(s.substr(i-2,2)))dp[i]|=dp[i-2];
			if(i>2&&b.count(s.substr(i-3,3)))dp[i]|=dp[i-3];
		}
		if(dp[m]){
			int ans=0;
			for(int i=m;i;){
				if(dp[i-2])i-=2;
				else if(dp[i-3])i-=3;
				else break;
				ans++;
			}
			cout<<ans<<endl;
			stack<string>st;
			for(int i=m;i;){
				ostringstream oss;
				if(dp[i-2]){
					oss<<l[s.substr(i-2,2)]+1<<' '
					<<l[s.substr(i-2,2)]+2<<' '
					<<id[s.substr(i-2,2)]<<endl;
					i-=2;
				}
				else if(dp[i-3]){
					oss<<l[s.substr(i-3,3)]+1<<' '
					<<l[s.substr(i-3,3)]+3<<' '
					<<id[s.substr(i-3,3)]<<endl;
					i-=3;
				}
				else break;
				st.push(oss.str());
			}
			while(!st.empty()){
				cout<<st.top();
				st.pop();
			}
		}
		else cout<<-1<<endl;
	}
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# CF1624E - Masha Forgetful 题解

## 题目大意

给定 $n+1$ 个长度为 $m$ 的数字串，问最后一个数字串能否切割成若干个长度 $>1$ 的字串，使得这些字串均在前 $n$ 个数字串内出现过

如果可以的话，请输出一种方案，否则输出 $-1$

## 思路分析

可以证明，每一个长度 $>1$ 的字符串都能被切割成若干个长度为 $2$ 的字串和若干个长度为 $3$ 的字串

所以只需要考虑最后一个数字串被切割成长度为 $2$ 或 $3$ 的字串的情况

考虑用哈希表来存储前 $n$ 个数字串里长度为 $2$ 和 $3$ 的所有字串

然后用 $f[i]$ 记录最后一个数字串的第 $i$ 位切割成了长度为 $2$ 的字串还是长度为 $3$ 的字串，如果都不行的话就是 $0$

所以无解的情况就是 $f[m]=0$

显然边界条件是 $f[0]=1$ 因为长度为 $0$ 时一定可以（赋值为 $1$ 是因为区别于 $0$，表示可以转移)

状态转移方程就很好写出了：

```cpp
//mp是一个哈希表，记录了前n个串内所有长度为2和3的字串
//mp.find(x)返回一个迭代器表示x出现的位置，如果找不到返回mp.end()，用来判断有没有出现
if(i>=3&&mp.find(s.substr(i-3,3))!=mp.end()&&f[i-3]) f[i]=3; //长度为2的情况
if(i>=2&&mp.find(s.substr(i-2,2))!=mp.end()&&f[i-2]) f[i]=2; //长度为3的情况
```

时间复杂度 $\Theta(nm)$ （一般认为哈希表的时间复杂度是常数）

## 代码呈现

```cpp
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
//pbds哈希表的头文件 
#include<bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds; 
//pbds的命名空间 
const int MAXN=1e6+1;
int f[MAXN];
struct node {
	int l,r,belong;
	//l,r表示字串的左右区间，belong表示来自哪个数字串 
	node() { l=r=belong=0; }
};
inline node cn(int l,int r,int belong) {
	//用l,r,belong构造一个node节点 
	node ans;
	ans.l=l,ans.r=r,ans.belong=belong;
	return ans;
}
gp_hash_table <string,node> mp; 
//pbds的哈希表，操作和stl里的map基本相同，不过可能快一点 
vector <node> ans; //ans记录答案 
inline void solve() {
	mp.clear(); ans.clear(); memset(f,0,sizeof(f)); //清空 
	int n,m;
	cin>>n>>m;
	for(register int i=1;i<=n;++i) {
		string x;
		cin>>x;
		for(register int j=0;j<m-1;++j) {
			//插入长度为2的字串 
			mp[x.substr(j,2)]=cn(j,j+1,i);
		}
		for(register int j=0;j<m-2;++j) {
			//插入长度为3的字串
			mp[x.substr(j,3)]=cn(j,j+2,i);
		}
	}
	f[0]=1; //边界 
	string s;
	cin>>s;
	for(register int i=1;i<=m;++i) {
		//转移 
		if(i>=3&&mp.find(s.substr(i-3,3))!=mp.end()&&f[i-3]) f[i]=3;
		if(i>=2&&mp.find(s.substr(i-2,2))!=mp.end()&&f[i-2]) f[i]=2;
	}
	if(f[m]==0) {
		cout<<"-1"<<'\n';
		return ;
	}
	int pos=m;
	while(pos) {
		//记录答案 
		string tmp=s.substr(pos-f[pos],f[pos]);
		ans.push_back(mp[tmp]);
		pos-=f[pos];
	}
	reverse(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(register auto i:ans) cout<<i.l+1<<' '<<i.r+1<<' '<<i.belong<<'\n';
	//注意储存节点是以0为初始的，所以输出时要+1 
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) solve(); //多组数据 
	return 0;
} 
```



---

## 作者：Hhy140516 (赞：1)

[CF1624E](https://www.luogu.com.cn/problem/CF1624E)
# 题意
有 $n$ 和长度为 $m$ 的已知电话号码。

现有一新号码 $s$，想让你把电话号码 $s$ 拆分成几个长度大于等于 2 的字符串，使得拆出的字符串是已知字符串的子串。
# 分析
先把已知字符串分解成长度为 $2$ 或 $3$ 的子串，再对 $s$ 进行动态规划，判断是否可行。边动态规划还要记录操作。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
const int kMaxN = 1e3 + 5 ;
map<string , int> f ;
map<string , tuple<int , int , int> > pos ;
bool dp[kMaxN] ;
int pr[kMaxN] ;
int main() 
{
    int t ;
    cin >> t ;
    while(t--)
    {
        int n , m ; 
    	cin >> n >> m ;
    	memset(dp , 0 , sizeof dp) ;
        memset(pr , 0 , sizeof pr) ;
        vector<string> v ;
        dp[0] = 1 ;
        for( int i = 1 ; i <= n ; i++ )
    	{
            string s ; 
    		cin >> s ;
            for( int j = 0 ; j < m ; j++ ) 
    		{
                string t ;
                t += s[j] ; 
                for( int k = 1 ; k <= 2 ; k++ ) 
    			{
                    if (k + j >= m) break ;
                    t += s[j + k] ;
                    if (!f[t]) 
    				{
                        f[t] = 1 ;
                        pos[t] = {j , j + k , i} ;
                        v.push_back(t) ;
                    }
                }
            }
        }
        string s ; 
    	cin >> s ;
        for( int i = 0 ; i < m ; i++ )
    	{
            string t ;
            t += s[i] ;
            for( int k = 1 ; k <= 2 ; k++ )
    		{
                if (i - k < 0) break ;
                t = s[i - k] + t ;
                if (f[t] && dp[i - k]) 
    			{
                    dp[i + 1] = 1 ;
                    pr[i + 1] = i - k ;
                }
                if (dp[i + 1]) break ;
            }
        }
        for(string t : v) 
    	{
            f[t] = 0 ;
        }
        if(!dp[m]) 
    	{
            cout << "-1\n" ;
            continue ;
        }
        vector<tuple<int , int , int> > ans ;
        for( int k = m ; k > 0 ; ) 
    	{
            int p = pr[k] ;
            string t = s.substr(p, k - p) ;
            ans.push_back(pos[t]) ;
            k = p ;
        }
        cout << ans.size() << "\n" ;
        reverse(ans.begin() , ans.end()) ;
        for( auto it : ans ) 
        {
            int l , r , i ;
            tie(l , r , i) = it ;
            cout << l + 1 << " " << r + 1 << " " << i << "\n" ;
        }
    }
    return 0 ;
}    
```
**注：本题解参考了这题[codeforces](https://codeforces.com/)的官方题解。**

---

## 作者：Bh_hurter (赞：1)

# CF1624E题解
## 题目描述
给 $n$ 个长度为 $m$ 的字符串，还有一个长度也为 $m$ 的字符串 $s$ 。  

把数字字符串 $s$ 从前往后分出 $k$ 个互不相交的子串（子串长度 $\ge 2$），都能在 $n$ 个已知的字符串中找到即可。答案可能不唯一。  

## 思路
只要有合法解，找到一种匹配即可。那每次匹配的时候肯定是能匹配的长度越短越好，比如，$2$ 个字符串有 “12341” ，“11145”，$s =$“12345”，我们可以找到“123”，再找到“45”。但如果我们找到“1234”，“5”就匹配不上了。

那是不是每次都匹配长度 $2$ 就可以了呢？显然刚才例子中需要匹配长度为 $3$ 长度的子串，由此可以想到对任意一个长度的字符串，我们都可以将其分解为若干个长度为 $2$ 和 $3$ 的字符串。也就是任意数字 $num$ 都有， $num = 2 \times x+3 \times y$ 。

所以可以提前标记 $n$ 个字符串中所有长度为 $2$ 和 $3$ 的字符串，然后模拟字符串 $s$ 中。之后根据这些标记的子串，可以搜索 $s$ 串。  
## AC Code

```cpp
#include<iostream>
#include<cstring>
using namespace std;
string a[1003],s;
struct node{
    int l,r,id;
}z[250][250][250],path[600];//标记两个长度或者三个长度字符串的左右下标+出现的字符串id
bool v[150][150][150];//标记改字符串有没有出现过
int dp[1003];
int n,m,flag;
void dfs(int l, int k){//从s串的l下标开始搜子串，找到就填到path[k]上
    if(dp[l])return;//注意标记，重复搜会时间超限
    if(l==m){
        flag=1;
        printf("%d\n",k-1);
        for(int i=1;i<k;i++){
            printf("%d %d %d\n",path[i].l+1,path[i].r+1,path[i].id);
        }
        return ;
    }
    if(l==m-1)return;//不能分解的只剩一个
    if(flag){//优化
        return;
    }
    if(l+1<m && v['9'+1][s[l]][s[l+1]]){//2个长度的串
        path[k]=z['9'+1][s[l]][s[l+1]];
        dfs(l+2,k+1);
    }
    if(l+2<m && v[s[l]][s[l+1]][s[l+2]]){//3个长度的串
        path[k]=z[s[l]][s[l+1]][s[l+2]];
        dfs(l+3,k+1);
    }
    dp[l]=1;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        memset(dp,0,sizeof dp);
        memset(v,0,sizeof v);
        cin >> n >> m;//知道n个电话号码，号码是m位
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            for(int j = 0; j < m; j++){
                if(j + 1 < m){
                    z['9'+1][a[i][j]][a[i][j+1]] = {j, j+1, i};
                    v['9'+1][a[i][j]][a[i][j+1]] = 1;
                }
                if(j + 2 < m){
                    z[a[i][j]][a[i][j+1]][a[i][j+2]] = {j, j+2, i};
                    v[a[i][j]][a[i][j+1]][a[i][j+2]] = 1;
                }
            }
        }
        cin >> s;//待拆分的
        flag = 0;
        dfs(0, 1);//从下标0开始拼字符串s
        if(flag == 0){
            cout << -1 << endl;
        }
    }
    return 0;
}

```

---

## 作者：AFewSuns (赞：1)

**CF764 Div.3（VP） 做题记录**

- A. plus One on the Subset

- B. Make AP

- C. Division by Two and Permutation

- D. Palindromes Coloring

- $\color{red}\texttt{E. Masha-forgetful}$

- F. Interacdive Problem

- G. MinOr Tree

### 题目大意

$t$ 组询问，每次给定 $n$ 个长度为 $m$ 的文本串，再给定一个长度为 $m$ 的模式串。你需要把模式串划分为若干个长度大于 $1$ 的子串，使得每个子串都可以与文本串匹配。

$1 \leq t \leq 10^4,1 \leq n,m \leq 10^3,\sum n\times m \leq 10^6$

### 题目分析

差点没做出这道题，个人认为是本场比赛最难的题。

设 $ck_i$ 为模式串前 $i$ 个字符 $s_{1\cdots i}$ 是否可以被划分成功。初始化 $ck_0=1$，然后再考虑从前面转移。

有个很暴力的想法，就是把文本串中的每个子串塞进 trie 里，然后把模式串中的每个子串都尝试匹配一下。时间复杂度 $O(nm^3+m^3)$。

可能有人说：我会优化！直接把每个文本串的前缀插入 trie 就行了，匹配的时候照样匹配。时间复杂度 $O(nm^2+m^3)$。

同理，匹配的时候也只匹配前缀，时间复杂度 $O(nm^2+m^2)$。

反正我一开始是这样写的，还没 TLE 就先 RE 了……代码就不贴了。

怎么办呢？时间复杂度的瓶颈在于插入与查询串，特别是当这个串很长的时候。

同时，如果一个长度为 $len$ 的字符串能被匹配，那么它的子串一定能匹配。我们能不能尽量匹配一些长度小的串呢？

因为题目要求划分出来的字符串长度要大于 $1$，所以我们选取长度为 $2$ 和 $3$ 的字符串。这时发现，所有长度大于 $1$ 的串都能被若干长度为 $2$ 和 $3$ 的子串划分（证明显然），这意味着我们只需插入与查询长度为 $2$ 和 $3$ 的字符串了！

重新梳理一遍，如果一个字符串匹配成功了，把它划分成一些长度为 $2$ 和 $3$ 的子串，那么这其实等价于这些子串匹配成功了，$ck_i$ 同样会被转移。

因为只有两种串，而且种类不多，所以就用数组替代了 trie。$ck_i$ 也只用由 $ck_{i-2}$ 和 $ck_{i-3}$ 转移。

时间复杂度约为 $O(nm)$，记得多测清空。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll t,n,m,pre[1010],lst[1010];
char c[1010];
bool ck[1010];
struct node{
	ll l,r,id;
}f2[99],f3[999],f[1010];//f2记录两位的字符串信息，f3记录三位的字符串信息，f记录ck（答案）的信息 
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld %lld",&n,&m);
		for(ll i=1;i<=n;i++){
			scanf("%s",c+1);
			for(ll j=1;j<=m-1;j++){//枚举两位字符串 
				ll tmp=(c[j]-'0')*10+(c[j+1]-'0');
				f2[tmp]=(node){j,j+1,i};
			}
			for(ll j=1;j<=m-2;j++){//枚举三位字符串 
				ll tmp=(c[j]-'0')*100+(c[j+1]-'0')*10+(c[j+2]-'0');
				f3[tmp]=(node){j,j+2,i};
			}
		}
		scanf("%s",c+1);
		ck[0]=1;
		for(ll i=1;i<=m;i++){
			ll tmp;
			if(i>1){
				tmp=(c[i-1]-'0')*10+(c[i]-'0');
				if(f2[tmp].id){
					if(ck[i-2]){//从ck[i-2]转移 
						ck[i]=1;
						lst[i]=i-2;//lst表示从哪里转移过来，便于输出答案 
						f[i]=f2[tmp];
					}
				}
			}
			if(i>2){
				tmp=(c[i-2]-'0')*100+(c[i-1]-'0')*10+(c[i]-'0');
				if(f3[tmp].id){
					if(ck[i-3]){//从ck[i-3]转移 
						ck[i]=1;
						lst[i]=i-3;
						f[i]=f3[tmp];
					}
				}
			}
		}
		if(!ck[m]) printf("-1\n");//无解 
		else{
			ll ans=0;
			for(ll i=m;i;i=lst[i],ans++) pre[lst[i]]=i;//因为要从前往后输出，所以倒过来了 
			printf("%lld\n",ans);
			for(ll i=pre[0];i;i=pre[i]) printf("%lld %lld %lld\n",f[i].l,f[i].r,f[i].id);
		}
		for(ll i=0;i<=99;i++) f2[i]=(node){0,0,0};//记得清空 
		for(ll i=0;i<=999;i++) f3[i]=(node){0,0,0};
		for(ll i=1;i<=m;i++) f[i]=(node){0,0,0};
		for(ll i=1;i<=m;i++) ck[i]=0;
		for(ll i=0;i<=m;i++) lst[i]=pre[i]=0;
	}
}
```

---

## 作者：__cheems__ (赞：1)

## 题目描述

给出 $n$ 个长度为 $m$ 的字符串，要求给出一种包含一个或多个长度 $\ge 2$ 的子串的构造，使得它们拼出一个长度为 $m$ 目标字符串。

## 解题思路

考虑哈希、动规、搜索。

题目并无要求子串数量最少。我们考虑尽可能用长度为 $2$ 的子串进行拼接。然而长度为 $2$ 的子串无法拼出所有长度的字符串，因此还需要长度 $3$ 的子串进行拼接。用一个哈希表存储每个长度为 $2$ 与 $3$ 的子串的位置，然后枚举目标字符串的每一个长度 $2$ 与 $3$ 的子串，在哈希表中查询子串的位置进行拼接即可。代码如下。

```cpp
// p[i] 表示第 i 个字符串，s 为目标字符串。sp, mp为哈希表。
for (int i = 1; i <= n; i++)
{
	for (int j = 0; j < m - 1; j++)
	{
		string k = "";
		k = k + p[i][j]; k = k + p[i][j + 1];
		mp[k].l = j; mp[k].r = j + 1; mp[k].id = i;
		sp[k] = 1;
	}
	for (int j = 0; j < m - 2; j++)
	{
		string k = "";
		k = k + p[i][j]; k = k + p[i][j + 1]; k = k + p[i][j + 2];
		mp[k].l = j; mp[k].r = j + 2; mp[k].id = i;
		sp[k] = 1;
	}
}
for (int i = 0; i < m; i++)
{
	if (i + 2 < m)
   	{
    	  	string temp = "";
		temp = temp + s[i]; temp = temp + s[i + 1]; temp = temp + s[i + 2];
    		if (sp[temp] == 1) { id3[i] = mp[temp].id; l3[i] = mp[temp].l; r3[i] = mp[temp].r; }
    	}
        if (i + 1 < m)
        {
            string temp = "";
            temp = temp + s[i];
            temp = temp + s[i + 1];
            if (sp[temp] == 1) { id2[i] = mp[temp].id; l2[i] = mp[temp].l; r2[i] = mp[temp].r; }
        }
}
```

然后是动规部分。对于动规数组 $dp$ 而言，每一个 $dp_i$ 表示长度为 $i$ 的字符串，从 $dp_i$ 拼接子串而来。代码如下。

```cpp
dp[0] = 0;
for (int i = 1; i <= m; i++)
{
	if (i >= 3)
		if ((l3[i - 3] != 0 || r3[i - 3] != 0 || id3[i - 3] != 0) && dp[i - 3] != -1) dp[i] = i - 3;
	if (i >= 2)
		if ((l2[i - 2] != 0 || r2[i - 2] != 0 || id2[i - 2] != 0) && dp[i - 2] != -1) dp[i] = i - 2;
}
```

最后是搜索部分。这部分的代码可以直接通过动规数组推算而来。代码如下。

```cpp
void dfs(int step)
{
	if (step <= 0) return ;
	if (dp[step] == step - 3)
	{
		sum++;
		ansl[sum] = l3[step - 3] + 1, ansr[sum] = r3[step - 3] + 1, ansid[sum] = id3[step - 3];
		dfs(step - 3);
	}
	if (dp[step] == step - 2)
	{
		sum++;
		ansl[sum] = l2[step - 2] + 1, ansr[sum] = r2[step - 2] + 1, ansid[sum] = id2[step - 2];
		dfs(step - 2);
	}
}
```

搜索完毕后，对于标记答案的数组进行排序，然后输出即可。题目是多测，需要进行清空。

## 解题代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int t, n, m;
string s;
string p[1024];
int dp[1024];
int f[1024];

struct node
{
	int id, l, r;
};

struct nodes
{
	int l, r, id, rk;
};

bool cmp(nodes x, nodes y)
{
	return x.rk < y.rk;
}

nodes g[1024];
unordered_map<string, node> mp;
map<string, bool> sp;
int l2[1024], r2[1024], id2[1024];
int l3[1024], r3[1024], id3[1024];
int ansl[1024], ansr[1024], ansid[1024];
int sum = 0;

void dfs(int step)
{
	if (step <= 0) return ;
	if (dp[step] == step - 3)
	{
		sum++;
		ansl[sum] = l3[step - 3] + 1, ansr[sum] = r3[step - 3] + 1, ansid[sum] = id3[step - 3];
		dfs(step - 3);
	}
	if (dp[step] == step - 2)
	{
		sum++;
		ansl[sum] = l2[step - 2] + 1, ansr[sum] = r2[step - 2] + 1, ansid[sum] = id2[step - 2];
		dfs(step - 2);
	}
}

int main()
{
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false); 
	for (int i = 1; i <= 1024; i++) dp[i] = -1;
	cin >> t;
	while (t--)
	{
		sum = 0;
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
		{
			cin >> p[i];
		}
		cin >> s;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < m - 1; j++)
			{
				string k = "";
				k = k + p[i][j];
				k = k + p[i][j + 1];
				mp[k].l = j;
				mp[k].r = j + 1;
				mp[k].id = i;
				sp[k] = 1;
			}
			for (int j = 0; j < m - 2; j++)
			{
				string k = "";
				k = k + p[i][j];
				k = k + p[i][j + 1];
				k = k + p[i][j + 2];
				mp[k].l = j;
				mp[k].r = j + 2;
				mp[k].id = i;
				sp[k] = 1;
			}
		}
		for (int i = 0; i < m; i++)
		{
			if (i + 2 < m)
            {
                string temp = "";
				temp = temp + s[i];
				temp = temp + s[i + 1];
				temp = temp + s[i + 2];
				
                if (sp[temp] == 1)
                {
                	id3[i] = mp[temp].id;
                	l3[i] = mp[temp].l;
                	r3[i] = mp[temp].r;
				}
            }
            if (i + 1 < m)
            {
                string temp = "";
				temp = temp + s[i];
				temp = temp + s[i + 1];
				
                if (sp[temp] == 1)
                {
                	id2[i] = mp[temp].id;
                	l2[i] = mp[temp].l;
                	r2[i] = mp[temp].r;
				}
            }
		}
		dp[0] = 0;
		for (int i = 1; i <= m; i++)
		{
			if (i >= 3)
			{
				if ((l3[i - 3] != 0 || r3[i - 3] != 0 || id3[i - 3] != 0) && dp[i - 3] != -1)
				{
					dp[i] = i - 3;
				}
			}
			if (i >= 2)
			{
				if ((l2[i - 2] != 0 || r2[i - 2] != 0 || id2[i - 2] != 0) && dp[i - 2] != -1)
				{
					dp[i] = i - 2;
				}
			}
		}
		if (dp[m] == -1) cout << -1 << "\n";
		else
		{
			dfs(m);
			cout << sum << "\n";
			for (int i = 1; i <= sum; i++)
			{
				g[i] = (nodes){ansl[i], ansr[i], ansid[i], sum - i + 1};
			}
			sort(g + 1, g + sum + 1, cmp);
			for (int i = 1; i <= sum; i++)
			{
				cout << g[i].l << " " << g[i].r << " " << g[i].id << "\n";
			}
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < m - 1; j++)
			{
				string k = "";
				k = k + p[i][j];
				k = k + p[i][j + 1];
				mp[k].l = 0;
				mp[k].r = 0;
				mp[k].id = 0;
				sp[k] = 0;
			}
			for (int j = 0; j < m - 2; j++)
			{
				string k = "";
				k = k + p[i][j];
				k = k + p[i][j + 1];
				k = k + p[i][j + 2];
				mp[k].l = 0;
				mp[k].r = 0;
				mp[k].id = 0;
				sp[k] = 0;
			}
		}
		
		for (int i = 0; i <= sum; i++)
		{
			g[i] = {0,0,0};
		}
		for (int i = 0; i <= m; i++)
		{
			dp[i] = ansl[i] = ansr[i] = ansid[i] = l2[i] = r2[i] = id2[i] = l3[i] = r3[i] = id3[i] = 0;
			dp[i] = -1;
		}
	}
    return 0;
}

```

---

## 作者：ybclch2026 (赞：0)

## 题目大意
给 $n+1$ 个字符串，问你如何用前 $n$ 个字符串中长度至少为 $2$ 的子字符串拼成第 $n+1$ 字符串，输出任意一个方案。
## 思路
因为子字符串长度至少为 $2$，所以直接暴力处理出长度为 $2$ 和 $3$ 的子字符串，用 map 处起来。

map 中存第几个字符串和子字符串在原字符串的开始下标与最后下标，便于输出方案。

后用 dp 求是否可以拼成。设 $dp_i$ 的值为 $0/2/3$，$0$ 为目标字符串的 $1$ 到 $i$ 位无法拼成；$2$ 为目标字符串的 $1$ 到 $i$ 位可从 $dp_{i-2}$ 处转移；$3$ 为目标字符串的 $1$ 到 $i$ 位可从 $dp_{i-3}$ 处转移。

然后就可以递推求方案了！
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T,dp[1000005],cnt;
struct asw{
    int l,r,op;
};
map<string,asw>mp;
string s;
asw kl[1005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        memset(dp,0,sizeof dp);
        cnt=0;
        cin>>n>>m;
        mp.clear();
        for(int k=1;k<=n;k++){
            cin>>s;
            s=' '+s;
            string t="";
            for(int i=2;i<=m;i++){
                t="";
                t.push_back(s[i-1]);
                t.push_back(s[i]);
                mp[t].l=i-1;
                mp[t].r=i;
                mp[t].op=k;
            }
            for(int i=3;i<=m;i++){
                t="";
                t.push_back(s[i-2]);
                t.push_back(s[i-1]);
                t.push_back(s[i]);
                mp[t].l=i-2;
                mp[t].r=i;
                mp[t].op=k;
            }
        }
        cin>>s;
        if(m==1){
            cout<<-1<<endl;
            continue;
        }
        s=' '+s;
        dp[0]=1; 
        for(int i=0;i<=m;i++){
            if(i<=m-2){
                string h="";
                h.push_back(s[i+1]);
                h.push_back(s[i+2]);
                if(mp[h].op!=0&&dp[i])dp[i+2]=2;
            }
            if(i<=m-3){
                string h="";
                h.push_back(s[i+1]);
                h.push_back(s[i+2]);
                h.push_back(s[i+3]);
                if(mp[h].op!=0&&dp[i])dp[i+3]=3;
            }
        }
        int i=m,f=0;
        while(i>1){
            string h="";
            if(dp[i]==0){
                f=1;
                break;
            }
            for(int o=max(i-dp[i],0)+1;o<=i;o++)h.push_back(s[o]);
            // cout<<h<<endl;
            kl[++cnt]=mp[h];
            i-=dp[i];
        }
        if(f==1||cnt==0){
            cout<<-1<<endl;
            continue;
            // return 0;
        }
        cout<<cnt<<endl;
        for(int i=cnt;i>=1;i--)cout<<kl[i].l<<" "<<kl[i].r<<" "<<kl[i].op<<endl;
    }
    return 0;
} 
```

---

## 作者：BHDwuyulun (赞：0)

### 1 题目描述
给定一个长度为 $m$ 的字符串 $s$ 和 $n$ 个字符串，请问如何用这几个字符串中的各个部分拼出 $s$。
### 2 大体思路
因为题目要求划分出来的字符串长度要大于 $1$，所以我们选取长度为 $2$ 和 $3$ 的字符串。这时发现，所有长度大于 $1$ 的串都能被若干长度为 $2$ 和 $3$ 的子串划分，这意味着我们只需插入与查询长度为 $2$ 和 $3$ 的字符串了。
### 3 AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define bug printf("---OK---")
#define pa printf("A: ")
#define pr printf("\n")
#define pi acos(-1.0)
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
ll t,n,m,pre[1010],lst[1010];
char c[1010];
bool ck[1010];
struct node{
	ll l,r,id;
}f2[99],f3[999],f[1010];
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld %lld",&n,&m);
		for(ll i=1;i<=n;i++){
			scanf("%s",c+1);
			for(ll j=1;j<=m-1;j++){
				ll tmp=(c[j]-'0')*10+(c[j+1]-'0');
				f2[tmp]=(node){j,j+1,i};
			}
			for(ll j=1;j<=m-2;j++){
				ll tmp=(c[j]-'0')*100+(c[j+1]-'0')*10+(c[j+2]-'0');
				f3[tmp]=(node){j,j+2,i};
			}
		}
		scanf("%s",c+1);
		ck[0]=1;
		for(ll i=1;i<=m;i++){
			ll tmp;
			if(i>1){
				tmp=(c[i-1]-'0')*10+(c[i]-'0');
				if(f2[tmp].id){
					if(ck[i-2]){
						ck[i]=1;
						lst[i]=i-2;
						f[i]=f2[tmp];
					}
				}
			}
			if(i>2){
				tmp=(c[i-2]-'0')*100+(c[i-1]-'0')*10+(c[i]-'0');
				if(f3[tmp].id){
					if(ck[i-3]){
						ck[i]=1;
						lst[i]=i-3;
						f[i]=f3[tmp];
					}
				}
			}
		}
		if(!ck[m]) printf("-1\n");
		else{
			ll ans=0;
			for(ll i=m;i;i=lst[i],ans++) pre[lst[i]]=i;
			printf("%lld\n",ans);
			for(ll i=pre[0];i;i=pre[i]) printf("%lld %lld %lld\n",f[i].l,f[i].r,f[i].id);
		}
		for(ll i=0;i<=99;i++){
			f2[i]=(node){0,0,0};
		}
		for(ll i=0;i<=999;i++){
			f3[i]=(node){0,0,0};
		}
		for(ll i=1;i<=m;i++){
			f[i]=(node){0,0,0};
		}
		for(ll i=1;i<=m;i++){
			ck[i]=0;
		}
		for(ll i=0;i<=m;i++){
			lst[i]=pre[i]=0;
		}
	}
}
```

---

## 作者：ZZQF5677 (赞：0)

### 解题思路

题目告诉我们可以将一个号码拆分出长度至少 $\geq 2$ 的段，我们先预处理出所有长度为 $2$ 的号码段和所有长度为 $3$ 的号码段，因为所有符合条件的号码段都只可能由这两种组合出来。因为如果这个段的长度为 $x$，那么 $x$ 可以拆分成 $x=(\lfloor  \dfrac{x}{2} \rfloor -1)\times 2+(2+x \bmod 2)$。我们用 `map<string,struct st>` 保存每个号码段的信息，这样方便我们使用。

比如样例：

```
4 3
251
064
859
957
054

```

我们先预处理出：

```
25 51 251
06 64 064
85 59 859
95 57 957

```

然后 $dp$ 判断 `054` 应该是怎么组合而来，$dp_i$ 表示前 $i$ 个字符已经匹配成功。那么  $dp_i$ 只可能转移到 $dp_{i+2}$ 或者转移到 $dp_{i+3}$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, dp[1005] /*某个状态的长度*/;
char s[1005][1005], a[1005];
struct Node {
  int l, r, id;
} ct[1005];
unordered_map<string, Node> mp;  //无序map
unordered_map<string, bool> flag;
vector<Node> ans;
int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0', ch = getchar();
  }
  return x * f;
}
int main() {
  t = read();
  while (t--) {
    n = read();
    m = read();
    memset(dp, 0, sizeof(dp));
    mp.clear();
    flag.clear();
    ans.clear();
    for (int i = 1; i <= n; i++) {
      scanf("%s", s[i] + 1);
    }
    scanf("%s", a + 1);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        string str = "";
        str += s[i][j];
        if (j + 1 <= m) {  //拆分成长度为2的。
          str += s[i][j + 1];
          mp[str] = {j, j + 1, i};
          flag[str] = 1;
        }
        if (j + 2 <= m) {  //拆分成长度为3的。
          str += s[i][j + 2];
          mp[str] = {j, j + 2, i};
          flag[str] = 1;
        }
      }
    }
    for (int i = 1; i <= m; i++) {  // dp[i]尝试转移dp[i+2]或者dp[i+3]。
      string str = "";
      str += a[i];
      if (i + 1 <= m) {  //转移dp[i+2]
        str += a[i + 1];
        if (flag[str] && dp[i - 1] == i - 1) {
          dp[i + 1] = dp[i - 1] + 2;
          ct[i + 1] = mp[str];
        }
      }
      if (i + 2 <= m) {  //转移dp[i+3]
        str += a[i + 2];
        if (flag[str] && dp[i - 1] == i - 1) {
          dp[i + 2] = dp[i - 1] + 3;
          ct[i + 2] = mp[str];
        }
      }
    }
    if (dp[m] != m) {  //长度不达到。
      puts("-1");
    } else {
      for (int i = m; i > 0;) {
        ans.push_back(ct[i]);
        i -= (ct[i].r - ct[i].l + 1);
      }
      printf("%d\n", ans.size());
      for (int i = ans.size() - 1; i >= 0; i--) {
        printf("%d %d %d\n", ans[i].l, ans[i].r, ans[i].id);
      }
    }
  }
  return 0;
}//
```

---

