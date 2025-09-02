# Passwords

## 题目描述

## 题目大意
Vanya想去他最喜欢的名为Codehorses的网站，他平时用n个密码作为他所有网站的密码。但是这天，Vanya突然忘了他的密码。
Vanya试的所有密码中，不存在某一次长度小于上一次的长度，他每次会随机试同一长度的密码（当这种长度试完后，会试下一长度的密码）。当他试对时，会瞬间批准进入网站。
他每次输入密码需要1秒，每连续k次输错后，需要等5秒再试下一次。他输密码的过程中不会休息停顿。
准确算出他进入网站最好情况和最差情况所需要的秒数。

## 样例 #1

### 输入

```
5 2
cba
abc
bb1
abC
ABC
abc
```

### 输出

```
1 15
```

## 样例 #2

### 输入

```
4 100
11
22
1
2
22
```

### 输出

```
3 4
```

# 题解

## 作者：OldVagrant (赞：3)

## 题意
Vanya要用 $n$ 个字符串作为密码去试着登录一个网站，正确的密码为 $s$ （保证 $s$ 被包含在给定的 $n$ 个字符串中）。   
Vanya每次会随机试同一长度的密码（当这种长度的密码试完后，会试下一长度的密码）,并且他每次尝试的密码的长度都不会比上一次尝试的密码的长度短，每次都会再每次输入密码都需要 $1$ 秒，每连续输错 $k$ 次之后需要等 $5$ 秒才能再次尝试，对了就会瞬间登录。    
Vanya在没登录进去之前会一直尝试，求Vanya成功登进网站需要的时间的最小值和最大值。
## Solution
简单的贪心，按题意模拟一下就能大概想到。  
首先，所有比 $s$ 的长度短的字符串都会被尝试一遍。  
最好的情况就是试完所有比 $s$ 的长度短的字符串之后下一个试的是 $s$ 。 
最坏的情况就是试完除了 $s$ 之外的所有长度不小于 $s$ 的字符串再试 $s$ 。  
然后根据题意模拟即可，注意一点，就是试对了会瞬间登录，如果这是试的第 $k$ 次，那么不需要等那个额外的 $5$ 秒。  
## Code
```c
#include <bits/stdc++.h>
using namespace std;
#define ll int
#define rint register int
ll ans,n,k,ls,cnt,a[101],now,ans2;
string s,pswd;
int main(){
	scanf("%d%d",&n,&k);
	for(rint i=0;i<n;i++) cin>>s,a[i]=s.size();//直接存长度，字符串的内容不重要
	cin>>pswd,sort(a,a+n),ls=pswd.size();//根据字符串的长度排序
	while(now<n&&a[now]<ls){
		ans++,cnt++,now++;
		if(cnt==k) ans+=5,cnt=0;
	}printf("%d ",ans+1);//试完了所有长度小于正确密码的长度的字符串，最少再试1次就成功登录
	while(now<n&&a[now]==ls){
		ans++,cnt++,now++;
		if(cnt==k&&a[now]==ls) ans+=5,cnt=0;//在最坏情况下，如果下一个字符串的长度比正确密码的长度大，那么当前的字符串就是正确密码，不用再等5s	
	}printf("%d",ans);
	return 0;
}

```


---

## 作者：_l_l_ (赞：3)

[题目页面](https://www.luogu.com.cn/problem/CF721B)

[更好的阅读体验](https://www.luogu.com.cn/blog/yinjun2024/solution-cf721B)

这道题就是贪心。

首先我们算出正确密码的长度，则输入正确密码之前得将长度小于正确密码的密码全部试一遍。

最优为试到长度为正确密码时一遍试出来，最差为试到长度为正确密码时最后一遍才试出来。

代码：
```cpp
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 105;
char a[MAXN][MAXN];
char lim[MAXN];
int lenth[MAXN];
int main() {
	int n, k, aa = 0, bb = 0;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		memset(a, 0, sizeof a);
		scanf("%s", &a[i]);
		lenth[i] = strlen(a[i]);
	}
	scanf("%s", lim);
	int lm = strlen(lim);
	for (int i = 1; i <= n; i++) {
		if (lenth[i] < lm) aa++;
		else if (lenth[i] == lm) bb++;
	}
	printf("%d %d", ((aa) / k) * 5 + aa + 1, ((aa + bb - 1) / k) * 5 + aa + bb);
	return 0;
}
```

---

## 作者：锦瑟，华年 (赞：1)

好一个恶意评分的水题！

我也不知道他为什么是蓝题，反正很简单，只需算出低于正确密码的字符个数的字符串的个数和低于等于正确密码的字符个数的字符串的个数，再加以计算即可。所以，一个小小的桶，就可以解决这水题了。（~~正好桶是装水的~~）

代码来袭：

	#include<stdio.h>
	using namespace std;
	char a[105][105],c[105];
	int f[105];
	int main(){
		int n,k;
		scanf("%d%d",&n,&k);
		int i;
		for(i=1;i<=n;i++){
			scanf("%s",a[i]);//字符串读入
			int l1=0;
			for(;a[i][l1];l1++);//算字符串长度
			f[l1]++;//桶计数
		}
		scanf("%s",c);//输入正确密码
		int l=0;
		for(;c[l];l++);//算正确密码长度
		int s=0,s1=-1;//算s1是要赋-1，为了把它本身给剔除掉
		for(i=1;i<l;i++){//统计个数
			s+=f[i];
			s1+=f[i];
		}
		s1+=f[l];//别忘了加
		int ans=s+s/k*5+1;//计算
		int ans1=s1+s1/k*5+1;
		printf("%d %d",ans,ans1);//输出
		return 0;
	}
    
好了，剩下的自己体会，别抄题解，拜拜~~（^_^）。

---

## 作者：爬行者小郑 (赞：1)

# 好不容易看懂意思
## 好吧，其实很容易
只需要计算少于正确情况字符的个数，在考虑最好和最坏情况即可。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	int n,k,ci=0,ge=0;
	char a[1005][105];
	char right[105];       //正确的情况
	int l[1005];
	int r;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",&a[i]);
		l[i]=strlen(a[i]);  //计算每一个字符串的长度
	}
	cin>>right;
	r=strlen(right);
	for(int i=1;i<=n;i++)
	{
		if(l[i]<r)
		   ci++;        //计算小于的个数
		else if(l[i]==r)
		   ge++;        //计算等于的个数
	}
	printf("%d %d",((ci)/k)*5+ci+1,((ci+ge-1)/k)*5+ci+ge);  //依次考虑两种情况
	return 0;
}
```


---

## 作者：ytcccf (赞：0)

### 题意简述

给出 $n$ 个可能的密码以及正确的密码。从短到长尝试密码，只有试完一种长度的所有密码，才可以去试下一个长度的密码。对于一种长度的所有密码，每次试的时候都是随机尝试的。每试一个密码需要一秒钟的时间，连续 $k$ 次试错需要多等待五秒。求最好情况和最坏情况各需要多长时间。

### 题目分析

题目难度：普及-

$\text{AC code}$ 时间复杂度大概为 $\Theta(n)$

### 解题思路 

因为每个密码的长度都不超过 $100$ ,所以可以把每个密码字符串的长度开桶储存一下，然后利用桶来统计出长度小于正确密码长度的字符串的数量，在这个基础上，最好的情况是只需要再试 $1$ 次就可以了，最坏的情况是需要把所有长度等于正确密码长度的字符串都尝试一遍才能取到正确答案，统计出次数之后按题中的要求计算出所需时间即可。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[105];
string str;
int main()
{
	ios::sync_with_stdio(false);//cin、cout优化 
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>str;
		a[str.length()]++;//字符串的内容没有用，按长度存在桶里就可以了。 
	}
	cin>>str;
	int l=str.length();//l代表密码字符串的长度。 
	int s=0;
	for(int i=0;i<l;i++)
	{
		s+=a[i];//s代表长度小于l的字符串的数量。 
	}
	int x=s+1,y=s+a[l];//x和y分别代表最好和最坏情况所需尝试的次数。 
	cout<<(x-1)/k*5+x<<" "<<(y-1)/k*5+y<<endl;
	return 0;//完结撒花 
}
```

---

## 作者：bmatrix (赞：0)

这题这么水怎么还是蓝啊（恼

~~即使这么水我还是脑子抽风交了好几遍~~

其实很简单：

不妨设正确密码长度为 $len$ ，根据题意，在试到正确密码前都要先把长度小于 $len$ 的密码全部试一遍，则最优情况就是试长度为 $len$ 的密码时一遍试对，最劣情况就是把长度为 $len$ 的所有密码试到最后才试对。

这里提供一种类似桶排序的实现思路：

首先把每个长度的密码个数存起来：
```cpp
for(int i=1;i<=n;i++)
    cin>>ps[i];
cin>>ps[0];len=ps[0].size();
for(int i=1;i<=n;i++)
    if(ps[0]!=ps[i])//这里除去正确密码，方便后续计算
        wd[ps[i].size()]++;
```
然后处理答案的时候：
```cpp
for(int i=1;i<len;i++)ans+=wd[i];//最小是试完所有小于len的
cout<<ans/k*(k+5)+ans%k+1<<' ';//记得+1
ans+=wd[len];//加上长度等于len且与正确密码不同的
cout<<ans/k*(k+5)+ans%k+1<<endl;
```
这样就完美杜绝了考虑最后一次尝试后不用等5秒的问题（

---

## 作者：Isshiki·Iroha (赞：0)

## 题解

[题目传送门](https://www.luogu.com.cn/problem/CF721B)

[~~在博客里食用效果更佳~~](https://www.luogu.com.cn/blog/yousa22/solution-cf721b)


说句闲话：看了看别人的题解都用了一点数学小知识，~~我很不服，什么时候暴力才有出头之日！~~

好了回归正题，这题要你求最大时间和最小时间，考虑贪心。因为 Vanya 是按密码长度升序来试的，所以长度小于正确密码的不用管，直接暴力模拟即可。

- 最优情况：即 Vanya 刚刚好试完了长度小于正确密码的字符串的密码，她开始试长度等于正确密码的字符串，她可能第一次就试的是正确答案，这是最优情况

- 最差情况：同上，只是试长度等于正确密码的字符串的时候，运气很差，试到最后一个才对。

部分代码：

```cpp
    for(int i(1),now=0;i<=n+1;++i){
    //刚刚好长度相等，就可以认为试对了，但是要加上试这个密码的时间
        if(p[i].len==palen){
            ++ans_min;
            break;
        }
        else{
            ++now;//模拟，超过 k 次加一
            if(now>=k)now=0,ans_min+=5;
            ++ans_min;
        }
    }
    for(int i(1),now=0;i<=n+1;++i){
    //判断此时是不是长度已经超过了答案串长度，
    //第一次判断为真的时候前面一定是与答案串长度相等的字符串
    //此时认为她现在在试对，但是有一个坑
    //万一她上一次刚好要罚时，但是你密码对了不要罚，所以要特判
        if(p[i].len>palen){
        	if(now==0)ans_max-=5;
            break;
        }
        else{
            ++now;
            if(now>=k)now=0,ans_max+=5;
            ++ans_max;
        }
    }
```


但是我们忽略了一种情况：没有字符串的长度比答案串长，这个时候我们人为的在最后加一个长度非常长的就可以了。最后是代码：

```cpp
/*
	Name: Passwords
	Copyright: CF721B
	Author: Isshiki Iroha
	Date: 08/10/21 14:56
	Description: String
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,k;
const int maxn=105;
struct password{
    string s;
    int len;
}p[maxn];
const int cmp(const password A,const password B){
    return A.len<B.len;
}
//按长度排序
string pa;
int ans_min,ans_max;
int palen;
int main() {
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i(1);i<=n;++i){
        cin>>p[i].s;
        p[i].len=p[i].s.length();
    }
    cin>>pa;

    palen=pa.length();

    sort(p+1,p+1+n,cmp);

	p[n+1].len=100000;
    //人为插入
    for(int i(1),now=0;i<=n+1;++i){
        if(p[i].len==palen){
            ++ans_min;
            break;
        }
        else{
            ++now;
            if(now>=k)now=0,ans_min+=5;
            ++ans_min;
        }
    }
    for(int i(1),now=0;i<=n+1;++i){
        if(p[i].len>palen){
        	if(now==0)ans_max-=5;
            break;
        }
        else{
            ++now;
            if(now>=k)now=0,ans_max+=5;
            ++ans_max;
        }
    }
    cout<<ans_min<<" "<<ans_max;
    return 0;
}

```


---

## 作者：Luboyan_ (赞：0)

## 题意

题目意思其实很清晰，重要的是下面这句话：

「Vanya 试的所有密码中，不存在某一次长度小于上一次的长度，他每次会随机试同一长度的密码（当这种长度试完后，会试下一长度的密码）。」

意思就是这个人试密码是按长度升序来试的，所以我们并不需要记录密码的内容，只需要在读入时记录每一种长度的密码的数量，然后贪心就行了。

关于题目中所说的最好情况和最坏情况，我们设正确密码的长度为 $k$，在尝试长度为 $k$ 的密码时，第一次就输入了正确密码和最后一次才输入正确密码的情况分别就是题目所说的最好和最坏。

剩余部分根据题意模拟就好了。

## 代码

```cpp
#include<iostream>
#include<string>
using namespace std;
int n,k,rl,sum=0,ans;
int a[101];
string s,r;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>s;
		a[s.size()]++;//记录每种长度的密码数量 
	}
	cin>>r;
	rl=r.size();//正确密码的长度 
	for(int i=1;i<rl;i++)sum+=a[i]; //首先尝试长度小于正确长度的密码 
	ans=sum+sum/k*5+1;//最好情况用时：输入长度小于rl的密码用时+错误罚时+输入正确密码的用时 
	cout<<ans<<" ";
	sum=sum+a[rl]-1; 
	ans=sum+sum/k*5+1;//最坏情况用时：输入长度小于rl的密码用时+输入长度为rl的其他所有密码用时+错误罚时+输入正确密码的用时 
	cout<<ans;
	return 0;
}
```


---

## 作者：MeowScore (赞：0)

## 题目大意

给出 $n$ 个候选密码以及一个正确密码。每次会从短到长尝试密码，只有试完了一种长度，才会去试下一长度。对于一种长度的所有加密码，每次去试的时候是随机的。试一个密码需要一秒，连续 $k$ 次错误需要等五秒。求最好和最坏需要几秒才能试出密码。

------------

## 解决问题

~~恶评！建议降橙！~~

开一个桶记录每一个长度的密码有几个。由于是从短到长试密码，所以长度小于正确密码的密码数都要计入尝试次数。对于最好情况，在尝试长度等于正确密码长度的密码时，第一次就可以试出来，对于最差情况，需要把长度等于正确密码长度的密码全都尝试一遍。我们求出试错的次数，一次就是一秒，每试错 $k$ 次加五秒。注意最后一次试对了花的一秒也得加上。


------------


## 上代码
```
#include<bits/stdc++.h>
using namespace std;
int p[200];
int main(){
	int n,k;
	cin>>n>>k;
	char a[200];
	for(int i=1;i<=n;i++){
		cin>>a;
		p[strlen(a)]++;
	}
	cin>>a;
	int len=strlen(a);
	int times=0;
	for(int i=1;i<len;i++)
		times+=p[i];
	int ansmin=times;//这是最小的试错的次数 
	int ansmax=times+p[len]-1;//这是最大的试错的次数 
	ansmin+=5*(ansmin/k);//每试错k次加五秒 
	ansmax+=5*(ansmax/k);
	cout<<ansmin+1<<' '<<ansmax+1;//最后试对的时候也会花一秒，别忘了加上 
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有一天，小 V 突然忘记了他在 Codehorses 的网站上的密码。但是他有所有网站上的 $n$ 个密码 $\{s_i\}_{i=1}^n$，所以他开始一个一个试。他会先从长度最小的密码开始试，如果有多个长度相等的密码就等概率随机选一个，并且他不会再去试已经试过的密码。输入密码需要 $1$ 秒，如果连续输错 $k$ 次密码就需要再等 $5$ 才能重新开始试。已知他的密码是一个字符串 $t$。求最好情况和最坏情况下他试密码需要的时间。

**数据范围：$1\leqslant n,k\leqslant 100,0\leqslant |s_i|,|t|\leqslant 100$。**
## Solution
我们可以开个桶存储一下所有的 $|s_i|$，然后利用桶统计出所有长度 $<|t|$ 的字符串个数，加进答案里面去，设此时答案为 $ans$，那么这时，最好情况的话就只需要再试一次密码，最坏的情况就需要试所有 $n$ 个密码中长度为 $|t|$ 的密码。注意需要考虑连续输错需要加时的情况。
## Code
```cpp
int n, k, a[107];
string s[107], t;

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i) {
		cin >> s[i];
		int len = s[i].size();
		a[len]++;
	}
	cin >> t; int lent = t.size(), ans = 0;
	for(int i = 1; i < lent; ++i) ans += a[i];
    printf("%d %d", (ans + 1) + (ans + 1) / k * 5 - (!((ans + 1) % k) ? 5 : 0), (ans + a[lent]) + (ans + a[lent]) / k * 5 - (!((ans + a[lent]) % k) ? 5 : 0));
	return 0;
}
```

---

## 作者：Link_Space (赞：0)

~~非常水的一道题目~~

题目的意思就是告诉你一串密码，一个人会按照密码长度的升序输入密码，输出错误连续k次会需要等5秒，输一次密码1秒，问你最多和最少需要多少秒可以输对。

那么很简单就可以想到，最少的情况就是正确密码长度为n，输完密码长度小于n的所有密码后第一个就输到了正确的密码。

而最多的情况就是正确密码长度为n，输完密码长度小于n的所有密码后再输入了密码长度为n的除了正确密码以外的所有密码之后最后一个才输入了正确密码。

那么知道思路以后我们就可以很轻松地将这道题秒掉了，只需要处理一个前缀和数组便可。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
string s[1000000];
int sum[1000];
int main()
{
    int n;
    scanf("%d", &n);
    int k;
    scanf("%d", &k);
    int maxsize = 0;
    for (int i = 1; i <= n;i++)
    {
        cin >> s[i];
        sum[s[i].size()]++;
        if(s[i].size()>maxsize)
            maxsize = s[i].size();
    }
    for (int i = 1; i <= maxsize;i++)
        sum[i] += sum[i - 1];
    string ans;
    cin >> ans;
    int minn = sum[ans.size() - 1] + sum[ans.size() - 1] / k * 5 + 1;
    int maxn = sum[ans.size()] + (sum[ans.size()] - 1) / k * 5;
    cout << minn << " " << maxn << endl;
}
```


---

## 作者：king_xbz (赞：0)

一道字符串的题目，尽管已经有题解了，但我发现还木有思路和我一样用结构体排序做的题解，所以我来发一发这种神奇的做法~~造福人类~~！

# 解题思路
由于这家伙是从最低位的到最高位试，所以我们将密码按位数排序，然后分类讨论：

- 当前位数少于正确密码最小值和最大值都累加．
- 当位数等于正确密码值时，只有最大值累加。

最后，每k位进行一次等5秒的操作即可。

# 代码实现
写好struct和cmp排序即可
注意$×5$前要将$min-1,max-1$（因为等五秒和试密码要先后进行，不能直接替代，否则会$WA#4$ ）
```cpp
int main()
{
	int n,k;
	cin>>n>>k;
	for(fint i=1;i<=n;i++)
	cin>>a[i].cod,a[i].len=a[i].cod.size();
	string tru;
	cin>>tru;
	sort(a+1,a+n+1,cmp);
	int tru_len=tru.size();
	int mins=0,mas=0;
	for(fint i=1;i<=n;i++)
	{
		if(a[i].len<tru_len)
		mins++,mas++;
		if(a[i].len==tru_len)
		mas++;
		if(a[i].len>tru_len)
		break;
	}
	mins++;
	cout<<(mins-1)/k*5+mins<<" "<<(mas-1)/k*5+mas;
	return 0;
}

inline bool cmp(node aa,node bb)
{
	return aa.len<bb.len;
}
```

祝大家AC愉快！！！

---

