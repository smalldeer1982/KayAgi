# [USACO21OPEN] Do You Know Your ABCs? S

## 题目描述

Farmer John 的奶牛正在 mooZ 视频会议平台上举行每日集会。她们发明了一个简单的数字游戏，为会议增添一些乐趣。

Elsie 有三个正整数 $A$、$B$ 和 $C$（$1\le A\le B\le C$）。这些数字是保密的，她不会直接透露给她的姐妹 Bessie。她告诉 Bessie $N$（$4\le N\le 7$）个不同的整数 $x_1,x_2,\ldots,x_N$（$1\le x_i\le 10^9$），并宣称每一个 $x_i$ 都是 $A$、$B$、$C$、$A+B$、$B+C$、$C+A$ 或 $A+B+C$ 之一。然而，Elsie 可能在撒谎；这些整数 $x_i$ 可能并没有对应任何一组合法的 $(A,B,C)$。

Bessie 百思不得其解，所以需要靠你来求出与 Elsie 给出的数相符合的三元组 $(A,B,C)$ 的数量。

每个输入包含 $T$（$1\le T\le 100$）组需要独立求解的测试用例。

## 说明/提示

#### 样例说明

对于 $x=\{4,5,7,9\}$，五个可能的三元组如下：

$$(2, 2, 5), (2, 3, 4), (2, 4, 5), (3, 4, 5), (4, 5, 7).$$

#### 测试点性质：

- 测试点 $1 \sim 4$ 中，所有的 $x_i$ 不超过 $50$。
- 测试点 $5 \sim 5$ 满足 $N=7$。
- 测试点 $7 \sim 15$ 没有额外限制。

#### 说明

供题：Benjamin Qi

## 样例 #1

### 输入

```
10
7
1 2 3 4 5 6 7
4
4 5 7 8
4
4 5 7 9
4
4 5 7 10
4
4 5 7 11
4
4 5 7 12
4
4 5 7 13
4
4 5 7 14
4
4 5 7 15
4
4 5 7 16```

### 输出

```
1
3
5
1
4
3
0
0
0
1```

# 题解

## 作者：封禁用户 (赞：9)

~~这题题意比较清楚，就不解释了。~~

先进行分析，题目已经告诉我们，$1 \le A \le B \le C$，所以可以分析出
 $1 \le A \le B \le A+B,C \le A+C \le B+C \le A+B+C$，除了$A+B$ 和 $C$ 其它大小关系都是可以确定的。
 
我们把每一个进行二进制编号，$A$ 放在第一位，$B$ 放在第二位，$C$ 放在第三位，所以上述字母编号分别对应着 $1,2,3,4,5,6,7$，**但其中 $3$ 和 $4$ 的大小关系无法确定**。

所以只要枚举每个式子对应的数字，进行加减操作求解，注意只有互相包含的两个数字可以进行操作。

因为可能解出相同的解，注意最后要对解进行**去重**。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -1;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10^48);
}
int a[10],b[10],num[10];
//1:A 2:B 3:A+B 4:C 5:A+C 6:B+C 7:A+B+C
int T,n,ans;
bitset<10> vis;
vector<int> g[10],h[10]; 
set<long long> pt;
void dfs(int u)
{
	if(u > n) 
	{
		memset(num,0,sizeof(num));
		for(int i = 1;i <= n;++i)  num[b[i]] = a[i];
		bool flag = 0;
		for(int o = 1;o <= 3;++o)
			for(int i = 1;i <= 7;++i)
			{
				for(auto j:g[i]) 
				{
					if(!num[j]||!num[i-j]) continue;
					if(num[i]&&num[i] != num[j] + num[i-j]) 
						return;	
					num[i] = num[j] + num[i-j];	
				}
				for(auto j:h[i])
				{
					if(!num[j]||!num[j-i]) continue;
					if(num[i]&&num[i] != num[j] - num[j-i]) 
						return;	
					num[i] = num[j] - num[j-i];	
				}
			}
		if(num[1] >= 1&&num[2] >= num[1]&&num[4] >= num[2]) pt.insert(114514ll*114514ll*num[1]+114514ll*num[2]+num[4]);
		return;
	}
	for(int i = 1;i <= 7;++i)
	{
		if(vis[i]) continue;
		b[u] = i;
		bitset<10> tp = vis;
		bool flag = 0;
		if(i == 4&&!vis[3]) flag = 1;
		for(int j = 1;j <= i;++j) vis[j] = 1;
		if(flag) vis[3] = 0;
		dfs(u+1);
		vis = tp; 
	}
}
int main()
{
	g[3].push_back(1),g[3].push_back(2);
	g[5].push_back(1),g[5].push_back(4);
	g[6].push_back(2),g[6].push_back(4);
	for(int i = 1;i <= 6;++i) g[7].push_back(i);
	h[1].push_back(3),h[1].push_back(5),h[1].push_back(7);
	h[2].push_back(3),h[2].push_back(6),h[2].push_back(7);
	h[3].push_back(7); 
	h[4].push_back(5),h[4].push_back(6),h[4].push_back(7);
	h[5].push_back(7);
	h[6].push_back(7);
	read(T);
	while(T--)
	{
		read(n);
		for(int i = 1;i <= n;++i) read(a[i]);
		sort(&a[1],&a[n+1]);
		vis = 0;
		pt.clear();
		dfs(1);
		write(pt.size());
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：tiger2005 (赞：7)

### 题意简述

给定一些数字 $x_i$，求出有多少组 $(A,B,C)$，使得 $1 \leq A \leq B \leq C$，并且 $\forall i,x_i \in \{A,B,C,A+B,B+C,A+C,A+B+C\}$。

其中保证 $x_i$ 互不相同且个数在 4 到 7 中间。

### 分析

这道题实际上并没有什么好解决的方法。我们假设上面的 7 种和是 7 个桶，而我们需要做的就是往里面放入几个数字使其对应，然后暴力求出解。我们很容易发现者 7 个数的大小关系只有两个（从小到大）：

$$A,B,C,A+B,A+C,B+C,A+B+C\ or\ A,B,A+B,C,A+C,B+C,A+B+C$$

那么我们只需要将 $x_i$ 按大小顺序填进去，然后计算的时候把第三个和第四个交换一下再算一次就行。

关于计算的方法：我们发现会有四种情况：

$A,B,C$ 中三个确定了：直接进行校验就行。

$A,B,C$ 中两个确定了：通过剩下的 5 个位置中，除了两个确定的位置之和外还有四个位置，并且里面一定有一个确定的数字。直接利用那个数字解出剩下的数字校验。

$A,B,C$ 中一个确定了：发现 $A+B,B+C,A+C$ 中有两个确定，可以直接计算出剩下两个数字并且校验。

$A,B,C$ 中没有确定的：可以知道 $A+B,B+C,A+C,A+B+C$ 确定，可以接解出 $A,B,C$，最后校验就行。



```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;
int T,N,A[10];
int B[10],C[4];
int ans;
set<pair<int,pair<int,int> > > st;
inline bool checkD(int a,int b){
	return a==0 || a==b;
}
inline bool checkIf(){
	return C[1]>0 && C[2]>=C[1] && C[3]>=C[2]
	&& checkD(B[1],C[1]) && checkD(B[2],C[2]) && checkD(B[3],C[3])
	&& checkD(B[4],C[1]+C[2]) && checkD(B[5],C[1]+C[3]) && checkD(B[6],C[3]+C[2])
	&& checkD(B[7],C[1]+C[2]+C[3])
	&& !st.count(make_pair(C[1],make_pair(C[2],C[3])));
}
inline void Overall(){
	C[1]=C[2]=C[3]=0;
	if(B[1] && B[2]){
		C[1]=B[1];C[2]=B[2];
		if(B[3])	C[3]=B[3];
		else if(B[5])	C[3]=B[5]-C[1];
		else if(B[6])	C[3]=B[6]-C[2];
		else C[3]=B[7]-C[1]-C[2];
		if(checkIf())	++ans,st.insert(make_pair(C[1],make_pair(C[2],C[3])));
		return;
	}
	if(B[1] && B[3]){
		C[1]=B[1];C[3]=B[3];
		if(B[2])	C[2]=B[2];
		else if(B[4])	C[2]=B[4]-C[1];
		else if(B[6])	C[2]=B[6]-C[3];
		else C[2]=B[7]-C[1]-C[3];
		if(checkIf())	++ans,st.insert(make_pair(C[1],make_pair(C[2],C[3])));
		return;
	}
	if(B[2] && B[3]){
		C[2]=B[2];C[3]=B[3];
		if(B[1])	C[1]=B[1];
		else if(B[4])	C[1]=B[4]-C[2];
		else if(B[5])	C[1]=B[5]-C[3];
		else C[1]=B[7]-C[2]-C[3];
		if(checkIf())	++ans,st.insert(make_pair(C[1],make_pair(C[2],C[3])));
		return;
	}
	if(B[1]){
		C[1]=B[1];
		if(B[4])	C[2]=B[4]-C[1];
		if(B[5])	C[3]=B[5]-C[1];
		if(B[6]){
			if(C[2])	C[3]=B[6]-C[2];
			else	C[2]=B[6]-C[3];
		}
		if(checkIf())	++ans,st.insert(make_pair(C[1],make_pair(C[2],C[3])));
		return;
	}
	if(B[2]){
		C[2]=B[2];
		if(B[4])	C[1]=B[4]-C[2];
		if(B[6])	C[3]=B[6]-C[2];
		if(B[5]){
			if(C[1])	C[3]=B[5]-C[1];
			else	C[1]=B[5]-C[3];
		}
		if(checkIf())	++ans,st.insert(make_pair(C[1],make_pair(C[2],C[3])));
		return;
	}
	if(B[3]){
		C[3]=B[3];
		if(B[5])	C[1]=B[5]-C[3];
		if(B[6])	C[2]=B[6]-C[3];
		if(B[4]){
			if(C[1])	C[2]=B[4]-C[1];
			else	C[1]=B[4]-C[2];
		}
		if(checkIf())	++ans,st.insert(make_pair(C[1],make_pair(C[2],C[3])));
		return;
	}
	int p=1ll*(B[4]+B[5]+B[6])/2;
	C[1]=p-B[6];
	C[2]=p-B[5];
	C[3]=p-B[4];
	if(checkIf())	++ans,st.insert(make_pair(C[1],make_pair(C[2],C[3])));
}
void dfs(int x,int k){
	if(x==8 && k!=N+1)	return;
	if(k==N+1){
		Overall();
		swap(B[3],B[4]);
		Overall();
		swap(B[3],B[4]);
		return;
	}
	dfs(x+1,k);
	B[x]=A[k];
	dfs(x+1,k+1);
	B[x]=0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=1;i<=N;i++)
			scanf("%d",&A[i]);
		sort(A+1,A+N+1);
		dfs(1,1);
		printf("%d\n",ans);
		ans=0;st.clear();
	}
	return 0;
}
```

---

## 作者：lyt_awa (赞：5)

## 简要题意
给定一些数字 $x_i$，求出有多少组 $(A,B,C)$，使得 $1 \leq A \leq B \leq C$，并且 $\forall i,x_i \in \{A,B,C,A+B,B+C,A+C,A+B+C\}$ 其中保证 $x_i$ 互不相同且个数在 $4$ 到 $7$ 中间。
## 思路
**暴力**。

枚举每一个 $x_i$ 分别对应 $\{A,B,C,A+B,B+C,A+C,A+B+C\}$ 中的哪一个，可以用一个 $a$ 数组来记录：  
$a_1$ 表示 $A$ 的值。  
$a_2$ 表示 $B$ 的值。  
$a_3$ 表示 $C$ 的值。  
$a_4$ 表示 $A+B$ 的值。  
$a_5$ 表示 $B+C$ 的值。  
$a_6$ 表示 $A+C$ 的值。  
$a_7$ 表示 $A+B+C$ 的值。

然后枚举每一个 $x_i$ 填在哪，再通过已知的值（未知的值用 $0$ 来表示）算出 $A,B,C$ 再验证正确性就 ok 了（记得判重）。


------------
最后，AC代码奉上。
```cpp
#include <bits/stdc++.h>
using namespace std;

int t;
int n, x[8], a[8], ans, b[8];
int ji[1000005][3];

void dfs(int p) {
	if (p == n) {
		memcpy(b, a, sizeof(b));
		if (b[4]) {
			if (!b[1] && b[2]) b[1] = b[4] - b[2];
			if (!b[2] && b[1]) b[2] = b[4] - b[1];
			if (!b[3] && b[7]) b[3] = b[7] - b[4];
		}
		if (b[5]) {
			if (!b[2] && b[3]) b[2] = b[5] - b[3];
			if (!b[3] && b[2]) b[3] = b[5] - b[2];
			if (!b[1] && b[7]) b[1] = b[7] - b[5];
		}
		if (b[6]) {
			if (!b[1] && b[3]) b[1] = b[6] - b[3];
			if (!b[3] && b[1]) b[3] = b[6] - b[1];
			if (!b[2] && b[7]) b[2] = b[7] - b[6];
		}
		if (b[1] > 0 && b[1] <= b[2] && b[2] <= b[3]) {
			if (b[4] && b[4] != b[1] + b[2]) return;
			if (b[5] && b[5] != b[2] + b[3]) return;
			if (b[6] && b[6] != b[3] + b[1]) return;
			if (b[7] && b[7] != b[1] + b[2] + b[3]) return;
			for (int i = 1; i <= ans; ++i)
				if (ji[i][0] == b[1] && ji[i][1] == b[2] && ji[i][2] == b[3]) return;
			++ans;
			ji[ans][0] = b[1];
			ji[ans][1] = b[2];
			ji[ans][2] = b[3];
		}
		return;
	}
	for (int i = 1; i <= 7; ++i) {
		if (a[i]) continue;
		a[i] = x[p];
		dfs(p + 1);
		a[i] = 0;
	}
}

signed main() {
	scanf("%d", &t);
	while (t--) {
		ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) scanf("%d", &x[i]);
		sort(x, x + n);
		memset(a, 0, sizeof(a));
		dfs(0);
		printf("%d\n", ans);
	}
	return 0;
}
```
时间复杂度 $\Theta (T\cdot A_7^n)$。

---

## 作者：NDFS (赞：3)

这一题的数据范围非常小，考虑设数组 $D_{1...7}$ 分别表示 $A,B,C,A+B,B+,A+C,A+B+C$，可以在 $O(7^n)$ 的时间内求出 $D_{1...7}$ 的所有方案，对于这些方案可以分类讨论判断。

1. $A+B,B+C,A+C$ 未确定（为 $0$），那么如果 $1≤A≤B≤C$ 且和为 $A+B+C$ 就是合法的情况。

2. $A+B,B+C,A+C$ 有确定的再分类讨论，根据这三个值看能否确定不确定的 $A,B,C$ 以及是否合法。

最后再一个个对应判断，并且和以前的答案作比较去重。

总的时间复杂度 $O(T·7^n)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,x[8],sum,a,b,c,d[8];
int ax[1000005],bx[1000005],cx[1000005];
void dfs(int t)
{
	if(t>n)
	{
		a=d[1],b=d[2],c=d[3];
		if(!d[4]&&!d[5]&&!d[6])
		{
			if(a+b+c==d[7]&&a<=b&&b<=c)sum++;
			return;
		}
		if(d[4])
		{
			if(a&&!b&&d[4]-a<=0)return;
			else if(a&&!b)b=d[4]-a;
			if(!a&&b&&d[4]-b<=0)return;
			else if(!a&&b)a=d[4]-b;
			if(a&&b&&a+b!=d[4])return;
			if(d[7]&&!c&&d[7]-d[4]<=0)return;
			else if(d[7]&&!c)c=d[7]-d[4];
			if(d[7]&&c&&d[7]-c!=d[4])return;
		}
		if(d[5])
		{
			if(b&&!c&&d[5]-b<=0)return;
			else if(b&&!c)c=d[5]-b;
			if(!b&&c&&d[5]-c<=0)return;
			else if(!b&&c)b=d[5]-c;
			if(b&&c&&b+c!=d[5])return;
			if(d[7]&&!a&&d[7]-d[5]<=0)return;
			else if(d[7]&&!a)a=d[7]-d[5];
			if(d[7]&&a&&d[7]-a!=d[5])return;
		}
		if(d[6])
		{
			if(a&&!c&&d[6]-a<=0)return;
			else if(a&&!c)c=d[6]-a;
			if(!a&&c&&d[6]-c<=0)return;
			else if(!a&&c)a=d[6]-c;
			if(a&&c&&a+c!=d[6])return;
			if(d[7]&&!b&&d[7]-d[6]<=0)return;
			else if(d[7]&&!b)b=d[7]-d[6];
			if(d[7]&&b&&d[7]-b!=d[6])return;
		}
		if(a>b||b>c||a>c)return;
		if(a!=d[1]&&d[1])return;
		if(b!=d[2]&&d[2])return;
		if(c!=d[3]&&d[3])return;
		if(a+b!=d[4]&&d[4])return;
		if(b+c!=d[5]&&d[5])return;
		if(a+c!=d[6]&&d[6])return;
		if(a+b+c!=d[7]&&d[7])return;
		for(int i=1;i<=sum;i++)
		{
			if(ax[i]==a&&bx[i]==b&&cx[i]==c)return;
		}
		sum++,ax[sum]=a,bx[sum]=b,cx[sum]=c;
		return;
	}
	for(int i=1;i<=7;i++)
	{
		if(!d[i])d[i]=x[t],dfs(t+1),d[i]=0;
	}
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&x[i]),d[i]=0;
		sum=0,dfs(1);
		printf("%d\n",sum);
	}
	return 0;
}
```

---

## 作者：Hooch (赞：2)

可以把它分成 4 种情况来做：

+ 第一种情况 （已知 $A,B,C$）：

直接判断是否合法即可。

+ 第二种情况 （已知 $A,B$）：

枚举一个 $x$ 的值为 $A+C$ 或 $B+C$ 或 $A+B+C$。

然后把 $C$ 算出来。

最后知道 $A,B,C$， 就用第一种情况的方法去算。

+ 第三种情况 （已知 $A$）：

枚举一个 $x$ 的值为 $A+B$。

然后把 $B$ 算出来。

最后用第二种情况的方法算。

+ 第四种情况 （什么也不知道）：

由于题目中 $N \ge 4$ 的原因, 所以也就只有 $A+B, A+C, B+C, A+B+C$ 的值确定。

所以可以枚举得到 $A+B$ 与 $A+C$ 与 $A+B+C$ 的值。

然后将 $A+B$ 加上 $A+C$ 减去一个 $A+B+C$ 确定了 $A$ 的值。

$A$ 的值确定了， $B$ 和 $C$ 的值也能相继算出来。

最后用第一种情况的方法验证。

***

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, j, n) for (register int i = j; i <= n; ++i)
#define rep2(i, j, n) for (register int i = j; i >= n; --i)
#define il inline
#define ll long long
#define int long long
using namespace std;
int n, x[20], aa, bb, cc; bool vis[10];
map <int, map <int, map <int, int> > > v;  
const int Buffer_Size = 1 << 10;
char buffer[Buffer_Size], *ihead = buffer + Buffer_Size, *itail = ihead;
char Next_Char() {
	if (ihead == itail) fread(buffer, 1, Buffer_Size, stdin), ihead = buffer;
	return *ihead++;
}
template <typename T>
il void read(T &x) {
	x = 0; T f = 1; char ch = Next_Char();
	while (!isdigit(ch)) {if (ch == '-') f = -1; ch = Next_Char();}
	while (isdigit(ch)) {x = (x << 1) + (x << 3) + (ch & 15); ch = Next_Char();} x *= f;
} //以上为快读，与最终代码无关
il bool check(int i, int j, int k) { //第一种情况 
	memset(vis, 0, sizeof vis);
	int a = x[i], b = x[j], c = x[k];
	rep1(p, 1, n) {
		if (p == i || p == j || p == k) continue;
		if (a + b == x[p]) {
			if (vis[1]) return false;
			vis[1] = true; //找到 A+B 
		} else if (a + c == x[p]) {
			if (vis[2]) return false;
			vis[2] = true; //找到 A+C 
		} else if (b + c == x[p]) {
			if (vis[3]) return false;
			vis[3] = true; //找到 B+C 
		} else if (a + b + c == x[p]) {
			if (vis[4]) return false;
			vis[4] = true; //找到 A+B+C 
		} else return false;
	}
	int l[10] = {0, a, b, c};
	sort(l + 1, l + 1 + 3);
	if (!v[l[1]][l[2]][l[3]] /* map 判重*/) {v[l[1]][l[2]][l[3]] = 1; return true;}
	return false;
}
il int check1(int i, int j) { //第二种情况 
	int a = x[i], b = x[j], count = 0;
	rep1(_, 1, n) {
		if (_ == i || _ == j) continue;
		if (x[_] > a + b) {
			x[9] = x[_] - a - b; //因为原数列中没有 C, 所以用 9 代替
			int p = check(i, j, 9);
			if (p) ++count;
		} if (x[_] > a) {
			x[9] = x[_] - a; 
			int p = check(i, j, 9);
			if (p) ++count;
		} if (x[_] > b) {
			x[9] = x[_] - b; 
			int p = check(i, j, 9);
			if (p) ++count;
		}
	}
	return count;
}
il int check2(int i) { //第三种情况 
	int a = x[i], p = 0;
	rep1(_, 1, n) {
		if (_ == i) continue;
		if (x[_] > a) {
			x[8] = x[_] - a; //与51行同理 
			p += check1(i, 8);
		}
	}
	return p;
}
il int check3(int i, int j, int k) { //第四种情况 
	int aplusb = x[i], aplusc = x[j], aplusbplusc = x[k];
	int a = aplusb + aplusc - aplusbplusc;
	int b = aplusb - a;
	int c = aplusc - a;
	if (a > 0 && b > 0 && c > 0 ) {
		x[8] = a, x[9] = b, x[10] = c; //与51行同理
		int tmp = check(8, 9, 10);
		return tmp;
	}
	return 0;
}
signed main(void) {
	int t; read(t);
	while (t--) {	
		read(n); v.clear(); memset(x, 0, sizeof x);
		rep1(i, 1, n) read(x[i]); memset(vis, 0, sizeof vis);
		sort(x + 1, x + 1 + n); int ans = 0;
		rep1(i, 1, n) rep1(j, i + 1, n) rep1(k, j + 1, n) ans += check(i, j, k);
		rep1(i, 1, n) rep1(j, i + 1, n) ans += check1(i, j);
		rep1(i, 1, n) ans += check2(i);
		if (n == 4 /*小优化，因为只有在只有 A+B,A+C,B+C,A+B+C 的时候才找*/) {
			rep1(i, 1, n) rep1(j, i + 1, n) rep1(k, j + 1, n) ans += check3(i, j, k);
		} 
		printf("%d\n", ans);
	}
}
```

~~感觉比一堆 if 更优美一些~~



---

## 作者：CrTsIr400 (赞：2)

https://blog.csdn.net/STJqwq/article/details/119718414

题目考虑暴力，既然 $4\le n\le 7$ ，$O(T(n+1)^7)$ 都可以。

枚举每个位置 $A,B,C,A+B,A+C,B+C,A+B+C$ 这七个位置分别放哪个数，也可以不放。最后直接判断是否合法即可。

注意这里的方案可能有重复，多个相同的 $A,B,C$ ，所以我们搞一个哈希判重。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int inf=1073741823;typedef long long LL;int FL;char CH;template<typename T>bool in(T&a){if(CH==EOF)return 0;for(FL=1,CH=getchar(),a=0;(CH<'0'||CH>'9')&&CH!=EOF;CH=getchar())if(CH=='-')FL=-1;for(;CH>='0'&&CH<='9'&&CH!=EOF;CH=getchar())a=a*10+CH-'0';return a*=FL,1;}template<typename T,typename...Args>int in(T&a,Args&...args){return in(a)+in(args...);}
int fo[8][3]={{},{},{},{},{1,2},{1,3},{2,3},{1,2,3}},a[8],c[8],d[8],n;
int HD[1145149],Ea[1000010],Eb[1000010],Ec[1000010],CNT,FR[1000010],NX[1000010];
int usd[8];
void ins(int x,int a,int b,int c){
	Ea[++CNT]=a;Eb[CNT]=b;Ec[CNT]=c;NX[CNT]=HD[x];HD[x]=CNT;FR[CNT]=x;
}
bool chk(int x,int a,int b,int c){
	for(RI i=HD[x];i;i=NX[i]){
		if(Ea[i]==a&&Eb[i]==b&&Ec[i]==c)return 1;
	}return 0;
}
bool chkhs(int a,int b,int c){
	LL num=a*1000000007ll+b*10000007ll+c;
	num%=1145149;
	if(chk(num,a,b,c))return 1;
	ins(num,a,b,c);return 0;
}
bool pdres(){
	for(RI i=1;i<=7;++i)c[i]=d[i];
	for(RI i=1;i<=2;++i){//这里循环两次是因为后面的计算有可能计算出一开始未计算出的数，我们需要将d数组全部计算出来再次判定
		if(c[1]&&c[2]){if(c[4]&&c[4]!=c[1]+c[2])return 0;if(!c[4])c[4]=c[1]+c[2];}
		if(c[1]&&c[3]){if(c[5]&&c[5]!=c[1]+c[3])return 0;if(!c[5])c[5]=c[1]+c[3];}
		if(c[2]&&c[3]){if(c[6]&&c[6]!=c[2]+c[3])return 0;if(!c[6])c[6]=c[2]+c[3];}
		if(c[1]&&c[6]){if(c[7]&&c[7]!=c[1]+c[6])return 0;if(!c[7])c[7]=c[1]+c[6];}
		if(c[6]&&c[7]){if(c[1]&&c[1]!=c[7]-c[6])return 0;if(!c[1])c[1]=c[7]-c[6];}
		if(c[2]&&c[5]){if(c[7]&&c[7]!=c[2]+c[5])return 0;if(!c[7])c[7]=c[2]+c[5];}
		if(c[5]&&c[7]){if(c[2]&&c[2]!=c[7]-c[5])return 0;if(!c[2])c[2]=c[7]-c[5];}
		if(c[3]&&c[4]){if(c[7]&&c[7]!=c[3]+c[4])return 0;if(!c[7])c[7]=c[3]+c[4];}
		if(c[4]&&c[7]){if(c[3]&&c[3]!=c[7]-c[4])return 0;if(!c[3])c[3]=c[7]-c[4];}
		if(c[1]&&c[2]&&c[3]){if(c[7]&&c[7]!=c[1]+c[2]+c[3])return 0;if(!c[7])c[7]=c[1]+c[2]+c[3];}
	}//码农判断
	if(c[1]<=0||c[2]<=0||c[3]<=0)return 0;
	if(c[1]+c[2]!=c[4])return 0;
	if(c[1]+c[3]!=c[5])return 0;
	if(c[2]+c[3]!=c[6])return 0;
	if(c[1]+c[2]+c[3]!=c[7])return 0;
	//判定一下
	memset(usd,0,sizeof(usd));
	for(RI i=1;i<=7;++i){
		int fndpos=lower_bound(a+1,a+n+1,c[i])-a;
		if(a[fndpos]==c[i])++usd[fndpos];
	}//判断这个d数组是否出现了 a 的全部元素
	for(RI i=1;i<=n;++i)if(!usd[i])return 0;
	sort(c+1,c+4);
	if(chkhs(c[1],c[2],c[3]))return 0;
	return 1;
}
int dfs(int dep){
//	for(RI i=1;i<=dep;++i)putchar('>');
//	printf("%d\n",d[dep-1]);
	if(dep==8)
		return pdres();
	int ans=0;
	d[dep]=0;ans+=dfs(dep+1);
	for(RI i=1;i<=n;++i){
		d[dep]=a[i];
		ans+=dfs(dep+1); 
		d[dep]=0;
	}return ans;
}
int gans(){
	in(n);
	for(RI i=1;i<=n;++i)in(a[i]);
	sort(a+1,a+n+1);
//	for(RI i=1;i<=n;++i)printf("%d ",a[i]);putchar(10);
	memset(d,0,sizeof(d));
	memset(c,0,sizeof(c));
	for(RI i=1;i<=CNT;++i)HD[FR[i]]=0,Ea[i]=Eb[i]=Ec[i]=NX[i]=0;
	CNT=0;
	printf("%d\n",dfs(1));
}
int main(){
	int t;
	in(t);
	while(t--)gans();
	return 0;
}
```

然后交上去 88 分，其中有一个点跑了 5000+ ms，于是我们在循环里剪枝即可 AC 。

正解代码：

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int inf=1073741823;typedef long long LL;int FL;char CH;template<typename T>bool in(T&a){if(CH==EOF)return 0;for(FL=1,CH=getchar(),a=0;(CH<'0'||CH>'9')&&CH!=EOF;CH=getchar())if(CH=='-')FL=-1;for(;CH>='0'&&CH<='9'&&CH!=EOF;CH=getchar())a=a*10+CH-'0';return a*=FL,1;}template<typename T,typename...Args>int in(T&a,Args&...args){return in(a)+in(args...);}
int fo[8][3]={{},{},{},{},{1,2},{1,3},{2,3},{1,2,3}},a[8],c[8],d[8],n;
int HD[1145149],Ea[1000010],Eb[1000010],Ec[1000010],CNT,FR[1000010],NX[1000010];
int usd[8];
void ins(int x,int a,int b,int c){
	Ea[++CNT]=a;Eb[CNT]=b;Ec[CNT]=c;NX[CNT]=HD[x];HD[x]=CNT;FR[CNT]=x;
}
bool chk(int x,int a,int b,int c){
	for(RI i=HD[x];i;i=NX[i]){
		if(Ea[i]==a&&Eb[i]==b&&Ec[i]==c)return 1;
	}return 0;
}
bool chkhs(int a,int b,int c){
	LL num=a*1000000007ll+b*10000007ll+c;
	num%=1145149;
	if(chk(num,a,b,c))return 1;
	ins(num,a,b,c);return 0;
}
bool pdres(){
	for(RI i=1;i<=7;++i)c[i]=d[i];
//	printf(">{%d,%d,%d,%d,%d,%d,%d}\n",c[1],c[2],c[3],c[4],c[5],c[6],c[7]);
	for(RI i=1;i<=2;++i){
		if(c[1]&&c[2]){if(c[4]&&c[4]!=c[1]+c[2])return 0;if(!c[4])c[4]=c[1]+c[2];}
		if(c[1]&&c[3]){if(c[5]&&c[5]!=c[1]+c[3])return 0;if(!c[5])c[5]=c[1]+c[3];}
		if(c[2]&&c[3]){if(c[6]&&c[6]!=c[2]+c[3])return 0;if(!c[6])c[6]=c[2]+c[3];}
		if(c[1]&&c[6]){if(c[7]&&c[7]!=c[1]+c[6])return 0;if(!c[7])c[7]=c[1]+c[6];}
		if(c[6]&&c[7]){if(c[1]&&c[1]!=c[7]-c[6])return 0;if(!c[1])c[1]=c[7]-c[6];}
		if(c[2]&&c[5]){if(c[7]&&c[7]!=c[2]+c[5])return 0;if(!c[7])c[7]=c[2]+c[5];}
		if(c[5]&&c[7]){if(c[2]&&c[2]!=c[7]-c[5])return 0;if(!c[2])c[2]=c[7]-c[5];}
		if(c[3]&&c[4]){if(c[7]&&c[7]!=c[3]+c[4])return 0;if(!c[7])c[7]=c[3]+c[4];}
		if(c[4]&&c[7]){if(c[3]&&c[3]!=c[7]-c[4])return 0;if(!c[3])c[3]=c[7]-c[4];}
		if(c[1]&&c[2]&&c[3]){if(c[7]&&c[7]!=c[1]+c[2]+c[3])return 0;if(!c[7])c[7]=c[1]+c[2]+c[3];}
	}
	if(c[1]<=0||c[2]<=0||c[3]<=0)return 0;
	if(c[1]+c[2]!=c[4])return 0;
	if(c[1]+c[3]!=c[5])return 0;
	if(c[2]+c[3]!=c[6])return 0;
	if(c[1]+c[2]+c[3]!=c[7])return 0;
//	printf("T:a=%d b=%d c=%d a+b=%d b+c=%d a+c=%d a+b+c=%d\n",c[1],c[2],c[3],c[4],c[5],c[6],c[7]);
//	printf("%d %d %d %d %d %d %d\n",d[1],d[2],d[3],d[4],d[5],d[6],d[7]);
	memset(usd,0,sizeof(usd));
	for(RI i=1;i<=7;++i){
		int fndpos=lower_bound(a+1,a+n+1,c[i])-a;
		if(a[fndpos]==c[i])++usd[fndpos];
	}
	for(RI i=1;i<=n;++i)if(!usd[i])return 0;
//	printf(">Q:a=%d b=%d c=%d a+b=%d b+c=%d a+c=%d a+b+c=%d\n",c[1],c[2],c[3],c[4],c[5],c[6],c[7]);
	sort(c+1,c+4);
	if(chkhs(c[1],c[2],c[3]))return 0;
//	printf(">>a=%d b=%d c=%d a+b=%d b+c=%d a+c=%d a+b+c=%d\n",c[1],c[2],c[3],c[4],c[5],c[6],c[7]);
	return 1;
}
int dfs(int dep){
//	for(RI i=1;i<=dep;++i)putchar('>');
//	printf("%d\n",d[dep-1]);
	if(dep==5&&d[4])if(d[1]&&d[2]&&d[1]+d[2]!=d[4])return 0;
	if(dep==6&&d[5])if(d[1]&&d[3]&&d[1]+d[3]!=d[5])return 0;
	if(dep==7&&d[6])if(d[2]&&d[3]&&d[2]+d[3]!=d[6])return 0;
    //循环中也判断一下合法性，直接剪枝
	if(dep==8)
		return pdres();
	int ans=0;
	d[dep]=0;ans+=dfs(dep+1);
	for(RI i=1;i<=n;++i){
		d[dep]=a[i];
		ans+=dfs(dep+1); 
		d[dep]=0;
	}return ans;
}
int gans(){
	in(n);
	for(RI i=1;i<=n;++i)in(a[i]);
	sort(a+1,a+n+1);
//	for(RI i=1;i<=n;++i)printf("%d ",a[i]);putchar(10);
	memset(d,0,sizeof(d));
	memset(c,0,sizeof(c));
	for(RI i=1;i<=CNT;++i)HD[FR[i]]=0,Ea[i]=Eb[i]=Ec[i]=NX[i]=0;
	CNT=0;
	printf("%d\n",dfs(1));
}
int main(){
	int t;
	in(t);
	while(t--)gans();
	return 0;
}
```

AC快乐！

---

## 作者：free_fall (赞：2)

# 题目大意
给 $t$ 组数据，每组数据有一个 $n$ 和 $n$ 个数，这些数为 $A$、$B$、$C$、$A+B$、$B+C$、$A+C$、$A+B+C$ 中任意 $n$ 个不重复的数。求每个满足条件的不同的 $(A,B,C)$ 三元组的数量。
# 思路
因为可能的情况数很少，所以可以考虑使用暴力枚举的方法来枚举这些情况，用 
$a_1$、$a_2$、$a_3$、$a_4$、$a_5$、$a_6$、$a_7$ 分别表示 $A$、$B$、$C$、$A+B$、$B+C$、$A+C$、$A+B+C$，然后进行验证，一个满足条件的 $(A,B,C)$ 三元组需要满足以下条件：

$\left\{\begin{matrix}
a_1\le a_2\le a_3
 \\
a_1+a_2=a_4
 \\
a_2+a_3=a_5
 \\
a_1+a_3=a_6
 \\
a_1+a_2+a_3=a_7
\end{matrix}\right.$

由题目可知 $4\le N\le 7$ 所以可能出现有数空着的情况，这个时候我们可以将空着的情况记为 $0$，然后根据确定的数来推出空着的数，再进行检查，这样用代码实现就会比较简单。

```
if(a[1]>0&&a[1]<=a[2]&&a[2]<=a[3]){
	if(a[4]&&a[4]!=a[1]+a[2])return;
	if(a[5]&&a[5]!=a[2]+a[3])return;
	if(a[6]&&a[6]!=a[1]+a[3])return;
	if(a[7]&&a[7]!=a[1]+a[2]+a[3])return;
	ans++;
}
```

最后一定要记住不要忘记把重复的情况去掉：
```
for(int i=1;i<=ans;i++){
	if(v[i][0]==a[1]&&v[i][1]==a[2]&&v[i][2]==a[3])return;
}
```
这样就能把这道题过掉了，时间复杂度为 $O(t\times A^n_7)$，剩余代码比较简单，就不再展示了。

---

