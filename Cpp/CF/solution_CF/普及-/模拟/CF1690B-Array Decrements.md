# Array Decrements

## 题目描述

Kristina has two arrays $ a $ and $ b $ , each containing $ n $ non-negative integers. She can perform the following operation on array $ a $ any number of times:

- apply a decrement to each non-zero element of the array, that is, replace the value of each element $ a_i $ such that $ a_i > 0 $ with the value $ a_i - 1 $ ( $ 1 \le i \le n $ ). If $ a_i $ was $ 0 $ , its value does not change.

Determine whether Kristina can get an array $ b $ from an array $ a $ in some number of operations (probably zero). In other words, can she make $ a_i = b_i $ after some number of operations for each $ 1 \le i \le n $ ?

For example, let $ n = 4 $ , $ a = [3, 5, 4, 1] $ and $ b = [1, 3, 2, 0] $ . In this case, she can apply the operation twice:

- after the first application of the operation she gets $ a = [2, 4, 3, 0] $ ;
- after the second use of the operation she gets $ a = [1, 3, 2, 0] $ .

Thus, in two operations, she can get an array $ b $ from an array $ a $ .

## 说明/提示

The first test case is analyzed in the statement.

In the second test case, it is enough to apply the operation to array $ a $ once.

In the third test case, it is impossible to get array $ b $ from array $ a $ .

## 样例 #1

### 输入

```
6
4
3 5 4 1
1 3 2 0
3
1 2 1
0 1 0
4
5 3 7 2
1 1 1 1
5
1 2 3 4 5
1 2 3 4 6
1
8
0
1
4
6```

### 输出

```
YES
YES
NO
NO
YES
NO```

# 题解

## 作者：minVan (赞：7)

小学生第一次发题解

**题目解释**

给出两个长度为 $n$ 的序列 $a$ 和 $b$。

定义一次操作为将一个序列中的所有非零整数全都减少 $1$。
例如对于序列 $[3,5,4,1]$，我们对其进行两次操作之后得到的结果分别是 $[2,4,3,0]$ 和 $[1,3,2,0]$。

现在我们要求出能否可以通过对序列 $a$ 进行许多次操作（也可以不做）得到序列 $b$。

如果可以的话就输出 `YES` ，反之输出 `NO` 。

**题目思路**

首先，$a_i$ 一定要大于等于 $b_i$ ，不然永远也减不到 $b_i$  ，出现这种情况直接输出 `NO`。

上面是需要特判的，接下来我们先找到第一个 $b_i \neq 0$ 的数并取出对应的 $a_i$ ，然后建立差 $bz$ ，$bz \gets a_i - b_i$  ，接着遍历所有相对应的 $a_i$ 与 $b_i$ ，如果 $a_i - b_i > bz$ ，那么一定减不到； 如果 $a_i - b_i < bz$ ，那么一定减过头了，但除 $b_i = 0$ 外，因为即使减到 $0$ 了还可以继续减而不会变成负数，因为题面说过：定义一次操作为将一个序列中的所有非零整数全都减少 $1$。

**AC代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 50005;
int t, n;
int a[N], b[N];
int main() {
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for(int i = 1; i <= n; i++) {
			cin >> b[i];
		}
		bool flag = 1;
		int maxc = 0;
		for(int i = 1; i <= n; i++) {
			if(a[i] < b[i]) {
				flag = 0;
				break;
			}
			maxc = max(maxc, a[i] - b[i]);
		}
		if(!flag) {
			cout << "NO\n";
			continue;
		}
		for(int i = 1; i <= n; i++) {
			if(max(a[i] - maxc, 0) != b[i]) {
				flag = 0;
				break;
			}
		}
		if(flag) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
	return 0;
}
```

---

## 作者：liruixiong0101 (赞：5)

## 题目简述：
本题有多组测试数据。  
给定两个长度为 $n$ 的序列 $a$ 和 $b$。  
定义一次操作为将一个序列中的所有非零整数全都减少 $1$。   
例如对于序列 $[3,5,4,1]$，我们对其进行两次操作之后得到的结果分别是 $[2,4,3,0]$ 和 $[1,3,2,0]$。  
现在我们需要求出是否可以通过对序列 $a$ 进行若干次操作（也可以不做）得到序列 $b$。  
如果可以的话就输出 `YES`，反之输出 `NO`，对大小写不做要求。

~~题意简述复制 markdown 。~~

## 思路：
首先我们可以发现如果 $b_i=0$，说明 $b_i$ 至少减了 $a_i$ 次。  
否则设 $d_i=a_i-b_i$，$d_i<0$ 时，肯定无解输出 `NO`，若 $d_i\ge0$ ,需要保证所有 $b_i\ne0$ 的 $i$ 满足所有 $d_i$ 相同，若有 $d_i$ 不相同无解输出 `NO`。

**但是这样就一定有解吗？**  
<https://www.luogu.com.cn/record/104080286>

答案是不一定。
我们前面说过若 $b_i=0$，说明 $b_i$ 至少减了 $a_i$ 次，所以还要满足所有的 $a_i>d_i$ 否则还是无解，然后就 AC 了。

------------

代码比较简短，如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
int T;
int main(){
    scanf("%d" , &T);
    for(int n , a[N] , b[N]; scanf("%d" , &n) == 1 && T--;){
        for(int i = 1; i <= n; i++) scanf("%d" , &a[i]);
        int d = INT_MAX;//其实d不需要开数组，只需要变量即可
        bool flag = 1;//1为有解，0为无解
        for(int i = 1; i <= n; i++){
            scanf("%d" , &b[i]);
            if(!b[i]) continue;//b[i]为0时跳过
            if(a[i] < b[i]) flag = 0;//d < 0
            if(d == INT_MAX) d = a[i] - b[i];//第一个差
            if(a[i] - b[i] != d) flag = 0;//差不相同
        }
        for(int i = 1; i <= n; i++) if(!b[i]){
            //b[i]为0要保证a[i] > d
            if(a[i] > d) flag = 0;
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：LEle0309 (赞：1)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1690B) or [CF传送门](https://codeforces.com/contest/1690/problem/B)

#### 题目大意：

对 $ a $ 数列里每一个**非零**的数减去 $ 1 $，问减 $ n $ 此能不能变成 $ b $ 数组。

#### 题目分析：

首先，$ a $ 数组中如果有 $ a_i $ 满足 $ a_i<b_i $，因为只能减去 $ 1 $，所以直接输出 `NO`。

然后，我们可以直接求出 $ a $ 与 $ b $ 每一项之差 $ a_i-b_i $，设为 $ d_i $，其中最大值记为 $ max $，易得我们操作了 $ max $ 次。此时因为 $ max $ 是 $ d $ 数组中的最大值，所以其他的数必定也减了 $ max $ 次。所以如果 $ a_i-b_i<max $，则减过后的 $ a_i $ 要么是 $ 0 $，要么比 $ b_i $ 小。而如果 $ b $ 数组满足条件，第二种情况肯定不行，则就只能是第一种情况，可得 $ b_i=0 $。


```cpp
#include<iostream>
using namespace std;
#define INF 0x7f7f7f7f//赋最大值
const int maxn=5e4+7;
int a[maxn],b[maxn],n,t,i,maxm=-INF;
int main()
{
	cin>>t;
	while(t--)//t组数据
	{
		cin>>n;bool flag=0;maxm=-INF;//多测不清空，提交两行泪
		for(i=1;i<=n;i++)cin>>a[i];
		for(i=1;i<=n;i++)cin>>b[i];
		for(i=1;i<=n;i++)if(a[i]<b[i])flag=1;//特判第一种
		for(i=1;i<=n;i++)maxm=max(maxm,a[i]-b[i]);//求最大值
		for(i=1;i<=n;i++)if(a[i]-maxm!=b[i]&&b[i]!=0)flag=1;//判断第二种
		if(flag)cout<<"NO\n";//不可以
		else cout<<"YES\n";//可以
	}
	return 0;//完结撒花！
}
```

---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1690B)

### **[题意解析]**
给出两个序列 $a$ 和 $b$，我们可以对 $a$ 中的每个 $a_i$ 进行一次减 $1$ 的操作，问能否通过这个操作，使序列 $a$ 变成 序列 $b$。

### **[思路分析]**
我们考虑一下在满足什么情况才能把一个 $a_i$ 通过减 $1$ 的操作变成 $b_i$ 呢，$b_i = 0$ 除外。
+ $a_i$ 不能小于于 $b_i$，不然怎么减都不会变成 $b_i$。
+ $a_i$ 减去 $b_i$ 后要与我们的 $a_1$ 减去 $b_1$ 的差相同，这样才不会减出负数。
+ 特殊情况：如果 $b_i$ 是 $0$，$a_i$ 必须小于 $a_1$ 减去 $b_1$ 的差才能减出 $0$。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[100010],nw,b[100010];
bool flag=1;/*是否可行*/
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1; i<=n; i++)cin>>a[i];
		flag=1,nw=2147483647;
		/*nw表示第一个非0的公差*/
		for(int i=1; i<=n; i++)cin>>b[i];
		for(int i=1; i<=n; i++){
			if(b[i]==0)continue;
			/*非0特判，后面处理*/
			if(nw==2147483647)nw=a[i]-b[i];
			/*算出第一个非0的公差*/
			if(a[i]<b[i]||a[i]-b[i]!=nw){flag=0;break;}
			/*不符合条件，直接退出*/
		}
		for(int i=1; i<=n; i++) 
			if(b[i]==0&&a[i]>nw){flag=0;break;}
		/*特判是0的条件，不符合直接退出*/
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
		/*输出是否可以*/
	}
	return 0;
}
```


---

## 作者：legend_cn (赞：0)

# 解题思路
首先， 必须 $a_i \ge b_i$，否则直接无解。

然后要先找到第一个 $b_i \neq 0$ 的位置 $i$。

接着遍历所有的 $a_j$ 与 $b_j$。

如果 $a_j-b_j>(a_i-b_i)$，那么一定减得不够；

如果$a_j-b_j<(a_i-b_i)$， 那么一定减得太多了。

但是当 $b_j=0$ 时，就符合题意了。

# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
int a[N],b[N];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		bool flag=1;
		int maxn=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<b[i])
			{
				flag=0;
				break;
			}
			maxn=max(maxn,a[i]-b[i]);
		}
		if(!flag)
		{
			cout<<"NO\n";
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(max(a[i]-maxn,0)!=b[i])
			{
				flag=0;
				break;
			}
		}
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
```


---

## 作者：lidundun (赞：0)

# Array Decrements
本题暴力枚举就行，可以用 $x$ 存 $b[i]$ 不为零的情况下 $a[i]-b[i]$ 的值，用 $y$ 存 $b[i]$ 的情况下 $a[i]-b[i]$ 的值。

题目要求允许的情况，我们可以反过来，只推出无解的情况就行了。
1. 当 $x<y$ 时，证明减掉 $x$ 次后 $a[i]$ 无法为 $0$，无解。
2. 任意一次 $x$ 赋值后与赋值前不同（不包括赋值前为 $0$ 的情况），证明减的次数不同，无解。
3. 任意情况下 $x<0$，证明 $b[i]>a[i]$，无解。


# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100010],b[100010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x=0,y=0,bj=0,bz=0;
		scanf("%d",&m);
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		for(int j=1;j<=m;j++)  scanf("%d",&a[j]);
		for(int j=1;j<=m;j++)  scanf("%d",&b[j]);
		for(int j=1;j<=m;j++)
		{
			if(b[j]!=0)
			{
				if(bj==0)
				{
					x=a[j]-b[j];
					bj=1;
				}
				if(x<0||x!=a[j]-b[j])
				{
					bz=1;
					break;
				}
			}
			else
			{
				y=max(y,a[j]-b[j]);
			}
		}
		if(!bz&&(x>=y||bj==0))  printf("YES\n");
		else  printf("NO\n");
	}
	return 0;
}
```


---

## 作者：newbeeglass (赞：0)

### 思路：
"定义一次操作为将一个序列中的所有非零整数全都减少 $1$"，因为是所有数都要减 $1$，所以可以考虑一次减完。既然在很多次操作之后会使序列 $a$ 等于 $b$，那么除了 $b_{i}=0$ 的情况以外，所有 $a_{i}$ 减去的数都要相等，因为是所有数一起减的。
### 代码实现：
以一个 $a_{i}-b_{i}$ 作为基准，去判断其他的 $a_{i}-b_{i}$ 是否与之相等，但是如果 $b_{i}=0$，只需判断 $a_{i}-b_{i}$ 是否不超过基准就好了，因为减到 $0$ 了之后，每次操作就无需再减了。另外，有需要注意的地方，以 $a_{i}-b_{i}$ 作为基准必须满足 $b_{i}$ 不为 $0$，否则有可能出现这个基准比真正的基准小的情况，所以又有了一种特殊情况，所有的 $b_{i}$ 都为 $0$ ，这时找不到基准，但是一定输出 ```YES```，因为所有 $a_{i}$ 都可以减到 $0$ 并且不再减下去。
### AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100001],b[100001];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		bool flag=0;
		int temp;
		bool flag2=0;
		for(int i=1;i<=n;i++){
			if(b[i]!=0){
				flag2=1;
				temp=a[i]-b[i];
				break;
			}
		}
		if(!flag2){
			cout<<"YES"<<endl;
			continue;
		}
		if(temp<0){
			cout<<"NO"<<endl;
			continue;
		}
		for(int i=1;i<=n;i++){
			if(b[i]==0){
				if(a[i]-b[i]>temp){
					flag=1;
					break;
				}
			}
			else{
				if(a[i]-b[i]!=temp){
					flag=1;
					break;
				}
			}
		}
		if(flag){
			cout<<"NO"<<endl;
		}
		else{
			cout<<"YES"<<endl;
		}
	}
}

```



---

## 作者：libowei6666 (赞：0)

**题目大意：**

给出两个长度为 $n$ 的序列 $a$ 和 $b$。

定义一次操作为将一个序列中的所有非零整数全都减少 $1$。

要求出能否可以通过对序列 $a$ 进行许多次操作（也可以不做）得到序列 $b$

**题目思路**

可以考虑按照 $a-b$排序，求出最大的 $s=a_i-b_i$，若 $s<0$ 则无解

如果有 $a_i-b_i<s$ ，那么则说明 $a_i$ 不能再减了：如果 $b_i=0$，$0$无法操作，是可以的; 否则 $a_i$ 会一直减下去，就不满足了。

**代码:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int d,a[50005],b[50005],n;
bool f;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		f=1;
		d=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=n;i++)
		{
			cin>>b[i];
			d=max(d,a[i]-b[i]);
		}
		for(int i=1;i<=n;i++)
		{
			if(b[i]>a[i])
			{
				f=0;
				break;
			}
			if(b[i]!=0&&a[i]-b[i]!=d)
			{
				f=0;
				break;
			}
		}
		if(f)
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：qwq___qaq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1690B)

可以考虑按照 $a-b$ 排序，求出最大的 $s=a_i-b_i$，若 $s<0$ 显然无解。

如果有 $a_i-b_i<s$，那么则说明 $a_i$ 不能再减了：如果 $b_i=0$，$0$ 无法操作，是可以的；否则 $a_i$ 会继续减下去，就不满足了。

时间复杂度 $O(n)$。

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
+ 首先如果 $b_i$ 都等于 $0$ 那就简单了，直接输出 `YES` 就完事了，因为任何数都能减到 $0$ 而不出现负数。

+ 还有，$a_i$ 一定不能小于 $b_i$，不然永远也减不到 $b_i$，出现这种情况直接输出 `NO`。

+ 以上是需要特判的，接下来我们先找到第一个 $b_i \neq 0$ 的数并且取出对应的 $a_i$，然后建立标准差 $bz$，$bz \gets a_i - b_i$，接着遍历所有相对应的 $a_i$ 与 $b_i$，如果 $a_i - b_i > bz$，那么一定减不到； 如果 $a_i - b_i < bz$，那么一定减过头了，**但除 $b_i = 0$ 外**，因为即使减到 $0$ 了还可以继续减而不会变成负数，因为题面说过：定义一次操作为将一个序列中的所有**非零整数**全都减少 1。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005], b[200005];
int read() {
  int lll = 0;
  scanf("%d", &lll);
  return lll;
}
int main() {
  t = read();
  while (t--) {
    n = read();
    for (int i = 1; i <= n; i++) {
      a[i] = read();
    }
    bool f0 = 0;
    int bz = 0;
    for (int i = 1; i <= n; i++) {
      b[i] = read();
      if (b[i] != 0) {
        bz = a[i] - b[i];  //设置标准差。
        f0 = 1;
      }
    }
    if (!f0) {
      puts("YES");  //全都是 0。
      continue;
    }
    bool yes_or_no = 1;
    for (int i = 1; i <= n; i++) {
      if (a[i] < b[i]) {
        yes_or_no = 0;
        break;
      }
      if (a[i] - b[i] > bz) {
        yes_or_no = 0;
        break;
      }
      if (a[i] - b[i] < bz && b[i] != 0) {
        yes_or_no = 0;
        break;
      }
    }
    if (yes_or_no) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}
```

---

## 作者：Hooch (赞：0)

### 题目大意

给定两个长度为 $n$ 的非负整数序列 $a$ 和 $b$。求出是否能让 $a$ 中的所有数都减 $1$ 若干次使得 $i\in [1,n]$ 都有 $a_i=b_i$。

**如果有一个 $a_i=0$，那么它将不会再次减少 $1$**。

### 基本思路

这道题我们只需要讨论它的无解情况就行了。每个无解可能都是下面几个情况：

+ 有一个 $a_i<b_i$，由于题目中只能减少，所以无解。

+ 对与所有 $a_i$ 中满足 $a_i\ne 0$ 的 $i$，记一个 $c_i=b_i-a_i$，若有 $c_i\ne c_j$，则无解。

+ 当 $b_i=0$，但是非零的 $b_j$ 的 $c_j$，若 $a_i>c_j$，那么就不能将 $a_i$ 减到 $0$，那么无解。

若以上三种情况全都不是，那么一定有解。

### 代码

代码：

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (register int i(l); i <= r; ++i)
#define rep2(i, l, r) for (register int i(l); i >= r; --i)
using namespace std;
const int inf = 1e9 + 1;
int ans = -inf, p[200005], n, t, q[50005];
inline void solve() {
	ans = -inf;
	cin >> n; rep1(i, 1, n) {
		cin >> p[i];
	} bool flg = 0;
	rep1(i, 1, n) {
		int x; cin >> q[i]; x = q[i];
		if (!x) continue;
		if (ans == (-inf)) ans = p[i] - x; 
		else if (ans != p[i] - x) flg = 1;
	} 
	rep1(i, 1, n) 
		if ((ans != (-inf)) && q[i] == 0 && p[i] > ans) flg = 1;
	if ((ans < 0 || flg) && ans != (-inf)) puts("NO");
	else puts("YES");
}
signed main(void) {
	int t; cin >> t; while (t--) {
		solve();
	}
}
```

---

## 作者：duchengjun (赞：0)

# 题意

给一个数组长度 $n$ 和两个长度为 $n$ 的数组 $a,b$，判断 $a$ 能不能变换到 $b$。

变换规则：

每一次都将所有的 $a[i]$ 减一，减到 0 就不减了。

# 分析

由于减到 0 就不减了，所以 $a[i]$ 降到 $b[i]$ 需要变换 $a[i]-b[i]$ 次，然后将 $a[i]-b[i]$ 的最大值求出来，记作 $ans$。

则若有一次的 $\min(a[i]-ans,0)\ne b[i]$ 就可以输出 ``NO``，否则输出 ``YES``。

# Code

```cpp
#include<bits/stdc++.h>
#define ri register int
#define ll long long
#define ull unsigned long long
using namespace std;
#define getchar() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
namespace get_out
{
    char B[1<<20],*S=B,*T=B;
    char op;
    inline void read_(int &x)
    {
        x=0;
        int fi(1);
        op=getchar();
        while((op<'0'||op>'9')&&op!='-') op=getchar();
        if(op=='-') op=getchar(),fi=-1;
        while(op>='0'&&op<='9') x=(x<<1)+(x<<3)+(op^48),op=getchar();
        x*=fi;
        return;
    }
    inline void read_(long long &x)
    {
        x=0;
        int fi(1);
        op=getchar();
        while((op<'0'||op>'9')&&op!='-') op=getchar();
        if(op=='-') op=getchar(),fi=-1;
        while(op>='0'&&op<='9') x=(x<<1)+(x<<3)+(op^48),op=getchar();
        x*=fi;
        return;
    }
    inline void read_(double &x)
    {
        x=0.0;
        float fi(1.0),sm(0.0);
        op=getchar();
        while((op<'0'||op>'9')&&op!='-') op=getchar();
        if(op=='-') op=getchar(),fi=-1.0;
        while(op>='0'&&op<='9') x=(x*10.0)+(op^48),op=getchar();
        if(op=='.') op=getchar();
        int rtim=0;
        while(op>='0'&&op<='9') sm=(sm*10.0)+(op^48),++rtim,op=getchar();
        while(rtim--) sm/=10.0;
        x+=sm,x*=fi;
        return;
    }
    inline void read_(string &s)
    {
        char c(getchar());
        s="";
        while(!isgraph(c)&&c!=EOF) c=getchar();
        for(;isgraph(c);c=getchar()) s+=c;
    }
    inline void read_(char &c)
    {
        for(c=op;c==' '||c=='\n'||c=='\r'||c=='\t';c=getchar());
        op=c;
    }

    template<typename Head,typename ...Tail>
    inline void read_(Head& h,Tail&... t)
    {read_(h),read_(t...);}

    inline void write_(){}
    inline void postive_write(unsigned x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(unsigned long long x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(int x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(long long x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void postive_write(short x)
    {
        if(x>9) postive_write(x/10);
        putchar(x%10|'0');
    }
    inline void write_(const char* ss) {while(*ss) putchar(*ss++);}
    inline void write_(char c) {putchar(c);}
    inline void write_(string s) {for(unsigned i=0;i<s.size();++i) putchar(s[i]);}
    inline void write_(short x)
    {
        if(x<0) putchar('-'),postive_write(-x);
        else postive_write(x);
    }
    inline void write_(int x)
    {
        if(x<0) x=-x,putchar('-');
        postive_write(x);
    }
    inline void write_(long long x)
    {
        if(x<0) x=-x,putchar('-');
        postive_write(x);
    }
    inline void write_(unsigned x) {postive_write(x);}
    inline void write_(ull x) {postive_write(x);}

    template<typename Head,typename ...Tail>
    inline void write_(Head h,Tail ...t) {write_(h),write_(t...);}
}
using get_out::read_;
using get_out::write_;
const int N=5*1e4+10;
int T;
int n;
int a[N],b[N];
int main(void){
	std::ios::sync_with_stdio(false);
	read_(T);
	while(T--){
		read_(n);
		for(int i=1;i<=n;i++)
			read_(a[i]);
		int ans=0;
		for(int i=1;i<=n;i++){
			read_(b[i]);
			ans=max(ans,a[i]-b[i]);
		}
		bool ok=true;
		for(int i=1;i<=n;i++)
			if(max(a[i]-ans,0)!=b[i]){
				ok=false;
				write_("NO\n");
				break;
			}
		if(ok)write_("YES\n");
	}
	write_("\n");
	return 0;
}

//T2
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

这道题相当简单。

首先，看看有没有某一个位置，使 $b$ 数组大于 $a$ 数组的。如果有，那显然就输出 `NO`，因为 $a$ 数组的每一个数都只能减少不能增加。

然后，看看所有位置上 $b$ 数组与 $a$ 数组的差的最大值，在以下代码中记为 $maxc$。

最后，对于每个位置，都计算 $a$ 数组减去 $maxc$ 的值，然后将这个值和 $0$ 取最大的（因为题目中也有讲，对于每次操作，如果 $a$ 数组的某个位置等于 $0$，那么不对此位置进行操作）。如果这个值不等于 $b$ 数组的对应位置，则输出 `NO`。

如果以上步骤都没有输出 `NO`，那就说明输入数据有解，输出 `YES`。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t;
int n;
int a[50005],b[50005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&b[i]);
		}
		bool flag=true;
		int maxc=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<b[i])
			{
				flag=false;
				break;
			}
			maxc=max(maxc,a[i]-b[i]);
		}
		if(!flag)
		{
			printf("NO\n");
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(max(a[i]-maxc,0)!=b[i])
			{
				flag=false;
				break;
			}
		}
		if(flag)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}

```


---

## 作者：heaksicn (赞：0)

## 1 题意
给定两个长度为 $n$ 的序列 $a$ 和 $b$，每一次操作可以使每一个 $a_i=\max(a_i-1,0)(1\leq i\leq n)$。

求能否可以对 $a$ 进行若干次操作，使得 $a=b$。

## 2 思路
首先我们观察到，对于 $a$ 的操作只减不加，所以当某一个 $b_i>a_i$ 是，必定无解。

然后，对 $b$ 中的每一个数分类讨论：

1. $b_i=0$，此时 $ans$ 应满足 $ans\geq a_i$。

2. $b_i\neq0$，此时 $ans$ 应满足 $ans=a_i-b_i$。

最后判断是否存在一个 $ans$ 满足条件即可。

单次询问时间复杂度 $O(n)$。

## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int t;
int n,a[50001],b[50001];
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		int maxn=-2e9+100;
		for(int i=1;i<=n;i++){
			b[i]=read();
			if(b[i]!=0) maxn=max(maxn,a[i]-b[i]);//找到其中最大的差
		}
		if(maxn==-2e9+100){//所有b[i]都等于0，此时进行inf次操作即可
			cout<<"YES\n";
			continue;
		}
		bool flag=1;
		int dis=maxn;//所求的ans
		for(int i=1;i<=n;i++){
			if(a[i]<b[i]) flag=0;//不能操作
			if(b[i]==0&&a[i]-dis<=0){
				continue; 
			}
			if(a[i]-b[i]!=dis) flag=0;
		}
		if(flag) puts("YES");
		else puts("NO");
	}
	return 0;
}

```


---

## 作者：Coros_Trusds (赞：0)

# 题目分析

+ 如果 $\exists i,b[i]\gt a[i]$，那么无解。

+ 如果所有的 $a[i]-b[i]$ 都相等，那么有解。

+ 否则，找出 $t=\max\{a[i]-b[i]\}$，如果 $a[i]-b[i]\neq t$，那有可能 $a[i]$ 提前停下了，标志就是 $b[i]=0$。所以如果 $\exists i,a[i]-b[i]\neq t,b[i]\neq 0$，那么无解。否则有解。

# 代码

```cpp
// Problem: B. Array Decrements
// Contest: Codeforces - Codeforces Round #797 (Div. 3)
// URL: https://codeforces.com/contest/1690/problem/B?f0a28=1
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Date:2022-06-07 22:55
// 
// Powered by CP Editor (https://cpeditor.org)

#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <cmath>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	inline int read() {
		int ret = 0,f = 0;char ch = getchar();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getchar();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getchar();
		}
		return f ? -ret : ret;
	}
	inline double double_read() {
		long long ret = 0,w = 1,aft = 0,dot = 0,num = 0;
		char ch = getchar();
		while (!isdigit(ch)) {
			if (ch == '-') w = -1;
			ch = getchar();
		}
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot = 1;
			} else if (dot == 0) {
				ret = (ret << 3) + (ret << 1) + ch - 48;
			} else {
				aft = (aft << 3) + (aft << 1) + ch - '0';
				num ++;
			}
			ch = getchar();
		}
		return (pow(0.1,num) * aft + ret) * w;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 5e4 + 5;
int a[N],b[N];
int T,n;
inline void solve() {
	n = read();
	for (register int i = 1;i <= n; ++ i) a[i] = read();
	for (register int i = 1;i <= n; ++ i) b[i] = read();
	for (register int i = 1;i <= n; ++ i) {
		if (b[i] > a[i]) {
			puts("NO");
			return;
		}
	}
	int Max = 0;
	bool mark = true;
	for (register int i = 1;i <= n; ++ i) {
		Max = std::max(Max,a[i] - b[i]);
	}
	for (register int i = 1;i <= n; ++ i) {
		if (Max != a[i] - b[i]) {
			mark = false;
			break;
		}
	}
	if (mark) puts("YES");
	else {
		for (register int i = 1;i <= n; ++ i) {
			if (Max != a[i] - b[i] && b[i] != 0) {
				puts("NO");
				return;
			}
		}
		puts("YES");
	}
}
int main(void) {
	T = read();
	while (T --) {
		solve();
	}
	
	return 0;
}
```

---

