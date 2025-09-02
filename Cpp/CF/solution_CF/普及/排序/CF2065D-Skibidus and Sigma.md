# Skibidus and Sigma

## 题目描述

定义一个 $k$ 个元素的数组 $b$ 的分数为
$\sum_{i=1}^{k}\left(\sum_{j=1}^{i}b_j\right)$，也就是说，设 $S_i$ 表示数组 $b$ 的前 $i$ 个元素之和，则分数可以写作
$S_1 + S_2 + \ldots + S_k$。

Skibidus 得到了 $n$ 个数组 $a_1, a_2, \ldots, a_n$，每个数组包含 $m$ 个元素。作为西格玛男人，他希望能将这 $n$ 个数组按任意顺序拼接成一个包含 $n \cdot m$ 个元素的数组，以使最终得到的拼接数组的分数达到最大。请你帮助他计算拼接后能够获得的最大分数！

形式上地说，在所有可能的长度为 $n$ 的排列 $p$ 中，
求出数组 $a_{p_1} + a_{p_2} + \dots + a_{p_n}$ 的最大分数，
其中符号 $+$ 表示数组拼接。

$ ^{\text{∗}} $ 一个排列指的是一个包含 $1$ 到 $n$ 的所有整数且每个整数恰好出现一次的序列。  
$ ^{\text{∗}} $ 两个数组 $c$ 和 $d$（长度分别为 $e$ 和 $f$）的拼接 $c+d$ 定义为 $c_1, c_2, \ldots, c_e, d_1, d_2, \ldots, d_f$。

## 说明/提示

在第一个测试用例中，有可能的两种排列：
- $p = [1, 2]$，拼接后的数组为 $a_{p_1} + a_{p_2} = [4, 4, 6, 1]$，分数为 $4 + (4+4) + (4+4+6) + (4+4+6+1) = 41$。
- $p = [2, 1]$，拼接后的数组为 $a_{p_1} + a_{p_2} = [6, 1, 4, 4]$，分数为 $6 + (6+1) + (6+1+4) + (6+1+4+4) = 39$。  

因此，最大可能分数为 $41$。

在第二个测试用例中，一个最优的拼接结果为 $[4,1,2,1,2,2,2,2,3,2,1,2]$，分数为 $162$。

## 样例 #1

### 输入

```
3
2 2
4 4
6 1
3 4
2 2 2 2
3 2 1 2
4 1 2 1
2 3
3 4 5
1 1 9```

### 输出

```
41
162
72```

# 题解

## 作者：nightwatch.ryan (赞：3)

### Analysis
先将 $a$ 的每一行按照每一行元素之和升序排序。然后按照顺序将 $a$ 的所有元素全部放进数组 $all$。

记答案为 $ans$。

对于每个 $i$，$1 \leq i \leq n \times m$，我们记当前所有元素之和为 $sum$，则 $ans \gets sum + ans$。
### Code
```cpp
#include<bits/stdc++.h>
using ll = long long;
bool cmp(std::vector<int> a, std::vector<int> b){
    int s1 = 0, s2 = 0;
    for(auto i : a) s1 += i;
    for(auto i : b) s2 += i;
    return s1 > s2;
}
int main(){
    std::cin.tie(0)->sync_with_stdio(0);
    int T; std::cin >> T;
    while(T--){
        int n, m; std::cin >> n >> m;
        std::vector<std::vector<int>> a(n, std::vector<int>(m));
        for(int i = 0; i < n; i++)
         for(int j = 0; j < m; j++)
          std::cin >> a[i][j];
        sort(a.begin(), a.end(), cmp);
        std::vector<int> all;
        for(auto i : a) for(auto j : i) all.push_back(j);
        ll ans = 0, sum = 0;
        for(int i = 0; i < n * m; i++)
         sum += all[i], ans += sum;
        std::cout << ans << "\n";
    }
}
```

---

## 作者：yvbf (赞：2)

![](bilibili:BV1eiNhe7EZ9?t=565)

---

## 作者：Programming_Konjac (赞：1)

博客正在撰写中。

更新在：[这个 CSDN 账号上](https://blog.csdn.net/ainiyoung?type=blog)。

更新：修改了一处。
# 思路
假设我们现在有两个数组 $a,b$，长度为 $m$，它们的得分分别为 $ansa,ansb$，则它们合并后的结果为：
$$2ma_1+(2m-1)a_2+\cdots+(m+1)a_m+mb_1+(m-1)b_2+\cdots+b_m$$
化简，得到：
$$ma_1+(m-1)a_2+\cdots+a_m+ma_1+ma_2+\cdots+ma_m+ansb$$
再化简，得到：
$$ansa+m(\sum^m_{i=1}a_i)+ansb$$
那如果是 $k$ 个数组呢（这个二维数组是 $c$）？
$$\sum^{k}_{i=1}(ansc_i+(k-i)m(\sum^m_{j=1}c_{i,j}))$$
设 $(\sum^m_{j=1}c_{i,j})=sumc_i$，则原式等于：
$$\sum^{k}_{i=1}(ansc_i+(k-i)m\times sumc_i)$$

要让这个值最大，就必须 $\sum^{k}_{i=1}((k-i)m\times sumc_i)$ 最大，所以将每行的和进行从大到小排序，然后计算就行了。
# 赛时代码
[代码](https://codeforces.com/contest/2065/submission/305281429)。

---

## 作者：EternalLabyrinth (赞：1)

### 题意：
给定 $n$ 个序列 $B_i$，每个序列里面有 $m$ 个数，要求把这些序列以某种方式拼合在一起，拼成的大序列 $A$ 共有 $n\times m$ 个数，求让 $\sum A_i\times (n\times m-i+1)$。

注意题意经过了显然的转化。

### 解法：

对于每个序列我们记 $S_i=\sum B_{i,j}\times (m - j + 1)$，记 $G_i=(\sum B_{i,j})\times m$。

考虑临项交换法。选两个序列，设其编号为 $x$ 和 $y$。你要做的是让 $S_x+S_y+G_x>S_x+S_y+G_y$，即 $G_x>G_y$。所以其实和 $S$ 没关系。

按这个排序后直接计算即可。我们就做完了。

---

## 作者：StormWhip (赞：1)

### 思路
考虑贪心。不难发现，排在前面的数组的所有数字之和会加到排在其后面的数组的前缀和数组的每一位上，因此可以预处理每一个数组的前缀和，再根据每一个数组中元素之和降序排序，具体实现可以看代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int T,n,m,ans;
struct dis
{
	int p,q;//p是数组元素之和，q是数组前缀和之和
}a[N];
bool cmp(dis x,dis y)
{
	return x.p>y.p;
}
signed main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			int x=0,v=0;
			a[i].p=a[i].q=0;
			for(int j=1;j<=m;j++) {cin>>x;a[i].p+=x;v+=a[i].p;}
			a[i].q=v;
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++) ans+=a[i].q+a[i-1].p*m,a[i].p+=a[i-1].p;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：fish_love_cat (赞：0)

抛开题目规定的放置方式不谈，我们观察一个数组由初始的位置如果向前移动一格会发生什么。

注意到该数组每一个值的统计次数都多了一次。

推广可得，每一个数组前移多少格，该数组每一个值的统计次数就会多几次。

我们定义第 $i$ 个数组所有元素的和为 $sum_i$。

假设对于 $(i,j)$ 两个数组进行排序，容易发现两种顺序方案的贡献差为 $k\times(sum_i-sum_j)$。

证明：

假设 $k$ 是两个数组开头的距离，也就是前移或者后退的格数。

那么以 $a_j$ 在前，$a_i$ 在后的方案为基础，变成另一种方案的贡献差距就是前移 $k$ 格 $a_i$ 并后移 $k$ 格 $a_j$ 的贡献，即 

$$k\times sum_i+(-k)\times sum_j$$

化简得

$$k\times(sum_i-sum_j)$$

证毕。

那么我们按照 $sum$ 升序排序即可。

统计模拟题意。

实现简单，代码不放了。

---

## 作者：thedyingkai (赞：0)

### 思路
首先我们清楚，如果想得到拼接后整个数组的分数最高，那么就应该把前 $m$ 项和最高的数组排在最前面，因为各个数组作为一个整体拼接，排在前面的数组会加更多次。

先观察，用样例的第一组数据手动模拟（这里，$\operatorname{Score(x)}$ 是 $x$ 的分数，$S_x$ 是 $x$ 的各元素之和）：
$$\operatorname{Score(a)}=4+[4+4]，\operatorname{Score(b)}=6+[6+1]$$
$$\because S_a>S_b$$
$$\therefore \text{拼接后的字符串} c=\{4,4,6,1\}$$
$$\begin{aligned} \therefore \operatorname{Score(c)}&=4+[4+4]+[[4+4]+6]+[[4+4]+[6+1]]\\&=41\end{aligned}$$

有的人应该能看出来规律，$\operatorname{Score(c)}=[4+[4+4]]+2[4+4]+[6+[6+1]]$，即$\operatorname{Score(c)}=\operatorname{Score(a)}+\operatorname{Score(b)}+2S_a$，结合下面的样例，可以推导出递推公式。

设已经拼接了 $n$ 个数组，当前的分数为 $\operatorname{Score(n)}$，若要在数组 $a_n$ 后继续拼接 $a_{n+1}$，拼接后数组的分数为：

$$\operatorname{Score(n+1)}=\operatorname{Score(n)}+\operatorname{Score(a_{n+1})}+m(S_{a_1}+S_{a_2}+\cdots+S_{a_n})$$
### 证明
设 $c=\{b_1,b_2,\cdots,b_n\}$，$a_{n+1}=\{b_{n+1},b_{n+2},\cdots,b_{n+m}\}$。

有 $\operatorname{Score(n+1)}=\operatorname{Score(n)}+(S_c+b_{n+1})+(S_c+b_{n+1}+b_{n+2})+\cdots+(S_c+b_{n+1}+b_{n+2}+\cdots+b_{n+m})$。
- 此处共有 $m$ 个 $S_c$，一个 $\operatorname{Score(n)}$，其余项恰好为 $\operatorname{Score(a_{n+1})}$。

即得证，$\operatorname{Score(n+1)}=\operatorname{Score(n)}+\operatorname{Score(a_{n+1})}+m(S_{a_1}+S_{a_2}+\cdots+S_{a_n})$。
### AC code
```cpp
//
// Created by ASUS on 2025/2/9.
//
#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;
int t,n,m;
vector<long long> b;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>m;
        vector<vector<int>> a(n+1,vector<int>(m+1));
        long long ans=0;
        for(int i=1;i<=n;i++){
            long long s=0;
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
                s+=a[i][j];
                ans+=s;
            }
            b.push_back(s);
        }
        sort(b.begin(),b.end(),greater<>());
        long long tem=0;
        for (int i=0;i<n;i++){
            ans+=tem*m;
            tem+=b[i];
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：jzjr (赞：0)

## 前置知识

* 数学
* 排序

## 题意

有 $n$ 个长度为 $m$ 的序列，将其任意的拼接为长度为 $n\cdot m$ 的序列 $A$ 后其贡献为:

$$
\sum_{i=1}^{n\cdot m}A_i\cdot(n\cdot m-i+1)
$$

问所有贡献中的最大贡献。

## 思路

记 $s_i$ 表示第 $i$ 个序列的和，$e_i$ 表示第 $i$ 个序列的贡献。

那么如果某个序列排在第 $i$ 位，那么其贡献为 $(n-i)\cdot m\cdot sum+e$。

这说明贡献恒定，和才是排序的标准。

将和从大到小排序，得到答案。

## 实现

按思路排序即可。

### AC code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const LL N=2e5+5;
LL n,m,sum[N],a[N];
bool cmp(LL a,LL b){return a>b;}
inline void solve(){
	cin>>n>>m;
	LL ans=0;
	for(LL i=1;i<=n;i++){
		LL sum=0;
		for(LL j=1;j<=m;j++){
			LL x;cin>>x;
			ans+=(m-j+1)*x;
			sum+=x;
		}
		a[i]=sum;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		ans+=((n-i)*m)*a[i];
	}
	cout<<ans<<'\n';
}
int main (){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--)solve();
	return 0;
} 
```

---

## 作者：Lele_Programmer (赞：0)

# CF2065D 题解

## 思路

将给定的 $n$ 个各含有 $m$ 个元素的数组，让我们将这 $n$ 个数组以任意顺序拼接起来，使得前缀和数组的元素之和最大。

自行推一下式子，可以发现前缀和数组的元素之和，原数组 $a_1$ 出现 $n \times m$ 次，$a_2$ 出现 $n \times m-1$ 次，$a_{n \times m}$ 出现 $1$ 次。

对于第 $k$ 个长度为 $m$ 的数组，如果它在最终的数组的位置左移 $1$，那么答案就会增加这个数组的元素和，如果右移 $1$，答案就会减少这个数组的元素和，那么，元素之和更大的放在更前面，将数组按元素和降序排序，最后统计一下即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define _dinic(i,u) for (int i=cur[u];~i && k<limit;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[idx++]=c,c=getchar();
        x[idx]='\0';
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
    inline void writestr(string& x) { _iter(it,x) putchar(*it); }
    inline void writestr(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); }
    inline void writestrsp(string& x) { _iter(it,x) putchar(*it); putchar(' '); }
    inline void writestrsp(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(' '); }
    inline void writestrln(string& x) { _iter(it,x) putchar(*it); putchar(10); }
    inline void writestrln(char* x) { _rep(i,0,strlen(x)) putchar(x[i]); putchar(10); }
};

using namespace IO;

const int N=200005;

int T,n,m;
vector<int> vec[N];

bool cmp(const vector<int>& a,const vector<int>& b) {
    return a.back()>b.back();
}

i32 main() {
    read(T);
    while (T--) {
        read(n),read(m);
        _rep(i,1,n) {
            vec[i].clear();
            int sum=0;
            _rep(j,1,m) {
                int k;
                read(k);
                vec[i].emplace_back(k);
                sum+=k;
            }
            vec[i].emplace_back(sum);
        }
        sort(vec+1,vec+1+n,cmp);
        int k=n*m;
        int ans=0;
        _rep(i,1,n) {
            _rep(j,0,m-1) {
                ans+=vec[i][j]*k;
                k--;
            }
        }
        writeln(ans);
    }
    return 0;
}
```

---

## 作者：ztd___ (赞：0)

简单题。显然题意就是其前缀和数组的和。  
然后容易发现的是，在最终序列中，第 $i$ 个数 $a_i$ 会计入 $n - i + 1$ 次。  
考虑贪心。显然我们应该让值越大的数组计入的次数越多，也就是把它放到最前面，这样总价值也会最大。那么做法就是直接将 $n$ 个数组按其和从大到小排序，然后直接模拟计算即可。注意最终的统计答案数组要开到 $n \times m$ 的大小，然后由于大小不固定，用 `vector` 来存即可。代码自己写吧。

---

