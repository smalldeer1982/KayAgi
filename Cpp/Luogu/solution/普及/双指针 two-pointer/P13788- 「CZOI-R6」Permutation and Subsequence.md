#  「CZOI-R6」Permutation and Subsequence

## 题目描述

给定两个长为 $n$ 的由 $1 \sim n$ 构成的**排列** $a, b$。你需要求出有多少个 $a$ 的 **非空** 连续子段是 $b$ 的子序列。

序列 $c$ 是序列 $a$ 的连续子段，当且仅当在序列 $a$ 的 *开头和结尾* 各删除若干（可能为 $0$）个元素，能够得到序列 $c$；序列 $c$ 是序列 $b$ 的子序列，当且仅当在序列 $b$ 中 *任意位置* 删除若干（可能为 $0$）个元素，能够得到序列 $c$。

## 说明/提示

**【数据范围】**

**本题采用捆绑测试。**

- Subtask #1（$10\ \text{pts}$）：$n\le 5$。
- Subtask #2（$30\ \text{pts}$）：$n\le 10^3$。
- Subtask #3（$30\ \text{pts}$）：$a_i=i$。
- Subtask #4（$30\ \text{pts}$）：无特殊限制。

对于 $100\%$ 的数据，$1\le n\le 10^6$，$a,b$ 构成 $1 \sim n$ 的排列。

## 样例 #1

### 输入

```
5
3 5 2 4 1 
2 4 5 3 1 ```

### 输出

```
8```

# 题解

## 作者：fish_love_cat (赞：5)

$a$ 里的具体值显然是没用的，考虑将其每个元素的下标映射到 $b$ 中。具体的，我们令 $t_{a_i}=i$，然后 $b_i\gets t_{b_i},a_i\gets i$。

以样例为例，转化后有 $a=\{1,2,3,4,5\},b=\{3,4,2,1,5\}$。

此时仍然和原情况等价。

这个时候考虑问题，我们发现就是求 $b$ 的连续上升子序列个数。

简单 dp 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int p[1000005];
int a[1000005];
int dp[1000005];
int ans;
signed main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        p[x]=i;
    }
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        a[i]=p[x];
    }
    for(int i=1;i<=n;i++){
        dp[a[i]]+=dp[a[i]-1]+1;
        ans+=dp[a[i]];
    }
    cout<<ans;
    return 0;
}
// 「将来，我一定会成为像珂朵莉学姊那样的妖精兵。」
// 「……我说的将来，就是将来啊。」
// 「比明天稍远一点的未来。」

// Tiat Siba Ignareo
```

---

## 作者：HEYTEA (赞：2)

## 题目大意

> 找到序列 $c$ 是序列 $a$ 的连续子段，并且只能在序列 $a$ 的**开头和结尾**各删除若干（可能为 0）个元素；找到序列 $c$ 是序列 $b$ 的子序列，并且可以在序列 $a$ 的**任意位置**删除若干（可能为 0）个元素。

题目也是很好理解的。

## 思路

首先第一眼看到题目：数据范围 $n$ 是 $1\le n\le 10^6$ 想都不用想从头到尾依次遍历所有可能的连续子段的时间复杂度是 $n^2$ 肯定是会 `TLE` 的，只能拿 $40$ 分。

于是果断换一种 $\Theta(n)$ 的做法，可以把 $a$ 序列里的每个元素替换成它在 $b$ 序列中的下标，然后就得到了数组 $d$，所以我们就把问题转化为：求 $d$ 序列中有多少个连续子段是**严格递增**的。

严格递增的连续子段等价于 **“连续上升段”**，随后用一次线性扫描即可统计所有这样的子段个数。

#### **思路推导**：

1. 设 $c_x$ 为 $x$ 在 $b$ 中的下标。
2. 令 $d_i=c_{a_i}$。
3. 原题要求：$a_l \text{到} a_r \text{是} b \text{的子序列} \Leftrightarrow c_{a_l} < c_{a_l+1} < \dots < c_{a_r}$。
4. 于是只需统计 $d$ 中所有长度 $\ge 1$ 的 连续上升段的个数。长度为 $k$ 的连续上升段会贡献 $\frac{k(k+1)}{2}$ 个合法子段；但线性扫描时边做边累加即可，无需额外计算。

下面代码的时间复杂度是 $\Theta(n)$ 的，可以通过此题。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000100;
int n,a[N],b[N],c[N],d[N],ans=1,cnt=1;
//快读模板
template<typename _Tp> inline void read(_Tp&x) {
	char ch;bool flag=0;x=0;
	while(ch=getchar(),!isdigit(ch)) if(ch=='-')flag=1;
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	if(flag) x=-x;
}
inline void print(__int128 x) {
	if(x<0) {x=-x;putchar('-');}
	if(x>9) print(x/10);
	putchar(x%10+'0');
}

signed main(){
    read(n);
    for(int i=1;i<=n;i++){
    	read(a[i]);
	}
	for(int i=1;i<=n;i++){
    	read(b[i]);
	}
    for(int i=1;i<=n;i++){
    	c[b[i]]=i;
	}
  // 把 a 映射成 d
    for(int i=1;i<=n;i++){
    	d[i]=c[a[i]];
	}
    cnt=1;    
    for(int i=2;i<=n;i++){
        if(d[i]>d[i-1]){
            ++cnt;
        }
		else{
            cnt=1;
        }
        ans+=cnt;     //以 i 结尾的所有上升子段   
    }
    print(ans);
    cout<<endl;
    return 0;
}
```

---

## 作者：yanzixuan2024 (赞：2)

marp:true

---
### 题意

统计排列 $a$ 的非空连续子段中，有多少个是排列 $b$ 的子序列。

### 分析

我们需要证明：$a$ 的连续子段 $a_i,a_{i+1},\dots,a_j$ 是 $b$ 的子序列，当且仅当该子段在 $b$ 中的位置构成严格递增序列。

1. 必要性

若 $a_i,a_{i+1},\dots,a_j$ 是 $b$ 的子序列，则根据子序列定义，存在 $b$ 中的位置序列 $k_i<k_{i+1}<\dots<k_j$，使得 $b_{k_m}=a_m$（其中 $i\leq m\leq j$）。

由于 $pos_x$ 表示 $x$ 在 $b$ 中的位置（即 $pos_{a_m}=k_m$），因此 $pos_{a_i}<pos_{a_{i+1}}<\dots<pos_{a_j}$，即位置序列严格递增。

2. 充分性

若 $a_i,a_{i+1},\dots,a_j$ 在 $b$ 中的位置序列严格递增（即 $pos_{a_i}<pos_{a_{i+1}}<\dots<pos_{a_j}$），则在 $b$ 中取这些位置对应的元素，恰好是 $a_i,a_{i+1},\dots,a_j$，且顺序与 $b$ 中一致。
根据子序列定义，$a_i,a_{i+1},\dots,a_j$ 是 $b$ 的子序列。

注意，$pos$ 是元素到**固定位置**的映射，而 $k$ 是**动态**的子序列位置。

综上，问题可转化为：统计数组 $c$ 中所有非空连续严格递增子段的数量，其中 $c_i=pos_{a_i}$（即 $a$ 中元素在 $b$ 中的位置）。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1000005;
int a[maxn],b[maxn],n,pos[maxn],c[maxn];
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",a+i);
    for(int i=1;i<=n;++i) scanf("%d",b+i),pos[b[i]]=i;
    for(int i=1;i<=n;++i) c[i]=pos[a[i]];
    ll sum=1;
    int cnt=1;
    for(int i=2;i<=n;++i){
        if(c[i]>c[i-1]) ++cnt;
        else cnt=1;
        sum+=cnt;
    }
    printf("%lld",sum);
}
```

---

## 作者：Make_China_Great (赞：2)

## 思路

盲目的 DP 可能做不出来，因为复杂度要求 $O(n)$。

我们想一想，可以再开一个数组 $s$，$s_i$ 表示 $a_i$ 在数组 $b$ 中出现的位置。

我们拿样例举例。

样例的数组 $a$ 与数组 $b$ 如下。

`3 5 2 4 1` `2 4 5 3 1`

所以 $s$ 数组即为

`4 3 1 2 5`

如果还是没听懂，我再来详细解释一下。$a_1$ 为 $3$，而 $3$ 是在 $b$ 数组中第 $4$ 个位置出现的，即 $b_4=3$，所以 $s_1=4$。

然后如何 $O(n)$ 处理呢？

我们可以先用一个数组 $p$，$p_i$ 表示 $b$ 数组中 $i$ 出现的位置，比如样例，$p_1$ 即为 $5$，这样，数组 $p$ 就可以在边读入 $b$ 的时候边处理，复杂度符合标准。

考虑如何从 $p$ 转化为 $s$。我们在处理完数组 $p$ 的时候，再遍历一下数组 $a$，让所有的 $s_i=p_{a_i}$，这样就处理完毕了。

之后，由于在 $a$ 数组中的子序列要求连续，而 $b$ 数组没有要求连续，所以我们遍历 $s$ 数组，看 $s$ 数组里有多少个连续的上升子序列就可以了。

为什么这样可以呢？因为我们找到了所有 $a_i$ 在数组 $b$ 中出现的位置，这样如果 $s_{i+1}>s_i$ ，也就意味着 $a_i$ 在数组 $b$ 中出现的位置比 $a_{i+1}$ 要靠前，也就符合要求了。

## 代码

我认为思路已经讲解很详细了，如果还是看不懂，那就参考代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],b[1000005],p[1000005],s[1000005],dp;
long long ans;
int main(){
    cin>>n;
    for(int i=0;i<n;i++)
    cin>>a[i];
    for(int i=0;i<n;i++){
        cin>>b[i];
        p[b[i]]=i;
    }
    for(int i=0;i<n;i++)
    s[i]=p[a[i]];
    for(int i=0;i<n;i++){
        if(i==0||s[i]<s[i-1])dp=1;
        else dp++;
        ans+=dp;
    }
    cout<<ans;
}
```

---

## 作者：IMGCsir (赞：1)

## 题目大意
给定两个 $1 \sim n$ 的排列 $a$ 和 $b$，求 $a$ 有多少个非空连续子段（子数组）在 $b$ 中作为子序列出现。
## 解题思路
通过观察发现：$a$ 的一个连续子段是 $b$ 的子序列当且仅当该子段中每个元素在 $b$ 中的位置构成严格递增序列。

我们可以先预处理
 - 创建 $pb$ 数组，记录每个值在 $b$ 中的位置。
 - 将 $a$ 数组转换为 $arr$ 数组，其中 $arr_i = pb_{a_i}$。

然后寻找连续递增段：在 $arr$ 数组中找出所有最长的连续递增子数组，并计算出其包含的所有有效子段。

对于每个长度为 $L$ 的连续递增段，其包含的有效子段数量为 $L \times (L + 1) \div 2$。

最后将所有连续递增段的子段数量相加得到最终答案。

这种方法将原问题转化为简单的寻找连续递增序列问题，时间复杂度为 $O(n)$。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,a[N],b[N],pb[N],arr[N];
int main() {
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    for(int i=0;i<n;i++){//预处理
        scanf("%d",&b[i]);
        pb[b[i]]=i;
    }
    for(int i=0;i<n;i++)arr[i]=pb[a[i]];//预处理
    long long ans=0;
    int start=0;
    for(int i=1;i<=n;i++) {//寻找连续递增段并累加贡献
        if(i==n or arr[i]<=arr[i-1]){
            int len=i-start;
            ans+=(long long)len*(len+1)/2;
            start=i;
        }
    }
    printf("%lld\n",ans);//输出
    return 0;
}
```

---

## 作者：chenzefan (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13788)
## 前言
终于想出了一个奇葩思路，或许是正解？
## 思路
首先 $1 \le n \le 10^6$，考虑 $O(n)$ 和 $O(n \log n)$ 的时间复杂度，在百般思索下，感觉更像 $O(n)$ ~~，当然，你用 map 多一个 $\log$ 我也不能说什么~~。

然后就是线性的做法。

答案 $ans$ 由两部分组成，一部分是长度为 $1$ 的连续子段，满足题目要求的**非空**，这一部分的答案就是 $n$，还有一部分就要算了。

不难发现，当确定一部分区间内是否可以组合成答案时，我们就可以求出排列组合数。

先映射排列 $b$ 的下标，用什么随便，多个 $\log$ 也不会超时，我用的是一个 $id$ 数组，$id_i$ 表示 $i$ 在排列 $b$ 中的位置，也就是说，$b_{id_x}=x$。

然后可以使用类似动态规划的方法，定义 $dp_i$ 表示以 $i$ 为结尾的最长满足条件的连续子段的长度（排列 $a$ 中），可以用 $id$ 数组来转移。就像这样：
```cpp
for(int i=2;i<=n;i++)
    if(id[a[i-1]]<id[a[i]])
        dp[i]=dp[i-1]+1;
```
意思就是此时的 $a_i$ 在排列 $b$ 中的位置如果在 $a_{i-1}$ 之后，那么此时就可以在以 $i$ 结尾的子序列后加上一个 $i$，因为不要求连续。所以 $dp_i=dp_{i-1}+1$。

然后再线性求答案。

注意到如果 $dp_{i+1}=0$ 时（当然，最后一段要算上，所以 $i+1 \le n+1$），$dp_i$ 可以用来转移答案。

此时的答案经过组合后共有 $\frac{dp_i \times (dp_i+1)}{2}$，直接将 $ans$ 累加上去，算完后，这另外一部分的答案也就算好了。然后输出即可。

由于 $ans$ 的计算极有可能超出 int 的范围，所以要开 long long。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,a[N],dp[N],id[N],ans;
signed main(){
    scanf("%lld",&n);ans=n;
    for(int i=1;i<=n;i++) scanf("%lld",a+i);
    for(int i=1,x;i<=n;i++) scanf("%lld",&x),id[x]=i;
    for(int i=2;i<=n;i++)
    	if(id[a[i-1]]<id[a[i]])
    		dp[i]=dp[i-1]+1;
    for(int i=1;i<=n;i++)
    	if(dp[i+1]==0) ans+=(dp[i]*(dp[i]+1)/2);
    printf("%lld",ans);
    return 0;
}

```
撒花！

---

## 作者：Lemon19 (赞：0)

观察题目，我们发现 $a, b$ 是全排列，故 $a, b$ 中的元素值一一对应。我们将 $b$ 进行桶排便能很快找出 $a, b$ 的对应关系。  
如 $a = {2, 1, 3, 4}$，$b = {3, 2, 4, 1}$ 中，$a_1$ 对应 $b_2$，$a_2$ 对应 $b_4$。

容易得到，任意 $a$ 的非空连续子段是 $b$ 的子序列当且仅当此子段每个元素所对应 $b$ 的元素的下标逐渐变大（即对应元素依次排开）。  
还是 $a = {2, 1, 3, 4}$，$b = {3, 2, 4, 1}$，子段 $a_1, a_2$ 对应子序列 $b_2, b_4$，子段 $a_2, a_4$ **不对应**子序列 $b_3, b_4$，因为顺序不同。

此外，我们还发现，若 $a$ 的子段 $c$ 是 $b$ 的子序列，则 $c$ 的子段也是，因为其中对应元素依次排开。

所以我们可以双指针找到每一个是 $b$ 的子序列的最长的子段，则所有子段的子段都计入答案。累加即可。

```cpp
#include<iostream>
using namespace std;
typedef long long ll;
const int si=1e6+10;
int n,a[si],b[si],t[si],l,r,la;
//t_i 桶排
ll ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]),t[b[i]]=i;
	l=1,r=1,ans=0;//双指针
	while(l<=n){
		la=t[a[l]];
		while(r<=n&&la<=t[a[r]])
			la=t[a[r]],++r;
		--r;
		ll q=r-l+1;//区间长度
		ans+=q*(q+1)/2;//累加
		++r,l=r,++r;
	}printf("%lld",ans);
	return 0;
}
```

---

## 作者：_DATA_X_ (赞：0)

# P13788 题解：

## 主要思路：

* 用数组 $c$ 存储 $b$ 排列中的每个数在 $a$ 排列中的位置。

::::info[为什么是 $a$ 在 $b$ 中的位置，而不是 $b$ 在 $a$ 中的位置？]
阅读题面可以发现，我们要求的是 $a$ 的连续子段是否是 $b$ 的子序列，不难发现存储 $b$ 在 $a$ 中的位置，再判断位置是否连续会比较好做。
::::

* 我们设 $dp_{b_i}$ 为以 $b_i$ 结尾的在 $a$ 中出现过的子序列的数量，于是不难写出这样的状态转移方程：

$$
dp_{b_i}=dp_{b_j}+1
$$
其中 $j<i$ 且 $c_{b_i}-1=c_{b_j}$。

于是就有了这样的 $O(n^2)$ 暴力代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=1e6+7;
int n;
int a[N],b[N],c[N],dp[N];
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		c[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int sum=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(c[b[i]]-1==c[b[j]]){
				dp[b[i]]=dp[b[j]]+1;
				sum+=dp[b[i]];
			}
		}
	}
	cout<<sum;
	return 0;
}
``````
交上去，获得 $40$ 分。

那么问题又来了，怎么消掉内部循环？

我们不难发现，内部循环遍历时，只有一个 $c_{b_j}$ 满足要求，其余的则都为不必要的操作，那我们就可以用 $a_{c_{b_i}-1}$ 来代替上文的 $c_{b_j}$。

::::info[为什么是 $a_{c_{b_i}-1}$？]
我们都知道，$c$ 数组存储的是 $b$ 中的每个值在 $a$ 中的位置，于是 $c_{b_i}-1$ 的含义就是 $b_i$ 在 $a$ 中的上一个值的位置，于是这一坨的意思也就显而易见了。
::::

知道了这些，我们就可以写出状态转移方程了！

$$
dp_{b_i}=dp_{a_{c_{b_i}-1}}+1
$$

## 代码实现：

定义一个变量存储最终答案，再用上文的状态转移方程求和就可以了。

~其实上文那一大坨放代码里也挺清晰的。~

**[AC](https://www.luogu.com.cn/record/232402445) Code：**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N=1e6+7;
int n;
int a[N],b[N],c[N],dp[N];
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		c[a[i]]=i;//存储位置
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int sum=0;//存最终答案
	for(int i=1;i<=n;i++){
		dp[b[i]]=dp[a[c[b[i]]-1]]+1;//状态转移方程
		sum+=dp[b[i]];
	}
	cout<<sum;
	return 0;//完结撒花！！！
}
``````

感谢阅读。

写题解不易，留个赞再走吧！！！

---

## 作者：elonzhang (赞：0)

# [P13788  「CZOI-R6」Permutation and Subsequence](https://www.luogu.com.cn/problem/P13788)

## 思路
因为我们要求的东西在 $a$ 中是连续的，所以我们可以考虑将答案直接从在 $a$ 中的前一个数更新过来，这样就保证这个方案一定在 $a$ 中是连续的。然后我们令数组 $id_i$ 表示其在 $a$ 中的位置，随后顺序遍历 $b$ 初始化 $dp_i = 1$ （单独的一个数字肯定既是 $a$ 的字串又是 $b$ 的子序列），同时 $dp_{b_i} \gets dp_{b_i}+dp_{a_{id_{b_i}}-1}$，也就是加上其在 $a$ 中前一个数的答案，这样就做完了。这是正确的，因为如果前一个没有值，那么说明在 $b$ 中他们不是子序列，也就不能取其余以它为结尾的在 $a$ 中的字串。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define freop(s) freopen(s".in","r",stdin);freopen(s".out","w",stdout);
#define int long long
#define double long double
#define re register
#define endl '\n'
#define inf 0x7f7f7f7f7f7f7f7f
#define lb(x) (x&-x)
#define pii pair<int,int>
#define fir first
#define sec second
#define umap unordered_map
#define uset unordered_set
const int N=1e6+1;
int n,a[N],id[N],dp[N],ans;//如上文所说，b在循环中

signed main(){
	cin.tie(0)->ios::sync_with_stdio(false);
	cout.tie(0);
//	freop();
//↑以上为初始化↑
//------------------------------
	cin >> n;
	for(int i = 1;i<=n;++i) cin >> a[i],id[a[i]]=i;
	for(int i = 1,b;i<=n;++i){
		cin >> b,dp[b]=1;
		dp[b]+=dp[a[id[b]-1]];更新dp数组
		ans+=dp[b];//统计答案
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：qW__Wp (赞：0)

因为做过 [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439) 所以秒了。

考虑建立 $a$ 在 $b$ 中的映射 $q$（即记录 $a_i$ 在 $b$ 中的位置）。具体地，$\forall 1 \le i \le n,p_{b_i}=i$；$\forall 1 \le i \le n,q_i=p_{a_i}$。

一个显而易见的事实是，$q$ 中上升的子序列映射回 $a$ 中的子序列，是 $b$ 的子序列。

问题转换为求 $q$ 的非空上升连续子段数量。可以将 $q$ 划分为若干极长上升子段。对于某一段，则记其长度为 $l$，则这段的贡献为 $\frac{1}{2}l(l + 1)$。

时间复杂度 $O(n)$。

::::info[Code]
```cpp
#include <bits/stdc++.h>
#define int long long // 祖宗 
#define endl '\n'
#define INF 0x3f3f3f3f
#define INFF 1e18

using namespace std;

const int N = 1e6 + 5;

int a[N], p[N], q[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; cin >> n;
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i ++) {
		int b; cin >> b;
		p[b] = i;
	}
	for (int i = 1; i <= n; i ++) q[i] = p[a[i]];
	int ans = 0, sum = 0;
	for (int i = 1; i <= n; i ++) {
		if (q[i] > q[i - 1]) {
			sum ++;
		} else {
			ans += sum * (sum + 1) / 2;
			sum = 1;
		}
	}
	ans += sum * (sum + 1) / 2;
	cout << ans;
	return 0;
}
```
::::

---

## 作者：lw393 (赞：0)

双指针。

我们发现，若 $[l,r]$ 是合法的连续段，则有 $l\le p\le r$ 时，$[l,p]$ 与 $[p,r]$ 都是合法的。

那我们就需要求出最长的段。

我们定义 $p_{b_i}=i$，这样我们 $p_{a_i}$ 的每个最长上升连续段就是我们所求。

对于一个连续段为 $l$，合法区间数可以计算出，为 $\frac{l\times(l+1)}{2}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;

int a[N], b[N], pos[N];

void solve(){
  int n; cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= n; i++) cin >> b[i], pos[b[i]] = i;
  int ans = 0;
  for(int l = 1, r; l <= n; l = r + 1) {
    r = l; int maxn = pos[a[l]];
    while(r <= n && pos[a[r + 1]] > maxn) maxn = pos[a[r + 1]], r++;
    int len = r - l + 1; ans += (len + 1) * len / 2; 
  }
  cout << ans << '\n';
}

signed main(){
  int t = 1;
  //cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
```

---

## 作者：xu_zhihao (赞：0)

注意到输入的 $a,b$ 是 $1 \sim n$ 的排列，这说明不论 $a$ 或 $b$ 都没有重复出现的数字。

我们可以初始化 $w_{b_i}=i$，然后遍历 $a$ 数组。用一个栈来记录信息，最后一个入栈的元素记为 $top$，然后分三类讨论。

1. $w_{top} < w_{a_i}$。可以看成栈内的元素从栈底到栈顶可以看成是序列 $a$ 的一个子串，这个子串记为 $n$，那么对于每一个 $2 \le i \le \lvert n \rvert$ 有 $w_{n_{i-1}} < w_{n_i}$，在子串末尾加入 $a_i$ 性质不变。故直接把 $a_i$ 加入栈顶。

2. $w_{top} >w_{a_i}$。说明加入 $a_i$ 后上述的性质有变，而已在栈内的所有元素符合性质，所以对于 $n$ 的每一个子串（非空）都能在 $b_i$ 中找到一个与其相匹配的子序列。将栈内元素个数记为 $l$，则栈内所有元素对答案的贡献为 $\frac{l(l+1)}{2}$。之后即可清空栈并加入 $a_i$ 元素。

3. 栈为空。同分讨 $1$，直接将 $a_i$ 加入栈顶即可。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int w[1000010];
int a[1000010];
int b[1000010];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	for(int i=1;i<=n;i++){
		cin>>b[i];
		w[b[i]]=i;
	}
	stack<int>q;
	long long ans=0;
	for(int i=1;i<=n;i++){
		if(!q.empty() && w[q.top()]>w[a[i]]){
			long long l=q.size();
			ans+=l*(l+1)/2;
			while(!q.empty())q.pop();
		}
		q.push(a[i]);
	}
	long long l=q.size();
	ans+=l*(l+1)/2;
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：lijingshu_304775 (赞：0)

## 分析

### 题意

给定两个长度均为 $n$ 的由 $1$ 到 $n$ 构成的排列 $a$ 和 $b$。要求求出 $a$ 的非空连续子段中，有多少个是 $b$ 的子序列。

其中，$a$ 的连续子段是指从 $a$ 的开头和结尾各删除若干个元素（可能为 $0$ 个）后得到的序列；$b$ 的子序列是指在 $b$ 中任意位置删除若干个元素（可能为 $0$ 个）后得到的序列。

### 思路

一个序列 $c$ 是 $b$ 的子序列，意味着 $c$ 中元素在 $b$ 中出现的顺序与 $c$ 中元素的顺序一致。对于 $a$ 的连续子段，若要成为 $b$ 的子序列，其对应元素在 $b$ 中的位置应是递增的。

首先，我们可以通过一个 $pos$ 数组记录 $b$ 中每个元素的位置，即 $pos _x$ 表示元素 $x$ 在 $b$ 中的位置。

然后定义 $dp_i$ 表示以 $a_i$ 为结尾的 $a$ 的连续子段中是 $b$ 的子序列的数量。

当考虑 $a_i$时，初始情况下 $dp_i$ 至少为 $1$（即 $a_i$ 自身构成的子段）。

若 $i>1$ 且 $a_{i-1}$ 在 $b$ 中的位置 $pos_{a_{i-1}}$ 小于 $a_i$ 在 $b$ 中的位置 $pos_{a_i}$，说明以 $a_{i - 1}$ 为结尾的符合要求的子段可以和 $a_i$ 组成新的符合要求的子段，所以 $dp_i = dp_{i-1} + 1$。

最后将所有的 $dp_i$ 相加，得到的结果就是答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int a[MAXN], b[MAXN];
int pos[MAXN];
int dp[MAXN];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        pos[b[i]] = i;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int cur = pos[a[i]];
        dp[i] = 1;
        if (i > 1 && pos[a[i - 1]] < cur) {
            dp[i] = dp[i - 1] + 1;
        }
        ans += dp[i];
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：2023fyc (赞：0)

# P13788题解

## 题目大意
给定两个长度为 $n$ 的排列 $a$ 和 $b$。需要统计 $a$ 的所有**非空连续子段**中，有多少个是 $b$ 的**子序列**。

## 解题思路
我们观察到 $a$ 的一个连续子段是 $b$ 的子序列，当且仅当这个子段中的元素在 $b$ 中的出现位置是严格递增的。因为 $b$ 是排列，每个元素在 $b$ 中的位置唯一。于是我们可以分以下步骤解决此题：
1. **预处理**：创建一个数组 $\text{bz}$，其中 $\text{bz}_x$ 表示元素 $x$ 在 $b$ 中的位置。
2. **双指针扫描**：使用两个指针 $l$ 和 $r$ 遍历 $a$ 数组：
   - $l$ 表示当前子段的起始位置，$r$ 表示当前满足条件的子段的结束位置。
   - 对于每个 $l$，尽可能扩展 $r$，直到无法扩展（即 $a_{r+1}$ 在 $b$ 中的位置不大于 $a_r$ 在 $b$ 中的位置）。
3. **统计答案**：对于每个 $l$，从 $l$ 到 $r$ 的连续子段都满足条件，因此共有 $r-l+1$ 个子段，将这些数量累加到答案中。
4. **移动指针**：每次将 $l$ 右移一位，如果 $l$ 超过 $r$，则将 $r$ 变为 $l$。

### 复杂度分析
- 预处理步骤的时间复杂度为 $O(n)$。
- 双指针扫描中，每个元素最多被访问两次（$l$ 和 $r$ 各一次），因此时间复杂度为 $O(n)$。

### CODE
```cpp
#include<bits/stdc++.h>
#define int long long//记得开long long
using namespace std;
int n,l=1,r=1,ans,a[1000005],b[1000005],bz[1000005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i],bz[b[i]]=i;
	while(l<=n){
		while(bz[a[r+1]]>bz[a[r]]&&r<n) r++;//扩展r
		ans+=r-l+1,l++;
		if(l>=r) r=l;//右边界不能小于左边界
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：XXh0919 (赞：0)

我还要写题解！！

## 解法

### 1.双指针

这个方法也是官方的解法。

首先我们可以发现一个性质：数组 $a$ 的某个非空子数组如果能成为数组 $b$ 的子序列，那么这个子数组的每个数的编号在 $b$ 中的编号一定是严格递增的。所以我们可以先将 $a$ 中每个数在 $b$ 中的编号 $posa$ 处理出来，然后用一个双指针处理每一个 $posa_i>posa_{i-1}$ 的部分，将这些部分的答案累加起来就行了，而这些部分的答案就是两个指针的距离。

::::info[为什么答案是两个指针的距离]
假设左端点为 $l$，右端点为 $r$，则长度 $k=r-l+1$。对于这一部分，长度为 $1$ 的、长度为 $2$ 的、长度为 $3$ 的一直到长度为 $k$ 的子数组，每一个都能产生一个的贡献，总共就有 $k$ 个，即长度。这里不用考虑重复，因为在处理这一部分之前，可能重复的那部分已经处理过了。
::::

### Code

```cpp
#include <bits/stdc++.h>
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 15, mod = 998244353;

ll n;
ll a[N], b[N];
unordered_map <ll, ll> posb, posa;

int main () {
	scanf ("%lld", &n);
	for (int i = 1; i <= n; ++ i) scanf ("%lld", &a[i]);
	for (int i = 1; i <= n; ++ i) scanf ("%lld", &b[i]), posb[b[i]] = i;
	for (int i = 1; i <= n; ++ i) posa[i] = posb[a[i]];//预处理每一个位置
	ll res = 0, l = 1, r = 1;
	for (; r <= n; ++ r){
		if (r > 0 && posa[r] <= posa[r - 1]) l = r;//不满足条件，把 l 指针往后跳
		res += r - l + 1;
	}
	printf ("%lld\n", res);
    return 0;
}
```
### 2.dp 做法

这个做法是赛后和同机房的人讨论后写出来的，也是比较好理解的方法。

和上一个做法的一样，我们先来看性质：如果数组 $b$ 的子序列能成为 $a$ 的子数组，那么这个子序列在 $a$ 中的位置一定是连续的（好像是废话）。所以我们可以先将数组 $b$ 中的每个数在 $a$ 中的位置处理出来。接着就是 dp。令 $dp_i$ 表示以 $i$ 这个**位置**为末尾所得到的方案数。根据上面的性质，可得方程 $dp_i=dp_{i-1}+1$。那么答案就是 $\sum_{i=1}^ndp_i$。

### Code

```cpp
#include <bits/stdc++.h>
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
using namespace std;
typedef unsigned long long ull;
constexpr int N = 2e6 + 15, mod = 1e9 + 7, P = 1331;

int n;
int a[N], b[N];
unordered_map <int, int> posa, posb;
long long dp[N];

int main() {
	scanf ("%d", &n);
	for (int i = 1; i <= n; ++ i) scanf ("%d", &a[i]), posa[a[i]] = i;
	for (int i = 1; i <= n; ++ i) scanf ("%d", &b[i]), posb[i] = posa[b[i]];//处理 b 中每个数在 a 中的位置
	long long res = 0;
	for (int i = 1; i <= n; ++ i) {
		dp[posb[i]] = dp[posb[i] - 1] + 1;//转移
		res += dp[posb[i]];//累加答案
	}
	printf ("%lld\n", res);
    return 0;
}
```
记得开 long long。

---

