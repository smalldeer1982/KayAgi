# 【MX-X8-T0】「TAOI-3」分数

## 题目背景

原题链接：<https://oier.team/problems/X8A>。

## 题目描述

小巡参加了 $n$ 场考试。所有考试结束后，小由进行批改。

一开始，小由给小巡第 $i$ 场考试的结果评了 $a_i$ 分。

但是由于小由很严厉，如果小由发现小巡总分大于等于及格分 $T$ 就会重新批改，第二次批改后小巡的第 $i$ 场考试的结果会评为 $b_i$ 分，总分也应该按照第二次批改的评分计算。

你需要告诉小巡他最后的总分。

## 说明/提示

**【样例解释 #1】**

第一次批改后，小巡的得分为 $253$，没有及格，因此小由不会重新批改，总分为 $253$。

**【样例解释 #2】**

第一次批改后，小巡的得分为 $253$，达到了 $100$，因此小由会重新批改，重新批改的总分为 $364$。


**【数据范围】**

对于所有数据，保证 $1\leq n\leq 10$，$1\leq T\leq 1000$，$1\leq a_i,b_i\leq 100$。

## 样例 #1

### 输入

```
4 300
98 87 56 12
99 88 87 90
```

### 输出

```
253```

## 样例 #2

### 输入

```
4 100
98 87 56 12
99 88 87 90
```

### 输出

```
364```

# 题解

## 作者：pipilong2024 (赞：7)

### 题目大意
给出两个正整数 $n,T$，两个长度为 $n$ 的序列 $a$ 和 $b$。
$$
ans= \begin{cases}
  \sum_{i = 1}^{n} a_i & (\sum_{i = 1}^{n} a_i < T) \\
  \sum_{i = 1}^{n} b_i & (\sum_{i = 1}^{n} a_i \ge T)
\end{cases}$$
### 解决思路
模拟即可。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a,sum1,sum2;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>a;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		sum1+=x;
	}//此处x即为a[i]
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		sum2+=x;
	}//此处x即为b[i]
	cout<<(sum1<a?sum1:sum2);
	return 0;
}
```

---

## 作者：qiutian120529 (赞：6)

# 0x01 题意
求出两种总分，如果第一种总分小于及格分，则输出第一种总分，否则输出第二种总分。

# 0x02 思路
先求出第一种总分，如果符合要求就标记，接着求出第二种总分。最后如果有标记就输出第一种总分，否则输出第二种总分。

# 0x03 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int sum, ans, f;

int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, t;
    cin >> n >> t;
    for(int i = 1, x; i <= n; i++){
        cin >> x;
        ans += x;
    }
    if(ans < t){
        f = 1;
    }
    for(int i = 1, x; i <= n; i++){
        cin >> x;
        sum += x;
    }
    cout << (f ? ans : sum);
    return 0;
}
```

---

## 作者：ikunTLE (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P11641)

### 思路

首先算出 $S_1=\sum a_i$，若 $S_1<T$，输出 $S_1$。否则计算 $S_2=\sum b_i$，并输出 $S_2$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=15;
int a[N];
signed main(){
	int n=read(),t=read();
	int sum=0;
	for(int i=1;i<=n;++i){
		a[i]=read();
		sum+=a[i];
	}
	if(sum<t)
		return printf("%d\n",sum),0;
	int ans=0;
	for(int i=1;i<=n;++i){
		int x=read();
		ans+=x;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Helenty (赞：4)

### 解题思路

题目讲的很清楚了，$a$ 数组的总和大于等于 $T$ 就输出 $b$ 数组的总和，否则输出 $a$ 数组的总和。

### 完整代码


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, T, suma, sumb, a[15], b[15];
int main()
{
    cin >> n >> T;
    for (int i = 1; i <= n; ++i)
	{
        cin >> a[i];
        suma += a[i];
    }
    for (int i = 1; i <= n; ++i)
	{
        cin >> b[i];
        sumb += b[i];
    }
    if (suma >= T) cout << sumb << endl;
	else cout << suma << endl;
    return 0;
}
```

---

## 作者：zlqwq (赞：3)

好水啊，先算一下 $a$ 的和，如果小于 $T$ 就输出。

否则输出 $b$ 的和即可。


```cpp
#include<iostream>
#define int long long
using namespace std;
int n,m;
int a[15],b[15];
int ans=0;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i];
	}
	if(ans<m){
		cout<<ans;
		return 0;
	}
	ans=0;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		ans+=b[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

如果第一次总分达到了 $T$ 就按第二次算成绩，否则按第一次算成绩。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[15],b[15],cnt1,cnt2;
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt1+=a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		cnt2+=b[i];
	}
	if(cnt1>=t)
		cout<<cnt2;
	else
		cout<<cnt1;
}
```

---

## 作者：xyx404 (赞：2)

## 思路：
语法题。

考点：循环结构和分支结构。

将两个批改结果的和分别存下来，如果第一次的和大于等于 $T$，则输出第二次批改结果的和，否则输出第一次批改结果的和。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long 
int T=1;
int n; 
int a[15],b[15];
int main(){
	cin>>n>>T;
	LL sum1=0,sum2=0;
	for(int i=1;i<=n;i++)cin>>a[i],sum1+=a[i];
	for(int i=1;i<=n;i++)cin>>b[i],sum2+=b[i];
	if(sum1>=T)cout<<sum2<<"\n";
	else cout<<sum1<<"\n";
	return 0;
}
```

---

## 作者：M1__ (赞：2)

# 题解：P11641 【MX-X8-T0】「TAOI-3」分数
依照题意模拟即可。                           
用 $sum$ 和 $ans$ 分别求出小由给小巡的第一次评的总分和第二次评的总分。如果第一次的评分大于等于及格分 $T$，就输出 $ans$。反之则输出 $sum$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,t,a[100010],b[100010];
ll sum,ans;
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++) cin>>a[i],sum+=a[i];
	for(int i=1;i<=n;i++) cin>>b[i],ans+=b[i];
	if(sum>=t) cout<<ans;
	else cout<<sum;
	return 0;
}
```

---

## 作者：Eric1030 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P11641)

这是一道一点也不难的运用到了循环和判断的题目。

我们只需要把数据输入进来之后判断第一次输入进来的总和是否大于等于 $T$，如果大于等于 $T$，输出第二次输入进来的数的总和。否则就输出第一次输入进来数的总和。

整体思路就说完了，下面就是代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t;
int a[10005],b[10005],sum,sum1;
int main()
{
    cin>>n>>t;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        sum+=a[i];//sum用来记录第一次判出来的成绩总和
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
        sum1+=b[i];//sum1用来记录第二次判出的成绩总和
    }
    if(sum>=t)//如果第一次的总分大于等于T
    {
        cout<<sum1;//输出第二次的总分
        return 0;
    }
    cout<<sum;//如果上面的判断不成立，也就不会结束程序，在这里直接输出sum就可以了
    return 0;
}
```

[AC](https://www.luogu.com.cn/record/200936192) 记录。

---

## 作者：BeeAC (赞：2)

## 思路
简单的模拟题。先分别求出 $a_1,a_2,\dots,a_n$ 之和 $sum_a$ 以及 $b_1,b_2,\dots,b_n$ 之和 $sum_b$；若 $sum_a<T$ 输出 $sum_a$，否则输出 $sum_b$。时间复杂度 $O(n)$，期望得分 $100$ 分。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b,sa,sb;
void read(int &x)
{//快读
	x=0;int f=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		f=c=='-';
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	x=f?-x:x;
	return;
}
int main()
{
	read(n);read(t);
	for(int i=1;i<=n;++i)
		read(a),sa+=a;
	for(int i=1;i<=n;++i)
		read(b),sb+=b;
	printf("%d",sa>=t?sb:sa);
	return 0;
}
```

---

## 作者：Co_Ce (赞：0)

# solution  

[link](https://www.luogu.com.cn/problem/P11641)  

首先，读入 $n$ 和 $t$。  
在读入 $a$ 数组和 $b$ 数组，并将其累加。  
如果 $sum_a \geq t$ 输出 $sum_b$，否则输出 $sum_a$。  

## std：
```cpp
#include <bits/stdc++.h>

using namespace std ;

int n , t ;

int a[20] , b[20] ;

int sum_a , sum_b ;

int main () {
	cin >> n >> t ;
	for ( int i = 1 ; i <= n ; i ++ ) cin >> a[ i ] , sum_a += a[ i ] ;
	for ( int i = 1 ; i <= n ; i ++ ) cin >> b[ i ] , sum_b += b[ i ] ;
	if ( sum_a >= t ) cout << sum_b ;
	else cout << sum_a ;
	return 0 ;
}
```

---

## 作者：Charles_with_wkc (赞：0)

# 思路：
一道简单的入门题。

我们可以令两个变量计算 $a_i$ 的和和 $b_i$ 的和。判断，如果 $a_i$ 和大于等于 $T$，输出 $b_i$ 和，否则输出 $a_i$ 和。
# 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
int n,t,x,sum1,sum2;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		cin>>x;
		sum1+=x;
	}
	for(int i=1;i<=n;i++){
		cin>>x;
		sum2+=x;
	}
	if(sum1>=t) cout<<sum2;
	else cout<<sum1;
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# P11641 题解

## 思路

计算 $a$ 数组元素的和，如果元素和大于等于 $T$，则输出 $b$ 数组元素和，否则输出 $a$ 数组元素和。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
#define i32 signed
#define i64 long long
#define i128 __int128
#define u32 unsigned
#define u64 unsigned long long
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<double,double> pdd;

namespace IO {
    template<typename T> inline void read(T& x) {
        int s=1; char c=getchar(); x=0;
        while (!isdigit(c)) { if (c=='-') s=-1; c=getchar(); }
        while (isdigit(c)) x=x*10+(c-'0'),c=getchar();
        x*=s;
    }
    inline void readstr(string& x) {
        x.clear(); char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x.push_back(c),c=getchar();
    }
    inline void readstr(char* x) {
        int idx=0; char c=getchar();
        while (isspace(c)) c=getchar();
        while (!isspace(c)) x[++idx]=c,c=getchar();
    }
    template<typename T> inline void write(T x) {
        if (x<0) putchar('-'),x=-x;
        if (x/10) write(x/10);
        putchar('0'+(x%10));
    }
    template<typename T> inline void writesp(T x) { write(x); putchar(' '); }
    template<typename T> inline void writeln(T x) { write(x); putchar(10); }
};

using namespace IO;

const int N=15;

int n,T,sum;
int a[N],b[N];

int main() {
    read(n),read(T);
    _rep(i,1,n) read(a[i]),sum+=a[i];
    _rep(i,1,n) read(b[i]);
    if (sum>=T) {
        sum=0;
        _rep(i,1,n) sum+=b[i];
    }
    write(sum);
    return 0;
}
```

---

## 作者：DashZhanghanxu (赞：0)

# 解析
一道语法题。

输入考试分数和及格分数，计算总分，若大于及格分，则再次输入第二次批改的分数，并计算总分。最后输出总分。
# CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10001];
int main(){
	int n,t;
	cin>>n>>t;
	int sum=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}if(sum>=t){
		sum=0;
		for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	}cout<<sum;
	return 0;
}
```

---

## 作者：Jerry_zpl (赞：0)

题目很简单，我们可以计算第一次的评分总分，如果大于 $T$，那么直接输出总分。否则我们计算第二次的总分，再输出就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int a[maxn],b[maxn];
int n,t;
signed main()
{
	cin>>n>>t;
	int ans=0;
	for(int i=1;i<=n;i++) cin>>a[i],ans+=a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	if(ans<t) cout<<ans;
	else
	{
		ans=0;
		for(int i=1;i<=n;i++) ans+=b[i];
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：gengchenghao (赞：0)

## 题意
如果第一次成绩总和不及格就输出第一次成绩，否则输出第二次成绩总和。
## 做法
将第一次成绩求和，与及格线比较，及格就输出第二次成绩的和，不及格就输出第一次的和。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,sum;
int main(){
	cin>>n>>t;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		sum+=a;//求和
	}
	if(sum<t){//比较
		cout<<sum;
		return 0;
	}
	sum=0;
	for(int i=1;i<=n;i++){
		int b;
		cin>>b;
		sum+=b;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Rain_Joker (赞：0)

计算出 $\sum_{i=1}^{n} a_i$ 是否 $\ge T$，如果不是输出这个数，否则输出 $\sum_{i=1}^{n} b_i$。

```cpp
int n,T,sa=0,sb=0,x;
cin >> n >> T;
    
for(int i=1;i<=n;i++){
  cin >> x;
  sa+=x;
}
    
if(sa<T){
  cout << sa << endl;
  return 0;
}
 
for(int i=1;i<=n;i++){
  cin >> x;
  sb+=x;
}
    
cout << sb;
return 0;
```

---

## 作者：fish_love_cat (赞：0)

直接模拟即可，先统计 $a$ 序列的和 $sum_a$，再统计 $b$ 序列的和 $sum_b$，然后将 $sum_a$ 同及格线 $T$ 比较，若没有及格输出 $sum_a$，及格输出 $sum_b$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
    int n,t;
    cin>>n>>t;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        a+=x;
    }
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        b+=x;
    }
    if(a>=t)cout<<b;
    else cout<<a;
    return 0;
}
```

建议评红。

---

