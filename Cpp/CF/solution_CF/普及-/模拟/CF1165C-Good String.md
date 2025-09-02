# Good String

## 题目描述

Let's call (yet again) a string good if its length is even, and every character in odd position of this string is different from the next character (the first character is different from the second, the third is different from the fourth, and so on). For example, the strings good, string and xyyx are good strings, and the strings bad, aa and aabc are not good. Note that the empty string is considered good.

You are given a string $ s $ , you have to delete minimum number of characters from this string so that it becomes good.

## 样例 #1

### 输入

```
4
good
```

### 输出

```
0
good
```

## 样例 #2

### 输入

```
4
aabc
```

### 输出

```
2
ab
```

## 样例 #3

### 输入

```
3
aaa
```

### 输出

```
3

```

# 题解

## 作者：ivoleuoy (赞：1)

考试考挂了，写篇题解以祭之。

------------
题目: [link](https://www.luogu.com.cn/problem/CF1165C)

### 题意 :
给定一个字符串，要求删除最少的字符数，使得每个奇数位的字符和它后面的那个字符都不相同，且最后剩余的字符串的长度为偶数 。

### 思路：
按位判断每个奇数位的字符是否要被删去。

但是问题就在于删掉一个字符后，后面字符对应的下标的奇偶性会发生改变，所以要通过取模 $flag$ ,判断是否要改变，且 $flag$ 的值只会在 `0` 与  `1` 之间。

如果它是需要被删去的，就将它标记，最后输出没有被标记过的字符就可以啦。
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
string s;
int vis[N],flag,ans,cnt,n;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch))	{if(ch=='-'){f=-1;}ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return x*f;
}
int main()
{
	n=read();cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(i%2==flag)
		{
			if(s[i]==s[i+1])
			{
				vis[i]=1;//vis数组表示这一位是否被删去了 
				flag^=1;
				ans++;//ans表示要被删去的字符的总长 
			}
			else cnt++;//cnt就对应不需要被删去的长度 
		}
		else cnt++;
	}
	if(cnt%2==1)//如果最后是奇数 就要再删去一位 
	{
		vis[s.size()-1]=1;ans++;
	}
	printf("%d\n",ans);
	for(int i=0;i<s.size();i++)
	{
		if(!vis[i]) cout<<s[i];
	}
	return 0;
}
```


---

## 作者：猜一猜我是谁 (赞：1)

# 思路
逐位判断每个奇数位是否要删除。每个数字删除后，对应的下标会发生改变，所以要通过取模一个变量 $m$，$m$ 的值在 0 和 1 之间变换。最后通过判断每个数字是否被删除来输出。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
bool f[200010];
int n,ans,m;
int main(){
    cin>>n>>s;
    for(int i=0;i<n;i++)
        if(i%2==m){
            if(i<n-1&&s[i]==s[i+1]) ans++,m=m^1,f[i]=1;
            if(i==n-1) ans++,f[i]=1;
        }
    cout<<ans<<endl;
    for(int i=0;i<n;i++)
        if(!f[i]) cout<<s[i];
}
```

---

## 作者：pandaSTT (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1165C)

## 思路

题目让我们判断每一个奇数位上的字符串是否需要删除，但需要注意的是当删除一个字符，后面字符的下标的奇偶性就要变，而且由于字符串的下标是从 0 开始存的，所以小标就行的判断应该是反的才行哦，剩下的就是模拟啦

## 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  string s,ans;//ans存储删除完数字的最终字符串
  int tot,len,mod;//mod用来判断下标的奇偶性
  int main(){
      cin>>len>>s;
      for(int i=0;i<len;i++){
          if(i%2==mod){//注意这里奇数性是反的
              if(i+1<len&&s[i]==s[i+1]){//判断是否需要删除这个字符 
                  tot++;
                  mod=(mod+1)%2;//删除这个字符，后面字符的下标的奇偶性就要变哦 
              }
              else if(i+1==len){
                  tot++;
              }
              else{
                  ans+=s[i];
              }
          }
          else{
              ans+=s[i];
          }
      }
      cout<<tot<<endl<<ans;
      return 0;
  }
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1165C)

## 思路

看一眼数据范围，可以直接跑循环。

直接用循环跑，看一看奇数位要不要删除。

但还有一个问题，就是下标。

这个问题好解决，直接用一个数判断前面的位置是否是奇数位。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
char s[N];
bool f[N];
int main()
{
	int n,m=0;
	int sum=0;
    cin>>n>>s;
    for(int i=0;i<n;i++)
	{
        if(i%2==m)
		{
            if(i<n-1&&s[i]==s[i+1]) 
            {
                sum++;
                m=(m+1)%2;
                f[i]=1;
            }
            if(i==n-1) 
            {
                sum++;
                f[i]=1;
            }
        }
    }
    cout<<sum<<"\n";
    for(int i=0;i<n;i++)if(!f[i])cout<<s[i];
    cout<<"\n";
    return 0;
}
```


---

## 作者：zhoukaixiang (赞：0)

# 题目分析
这个题目有一个字符串，要求删除最少的字符数量，使得每一个奇数位置的字符都不等于它后面的那个字符。逐位判断每个奇数位是否要删除。 所以我们必须保证奇数字符与它后一个字符不相等相邻，因为相邻的元素相同必定让奇数位置的字符与它后面的那个字符相等。然后判断若剩余位数为奇数，则删除最后一位，再遍历字符串输出个数和新的字符串。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
  int n, f;
  char pos;
  cin >> n >> s;
  pos = s[0];
  f = 1; 
  for(int i = 1; i < n; i ++)//保证奇数字符与它后一个字符不相等
  {
    if(f == 1)
      if(pos == s[i])  s[i] = '-';//s[i]为-代表这个位置字符需要删除
      else f = 0;
    else  pos = s[i], f = 1;
  }
  f = 0;
  for(int i = 0; i < n; i ++)
    if(s[i] == '-')  f ++;
  if((n - f) % 2 == 1)//若剩余位数为奇数，去除最后一个字符
    for(int i = n - 1; i >= 0; i --)
      if(s[i] != '-')
      {
        s[i] = '-', f ++;
        break;
      }
  cout << f << "\n";
  for(int i = 0; i < n; i ++)
    if(s[i] != '-')
      cout << s[i];
  return 0;
}
```


---

## 作者：JustinXiaoJunyang (赞：0)

此题与 [CF1140B](https://www.luogu.com.cn/problem/CF1140B) 重名，危……难度差不多。

前排芝士：

Q：字符串索引是怎样的？

A：如果较真的话，在 NOIP 大型考试大多从 `0` 开始，本题不例外。建议我们在处理时采用 `i < s.length()` 来做循环条件。因为在空字符串时，我们系统小于是可以避免 RE 的，比 
`i <= s.length() - 1`， `i` 变成 `-1` 保险。 

思路分析：

有一个字符串，要求删除最少的字符数量，使得每一个奇数位置的字符都不等于它后面的那个字符。

判断每个奇位是否要删。每个字符删除后，下标会变。所以要取模一个变量 $m$，这个 $m$ 的值是 `0` 或 `1` 之间。

通过判断每个字符是否被删除决定输出，就靠取模 $m$。

这里判断奇数位就是索引 $\bmod2=m$ ，考虑代码的话就是 `^= 1` （异或）。

参考代码：

[AC 记录](https://www.luogu.com.cn/record/69759658)，给核心代码～


```cpp
if (i % 2 == mod)
{
    if (i < n - 1 && s[i] == s[i + 1]) ans++, m ^= 1, flag[i] = 1;
    if (i == n - 1) ans++, flag[i] = true;
}

---

## 作者：Luo_gu_ykc (赞：0)

## 题目大意

给定一个字符串，你要删除最少的字符，使字符串中下标为奇数的字符不等于他后面的字符，最后输出最后剩下的字符。

## 思路

枚举字符串，如果有下标为奇数且与后一个字符相等的数，就把它标记，最后输出没有被标记过的即可。

注意本题有个大坑点，就是最后的字符串长度不能为奇数；
而且字符删除后下标会发生改变。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, cnt, sum;
bool f = 0, v[200005];
string s, a;
int main(){
	cin >> n >> s;
	for(int i = 0; i < s.size(); i++){
		if(i % 2 == f){
			if(s[i] == s[i + 1]){ // 需要删除
				f = !f; // 下标会变，所以要取反
				sum++;
				v[i] = 1; // 标记
			} else{
				cnt++; // 计算剩余的长度
			}
		} else {
			cnt++;
		}
	}
	if(cnt % 2 == 1){ // 为奇数
		v[s.size() - 1] = 1; // 删掉最后一位
		sum++;
	}
	cout << sum << "\n";
	for(int i = 0; i < s.size(); i++){
		if(!v[i]){ 
			cout << s[i];
		}
	}
	return 0;
}

---

## 作者：hanyaxin (赞：0)

循环遍历一遍，判断奇数位是否要删，但这样有个问题，如果要删，那么每一位的下标也会变，所以我定义一个数，判断当前位置是否是奇数。

看代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
string s;
bool f[N];
int n, ans, m;
int main() {
	cin >> n >> s;
	for (int i = 0; i < n; i++) {
		if (i % 2 == m) {
			if (i < n - 1 && s[i] == s[i + 1]) 
			{
				ans++;
				m=(m+1)%2;
				f[i] = 1;
			}
			if (i == n - 1) 
			{
				ans++;
				f[i] = 1;
			}
		}
	}
	cout << ans << endl;
	for (int i = 0; i < n; i++)
		if (!f[i]) cout << s[i];
	return 0;
}
```

---

## 作者：iiawaKL (赞：0)

# ~~dalao~~写题解啦

%%orz Benq

刚刚模拟了一下div3，A和B都是水体，C还行吧，看上去很难，但是想通了以后就可以很简单搞定。

### 我们可以先算一下样例，见下->

|  | 是否奇数位 | 要不要换 |
| -----------: | -----------: | -----------: |
| a | √ | √ |
| a | × | × |
| b |  √|×  |
| c | × | × |


看完这个就应该懂了吧，所以，我们可以暴力循环，然后就可以暴力算了。最后看位数是否为偶，如果是奇数，就再删掉最后一位。

 _Code->_ 
 
 ```
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
bool vis[200010];
int main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	int cnt=0;
	for(int i=0;i<n;i++){
		if(i+1<n&&s[i]==s[i+1]&&(i-cnt)%2==0){
			cnt++;
			vis[i]=1;
		}
	}
	if((s.size()-cnt)%2)vis[s.size()-1]=1,cnt++;
	cout<<cnt<<endl;
	for(int i=0;i<s.size();i++){
		if(!vis[i])cout<<s[i];
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：A_Big_Jiong (赞：0)

# 题意
一个字符串，若满足长度为偶数，第k和第k+1个（k为奇数）字符不同，那么我们称之为这个字符串为 Good String，如果不是，那么最少删除几个字符可以将其转换为 Good String。输出删除的次数和删除后的字符串 

## 略谈思路

先读入并维护，保证没有相同的字符相邻。

然后删除最后一位，输出个数和新的字符串

# 直接上代码
**请见注释**
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<vector>
#include<string>//头文件
using namespace std;
const int maxn=200005;
int n,len;//len为现在字符串的长度，通过边读边判断来读入字符串
char str[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
    	cin>>str[++len];//读入第k个字符
    	if(i<n)  cin>>str[++len],i++;//读入第k+1个
    	else i++;//如果最后k没有后面的k+1，就啥也不读
		while(str[len-1]==str[len]&&i<n){
			cin>>str[len];
			i++;
		}//疯狂while，直到新读入的两个字符不同
	}
	if(str[len]==str[len-1])  len--; //如果最后一位与其前一位相同，去掉最后一位，请见样例3
    printf("%d\n",n-(len%2==0?len:--len));//判断len是否是个位数，并计算总删除次数
    for(int i=1;i<=len;i++)  printf("%c",str[i]);
    printf("\n");
	return 0;
}
```


---

