# Fault-tolerant Network

## 题目描述

There is a classroom with two rows of computers. There are $ n $ computers in each row and each computer has its own grade. Computers in the first row has grades $ a_1, a_2, \dots, a_n $ and in the second row — $ b_1, b_2, \dots, b_n $ .

Initially, all pairs of neighboring computers in each row are connected by wire (pairs $ (i, i + 1) $ for all $ 1 \le i < n $ ), so two rows form two independent computer networks.

Your task is to combine them in one common network by connecting one or more pairs of computers from different rows. Connecting the $ i $ -th computer from the first row and the $ j $ -th computer from the second row costs $ |a_i - b_j| $ .

You can connect one computer to several other computers, but you need to provide at least a basic fault tolerance: you need to connect computers in such a way that the network stays connected, despite one of its computer failing. In other words, if one computer is broken (no matter which one), the network won't split in two or more parts.

That is the minimum total cost to make a fault-tolerant network?

## 说明/提示

In the first test case, it's optimal to connect four pairs of computers:

1. computer $ 1 $ from the first row with computer $ 2 $ from the second row: cost $ |1 - 4| = 3 $ ;
2. computer $ 3 $ from the first row with computer $ 2 $ from the second row: cost $ |1 - 4| = 3 $ ;
3. computer $ 2 $ from the first row with computer $ 1 $ from the second row: cost $ |10 - 20| = 10 $ ;
4. computer $ 2 $ from the first row with computer $ 3 $ from the second row: cost $ |10 - 25| = 15 $ ;

 In total, $ 3 + 3 + 10 + 15 = 31 $ .In the second test case, it's optimal to connect $ 1 $ from the first row with $ 1 $ from the second row, and $ 4 $ from the first row with $ 4 $ from the second row.

## 样例 #1

### 输入

```
2
3
1 10 1
20 4 25
4
1 1 1 1
1000000000 1000000000 1000000000 1000000000```

### 输出

```
31
1999999998```

# 题解

## 作者：qwqszxc45rtnhy678ikj (赞：8)

首先考虑怎样连接合法。

如果没有线连接两排编号为 $1$ 或 $n$ 的电脑上，那么断掉连接处就会使网络分裂，换而言之，每排编号 $1$、$n$ 的电脑一定会有线连接，也只需要连接这些线段。

对于每一排编号为 $1$、$n$ 的电脑，循环遍历对面的电脑，找到花费最小的一个连接，但此处也需要特判 $1$ 和 $1$、$n$ 和 $n$、$1$ 和 $n$ 相互连接的情况。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, a[200010], b[200010], ans, ta1, tam, tb1, tbn;
int main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; i++) cin >> b[i];
		ta1 = tam = tb1 = tbn = 4e18;
		for(int i = 1; i <= n; i++) ta1 = min(ta1, abs(a[1] - b[i]));
		for(int i = 1; i <= n; i++) tam = min(tam, abs(a[n] - b[i]));
		for(int i = 1; i <= n; i++) tb1 = min(tb1, abs(a[i] - b[1]));
		for(int i = 1; i <= n; i++) tbn = min(tbn, abs(a[i] - b[n]));
		ans = min(abs(a[1] - b[1]) + abs(a[n] - b[n]), abs(a[1] - b[n]) + abs(a[n] - b[1]));
		ans = min(ans, min(abs(a[1] - b[1]) + tam + tbn, abs(a[n] - b[n]) + ta1 + tb1));
		ans = min(ans, min(abs(a[1] - b[n]) + tam + tb1, abs(a[n] - b[1]) + ta1 + tbn));
		ans = min(ans, ta1 + tb1 + tam + tbn);
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：Genius_Star (赞：3)

### 题意：

现有 $2 \times n$ 台计算机分成两排，每排有 $N$ 台，每台都有一定的价值，并且相邻的两台计算机之间通过网线连接。

现在请你在这两排之间接通一些网线，使得任意一台计算机坏掉后这些计算机还是连通的。

连接两台计算机的代价为 $|a-b|$，$a,b$ 分别表示这两台计算机的价值。

### 思路：

画一下图不难发现 $(1,1),(1,n),(2,1),(2,n)$ 这四个端点必须要与另一排相连，因为如果最边上没有与另一排相邻的话，若它旁边的电脑坏掉就联通不了。

所以只要这满足了这四个点有与另一排的连接，就可以保证任意一台计算机坏了之后整个网络还是连通的。

于是就有以下三种情况：

- $(1,1),(1,n)$ 与 $(2,1),(2,n)$ 两两之间连接一下。（两条边）

- $(1,1),(1,n)$ 其中一个与 $(2,1),(2,n)$ 其中一个两两之间连接，剩下两个点与另外一排造成代价最小的连接。（三条边）

- 四根线都与另外一排造成代价最小的连接。（四条边）

也就可以分为两条边、三条边、四条边这三种情况，扫一遍求最小的即可。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,ans;
ll a[N],b[N];
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)
		  a[i]=read();
		for(int i=1;i<=n;i++)
		  b[i]=read();
		ans=min(
			abs(a[1]-b[1])+abs(a[n]-b[n]),
			abs(a[1]-b[n])+abs(a[n]-b[1])
		); //两条边
	    ll d1=1e9,d2=1e9,d3=1e9,d4=1e9; //4个端点与另外一排连接的最小代价
	    for(int i=1;i<=n;i++){
	        d1=min(d1,abs(b[i]-a[1]));
	        d2=min(d2,abs(b[i]-a[n]));
	        d3=min(d3,abs(b[1]-a[i]));
	        d4=min(d4,abs(b[n]-a[i]));
	    }
	    ans=min({
			ans,
			d1+d2+d3+d4, //四条边
			abs(a[1]-b[1])+d2+d4, 
			abs(a[1]-b[n])+d2+d3,
			abs(a[n]-b[1])+d1+d4,
			abs(a[n]-b[n])+d1+d3//三条边
		});
	    write(ans);
	    putchar('\n');
	}
	return 0;
}
```


---

## 作者：wawatime1 (赞：0)

### 题目分析
这道题思维上有难度。

**思路**：要把两排电脑连接成一个容错网络，即任意一台电脑坏掉，网络仍能保持连通。

可以考虑这样一种连接方式：选择两排电脑两端的电脑以及中间至少一对电脑进行连接。这样即使有一台电脑故障，网络也不会断开。

对于每排有台电脑的情况，计算以下几部分代价：

- 第一排第一台电脑与第二排所有电脑连接的最小代价。

- 第一排最后一台电脑与第二排所有电脑连接的最小代价。

- 第一排中间（从第二台到倒数第二台）电脑与第二排所有电脑连接的最小代价。

- 最后将前两部分最小代价之和与第三部分最小代价相加，就是所求的最小总代价。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, a[200010], b[200010], x, y, z, w, u;
int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];
		x = y = z = w = 4e18;
		for (int i = 1; i <= n; i++) x = min(x, abs(a[1] - b[i]));
		for (int i = 1; i <= n; i++) y = min(y, abs(a[n] - b[i]));
		for (int i = 1; i <= n; i++) z = min(z, abs(a[i] - b[1]));
		for (int i = 1; i <= n; i++) w = min(w, abs(a[i] - b[n]));
		u = min(abs(a[1] - b[1]) + abs(a[n] - b[n]), abs(a[1] - b[n]) + abs(a[n] - b[1]));
		u = min(u, min(abs(a[1] - b[1]) + y + w, abs(a[n] - b[n]) + x + z));
		u = min(u, min(abs(a[1] - b[n]) + y + z, abs(a[n] - b[1]) + x + w));
		u = min(u, x + y + z + w);
		cout << u << endl;
	}
	return 0;
}
```

---

## 作者：SnowTrace (赞：0)

这道题目题意有点难懂，基本上意思是让四个角和四个点相连（这四个点也可以是角）。只需找出两边中间最大值，随后考虑四个角两两相连的情况。
```
#include<bits/stdc++.h>
using namespace std;
long long __abs(long long q,long long p){
	if( p == q)return 0;
	else if(p<q)return q-p;
	return p-q;}
long long __mn(long long k,long long l){
	if(k>=l)return l;
	return k;
}
int main(){
	int t;
	cin >> t;
	for(int i = 0;i<t;i++){
		bool can = 1;
		int n;
		long long mn = 10000000000;
		cin >> n;
		long long a[n+5];
		long long b[n+5];
		for(int j = 0;j<n;j++)cin >> a[j];
		for(int j = 0;j<n;j++)cin >> b[j];
		//二点 
		//四点
      //两两不相连
		int p1,p2,p3,p4;
		long long mn5 = __abs(a[0],b[0]);
		long long mn6 = __abs(a[n-1],b[n-1]);
		long long mn7 = __abs(a[0],b[n-1]);
		long long mn8 = __abs(a[n-1],b[0]);
		long long mn1 = 100000000000,mn2 = 100000000000,mn3=1000000000000,mn4 =1000000000000;
		for(int j = 0;j<n;j++){
			if(__abs(a[0],b[j])<mn1){
			mn1= __abs(a[0],b[j]);}
			if(__abs(a[n-1],b[j])<mn2){
			mn2 = __abs(a[n-1],b[j]);}
			if(__abs(b[0],a[j])<mn3){
				mn3 = __abs(b[0],a[j]);
			}if(__abs(b[n-1],a[j])<mn4){
				mn4 = __abs(b[n-1],a[j]);
			}
		}
		mn=  __mn(mn5+mn6,mn);
		mn = __mn(mn7+mn8,mn);
		mn = __mn(mn1+mn3+mn6,mn);
		mn = __mn(mn1+mn4+mn8,mn);//cout << mn << " ";
		mn = __mn(mn2+mn3+mn7,mn);//cout << mn << " ";
		mn = __mn(mn2+mn4+mn5,mn);//cout << mn << " ";
		mn= __mn(mn1+mn2+mn3+mn4,mn);
		cout << mn << endl;
	}return 0;
}
```




---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1500}$
---
### 解题思路：

考虑贪心。

可以发现，任何一个合法的链接方案中，第一排的第一个和最后一个， 第二排的第一个和最后一个一定要和另一端的某一些点链接，否则断开与之相邻的那一个就立即能够使得整个系统不连通。而且，只要这四个被连接了，就一定是一个合法的方案，也就是构成了一个点双。

那么直接讨论这些个点与哪一些点链接即可，需要注意的是，这些点内部也可以相互链接，此时对于链接的两个点而言，不需要另外找点链接。

总复杂度 $O(n)$。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
int T,a[200005],b[200005],ans1,ans2,ans3,ans4,ans,n;
signed main(){
	scanf("%I64d",&T);
	while(T--){
		scanf("%I64d",&n);
		for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
		for(int i=1;i<=n;i++)scanf("%I64d",&b[i]);
		ans1=ans2=ans3=ans4=9223372036854775807;
		for(int i=1;i<=n;i++){
			ans1=min(ans1,abs(a[1]-b[i]));
			ans2=min(ans2,abs(a[n]-b[i]));
			ans3=min(ans3,abs(a[i]-b[1]));
			ans4=min(ans4,abs(a[i]-b[n]));
		}
		ans=ans1+ans2+ans3+ans4;
		ans=min(ans,ans1+ans3+abs(a[n]-b[n]));
		ans=min(ans,ans1+ans4+abs(a[n]-b[1]));
		ans=min(ans,ans2+ans3+abs(a[1]-b[n]));
		ans=min(ans,ans2+ans4+abs(a[1]-b[1]));
		ans=min(ans,abs(a[1]-b[1])+abs(a[n]-b[n]));
		ans=min(ans,abs(a[1]-b[n])+abs(a[n]-b[1]));
		printf("%I64d\n",ans);
	}
	return 0;
}
```


---

