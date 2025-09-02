# [ARC023B] 謎の人物X

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc023/tasks/arc023_2

高橋君は謎の人物Xに連れ去られてしまい、謎の施設に閉じ込められてしまいました。この施設の床には $ R $ 行 $ C $ 列 のマス目が書かれていて、それぞれのマスには $ 1 $ つずつ数字が書かれています。高橋君はこのマス目の $ 1 $ 行目の $ 1 $ 列目のマスにいます。

長い時間閉じ込められていたので、高橋君はお腹が減ってきました。謎の人物Xによると、「隣のマスに移動する」ということをちょうど $ D $ 回行った後に高橋君がいるマスに書いてある数字と同じ値段のたこ焼きを用意してくれるそうです。あるマスの「隣のマス」とは、そのマスと辺を共有するマスのことを指します。高橋君は出来るだけ値段の高いたこ焼きが食べたいと思ったので、最大でいくらのたこ焼きを食べることが出来るかを考えることにしました。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ R\ ≦\ 100 $ かつ $ C\ ≦\ 100 $ かつ $ D\ ≦\ 200 $ を満たすテストケースすべてに正解した場合は $ 60 $ 点が与えられる。

### Sample Explanation 1

ちょうど $ 1 $ 回移動することで行くことが出来るマスは、$ 1 $ 行目の $ 2 $ 列目のマスか $ 2 $ 行目の $ 1 $ 列目のマスだけです。このケースでは、高橋君は最大で $ 5 $ 円のたこ焼きを食べることが出来ます。

### Sample Explanation 2

このケースでは、高橋君はどのように移動しても $ 999 $ 円のたこ焼きを食べることが出来ます。

### Sample Explanation 3

このケースでは、高橋君はどのように移動しても $ 198 $ 円のたこ焼きしか食べることが出来ません。

## 样例 #1

### 输入

```
3 2 1
9 5
3 1
8 9```

### 输出

```
5```

## 样例 #2

### 输入

```
4 4 100
999 999 999 999
999 999 999 999
999 999 999 999
999 999 999 999```

### 输出

```
999```

## 样例 #3

### 输入

```
3 4 5
700 198 700 198
198 700 198 700
700 198 700 198```

### 输出

```
198```

# 题解

## 作者：_zby_ (赞：1)

## 做法 ：找规律！！！
#### ~~（不知道暴搜能不能过）~~
让我们先看看样例三

3 4 5

700 198 700 198

198 700 198 700

700 198 700 198

试着走一走，你会发现所有的198都能走到

让我们把这个矩阵扩大一下(同样只走五步）

#### 700 ~~198~~ 700 ~~198~~ 700 ~~198~~ 700 198

#### ~~198~~ 700 ~~198~~ 700 ~~198~~ 700 198 700

#### 700 ~~198~~ 700 ~~198~~ 700 198 700 198

#### ~~198~~ 700 ~~198~~ 700 198 700 198 700

#### 700 ~~198~~ 700 198 700 198 700 198

#### ~~198~~ 700 198 700 198 700 198 700

#### 700 198 700 198 700 198 700 198  （图一）

于是会只有划掉的198能走到

再比较划掉的198与不划掉的198的坐标和就会发现

#### x+y<=7

好了，现在我们把步数调为4步，再来看看

#### ~~700~~ 198 ~~700~~ 198 ~~700~~ 198 700 198

#### 198 ~~700~~ 198 ~~700~~ 198 700 198 700

#### ~~700~~ 198 ~~700~~ 198 700 198 700 198

#### 198 ~~700~~ 198 700 198 700 198 700

#### ~~700~~ 198 700 198 700 198 700 198

#### 198 700 198 700 198 700 198 700

#### 700 198 700 198 700 198 700 198  （图二）

此时发现
#### x+y<=6
你可以试着再多试一次，就会发现
## x+y<=sum+2
同时再比较一下图一和图二中划掉的数坐标和的奇偶性，还可以发现
## (x+y)%2==1(sum为奇数）
## (x+y)%2==0(sum为偶数）
于是就有了下面的做法（用时351ms）
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<queue>
#include<set>
#include<map>
#include<iomanip>
#include<stack>
#include<sstream>
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rep(i,a,b) for(int i=(a);i>=(b);i--)
/*#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
*///必要时卡时间用
typedef long long LL;
typedef double db;
using namespace std;
template<typename T>void read(T &x) {
    char ch=getchar(); x=0; T f=1;
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    for(;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0'; x*=f;
}
int a[1001][1001];
int main(){
	long long sum,n,m,jo=0,max1=0;
	read(n);read(m);read(sum);
	if(sum%2==0)//奇偶标记
	jo=0;
	else
	jo=1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	{
		read(a[i][j]);
		if((i+j)%2==jo&&i+j<=sum+2&&a[i][j]>max1)//求最大值
		max1=a[i][j];
	}
	cout<<max1<<endl;//别忘了endl，我就被坑过
	return 0;
}
```
#### 这才是一道灰（shui）题应该有的难度嘛

---

## 作者：olegekei (赞：0)

## 思路
容易发现，当前格子 $A_{i,j}$ 只有 $i+j-2 \le d$，即在距离起点 $d$ 的范围内才能取到。

同时考虑步数的奇偶性限制，对于每个格子 $A_{i,j}$，能否走到这个格子取决于给定 $d$ 的奇偶性。当 $d$ 与 $i+j$ 同奇同偶时便可到达 $A_{i,j}$。

最后输出满足以上条件的 $A_{i,j}$ 的最大值即可。

## 代码
```cpp
#include<iostream>
using namespace std;
int n,m,d;
int maxn=0;
int main(){
cin>>n>>m>>d;
int f=d&1;//f用来记录d的奇偶
for(int i=1,x;i<=n;i++){
	for(int j=1;j<=m;j++){
		cin>>x;
		if(((i+j&1)==f)&&(i+j-2<=d))maxn=max(maxn,x);
		//与d同奇同偶且在d范围内，更新最大值即可
	}
}
cout<<maxn<<'\n';
return 0;
}
```
AT 上古题，不加换行算错。

---

## 作者：achjuncool (赞：0)

[题面](https://www.luogu.com.cn/problem/AT879)

[博客](https://www.luogu.com.cn/blog/achjuncool/solution-at879)

## 题目大意

一个长、宽分别为 $R,C$ 的点阵，每一个点上都有一个数，从 $(1,1)$ 出发，一步可以在点阵内（包括边缘）向上下左右任意一个方向移一个点，问走 $D$ 步以后所在点的数的最大值是多少。

## 做法

首先预处理，定义一个布尔二维数组 $f$，$f_{i,j}$ 表示走 $D$ 步后有没有可能在 $(i,j)$ 上。

那么该如何处理这个数组呢？

通过尝试 $D$ 为某个值时哪些点可以走到，我们会得出：

- 当 $D=2$ 时，可以走到的点如下（$1$ 表示可以走到，$0$ 表示不能走到）：
  
  $101$
  
  $010$
  
  $100$

- 当 $D=3$ 时，可以走到的点如下：
  
  $0101$
  
  $1010$
  
  $0100$
  
  $1000$

- $\dots$

通过观察以上数据，我们会发现：

- 当 $D$ 为奇数时，可以走到的点的特点是：
  
  - 在以 $(1,1),(1,D),(D,1)$ 三个点组成的三角形中（包括边缘）。
  
  - $x$ 坐标与 $y$ 坐标奇偶性不同。

- 当 $D$ 为偶数时，可以走到的点的特点是：
  
  - 在以 $(1,1),(1,D),(D,1)$ 三个点组成的三角形中（包括边缘）。
  
  - $x$ 坐标与 $y$ 坐标奇偶性相同。

因此，我们只需要将满足以上条件的点标记成 `true`，最后扫一遍，找出可以走到的点上的数中的最大值。

## Code

[AC](https://www.luogu.com.cn/record/82970546)

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int r, c, d, a[1005][1005], ans; //ans 存储答案
bool f[1005][1005];
int main(){
	cin >> r >> c >> d;
	for(int i = 1; i <= r; i++) for(int j = 1; j <= c; j++) cin >> a[i][j];
	//预处理
    if(d % 2){
		for(int i = 1; i <= r; i++) for(int j = 1; j <= c; j++) if(i % 2 != j % 2 && (i - 1) + (j - 1) <= d) f[i][j] = true;
	} else {
		for(int i = 1; i <= r; i++) for(int j = 1; j <= c; j++) if(i % 2 == j % 2 && (i - 1) + (j - 1) <= d) f[i][j] = true;
	}
    //扫一遍找最大值
	for(int i = 1; i <= r; i++) for(int j = 1; j <= c; j++) if(f[i][j]) ans = max(a[i][j], ans);
	cout << ans << endl;
    return 0;
}
```


---

## 作者：LB_tq (赞：0)

# Solution

## 数学题
考虑一个点（i，j），从（1,1）走到它需要（**i-1+j-1**）步。


如果一个点需要走的步数大于d，那么肯定走不到；而等于时肯定能走到，**所以我们只讨论小于d的情况**。

显然，**奇数+偶数=奇数，偶数+偶数=偶数**。

那么如果需要走的步数是奇数，**经过偶数步后仍然可以回来**；偶数步同理。

所以如果要d步刚好走到一个点（i，j），**那么（i-1+j-1）与d的奇偶性相同**（当然也可以是i+j不影响结果），不相同就无法再回到这个点了。

我们可以边读入边判断。

最后（最重要的）：**一定要在最后换行！**（~~坑了我好久~~）



------------


# Code
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,d,ans;
int fr() {
	char ch=getchar();
	while(ch>'9'||ch<'0')
		ch=getchar();
	int sum=ch-'0';
	while((ch=getchar())>='0'&&ch<='9')
		sum=(sum<<3)+(sum<<1)+ch-'0';
	return sum;
}
int main() {
	n=fr();
	m=fr();
	d=fr();
	int x;
	if(d%2==1) {
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++) {
				x=fr();
				if((i-1+j-1)%2==1&&(i-1+j-1)<=d)
					ans=max(ans,x);
			}
	}//分别处理
	else{
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++){
				x=fr();
				if((i-1+j-1)%2==0&&(i-1+j-1)<=d)
					ans=max(ans,x);
			}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

