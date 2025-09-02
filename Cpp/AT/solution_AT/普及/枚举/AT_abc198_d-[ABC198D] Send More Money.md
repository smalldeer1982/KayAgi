# [ABC198D] Send More Money

## 题目描述

给你三个由小写字母组成的字符串 $ S_1, S_2, S_3 $。请解出这道覆面算：$ S_1 + S_2 = S_3 $。

具体来说，要求你确定是否存在一组符合以下条件的正整数 $ N_1, N_2, N_3 $，如果存在，请输出其中一个组合：

1. $ N_1, N_2, N_3 $ 分别表示的十进制数字串 $ N'_1, N'_2, N'_3 $ 的长度与对应的字符串 $ S_1, S_2, S_3 $ 的长度相同，并且不含前导零。
2. 满足 $ N_1 + N_2 = N_3 $。
3. 如果 $ S_i $ 的第 $ x $ 个字符和 $ S_j $ 的第 $ y $ 个字符相同，那么 $ N'_i $ 的第 $ x $ 个数字和 $ N'_j $ 的第 $ y $ 个数字也必须相同。

## 说明/提示

- $ S_1, S_2, S_3 $ 是长度在 $ 1 $ 到 $ 10 $ 之间的小写字母字符串。

### 示例解释

在示例 1 中，输出 $ (N_1, N_2, N_3) = (4, 5, 9) $ 是正确的组合，而 $ (1, 1, 2) $ 因不满足条件 3 （例如，字符 `a` 和 `b` 都对应 $ 1 $）因此是错误的。

在示例 2 中，输出 $ (N_1, N_2, N_3) = (3, 3, 6) $ 是一个正确的答案，而 $ (1, 2, 3) $ 因为未满足条件 3（例如，数字 $ 1 $ 和 $ 2 $ 在对应字符 `x` 时不一致）是错误的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
a
b
c```

### 输出

```
1
2
3```

## 样例 #2

### 输入

```
x
x
y```

### 输出

```
1
1
2```

## 样例 #3

### 输入

```
p
q
p```

### 输出

```
UNSOLVABLE```

## 样例 #4

### 输入

```
abcd
efgh
ijkl```

### 输出

```
UNSOLVABLE```

## 样例 #5

### 输入

```
send
more
money```

### 输出

```
9567
1085
10652```

# 题解

## 作者：__little__Cabbage__ (赞：2)

## Solution

由于字符串长度最多只有 $10$，所以考虑暴力枚举。因为每个字母代表一个**个位数**，所以可以枚举 $0 \sim 9$ 的全排列，再对于每一个排列逐一判断是否合法，如果有合法的就输出。一直没有合法的解则输出无解。一个小优化是，如果三个字符串中出现的字母种类数 $>10$，则不可能找到一个合法的排列（因为只有 $10$ 个个位数），这时直接输出无解即可。

在具体的实现上，设 $s = s_1 + s_2 + s_3$（此处的加法表示字符串拼接），我们可以先给 $s$ 种的每种字符一个编号，字符 $c$ 的编号设为设为 $mp_c$，然后对于每个 $0 \sim 9$ 的排列，设当前排列为 $p_0 , p_1 , \dots , p_9$，则字符 $c$ 代表的数字为 $p_{mp_c}$，根据这个算出 $3$ 个数，判断是否满足要求即可。

关于全排列的生成，可以用 STL 里的 `next_permutation()` 函数，不过具体用法这里就不再赘述了。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
#define int long long
#define il inline
using namespace std;
string s1,s2,s3,s;
int mp[200],sz=0;
il bool check_nosol()
{
	int _cnt[200]={},__cnt=0;
	for(char i:s) _cnt[i]=1;
	for(char i='a';i<='z';++i) __cnt+=_cnt[i];
	if(__cnt>10) return 1;
	for(char i='a';i<='z';++i)
		if(_cnt[i])
			mp[i]=sz++;
	return 0;
}
il bool check(int *p)
{
	if(p[mp[s1[0]]]==0 || p[mp[s2[0]]]==0 || p[mp[s3[0]]]==0)
		return 0;
	int a=0,b=0,c=0;
	for(char i:s1)
		a=a*10+p[mp[i]];
	for(char i:s2)
		b=b*10+p[mp[i]];
	for(char i:s3)
		c=c*10+p[mp[i]];
	return a+b==c;
}
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>s1>>s2>>s3;
	s=s1+s2+s3;
	if(check_nosol())
	{
		cout<<"UNSOLVABLE";
		return 0;
	}
	int p[20]={0,1,2,3,4,5,6,7,8,9};
	do
	{
		if(check(p))
		{
			for(char i:s1) cout<<p[mp[i]];
			cout<<'\n';
			for(char i:s2) cout<<p[mp[i]];
			cout<<'\n';
			for(char i:s3) cout<<p[mp[i]];
			cout<<'\n';
			return 0;
		}
	}while(next_permutation(p,p+10));
	cout<<"UNSOLVABLE";
	return 0;
}

```

---

## 作者：loser_seele (赞：1)

不难发现出现的字母数如果超过 $ 10 $ 则显然无解。

否则，因为最多只有 $ 10 $ 个不同字母，于是暴力枚举 $ 10!=3628800 $ 种字母与数字之间的映射是否合法，如果一个映射满足对于三个数 $ a,b,c $ 满足 $ a+b=c $ 且 $ a,b,c $ 均无前导零则合法，直接输出即可。

时间复杂度 $ \mathcal{O}(n! \times n) $，其中 $ n \leq 10 $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
#define int long long
using namespace std;
const int maxm=2e6+5;
int s[maxm];
string a,b,c;
signed main()
{
    cin>>a>>b>>c;
    map<char,int>mp;
    for(auto i:a)
    mp[i]=1;
    for(auto i:b)
    mp[i]=1;
    for(auto i:c)
    mp[i]=1;
    if(mp.size()>10)
    {
        cout<<"UNSOLVABLE";
        return 0;
    }
    for(int i=0;i<10;i++)
    s[i]=i;
    do
    {
        map<char,int>mp2;
        int j=0;
        for(auto i:mp)
            mp2[i.first]=s[j++];
        if(mp2[a[0]]==0||mp2[b[0]]==0||mp2[c[0]]==0)
        continue;
        int x=0,y=0,z=0;
        for(auto i:a)
        x=x*10+mp2[i];
        for(auto i:b)
        y=y*10+mp2[i];
        for(auto i:c)
        z=z*10+mp2[i];
        if(x+y==z)
        {
            cout<<x<<endl;
            cout<<y<<endl;
            cout<<z;
            return 0;
        }
    }while(next_permutation(s,s+10));
    cout<<"UNSOLVABLE";
}
```


---

## 作者：Rainbow_SYX (赞：0)

## 思路
读完题可以发现，个位数最多也只有 $10$ 个，所以直接暴力枚举每一个出现的字符代表哪个个位数，如果字符个数超过 $10$ 一定无解，直接输出 `UNSOLVABLE`。

然后暴力搜索加 `map` 映射字符的值，使用 `next_permutation(a,a+b)` 生成所有的全排列，判断是否满足输出要求即可。

~~总的来说就是一通暴力。~~

时间复杂度 $O(n! \times n)$，可以通过。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
map<char,int> map1;
string a,b,c,x;
int q[200005];
signed main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
    cin>>a>>b>>c;
    x=a+b+c;
    for(char i:x) map1[i]=1;
    if(map1.size()>10) {cout<<"UNSOLVABLE";return 0;}
    for(int i=0;i<10;i++) q[i]=i;
    do
    {
	    int A=0,B=0,C=0,j=0;
        map<char,int> map2;
		 
        for(auto i:map1) map2[i.first]=q[j++];
            
        if(map2[a[0]]==0 || map2[b[0]]==0 || map2[c[0]]==0) continue;
        
        for(char i:a) A=A*10+map2[i];
        for(char i:b) B=B*10+map2[i];
        for(char i:c) C=C*10+map2[i];
        
        if(A+B==C) {cout<<A<<endl<<B<<endl<<C;return 0;}
    }while(next_permutation(q,q+10));
    cout<<"UNSOLVABLE";
}
```

---

## 作者：I_Like_Play_Genshin (赞：0)

还算简单

## Solution

给出一组映射代表一个一个字符代表的个位数使得最终 $s_1, s_2, s_3$ 的映射结果 $x_1, x_2, x_3$ 满足 $x_1+x_2=x_3$。

很简单，时限 $5$ 秒，直接暴力枚举每一个出现的字符代表哪个个位数，如果字符个数大于 $10$ 个，输出 `UNSOLVABLE`。

总时间复杂度为 $\mathcal O(c!\max n)$（$c$ 表示字符数量）。

## Code

代码可以用 DFS 或者 `next_permutation` 来求得映射数组，但是注意后者需要用 `do-while`。

---

## 作者：MAX007_CRN (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc198_d)
## 思路
可以发现，个位数最多也只有 10 个，所以先判断不同的数的数量，如果超过 10 一定无解，直接输出 ```"UNSOLVABLE"``` 。否则用暴力搜索加 ```map``` 映射字符的值，然后生成所有**全排列**判断是否满足要求输出即可。生成全排列可以用 STL 函数                 ```next_permutation(a,a+b)``` 来实现。~~果然，STL 大法好~~。

## 代码：
只贴重要部分，防抄。


```cpp
do { //要用do_while,不然第一个排序遍历不到
		int j = 0;
		map<char, int>mp1;
		for (auto i : mp)
			mp1[i.first] = s[j++];
		if (mp1[a[0]] == 0 || mp1[b[0]] == 0 || mp1[c[0]] == 0)continue;
		int A = 0, B = 0, C = 0;
		for (auto i : a)A = A * 10 + mp1[i];
		for (auto i : b)B = B * 10 + mp1[i];
		for (auto i : c)C = C * 10 + mp1[i];
		if (A + B == C) {
			cout << A << endl;
			cout << B << endl;
			cout << C << endl;
			return 0;
		}
	} while (next_permutation(s, s + 10));
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

暴力枚举，看合不合理。

首先根据题意，如果出现的字符种数大于 $10$，就一定无解。

否则，枚举每一个字母对应的数，检查合不合法即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s1,s2,s3; vector<char>v;
unordered_set<char>s;
vector<int>vl;
unordered_map<char,int>vtv;
inline bool check(){
	if(!vtv[s1[0]]||!vtv[s2[0]]||!vtv[s3[0]]) return 0;
	int v1(0),v2(0),v3(0);
	for(char c:s1) v1=v1*10+vtv[c];
	for(char c:s2) v2=v2*10+vtv[c];
	for(char c:s3) v3=v3*10+vtv[c];
	if(v1+v2==v3) cout<<v1<<'\n'<<v2<<'\n'<<v3<<'\n';
	return (v1+v2==v3);
}
signed main(){
	cin>>s1>>s2>>s3;
	for(char c:s1) s.insert(c);
	for(char c:s2) s.insert(c);
	for(char c:s3) s.insert(c);
	if(s.size()>10) return puts("UNSOLVABLE"),0;
	for(unordered_set<char>::iterator it
		=s.begin();it!=s.end();++it) v.push_back(*it);
	for(int i=0;i!=10;++i) vl.emplace_back(i);
	do{
		for(int i=0;i!=v.size();++i) vtv[v[i]]=vl[i];
		if(check()) return 0;
	}while(next_permutation(vl.begin(),vl.end()));
	return puts("UNSOLVABLE"),0;
} 
```

---

## 作者：Legend_Beaver (赞：0)

## **~~STL大法好~~**

+ **思路$：$** 

数据范围可以暴力，实现代码可以用 STL 大法可以 map 暴力。

1.简单判断一下三个字符串中总的不同字母数量，如果超过 $10$ 显然无解。

2.否则可以枚举每一个字母代表的数，注意处理前缀 $0$，枚举过程通过 next_permutation 实现。

然后看 $0,1,2,3,4,5,6,7,8,9$ 的所有排列，而字母用来对应下标，这样代码实现就会轻松。


+ **code:**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> v(30, 0);//STL
string a, b, c, s;
int cnt, p[10];
map<int, int> ma;//STL

main() {
    cin >> a >> b >> c;
    s = a + b + c;
    for (char i : s)
        v[i - 'a' + 1]++;
    for (int i = 1; i <= 26; i++) {
        if (v[i])
            ma[i] = cnt++;
    }
    if (cnt > 10) {
        cout << "UNSOLVABLE\n";
        return 0;
    }
    for (int i = 0; i < 10; i++)
        p[i] = i;
    while (1) { //一直找直到跳出
        int A = 0, B = 0, C = 0;
        bool f = 1;
        for (int i = 0; i < a.size(); i++) {
            A = (p[ma[a[i] - 'a' + 1]]) + A * 10;
            if (i == 0 && p[ma[a[i] - 'a' + 1]] == 0)
                f = 0;
        }
        for (int i = 0; i < b.size(); i++) {
            B = (p[ma[b[i] - 'a' + 1]]) + B * 10;
            if (i == 0 && p[ma[b[i] - 'a' + 1]] == 0)
                f = 0;
        }
        for (int i = 0; i < c.size(); i++) {
            C = (p[ma[c[i] - 'a' + 1]]) + C * 10;
            if (i == 0 && p[ma[c[i] - 'a' + 1]] == 0)
                f = 0;
        }
        if (f && A + B == C) {
            cout << A << '\n' << B << '\n' << C;
            return 0;
        }
        if (!next_permutation(p, p + 10)) //next_permutation大法好
            break;  // 结束循环
    }
    cout << "UNSOLVABLE";
    return 0;
}

---

## 作者：Crasole (赞：0)

## 题意

给定三个字符串 $S_1 , S_2 , S_3$，每个字符分别代表一个个位数，问：有没有方案可以使得 $S_1 + S_2 = S_3$。如果有则输出具体方案，没有则输出 `UNSOLVABLE`。

## 思路

因为个位数只有 $10$ 个，所以，如果字符的种类超过十个那肯定无解。所以可以在开头特判。

对于剩下的情况。我们可以用 C++ 中的 map 映射每一个字符的值，接着生成所有的排列，判断所有的情况，如果成立就直接输出。

### map 的基本操作

------

- 定义：`map<A,B> m`，`m` 的下标类型为 `A`，存储的值的类型是 `B`。

例：`map<string,int> m`，`m` 的下标类型为 `string`，值的类型为 `int`。

-----

- 赋值：`m[A]=B`，将下标为 `A` 的值赋值成 `B`，如果下标为 `A` 的位置不存在，则会创建的位置，其下标为 `A`，值为 `B`。

例：`m["abc"]=123`，将 `m` 中下标为 `abc` 的值赋成 `123`。

-----

- 查询：`m[A]`，返回 `m` 中下标为 `A` 的值。

例：`cout<<a["abc"]`，输出 `m` 中下标为 `abc` 的值。

-----

- 遍历：

1. 用迭代器来遍历：

```cpp
map<int,int>::iterator it;//定义迭代器it
for(it=m.begin();it!=m.end();it++)//从头到尾
	cout<<it->first<<' '<<it->second<<endl;//first下标的值second存储的值
```

2. 也可以用 C++11 的范围 `for` 循环：

```cpp
for(auto it:m)//遍历m
	cout<<it.first<<' '<<it.second<<endl;
```
---
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//记得开long long 
string s1,s2,s3;
map<char,bool> m;
ll a[15]={0,1,2,3,4,5,6,7,8,9};
bool check(map<char,ll> tm){
	ll n1=0,n2=0,n3=0;
	for(auto i:s1)
		n1=n1*10+tm[i];
	for(auto i:s2)
		n2=n2*10+tm[i];
	for(auto i:s3)
		n3=n3*10+tm[i];
	if(n1+n2==n3){
		cout<<n1<<endl<<n2<<endl<<n3<<endl;
		return 1;
	}
	return 0;
}
int main(){
	cin>>s1>>s2>>s3;
	//现将所有出现过的字符映射到map中 
	for(auto i:s1)
		m[i]=1;
	for(auto i:s2)
		m[i]=1;
	for(auto i:s3)
		m[i]=1;
	if(m.size()>10){//先看一下有没有超过十个 
		cout<<"UNSOLVABLE\n";
		return 0;
	}
	do{//用do-while语句，否则会没有第一次的排列 
		ll i=0;
		map<char,ll> tm;
		for(auto item:m)
			tm[item.first]=a[i++];
		if((tm[s1[0]]==0||tm[s2[0]]==0||tm[s3[0]]==0)) continue;//特判前导零 
		
		if(check(tm)){
			return 0;
		}
	}while(next_permutation(a,a+10));//生成全排列 
	cout<<"UNSOLVABLE\n";
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

## 题目大意
现在有三个字符串，在这三个字符串中，有很多个不同的小写英文字母，这三个字符串不相同的字符代表的数字不相同，现在请问，你是否能找到一个方案，使得代表的数字 $n1,n2$ 和 $n3$ 中，$n1+n2=n3$？
## 思路
我们可以运用爆搜的思想，每次我们枚举每个字母不相同对应的数字，并且在每一次匹配完成之后，检查是否可以成功使得 $n1+n2=n3$ 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
char a[maxn],b[maxn],c[maxn];
char node[maxn];
int idx;
bool vis[maxn],vis1[maxn],flag=false;
int ans[maxn];
void did(char ch){
	vis[ch]=1;
	node[++idx]=ch;
}
bool did2(char ch){
	if(ans[ch]==0){
		return false;
	}
	return true;
} 
void check(){
	int len1=strlen(a+1),len2=strlen(b+1),len3=strlen(c+1);	
	int ansa,ansb,ansc;
	ansa=ansb=ansc=0;
	for(int i=1;i<=len1;++i){
		ansa=ansa*10+ans[a[i]];
		if(i==1 && did2(a[i])==false)return ;
	}
	for(int i=1;i<=len2;++i){
		ansb=ansb*10+ans[b[i]];
		if(i==1 && did2(b[i])==false)return ;
	}
	for(int i=1;i<=len3;++i){
		ansc=ansc*10+ans[c[i]];
		if(i==1 && did2(c[i])==false)return ;
	}
//	cout << ansa << " " << ansb << " " << ansc << endl;
	if(ansa+ansb==ansc && ansa!=0 && ansb!=0){
		cout << ansa << endl << ansb << endl << ansc << endl;
		exit(0);
	}
}
void dfs(int sum,int now){
	if(now==sum){
		check();
	}else{
//		cout << node[now] << endl;
		for(int i=0;i<=9;++i){
			if(now==1 && i==0)continue;
			if(vis1[i]==0){
				ans[node[now]]=i;
				vis1[i]=1;
				dfs(sum,now+1);
				vis1[i]=0;
			}
		}
	}
}
signed main(){
	cin >> a+1 >> b+1 >> c+1;
	int len1=strlen(a+1),len2=strlen(b+1),len3=strlen(c+1);
	for(int i=1;i<=len1;++i){
		if(vis[a[i]]==0){
			did(a[i]);
		}
	}
	for(int i=1;i<=len2;++i){
		if(vis[b[i]]==0){
			did(b[i]);
		}
	}
	for(int i=1;i<=len3;++i){
		if(vis[c[i]]==0){
			did(c[i]);
		}
	}
	if(idx>10 || (len1>len3 || len2>len3)){
		puts("UNSOLVABLE");
		return 0;
	}
	dfs(idx+1,1);
	puts("UNSOLVABLE");
	return 0;
}
```


---

## 作者：max666dong123 (赞：0)

## 思路
这道题不难发现暴搜是可以的，因为时间限制为 $5$ 秒。
而我们可以想到，这 $3$ 个字符串中，最多只能用 **10** 个字母，
否则无论怎么放都会放重。

我们使用全排列来枚举每个字母对应的数字，最后求出看是否
$N_1+N_2=N_3$ 。

## AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
string s1,s2,s3;
map<char,int>num;
map<char,bool>vis;
vector<char>c;
map<int,int>us;
char path[100];
bool f;
void dfs(int x,int n) {
	if(f)return ;
	if(x==n) {
		bool r=0;
		int t1=0,t2=0,t3=0;
		for(int i=0; i<s1.length(); i++) {
			t1=t1*10+num[s1[i]];
			if(i==0&&num[s1[i]]==0) {
				r=1;
				break;
			}
		}
		for(int i=0; i<s2.length(); i++) {
			t2=t2*10+num[s2[i]];
			if(i==0&&num[s2[i]]==0) {
				r=1;
				break;
			}
		}
		for(int i=0; i<s3.length(); i++) {
			t3=t3*10+num[s3[i]];
			if(i==0&&num[s3[i]]==0) {//去掉前导0 
				r=1;
				break;
			}
		}
		if(r){
			return ;
		}
		//cout<<t1<<" "<<t2<<" "<<t3<<endl;
		if(t1+t2==t3&&t1!=0&&t2!=0) {
			f=1;
			cout<<t1<<endl<<t2<<endl<<t3<<endl;
			return ;
		}
		return ;
	}
	for(int i=0; i<=9; i++) {//枚举 
		if(us[i]==0) {//防止不同字母数字相同 
			us[i]=1;
			num[c[x]]=i;
			dfs(x+1,n);
			us[i]=0;
		}
	}
}
signed main() {
	IOS;
	cin>>s1>>s2>>s3;
	for(int i=0; i<s1.length(); i++) {
		if(vis[s1[i]]==0) {
			vis[s1[i]]=1;
			c.push_back(s1[i]);
		}
	}
	for(int i=0; i<s2.length(); i++) {
		if(vis[s2[i]]==0) {
			vis[s2[i]]=1;
			c.push_back(s2[i]);
		}
	}
	for(int i=0; i<s3.length(); i++) {
		if(vis[s3[i]]==0) {
			vis[s3[i]]=1;
			c.push_back(s3[i]);
		}
	}//数字母有多少 
	if(c.size()>10) {//超过10 
		cout<<"UNSOLVABLE"<<endl;
		return 0;
	}
	//cout<<c.size()<<endl;
	dfs(0,c.size());
//	for(int i=0;i<c.size();i++){
//		cout<<c[i]<<" ";
//	}
//	cout<<endl;
//
	if(!f) {
		cout<<"UNSOLVABLE"<<endl;
	}
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题其实并不复杂，我们知道个位数字总共只有十个，那么要是字母数量超过十个直接输出不行。

接下来就可以把每一个字母编一个号，给每一个号枚举一个互不相同的值，去判断合不合法即可。暴力搜索因为最多只有十个位置需要模拟，时间复杂度合法。

注意，开头的数字不能是零，不然会错的。
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int sum[27],cnt,a,b,c,bj[555],jl[555];
string s,t,g;
void dfs(int p,int n){
	if(p>n){
		int sum3=0,sum1=0,sum2=0;
		for(int i=1;i<=a;i++){
			if(i==1 && bj[sum[s[i]]]==0) return;
			sum3=sum3*10+bj[sum[s[i]]];
//			cout<<sum[s[i]];
		}
		for(int i=1;i<=b;i++){
			if(i==1 && bj[sum[t[i]]]==0) return;
			sum1=sum1*10+bj[sum[t[i]]];
//			cout<<sum[g[i]];
		}
		for(int i=1;i<=c;i++){
			if(i==1 && bj[sum[g[i]]]==0) return;
			sum2=sum2*10+bj[sum[g[i]]];
		}
		if(sum3+sum1==sum2) {
			cout<<sum3<<endl<<sum1<<endl<<sum2;exit(0);
		}
		return;
	}
	for(int i=0;i<=9;i++){
		if(jl[i]==0){
			jl[i]=1;bj[p]=i;
			dfs(p+1,n);
			jl[i]=0;
		}
	}
}
signed main(){
	cin>>s>>t>>g;
	s=' '+s,t=' '+t,g=' '+g;
	a=s.size()-1,b=t.size()-1,c=g.size()-1;
	for(int i=1;i<=a;i++) {
		s[i]-='a';
		if(sum[s[i]]==0) cnt++,sum[s[i]]=1;
	}
	for(int i=1;i<=b;i++) {
		t[i]-='a';
		if(sum[t[i]]==0) cnt++,sum[t[i]]=1;
	}
	for(int i=1;i<=c;i++) {
		g[i]-='a';
		if(sum[g[i]]==0) cnt++,sum[g[i]]=1;
	}
	if(cnt>10) return cout<<"UNSOLVABLE",0;
	cnt=0;
	for(int i=0;i<=26;i++){
		if(sum[i]){
			sum[i]=++cnt;
		}
	}
//	cout<<cnt;
	dfs(1,cnt);
	return cout<<"UNSOLVABLE",0;
	return 0;
}
```

---

