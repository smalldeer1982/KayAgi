# Dorms War

## 题目描述

Hosssam decided to sneak into Hemose's room while he is sleeping and change his laptop's password. He already knows the password, which is a string $ s $ of length $ n $ . He also knows that there are $ k $ special letters of the alphabet: $ c_1,c_2,\ldots, c_k $ .

Hosssam made a program that can do the following.

1. The program considers the current password $ s $ of some length $ m $ .
2. Then it finds all positions $ i $ ( $ 1\le i<m $ ) such that $ s_{i+1} $ is one of the $ k $ special letters.
3. Then it deletes all of those positions from the password $ s $ even if $ s_{i} $ is a special character. If there are no positions to delete, then the program displays an error message which has a very loud sound.

For example, suppose the string $ s $ is "abcdef" and the special characters are 'b' and 'd'. If he runs the program once, the positions $ 1 $ and $ 3 $ will be deleted as they come before special characters, so the password becomes "bdef". If he runs the program again, it deletes position $ 1 $ , and the password becomes "def". If he is wise, he won't run it a third time.

Hosssam wants to know how many times he can run the program on Hemose's laptop without waking him up from the sound of the error message. Can you help him?

## 说明/提示

In the first test case, the program can run $ 5 $ times as follows: $ \text{iloveslim} \to \text{ilovslim} \to \text{iloslim} \to \text{ilslim} \to \text{islim} \to \text{slim} $

In the second test case, the program can run $ 2 $ times as follows: $ \text{joobeel} \to \text{oel} \to \text{el} $

In the third test case, the program can run $ 3 $ times as follows: $ \text{basiozi} \to \text{bioi} \to \text{ii} \to \text{i} $ .

In the fourth test case, the program can run $ 5 $ times as follows: $ \text{khater} \to \text{khatr} \to \text{khar} \to \text{khr} \to \text{kr} \to \text{r} $

In the fifth test case, the program can run only once as follows: $ \text{abobeih} \to \text{h} $

In the sixth test case, the program cannot run as none of the characters in the password is a special character.

## 样例 #1

### 输入

```
10
9
iloveslim
1 s
7
joobeel
2 o e
7
basiozi
2 s i
6
khater
1 r
7
abobeih
6 a b e h i o
5
zondl
5 a b c e f
6
shoman
2 a h
7
shetwey
2 h y
5
samez
1 m
6
mouraz
1 m```

### 输出

```
5
2
3
5
1
0
3
5
2
0```

# 题解

## 作者：Withershine (赞：5)

不好意思，把这道题的通过率拉低了，但坑点确实有。

## 思路
多出几个数据，我们可以发现，在不报警的前提下，最多可以操作数量是**两个特殊字符间的最长距离**。

### 解释
对于不报警的定义是：每次删除操作进行前，当前的字符串中的**所有**特殊字符的前一个位置必须**不是**特殊字符。

换句话说，只要当前字符串的**任意一个**特殊字符前仍有不是特殊字符的字符，就不会报警。

所以找到初始字符串中两个特殊字符间的最长距离，就是最多操作次数。设这两个字符的位置分别是 $i$，$j$，满足 $1 \le i < j \le n$，那么最长操作数量就是 $j - i$。

为什么不是 $j - i + 1$ 呢？因为操作到第 $j - i$ 次时，距离最长的这两个特殊字符都已经贴在一起了，下一次操作必定会报警，故最长操作数量是 $j - i$。

## 代码
吐槽一句，原先的两篇题解给出的代码都超时了，别问我怎么知道的。

### 细节
在输入时，如果直接将 $k$ 个字符读入的话会超时（不知道怎么回事）。因此在读入 $k$ 时加了一点小优化，将后面的空格符也读入。（~~在这里被卡了好久，以后再也不想用 `cin` 了。~~）

### 代码实现
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(register ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(register ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    register ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll T , n , k;
char s[100005] , ch;
ll t[27] , last , max_dis;
signed main()
{
    T = read();
    while(T--)
    {
        max_dis = 0;
        fr(i , 0 , 26)
        {
            t[i] = 0;
        }
        n = read();
        scanf("%s" , s + 1);
        k = read();
        fr(i , 1 , k)
        {
            scanf("%c" , &ch);
            getchar();
            t[ch - 'a'] = 1;
        }
        last = 1;
        fr(i , 1 , n)
        {
            if(t[s[i] - 'a'])
            {
                max_dis = max(max_dis , i - last);
                last = i;
            }
        }
        printf("%lld\n", max_dis);
    }
    system("pause");
	return 0;
}
```


---

## 作者：ssSSSss_sunhaojia (赞：2)

[**原题传送门**](https://www.luogu.com.cn/problem/CF1670B)
# 思路：
题目中报错的定义我们可以理解为不存在任何一个**位置不在第一位的特殊字符**，即**除第一位外其他位置上的特殊字符均已被删去**。而当一个特殊字符被删去当且仅当它被它后面第一个特殊字符删去。于是，题目就变成了**求任意两个中间没有其他特殊字符的特殊字符的最长距离**（要算上第一个特殊字符与位置 $1$ 的距离）。

# 实现方法：
我们把整个字符串从前往后扫一遍，遇到一个特殊字符时，计算它与上一个特殊字符的距离并更新答案，再将下一个特殊字符的上一个字符更新为它。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL T, n, k, lst, ans, f[220]; 
char s[110000], ch;  
int main() {
    IOS;
    cin >> T; 
    while(T --) {
        cin >> n >> s + 1;
        cin >> k; 
        for(re char i = 'a'; i <= 'z'; i ++) f[i] = 0; 
        for(re int i = 1; i <= k; i ++) cin >> ch, f[ch] = 1; 
        lst = 1; ans = 0; 
        for(re int i = 1; i <= n; i ++)
            if(f[s[i]]) ans = max(ans, i - lst), lst = i; 
        cout << ans << "\n"; 
    }   
    return 0;
}
```

---

## 作者：Cloud_Umbrella (赞：1)

当你看了简化版的题意，你会发现没那么难。

## 简化题意

“每次可以删掉 $s$ 中所有特殊字符之前相邻的一个元素，当最后存留下来的特殊字符前都没有相邻元素时，再删除就会报错”。报错其实就是结束，如若一个特殊字符前一个不是特殊字符，就一直删。这不就是两个特殊字符的最大距离吗？注意，中间不能有其他特殊字符。

## 分析

只需用一个变量 $last$ 表示上一个特殊字符的位置，如若又找到，相减得到它们之间的距离，用 $\max$ 更新答案，顺手更新一下 $last$，就完成了。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;//静态定义
int f[220]; 
char s[N];  
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);//读入优化，拒绝scanf和printf
    int T;
    cin>>T; 
    while(T--){
    	int n,k;
        cin>>n>>s>>k;
        memset(f,0,sizeof(f));//多测不清空，请人T-1行泪
        for(int i=0;i<k;i++){
        	char c;
        	cin>>c;
        	f[c]=1; //记录特殊字符
        }
        int last=0,ans=-1; //找最大，定义成最小
        for(int i=0;i<n;i++){
            if(f[s[i]]){
            	ans=max(ans,i-last);//更新最大值
            	last=i; //更新特殊字符的位置
            }
        }
        cout<<ans<<"\n"; 
    }   
    return 0;//好习惯伴终生
}
```

---

## 作者：ttq012 (赞：1)

**Solution**

简单题。

容易发现，第 $i$ 个特殊字符在追到第 $i - 1$ 个特殊字符的右边第一个元素的时候就会消失，所以第 $i$ 个特殊字符“活着”的时候进行的操作数量就是这一个字符和第 $i-1$ 个特殊的字符的距离。

距离的定义：假设第 $i$ 个特殊的字符的下标为 $x_1$，第 $i - 1$ 个特殊的字符的下标为 $x_2$，那么这两个特殊的字符的距离就是 $x_1 - x_2$。

注意：第 $1$ 个特殊的字符的操作是它自己的下标！如果没有特殊的字符输出 $0$！

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int k;
    cin >> k;
    vector <char> arr(k);
    map <char, bool> alp;
    for (int i = 0; i < k; i ++)
        cin >> arr[i];
    for (int i = 0; i < k; i ++)
        alp[arr[i]] = true;
    vector <int> id;
    for (int i = 0; i < n; i ++)
        if (alp[s[i]])
            id.push_back(i);
    if (id.empty()) {
        puts("0");
        return ;
    }
    int ans = id[0];
    for (int i = 1; i < (int) id.size(); i ++)
        ans = max(ans, id[i] - id[i - 1]);
    cout << ans << '\n';
}

signed main() {
    // freopen (".out", "w", stdout);
    int T;
    cin >> T;
    while (T --)
        solve();
    return 0;
}

```


---

## 作者：zhengenzhe (赞：0)

## 【题目大意】
给定一个长度为 $n$ 的字符串 $s$，再给 $k$ 个特殊字符。每次可以删掉 $s$ 中所有特殊字符之前相邻的一个元素，当最后存留下来的特殊字符前都没有相邻元素时，再删除就会报错。

求：最多的操作次数。

换句话说就是当 $k$ 个特殊字符前没有其他字符才能操作，反之则不行。因此 $ans$ 就等于**相邻两个特殊字符的最大距离。** （注意多测要清空！！！！）
## 【思路】
综上，我们可以用一个变量 $f$ 记录上一次特殊字符出现的下标，再与这次进行比较，并更新 $ans$。
## Code：
```c++
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN=1e6+1;
ll T,n,k,f,ans=-0x3f3f3f;
bool F[MAXN]={false};
char s[MAXN],To_Get;
namespace IO {//快速读入
    const int MAXR = 10000000;
    char _READ_[MAXR], _PRINT_[MAXR];
    int _READ_POS_, _PRINT_POS_, _READ_LEN_;
    inline char readc() {
    #ifndef ONLINE_JUDGE
        return getchar();
    #endif
        if (!_READ_POS_) {
            if (feof(stdin)) return -1;
            _READ_LEN_ = fread(_READ_, 1, MAXR, stdin);
        }
        char c = _READ_[_READ_POS_++];
        if (_READ_POS_ == _READ_LEN_) _READ_POS_ = 0;
        return c;
    }
    template<typename T> inline int read(T &x) {
        x = 0; register int flag = 1, c;
        while (((c = readc()) < '0' || c > '9') && c != '-')
            if (c < 0) return -1;
        if (c == '-') flag = -1; else x = c - '0';
        while ((c = readc()) >= '0' && c <= '9') x = x * 10 - '0' + c;
        x *= flag; return 0;
    }
}
using namespace IO;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//输入输出优化
	read(T);
	while(T--){
		f=0;
		ans=-0x3f3f3f;//赋为一个最小值以确保能被覆盖
		read(n);
		cin>>s>>k;
		for(ll i=0;i<k;i++){
			cin>>To_Get;
			F[To_Get]=true;
		}
		for(ll i=0;i<n;i++){
			if(F[s[i]]==true){
				if(i-f>ans){//更新答案
					ans=i-f;
				}
				f=i;
			}
		}
		printf("%lld\n",ans);
		memset(F,0,sizeof(F));//多测不清空，亲人两行泪
	}
	return 0;
}
```

---

## 作者：haozinojc (赞：0)

## 思路：

在这道题中，我们不妨把字符分为两类：**特殊字符**和**其他字符**。

根据题意可知，当所有特殊字符前没有其他字符时，就不能继续操作了。

所以我们就只用算出**相邻两个特殊字符的最大距离**就可以愉快的切掉这道题了。

**注：多组数据测试，记得初始化。**

## 代码：

```cpp

#include<bits/stdc++.h>
#define in inline
#define LL long long
#define re register
using namespace std;
LL T,n,k,last,ans,f[220]; 
char s[110000],ch;  
int main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>T; 
    while(T--){
        cin>>n>>(s+1)>>k;
        for(re char i='a';i<='z';i++)f[i]=0; 
        for(re int i=1;i<=k;i++){
        	cin>>ch;
			f[ch]=1; 
		}
        last=1;ans=0; 
        for(re int i=1;i<=n;i++){
            if(f[s[i]]){
            	ans=max(ans,i-last);
				last=i;
			}
		}
        cout<<ans<<"\n"; 
    }   
    return 0;
}

```

---

## 作者：YG_King (赞：0)

直接上思路。

因为要删 **最长距离**，那么什么叫最长距离呢？最长距离，其实就是两个特殊字符之间的距离，我们只需要对所有相邻的两个特殊字符的距离取 $\max$ 就是答案。

### code：
```
#include<bits/stdc++.h>
using namespace std;

char s[100010];
void solve(){
	map<char,int>mp;
	int n,k;
	cin>>n>>s>>k;
	for(int i=1;i<=k;i++){
		char c;
		cin>>c;
		mp[c]=1;
	}
	int mx=0,nxt=0;
	for(int i=0;i<n;i++){
		if(mp[s[i]]){
			mx=max(mx,i-nxt);
			nxt=i;//记录上一次的特殊字符
		}
	}
	cout<<mx<<'\n';
}
int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
} 
```


---

## 作者：JOKER_chu (赞：0)

题确实简单，但是坑点很多：

坑点 $1$：报错的定义

当**最后**存留下来的**特殊字符**前都没有**相邻**元素时，再删除就会报错，换句话说，就是**特殊字符不能相邻**（反正我是这么理解的）

坑点 $2$：最长距离的定义（此处参考第一篇题解）

思考发现：**最大操作数就是两个特殊字符的间距取最大值**

如果一个字符的位置是 $a$，第二个为 $b$ 那么答案就与 $\max(a,b)  - \min(a,b)$ 取最大值，而不用加 $1$，因为再删一个的话，两个特殊字符就相邻报错了

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, l;
string a;
char f;

int main(){
	ios::sync_with_stdio(0), cin.tie(0); // 不加这个会超时 
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> m >> a >> l;
		map<char, bool>cnt; // 局内定义 map 不用清空 
		for(int j = 1; j <= l; j++){
			cin >> f;
			cnt[f] = 1; // 将特殊字符标记 
		}
		int ans = 0, syg = 0; // 定义答案，上一个特殊字符所在位置 
		for(int i = 0; i < m; i++){
			if(cnt[a[i]] == 1){
				ans = max(ans, i - syg); // 统计距离，答案 
				syg = i; // 标记特殊字符 
			}
		}
		cout << ans << '\n'; // 输出答案 
	}
	return 0;
}
```

---

## 作者：zzy0618 (赞：0)

### 题目简化大意

求一个字符串 $s$ 中特殊字符的最大“距离”。此处的 $a,b$ 的距离指 $b$ 的下标减去 $a$ 的下标。

### 题目分析

因为我们可见，第 $i$ 个特殊字符每次操作会一直消耗它之前的字符，直到上一个特殊字符 $i-1$。所以直到连最大距离间的字符都被删除完了，所以才会报错。这里有一点贪心的思想。由此，题目简化的大意就被解释了。

我们用一个 $mp$ 记录特殊字符，发现每一个特殊字符的位置储存，去打擂台取最大值。但要注意字符串中没有特殊字符是要输出 $0$。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, i;
string a;
char ch;
int s[100001], cnt;
int main() {
	cin >> t;
	while (t--) {
		map<char, bool>mp;//记录特殊字符 
		memset(s, 0, sizeof(s)); cnt = 0;//清空记录位置的数组 
		cin >> n >> a >> m;
		for (i = 1; i <= m; i++) {
			cin >> ch;
			mp[ch] = true;
		}
		for (i = 0; i < a.size(); i++)
			if (mp[a[i]])
				s[++cnt] = i;//统计 
		if (cnt == 0) {
			cout << 0 << endl;
			continue;
		}//注意特判 
		int ans = s[1];
		for (i = 2; i <= cnt; i++) {
			ans = max(ans, s[i] - s[i - 1]);
		}//取最大值 
		cout << ans << endl;
	}
	return 0;
}
```


---

