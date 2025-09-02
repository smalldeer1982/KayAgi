# [ABC137C] Green Bin

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc137/tasks/abc137_c

文字列 $ a $ に含まれる文字を何らかの順序で並べることで得られる文字列を $ a $ の *アナグラム* と呼びます。

例えば、`greenbin` は `beginner` のアナグラムです。このように、同じ文字が複数回現れるときはその文字をちょうどその回数だけ使わなければなりません。

$ N $ 個の文字列 $ s_1,\ s_2,\ \ldots,\ s_N $ が与えられます。それぞれの文字列は長さが $ 10 $ で英小文字からなり、またこれらの文字列はすべて異なります。二つの整数 $ i,\ j $ $ (1\ \leq\ i\ <\ j\ \leq\ N) $ の組であって、$ s_i $ が $ s_j $ のアナグラムであるようなものの個数を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ s_i $ は長さ $ 10 $ の文字列である。
- $ s_i $ の各文字は英小文字である。
- $ s_1,\ s_2,\ \ldots,\ s_N $ はすべて異なる。

### Sample Explanation 1

$ s_1\ = $ `acornistnt` は $ s_3\ = $ `constraint` のアナグラムです。他に $ s_i $ が $ s_j $ のアナグラムであるような $ i,\ j $ の組はないため、答えは $ 1 $ です。

### Sample Explanation 2

$ s_i $ が $ s_j $ のアナグラムであるような $ i,\ j $ の組がないときは $ 0 $ と出力してください。

### Sample Explanation 3

ここにそのようなケースを置くことはできませんが、答えは $ 32 $ bit 整数型に収まらない可能性があるので注意してください。

## 样例 #1

### 输入

```
3
acornistnt
peanutbomb
constraint```

### 输出

```
1```

## 样例 #2

### 输入

```
2
oneplustwo
ninemodsix```

### 输出

```
0```

## 样例 #3

### 输入

```
5
abaaaaaaaa
oneplustwo
aaaaaaaaba
twoplusone
aaaabaaaaa```

### 输出

```
4```

# 题解

## 作者：MattL (赞：2)

这篇题解可能和另一篇题解会有雷同 ~~，但我的解释多一点~~

[题目传送门](https://www.luogu.com.cn/problem/AT4862)

## 思路：
1. 输入字符串，排序，加入map
2. 把所有有数据的map都循环一次，答案加上它的对数
3. 输出答案

这里介绍一下数据类型——**auto**

- **auto**有优点有缺点
- **auto**可以缩短太长的数据类型名，但需要初始化
- ###  这里是运用了**auto**的特性——只访问有数据的元素
格式：for(auto name:数组/map/vector……)

map<key,value>实际储存了一串pair<const key,value>

例子：

map用来存有多少个下标这样的字符组合
```cpp
map<string,int> mp;
auto a=mp;
for(auto i:mp)
{
  i.first返回key
  i.second返回value
}
```


更详细说明请见代码：

```cpp
#include <iostream>
#include <algorithm>
#include <map>
#define ff(i,q,a,z) for(auto i=q;i<=a;i+=z)
using namespace std;
typedef long long ll;
inline ll read(){
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
void write(long long out){
	if(out<0){putchar('-');out=abs(out);}
	if(out>9)write(out/10);
	printf("%d",out%10);
}
ll n,ans;//十年OI一场空，忘开long long 见祖宗
string t;
map<string,ll> mp;
int main()
{
	n=read();//n个字符串
	ff(i,1,n,1)
	{
		getline(cin,t);//读一整行字符串
		sort(t.begin(),t.end());//把字符串按字典序排序
		mp[t]++;//放入mp
	}
	for(auto i:mp)
	{
		ans+=i.second *(i.second-1)/2;有i.second个i.first这样的字符串，就是有i.second *(i.second-1)/2对
	}
	write(ans);输出
	puts("");AT的题一定一定一定要输出换行
	return 0;
}

```
[AC记录](https://www.luogu.com.cn/record/50680371)

---

## 作者：Zirnc (赞：2)

[ChungZH's blog](https://chungzh.cn) · [ChungZH's portfolio](https://chungzh.cc)


## 题目

我们将调用通过以某种顺序排列字符串 $a$ 中包含的字符而获得的字符串，即 _anagram_。

例如，`greenbin` 是 `beginer` 的 _anagram_。 如此处所示，当同一字符多次出现时，该字符必须使用该次数。

给定 $N$ 个字符串 $s_1,s_2,\ldots,s_N$。每个字符串的长度为 $10$，由小写英文字符组成。 此外，所有这些字符串都是不同的。 找出整数对的数量 $(1 \leq i < j \leq N)$，使 $s_i$ 是 $s_j$ 的 _anagram_。

## 题解

每输入一个字符串就先排好序，然后用 STL 中的 map 记录每种字符串出现的次数，最后用 `(a.second * (a.second - 1) / 2)` 求出 $i, j$ 对数。

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#define ll long long
using namespace std;
int main() {
  int n;
  cin >> n;
  map<string, ll> m;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    m[s]++;
  }
  ll ans = 0;
  for (auto a : m) 
    ans += (ll)(a.second * (a.second - 1) / 2);
  cout << ans << endl;
  return 0;
}
  ```

---

## 作者：so_find_skind (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc137_c)

## 本题思路：

首先不难看出，两者被判定为 anagram 的话，说明在排序之后是**完全相等**的，那么第一步就是排序，即：

~~~
for(...)
	sort(a[i].begin(),a[i].end());
sort(a+1,a+1+n);
~~~

第二步两种做法：

一、直接暴力枚举，只是因为 $n\leq10^5$，所以泡汤了。

二、每次记录连续相等的数量，同时我们假定数量为 $ans$，那么这个区间的对数即为 $\frac{ans\times(ans-1)/2}{2}$，将每个连续区间对数相加得和即可。

## 代码实现

~~~
#include<bits/stdc++.h>
using namespace std;
long long n,ans=1,sum;
//长度为十的字符串有至多3628800种表达方式还是得防超int的
string a[100005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sort(a[i].begin(),a[i].end());
    }
    sort(a+1,a+1+n);
    a[n+1]="1";
    for(int i=2;i<=n+1;i++){
        if(a[i]==a[i-1])
            ++ans;
        else{
            sum+=ans*(ans-1)/2;
            ans=1;
        }
    }
    cout<<sum<<"\n";
    //不要忘换行
    return 0;
}
~~~

---

## 作者：xiaomuyun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT4862)

## 题目分析

若有两个字符串互为 _anagram_ ，当且仅当将这两个字符串分别排序之后完全相等。比如说把 $\texttt{greenbin}$ 和 $\texttt{beginner}$ 分别排序之后都得到了 $\texttt{beeginnr}$，因此 $\texttt{greenbin}$ 和 $\texttt{beginner}$ 互为 _anagram_ 。

所以我们可以弄一个 map，用来给字符串当桶。给每个字符串排序后更新桶。最后用迭代器遍历一遍桶，对于每组排序后相同的字符串，也就是两两互为 _anagram_ 的字符串，就用 $C_n^2=\frac{n\times(n-1)}2$ 求解即可（设 $n$ 为排序后相同的字符串的数量，$C_n^2$ 为组合数，即 $n$ 个互不相同的数中任选两个的方案总数）。

## 代码实现

```cpp
#include<algorithm>
#include<iostream>
#include<string>
#include<cstdio>
#include<map>
#define int long long
using namespace std;
const int maxn=1e5+1;
int n,res=0;
string s[maxn];
map<string,int> mp;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		cin>>s[i];
		sort(s[i].begin(),s[i].end());//排序
		++mp[s[i]];//更新桶
	}
	for(map<string,int>::iterator it=mp.begin();it!=mp.end();++it) res+=(it->second)*(it->second-1)/2;//迭代器遍历，更新答案
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc137_c)

## 思路

> 我们将调用通过以某种顺序排列字符串 $a$ 中包含的字符而获得的字符串，即 $anagram$。

题目中这句话的意思呢，大概就是一个字符串 $a$ 不管以何种顺序给出，都只能算是一种字符串。于是这时，我们就要用到字符串排序了。之后因为要存储这些字符串，那么就需要我们用到一个键类型为字符串的 map 了。又因为这道题的数据范围是 $2\leq N\leq 10^5$ ，而我们之后要用到 $ N^2$ 的空间，所以需要开 long long。

组合数公式是 $C^m_n=\frac{n!}{m!(n-m)!}$，而这道题可以把这个公式变式为 $C^2_n=\frac{n\times (n-1)}{2}$，这就是此上阐述要开 long long 的理由。

最后循环迭代，给每个得到的 pair 键值对利用上面的组合数公式求和，并输出。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
string s;
map<string,long long>mp;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>s;
        sort(s.begin(),s.end());//字符串排序并存储
        mp[s]++;
    }
    for(auto i:mp)ans+=i.second*(i.second-1)/2;//迭代求和
    cout<<ans<<endl;
    return 0;
}
~~~

[AC 记录](https://www.luogu.com.cn/record/96099855)

---

## 作者：tZEROちゃん (赞：0)

直接做就可以了。

考虑给每个字符串的内部按字典序排序，然后再 $O(n^2)$ 枚举 $i, j$，当 $s_i = s_j$ 时，那么这一对就是可以的。

但是因为 $n = 10^5$ ，所以这个做法是会 TLE 的。

考虑使用 `map` 存储一个字符串已经出现的个数，以第 3 个样例为例：

1. $s_1 = \tt abaaaaaaaa$，排序后是 $s_1' = \tt aaaaaaaaab$，此时 `mp["aaaaaaaaab"] = 1`；
2. $s_2 = \tt oneplustwo$，排序后是 $s_2' = \tt elnoopstuw$，此时 `mp["elnoopstuw"] = 1`；
3. $s_3 = \tt aaaaaaaaba$，排序后是 $s_3' = \tt aaaaaaaaab$，此时 `mp["aaaaaaaaab"] = 2`；
4. $s_4 = \tt twoplusone$，排序后是 $s_4' = \tt elnoopstuw$，此时 `mp["elnoopstuw"] = 2`；
5. $s_5 = \tt aaaaaaaaba$，排序后是 $s_5' = \tt aaaaaaaaab$，此时 `mp["aaaaaaaaab"] = 3`。

我们知道对于第 $i$ 次出现的字符串 $s$，都可以和前面出现过的 $i-1$ 个与它相同的字符串匹配，所以每次我们都加上 $mp_s - 1$。

需要注意的是，本题需要开 `long long`，原因显然，而且再题面里也说了这一点。


```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

#define rep(i, l, r) for(auto i = (l); i <= (r); i ++)

void solve() {
  map<string, int> mp;
  LL n;
  cin >> n;
  LL cnt = 0;
  rep (i, 1, n) {
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    mp[s]++;
    cnt += mp[s] - 1;
  }
  cout << cnt;
  putchar('\n');
}

signed main(){
  solve();
  return 0;
}
```

---

