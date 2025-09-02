# Tree Diameter

## 题目描述

有一棵包含 $n$ 个节点和 $n-1$ 条边的带权树。节点编号为 $1$ 到 $n$。每条边的权值为不超过 $100$ 的正整数。定义两个节点之间的距离为它们之间唯一路径上所有边权之和。你需要找到这棵树的直径。直径指的是任意一对节点之间的最大距离。

遗憾的是，树的具体结构并未给出，但你可以对其进行若干次询问。每次询问时，你可以指定两个非空且不相交的节点集合 $p$ 和 $q$，裁判会返回 $p$ 中某个节点与 $q$ 中某个节点之间的最大距离。换句话说，返回 $\max_{x \in p,\, y \in q} dist(x, y)$。在不超过 $9$ 次询问后，你必须报告任意一对节点之间的最大距离。

## 说明/提示

在第一个样例中，第一棵树如下图所示：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146C/94235129f3da7cfec124ca714e30d0068863bd5b.png)

第一次询问时，$p = \{1\}$，$q = \{2, 3, 4, 5\}$。$p$ 中某个节点与 $q$ 中某个节点之间的最大距离为 $9$（即节点 $1$ 与节点 $5$ 之间的距离）。

第二棵树是一棵有两个节点的树，二者之间有一条权值为 $99$ 的边。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
9
6
10
9
10
2
99
```

### 输出

```
1 4 1 2 3 4 5
1 4 2 3 4 5 1
1 4 3 4 5 1 2
1 4 4 5 1 2 3
1 4 5 1 2 3 4
-1 10
1 1 1 2
-1 99```

# 题解

## 作者：kele7 (赞：3)

### CF1146C Tree Diameter 题解

二分做法。

看到题目中说最多询问 $9$ 次，所以询问次数一定是 $\log n$ 级别的，由此想到二分。

考虑到距离一个点最远的节点，一定是树的直径的两端，所以考虑先询问 $1$ 号节点到其他所有点的最远距离，目前已经询问了 $1$ 次。

我们希望求出距离 $1$ 号节点最远的节点是哪一个，考虑二分，在 $2\sim n$ 的节点中，选取其中一半的节点，每次询问从 $1$ 节点到这些节点的最远距离，如果等于一开始求出的距离，那么直径的一端一定就在这一半的点中，否则就不在，最后，我们一定能确定唯一的一个点，它一定是直径的一端。目前我们已经询问了 $1+\log n=1+7=8$ 次。

最后，由于我们已经求出了直径的一端，那么我们可以直接询问从这个点到其他所有点的最远距离，询问的结果就是直径的长度。目前我们已经询问了 $1+\log n+1=1+7+1=9$ 次。刚好。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,y,l,r;
void print(int l,int r){//询问从 1 节点到 l~r 节点的最远距离
	cout<<"1 "<<r-l+1<<" 1 ";
	for(int i=l;i<=r;i++)cout<<i<<" ";cout<<endl;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		print(2,n);//求出从 1 节点到其他所有节点的最远距离
		cin>>x;
		l=2;r=n;
		while(l<r){//二分找直径的一端
			int mid=(l+r)/2;
			print(l,mid);cin>>y;
			if(x==y)r=mid;
			else l=mid+1;
		}
		cout<<"1 "<<n-1<<" "<<l<<" ";//从直径的一端求最远距离
		for(int i=1;i<l;i++)cout<<i<<" ";
		for(int i=l+1;i<=n;i++)cout<<i<<" ";
		cout<<endl;
		cin>>y;
		cout<<"-1 "<<y<<endl;
	}
}
```

---

## 作者：da32s1da (赞：2)

二进制分组。

一个数与另外一个数在二进制上至少有一位不同。

所以每次询问把有二进制相同位的放在一起，其他的放在一起询问即可。

```cpp
#include<cstdio>
const int N=105;
int T,n,a[N],b[N],cnt,cmt,x,Ans;
int main(){
	for(scanf("%d",&T);T;T--){
		scanf("%d",&n);Ans=0;
		for(int i=1;i<=n;i<<=1){//枚举二进制位
			cnt=cmt=0;
			for(int j=1;j<=n;j++)
			if(i&j)a[++cnt]=j;//二进制分组
			else b[++cmt]=j;
			printf("%d %d ",cnt,cmt);
			for(int j=1;j<=cnt;j++)printf("%d ",a[j]);
			for(int j=1;j<=cmt;j++)printf("%d ",b[j]);
			fflush(stdout);
			scanf("%d",&x);
			if(Ans<x)Ans=x;
		}
		printf("-1 %d\n",Ans);
		fflush(stdout);
	}
} 
```

---

## 作者：λᴉʍ (赞：1)

这个做法只要$7$次询问就行了，比std优秀一点。

考虑$query(S)=\max_{a,b\in S}dist(a,b)$，答案就是$query(\{1,2,...,n\})$。

$query(S)$可以先将$S$分成两个集合$A,B$，询问$A,B$，再分别处理$query(A)$和$query(B)$，$query(S)$就是这些的最大值。如果A,B尽量平均分配，那么只需要$\log n$次就可以将$S$分的只剩一个点。但是这样好像还是$O(n)$的，然后又发现可以分别处理$query(A)$和$query(B)$的时候，将$A$分成$A_1,A_2$，$B$分成$B_1,B_2$，那么询问可以合在一起询问。每一层都合在一起询问就只需要$\log n$了（所以$n$还能出大一点？）

https://codeforces.com/contest/1146/submission/53065055

https://www.cnblogs.com/xzz_233/p/10744690.html

---

## 作者：LJC00753 (赞：0)

交换题。

一棵树

每次问两个集合，回答他们的最远点对

求这棵树是直径

------------------

我们可以每次询问的时候 按照编号二进制每一位 0/1 分组询问

这样，对于任意一组点 显然会在至少一位二进制不同 ，则会在一次询问被分为不同的两组

这样相当于我们就询问了任意两组点的距离最大值

也就求出了树的直径

```
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define LL long long
#define INF (LL)(0x3f3f3f3f)*(LL)0x3f3f3f3f
#define MAXN 100005 

LL n,m,t;
int a[MAXN],b[MAXN],cnt1,cnt2;
int ans = 0;

void qaq(int x) {// 按照第x位 分组
	cnt1 = 0;
	cnt2 = 0;
	for(int i = 1; i <= n; i ++) 
	if(i&(1<<x)){
		cnt1 ++;
		a[cnt1] = i;//第一组
	} else  {
		cnt2 ++;
		b[cnt2] = i;//第二组
	}
	if(cnt1 == 0 || cnt2 == 0) return;
	cout<<cnt1<<" "<<cnt2<<" ";
	for(int i = 1; i <= cnt1; i ++) cout<<a[i]<<" ";
	for(int i = 1; i <= cnt2; i ++) cout << b[i] <<" "; 
	cout<<"\n";
	cout.flush();
	int y;
	cin >> y;
	ans = max(ans,y);
	
}

signed main()
{
	cin >> t;
	while(t --) {
		cin >> n;
		ans = 0;
		for(int i = 0; i <= 7; i ++)
			qaq(i);
		cout<<-1<<" "<<ans<<"\n";
		cout.flush();
	}
	return 0;
 } 
```

---

