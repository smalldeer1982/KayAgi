# Yandex Cuneiform (Hard Version)

## 题目描述

这是该问题的困难版本。不同之处在于本版本对问号的数量没有限制。只有在你解决了所有版本的问题后，才能进行 hack。

很长一段时间里，没有人能破译苏美尔楔形文字。然而，它终于屈服于压力！今天，你有机会破译 Yandex 楔形文字。

Yandex 楔形文字由以下规则定义：

1. 空字符串是 Yandex 楔形文字。
2. 如果你在一个 Yandex 楔形文字中，恰好插入一份 'Y'、'D'、'X' 三个字母各一份，并且插入后没有两个相邻的字母相同，那么你得到的字符串也是 Yandex 楔形文字。
3. 如果一个字符串无法通过上述规则得到，那么它就不是 Yandex 楔形文字。

现在给你一个模板。模板是一个只包含 'Y'、'D'、'X' 和 '?' 的字符串。

你需要判断是否存在一种方法，将每个问号替换为 'Y'、'D' 或 'X'，使得最终得到的字符串是一个 Yandex 楔形文字。如果存在，输出任意一种可行的方案，并输出一组插入操作序列，使得可以得到你输出的楔形文字。

在本题版本中，模板中的问号数量没有限制。

## 说明/提示

在第二个样例中，字符串的变化过程如下：$"" \to \mathtt{YDX} \to \mathtt{YDXDYX}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
???
Y??D?X
???
D??DXYXYX```

### 输出

```
YES
YDX
X 0 D 0 Y 0 
YES
YDXDYX
X 0 Y 0 D 1
X 2 D 3 Y 4
YES
YDX
Y 0 D 1 X 2
NO```

# 题解

## 作者：wjwWeiwei (赞：6)

F1 做法[在此](https://www.luogu.com.cn/article/oeswjbaw)。


前言：F2 看官方题解后觉得不可写，于是贺某提交记录贺懂的。


现在问题在于如何从模板中构造初始串。


考虑设 dp 状态，记 $ma_{i,j,k}$ 表示考虑前 $i$ 个字符，且第 $i$ 个字符为 $j$ 时，字符为 $k$ 的个数至多为多少，$mi_{i,j,k}$ 为至少个数。转移显然。


可以发现，倒着构造是可行的，第 $i$ 个位置能填字符 $j$ 当且仅当 $\forall k\in \{\texttt{Y,D,X}\},mi_{i,j,k} \le cur_k \le ma_{i,j,k}$（$cur_k$ 为字符 $k$ 剩余个数），且字符 $j$ 不与第 $i+1$ 个位置上的字符相等。这是因为只要满足此限制，dp 状态一定能转移。


没有其他的了，在 F1 基础上略加修改一下就好了。


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5,M=1e6+5,mod=1e6+5;
const int INF=1e9+7;
using ll=long long;
int T,n;
int ton[4];
int a[N];
inline int to(char c){
	if(c=='Y')return 1;
	if(c=='D')return 2;
	if(c=='X')return 3;
	return 4;
}
inline char rto(int x){
	if(x==1)return 'Y';
	if(x==2)return 'D';
	return 'X';
}
string s;
int tr[N];
inline void add(int x,int v){while(x<=n)tr[x]+=v,x+=x&(-x);}
inline int qry(int x){
	int res=0;
	while(x)res+=tr[x],x-=x&(-x);
	return res;
}
bool vis[N];
int pre[N],nxt[N];
struct pii{
	int fi,se;
};
struct My_stack{
	pii st[N<<1];int Top;
	inline void clear(){Top=0;}
	inline bool empty(){return !Top;}
	inline pii top(){return st[Top];}
	inline void pop(){Top--;}
	inline void push(pii x){st[++Top]=x;}
}us[12];
inline int kt(int x,int y){return (x-1)*3+y-1;}
inline void fadd(int x,int y){
	if(a[x]==a[y]||!a[x]||!a[y])return ;
	int ks=kt(a[x],a[y]);
	us[ks].push({x,y});
}
inline void fdel(int pos){
	add(pos,-1);
	nxt[pre[pos]]=nxt[pos];pre[nxt[pos]]=pre[pos];
	fadd(pre[pos],nxt[pos]);
	pre[pos]=nxt[pos]=0;
	vis[pos]=1;
}
inline pii find_valid(int ks){
	while(!us[ks].empty()){
		pii P=us[ks].top();us[ks].pop();
		if(vis[P.fi]||vis[P.se])continue; 
		return P;
	}
	return {-1,-1};
}
struct node{
	pii p1,p2,p3;
};
vector<node>ans;
int ma[N][4][4],mi[N][4][4];
inline void Max(int &u,int v){if(u<v)u=v;}
inline void Min(int &u,int v){if(u>v)u=v;}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>s;
		n=s.length();
		memset(ton,0,sizeof ton);
		for(int i=1;i<=n;i++)pre[i]=i-1,nxt[i]=i+1;
		nxt[n]=a[n+1]=0;
		for(int i=1;i<=n;i++)a[i]=to(s[i-1]),tr[i]=vis[i]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=3;j++){
				for(int k=1;k<=3;k++)ma[i][j][k]=-INF,mi[i][j][k]=INF;
			}
		}
		bool va=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=3;j++){
				if(a[i]==j||a[i]==4){
					for(int k=1;k<=3;k++){
						if(j==k)continue;
						for(int l=1;l<=3;l++){
							Max(ma[i][j][l],ma[i-1][k][l]+(j==l));
							Min(mi[i][j][l],mi[i-1][k][l]+(j==l));
						}
					}
				}
			}
		}
		int las=0;
		ton[1]=ton[2]=ton[3]=n/3;
		for(int i=n;i>=1;i--){
			int cur=0;
			for(int j=1;j<=3;j++){
				if(j==las)continue;
				bool fl=1;
				for(int k=1;k<=3;k++){
					if(ma[i][j][k]<ton[k]||mi[i][j][k]>ton[k]){fl=0;break;}
				}
				if(fl)cur=j;
			}
			if(!cur){
				va=0;break;
			}
			a[i]=las=cur;ton[cur]--;
		}
		if(!va){
			cout<<"NO\n";
			continue;
		}
		ans.clear();
		for(int i=0;i<=10;i++)us[i].clear();
		for(int i=1;i<=n;i++)add(i,1);
		for(int i=1;i<n;i++)fadd(i,i+1);
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			vis[i]=1;
			int p1=0,p2=0;
			for(int j=1;j<=3;j++){
				if(j^a[i]){
					if(!p1)p1=j;
					else p2=j;
				}
			}
			pii cur=find_valid(kt(p1,p2));
			if(cur.fi==-1&&cur.se==-1)swap(p1,p2),cur=find_valid(kt(p1,p2));
			int x=pre[cur.fi],y=nxt[cur.se];
			if(x==i)ans.push_back({{p2,0},{p1,0},{a[i],0}}),fdel(i),fdel(cur.fi),fdel(cur.se);
			else if(a[x]^a[y]){
				int tot=qry(x)-1;
				ans.push_back({{p1,tot},{p2,tot+1},{a[i],0}});
				fdel(i),fdel(cur.fi),fdel(cur.se);
			}
			else{
				int tot=qry(x)-1;
				ans.push_back({{p2,tot},{a[i],tot},{p1,tot+1}});
				vis[i]=0;i--;
				fdel(x),fdel(cur.fi),fdel(cur.se);
			}
		}
		reverse(ans.begin(),ans.end());
		cout<<"YES\n";
		for(int i=1;i<=n;i++)cout<<rto(a[i]);
		cout<<"\n";
		for(auto v:ans){
			cout<<rto(v.p1.fi)<<" "<<v.p1.se<<" ";
			cout<<rto(v.p2.fi)<<" "<<v.p2.se<<" ";
			cout<<rto(v.p3.fi)<<" "<<v.p3.se<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

[Problem Link](https://www.luogu.com.cn/problem/CF2046F2)

**题目大意**

> 给定 `Y,D,X,?` 构成的长度为 $n$ 的字符串 $S$，把 `?` 填成 `Y,D,X` 的某一种，使得该 $S$ 可以由如下方式构造：从空串开始，每次向串中插入一个 `Y,D,X`，并且每次插入之后 $S$ 中不存在相邻相同的字符，给出方案。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

先解决不存在 `?` 的情况，$S$ 合法的必要条件是三种字符数量相等，且 $S$ 中不存在相邻相同的字符。

假设 $S$ 满足上述条件，我们尝试删除一个 `Y,D,X`，并且使得得到的新 $S$ 也满足上述条件，那么就归纳地证明了该条件的充分性，并且翻转这个过程就能得到一组构造。

不妨假设 $S_1=\texttt Y$，由于 `Y,D,X` 个数相等，因此 $S$ 中至少能找到一个 `DX` 或 `XD` 子串 $S[i,i+1]$。

如果 $S_{i-1}\ne S_{i+2}$，直接删除 $S_1,S_{i},S_{i+1}$ 就是合法构造。

否则一定有 $S_{i-1}=S_{i+2}=\texttt Y$，且 $S_{i-2}\ne S_{i-1}=S_{i+2}$ 删除 $S_{i-1},S_i,S_{i+1}$ 就是合法构造。

因此用链表动态维护 $S$，`set` 维护每种长度为 $2$ 的子串的出现位置即可。

接下来回到原问题，我们要找到一个 $S$ 满足相邻字符不同，且每种字符出现次数为 $n/3$。

此时提取出所有极长 `?` 连续段，可以发现可能的 `Y,D` 个数构成一个凸包，把每个连续段的凸包求闵可夫斯基和，并判断 $(n/3,n/3)$ 是否在凸包内，然后还原即可。

但这种方法太难实现，我们通过打表发现 $s[1,i]$ 中每种字符可能的出现次数都是一个区间，并且出现次数分别在三个区间内任取都是合法的。

那么直接 dp $f_{i,j,k}$ 表示 $s[1,i]$ 中 $s_i=j$ 时字符 $k$ 的出现次数对应的区间，转移是平凡的。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void chkmin(int &x,const int &y) { x=y<x?y:x; }
inline void chkmax(int &x,const int &y) { x=y>x?y:x; }
const int MAXN=2e5+5;
int n,a[MAXN],pr[MAXN],sf[MAXN],wys[MAXN];
char s[MAXN];
set <int> ps[4];
struct FenwickTree {
	int tr[MAXN],s;
	void init() { fill(tr+1,tr+n+1,0); }
	void add(int x,int v) { for(;x<=n;x+=x&-x) tr[x]+=v; }
	int qry(int x) { for(s=0;x;x&=x-1) s+=tr[x]; return s; }
}	TR;
int L[MAXN][4][4],R[MAXN][4][4];
void solve() {
	scanf("%s",s+1),n=strlen(s+1);
	for(int i=1;i<=n;++i) a[i]=(s[i]=='?'?0:(s[i]=='D'?1:(s[i]=='X'?2:3)));
	for(int i=1;i<=n;++i) {
		memset(L[i],0x3f,sizeof(L[i]));
		memset(R[i],-0x3f,sizeof(R[i]));
		for(int j:{1,2,3}) if(!a[i]||a[i]==j) {
			for(int k:{1,2,3}) for(int c:{1,2,3}) if(c^j) {
				chkmin(L[i][j][k],L[i-1][c][k]+(j==k));
				chkmax(R[i][j][k],R[i-1][c][k]+(j==k));
			}
		}
	}
	int c[4]={0,n/3,n/3,n/3};
	for(int i=n;i>=1;--i) {
		a[i]=0;
		for(int j:{1,2,3}) if(i==n||j!=a[i+1]) {
			bool ok=true;
			for(int k:{1,2,3}) ok&=(L[i][j][k]<=c[k]&&c[k]<=R[i][j][k]);
			if(ok) { a[i]=j; break; }
		}
		if(!a[i]) return puts("NO"),void();
		s[i]=" DXY"[a[i]],--c[a[i]];
	}
	for(int i=1;i<=n;++i) pr[i]=i-1,sf[i]=i+1;
	pr[n+1]=n,sf[0]=1;
	for(int i=1;i<n;++i) ps[a[i]^a[i+1]].insert(i);
	int tp=n;
	auto del=[&](int x) {
		wys[tp--]=x;
		int l=pr[x],r=sf[x];
		if(l>=1) ps[a[l]^a[x]].erase(l);
		if(r<=n) ps[a[x]^a[r]].erase(x);
		if(l>=1&&r<=n) ps[a[l]^a[r]].insert(l);
		sf[l]=r,pr[r]=l;
	};
	for(int _=0;_<n/3;++_) {
		int y=*ps[a[sf[0]]].begin(),z=sf[y],x=(sf[z]<=n&&a[pr[y]]==a[sf[z]]?pr[y]:sf[0]);
		del(z),del(y),del(x);
	}
	printf("YES\n%s\n",s+1);
	for(int i=1;i<=n;++i) {
		printf("%c %d%c"," DXY"[a[wys[i]]],TR.qry(wys[i])," \n"[i%3==0]);
		TR.add(wys[i],1);
	}
	TR.init();
	for(int i:{1,2,3}) ps[i].clear();
}
signed main() {
	int _; scanf("%d",&_);
	while(_--) solve();
	return 0;
}
```

---

