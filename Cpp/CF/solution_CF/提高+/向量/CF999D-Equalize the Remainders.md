# Equalize the Remainders

## 题目描述

You are given an array consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ , and a positive integer $ m $ . It is guaranteed that $ m $ is a divisor of $ n $ .

In a single move, you can choose any position $ i $ between $ 1 $ and $ n $ and increase $ a_i $ by $ 1 $ .

Let's calculate $ c_r $ ( $ 0 \le r \le m-1) $ — the number of elements having remainder $ r $ when divided by $ m $ . In other words, for each remainder, let's find the number of corresponding elements in $ a $ with that remainder.

Your task is to change the array in such a way that $ c_0 = c_1 = \dots = c_{m-1} = \frac{n}{m} $ .

Find the minimum number of moves to satisfy the above requirement.

## 样例 #1

### 输入

```
6 3
3 2 0 6 10 12
```

### 输出

```
3
3 2 0 7 10 14 
```

## 样例 #2

### 输入

```
4 2
0 1 2 3
```

### 输出

```
0
0 1 2 3 
```

# 题解

## 作者：Tachibana27 (赞：6)

用不定长二维数组 $mod_i$ 表示余数为 $i$ 的所有下标。随后我们的目标是使得 $mod_i(1\le i\le m-1)$ 相等，思路是让多于 $\frac{n}{m}$ 的匀给少于 $\frac{n}{m}$ 的。用一个二元组队列（这个数据结构不重要）$lot$ 存储多于 $\frac{n}{m}$ 的，其中二元组表示下标与值。枚举余数，当遇到少于 $\frac{n}{m}$ 的就匀给它并使用下标修改原数组。

需要循环 $2$ 遍，因为有可能遇到少于 $\frac{n}{m}$ 的时候 $lot$ 为空，也就是在这之前多的已经被用光了。

但是考虑到一个问题，原数组只能加不能减，如果 $ans$ 和原数组直接加上 $i\mod m-yu$ ($i$ 是枚举的余数，$yu$ 是二元组中存的值)，就会出现特殊情况。

比如：现在余数是 $4$，希望到 $3$。

错误做法：$4-3=1$，$ans\gets ans+1$。

正确做法：$m-(4-3)=m-1$，$ans\gets ans+m-1$。

所以特判一下，使得余数绕一圈在回到当前枚举余数，这样可以通过。

不开 long long 会见祖宗。

code:

```cpp
%:include<bits/stdc++.h>
#define int __int128//因为用了快读快写，所以用int128 
inline int read()<%
	int s=0;
	int w=1;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
    	if(ch=='-')
			w=-1;
	for(;ch>='0' and ch<='9';ch=getchar())
		s=s*10+ch-'0';
	return s*w;
%>

void write(int x)<%
	if(x<0)<%
   		putchar('-');
   		x=-x;
	%>
	if(x>9)
    	write(x/10);
	putchar(x%10+'0');
	return;
%>//自动掠过 
int n;
int m;
int a[2000086];
int ans;
std::queue<std::pair<int,int> >lot;
signed main()<%
  	//freopen(".in","r",stdin);
  	//freopen(".out","w",stdout);
	n=read();
	m=read();
	int op=n/m;
	std::vector<std::vector<int> >mod(m);
	for(int i=1;i<=n;i++){
		a[i]=read();
		mod[a[i]%m].push_back(i);//存下余数 
	}
	for(int i=0;i<2*m;i++){//需要枚举2次余数 
		while(mod[i%m].size()>op){//如果超出n/m就放到lot里面 
			lot.push({i%m,mod[i%m].back()});
			mod[i%m].pop_back();
		}
		while(mod[i%m].size()<op){//否则去lot里面匀 
			if(!lot.size())
				break;
			int yu=lot.front().first;//余数 
			int id=lot.front().second;//下标 
			mod[i%m].push_back(id);
			if(i%m<a[id]%m){//需要特判，这种情况便是我举的例子 
				a[id]+=i-yu;
				ans+=i-yu;
			}
			else{//正常情况 
				a[id]+=i%m-yu;
				ans+=i%m-yu;
			}
			lot.pop();//你需要把它再弹出来，因为它被用过了。 
		}
	}
	write(ans); 
	puts("");
	for(int i=1;i<=n;i++){
		write(a[i]);
		std::cout<<" ";
	}
  	return 0;//撒花 
%>


```

---

## 作者：wutiruo (赞：3)

这题使用M个向量，分别存余数**0,1,2,...m**.（每次存下标）
每次要增加1，就是把当前队列里的一个数放到下个队列里。

如果当前队列比正常数量多，就扔到一个“free”队列里。

如果少：

         如果“free”不为空
            一直从“free”队列里把下标扔到Ci向量里
         否则
            再做第二次，最多做两次，同时，计算代价。
 		   计算方法在程序里


程序：

```cpp
#include<iostream>
#include<vector>
using namespace std;
int main(){
	int n,m,k;
	long long s=0;
	cin>>n>>m;
	k=n/m;//k是每个队列数字的正常数量 
	vector<int> a(n);//原数组 
	vector<vector<int>> v(m);//m个队列 
	vector<pair<int,int>> free;//多出来的数放在这 
	for(int i=0;i<n;i++){//读入，不做解释 
		cin>>a[i];
		v[a[i]%m].push_back(i);
	}
	for(int i=0;i<m*2;i++){//最多走两次队列 
		int cur=i%m;
		while(v[cur].size()>k){//当前Ci比正常数量多 
			int p=v[cur].back();
			v[cur].pop_back();
			free.push_back(make_pair(p,i));
		}
		while(free.size() && v[cur].size()<k){//当前Ci比正常数量少 
			int element=free.back().first;
			int mod=free.back().second;
			free.pop_back();
			v[cur].push_back(element);
			int dj=i-mod;
			a[element]+=dj;
			s+=dj;
		}
	}
	cout<<s<<endl;
	for(int i=0;i<n;i++)
		cout<<a[i]<<' ';
	return 0;
}
```

---

## 作者：_RainCappuccino_ (赞：2)

# 题意

给定一个长度为 $n$ 的序列和一个模数 $m$，记 $c_i$ 表示 $\bmod m$ 后的结果为 $i$ 的数的个数。现在可以使每个数增加 $1$，请问最少要操作多少次才能使所有 $c_i = \frac{n}{m}$。并输出最后的序列。

# First. 如何最小化操作次数

由于每次操作会使 $c_{a_i \bmod m} - 1$，$c_{(a_i + 1) \bmod m} + 1$，那么不妨先将所有 $a_i$ 按照 $\bmod m$ 后的结果分组，下文称模数集合。对于每个余数考虑是否将其中的一些数给到下一个没有达到 $\frac{n}{m}$ 的余数。

对于 $c_i > \frac{n}{m}$ 的模数 $i$，首先，它里面的值一定都要加至没要达到 $\frac{n}{m}$ 的模数集合里。那么，肯定移动到的模数集合的距离越近越好。所以，可以用一个 set 来维护所有没有达到 $\frac{n}{m}$ 的模数，查找离其最近的一个模数 $nxt$，然后将 $i$ 中的元素加至 $nxt$ 中。

这里的查找可以用 `s.lower_bound`。如果没有，那么取 set 里的第一个元素（因为模数 $+ 1$ 是循环的）。

每次操作完，如果该模数已经满足，那么将其从 set 中删去。

这样，由于每次我们移动都是移至最近的一个没有满足的模数（移至满足了的模数没有意义，因为枚举到它的时候又会传给下一个数），那么操作次数也肯定是最少的。

# Second. 怎么输出序列

这个很简单，你在维护集合的过程中，集合中既存数值，也存该数值的编号。移动的时候只修改值。最后再加上修改完的值与原来的值的差即可。

# Third. 细节和时间复杂度分析

## 时间复杂度分析

对于每个数，我们只将其分组 + 移动，移动过后不会再操作（因为刚好达到条件的组不需要再次操作），而每次移动是 $O(\log_2n)$ 的，数又有 $n$ 个，于是整体复杂度是 $O(n \log_2n)$ 的。

## 细节

1. 题目要求最终的值不能超过 $10^{18}$ 那么每次移动数要尽可能小。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 2e5 + 10;
int n, m;
int a[N], c[N];
set<int> s;
vector< pair<int, int> > b[N];

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	int len = n / m;
	for (int i = 1; i <= n; i ++) cin >> a[i], b[a[i] % m].push_back({a[i], i});
	for (int i = 0; i < m; i ++) {
		sort(b[i].begin(), b[i].end(), greater<pair<int, int> > ());
		if (b[i].size() < len) s.insert(i);
	}
	for (int i = 0; i < m; i ++) {
		while (b[i].size() > len) {
			auto pos = s.lower_bound(i);
			pair<int, int> ft = b[i].back();
			b[i].pop_back();
			if (pos == s.end()) pos = s.begin();
			int nxt = *pos;
			b[nxt].push_back({ft.first + (nxt - i + m)% m/*操作次数*/ , ft.second});
			if (b[nxt].size() == len) s.erase(pos);
		}
	}
	for (int i = 0; i < m; i ++) {
		for (auto x : b[i]) {
			c[x.second] = x.first;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		ans += c[i] - a[i];
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i ++) cout << c[i] << ' ';
	return 0;
}
```

---

## 作者：Miracle_1024 (赞：2)

### 思路：
这是一道明显的贪心题。

首先我们考虑所有数模上 $m$ 的余数存储起来，由于我们要找的是某固定余数的数量，我们可以换一种存法：对于每种可能的余数用一个队列维护余数为该数的数的坐标。

存储起来后，我们一次遍历所有可能的余数。如果当前余数的个数大于 $n/m$，那么这个余数中的一些数肯定可以用于给个数少的余数增加个数，因此我们将这些数推入另一个专门存放这些多余的数的队列。

如果我们发现一个数量小于 $n/m$，那么我们取队头的那个元素并计算其变为当前余数的代价。如果两个数中我们要使余数较小的那个数 $s$ 的余数增加到余数较大的那个数 $t$ 的余数，那么我们需要增加的就是 $t$ $\bmod$ $m$ $-$ $s$ $\bmod$ $m$。如果我们要使余数较大的数 $t$ 增加到余数较小的数 $s$，那么我们需要增加的就是 $s$ $\bmod$ $m$ $+$ $m$ $-$ $t$ $\bmod$ $m$。

此时可能出现一种问题：开始的几个小余数数量全部没有 $n/m$ 大，导致我们开始无法补偿，后面溢出。为了解决这一问题，我们可以破环为链，将整个循环遍历两遍，从 $0$ 遍历到 $2 \times n - 1$。这样我们在第二遍遍历到的时候就可以用后面的余数弥补了。

### 代码：
```
#include <iostream>
#include <queue>
using namespace std;
const int N = 2e5+10;
#define int long long
int n, m, c, cnt;
int a[N];
queue<int> q[N];
queue<int> Q;
signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    c = n / m;
    for (int i = 1; i <= n; i++) q[a[i] % m].push(i);
    for (int i = 0; i < 2 * m; i++)
    {
        while (q[i%m].size() > c)
        {
            Q.push(q[i%m].front());
            q[i%m].pop();
        }
        while (Q.size() && q[i%m].size() < c)
        {
            if (i % m < a[Q.front()] % m)
            {
                cnt += (i % m) + m - (a[Q.front()] % m);
                a[Q.front()] += (i % m) + m - (a[Q.front()] % m);
                q[i%m].push(Q.front());
                Q.pop();
            }
            else
            {
                cnt += (i % m - a[Q.front()] % m);
                a[Q.front()] += (i % m - a[Q.front()] % m);
                q[i%m].push(Q.front());
                Q.pop();
            }
        }
    }
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    return 0;
}
```


---

## 作者：jch123 (赞：1)

## 思路：

首先可以发现可以用一个数通过一直加去补少的余数，代价为余数之差，如果目标小，则需要 $+m$，可以开两个队列，一个队列记录余数为某个数时的个数，另外一个记录当前哪些数可以去补。然后就非常简单，如果这个数多余，那么就扔到补偿队列中，否则就从补偿队列中补就行，同时更新原数组的元素与操作次数。注意要破环成链，因为前面的数最开始无法补偿。下标从 $0$ 开始比较好写。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll a[N];
queue<int> p[N];//余数队列 
queue<int> q;//补偿队列 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i],p[a[i]%m].push(i);
	int k=n/m;
	ll ans=0;
	for(int i=0;i<2*m;i++)//防止前面的数没有补偿 
	{
		while(p[i%m].size()>k)
		{
			q.push(p[i%m].front());
			p[i%m].pop();
		}
		while(q.size()&&p[i%m].size()<k)
		{
			int x=i%m,y=a[q.front()]%m;
			ll dis=x-y;
			if(x<y) dis+=m;//只能循环一圈 
			ans+=dis,a[q.front()]+=dis;
			p[i%m].push(q.front());
			q.pop();
		}
	}
	cout<<ans<<'\n';
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	return 0;
}
```

---

## 作者：TruchyR (赞：1)

贪心不会证，于是有了这个推法。   

下文的 $k$ 指 $m$，$T(i)=(i+1)\bmod k$，$h=\dfrac{n}{k}$。  

首先，令 $a_i$ 表示模 $k$ 余 $i$ 的数的数量。  

于是问题转化为：

- 每次操作可以使 $a_i\rightarrow a_i-1$，$a_{T(i)}\rightarrow a_{T(i)}+1$，问让所有数都为 $h$ 的最小操作数。  

设 $l_i$ 为对 $i$ 操作的次数，可以列出以下方程：  

- $l_{i-1}-l_i=h-a_i$，前提是 $i\geq 1$。  
- $l_{k-1}-l_0=h-a_0$，这个式子可以由上式得出。  

发现方程有多解，不妨钦定 $l_{k-1}=0$，然后就可以 $O(n)$ 解出方程。  

又发现 $l_i\geq0$，且答案需要最小，所以让所有数减去他们的最小值是最优的。  

至此，输出答案解决。

至于构造方案： 
- 考虑按照模 $k$ 的余数将输入排序。  
- 找到一个使得 $l_i\leq a_i$ 的 $i$，开始构造。
  - 易证一定存在这么一个 $i$。  
- 每次可以将模 $k$ 余 $i$ 的后 $l_i$ 个数加一，令 $i\rightarrow T(i)$。  
- 以上过程其实就是一个模拟，运用差分可以做到  $O(n)$。  

代码如下： 
```cpp
#include<bits/stdc++.h>
#define MX 200005
#define int long long
using namespace std;
int n,h,k,w,a[MX],l[MX],res,ans[MX];
struct eg{int u,id;}b[MX];int ed[MX];
bool cmp(eg X,eg Y){return X.u%k<Y.u%k;}
void add(int i,int j){
	if(i>=1) b[i].u++,b[j+1].u--;
	else b[1].u++,b[j+1].u--,b[(i+n-1)%n+1].u++;
}
signed main(){
	ios::sync_with_stdio(false); 
	cin.tie(0);cout.tie(0);
	cin>>n>>k;h=n/k;
	for(int i=1;i<=n;i++){
		cin>>w;a[w%k]++;
		b[i].u=w,b[i].id=i;
	}sort(b+1,b+1+n,cmp);
	for(int i=1;i<=n;i++) ed[b[i].u%k]=i;
	for(int i=n;i>=1;i--) b[i].u-=b[i-1].u;
	l[1]=a[0]-h;
	for(int i=1;i<k;i++) l[i]=l[i-1]-h+a[i];
	int mn=n;
	for(int i=0;i<k;i++) mn=min(mn,l[i]);
	for(int i=0;i<k;i++){l[i]-=mn;res+=l[i];}
	cout<<res<<'\n';
	int w=0;while(l[w]>a[w]) w++;
	for(int i=1;i<=k;i++){
		add(ed[w]-l[w]+1,ed[w]);
		if(!ed[(w+1)%k]) ed[(w+1)%k]=ed[w];
		w=(w+1)%k;
	}
	w=0;
	for(int i=1;i<=n;i++){
		w+=b[i].u;
		ans[b[i].id]=w;
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' '; 
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### 题意简述：

给出 $n$ 个数，以及一个数 $m$，每一次操作可以使得一个数加一，用最小次数使得这 $n$ 个数模 $m$ 之后恰好每一种余数都是 $\dfrac{n}{m}$ 个。

-----
### 解题思路：

增加数的思路肯定是要把某一些数量比较多的数挪到数量比较少的数上，那么就考虑怎样增加数使得总代价最小。

显然有，将每一个缺少的数与之前的最后一个比他小的多余的数配对可以得到最优解。

----------
然后考虑如何实现，这里有两种方法：

1. Codeforces 的官方题解上介绍了这样一种方法，用一个栈（读作栈，写作 vector）维护当前剩下的可用的数，每当遇到一个比预计值大的数就放进栈中，比预计的小则从栈中取出栈顶，没有则不取。这样一共做两遍，可以在第一遍的时候保证每一个多余的数都放进了栈中，在第二遍的时候所有的数都从栈中取出，显然是正确的。这种方法非常巧妙。

2. 但是我太菜了，想不到上面那一种方法，于是就用了一个俗一点的方法。用三个指针分别指向从前往后第一个有剩下，从前往后第一个缺的，从后往前第一个有剩下的。每一次操作之前更新这三个指针。当缺少的那一个的位置在第一个指针之后的时候，第一个指针所指向的位置就是所要求的的最近的位置；反之，如果缺少的指针指向的位置在从前往后第一个剩下的位置之前，那么从第一个剩下的位置就需要绕一圈才能到达，此时的最优位置一定是从后往前第一个剩下的位置。

这里有一个环形的概念，理解的时候需要注意。

----------
### 代码：

```
#include<cstdio>
#include<vector>
using namespace std;
long long n,a[200005],m,sz[200005],x,l1,l2,l3,ans,top[200005],pri[200005];
vector <long long> num[200005];
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		num[a[i]%m].push_back(a[i]);
		sz[a[i]%m]++;
	}
	l3=m-1;
	while(l1<m&&l2<m){
		//l1 >,->  l3>,<-      l2 <
		while(sz[l1]<=n/m&&l1<m)l1++;
		while(sz[l3]<=n/m&&l3>=0)l3--;
		while(sz[l2]>=n/m&&l2<m)l2++;
		if(l1>l3||l2>=m)break;
		if(l2>l1){
			sz[l1]--;sz[l2]++;
			ans+=(l2-l1+m)%m;
			num[l1][top[l1]]=num[l1][top[l1]]+(l2-l1+m)%m;
			top[l1]++;
		}
		else{
			sz[l3]--;sz[l2]++;
			ans+=(l2-l3+m)%m;
			num[l3][top[l3]]=num[l3][top[l3]]+(l2-l3+m)%m;
			top[l3]++;
		}
	}
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++){
		printf("%lld ",num[a[i]%m][pri[a[i]%m]++]);
	}
	return 0;
}
```




---

