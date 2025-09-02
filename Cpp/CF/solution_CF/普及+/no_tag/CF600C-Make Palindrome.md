# Make Palindrome

## 题目描述

A string is called palindrome if it reads the same from left to right and from right to left. For example "kazak", "oo", "r" and "mikhailrubinchikkihcniburliahkim" are palindroms, but strings "abb" and "ij" are not.

You are given string $ s $ consisting of lowercase Latin letters. At once you can choose any position in the string and change letter in that position to any other lowercase letter. So after each changing the length of the string doesn't change. At first you can change some letters in $ s $ . Then you can permute the order of letters as you want. Permutation doesn't count as changes.

You should obtain palindrome with the minimal number of changes. If there are several ways to do that you should get the lexicographically (alphabetically) smallest palindrome. So firstly you should minimize the number of changes and then minimize the palindrome lexicographically.

## 样例 #1

### 输入

```
aabc
```

### 输出

```
abba
```

## 样例 #2

### 输入

```
aabcd
```

### 输出

```
abcba
```

# 题解

## 作者：wanggk (赞：6)

回文串有一个特性：

- 长度为奇数：中间是单个的，其他成对向外扩散。（只有一个字母为奇数个）
- 长度为偶数：成对向外扩散。

所以要尽量两两凑成一样的。令 $ans$ 数组为最终答案要用到的字符。

统计在原字符串中每个字母出现的个数，每出现两个一样的直接加到 $ans$ 里；其他不一样的，需要改变某一些字母使得他们和其他字母能保持一致，再加入 $ans$ 。

又因为要字典序最小，所以 $ans$ 需要在处理一下，最终输出 $ans2$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ct=0;
int cnt[27];
char ans[200005];
char ans2[200005];
int main()
{
	cin>>s;
	for(int i=0;i<s.size();i++) cnt[s[i]-'a']++;
	int l=0,r=s.size()-1;
	for(int i=0;i<26;i++) for(int j=1;j<=cnt[i]/2;j++) ans[l++]=ans[r--]=i+'a';
	for(int i=0;i<26;i++)
		if(cnt[i]%2&&l<=r)
			ans[l++]=ans[r--]=i+'a';
	sort(ans,ans+s.size());
	int l2=0,r2=s.size()-1;
	for(int t=0;t<s.size();)
	{
		if(ans[t]==ans[t+1]) ans2[l2++]=ans2[r2--]=ans[t],t+=2;
		else ans2[(s.size()-1)/2]=ans[t++];
	}
	for(int i=0;i<s.size();i++) cout<<ans2[i];
	return 0;
}
```


---

## 作者：EdenSky (赞：4)

# [CF600C Make Palindrome](https://www.luogu.com.cn/problem/CF600C)
- [更好的阅读体验](https://www.cnblogs.com/wanguan/p/16745745.html)

## 题意

有一串字符串 $S$，设改变 $S$ 中的任意一个字符称为 1 次转变（交换任意 2 个字符不算转变次数），求在操作最少的情况下可得到的回文字符串

## 正文

对于一个回文串，有两种情况：

1. 回文串字符数为偶数，如 `assddssa`，易得其中每种字符数量都是偶数。

2. 回文串字符数为奇数，如 `asdfdsa`，易得其中除了最中间的字符数量为奇数，其余都是偶数。

再想到排序是不算转变次数的，很容易想到桶排序。

将 $S$ 中的每个字符对应的桶加 1，通过上述规律可以知道，每个为偶数的桶不需要转变，每个为奇数的桶执行以下操作：

去掉一个字符使桶为偶数，将去除的字符留下备用，而接下来就是对这些字符进行转变，见例子。

```txt
字符串：
aesdffdaa
桶排后：
31122
aesdf
操作后的桶：
20022
aesdf
剩余字符：
aes
```

设剩下的字符按字典序排序后组成的字符串为 $B$，长度为 $a$。

1. 若 $a$ 为偶数，则将靠后的字符变成靠前的字符，由于要使转变次数最少，容易发现一个方法：令 $B_i$ 和 $B_{a-i+1}$ 配对，将 $B_{a-i+1}$ 变成 $B_i$，最后把获得的字符串加入桶，按照字典序输出。这可以在最少次数的转变下将 $S$ 变成一个字典序最小的回文串。

2. 若 $a$ 为奇数，方法和上一个差不多，只对最中间的字符不操作并保存即可。

当然，可能会有人对 2 有疑惑，为什么不选择排头的字符或末尾的呢？

请看（红名请略过）：

```txt
字符串：
asdfghgfd
桶排后：
112221
asdfgh
剩余字符（按字典序排）：
ahs
若选择排头：
 转换：ahh
 回文串：dfghahgfd
若选择末尾：
 转换：aas
 回文串：adfgsgfda
若选择中间：
 转换：aha
 回文串：adfghgfda
```

很显然，**选中间所得的回文串字典序更小**。

输出是这样的：

1. 若回文串长度为偶数，由于回文串是先后对应的，只需要在所有桶中先从头到尾输出一半，再从尾到头输出剩下的即可。

2. 若为奇数，先在所有桶中从头到尾输出一半，再输出中间的字符，最后再从头到尾输出剩下的即可。

理论讲了一大堆，上代码思路和代码：

按 ASCII 从小到大开辟一些桶，将输入的字符串桶排，然后从小到大对每个桶进行操作。蒟蒻自认为有一种~~巧妙的方法~~，就是弄一个队列，对于每个为奇数的桶切下一个字符压入，由于这是按 ASCII 从小到大操作，所以后面出队的字符也是按 ASCII 从小到大排的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[205],num;
queue<char>q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	char a;
	while(cin>>a){
		++c[a];//桶排
	}
	for(int i=1;i<=200;++i){
		if(c[i]%2==0)	continue;//若为偶数，略过
		++num;//统计字符串长度
		q.push(i);//若为奇数，保存
		//由于所有桶是按字典序排的，所以保存的字符也是按字典序排列的
		//队列的特性
	}
	
	if(num%2==0){//其实无需计算设下的字符数，易得若S长度为偶数，则剩下的字符数也是偶数
		for(int i=1;i<=num/2;i++){
			c[q.front()]+=2;//将靠后的转变为靠前的，并加入桶
			q.pop();
		}
		for(int i=1;i<=200;++i){
			for(int j=1;j<=c[i]/2;j++){
				cout<<(char)i;//输出
			}
		}
		for(int i=200;i>=1;--i){
			for(int j=1;j<=c[i]/2;j++){
				cout<<(char)i;
			}
		}
		return 0;
	}
	else{
		for(int i=1;i<=num/2;i++){
			c[q.front()]+=2;
			q.pop();
		}
		for(int i=1;i<=200;++i){
			for(int j=1;j<=c[i]/2;j++){
				cout<<(char)i;
			}
		}
		cout<<q.front();//输出中间的
		for(int i=200;i>=1;--i){
			for(int j=1;j<=c[i]/2;j++){
				cout<<(char)i;
			}
		}
		return 0;
	}
}//撒花
```
[提交记录](https://www.luogu.com.cn/record/87648573)，华丽结束。

---

## 作者：linyihdfj (赞：3)

## C.Make Palindrome ##
### 题目描述： ###
[原题面](https://codeforces.com/contest/600/problem/C)
### 题目分析： ###
因为排列这个字符串不算做操作次数，所以我们不用在意这些字符的排列方式，只需要记录一下这个字符串里每个字母有多少个就可以了。

考虑一个回文串就是最多只有一个字母的个数是奇数，为了使得操作最小我们就只能将奇数的字母变化为奇数的字母，这样就可以将这两个字母变成偶数也就是可以回文了。

为了让最后的字典序最小很显然我们要将尽量大的数变成尽量小的数，就直接逆序然后顺序扫就可以了。注意输出的时候要按照字典序将字母从小到大按规定个数输出，如果存在字母个数为奇数要在中间输出
### 代码详解： ###

```
#include<bits/stdc++.h>
using namespace std;
int cnt[26];
int main(){
	string s;
	cin>>s;
	for(int i=0; i<s.size(); i++){
		cnt[s[i] - 'a']++;
	}
	for(int i=25; i>=0; i--){
		if(cnt[i] & 1){
			for(int j=0; j<=25; j++){
				if(cnt[j] & 1){
					cnt[j]++;
					cnt[i]--;
					break;
				}
			}
		}
	}
	int flag = -1;
	for(int i=0; i<=25; i++){
		if(cnt[i] & 1){
			flag = i;
		}
	}
	stack<char> st;
	for(int i=0; i<=25; i++){
		for(int j=1; j<=cnt[i]/2; j++){
			cout<<char(i + 'a');
			st.push(char(i + 'a'));
		}
	}
	if(flag != -1){
		cout<<char(flag + 'a');
	}
	while(!st.empty()){
		cout<<st.top();
		st.pop();
	}
	return 0;
}

```
因为回文串的后半部分相当于前半部分的逆序所以直接拿个栈就可以了。

---

## 作者：xunhuanyihao (赞：2)

### CF600C Make Palindrome
我们可以开一个桶来记录每个字符出现的次数，然后考虑每个字符，如果出现了偶数次，直接加在答案的头和尾即可，如果出现了奇数次，则分两种情况讨论：

1. 如果能找到另一个没有考虑过的字符也出现了奇数次，就将一个那种字符改变成这个字符，这样两种字符都出现了偶数次，加到答案头尾即可。
2. 找不到另一个没有考虑过的字符出现了奇数次，那么先将这种字符出现次数 $-1$ 放入答案头尾，再将剩下的一个字符放在答案中间，维持回文性质。

可以证明，第二种情况最多只会出现一次，故没有重复问题。

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
char s[N], ans[N];
int n, c[30];
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    int tot = 0;
    for (int i = 1; i <= n; i++) c[s[i] - 'a']++;
    for (int i = 0; i < 26; i++) {
        if (c[i] & 1) {
            for (int j = 1; j <= c[i] / 2; j++) ans[++tot] = 'a' + i, ans[n - tot + 1] = 'a' + i;
            int p = -1;
            for (int j = 25; j > i; j--) {
                if (c[j] & 1) {
                    p = j;
                    break;
                }
            }
            if (p == -1) ans[n / 2 + 1] = 'a' + i;
            else c[p]--, ans[++tot] = 'a' + i, ans[n - tot + 1] = 'a' + i;
        } else {
            for (int j = 1; j <= c[i] / 2; j++) {
                ans[++tot] = 'a' + i;
                ans[n - tot + 1] = 'a' + i; 
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i];
    puts("");
    return 0;
}
```

---

## 作者：maokaiyu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF600C)
## 思路
我们可以根据贪心的思想，只改变出现次数为奇数的字符，这样操作次数必然是最优的。对于修改字符，我们从 `a` 到 `z` 遍历，如果当前字符出现了奇数次，我们就从 `z` 到 `a` 遍历第一个同样出现奇数次的字符**不能是当前字符**。这样，字典序必然是最小的。
## 做法
用循环求出字符出现次数，再循环进行修改，最后输出。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
char s[200010];
I n,w[30],use[30];
I main(){
	scanf("%s",s + 1);
	n = strlen(s + 1);
	for(I i = 1;i <= n;i++){//统计字符数 
		w[s[i] - 'a']++;
	}
	for(I i = 'a';i <= 'z';i++){
		if(w[i - 'a'] % 2 && !use[i - 'a']){//出现次数为奇数，且未被修改 
			use[i - 'a'] = 1;
			for(I j = 'z';j > i;j--){
				if(!use[j - 'a'] && w[j - 'a'] % 2){//找到第一个未被修改的字符 
					w[j - 'a']--;
					w[i - 'a']++;
					use[j - 'a'] = 1;
					break;//修改完毕，退出 
				}
			}
		}
	}
	for(I i = 'a';i <= 'z';i++){//先输出前一半，从a开始 
		for(I j = 1;j <= w[i - 'a'] / 2;j++){
			printf("%c",i);
		}
	}
	for(I i = 'a';i <= 'z';i++) if(w[i - 'a'] % 2) printf("%c",i);//可能有额外一个出现了奇数次 
	for(I i = 'z';i >= 'a';i--){//反着要从z开始 
		for(I j = 1;j <= w[i - 'a'] / 2;j++){
			printf("%c",i);
		}
	}
	return 0;
}
```

---

## 作者：OIer_Hhy (赞：0)

这题显然贪心。

我用了一个双指针枚举。

当两个字母均为奇数个时，把一个字典序较大的改成较小的。

代码如下，不懂看注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
char a[maxn+20];
int b[128];
int n;
signed main(){
	cin>>a;
	n=strlen(a);
	for(int i=n;i>=1;i--) a[i]=a[i-1]; // 强迫症
	for(int i=1;i<=n;i++) b[a[i]-96]++; // 桶计数
	if(!(n&1)){ // 长度为偶数
		int l=1,r=26; // 双指针枚举奇数个
		while(l<=r){
			while(!(b[l]&1)&&l<=26) l++;
			while(!(b[r]&1)&&r>=1) r--;
			b[l]++;
			b[r]--;
		}
     // 以下输出
		for(int i=1;i<=26;i++){
			for(int j=1;j<=(b[i]>>1);j++) cout<<char(96+i);
		}
		for(int i=26;i>=1;i--){
			for(int j=1;j<=(b[i]>>1);j++) cout<<char(96+i);
		}
	}else{ // 长度为奇数
		int l=1,r=26;
		while(l<r){
			while(!(b[l]&1)&&l<=26) l++;
			while(!(b[r]&1)&&r>=1) r--;
			b[l]++;
			b[r]--;
		}
      // 以下输出
		for(int i=1;i<=26;i++){
			for(int j=1;j<=(b[i]>>1);j++) cout<<char(96+i);
		}
		cout<<char(96+l);
		for(int i=26;i>=1;i--){
			for(int j=1;j<=(b[i]>>1);j++) cout<<char(96+i);
		}
	}
	return 0;
}

```

---

## 作者：liuyuanpei (赞：0)

本题条件说可以改变 $s$ 中任意多个字母，还可以改变 $s$ 中各个字母的排列顺序。很显然我们要先考虑字母的排列顺序，再对排好序的 $s$ 中不符合回文串的字母进行改变。

对于排序，我们进行桶排序。将每个字母放入桶中，记录每个字母出现的个数。

对于构造，以为回文串都是两两对应的对称形式，所以先头尾构造两两相同成对的，接着改变部分字母使其构成回文串，最后输出。

CODE：
```cpp
# include <iostream>
# include <cmath>
# include <cstring>
# include <string>
# include <algorithm>
# include <stack>
# include <queue>
# include <vector>
# include <set>
# include <map>
using namespace std;
char s[1000005];
int tong[100];//26个字母的桶 
char tmp[1000005];
char ans[1000005];
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio (false);
    cin.tie(NULL);
    cout.tie(NULL);
	cin >>s;
	int g=0;//元素个数 
	for(int i=0;s[i];i++) 
		tong[s[i]-'a']++,g++;//桶排序
	int l=0,r=g-1;
	for(int i=0;i<26;i++){
		for(int j=1;j<=tong[i]/2;j++) 
			tmp[l++]=tmp[r--]=i+'a';
	}//构造已经两两成对的字母 
	for(int i=0;i<26;i++){
		if(tong[i]%2==1&&l<=r)
			tmp[l++]=tmp[r--]=i+'a';
	}//对于两两分组还多一个的字母，进行改变，继续构造 
	sort(tmp,tmp+g);//将大致构造的字符串进行排序 
	int ll=0,rr=g-1;
	for(int i=0;i<g;i++){
		if(tmp[i]==tmp[i+1]) ans[ll++]=ans[rr--]=tmp[i],i++;//放入答案 
		else ans[(g-1)/2]=tmp[i];//对于为一的无法配对的放最中间 
	}
	for(int i=0;i<g;i++) 
		cout <<ans[i];//输出 
	cout <<endl;
	return 0;
}
```




---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF600C)

------------
# 题意：
给定一个只包含小写字母的字符串，你可以修改任意位置的字符（变换为 $a$ 到 $z$ 中任一个）。

然后重新排列字符串。现在要求用最少次数的修改得到一个回文串，若有多种方案，输出字典序最小的方案。

------------
# 思路：
对于长度为偶数的字符串显然好说，我们只需开一个桶记录下a-z分别有多少个。

偶数个的前后分别输出个数除以 $2$ 次即可。

奇数个的两两匹配，分别输出前面的个数除以 $2$ 加 $1$ 次，输出后面的的个数除以 $2$ 次即可。

对于长度为奇数的的字符串我们发现有一部分字符串是不输出（被替换掉的）。

我们在不输出的中和剩余的唯一的奇数个字符中找最小的填入序列中间即可。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long 
const int N=1e6+10;
char a[N],b[N];
int n,m,k,x,y,c[N],d[N];
signed main(){
    scanf("%s",a+1);
	n=strlen(a+1);
    for(int i=1;i<=n;i++){
    	c[a[i]-'a']++;
	}
    for(int i=0;i<26;i++){
    	if(c[i]&1){
    		d[++m]=i;
		}
	}
    for(int i=0;i<26;i++){
    	x+=c[i];
	}
    if(x&1){
        b[(n>>1)+1]='a'+d[(m>>1)+1];
        c[d[(m>>1)+1]]--;
		m--;
    }
    for(int i=0;i<26;i++){
        for(int j=(c[i]>>1);j>=1;j--){
            y++;
            b[n-y+1]=b[y]='a'+i;
        }
        if(c[i]&1){
            k++;
            if(k<=m){
                y++;
                b[n-y+1]=b[y]='a'+i;
                m--;
            }
        }
    }
    for(int i=1;i<=n;i++){
    	cout<<b[i];
	}
    return 0;
}
```
完结撒花~

---

## 作者：wang_freedom (赞：0)

### 思路:
当回文串长度为奇数时：最中间的字符在回文串中总共有奇数个。

当回文串长度为偶数时：所有字符在回文串中都总共有偶数个。

所以我们用一个 $cnt$ 数组来统计每个字母在字符串中出现的次数，当出现两个一样的直接加到 $ans$  里。

其他不一样的，需要改变某一些字母使得他们和其他字母能保持一致，再加入 $ans$。

由于答案要求字典序最小，所以在对 $ans$ 进行排序，将排序后的新 $ans$ 输出。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define endl '\n'
#define pii pair<int,int>
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
string s;
int cnt[26],l,r;
char ans[200005],ans2[200005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>s;
	rep(i,0,s.size()-1){
		cnt[s[i]-'a']++;
	}
	r=s.size()-1;
	rep(i,0,25)
		rep(j,1,cnt[i]/2)
			ans[l++]=ans[r--]=(char)i+'a';
	rep(i,0,25)
		if(cnt[i]%2&&l<=r)
			ans[l++]=ans[r--]=i+'a';
	sort(ans,ans+s.size());
	int l2=0,r2=s.size()-1;
	for(int t=0;t<s.size();){
		if(ans[t]==ans[t+1]){
			ans2[l2++]=ans2[r2--]=ans[t];
			t+=2;
		}
		else
			ans2[(s.size()-1)/2]=ans[t++];
	}
	rep(i,0,s.size()-1)
		cout<<ans2[i];
	return 0;
}
/*

*/

```

---

## 作者：hxhhxh (赞：0)

## 大意

给定一个字符串，可以任意改变字符顺序，花费一代价改变一个字符。在花费最少代价将字符串变成回文的前提下，使结果字典序最小。

## 思路

字符串顺序没有用，就可以使用一个桶记下来。让后分长度的奇偶性讨论：

---

### 偶数长度

因为要让代价最小，所以有偶数个的字符就不要管它了。对于有奇数个的字符，一定可以让它们（奇数次数的字符）配对，才能使得代价最小。

为了让字典序最小，应该尽量增加尽量小的字符的个数。最后答案的前半段就是字符从 `a` 到 `z` 每一种字符 `cnt[i]/2` 次，后一半就反过来。

### 奇数长度

大部分和上面同理，但是一定会剩下一种字符。这时我们希望所有这种字符比其他的字符都要大，且尽量小。我们可以让最大和最小配对，最后在中间剩下的那个就是多出来的。

答案中间要加那个字符。

---

其实两种情况在代码上就是一种情况里面特判。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T,cnt[30],l=1,r=26,ccnt;
char ch[200005],ans[200005];
int main(){
	cin>>ch+1;
	n=strlen(ch+1);
	for(int i=1;i<=n;i++) cnt[ch[i]-'a'+1]++;
	while(l<r){
		while(cnt[l]%2==0&&l<26) l++;
		while(cnt[r]%2==0&&r>1) r--;
		if(l>=r) break;
		cnt[l]++;
		cnt[r]--;
	}
	char ch=' ';
	for(int i=1;i<=26;i++){
		for(int j=1;j*2<=cnt[i];j++) ans[++ccnt]=char(i+'a'-1),ans[n-ccnt+1]=char(i+'a'-1);
		if(cnt[i]&1) ans[n/2+1]=char(i+'a'-1);
	}
	cout<<ans+1;
	return 0;
}
```

听说题解里要 $ \LaTeX $ 。

---

## 作者：cold_cold (赞：0)

 [安利一波博客](https://www.cnblogs.com/cold-cold/p/10080808.html)

题意：给定一个只包含小写字母的字符串，你可以修改任意位置的字符（变换为a-z中任一个）

然后重新排列字符串。现在要求用最少次数的修改得到一个回文串，若有多种方案，输出字典序最小的方案。



- **对于长度为偶数的字符串显然好说**

我们只需开一个桶记录下a-z分别有多少个

偶数个的前后分别输出 个数/2次 即可

奇数个的两两匹配，分别输出前面的 个数/2+1次，输出后面的的 个数/2次 即可


- **对于长度为奇数的的字符串我们发现有一部分字符串是不输出的（被替换掉的）**

我们在不输出的中 和 剩余的唯一的奇数个字符中找最小的填入序列中间即可


实现如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=200010;
char a[N],cun[N];
int n,book[30],dan[N],ge,ji,all=0,us=0,fla;
int main()
{
//    freopen("input","r",stdin);
//    freopen("output","w",stdout);
    scanf("%s",a+1);n=strlen(a+1);
    for(int i=1;i<=n;i++) book[a[i]-'a']++;
    for(int i=0;i<26;i++) if(book[i]&1) dan[++ge]=i;
    for(int i=0;i<26;i++) all+=book[i];
    if(all&1)
    {
    	cun[(n>>1)+1]='a'+dan[(ge>>1)+1];
    	book[dan[(ge>>1)+1]]--;ge--;
	}
	for(int i=0;i<26;i++)
	{
		for(int j=(book[i]>>1);j>=1;j--)
		{
			++us;
			cun[n-us+1]=cun[us]='a'+i;
		}
		if(book[i]&1)
		{
			++ji;
			if(ji<=ge)
			{
				++us;
				cun[n-us+1]=cun[us]='a'+i;
				ge--;
			}
		}
	}
	for(int i=1;i<=n;i++) printf("%c",cun[i]);
    return 0;
}
/*

*/
```

---

