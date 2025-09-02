# [COCI 2010/2011 #3] ZNANSTVENIK

## 题目描述

给定一个 $r\times c$ 的字母矩阵。你需要从这个矩阵的第一行开始，删除尽量多的行， 且保证矩阵任意两列都不相等。输出最多可以删除的行数。

- 两列相等定义为在这两列中同一行的字母都相等。
- 初始的矩阵中任意两列都是不相等的。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证 $2\le r,c\le 1000$。

#### 说明

**题目译自 [COCI2010-2011](https://hsin.hr/coci/archive/2010_2011/) [CONTEST #3](https://hsin.hr/coci/archive/2010_2011/contest3_tasks.pdf) *T4 ZNANSTVENIK***。

## 样例 #1

### 输入

```
2 6
dobarz
adatak```

### 输出

```
0```

## 样例 #2

### 输入

```
3 4
alfa
beta
zeta```

### 输出

```
2```

## 样例 #3

### 输入

```
4 6
mrvica
mrvica
marica
mateja```

### 输出

```
1```

# 题解

## 作者：cfkk (赞：4)

这道题可以用哈希来做，因为 n 和 m 的范围比较大，还需要二分和前缀和寻找答案。

但是输入是是行在前，求哈希是要列在前，需要转换。

求哈希需要用到 Ascii 码，但是 Ascii 中有很多浪费的元素，所以将 Ascii 的 256 为改成 131 位是容错率最小的。

所以哈希数组的转换公式为：

$has_{i,j}$ = $has_{i,j-1}$ × 131+ $c_{i,j}$

与大家不同的是，我用的是单哈希，别人是双哈希。

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[5005][5005];//原方阵
int n,m;
unsigned long long has[5005][5005],data[5005];//防止爆内存
bool check(int mid)
{
    for(int i=1;i<=m;i++){data[i]=has[i][n-mid];}//把哈希转换到每一列
    sort(data+1,data+m+1);//从小到大排序
    for(int i=2;i<=m;i++)
    {
        if(data[i]==data[i-1]){return 0;}//排序后如果相邻两个相同，就不是正确答案
    }
    return 1;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++){cin>>c[i][j];}
    }
    for(int j=1;j<=m;j++)//因为是判断列，所以把列放在前面
    {
        for(int i=n;i>0;i--)
        {
            has[j][n-i+1]=has[j][n-i]*131+c[i][j];//哈希转换
        }
    }
    int l=0,r=n-1;
    while(l<r)//二分
    {
        int mid=(l+r+1)/2;//如果是(l+r)/2会死循环
        if(check(mid)){l=mid;}//判断check
        else{r=mid-1;}
    }
    cout<<l<<endl;
    return 0;
}

```

---

## 作者：lyas145 (赞：2)

题目在[这里](https://www.luogu.com.cn/problem/P6502)  
### 解题思路
注意是从**第一行**开始删，所以可以倒过来想，就成了从最后一行开始，最少必须加几行，然后就可以倒序来解决。  
这道题也可以不用哈希，用 map 就行~~主要是因为我懒~~。倒序求出每一列，用 map 判重，如果搜完一整行都没有任意两列相等，那么**这一行的行数减一**就是答案（为什么呢？下一段有解释），并且也没必要继续往前求了，因为是倒序处理的，所以求出满足条件的第一行就可以求出最多可以删多少行。  
为什么满足条件的第一行的行数减一是答案？因为这一行要么是最后一行，要么后面那几行任意两列有相等的。如果是最后一行，那么起码得保留一行，因为全删去就不是矩阵了；如果是第二种情况，那么必须保留这一行，因为这一行后面都不满足条件，所以必须保留这一行来保证删掉前面几行后剩下的几行任意两列都不相等。  
代码里也有一些注释。  
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int n,m;
string s[N];
char a[N][N];
map<string,bool> mp;
void _() {
	for (int i=n;i>=1;i--) {
		bool f=0;
		mp.clear();   
/*清空map是因为之前存进map的那几列没用了，没用是因为那几列
的长度一定比接下来求的列的长度短，放在map里还浪费时间。*/
		for (int j=1;j<=m;j++) {
			s[j]+=a[i][j];
			if (mp[s[j]]) {f=1;}
//这里千万不要break，不然后面那几列都缺字母。(我因此爆0了好多次)
			else {mp[s[j]]=1;}
		}
		if (!f) {printf("%d\n",i-1);return ;}
//没有任意两列相等，输出答案。
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {scanf("%s",a[i]+1);}
	_();
	return 0;
}
```
本人第一次写题解，有不足之处请谅解，还有辛苦审核了。

---

## 作者：封禁用户 (赞：2)

# 思路

倒序考虑，即从最后一行开始加，直到有一行没有相同。

其实不需要用哈希。

记录目前每个列的字符串，使用 unordered_map 判重，如果无重复则输出。

每次循环将这一行每一列增加的一个字母加进字符串中。

```cpp
#include<bits/stdc++.h>
#define sd std::
#define ll long long
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
#define il inline 
#define umap(x,y) sd unordered_map<x,y>
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
const int N=1e3+10;
int n,m;
char a[N][N];
sd string s[N];//记录存进去的列的字符串 
umap(sd string,int) mp;
il void solve()
{
	F(i,1,m) s[i]="";
	n=read(),m=read();
	F(i,1,n) scanf("%s",a[i]+1);
	f(i,n,1)//倒序处理 
	{
		mp.clear();
		int flag=0;
		F(j,1,m)
		{
			s[j]+=a[i][j];
			if(mp[s[j]]) flag=1;//有相同 
			mp[s[j]]++;
		}
		if(!flag) return void(print(i-1));
	}
}
int main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：SunsetLake (赞：2)

其实直接模拟就好了。

因为要从第一行开始依次往下删，所以从小到大枚举行，看这行删完是否合法。如果不合法了，就输出答案并结束程序。然后我们就要思考如何判断当前矩阵是否合法。

一个暴力的想法是把下面的每一列字符串都表示出来，看他们之中有没有不同的。但是这样做是 $\mathcal{O(n^2m)}$ 的，不能通过。可以发现主要是在把下面的字符串表示出来时耗费了大量时间，怎么优化呢？我们可以使用字符串哈希。

先预处理出每一列的哈希值，当我们把前 $i$ 行删掉过后，每一列就剩下 $i+1$ 到 $n$ 行了，这时它的哈希值便是 $h_{n,j}-h_{i,j} \times p_{n-i}$，其中 $p_i$ 是我们选的 $base$ 值的 $i$ 次方。这样我们就可以快速地判断是否有两列相同了，只需要看哈希值是否有重复，使用 map 即可。

如果怕被卡哈希，可以写双哈，也可以找一些奇怪的模数和 $base$，就能过辣。

复杂度 $\mathcal{O(nm \log n)}$。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char c[1005][1005];
const int mod=1e9+7;
const ll base=199;
ll h[1005][1005],p[1005];
int n,m,ans; 
map<ll,int>mp;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			cin>>c[i][j];
	p[0]=1;		
	for(int i=1;i<=n;++i)p[i]=(p[i-1]*base)%mod;
	for(int j=1;j<=m;++j){
		for(int i=1;i<=n;++i)
			h[i][j]=(h[i-1][j]*base+c[i][j]-'a')%mod;//预处理哈希数组
	for(int i=1;i<=n;++i){
		bool f=0;
		for(int j=1;j<=m;++j){
			ll now=(h[n][j]-h[i][j]*p[n-i]%mod+mod)%mod;
			if(mp[now]){//判断是否有两列相等
				f=1;
				break;
			}
			mp[now]=1;
		}
		if(!f)ans++;
		else return cout<<ans,0;
		mp.clear();
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：yydfj (赞：1)

这是本蒟蒻第三十七次写的题解，如有错误点请好心指出！

## 问题简述

有一个大小为 $n \times m$ 的字母矩阵，你需要删除矩阵的前 $k(0 \le k<n)$ 行使得当前矩阵任意两列不相同，求 $k$ 的最大值。

## 解法综述

显然直接一个字母一个字母地比较每一列是否相同的做法不够优美，考虑用哈希预处理出每一列字符串的所有后缀，不同于其他题解的自然溢出哈希和双哈希，这里用单模数哈希也是可以的。

考虑从大到小枚举 $k$ 的值，用 unordered_map 判断每一列第 $k+1$ 到第 $n$ 个字母是否有重，若有重则缩小 $k$ 的值，否则输出答案 $k$。

发现我们可以边枚举 $k$ 的值边给每一列第 $k+1$ 到第 $n$ 个字母判重，另外，由于哈希和判重的操作时间开销较小，可以不用二分答案。

## 代码描述

```cpp
#include<cstdio>
#include<unordered_map>
using namespace std;
typedef long long ll;
const ll base=233,mod=1e9+7;
char s[1005][1005];
ll n,m,hx[1005];
bool check(ll x)
{
	unordered_map<ll,bool> mp;
	for(int i=1;i<=m;i++)
	if(!mp.count(hx[i])) mp[hx[i]]=1;//unordered_map判断每一列第k+1到第n个字母是否有重
	else return 0;
	return 1;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	for(int i=n;i>=0;i--)//考虑从大到小枚举k的值，发现我们可以边枚举k的值边给每一列第k+1到第n个字母判重，可以不用二分答案
	{
		if(check(i))
		{
			printf("%d",i);
			break;
		}
		for(int j=1;j<=m;j++) hx[j]=(hx[j]*base+s[i][j]-'a')%mod;//用单模数哈希也是可以的
	}
	return 0;
}
```

---

## 作者：lnwhl (赞：1)

# P6502 [COCI2010-2011#3] ZNANSTVENIK 题解
## 题目描述
给定一个 $r \times c$ 的字母矩阵。你需要从这个矩阵的第一行开始，删除尽量多的行， 且保证矩阵任意两列都不相等。输出最多可以删除的行数。

- 两列相等定义为在这两列中同一行的字母都相等。
- 初始的矩阵中任意两列都是不相等的。

## 思路
有许多人用的是二分答案，虽然可以通过本题数据，但复杂度不对（```strcmp``` 函数复杂度是 $O(n)$，总复杂度是 $O(n^3 \log n)$)。

这里给出一种二分答案+哈希的解法。把每列的字符串哈希成一个数。二分判断时用的是排序后相邻的是否相等。复杂度 $O(n^2)$。跑得飞快。具体见代码。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned long long has[1005][1005];//哈希数组，自然溢出
char ch[1005][1005];
int r,c,data[1005];
inline bool check(int x)//判断是否可行
{
    for(int i=1;i<=c;i++)data[i]=has[i][r-x];
    sort(data+1,data+c+1);//排序
    for(int i=2;i<=c;i++)//只能是排序后相邻的相等
    {
	if(data[i]==data[i-1])return 0;
    }
    return 1;
}
int main()
{
    cin>>r>>c;
    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
           cin>>ch[i][j];
        }
    }
    for(int j=1;j<=c;j++)
    {
        for(int i=r;i>=1;i--)
        {
            has[j][r-i+1]=has[j][r-i]*131+ch[i][j]-'a';//哈希
        }
    }
    int low=0,high=r-1,mid,ans=0;
    while(low<high)//二分答案
    {
        mid=(low+high+1)/2;
        if(check(mid))low=mid;
        else high=mid-1;
    }
    cout<<low<<endl;
    return 0;
}
```
$\texttt{By whl}$

$\texttt{2021.12.11}$

---

## 作者：yx666 (赞：0)

# P6502 ZNANSTVENIK 题解
## Part 1：题意
### Part 1.1：题干
#### Part 1.1.1：题目描述
给定一个 $r\times c$ 的字母矩阵。你需要从这个矩阵的第一行开始，删除尽量多的行，且保证矩阵任意两列都不相等。输出最多可以删除的行数。

- 两列相等定义为在这两列中同一行的字母都相等。
- 初始的矩阵中任意两列都是不相等的。

#### Part 1.1.2：数据规模与约定
- 对于 $100\%$ 的数据，保证 $2\le r,c\le 1000$。

- 保证矩阵中的字母皆为小写字母。

- 保证矩阵刚开始时任意两列都不相等。

### Part 1.2：样例解释
最开始没读懂题意，对照样例才理解出来。

举例：

**input**：

```
4 3
acb
acb
caa
acc
```

**output**：

```
1
```

**解释**：

- 刚开始时：

| 第一列 | 第二列 | 第三列 |
| :----------: | :----------: | :----------: |
| a | c | b |
| a | c | b |
| c | a | a |
| a | c | c |

- 删去第一行后：

| 第一列 | 第二列 | 第三列 |
| :----------: | :----------: | :----------: |
| a | c | b |
| c | a | a |
| a | c | c |

- 删去第二行后：

| 第一列 | 第二列 | 第三列 |
| :----------: | :----------: | :----------: |
| c | a | a |
| a | c | c |

此时第二列与第三列相同，所以只能删去 $1$ 列。

## Part 2：解法
### Part 2.1：思路
转换一下思维：删去的行数最多的时候，就是剩下的再减一行，就会存在相同列的时候。

所以题目相当于是在求：从最后一行选起，最少能选 $t$ 行连续的行使得这 $t$ 行恰好没有相同的列。

最后的答案是 $r-t$，一共 $r$ 行，留下来了 $t$ 行，就删去了 $r-t$ 行。

### Part 2.2：实现
从最后一行选起，就要逆序枚举，每次判断有没有相同的列就行。

为了使时间复杂度更优，判断相同列时，采用字符串哈希，记录每一列。

用 `unordered_set<string>`，贪码量少。

## Part 3：代码
$str_i$ 表示读入的第 $i+1$ 行，$s_i$ 表示逆序的第 $i+1$ 列。代码里的下标从 $0$ 开始。

坑点是更新每一列的地方，不能直接把它扔进下面的循环里，不然后面的 `break` 之后就更新漏了，后面的就要出问题。

每次记得清空 `mp`。

``` cpp
#include<bits/stdc++.h>
using namespace std;

#define R 1024
#define C 1024
#define pii pair<int,int>

int r,c;
vector<string> str,s;
unordered_set<string>mp;
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	
	cin>>r>>c;
	
	str.resize(r);
	s.resize(c);
	
	for(int i=0;i<r;++i){
		cin>>str[i];
	}
	
	for(int i=r-1;i>=0;--i){
		mp.clear();
		bool flag=1;	// 是否无重复
		
		for(int j=0;j<c;++j)
			s[j].push_back(str[i][j]);	// 更新现在的每一列
		
		for(int j=0;j<c;++j){
			if(mp.count(s[j])){			// 有重复的，不是最优解
				flag=0;
				break;
			}
			
			mp.insert(s[j]);
		}
		
		if(flag){
			cout<<i;
			return 0;
		}
	}
	
	cout<<"Orz";
	return 0;
}
```

---

## 作者：be_RISK (赞：0)

## 题意
**此题题意还算清晰，不再赘述。**

## 思路
~~这题好水啊！~~\
首先，这一题在题面中写了字符串判相等，而且次数较多，所以不难想到使用 map。

其次，由于 $2\le r,c,\le 1000$，所以可以暴力的去遍历并增加每一列的字符并判重。

再次，如果当前的字符串不能再删了，那么后面的也就一定不能删了，所以我们可以从后往前枚举。

最次，一定要在枚举的时候清空 map，~~不然会 MLE~~。

## code
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,m;
char a[N][N];
map<string,int>mp;map
string s[N];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i]+1;
	for(int i=n;i>=1;i--){//倒序枚举
		mp.clear();//清空map！！！
		bool f=1;
		for(int j=1;j<=m;j++){
			s[j]+=a[i][j];
			if(mp[s[j]])f=0;//判重
			mp[s[j]]++;
		}if(f)return cout<<i-1<<endl,0;//输出
	}puts("0");//咩得
	return 0;
}//~*完结撒花*~
```

---

## 作者：Z_AuTwT (赞：0)

~~水黄一道~~

## 题意

从最前面开始一行一行删除，问最多可以删除多少行且删除完后没有任何两列相同。

## 思路

可以从后往前枚举每一行，拿一个 `string` 数组记录从后面开始到现在的每列，最后用 `map` 判一下重就可以了。

## CODE

```c++
#include<bits/stdc++.h>
using namespace std;
char arr[1010][1010];
string s[1010];
map<string,bool> mp;
main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=n;i>=1;i--){
    	mp.clear();
        int flag=0;
        for(int j=1;j<=m;j++){
            s[j]+=arr[i][j];//处理当前行所增加的字母
            flag=(mp[s[j]]?1:flag);
            mp[s[j]]=1;
        }
        if(flag==0){
            cout<<i-1;//要留下一行不同的才能保证不同
            return 0;
        }
    }
    cout<<0;
}
```

---

## 作者：Tachibana27 (赞：0)

或许本题重点是字符串判重。？

### 题意

给定 $r$ 个 长度为 $c$ 且仅有小写字母的字符串，从第 $1$ 个字符串开始删除，且需要保证删除后任意 $2$ 列不重复，求最多删几个。

### Sol

可以考虑**倒序**枚举 $p$，表示删到第 $p$ 行。我们可以用 map 存储直到当前行每列的字符串，不难发现，如果可以删除到第 $p$ 行，仅当算上第 $p-1$ 行后不存在 $2$ 列重复。如果仍存在重复则代表答案不合法，需要继续枚举。在出现不重复时输出 $p$ 是最优解。

用 hash 代替 map，可以优化一个 $\log$，但其实换成 unordered_map 复杂度是差不多的。

code:

```cpp
#include<bits/stdc++.h>
int r;
int n;
char s[1086][1086];
std::string op[1086];
std::unordered_map<std::string,bool>mp;
int main(){
	std::cin>>r>>n;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=n;j++)
			std::cin>>s[i][j];//读入，建议不要写getchar
	for(int p=r;p;p--){//倒序枚举p
        mp.clear();//切记需要清空，否则会出现mle
        bool flag=false;
		for(int j=1;j<=n;j++){
			op[j]+=s[p][j];
		    if(mp[op[j]])
                flag=true;//如果仍有相同的，则答案不合法
		    mp[op[j]]=true;//标记该字符串出现过
        }
        if(not flag){
            std::cout<<p-1<<"\n";//合法输出即可
            exit(0);//退出程序
        }
    }
    return 0;//这个return 0可以不打，但是撒花！
}
```

---

## 作者：huqingyi (赞：0)

# 洛谷P6502
几乎是哈希板子题了，稍微转换一下思路就可以模拟出来。
## 题目大意
给定一个字母矩阵，你需要从第一行开始连续删除尽量多的行，使得剩下行中任意两列字母都不相等。
## 解题思路
考虑哈希与 map 判断重复。

首先，我们很容易想到，删除的行数最多，就意味着剩下的行数最少。

我们可以从最后一行开始对每一列进行哈希，**每一轮要更新 map 数组记录重复次数**。等到重复次数为零的时候，就是行数最少的无重复列矩阵。
## Code
```cpp
#include<bits/stdc++.h>
#define mod 19190813
#define base 131
using namespace std;
int r,c1,ans;
char c[1010][1010];
long long h[1010];
bool f=1;
int main(){
	cin>>r>>c1;
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c1;j++)//输入矩阵
		{
			cin>>c[j][i];
		}
	for(int i=r;i>=1;i--)//倒序枚举
	{	
	    map<long long,int> mp;
		for(int j=1;j<=c1;j++)
		{
			h[j]=(h[j]*base+c[j][i]-'a')%mod;
			mp[h[j]]++;//统计出现次数
		}	
		f=1;
		for(int j=1;j<=c1;j++)//判断是否重复
		{
			if(mp[h[j]]>1) 
			{
				f=0;break;
			}
		}
		if(f) 
		{
			ans=i-1;//因为当前的i是剩下行的第一位，所以要-1
			break;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：EuphoricStar (赞：0)

## 思路

二分答案 + 哈希。

不难想到二分删去的行数，然后判断剩下的行中是否存在完全相同的列。

重点在判重这部分。虽然可以 `strcmp` 暴力过，但是复杂度是错的。因此使用哈希判重。为了方便哈希，字符矩阵的行列可以转换，行存储列，列存储行。

防止被卡，我使用双重哈希。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 1010;
const ll base = 131, mod1 = 1000000007, mod2 = 19260817;

int n, m;
ll h1[maxn][maxn], pw1[maxn], h2[maxn][maxn], pw2[maxn];
char s[maxn][maxn], ss[maxn];

ll hash1(int l, int r, int i) {
	return ((h1[i][r] - h1[i][l - 1] * pw1[r - l + 1]) % mod1 + mod1) % mod1;
}

ll hash2(int l, int r, int i) {
	return ((h2[i][r] - h2[i][l - 1] * pw2[r - l + 1]) % mod2 + mod2) % mod2;
}

bool check(int x) {
	set<ll> st1, st2;
	for (int i = 1; i <= n; ++i) {
		ll tmp1 = hash1(x + 1, m, i), tmp2 = hash2(x + 1, m, i);
		if (st1.count(tmp1) && st2.count(tmp2)) {
			return 0;
		}
		st1.insert(tmp1);
		st2.insert(tmp2);
	}
	return 1;
}

void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", ss + 1);
		for (int j = 1; j <= m; ++j) {
			s[j][i] = ss[j];
		}
	}
	swap(n, m);
	pw1[0] = pw2[0] = 1;
	for (int i = 1; i <= max(n, m); ++i) {
		pw1[i] = pw1[i - 1] * base % mod1;
		pw2[i] = pw2[i - 1] * base % mod2;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			h1[i][j] = (h1[i][j - 1] * base + s[i][j] - 'a') % mod1;
			h2[i][j] = (h2[i][j - 1] * base + s[i][j] - 'a') % mod2;
		}
	}
	int l = 0, r = m - 1, ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	printf("%d", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：sysong (赞：0)

# 题解P6502 [COCI2010-2011#3] ZNANSTVENIK

### 题目描述

给定一个 $r \times c$ 的字母矩阵。你需要从这个矩阵的第一行开始，删除尽量多的行， 且保证矩阵任意两列都不相等。输出最多可以删除的行数。

- 两列相等定义为在这两列中同一行的字母都相等。
- 初始的矩阵中任意两列都是不相等的。

### 思路

这题有两种解法（目前来看）。

1. 二分答案（前面那个题解就是），不难想到，二分可以删去的行数，再暴力比较重复字串。

   这里把横纵坐标对换之后，可以直接使用 `strcmp` 函数比较。

   #### $Code$

   ```c++
   #include <bits/stdc++.h>
   #define R register
   #define gc() getchar()
   using namespace std;
   
   int n,m;
   char s[1010][1010];
   
   inline int check(int k){
   	for(R int i=1;i<=m;i++)
   		for(R int j=1;j<i;j++)
   			if(strcmp(s[i]+k,s[j]+k)==0)
   				return 0;
   	return 1;
   }
   
   int main(){
   	ios::sync_with_stdio(false);
   	cin>>n>>m;
   	for(R int i=0;i<n;i++)
   		for(R int j=1;j<=m;j++)
   			cin>>s[j][i];
   	R int le=0,ri=n-1,mid,ans=0;
   	while(le<=ri){
   		mid=le+ri>>1;
   		if(check(mid))ans=mid,le=mid+1;
   		else ri=mid-1;
   	}
   	cout<<ans<<endl;
   	return 0;
   }
   
   ```

2. 当我提交了二分答案的程序后，发现很多人比我快，还快了不少。

   看了几份代码后，才发现他们用的是排序。

   将**纵列**排序后，相邻两个字串的公共序列长度一定最长，所以这个方法快一些（只要一次排序就行了）。

   （代码中有注释）

   #### $Code$

   ```c++
   #include <bits/stdc++.h>
   #define R register
   #define gc() getchar()
   using namespace std;
   
   inline int rd(){
   	R int x=0;R char c=gc();//,f=1
   	while(c>'9'||c<'0')c=gc();//{if(c=='-')f=-1;
   	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
   	return x;//*f
   }
   
   int n,m,ans;
   char s[1010][1010];
   string f[1010];										// 这里用 string，是为了方便比较
   
   int main(){
   	n=rd(),m=rd();
   	for(R int i=1;i<=n;i++)
   		scanf("%s",s[i]+1);
   	for(R int i=1;i<=m;i++)f[i].resize(n);			// 如果没有这一句，后面的字符会把前面的覆盖掉 
   	for(R int j=1;j<=m;j++)
   		for(R int i=n;i>=1;i--)
   			f[j][n-i]=s[i][j];						// 这里是把原字母矩阵的横纵坐标调换过来，可以自己输出体会一下 
   	sort(f+1,f+m+1);								// 排序，这也是这个算法快的原因 
   	for(R int i=1,l;i<m;i++){
   		l=0;
   		for(R int j=0;j<n;j++)
   			if(f[i][j]==f[i+1][j])++l;				// 因为排过序，所以只要比较相邻字符串即可 
   			else break;
   		ans=max(ans,l);								// 求最长相同长度 
   	}
   	printf("%d\n",n-ans-1);							// 因为求的是最多删去不重复的行数，所以 n-ans 之后还要 -1 
   	return 0;
   }
   
   ```

   



***by jsntsys***

$2020.12.23$



---

## 作者：KadiaNEFU (赞：0)

1. 思路是把每一列存为一个字符串，然后用strcmp函数with二分搜索判断去掉前x个后所有的m个字符串是否都不相同。
2. 如果此x下满足条件，就ans=x，然后继续二分找能否有更大的x。
3. 如果此x下不满足条件，就找更小的x。
4. 注意二分的初始条件，最小去掉0个，最多去掉n-1个。

```cpp
#include <bits/stdc++.h>
using namespace std;
char ch[1005][1005];//存字符串
int n,m;
int check(int x)//check函数
{
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<i;j++)
        {
            if(strcmp(ch[i]+x,ch[j]+x)==0)
                return 0;
        }
    }
    return 1;
}
int main()
{
    cin >> n >> m;
    for(int i=0;i<n;i++)//字符串的下标
    {
        for(int j=1;j<=m;j++)//字符串的序号
        {
            scanf(" %c",&ch[j][i]);
        }
    }
    for(int j=1;j<=m;j++)//建立字符串末尾
        ch[j][n]='\0';
    int ans=0;
    int low=0,high=n-1,mid;
    while(low<=high)//二分搜索
    {
        mid=(low+high)/2;
        if(check(mid))
        {
            ans=mid;
            low=mid+1;
        }
        else
            high=mid-1;
    }
    cout << ans << endl ;
    return 0;
}

```


---

