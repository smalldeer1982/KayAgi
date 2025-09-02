# Array Destruction

## 题目描述

### 题意简述

你有一个长度为 $2n$ 的无用数组 $a$ ，现在要进行一些操作将数组的所有元素清除：

- 选择一个正整数 $x$。

- 选择 $a$ 数组的任意两个数使得它们的和等于 $x$，并将这两个数从 $a$ 数组中删除。

- 将 $x$ 更改为选择的两个数的最大值。

- 重复第二步直到 $a$ 数组清空。

**注意：$x$ 不能在运算过程中随意更改。**

现在请你输出通过怎样的过程使 $a$ 数组清空。

## 样例 #1

### 输入

```
4
2
3 5 1 2
3
1 1 8 8 64 64
2
1 1 2 4
5
1 2 3 4 5 6 7 14 3 11```

### 输出

```
YES
6
1 5
2 3
NO
NO
YES
21
14 7
3 11
5 6
2 4
3 1```

# 题解

## 作者：Blunt_Feeling (赞：8)

## CF1474C Array Destruction 题解

首先可以明确一点，题目中要我们构造的 $x$，一定是最大的那个数和数列中另一个数的和。因为如果不用最大的那个数，而采用第二大、第三大的数的和作为最初的 $x$，就不可能找到一个数与第一大的数加起来，刚好等于第二大的数，也就无法把第一大的数消掉。

于是就可以把数列从大到小排序，枚举 $2\sim 2n$，选出一个数，把它与 $a_1$ 加起来作为最初的 $x$，检验是否可行，并且记录消除的过程。

为了模拟删除、查找的过程且保持数列单调不上升，这里使用了 C++ `STL` 库中的 `multiset`（有序多重集）。`st.find(num)`返回`num`在`st`中的迭代器，`st.erase(it)`删除迭代器`it`指向的元素。如果每个元素都能被删除，就说明方案可行，直接输出。

### Code

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=1024;
int T,n,a[maxn<<1],ans[maxn<<1][2],cnt;
multiset<int> st;
bool cmp(int x,int y) {
	return x>y;
}
bool judge(int i) //检验最初的x=a[i]+a[1]是否可行 
{
	st.clear();
	For(j,2,n<<1)
		if(j!=i) //i被删除了
			st.insert(a[j]); //初始化原数列
	int x=a[1];
	memset(ans,0,sizeof(ans));
	ans[1][0]=x,ans[1][1]=a[i]; //第一个操作把x和a[i]删除
	cnt=1; //操作次数
	For(j,2,n<<1)
	{
		if(st.find(a[j])==st.end()) continue; //a[j]已经被删除了
		st.erase(st.find(a[j])); //删除a[j]
		if(st.find(x-a[j])==st.end())
			return false;
		else
		{
			ans[++cnt][0]=x-a[j],ans[cnt][1]=a[j]; //ans记录操作
			st.erase(st.find(x-a[j]));
			x=a[j]; //更新x
		}
	}
	return true;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		For(i,1,n<<1) cin>>a[i];
		sort(a+1,a+(n<<1)+1,cmp); //降序排序
		bool flag=false;
		For(i,2,n<<1)
			if(judge(i))
			{
				puts("YES");
				cout<<ans[1][0]+ans[1][1]<<endl;
				For(i,1,n) cout<<ans[i][0]<<' '<<ans[i][1]<<endl;
				flag=true; //表示有可行方案
				break;
			}
		if(!flag) puts("NO");
	}
	return 0;
}
```


---

## 作者：__zhuruirong__ (赞：2)

## 解法分析

很显然，这题中的 $x$ 必然是 $a$ 中最大的数字和 $a$ 中另外一个数字的和，因为如果你开始时选择了一个很小的数字，大的数字显然就没办法删除了。而无解的情况就是 $a$ 中最大的的数字无论和 $a$ 中哪个数字配对都无解，则无解，而判断一种方案是否无解则需看现在的 $x$ 减去 $a$ 中没有选择的最大的数字在 $a$ 中是否存在。

这样，我们总结出一个策略：优先选择较大的数字 $a_i$，如果 $x - a_i$ 在 $a$ 中未出现则此方案无解，否则将 $x$ 设为 $a_i$ 继续此过程直到无法继续为止。

## AC代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2010, M = 1e6 + 10;
int T, n, cnt, a[N], l[N], r[N];

bool check(int j, unordered_map<int, int> sum) {
	l[1] = a[n];
	r[1] = a[j];
	cnt = 1;
	int now = a[n], num = n - 2;
	bool flag = true;
	sum[a[n]]--;
	sum[a[j]]--;
	for(int i = n - 1; num; i--)
		if(sum[a[i]]) {
			if(!sum[now - a[i]] or a[i] * 2 == now and sum[a[i]] <= 1) 
				return false;
			cnt++;
			l[cnt] = a[i];
			r[cnt] = now - a[i];
			sum[a[i]]--;
			sum[now - a[i]]--;
			now = a[i];
			num -= 2;
		}
	return (num == 0 and cnt * 2 == n);
}

signed main() {
	
	cin >> T;
	while(T--) {
		unordered_map<int, int> sum;
		cin >> n;
		n *= 2;
		for(int i = 1; i <= n; i++) {
			cin >> a[i];
			sum[a[i]]++;
		}
		sort(a + 1, a + n + 1);
		bool flag = false;
		int j;
		for(int i = 1; i < n; i++) 
			if(check(i, sum) and cnt <= n) {
				j = i;
				flag = true;
				break;
			}
		if(flag) {
			puts("Yes");
			cout << a[n] + a[j] << endl;
			for(int i = 1; i <= cnt; i++)
				cout << l[i] << " " << r[i] << endl;
		}
		else
			puts("No");
	}

	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/144414442)

1.14KB耶

---

## 作者：appear_hope (赞：1)

假设你当前的 $x$，你选的两个数并不是当前剩余的最大值，由于题目数据保证了 $a_i$ 为正整数所以你后面就不能选择最大值了。

所以根据这个假设，可以想到我们的思路是：每次凑数是一定选最大值。而第一个 $x$ 一定有 $a_i$ 的最大值构成，所以我们可以枚举第一次除 $a_i$ 外选择的数，然后计算第一次 $x$，在模拟贪心思路模拟一遍。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;

multiset<int> s;
int T, n, a[2 * N]; //注意题目的数据范围
pair<int, int> v[N];

bool Solve(){
  cin >> n;
  for(int i = 1; i <= 2 * n; i++){
    cin >> a[i];
  }
  sort(a + 1, a + 2 * n + 1);
  for(int i = 1; i < 2 * n; i++){
    s.clear(); //记得清空
    for(int j = 1; j <= 2 * n; j++){
      s.insert(a[j]);
    }
    int x = *prev(s.end()) + a[i], k = 0, temp = x;
    for(; k < n && *prev(s.end()) <= x && s.find(x - *prev(s.end())) != s.end(); x = max(v[k].first, v[k].second)){ 
      v[++k] = {*prev(s.end()), x - *prev(s.end())};
      s.erase(s.find(v[k].first)); //只能删除一个数
      if(s.find(v[k].second) == s.end()){ //由于选择的两个数可能相同，但判断的时候只判断了其中的一个数的出现情况未考虑完全
        k = 0;
        break;
      }
      s.erase(s.find(v[k].second));
    }
    if(k == n){
      cout << "YES\n" << temp << '\n';
      for(int i = 1; i <= k; i++){
        cout << v[i].first << ' ' << v[i].second << '\n';
      }
      return true;
    }
  }
  return false;
}

int main(){
  iosync_with_stdio(0), cin.tie(0), cout.tie(0);
  for(cin >> T; T--; T++){
    if(!Solve()){
      cout << "NO\n";
    }
  }
  return 0;
}
//请勿抄袭
```

---

## 作者：UperFicial (赞：1)

# 模拟

### 前言

有一定思维的模拟，外加一些剪枝就能过。

但总体还是挺水的，考验码力（

题目链接：[$\text{Link}$](https://www.luogu.com.cn/problem/CF1474C)

### 题意简述

提交了一篇翻译但还没审（？）

给定长度为 $2n$ 的数组 $a$，要求在一开始选定一个正整数 $x$，之后通过一系列运算将 $a$ 数组清空：

1. 选择 $a$ 数组中的两个数 $m,n$，并保证 $m+n=x$。

2. 从 $a$ 数组删去 $m,n$，并将 $x$ 更改为 $\max(m,n)$。

3. 重复第一个步骤直到删去 $a$ 数组中所有的元素。


请你求出一开始选择的 $x$ 与每次删去的两个数。


### 题目分析

先有一个想法：每次肯定要删去 $a$ 数组中最大的数 $b$，因为如果删小的数，$x$ 永远不会比 $b$ 要大，那么 $b$ 也就删不掉了。


有了这个想法，再看数据范围：$1\le n\le 1000$，提示我们暴力就能直接艹过去。

$x$ 的取值便可以暴力枚举了，前提 $x>b$，$b$ 为 $a$ 数组中最大的数。

每当确定一个 $x$ 后就是模拟了，只要一旦找不到合法的数 $a_i$ 使 $a_i+b=x$，那么 $x$ 的取值也就吧不合法，换一个 $x$ 重试。

但 $x$ 的枚举也是有技巧，既然 $x=b+a_i$，那么我们可以直接枚举一个 $a_i$，从而来确定一开始的 $x$，复杂度大大下降。

要注意删数不需要真正地将元素从数组中删除，可以再开一个数组 $mp$ 来维护一个数出现了几次，一旦遇到不合法的 $x$，就可以还原回去了。方法有很多，我是记录删去了那些位置，将 $mp$ 还原即可。

别忘数组开两倍空间。

[$code$](https://paste.ubuntu.com/p/rrgyrdZsBg/)


[$AC$ 记录](https://www.luogu.com.cn/record/45680818)

$$\texttt{The End.by UF}$$



---

## 作者：INT_MAX66zz (赞：0)

******题目大意******

有一个长度为 $2n$ 的数组，你要遵循某种规则将这些数组删除：

选择一个基准 $x$ ；

选择 $a$ 数组的任意两个数使得它们的和等于 $x$，并将这两个数从 $a$ 数组中删除。

将 $x$ 更改为选择的两个数的最大值。

对于每个测试用例，如果可以将数组中的所有元素移除，则在第一行打印 YES ，否则打印 NO 。

如果可以将数组中的所有元素移除，则打印你选择的 $x$ 的初始值。接下来打印 $n$ 次操作的描述。对于每次操作，打印你移除的两个整数。

---

********思路详述：********

其实思路并不难，由于数组里的数都是正数，所以当一个数被当作基准时，比它大的数就不会再选中。换言之，每次选择基准都要从剩余数组中最大的数作为基准。

我们注意到，如果无法完成当前操作，那么后续操作会终止，这是一个典型的贪心。所以大体思路就可以想出来了。

先令最大的数为最先选中的其中一个数，然后遍历剩余数组里的数，令当前选中的数作为第二个数，并将基准改为第一个数。然后选择剩余数组中选择第二大个数，判断是否有符合条件的数，有即选择其为第二个数，然后重复循环。

对于如何找出符合条件的数，可以用 map 维护

---

********代码呈现********

```
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define ll long long
#define u unsigned
using namespace std;
int t;
int n;
int a[2001];
int ji,d;
vector<pair<int,int>>x;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--){
		x.clear();
		map<int,int>c;
		cin >> n;
		n += n;
		memset(a,0,sizeof(a));
		for(int i = 1;i<=n;i++)
			cin >> a[i],c[a[i]]++;
		sort(a + 1,a + n + 1);
		d = 0;
		ji = a[n];
		c[a[n]]--;
		bool ok = true;
	for(int i = 1;i<n;i++){
		ji = a[n];
		ok = true;
		x.clear();
		map<int,int>c_(c);
		d = a[i];
		c_[a[i]]--;
		int G = d + ji;
		x.push_back(make_pair(d,ji));
		for(int ii = n - 1;x.size() != n / 2;ii--){
			if(!c_[a[ii]])
				continue;
			c_[a[ii]]--;	
			if(c_.find(ji - a[ii]) != c_.end() && c_[ji - a[ii]] && ji - a[ii] != 0){
				x.push_back(make_pair(ji - a[ii],a[ii]));
				c_[ji - a[ii]]--;
				ji = a[ii];
			}
			else{
				ok = false;
				break;	
			}	
		}
		if(ok){
				cout << "YES\n" << G << "\n";
			for(auto y : x)
					cout << y.first << " " << y.second << "\n";
			break;
		}	
		c_[a[i]]++;
	}
	if(!ok)
		cout << "NO\n";
	}
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF1474C Array Destruction
## 题意
给定一个长度为 $2n$ 的数组 $a$，下面要执行如下操作使数组清空。\
第一步任选一个数字 $x$，从数组中任意删除两个元素 $a_i,a_j$ 满足 $a_i+a_j=x$。并令 $x=\max(a_i,a_j)$，继续重复操作，问能否有一种方案使数组清空，如果有则输出方案。
## 从简单性质入手
首先我们可以观察到一个比较简单的性质：每次我们都必须把数组中最大的元素删除。\
这个证明也比较容易：假设我们不把数组中最大的元素删除，那么 $x$ 在操作后一定小于数组中最大的元素，因为 $a$ 是个正整数序列，所以数组中最大的元素一定不能被删除。\
知道这个性质以后，我们考虑假设 $x$ 已经确定了，那么我们既然要选择数组最大的元素，那么另一个元素也就确定等于 $x-\max\{a_i\}$。\
那由于我们从第二次开始的 $x$ 都是由上一次的结果而决定，而上一次的结果是由上上次的结果而决定，于是只要我们确定了第一次的 $x$，整个删除过程也就确定了。\
那么我们就考虑第一次的 $x$ 如何确定。\
因为每次我们肯定第一次要删除 $a_n$，于是我们只需要枚举另一个数即可。\
具体代码实现方面，我们要维护一个支持删除，查找某一元素的数据结构，这当然可以用平衡树，但是 `STL` 库里给我们提供了更好用的 `set`。唯一的问题是 set 会自动去重，这时候我们可以利用 `multiset`，也可以利用 `map+set` 的经典组合解决。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2222;
int a[N];
int n;
bool flag;
void solve(){
    unordered_map<int,int>mp;
    set<int>s;
    cin>>n;
    flag=0;
    for(int i=1;i<=n*2;++i){
        cin>>a[i];
        mp[a[i]]++;
        s.insert(a[i]);
    }
    sort(a+1,a+1+2*n);
    for(int t=1;t<2*n;++t){
        set<int>st=s;
        unordered_map<int,int>mpp=mp;
        flag=1;
        int x=a[n*2];
        vector<pair<int,int> >ans;
        if(--mpp[a[t]]==0)st.erase(a[t]);
        if(--mpp[a[2*n]]==0)st.erase(a[2*n]);
        for(int i=2*n-1;i>=1;--i){
            if(st.find(a[i])==st.end())continue;
            if(--mpp[a[i]]==0){
                st.erase(a[i]);
            }
            if(st.find(x-a[i])==st.end()){
                flag=0;
                break;
            }
            ans.push_back({a[i],x-a[i]});
            if(--mpp[x-a[i]]==0){
                st.erase(x-a[i]);
            }
            x=a[i];
        }
        if(flag){
            cout<<"YES\n";
            cout<<a[t]+a[2*n]<<'\n';
            cout<<a[t]<<' '<<a[2*n]<<'\n';
            for(auto p:ans){
                cout<<p.first<<' '<<p.second<<'\n';
            }
            return;
        }
    }
    cout<<"NO\n";
    return;
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：白鲟 (赞：0)

## 前言
好久没写题解了……

## 题意简述
题面很简略了。

## 题目分析
明确事实：由于数组非负，每次作为基准值的 $x$ 单调递减。

推出结论：每次取出的两个数中，必有一个是当前数组最大值（若不是，则当前数组最大值无法被消去）。

得到做法：枚举与最初的最大值一同消去的数，用数据结构模拟剩余过程并判断是否满足题意。

## 代码
使用 `multiset` 减少代码量。

```cpp
#include<algorithm>
#include<cstdio> 
#include<functional>
#include<set>
using namespace std;
const int maxn=1e3;
int T,n,ans,x,a[maxn<<1|1],l[maxn<<1|1],r[maxn<<1|1];
bool failed;
multiset<int,greater<int> > s;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=(n<<1);++i)
			scanf("%d",&a[i]);
		sort(a+1,a+(n<<1)+1,greater<int>());
		for(int opt=2;opt<=(n<<1);++opt)
		{
			s.clear();
			for(int i=2;i<=(n<<1);++i)
				if(i!=opt)
					s.insert(a[i]);	
			failed=false;
			ans=0;
			l[++ans]=a[1];
			r[ans]=a[opt];
			for(int i=1;i<n;++i)
			{
				l[++ans]=*s.begin();
				s.erase(s.begin());
				multiset<int,greater<int> >::iterator iter=s.find(l[ans-1]-l[ans]);
				if(iter!=s.end())
				{
					r[ans]=*iter;
					s.erase(iter);
				}
				else
				{
					failed=true;
					break;
				}
			}
			if(!failed)
			{
				printf("YES\n%d\n",l[1]+r[1]);
				for(int i=1;i<=ans;++i)
					printf("%d %d\n",l[i],r[i]);
				break;
			}
			else if(opt==(n<<1))
				puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：45dino (赞：0)

显然的一点，由于上一次删除的最大值是下一次删去两个数的和，所以有如下结论。
- 第一次会删去最大值。
- 由于没有0，每一次删去的最大值是单调递减的。

综上，如果确定第一次删去的两个数，就可以确定全过程。

枚举第一次删去的另一个数，用 $\Theta(n)$ 的复杂度判断是否可行，因此总复杂度为 $\Theta(n^2)$

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[100011],buc[1000011],q[100011][2],qn;
inline int read()
{
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=0;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
    return (flag?x:~(x-1));
}
signed main()
{
	t=read();
	while(t--)
	{
		n=read();
		n<<=1;
		for(int i=1;i<=n;i++)
			a[i]=read();
		sort(a+1,a+1+n);
		bool ok=0;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<=n;j++)
				buc[a[j]]=0;
			for(int j=1;j<=n;j++)
				buc[a[j]]++;
			qn=0;
			int x=a[i]+a[n];
			bool flg=1;
			for(int j=n;j;j--)
			{
				if(!buc[a[j]])
					continue;
				buc[a[j]]--;
				if(!buc[x-a[j]])
				{
					flg=0;
					break;
				}
				qn++;
				q[qn][0]=a[j];
				q[qn][1]=x-a[j];
				buc[x-a[j]]--;
				x=a[j];
			}
			if(flg&&qn==n/2)
			{
				printf("YES\n%lld\n",a[i]+a[n]);
				for(int i=1;i<=qn;i++)
					printf("%lld %lld\n",q[i][0],q[i][1]);
				ok=1;
				break;
			}
		}
		if(!ok)
			printf("NO\n");
	}
	return 0;
}
```


---

