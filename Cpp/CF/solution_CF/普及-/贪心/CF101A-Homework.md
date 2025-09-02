# Homework

## 题目描述

Gerald在上学的一天，他的老师在班上布置了一项作业：她给每个同学一个有n个小写拉丁字母（即英文字母）的字符串，要求学生学习这个字符串中的字母的写法。但是，由于Gerald太懒了，他不想学习这些字母。这就是为什么他决定丢掉这个字符串的部分（不需要是连续的一部分）。他所丢失的部分可以由若干个任意长度在任意位置的连续的子字符串组成。但是，Gerald知道，如果他丢掉了超过k个字母，他就会显得非常可疑。

请求出在不超过k个字母被删除之后，字符串中最少剩下多少个不同的字母。你还需要求出一种删除这些字母的方式。

## 说明/提示

在第一个样例中这个字符串含有5个字母但是你只允许删去其中4个，所以会剩下至少一个字母。所以，正确答案就是1和任意一个长度在1到5的、只含有字母a的字符串。

在第二个杨立忠你可以删去4个字母。你不能删去所有的字母，因为这个字符串的长度是7。 但是，你可以删去所以除了a以外的字母（这样的字母不多于4个），所以得到的答案是"aaaa"。

在第三个样例中字符串的长度是8，且k=10，所以可以将所有的字母都删去。正确答案是0和空字符串。

Translated by @oolliivveerr

## 样例 #1

### 输入

```
aaaaa
4
```

### 输出

```
1
aaaaa
```

## 样例 #2

### 输入

```
abacaba
4
```

### 输出

```
1
aaaa
```

## 样例 #3

### 输入

```
abcdefgh
10
```

### 输出

```
0

```

# 题解

## 作者：liuyifan (赞：2)

## 思路:贪心

蒟蒻表示不知道这道题是怎么评到![PJ/TG-](https://s1.ax1x.com/2018/10/06/iGFfKK.png)的,个人觉得最多PJ-

按出现次数多少贪心即可,时间复杂度O(26)

code://注释在下面
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register
using namespace std;
string s;
int k,a[100],d[100],f[100],ans;
inline bool cmp(const int &x,const int &y)//加一个&(取地址符)和const更保险,~~虽然我还没遇到过被卡的情况~~
{
    return a[x]<a[y];
}//sort自定义比较函数
int nain()
{
    cin>>s>>k;//cin读入
    for(reg int i=0;i<s.length();i++)a[s[i]-'a']++;//统计出现次数
    for(reg int i=0;i<26;i++)d[i]=i;//初始化
    sort(d,d+26,cmp);//按a从小到大排序d
    这就是sort的优点:可以按照自己的各种方法排序
    return 0;
    for(reg int i=0;i<26;i++)
    {
        if(k<a[d[i]])break;
        k-=a[d[i]];
        f[d[i]]++;
    }
    for(reg int i=0;i<26;i++)
	if(!f[i])ans++;//统计答案
	printf("%d\n",ans);//输出
    if(ans!=0)
	for(reg int i=0;i<s.size();i++)
    if(!f[s[i]-'a'])putchar(s[i]);//putchar输出字符,在字符上是最快的处理方法,数字的快速输出就是用它实现的
}
```
# 拒绝抄袭,共建和谐洛谷

---

## 作者：小恐 (赞：1)

简述一下题意，就是从一个字符串中删去不超过k个字符，使得字符种类个数最少。

思路灰常自然，就是紧着个数少的删（这不就是贪心吗？）

都是小写字母，所以就建一个数组存储每个字母的个数，然后排个序，贪心一下，就可以了。

贴代码：
```cpp
#include<stdio.h>
#include<algorithm>//sort要用 
#define MAXN 100005//a数组范围 
using namespace std;
char a[MAXN];//字符数组
struct node//结构体，不会上网查 
{
	int cnt;//记录每个字母出现次数，例如cnt[0]记录‘a’的次数 
	char ch;//记录这个字母是什么 
}f[30];
bool cmp(node x,node y)//sort中排序依据 
{
	return x.cnt<y.cnt;
}
bool book[28];//记录此字符种类是否被删 
int main()
{
	int k;
	scanf("%s",a);
	scanf("%d",&k);
	for(int i=0;i<26;++i)
		f[i].ch='a'+i;//初始化 
	for(int i=0;a[i]!='\0'/* 字符数组自动在末尾+一个‘\0’结束符 */ ;++i)
		++f[a[i]-'a'].cnt; 
	sort(f,f+26,cmp);//排序 
	int start;//在字符串中出现最少次数的下标 
	for(int i=0;i<26;++i)
	{
		if(f[i].cnt!=0)//如果字符串中有了 
		{
			start=i;//记录 
			break;//退出循环 
		}
	} 
	int ans=0;//最后的字符种类数 
	for(int i=start;i<26;++i)
	{
		if(f[i].cnt>k)//不能将这种字符全删了 
		{
			ans=26-i;//记录答案 
			break;//跳出循环 
		}
		book[f[i].ch-'a']=1;//这种字符全部删除 
		k-=f[i].cnt;//删的次数减少 
	}
	printf("%d\n",ans);//输出种数 
	for(int i=0;a[i]!='\0';++i)
		if(!book[a[i]-'a'])//如果还没被删 
			printf("%c",a[i]);//输出 
	return 0;
}
```
[AC凭证](https://www.luogu.com.cn/record/30413754)

珍爱生命，远离抄袭

---

## 作者：duchengjun (赞：0)

# 题意

一个字符串，最多删去 k 个字符，使得字符种类最少。

求删去后的字符的字符种类和字符串。

# 分析

贪心求解即可。

求每一个字符的个数，先将个数少的字符删去，直到 k 不够用。

# Code


```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
string s;
int k,cnt,ans=1;
bool vis[30];
struct letter{
	char c;
	int many;
}a[30];
bool cmp(letter u,letter v){
	return u.many<v.many;
}
signed main(){
	for(int i=1;i<=26;i++)
		a[i].many=0x3f3f3f3f;
	cin>>s>>k;
	for(int i=0;i<s.size();i++){
		int x=s[i]-'a'+1;
		if(a[x].many==0x3f3f3f3f){
			cnt++;
			a[x].many=0;
			a[x].c=s[i];
			vis[x]=true;
		}
		a[x].many++;
	}
	sort(a+1,a+1+26,cmp);
	while(k){
		if(a[ans].many>k)break;
		int t=a[ans].many;
		a[ans].many-=k;
		vis[a[ans].c-'a'+1]=false;
		k-=t;
		ans++;
	}
	cout<<cnt-ans+1<<endl;
	for(int i=0;i<s.size();i++){
		int x=s[i]-'a'+1;
		if(vis[x])
			cout<<s[i];
	}
	return 0;
}

```


---

## 作者：Chenxiaozhi (赞：0)

题目大意：给出一个字符串和 k ，要求删掉少于 k 的字母。思路：
1. 首先可以用 map 来存储字母的数量；
2. 然后创建一个迭代器数组对 map 按升序进行排序；
3. 按照要求删减。


------------
代码如下：

```c
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;

map<char, ll>mp;
map<char, ll>::iterator its[30];

int main()
{
	ll k,sum=0;
	string str;
	cin >> str;
	cin >> k;
	for (ll i = 0; i < str.size(); i++)mp[str[i]]++; sum = mp.size();
	map<char, ll>::iterator it = mp.begin();
	ll i = 0;
	for (it; it != mp.end(); it++)its[i] = it,i++;
	for (ll j = 0; j < i-1; j++)
	{
		for (ll k = j; k < i; k++)
		{
			if (its[j]->second > its[k]->second)
			{
				it = its[k];
				its[k] = its[j];
				its[j] = it;
			}
		}
	}
	for (ll j = 0; j < i; j++)
	{
		if (its[j]->second > k)break;
		k -= its[j]->second;sum --;
		its[j]->second = 0;
		
	}
	printf("%lld\n", sum);
	for (ll j = 0; j < str.size(); j++)
	{
		if (mp[str[j]])printf("%c", str[j]);
	}

	return 0;
}
```
首次交题解谢谢各位。

---

## 作者：Need_No_Name (赞：0)

# Solution For CF101A

## 题意

给定一个字符串 $s$ ，最多能删除 $k$ 个字符，使得最后剩下的字符**种类**最少。求剩下的字符。输出时剩下的按字符在原字符串中的顺序输出。

## 思路

我们可以考虑用结构体建立一个桶，记录每个字母出现的次数以及分别对应的字符，然后采用贪心的策略去从小到大将其删去。如果能删掉这一种就删掉，以此类推。作为一个~~学生党~~乐于助人的好少年，深知这位 Gerald の痛苦，于是能删就删，可以在打的时候略去。然后注意下小细节，就可以了。（然后就是这个小细节浪费了我的1个半小时以上。。。）

## 代码

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 1e5 + 10;
const int M = 30;
struct Node
{
	char val;
	int num;
	int diff;
	inline bool operator <(const Node &x)const
	{
		return x.num > num;
	}
}t[N];
int t1[M];
string s;
string s1;
int len;
int k;
int cnt = 0;
signed main()
{
	cin >> s;
	len = s.size();
	s1 = s;
	for(int i = 0; i < len; i++)
	{
		t[(int)(s[i] - 'a') + 1].val = s[i];
		t[s[i] - 'a' + 1].num++;
		t[s[i] - 'a' + 1].diff = 0;
	}
	cin >> k;
	if(k >= len)
	{
		puts("0");
		return 0;
	}
	for(int i = 1; i <= 26; i++) if(t[i].num > 0) cnt++;
	for(int i = 1; i <= 26; i++) if(t[i].num > 0) t1[(int)(t[i].val - 'a') + 1] = t[i].num;
	sort(t + 1, t + 26 + 1);
	int tmp = 0;
	for(int i = 1; i <= 26; i++)
	{
		if(t[i].num == 0) tmp++;
		else break;
	}
	cnt += tmp;
	if(k < t[1].num)
	{
		cout << cnt << endl;
		for(int i = 0; i < len; i++) cout << s[i];
		cout << endl;
		return 0;
	}
	int kval = k;
	int cnt1 = cnt;
	for(int i = tmp + 1; i <= cnt; i++)
	{
		if(t[i].num == 0) break;
		if(kval >= t[i].num)
		{
			cnt1--;
			t[i].diff = t[i].num;
			t1[(int)(t[i].val - 'a') + 1] = 0;
			kval -= t[i].num;
			t[i].num = 0;
		}
		else if(kval < t[i].num && kval > 0)
		{
			t[i].num -= kval;
			t1[(int)(t[i].val - 'a') + 1] -= kval;
			kval = 0;
			break;
		}
	}
	cout << cnt1 - tmp << endl;
	for(int i = 0; i < len; i++)
	{
		int tmp1 = ((int)(s1[i] - 'a') + 1);
		if(t1[tmp1] == 0) continue;
		else
		{
			cout << s1[i];
			t1[tmp1]--;
		}
	}
	cout << endl;
	return 0;
}
```


---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF101A)

### 思路

总的来说这个题目就是 贪心 $+$ 排序。题目意思比较明确，这里将不再阐述。

首先，他要让我们在删去 $k$ 个字符之后，留下的字母种类数尽量的小，也就是让删去的种类尽量的多。我们可以运用桶的思想，将每个字母的数量储存下来，为了让删去的种类越多，我们先根据这个字母的数量从小到大排序，然后每次都先删去数量越少的字母。因为这样的话，我们可以删去的 $k$ 个字符才能利用到最大化，使得他能删去更多的字母种类。

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
char a[100005];
int n,m;
struct node
{
    int p,id;//p储存数量，id储存这个字母。
    bool operator <(const node &n)const
    {
        return p<n.p;//根据数量进行排序。
    }
}arr[100005];
int vis[100005],cnt;//vis标记每个字母在结构体中的下标
int ans;
int main()
{
    cin>>a+1;
    n=strlen(a+1);
    cin>>m;
    for(int i=1;i<=n;++i)
    {
    	//运用桶的思想储存。
        if(vis[a[i]]==0)
        ans++,vis[a[i]]=++cnt;//记得将答案默认为当前的字母种类。
        arr[vis[a[i]]].p++;
        arr[vis[a[i]]].id=a[i];
    }
    sort(arr+1,arr+cnt+1);//排序。
    for(int i=1;i<=cnt;++i)
    {
    	//判断是否可以继续删除一个字母种类
        m-=arr[i].p;
        if(m>=0)
        ans--,arr[i].p=0;//被删除了，将数量标记为0，答案-1
        else if(m<0)
        {
            break;//不能被删除就直接跳出循环。
        }
    }
    cout<<ans<<endl;//输出种类
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i)
    {
        int q;
        for(int j=1;j<=cnt;++j)
        {
            if(arr[j].id==a[i])
            {
                q=arr[j].p;//找到a_i这个字母是否被删除
                break;
            }
        }
        for(int j=1;j<=min(1,q);++j)//如果这个字母没有被删除就输出，被删除了q就是0，就不会输出。
        cout<<a[i];
    }
    cout<<endl;
}

```

---

## 作者：happybob (赞：0)

用一个 `map` 统计每个字符出现的个数，然后转成 `vector` 排序，然后贪心。

贪心思路：从字符数量最少的字符开始删，如果可以删把这个字符记录下来，如果删到剩下可以删的字符数小于这个字符数量时就直接退出。输出的时候对于每一个字符再我们记录下来的字符里查找。

这竟然没有 TLE ？

代码：

```cpp
#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(const pair<char, int>& a, const pair<char, int>& b)
{
	return a.second < b.second;
}

map<char, int> mp;

int main()
{
	string s;
	int k;
	ios::sync_with_stdio(FALSE);
	cin >> s >> k;
	int len = s.length() - 1;
	for (int i = 0; i <= len; i++)
	{
		mp[s[i]]++;
	}
	vector< pair<char, int> > vec(mp.begin(), mp.end());
	int cnt = vec.size();
	sort(vec.begin(), vec.end(), cmp);
	string tmp = "";
	auto it_end = vec.end();
	for (auto it = vec.begin(); it != it_end; ++it)
	{
		if (k <= 0 || k < (*it).second)
		{
			break;
		}
		else
		{
			k -= (*it).second;
			cnt--;
			tmp += (*it).first;
		}
	}
	cout << cnt << endl;
	for (int i = 0; i <= len; i++)
	{
		if (tmp.find(s[i]) != string::npos)
		{
			continue;
		}
		cout << s[i];
	}
	cout << endl;
	return 0;
}
```


---

