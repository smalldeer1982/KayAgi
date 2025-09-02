# Repetitions Decoding

## 题目描述

Olya has an array of integers $ a_1, a_2, \ldots, a_n $ . She wants to split it into tandem repeats. Since it's rarely possible, before that she wants to perform the following operation several (possibly, zero) number of times: insert a pair of equal numbers into an arbitrary position. Help her!

More formally:

- A tandem repeat is a sequence $ x $ of even length $ 2k $ such that for each $ 1 \le i \le k $ the condition $ x_i = x_{i + k} $ is satisfied.
- An array $ a $ could be split into tandem repeats if you can split it into several parts, each being a subsegment of the array, such that each part is a tandem repeat.
- In one operation you can choose an arbitrary letter $ c $ and insert $ [c, c] $ to any position in the array (at the beginning, between any two integers, or at the end).
- You are to perform several operations and split the array into tandem repeats or determine that it is impossible. Please note that you do not have to minimize the number of operations.

## 说明/提示

In the first test case, you cannot apply operations to the array to make it possible to split it into tandem repeats.

In the second test case the array is already a tandem repeat $ [5, 5] = \underbrace{([5] + [5])}_{t_1 = 2} $ , thus we can do no operations at all.

In the third test case, initially, we have the following array: $ $$$[1, 3, 1, 2, 2, 3]. $ $  After the first insertion with  $ p = 1, c = 3 $ :  $ $ [1, \textbf{3, 3}, 3, 1, 2, 2, 3]. $ $  After the second insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 2, 2, 3]. $ $  After the third insertion with  $ p = 5, c = 3 $ :  $ $ [1, 3, 3, 3, 1, \textbf{3, 3}, 3, 3, 2, 2, 3]. $ $  After the fourth insertion with  $ p = 10, c = 3 $ :  $ $ [1, 3, 3, 3, 1, 3, 3, 3, 3, 2, \textbf{3, 3}, 2, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([1, 3, 3, 3] + [1, 3, 3, 3])}_{t_1 = 8} + \underbrace{([3, 2, 3] + [3, 2, 3])}_{t_2 = 6}. $ $ </p><p>In the fourth test case, initially, we have the following array:  $ $ [3, 2, 1, 1, 2, 3]. $ $  After the first insertion with  $ p = 0, c = 3 $ :  $ $ [\textbf{3, 3}, 3, 2, 1, 1, 2, 3]. $ $  After the second insertion with  $ p = 8, c = 3 $ :  $ $ [3, 3, 3, 2, 1, 1, 2, 3, \textbf{3, 3}]. $ $  After the third insertion with  $ p = 5, c = 3 $   $ $ [3, 3, 3, 2, 1, \textbf{3, 3}, 1, 2, 3, 3, 3]. $ $  After the fourth insertion with  $ p = 6, c = 2 $ :  $ $ [3, 3, 3, 2, 1, 3, \textbf{2, 2}, 3, 1, 2, 3, 3, 3]. $ $  After the fifth insertion with  $ p = 7, c = 1 $ :  $ $ [3, 3, 3, 2, 1, 3, 2, \textbf{1, 1}, 2, 3, 1, 2, 3, 3, 3]. $ $  The resulting array can be represented as a concatenation of tandem repeats:  $ $ \underbrace{([3] + [3])}_{t_1 = 2} + \underbrace{([3, 2, 1] + [3, 2, 1])}_{t_2 = 6} + \underbrace{([1, 2, 3] + [1, 2, 3])}_{t_3 = 6} + \underbrace{([3] + [3])}_{t_4 = 2}. $ $$$

## 样例 #1

### 输入

```
4
2
5 7
2
5 5
6
1 3 1 2 2 3
6
3 2 1 1 2 3```

### 输出

```
-1
0
1
2
4
1 3
5 3
5 3
10 3
2
8 6 
5
0 3
8 3
5 3 
6 2 
7 1
4
2 6 6 2```

# 题解

## 作者：DarkBird (赞：22)

介绍一个暴力但看起来比较舒服的做法

我们考虑如何构造答案。

假设 $n=8$，$a=\{1,2,3,3,2,4,1,4\}$

我们看第一个失配的地方，此时是 $a_{1}$。

那么我们找到往后第一个 $1$：$a_7$。

我们暴力的让他匹配上，**不用考虑是不是可以节省**，就是按照顺序把 $\{2,3,3,2,4\}$ 全部加一遍，得到：$\{1,2,3,3,2,4,1,2,3,3,2,4,4,2,3,3,2,4\}$

此时我们已经匹配了 $1$，所以可以把已经匹配的删掉，得到 $\{4,2,3,3,2,4\}$

发现没有？

**我们进行一批操作，相当于删掉头和与它匹配的那个字符，再把中间的部分翻转过来**

然后由于一共最多有 $\frac{n}{2}$ 组字符，且每一批操作最多有 $n$ 次小操作，故总操作数量一定不超过 $\frac{n^2}{2}$

最后特判一下某个数出现次数是奇数的情况（显然不能完成）

Code:

```cpp
int n;
vector<int>v;
inline void solve(){
	cin>>n;
	map<int,int>cnt;
	v.clear();cnt.clear();
	for(int i=0,x;i<n;++i)cin>>x,v.push_back(x),++cnt[x];
	for(auto it:cnt)if(it.second%2==1){
		cout<<-1<<'\n';
		return;
	}
	vector<int>ans;
	vector<pair<int,int> >opr;
	int fnt=0;    //fnt是记录前面删除了多少个数
	for(;v.size();){
		int i=0;
		for(int j=i+1;j<v.size();++j){
			if(v[i]==v[j]){
				ans.push_back(2*(j-i));
				int len=j-i-1;
				for(int t=0;t<len;++t)opr.push_back(mp(fnt+1+t+j,v[t+1]));
				fnt+=2*len+2;
				reverse(v.begin()+1,v.begin()+j);
				v.erase(v.begin()+j);
				v.erase(v.begin());
				break;
			}
		}
//		cerr<<"?? "<<fnt<<'\n';
//		for(auto i:v)cerr<<i<<' ';cerr<<'\n';
	}
	cout<<opr.size()<<'\n';
	for(auto p:opr)cout<<p.first<<' '<<p.second<<'\n';
	cout<<ans.size()<<'\n';
	for(auto i:ans)cout<<i<<' ';cout<<'\n';
}
```

---

## 作者：yzy1 (赞：3)

## 题目大意

- 定义一个长度为 $2k(k \in \mathbb N_+)$ 的数组 $a$ 为「双连续」的，当且仅当 $\forall i \in[1,k], a_i=a_{i+k}$。
- 定义一个数组为「好的」，当且仅当该数组能被划分为若干个连续段，且每个连续段都是「双连续」的。
- $t(1\le t \le 3\times 10^4)$ 组数据，每组数据给出一个长度为 $n(1\le n \le 500)$ 的数组 $a(1 \le a_i \le 10^9)$。你可以对这个数组进行最多 $2\times n^2$ 次操作，每次操作定义为选择一个位置 $p(0 \le p\le|a|)$ 和一个整数 $c(1\le c\le 10^9)$，在 $a$ 数组的下标为 $p$ 的整数后面的位置插入两个整数 $c$，若 $p=0$ 则代表在开头插入。你需要构造任意一种合法的方案，或者报告无解。

## 简要做法

- 若 $a$ 数组中有数字出现了奇数次，显然无解：因为你的操作只会对每个数字增加偶数个，而一个「好的」数组中每个整数都应出现偶数次。
- 否则，我们可以按照以下方法构造：
  - 考虑用给出的操作拼出一个「反转」操作：假设我们要把 $\{a_l,a_{l+1},\cdots,a_r\}$ 反转，可以在 $a_r$ 后面依次插入 $a_l,a_l+1,\cdots,a_r$，此时该段区间变为 $\{{\color{red}{a_l,a_{l+1},\cdots,a_r}},{\color{blue}{a_l,a_{l+1},\cdots,a_r}},{\color{red}{a_r,a_{r-1},\cdots,a_l}}\}$，前 $2(r-l+1)$ 个数形成了一个「双连续」数组，我们可以直接把它扔掉，最后得到一个形如 $\{a_r,a_{r-1},\cdots,a_l\}$ 的数组，正好是原区间反转过来。
  - 有了反转操作就好构造了：考虑从 $1$ 到 $n-1$ 遍历 $i$，若 $a_i=a_{i+1}$，则直接让这两个数形成一个「双连续」，然后 $i\gets i+2$。否则，反转区间 $[i,a_i\text{ 下一次出现的下标}-1]$，这会让两个值为 $a_i$ 的元素连在一起。不断重复这个步骤直到 $a_i=a_{i+1}$。
- 上界分析：显然每次「反转」操作的操作次数上界是 $n$。而每次操作都会让两个相同的数连在一起，最差情况发生在 $a$ 中每个整数都出现了零次或两次，这时最多需要进行 $n/2$ 次「反转」操作。所以该构造方式操作次数上界为 $n^2/2$。

## 参考代码

```cpp
void Work(){
  map<int,int> mp1;
  vector<int>ans;
  vector<pair<int,int>>op;
  cin>>n;re(i,n)cin>>a[i],++mp1[a[i]];
  each(x,mp1)if(x.second%2==1)return cout<<"-1\n",void();
  int dlt=0;
  re(i,n-1){
    while(a[i]!=a[i+1]){
      int pos=-1;
      rep(j,i+1,n)if(a[j]==a[i]){pos=j;break;}
      int len=pos-i;
      rep(j,i,i+len-1)op.push_back({j+len+dlt-1,a[j]});
      reverse(a+i,a+i+len);
      ans.push_back(len*2);
      dlt+=len*2;
    }
    ans.push_back(2),++i;continue;
  }
  cout<<op.size()<<'\n';
  each(x,op)cout<<x.first<<' '<<x.second<<'\n';
  cout<<ans.size()<<'\n';
  each(x,ans)cout<<x<<' ';
  cout<<'\n';
}
```



---

## 作者：KiloP (赞：2)

容易发现，一个数组满足题意，当且仅当这个数组中的每个数出现了偶数遍。因为最终要求的数组能被分成许多 tandem 子数组（tandem 定义见原题面），那么最终的数组每个数一定都出现了偶数遍。又因为每次加数是 $2$ 个相同的数一起加，所以原先的数组每个数一定出现了偶数遍。

我们假设当前数组中 $a_1$​ 至 $a_{i-1}$​ 已经满足题意（能分为许多 tandem 子数组，下同）。现在对于 $a_i$​，若后面满足题意，那么一定有一个下标 $j>i$​，使得 $a_i=a_j$​​。

现在我们考虑用至多 $n$​ 次插入来使剩下不满足题意的数的个数减2。

我们就可以用 $(j-1)-(i+1)+1=j-i-1$ 次操作，使得 $a_i$ 至 $a_{j-1}$​​​ 为一个 tandem 数组的前半段。具体如下（当前数组长度为 $t$）。

数组由
$$
a_1\cdots a_ia_{i+1}\cdots a_ja_{j+1}\cdots a_t
$$
经过操作，可以变成（$b_x$，$c_x$ 表示新加入的数，且 $c_x=b_x=a_x$）
$$
a_1\cdots a_ia_{i+1}\cdots a_jb_{i+1}b_{i+2}\cdots b_{j-2}b_{j-1}c_{j-1}c_{j-2}\cdots c_{i+2}c_{i+1}a_{j+1}\cdots a_t
$$
那么此时 $a_i$​​​ 至 $b_{j-1}$​​​ 为一个 tandem 数组，从而，$a_1$​​​ 至 $b_{j-1}$​​​ 满足条件。

此时，原来的不满足条件的数（ $a_i$​​ 至 $a_t$​​​）的个数为 $t-i+1$​。

操作后不满足条件的数（$c_{j-1}$​​​​​ 至 $a_t$​​​​​​）的个数为 $j-1-i+t-j=t-i-1$​。

减了 $2$！

而且，若操作前剩下的数满足题意，那么操作后剩下的数一定满足题意（因为若原来每个数出现了偶数次，操作后每个数仍出现了偶数次）！

从而，我们可以用至多 $n$​ 次操作，使得不满足题意的数的个数减 $2$​！

~~不理解的话就看代码吧~~

总操作数至多 $q=\frac{n^2}2$​，是原题的 $2n^2$​ 的 $\frac14$​。耶！

因为 $n\le500$，所以暴力绰绰有余。

完结撒花！（放上你们最想看的东西）

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, a[1000005];
vector< pair<int, int> > ans;	// 方案
vector< int > num; 				// 长度

void deal() {
	ans.clear(); num.clear();
	int pos = 1, tot = n; 					// tot 是当前数组的长度，pos 是当前不满足题意的数的第一个数
	for(int i = 1; i <= n / 2; i ++) {		// 每次能减2，那么只用n/2次
		int nxt = pos + 1;					// nxt 是之后等于a[pos]的第一个数
		while(a[nxt] != a[pos] && nxt <= tot) nxt ++;
		if(nxt > tot) { puts("-1"); return ; }				// 找不到就输出 -1
		num.push_back((nxt - pos) * 2);						// 这一段tandem数组的长度就是(nxt-pos)*2
		int sum = nxt - 1 - (pos + 1) + 1; sum <<= 1;		// sum这次是要插入的数的总个数
		for(int j = tot; j > nxt; j --) a[j + sum] = a[j];	// 暴力即可，时间绰绰有余
		tot += sum;
		for(int j = pos + 1; j < nxt; j ++) {
			int xx = nxt + j - pos, yy = sum - (j - pos) + 1 + nxt;
			a[xx] = a[yy] = a[j];
			ans.push_back(make_pair(xx - 1, a[j]));
		} // 插入数，记录答案的时候很细节
		pos = pos + sum + 2; // 跳过中间这一段，到下一段不满足题意的数
	}
	cout << ans.size() << endl;
	for(int i = 0; i < ans.size(); i ++) cout << ans[i].first << ' ' << ans[i].second << endl;
	cout << num.size() << endl;
	for(int i = 0; i < num.size(); i ++) cout << num[i] << ' '; cout << endl;
}
signed main() {
	int _; for(cin >> _; _; _ --) {
		cin >> n;
		for(int i = 1; i <= n; i ++) cin >> a[i];
		if(n % 2 == 1) { puts("-1"); continue; }
		deal();
	}
    return 0;
}
```



---

## 作者：Presentation_Emitter (赞：1)

好题。

题目给出的操作过于神仙。因为不需要最小化操作数量，所以把操作转换一下：

- 每次在一个位置后添加一个回文串。添加部分长度之和不超过 $4n^2$。

设一个子串为 $s_1s_2...s_t$，在其后添加一个 $s_1s_2...s_{t-1}s_ts_ts_{t-1}...s_2s_1$ 等同于将这个子串翻转并在其前面添加一个 `tandem repeats`。如果这个子串是原串的前缀，则添加的 `tandem repeats` 对后续翻转操作无影响，可以记录位置偏移量后直接删去。

考虑将 $a$ 重组得到任意一个 `tandem repeats`（记为 $b$），之后对 $a$ 进行类似排序的过程。具体而言：

- 从后往前枚举位置 $i$；
- 如果 $a_i=b_i$，跳过；
- 否则设 $j$ 为最大的满足 $a_j=b_i \land j<i$ 的位置。翻转 $a_{1..j}$ 后翻转 $a_{1..i}$。不难发现翻转后 $a_i=b_i$；
- 翻转至多 $2n$ 次，每次翻转所添加的回文串长度不超过 $2n$，长度之和不超过 $4n^2$ 次。

Code:

```cpp
ll T,n,a[505],b[505],cnt[505],tmp[505],tot,dt;vector<pr>ans;vector<ll>res;
il bool build()
{
	ll cur=0;clr(cnt,n+1);for(int i=1;i<=n;++i)++cnt[a[i]];
	for(int i=1;i<=n;++i)for(int j=2;j<=cnt[i];j+=2)b[++cur]=i;
	for(int i=1;i<=n;++i)for(int j=2;j<=cnt[i];j+=2)b[++cur]=i;
	for(int i=1;i<=n;++i)if(cnt[i]&1)ret 0;
	ret 1;
}
il void rev(ll x)
{
	if(x<=1)ret;
	for(int i=1;i<=x;++i)ans.pb(prpr(i+x-1+dt,a[i]));
	res.pb(x<<1);dt+=x<<1;
	for(int i=1,j=x;i<=j;++i,--j)swap(a[i],a[j]);
}
int main()
{
	T=rd();
	while(T --> 0)
	{
		n=rd();dt=0;ans.clear();res.clear();for(int i=1;i<=n;++i)tmp[i]=a[i]=rd();
		sort(tmp+1,tmp+1+n);tot=unique(tmp+1,tmp+1+n)-tmp-1;
		for(int i=1;i<=n;++i)a[i]=lower_bound(tmp+1,tmp+1+tot,a[i])-tmp;
		if(!build()){prt(-1);continue;}
		for(int i=n;i>=1;--i)
		{
			if(a[i]^b[i])
			{
				ll pos=i-1;
				while(pos&&(a[pos]^b[i]))--pos;
				assert(pos);
				rev(pos);rev(i);
			}
		}
		prt(ans.size());for(auto x:ans)prt(x.fir,' '),prt(tmp[x.sec]);
		prt(res.size());for(auto x:res)prt(x,' ');
		prt(n);
	}
	ret 0;
}
```

---

## 作者：_Tooler_Fu_ (赞：1)

模拟题。

很显然，若这 $n$ 个数中有出现奇数个数字的数，因为每次只会添加 $2$ 个相同的数，所以总会有一个剩余，无法配对，因而输出 $-1$ 。

对于成立的情况，考虑最容易模拟的暴力。

假设数组为 $a$ 。

在 $a$ 中找到第一个与 $a_1$ 相同的数，设下标为 $r$ 。

则于 $a_r$ 后插入 $a_2$ 至 $a_{r-1}$ 的所有数。

消除这些 “串联重复” 后将剩余的数存入一个中间数组，再返回给 $a$ 。

如此反复，若 $a_1$ 与 $a_2$ 相等，则跳出。

由于每次消掉一对数，故一次得出答案复杂度为 $O(n^2)$ 。

故总复杂度为 $O(Tn^2)$ 。

代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long T;
long long n;
long long a[5005];
long long b[5005];
long long len=0;
long long tp=0;
long long l,r;
bool flag=false;
vector<pair<long long,long long> > v;
vector<long long> ans;
int main() {
	scanf("%lld",&T);
	while(T--){
		tp=0;
		flag=false;
		v.clear();
		ans.clear();
		map<long long,long long> mp;
		scanf("%lld",&n);
		len=n;
		for(long long i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			mp[a[i]]++;
		}
		for(auto i:mp){
			long long y=i.second;
			if(y&1){
				flag=true;
				printf("-1\n");
				break;
			}
		}
		if(flag){
			continue;
		}
		while(1){
			l=1,r=2;
			while(a[l]!=a[r]){
				r++;
			}
			//printf("%d %d %d\n",l,r,n);
			long long xxx=0;
			for(long long i=l+1;i<r;i++){
				v.push_back(make_pair(r+xxx+tp,a[i]));
				xxx++;
			}
			xxx=0;
			for(long long i=r-1;i>=l+1;i--){
				b[++xxx]=a[i];
			}
			for(long long i=r+1;i<=n;i++){
				b[++xxx]=a[i];
			}
			ans.push_back((r-l)*2);
			tp+=(r-l)*2;
			if(r==n&&r-l==1){
				break;
			}
			for(long long i=1;i<=xxx;i++){
				a[i]=b[i];
			}
			n=xxx;
		}
		printf("%d\n",v.size());
		for(long long i=0;i<v.size();i++){
			printf("%lld %lld\n",v[i].first,v[i].second);
		}
		printf("%d\n",ans.size());
		for(long long i=0;i<ans.size();i++){
			printf("%lld ",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
```

~~其实赛时只过了 A B ，C 都 FST 了 /kk ~~

---

## 作者：DaiRuiChen007 (赞：0)

# CF1641B 题解



## 思路分析

显然，如果有元素出现次数为奇数，则必定无解。

考虑如何用题目中的操作复制一个序列 `1 2 3 4`，显然每次在序列中间插入下一个数可以得到序列 `1 2 3 4 4 3 2 1`。

考虑 $a_1$ 和谁匹配，显然我们应该找到第一个和 $a_1$ 值相等的数 $a_i$，然后在 $a_i$ 的后面复制 $a_{2}\sim a_{i-1}$，此时我们可以消掉 $a_1\sim a_i$，并且留下序列 $a_{i-1}\sim a_2$，注意到每次这样的操作会让原序列未匹配数减少 $2$，而每次这样的操作需要至多 $n$ 轮复制，那么这样的复制总次数大概在 $\dfrac {n^2}2$ 左右，因此可以通过本题。

代码实现用 `vector` 每次调用 `reverse` 函数和 `erase` 函数即可。

时间复杂度 $\Theta(n^2)$。

## 代码呈现

```cpp
#include<bits/stdc++.h> 
#define pii pair <int,int>
using namespace std;
inline void solve() {
	int n;
	scanf("%d",&n);
	map <int,int> cnt;
	vector <int> a(n),ans;
	vector <pii> op;
	for(int i=0;i<n;++i) scanf("%d",&a[i]),++cnt[a[i]];
	for(auto p:cnt) {
		if(p.second%2==1) {
			puts("-1");
			return ;
		}
	}
	int tot=0;
	while(!a.empty()) {
		for(int i=1;i<(int)a.size();++i) {
			if(a[i]==a[0]) {
				for(int j=1;j<i;++j) op.push_back(make_pair(tot+i+j,a[j]));
				tot+=i*2,ans.push_back(i*2);
				reverse(a.begin(),a.begin()+i+1);
				a.erase(a.begin()+i),a.erase(a.begin());
				break;
			}
		}
	}
	printf("%d\n",(int)op.size());
	for(auto p:op) printf("%d %d\n",p.first,p.second);
	printf("%d\n",(int)ans.size());
	for(auto u:ans) printf("%d ",u);
	puts("");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：I_am_Accepted (赞：0)

### Preface

骄傲地使用多年没写的链表过了此题。

### Analysis

首先，如果原序列中某一种值出现了奇数次肯定不行。我们下面构造偶数必然可行。

我们先观察一个样例：

```
look :1 2 3 1 3 4 2 4
step1:1 2 3 1(2 2)3 4 2 4
step2:1 2 3 1 2(3 3)2 3 4 2 4
look :1 2 3 1 2 3|3 2 3 4 2 4
step3:1 2 3 1 2 3|3 2 3(2 2)4 2 4
end  :1 2 3 1 2 3|3 2 3 2|2 4 2 4
```

也就是说，我们找到 $a_1$ 之后第一个 $a_i=a_1$，然后在 $a_i$ 位置后操作使得 $a[i,2i-1]=a[1,i-1]$，接下来从 $a_{2i}$ 开始（每次操作后重新标号）重复此操作即可。

由于每种值均出现偶数次，此方法必然可行。并且设 $f_i$ 表示原长度为 $i$ 的操作总次数：

$$\begin{cases}
f_0=0
\\
f_n\le n-2+f(n-2)
\end{cases}$$

易知 $f_n\le\dfrac{n(n-2)}{4}$，满足题意。

我们用链表也能够轻松让时间复杂度同阶于操作数。

### Code

[Link](https://codeforces.com/contest/1641/submission/147749471)

---

## 作者：清烛 (赞：0)

其实这题出的很不错来着，但是毒瘤是真的毒瘤。

给定长度为 $n$（$1\le n\le 500$）的正整数序列 $a$，可以进行形如 $(x, c)$ 的操作：在 $a_x$ 后面插入**两个连续的**正整数 $c$（$x\in[0, \text{the length of }a]$）。构造操作方案使得 $a$ 最后可以拆分为若干个连续的子段，这些子段满足：长度为 $2k$，$k$ 为任意正整数，且 $\forall i\in [1, k]$ 有 $a_i = a_{i + k}$。

保证 $\sum n^2\le 2.5\times 10^5$，操作次数需 $\le 2n^2$，若无解则报告之。

首先，注意到每种数字的出现次数必须为偶数次，因为添加数字一定是给某种数字添加两个，若存在出现了奇数次的数字则无论如何都没办法找到与之配对的数，所以无解。

然后可以注意到，我们可以对一个前缀做翻转操作，具体地，看下面的例子：

```plain
1 2 3 1 3 2
1 2 3 - 1 2 3 3 2 1 - 1 3 2 // 这一步可以通过 3 次操作实现
(1 2 3 | 1 2 3) - 3 2 1 1 3 2 // 即我们构造一个回文串，然后将前面的合并到一段，前缀就成功被翻转了。
```

而通过这样，我们就可以将两个 $1$ 放在一起，再反转一下：

```plain
(1 2 3 | 1 2 3) - (3 2 1 1 | 3 2 1 1) - 1 1 2 3 - 3 2
```

然后两个 $1$ 就顺理成章的在一起了，可以放在一段消掉了。

 ```plain
(1 2 3 | 1 2 3) - (3 2 1 1 | 3 2 1 1) - (1 | 1) 2 3 3 2
 ```

接下来就解决 `2 3 3 2` 就行了，思路是一样的。

通过这样的操作，我们就能在 $O(n^2)$ 的操作次数下，将两个数“两两合并”，解决这道题目。

输出方案比较毒瘤，大家写的时候需要注意细节。

```cpp
using pii = pair<int, int>;
const int maxn = 505;
int n, a[maxn], alreadyLen, now;
vector<pii> op;
vector<int> ans;
map<int, int> vis;

void rev(int pos) {
    FOR(i, now + 1, pos - 1) op.push_back({i - now + alreadyLen + pos - 2, a[i]});
    ans.push_back(2 * (pos - now - 1));
    alreadyLen += 2 * (pos - now - 1);
    reverse(a + now + 1, a + pos);
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        decltype(vis)().swap(vis);
        FOR(i, 1, n) read(a[i]), ++vis[a[i]];
        bool flg = 1;
        for (auto &p : vis) if (p.second & 1) flg = 0;
        if (!flg) {
            print(-1);
            continue;
        }
        decltype(op)().swap(op);
        decltype(ans)().swap(ans);
        alreadyLen = 0, now = 0;

        while (now < n) {
            if (now == n - 2) {
                ans.push_back(2);
                break;
            }
            int pos = 0;
            FOR(i, now + 2, n) if (a[i] == a[now + 1]) {
                pos = i;
                break;
            }
            rev(pos), rev(pos + 1);
            ans.push_back(2);
            now += 2;
        }

        print(op.size());
        for (auto &p : op) print(p.first, p.second);
        print(ans.size());
        for (auto x : ans) print(x, ' ');
        putchar('\n');
    }
    return output(), 0;
}
```


---

## 作者：Suzt_ilymtics (赞：0)

我们先来看一下 qyc 对此题的评价：

![](https://cdn.luogu.com.cn/upload/image_hosting/9o7qq18i.png)

### Description

> $T$ 组数据，每组数据给你 $n$ 个数，满足 $n \le 500$ 且 $n^2 \le 250000$。
> 
> 你要完成一个任务：就是把整个序列分成几段。每一段都必须是偶数段并且前半段和后半段要完全相同。
>
> 为了让你完成这个任务，你可以执行这样一个操作：在**当前的**第 $p$ 个数后面加 **两个** $c$。位置和数值任意。
> 
> 操作次数不能超过 $2 \times n^2$ 次。
>
> 你需要判断有无解。如果有解，你需要输出操作了几次，以及每次操作时的 $p,c$。你还需要输出划分了几段和每段的大小。

### Solution

观察第一组样例+手模可以发现，如果存在一个数出现了奇数次那么无解。

接下来考虑如何构造答案。

我们采用这样一种构造方式：

每次从未划分的序列找到第一个数，然后找到这个数第二次出现的地方。

设两个位置分别为 $l,r$，接下来我们要做的是通过在 $r$ 后面加数使得它能和 $[l,r-1]$ 这一段完全相同。

我们从 $l,r$ 同时向后扫，如果当前位置可以和前面的序列匹配就匹配，否则就加一次数使其匹配，直到其和 $[l,r-1]$ 这一段全部匹配。

设这段长度为 $len$，这时我们就可以将 $[l,l+2len-1]$ 这一段划分出来。

不断重复上述操作直到划分完毕。

正确性：

每次我们都至少将原序列中的一对进行匹配。最坏会进行 $\frac{n}{2}$ 次，每次插入 $n$ 次数。此时总操作数为 $\frac{n^2}{2}$，合法。

最坏情况的序列应该是这样的形式：

`abcdef...fedcba`

### Code

模拟即可。~~注意选择合适的实现方式~~。

```cpp
struct node { int p, c; }d[MAXN];
int m = 0;

int n;
int a[MAXN], date[MAXN];
int cnt[MAXN];
int b[MAXN], sc = 0;
int t[MAXN], top = 0;
deque<int> q; 

void Main() {
    sc = 0, top = 0, m = 0;
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = date[i] = read();
    sort(date + 1, date + n + 1);
    int Cnt = unique(date + 1, date + n + 1) - date - 1;
    for(int i = 1; i <= Cnt; ++i) cnt[i] = 0;
    for(int i = 1; i <= n; ++i) a[i] = lower_bound(date + 1, date + Cnt + 1, a[i]) - date, cnt[a[i]] ++;
    bool Flag = false;
    for(int i = 1; i <= Cnt; ++i) if(cnt[i] & 1) Flag = true;
    if(Flag) return puts("-1"), void();
    
    for(int i = 1; i <= n; ++i) q.push_back(a[i]);
    int now_ = 0, tmp;
    while(!q.empty()) {
        int u = q.front(); q.pop_front();
        b[++sc] = u;
        if(sc != 1 && u == b[1]) {
            sc --, q.push_front(u);
            now_ += sc;
            t[++top] = sc * 2;
            for(int i = 1; i <= sc; ++i) {
                if(!q.empty() && q.front() == b[i]) {
                    q.pop_front(), now_ ++;
                } else if(i < sc && b[i] == b[i + 1]) {
                    d[++m].p = now_, d[m].c = date[b[i]]; now_ += 2, ++i;
                } else {
                    d[++m].p = now_, d[m].c = date[b[i]], now_ ++, q.push_front(b[i]);
                }
            }
            sc = 0;
        }
    }
    printf("%d\n", m);
    for(int i = 1; i <= m; ++i) printf("%d %d\n", d[i].p, d[i].c);
    printf("%d\n", top);
    for(int i = 1; i <= top; ++i) printf("%d ", t[i]);
    puts("");
}

int main()
{
    int T = read();
    while(T--) Main();
    return 0;
}
```

---

