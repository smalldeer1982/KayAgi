# [NWRRC 2016] Easy Reading

## 题目描述

Eugene正在读一本无聊的书。为了使阅读更有趣，他在阅读的同时同时作画。 他有一张方格纸。 所有的方格一开始都是空的。

Eugene一开始在一个方格上作画。让后他随机翻开一页并开始阅读。当他遇到字母 `u`  时, 他把笔向上移动一格并在这格上画画。 当他看到 `d`时, 他会做同样的操作，但是向下移动一格而不是向上移动一格。 `l` ,`r`分别是向左和向右一格。 如果这个单元格已经画过了他会再画一次。

现在你有一张纸与这本书中的内容。 现在你想知道这张纸上的图片是否可能被Eugene在某一时刻画过。 记住：Eugene可以只使用用这个内容的子字符串。

## 说明/提示

时限: 2 s, 内存限制: 256 MB.

## 样例 #1

### 输入

```
43
you should read statement really carefully.
3 6
...XX.
..XXX.
...XXX
```

### 输出

```
YES
3 42
```

## 样例 #2

### 输入

```
43
you should read statement really carefully.
3 2
XX
XX
XX
```

### 输出

```
NO
```

# 题解

## 作者：ix35 (赞：1)

巨大多简单题。

两个图案相等，至少要满足它们的点数相等，这里就有一个单调性。

考虑双指针，当前右端点扫描到 $r$，我们只需要将左端点移动到位置 $l$ 使得 $[l,r]$ 内画出的图恰有和给定图案一样的点数。

接下来的问题有两个：

- 如何求当前图案的点数：不妨设起点是 $(0,0)$，由于我们只需要 $2n\times 2m$ 个点，所以对每个位置维护当前有几笔经过了它，事实上更简单的实现是直接用 map 维护每个二元组有几笔经过它，当这个值清零是点数减少 $1$，当这个值从 $0$ 变成 $1$ 时点数增加 $1$；

- 如果比较两个图案：首先我们将它们对齐：让它们的左边界和上边界分别是 $x=0,y=0$，然后就可以用哈希比较了，设计哈希时要支持平移，所以对 $(x,y)$ 设定 $a^xb^y$ 的哈希值就比较合适。

时间复杂度为 $O(nm+l\log l)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010,P1=998244353,P2=10000019,P3=1000000009;
int inv1,inv2,l,m,n,cnt,cnt2,tot,hs,hs2,mnx,mny,cur,pos[MAXN],typ[MAXN],nx[MAXN],ny[MAXN];
string s;
multiset <int> mx,my;
map <pair<int,int>,int> mp;
int qpow (int a,int b) {
	if (b<0) {b=P3-1+b;}
	int res=1;
	while (b) {
		if (b&1) {res=(1ll*res*a)%P3;}
		a=(1ll*a*a)%P3,b>>=1;
	}
	return res;
}
int calc () {
	int mnnx=*(mx.begin()),mnny=*(my.begin());
	return (1ll*hs2*((1ll*qpow(inv1,mnnx)*qpow(inv2,mnny))%P3))%P3;
}
int main () {
	getline(cin,s);
	int len=s.length();
	for (int i=0;i<len;i++) {
		if (s[i]>='0'&&s[i]<='9') {l=l*10+s[i]-'0';}
	}
	getline(cin,s);
	len=s.length();
	nx[0]=ny[0]=0;
	for (int i=0;i<len;i++) {
		if (s[i]=='u') {
			cnt++;
			typ[cnt]=1,pos[cnt]=i+1,nx[cnt]=nx[cnt-1]-1,ny[cnt]=ny[cnt-1];
		} else if (s[i]=='d') {
			cnt++;
			typ[cnt]=2,pos[cnt]=i+1,nx[cnt]=nx[cnt-1]+1,ny[cnt]=ny[cnt-1];
		} else if (s[i]=='l') {
			cnt++;
			typ[cnt]=3,pos[cnt]=i+1,nx[cnt]=nx[cnt-1],ny[cnt]=ny[cnt-1]-1;
		} else if (s[i]=='r') {
			cnt++;
			typ[cnt]=4,pos[cnt]=i+1,nx[cnt]=nx[cnt-1],ny[cnt]=ny[cnt-1]+1;
		}
	}
	scanf("%d%d",&n,&m);
	mnx=n,mny=m;
	for (int i=1;i<=n;i++) {
		cin >> s;
		for (int j=0;j<m;j++) {
			if (s[j]=='X') {
				mnx=min(mnx,i),mny=min(mny,j+1),cnt2++;
				hs=(hs+(1ll*qpow(P1,i)*qpow(P2,j+1))%P3)%P3;
			}
		}
	}
	inv1=qpow(P1,P3-2),inv2=qpow(P2,P3-2);
	hs=(1ll*hs*((1ll*qpow(inv1,mnx)*qpow(inv2,mny))%P3))%P3;
	tot=1,hs2=1;
	mx.insert(0),my.insert(0);
	mp[make_pair(0,0)]=1;
	while (cur<cnt&&tot<cnt2) {
		cur++;
		mx.insert(nx[cur]),my.insert(ny[cur]);
		if (mp.find(make_pair(nx[cur],ny[cur]))==mp.end()) {
			tot++;
			mp[make_pair(nx[cur],ny[cur])]=1;
			hs2=(hs2+(1ll*qpow(P1,nx[cur])*qpow(P2,ny[cur]))%P3)%P3;
		} else if (mp[make_pair(nx[cur],ny[cur])]==0) {
			mp[make_pair(nx[cur],ny[cur])]=1;
			tot++;
			hs2=(hs2+(1ll*qpow(P1,nx[cur])*qpow(P2,ny[cur]))%P3)%P3;
		} else {
			mp[make_pair(nx[cur],ny[cur])]++;
		}
	}
	if (calc()==hs) {
		printf("YES\n1 %d\n",pos[cur]);
		return 0;
	}
	for (int i=1;i<cnt;i++) {
		mx.erase(mx.find(nx[i-1])),my.erase(my.find(ny[i-1]));
		if (--mp[make_pair(nx[i-1],ny[i-1])]==0) {
			tot--;
			hs2=(hs2-(1ll*qpow(P1,nx[i-1])*qpow(P2,ny[i-1]))%P3+P3)%P3;
		}
		while (cur<cnt&&tot<cnt2) {
			cur++;
			mx.insert(nx[cur]),my.insert(ny[cur]);
			if (mp.find(make_pair(nx[cur],ny[cur]))==mp.end()) {
				tot++;
				mp[make_pair(nx[cur],ny[cur])]=1;
				hs2=(hs2+(1ll*qpow(P1,nx[cur])*qpow(P2,ny[cur]))%P3)%P3;
			} else if (mp[make_pair(nx[cur],ny[cur])]==0) {
				mp[make_pair(nx[cur],ny[cur])]=1;
				tot++;
				hs2=(hs2+(1ll*qpow(P1,nx[cur])*qpow(P2,ny[cur]))%P3)%P3;
			} else {
				mp[make_pair(nx[cur],ny[cur])]++;
			}
		}
		if (calc()==hs) {
			printf("YES\n%d %d\n",pos[i+1],pos[cur]);
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}

```


---

