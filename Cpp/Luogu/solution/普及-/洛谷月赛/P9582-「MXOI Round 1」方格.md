# 「MXOI Round 1」方格

## 题目描述

小 C 和方格是好朋友。

小 C 有一个 $n$ 行 $m$ 列的方格图，每个方格中都有一个数字，其中第 $i$ 行第 $j$ 列的方格中的数字为 $a_{i,j}$。

我们定义，在这个方格图中，两个不同的方格不相邻，当且仅当这两个方格**没有公共边**。

小 C 认为，两个不同的方格互为好朋友，当且仅当这两个方格**不相邻**且**这两个方格中的数字相同**。

小 C 想让你帮忙求出，所有方格的好朋友的数量之和是多少。

## 说明/提示

#### 【样例解释 #1】

第 $1$ 行第 $1$ 列的方格共有 $3$ 个好朋友，第 $1$ 行第 $2$ 列的方格共有 $2$ 个好朋友，第 $1$ 行第 $3$ 列的方格共有 $1$ 个好朋友，第 $1$ 行第 $4$ 列的方格共有 $0$ 个好朋友；

第 $2$ 行第 $1$ 列的方格共有 $1$ 个好朋友，第 $2$ 行第 $2$ 列的方格共有 $2$ 个好朋友，第 $2$ 行第 $3$ 列的方格共有 $1$ 个好朋友，第 $2$ 行第 $4$ 列的方格共有 $1$ 个好朋友；

第 $3$ 行第 $1$ 列的方格共有 $1$ 个好朋友，第 $3$ 行第 $2$ 列的方格共有 $3$ 个好朋友，第 $3$ 行第 $3$ 列的方格共有 $1$ 个好朋友，第 $3$ 行第 $4$ 列的方格共有 $4$ 个好朋友；

所有方格的好朋友数量之和为 $20$。

#### 【样例 #2】

见附加文件中的 `square/square2.in` 与 `square/square2.ans`。

该样例满足测试点 $1$ 的限制。

#### 【样例 #3】

见附加文件中的 `square/square3.in` 与 `square/square3.ans`。

该样例满足测试点 $4$ 的限制。

#### 【样例 #4】

见附加文件中的 `square/square4.in` 与 `square/square4.ans`。

该样例满足测试点 $6$ 的限制。

#### 【样例 #5】

见附加文件中的 `square/square5.in` 与 `square/square5.ans`。

该样例满足测试点 $10$ 的限制。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le n,m \le 2000$，$1 \le a_{i,j} \le 9$。

|测试点编号|$n,m \le$|$a_{i,j} \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim3$|$80$|$9$|否|
|$4\sim5$|$2000$|$1$|否|
|$6\sim7$|$2000$|$9$|是|
|$8\sim10$|$2000$|$9$|否|

特殊性质：保证任意两个相邻的方格中的数不相等。

## 样例 #1

### 输入

```
3 4
1 1 4 5
2 1 2 3
3 1 4 1```

### 输出

```
20```

# 题解

## 作者：Coffee_zzz (赞：8)

### Task 1~3

四重循环暴力枚举每一对方格即可。

### Task 4~5

保证了 $a_i \le 1$，也就是每一个方格内的数都相等。

我们考虑每一个位置的方格。

对于在角落的方格，共有 $nm-3$ 个好朋友；

对于在边上的方格，共有 $nm-4$ 个好朋友；

对于在中间的方格，共有 $nm-5$ 个好朋友；

考虑每个位置的方格的数量，与该位置的方格的好朋友的数量相乘再相加即可。

时刻铭记不开 `long long` 见祖宗。

### Task 6~7

由于特殊性质保证了任意两个相邻的方格中的数不相等，所以判定两个方格是否为好朋友的条件等价于这两个方格中的数字是否相同。

那我们开一个桶 $c$，记录每一个数字出现的次数，根据乘法原理，对于所有中间的数字为 $i$ 的方格，好朋友的数量的总和就是 $c_i \times (c_i-1)$。

所以答案就是 $\sum\limits^9_{i=1} c_i \times (c_i-1)$。

### Task 8~10

现在相邻的方格中的数可能相等，那我们可以用刚才求出的答案 $\sum\limits^9_{i=1} c_i \times (c_i-1)$ 减去不合法的情况。

而不合法的情况其实就是两个相邻的方格中的数相等。

那么对于每一个方格，我们统计与其相邻且中间的数字相同的方格的数量，将答案减去这个值即可。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2005,A=15;
int n,m,a[N][N],c[A];
ll ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			c[a[i][j]]++;
		}
	}
	for(int i=1;i<=9;i++) ans=ans+1ll*c[i]*(c[i]-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==a[i-1][j]) ans--;
			if(a[i][j]==a[i][j-1]) ans--;
			if(a[i][j]==a[i+1][j]) ans--;
			if(a[i][j]==a[i][j+1]) ans--;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：zzx114514 (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/P9582)
# 题目大意
给定 $n \times m$ 的数组 $a$，定义 $f(i,j)$ 为所有与 $a_{i,j}$ 没有共同边（即相邻）且相同的元素个数，求 $\sum^n_{i=1}\sum^m_{j=1}f(i,j)$，其中数组下标从 $1$ 开始。
# 解题思路
观察到此题 $1 \le a_{i,j} \le 9$，数据范围很小，可以开 $9$ 个桶 $t$ 存储每个元素出现的次数，再依次枚举每个元素，每次先将 $ans$ 加上 $t_{a_{i,j}} - 1$（因为自身不计算在其中），如果有相邻且相同的元素则将 $ans - 1$，最后输出 $ans$ 即可，时间复杂度 $O(nm)$，可以通过，记得开 `long long`。
# 完整代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,a[2005][2005],t[10],ans; 
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			t[a[i][j]]++;//统计数字出现个数 
		}
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
		{
			ans+=t[a[i][j]]-1;//开始假设所有相同元素均不相邻 
			if (i>1 && a[i-1][j]==a[i][j]) ans--;
			if (i<n && a[i+1][j]==a[i][j]) ans--;
			if (j>1 && a[i][j-1]==a[i][j]) ans--;
			if (j<m && a[i][j+1]==a[i][j]) ans--;
			//如果相邻且相同则将ans-1 
		}
	cout<<ans;
	return 0;//华丽的结尾 
}


```


---

## 作者：Pink_Cut_Tree (赞：2)

# P9582 方格 题解

这算是本次比赛最让我后悔的题目了。

### 思路

桶排。这很好想到，因为数据范围 $1\leq a_{i,j} \leq 9$ 明显是让我们桶排的。

### 解析

其实思路也很简单，开一个桶存储每一个数字出现了多少次，$O(nm)$ 扫一遍方阵，每次判断有多少个数与之相同，再对其周边 $4$ 个格子进行判断是否有与之相同的，若有，则答案减 $1$，最后输出答案即可。

### 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
const int N=2e3+5;
int n,m;
long long ans; //十年 OI 一场空，不开 long long 见祖宗，不开 long long 实测 $30$ 分。 
int num[N][N],dx[4]={0,-1,0,1},dy[4]={1,0,-1,0}; //dx,dy 是偏移量数组 
bool flag;
#define ri register int
int bucket[15]; //桶 
int main(){
	cin>>n>>m;
	for(ri i=1;i<=n;i++){
		for(ri j=1;j<=m;j++){
			cin>>num[i][j];
			bucket[num[i][j]]++; //加入桶 
		}
	}
	for(ri i=1;i<=n;i++){
		for(ri j=1;j<=m;j++){
			ans+=bucket[num[i][j]];
			for(ri k=0;k<4;k++){
				if(num[i+dx[k]][j+dy[k]]==num[i][j]){ //与之相邻的有数字相同的 
					ans--;
				}
			}
			ans--; //因为算的时候包括了自己，需要把自己减掉 
		}
	}
	cout<<ans;
return 0;
}
```


---

## 作者：Cloud_Umbrella (赞：1)

## 题意简述

定义“相邻”的含义为两个方格没有公共边，定义“好朋友”为两个不“相邻”的方格中的元素相同。问“好朋友”的数量。

## 分析

也不知怎么，我突然想到一种比较新颖的思路。敲黑板了！！！

首先，因为方格中只有 $1$ 到 $9$ 之间的正整数，所以可以用一个数组 $cnt$ 记录每个数字出现的次数。我们考虑最优情况，答案其实就是 $n(n-1)$。其中 $n$ 表示某个数字出现的个数，因为每个数字都有 $n-1$ 个“好朋友”，有点类似于双循环。所以最优情况就是 $cnt[i]=cnt[i] \times (cnt[i]-1)$。但是，有重复的情况，其实就是一个数的上下左右，只有这四个数会与它有公共边（如果超过边界不用考虑，因为默认是零）。只要每次遇到这样重复的，$cnt[i]$ 就减一。最后，时间也是非常的优秀。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long见祖宗
const int N=2010;//静态定义
int n,m,a[N][N],cnt[10];
int read(){//快读
	char c=getchar();
	int x=0,s=1;
	while(c<'0' || c>'9'){
		if(c=='-') s=-1;
		c=getchar();
	}
	while(c>='0' && c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*s;
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
			cnt[a[i][j]]++;//记录次数
		}
	}
	for(int i=1;i<=9;i++) cnt[i]=cnt[i]*(cnt[i]-1);//不管cnt[i]是0还是1，都不用考虑
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){//判断上下左右
			if(a[i][j]==a[i-1][j]) cnt[a[i][j]]--;
			if(a[i][j]==a[i+1][j]) cnt[a[i][j]]--;
			if(a[i][j]==a[i][j-1]) cnt[a[i][j]]--;
			if(a[i][j]==a[i][j+1]) cnt[a[i][j]]--;
		}
	}
	int ans=0;
	for(int i=1;i<=9;i++) ans+=cnt[i];//用ans记录cnt数组中所有元素的“好朋友”
	cout<<ans;
	return 0;//好习惯伴终生
}
```

---

## 作者：_JF_ (赞：1)

签到题

因为值域很小，考虑对值域动手。

对于每一种数字，存储他出现的次数，那么根据排列组合，假设当前的数有 $x$ 个，根据排列组合，我们就知道最多可以可以组合出来 $x\times (x-1)$ 种。

然后我们再遍历一次这个矩阵，所谓公共边其实就是上下左右四个点。按照题意排除掉不满足的就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =5001;
#define int long long 
int a[N][N],t[N],ans;
signed main()
{
//	freopen("square5.in","r",stdin);
//	freopen("ans.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)	
			scanf("%lld",&a[i][j]),t[a[i][j]]++;
	for(int i=1;i<=9;i++)
		ans+=t[i]*(t[i]-1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(a[i][j]==a[i-1][j])	ans--;
			if(a[i][j]==a[i][j-1])	ans--;
			if(a[i][j]==a[i+1][j])	ans--;
			if(a[i][j]==a[i][j+1])	ans--;
		}
	cout<<ans<<endl;
	return 0;
}
/*
start: 2023.8.26 18:45

总的减去分的，没了。
按着值域做。
 
end: 2023.8.26 18:56 
*/
```


---

## 作者：Hog_Dawa_IOI (赞：0)

### 题意简述
小 C 有一个 $n$ 行 $m$ 列的方格图，每个方格中都有一个数字，其中第 $i$ 行第 $j$ 列的方格中的数字为 $s_{i,j}$。  
我们定义，在这个方格图中，两个不同的方格不相邻，当且仅当这两个方格**没有公共边**。也就是说，一个方格和它上、下、左、右的方格相邻，对角线的方格是不相邻的。    
小 C 认为，两个不同的方格互为好朋友，当且仅当这两个方格**不相邻**且这两个方格中的**数字相同**。        
小 C 想让你帮忙求出，所有方格的好朋友的数量之和是多少。     
数据范围：$1 \le n,m \le 2000,s_{i,j} \le 9$。    
### 做法分析 
首先大家应该都会想要对于每一个方格求出它的好朋友数量。      
但是枚举每一个方格，再去统计它的好朋友数量是会超时的。     
这时候我们可以考虑先求出所有的和它数字相同的方格数量，再减去这其中不是它的好朋友的数量，即和它相邻且数字相同的格子数量。       
求所有的和它数字相同的方格数量，只需要一个桶。由于 $s_{i,j} \le 9$，所以这个大小为 $10$ 的桶非常轻松就开下了。   
再求和它相邻且数字相同的格子数量，由于和它相邻的格子数量只有 $4$ 个，所以暴力判断就可以了。    
**最后由于和它数字相同的方格数量中包括它自己，所以还要减 $1$。**   
### 参考代码
```cpp
#include<stdio.h>
long long n,m,s[2005][2005],num[15],ans;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    scanf("%lld",&s[i][j]),num[s[i][j]]++;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
    ans+=num[s[i][j]]-(s[i-1][j]==s[i][j])-(s[i+1][j]==s[i][j])-(s[i][j-1]==s[i][j])-(s[i][j+1]==s[i][j]);
    printf("%lld",ans-n*m);
}
```

---

## 作者：liangjindong0504 (赞：0)

~~大号打了排名老低，不用大号打排名老高~~

**【主要思路】**

最先想到：暴力枚举，时间复杂度 $O(n^4)$，肯定 TLE。

既然常规思路不行，那我们就来看看输入的东西里面有什么突破口。

简单看一遍后，有一个地方显得十分显眼：$1 \le a_{i,j} \le 9$。于是便有了大体思路：统计每个数字忽略合法有几次、若要合法去掉几次，将每个数字合法个数相加输出即可。

1. 忽略合法出现几次：假设有 $m$ 个相同数字，忽略合法之后就是任取 $2$ 个，即为 $A_{m}^{2}$，也就是 $m(m-1)$。
2. 若要合法去掉几次：仅需遍历每个点即可。

**【实现】**

对于第一种，先把每个数字出现次数统计出来，再进行计算。
```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		a[i][j]=read();
		t[a[i][j]]++;
	}
}
for(int i=1;i<=9;i++){
	t[i]*=(t[i]-1);
}

```
第二种，遍历每一个点，判断四周有几个相同点，相加即可。
```cpp
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		z[a[i][j]]+=(a[i][j]==a[i+1][j]);
		z[a[i][j]]+=(a[i][j]==a[i-1][j]);
		z[a[i][j]]+=(a[i][j]==a[i][j+1]);
		z[a[i][j]]+=(a[i][j]==a[i][j-1]);
	}
}
```
最后统计答案，只需遍历 $1 \sim 10$，将 $t_i-z_i$ 的值相加即可。

**【总结】**

普及组 T2 相比于 T1 来说对思维量要求更高，个人认为评橙。

还有不懂的可以私信本人。

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9582)

本题的主要意思就是求满足“任意两个方格不相邻且这两个方格中的数字相同”条件的有几个。

注意到要求方格之间不能相邻，即这两个方格没有公共边，那么满足相邻的只有自身格子的**上下左右四个方格**。于是我们便在计算的时候**不考虑**自身格子的上下左右这四个格子即可。

但如果我们每次看到一个数字再去 $\mathcal{O}(nm)$ 进行暴力统计肯定会超时。于是我们可以在输入时就将每个数存入桶里，代表有几个这样的数。因为注意到 $1\le a_{i,j}\le9$，所以说桶是可以存下的。

然后每次遍历时减去自身所在格子所占的 $1$，上下左右这四个格子里如果也有是自身格子的那个数，再减即可。统计完后累加变量，最后输出累加变量即可完成本题。

同样还需特别注意的是，由于 $2000\times2000$ 可以到达 $4\times10^6$，再加上每次的格子数，会爆 `int`，所以本题要开 `long long`。不开 `long long` 只有 $30$ 分。~~还好有大样例，不然我也中招了。~~

于是得代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
int a[2010][2010];
int b[20];
inline bool chk(int n,int m,int s,int l)
{
	return a[n][m]==a[s][l];
}
signed main()
{
	int n,m;
	rd(n,m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			rd(a[i][j]);
			b[a[i][j]]++;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			ans+=b[a[i][j]]-1-(chk(i,j-1,i,j)+chk(i-1,j,i,j)+chk(i+1,j,i,j)+chk(i,j+1,i,j));
		}
	}
	wtl(ans);
	return 0;
}
```

---

## 作者：Xdwjs (赞：0)

我们可以预先处理出每一个数字的出现个数，再枚举每一个方格，将这个数字的出现次数减去**自己及相邻方格中**这个数的出现次数，累加这个结果，即可通过此题。

需要开 ```long long```。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,long long> mp;
int a[2005][2005]={0};
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
            mp[a[i][j]]++;
        }
    }
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            long long th=1;//加上自己的一份
            if(a[i-1][j]==a[i][j]) th++;
            if(a[i+1][j]==a[i][j]) th++;
            if(a[i][j-1]==a[i][j]) th++;
            if(a[i][j+1]==a[i][j]) th++;
            ans+=mp[a[i][j]]-th;
        }
    }
    cout<<ans;
    //system("pause");
    return 0;
}
```


---

