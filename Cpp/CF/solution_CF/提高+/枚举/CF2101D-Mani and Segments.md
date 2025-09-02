# Mani and Segments

## 题目描述

一个长度为 $|b|$ 的数组 $b$ 被称为"可爱的"，当且仅当其最长递增子序列（LIS）的长度与最长递减子序列（LDS）的长度 $^{\text{∗}}$ 之和恰好比数组长度大 1。更正式地说，数组 $b$ 是可爱的当且仅当 $\operatorname{LIS}(b) + \operatorname{LDS}(b) = |b| + 1$。

给定一个长度为 $n$ 的排列 $a$ $^{\text{†}}$。你的任务是统计排列 $a$ 中所有非空子数组 $^{\text{‡}}$ 中满足可爱条件的数量。

$^{\text{∗}}$ 序列 $x$ 是序列 $y$ 的子序列，如果可以通过从 $y$ 中删除任意位置（可能为零或全部）的元素得到 $x$。

数组的最长递增（递减）子序列是指元素按严格递增（递减）顺序排列的最长子序列。

$^{\text{†}}$ 长度为 $n$ 的排列是由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 出现了两次），$[1,3,4]$ 也不是排列（$n=3$ 但数组中出现了 $4$）。

$^{\text{‡}}$ 数组 $x$ 是数组 $y$ 的子数组，如果可以通过从 $y$ 的开头和结尾删除若干（可能为零或全部）元素得到 $x$。

## 说明/提示

在第一个测试用例中，所有 6 个非空子数组都是可爱的：
- $[3]$：$\operatorname{LIS}([3]) + \operatorname{LDS}([3]) = 1 + 1 = 2$
- $[1]$：$\operatorname{LIS}([1]) + \operatorname{LDS}([1]) = 1 + 1 = 2$
- $[2]$：$\operatorname{LIS}([2]) + \operatorname{LDS}([2]) = 1 + 1 = 2$
- $[3, 1]$：$\operatorname{LIS}([3, 1]) + \operatorname{LDS}([3, 1]) = 1 + 2 = 3$
- $[1, 2]$：$\operatorname{LIS}([1, 2]) + \operatorname{LDS}([1, 2]) = 2 + 1 = 3$
- $[3, 1, 2]$：$\operatorname{LIS}([3, 1, 2]) + \operatorname{LDS}([3, 1, 2]) = 2 + 2 = 4$

在第二个测试用例中，一个可爱的子数组是 $[2, 3, 4, 5, 1]$，因为 $\operatorname{LIS}([2, 3, 4, 5, 1]) = 4$ 且 $\operatorname{LDS}([2, 3, 4, 5, 1]) = 2$，满足 $4 + 2 = 5 + 1$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
3
3 1 2
5
2 3 4 5 1
4
3 4 1 2
7
1 2 3 4 5 6 7
10
7 8 2 4 5 10 1 3 6 9```

### 输出

```
6
15
9
28
36```

# 题解

## 作者：Mr_罗 (赞：2)

我怎么连这种题都不会做了。晚上实在是太不清醒了。

考虑枚举 LIS 和 LDS 相交的位置 $i$ ，所有可能贡献的区间 $[l,r]$ 满足

- $[l,i)$ 中所有 $<a_i$ 的数递增，$>a_i$ 的数递减。
- $(i,r]$ 中所有 $>a_i$ 的数递增，$<a_i$ 的数递减。

~~断言：除去单调的区间外，每个合法的区间一定能恰好找到这样一个位置，且能找到这样位置的区间一定合法。~~ 感谢 @[masonpop](https://www.luogu.com.cn/user/614725) 指出错误。

注意到每个区间一定能找到这样的位置，于是考虑扫描线，按照值域从小到大扫，设当前枚举到的值是 $x$ ，其在排列中的位置是 $i$ 。

考察哪些位置会炸：因为我们是从小到大扫的，因此在 $i$ 右边且比 $i$ 小的位置都似了，它们的左端点应该和 $i+1$ chkmax ，左侧类似。

这是递增的 case ，再倒着扫一遍进行类似的过程。

统计答案是简单的（矩形并），这样我们就做完了。时间复杂度 $\mathcal O(n\log n)$ 。

[CF AC link](https://codeforces.com/contest/2101/submission/319337167).

---

## 作者：Unnamed114514 (赞：2)

容易发现 LIS 和 LCS 会有一位重叠，我们就从重叠的这一位入手。

如果 $[l,r]$ 重叠的位置为 $x$，那么有左侧 $<a_x$ 的数递增，$>a_x$ 的数递减，右侧 $>a_x$ 的数递增，$<a_x$ 的数递减。

然后你考虑维护出对于每个 $x$ 最大的 $l,r$。

可以发现如果我们知道所有的大小关系之后可以转化为求最长 01 串。

考虑把值从小往大加入数组，这样就能满足大小关系的限制。可以发现可行性有调整的只有 $x$ 及其前后最近的一个已经插入了的位置，手玩一下即可。

那么我们就可以得到 $[l_i,r_i]$ 表示 $i$ 能满足的最大区间。剩下的就是一个经典的扫描线问题了，每次 $r$ 往右扫的时候，清掉 $r_i=r-1$ 的贡献，加上 $[l_r,r_r]$ 的贡献。维护的话可以用区间加，显然为 $0$ 时是没有贡献的，于是转化为区间加区间最小值计数。

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f3f3f3f3fLL
#define endl '\n'
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int N=2e5+5;
int T,n,a[N],pos[N],L[N],R[N];
set<int> s;
vector<int> vec[N];
struct Seg1{
	struct node{
		int L,R;
		node operator +(const node &o) const{ return node({L==-1?o.L:L,o.R==-1?R:o.R}); }
	}t[N<<2];
	void build(int p,int l,int r){
		if(l==r){
			t[p].L=t[p].R=-1;
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		t[p]=t[ls]+t[rs];
	}
	void update(int p,int l,int r,int pos,int op){
		if(l==r){
			if(op==-1) t[p].L=t[p].R=l;
			else t[p].L=t[p].R=-1;
			return;
		}
		int mid=l+r>>1;
		if(pos<=mid) update(ls,l,mid,pos,op);
		else update(rs,mid+1,r,pos,op);
		t[p]=t[ls]+t[rs];
	}
	node query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return t[p];
		int mid=l+r>>1;
		if(qr<=mid) return query(ls,l,mid,ql,qr);
		if(mid<ql) return query(rs,mid+1,r,ql,qr);
		return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
	}
}T1;
struct Seg2{
	struct node{
		int mi,cnt,tag;
		node operator +(const node &o) const{
			int m=min(mi,o.mi),c=0;
			if(mi==m) c+=cnt;
			if(o.mi==m) c+=o.cnt;
			return node({m,c});
		}
	}t[N<<2];
	void build(int p,int l,int r){
		t[p].tag=0;
		if(l==r){
			t[p].mi=0,t[p].cnt=1;
			return;
		}
		int mid=l+r>>1;
		build(ls,l,mid),build(rs,mid+1,r);
		t[p]=t[ls]+t[rs];
	}
	void pushdown(int p){
		t[ls].mi+=t[p].tag,t[rs].mi+=t[p].tag;
		t[ls].tag+=t[p].tag,t[rs].tag+=t[p].tag;
		t[p].tag=0;
	}
	void update(int p,int l,int r,int ql,int qr,int val){
		if(ql<=l&&r<=qr){
			t[p].mi+=val,t[p].tag+=val;
			return;
		}
		pushdown(p);
		int mid=l+r>>1;
		if(ql<=mid) update(ls,l,mid,ql,qr,val);
		if(mid<qr) update(rs,mid+1,r,ql,qr,val);
		t[p]=t[ls]+t[rs];
	}
	int query(int p,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return !t[p].mi?(r-l+1)-t[p].cnt:r-l+1;
		pushdown(p);
		int mid=l+r>>1,res=0;
		if(ql<=mid) res+=query(ls,l,mid,ql,qr);
		if(mid<qr) res+=query(rs,mid+1,r,ql,qr);
		return res;
	}
}T2;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>a[i],pos[a[i]]=i;
		for(int i=1;i<=n;++i) L[i]=-inf,R[i]=inf;
		s.clear();
		T1.build(1,1,n);
		for(int i=1;i<=n;++i){
			int x=pos[i];
			auto it=s.lower_bound(x);
			if(it!=s.begin()){
				--it;
				T1.update(1,1,n,*it,1);
				++it;
			}
			int res=T1.query(1,1,n,1,x).R;
			if(res==-1) L[x]=max(L[x],1LL);
			else L[x]=max(L[x],res+1);
			if(it!=s.end()) T1.update(1,1,n,x,-1);
			s.insert(x);
		}
		s.clear();
		T1.build(1,1,n);
		for(int i=n;i;--i){
			int x=pos[i];
			auto it=s.lower_bound(x);
			if(it!=s.begin()){
				--it;
				T1.update(1,1,n,*it,1);
				++it;
			}
			int res=T1.query(1,1,n,1,x).R;
			if(res==-1) L[x]=max(L[x],1LL);
			else L[x]=max(L[x],res+1);
			if(it!=s.end()) T1.update(1,1,n,x,-1);
			s.insert(x);
		}
		s.clear();
		T1.build(1,1,n);
		for(int i=1;i<=n;++i){
			int x=pos[i];
			auto it=s.lower_bound(x);
			if(it!=s.end()) T1.update(1,1,n,*it,1);
			int res=T1.query(1,1,n,x,n).L;
			if(res==-1) R[x]=min(R[x],n);
			else R[x]=min(R[x],res-1);
			if(it!=s.begin()) T1.update(1,1,n,x,-1);
			s.insert(x);
		}
		s.clear();
		T1.build(1,1,n);
		for(int i=n;i;--i){
			int x=pos[i];
			auto it=s.lower_bound(x);
			if(it!=s.end()) T1.update(1,1,n,*it,1);
			int res=T1.query(1,1,n,x,n).L;
			if(res==-1) R[x]=min(R[x],n);
			else R[x]=min(R[x],res-1);
			if(it!=s.begin()) T1.update(1,1,n,x,-1);
			s.insert(x);
		}
		for(int i=1;i<=n;++i) vec[R[i]].emplace_back(L[i]);
		T2.build(1,1,n);
		int ans=0;
		for(int i=1;i<=n;++i){
			T2.update(1,1,n,L[i],R[i],1);
			ans+=T2.query(1,1,n,1,i);
			for(auto l:vec[i]) T2.update(1,1,n,l,i,-1);
		}
		cout<<ans<<endl;
		for(int i=1;i<=n;++i) vec[i].clear(),vec[i].shrink_to_fit();
	}
	return 0;
}
```

---

## 作者：N_z_ (赞：2)

考察这个要求，如果我们能直接转化成 1144G 那么就做完了，原因是一个前缀的状态数 $\le4$，直接证明我不会，但大概可以跑一遍 $n\le11$ 发现 $\le4$ 然后归纳一下。

但现在不完全一样，不过这可以解决。我们猜测只需要额外去掉 $2,4,1,3$ 和 $3,1,4,2$ 形即可，跑个搜发现很对。必要性显然，充分性大概考虑没有这俩 $\text{pattern}$ 的时候划分出来的 $\operatorname{IS}$ 和 $\operatorname{DS}$ 有交。

然后就做完了，时间复杂度 $O(n)$。

<https://codeforces.com/contest/2101/submission/319312314>。

---

## 作者：Zi_Gao (赞：1)

这是一篇 $\mathcal{O}(n)$ 题解，代码**巨**简洁。

首先考虑这个限制条件意味着什么，发现当且仅当，区间 LIS 序列和 LDS 序列并为整个区间，交为一个点，形如一个叉叉的样子。枚举交的这个点 $a_i$，考虑向后向前的扩展，这里只考虑向后，那么每个 $a_j\le a_i$ 一定要加入 LIS 序列，否则一定要加入 LDS 序列。那么单调栈就可维护，每次把端点移动到弹出点的位置即可。

然后需要维护一个矩形并面积大小，但是发现左下角的点和右上角的点横纵坐标都单调递增，那么每次减去相交即可。

```cpp
il void calc(int op){
    int i,j,p=0,sum;
    std::stack<int> A,B;
    for(i=1;i<=n;++i){
        while((!A.empty())&&a[i]>a[A.top()]) p=std::max(p,A.top()),A.pop();
        while((!B.empty())&&a[i]<a[B.top()]) p=std::max(p,B.top()),B.pop();

        if(a[i]>a[i+1]) A.push(i);
        else B.push(i);

        pos[op][op?n-i+1:i]=i-p;
    }
}

void solve(){
    int i;
    i64 res=0,lx=0,ly=0,xa,ya,xb,yb;
    lg=std::__lg(n=read());
    for(i=1;i<=n;++i) a[i]=read();
    calc(0);
    std::reverse(a+1,a+1+n);
    calc(1);

    for(i=1;i<=n;++i){
        xa=i-pos[0][i]+1,ya=i;
        xb=i,yb=i+pos[1][i]-1;
        res+=(xb-xa+1)*(yb-ya+1)-std::max(lx-xa+1,0ll)*std::max(ly-ya+1,0ll);
        lx=xb,ly=yb;
    }
    print(res),putchar('\n');
}
```

---

## 作者：Officer_Xia_ZhuRen (赞：0)

口胡一下。

观察到 $+1$，则区间的特征在断点上，我们双指针扫描出一个前缀的 > 形和一个后缀的 < 形，记录极长长度即可，可以做到线性或者 $\mathcal{O}(n\log)$。

发现断点枚举会重复，不要慌，直接相邻项取交去重。

---

