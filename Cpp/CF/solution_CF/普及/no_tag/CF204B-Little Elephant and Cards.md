# Little Elephant and Cards

## 题目描述

The Little Elephant loves to play with color cards.

He has $ n $ cards, each has exactly two colors (the color of the front side and the color of the back side). Initially, all the cards lay on the table with the front side up. In one move the Little Elephant can turn any card to the other side. The Little Elephant thinks that a set of cards on the table is funny if at least half of the cards have the same color (for each card the color of the upper side is considered).

Help the Little Elephant to find the minimum number of moves needed to make the set of $ n $ cards funny.

## 说明/提示

In the first sample there initially are three cards lying with colors 4, 4, 7. Since two of the three cards are of the same color 4, you do not need to change anything, so the answer is 0.

In the second sample, you can turn the first and the fourth cards. After that three of the five cards will be of color 7.

## 样例 #1

### 输入

```
3
4 7
4 7
7 4
```

### 输出

```
0
```

## 样例 #2

### 输入

```
5
4 7
7 4
2 11
9 7
1 1
```

### 输出

```
2
```

# 题解

## 作者：NY_An18623091997 (赞：2)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF204B)  
有 $n$ 张牌，每张牌正反两面都有 $a,b$ 两种颜色，最开始每张牌都正面朝上。求最少需要翻转多少次才能使得一半以上的牌朝上的面颜色相同。如果无法实现则输出 $-1$。
## 思路
首先我们可以想到把每种颜色出现的次数存在数组里，但是 $1 \le a_i,b_i \le 1\times 10^9$，不过用 map 就可以解决这个问题。  
计算一个颜色出现的次数时，反面的颜色也要加进正面里，因为这张牌可以通过翻转交换使得反面朝上。如果两面颜色相同，那么只加一遍。  
然后我们可以用队列来存出现过的颜色，方便枚举。在枚举的时候，当所有牌两面颜色为队首颜色的张数大于等于 $ \displaystyle \frac{n}{2}$ 且所有牌反面颜色为队首颜色的张数大于等于 $ \displaystyle \frac{n}{2}$ 时，不需要任何翻转就能使一半以上的牌朝上的面颜色相同，输出 $0$。  
如果这种颜色在牌堆中出现的次数大于等于 $ \displaystyle \frac{n}{2}$，则更新 $ans$，在 $ans$ 和 $\displaystyle \frac{n}{2}\ -$ 这种颜色在牌堆中出现的次数取最小值。  
最后，当 $ans$ 为初始值时（初始化为正无穷），无解，输出 $-1$，反之输出 $ans$。
## AC code
```cpp
#include<bits/stdc++.h>
#pragma G++ optimize(1)
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#define ll long long
using namespace std;
const int N=1e5+3;
ll n,m,a,b,ans=0x3f3f3f3f3f3f3f3f;
map<ll,ll> mz,mf;//mz标记正面的颜色，mf标记反面的颜色
queue<ll> q; 
int main(){
	scanf("%d",&n);
	m=(n+1)/2;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		if(a!=b){
			mz[a]++;
			mf[a]++;
			mz[b]++;
		}
		else{//颜色相同时，只加一遍
			mz[a]++;
			mf[a]++;
		}
		q.push(a),q.push(b);
	}
	while(!q.empty()){//枚举每种出现过的颜色是否可能符合条件
		if(mz[q.front()]>=m&&mf[q.front()]>=m){
			printf("0");
			exit(0);
		}
		if(mz[q.front()]>=m)	ans=min(ans,m-mf[q.front()]);//更新ans
		q.pop();
	}
	if(ans==0x3f3f3f3f3f3f3f3f)	printf("-1");//如果ans没有更新，输出-1
	else						printf("%d",ans);//否则输出ans
	return 0;
}
```
###  [AC记录](https://www.luogu.com.cn/record/166198736)

---

## 作者：Hellen68 (赞：2)

# CF204B

## 题目大意
有 $n$ 张卡牌，每张卡牌有正面和反面，每一面都会有它的颜色。

现在，每一张卡牌都正面朝上，我们可以通过翻卡牌，使得卡牌朝上的颜色发生变化。那么至少需要翻多少次才能使得所有卡牌中，有至少一半的卡牌朝上的颜色相同。

### 需要注意的点
- 1.有的卡牌可能**正反面颜色相同**
- 2.如果卡牌总数量 $n$ 是奇数，那么一半的定义为 $\frac{n + 1}  2$

## 题解

### Step.1 统计
如果要让至少一半的卡牌朝上颜色相同，那得先保证某种颜色的数量（排除正反面颜色相同的情况）至少有一半吧。

#### 举个栗子
```
3
1 2
3 4
5 6
```
如果给你这样的数据，那就妥妥的输出 $-1$ 了

其实我们可以用两个桶，记录一下每个数一共出现了多少次和初始时，每个数位于卡牌**背面**的数量。

#### 代码实现
```cpp
int a[maxn] , b[maxn];// a数组是每个数一共出现的次数，b数组是每个数位于卡牌背面的数量
cin >> x >> y;// x：正面颜色，y：反面颜色
a[x] ++;// 总的颜色数量统计 
if(x != y) {// 这里要特判正反面颜色是否相同，如果相同的话，那么这张牌翻在正面还是反面就都一样了，直接假设它反面没有颜色就行 
	a[y] ++;
	b[x] ++;
	// 如果不相同，再做统计 
}
```

### Step.2 做翻牌处理
我们通过刚才的统计，发现了一些能通过翻牌符合题目要求的颜色，现在需要翻牌了。

我们知道了总颜色数量和背面颜色数量，拿总的减去背面的，就是正面的了！

如果正面的数量 $\geq{\frac{n + 1}2}$ ，那就不用翻了，直接答案是 0 就得了； 

如果小于，那就翻掉一些反面的牌让期望的颜色回到正面。

其实翻掉 ${\frac{n + 1}2}-(a[i] - b[i])$ 张牌就够了，这样正好一半的牌。

然后拿上面那个式子取最小值就 ok 。

#### 代码实现
```cpp
if(a[i] >= (n + 1) / 2) {
	if(a[i] - b[i] < (n + 1) / 2) {
		minn = min(minn , (n + 1) / 2 - (a[i] - b[i]));
	}
	else minn = 0;
}
```
### Step.3 离散化
我们风风火火干了这么些事情，一看数据范围： What ？？颜色值 $\le10^9$ ？？？难不成还得开一堆 map 统计数量？！

不至于吧！

$n\le10^5$ ，就算卡牌颜色没有重样的，也不可能多到 $10^9$ ，顶多 $2\times10^5$ 啊！

这样我们没必要大费周章开 map 了，给不同颜色一个编号，统计一下有多少种颜色出现过，拿编号去作为颜色代号，参与后面的处理就行了！

#### 代码实现
这里只截了输入部分，但离散化需要贯穿全篇代码哦~

```cpp
for(int i = 1 ; i <= n ; ++ i) {
	int x , y;
	cin >> x >> y;
	if(mp[x] == 0) mp[x] = ++ cnt;// 如果这种颜色没有出现过，把它注册一下，下同。
	if(mp[y] == 0) mp[y] = ++ cnt;
	a[mp[x]] ++;// 拿颜色代号去做处理。
	if(x != y) {
		a[mp[y]] ++;
		b[mp[y]] ++;
	}
}
```

## 完整代码

```cpp
#include <bits/stdc++.h>
#define long long int// 这里把long long 注册成 int，main函数要用signed
using namespace std;
const int maxn = 2e5 + 5;
int n;
map <int , int> mp;
int cnt;
int a[maxn] , b[maxn];
int minn = 1e9 + 7;
signed main() {
	//freopen(".in" , "r" , stdin);
	//freopen(".out" , "w" , stdout);
	cin >> n;
	for(int i = 1 ; i <= n ; ++ i) {
		int x , y;
		cin >> x >> y;
		if(mp[x] == 0) mp[x] = ++ cnt;
		if(mp[y] == 0) mp[y] = ++ cnt;
		a[mp[x]] ++;
		if(x != y) {
			a[mp[y]] ++;
			b[mp[y]] ++;
		}
	}
	for(int i = 1 ; i <= cnt ; ++ i) {
		if(a[i] >= (n + 1) / 2) {
			if(a[i] - b[i] < (n + 1) / 2) {
				minn = min(minn , (n + 1) / 2 - (a[i] - b[i]));
			}
			else minn = 0;
		}
	}
	if(minn == 1e9 + 7) cout << "-1" << endl;
	else cout << minn << endl;
	return 0;
}



```
求管理通过 QAQ

本蒟蒻的第一篇题解，大家觉得不错就点个赞呗 $\sim$

---

## 作者：123456zmy (赞：1)

题意：  
你有 $n$ 张牌，每张的两面都有颜色，问要使其中至少一半的排正面颜色相同，至少需要翻几张牌。
___
首先，至少要有一种颜色出现在至少一半的牌上，所以可以统计正反面的颜色数量，如果正反颜色相同则不计反面（因为翻了还不如不翻）。然后对于所有出现总次数不少于  $(n+1)/2$ 的颜色统计答案并维护最小值，最后判一下无解输出，记得加离散化。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ansz[200001],ansf[200001],z,f,ans=0x3f3f3f3f,an;
map<int,int>a;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&z,&f);
		if(!a[z])a[z]=++an;
		if(!a[f])a[f]=++an;
		++ansz[a[z]];
		if(z!=f)++ansf[a[f]];
	}
	for(int i=1;i<=an;i++)if(ansz[i]+ansf[i]>=(n+1>>1))ans=min(ans,(n+1>>1)-ansz[i]);
	if(ans==0x3f3f3f3f)printf("-1");
	else printf("%d",max(ans,0));
	return 0;
}
```

---

## 作者：czh___ (赞：0)

题意：

给你 $n$ 张卡片，每张卡片都有正反 $a$，$b$ 两种颜色，问你至少需要反转多少次才能使正面的一样的颜色超过一半以上。

思路：

统计下每种颜色的个数，只有当一种颜色的个数 $\ge  \frac{(n+1)}{2}$ 时我们才考虑它，然后判定下该颜色在正面的个数是否 $\ge \frac{(n+1)}{2}$ 如果大于不需要反转，如果小于则需要反转至少 $\frac{(n+1)}{2} -$在正面的个数，然后不断维护这个的最小值。

代码：

```cpp
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
 
const int INF=0x3f3f3f3f;
const int MAX=1e5+5;
int n,a[MAX],b[MAX];
map<int,int> sum,l;
 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		sum[a[i]]++;
		if(a[i]!=b[i]) sum[b[i]]++;
		l[a[i]]++;
	}
	int ans=INF,Max=(n+1)/2;
	for(int i=1;i<=n;i++){
		if(sum[a[i]]>=Max){
			if(l[a[i]]>=Max){
				ans=0;
				break;
			}
			else ans=min(ans,Max-l[a[i]]);
		}
		if(sum[b[i]]>=Max){
			if(l[b[i]]>=Max){
				ans=0;
				break;
			}
			else ans=min(ans,Max-l[b[i]]);
		}
	}
	if(ans!=INF) printf("%d\n",ans);
	else printf("-1\n");
	return 0;
}
```

[改编于](https://blog.csdn.net/w446506278/article/details/52067938?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522FE80035A-7417-40D3-9909-FDD5476A4AB8%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=FE80035A-7417-40D3-9909-FDD5476A4AB8&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-52067938-null-null.142^v100^pc_search_result_base8&utm_term=Little%20Elephant%20and%20Cards&spm=1018.2226.3001.4187)

---

## 作者：Escapism (赞：0)

[题目](https://www.luogu.com.cn/problem/CF204B)

# 题意

有 $n$ 张卡片，每张卡片有两面，每面都有一种颜色（有可能是不同的，也可能是相同的）。初始时每张卡片都是正面朝上。

现在问至少要给几张卡片翻面，才能使所有卡片上面有一种颜色超过一半。

# 思路

首先考虑输出 $-1$ 的情况。如果没有任何一种颜色（正面反面都包括），超过卡片数量的一半，那么就是不可能的，即输出 $-1$。

如果目标是可能达成的，那么我们就统计翻牌的数量。为了保证翻牌的数量最少，我们显然会选择出现次数最多的那种颜色来作为超过一半的颜色。

如果这种颜色在正面就已经超过了一半，那么就输出 $0$，毕竟没有翻面就已经符合条件了。反之我们就需要考虑翻面的数量。

另外有一点要注意的是，卡片的颜色数量**范围达到了 $10^9$**，我们开桶计数的时候显然不能做到开这么多的桶。因而我们需要一种新的编号来统计颜色。

由于卡的数量至多只有 $10^5$，极限情况下也只会有 $2\times 10^5$ 种颜色，对于新的编号来说绰绰有余。

# 代码

```cpp
#include <bits/stdc++.h>
#define long long int //开 long long
using namespace std;

const int MAXN = 2e5 + 5,INF = 0x3f3f3f3f;
int n;
map <int,int> MP; //用来存储颜色与其编号的映射
int cnt;
int a[MAXN],b[MAXN],minn = INF;

signed main() {
	cin >> n;
	for(int i = 1;i <= n;i++) {
		int x,y;
		cin>>x>>y;
		if(MP[x] == 0) MP[x] = ++cnt;
		if(MP[y] == 0) MP[y] = ++cnt; //遇到新的颜色就要新的编号
		a[MP[x]]++; //记录数量
		if(x != y) { //颜色不同就统计两次，反之就只统计一次，因为对于两面颜色相同的牌翻面没有意义
			a[MP[y]]++;
			b[MP[y]]++;
		}
	}
	for(int i = 1;i <= cnt;i++) {
		if(a[i] >= (n + 1) / 2) { //过半
			if(a[i] - b[i] < (n + 1) / 2){ //统计正面
				minn = min(minn,(n + 1) / 2 - (a[i] - b[i]));
			}
			else minn = 0;
		}
	}
	if (minn == INF) cout << "-1" << endl;
	else cout << minn << endl;
	return 0;
}


```


---

## 作者：Su_Zipei (赞：0)

首先根据样例可以知道，一半的卡牌中的一半是要上取整的，容易发现如果一种颜色一共出现的次数都少于卡牌的一半，那这种颜色一定不可能是最后答案，所以只需要在出现次数大于卡牌的一半的颜色中取反转次数最少的卡牌输出即可。
```cpp
/*
3
4 7
4 7
7 4
*/
#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int q[N],tt;
map<int,int> cnt1,cnt2;
int main(){
	int n;
	scanf("%d",&n);
	int s=n+1>>1;
	for(int i=1;i<=n;i++){
		int	x,y;
		scanf("%d%d",&x,&y);
		cnt1[x]++;
		if(x!=y)cnt1[y]++;
		cnt2[x]++;
		q[++tt]=x;q[++tt]=y;
	}
	int res=0x7f7f7f7f;
	for(int i=1;i<=tt;i++){
		if(cnt1[q[i]]>=s&&cnt2[q[i]]>=s)return puts("0"),0;
		if(cnt1[q[i]]>=s)res=min(res,s-cnt2[q[i]]);
	}
	if(res==0x7f7f7f7f)puts("-1");
	else printf("%d\n",res);
	return 0;
}

```

---

