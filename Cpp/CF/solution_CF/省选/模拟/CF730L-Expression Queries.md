# Expression Queries

## 题目描述

一个正确的算术表达式，允许包含括号、数字（可能带有前导零）、乘法和加法。例如表达式 “$(0+01)$”，“$0$” 和 “$1*(0)$” 是简化的算术表达式，但是表达式 “$2-1$”，“$+1$” 和 “$1+2)$” 不是。

给定一个字符串 $s_1s_2...s_{\left\vert{s}\right\vert}$，表示一个简化算术表达式；$s_i$ 表示字符串的第 $i$ 个字符，它可以是数字 $('0'-'9')$，加号 $('+')$，乘号 $('*')$，左括号 $(\ '(' \ )$ 或右括号 $( \ ')' \ )$。

一个字符串的部分 $s_{l}s_{l+1}...s_{r}$ 被称为子表达式，当且仅当它是一个 $SAE$ (简化算术表达式)。

你的任务是回答 $m$ 个查询，每个查询都是一对整数 $l_i$ 和 $r_i$ $(1\le l_i\le r_i\le \left\vert{s}\right\vert)$。对于每个查询，确定给定字符串的相应部分是否为子表达式，并在它是子表达式的情况下计算它的值模 $1000000007$ $(10^9+7)$。应使用标准运算符优先级计算值。

## 样例 #1

### 输入

```
((1+2)*3+101*2)
6
8 14
1 6
2 10
11 14
5 5
4 5
```

### 输出

```
205
-1
10
2
2
-1
```

## 样例 #2

### 输入

```
(01)
1
1 4
```

### 输出

```
1
```

# 题解

## 作者：xtx1092515503 (赞：1)

在串的两边加一对括号，然后建出表达式树。

这里的表达式树并非常规的表达式树——对于一连串 `+` 连接着的表达式，我们将其从左到右作为父节点的子节点，`*` 连接着的同理。

为了让这棵树长得更加标致，我们将所有点分成3类：

0. 括号点，其内部是一个由 `+` 连接的式子（可以只有一项）。
1. `+` 点，即一个由 `+` 连接的式子中的一项，内部是一个由 `*` 连接的式子（可以只有一项）。
2. `*` 点，其要么仅仅是一串数（此时没有儿子），要么有唯一的儿子——一个0点。

这样的树虽然节点数可能是 $1.5n$，有很多节点也是冗余的，但是却有着很好的结构。

现在我们考虑一次询问。显然，其不为 $-1$，当且仅当左右端点外层括号相同。

然后考虑回答询问。我们找到左右端点外层括号所对应的括号点。二分找到该括号点的所有子节点中，区间包含左右端点的那两个。则，此两个节点中间夹着的所有点，显然贡献就是它们的值之和。使用前缀和维护一下即可。

然后考虑包含左右端点的那两个 `+` 点。我们仍然可以二分找到其所有子节点中包含左右端点的那两个。则此二节点中间夹着的所有点贡献是它们的值之积。使用前缀积维护一下——是不行的，因为有 $0$。额外维护一下所有 $0$ 出现的位置，并维护非零元素的前缀积即可。这是老套路了。

然后考虑包含左右端点的那两个 `*` 点。其要么是一个括号，要么是一串数。如果是括号则显然其应该被完整地包括在区间内——因为如果其未被完整包括，则显然括号就没有被完全匹配，表达式是不合法的，所以此时就可以直接返回此括号内部表达式的值；否则，其是一串数，那就还是前缀和维护即可。

但是还需要特判。

首先要特判两个 `+` 点相同的情形。此时合法的 `*` 点是此点的一段子区间。

但是，在上述特判的前提下，还要继续特判两个 `*` 点相同的情形。此时询问的是该 `*` 点对应的整个括号（如果其对应的是括号的话），或者其对应的串的一段子串（如果其对应的是串的话）。

细节很多，要注意越界什么的，比较烦人。

时间复杂度 $O(n\log n)$。

代码：

```cpp
//following:a whole piece of shit.
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int ksm(int x,int y=mod-2){int z=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)z=1ll*z*x%mod;return z;}
const int inv10=ksm(10);
int n,m,pos[400100],cnt,lp[1200100],rp[1200100],tp[1200100];//0:bracket 1:plus 2:times.
int ten[400100],net[400100];
char s[400100];
vector<int>v[1200100];
vector<int>pre[1200100],zer[1200100];
stack<int>stk;
void dfs(int x){
	if(tp[x]==0)pre[x].push_back(0);
	if(tp[x]==1)pre[x].push_back(1);
	for(auto y:v[x]){
		dfs(y);
		if(tp[x]==0)pre[x].push_back((pre[x].back()+(zer[y].empty()?pre[y].back():0))%mod);
		if(tp[x]==1){
			if(pre[y].back()==0)zer[x].push_back(pre[x].size()),pre[x].push_back(pre[x].back());
			else pre[x].push_back(1ll*pre[x].back()*pre[y].back()%mod);
		}
	}
	if(tp[x]==2){
		if(!v[x].empty())pre[x].push_back(pre[v[x].back()].back());
		else{
			pre[x].push_back(0);
			for(int i=lp[x];i<=rp[x];i++)pre[x].push_back((10ll*pre[x].back()+s[i]-'0')%mod);
		}
	}
}
#define all(x) x.begin(),x.end()
int calc(int x,int l,int r){
	if(!v[x].empty())return pre[x].back();
	return (pre[x][r-lp[x]+1]+mod-1ll*pre[x][l-lp[x]]*ten[r-l+1]%mod)%mod;
}
int CALC(int x,int l,int r){
//	printf("%d %d\n",l,r);
//	for(auto i:zer[x])printf("%d ",i);puts("");
//	printf("%d %d\n",r,pre[x].size());
	auto it=upper_bound(all(zer[x]),l);
	if(it!=zer[x].end()&&*it<=r)return 0;
	if(!r)return 1;
	if(l==v[x].size()+1)return 1;
//	printf("[%d,%d]<%d,%d>\n",l,r,pre[x][r],pre[x][l+1]);
	return 1ll*pre[x][r]*ksm(pre[x][l+1])%mod;
}
int main(){
	scanf("%s",s+1),n=strlen(s+1);
	ten[0]=net[0]=1;for(int i=1;i<=n;i++)ten[i]=10ll*ten[i-1]%mod,net[i]=1ll*inv10*net[i-1]%mod;
	s[0]='(',s[n+1]=')';
	for(int i=0;i<=n+1;i++){
		if(s[i]=='(')stk.push(++cnt),lp[cnt]=i,tp[cnt]=0;
		pos[i]=stk.top();
		if(s[i]==')')rp[stk.top()]=i,stk.pop();
	}
	for(int i=0;i<=n+1;i++){
//		printf("%d:%d %c\n",i,stk.size(),s[i]);
		if(s[i]=='('){
			if(!stk.empty())v[stk.top()].push_back(pos[i]);
			stk.push(pos[i]);
			tp[++cnt]=1,lp[cnt]=i+1,stk.push(cnt);
			tp[++cnt]=2,lp[cnt]=i+1,stk.push(cnt);
		}
		if(s[i]=='+'){
			int tms=stk.top();stk.pop();
			rp[tms]=i-1;
			int pls=stk.top();stk.pop();
			rp[pls]=i-1;
			int bra=stk.top();
			v[pls].push_back(tms);
			v[bra].push_back(pls);
			tp[++cnt]=1,lp[cnt]=i+1,stk.push(cnt);
			tp[++cnt]=2,lp[cnt]=i+1,stk.push(cnt);
		}
		if(s[i]=='*'){
			int tms=stk.top();stk.pop();
			rp[tms]=i-1;
			int pls=stk.top();
			v[pls].push_back(tms);
			tp[++cnt]=2,lp[cnt]=i+1,stk.push(cnt);
		}
		if(s[i]==')'){
			int tms=stk.top();stk.pop();
			rp[tms]=i-1;
			int pls=stk.top();stk.pop();
			rp[pls]=i-1;
			int bra=stk.top();stk.pop();
			v[pls].push_back(tms);
			v[bra].push_back(pls);
		}
	}
//	for(int i=1;i<=n;i++)printf("%d ",pos[i]);puts("");
	dfs(1);
/*	for(int i=1;i<=cnt;i++){
		printf("%d(%d)[%d,%d]<%d,%d>",i,tp[i],lp[i],rp[i],pre[i].back(),zer[i].empty());
		for(auto j:v[i])printf("%d ",j);puts("");
	}*/
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;i++){
		scanf("%d%d",&l,&r);
//		for(int x=l;x<=r;x++)putchar(s[x]);puts("");
		if(pos[l-1]!=pos[r+1]||s[l]=='+'||s[l]=='*'||s[r]=='+'||s[r]=='*'){puts("-1");continue;}
		int x=pos[l-1];
		lp[0]=l;
		int p=upper_bound(all(v[x]),0,[](int a,int b){return lp[a]<lp[b];})-v[x].begin()-1;
		int P=v[x][p];
		int _p=upper_bound(all(v[P]),0,[](int a,int b){return lp[a]<lp[b];})-v[P].begin()-1;
		int _P=v[P][_p];
		rp[0]=r;
		int q=lower_bound(all(v[x]),0,[](int a,int b){return rp[a]<rp[b];})-v[x].begin();
		int Q=v[x][q];
		int _q=lower_bound(all(v[Q]),0,[](int a,int b){return rp[a]<rp[b];})-v[Q].begin();
		int _Q=v[Q][_q];
//		printf("X%dp%dP%d_p%d_P%dq%dQ%d_q%d_Q%d\n",x,p,P,_p,_P,q,Q,_q,_Q);
		if(p==q&&_p==_q){printf("%d\n",calc(_P,l,r));continue;}
		int pp=calc(_P,l,rp[_P]);
		int qq=calc(_Q,lp[_Q],r);
//		printf("[%d %d]\n",pp,qq);
		if(p==q){printf("%d\n",1ll*pp*CALC(P,_p,_q)%mod*qq%mod);continue;}
		pp=1ll*pp*CALC(P,_p,v[P].size())%mod;
		qq=1ll*qq*CALC(Q,-1,_q)%mod;
//		printf("[%d %d]\n",pp,qq);
		printf("%d\n",(0ll+pp+(pre[x][q]+mod-pre[x][p+1])%mod+qq)%mod);
	}
	return 0;
} 
```



---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/730/problem/L) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF730L)

大模拟（？）+阿巴细节题，模拟赛时刚了 3h 最后因为某个细节写挂 100->40/ll/ll（下次一定不能再挂分了啊 awa）

首先先考虑怎么判 $-1$，显然如果区间 $[l,r]$ 中间的括号构不成合法的括号序列，答案显然是 $-1$，其次如果 $s_l$ 是加号或乘号那算式也不合法，$s_r$ 也同理，这可以通过前缀和+ST 表在 $\mathcal O(n\log n)-\mathcal O(1)$ 时间内判断。

其次考虑怎样计算一个表达式的值，首先按照套路建出表达式树，不过这里建表达式树与平常略微有点不同，平常我们建的表达式树都是二叉树，即将运算符放在中间，参与运算的两个部分作为该节点的左右儿子，这次咱们偏不建二叉树，咱们建多叉树，具体来说，对于同一个括号内的统计运算我们同时将它们设为该运算代表的节点的儿子（比方说 $1+2\times 3+4\times 5$ 的根节点就有 $3$ 个儿子 $1,2\times 3,4\times 5$，中间运算符为加号），我们同时记录这些儿子执行的运算在原字符串中对于的区间，比方说 $2\times 3$ 这个儿子在原字符串中的区间就是 $[3,5]$。

那么对于一个询问而言，如果它本身就是一个数（比方说 $1234$ 或 $(((7)))$）那么我们就直接输出这个数即可，否则我们找出计算这个表达式时最后一次执行的运算表示的节点 $x$，显然 $x$ 表示的运算有加号或乘号两种可能，分情况讨论：

首先考虑乘法，我们假设 $x$ 的儿子在原字符串中的区间分别为 $[a_1,b_1],[a_2,b_2],\cdots,[a_m,b_m]$，那么我们二分找出 $l,r$ 所在的区间，假设为 $[a_L,b_L]$ 和 $[a_R,b_R]$，显然这些区间在 $[l,r]$ 中的部分是一个个整段+边上两个散块，中间部分对答案的贡献显然是完整的，直接前缀积即可 $\mathcal O(1)$ 求出，注意特判前缀积为 $0$ 的情况，此时需记录前缀 $0$ 的个数加以判断，对于边上两块的情况分情况讨论：有可能两边也是整块贡献，这时候直接计入答案即可，也有可能两边是某一段数计入贡献（比方说 $12\times 34\times 56$，对于询问 $[2,7]$ 而言，左边的 $12$ 和右边的 $56$ 就分别被一分为二），此时写一个类似哈希的东西快速求出一段区间表示的数即可在常数时间内累加贡献。

接下来考虑加法，和乘法类似，我们还是找出 $l,r$ 所在的区间 $[a_L,b_L]$ 和 $[a_R,b_R]$，这些区间在 $[l,r]$ 中的部分还是一个个整段+边上两个散块，对于中间部分对前缀和搞一下即可，对于边上两块的情况还是分情况讨论：前两类（整块贡献&某个数一分为二）与乘法一样不再赘述，但是加法比乘法多的一种情况是，有可能边角块对应的运算是一个序列的乘法运算（比方说 $12\times 34+56\times 78$ 对于询问 $[2,10]$ 而言，左边区间计入贡献的部分就是 $2\times 34$，右边部分也同理），以左边的散块为例，这种情况就找到 $[a_L,b_L]$ 对应的节点，二分一下乘法对应的区间（显然是一段后缀），然后还是前缀积算一算即可，注意，在这部分里的乘法操作中还是有可能出现某个数一分为二的情况，注意判断。

时间复杂度 $n\log n$，注意特判一些奇奇怪怪的情况，比方说 $((((((1145141919810))))))$ 或者 $(998244353)\times (19260817)$，我就是因为这边有个细节写挂了而丢了 60pts/ll

代码（码了 238 行，现以吊打切树游戏、吊打 CF788E，荣膺我 AC 的题目中的码量之最）

```cpp
const int MAXN=5e5;
const int LOG_N=20;
const int MOD=1e9+7;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int n,qu,ncnt,sum[MAXN+5],dep[MAXN+5];char s[MAXN+5];
int nt[MAXN+5],pr[MAXN+5];
vector<int> son[MAXN+5];
vector<pii> itvl[MAXN+5];
int mch[MAXN+5],rt,bel[MAXN+5],op[MAXN+5],val[MAXN+5];
int pre[MAXN+5],pw10[MAXN+5];
int getnum(int l,int r){return (pre[r]-1ll*pre[l-1]*pw10[r-l+1]%MOD+MOD)%MOD;}
int build(int l,int r){
	if(s[l]=='('&&mch[l]==r) return bel[l]=bel[r]=build(l+1,r-1);
	int opt=-1,id=++ncnt;
	for(int i=l;i<=r;){
		if(s[i]=='+') opt=0;
		else if(s[i]=='*'&&!~opt) opt=1;
		if(s[i]=='(') i=mch[i]+1;
		else i++;
	} op[id]=opt;
	if(!~opt){
		for(int i=l;i<=r;i++){
			bel[i]=id;
			val[id]=(10ll*val[id]+s[i]-'0')%MOD;
		} return id;
	} int pre=l-1;
	for(int i=l;i<=r;){
		if((s[i]=='+'&&!opt)||(s[i]=='*'&&opt)){
			son[id].pb(build(pre+1,i-1));
			itvl[id].pb(mp(pre+1,i-1));
			pre=i;bel[i]=id;
		} if(s[i]=='(') i=mch[i]+1;
		else i++;
	} son[id].pb(build(pre+1,r));itvl[id].pb(mp(pre+1,r));
//	printf("build [%d,%d]:\n",l,r);
//	printf("op[%d]=%d\n",id,op[id]);
//	for(int x:son[id]) printf("%d ",x);printf("\n");
//	for(pii p:itvl[id]) printf("[%d,%d]\n",p.fi,p.se);
//	printf("\n");
	return id;
}
struct num0{
	int x,y;
	num0(int _x=0){(_x)?(x=_x,y=0):(x=y=1);}
	int val(){return (y)?0:x;}
	num0 operator +(const int &rhs){
		int sum=(val()+rhs)%MOD;
		return (sum)?num0(sum):num0(0);
	}
	num0 operator *(const int &rhs){
		num0 res=*this;
		(rhs)?(res.x=1ll*res.x*rhs%MOD):(res.y++);
		return res;
	}
	num0 operator /(const num0 &rhs){
		num0 res;res.x=1ll*x*qpow(rhs.x,MOD-2)%MOD;
		res.y=y-rhs.y;return res;
	}
};
vector<num0> ss[MAXN+5];
void calc(int x){
	if(~op[x]) val[x]=op[x];
	ss[x].resize(son[x].size());
	for(int i=0;i<son[x].size();i++){
		int y=son[x][i];dep[y]=dep[x]+1;calc(y);
		if(!i) ss[x][i]=val[y];
		if(op[x]==0){
			val[x]=(val[x]+val[y])%MOD;
			if(i) ss[x][i]=ss[x][i-1]+val[y];
		} else {
			val[x]=1ll*val[x]*val[y]%MOD;
			if(i) ss[x][i]=ss[x][i-1]*val[y];
		}
//		printf("%d %d %d\n",x,i,ss[x][i].val());
	}
}
int st_sum[MAXN+5][LOG_N+2];
pii st_dep[MAXN+5][LOG_N+2];
void buildst(){
	for(int i=1;i<=LOG_N;i++) for(int j=1;j+(1<<i)-1<=n;j++){
		st_sum[j][i]=min(st_sum[j][i-1],st_sum[j+(1<<i-1)][i-1]);
		st_dep[j][i]=min(st_dep[j][i-1],st_dep[j+(1<<i-1)][i-1]);
	}
}
int query_sum(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return min(st_sum[l][k],st_sum[r-(1<<k)+1][k]);
}
pii query_dep(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return min(st_dep[l][k],st_dep[r-(1<<k)+1][k]);
}
int main(){
//	freopen("calc.in","r",stdin);
//	freopen("calc.out","w",stdout);
	scanf("%s%d",s+1,&qu);n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(isdigit(s[i])) pre[i]=(10ll*pre[i-1]+s[i]-'0')%MOD;
		else pre[i]=pre[i-1];
	}
	for(int i=(pw10[0]=1);i<=n;i++) pw10[i]=10ll*pw10[i-1]%MOD;
	stack<int> stk;
	for(int i=1;i<=n;i++){
		if(s[i]=='(') stk.push(i),sum[i]=sum[i-1]+1;
		else if(s[i]==')'){
			mch[i]=stk.top();mch[stk.top()]=i;
			stk.pop();sum[i]=sum[i-1]-1;
		} else sum[i]=sum[i-1];
	}
	int pp=n+1;
	for(int i=n;i;i--){
		if(!isdigit(s[i])) pp=i;
		else nt[i]=pp-1;
	} pp=0;
	for(int i=1;i<=n;i++){
		if(!isdigit(s[i])) pp=i;
		else pr[i]=pp+1;
	}
//	for(int i=1;i<=n;i++) printf("%d%c",mch[i]," \n"[i==n]);
	rt=build(1,n);calc(rt);
//	for(int i=1;i<=n;i++) printf("%d%c",bel[i]," \n"[i==n]);
	for(int i=1;i<=n;i++) st_sum[i][0]=sum[i],st_dep[i][0]=mp(dep[bel[i]],i);
	buildst();
	while(qu--){
		int l,r;scanf("%d%d",&l,&r);
		if(sum[l-1]!=sum[r]){puts("-1");continue;}
		if(query_sum(l,r)<sum[l-1]){puts("-1");continue;}
		if(s[l]=='+'||s[l]=='*'){puts("-1");continue;}
		if(s[r]=='+'||s[r]=='*'){puts("-1");continue;}
		pii p=query_dep(l,r);int x=bel[p.se];
//		printf("%d\n",x);
		if(!~op[x]){
			if(isdigit(s[l])&&isdigit(s[r])) printf("%d\n",getnum(l,r));
			else printf("%d\n",val[x]);
			continue;
		}
		int L=upper_bound(itvl[x].begin(),itvl[x].end(),mp(l,n+1))-itvl[x].begin()-1;
		int R=upper_bound(itvl[x].begin(),itvl[x].end(),mp(r,n+1))-itvl[x].begin()-1;
		if(L<0) L=0;
		int u=son[x][L],v=son[x][R];
//		printf("%d %d\n",L,R);
		if(op[x]==1){
			int res=1;
			if(L!=R){
				num0 qwq=ss[x][R-1]/ss[x][L];
				res=qwq.val();
			}
			if(~op[u]) res=1ll*res*val[u]%MOD;
			else{
				if(isdigit(s[l])) res=1ll*res*getnum(l,nt[l])%MOD;
				else res=1ll*res*val[u]%MOD;
			} if(~op[v]) res=1ll*res*val[v]%MOD;
			else{
				if(isdigit(s[r])) res=1ll*res*getnum(pr[r],r)%MOD;
				else res=1ll*res*val[v]%MOD;
			}
			printf("%d\n",res);
		} else {
			int res=0;
			if(L!=R) res=(ss[x][R-1].val()-ss[x][L].val()+MOD)%MOD;
			if(~op[u]){
				if(op[u]==0) res=(res+val[u])%MOD;
				else{
					int LL=upper_bound(itvl[u].begin(),itvl[u].end(),mp(l,n+1))-itvl[u].begin()-1;
					if(LL<0) LL=0;
					int su=son[u][LL],mul=1;
					if(LL+1!=ss[u].size())
						mul=(ss[u].back()/ss[u][LL]).val();
					if(~op[su]) mul=1ll*mul*val[su]%MOD;
					else{
						if(isdigit(s[l])) mul=1ll*mul*getnum(l,nt[l])%MOD;
						else mul=1ll*mul*val[su]%MOD;
					}
					res=(res+mul)%MOD;
				}
			} else{
				if(isdigit(s[l])) res=(res+getnum(l,nt[l]))%MOD;
				else res=(res+val[u])%MOD;
			}
			if(~op[v]){
				if(op[v]==0) res=(res+val[v])%MOD;
				else{
					int RR=upper_bound(itvl[v].begin(),itvl[v].end(),mp(r,n+1))-itvl[v].begin()-1;
					int sv=son[v][RR],mul=1;
					if(RR) mul=(ss[v][RR-1]).val();
					if(~op[sv]) mul=1ll*mul*val[sv]%MOD;
					else{
						if(isdigit(s[r])) mul=1ll*mul*getnum(pr[r],r)%MOD;
						else mul=1ll*mul*val[sv]%MOD;
					}
					res=(res+mul)%MOD;
				}
			} else{
				if(isdigit(s[r])) res=(res+getnum(pr[r],r))%MOD;
				else res=(res+val[v])%MOD;
			}
			printf("%d\n",res);
		}
	}
	return 0;
}
```



---

