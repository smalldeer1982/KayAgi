# Repainting Street

## 题目描述

- 有一条街道，$n$ 栋房子排成一行，编号从 $1$ 到 $n$。每个房子的颜色为 $c_i$ ，工人每次可粉刷连续的 $k$ 个房子，求出将整条街刷成同一个颜色的最短的次数。

------------

## 样例 #1

### 输入

```
3
10 2
1 1 2 2 1 1 2 2 2 1
7 1
1 2 3 4 5 6 7
10 3
1 3 3 3 3 1 2 1 3 3```

### 输出

```
3
6
2```

# 题解

## 作者：Sktic (赞：1)

模拟贪心题。
## Problem
给你一条长度为 $n$ 的街道，每个房子的颜色为 $a_i$，每次可粉刷 $k$ 个房子，要求使用最短的次数将整条街刷成同一个颜色。

## Solution
这道题目的数据范围并不大，题目中说了 $\texttt{颜色}≤100$ ，所以我们可以大力枚举颜色来得到结果。

对于每一种颜色，我们采用贪心的办法，如果目前第 $i$ 个房子已经是当前第 $p$ 种颜色，那么跳过进行下一个房子，反之则无脑的将 $[i,i+k-1]$ 个房子都刷上 $p$，同时 $\texttt{num}+1$，然后判断第 $i+k$ 个房子。

证明此贪心最优：因为在刷第 $i$ 个房子时，前面的 $[1,i-1]$ 个房子全部都已经刷过或本来就是同样的颜色，从前面刷起没有意义，只会使右端点更小使答案变劣。所以此方法一定是最优解。

## Code
```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
inline int read()
{
	register char c=getchar();
	register long long x=0,f=1;
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int a[maxn],p[110];
int main()
{
	int t; 
	cin>>t;
	while(t--)
	{
		int n,k;
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			p[a[i]]++;
		}
		int mn=0x3f3f3f3f;
		if(n==0)
			mn=0;
		for(int i=1;i<=100;i++)
		{
			int s=0;
			for(int j=1;j<=n;j++)
			{
				if(a[j]!=i)
					j+=k-1,s++;
			}
			mn=min(mn,s);
		}
		printf("%d\n",mn);
	}
} 
```

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1415B) & [CF链接](http://codeforces.com/problemset/problem/1415/B)

## 思路分析：

因为 $1\le c_i\le100$，所以可以枚举要把房屋全部涂成什么颜色，一共枚举 $100$ 次。枚举时，如果当前房屋颜色正好是我们想得到的，就 $i++$，否则就证明需要修改，那直接 $i+=k$ 并且次数加一，也就是以后这 $k$ 个都不用再修改了，有一点贪心的意思。

## 代码：

```cpp
#include<iostream>
using namespace std;
int T,n,k,a[100010],ans;
int f(int x){//计算将房屋全部涂成x需要最小的操作次数
	int res=0;
	for(int i=1;i<=n;){
		if(a[i]==x){//如果符合要求
			i+=1;//就不修改
		}else{
			i+=k;//否则直接修改k个
			res+=1;//次数+1
		}
	}
	return res;
}
int main(){
	cin>>T;
	while(T--){
		ans=0x3f3f3f3f;//ans赋极大值
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=100;i++){//枚举
			ans=min(ans,f(i));//记录答案
		}
		cout<<ans<<endl;//输出
	}
	return 0;
}
```

---

## 作者：Jasonshan10 (赞：0)

[洛谷](https://www.luogu.com.cn/problem/CF1415B)

[Codeforces](https://codeforces.com/problemset/problem/1415/B)

### Part1：题意
有一条街道，$n$ 栋房子排成一行，编号从 $1$ 到 $n$。每个房子有不同的颜色，工人每次可粉刷连续的 $k$ 个房子，求出将整条街刷成同一个颜色的最短的次数。
 
### Part2：思路

考虑这道题的数据范围，可以直接暴力**枚举**。

对于 $T$ 组数据的每一组，进行下列操作：

第一步：读入。

第二步：从 $1$ 到 $100$ 枚举每一种颜色。

第三步：从 $1$ 到 $n$ 遍历数组，如果一遇到与目标颜色不符合的，将所需要的粉刷天数 $+1$，然后将 $j$ 到 $j+k-1$ 的房子都跳过。

第四步：对于每一种颜色，统计答案，将这些答案取 $\min$ 再输出便可。

### Part3：代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+1;
int a[MAXN];
int main(){
	int T; 
	scanf("%d",&T);
	while(T--){//T组样例
		int n,k,ans=1e9;//因为要去最小值，所以赋较大的值
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=100;++i){//枚举颜色
			int temp=0;
			for(int j=1;j<=n;++j){//枚举房子
				if(a[j]!=i){//如果不一样就将答案+1
					j=j+k-1;
					temp++;
				}
			}
			ans=min(ans,temp);//对于每一种颜色，取最小值
		}
		printf("%d\n",ans);//不要忘记换行
	}
	return 0;
}
```



---

## 作者：hanzhang666 (赞：0)

# 题面
有一条街道，$n$ 栋房子排成一行，编号从 $1$ 到 $n$。每个房子的颜色为 $c_{i}$，工人每次可粉刷**连续的** $k$ 个房子，求出将整条街刷成同一个颜色的最短的次数。
# 分析
题目中规定颜色数量不超过 $100$，我们可以由此为突破口，暴力枚举每种出现过的颜色。对于每个房子，如果颜色与枚举的颜色不同，就将后 $k$ 个修改为正在枚举的颜色。**我们知道修改后这 $k$ 个房子是一定符合要求的，所以此时不需要真的修改，只需跳过后 $k$ 个即可。**
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[100004];
bool flag[104];//flag[i]为0表示i这个颜色没有出现过，1表示这个颜色出现过。 
signed main(){
	int T=read();
	while(T--){
		for(int z=1;z<=100;z++){
			flag[z]=0;
		}
		int n=read(),k=read();
		for(int z=1;z<=n;z++){
			a[z]=read();
			flag[a[z]]=1;
		}
		int ans1=1e18;
		for(int w=1;w<=100;w++){
			if(!flag[w]) continue;//这个颜色没有出现过，一定不是最优解。 
			int ans=0;
			for(int z=1;z<=n;z++){
				if(a[z]!=w){
					z+=k-1;//跳过后k个 
					ans++;
				}
			}
			ans1=min(ans1,ans);
		}
		cout<<ans1<<endl;
	}
}
```


---

## 作者：_lgh_ (赞：0)

### 思路：
可以发现颜色个数 $\le 100$ ，因此可以暴力枚举每一种颜色，从头开始暴力，如果是当前枚举的颜色就跳过，不是则暴力修改后 $k$ 个，在枚举每个颜色中的多个答案中取最小值。

### AC Code:
```cpp
#include <stdio.h>
using namespace std;
int a[100005/*这里翻译也许有点问题，我一开始没有看到n<=100000，直接RE*/],Mint=1000000,T,n,k;
int main()
{
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d%d",&n,&k);//输入
    for(int i=1; i<=n; i++) scanf("%d",&a[i]);//再输入
    int Time;//定义一个保存时间的数
    for(int i=1; i<=101; i++)//枚举各个颜色
    {
      Time=0;//时间归零
      for(int j=1; j<=n; j++)
        if(a[j]!=i)//如果不是现在的颜色
          j+=k-1,++Time;//需要处理
      //else ;不需要处理直接往后跳
      if(Time<Mint) Mint=Time;//取最小时间
    }
    if(n==0) Time=0;////建议加特判，会快一点（虽然不加也能A）
    printf("%d\n",Mint);//输出
    Mint=1000000;//最小时间重新设为最大
  }
  return 0;
}

```


---

## 作者：oimaster (赞：0)

首先，我们可以枚举最后所有房子的颜色是多少，因为房子的颜色在 $[1,100]$ 之内，很小。

接下来，对于每次枚举，我们可以使用贪心的手法——每次遇到一个不为目标颜色的房子 $i$，就把房子 $i$ 到房子 $i+k-1$ 全部涂成目标颜色（如果原来就是目标颜色等于没涂色）。

为什么这样贪心是正确的？可以发现，我们每次都会在涂上这个房子的同时，将后面的房子尽可能多的涂起来。每次前面的房子都能保证全都涂完了，这次也能涂尽可能多的房子，对下一步没有副作用。局部最优解可以推出全局最优解，所以贪心成立。

时间复杂度 $\text{O}(100n)$（或者忽略 $100$ 是 $\text{O}(n)$ ）。
```cpp
#include<iostream>
#define int long long
using namespace std;
void solve(){
	int n,k;
	cin>>n>>k;
	int c[n+1];
	for(int i=1;i<=n;++i)
		cin>>c[i];
	int minv=10000000000;
	for(int maxi=1;maxi<=100;++maxi){
		int tot=0;
		for(int i=1;i<=n;++i){
			while(i<=n&&c[i]==maxi)
				++i;
			if(i>n)
				break;
			++tot;
			i+=k-1;
		}
		minv=min(minv,tot);
	}
	cout<<minv<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```

---

## 作者：Sora1336 (赞：0)

这里有一个很糟糕的而且看起来过不了题目的作法。

时间复杂度为 $O(T\times100nk)$ 。

枚举每一种可能的颜色：采用贪心的办法直接向后涂色再跳过就可以了。


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	int t;
	cin >> t;
	while(t --) {
		int n, k, ans = 1919810, curans = 0;
		int a[100005];
		cin >> n >> k;
		for(int i = 1; i <= n; i ++) cin >> a[i];
		for(int j = 1; j <= 100; j ++) {
		    curans = 0;
			for(int i = 1; i <= n; i ++) {
				if(a[i] != j) {
					curans ++;
					i += (k - 1);
				}
			} if(curans < ans) ans = curans;
		}
        cout << ans << endl;
	}
}
```

---

## 作者：比利♂海灵顿 (赞：0)

# CF1415B Repainting Street

贪心题，枚举将所有房子刷成第 $i$ 种颜色，然后贪心地刷，比较刷成的这 $100$ 种颜色的天数，取最优。

贪心策略为:

* 如果当前房子是要刷的颜色的，忽略它。
* 不是要刷的颜色，那么这一天就不分青红皂白连续往后刷 $k$ 个房子。

证明这样刷得到的天数最少:

首先，刷满 $k$ 个房子不会使答案更劣:

如果有一次刷 $k - p$ 栋房子，多刷一栋会使下一次起刷的第一栋房子往后移动或刷 $p$ 栋本就合法的房子，第二种情况不会影响结果，第一种情况可能使答案更优，所以每次都要刷满 $k$ 栋。

然后，没有必要从一栋本就合法的房子刷起，如果一种方案中，有一天从 $p$ 栋本就合法的连续的房子起刷，那么对应一种方案里，这一天从这 $p$ 栋房子后面第一栋不合法的房子起刷，就等价于这一天从原来的起点连刷 $k + p$ 栋房子，之前已经说明，多刷无害，所以从不合法的房子起刷无害。

综上，用这种策略求得每一种颜色的最优结果，汇总出最优颜色的最优结果。

最差时间复杂度 $O(100sum_n)$，没有问题。

## 代码

```cpp
int n, k, a[100005], t, ans, f;
int main() {
  t = RD();
  for (register int T(1); T <= t; ++T) {
    n = RD();
    k = RD();
    ans = 0x3f3f3f3f;
    for (register int i(1); i <= n; ++i) {
      a[i] = RD();
    }
    for (register int i(1); i <= 100; ++i) {  //枚举都刷成每个颜色
      f = 0;                                  //清空
      for (register int j(1); j <= n;) {  //挨个刷 (这里加上扇动的手势)
        if (i != a[j]) {                  //不符合颜色要求
          ++f;                            //刷一天
          j += k;                         //连刷k个
        } else {                          //无需再刷
          ++j;                            //忽略
        }
      }
      ans = min(f, ans);
    }
    printf("%d\n", ans);
  }
  return 0;
}
```

---

