# Taxi drivers and Lyft

## 题目描述

Palo Alto is an unusual city because it is an endless coordinate line. It is also known for the office of Lyft Level 5.

Lyft has become so popular so that it is now used by all $ m $ taxi drivers in the city, who every day transport the rest of the city residents — $ n $ riders.

Each resident (including taxi drivers) of Palo-Alto lives in its unique location (there is no such pair of residents that their coordinates are the same).

The Lyft system is very clever: when a rider calls a taxi, his call does not go to all taxi drivers, but only to the one that is the closest to that person. If there are multiple ones with the same distance, then to taxi driver with a smaller coordinate is selected.

But one morning the taxi drivers wondered: how many riders are there that would call the given taxi driver if they were the first to order a taxi on that day? In other words, you need to find for each taxi driver $ i $ the number $ a_{i} $ — the number of riders that would call the $ i $ -th taxi driver when all drivers and riders are at their home?

The taxi driver can neither transport himself nor other taxi drivers.

## 说明/提示

In the first example, we have only one taxi driver, which means an order from any of $ n $ riders will go to him.

In the second example, the first taxi driver lives at the point with the coordinate $ 2 $ , and the second one lives at the point with the coordinate $ 6 $ . Obviously, the nearest taxi driver to the rider who lives on the $ 3 $ coordinate is the first one, and to the rider who lives on the coordinate $ 5 $ is the second one. The rider who lives on the $ 4 $ coordinate has the same distance to the first and the second taxi drivers, but since the first taxi driver has a smaller coordinate, the call from this rider will go to the first taxi driver.

In the third example, we have one rider and the taxi driver nearest to him is the fourth one.

## 样例 #1

### 输入

```
3 1
1 2 3 10
0 0 1 0
```

### 输出

```
3 ```

## 样例 #2

### 输入

```
3 2
2 3 4 5 6
1 0 0 0 1
```

### 输出

```
2 1 ```

## 样例 #3

### 输入

```
1 4
2 4 6 10 15
1 1 1 1 0
```

### 输出

```
0 0 0 1 ```

# 题解

## 作者：_Cloud_ (赞：5)

###### 重新用latex渲染了一下

# 目前最快的方法
## 思路：
开两个数组，类似前缀和与后缀和 $(\text {sumf,sumb})$，一个记录前 $i$ 个节点到第 $i$ 节点最小距离的节点（前缀最优点），一个记录从 $n+m$ 到第 $i$ 节点的最小距离的节点（后缀最优点）。

遍历每一个 $i$，比较 $\text {sumf}$ 与 $\text {sumb}$ 大小即可。$\text {sumf}_0,\text {sumb}_{n+m+1}$附无穷大表示 $0$ 节点之前无司机和 $n+m+1$ 节点后无司机。

注意：因为最后输出的是数组，所以要在节点无穷大的地方特判。

### $\text {Code}$

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e5 + 5;

int sumf[N * 2], sumb[N * 2];
int ans[N * 2];

struct Node {
	int z, s;
} a[N * 2];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n + m; i++) 
		scanf("%d", &a[i].z);
	for (int i = 1; i <= n + m; i++)
		scanf("%d", &a[i].s);//按从小到大给的数据，不用sort 
	
	sumf[0] = sumb[n + m + 1] = 214748364;//无穷大表示没有司机 
	
	for (int i = 1; i <= n + m; i++) {//前缀最优 
		if (a[i].s == 1)
			sumf[i] = i;
		else
			sumf[i] = sumf[i - 1];
	}
	
	for (int i = n + m; i >= 1; i--) {//后缀最优 
		if (a[i].s == 1)
			sumb[i] = i;
		else
			sumb[i] = sumb[i + 1];
	}
	
	for (int i = 1; i <= n + m; i++) {
		if (a[i].s == 0) {
			if (sumf[i] == 214748364 && sumb[i] < 214748364) {//特判，不然会下标越界 
				ans[sumb[i]]++;
				continue;
			}
			if ((sumb[i] == 214748364 && sumf[i] < 214748364)) {//同上 
				ans[sumf[i]]++;
				continue;
			}
			if (a[i].z - a[sumf[i]].z <= a[sumb[i]].z - a[i].z) {
				ans[sumf[i]]++;
			} else {
				ans[sumb[i]]++;
			}
		}
	}
	
	for (int i = 1; i <= n + m; i++) {
		if (a[i].s == 1)//是司机就输出 
			printf("%d ", ans[i]);
	}
	return 0;
}
```

#### 评测结果：
![非O2](https://cdn.luogu.com.cn/upload/image_hosting/eogystt0.png)
PS：当然，这也只是目前最快的，原因是做的人不多。感谢@[做梦想Peach](https://www.luogu.com.cn/user/239030)提供的latex渲染。

---

## 作者：DarkShadow (赞：4)

# CF1075B（模拟）

## 题目大意：

给出 $M$ 个司机和 $N$ 个乘客，每个人会叫离自己最近的出租车，求对于没辆出租车，有多少个乘客会叫它。

## 思路分析：

首先我们可以想到对于每个乘客，暴力枚举每个司机，看哪个司机离自己最近。时间复杂度 $O(NM)$，会 TLE。

考虑优化，因为每个乘客呼叫的司机一定是自己左右两边的司机中较近的一个，所以我们可以 $O(N)$ 预处理出每个乘客左右两边的司机，然后再 $O(N)$ 算出每个司机的答案就可以了。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200005;
int n,m,pos[N],d[N],ans[N],lst[N],nxt[N];
/*
pos表示每个乘客、司机的位置
d表示当前位置是司机还是乘客
ans表示每个司机的答案
lst、nxt分别表示乘客前面、后面的第一个司机
*/
int main(){
	int t;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+m;i++)
		scanf("%d",&pos[i]);
	for(int i=1;i<=n+m;i++){
		scanf("%d",&d[i]);
		if(d[i])  lst[i]=i;//计算自己前面的第一个司机
		else  lst[i]=lst[i-1];
	}
	for(int i=n+m;i>=1;i--)
		if(d[i])  nxt[i]=i;//计算自己后面的第一个司机
		else  nxt[i]=nxt[i+1];
	for(int i=1;i<=n+m;i++){
		if(d[i])  continue;//分情况讨论计算答案
		if(lst[i]==0)  t=nxt[i];
		else if(nxt[i]==0)  t=lst[i];
		else if(pos[i]-pos[lst[i]]<=pos[nxt[i]]-pos[i])  t=lst[i];
		else  t=nxt[i];
		ans[t]++;
	}
	for(int i=1;i<=n+m;i++)
		if(d[i])  printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：Weak_Konjak (赞：2)

## 思路

### 二分查找

##### 对于每个乘客，查找他在哪两个司机中间，判断哪个更近就可以了

## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m,driver[100001],a[200001],rider[100001],d,rr,p,s[100001];//s为计数数组
int find(int x){//二分查找在driver[]中最后一个小于等于x的数
	int l=1,r=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(x<driver[mid]) r=mid-1;
		else l=mid+1;
	}
	return r;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n+m;i++) cin>>a[i];
	for(int i=1;i<=n+m;i++){//输入，储存
		cin>>p;
		if(p) driver[++d]=a[i];
		else rider[++rr]=a[i];
	}
	for(int i=1;i<=n;i++){
		int k=find(rider[i]);
		if(k==m) s[m]++;//特判
		else{
			if(!k) s[1]++;
			else
			if(driver[k+1]-rider[i]<rider[i]-driver[k]) s[k+1]++;
			else s[k]++;
		}
	}
	for(int i=1;i<=m;i++) cout<<s[i]<<' ';
} 
```


---

## 作者：liuyz11 (赞：1)

原比赛题解：[https://www.cnblogs.com/nblyz2003/p/9907114.html](https://www.cnblogs.com/nblyz2003/p/9907114.html) 

题意：一条路上有n个乘客和m个出租车司机，给你他们的坐标（增序且保证没有坐标相同），每个乘客会向最近的一个司机发送订单，假如有两个最近的司机，发给坐标小的。求每个司机会收到多少个订单。

用数组res[i].first记录第i个人（乘客）最近的司机距离，res[i].second记录下标（因为有序，只要下标小坐标也一定小），即会收到订单的司机。

只要对于每个司机，向前后分别找所有的乘客j，更新res[j]，遇到别的司机就停止。最后再记录每个司机收到的订单。

代码如下

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define all(x) begin(x), end(x)
#define pb push_back
#define mp make_pair
#define MAXN 200005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long LL;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 10000007;
//head by DYH

pii res[MAXN];
int a[MAXN], ans[MAXN];
bool flag[MAXN];

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    rep(i, 1, n + m){
        scanf("%d", &a[i]);
        res[i] = mp(INF, INF);
    }
    rep(i, 1, n + m) scanf("%d", &flag[i]);
    rep(i, 1, n + m){
        if(flag[i]){
            repd(j, i - 1, 1){
                if(flag[j]) break;
                res[j] = min(res[j], mp(a[i] - a[j], i));
            }
            rep(j, i + 1, n + m){
                if(flag[j]) break;
                res[j] = min(res[j], mp(a[j] - a[i], i));
            }
        }
    }
    rep(i, 1, n + m)
        if(!flag[i]) ans[res[i].se]++;
    rep(i, 1, n + m)
        if(flag[i]) printf("%d ", ans[i]);
    puts("");
    return 0;
}
```

---

## 作者：qw1234321 (赞：0)

简单二分。

将司机的坐标存进一个数组并排序，然后遍历每一个乘客，在司机的坐标中查找到当前乘客的位置在哪两个司机中间，判断一下那哪个司机离得近即可。

二分可以偷懒使用 `upper_bound`。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define rg register
using namespace std;

const int N = 2e5 + 5;
int n, m, a[N], b[N], c[N], ans[N], ida, idb;

signed main(){
	cin >> n >> m;
	for (int i = 1; i <= n + m; i++) cin >> c[i];
	for (int i = 1, x; i <= n + m; i++){
		cin >> x;
		if (!x) a[++ida] = c[i];
		else b[++idb] = c[i];
	}
	sort(b + 1, b + m + 1);
	b[0] = LONG_LONG_MIN;
	b[m + 1] = LONG_LONG_MAX;
	for (int i = 1; i <= n; i++){
		int p = upper_bound(b + 1, b + m + 1, a[i]) - b - 1;
		if (p == m){
			ans[m]++;
			continue;
		}
		if (p == 0){
			ans[1]++;
			continue;
		}
		if (b[p + 1] - a[i] < a[i] - b[p]) ans[p + 1]++;
		else ans[p]++;
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

显然对于第 $i$ 个乘客，司机的位置必定在 $x_i$ 的左边或右边，则正序和倒序分别跑出第 $i$ 个乘客左边最近的司机和右边最近的司机即可进行处理。

处理的时候必定要分成三类进行处理，情况如下：

1. 第 $i$ 个乘客的左边没有司机，此时的司机为右边最近的。
1. 第 $i$ 个乘客的右边没有司机，此时的司机为左边最近的。
1. 第 $i$ 个乘客的左右均有司机，此时需要判断处理。

#### code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define lx first
#define ly second
const int maxn=2e5+10;
int n,m;
pii a[maxn];int num[maxn];
int ans[maxn];
inline int read(){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n+m;++i)a[i].lx=read();
    for(int i=1;i<=n+m;++i)a[i].ly=read();
    // sort(a+1,a+n+m+1);
    int last=-1;
    for(int i=1;i<=n+m;++i){
        if(a[i].ly!=0)last=i;
        else num[i]=last;
    }
    last=n+m+1;
    for(int i=n+m;i>=1;--i){
        if(a[i].ly!=0)last=i;
        else{
            if(num[i]==-1)ans[last]++;
            else if(last==n+m+1)ans[num[i]]++;
            else {
                // ans[min(i-num[i],last-i)]++; 
                if(a[i].lx-a[num[i]].lx<=a[last].lx-a[i].lx)ans[num[i]]++;
                else ans[last]++;//这里绝对不能直接用 i,num[i],必须要用 a[i]取地址。
            }
        }
    }
    for(int i=1;i<=n+m;++i){
        if(a[i].ly!=0)cout << ans[i] << " ";
    }
    return 0;
}
```

---

## 作者：TRZ_2007 (赞：0)

**[题解 【CF1075B Taxi drivers and Lyft】](https://www.luogu.com.cn/problem/CF1075B)**    
# Solution  

观察数据范围，发现 $\mathcal{O(nm)}$ 的算法是跑不过去的，也就是说我们不能通过枚举 $a_i$ 来解决问题。  
发现所有的坐标都是单调的，而且对于每一个乘客来说，接她的车只会是在离她**最近的左边的一辆和离她最近的右边的一辆中选最小值**，所以可以通过二分来计算出这两辆车的坐标最后得到解，时间复杂度 $\mathcal{O(n\log m)}$。  
~~最后贴一下最优解代码。~~  
# Code  
```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;

#define gc getchar
inline int read() {
	int c = gc(), t = 1, n = 0;
	while(isspace(c)) { c = gc(); }
	if(c == '-') { t = -1, c = gc(); }
	while(isdigit(c)) { n = n * 10 + c - '0', c = gc(); }
	return n * t;
}
#undef gc

const int N = 2e5 + 9;

int a[N],b[N],p[N],d[N],ans[N];
int n,m,np,nd,id;

int main() {
	n = read(); m = read();
	for(int i = 1;i <= n + m;i++) a[i] = read();
	for(int i = 1;i <= n + m;i++) b[i] = read();
	for(int i = 1;i <= n + m;i++) {
		if(b[i] == 0) p[++np] = a[i];
		else d[++nd] = a[i];
	}
	sort(d + 1,d + m + 1);
	d[0] = -1e9;	//注意，这里一定要设立极限值，不然有可能会有乘客上了 0 号黑车（逃
	for(int i = 1;i <= n;i++) {
		if(p[i] >= d[m]) { ans[m]++; continue; }	//都比最表最大的大了，那么只能有最后一辆车来接他
		id = lower_bound(d + 1,d + m + 1,p[i]) - d;	//否则计算第一个大于等于他的坐标的车（右边离他最近的）
		if(d[id] - p[i] >= p[i] - d[id - 1]) ++ans[id - 1];
		else ++ans[id];
	}
	for(int i = 1;i <= m;i++) printf("%d ",ans[i]);
	return 0;
}

```

---

