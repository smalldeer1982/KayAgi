# LuoTianyi and the Table

## 题目描述

LuoTianyi gave an array $ b $ of $ n \cdot m $ integers. She asks you to construct a table $ a $ of size $ n \times m $ , filled with these $ n \cdot m $ numbers, and each element of the array must be used exactly once. Also she asked you to maximize the following value:

  $ \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\left(\max\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}-\min\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}\right) $ This means that we consider $ n \cdot m $ subtables with the upper left corner in $ (1,1) $ and the bottom right corner in $ (i, j) $ ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ), for each such subtable calculate the difference of the maximum and minimum elements in it, then sum up all these differences. You should maximize the resulting sum.

Help her find the maximal possible value, you don't need to reconstruct the table itself.

## 说明/提示

In the first test case, the table is follows:

4113In the subtable with the bottom right corner in $ (1, 1) $ , the difference of the maximal and minimal elements is $ 4 - 4 = 0 $ .

In the subtable with the bottom right corner in $ (1, 2) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

In the subtable with the bottom right corner in $ (2, 1) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

In the subtable with the bottom right corner in $ (2, 2) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

Then the maximum possible value is $ 0+3+3+3=9 $ .

In the second test case, all elements are equal, so all differences are $ 0 $ , and the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
2 2
1 3 1 4
2 2
-1 -1 -1 -1
2 3
7 8 9 -3 10 8
3 2
4 8 -3 0 -7 1
4 3
-32030 59554 16854 -85927 68060 -64460 -79547 90932 85063 82703 -12001 38762```

### 输出

```
9
0
64
71
1933711```

# 题解

## 作者：Pt_crN (赞：3)

构造题。

跟着感觉走，想到要让最大化，那么就让最大的那个数贡献最多次，放 $(1,1)$，然后让最小的两个数分别放 $(1,2),(2,1)$。其中最小的那一个放的位置为 $\begin{cases}(1,2),n\leq m\\(2,1),n>m\end{cases}$。这样产生的贡献是最大的。

然后发现也可以将最小的放 $(1,1)$，最大两个放 $(1,2),(2,1)$，同理解决，取最大值即可。

code：

```cpp
int n,m,e[200007];
void solve(){
	scanf("%d%d",&n,&m);
	if(n<m)
		swap(n,m);
	for(int i=1;i<=n*m;i++)
		scanf("%d",&e[i]);
	sort(e+1,e+n*m+1);
	printf("%lld\n",1ll*(n-1)*m*(e[n*m]-e[1])+1ll*(m-1)*max(e[n*m-1]-e[1],e[n*m]-e[2]));
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：ScapegoatTree (赞：1)

构造题。

答案只跟最大值和最小值有关，所以我们考虑把最大值放在 $(1,1)$，把最小的两个值放在 $(2,1)$ 和 $(1,2)$，使贡献最大，或者最小值在 $(1,1)$，两个大值放在 $(2,1)$ 和 $(1,2)$，两种方案取大即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,m;
int b[10005];
void solve(){
	cin>>n>>m;
	memset(b,0,sizeof(b));
	for(int i=0;i<n*m;i++) cin>>b[i];
	sort(b,b+n*m);
	long long ans1=((b[n*m-1]-b[1])*(min(n,m)-1))+((b[n*m-1]-b[0])*(n*m-(min(n,m)-1)-1));
	long long ans2=((b[n*m-2]-b[0])*(min(n,m)-1))+((b[n*m-1]-b[0])*(n*m-(min(n,m)-1)-1));
	long long ans=max(ans1,ans2);
	cout<<ans<<'\n';
}
int main(){
	cin>>T;
	while(T--)solve();
    return 0;
}
```

---

## 作者：fengziyi (赞：1)

### 前言

赛时居然先搓 C 题没搓出来，夜自修结束前在机房卡点搞过，南蚌。

### 思路

要让差值最大，则使该矩形中最大值尽量大，最小值尽量小。

要让尽可能多的矩阵差值较大，则要将最大最小尽量放在左上角。

然而会有一行或者一列不能同时含有最大和最小，考虑使用次大次小值。

观察样例发现需要考虑放：

 - 最大值，次大值和最小值，其中最小值在最左上角。
 - 最小值，次小值和最大值，其中最大值在最左上角。

同时次大次小值要沿着短边放，否则会有更多的值取不到最大最小之差。

统计答案并比较输出即可。

### 贴个代码

```cpp
while (T--)
{
    cin >> n >> m;
    int len = n * m;
    int mx = -inf, smx = -inf, mn = inf, smn = inf;
    for (reg int i = 1, x; i <= len; ++i)
    {
        cin >> x;
        if (x >= mx)       { smx = mx; mx = x; }
        else if (x >= smx) { smx = x; }
        if (x <= mn)       { smn = mn; mn = x; }
        else if (x <= smn) { smn = x; }
    }
    i64 res1 = (mx - smn) * (min(n, m) - 1)
    		 + (max(n, m) - 1) * min(n, m) * (mx - mn);
    i64 res2 = (smx - mn) * (min(n, m) - 1) 
    		 + (max(n, m) - 1) * min(n, m) * (mx - mn);
    cout << max(res1, res2) << endl;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1825B)    
有意思的思维题。         
我们贪心地想，容易发现 $a_{1,1}$ 不是最小值就是最大值。      
那么我们也容易发现 $a_{1,2}$ 和 $a_{2,1}$ 可能是最大值、最小值、次小值或次大值。    
那么我们对于所有情况计算出来结果取最大值即可。     
接下来是对所有情况的分析：        
我们先对 $b$ 从小到大进行排序，$b_1$ 为最小值，$b_2$ 为次小值，$b_{n\times m-1}$ 为次大值，$b_{n\times m}$ 为最大值。         
## $a_{1,1}$ 填最小值     
还是贪心地想，为了结果最大，$a_{1,2}$ 和 $a_{2,1}$ 只能是最大值或次大值。但是填次大值和最大值产生的结果可能不同。      
### $a_{1,2}$ 填最大值，$a_{2,1}$ 填次大值     
我们 $a_{2,1}$ 填了次大值，所以第一列除了第一行的结果都为 $a_{2,1}-a_{1,1}$，这一部分结果为 $(n-1)\times(b_{n\times m-1}-b_1)$。       
那么对于其他情况，都包含了 $a_{1,1}$ 和 $a_{1,2}$，所以对于其他所有情况，贡献都为 $a_{1,2}-a_{1,1}$，这一部分结果易知为 $n\times(m-1)\times(b_{n\times m}-b_1)$。     
这部分总共产生的贡献为两部分贡献之和。     
接下来的内容大体相似，这里就只放式子了。      
### $a_{1,2}$ 填次大值，$a_{2,1}$ 填最大值 
贡献为 $(m-1)\times(b_{n\times m-1}-b_1)+m\times(n-1)\times (b_{n\times m}-b_1)$。     
## $a_{1,1}$ 填最大值     
这里的 $a_{1,2}$ 和 $a_{2,1}$ 需要填最小值和次小值。       
### $a_{1,2}$ 填最小值，$a_{2,1}$ 填次小值 
贡献为 $(n-1)\times(b_{n\times m}-b_2)+n\times(m-1)\times(b_{n\times m}-b_1)$。
### $a_{1,2}$ 填次小值，$a_{2,1}$ 填最小值 
贡献为 $(m-1)\times(b_{n\times m}-b_2)+m\times(n-1)\times (b_{n\times m}-b_1)$。             
由于这部分的数学式子比较多，所以如果有写错的地方请指出。       
[CODE](https://www.luogu.com.cn/paste/c19bwm53)

---

## 作者：WRuperD (赞：0)

简单构造题。

### 思路

发现答案只跟这个矩形中最大值和最小值有关。于是考虑将最大或最小的那个数放在左上角，保证每一个矩形的最大值最大或最小值最小。容易想到，我们会将最大，次大或者最小，次小放在 $(1,1)$ 和 $(2,1)$。分类讨论即可。

### 代码

```cpp

// Problem: LuoTianyi and the Table
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1825B
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 4e5+10;

int a[MAX];

bool cmp(int x, int y){
	return x > y;
}

void solve(){
	int n = read(), m = read();
	for(int i = 1; i <= n * m; i++){
		a[i] =  read(); 
	}
	sort(a+1, a+n*m+1);
	int x = 0;
	if((n-1)*m < (m-1)*n){
		x = n - 1;
	}else if((n-1)*m == (m-1)*n){
		x = max(n-1, m-1);
	}else{
		x = m - 1;
	}
	int cnt1 = (a[n*m] - a[1]) * max((n-1)*m,(m-1)*n) + (a[n*m]-a[2]) * x;
	sort(a+1, a+n*m+1, cmp);
	int cnt2 = abs(a[n*m] - a[1]) * max((n-1)*m,(m-1)*n) + abs(a[n*m]-a[2]) * x; endl;
	write(max(cnt1, cnt2)),endl;
}

signed main(){
	int t = read();
	while(t--)	solve();
	return 0;
}
```

---

