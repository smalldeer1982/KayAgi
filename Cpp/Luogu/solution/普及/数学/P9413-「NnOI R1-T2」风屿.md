# 「NnOI R1-T2」风屿

## 题目背景

「与风为名，屿之齐鸣。」——风屿

## 题目描述

风屿是一块 $ n $ 行，$ m $ 列的群岛，第 $ i $ 行第 $  j $ 列记为 $ (i,j) $。

风屿的重力系统很奇怪，$ (i,j) $ 的重力系数 $ g_{i,j}=a_i+b_j $。$ a,b $ 是两个已知的长度分别为 $ n,m $ 的数组。

我们定义岛 $ (x,y) $ 和 $ (z,w) $ **相邻**当且仅当 $ |x-z|+|y-w|=1 $，定义 $ (x,y) $ 和 $ (z,w) $ **连通**当且仅当两种情况至少有一种满足：

* $ (x,y),(z,w) $ 相邻，且 $ g_{x,y}=g_{z,w} $。

* 存在另一个岛 $ (u,v) $ 使得 $ (x,y) $ 和 $ (u,v) $ 连通且 $ (u,v) $ 和 $ (z,w) $ 连通，也就是说，连通关系**具有传递性**。

我们定义无序互异的岛集 $ \{(x_i,y_i)\} $ 为**同色连通块**，当且仅当岛集中任意两岛连通。

找到最大的同色连通块，并求出大小和这样的块的个数。

## 说明/提示

### 样例解释

对于样例 $ 1 $：

对于第 $ 1 $ 组测试数据，重力系数依次如下：

```
2 3 4 5
3 4 5 6
3 4 5 6
```

```
2 3 4 5
* # ? .
* # ? .
```

标记符号的为最大的同色连通块，大小为 $ 2 $，共 $ 4 $ 个。

### 数据范围

对于 $ 20\% $ 的数据，$ n,m \le 10^3 $。

对于另 $ 20\% $ 的数据，所有 $ b_i $ 相等。

对于另 $ 20\% $ 的数据，第二问答案一定为 $ 1 $。

对于另 $ 20\% $ 的数据，$ T=1 $，这四档部分分表示的测试点集合互不包含。

对于 $ 100\% $ 的数据，$ 1 \le T \le 5 $，$ 1 \le n,m \le 10^5 $，$ 1 \le a_i,b_i \le 10^9 $。

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
| idea | Kevin0501 |
| std | Kevin0501
| data | EstasTonne |
| check | EstasTonne |
| solution | Kevin0501 |

## 样例 #1

### 输入

```
3
3 4
1 2 2
1 2 3 4
4 5
1 2 2 3
2 3 3 3 4
6 7
1 1 2 2 3 4
1 2 2 2 3 3 3```

### 输出

```
2 4
6 1
6 4```

# 题解

## 作者：___w (赞：8)

### [P9413 「NnOI R1-T2」风屿](https://www.luogu.com.cn/problem/P9413)
#### 题外话
这一题定义得花里胡哨的。

#### 题意简述
构造一个 $n\times m$ 的矩阵 $g_{i,j}=a_i+b_j$，求 $g$ 的最大连通块的数量及其个数。

#### 题目分析
首先考虑搜索，可以用 dfs 或 bfs 求一个连通块的大小，再统计答案，时间复杂度为 $\mathcal{O}(Tnm)$。但是 $1\le n,m\le 10^5$ 时间和空间上都难以忍受，所以 pass 掉，代码就省略了。

观察样例我们注意到，因为 $g_{i,j}=a_i+b_j$，所以联通块都是个矩形。而这个矩形的长宽分别为 $a,b$ 连续相同的区间的长度，所以大小就为两个连续相同的区间长度的乘积。由于乘法原理，最大矩形的个数就为 $a,b$ 最长连续相同的区间的个数的乘积，时间复杂度为 $\mathcal{O}(T(n+m))$。

所以这题的做法是就 $a,b$ 两个数组的最长连续相同的区间的长度 $l_1,l_2$ 及其个数 $c_1,c_2$，最大块的的大小就为 $l_1l_2$，最大块个数为 $c_1c_2$，代码如下。

#### 代码
由于有相乘，所以可能会爆 ```int```，要开 ```long long```。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+5;
int t, n, m, ans1, ans2, a[N], b[N];
signed main() {
	cin >> t;
	while (t--) {
		cin >> n >> m;
		int c = 1, l = 1, len = 1;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			if (i == 1) continue;
			if (a[i] == a[i-1]) ++len;
			else len = 1;
			if (len > l) l = len, c = 1;
			else if (len == l) ++c;
		}
		ans1 = l, ans2 = c;
		c = 1, l = 1, len = 1;
		for (int i = 1; i <= m; ++i) {
			cin >> a[i];
			if (i == 1) continue;
			if (a[i] == a[i-1]) ++len;
			else len = 1;
			if (len > l) l = len, c = 1;
			else if (len == l) ++c;
		}
		ans1 *= l, ans2 *= c;
		cout << ans1 << ' ' << ans2 << '\n';
	}
	return 0;
}
```

---

## 作者：船酱魔王 (赞：4)

# [NnOI-R1 T2] 风屿 官方题解

## 题意回顾

给定长度分别为 $ n,m $ 的数组 $ a,b $。构造 $ n \times m $ 的矩阵使得 $ g_{i,j}=a_i+b_j $，求 $ g $ 的最大连通块大小和个数。

$ T \le 5 $，$ n,m \le 10^5 $。

## 分析

对于两个矩阵中格子，当他们相邻且连通时，必有构造他们的一个数组位置一样，一个数组位置差 $ 1 $ 但是数值一样。因为连通块是连续的所以对于一个连通块，必然可以把它投影到两个数组上，每个数组的投影段全相等，此时我们可以构造出一个包含原连通块的矩形连通块。因此最大的连通块一定是矩形。

我们找出两个数组的最长连续相等段的大小和个数，将其乘积即可。

复杂度 $ O(T(n+m)) $。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int T;
int n, m;
int a[N];
int lent;
int cnt;
int nowl;
void calc(int x) {
	for(int i = 1; i <= x; i++) {
		scanf("%d", &a[i]);
	}
	a[x + 1] = 0;
	lent = 0;
	cnt = 0;
	nowl = 0;
	for(int i = 1; i <= x + 1; i++) {
		if(a[i] == a[i - 1]) {
			nowl++;
		} else {
			if(nowl == lent) {
				cnt++;
			} else if(nowl > lent) {
				lent = nowl;
				cnt = 1;
			}
			nowl = 1;
		}
	}
}
signed main() {
	scanf("%d", &T);
	for(int ti = 1; ti <= T; ti++) {
		scanf("%d%d", &n, &m);
		calc(n);
		int la = lent;
		int ca = cnt;
		calc(m);
		int lb = lent;
		int cb = cnt;
		cout << la * lb << " " << ca * cb << endl;
	}
	return 0;
}
```

---

## 作者：wdgm4 (赞：4)

这道题是我在比赛时 A 的。

## 思路

由于一座岛（假设是 $(i,j)$）相邻的岛只是上下左右的一共四个岛（即是 $(i-1,j),(i+1,j),(i,j-1),(i,j+1)$ 四个）。那么对于它左右两座岛，这三座岛的重力系数分别只与 $b_j,b_{j-1},b_{j+1}$ 有关，那么要想重力系数相同，只能是 $b$ 中的值相同，与 $a$ 中的值无关（因为这三个的重力系数都是 $a_i$ 加一个数）。$(i,j)$ 上下两座岛同理。

显然，同色连通块在平面图中是个矩形（就是把风屿群岛形象化成一个由 $n$ 行和 $m$ 列的 $n \times m$ 个小方格组成的矩形，然后把重力系数不同的方格染成不同颜色）。这个可以证明一下。

#### 证明

这里运用反证法。~~证明得很烂，凑合看吧。QWQ~~

暂时不考虑长或宽是 $1$ 的情况。

设 $(i+1,j),(i,j+1),(i+1,j+1)$ 的重力系数相同，$(i,j)$ 的重力系数与其不同（注重的是相对位置关系），则 $a_i \ne a_{i+1}$，$b_j \ne b_{j+1}$。看 $(i+1,j)$ 和 $(i+1,j+1)$ 由最前面的可得 $b_j=b_{j+1}$，这与我们假设的矛盾，再看 $(i,j+1)$ 和 $(i+1,j+1)$，同上可得 $a_i=a_{i+1}$，也与我们假设的矛盾。这样就可以证明不会出现同色连通块有缺角的情况（感性理解一下），由于我们只考虑已经是联通的，所以其他的一些情况也可以像刚才那样证明。

所以就证明完了。QWQ

------------

所以只需找到 $a$ 数组和 $b$ 数组中最长的相同子串的长度和数量。

最大块大小就是两个长度相乘，个数是两个数量相乘。

## 代码

```cpp
#include<bits/stdc++.h>
#define XD 114514
#define MAXN 100010
#define int long long
using namespace std;
int read(){
	char ch=getchar();
	int nem=0;
	while(!(ch<='9' and ch>='0')) ch=getchar();
	while(ch<='9' and ch>='0') nem=nem*10+ch-'0',ch=getchar();
	return nem;
}
int t;
int n,m,a[MAXN],b[MAXN];
int aa[MAXN],len1,bb[MAXN],len2;
int num1[MAXN],num2[MAXN];
int max1,max2,sum1,sum2;
signed main(){
//	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>n>>m;
		//初始化 
		len1=len2=0;
		for(int i=1;i<=n;i++) aa[i]=num1[i]=0;
		for(int i=1;i<=m;i++) bb[i]=num2[i]=0;
		max1=max2=sum1=sum2=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(aa[len1]!=a[i]){
				if(max1<num1[len1]){
					max1=num1[len1];
					sum1=1;
				}else if(max1==num1[len1]){
					sum1++;
				}
				aa[++len1]=a[i];
				num1[len1]=1;
			}else num1[len1]++;
		} 
		if(max1<num1[len1]){
			max1=num1[len1];
			sum1=1;
		}else if(max1==num1[len1]){
			sum1++;
		}
		for(int i=1;i<=m;i++){
			b[i]=read();
			if(bb[len2]!=b[i]){
				if(max2<num2[len2]){
					max2=num2[len2];
					sum2=1;
				}else if(max2==num2[len2]){
					sum2++;
				}
				bb[++len2]=b[i];
				num2[len2]=1;
			}else num2[len2]++;
		} 
		if(max2<num2[len2]){
			max2=num2[len2];
			sum2=1;
		}else if(max2==num2[len2]){
			sum2++;
		}
		cout<<max1*max2<<" "<<sum1*sum2<<"\n";
	}
	return 0;
}

```

## 后记

1. 记得开 `long long`，不然只能得 $20pts$。

2. 我感觉这道题思路比代码实现更难，所以我没有太详细的说代码如何实现，~~其实就是我懒~~。QWQ

---

## 作者：zhzkiller (赞：2)

## 题目描述
这道题要求我们找出一个行为 $n$，列为 $m$ 的矩阵中最大联通块的大小及个数，该联通块以行、列数值相加定义。

## 解题思路
我们很容易得出一个性质：由于行值与列值固定，联通块内数值相同，所以其形状一定为矩形。该问题就转化为了这样一个模型：

定义相等子段为数组中值相等的一段区间，找出数组 $a$ 和 $b$ 中各自的最长相等子段长，这样联通块的大小就为两者相乘。

而相同大小的联通块可以有多个，这是因为最大相等子段长可能不止一个。又根据乘法原理，两个数组中最大相等子段长的个数相乘即为相同大小联通块个数。

具体实现为：

1.扫一遍数组，记录最大相等子段长；

2.扫的同时用一个变量实时记录最大相等子段长出现的次数。

总复杂度为 $O(T(n+m))$。

完结撒花~

献上蒟蒻的 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100010;

int t;
int n,m;
int a[N],b[N];
long long num1[N],num2[N];
long long cnt;//一定满足a[0]!=a[1]和b[0]!=b[1]，所以无需初始化 

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d",&n,&m);
		long long maxn=1,maxm=1;//记录a[]与b[]的最长子段长 
		memset(num1,0,sizeof(num1));//记录a[]最长子段长的数量 
		memset(num2,0,sizeof(num2));//记录b[]最长子段长的数量 
		num1[1]=n,num2[1]=m;//防止全部为长度为1的坑人数据不更新num数组 
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]==a[i-1])
			{
				cnt++;
				if(cnt>=maxn) maxn=cnt,num1[cnt]++;
			}
			else cnt=1;
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&b[i]);
			if(b[i]==b[i-1])
			{
				cnt++;
				if(cnt>=maxm) maxm=cnt,num2[cnt]++;
			}
			else cnt=1;
		}
		printf("%lld %lld\n",maxn*maxm,num1[maxn]*num2[maxm]);
	}
	return 0;
}
```

### 细节

1.不开 `long long` 会炸（最大到 $10^{10}$ 级别，但是数据水不水不知道）；

2.`cnt` 初始为 $1$，最小长度肯定是自己。

---

## 作者：HEIMOFA (赞：2)

分析题目，由于同色连通块当中每两个岛都相邻，则必须是一个矩阵。

其次，又因为重力系数，所以同色连通块的两个岛值相等。

也就是说，第一问就是最大矩阵，并且其大小为 $a$ 数组当中**最长连续且相等的序列长度**乘以 $b$ 数组当中**最长连续且相等的序列长度**。

第二问呢？自然就是求有几个这样的矩阵。

时间复杂度为 $O(T(n+m))$ 。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100005;
int a[N],b[N];
int a_siz,a_num,b_siz,b_num;

signed main()
{
	int t;scanf("%lld",&t);
	while(t--){
		int n,m;scanf("%lld%lld",&n,&m);
		int tmp=1;
		a_siz=a_num=b_siz=b_num=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			if(a[i]==a[i-1]) tmp++;
			else tmp=1;
			if(tmp>a_siz) a_siz=tmp,a_num=1;
			else if(tmp==a_siz) a_num++;
		}
		tmp=1;
		for(int i=1;i<=m;i++){
			scanf("%lld",&b[i]);
			if(b[i]==b[i-1]) tmp++;
			else tmp=1;
			if(tmp>b_siz) b_siz=tmp,b_num=1;
			else if(tmp==b_siz) b_num++;
		}
		printf("%lld %lld\n",a_siz*b_siz,a_num*b_num);
	}
	return 0;
}
```


---

## 作者：PP__ (赞：2)

其实很好想，不用求出整个矩阵。

其实分析那个曼哈顿距离的式子，会发现其实它本质上就是在 $a$ 数组中取一个元素 $a_i$，然后在另一个数组中取两个相邻的元素 $b_i$ 和 $b_{i + 1}$，这里 $a$ 和 $b$ 可以互换。

然后另一个要求就是要让 $a_i+b_i=a_i+b_{i+1}$。很明显，要让 $b_i=b_{i+1}$。

所以我们在 $a$ 数组和 $b$ 数组中各求一遍最长区间使得区间内所有数相等就可以了。储存最长区间的长度和个数。最大连通块的答案就是 $a$ 数组和 $b$ 数组中最长区间的长度相乘，个数就是最长区间的个数相乘。

最后提醒一遍：多测不清空，爆零两行泪。

## AC CODE

```c++
#include <iostream>
#include <cstring>
using namespace std;
int T,n,a[100010],m,b[100010],t[100010],tt[100010];
int main()
{
	cin >> T;
	while(T--)
	{
		memset(t,0,sizeof(t));
		memset(tt,0,sizeof(tt));
		cin >> n >> m;
		long long cnt = 1,maxn = 0,mmaxn = 0;  //记得开long long
		for (int i = 1;i <= n;i++)
		{
			cin >> a[i];
			if(a[i] == a[i - 1])cnt++;
			else 
			{
				t[cnt]++;
				maxn = max(maxn,cnt);
				cnt = 1;
			}
		} 
		t[cnt]++;
		maxn = max(maxn,cnt);
		cnt = 1;
		for (int i = 1;i <= m;i++)
		{
			cin >> b[i];
			if(b[i] == b[i - 1])cnt++;
			else 
			{
				tt[cnt]++;
				mmaxn = max(mmaxn,cnt);
				cnt = 1;
			}
		}
		tt[cnt]++;
		mmaxn = max(mmaxn,cnt);
		cnt = 1;
		cout << maxn * mmaxn << " " << t[maxn] * tt[mmaxn] << endl; 
	}
	return 0;
}
```

---

## 作者：tsqtsqtsq0309 (赞：1)

# P9413 「NnOI R1-T2」风屿

## 题目大意

给定两个长度分别为 $n$，$m$ 的数组 $a$、$b$，以及一个满足 $g_{i,j} = a_i + b_j$ 的大小为 $n \times m$ 的矩阵 $g$。

定义岛 $ (x,y) $ 和 $ (z,w) $ **相邻**当且仅当 $ |x-z|+|y-w|=1 $，定义 $ (x,y) $ 和 $ (z,w) $ **连通**当且仅当两种情况至少有一种满足：

* $ (x,y),(z,w) $ 相邻，且 $ g_{x,y}=g_{z,w} $。

* 存在另一个岛 $ (u,v) $ 使得 $ (x,y) $ 和 $ (u,v) $ 连通且 $ (u,v) $ 和 $ (z,w) $ 连通。

定义无序互异的岛集 $ \{(x_i,y_i)\} $ 为**同色连通块**，当且仅当岛集中任意两岛连通。

试找出矩阵 $g$ 中**最大**的同色连通块，并求出该连通块的大小和这样的连通块的个数。

## 思路

由题面可知定义岛 $ (x,y) $ 和 $ (z,w) $ **相邻**当且仅当 $ |x-z|+|y-w|=1 $。显然由此可以推导出：
$$
|x-z|+|y-w|=1 \Rightarrow (x = z \wedge y \ne w) \vee (x \ne z \wedge y = w)
$$
显然，要求 $a_x + b_y = a_z + b_w$，则必须满足：
$$
(a_x = a_z \wedge b_y \ne b_w) \vee (a_x \ne a_z \wedge b_y = b_w)
$$
此时，只需求 $a$ 和 $b$ 中的最长连续相同区间的长度。

令 $a$ 的最长连续相同区间长度为 $lena$，$b$ 的最长连续相同区间长度为 $lenb$，$a$ 的最大连通块个数为 $tota$，$b$ 的最大连通块个数为 $totb$。由乘法原理可知，最大连通块的大小为 $lena \times lenb$，最大连通块的个数为 $tota \times totb$。

## 代码

```cpp
#include <iostream>
#define int long long
#define MAXN 100005
#define MAXM 100005
using namespace std;
int T, n, m;
int a[MAXN], b[MAXM];
int lena, lenb, tota, totb, tmpa, tmpb;
int read(){
    int t = 1, x = 0;char ch = getchar();
    while(!isdigit(ch)){if(ch == '-')t = -1;ch = getchar();}
    while(isdigit(ch)){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
    return x * t;
}
void write(int x){
    if(x < 0){putchar('-');x = -x;}
    if(x >= 10)write(x / 10);
    putchar(x % 10 ^ 48);
}
void solve(){
    n = read();m = read();
    for(int i = 1 ; i <= n ; i ++)a[i] = read();
    for(int i = 1 ; i <= m ; i ++)b[i] = read();
    lena = 1;tmpa = 1;tota = 0;
    lenb = 1;tmpb = 1;totb = 0;
    for(int i = 2 ; i <= n ; i ++){
        if(a[i] == a[i - 1])tmpa++;
        else{lena = max(lena, tmpa);tmpa = 1;}
    }lena = max(lena, tmpa);
    for(int i = 2 ; i <= m ; i ++){
        if(b[i] == b[i - 1])tmpb++;
        else{lenb = max(lenb, tmpb);tmpb = 1;}
    }lenb = max(lenb, tmpb);
    tmpa = 1;tmpb = 1;
    for(int i = 2 ; i <= n ; i ++){
        if(a[i] == a[i - 1])tmpa++;
        else{
            if(tmpa == lena)tota++;
            tmpa = 1;
        }
    }if(tmpa == lena)tota++;
    for(int i = 2 ; i <= m ; i ++){
        if(b[i] == b[i - 1])tmpb++;
        else{
            if(tmpb == lenb)totb++;
            tmpb = 1;
        }
    }if(tmpb == lenb)totb++;
    write(lena * lenb);putchar(' ');
    write(tota * totb);putchar('\n');
}
signed main(){
    T = read();
    while(T--)solve();
    return 0;
}
```



---

## 作者：哈哈人生 (赞：0)

## 题外话
~~这题很花里胡哨，不得不说出题人很不良心。~~

## 简要题意
由 $a$ 数组和 $b$ 数组两两项相加构成一个矩阵，求**连通块**。

## 思路
观察这两个数组能组成得最大连通的且数字相同的“块”的个数（即最大连通块个数），可以发现 $a_i$ 或者 $b_i$ 有连续 $x$（$x\ge 2$）个数字相同时，一定会出现非 $1$ 个数的连通块。因为 $a_i$ 和 $b_i$ 构成数列时是两两相加的（不会有两个不属于同一数组的数没有相加过），如果两个相同数相邻，它们都会加上 $b$ 中的一个数，最终数字就会相同，并且保证相邻。而这个连通块的大小就是 $b_i$ 的连续个数乘上 $a_i$ 的连续个数（原理同上，读者可以自己试验），这样就能不构造出真正的矩阵也求出来答案啦。

每天一个小技巧：打表求最大值，相等就 $g$（专门设一个变量）加一。

## 代码
我的代码使用了模块化编程思想（人话：函数），十分好看。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m;
void cinn(int k,int &g1,int &g2){
	int num=1,s,ls;//g2记录个数，g1为最大值
	scanf("%lld",&ls);
	for(int i=2;i<=k;i++){
		scanf("%lld",&s);
		if(s==ls)num++;//连续个数
		else{
			if(g1<num)g1=num,g2=1;
			else if(g1==num)g2++;
			num=1;//别忘了清1
		}
		ls=s;
	}
	if(g1<num)g1=num,g2=1;
	else if(g1==num)g2++;
	return;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		int max1=-1,max2=-1,mgs1=0,mgs2=0;
		scanf("%lld%lld",&n,&m);
		cinn(n,max1,mgs1);
		cinn(m,max2,mgs2);
		printf("%lld %lld\n",max1*max2,mgs1*mgs2);
	}
	return 0;
}
```
请读者诚信粘贴题解，遵守洛谷社区守则，最后，点个赞吧。

---

## 作者：Ferdina_zcjb (赞：0)

这道题，第一下考虑搜索，用 dfs 和 bfs 进行需要 $O(Tnm)$ 的复杂度，明显在 $1 \le n,m \le 10^5$ 的情况下，是肯定超时的。那让我们用数学的方法去分析一下它。

题目中要求了 $g_{i,j} = a_i+b_i$，所以题目问题中所形成的必定是一个矩阵。而且画图以后容易发现，矩阵的长与宽分别都是 $a$ 与 $b$ **连续相同元素区间的长度**，固然大小就是两者的积（即矩阵面积）。经过~~小学~~数学可得，题目要求的最大矩阵的个数就是 $a$ 与 $b$ 最长连续相同元素区间的的个数的乘积。时间复杂度  $O(T(n+m))$。

以下是简单易懂的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN_M = 1e5+5;
int a[MAXN_M],b[MAXN_M],T;
signed main(){
    cin >> T;
    while(T--){
        int n,m;
        cin >> n >> m;
        int l = 1,h = 1,l_max = 1;/*
        l是当前连续相同元素区间的长度。
        l_max是目前最长连续相同元素区间的长度。
        h是整个区间中最长连续相同元素区间个数。
        */
        for(int i = 1;i <= n;++i){
            cin >> a[i];
            if(i == 1)continue;
            if(a[i] == a[i-1]){//如果元素相等。
                l++;
            }else{
                l = 1;
            }
            if(l_max < l){//如果出现更长的区间。
                l_max = l; 
                h = 1;
            }else if(l == l_max){
                h++;
            }
        }
        int ans_one = l_max,ans_two = h;
        l = 1,h = 1,l_max = 1;
        for(int i = 1;i <= m;++i){//同上。
            cin >> a[i];
            if(i == 1)continue;
            if(a[i] == a[i-1]){
                l++;
            }else{
                l = 1;
            }
            if(l_max < l){
                l_max = l; 
                h = 1;
            }else if(l == l_max){
                h++;
            }
        }
        ans_one *= l_max,ans_two *= h;//l1*l2是大小，则h1*h2位个数。
        cout << ans_one << " " << ans_two << endl;
    }
    return 0;
}
```




---

## 作者：sz_jinzikai (赞：0)

[题目传送门](/problem/P9413)
# 题意
现有一个 $n\times m$ 的矩阵 $g$，$g_{i,j}=a_i+b_j$，求 $g$ 中最大连通块的数量及最大连通块个数。
# 思路
这题设计到最大连通块，我们很容易想到 dfs 和 bfs，但是一看数据范围，$1\le n,m\le10^5$，这样搜索肯定吃不消。这时候，我们发现题目中有一句很重要的话：岛 $(x,y)$ 和 $(z,w)$ **相邻**当且仅当 $\mid x-z\mid+\mid y-w\mid=1$。这说明什么？这说明了 $x=z$ 和 $y=w$ 中恰好有 $1$ 个是成立的！这时候我们要求 $a_x+b_y=a_z+b_w$，则必须满足 $a_x=a_z$ 和 $b_y=b_w$ 中的一个，这个问题就转变成了求 $a$ 和 $b$ 的最长连续相同的区间的长度。我们现在设 $a$ 的最长连续相同的区间的长度为 $maxa$，$b$ 的最长连续相同的区间的长度为 $maxb$，$a$ 的最大连通块个数为 $suma$，$b$ 的最大连通块个数为 $sumb$，根据乘法原理，最大联通块的大小就是 $maxa\times maxb$，最大连通块个数就是 $suma\times sumb$ 了。
# 代码
```cpp
//P9413
# include <bits/stdc++.h> //万能头 
typedef long long ll; //不开 long long 见祖宗，以后 long long 可以简写作 ll
using namespace std;
ll t, n, m, a[100005], b[100005], maxa, maxb, suma, sumb, nowa, nowb; //定义变量
int main () { //定义主函数
	cin >> t; //输入数据组数
	while (t --) { //多组数据的通用写法
		cin >> n >> m; //输入 
		for (ll i = 0; i < n; ++ i)
			cin >> a[i]; //输入 
		for (ll i = 0; i < m; ++ i)
			cin >> b[i]; //输入 
		maxa = maxb = nowa = nowb = 1, suma = sumb = 0; //多组数据别忘了初始化！！！ 
		for (ll i = 1; i < n; ++ i)
			if (a[i] == a[i - 1]) //如果和上一个相同 
				++ nowa; //计数器加 1 
			else //如果和上一个不同 
				maxa = max (maxa, nowa), nowa = 1; //更新当前最大值，计数器重置 
		maxa = max (maxa, nowa); //别忘了最后一段！！！ 
		for (ll i = 1; i < m; ++ i) //类似的，不讲了 
			if (b[i] == b[i - 1])
				++ nowb;
			else
				maxb = max (maxb, nowb), nowb = 1;
		maxb = max (maxb, nowb);
		nowa = nowb = 1; //计数器重置 
		for (ll i = 1; i < n; ++ i) //类似的重新做一遍，用于求最大值个数 
			if (a[i] == a[i - 1])
				++ nowa;
			else {
				if (nowa == maxa) //如果这一段是最大值 
					++ suma; //最大值数量加 1 
				nowa = 1;
			}
		if (nowa == maxa) //最后一段别忘记 
			++ suma;
		for (ll i = 1; i < m; ++ i) //类似的，不讲了 
			if (b[i] == b[i - 1])
				++ nowb;
			else {
				if (nowb == maxb)
					++ sumb;
				nowb = 1;
			}
		if (nowb == maxb)
			++ sumb;
		cout << maxa * maxb << ' ' << suma * sumb << '\n'; //输出 
	}
	return 0; //结束程序
}
```

---

