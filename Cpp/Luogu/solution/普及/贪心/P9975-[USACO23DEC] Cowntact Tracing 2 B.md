# [USACO23DEC] Cowntact Tracing 2 B

## 题目描述

Farmer John 有 $N$ 头奶牛排成一列（$1 \leq N \leq 3\cdot 10^5$）。不幸的是，有一种疾病正在传播。

最初，有一些奶牛被感染。每到夜晚，被感染的奶牛会将疾病传播给它左右两边的奶牛（如果这些奶牛存在的话）。一旦奶牛被感染，她就会持续处于感染状态。

经过一些晚上，Farmer John 意识到情况已经失控，因此他对奶牛进行了检测以确定哪些奶牛感染了疾病。请找出最少有多少头奶牛最初可能感染了这种疾病。

## 说明/提示

### 样例解释 1

假设只有中间的奶牛最初被感染。那么，奶牛们将按以下顺序被感染：

- 第 $0$ 晚：$00100$（第三只奶牛一开始被感染）
- 第 $1$ 晚：$01110$（第二和第四只奶牛现在被感染了）
- 第 $2$ 晚：$11111$（第一和第五只奶牛现在被感染了）
- 第 $3$ 晚：$11111$（所有的奶牛都已经被感染了，没有新的奶牛被感染）
- ……

经过两个或更多的晚上，奶牛们的状态即与输入的状态相符。还有许多其他的初始状态和夜晚数量可能导致了输入的状态，例如：

- 第 $0$ 晚：$10001$
- 第 $1$ 晚：$11011$
- 第 $2$ 晚：$11111$

或者：

- 第 $0$ 晚：$01001$
- 第 $1$ 晚：$11111$

或者：

- 第 $0$ 晚：$01000$
- 第 $1$ 晚：$11100$
- 第 $2$ 晚：$11110$
- 第 $3$ 晚：$11111$

所有这些初始状态中至少有一头奶牛被感染。

### 样例解释 2

唯一可能导致这个最终状态的初始状态和夜晚数是：没有经过任何夜晚，输入中的四头感染的奶牛都是从最开始就感染了这种疾病。

### 测试点性质

- 测试点 $3-7$ 满足 $N \le 1000$。
- 测试点 $8-12$ 没有额外限制。

## 样例 #1

### 输入

```
5
11111```

### 输出

```
1```

## 样例 #2

### 输入

```
6
011101```

### 输出

```
4```

# 题解

## 作者：No_Rest (赞：13)

# 思路

为了让最开始感染的牛尽量少，我们要让传染的天数尽量多。我们可以先求出这个天数，再根据天数来倒推最开始最少的感染牛数。

通过思考可以发现，连续 $x$ 只感染的牛最多通过 $\lfloor \frac{x-1}{2} \rfloor$ 天的传染得到（想象一只牛在中间，每天都把两边的牛传染到）。通过样例二可以发现，整群牛最多传染天数是所有连续的牛的最多传染天数中的最少天数。

让我们假设这个求出来的天数是 $m$。确定天数后，我们就可以倒推牛数了。每只牛在 $m$ 天后会传染左面、右面各 $m$ 只牛，算上自己，会传染 $2m+1$ 只牛。因此，为了最初感染的牛最少，我们每 $2m+1$ 只牛就只把中间的那头牛当最初感染的牛。这样的话，连续 $x$ 只感染的牛中，最少会有 $\lceil \frac{x}{2m+1} \rceil$ 只是最初感染的。

最后是要注意边界，因为边界的情况与中间不太一样。在边界，连续 $x$ 只牛能传染 $x - 1$ 天。

# 代码

```cpp
#include<iostream>
#include<vector>
#include<cmath>
#define ll long long
#define in inline
#define re register
using namespace std;
const ll maxn = 3e5 + 5;
in ll read(){
	char ch;
	ll f = 1, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0'){ if(ch == '-') f = -1; ch = getchar();}
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return r * f;
}
in void write(ll f){
	if(f < 0) f = -f, putchar('-');
	if(f > 9) write(f / 10);
	putchar(f % 10 + '0');
	return;
}
ll n = read(), a[maxn], ans[maxn], mn = maxn, last, cnt;
vector <ll> st, ed;//记录每一段连续感染奶牛的起点和终点
int main(){
	for(re ll i = 1; i <= n; ++i){
		scanf("%1d", &a[i]);
		if(a[i]){
			last++;
			if(!a[i - 1]) st.push_back(i);//一段连续感染奶牛的开始
		} else if(!a[i] && last){
			if(st[st.size() - 1] == 1) mn = min(mn, i - 2);//注意边界
			else mn = min(mn, (last - 1) / 2);//计算最多天数
			last = 0, ed.push_back(i - 1);
		}
	}
	if(last) mn = min(mn, last - 1), ed.push_back(n);//最后别忘了
	for(re ll i = 0; i < st.size(); ++i) cnt += ceil(1.0 * (ed[i] - st[i] + 1) / (2 * mn + 1));//计算牛数
	write(cnt);
    return 0;
}
```

---

## 作者：Expert_Dream (赞：9)

[博客园](https://www.cnblogs.com/gsczl71/p/17909469.html)。

首先我在这题上写了三份代码。原因是我一开始想到分讨，写复杂了。

根据贪心策略，很容易知道：**天数越大，奶牛数少**，所以我们让天数最多。然后我们会发现头尾的那个区间如果是 $x$，那么相当于一个 $2 \times x - 1$ 的一个普通区间（就是在中间的那种区间）。

所以我们根据处理后的每一个区间的长度进行计算，然后得到了每一个区间最小的天数，也就是我们能够放最多的天数。

所以按照这个去模拟即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int xx=-1,yy=-1;
string s;
vector<pair<int,bool> > v;
int res,ok=1,cnt=0;
int minn = 1e9;

void solve(){
	cin >> n >> s;
	s = ' '+s;
	for(int i = 1;i <= n;i++){
		if(s[i]=='0'){
			if(res)v.push_back({res,ok});
			ok=0;
			res=0;
		}else if(s[i]=='1'){
			res++;cnt++;
		}
	}
	if(res) v.push_back({res,1});
	
	int min2=1e9;
	for(auto it:v){
		if(it.second == 0)min2 = min(min2,it.first);
		else{
			min2 = min(min2,it.first * 2-1);
			if(xx == -1)
				xx = it.first;
			else
				yy = it.first;
		}	
		
	}
	minn=(min2+1)/2;
	int res=0;
	for(auto it:v){
		if(it.first % (minn * 2 - 1) == 0) res+=it.first / (minn * 2 - 1);
		else res+=it.first / (minn * 2 - 1) + 1;
	}
	cout<<res;
}

signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	solve();
	return 0;
}

```

---

## 作者：strcmp (赞：5)

一道分讨题。

------------

我们考虑一下，在合法的前提下，肯定是天数越大越优。

那么是什么限制了我们增大天数呢？

是最小的连续 `1` 段。

比如对于位于中间的末状态是 `...01111110...` 的状态，我们最多只能有两天来传播。

为什么要强调是位于中间的，因为我们可以有 `...0111111`，此时如果从最右边开始传播，可以传播五天。开头的 `1111110...` 也有同样的效果。

只有这两种情况，分讨即可。

最后我们令最大的合法天数为 $d$。

对于长度为 $l_i$ 的连续 `1` 段，总贡献为 $\sum \lceil\dfrac{l_i}{2d + 1}\rceil$。

时间复杂度 $\Theta(n)$。

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long int ll;
using pll = pair<int, ll>;
const int maxn = 4e5 + 10;
const ll mod = 998244353LL;
const ll inf = 1145141919810LL;
int n, a[maxn], p = 0; char s[maxn];
int main() {
	scanf("%d%s", &n, s + 1); s[++n] = '0'; int num = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '1') ++num;
		else if (num) {
			a[++p] = num; num = 0;
		}
	}
	int day = maxn; day = min(day, a[1] - 1);
	if (s[1] == '0') day = min(day, (a[1] - 1) / 2);
	for (int i = 2; i < p; i++) {
		day = min(day, (a[i] - 1) / 2);
	}
	day = min(day, a[p] - 1);
	if (s[n - 1] == '0') day = min(day, (a[p] - 1) / 2); int sum = 0;
	for (int i = 1; i <= p; i++) sum += ceil((double)a[i] / (day * 2 + 1));
	printf("%d\n", sum);
	return 0;
}
```

---

## 作者：Loser_Syx (赞：3)

有结论：持续天数越长需要最少奶牛数越小（因为每天都在扩散其他奶牛）。

所以直接对于每个连通 `1` 块算最多要用几天，具体而言：

- 如果这个连通 `1` 块在牛棚边缘

> - 如果长度 $< 1$，一天都不能扩散。
> - 否则，扩散天数为长度减一。

- 否则

> - 如果长度 $\leq 2$，一天都不能扩散。
> - 否则，扩散天数为 $(len-1) \div 2$ 向下取整（从最中间开始扩展）。

得出每个连通块最多可以几天之后，随即得出的整个字符串最长可以扩散几天（对上面答案取 $\min$），然后得出每个感染源一共最多扩散 $day \times 2 + 1$ 个。

统计每个连通块的长度除以最多扩散牛数向上取整的和即可。

```cpp
signed main() {
	int n = read();
	string s; cin >> s;
	auto quit = [&]() -> void {
		int cnt = 0;
		for (int i = 0; i < n; ++i) cnt += s[i] == '1';
		write(cnt, '\n');
		exit(0);
	};
	int ans = 1e9, flg = 0;
	string p = "";
	auto check = [&]() -> void {
		if (p.size() < 3) quit();
		if (flg == 1) ans = min(ans, (int)p.size() - 2);
		else ans = min(ans, ((int)p.size() - 1) / 2LL);
	};
	if (s[0] == '1') {
		flg = 1;
		p += "1";
	}
	for (int i = 0; i < n; ++i) {
		if (s[i] == '1') p += "1";
		else {
			if (p != "") {
				check();
				flg = 0;
				p = "";
			}
		}
	}
	if (p != "") {
		flg = 1;
		p += "1";
		check();
		p = "";
	}
	int qwq = 0, cnt = ans * 2 + 1;
	s += "0"; 
	for (int i = 0; i < n+1; ++i) {
		if (s[i] == '1') p += "1";
		else {
			if (p != "") {
				int len = p.size();
				qwq += len / cnt + (bool)(len % cnt);
				p = "";
			}
		}
	}
	write(qwq, '\n');
	return 0;
}
```

---

## 作者：xixihaha2021 (赞：3)

# [[USACO23DEC] Cowntact Tracing 2 B](https://www.luogu.com.cn/problem/P9975)
## 题意简述
一个农场，农场里有 $N$ 头奶牛排成一列。有一种疾病正在传播，最初，有一些奶牛被感染。每到夜晚，被感染的奶牛会将疾病传播给它左右两边的奶牛（如果这些奶牛存在的话）。一旦奶牛被感染，她就会持续处于感染状态。经过一些晚上，农场主人意识到情况已经失控，因此他对奶牛进行了检测以确定哪些奶牛感染了疾病。题目要求找出最少有多少头奶牛最初可能感染了这种疾病。
## 思路分析
省流：通过模拟疾病的传播过程，来找出最少有多少头奶牛最初可能感染了这种疾病。

首先，读入奶牛的数量 $N$ 和每头奶牛的状态。状态被存储在数组中，其中 $1$ 表示奶牛被感染，$0$ 表示奶牛未被感染。

然后，遍历了所有的奶牛。如果一头奶牛被感染，检查前一头奶牛的状态。如果前一头奶牛未被感染，增加一段连续感染，并初始化该段的感染奶牛数量为 $1$。如果前一头奶牛被感染，增加当前段的感染奶牛数量。这一步的目的是找出所有连续感染的段，并记录每一段的感染奶牛数量。

接下来，计算了中间段的最小感染天数。这是通过对每一段连续感染的奶牛数量减一后除以二得到的。这一步的目的是找出最小的感染天数，因为这个值决定了最初可能感染的奶牛数量。

注意检查第一头奶牛和最后一头奶牛的状态，如果她们被感染，代码会更新最小感染天数。这一步的目的是确保最小感染天数的计算考虑到了所有可能的情况。

最后，代码计算了最少感染奶牛数量。具体方法见代码第 $23$ 行。
## 复杂度分析
### 时间复杂度分析
设连续感染的段数为 $K$，显然时间复杂度为 $O(K+N)$.因为 $K \le \frac{1}{2}N$，所以时间复杂度去掉常数为 $O(N)$。
### 空间复杂度分析
显然，$O(N)$。
### 数据范围
数据范围：$1 \le N \le 3 \cdot 10^5$.

最劣时间：$N=3 \cdot 10^5 \le 10^8$，显然不会超时。

空间：$N=3 \cdot 10^5 \le 3 \cdot 10^7\space_{[1]}$，显然不会超空间。
## 代码实现
```cpp
#include <bits/stdc++.h>//导入所有标准库
using namespace std;//使用标准命名空间
typedef long long ll;//定义长整型别名为ll
ll n,a[300005],my_array[300005],my_len = 0,minn = 2147483647,ans = 0;//定义全局变量，n为奶牛数量，a[i]为第i头奶牛的状态，my_array[i]为第i段连续感染的奶牛数量，my_len为连续感染的段数，minn为最小感染天数，ans为最少感染奶牛数量
char ch;//定义字符变量，用于读入奶牛的状态
int main(){//主函数开始
    scanf("%lld",&n);//读入奶牛数量
    for(ll i = 1;i <= n;i++){//对于每头奶牛，进行以下操作
        scanf(" %c",&ch);//读入奶牛的状态
        a[i] = ch - '0';//将字符转换为数字
    }
    for(ll i = 1;i <= n;i++){//对于每头奶牛，进行以下操作
        if(a[i] == 1){//如果奶牛被感染
            if(a[i - 1] == 0)my_array[++my_len] = 1;//如果前一头奶牛未被感染，增加一段连续感染，初始化该段的感染奶牛数量为1
            if(a[i - 1] == 1)my_array[my_len]++;//如果前一头奶牛被感染，增加当前段的感染奶牛数量
        }
    }
    for(ll i = 2;i <= my_len - 1;i++)if((my_array[i] - 1) / 2 < minn)minn = (my_array[i] - 1) / 2;//计算中间段的最小感染天数
    if(a[1] == 1)minn = min(minn,my_array[1] - 1);//如果第一头奶牛被感染，更新最小感染天数
    else minn = min(minn,(my_array[1] - 1) / 2);//如果第一头奶牛未被感染，更新最小感染天数
    if(a[n] == 1)minn = min(minn,my_array[my_len] - 1);//如果最后一头奶牛被感染，更新最小感染天数
    else minn = min(minn,(my_array[my_len] - 1) / 2);//如果最后一头奶牛未被感染，更新最小感染天数
    for(ll i = 1;i <= my_len;i++)ans += (my_array[i] + 2 * minn) / (2 * minn + 1);//计算最少感染奶牛数量
    printf("%lld",ans);//输出最少感染奶牛数量
    return 0;//主函数返回0，表示程序正常结束
}
```
**注：**

[1]：经计算，若所有变量均为长长整型，最多可以使用约 $3 \cdot 10^7$ 个变量。

---

## 作者：tder (赞：3)

USACO 还是很喜欢二分的。

---

FJ 有一排 $N$ 头牛。

其中，在第 $0$ 天，有若干头牛被感染。每天晚上，已经被感染的牛会传染给左右相邻的两头牛。

过了若干天，FJ 告诉你当天每头牛是否被感染。请你求出在第 $0$ 天，最少有多少头牛被感染。

---

先把感染情况抽象为很多个连续块，即有连续被感染的若干头牛。

具体地，当感染情况为 `1110100111100011` 时（`1` 表示被感染），我们可以把它抽象成：

$$
P'=\{3,1,4,2\}
$$

再形象一点，还可以加上是否在边缘的标记（$1$ 表示在边缘）：

$$
P=\{(3,1),(1,0),(4,0),(2,1)\}
$$

我们称一个连续块 $P_i$ 的大小为 $P_{i,1}$，而标记其是否在边缘称作 $P_{i,2}$。


那么，考虑二分天数，显然有递增性。

设共进行了 $M$ 天，则有 $0\le M<\min(P_i)$，二分即可。

下面介绍 $\text{check}()$ 函数的写法：

过了 $M$ 天，$1$ 头牛会感染包括自己在内的 $2\cdot M-1$ 头牛，可以看作是一个长度为 $2\cdot M-1$ 的线段。对于第 $i$ 个连续块，我们需要用最少的线段，覆盖一个长度为 $P_{i,1}$ 的线段。

- 对于不在边缘的连续块，即 $P_{i,2}=0$ 时，若 $2\cdot M-1>P_{i,1}$，显然会覆盖线段外的区域，无解；
- 对于在边缘的连续块，即 $P_{i,2}=1$ 时，当被感染的牛置于端点时，其能覆盖的可见大小为 $2\cdot P_{i,1}-1$，故若 $2\cdot P_{i,1}-1>2\cdot M-1$ 时，无解。

若有解，显然我们只需 $\lceil\dfrac{P_{i,1}}{2\cdot M-1}\rceil$ 个线段即可完成覆盖。因此，当共进行 $M$ 天时，第 $0$ 天最少的被感染的牛的头数 $r$ 为：

$$
r=\sum\lceil\dfrac{P_{i,1}}{2\cdot M-1}\rceil
$$

时间复杂度 $O(N\log N)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
int n;
string s;
vector<pair<int, int> > v; 
int check(int d) {
	int t = 0;
	for(auto i : v) {
		int f = i.first, g = d * 2 + 1;
		if(!i.second) {
			if(g > f) return -1;
			else t += ceil(1.0 * f / g);
		} else {
			if(g > f * 2 - 1) return -1;
			else t += ceil(1.0 * f / g);
		}
	}
	return t;
}
signed main() {
	cin>>n>>s;
	s += '0';
	for(int i = 0, f = 0; i < s.length(); i++)
		if(s[i] == '1') f++;
		else if(f) {
			if(i == f || i == s.length() - 1) v.push_back({f, 1});
			else v.push_back({f, 0});
			f = 0;
		} 
	sort(v.begin(), v.end());
    if(v.empty()) {
        cout<<0<<endl;
        return 0;
	}
    int l = 0, r = v[0].first - 1;
	while(l < r) {
		int m = ceil(1.0 * (l + r) / 2), p = check(m);
		if(p == -1) r = m - 1;
		else l = m;  
	}
	cout<<check(l)<<endl;
	return 0;
}
```

---

## 作者：Adchory (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9975)。

## 思路

考虑贪心，一个很显然的结论是：感染的天数越多，最初奶牛感染的数量就越少。因此我们只需求出最大可能的感染天数即可。

考虑中间的一段连续的 $1$，即 $011\cdots110$，设其 $1$ 的长度为 $l$，分类讨论：

- 假设 $l$ 为奇数，那么感染天数为 $\dfrac{l-1}{2}$，从中间的奶牛开始感染即可。

- 假设 $l$ 为偶数，那么感染天数为 $\dfrac{l}{2}-1$，从中间两个奶牛开始感染即可（注意：只有一个奶牛是填不满这段 $1$ 的）。

综上，我们可以写成 $\biggl\lfloor\dfrac{l-1}{2}\biggl\rfloor$。

考虑边缘的两段连续的 $1$，即 $011\cdots1$ 和 $1\cdots110$，我们可以从最边缘开始感染，其感染天数为 $l-1$。

我们对这些连续的 $1$ 段的感染天数取 $\min$ 就是最大可能的感染天数。

接下来我们只用考虑对于一段连续的 $1$，在固定的感染天数内，最少需要多少只感染的奶牛。

以一个奶牛为中心点，经过 $r$ 天，它会感染 $2r+1$ 头奶牛，那么对于这段长度为 $l$ 的连续 $1$ 段，它最少需要 $\biggl\lceil\dfrac{l}{2r+1}\biggl\rceil$ 天。

最后，答案就是这些连续 $1$ 段所需奶牛的总和。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll Maxn=3e5+7,inf=1e12;
ll N,res=inf,ans;
// day 
char S[Maxn];
vector<ll>g;

int main(){
	scanf("%lld",&N);
	cin>>(S+1);S[N+1]='0';
	ll cnt=0;
	for(ll i=1;i<=N+1;i++){
		if(S[i]!=S[i-1]&&S[i]=='1') cnt=1;
		if(S[i]==S[i-1]&&S[i]=='1') cnt++;
		if(S[i]!=S[i-1]&&S[i-1]=='1'){
			if(i-cnt==1) res=min(res,cnt-1);
			else if(i==N+1) res=min(res,cnt-1);
			else res=min(res,(cnt-1)/2);
			g.emplace_back(cnt),cnt=0;
		}
	}
	for(auto i:g){
		ans+=ceil(i*1./(res*2+1));
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：紊莫 (赞：2)

题意略。

## 思路

首先对每一个连续块分开处理，分类讨论一下，发现有下面这几种可能。

1. 和边界相连的块。

2. 奇数块。

3. 偶数块。

我们不妨计算出每个块最多能几天形成，这是一个贪心的思路，因为时间越长，答案肯定是越小的，最后对这几个时间取最小值即可。

设一个块的长度为 $len$，则和边界相连的块时间最多可以达到 $len-1$，只要放在边上就可以了，奇数和偶数块考虑每天扩展两个即可。

然后计算答案，假设我们已经求出了当前最小值为 $d$，那么对于每一个病牛，可以扩展 $2d+1$ 头牛（包括自己），做个除法上取整即可。

## 代码

```cpp
//@紊莫 on Luogu (uid=443675)
#include <bits/stdc++.h>
#define F(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
typedef pair<int,int> Pair;
const int N=100005,M=(N<<1),inf=0x3f3f3f3f,mod=1e9+7;
int n,m,ans,day=inf;string s;
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>s; s=" "+s; vector<Pair> a;
	F(i,1,n){
		if(s[i]=='1'){
			int j=i;while(s[j]=='1')j++;
			a.push_back({i,j-1});i=j;
		}
	}
	for(auto x:a){
		int len=x.second-x.first+1;
		if(x.first==1||x.second==n) day=min(day,len-1);
		else day=min(day,(len&1)?len/2:(len/2-1));	
	}
	for(auto x:a){
		int len=x.second-x.first+1;
		ans+=(int)ceil(len*1.0/(day*2+1));
	}cout<<ans;
    return 0;
}
```


---

