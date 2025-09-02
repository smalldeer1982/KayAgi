# 雪玉 (Snowball)

## 题目描述

# [JOI 2021 Final] 雪玉


在一条无限长的数轴上，有 $N$ 个雪球，这 $N$ 个雪球编号为 $1 \sim N$，第 $i$ 个雪球在第 $A_i$ 个点上。刚开始，整条数轴覆盖满了雪，接下来 $Q$ 天将会刮起大风，第 $j$ 天的风力强度为 $W_j$，如果 $W_j$ 为正数，所有雪球都朝右移动 $W_j$ 个单位长度，如果 $W_j$ 为负数，所有雪球都朝左移动 $-W_j$ 个单位长度。

当一个区间 $[a,a+1]$ 被雪覆盖时，雪球滚上去雪球的质量会加一，这一个区间里的雪也会被清空。刚开始每一个雪球的质量均为 $0$，而这 $Q$ 天里也没有再下雪。

你想问这 $Q$ 天结束后每个雪球的质量是怎样的。

## 说明/提示

#### 样例 1 解释

雪球初始位置为 $-2,3,5,8$，初始质量为 $0,0,0,0$。

- 第一天过后，雪球位置为 $0,5,7,10$，质量为 $2,2,2,2$。
- 第二天过后，雪球位置为 $-4,1,3,6$，质量为 $4,4,2,3$。
- 第三天过后，雪球位置为 $3,8,10,13$，质量为 $5,4,2,6$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（33 pts）：$N,Q \le 2000$。
- Subtask 2（67 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le N,Q \le 2 \times 10^5$，$|A_i|,|W_j| \le 10^{12}$，$A_i<A_{i+1}$。


翻译自 [The 20th Japanese Olympiad in Informatics Final Round B 雪玉的英文翻译 Snowball](https://www.ioi-jp.org/joi/2020/2021-ho/2021-ho-t2-en.pdf)。

## 样例 #1

### 输入

```
4 3
-2 3 5 8
2
-4
7```

### 输出

```
5
4
2
6```

## 样例 #2

### 输入

```
1 4
1000000000000
1000000000000
-1000000000000
-1000000000000
-1000000000000```

### 输出

```
3000000000000```

## 样例 #3

### 输入

```
10 10
-56 -43 -39 -31 -22 -5 0 12 18 22
-3
0
5
-4
-2
10
-13
-1
9
6```

### 输出

```
14
8
7
9
11
10
9
8
5
10```

# 题解

## 作者：xyin (赞：4)

[双倍经验](https://www.luogu.com.cn/problem/P7405)

手玩样例，我们能发现一些特殊性质：

* 对于每一个雪球来说，能对它的质量产生贡献的位置和起来是一个**区间**。

顺着这个思路往下想，就能想到对每一个雪球维护一个能延伸到的**最远**的端点值（前提条件是对它的质量有贡献），最终的答案就是 $r_i-l_i$。

怎么维护这个端点值呢？

**解法一**：

考虑枚举天数，根据每一天的风力强度 $W_j$ 和上一次的坐标（设为 $last$）更新 $i$ 的端点值，最后直接输出就行。

记得在更新端点值的时候比较相邻两个雪球的端点值（看是否对 $i$ 产生贡献），判断是否能更新。

此时你有了一份 $O(nq)$ 的代码，得分 $33$ 分，[记录详情](https://www.luogu.com.cn/record/172635700)。

```cpp
signed main(){
	n=read();q=read();
	for (int i=1;i<=n;i++)
	  last[i]=l[i]=r[i]=read();
	for (int i=1;i<=q;i++)
	  w[i]=read();
	for (int i=1;i<=q;i++)//枚举天数 
		for (int j=1;j<=n;j++){//枚举雪球 
	  	last[j]+=w[i];
	  	if (last[j]<l[j]){//如果新的位置小于左端点->“尝试 ”更新 
	  		if (j==1) l[j]=last[j];
	  		else if (last[j]>=r[j-1]) //能更新 
	  		  l[j]=last[j];
	  		else l[j]=r[j-1];//不能 
		  }
		else if (last[j]>r[j]){//如果新的位置大于右端点 
			if (j==n) r[j]=last[j];
			else if (last[j]<=l[j+1])//同上 
			  r[j]=last[j];
			else r[j]=l[j+1];//同上 
		}
	  }
	for (int i=1;i<=n;i++)
	  printf("%lld\n",r[i]-l[i]);
	return 0;
}
```

**解法二**：

考虑能不能优化上述方法，我们其实还能发现一些其它性质：

* 经过 $Q$ 天以后，雪球 $i$ 的运动路径其实是一条**折线**（不断做往复运动），折线的端点其实并没有 $Q$ 这么多。

我们尝试将折线的**几次**沿着直线的运动（不折返）**浓缩**为**一次**，直到它折返。

但这只是我们对常数的小优化，实际复杂度还是 $O(nq)$，别对它报什么期望。得分 $33$ 分，[记录详情](https://www.luogu.com.cn/record/172635333)，能看出确实比之前快了不少（还多过了两个点），但还是 T 了很多点___*( ￣皿￣)/#____。

```cpp
//cnt 记录浓缩后的段数 
//tag的含义：1->此时正在处理>0的数，0->正在处理<=0的数 
signed main(){
	n=read();q=read();
	for (int i=1;i<=n;i++)
	  last[i]=l[i]=r[i]=read();
	for (int i=1,x;i<=q;i++){
		x=read();
		if (i==1) {
			if (x>0) tag=1;
			else tag=0;
			tot+=x;
		}
	  	else if (x<=0){
	  		if (tag==1) 
			  w[++cnt]=tot,tag=0,tot=x;
	  		else tot+=x;
		  }
		else {
			if (tag==1) tot+=x;
			else w[++cnt]=tot,tag=1,tot=x;
		}
	}
	w[++cnt]=tot;
	for (int i=1;i<=cnt;i++)//这一部分与之前一样 
	{
		for (int j=1;j<=n;j++){
	  	last[j]+=w[i];
	  	if (last[j]<l[j]){
	  		if (j==1) l[j]=last[j];
	  		else if (last[j]>=r[j-1]) 
	  		  l[j]=last[j];
	  		else l[j]=r[j-1];
		  }
		else if (last[j]>r[j]){
			if (j==n) r[j]=last[j];
			else if (last[j]<=l[j+1])
			  r[j]=last[j];
			else r[j]=l[j+1];
		}
	  }
	}
	for (int i=1;i<=n;i++)
	  printf("%lld\n",r[i]-l[i]);
	return 0;
}
```

**解法三**：

终于来到了正解，我们考虑能优化哪一维，最终输出答案时你肯定必须枚举雪球（~~怎么都甩不开~~），所以只能在 $q$ 上下功夫。

观察数据范围 $1\le N,Q \le 2\times 10^5$，最终复杂度肯定是 $O(n\log q)$ 的，说实话，看到 $\log$ 你应该考虑考虑**二分**的。

我们来看看答案是否具有二分的性质：

* 端点值的更新肯定是单调的（只会扩张不会缩减）。

* 当某天雪球滚动完之后，若它和它**相邻**的雪球，在左（右）端点值更新时出现了**冲突**之后，该点的左（右）端点值再也不会更新，同样相邻点的右（左）端点值也再也不会更新。

* 当两个相邻的雪球出现冲突时，这段冲突区间到底是谁的贡献（根据风的**正负**）其实很好判断。

有了这几个性质就万事大吉了，我们直接二分冲突时间 $t$ 就行，复杂度 $O(n\log q)$，得分 $100$ 分，[记录详情](https://www.luogu.com.cn/record/172603069)。

代码写得重复啰嗦，马蜂丑陋。

```cpp
int last,q,n,a[maxn],ans1,ans2;
int L[maxn],R[maxn],w[maxn];
bool check1(int x,int i){
	if (a[i-1]+R[x]>a[i]+L[x]) return 0;
	return 1;
}
bool check2(int x,int i){
	if (a[i+1]+L[x]<a[i]+R[x]) return 0;
	return 1;
}
int solve(int i,int k1,int k2){
	int ans=0;
	ans+=R[k2]-L[k1];
	if (i==1) ans+=-L[q];
	else if (k1<q&&w[k1+1]<0)
	  ans+=a[i]+L[k1]-a[i-1]-R[k1];
	if (i==n) ans+=R[q];
	else if (k2<q&&w[k2+1]>0)
	  ans+=a[i+1]+L[k2]-a[i]-R[k2];
	return ans; 
}
signed main(){
	n=read();q=read();
	for (int i=1;i<=n;i++) 
	  a[i]=read();
	for (int i=1;i<=q;i++){
		w[i]=read();last+=w[i];
		R[i]=R[i-1];L[i]=L[i-1];
		if (last>R[i]) R[i]=last;
		else if (last<L[i]) L[i]=last;
	}
	for (int i=1;i<=n;i++){
		ans1=ans2=0;
		if (i!=1){
			int l=1,r=q;
			while (l<=r){
				int mid=(l+r)>>1;
				if (check1(mid,i)) 
				  l=mid+1,ans1=mid;
				else r=mid-1;
			}
		}
		if (i!=n){
			int l=1,r=q;
			while (l<=r){
				int mid=(l+r)>>1;
				if (check2(mid,i))
				  l=mid+1,ans2=mid;
				else r=mid-1;
			}
		}
		printf("%lld\n",solve(i,ans1,ans2));
	}
	return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：3)

一道并不困难的思维题，基本没有考察算法知识。

容易发现，对于雪球 $i$，覆盖的雪是一段连续的区间，且所有的区间的交集为空集。

那么我们希望找到相邻两个区间的交点，不妨记为 $f_i$，表示第 $i$ 个雪球的区间为 $[f_i,f_{i+1}]$，没有交点时另外讨论。

考虑怎么求出 $f_i$。首先我们发现有些移动是无用的，比如先向右移动 $5$，然后再向左移动 $3$。很明显这个向左移动是无用的，需要过滤掉。这个问题的处理是简单的，不再赘述。

再定义两个数组 $l_i$ 和 $r_i$，表示做到第 $i$ 天时雪球最远往左/右移动了多远，方便我们找到交点。

进一步思考，发现当 $l_i+r_i\ge a_x-a_{x-1}$ 时，两个雪球会相交。由于 $l_i+r_i$ 是单调不降的，那么可以通过二分来找到最早两个雪球何时相交，$f_i$ 即可得到。

注意判断没有相交的情况，代码并不难写，时间复杂度 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,inf=1e18+5;
int n,q;
int a[N],l[N],r[N],s[N],f[N],c[N];
signed main()
{
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	int now=0;
	for(int i=1;i<=q;i++)
	{
		int &x=c[i];
		scanf("%lld",&x),now+=x;
		l[i]=l[i-1],r[i]=r[i-1];
		if(now<0)l[i]=max(l[i],-now);
		else r[i]=max(r[i],now);
		s[i]=l[i]+r[i];
	}
	for(int i=2;i<=n;i++)
	{
		int id=upper_bound(s+1,s+1+q,a[i]-a[i-1])-s;
		if(a[i]-a[i-1]>=s[q])
		{
			f[i]=inf;//不相交
			continue;
		}
		if(c[id]>0)f[i]=a[i]-l[id-1];
		else f[i]=a[i-1]+r[id-1];
	}
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		if(i==1)ans+=l[q];
		else ans+=f[i]==inf?l[q]:a[i]-f[i];
		if(i==n)ans+=r[q];
		else ans+=f[i+1]==inf?r[q]:f[i+1]-a[i];
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：sndd (赞：2)

题目链接->[ AT_joi2021ho_b](https://www.luogu.com.cn/problem/AT_joi2021ho_b)

双倍经验->[P7405](https://www.luogu.com.cn/problem/P7405)

## 思路

容易发现每个雪球都可以形成一段区间，区间端点 $R-L$ 的值即为贡献。

于是维护区间端点，每次检查位置是否到了已覆盖区间。

时间复杂度 $O(nq)$，能拿 $33$ 分。

# 优化

因为要求每个点的贡献，所以避免不了枚举 $n$，考虑优化 $q$。

雪球间位置应是两两相对静止，影响区间端点的只有**相邻两区间**的**冲突**。

于是可以**二分**求得两端冲突时间，复杂度 $n \log n$。

具体做法：

*  预处理每个时间的两端点最远相对位移。
*  枚举 $n$，分别用二分求出两端端点的冲突时间。
*  根据冲突时间 $O(1)$ 查询答案。

注：这里查询的时候要看看是谁先覆盖到的。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;

int n,Q;
int pos[N];
int ll[N],rr[N];	//两端点每个时间相对最远位移 
int ans1,ans2;		//分别记录两端点冲突时间 

bool check1(int num,int t){
	return (pos[num]+ll[t]<pos[num-1]+rr[t]);
}
bool check2(int num,int t){
	return (pos[num]+rr[t]>pos[num+1]+ll[t]);
}

int solve(int num,int l,int r){			//O(1)查答案 
	if(l==0) l=pos[num]+ll[Q];
	else l=min(pos[num-1]+rr[l],pos[num]+ll[l-1]);		//这里看看是谁先覆盖然后再加贡献 
	if(r==0) r=pos[num]+rr[Q];
	else r=max(pos[num+1]+ll[r],pos[num]+rr[r-1]);
	return r-l;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>Q;
	for(int i=1;i<=n;i++) cin>>pos[i];
	int now=0;
	for(int i=1,W;i<=Q;i++){			//预处理相对位移 
		cin>>W;
		now+=W;
		ll[i]=ll[i-1],rr[i]=rr[i-1];
		if(now<ll[i]) ll[i]=now;
		if(now>rr[i]) rr[i]=now;
	}
	for(int i=1;i<=n;i++){
		ans1=ans2=0;			//二分冲突时间 
		if(i!=1){
			int l=1,r=Q;
			while(l<=r){
				int mid=(l+r)>>1;
				if(check1(i,mid)){
					ans1=mid;
					r=mid-1;
				}
				else{
					l=mid+1;
				}
			}
		}
		if(i!=n){
			int l=1,r=Q;
			while(l<=r){
				int mid=(l+r)>>1;
				if(check2(i,mid)){
					ans2=mid;
					r=mid-1;
				}
				else{
					l=mid+1;
				}
			}
		}
		cout<<solve(i,ans1,ans2)<<"\n";
	}
	return 0;
}
```

---

## 作者：New_Void (赞：1)

# [AT_joi2021ho_b 雪玉 (Snowball)](https://www.luogu.com.cn/problem/AT_joi2021ho_b)

### 思路

看完题目，我们发现大概思路就是计算每个雪球最终的半径。每个雪球的半径由它在移动过程中未被阻挡的移动距离决定。当两个相邻雪球接触之后，后续的雪球的贡献就不会再进行增加了，贡献转移到相邻的雪球上。关键在于找到每个相邻雪球对的移动范围开始接触的时间，并分别处理该时间点前后的移动贡献。

但是光写暴力肯定是过不了的，所以我们可以用二分冲突时间来进行优化。可能说的比较生涩，请结合代码注释理解。
### Code


```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N=5000005;
long long arr[N],w[N],left1[N],right1[N],ans[N];
long long jc(long long mid,long long i){
    if (right1[mid]-left1[mid]<=arr[i+1]-arr[i]){
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    long long n,q;
    cin>>n>>q;
    w[0]=0;
    right1[0]=0;
    left1[0]=0;
    for (long long i=1;i<=n;i++){
        cin>>arr[i];
    }
    for (long long i=1;i<=q;i++){
        cin>>w[i];
        w[i]+=w[i-1];
        right1[i]=max(right1[i-1],w[i]);
        left1[i]=min(left1[i-1],w[i]);
    }
    for (long long i=1;i<=n;i++){
        long long l=1,r=q,day=0;
        if (i==n){   //最后一个雪球只有右贡献，这里是在判断是否为最后一个雪球
            ans[i]+=right1[q];
        }
        else{
            while (l<=r){  //这里是个优化，是在用二分查找临界点day
                long long mid=(l+r)/2;
                if (jc(mid,i)){ //这里是在检查是否重叠
                    l=mid+1;
                    day=mid;
                }
                else{ //重叠上了，所以右端点要减1，不然就会有重复贡献
                    r=mid-1;
                }
            }
            //当所有天数的移动未导致相邻雪球 i 和 i+1 的覆盖区间重叠时，直接分配它们的贡献。

            if (day==q){  //这里看一下day和q是否相等，一旦相等就证明全部的天数都没有重叠
                ans[i]+=right1[q];
                ans[i+1]-=left1[q]; //因为left[q]是负数，所以减去就是加
            }
            else{
                ans[i]+=right1[day];
                ans[i+1]-=left1[day];
                //处理剩余天数

                if (right1[day]==right1[day+1]){ //如果最后一次是左移
                    ans[i+1]+=min(arr[i+1]-arr[i]-(right1[day]-left1[day]),left1[day]-left1[day+1]);
                }
                else if (left1[day]==left1[day+1]){  //如果最后一次是右移
                    ans[i]+=min(arr[i+1]-arr[i]-(right1[day]-left1[day]),right1[day+1]-right1[day]);
                }
            }
        }
    }
    ans[1]-=left1[q];
    for (long long i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}

```




由于我太蒻了，所以我是看https://www.luogu.com.cn/article/4egz5823 这篇题解来写的，所以思路基本一样。

---

## 作者：ganpig (赞：1)

转换参照系，将雪球移动看成地上的雪移动，问题转化为每一片雪给左边和右边的雪球分别带来多少贡献。

发现只要维护往左和往右移动的最远距离，就能二分找到一片雪被完全消耗完的时间，从而得到答案。

时间复杂度 $O(N \log Q)$。

### $\text{Code}$

```cpp
#include <bits/stdc++.h>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<long long> w(n);
    for (auto &x : w)
        std::cin >> x;
    std::adjacent_difference(w.begin(), w.end(), w.begin());
    w.front() = 1e18;
    w.push_back(1e18);

    std::vector<long long> s(m), ma(m + 1), mi(m + 1), r(m + 1);
    for (auto &x : s)
        std::cin >> x;
    std::partial_sum(s.begin(), s.end(), s.begin());
    for (int i = 1; i <= m; i++)
        ma[i] = std::max(ma[i - 1], s[i - 1]),
        mi[i] = std::min(mi[i - 1], s[i - 1]),
        r[i] = ma[i] - mi[i];

    std::vector<long long> ans(n + 2);
    for (int i = 0; i <= n; i++) {
        int t = std::lower_bound(r.begin(), r.end(), w[i]) - r.begin();
        if (t == m + 1)
            ans[i] += ma.back(), ans[i + 1] -= mi.back();
        else if (ma[t - 1] == ma[t])
            ans[i] += ma[t], ans[i + 1] += w[i] - ma[t];
        else
            ans[i] += w[i] + mi[t], ans[i + 1] -= mi[t];
    }
    for (int i = 1; i <= n; i++)
        std::cout << ans[i] << '\n';
}
```

---

## 作者：liuliucy (赞：1)

显然一个雪球与与他不相邻的雪球无关，因为如果滚到了不相邻雪球的区域，因为雪球间距离不变，他会先被别的雪球滚到，固没有贡献。所以我们只需要考虑相邻雪球间的贡献。

我们只需要注意看相邻两个球相交的区域，因为两个球间距相同，我们只需要找到两个球恰好没有相交的时候，那么下一时刻他们就相交了。

因为 $\max{l_i}$ 和 $\max{r_i}$ 关于时间 $t$ 单调递增，我们考虑二分，找到恰好 $l_i+r_i \le len$ 的时候，将区间内的雪球分配给左右两个点，然后考虑这个时候是往右还是往左，便可以确定剩下的雪去哪了。

## code
talk is cheap,show me the code.
```
#include<bits/stdc++.h>
using namespace std;
int n,q;
#define int long long
int a[200005],w[200005];
int l[200005],r[200005];
int ans[200005];
signed main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	int s=0;
	for(int i=1;i<=q;i++){
		scanf("%lld",&w[i]);
		s+=w[i];
		l[i]=max(l[i-1],-s);r[i]=max(r[i-1],s);
	}
	ans[1]=l[q];ans[n]+=r[q];
	for(int i=2;i<=n;i++){
		int len=a[i]-a[i-1];
		if(l[q]+r[q]<=len){
			ans[i-1]+=r[q];
			ans[i]+=l[q];
			continue;
		}
		int ll=1,rr=q,tp=0;
		while(rr>=ll){
			int mid=ll+rr>>1;
			if(r[mid]+l[mid]<=len){
				tp=mid;
				ll=mid+1;
			}
			else rr=mid-1;
		}
		ans[i-1]+=r[tp];
		ans[i]+=l[tp];
		if(w[tp+1]>0)ans[i-1]+=len-l[tp]-r[tp];
		else if(tp!=n)ans[i]+=len-l[tp]-r[tp];
	}
	for(int i=1;i<=n;i++){
		printf("%lld",ans[i]);
		if(i!=n)putchar('\n');
	}
	return 0;
}
```

---

## 作者：aike_6yoshi9 (赞：0)

首先我们知道我们如果直接模拟肯定是会超时的，所以我们要换一种思虑。  
我们发现每两个雪球之间的线段要么被全部使用，要么被部分使用，如果被部分使用，那么一定是左边一段和右边一段被使用，就很好处理，主要是考虑被全部使用的情况。  
被全部使用的话，一些会分到左边雪球，一些会分到右边雪球，但是又多少会分到左边雪球，有多少会分到右边雪球，这个时候，我们只要找到第一个使得这段区间被使用完的时间点然后根据那一天的风是往哪边吹的就好了，而找的这个过程直接二分就好了。
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=1e6+100;
inline long long read(){
	long long x=0ll,f=1ll;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1*f;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
long long maxv[MAXN][2];//0表示往左能到的最小值，1表示往右能到的最大值 
long long sum[MAXN],ans[MAXN],ww[MAXN],n,q,a[MAXN],w[MAXN];
long long erf(long long x){//记忆二分找到第一个>=x的点 
	long long l=1,r=q,res=-1;
	while(l<=r){
		long long mid=(l+r)>>1;
		if(sum[mid]>=x){
			res=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return res;
}
int main(){
//	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
	n=read(),q=read();
	for(long long i=1;i<=n;i++){
		a[i]=read();
	}
	for(long long i=1;i<=q;i++){
		ww[i]=read();
		w[i]=w[i-1]+ww[i];
		maxv[i][0]=min(maxv[i-1][0],w[i]);
		maxv[i][1]=max(maxv[i-1][1],w[i]);
		sum[i]=abs(maxv[i][0])+maxv[i][1];//左右滚动最大值的和，一定是递增的  
	}
	for(long long i=1;i<n;i++){//i and i+1
		long long c=a[i+1]-a[i];//第i个雪球和第i+1个雪球之前的区间长度，如果左右滚动到的最大值的和大于这个数，那么i到i+1的这个区间就用完了 
		long long id=erf(c);//在sum里找到第一个>=c的值，这个点就是第一个能把区间用完第一个点 
		if(id==-1){//没找到，说明用不完，直接把第i个雪球加上q天过完的往右边滚的最大值，第i+1个雪球加上q天过完的往左边滚的最大值 
			ans[i]+=maxv[q][1];
			ans[i+1]+=abs(maxv[q][0]);
		}
		else if(sum[id]==c){//刚好可以用完，不会出现滚到每个点但是没滚上雪的情况，接把第i个雪球加上id天过完的往右边滚的最大值，第i+1个雪球加上id天过完的往左边滚的最大值 
			ans[i]+=maxv[id][1];
			ans[i+1]+=abs(maxv[id][0]);
		}
		else{
			if(ww[id]>0){//是因为往右滚用完的，所以第i+1个雪球加上往左滚的最大值不受影响，剩下的雪全部给到i就好了 
				ans[i+1]+=abs(maxv[id][0]);
				ans[i]+=c-abs(maxv[id][0]);
			}
			else{//是因为往左滚用完的，所以第i个雪球加上往右滚的最大值不受影响，剩下的雪全部给到i+1就好了 
				ans[i]+=maxv[id][1];
				ans[i+1]+=c-maxv[id][1];
			}
		}
	}
	ans[1]+=abs(maxv[q][0]);ans[n]+=maxv[q][1];
	for(long long i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：naught (赞：0)

# [JOI 2021 Final] 雪玉

## 题目描述

翻译很简洁，不作赘述。

## Solution

对于相邻的两个雪球 $a_i$ 和 $a_{i+1}$，两者夹着的区间中的雪要么是被 $a_i$ 或 $a_{i+1}$ 卷起，要么不可能被清理掉。

那么思路非常简单了，对于每个区间，只有 $2$ 种情况：

* 区间左侧雪球的最右点小于区间右侧雪球的最左点：两侧雪球各自加上自己卷起大小即可。

* 区间左侧雪球的最右点大于等于区间右侧雪球的最左点：二分计算各自卷起雪的多少即可。

其他疑问见代码。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define Maxn 200005
#define fo(i, l, r) for (int i = l; i <= r; ++i)
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read(int x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}
inline ll lread(ll x=0, bool f=0, char c=getchar()) {for(;!isdigit(c);c=getchar()) f^=!(c^45);for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);return f?-x:x;}

int n, m;
ll a[Maxn], l[Maxn], r[Maxn], ans[Maxn], sum;

int main()
{
    n = read(), m = read();
    fo(i, 1, n) a[i] = lread();
    fo(i, 1, m)
    {
        ll x = lread();
        sum += x;
        l[i] = max(l[i-1], -sum), r[i] = max(r[i-1], sum);
    }
    ans[1] += l[m], ans[n] += r[m];
    fo(i, 1, n-1)
    {
        if(l[m] + r[m] <= a[i+1]-a[i]) ans[i] += r[m], ans[i+1] += l[m]; // 两侧雪球没交集。
        else // 有交集。
        {
            int left = 1, right = m, pos = m;
            while(left <= right)
            {
                int mid = (left + right) >> 1;
                if(l[mid] + r[mid] > a[i+1]-a[i]) pos = mid, right = mid-1;
                else left = mid+1;
            }
            // 各自加上卷起的雪。
            if(l[pos-1] == l[pos]) ans[i+1] += l[pos], ans[i] += a[i+1]-a[i]-l[pos];
            else ans[i] += r[pos], ans[i+1] += a[i+1]-a[i]-r[pos];
        }
    }
    fo(i, 1, n) printf("%lld\n", ans[i]);
    return 0;
}
```

## Tips

记得开 `long long`！

---

## 作者：Fla_Akebono (赞：0)

# AT_joi2021ho_b 雪玉

## 题目大意

有 $n$ 个雪球排列在数轴上，第 $i$ 个雪球的编号为 $a_i$。有 $q$ 次操作，每次使得所有雪球向左或右滚动 $w_i$ 个单位长度。起初数轴每个点上都有一层雪，雪球滚上有雪的点时会使自己的质量加一，同时清除该点上的雪。

每个雪球的初始质量均为 $0$，求 $q$ 次操作后每个雪球的质量。

## 题目分析

显然的，暴力枚举每个雪球滚动的路径必定会超时。

观察到当区间 $[l,r]$ 在第 $i$ 次操作后若不存在雪，则后续操作无需计算贡献。同时，由于每个雪球的运动是相同的，**雪球 $i$ 能产生更新的区间仅为 $[a_{i-1},a_{i+1}]$，并且区间 $[a_i,a_{i+1}]$ 能且仅能使雪球 $i$ 和 $i+1$ 更新。**

于是考虑枚举每两个雪球 $i$ 和 $i+1$ 之间的区间 $dis_i$，同时使用数组 $L_i$ 和 $R_i$ 来维护在第 $i$ 次操作后，雪球向左/右方向达到的最大位移。对于每个区间 $dis_i$，若 $dis_i \ge L_p+R_p$，则其一定能对雪球 $i$ 和 $i+1$ 分别产生相当于 $R_p$ 和 $L_p$ 的贡献。

否则，当 $dis_i < L_p+R_p$ 时，考虑搜索第一次使得区间 $dis_i$ 清空的操作 $j$，即使得 $dis_i < L_j+R_j$ 最小的 $j$，由于数组 $L$ 和 $R$ 具有单调性，考虑二分查找 $j$ 或者使用 `stl::set` 查询。

找到符合要求的 $j$ 后，说明在 $j-1$ 次操作后 $L_{j-1}$ 与 $R_{j-1}$ 依然没有“发生冲突”，即 $dis_i \ge L_{j-1}+R_{j-1}$。若 $w_j \ge 0$，则第 $j$ 次操作不会使得 $L_j$ 更新，此时 $dis_j$ 将会对 $i+1$ 产生 $L_j$ 的贡献，而 $dis_i$ 剩下的 $dis_i-L_j$ 将会全部成为 $i$ 的贡献（即“发生冲突”）。此时 $dis_i$ 区间上已经没有雪了，即已经处理完成。

同样地，$w_j<0$ 的情况以相同的方法处理即可。

## 实现细节/警示后人？

使用 `std::set` 预处理的时间复杂度为 $O(n\log n)$，枚举单个区间并使用 $ \operatorname{upper\_bound}$ 计算贡献的最坏时间复杂度是 $O(\log n)$，则总时间复杂度是 $O(n \log n)$。

对于数组 $L$ 和 $R$，请**不要**将其初值赋为 $\textup{\textmd{\texttt{INF/-INF}}}	$，这样会使得在 $L_i/R_i$ 第一次更新之前的值意外的赋为了$\textup{\textmd{\texttt{INF/-INF}}}。$

 _**三年 OI 一场空，不开 long long 见祖宗。**_ 

## CODE

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;
const int MAXN = 2e5 + 5;

int n, q;
long long dat[MAXN], d, con[MAXN], w[MAXN], L[MAXN], R[MAXN];
set<pair<long long, int>> s;

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &dat[i]);
    }
    for (int i = 1; i <= q; i++)
    {
        scanf("%lld", &w[i]);
        d += w[i];
        L[i] = L[i - 1] > d ? d : L[i - 1];
        R[i] = R[i - 1] < d ? d : R[i - 1];
        s.insert(make_pair(R[i] - L[i], i));
    }

    const long long maxl = -L[q], maxr = R[q];
    con[1] += maxl, con[n] += maxr;

    for (int i = 1; i < n; i++)
    {
        long long dis = dat[i + 1] - dat[i];
        if (dis >= maxl + maxr)
        {
            con[i] += maxr, con[i + 1] += maxl;
        }
        else
        {
            int Q = s.upper_bound(make_pair(dis, 0))->second;

            if (w[Q] > 0)
            {
                con[i] += dis + L[Q - 1];
                con[i + 1] += -L[Q - 1];
            }
            else
            {
                con[i] += R[Q - 1];
                con[i + 1] += dis - R[Q - 1];
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        printf("%lld\n", con[i]);
    }

    return 0;
}
```
## THE END
~~不是这样例太水了吧~~

upd 24.9.10 修改了文章标点的使用，修改了部分语句。

---

## 作者：DgNeHzL7777 (赞：0)

## 思路

可以想到，雪球的相对位置是不变的，所以雪球 $i$，雪球 $i+1$ 之间的区域只可能加到雪球 $i$ 和 $i+1$ 的质量上。

我们可以 $O(n)$ 求出第 $i$ 个风刮完之后，每一个雪球向左或向右最多能滚多远。

然后枚举 $\left[1,n-1\right]$ 之间的每一个雪球。

如果风刮完之后，第i个雪球向右滚的长度加上第 $i+1$ 个雪球向左滚的长度不超过 $i$ 和 $i+1$ 之间的长度，那么它们之间互不影响。

否则的话，说明它们之间有影响。我们要求出使它们能够互相影响的第一个风的编号，使用二分。
具体看代码。

## 代码

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 200005
#define R(x) x=read()
#define int long long
using namespace std;

inline int read() {
	int x=0,y=1;
	char e=getchar();
	while(e<'0'||e>'9') {
		if(e=='-')y=-1;
		e=getchar();
	}
	while(e>='0'&&e<='9') {
		x=(x<<3)+(x<<1)+(e^'0');
		e=getchar();
	}
	return x*y;
}
int n,q,x[N];
int l[N],r[N];
int ans[N];
int nw,a[N];
signed main() {
	R(n),R(q);// 读入qwq
	for(int i=1; i<=n; ++i) {
		R(x[i]);
	}
	for(int i=1; i<=q; ++i) {
		R(a[i]);
		nw+=a[i];
		l[i]=min(l[i-1],nw),r[i]=max(r[i-1],nw);//计算每一个雪球向左或向右最多能滚多远
		//向左滚取长度的时候要变号 
	}
	int L=l[q],R=r[q];
	ans[1]+=(-L)/*变号*/,ans[n]+=R;
	//第一个雪球向左滚不受任何影响，最后一个雪球向右滚同理  
	
	for(int i=1;i<n;++i){
		//x[i+1]-x[i]为区间长度 
		if(R-L<=x[i+1]-x[i]) {//i,i+1互不影响 
			ans[i]+=R,ans[i+1]+=(-L);
		} else {
			int ll=1,rr=q,mid,midd=q;//因为l,r都被定义过了,这里用ll、rr表示 
			while(ll<=rr) {//二分 
				mid=ll+rr>>1; 
				if(r[mid]-l[mid]<=x[i+1]-x[i]) {
					ll=mid+1;
				} else {
					midd=mid;
					rr=mid-1;
				}
			}
			if(a[midd]>0) {//向右 
				ans[i]+=(x[i+1]-x[i]+l[midd-1]);
				ans[i+1]+=(-l[midd-1]) ;
			} else {//向左 
				ans[i]+=r[midd-1];
				ans[i+1]+=(x[i+1]-x[i]-r[midd-1]);
			}
		}
	}
	for(int i=1; i<=n; ++i) {
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

大水题。但是水平就是不够，就是没能写出来啊。

~~写出来就解锁新成就：AK 一次 CSP-S 模拟赛~~

容易发现初始 $i$ 点和 $i+1$ 点之间的地方只有 $i$ 和 $i+1$ 才可能清扫到。因此考虑计算相邻两个点 $i$ 和 $i+1$ 对答案的贡献。

因此分类讨论：如果 $i$ 和 $i+1$ 之间的空隙没有被用完那么就是每一边走了多少就是多少，否则二分出最后一次对区间有贡献的操作然后计算一下即可。时间复杂度为  $O(n\log n)$。

```cpp
const int N=1000100,mod=998244353;
int zuo[N],you[N],res[N],a[N];
signed main(){
	int n,m;cin>>n>>m;
	F(i,1,n)cin>>a[i];
	int p=0;
	F(i,1,m){
		int x;cin>>x;
		p+=x;
		zuo[i]=max(zuo[i-1],-p);
		you[i]=max(you[i-1],p);
	}
	res[1]+=zuo[m];
	res[n]+=you[m];
	F(i,1,n-1){
		if(zuo[m]+you[m]<=a[i+1]-a[i]){
			res[i]+=you[m];
			res[i+1]+=zuo[m];
		}else{
			int l=1,r=m,best=m;
			while(l<=r){
				int mid=l+r>>1;
				if(zuo[mid]+you[mid]>a[i+1]-a[i])
					best=mid,r=mid-1;
				else
					l=mid+1;
			}
			if(zuo[best-1]==zuo[best]){
				res[i+1]+=zuo[best];
				res[i]+=a[i+1]-a[i]-zuo[best];
			}else{
				res[i]+=you[best];
				res[i+1]+=a[i+1]-a[i]-you[best];
			}
		}
	}
	F(i,1,n)
		cout<<res[i]<<'\n';
	return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
看完题目，不难发现对于一个位置的雪，只有可能被它初始位置相邻的两个雪球所合并，因为雪球是一起移动的，如果当前位置被其他雪球覆盖，那必定先前被其他节点覆盖。

于是我们考虑二分，求一个前缀和，并求当前位置前后的最远点，二分**当前雪球前面的雪堆恰好不被前面的雪球覆盖（就是不交叉）**，对应的 $q_i$ 值。

但这样可能会有一段区间取不到，于是便看 $q_{i+1}$ 是减少还是增加，即可判断是属于前还是后（根据前面二分的定义，必然能保证这一段的雪球是取完的，$i=n$ 时除外）。

思想比较抽象，请读者结合代码理解。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[5000005],w[5000005],maxn[5000005],minn[5000005],ans[5000005],n,q,l,r,mid,res;
bool check(long long x,long long i)
{
	if(maxn[x]-minn[x]<=a[i+1]-a[i]) return 1;
	else return 0;
}
int main()
{
    cin>>n>>q;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=q;i++) 
    {
        scanf("%lld",&w[i]);
        w[i]+=w[i-1];
        maxn[i]=max(maxn[i-1],w[i]);
        minn[i]=min(minn[i-1],w[i]);
    }
    for(int i=1;i<=n;i++)
    {
        l=1,r=q,res=0;
        if(i==n)
        {
            ans[i]+=maxn[q];
            continue;
        }
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(check(mid,i)) l=mid+1,res=mid;
            else r=mid-1;
        }
        if(res==n) ans[i]+=maxn[res],ans[i+1]-=minn[res];
        else
        {
            ans[i]+=maxn[res],ans[i+1]-=minn[res];
            if(maxn[res]==maxn[res+1]) ans[i+1]+=min(a[i+1]-a[i]-maxn[res]+minn[res],minn[res]-minn[res+1]);
            else if(minn[res]==minn[res+1])ans[i]+=min(a[i+1]-a[i]-maxn[res]+minn[res],maxn[res+1]-maxn[res]);
        }
    }
    ans[1]-=minn[q];
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
}
```

---

## 作者：tyukp233 (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P7405)

***

### 定义：
$$pos_i=\sum_{k=1}^{i}W_k$$
$$L_i=\min_{0\le k\le i}pos_k$$
$$R_i=\max_{0\le k\le i}pos_k$$
$$X_i=A_{i+1}-A_i$$
其中 $X_i$ 为初始位置为 $A_i$ 与 $A_{i+1}$ 的雪球间隔的大小，后文对当前雪球均只考虑该间隔。以 $m$ 代指题中的 $Q$。

***

### 本题从间隔入手。

#### 考虑雪球间隔足够大的时候，

手动模拟可知，雪球 $i$ 滚过的区域 $[A_i+L_m,A_i+R_m]$，此时 $X_i\ge R_m-L_m$。

#### 当间隔较小时，

注意到雪球之间相对位置不变，故当前雪球能够到达的区域，若被不相邻的雪球滚过，则一定被相邻的雪球滚过。下面只考虑相邻雪球的影响。

雪球 $i$ 会在某一次移动后到达相邻雪球滚过的区域，记该次移动为第 $t$ 次，则 $R_{t-1}-L_{t-1}<X_i$ 且 $R_t-L_t\ge X_i$。

由定义，$t$ 关于 $X_i$ 是不减的，我们可以对 $X_i$ 进行排序，然后枚举 $t$。

令 $W_t>0$，我们有 $R_t> R_{t-1}$。此前雪球 $i$ 滚过 $[A_i,A_i+R_{t-1}]$ 的区域，雪球 $i+1$ 滚过 $[A_{i+1}+L_{t-1},A_{i+1}]$ 的区域，两区域不相交。故雪球 $i$ 新增的区域为 $[A_i+R_{t-1},A_{i+1}+L_{t-1}]$。

即雪球 $i$ 在间隔 $X_i$ 中占有 $[A_i,A_{i+1}+L_{t-1}]$，而雪球 $i+1$ 占有 $[A_{i+1}+L_{t-1},A_{i+1}]$。将该部分加到答案里。

$W_i<0$ 的情况同理。

另外，对于雪球 $1$ 和雪球 $n$，我们额外计算 $L_m$ 和 $R_m$ 即可。

***

该算法的时间复杂度为 $O(n\log n+m)$，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
int n,m,pt=1;
ll pos=0;
ll L,R;
ll a[N],b[N];
pair<ll,int> mid[N];
ll ans[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	for(int i=1;i<n;i++)mid[i]={a[i+1]-a[i],i};
	sort(mid+1,mid+n);
	for(int i=1;i<=m;i++){
		pos+=b[i];
		L=min(L,pos);
		R=max(R,pos);
		while(pt<n&&mid[pt].first<=R-L){
			if(b[i]>0){
				ans[mid[pt].second+1]+=(-L);
				ans[mid[pt].second]+=(mid[pt].first+L);
			}else {
				ans[mid[pt].second]+=R;
				ans[mid[pt].second+1]+=(mid[pt].first-R);
			}
			pt++;
		}
	}
	while(pt<n){
		ans[mid[pt].second]+=R;
		ans[mid[pt].second+1]+=(-L);
		pt++;
	}
	ans[1]+=(-L);
	ans[n]+=R;
	for(int i=1;i<=n;i++)cout<<ans[i]<<"\n";
}
```

---

## 作者：P7GAB (赞：0)

### 思路

由于雪球之间的相对位置是不会改变的，所以对于一个雪球，越过相邻的雪球的初始位置一定不会令其变大。

如果雪球的滚动范围没有交集，答案显然就是区间长度。但如果有了交集，我们必须判断哪个雪球先滚到，一个区间便分为了分属左右两雪球的两个区间，于是就要找出两边最后一次不交的那个断点。

由于断点具有单调性，直接二分启动。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxn=2e5+5;
ll n,q;
ll a[maxn],w[maxn];
ll L[maxn],R[maxn],ans[maxn];
void solve(ll x,ll len) {
	if(L[q]+R[q]<=len) {
		ans[x]+=R[q];
		ans[x+1]+=L[q];
		return;
	}
	ll l=1,r=q;
	while(l<r) {
		ll mid=(l+r)/2;
		if(L[mid]+R[mid]>len)
			r=mid;
		else
			l=mid+1;
	}
	if(L[l]==L[l-1]) {
		ans[x]+=len-L[l];
		ans[x+1]+=L[l];
	} else {
		ans[x]+=R[l];
		ans[x+1]+=len-R[l];
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(ll i=1; i<=n; i++)
		cin>>a[i];
	ll sum=0;
	for(ll i=1; i<=q; i++) {
		cin>>w[i];
		sum+=w[i];
		L[i]=max(L[i-1],-sum),R[i]=max(R[i-1],sum);
	}
	ans[1]+=L[q],ans[n]+=R[q];
	for(ll i=1; i<n; i++)
		solve(i,a[i+1]-a[i]);
	for(ll i=1; i<=n; i++)
		cout<<ans[i]<<endl;
	return 0;
}
```

---

