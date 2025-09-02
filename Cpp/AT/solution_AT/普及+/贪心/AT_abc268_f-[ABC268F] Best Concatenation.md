# [ABC268F] Best Concatenation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc268/tasks/abc268_f

`1` から `9` の数字および `X` のみからなる $ N $ 個の文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ が与えられます。

$ (1,\ 2,\ \ldots,\ N) $ を並べ替えた列 $ P\ =\ (P_1,\ P_2,\ \ldots,\ P_N) $ を一つ選び、 文字列 $ T\ =\ S_{P_1}\ +\ S_{P_2}\ +\ \cdots\ +\ S_{P_N} $ を作ります。ここで、$ + $ は文字列の連結を表します。

そして、文字列 $ T\ =\ T_1T_2\ldots\ T_{|T|} $ の「スコア」を計算します（ $ |T| $ は文字列 $ T $ の長さを表します）。  
 $ T $ のスコアは、スコアが $ 0 $ の状態から始め、下記の $ 9 $ 個の手順を行うことで計算されます。

- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `1` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 1 $ 点加算する 。
- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `2` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 2 $ 点加算する。
- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `3` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 3 $ 点加算する。
- $ \cdots $
- $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `9` を満たす整数の組 $ (i,\ j) $ の個数だけ、スコアを $ 9 $ 点加算する。

$ P $ を任意に選ぶときの、$ T $ のスコアとしてあり得る最大値を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N $ は整数
- $ S_i $ は `1` から `9` の数字および `X` のみからなる長さ $ 1 $ 以上の文字列
- $ S_1,\ S_2,\ \ldots,\ S_N $ の長さの総和は $ 2\ \times\ 10^5 $ 以下

### Sample Explanation 1

$ P\ =\ (3,\ 1,\ 2) $ とすると、$ T\ =\ S_3\ +\ S_1\ +\ S_2\ = $ `XXX1X359` です。 このとき、$ T $ のスコアは次の通り計算されます。 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `1` を満たす整数の組 $ (i,\ j) $ が $ 3 $ 個あり、 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `3` を満たす整数の組 $ (i,\ j) $ が $ 4 $ 個あり、 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `5` を満たす整数の組 $ (i,\ j) $ が $ 4 $ 個あり、 - $ 1\ \leq\ i\ \lt\ j\ \leq\ |T| $ および $ T_i\ = $ `X` かつ $ T_j\ = $ `9` を満たす整数の組 $ (i,\ j) $ が $ 4 $ 個あります。 よって、$ T $ のスコアは $ 1\ \times\ 3\ +\ 3\ \times\ 4\ +\ 5\ \times\ 4\ +\ 9\ \times\ 4\ =\ 71 $ であり、これが考えられる最大値です。

## 样例 #1

### 输入

```
3
1X3
59
XXX```

### 输出

```
71```

## 样例 #2

### 输入

```
10
X63X395XX
X2XX3X22X
13
3716XXX6
45X
X6XX
9238
281X92
1XX4X4XX6
54X9X711X1```

### 输出

```
3010```

# 题解

## 作者：FFTotoro (赞：6)

本题可以用一种比官方解法较好理解的做法。

首先，我们定义一个函数 $f(S)$ 表示字符串 $S$ 的得分。有了这个函数，下面的操作就十分方便。

其次，本题的得分计算有一个性质：

对于字符串 $S_1,S_2,S_3$，用 $+$ 表示字符串的连接操作，那么

$$f(S_1+S_2+S_3)-f(S_2+S_1+S_3)=f(S_1+S_2)-f(S_2+S_1)$$

证明：

因为 $S_1+S_2$ 和 $S_2+S_1$ 中各种字符的数量相等，而连接上 $S_3$ 后，它们的顺序对 $S_3$ 的参与计算没有影响。所以，能对最终答案产生影响的，只有 $S_1+S_2$ 和 $S_2+S_1$ 的大小关系。

所以，对于每两个相邻的字符串 $S_1$ 和 $S_2$（可以用类似冒泡排序的思想去理解），如果 $f(S_1+S_2)<f(S_2+S_1)$，就可以交换它们——能使答案增加且无后效性。

可以用 `std::sort` 中的 `cmp` 函数作工具人，按上面的方法排个序再连接起来就好了。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f(string s){
    int p=0,c=0;
    for(auto &i:s){
        if(i=='X')p++;
        else c+=p*(i-48);
    }
    return c;
}
bool cmp(string s1,string s2){return f(s1+s2)>f(s2+s1);}
// 用连接后的权值做判断
signed main(){
    int n; string g; cin>>n;
    vector<string> s(n);
    for(auto &i:s)cin>>i;
    sort(s.begin(),s.end(),cmp);
    for(auto &i:s)g+=i; // 连接
    cout<<f(g)<<endl; // 计算最终答案
    return 0;
}
```

---

## 作者：Zikake (赞：1)

# 题意
给定 $ n $ 个由 $ X $ 和数字构成的字符串，你需要对其进行排列并拼接成新的字符串 $ T $ 以最大化其分数。定义其分数为对于字符串中每一个数字，使数字对应的数值乘上其之前 $ X $ 的数量，并求和。输出分数最大值。

# 思路
用排序函数，将每两个字符串结合在一起的价值最大，就可以达到最终答案为最大。实现字符串的子串价值最大，这个字符串的价值最大。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n;
string a[N];
bool cmp(string a,string b){
	//a+b的价值
	string ab=a+b;
	int cntab=0,ansab=0;
	for(int i=0;i<ab.size();i++){
		if(ab[i]=='X')cntab++;
		else{
			ansab+=(ab[i]-'0')*cntab;//统计ab价值 
		}
	}
	//b+a的价值
	string ba=b+a;
	int cntba=0,ansba=0;
	for(int i=0;i<ba.size();i++){
		if(ba[i]=='X')cntba++;
		else{
			ansba+=(ba[i]-'0')*cntba;//统计ba价值 
		}
	}
	return ansab>ansba;//价值对比 
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);//sort排序，求最优价值 
	string o="";
	for(int i=1;i<=n;i++){
		o+=a[i];//最终价值字符串 
	}
	int cnt=0,ans=0;
	for(int i=0;i<o.size();i++){
		if(o[i]=='X')cnt++;
		else{
			ans+=cnt*(o[i]-'0');//统计总价值 
		}
	}
	cout<<ans<<endl;//最终价值，完结撒花 
	return 0;
}
```

---

## 作者：Huangjy88 (赞：1)

# AT_abc268_f 题解
题目要求最大得分，考虑用贪心的策略解答。定义函数 $f(S)$ 为字符串 $S$ 的得分。对于每个给定的字符串 $S_{i}$，我们先预处理出它的 `X` 的个数 $cnt_{i}$，数字之和 $sum_{i}$，以及 $f(S_{i})$。

先考虑两个字符串。 
$$f(S_{1}+S_{2})-f(S_{2}+S_{1})$$
$$=(f(S_{1})+f(S_{2})+cnt_{1} \cdot sum_{2})-(f(S_{1})+f(S_{2})+cnt_{2} \cdot sum_{1})$$
$$=cnt_{1} \cdot sum_{2}-cnt_{2} \cdot sum_{1}$$
即 $f(S_{1}+S_{2})>f(S_{2}+S_{1})$ 等价于 $cnt_{1} \cdot sum_{2}>cnt_{2} \cdot sum_{1}$。

对于三个字符串，若 $S_{1},S_{2}$ 要放在 $S_{3}$ 之前。
$$f(S_{1}+S_{2}+S_{3})-f(S_{2}+S_{1}+S_{3})$$
$$=f(S_{1}+S_{2})+(cnt_{1}+cnt_{2}) \cdot sum_{3}-f(S_{2}+S_{1})-(cnt_{1}+cnt_{2}) \cdot sum_{3}$$
$$=f(S_{1}+S_{2})-f(S_{2}+S_{1})$$

即 $f(S_{1}+S_{2}+S_{3})>f(S_{2}+S_{1}+S_{3})$ 等价于 $f(S_{1}+S_{2})>f(S_{2}+S_{1})$。

扩展到 $n$ 个也应有类似关系。

所以，对于两个相邻的字符串 $S_{i},S_{j}$，若 $cnt_{i} \cdot sum_{j}<cnt_{j} \cdot sum_{i}$，则交换顺序，最后得到的顺序便是最优的，我们可以用快排来实现。最后计算总得分，复杂度 $\mathcal{O}(n \cdot \log n)$。

---

## 作者：bigclever (赞：0)

## 思路：
题目让我们将一些字符串拼接在一起，使其最后的总分数最大。因为任意两个相邻的字符串交换顺序并不会影响总得分，则我们可以运用**冒泡排序**的思想。假如我们定义字符串 $s$ 的分数为 $SC(s)$，若 $SC(s_i+s_{i+1}) \gt SC(s_{i+1}+s_i)$，显然 $s_i$ 应该排在 $s_{i+1}$ 的前面才能使最后的总分数最大。因此我们**按此规则**将题目给定的字符串数组 sort 一遍就完美解决了。

[类似好题推荐](https://www.luogu.com.cn/problem/P1012)。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//总分数有可能爆int，要开long long
string s[200005];
int cal(string k){//计算字符串k的分数
	int ans=0,cnt=0;
	for(int i=0;i<k.size();i++)
		if(k[i]=='X')cnt++;
		else ans+=(k[i]-'0')*cnt;
	return ans;
} 
bool cmp(string x,string y){return cal(x+y)>cal(y+x);}//排序规则
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n; cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	sort(s+1,s+n+1,cmp);
	string moo="";
	for(int i=1;i<=n;i++)moo+=s[i];//最后按排序后的结果依次拼接出的字符串就是分数最大的字符串
	cout<<cal(moo);
	return 0;
}
```

---

## 作者：ys_kylin__ (赞：0)

## 题目大意
给 $n$ 个只有数字与大写“X”的字符串，将他们接在一起，使得“得分”（每个数字乘之前 X 的数量）最大。

## 思路
一看就是一道排序题，我们只要找出一种排序规则就行了。

注意到，仅针对于两个字符串的排法，无论谁前谁后，对之后 X 的数量贡献相同，于是这里的局部最优就是全局最优。

简单来说，就是对于两个字符串，谁先谁后都试一遍，找大一些的就行了。而这就是 cmp 函数的内容。最后 sort 一下，接起来再算一次就是总分。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[200005];
long long calc(string x) {//计算得分
	long long res=0;
	int X=0;
	for(int i=0;i<x.size();i++) {
		if(x[i]=='X') X++;
		else {
			res+=(x[i]-'0')*X;
		}
	}
	return res;
}
int cmp(string x,string y) {
	string a=x+y,b=y+x;
	return calc(a)>calc(b);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>s[i];
	}
	sort(s+1,s+n+1,cmp);
	string tmp="";//拼接用的字符串
	for(int i=1;i<=n;i++) {
		tmp+=s[i];
	}
	printf("%lld",calc(tmp));//要开 long long 
	return 0;
}
```
[record](https://www.luogu.com.cn/record/139859182)

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc268_f)

考虑有三个字符串 $s_1$、$s_2$、$s_3$ 时的情况。

设 $f(s)$ 表示字符串 $s$ 得到的分数。

现在我们比较一下 $f(s_1+s_2+s_3)$ 和 $f(s_2+s_1+s_3)$ 的大小。

因为 $s_1+s_2$ 和 $s_2+s_1$ 含有的字符相同，所以无论 $s_1$ 和 $s_2$ 怎么排，$s_3$ 对总分数的贡献永远是一样的。

所以比较 $f(s_1+s_2)$ 和 $f(s_2+s_1)$ 的大小，如果 $f(s_1+s_2)$ 比 $f(s_2+s_1)$ 小就把 $s_2$ 放到前面。

有点像冒泡排序的思想。

搞个比较函数，给字符串数组排个序得到最终的字符串 $T$，计算 $f(T)$ 输出。

**最后记得开 long long。**

贴上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n; string s[200001], t;
long long f(string s){//按题意写计算分数的函数
	long long ans = 0, x = 0;
	for (int i = 0; i < s.length(); i++){
		if (s[i] == 'X') x++;
		else ans += x * (s[i] - 48);
	}
	return ans;
}
bool cmp(string s1, string s2){return f(s1 + s2) > f(s2 + s1);}//比较函数
int main(){
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) cin >> s[i];
	sort(s + 1, s + n + 1, cmp);
	for (int i = 1; i <= n; i++) t += s[i];
	printf("%lld", f(t));
	return 0;
}
```

---

## 作者：feiji_code (赞：0)

# 题目大意：
有 $n$ 个字符串，每个字符串由 ```X``` 和数字组成，分数 $T$ 为数字乘前面的 ```X``` 数量组成，怎样排序字符串让分数最大。
## 思路：
每个字符串的分数是固定的，任意两个字符串的位置交换不会影响到后面的字符串的分数，所以这里的局部最优解就是全局最优解。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long ans,n;
string s[300009];
string a;
long long f(string a){
	long long anns=0,sum=0;
    int len=a.size();
	for(int i=0;i<len;++i){
		if(a[i]=='X') anns++;
		else sum=sum+anns*(a[i]-'0');
	}
	return sum;
}
bool cmp(string a,string b){
	return f(a+b)>f(b+a);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//输入输出优化
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>s[i];
	}
	sort(s+1,s+n+1,cmp);
	
	for(int i=1;i<=n;++i){
		a=a+s[i];//拼接成一个字符串算分数
	}
	cout<<ans;
	return 0;
}

```



---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[ABC268F](https://www.luogu.com.cn/problem/AT_abc268_f)

# 思路

这题要我们求最后字符串拼起来的最大值。因为任意两个字符串交换顺序是不会改变大小的，所以我们可以利用一种类似与冒泡排序的方法。

在这里，我们定义第 $s$ 个字符串的得分为 $SCR(s)$。

若 $SCR(s_i+s_{i+1}) \gt SCR(s_{i+1}+s_i)$，我们就要把 $s_i$ 个字符串放在 $s_{i+1}$ 个字符串前面才可以使最大值尽可能大。

那么我们可以用一个类似于赋比重的方法，让数组排一次序就可以得出答案。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    long long a,b;
}a[200005];
long long n,ans,t;
string s;
bool cmp(node x,node y){
    return x.a*y.b<x.b*y.a;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>s;
        for(auto j:s){
            if(j=='X'){
                a[i].b++;
            }else{
                a[i].a+=j-'0';
                ans+=a[i].b*(j-'0');
            }
        }
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        ans+=t*a[i].a;
        t+=a[i].b;
    }
    cout<<ans<<endl;
}
```

[AC记录](https://www.luogu.com.cn/record/139779784)

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/AT_abc268_f)
如果随意排一次序，然后在交换相邻的两个字符串，则这两个字符串的 $X$ 总数不变，所以这两个字符串后的部分不受影响。

那么思路就很明确了，类似冒泡排序，对于两个相邻的字符串 $S_1$ 和 $S_2$，如果 $\left(S_1+S_2\right)$ 的得分大于 $\left(S_2+S_1\right)$，则将 $S_1$ 放在 $S_2$ 前面。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s[200005],anss;
int check(string ss){//统计得分
	int len=ss.size(),num=0,ans=0;
	for(int i=0;i<len;i++){
		if(ss[i]=='X')num++;
		else ans+=num*(ss[i]-'0');
	}
	return ans;
}
bool cmp(string x,string y){//排序
	return check(x+y)>check(y+x);
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)cin>>s[i];
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++)anss+=s[i];
	int lens=anss.size(),numm=0,ansss=0;
	for(int i=0;i<lens;i++){
		if(anss[i]=='X')numm++;
		else ansss+=numm*(anss[i]-'0');
	}
	printf("%lld",ansss);
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

#  [[ABC268F] Best Concatenation](https://www.luogu.com.cn/problem/AT_abc268_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC268F)

## 题面

给定 $ n $ 个由 `X` 和数字构成的字符串，你需要对其进行排列并拼接成新的字符串 $ T $ 以最大化其分数。定义其分数为对于字符串中每一个数字，使数字对应的数值乘上其之前 `X` 的数量，并求和。输出分数最大值。

## Solution

首先一个显然的结论即为对于题目定义的分数，同一字符串内部的 `X` 对其数字的贡献，与字符串在排列中的顺序无关。

于是我们考虑其它字符串的 `X` 对字符串数字的贡献，我们考虑字符串 $ S_i, S_j $，令 $ cnt_i $ 表示字符串 $ i $ 中 `X` 的数目，令 $ sum_i $ 表示字符串 $ i $ 中所有数字数值之和。显然若 $ S_i $ 在 $ S_j $ 之前，$ j $ 对 $ i $ 无贡献，$ i $ 对 $ j $ 的贡献为 $ cnt_i \times sum_j $。反之则为 $ cnt_j \times sum_i $。

则不难想到若我们要将 $ S_i $ 放在 $ S_j $ 之前，那么一定有这样的贡献更大一些，即 $ cnt_i \times sum_j \gt cnt_j \times sum_i $。

所以我们直接考虑对字符串进行排序，比较规则则按照刚才的式子跑一下即可。

同时我们也可以从意义上感性理解，显然只有前面的 `X` 对后面的数字产生贡献，所以我们将 `X` 更多数字更少的放在前面，则 $ \dfrac{cnt_i}{sum_i} $ 可以作为一个类似估价函数的作用进行排序，转换一下即我们刚才证明的上式。

同时对于此贪心的证明，考虑若满足偏序关系 $ S_1, S_2 $ 和 $ S_2, S_3 $，那么一定也有 $ cnt_1 \times sum_3 \gt cnt_3 \times sum_1 $，所以也有偏序关系 $ S_1, S_3 $，也就是 $ S_1, S_2, S_3 $，扩展到整个序列依然满足。

存在双倍经验 [LG-P1080 [NOIP2012 提高组] 国王游戏](https://www.luogu.com.cn/problem/P1080)。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
struct Node{string S; int sum, cnt;}d[210000];
ll ans(0);

int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        cin >> d[i].S;
        for(auto c : d[i].S)
            if(c == 'X')++d[i].cnt;
            else d[i].sum += c - '0';
    }sort(d + 1, d + N + 1, [](const Node &a, const Node &b)->bool{return (ll)a.sum * b.cnt < (ll)b.sum * a.cnt;});
    ll cur(0);
    for(int i = 1; i <= N; ++i)
        for(auto c : d[i].S)
            if(c == 'X')++cur;
            else ans += cur * (c - '0');
    printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_18 初稿

---

## 作者：DengDuck (赞：0)

注意到对于一个字符串，其内部的得分不因排序而改变，所以提前算出，接下来只需要看字符串之间的得分了。

我们考虑贪心解决问题，如何排序？

假设当前是最优排序，我们将某两个相邻的字符串 $i$ 和 $i+1$ 调换位置，显然不会干扰到与其他字符串之间的得分，所以我们把目光聚焦这两个字符串。

最优排序的得分应该更高，所以应该有：

$$
a_ib_{i+1} \leq b_ia_{i+1}
$$

解释以下，$b_i$ 表示第 $i$ 个字符串中 X 的数量， $a_i$ 表示第 $i$ 个字符串的数字之和。

左边是调换后的得分，右边是调换前的得分。

所以我们得到了字符串的排序方式。

然后计算即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    long long a,b;
}a[200005];
long long n,ans,t;
string s;
bool cmp(node x,node y)
{
    return x.a*y.b<x.b*y.a;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        for(auto j:s)
        {
            if(j=='X')
            {
                a[i].b++;
            }
            else
            {
                a[i].a+=j-'0';
                ans+=a[i].b*(j-'0');
            }
        }
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)
    {
        ans+=t*a[i].a;
        t+=a[i].b;
    }
    cout<<ans<<endl;
}
```

---

