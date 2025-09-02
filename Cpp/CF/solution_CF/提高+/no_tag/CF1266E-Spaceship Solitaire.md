# Spaceship Solitaire

## 题目描述

## 题意翻译

Bob在玩一款叫*Spaceship Solitaire*的游戏。游戏的核心是建造一艘宇宙飞船。为了建造，他首先需要积累足够的资源。有$n$种资源，从$1$到$n$标号，Bob需要$a_i$个第$i$种资源来建造飞船。我们称$a_i$为资源$i$的目标。

一回合能且只能生产一个资源。但是，有一些“成就”可以加快生产速度。每个成就可以用一个三元组表示$(s_j, t_j, u_j)$，意思是当Bob拥有的第$s_j$种资源个数达到$t_j$时，他可以获得1个免费的第$u_j$种资源。获得此免费资源有可能使Bob要求获得另一个成就的奖励。

不会有两个成就含有相同的$s_j$和$t_j$，也就是说，达到资源$t_j$个资源$s_j$的奖励最多是一个额外的资源。

对于每个成就，有$0 < t_j < a_{s_j}$

达到一定资源量的奖励可以是这个资源本身，也就是$s_j = u_j$

最开始时没有成就的。你需要处理$q$次更新，可能是添加，删除或改变成就。在每次更新后，输出完成游戏（也就是对于每个资源$i \in [1, n]$，收集至少$a_i$个）所需的最小回合数。

## 样例 #1

### 输入

```
2
2 3
5
2 1 1
2 2 1
1 1 1
2 1 2
2 2 0
```

### 输出

```
4
3
3
2
3
```

# 题解

## 作者：万弘 (赞：6)

记$cnt_i$表示$u_j=i$的$j$的数量.记最优解为$B$.  
显然$B\ge\sum_{i=1}^nmax(0,a_i-cnt_i)$

接下来证明$B=\sum_{i=1}^nmax(0,a_i-cnt_i)$

由题意得引理1:达到资源$t_j$个资源$s_j$的奖励最多是一个额外的资源  
假设资源$u$需要$a(u)$个,现在已经有了$x$个$(x<a(u))$
- $x=a(u)-1$.建造/被奖励 一个资源$u$,$x=a(u)$,无法获得奖励.
- $x<a(u)-1$.建造/被奖励 一个资源$u$,$x<a(u)$,至多奖励一个资源$v$.若$v\ne u$,不会对$u$产生贡献;否则$x+1$,最终必然到达前一种情况.  

于是证毕.(其实这篇证明存在漏洞....如果有更好的证明可以联系我,也可以另写一篇题解)

有了这个结论,用`std::map`维护即可做到$\mathcal O(q\log n)$.官方还有线性的做法.  
```cpp
/**********/
#define MAXN 200011
std::map<ll,ll>p[MAXN];
ll a[MAXN],cnt[MAXN];
int main()
{
    ll n=read(),ans=0;
    for(ll i=1;i<=n;++i)a[i]=read(),ans+=a[i];
    ll q=read();
    while(q--)
    {
        ll s=read(),t=read(),u=read();
        if(p[s].count(t))
        {
            ll v=p[s][t];
            if(cnt[v]<=a[u])++ans;
            --cnt[v];
            p[s].erase(t);
        }
        if(u)
        {
            if(cnt[u]<a[u])--ans;
            ++cnt[u];
            p[s][t]=u;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

## 思路

考虑贪心。最开始如果什么成就都没有，答案显然为 $\displaystyle\sum_{i=1}^{n}a_i$。每多一项成就，就意味着第 $u_i$ 种资源可以少用一个回合，所以答案要减一。但这样有问题，因为可能第 $u_i$ 种资源已经不需要耗费回合了，但仍出现与它有关的成就，这时候答案就不需要有任何改变。所以应该记录 $p_i$ 表示第 $i$ 种资源目前需要的回合数，$p_i$ 可以小于 $0$。那么每次删除，就将需要删除的成就的 $p_{u_i}$ 加一，如果加完后这个数**大于** $0$，意味着这是增加的回合数，则答案加一。而每次添加，就将需要添加的成就的 $p_{u_i}$ 减一，如果加完后这个数**大于等于** $0$，就意味着可以少耗费回合数，则答案减一。

总时间复杂度 $O(q\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define mk make_pair
using namespace std;
const int N=2e5+5;
int n,a[N],q,ans;
map<pair<int,int>,int>mp;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),ans+=a[i];
	q=read();
	while(q--){
		int s,t,u;s=read();t=read();u=read();
		if(mp[mk(s,t)]){
			a[mp[mk(s,t)]]++;
			if(a[mp[mk(s,t)]]>0)ans++;
		}
		mp[mk(s,t)]=u;a[u]--;
		if(a[u]>=0&&u)ans--;
		printf("%lld\n",ans);
		//cout<<a[1]<<" "<<a[2]<<endl;
	}
	return 0;
}
```



---

## 作者：lfxxx (赞：0)

不妨令 $u_j = i$ 的 $j$ 数量记为 $cnt_i$，则有操作次数不少于 $\sum \max(0,a_i - cnt_i)$，下面说明为什么可以取到这个值。

这个式子的意义是对于每种资源，能对其产生贡献的成就全部生效，考虑这样一件事：不可能对于每个 $i$ 均有 $cnt_i \geq a_i$，因为这样的话 $\sum cnt_i$ 就超过了 $\sum a_i - 1$，成就总数超标，所以总是可以找到一个 $cnt_i < a_i$ 的，那么我们本回合收集这种资源，这种资源上的成就可以留到后面的回合且理论上还是可以全部取到。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map< pair<int,int> ,int> d;
const int maxn = 2e5+114;
int a[maxn],cnt[maxn],ans,n,q;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],ans+=a[i];
    cin>>q;
    for(int i=1;i<=q;i++){
        int s,t,u;
        cin>>s>>t>>u;
        if(d[make_pair(s,t)]!=0){
            cnt[d[make_pair(s,t)]]--;
            if(cnt[d[make_pair(s,t)]]<a[d[make_pair(s,t)]]) ans++;
            d[make_pair(s,t)]=0;
        }
        if(u!=0){
            d[make_pair(s,t)]=u;
            cnt[u]++;
            if(cnt[u]<=a[u]) ans--;
        }
        cout<<ans<<'\n';
    }
}
```

---

