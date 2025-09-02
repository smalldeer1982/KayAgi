# Interview

## 题目描述

This is an interactive problem. If you are unsure how interactive problems work, then it is recommended to read [the guide for participants](https://codeforces.com/blog/entry/45307).

Before the last stage of the exam, the director conducted an interview. He gave Gon $ n $ piles of stones, the $ i $ -th pile having $ a_i $ stones.

Each stone is identical and weighs $ 1 $ grams, except for one special stone that is part of an unknown pile and weighs $ 2 $ grams.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1807E/47dd63211ca258927e8a8d0a66d052f86ba7c589.png) A picture of the first test case. Pile $ 2 $ has the special stone. The piles have weights of $ 1,3,3,4,5 $ , respectively.Gon can only ask the director questions of one kind: he can choose $ k $ piles, and the director will tell him the total weight of the piles chosen. More formally, Gon can choose an integer $ k $ ( $ 1 \leq k \leq n $ ) and $ k $ unique piles $ p_1, p_2, \dots, p_k $ ( $ 1 \leq p_i \leq n $ ), and the director will return the total weight $ m_{p_1} + m_{p_2} + \dots + m_{p_k} $ , where $ m_i $ denotes the weight of pile $ i $ .

Gon is tasked with finding the pile that contains the special stone. However, the director is busy. Help Gon find this pile in at most $ \mathbf{30} $ queries.

## 说明/提示

In the first test case, the stone with weight two is located in pile $ 2 $ , as shown in the picture. We perform the following interaction:

- $ \texttt{? 4 1 2 3 4} $ — ask the total weight of piles $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ . The total weight we receive back is $ 1+3+3+4=11 $ .
- $ \texttt{? 2 2 3} $ — ask the total weight of piles $ 2 $ and $ 3 $ . The total weight we receive back is $ 3+3=6 $ .
- $ \texttt{? 1 2} $ — ask the total weight of pile $ 2 $ . The total weight we receive back is $ 3 $ .
- $ \texttt{! 2} $ — we have figured out that pile $ 2 $ contains the special stone, so we output it and move on to the next test case.

In the second test case, the stone with weight two is located on index $ 7 $ . We perform the following interaction:

- $ \texttt{? 4 2 3 5 6} $ — ask the total weight of piles $ 2 $ , $ 3 $ , $ 5 $ , and $ 6 $ . The total weight we receive back is $ 2+3+3+4=12 $ .
- $ \texttt{? 2 1 4} $ — ask the total weight of piles $ 1 $ and $ 4 $ . The total weight we receive back is $ 1+5=6 $ .
- $ \texttt{! 7} $ — we have somehow figured out that pile $ 7 $ contains the special stone, so we output it and end the interaction.

## 样例 #1

### 输入

```
2
5
1 2 3 4 5

11

6

3

7
1 2 3 5 3 4 2

12

6```

### 输出

```
? 4 1 2 3 4

? 2 2 3

? 1 2

! 2

? 4 2 3 5 6

? 2 1 4

! 7```

# 题解

## 作者：Larryyu (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1807E)
## _Description_
```director``` 有 $n$ 堆石头，其中 $n-1$ 堆都只有重量为一克的石头，剩下一堆有则有一块有两克的石头和若干重量为一克的石头。

你的任务是在 $30$ 次询问内推理出那一堆有重量为两克的石头是第几堆。

首先输入 $n$，接下来输入 $n$ 个数 $a_1,a_2\dots a_n$，其中 $a_i$ 表示第 $i$ 堆有 $a_i$ 块石头。

一共有 $t$ 组数据。

每次询问你需要输出 ```?``` 这个符号，然后输出 $k$ 及  $p_1,p_2\dots p_k$（用空格隔开），表示询问 $p_1,p_2\dots p_k$ 这 $k$ 堆石头的总重量，然后你需要输入一个数 $x$ 表示你刚刚询问得到的答案。

如果你推理出来答案，输出 ```!``` 这个符号以及你得到的答案 $m$。

如果你的询问次数大于 $30$ 次，或有非法的询问，将会得到 ```Wrong Answer``` 评测结果。

记得每次输出后，都要输出一行代码来刷新缓冲区，否则会得到 ```Idleness limit exceeded``` 评测结果或其他评测结果。
- 对于 ```C++```，输出 ```fflush(stdout)``` 或 ```cout.flush()```
- 对于 ```Java```，输出 ```System.out.flush()```
- 对于 ```Pascal```，输出 ```flush(output)```
- 对于 ```Python```，输出 ```stdout.flush()```
## _Soluton_
我们可以考虑运用二分的思想，每次选目标区间的前二分之一去询问，最多需要 $\log_2 n$ 次，在给定范围内一定小于 $30$。

判断方法，若当前得到了第 $l$ 到 $r$ 堆的总重量，如果得到的答案等于 $sum_r-sum_{l-1}$，则目标堆不在这一区间内，否则反之，其中 $sum_i=a_1+a_2+\dots+a_i$。

具体步骤见代码。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
ll sum[200200];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read();
	sum[0]=0;
	for(int i=1;i<=n;i++){
		int x=read();
		sum[i]=0;
		sum[i]=sum[i-1]+x; //预处理求前缀和
	}
	int l=1,r=n;
	while(l<r){ //还没确定到具体堆的编号
		int mid=l+r>>1;
		cout<<"? "<<mid-l+1;
		for(int i=l;i<=mid;i++){ //取前二分之一
			cout<<" "<<i;
		}
		cout<<endl;
		fflush(stdout);
		int get=read();
		if(sum[mid]-sum[l-1]!=get){ //如果匹配不上说明目标堆在前半部分
			r=mid;
		}else l=mid+1; //否则在后半部分
	}
	cout<<"! "<<r<<endl;
	fflush(stdout); //记得刷新缓冲区
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：arrow_king (赞：1)

## 思路

一道交互题，也是二分板子题。

考虑正常情况下如何确定哪一堆石子中有质量不同的。直接在前缀和数组上二分就行了。

现在我不知道前缀和数组，但是可以交互。

直接利用二分的思路，如果返回的值不等于区间 $a_l,a_{l+1},\dots,a_r$ 的和，那么说明 2g 的石子在这个区间中；反之则查找右半区间。

询问的次数是 $\mathcal O(\log n)$ 级的，$30$ 次显然没问题。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t;
int n,a[200005],sum[200005];
int main() {
	t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
			sum[i]=sum[i-1]+a[i];    //预处理前缀和数组
		}
		int l=1,r=n;
		while(l<r) {
			int mid=(l+r)>>1;
			printf("? %d ",mid-l+1);
			fflush(stdout);
			for(int i=l;i<=mid;i++) {
				printf("%d ",i);
				fflush(stdout);
			}
			putchar('\n');
			fflush(stdout);
			int tmp=read();
			if(tmp!=sum[mid]-sum[l-1]) {
				r=mid;
			}
			else l=mid+1;
		}
		printf("! %d\n",l);
		fflush(stdout);
	}
	return 0;
}

```

---

## 作者：_299817_ (赞：1)

## Part 1: 前言

这是一道交互题

## Part 2: 题意简述

你现在有 $n$ 个石头堆，每个石头堆里有 $a_i$ 个石头，在这些石头中，只有一个石头的重量为 $2$，剩余的石头的重量都是 $1$，现在给你至多 $30$ 次询问的机会，请找出哪个石头的重量为 $2$。

对于每次询问，你可以询问第 $l$ 到 $r$ 堆石头的重量之和。

## Part 3: 思路

数据是 $2 \times 10^5$ 的级别的，然后最多询问 $30$ 次，这也就意味着我们可在 $\log_2n$ 次询问内解决这道题。

那么既然是 $\log_2n$ 次，我们就能想到二分查找。

那具体怎么查找呢？

我们只需要询问区间内一半的石头的重量，如果重量等于石头的数量，那么就说明重量为 $2$ 的石头就在另外一半的石头里面，否则就在这一半的石头里面。

对于任意一个区间的石头个数，我们就可以用前缀和解决。

## Part 4: 代码

~~蚂蜂比较奇怪，轻喷。~~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#define sort stable_sort
#define map unordered_map
#define ff fflush // 清空缓冲区，交互题的基本操作。
using namespace std;
typedef long long ll;

int T;
int n;
int a[200010];
int sum[200010];
int l, r, mid;

bool check(int le, int ri){ // 询问
    cout << "? " << ri - le + 1 << " ";
    for(int i = le; i <= ri; i++){
        cout << i << " ";
    }
    cout << endl;
    int k;
    cin >> k;
    if(sum[ri] - sum[le - 1] == k){ // 重量等于石头的数量，重量为2的石头在另外一半里面。
        return 1; // 返回1
    }else{ // 否则重量为2的石头就在这一半里面。
        return 0; // 返回0
    }
}

int main(){
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        } // 输入
        for(int i = 1; i <= n; i++){
            sum[i] = sum[i - 1] + a[i];
        } // 前缀和
        l = 1;
        r = n;
        while(l < r){ // 二分查找
            int mid = (l + r) >> 1;
            if(check(l, mid) == 0){ // 如果重量为2的石头在l到mid这个区间里面。
                r = mid; // 缩小查找范围
            }else{ // 如果重量为2的石头在mid+1到r这个区间里面。
                l = mid + 1; // 缩小查找范围
            }
        }
        cout << "! " << l << endl; // 找到了就输出
    }
    return 0;
}

```

---

## 作者：hereiszd (赞：1)

## 一.题意简述
**交互题**，现在有 $n$ 堆石子 ($n\le 2 \times 10^5$)，每堆石子有 $a_i$ 个，每个石子的重量为 $1$ ，但是现在有一堆石子中的一个质量为 $2$，现在你可以询问最多 $30$ 个问题，每次询问任意 $i$ 堆石子的重量，找出这堆石头。
## 二.题目分析
看到交互想二分，发现二分的话 $30$ 次绰绰有余，这鼓励我们继续往后想。

考虑二分区间，问题便转化为快速判定区间 $[l,r]$ 是否含有特殊的石子。

这很简单，记录前缀和看看这个区间和是不是询问的和，如果多 $1$ 就是在区间里，否则就是不在。

这样一个二分就可以解决了。

## 三.代码实现
注意开 `long long`。

```cpp
/*
	Author:zd
	Status:Accept
	note: 省去了缺省源，别忘了开 long long
*/

#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define OK cerr<<"OK"<<endl;
#define INF 0x7f7f7f7f
#define LINF 0x7f7f7f7f7f7f7f7f
#define int long long
//#define lc x*2
//#define rc x*2+1
#define mid (((l)+(r))/2)
const int mod=998244353;//1e9+7;

int n,m,k,a[N];

signed main(){
	mul();
	return 0;
}

//数组开大了没有 ？开不开 long long ？多测清空了吗 ？

int ask(int l,int r){
	printf("? %lld ",r-l+1);
	for(int i=l;i<=r;i++)printf("%lld ",i);
	puts("");
	fflush(stdout);
	int x;
	scanf("%lld",&x);
	return x;
}
void zd::solve(){
	read(n);
	int ans=0,fl=1;
	for(int i=1;i<=n;i++){
		read(a[i]);
		a[i]+=a[i-1];
	}
	int l=1,r=n;
	while(l<r){
		if(ask(l,mid)!=a[mid]-a[l-1]) r=mid;
		else l=mid+1;
	}
	printf("! %lld\n",l);
	fflush(stdout);
}

```

---

## 作者：云裳 (赞：0)

**方便起见，把含有特殊的石子的石堆称作“特殊的石堆”。**

**思路**

看过这种故事的人都知道，正解是二分。

设现在二分的左端点是 $l$，右端点是 $r(l\le r)$，每次询问 $a_l,a_{l+1},\cdots,a_\frac{l+r}{2}$ 有没有特殊的石堆。

- 如果有，就把这段区间劈成两段，查找左边一段。即， $r\gets \frac{l+r}{2}-1$。

- 如果没有，就查询这段区间的右边区间。即 $l\gets\frac{l+r}{2}+1$。

到最后 $l$ 会等于 $r$，答案也就是 $l$ 了。

那我们考虑如何判断任意一段区间 $a_x,a_{x+1},\cdots,a_y$ 里有没有特殊的石堆。根据定义，如果特殊的石堆是第 $k$ 堆，那它的重量是 $a_k+1$。同样，如果区间 $a_x,a_{x+1},\cdots,a_y$ 里有特殊的石堆，那它的重量应为 $1+\sum\limits_{i=x}^{y} a_i$。因此问题转换成了如何 $O(1)$ 求一段区间的和。显然，可以使用前缀和完成。

至此，这道题就做完了。

**代码**

```cpp
void solve() {
		int t;
		cin>>t;
		while(t--) {
			int a[200007];
        int pre[200007];//前缀和
			int n;
			cin>>n;
			for(int i=1;i<=n;i++) cin>>a[i],pre[i]=pre[i-1]+a[i];
			int l=1,r=n;
			while(l<=r) {//二分
				ll mid=(l+r)>>1;
				cout<<"? "<<mid-l+1<<" ";
				up(i,l,mid) cout<<i<<" ";//询问
				cout<<endl;
				ll x;
				cin>>x;
				if(x==(pre[mid]-pre[l-1])) l=mid+1;
				else r=mid-1;
			}
			cout<<"! "<<l<<endl;
		}
	}
```


---

## 作者：ダ月 (赞：0)

### 题意概要：

交互题。每组数据给你 $n$ 堆石子，每堆石头有 $a_i$ 个。其中某一块石子质量为 $2$，其余为 $1$。现在你和系统交互，你可以以 `? k p1 p2 p3 …… pk` 的方式询问，表示提问对于 $p_1,p_2,p_3,\dots,p_k$ 这几堆石头的质量和。最后要以 `! x` 的方式回答，回答质量为 $2$ 的石头所在堆的位置。最多询问 $30$ 次。

### 题目分析：

显然，对于每次询问，系统返回一个质量 $x$，若 $\sum_{i=1}^ka_{p_i}=x$，说明这个质量为 $2$ 的石头不在所询问的堆里面；否则，是在所询问的堆里面。

我们可以二分询问，若当前还剩下 $l$ 到 $r$ 区间内的石头未知，我们就询问 $l$ 到 $\left\lfloor\frac{l+r}{2}\right\rfloor$ 区间内的石头。若不存在，则说明质量为 $2$ 石头在 $\left\lfloor\frac{l+r}{2}\right\rfloor$ 到 $r$ 的区间内。直到只剩下一堆石头未定，显然，我们需要的石头就在这一堆里面。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
const int N=2e5+10;
int a[N];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		vector<int> v;
		for(int i=1;i<=n;i++)v.push_back(i);
		while(v.size()!=1){
			int mid=v.size()>>1;
			vector<int> o,e;
			for(int i=0;i<mid;i++)o.push_back(v[i]);
			for(int i=mid;i<v.size();i++)e.push_back(v[i]);
			printf("? %d ",o.size());
			for(auto x:o)printf("%d ",x);printf("\n");fflush(stdout);
			int w;scanf("%d",&w);int sum=0;
			for(auto x:o) sum+=a[x];v.clear();
			if(w!=sum)for(auto x:o)v.push_back(x);
			else for(auto x:e)v.push_back(x);
		}printf("! %d\n",v[0]);fflush(stdout);
	}
	return 0;
} 
```

时间复杂度：$O(Tn\log n)$。

别忘记 `fflush`。


---

## 作者：aCssen (赞：0)

[A](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807a)|[B](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807b)|[C](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807c)|[D](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807d)|[E](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807e)|[F](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807f)|[G1](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807g1-post)|[G2](https://www.luogu.com.cn/blog/534296/ti-xie-cf1807g2-post)

### Solution
首先，如果询问 $p_1,p_2,...,p_k$ 中含有特殊的一堆，则它的和应该大于 $\sum_{i=1}^k a_{p_i}$，这将是判断的依据。

同时发现询问次数很小，应该是 $\log n$ 级别的。

有两种做法，时间复杂度均为 $\mathcal{O}(n \log n)$。

**做法一**：

官方做法。

使用一个类似于二分的做法，初始时令 $l=1,r=n$，每次询问令  
 $mid=\frac{l+r}{2}$，询问区间 $[l,mid]$，如果含有特殊的一堆，则答案在 $[l,mid]$ 之间，可以缩小区间为 $[l,mid]$，否则，可以将区间缩小为 $[mid+1,r]$。

**做法二**

二进制分解。

考虑将答案转为二进制，如果其从低到高第 $k$ 为 $1$，则 $1 \sim n$ 中所有第 $k$ 位为 $1$ 的数中，一定包含了答案，反之亦然，即若 $1 \sim n$ 二进制第 $k$ 位为 $1$ 的数中包含特殊的一堆，则答案的第 $k$ 位也一定为 $1$。

所以，我们从 $0$ 到 $\log n$ 枚举 $k$，每次询问所有第 $k$ 位为 $1$ 的数，如果含有特殊的一堆，则令答案加上 $2^k$ 即可。

### 细节

+ 做法一中询问的长度为 $mid-l+1$。
+ 做法二可以使用位运算。
+ 注意输出格式。
+ 可以用 `endl` 刷新缓冲区。
### 代码

做法一：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=2e5+5;
int a[maxn],n;
bool check(int l,int len){
	int sum=0,ans;
	cout<<"? "<<len-l+1<<' ';
	for(int i=l;i<=len;i++){
		cout<<i<<' ';
		sum+=a[i];
	}
	cout<<endl;
	cin>>ans;
	return ans>sum;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int l=1,r=n;
	while(l<r){
		int mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<"! "<<l<<endl;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

做法二：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
const int MOD=998244353;
int n,a[maxn];
void solve(){
    int ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=0;(1<<i)<=n;i++){
        int cnt=0,val=0,x;
        cout<<'?';
        for(int j=1;j<=n;j++)
            if(j&(1<<i)) val++;
        cout<<' '<<val;
        for(int j=1;j<=n;j++){
            if(j&(1<<i)){
                cout<<' '<<j;
                cnt+=a[j];
            }
        }
        cout<<endl;
        cin>>x;
        if(x==cnt+1) ans+=(1<<i);
    }
    cout<<"! "<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
```

---

