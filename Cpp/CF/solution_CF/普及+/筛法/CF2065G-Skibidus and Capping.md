# Skibidus and Capping

## 题目描述

Skibidus 被 Amog 外星人绑架了！Skibidus 试图以言辞自辩脱身，但 Amog 外星人不相信他。为了证明自己不是在撒谎(capping)，Amog 外星人要求他解决以下问题：

一个整数 $x$ 如果可以写成 $p \cdot q$ 的形式（$p$ 和 $q$ 均为质数，可以相同），则称其为半质数。例如，$9$ 是半质数，因为它可以写成 $3 \cdot 3$，而 $3$ 是质数。

Skibidus 得到了一个包含 $n$ 个整数的数组 $a$。他需要统计所有满足 $i \leq j$ 且 $\operatorname{lcm}(a_i, a_j)$ $ ^{\text{∗}} $ 为半质数的索引对 $(i, j)$ 的数量。

$ ^{\text{∗}} $ 给定两个整数 $x$ 和 $y$，$\operatorname{lcm}(x, y)$ 表示 $x$ 与 $y$ 的 [最小公倍数](https://zh.wikipedia.org/wiki/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B8)。

## 说明/提示

在第一个测试用例中，满足条件的 $5$ 个索引对分别为 $(1, 3)$、$(1, 4)$、$(2, 3)$、$(2, 4)$ 和 $(4, 4)$。

## 样例 #1

### 输入

```
3
4
2 2 3 4
6
2 2 3 4 5 6
9
2 2 4 5 7 8 9 3 5```

### 输出

```
5
12
18```

# 题解

## 作者：gesong (赞：6)

题目传送门：[Skibidus and Capping](https://codeforces.com/problemset/problem/2065/G)。
# 思路
首先有一个很显然的东西：设 $a=\prod_{i=1}^n{p_i}^{x_i},b=\prod_{i=1}^n{p_i}^{y_i}$ 其中 $p_i$ 均为质数，则 $\operatorname{lcm}(a,b)=\prod_{i=1}^n{p_i}^{\max(x_i,y_i)}$。

由上所述，再根据题目半质数的定义，我们可以知道，如果一个数想要被计算到那么必须满足它的质因数分解的质数个数只能为 $1,2$ 并且每一个质数的指数不能大于 $2$，特别的，如果有两个质数那么每一个质数的指数都要为 $1$。

这里可能有点绕，读者可以根据代码前面的预处理理解。

为了方便，我们按照质因数分解的质数个数从大到小排序。

我们从后往前遍历，我们设 $cnt_{i,j}$ 表示处理过的数中 $i^j$ 的个数，$cnt_0$ 表示处理过的数字所有质因数分解的质数个数为 $1$ 且指数也为 $1$ 的个数，$mp_{i,j}$ 表示处理过的数中 $i\times j$ 的个数，按照下面的情况讨论：

- 若质因数分解的质数为 $1$，那么设这个数为 ${p_1}^{q_1}$。
- - 若 $q_1=1$ 对答案的贡献即为 $cnt_{p_1,2}+cnt0-cnt_{p_1,1}$。
  - 若 $q_1=2$ 对答案的贡献即为 $cnt_{p_1,1}+cnt_{p_1,2}+1$ 注意这里要加上自己。
- 若质因数分解的质数为 $2$，那么设这个数为 ${p_1}^{q_1}\times {p_2}^{q_2}$，那么对答案的即为 $cnt_{p_1,1}+cnt_{p_2,1}+mp_{p_1,p_2}+1$ 注意这里要加上自己。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
const int N=2e5+10;
struct nord{
	int p1,q1,p2,q2;
	bool operator <(const nord &x) const{
		if (p2==-1&&x.p2==-1) return 0;
		else if (p2==-1&&x.p2!=-1) return 0;
		else if (p2!=-1&&x.p2==-1) return 1;
		else return 0;
	}
}a[N];
int cnt[N][3],cnt0=0;
#define pii pair<int,int>
map<pii,int>mp;
inline void solve(){
	mp.clear();
	int n=read();
	for (int i=1;i<=n;i++) cnt[i][2]=cnt[i][1]=0;cnt0=0;
	int cnt1=0;
	for (int i=1;i<=n;i++){
		int x=read();
		bool flag=1;
		vector<pii >aa;
		for (int j=2;j*j<=x;j++)
			if (x%j==0){
				int sum=0;
				while(x%j==0) sum++,x/=j;
				if (sum>2){
					flag=0;
					break;
				}
				aa.push_back({j,sum});
			}
		if (!flag) continue;
		if (x^1) aa.push_back({x,1});
		if (aa.size()>2) continue;
		if (aa.size()==1) a[++cnt1]={aa[0].first,aa[0].second,-1,-1};
		else{
			if (aa[0].second>1||aa[1].second>1) continue;
			a[++cnt1]={aa[0].first,aa[0].second,aa[1].first,aa[1].second};
			if (a[cnt1].p1>a[cnt1].p2) swap(a[cnt1].p1,a[cnt1].p2),swap(a[cnt1].q1,a[cnt1].q2);
		} 
	}
	n=cnt1;
	sort(a+1,a+n+1);
	int ans=0;
	for (int i=n;i>0;i--){
		if (i<=n){
			if (a[i].p2==-1){
				if (a[i].q1==1) ans+=cnt[a[i].p1][2]+cnt0-cnt[a[i].p1][1];
				else ans+=cnt[a[i].p1][1]+cnt[a[i].p1][2]+1;
			}
			else ans+=cnt[a[i].p1][1]+cnt[a[i].p2][1]+mp[{a[i].p1,a[i].p2}]+1;
		}
		if (a[i].p2==-1){
			if (a[i].q1==1) cnt0++;
			cnt[a[i].p1][a[i].q1]++;
		} 
		else mp[{a[i].p1,a[i].p2}]++;
	}
	printf("%lld\n",ans);
}
main(){
	int T=read();
	while(T--) solve();
	return 0;
}
//Codeforces Round 1003 RP++
//Codeforces Round 1003 RP++
//Codeforces Round 1003 RP++
//Codeforces Round 1003 RP++
//Codeforces Round 1003 RP++
```

---

## 作者：fish_love_cat (赞：3)

感觉是全场最一眼的了。

---

显然有 $\text{lcm}(x,x)=x$。

那么任意两个相同的半质数显然是合法的组合。

显然有 $x\perp y$ 时 $\text{lcm}(x,y)=xy$。

那么任意两个不同的质数显然是合法的组合。

显然有 $x\mid y$ 时 $\text{lcm}(x,y)=y$。

那么任意一个半质数与它的因子显然是合法的组合。

其他的情况不行，质因子数量必然不为 $2$。

那么打个质数筛找到半质数和质数以后，对于每组数据开个桶处理即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[200005];
vector<int>ve[200005];
void zss(int n){
	for(int i=2;i<=n;i++)
	if(!f[i])for(long long j=1;j*i<=n;j++){
        int x=i*j;
        while(x%i==0&&f[j*i]!=3)
        f[j*i]++,x/=i;
        ve[i*j].push_back(i);
    }
}
int a[200005],sum[200005];
void solve(){
    memset(sum,0,sizeof sum);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>a[i],sum[a[i]]++,sum[0]+=(f[a[i]]==1);
    //cout<<sum[0]<<' ';
    int ans=0,flc=0;
    for(int i=1;i<=n;i++)
    if(f[i]==2)ans+=sum[i]*(sum[i]-1)/2+sum[i]+sum[i]*sum[ve[i][0]]+(ve[i].size()>1?sum[ve[i][1]]*sum[i]:0);
    else if(f[i]==1)flc+=sum[i]*(sum[0]-sum[i]);
    cout<<ans+flc/2<<endl;
}
signed main(){
    zss(200000);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

好像是写的最为简洁的（？）

---

## 作者：_hi_ (赞：3)

## 思路

可以先考虑一些性质：

1. 半质数只有 2 种拆分方式，即为 1 $\times$ 它自己，$p \times q$。

3. $\operatorname{lcm}(x,y)=x^\prime \times y^\prime \times \gcd(x,y)$，其中 $x^\prime=x/\gcd(x,y)$，$y^\prime=y/\gcd(x,y)$。


---
发动我们惊人的注意力可以注意到，需要 $\operatorname{lcm}(x,y)$ 为半质数时，$x^\prime$，$y^\prime$，$\gcd(x,y)$ 中必定有一个是一。（半质数性质）

由此进行分讨：

1. $\gcd(x,y)=1$，且 $x^\prime$，$y^\prime$ 都是质数，根据性质 2，反推 **$x=x^\prime$，$y=y^\prime$ 且 $x \neq y$。**(否则 $\gcd(x,y)=x=y$）

2. $x^\prime$，$y^\prime$ 中较小的为 1，接下来，假设较大的为 $x^\prime$，较小的为$y^\prime$。需要满足 $\gcd(x,y)$，$x^\prime$，$y$ 都为质数。

注意到，$y=\gcd(x,y)$，$x=x^\prime \times \gcd(x,y)=x^\prime \times y$。**惊人发现** **$x$ 为半质数且其中一个质因数为 $y$。**

看似结束了，实则还有一种。如：$x=y=4$。

3. $x^\prime=y^\prime=1$，**$x=y$ 且 $x$，$y$ 为半质数**，这样 $\operatorname{lcm}(x,y)=\gcd(x,y)=x=y$ 为半质数。

## AC code:


```cpp
#include<bits/stdc++.h>
using namespace std;
long long _,n,a[200005],sum[200005],ji[200005],jib[200005],ck2[200005],ck[200005],ck3[200005];
inline bool CK(long long x){//是否为质数
    for(long long i=2;i*i<=x;i++){
        if(x%i==0)return 0;
    }
    return 1;
}
inline long long CK2(long long x){//是否为半质数
    long long ans=0;
    for(long long i=2;i*i<=x;i++){
        if(x%i==0 && (ck[i]==0 || ck[x/i]==0))return -1;
    }
    return 1;
}
inline long long CK3(long long x){//若为半质数，它的q,p是多少
    for(long long i=2;i*i<=x;i++){
        if(x%i==0)return i;
    }
    return 0;
}
int main(){
    for(long long i=1;i<=200000;i++)ck[i]=CK(i);
    for(long long i=1;i<=200000;i++){
        if(!ck[i])ck2[i]=CK2(i),ck3[i]=CK3(i);
    }
    scanf("%lld",&_);
    while(_--){
        long long ans=0;
        scanf("%lld",&n);
        for(long long i=1;i<=n;i++){
            sum[i]=ji[i]=jib[i]=0;
            scanf("%lld",&a[i]);
        }
        for(long long i=1;i<=n;i++){
            if(ck[a[i]])ans+=(sum[i-1]-ji[a[i]]),ji[a[i]]++;//第一种分讨
            sum[i]=sum[i-1]+ck[a[i]];
            if(ck2[a[i]]==1)jib[a[i]]++,ans+=jib[a[i]];//第三种分讨
        }
        for(long long i=1;i<=n;i++){//第二种分讨
            if(ck2[a[i]]==1){
                long long t=ck3[a[i]];
                ans+=ji[t]+ji[a[i]/t];
                if(t*t==a[i])ans-=ji[t];
            }
        }
        printf("%lld\n",ans);
    }
}
```

---

## 作者：Magallan_forever (赞：1)

#### 简要说明题意：

定义满足 $x=pq$（$p,q$ 均为质数）的数 $x$ 为半质数。现在给出一个长度为 $n$ 的数组 $a$，求满足 $1 \leq i \leq j \leq n,\rm{lcm}(a_i,a_j)$ 为半质数的 $(i,j)$ 的对数。

#### 题目分析：

~~注意到~~符合条件的只有这三种情况：

1. $a_i,a_j$ 都是质数且 $a_i \neq a_j$，$(i,j)$ 当然满足条件。

2. $a_i,a_j$ 中有一个半质数，另一个数是这个数的因数（即 $p,q$ 之一），$(i,j)$ 也满足条件。

3. 第三种情况是 $a_i=a_j$，$a_i$ 是半质数。

如果 $a_i,a_j$ 都是质数且 $a_i=a_j$，$\textrm{lcm}(a_i,a_j)=a_i$，不符合题意。

如果 $a_i,a_j$ 中有一个半质数（记作 $x=pq$），但另一个数不是这个数的因数（记作 $p'$），则 $\textrm{lcm}(a_i,a_j)=pqp'$，不符合题意。

如果 $a_i,a_j$ 至少有一个不属于半质数的合数（记作 $t$ 吧），那么 $\textrm{lcm}(a_i,a_j)=t*m$，$t$ 已经不能写成 $x=pq$ 的形式了。

那么就比较好做了，预处理所有的质数，在读入时根据 $a_i$ 是否是质数/半质数进行统计和求和。实现方法应该比较多，我使用了树状数组：

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
vector<int> p;
int markp[200001];
bool semip[200001];
void euler(){
    for(int i=2;i<=200000;++i){
        if(!markp[i]) markp[i]=i,p.push_back(i);
        for(int j=0;j<p.size()&&(long long)p[j]*i<=200000&&p[j]<=markp[i];++j){
            markp[p[j]*i]=p[j];
            if(markp[i]==i) semip[p[j]*i]=true;
        }
    }
}
int C[200001],n,mark[200001],cntp[200001];//C是权值树状数组，mark用于统计质数和半质数，cntp[i]是已经出现的含i的半质数个数
int lowbit(int v){
    return v&(-v);
}
void modify(int x,int v){
    for(;x<=n;x+=lowbit(x)) C[x]+=v;
}
int query(int l,int r){ //[l,r]
    int cnt=0;
    for(--l;l;l-=lowbit(l)) cnt-=C[l];
    for(;r;r-=lowbit(r)) cnt+=C[r];
    return cnt;
}
int main(){
    int T;
    long long cnt;//这答案肯定会爆int
    scanf("%d",&T),euler();
    while(T--){
        scanf("%d",&n),fill(C+1,C+1+n,0),fill(mark+1,mark+1+n,0),fill(cntp+1,cntp+1+n,0),cnt=0ll;
        for(int i=0,temp;i<n;++i){
            scanf("%d",&temp);
            if(markp[temp]==temp) ++mark[temp],modify(temp,1),cnt+=query(1,temp-1)+query(temp+1,n)+cntp[temp];
            if(semip[temp]){
                ++mark[temp],++cntp[markp[temp]],cnt+=mark[markp[temp]]+mark[temp];
                if(markp[temp]^(temp/markp[temp])) cnt+=mark[temp/markp[temp]],++cntp[temp/markp[temp]];
            }
        }
        printf("%lld\n",cnt);
    }
    return 0;
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV1eiNhe7EZ9?t=2441)

---

## 作者：Double_Light (赞：0)

考虑预处理质数，这样容易把 $a_i$ 分成质数、半质数、其他数三种类型。

对于不是质数、半质数的数，考虑它们是完全没有意义的，因为它们的倍数不可能是一个半质数，故它们不会对答案产生贡献。

接下来保留所有质数、半质数，同时记录下所有半质数的两个质因子 $p_1,p_2$。

考虑将答案的二元组分成两类计数：$i=j$ 与 $i<j$。

对于前者，显然 $(i,i)$ 能对答案产生 $1$ 的贡献当且仅当 $a_i$ 为半质数。

对于后者，考虑枚举 $j$，同时记录下对于下标是 $1\sim j-1$ 的数中：

- 数字 $i$ 出现的次数 $t_i$。
- 质数的个数 $cnt$。
- 所有半质数中含有因子 $i$ 的个数 $c_i$。

显然这些都可以在枚举 $j$ 的时候更新。

最后考虑计算答案。如果 $a_j$ 是质数，那么贡献的答案显然是质数个数 $cnt$ 减去 $a_j$ 的数量 $t_{a_j}$ 再加上含有因子 $a_j$ 的半质数个数 $c_{a_j}$。如果 $a_j$ 是半质数，答案就是 $t_{p_1}+t_{p_2}+t_{a_j}$，注意如果 $p_1=p_2$ 不能重复计算。
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int Is[200005],tot,pri[200005];
int n,T;
const int N=2e5;
int a[200005];
int b[200005];
int c[200005];
int t[200005];
int ans;
signed main(){
	for(int i=2;i<=N;i++)Is[i]=1;
	for(int i=2;i<=N;i++){
		if(Is[i])pri[++tot]=i;
		for(int j=1;j<=tot&&i*pri[j]<=N;j++){
			Is[pri[j]*i]=0;
			if(i%pri[j]==0)break;
		}
	}
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)t[i]=c[i]=b[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			if(Is[a[i]])b[i]=1;
			else{
				for(int j=2;j*j<=a[i];j++){
					if(a[i]%j==0){
						if(Is[j]&&Is[a[i]/j])b[i]=j;
						break;
					}
				}
			} 
		}
		int cnt=0;
		ans=0;
		for(int i=1;i<=n;i++){
			if(b[i]==1){
				ans+=cnt-t[a[i]];
				ans+=c[a[i]];
			}
			if(b[i]>1){
				ans++;
				if(b[i]*b[i]!=a[i])ans+=t[b[i]]+t[a[i]/b[i]]+t[a[i]];
				else ans+=t[b[i]]+t[a[i]];
			}
			if(b[i]==1)cnt++;
			if(b[i]>1){
				c[b[i]]++;
				if(b[i]*b[i]!=a[i])c[a[i]/b[i]]++;
			}
			t[a[i]]++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

hjs：对于赛时没过 G 的人，我也只能胡之嘲讽。

我们可以把所有数分 $3$ 类讨论：质数、质数的平方、半质数，其他的数显然是无法产生任何贡献的。

贡献的种类：

1. 质数和其他质数可以产生贡献，如 $5$ 和 $11$，而 $7$ 和 $7$ 就不能。

2. 质数和该质数的平方可以产生贡献，如 $7$ 和 $49$。

3. 质数可以含有这个质数的半质数产生贡献，如 $5$ 和 $15$。

4. 同质数的平方可以互相产生贡献，如 $25$ 和 $25$。

5. 半质数只能和自己或别的一模一样的半质数产生贡献，如 $6$ 和 $6$。

线性筛出所有 $10^5$ 以内的质数，用三个 `map` 存储即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 2e5 + 10;
const int inf = 1e16;
const int mod = 1e9 + 7;
int T,n,tot;
int a[N],b[N];
int Prime[N];
bool vis[N];
map <int,int> Map2,Map3,t;
map <pair <int,int>,int> Map;
vector <int> pri;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void init(){ // 线性筛
	vis[1] = 1;
	for (int i = 2 ; i <= 200000 ; i++){
		if (!vis[i]) Prime[++tot] = i;
		for (int j = 1 ; j <= tot && i * Prime[j] <= 200000 ; j++){
			vis[i * Prime[j]] = 1;
			if (i % Prime[j] == 0) break;
		}
	}
}
void solve(){
	Map.clear(); Map2.clear(); Map3.clear(); t.clear();
	int tot1 = 0;
	cin >> n;
	for (int i = 1 ; i <= n ; i++) cin >> a[i];
	int ans = 0;
	for (int i = 1 ; i <= n ; i++){
		int flag = 0;
		pri.clear(); // 筛出这个数的所有质因子
		for (int j = 1 ; j * j <= a[i] ; j++){
			if (a[i] % j != 0 || vis[j]) continue;
			int cnt = 0;
			while (a[i] % j == 0){
				a[i] /= j;
				cnt++;
			}
			if (cnt > 2){
				flag = 2;
				break;
			}
			if (cnt == 2)
				flag = 1;
			pri.push_back(j);
			if ((int)pri.size() == 3 || ((int)pri.size() == 2 && flag == 1)){
				flag = 2;
				break;
			}
		}
		if (flag == 2) continue; 
		for (int j = 1 ; j * j <= a[i] ; j++){
			j = a[i] / j;
			if (a[i] % j != 0 || vis[j]) continue;
			int cnt = 0;
			while (a[i] % j == 0){
				a[i] /= j;
				cnt++;
			}
			if (cnt > 2){
				flag = 2;
				break;
			}
			if (cnt == 2)
				flag = 1;
			pri.push_back(j);
			if ((int)pri.size() == 3 || ((int)pri.size() == 2 && flag == 1)){
				flag = 2;
				break;
			}
		}
		if (flag == 2) continue;// 不是上述三类数
		if ((int)pri.size() == 2){
			Map[make_pair(pri[0],pri[1])]++;
			ans += Map[make_pair(pri[0],pri[1])];
			ans += Map3[pri[0]];
			ans += Map3[pri[1]];
			t[pri[0]]++; t[pri[1]]++;
		}else if (flag == 1){
			Map2[pri[0]]++;
			ans += Map2[pri[0]];
			ans += Map3[pri[0]];
		}else{
			Map3[pri[0]]++;
			tot1++;
			ans += (tot1 - Map3[pri[0]]);
			ans += Map2[pri[0]];
			ans += t[pri[0]];
		} // 计算贡献
		//cout << "i = " << i << ' ' << ans << endl;
	}
	cout << ans << endl;
}
signed main(){
	close();
	init();
	T = 1;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：EternalLabyrinth (赞：0)

### 题意：
给定长度为 $n$ 的序列 $a$。求有多少个点对 $(i,j)(i\leq j)$，使得 $a_i$ 和 $a_j$ 的最小公倍数能且仅能分解出两个质因数（可以相同）。

### 做法：

首先对每个数分解质因数，把其质因数记到一个 vector 里。若 vector 的大小大于等于 $3$，则它没有贡献，直接把它扔了。

下列我说的 $k$ 只是哈希表下标。

开 $3$ 个哈希表。第一个维护有一个质因数且质因数为 $k$ 的数的个数。第二个维护有两个质因数的数，且这个数本身为 $k$ 的个数。第三个维护有两个质因数的数，设这个数能分解为 $p\times q$，那么你让下标为 $p$ 的桶和下标为 $q$ 的桶都加上自己的贡献。

然后分类讨论：

1. 若只有一个因数，那么贡献由两部分组成。一个是包含自己这个数且质因数个数为 $2$ 的数的个数，这个查第三个哈希表。一个是由一个因数组成且不等于自己的数的个数，查第一个哈希表小容斥一下就行。
2. 若有两个因数。设其能分解为 $p\times q$。则其贡献为前面等于 $p$ 的数的个数，前面等于 $q$ 的数的个数，减去前面 $p\times q$ 的数的个数。这个分别查第一个和第二个哈希表就行了。

注意要先把自己的贡献加进去再算此点的答案。其中两个因数的数中，完全平方数较为特殊，只能加一份贡献，也很好处理在此不做展开。

---

## 作者：Lele_Programmer (赞：0)

# CF2065G 题解

## 思路

给定序列 $a$，统计符合下列条件的 $(i,j)$ 的数量：

- $i \le j$
- $\text{lcm}(a_i,a_j)$ 能够表示为以下两种形式之一（$p$ 为质数）：
  - $p_1^2$
  - $p_1p_2$

对于一个 $a_i$，要寻找符合条件的 $a_j$，分下列几种情况讨论（$p$ 为质数）：

1. 若 $a_i$ 可以表示为 $p_1^2$，则 $a_j=a_i$。
2. 若 $a_i$ 可以表示为 $p_1$，则 $a_j=p_1^2$ 或 $a_j=p_2$ 或 $a_j=p_1p_2$，其中 $p_1 \neq p_2$。
3. 若 $a_i$ 可以表示为 $p_1p_2$，则 $a_j=p_1p_2$，其中 $p_1 \neq p_2$，因为 $p_1 = p_2$ 的情况属于第一种情况。

分解质因数，然后开个桶统计数字出现以下就行了，为了方便，可以先忽略 $i \le j$ 的限制，将 $(i,j)$ 和 $(j,i)$ 认为是两种不同方案算进答案，特别地，$i=j$ 的情况也算两次，最后答案取二分之一输出即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int N=200005;

int T,n,a[N];
int pri[N],idx;
bool flag[N];
int hs[N];

void init() {
    _rep(i,2,N-1) {
        if (!flag[i]) pri[++idx]=i;
        _rep(j,1,idx) {
            if (i*pri[j]>=N) break;
            flag[i*pri[j]]=true;
            if (i%pri[j]==0) break;
        }
    }
}

int sieve(int k) {
    int res=k,cnt=0;
    _rep(i,2,sqrt(k)+1) while (k%i==0) k/=i,cnt++;
    if (k!=1) cnt++;
    if (cnt>=3) return -1;
    else return res;
}

i32 main() {
    init();
    read(T);
    while (T--) {
        read(n);
        _rep(i,1,n) read(a[i]),hs[i]=0;
        int cnt1=0;
        _rep(i,1,n) {
            int t=sieve(a[i]);
            if (!~t) continue;
            hs[t]++;
            if (!flag[t]) cnt1++;
        }
        int ans=0;
        _rep(i,1,idx) {
            if (pri[i]>n) break;
            // cout<<"prime "<<pri[i]<<endl;
            if (hs[pri[i]]) {
                _rep(j,1,idx) {
                    if (pri[i]*pri[j]>n) break;
                    ans+=hs[pri[i]]*hs[pri[i]*pri[j]]*2;
                }
                // cout<<"TEST1: "<<ans<<endl;
                ans+=hs[pri[i]]*(cnt1-hs[pri[i]]);
                // cout<<"TEST2: "<<ans<<endl;
            }
            if (pri[i]*pri[i]<=n) ans+=hs[pri[i]*pri[i]]*hs[pri[i]*pri[i]]+hs[pri[i]*pri[i]];
            // cout<<"TEST3: "<<ans<<endl;
        }
        _rep(i,2,n) {
            if (!flag[i]) continue;
            if (!hs[i]) continue;
            int k=sqrt(i);
            if (k*k==i) continue;
            ans+=hs[i]*hs[i]+hs[i];
        }
        writeln(ans/2);
    }
    return 0;
}

/*
1
6
2 2 3 4 5 6
*/
```

---

