# Lightsabers (easy)

## 题目描述

海蒂大师面前有 $n$ 名绝地武士，每个人都拿着一把光剑，光剑有 $m$ 种可能的颜色。她需要选择一些连续的武士，使得在选中的武士中，有 $k_1$ 名手持 $1$ 号颜色的光剑，$k_2$ 名手持 $2$ 号颜色的光剑，以此类推，$k_m$ 名手持 $m$ 号颜色的光剑。海蒂想知道这个方案是否可行，如果可行，输出 $\texttt{YES}$，否则输出 $\texttt{NO}$。

## 样例 #1

### 输入

```
5 2
1 1 2 2 1
1 2
```

### 输出

```
YES
```

# 题解

## 作者：___define___ (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF958F1)

题目大意就不讲了，因为题目中已经说的很清楚了。

## 思路

我们可以用双指针去查找，因为它的长度是一定的。定义左右两个端点 $l,r$，先用数组计数把 $1$ 到 $sum$（$sum$ 为 $k$ 数组的总和）的数记录下来，每一次变化就让 $l-1$ 的位置减一、让 $r$ 的位置加一，然后再判断这一段数符不符合条件就可以了。

![](https://cdn.luogu.com.cn/upload/image_hosting/ffeb397d.png)

## AC Code

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[105],z[105],x[105],sum;
bool s=1;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
		cin>>z[i],sum+=z[i];
	for(int i=1;i<=sum;i++)
		x[a[i]]++;
	for(int i=1;i<=m;i++)
		if(x[i]!=z[i]){s=0;break;}
	if(s){
		cout<<"YES";
		return 0;
	}
	for(int l=2,r=sum+1;r<=n;l++,r++)
	{
		x[a[l-1]]--,x[a[r]]++,s=1;
		for(int i=1;i<=m;i++)
			if(x[i]!=z[i]){s=0;break;}
		if(s){
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：DarkShadow (赞：4)

# CF958F1（模拟）

## 题目大意：

给出 $N$ 个数和 $M$ 个要求，求一段区间，使得第 $i$ 种颜色的个数恰好等于第 $i$ 个要求。

## 思路分析：

观察到这道题 $N$、$M \le 100$，所以我们可以直接暴力 $O(N)$ 枚举选中的区间，再 $O(NM)$ 检查当前区间是否符合要求。

首先我们可以算出 $k_1+k_2+...+k_m$ 的值，也就是区间的长度，然后我们再 $O(N)$ 枚举区间左端点并算出右端点，然后对当前区间进行 $M$ 次遍历，每次检查有多少个人拿着第 $i$ 种颜色的剑，总时间复杂度 $O(N^2M)$，可以通过本题。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,d[105],k[105],sum,cnt;
int main(){
	bool flag;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	for(int i=1;i<=m;i++){
		scanf("%d",&k[i]);
		sum+=k[i];
	}
	for(int l=1,r;l<=n;l++){//枚举选中的区间
		r=sum+l-1,flag=1;
		for(int i=1;i<=m;i++){//检查当前区间是否符合要求
			cnt=0;
			for(int j=l;j<=r;j++)
				if(d[j]==i)  cnt++;
			if(cnt!=k[i]){
				flag=0;
				break;
			}
		}
		if(flag){
			printf("YES");
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```

---

## 作者：Withershine (赞：3)

不好意思，当我看到 $1 \le n \le 100$，$1 \le m \le n$ 的那一刻，我承认我心动了。

题目没翻译，用翻译软件翻译了才看懂。

## 思路
依据题意直接模拟即可。这里我用了三层循环来模拟。第一层为 $len$，表示长度；第二层为 $from$，表示出发点，此时需要遍历的区间的终点 $to=from+len-1$，直接遍历，用一个桶数组记录下这里面每个数出现的次数。

每次遍历完后额外进行判断，当满足题意时直接输出 YES 结束程序，否则一律输出 NO。注意每次开始时桶数组要清空。

本题数据范围极小，上述思路复杂度合理，可以通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n , m;
ll a[101] , b[101];
ll t[101] , flag;
signed main()
{
    n = read();
    m = read();
    fr(i , 1 , n)
    {
		a[i] = read();
	}
	fr(i , 1 , m)
	{
		b[i] = read();
	}
	fr(len , 1 , n)
	{
		fr(from , 1 , n)
		{
			flag = 0;
			fr(i , 1 , m)
			{
				t[i] = 0;
			}
			ll to = from + len - 1;
			fr(i , from , to)
			{
				t[a[i]]++;
			}
			fr(i , 1 , m)
			{
				if(t[i] != b[i])
				{
					flag = 1;
					break;
				}
			}
			if(!flag)
			{
				printf("YES");
				return 0;
			}
		}
	}
	printf("NO");
    system("pause");
    return 0;
}
```

---

## 作者：_Violet_Evergarden (赞：2)

看到题解有些空缺，来发一发。

# 思路
由于数据范围较小，所以我们只需要考虑暴力方法即可。我们首先考虑到一个数只能提供一的价值，所以我们要想满足题意的情况，其实就是找一个以 $k_i$ 总和为区间长度的区间，将数统计完和所需的答案一致即可。而我们发现 $n\le100$ 所以我们可以暴力的进行判断即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n;
int len;
int a[1000001];
int k[100001];
int sum[100001];
int flag;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>k[i];
		len+=k[i];
	}
	if(len>n){
		cout<<"NO"<<endl;
		return 0;
	}
	for(int i=1;i<=len;i++){
		sum[a[i]]++;
	}
	for(int i=1;i<=m;i++){
		if(sum[i]!=k[i]){
			flag=1;
		}
	}
	if(flag==0){
		cout<<"YES"<<endl;
		return 0;
	}
	for(int i=2;i+len-1<=n;i++){
		sum[a[i-1]]--;
		sum[a[i+len-1]]++;
		flag=0;
		for(int j=1;j<=m;j++){
			if(sum[j]!=k[j]){
				flag=1;
			}
		}
		if(flag==0){
			cout<<"YES"<<endl;
			return 0;
		}
	}
	cout<<"NO"<<endl;
	return 0;
}
```


---

## 作者：do_while_true (赞：2)

有 $n$ 个绝地武士，每个人手里都拿着一个带有颜色的光剑，共有 $m$ 种不同的颜色。现在想要挑选出连续的一段绝地武士，使得第 $i$ 种颜色出现的次数$=k_i$。求是否能挑选出，能则输出 ```YES```，否则输出```NO```。


设 $sum$=$\sum\limits_{i=1}^{n}k_i$，也就是我们所需要挑选出多少绝地武士，则我们需要找一段 $[l,r]$ 的区间，长度为 $sum$，且满足题目所给条件，选择直接枚举 $l$ 和 $r$ ，同时向右移动，每次移动弹出最前面的，压入下一个。$\mathcal{O}(m)$判断是否合法即可。

### [$\mathcal{Code}$](https://codeforces.com/contest/958/submission/78556033)

---

## 作者：RioFutaba (赞：1)

## 题意
给出 $n$ 和 $m$ 还有序列 $a$ 和 $k$。问 $a$ 是否存在一个连续子序列，其中元素 $i$ 出现了 $k_i$ 次。
## 思路
显而易见，因为编号为 $i$ 的元素出现了 $k_i$ 次，那么这个连续子序列的长度一定为所有 $k_i$ 的和。

那么我们可以枚举长度正确的子序列并进行检查。在枚举过程中，开一个 $cnt$ 数组记录元素出现次数。

首先令 $l=1$ 且 $r=\sum_{m}^{i=1}k_i$。然后每次使 $l+1$，$r+1$	并把前段已经丢弃的元素的出现次数 $-1$，把末端新元素的次数 $+1$。暴力检查每一个连续子序列是否符合要求。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e2+5;
int n,m,a[maxn],k[maxn],cnt[maxn],num;
bool check(){
	for(int i=1;i<=m;i++) if(k[i]!=cnt[i]) return false;//不符合要求 
	return true;
}
int main(){
	cin >> n >> m;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=m;i++){ 
		cin >> k[i];
		num+=k[i];//连续子序列的长度 
	}
	for(int i=1;i<=num;i++) cnt[a[i]]++;//先预处理1~num的元素出现次数 
	if(check()){
		cout << "YES" << endl;
		return 0;
	}//判断 
	for(int l=2;l<=n;l++){
		int r=l+num-1;
		cnt[a[l-1]]--;cnt[a[r]]++;//核心操作 
		if(check()){
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl;//无解 
	return 0;
}
```

---

## 作者：kingho11 (赞：0)

# CF958F1 Lightsabers (easy)题解

原题链接：[Lightsabers (easy)](https://www.luogu.com.cn/problem/CF958F1)

读懂题意后，我们先看一下数据范围 $1\le n\le 100 \quad 1 \le m \le n$。

可见，$n$ 只有 $100$，考虑 $O(n^3)$ 的暴力。

## 思路

暴力枚举区间的左右端点，再用一遍循环去统计里面每个数字的出现次数，放到一个桶里面，最后把每个桶的值与 $k$ 数组进行比对，如果全部都一样，则说明找到了正确的方案，输出```YES```。如果到最后都没有找到正确的方案，就说明没有合理的方案，输出 ```NO``` 即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=105;//n的范围 
long long n,m,a[N],k[N],tong[N]; 
int main()
{
	cin>>n>>m;
	for(long long i=1;i<=n;i++)//输入 
	{
		cin>>a[i];
	}
	for(long long i=1;i<=m;i++)
	{
		cin>>k[i];
	}
	for(long long l=1;l<=n;l++)//暴力枚举两个端点 
	{
		for(long long r=l;r<=n;r++)
		{
			memset(tong,0,sizeof(tong));//记得清空桶哦 
			for(long long i=l;i<=r;i++)
			{
				tong[a[i]]++;
			}
			bool b1=true;
			for(long long i=1;i<=m;i++)
			{
				if(tong[i]!=k[i])
				{
					b1=false;
				}
			}
			if(b1==true)
			{
				cout<<"YES";
				return 0;
			}
		}
	}
	cout<<"NO";
}
```

---

## 作者：Furina_Saikou (赞：0)

这题的思路十分清楚，我就不讲了，看这个数据范围十分小，明显是一个水题，考虑暴力 $ O(n^3) $。

### 思路

第一层循环枚举左端点，第二层循环枚举右端点，第三层循环判断是否成立，为了优化时间，我用函数代替了第三层循环。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1145;
int n,m,k[N],a[N],t[N];//额外开一个t数组作为计数器，记录每种颜色的出现次数 
bool check(int l,int r)
{
	memset(t,0,sizeof t);//每次重置桶 
	for(int i=l;i<=r;i++)
	{
		t[a[i]]++;//对应颜色计数器增加 
		if(t[a[i]]>k[a[i]])return 0;//超出范围直接退出 
	}
	for(int i=1;i<=m;i++)
	{
		if(t[i]<k[i])//不足也要退出 
		{
			return 0;
		}
	}
	return 1; 
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>k[i];
	}
	for(int i=1;i<=n;i++)//枚举左端点 
	{
		for(int j=i;j<=n;j++)//枚举右端点 
		{
			if(check(i,j))//判断区间是否符合题意 
			{
				cout<<"YES";
				return 0;
			}
		}
	}
	cout<<"NO";
	return 0;
}
```

这道题目很简单，可以锻炼打字速度，加强初学者基础。

---

