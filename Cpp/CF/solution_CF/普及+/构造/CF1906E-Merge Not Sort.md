# Merge Not Sort

## 题目描述

You are currently researching the Merge Sort algorithm. Merge Sort is a sorting algorithm that is based on the principle of Divide and Conquer. It works by dividing an array into two subarrays of equal length, sorting each subarrays, then merging the sorted subarrays back together to form the final sorted array.

You are particularly interested in the merging routine. Common merge implementation will combine two subarrays by iteratively comparing their first elements, and move the smaller one to a new merged array. More precisely, the merge algorithm can be presented by the following pseudocode.

```
<pre class="verbatim"><br></br>    Merge(A[1..N], B[1..N]):<br></br>        C = []<br></br>        i = 1<br></br>        j = 1<br></br>        while i <= N AND j <= N:<br></br>            if A[i] < B[j]:<br></br>                append A[i] to C<br></br>                i = i + 1<br></br>            else:<br></br>                append B[j] to C<br></br>                j = j + 1 <br></br>        while i <= N:<br></br>            append A[i] to C<br></br>            i = i + 1 <br></br>        while j <= N:<br></br>            append B[j] to C<br></br>            j = j + 1 <br></br>        return C<br></br>
```

During your research, you are keen to understand the behaviour of the merge algorithm when arrays $ A $ and $ B $ are not necessarily sorted. For example, if $ A = [3, 1, 6] $ and $ B = [4, 5, 2] $ , then $ \text{Merge}(A, B) = [3, 1, 4, 5, 2, 6] $ .

To further increase the understanding of the merge algorithm, you decided to work on the following problem. You are given an array $ C $ of length $ 2 \cdot N $ such that it is a permutation of $ 1 $ to $ 2 \cdot N $ . Construct any two arrays $ A $ and $ B $ of the same length $ N $ , such that $ \text{Merge}(A, B) = C $ , or determine if it is impossible to do so.

## 说明/提示

Explanation for the sample input/output #1

The solution $ A = [3, 1, 4] $ and $ B = [5, 2, 6] $ is also correct.

Explanation for the sample input/output #2

The solution $ A = [1, 2, 3, 4] $ and $ B = [5, 6, 7, 8] $ is also correct.

## 样例 #1

### 输入

```
3
3 1 4 5 2 6```

### 输出

```
3 1 6
4 5 2```

## 样例 #2

### 输入

```
4
1 2 3 4 5 6 7 8```

### 输出

```
2 3 5 7
1 4 6 8```

## 样例 #3

### 输入

```
2
4 3 2 1```

### 输出

```
-1```

# 题解

## 作者：FFTotoro (赞：4)

考虑怎样的一段数一定要被绑在一块（即一定要在同一个序列并且相邻），我们可以通过如下的方式来寻找这样的一段：

扫一遍输入序列 $c$，对于一个数，如果是新扫到的，那么将它作为块头，一直往右扫直到扫到比它大的就停止，比它大的那个作为另一个块的块头……以此往复。

这样做显然是正确的。因为如果一个块的任意一个非块头元素放到另一个序列都会被先放到 $c$。

然后把所有块打包起来，看能不能把块往 $a,b$ 里放使得 $a,b$ 的大小都为 $n$。这一部分做一个背包即可，中间借助 `std::set` 构造方案。

最后记得对于最终序列中的每一个块按照块头元素大小升序排序。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int n,l=0; cin>>n;
  vector<int> c(n<<1);
  for(auto &i:c)cin>>i;
  vector<int> h=c,s(n<<1);
  for(int i=1;i<n<<1;i++)
    if(h[i]<h[i-1])h[i]=h[i-1],s[i-1]=1;
    // 标记一下位置
  vector<vector<int> > w,a,b;
  while(l<n<<1){
    vector<int> v;
    while(l<n<<1&&s[l])
      v.emplace_back(c[l++]);
    v.emplace_back(c[l++]);
    w.emplace_back(v);
  } // 把所有块找出来
  vector<set<int> > f(n+1);
  for(int j=0;j<w.size();j++)
    for(int i=n-1;~i;i--)
      if(!i||!f[i].empty()){
        if(i+w[j].size()<=n&&f[i+w[j].size()].empty()){
          for(int k:f[i])f[i+w[j].size()].emplace(k);
          f[i+w[j].size()].emplace(j);
        }
      } // 背包 DP，构造
  if(f[n].empty()){cout<<"-1\n"; return 0;}
  for(int i=0;i<w.size();i++)
    if(f[n].find(i)==f[n].end())b.emplace_back(w[i]);
    else a.emplace_back(w[i]); // 分配到 2 个序列
  sort(a.begin(),a.end()); // 对块进行排序
  sort(b.begin(),b.end());
  for(auto i:a)for(int j:i)cout<<j<<' ';
  cout<<endl; // 直接遍历输出
  for(auto i:b)for(int j:i)cout<<j<<' ';
  cout<<endl;
  return 0;
}
```

---

## 作者：Xiphi (赞：0)

一个 __可能__ 更好理解的做法。考虑从大往小一次考虑。对于一个长度为 $n$ 的序列，则 $n$ 及其以后的数必然是“固定”在一起的。

也就是说不论其他如何变化，这些 $n$ 及其以后的数必然是在 $A$ 或 $B$ 数组的最尾端且按原来的顺序挨着的。

那么我们就可以递归的考虑，每次取出一段 $n$ 到结尾的段，放到某个数组的最后边（还未被填的地方的最后）。但这样无法得知每次要放在 $A$ 还是 $B$ 数组里，就可能会导致输出无解情况。

那么我们现在把这一段段“固定在一起”的东西看成若干个物品，代价为其长度。也就是说要求一个代价和为 $n$ 的物品子集，跑背包即可。记得输出时要按原来 $C$ 数组中段与段的相对关系从前到后输出。

为了方便输出，笔者使用了记忆化的写法来跑背包。

```cpp
#include<bits/stdc++.h>
#define _for(i,x,y) for(int i=x;i<=y;++i)
#define _forp(i,x,y,z) for(int i=x;i<=y;i+=z)
#define _rep(i,x,y) for(int i=x;i<y;++i)
using namespace std;
int n;
int a[4005];
int abc;
int f[4005];
vector<pair<int,int>> v,ans;
bool V[4005],vis[4005];
bool dfs(int x){
	if(f[x]!=0x3f3f3f3f) return f[x];
	if(x==n/2){
		return 1;
	}else if(x>n/2) return 0;
// 	else{
	int cnl=0;
	for(auto i:v){
		if(!V[cnl]){
			V[cnl]=1;
			bool X=dfs(x+i.first);
			if(X){
				ans.push_back({i.second,i.first});
				return f[x]=1;
			}
			V[cnl]=0;
		}
		cnl++;
	}
	return f[x]=0;
}
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n;n*=2;
	_for(i,1,n){
		cin>>a[i];
	}
	int l=a[1],len=1;
	a[n+1]=0x3f3f3f3f;
	a[0]=0x3f3f3f3f;
	_for(i,2,1+n){
		if(a[i]>l){
			v.push_back({len,i-len});
			l=a[i];len=1;
		}else{
			len++;
		}
	}
	memset(f,0x3f,sizeof f);
	bool X=dfs(0);
	if(!X){
		cout<<"-1\n";return 0;
	}
	sort(ans.begin(),ans.end());
	for(auto i:ans){
		_for(j,i.first,i.first+i.second-1){
			cout<<a[j]<<' ';
			vis[j]=1;			
		}
	}
	cout<<'\n';
	_for(i,1,n){
		if(!vis[i]) cout<<a[i]<<' ';
	}
	return 0;
}

```

---

## 作者：xyz105 (赞：0)

一定程度上参考了 [官方英文题解](https://competition.binus.ac.id/icpc2023/problem_analysis.pdf)。


### 题目描述

你可以用 归并排序 中合并两个序列的方式来合并两个长度为 $n$ 的、**不一定**有序的两个序列 $A,B$，设合并出的序列为 $C$，它的长度显然为 $2n$。

现给定序列 $C$，要求据此倒推出可能的序列 $A,B$。


### 解题思路

先思考一下原本合并 $A,B$ 的过程。假设 $A_1<B_1$，那么 $A_1$ 肯定要被塞进 序列 $C$ 里；接着依次判断 $A_2,A_3,A_4,\ldots$ 是否小于 $B_1$，是则继续塞进 序列 $C$，否则塞进去的就变成 $B_1$。

考虑将原本的过程再细分一下。假设 $P$ 是最小的且满足 $A_1<A_P$ 的数（即 $A_P$ 是从左向右数第一个大于 $A_1$ 的数字），则 $A_2,A_3,\ldots,A_{P-1}$ 都小于 $A_1$，故它们都像 $A_1$ 一样因为小于 $B_1$ 而被塞进 序列 $C$。序列 $A$ 中剩下的那些数形成了新的 序列 $A$，故之后再进行上述操作即可。

对于 $A_1>B_1$ 的情况同理。

于是构造方式便出来了。将 序列 $C$ 划分成若干个连续段，要求 每一段的第一个数 都要小于 下个相邻段的第一个数；在这若干段中任意选择一些段放入 序列 $A$，余下的放入 序列 $B$，即可构造合法方案。

还有一个问题是，序列 $A,B$ 的长度都必须为 $n$。其实只看 序列 $A$ 的长度是否为 $n$ 就够了，因为只要确定 $A$ 的长度，$B$ 的长度也就自然确定了（总共有固定 $2n$ 个数字）。这相当于要求取出的段的总长为 $n$，背包 DP 判断可行性即可，顺便在转移过程中记录方案。

总时间复杂度 $O(n^2)$。


### 参考代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 2020;

int n, a[MAXN], b[MAXN], l[MAXN], r[MAXN], b_cnt = -1;
bool ok[MAXN]; int pre[MAXN];
bool mark[MAXN];

int main()
{
	scanf("%d", &n);
	
	int i1 = 0;
	for (int i = 1, i2 = 0; i <= 2 * n; i++)
	{
		scanf("%d", a + i);
		if (i2 > a[i]) i1++;
		else i2 = a[i], b[++b_cnt] = i1, l[b_cnt] = i - i1, r[b_cnt] = i - 1, i1 = 1;
	}
	b[++b_cnt] = i1, l[b_cnt] = 2 * n + 1 - i1, r[b_cnt] = 2 * n;
	
	ok[0] = 1;
	for (int i = 1; i <= b_cnt; i++)
		for (int j = 2 * n; j >= b[i]; j--)
			if (!ok[j] && ok[j - b[i]]) ok[j] = 1, pre[j] = i;
	if (!ok[n]) return printf("-1"), 0;
	
	i1 = n;
	while (i1)
	{
		for (int i = l[pre[i1]]; i <= r[pre[i1]]; i++) mark[i] = 1;
		i1 -= b[pre[i1]];
	}
	for (int i = 1; i <= 2 * n; i++) if (mark[i]) printf("%d ", a[i]);
	puts("");
	for (int i = 1; i <= 2 * n; i++) if (!mark[i]) printf("%d ", a[i]);
	
	return 0;
}
```

---

