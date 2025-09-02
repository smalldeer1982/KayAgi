# [ABC294E] 2xN Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc294/tasks/abc294_e

$ 2 $ 行 $ L $ 列のマス目があります。 上から $ i $ 行目 $ (i\in\lbrace1,2\rbrace) $、左から $ j $ 列目 $ (1\leq\ j\leq\ L) $のマス目を $ (i,j) $ で表します。 $ (i,j) $ には整数 $ x\ _\ {i,j} $ が書かれています。

$ x\ _\ {1,j}=x\ _\ {2,j} $ であるような整数 $ j $ の個数を求めてください。

ただし、$ x\ _\ {i,j} $ の情報は $ (x\ _\ {1,1},x\ _\ {1,2},\ldots,x\ _\ {1,L}) $ と $ (x\ _\ {2,1},x\ _\ {2,2},\ldots,x\ _\ {2,L}) $ をそれぞれ連長圧縮した、長さ $ N\ _\ 1 $ の列 $ ((v\ _\ {1,1},l\ _\ {1,1}),\ldots,(v\ _\ {1,N\ _\ 1},l\ _\ {1,N\ _\ 1})) $ と長さ $ N\ _\ 2 $ の列 $ ((v\ _\ {2,1},l\ _\ {2,1}),\ldots,(v\ _\ {2,N\ _\ 2},l\ _\ {2,N\ _\ 2})) $ として与えられます。

ここで、列 $ A $ の連長圧縮とは、$ A $ の要素 $ v\ _\ i $ と正整数 $ l\ _\ i $ の組 $ (v\ _\ i,l\ _\ i) $ の列であって、次の操作で得られるものです。

1. $ A $ を異なる要素が隣り合っている部分で分割する。
2. 分割した各列 $ B\ _\ 1,B\ _\ 2,\ldots,B\ _\ k $ に対して、$ v\ _\ i $ を $ B\ _\ i $ の要素、$ l\ _\ i $ を $ B\ _\ i $ の長さとする。

## 说明/提示

### 制約

- $ 1\leq\ L\leq\ 10\ ^\ {12} $
- $ 1\leq\ N\ _\ 1,N\ _\ 2\leq\ 10\ ^\ 5 $
- $ 1\leq\ v\ _\ {i,j}\leq\ 10\ ^\ 9\ (i\in\lbrace1,2\rbrace,1\leq\ j\leq\ N\ _\ i) $
- $ 1\leq\ l\ _\ {i,j}\leq\ L\ (i\in\lbrace1,2\rbrace,1\leq\ j\leq\ N\ _\ i) $
- $ v\ _\ {i,j}\neq\ v\ _\ {i,j+1}\ (i\in\lbrace1,2\rbrace,1\leq\ j\lt\ N\ _\ i) $
- $ l\ _\ {i,1}+l\ _\ {i,2}+\cdots+l\ _\ {i,N\ _\ i}=L\ (i\in\lbrace1,2\rbrace) $
- 入力はすべて整数
 
### Sample Explanation 1

マス目は以下の図のようになっています。 !\[\](https://img.atcoder.jp/abc294/14f38720983c464a322b504738344f24.png) $ x\ _\ {1,j}=x\ _\ {2,j} $ となるような整数 $ j $ は、$ j=1,2,5,8 $ の $ 4 $ つなので、出力すべき値は $ 4 $ です。

### Sample Explanation 2

答えが $ 32\operatorname{bit} $ 整数に収まらない場合があることに注意してください。

## 样例 #1

### 输入

```
8 4 3
1 2
3 2
2 3
3 1
1 4
2 1
3 3```

### 输出

```
4```

## 样例 #2

### 输入

```
10000000000 1 1
1 10000000000
1 10000000000```

### 输出

```
10000000000```

## 样例 #3

### 输入

```
1000 4 7
19 79
33 463
19 178
33 280
19 255
33 92
34 25
19 96
12 11
19 490
33 31```

### 输出

```
380```

# 题解

## 作者：timmark (赞：11)

# ABC 294E题解

一道不错的**双指针法**练手题。

首先看题，$L$ 的大小非常爆炸，$\text{O(n)}$ 填入数字肯定不现实。

因为有两个序列，我们考虑使用双指针法实现。

定义 $4$ 个变量 $i$、$j$、$l_1$、$l_2$，分别表示序列一扫到了第几段、序列二扫到了第几段，序列一目前扫过的段的长度和，序列二目前扫过的段的长度和。

看不懂没关系，可以看一下样例一的模拟过程来辅助理解。

首先 $i$ 初始化为 $1$，$j$ 初始化为 $2$，$l_1$ 初始化为 $2$，$l_2$ 初始化为 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/q1ct3xah.png)

目前两段的数字是一样的，计算答案 $=\min{(2,4)}-\max{(0,0)}=2$ ,也就是说有 $2$ 个数字相等。

然后因为 $l_1 < l_2$ ，所以 $l_1$ 跳到下一段，$i$ 变成 $2$，$l_1$ 变成 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/h8w5j0yp.png)

此时两段的数字不同，不进行答案统计。

现在 $l_1 = l_2$ ，我们就随便选一个往后跳(我选的是 $l_2$)，$j$ 变成 $2$，$l_2$ 变成 $5$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ttcwdx63.png)

目前两段数字不同，我们不进行答案统计。

这时 $l_1$ 比较小，所以 $l_1$ 往后跳，$i$ 变成 $3$，$l_1$ 变成 $7$。

![](https://cdn.luogu.com.cn/upload/image_hosting/5qc2uus9.png)

这两段数字一样，我们进行答案统计。计算答案 $=\min{(7,5)}-\max{(4,4)}=1$ ,也就是说有 $1$ 个数字相等。

这时 $l_2$ 比较小，$l_2$ 向后跳到 $8$ ，$j$ 变成 $3$。

![](https://cdn.luogu.com.cn/upload/image_hosting/fe5y5kbk.png)

两段的数字不同，不进行答案统计。

现在 $l_1$ 比较小，$l_1$ 往后跳到 $8$，$i$ 跳到 $4$。

![](https://cdn.luogu.com.cn/upload/image_hosting/f3limo7c.png)

两段数字相同，进行答案统计。计算答案 $=\min{(8,8)}-\max{(7,5)}=1$ ,也就是说有 $1$ 个数字相等。

现在两个指针都跳到了终点，模拟结束，一共有 $4$ 个相等的数字。

那么我们整理一下上述过程，得到一个完整的实现方法：

- 如果当前两段相交且数字相同，那么进行答案统计；

- 如果 $l_1<l_2$ 选择第一段，否则选择第二段；

- 如此循环往复，直到两个指针都跳到最后一段。

要注意的几个点：

1.要开 long long，会超的都要开；

2.如果两段无交，则不答案统计。

好了，上代码！

code :

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long l,a1[100005],b1[100005],a2[100005],b2[100005],ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> l >> n >> m ;
	for(int i=1;i<=n;i++) cin >> a1[i] >> b1[i] ;
	for(int i=1;i<=m;i++) cin >> a2[i] >> b2[i] ;
	int i=1,j=1;
	long long l1=b1[1],l2=b2[1];
	while(i<=n && j<=m){
		if(a1[i]==a2[j]){
			long long x=l1-b1[i],y=l2-b2[j];
			ans+=max(0ll,min(l1,l2)-max(x,y));
			
		}if(l1>=l2) l2+=b2[++j];
		else l1+=b1[++i];
	}cout << ans ;
	return 0;
}
```

看完别忘了给我点个赞吧 QwQ。

---

## 作者：Neil_Qian (赞：2)

# [ABC294E] 2xN Grid 题解

两个长度为 $L$ 的序列分别以邮码形式给出，求有多少个位置两个序列相同。邮码形式就是 $bbb\dots b$，设有 $a$ 个，则可记为 $b,a$。

如果能算出序列那就太简单了，但 $L\le 10^{12}$，显然过不了。它这样给出这个序列，我们可以考虑双指针。

两个序列各有一个指针 $la$ 和 $lb$，表示在两个序列的位置，每次记录所在区间的并集长度，然后哪个的结束位置更靠后哪个就向后一个位置。时间复杂度 $O(N1+N2)$。

计算区间的并集长度，将左端点的最大值、右端点的最小值构成的线段的长度记录即可。记得和 $0$ 取最大值。

代码：（应该算比较简洁的了）

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;const ll N=1e5+2;
ll len,n1,n2;char c;ll v[3][N],l[3][N],ans,h,i,j,la=1,lb=1;
inline ll read(){//快读
	c=getchar(),h=0;
	while(!(c>='0'&&c<='9'))c=getchar();
	while(c>='0'&&c<='9')h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h;
}
inline ll calc(ll l1,ll r1,ll l2,ll r2){//计算区间并集
	return max(0LL,min(r1,r2)-max(l1,l2)+1);
}
int main(){
	len=read(),n1=read(),n2=read();
	for(i=1;i<=n1;i++)
		v[1][i]=read(),l[1][i]=read(),l[1][i]+=l[1][i-1];//做前缀和才能知道区间左右端点
	for(i=1;i<=n2;i++)
		v[2][i]=read(),l[2][i]=read(),l[2][i]+=l[2][i-1];//同上
	for(;la<=n1&&lb<=n2;){//双指针
		if(l[1][la]<=l[2][lb])ans+=(v[1][la]==v[2][lb])*
			calc(l[1][la-1]+1,l[1][la],l[2][lb-1]+1,l[2][lb]),
			la++;//第一个序列区间更靠后
		else ans+=(v[1][la]==v[2][lb])*calc(l[1][la-1]+1,
			l[1][la],l[2][lb-1]+1,l[2][lb]),lb++;//第二个序列区间更靠后
	}
	return printf("%lld\n",ans),0;
}
```

---

## 作者：xwh_Marvelous (赞：1)

#### 题目大意

给两个特别长的序列，是由很多连续的相同数字组成的。所以表示为 $(v_i,l_i)$。其中 $v_i$ 表示第 $i$ 段的数字，$l_i$ 表示长度。保证 $\forall i, v_i\neq v_{i+1}$。两个序列分别拆成了 $n_1$ 和 $n_2$ 个这种段,需要求这两串相同位置的个数。

#### 思路

由于很长，暴力算法排除，考虑根据数字一段一段的特性来做。

显然发现对答案的贡献从数字变成了数字相同段的交集长度，两个序列中段与段的交集数不超过 $\max(n_1,n_2)$。

具体实现就是维护两个指针，每次加一段到指针小的一个序列，同时计算对答案的贡献并更新指针，重复这种操作即可。

[AC 代码](https://www.luogu.com.cn/paste/ko1y21ze)

---

## 作者：_dijkstra_ (赞：1)

题目大意可以通过阅读[原页面](https://atcoder.jp/contests/abc294/tasks/abc294_e)的样例解释迅速理解。

## 思路

用一个 $pos_i$ 维护一下转折点。也就是说 $pos_i \sim pos_{i+1}-1$ 的颜色都是 $val_i$。

于是把两段的 $pos_i$ 都一起放进一个数轴上（假设这个数轴是 $a$）。

那么对于当前位置的颜色就可以用**二分**很快求出来了。


如果颜色相同，这一段对答案的贡献应该就是 $a_i - a_{i-1}$。

另外数轴要记得往里面放 $0$，这样可以特判边界。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int val1[N]; ll pos1[N];
int val2[N]; ll pos2[N];
int main()
{
	ll sum, ans = 0;
	int n1, n2;
	scanf("%lld%d%d", &sum, &n1, &n2);
	vector <ll> vec; vec.push_back(0);
	for (int i = 1; i <= n1; i++) scanf("%d%lld", &val1[i], &pos1[i]), pos1[i] += pos1[i - 1], vec.push_back(pos1[i]);
	for (int i = 1; i <= n2; i++) scanf("%d%lld", &val2[i], &pos2[i]), pos2[i] += pos2[i - 1], vec.push_back(pos2[i]);
	sort(vec.begin(), vec.end());
	for (int i = 1, siz = vec.size(); i < siz; i++)
	{
		int col1 = val1[lower_bound(pos1 + 1, pos1 + n1 + 1, vec[i]) - pos1];
		int col2 = val2[lower_bound(pos2 + 1, pos2 + n2 + 1, vec[i]) - pos2];
		if (col1 == col2) ans += (vec[i] - vec[i - 1]);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：zzx0102 (赞：1)

赛时降智了，1h 才做掉。

首先，题目大意比较简单，这里不做任何解释。

暴力做法 1：

$O(L)$ 比较出所有点的两个颜色，计算相等个数即可。

由于 $L \leq 10^{12}$，不可取。

暴力做法 2：

由于暴力做法 1 有许多点相邻，所以考虑将相邻的节点合并成区间计算。

$O(n1\times n2)$ 枚举每个区间，当这两个区间颜色相等时，计算这两个区间的交集。

可是 $1\leq n1,n2\leq 10^5$，还是不行。

正解 1：

显然，当 $r_j<l_i$ 时，当 $k>i$，$l_k>r_j$。那么 $k$ 和 $j$ 没有交集。

双指针跳即可。

正解 2：

由于序列二最多只有 $10^5$ 种不同的颜色，考虑将这些颜色全部映射到 map 中，再将它们的 $l,r$ 全部存进 vector 中。

然后枚举序列一，将序列一中的所有与序列二颜色相同的全部计算一次交集，注意要二分左右端点，再计算，否则会 TLE on #31。

时效：1530ms（最慢的点 #31），考虑到时限 2s，所以还算不错。

```cpp
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
#define pb push_back
#define int long long
namespace SlowIO{
    I int read() {
        int x = 0; char ch = gc();
        W(ch < '0' || ch > '9') ch = gc();
        W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
        return x;
    }
    I void Read(int &x) {x = read();}
} using namespace SlowIO;
CI N = 100010;
int v1[N], v2[N], l1[N], le2[N], le1[N], r1[N], l2[N], r2[N];
int n, m, num; int Le, ans; map<int, int> mp; vector<int> v[2 * N];
int calc(int x, int y) {
	return min(r1[x], r2[y]) - max(l1[x], l2[y]) + 1;
}
signed main() {
	cin >> Le; Read(n, m); for(int i = 1; i <= n; i++) Read(v1[i], le1[i]);
	for(int i = 1; i <= m; i++) Read(v2[i], le2[i]); int sum = 0;
	for(int i = 1; i <= n; i++) l1[i] = sum + 1, r1[i] = sum + le1[i], sum += le1[i];
	sum = 0; for(int i = 1; i <= m; i++) l2[i] = sum + 1, r2[i] = sum + le2[i], sum += le2[i];
	for(int i = 1; i <= m; i++) if(!mp[v2[i]]) mp[v2[i]] = ++num;
	for(int i = 1; i <= m; i++) v[mp[v2[i]]].pb(i);
	for(int i = 1; i <= n; i++) {
		int l = 1, r = m, pos1 = -1;
		W(l <= r) {
			int mid = l + r >> 1;
			if(r2[mid] >= l1[i]) r = mid - 1, pos1 = mid;
			else l = mid + 1;
		}
		int L = 1, R = m, pos2 = -1;
		W(L <= R) {
			int mid = L + R >> 1;
			if(l2[mid] <= r1[i]) L = mid + 1, pos2 = mid;
			else R = mid - 1;
		}
		if(~pos1 && v2[pos1] == v1[i]) ans += calc(i, pos1);
		if(~pos2 && v2[pos2] == v1[i] && pos1 != pos2) ans += calc(i, pos2);
		for(int x: v[mp[v1[i]]])
			if(x > pos1 && x < pos2)
				ans += calc(i, x);
	}
	cout << ans << endl;
    return 0;
}
```

---

## 作者：JuRuoOIer (赞：0)

# 题解 [ABC294E] 2xN Grid


### Part1 题意

[传送门（洛谷）](https://www.luogu.com.cn/problem/AT_abc294_e)

[传送门（原站）](https://atcoder.jp/contests/abc294/tasks/abc294_e)

- 一个数组可以用下面这种方式表示：
  - 给定一些形如 `x y` 的东西，其中每个 `x y` 表示接下来有 $y$ 个 $x$。
- 现在用这种方式表示一个 $2 \times L$ 的数组，其中第一行可以分成 $N_1$ 段表示，第二行可以分成 $N_2$ 段表示。求有多少个 $1 \le i \le L$ 满足 $L_{1,i}=L_{2,i}$。
- 数据范围：
  - $1 \le L \le 10^12$
  - $1 \le N_1,N_2 \le 10^5$
  - $1 \le x \le 10^9$
  - $1 \le y \le L$，且所有的 $y$ 之和为 $L$。

### Part2 思路

首先我们肯定不能一个个枚举，这样时空复杂度均为 $\text{O}(L)$，直接 T 飞。

显然，**两段相交的部分要么都相等要么都不相等**，因为同一段里所有的数都是一样的。

发现段数较少（只有 $10^5$），我们可以以它为突破口，直接考虑把原数组分成若干段，使每一段均为某两段的相交部分，如果值相同就累加答案，这样就可以通过了。

### Part3 实现

实现的时候，我是准备了 $p1,p2$ 两个变量，分别记录第一行和第二行考虑到哪一段了。然后看两段中哪一段结束更早（边读入边预处理出来即可），用这一段结束的位置减去上次考虑的结束位置（初始为 $0$，一直统计）就是长度。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<string>
#define ll long long
#define ull unsigned long long
#define lf double
#define ld long double
using namespace std;
ll l,n,m,x,y,a1[100010],b1[100010],a2[100010],b2[100010],p1,p2,tmp,last,sum;
//a1,b1 分别表示第一行的各个 x,y;a2,b2 同理
//l,n,m 分别表示题目中的 L,N1,N2
//p1,p2 往上看
//tmp 当前考虑的结束位置 last 上次考虑的结束位置 两个变量均用于求长度
//sum 统计答案 
int main(){
	cin>>l>>n>>m;
	//初始化，方便后续计算 
	b1[0]=1;
	b2[0]=1;
	//读入 
	for(int i=0;i<n;i++){
		cin>>x>>y;
		//预处理结束位置 
		b1[i+1]=b1[i]+y;
		a1[i]=x;
	}
	for(int i=0;i<m;i++){
		cin>>x>>y;
		//同上 
		b2[i+1]=b2[i]+y;
		a2[i]=x;
	}
	while(p1<n&&p2<m){//两边都没考虑完 
		last=tmp;//注意更新 last 
		if(b1[p1+1]<b2[p2+1]){//第一行考虑的区间结束更早 
			tmp=b1[p1+1]-1;//记录结束位置 
			if(a1[p1]==a2[p2]){//相等则统计答案 
				sum+=tmp-last;
			}
			p1++;//移动位置 
		}
		else{//同理 
			tmp=b2[p2+1]-1;
			if(a1[p1]==a2[p2]){
				sum+=tmp-last;
			}
			p2++;
		}
	}
	//输出答案 
	cout<<sum;
	return 0;
}
```

---

## 作者：OIerBoy (赞：0)

## 分析
这道题是一道 $O(N_1+N_2)$ 的模拟题。我们只需要维护两组指针去不断指向区间 $a_i,a_j$ 左右端点 $v_{1,i},l_{1,i}$ 与 $v_{1,j},l_{1,j}$，并判断区间 $a_i,a_j$ 重叠部分是否数值是否相等，如果数值是相等的就累加答案。然后将两块区间中较后的区间向前推动就可以了。这里当两组指针指向区间 $a_{N1},a_{N2}$ 时就退出循环。

具体细节请参考代码。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define Mod 1000000007
using namespace std;
int L,n,m,a[1000005][3],b[1000005][3],l,r,h,t,ans;
//a数值表示i=1段每个区间左右端点
//b数值表示i=2段每个区间左右端点
//l,r表示i=1段指向的区间左右端点
//h,t表示i=2段指向的区间左右端点
//ans表示答案
signed main(){
	cin>>L>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i][1]>>a[i][2];
	for(int i=1;i<=m;i++)cin>>b[i][1]>>b[i][2];
	int i=0,j=0;//区间a_i,a_j的指针
	l=1,h=1,r=a[++i][2],t=b[++j][2];
	while(t!=L||r!=L){	//判断结束循环
		if(a[i][1]==b[j][1])ans+=max(min(t,r)-max(l,h)+1,0ll);//累加答案
        	//将两块区间中较后的区间向前推动
		if(l<h)//判断是否重叠
			if(t<r)h+=b[j][2],t+=b[++j][2];
			else l+=a[i][2],r+=a[++i][2];
		else
			if(t<r)h+=b[j][2],t+=b[++j][2];
			else l+=a[i][2],r+=a[++i][2];
	}if(a[i][1]==b[j][1])ans+=max(min(t,r)-max(l,h)+1,0ll);//累加最后一次答案
	cout<<ans;
	return 0;
}
```

---

## 作者：programmer2048 (赞：0)

## 简要题意

给定两个长度为 $L$ 的序列 $A,B$，求满足 $A_i=B_i$ 的 $i$ 的数量。

## 思路分析

在本题的输入样例中，序列被压缩为了一些由相同元素组成的子序列，如序列 $\{2,2,2,2\}$ 就用 $2,4
$ 表示，其中前者是其元素，后者是其长度。

受此启发，我们可以将两个序列抽象为两个由线段组成的集合，每条线段都有其位置信息与它的代表数字。从两个线段集合中分别取出两条线段 $a,b$，若 $a,b$ 的代表数字相同并且存在重合部分，那么答案就累加其重合部分的长度。

由于两个线段集合中线段的左右端点都单调不降，所以我们可以使用双指针算法解决这个问题。

## AC代码
```cpp
#include<iostream>
using namespace std;
using LL = long long;
const int N = 100010;
struct Node{LL l,r,val;};//左右端点的位置可能会爆int，所以要开LL。
LL len,n1,n2,v,l,Left,ans;
int p=1,q=1;
Node a[N],b[N];
int main()
{
    cin>>len>>n1>>n2;
    Left=1;
    for(int i=1;i<=n1;i++)cin>>v>>l,a[i]={Left,Left+l-1,v},Left+=l;
    Left=1;
    for(int i=1;i<=n2;i++)cin>>v>>l,b[i]={Left,Left+l-1,v},Left+=l;
    while(p<=n1 && q<=n2)
    {
        //可以保证被扫描到的两线段间存在重合部分，且对应的重合部分长度只会被计算一次。
        if(a[p].val==b[q].val)ans+=min(a[p].r,b[q].r)-max(a[p].l,b[q].l)+1;
        if(a[p].r<b[q].r)p++;
        else q++;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Qinzh (赞：0)

# ABC294E

## 题意

现有两个长度为 $ l $ 的数组。

他们分别被压缩成了长度为 $ n1 $, $ n2 $ 的压缩数组。

第一个压缩数组表示为 $ (v_{1, 1}, l_{1, 1}), (v_{1, 2}, l_{1, 2}), (v_{1, 3}, l_{1, 3}), ...,(v_{1, n1}, l_{1, n1}) $。

其中 $ (v_{1, i}, l_{1, i}) $ 表示 $ l_{1, i} $ 个连续的 $ v_{1, i}$。

第二个压缩数组表示为 $ (v_{2, 1}, l_{2, 1}), (v_{2, 2}, l_{2, 2}), (v_{2, 3}, l_{2, 3}), ...,(v_{2, n2}, l_{2, n2}) $。

其中 $ (v_{2, i}, l_{2, i}) $表示 $ l_{2, i} $ 个连续的 $ v_{2, i} $。

要求把这两个压缩序列展开，求这两个数组对应位置元素相同的个数。

## 解释

如 $ (1, 2), (2, 3) $ 展开即为 $ 1, 1, 2, 2, 2 $。

 $ (1, 4) , (2, 1) $ 展开即为 $ 1, 1, 1, 1, 2 $。
 
第 $ 1 , 2 , 5 $ 的对应位置上元素相同，则最终答案为 $3$。

## 分析

~~这题一眼暴力拆开模拟即可， 怎么能放到 E 题上~~

艹，$ 1 \leqslant l \leqslant 10^{12}$

于是我们考虑双指针法。

我们记录 $i$ 和 $j$ 为两个序列的指针，即它们分别枚举到哪里。最开始它们都在1的位置，现在对于每一组 $i$ 和 $j$，我们都可以找到一组对应的压缩块 $A$, $B$，把 $A$ 和 $B$ 解压并把前 $\min{(l_{1, i},l_{2, i})}$ 长度的元素展开，我们可以发现，如果 $l_{1, i}=l_{2, i}$，那么答案就要加上这些长度的元素，否则就不加。然后我们再把这些已经进行对比过的元素“删掉”，这里的删掉其实就是把两个指针 $i$ 或者 $j$ 往后走一步，具体走哪一个可以这样判断： 

若压缩块 $A$ 压缩为 $0$（即 $ cnt1 = 0 $）则 $i$ 向前走一步， 更新 $cnt1$ 为 $ l_{1, i} $。

若压缩块 $B$ 压缩为 $0$（即 $ cnt2 = 0 $）则 $j$ 向前走一步， 更新 $cnt2$ 为 $ l_{2, j} $。

不断枚举下去直到有一个压缩数组枚举完毕终止即可，时间复杂度 $ O(n) $。

具体实现见代码。
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define gt getchar
#define pt putchar
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=gt();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=gt();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=gt();}
	return x*f;}//快读
ll l, n, m;//超过1e12用long long
struct node{
	ll x, l;
}a[100005], b[100005];//压缩数组A， B
int main(){
	l = read(), n = read(), m = read();
	for(int i = 1; i <= n; ++i)a[i].x = read(), a[i].l = read();
	for(int i = 1; i <= m; ++i)b[i].x = read(), b[i].l = read();
	ll i = 1, j = 1;
	ll cnt1 = a[1].l, cnt2 = b[1].l;//初始枚举
	ll ans = 0;
	while(i <= n && j <= m){//一个数组伸展完就没有继续判断的必要了
		//cout << "i " << i << " j " << j << endl;//调试qwq
		if(a[i].x == b[j].x)ans += min(cnt1, cnt2);//统计
		ll v = min(cnt1, cnt2);//千万开一个变量现存最小值，直接写就会出现酱汁错误
		cnt1 -= v, cnt2 -= v;
		if(cnt1 == 0)++i, cnt1 = a[i].l;//更新cnt1
		if(cnt2 == 0)++j, cnt2 = b[j].l;//更新cnt2
	}
	cout << ans;//输出
	return 0;
}

```


---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc294_e)
### 题解（二分+思维）
思路较为简单，就是把每一个数字变化的位置进行分割，然后判断每一个分割后的区间颜色是否相等。

这里讲一下如何判断分割后，一个位置 $x$ 的颜色。

首先二分出最大的起点小于等于 $x$ 的位置。
然后这个位置就是涵盖 $x$ 的位置，所以 $x$ 的颜色就是这个位置的颜色。

上下两排都是如此。

再讲一下怎么分割：
以以下图为例：

![](https://img.atcoder.jp/abc294/14f38720983c464a322b504738344f24.png)

第一排颜色不同的位置有 $1,3,5,8$，第二排有 $1,5,6$，所以所有要分割的位置就是 $1,3,5,7,8$。也就是说，要判断答案的区间分别为 $[1,3),[3,5),[5,6),[6,8),[8,9)$。

由于区间里的有边界是开区间，所以我们还要额外加一个位置 $l+1$，在这里就是 $9$。
### 代码
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair <LL,LL> PII;
const int N = 100010;
LL l;
int n1,n2;
PII a[N],b[N];
LL sa[N],sb[N];
vector <LL> v;
int main () {
	cin >> l >> n1 >> n2;
	LL s = 0;
	for (int i = 1;i <= n1;i++) {
		cin >> a[i].x >> a[i].y;
		sa[i] = s + 1;
		v.push_back (s + 1);
		s += a[i].y;
	}
	s = 0;
	for (int i = 1;i <= n2;i++) {
		cin >> b[i].x >> b[i].y;
		sb[i] = s + 1;
		v.push_back (s + 1);
		s += b[i].y;
	}
	sa[n1 + 1] = l + 1,sb[n2 + 1] = l + 1;
//	puts ("-----------");
//	for (int i = 1;i <= n1;i++) cout << sa[i] << ' ';
//	cout << endl;
//	for (int i = 1;i <= n2;i++) cout << sb[i] << ' ';
//	cout << endl;
	v.push_back (l + 1);
	sort (v.begin (),v.end ());
	v.erase (unique (v.begin (),v.end ()),v.end ());
	LL ans = 0;
//	for (LL x : v) cout << x << ' ';
//	cout << endl;
	for (int i = 0;i < v.size () - 1;i++) {
		LL x = v[i];
		int l = 1,r = n1 + 1;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (sa[mid] <= x) l = mid;
			else r = mid - 1;
		}
		int pa = l;
		l = 1,r = n2 + 1;
		while (l < r) {
			int mid = l + r + 1 >> 1;
			if (sb[mid] <= x) l = mid;
			else r = mid - 1;
		}
		int pb = l;
//		cout << "num = " << x << "    " << '[' << v[i] << ',' << v[i + 1] << ')' << "--------" << a[pa].x << ' ' << b[pb].x << endl;
//		cout << pa << ' ' << pb << endl;
//		cout << (sb[pb] <= x) << ' ' << (sb[pb + 1] <= x) << endl;
		if (a[pa].x == b[pb].x) ans += v[i + 1] - v[i];
	}
	cout << ans << endl;
    return 0;
}
```

---

## 作者：快乐的大童 (赞：0)

### 题目大意
给定一个 $2$ 行 $L$ 列的矩阵 $A$，求出满足 $1\le i\le L,A_{1,i}=A_{2,i}$ 的 $i$ 的数量。

但由于 $L$ 太大了，所以我们将 $A$ 的每一行用若干个段表示出来。

对于第一行，我们将其分成 $n_1$ 个段，第 $i$ 个段的颜色是 $V_{1,i}$，长度是 $L_{1,i}$。$V_1,L_1$ 的长度均为 $n_1$。

对于第二行，我们将其分成 $n_2$ 个段，第 $i$ 个段的颜色是 $V_{2,i}$，长度是 $L_{2,i}$。$V_2,L_2$ 的长度均为 $n_2$。

$1\le L\le 10^{12},1\le n_1,n_2\le 10^5$，$1\le V_{1/2,i}\le 10^9,\sum_{i=1}^{n_1}L_{1,i}=\sum_{i=1}^{n_2}L_{2,i}=L$。


### 思路


由于两行造成的贡献具有单调性（即对于两个点 $i,j$，他们所能造成贡献的点 $w_i,w_j$ 一定满足 $w_i\le w_j$），所以我们考虑先控制其中一行所到段数，对于另一行，不断向右移动直到另一行所到段数的终点远于被控制的一行所到段数的终点，在此之间计算这些段对当前被控制行所移动到的段造成的贡献即可。

注意对于未控制行的某一段，它可能会对被控制行的多个段造成贡献，所以我们在在被控制行移动段后，要先特判先前移动到的段对此段的贡献，在在未控制行上移动段。


### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int R(){
	int x=0,f=1;int ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x*f;
}
inline void write(int x){
	if(x<0){x=-x;putchar('-');}
	int y=0;char z[70];
	while(x||!y){z[y++]=x%10+48;x/=10;}
	while(y--)putchar(z[y]);
}
#define rep(a,b,c) for(int a=b;a<=c;a++)
const int maxn=2e5+5;
int L,n1,n2;
int v[maxn][2],l[maxn][2];
int jiao(int x1,int y1,int x2,int y2){//计算线段交
	if(x1>x2) swap(x1,x2),swap(y1,y2);
	if(y1<x2) return 0;
	else return y1-x2+1-(y2<=y1?y1-y2:0);//注意这里答案要额外加上1
}
void solve_the_problem(){
	L=R(),n1=R(),n2=R();
	rep(i,1,n1) v[i][0]=R(),l[i][0]=R();
	rep(i,1,n2) v[i][1]=R(),l[i][1]=R();
	int now=0,ans=0;
	int lena=0,lenb=0;
	rep(i,1,n1){//移动被控制行
		int lst=lena+1;
		lena+=l[i][0];
		if(now&&v[now][1]==v[i][0]) ans+=jiao(lenb-l[now][1]+1,lenb,lst,lena);
		while(lenb<lena&&now<=n2){//移动未控制行
			int llst=lenb+1;
			lenb+=l[++now][1];
			if(v[now][1]==v[i][0]) ans+=jiao(llst,lenb,lst,lena);
		}
	}
	write(ans);
}
signed main(){int _=1;while(_--)solve_the_problem();}

```


---

## 作者：六楼溜刘 (赞：0)

## 题解
题意不多赘述（其实是我不知道怎么概括￣□￣｜｜）

我们可以把 $a_1$ 中读入的每个区间左右端点和颜色存下来，按左端点排序，然后用一个指针维护，$a_2$ 中每读入一个区间，就把指针右移到合适的位置进行计算，由于区间不重合，所以 $a_1$ 中每个区间只会被访问一次，复杂度 $O(N_1+N_2)$。具体见代码。

## code

```cpp
#include<iostream>
#include<algorithm>
#include<map>
#define int long long
#define fi first
#define se second
#define mkp(a,b) make_pair(a,b)
#define forup(i,s,e) for(register int i=(s);i<=(e);i++)
#define fordown(i,s,e) for(register int i=(s);i>=(e);i--)
using namespace std;
#define gc getchar()
inline int read(){//快读
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
using pii=pair<int,int>;
const int N=1e5+5,inf=0x3f3f3f3f;
int l,n1,n2,sum,ans;
map<pii,int> mp;//我用 map 存的
signed main(){
	l=read();n1=read();n2=read();
	forup(i,1,n1){
		int v=read(),len=read();
		mp[mkp(sum+1,sum+len)]=v;
		sum+=len;
	}
	auto it=mp.begin();
	sum=0;
	forup(i,1,n2){
		int v=read(),len=read();
		while(it->fi.se<sum+1) ++it;//右移
		if(it==mp.end()) break;//如果访问到边界直接退出
		if(it->se==v){
			ans+=min(it->fi.se,sum+len)-max(it->fi.fi,sum+1)+1;
		}
		while(it->fi.se<sum+len){//有可能覆盖多个区间
			++it;
			if(it==mp.end()) break;
			if(it->fi.fi<=sum+len&&it->se==v){
				ans+=min(it->fi.se,sum+len)-max(it->fi.fi,sum+1)+1;
			}		
		}
		sum+=len;	
	}
	printf("%lld",ans);
}
```


---

## 作者：SlyCharlotte (赞：0)

[或许更好的阅读体验？](https://zhuanlan.zhihu.com/p/615414755)
### 题意描述

给你长度为 $L$ 的两个数组，求出 $i$ 的数量满足 $a_i = b_i$。

$(a,b)$ 指连续的 $b$ 个元素的值为 $a$。

### 简要分析

发现长度为 $10^{12}$，但是每个数组的块只有 $10^5$ 个，于是考虑枚举块。

维护两个指针指向两个数组的块，然后暴力枚举迭代指针即可。

时间复杂度 $O(n)$。

### 代码实现

```cpp
void solve() {
    ccin >> L >> n >> m;
    ll res = 0;
    for (int i = 1; i <= n; i++)ccin >> a[i] >> b[i];
    ll l;
    for (int v, tp = 1; m--;) {
        ccin >> v >> l;
        while (l) {
            ll len = min(l, b[tp]);
            if (v == a[tp])res += len;
            b[tp] -= len, l -= len;
            if (!b[tp])++tp;
        }
    }
    printf("%lld\n", res);
}
```

## 

---

## 作者：Butterfly___qwq (赞：0)

# 简述
这道题在考试中没有做出来，仅有 $7$ 秒之差，否则长大分！
# 题意
对于两行数，对他们的描述有 $n1,n2$ 条，每一条都是一个数 $x$ 加上这个数持续长度 $y$，比如说 `2 3` 代表的就是 `2 2 2`。
# 思路一
开两个数组，根据题目描述赋值，然后发现 $n1,n2 \leq 5 \times 10^5$，于是放弃了这种做法。
# 思路二
考虑维护两个双端队列，每个队列中的元素分别存两个值，是一个数字和他的持续长度，每次取出队首元素并弹出，如果元素的第一个值相同，则答案加上他们持续长度较小的一个，最后，两个长度还要减去较小的一个，以便于再次进行比较，如果不为 $0$，则重新返回队列。
# 警告
- 要用 `deque`，不用 `queue`！
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#include<queue>
deque <pair<long long,long long> > pq1,pq2;
int main(){
	long long l,n1,n2,a,b,ans=0;
	cin>>l>>n1>>n2;
	for(int i=1;i<=n1;i++)cin>>a>>b,pq1.push_back({a,b});
	for(int i=1;i<=n2;i++)cin>>a>>b,pq2.push_back({a,b});
	while(!pq1.empty()){
		long long t1=pq1.front().first;
		long long t2=pq2.front().first;
		long long x1=pq1.front().second;
		long long x2=pq2.front().second;
		long long t=min(x1,x2);
		x1-=t,x2-=t;
		pq1.pop_front(),pq2.pop_front();
		if(t1==t2)ans+=t;
		if(x1)pq1.push_front({t1,x1});
		if(x2)pq2.push_front({t2,x2});
	}cout<<ans;
	return 0;
}

```

---

