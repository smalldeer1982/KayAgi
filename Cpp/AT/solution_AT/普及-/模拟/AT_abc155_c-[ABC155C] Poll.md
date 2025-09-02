# [ABC155C] Poll

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc155/tasks/abc155_c

$ N $ 枚の投票用紙があり、$ i\ (1\ \leq\ i\ \leq\ N) $ 枚目には文字列 $ S_i $ が書かれています。

書かれた回数が最も多い文字列を全て、辞書順で小さい順に出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ S_i $ は英小文字のみからなる文字列 $ (1\ \leq\ i\ \leq\ N) $
- $ S_i $ の長さは $ 1 $ 以上 $ 10 $ 以下 $ (1\ \leq\ i\ \leq\ N) $

### Sample Explanation 1

書かれた回数は `beet` と `vet` が $ 2 $ 回、`beat` と `bed` と `bet` が $ 1 $ 回です。したがって、$ 2 $ 回書かれた `beet` と `vet` を出力します。

## 样例 #1

### 输入

```
7
beat
vet
beet
bed
vet
bet
beet```

### 输出

```
beet
vet```

## 样例 #2

### 输入

```
8
buffalo
buffalo
buffalo
buffalo
buffalo
buffalo
buffalo
buffalo```

### 输出

```
buffalo```

## 样例 #3

### 输入

```
7
bass
bass
kick
kick
bass
kick
kick```

### 输出

```
kick```

## 样例 #4

### 输入

```
4
ushi
tapu
nichia
kun```

### 输出

```
kun
nichia
tapu
ushi```

# 题解

## 作者：zjyqwq (赞：5)

### AT5274 [ABC155C] Poll题解
Pascal题解。

一看这题，感觉有点眼熟。

这不是AT的[AT899 投票](https://www.luogu.com.cn/problem/AT899)吗？
我还发了题解！！！

[~~顺便安利一下我以前的题解~~](https://www.luogu.com.cn/blog/20090703zjy/solution-at899)。

还是回归正题吧。

------------
#### 题意解析
给你 $n$ 个字符串，叫你求出出现频率最高的。


------------
#### 解题思路
c++党有 $map$ ,Pascal党却没有。

但我们能通过排序加上最长平台长度来求出最大的。

但是，这道题的 $n$ 却达到了 $2$ 乘上 $10^5$ ，也就是 $200000$  ,这种大小就只能用快排了。


------------
#### 与AT899 投票的不同
[AT899](https://www.luogu.com.cn/problem/AT899)让我们随便输出一个最大的就好了。而这题却让我们每个都按字典序输出。


------------
#### 输出明细

这题让我们按字典序输出。

那“按字典序输出”是什么意思呢？

就是按字符串的大小排序后输出。

那该怎样处理呢？

我们为了使用最长平台长度，已经将他们排好了。所以，我们只要做两遍最长平台长度，后面的一次，将单个平台数量与第一遍求出的最大值相比，如果一样，输出就好了。


------------
#### 代码
```Pascal

var
n,i,x,max:longint;
t:string;
a:Array[0..1000000]of string;//定义部分，没什么好讲的。
procedure sort(l,r:longint);//快排，也没什么好讲的。
var
i,j:longint;m,t:string;
begin
i:=l;j:=r;m:=a[(i+j)div 2];
while i<=j do
begin
while a[i]<m do inc(i);
while a[j]>m do dec(j);
if i<=j then
begin
t:=a[i];
a[i]:=a[j];
a[j]:=t;
inc(i);
dec(j);
end;
end;
if j>l then sort(l,j);
if i<r then sort(i,r);
end;
 begin
  readln(n);
  for i:=1 to n do
   readln(a[i]);//输入
  sort(1,n);
  for i:=1 to n+1 do
   if a[i]=t then x:=x+1
   else
    begin
     if x>max then begin max:=x;end;
     x:=1;
     t:=a[i];
    end;//第一遍循环，求出最大长度是多少。
  t:='';x:=0;//为了防止一些奇奇怪怪的错误，恢复成原始状态总是好的。
  for i:=1 to n+1 do//为了输出和简易，copy一下再改一改，就好了。
   if a[i]=t then x:=x+1
   else
    begin
     if x=max then begin writeln(t);end;//是最大的，输出输出！！！
     x:=1;
     t:=a[i];
    end;
 end.
```
结束了！！！

---

## 作者：eEfiuys (赞：3)

题目：[AT5274](https://www.luogu.com.cn/problem/AT5274)
### 题意：
输入 $n$ 个字符串，按**字典序**输出**出现次数最多的**。
### 思路：
- 用 **map** 存出现次数，找出最多的；
- 对所有字符串**排序**。
- 输出符合以下条件的字符串：
	- **没有输出过**；
    - **出现次数等于最多次数**。

------------

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[200001];
map<string,int>a; //出现次数。
int num; //最多次数。
map<string,bool>b; //是否输出过。
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		a[s[i]]++;
	}
	sort(s+1,s+n+1); //按照字典序排序。
	for(int i=1;i<=n;i++) //找出最多次数。
		num=max(num,a[s[i]]);
	for(int i=1;i<=n;i++) //按字典序输出。
		if(!b[s[i]]&&a[s[i]]==num) //符合条件（见上）。
		{
			b[s[i]]=1; //改为输出过。
			cout<<s[i]<<endl;
		}
	return 0;
}
```

---

## 作者：cjZYZtcl (赞：2)

## AT5274 [ABC155C] Poll 题解
这题与[AT899 投票](https://www.luogu.com.cn/problem/AT899)几乎一模一样。

[~~顺便安利一下我的AT899 投票的题解~~](https://www.luogu.com.cn/blog/188286/solution-at899)

#### 进入正题。

作为一名C党的程序员，我~~骄傲地~~拿出了C++的map。

我们只需要在读入的时候把当前字符串在map的桶中加一，读入完之后再遍历一遍map即可。

~~蒟蒻楼主现学map遍历~~

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<string, int> a;
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), ans = 0;
	string s;
	for(int i = 1; i <= n; i++){//读入，存入map
		cin>>s;
		a[s]++;
		if(a[s] > ans){//找到出现次数最多的字符串的出现次数
			ans = a[s];
		}
	}
	//接下来与AT899不一样了
	map<string, int>::iterator i;//蒟蒻现学的map遍历
	for(i = a.begin(); i != a.end(); i++){
	    if(i -> second == ans){//如果当前字符串的出现次数是最多的
	        cout<<i -> first<<endl;//输出
	    }
	}
}
```


---

## 作者：StObOtZ (赞：2)

# **AT5274题解报告**

这题跟[AT899 投票](https://www.luogu.com.cn/problem/AT899)非常像！！！

首先还是老规矩，用Map边输入边统计，然后按字典序快排（注意是快排！！！不然会超），最后去重输出就OK了。

**代码如下**
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
string t,s[200005];
bool b[200005];
map<string, int> a;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		a[s[i]]++;
		if(a[s[i]]>ans){
			ans=a[s[i]];
		}
	}
	sort(s+1,s+1+n);
	for (int i=1;i<=n;i++)
	if (a[s[i]]==ans&&s[i]!=s[i-1])	cout<<s[i]<<endl;
}
```


---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

把所有读入的字符串插入`map`里统计，计算map里的最大统计数量。最后枚举`map`里面所有元素；如果这个元素的统计等于最大统计数量则输出这个元素。

最易不需要额外排序结果，应为枚举`map`的时候已经用字典序排序了。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

map<string, int> mpp;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    rep(i, n) {
        string s; cin >> s;
        mpp[s]++;
    }
    int bes = 0;
    for(auto& v:mpp) bes = max(bes, v.se);
    for(auto& v:mpp) {
        if(v.se == bes) cout << v.fi << endl;
    }
}

```

---

## 作者：封禁用户 (赞：0)

# 思路
看到题解区大佬全部用的什么迭代器，指针，本蒟蒻很难受。

我的思路是先使用 `map<string,int> nm;vector<string> v;` 两个东西存放所有的名字以及每一个名字出现的次数。
输入的时候：
```
    for(int i=0;i<n;i++){
        string tmp;
        cin>>tmp;
        nm[tmp]++;
        v.push_back(tmp);
    }
```
注意，我们还要去重，去重前还要先排序！
```
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
```
在 C++ 中 `algorithm` 库中的 `unique`函数 就可以实现去重的功能！

紧接着，我们可以再弄一个 `vector<string> ans;` 用来记录所有票数最高的名字。
```
    int mx=-1;
    for(int i=0;i<v.size();i++){
        mx=max(nm[v[i]],mx);
    }
    for(int i=0;i<v.size();i++){
        if(nm[v[i]]==mx)ans.push_back(v[i]);
    }
```
`mx` 表示最高的票数，第一个循环就是找到 `mx`，第二个循环将所有票数最高的名字存放如 `ans` 中。
由于题目中说：
> Print all strings that are written on the most number of votes, in lexicographical order.
(按字典顺序打印以最高票数记录的所有字符串。)

我们还需要将 `ans` 排序后才能输出。

*小知识:C++ 中的 `sort`  可以自动将字符串数组排序成字典序，而 `iostream` 库 中的（不是`algorithm`  中的，`algorithm` 库中的不行）`max` 和 `min` 可以比较字符串大小，比较其字典序。

接下来，排序输出即可：
```
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<endl;
    }
```

# 完整 Code
```
using namespace std;
int n;  
int main(){
    ios::sync_with_stdio(false);
    map<string,int> nm;
    vector<string> v;
    cin>>n;
    for(int i=0;i<n;i++){
        string tmp;
        cin>>tmp;
        nm[tmp]++;
        v.push_back(tmp);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    vector<string> ans;
    int mx=-1;
    for(int i=0;i<v.size();i++){
        mx=max(nm[v[i]],mx);
    }
    for(int i=0;i<v.size();i++){
        if(nm[v[i]]==mx)ans.push_back(v[i]);
    }
    sort(ans.begin(),ans.end());
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
```

---

