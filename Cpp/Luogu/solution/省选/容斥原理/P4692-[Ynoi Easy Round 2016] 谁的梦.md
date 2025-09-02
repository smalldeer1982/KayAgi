# [Ynoi Easy Round 2016] 谁的梦

## 题目背景

6.373 

世界是独立于我的意志的。 

6.374 

就算我们所期望的全部的事情都发生了 

这果然也只能说是命运的恩惠吧。 

要问为什么，那是因为意志和世界之间 

能够保证这件事的逻辑性的关联并不存在 

Ludwig Josef Johann Wittgenstein [逻辑哲学论] 

自从双胞胎的哥哥过世起，已经过了多久了呢… 

从那时起，我一直保存着那个布偶。 

在那以后的我只是个影子…而这个布偶才是我… 

这样也并没有什么不好。 

我觉得只要现在的我消失掉就行了… 

那两个人却救了这样的我。 

一个是由歧姐… 

她又来到了我的身边… 

带着皆守哥…回到了我们的身边… 

水上由岐姐姐…温柔的姐姐 

曾经非常喜欢皆守哥的人……

![](https://cdn.luogu.com.cn/upload/pic/21195.png)

回去的路上…

平时不会经过的坡道…

在登上那个坡道的途中…

我看到了夜晚的太阳。

明明就在附近，却一直不知道的巨大的向日葵。

夜露使它的绒毛泛出了白光。

碧蓝的月光和黄色的向日葵…

就好像太阳和月亮的立场反过来一样…

原本是那么耀眼的的太阳在地上，只能在其背后下发光的月亮在天上…

黄色的向日葵被染成了碧蓝色。

那副样子虽然很美丽…

努力绽放的向日葵，看起来反而是柔弱的存在。

在夜里向天空伸展的向日葵…

我在车内一直追寻着它的身影…

被夜晚的月光映照着的太阳。

被染成碧蓝色的太阳…

它的身影…我一直追寻着……

![](https://cdn.luogu.com.cn/upload/pic/21196.png)

被月光照亮的天台上…

一个人影…

明明只是一个人影…却好像…在和什么东西对峙着一样…

皆守哥…

月下的立像，一个人影。

胸口在风中闪烁。

放在胸前的手里的是…那时的小刀。

和七年前同样的姿势。

唯一不同的是，那里的人影只有一个。

那把小刀，好像是被他自己刺入体内。

![](https://cdn.luogu.com.cn/upload/pic/21197.png)

是诅咒…

这是理所当然的事…

那并不是什么精神病…

那是诅咒…

下在幸存的我们身上的…诅咒…

说不定，不仅仅是卓司哥…连由岐姐也在诅咒我们…

所以变成这种结果…

哥哥刺向了自己的胸口…

破坏了我的半身…

然后…还要把很多人送回到天空…

回归天空的日子。

交还灵魂的日子。

那一天，卓司哥对我做的事情。

杀了由岐姐的…那个行为…

他想要再一次实行…

这次…和很多人一起…

![](https://cdn.luogu.com.cn/upload/pic/21198.png)

不是…

那是…我啊…

是那个…坡道的事情啊…

两个人一起看到向日葵的…那个坡道…

…我说要爬上那个坡道…要去寻找爸爸的灵魂…

我想，如果到了那个坡道的前方，就能取回爸爸的灵魂…爸爸就会复生的…

如果越过向日葵之路…向着向日葵所朝向的天空延伸的…那个大大的坡道的话…
大概，就会有爸爸的灵魂…

爸爸的故乡的…大大的坡道…

![](https://cdn.luogu.com.cn/upload/pic/21199.png)

哥哥的身体浮在空中…

我无言地跳了出去。

啊啊…是这样啊…

由岐姐也是这种心情啊…

并没有什么道理可言…

只是因为喜欢的人向着天空跳下去了…

我想要抓住那个身体…

我——

## 题目描述

您正在打 galgame，突然断电了，于是您跑去物管处问，结果发现是由于一个光头踢了变压器一脚导致的，可能还要修很久，于是您决定想一个之前见过的数据结构题：

定义一个序列的权值为不同数字的个数，例如 $[1,2,3,3]$  权值为 $3$。

现在有 $n$ 个序列，我们在每个序列里面选一个连续非空子串，拼接起来，求所有选法得到的序列的权值之和。

如果一个序列能通过多种方法被选择出来，那么计算多次。

本题带修改操作，格式请参考输入格式。

由于结果可能过大，请输出答案 $\bmod 19260817$ 的结果。

## 说明/提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477( partially uploaded )

$1 \leq n,m,len_i \leq 10^5$，序列中的元素均为 $32$ 位整型数，$\sum len_i \leq 10^5$。

共 $50$ 组数据。

## 样例 #1

### 输入

```
2 5
6 6
1 3 1 1 3 2 
2 3 3 2 1 1 
1 1 1
1 1 2
1 1 2
1 1 1
1 1 1```

### 输出

```
1158
1158
1168
1168
1158
1158```

# 题解

## 作者：诗乃 (赞：13)

简单容斥+毒瘤STL。

设长度为$n$的序列共有$G(n)$个子区间，则：

$$G(n)=\frac{n(n+1)}{2}$$

考虑分开计算每个颜色的贡献，利用补集转化的思想，设颜色$c$的总贡献为$res_c$，则：

$$res_c=\prod_{i=1}^{n}G(len_i)-\prod_{i=1}^{n}ans_{c,i}$$

其中$ans_{c,i}$为第$i$个序列中**不包含**颜色$c$的子区间个数。

考虑如何求出$ans_{c,i}$。不难发现，使一个子区间不包含某种颜色，则这个区间的左右端点一定在相邻两个颜色$c$之间。可以看成一个颜色将某个序列分成$m$个长度分别为$l_i$的子序列，则可以得出：

$$ans_{c,i}=\sum_{i=1}^{m}G(l_i)$$

对于每个颜色在每个序列内的出现位置维护$set$即可求出$ans_{c,i}$。

考虑如何统计总答案，设总答案为$ANS$，颜色数量为$cntcol$则：

$$ANS=\sum_{i=1}^{cntcol}res_c=\sum_{i=1}^{cntcol}\prod_{i=1}^{n}G(len_i)-\sum_{i=1}^{cntcol}\prod_{i=1}^{n}ans_{c,i}$$

维护$all_c=\prod_{i=1}^{n}ans_{c,i}$，$S=\sum_{i=1}^{cntcol}all_c$即可求出答案。

考虑如何进行修改。将某个位置的颜色修改可以看成在某颜色的$set$中删除一个位置后在另一个颜色的$set$中添加一个位置。

考虑添加/删除一个位置产生的影响。实质上是将一段划分出的子序列分成两段或将两段合成一段，直接维护统计答案即可。

细节：维护过程中可能存在$all_c$变成$0$又变回不为$0$的情况，容易出错，需要特别维护。将位置$-1$和$len_i$插入所有颜色的$set$中可以规避掉很多细节。

代码：

```cpp
#include <bits/stdc++.h>
#define sIT set<int>::iterator
using namespace std;
const int MAXN = 200050, P = 19260817, inv2 = 9630409;
int read() {
	char ch; int x; while(ch = getchar(), ch < '!'); x = ch - 48;
	while(ch = getchar(), ch > '!') x = (x << 3) + (x << 1) + ch - 48; return x;
}
int inv(int a) {
	if(a == 0) return 1;
	int b = P-2, res = 1;
	for(; b; a = 1ll*a*a%P, b >>= 1) if(b&1) res = 1ll*res*a%P;
	return res;
}
int G(int _n) {return 1ll*_n*(_n+1)%P*inv2%P;}
struct Z {
	int p, c;
	bool operator < (const Z &b) const {
		return p == b.p ? c < b.c : p < b.p;
	}
};
map <Z, int> id; map <int, int> idc;
int n, m, len[MAXN], sigma, _ans[MAXN], all[MAXN], S, piL, cnt, cntcol, _0[MAXN], _all[MAXN];
bool __0[MAXN];
vector <int> a[MAXN]; set <int> s[MAXN];
void modify(int p, int _n, int c, int tp) {
	bool tmp = __0[p];
	S = (S + P - all[c]) % P;
	if(!tmp) _all[c] = 1ll*_all[c]*inv(_ans[p])%P;
	if(!tmp) all[c] = 1ll*all[c]*inv(_ans[p])%P;
	if(!tp) _ans[p] = (_ans[p] - G(_n) + P) % P;
	else _ans[p] = _ans[p] + G(_n) % P;
	if(_ans[p]) _all[c] = 1ll*_all[c]*_ans[p]%P;
	if(!_ans[p] && !tmp) __0[p] = 1, ++_0[c];
	if(_ans[p] && tmp) __0[p] = 0, --_0[c];
	all[c] = 1ll*all[c]*_ans[p]%P;
	if(!_0[c]) all[c] = _all[c];
	S = (S + all[c]) % P;
}
void del(int p, int t) {
	int c = a[p][t], u = id[(Z){p, c}];
	sIT it = s[u].lower_bound(t), itl, itr;
	itl = (--it)++; itr = (++it)--;
	modify(u, (*itr)-(*itl)-1, c, 1);
	modify(u, (*it)-(*itl)-1, c, 0);
	modify(u, (*itr)-(*it)-1, c, 0);
	s[u].erase(it);
}
void add(int p, int t) {
	int c = a[p][t], u = id[(Z){p, c}];
	sIT itr = s[u].upper_bound(t), itl;
	itl = (--itr)++;
	modify(u, t-(*itl)-1, c, 1);
	modify(u, (*itr)-t-1, c, 1);
	modify(u, (*itr)-(*itl)-1, c, 0);
	s[u].insert(t);
}
void getans() {
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < len[i]; ++j)
			add(i, j);
}
void update(int x, int y, int k) {del(x, y); a[x][y] = k; add(x, y);}
int main() {
	n = read(); m = read(); piL = 1;
	for(int i = 1; i <= n; ++i) len[i] = read(), piL = 1ll*piL*G(len[i])%P;
	for(int i = 1; i <= n; ++i)
		for(int x, j = 0; j < len[i]; ++j) {
			x = read();
			if(!idc[x]) {
				sigma = (sigma + piL) % P;
				idc[x] = ++cntcol;
				_all[cntcol] = all[cntcol] = piL; S = (S + all[cntcol]) % P;
			} x = idc[x];
			Z t; t = (Z) {i, x};
			if(!id[t]) {
				id[t] = ++cnt;
				s[cnt].insert(-1); s[cnt].insert(len[i]);
				_ans[cnt] = G(len[i]);
			}
			a[i].push_back(x);
		}
	getans();
	printf("%d\n", (sigma+P-S)%P);
	for(int x, y, k; m--; ){
		x = read(); y = read(); k = read();
		if(!idc[k]) {
			sigma = (sigma + piL) % P;
			idc[k] = ++cntcol;
			_all[cntcol] = all[cntcol] = piL; S = (S + all[cntcol]);
		} k = idc[k];
		Z t; t = (Z) {x, k};
		if(!id[t]) {
			id[t] = ++cnt;
			s[cnt].insert(-1); s[cnt].insert(len[x]);
			_ans[cnt] = G(len[x]);
		}
		update(x, y-1, k);
		printf("%d\n", (sigma+P-S)%P);
	}
}

```

---

## 作者：cyfff (赞：8)

一个目前最优解的权值树状数组做法。

首先发现贡献可以对每个数字分开来考虑。

要求包含一个数字的区间数量，直接容斥成总方案数减去不包含的方案数。

$ans_i=\prod \frac{len \times (len-1)}{2}- \prod w_{i,j}$

其中 $w_{i,j}$ 表示第 $j$ 行不包含第 $i$ 个数字的方案数。

假如第 $j$ 行的第 $k$ 个数字由非数字 $i$ 变为数字 $i$，且 $k$ 前的第一个数字 $i$ 位置为 $u$，$k$ 后的第一个数字 $i$ 位置为 $v$，则有 $w_{i,j} \leftarrow  w_{i,j} -(v-k) \times (k-u)$，删去数字 $i$ 则相反。

于是对于每个 $i$ 执行与数字 $i$ 有关的每一个操作，利用权值树状数组可以简单维护前后为 $i$ 的第一个位置。

写代码时需要对数字和数字出现位置进行两次离散化。

数据可能出现 $w_{i,j}=0$ 的情况，可以维护一个变量表示 $\prod w_{i,j} $ 乘了几次 $0$。

```cpp
#include<bits/stdc++.h>
#define ri register int
#define L(x) lower_bound(A+1,A+1+cn,x)-A
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int rd(){
    char c=getchar();int x=0;
    for(;!isdigit(c);c=getchar());
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    return x;
}
typedef long long LL;
const int N=300005,p=19260817;
int n,m,x[N],y[N],z[N],cn,cnt,s[N],q[N],tr[N],A[N],f[N];LL w[N],W,WW,nw=1;
struct nd{int x,u,y,z;};pair<int,int>a[N];
vector<nd>g[N];vector<int>vc[N];
inline LL qp(LL x,int y){LL z=1;for(;y;y>>=1,x=x*x%p)if(y&1)z=z*x%p;return z;}
inline void add(int x,int y){for(;x<=cnt;x+=x&-x)tr[x]+=y;}
inline int qr(int x){ri y=0;for(;x;x-=x&-x)y+=tr[x];return y;}
inline int ask(int x){
	ri u=0,v=0,p=0,q=0;
	for(ri i=18;i>=0;--i)
	if((u=p+(1<<i))<=cnt&&(v=q+tr[u])<x)p=u,q=v;
	return p+1;
}
signed main(){
	n=rd();m=rd();
	for(ri i=1;i<=n;++i)s[i]=rd();
	for(ri i=1;i<=n;++i)for(ri j=1;j<=s[i];++j)vc[i].push_back(A[++cn]=rd());
	for(ri i=1;i<=m;++i)x[i]=rd(),y[i]=rd(),A[++cn]=z[i]=rd();
	sort(A+1,A+1+cn);cn=unique(A+1,A+1+cn)-A-1;
	for(ri i=1,x;i<=n;++i)for(ri j=1;j<=s[i];++j)
	{g[L(vc[i][j-1])].push_back((nd){i,j,0,1});}
	for(ri i=1;i<=m;++i)if(vc[x[i]][y[i]-1]!=z[i]){
		g[L(vc[x[i]][y[i]-1])].push_back((nd){x[i],y[i],i,0});
		g[L(z[i])].push_back((nd){x[i],y[i],i,1});
		vc[x[i]][y[i]-1]=z[i];
	}
	for(ri i=1;i<=n;++i)for(ri j=1;j<=s[i];++j)
	g[L(vc[i][j-1])].push_back((nd){i,j,m+1,0});
	for(ri i=1;i<=n;++i)w[i]=1ll*s[i]*(s[i]+1)/2%p,nw=nw*w[i]%p;
	for(ri i=1;i<=cn;++i){
		cnt=0;for(auto j:g[i])a[++cnt]={j.x,j.u};
		sort(a+1,a+1+cnt);cnt=unique(a+1,a+1+cnt)-a-1;
		ri zs=0,ZS=0,X,CN=0;W=nw;
		for(auto j:g[i])if(j.z){
			X=j.x;ri J=lower_bound(a+1,a+1+cnt,make_pair(X,j.u))-a;
			ri A=qr(J),AA=0;if(A)AA=ask(A);
			if(!AA||a[AA].first!=X)AA=0;else AA=a[AA].second;
			ri B=CN,BB=0;if(B!=A)BB=ask(A+1);
			if(!BB||a[BB].first!=X)BB=s[X]+1;else BB=a[BB].second;
			WW=W;zs=ZS;
			if(!w[X])--zs;else WW=WW*qp(w[X],p-2)%p;
			w[X]+=p-(j.u-AA)*(BB-j.u)%p;if(w[X]>=p)w[X]-=p;
			if(!w[X])++zs;else WW=WW*w[X]%p;
			(f[j.y]+=(ZS?0:W)+p-(zs?0:WW))%=p;W=WW;ZS=zs;add(J,1);++CN;
		}else{
			X=j.x;ri J=lower_bound(a+1,a+1+cnt,make_pair(X,j.u))-a;add(J,-1);--CN;
			ri A=qr(J),AA=0;if(A)AA=ask(A);
			if(!AA||a[AA].first!=X)AA=0;else AA=a[AA].second;
			ri B=CN,BB=0;if(B!=A)BB=ask(A+1);
			if(!BB||a[BB].first!=X)BB=s[X]+1;else BB=a[BB].second;
			WW=W;zs=ZS;
			if(!w[X])--zs;else WW=W*qp(w[X],p-2)%p;
			w[X]+=(j.u-AA)*(BB-j.u)%p;if(w[X]>=p)w[X]-=p;
			if(!w[X])++zs;else WW=WW*w[X]%p;
			(f[j.y]+=(ZS?0:W)+p-(zs?0:WW))%=p;W=WW;ZS=zs;
		}
	}
	for(ri i=0;i<=m;++i){
		if(i){f[i]+=f[i-1];if(f[i]>=p)f[i]-=p;}
		printf("%d\n",f[i]);
	}
	return 0;
}

---

## 作者：wwwwwza (赞：5)

思路不难，细节有点多。

正难则反，对于每个数 $x$，考虑什么时候没有贡献。当每个序列都没选到 $x$ 的时候才会有贡献，用 set 维护每一个序列中数值为 $x$ 的下标。

注意判一下一个序列都是一种数值的情况。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
const int mod=19260817;
int n,m,len[N],x,y,z,idx=0,tot=0,sum=1,ans=0;
int w[N];
map<int,int>mp[N],res,zero;
set<int>s[N];
vector<int>g[N],num[N],ve;
int ksm(int a,int b){
	int sum=1;
	while(b){
		if(b&1)sum=sum*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return sum;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&len[i]);
		sum=sum*(((len[i]+1)*len[i]/2)%mod);
		sum%=mod;
	}
	for(int i=1;i<=n;i++){
		g[i].push_back(0);
		for(int j=1;j<=len[i];j++){
			scanf("%lld",&x);
			if(!res[x]){
				res[x]=sum;
				ve.push_back(x);
			}
			if(!mp[i][x]){
				mp[i][x]=++idx;
				num[i].push_back(x);
			}
			s[mp[i][x]].insert(j);
			g[i].push_back(x);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<num[i].size();j++){
			res[num[i][j]]=res[num[i][j]]*ksm(((len[i]+1)*len[i]/2)%mod,mod-2)%mod;
			int pos=mp[i][num[i][j]],lst=0;
			for(set<int>::iterator it=s[pos].begin();it!=s[pos].end();it++){
				int cnt=*it-lst-1;
				lst=*it;
				w[pos]+=cnt*(cnt+1)/2;
				w[pos]%=mod;
			}
			int cnt=len[i]-lst;
			w[pos]+=cnt*(cnt+1)/2;
			w[pos]%=mod;
			if(w[pos]==0)zero[num[i][j]]++;
			else res[num[i][j]]*=w[pos],res[num[i][j]]%=mod;
		}
	}
	for(int i=0;i<ve.size();i++){
		ans=ans+sum-res[ve[i]]*(zero[ve[i]]==0)+mod;
		ans%=mod;
	}
	printf("%lld\n",ans);
	while(m--){
		scanf("%lld%lld%lld",&x,&y,&z);
		if(g[x][y]==z){
			printf("%lld\n",ans);
			continue;
		}
		int pos=mp[x][g[x][y]];
		set<int>::iterator it=s[pos].lower_bound(y);
		set<int>::iterator ii=s[pos].end();ii--;
		int l,r;
		if(it!=s[pos].begin()){
			it--;
			l=*it;
			it++;
		}else l=0;
		if(it!=ii){
			it++;
			r=*it;
			it--;
		}else r=len[x]+1;
		s[pos].erase(y);
		
		ans-=(sum-res[g[x][y]]*(zero[g[x][y]]==0));
		ans=(ans+mod)%mod;
		if(w[pos]==0)zero[g[x][y]]--;
		else res[g[x][y]]=res[g[x][y]]*ksm(w[pos],mod-2)%mod;
		w[pos]=w[pos]-(y-l-1)*(y-l)/2-(r-y-1)*(r-y)/2+(r-l-1)*(r-l)/2;
		if(w[pos]==0)zero[g[x][y]]++;
		else res[g[x][y]]=res[g[x][y]]*w[pos]%mod;
		ans+=(sum-res[g[x][y]]*(zero[g[x][y]]==0));
		ans=(ans+mod)%mod;
		
		if(!res[z]){
			res[z]=sum;
			ve.push_back(z);
		}
		if(!mp[x][z]){
			mp[x][z]=++idx;
			w[mp[x][z]]=((len[x]+1)*len[x])/2;
		}
		g[x][y]=z;
		pos=mp[x][z];
		s[pos].insert(y);
		it=s[pos].lower_bound(y);
		ii=s[pos].end();ii--;
		if(it!=s[pos].begin()){
			it--;
			l=*it;
			it++;
		}else l=0;
		if(it!=ii){
			it++;
			r=*it;
			it--;
		}else r=len[x]+1;
		ans-=(sum-res[g[x][y]]*(zero[g[x][y]]==0));
		ans=(ans+mod)%mod;
		if(w[pos]==0)zero[g[x][y]]--;
		else res[g[x][y]]=res[g[x][y]]*ksm(w[pos],mod-2)%mod;
		w[pos]=w[pos]+(y-l-1)*(y-l)/2+(r-y-1)*(r-y)/2-(r-l-1)*(r-l)/2;
		if(w[pos]==0)zero[g[x][y]]++;
		else res[g[x][y]]=res[g[x][y]]*w[pos]%mod;
		ans+=(sum-res[g[x][y]]*(zero[g[x][y]]==0));
		ans=(ans+mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

```
哥哥的身体浮在空中…

我无言地跳了出去。

啊啊…是这样啊…

由岐姐也是这种心情啊…

并没有什么道理可言…

只是因为喜欢的人向着天空跳下去了…

我想要抓住那个身体…

我——
```         

素晴日~~         

-----------------------------------------

其实想到容斥算是一道很简单的题。            

请在阅读时区分“序列”和“生成序列”两个概念。

如果正着算估计要对每个序列的颜色各开一棵平衡树然后区间乘维护一堆东西，又难写又难调建议不要轻易尝试。               

对于这种计数题，我们首先考虑每种状态的贡献是由什么组成。很显然的是，一种状态最后的总贡献由生成序列中的每一种颜色贡献，这是一种很套路的计数模型，我们直接考虑每种颜色对所有生成序列的贡献。          

接着我们发现其实正着求这东西很困难，毕竟这东西不是可以直接由排列组合可以得出来的，所以我们考虑用容斥来算这东西。我们维护当前总的情况中有多少种生成序列序列里面，颜色 $i$ 对其没有贡献，记为 $mul_i$ ，很显然的是最后总的生成序列数减去 $mul_i$ 就是一种颜色的所有贡献次数，答案即是每种颜色的总贡献次数。            

很显然我们一次单点修改只会修改两种颜色的总贡献次数，所以直接暴力改这两种颜色的总贡献即可。根据乘法原理，我们知道一种颜色的 $mul_i$ 是所有序列中不包含颜色 $i$ 的子串的个数之积，记一个序列 $x$ 中不包含颜色 $i$ 的子串数量为 $sum_{x,i}$ ，那么可以将 $mul_i$ 用数学公式表达成 $mul_i = \prod_{x = 1} ^ n sum_{x,i}$ ，由于一次只会动一个序列的两种颜色，所以我们直接暴力修改这两种颜色对应的 $sum$ 。            

然后你就发现这东西开始套路起来了，我们直接维护每个序列中颜色 $i$ 的一个位置关系，这个开 set 就好了，然后 $sum_{x,i}$ 的值就是任意的两个离得最近的颜色位置中间可以选的子串个数之和，这个也可以在插入/删除时大常数暴力维护，接着我们顺便修一下 $mul$ 就可以解决这道题目。            

是不是感觉很简单？然而实现细节是真的多，调了我一晚上……         

首先我们要考虑一下我们代码的核心，维护每个序列中颜色 $i$ 位置关系的 set 我们可以直接这么开：          

```cpp
map<int,set<int> > mp[100005];
```       

~~然后实现起来就不用离散化了，典型的用常数换代码实现~~                   

接着我们需要注意你在维护 $mul$ 时可能碰到当前的 $mul$ 为 $0$ 但是我们修了一个 $sum$ 之后你这个 $mul$ 要变回去却变不回去的情况……我的办法是，直接把 $mul$ 拆成两个数组一部分维护 $0$ 的情况一部分维护非 $0$ 的情况。           

然后注意给之前没有出现过的颜色的 $sum$ 和 $mul$ 赋一下值。

其他比较重要的实现细节其实也没太多了，但是小细节很多，实现时候小心一下。              

```cpp
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int mod = 19260817;
const int Len = 2e5 + 5;
map<int,set<int> > mp[Len];
set<int>::iterator it,itt;
map<int,long long> mul,mul0,sum[Len],flag,frag,lst;
map<int,long long>::iterator mpit;
long long All,Ans,pre[Len];
inline long long qpow(long long a,long long b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1) res = res * a % mod;
		a = 1LL * a * a % mod;
		b = b >> 1;
	}
	return res;
}
int n,m,len[Len];
vector<int> v[Len];
inline long long qs(long long x){return 1LL * x * (x + 1) / 2 % mod;}
inline int Zero(int x){return (x != 0) ? 0 : 1;}
inline long long Mul(int x){return mul[x] * Zero(mul0[x]) % mod;}
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&len[i]);
	All = 1;
	pre[0] = 1;
	for(int i = 1 ; i <= n ; i ++) 
	{
		All = All * qs(len[i]) % mod;
		pre[i] = All;
		v[i].push_back(0);
		for(int j = 1 ; j <= len[i] ; j ++) 
		{
			int x;scanf("%lld",&x);
			v[i].push_back(x);
			mp[i][x].insert(j);
		}
		for(int j = 1 ; j <= len[i] ; j ++) 
		{
			int l , r = j - 1;
			it = mp[i][v[i][j]].lower_bound(j);
			if(it == mp[i][v[i][j]].begin()) l = 1;
			else itt = it , l = (*-- itt) + 1;
			if(l <= r) sum[i][v[i][j]] += qs(r - l + 1) , sum[i][v[i][j]] %= mod;
			if(it == -- mp[i][v[i][j]].end()) sum[i][v[i][j]] += qs(len[i] - j) , sum[i][v[i][j]] %= mod;
		}
		flag.clear();
		for(int j = 1 ; j <= len[i] ; j ++) 
		{
			if(flag[v[i][j]]) continue;
			if(!frag[v[i][j]])
			{
				frag[v[i][j]] = 1;
				mul[v[i][j]] = 1;
			}
			flag[v[i][j]] = 1;
			if(sum[i][v[i][j]]) mul[v[i][j]] = mul[v[i][j]] * sum[i][v[i][j]] % mod;
			else mul0[v[i][j]] ++;
			mul[v[i][j]] = mul[v[i][j]] * qpow(pre[lst[v[i][j]]] , mod - 2) % mod * pre[i - 1] % mod;
			lst[v[i][j]] = i;
		}
	}
	for(mpit = mul.begin() ; mpit != mul.end() ; mpit ++) 
	{
		int idx = mpit -> first;
		mul[idx] = mul[idx] * qpow(pre[lst[idx]] , mod - 2) % mod * pre[n] % mod;
	}
	for(mpit = mul.begin() ; mpit != mul.end() ; mpit ++) 
	{
		long long nums = mpit -> second;int idx = mpit -> first;
		nums = nums * Zero(mul0[idx]);
		Ans += (All - nums + mod) % mod , Ans %= mod;
	}
	printf("%lld\n",Ans);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y,z,L,R;scanf("%lld %lld %lld",&x,&y,&z);
		Ans -= (All - Mul(v[x][y]) + mod) % mod , Ans %= mod;
		if(sum[x][v[x][y]]) mul[v[x][y]] = mul[v[x][y]] * qpow(sum[x][v[x][y]] , mod - 2) % mod;
		else mul0[v[x][y]] --;
		it = mp[x][v[x][y]].lower_bound(y);
		int l,r = y - 1;
		if(it == mp[x][v[x][y]].begin()) L = l = 1;
		else itt = it , L = l = (*-- itt) + 1;
		if(l <= r) sum[x][v[x][y]] += mod - qs(r - l + 1) , sum[x][v[x][y]] %= mod;
		l = y + 1;
		if(it == -- mp[x][v[x][y]].end()) R = r = len[x];
		else itt = it , R = r = (*++ itt) - 1;
		if(l <= r) sum[x][v[x][y]] += mod - qs(r - l + 1) , sum[x][v[x][y]] %= mod;
		sum[x][v[x][y]] += qs(R - L + 1) , sum[x][v[x][y]] %= mod;
		if(sum[x][v[x][y]]) mul[v[x][y]] = mul[v[x][y]] * sum[x][v[x][y]] % mod;
		else mul0[v[x][y]] ++;
		Ans += (All - Mul(v[x][y]) + mod) % mod , Ans %= mod;
		mp[x][v[x][y]].erase(y);
		v[x][y] = z;
		if(frag[v[x][y]]) Ans -= (All - Mul(v[x][y]) + mod) % mod , Ans %= mod;	
		if(!mp[x][z].size()) 
		{
			sum[x][z] = qs(len[x]);	
			mul[z] = mul[z] * qpow(qs(len[x]) , mod - 2) % mod;
		}
		else 
		{
			if(sum[x][v[x][y]]) mul[z] = mul[z] * qpow(sum[x][v[x][y]] , mod - 2) % mod;
			else mul0[z] ++;
		}
		mp[x][v[x][y]].insert(y);
		r = y - 1;
		it = mp[x][v[x][y]].lower_bound(y);
		if(it == mp[x][v[x][y]].begin()) L = l = 1;
		else itt = it , L = l = (*-- itt) + 1;
		if(l <= r) sum[x][v[x][y]] += qs(r - l + 1) , sum[x][v[x][y]] %= mod;
		l = y + 1;
		if(it == -- mp[x][v[x][y]].end()) R = r = len[x];
		else itt = it , R = r = (*++ itt) - 1;
		if(l <= r) sum[x][v[x][y]] += qs(r - l + 1) , sum[x][v[x][y]] %= mod;
		sum[x][v[x][y]] += mod - qs(R - L + 1) , sum[x][v[x][y]] %= mod;
		if(!frag[v[x][y]]) 
		{
			mul[v[x][y]] = All * qpow(qs(len[x]) , mod - 2) % mod;
			frag[v[x][y]] = 1;
		}
		if(sum[x][v[x][y]]) mul[v[x][y]] = mul[v[x][y]] * sum[x][v[x][y]] % mod;
		else mul0[v[x][y]] ++;
		Ans += (All - Mul(v[x][y]) + mod) % mod , Ans %= mod;
		printf("%lld\n",(Ans + mod) % mod);
	}
	return 0;
}
```

---

## 作者：foreverlasting (赞：2)

[题面](https://www.lydsy.com/JudgeOnline/problem.php?id=5395)

STL+容斥

好像也没什么好说的吧，就是一道纯粹的细节题，思路什么的还是很普通的吧。
考虑对颜色分开考虑贡献。补集转化为颜色不贡献的所有区间。即每个序列颜色的相邻位置中选区间。再把每个序列的答案乘起来。这些都可以用STL维护。

$S(set)$维护一下每种颜色的位置，$tj(map)$维护一下每种颜色在每一个序列的贡献，$vec(map)$维护一下每一个序列每一个位置所对应的编号，加上容斥原理的思想，每次修改前先去掉这个位置的贡献，再加上这个位置的贡献，就好了。就是细节多，其他都好......(调了我两个小时）

update:好像说要多一点细节的描述。那就写一下吧。每次修改$tj$的时候，如果$tj$大于0，则用$ret$数组去把这一种颜色的总贡献乘进去，如果等于0，说明这一个位置颜色不存在贡献，那我们就需要在统计最终答案的时候减去这种颜色的贡献。修改的时候，我们也是同样的做法。修改$tj$，查看是否有贡献，再相应地修改答案。然后就好了。

code:
```
//2018.9.18 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register LL
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline LL read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline LL _abs(const res &x){
    return x>0?x:-x;
}
inline LL _max(const res &x,const res &y){
    return x>y?x:y;
}
inline LL _min(const res &x,const res &y){
    return x<y?x:y;
}
const LL kcz=19260817,N=2e5+10;
namespace MAIN{
    LL n,m;
    LL len[N],INV,tot;
    LL s=1;
    LL fac[N],inv[N];
    inline LL qpow(res x,res y){
        res Ans=1;
        while(y){
            if(y&1)Ans=Ans*x%kcz;
            x=x*x%kcz,y>>=1;
        }
        return Ans%kcz;
    }
    map<LL,LL> pos;
    set<LL> S[N];
    LL num;
    struct P{
        LL x,y,va;
        P() {}
        P(res x,res y,res va):x(x),y(y),va(va) {}
    }a[N];
    inline LL calc(const res &x){
        return x*(x+1)/2%kcz;
    }
    LL ans,ret[N];
    map<LL,LL> tj[N];
    inline void add(res &x,const res &y){
        x+=y;
        x>=kcz?x-=kcz:1;
    }
    LL qaq[N];
    typedef pair<LL,LL> Pair;
#define mp make_pair
    map<Pair,LL> vec;
    set<LL>::iterator it,l,r;
    inline void pre(){
        fac[0]=inv[0]=1;
        for(res i=1;i<=n;i++){
            fac[i]=calc(len[i])*fac[i-1]%kcz;
            inv[i]=qpow(fac[i],kcz-2);
            for(res j=1;j<=len[i];j++){
                a[++tot]=P(i,j,read());
                if(!pos[a[tot].va])pos[a[tot].va]=++num;
                a[tot].va=pos[a[tot].va];
                S[a[tot].va].insert(tot);
                vec[mp(i,j)]=tot;
            }
        }
        for(res i=1;i<=num;i++){
            res x=0,y=0;
            ret[i]=1;
            for(it=S[i].begin();it!=S[i].end();it++){
                res p=*it;
                if(!x)ret[i]=ret[i]*fac[a[p].x-1]%kcz,add(tj[i][a[p].x],calc(a[p].y-1));
                else if(x==a[p].x)add(tj[i][a[p].x],calc(a[p].y-y-1));
                else {
                    add(tj[i][x],calc(len[x]-y));
                    if(tj[i][x])ret[i]=ret[i]*tj[i][x]%kcz;
                    else qaq[i]++;
                    ret[i]=ret[i]*fac[a[p].x-1]%kcz*inv[x]%kcz;
                    add(tj[i][a[p].x],calc(a[p].y-1));
                }
                x=a[p].x,y=a[p].y;
            }
            //这里有三类，注意分类
            add(tj[i][x],calc(len[x]-y));
            if(tj[i][x])ret[i]=ret[i]*tj[i][x]%kcz;
            else qaq[i]++;
            ret[i]=ret[i]*fac[n]%kcz*inv[x]%kcz;
            add(ans,s-(qaq[i]?0:1)*ret[i]);
        }
        ans=(ans%kcz+kcz)%kcz;
        printf("%lld\n",ans);
    }
    inline void modify(const res &c,const res &x,const res &y,const res &p,const res &bol){
        res L,R;
        l=S[c].lower_bound(p),r=l;
        if(l==S[c].begin())L=0;
        else{
            l--,L=*l;
            if(a[L].x!=x)L=0;
            else L=a[L].y;
        }
        r++;
        if(r==S[c].end())R=len[x];
        else{
            R=*r;
            if(a[R].x!=x)R=len[x];
            else R=a[R].y-1;
        }
        if(bol&&R==len[x]&&!L)tj[c][x]=calc(len[x]);//如果是增加的时候，还要注意一下tj的初始化问题
        ans-=s-(qaq[c]?0:1)*ret[c];
        if(tj[c][x])ret[c]=ret[c]*qpow(tj[c][x],kcz-2)%kcz;
        else qaq[c]--;
        tj[c][x]+=(bol?-1:1)*(calc(R-L)-calc(R-y)-calc(y-L-1));
        if(tj[c][x])ret[c]=ret[c]*tj[c][x]%kcz;
        else qaq[c]++;
        ans+=s-(qaq[c]?0:1)*ret[c];
    }
    inline void solve(){
        res x=read(),y=read(),w=read(),p=vec[mp(x,y)],c=a[p].va;
        modify(c,x,y,p,0);
        S[c].erase(p);
        if(!pos[w])pos[w]=++num,ret[num]=fac[n];//修改颜色的时候先看看原本有没有这种颜色
        w=pos[w];
        a[p].va=w;
        S[w].insert(p);
        modify(w,x,y,p,1);
        ans=(ans%kcz+kcz)%kcz;
        printf("%lld\n",ans);
    }
    inline void MAIN(){
        INV=qpow(2,kcz-2);
        n=read(),m=read();
        for(res i=1;i<=n;i++)len[i]=read(),s=s*len[i]%kcz*(len[i]+1)%kcz*INV%kcz;
        pre();
        while(m--)solve();
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：Jμdge (赞：2)

Ynoi 中少见的不卡常题呢....虽说有 50 个数据点...

果然还是道好题

# noteskey

总之就是补集转化的思想，算出每种颜色选点的总方案减去不可行方案（就是不包含 该种颜色的点的区间选取方案）就是每种颜色的贡献

然后就是考虑每种颜色把一个区间分成若干份，那么我们只需要算出这若干份区间内的子区间个数就行了

具体操作也就是考虑每次加入一个点后会减去原来区间的贡献然后加上新的两个区间的贡献

那么删除点也是同理

复杂度 $(n+m)log(n+m)$ ，说白了就是 $O(n   ~log  ~n)$


# watch out

要注意的就是这里需要离散化，当然修改操作中的值也是要加进离散化的数组中的，具体离散是开数组还是用 vector 就看喜好了...


# code 

代码还是比较短的，Ynoi 里这么短的代码都没有多少的...


```cpp
//by Judge
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define Rg register
#define Pi pair<int,int>
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define ll long long
using namespace std;
const int mod=19260817;
const int M=5e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int mul(int x,int y){return 1ll*x*y%mod;}
inline int dec(int x,int y){return x<y?x-y+mod:x-y;}
inline int inc(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline bool cmax(int& a,int b){return a<b?a=b,1:0;}
inline bool cmin(int& a,int b){return a>b?a=b,1:0;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int CCF=-1,Z;
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(int x,char chr='\n'){
    if(CCF>1<<20)Ot();if(x<0)sr[++CCF]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} int n,m,ans,Ynoi=1; arr L,R,pos,len,a,inv,LN,ept,P;
set<int> s[M]; vector<int> lr; map<Pi,int> gx;
struct opts{ int x,y,z; }q[M];
inline int C2(int x){return (1ll*x*(x-1)>>1)%mod;}
inline int INV(int x){return x<=5e5?inv[x]:mul(mod-mod/x,INV(mod%x));}
#define LL long long
#define pii Pi
#define md mod
inline void insert(int col,int x){
	int pre=*--s[col].lower_bound(x),suf=*s[col].upper_bound(x);
	cmax(pre,L[pos[x]]-1),cmin(suf,R[pos[x]]+1); Pi xb=Pi(pos[x],col);
	if(!gx.count(xb)) gx[xb]=C2(len[pos[x]]+1); int &v=gx[xb];
	ans=inc(ans,ept[col]?0:LN[col]),LN[col]=mul(LN[col],INV(v));
	v=inc(dec(v,C2(suf-pre)),inc(C2(x-pre),C2(suf-x)));
	if(v) LN[col]=mul(LN[col],v); else ++ept[col];
	ans=dec(ans,ept[col]?0:LN[col]),s[col].insert(x);
}
inline void erase(int col,int x){
	int pre=*--s[col].lower_bound(x),suf=*s[col].upper_bound(x);
	cmax(pre,L[pos[x]]-1),cmin(suf,R[pos[x]]+1); Pi xb=Pi(pos[x],col);
	if(!gx.count(xb)) gx[xb]=C2(len[pos[x]]+1); int& v=gx[xb];
	ans=inc(ans,ept[col]?0:LN[col]);
	if(!v) --ept[col]; else LN[col]=mul(LN[col],INV(v));
	v=dec(inc(v,C2(suf-pre)),inc(C2(x-pre),C2(suf-x))),LN[col]=mul(LN[col],v);
	ans=dec(ans,ept[col]?0:LN[col]),s[col].erase(x);
}
int main(){ n=read(),m=read(),inv[1]=1;
	fp(i,2,5e5) inv[i]=mul(mod-mod/i,inv[mod%i]);
	fp(i,1,n) len[i]=read(),L[i]=R[i-1]+1,R[i]=R[i-1]+len[i],
		Ynoi=mul(Ynoi,C2(len[i]+1)),P[i]=P[i-1]+len[i];
	fp(i,1,n) fp(j,L[i],R[i]) pos[j]=i,a[j]=read(),lr.push_back(a[j]);
	fp(i,1,m) q[i].x=read(),q[i].y=read(),q[i].z=read(),lr.push_back(q[i].z);
	sort(lr.begin(),lr.end()),lr.erase(unique(lr.begin(),lr.end()),lr.end());
	fp(i,0,lr.size()) s[i].insert(0),s[i].insert(R[n]+1),LN[i]=Ynoi;
	fp(i,1,R[n]) a[i]=lower_bound(lr.begin(),lr.end(),a[i])-lr.begin(),insert(a[i],i);
	for(Rg int i=(print(ans),1);i<=m;++i,print(ans)){ int id=P[q[i].x-1]+q[i].y;
		erase(a[id],id),insert(a[id]=lower_bound(lr.begin(),lr.end(),q[i].z)-lr.begin(),id);
	} return Ot(),0;
}
```







---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定 $n$ 个序列 $a_1,\cdots,a_n$，第 $i$ 个序列长度为 $l_i$。

有 $m$ 次询问，每次询问给出 $x,y,z$，表示 $a_{x,y}\gets z$。

在所有修改之前，以及每次修改之后，你需要输出：对于每一个序列选取一个子串，将所有子串拼接而成的序列的颜色数，称为这种选取方法的权值，你需要求出所有选取方法的权值之和。答案对 $19260817$ 取模。

$1\leq n,m,l_i\leq 10^5,1\leq \sum l_i\leq 10^5$。

## 思路

毁人心智的大型拆贡献题，个人感觉其实分类讨论成分不大。

首先离线离散化，然后考虑每一种颜色对答案的贡献。发现拼接而成的序列必须有这种颜色比较困难，正难则反，改为考虑必须没有这种颜色。

我们很容易列出对于某种颜色 $k$，拼接而成的序列必须没有这种颜色的方案数为 $\prod_i w(i,k)$，其中 $w(i,k)$ 表示从 $a_i$ 中选取一个子串，使得不出现 $k$ 的方案数。

然后考虑如何求出 $w(i,k)$，可以将 $a_i$ 中所有等于 $k$ 的元素取出来，这可以看成将序列分成了 $k+1$ 段，每一段（不包含断点）的子串数量之和就是答案。为了减少分类讨论，我们钦定 $0,l_i$ 总是断点，并且用 `set` 记录断点情况。

为了方便后面的修改，我们对于每一个序列 $a_i$，离线后处理出哪些颜色与它有关，也就是在某个时刻，序列 $a_i$ 中出现过这个颜色。然后对于所有与 $a_i$ 相关的颜色，将一个 `set` 关联到 $a_i$，表示对应颜色的断点情况（当然，为了方便快速找到这个 `set`，你可能需要用一个 `map`），由于这样的 `set` 最多只有 $O(m+\sum l_i)$ 个，所以开的下。

接着考虑如何处理修改，我们可以看成这个元素的贡献消失，然后加入新的点的贡献，这一部分非常简单，但是要注意细节，具体看代码。

你可能发现了，为了维护贡献的消失和新增，我们需要维护一个颜色的答案，而如果出现了一个序列全是某一种颜色，那么答案会为 $0$，这样后面的处理会出现问题。一种比较好的解决方法是维护每种颜色对应的贡献为 $0$ 的序列数量，具体可以参考代码中 `node` 的实现。

时间复杂度 $O(n\log n)$，默认 $n,m,\sum l_i$ 同阶。

## 代码

自认为写的挺清晰的，但是仍然有 3.8 KB：

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 19260817, inv2 = (mod + 1) >> 1;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

int fastpow(int x, int y){
    int ret = 1;
    for(;y;y>>=1,x=Mul(x, x)){ if(y & 1) ret = Mul(ret, x); }
    return ret;
}

struct node{
    int val, cnt;
    node() : val(1), cnt(0) {}
    void muls(int x){ !x ? ++cnt : val = Mul(val, x); }
    void divs(int x){ !x ? --cnt : val = Mul(val, fastpow(x, mod - 2)); }
    int operator()(){ return cnt ? 0 : val; }
};

const int N = 1e5 + 5;
int n, m, len[N], buf[N << 1];
node ans[N << 1];
vector<int> a[N];

struct opt{
    int a, b, x;
} opts[N];

vector<set<int>> col[N];
map<int,int> colp[N];
vector<int> f[N];

void create(int i, int x){
    colp[i][x] = col[i].size();
    col[i].push_back(set<int>());
    col[i].back().insert(0);
    col[i].back().insert(len[i] + 1);
}

int subs(int x){ return Mul(inv2, Mul(x, Add(x, 1))); }
int subs(int l, int r){ return subs(r - l + 1); }

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m; int tot = 0;
    for(int i=1;i<=n;i++) cin >> len[i], a[i].resize(len[i] + 1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len[i];j++) cin >> a[i][j], buf[++tot] = a[i][j];
    }
    for(int i=1;i<=m;i++) cin >> opts[i].a >> opts[i].b >> opts[i].x, buf[++tot] = opts[i].x;
    sort(buf + 1, buf + tot + 1);
    tot = unique(buf + 1, buf + tot + 1) - buf - 1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len[i];j++) a[i][j] = lower_bound(buf + 1, buf + tot + 1, a[i][j]) - buf;
    }
    for(int i=1;i<=m;i++) opts[i].x = lower_bound(buf + 1, buf + tot + 1, opts[i].x) - buf;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=len[i];j++){
            int x = a[i][j];
            if(!colp[i].count(x)) create(i, x);
            col[i][colp[i][x]].insert(j);
        }
    }
    for(int i=1;i<=m;i++){
        int a = opts[i].a, x = opts[i].x;
        if(!colp[a].count(x)) create(a, x);
    }
    int total = 1;
    for(int i=1;i<=n;i++) total = Mul(total, subs(len[i]));
    for(int i=1;i<=tot;i++) ans[i].muls(total);
    for(int i=1;i<=n;i++){
        f[i].resize(col[i].size());
        for(auto [c, j] : colp[i]){
            int tmp = 0;
            for(auto it1=col[i][j].begin(),it2=next(it1);it2!=col[i][j].end();it1++,it2++){
                int l = *it1, r = *it2;
                tmp = Add(tmp, subs(l + 1, r - 1));
            }
            f[i][j] = tmp;
            ans[c].divs(subs(len[i])), ans[c].muls(tmp);
        }
    }
    total = Mul(total, tot);
    for(int i=1;i<=tot;i++) total = Sub(total, ans[i]());
    cout << total << '\n';
    for(int i=1;i<=m;i++){
        int x = opts[i].a, y = opts[i].b, z = opts[i].x;
        int ori = a[x][y], pos = colp[x][ori];
        auto it = col[x][pos].find(y);
        auto pre = prev(it), nxt = next(it);
        total = Add(total, ans[ori]());
        ans[ori].divs(f[x][pos]);
        f[x][pos] = Sub(f[x][pos], subs(*pre + 1, *it - 1));
        f[x][pos] = Sub(f[x][pos], subs(*it + 1, *nxt - 1));
        f[x][pos] = Add(f[x][pos], subs(*pre + 1, *nxt - 1));
        ans[ori].muls(f[x][pos]);
        total = Sub(total, ans[ori]());
        col[x][pos].erase(it);
        pos = colp[x][z];
        total = Add(total, ans[z]());
        ans[z].divs(f[x][pos]);
        nxt = col[x][pos].upper_bound(y), pre = prev(nxt);
        f[x][pos] = Add(f[x][pos], subs(*pre + 1, y - 1));
        f[x][pos] = Add(f[x][pos], subs(y + 1, *nxt - 1));
        f[x][pos] = Sub(f[x][pos], subs(*pre + 1, *nxt - 1));
        ans[z].muls(f[x][pos]);
        total = Sub(total, ans[z]());
        col[x][pos].insert(y);
        a[x][y] = z;
        cout << total << '\n';
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Piwry (赞：1)

## 解析

不难发现每种颜色的贡献都是独立的；即我们可以分别计算每种颜色会在多少方案中出现，再把这些贡献加起来

直接计算每种颜色会在多少种方案中出现可能比较麻烦，我们考虑容斥；具体来说，设所有可能的方案 $S$，颜色 $c$ 不出现的方案数 $f(c)$，对每种颜色我们要求的值即为 $S-f(c)$。其中 $S$ 应为 $\prod\limits_{i=1}^n{h(len_i)}$（这里 $h(x)$ 指长度为 $x$ 的序列的子串选法个数，不难得到 $h(x)=\frac {x(x+1)} {2}$
），答案即为 $\sum{(S-f(c))}$

再考虑 $f(c)$ 怎么求。考虑序列 $i$ 中 $c$ 出现的每个位置 $\{p_k\}$，并额外添加两个位置 $p_s=0, p_t=len_i+1$ （即该序列的开始与末尾，为了方便后面的处理），则在序列 $i$ 中选择一个子串且该子串不包含 $c$ 的子串个数即为 $\sum {h(p_l-p_r)}$（这里 $p_r$ 是将 $\{p_k\}$ 排序后与 $p_l$ 相邻且大于 $p_l$ 的元素；$h(x)$ 见上），于是就有 $f(c)=\prod\limits_{i=1}^n\sum {h(p_l-p_r)}$

到这里题目就差不多做完了，不难发现上述的东西都可以用 `set` 什么的直接维护（包括修改操作）。但是实现的细节很多...例如 $\sum {h(p_l-p_r)}$ 可能为 $0$，于是更新 $f(c)$ 及答案时需要特判下，不能真的除/乘 $0$

剩下的就见代码及注释把 \fad

## CODE

```cpp
#include <cstdio>
#include <map>
#include <set>
#include <vector>
using std::map;
using std::set;
using std::vector;
using std::pair;
typedef pair<int, int> pad;

const int MAXN =1e5+20, M =19260817;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return x;
}

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

/*------------------------------Base------------------------------*/

inline void Plus(int &A, const int &B){
	A +=B;
	if(A >= M)
		A -=M;
}

inline void Minus(int &A, const int &B){
	A -=B;
	if(A < 0)
		A +=M;
}

inline int Minus2(int A, const int &B){
	A -=B;
	if(A < 0)
		A +=M;
	return A;
}

int Inv(int x){
	int ret =1;
	for(int k =M-2; k; k >>=1, x =1ll*x*x%M)
		if(k&1)
			ret =1ll*ret*x%M;
	return ret;
}

int sum_t[MAXN];

// 这里返回的位置下标和题解中的有些不太一样...相当于是将所有序列拼接成了一个序列 //
inline int get_pos(const int &i, const int &j){
	return sum_t[i-1]+2+j;
}

/*------------------------------Operation------------------------------*/

set<int> Set[MAXN<<1];
map<int, int> Col;
int Cnt_col;
/** Set[col_id] : 该颜色 (col_id) 的所有出现位置 //
 *  Col : 离散化颜色 //
 *  Cnt_col : 总颜色数 //
**/

int Ctrb[MAXN<<1], Cnt_zero[MAXN<<1];
map<int, int> Map_ctrb[MAXN<<1];
int Ctrb_All, Ans;
/** Ctrb[col_id] : 不包含该颜色 (col_id) 的方案数 //
 *  Cnt_zero[col_id] : 该颜色 (col_id) 存在某个序列满足要求的子串数为 0，统计这个 0 的个数 //
 *  Map_ctrb[col_id] : 每个序列不包含该颜色 (col_id) 的子串个数 //
 *  Ctrb_All : 总方案数 ( 不同区间的选法 ) //
 *  Ans : 就是答案 //
**/

inline void updata(const int &col_id, const int &pre, const int &now){
	Minus(Ans, Minus2(Ctrb_All, (Cnt_zero[col_id] == 0) ? Ctrb[col_id] : 0));
	
	if(pre == 0)
		--Cnt_zero[col_id];
	if(now == 0)
		++Cnt_zero[col_id];
	
	Ctrb[col_id] =1ll*Ctrb[col_id]*((pre == 0) ? 1 : Inv(pre))%M;
	Ctrb[col_id] =1ll*Ctrb[col_id]*((now == 0) ? 1 : now)%M;
	
	Plus(Ans, Minus2(Ctrb_All, (Cnt_zero[col_id] == 0) ? Ctrb[col_id] : 0));
}

void insert(const int &val, const int &i, const int &j){
	map<int, int>::iterator it =Col.find(val);
	if(it == Col.end()){
		++Cnt_col;
		it =(Col.insert(pad(val, Cnt_col))).first;
		Ctrb[Cnt_col] =Ctrb_All;
	}
	int cur =it->second, pos =get_pos(i, j);
	
	if(!Map_ctrb[cur].count(i)){
		Set[cur].insert(sum_t[i-1]+2);
		Set[cur].insert(sum_t[i]+1);
		
		int len =sum_t[i]-(sum_t[i-1]+2);
		Map_ctrb[cur].insert(pad(i, 1ll*len*(len+1)/2%M));
	}
	Set[cur].insert(pos);
	
	int posl =*(--Set[cur].lower_bound(pos)), posr =*(Set[cur].upper_bound(pos));
	int len1 =pos-posl-1, len2 =posr-pos-1, len3 =posr-posl-1;
	it =Map_ctrb[cur].find(i);
	
	// it->second : 该序列 (i) 不包含该颜色 (cur) 的子串个数 //
	
	int div =it->second;
	Minus(it->second, 1ll*len3*(len3+1)/2%M);
	Plus(it->second, 1ll*len1*(len1+1)/2%M);
	Plus(it->second, 1ll*len2*(len2+1)/2%M);
	int mul =it->second;
	updata(cur, div, mul);
}

void erase(const int &val, const int &i, const int &j){
	int cur =Col.find(val)->second, pos =get_pos(i, j);
	
	int posl =*(--Set[cur].lower_bound(pos)), posr =*(Set[cur].upper_bound(pos));
	int len1 =pos-posl-1, len2 =posr-pos-1, len3 =posr-posl-1;
	map<int, int>::iterator it =Map_ctrb[cur].find(i);
	
	// it->second : 该序列 (i) 不包含该颜色 (cur) 的子串个数 //
	
	int div =it->second;
	Minus(it->second, 1ll*len1*(len1+1)/2%M);
	Minus(it->second, 1ll*len2*(len2+1)/2%M);
	Plus(it->second, 1ll*len3*(len3+1)/2%M);
	int mul =it->second;
	updata(cur, div, mul);
	
	Set[cur].erase(pos);
}

/*------------------------------Main------------------------------*/

vector<vector<int> > col;

int main(){
	int n =read(), m =read();
	col.resize(n+1);
	sum_t[0] =-2;
	Ctrb_All =1;
	for(int i =1; i <= n; ++i){
		int t =read();
		col[i].resize(t+1, 0);
		Ctrb_All =1ll*Ctrb_All*(1ll*t*(t+1)/2%M)%M;
		sum_t[i] =t+sum_t[i-1]+2/*<- 每两个序列间插两个空位*/;
	}
	for(int i =1; i <= n; ++i)
		for(int j =1; j <= sum_t[i]-(sum_t[i-1]+2); ++j){
			int a =read();
			col[i][j] =a;
			insert(a, i, j);
		}
	// init done. //
	
	write(Ans), putchar('\n');
	for(int t =0; t < m; ++t){
		int x =read(), y =read(), z =read();
		erase(col[x][y], x, y);
		col[x][y] =z;
		insert(z, x, y);
		write(Ans), putchar('\n');
	}
}
```

---

## 作者：Purslane (赞：0)

# Solution

显然要把贡献拆开计算。

也就是你需要对每种颜色求出，有多少种选取方案使得包含了至少一个这种颜色。显然正难则反，求出有多少种选取方案这种颜色一个都没有包含。

那你有一个很基础的思路：对于每种颜色维护 $cnt_i$ 表示有多少种方案使得 $i$ 不出现，维护 $cnt_i$ 的和。

发现你对 $cnt_i$ 的操作只有单点乘除，所以直接维护线性数组即可？

注意到会出现乘除 $0$ 的情况。不过不太重要，你维护 $zero_i$ 表示 $i$ 处乘了多少个 $0$，$rcnt_i$ 表示不考虑 $0$ 时 $i$ 的答案（即 $cnt_i = rcnt_i [zero_i = 0]$）。

复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=19260817;
int n,m,len[MAXN],tot,lsh[MAXN],px[MAXN],py[MAXN],pv[MAXN];
vector<int> ar[MAXN];
map<pair<int,int>,set<int>> st;
map<pair<int,int>,int> val;
int rcnt[MAXN],zero[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>len[i];
	ffor(i,1,n) {
		ar[i].resize(len[i]+1);
		ffor(j,1,len[i]) cin>>ar[i][j],lsh[++tot]=ar[i][j];	
	}
	ffor(i,1,m) cin>>px[i]>>py[i]>>pv[i],lsh[++tot]=pv[i];
	sort(lsh+1,lsh+tot+1),tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	ffor(i,1,n) ffor(j,1,len[i]) ar[i][j]=lower_bound(lsh+1,lsh+tot+1,ar[i][j])-lsh;
	ffor(i,1,m) pv[i]=lower_bound(lsh+1,lsh+tot+1,pv[i])-lsh;
	ffor(i,1,n) ffor(j,1,len[i]) st[{i,ar[i][j]}].insert(j);
	int mul=1;
	ffor(i,1,n) mul=len[i]*(len[i]+1)/2%MOD*mul%MOD;
	ffor(i,1,tot) rcnt[i]=mul,zero[i]=0;
	for(auto pr:st) {
		int h=pr.first.first,col=pr.first.second,c=0;
		auto stx=pr.second;
		int lst=0;
		stx.insert(len[h]+1);
		for(auto id:stx) c=(c+(id-lst)*(id-lst-1)/2)%MOD,lst=id;
		if(c) rcnt[col]=rcnt[col]*qpow(len[h]*(len[h]+1)/2%MOD,MOD-2)%MOD*c%MOD,val[pr.first]=c;
		else rcnt[col]=rcnt[col]*qpow(len[h]*(len[h]+1)/2%MOD,MOD-2)%MOD,zero[col]++,val[pr.first]=0;
	}
	int sum=0;
	ffor(i,1,tot) sum=(sum+(zero[i]==0)*rcnt[i])%MOD;
	cout<<((tot*mul-sum)%MOD+MOD)%MOD<<'\n';
	ffor(i,1,m) {
		int mzx=ar[px[i]][py[i]],v=val[{px[i],mzx}];
		if(mzx==pv[i]) {cout<<((tot*mul-sum)%MOD+MOD)%MOD<<'\n';continue ;}
		sum=(sum-(zero[mzx]==0)*rcnt[mzx]-(zero[pv[i]]==0)*rcnt[pv[i]])%MOD;
		if(v==0) zero[mzx]--;
		else rcnt[mzx]=rcnt[mzx]*qpow(v,MOD-2)%MOD;
		
		auto it=st[{px[i],mzx}].find(py[i]);
		int lst=-1,nxt=-1;
		if(it!=st[{px[i],mzx}].begin()) lst=*prev(it);
		else lst=0;
		if(it!=--st[{px[i],mzx}].end()) nxt=*next(it);
		else nxt=len[px[i]]+1;
		
		val[{px[i],mzx}]=(val[{px[i],mzx}]-(py[i]-lst)*(py[i]-lst+1)/2)%MOD;
		val[{px[i],mzx}]=(val[{px[i],mzx}]-(nxt-py[i])*(nxt-py[i]+1)/2)%MOD;
		val[{px[i],mzx}]=(val[{px[i],mzx}]+(nxt-lst)*(nxt-lst+1)/2)%MOD;
		
		v=val[{px[i],mzx}];
		if(v==0) zero[mzx]++;
		else rcnt[mzx]=rcnt[mzx]*v%MOD;
		
		if(val.count({px[i],pv[i]})==0) val[{px[i],pv[i]}]=len[px[i]]*(len[px[i]]+1)/2%MOD;
		v=val[{px[i],pv[i]}];
		if(v==0) zero[pv[i]]--;
		else rcnt[pv[i]]=rcnt[pv[i]]*qpow(v,MOD-2)%MOD;
		
		it=st[{px[i],pv[i]}].lower_bound(py[i]);
		lst=-1,nxt=-1;
		if(it!=st[{px[i],pv[i]}].begin()) lst=*prev(it);
		else lst=0;
		if(it!=st[{px[i],pv[i]}].end()) nxt=*it;
		else nxt=len[px[i]]+1;
		
		val[{px[i],pv[i]}]=(val[{px[i],pv[i]}]+(py[i]-lst)*(py[i]-lst+1)/2)%MOD;
		val[{px[i],pv[i]}]=(val[{px[i],pv[i]}]+(nxt-py[i])*(nxt-py[i]+1)/2)%MOD;
		val[{px[i],pv[i]}]=(val[{px[i],pv[i]}]-(nxt-lst)*(nxt-lst+1)/2)%MOD;
		
		v=val[{px[i],pv[i]}];
		if(v==0) zero[pv[i]]++;
		else rcnt[pv[i]]=rcnt[pv[i]]*v%MOD;
		
		st[{px[i],mzx}].erase(py[i]),st[{px[i],pv[i]}].insert(py[i]);
		
		sum=(sum+(zero[mzx]==0)*rcnt[mzx]+(zero[pv[i]]==0)*rcnt[pv[i]])%MOD;
		ar[px[i]][py[i]]=pv[i];
		cout<<((tot*mul-sum)%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```

---

## 作者：Gmt丶FFF (赞：0)

很暴力的一道题。

首先我们可以想到用补集来计算一种数 $x$ 的贡献，即所有的情况减去序列中不含有 $x$ 的情况。

所有的情况即为 $\prod len_i$，不含有 $x$ 的情况即把每一个序列不含有 $x$ 的区间的个数求出来，再相乘即可。

我们插入一个数找到在它前后的与它相等的数，若在前面的数位置为 $l$，后面的为 $r$，当前位置为 $x$，那么区间个数就得减去 $(x-l)\times(r-x)$。初始的区间个数为 $\frac{len\times(len+1)}{2}$。

由于一个数的贡献值为所有序列的区间数相乘，所以我们在修改一个区间时，先除以我们要修改的序列原来的区间，再乘上现在的区间即可。

删去一个数同理，很明显，这个操作可以先离散化后用 set 处理，而一个序列的区间数，由于我们开不了一个二维表来存储这个信息，所以选择用 map 来存储。

你以为这就完了，但交上去只有 $48$ pts。

实际上是对于一个序列全是一个数的特判，因为一个序列全是一个数那么其区间个数为 $0$，会导致答案为 $0$，即使后面改变了数以后也为 $0$。

这个问题好解决，我们维护每一个数 $x$ 有多少个序列全是 $x$，然后对于贡献，我们不乘上区间数为 $0$ 的情况，当我们需要使用贡献时，看一下是否有一个序列全为 $x$，若有则变为 $0$，对于一个区间从全为 $x$ 变为不全为 $x$，我们特判将其加上即可。

代码不长，3k 左右，不需卡常，还是很良心的一道题的，如需代码私。



---

## 作者：XBaiC (赞：0)

这道题的思路并不难想。

很明显我们可以对每种数分别求出它们的贡献，在加起来就是答案（$con.size() \times mlen - ans$）（$con$ 表示迄今为止出现了多少种数）。

对于一种数（$v$）怎么求贡献？

正难则反，用总方案（$mlen$）减去不合法的方案（$mul_{v}$）。

怎么求一种数的不合法方案数？

求出该种数在每个序列的不合法方案数（$sum_{i,v}$），再乘起来就是不合法的方案总数（$mul_{v}$）。

怎么求一种数在一个序列里的不合法方案数？

对这种数开一个 set（$mp_{i,v}$），记录一下出现的坐标，把相邻两个坐标之间的子区间（不包含这两个坐标）数全部加起来即可。

代码写起来太麻烦了。

而且有一个巨坑无比的细节：$sum_{i,v}$ 可能为 $0$（即序列 $i$ 的所有数都为 $v$），如果将其乘进 $mul_{v}$ 的话，会导致后面将要除 $0$。

这怎么办？

我们可以记录一下，对于数 $v$，有几个序列的 $sum_{i,v}$ 为 $0$，记为 $zer_{v}$。

在更新的时候注意判断一下 $zer_{v}$，只有 $zer_{v}$ 为 $0$ 才更新 $ans$（$ans$ 表示所有数的不合法方案数之和）。


接下来就是鬼畜卡常数时间（为什么每次做 Ynoi 的题都要卡常数）。

唉，大常数选手的叹息。

先优化了一些显而易见的重复计算。

又发现自己一次 insert 要查询十几次 map。

于是用 & 优化了一下，就只用查 $5$ 次 map 了。

然后 TLE。

尝试预处理逆元，被卡空间了。

后来才发现可以直接离散化优化掉 $con,zer,mul$ 三个 map（由于比较懒，没有把 $con$ 优化掉）。

然后就 AC了。

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
using namespace std;
inline int gi()
{
	char c;int num=0,flg=1;
	while((c=getchar())<'0'||c>'9')if(c=='-')flg=-1;
	while(c>='0'&&c<='9'){num=num*10+c-48;c=getchar();}
	return flg==1?num:-num;
}
#define N 100005
const int mod=19260817;
const int inv2=9630409;
int inv(int x)
{
	if(!x) return 1;
	int ret=1,y=mod-2;
	while(y){
		if(y&1)ret=1ll*ret*x%mod;
		y>>=1;x=1ll*x*x%mod;
	}
	return ret;
}
int n,m,ans,len[N],cal[N],mlen;
vector<int> a[N];
map<int,set<int> >mp[N];
set<int>::iterator it,it1,it2;
map<int,int> sum[N],con;
int hh[2*N],hcnt;
struct node{int i,j,z;}q[N];
int mul[2*N],zer[2*N];
void insert(int i,int j,int v)
{
	int &mu=mul[v],&su=sum[i][v],tm=mu,ts=su;
	set<int> &S=mp[i][v];
	if(!con[v]++)mu=mlen;
	if(S.empty()){
		S.insert(-1);S.insert(len[i]);
		ts=su=cal[len[i]+1];
	}
	it1=S.lower_bound(j);
	it2=it1;it1--;
	su=(su-cal[(*it2)-(*it1)]+cal[(*it2)-j]+cal[j-(*it1)]+mod)%mod;
	S.insert(j);
	if(!su){if(!zer[v]++){ans=ans-tm+mod;if(ans>=mod)ans-=mod;}}
	else{
		mu=1ll*mu*inv(ts)%mod*su%mod;
		if(!zer[v])ans=(ans-tm+mu+mod)%mod;
	}
}
void delet(int i,int j,int v)
{
	int &mu=mul[v],&su=sum[i][v],tm=mu,ts=su;
	set<int> &S=mp[i][v];
	it1=it2=it=S.lower_bound(j);
	it1--;it2++;
	su=(su+cal[(*it2)-(*it1)]-cal[(*it2)-j]-cal[j-(*it1)]+2*mod)%mod;
	S.erase(it);con[v]--;
	if(!ts){if(!(--zer[v])){ans=ans+mu;if(ans>=mod)ans-=mod;}}
	else{
		mu=1ll*mu*inv(ts)%mod*su%mod;
		if(!zer[v])ans=(ans-tm+mu+mod)%mod;
	}
}
int main()
{
	int i,j,z;
	mlen=1;ans=0;
	for(cal[1]=0,i=1;i<=100000;i++)
		cal[i+1]=(cal[i]+i)%mod;
	n=gi();m=gi();
	for(i=1;i<=n;i++){
		len[i]=gi();
		mlen=1ll*mlen*cal[len[i]+1]%mod;
	}
	for(i=1;i<=n;i++)for(j=0;j<len[i];j++){
		a[i].push_back(gi());
		hh[++hcnt]=a[i][j];
	}
	for(i=1;i<=m;i++){
		q[i].i=gi();q[i].j=gi()-1;q[i].z=gi();
		hh[++hcnt]=q[i].z;
	}
	sort(hh+1,hh+hcnt+1);
	hcnt=unique(hh+1,hh+hcnt+1)-hh-1;
	for(i=1;i<=n;i++)for(j=0;j<len[i];j++){
		a[i][j]=lower_bound(hh+1,hh+hcnt+1,a[i][j])-hh;
		insert(i,j,a[i][j]);
	}
	printf("%d\n",(1ll*con.size()*mlen%mod+mod-ans)%mod);
	for(int k=1;k<=m;k++){
		i=q[k].i;j=q[k].j;
		z=q[k].z=lower_bound(hh+1,hh+hcnt+1,q[k].z)-hh;
		delet(i,j,a[i][j]);
		insert(i,j,a[i][j]=z);
		printf("%d\n",(1ll*con.size()*mlen%mod+mod-ans)%mod);
	}
}
```



---

