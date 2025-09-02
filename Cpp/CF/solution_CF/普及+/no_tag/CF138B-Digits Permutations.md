# Digits Permutations

## 题目描述

Andrey's favourite number is $ n $ . Andrey's friends gave him two identical numbers $ n $ as a New Year present. He hung them on a wall and watched them adoringly.

Then Andrey got bored from looking at the same number and he started to swap digits first in one, then in the other number, then again in the first number and so on (arbitrary number of changes could be made in each number). At some point it turned out that if we sum the resulting numbers, then the number of zeroes with which the sum will end would be maximum among the possible variants of digit permutations in those numbers.

Given number $ n $ , can you find the two digit permutations that have this property?

## 样例 #1

### 输入

```
198
```

### 输出

```
981
819
```

## 样例 #2

### 输入

```
500
```

### 输出

```
500
500
```

# 题解

## 作者：ZLCT (赞：0)

# CF138B Digits Permutations
## 题目翻译
给定一个数 $n$，要求求出这个数的两个排列使这两个排列相加的末尾有最多的 $0$。
## 小模拟
这个题的思路还是比较明了的，由于构造出来的排列一定是最后有若干个 $0$，前面有两个相加和为 $10$ 的数，然后前面一堆和为 $9$ 的数，接下来前面一堆没用的数。\
接下来我们考虑如何处理能使代码简洁优雅一些。\
首先我们可以枚举最后和为 $10$ 的是哪两个数，由于我们不关心这两个排列的顺序，所以我们可以假设第一个数的该位比第二个数的该位小，那么我们只需要枚举 $[1,5]$ 这 $5$ 个数即可。\
当确定完最后一位以后，前面由于 $a+b=9$ 的构造方法中没有两组的 $a$ 或 $b$ 相同，所以直接每个数都单独考虑构造即可。\
注意这里有个细节，我们把两个 $9+0$ 构造一起一定比构造一个 $0+0$ 放最后面优（$2>1$）。
## code（优雅至极）
```cpp
#include<bits/stdc++.h>
using namespace std;
string n,p1,p2;
int num[10],num2[10],num3[10],ans,ansid,now0,f0;
int get(int x){
    int res=0;
    for(int i=0;i<=9;++i){
        num2[i]=num3[i]=num[i];
    }
    num2[x]--;num3[10-x]--;
    if(num2[x]<0||num3[10-x]<0)return 0;
    res=1;
    for(int i=0;i<=9;++i){
        res+=min(num2[i],num3[9-i]);
        int d=min(num2[i],num3[9-i]);
        for(int j=1;j<=d;++j){
            num2[i]--;num3[9-i]--;
        }
    }
    now0=min(num2[0],num3[0]);
    return res+now0;
}
void make(int x){
    for(int i=0;i<=9;++i){
        num2[i]=num[i];
    }
    num[x]--;num2[10-x]--;
    for(int i=1;i<=f0;++i){
        p1+='0';p2+='0';num[0]--;num2[0]--;
    }
    p1+=char(x+'0');p2+=char(10-x+'0');
    for(int i=0;i<=9;++i){
        while(num[i]&&num2[9-i]){
            p1+=char(i+'0');p2+=char(9-i+'0');
            num[i]--;num2[9-i]--;
        }
    }
    for(int i=0;i<=9;++i){
        while(num[i]){
            p1+=char(i+'0');num[i]--;
        }
    }
    for(int i=0;i<=9;++i){
        while(num2[i]){
            p2+=char(i+'0');num2[i]--;
        }
    }
}
signed main(){
    cin>>n;
    for(char c:n){
        num[c-'0']++;
    }
    for(int i=1;i<=5;++i){
        int g=get(i);
        if(g>ans){
            ansid=i;
            ans=g;
            f0=now0;
        }
    }
    if(ans==0){
        sort(n.begin(),n.end(),greater<char>());
        cout<<n<<'\n'<<n<<'\n';
        return 0;
    }
    make(ansid);
    reverse(p1.begin(),p1.end());
    reverse(p2.begin(),p2.end());
    cout<<p1<<'\n'<<p2<<'\n';
    return 0;
}
```

---

## 作者：Light_Pursuer (赞：0)

# [Digits Permutations](https://www.luogu.com.cn/problem/CF138B) 1800

## Solution

发现，如果末尾一个是 $0$ 的话，那么上下两个加起来不是 $10$ 就是 $0$，那就把它们拆成两个就好了。

首先对于前一位加起来是 $10$ 的情况，当前两个数加起来一定是 $9$，知道了这点，枚举最后一位是 $10$ 的情况，再枚举可能和为 $9$ 的情况，最后处理两个 $0$ 放在最后的情况。使用双端队列记录答案即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e3+5;
int read()
{
	int ret=0,f=1;char c=getchar();
	while(!(c>='0'&&c<='9'))
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		ret=ret*10+c-'0';
		c=getchar();
	}
	return ret*f;
}
string s;
int len,cnt[N],p[N];
deque<int> d1,d2;
void solve()
{
	cin>>s;len=s.size();
	for(int i=0;i<len;i++) cnt[s[i]-'0']++;
	for(int i=0;i<=9;i++) p[i]=cnt[i];
	int flag=0;
	for(int i=1;i<=9;i++)
	{
		if(cnt[i]>cnt[9-i]&&p[10-i]>p[9-(10-i)])
		{
			d1.push_front(i);d2.push_front(10-i);
			cnt[i]--;p[10-i]--;flag=1;break;
		}
	}
	if(!flag)
	{
		for(int i=1;i<=9;i++)
		{
			if(cnt[i]&&p[10-i])
			{
				if(cnt[i]&&p[10-i])
				{
					d1.push_front(i);d2.push_front(10-i);
					cnt[i]--;p[10-i]--;break;
				}	
			}	
		} 
	}
	for(int i=0;i<=9;i++)
	{
		for(int j=1;j<=min(cnt[i],p[9-i]);j++)
		{
			d1.push_front(i);
			d2.push_front(9-i);
		}
		int k=min(cnt[i],p[9-i]);
		cnt[i]-=k,p[9-i]-=k;
	}
	while(cnt[0]&&p[0])
	{
		d1.push_back(0),d2.push_back(0);
		cnt[0]--,p[0]--;
	}
	for(int i=0;i<=9;i++)
	{
		for(int j=1;j<=cnt[i];j++)
		{
			d1.push_front(i);
		}
	}
	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=p[i];j++)
		{
			d2.push_front(i);
		}
	}
	while(d1.size())
	{
		cout<<d1.front();d1.pop_front();
	}
	cout<<endl;
	while(d2.size())
	{
		cout<<d2.front();d2.pop_front();
	}
}
signed main()
{
	solve();
	return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 题意
给定一个数 $n$，要求求出这个数的两个排列使这两个排列相加的末尾有最多的 $0$。
## 思路
很显然，当某一位为 $0$ 时那么两个数相加的和只有可能是 $0$ 和 $10$。当和为 $10$ 时会产生进位，而这时下一位的和就必须是 $9$。因此我们可以先找出一对相加等于 $10$ 的数，然后找相加等于 $9$ 的数，最后找相加等于 $0$ 的数（只能由 $0$ 和 $0$ 构成）。在找相加为 $10$ 的数的时候要对相加等于 $9$ 的数影响最小。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a[15],b[15],f;
deque<int> a1,a2;//储存答案
int main()
{
	cin>>s;
	for(int i=0;i<s.length();i++)
	{
		a[s[i]-'0']++;//统计剩余的数的个数
		b[s[i]-'0']++;
	}
	for(int i=1;i<=9;i++)
	{
		if(a[i]>a[9-i]&&b[10-i]>b[i-1])//找一对相加为10的数（不拆散任何一对相加为9的数）
		{
			a1.push_front(i);
			a2.push_front(10-i);
			a[i]--;
			b[10-i]--;
			f=1;
			break;
		}
	}
	if(!f)
	{
		for(int i=1;i<=9;i++)//必须拆散
		{
			if(a[i]&&b[10-i])
			{
				a1.push_front(i);
				a2.push_front(10-i);
				a[i]--;
				b[10-i]--;
				break;
			}
		}
	}
	for(int i=0;i<=9;i++)//找相加为9的数
	{
		for(int j=1;j<=min(a[i],b[9-i]);j++)
		{
			a1.push_front(i);
			a2.push_front(9-i);
		}
		int t=min(a[i],b[9-i]);
		a[i]-=t;
		b[9-i]-=t;
	}
	while(a[0]&&b[0])//找相加为0的数
	{
		a1.push_back(0);
		a2.push_back(0);
		a[0]--;
		b[0]--;
	}
	for(int i=0;i<=9;i++)
	{
		for(int j=1;j<=a[i];j++)//多出来的数
		{
			a1.push_front(i);
		}
		a[i]=0;
	}
	for(int i=0;i<=9;i++)
	{
		for(int j=1;j<=b[i];j++)//多出来的数
		{
			a2.push_front(i);
		}
		b[i]=0;
	}
	while(a1.size())//输出
	{
		cout<<a1.front();
		a1.pop_front();
	}
	cout<<endl;
	while(a2.size())//输出
	{
		cout<<a2.front();
		a2.pop_front();
	}
}
```


---

