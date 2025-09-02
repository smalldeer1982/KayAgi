# [CCC 2007] Snowflake Snow Snowflakes

## 题目描述

你可能听说过没有两片雪花是相同的。你的任务是编写一个程序来确定这是否真的是正确的。你的程序将读取关于一组雪花的信息，并搜索可能相同的一对雪花。每片雪花有六条“角”。对于每片雪花，你的程序将提供每条角的长度测量。任何一对长度对应的角相同的雪花都应该被你的程序标记为可能相同。

## 样例 #1

### 输入

```
2 
1 2 3 4 5 6 
4 3 2 1 6 5```

### 输出

```
Twin snowflakes found.```

# 题解

## 作者：NTT__int128 (赞：11)

# P10467 [CCC 2007] Snowflake Snow Snowflakes题解
直接上 ```STL```。

开一个 ```map``` 记录每种雪花六角长度序列是否存在，若存在，则答案为 ```No two snowflakes are alike.```，否则，答案为 ```Twin snowflakes found.```。

本蒟蒻不会用高级的东西，只好用套了 $5$ 重的 ```pair``` 来维护序列。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std ;
map <pair <int , pair <int , pair <int , pair <int , pair <int , int> > > > > , bool> mp ;
int n , a[7] , b[7] ;
pair <int , pair <int , pair <int , pair <int , pair <int , int> > > > > make()
{
	return {b[1] , {b[2] , {b[3] , {b[4] , {b[5] , b[6]}}}}} ;
}
int main()
{
	cin >> n ;
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= 6 ; j++)	cin >> a[j] , b[j] = a[j] ;
		if(mp.count(make()))
		{
			cout << "Twin snowflakes found." ;
			return 0 ;
		}
		for(int j = 1 ; j <= 6 ; j++)
		{
			int s = 0 ;
			for(int k = j ; k <= 6 ; k++)	b[++s] = a[k] ;
			for(int k = 1 ; k < j ; k++)	b[++s] = a[k] ;
			mp[make()] = 1 ;
			s = 0 ;
			for(int k = j ; k >= 1 ; k--)	b[++s] = a[k] ;
			for(int k = 6 ; k > j ; k--)	b[++s] = a[k] ;
			mp[make()] = 1 ;
		}
	}
	cout << "No two snowflakes are alike." ;
	return 0 ;
}
```

---

## 作者：forever_nope (赞：9)

考虑到可以哈希处理。

设计哈希函数，

$$
H(a)=\left(\sum_{i=1}^6a_i+\prod_{i=1}^6a_i\right)\bmod p
$$

取 $p$ 为一大质数，例如 `0xccf54188 - 1`。

这样，如果两片相同的雪花，其散列值是相同的。

然后设计判断取等的函数，直接模拟即可。

这里使用 `unordered_map` + 手写哈希实现，

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll P = 0xccf54188 - 1;

#define int ll

struct emm {
    array<int, 6> s;
    friend bool operator ==(const emm &a, const emm &b) {
    	auto s = b.s;
    	for (int t = 0; t < 6; ++t) {
    		if (s == a.s) return 1;
    		int e = s[0];
    		for (int i = 0; i < 5; ++i) s[i] = s[i + 1];
    		s[5] = e;
		}
		reverse(s.begin(), s.end());
    	for (int t = 0; t < 6; ++t) {
    		if (s == a.s) return 1;
    		int e = s[0];
    		for (int i = 0; i < 5; ++i) s[i] = s[i + 1];
    		s[5] = e;
		}
		return 0;
	}
};

struct my_hash {
    ll operator ()(const emm a) const {
        ll r = 0;
        for (int i : a.s) r = (r + i) % P;
        ll e = 1;
        for (int i : a.s) e = e * i % P;
        return (r + e) % P;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n; emm t;
    unordered_set<emm, my_hash> app;
    for (int i = 0; i < n; ++i) {
        for (int &i : t.s) cin >> i;
        if (app.count(t)) puts("Twin snowflakes found."), exit(0);
        app.insert(t);
    } return puts("No two snowflakes are alike."), 0;
}
```

---

## 作者：wmrqwq (赞：3)

# 题目链接

[P10467 [CCC 2007] Snowflake Snow Snowflakes](https://www.luogu.com.cn/problem/P10467)

# 解题思路

字符串哈希板子题。

思路就是我们给每个数列的所有排列都哈希一个值，然后判断是否有不同的数列的哈希值相同，如果有，就输出 `Twin snowflakes found.`，否则就输出 `No two snowflakes are alike.`。

# 参考代码

这里使用双哈希。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
//#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll Base1=666,Base2=223,Base3=771;
ll mod1=1e9+7,mod2=998244353,mod3=1e9+9;
map<ll,map<ll,ll>>mp;
ll n,a[10];
ll nxt(ll x){
	if(x==6)
		return 1;
	return x+1;
}
ll lst(ll x){
	if(x==1)
		return 6;
	return x-1;
}
void dfs1(ll st){
	ll L=st,sum1=0,sum2=0,sum3=0;
	forl(i,1,6){
		sum1*=Base1,sum2*=Base2,sum3*=Base3;
		sum1+=a[L],sum2+=a[L],sum3+=a[L];
		L=nxt(L);
	}
	if(mp[sum1][sum2])
	{
		cout<<"Twin snowflakes found.\n";
		exit(0);
	}
	mp[sum1][sum2]=1;
}
void dfs2(ll st){
	ll L=st,sum1=0,sum2=0,sum3=0;
	forl(i,1,6){
		sum1*=Base1,sum2*=Base2,sum3*=Base3;
		sum1+=a[L],sum2+=a[L],sum3+=a[L];
		L=lst(L);
	}
	if(mp[sum1][sum2])
	{
		cout<<"Twin snowflakes found.\n";
		exit(0);
	}
	mp[sum1][sum2]=1;
}
void solve()
{
	cin>>n;
	forl(i,1,n)
	{
		forl(j,1,6)
			cin>>a[j];
		forl(j,1,6)
			dfs1(j),dfs2(j);
	}
	cout<<"No two snowflakes are alike.\n";
}
int main()
{
	IOS;
	t=1;
//	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：abc1234shi (赞：3)

我们给每个数列都哈希一个值，然后判断有没有数列的哈希值相同，如果有，就输出  `Twin snowflakes found.`，否则就输出 `No two snowflakes are alike.`。这里使用         `unordered_map` + 手写哈希实现。那么什么是哈希值呢？
哈希值是把任意长度的输入（又叫做预映射 pre-image ）通过散列算法变换成固定长度的输出，该输出就是散列值。这种转换是一种压缩映射，也就是，散列值的空间通常远小于输入的空间，不同的输入可能会散列成相同的输出，所以不可能从散列值来确定唯一的输入值。简单的说就是一种将任意长度的消息压缩到某一固定长度的消息摘要的函数。手写哈希代码如下：
     
    int hash(string& key) {
    unsigned int hash1 = 0;
    for (char ch : key) {
        hash1 = (hash1 << 5) + ch; //将每个字符的ASCII码值左移5位，然后相加 
    }
    return hash1;
    }
这个哈希函数使用了简单的乘法和位移操作来计算字符串的哈希值。

---

## 作者：Stars_visitor_tyw (赞：3)

## P10467 [CCC 2007] Snowflake Snow Snowflakes 题解
### 分析
排序不是正解。我们采用单哈希，这样不容易超时。

给每个序列按照处理字符串哈希值的方式处理数列的哈希值，一边输入一边判断，前后分别找，若这个数列的两个哈希值都有同一片雪花对应上，输出 `Twin snowflakes found.`。最后若程序还没有结束，输出 `No two snowflakes are alike.`。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[7];
map<long long,long long> mp;
long long hs, pw, hs1;
const long long base=131, base1=191;
void hadsh(long long pos)
{
    hs=hs1=0;
	for(register int i=1;i<=6;i++)
	{
		hs=hs*base+a[pos];
// 		hs1=hs1*base1+a[pos];
		pw=pw*base;
		if(pos!=6)
		{
		    pos=pos+1;
		}
		else pos=1;
	}
}
void hadsh1(long long pos)
{
    hs=hs1=0;
	for(register long long i=1;i<=6;i++)
	{
		hs=hs*base+a[pos];
		pw=pw*base;
// 		hs1=hs1*base1+a[pos];
		if(pos!=1)
		{
		    pos-=1;
		}
		else pos=6;
	}
}
void work(long long x)
{
    hadsh(x);
    if(mp[hs])
    {
		cout<<"Twin snowflakes found.";
		exit(0);
    }
    mp[hs]=1;
}
void work1(long long x)
{
    hadsh1(x);
    if(mp[hs])
    {
		cout<<"Twin snowflakes found.";
		exit(0);
    }
    mp[hs]=1;
}
int n;
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(register long long i=1;i<=n;i++)
    {
        for(register long long j=1;j<=6;j++)
        {
            cin>>a[j];
        }
        for(register long long j=1;j<=6;j++)
        {
            work(j),work1(j);
        }
    }
    cout<<"No two snowflakes are alike.";
}
```

---

## 作者：AAA404 (赞：2)

哈希题。

提供一种和蓝书上不同的做法：由于雪花“角”的顺序不区分，容易想到用相乘的关系来刻画。

为了避免哈希冲突，想到根据唯一分解定理，采用质数哈希。

具体的，对于一个雪花数字序列为 $\{a\}$，哈希值为：

$$\prod_i prime_{a_i}$$

其中 $prime_i$ 表示第 $i$ 个质数。

值域较大，需要离散化，最终需要质数个数上界在 $6\times 10^5$，筛法筛到 $10^7$ 内即可。

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5,M=2e7+5;
#define ull unsigned long long
map<ull,int>ma;
int n,a[N][10],prime[N],tot;
bool np[M];
ull s[N];
vector<int>v;
void work(int x)
{
    np[1]=1;
    for(int i=2;i<=x;i++)
    {
        if(!np[i])
        {
            prime[++tot]=i;
            for(int j=2;j*i<=x;j++)
            {
                np[j*i]=1;
            }
        }
    }
    return;
}
int main()
{
	clock_t c1=clock();
#ifdef LOCAL
 	freopen("1.in","r",stdin);
 	freopen("1.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
 	cin.tie(0);cout.tie(0);
    work(1e7);
	cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=6;j++)
        {
            cin>>a[i][j];
            v.push_back(a[i][j]);
        }
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++)
    {
        s[i]=1;
        for(int j=1;j<=6;j++)
        {
            a[i][j]=lower_bound(v.begin(),v.end(),a[i][j])-v.begin()+1;
            s[i]*=1ull*prime[a[i][j]];
        }
        if(ma[s[i]])
        {
            cout<<"Twin snowflakes found.";
            return 0;
        }
        ma[s[i]]++;
    }
    cout<<"No two snowflakes are alike.";
#ifdef LOCAL
	cerr<<"Time used:"<<clock()-c1<<"ms";
#endif
 	return 0;
}
```

---

## 作者：smydahaoren (赞：2)

**题目思路：**

使用哈希映射实现雪花的储存和判断。

需要注意的是：雪花可以顺时针或者逆时针旋转。那么需要把顺时针和逆时针的哈希值（可以用自然溢出）同时存在 ```unordered_map``` 中。同时需要注意的是在储存顺时针和逆时针的哈希值过程中，要防止顺时针或者逆时针的结果是相等的，因此可以再开一个 ```unordered_map``` 解决问题。

**AC 代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000001;
long long n,a[6],b[6];
unordered_map<long long,long long> hs;
void swap(){
	for(int i=0;i<6;i++)
	b[i]=a[5-i];
	return;
}
int main(){
	//freopen(" ","r",stdin);
	//freopen(" ","w",stdout);
	cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<6;j++) cin>>a[j];
		unordered_map<long long,long long> hs1;
		for(int j=0;j<6;j++) {
			long long ans=0;
			for(int l=j;l<6+j;l++)
				ans=ans*N+a[l%6];
			hs1[ans]=1;
		}
		swap();
		for(int j=0;j<6;j++) {
			long long ans=0;
			for(int l=j;l<6+j;l++)
				ans=ans*N+b[l%6];
			hs1[ans]=1;
		}
		for(unordered_map<long long,long long>::iterator i=hs1.begin();i!=hs1.end();i++){
			if(hs[((*i).first)]==1){
			cout<<"Twin snowflakes found.";
			return 0;
			}
			else 
			hs[((*i).first)]=1;
		}
	}
//	for(int i=0;i<6;i++) cout<<a[i]<<" ";
//	cout<<"\n";
//	for(int i=0;i<6;i++) cout<<b[i]<<" ";
//	for(unordered_map<long long,long long>::iterator i=hs.begin();i!=hs.end();i++)
//	cout<<((*i).first)<<endl;
	cout<<"No two snowflakes are alike.";
	return 0;
}

```

---

## 作者：zren6ing (赞：1)

# 思路

其实和映射哈希值差不多，但是换了一个通俗的说法。我们定义“标准化”为通过生成所有旋转和映射，其中字典序最小的。

对于一片雪花，他顺时针和逆时针的标准化形式是一样的。意思就好比：一个戴眼镜的男生和一个带帽子的男生，关键要比较他们的区别，肯定是先确定他们都是男生。根据这个思路我们使用一个 ```set``` 来存储标准化后的雪花形式。```set``` 用于快速检测是否有重复的雪花。那么，如果有相同标准化形式则说明找到了一对可能相同的雪花，输出 ```Twin snowflakes found.```。否则，将当前雪花的标准化形式插入到 ```set``` 中。如果到最后都没找到都没有发现重复的标准化形式的化，输出 ```No two snowflakes are alike.```。（注意：两个英文句子后面应该有一个句号点）。

## 整体步骤梳理

1. **标准化雪花**：

- 对每片雪花枚举出所有可能的旋转，并生成这些旋转的映射形式。
- 找到这些旋转和映射中字典序最小的表示，作为该雪花的标准化形式。

2. **查重**：

- 使用 ```set``` 检查当前雪花的标准化形式是否已经存在。
- 如果存在，则说明找到了一对可能相同的雪花。
- 如果不存在，将当前雪花的标准化形式插入到 ```set``` 中。

3. **输出**：

- 如果遍历完所有雪花都没有发现重复的标准化形式，就输出 ```No two snowflakes are alike```。

### tips：

- **效率**：```set``` 查复效率较高，能处理雪花数量较大的情况。~~我是绝对不会告诉你们我是因为不会 unodered_map 而写 set 做法的~~。

#### 代码（注释在后面）

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main() {    
    cin >> n;
    // 使用 set 来存储雪花的标准化形式
    set < array < int, 6 > > S;    
    for (int i = 1; i <= n; ++i) {
        int sf[6];
        for (int j = 0; j < 6; ++j) {
            cin >> sf[j]; 
        }
        int a[6];
        memset(a,0x3f,sizeof(a)); // 初始化数组 a 为一个非常大的数，用于存储当前雪花的标准化形式
        for (int i = 0; i < 6; ++i) {
            int dx[6], dy[6];
            for (int j = 0; j < 6; ++j) {
                dx[j] = sf[(i + j) % 6]; // 旋转当前的雪花
                dy[j] = sf[(i + j) % 6]; // 旋转当前的雪花（用于映射）
            }
            reverse(dy, dy + 6); // 当前旋转雪花的映射
            bool visx = 0;
            bool visy = 0;
            // 比较旋转后的雪花
            for (int k = 0; k < 6; ++k) {
                if (dx[k] < a[k]) {
                    visx = true;
                    break;
                } else if (dx[k] > a[k]) {
                    break;
                }
            }
            if (visx) {
                copy(dx, dx + 6, a); // 更新 a 为当前最小的旋转形式
            }
            // 比较映射的雪花
            for (int k = 0; k < 6; ++k) {
                if (dy[k] < a[k]) {
                    visy = true;
                    break;
                } else if (dy[k] > a[k]) {
                    break;
                }
            }
            if (visy) {
                copy(dy, dy + 6, a); // 更新 a 为当前最小的映射形式
            }
        }
        array < int, 6 > s;
        copy(a, a + 6, s.begin()); // 将标准化形式复制到array 中
        if (S.count(s)) {
            cout << "Twin snowflakes found.\n";
            return 0; 
        }
        S.insert(s); // 将当前雪花的标准化形式插入到集合中
    }
    cout << "No two snowflakes are alike.\n"; 
    return 0;
}
```

---

## 作者：__delta_epsilon__ (赞：1)

### 题目大意

输入 $n$ 片六角雪花各角长度的信息，请问是否存在两片一样的雪花？雪花可旋转和翻折。

### 解题思路

对于每片雪花，将其经过旋转、翻折后的所有形态中字典序最小的存储在 map 中，然后判断有没有重复的即可。

看到别的题解都用哈希，但我比较懒，所以不用。

我们知道 STL 中有一个东西叫做 tuple，中文名叫元组，和结构体类似，但不需要自己写重载运算符，非常的优秀。

简单介绍一下用法：

建立一个成员数为 $n$，各成员类型为 $T_i$ 的 tuple。

```cpp
tuple<T1, T2, ..., Tn> t;
```

判断两个 tuple 是否相等。

```cpp
t1 == t2
```

按照判断两个 tuple 的大小。（`relop` 为关系运算符）

```cpp
t1 relop t2
```

调用 tuple 中第 $i$ 个成员。

```cpp
get<i>(t)
```

好了，以上为基础内容，我们开始写代码。

首先，一片雪花经过翻折和旋转最多只有 $12$ 种状态，设原雪花为 $123456$，则不难发现这 $12$ 种状态分别为：

$$\begin{array}{c}123456&234561&345612&456123\\561234&612345&654321&543216\\432165&321654&216543&165432\end{array}$$

对于每一片雪花，我们可以手动求出这 $12$ 种状态并找到最小的一组。

我们用函数 `Change()` 来计算结果：

```cpp
tuple<int, int, int, int, int, int> Change(tuple<int, int, int, int, int, int> x) {
	tuple<int, int, int, int, int, int> t[13];
	int g[6] = {get<0>(x), get<1>(x), get<2>(x), get<3>(x), get<4>(x), get<5>(x)};
	t[0] = make_tuple(g[0], g[1], g[2], g[3], g[4], g[5]);
	t[1] = make_tuple(g[1], g[2], g[3], g[4], g[5], g[0]);
	t[2] = make_tuple(g[2], g[3], g[4], g[5], g[0], g[1]);
	t[3] = make_tuple(g[3], g[4], g[5], g[0], g[1], g[2]);
	t[4] = make_tuple(g[4], g[5], g[0], g[1], g[2], g[3]);
	t[5] = make_tuple(g[5], g[0], g[1], g[2], g[3], g[4]);
	
	t[ 6] = make_tuple(g[5], g[4], g[3], g[2], g[1], g[0]);
	t[ 7] = make_tuple(g[4], g[3], g[2], g[1], g[0], g[5]);
	t[ 8] = make_tuple(g[3], g[2], g[1], g[0], g[5], g[4]);
	t[ 9] = make_tuple(g[2], g[1], g[0], g[5], g[4], g[3]);
	t[10] = make_tuple(g[1], g[0], g[5], g[4], g[3], g[2]);
	t[11] = make_tuple(g[0], g[5], g[4], g[3], g[2], g[1]);
	
	t[12] = make_tuple(INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX);
	for(int i = 0; i <= 11; i++)
		if(t[i] < t[12])
			t[12] = t[i];
	return t[12];
}
```

虽然这很原始，但效果还行。

接着就是主程序部分，我们对于每一组输入，只需要调用 `Change()` 并存入 map 中判断即可。

```
signed main(){
	cin >> n;
	while(n--) {
		tuple<int, int, int, int, int, int> tp;
		int _[6]; for(int i = 0; i <= 5; i++) cin >> _[i];
		tp = make_tuple(_[0], _[1], _[2], _[3], _[4], _[5]);
		auto k = Change(tp);
		if(!mp[k]) mp[k] = true;
		else puts("Twin snowflakes found."), exit(0);
	}
	puts("No two snowflakes are alike.");
	return 0;
}
```

完整程序就不放了，时间复杂度为 $O(12n)$。

---

## 作者：sillation (赞：0)

### [题目通道](https://www.luogu.com.cn/problem/P10467)
---------------
### 思路：
使用哈希映射加 `unordered_map` 实现（`map` 会超时）。开一个数组存入数值，经过把每个数字顺时针和逆时针都映射一遍，如果在 `map` 有映射值相同的。输出 `Twin snowflakes found.`。如果等到输入完每一次描述后都未找到相同的，输出 `No two snowflakes are alike.`。

核心代码：
```cpp
void ha(long long x){//顺时针
	ans=0;
	for(int i=1;i<=6;i++){
		ans=ans*1l+s[x];
		if(x!=6) x+=1;
		else x=1;
	}
}
void ha1(long long x){//逆时针
	ans=0;
	for(int i=1;i<=6;i++){
		ans=ans*1l+s[x];
		if(x!=1) x-=1;
		else x=6;
	}
}
```


### 注意：

- 输入输出要优化。
- 请用 long long。

### [代码](https://www.luogu.com.cn/paste/8h0752yu)

---

