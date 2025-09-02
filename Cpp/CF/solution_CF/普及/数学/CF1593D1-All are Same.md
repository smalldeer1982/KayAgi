# All are Same

## 题目描述

给定一个包含 $n$（$n$ 是偶数）个整数的数列 $a_1,a_2,\ldots,a_n$。

考虑一个可能的**正整数** $k$，在每次操作中，你可以选定一个 $i$，并将 $a_i$ 减少 $k$。

你可以执行任意多次（也可能是零次）操作，使这个数列中的**每一个数**都相等。

请找出最大的符合条件的 $k$，如果 $k$ 可以是任意的大小，输出 $-1$。

## 说明/提示

- $1 \le t \le 10$；
- $4 \le n \le 40$；
- $-10^6 \le a_i \le 10^6$。

保证 $\sum\limits{n} \le 100$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
3
6
1 5 3 1 1 5
8
-1 0 1 -1 0 1 -1 0
4
100 -1000 -1000 -1000```

### 输出

```
2
1
1100```

# 题解

## 作者：sijiajun (赞：6)

[CodeForces  CF1593D1 All are Same](https://www.luogu.com.cn/problem/CF1593D1) 题解

**题目描述：**

给定一个包含 $n$($n$ 是偶数）个整数的数列 $a_1,a_2,\ldots,a_n$。

考虑一个可能的**正整数** $k$，在每次操作中，你可以选定一个 $i$，并将 $a_i$  减少 $k$。

你可以执行任意多次（也可能是零次）操作，使这个数列中的**每一个数**都相等。

请找出最大的符合条件的 $k$，如果 $k$ 可以是任意的大小，输出 $-1$。

**输入格式：**

本题包含多组数据。

输入的第一行包含一个正整数 $t$，表示数据组数。

每组数据包含两行，其中第一行包含一个偶数 $n$，第二行包含 $n$ 个整数  $a_1,a_2,\ldots,a_n$。

**输出格式：**

对于每组数据，输出一个正整数 $k$ 或 $-1$，表示答案。

**数据范围：**

- $1 \le t \le 10$；
- $4 \le n \le 40$；
- $-10^6 \le a_i \le 10^6$。

保证 $\sum\limits{n} \le 100$。
### 样例输入 #1

```
3
6
1 5 3 1 1 5
8
-1 0 1 -1 0 1 -1 0
4
100 -1000 -1000 -1000
```

### 样例输出 #1

```
2
1
1100
```

总结：

其实就是对于数列 $a$，并给定一个数字 $ i ( 1 \le i \le n )$，每次可以将  $a_i$ 减去 $k$，最终使

 $a = { a_1,a_2,a_3,\ldots,a_n }$ 都相等，求出 $\max\{k\}$。

当看到将 $a$ 中的每一个元素都减去 $k$ 时，就应当想到要使用最大公因数来求解这道题，先将结果——$ans$ 初始化为第一个和第二个的差，再每次与第 $a_i - a_j$(由于 $\LaTeX$ 我还用的不怎么熟练，就设 $j=i-1$）个进行取 $\gcd$，当 $ans = 0$ 时，就代表 $k$ 可以是任意的大小，输出 $-1$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define sort(a,b) stable_sort(a,b)
const int inf=0x3f3f3f3f;
using namespace std;
int a[50],n,T;
signed main(){
	std::ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int ans=a[2]-a[1];
        for(int i=3;i<=n;i++)ans=__gcd(ans,a[i]-a[i - 1]);
        ans=abs(ans);
        if(!ans)ans--;
        cout<<ans<<endl;
	}
	return 0;
}
```

~~管理员辛苦了，求过~~

---

## 作者：little_cindy (赞：3)

## 题意简述
$t$ 组数据。

对于每组数据，包含一个数 $n$，和 $n$ 个数 $a_i(1\le i\le n)$。

请求出最大一个数 $k$，使得 $a_i$ 进行任意次操作后变为一个数。
## 思路
这一题只需要先去重，去重之后取这些数两两之差的绝对值的最大公因数即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
#define inl inline
#define base 1000001
#define Ofast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
bool vis[2000005];
int a[45],tot,n,t,ans;
int main() {
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=tot;i++){
			vis[a[i]+base]=0;
		}
		tot=0;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			if(!vis[x+base]){
				vis[x+base]=1;
				a[++tot]=x;
			}
		}
		if(tot==1){
			cout<<"-1\n";
			continue;
		}
		ans=abs(a[1]-a[2]);
		for(int i=1;i<=tot;i++){
			for(int j=i+1;j<=tot;j++){
				ans=__gcd(ans,abs(a[i]-a[j]));
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：naroto2022 (赞：2)

# CF1593D1题解
### 题意
把题意转换一下就可以得到：给定一个数列 $a_1,a_2,a_3,\cdots,a_n$，要求一个数列 $b$（$b$ 中的数为非负整数）和一个正整数 $k$，使得 $a[1]-b[1]\times k=a[2]-b[2]\times k=\cdots=a[n]-b[n]\times k$。若有无数多个 $k$，请输出 $-1$。（有多组数据）
### 思路
首先直接讲解法：将数组去重并判断是否有无数多个 $k$ 之后再两两作差求最大公因数即可。那么就有以下解释：

1. 咋去重？答：建立一个 $vis$ 数组和 $a$ 数组，$vis$ 数组为判断一个数是否已经出现过，$a$ 数组为去重之后的数组，如果一个数没有出现过，就录入到数组 $a$ 中。
2. 咋判断有无数多个 $k$？答：在去重的时候，用一个 $len$ 记录去重之后的数组长度，如果为 $1$，也就是去重以前所有数都相同，所以 $k$ 为任意数，输出 $-1$。 
3. 为啥用两两相减求最大公因数？接下来我就来证明。

证明：

 $\because a_i-b_i\times k=a_j-b_j\times k$

 $\therefore a_i-a_j=k\times(b_i-b_j)$

 $\therefore a_i\equiv a_j\pmod k$

 $\therefore a_1\equiv a_2\equiv a_3\equiv\cdots\equiv a_n\pmod k$

 $\therefore$ 只要两两作差求最大公因数即可。

### 总结
1. 多组数据。
2. 换行。
3. 两两作差求最大公因数。
4. 去重。
5. 特判。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int T;
int n,a[45],ans,cnt,len;
bool vis[2000005];
//a数组为去重之后的数组 
//cnt为临时变量。
//len为去重之后的数组长度。
//vis数组是一个数字是否出现过的统计数组，去重要用。 
int gcd(int a, int b){//求最大公因数 
	if(b==0) return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(vis,0,sizeof(vis));//一定要重置。 
		len=0;
		for(int i=1; i<=n; i++){
			scanf("%d",&cnt);
			if(vis[cnt+1000001]==0){//以前这个数没出现过（这个数是新的）。 
				vis[cnt+1000001]=1;//标记为出现过（旧的）。 
				a[++len]=cnt;//录入a数组 
			}
		}
		if(len==1){//去重之后只有1个数，也就是去重以前所有数都相同，所以k为任意数，输出-1。 
			printf("-1\n");//别忘了换行 
			continue;
		} 
		ans=abs(a[2]-a[1]);//取绝对值
		for(int i=2; i<len; i++)
			for(int j=i+1; j<=len; j++)
				ans=gcd(ans,abs(a[j]-a[i]));
		printf("%d\n",ans);
	}
	return 0;
} 
```
### 附（选看）
#### 怎么求最大公因数
方法 $1$：用唯一分解定理，先分解质因数，然后求最大公因数。

令 $a=p_1^{a_1}\times p_2^{a_2}\times p_3^{a_3}\times \cdots p_m^{a_m}$，$b=p_1^{b_1}\times p_2^{b_2}\times p_3^{b_3}\times \cdots p_m^{b_m}$。

则 $\gcd(a,b)=p_1^{\min(a_1,b_1)}\times p_2^{\min(a_2,b_2)}\times p_2^{\min(a_2,b_2)}\times\cdots p_m^{\min(a_m,b_m)}$。

方法 $2$：九章算术 $\bullet$ 更相减损术。

 $\forall a,b\in \mathbb{N}$，$b\le a$，有 $\gcd(a,b)=\gcd(b,a-b)=\gcd(a,a-b)$。

 $\forall a,b\in \mathbb{N}$，有 $\gcd(2a,2b)=2\gcd(a,b)$。

证明：

对于 $a$，$b$ 的任意公约数 $d$，因为 $d\vert a$，$d\vert b$，所以 $d\vert (a-b)$。因此，$d$ 为 $b$，$(a-b)$ 的公约数。反之亦成立。

方法 $3$：欧几里得算法。

 $\forall a,b\in \mathbb{N}$，$b\neq0$，$\gcd(a,b)=\gcd(b,a\bmod b)$。

证明：

若 $a<b$，则 $\gcd(b,a\bmod b)=\gcd(a,b)$，命题成立。

若 $a\geq b$，设 $a=q\times b+r$，其中 $0\le r<b$。显然 $r=a\bmod b$。对于 $a$，$b$ 的任意公约数 $d$，因为 $d\vert a$，$d\vert q\times b$，所以 $d\vert (a-qb)$。即 $d\vert r$，因此，$d$ 为 $b$，$r$ 的公约数。反之亦成立。所以他们的最大公因数相等。

代码实现：
```cpp
int gcd(int a, int b){ 
	if(b==0) return a;
	return gcd(b,a%b);
}
```

---

## 作者：智子 (赞：2)

## 题意

输入 $n$ 个数 $a_1,a_2,...a_n$，每次操作可以将一个数减小 $k$，若干次操作后所有的数的值全部相同，求 $k$ 的最大值。如果 $k$ 可以任意大，输出 $-1$。

## 思路

将一个数 $a$ 不断减去相同的数 $k$ 之后，变为另一个数 $b$ ，$k$ 显然是 $|b - a|$ 的约数，拓展到 $n$ 个数后同样成立。

所以题目中所求的 $k$ 就是 $\gcd(a_1 - a_2, a_2 - a_3, a_3 - a_4,... a_{n - 1} - a_n)$，即对差分求最大公约数。

## 代码

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

const int MAXN = 40 + 5;

int a[MAXN];
int n;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int T;

    cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        for(int i = 2; i <= n; i++) {
            ans = gcd(ans, a[i] - a[i - 1]);
        }
        if(ans < 0) {
            ans = -ans;
        }
        if(ans == 0) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
```

---

## 作者：细数繁星 (赞：0)

[宣传一下我的个人博客。](http://2044blog.skyman.cloud)

在一个月黑风高的夜晚，我随机跳到了这道题目。

我：这不就是退化的 P7191 吗？这道题目虽然题面和 P7191 差别不小，但是 AC 代码几乎一样。

大家可以发现，我们要做的是解这个方程组：

$$
\begin{cases}
a_1-b_1k&=&y\\
a_2-b_2k&=&y\\
a_3-b_3k&=&y\\
&\vdots\\
a_n-b_nk&=&y
\end{cases}
$$

$y$ 很烦人，于是可以错位相减，抵消掉 $y$。

$$
\begin{cases}
a_2-a_1-(b_2-b_1)k&=&0\\
a_3-a_2-(b_3-b_2)k&=&0\\
a_4-a_3-(b_{4}-b_{3})k&=&0\\
&\vdots\\
a_n-a_{n-1}-(b_{n}-b_{n-1})k&=&0
\end{cases}
$$

因为当 $a\mid q$，$b\mid q$ 的时候必然有 $(a-b)\mid q$，所以：我们要求的实际上是：

$$
\gcd(a_2-a_1,a_3-a_2,a_4-a_3,a_5-a_4,\ldots,a_n-a_{n-1})
$$
设值为 $\gamma$。

如果 $\gamma\ne0$，$\gamma$ 直接输出就行了，否则表示里面有重复元素，那么此时 $k$ 取任意值都成立。

这道题甚至比 P7191 的做法都简便。这里也不给出代码了，最后大家需要注意的是，使用最大公约数函数之前一定要排序！

---

## 作者：Milthm (赞：0)

## CF1593D1 题解

### 题目解法
拿到题目，思考一下，如果要使每个数都相等，那么减去的一定是所有两个数差值的最大公因数（这个很容易知道，因为要使最后的值最大，还要能减成一个值）。所以先排个序，然后肯定要去重（不去重就趋势）。写完了，~~然后满江红了~~一看发现没有判断无数种解。

那么问题来了，如何判断无数种解呢？我们又发现，无数个解的情况只可能出现于序列中所有数都相同的情况下，判断就可以了。

### AC代码

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int t,n,a[200005],b[200005],k;
int gcd(int x,int y){//最小公倍数函数
	if(x%y==0)return y;
	return gcd(y,x%y);
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;++i)cin>>a[i];
		sort(a+1,a+n+1);
		if(a[1]==a[n]){//这里如果最大值和最小值相等，就说明整个序列全都一样，也就是无数解的情况
			cout<<-1<<endl;
			continue;
		}
		k=0;
		for(int i=1;i<=n;++i){//去重，也可以用STL中的unique
			if(a[i]!=a[i+1]){
				b[++k]=a[i];
			}
		}
		int ans;
		for(int i=1;i<=k;++i){//两两最小公倍数
			for(int j=i+1;j<=k;++j){
				if(i==1&&j==2)ans=b[j]-b[i];//这里一定要设置初始值！
				else ans=gcd(ans,b[j]-b[i]);
			}
		}
		cout<<ans<<endl;//输出
	}
	return 0;
}
```


---

## 作者：xwh_hh (赞：0)

先分析题意。  
给定数列 $a_1,a_2,a_3,...,a_n$，求出一个最大的 $k$ 使得存在整数数列 $b_1,b_2,b_3,...,b_n$，满足 $a_1-b_1\times k=a_2-b_2\times k=...=a_n-b_n\times k$。  
由 $a_i-b_i\times k=a_j-b_j\times k$，得 $a_i\equiv a_j (\bmod\ k)$，推得 $a_1\equiv a_2\equiv...\equiv a_n(\bmod\ k)$，两两作差求最大公因数即可。  
由于 $\gcd(a,b)=\gcd(a+b,b)=\gcd(a,a+b)$，实际上只要相邻数作差即可。  
**注意：** 这题输出 $-1$ 当且仅当所有数都相等，此时求出来的最大公因数是 $0$，特判一下即可。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int beg,tmp,ans;//beg上一个数  tmp当前数  ans现在的最大公因数 
int t,n; 
int gcd(int a,int b){
	if(a>b) swap(a,b);
	return a==0?b:gcd(b%a,a);
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>beg>>tmp;
		ans=abs(beg-tmp);
		for(int i=1;i<=n-2;i++){//还有n-2个数 
			beg=tmp;
			cin>>tmp;
			ans=gcd(ans,abs(beg-tmp));
		}
		if(ans==0) ans=-1;//特判 
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：ZZQF5677 (赞：0)

### 分析内容
+ 如果 $k$ 可以是任意的大小，输出 $-1$。

因为 $k$ 只有在数组中的数字全相等的时候才能随意变化，所以只有这个情况才会输出 $-1$。

+ 考虑一个可能的正整数 $k$，在每次操作中，你可以选定一个 $i$，并将 $a_i$ 减少 $k$。

因为每个元素只能减少，而减得还是正整数，所以就只能把数组中所有元素变成当前最小值。

### 解题思路
因为 $a_i$ 减少时，必须往选尽量大的 $k$ 减，于是就要找整个数组的最大公倍数，所以只要找出 $a_i$（非当前最小值，并且对于数组还要去重）与当前最小值的差就行，然后再将这个差和其他数与当前最小值的差找个最大公倍数就行。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[105];
map<int, int> mp;  //去重。（防止多余 gcd ）
int main() {
  cin >> t;
  while (t--) {
    mp.clear();
    cin >> n;
    int minn = INT_MAX;
    bool f = 1;  // 判断数组是否全是一个数。
    cin >> a[1];
    for (int i = 2; i <= n; i++) {
      cin >> a[i];
      if (a[i] != a[1]) {
        f = 0;
      }
      minn = min(minn, a[i]);
    }
    if (f) {
      cout << -1 << endl;  //因为只有整个数组都一样时才会这样。
      continue;
    }
    int a_gcd = 0;
    bool fl = 0;  // 找第一个要是用 gcd 的数。
    for (int i = 1; i <= n; i++) {
      if (a[i] != minn) {
        if (!fl) {
          a_gcd = abs(a[i] - minn);
          mp[a[i]] = 1;  //加入去重列表。
          fl = 1;
          continue;
        }
        if (mp[a[i]] != 0) {
          continue;  //防止重复。
        }
        a_gcd = __gcd(a_gcd, abs(a[i] - minn /*当前数与要变得数的差距。。。*/));
        mp[a[i]] = 1;  //加入去重列表。
      }
    }
    cout << a_gcd << endl;
  }
  return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 题意

取正整数 $k$，使得存在一个数 $x$，对于任意一个 $i\ (1\le i\le n)$，都有 $x-a[i]\equiv0\pmod k$。尽量让 $k$ 最大。

如果 $k$ 可以取无限大，输出 $-1$。

### 2 思路

很明显，对于所有的满足 $1\le i,j\le n$ 的 $i$ 和 $j$，都有 $|a[i]-a[j]|\equiv0\pmod k$。

那么，本题就求的是：

$$\operatorname{gcd}(a[i]-a[j])\ (1\le i,j\le n\operatorname{and}a[i]-a[j]\ge1)$$

但是，有一种情况例外，就是整个序列里的数都相等的情况，输出 $-1$ 即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 40
int t;
int n;
int a[max_n+2];
int g[max_n*max_n+2];
int gi;
int ans;
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1593D1_1.in","r",stdin);
	freopen("CF1593D1_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
		}
		gi=0;
		for(int i=1;i<=n;++i){
			for(int j=1,k;j<=n;++j){
				k=a[i]-a[j];
				if(k<=0)continue;
				g[++gi]=k;
			}
		}
		if(!gi){
			printf("-1\n");
			continue;
		}
		ans=g[1];
		for(int i=2;i<=gi;++i)ans=gcd(ans,g[i]);
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59839008)

By **dengziyue**

---

## 作者：Jairon314 (赞：0)

### CF1593D1

----------

> 给定一个长度为 $ n $ 的数组 $ a $ ， 找到一个最大的 $ k $ ，使得存在一个定值 $ val $ ，使得所有的 $ a_i-val $ 都被 $ k $ 整除或者 $ a_i=val $ 。如果这个 $ k $ 可以任意大，输出 $ -1 . $

首先考虑 $ k $ 任意大的情况。容易发现数组中的所有数字为定值是 $ k $ 能否任意大的充要条件。

根据同余的知识，我们可以发现，这个定值 $ val $ 肯定可以为最小值，那我们就把最值当作最小值来看。根据题意，可以发现，答案即为所有 $ a_i-val $ 的 $ gcd $（由题意可以直接得）。注意，这里所谓的所有 $ a_i $，不包括 $ a_i=val $ 的情况，所以注意特判。

该弱化版其实就是签到吧，看能不能读懂题。

### CF1593D2

----------

> 此题与上一题的区别在于，上一个题必须保证所有的 $ a_i-val $ 被 $ k $ 整除，而这个题只需要保证至少 $ \frac{n}{2} $ 个即可。

考虑与上一个题相同的做法，形成转化。

注意到该题可以考虑为从 $ n $ 个数字中选择 $ \frac{n}{2} $ 个数字使得 $ k $ 最大。

还是先考虑 $ k $ 任意大。容易发现是否存在大于等于 $ \frac{n}{2} $ 个相同的数字是 $ k $ 能否任意大的充要条件。

然后进行转化，因为选择 $ n $ 个数字的答案是不考虑 $ a_i=val $ 的情况中所有 $ a_i-val $ 的 $ gcd $ ，所以此题同理。由上一题的结论可得，定值 $ val $ 为选出来的数字中的最小值，所以我们可以枚举这个最小值，然后在比这个最小值大的数字中找到 $ \frac{n}{2} $ 个数字，使得这些数字与 $ val $ 的差的 $ gcd $ 最大。[就是这个题的结论。](https://www.luogu.com.cn/problem/P1414)

### 代码

----------

$ D1 $ 过于简单，代码就不放了哈，想要的找我私聊。

```cpp
// D2

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
 
#define int long long
 
/***** Fast_IO *****/
 
using std::cin;
using std::cout;
using vii = std::vector<int> ;
using pii = std::pair<int,int> ;
 
namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;
 
	inline char gc (){
		return p1==p2&&(p2=(p1=buf)+fread(buf,1,(1<<21),stdin),p1==p2)?EOF:*p1++;
	}
 
	#define gc getchar
	#define pc putchar
	#define ONLINE_JUDGE OJ
 
	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}
 
	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}
 
	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		int tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}
 
	void _FILE(){
		#ifndef ONLINE_JUDGE
			freopen("text.in","r",stdin);
			freopen("text.out","w",stdout);
		#endif
	}
 
	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define pb push_back
	#define mp make_pair
	#define fir first
	#define sec second
}using namespace IO;
 
/***** Fast_IO *****/
 
#define maxn 2000010
#define SIZE 5010
 
int T;
int a[maxn];
int c[maxn];
int n;
 
::unordered_map<int,int> buc;
 
signed main(){
	_FILE();
	read(T);
	while(T--){
		n=read(_);
		memset(a,0,sizeof a);
		buc.clear();
		int CNT=0,ans=0;
		FOR(i,1,n){ read(a[i]); CNT=::max(CNT,++buc[a[i]]); }
		if(CNT>=n/2){ puts("-1"); continue; }
		::sort(a+1,a+n+1);
		FOR(i,1,n/2+1){
			int res=0,rul=0;
			memset(c,0,sizeof c);
			FOR(j,i+1,n){
				int x=a[j]-a[i];
				if(x==0){ ++rul; continue; }
				res=::max(res,x);
				int lim=sqrt(x);
				for(int k=1;k<=lim;k++){
					if(x%k==0){
						++c[k];
						if(x!=k*k){
							++c[x/k];
						}
					}
				}
			}
			int delta=res;
			FOR(i,1,n/2-1-rul){
				while(c[delta]<i){ --delta; }
			}
			ans=::max(ans,delta);
		}
		outn(ans);
	}
	return 0;
}
```


---

