# Mark the Photographer

## 题目描述

Mark is asked to take a group photo of $ 2n $ people. The $ i $ -th person has height $ h_i $ units.

To do so, he ordered these people into two rows, the front row and the back row, each consisting of $ n $ people. However, to ensure that everyone is seen properly, the $ j $ -th person of the back row must be at least $ x $ units taller than the $ j $ -th person of the front row for each $ j $ between $ 1 $ and $ n $ , inclusive.

Help Mark determine if this is possible.

## 说明/提示

In the first test case, one possible order is to have the third, fifth, and sixth person on the back row and the second, first, and fourth on the front row. The heights of the people will look like this.

 Back $ 9 $  $ 12 $  $ 16 $ Front $ 3 $  $ 1 $  $ 10 $ It works because

- $ h_3-h_2 = 9-3 \geq 6 $ ,
- $ h_5-h_1 = 12-1\geq 6 $ , and
- $ h_6-h_4 = 16-10\geq 6 $ .

In the second test case, it can be shown there is no way to order people in a way that satisfies the condition.

In the third test case, the only way to arrange people to satisfy the condition is to have the first person on the back row and the second person on the front row.

## 样例 #1

### 输入

```
3
3 6
1 3 9 10 12 16
3 1
2 5 2 2 2 5
1 2
8 6```

### 输出

```
YES
NO
YES```

# 题解

## 作者：FFTotoro (赞：5)

简单贪心题。贪心结论的证明参考了 CF 官方题解。

首先我们将数组 $h$ 从小到大排序，如果可以安排，那么这个数组一定满足以下条件：

- $\forall 1\le i\le n,h_{i+n}-h_i\ge x$。

为什么是这样的呢？

我们选取一个 $i(1\le i\le n)$，对于区间 $[h_i,h_{i+n}]$，共有 $n+1$ 个身高。这 $n+1$ 个人需要分配到 $n$ 列上去，根据鸽巢原理，必有至少 2 人分到同一列。区间中身高最大的差值显然为 $h_{i+n}-h_i$，为保证可以安排，我们将 $i$ 和 $i+n$ 两人分配在同一列。因为每一列都要满足身高差大于等于 $x$，所以我们只要判断 $h_{i+n}-h_i$ 是否大于等于 $x$ 即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        int n,k; cin>>n>>k;
        vector<int> a(n<<1);
        for(auto &i:a)cin>>i;
        sort(a.begin(),a.end());
        bool flag=true;
        for(int i=0;i<n;i++)
            if(a[i+n]-a[i]<k){flag=false; break;}
        cout<<(flag?"YES\n":"NO\n");
    }
    return 0;
}
```

---

## 作者：MH_SLC (赞：4)

## 题目分析
给出一个 $n$ 和一个 $x$，$x$ 指数列中的差最小值，若差大于 $x$ 则不成立，输出 No。我们读入的是 $2 \times n$ 个数，为了保证每一个 $a_i$ 的差达到最大。

首先我们考虑第 $1$ 矮的人（暗示排序的存在）。我们可以发现，如果第 $n+1$ 矮的人无法与它匹配，那么第 $n+1$ 矮的人必定无法与其它人匹配，所以将第 $1$ 和 $n+1$ 矮的人匹配是最优的，以此类推。

我们可以先从小至大排序一次（记得要排到 $2 \times n$)，然后枚举到 $n$,从 $1$ 开始枚举到 $n$，排序后如果 $h_i$ 与 $h_{n+i}$ 相差不小于 $x$ 则成立，应为我们已经排序了，所以 $h_{i+1}$ 一定大于 $h_i$，$h_{n+i}-h_{i+1}$ 一定小于 $x$。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define MAX 1010	//注意数据范围哦
inline int read() {		//快读，可忽略
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}
int T = read(), n, x, a[MAX];
int main() {
	while (T--) {
		n = read(), x = read();
		for (int i = 1; i <= 2 * n; i++)a[i] = read();
		sort(a + 1, a + 2 * n + 1);//排序时记得要排到 2*n 哦~
		bool flag = 0;
		for (int i = 1; i <= n; i++)
			if (a[n + i] - a[i] < x) flag = 1;//判断的过程，考场上写挂在这了一次，qwq
		if (flag)cout << "No" << endl;
		else cout << "Yes" << endl;
	}
	return 0;
}
```


---

## 作者：Jeremiahy (赞：4)

## 题意

$2n$ 个人拍照，要排成两排，每排 $n$ 人，且每列后面的人要比前面的人高 $x$，询问是否有解。

# 分析

很容易想到一个贪心策略：小的在前，大的在后，并且最矮的人后面是第 $n+1$ 矮的人，以此类推。

证明很容易，因为如果前排有比后排高的，我们就交换一下，答案会更优。对于第二点，如果最矮的人与第 $n+1$ 矮的人身高之差小于 $x$，那比就没人与第 $n+1$ 矮的人配对了（其他更高的人肯定更不可能），所以这样做是正确的。

于是我们可以将 $h$ 数组排序后，依次检查 $h_1$ 与 $h_{n+1}$，$h_2$ 与 $h_{n+2}$，···，$h_n$ 与 $h_{2n}$ 是否满足差大于等于 $x$，若有一个不符合立即判定失败退出。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, x, h[210];
int main () {
	cin >> t;
	while (t--) {
		int is = 1;//每次初始化
		cin >> n >> x;
		for (int i = 1; i <= 2 * n; i++)
			cin >> h[i];
		sort(h + 1, h + 1 + 2 * n);//快速排序
		for (int i = 1; i <= n; i++)
			if (h[i + n] - h[i] < x) {//有不合格的就停止
				cout << "NO\n";
				is = 0;
				break;
			}
		if (is)
			cout << "YES\n";
	}
	return 0;
}
```


---

## 作者：sunkuangzheng (赞：2)

## 题目分析
有 $2n$ 个人，知道他们的身高，要让他们排成两排，问是否存在一种方案使每个后排的人的身高减去前排人的身高都 $ \ge x$ 。

首先如果想让每组身高差都 $ \ge x$ ，一定是要让他们的身高差平均化。因为如果有一组身高差得很大，那么必定就会有一组身高差相应的比较小。

那怎么实现让他们身高差平均化呢？首先给一个结论：将 $2n$ 个数升序排序，然后每次 $a_i$ 在前排， $a_{i+n}$ 在后排，这样就是最优方案。这个的证明放在最后。

也就是说，如果存在这样的方案，必须满足：$h_{i+n} - h_i \ge x$。

那么有了这个结论，就可以写代码了。

## 完整代码
不太想用`sort`排序，所以手写了个归并排序。
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[205];
void msort(int l , int r){//归并排序
    if(r-l > 0){
        int mid = (l+r) / 2 ;
        int i = l; 
        int p = l , q = mid+1;
        msort(l , mid);
        msort(mid+1 , r);     
        while(p<=mid || q<=r){
            if(q>r || (p<=mid && a[p]<=a[q]))
                b[i++] = a[p++];
            else
                b[i++] = a[q++];
        }
        for(i = l ; i <= r; i++){
            a[i] = b[i];
        }
    }
}
int main(){
    int n,x,t;//t是数据组数，n表示一排的人数，x表示要求的身高差
    cin >> t;
    for(int k = 1;k <= t;k ++){
	    bool f = 0;
	    cin >> n >> x;
	    for(int i = 1;i <= 2*n;i ++){
	    	cin >> a[i];
		}
	    msort(1,2*n);
	    for(int i = 1;i <= n;i ++){
	    	if(a[i+n] - a[i] < x){
	    		cout << "NO" << endl;
	    		f = 1;
	    		break;
			}
		}
		if(f == 0){
			cout << "YES" << endl;
		}
	}
	return 0;
}
```
## 证明结论
证明方法参考了CF的官方题解。

因为只有 $n$ 列，所以 $n+1$ 个身高在 $[h_i,h_{i+n}]$ 范围内的人，至少会有两个人被分到同一列。而这个范围内，身高差最大就是 $h_{i+n}-h_i$ ，因此如果方案存在，必须满足 $h_{i+n} - h_i \ge x$ ，原结论得证。

---

## 作者：BetaCutS (赞：0)

引理：如果把 $h$ 从小到大排序后，$h_{i+n}-h_i<x(1\le i\le n)$，那么没有符合要求的摄影排列。

证明：

反证法。如果把 $h$ 从小到大排序后，$h_{i+n}-h_i<x(1\le i\le n)$，那么前排的 $h_i$ 必须要找一个比 $h_{i+n}$ 大的来配对，记为 $h_{j+n}$。而 $h_j$ 又要找比 $h_{j+n}$ 大的配对……直到最后，肯定有人没有能配对的。

所以，代码就很好写了：

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<queue>
#include<string>
#include<vector>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=1e5+10;
const double eps=1e-5;
int read()
{
	char ch=getchar();
	int x=0,f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48,ch=getchar();}
	return x*f;
}
int T,n,m,a[N];
signed main()
{
	T=read();
	while(T--)
	{
		n=read(),m=read();
		for(int i=1;i<=n*2;i++)
			a[i]=read();
		sort(a+1,a+1+n*2);
		int flag=1;
		for(int i=1;i<=n&&flag;i++)
			if(a[i+n]-a[i]<m)
				flag=0;
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}

```


---

## 作者：JustinXiaoJunyang (赞：0)

思路分析：

把 $2n$ 个人排成两排，后排至少比前面的人高 $x$ 个单位长度。先对 $h$ 进行排序，大的 $n$ 个一定在后排，小的就在前排。那么只需要让 $a_{n+i}$ 站在 $a_i$ 后面就可以了。想一想：将后排的 $a_{n+i}$ 和 $a_{n+j}$ 换过来，那么原来的两对差换过来后，两对数最小值小了，还是原来的方案聚划算。

参考代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[10005];

int main()
{
    int t;
    cin >> t;
	while (t--)
	{
		bool flag = false;
		int n, x;
		cin >> n >> x;
		for (int i = 1; i <= 2 * n; i++) cin >> a[i];
		sort (a + 1, a + 2 * n + 1);
		for (int i = 1; i<= n; i++)
		{
			if (a[n + i] - a[i] < x)
			{
			    cout << "NO" << endl;
			    flag = true;
			    break;
			}
		}
		if (flag == true) continue;
		cout << "YES" << endl;
	}
	return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1ud4y1Q7f5)

### 2 思路

我们可以发现，将它们按照身高排序，然后前面放最矮的 $n$ 个人，后面放最高的 $n$ 个人，一定是最好的。

并且，第 $i(1\le i\le n)$ 矮的人要和第 $n+i$ 矮的人搭配。

为什么呢？

首先我们考虑第 $1$ 矮的人。我们可以发现，如果第 $n+1$ 矮的人无法与它匹配，那么第 $n+1$ 矮的人必定无法与其它人匹配，所以将第 $1$ 和 $n+1$ 矮的人匹配是最好的。

同样的道理，如果第 $2$ 矮的人无法与第 $n+2$ 矮的人匹配，那么第 $n+2$ 矮的人必定无法与除第 $1$ 矮的人外的剩下人匹配，所以将第 $2$ 和 $n+2$ 矮的人匹配是最好的。

以此类推。

模拟一遍后，如果还是无法满足要求，就肯定无解。

### 3 代码与记录

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define max_n 200
int t;
int n;
int x;
int a[max_n+2];
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1705A_1.in","r",stdin);
	freopen("CF1705A_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&x);
		for(int i=1;i<=(n<<1);++i)scanf("%d",a+i);
		sort(a+1,a+(n<<1)+1);
		ans=true;
		for(int i=1;i<=n;++i){
			if(a[i+n]-a[i]<x){
				ans=false;
				break;
			}
		}
		if(ans)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```

[记录传送门](https://www.luogu.com.cn/record/80111556)

By **dengziyue**

---

## 作者：zhicheng (赞：0)

### 思路

简单的结论题

先说结论：排序后如果 $h_i$ 与 $h_{n+i}$ $(1 \leq i \leq n)$ 相差不小于 $x$，那么就可行。

证明：对于一个 $h_i$ $(1 \leq i \leq n)$，如果 $h_{n+i}-h_i < x$，那它只能和后面的某一个数（假设是 $h_{n+i+j}$ 配对）。因为我们已经排好序了，$h_{i+1}$ 一定比 $h_{i}$ 大，$h_{n+i}-h_{i+1}$ 也一定小于 $x$。所以对于 $k \in [n+i,n+i+j)$，就没有一个数能和 $h_k$ 配对了，因此就不行。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[110];
int main(){
	int n,a,x,o;
	scanf("%d",&n);
	while(n--){
		o=0;
		scanf("%d%d",&a,&x);
		for(int i=1;i<=2*a;i++){
			scanf("%d",&p[i]);
		}
		a*=2;
		sort(p+1,p+a+1);  //先排序
		for(int i=1;i<=a/2;i++){
			if(p[i]+x>p[i+a/2]){  //不符合条件
				o=1;
				printf("NO\n");
				break;
			}
		}
		if(o==0){  //符合条件
			printf("YES\n");
		}
	}
}
```

---

## 作者：_lfxxx_ (赞：0)

### 题意：
Mark 要给 $2n$ 个人拍照，第 $i$ 个人的身高为 $h_i$，问有没有一种划分方式，使得后排 $n$ 个人比前排的对应的 $n$ 个人至少高 $x$。即对于所有的 $i$，都有 $h_{i+n}-h_i\ge x$。
### 思路：
一个很容易想到的贪心，先按从小到大给 $h$ 排序，然后 $1$ 对应 $n+1$，$2$ 对应 $n+2$ 等等。

那为什么这个贪心可以呢？我们假设这个贪心不满足题意，且 $h_{i+n}-h_i<x$。如果要找到更优的，显然要把这两个其中的一个与其他交换。

不妨交换 $h_i$ 和 $h_j$。

如果 $j>n$，那么 $h_i<h_j$ 且 $h_i<h_{j-n}$，不符合。

如果 $j<i$，因为刚开始 $h_{i+n}-h_i<x$，且 $h_{j+n}<h_{i+n}$，那么 $h_{j+n}-h_i<x$，不符合。

如果 $j>i$，因为刚开始 $h_{i+n}-h_i<x$，且 $h_i<h_j$，那么 $h_{i+n}-h_j<x$，不符合。

所以找不到更优的，即原方案为最优方案。

代码很简单我就不贴了。

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

我们需要把 $2n$ 个人排成两排，后排至少比他前面的人高 $x$ 个单位长度。

首先我们先对整个 $h$ 进行排序，较大的 $n$ 个一定在后排，较小的在前排。那么只需要将 $a_{i+n}$ 放在 $a_i$ 后面即可（$i\le n$）

证明：如果我们将后排的 $a_{i+n}$ 与 $a_{j+n}$ 互换，那么原来的两对差值 $a_{i+n}-a_i$ 和 $a_{j+n}-a_j$ 就变成了 $a_{i+n}-a_j$ 和 $a_{j+n}-a_i$。两对数的最小值变小了，所以肯定不优。（希望都大于等于 $x$，所以只考虑最小值）

PS.这里没有采用 editorial 的方法，只代表个人思路（其实差不太多）。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,x,f=0;
ll a[10005];
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		f=0;
		scanf("%lld%lld",&n,&x);
		for(int i=1;i<=2*n;i++)scanf("%lld",&a[i]);
		sort(a+1,a+2*n+1);
		for(int i=1;i<=n;i++)
		{
			if(a[i+n]-a[i]<x){printf("NO\n");f=1;break;}
		}
		if(f==1)continue;
		printf("YES\n");
	}
	return 0;
}
```
谢谢大家观看，祝大家 CF 上大分！

---

