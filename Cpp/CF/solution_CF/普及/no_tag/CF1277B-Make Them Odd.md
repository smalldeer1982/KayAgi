# Make Them Odd

## 题目描述

### 题意简述

有一个长度为 $n$ 的数列 $a_1,a_2,...,a_n$。

您每次可以选择任意一个偶数 $c$，将数列中等于 $c$ 的数都除以 $2$，求至少需要多少次才能把数列中的所有数都变成奇数。

## 样例 #1

### 输入

```
4
6
40 6 40 3 20 1
1
1024
4
2 4 8 16
3
3 1 7
```

### 输出

```
4
10
4
0
```

# 题解

## 作者：rainbow_cat (赞：3)

显然处理更大的数更优，对于偶数，将它们存入优先队列中，然后暴力除以二。若结果是偶数，再次加入优先队列，否则舍弃。   
每个数至多被处理 $32$ 次所以时间复杂度为 $O(n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,now,a[200010];
priority_queue<int>q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=0,now=-1;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]%2==0)q.push(a[i]);
		}
		while(q.size())
		{
			int num=q.top();
			q.pop();
//			cout<<num<<' '<<now<<'\n';
			if(num==now&&num%4==0)q.push(num/2);
			else if(now!=num)
			{
				now=num,ans++;
				if(num%4==0)q.push(num/2);
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：promise_ (赞：2)

根据题目，没有说奇数如何处理，所以我们放着奇数不管。所以我们处理偶数，考虑贪心。

我们可以每次从序列中取出最大的数（我们将大的数化成小的数后，与小的数一起修改，这样不会有多余的操作，是最优的），将与它相同的数也一并取出，然后除以 $2$ 再放回序列，直到序列里全都是奇数为止。

每次要从序列中取出最大值，还要把数放回序列，容易想到用优先队列来实现。

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1277/B)
就是给一个序列，可以选一个偶数 $k$，将序列中等于 $k$ 的数都除以 $2$，求使整个序列变为奇数的最小操作次数。

## 思路
显然，我们可以直接将偶数单独拿出来，奇数不用考虑。

如果再仔细读一下题目，它是对整个序列中等于偶数 $k$ 的数都除以 $2$，显然可以**去重。**

直接得到所有的偶数然后一一除以 $2$ 就行了。

吗？

因为除以 $2$ 后有可能除出来的数在**原本的集合内**，所以还需要加个特判。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005];
set<int> even; // 存储所有偶数（去重）
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		even.clear();
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			if (a[i] % 2 == 0) {
				even.insert(a[i]);
			}
		}
		// 将偶数从大到小排序
		vector<int> steven(even.begin(), even.end());
		sort(steven.rbegin(), steven.rend());
		int op = 0;
		for (int num : steven) {
			while (num % 2 == 0) {
				num /= 2;
				op++;
				// 如果 num 已经存在于集合中，则不需要再处理
				if (even.count(num)) {
					break;
				}
			}
		}
		cout << op << '\n';
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn \log n) $，因为 $\sum{n}$ 不超过 $2 \times 10^5$，因此可以通过本题。

---

## 作者：Fuxh_18 (赞：1)

## [题意](https://www.luogu.com.cn/problem/CF1277B) 
有一个长度为 $n$ 的数列，你每次可以选择一个偶数 $c$，把数列中所有等于 $c$ 的数除以 $2$。问几次操作能把所有的数变成奇数。
## 思路
考虑贪心。把所有偶数用一个数组（数组模拟栈）存起来，从最大的开始进行操作（因为从最大的开始除，可能一起带动其他数）。一个数除成奇数时，就从这个数组出去，直到数组为空为止。操作过程中统计次数。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+1;
int q[N],n;
int main(){
	int t;
	cin>>t;
	while(t--){ //多组数据 
		int qt=0; //指针 
		int ans=0; //答案 
		cin>>n;
		for(int i=1;i<=n;i++){
			int a;
			cin>>a;
			q[++qt]=a;
			/*
			if(a%2==0){
				q[++qt]=a;
			}
			也可以在这把已有奇数排除*/
		}
		sort(q+1,q+1+qt); //排序，使大的先操作 
		while(qt>0){ //数组不为空时  
			if(q[qt]%2==1){ //是奇数，就出去 
				qt--;
				continue;
			}
			int x=q[qt];
			q[qt]=x/2; //将偶数除以 2 
			ans++;
			for(int i=1;i<=qt;i++){ //操作其他和这个数相等的数 
				if(q[i]==x){
					q[i]/=2;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
一道黄题就完成啦。

---

## 作者：_sh1kong_ (赞：1)

[in luogu](https://www.luogu.com.cn/problem/CF1277B)

[in codeforces](https://codeforces.com/problemset/problem/1277/B)


### Solution

可以发现，对于奇数，我们可以不用管。而对于偶数，进行数次操作后，最后都会变成 $1$ 。

一种类似贪心的思路。

我们可以每次从序列中取出最大的数（我们将大的数化成小的数后，与小的数一起修改，这样不会有多余的操作，是最优的），将与它相同的数也一并取出，然后除以 $2$ 再放回序列，直到序列里全都是奇数为止。

每次要从序列中取出最大值，还要把数放回序列，容易想到用优先队列来实现。

核心代码：

```cpp
void solve()

{
	cin >> n;
	priority_queue <int> q;
	for (int i = 1; i <= n; i ++ ) 
	{
		cin >> d[i];
		q.push(d[i]);
	}
	int cnt = 0;
	while (!q.empty())
	{
		int top = q.top();
		q.pop();
		if (top % 2) continue;//奇数跳过 
		q.push(top >> 1);
		cnt ++;//操作数 + 1 
		while (!q.empty() && q.top() == top) q.pop(), q.push(top >> 1);//判断相同的数 
	}
	cout << cnt << '\n';
}
```

---

## 作者：Greenqwq (赞：0)

# 前置知识

贪心、进制、模拟。

# 思路
我们可以发现如果原数组中存在奇数的话，对我们的答案是没有影响的，因为我们不会用到它，因此我们就把原数组的奇数去掉，这样我们的新数组全是偶数了。

此时，我们不妨把这新数组的每个数都除 $2$ 直到它为奇数，然后我们统计这个偶数变成奇数的次数和变成奇数的数是什么，如果最后除完得到的奇数跟之间得到的奇数是相等的，我们就把它们取个最大值。

最后我们只需要累加答案即可。

# 代码

时间复杂度 $O(tn\log {n})$。

```
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3,"Ofast","inline")

#include<bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define int long long
#define ll __int128
#define double long double
#define lowbit(x) (x&(-x))
#define log(x) (31^__builtin_clz(x))
#define endl '\n'

typedef pair<int,int>PII;
typedef tuple<int,int,int>TIII;

const int N = 2e5+10;
const int mod = 1e9+7;
const double PI = acos(-1);
const double eps = 1e-8;

mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());//随机数

bool FileIfstream(string name){
    ifstream f(name.c_str());
    return f.good();
}

int read(){
    char c=0;
    int res=0;
    int f=1;
    while(!(c>='0'&&c<='9')){
        if(c=='-'){
            f=-f;
        }
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        res=(res<<3)+(res<<1)+c-'0';
        c=getchar();
    }
    return res*f;
}

void write(int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(char(x%10+'0'));
}

int n;
int a[N],b[N];

void solve(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>a[i];
    }

    sort(a+1,a+1+n);

    int cnt=0;

    for(int i=n;i>=1;i--){
        if(!(a[i]&1)){
            b[++cnt]=a[i];
        }
    }

    map<int,int>S;

    for(int i=1;i<=cnt;i++){
        int p=0;
        while(b[i]%2==0){
            b[i]>>=1;
            p++;
        }
        S[b[i]]=max(S[b[i]],p);
    }

    int res=0;

    for(auto [v,w]:S){
        // cout<<v<<' '<<w<<endl;
        res+=w;
    }

    cout<<res<<endl;

}

signed main(){
#ifdef GREENQWQ
    if(!FileIfstream("IO.in")){
        freopen("IO.in","w",stdout);
        return 0;
    }
    freopen("IO.in","r",stdin);
    freopen("IO.out","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)solve();

#ifdef GREENQWQ
    cerr<<fixed<<setprecision(10)<<1.0*clock()/CLOCKS_PER_SEC<<endl;
#endif
    return 0;
}
```
审核大大辛苦了！！！

---

## 作者：IAKIOI__ (赞：0)

# 前置知识

模拟、离散化。

# 思路

每遇到一个偶数就将它不断操作直至其变成奇数，每次操作前先判断它这个数是否被操作过，若没有就将这个数设为操作过且改变次数加一，最后输出统计的操作次数。

### 离散化

将需要操作的偶数离散化，因为 $10^9$ 数组开不下。

# 代码

```cpp
#include<bits/stdc++.h>
#define _ 0
using namespace std;
const int MAXN=4e5;
int t,n,a[MAXN]; 
map <int,bool> mp;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		int cnt=0;//统计修改次数 
		mp.clear();//记得清空 
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]%2==0){//若a[i]是偶数 
				while(a[i]%2==0&&!mp[a[i]]){//这个数还没被操作时 
					a[i]/=2;
					mp[a[i]*2]=1;//设为操作过
					cnt++;//操作次数加一
				}
				while(mp[a[i]]){ //将a[i]变成奇数，可要可不要 
					a[i]/=2;
				}
			}
		}
		cout<<cnt<<"\n";//输出 
	}
	return ~~(0^_^0);
}
```

---

## 作者：koukou (赞：0)

## 考察知识点：
优先队列 $+$ 贪心。

## 思路：
题目没有说到奇数，所以我们暂时不管奇数，先处理偶数，考虑贪心。

我们可以每次从序列中取出最大的数，将与它相同的数也一并取出，然后除以 $2$ 再放回序列，直到序列里全都是奇数为止，这样就不会有多余的操作，达到最优效果。

每次要从序列中取出最大值，还要把数放回序列，容易想到用优先队列来实现（因为它自动排序）。

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1277B Make Them Odd

[题目传送门](https://www.luogu.com.cn/problem/CF1277B)

## 思路

我们先看看题目：选择一个整数 $c$，将数列中等于 $c$ 的数都除以 $2$，求至少需要多少次才能把数列中的所有数都变成奇数（假设这个数为 $x$）。

我们先筛选出所有偶数，然后每次取大的偶数除以 $2$，相同的一起操作。如果最大的是奇数，那不理，弹出。很容易想到可以用优先队列来实现。（毕竟 $O(Txn \log n)$（每次排序）或 $O(Txn)$（每次查找）的情况太~~垃圾~~了，而优先队列的时间是 $O(Tx \log n)$，可以通过本题）

接下来让我们来看看优先队列如何实现。

[手写](https://www.luogu.com.cn/paste/nc4pq9l3)

#### STL

##### 定义

大根堆：
```cpp
priority_queue<int> st;
```
小根堆：
```cpp
priority_queue<int,vector<int>,greater<int> > st;
```
##### 函数

1.`top ()`

访问队头元素，只是访问。

2.`push ()`

插入元素到队尾（并排序）。

3.`pop ()`

弹出队头元素，无返回值。

4.`size ()`

返回队列内元素个数。

5.`empty ()`

队列是否为空。

这部分代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main ()
{
	cin>>t;
	while (t--)
	{
		priority_queue<int> st;
		int n,t=0;
		cin>>n;
		vector<int> a (n+1);
		for (int i=1;i<=n;i++)
		{
			cin>>a[i];
			if (!(a[i]%2)) st.push (a[i]);
		}
		while (!st.empty ())
		{
			while (!st.empty ()&&st.top ()%2==1) st.pop ();
			if (st.empty ()) break;
			int ft=st.top ();
			while (st.top ()==ft) st.pop (),st.push (ft/2);
			t++;
		}
		cout<<t<<endl;
	}
	return 0;
}
```

---

## 作者：L_shadow (赞：0)

## 前置芝士：
优先队列+贪心。
## 思路：
如果先处理大的数，它除以二之后可能会与某个偶数合并，如果先处理小的数，某个可能与它合并的数还要在处理一次，这并不是最少的操作数。

因此，先处理大的数是最优的，这就是贪心的思路。

对于某些数，它们可能需要处理多遍，结合上文的需求，使用优先队列是最合理的。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a;
int main(){
	int t;cin>>t;
	while(t--){
		priority_queue<int> q;
		int n;cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a;
			q.push(a);
		}
		int cnt=0;
		while(!q.empty()){
			int now=q.top();
			q.pop();
			if(now%2) continue;
			now/=2;
			cnt++;
			q.push(now);//重复处理
			while(q.top()==now*2) q.pop(),q.push(now);//一样的，一起处理
		}
		cout<<cnt<<endl;
	}
}
```


---

## 作者：20120511qhc (赞：0)

## 思路

题目中说要把所有的数都变成奇数，那么肯定是先处理大的，再处理小的。

因为大数降下来之后可以与小数一起处理，小数则不行。

我们可以使用优先队列维护数组中所有偶数，每次取最大的数处理即可。

## Code

```
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005];
int main(){
  for(cin >> t; t; t--){
    cin >> n;
    for(int i = 1; i <= n; i++){
      cin >> a[i];
    }
    priority_queue<int> q;
    for(int i = 1; i <= n; i++){
      if(!(a[i] % 2)) q.push(a[i]);
    }
    int cnt = 0;
    while(!q.empty()){
      int tmp = q.top();
      if(tmp % 2) {q.pop(); continue;}
      while(q.top() == tmp){
        q.pop();
        q.push(tmp / 2);
      }
      cnt++; 
    }
    cout << cnt << "\n";
  }
  return 0;
}
```


---

## 作者：gyh20 (赞：0)

贪心，从大的开始修改，这样不会有多余的修改操作。

用优先队列维护当前最大值，如果是奇数就一直弹，否则一次性弹出相同的再插入这个值/2。

代码：
```cpp
#include<cstdio>
#include<queue>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0'||v>'9')v=getchar();
	while(v>='0'&&v<='9'){
		t=(t<<3)+(t<<1)+(v^48);
		v=getchar();
	}
	return t;
}
priority_queue <int> q;
int main(){
	int t=read(),n;
	while(t--){
		n=read();
		int ans=0,tmp=0;
		while(n--){
			q.push(read());
		}
		while(!q.empty()){
			if(q.top()&1){
				q.pop();
				continue;
			}
			else{
				if(q.top()==tmp){
					q.push(q.top()/2);
					q.pop();
					continue;
				}
				else{
					++ans;
					q.push(q.top()/2);
					tmp=q.top();
					q.pop();
					}
			}
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：LCuter (赞：0)

## $\text{Description}$

给定一个长度为 $n$ 的序列，每次操作可以选择一个偶数 $c$ ，然后将序列中等于 $c$ 的值全部除以 $2$ 。问最少进行多少次操作可以让序列中的数都变成奇数。

## $\text{Solution}$

主要是考虑有没有可能一个数会被除成另一个数，从而减少操作次数。

注意到别的数一定不会被除成当前序列中最大的偶数，故我们每次取出当前序列中最大的偶数除以 $2$ 即可。

使用优先队列维护这一操作即可，注意，一定要将相同元素一起弹出。

---

## 作者：rsjw (赞：0)

~~Luogu和Codeforces对接不上了吗...~~

**一道水题，可以想到用计数的思想每次把最大的偶数除以2，再取消标记就能轻松解决**

标记用$map$

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[200010];
bool cmp(const int &a,const int &b) { return a>b; }
int main() {

	int t,n;
	scanf("%d",&t);
	while(t--) {
		int k=0;
		map<int,int> m;
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&a[i]),m[a[i]]=1;
		sort(a+1,a+n+1,cmp);
		for(int i=1; i<=n; i++) {
			if((a[i]&1)==0&&m[a[i]]) {
				while((a[i]&1)==0) {
					m[a[i]]=0;
					a[i]>>=1;
					k++;
				}
			}
		}
		printf("%d\n",k);
	}
	return 0;
}

```

---

