# Maximize Nor

## 题目描述

对于一个包含 $k$ 位整数的数组 $b_1, b_2, \ldots, b_m$，其按位或非运算$^{\text{∗}}$可以通过从左到右累积计算得到。更正式地说，对于 $m \ge 2$，$\operatorname{nor}(b_1, b_2, \ldots, b_m) = \operatorname{nor}(\operatorname{nor}(b_1, b_2, \ldots, b_{m - 1}), b_m)$，而 $\operatorname{nor}(b_1) = b_1$。

给定一个包含 $k$ 位整数的数组 $a_1, a_2, \ldots, a_n$。对于每个下标 $i$（$1 \le i \le n$），找出所有包含下标 $i$ 的子数组$^{\text{†}}$中按位或非运算的最大值。换句话说，对于每个下标 $i$，找出所有满足 $1 \le l \le i \le r \le n$ 的子数组 $a_l, a_{l+1}, \ldots, a_r$ 中 $\operatorname{nor}(a_l, a_{l+1}, \ldots, a_r)$ 的最大值。

$^{\text{∗}}$ 两个布尔值的逻辑或非运算定义为：当两个值都为 $0$ 时结果为 $1$，否则为 $0$。两个 $k$ 位整数的按位或非运算是对每对对应位进行逻辑或非运算得到的结果。

例如，将 $2$ 和 $6$ 表示为 $4$ 位二进制数时，计算 $\operatorname{nor}(2, 6)$。$2$ 的二进制表示为 $0010_2$，$6$ 为 $0110_2$。因此，$\operatorname{nor}(2,6) = 1001_2 = 9$，因为从左到右逐位进行逻辑或非运算：
- $\operatorname{nor}(0,0) = 1$
- $\operatorname{nor}(0,1) = 0$
- $\operatorname{nor}(1,0) = 0$
- $\operatorname{nor}(1,1) = 0$

注意，如果 $2$ 和 $6$ 表示为 $3$ 位整数，则 $\operatorname{nor}(2,6) = 1$。

$^{\text{†}}$ 数组 $x$ 是数组 $y$ 的子数组，当且仅当 $x$ 可以通过从 $y$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 说明/提示

在第一个测试用例中：
- 包含下标 $1$ 的子数组有 $[1]$ 和 $[1, 3]$。它们的按位或非运算结果分别为 $1$ 和 $0$。因此，下标 $1$ 的答案为 $1$。
- 包含下标 $2$ 的子数组有 $[3]$ 和 $[1, 3]$。它们的按位或非运算结果分别为 $3$ 和 $0$。因此，下标 $2$ 的答案为 $3$。

在第二个测试用例中：
- 对于 $i = 1$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。
- 对于 $i = 2$，按位或非运算最大的子数组是 $[a_2] = [7]$，$\operatorname{nor}(7) = 7$。
- 对于 $i = 3$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。
- 对于 $i = 4$，按位或非运算最大的子数组是 $[a_4] = [6]$，$\operatorname{nor}(6) = 6$。
- 对于 $i = 5$，按位或非运算最大的子数组是 $[a_1, a_2, a_3, a_4, a_5] = [1, 7, 4, 6, 2]$，$\operatorname{nor}(1, 7, 4, 6, 2) = 5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
2 2
1 3
5 3
1 7 4 6 2```

### 输出

```
1 3
5 7 5 6 5```

# 题解

## 作者：_Eriri_ (赞：0)

还是有难度的一道题，没做出来比较可惜。参考了官方题解。

题意：

有一个长度为 $n$ 的序列 $a$。对于每一个 $i$，求 $\max_{l \le i \le r} {\rm{nor}}(a_l,a_l+1 \ ...\ a_r)$。

其中 $\rm nor$ 的运算顺序是从左到右。

大家都知道对于“与”，”或“两种运算，当 $r$ 确定时，对于所有 $l$，$\oplus_{i=l}^r a_i$ 不同的值只有 $\log_2 V$ 种，并且产生相同值的 $l$ 是连续的一段下标。

而对于 $\rm{nor}$，也可以证明当 $r$ 确定，所有 $l$ 产生的值只有 $\log_2 V$ 种。


证明：

-  让我们先考虑一个区间 $[l,r]$ 的 ${\rm{nor}}(a_l,a_l+1 \ ... \ a_r)$ 怎么求。先按位考虑，设当前考虑到二进制第 $b$ 位。注意到从左到右的运算过程中，最后一个第 $b$ 位为 $1$ 的位置尤为重要，设其为 $x$。不管 $x$ 前的运算结果如何，前面的运算值跟 $a_x$ $\rm{nor}$ 后第 $b$ 位一定是 $0$，并且 $x$ 之后的所有数第 $b$ 位都是 $0$。因此可以靠下标奇偶性判断最终的值。尝试用形式化的语言刻画。
     -  设 $x$ 为 $r$ 及之前最后一个第 $b$ 位为 $1$ 的元素的下标。
     -  当 $x > l $ 时，若 $x$ 与 $r$ 奇偶性不同，则最终值第 $b$ 位为 $1$，否则为 $0$。
     -  当 $x = l$ 时，若 $l$ 与 $r$ 奇偶性不同，则最终值第 $b$ 位为 $0$，否则为 $1$。
     -  当 $x < l$ 时，若 $l$ 与 $r$ 奇偶性不同。则最终值第 $b$ 位为 $1$，否则为 $0$。
- 接下来证明最开始的结论。当 $r$ 确定，设 $p_i$ 表示第 $i$ 位的 $x$。将 $p$ 数组排序后，很明显对于 $(p_i,p_{i+1})$ 内的 $l$，最多只会产生两个不同的到 $r$ 的值，因为它们和所有 $x$ 的大小关系一样，值不同只能因为下标奇偶性不同。而 $l$ 取端点时本来就只有 $\log$ 个值。所以不同的值在 $\log$ 级别，根据证明过程，我们也能在写代码时很清楚地找出这些值的分布。


找出产生每个值的最小 $l$，将 $i \in [l,r]$ 的答案取 $\max$，这个操作用线段树即可。

时间复杂度 $O(n \log_2 V \log_2 n)$


代码（不建议阅读）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,K,pre[21],tmp[21],tong[21];
int ans[N];
vector<int>pos[N];
#define ls rt<<1
#define rs rt<<1|1
int Rt=1;
struct segment{int mx;}seg[N<<2];
void chkmax(int rt,int l,int r,int L,int R,int v){
	if(L>R||r<L||l>R)return;
	if(L<=l&&r<=R)return seg[rt].mx=max(seg[rt].mx,v),void();
	int mid=l+r>>1;
	chkmax(ls,l,mid,L,R,v);
	chkmax(rs,mid+1,r,L,R,v);
}	
void flat(int rt,int l,int r,int v){
	if(l==r){
		v=max(v,seg[rt].mx);
		ans[l]=v;
		seg[rt].mx=0;
		return;
	}
	int mid=l+r>>1;
	flat(ls,l,mid,max(v,seg[rt].mx));
	flat(rs,mid+1,r,max(v,seg[rt].mx));
	seg[rt].mx=0;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&K);
		for(int i=0;i<K;i++)pre[i]=0;
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			for(int j=0;j<K;j++){
				if(x>>j&1)pre[j]=i;
				tmp[j]=pre[j];
				pos[pre[j]].push_back(j);
				tong[j]=-1;
			}
			sort(tmp,tmp+K);
			int nk=unique(tmp,tmp+K)-tmp;
			tmp[nk]=i;
			for(int j=nk-1;j>=0;j--){
				int res=0,exr=0;
				for(int k=0;k<K;k++){
					if(tong[k]!=-1)res+=tong[k]*(1<<k);
					else exr+=(1<<k);
				}
				if(i%2==0){
					if((tmp[j]+2)/2*2<tmp[j+1])chkmax(Rt,1,n,(tmp[j]+2)/2*2,i,res);
					if((tmp[j]+1)/2*2+1<tmp[j+1])chkmax(Rt,1,n,(tmp[j]+1)/2*2+1,i,res+exr);			
				}else {
					if((tmp[j]+2)/2*2<tmp[j+1])chkmax(Rt,1,n,(tmp[j]+2)/2*2,i,res+exr);
					if((tmp[j]+1)/2*2+1<tmp[j+1])chkmax(Rt,1,n,(tmp[j]+1)/2*2+1,i,res);	
				}
				int nres=0;
				for(int v:pos[tmp[j]]){
					tong[v]=(tmp[j]&1)!=(i&1);
					nres+=(1<<v);
				}
				pos[tmp[j]].clear();
				if(tmp[j])chkmax(Rt,1,n,tmp[j],i,res+((tmp[j]&1)==(i&1))*nres+((tmp[j]&1)!=(i&1))*(exr-nres));				
			}		
			if(tmp[0]>1){
				int res=0;
				for(int k=0;k<K;k++)res+=tong[k]*(1<<k);
				chkmax(Rt,1,n,1,i,res);
			} 
		}
		flat(Rt,1,n,0);
		for(int i=1;i<=n;i++)cout<<ans[i]<<' ';
		cout<<'\n';	
	}
	return 0; 
}
```

---

