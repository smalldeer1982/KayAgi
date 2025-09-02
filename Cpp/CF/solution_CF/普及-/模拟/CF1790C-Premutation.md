# Premutation

## 题目描述

A sequence of $ n $ numbers is called permutation if it contains all integers from $ 1 $ to $ n $ exactly once. For example, the sequences \[ $ 3, 1, 4, 2 $ \], \[ $ 1 $ \] and \[ $ 2,1 $ \] are permutations, but \[ $ 1,2,1 $ \], \[ $ 0,1 $ \] and \[ $ 1,3,4 $ \] — are not.

Kristina had a permutation $ p $ of $ n $ elements. She wrote it on the whiteboard $ n $ times in such a way that:

- while writing the permutation at the $ i $ -th ( $ 1 \le i \le n) $ time she skipped the element $ p_i $

 So, she wrote in total $ n $ sequences of length $ n-1 $ each.For example, suppose Kristina had a permutation $ p $ = $ [4,2,1,3] $ of length $ 4 $ . Then she did the following:

1. Wrote the sequence $ [2, 1, 3] $ , skipping the element $ p_1=4 $ from the original permutation.
2. Wrote the sequence $ [4, 1, 3] $ , skipping the element $ p_2=2 $ from the original permutation.
3. Wrote the sequence $ [4, 2, 3] $ , skipping the element $ p_3=1 $ from the original permutation.
4. Wrote the sequence $ [4, 2, 1] $ , skipping the element $ p_4=3 $ from the original permutation.

You know all $ n $ of sequences that have been written on the whiteboard, but you do not know the order in which they were written. They are given in arbitrary order. Reconstruct the original permutation from them.

For example, if you know the sequences $ [4, 2, 1] $ , $ [4, 2, 3] $ , $ [2, 1, 3] $ , $ [4, 1, 3] $ , then the original permutation will be $ p $ = $ [4, 2, 1, 3] $ .

## 说明/提示

The first test case is described in the problem statement.

In the second test case, the sequences are written in the correct order.

## 样例 #1

### 输入

```
5
4
4 2 1
4 2 3
2 1 3
4 1 3
3
2 3
1 3
1 2
5
4 2 1 3
2 1 3 5
4 2 3 5
4 1 3 5
4 2 1 5
4
2 3 4
1 3 4
1 2 3
1 2 4
3
2 1
1 3
2 3```

### 输出

```
4 2 1 3 
1 2 3 
4 2 1 3 5 
1 2 3 4 
2 1 3```

# 题解

## 作者：LegendaryGrandmaster (赞：9)

贪心。

用结构体记录这个数的值，以及这个数的权值。

权值计算如下：

$a_1,a_2,a_3,a_4, \dots ,a_n$ 权值为 $n,n-1,n-2,n-3,n-4, \dots ,1$。

那么第 $i$ 项的权值即为 $n-i+1$，之后我们只需要按权值排序后输出数字本身的值即可。


代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int id,x;
}a[200001];
bool cmp(node a,node b)
{
	return a.x>b.x;
}
int main()
{
	int t;
	cin>>t;
	while(t--){
		memset(a,0,sizeof(a));
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<n;j++){
				int x;
				cin>>x;
				a[x].x+=n-j+1;
				a[x].id=x;
			}
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)cout<<a[i].id<<' ';
		puts("");
	}
}
```

---

## 作者：loser_seele (赞：1)

提供一个不一样的思路。

前置知识：拓扑排序。

具体做法：对于输入的所有 $ p $，在 $ p_i $ 和 $ p_{i+1} $ 之间连有向边表示 $ p_i $ 在 $ p_{i+1} $ 前面，然后拓扑排序即可。

这么做的正确性：首先边只会由编号小的点连向编号大的，所以不会出现环，则有解。然后发现建出的图一定是每个点都有 $ n-2 $ 条边（包括入边和出边），所以这个算法一定能找到至少一组解，又因为解唯一，故算法正确。

时间复杂度 $ \mathcal{O}(Tn^2) $，因为只需要建 $ n^2 $ 条边，达到了理论下界。

代码：

```cpp
#import <bits/stdc++.h>
using namespace std;
const int maxn=2e6+10;
vector<int>out[maxn];
int in[maxn];
int mapp[1010][1010];
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
    int n; 
    cin>>n;
    for(int i=1;i<=n;i++)
    in[i]=0,out[i].clear();
    for(int i=1;i<=n;i++)
    for(int j=1;j<n;j++)
    cin>>mapp[i][j];
    for(int i=1;i<=n;i++)
    for(int j=1;j<n-1;j++)
    {
        int u=mapp[i][j],v=mapp[i][j+1];
        out[u].push_back(v);
        ++in[v];
    }
    priority_queue<int,vector<int>,greater<int> >que;

    for(int i=1;i<=n;i++)
    if(!in[i])
    que.push(i);
    vector<int>res; 
    res.reserve(n);
    while(!que.empty())
    {
        int node=que.top();
        que.pop(); 
        res.push_back(node);
        for (auto x:out[node])
        {
            --in[x];
            if(!in[x])
            que.push(x);
        }
    }
    if(res.size()!=n)
    cout<<-1;
    else 
    for(auto x:res)
    cout<<x<<' ';
    cout<<'\n';
    }
}
```

---

## 作者：瀛洲仙子 (赞：1)

### 思路简述
此题显然**不能**用全排列。       
于是考虑模拟。      
显然，每个排列都是正解的子序列，所以只需要考虑在第一个排列中某个位置插入那个第一个排列中没有的数，满足其他所有序列都是这个排列的**子序列**。
思路为：
```
input: n,first_permutation,*other_permutations
not_find_num=0
for i=1 to n{
	if i not find in first_permutation{
    	not_find_num=i 
        break}}
for pos=1 to n do{
	insert not_find_num into first_permutation on index pos
    	   if ok{
           output
      	   break }
        delete index pos}
```
### 完整代码
根据以上思路，[无注释代码](https://codeforces.com/contest/1790/submission/191063229)如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int tmp[105],arr[105][105];
int n;
void insert(int pos,int x)
{
 for(int t=n-1;t>=pos;--t)
  tmp[t+1]=tmp[t];
 tmp[pos]=x;return;
}
bool check()
{
 for(int i=1;i<n;++i)
 {
  int point=1;
  for(int j=1;j<=n;++j)
   if(tmp[j]==arr[i][point])
    ++point;
  if(point^n)return false;
 }
 return true;
}
void Delete(int pos)
{
 for(int t=pos;t<n;++t)
  tmp[t]=tmp[t+1];
 tmp[n]=0;return;
}
int main()
{
 int t;cin>>t;while(t--)
 {
  memset(tmp,0,sizeof(tmp));
  memset(arr,0,sizeof(arr));
  cin>>n;
  for(int i=1;i<n;++i)
   cin>>tmp[i];
  for(int i=1;i<n;++i)
   for(int j=1;j<n;++j)
    cin>>arr[i][j];
  int lef=0;
  for(int i=1;i<=n;++i)
  {
   bool flag=false;
   for(int j=1;j<n;++j)
    if(tmp[j]==i)
     {flag=true;break;}
   if(!flag){lef=i;break;}
  }
  for(int pos=1;pos<=n;++pos)
  {
   insert(pos,lef);
   if(check())
   {
    for(int i=1;i<=n;++i)
     cout<<tmp[i]<<' ';
    cout<<endl;break;
   }
   Delete(pos);
  }
 }
}
```
----------------------
**珍爱生命，远离抄袭！**

---

## 作者：DANIEL_x_ (赞：0)

思路：一定有一个序列没有包含原始序列的第一项，所以只要知道那个序列并知道第一项就可以原始得出序列。

细节：可以先记录前两个序列的第一项，判断是否一样。

如果一样，就在后面的序列里找到没有包含第一项的序列。

如果不一样，就判断那个是有第一项的数列即可。

具体看代码。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,n,s,r,ans[105];
int a[105][105];
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n-1;j++)
				cin>>a[i][j];
		int t1=a[1][1],t2=a[2][1],t3=a[3][1];
		if(t1==t2)
		{
			int pos=0;
			for(int i=3;i<=n;i++)
				if(a[i][1]!=t1&&a[i][1]!=t2)
					pos=i;
			ans[1]=t1;
			for(int i=2;i<=n;i++)
				ans[i]=a[pos][i-1];	
		}		
		else{
			if(t1==t3)
			{
				ans[1]=t1;
				for(int i=2;i<=n;i++)
					ans[i]=a[2][i-1];
			}
			else
			{
				ans[1]=t2;
				for(int i=2;i<=n;i++)
					ans[i]=a[1][i-1];
			}
		}
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<"\n";
		
	}
}
```


---

## 作者：Otue (赞：0)

## 题目大意
给定一个序列 $a$ 为 $1\sim n$ 的排列，某个聪明的小朋友对这个序列操作 $n$ 次（每次操作后会还原序列）。对于第 $i$ 次操作，会删掉数 $a_i$，并组成一个新的序列。操作 $n$ 次后，会生成 $n$ 个新的序列。现在这个小朋友想考验你，他把 $n$ 个新序列打乱顺序之后交给你，你需要求出原来的序列 $a$。
## 思路
在生成的 $n$ 个新序列当中，我们会发现总有一个数在新序列的第一个位置出现 $n-1$ 次，这个数其实就是原序列的 $a_1$。

证明：第一次操作会将 $a_1$ 删掉，其余 $n-1$ 次操作 $a_1$ 都在第一个位置。所以 $a_1$ 会在新序列第一个位置出现 $n-1$ 次。

于是我们可以求出 $a_1$，并将其拼接在第一次操作生成的序列前面，就是原本序列了。（注：第一次操作之后生成的序列不包含 $a_1$）
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 105, mod = 1e8;
#define int long long
int T, n, a[N][N];
int tong[N];

signed main() {
    cin >> T;
    while (T--) {  
        memset(tong, 0, sizeof tong);
        cin >> n;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < n; j++) {
                int c;
                cin >> c;
                a[i][j] = c;
            }
        }
        for (int i = 1; i <= n; i++) tong[a[i][1]]++;  
        // 开个桶寻找出现 n-1 次的数
        int id = 0;
        for (int i = 1; i <= n; i++) {
            if (tong[i] == n - 1) id = i;  // 找到了
        }
        int t = 0, x = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i][1] != id) t = i, x = a[i][1];
        }
        cout << id << ' ';  // 拼接在前面
        for (int i = 1; i <= n - 1; i++) {
            cout << a[t][i] << ' ';
        }
        puts("");
    }
}
```
欢迎提出问题并指正。

---

## 作者：云裳 (赞：0)

**思路**

注意到，初始的排列 $p$ 中的第一个数字只在第一次书写时消失了，而在其它 $n-1$ 次书写中仍作为第一个元素。

因此，我们可以先遍历一遍所有书写的序列，找到这些序列中的第一个元素出现了 $n-1$ 次的数，这个数便是原始排列中的 $p_1$。

找到了 $p_1$ 之后，我们再从所有的序列中找到第一次书写的序列，也就是第一个元素与 $p_1$ 不同的序列。这个序列便是初始的排列中的 $p_2,p_3,\cdots,p_n$。

最后，我们把它们依次输出就行了！



------------

**代码**

```cpp
void solve() {
  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    ll a[110][110], buc[110]; // buc[i] 表示 i 出现的次数，用于找到 p_1
    for(int i=1;i<=100;i++) buc[i] = 0; //注意清空
    for(int i=1;i<=n;i++)  for(int j=1;j<n;j++)  cin >> a[i][j];
    ll first,
        id; // first 表示 p_1，id 表示第一次书写的序列在本次测试数据的第几行
    for(int i=1;i<=n;i++) {
      buc[a[i][1]]++;
      if (buc[a[i][1]] > 1) { //超过1次的数字便是 p_1
        first = a[i][1];
        break;
      }
    }
    for(int i=1;i<=n;i++) if (a[i][1] != first) { //找到 p_2,p_3,...,p_n
      id = i;
      break;
    }
    cout << first << " ";                    //先输出p_1
    for(int i=1;i<n;i++) cout << a[id][i] << " "; //再输出 p_2,p_3,...,p_n
    cout << "\n";
  }
}

```


---

## 作者：arrow_king (赞：0)

## 题意

有一个长度为 $n$ 的排列 $p$，现在生成 $n$ 个长度为 $n-1$ 的序列 $a_1,a_2,\dots, a_n$，第 $i$ 个序列 $a_i$ 表示排列 $p$ 删除元素 $p_i$ 后剩下的元素。

现在以任意顺序给出 $n$ 个序列，恢复原排列。

$1\le t\le10^4$，$3\le n\le100$，$\sum n^2\le2\times10^5$。

## 思路

说实在的只有输入的时间复杂度是 $\mathcal O(n^2)$ 的，其他部分都是 $\mathcal O(n)$。

既然每个序列都是由原来的排列扣掉一个元素后产生的，那把这个元素找回来就行了呗。

观察到 $p$ 的第一个元素会在 $n-1$ 个生成序列中排在第一个。那显然剩下的一个就是原来的排列 $p$ 除掉开头元素后剩下的了。

接下来就好办了，线性时间找出开头元素和那个单独的序列，先输出开头元素再输出那个序列就完事了。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n;
int a[105][105];
int main() {
	t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) for(int j=1;j<n;j++) a[i][j]=read();
		int k[2][3];
        /*
        我觉得这里需要解释一下k数组。
        k[0][0]表示第一列中第一个发现的元素。
        k[1][0]表示第一列中第一个发现的不同于k[0][0]的元素。
        显然k[0][0]和k[1][0]中就有一个是要找的p的开头元素，因为第一列只能有两个元素。
        k[0][1]表示第一列中k[0][0]出现的次数。
        k[1][1]表示第一列中k[1][0]出现的次数。
        显然如果k[0][1]>k[1][1]则k[0][0]是开头元素。
        反之亦然。
        k[0][2]表示最后发现的k[0][0]出现的位置（行数）。
        k[1][2]表示最后发现的k[1][0]出现的位置（行数）。
        这样就顺便把没有第一个元素的那个序列的编号记录了下来。
        那么找到第一个元素是0还是1，另一个记录的编号就是要找的序列。
        */
		k[0][0]=k[0][1]=k[0][2]=k[1][0]=k[1][1]=k[1][2]=0;
		for(int i=1;i<=n;i++) {
			if(k[0][0]==0||k[0][0]==a[i][1]) {
				k[0][0]=a[i][1];
				k[0][1]++;
				k[0][2]=i;
			}
			else {
				k[1][0]=a[i][1];
				k[1][1]++;
				k[1][2]=i;
			}
		}
		int x=0;
		if(k[0][1]>k[1][1]) x=1;
		printf("%d ",k[x^1][0]);
		for(int i=1;i<n;i++) printf("%d ",a[k[x][2]][i]);
		putchar('\n');
	}
	return 0;
}
```

---

