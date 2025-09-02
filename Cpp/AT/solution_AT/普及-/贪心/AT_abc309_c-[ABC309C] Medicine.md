# [ABC309C] Medicine

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc309/tasks/abc309_c

高橋君は医者のすぬけ君から $ N $ 種類の薬を処方されました。$ i $ 種類目の薬は(処方された日を含めて) $ a_i $ 日間、毎日 $ b_i $ 錠ずつ飲む必要があります。また、高橋君はこれ以外の薬を飲む必要がありません。

薬を処方された日を $ 1 $ 日目とします。$ 1 $ 日目以降で、初めて高橋君がその日に飲む必要がある薬が $ K $ 錠以下になるのは何日目かを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 3\ \times\ 10^5 $
- $ 0\ \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ a_i,b_i\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1 $ 日目には、高橋君は $ 1,2,3,4 $ 種類目の薬をそれぞれ $ 3,5,9,2 $ 錠飲む必要があります。よってこの日は $ 19 $ 錠飲む必要があり、$ K(=8) $ 錠以下ではありません。 $ 2 $ 日目には、高橋君は $ 1,2,4 $ 種類目の薬をそれぞれ $ 3,5,2 $ 錠飲む必要があります。よってこの日は $ 10 $ 錠飲む必要があり、$ K(=8) $ 錠以下ではありません。 $ 3 $ 日目には、高橋君は $ 1,4 $ 種類目の薬をそれぞれ $ 3,2 $ 錠飲む必要があります。よってこの日は $ 5 $ 錠飲む必要があり、初めて $ K(=8) $ 錠以下になります。 以上より、$ 3 $ が答えです。

## 样例 #1

### 输入

```
4 8
6 3
2 5
1 9
4 2```

### 输出

```
3```

## 样例 #2

### 输入

```
4 100
6 3
2 5
1 9
4 2```

### 输出

```
1```

## 样例 #3

### 输入

```
15 158260522
877914575 2436426
24979445 61648772
623690081 33933447
476190629 62703497
211047202 71407775
628894325 31963982
822804784 50968417
430302156 82631932
161735902 80895728
923078537 7723857
189330739 10286918
802329211 4539679
303238506 17063340
492686568 73361868
125660016 50287940```

### 输出

```
492686569```

# 题解

## 作者：Molina (赞：7)

# 题目大意：

题目链接：[luogu](https://www.luogu.com.cn/problem/AT_abc309_c) && [atcoder](https://atcoder.jp/contests/abc309/tasks/abc309_c)

给了你 $ n $ 种药，对于每一种药，需要服用到第 $ a_i $ 天，每天需要吃 $ b_i $ 颗药，求第一天服用 $ k $ 颗药或 $ k $ 颗以下是第几天。

# 本题思路：
本题数据还是有点大，就先不考虑暴力，但可以用二分，有人使用了，这里就不再赘述。

我们介绍一种巧妙的方法。这里先用了一个结构体，记录每一种药需要吃到的天数与每天需要吃多少片。在输入时，记录下在一天最多吃多少片药，特判，若比 $ k $ 小，就证明第一天就满足情况，输出 $ 1 $ 即可。

然后，我们以每种药需要吃的天数给结构体排序。最重要的部分来了，这时我们开一重循环，从天数从小到大判断，看在一天最多吃的片数减去查到的这种药每天需要吃的片数（详细解释请看代码），若比 $ k $ 证明在查到的这种药吃完后，就满足了情况，直接输出天数即可。反之，就继续查找，直到找到答案。

有点慢，但是不会超时。

# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,k;
long long sum=0;//在一天最多吃多少片药
struct cz{//结构体
	int x,y;
}a[N];
bool cmp(cz a,cz b){
	return a.x < b.x ;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y;
		sum+=a[i].y;
	}
	if(sum<=k){//特判
		cout<<"1";
		return 0;
	}
	sort(a+1,a+n+1,cmp);//按天数排序
	for(int i=1;i<=n;i++){//开循环查找答案
		sum-=a[i].y;
		if(sum<=k){
			cout<<a[i].x+1;
			return 0;
		}
	}
	return 0;
}
```

---

## 作者：minVan (赞：4)

**题目大意**

有 $n$ 种药，对于每种药，如果今天还没到第 $a_i$ 天，那么就需要吃 $b_i$ 粒药，问至少要到第几天才能使那一天需要吃不大于 $k$ 粒药。

**解题思路**

我们可以在 $1$ 至 $\max\limits_{1\le i\le n}\{a_i+1\}$ 中二分，检查函数如下：

```cpp
inline int check(int x) {
  int sum = 0;
  for(int i = 1; i <= n; i++) {
    if(x <= a[i].x) {
      sum += a[i].y;
    }
  }
  return sum;
}
```

总时间复杂度：$O(n\log_2{\max\limits_{1\le i\le n}\{a_i+1\}})$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5;
struct node {
  int x, y;
} a[N];
int n, k;
inline bool cmp(node x, node y) {
  return x.x < y.x;
}
inline int check(int x) {
  int sum = 0;
  for(int i = 1; i <= n; i++) {
    if(x <= a[i].x) {
      sum += a[i].y;
    }
  }
  return sum;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for(int i = 1; i <= n; i++) {
    cin >> a[i].x >> a[i].y;
  }
  sort(a + 1, a + n + 1, cmp);
  int l = 1, r = a[n].x + 1, ans;
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(check(mid) <= k) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans;
  return 0;
}

```

---

## 作者：Dream_poetry (赞：1)

### 题意：

给定药品种数 $N$ 和目标量 $K$，接下来输入 $N$ 行，每行一个 $A$ 和 $B$，表示需要连续吃 $A$ 天该类药，每次吃 $B$ 粒药丸，输出第一次所吃总药丸数小于目标量 $K$ 的日子。

### 思路：

加入按照常规一遍又一遍的暴力，不出意外是会 **TLE** 的，所以，我们可以换个思路：

将整个存储 $A$ 和 $B$ 的结构体 $P$ 按照持续时间 $A$ 来排序。这样，越往后，所吃的药丸越少，因此倒序模拟查找即可大大减少时间复杂度。

同时，为了避免 **RE**，我们可以使用 ```vector``` 可变数组加上 ```pair``` 来存储信息，而不必使用结构体。

### 部分代码及解释：

```vector<pair<int,int> > p(N);```

定义一个可变数组，内部元素是 ```pair```，长度为 $N$。

```cpp
for(int i=0;i<n;i++)	
    cnt+=p[i].second;
if(cnt<=k) 
	return cout<<1,0;
```


如果第一天所有药丸之和相加仍少于 $K$，输出 $1$ 并终止程序即可。

```
for(int i=0;i<p.size();i++){
		if(cnt<=k){	
			cout<<p[i-1].first+1;	
			return 0;
		}
		cnt-=p[i].second;
	}
```

从前开始删减，直到满足条件，输出前一个元素持续天数加一，终止程序；如不能满足，让 $cnt$ 不断减少。

```
cout<<p.back().first+1;
```

到了最后，输出最后的天数加一。

### 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll cnt,n,k;
int main() {
	cin>>n>>k;
	vector<pair<int,int> > p(n);
	for(int i=0;i<n;i++)	cin>>p[i].first>>p[i].second;
	sort(p.begin(),p.end());
	for(int i=0;i<n;i++)	cnt+=p[i].second;
	if(cnt<=k) return cout<<1,0;
	for(int i=0;i<p.size();i++){
		if(cnt<=k){	cout<<p[i-1].first+1;	return 0;}
		cnt-=p[i].second;
	}
	cout<<p.back().first+1;
	return 0;
}
```


---

## 作者：yuheng_wang080904 (赞：1)

## 题意

有 $n(1\le n\le 3 \times 10^5)$ 种药，第 $i$ 种在前 $a_i$ 天都要服用，每天服用 $b_i$ 片药。问哪天第一次服用小于等于 $k$ 片的药。

## 思路

结构体、前缀和小练习。

对于所有的药，按照 $a_i$ 升序排序，然后用前缀和思路（即总药片数减去不用吃了的片数）$O(1)$ 求出每种药不再吃的第一天所要吃的药片数，与 $k$ 比较即可。若第 $i$ 种药不再吃的第一天首次满足条件，则答案即 $a_i+1$。

总时间复杂度 $O(n\log n)$。

## 代码

注：代码中没有用标准前缀和，而是用总量 $sum$，每次减去不再要吃的药片数，达到同样效果。

```cpp
ll n,k,ans,sum;
struct me{
    ll a,b;
}m[300005];
bool cmp(me x,me y){return x.a<y.a;}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>m[i].a>>m[i].b;
    sort(m+1,m+n+1,cmp);
    for(int i=1;i<=n;i++)sum+=m[i].b;
    if(sum<=k){
	cout<<1<<endl;
	return 0;
    }
    for(int i=1;i<=n;i++){
	sum-=m[i].b;
	if(sum<=k){
	    cout<<m[i].a+1<<endl;
	    return 0;
	}
    }
    return 0;
}
```


---

## 作者：hellolin (赞：1)

## AtCoder Beginner Contest 309 - C - Medicine

[洛谷题面](https://www.luogu.com.cn/problem/AT_abc309_c) | [AtCoder 题面](https://atcoder.jp/contests/abc309/tasks/abc309_c) | [前往 blog.hellolin.cf 获取更好的阅读体验](https://blog.hellolin.cf/articles/5d71bac6.html)

首先我们对这些吃药信息排序，以 $a_i$（吃药持续的天数）为关键字升序排序，这样我们这些吃药信息就是按结束时间排序的了。

`pair` 大法好！

``` cpp
// pair<ll,ll> a[N];
cin >> n >> k;
for(ll i=1; i<=n; i++) {
    cin >> a[i].first >> a[i].second;
    now += a[i].second;
}
sort(a+1, a+1+n);
```

获取到第一天要吃的药总数（即代码中的 `now`），之后，遍历这些信息，总数减去 $b_i$，一旦总数小于等于 $k$，输出答案。

输出答案时需要注意当前这天还是在吃药的，所以要输出 $a_i + 1$。

时间复杂度 $O(N\log N)$。

``` cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n,k,now;
pair<ll,ll> a[300010];
void solve() {
    cin >> n >> k;
    for(ll i=1; i<=n; i++) {
        cin >> a[i].first >> a[i].second;
        now += a[i].second;
    }
    sort(a+1, a+1+n);
    if(now <= k) {
        cout << 1 << endl;
        return;
    }
    for(ll i=1; i<=n; i++) {
        now -= a[i].second;
        if(now <= k) {
            cout << a[i].first + 1 << endl;
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

因为所有药开始吃的时间都是 $1$，所以随着天数增大，吃的药一定会减小。据此，先计算药物总量，将所有药按吃的天数排序后，顺序向后扫，减去当天吃的即可。

因为本题药物总量可以达到 $3 \times 10^5 \times 10^9 = 3 \times 10^{14}$，所以需要开 `long long`。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct p{
    int a,b;
}a[300005];
int n,q,k;
bool cmp(p a,p b){
    return a.a == b.a ? a.b < b.b : a.a < b.a;
}
signed main(){
    cin >> n >> q;
    for(int i = 1;i <= n;i ++) cin >> a[i].a >> a[i].b,k += a[i].b;
    sort(a+1,a+n+1,cmp);
    for(int i = 0;i <= n;i ++){
        k -= a[i].b;
        if(k <= q) return cout << a[i].a + 1,0;
    }
    return 0;
}
```

---

## 作者：kkxacj (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc309_c)

#### 前言

百度翻译误人子弟。

#### 题目大意

你有 $n$ 个药方，第 $i$ 个药方为你在 $a_i$ 天以前（包括 $a_i$ 天）都需服用 $b_i$ 颗药（可叠加），求你至少在第几天才使得服用的药的总颗数小于等于 $k$。

#### 思路

可以按时间 $a_i$ 排个序，把所有药累加起来，然后每次判断是否小于等于 $k$，如果小于，直接输出 $a_{i - 1} + 1$，（即不用再服用 $b_{i - 1}$ 颗药的第一天），否则继续模拟，每次判断失败后减去 $b_i$ 颗药。

code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum,ans,n,k;
struct w
{
	long long a,b;
}c[500010];
bool cmp(w x,w y)
{
	return x.a < y.a;
}
int main()
{
	cin >> n >> k;
	for(int i = 1;i <= n;i++) cin >> c[i].a >> c[i].b,sum += c[i].b;
	sort(c + 1,c + 1 + n,cmp);
	for(int i = 1;i <= n;i++)
	{
		if(sum <= k)//满足条件，直接输出
		{
			cout << c[i - 1].a + 1;
			return 0;
		}	
		sum -= c[i].b;
	}
	cout << c[n].a + 1 << endl;//这时一颗都不用服用了，一定可以
    return 0;
}

```


---

## 作者：Escapism (赞：0)

[原题链接](https://atcoder.jp/contests/abc309/tasks/abc309_c)

# 题意

高桥君要吃药，一共 $n$ 种药。医生让他对于第 $i$ 种药片要在前 $x_i$ 天（包括给处方的那一天）每天吃 $y_i$ 片。

现在问高桥君最早哪天会吃小于等于 $m$ 颗药片。

# 思路

显然可以发现吃小于等于 $m$ 颗药片最早的那一天肯定是某种药片恰好不再需要吃的时候，即某种药的 $x_i$ 天的下一天。

根据题意，显然第一天的时候是所有类型的药片都是要吃的，随后要吃的越来越少。

那么我们可以对所有类型的药品的 $x_i$ 进行从小到大的排序，然后我们可以算出每种药品吃完之后的第二天要吃多少种药（因为只有这种时候吃的药片数量会有变化）。

因而我们判断什么时候药片数量变的小于等于 $m$ 就行了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 3 * 1e5 + 5;
struct Node{
    long long a,b;
} x[MAXN];
bool cmp(Node t1,Node t2) {
    return t1.a < t2.a;
}
int main(){
    long long n,m,sum = 0;
    cin>>n>>m;
    for (int i = 1;i <= n;i++){
        cin>>x[i].a>>x[i].b; //每种药片要吃几天和每天吃多少片
        sum += x[i].b; //得出第一天时要吃多少片药片
    }
    sort(x + 1,x + n + 1,cmp); //排序
    if (sum <= m){ //特判刚开始时就吃小于等于 m 颗药片的情况
        cout<<1<<endl;
        return 0;
    }
    for (int i = 1;i <= n;i++){
        sum -= x[i].b;
        if (sum <= m){
            cout<<x[i].a + 1<<endl; //需要加一天，因为实际上 x[i].a 指的是吃某种药的最后一天。
            return 0;
        }
    }
}
```

[通过记录](https://www.luogu.com.cn/record/114811661)

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc309_c)      
水。     
## 题意   
高桥的医生给他开了 $n$ 种药，第 $i$ 种要需要服用 $a_i$ 天，每天服用 $b_i$ 片药。问高桥第一次服用 $k$ 片或 $k$ 片以下药是什么时候。      
## 解法
我们发现，$a_i$ 给出的贡献是会重复的，而每个重复的天数就是 $a_i$。      
那这样我们可以按 $b_i$ 排序，并对**排序后**的 $b_i$ 做前缀和，这里设 $q_i=\sum\limits^i_{j=1}a_j$。      
我们可以先先进行特判：如果 $q_n\le k$，那么直接输出 `1` 即可。     
之后我们对 $1$ 到 $n$ 扫一遍，设扫到了 $i$，那么我们这一次要服用的有 $q_n-q_i$ 片，进行判断即可。  
时间复杂度为 $O(n\log n)$，可以通过。    
[CODE](https://www.luogu.com.cn/paste/qp2s5q55)

---

