# Serval and Colorful Array (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本的区别在于此版本中 $n \leq 4 \cdot 10^5$。仅当您解决了该问题的所有版本时才能进行 hack。

Serval 有一个魔法数 $k$（$k \geq 2$）。我们称数组 $r$ 为 colorful 当且仅当：
- $r$ 的长度为 $k$，且
- $1$ 到 $k$ 之间的每个整数在 $r$ 中恰好出现一次。

给定一个由 $n$ 个介于 $1$ 到 $k$ 的整数组成的数组 $a$。保证 $1$ 到 $k$ 之间的每个整数在 $a$ 中至少出现一次。您可以对 $a$ 执行以下操作：
- 选择一个下标 $i$（$1 \leq i < n$），然后交换 $a_i$ 和 $a_{i+1}$。

求使得 $a$ 中至少存在一个 colorful 子数组$^{\text{∗}}$所需的最小操作次数。可以证明在题目约束下这总是可行的。

$^{\text{∗}}$数组 $b$ 是数组 $a$ 的子数组，当且仅当 $b$ 可以通过从 $a$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 说明/提示

第一个测试案例中，由于子数组 $[a_1, a_2] = [1, 2]$ 和 $[a_2, a_3] = [2, 1]$ 已经是 colorful 的，因此无需执行任何操作。答案为 $0$。

第二个测试案例中，我们可以交换 $a_1$ 和 $a_2$ 得到 $[1, \underline{2, 1, 3}, 1, 1, 2]$，其中包含一个 colorful 子数组 $[a_2, a_3, a_4] = [2, 1, 3]$。由于原数组初始时没有 colorful 子数组，因此答案为 $1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
6
3 2
1 2 1
7 3
2 1 1 3 1 1 2
6 3
1 1 2 2 2 3
6 3
1 2 2 2 2 3
10 5
5 1 3 1 1 2 2 4 1 3
9 4
1 2 3 3 3 3 3 2 4```

### 输出

```
0
1
2
3
4
5```

# 题解

## 作者：donaldqian (赞：4)

## 题意
给定一个长为 $n$ 的数组 $a$，且 $a_i\isin[1,k]$。\
问至少需要交换多少次相邻两项，才能使 $a$ 存在一个长为 $k$ 的子段是 $1$ 到 $k$ 的排列。\
$k\le n\le 4\times 10^5$，且保证 $[1,k]$ 内的每个数字都在 $a$ 中出现过。\
这篇题解是 [官方题解](https://codeforces.com/blog/entry/140933) 做法。
## 弱化版做法
考虑 $k\le n\le 3000$ 时怎么做。

假设我们选出了一些位置，这些位置上的数构成了一个 $1$ 到 $k$ 的排列。现在我们希望用最少的交换次数，让这些数形成一个子段（靠拢起来）。显然，我们会让两边的数向中间靠拢，中间的数（也就是第 $\frac{k}{2}$ 个数）不动。

那么我们考虑枚举中间的数（也就是区间中点）在哪里，假设当前枚举到的点是 $pos$。那么相当于我们要在 $[1,pos-1]$ 里选 $\frac{k}{2}$ 个点，$[pos+1,n]$ 里选 $\frac{k}{2}$ 个点，且这些点的值两两不同，最小化每个点到 $pos$ 的距离的和。

我们设 $l_i$ 表示 $pos$ 往左扫第一个 $i$ 的位置，$r_i$ 表示 $pos$ 往右扫第一个 $i$ 的位置，问题转化成了：对于每个 $1\le x\le k$ 选择 $l_x$ 或 $r_x$，要求最后一共选 $\frac{k}{2}$ 个 $l_i$，$\frac{k}{2}$ 个 $r_i$，最小化选择的数的和。这个问题可以如下解决：设 $c_i=r_i-l_i$，将 $c$ 数组从小到大排序，答案即为 $\sum\limits_{i=1}^k l_i+\sum\limits_{i=1}^{\frac{k}{2}}c_i$。

显然对于每个 $pos$，$l$ 数组和 $r$ 数组都是可以 $\varTheta(n)$ 计算的，瓶颈在每次对 $c$ 排序，最终复杂度 $\varTheta(n^2\log n)$。
## 正解
观察上面的思路：
>我们要在 $[1,pos-1]$ 里选 $\frac{k}{2}$ 个点，$[pos+1,n]$ 里选 $\frac{k}{2}$ 个点，且这些点的值两两不同，最小化每个点到 $pos$ 的距离的和。

能不能将左右两边各取 $\frac{k}{2}$ 个点的限制去掉？可以的。
> 正确性证明：假设用这种方法求出的答案是 $res$，正确答案是 $ans$。首先因为左右分配不均时，答案一定不会更优，所以 $res\ge ans$。其次，我们考虑取到 $ans$ 时的最优策略，它一定会在区间中点处被 $res$ 考虑到，所以 $res\le ans$，证毕。

所以假设我们还是枚举 $pos$，算出 $l_i$ 和 $r_i$，这时候的答案就变成了 $\sum\limits_{i=1}^k \min(l_i,r_i)$，至此我们得到了一个 $\varTheta(n^2)$ 做法。

为了方便，以下记 $val_i=\min(l_i,r_i)$。发现此时瓶颈在于如何计算 $val_i$。我们发现，从 $pos$ 到 $pos+1$ 的过程中，$val_i$ 的变化只有可能是 $0,1,-1$，这是非常优秀的。

那么我们考虑对于每个 $1\le i\le k$ 计算出 $i$ 对所有 $pos$ 的贡献。每次看一下 $val$ 的变化量是几即可，复杂度 $\varTheta(nk)$。然后我们又发现可以二维差分一下，然后就做完了，时间复杂度 $\varTheta(n)$。

[代码](https://codeforces.com/contest/2085/submission/312140884)。

---

## 作者：Kevin911 (赞：2)

## 题意
给定一个序列，可以交换相邻元素，问至少交换多少次使得存在一个子区间是一个 $1$ 到 $k$ 的排列。
## 思路
由 F1 的暴力做法得知，可以钦定一个位置为中心，其他期望出现在区间中的数向中间靠拢，计算过程就是统计每种数出现在中心的左或右的最近位置，看左右两边去哪个更优，最后减去多余的移动即可（就是不需要都移到中心位置，一个接一个就行）。

考虑如何优化这一过程。先对每种数分开观察，会发现每次的变化量的绝对值 $\leq 1$，即只有加 $1$，减 $1$，不变三种情况。如果两个相邻数之间的距离是偶数，那就有两个中心，从左到右就不变；否则是奇数时就只有一个中心。在中心之前，变化量为减 $1$；在中心之后，变化量为加 $1$。然后就好办了,用差分给区间的变化量赋值就行了。

实现简洁，代码如下
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int maxn=4e5+10;
int n,k,s,d,ans;
int a[maxn],lst[maxn],sum[maxn];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		s=0,ans=1e18;
		cin>>n>>k;
		for(int i=1;i<=n;i++) lst[i]=sum[i]=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(!lst[a[i]]) s+=i-1;
			else
			{
				int pre=lst[a[i]],mid=(pre+i)/2;
				if((pre+i)&1) sum[mid]--,sum[mid+1]--;
				else sum[mid]-=2;
			}
			sum[i]+=2;
			lst[a[i]]=i;
		}
		d=-k;
		for(int i=1;i<=n;i++)
		{
			ans=min(ans,s);
			d+=sum[i],s+=d;
		}
		for(int i=1;i<=k;i++) ans-=abs(i-(k+1)/2);
		cout<<ans<<endl;
	}
}
```

---

## 作者：incra (赞：1)

### Sol
下文中答案表示 $k$ 个点到某个中心的距离之和，真正的答案需要减去 $\displaystyle\sum_{i=1}^n\left|i-\left\lfloor\frac{k+1}{2}\right\rfloor\right|$。

考虑 F1 做法，假设选定一个点在 $i$，并且以这个点为中心，$i$ 左边第一个颜色为 $j$ 的位置到 $i$ 的距离为 $l_j$，右边第一个颜色为 $j$ 的到 $i$ 的距离为 $r_j$。

此时最优方案一定是 $i$ 两侧 $l_j$ 和 $r_j$ 各选一半。

令 $c_j=r_j-l_j$，将 $c$ 排序后答案就是 $\displaystyle\sum_{i=1}^nl_j+\sum_{i=1}^{\left\lfloor\frac{k+1}{2}\right\rfloor}c_j$。

时间复杂度：$O(n^2)$。

引理：不用考虑在 $i$ 两侧各选一半 $l_j$ 和 $r_j$，一定能统计到最优解。

证明：由仓库选址问题可知如果选的中心不在正中间那么答案一定不优，且该方案一定能统计到最优解。

那么事情就变得简单了，答案变成了 $\displaystyle\sum_{i=1}^n\min(l_i,r_i)$，感觉还是不太好做，对于每一个 $\min(l_i,r_i)$ 观察可得每当 $i$ 加上 $1$，$\min(l_i,r_i)$ 变化的绝对值不超过 $1$，观察变化规律可以发现每次都是区间加一个等差数列，也就是一个二维差分，那么就做完了。

时间复杂度：$O(n^2)$。
### Code
[F1](https://codeforces.com/contest/2085/submission/314694337)。

[F2](https://codeforces.com/contest/2085/submission/314696130)。

---

## 作者：wmrqwq (赞：1)

感谢 @incra 的讲解。

# 题目链接

[CF2085F2 *2900](https://www.luogu.com.cn/problem/CF2085F2)

# 解题思路

考虑 F1 做法，发现直接枚举每个数作为中心点即可，只需要维护距离中心点的其余值的最小位置，时间复杂度 $O(n^2)$。

然后你可以注意到中心点不一定是中心点，具体的，左右两边数字不一定是平均的，由于这种情况一定是不优的，所以不用去管。

那么你发现剩下的可以直接使用二维差分对原来的暴力做优化，做完了。

注意需要分讨一下区间不同的奇偶情况。

时间复杂度 $O(n)$。

# 参考代码

```cpp
ll n,m;
ll a[1000010],ans[1000010];
ll lst[1000010],now[1000010];
void upd(ll l,ll r,ll x)
{
    if(l<=r)
        ans[l]+=x,
        ans[r+1]-=x;
}
void _clear(){}
void solve()
{
    _clear();
    cin>>n>>m;
    forl(i,1,m)
        lst[i]=now[i]=0;
    forl(i,1,n)
        ans[i]=0;
    forl(i,1,n)
        cin>>a[i],
        lst[a[i]]=i;
    forl(i,1,n)
    {
        if(i==lst[a[i]])
            upd(i+1,n,1);
        if(!now[a[i]])
            upd(1,1,i-1),
            upd(2,i,-1);
        else
        {
            ll l=now[a[i]],r=i;
            ll Mid=(l+r+1)/2;
            if((l+r)%2==0)
                upd(l+1,Mid,1),
                upd(Mid+1,r,-1);
            else
                upd(l+1,Mid-1,1),
                upd(Mid+1,r,-1);
        }
        now[a[i]]=i;
    }
    forl(i,1,n)
        ans[i]+=ans[i-1];
    forl(i,1,n)
        ans[i]+=ans[i-1];
    ll A=1e18;
    forl(i,1,n)
        Min(A,ans[i]);
    forl(i,1,m)
        A-=abs((m+1)/2-i);
    cout<<A<<endl;
}
```

---

## 作者：Unnamed114514 (赞：0)

首先，延续 F1 的思路，我们容易想到枚举中间点。

注意到我们并不需要钦定它是真正的中心点，因为如果它不是，那么真正的中心点的花费一定比它少。

然后我们就转化为了求其他颜色每种颜色到它的最小距离之和。

显然只有它左边和右边第一个有可能造成贡献。

因此我们把每种值单独提出来，显然对于左边/右边的段，他们分别取的是右边/左边的对应值，对于中间的段，显然中点和左边取左边的值，右边的取右边的值。

然后你会发现距离这个贡献是一个等差数列，经典套路了，线段树标记永久化轻松解决。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ls p<<1
#define rs p<<1|1
#define int long long
using namespace std;
const int N=4e5+5;
int T,n,k,a[N];
vector<int> vec[N];
struct ST{ int tag1,cnt1,tag2,cnt2; }t[N<<2];
void build(int p,int l,int r){
	t[p].tag1=t[p].tag2=t[p].cnt1=t[p].cnt2=0;
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
}
void update1(int p,int l,int r,int ql,int qr,int w){
	if(ql<=l&&r<=qr){
		t[p].tag1+=w,++t[p].cnt1;
		return;
	}
	int mid=l+r>>1;
	if(qr<=mid) return update1(ls,l,mid,ql,qr,w);
	if(mid<ql) return update1(rs,mid+1,r,ql,qr,w);
	update1(ls,l,mid,ql,qr,w);
	update1(rs,mid+1,r,ql,qr,w+(mid-max(l,ql)+1));
}
void update2(int p,int l,int r,int ql,int qr,int w){
	if(ql<=l&&r<=qr){
		t[p].tag2+=w,++t[p].cnt2;
		return;
	}
	int mid=l+r>>1;
	if(qr<=mid) return update2(ls,l,mid,ql,qr,w);
	if(mid<ql) return update2(rs,mid+1,r,ql,qr,w);
	update2(ls,l,mid,ql,qr,w+(min(r,qr)-mid));
	update2(rs,mid+1,r,ql,qr,w);
}
int query(int p,int l,int r,int pos){
	if(l==r) return t[p].tag1+t[p].tag2;
	int mid=l+r>>1;
	if(pos<=mid) return query(ls,l,mid,pos)+t[p].tag1+t[p].cnt1*(pos-l)+t[p].tag2+t[p].cnt2*(r-pos);
	return query(rs,mid+1,r,pos)+t[p].tag1+t[p].cnt1*(pos-l)+t[p].tag2+t[p].cnt2*(r-pos);
}
void update(int l,int r){
	int mid=l+r>>1;
	update1(1,1,n,l,mid,0);
	update2(1,1,n,mid+1,r,0);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;++i) cin>>a[i],vec[a[i]].emplace_back(i);
		build(1,1,n);
		for(int i=1;i<=k;++i){
			int L=vec[i].size();
			update2(1,1,n,1,vec[i][0],0);
			for(int j=1;j<L;++j) update(vec[i][j-1],vec[i][j]);
			update1(1,1,n,vec[i][L-1],n,0);
		}
		int ans=1e18;
		for(int i=1;i<=n;++i) ans=min(ans,query(1,1,n,i));
		if(k&1) ans-=((k>>1)*((k>>1)+1));
		else ans-=((k>>1)*((k>>1)-1)/2+(k>>1)*((k>>1)+1)/2);
		cout<<ans<<endl;
		for(int i=1;i<=k;++i) vec[i].clear(),vec[i].shrink_to_fit();
	}
	return 0;
}
```

---

## 作者：Mr_罗 (赞：0)

默认都会 F1 。

首先枚举中间位置时两边不必都是恰好 $n/2$ 个数，因为如果偏了会在真正的中间位置算出来更优值。

所以只要对于每种数加上到当前位置的距离的最小值即可。

考虑拆贡献，注意到每种数对整个序列的贡献是类似于 `2 1 0 1 2 3 3 2 1 0 1 0 1 2 3` 这样一个序列，发现可以拆成若干 `/` 和 `\` 这样公差为 $\pm 1$ 的等差数列，于是直接上线段树等差数列加单点查询维护即可。~~我想都没想二维差分直接撸的线段树~~

时间复杂度 $\mathcal O(n\log n+m)$ 。

[CF 提交记录](https://codeforces.com/contest/2085/submission/313898383) 。

---

