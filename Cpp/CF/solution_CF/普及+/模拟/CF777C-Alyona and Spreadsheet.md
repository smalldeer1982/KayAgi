# Alyona and Spreadsheet

## 题目描述

During the lesson small girl Alyona works with one famous spreadsheet computer program and learns how to edit tables.

Now she has a table filled with integers. The table consists of $ n $ rows and $ m $ columns. By $ a_{i,j} $ we will denote the integer located at the $ i $ -th row and the $ j $ -th column. We say that the table is sorted in non-decreasing order in the column $ j $ if $ a_{i,j}<=a_{i+1,j} $ for all $ i $ from $ 1 $ to $ n-1 $ .

Teacher gave Alyona $ k $ tasks. For each of the tasks two integers $ l $ and $ r $ are given and Alyona has to answer the following question: if one keeps the rows from $ l $ to $ r $ inclusive and deletes all others, will the table be sorted in non-decreasing order in at least one column? Formally, does there exist such $ j $ that $ a_{i,j}<=a_{i+1,j} $ for all $ i $ from $ l $ to $ r-1 $ inclusive.

Alyona is too small to deal with this task and asks you to help!

## 说明/提示

In the sample, the whole table is not sorted in any column. However, rows 1–3 are sorted in column $ 1 $ , while rows 4–5 are sorted in column $ 3 $ .

## 样例 #1

### 输入

```
5 4
1 2 3 5
3 1 3 2
4 5 2 3
5 5 3 2
4 4 3 4
6
1 1
2 5
4 5
3 5
1 3
1 5
```

### 输出

```
Yes
No
Yes
Yes
Yes
No
```

# 题解

## 作者：210101zhaosicheng (赞：3)

# 题解：CF777C Alyona and Spreadsheet
思维好题。
## 前言和闲话
~~说句闲话，今年是《说句闲话》的六周年。~~

当时本人使用了多种做法尝试过这一道题，导致心态比较爆炸。
## 题意
~~题目表述已够明确，此处不再赘述~~。

此处只标记处重点：问如果只保留矩阵的第 $L\to R$**行**，矩阵中是否存在不下降的**一列**。

当时本人因为读题错误导致了心态崩溃。
## 思路（包含读题错误的部分）
首先拿到题目，读完题（理解成了矩阵中是否存在不下降的一行），显然有一种思路：

设输入的数组某一行为 $a$。

定义一个数组 $t$，使得 $t_i=a_i-a_{i-1}$。再对于每一个区间 $[l,r]$ 查询每一行对于 $i\in [i+1,r]$ 是否有 $t_i\geq 0$，如果答案是否定的，那么说明不可以组成不下降的序列。反之，则可以。

当时想到了线段树区间最小值的做法，复杂度为 $O(q\times n\log m)$，也是成功的 $TLE$ 在了第三个测试点。

想办法优化：

线段树的复杂度是 $O(n\log n)$ 建树，$O(\log n)$ 查询。

但是并不需要更改，自然想到 ST 表。

ST 表复杂度 $O(n\log n)$ 建表，$O(1)$ 查询。

但是 $WA$ 在了第三个测试点，时间也来到了惊人的 $900ms$。重新读题，发现题读错了，这个做法的时间复杂度也并不可靠，可以被卡成 $O(q\times n)$，此时 $n=10^5$。妥妥的挂掉了。

果断换做法，想到可以 $O(n\times m)$ 预处理，$O(1)$ 查询答案。
## 正解
计算每一行的最长上升子序列，并且取最大值存储在答案数组中，可以看代码感性理解。

我的写法是：输入以后用 $(i-1)*m+j$ 来映射到原来的 $a[i][j]$。

每一次输出的时候看答案数组以 $r$ 结尾的部分是否大于 $r-l+1$ 即可。
## 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int a[N],n,m;
int dp[N];
int s[N],tot;
int ans[N];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);
	cin>>n>>m;
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			tot++;
			cin>>s[tot];
//			cin>>a[j];
		}
	}
	dp[1]=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<n;j++)
		{
//			cout<<s[(j)*m+1]<<' '<<s[(j-1)*m+i]<<'\n';
			if(s[(j)*m+i]>=s[(j-1)*m+i])
			{
				dp[j+1]=min(dp[j+1],dp[j]+1);
			}
			else
			{
				dp[j+1]=1;
			}
			ans[j]=max(ans[j],dp[j]);
		}
		ans[n]=max(ans[n],dp[n]);
		for(int j=2;j<=n;j++)
		{
			dp[j]=0x3f3f3f3f;
		}
	}
	int q;
	cin>>q;
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		if(ans[r]>=r-l+1)
		{
			cout<<"Yes\n";
		}
		else
		{
			cout<<"No\n";
		}
	}
	return 0;
}
```

感谢你能看到这里，如果有讲的不清楚的部分，欢迎讨论。

---

## 作者：thh_loser (赞：3)

# CF777C Alyona and Spreadsheet 题解

[题目链接](https://www.luogu.com.cn/problem/CF777C)



## 题意

给定 $n\times m$ 的矩阵，进行 $q$ 次询问，每次询问给出 $l,r$，问对于矩阵的 $l$ 到 $r$ 行，矩阵是否存在某一列不下降。



## 思路

我们很容易发现如果一段序列 $\left[l,r\right]$，如果它是单调不下降的，则 $\forall i \in\left[l,r-1\right]$，序列 $\left[i,r\right]$ 都是单调不下降的。

同时我们发现题目只要求存在一列不下降即可，因此我们可以对数组进行预处理，如下。

我们依次对于每一行进行处理，对于每一个数，维护该列以它结尾的不下降序列最长是在哪一处开始，最后每一列取最小值即可。

得到该数组后，我们对于询问 $\left[l,r\right]$，判断记录的第 $r$ 行的答案是否小于等于 $l$，如果是，则存在某一行的不下降序列包括 $\left[l,r \right]$，即存在一列满足答案。

预处理 $O(n\cdot m)$，询问可以做到 $O(1)$，最终复杂度 $O\left(n\cdot m + q\right)$。



## code

```c++
#include<bits/stdc++.h>
#define N 100010
//#define int long long
using namespace std;
int t(1),n,m,k;
int a[N];
int out[N];//记录答案 
int ans[N];//第i行的答案
int las[N];//上一行的数（其实不需要） 
int gid(int x,int y){
	return (x-1)*m+y;
}
signed main(){
	//cin>>t;
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i){
			for(int j=1,x;j<=m;++j){
				scanf("%d",&x);
				a[gid(i,j)]=x;//储存也可以用vector 
			}
		}
		for(int i=1;i<=n;++i){
			int re=i;
			for(int j=1;j<=m;++j){
				int now=gid(i,j);
				if(a[now]<las[j]){//如果不能构成不下降序列 
					ans[j]=i;//以当前开始 
				}
				las[j]=a[now];
				re=min(re,ans[j]);//该行取min 
			}
			out[i]=re;
		}
		scanf("%d",&k);
		for(int i=1,x,y;i<=k;++i){
			scanf("%d%d",&x,&y);
			if(out[y]<=x)cout<<"Yes\n";
			else cout<<"No\n";
		}
	}
	return 0;
}

```

---

## 作者：Comentropy (赞：3)

# CF777C 题解

可以看出，本题可以用各种 STL 容器做，但蒟蒻的我选择了数组。。。

### 本题的数据可以用三个数组来存储，不需要二维数组。其中具体分析如下：
1.从上到下非递减，即上面的数不大于下面的数。
为了适应第2点的说法，可以转换为“非递增”。

2.用二维数组大概率会爆掉，所以用一维数组  _**$a$**_  来存储**每一行的数**
，从后往前推，用一维数组  **_$b$_**  来存储每一列的数能到达的最前面的一行，在用  _**$c$**_  来存储每一行的数能到达的最前面的一行

3.最后只需要**比较 $ c[i] $ 与 $ l $ 的大小**即可。

值得注意的是，可以通过把二维数组的“ _超大空间_ ”和“ _超大时间复杂度_ ”转换成一位数组，来 A 这道题（**千万不要忘记初始化**）。其实大致的思路类似于前缀和等的预处理，以减小时间复杂度

不知道还有没有其它 $ nm $ 的算法可以过，希望各位大佬指出，并指正本人的算法。
以下是我的代码：
```cpp
//注释中的"到达"，都是指:最长的非递增的位置 
#include<iostream>
using namespace std;
const int N=1e5+5; 
int a[N],b[N],c[N]; //a存数据,用一维做不会爆
//b存每一列数到的最远的一行 
//c存每一行数到的最远的一行,即max 
int main(){
    int n,m,x;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)//能到的最远的一行是第一行。
        b[i]=1;
    for(int i=1;i<=n;i++){
        c[i]=i;    //每个数都能到达所在的行(init)。
        for(int j=1;j<=m;j++){
            scanf("%d",&x);
            if(x<a[j])//如果x上面的数比x大，则不是非递增的，所以x不能到达上一行。
                b[j]=i;
                
            a[j]=x; //save
            if(b[j]<c[i])
            	c[i]=b[j]; //找每一列能到达的最前面的行。
        }
    }
    int k,l,r;
    scanf("%d",&k);
    while(k--){
        scanf("%d%d",&l,&r);
        if(c[r]<=l)	printf("Yes\n");
        else	printf("No\n");
    }
    return 0;
}
```


---

## 作者：Aiopr_2378 (赞：1)

### 题目理解

我们要求出 $L$ 至 $R$ 行中的不下降序列。那我们只需要记录每个数在每一列中上一个能与其构成逆序对的数的位置，通俗点说，就是记录上一个比这个数大的数的位置，然后获得这一行最大延伸长度（定义最大延伸长度为：能构成的最长不下降序列长度），复杂度为 $O(mn)$。对于每组询问，我们只需要判断 $R$ 这行的延伸长度是否能达到 $L$ 这一行，即可进行 $O(1)$ 查询。

最大复杂度为 $O(mn)$，在 $10^5$ 内合法。

还要注意一下，不能开二维数组，会爆。

### 程序设计

- 设计数组 `reach[]`，记录上一个比这个数大的数；

- 设计数组 `lastreach[]`，记录上一行的数的 `reach[]`；

- 设计数组 `last[]`，记录上一行的数；

- 设计数组 `linereach[]`，记录该行最大延伸长度能到达的点；

- 不要忘记用 `memset` 初始化 `lastreach[]` 和 `last[]`；

### 参考代码

`CODE TIME`

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 100005
int n,m,k,lastreach[MAXN],reach[MAXN],linereach[MAXN],last[MAXN];
int main(){
    cin>>n>>m;
    memset(linereach,0x3f,sizeof(linereach));//初始化
    memset(last,0x3f,sizeof(last));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int x;
            cin>>x;
            if(x<last[j]){//如果比上一行的数小，不能与上面一行的数构成不下降序列
                reach[j]=i;
            }
            else{//否则，可以与上一行的数构成不下降序列，延续上一行的信息
                reach[j]=lastreach[j];
            }
            lastreach[j]=reach[j];//传递信息
            last[j]=x;
            linereach[i]=min(linereach[i],reach[j]);//记录linereach，即能到达的最小的行
        }
    }
    cin>>k;
    while(k--){
        int l,r;
        cin>>l>>r;
        cout<<(linereach[r]<=l?"Yes":"No")<<endl;
    }
    return 0;
}
```

### END

---

## 作者：nonanalyzer (赞：1)

要多次询问某区间是否单调不降，为了不让时间复杂度爆炸，就想到预处理。

1. 首先要能快速判断某一列的区间$ [L,R] $是不是不下降序列。
     - 设$ b_{i,j} $表示第j列中，以第i行元素$ a_{i,j} $为结尾，最长的不下降序列开头的位置（“最长”是贪心想法，因为不下降序列的子序列必定也是不下降序列），那么第j列的区间$ [L,R] $不下降的充要条件为$ b_{i,j} \leq L $。

   - 构造b数组也很简单，如果$ a_{i,j} $相对于$ a_{i-1,j} $不下降（$ a_{i,j} \geq a_{i-1,j} $），那么$ a_{i,j} $就可以加入到原本以$ a_{i-1,j} $为结尾的不下降序列中而成为新的结尾，此时$ b_{i,j}=b_{i-1,j} $；反之，如果$ a_{i,j}<a_{i-1,j} $，那么这个元素只能自成一个新序列，$ b_{i,j}=i $。

2. 然后要能快速判断所有列中是否有区间$ [L,R] $是不下降序列的一列。
	- 根据前面得出的结论“区间$ [L,R] $不下降的充要条件为$ b_{R,j} \leq L $”可知，如果至少有一列是不下降的，那么$ min \{ b_{R,j}|j \in [1,m] \} \leq L $。这个每一行的最小值，暴力算出来再拿个数组存一下就可以O(1)判断了。
	- 拓展：如果j的范围不是$ [1,m] $，把数组换成线段树就OK了。

最后一个小问题：题面中只给了$ n \times m $的范围$ 1 \leq n \times m \leq 100000 $，要是直接开1e5\*1e5的二维数组，空间不知道炸到哪里去。这儿有几个解决方法：
- C++，把普通二维数组`int a[maxn][maxm]`用vector一位数组`vector<int>a[maxn]`代替。STL真是好东西。~~但vector看不起蒟蒻我，我这样写会莫名RE。大佬叫我手写vector，可我太菜不会。~~
- Python的list，可以用变量来指定大小。~~但Python实在是慢，会TLE。~~
- ~~应该是任何语言都适用的：~~数组只开1e5个元素，原来的`a[i][j]`用`a[(i-1)*m+j]`表示（前i-1行每行有m个元素，第i行的第j个元素）。我因为要用到第0行，所以i没减1，如果有人也要这样写，记得数组大小开**2e5**！

时间复杂度：$ O(nm) $

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
const int maxn=2e5+5,maxm=maxn,INF=0x7fffffff;
int n,m,Q,tmp,a[maxn],b[maxn],c[maxn];
#define a(i,j) a[(i)*m+(j)]
#define b(i,j) b[(i)*m+(j)]
/*
这样写我觉得会方便一点。
其原理是把所有a(i,j)替换成a[(i)*m+(j)]，其中i和j会被换成我们自己给的参数。
具体可以看主程序里用到的地方。b同理。
*/
inline int read(int &Res=tmp){
	Res=0;bool fh=0;char ch=getchar();
	while(!isdigit(ch)) fh^=!(ch^45),ch=getchar();
	while(isdigit(ch)) Res=(Res<<3)+(Res<<1)+(ch&15),ch=getchar();
	return fh?Res=-Res:Res;
}
int main(){
	memset(a,63,sizeof(a)),memset(c,63,sizeof(c));
	read(n),read(m);
	for(int i=1;i<=n;++i)
	  for(int j=1;j<=m;++j) a(i,j)=read();
	
	for(int j=1;j<=m;++j)
	  for(int i=1;i<=n;++i)
	    if(a(i,j)>=a(i-1,j)) b(i,j)=b(i-1,j);else b(i,j)=i;
	for(int i=1;i<=n;++i)
	  for(int j=1;j<=m;++j) c[i]=std::min(c[i],b(i,j));
	
	read(Q);
	while(Q--){
		int L=read(),R=read();
		printf(c[R]<=L?"Yes\n":"No\n");
	}
	return 0;
}
```


---

