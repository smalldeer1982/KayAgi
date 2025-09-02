# Polycarp's phone book

## 题目描述

There are $ n $ phone numbers in Polycarp's contacts on his phone. Each number is a 9-digit integer, starting with a digit different from $ 0 $ . All the numbers are distinct.

There is the latest version of Berdroid OS installed on Polycarp's phone. If some number is entered, is shows up all the numbers in the contacts for which there is a substring equal to the entered sequence of digits. For example, is there are three phone numbers in Polycarp's contacts: $ 123456789 $ , $ 100000000 $ and $ 100123456 $ , then:

- if he enters $ 00 $ two numbers will show up: $ 100000000 $ and $ 100123456 $ ,
- if he enters $ 123 $ two numbers will show up $ 123456789 $ and $ 100123456 $ ,
- if he enters $ 01 $ there will be only one number $ 100123456 $ .

For each of the phone numbers in Polycarp's contacts, find the minimum in length sequence of digits such that if Polycarp enters this sequence, Berdroid shows this only phone number.

## 样例 #1

### 输入

```
3
123456789
100000000
100123456
```

### 输出

```
9
000
01
```

## 样例 #2

### 输入

```
4
123456789
193456789
134567819
934567891
```

### 输出

```
2
193
81
91
```

# 题解

## 作者：404Not_Found (赞：2)

# 前言
~~这么明显的字典树TM没人写？4秒时限啊那没事了。~~

如前，这几乎是一道字典树的板子题，AC 之后发现大家都是  map +暴力……

[评测记录](https://www.luogu.com.cn/record/54404280)

甩了最优解第二两条街好吗？

# 正文

好吧不多BB了。先说一下为什么这是字典树。题目要求我们找到每个字符串**非公共部分**，那不就相当于每一次查询的时候删除公共部分吗？字典树就呼之欲出了。

这里就不详细解释字典树了，不会的可以看[这里](https://zhuanlan.zhihu.com/p/28891541)。

这里用上了字典树中比较少出现的删除操作，其实很简单，在插入的模板上稍微改一改就好了。

这里还要强调一下查询。在每一轮查询的时候去判断子串数量是否为 $0$ ，如果是的话就维护一下最小长度拷贝一下就好了。

建树：
```cpp
struct Trie{
	int next[10];
	int val;
} trie[5000005];
```

val 存储的是子串个数。

记得数组别开小了，$9$ 位的电话号码中共有 $9+8+7+6+5+4+3+2+1=45$ 个子串，长度之和也是 $45$ ，所以开 $7e4 \times 45$ 就够了。

插入：

```cpp
void ins(char *s){
	int len=strlen(s);
	int now=0;
	for(int i=0;i<len;i++)
	{
		int id=s[i]-'0';
		int to=trie[now].next[id];
		if(to==0)
		{
			to=++tot;
			trie[now].next[id]=to;
		}
		trie[to].val++;
		now=to;
	}
}
```

打板子，没什么好说的。

删除，在插入的基础上改一改就好了：

```cpp
void del(char *s)
{
	int len=strlen(s);
	int now=0;
	for(int i=0;i<len;i++)
	{
		int id=s[i]-'0';
		int to=trie[now].next[id];
		trie[to].val--;
		now=to;
	}
}
```

查询：

```cpp
void query(char *s)
{
	int len=strlen(s);
	int now=0;
	for(int i=0;i<len;i++)
	{
		tmp[i]=s[i];
		int id=s[i]-'0';
		int to=trie[now].next[id];
		if(trie[to].val==0)
		{
			if(i+1<minn)
			{
				minn=i+1;
				tmp[i+1]='\0';
				strcpy(ans,tmp);
				break;
			}
		}
		now=to;
	}
}
```
主函数也很简单，每次查询只要三个步骤：

1. 把公共子串删掉；

2. 枚举每个子串，有满足条件的子串没有出现，记录答案，维护最小；

3. 把每个子串重新插入。

代码：
```cpp
for(int i=1;i<=n;i++)
{
	minn=10;
	for(int j=0;j<9;j++) del(a[i]+j);
	for(int j=0;j<9;j++) query(a[i]+j);
	for(int j=0;j<9;j++) ins(a[i]+j);
	printf("%s\n",ans);
}
```

总的来说，字典树是一种**以空间换时间**的数据结构，像这道题要开 214MB 的内存，数据范围大了就不建议用字典树了。~~像CCF又不会给你动态开空间。~~


---

## 作者：Bai_R_X (赞：1)

## 思路
暴力，保存每个字符串的子串，再存进字典里。最后找一下出现次数为 $1$ 且长度最小的子串就行。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,i,j,k;
string s[70005];
map<string,int> mp;
vector<string> sons[70005];
signed main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>s[i];
		for(j=0;j<9;j++)
		{
			for(k=j;k<9;k++)
			{
				string son=s[i].substr(j,k-j+1);
				if(find(sons[i].begin(),sons[i].end(),son)==sons[i].end())mp[son]++;
				sons[i].push_back(son);
			}
		}
	}
	for(i=1;i<=n;i++)
	{
		int minsize=INT_MAX;
		string minstr;
		for(auto& it:sons[i])
		{
			if(mp[it]>1)continue;
			if(it.size()<minsize)
			{
				minsize=it.size();
				minstr=it;
			}
		}
		cout<<minstr<<endl;
	}
	return 0;
}
```

---

## 作者：kimi0705 (赞：0)

# 思路
观察数据范围发现比较小。然后可以用**暴力**加 **map** 的方法去做，可以不用字典树。

map 表示这个字符串是多少种字符串里的子串， 如果这个字符串里有多个 $a$ 串，只能算一个。例如样例 $1$ 中子串 `000` 只能算 $1$ 次，虽然在串 $2$ 中出现了很多次，但是这些都是重复的，只能算做一次，子串 `123456` 算 $2$ 次，因为在串 $1$ 和串 $3$ 中各出现了一次。

每次枚举每一个字符串的子串，放到 map 中，map++。

然后合法的识别码是一种字符串子串，不合法的有多个。

# 代码

```cpp
// LUOGU_RID: 111591976
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast") // 卡常....
using namespace std;
const int N = 7e4 + 10;
int n;
string s[N];
map<string, int> C;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1; i <= n; i++)
    {
        set<string> SET; // 为了防止重复计算，做了一个标记，相当于vis
        for (int L = 0; L < 9; L++)
        {
            for (int R = L; R < 9; R++)
            {
                string S = s[i].substr(L, R - L + 1);//表示得到从 L 开始得到长度为R - L + 1的子串。
                if (!SET.count(S))
                {
                    C[S]++;
                    SET.insert(S);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        bool Printed = false;
        for (int Len = 1; Len <= 9; Len++)
        {
            for (int L = 0; L + Len - 1 < 9; L++)
            {
                string S = s[i].substr(L, Len);
                if (C[S] == 1) // 只能出现一次。
                {
                    cout << S << '\n';
                    Printed = true;
                    break;
                }
            }
            if (Printed)
                break;
        }
    }
    return 0;
}
```

---

