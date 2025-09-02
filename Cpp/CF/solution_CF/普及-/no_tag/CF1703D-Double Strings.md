# Double Strings

## 题目描述

You are given $ n $ strings $ s_1, s_2, \dots, s_n $ of length at most $ \mathbf{8} $ .

For each string $ s_i $ , determine if there exist two strings $ s_j $ and $ s_k $ such that $ s_i = s_j + s_k $ . That is, $ s_i $ is the concatenation of $ s_j $ and $ s_k $ . Note that $ j $ can be equal to $ k $ .

Recall that the concatenation of strings $ s $ and $ t $ is $ s + t = s_1 s_2 \dots s_p t_1 t_2 \dots t_q $ , where $ p $ and $ q $ are the lengths of strings $ s $ and $ t $ respectively. For example, concatenation of "code" and "forces" is "codeforces".

## 说明/提示

In the first test case, we have the following:

- $ s_1 = s_2 + s_2 $ , since $ \texttt{abab} = \texttt{ab} + \texttt{ab} $ . Remember that $ j $ can be equal to $ k $ .
- $ s_2 $ is not the concatenation of any two strings in the list.
- $ s_3 = s_2 + s_5 $ , since $ \texttt{abc} = \texttt{ab} + \texttt{c} $ .
- $ s_4 $ is not the concatenation of any two strings in the list.
- $ s_5 $ is not the concatenation of any two strings in the list.

 Since only $ s_1 $ and $ s_3 $ satisfy the conditions, only the first and third bits in the answer should be $ \texttt{1} $ , so the answer is $ \texttt{10100} $ .

## 样例 #1

### 输入

```
3
5
abab
ab
abc
abacb
c
3
x
xx
xxx
8
codeforc
es
codes
cod
forc
forces
e
code```

### 输出

```
10100
011
10100101```

# 题解

## 作者：lizhous (赞：6)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1703D)  
[本家传送门](https://codeforces.com/contest/1703/problem/D)  
## 分析
### 朴素的算法
$O(n^3)$ 枚举三个字符串，判断并输出答案。但是一看数据范围 $1 \le n \le 10^5$，直接 TLE 送走了。
### 优化
~~其实不算优化了，直接重写~~  
题目中专门强调了字符串长度最多为 $8$，我们就以此作为突破口。长度如此短，说明我们可以枚举分割点。分割完后对于左右两边的字符串，分别判断是否在 $s$ 中存在即可。此处可以使用 `map` 存储 $s$ 中的字符串的存在情况，用 `substr` 分割。总时间复杂度 $O(n\log n)$。
## code
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<map>
using namespace std;
string a[100001];
int t, n, ans, nn;
bool ton[26];
map<string, bool> mp;
int main() {
	scanf("%d", &t);
	while (t--) {
		mp.clear();
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) mp[a[i]] = true; //标记字符串存在
		for (int i = 1; i <= n; i++) {
			ans = 0;
			for (int z = 0; z < a[i].size(); z++) { //枚举断点
				if (mp[a[i].substr(0, z)] && mp[a[i].substr(z, a[i].size() - z)]) { //如果存在
					ans = 1; //ans增加
					break; //跳出循环
				}
			}
			cout << ans; //输出
		}
		cout << endl;
	}
}
```


---

## 作者：mzyc_yang2021 (赞：3)

题意：给你一堆字符串，看每一个是否能被此堆中其他任意两个字符串拼出来（可以重复）。

思路：使用朴素算法（即暴力）肯定是不行的，复杂度是输入数量的立方。所以我们可以使用集合或映射来降低时间复杂度。这里主要讲集合（映射代码也会贴出来）。我们将每个字符串都添加进集合中，这时候，朴素算法的三重循环被降低到了二重。这二重，第一重枚举每个字符串，第二重枚举每个字符串的每个字符，我们就以这个字符作为分割点，将这个字符串分成两个子串。我们再来判断两个子串是否在集合里。若两个都在，那说明这个字符串满足条件。

做法解释：我们每次将这个字符串分成两个子串，判断这两个子串是否在集合里（即判断这两个子串是不是可以用来拼字符串的），若两个子串都在集合里，说明这个字符串可以被拼出来，并且打上标记。否则就不能被拼出来，不打标记。

代码（集合，加注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
string str[100010];
int f[100010];
set<string> s;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		s.clear(); // 注意清空集合
		memset(f,0,sizeof(f)); // 还有标志数组
		cin>>n;
		for(int i=1;i<=n;i++){cin>>str[i];s.insert(str[i]);}
		// 如上所说加入集合
		for(int k=1;k<=n;k++)
		for(int i=0;i<str[k].size();i++)
		{
			string q=str[k].substr(0,i),h=str[k].substr(i,str[k].size()); // 分割字符串
			if(s.find(q)!=s.end()&&s.find(h)!=s.end()) f[k]=1; // 若在集合中，就打标记。一表示可以，零则不可以
		}
		for(int i=1;i<=n;i++) cout<<f[i]; // 输出，注意没有空格
		cout<<endl;
	}
	return 0;
}
```
接着是映射：
```cpp
#include<bits/stdc++.h>
using namespace std;
string str[100010];
bool f[100010];
map<string,int> s;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		s.clear(); // 同样注意清空
		memset(f,0,sizeof(f)); // 包括标志数组
		cin>>n;
		for(int i=1;i<=n;i++){cin>>str[i];s[str[i]]=1;} // 添加
		for(int k=1;k<=n;k++)
		for(int i=0;i<str[k].size();i++)
		{
			string q=str[k].substr(0,i),h=str[k].substr(i,str[k].size());
			if(s[q]==1&&s[h]==1) f[k]=1; // 唯一不同的在于判断方式，映射可以直接判断
		}
		for(int i=1;i<=n;i++) cout<<f[i];
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：xiaomuyun (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1703D)

## 题目分析

CF 有一点很好，就是它会提醒你算法的时间复杂度（

> The sum of $n$ over all test cases doesn't exceed $10^5$.

所以 $\mathcal{O}(n^2)$ 是过不了的，这时可以往 $\mathcal{O}(n\log n)$ 的方向想。

可以用一个 map 来存每个字符串是否在 $s_1\cdots s_n$ 中出现过，然后遍历一遍 $1$ 到 $n$。因为符合条件的字符串是由两个字符串拼接组成的，所以只要在当前枚举到的字符串中枚举左边的字符串的长度，同时用 iterator 来维护右边的字符串，每次看一看是不是枚举出来的两条字符串都在 $s_1\cdots s_n$ 中出现过，出现过直接输出 `1` 并 `break` 即可。

关于 iterator 可以看我的[这篇文章](https://www.luogu.com.cn/blog/324350/iterator-and-STL-traversal)

## 代码实现
```cpp
#include<iostream>
#include<string>
#include<cstdio>
#include<map>
using namespace std;
int t,n;
string s[100001];
map<string,bool> mp;
int main(){
	scanf("%d",&t);
	while(t--){
		mp.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			cin>>s[i];
			mp[s[i]]=true;
		}
		for(int i=1;i<=n;++i){
			string t="",u=s[i];//维护左右两个字符串
			bool flag=false;
			for(int j=0;j<s[i].length();++j){
				t+=s[i][j],u.erase(u.begin());//每次左边多一个字符，右边少一个字符
				if(mp[t]&&mp[u]){//如果两个字符串都存在，就输出答案，说明可行
					printf("1");
					flag=true;
					break;
				}
			}
			if(!flag) printf("0");
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：ZhanPJ (赞：0)

**题目简述：**

给出 $n$ 个字符串，你需要判断字符串 $s_i$ 能否有两个字符串 $s_j$ 和 $s_k$ 相加组成。其中 $j \not = i , k \not = j$。

---

**解题思路：**

刚看到开始题目的数据量十分的大，$t \leq 10^4$，$n \leq 10^5$ 的数据范围可以看到不可能枚举 $s_j$ 和 $s_k$。（这样的时间复杂度是 $O(n^2)$，完全超时）。

那么我们要针对字符串“下手”。通过题面中强调了 $s_i$ 的长度不超过 $8$，那么在枚举 $s_i$ 的拆分最多只有 $8$ 种可能（包含）。那么枚举 $s_i$ 的拆分去寻找 $s_j,s_k$。

$s_i$ 的拆分一直按 $8$ 种计算，那么所有的拆分时间复杂度仅仅为 $O(8 \cdot n)$。接下来我们要尝试使用 $O(1)$ 的算法去寻找 $s_j,s_k$。在这里我使用了 map。（这是由红黑树实现的容器）

```map<string,bool> strs;```

这样我们就可以使用 $O(\log n)$ 的时间复杂度去查找 $s_j,s_k$ 和插入 $s_x$。

---

**AC 代码：**

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#pragma GCC optimize(2)//O2优化
using namespace std;
string s[100050];
map<string,bool> strs;
string a,b;
int main(){
	int T,n;bool flag;
	scanf("%d",&T);
	while(T--){
		strs.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			cin>>s[i];
			strs[s[i]]=1;
		}
		for(int i=1;i<=n;i++){
			flag=0;
			for(int j=1;j<s[i].length();j++){
				a="";b="";
				for(int k=0;k<j;k++)a+=s[i][k];
				for(int k=j;k<s[i].length();k++)b+=s[i][k];
				if(strs[a]&&strs[b]){flag=1;printf("1");break;}
			}
			if(!flag)printf("0");
		}
		printf("\n");
	}
	
	return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

# 题面翻译
输入 $n$ 个字符串，对于每个字符串，判断能否由其余字符串中任意两个拼接而成。
# 前置知识
## map
map 是 STL 库中的一个容器，可以看作一个数组。
不同点是 map 可以支持任意类型的下标，如负数，字符串等。     
map 单次查询复杂度 $\mathcal{O}(\log n)$。
## string
string 即字符串，支持相加。具体使用请查看本题代码。
# 题目分析
朴素的暴力枚举算法显然会超时。我们考虑更快的比较方式，即利用 map 进行比较。    
题目中规定字符串长度不超过 $8$，非常短，所以我们可以暴力枚举不同的分割方案，使用一个结构体储存每一个字符串，用 map 记录字符串是否出现过，将分割后的字符串用 string 储存，代入 map 中查询即可。时间复杂度为 $\mathcal{O}(n\log n)$。此题得解。     
**注意：本题有多组数据。**
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
struct edge{
	string s;
}e[100005];
map <string,bool> mp;//以字符串为下标的map 
string str="";
signed main(){
	int T=read();
	while(T--){
		int n=read();
		for(int z=1;z<=n;z++){
			cin>>e[z].s;
			mp[e[z].s]=1;
		}
		bool v=0;
		for(int i=1;i<=n;i++){
			v=0;
			for(int z=0;z<(e[i].s).length()-1;z++){
				str="";
				for(int j=0;j<=z;j++){
					str=str+e[i].s[j];//string相加 
				}
				if(!mp[str]){
					continue;
				} 
				str="";
				for(int j=z+1;j<(e[i].s).length();j++){
					str=str+e[i].s[j];//string相加 
				}
				if(!mp[str]){
					continue;
				} 
				cout<<1;
				v=1;
				break;
			}
			if(!v){
				cout<<0;
			}
		}
		cout<<endl;
		mp.clear();//清除map数据 
	}
}
```


---

## 作者：hmzclimc (赞：0)

## 题意大意
原题传送门在这 [CF](https://codeforces.com/contest/1703/problem/D) [Luogu](https://www.luogu.com.cn/problem/CF1703D)

给你几个字符串，问每一个字符串能不能拆分成另外两个字符串。

注意，一个字符串可以拆分为两个相同的字符串。

## 思路

注意范围，可以发现 $t$ 和 $n$ 都不小，但是每个字符串的长度都很小。

也就是说，我们可以开一个 `std::map` 来记录一个字符串是否存在，然后枚举一下每个字符串，来判断是否可行。

另外，最好优化一下常数，~~我才不会告诉你我没优化卡了好几次~~。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
#include<map>
using namespace std;
int t;
const int maxn=100005;
inline string cut(string x,int from,int end){
    string ret(""); //把一个字符串切开
    for(int i=from;i<=end;i++){
        ret=ret+x[i];
    }
    return ret;
}
map<string,bool> vis;
string str[maxn];
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t-->0){
        vis.clear(); // 记得清空 map
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>str[i];
            vis[str[i]]=true; // 读入并标记这个字符串存在
        }
        for(int i=1;i<=n;i++){ //枚举每个字符串
            bool ans=false;
            for(int j=0;j<str[i].size()-1;j++){ //一位一位的来把它拆开判断
                ans|=(vis[cut(str[i],0,j)]&&vis[cut(str[i],j+1,str[i].size()-1)]);
                // 只要可以把它拆开就把 ans 标记为 true
                if(ans){
                    cout<<1;
                    break;// 可以直接 break
                }
            }
            if(!ans){
                cout<<0;
            }
        }
        cout<<"\n";
    }
    return 0;
}
```

---

谢谢观看，本人是菜鸡，如发现有问题，请指出，谢谢。

---

## 作者：zhicheng (赞：0)

### 思路

这个题如果直接枚举每一个字符串进行判断，因为 $n$ 是 $10^5$ 级别的，枚举肯定不行。我们需要找一个很小的量进行枚举。

注意到字符串的长度很小，所以我们枚举除了第一个以外的每一个字符，将字符串从它的前面断开，查找分开后两段是否都存在。这个查找操作可以通过 `map` 实现。而断开操作可以用 `substr` 实现。

#### 关于 map

1. 是一个 STL 容器，可以将一种类型的数据映射为另一种类型，也可以看做一个能以不同类型数据（不只是自然数）作为下标的数组。

2. 用法：
   * 声明： `map<类型一,类型二> map名字`；
   
   * 使用： `map名字[类型一]=类型二`。

#### 关于 substr

1. C++ 内置的 `string` 截取函数；

2. 用法：
   * 原型： `substr(size_type __pos = 0, size_type __n = npos)`
   
   * 意义： 
      * `__pos`: 截取的起始位；
      
      * `__n`: 截取的长度，留空则为截取到末尾。
### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string p[100010],q,w;
map<string,bool>mapp;
int main(){
	int n,a,r;
	scanf("%d",&n);
	while(n--){
		mapp.clear();  //记得多测清空
		scanf("%d",&a);
		for(int i=1;i<=a;i++){
			cin>>p[i];
			mapp[p[i]]=1;  //事先将每个字符串存入
		}
		for(int i=1;i<=a;i++){
			r=0;
			for(int j=1;j<=p[i].length()-1;j++){  //枚举
				q=p[i].substr(0,j);  //substr:截取j个
				w=p[i].substr(j);  //截取到末尾
				if(mapp[q]&&mapp[w]){  //两个子串都存在
					printf("1");
					r=1;  //记得打标记
					break;
				}
			}
			if(r==0){
				printf("0");  //没找到
			}
		}
		printf("\n");
	}
}
```

---

## 作者：NATO (赞：0)

### 题意简述：
给定 $n$ 个字符串，求每个字符串是否可以被其他两个字符串（可以是两个相同字符串）拼成，如果可以，输出 $1$，否则输出 $0$，最后构成一个长度为 $n$ 的 $01$ 串并输出。

### 解法分析：
因为每个字符串长度最大为 $8$，因此，我们可以枚举每种拆分情况来判断。

用一个映射用来判断拆分出的字符串是否是输入的字符串，拆分可以用 ```substr()```（使用方法：两个参数，第一个为拆分起点，第二个为拆分长度，如果只有第一个参数，默认拆分到字符串结尾。比如一个字符串 ```s=abcd```，那么 ```s.substr(0,3)``` 就会返回字符串 ```abc```。详细可参考[这篇博客](https://blog.csdn.net/weixin_42240667/article/details/103131329)）。循环每个字符串枚举拆分位置即可（为了节省时间可以在判断该字符串能被拆分后停止枚举）。

#### 参考代码：
```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
ll t,n;
map<string,ll>a;
string b[100005];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;a.clear();
		for(ll i=1;i<=n;++i)
			cin>>b[i],a[b[i]]=1;
		for(ll i=1;i<=n;++i)
		{
			bool flag=0;
			for(ll j=1;j<b[i].size();++j)
				if(a.find(b[i].substr(0,j))!=a.end()&&a.find(b[i].substr(j))!=a.end())
				{
					flag=1;break;
				}
			cout<<flag;
		}
		cout<<'\n';
	}	
}
```


---

## 作者：Buried_Dream (赞：0)

## 题意：

给你 $n$ 个字符串 $s_i$，判断 $s_i$ 是否能被另外两个字符串拼接而来。

## Solution

注意到字符串的 $len \le 8$。

我们先用一个 map 在读入的时候判断该字符串出现过。

然后我们对于每一个字符串，枚举每一个分割的位置，把他分割成两个字符串，判断这两个字符串是否出现过就行。

```cpp
map <string, bool > mp;
string s[N];
int vis[N];
void Main() {
	mp.clear();
	int n = read();
	string tot = "";
	for(int i = 1; i <= n; i++) cin >> s[i], mp[s[i]] = 1, vis[i] = 0;
	for(int i = 1; i <= n; i++) {
		int len = s[i].size();
		bool f = 0;
		for(int j = 0; j < len; j++) {
			string s1 = s[i].substr(0, j);
			string s2 = s[i].substr(j);
			if(mp[s1] && mp[s2]) f = 1;
		}
		
		if(f) vis[i] = 1;
	}
	for(int i = 1; i <= n; i++) printf("%d", vis[i]);
	printf("\n");
}
signed main() 
{
	int T = read();
	while(T--) Main();
	return 0;
}


---

