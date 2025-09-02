# [JOI 2016 Final] 集邮比赛 2 / Collecting Stamps 2

## 题目描述

给定一个长度为 $N$ 的仅包含字符 `J`、`O`、`I` 的字符串，现在你可以在该串的任意一个位置插入一个字符，求最多能有多少个子序列（不一定连续）为 `JOI`。

## 说明/提示

【数据范围与约定】

对于所有数据，均满足 $3 \le N \le 100000$。

1. Subtask $1$（$30$ pts）：$N \le 200$。
2. Subtask $2$（$20$ pts）：$N \le 3000$。
3. Subtask $3$（$50$ pts）：无特殊限制。

## 样例 #1

### 输入

```
5
JOIOI```

### 输出

```
6```

## 样例 #2

### 输入

```
7
JJJOIII```

### 输出

```
18```

## 样例 #3

### 输入

```
4
OIIJ```

### 输出

```
2```

# 题解

## 作者：dongzirui0817 (赞：3)

首先，要放 `J` 就放开头，要放 `I` 就放末尾就会最优。  
这可由子序列的定义直接推出。

对于 `O` 而言，如果它放下标为 $i - 1$ 和 $i$ 的字母之间，其贡献是 $i - 1$ 及以前的 `J` 的数量乘 $i$ 及以后的 `I` 的数量。其中 $1 \le i \le n + 1$。  
因为这个 `O` 加进来后，原来的数量不变，直接加上其贡献即可。

所以只需给 `J` 的数量做前缀和，`I` 的数量做后缀和即可。

---

## 作者：lilong (赞：3)

首先考虑如何求出原串中 ```JOI``` 的出现次数。不难想到以 ```O``` 为中心，将左边 ```J``` 与右边 ```I``` 的数量相乘再累加起来即可。同样，我们可以运用类似的思路分析插入的字母对答案的影响。当插入 ```J``` 时，增加的贡献即为**每个 ```O``` 后面 ```I``` 的出现次数的和（注意是每个）**，此时显然在最前面插入最优。同理，插入 ```I``` 时，增加的贡献即为**每个 ```O``` 前面 ```J``` 的出现次数的和**，在最后面插入最优。插入 ```O``` 时，则与最开始的计算方式相同。三种情况取最大值即可。时间复杂度 $O(n)$。


```cpp
#include <iostream>
#include <cstdio>
#define ll long long
#define N 200010

using namespace std;

int n,a[N];
ll c1,c2,c3,s1[N],s2[N],s3[N],ans,mx1,mx2,mx3;
string s;

int main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 ); 
	cin >> n;
	cin >> s;
	for( int i = 1 ; i <= n ; i ++ )
	{
		if( s[i - 1] == 'J' ) a[i] = 1;
		if( s[i - 1] == 'O' ) a[i] = 2;
		if( s[i - 1] == 'I' ) a[i] = 3,c3 ++;
	}
	for( int i = 1 ; i <= n ; i ++ )
	{
		if( a[i] == 1 ) c1 ++;
		if( a[i] == 3 ) c3 --;
		if( a[i] == 2 )
		{
			s1[i] = c1;
			s3[i] = c3;
			ans += c1 * c3;
		}
        mx2 = max( mx2 , c1 * c3 );
	}
	for( int i = 1 ; i <= n + 1 ; i ++ )
		s1[i] += s1[i - 1],mx1 = max( mx1 , s1[i] );
	for( int i = n + 1 ; i >= 1 ; i -- )
		s3[i] += s3[i + 1],mx3 = max( mx3 , s3[i] );
	cout << ans + max( max( mx1 , mx3 ) , mx2 );
	return 0;
}
```

---

## 作者：bayiran (赞：2)

## ****集邮比赛2/Collecting Stamps2题解****

### 题目分析：
想让子序列`JOI`的数量最大化，我们就需要分析插入不同字符对结果的影响。

### 解题思路：
1. ‌计算原始`JOI`数量‌：对于每个`O`前面 `J`的数量和后面`I`的数量相乘，就是这个`O`所贡献的`JOI`的数量，然后累加每个`O`的贡献，就是原始`JOI`的数量。

2. ‌考虑插入不同字符的影响‌：

- 插入`J`：会增加它后面的所有`O`的前缀`J`的数量，因此可以放在最前面，使增加数最大。

- 插入`O`：会增加前面所有`J`和后面所有`I`的组合，因此需要讨论每个位置。

- 插入`I`：会增加它前面所有的`O`的后缀`I`计数，因此最优解是放在最后。

**高效计算‌**：我们可以先预处理每个位置的前缀`J`计数和后缀`I`计数，以便快速计算插入不同字符带来的增量。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n;
    string s;
    cin>>n>>s;
  
    // 预处理前缀J和后缀I的数量
    vector<int> J(n+1, 0); // J[i]表示前i个字符中J的数量
    vector<int> I(n+1, 0);  // I[i]表示从i开始到末尾的I的数量

    // 计算原始JOI数量
    for(int i=0; i<n;i++){
        J[i+1] = J[i] + (s[i] == 'J');
    }
    for(int i=n-1; i>=0;i--){
        I[i] = I[i+1] + (s[i] == 'I');
    }

    long long ans = 0;
    for (int i=0; i<n;i++) {
        if (s[i] == 'O') {
            ans += (long long)J[i] * I[i+1];
        }
    }
    
    // 计算插入每个位置能带来的最大增量
    long long zl = 0;
    
    // 尝试在每个位置插入J/O/I
    for (int p=0;p<=n;p++){

        // 插入J的情况：会增加后面所有O的J计数
        long long incJ = 0;
        for (int i=p;i<n;i++) {
            if (s[i] == 'O') {
                incJ += suffixI[i+1];
            }
        }

        // 插入O的情况：会增加前面所有J和后面所有I的组合
        long long incO = (long long)J[p] * I[p];

        // 插入I的情况：会增加前面所有O的I计数
        long long incI = 0;
        for (int i=0;i<p;i++) {
            if (s[i] == 'O') {
                incI += J[i];
            }
        }

        // 取三种插入情况的最大增量
        long long cm = max(max(incJ, incO), incI);
        if(cm > zl) {
            zl = cm;
        }
    }
    cout<<ans + max_increase<<endl;
    
    return 0;
}
```
时间复杂度： $ O(n^2)$。

对于 $n=1 \times 10^5$ 以上的数据会超时，因此我们需要优化。
### 优化
1. 预处理每个位置前面`O`的数量和后面`O`的数量。
2. 预处理每个位置前面`J`的数量和后面`I`的数量。
3. 计算插入`J/O/I`的增量时可以基于预处理的数据快速计算。

### 优化后的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    string s;
    cin>>n>>s;
    
    // 预处理前缀J和后缀I的数量
    vector<int> J(n+1, 0);
    vector<int> I(n+1, 0);
    
    for (int i=0; i<n;i++) {
        J[i+1] = J[i] + (s[i] == 'J');
    }
    
    for (int i=n-1; i>=0;i--) {
        I[i] = I[i+1] + (s[i] == 'I');
    }

    // 预处理前缀O的J计数和后缀O的I计数
    vector<long long> qz(n+1, 0); // 前i个字符中所有O前面J的总和
    vector<long long> hz(n+1, 0); // 从i开始所有O后面I的总和
    
    for(int i=0;i<n;i++) {
        qz[i+1] = qz[i];
        if (s[i] == 'O') {
            qz[i+1] +=J[i];
        }
    }
    
    for (int i=n-1; i>=0;i--) {
        hz[i] = hz[i+1];
        if(s[i] == 'O') {
            hz[i] += I[i+1];
        }
    }
    
    // 计算原始JOI数量
    long long ans = 0;
    for (int i=0;i<n;i++) {
        if (s[i] == 'O') {
            ans += (long long)J[i] * I[i+1];
        }
    }
    
    // 计算插入每个位置能带来的最大增量
    long long zl = 0;
    
    for (int pos = 0; pos <= n; ++pos) {
        // 插入J的情况：会增加后面所有O的J计数
        long long incJ = hz[pos];
        
        // 插入O的情况：会增加前面所有J和后面所有I的组合
        long long incO = (long long)J[pos] * I[pos];
        
        // 插入I的情况：会增加前面所有O的I计数
        long long incI = qz[pos];
        
        // 取三种插入情况的最大增量
        long long cm = max(max(incJ, incO), incI);
        if (cm > zl) {
            zl = cm;
        }
    }
    
    cout<<ans + cm<<endl;
    
    return 0;
}
```
优化后的时间复杂度：$O(n)$。

现在可以处理 $1 \times 10^5$ 以上规模的数据。主要优化点在于预处理了`qz`和`hz`数组，使得计算增量时可以 $O(1)$ 时间完成。

---

## 作者：liuyuantao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P11794)  
这真的是蓝题？个人觉得跟[这个](https://www.luogu.com.cn/problem/P11788)差不多。  
我们考虑枚举中间的 ```O```，根据乘法原理，分两步选择 ```J``` 和 ```I```，预先统计出在其之前的 ```J``` 和之后的 ```I``` 的数量，相乘即可。  
预处理可利用 $dpj_i=dpj_{i-1}+[s_i=J]$ 和 $dpi_i=dpi_{i+1}+[s_i=I]$ 计算 $ans=\sum[s_i=O]\times{dpi_i \times dpj_i}$。  
之后来增加字符。当增加 ```O``` 时，只有在两字符间增加才有贡献，其贡献可仿照上式计算。  
当增加 ```J``` 时，只有在它之后的字符可以与它组合，于是我们贪心地将它放到最前，再遍历数组中的 ```O``` 增加贡献 $dpj_i$ (显然只有一个 ```J``` 产生新贡献)。增加 ```I``` 同理。  
最后在所有贡献中取最大值加入答案即可。  
时间复杂度 $O(n)$。  
[AC 参考代码](https://www.luogu.com.cn/record/205548847)

```cpp
#include<bits/stdc++.h>

using namespace std;

#define LL long long

const int N=1e5+5;
LL n,cnt,cnt1,ans;
LL dpj[N],dpof[N],dpol[N],dpi[N];
string s;

int main(){
    ios::sync_with_stdio(false);
    cin>>n>>s;
    for(int i=1;i<=n;i++){
        dpj[i]=dpj[i-1];
        if(s[i-1]=='J')dpj[i]++;
    }
    for(int i=n;i>=1;i--){
        dpi[i]=dpi[i+1];
        if(s[i-1]=='I')dpi[i]++;
    }
    ans=0;
    for(int i=1;i<=n;i++){
        if(s[i-1]=='O'){
            ans+=dpj[i]*dpi[i];
        }
    }
    cnt=0;
    for(int i=1;i<n;i++){
        cnt=max(cnt,dpj[i]*dpi[i+1]);
    }
    cnt1=0;
    for(int i=1;i<=n;i++){
        if(s[i-1]=='O'){
            cnt1+=dpi[i];
        }
    }
    cnt=max(cnt,cnt1);
    cnt1=0;
    for(int i=1;i<=n;i++){
        if(s[i-1]=='O'){
            cnt1+=dpj[i];
        }
    }
    cnt=max(cnt,cnt1);
    ans+=cnt;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：zhanghq2012 (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/P11794)

## 思路
### 预处理
首先先算出最初的个数，固定枚举 `JOI` 中间的 `O`，然后在 `O` 的前面统计枚举 `J`，后面统计枚举 `I`，然后根据乘法原理相乘然后再根据假发原理将每个 `O` 的情况个数再相加即可。

也就是：$totj_i = totj_{i−1}+[s_i=J]$ 和 $toti_i=toti_{i+1}+[s_i=I]$，然后再计算 $ans=∑[s_i=O]×toti_i×totj_i$。
### 增加字符
分为三种情况
1. 插入 `O`：`O` 必须在 `J` 和 `I` 两个字符之间才有贡献，做法和**预处理**类似，都是用乘法原理，找到个数最多的那个， 也就是 `cnt = max(cnt, totj[i] * toti[i+1])`。
2. 插入 `J`：只有在它之后的字符可以与它组合，于是将它放到最前，再计算枚举每个 `O` 能搭配的情况个数，相加，即 `cnt1 += toti[i]`。
3. 插入 `I`：同插入 `J`，只需插到最后面。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long toti[100005]/*I的情况*/, totj[100005]/*J的情况*/;

int main()
{
	long long n, cnt = 0, cnt1 = 0, cnt2 = 0, ans = 0;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> n >> s;
    for(int i = 1; i <= n; i++)
	{
        totj[i] = totj[i - 1];
        if(s[i - 1] == 'J')
			totj[i]++;
    }
    for(int i = n; i >= 1; i--)
	{
        toti[i] = toti[i + 1];
        if(s[i - 1] == 'I')
			toti[i]++; 
    }
    for(int i = 1; i <= n; i++)
	{
        if(s[i - 1] == 'O')
		{
            ans += totj[i] * toti[i];
        }
    }
    //插入O 
    for(int i = 1; i < n; i++)
	{
        cnt = max(cnt, totj[i] * toti[i+1]);
    }
    //插入J 
    for(int i = 1; i <= n; i++)
	{
        if(s[i - 1] == 'O')
		{
            cnt1 += toti[i];
        }
    }
    //插入I 
    for(int i = 1; i <= n; i++)
	{
        if(s[i - 1] == 'O')
		{
            cnt2 += totj[i];
        }
    }
    cnt = max({cnt, cnt1, cnt2}); //比较求最大的 
    ans += cnt;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：114514lhc (赞：1)

~~感觉小日子题难度虚高，建议降绿。~~   
先把字符转化成数字数组 $a$ ， $1,2,3$ 分别代表 $\text{J,O,I}$ 。   
定义一个前缀数组 $x$ 和一个后缀数组 $y$ ,其中   
$x_{i,1},x_{i,2},x_{i,3}$ 分别为到 $i$ 为止子序列是 $\text{J , JO , JOI}$ 的数量，$x_{i,j}=x_{i-1,j}$ ，若 $a_i=j$ ,则 $x_{i,j}$ 要再加上 $x_{i-1,j-1}$ 。 
$y_{i,1},y_{i,2},y_{i,3}$ 分别为到 $i$ 为止子序列是 $\text{JOI , OI , I}$ 的数量，$y_{i,j}=y_{i+1,j}$ ，若 $a_i=j$ ,则 $y_{i,j}$ 要再加上 $y_{i+1,j+1}$ 。   
**需要注意，$x_{i,0}$ 和 $y_{j,4}$ 初始为 $1$ 。**   
然后从到枚举添加位置和添加字符，  
答案便是 $x_{i,j-1}\times y_{i+1,j+1}+x_{n,3}$ （ $j$ 是添加字符）的最大值。
代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=114514;
int n,a[N],x[N][5],y[N][5];
string s;
signed main()
{
    cin>>n>>s;s=' '+s;
    x[0][0]=1;y[n+1][4]=1;
    for(int i=1;i<=n;i++)
    {
        if(s[i]=='J')a[i]=1;
        if(s[i]=='O')a[i]=2;
        if(s[i]=='I')a[i]=3;
        x[i][0]=1;
        for(int j=1;j<=3;j++)
            x[i][j]=x[i-1][j]+(a[i]==j)*x[i-1][j-1];
    }
    for(int i=n;i>=1;i--)
    {
        y[i][4]=1;
        for(int j=1;j<=3;j++)
            y[i][j]=y[i+1][j]+(a[i]==j)*y[i+1][j+1];
    }
    int ans=0;
    for(int i=0;i<=n;i++)
    {
        for(int j=1;j<=3;j++)
            ans=max(ans,x[i][j-1]*y[i+1][j+1]+x[n][3]);
    }
    cout<<ans;
	return 0;
}

```

---

## 作者：ELECTRODE_kaf (赞：1)

先考虑修改前的答案。统计前缀中 `J` 的个数和后缀中 `I` 的个数，每一个 `O` 前后相乘加起来即可。

若添加 `J`，则贪心地加在开头，对于每一个 `O`，贡献即为后缀中 `I` 的数量。添加 `I` 同理。

若添加 `O`，则枚举每个位置插入，贡献计算方法不变。

复杂度线性。

```cpp
const ll N = 1e5 + 10;
ll n, ps[N], ss[N], sum, ans;
string s;

void cal_j() {
	ll add = 0;

	rep(i, 0, n - 1) {
		if (s[i] == 'O')
			add += ss[i];
	}

	update(ans, sum + add, max);
}

void cal_i() {
	ll add = 0;

	rep(i, 0, n - 1) {
		if (s[i] == 'O')
			add += ps[i];
	}

	update(ans, sum + add, max);
}

void cal_o() {
	ll add = 0;

	rep(i, 0, n - 2) update(add, ps[i]*ss[i], max);

	update(ans, sum + add, max);
}

int main() {
	cin >> n >> s;
	ps[0] = s[0] == 'J';

	rep(i, 1, n - 1) ps[i] = ps[i - 1] + (s[i] == 'J');

	ss[n - 1] = s[n - 1] == 'I';

	rep_(i, n - 2, 0) ss[i] = ss[i + 1] + (s[i] == 'I');

	rep(i, 1, n - 2) {
		if (s[i] == 'O')
			sum += ps[i] * ss[i];
	}

//	cout << "sum=" << sum << '\n';
//	pause;
	cal_j();
	cal_o();
	cal_i();
	cout << ans;
}
```

---

## 作者：yanmingqian (赞：0)

显然，如果没有插入的这个数，我们可以直接前缀和维护 J 的个数，后缀和维护 I 的个数，对于每个 O，对答案的贡献就是前缀 J 的个数乘后缀 I 的个数。不难写出下面的代码：
```cpp
	s=" "+s;
	for(int i=1;i<=n;i++){
		t1[i]=t1[i-1]+(s[i]=='N');
	} 
	for(int i=n;i>=1;i--){
		t2[i]=t2[i+1]+(s[i]=='I');
	}
    long long ans=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='O'){
            ans+=t1[i]*t2[i];
        }
    }
```

在此基础上，考虑如何求解答案。

有下面三种情况：

1. 插入 J：显然，在最前面位置插入是最优的。

2. 插入 I：显然，在最后面位置插入是最优的。

3. 插入 O：枚举每个插入点即可，统计方式同上面不插入时。

这样我们就可以过掉这个题了。

代码：

```cpp
#include<iostream>
using namespace std;
const int N=1e5+10; 
long long t1[N],t2[N];
int main(){
	int n;
	string s;
	cin>>n>>s;
	s=" "+s;
	for(int i=1;i<=n;i++){
		t1[i]=t1[i-1]+(s[i]=='J');
	} 
	for(int i=n;i>=1;i--){
		t2[i]=t2[i+1]+(s[i]=='I');
	}
	long long ans1=0,ans2=0,ans3=0,maxx=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='O'){
			ans1+=(t1[i]+1)*t2[i];
			ans2+=t1[i]*(t2[i]+1);
        	ans3+=t1[i]*t2[i];
		}maxx=max(maxx,t1[i]*t2[i]);
	}  
	cout<<max(max(ans1,ans2),ans3+maxx);
	return 0;
}
```

---

## 作者：yihang2011 (赞：0)

### [P11794 [JOI 2016 Final] 集邮比赛 2 / Collecting Stamps 2](https://www.luogu.com.cn/problem/P11794)

初一考完来拯救一下咕值。

计数问题。考察前缀和应用。

首先，很容易得出，在没有添加任何字符的情况下，子序列 `JOI` 的个数为 $\sum_{i=1}^{n}[s_i = O](\sum_{j=1}^{i - 1}[s_j = J])(\sum_{k=i+1}^{n}[s_k = I])$。

考虑前缀和优化，记 $J_i$ 为从第 $1$ 个字符到第 $i$ 个字符为 `J` 的个数，$I_i$ 为从第 $1$ 个字符到第 $i$ 个字符为 `I` 的个数。则子序列 `JOI` 的个数为 $\sum_{i=1}^{n}[s_i = O][J_i(I_n - I_i)]$。

添加字符分为三种情况。当在第 $i(0 \le i \le n)$ 个字符后面添加字符时：

如果添加的字符为 `J`，则答案在原序列的基础上增加了添加的字符之后部分的子序列 `OI` 的个数。

如果添加的字符为 `I`，则答案在原序列的基础上增加了添加的字符之前部分的子序列 `JO` 的个数。

如果添加的字符为 `O`，则答案在原序列的基础上增加了 $J_i(I_n - I_{i})$。

前面两种情况分别需要计算第 $i$ 个字符及前面部分的子序列 `JO` 的个数呵第 $i$ 个字符及后面部分的子序列 `OI` 的个数。

以求前者为例。可以借助刚才求出的前缀和，求出每一个字符 `O` 的前面字符 `J` 的个数，最后累加即可。后者原理相同，不再解释。

时间复杂度 $O(n)$。

最后上代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define pqueue priority_queue
#define umap unordered_map
#define set(f, x) memset(f, x, sizeof f)
using ll = long long;
ll read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0', ch = getchar();
    }
    return x * f;
}
#define rd read()
void write(ll x) {
    if (x < 0) {
        putchar('-'), x = -x;
    } 
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
#define wln(x) write(x); putchar('\n');
#define wt(x) write(x); putchar(' ');
#define db(x) printf(#x); putchar(':'); wln(x);

const int N = 1e5 + 10;
string s;
int n;
ll J[N], I[N], O[N], JO[N], OI[N];

int main() {
    n = rd;
    cin >> s;
    s = " " + s;
    for (int i = 1; i <= n; i++) {
        J[i] = J[i - 1] + (s[i] == 'J');
        I[i] = I[i - 1] + (s[i] == 'I');
    }
    for (int i = 1; i <= n; i++) {
        OI[i] = (I[n] - I[i]) * (s[i] == 'O');
        JO[i] = J[i] * (s[i] == 'O');
    }
    for (int i = n; i; i--) {
        OI[i] += OI[i + 1];
    }
    for (int i = 1; i <= n; i++) {
        JO[i] += JO[i - 1];
    }
    ll cnt = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'O') {
            cnt += J[i] * (I[n] - I[i]);
        }
    }
    for (int i = 0; i <= n; i++) {
        ans = max(ans, cnt + OI[i + 1]);
        ans = max(ans, cnt + J[i] * (I[n] - I[i]));
        ans = max(ans, cnt + JO[i]);
    }
    wln(ans);
    return 0;
}
```

你说……既然子序列 `JO` 的前缀和数组名叫 JO，那么子序列 `OI` 的后缀和数组名叫什么呢？**那当然是 OI 啦！**

---

