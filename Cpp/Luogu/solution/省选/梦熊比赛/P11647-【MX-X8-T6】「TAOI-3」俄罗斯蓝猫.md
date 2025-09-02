# 【MX-X8-T6】「TAOI-3」俄罗斯蓝猫

## 题目背景

原题链接：<https://oier.team/problems/X8G>。

---

由于洛谷有特殊的交互题机制，你不需要也不应该在文件开头包含 `kiwi.h`，而是把以下语句复制在文件开头：

```cpp
#include<vector>
std::vector<long long> game(int n);
std::vector<long long> ask(std::vector<int> x,std::vector<int> y);
```


---

小千绘莉想和你玩游戏！

## 题目描述

小千藏有 $n$ 个在 $[0,10^{18}]$ 中间**随机生成**的非负整数 $a_0,a_1,\dots,a_{n-1}$。

你一组询问可以向小千给出不超过 $2n$ 个二元组 $(x_0,y_0),(x_1,y_1),\dots,(x_{m-1},y_{m-1})$，假设 $b_i=a_{x_i}+a_{y_i}$，小千会告诉你 $b_0,b_1,\dots,b_{m-1}$ **从小到大排序**后的结果。

你可以向小千提出不超过 $n$ 组询问，你需要**按顺序**返回 $a_0,a_1,\dots,a_{n-1}$。

需要注意的是：

- 如果你一次询问提出大于 $2n$ 个二元组，或者提出了大于 $n$ 次询问，你会获得 $0$ 分。
- 小千不喜欢重复，如果你某次询问的某个二元组有 $x_i=y_i$，或者有某个**无序对** $(x_i,y_i)$ 被询问了多次（在一组询问间或两组不同的询问之间）。小千都会扣除部分分数。
- 具体评分标准见下面【**评分标准**】。
- **请不要在标准输出输出任何内容**。否则视为攻击交互库。会被判定为 Wrong Answer。

## 说明/提示

**【评分标准】**

**本题首先会受到和传统相同的限制**。例如编译错误会导致整道题目得 $0$ 分，运行时错误、超过时间限制、超过空间限制都会导致相应测试点得 $0$ 分。选手只能在程序中访问自己定义的和交互库给出的变量或数据，及其相应的内存空间。尝试访问其他位置空间将可能导致编译错误或运行错误。

假设该测试点满分为 $P$。

- 如果你违反了上述 Wrong Answer 的规则，或者在标准输出中输出了内容，会直接得 $0$ 分。
- 如果你某次调用 `ask` 时 $x_i=y_i$ 则 $C_1=0.8$，否则 $C_1=1$；
- 如果你调用 `ask` 时，询问了两组相同的 $\{x_i,y_i\}$ 则 $C_2=0.7$，否则 $C_2=1$；
- 假设你一共调用了 $A$ 次 `ask`，则：
	- 如果 $0\leq A\leq 2$，则 $C_3=1$；
   - 如果 $A=3$，则 $C_3=0.8$；
   - 如果 $A=4$，则 $C_3=0.6$；
   - 如果 $5\leq A\leq 10$，则 $C_3=0.4$；
   - 如果 $11\leq A$，则 $C_3=0.2$。
- 假设你调用 `ask` 时，$x$ 数组的**最大长度**为 $B$，则：
	- 如果 $1\leq B\leq n-1$，则 $C_4=1$；
   - 如果 $B=n$，则 $C_4=0.9$；
   - 如果 $B=n+1$，则 $C_4=0.8$；
   - 如果 $B=n+2$，则 $C_4=0.7$；
   - 如果 $n+3\leq B\leq n+20$，则 $C_4=0.6$；
   - 如果 $n+21\leq B$，则 $C_4=0.5$。
   
本测试点的最终得分为所有 `game` 函数，$P\times C_1\times C_2\times C_3\times C_4$ 最小值**向下取整**。

**【数据范围】**

对于所有数据，保证 $T=20$，$5\leq n\leq 500$。

- 测试点 1（30 分）：$n=5$。
- 测试点 2（30 分）：$n=50$。
- 测试点 3（40 分）：$n=500$。

# 题解

## 作者：_lmh_ (赞：2)

不妨假设所有 $a_i$ 和 $a_i+a_j$ 互不相等，数据随机，显然冲突的概率极低。

正解数据范围：$n\ge 5$，两次询问，每次询问不超过 $n-1$ 个点对，所有点对互不相等。

一个想法是第一次问一个菊花，第二次问一个环，但这样只能确定第一个位置的值，以及后面的位置组成的集合。

考虑把环上 $(1,2)$ 的询问和菊花上 $(0,n-1)$ 的询问交换，这样只要我们能够正确地把它们换回来，就能用这个信息唯一确定环上节点的顺序。

正确地把它们换回来的方法也很简单，就是枚举所有可能的方案，首先 $a_0$ 需要是整数，其次后面的部分需要能够正确地连成一个环，最后这个环上需要有相邻的 $(1,2)$ 和 $n-1$。

直接做似乎是 $O(n^4)$ 的，不可接受。然而，第一步的正确概率在 $\frac{1}{n}$ 级别，这样复杂度就优化到了 $O(n^3)$；同时，如果发现连不成环可以在循环中途跳出，因此这个复杂度跑不满。

正确率我不太会算，但数据范围 $n=500,V=10^{18},T=20$，这样的话 $\frac{n^5}{V}$ 级别的错误概率也是可以接受的；同时，在本地用 `0x66CCFF` 的种子随机了 $2\times 10^5$ 组极限数据全部正确，所以没啥过不去的道理。

```cpp
#include"kiwi.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=507;
ll to[N][N],deg[N],U,V;
unordered_map<ll,ll> mp;
__int128 sA,sB;
vector<ll> game(int n){
	vector<ll> ans(n,0),A,B;
	vector<int> qx(n-1),qy(n-1);
	for (int i=1;i<n-1;++i) qy[i-1]=i;
	qx[n-2]=1;qy[n-2]=2;
	A=ask(qx,qy);
	qy[n-2]=n-1;
	for (int i=1;i<n-2;++i){
		qx[i]=i+1;qy[i]=i+2;
	}
	qy[0]=n-1;
	B=ask(qx,qy);
	sA=sB=0;
//	for (int i=0;i<n-1;++i) cout<<A[i]<<' ';cout<<endl;
//	for (int i=0;i<n-1;++i) cout<<B[i]<<' ';cout<<endl;
	for (int i=0;i<n-1;++i){
		sA+=A[i];sB+=B[i];
	}
	for (int i=0;i<n-1;++i) for (int j=0;j<n-1;++j){
		__int128 sumA=sA-A[i]+B[j],sumB=sB-B[j]+A[i];
		if ((sumB%2==0)&&(sumA-sumB/2)%(n-1)==0){
			ans[0]=(sumA-sumB/2)/(n-1);
//			cout<<i<<' '<<j<<' '<<ans[0]<<endl;
			swap(A[i],B[j]);
//			for (int i=0;i<n-1;++i) cout<<A[i]<<' ';cout<<endl;
//			for (int i=0;i<n-1;++i) cout<<B[i]<<' ';cout<<endl;
			for (int k=1;k<n;++k) deg[k]=0;
			int cnt=0;mp.clear();
			for (int k=0;k<n-1;++k) mp[B[k]]=k;
			bool fl=1;
			for (int o=1;o<n;++o){
				for (int p=o+1;p<n;++p) if (mp.find(A[o-1]+A[p-1]-2*ans[0])!=mp.end()){
					++cnt;
					to[o][deg[o]++]=p;to[p][deg[p]++]=o;
					if (mp[A[o-1]+A[p-1]-2*ans[0]]==j) U=o,V=p;
				}
				if (deg[o]!=2){
					fl=0;break;
				}
			}
			if (!fl){
				swap(A[i],B[j]);continue;
			}
			if ((to[V][0]^to[V][1]^U)==i+1) swap(U,V);
			if ((to[U][0]^to[U][1]^V)!=i+1){
				swap(A[i],B[j]);
				continue;
			}
			ans[n-1]=A[i]-ans[0];
			ans[1]=A[U-1]-ans[0];
			ans[2]=A[V-1]-ans[0];
			for (int i=3;i<n-1;++i){
				U=to[V][0]^to[V][1]^U;swap(U,V);
				ans[i]=A[V-1]-ans[0];
			}
			return ans;
		}
	}
	return vector<ll>(n,-1);
}
```

---

## 作者：dspt (赞：1)

比较简单的做法。

满分做法要求：
+ $5\le n\le 500$
+ 不超过两次询问
+ 每次询问不超过 $n-1$ 个二元组
+ 不能重复询问一个二元组多次
+ 二元组两个元素不能相同

不妨先满足条件一二五，放宽条件三四，因为条件一二五不好卡，条件三四可以卡。

两次询问容易想到一次菊花一次环，二元组数量分别为 $n-1$ 和 $n$。

&nbsp;
### 做法一

**菊花**：$\forall1\le i<n$，询问 $(0,i)$。

**环**：$\forall1\le i<n$，询问 $(i-1,i)$，另外再询问 $(0,n-1)$。

通过菊花的返回值，容易获知 $(n-2)a_0+\sum a_i$。

通过环的返回值，容易获知 $\sum a_i$。

这两个值可以进一步得到 $a_0$ 和 $\set{a_1,\dots,a_{n-1}}$。

由于 $n\le 500$ 对于 $[0,10^{18}]$ 的值域十分稀疏，可以认为任意两个数的和不会相同。

在 $\set{a_1,\dots,a_{n-1}}$ 中枚举 $a_1$，判定标准就是 $a_0+a_1$ 出现在环的返回值中，紧接着就可以枚举确定 $a_2$，依次类推。

此做法时间复杂度 $O(n^2)$。存在的问题是：在第一次枚举中可能枚举到 $a_{n-1}$，导致 $a_1\sim a_{n-1}$ 整体翻转。

&nbsp;
### 做法二

为了对 $a_1$ 和 $a_{n-1}$ 加以区分，稍稍修改询问，并使其满足条件三。

**菊花**：$\forall1\le i<n$，询问 $(0,i)$。

**链**：$\forall1\le i<n$，询问 $(i-1,i)$。

环的询问被改为链的询问。信息 $\sum a_i$ 仍然是必需的，所以可以在菊花的返回值中枚举哪一个返回值对应着 $a_0+a_{n-1}$。随后再套用做法一。

此做法时间复杂度 $O(n^3)$。存在的问题是：二元组 $(0,1)$ 在两次询问中同时出现了。

&nbsp;
### 做法三

在菊花的询问中去掉 $(0,1)$，使其满足条件四。

**菊花**：$\forall2\le i<n$，询问 $(0,i)$。

**链**：$\forall1\le i<n$，询问 $(i-1,i)$。

再模仿做法二解决问题的办法绕一步：在链的返回值中枚举哪一个返回值对应着 $a_0+a_1$。随后再套用做法二。

此做法时间复杂度 $O(n^4)$。

可以加点剪枝。注意到 $a_0$ 有整数解的条件为 $(n-2)a_0+\sum a_i-\sum a_i$ 是 $n-2$ 的倍数。这个条件随机情况下成立的概率很小，所以实际效率类似于时间复杂度 $O(n^3)$。

---

## 作者：operator_ (赞：0)

# P11647 【MX-X8-T6】「TAOI-3」俄罗斯蓝猫

[题目传送门](https://www.luogu.com.cn/problem/P11647)

首先我们的第一反应肯定是先问菊花再问链/环，然而这样你发现除了 $a_0$ ，其他只能知道权值集合而无法配对。

还是考虑先问菊花（$0$ 连向 $1\to n-1$）再问链（从 $1\to n-1$），你发现麻烦之处在于我们不知道链的两端哪个是 $1$，哪个是 $n-1$。于是考虑把 $0$ 也加进链里，这样就可以确定链的开头了，但是 $(0,1)$ 问了两次，怎么办呢？很简单，第一次不问$(0,1)$ 就行了，也没规定必须要 $n-1$ 个对。

现在的流程如下：

+ 确定 $a_0$：方法很多，这里用了一个奇怪的方式，暴力枚举所有 $i,j,k$，取 $ans1_i+ans1_j-ans2_k$ 的众数，即为 $a_0$ 的两倍。这是 $O(n^3\log n)$ 的，但你注意到其出现次数是 $O(n)$ 级别，而其他都是 $O(1)$，所以当一个数出现次数 $>C$ 时就可以停了，期望大概是 $O(n^2\log V)$ 级别。
+ 确定 $a_1,a_2$：此时得到了 $a_2$ 到 $a_{n-1}$ 的集合，枚举所有 $ans2_i$，如果其可以被表示为 $ans1_u+ans1_v-2a_0$，则将 $u,v$ 连边。最终只会剩下 $(0,1)$ 和 $(1,2)$（因为不知道 $a_1$）。找到这两个数之后（记作 $x,y$），我们再枚举所有 $ans1_i$，若有 $x+ans1_i-2a_0=y$ 或 $y+ans1_i-2a_0=x$，则我们就分辨出了这两个数，而且 $ans1_i$ 对应的一定是 $(0,2)$ 的询问。
+ 最后，按照链递推出 $a_3\to a_{n-1}$ 即可。

本做法的缺点：时间复杂度较高，**常数 $C$ 的值需要根据 $n$ 来修改**，而且我不会分析概率。本做法的优点：第一次只需要 $n-2$ 次询问，且基本没有 corner case。

代码：

```cpp
//Date: 2025-01-31 21:32:26
#include<vector>
std::vector<long long> game(int n);
std::vector<long long> ask(std::vector<int> x,std::vector<int> y);
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P emplace_back
#define CLEAR(a,v) memset(a,(v),sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
std::vector<long long> game(int n) {
	map<ll,int> vis;map<ll,pair<int,int>> mp;vector<int> p,q,g[505];vector<ll> a,b,ans;
	int flag=0,x=-1,y=-1,z=-1,lst=-1;ans.resize(n);
    rep(i,2,n-1) p.P(0),q.P(i);a=ask(p,q);p.clear(),q.clear();rep(i,1,n-1) p.P(i-1),q.P(i);b=ask(p,q);
	rep(i,0,a.size()-1) if(!flag) rep(j,i+1,a.size()-1) if(!flag) rep(k,0,b.size()-1) if(!flag)
    	{ans[0]=a[i]+a[j]-b[k];if(ans[0]>=0&&ans[0]%2==0&&++vis[ans[0]]>=(n==5?2:3)) flag=1;}
	ans[0]/=2;rep(i,0,a.size()-1) a[i]-=ans[0];rep(i,0,a.size()-1) rep(j,i+1,a.size()-1) mp[a[i]+a[j]]={i,j};
    rep(i,0,b.size()-1) {
        if(!mp.count(b[i])) {if(x==-1) x=i;else y=i;continue;}
        int u=mp[b[i]].first,v=mp[b[i]].second;g[u].P(v),g[v].P(u);
    }
    rep(i,0,a.size()-1) {if(b[x]+a[i]-ans[0]==b[y]) z=i;if(b[y]+a[i]-ans[0]==b[x]) swap(x,y),z=i;}
    ans[1]=b[x]-ans[0],ans[2]=b[y]-ans[1];rep(i,3,n-1) for(int t:g[z]) if(t!=lst) {lst=z,z=t,ans[i]=a[z];break;}
    return ans;
}
```

---

## 作者：AKPC (赞：0)

好题。

考虑这样一个构造方案：

- 第一次询问 $\{(0,1),(0,2),(0,3)\}\cup\{(i-1,i)\mid i\in[4,n-1]\}$。
- 第二次询问 $\{(1,2),(2,3),(1,3)\}\cup\{(1,i)\mid i\in[4,n-1]\}$。

记 $\operatorname{sum}(x,y)$ 表示 $a_x+a_y$ 的值。

容易发现，如果我们知道了 $a_1$ 这个值是多少，那么只需要将第二次询问的结果正确分配，$a_4,a_5,\dots,a_{n-1}$ 的值便全部被确定。

因为本题数据在 $[0,10^{18}]$ 范围内随机，所以有个很强的性质，就是 $\operatorname{sum}(x_0,y_0)=\operatorname{sum}(x_1,y_1)$ 这个条件在 $x_0\neq x_1$ 或 $y_0\neq y_1$ 的条件下达成的概率极低，减法是同理的。

把这两次询问返回结果的数列两两求和，，因为 $\operatorname{sum}(0,1)+\operatorname{sum}(2,3)=\operatorname{sum}(0,2)+\operatorname{sum}(1,3)=\operatorname{sum}(0,3)+\operatorname{sum}(1,2)$，且有上述性质，$a_0+a_1+a_2+a_3$ 这个值在这 $(n-1)^2$ 个和里面出现次数是最多的，所以容易找出 $\{\operatorname{sum}(0,1),\operatorname{sum}(0,2),\operatorname{sum}(0,3)\}$ 和 $\{\operatorname{sum}(1,2),\operatorname{sum}(2,3),\operatorname{sum}(1,3)\}$ 这两个无序集合。

因为 $\operatorname{sum}(1,2)+\operatorname{sum}(2,3)+\operatorname{sum}(1,3)=2(a_1+a_2+a_3)$，而 $\operatorname{sum}(0,1)+\operatorname{sum}(0,2)+\operatorname{sum}(0,3)=3a_0+(a_1+a_2+a_3)$，所以可以直接求出 $a_0$ 的值以及 $\{a_1,a_2,a_3\}$ 这个无序集合。

为了分别求出 $a_1,a_2,a_3$，而 $\operatorname{sum}(3,4)-\operatorname{sum}(1,4)=a_3-a_1$，考虑在 $\{(i-1,i)\mid i\in[4,n-1]\}$ 以及 $\{(1,i)\mid i\in[4,n-1]\}$ 这两个询问返回的结果（需要分别把 $\{(0,1),(0,2),(0,3)\}$ 和 $\{(1,2),(2,3),(1,3)\}$ 从结果里面提前去掉）找到 $\operatorname{sum}(3,4)$ 和 $\operatorname{sum}(1,4)$。还是考虑在两个返回数列中各选一个相减，极大概率会只有一种选取方案使得两两相减的结果是 $a_3-a_1$。可以在 $a_1,a_2,a_3$ 这三个数中枚举全排列，然后看是否存在一种合法的选取方案使得相减后结果是 $a_3-a_1$，如果有，那 $a_1,a_2,a_3$ 就可以确定了，出错几率很低，因为前面的性质。

接下来确定剩下的所有数，以 $a_4$ 为例。仍然是两个返回结果中各选一个枚举，如果差是 $a_3-a_1$，则这两个结果大概率就是 $\operatorname{sum}(3,4)$ 和 $\operatorname{sum}(1,4)$ 了。后面的数也是以此类推。

复杂度瓶颈在于最后确定所有数的值，所以是 $\Theta(n^3)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fr first
#define sc second
vector<ll>game(int n);
vector<ll>ask(vector<int>x,vector<int>y);
void del(vector<ll>&x,ll k){
    vector<ll>rs;
    bool sb=1;
    for (auto i:x){
        if (sb&&i==k) sb=0;
        else rs.push_back(i);
    }
    x=rs;
}
vector<ll>game(int n){
    vector<int>a1,a2,b1,b2;
    vector<ll>r1,r2,ans(n,0),v123;
    a1={0,0,0},a2={1,2,3};
    for (int i=3;i<n-1;i++)
        a1.push_back(i),a2.push_back(i+1);
    r1=ask(a1,a2);
    b1={1,2,3},b2={2,3,1};
    for (int i=4;i<n;i++)
        b1.push_back(1),b2.push_back(i);
    r2=ask(b1,b2);
    map<ll,vector<pair<ll,ll> > >mp;
    ll mx=0,id=0;
    for (auto i:r1)
        for (auto j:r2){
            mp[i+j].push_back({i,j});
            if (mp[i+j].size()>mx){
                mx=mp[i+j].size();
                id=i+j;
            }
        }
    ll s123=0;
    for (auto i:mp[id]){
        ll x=i.fr,y=i.sc;
        ans[0]+=x,s123+=y;
        del(r1,x),del(r2,y);
    }
    s123>>=1;
    ans[0]=(ans[0]-s123)/3ll;
    for (auto i:mp[id])
        v123.push_back(i.fr-ans[0]);
    bool sb=1;
    for (int i=0;i<=2&&sb;i++)
        for (int j=0;j<=2&&sb;j++){
            if (i==j) continue;
            for (auto x:r1){
                for (auto y:r2)
                    if (x-y==v123[i]-v123[j]){
                        sb=0;
                        ans[1]=v123[j];
                        ans[3]=v123[i];
                        ans[2]=v123[3-i-j];
                        break;
                    }
                if (!sb) break;
            }
        }
    for (int i=4;i<n;i++){
        bool sb=1;
        ll tx=0,ty=0;
        for (auto x:r1){
            for (auto y:r2)
                if (x-y==ans[i-1]-ans[1]){
                    sb=0,tx=x,ty=y;
                    break;
                }
            if (!sb) break;
        }
        del(r1,tx),del(r2,ty);
        ans[i]=tx-ans[i-1];
    }
    return ans;
}
```

---

