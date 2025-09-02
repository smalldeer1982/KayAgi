# Elimination of a Ring

## 题目描述

Define a cyclic sequence of size $ n $ as an array $ s $ of length $ n $ , in which $ s_n $ is adjacent to $ s_1 $ .

Muxii has a ring represented by a cyclic sequence $ a $ of size $ n $ .

However, the ring itself hates equal adjacent elements. So if two adjacent elements in the sequence are equal at any time, one of them will be erased immediately. The sequence doesn't contain equal adjacent elements initially.

Muxii can perform the following operation until the sequence becomes empty:

- Choose an element in $ a $ and erase it.

For example, if ring is $ [1, 2, 4, 2, 3, 2] $ , and Muxii erases element $ 4 $ , then ring would erase one of the elements equal to $ 2 $ , and the ring will become $ [1, 2, 3, 2] $ .

Muxii wants to find the maximum number of operations he could perform.

Note that in a ring of size $ 1 $ , its only element isn't considered adjacent to itself (so it's not immediately erased).

## 说明/提示

In the first test case, you can erase the second element first, then erase the remaining elements one by one in any order. In total, you can perform the operation $ 4 $ times. Note that if you erase the first element first, then the sequence will be turned into $ [2,3,2] $ and then immediately become $ [2,3] $ .

In the second test case, you can erase the first element first, then the sequence becomes $ [2,1] $ . Then you can erase all remaining elements one by one in any order.

## 样例 #1

### 输入

```
3
4
1 2 3 2
4
1 2 1 2
1
1```

### 输出

```
4
3
1```

# 题解

## 作者：linyihdfj (赞：1)

## CF1761B Elimination of a Ring
### 题目分析：
好恶心啊，一开始想了两个贪心都错了。

考虑如果含有不止两个数，就可以使用其中一个数去删掉另外的数，然后这样互相删最后一定删完，也就是答案一定是 $n$。

而如果只含有两个数，那么一定是形如 $abab\cdots$ 的形式，会发现前 $n-2$ 个我们没办法，只可以获得 $\dfrac{n-2}{2}$ 的贡献，而对于最后两个我们都可以得到，所以最后的答案就是 $\dfrac{n-2}{2} + 2$。

需要特判 $n=1$ 的情况。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int a[N],n;
bool vis[N];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++)	scanf("%d",&a[i]);
		int cnt = 0;
		for(int i=1; i<=n; i++)	if(!vis[a[i]])	cnt++,vis[a[i]] = true;
		if(cnt > 2)	printf("%d\n",n);
		else	printf("%d\n",n == 1 ? 1 : (n - 2) / 2 + 2);
		for(int i=1; i<=n; i++)	vis[a[i]] = false;
	}
	return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[CF1761B imination of a Ring ](https://www.luogu.com.cn/problem/CF1761B)

我这个屑这题又吃一罚时。

## 思路

本题目为简单的贪心和构造。

先读入序列。

计算序列不重复元素个数。

如果只有一个元素，就直接输出 $1$。

如果不重复元素个数大于两个，直接输出 $n$。

其他情况一定是有两种不同元素，那么序列一定是 `1 2 1 2 1 2 ...`，那么答案就是 ${n\over 2}+1$。

## 代码

```cpp
#include <bits/stdc++.h>
const int N = 205;
int a[N];
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int len = unique(a + 1, a + n + 1) - a - 1;
    if (len == 1) //只有一种元素
      cout << 1;
    else if (len == 2) //有两种元素
      cout << min(n, (n >> 1) + 1);
    else //多于两种元素
      cout << n;
    cout << '\n';
  }
  return 0;
}
```

我的 [AC 记录](https://www.luogu.com.cn/record/95358402)

---

## 作者：Engulf (赞：0)

若仅有 2 种数字出现，即形如 $a, b,\dots a,b$，我们仅能删除 $\lfloor \dfrac{n}{2} \rfloor + 1$ 次。

否则，一定可以完成 $n$ 次，两种相同的数字间一定隔了至少 2 个数字，就不会发生消除。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 105;
int n, a[N];
int cnt[N];

int main()
{
	int T;
	cin >> T;
	while (T -- )
	{
		memset(cnt, 0, sizeof cnt);
		cin >> n;
		int typ = 0;
		for (int i = 1; i <= n; i ++ ) cin >> a[i], cnt[a[i]] ++ ;
		for (int i = 1; i <= n; i ++ ) typ += cnt[i] > 0;
		if (n > 2 && typ == 2) cout << n / 2 + 1 << endl;
		else cout << n << endl;
	}
	return 0;
}
```

---

## 作者：KingPowers (赞：0)

## 题意

给你一个长度为 $n$ 的环，每次可以在环上选择一个数删除，如果被删除的数相邻两个数相同，那么再从这两个数中选择一个删除，最大化操作次数。

## 正文

这里是一个赛时脑抽了，想了不少时间的蒟蒻。

稍微手模一下，不难得出一个结论：除非环的长度为偶数并且整个环都是两个数字交替出现，不然操作次数一定为 $n$。

这个证明的话不是很好表达，但是应该不难理解。

然后考虑下当出现如上所述的情况下的答案：如果整个环都是两个数字交替出现，那么我们每一次操作都一定会删除掉两个数，直到最后只剩下两个数的时候，我们再把最后的两个挨个删除，那么答案即为 $\frac{n}{2}+1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fx first
#define fy second
#define mkp make_pair
#define umap unordered_map
using namespace std;
const int N=2e5+5;
const int inf=1e18;
int read(){
	int ans=0,flag=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') flag=-1;
	for(;isdigit(ch);ch=getchar()) ans=ans*10+(ch^48);
	return ans*flag;
}
int T,n,m,a[N],b[N];
signed main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		if(n&1||n==2) printf("%lld\n",n);
		else{
			bool flag=1;
			for(int i=3;i<n;i++) if(a[i]!=a[i-2]) flag=0;
			for(int i=4;i<=n;i++) if(a[i]!=a[i-2]) flag=0; 
			if(flag) printf("%lld\n",1+(n/2));
			else printf("%lld\n",n);
		}
	}
	return 0;
}
```



---

