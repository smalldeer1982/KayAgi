# 一流の団子職人 (Super Dango Maker)

## 题目描述

有一个竞赛任务，请求你选出一组团子并判断某个二进制数组的状态。

### 输入格式

输入第一行提供整数 $N$ 和 $M$。

### 查询操作

我们设想有一个长度为 $N \times M$ 的数组 $A$。对于数组中的每一个团子，第 $i$ 个被选中时 $A[i] = 1$，未被选中时 $A[i] = 0$。

在进行查询操作时，输出字母 `Q`，紧接着无需空格直接输出数组 $A$ 的二进制表示，最后进行换行。

例如，假设 $A = (0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0)$，在查询阶段你需要输出 `Q 4` 并换行。

查询返回结果将在接下来的输入行中给出。

### 回答操作

同样地，我们面对的是一个长度为 $N \times M$ 的数组 $A$，根据条件选取相应的团子。当选择第 $i$ 个团子时 $A[i] = 1$，否则 $A[i] = 0$。

此时输出字母 `A`，紧接着输出二进制数组 $A$ 的表示，最后换行。

之后将会读取到输入行中提供的数值 `0`。

### 其他说明

如果在输出过程中，格式不符合要求或者条件未达成，输入将变为 `-1`。此时你需要立即终止程序的运行。

完成 $M$ 次回答操作后，输出 `F`。

**请确保每次输出之后都刷新输出流，以确保内容被及时输出。**

 **本翻译由 AI 自动生成**

# 题解

## 作者：Augen_stern (赞：2)

## Part 1: 分析求解

中文题面可以看 [UOJ](https://uoj.ac/problem/731)，这里就不过多赘述。

我们可以先考虑一种暴力：

每次从左往右扫描整个团子集合，插入进询问集合，直到询问出此时你的询问集合中包含了一串团子（即每种颜色都至少有一个）；

接着，再对这个询问集合，尝试删掉每一个团子，看能否包含一串完整的团子，若删掉后无影响，则直接删了，否则，它就是在这个集合中那一串团子中，是必要的，可以作为待会儿输出的元素。

然后重复操作，就把整个团子集合给拆开了。

可惜这个暴力效率较低，考虑优化：

我们可以二分出包含一串团子的集合的左端点和右端点，然后再进行上述操作。但这样会被特殊数据卡，所以直接 ```random_shuffle``` 一下就可以了，因为考虑所有颜色随机分布在数轴上，包含所有颜色的期望长度就是颜色种数，所以这样在随机数据下很快，而在数据中询问次数差不多就 $40000$ 出头而已。

## Part 2: CODE

```cpp
//#pragma GCC optimize(3)
#include<iostream>
#include<climits>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<vector>
#include "dango3.h"
//#include<random>
//#include<chrono>
//#define int long long
//#define double long double
using namespace std;
const long long INF=LLONG_MAX/2ll;
const long long mod=998244353;
//const long long mod=1000000007;
const double Pai=acos(-1);
const double eps=1e-8;
vector<int> v,ex;
int n,m,cnt=0;
int vst[1000005],be[1000005],vis[1000005],b[1000005];
int mp[405][30];
bool check(int l,int r) {
	for(int i=l;i<=r;i++) v.push_back(b[i]);
	int res=Query(v);v.clear();
	return res>=1;
}
bool del(int x,int l,int r) {
	for(int i=l;i<=r;i++) if(i!=x&&!vst[i]) v.push_back(b[i]);
	int res=Query(v);v.clear();
	return res>=1;
}
void solve() {
	b[0]=0;
	for(int i=1;i<=n*m;i++) {
		if(!vis[be[i]]) b[++b[0]]=be[i];
	}
	int l=1,r=b[0],L=0,R=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(1,mid)) r=mid-1,R=mid;
		else l=mid+1;
	}
	l=1,r=R,L=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		if(check(mid,R)) l=mid+1,L=mid;
		else r=mid-1;
	}
	for(int i=L;i<=R;i++) if(del(i,L,R)) vst[i]=1;
	for(int i=L;i<=R;i++) if(!vst[i]) ex.push_back(b[i]),vis[b[i]]=1;
	for(int i=1;i<=b[0];i++) vst[i]=0;
	Answer(ex);ex.clear();
	random_shuffle(be+1,be+n*m+1);
}
void Solve(int nn,int mm) {
	n=nn,m=mm;
	for(int i=1;i<=n*m;i++) be[i]=i;
	random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);
	random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);random_shuffle(be+1,be+n*m+1);
	for(int i=1;i<m;i++) solve();
	for(int i=1;i<=n*m;i++) if(!vis[be[i]]) ex.push_back(be[i]);
	Answer(ex);ex.clear();
}
```


---

