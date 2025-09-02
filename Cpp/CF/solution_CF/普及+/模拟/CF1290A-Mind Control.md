# Mind Control

## 题目描述

You and your $ n - 1 $ friends have found an array of integers $ a_1, a_2, \dots, a_n $ . You have decided to share it in the following way: All $ n $ of you stand in a line in a particular order. Each minute, the person at the front of the line chooses either the first or the last element of the array, removes it, and keeps it for himself. He then gets out of line, and the next person in line continues the process.

You are standing in the $ m $ -th position in the line. Before the process starts, you may choose up to $ k $ different people in the line, and persuade them to always take either the first or the last element in the array on their turn (for each person his own choice, not necessarily equal for all people), no matter what the elements themselves are. Once the process starts, you cannot persuade any more people, and you cannot change the choices for the people you already persuaded.

Suppose that you're doing your choices optimally. What is the greatest integer $ x $ such that, no matter what are the choices of the friends you didn't choose to control, the element you will take from the array will be greater than or equal to $ x $ ?

Please note that the friends you don't control may do their choice arbitrarily, and they will not necessarily take the biggest element available.

## 说明/提示

In the first test case, an optimal strategy is to force the first person to take the last element and the second person to take the first element.

- the first person will take the last element ( $ 5 $ ) because he or she was forced by you to take the last element. After this turn the remaining array will be $ [2, 9, 2, 3, 8] $ ;
- the second person will take the first element ( $ 2 $ ) because he or she was forced by you to take the first element. After this turn the remaining array will be $ [9, 2, 3, 8] $ ;
- if the third person will choose to take the first element ( $ 9 $ ), at your turn the remaining array will be $ [2, 3, 8] $ and you will take $ 8 $ (the last element);
- if the third person will choose to take the last element ( $ 8 $ ), at your turn the remaining array will be $ [9, 2, 3] $ and you will take $ 9 $ (the first element).

Thus, this strategy guarantees to end up with at least $ 8 $ . We can prove that there is no strategy that guarantees to end up with at least $ 9 $ . Hence, the answer is $ 8 $ .

In the second test case, an optimal strategy is to force the first person to take the first element. Then, in the worst case, both the second and the third person will take the first element: you will end up with $ 4 $ .

## 样例 #1

### 输入

```
4
6 4 2
2 9 2 3 8 5
4 4 1
2 13 60 4
4 1 3
1 2 2 1
2 2 0
1 2```

### 输出

```
8
4
1
1```

# 题解

## 作者：乐哥 (赞：10)

### 题意：一串数共n个，排成一列，有n次操作对数进行，每次去数列的第一个或最后一个。现在你要操作的是第m次，并且你可以控制任意k次操作的选择。问你在最优选择下所能取到的最小的数的最大值是多少？

由于能控制的操作有限，所以**必须考虑无法控制的所有情况**。

为了将可控范围最大化，**这 $k$ 次控制必须施加在前 $k$ 次操作上**。

第 $m$ 次之后的操作与答案无关，无需考虑，所以 $k=\min(k,m-1)$.

假设能控制的 $k$ 次操作中选第一位的有 $x$ 个，不能控制的操作中选第一位的有 $y$ 个。可以推出此时第 $m$ 次操作能取得数的最大值即为:
$\max(a[x+y+1],a[n-(k-x)-(m-1-k-y)])$

由于原题数据范围~~比较水~~，直接枚举 $x$ , $y$ 就可以过了
时间复杂度：$O(n^2)$.

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=3505;
int n,m,k,a[M];
int main()
{
    int t; scanf("%d",&t);
    while(t--)
    {
    	scanf("%d%d%d",&n,&m,&k);
    	k=min(k,m-1); //第m次之后的操作与答案无关，无需考虑
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    	int ans=0;
    	for(int i=0;i<=k;i++) //枚举能控制的k次操作中选第一位的个数 
    	{
    		int s=1e9;
    		for(int j=0;j<=m-k-1;j++) //枚举不能控制的操作中选第一位的个数 
    			s=min(s,max(a[i+j+1],a[n+i-m+j+1]));
    		ans=max(ans,s);
		}
		printf("%d\n",ans);
	}
    return 0;
}
```
### 更优解

发现上述思路中 $x$ 变化后 $y$ 的枚举有很大一部分会使答案重复计算，而且所用操作均是取极值，所以想到用**单调队列**优化，操作类似[单调队列模板题](https://www.luogu.com.cn/problem/P1886)，具体见代码注释。

时间复杂度：$O(n)$.

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=350005;
int n,m,k,a[M],b[M];
int main()
{
    int t; scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        k=min(k,m-1); //第m次之后的操作与答案无关，无需考虑
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=m;i++) b[i]=max(a[i],a[i+n-m]); //预处理
		deque<int> q; //单调队列
		//x为可控制的操作中选第一位的个数,y为不可控制的操作中选第一位的个数 
		for(int y=0;y<=m-k-1;y++) //预处理x=0时的单调队列 
		{
			while(q.size()&&b[y+1]<b[q.back()]) q.pop_back(); //维护单调队列 
			q.push_back(y+1);
		}
		int ans=b[q.front()];
        for(int x=1;x<=k;x++) //之后的x变化时y的变化用单调队列维护，降低复杂度 
        {
            while(q.size()&&q.front()<x+1) q.pop_front(); //删去过期元素
			while(q.size()&&b[x+m-k]<b[q.back()]) q.pop_back(); //维护队列单调性
			q.push_back(x+m-k); //把新元素加入队列
			ans=max(ans,b[q.front()]); //更新答案 
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
#### 大佬轻喷
求管理员过qwq

---

## 作者：cff_0102 (赞：4)

注意到数据范围比较小，可以直接 $O(n^2)$ 枚举前面几个人的行为。

具体见注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int mian(){
	int n,m,k;cin>>n>>m>>k;
	k=min(m-1,k);
	m=m-k-1;//自己前面有几个人不受自己控制 
	int a[n+2];a[0]=a[n+1]=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	int ans=0;
	for(int i=0;i<=k;i++){//控制几个人去左边
		int nans=2e9;
		for(int j=0;j<=m;j++){//剩下几个人去左边 
			int l=1+i+j;//左边的人取完后左边的数原来的下标
			int r=n-(k-i)-(m-j);//右边的人取完后右边的数原来的下标
			nans=min(nans,max(a[l],a[r]));//此时要取更大的那个所以是 max(a[l],a[r])，但是要考虑最坏情况所以取这些 max 值的 min 
		}
		ans=max(ans,nans);//可以选择控制去左边的人数使答案最大 
	}
	cout<<ans<<endl;
	return 0;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--)mian();
	return 0;
}
```

注：`mian()` 是一个我自己为了方便多组数据输入的函数（这样缩进不会太多什么的），不是防抄袭内容，这是原版 AC 代码，[这里有 AC 链接](https://codeforces.com/contest/1290/submission/280952640)，我写过多少题解，不能加防抄袭内容我还能不知道。

---

## 作者：Theophania (赞：4)

## 简单翻译
你和$n-1$个朋友发现了一个含有$n$个整数的双端队列，$n$个人排队依次取走队首或队尾。你是队伍中的第$m$个人，在**所有人开始取数字前**你可以指定队伍中不同的$k$个人，使他们在取的时候听从你的指挥。一旦第一个人开始取数字，你就不能再指挥其他人或改变你之前的命令了。

求最大的整数$X$使得**无论未经你控制的人如何选择**，你能取到的数都**不小于**$X$。
## 思路：
首先这道题的数据范围很小，$n \le 3500$，所以本题用$O(n^2)$的暴力做是理所应当的。但是，可以通过单调队列的优化将时间复杂度降低到$O(n)$。

根据题意，可以发现以下两点：

- 不需要考虑排在自己后面的人。即当$k$的值超过在自己之前的人数$m-1$时，多余的受控制的人数不会对结果产生任何影响。
- 轮到自己时的情况只和之前在队首和队尾取的人数有关，和受自己控制的人取数字的先后顺序没有关系。也就是说，假设有一个人受到控制，并且已经确定他在队首(或队尾)取，那么无论他排在你前面的哪一位效果都是一样的。

自己是队伍的第$m$个人，由于之前的$m-1$人都只会取队首或队尾的元素，留给自己的一定是一个完整的且长度为$n-m+1$的区间。比较每一个区间的首尾元素并取最大值，可以得到一个值表示对于这一个区间可以取到的最大值。这样的区间一共有$m$个，所以开一个新的数组$s$来存储。

由于不受自己控制的人的选择是不可预计的，如果没有可以控制的人，那我们的$X$只能选择最坏的情况。所以控制一些人的选择可以帮助我们排除掉一些相对坏的情况。

接下来对**取队首的人**中**受到自己控制的人的数量**进行遍历，然后用一个单调队列找出每一次符合条件的最坏情况，再将所有的最坏情况取最大值，就可以找到所求的答案。这里单调队列的操作和[单调队列模板题](https://www.luogu.com.cn/problem/P1886)的操作非常相似，这种方法可以将复杂度降低到$O(n)$。

## AC代码：

```c++
#include <bits/stdc++.h>
using namespace std;
deque<int> q;
vector<int> v, a;
int main()
{
    int t, n, m, k, r, ans;
    scanf("%d", &t);
    while (t--)
    {
        ans = 0;
        a.clear();
        v.clear();
        q.clear();
        scanf("%d%d%d", &n, &m, &k);
        k = min(k, m - 1);
        for (register int i = 0; i < n; i++)
        {
            scanf("%d", &r);
            a.push_back(r);
        }
        for (register int i = 0; i < m; i++)
            v.push_back(max(a[i], a[i + n - m]));
        for (register int i = 0, j = 0; i <= k; i++)
        {
            for (; j < i + m - k; j++)
            {
                while (!q.empty() && v[q.back()] >= v[j])
                    q.pop_back();
                q.push_back(j);
            }
            while (!q.empty() && q.front() < i)
                q.pop_front();
            ans = max(ans, v[q.front()]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```


---

## 作者：I_am_Accepted (赞：2)

2021/7/17:增加了句号与空格

2021/7/9:增加了 $LaTeX$

~~良心题解 管理员求过~~

### 题意简述
一串数共 $n$ 个,有 $n$ 次操作,每次去掉数列的第一个或最后一个。现在你要操作的是第 $m$ 次，并且你可以控制任意 $k$ 次操作的选择。问你在最优选择下所能取到的最小的数的最大值是多少？
### 题目分析
首先，有用的控制一定控制"我"前面的人。

所以不妨将 $k$ 改为 $\min(k,m-1)$ 。

前 $m-1$ 个人先取,共 $m$ 种情况:

**case 1:** $0$ 人取前端, $m-1$ 人取后端，此时你取 $\max(a_1,a_{n-m+1})$ ；

**case 2:** $1$ 人取前端, $m-2$ 人取后端，此时你取 $\max(a_2,a_{n-m+2})$ ；

**case 3:** $2$人取前端, $m-3$ 人取后端，此时你取 $\max(a_3,a_{n-m+3})$ ；

$...$

**case m:** $m-1$ 人取前端, $0$ 人取后端，此时你取 $\max(a_m,a_n)$ 。

构建一个数组 `b[m]` ：

`b[i]=max(a[i],a[n-m+i])`

所以 $k=0$ 时(即不能控制),最优选择下所能取到的最小的数的最大值 $ans$ 是 $\min(b_1,b_2,b_3,...,b_m)$ 。

**若 $k>0$ 呢?**

为了使 $ans$ 最大,你会让 $k$ 个在你前面的人指定取前面/后面。

于是部分 **case** 取不到了。

哪些?

若你派 $t$ 人取前面, $(k-t)$ 人取后面，

则取前面至少有 $t$ 人,取后面至少有 $(k-t)$ 人。

于是 **case** $1$ ~ $t$ 和 **case** $(m-k+t+1)$ ~ $m$ 均不可取，

即对应的 $b$ 数组中元素不可取。

$ans$ 从$k=0$时的 $\min(b_1,b_2,b_3,...,b_m)$ 变成了 $\min(b_{t+1},b_2,b_3,...,b_{m-k+t})$ 。

**接下来只要求出使 $ans$ 最大的 $t$ 了**

~~此题数据水~~ $\mathcal{O}(Tn^2)$ 暴力即可，

也可以 $\mathcal{O}(Tn)$ 单调队列优化。

### Code:
```cpp
//https://www.luogu.com.cn/problem/CF1290A 
#include<bits/stdc++.h>
#define inf 0x7fffffff
#define fo(x,y,z) for(int x=y;x<=z;x++)
#define N 4000
using namespace std;
typedef long long ll;
void setio(string);

int T,n,m,k,a[N],b[N],minn,ans; 
int main(){
	setio("");
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		k=min(k,m-1);
		fo(i,1,n)cin>>a[i];
		fo(i,1,m)b[i]=max(a[i],a[i+n-m]);
		ans=0;
		fo(i,1,k+1)//这里可以用单调队列，但n^2能过就行了 （landuo） 
		{
			minn=inf;
			fo(j,i,i+m-k-1){
				minn=min(minn,b[j]);
			}
			ans=max(minn,ans);
		}
		cout<<ans<<endl;
	}
	return 0;
}
void setio(string name){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    if(name!=""){
        freopen((name+".in").c_str(),"r",stdin);
        freopen((name+".out").c_str(),"w",stdout);
    }
}

```


---

## 作者：学委 (赞：1)

$n \leq 3500$ 暗示有一个 $n ^ 2 \log n$ 的暴力。

如果操纵 $a$ 个人选择左端，$k - a$ 个人选择右端，那么不管你操纵的是哪几个人，都等效于：去掉数组左端 $a$ 个，右端 $k - a$ 个，然后剩下自由人开始选择。

$k$ 次操纵可以完全用掉，因为如果少操纵可以做到，多操纵必能做到。但不超过 $m - 1$ 次，后面的操纵无意义。

二分答案让元素都变成 $01$ 状态，暴力枚举左端操纵几个，然后暴力枚举自由人的决策（也是左右选几个）。如果某种操纵后，自由人无论怎样选择都无法使剩余的两端为 $0$（轮到你选的时候两端都不满足要求），那说明存在卓越的操纵。

```cpp
// 头文件
const int N = 3.5e3 + 10, E = 5e5 + 10;
const LL INF = 1e9;

int n, m, k, a[N], leg[N], b[N];

bool check(int v) {
  for (int i = 1; i <= n; ++i)
    leg[i] = a[i] >= v;
  int ex = 0, d = m - 1 - k;
  for (int i = 0; i <= k; ++i) {
    // left made i, right made k - i
    int suc = 1;
    for (int j = 0; j <= d; ++j)
      // left choose j, right choose d - j 
      if (leg[i + j + 1] == 0 and leg[n - (k - i) - (d - j)] == 0)
        suc = 0;
    if (suc) ex = 1;
  }
  return ex;
}
int gate() {
  n = getint(); m = getint(), k = getint();
  if (k > m - 1) k = m - 1;
  for (int i = 1; i <= n; ++i) a[i] = b[i] = getint();
  sort(b + 1, b + n + 1);
  int l = 1, r = n;
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if (check(b[mid])) // ans able >= mid
      l = mid; 
    else
      r = mid - 1;
  }
  printf("%d\n", b[l]);
  return 0;
}
signed main() {
  int t = getint();
  while (t--) gate();
  return 0;
}

```

---

## 作者：Peter20122012 (赞：0)

## 思路
注意到 $n$ 的范围很小，只有 $3500$，$\mathcal{O(n^{2})}$ 的时间复杂度能过。而且其实无论选择顺序怎样，只要选择从前面取的人一样多，那么你选的时候的情况就是一样的。

所以尝试先枚举你控制的人中有几个人选择从前面取，然后再枚举其他人有几个做出了从前面取的选择，然后在第二种里面取**最小值**（因为题目问的是无论**未经你控制的人如何选择**，你都能取到的最大数 $X$），然后再在这些最小值中取**最大值**（因为题目问的是无论未经你控制的人如何选择，你都能取到的**最大数** $X$）。

注意是要取**最小值中的最大值**，别搞混了。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = (st); i <= (ed); ++i)
#define RFOR(st, ed, i) for (int i = (ed); i >= (st); --i)

//#define debug

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;

const int inf = 0x3f3f3f3f;
const int maxn = 3.5e3 + 10;

int t;
	int n, m, k;
	int a[maxn];

	int ans;

void work_t () {
	ans = 0;
	
	scanf("%i%i%i", &n, &m, &k);
	FOR (1, n, i) {scanf("%i", &a[i]);}
	
	k = MIN(k, m - 1);
	FOR (0, k, i) {
		int mn = inf;
		FOR (0, m - k - 1, j) {
			mn = MIN(mn, MAX(a[i + j + 1], a[i + n - m + j + 1]));
		}
		ans = MAX(ans, mn);
	}
	
	printf("%i\n", ans);
}
int main () {
	scanf("%i", &t);
	while (t--) {work_t();}
	return 0;
}
```

---

## 作者：LZYAC (赞：0)

## 思路

——没有的时候先看时间复杂度。

$n \le 3500$ ，能非常轻松地跑 $O(n^2)$ 的算法。

于是我们可以想到一种比较暴力的方法——分别枚举可以控制的人中选左边的人数和不可控制的人中选左边的人数，再由此推出选右边的人数，在端点处取最小值，再对每个可能的值取最大即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,k,a[4010],ans,tmp;
signed main(){
	scanf("%d",&t);
	for(int tt=1;tt<=t;tt++){
		scanf("%d%d%d",&n,&m,&k);
		ans=INT_MIN;
		k=min(k,m-1);
		m=m-k-1;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=0;i<=k;i++){
			tmp=INT_MAX;
			for(int j=0;j<=m;j++) tmp=min(tmp,max(a[1+i+j],a[n-(k-i)-(m-j)]));
			ans=max(ans,tmp);
		}
		printf("%d\n",ans);
	}
    return 0;
}
```

---

## 作者：gyh20 (赞：0)

原本看题没有任何思路，但看完数据范围就恍然大悟

$1 \leq n \leq 3500$

$O(n^2)$可以过

于是枚举让几个人拿前面，几个人拿后面再判断自己能至少拿到多少即可。

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
int t,n,a[3505],m,k,ans;
inline int work(int l,int r,int x){
	int kk=1e9;
	for(int i=0;i<=x;++i){
		kk=min(kk,max(a[l+i],a[r-x+i]));
	}
	return kk;
}
signed main(){
scanf("%d",&t);
while(t--){
	scanf("%d%d%d",&n,&m,&k);
	if(k>=m)k=m-1;
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	m-=k;
	m-=1;
	ans=0;
	for(int i=0;i<=k;++i){
		ans=max(ans,work(i+1,n-k+i,m));
	}
	printf("%d\n",ans);
}
}
```

但我感觉肯定有 $O(n \log n)$ 或 $O(n)$ 的做法

---

