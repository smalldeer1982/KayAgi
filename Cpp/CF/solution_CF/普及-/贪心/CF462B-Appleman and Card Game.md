# Appleman and Card Game

## 题目描述

给你个长度为 $n$ 的字符串，要求你从这个字符串中选取 $k$ 个字符，使选到的每个字母的数量的平方和最大。

## 样例 #1

### 输入

```
15 10
DZFDFZDFDDDDDDF
```

### 输出

```
82
```

## 样例 #2

### 输入

```
6 4
YJSNPI
```

### 输出

```
4
```

# 题解

## 作者：hensier (赞：1)

这道题目其实与字母是没有任何关联的。我们把所有的字符存入桶，再快排，最后按照贪心的性质求得答案即可。

代码：

```cpp
#include<cstdio>
#include<algorithm>
int n,k,ans,a[26];//a为桶，ans为答案，n、k与题目中相符合
bool cmp(int x,int y)//定义从大到小排序
{
    return x>y;
}
int main()
{
    scanf("%d%d\n",&n,&k);//输入，注意换行符必须吸收掉，否则会影响后面的getchar
    while(n--)a[getchar()-'A']++;//直接输入n个字符，用getchar()会更快，一边输入一边存入桶中
    std::sort(a,a+26,cmp);//快排
    for(int i=0;i<26;i++)
    {
        int m=std::min(a[i],k);//每次取剩余个数和当前序列总个数的最小值
        ans+=m*m;//累加答案
        k-=m;//剩余个数要减去m
        if(!k)break;//当k=0时，循环结束
    }
    printf("%d",ans);//输出答案
}
```

提交评测后，在第$24$个点的时候，出现了问题。把鼠标放在该测试点上看，发现输出结果居然为负！因此我们断定变量类型不够大。~~十年`OI`一场空，不开`long long`见祖宗。~~

解决方法：

宏定义是一个好东西——我们不妨使用下列语句：

```cpp
#define int long long
```

上述语句看上去是有错误的，但是其实使用它并不会引起系统名冲突，但是唯一的问题是，主函数的返回值变成了$long\,long$，所以我们必须将其改回$int$。而$int$已经变成了$long\,long$，所以我们可以使用等效于$int$的$signed$。最后把输入输出中的$\%d$改为$\%lld$即可。

$AC$代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
int n,k,ans,a[26];
bool cmp(int x,int y)
{
    return x>y;
}
signed main()
{
    scanf("%lld%lld\n",&n,&k);
    while(n--)a[getchar()-'A']++;
    std::sort(a,a+26,cmp);
    for(int i=0;i<26;i++)
    {
        int m=std::min(a[i],k);
        ans+=m*m;
        k-=m;
        if(!k)break;
    }
    printf("%lld",ans);
}
```

---

## 作者：TRZ_2007 (赞：1)

### 题解 [CF462B 【Appleman and Card Game】](https://www.luogu.com.cn/problem/CF462B)  
# Description  
给你一串字符，要求你从这 $n$ 个字符中选取 $k$ **个**字符，要求每个字母的数量的**平方和**最大。  
# Solution  
如果你不能看出来这是贪心，我奉劝你还是先去做一做红题。  
我们先把所有的字符数**自大到小**排序，然后去取字符。注意，要取 $k$ **个**字符，不是 $k$ **种**！  
最后还有坑点：如果所有的数字都取光了那你就直接输出！！不开$\texttt{long long}$见祖宗！！  

# Code 
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 100009;

long long ans = 0;
long long n,k;
long long book[209];//字符数在这里存
char str[N];

bool cmp(long long u,long long v) {
	return u > v;
}

int main() {
	scanf("%lld %lld",&n,&k);getchar();//不加这个第一个字符就是换行了
	for(int i = 1;i <= n;i++) {
		scanf("%c",&str[i]);
		book[str[i] - 'A' + 1]++;
	}
	sort(book + 1,book + 30,cmp);
	for(int i = 1;k > 0;i++) {
		if(book[i] <= k) {//可以直接全部拿走
			ans += book[i] * book[i];
			k -= book[i];
		}else {//拿不光，把剩下来的都拿了！
			ans += k * k;
			break;
		}
		if(book[i] == 0) break;//这里不加就很快乐了
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：chenkaiwen (赞：0)

这一题是一道贪心题，题目的大意是：输入一个长度为n的字符串，在这个字符串中取k个字符，求这k个字符中每个字符出现的次数的平方是多少

那么我们需要以下几个步骤：

1. 统计每个字符出现的次数
2. 以出现次数为关键字从大到小排序
3. 以从大到小的顺序去k个字符

因为字符只为大写字母，所以第一步只需要建立一个大小为26的桶就好。
```cpp
string s;
long long t[1000];
cin>>s;
l=s.length();
for(int i=0; i<l; i++) {
	t[s[i]-'A']++;
}
```
第二步是用sort进行排序，这里要注意，是从大到小排序。
```cpp
bool as(int a,int b) {
	if(a>b) {
		return 1;
	} else {
		return 0;
	}	
}
int main(){
	sort(t,t+27,as);
    return 0;
}
```
第三步是以从大到小的顺序求答案
```cpp
	for(int i=0; i<26&&k>0; i++) {
		if(t[i]>k) {
			ans+=k*k;
			break;
		} else {
			ans+=t[i]*t[i];
			k-=t[i];
		}
	}
	cout<<ans<<endl;
```
其他细节上的内容我会在下面的代码的注释中写出，代码如下：

[![](https://cdn.luogu.com.cn/upload/image_hosting/bhfc7ota.png)证明](https://www.luogu.com.cn/record/32891696)

```cpp
#include<bits/stdc++.h>
#include <iostream>
using namespace std;
string s;
long long t[1000];//建立桶 
long long n,k,l,ans=0;
bool as(int a,int b) {//从大到小排序 
	if(a>b) {
		return 1;
	} else {
		return 0;
	}	
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0);
	cin>>n>>k;
	cin>>s;//输入字符串 
	l=s.length();
	for(int i=0; i<l; i++) {
		t[s[i]-'A']++;//用桶来统计每个字符的数量 
	}
	sort(t,t+27,as);//排序 
	for(int i=0; i<26&&k>0; i++) {//以从大到小的顺序贪心取答案 
		if(t[i]>k) {
			ans+=k*k;//统计答案 
			break;
		} else {
			ans+=t[i]*t[i];//统计答案 
			k-=t[i];
		}
	}
	cout<<ans<<endl;//输出 
	return 0;
}
```
### 感谢观看

---

## 作者：Goldia (赞：0)

## 大致题意
    给你一串字符串，从中选k个，最后获得的数为你所选的字符串中所选的每个字母的数量的平方（同个字母只算一次）求最大数。
## 思路
	读入字符串后，用一个桶记录每个字母出现的次数，然后从大到小排序排序，贪心的从最大的选。
## code
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;
#define ll long long
#define R register
ll n,k,tong[300],ans;//不long long见祖宗
char s[100005];
bool cmp(int a,int b){return a>b;}//从大到小排序
int main()
{
    scanf("%d%d",&n,&k);cin>>s;
    for(R int i=0;i<n;i++)tong[s[i]]++;//记录出现次数
    sort(tong+1,tong+299+1,cmp);
    int now=1;//从最大的开始贪
    while(k>0)
    {
    	if(tong[now]>k)//如果不能选这么多就尽量多的选。
		{
			ans+=k*k;
			k=0;
		}
    	else //可以就全拿
		{
			ans+=tong[now]*tong[now];
			k-=tong[now];
			now++;
		}
    }
    cout<<ans<<'\n';
    //树状数组那道题用endl比\n慢500ms......养成好习惯
    return 0;
}
```


---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF462B)

既然没人用结构体做，那么我就发一篇结构体的题解吧。


------------
### 分析与思路

这道题就其实就是给你一个字符串，要求你从这 ```n``` 个字符中选取 ```k``` 个字符，并且要**每个字母的数量的平方和尽可能的大**。

我们需要定义一个结构体，其中结构体里面有一个字符还有和它对应出现的次数。利用快排排一下序，然后我们用双重循环不断遍历每个次数，每次遍历完以后都要判断 ```k```  是否等于零，是的话退出内循环，计算平方和，再退出外循环，输出。否则继续。

看似很复杂，我们一步步来实现。



------------
### 代码实现

1. 输入字母，将字母累加一，排序。

这个不难，只需要注意所有变量都是 ```long long``` 。
```
for(long long i=1;i<=n;i++){
    cin >> ch;
    a[ch-'A'+1].sl++;
    a[ch-'A'+1].c=ch;
    maxn=max((long long)(ch-'A'+1),maxn);//计算最大的字母，便于排序。
}
sort(a+1,a+maxn+1,cmp);
```

还有 ```cmp``` :

```
long long cmp(CF462B x,CF462B y){
    return x.sl>y.sl;
}
```


2. 双重循环，遍历每一个次数，判断 ```k``` 是否等于零，如果不等于的话就累加次数。

注意 ```i``` 和 ```j``` 结束位置。

```
for(long long i=1;i<=maxn;i++){
    for(long long j=1;j<=a[i].sl;j++){
        if(k!=0)sum++;
        else break;
        k--;
    }
}
```



3. 如果等于零，那么退出内循环，计算平方和，退出外循环。否则继续。

所以我们必须在外循环退出之前加上这几条语句：
```
ans+=sum*sum;
if(k==0)break;
else sum=0;
```
最后再输出 ```ans``` 就搞定啦！


------------
### 完整 ```AC``` 代码：
```
#include<iostream>
#include<algorithm>
using namespace std;
long long n,k,maxn,sum,ans;
char ch;
struct CF462B{
    char c;
    long long sl;
}a[100010];
long long cmp(CF462B x,CF462B y){
    return x.sl>y.sl;
}
int main()
{
    cin >> n >> k;
    for(long long i=1;i<=n;i++){
        cin >> ch;
        a[ch-'A'+1].sl++;
        a[ch-'A'+1].c=ch;
        maxn=max((long long)(ch-'A'+1),maxn);
    }
    sort(a+1,a+maxn+1,cmp);
    for(long long i=1;i<=maxn;i++){
        for(long long j=1;j<=a[i].sl;j++){
            if(k!=0)sum++;
            else break;
            k--;
        }
        ans+=sum*sum;
        if(k==0)break;
        else sum=0;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：2132B (赞：0)

这道题乍一看似乎是字符串

实际上这是一道关于桶排序和$sort$函数的题

### 题意

给你一个字符串，和一个$k$,输出其中选$k$个字符的同字母数的数量之平方和

~~不懂请看code~~

### 思路

首先用桶来计每一个字符出现次数，接着用快排从大到小排序，最后求出答案

### $code$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, k, vis[30], ans;//注意！！！这里要开long long
char l;
bool cmp(int a, int b)//使sort从大到小
{
	return a > b;
}
int main()
{
	cin >> n >> k;
	for (int i = 1;i <= n;i++)
	{
		cin >> l;
		vis[l - 'A' + 1]++;//用桶统计数量
	}
	sort(vis + 1, vis + 27, cmp);//sort快排
	int i = 1;
	while (k >= vis[i])//只要还能选就继续
	{
		ans += vis[i] * vis[i];//ans加上这个字母出现次数的平方
		k -= vis[i];
		i++;
	}
	ans += k * k;//最后剩的选的次数
	cout << ans;
	return 0;
}
```


---

## 作者：BotDand (赞：0)

# $\text{Problems}$
给你一串字符，要求你从这$n$个字符中选取$k$个字符，要求每个字母的数量的**平方和**最大。
# $\text{Answer}$
题目没有说要连续的字符串，所以可以用一个桶$a_x$来储存$x$在$n$中出现的次数，再将$a$从大到小排序，最后贪心一下即可。
# $\text{Code}$
```pascal
var
  a:array['A'..'Z'] of int64;
  n,t,i:longint;
  s,k:int64;//不开long long见祖宗
  ch1,ch2,x:char;
begin
  readln(n,k);
  for i:=1 to n do begin read(x);inc(a[x]);end;//桶
  for ch1:='A' to 'Y' do
    for ch2:=succ(ch1) to 'Z' do
      if a[ch1]<a[ch2] then
        begin
          t:=a[ch1];a[ch1]:=a[ch2];a[ch2]:=t;
        end;
        //选择排序
  ch1:='A';
  while k>0 do
    begin
      if k<a[ch1] then s:=s+k*k//如果剩下的只能装k个数，则装完
        else s:=s+a[ch1]*a[ch1];//否则继续装
      k:=k-a[ch1];ch1:=succ(ch1);//下一个
    end;
  writeln(s);//输出
end.
```
# $\text{Ps}$
$\text{succ(x)}$为$x$字符的下一个。

---

