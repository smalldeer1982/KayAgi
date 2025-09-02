# Robbers' watch

## 题目描述

Robbers, who attacked the Gerda's cab, are very successful in covering from the kingdom police. To make the goal of catching them even harder, they use their own watches.

First, as they know that kingdom police is bad at math, robbers use the positional numeral system with base $ 7 $ . Second, they divide one day in $ n $ hours, and each hour in $ m $ minutes. Personal watches of each robber are divided in two parts: first of them has the smallest possible number of places that is necessary to display any integer from $ 0 $ to $ n-1 $ , while the second has the smallest possible number of places that is necessary to display any integer from $ 0 $ to $ m-1 $ . Finally, if some value of hours or minutes can be displayed using less number of places in base $ 7 $ than this watches have, the required number of zeroes is added at the beginning of notation.

Note that to display number $ 0 $ section of the watches is required to have at least one place.

Little robber wants to know the number of moments of time (particular values of hours and minutes), such that all digits displayed on the watches are distinct. Help her calculate this number.

## 说明/提示

In the first sample, possible pairs are: $ (0:1) $ , $ (0:2) $ , $ (1:0) $ , $ (1:2) $ .

In the second sample, possible pairs are: $ (02:1) $ , $ (03:1) $ , $ (04:1) $ , $ (05:1) $ , $ (06:1) $ .

## 样例 #1

### 输入

```
2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 2
```

### 输出

```
5
```

# 题解

## 作者：zhang_kevin (赞：11)

## 题意简述 

把一天分成 $n$ 小时，$1$ 小时分成 $m$ 分钟，用 **七进制** 来统计几点几分（有前导 $0$），求一天中每个数字都不同的时刻的个数。

## 做题思路

如果时刻的小时和分钟的位数加起来大于 $7$ 那么必然不存在这样的时刻。所以我们暴力枚举出所有情况，写一个 `check` 函数判断它们是否存在，存在个数就 `+1` 即可。

## AC代码

```cpp
#include<cstdio>
#define Max(a, b) (a>b?a:b)
const int N = 1e6+1;
int x, y, tx, ty, vis[N];
bool check(int x, int y){
	for(int i = 0; i <= 6; i++) vis[i] = 0;
	for(int i = 1; i <= tx; i++) vis[x%7]++,x /= 7;
	for(int i = 1; i <= ty; i++) vis[y%7]++,y /= 7;
	for(int i = 0; i <= 6; i++) if(vis[i]>1) return false;
	return true;
}
int main() {
	scanf("%d%d", &x, &y);
	x--;
	y--;
	if(1ll*x*y>6543210){
		printf("0");
		return 0;
	}
	for(int i = x; i; i /= 7){
		tx++;
	}
	for(int i = y; i; i /= 7){
		ty++;
	}
	tx = Max(tx, 1);
	ty = Max(ty, 1);
	int ans = 0;
	for(int i = 0; i <= x; i++){
		for(int j = 0; j <= y; j++){
			if(check(i, j)){
				//printf("(%d:%d)\n", i, j);
				ans++;
			}
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：_edge_ (赞：2)

~~大家好，我是经常喜欢做加强数据版的选手。~~

一看到这道题目，直接想到可以把出现的数给状压掉，然后可以枚举两个数的状压值乘一乘就行了。

更具体的，考虑 234 这个数，那就把 2 进制下的第 2~4 位全都变成 1。

但是怎么求这个呢，暴力枚举然后加个特判也能过，但我脑子很糊涂，写了一个数位 DP。。

具体的，`int DFS(int a1,int a2,int a3)`，a1 表示当前到第几位，a2 表示是否卡着上限，a3 表示当前状压的值。

然后枚举状压值进行数位 DP 即可。

~~结果跑的比暴力还要慢。。。。~~

简单说一下暴力思路，就枚举第一个数枚举第二个数，如果 $n \times m \ge 10^6$ 就直接输出 `0`。

给出数位 DP 实现的代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long 
using namespace std;
const int INF=105;
const int INFN=1e4+5;
int n,m,f[INF][INFN],g[INF],K,F[INFN],F1[INFN];
int calc(int x) {int sum=0;while (x) x/=7,sum++;return sum;}
int DFS(int a1,int a2,int a3) {
	if (a1==0) return a3==K;
	if (!a2 && ~f[a1][a3]) return f[a1][a3];
	int res=0,Max=a2?g[a1]:6;
	for (int i=0;i<=Max;i++) 
		if (!(a3&(1<<i)))
			res+=DFS(a1-1,i==Max && a2,a3|(1<<i));
	if (!a2) f[a1][a3]=res;
	return res;
}
int Calc(int x,int y) {
	memset(g,0,sizeof g);
	memset(f,255,sizeof f);
	while (x) {
		g[++g[0]]=x%7;
		x/=7;
	}
	K=y;
	return DFS(g[0],1,0);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;n--;m--;
	if (m) {for (int i=0;i<128;i++) F[i]=Calc(m,i);}
	else F[1]=1;
	if (n) {for (int i=0;i<128;i++) F1[i]=Calc(n,i);}
	else F1[1]=1;
	int ans=0;
	for (int i=0;i<128;i++)
		for (int j=0;j<128;j++) {
			if (i&j) continue;
//			if (F1[j])
//				cout<<F[i]<<" "<<F1[j]<<" "<<i<<" "<<j<<" ?\n";
			ans+=F[i]*F1[j];
		}
	cout<<ans<<"\n";
	return 0;
}
```

感谢阅读。

---

## 作者：_Execution_ (赞：1)

## 思路

使用暴力枚举，通过检查是否满足每一位都不一样，满足就使计数器增加，最后输出即可。

## 细节

如果小时和分钟的位数加起来大于 $7$，则不存在这样的计时方式。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1e6 + 5;
using namespace std;
int x, y, x0, y0, ans, k[N];
bool check(int x, int y) {
  for (int i = 0; i <= 6; i++)
    k[i] = 0;
  for (int i = 1; i <= x0; i++) {
    k[x % 7]++;
    x /= 7;
  }
  for (int i = 1; i <= y0; i++) {
    k[y % 7]++;
    y /= 7;
  }
  for (int i = 0; i <= 6; i++)
    if (k[i] > 1)
      return 0;
  return 1;
}
signed main() {
  cin>>x>>y;
  x--, y--;
  if (x * y > 6725600) {  // 即总位数大于7
    puts("0");
    return 0;
  }
  for (int i = x; i; i /= 7) x0++;
  for (int i = y; i; i /= 7) y0++;
  x0 = max(x0, 1ll), y0 = max(y0, 1ll);
  for (int i = 0; i <= x; i++)
    for (int j = 0; j <= y; j++)
      if (check(i, j))
        ans++;
  cout<<ans<<"\n";
}

```

---

## 作者：Ryan_Adam (赞：0)

## 题解：CF685A Robbers' watch
感觉这题难点主要在理解题意。
### 题意
一天 $n$ 个小时，一小时 $m$ 分钟，手表用 $7$ 进制表示时间（位数未填满补前导零），求问这个手表显示的**每一位数字都不一样**的时刻数量。
### 分析
因为是 $7$ 进制，所以每一个数字位只可能出现 $0\sim 6$ 这 $7$ 种数字，根据容斥原理，如果 $n$ 和 $m$ 的 $7$ 进制位数之和大于 $7$ 位了，那么就一定会有重复的数字，直接输出 $0$。

因为限制到位数和只能不超过 $7$ 位，那么数据规模就很小了，可以直接暴力枚举 $n$ 和 $m$，枚举每个时刻，用 $\text{check}$ 函数枚举一下 $7$ 进制位有无重复即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int xx,yy;
int vis[10];
bool check(int x,int y)
{
    int a=x,b=y;
    for(int i=0;i<=6;i++)
        vis[i]=0;
    for(int i=1;i<=xx;i++)
    {
        vis[a%7]++;
        a/=7;
    }
    for(int i=1;i<=yy;i++)
    {
        vis[b%7]++;
        b/=7;
    }
    for(int i=0;i<=6;i++)
        if(vis[i]>=2)
            return 0;
    return 1;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    if(n*m>6543210)
    {
        cout<<0<<endl;
        return 0;
    }
    int nn=n,mm=m;
    n--,m--;
    while(n)
    {
        xx++;
        n/=7;
    }
    while(m)
    {
        yy++;
        m/=7;
    }
    xx=max(xx,1ll);
    yy=max(yy,1ll);
    // cout<<xx<<" "<<yy<<endl;
    int ans=0;
    for(int i=0;i<nn;i++)
        for(int j=0;j<mm;j++)
            if(check(i,j))
                ans++;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：__PJL__ (赞：0)

### 思路

观察题面，可以发现，只要 $x$ 和 $y$ 的位数超过或等于 $7$ 位，答案一定是 $0$，所以可以先特判处理 $x$ 和 $y$ 较大的的数据，再暴力枚举所有可能时间。

### 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1e6 + 1;

long long x, y, n, m, lenx, leny, ans, a[MAXN], sumn[MAXN];
bool check(int x, int y) {
	bool ans = true;
	for(int i = 1; i <= lenx; i++) {
		sumn[x % 7]++;
		x /= 7;
	}
	for(int i = 1; i <= leny; i++) {
		sumn[y % 7]++;
		y /= 7;
	}
	for(int i = 0; i <= 6; i++) {
		ans &= (sumn[i] <= 1);
	}
	return ans;
}

int main() {
	cin >> n >> m;
	n--, m--;
	if(n * m > 1000000) {
		cout << 0;
		return 0;
	}
	x = n, y = m;
	while(n) {
		lenx++;
		n /= 7;
	}
	while(m) {
		leny++;
		m /= 7;
	}
	lenx = max(lenx, 1ll);
	leny = max(leny, 1ll);
	for(int i = 0; i <= x; i++) {
		for(int j = 0; j <= y; j++) {
			fill(sumn, sumn + 7, 0);
			ans += check(i, j);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Li_Yichen (赞：0)

给出小时和分钟的上限值，求出一天中每一个用七进制表示的时刻里，每一位都不相同的数量。首先，当小时和分钟超过七位数时，则表示方式不合法，输出零即可。然后计算出小时和分钟的最大位数，枚举每一个可能的时间段，判断是否合法，如果合法就累加答案，输出答案即可。

判断函数里，按照拆位的方式把每一位都保存下来，如果有一个数的出现次数超过一，说明重复了，返回否即可。如果知道判断完了每一个数还没有返回否，说明合法，返回真。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int hour,minute;
int lenh,lenm;
int used[7];
int ans;
int check(int h, int m){
	memset(used,0,sizeof(used));
	int hour = h,minute = m;
	for(int i=1;i<=lenh;i++){
		used[hour % 7] ++;
		hour /= 7;
	}
	for(int i=1;i<=lenm;i++){
		used[minute % 7] ++;
		minute /= 7;
	}
	for(int i=0;i<=6;i++){
		if(used[i] > 1) return 0;
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> hour >> minute;
	hour --,minute --;
	int maxnum = hour * minute;
	if(maxnum > 6543210){
		cout << 0;
		return 0;
	}
	for(int i=hour;i!=0;i/=7){
		lenh ++;
	}
	for(int i=minute;i!=0;i/=7){
		lenm ++;
	}
	if(lenh < 1) lenh = 1;
	if(lenm < 1) lenm = 1;
	for(int i=0;i<=hour;i++){
		for(int j=0;j<=minute;j++){
			if(check(i,j)){
				ans ++; 
			}
		}
	}
	cout << ans;
	return 0;
}
```

---

