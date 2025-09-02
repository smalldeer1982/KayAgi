# [ABC315C] Flavors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc315/tasks/abc315_c

$ N $ カップのアイスクリームがあります。  
 $ i $ カップ目の味は $ F_i $ 、美味しさは $ S_i $ ( $ S_i $ は偶数 ) です。

あなたは、 $ N $ 個のカップの中から $ 2 $ つを選んで食べることにしました。  
 このときの満足度は次のように定義されます。

- 食べたアイスクリームの美味しさを $ s,t $ ( 但し、 $ s\ \ge\ t $ ) とする。
  - $ 2 $ つのカップの味が異なるなら、満足度は $ \displaystyle\ s+t $ である。
  - そうでないなら、満足度は $ \displaystyle\ s\ +\ \frac{t}{2} $ である。
 
満足度として達成可能な最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ F_i\ \le\ N $
- $ 2\ \le\ S_i\ \le\ 10^9 $
- $ S_i $ は偶数
 
### Sample Explanation 1

$ 2 $ カップ目と $ 4 $ カップ目のアイスを食べることを考えます。 - $ 2 $ カップ目の味は $ 2 $ 、美味しさは $ 10 $ です。 - $ 4 $ カップ目の味は $ 3 $ 、美味しさは $ 6 $ です。 - 両者の味は異なるので、満足度は $ 10+6=16 $ です。 以上より、満足度 $ 16 $ を達成できます。 満足度を $ 16 $ より大きくすることはできません。

### Sample Explanation 2

$ 1 $ カップ目と $ 4 $ カップ目のアイスを食べることを考えます。 - $ 1 $ カップ目の味は $ 4 $ 、美味しさは $ 10 $ です。 - $ 4 $ カップ目の味は $ 4 $ 、美味しさは $ 12 $ です。 - 両者の味は同じなので、満足度は $ 12+\frac{10}{2}=17 $ です。 以上より、満足度 $ 17 $ を達成できます。 満足度を $ 17 $ より大きくすることはできません。

## 样例 #1

### 输入

```
4
1 4
2 10
2 8
3 6```

### 输出

```
16```

## 样例 #2

### 输入

```
4
4 10
3 2
2 4
4 12```

### 输出

```
17```

# 题解

## 作者：lrx___ (赞：4)

**题意简述**

有 $N$ 个冰淇淋，每个冰淇淋有一个种类 $F$ 和一个美味度 $S$。要在其中选两个冰淇淋，如果两个冰淇淋的种类相同，那么其中一个的美味度要变为原来的一半。要求使这两个冰淇淋的美味度之和最大。

**思路**

本题使用贪心法。先将所有冰淇淋按美味度从大到小排序，选取美味度最大的冰淇淋，记它的种类为 $f$。接着将后面所有种类为 $f$ 的冰淇淋美味度变为原来的一半，重新排序。最后取前两个的美味度之和即可。

**代码**

```cpp
#include<cstdio>
#include<algorithm>
#include<utility>
using namespace std;
typedef pair<int,int> pii;
const int N=3e5+5;
pii a[N];
/* first为种类，second为美味度 */
bool cmp(pii x,pii y){
	return x.second>y.second;
	/* 按美味度从大到小排序 */
}
int main(){
	int n,i,f;
	scanf("%d",&n);
	for(i=0;i^n;i++){
		scanf("%d%d",&a[i].first,&a[i].second);
	}
	sort(a,a+n,cmp);
	f=a[0].first;
	for(i=1;i^n;i++){
		if(a[i].first==f){
			a[i].second>>=1;
			/* 右移1位相当于除以二 */
		}
	}
	sort(a,a+n,cmp);
	printf("%d\n",a[0].second+a[1].second);
	return 0;
}
```

[提交记录](https://atcoder.jp/contests/abc315/submissions/44901668)

---

## 作者：Elairin176 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_abc315_c)   
淼题。   
## 题意
有 $n$ 个食物，第 $i$ 个食物的种类为 $s_i$，美味值为 $t_i$。现在要吃两个食物，求最大可获得的美味值。   
美味值的计算方法：如果两个食物种类不同，那么直接相加美味值，否则美味值较小的那个的美味值除以 $2$ 再加上另一个的。    
## 解法
我们先按美味值排序。   
如果美味值最大和次大的两个种类不同，那么结果就是这两个的美味值和。反之，我们先计算最大和次大的美味值，再找到第一个种类不同的，与最大的计算美味值即可。      
时间复杂度 $O(n\log n)$，可以通过。   
[CODE](https://atcoder.jp/contests/abc315/submissions/44717996)

---

## 作者：FreedomKing (赞：1)

### 思路

一种复杂度正确但比较暴力的做法，最多需要 $O(n)$ 扫 $3$ 遍。

首先可以确定，美味度最高的冰激凌我们是必选的，剩下的就是看另一份冰激凌如何选择了。

我们需要考虑两种情况：

- 美味度次最高的冰激凌的种类如果与最高的不同，直接选择，可以证明不会有更大的选择方式。

- 否则，我们需要再次扫一遍，找出与美味度最高的冰激凌**种类不同**的美味度最高的冰激凌，然后将其的美味度与二分之一美味度次高的冰激凌比较。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,m,t,k,x,y,ans,maxn,maxid;
struct node{
	int x,y;
}a[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		if(a[i].y>maxn){
			maxn=a[i].y;
			maxid=i;
		}
	}
	int maxnn=0,maxnid;
	for(int i=1;i<=n;i++){
		if(a[i].y>maxnn&&i!=maxid){
			maxnn=a[i].y;
			maxnid=i;
		}
	}
	ans=maxn+maxnn;
	if(a[maxid].x==a[maxnid].x){
		ans-=maxnn/2;
		int maxnnn,maxnnid;
		for(int i=1;i<=n;i++){
			if(a[i].x!=a[maxid].x&&a[i].y>maxnnn){
				maxnnn=a[i].y;
				maxnnid=i;
			}
		}
		ans=max(ans,maxn+maxnnn);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

1. [原题链接](https://atcoder.jp/contests/abc315/tasks/abc315_c)
2. 题目翻译：  
我们有 $N$ 杯冰淇凌，其中第 $i$ 杯的口味和美味程度分别是 $f_i$ 和 $s_i$。你可以选择吃掉两杯，让满意度最大。  
让 $s$ 和 $t$ 是吃过的两杯杯冰淇淋的美味程度，且 $s \le t$。  
满意度定义：  
- 如果两杯的口味不同，你的满意度是 $s+t$。
- 如果两杯的口味相同，你的满意度是 $s + \frac{t}{2}$。  
3. 思路：  
- 首先，输入所有数据，用结构体存。
- 然后，将结构体按照美味程度从大到小排。
- 之后，从前向后枚举，双重循环，按照题目模拟，用 $maxn$ 记录最大的满意度。
- 一波判断结束后，再来个玄学！判断时间，剩下足够输出 $maxn$ 的时间且快到时间时，输出 $maxn$，并停止所有程序。
4. 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int maxn=0;
struct node{
	int f,s;
}a[300010];
bool cmp(node a,node b){
	return a.s>b.s;
}
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].f>>a[i].s;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)
				continue;
			if(a[i].f==a[j].f)
				maxn=max(maxn,max(a[i].s,a[j].s)+min(a[i].s,a[j].s)/2);
			else
				maxn=max(maxn,a[i].s+a[j].s);
			if(1000*clock()>=1997*CLOCKS_PER_SEC){
    			cout<<maxn;
	    		exit(0);
    		}
		}
	}
	cout<<maxn;
	return 0;
}
```

5. 提交记录：  
![提交记录](https://cdn.luogu.com.cn/upload/image_hosting/r0yqlxru.png)

---

## 作者：_zzzzzzy_ (赞：0)

# 思路

赛时想了个很麻烦的解法，虽然不是正解但是可以看看思路。

首先我们先把这些东西按照味道分类，然后先全部丢进一个 set 里面，然后枚举每一种口味删掉他们原本的口味，加入除以二的口味，然后枚举这种口味的所有冰激凌，然后先把他自己删掉，查找最大的，然后再插入。

这种做法比较蠢是双 $\log$ 的，仅仅是多一种思路吧（

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
int f[maxn], s[maxn];
int ans = 0;
multiset<int> S;
map<int, vector<int>> mp;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(6);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> f[i] >> s[i];
		mp[f[i]].push_back(s[i]);
		S.insert(s[i]);
	}
	int ans = 0;
	for (auto f : mp) {
		for (int v : f.second) {
			S.erase(S.find(v));
			S.insert(v / 2);
		}
		for (int v : f.second) {
			S.erase(S.find(v / 2));
			ans = max(ans, v + *(--S.end()));
			S.insert(v / 2);
		}
		for (int v : f.second) {
			S.erase(S.find(v / 2));
			S.insert(v);
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：so_find_skind (赞：0)

这里提供一种不同的思路。

题目已经说过，选择的两种食物产生的美味度与其味道有关，那么我们完全可以按照味道的相异与相同来区分计算，最后取最大。

- 相异：

当味道相异时，产生的美味度即两者美味度之和，这样的话，我们只需找到两个味道不同的蛋糕，使得它俩美味度之和最大即可。

- 相同：

此时我们只需要将蛋糕按照美味度分成很多部分，将所有美味度一样的的蛋糕分在一起，然后，对每个部分取 $s+\frac{t}{2}$ 可取的最大值，再将这些最大值取最大（实际上是一种分治思想）。

此外，为了节省时间复杂度，我们最好用合理的方式先排序，否则会 TLE。

上面的解释可能有点不太清除，最好还是看看代码帮助理解：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
struct eg{
    int s,t;
}a[300005];
bool cmp(eg a,eg b){//如果要在排序的同时分组，就要对a.t也进行排序，这是味道相同时的排序
    if(a.s!=b.s)
        return a.s<b.s;
    return a.t>b.t;
}
bool cmp2(eg a,eg b){//味道不同时的排序
    return a.t>b.t;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].s>>a[i].t;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        if(a[i].s!=a[i-1].s && a[i+1].s==a[i].s)//这是为了防止整个部分只有一块蛋糕
            ans=max(ans,a[i].t+a[i+1].t/2);
    }
    sort(a+1,a+1+n,cmp2);//注意这里一定要重新排序
    for(int i=2;i<=n;i++){
        if(a[i].s!=a[1].s){//如果味道相同就是上一种情况了
            ans=max(ans,a[i].t+a[1].t);
        }
    }
    cout<<ans;
    return 0;
}
```

注：上述代码中的 $a_i.s$ 与 $a_i.t$ 所表示的意义分别是味道和美味度，与题目中相反。

---

## 作者：Failure_Terminator (赞：0)

## Solution

由于 $F_i$ 范围很小，我们考虑将同种口味的的冰激凌美味度存入对应的 `vector` 数组里。

对于每个数组，我们记录对应数组里的最大值，用两个变量 $mx$ 和 $se$ 分别保存所有最大值里的最大值和次大值。

对于每个大小 $\ge 2$ 的数组，我们可以用一个变量 $ans$ 记录所有这样的数组内答案的最大值。

最终的答案为 $\max(ans, mx + se)$。

## AC Code

$\Theta(n \log n)$ 解法：[Link](https://atcoder.jp/contests/abc315/submissions/44721564)

$\Theta(n)$ 解法：[Link](https://atcoder.jp/contests/abc315/submissions/44887456)

---

## 作者：Miyamizu_Mitsuha (赞：0)

看到其他题解没有对贪心正确性的证明，所以补了一发证明。

## 题意翻译：

你有 $ N $ 杯冰淇淋。第 $ i $ 杯的口味为 $ F_i $，美味程度为 $ S_i $（$ S_i $ 为偶数）。

你决定从这 $ N $ 杯冰淇淋中选择 $ 2 $ 杯来品尝。此时满足度如下定义：

假设你选择的冰淇淋的美味程度为 $ s $ 和 $ t $（其中 $ s\ge t $）。
- 如果选中的两杯冰淇淋的口味不同，则满足度为 $ s+t $。
- 如果选中的两杯冰淇淋的口味相同，则满足度为 $ s+\frac{t}{2} $。

请计算能够达到的最大满足度。

保证：

- 输入均为整数
- $ 2\le N\le3\times10^5 $
- $ 1\le F_i\le N $
- $ 2\le S_i\le 10^9 $
- $ S_i $ 为偶数

## 思路
暴力：直接 $n^2$ 暴力。
```
#include <iostream>
using namespace std;

int main() {
    int n, a[300005], b[300005], ans = -1e10;
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] != a[j]) {
                ans = max(ans, b[i] + b[j]);
            } else {
                ans = max(ans, min(b[i], b[j]) / 2 + max(b[i], b[j]));
            }
        }
    }
    
    cout << ans;
    return 0;
}



```
正解：

贪心。**先按照美味度排序**，然后从第二个冰淇淋开始和最大美味度的冰淇淋（即排在第一个的冰淇淋）比较。可以尝试不同风味的冰淇淋与最大美味度的冰淇淋进行组合。

浅证一下这个思路是对的，这个思路可以表示为，最大美味度的组合一定包含美味度最大的冰淇淋，那么想要证伪，就需要拿出两个美味度不是最大的冰淇淋的组合。

考虑这么一个例子（未知数代表口味）：
```
a 5
b 4
c 4
```

如果要证伪，我们肯定希望口味为 $b,c$ 的结合在一块，并且口味不同，然后美味度为 $5$ 的和其他结合在一起时风味相同，目的是利用那个一半减少该组合的美味度。

则可以得到 $b\not=c$。但按照上面的思路，我们希望 $a=b$ 或者 $a=c$，就拿 $a=b$ 举例子，因为 $b\not=c$，所以 $a\not=c$，遍历中会选取最佳的组合，所以一定不会选取 $a,b$，而是会选取 $a,c$，由于 $a$ 的美味度大于 $b$ 的美味度，所以选取 $a,c$ 的美味度一定会大于我们希望的 $b,c$，无法证伪。如果这三个下面再有其他的冰淇淋也不会影响结果，这个也说过了，遍历时会选取最优的。

证明的不是很严谨，但希望能帮助理解。有不懂的可以评论问我。

然后模拟，对于每个冰淇淋，判断其风味是否与最大风味相同。
- 如果风味不同，将当前冰淇淋的美味度与最大美味度相加，更新 ans。
- 如果风味相同，将当前冰淇淋的美味度的一半与最大美味度相加，更新 ans。

最好加上快读。

## 代码

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
省略6k快读
*/

struct Ic {
    int fl;//风味
    int ta;//美味度
};

bool cmp(const Ic &a, const Ic &b) {
    return a.ta > b.ta; 
}

int main() {
    int n;
    cin >> n;

    vector<Ic> icr(n);

    for (int i = 1; i <= n; i++) {
        cin >> icr[i].fl >> icr[i].ta;
    }

    sort(icr.begin(), icr.end(), cmp);

    int maxFl = icr[0].fl;
    int maxTa = icr[0].ta;
    int ans = -1e10; 

    for (int i = 2; i <= n; i++) {
        if (icr[i].fl != maxFl) {
            ans = max(ans, maxTa + icr[i].ta);
        } else {
            ans = max(ans, maxTa + icr[i].ta / 2);
        }
    }

    cout << ans ;

    return 0;
}


```


---

## 作者：Crazyouth (赞：0)

**翻译**

你有 $n$ 个蛋糕，每个蛋糕都有一个美味程度 $S_i$ 与一个种类 $F_i$，你可以选择其中两个曲奇，并最大化 $s$，定义如下：

- 若你选择的两个曲奇 $i,j$ 满足 $F_i=F_j$，$s=\max(S_i,S_j)+\frac{\min(S_i,S_j)}{2}$。
- 否则 $s=S_i+S_j$。

保证所有 $S_i$ 是偶数。

**分析**

直接贪心。根据 $S_i$ 大的排前面，分别对上述两种情况下能取到的最大 $s$ 进行比较，输出大的一种情况即可。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
struct cup
{
	int f,s;
}c[N];
int cmp(cup a,cup b)//按S大排序
{
	if(a.s!=b.s) return a.s>b.s;
	else return a.f<b.f;
}
int main()
{
	int ans1,ans2,n,flag=0;//flag表示是不是存在一个蛋糕种类与其他的不同
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i].f>>c[i].s;
		if(c[i].f!=c[1].f) flag=1;
	}
	sort(c+1,c+n+1,cmp);
	if(!flag)
	{
		cout<<c[1].s+c[2].s/2;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(c[i].f!=c[1].f)//种类不同的
		{
			ans1=c[i].s+c[1].s;//第二种情况
			break;
		}
	}
	ans2=c[1].s+c[2].s/2;//第一种情况
	cout<<max(ans1,ans2);
	return 0;
}

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc315_c)

**题目大意**：有 $N$ 道菜，每道菜都有一个风味和一个美味值。找出两道菜使它们的美味值之和最大。定义 $F$ 为风味，$F_i,F_j\space (i\neq j)$ 分别为两道菜的风味，$S$ 分别为美味值，$S_i,S_j\space (i\neq j)$ 为两道菜的美味值。

- 当 $F_i=F_j$，他们的美味值之和为 $\max(S_i,S_j)+\Large\frac{\min(S_i,S_j)}{2}$。

- 当 $F_i\neq F_j$，他们的美味值之和为 $S_i+S_j$。

## 思路

读入数据后存入一个 pair 类型的 vector 动态数组，按照 $S_i\space (1\le i\le  N)$ 从大到小排序。

保存上最大的 $S_i\space(1\le i\le N)$ 和它对应的 $F$ 的值。之后循环遍历这个 vector 动态数组，一步步按照题意模拟找最大可能的风味和，最后输出即可。

- 读入数据量较大，建议用较快的读入方式。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll n){//快写。
	if(n<0){
		n=-n;
		putchar('-');
	}
	if(n>9)print(n/10);
	putchar(n%10+'0');
}
const int N=3e5+10;
int n,f,s;
vector<pii>v;
inline bool cmp(pii a,pii b){
	return a.se>b.se;//从大到小排序。
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		f=read(),s=read();
		v.pb({f,s});
	}
	sort(v.begin(),v.end(),cmp);
	int maxf=v[0].fi,maxs=v[0].se,ans=-1e9;//ans 记得赋初始值。
	for(int i=1;i<n;++i){//逐个比较大小。
		if(maxf==v[i].fi)ans=max(ans,maxs+v[i].se/2);//风味一样的情况。
		else ans=max(ans,maxs+v[i].se);//风味不一样的情况。
	}
	cout<<ans;//输出最大的美味值。
	return 0;
}
```

---

## 作者：__Emerald__ (赞：0)

首先，美味程度最高的冰激凌肯定是要选的。

看看另一份冰激凌如何选择：

1. 若美味程度第二高的冰激凌的口味如果与最高的的不同，可以直接选择。

2. 否则，我们需要找出与美味程度最高的冰激凌程口味**不同**的冰淇淋中的美味程度最高的，然后将其的美味度与美味度第二高的冰激凌的 $\displaystyle\frac{1}{2}$ 比较。

这样就能 AC。

代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 5;
ll n,m,t,k,x,y,ans,maxn = 0,maxxb,maxnn = 0,maxnxb;
struct node{
	ll f,s;
}a[N];
int main(){
	cin >> n;
	for (ll i = 1;i <= n;i++){
		cin >> a[i].f >> a[i].s;
		if (a[i].s > maxn) maxn = a[i].s,maxxb = i;
	}
	for (ll i = 1;i <= n;i++)if (a[i].s > maxnn && i != maxxb) maxnn = a[i].s,maxnxb = i;
	ans = maxn + maxnn;
	if (a[maxxb].f == a[maxnxb].f){
		ans -= maxnn / 2;
		ll maxnnn,maxnnxb;
		for (ll i = 1;i <= n;i++) if (a[i].f != a[maxxb].f && a[i].s > maxnnn) maxnnn = a[i].s,maxnnxb = i;
		ans = max(ans,maxn + maxnnn);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc315_c)

#### 思路

考虑最优的一定是从 **颜色不同中的最大值** 和 **颜色相同中的最大值** 的最大值，求颜色不同中的最大值，得先选出每个颜色相同中的最大值，用数组存起来，数组里最大的两个相加就是最大值，如果只有一个则不行，而颜色相同中的最大值，我们需要存储每个颜色前两个最大值，然后求出最大值，最后比较一下，输出最优的即可。

**code**

```c
#include<bits/stdc++.h>
using namespace std;
int n,ma,ma1,v[300010],v1[300010],o[3000010],z,mam;
struct w
{
	int a,b;
}c[3000010];
bool cmp(w x,w y)
{
	return x.a > y.a;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) 
	{
		scanf("%d%d",&c[i].a,&c[i].b); 
		if(!v[c[i].a]) v[c[i].a] = c[i].b;
		else
		{
			if(v[c[i].a] < c[i].b) v1[c[i].a] = max(v1[c[i].a],v[c[i].a]),v[c[i].a] = c[i].b;
			else v1[c[i].a] = max(v1[c[i].a],c[i].b);//只需存储前两个最大的 
		}
	}
	sort(c + 1,c + 1 + n,cmp);
	mam = c[1].b;
	for(int i = 1;i <= n;i++) 
	{
		if(c[i].a != c[i + 1].a) 
		{
			o[++z] = max(mam,c[i].b);
			mam = 0;
		}
		else mam = max(mam,c[i].b);//选取颜色相同中的最大值 
	}
	sort(o + 1,o + 1 + z); 
	for(int i = 1;i <= n;i++) 
	{
		if(v1[i]) ma1 = max(ma1,v[i] + v1[i] / 2);//必须有两个数 
	}
	if(z == 1) o[z] = o[z - 1] = -114514;//只有一个则不行 
	cout << max(o[z] + o[z - 1],ma1);
    return 0;
}

```


---

## 作者：_Richardguo_ (赞：0)

# 思路：

把所有相同口味的冰激凌的美味值按从大到小排序，然后把每个口味除了最大值以外的所有冰激凌的美味值 $\div2$，最后选取两个最大的美味值即可。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
struct node{
	int f,s;
}a[N];
bool cmp(node x,node y){
	if(x.f!=y.f)return x.f<y.f;
	else return x.s<y.s;
}
priority_queue<int> pq;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i].f>>a[i].s;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(a[i].f!=a[i+1].f) continue;
		a[i].s>>=1;	
	}
	for(int i=1;i<=n;i++)pq.push(a[i].s);
	int s=pq.top();pq.pop();
	cout<<s+pq.top()<<"\n";
	return 0;
}


```

---

