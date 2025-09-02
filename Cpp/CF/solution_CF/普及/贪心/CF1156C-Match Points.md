# Match Points

## 题目描述

给你一个在数轴上的点集$x_1, x_2, \dots, x_n$。  
每两个点$i$，$j$可以在满足以下情况的时候相连:  

- 点$i$和点$j$均未与其他点相连;
- $\left| x_i - x_j \right| \geq z$.

那么请你求出最多可以连接多少点对？

## 说明/提示

样例1中，可以连接1号点和2号点($\left| 3 - 1 \right| \geq 2$)，3号点和4号点($\left| 7 - 3 \right| \geq 2$).  
样例2中，可以连接1号点和3号点($\left|5 - 10\right| \geq 5$).

## 样例 #1

### 输入

```
4 2
1 3 3 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5
10 9 5 8 7
```

### 输出

```
1
```

# 题解

## 作者：米奇 (赞：3)

## 题解：贪心

这题我们发现如果对于每个数x，找大于等于x+m的数是会错的。

正确的贪心是把数分成两部分，1-n/2，n/2-n

把前一部分匹配后一部分即可

时间复杂度：O(n)

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define gc getchar
const int N=1e6+5;
int n,m,ans,a[N];
/*char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}*/
#define gc getchar
inline int read()
{
	int ret=0,f=0;char c=gc();
	while(!isdigit(c)){if(c=='-')f=1;c=gc();}
	while(isdigit(c)){ret=ret*10+c-48;c=gc();}
	if(f)return -ret;return ret;
}
signed main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	int x=n;
	for(int i=n/2;i;i--)
		if(a[x]-a[i]>=m)ans++,x--;
	cout<<ans;
	return 0;
}
```

---

## 作者：xwh_hh (赞：2)

一道经典的求解转判定的题。

首先，我们可以想到给 $x$ 数组从小到大排序，然后我们思考一个问题：如何判断该数组能否连接 $k$ 对点对？

我们发现，如果存在 $i$，使得 $1\le i\le k$ 与 $x_{n-k+i}-x_i<z$ 同时成立，说明该数组不能连接 $k$ 对点对，否则可以。  
证明很简单，如果 $x_i$ 需要匹配 $x_{n-k+i}$ 后面的元素才行，那么 $x_{i+1}$ 到 $x_k$ 的元素需配对 $x_{n-k-i+2}$ 到 $x_n$ 的元素，元素缺少了。  
所以来一个二分就没了。代码：
```cpp
#include<bits/stdc++.h>
#pragma optimize(3) 
using namespace std;
long long n,z;
long long x[200005];
bool check(int u){
	for(int i=1;i<=u;i++){
		if(x[n-u+i]-x[i]<z) return false;
	}
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>z;
	for(int i=1;i<=n;i++){
		cin>>x[i];
	}
	sort(x+1,x+1+n);//排序 
	int l=0,r=n/2;//二分 
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<r;
	return 0;
} 
```

---

## 作者：Doubeecat (赞：1)

显然，题目是要求在一条坐标轴上两点$(i,j)$满足  
1. 点$i$和点$j$均未与其他点相连;  
2. 两点距离差绝对值小于$z$   


------------

### 法一：  
我们可以想到一个很自然的思路：贪心解决即可。  
使用尺取法，将其从小到大排序后用两个端点移动处理。
复杂度 $O(n\log n)$ 。
代码：
```cpp
#include <cstdio>
#include <cctype>
#include <queue>
#include <algorithm>
#define MAXN 200010
#define ll long long
using namespace std;

inline ll read() {
    ll a=0,f=1;char v=getchar();
    while(!isdigit(v)) {if (v == '-') {f = -1;}v = getchar();}
    while (isdigit(v)) {a = a * 10 + v - 48;v = getchar();}
    return a * f;
}

int pre[MAXN],n,m,ans;

inline bool cmp(int x,int y) {
    return x > y;
}

int main() {
    n = read(),m = read();
    for (int i = 1;i <= n;++i) {
        pre[i] = read();
    }
    sort(pre+1,pre+n+1,cmp);//排序
    int p = n;//设立端点，开始尺取
    for (int i = n / 2;i;--i) {
        if (pre[i] - pre[p] >= m) {
            ans++;p--;//满足要求，答案增加1
        }
    }
    printf("%d",ans);
    return 0;
}
```
------------

### 法二：
同时，这道题我们也可以使用二分来解决，思路也是差不多的。  
先进行排序，后对答案进行二分，check函数就计算是否能达到这个值。  
复杂度 $O(n\log n)$，两种解法的瓶颈都在于排序。
```cpp
#include <cstdio>
#include <cctype>
#include <queue>
#include <stack>
#include <cmath>
#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>
#define MAXN 200010
#define ll long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

inline ll read() {
    ll a=0,f=1;char v=getchar();
    while(!isdigit(v)) {if (v == '-') {f = -1;}v = getchar();}
    while (isdigit(v)) {a = a * 10 + v - 48;v = getchar();}
    return a * f;
}


int pre[MAXN],n,m,ans;

int f(int x) {
    for (int i = 1;i <= x;++i) {
        if (pre[n - x + i] - pre[i] < m) {
            return 0;
        }
    }
    return 1;
}

int main() {
    n = read(),m = read();
    for (int i = 1;i <= n;++i) {
        pre[i] = read();
    }
    sort(pre+1,pre+n+1);
    int l = 0,r = n/2;
    while (l < r) {
        int mid = (l+r+1)>>1;
        if (f(mid)) {
            l = mid;
        }
        else {
            r = mid-1;
        }
    }
    printf("%d",l);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这一题思路：尺取法。

先选第一条边，然后往后枚举。如果找到一条边比第一条边大，那我们就可以选第二条边为最长边,满足 $a[n - k + i] - a[i] < m$。依次枚举，最后取 $n \div 2$ 和当前边取最小值，这题就做完了。

# AC 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN = 1e6 + 10;
const int INF = 0x3f;
int n, m;
int a[MAXN];
int main()
{
	cin >> n >> m;
	for(int i = 1;i <= n; i++){
		cin >> a[i];
	}
	sort(a + 1,a + 1 + n);
	int now = 1;
	for(int i = 1;i <= n; i++){
		if(a[i] - a[now] >= m){
			now++;
		}
	}
	cout << min(n / 2,now - 1);
    return 0;
}
```


---

## 作者：MikeC (赞：0)

## 分析

首先对点进行排序，然后通过二分来枚举答案，显然对于枚举的每一个答案 $k$ ，我们需要满足对于每一个 $i\in [1,k]$，都需要满足 $a[n-k+i]-a[i]<m$，这样使两个端点不断相互逼近最优解即可得到答案。

时间复杂度就是 $O(n \log n)$

## 代码

``````cpp
#include<bits/stdc++.h>
#define AC return
#define AK 0;
using namespace std;
int n,m,l,r;
int a[200001];
inline int check(int k) {
    for (int i=1;i<=k;++i)
        if (a[n-k+i]-a[i]<m) return 0;
    return 1;
}
int main() {
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
    	scanf("%d",&a[i]);	
    }
    sort(a+1,a+n+1);
    l=0,r=n/2;
    while (l<r) {
        int mid=(l+r+1)/2;
        if (check(mid)) l=mid;
        else r=mid-1;
    }
    printf("%d",l);
    AC AK
}
``````

---

## 作者：世末OIer (赞：0)

题解：二分+贪心

二分答案。

贪心策略：先排序。将第i个与第n-md+1个配对，如果不可以就一定不行了


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int n,z;
int main(){
	int i,j;
	scanf("%d%d",&n,&z);
	for(i=0;i<n;i++) scanf("%d",&a[i]);     //读入
	sort(a,a+n);                    //排序后好贪心
	int l=1,r=n/2,ans=0,md;
	while(l<=r){                    //开始二分
		md=l+r>>1;
		bool f=1;
		for(i=0;i<md;++i){             //开始贪心：
			if(a[n-md+i]-a[i]<z){
				f=0;
				break;
			}
		}
		if(f){
			ans=md;                  //储存答案
			l=md+1;
		}else r=md-1;
	}
	printf("%d\n",ans);               //输出
	return 0;
}
```

---

