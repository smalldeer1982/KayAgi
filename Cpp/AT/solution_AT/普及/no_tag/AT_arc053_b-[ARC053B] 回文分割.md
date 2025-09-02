# [ARC053B] 回文分割

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc053/tasks/arc053_b



# 题解

## 作者：紫题 (赞：11)

记录字符串中每个字符出现的次数$s_i$

如果$s_i$为偶数，那么这些字符i就可以和别的回文串拼在一起变成更长的回文串

如果$s_i$为奇数，那就必须从i中拿一个出来作为某个回文串的中间字符

比如$S=aabbb$ 一个b要在中间 而剩下的可以和这个b合在一起 变成 $abbba$或者$babab$

容易发现，$s_i$中有多少个为奇数，最少就可以分成几个串

知道最少可以分成几个串以后枚举长度即可

$update :$不用枚举长度，答案即为【比$len/num$大的最小奇数$-2$】除一下即可

$Code:$

```cpp
include<cstdio>
#include<cstring>
char str[100010];
int ed[30], num;
int main() {
	scanf("%s", str);
	for(int i = strlen(str)-1; i >= 0; i--) ++ed[str[i]-'a'];
	for(int i = 0; i < 26; i++) num += ed[i]&1;
    if(!num) printf("%d\n", strlen(str));
    else printf("%d\n", ((strlen(str)/num+1)|1)-2);
    return 0;
}
```


---

## 作者：jbc392 (赞：2)

题意：给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
返回 s 所有可能的分割方案。

示例:

输入：aab

输出：3

解释：aba

思路：

记录字符串中每个字符出现的次数si 

如果si为偶数，那么这些字符i就可以和别的回文串拼在一起变成更长的回文串

如果si为奇数，那就必须从i中拿一个出来作为某个回文串的中间字符

容易发现，si中有多少个为奇数，最少就可以分成几个串

知道最少可以分成几个串以后枚举长度即可

可得以下AC代码：

```
#include<bits/stdc++.h>
using namespace std;
int a[30],p,i;
int main(){
    string s;
    cin>>s;//输入
    int l=s.size();//求串长
    for(i=0;i<l;i++)a[s[i]-'a']++;//拼起来
    for(i=0;i<26;i++)p+=a[i]%2;
    if(!p){//特判p=0
        cout<<l;
        return 0;//退出很重要，否则会输出其他东西
    }
    for(i=1;p*i<=l;i+=2);//枚举长度
    cout<<i-2;//输出
    return 0;//好习惯
}
```
##  _[My Blog](https://www.cnblogs.com/jbc666/)_ 

---

## 作者：wzm2007 (赞：1)

    记录字符串中每个字符出现的次数s
    若s为偶,那么这些字符就可以和别的回文拼在一起变成更长的回文
    若s为奇,那就必须从中拿一个出来作为某个回文串的中间字符
    易知s中有多少个是奇,最少就可以分成几个串,之后枚举长度

------------

    #include<bits/stdc++.h>
    using namespace std;
    int main()
    {
        int a[100],num=0;
        string s;
        memset(a,0,sizeof(a));
        cin>>s;
        for(int i=0;i<s.length();i++)a[s[i]-'a'+1]++;  //累计每个字符个数
        for(int i=1;i<=26;i++)
            if(a[i]&1)num++;  //累计奇数的个数
        if(!num)cout<<s.length(); //特殊判断
        else //枚举
            for(int i=1;;i+=2)
                if(num*i>s.length())
                {
                    cout<<i-2;
                    break;
                }
        return 0;
    }

---

## 作者：BrandonSoong (赞：1)

# AT1877 回文分割（自我总结）
***
## 题目：
高桥君有字符串S。S只由英语小写字母组成。

首先，高桥将S的文字按任意顺序排列，制作字符串S'。

接着，高桥在任意位置分割S'为几个回文子串S1，S2...SN

把各Si的长度的最小值作为X.求X的最大值。

数据范围:1≦|S|≦105

样例：

1：
in:rokovoko out:3

2：
in:tomtom out:6

3：
in:vwxyz out:1

4：
in:succeeded out:3
***
## 思路：
1、因为可以打乱顺序，所以不用考虑顺序的事情，故可以拉通操作

2、我要想知道最大的最短字回文串的长度，就要知道能至少有几个回文子串

3、要尽量少产生回文子串（因为要尽量多算出单个最大值），就要尽量少产生偶数位数的子串

4、如果只有偶数位数的子串，那没有办法就只能是一个（如abccba）

5、否则一定会形成如下最优状态：

（input:aabbcccdddfffeee【aX2,bX2,cX3,dX3,eX3,fX3】）

cacac

dbdbd

fef

efe

#### 6、遍历i:
#### ----for ( int  i=1 ; ;  i+=2 )
#### ----当 【 i  *  最少子串数  >   字符串长度  】 的时候
#### ----i  就是这里面最长的的子串的长度（如上面的cacac）
#### ----所以 i-2  就是这里面最短的（第二长，比最长短了2）的长度（如上面的fef）
## ---∴  ans=i-2
***
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int  ans=0,n=0,times[100];
string a;
inline void readin()
{
    cin>>a;
    return;
}

inline bool ji(int b)
{
    if(b%2)
    return 1;
    return 0;
}

inline void solve()
{
    memset(times,0,sizeof(times));
    for(int i=0;i<a.length();i++)
    times[a[i]-'a'+1]++;
    for(int i=1;i<=26;i++)
    if(ji(times[i]))
    n++;//看看至少到底有多少个回文数
    if(!n)
    ans=a.length();
    else
    for(int i=1;;i+=2)
    if(i*n>a.length())
    {
        ans=i-2;
        break;
    }
    return;
}

inline void print()
{
    printf("%d",ans);
    return ;
} 

int main()
{
    readin();
    solve();
    print();
    return 0;
}
```
***
2018/12/22  BrandonSoong 于成都七中李飞飞机房

---

## 作者：scp020 (赞：0)

### 题目大意

给定一个字符串 $s$，可以任意组合 $s$，然后对 $s$ 进行分割，使每一个字串都为回文，字串编号从 $1$ 到 $n$。

求对于所有子串中最短子串可以达到的最大值。

### 解决

记录下每一种字符出现的次数。如果出现奇数次，则该字符一定在某个子串的中间；如果出现偶数次，那更改字符就可以在子串对称的位置上。

所以子串的数量为出现奇数次的字符的个数。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int cnt[27],ans;
int main()
{
	cin>>s;
	for(int i=0;i<s.size();i++) cnt[s[i]-'a']++;
	for(int i=0;i<26;i++) ans+=cnt[i]%2;
	if(ans==0) cout<<s.size()<<endl;
	else cout<<((s.size()/ans+1)|1)-2<<endl;
	return 0;
}
```


---

## 作者：cjZYZtcl (赞：0)

## 字符串练手题
我们先把输入的字符串中每一个字符出现的次数算出来，然后找到其中出现次数为奇数的字符，将其作为回文的中心，再将其他字符平均分配给这些字符即可。

### 为什么要找到出现次数为奇数的字符作为回文中心？
因为这些字符无法与别的字符配对，只有放在中心才可以作为回文。
### 为什么要平均分配？
因为这样才能使最小值最大。

如果没有出现次数为奇数的字符，那么回文就是一整个字符串。

否则求出字符串长度减去回文中心数量后平均分配给每个回文串的长度加一即可。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int b[30];
char s[100005];
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
	int num = 0;
	scanf("%s", &s);
	for(int i = 0; i < strlen(s); i++){
		b[s[i] - 'a']++;
	}
	for(int i = 0; i <= 25; i++){
		if(b[i] % 2){
			num++;
		}
	}
	if(!num) write(strlen(s));
	else{
		write((strlen(s) - num) / 2 / num * 2 + 1);
	}
	return 0;
}
```


---

## 作者：Azuree (赞：0)

[查看原题请戳这里](https://www.luogu.org/problemnew/show/AT1877)  
我们可以对读入的字符串`s`任意排序，但是实际上我们并没有必要对`s`进行排序——`aabbaa`和`baaaab`其实对于这道题来讲是一样的。   
我们可以发现，对于数量为偶数的字母，我们将其中的偶数个分别添加到某个回文串的两侧，这样就可以得到一个更长的回文串。而且，每个回文串中至多有一个字母在本回文串的个数为`1`。这就意味着，若数量为奇数的字母有`n`个，则我们至少需要把`s`分成`n`个回文串。  
因此，奇数影响着回文串的个数，偶数影响回文串的长度。所以，我们只需要记录每一个字母的出现次数即可。  
附一下代码：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
#define INF 0x7fffffff
#define re register

using namespace std;

int read()
{
	register int x = 0,f = 1;register char ch;
	ch = getchar();
	while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
	while(ch <= '9' && ch >= '0'){x = x * 10 + ch - 48;ch = getchar();}
	return x * f;
}

char s[1000005]; 

int t[100],j,o;

int main()
{
	cin >> s;
	int l = strlen(s);
	for(int i = 0; i < l; i++) t[s[i] - 'a' + 1] ++;
	for(int i = 1; i <= 26; i++)
	{
		j = j + t[i] % 2;
		o = o + t[i] / 2;
	}
	int ans;
	if(j) ans = o / j * 2 + 1;
	else ans = o * 2;
	cout << ans << endl;
    return 0;
}
```

---

