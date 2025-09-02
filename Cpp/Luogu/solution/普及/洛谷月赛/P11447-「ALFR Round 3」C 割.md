# 「ALFR Round 3」C 割

## 题目背景

**upd:** 添加的 hack 在 Sub 7。

## 题目描述

设 $f(S)$ 表示字符串 $S$ 字典序最大的子序列，给定 $k$，你需要将原字符串 $S$ 分割成 $k$ 段，设第 $i$ 段子串为 $a_i$，则该分割方案的权值为 $\max f(a_i)$，其中 $1\le i\le k$。由于分割方案有很多种，你需要求出所有分割方案中**字典序最小的权值**。

注：这里的权值实际上指的是字符串。

关于子序列的定义：某个序列的子序列是从最初序列通过去除某些元素但不破坏余下元素的相对位置（在前或在后）而形成的新序列。

关于字典序的定义：在字典序中，首先比较两个字符串的第一个字符，如果不同，则第一个字符较小的字符串更小；如果相同，则继续比较下一个字符，依此类推，直到比较完所有字符。如果一个字符串是另一个字符串的前缀，则较短的字符串更小。

## 说明/提示

### 样例解释
可以将字符串 $S$ 分割成 `sky`、`aqua` 这 $2$ 段，这 $2$ 段的 $f$ 分别为 `y`、`ua`，其中字典序最大的 $f$ 为 `y`，所以该分割方案的权值为 `y`。可以证明 `y` 是所有分割方案中字典序最小的权值。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $1$ | $10$ | $n\le 10$ |
| $2$ | $20$ | $n\le 10^2$ |
| $3$ | $20$ | $n\le 3\times 10^2$| 
| $4$ | $10$ | 保证字符串 $S$ 中所有字符都相等 |
| $5$ | $10$ | $k=1$ |
| $6$ | $30$ | - |

对于 $100\%$ 的数据，$1\le k\le n\le 2\times10^5$，且字符串 $S$ 中的字符均为小写英文字母。

## 样例 #1

### 输入

```
7 2
skyaqua```

### 输出

```
y```

# 题解

## 作者：cff_0102 (赞：14)

给定一个字符串 $s$，假设它的最大字符 $c$ 在 $s$ 中出现了 $x$ 次，那么 $f(s)$ 一定以 $x$ 个 $c$ 开头。

给定两个字符串 $s_1,s_2$，假设它们的最大字符都是 $c$，且 $c$ 在 $s_1,s_2$ 中分别出现了 $x_1,x_2$ 次。若 $x_1>x_2$，那么 $f(s_1)$ 在字典序上一定大于 $f(s_2)$，因为它们开头的 $c$ 的个数不一样。

因此，最终的划分方案中，一定要让每个子串中 $c$ 出现的个数的最大值尽可能小。根据抽屉原理（鸽巢原理），这个数是 $\lceil\frac{x}{k}\rceil$。

把那些出现个数更大的分段放到前面。除了最后一段外，让划分的边界刚好在每一段最后一个 $c$ 的右边，这样前 $k-1$ 段的 $f$ 值都正好是 $\lceil\frac{x}{k}\rceil$ 个 $c$，后面不会再有多余的字符，就做到了字典序尽量小。

如果 $k\nmid x$，那么正确答案就是 $\lceil\frac{x}{k}\rceil$ 个 $c$，因为最后一段的 $c$ 的数量小于前面的 $c$ 的数量，它的 $f$ 值不可能成为最终的权值。

否则，最后一段的 $c$ 的个数与前面相同，那么就还需要在最后一个 $c$ 的后面加上从整个字符串的最后一个 $c$ 的后缀最大字典序子序列。这个只需要提前预处理一下，记录下每个位置的后缀最大字符出现的位置即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[240520];
int a[240520];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,k;cin>>n>>k;
	vector<int>v;
	char mx=' ';
	cin>>s+1;
	for(int i=1;i<=n;i++)mx=max(mx,s[i]);
	for(int i=1;i<=n;i++)if(s[i]==mx)v.emplace_back(i);
	int pos=n;a[n]=n+1;
	for(int i=n-1;i>=1;i--){
		a[i]=pos;
		if(s[i]>=s[pos])pos=i;
	}
	if(v.size()%k){
		cout<<string(v.size()/k+1,mx);
	}else{
		cout<<string(v.size()/k,mx);
		for(int i=a[v.back()];i<=n;i=a[i])cout<<s[i];
	}
	return 0;
}
```

另注：上面代码中的 `cin>>s+1` 从 C++20 开始就不能用了，会 CE。

---

## 作者：SFlyer (赞：9)

答案一定不小于整个字符串的最大值，而在一个字符串内小于最大值的字符出现在最后一个最大值的地方就是不可能出现在字典序最大子序列内部的。

这个启发我们首先找出最大值（设为 $x$）的出现位置，设为 $p_1\sim p_m$。那么讨论两种情况：

- $p_m=n$。那么子串 $1\sim p_1,p_1+1\sim p_2,\cdots ,p_{m-1}+1\sim p_m$ 的字典序最大子序列都是 $x$，并且这样分组是优的。那么现在问题转换为：有 $m$ 个东西分成 $k$ 组，这个鸽巢原理即可。
- 否则如果 $k\nmid m$，和原问题一样，答案是 $\lceil \frac{m}{k}\rceil$ 个 $x$ 的拼接，否则答案是 $\frac{m}{k}$ 个 $x$ 的拼接再加上 $p_{m+1}\sim n$ 的字典序最大子序列。这个可以单调栈求出，或者维护后缀最大值出现位置。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 1e6+6;

int n,k;
string a;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>n>>k>>a;
	a=" "+a;
	char mx=0;
	for (int i=1; i<=n; i++){
		mx=max(mx,a[i]);
	}
	vector<int> v;
	for (int i=1; i<=n; i++){
		if (a[i]==mx) v.push_back(i);
	}
	if (a[n]!=mx){
		int cnt=v.size()/k; 
		for (int i=1; i<=cnt; i++) cout<<mx;
		if (cnt*k==v.size()){
			stack<char> st;
			for (int i=v.back()+1; i<=n; i++){
				while (st.size() && st.top()<a[i]) st.pop();
				st.push(a[i]);
			}
			vector<char> ot;
			while (st.size()) ot.push_back(st.top()),st.pop();
			for (int i=ot.size()-1; i>=0; i--) cout<<ot[i];
		}
		else cout<<mx;
		cout<<"\n";
	}
	else{
		int cnt=(v.size()+k-1)/k;
		for (int i=1; i<=cnt; i++) cout<<mx;
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Moya_Rao (赞：9)

# 题目大意
定义 $f(T)$ 表示字符串 $T$ 的所有子序列中字典序最大的一个，**注意其返回值为一个字符串**。

现在有一个字符串 $S$，要求被分成 $k$ 段，这种分法的权值为每个子序列（假设分别为 $a_i$）的 $f$ 函数值的最大值，也就是 $\max f(a_i)$。

可能会有很多分法，所以请输出权值最小的分法，所对应的权值。

# 思路
不可否认，我们肯定是一步一步来推哟。

## 满足什么条件
思考一下，要满足什么条件，才能使得我们可以不动脑子就快速给出答案呢？让我来揭晓一下吧。

首先，我们定义 $c$ 为字符串 $S$ 中**最大的字符**，$cnt$ 为字符串 $S$ 中最大字符 $c$ **出现的次数**。那么，这个 $cnt$ 需要满足什么条件？

对，要满足 $cnt<k$。  
这是什么意思？意思就是，如果我们的 $k$ 比 $cnt$ 要大，那我们可以每次都让一个 $c$ 字符作为一个分割子串的结尾，这样，每个子串的 $f$ 值都一定会是 $c$。但是，这样分完以后，或许还需要继续分一下，没关系，随便分就是了，没什么关系。

所以，现在我们就只要考虑 $cnt \ge k$ 的情况了。

## 到底怎么处理
简单！抽屉原理上场！  
抽屉原理？对啊，好像是的！

现在我们分两种情况来讨论。

- 如果 $k \mid cnt$ 成立：  
那我们就可以让分出的每一组都含有 $cnt \div k$ 个 $c$，答案就是这么多个 $c$ 再加上后面的一串小尾巴，这一串小尾巴可以用倒着求字符 $\max$ 再稍微处理一下搞定。
- 如果 $k \mid cnt$ 不成立：  
那就好办了，反正无论怎么分，根据抽屉原理，总有一份是含有 $\lceil \frac{cnt}{k} \rceil$ 个 $c$ 的，那么答案就是这个了，因为就算是 $\lceil \frac{cnt}{k} \rceil - 1 $ 个 $c$ 再带上一大串尾巴也没办法使自己的字典序超过它。

现在就好办了，算出 $cnt$，分别对应求解一下答案即可。

# 代码
赛时的 AC 代码，不要怀疑啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n,k,cnt,id,p[N];
string s,str;
char ch,mx[N];
int main(){
    cin>>n>>k>>s;s='0'+s;
    ch=s[1];
    for(int i=1;i<=n;i++)ch=max(ch,s[i]);
    for(int i=1;i<=n;i++)if(s[i]==ch)cnt++,id=max(id,i);
    if(k>cnt){cout<<ch;return 0;}
    int ct=(cnt+k-1)/k;
    while(ct--)cout<<ch;
    if(cnt%k==0){
        str=s.substr(id+1);
        int m=str.size();str='0'+str;
        mx[m]=str[m],p[m]=m;
        for(int i=m-1;i>=1;i--){
            mx[i]=mx[i+1],p[i]=p[i+1];
            if(str[i]>=mx[i])mx[i]=str[i],p[i]=i;
        }
        int now=1;string ans="";
        while(now<=m){
            ans+=mx[now];
            now=p[now]+1;
        }
        cout<<ans;
    }
    return 0;
}
```

求点赞，谢谢！

---

## 作者：ChenZQ (赞：9)

我们发现，字符串里最大的字母的位置才有可能影响到整体答案，再进一步的观察，可以发现每一段中字符串里最大的字母的出现次数对答案的影响十分关键，所以我们考虑二分这个出现次数。

考虑二分中的检查，我们可以用一个前缀和来统计最大字母的出现次数，然后每次发现我们分的段里最大字母的出现次数超过了我们二分的值，就在这里画一段。到最后判断画的段数是否超过 $k$。

而此时就有一个细节，最后一段不需要再画了，但是这种方式会被判定为要画，可能影响答案，所以我们可以先退一步，让画的段数可以等于 $k$，而非 $k - 1$。

```cpp
bool check(int m)
{//mx代表整个字符串中的最大字母。k
	int cnt=0,l=0;
	int l1=0;
	for(int i=1;i<=n;i++)
	{
		if(qz[i]-qz[l]>=m)
		{
			l1=l;
			cnt++;l=i;
		}
	}
	int cc=0;
	if(cnt==k)//判断多画一段是否会满足最大字母出现次数小于等于m。
	{
		for(int i=l1+1;i<=n;i++)
		{
			if(mx==s[i]) cc++;
		}
		return cc<=m;
	}
	return cnt<=k;
}
```

而我们知道了每一段中最小的最大字母出现次数后，就可以按照检查的方法，再把答案算一遍，并把分段的方案记录下来。

接下来分为两种情况，首先就是分完后段数小于等于 $k$，由于我们是在最大字母出现位置的后面画段，那么答案就不会有其他字母了，因为最大子序列会先选最大字母，选完这段就结束了，不会有其他答案，所以直接输出我们二分的次数个最大字母。

而如果是分后的段数等于 $k + 1$，我们注意到，我们是因为**直接在最大字母的后面画分界线**导致了会多出一段，也就是说，**撤掉最后一条分界线不会影响最大字母出现的最小次数**，所以我们可以直接撤掉最后一条分界线，但是字符串的末尾会有一些其他字符，需要我们再求一遍最大子序列，我们可以直接预处理出一个后缀最大值，然后发现后缀最大值和这个字符相同就输出这个字符。因为最大子序列每次肯定选的是后面中最大的字符（就是字典序的定义），所以这么做是正确的。

然后这道题就做完了，注意些细节。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k;
int tot=0;
char s[200010];
int c[200010];int qz[200010];
char mx;
bool check(int m)
{
	int cnt=0,l=0;
	int l1=0;
	for(int i=1;i<=n;i++)
	{
		if(qz[i]-qz[l]>=m)
		{
			l1=l;
			cnt++;l=i;
		}
	}
	int cc=0;
	if(cnt==k)
	{
		for(int i=l1+1;i<=n;i++)
		{
			if(mx==s[i]) cc++;
		}
		return cc<=m;
	}
	return cnt<=k;
}
char mxx[1231232];
char fmx[212311];
vector<int> v;
int main()
{
	scanf("%d%d",&n,&k); 
	scanf("%s",s+1);
	bool f=1;
	for(int i=1;i<=n;i++)
	{
		if(s[i]!=s[1])
		{
			f=0;
			break;
		}
	}
	if(f)//部分分。
	{
		int g=n/k;
		if(n%k!=0) g++;
	//	int mx=max(g,n-(g*k));
		for(int i=1;i<=g;i++) cout<<s[i];
		return 0;
	}
	mxx[n]=s[n];
	for(int i=n-1;i>=1;i--) mxx[i]=max(mxx[i+1],s[i]);
	if(k==1)//部分分。
	{
		for(int i=1;i<=n;i++) if(mxx[i]==s[i])cout<<s[i];return 0;
	}
	for(int i=1;i<=n;i++) mx=max(mx,s[i]);
	for(int i=1;i<=n;i++)
	{
		qz[i]=qz[i-1];
		if(s[i]==mx) qz[i]++;
	}
	int l=1,r=n,best=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) best=mid,r=mid-1;
		else l=mid+1;
	}
	int cnt=0,la=0;
	v.push_back(1);
	for(int i=1;i<=n;i++)
	{
		if(qz[i]-qz[la]>=best)
		{
			v.push_back(i);//预处理出画段的位置。
			cnt++;la=i;
		}
	}
	int t=v.size();
	if(cnt==k)
	{
		int g=v[t-2];
		g++;
		for(int i=g;i<=n;i++)
		{
			if(mxx[i]==s[i]) cout<<s[i];
		}
		return 0;
	}
	else
	{
		int a=v[t-2],b=v[t-1];//找最后一段的最大子序列，末尾的一段没有出现最大字母所以不用管，编者这里写的有些多余，直接输出二分结果个最大字母就行了。
		a++;
		//for(int i=0;i<t;i++) cout<<v[i]<<" ";cout<<endl;
		fmx[b]=s[b];
		for(int i=b-1;i>=a;i--) fmx[i]=max(fmx[i+1],s[i]);
		for(int i=a;i<=b;i++) if(fmx[i]==s[i]) cout<<s[i];
	}
}
```

---

## 作者：TemplateClass (赞：7)

Update 24/12/25：被 Hack 了，更新下代码。

---

本题关键在于 $\max\{S\}$。

显然一个划分成的某个区间 $[l, r]$ 内如果包含 $x$ 个 $\max\{S\}$ 且 $S _ r = \max\{S\}$，则 $f\!\left(S _ {[l, r]}\right) = \max\{S\}\times x$。

因为一个划分成的区间内 $\max\{S\}$ 数量的减小会带来其他划分成的区间内 $\max\{S\}$ 数量的增大。所以我们希望尽可能每个区间内的 $\max\{S\}$ 数量相同，即 $\max\{S\}\times\left\lceil\frac{\operatorname{cnt}(\max\{S\})}{k}\right\rceil$ 一定是 $\max f(a _ i)$ 的前缀。

然后讨论 $k$ 能否整除 $\operatorname{cnt}(\max\{S\})$，如果不可以，刚才所述即为答案；否则，说明最后一个 $\max\{S\}$ 后面还有别的字符会加到答案的末尾。此时暴力计算即可。

不难发现暴力地求一个区间 $[l, r]$ 内字典序最大的子序列的方法如下：

- 找到该区间里的最大值第一次出现的位置 $p$，将 $S _ p$ 加入答案，然后把区间范围设为 $[S, r]$；
- 然后照此重复执行，直至 $S > r$。

记得特判 $\operatorname{cnt}(\max\{S\}) < k$ 的情况，此时答案即为 $\max\{S\}$。

代码（赛时代码，很多地方可能写得都不是很优秀）：

```cpp
#include<iostream>
#include<string>
#include<algorithm>
#include<climits>

const int N = 2e5 + 1;
int n, k; std::string s;

int x, y; char tree[N << 2];
char build(int i = 1, int l = 1, int r = n) {
	if(l == r) return tree[i] = s[l];
	
	int mid = (l + r) >> 1;
	return tree[i] = std::max(build(i << 1, l, mid), build((i << 1) + 1, mid + 1, r));
}
char query(int i = 1, int l = 1, int r = n) {
	if(x > r || y < l) return CHAR_MIN;
	if(x <= l && r <= y) return tree[i];
	
	int mid = (l + r) >> 1;
	return std::max(query(i << 1, l, mid), query((i << 1) + 1, mid + 1, r));
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n >> k >> s; s = " " + s;
	
	build(); x = 1, y = n; char maxc = query();
	int cntmax = 0, maxlastpos = 0;
	for(int i = n; i >= 1; --i) {
		if(s[i] == maxc) {
			++cntmax;
			if(!maxlastpos) maxlastpos = i;
		}
	}
	
	if(cntmax < k) std::cout << maxc;
	else {
		int len = cntmax / k + (cntmax % k ? 1 : 0);
		while(len--) std::cout << maxc;
		if(cntmax % k == 0 && maxlastpos != n) {
			x = maxlastpos + 1, y = n;
			while(x <= y) {
				char get = query(); std::cout << get;
				for(int i = x; i <= y; ++i) {
					if(s[i] == get) { x = i + 1; break; }
					else if(i == y) x = n + 1;
				}
			}
		}
	}
	
	return 0;
}
```

---

## 作者：CaiZi (赞：6)

好的部分分对正解可以有启发作用，所以先从两个部分分讲起（虽然我赛时这两个部分分都做出来了还是没写出正解）。

Subtask #4：贪心的考虑，肯定要让分割出来长度最长的字符串最短，根据鸽巢原理答案为 $\lceil\dfrac{n}{k}\rceil$。

Subtask #5：此时不需要分割，只需要求 $f(S)$。你考虑从字符串第一个出现的最大的字符开始，每次跳到该字符后面最大的字符，这个是可以预处理的。

正解：考虑形如下面这样的字符串，其中 $\text{Z}$ 指其中最大的字符，记 $\text{Z}$ 的出现次数为 $t$。
$$\dots\text{Z}\dots\text{Z}\dots\text{Z}\dots\text{Z}\dots$$
- 如果 $k\mid t$，根据 Subtask #4 的原理，每 $\dfrac{t}{k}$ 个 $\text{Z}$ 分成一段。然后问题就转化成了，在这个字符串的中间若干个省略号中分割，求出 $\max f(a_i)$。显然的，将每个分割的位置都放在 $\text{Z}$ 后是最优的。然而这样无论如何都无法处理掉最后的省略号那段，于是 $\max f(a_i)=a_k$。套用 Subtask #5 的做法，求出 $a_k$ 即可。
- 否则，根据 Subtask #4 的原理，每 $\lceil\dfrac{t}{k}\rceil$ 个 $\text{Z}$ 分成一段。这样操作后，至少还会剩下一次分割机会，将其放在最后一个 $\text{Z}$ 的后面，不会有其他任何多余的字符。

代码如下（时间复杂度线性）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,x,y,a[200001],b;
char m;
string s;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>n>>k>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		m=max(m,s[i]);
	}
	for(int i=1;i<=n;i++){
		if(s[i]==m){
			x++;
			y=i;
		}
	}
	b=n;
	for(int i=n-1;i>=1;i--){
		a[i]=b;
		if(s[i]>=s[b]){
			b=i;
		}
	}
	if(x%k==0){
		for(int i=1;i<=x/k;i++){
			putchar(m);
		}
		for(int i=a[y];i!=0;i=a[i]){
			putchar(s[i]);
		}
	}
	else{
		for(int i=1;i<=x/k+1;i++){
			putchar(m);
		}
	}
	return 0;
}
```

---

## 作者：lijunxi20231818 (赞：6)

这是一道非常细节的贪心题，赛时硬控本蒟蒻 $\text{1.5h}$。

## 部分分

本题的部分分设置很好地启发了对正解的思考。

### Subtask #4

特殊性质：保证字符串 $S$ 中所有字符都相等。

贪心地，将字符尽可能平均分配，让最大字符在每个块中出现次数尽可能小，显然答案为 $\lceil \frac n k \rceil$。

### Subtask #5

特殊性质：$k=1$。

这部分就是求字典序最大的子序列的板子，我们每次贪心地选择字典序最大的字符即可。

```cpp
pair<int, int> mxx[200005];
for(int i = n; i > 0; i--){
	int now = s[i] - 'a';
	if(now >= mxx[i + 1].first){
		mxx[i] = make_pair(now, i);
	}else{
		mxx[i] = mxx[i + 1];
	}
}
int x = 1;
while(x <= n){
	putchar((char)(mxx[x].first + 'a'));
	x = mxx[x].second + 1;
}
```

## 正解

类似于 Subtask #4，为使答案最小，我们要让最大字符 $mx$ 尽量平均分配。

有分类讨论：

> 若 $k∤n$，
>
> 此时一些块中有 $\lceil \frac n k \rceil$ 个 $mx$，由于最后一个块的最后一个 $mx$ 后的字符也会产生贡献且不可避免，我们贪心地让前面的块包含更多的 $mx$。
>
> 为了避免前面 $k - 1$ 块中最后的 $mx$ 后的字符有贡献，我们直接把这些字符划分到下一个块，具体而言是对于前 $k-1$ 个块，都在最后的 $mx$ 的后面进行块之间的分割。
>
> 例子：
> ```text
> 26 3
> c z z c z c z | c z c z c z | c z c z c z j x a k i o i
> ```
>
> 答案为 $\lceil \frac n k \rceil$ 个 $mx$。

> 若 $k∣n$，
>
> 此时每个块都包含 $\frac n k$ 个 $mx$。
>
> 同前一种情况，我们对前 $k-1$ 个块，都在最后的 $mx$ 的后面进行块之间的分割。
>
> 此时答案必定由最后一个块贡献。
>
> 答案的前 $\frac n k$ 位显然为 $mx$，然后我们从最后的 $mx$ 下一位开始跑一边字典序最大子序列即可，这一步同 Subtask #5。

## Code

[赛后提交 AC 记录](https://www.luogu.com.cn/record/195581855)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
char s[200005];
pair<int, int> mxx[200005];
signed main(){
	cin >> n >> k >> (s + 1);
	int mx = 0;
	for(int i = 1; i <= n; i++){
		mx = max(mx, s[i] - 'a');
	}
	vector<int> pos;
	for(int i = 1; i <= n; i++){
		if(s[i] - 'a' == mx){
			pos.push_back(i);
		}
	}
	int cnt = pos.size();
	if(cnt % k != 0){
		int len = cnt / k + 1;
		for(int i = 1; i <= len; i++) putchar((char)(mx + 'a'));
	}else{
		int len = cnt / k;
		for(int i = 1; i <= len; i++) putchar((char)(mx + 'a'));
		for(int i = n; i > pos.back(); i--){
			int now = s[i] - 'a';
			if(now >= mxx[i + 1].first){
				mxx[i] = make_pair(now, i);
			}else{
				mxx[i] = mxx[i + 1];
			}
		}
		int x = pos.back() + 1;
		while(x <= n){
			putchar((char)(mxx[x].first + 'a'));
			x = mxx[x].second + 1;
		}
	}
	return 0;
}
```

---

## 作者：hanchengyi (赞：3)

## 思路

记 $S$ 中最大的字符为 $C$，出现个数为 $cnt$。

手推一下 $f(S)$ 发现，$f(S)$ 总是想先选到 $S$ 中的 $C$，无论第一个 $C$ 有多靠后。为了不让它选了 $C$ 后继续去选后面小于等于 $C$ 的字符作“尾巴”，分段时最优一定时断在 $C$ 后，如果可以每个 $C$ 后都断，那么答案就是 $C$，这是最好情况。但是当 $k < cnt$ 时，就不一定了。

根据抽屉原理，我们先在每一段放 $\lfloor \frac{cnt}{k} \rfloor$ 个 $C$。当 $k \nmid cnt$ 时，再将多余的 $C$ 放入段中，答案就是 $\lfloor \frac{cnt}{k} \rfloor + 1$ 个 $C$。当 $k \mid cnt$ 时，最后一个 $C$ 的后面会带着一串“尾巴”，答案就是 $\lfloor \frac{cnt}{k} \rfloor$ 个 $C$ 加后面一串“尾巴”。

## 代码


```cpp
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define vi vector<int>
#define mii map<int, int>
#define pii pair<int, int>
#define pi priority_queue<int>
#define pib priority_queue<int, vector<int>, greater<int> >
#define ll long long
#define db double
#define ldb long double
#define ull unsigned long long
#define lowbit(x) (x) & (-x)
#define endl '\n'

using namespace std;

const int N = 2e5 + 7;

int n, k;
char s[N];

priority_queue<double> q;

char c[N];

signed main() {
	//	ios::sync_with_stdio(false);
	//	cin.tie(0); cout.tie(0);
	
	cin >> n >> k;
	scanf("%s", s + 1);
	
	char maxx = 0;
	int tot = 0;
	int lasts;
	for(int i = 1; i <= n; i ++) {
		if(s[i] >= maxx) {
			maxx = s[i];
		}
	}
	
	for(int i = n; i >= 1; i --) {
		c[i] = max(c[i + 1], s[i]);
	}
	
	for(int i = 1; i <= n; i ++) {
		if(s[i] == maxx) {
			lasts = i;
			tot += 1;
		}
	}
	
	int x = tot / k;
	int y = tot % k;
	
	if(y) {
		for(int i = 1; i <= x + 1; i ++) cout << maxx;
	}else {
		if(lasts == n) for(int i = 1; i <= x; i ++) cout << maxx;
		else {
			for(int i = 1; i <= x; i ++) cout << maxx;
			for(int i = lasts + 1; i <= n; i ++) if(c[i] == s[i]) cout << s[i];	
		}
	}
	cout << endl;
	return 0;
}
```

---

## 作者：YBJ1006 (赞：3)

本蒟蒻赛时写的比较傻，首先从特殊性质考虑子任务 4，简单思考一下就会知道答案为 $\lceil n/k \rceil$。

子任务 5，用一个函数实现返回一段字符串的 $f(S)$。

最后思考正解，首先字典序大代表着这个字符串的开头的字符尽可能大，其次长度尽可能长，所以我们考虑在最大字符的后面分割，首先统计最大字符的出现位置和个数。

1. 如果个数小于 $k$。那么可以把每个最大字符都分开。此时答案就是最大字符。
2. 如果个数等于 $k$。那么我们把最后一个最大字符的位置开到原字符串结尾这段字符串称之为 $t$，那么答案显然就是 $f(t)$。因为前面每一段的权值为单个最大字符，而 $f(t)$确实一个最大字符后面加一部分，显然字典序更大。
3. 个数大于 $k$。此时只需要贪心得加上枚举，让多个最大字符在同一段，重复 1 和 2 即可。

**具体细节看代码**

```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 20;
int n, k;
int l;
char fun(string s)
{
    int id = l;
    char c = s[l];
    for (int i = l; i < n; i++)
    {
        if (s[i] > c)
        {
            id = i;
            c = s[i];
        }
    }
    l = id + 1;
    return s[id];
}
int a[N];
bool cmp(char a, char b)
{
    return a > b;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    string s;
    cin >> s;
    int f = 1;
    for (int i = 0; i < n-1; i++)
    {
        if (s[i] != s[i + 1])
            f = 0;
    }
    if (k == 1)
    {
        l = 0;
        string t;
        while (l <= n)
        {
            t += fun(s);
        }
        cout << t;
        return 0;
    }
    if (f == 1)
    {
        if (n % k == 0)
        {
            int c = n / k;
            for (int i = 0; i < c; i++)
            {
                cout << s[0];
            }
            return 0;
        }
        else
        {
            int c = n / k+1;
            for (int i = 0; i < c; i++)
            {
                cout << s[0];
            }
            return 0;
        }
    }
    
    int id = 0;
    char c = s[0];
    for (int i = 0; i < n; i++)
    {
        if (s[i] > c)
        {
            id = i;
            c = s[i];
        }
    }
    int tot = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == c)
        {
            a[++tot] = i;
        }
    }
    if (k > tot)
    {
        cout << c;
        return 0;
    }
    else if (k == tot)
    {
        string t;
        t += c;
        l = a[tot] + 1;
        while (l <= n)
        {
            t += fun(s);
        }
        cout << t;
        return 0;
    }
    for (int i = 2;; i++)
    {
        int t = tot;
        if (t % i != 0)
        {
            t /= i, t += 1;
        }
        else
        {
            t /= i;
            if (k == t)
            {
                if (a[n] != c)
                {
                    string t;
                    for (int j = 1; j <= i; j++)
                        t += c;
                    l = a[tot] + 1;
                    while (l <= n)
                    {
                        t += fun(s);
                    }
                    cout << t;
                    return 0;
                }
            }

        }
        if (k >= t)
        {
            for (int j = 1; j <= i; j++)
                cout << c;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：linjunye (赞：3)

### 从特殊性质开始思考

考虑子任务 $4$ 怎么写。

我们发现，当一个字符串所有的字符都相同时，每一段的权值就是这一段本身，俗称“全选”。

那么，我们要找到字典序最小的权值，也就是长度最小的权值（因为每一个权值所构成字符都是相同的）。

容易想到鸽巢原理，那么所找的权值也就显而易见了，它的长度为 $\lceil\frac{n}{k}\rceil$。

这里放一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=310;
int n,k;
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	cin>>s;
	n=(n+k-1)/k;
	for(int i=1;i<=n;i++)cout<<s[0];
	return 0;
}
```

然后考虑子任务 $5$ 怎么写。

子任务 $5$ 本质上就是让你求“字典序最大子序列”。

考虑贪心。将字符串按从大到小排序，并记录原先的下标在排序后的位置。

可能不好理解，所以给个示例：

```
字符串 accb => ccba
下标   1234 => 2341
```

观察示例，发现构造此子序列，相当于求一个下标从 $1$ 开始的最长上升子序列，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
int n,k;
struct Node{
	char ch;
	int id;
}a[N];
bool cmp(Node a,Node b){
	if(a.ch==b.ch)return a.id<b.id;
	return a.ch>b.ch;
}
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	cin>>s;
	if(k==1){
		s=" "+s;
		for(int i=1;i<=n;i++){
			a[i].ch=s[i];
			a[i].id=i;
		}
		sort(a+1,a+n+1,cmp);
		int L=0;//下界
		for(int i=1;i<=n;i++){
			if(L<a[i].id){//是可以构成上升子序列的
				cout<<a[i].ch;
				L=a[i].id;
			}
		}
	}
	else{//这里是特殊性质4的代码
		n=(n+k-1)/k;
		for(int i=1;i<=n;i++)cout<<s[0];
	}
	return 0;
}
```

此代码也将特殊性质 $4$ 结合在一起，可以拿到 $20$ 分。

### 正解

说了这么多，有什么用呢？

仔细想想一次划分对我们新的下标序列的影响。

我们发现，划分似乎可以贪心，每次划分最前面的那些字母。

再想一想，我们好像只用考虑划分最大的字符就可以了，因为首位决定一切。

设最大的字符有 $x$ 个，那么这 $x$ 个字符又都是一样的。

等等……这不是子任务 $4$ 吗？

那就可以写了。但是还是要注意一个细节，当 $k \mid x$ 时，最后的几个字符要与后面的其他字符相连。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300010;
int n,k;
struct Node{
	char ch;
	int id;
}a[N];
bool cmp(Node a,Node b){
	if(a.ch==b.ch)return a.id<b.id;
	return a.ch>b.ch;
}
string s;
string ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	cin>>s;
	s=" "+s;
	for(int i=1;i<=n;i++){
		a[i].ch=s[i];
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i].ch!=a[1].ch)break;
		cnt++;
	}
	if(cnt%k==0){
		int L=-1;
		for(int i=cnt-cnt/k+1;i<=n;i++)//计算最后一段连接后面的权值
			if(L<a[i].id){
				cout<<a[i].ch;
				L=a[i].id;
			}
	}
	else{
		for(int i=1;i<=cnt/k+1;i++)ans+=a[i].ch;
		cout<<ans;
	}
	return 0;
}
```

所以有时候做题可以先不考虑暴力，这样的思路做题也很爽。

---

## 作者：zhanghy123 (赞：2)

### 思路
不难想到一个性质：字符串 $S$ 的字典序最大的子序列，一定为以其**最大字符首次出现**的位置为起点的，**单调不增**序列。所以考虑到使用单调栈维护。显然，当 $k=1$ 时，把整个字符串从头到尾维护一遍的结果就是答案。

现在要分成 $k$  段，可以先把几个最大字符的位置存出来。设有 $cnt$ 个最大字符，一个容易想到的结论是，**最佳的分割方式的分割点一定在这些最大字符之后紧邻的一个位置**。因为每个最大字符，都一定会成为它所在小段 $s$ 的最大字典序子序列 $f(s)$ 的一部分。在其之后紧邻的一个位置分割，就保证了 $f(s)$ 最后一位也是最大字符，没有了后面的冗余字符来使其字典序增大。这样，$f(s)$ 就**仅由最大字符构成**。

那么，问题就转化为将 $cnt$ 个最大字符放入 $k$ 个序列中。要求最小的分割方式权值，就要使最大字符最多的序列中最大字符的数量尽量少。换句话说，最佳的分配方式是按**抽屉原理**，平均地分配最大字符。这时还需要分类：

- 当 $cnt$ 不能被 $k$ 整除时，最大字符最多的区间 $s$ 的 $f(s)$ 就有 $\lceil\frac{cnt}{k}\rceil$ 个字符。此时我们可以将该区间放在前面，**最终答案就是 $\lceil\frac{cnt}{k}\rceil$ 个最大字符**；
- 当能整除时，因为需要平均分配，所以这整个字符串**最后一个最大字符的末尾就没有分割点**。此时，最后一个最大字符后面还有冗余字符，需要再跑一遍单调栈，把这些冗余字符组成的串的最大字典序子序列拼接在 $\frac{cnt}{k}$ 个最大字符之后。

总结：**最终答案为 $\lceil\frac{cnt}{k}\rceil$ 个最大字符。若能整除，则再跑一遍单调栈，把尾巴的最大字典序子序列拼接在后面。**

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k,pos[200001],cnt,top;
string s,ans1,ans2;
char maxx,stk[200001];
void ddz(int begin)//单调栈求以 begin 为起点的最大字典序子序列 
{
	for(int i=begin; i<n; i++)
	{
		while(top && stk[top]<s[i]){top--;}
		stk[++top]=s[i];
	}
	for(int i=1; i<=top; i++)
		cout<<stk[i];
}
int main()
{
	cin>>n>>k>>s; 
	for(int i=0; i<n; i++)
		maxx=max(s[i],maxx);
	for(int i=0; i<n; i++)
		if(s[i]==maxx) pos[++cnt]=i;
	if(k==1){
		ddz(0);
		return 0;
	}
	for(int i=1; i<=ceil(cnt*1.0/k); i++)
		cout<<maxx;
	if(cnt%k==0)//能整分，最后一段需要再求一次 
		ddz(pos[cnt]+1);
	return 0;
}


```

---

## 作者：_H17_ (赞：2)

## 题目分析

有意思的贪心题：把字符串分成 $k$ 段使得每一段的最大字典序子序列的最大序列最小（可能有点绕）。

首先找到最大的字符 $z$（这是表示未知字符，不是表示字符 $\texttt{z}$），假设它出现了 $cnt_z$ 次。

显然如果一个字符串 $s'=t+z$ 其中 $t$ 是一个字符串，那么它的最大字典序子序列是 $z$，受到这启发，当 $k>cnt_z$ 时，答案是 $z$。

考虑 $k\le cnt_z$ 的情况。如果 $cnt_z\bmod k\ne 0$，显然此时的答案是 $\lceil \frac{cnt_z}{k}\rceil$ 个 $z$。但是如果 $cnt_z\bmod k=0$ 时，就不一定了，这时候最后一个 $z$ 之后的字符无论如何也不能利用更后面的 $z$ 来去掉，所以要加上后面的字典序最大子序列。

## 代码

```cpp
#include<bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
using namespace std;
int n,k,cnt[300];
string s;
char maxc,ans;
string get_max(string s){
	vector<char>vec;
	string ret;
	for(auto c:s){
		if(vec.size()==0){
			vec.push_back(c);
			continue;
		}
		if(c<=vec[vec.size()-1]){
			vec.push_back(c);
			continue; 
		}
		auto it=upper_bound(ALL(vec),c,greater<int>());
		vec.erase(it,vec.end());
		vec.push_back(c);
	}
	for(auto c:vec)
		ret=ret+c;
	return ret;
}
bool cmp(string a,string b){
	for(int i=0;i<min(a.size(),b.size());i++)
		if(a[i]!=b[i])
			return a[i]>b[i];
	return a.size()>b.size();
}
int main(){
    cin>>n>>k>>s;
    for(auto c:s)
        cnt[c]++,maxc=max(maxc,c);
    if(cnt[maxc]<k){
        cout<<maxc;
        return 0;
    }
    int x=(cnt[maxc]+k-1)/k,y=cnt[maxc]%k;
    if(y){
	    for(int i=1;i<=x;i++)
	        cout<<maxc;
	    return 0;
	} 
	x=cnt[maxc]/k;
	vector<int>place(1,0);
	vector<string>count(0);
	for(int i=0;i<n;i++){
		if(s[i]==maxc)
			place.push_back(i);
	}
	place.push_back(n);
	for(int i=1;i<=cnt[maxc];i++)
		if(i%x==0)
			count.push_back(s.substr(place[i]+1,place[i+1]-place[i]-1));//place[i]~place[i+1]-1
			//a~b:a,b-a+1,place[i],place[i+1]-place[i];
	/*for(auto p:count)
		cerr<<p<<' ';
	cerr<<'\n';*/
	for(auto&p:count){
		p=get_max(p);
	}
//	sort(ALL(count),cmp);
	for(int i=1;i<=x;i++)
		cout<<maxc;
	cout<<count[count.size()-1];
    return 0;
}
```

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11447)
## 思路
记 $S$ 中有 $x$ 个最大字符 $c$，$a_i$ 中有 $t_i$ 个 $c$，那么 $f(a_i)$ 的结果一定是以 $t_i$ 个 $c$ 开头再加上后面一串尾巴。

可以想到把 $x$ 个 $c$ 均匀地分配到 $k$ 段中，这样就能使得字典序最小。

当 $x\bmod k=0$ 时，$t_i=\dfrac{x}{k}$，由于 $a_k$ 的最后一个 $c$ 后面还可能有字符，故结果的后面会有一段小尾巴，这段小尾巴暴力求出即可。

当 $x\bmod k\not=0$ 时，在均匀分配的情况下显然有至少一个 $i$ 使得 $t_i=\left\lceil\dfrac{x}{k}\right\rceil$，此时的结果即为 $\left\lceil\dfrac{x}{k}\right\rceil$ 个 $c$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[51],mxp,n,k,mx,tn[51];
string str;
string js(int l,int r) {//暴力求出小尾巴
	if(l>r)return ""; //出界，返回空字符串
	int tmx=26;
	while(!tn[tmx])tmx--;
	for(int i=l;i<=r;i++) {
		tn[str[i]-'a'+1]--;
		if(str[i]-'a'+1==tmx) {
			return str[i]+js(i+1,r);
		}
	}
}
int main() {
	cin>>n>>k;
	cin>>str;
	for(int i=0; i<n; i++) {
		int t=str[i]-'a'+1;
		a[t]++;
		if(t>=str[mxp]-'a'+1)mxp=i;//找到最后一个最大字符
	}
	for(mx=26; mx>=1; mx--) {
		if(a[mx]!=0) break;
	}
	char c=(char)mx+'a'-1;
	if(k>a[mx]) {
		cout<<c;
	} else {
		if(!(a[mx]%k)) {
			for(int i=1; i<=a[mx]/k; i++)cout<<c;
			for(int i=mxp+1; i<n; i++) {
				int t=str[i]-'a'+1;
				tn[t]++;
			}
			cout<<js(mxp+1,n-1);
		} else for(int i=1; i<=a[mx]/k+1; i++)cout<<c;
	}
}
```

---

