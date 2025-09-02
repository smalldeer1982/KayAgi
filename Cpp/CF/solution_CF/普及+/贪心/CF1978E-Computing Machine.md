# Computing Machine

## 题目描述

给定长度为 $n$ 的二进制字符串 $s,t$，串内只包含 $0$ 和 $1$，现有 $q$ 次询问，每次给出一个区间 $[l,r]$，分别记 $s,t$ 在 $[l,r]$ 上的子串为 $a,b$，进行任意次如下两种操作：
 - 若 $\exist i,i+2\in[l,r]$ 使得 $a_i=a_{i+2}=0$，则可以使 $b_{i+1}$ 的值变为 $1$。
 - 若 $\exist i,i+2\in[l,r]$ 使得 $b_i=b_{i+2}=1$，则可以使 $a_{i+1}$ 的值变为 $1$。

现求所有操作结束后，串 $a$ 内最多可以包含多少 $1$。

## 样例 #1

### 输入

```
3
4
1111
0000
2
1 2
2 4
4
1010
1101
2
1 3
1 4
6
010101
011010
5
2 3
1 6
2 5
4 4
3 6```

### 输出

```
2
3
2
3
1
4
3
1
2```

# 题解

## 作者：NATO (赞：8)

赛时笔者的消愁解法。

### 思路浅析：

先考虑最优操作方式。

注意到先执行完所有能执行的操作 $1$ 后再执行操作 $2$ 必然是最优的。很好证，就是你如果先执行了操作 $2$，那么原来可执行的操作 $1$ 的数量必然不会增加（因为你是增加了 $s$ 中 $1$ 的数量，而操作 $1$ 需要的是 $s$ 中的 $0$，所以这么搞必然不会新增加可执行的操作 $1$ 的数量。同时也说明“执行操作不会导致新的可执行操作”这一性质）。而执行完所有操作 $1$ 能够尽可能地增加 $t$ 中 $1$ 的数量，从而最大化操作 $2$ 的数量，从而最大化执行完操作 $2$ 后 $s$ 中 $1$ 的数量。

那么我们有了最优操作方式并且知道“执行操作不会导致新的可执行操作”这一性质之后能干什么呢？

考虑由于上述性质，我加入一个位置的影响就是 $O(1)$ 级别的：

1. $s_i=0$ 时，若 $s_{i-2}$ 或 $s_{i+2}$ 在区间内，值为 $0$，且 $t_{i-1}$ 或 $t_{i+1}$ 值为 $0$，那么 $s_i$ 使其发生了变化，变为 $1$，且之后由于 $t_{i-1},t_{i+1}$ 必然为 $1$，$s_i$ 亦可变为 $1$。
2. 在第一步的基础上，若 $t_{i-3}$ 或 $t_{i+3}$ 为 $1$，那么对应地，$s_{i-2}$ 或 $s_{i+2}$ 变为 $1$。
3. 若 $t_i=1$，且 $t_{i-2}$ 或 $t_{i+2}$ 为 $1$，对应 $s_{i-1}$ 或 $s_{i+1}$ 变为 $1$。

删除一个位置同理。

于是我们需要一个支持快速扩充（减小）区间的数据结构，我们会想到什么？莫队啊！

用普通莫队维护上述过程即可。

时间复杂度高贵的 $O(n\sqrt n)$，相比于 $O(n)$ 遥遥落后。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T;
string s,t;
ll q;
ll ans[200005],ss,from[200005];
ll l,r,res=0;
ll ns[200005],nt[200005];
struct px
{
	ll l,r,uid;
	bool operator<(const px&b)const
	{
		return ((from[l]^from[b.l])?l<b.l:(from[l]&1)?r<b.r:r>b.r);
	}
}ask[200005];
void check(ll where)
{
	if(nt[where])
	{
		if(where+2<=r&&nt[where+2])
			if(s[where+1]=='0')++res,ns[where+1]=1;
		if(where-2>=l&&nt[where-2]&&where-2)
			if(s[where-1]=='0')++res,ns[where-1]=1;
	}
	else
	{
		if(where+2<=r&&nt[where+2])
			if(s[where+1]=='0')--res,ns[where+1]=0;
		if(where-2>=l&&nt[where-2]&&where-2)
			if(s[where-1]=='0')--res,ns[where-1]=0;
	}
}
void add(ll where)
{
	if(!where)return;
	if(ns[where])++res;
	if(nt[where])check(where);
	if(where+2<=r)
	{
		if(s[where]=='0'&&s[where+2]=='0'&&t[where+1]=='0')nt[where+1]=1,check(where+1);
	}
	if(where-2>=l&&where-2)
	{
		if(s[where]=='0'&&s[where-2]=='0'&&t[where-1]=='0')nt[where-1]=1,check(where-1);
	}
}
void erase(ll where)
{
	if(!where)return;
	if(ns[where])--res;
	if(nt[where])
	{
		nt[where]=0;check(where);
		nt[where]=1;
	}
	ns[where]=s[where]-'0';
	if(where+2<=r)
	{
		if(s[where]=='0'&&s[where+2]=='0'&&t[where+1]=='0')nt[where+1]=0,check(where+1);
	}
	if(where-2>=l&&where-2)
	{
		if(s[where]=='0'&&s[where-2]=='0'&&t[where-1]=='0')nt[where-1]=0,check(where-1);
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		ll n;
		cin>>n;
		cin>>s>>t;
		l=1,r=0,res=0;
		s=' '+s;t=' '+t;ss=sqrt(n);
		for(ll i=1;i<=n;++i)from[i]=(i-1)/ss+1,ns[i]=s[i]-'0',nt[i]=t[i]-'0';
		cin>>q;
		for(ll i=1;i<=q;++i)cin>>ask[i].l>>ask[i].r,ask[i].uid=i;
		sort(ask+1,ask+1+q);
		for(ll i=1;i<=q;++i)
		{
			while(r<ask[i].r)add(++r);
			while(l>ask[i].l)add(--l);
			while(r>ask[i].r)erase(r--);
			while(l<ask[i].l)erase(l++);
			ans[ask[i].uid]=res;
		}
		for(ll i=1;i<=q;++i)cout<<ans[i]<<'\n';
	}
}
```

---

## 作者：GGapa (赞：7)

考虑每次操作都最大化，则最多只需要两次操作就可以使得数组 $a$ 中的 $1$ 最大化。

接着手玩一下样例可以发现这个 $0$ 和 $1$ 并没有传递性，对于每一次询问就只需要特殊判断一下边界的 $1$ 是不是由 $0$ 转变而来即可。

实现：

- 首先预处理出全局的 $1$ 的最大化序列。

- 对于每次询问，对边缘的 $1$ 进行判断，若被截断则答案 $-1$ 即可。

注意：若区间的长度是小于等于 $3$ 的需要特判，不然可能会重。

```cpp
//君本凌云客，何故喜蓬蒿？
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
typedef long long ll;
using VI = vector<int>;

void solve() {
    int n; cin >> n;
    string a, b; cin >> a >> b;
    a = " " + a, b = " " + b;
    auto c = a, d = b;
    for(int i = 1; i + 2 <= n; i++) if(a[i] == a[i + 2] && a[i] == '0') d[i + 1] = '1';
    for(int i = 1; i + 2 <= n; i++) if(d[i] == d[i + 2] && d[i] == '1') c[i + 1] = '1'; 
    vector<int> S(n + 1);
    rep(i, 1, n) S[i] = S[i - 1] + (c[i] == '1');
    int q; cin >> q;
    int ret = 0;
    auto chk = [&](int i, int j) {
        if(c[i] == '1' && a[i] == '0') ret--;
        if((i < n || j < 0) && (i > 1 || j > 0)) 
            if(c[i - j] == '1' && a[i - j] == '0' && b[i] == '0') ret--;
    };
    for(int o = 1, l, r; o <= q; o++) {
        cin >> l >> r;
        if(r - l + 1 <= 3) {
            ret = 0;
            ret += (a[l] == '1');
            if(l != r) ret += (a[r] == '1');
            if(r - l + 1 == 3) ret += ((c[l + 1] == '1' && b[r] == '1' && b[l] == '1') || a[l + 1] == '1');
            cout << ret << '\n';
            continue;
        }
        ret = S[r] - S[l - 1];
        chk(r, 1); chk(l, -1); 
        cout << ret << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：hard_plan (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF1978E)

# 题意
有两个序列 $ a $，$ b $，对于每一次查询给出 $ l $ 和 $ r $，对于 $ l\le i\le r-2 $ 在原序列中可以进行以下操作任意次：

1. 若 $ a_i=0 $ 且 $ a_{i+2}=0 $，则可以将 $ b_{i+1} $ 赋值为 $ 1 $。

2. 若 $ b_i=1 $ 且 $ b_{i+2}=1 $，则可以将 $ a_{i+1} $ 赋值为 $ 1 $。

对于每一次查询，请求出操作结束后对于 $ l\le i\le r $， $a_i=1 $的 $ i $的个数的最大值。

# 思路

读完题后发现这道题有几个特点：

- 序列区间查询

- 不带修改

-  $ n\le 2\times 10^5 $

- 不强制在线

那么，就可以用莫队做。

考虑如何 $ O(1) $ 移动左右端指针。

那么我们如何让 $ a_i $ 从 $ 0 $ 变为 $ 1 $ 呢？那必有 $ b_{i-1} $ 和 $ b_{i+1} $ 在经操作后一定为 $ 1 $。对于 $ b_{i-1} $，要么是它本来就是 $ 1 $，要么是 $ a_{i-2} $ 为 $ 0 $，把 $ b_{i-1} $ 变为 $ 1 $。 $ b_{i+1} $ 同理。

那这个 $ a_i $ 贡献会在什么时候合法呢？

如果去找它的合法的最左端和最右端，也就是当 $ l\le  $ 最左端且 $ r\ge  $ 最右端时， $ a_i $ 会对答案有贡献。

而当 $ b_{i-1} $ 是 $ 1 $ 时，该贡献的最左端为 $ i-1 $，否则为 $ i-2 $。

同理，当 $ b_{i+1} $ 是 $ 1 $ 时，该贡献的最右端为 $ i+1 $，否则为 $ i+2 $。

所以在伸缩区间时判断一下最左端和最右端是否在区间内就行了。

还有就是在伸缩区间时别忘了加上原来 $ a_i $ 就为 $ 1 $ 的答案贡献。

理论时间复杂度 $ O(n\sqrt{n}) $，只不过带了亿点常数，$ 2 $ 秒跑过没什么问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,D=505;
int n,t,d[N],l,r,idx,Q,c[N],ans[N],now;
bool a[N],b[N];
struct que{int l,r,idx;}q[N];
int read()//快读 
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void init()//分块 
{
	int len=sqrt(n);
	idx=1;
	for(int i=1;i<=n;i++)
	{
		d[i]=idx;
		if(i%len==0) idx++;
	}
}
bool cmp(que aa,que bb)//莫队排序 
{
	if(d[aa.l]!=d[bb.l])return aa.l<bb.l;
	if((d[aa.l]&1)) return aa.r<bb.r;
	return aa.r>bb.r;
}
int checkl(int pos)//找最左端或判无解 
{
	if(a[pos-2]) return 0;
	if(!b[pos-1]&&(pos<l||pos>r||a[pos])) return 0;
	if(!b[pos-3]&&(pos-4<l||pos-4>r||a[pos-4])) return 0;
	if(b[pos-3]) return pos-3;
	else return pos-4;
}
int checkr(int pos)//找最右端或判无解 
{
	if(a[pos-2]) return 0;//不会有贡献，因为原来就是1 
	if(!b[pos-1]&&(pos<l||pos>r||a[pos])) return 0;
	if(!b[pos-3]&&(pos-4<l||pos-4>r||a[pos-4])) return 0;
	if(b[pos-1]) return pos-1;
	return pos;
}
void radd(int pos) 
{
	if(a[pos]) now++;
	if(pos-3>=l&&checkr(pos)==pos) now++;//可能会更新a[i-2]或a[i-1]的贡献 
	if(pos-2>=l&&checkr(pos+1)==pos)now++;
}	
void rdel(int pos)
{
	if(pos-2>=l&&checkr(pos+1)==pos)now--;
	if(pos-3>=l&&checkr(pos)==pos)now--;
	if(a[pos]) now--;
}
void ladd(int pos)
{
	if(a[pos]) now++;
	if(pos+3<=r&&checkl(pos+4)==pos) now++;
	if(pos+2<=r&&checkl(pos+3)==pos) now++;
}
void ldel(int pos)
{
	if(pos+2<=r&&checkl(pos+3)==pos)now--;
	if(pos+3<=r&&checkl(pos+4)==pos)now--;
	if(a[pos]) now--;
}
int main()
{
	t=read();
	while(t--)
	{
		memset(c,0,sizeof(c));//初始化 
		n=read();
		for(int i=1;i<=n;i++)
		{
			char w;
			cin>>w;
			a[i]=w-'0';
		}
		for(int i=1;i<=n;i++)
		{
			char w;
			cin>>w;
			b[i]=w-'0';
		}
		init();
		Q=read();
		for(int i=1;i<=Q;i++) q[i].l=read(),q[i].r=read(),q[i].idx=i;
		sort(q+1,q+Q+1,cmp);//离线排序 
		l=1,r=0,now=0;
		for(int i=1;i<=Q;i++)
		{
			int ql=q[i].l,qr=q[i].r;
			while(r<qr) r++,radd(r);
			while(r>qr) rdel(r),r--;
			while(l<ql) ldel(l),l++;
			while(l>ql) l--,ladd(l);//最好把--l从括号里脱离出来，避免一些奇怪的错误 
			ans[q[i].idx]=now;
		}
		for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：4)

$E\lt D$。

## 解题思路

注意到执行操作 $1$ 直到不能执行，然后执行操作 $2$ 直到不能执行一定能使 $a$ 中的 $1$ 个数最多。

我们模拟出以上操作，然后用前缀和维护其区间和。

但是每一次询问返回区间和是不可取的：究其原因是因为每一次询问会规定询问区间的边界，靠近边界上的数可能会因此与模拟出的值不同。

那么分类讨论即可：

- 若询问的区间长度 $\leq 20$，那么暴力计算。

- 否则，独立计算靠左边界的 $5$ 个数操作后的值，独立计算靠右边界的 $5$ 个数操作后的值，前缀和算出其余值的和，相加即可。

时间复杂度 $O(20q)$。

---

## 作者：fengxiaoyi (赞：3)

### 特殊情况

首先考虑当 $l=1,r=n$ 时怎么做。

一个最优的操作方案是：

先对 $a$ 进行操作 $1$，使 $b$ 拥有尽可能多的 `1`，再对 $b$ 进行操作 $2$，这样 $a$ 中的 `1` 数量就是最多的了。

### 一般情况

记 $f_{i,j}$ 表示进行上述操作方案后 $a$ 的区间 $[i,j]$ 中的 `1` 的个数，$g_{i,j}$ 表示区间 $[i,j]$ 的答案。

显然 $f_{1,n}=g_{1,n}$ 。

而当 $r-l+1\lt n$ 时（既有 $l\not=1$ 或 $r\not=n$），$g_{l,r}$ 不一定等于 $f_{l,r}$。

------------

记 $c_{i,0}$ 表示 $a$ 中的第 $i$ 位是否是由 $0$ 变为 $1$ 的，$c_{i,1}$ 表示 $b$ 中的第 $i$ 位是否是由 $0$ 变为 $1$ 的。

不难想到当 $c_{l,0}=1$ 或 $c_{r,1}=1$ 时，$g_{l,r}$ 都会减少一。

还有当 $c_{l+1,0}\lor c_{l,1}=1$ 或 $c_{r-1,0}\lor c_{r,1}=1$ 时，$g_{l,r}$ 也都会减少一。

所以判断这几种情况，就能算出 $g_{l,r}$。

**注意一些细节**，具体见代码。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,a[200010];
bool f[200010][2];//这里的 f 即上文中的 c
char s[200010],t[200010];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		scanf("%s",s+1);
		scanf("%s",t+1);
		for(int i=0;i<=n+1;i++) f[i][0]=f[i][1]=0;
		for(int i=2;i<n;i++){
			if(s[i-1]==s[i+1]&&s[i-1]=='0'){
				f[i][1]=(t[i]=='0');
				t[i]='1';
			}
		}
		for(int i=2;i<n;i++){
			if(t[i-1]==t[i+1]&&t[i-1]=='1'){
				f[i][0]=(s[i]=='0');
				s[i]='1';
			}
		}
		for(int i=1;i<=n;i++) a[i]=a[i-1]+(s[i]=='1');
		scanf("%d",&q);
		while(q--){
			int l,r;
			scanf("%d%d",&l,&r);
			int ans=a[r]-a[l-1];
			if(l==r){ //细节 1
				if(f[l][0]) ans--;
				printf("%d\n",ans);
				continue;
			}
			ans-=f[l][0]+f[r][0];
			if(r-l+1==2){//细节 2
				printf("%d\n",ans);
				continue;
			}
			if(l+1==r-1) ans-=(f[l+1][0]&f[l][1])|(f[r-1][0]&f[r][1]);//细节 3
			else ans-=(f[l+1][0]&f[l][1])+(f[r-1][0]&f[r][1]);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：KSCD_ (赞：2)

## 题意
给定 $s,t$ 两个 $01$ 串，有以下两种操作：

- 若 $s_i=0$ 且 $s_{i+2}=0$，可将 $t_{i+1}$ 赋为 $1$。
- 若 $t_i=1$ 且 $t_{i+2}=1$，可将 $s_{i+1}$ 赋为 $1$。

求经过若干次操作后 $s$ 中 $1$ 的最大个数。
## 思路
考虑一个区间的最优操作方案，发现先用 $s$ 中的 $0$ 把 $t$ 中所有能变 $1$ 的变完，再把 $s$ 中所有能变 $1$ 的变完，这样一定是最优的，因为这样保证了第一步之后 $t$ 中的 $1$ 最多，从而最终 $s$ 中的 $1$ 也最多。

接着考虑每一位会怎样被改变。若 $s_i$ 被变为 $1$，需要 $t_{i-1}=1$ 且 $t_{i+1}=1$，$t$ 的这两位又会受到 $s_{i-2},s_i,s_{i+2}$ 的影响，所以对于每一位 $s_i$，都只会受到 $[i-2,i+2]$ 区间内的影响。

因此可以提前对整个区间进行操作，并对最终的 $s$ 求前缀和。询问长度不超过 $4$ 时直接暴力操作求解。超过 $4$ 时由于 $[l+2,r-2]$ 只受区间 $[l,r]$ 内的影响，答案不变，直接记录下原来的答案，再单独对 $[l,l+4]$ 操作并记录前两位的答案，对 $[r-4,r]$ 操作并记录后两位的答案，把三部分相加即可。
## 代码
```cpp
#include<iostream>
using namespace std;
const int N=2e5+10;
int n,q,pre[N],s[N],t[N],ts[N],tt[N];
char ss[N],st[N]; 
void solv(int l,int r)
{
	int len=r-l+1;
	for(int i=l;i<=r;i++) ts[i-l+1]=s[i],tt[i-l+1]=t[i];
	for(int i=1;i+2<=len;i++) if(!ts[i]&&!ts[i+2]) tt[i+1]=1;
	for(int i=1;i+2<=len;i++) if(tt[i]&&tt[i+2]) ts[i+1]=1;
	for(int i=1;i<=len;i++) ts[i]+=ts[i-1];
}
void sol()
{
	cin>>n>>ss>>st>>q;
	for(int i=1;i<=n;i++) s[i]=ss[i-1]-'0',t[i]=st[i-1]-'0';
	solv(1,n);
	for(int i=1;i<=n;i++) pre[i]=ts[i];
	while(q--)
	{
		int l,r; cin>>l>>r;
		if(r-l<4) solv(l,r),cout<<ts[r-l+1]<<'\n';
		else
		{
			int res=pre[r-2]-pre[l+1];
			solv(l,l+4),res+=ts[2];
			solv(r-4,r),res+=(ts[5]-ts[3]);
			cout<<res<<'\n';
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int T; cin>>T;
	while(T--) sol();
	return 0;
}
```

---

## 作者：wdl_ (赞：1)

菜鸟的挠餐暴力前缀和做法……

------------
对于这道题，显然有贪心策略：

先用 $s$ 中所有的 $0$ 使 $t$ 中的 $1$ 最大化，再用 $t$ 将 $s$ 中的 $1$ 最大化。

问题在于如何将 $1$ 的数量存入前缀和数组。

我们先将 $s$ 中本就存在的 $1$ 存入一个前缀和数组，然后就是后面新增加的 $1$ 的个数了。

我们将 $t$ 中的 $1$ 分为 $2$ 类：原本存在的 $1$、通过 $s$ 中 $0$ 变化得来的 $1$（我们简单将其称为 $a$ 和 $b$）。

我们不难发现共有下列 $4$ 种情况能使 $s$ 中 $1$ 的个数增加：

$$(a,a) (a,b) (b,a) (b,b)$$

然后就是打 if 判断是否出现这些情况，并用 $4$ 个前缀和数组记录了（注意判重）。

详情见代码。

对比 dalao 的简练做法还是太挠餐了……



------------
Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
int n,q,l,r;
int sum1[200005],sum2[200005],sum3[200005],sum4[200005],sum5[200005];
char s[200005],t[200005];
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin >> T;
	while(T --)
	{
		cin >> n >> (s + 1) >> (t + 1);
		for(int i = 1;i <= n;i ++)
		{
			sum1[i] = sum1[i - 1] + s[i] - '0';//本就存在于 s 中的 1 
			if(i <= 2)continue;
			sum2[i] = sum2[i - 1];
			if(t[i - 2] == '1' && t[i] == '1' && s[i - 1] == '0')sum2[i] ++;//（a,a） 情况
			if(i <= 3)continue;
			sum3[i] = sum3[i - 1];
			sum4[i] = sum4[i - 1];
			if(s[i] == '0' && s[i - 2] == '0' && t[i - 3] == '1' && t[i - 1] == '0')sum3[i] ++;//（a,b） 情况
			if(t[i] == '1' && t[i - 2] == '0' && s[i - 1] == '0' && s[i - 3] == '0')sum4[i] ++;//（b,a） 情况
			if(i <= 4)continue;
			sum5[i] = sum5[i - 1];
			if(s[i] == '0' && s[i - 2] == '0' && s[i - 4] == '0' && t[i - 1] == '0' && t[i - 3] == '0')sum5[i] ++;//（b,b）情况
			
		}
		cin >> q;
		while(q --)
		{
			cin >> l >> r;
			int ans = 0;
			ans += sum1[r] - sum1[l - 1];
			if(l + 2 <= r)ans += sum2[r] - sum2[l + 1];
			if(l + 3 <= r)ans += sum3[r] - sum3[l + 2] + sum4[r] - sum4[l + 2];
			if(l + 4 <= r)ans += sum5[r] - sum5[l + 3];//统计时有用到 i 前面的元素，前缀和的左界需往右移
			cout << ans << endl;
		}
	}
	return 0;
}//完结撒花QwQ

```

---

## 作者：mango2011 (赞：1)

救命题，大力感谢这道题！

首先，我们肯定有贪心策略：

即先把 $b$ 中的 $0$ 通过第一种操作变成 $1$；再把 $a$ 中的 $1$ 变成 $0$。

为了方便，令 $s_1=a$，$s_2=b$。

我们先考虑把整个字符串进行操作，把操作过后的字符串保存为 $b$ 保存为 $s_4$，再把操作过后的字符串保存为 $s_3$，于是乎我们用一个前缀和维护区间 $1$ 的个数，然后~~做完了~~我们需要解决什么问题呢？

我们发现对于一个询问区间 $[l,r]$ 其中的 $[l+2,r-2]$ 一定不受影响，因为与左右两端的操作没有关系。

但是 $l,l+1,r,r-1$ 这 $4$ 个位置是会受到影响的（可能有重合，需要特判）。

对于两端的点，如果他们是 $1$，那么有贡献，否则没救；对于端点向中间移动一格的点，即 $l+1,r-1$，怎么特殊判断呢？

当这个位置是 $1$ 或者与之对应的两个位置可以通过操作变成 $1$ 就可以了，于是我们也完成了这个特殊判断。

这样，我们就成功做完了这一道 *2000 的思维题。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
string s1,s2,s3,s4;
int pre[maxn];
int n;
bool check(int x)
{
    return s1[x]=='1';
}
bool c1(int x)
{
    if(s1[x]=='1') return 1;
    if(s2[x-1]=='1'&&s4[x+1]=='1') return 1;
    return 0;
}
bool c2(int x)
{
    if(s1[x]=='1') return 1;
    if(s2[x+1]=='1'&&s4[x-1]=='1') return 1;
    return 0;
}
void solve()
{
    cin>>n>>s1>>s2;
    s1='*'+s1,s2='*'+s2;
    s4=s2,s3=s1;
    for(int i=1;i<n-1;i++) if(s1[i]=='0'&&s1[i+2]=='0') s4[i+1]='1';
    for(int i=1;i<n-1;i++) if(s4[i]=='1'&&s4[i+2]=='1') s3[i+1]='1';
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+s3[i]-'0';
    int q;
    cin>>q;
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        if(l+1>=r)
        {
            int o=0;
            for(int i=l;i<=r;i++) o+=check(i);
            cout<<o<<'\n';
        }
        else
        {
            if(l+2==r)
            {
                int t1=check(l)+check(r);
                cout<<t1+(s1[l+1]=='1'||(s2[l]=='1'&&s2[r]=='1'))<<'\n';
            }
            else
            {
                int t=pre[r-2]-pre[l+1];
                if(check(l)) t++;
                if(check(r)) t++;
                if(c1(l+1)) t++;
                if(c2(r-1)) t++;
                cout<<t<<'\n';
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
    int T=1;
    cin>>T;
    while(T--) solve();
    return 0;
}

```

---

## 作者：Ghosty_Neutrino (赞：0)

### 题意

有两个长度相同的二进制字符串 $s$ 和 $t$，长度为 $n$，由字符 $0$ 和 $1$组成。

还有一台计算器可以对长度相同的二进制字符串 $a$ 和 $b$ 进行两种运算 $k$：

如果 $a_i=a_{i+2}=0$，则可以赋值 $b_{i+1}:=1$。

如果 $b_i=b_{i+2}=1$，则可以赋值 $a_{i+1}:=1$。

萨沙对下面的问题产生了兴趣：如果我们考虑字符串 $a=s_ls_{l+1}...s_r$ 和字符串 $b=t_lt_{l+1}...t_r$，那么使用计算器最多可以在字符串 $a$ 中得到多少个 $1$ 字符。由于萨沙非常好奇但很懒惰，所以由你来回答他感兴趣的几对字符串 $(l_i,r_i)$ 的问题。

### 分析

对于区间，寻找最优操作方案，我们贪心地考虑，先用 $s$ 增加 $t$ 的 $1$。若，再用 $t$ 的 $1$ 使 $s$ 的 $1$ 变多，这样做一定是最优的，保证了第一步之后 $t$ 中的 $1$ 最多，从而最终 $s$ 中的 $1$ 也最多。

接着我们考虑每一位会怎样被改变。若 $s_i$ 被变为 $1$，需要 $t_{i-1}=1$，同时 $t_{i+1}=1$ 和 $t$ 的这两位又会受到 $s_{i-2},s_{i},s{i+2}$ 的影响，所以对于每一位 $s_i$，都只会受到 $[i-2,i+2]$ 区间内的影响。

因此可以提前对整个区间进行操作，并对最终的 $s$ 求前缀和。对于询问长度不超过 $4$ 的情况暴力操作求解。超过 $4$ 时由于 $[l+2,r-2]$ 只受区间 $[l,r]$ 内的影响，答案不变，记录下原来的答案，再单独对 $[l,l+4]$ 操作并记录前两位的答案，然后对 $[r-4,r]$ 操作并记录后两位的答案，最后三部分相加即可。

### 代码


```cpp
#include<bits/stdc++.h>

typedef long long LL;
using namespace std;
const int N = 2e5 + 10;
LL n, q, pre[N], s[N], t[N], t1[N], t2[N];
char ss[N], st[N];

void deal(int l, int r) {
    int len = r - l + 1;
    for (int i = l; i <= r; i++) {
        t1[i - l + 1] = s[i];
        t2[i - l + 1] = t[i];
    }
    for (int i = 1; i + 2 <= len; i++) {
        if (!t1[i] && !t1[i + 2])
            t2[i + 1] = 1;
    }
    for (int i = 1; i + 2 <= len; i++) {
        if (t2[i] && t2[i + 2])
            t1[i + 1] = 1;
    }
    for (int i = 1; i <= len; i++)
        t1[i] += t1[i - 1];
}

void solve() {
    cin >> n >> ss >> st >> q;
    for (int i = 1; i <= n; i++) {
        s[i] = ss[i - 1] - '0';
        t[i] = st[i - 1] - '0';
    }
    deal(1, n);
    for (int i = 1; i <= n; i++)
        pre[i] = t1[i];
    while (q--) {
        LL l, r;
        cin >> l >> r;
        if (r - l < 4) {
            deal(l, r);
            cout << t1[r - l + 1] << endl;
        } else {
            int res = pre[r - 2] - pre[l + 1];
            deal(l, l + 4);
            res += t1[2];
            deal(r - 4, r);
            res += (t1[5] - t1[3]);
            cout << res << endl;
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}


```

---

## 作者：_WRYYY_ (赞：0)

[在我的博客观看。](https://www.cnblogs.com/wryyy-233/p/18262380)

好写程度：$E>D>C$。

好想程度：$C>D=E$。

总结：~~C 是全场最难。~~

我们考虑把两个操作对全体的 $a_i,b_i$ 都做一遍，会发现我们只会做这两遍，不会再有嵌套的了，因为都做过一遍后 $\{a\}$ 中 0 的数量只会减少，而且即使再做一遍也无法给 $\{b\}$ 改成不一样的了，比较显然。

下文中令 $\{a\},\{b\}$ 分别表示修改过的数组，$\{\overline a\},\{\overline b\}$ 表示原数组。

然后观察我们可以知道，对于任意一对满足 $r-l>2$ （即区间长度大于等于 4）的 $(l,r)$，$\{b\}$ 中受影响的只有左右端点，那么 $\{a\}$ 中受影响的就会是左右边界的各两个字符，所以我们考虑做前缀和，将不受影响的直接前缀和求出，受影响的就直接加上 $\overline a_l$ 和 $\overline a_l$，然后结合 $\overline b$ 和 $b$ 求出另外两个。

至于区间长度小于 4 的，直接暴力即可。

时间复杂度 $O(\sum n+\sum q)$。

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 200010
using namespace std;
using namespace __gnu_pbds;
int sum[N], n, q;
int A[N], B[N], B1[N];
void all_in()
{ // all in!
	char c;
	for (int i = 1; i <= n; i++)
	{
		cin >> c;
		sum[i] = A[i] = (c == '1');
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> c;
		B1[i] = B[i] = (c == '1');
	}
	return;
}
void mksum()
{
	for (int i = 2; i < n; i++)
		B1[i] |= !(A[i - 1] | A[i + 1]);
	for (int i = 2; i < n; i++)
		sum[i] |= (B1[i - 1] & B1[i + 1]);
	for (int i = 1; i <= n; i++)
		sum[i] += sum[i - 1];
	return;
}
void query()
{
	int x, y;
	while (q--)
	{
		cin >> x >> y;
		if (y == x)
			cout << A[x] << "\n";
		else if (y - x == 1)
			cout << A[x] + A[y] << "\n";
		else if (y - x == 2)
			cout << A[x] + A[y] + ((B[x] & B[y]) | A[x + 1]) << "\n";
		else
			cout << sum[y - 2] - sum[x + 1] + A[x] + A[y] + ((B[x] & B1[x + 2]) | A[x + 1]) + ((B[y] & B1[y - 2]) | A[y - 1]) << "\n";
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n;
		all_in();
		mksum();
		cin >> q;
		query();
	}
	return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

**E		\*2042**

1. 暴力怎么做？

   贪心的用 $s$ 的 $0$ 使 $t$ 的 $1$ 先变多，再用 $t$ 的 $1$ 使 $s$ 的 $1$ 变多。

2. 能影响 $s_i \to 1$ 的有效范围是多少？

   $s_i$ 取决于 $t_{i - 1}$ 和 $t_{i + 1}$ 是否为 $1$。

    $t_{i - 1}$ 取决于 $s_{i - 2}$ 和 $s_i$ 是否为 $0$，而 $s_{i - 2} = 0$ 只与原始序列有关。 
   
   因此 $s_i$ 的值只与 $[i - 2, i + 2]$ 有关。

我们不妨对整个 $s$  操作变为 $s'$。（即 $s_1\sim s_n$ 最多几个 $1$）

对于一个询问 $[l, r]$，$[l + 2, r - 2]$ 最后结果肯定是与 $s'$ 一致的。

然后再单独处理左右边界。

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
using namespace std;

using ll = long long;

void solve() {
	int n; string s, t;
	cin >> n;
	cin >> s >> t;
	vector<int> a(n), b(n);
	for(int i = 0; i < n; ++ i) {
		a[i] = s[i] - '0';
		b[i] = t[i] - '0';
	}
	vector<int> nb = b;
	for(int i = 0; i < n - 2; ++ i) {
		if(!a[i] && !a[i + 2]) {
			nb[i + 1] = 1;
		}
	}
	vector<int> na = a;
	for(int i = 0; i < n - 2; ++ i) {
		if(nb[i] && nb[i + 2]) {
			na[i + 1] = 1;
		}
	}
	for(int i = 1; i < n; ++ i) {
		na[i] += na[i - 1];
	}
	int m; cin >> m;
	while(m --) {
		int l, r; cin >> l >> r, -- l, -- r;
		if(r - l <= 4) {
			int tmp = 0;
			for(int i = l; i <= r; ++ i) {
				tmp += a[i];
			}
			vector<int> xb;
			for(int i = l; i <= r - 2; ++ i) {
				if(!b[i + 1] && !a[i] && !a[i + 2]) {
					b[i + 1] = 1;
					xb.eb(i + 1);
				} 
			}
			for(int i = l; i <= r - 2; ++ i) {
				if(!a[i + 1] && b[i] && b[i + 2]) {
					++ tmp;
				} 
			}
			cout << tmp << '\n';
			for(int i : xb) b[i] = 0;
		}
		else {
			int tmp = a[l] + a[r] + (na[r - 2] - na[l + 1]);
			if(b[l] && nb[l + 2]) 
				++ tmp;
			else
				tmp += a[l + 1];
			if(b[r] && nb[r - 2]) 
				++ tmp;
			else
				tmp += a[r - 1];
			cout << tmp << '\n';
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int T;
	cin >> T;
	
	while(T --) {
		solve();
	}
	return 0;
}
```

---

