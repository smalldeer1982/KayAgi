# Same Count One

## 题目描述

给定 $n$ 个长度为 $m$ 的，只包含 $0$ 和 $1$ 的数组，选择任意两个数组交换位置 $pos$ 上的数。在经过最少的操作后使得每个数组中的 $1$ 数量相等，并输出操作过程。

## 样例 #1

### 输入

```
3
3 4
1 1 1 0
0 0 1 0
1 0 0 1
4 3
1 0 0
0 1 1
0 0 1
0 0 0
2 2
0 0
0 1```

### 输出

```
1
2 1 1
1
4 2 2
-1```

# 题解

## 作者：Dream_weavers (赞：6)

## 题意

给出 $m$ 个长度为 $n$ 的数组，数组中每个数不是 $0$ 就是 $1$。你可以选择任意两个数组交换 $pos$ 位置上的数。请构造一种交换方案，使得操作数最少，并且操作完成后每个数组中 $1$ 的个数相等。

## 思路

贪心思路其实挺好想的。

要让每个数组 $1$ 的个数相等，我们需要算出所有 $1$ 的和 $sum$，每个数组要有 $\frac{sum}{n}$ 个 $1$。如果 $\frac{sum}{n}$ 不是整数，也就是不能被整除，那么直接输出 $-1$。

每次交换只能选择两个数组。先统计出一个数组中 $1$ 的个数 $cnt$。对于位置 $pos$，每次都要遍历每个数组。对于以下两种情况：

- 如果 $cnt<\frac{sum}{n}$，就要把数组中的一些 $0$ 变为 $1$

- 如果 $cnt>\frac{sum}{n}$，就要把数组中的一些 $1$ 变为 $0$

注意在位置 $pos$ 上要有两个数组分别满足这两个情况的其中一个，才可以交换。容易证明，只要 $sum$ 是 $n$ 的倍数，就可以通过交换使得每个数组中 $1$ 的个数相等。


## 代码

```cpp
void solve(){
    scanf("%d%d",&n,&m);
    init();
    for(int i=0;i<n;i++){
        int tmp=0;
        for(int j=0;j<m;j++){
            int x;scanf("%d",&x);
            a[i].push_back(x);
            sum+=x,tmp+=x;
        }
        cnt.push_back(tmp);
    }
    if(sum%n!=0){
        puts("-1");
        return;
    }
    sum/=n;
    for(int i=0;i<m;i++){
        locmore.clear(),locless.clear();
        for(int j=0;j<n;j++){
            if(cnt[j]>sum&&a[j][i])locmore.push_back(j);
            if(cnt[j]<sum&&!a[j][i])locless.push_back(j);
        }
        int len=min(locmore.size(),locless.size());
        for(int j=0;j<len;j++){
            ans[++tot]=(node){locless[j],locmore[j],i};
            cnt[locmore[j]]--,cnt[locless[j]]++;
        }
    }
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++)printf("%d %d %d\n",ans[i].x+1,ans[i].y+1,ans[i].z+1);
}
```

---

## 作者：WaterSun (赞：3)

# 思路

首先记所有 $1$ 的数量为 $num$，那么显然有当 $n \bmod num \neq 0$ 时无解。那么考虑有解的时候该怎么办。

显然对于每一个 $a_i$ 序列中，最终 $1$ 的数量为 $\frac{num}{n}$，记作 $t$；并记 $cnt_i$ 表示 $a_i$ 序列中 $1$ 的数量。

我们希望最终所有的 $cnt_i$ 都等于 $t$，并且希望操作步数最小，我们考虑一个显然的贪心：将 $cnt_i > t$ 的序列中的 $1$ 补 $cnt_j < t$ 缺失的 $1$。

这样我们每一次的操作都会使 $\sum_{i = 1}^{n}|cnt_i - t|$ 减少 $2$，显然是最优的方案。

**注意：如果你在交换的时候，一定需要更新 $a_{i,k}$ 和 $a_{j,k}$，否则有一个很简单的 [Hack](https://www.luogu.com.cn/paste/5evdgv7n)。因为你不更新，你的程序会认为 $a_{3,1}$ 在第一次操作后还是 $0$ 可以交换。**

# Code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register

using namespace std;

typedef pair<int,int> pii;
const int N = 1e5 + 10;
int n,m;
int cnt[N];
pii del[N];

struct answer{
    int a,b,pos;
};

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    int num = 0;
    n = read();
    m = read();
    bool vis[n + 10][m + 10];
    vector<answer> ans;
    for (re int i = 1;i <= n;i++){
        cnt[i] = 0;
        for (re int j = 1;j <= m;j++){
            int x;
            x = read();
            if (x) vis[i][j] = true;
            else vis[i][j] = false;
            num += x;
            cnt[i] += x;
        }
    }
    if (num % n) return puts("-1"),void();
    num /= n;
    for (re int i = 1;i <= n;i++) del[i] = {cnt[i] - num,i};
    sort(del + 1,del + n + 1);
    for (re int i = 1,j = n;i < j;){
        int p = del[i].snd,q = del[j].snd;
        for (re int k = 1;k <= m && del[i].fst && del[j].fst;k++){
            if (!vis[p][k] && vis[q][k]){
                del[i].fst++;
                del[j].fst--;
                vis[p][k] = true;
                vis[q][k] = false;
                ans.push_back({p,q,k});
            }
        }
        if (!del[i].fst) i++;
        if (!del[j].fst) j--;
    }
    printf("%d\n",ans.size());
    for (auto p:ans) printf("%d %d %d\n",p.a,p.b,p.pos);
}

int main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：wenhaoran11 (赞：2)

## 题目大意
一共 $T$ 组测试数据，对于每组测试数据。给出 $n$ 组数，每组 $m$ 个数。其中数只有可能是 $0$ 或 $1$。可以在任意两组数中交换相同位置的数，求最少几次变换后，可以使每组数 $1$ 的数量一致。输出变换次数与具体是如何变换的。如果无法满足题意，输出 $-1$。

## 简单分析
什么样是输出 $-1$ 的情况。设 $n$ 组数中一共有 $a$ 个 $1$。则每组中1的数量为 $a/n$，而如果 $a/n$ 不是整数，说明无法每组平均分，输出 $-1$ 即可。

## 深入探讨
剩余情况如何解决。设正常每组中应有 $1$ 的数量为 $t$，而现在组中有 $o$ 个 $1$。则如果 $o>t$ 说明应该有一些 $1$ 变为 $0$，而如果当前 $i$ 位置是 $1$，就统计起来。同理，如果 $o<t$，说明应该有一些 $0$ 应变为 $1$，而如果当前位置 $i$ 位置是 $0$，也统计起来。而最小次数用 $len$ 表示即可，在记录上文所说的两种情况中变动就好了。

主要代码。
```cpp
for(int i=1;i<=m;i++){
			int t1=0,t2=0;
			for(int j=1;j<=n;j++){
				if(cnt[j]>t&&p[j][i]==1) a[++t1]=j;
				if(cnt[j]<t&&p[j][i]==0) b[++t2]=j;
			}
			for(int j=1;j<=min(t1,t2);j++){
				ans[++len].x=b[j];
				ans[len].y=a[j];
				ans[len].z=i;
				cnt[a[j]]--;
				cnt[b[j]]++;
			}
		}
		cout<<len<<"\n";
		for(int i=1;i<=len;i++){
			cout<<ans[i].x<<' '<<ans[i].y<<' '<<ans[i].z<<"\n";
		}
```

整体代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int T,n,m,len,cnt[N],a[N],b[N];
vector<int> p[N];//统计每组1的数量
struct node{
	int x,y,z;
};
node ans[N];//统计题目所说的答案
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		memset(cnt,0,sizeof cnt);
		int t=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			p[i].clear(); 
			p[i].push_back(0);
			for(int j=1;j<=m;j++){
				int x;
				cin>>x;
				p[i].push_back(x);
				t+=x;
				cnt[i]+=x;
			}
		}
		if(t%n!=0){//判断是否有解
			cout<<-1<<"\n";
			continue;
		}
		t/=n;
		len=0;
		for(int i=1;i<=m;i++){
			int t1=0,t2=0;
			for(int j=1;j<=n;j++){
				if(cnt[j]>t&&p[j][i]==1) a[++t1]=j;
				if(cnt[j]<t&&p[j][i]==0) b[++t2]=j;
			}
			for(int j=1;j<=min(t1,t2);j++){
				ans[++len].x=b[j];
				ans[len].y=a[j];
				ans[len].z=i;
				cnt[a[j]]--;
				cnt[b[j]]++;
			}
		}
		cout<<len<<"\n";
		for(int i=1;i<=len;i++){
			cout<<ans[i].x<<' '<<ans[i].y<<' '<<ans[i].z<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：lilong (赞：2)

首先 $1$ 的总个数不能被 $n$ 整除时无解。

否则一定有解（因为每一列上的 $1$ 的位置都可以随意变动，故实际上相当于可以随便放）。为了步数最少，一定是用缺少 $1$ 行的 $0$ 与过多 $1$ 行的 $1$ 交换，这样能同时使两行更接近答案。实现时先枚举列，再根据每行的情况找出上面两种行，并一一配对交换即可。时间复杂度 $O(\sum nm)$。


```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define N 200010
using namespace std;
int n,m,cnt[N],cnt0;
vector<int> G[N],a,b;
int ans,ansx[N*10],ansy[N*10],ansz[N*10];
void solve(){
    cnt0=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        G[i].clear();
    for(int i=1;i<=n;i++){
        G[i].push_back(0);
        cnt[i]=0;
        for(int j=1;j<=m;j++){
            G[i].push_back(0);
            cin>>G[i][j];
            cnt0+=G[i][j];
            cnt[i]+=G[i][j];
        }
    }
    if(cnt0%n){
        cout<<-1<<'\n';
        return;
    }
    cnt0/=n;
    ans=0;
    for(int j=1;j<=m;j++){
        a.clear();b.clear();
        for(int i=1;i<=n;i++){
            if(cnt[i]<cnt0&&!G[i][j])a.push_back(i);
            if(cnt[i]>cnt0&&G[i][j])b.push_back(i);
        }
        for(int i=0;i<min(a.size(),b.size());i++){
            ans++;
            ansx[ans]=a[i],ansy[ans]=b[i],ansz[ans]=j;
            cnt[a[i]]++,cnt[b[i]]--;
        }
    }
    cout<<ans<<'\n';
    for(int i=1;i<=ans;i++)
        cout<<ansx[i]<<' '<<ansy[i]<<' '<<ansz[i]<<'\n';
    return;
}
int main(){
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：VinstaG173 (赞：2)

首先显然 1 的总数不是 $n$ 的倍数时显然无法做到。

接下来给出是 1 的总数是 $n$ 的倍数时的操作方案。设 1 的总数为 $nk$，则当所有行中 1 的个数还不全相同时，一定有一行 1 的个数多于 $k$，也有一行 1 的个数少于 $k$。设这两行分别有 $a,b$ 个 1，其中 $a>k>b$。则至少有 $a-b>\min\{a-k,k-b\}$ 列上 1 较多的一行为 1，较少的一行为 0，故我们必可以找到 $\min\{a-k,k-b\}$ 列进行如题所述的操作，在操作后这两行中 1 的个数变为 $k,a+b-k$。

综上所述，每当不满足要求时，我们都可以让 1 的个数为 $k$ 的行数至少增加 $1$，由于总行数有限，因此我们最终一定能满足题目要求。

但是我们还要证明这样的操作次数是最少的。事实上，注意到初始时 1 的个数多于 $k$ 的行的每个多出来的 1 都必须通过一次操作换走，且操作过程中我们总是将 1 的个数多于 $k$ 的行的 1 和 1 的个数少于 $k$ 的行的 0 互换，对每个多余的 1 恰进行了一次操作。因此这样可以达到操作次数最小值。

具体操作过程可以将行按初始 1 个数排序，用双指针扫描当前操作行即可做到 $O(nm)$。

Code:
```cpp
int n,m,s;
int v[100003];
int a[200003];
int id[100003];
int I[200003],c;
int L[200003],R[200003];
inline int cmp(int x,int y){
	return v[x]>v[y];
}inline void solve(){rd(n),rd(m);s=c=0;
	for(rg int i=0;i<n;++i)
		v[i]=0,id[i]=i;
	for(rg int i=0;i<n;++i)
		for(rg int j=0;j<m;++j)
			s+=rd(a[i*m+j]),\
			v[i]+=a[i*m+j];
	if(s%n){puts("-1");return;}
	s/=n;sort(id,id+n,cmp);
	for(rg int _l=0,_r=n-1,l,r;_l<_r;){
		l=id[_l],r=id[_r];
		for(rg int i=0;v[l]>s&&v[r]<s;++i){
			if(a[l*m+i]&&!a[r*m+i])
				--v[l],++v[r],\
				I[++c]=i+1,L[c]=l+1,R[c]=r+1,\
				a[l*m+i]=0,a[r*m+i]=1;
		}if(v[l]==s)++_l;if(v[r]==s)--_r;
	}printf("%d\n",c);
	for(rg int i=1;i<=c;++i){
		printf("%d %d %d\n",L[i],R[i],I[i]);
	}
}
```

---

## 作者：CQ_Bob (赞：1)

## 分析

考虑模拟。

很容易想到贪心：对于第 $i$ 行 $j$ 列的 $1$，如果这个 $1$ 是多余的，则转移到某个少 $1$ 且第 $j$ 列没有 $1$ 的位置上。无解就是 $sum \bmod n \ne 0$，其中 $sum$ 表示 $1$ 的总数。

然后就是模拟。枚举每一列 $row$ 以及每一行 $line$。如果这一列未匹配成功且 $a_{line,row}=0$，则在 $x_{row}$ 中进行寻找一个能交换的 $line'$。其条件根据贪心可得：$line'$ 这一行需要是之前匹配成功且有多余的 $1$。

在将 $a_{line,row}$ 与 $a_{line',row}$ 交换之后再判断一下 $line$ 这一行是否匹配成功即可。

复杂度 $O(nm)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=1e5+10;
int n,m;
bool vis[N];
int cnt2[N],cnt[N];
vector<int> a[N],x[N];
struct node{
	int x,y,z;
}ans[N];
int sum,idx;

il void solve(){
	n=read(),m=read();
	sum=idx=0;
	for(re int i=1;i<=max(n,m);++i) 
		x[i].clear(),a[i].clear(),
		cnt[i]=cnt2[i]=vis[i]=0;	
	for(re int line=1;line<=n;++line)
	for(re int row=1;row<=m;++row){
		a[line].push_back(read()),cnt[line]+=a[line][row-1];
		if(a[line][row-1]) ++sum,x[row].push_back(line);
	}
	for(re int line=1;line<=n;++line) vis[line]=(cnt[line]>=sum/n);
	if(sum%n) return printf("-1\n"),void(0);	
	for(re int row=1,now=0;row<=m;++row){
		now=0;
		for(re int line=1;line<=n;++line){
			if(vis[line]||a[line][row-1]) continue;
			while(now<x[row].size()&&(cnt[x[row][now]]-sum/n<=0)) ++now;
			if(now<x[row].size()){
				--cnt[x[row][now]],++cnt[line];
				if(cnt[line]==sum/n) vis[line]=1;
				ans[++idx]={x[row][now],line,row};
				++now;
			}
		}
	}
	printf("%lld\n",idx);
	for(re int i=1;i<=idx;++i) printf("%lld %lld %lld\n",ans[i].x,ans[i].y,ans[i].z);
	return ;
}

signed main(){
	int t=read();while(t--)
	solve();
	return 0;
}
```


---

## 作者：highkj (赞：1)

# 前言
被教练拉着和高中的一起 VP 的一场，中途做了会文化课然后最终还是把 D 调过了，感觉题目还不错就来发题解了。 
# 思路
我们首先可以求出所有 $1$ 的个数,那么如果 $sum1\div n$ 有余数那么一定是无解的，然后我们设每一行需要的 $1$ 为 $x$ 个，那么我们对于一行中求出当前 $1$ 的个数为 $sum_i$ 那么我们可以分类讨论。

- 如果 $sum_i<x$ 那么我们需要将另一行的 $1$ 交换上这一行的 $0$。
- 如果 $sum_i>x$ 那么我们将这一行的 $1$ 交还给其他行的 $0$ 即可。

有了以上的结论之后我们很好做了，首先我们枚举出交换的那一列，然后再去遍历所有点，再开两个桶分别装上面所说的两种情况的点的位置,然后我们可以将第 $i$ 个满足一条件的点和第 $i$ 个满足二条件的点交换一下，那么我们的计入答案也就很简单了只需要用一个 vector 存下每一个交换指令即可，但是主要要将 $sum_i$ 更新一下以便后面的处理。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define pb push_back
#define w(x)  while(x--)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int t;
int n,m;
vector<int>v[1001000];
int sum[1001000];
vector<int>duo,shao;
struct node{
	int x,y,z;
};
vector<node>res;
int one;
fire main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	in(t);
	w(t) {
		in(n),in(m);
		one=false;
		rep(i,1,n) sum[i]=false;
		rep(i,1,n) {
			v[i].clear();
			v[i].pb(INT_MAX);
			rep(j,1,m) {
				int x;
				in(x);
				v[i].pb(x);
				one+=x;
				sum[i]+=x;
			}
		} 
		if(one%n) {
			cout<<"-1\n";
			continue;
		}
		int x=one/n,f=false;
		rep(i,1,m) {
			rep(j,1,n){
				if(sum[j]>x&&v[j][i]==1) {
					duo.pb(j);
				}else if(sum[j]<x&&v[j][i]==0) shao.pb(j);
			}
			int idx=false;
			while(idx<shao.size()&&idx<duo.size()) {
				sum[duo[idx]]--;
				sum[shao[idx]]++;
				res.pb({duo[idx],shao[idx],i});
				idx++;
			}
			duo.clear();
			shao.clear();
		}
		if(f) continue;
		cout<<res.size()<<endl;
		for(node a:res) cout<<a.x<<" "<<a.y<<" "<<a.z<<endl;
		res.clear();
	}
	return false;
}


```

---

## 作者：little_cindy (赞：1)

## 题意简述
~~貌似 Dream_weavers 的题意 $m$ 和 $n$ 反了？~~

给定 $n$ 个长度为 $m$ 的01数组。

对于一次操作，可以交换两个数组同一位置的两个数。

求使得每个数组的 $1$ 的个数都相同的最小操作数。

不存在方案输出 $-1$。

## 思路
假设一共有 $tot$ 个 $1$，显然每个数组都有 $\frac{sum}{n}$ 个 $1$。

显然如果 $\frac{sum}{n}$ 不为整数即 $tot$ 不为 $n$ 的倍数可以直接判无解，否则必然有解（证明见最后）。

考虑统计每个数组中的 $1$ 的个数 $num$。显然 $num<\frac{sum}{n}$ 时，需要将 $0$ 与满足 $num>\frac{sum}{n}$ 的数组中同一位 $1$ 换。

遍历每一位，暴力换满足 $num<\frac{sum}{n}$ 的数组中的 $0$ 和满足 $num>\frac{sum}{n}$ 的数组中的 $1$ 即可。

时间复杂度为 $O(nm)$。

## 证明
对于一个 $1$ 个数不足 $\frac{sum}{n}$ 的数组 $a$ 和一个 $1$ 个数超过 $\frac{sum}{n}$ 的数组 $b$，必然存在 $i$ 满足 $a_i=0,b_i=1$，所以交换后一定能使得 $a,b$ 中的一个数组的 $1$ 的个数为 $\frac{sum}{n}$。

显然只存在同时有 $1$ 个数超过 $\frac{sum}{n}$ 的数组和 $1$ 个数不足 $\frac{sum}{n}$ 的数组以及每个数组 $1$ 的个数恰好为 $\frac{sum}{n}$ 两种情况。

第一种情况下，交换 $1$ 个数不足 $\frac{sum}{n}$ 的数组 $a$ 和 $1$ 个数超过 $\frac{sum}{n}$ 的数组 $b$ 中满足 $a_i=0,b_i=1$ 的位置 $i$ 直到 $a$ 的 $1$ 个数为 $\frac{sum}{n}$。此时 $1$ 个数不为  $\frac{sum}{n}$ 必然减少 $1$。当只剩下 $2$ 个时，显然交换后会变为情况二，即有解。						

---

## 作者：lovely_qiqi (赞：0)

## 思路

发现由于每一位上的 $1$ 可以通过操作来随意分配。于是只有 $1$ 的个数不是 $n$ 的倍数时无解。

其他情况下对于每一列统计两个东西：

+ 当前序列满足条件且当前位置是多余的 $1$。
+ 当前序列不满足条件且当前位置是 $0$。

然后进行交换，记录下来就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int a1,a2,a3;
}ans[100010];
int t,n,m,arr,all,len,o[100010],t1,t2,on[100010],ze[100010];
vector<int> v[100010];
void solve(){
	scanf("%lld%lld",&n,&m);
	all=0;
	for(int i=1;i<=n;i++){
		o[i]=0;
		v[i].clear();
		v[i].push_back(0);
		for(int j=1;j<=m;j++){
			scanf("%lld",&arr);
			if(arr==1) o[i]++,all++;
			v[i].push_back(arr);
		}
	}
	if(all%n!=0){
		printf("-1\n");
		return ;
	}
	all/=n;
	len=0;
	for(int i=1;i<=m;i++){
		t1=t2=0;
		for(int j=1;j<=n;j++){
			if(o[j]>all&&v[j][i]==1) on[++t1]=j;
			if(o[j]<all&&v[j][i]==0) ze[++t2]=j;
		}
		for(int j=1;j<=min(t1,t2);j++){
			ans[++len].a1=ze[j];
			ans[len].a2=on[j];
			ans[len].a3=i;
			o[on[j]]--;
			o[ze[j]]++;
		}
	}
	printf("%lld\n",len);
	for(int i=1;i<=len;i++) printf("%lld %lld %lld\n",ans[i].a1,ans[i].a2,ans[i].a3);
	return ;
}
signed main(){
	scanf("%lld",&t);
	while(t--) solve();
    return 0;
}

```

---

## 作者：ttq012 (赞：0)

为了让所有数组的 $1$ 的个数相等，需要算出 $1$ 在所有数组中出现的次数 $c$。为了让这些 $1$ 平均分在所有的数组里面，需要满足 $c\bmod n=0$，否则无解。

然后考虑贪心。

当数组满足条件的时候，每一个数组里出现的 $1$ 的次数都是 $g = \frac{c}{n}$。

设 $cnt_i$ 表示第 $i$ 个数组中 $1$ 出现的次数。

然后分类讨论：

+ $cnt_i = g$，不需要讨论。①
+ $cnt_i < g$，需要将数组中的一些 $0$ 用 $1$ 替换。②
+ $cnt_i > g$，需要将数组中的一些 $1$ 用 $0$ 替换。③

对于每一组 ② 和 ③，都只需要将 ③ 的 $1$ 用 ② 的 $0$ 替换，② 的 $0$ 用 ③ 的 $1$ 替换，一直到有一个出现 ① 情况为止。

时间复杂度是 $O(nm)$ 的。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 19;
int cnt[N];
map <int, map <int, int> > a;
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  wt:;
  if (T == 0)
    return 0;
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i ++)
    cnt[i] = 0;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      cin >> a[i][j];
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      cnt[i] += a[i][j];
  int sum = accumulate(cnt + 1, cnt + n + 1, 0ll);
  if (sum % n) cout << "-1\n";
  else
  {
    vector<tuple<int, int, int> > res;
    sum /= n;
    for (int i = 1; i <= m; i ++)
    {
      vector<int> ar1, ar2;
      for (int j = 1; j <= n; j ++)
        if (a[j][i] == 1 && cnt[j] > sum)
          ar1.push_back(j);
        else if (a[j][i] == 0 && cnt[j] < sum)
          ar2.push_back(j);
      for (int j = 0; j < min(ar1.size(), ar2.size()); j ++)
      {
        cnt[ar1[j]] --;
        cnt[ar2[j]] ++;
        res.push_back({ar2[j], ar1[j], i});
      }
    }
    cout << res.size() << '\n';
    for (auto &[i, j, k] : res)
      cout << i << ' ' << j << ' ' << k << '\n';
  }
  T --;
  goto wt;
}
```



---

## 作者：AlicX (赞：0)


被教练拉着和高中学长一起 VP，极限过 D，但是被虐得惨不忍睹。

## Solution 

无解的情况很简单，令 $sum$ 表示 $1$ 的总个数，判断 $sum \bmod n=0$ 即可。如果可行，则每一行的 $1$ 的个数为 $\frac{sum}{n}$，用 $kim$ 表示。

不难想到智障贪心，即把 $1$ 的个数多的给 $1$ 的个数少的。所以考虑将每一行按照 $1$ 的个数用 $cnt_i$ 表示，并从小到大排序。对于 $cnt_i < kim$ 的，用 `vector` 存下每一列哪些行为 $0$ 的行。然后对于 $cnt_i > kim$ 的，遍历 `vector` 去放即可。

细节有两处：注意 $cnt_i$ 的加减和 $mp_{i,j}$ 的更新（$mp_{i,j}$ 表示 $(i,j)$ 这一处是否为 $1$）。

~~代码又臭又长。~~

```cpp
#include<bits/stdc++.h>
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=1e6+10; 
int n,m; 
int cnt[N],Mp[N]; 
struct Node{ int a,b,c; }; 
vector<int> g[N],v[N],l[N]; 
bool cmp(pii a,pii b){ return a.x<b.x; } 
il void work(){ 
    cin>>n>>m; int sum=0;
	bool mp[n+10][m+10]; 
    vector<pii> e; 
    for(int i=1;i<=n;i++){ 
    	Mp[i]=cnt[i]=0; 
    	g[i].clear(),v[i].clear(),l[i].clear(); 
        for(int j=1;j<=m;j++){ 
            int x; cin>>x; mp[i][j]=false;  
            if(x) mp[i][j]=true,v[i].push_back(j),cnt[i]++,sum++; 
        } e.push_back({cnt[i],i}); 
    } if(sum%n!=0){ puts("-1"); return ; } 
	int kim=sum/n; 
	sort(e.begin(),e.end(),cmp); 
    for(int i=0;i<e.size();i++) l[i+1]=v[e[i].y],Mp[i+1]=e[i].y; 
    for(int i=1;i<=n;i++) v[i]=l[i]; 
	vector<Node> ans; int id=0; 
    for(int i=1;i<=n;i++){ 
        if(cnt[Mp[i]]<kim){ 
            for(int j=1;j<=m;j++) if(!mp[Mp[i]][j]) g[j].push_back(Mp[i]); 
        } if(cnt[Mp[i]]>kim){ 
            for(int j=0;j<v[i].size();j++){ 
                int x=v[i][j]; 
                if(cnt[Mp[i]]>kim){ 
	                while(g[x].size()&&(cnt[g[x][g[x].size()-1]]>=kim||mp[g[x][g[x].size()-1]][x])) g[x].pop_back(); 
					if(g[x].size()) ans.push_back({Mp[i],g[x][g[x].size()-1],x}),cnt[g[x][g[x].size()-1]]++,cnt[Mp[i]]--,mp[g[x][g[x].size()-1]][x]=true,id++;  
				} 
            } 
        } 
    } cout<<id<<endl; 
    for(int i=0;i<ans.size();i++) cout<<ans[i].a<<" "<<ans[i].b<<" "<<ans[i].c<<endl; 
} 
signed main(){ 
    int T; cin>>T; 
    while(T--) work(); 
    return 0;   
} /*
1
3 4
1 1 1 1
1 1 1 1
0 0 1 0
*/
```



---

## 作者：Zimo_666 (赞：0)

## D. Same Count One

极为正常的一道题。

### Statement

给定 $n$ 个长度为 $m$ 的，只包含 $0$ 和 $1$ 的数组，选择任意两个数组交换位置 $pos$ 上的数。在经过最少的操作后使得每个数组中的 $1$ 数量相等，并输出操作过程。.

### Solution

无解就是 $0$ 的个数总和不能被 $n$ 整除。

有解的时候我们对于每一列，都记录下可以被转移的行，然后转移就行。

记得清空！！尤其是无解之后要清空！！！

[Code](https://codeforces.com/contest/1774/submission/229373059)

---

