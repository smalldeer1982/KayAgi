# 【MX-X12-T5】「ALFR Round 5」Another string problem

## 题目背景

原题链接：<https://oier.team/problems/X12E>。

---

决（け）して逃（に）げない怖（こわ）くはないから

目（め）を开（あ）け弱（よわ）さをかき消（け）すんだ

## 题目描述

我们定义 $S\mid T$ 为：设 $k=\lfloor |T|/|S| \rfloor$，则 $k$ 个 $S$ 连起来在 $T$ 中以子序列出现过。例如 $S=\textsf{ab},T=\textsf{abcab}$，则 $S\mid T$，$T$ 中出现的 $S$ 有 $\underline{\textsf{ab}}\textsf c{\underline{\textsf{ab}}}$。

对于 $t$ 组测试数据，给定一个 $S$ 和正整数 $q$，$q$ 次询问：

- 给定 $T_i$，问是否 $T_i\mid S$。如果 $T_i\mid S$，输出 `Yes`，否则输出 `No`。

## 说明/提示

**【样例解释】**

第一组测试数据中，$T=\textsf{abc}$ 时可以在 $S$ 种寻找到 $\textsf{abcabc}$ 作为子序列，具体的，$S$ 种出现的 $T$ 有 $\underline{\textsf{abc}}\textsf a{\underline{\textsf{abc}}}$。而 $T=\textsf{ab}$ 时 $\textsf{ababab}$ 不是 $S$ 的子序列。

第二组测试数据中，第一、三个询问分别有 $\underline{\textsf{ab}}\textsf a{\underline{\textsf{abab}}}$、$\underline{\textsf{aba}} {\underline{\textsf{aba}}}\textsf b$。

**【数据范围】**

**本题使用捆绑测试。**

对于 $100\%$ 的数据，$1 \le t \le 2\times 10^5$，$\lvert S\rvert,q,\lvert T_i\rvert\ge 1$，$\sum \lvert S\rvert\le 2\times 10^5$，$\sum q\le 2\times 10^5$，$\sum \sum \lvert T_i\rvert\le 4\times 10^5$，并且 $|T_i|\le |S|$。$S,T_i$ 均由小写英文字符（`a` 到 `z`）组成。

| 子任务 | $\sum \lvert S\rvert\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $2\times 10^5$ | $\lvert S\rvert\le 10$ | $3$ |
| $2$ | $3\times 10^3$ | 无 | $17$ |
| $3$ | $2\times 10^5$ | 数据随机$^†$ | $2$ | 
| $4$ | $2\times 10^5$ | $S$ 中不同字符最多 $1$ 种 | $8$ |
| $5$ | $2\times 10^5$ | $S$ 中不同字符最多 $2$ 种 | $15$ |
| $6$ | $10^5$ | 无 | $20$ |
| $7$ | $2\times 10^5$ | 无 | $35$ |

$†$：并非完全均匀随机字符，具体见【**子任务 3 数据随机方式**】。

**【子任务 3 数据随机方式】**

下面是造“数据随机”的部分分的代码（因为 `generator` 较长，这里是所有有关片段）：

```cpp
mt19937 rng((unsigned long long) new char);

int rnd_l(int l,int r){
	return rng()%(r-l+1)+l;
}

char rnd(vector<int> v){ // 0~25 权重 
	int sum=0;
	for (auto u : v) sum+=u;
	int r=rng()%(sum)+1,c=0;
	sum=0;
	for (auto u : v){
		if (sum+u>=r) return c+'a';
		c++;
		sum+=u;
	}
}

vector<int> pl;

void rnd_g(){
	string s=rnd_s(pl,n);
	cout<<s<<" "<<q<<endl;
	string t=rnd_s(pl,n);
	vector<int> ct=rnd_v(n,q);
	ct.push_back(n);
	for (int i=1,pr=0; i<=q; i++){
		cout<<t.substr(pr,ct[i-1]-pr)<<endl;
		pr=ct[i-1];
	}
}

vector<int> rnd_v(int fw,int ti){ // 不可重复的划分 
	vector<int> ct;
	ct.push_back(0);
	for (int i=1,cr=0; i<ti; i++){
		ct.push_back(rnd_l(cr+1,fw-(ti-i)));
		cr=ct.back();
	}
	return ct;
}

for (int i=0; i<26; i++) pl.push_back(rnd_l(5,15));
```

需要注意的是，`rnd` 函数并非均匀随机，是按照随机生成的权重 `pl` 随机 $a\sim z$ 的（即 $c$ 的概率为 $\frac{pl_c}{\sum pl_i}$）。`pl` 每一个数据点都会重新生成。

这个代码中，$n=|S|,q$ 是数据范围内给定的数。随机的方式如下：

- $q\in [1,n]$，均匀随机。

- 按照 `rnd` 函数随机生成一个 $S$ 字符串和 $T$ 字符串，长度均为 $n$。

- 按照 `rnd_v` 函数随机一个 $T$ 的分割，一共 $q-1$ 个分割点，分成 $q$ 段，分别为 $T_1\sim T_q$。

## 样例 #1

### 输入

```
2
abcaabc 2
abc
ab
abaabab 3
ab
aa
aba
```

### 输出

```
Yes
No
Yes
No
Yes```

# 题解

## 作者：wmrqwq (赞：5)

验题人题解。

# 题目链接

[「ALFR Round 5」E Another string problem](https://www.luogu.com.cn/problem/P12422)

# 解题思路

考虑倍增。

注意到失配的次数显然不能大于 $|T| - 1$ 次，否则一定不合法。

那么也就意味着一个 $T$ 是合法的，当且仅当在 $S$ 中最多只会有 $|T| - 1$ 个断点。

暴力做法显然直接扫一遍原串暴力匹配过去即可。

我们考虑优化这个匹配的过程，若此时 $T$ 匹配到了 $L$ 这个位置，我们进行分讨：

- 若 $L$ 为 $T$ 的第一个位置，则我们可以直接倍增跳 $T$，特别的，若一个 $T$ 都跳不了，则直接改为倍增跳 $T$ 的字符，特别的，若一个字符都没有，则失配次数 $+ 1$。

- 若 $L$ 不为 $T$ 的第一个位置，则我们可以直接倍增跳 $T$ 的字符，特别的，若一个字符都没有，则失配次数 $+ 1$。

显然每个位置最多只有一个倍增 $\log |T| + \log |S|$ 的复杂度，总时间复杂度 $O(\sum |S| \log |T| + |S| \log |S|)$。

# 参考代码

```cpp
string s,s2;
ll n,m,q;
ll hsh[200010][20];
ll nxt[20];
ll hashing[200010];
ll Pw[200010];
ll Base[]={131,223,233,666,10011},Mod[]={998244353,998244853,(ll)1e9+7,(ll)1e9+9};
ll base,mod;
ll B;
ll f(ll l,ll r){
    return (hashing[r]-hashing[l-1]*Pw[r-l+1]%mod+mod)%mod;
}
map<string,ll>mp;
void _clear(){}
void solve()
{
    mp.clear();
    base=Base[rand_lr(0,4)],mod=Mod[rand_lr(0,3)];
    Pw[0]=1;
    _clear();
    cin>>s>>q;
    n=s.size();
    B=1e18;
    s=' '+s;
    forl(i,1,n)
        Pw[i]=Pw[i-1]*base%mod;
    forl(i,1,n)
        hashing[i]=(hashing[i-1]*base+s[i])%mod;
    forl(i,1,q)
    {
        cin>>s2;
        m=s2.size();
        s2=' '+s2;
        if(mp[s2])
        {
            printat(mp[s2]==1);
            continue;
        }
        if(m>n)
        {
            aty;
            continue;
        }
        if(m>B)
        {
            ll sum=0,L=0;
            forl(j,1,n)
            {
                if(s2[L+1]==s[j])
                    L++;
                if(L==m)
                    L=0,
                    sum++;
            }
            printat(sum>=n/m);
            continue;
        }
        forl(i,1,m)
            hsh[i][0]=s2[i];
        forl(j,1,17)
            forl(i,1,m-pw(j)+1)
                hsh[i][j]=(hsh[i][j-1]*Pw[pw(j-1)]+hsh[i+pw(j-1)][j-1])%mod;
        ll num=0;
        forl(i,1,m)
            num=(num*base+s2[i])%mod;
        nxt[0]=num;
        forl(i,1,19)
            nxt[i]=(nxt[i-1]*Pw[min(pw(i-1)*m,200005ll)]%mod+nxt[i-1])%mod;

        ll sum=0,L=0,last=n%m;
        forl(i,1,n)
        {
            // cout<<i<<endl;
            if(last<0)
                break;
            if(L==0)
            {
                if(i+m-1>n)
                    break;
                if(f(i,i+m-1)!=nxt[0])
                {
                    if(s[i]!=s2[1])
                    {
                        last--;
                        continue;
                    }
                    forr(j,__lg(m),0)
                        if(L+1+pw(j)-1<=m && i+pw(j)-1<=n && hsh[L+1][j]==f(i,i+pw(j)-1))
                            i+=pw(j),
                            L+=pw(j),
                            sum+=L/m,
                            L%=m;
                    i--;
                    continue;
                }
                else
                {
                    forr(j,19,0)
                        if(i+pw(j)*m-1<=n && f(i,i+pw(j)*m-1)==nxt[j])
                            i+=pw(j)*m,
                            sum+=pw(j);
                    i--;
                    continue;
                }
            }
            else
            {
                if(s[i]!=s2[L+1])
                {
                    last--;
                    continue;
                }
                forr(j,__lg(m),0)
                    if(L+pw(j)-1<=m && i+pw(j)-1<=n && hsh[L+1][j]==f(i,i+pw(j)-1))
                        i+=pw(j),
                        L+=pw(j),
                        sum+=L/m,
                        L%=m;
                i--;
            }
        }
        // cout<<endl;
        // cout<<last<<' '<<sum<<endl;
        mp[s2]=(last>=0 && sum>=n/m)?1:-1;
        printat(last>=0 && sum>=n/m);
    }
}
```

---

## 作者：qqqaaazzz_qwq (赞：3)

~~算是半个乱搞做法~~

若长度为 $k$ 的串 $T$ 是合法的，则我们可以将 $S$ 看作 $\lfloor \dfrac{|S|}{k} \rfloor$ 个 $T$ 连在一起，再插入 $|S| \bmod k$ 个其它字符。根据鸽巢原理，至少有 $\lfloor \dfrac{|S|}{k} \rfloor-(|S| \bmod k)$ 个完整的 $T$ 在 $S$ 里面出现了。对于每个 $T$ 我们先判断这个条件是否满足，若满足就 $\Theta(n)$ 暴力扫一遍，再加上记忆化，就能够通过本题。

此程序计算理论最高时间复杂度：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXLEN = 400000;

signed main()
{
	int ans = 0,id = 0;
	for (int MAXN=1;MAXN<=200000;MAXN++){
		int cur = 0,sum = 0;
		for (int i=1;i<=MAXN;i++){
			int lest = MAXN/i-MAXN%i;
			int all = MAXN-i+1;
			if(lest<=0){
				while(sum+i<=MAXLEN){
					++cur;
					sum += i;
				}
				break;
			}
			else{
				for (int j=1;j<=all/lest;j++){
					if(sum+i<=MAXLEN){
						++cur;
						sum += i;
					}
					else{
						i = MAXN+1;
						break;
					}
				}
			}
		}
		if(cur*MAXN>ans){
			ans = cur*MAXN;
			id = MAXN;
		}
	}
	cout << id << " " << ans << "\n";
	return 0;
}
```

输出结果是：`199987 1130926485`

但是稍加思考就知道肯定跑不满，故此方法是正确的。

My Code：

```cpp
#include <bits/stdc++.h>
#define int long long
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int n,q;
char s[200010];
int lest[200010];

//暴力计算答案
bool judge(string k){
	int cnt = 0;
	int u = k.length();
	for (int i=1;i<=n;i++){
		if(s[i]==k[cnt%u]) ++cnt;
	}
	if(cnt>=n/u*u) return true;
	return false;
}
//这是一个 SAM 模板，用于计算子串出现次数
struct Node{
	int len,link,val;
	map<int,int> nxt;
};
Node st[2000010];
vector<int> v[2000010];
int sz,lst;
void init(){
	sz = 0;
	st[0].len = 0;
	st[0].link = -1;
	st[0].nxt.clear();
	st[0].val = 0;
	++sz;
	lst = 0;
	return;
}
void sam_add(char x){
	int cur = sz++;
	st[cur].len = st[lst].len+1;
	st[cur].val = 1;
	st[cur].nxt.clear();
	int p = lst;
	while(p!=-1&&st[p].nxt[x-'a']==0){
		st[p].nxt[x-'a'] = cur;
		p = st[p].link;
	}
	if(p==-1){
		st[cur].link = 0;
	}
	else{
		int q = st[p].nxt[x-'a'];
		if(st[p].len+1==st[q].len){
			st[cur].link = q;
		}
		else{
			int clone = sz++;
			st[clone] = st[q];
			st[clone].len = st[p].len+1;
			st[clone].val = 0;
			while(p!=-1&&st[p].nxt[x-'a']==q){
				st[p].nxt[x-'a'] = clone;
				p = st[p].link;
			}
			st[q].link = st[cur].link = clone;
		}
	}
	lst = cur;
	return;
}
void dfs(int d){
	for (auto i : v[d]){
		dfs(i);
		st[d].val += st[i].val;
	}
	return;
}
//SAM模板至此结束

map<int,bool> mp;
const int mod = 1e17+13;

void solve(){
	mp.clear();
	cin >> s+1;
	n = strlen(s+1);
	init();
	for (int i=1;i<=n;i++) sam_add(s[i]);
	for (int i=0;i<=sz;i++) v[i].clear();
	for (int i=0;i<=sz;i++){
		if(st[i].link!=-1) v[st[i].link].push_back(i);
	}
	dfs(0);
    st[0].val = 0;
	//预处理 SAM
	int sum = 0;
	for (int i=1;i<=n;i++){
		lest[i] = max(0ll,n/i-n%i);//长度为 i 的串至少出现了 lest[i] 次才有可能成为答案 
	}
	cin >> q;
	while(q--){
		string k;
		cin >> k;
		int hh = 0;
		for (auto i : k) hh = (hh*29+i-'a'+1)%mod;
		if(mp.find(hh)!=mp.end()){
			if(mp[hh]) cout << "Yes\n";
			else cout << "No\n";
			continue;
		}
		int now = 0;
		for (auto qwq : k){
			if(st[now].nxt[qwq-'a']!=0){
				now = st[now].nxt[qwq-'a'];
			}
			else{
				now = 0;
				break;
			}
		}
		if(st[now].val>=lest[k.length()]&&judge(k)){
			mp[hh] = 1;
			cout << "Yes\n";
		}
		else{
			mp[hh] = 0;
			cout << "No\n";
		}
	}
}

signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

赛时降智不会 $O(n\log n)$，所以用 $O(n\sqrt{n\log n})$ 冲了过去。

先想到从失配位置的角度考虑，考虑二分出下一个失配位置，使用 Hash 判相等。

但这样有一个问题，若 chk 的长度大于 $|T|$，直接维护 $T$ 的哈希值就寄了，若延长长度（复制若干遍）则会退化为 $O(q|S|)$。

这里提供一些解决方法：

1. 使用倍增的方法维护哈希值，直接做是 $2$ 个 $\log$ 的，把二分去掉就是 $1$ 个 $\log$。（官方题解）

2. 发现这时的字符串包含很多连续的 $T$ 作为子串，可以发现这一部分的贡献形如 $\sum\limits_{i}base^{ik+b}\mathrm{Hash}(T)$（$\mathrm{Hash}(T)$ 表示 $T$ 的哈希值），使用等比数列求和公式可以 $O(1)$ 算出 $\mathrm{Hash}(T)$ 的系数，再把剩余部分（一段后缀和一段前缀）拼上就行，复杂度 $1$ 个 $\log$。

3. 如果不延长长度，二分只判断 $[now,now+|T|]$ 也可以做，单次询问复杂度 $O(|T|+\dfrac{|S|}{|T|}\log |S|)$，能获得 $65$ 分，考虑“部分延长”字符串 $|T|$（即不断往后面加原始的 $|T|$）直到长度大于 $B$，这样单次询问就是 $O(\max(|T|,B)+\dfrac{|S|}{\max(|T|,B)}\log|S|)$ 的，可以把总复杂度分析到 $O(\sum|T|+qB+\dfrac{q|S|}{B}\log|S|+|S|)$ 的，取 $B=\sqrt{|S|\log|S|}$ 最优，为 $O(\sum|T|+q\sqrt{|S|\log|S|}+|S|)$，但实际上 $B$ 取小一些可能更快。（赛时做法）

赛时代码：


```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define ull unsigned long long
#define uint unsigned int
#define bi __int128_t
#define lb(x) ((x)&(-(x)))
#define gp(i,j) (((i)>>(j-1))&1)
#define ppc __builtin_popcount
#define ushort unsigned short
#define db long double
using namespace std;
const int N=1e6+10,mod=998244353,mod2=1e9+7,B=150;
const int base=131;
const ll inf=1e18+10;
void Add(int &a,int b){a+=b;if(a>=mod) a-=mod;}
void Sub(int &a,int b){a-=b;if(a<0) a+=mod;}
void Mul(int &a,int b){a=1ll*a*b%mod;}
int n,m,q;
string s,t;
int bs[N],h1[N],h2[N];
int c1(int l,int r){
    return (h1[r]-1ll*h1[l-1]*bs[r-l+1]%mod+mod)%mod;
}
int c2(int l,int r){
    //cout<<l<<' '<<r<<endl;
    if(l>r) r+=m;
    return (h2[r]-1ll*h2[l-1]*bs[r-l+1]%mod+mod)%mod;
}
void slv(){
    cin>>s>>q;
    n=s.length()+1;s=' '+s+'@';
    bs[0]=1;
    for(int i=1;i<=n;i++) bs[i]=1ll*bs[i-1]*base%mod;
    h1[0]=1;
    for(int i=1;i<=n;i++){
        h1[i]=(1ll*base*h1[i-1]+s[i])%mod;
    }
    while(q--){
        int rea=0;
        cin>>t;string tmp=t;
        int ned=(n-1)%(t.length());
        rea=t.length();
        m=t.length();
        t=t+t;
        while(m<=B&&m*2<=n) m*=2,t+=t;
        t=' '+t;
        h2[0]=1;
        for(int i=1;i<=m*2;i++){
            h2[i]=(1ll*base*h2[i-1]+t[i])%mod;
        }
        int cnt=0,len=1,pos=1;
        while(cnt<=rea&&pos<=n){
            int l=pos,r=min(n,pos+m-1);
            if(c1(pos,r)==c2((len-1)%m+1,(len+r-pos-1)%m+1)){
                len+=(r-pos+1);pos=r+1;continue;
            }//cout<<1<<' ';
            while(l<r){
                int mid=(l+r)/2;
                if(c1(pos,mid)==
                c2((len-1)%m+1,(len+mid-pos-1)%m+1)){
                    l=mid+1;
                }else{
                    r=mid;
                }
            }
            //cout<<"!"<<pos<<' '<<l<<' '<<len-1<<' '<<len+l-pos-1<<endl;
            if(c1(pos,l)==c2((len-1)%m+1,(len+l-pos-1)%m+1)){
                    len+=(l-pos+1);pos=l+1;continue;
            }
            cnt++;
            len+=(l-pos);pos=l+1;
            //cout<<pos<<' '<<len<<' '<<n<<' '<<l<<endl;
        }cnt--;
        //cout<<cnt<<endl;
        if(cnt<=ned){
            cout<<"Yes"<<'\n';
        }else{
            cout<<"No"<<'\n';
        }
    }
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t=1;cin>>t;
    while(t--) slv();
    cerr<<clock()*1.0/CLOCKS_PER_SEC<<endl;
    return 0;
}
```

---

