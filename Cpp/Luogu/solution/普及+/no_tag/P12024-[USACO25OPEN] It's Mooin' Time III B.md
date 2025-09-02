# [USACO25OPEN] It's Mooin' Time III B

## 题目描述

Elsie 正在试图向 Bessie 描述她最喜欢的 USACO 竞赛，但 Bessie 很难理解为什么 Elsie 这么喜欢它。Elsie 说「现在是哞哞时间！谁想哞哞？请，我只想参加 USACO」。

Bessie 仍然不理解，于是她将 Elsie 的描述转文字得到了一个长为 $N$（$3 \leq N \leq 10^5$）的字符串，包含小写字母字符 $s_1s_2 \ldots s_N$。Elsie 认为一个包含三个字符的字符串 $t$ 是一个哞叫，如果 $t_2 = t_3$ 且 $t_2 \neq t_1$。

一个三元组 $(i, j, k)$ 是合法的，如果 $i < j < k$ 且字符串 $s_i s_j s_k$ 组成一个哞叫。对于该三元组，FJ 执行以下操作计算其值：

- FJ 将字符串 $s$ 在索引 $j$ 处弯曲 90 度
- 该三元组的值是 $\Delta ijk$ 的面积的两倍。

换句话说，该三元组的值等于 $(j-i)(k-j)$。

Bessie 向你进行 $Q$（$1 \leq Q \leq 3 \cdot 10^4$）个查询。在每个查询中，她给你两个整数 $l$ 和 $r$（$1 \leq l \leq r \leq N$，$r-l+1 \ge 3$），并询问满足 $l \leq i$ 和 $k \leq r$ 的所有合法三元组 $(i, j, k)$ 的最大值。如果不存在合法的三元组，输出 $-1$。

注意这个问题涉及到的整数可能需要使用 64 位整数类型（例如，C/C++ 中的 `long long`）。

## 说明/提示

样例解释：对于第一个查询，$(i,j,k)$ 必须满足 $1 \le i < j < k \le 12$。可以证明，对于某个合法的 $(i,j,k)$，$\Delta ijk$ 的最大面积在 $i=1$，$j=8$ 以及 $k=12$ 时取到。注意 $s_1 s_8 s_{12}$ 是字符串 "acc"，根据前述定义是一个哞叫。$\Delta ijk$ 的直角边长为 $7$ 和 $4$，从而它的面积的两倍将等于 $28$。
对于第三个查询，$(i,j,k)$ 必须满足 $4 \le i < j < k \le 8$。可以证明，对于某个合法的 $(i,j,k)$，$\Delta ijk$ 的最大面积在 $i=4$，$j=5$ 以及 $k=6$ 时取到。

对于第四个查询，不存在满足 $2 \le i < j < k \le 5$ 的 $(i,j,k)$ 使得 $s_i s_j s_k$ 是一个哞叫，所以该查询的输出为 $-1$。

- 测试点 $2\sim3$：$N,Q\le 50$。
- 测试点 $4\sim6$：$Q=1$，唯一的询问满足 $l=1$ 且 $r=N$。
- 测试点 $7\sim 11$：没有额外限制。

## 样例 #1

### 输入

```
12 5
abcabbacabac
1 12
2 7
4 8
2 5
3 10```

### 输出

```
28
6
1
-1
12```

# 题解

## 作者：IcyDragon (赞：10)

## 思路

先预处理一个字符集 $c$，$c_{i,j}$ 表示字符 $i$ 的第 $j$ 次出现实在字符串 $s$ 的第几位。

对于每次询问，

1. 枚举三元组中第一个**字符** $i$（不是下标，是**字符**！），接着在 $c_i$ 中查找 $\ge l$ 的第一个下标 $p1$。
2. 枚举最后一个**字符** $k$（注意不能与 $i$ 相等），接着在 $c_k$ 中查找 $\le r$ 的最后一个下标 $p3$。
3. 在 $c_k$ 中查找最接近 $\lfloor \frac{i+k}{2} \rfloor$ 的下标 $p2$。
4. 更新答案（实际上写代码时会找在左边和右边最接近 $\lfloor \frac{i+k}{2} \rfloor$ 的最大值来更新答案）。
5. 输出答案 ~~（废话）~~。
6. 十年 OI 一场空，不开 `long long` 见祖宗。

## 代码

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

vector<int> c[50];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,q,l,r;
	string s;
	cin>>n>>q>>s;
	for(int i = 0; i < n; i++){
		c[s[i]-'a'].push_back(i);
	}
	int i,j,k;
	long long ans;
	while(q--){
		cin>>l>>r;
		l--;r--;
		ans = -1;
		for(int c1 = 0; c1 < 26; c1++){
			i = lower_bound(c[c1].begin(),c[c1].end(),l)-c[c1].begin();
			if(i>=c[c1].size() || i>=r-1){
				continue;
			}
			for(int c3 = 0; c3 < 26; c3++){
				if(c3==c1 || c[c3].size()<2){
					continue;
				}
				k = upper_bound(c[c3].begin(),c[c3].end(),r)-c[c3].begin()-1;
				if(k<=0 || c[c3][k-1]<=c[c1][i]){
					continue;
				}
				j = upper_bound(c[c3].begin(),c[c3].end(),(c[c3][k]+c[c1][i])/2)-c[c3].begin();
				if(j < k){
					ans = max(ans,(c[c3][k]-c[c3][j])*1LL*(c[c3][j]-c[c1][i]));
				}
				j--;
				if(j>=0 && c[c1][i]<c[c3][j]){
					ans = max(ans,(c[c3][k]-c[c3][j])*1LL*(c[c3][j]-c[c1][i]));
				}
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：4)

首先 $t_2$ 确定时，$t_1$ 尽量靠左，$t_3$ 尽量靠右。

对于查询 $(l,r)$ 和颜色 $c$，尽量选最左边的不是 $c$ 的 $a_l$ 和最右边的 $c$，此时贡献中两个因数的和是固定的，所以约平均越好，二分即可，复杂度 $O(qV\log n)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R x<<1|1
#define mid ((l+r)>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK Ll<=l&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
#define yy return puts("Yes"),void()
#define nn return puts("No"),void()
#define YY puts("Yes"),exit(0)
#define NN puts("No"),exit(0) 
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(int x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
using namespace std;
const int N=1e5+5,M=1e7+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
inline void add(int &a,int b){if(b<0)b+=mod;((a+=b)>=mod) and (a-=mod);}
inline int Add(int a,int b){return add(a,b),a;}
inline int mul(int a,int b){add(b,mod);return 1LL*a*b%mod;}
inline void Mul(int &a,int b){a=mul(a,b);}
inline void red(int &a,int b){add(a,mod-b);}
inline int Red(int a,int b){return red(a,b),a;}
inline int qp(int a,ll b){if(!b)return 1;int c=qp(a,b>>1LL);Mul(c,c);if(b&1)Mul(c,a);return c;}
inline int INV(int x){return qp(x,mod-2);}
int n,m,tot,a[N];
string st;
int out[N];
struct node{
	int l,id;
};
vector<node>p[N];
int s[27][N],tp[27],nxt[N][27],ps[26];
inline void Main(){
	n=read(),m=read();
	cin>>st,st='#'+st;
	repn(i)a[i]=st[i]-'a'+1;
	repm(i){
		int l=read(),r=read();
		p[r].pb({l,i}),out[i]=-1;
	}
	rep(i,1,26)ps[i]=n+1;
	per(i,n,1){
		ps[a[i]]=i;
		rep(j,1,26)nxt[i][j]=ps[j];
	}
	repn(i){
		s[a[i]][++tp[a[i]]]=i;
		E(i){
			int le=y.l,id=y.id;
			rep(j,1,26)if(tp[j]>=2){
				int pr=le;
				if(le>=s[j][tp[j]])continue;
				if(a[le]==j){
					int nx=n+1;
					rep(k,1,26)if(j!=k)nx=min(nx,nxt[le][k]);
					if(nx>=s[j][tp[j]])continue;
					le=nx;
				}
				int l=1,r=tp[j]-1,pur=s[j][tp[j]]+le>>1,nw=0;
				while(l<=r){
					if(s[j][mid]<=pur)nw=mid,l=mid+1;
					else r=mid-1;
				}
				rep(k,max(1LL,nw-6),min(tp[j]-1,nw+6)){
					if(s[j][k]>le)out[id]=max(out[id],(s[j][tp[j]]-s[j][k])*(s[j][k]-le));
				}
				le=pr;
			}
		}
	}
	repm(i)cout <<out[i]<<'\n';
	
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}

```
如果题目中不是小写字母构成的字符串，而是值域为 $n$ 的数组，我们依旧可以完成。

考虑根号分治，设阈值为 $B$，对于每种颜色 $x$ 求出出现次数 $c_x$。

- $c_x\ge B$

直接做二分，复杂度 $O(\frac{n}{B}q\log n)$。

- $c_x\le B$

将询问离线，扫描线维护李超线段树插入线段，复杂度 $O(nB\log^2n)$。

取 $B=\sqrt{\frac{q}{\log n}}$ 时有理论最优复杂度 $n\log n\sqrt{q\log n}$。

---

## 作者：lzdll (赞：1)

本题数据很弱，导致有人复杂度不对的做法被放过去了，如果字母除了第一个以外全一样就炸了。我来写一篇复杂度正确的题解。

首先注意到字符集只有小写字母，所以考虑枚举那两个相同的字母是什么，然后求出最远的不同的字母，然后尽量从中间选出那个 $j$。

假设相同的字母是 $ch$，你要先预处理出 $ch$ 每次出现的位置，然后二分找出位置不超过 $r$ 的最远的，这个位置就是 $k$。

然后使用二分再求出 $i$，只需二分求出从 $l$ 开始连续的 $ch$ 就行，需要预处理前缀和。

最后，求出 $j$，我们需要求出 $i$，$k$ 中点的两边的最近的两个 $j$，然后取最大值。

注意判断越界问题。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
string s;
int pos[26][100005],tot[26],sum[26][100005];
int geti(int l,int r,int ch){
	if(s[l]-'a'!=ch)return l;
	int mid,res=-1;
	while(l<=r){
		mid=l+r>>1;
		if(sum[ch][mid]-sum[ch][l-1]==mid-l+1)l=mid+1;
		else r=mid-1,res=mid;
	}
	return res;
}
signed main(){
	cin>>n>>q>>s,s=" "+s;
	for(int i=1;i<=n;++i){
		int ch=s[i]-'a';
		++tot[ch];
		pos[ch][tot[ch]]=i;
		for(int j=0;j<26;++j){
			sum[j][i]=sum[j][i-1]+(j==ch);
		}
	}
	while(q--){
		int l,r,ans=-1;cin>>l>>r;
		for(int ch=0;ch<26;++ch){
			int k=pos[ch][upper_bound(pos[ch]+1,pos[ch]+tot[ch]+1,r)-pos[ch]-1];
			int i=geti(l,r,ch);
			if(i==-1||i>=k-1)continue;
			int posj=lower_bound(pos[ch]+1,pos[ch]+tot[ch]+1,(i+k>>1)+1)-pos[ch];
			int jl=pos[ch][posj-1],jr=pos[ch][posj];
			if(jl<k&&jl>i)ans=max(ans,(k-jl)*(jl-i));
			if(jr<k&&jr>i)ans=max(ans,(k-jr)*(jr-i));
		}cout<<ans<<"\n";
	}
	return 0;
}
```

代码不长。

---

## 作者：nbhs23a28 (赞：1)

~~（啥时候 Elsie 也喜欢 USACO 了）~~  
本题是铜组唯一有点思维含量的题。
## 思路分析
由于这是一场铜组的题，显然不必用上数据结构或是什么高级算法，事实上，贪心就能过，以下简述如何贪心及正确性证明。

注意到本题 $Q \le 3\cdot 10^4$ 较小，而字符串仅由小写字母构成。不难想到，我们可以枚举哞叫的 $t_2,t_3$ 对应的字母。对于每一个字母，我们可以进行贪心：无论 $i,j$ 如何，$k$ 最大显然更优（一次函数单调性）；同理，无论 $j,k$ 如何，$i$ 最大显然更优。至于 $j$，在固定 $i,k$ 下这就是一个二次函数了，此时当 $j$ 离对称轴 $\frac{i+k}{2}$ 越近越优。由此，贪心策略就显而易见了，其正确性也不言而喻了（藏在分析中）。

由此，我们只需开桶维护每个字母在每个 $[1,i]$ 中下标最大的位置和每个字母在每个 $[i,n]$ 中不为该字母的下标最小的位置即可，至于寻找 $j$，只需二分距中间位置最近的该字母即可。实现细节见代码。

时间复杂度 $O(Nk+Qk\log N)$。（$k$ 表示字符值域，本题 $k=26$）
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[100010];
int n,q,cnt[26][100010],pl[26][100010],f[26][100010];
//pl:每个字母在每个 [1,i] 中下标最大的位置
//f:每个字母在每个 [i,n] 中不为该字母的下标最小的位置
int main()
{cin>>n>>q>>c;
 for(int i=1;i<=n;i++)
 {for(int j=0;j<26;j++)	
  cnt[j][i]=cnt[j][i-1],pl[j][i]=pl[j][i-1];
  cnt[c[i-1]-'a'][i]++;pl[c[i-1]-'a'][i]=i;
 }
 for(int i=n;i>=1;i--)
 {for(int j=0;j<26;j++)
  f[j][i]=i;
  f[c[i-1]-'a'][i]=f[c[i-1]-'a'][i+1];
 }
 while(q--)	
 {int l,r;cin>>l>>r;
  long long _max=-1;
  for(int j=0;j<26;j++)
  {int k=pl[j][r],i=f[j][l];
   if(k<=l||i>=r) continue;
   int mid=(i+k)>>1;
   int id1=lower_bound(cnt[j]+1,cnt[j]+n,cnt[j][mid])-cnt[j];
   int id2=upper_bound(cnt[j]+1,cnt[j]+n,cnt[j][mid])-cnt[j];
   if(id1<=i&&id2>=k) continue;
   if(id1<=i) _max=max(_max,(long long)(k-id2)*(id2-i));
   else if(id2>=k) _max=max(_max,(long long)(k-id1)*(id1-i));
   else _max=max(_max,max((long long)(k-id2)*(id2-i),(long long)(k-id1)*(id1-i)));
  }
  cout<<_max<<'\n';	
 }
}
```

---

## 作者：ldll0721 (赞：1)

# 很好的二分题目

### 暴力分

$O(n^2)$ 很简单的暴力，循环遍历即可。

### 本人做法（非完全正解）

#### Part 1 预处理
观察到字符串只有小写字母这一条件，可直接用 $pos_{x,cnt_{x}}$ 记录第 $cnt_{x}$ 个字母 $x$ 的位置。

#### Part 2 二分查找（可优化部分）
对于区间 $[l,r]$，枚举 $26$ 个字母，二分查找 $pos$ 数组第一个小于 $r$ 的对应字母下标 $i$，同时再循环枚举从 $l$ 开始第一个与当前字符不同的字符的对应下标 $k$（这个地方机房大佬 l6506001 说可以预处理优化，但本人没有写出来）。因为我们要使得 $(j-i)(k-j) $ 尽量的大。所以选择 $j$ 时应该尽量靠近 $i$ 和 $k$ 的中间，最后二分查找 $j$ 即可。

### code


```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define maxn 200005
int n, q, a[maxn],pos[30][maxn],la[30],num[30][maxn],sl[30],wz[maxn];
string s;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	cin >> s;
	s = ' ' + s;
	for (int i = 1; i <= n; i++) {
        int x=s[i]-'a';	
        sl[x]++;
        wz[i]=sl[x];
        num[x][sl[x]]=i;
	}
	for(int i=1;i<=q;i++){
		int l,r,ans=0;
		cin>>l>>r;
		for(int j=0;j<=25;j++){
			int wb=upper_bound(num[j]+1,num[j]+sl[j]+1,r)-num[j]-1;
			if(wb==sl[j]+1)continue;
			int d=l;
			while(s[d]-'a'==j)d++;
			if(num[j][wb-1]<l)continue;
			int hd=upper_bound(num[j]+1,num[j]+sl[j]+1,d)-num[j];
			int mid=(num[j][wb]+d)/2;
			int hg=upper_bound(num[j]+hd+1,num[j]+wb+1,mid)-num[j];
			//cout<<d<<" "<<hg<<" "<<num[j][wb]<<endl;
			ans=max({ans,(num[j][wb]-num[j][hg])*(num[j][hg]-d),(num[j][wb]-num[j][hg-1])*(num[j][hg-1]-d)});
		}
		if(ans!=0)cout<<ans<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}

```

### 题外话
这题数据真的挺水的，因为本人做法最慢会卡到 $O(26*nq)$，并且机房另外一位dalao a_123_a 使用了$O(26^2*q*log_{n})$ 的做法也通过了此题。

---

## 作者：qW__Wp (赞：0)

假如已知 $i,k$，最优取 $j$ 应该是什么？显然当 $j - i$ 和 $k - j$ 尽量接近时，即 $j$ 尽量接近 $\frac{k-i}{2}$ 时，$(j - i)(k - j)$ 最大（这是一个经典问题，证明见后）。

假如已确定 moo 字符串 $t_it_jt_k$ 的组成为 $t_i = c1$，$t_j = t_k = c2 \ne c1$，又知 $l \le i < j < k \le r$，则最优情况为 $i$ 尽量小，$k$ 尽量大，$j$ 尽量接近 $\frac{k-i}{2}$。

那么可以枚举 $c1,c2$。记 $L_{i,c}$ 为满足 $j \le i$ 且 $s_j = c$ 的最大 $j$，$R_{i,c}$ 为满足 $j \ge i$ 且 $s_j = c$ 的最小 $j$。则三元组 $(i,j,k)$ 的最优方案为：$i = R_{l,c1}$，$k = L_{r,c2}$，$j$ 为 $L_{mid,c2}$ 和 $R_{mid,c2}$ 中最接近 $mid$ 的数，其中 $mid = \frac{k-i}{2}$。

```C++
#include <bits/stdc++.h>
#define int long long
#define INF 1e18

using namespace std;

const int N = 1e5 + 5;

int l[N][26], r[N][26];

signed main() {
	int n, q; cin >> n >> q;
	for (int i = 1; i <= n; i ++) for (int j = 0; j < 26; j ++) r[i][j] = INF;
	for (int i = 1; i <= n; i ++) {
		char c; cin >> c;
		l[i][c - 'a'] = r[i][c - 'a'] = i;
	}
	for (int j = 0; j < 26; j ++) {
		for (int i = 2; i <= n; i ++) {
			l[i][j] = max(l[i][j], l[i - 1][j]);
		}
		for (int i = n - 1; i >= 1; i --) {
			r[i][j] = min(r[i][j], r[i + 1][j]);
		}
	}
	while (q --) {
		int x, y; cin >> x >> y;
		int ans = -1;
		for (int i = 0; i < 26; i ++) {
			for (int j = 0; j < 26; j ++) {
				if (i == j) continue;
				int a = r[x][i], c = l[y][j];
				if (a > y || c < x) continue;
				int mid = (a + c) >> 1;
				int b1 = l[mid][j], b2 = r[mid][j];
				if (a != b1 && b1 != c && b1 > x) ans = max(ans, (b1 - a) * (c - b1));
				if (a != b2 && b2 != c && b2 < y) ans = max(ans, (b2 - a) * (c - b2));
					// 两种情况取最大
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

已知：正整数 $i,k$，$i < k$。

求证：对于 $i < j < k$，当 $|(j - i) - (k - j)|$ 越小，$(j - i)(k - j)$ 越大。

证明：不妨设 $a = j - i,b = k - j$，记常数 $S = a + b = k - i$。

因为 

$$ab = \frac{(a + b) ^ 2 - (a - b) ^ 2}{4} = \frac{S ^ 2 - (a - b) ^ 2}{4}$$

又因为当 $|a-b|$ 越大，$(a - b) ^ 2$ 越大。且 $S ^ 2$ 为常数。

所以当 $|a-b|$ 越小，$ab$ 越大。当 $a = b$ 时 $ab$ 取得最大值。

证毕。

---

## 作者：Tiger_Rory (赞：0)

由于三元组的值等于 $(j−i)(k−j)$，它等同于 $j$ 到 $i$ 的距离乘上 $k$ 到 $j$ 的距离，所以我们在对于区间内每个字母进行计算时，只需要遍历 $j$ 的位置即可，因为 $i$ 和 $k$ 显然在区间内的最左和最右的位置就是最优的，是固定的。

我们考虑对于每次询问，先强行找出 $i$，然后二分判断出区间内所有当前字母中哪个位于区间内最左的位置和最右的位置 $k$，然后再在其中找 $j$ 即可。也许有更优的解法吧。

代码如下。


```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
int n,q,l,r; 
string s; 
vector<int>vec[50];   
signed main() {
	cin.tie(0)->sync_with_stdio(0);cout.tie(0);
	cin>>n>>q>>s; 
	s=" "+s; 
	for(int i=1;i<=n;i++){
		vec[s[i]-'a'+1].pb(i);
    //字母的位置集合 
	}
	while(q--){
		cin >> l >> r; 
		int ans = -1; 
		for(int i = 1; i <= 26; i++){
			if(vec[i].size() <= 1) continue; 
			int L = 0, R = vec[i].size() - 1; 
			//while(vec[i][L] <= l && L <= R) L++;  
			int beg=L,end=R; 
			while(beg<=end){
				int mid=(beg+end)>>1; 
				if(vec[i][mid]<=l){
					L=mid; 
					beg=mid+1; 
				}
				else L=mid,end=mid-1;   
			}
			L=beg;//这是j的枚举左范围 
			//while(vec[i][R] > r && L <= R) R--; 
			beg=L,end=R; 
			while(beg<=end){
				int mid=(beg+end)>>1; 
				if(vec[i][mid]>r){
					R=mid; 
					end=mid-1; 
				}
				else R=mid,beg=mid+1; 
			}
			R=end;//这是最右端k 
			if(L >= R) continue;//没有答案
			int tmp = 0; int LL = l; 
			while(s[LL] - 'a' + 1 == i) LL++;
      //找i  
			for(int j = L; j < R; j++){
				int RR = vec[i][j];             
				tmp = vec[i][R] - RR;    
				ans = max(ans, tmp * (RR - LL)); 
			}
		}
		cout << ans << '\n'; 
	}
	return 0;
}
```

如有不足，欢迎批评指正。

---

