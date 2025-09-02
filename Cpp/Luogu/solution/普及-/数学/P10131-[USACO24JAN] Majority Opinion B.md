# [USACO24JAN] Majority Opinion B

## 题目描述

Farmer John 有一项重要的任务——弄清楚要为他的奶牛们购买什么类型的干草。

Farmer John 的 $N$ 头奶牛（$2\le N\le 10^5$）编号为 $1$ 到 $N$，每头奶牛喜欢恰好一种类型的干草 $h_i$（$1\le h_i\le N$）。他希望他的所有奶牛都喜欢同一种干草。

为了实现这一目标，Farmer John 可以主持焦点小组访谈。一次焦点小组访谈为让编号从 $i$ 到 $j$ 的连续范围内的所有奶牛聚集在一起参加一次访谈。如果有一种干草是小组中超过一半的奶牛喜欢的，则此次焦点小组访谈结束后，所有奶牛最终都会喜欢这种干草。如果不存在这种类型的干草，那么奶牛们不会改变她们喜欢的干草类型。例如，在由 $16$ 头奶牛组成的焦点小组访谈中，需要有其中 $9$ 头或更多的奶牛具有相同的干草喜好，才能使其余奶牛改变其喜好以与之一致。

Farmer John 想知道哪些类型的干草有可能变为同时受到所有奶牛的喜爱。他一次只能主持一个焦点小组访谈，但为了使所有奶牛都喜欢同一类型的干草，他可以根据需要任意多次地主持焦点小组访谈。 

## 说明/提示

### 样例解释

在输入样例中，有 5 个测试用例。

在第一个测试用例中，仅可能使所有奶牛喜欢种类 $2$。FJ 可以通过主持一次所有奶牛的焦点小组访谈达到这一目的。

在第二个测试用例中，可以证明没有奶牛会改变她们喜爱的干草种类。

在第三个测试用例中，有可能使所有奶牛喜欢种类 $1$，可以通过主持三次焦点小组访谈达到这一目的——首先使奶牛 $1$ 到 $4$ 进行一次焦点小组访谈，随后使奶牛 $1$ 到 $5$ 进行一次焦点小组访谈，随后使奶牛 $1$ 到 $6$ 进行一次焦点小组访谈。以类似的逻辑，依次操作奶牛 $3$ 到 $6$，随后是奶牛 $2$ 到 $6$，随后是奶牛 $1$ 到 $6$，我们可以使所有奶牛喜欢种类 $2$。

在第四个测试用例中，有可能使所有奶牛喜欢种类 $3$，可以通过主持一次所有奶牛的焦点小组访谈达到这一目的。

在第五个测试用例中，可以证明没有奶牛会改变她们喜爱的干草种类。

### 测试点性质

- 测试点 $2$：$N=2$。
- 测试点 $3-4$：$N\le 50$。
- 测试点 $5-6$：对于所有的 $1\le i\le N−1$，有 $h_i\le h_{i+1}$。
- 测试点 $7-15$：没有额外限制。

## 样例 #1

### 输入

```
5
5
1 2 2 2 3
6
1 2 3 1 2 3
6
1 1 1 2 2 2
3
3 2 3
2
2 1```

### 输出

```
2
-1
1 2
3
-1```

# 题解

## 作者：GONGX (赞：11)

# 题意简述
Farmer John 要弄清楚要为他的奶牛们购买什么类型的干草。

Farmer John 的 $N$ 头奶牛编号为 $1$ 到 $N$，每头奶牛都喜欢一种干草 $h_i$。他希望他的所有奶牛都喜欢同一种干草。

为实现这一目标，Farmer John 可以主持焦点小组访谈。每次焦点小组访谈让从 $i$ 到 $j$ 的连续范围内的所有奶牛聚在一起参加。如果有一种干草是小组中超过一半的奶牛喜欢的，则此次焦点小组访谈结束后，所有奶牛最终都会喜欢这种干草。

Farmer John 想知道哪些类型的干草有可能变得同时受到所有奶牛的喜爱。他一次只能主持一个焦点小组访谈，但为了使所有奶牛都喜欢同一类型的干草，他可以根据需要任意多次地主持焦点小组访谈。
# 解题思路
首先，我们可以先想一想当 $n=2$ 时，若小组内两头奶牛都喜欢同种类型的干草则有解；当 $n=3$ 时，则当组内有任意两头奶牛喜欢同种类型的干草时有解。

然后很容易即可推出，若奶牛 $i-1$ 和奶牛 $i$ 或 奶牛 $i$ 和奶牛 $i-2$ 喜欢同类型的干草，那么奶牛 $i-2$，奶牛 $i-1$ 和奶牛 $i$ 将可以同时喜欢奶牛 $i$ 所喜欢的干草类型。

而对于任何奶牛数大于 $3$ 的焦点访谈小组，我们一定能从中找到一个有 $3$ 头奶牛的焦点访谈小组。若有干草类型满足上面推导的关系，则这种类型的干草将可以受到所有奶牛的喜爱。
# 代码展示
```cpp
#include<iostream>//当然，也可以使用万能头代替此头文件
using namespace std;
int T,n,h[100005];
bool f[100005];//用于标记此干草类型是否可能受到所有奶牛的喜爱 
int main(){
	scanf("%d",&T);//输入操作次数
	while(T--){
		scanf("%d%d",&n,&h[1]);
		for(int i=2;i<=n;i++){
			scanf("%d",&h[i]);
			if(!f[h[i]]&&(h[i]==h[i-1]||h[i]==h[i-2]))//判断h[i]是否符合要求
				f[h[i]]=true;//符合要求时打标记 
		}bool flag=true;//用于判断是否无解 
		for(int i=1;i<=n;i++)
			if(f[i])printf("%d ",i),f[i]=flag=false;//别忘记将f数组清零
		if(flag)printf("-1");//无解时，输出-1
		putchar('\n');//最后注意要输出换行符
	}
return 0;
}

```

---

## 作者：_ImposterX_ (赞：6)

手推几组数据不难发现，如果有两个相同的 $h_i$ 之间最多只隔着一个其他元素，那么 $h_i$ 一定是答案。

分两种情况证明：

- 设 $h_i = h_{i+1}$，那么对区间 $[i,i+2]$ 进行一次会议肯定会让 $h_{i+2} = h_i$，同理，对 $[i-1, i+1]$ 进行会议很定会让 $h_{i-1}=h_i$。以此类推，就可以让所有的 $h_i$ 相同。

- 设 $h_i = h_{i+2}$ 且 $h_i \ne h_{i+1}$，那么对区间 $[i, i + 2]$ 进行一次会议很定会让 $h_{i+1}=h_i$。依次类推，就可以让所有的 $h_i$ 相同。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

int n;
int a[MAXN];
bool in_ans[MAXN];
int last[MAXN];

void solve() {
	memset(in_ans, 0, sizeof(in_ans));
	memset(last, 0, sizeof(last));
	vector<int> ans;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= n; i++) {
		if(last[a[i]]) {
			if(i - last[a[i]] < 3 && !in_ans[a[i]]) {
				in_ans[a[i]] = true;
				ans.push_back(a[i]);
			}
		}
		last[a[i]] = i;
	}
	sort(ans.begin(), ans.end());
	if(ans.empty()) printf("-1\n");
	else {
		for (int i = 0; i < (int)ans.size(); i++) {
			cout << ans[i] << " \n"[i == (int)ans.size() - 1];
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：5)

$\text{Update on 2024.2.5}:$ 补充唯一性证明。

[题目传送门](https://www.luogu.com.cn/problem/P10131)

若有两头喜欢同样干草的奶牛相邻或中间隔了一头奶牛，那这种干草是可以的。

为什么呢？请看下面这组数据：
```
7
1 2 1 3 5 4 6
```
首先，FJ 召集 $[1,3]$ 的奶牛开会，序列变成了 `1 1 1 3 5 4 6`。

然后再召集 $[1,4]$（其实为了加快进度也可以是 $[1,5]$）开会，序列变成 `1 1 1 1 5 4 6`。

以此类推（其实像一个消消乐），最终序列变成 `1 1 1 1 1 1 1`。

下证没有别的方法。

若 $[i,j]$ 内喜欢某种干草的奶牛数量 $\ge \lfloor \frac{j-i+1}{2} \rfloor +1$，设其为 $\lfloor \frac{j-i+1}{2} \rfloor +1$ 个。若有 $\lfloor \frac{j-i+1}{2} \rfloor +1$ 个距离至少为 $3$ 且喜欢同一种干草的奶牛，那么至少要有 $3 \times \lfloor \frac{j-i+1}{2} \rfloor+1 \ge j-i+1$ 头奶牛。证毕。

时间复杂度 $\mathcal O(Tn)$。

代码：
```cpp
#include<cstdio>
using namespace std;
const int N=100010;
int a[N];
bool can[N];
void solve() {
  int n;
  scanf("%d",&n);
  for(int i=1;i<=n;i++) {
  	scanf("%d",&a[i]);
  	can[i]=false;
  }
  for(int i=1;i<n;i++)
    if(a[i]==a[i+1]||a[i]==a[i+2]&&i!=n-1)
      can[a[i]]=true;
  bool flag=true;
  for(int i=1;i<=n;i++)
    if(can[i]) {
      printf("%d ",i);
      flag=false;
	}
  if(flag)
    printf("-1");
  printf("\n");
}
int main() {
  int t;
  scanf("%d",&t);
  while(t--)
    solve();
  return 0;
}
```

---

## 作者：Su777 (赞：4)

## 题意简述
给定一个长度为 $n$ 的序列 $h$ 且 $1 \leq h_i \leq n$。对于每次操作，可以选择一个区间 $[l,r]$，此时如果存在一个数的出现次数严格大于区间长度的一半，就把整个区间都替换成那个数。求最后一共有多少种数可以出现 $n$ 次（整个序列都是那种数）。

## 分析样例
- 在 $T=1$ 的情况下，$2$ 连续出现了三次，此时可以选择区间 $[1,5]$，将所有位置替换为 $2$，答案为 $2$。
- 在 $T=2$ 的情况下，没有两个相邻位置是同样的数，所以无法替换，答案为 $-1$。
- 在 $T=4$ 的情况下，出现了形如 $\{3,x,3\}$ 的情形，这时只需要选择这个长度为 $3$ 的区间替换为 $3$，就可以转化为 $T=1$ 的情况了。

## 感性理解
- 当有两个相邻位置是同样的数时，可以将整个序列替换为这种数。
- 当有两个位置是同样的数，且中间只隔了一个位置，可以将整个序列替换为这种数。
- 当不存在上述两种情况时，无法替换。

## 严谨证明

### 结论一

假设 $h_i=h_{i+1}=x$。此时考虑左右两种方向。

**左方向操作方法**：假设此时 $[i-k,i]$ 区间内的数均为 $x$，那么 $k \geq 1$。选择区间 $[i-k-1,i]$ 进行操作。  
**右方向操作方法**：假设此时 $[i,i+k]$ 区间内的数均为 $x$，那么 $k \geq 1$。选择区间 $[i,i+k+1]$ 进行操作。  
**操作可行性**：区间长度为 $k+2$，其中至少有 $k+1$ 个数为 $x$。又因为 $k \geq 1$，等价于 $k+1 \geq \frac{k+2}{2}+1$，所以可以将整个区间替换为 $x$。后续区间以此类推，直到 $i-k-1=0$ 为止。

### 结论二

假设 $h_i=h_{i+2}=x$。此时选择区间 $[i,i+2]$，长度为 $3$，至少有 $2$ 个元素为 $x$。因为 $2 > \frac{3}{2}$，所以可以将整个区间替换为 $x$。

替换后可以发现，$h_i=h_{i+1}=x$。然后用结论一中的替换方法把整个序列都替换为 $x$ 即可。

### 结论三

用反证法进行解决。如果上述两种情况都不存在，也就意味着任意连续的三个位置都**互不相同**。

假设存在可替换区间 $[l,r]$，那么这个区间中有一种数的出现次数必定 $\geq \frac{r-l+1}{2}+1$。又因为任意连续三个位置都不不相同，这种数的出现次数必定 $\leq \lfloor \frac{r-l+1}{3} \rfloor$，矛盾。所以原假设不成立，在这样的序列中不存在任何一个区间可以进行替换，也就不可能有数出现 $n$ 次。

## 赛时代码

注意特判行末空格即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N = 2e5 + 10;
ll T, n;
ll arr[N];
ll ok[N];

int main() {
	cin >> T;
	while (T--) {
		memset(ok, 0, sizeof(ok));
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			cin >> arr[i];
			if (arr[i] == arr[i - 1]) ok[arr[i]] = 1;
			if (i > 1 && arr[i] == arr[i - 2]) ok[arr[i]] = 1;
		}
		ll cnt = 0;
		for (int i = 1; i <= n; i ++) {
			if (ok[i]) {
				cnt ++;
			}
		}
		
		if (cnt != 0) {
			int cnt2 = 1;
			for (int i = 1; i <= n; i ++) {
				if (ok[i]) {
					if (cnt2 != cnt) {
						cnt2 ++;
						cout << i << " ";
					} else {
						cout << i;
					}
				}
			}
		} else if (cnt == 0) cout << "-1";
		cout << endl;
	}
	return 0;
}

```

---

## 作者：Genius_Star (赞：4)

### 思路：

简单题。

考虑如果一个长度为 $3$ 的区间 $[l,l+2]$ 内如果有两只牛有相同的喜好，那么是可以将这个区间全部同化，即这次开了焦点小组后 $[l,l+2]$ 内喜好相同，那么可以通过开 $[l,l+3]$ 的焦点小组来进一步扩充相同序号的干草，一步一步的拓展，最终一定可以覆盖 $[1,n]$。

对于其余情况，是不可能的，因为喜欢一个干草的数量必须是区间长度严格一半以上，就算隔一个放一个相同喜好的干草，三个里还是肯定有两个相同的，证毕。

时间复杂度为 $O(N \log N)$。

**注意去重。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
struct Node{
	ll data;
	ll num;
}b[N];
ll T,n,x,cnt,t;
ll a[N],S[N];
set<ll> ans; 
void solve(){
	ans.clear();
	n=read();
	cnt=t=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(i>=3){
			if(a[i]==a[i-2]||a[i]==a[i-1])
			  ans.insert(a[i]);
			else if(a[i-1]==a[i-2])
			  ans.insert(a[i-1]);
		}
	}
	if(n==2){
		if(a[1]==a[2]){
			write(a[1]);
			putchar('\n');
		}
		else
		  puts("-1");
		return ;
	}
	if(ans.empty())
	  write(-1);
	for(auto v:ans)
	  S[++t]=v;
	for(int i=1;i<=t;i++){
		write(S[i]);
		if(i!=t)
		  putchar(' ');
	}
	putchar('\n');
}
int main(){
	T=read();
	while(T--)
	  solve();
	return 0;
}

```

---

## 作者：tangml (赞：4)

很简单的题了，只需要推一下，因为他的访谈次数不限，所以只要存在有三个数中含有两个相同的数，即可推广到所有的数。若不存在这样的数，则说明无解。证明也很简单，举个例子，如果五个数中，任意连续的三个都没有达到有两个相同的数，那么五个数中不可能有三个相同的。这五个数可以划分为三个区间来看，其实还是有一种贪心的思想在里面。

题目较为简单，难道建议给到橙就好。

```
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+100;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int a[N],n,l,ans[N];
set<int> s;

int main()
{
	int T;
	T=read();
	while(T--)
	{
		n=read();
		for(int i=1;i<=n;i++)	a[i]=read();
		if(n==2) {printf("%d\n",a[1]==a[2]?a[1]:-1);continue;}
		s.clear();
		for(int i=1;i<=n-2;i++)	
			if(a[i]==a[i+1] || a[i+1]==a[i+2] || a[i+2]==a[i])	
				{
					int len=s.size();
					s.insert(a[i]==a[i+2]? a[i]:a[i+1]);
					if(len!=s.size())	ans[++l]=a[i]==a[i+2] ? a[i]:a[i+1];
				}
		if(s.empty())	printf("-1");
		sort(ans+1,ans+l+1);
		for(int i=1;i<=l;i++)	printf("%d ",ans[i]);
		puts("");
		l=0;
		memset(ans,0,sizeof ans); 
	}
	return 0;
 } 
```


---

## 作者：zzhbpyy (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/P10131)

## 思路

题目看似复杂，其实只需要对每 $3$ 只相邻的奶牛进行考虑。显然，只要任意三只相邻奶牛中，有两只奶牛干草喜好相同，这种喜好就能通过向外“扩散”的焦点小组访谈统一到所有奶牛。

例如：

对测试用例

```
8
1 2 3 4 5 4 6 7
```
观察到编号为 $4$、$5$、$6$ 的三只奶牛中有两只奶牛干草喜好均为 $4$，依次对编号 $4$ 到 $7$，$4$ 到 $8$，$3$ 到 $8$，以此类推，进行焦点小组访谈即可。

遍历所有三只相邻奶牛，并用 vector 数组存储满足上述条件的干草，最后大胆 sort 排序即可。

另外，对于 $n = 2$ 的情况，只须特判两只奶牛干草喜好是否相同即可。

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[200005];
vector<int>f;
signed main(){
    ios::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);//关流加速读入
    cin>>t;
    while(t--){
        cin>>n;
        f=vector<int>();
        for(int i=1;i<=n;i++)
            cin>>a[i];
        if(n==2)
            if(a[1]==a[2])cout<<a[1];
            else cout<<-1;
        else{
            for(int i=1;i<=n-2;i++){//遍历所有三只相邻的牛。
                if(a[i]==a[i+1]||a[i]==a[i+2])f.push_back(a[i]);
                else if(a[i+1]==a[i+2])f.push_back(a[i+1]);
            }
            if(!f.size())cout<<-1;
            else{
                sort(f.begin(),f.end());
                int last=-1;bool flag=false;
                for(int i=0;i<f.size();i++){
                    
                    if(f[i]!=last){
                        if(flag)
                        cout<<" "<<f[i];
                        else{cout<<f[i];flag=true;}
                        last=f[i];
                    }
                }
            }
        }
        cout<<'\n';
    }
}
```


---

## 作者：lilong (赞：3)

Update on 2024.2.5：经 [Wuyanru](https://www.luogu.com.cn/user/400201) 大佬的指教，补充了一些证明。

直接选择一个大区间操作，似乎没有发现什么规律。不妨先从 $n$ 较小的情况开始分析。

- $n=2$

显然，在此情况下若两头奶牛喜欢相同种类的草则有解，否则一定无解（一定没有超过一半）。

- $n=3$

首先，三个数都不相同的情况必然无解。接着，如果有两个数相同，可能出现形如 $aab$ 或 $aba$ 两种情况（$baa$ 同理）。对整个序列进行一次操作，就可以变成 $aaa$ 了。

想到这里，我们就可以把 $n=3$ 的情况拓展到其余情况了。不难发现，若 $h_i = h_{i - 2}$ 或 $h_i= h_{i - 1}$（即上文所述的两种形式），则可以先变成一个长度为 $3$ 的连续段，然后再一位一位向外拓展，即有解。

证明也十分简单。假设有序列 $a,b,a,c,d$，其符合上述 $n=3$ 的一种情况。可以依次进行下列操作：

- 选择 $[1,3]$，序列变为 $a,a,a,c,d$。

- 选择 $[1,4]$，序列变为 $a,a,a,a,d$。

- 选择 $[1,5]$，序列变为 $a,a,a,a,a$。

于是就可以通过一位一位向外拓展达到目的了。

无解的情况说明两个相同的数间隔大于 $2$。以长度为 $4$ 的序列 $a,b,c,a$ 为例子，显然无论选择哪个区间进行操作，序列都不会发生改变，因此无法使所有数相同。更长的序列同理。

实现时需避免重复加入，并且输出前要排序。

原题中要求行末不能有多余的空格，但在洛谷上应该没有影响。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
//#define int long long

using namespace std;

int n,a[1000001],ans[1000001],cnt,pd[1000001];

int main()
{
//	freopen ( "1.out" , "w" , stdout );
	int T;
	cin >> T;
	while( T -- )
	{
		cin >> n;
		for( int i = 1 ; i <= n ; i ++ )
			cin >> a[i],pd[i] = 0;
		cnt = 0;
		for( int i = 2 ; i <= n ; i ++ )
			if( a[i] == a[i - 2] || a[i] == a[i - 1] )
				if( !pd[a[i]] )
				{
					cnt ++;
					pd[a[i]] = 1;
					ans[cnt] = a[i];
				}
		sort( ans + 1 , ans + cnt + 1 );
		if( cnt == 0 ) cout << "-1" << endl;
		else
		{
			for( int i = 1 ; i < cnt ; i ++ )
				cout << ans[i] << ' ';
			cout << ans[cnt];
			cout << endl;
		}
	}
	return 0;
}
```


---

## 作者：Mortidesperatslav (赞：2)

好题。

首先，如果有两头连续的牛喜欢相同草料，我们就慢慢来，每次加一头牛进来，这样所有牛就都喜欢这种草料了。

然后，如果有两头牛喜欢相同草料，但它们中间的不喜欢，就选它们和它们中间的那头牛，这样它们中间的那头牛也会被迫喜欢这种草料。这样也能满足。

如果中间隔两头牛，那么如果这种草料能够被所有牛喜欢，就必须有两头连续的牛喜欢该草料。否则因为没有超过半数，不满足。

那么只要判断两种情况，因为其余情况都能归纳成这两种。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],vis[11][100005],ans[100005],cnt;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		cnt=0;
		for(int i=1;i<n;i++){
			if(vis[t][a[i]])continue;
			if(a[i]==a[i+1])ans[++cnt]=a[i],vis[t][a[i]]=1;//第一种情况
			else if(i<n-1&&a[i]==a[i+2])ans[++cnt]=a[i],vis[t][a[i]]=1;
		}//第二种情况，vis 数组去重
		if(cnt==0){
			cout<<-1<<"\n";
			continue;
		}
		sort(ans+1,ans+cnt+1);
		for(int i=1;i<cnt;i++)cout<<ans[i]<<" ";
		cout<<ans[cnt];
		cout<<"\n";
	}
}
```

---

## 作者：tder (赞：2)

**USACO 不过滤行末空格。**

---

据题意，可以选择一个区间中的所有奶牛召开大会，若相同喜好的牛数超过一半，则所有奶牛均会被同化。

考虑一种特殊情况，当选定连续 $3$ 头奶牛的区间 $[i,i+2]$ 时，若有 $2$ 头及以上的奶牛喜好相同，则他们均会被同化，此时大致可分为 $\tt aab$ 和 $\tt aba$ 两种情况，即 $h_i=h_{i+1}$ 或 $h_i=h_{i+2}$，则会变为 $\tt aaa$。此时可继续同化区间 $[i+1,i+3]$ 以及 $[i-1,i+1]$，以此类推，直到所有奶牛均被同化。

例如，令 $h=\tt abcdcef$：

- 注意到区间 $[3,5]$ 为 $\tt cdc$，可召开大会同化为 $\tt ccc$；
- 此时 $h=\tt abcccef$，区间 $[2,4]$ 和 $[4,6]$ 分别为 $\tt bcc$ 和 $\tt cce$，可召开大会进行同化；
- 此时 $h=\tt acccccf$，区间 $[1,3]$ 和 $[5,7]$ 分别为 $\tt acc$ 和 $\tt ccf$，可召开大会进行同化；
- 最终 $h$ 变为 $\tt ccccccc$。

因此，若存在 $h_i=h_{i+1}$ 或 $h_i=h_{i+2}$，即可同化所有奶牛为 $h_i$，故 $h_i$ 为一种可行解。

那么，对于长度为 $x$ 的区间（其中 $x>3$），若可以同化，则必定有至少 $\lceil\frac x2\rceil$ 头奶牛喜好相同。利用反证法，令不存在连续的形如 $\tt aab$ 或 $\tt aba$ 的情况，即任意连续的长度为 $3$ 的区间内没有两头奶牛相同，那么，在整个长度为 $x$ 的区间的区间内，最多有 $\lceil\frac x3\rceil$ 只奶牛喜好相同，故无法同化。

综上所述，任何一种可以同化的区间均可被转化为长度为 $3$ 的区间考虑。

最终输出注意去重，可使用 [$\text{unique}()$ 函数](https://oi-wiki.org/lang/csl/algorithm/)。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
int t, n, h[N];
signed main() {
    cin>>t;
    while(t--) {
        cin>>n;
        for(int i = 1; i <= n; i++) cin>>h[i];
        vector<int> v;
        for(int i = 1; i <= n; i++) 
            if((i + 1 <= n && h[i] == h[i + 1]) || (i + 2 <= n && h[i] == h[i + 2])) 
                v.push_back(h[i]);
        if(v.empty()) cout<<-1<<endl;
        else {
            sort(v.begin(), v.end());
            int k = unique(v.begin(), v.end()) - v.begin();
            for(int i = 0; i < k; i++) {
                cout<<v[i];
                if(i < k - 1) cout<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：linjunye (赞：1)

看到这道题，是不是大家都有些茫然？

~~应该就我一个。~~

通过“样例解释”中的方法，我们可以发现：其实我们可以先让一个区间的奶牛都喜欢一种干草，然后一点一点向外进行，就能达到目的。

可以证明，只要有至少相邻的两头奶牛喜欢一种干草，那么我们就可以每次增加一头奶牛与它们访谈，一直循环，最终使得所有奶牛都喜欢一种干草。

这下，我们就能从规划 $x$（一个整数）次访谈变成规划 $1$ 次访谈了。 

那么，第 $1$ 次访谈该如何进行呢。

题目中说到，“如果有一种干草是小组中**超过一半**的奶牛喜欢的，则此次焦点小组访谈结束后，所有奶牛最终都会喜欢这种干草。”

不难发现，这种情况的最小范围就是：有三头奶牛，其中两头奶牛都喜欢同一种干草。

也就是说，这两头奶牛之间最多只能隔一头奶牛。

但是，可能其他地方能做到上述现象，这里做不到。所以，我们需要给每种奶牛喜欢的干草设两个变量：`pre`、`mn`，分别表示上一头喜欢它的奶牛的出现地点（方便计算），以及这些喜欢它的奶牛两两间隔的最短距离。

只要这些奶牛两两间隔的最短距离 $\le 3$，那么就可以让这个区间完成访谈，然后再按之前说的，一步步完成所有访谈。

提示：比赛中，一些输出格式不对也会导致 WA，并且我的代码是考场代码，所以会有输出格式的变化，特在此说明！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x7f7f7f7f;
struct hay{
	int pre,mn;//题解中已说明 
}a[100010];//这里的下标是干草编号，不是奶牛编号！ 
int T,n,x;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){//清空 
			a[i].pre=0;
			a[i].mn=INF;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			if(a[x].pre)a[x].mn=min(a[x].mn,i-a[x].pre+1);
			a[x].pre=i;
		}
		int no_answer=true;
		for(int i=1;i<=n;i++){
			if(a[i].mn<=3){
				if(!no_answer)printf(" ");//因为输出格式的一些变化，现在可以直接在末尾添加空格 
				no_answer=false;
				printf("%d",i);
			}
		}
		if(no_answer)printf("-1");
		if(T)printf("\n");//这个也是因为输出格式，现在可以直接换行 
	}
    return 0;
}

```

---

## 作者：_WRYYY_ (赞：1)

### 大意：

给定你一个长度为 $n$ 的序列 $\{h\}$，$1\le h_i\le n$，你可以对其进行若干次操作，操作为：

1. 选定一个区间 $[l,r]$。
1. 若在 $i\in[l,r]$ 中存在 $h_i$ 的数量大于 $\lfloor\frac{l+r}{2}\rfloor$，则令所有的 $k\in[l,r]$ 上的 $h_k=h_i$

求所有可能使 $\{h\}$ 中的所有元素都变成 $h_i$ 的 $h_i$ 个数，并以升序输出可能的 $h_i$，或判断无解。

### 分析：

先给出结论，如果存在一个长度为 3 的区间有 2 个及以上的 $h_i$，那么 $h_i$ 就是合法的。

考虑证明。

先证明充分性，对于一个长度为 3 的区间，若存在两个及以上的相同元素，则这个区间可以变为相同元素，而我们将该区间变为相同元素后，可以一个一个地扩展左右边界，因为区间长度只加一，而除了新加进来的这个元素，其他元素都是相同的，所以这个元素也会变成相同的，这样就可以保证扩展到整个区间。证毕。

再证明必要性，区间长度小于 3 时是显然的，区间长度大于 3 时，所需要的最少相同元素个数就是 $\lfloor\frac{l+r}{2}\rfloor+1$，$r-l+1$ 为奇数时，想要在该区间内获得最长的相同元素个数小于 $\lfloor\frac{l_1+r_1}{2}\rfloor+1$ 的区间 $[l_1,r_1]$ 就需要隔一个放一个 $h_i$，但即使如此也才能得到 2，无论向左或向右扩展都是得到一个长度为 3 的区间且相同元素个数大于半区间长。$r-l+1$ 为偶时也是要隔开放置，然后在此基础上还要在其中隔开来的地方再放一个 $h_i$，显然得不到长度为 3 及以上。由上可知，所有的区间长度大于 3 的合法区间里面都含有区间长度为 3 的小合法区间。证毕。

### Code:

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
using namespace std;
using namespace __gnu_pbds;
int h[200010];
bitset<200010> v;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T, n, x, fl;
	cin >> T;
	while (T--)
	{
		cin >> n;
		fl = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> x;
			if (h[x] && (h[x] == i - 1 || h[x] == i - 2))
				v[x] = 1;
			h[x] = i;
		}
		for (int i = 1; i <= n; i++)
		{
			if (v[i])
			{
				if(fl)
					cout << " ";
				cout << i;
				fl = 1;
			}
			v[i] = 0;
			h[i] = 0;
		}
		if(!fl)
			cout << "-1";
		cout << "\n";
	}
	return 0;
}

```


---

## 作者：Graph (赞：1)

首先，我们找一找规律：

```txt
... x x ...
```

这种情况可以一直往旁边扩展，这种情况，$x$ 可以为答案。

```txt
... x y x ...
```

这种情况可以先将 $y$ 扩展到，随后转化为上图，$x$ 可以为答案。

```txt
... x y z x ...
```

这种情况，目前不能将 $y,z$ 扩展到，因此目前不行。

那么两个 $x$ 隔更远也一定不行。

-----

那么我们找到 $a_i$ 出现的所有位置，判断他们相邻的隔了几个，若为 $0$ 或 $1$，则 $a_i$ 可以扩展到全局。

注意一下输出，判断这组数据有没有输出过（比赛时没发现不能输出多余空格样例错了好多发），分类讨论，如果到最后都没输出过就输出 `-1`。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=1e5+5;
int n,a[N],flag;
vector<int>wz[N];

void output(int x)
{
	if(flag==false)
		cout<<x,flag=true;
	else
		cout<<" "<<x;
	return ;
}

void Work()
{
	for(int i=1;i<=n;i++)
		wz[i].clear();
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		wz[a[i]].push_back(i);
	}
	flag=false;
	for(int i=1;i<=n;i++)
	{
		if(wz[i].empty()==true)
			continue;
		for(int j=1;j<wz[i].size();j++)
			if(wz[i][j]-wz[i][j-1]<=2)
			{
				output(i);
				goto go;
			}
		go: ;
	}
	if(flag==false)
		puts("-1");
	else
		puts("");
	return ;
}

signed main()
{
	int T;
	cin>>T;
	while(T--)
		Work();
	return 0;
}
```

时间复杂度：$O(n)$。

---

## 作者：newbieTroll (赞：0)

找规律。

考虑以下 $2$ 种规律：

这里用一种字母代表一种干草。

- 在一个 $[i,i+1]$ 的区间内，存在 `x x` 的结构，则可以使整个 $[1,n]$ 的区间都变成 `x`。

- 在一个 $[i,i+2]$ 的区间内，存在 `x y x` 的结构，则可以使整个 $[1,n]$ 的区间都变成 `x`。

找到了这两种规律，本题便迎刃而解。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N];

void work(){
	int n;
	cin>>n;
	set<int> st;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<n;++i){
		if(a[i]==a[i+1]) st.insert(a[i]);
	}for(int i=1;i<n-1;++i){
		if(a[i]==a[i+2]) st.insert(a[i]);
	}if(st.empty()){
		cout<<-1<<endl;
		return ;
	}for(auto i:st){
		cout<<i<<' ';
	}cout<<endl;
	return ;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		work();
	}
	return 0;
}
```

USACO 原题要求行末没有多余空格，但是在 luogu 上应该没有影响（

---

## 作者：Crazyouth (赞：0)

## 分析

注意到如果某种干草 $i$，存在情况 $i,i$ 或 $i,j,i$ 的情况，就可以以这三个作为重点小组，然后再向外扩展，因此只需要有这样的情况，就把 $i$ 加入 set，最后一起输出即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
set<int> st;
int a[200010];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		st.clear();
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<n;i++)
		{
			if(a[i]==a[i+1]||(i<n-1&&a[i]==a[i+2])) st.insert(a[i]);
		}
		if(st.empty()) cout<<-1<<endl;
		else
		{
			for(auto i=st.begin();i!=st.end();i++)
			{
				if(i==st.begin()) cout<<*i;
				else cout<<' '<<*i;
			}
			cout<<endl;
		}
	}
	return 0;
}

---

## 作者：sgl654321 (赞：0)

## 题目大意
- 有 $n$ 个人排成了一个序列 $a$，每个人喜欢吃一种食物 $a_i$，可以进行无数次美食节活动。
- 一次美食节选择 $a$ 中连续的一段人，如果有一种食物在这一段人中，喜欢它的人数**严格超过**了总人数的一半，那么这一段中所有人都会变得喜欢这一种食物。
- 询问：共有哪几种食物，可以通过无数次美食节活动，变得所有人都喜欢。多组数据。

## 解题思路
贪心简单题。

我们考虑每次美食节，选择长度为 $3$ 的一段，如果有一种食物被两个人喜欢，那么这三个人都会变得喜欢它。接着我们再以之为中心，向两边分别扩展，开美食节。这样，这种食物就会被所有人喜欢了。

因此题意就等价为：有几种不同的 $a_i$，满足存在 $k\in[1,n-1]$，$a_k=a_{k+1}$。

这个入门组小朋友应该也会吧。

### 参考代码
```cpp
#include<bits/stdc++.h>
#define maxn 100010
using namespace std;
typedef long long ll;
ll tt,n,a[maxn],b[maxn],tot,ans[maxn];
bool flag; 
int main(){
	cin>>tt;
	while(tt--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i],b[i]=0;
		if(n==2){
			if(a[1]!=a[2])cout<<-1<<endl;
			else cout<<a[1]<<endl;
			continue;
		}
		for(int i=1;i<=n-2;i++){
			if(a[i]==a[i+1])b[a[i]]=1;
			if(a[i]==a[i+2])b[a[i]]=1;
			if(a[i+1]==a[i+2])b[a[i+1]]=1;
		}
		flag=0;tot=0;
		for(int i=1;i<=n;i++)
			if(b[i])flag=1,ans[++tot]=i;
		if(flag==0)cout<<-1;
		else{
			for(int i=1;i<tot;i++)cout<<ans[i]<<" ";
			cout<<ans[tot];
		}
		if(tt)cout<<endl;
	}
	return 0;
}

```

---

## 作者：M1saka16I72 (赞：0)

# P10131 [USACO24JAN] Majority Opinion B 题解

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-usaco-2024-jan.html)

## 题意

给定一个长度为 $N$ 的序列 $h$，每次操作可以选择一个 $h$ 的连续子串，并且将其中的元素全部修改成子串中出现次数最多且超过其长度一半的元素，输出在经过若干次操作后，可以让哪些元素 $h_i$ 成为序列中唯一一种元素。

## 思路

看到 $N$ 的数据范围是 $2\times 10^5$，我们首先思考 $\mathcal O(N)$ 的算法。

很容易想到，序列 $h$ 中存在三个元素，其中有两个相同的 $h_i$（即序列中存在两个距离相隔不超过一个元素的 $h_i$） 是 $h_i$ 满足题面要求的充分条件，因为我们可以先把这三个元素全部修改为 $h_i$，然后就可以一点点将 $h_i$ 扩展到整个 $h$ 序列里。

以下是充要条件的证明：

## 做法证明

假设 $h$ 中距离相隔最短的两个 $h_i$ 之间间隔为两个元素或以上。

那么一个包含最多 $h_i$ 的子串必然是以下形式：

> $h_i,x,x,h_i,x,x,h_i$

即头、尾均为 $h_i$，每两个 $h_i$ 相隔两个元素，子串长度 $l=3k+1(k\in \mathbb{N^+})$。

此时子串里包含的 $h_i$ 数量为 $\frac{l-1}{3}+1=\frac{l+2}{3}=\frac{2l+4}{6}$，而题面中的要求数量最少为 $\lceil\frac{l}{2}\rceil=\frac{l+1}{2}$，由于 $l\geq4$，解不等式可得该子串中的 $h_i$ 数量一定不满足题目要求。

## 实现

在循环里对每个 $h_i$ 扫一遍，判断是否出现 $h_{i-1}=h_{i+1}$，$h_i=h_{i-1}$ 或 $h_i=h_{i+1}$ 的情况，如果出现就用一个 map 记录下来，然后排序输出即可。

### 代码
```cpp
int h[200005];
int d[200005];	//满足要求的元素
map<int,bool> f;	//记录满足要求的元素
map<int,bool> vis;
void solve(){
	f.clear();vis.clear();
	int n;read(n);
	for(int i=1;i<=n;i++){read(a[i]);}
	a[0] = -1,a[n+1] = -1;	//防止第1个元素被判定为与第0个元素相同或最后一个元素被判定为与第n+1个元素相同
	bool nf = 0;	//记录是否有解，无解输出-1
	for(int i=1;i<=n;i++){
		if(a[i-1]==a[i] || a[i+1]==a[i]){
			nf = 1;
			f[a[i]] = 1;
		}
		if(a[i-1]==a[i+1]){
			nf = 1;
			f[a[i-1]] = 1;
		}	//标记当前的解
	}
	if(nf){
		int cnt = 0;
		for(int i=1;i<=n;i++){	//再扫一遍，把所有满足要求的元素放到数组d里
			if(f[a[i]] && !vis[a[i]]){	//有解且不与之前的解重复
				cnt++;
				d[cnt] = a[i];
				vis[a[i]] = 1;
			}
		}
		sort(d+1,d+1+cnt);	//排序
		for(int i=1;i<=cnt;i++){
			cout<<d[i];
			if(i!=cnt)	cout<<" ";
		}
	}
	else	cout<<-1;	//无解
	cout<<"\n";
}

int main(){
	int t = 1;
	read(t);
	for(int tt=1;tt<=t;tt++){
		solve();
	}
}
```

---

## 作者：NATO (赞：0)

考虑我们在三头牛开会时有两头牛相同是所需牛数最小的可以改变牛的喜好的方法，如果初始存在连续三头牛中有两头牛相同，我们就可以通过不断地每次拉一头牛与两头相同的牛开会达到全部相同的目的，那么记录所有初始存在连续三头牛有两头牛相同的情况中那两头喜好相同的牛的喜好即可。

代码实现可用 `set` 去重。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
#define db double
using namespace std;
ll t,n;
ll a[100005];
set<ll>ans;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		ans.clear();
		cin>>n;
		for(ll i=1;i<=n;++i)cin>>a[i];
		for(ll i=2;i<=n;++i)
		{
			if(a[i]==a[i-1])ans.insert(a[i]);
			if(i>=3)
			{
				if(a[i]==a[i-2])ans.insert(a[i]);
			}
		}
		if(!ans.size())cout<<"-1\n";
		else
		{
			auto it = ans.begin();
			cout<<*it;
			for(auto i:ans)
			if(i!=*it)
			cout<<' '<<i;
			cout<<'\n';
		}
	}
}
```

---

## 作者：1234567890regis (赞：0)

# 思路解析

在看了样例之后，不难发现，只要 $3$ 个连续的牛中有 $2$ 个喜欢的干草类型相同，它们就可以不停地开会，让所有的牛喜欢的干草类型全部相同。

这是什么意思呢？举个例子。记 $a_i$ 为第 $i$ 头牛喜欢的干草类型，那么假如 $a_i,a_{i+1},a_{i+2}$ 中喜欢的有两个相同，就可以让 $a_i,a_{i+1}, a_{i+2}$ 开会，让这三个牛喜欢同一种干草。然后：

$a_i,a_{i+1}, a_{i+2},a_{i+3}$ 开会，这四个牛喜欢同一种干草。

$a_i,a_{i+1}, a_{i+2},a_{i+3},a_{i+4}$ 开会，这五个牛喜欢同一种干草。

$\cdots$

$a_i,a_{i+1}, \cdots a_n$ 开会，这些牛喜欢同一种干草。

然后向前开会：

$a_{i-1},a_i, \cdots a_n$ 开会，这些牛喜欢同一种干草。

$\cdots$

$a_1,a_2, \cdots a_n$ 开会，成功！

于是我们证明了只要任意 $3$ 个连续的牛中有 $2$ 个喜欢的干草类型相同，那么就是可解的，而且最后的干草类型是这三个牛中那两个喜欢的干草类型相同的牛喜欢的干草类型。

不难发现，这个条件已经很宽泛了，如果任意 $3$ 个连续的牛喜欢的干草都不相同，肯定是不可解的。怎么证明呢？其实很简单。用反证法：

如果存在 $a_i, a_{i+1}, \cdots, a_j$ 中喜欢的干草的种类相同的数量 $\ge \lfloor \frac{j-i+1}{2} \rfloor +1$，那么因为任意连续 $3$ 个牛喜欢的干草都互不相同，那么喜欢的干草的种类相同的数量又 $\le \lceil \frac{j-i+1}{3} \rceil$。

解完方程得：

$j  - i + 1 \le 3$，于是我们的猜测是对的。

于是我们证明了 “任意 $3$ 个连续的牛中有 $2$ 个喜欢的干草类型相同” 是 “本问题可解” 的充要条件。

但是如果你把代码提交上去，你会发现你有一个测试点错了。这很显然是题目卡常。毕竟俗话说得好：

数据范围易有坑，不加特判见祖宗。

你会发现当 $n=2$ 时，还需要特判一下。于是：

# AC 代码：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 2e5 + 7;
int a[MAXN];
vector<int> can; // 表示所有可能的干草类型

signed main()
{
	int q;
	cin >> q;
	while (q--)
	{
		can.clear(); // 多测清空
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) cin >> a[i];
		if (n == 2 && a[0] == a[1]) // 特判
		{
			cout << a[0] << endl;
			continue;
		}
		for (int i = 2; i < n; i++) // 判断连续三头牛中有没有两个喜欢类型相同
		{
			int a1 = a[i - 2], a2 = a[i - 1], a3 = a[i];
			if (a1 == a2 || a1 == a3) can.push_back(a1);
			if (a2 == a3) can.push_back(a2);
		}
		if (can.empty()) // 如果没有则无解
		{
			cout << "-1\n";
			continue;
		}
		sort(can.begin(), can.end());
		// USACO 不过滤末空格，所以要这样输出
		cout << can[0];
		for (int i = 1; i < can.size(); i++)
		{
			if (can[i] != can[i - 1]) // 过滤掉重复的干草类型
				cout << " " << can[i];
		}
		if (q != 0) cout << endl; // USACO 不过滤末换行，所以要这样输出。
	}
}
```

---

## 作者：_O_v_O_ (赞：0)

首先，当有 $i$ 满足 $h_i=h_{i+1}$ 时，$h_i$ 一定可以（因为可以往外“扩散”出去，即分别对 $(i,i+2),(i,i+3),\cdots(i,n),(i-1,n),(i-2,n)\cdots (1,n)$ 进行操作）。

其次，当有 $i$ 满足 $h_i=h_{i+2}$ 时，$h_i$ 也可以，因为可以先对 $(i,i+2)$ 进行一次操作，接着再“扩散”出去。

这道题就做完了，因为其他区间出现 $>$ 一半的数肯定满足上述两个条件之一（自己可以手搓几个数试试）。

接下来证不满足时必定无解：

首先考虑一段不满足上述条件的序列 $a,b,c,a,b,d$。

我们发现，对任意一个区间进行操作都不能改变任意一个数，更长的序列同理。

改变不了任意一个数，就相当于无解了。

------------

其实我们还可以这样证：

上面有一句话：

> 其他区间出现 $>$ 一半的数肯定满足上述条件之一。

而题目可以转化成：让一个区间变为该区间密度 $>50\%$ 的一个数。

我们考虑一个区间，如果不满足，则这个区间最好时的形态为 $abca$，此时 $a$ 的密度 $=50\%$。

由上面可得：如果不满足条件，密度最多为 $50\%$，而不可能满足条件。

---

## 作者：indream (赞：0)

## P10131 [USACO24JAN] Majority Opinion B 题解
[USACO](http://usaco.org/index.php?page=viewproblem2&cpid=1371) | [P10131](https://www.luogu.com.cn/problem/P10131)

### 思路
对于每一种干草，显然有以下三种情况可以使得所有干草都变成它：

- 该种干草累计出现次数大于 $\frac{n}{2}$；
- 连续出现的干草：可以每次将外围一个同化，直到全部完成；
- 隔一个出现的干草：先把中间不同的部分同化，接下来同上一种情况。

循环判一遍即可。

为何其它情况无解？

其它情况中，显然任意两种相同干草距离大于 $1$，最小间隔为二时亦只有一半，即其在区间内**不可能达到绝对多数**，故无解。

---

显然上述做法没有问题，但我赛后一看，第一种其实不用判，因为抽屉原理，如果符合第一种情况必然也符合第二种情况。。。

### 代码
本来是可以 $O(n)$ 的，但比赛时脑抽写了个 $O(n \log n)$，但反正不超时。
```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
int n,h[MAXN],cnt[MAXN],ans[MAXN],tot;
int main(){
    h[1]=h[0]=-1;
    int t;
    scanf("%d",&t);
    while(t--){
        tot=0;
        memset(cnt,0,sizeof(cnt));
        memset(ans,127,sizeof(ans));
        scanf("%d",&n);
        for(int i=2;i<=n+1;++i){
            scanf("%d",&h[i]);
            ++cnt[h[i]];
            if(cnt[h[i]]>n/2)
                ans[tot++]=h[i];
            if(h[i]==h[i-1]||h[i]==h[i-2])
                ans[tot++]=h[i];
        }
        if(tot==0){
            puts("-1");
            continue;
        }
        sort(ans,ans+tot);
        tot=unique(ans,ans+tot)-ans;
        for(int i=0;i<tot;++i){
            printf("%d",ans[i]);
            printf((i==tot-1)?"\n":" ");
        }
    }
    return 0;
}
```


---

## 作者：T_TLucas_Yin (赞：0)

很容易想到，一种干草可以在越来越大的范围内被所有牛喜欢，直到最后被整个序列上的牛都喜欢。

又容易发现，每三头牛的区间里若有两头喜欢同一种草，则对这三头奶牛召开会议就会使得三头牛都喜欢这种草。然后对后两头牛和它们后面的那头牛召开会议，它们后面的那头牛也会喜欢这种草；对前两头牛和它们前面的那头牛召开会议，它们前面的那头牛也会喜欢这种草，这样就形成了更大的区间，以此类推，这种草就能成为所有牛都喜欢的草。

所以对于任意连续 $3$ 头牛的区间内，如果有被喜欢两次及以上的草，则这些草都可以成为风靡整个牛群的草。换句话说，一棵草如果被第 $i$ 头牛喜欢的同时也被第 $i-1$ 或第 $i-2$ 头牛喜欢，这棵草就满足要求。

如何证明其他情况下均不可解呢？也很简单。考虑反证：如果一个区间 $[l,r]$ 里任意连续 $3$ 个元素都各不重复，则这个区间里出现最多的元素最多就有 $\lceil \frac {r-l+1} 3\rceil$ 个。而只有当一个元素在 $[l,r]$ 里出现至少 $\lfloor \frac {r-l+1} 2\rfloor+1$ 次时，才有可能最终被所有牛喜欢。由于 $\lceil \frac {r-l+1} 3\rceil<\lfloor \frac {r-l+1} 2\rfloor+1$，所以这样的元素是不满足条件的。也就是说区间里只有在连续 $3$ 个位置上重复出现的元素才可能满足条件。进而得到只需判断这种元素即可。

注意别把草重复加入答案序列。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1000005],f[1000005],top;
map<int,bool> m;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        m.clear(),top=0;
        for(int i=1;i<=n;i++){
        	if(m[a[i]]) continue;//已经在答案中的草无需再看
			if(a[i]==a[i-1]||a[i]==a[i-2]) m[a[i]]=1,f[++top]=a[i];
		}
		sort(f+1,f+1+top);
		for(int i=1;i<=top;i++) cout<<f[i]<<" ";
		if(!top) cout<<-1;
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：MicroSun (赞：0)

策略题。

结论：当且仅当整个区间中有距离小于等于 $2$ 且共同喜欢品种 $m$ 的两只奶牛存在，FJ 可以使全体奶牛都喜欢 $m$。

证：

充分性：我们可以不断地召开包含三只奶牛且两只的爱好都为 $m$ 的焦点小组访谈，容易发现这样的区间是存在的。在一些操作后一定会使全部奶牛都喜欢 $m$。

必要性：可以考虑使用反证法。设召开焦点小组访谈的区间长为 $l$，其中有大于 $\lfloor\frac{l}{2}\rfloor+1$ 只爱好为 $m$ 的牛。考虑仅有 $\lfloor\frac{l}{2}\rfloor+1$ 只牛的情况，可以发现无法将 $\lfloor\frac{l}{2}\rfloor+1$ 只牛在长度为 $l$ 的区间内排布使得任意两只牛的距离最小为 $3$。所以牛数更多的情况显然也不可能。

证毕。

对上述结论进行模拟即可。代码实现上可以使用 map 进行去重。

code:

```cpp
// Problem: Problem 1. Majority Opinion
// LuoguUID: 514700 
// LuoguUserName: MicroSun
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
#define rep(i,s,t) for(int i=s;i<=t;++i)
void solve(){
	map<int,bool> mp;
	int n;
	cin>>n;
	memset(a,0,sizeof(a));
	rep(i,1,n) cin>>a[i];
	rep(i,1,n){
		if(a[i]==a[i+1]||a[i]==a[i+2])
			mp[a[i]]=1;
	}
	if(mp.size()){
		int cnt=0;
		for(auto i:mp){
			++cnt;
			if(cnt!=mp.size())
				cout<<i.first<<' ';
			else
				cout<<i.first;
		}
	}
	else cout<<-1;
	cout<<endl;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

给你一个长度为 $n$ 的序列 $a$，可以进行任意多次操作，每一次可以选择一个区间，其众数个数严格大于区间长度的一半，并将这个区间所有数改为为这个众数。请问最终这个序列所有的数都一样的时候这个数可能是多少？无法都一样则输出 $-1$。多测。

# 思路分析

怎么说都知道搜索是错的，$2\times10^5$ 能给你放过去？！

这时候我们分析一下每一次操作：其众数个数严格大于区间长度的一半。

首先我们知道，如果两个一样的数放在一起，那么这个数一定是可以的。他可以选两个这个数，然后从相邻的地方强制选一个数加进来，变成这个数，以此类推：$aab$ 变为 $aaa$。

我们就能发现，如果选的序列是偶数长度的，众数个数又在长度的一半以上，那么一定有相邻的。

如果是奇数长度呢？为了没有相邻的，这个串必须是这样：$abacadaeaf\dots$。

我们随机抓取一段，比如 $aba$。我们发现其还是可以变成 $aaa$。

就此我们知道，只用列举长度为 $3$ 的序列，找到一个出现两次的数就是一个可行的数。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[200005]; 
map<int, bool>ans; map<int, bool>::iterator it;
int main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n; ans.clear();
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			if (i > 1 && a[i] == a[i - 1]) ans[a[i]] = 1;
			if (i > 2 && a[i] == a[i - 2]) ans[a[i]] = 1;
		}
		for (it = ans.begin(); it != ans.end(); ++it)
			cout << it->first << " ";
		if (!ans.size()) cout << "-1";
		cout << endl;
	}
	return 0;
}
```

这题其实可以算是抄的，因为我竟然做过原题（形式化题意基本一样的那种），但是记不住题号了。

---

## 作者：Cuiyi_SAI (赞：0)

## 闲话

第一次打 USACO，真是太刺激太好玩了，会弄就多弄点。

update 2024-2-5：止步 $\text{Silver}$ 了，才 694pts，算了下次再努力。

## $\text{Question}$

给定一个 $n$ 个数的序列 $a$，定义一次操作为在序列中选定一个区间，若区间的某个数的个数大于区间长度的一半，那么就可以将这个区间全部变为这个数。问有哪些数可以经过若干次操作后使得整个序列都变成这个数。

## $\text{Solution}$

考虑选一个长度不大于 $3$ 的区间，如果里面有至少两个数相同，那么另外一个数必然会被变得相同，然后整个区间都相同了。此时我们就是的序列中有连续的三个数相同，所以此时我们如果把这个区间移动一位，又将得到一个长度为 $3$ 的区间，且这个区间同样至少有 $2$ 个数相同（因为上一次操作），所以我们又可以把这个区间变得相同。

于是这样一次次拿小区间来扩张，若干次后整个序列就会变成同一个数。
于是我们就有了策略：**如果一个数 $x$ 在距离它两格以内还有一个 $x$，那么整个序列都能变成 $x$**。

如果我们找不到这样的小区间，显然就连一次扩展也无法完成（小区间找不到大区间更不可能），此时无解。特别的，若 $n=2$，那么除非序列本身就全部相同，否则无解（因为你无法选出大于区间一半的人数）。

## $\text{Code}$

代码有点细节，考场上稀里糊涂的调过了。


```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100010];
bitset<100010> v;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        v&=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        if(n==2){
            if(a[1]==a[2]) cout<<a[1];
            else cout<<-1;
            cout<<"\n";
            continue;
        }
        for(int i=2;i<=n;i++){
            if(a[i-2]==a[i]||a[i-1]==a[i]) v[a[i]]=1;
        }
        if(v.count()==0) cout<<"-1";
        else{
            int i=1;
            while(!v[i]) i++;
            cout<<i;
            i++;
            for(;i<=n;i++) if(v[i]) cout<<' '<<i;
        }
        if(T) cout<<"\n";
    }
    return 0;
}
```

---

## 作者：Guizy (赞：0)

结论题。很容易发现，只要有连续的两个 $x$，或者有形如 $xyx$ 的情况出现，所有的奶牛就可以喜欢 $x$ 这种干草。

证明如下：

- $xx$：我们可以每次对 $x$ 的周围开会，直到所有的奶牛都喜欢 $x$ 为止。

例子：

假设 $a_i,a_{i+1}$ 都为 $x$，我们对 $a_i,a_{i+1},a_{i+2}$ 开一次会，对 $a_{i+1},a_{i+2},a_{i+3}$ 开一次会，就能让 $a_i\sim a_n$ 都为 $x$。向前同理。

- $xyx$：我们可以先对 $xyx$ 三个开会，然后就变成形如 $xxx$ 的情况，然后按照上面的情况处理即可。

坑点：要升序输出，要去重，行末不能有多余空格。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Max=100001;
int _,n,a[Max],ans[Max],flag[Max];

int main(){
	
	scanf("%d",&_);
	
	while(_--){
		int cnt=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]==a[i-1]&&!flag[a[i]]) ans[++cnt]=a[i],flag[a[i]]=1;
			else if(i>2&&a[i]==a[i-2]&&!flag[a[i]]) ans[++cnt]=a[i],flag[a[i]]=1;
		}
		sort(ans+1,ans+cnt+1);
		for(int i=1;i<=cnt;i++){
			if(i!=1) printf(" ");
			flag[ans[i]]=0;
			printf("%d",ans[i]);
		}
		if(cnt==0) printf("-1");
		puts("");
	}
	
	return 0;
} 
```

---

## 作者：apiad (赞：0)

[博客园食用更佳](https://www.cnblogs.com/gsczl71/p/17909469.html)。


一开始我试着用双指针，但发现好像写不了。

后面发现恍然大悟。这道题我们可以手玩一定长度的数组。假设我们只有两种情况 $1$ 代表的是相同数字的数，$0$ 代表的是不同数字的数。

我们会发现只有形如 $1,1$ 或 $1,0,1$ 的子数组是最基础的形式，由这样可以变成 $1,1,1$，$1,1,1,1$ 等知道填满数组，这样，就可以让所有的数字统一了。这也达到了目的。

因为只需要找到一段连续的（长度至少为 $2$）的 $1$ 必然可以扩充到长度为 $n$。

然而，我们发现很多种情况都是 $1,1,1,1,0,0,0,0$ 或者 $1,1,1,0,1,1,0,1$，这样都可以分为很小段的 $1,1$ 来解决，但是肯定不止这种情况。例如 $1,0,1,0,1$，这种可以分解成 $1,0,1$ 这种来解决，你会再发现，没有其他可能会分为其他更小的字串来解决了。于是，我们的问题也就是去找 $1,1$ 和 $1,0,1$ 了。

所以我们只需要记录哪些数 $a_i = a_{i+1}$ 或 $a_i = a_{i+2}$。用 set 记录。

然后 set 自动排序和去重，直接输出即可。

但注意的是，你可能也有这样的经历！

![](https://cdn.luogu.com.cn/upload/image_hosting/5egxw92w.png)

你会觉得很逆天，但是“每一行后不能加空格”。这样，我们又愚蠢的把 set 转成 vector，判断是不是到末尾，是的话就不加空格。

话说 USACO 这波真的很逆天。


```cpp
int n;
int a[N];
void solve(int T){
    cin >> n;
    for(int i = 1;i <= n;i++)cin >> a[i];    
    set<int >ans;
    for(int i = 1;i <= n;i++)if((a[i]==a[i+1] && i < n )|| (a[i]==a[i+2] && i < n-1))ans.insert(a[i]);    
    vector<int> s;for(auto it:ans) s.pb(it);
    for(int i = 0;i < (int(s.size()-1));i++) cout<<s[i]<<" "; if(s.size())cout<<s[s.size()-1];    
    if(s.size()==0)cout<<-1;
    if(T)cout<<endl;    
}
signed main(){
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T=1;
    cin >> T;
    while(T--) solve(T);
    return 0;
}
```

---

## 作者：WA_WonderfulAnswer (赞：0)

考试时直接 AK 了，来水一篇题解。

## 思路
我们不难发现，在连续的 $3$ 头奶牛中，只要有任意两头喜欢的干草品种相同，就可以让所有奶牛都喜欢这种草。我用 $mark$ 数组来统计 $i$ 号甘草是不是可以被所有奶牛喜欢。如果有，就输出。
>+ 对于升序输出的问题，用数组的下标做桶计数，因为下标是有序的。

>+ 对于行末没有空格的问题，我是先输出第一种满足题意的干草的编号，以后每次先输出空格再输出干草的编号。（变量 $count$ 的作用）

如果到最后 $count$ 还是 $0$，就说明没有奶牛会改变他们的喜好，输出 $-1$。
## AC Code
```c
#include <stdio.h>
#include <string.h>
#define N 200005
int mark[N], num[N], t, n, count;

int main() {
	scanf("%d", &t);
	for (int k = 1; k <= t; k++) {
		scanf("%d", &n);
		count = 0;
		memset(mark, 0, sizeof(mark));
		for (int i = 1; i <= n; i++)
			scanf("%d", &num[i]);
		for (int i = 1; i <= n; i++)
			if ((num[i - 2] == num[i] && i > 2) || (num[i - 1] == num[i] && i > 1))
				mark[num[i]] = 1;
		for (int i = 1; i <= n; i++)
			if (mark[i] > 0) {
				if (count > 0)
					printf("%c", ' ');
				printf("%d", i);
				count++;
			}
		if (!count)
			printf("%d", -1);
		if (k != t)
			printf("%c", '\n');
	}
	return 0;
}
```
## AC 记录
![AC](https://cdn.luogu.com.cn/upload/image_hosting/53g8p7pk.png)

[洛谷记录](https://www.luogu.com.cn/record/146195256)


---

## 作者：rnf5114 (赞：0)

铜组又在第一题放时间复杂度证明题了。

性质一：因为我们可以做无数次访谈，所以对于某种干草只要能够改变一次其它奶牛的喜好，那么就可以一直做下去。

性质一证明：如果发生改变，说明这一段区间内喜欢这种干草的奶牛数量是大于一半的，最少也会有两只（区间长为 $3$），在这之后一次只要纳入一只奶牛，就可以一直做下去，直到所有奶牛全部喜欢这种干草即可。

性质二：对于任意一种干草，只要能有两个相邻的奶牛同时喜欢它，就可以发生对于其它奶牛喜欢的干草产生改变。

性质二证明：选取包含这两头奶牛且长度为 $3$ 的区间即可，剩下的操作就回到了性质一。

对于无解情况：如果任意长度为 $3$ 的区间内没有相邻的两只奶牛喜欢同一品种的干草，那么无解，因为一次操作也做不了。

记得特判 $n$ 为 $1$ 或 $2$ 的情况。

代码很简单，就不放了。

---

