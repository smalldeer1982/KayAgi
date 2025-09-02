# [NERC2024] Judicious Watching

## 题目描述

Jill 喜欢在大学里获得好成绩，所以她从不拖延作业的截止日期。但她更喜欢观看剧集并与她的好朋友 Johnny 讨论。而不幸的是，今天她必须在这两项活动之间做出选择！

Jill 需要完成 $n$ 个作业任务。第 $i$ 个任务需要 $a_i$ 分钟来完成，并且必须在 $d_i$ 分钟内提交给老师。此外，还有 $m$ 集 Johnny 和 Jill 想要讨论的新剧集。第 $j$ 个剧集的时长是 $l_j$ 分钟。Jill 可以按任何顺序完成作业任务，但她需要按顺序观看剧集。开始后，无论是完成作业任务还是观看剧集，都不能中断。

Johnny 和 Jill 需要就一个时间 $t_k$ 达成一致，以便讨论剧集。她们尚未确定选择哪个时间。对于每个可能的时间，计算 Jill 在该时间之前可以观看的最大剧集数，同时仍能按时完成所有的作业任务。

注意：在这个问题中，我们假设与 Johnny 的剧集讨论不会占用 Jill 太多时间，并且**即使 Jill 正在完成作业任务，也可以在此时进行讨论**。

## 样例 #1

### 输入

```
2
1 2 3
10
15
5 5
5 15 20
3 4 5
8 100 8
10 150 20
2 32 1 1
9 200 51 50 10```

### 输出

```
1 1 2
1 4 2 2 1```

# 题解

## 作者：OIer_Hhy (赞：1)

双倍经验：[CF2052J](https://www.luogu.com.cn/problem/CF2052J)。

一道反悔贪心题。

因为保证有一种次序能完成所有作业，所以首先我们按照截止时间排序。

考虑到以下两种情况：

- 写完作业再看剧。
- 看完剧再写作业。

如果看完剧再写作业还能在截止时间之前交上的话，我们显然先看剧。

所以我们要尽早看完所有剧集。

我们可以先进行初始化，然后离线查询。

我们可以记录下所有剧集的结束时间。

先把第 $i$ 份作业截止时间与做前 $i$ 份作业需要时间的差求出来。

- 若能看一部剧，那就看。
- 若差为负数怎么办？这时候，我们就要反悔，把上次的剧撤销掉。

时间复杂度：$O(n+m+q \log n)$，能通过。


```cpp
#include<bits/stdc++.h>
#define int long long
//#define DEBUG
using namespace std;
const int N=2e5+10;
int n,m,q,b[N],x,c[N];
struct node{
	int a,b;
}a[N];
bool cmp(node a,node b){
	return a.b<b.b;
}
void solve(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) cin>>a[i].a;
	for(int i=1;i<=n;i++) cin>>a[i].b;
	for(int i=1;i<=m;i++) cin>>b[i];
	sort(a+1,a+n+1,cmp);
	int t=0,i=1,j=1;
	while(i<=n){
		while(j>0&&t+a[i].a>a[i].b){
			j--;
			t-=b[j];
			c[j]=1e9;
			#ifdef DEBUG
			cout<<i<<' '<<j<<' '<<c[j]<<'\n';
			#endif
		}
		while(j<=m&&t+b[j]<=a[i].b-a[i].a){
			t+=b[j];
			c[j]=t;
			#ifdef DEBUG
			cout<<i<<' '<<j<<' '<<c[j]<<'\n';
			#endif
			j++;
		}
		t+=a[i].a;
		i++;
	}
	while(j<=m){
		t+=b[j];
		c[j]=t;
		j++;
	}
	#ifdef DEBUG
	for(int i=1;i<=m;i++) cout<<c[i]<<" ";
	cout<<'\n';
	#endif
	while(q--){
		cin>>x;
		cout<<upper_bound(c+1,c+m+1,x)-c-1<<' ';
	}
	cout<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	
	return 0;
}
```

---

